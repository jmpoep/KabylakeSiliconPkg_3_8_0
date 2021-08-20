#ifndef __MrcMcRegister1xxx_h__
#define __MrcMcRegister1xxx_h__
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


#define DDRDATA8CH0_CR_RXTRAINRANK0_REG                                (0x00001000)

  #define DDRDATA8CH0_CR_RXTRAINRANK0_RxRcvEnPi_OFF                    ( 0)
  #define DDRDATA8CH0_CR_RXTRAINRANK0_RxRcvEnPi_WID                    ( 9)
  #define DDRDATA8CH0_CR_RXTRAINRANK0_RxRcvEnPi_MSK                    (0x000001FF)
  #define DDRDATA8CH0_CR_RXTRAINRANK0_RxRcvEnPi_MIN                    (0)
  #define DDRDATA8CH0_CR_RXTRAINRANK0_RxRcvEnPi_MAX                    (511) // 0x000001FF
  #define DDRDATA8CH0_CR_RXTRAINRANK0_RxRcvEnPi_DEF                    (0x00000000)
  #define DDRDATA8CH0_CR_RXTRAINRANK0_RxRcvEnPi_HSH                    (0x09001000)

  #define DDRDATA8CH0_CR_RXTRAINRANK0_RxDqsPPi_OFF                     ( 9)
  #define DDRDATA8CH0_CR_RXTRAINRANK0_RxDqsPPi_WID                     ( 6)
  #define DDRDATA8CH0_CR_RXTRAINRANK0_RxDqsPPi_MSK                     (0x00007E00)
  #define DDRDATA8CH0_CR_RXTRAINRANK0_RxDqsPPi_MIN                     (0)
  #define DDRDATA8CH0_CR_RXTRAINRANK0_RxDqsPPi_MAX                     (63) // 0x0000003F
  #define DDRDATA8CH0_CR_RXTRAINRANK0_RxDqsPPi_DEF                     (0x00000000)
  #define DDRDATA8CH0_CR_RXTRAINRANK0_RxDqsPPi_HSH                     (0x06091000)

  #define DDRDATA8CH0_CR_RXTRAINRANK0_RxEq_OFF                         (15)
  #define DDRDATA8CH0_CR_RXTRAINRANK0_RxEq_WID                         ( 5)
  #define DDRDATA8CH0_CR_RXTRAINRANK0_RxEq_MSK                         (0x000F8000)
  #define DDRDATA8CH0_CR_RXTRAINRANK0_RxEq_MIN                         (0)
  #define DDRDATA8CH0_CR_RXTRAINRANK0_RxEq_MAX                         (31) // 0x0000001F
  #define DDRDATA8CH0_CR_RXTRAINRANK0_RxEq_DEF                         (0x00000000)
  #define DDRDATA8CH0_CR_RXTRAINRANK0_RxEq_HSH                         (0x050F1000)

  #define DDRDATA8CH0_CR_RXTRAINRANK0_RxDqsNPi_OFF                     (20)
  #define DDRDATA8CH0_CR_RXTRAINRANK0_RxDqsNPi_WID                     ( 6)
  #define DDRDATA8CH0_CR_RXTRAINRANK0_RxDqsNPi_MSK                     (0x03F00000)
  #define DDRDATA8CH0_CR_RXTRAINRANK0_RxDqsNPi_MIN                     (0)
  #define DDRDATA8CH0_CR_RXTRAINRANK0_RxDqsNPi_MAX                     (63) // 0x0000003F
  #define DDRDATA8CH0_CR_RXTRAINRANK0_RxDqsNPi_DEF                     (0x00000000)
  #define DDRDATA8CH0_CR_RXTRAINRANK0_RxDqsNPi_HSH                     (0x06141000)

  #define DDRDATA8CH0_CR_RXTRAINRANK0_RxVref_OFF                       (26)
  #define DDRDATA8CH0_CR_RXTRAINRANK0_RxVref_WID                       ( 6)
  #define DDRDATA8CH0_CR_RXTRAINRANK0_RxVref_MSK                       (0xFC000000)
  #define DDRDATA8CH0_CR_RXTRAINRANK0_RxVref_MIN                       (-32)
  #define DDRDATA8CH0_CR_RXTRAINRANK0_RxVref_MAX                       (31) // 0x0000001F
  #define DDRDATA8CH0_CR_RXTRAINRANK0_RxVref_DEF                       (0x00000000)
  #define DDRDATA8CH0_CR_RXTRAINRANK0_RxVref_HSH                       (0x861A1000)

#define DDRDATA8CH0_CR_RXTRAINRANK1_REG                                (0x00001004)

  #define DDRDATA8CH0_CR_RXTRAINRANK1_RxRcvEnPi_OFF                    ( 0)
  #define DDRDATA8CH0_CR_RXTRAINRANK1_RxRcvEnPi_WID                    ( 9)
  #define DDRDATA8CH0_CR_RXTRAINRANK1_RxRcvEnPi_MSK                    (0x000001FF)
  #define DDRDATA8CH0_CR_RXTRAINRANK1_RxRcvEnPi_MIN                    (0)
  #define DDRDATA8CH0_CR_RXTRAINRANK1_RxRcvEnPi_MAX                    (511) // 0x000001FF
  #define DDRDATA8CH0_CR_RXTRAINRANK1_RxRcvEnPi_DEF                    (0x00000000)
  #define DDRDATA8CH0_CR_RXTRAINRANK1_RxRcvEnPi_HSH                    (0x09001004)

  #define DDRDATA8CH0_CR_RXTRAINRANK1_RxDqsPPi_OFF                     ( 9)
  #define DDRDATA8CH0_CR_RXTRAINRANK1_RxDqsPPi_WID                     ( 6)
  #define DDRDATA8CH0_CR_RXTRAINRANK1_RxDqsPPi_MSK                     (0x00007E00)
  #define DDRDATA8CH0_CR_RXTRAINRANK1_RxDqsPPi_MIN                     (0)
  #define DDRDATA8CH0_CR_RXTRAINRANK1_RxDqsPPi_MAX                     (63) // 0x0000003F
  #define DDRDATA8CH0_CR_RXTRAINRANK1_RxDqsPPi_DEF                     (0x00000000)
  #define DDRDATA8CH0_CR_RXTRAINRANK1_RxDqsPPi_HSH                     (0x06091004)

  #define DDRDATA8CH0_CR_RXTRAINRANK1_RxEq_OFF                         (15)
  #define DDRDATA8CH0_CR_RXTRAINRANK1_RxEq_WID                         ( 5)
  #define DDRDATA8CH0_CR_RXTRAINRANK1_RxEq_MSK                         (0x000F8000)
  #define DDRDATA8CH0_CR_RXTRAINRANK1_RxEq_MIN                         (0)
  #define DDRDATA8CH0_CR_RXTRAINRANK1_RxEq_MAX                         (31) // 0x0000001F
  #define DDRDATA8CH0_CR_RXTRAINRANK1_RxEq_DEF                         (0x00000000)
  #define DDRDATA8CH0_CR_RXTRAINRANK1_RxEq_HSH                         (0x050F1004)

  #define DDRDATA8CH0_CR_RXTRAINRANK1_RxDqsNPi_OFF                     (20)
  #define DDRDATA8CH0_CR_RXTRAINRANK1_RxDqsNPi_WID                     ( 6)
  #define DDRDATA8CH0_CR_RXTRAINRANK1_RxDqsNPi_MSK                     (0x03F00000)
  #define DDRDATA8CH0_CR_RXTRAINRANK1_RxDqsNPi_MIN                     (0)
  #define DDRDATA8CH0_CR_RXTRAINRANK1_RxDqsNPi_MAX                     (63) // 0x0000003F
  #define DDRDATA8CH0_CR_RXTRAINRANK1_RxDqsNPi_DEF                     (0x00000000)
  #define DDRDATA8CH0_CR_RXTRAINRANK1_RxDqsNPi_HSH                     (0x06141004)

  #define DDRDATA8CH0_CR_RXTRAINRANK1_RxVref_OFF                       (26)
  #define DDRDATA8CH0_CR_RXTRAINRANK1_RxVref_WID                       ( 6)
  #define DDRDATA8CH0_CR_RXTRAINRANK1_RxVref_MSK                       (0xFC000000)
  #define DDRDATA8CH0_CR_RXTRAINRANK1_RxVref_MIN                       (-32)
  #define DDRDATA8CH0_CR_RXTRAINRANK1_RxVref_MAX                       (31) // 0x0000001F
  #define DDRDATA8CH0_CR_RXTRAINRANK1_RxVref_DEF                       (0x00000000)
  #define DDRDATA8CH0_CR_RXTRAINRANK1_RxVref_HSH                       (0x861A1004)

#define DDRDATA8CH0_CR_RXTRAINRANK2_REG                                (0x00001008)

  #define DDRDATA8CH0_CR_RXTRAINRANK2_RxRcvEnPi_OFF                    ( 0)
  #define DDRDATA8CH0_CR_RXTRAINRANK2_RxRcvEnPi_WID                    ( 9)
  #define DDRDATA8CH0_CR_RXTRAINRANK2_RxRcvEnPi_MSK                    (0x000001FF)
  #define DDRDATA8CH0_CR_RXTRAINRANK2_RxRcvEnPi_MIN                    (0)
  #define DDRDATA8CH0_CR_RXTRAINRANK2_RxRcvEnPi_MAX                    (511) // 0x000001FF
  #define DDRDATA8CH0_CR_RXTRAINRANK2_RxRcvEnPi_DEF                    (0x00000000)
  #define DDRDATA8CH0_CR_RXTRAINRANK2_RxRcvEnPi_HSH                    (0x09001008)

  #define DDRDATA8CH0_CR_RXTRAINRANK2_RxDqsPPi_OFF                     ( 9)
  #define DDRDATA8CH0_CR_RXTRAINRANK2_RxDqsPPi_WID                     ( 6)
  #define DDRDATA8CH0_CR_RXTRAINRANK2_RxDqsPPi_MSK                     (0x00007E00)
  #define DDRDATA8CH0_CR_RXTRAINRANK2_RxDqsPPi_MIN                     (0)
  #define DDRDATA8CH0_CR_RXTRAINRANK2_RxDqsPPi_MAX                     (63) // 0x0000003F
  #define DDRDATA8CH0_CR_RXTRAINRANK2_RxDqsPPi_DEF                     (0x00000000)
  #define DDRDATA8CH0_CR_RXTRAINRANK2_RxDqsPPi_HSH                     (0x06091008)

  #define DDRDATA8CH0_CR_RXTRAINRANK2_RxEq_OFF                         (15)
  #define DDRDATA8CH0_CR_RXTRAINRANK2_RxEq_WID                         ( 5)
  #define DDRDATA8CH0_CR_RXTRAINRANK2_RxEq_MSK                         (0x000F8000)
  #define DDRDATA8CH0_CR_RXTRAINRANK2_RxEq_MIN                         (0)
  #define DDRDATA8CH0_CR_RXTRAINRANK2_RxEq_MAX                         (31) // 0x0000001F
  #define DDRDATA8CH0_CR_RXTRAINRANK2_RxEq_DEF                         (0x00000000)
  #define DDRDATA8CH0_CR_RXTRAINRANK2_RxEq_HSH                         (0x050F1008)

  #define DDRDATA8CH0_CR_RXTRAINRANK2_RxDqsNPi_OFF                     (20)
  #define DDRDATA8CH0_CR_RXTRAINRANK2_RxDqsNPi_WID                     ( 6)
  #define DDRDATA8CH0_CR_RXTRAINRANK2_RxDqsNPi_MSK                     (0x03F00000)
  #define DDRDATA8CH0_CR_RXTRAINRANK2_RxDqsNPi_MIN                     (0)
  #define DDRDATA8CH0_CR_RXTRAINRANK2_RxDqsNPi_MAX                     (63) // 0x0000003F
  #define DDRDATA8CH0_CR_RXTRAINRANK2_RxDqsNPi_DEF                     (0x00000000)
  #define DDRDATA8CH0_CR_RXTRAINRANK2_RxDqsNPi_HSH                     (0x06141008)

  #define DDRDATA8CH0_CR_RXTRAINRANK2_RxVref_OFF                       (26)
  #define DDRDATA8CH0_CR_RXTRAINRANK2_RxVref_WID                       ( 6)
  #define DDRDATA8CH0_CR_RXTRAINRANK2_RxVref_MSK                       (0xFC000000)
  #define DDRDATA8CH0_CR_RXTRAINRANK2_RxVref_MIN                       (-32)
  #define DDRDATA8CH0_CR_RXTRAINRANK2_RxVref_MAX                       (31) // 0x0000001F
  #define DDRDATA8CH0_CR_RXTRAINRANK2_RxVref_DEF                       (0x00000000)
  #define DDRDATA8CH0_CR_RXTRAINRANK2_RxVref_HSH                       (0x861A1008)

#define DDRDATA8CH0_CR_RXTRAINRANK3_REG                                (0x0000100C)

  #define DDRDATA8CH0_CR_RXTRAINRANK3_RxRcvEnPi_OFF                    ( 0)
  #define DDRDATA8CH0_CR_RXTRAINRANK3_RxRcvEnPi_WID                    ( 9)
  #define DDRDATA8CH0_CR_RXTRAINRANK3_RxRcvEnPi_MSK                    (0x000001FF)
  #define DDRDATA8CH0_CR_RXTRAINRANK3_RxRcvEnPi_MIN                    (0)
  #define DDRDATA8CH0_CR_RXTRAINRANK3_RxRcvEnPi_MAX                    (511) // 0x000001FF
  #define DDRDATA8CH0_CR_RXTRAINRANK3_RxRcvEnPi_DEF                    (0x00000000)
  #define DDRDATA8CH0_CR_RXTRAINRANK3_RxRcvEnPi_HSH                    (0x0900100C)

  #define DDRDATA8CH0_CR_RXTRAINRANK3_RxDqsPPi_OFF                     ( 9)
  #define DDRDATA8CH0_CR_RXTRAINRANK3_RxDqsPPi_WID                     ( 6)
  #define DDRDATA8CH0_CR_RXTRAINRANK3_RxDqsPPi_MSK                     (0x00007E00)
  #define DDRDATA8CH0_CR_RXTRAINRANK3_RxDqsPPi_MIN                     (0)
  #define DDRDATA8CH0_CR_RXTRAINRANK3_RxDqsPPi_MAX                     (63) // 0x0000003F
  #define DDRDATA8CH0_CR_RXTRAINRANK3_RxDqsPPi_DEF                     (0x00000000)
  #define DDRDATA8CH0_CR_RXTRAINRANK3_RxDqsPPi_HSH                     (0x0609100C)

  #define DDRDATA8CH0_CR_RXTRAINRANK3_RxEq_OFF                         (15)
  #define DDRDATA8CH0_CR_RXTRAINRANK3_RxEq_WID                         ( 5)
  #define DDRDATA8CH0_CR_RXTRAINRANK3_RxEq_MSK                         (0x000F8000)
  #define DDRDATA8CH0_CR_RXTRAINRANK3_RxEq_MIN                         (0)
  #define DDRDATA8CH0_CR_RXTRAINRANK3_RxEq_MAX                         (31) // 0x0000001F
  #define DDRDATA8CH0_CR_RXTRAINRANK3_RxEq_DEF                         (0x00000000)
  #define DDRDATA8CH0_CR_RXTRAINRANK3_RxEq_HSH                         (0x050F100C)

  #define DDRDATA8CH0_CR_RXTRAINRANK3_RxDqsNPi_OFF                     (20)
  #define DDRDATA8CH0_CR_RXTRAINRANK3_RxDqsNPi_WID                     ( 6)
  #define DDRDATA8CH0_CR_RXTRAINRANK3_RxDqsNPi_MSK                     (0x03F00000)
  #define DDRDATA8CH0_CR_RXTRAINRANK3_RxDqsNPi_MIN                     (0)
  #define DDRDATA8CH0_CR_RXTRAINRANK3_RxDqsNPi_MAX                     (63) // 0x0000003F
  #define DDRDATA8CH0_CR_RXTRAINRANK3_RxDqsNPi_DEF                     (0x00000000)
  #define DDRDATA8CH0_CR_RXTRAINRANK3_RxDqsNPi_HSH                     (0x0614100C)

  #define DDRDATA8CH0_CR_RXTRAINRANK3_RxVref_OFF                       (26)
  #define DDRDATA8CH0_CR_RXTRAINRANK3_RxVref_WID                       ( 6)
  #define DDRDATA8CH0_CR_RXTRAINRANK3_RxVref_MSK                       (0xFC000000)
  #define DDRDATA8CH0_CR_RXTRAINRANK3_RxVref_MIN                       (-32)
  #define DDRDATA8CH0_CR_RXTRAINRANK3_RxVref_MAX                       (31) // 0x0000001F
  #define DDRDATA8CH0_CR_RXTRAINRANK3_RxVref_DEF                       (0x00000000)
  #define DDRDATA8CH0_CR_RXTRAINRANK3_RxVref_HSH                       (0x861A100C)

#define DDRDATA8CH0_CR_RXPERBITRANK0_REG                               (0x00001010)

  #define DDRDATA8CH0_CR_RXPERBITRANK0_Lane0_OFF                       ( 0)
  #define DDRDATA8CH0_CR_RXPERBITRANK0_Lane0_WID                       ( 4)
  #define DDRDATA8CH0_CR_RXPERBITRANK0_Lane0_MSK                       (0x0000000F)
  #define DDRDATA8CH0_CR_RXPERBITRANK0_Lane0_MIN                       (0)
  #define DDRDATA8CH0_CR_RXPERBITRANK0_Lane0_MAX                       (15) // 0x0000000F
  #define DDRDATA8CH0_CR_RXPERBITRANK0_Lane0_DEF                       (0x00000000)
  #define DDRDATA8CH0_CR_RXPERBITRANK0_Lane0_HSH                       (0x04001010)

  #define DDRDATA8CH0_CR_RXPERBITRANK0_Lane1_OFF                       ( 4)
  #define DDRDATA8CH0_CR_RXPERBITRANK0_Lane1_WID                       ( 4)
  #define DDRDATA8CH0_CR_RXPERBITRANK0_Lane1_MSK                       (0x000000F0)
  #define DDRDATA8CH0_CR_RXPERBITRANK0_Lane1_MIN                       (0)
  #define DDRDATA8CH0_CR_RXPERBITRANK0_Lane1_MAX                       (15) // 0x0000000F
  #define DDRDATA8CH0_CR_RXPERBITRANK0_Lane1_DEF                       (0x00000000)
  #define DDRDATA8CH0_CR_RXPERBITRANK0_Lane1_HSH                       (0x04041010)

  #define DDRDATA8CH0_CR_RXPERBITRANK0_Lane2_OFF                       ( 8)
  #define DDRDATA8CH0_CR_RXPERBITRANK0_Lane2_WID                       ( 4)
  #define DDRDATA8CH0_CR_RXPERBITRANK0_Lane2_MSK                       (0x00000F00)
  #define DDRDATA8CH0_CR_RXPERBITRANK0_Lane2_MIN                       (0)
  #define DDRDATA8CH0_CR_RXPERBITRANK0_Lane2_MAX                       (15) // 0x0000000F
  #define DDRDATA8CH0_CR_RXPERBITRANK0_Lane2_DEF                       (0x00000000)
  #define DDRDATA8CH0_CR_RXPERBITRANK0_Lane2_HSH                       (0x04081010)

  #define DDRDATA8CH0_CR_RXPERBITRANK0_Lane3_OFF                       (12)
  #define DDRDATA8CH0_CR_RXPERBITRANK0_Lane3_WID                       ( 4)
  #define DDRDATA8CH0_CR_RXPERBITRANK0_Lane3_MSK                       (0x0000F000)
  #define DDRDATA8CH0_CR_RXPERBITRANK0_Lane3_MIN                       (0)
  #define DDRDATA8CH0_CR_RXPERBITRANK0_Lane3_MAX                       (15) // 0x0000000F
  #define DDRDATA8CH0_CR_RXPERBITRANK0_Lane3_DEF                       (0x00000000)
  #define DDRDATA8CH0_CR_RXPERBITRANK0_Lane3_HSH                       (0x040C1010)

  #define DDRDATA8CH0_CR_RXPERBITRANK0_Lane4_OFF                       (16)
  #define DDRDATA8CH0_CR_RXPERBITRANK0_Lane4_WID                       ( 4)
  #define DDRDATA8CH0_CR_RXPERBITRANK0_Lane4_MSK                       (0x000F0000)
  #define DDRDATA8CH0_CR_RXPERBITRANK0_Lane4_MIN                       (0)
  #define DDRDATA8CH0_CR_RXPERBITRANK0_Lane4_MAX                       (15) // 0x0000000F
  #define DDRDATA8CH0_CR_RXPERBITRANK0_Lane4_DEF                       (0x00000000)
  #define DDRDATA8CH0_CR_RXPERBITRANK0_Lane4_HSH                       (0x04101010)

  #define DDRDATA8CH0_CR_RXPERBITRANK0_Lane5_OFF                       (20)
  #define DDRDATA8CH0_CR_RXPERBITRANK0_Lane5_WID                       ( 4)
  #define DDRDATA8CH0_CR_RXPERBITRANK0_Lane5_MSK                       (0x00F00000)
  #define DDRDATA8CH0_CR_RXPERBITRANK0_Lane5_MIN                       (0)
  #define DDRDATA8CH0_CR_RXPERBITRANK0_Lane5_MAX                       (15) // 0x0000000F
  #define DDRDATA8CH0_CR_RXPERBITRANK0_Lane5_DEF                       (0x00000000)
  #define DDRDATA8CH0_CR_RXPERBITRANK0_Lane5_HSH                       (0x04141010)

  #define DDRDATA8CH0_CR_RXPERBITRANK0_Lane6_OFF                       (24)
  #define DDRDATA8CH0_CR_RXPERBITRANK0_Lane6_WID                       ( 4)
  #define DDRDATA8CH0_CR_RXPERBITRANK0_Lane6_MSK                       (0x0F000000)
  #define DDRDATA8CH0_CR_RXPERBITRANK0_Lane6_MIN                       (0)
  #define DDRDATA8CH0_CR_RXPERBITRANK0_Lane6_MAX                       (15) // 0x0000000F
  #define DDRDATA8CH0_CR_RXPERBITRANK0_Lane6_DEF                       (0x00000000)
  #define DDRDATA8CH0_CR_RXPERBITRANK0_Lane6_HSH                       (0x04181010)

  #define DDRDATA8CH0_CR_RXPERBITRANK0_Lane7_OFF                       (28)
  #define DDRDATA8CH0_CR_RXPERBITRANK0_Lane7_WID                       ( 4)
  #define DDRDATA8CH0_CR_RXPERBITRANK0_Lane7_MSK                       (0xF0000000)
  #define DDRDATA8CH0_CR_RXPERBITRANK0_Lane7_MIN                       (0)
  #define DDRDATA8CH0_CR_RXPERBITRANK0_Lane7_MAX                       (15) // 0x0000000F
  #define DDRDATA8CH0_CR_RXPERBITRANK0_Lane7_DEF                       (0x00000000)
  #define DDRDATA8CH0_CR_RXPERBITRANK0_Lane7_HSH                       (0x041C1010)

#define DDRDATA8CH0_CR_RXPERBITRANK1_REG                               (0x00001014)

  #define DDRDATA8CH0_CR_RXPERBITRANK1_Lane0_OFF                       ( 0)
  #define DDRDATA8CH0_CR_RXPERBITRANK1_Lane0_WID                       ( 4)
  #define DDRDATA8CH0_CR_RXPERBITRANK1_Lane0_MSK                       (0x0000000F)
  #define DDRDATA8CH0_CR_RXPERBITRANK1_Lane0_MIN                       (0)
  #define DDRDATA8CH0_CR_RXPERBITRANK1_Lane0_MAX                       (15) // 0x0000000F
  #define DDRDATA8CH0_CR_RXPERBITRANK1_Lane0_DEF                       (0x00000000)
  #define DDRDATA8CH0_CR_RXPERBITRANK1_Lane0_HSH                       (0x04001014)

  #define DDRDATA8CH0_CR_RXPERBITRANK1_Lane1_OFF                       ( 4)
  #define DDRDATA8CH0_CR_RXPERBITRANK1_Lane1_WID                       ( 4)
  #define DDRDATA8CH0_CR_RXPERBITRANK1_Lane1_MSK                       (0x000000F0)
  #define DDRDATA8CH0_CR_RXPERBITRANK1_Lane1_MIN                       (0)
  #define DDRDATA8CH0_CR_RXPERBITRANK1_Lane1_MAX                       (15) // 0x0000000F
  #define DDRDATA8CH0_CR_RXPERBITRANK1_Lane1_DEF                       (0x00000000)
  #define DDRDATA8CH0_CR_RXPERBITRANK1_Lane1_HSH                       (0x04041014)

  #define DDRDATA8CH0_CR_RXPERBITRANK1_Lane2_OFF                       ( 8)
  #define DDRDATA8CH0_CR_RXPERBITRANK1_Lane2_WID                       ( 4)
  #define DDRDATA8CH0_CR_RXPERBITRANK1_Lane2_MSK                       (0x00000F00)
  #define DDRDATA8CH0_CR_RXPERBITRANK1_Lane2_MIN                       (0)
  #define DDRDATA8CH0_CR_RXPERBITRANK1_Lane2_MAX                       (15) // 0x0000000F
  #define DDRDATA8CH0_CR_RXPERBITRANK1_Lane2_DEF                       (0x00000000)
  #define DDRDATA8CH0_CR_RXPERBITRANK1_Lane2_HSH                       (0x04081014)

  #define DDRDATA8CH0_CR_RXPERBITRANK1_Lane3_OFF                       (12)
  #define DDRDATA8CH0_CR_RXPERBITRANK1_Lane3_WID                       ( 4)
  #define DDRDATA8CH0_CR_RXPERBITRANK1_Lane3_MSK                       (0x0000F000)
  #define DDRDATA8CH0_CR_RXPERBITRANK1_Lane3_MIN                       (0)
  #define DDRDATA8CH0_CR_RXPERBITRANK1_Lane3_MAX                       (15) // 0x0000000F
  #define DDRDATA8CH0_CR_RXPERBITRANK1_Lane3_DEF                       (0x00000000)
  #define DDRDATA8CH0_CR_RXPERBITRANK1_Lane3_HSH                       (0x040C1014)

  #define DDRDATA8CH0_CR_RXPERBITRANK1_Lane4_OFF                       (16)
  #define DDRDATA8CH0_CR_RXPERBITRANK1_Lane4_WID                       ( 4)
  #define DDRDATA8CH0_CR_RXPERBITRANK1_Lane4_MSK                       (0x000F0000)
  #define DDRDATA8CH0_CR_RXPERBITRANK1_Lane4_MIN                       (0)
  #define DDRDATA8CH0_CR_RXPERBITRANK1_Lane4_MAX                       (15) // 0x0000000F
  #define DDRDATA8CH0_CR_RXPERBITRANK1_Lane4_DEF                       (0x00000000)
  #define DDRDATA8CH0_CR_RXPERBITRANK1_Lane4_HSH                       (0x04101014)

  #define DDRDATA8CH0_CR_RXPERBITRANK1_Lane5_OFF                       (20)
  #define DDRDATA8CH0_CR_RXPERBITRANK1_Lane5_WID                       ( 4)
  #define DDRDATA8CH0_CR_RXPERBITRANK1_Lane5_MSK                       (0x00F00000)
  #define DDRDATA8CH0_CR_RXPERBITRANK1_Lane5_MIN                       (0)
  #define DDRDATA8CH0_CR_RXPERBITRANK1_Lane5_MAX                       (15) // 0x0000000F
  #define DDRDATA8CH0_CR_RXPERBITRANK1_Lane5_DEF                       (0x00000000)
  #define DDRDATA8CH0_CR_RXPERBITRANK1_Lane5_HSH                       (0x04141014)

  #define DDRDATA8CH0_CR_RXPERBITRANK1_Lane6_OFF                       (24)
  #define DDRDATA8CH0_CR_RXPERBITRANK1_Lane6_WID                       ( 4)
  #define DDRDATA8CH0_CR_RXPERBITRANK1_Lane6_MSK                       (0x0F000000)
  #define DDRDATA8CH0_CR_RXPERBITRANK1_Lane6_MIN                       (0)
  #define DDRDATA8CH0_CR_RXPERBITRANK1_Lane6_MAX                       (15) // 0x0000000F
  #define DDRDATA8CH0_CR_RXPERBITRANK1_Lane6_DEF                       (0x00000000)
  #define DDRDATA8CH0_CR_RXPERBITRANK1_Lane6_HSH                       (0x04181014)

  #define DDRDATA8CH0_CR_RXPERBITRANK1_Lane7_OFF                       (28)
  #define DDRDATA8CH0_CR_RXPERBITRANK1_Lane7_WID                       ( 4)
  #define DDRDATA8CH0_CR_RXPERBITRANK1_Lane7_MSK                       (0xF0000000)
  #define DDRDATA8CH0_CR_RXPERBITRANK1_Lane7_MIN                       (0)
  #define DDRDATA8CH0_CR_RXPERBITRANK1_Lane7_MAX                       (15) // 0x0000000F
  #define DDRDATA8CH0_CR_RXPERBITRANK1_Lane7_DEF                       (0x00000000)
  #define DDRDATA8CH0_CR_RXPERBITRANK1_Lane7_HSH                       (0x041C1014)

#define DDRDATA8CH0_CR_RXPERBITRANK2_REG                               (0x00001018)

  #define DDRDATA8CH0_CR_RXPERBITRANK2_Lane0_OFF                       ( 0)
  #define DDRDATA8CH0_CR_RXPERBITRANK2_Lane0_WID                       ( 4)
  #define DDRDATA8CH0_CR_RXPERBITRANK2_Lane0_MSK                       (0x0000000F)
  #define DDRDATA8CH0_CR_RXPERBITRANK2_Lane0_MIN                       (0)
  #define DDRDATA8CH0_CR_RXPERBITRANK2_Lane0_MAX                       (15) // 0x0000000F
  #define DDRDATA8CH0_CR_RXPERBITRANK2_Lane0_DEF                       (0x00000000)
  #define DDRDATA8CH0_CR_RXPERBITRANK2_Lane0_HSH                       (0x04001018)

  #define DDRDATA8CH0_CR_RXPERBITRANK2_Lane1_OFF                       ( 4)
  #define DDRDATA8CH0_CR_RXPERBITRANK2_Lane1_WID                       ( 4)
  #define DDRDATA8CH0_CR_RXPERBITRANK2_Lane1_MSK                       (0x000000F0)
  #define DDRDATA8CH0_CR_RXPERBITRANK2_Lane1_MIN                       (0)
  #define DDRDATA8CH0_CR_RXPERBITRANK2_Lane1_MAX                       (15) // 0x0000000F
  #define DDRDATA8CH0_CR_RXPERBITRANK2_Lane1_DEF                       (0x00000000)
  #define DDRDATA8CH0_CR_RXPERBITRANK2_Lane1_HSH                       (0x04041018)

  #define DDRDATA8CH0_CR_RXPERBITRANK2_Lane2_OFF                       ( 8)
  #define DDRDATA8CH0_CR_RXPERBITRANK2_Lane2_WID                       ( 4)
  #define DDRDATA8CH0_CR_RXPERBITRANK2_Lane2_MSK                       (0x00000F00)
  #define DDRDATA8CH0_CR_RXPERBITRANK2_Lane2_MIN                       (0)
  #define DDRDATA8CH0_CR_RXPERBITRANK2_Lane2_MAX                       (15) // 0x0000000F
  #define DDRDATA8CH0_CR_RXPERBITRANK2_Lane2_DEF                       (0x00000000)
  #define DDRDATA8CH0_CR_RXPERBITRANK2_Lane2_HSH                       (0x04081018)

  #define DDRDATA8CH0_CR_RXPERBITRANK2_Lane3_OFF                       (12)
  #define DDRDATA8CH0_CR_RXPERBITRANK2_Lane3_WID                       ( 4)
  #define DDRDATA8CH0_CR_RXPERBITRANK2_Lane3_MSK                       (0x0000F000)
  #define DDRDATA8CH0_CR_RXPERBITRANK2_Lane3_MIN                       (0)
  #define DDRDATA8CH0_CR_RXPERBITRANK2_Lane3_MAX                       (15) // 0x0000000F
  #define DDRDATA8CH0_CR_RXPERBITRANK2_Lane3_DEF                       (0x00000000)
  #define DDRDATA8CH0_CR_RXPERBITRANK2_Lane3_HSH                       (0x040C1018)

  #define DDRDATA8CH0_CR_RXPERBITRANK2_Lane4_OFF                       (16)
  #define DDRDATA8CH0_CR_RXPERBITRANK2_Lane4_WID                       ( 4)
  #define DDRDATA8CH0_CR_RXPERBITRANK2_Lane4_MSK                       (0x000F0000)
  #define DDRDATA8CH0_CR_RXPERBITRANK2_Lane4_MIN                       (0)
  #define DDRDATA8CH0_CR_RXPERBITRANK2_Lane4_MAX                       (15) // 0x0000000F
  #define DDRDATA8CH0_CR_RXPERBITRANK2_Lane4_DEF                       (0x00000000)
  #define DDRDATA8CH0_CR_RXPERBITRANK2_Lane4_HSH                       (0x04101018)

  #define DDRDATA8CH0_CR_RXPERBITRANK2_Lane5_OFF                       (20)
  #define DDRDATA8CH0_CR_RXPERBITRANK2_Lane5_WID                       ( 4)
  #define DDRDATA8CH0_CR_RXPERBITRANK2_Lane5_MSK                       (0x00F00000)
  #define DDRDATA8CH0_CR_RXPERBITRANK2_Lane5_MIN                       (0)
  #define DDRDATA8CH0_CR_RXPERBITRANK2_Lane5_MAX                       (15) // 0x0000000F
  #define DDRDATA8CH0_CR_RXPERBITRANK2_Lane5_DEF                       (0x00000000)
  #define DDRDATA8CH0_CR_RXPERBITRANK2_Lane5_HSH                       (0x04141018)

  #define DDRDATA8CH0_CR_RXPERBITRANK2_Lane6_OFF                       (24)
  #define DDRDATA8CH0_CR_RXPERBITRANK2_Lane6_WID                       ( 4)
  #define DDRDATA8CH0_CR_RXPERBITRANK2_Lane6_MSK                       (0x0F000000)
  #define DDRDATA8CH0_CR_RXPERBITRANK2_Lane6_MIN                       (0)
  #define DDRDATA8CH0_CR_RXPERBITRANK2_Lane6_MAX                       (15) // 0x0000000F
  #define DDRDATA8CH0_CR_RXPERBITRANK2_Lane6_DEF                       (0x00000000)
  #define DDRDATA8CH0_CR_RXPERBITRANK2_Lane6_HSH                       (0x04181018)

  #define DDRDATA8CH0_CR_RXPERBITRANK2_Lane7_OFF                       (28)
  #define DDRDATA8CH0_CR_RXPERBITRANK2_Lane7_WID                       ( 4)
  #define DDRDATA8CH0_CR_RXPERBITRANK2_Lane7_MSK                       (0xF0000000)
  #define DDRDATA8CH0_CR_RXPERBITRANK2_Lane7_MIN                       (0)
  #define DDRDATA8CH0_CR_RXPERBITRANK2_Lane7_MAX                       (15) // 0x0000000F
  #define DDRDATA8CH0_CR_RXPERBITRANK2_Lane7_DEF                       (0x00000000)
  #define DDRDATA8CH0_CR_RXPERBITRANK2_Lane7_HSH                       (0x041C1018)

#define DDRDATA8CH0_CR_RXPERBITRANK3_REG                               (0x0000101C)

  #define DDRDATA8CH0_CR_RXPERBITRANK3_Lane0_OFF                       ( 0)
  #define DDRDATA8CH0_CR_RXPERBITRANK3_Lane0_WID                       ( 4)
  #define DDRDATA8CH0_CR_RXPERBITRANK3_Lane0_MSK                       (0x0000000F)
  #define DDRDATA8CH0_CR_RXPERBITRANK3_Lane0_MIN                       (0)
  #define DDRDATA8CH0_CR_RXPERBITRANK3_Lane0_MAX                       (15) // 0x0000000F
  #define DDRDATA8CH0_CR_RXPERBITRANK3_Lane0_DEF                       (0x00000000)
  #define DDRDATA8CH0_CR_RXPERBITRANK3_Lane0_HSH                       (0x0400101C)

  #define DDRDATA8CH0_CR_RXPERBITRANK3_Lane1_OFF                       ( 4)
  #define DDRDATA8CH0_CR_RXPERBITRANK3_Lane1_WID                       ( 4)
  #define DDRDATA8CH0_CR_RXPERBITRANK3_Lane1_MSK                       (0x000000F0)
  #define DDRDATA8CH0_CR_RXPERBITRANK3_Lane1_MIN                       (0)
  #define DDRDATA8CH0_CR_RXPERBITRANK3_Lane1_MAX                       (15) // 0x0000000F
  #define DDRDATA8CH0_CR_RXPERBITRANK3_Lane1_DEF                       (0x00000000)
  #define DDRDATA8CH0_CR_RXPERBITRANK3_Lane1_HSH                       (0x0404101C)

  #define DDRDATA8CH0_CR_RXPERBITRANK3_Lane2_OFF                       ( 8)
  #define DDRDATA8CH0_CR_RXPERBITRANK3_Lane2_WID                       ( 4)
  #define DDRDATA8CH0_CR_RXPERBITRANK3_Lane2_MSK                       (0x00000F00)
  #define DDRDATA8CH0_CR_RXPERBITRANK3_Lane2_MIN                       (0)
  #define DDRDATA8CH0_CR_RXPERBITRANK3_Lane2_MAX                       (15) // 0x0000000F
  #define DDRDATA8CH0_CR_RXPERBITRANK3_Lane2_DEF                       (0x00000000)
  #define DDRDATA8CH0_CR_RXPERBITRANK3_Lane2_HSH                       (0x0408101C)

  #define DDRDATA8CH0_CR_RXPERBITRANK3_Lane3_OFF                       (12)
  #define DDRDATA8CH0_CR_RXPERBITRANK3_Lane3_WID                       ( 4)
  #define DDRDATA8CH0_CR_RXPERBITRANK3_Lane3_MSK                       (0x0000F000)
  #define DDRDATA8CH0_CR_RXPERBITRANK3_Lane3_MIN                       (0)
  #define DDRDATA8CH0_CR_RXPERBITRANK3_Lane3_MAX                       (15) // 0x0000000F
  #define DDRDATA8CH0_CR_RXPERBITRANK3_Lane3_DEF                       (0x00000000)
  #define DDRDATA8CH0_CR_RXPERBITRANK3_Lane3_HSH                       (0x040C101C)

  #define DDRDATA8CH0_CR_RXPERBITRANK3_Lane4_OFF                       (16)
  #define DDRDATA8CH0_CR_RXPERBITRANK3_Lane4_WID                       ( 4)
  #define DDRDATA8CH0_CR_RXPERBITRANK3_Lane4_MSK                       (0x000F0000)
  #define DDRDATA8CH0_CR_RXPERBITRANK3_Lane4_MIN                       (0)
  #define DDRDATA8CH0_CR_RXPERBITRANK3_Lane4_MAX                       (15) // 0x0000000F
  #define DDRDATA8CH0_CR_RXPERBITRANK3_Lane4_DEF                       (0x00000000)
  #define DDRDATA8CH0_CR_RXPERBITRANK3_Lane4_HSH                       (0x0410101C)

  #define DDRDATA8CH0_CR_RXPERBITRANK3_Lane5_OFF                       (20)
  #define DDRDATA8CH0_CR_RXPERBITRANK3_Lane5_WID                       ( 4)
  #define DDRDATA8CH0_CR_RXPERBITRANK3_Lane5_MSK                       (0x00F00000)
  #define DDRDATA8CH0_CR_RXPERBITRANK3_Lane5_MIN                       (0)
  #define DDRDATA8CH0_CR_RXPERBITRANK3_Lane5_MAX                       (15) // 0x0000000F
  #define DDRDATA8CH0_CR_RXPERBITRANK3_Lane5_DEF                       (0x00000000)
  #define DDRDATA8CH0_CR_RXPERBITRANK3_Lane5_HSH                       (0x0414101C)

  #define DDRDATA8CH0_CR_RXPERBITRANK3_Lane6_OFF                       (24)
  #define DDRDATA8CH0_CR_RXPERBITRANK3_Lane6_WID                       ( 4)
  #define DDRDATA8CH0_CR_RXPERBITRANK3_Lane6_MSK                       (0x0F000000)
  #define DDRDATA8CH0_CR_RXPERBITRANK3_Lane6_MIN                       (0)
  #define DDRDATA8CH0_CR_RXPERBITRANK3_Lane6_MAX                       (15) // 0x0000000F
  #define DDRDATA8CH0_CR_RXPERBITRANK3_Lane6_DEF                       (0x00000000)
  #define DDRDATA8CH0_CR_RXPERBITRANK3_Lane6_HSH                       (0x0418101C)

  #define DDRDATA8CH0_CR_RXPERBITRANK3_Lane7_OFF                       (28)
  #define DDRDATA8CH0_CR_RXPERBITRANK3_Lane7_WID                       ( 4)
  #define DDRDATA8CH0_CR_RXPERBITRANK3_Lane7_MSK                       (0xF0000000)
  #define DDRDATA8CH0_CR_RXPERBITRANK3_Lane7_MIN                       (0)
  #define DDRDATA8CH0_CR_RXPERBITRANK3_Lane7_MAX                       (15) // 0x0000000F
  #define DDRDATA8CH0_CR_RXPERBITRANK3_Lane7_DEF                       (0x00000000)
  #define DDRDATA8CH0_CR_RXPERBITRANK3_Lane7_HSH                       (0x041C101C)

#define DDRDATA8CH0_CR_TXTRAINRANK0_REG                                (0x00001020)

  #define DDRDATA8CH0_CR_TXTRAINRANK0_TxDqDelay_OFF                    ( 0)
  #define DDRDATA8CH0_CR_TXTRAINRANK0_TxDqDelay_WID                    ( 9)
  #define DDRDATA8CH0_CR_TXTRAINRANK0_TxDqDelay_MSK                    (0x000001FF)
  #define DDRDATA8CH0_CR_TXTRAINRANK0_TxDqDelay_MIN                    (0)
  #define DDRDATA8CH0_CR_TXTRAINRANK0_TxDqDelay_MAX                    (511) // 0x000001FF
  #define DDRDATA8CH0_CR_TXTRAINRANK0_TxDqDelay_DEF                    (0x00000000)
  #define DDRDATA8CH0_CR_TXTRAINRANK0_TxDqDelay_HSH                    (0x09001020)

  #define DDRDATA8CH0_CR_TXTRAINRANK0_TxDqsDelay_OFF                   ( 9)
  #define DDRDATA8CH0_CR_TXTRAINRANK0_TxDqsDelay_WID                   ( 9)
  #define DDRDATA8CH0_CR_TXTRAINRANK0_TxDqsDelay_MSK                   (0x0003FE00)
  #define DDRDATA8CH0_CR_TXTRAINRANK0_TxDqsDelay_MIN                   (0)
  #define DDRDATA8CH0_CR_TXTRAINRANK0_TxDqsDelay_MAX                   (511) // 0x000001FF
  #define DDRDATA8CH0_CR_TXTRAINRANK0_TxDqsDelay_DEF                   (0x00000000)
  #define DDRDATA8CH0_CR_TXTRAINRANK0_TxDqsDelay_HSH                   (0x09091020)

  #define DDRDATA8CH0_CR_TXTRAINRANK0_Spare0_OFF                       (18)
  #define DDRDATA8CH0_CR_TXTRAINRANK0_Spare0_WID                       ( 2)
  #define DDRDATA8CH0_CR_TXTRAINRANK0_Spare0_MSK                       (0x000C0000)
  #define DDRDATA8CH0_CR_TXTRAINRANK0_Spare0_MIN                       (0)
  #define DDRDATA8CH0_CR_TXTRAINRANK0_Spare0_MAX                       (3) // 0x00000003
  #define DDRDATA8CH0_CR_TXTRAINRANK0_Spare0_DEF                       (0x00000000)
  #define DDRDATA8CH0_CR_TXTRAINRANK0_Spare0_HSH                       (0x02121020)

  #define DDRDATA8CH0_CR_TXTRAINRANK0_TxEqualization_OFF               (20)
  #define DDRDATA8CH0_CR_TXTRAINRANK0_TxEqualization_WID               ( 6)
  #define DDRDATA8CH0_CR_TXTRAINRANK0_TxEqualization_MSK               (0x03F00000)
  #define DDRDATA8CH0_CR_TXTRAINRANK0_TxEqualization_MIN               (0)
  #define DDRDATA8CH0_CR_TXTRAINRANK0_TxEqualization_MAX               (63) // 0x0000003F
  #define DDRDATA8CH0_CR_TXTRAINRANK0_TxEqualization_DEF               (0x00000000)
  #define DDRDATA8CH0_CR_TXTRAINRANK0_TxEqualization_HSH               (0x06141020)

  #define DDRDATA8CH0_CR_TXTRAINRANK0_Spare1_OFF                       (26)
  #define DDRDATA8CH0_CR_TXTRAINRANK0_Spare1_WID                       ( 6)
  #define DDRDATA8CH0_CR_TXTRAINRANK0_Spare1_MSK                       (0xFC000000)
  #define DDRDATA8CH0_CR_TXTRAINRANK0_Spare1_MIN                       (0)
  #define DDRDATA8CH0_CR_TXTRAINRANK0_Spare1_MAX                       (63) // 0x0000003F
  #define DDRDATA8CH0_CR_TXTRAINRANK0_Spare1_DEF                       (0x00000000)
  #define DDRDATA8CH0_CR_TXTRAINRANK0_Spare1_HSH                       (0x061A1020)

#define DDRDATA8CH0_CR_TXTRAINRANK1_REG                                (0x00001024)

  #define DDRDATA8CH0_CR_TXTRAINRANK1_TxDqDelay_OFF                    ( 0)
  #define DDRDATA8CH0_CR_TXTRAINRANK1_TxDqDelay_WID                    ( 9)
  #define DDRDATA8CH0_CR_TXTRAINRANK1_TxDqDelay_MSK                    (0x000001FF)
  #define DDRDATA8CH0_CR_TXTRAINRANK1_TxDqDelay_MIN                    (0)
  #define DDRDATA8CH0_CR_TXTRAINRANK1_TxDqDelay_MAX                    (511) // 0x000001FF
  #define DDRDATA8CH0_CR_TXTRAINRANK1_TxDqDelay_DEF                    (0x00000000)
  #define DDRDATA8CH0_CR_TXTRAINRANK1_TxDqDelay_HSH                    (0x09001024)

  #define DDRDATA8CH0_CR_TXTRAINRANK1_TxDqsDelay_OFF                   ( 9)
  #define DDRDATA8CH0_CR_TXTRAINRANK1_TxDqsDelay_WID                   ( 9)
  #define DDRDATA8CH0_CR_TXTRAINRANK1_TxDqsDelay_MSK                   (0x0003FE00)
  #define DDRDATA8CH0_CR_TXTRAINRANK1_TxDqsDelay_MIN                   (0)
  #define DDRDATA8CH0_CR_TXTRAINRANK1_TxDqsDelay_MAX                   (511) // 0x000001FF
  #define DDRDATA8CH0_CR_TXTRAINRANK1_TxDqsDelay_DEF                   (0x00000000)
  #define DDRDATA8CH0_CR_TXTRAINRANK1_TxDqsDelay_HSH                   (0x09091024)

  #define DDRDATA8CH0_CR_TXTRAINRANK1_Spare0_OFF                       (18)
  #define DDRDATA8CH0_CR_TXTRAINRANK1_Spare0_WID                       ( 2)
  #define DDRDATA8CH0_CR_TXTRAINRANK1_Spare0_MSK                       (0x000C0000)
  #define DDRDATA8CH0_CR_TXTRAINRANK1_Spare0_MIN                       (0)
  #define DDRDATA8CH0_CR_TXTRAINRANK1_Spare0_MAX                       (3) // 0x00000003
  #define DDRDATA8CH0_CR_TXTRAINRANK1_Spare0_DEF                       (0x00000000)
  #define DDRDATA8CH0_CR_TXTRAINRANK1_Spare0_HSH                       (0x02121024)

  #define DDRDATA8CH0_CR_TXTRAINRANK1_TxEqualization_OFF               (20)
  #define DDRDATA8CH0_CR_TXTRAINRANK1_TxEqualization_WID               ( 6)
  #define DDRDATA8CH0_CR_TXTRAINRANK1_TxEqualization_MSK               (0x03F00000)
  #define DDRDATA8CH0_CR_TXTRAINRANK1_TxEqualization_MIN               (0)
  #define DDRDATA8CH0_CR_TXTRAINRANK1_TxEqualization_MAX               (63) // 0x0000003F
  #define DDRDATA8CH0_CR_TXTRAINRANK1_TxEqualization_DEF               (0x00000000)
  #define DDRDATA8CH0_CR_TXTRAINRANK1_TxEqualization_HSH               (0x06141024)

  #define DDRDATA8CH0_CR_TXTRAINRANK1_Spare1_OFF                       (26)
  #define DDRDATA8CH0_CR_TXTRAINRANK1_Spare1_WID                       ( 6)
  #define DDRDATA8CH0_CR_TXTRAINRANK1_Spare1_MSK                       (0xFC000000)
  #define DDRDATA8CH0_CR_TXTRAINRANK1_Spare1_MIN                       (0)
  #define DDRDATA8CH0_CR_TXTRAINRANK1_Spare1_MAX                       (63) // 0x0000003F
  #define DDRDATA8CH0_CR_TXTRAINRANK1_Spare1_DEF                       (0x00000000)
  #define DDRDATA8CH0_CR_TXTRAINRANK1_Spare1_HSH                       (0x061A1024)

#define DDRDATA8CH0_CR_TXTRAINRANK2_REG                                (0x00001028)

  #define DDRDATA8CH0_CR_TXTRAINRANK2_TxDqDelay_OFF                    ( 0)
  #define DDRDATA8CH0_CR_TXTRAINRANK2_TxDqDelay_WID                    ( 9)
  #define DDRDATA8CH0_CR_TXTRAINRANK2_TxDqDelay_MSK                    (0x000001FF)
  #define DDRDATA8CH0_CR_TXTRAINRANK2_TxDqDelay_MIN                    (0)
  #define DDRDATA8CH0_CR_TXTRAINRANK2_TxDqDelay_MAX                    (511) // 0x000001FF
  #define DDRDATA8CH0_CR_TXTRAINRANK2_TxDqDelay_DEF                    (0x00000000)
  #define DDRDATA8CH0_CR_TXTRAINRANK2_TxDqDelay_HSH                    (0x09001028)

  #define DDRDATA8CH0_CR_TXTRAINRANK2_TxDqsDelay_OFF                   ( 9)
  #define DDRDATA8CH0_CR_TXTRAINRANK2_TxDqsDelay_WID                   ( 9)
  #define DDRDATA8CH0_CR_TXTRAINRANK2_TxDqsDelay_MSK                   (0x0003FE00)
  #define DDRDATA8CH0_CR_TXTRAINRANK2_TxDqsDelay_MIN                   (0)
  #define DDRDATA8CH0_CR_TXTRAINRANK2_TxDqsDelay_MAX                   (511) // 0x000001FF
  #define DDRDATA8CH0_CR_TXTRAINRANK2_TxDqsDelay_DEF                   (0x00000000)
  #define DDRDATA8CH0_CR_TXTRAINRANK2_TxDqsDelay_HSH                   (0x09091028)

  #define DDRDATA8CH0_CR_TXTRAINRANK2_Spare0_OFF                       (18)
  #define DDRDATA8CH0_CR_TXTRAINRANK2_Spare0_WID                       ( 2)
  #define DDRDATA8CH0_CR_TXTRAINRANK2_Spare0_MSK                       (0x000C0000)
  #define DDRDATA8CH0_CR_TXTRAINRANK2_Spare0_MIN                       (0)
  #define DDRDATA8CH0_CR_TXTRAINRANK2_Spare0_MAX                       (3) // 0x00000003
  #define DDRDATA8CH0_CR_TXTRAINRANK2_Spare0_DEF                       (0x00000000)
  #define DDRDATA8CH0_CR_TXTRAINRANK2_Spare0_HSH                       (0x02121028)

  #define DDRDATA8CH0_CR_TXTRAINRANK2_TxEqualization_OFF               (20)
  #define DDRDATA8CH0_CR_TXTRAINRANK2_TxEqualization_WID               ( 6)
  #define DDRDATA8CH0_CR_TXTRAINRANK2_TxEqualization_MSK               (0x03F00000)
  #define DDRDATA8CH0_CR_TXTRAINRANK2_TxEqualization_MIN               (0)
  #define DDRDATA8CH0_CR_TXTRAINRANK2_TxEqualization_MAX               (63) // 0x0000003F
  #define DDRDATA8CH0_CR_TXTRAINRANK2_TxEqualization_DEF               (0x00000000)
  #define DDRDATA8CH0_CR_TXTRAINRANK2_TxEqualization_HSH               (0x06141028)

  #define DDRDATA8CH0_CR_TXTRAINRANK2_Spare1_OFF                       (26)
  #define DDRDATA8CH0_CR_TXTRAINRANK2_Spare1_WID                       ( 6)
  #define DDRDATA8CH0_CR_TXTRAINRANK2_Spare1_MSK                       (0xFC000000)
  #define DDRDATA8CH0_CR_TXTRAINRANK2_Spare1_MIN                       (0)
  #define DDRDATA8CH0_CR_TXTRAINRANK2_Spare1_MAX                       (63) // 0x0000003F
  #define DDRDATA8CH0_CR_TXTRAINRANK2_Spare1_DEF                       (0x00000000)
  #define DDRDATA8CH0_CR_TXTRAINRANK2_Spare1_HSH                       (0x061A1028)

#define DDRDATA8CH0_CR_TXTRAINRANK3_REG                                (0x0000102C)

  #define DDRDATA8CH0_CR_TXTRAINRANK3_TxDqDelay_OFF                    ( 0)
  #define DDRDATA8CH0_CR_TXTRAINRANK3_TxDqDelay_WID                    ( 9)
  #define DDRDATA8CH0_CR_TXTRAINRANK3_TxDqDelay_MSK                    (0x000001FF)
  #define DDRDATA8CH0_CR_TXTRAINRANK3_TxDqDelay_MIN                    (0)
  #define DDRDATA8CH0_CR_TXTRAINRANK3_TxDqDelay_MAX                    (511) // 0x000001FF
  #define DDRDATA8CH0_CR_TXTRAINRANK3_TxDqDelay_DEF                    (0x00000000)
  #define DDRDATA8CH0_CR_TXTRAINRANK3_TxDqDelay_HSH                    (0x0900102C)

  #define DDRDATA8CH0_CR_TXTRAINRANK3_TxDqsDelay_OFF                   ( 9)
  #define DDRDATA8CH0_CR_TXTRAINRANK3_TxDqsDelay_WID                   ( 9)
  #define DDRDATA8CH0_CR_TXTRAINRANK3_TxDqsDelay_MSK                   (0x0003FE00)
  #define DDRDATA8CH0_CR_TXTRAINRANK3_TxDqsDelay_MIN                   (0)
  #define DDRDATA8CH0_CR_TXTRAINRANK3_TxDqsDelay_MAX                   (511) // 0x000001FF
  #define DDRDATA8CH0_CR_TXTRAINRANK3_TxDqsDelay_DEF                   (0x00000000)
  #define DDRDATA8CH0_CR_TXTRAINRANK3_TxDqsDelay_HSH                   (0x0909102C)

  #define DDRDATA8CH0_CR_TXTRAINRANK3_Spare0_OFF                       (18)
  #define DDRDATA8CH0_CR_TXTRAINRANK3_Spare0_WID                       ( 2)
  #define DDRDATA8CH0_CR_TXTRAINRANK3_Spare0_MSK                       (0x000C0000)
  #define DDRDATA8CH0_CR_TXTRAINRANK3_Spare0_MIN                       (0)
  #define DDRDATA8CH0_CR_TXTRAINRANK3_Spare0_MAX                       (3) // 0x00000003
  #define DDRDATA8CH0_CR_TXTRAINRANK3_Spare0_DEF                       (0x00000000)
  #define DDRDATA8CH0_CR_TXTRAINRANK3_Spare0_HSH                       (0x0212102C)

  #define DDRDATA8CH0_CR_TXTRAINRANK3_TxEqualization_OFF               (20)
  #define DDRDATA8CH0_CR_TXTRAINRANK3_TxEqualization_WID               ( 6)
  #define DDRDATA8CH0_CR_TXTRAINRANK3_TxEqualization_MSK               (0x03F00000)
  #define DDRDATA8CH0_CR_TXTRAINRANK3_TxEqualization_MIN               (0)
  #define DDRDATA8CH0_CR_TXTRAINRANK3_TxEqualization_MAX               (63) // 0x0000003F
  #define DDRDATA8CH0_CR_TXTRAINRANK3_TxEqualization_DEF               (0x00000000)
  #define DDRDATA8CH0_CR_TXTRAINRANK3_TxEqualization_HSH               (0x0614102C)

  #define DDRDATA8CH0_CR_TXTRAINRANK3_Spare1_OFF                       (26)
  #define DDRDATA8CH0_CR_TXTRAINRANK3_Spare1_WID                       ( 6)
  #define DDRDATA8CH0_CR_TXTRAINRANK3_Spare1_MSK                       (0xFC000000)
  #define DDRDATA8CH0_CR_TXTRAINRANK3_Spare1_MIN                       (0)
  #define DDRDATA8CH0_CR_TXTRAINRANK3_Spare1_MAX                       (63) // 0x0000003F
  #define DDRDATA8CH0_CR_TXTRAINRANK3_Spare1_DEF                       (0x00000000)
  #define DDRDATA8CH0_CR_TXTRAINRANK3_Spare1_HSH                       (0x061A102C)

#define DDRDATA8CH0_CR_TXPERBITRANK0_REG                               (0x00001030)

  #define DDRDATA8CH0_CR_TXPERBITRANK0_Lane0_OFF                       ( 0)
  #define DDRDATA8CH0_CR_TXPERBITRANK0_Lane0_WID                       ( 4)
  #define DDRDATA8CH0_CR_TXPERBITRANK0_Lane0_MSK                       (0x0000000F)
  #define DDRDATA8CH0_CR_TXPERBITRANK0_Lane0_MIN                       (0)
  #define DDRDATA8CH0_CR_TXPERBITRANK0_Lane0_MAX                       (15) // 0x0000000F
  #define DDRDATA8CH0_CR_TXPERBITRANK0_Lane0_DEF                       (0x00000000)
  #define DDRDATA8CH0_CR_TXPERBITRANK0_Lane0_HSH                       (0x04001030)

  #define DDRDATA8CH0_CR_TXPERBITRANK0_Lane1_OFF                       ( 4)
  #define DDRDATA8CH0_CR_TXPERBITRANK0_Lane1_WID                       ( 4)
  #define DDRDATA8CH0_CR_TXPERBITRANK0_Lane1_MSK                       (0x000000F0)
  #define DDRDATA8CH0_CR_TXPERBITRANK0_Lane1_MIN                       (0)
  #define DDRDATA8CH0_CR_TXPERBITRANK0_Lane1_MAX                       (15) // 0x0000000F
  #define DDRDATA8CH0_CR_TXPERBITRANK0_Lane1_DEF                       (0x00000000)
  #define DDRDATA8CH0_CR_TXPERBITRANK0_Lane1_HSH                       (0x04041030)

  #define DDRDATA8CH0_CR_TXPERBITRANK0_Lane2_OFF                       ( 8)
  #define DDRDATA8CH0_CR_TXPERBITRANK0_Lane2_WID                       ( 4)
  #define DDRDATA8CH0_CR_TXPERBITRANK0_Lane2_MSK                       (0x00000F00)
  #define DDRDATA8CH0_CR_TXPERBITRANK0_Lane2_MIN                       (0)
  #define DDRDATA8CH0_CR_TXPERBITRANK0_Lane2_MAX                       (15) // 0x0000000F
  #define DDRDATA8CH0_CR_TXPERBITRANK0_Lane2_DEF                       (0x00000000)
  #define DDRDATA8CH0_CR_TXPERBITRANK0_Lane2_HSH                       (0x04081030)

  #define DDRDATA8CH0_CR_TXPERBITRANK0_Lane3_OFF                       (12)
  #define DDRDATA8CH0_CR_TXPERBITRANK0_Lane3_WID                       ( 4)
  #define DDRDATA8CH0_CR_TXPERBITRANK0_Lane3_MSK                       (0x0000F000)
  #define DDRDATA8CH0_CR_TXPERBITRANK0_Lane3_MIN                       (0)
  #define DDRDATA8CH0_CR_TXPERBITRANK0_Lane3_MAX                       (15) // 0x0000000F
  #define DDRDATA8CH0_CR_TXPERBITRANK0_Lane3_DEF                       (0x00000000)
  #define DDRDATA8CH0_CR_TXPERBITRANK0_Lane3_HSH                       (0x040C1030)

  #define DDRDATA8CH0_CR_TXPERBITRANK0_Lane4_OFF                       (16)
  #define DDRDATA8CH0_CR_TXPERBITRANK0_Lane4_WID                       ( 4)
  #define DDRDATA8CH0_CR_TXPERBITRANK0_Lane4_MSK                       (0x000F0000)
  #define DDRDATA8CH0_CR_TXPERBITRANK0_Lane4_MIN                       (0)
  #define DDRDATA8CH0_CR_TXPERBITRANK0_Lane4_MAX                       (15) // 0x0000000F
  #define DDRDATA8CH0_CR_TXPERBITRANK0_Lane4_DEF                       (0x00000000)
  #define DDRDATA8CH0_CR_TXPERBITRANK0_Lane4_HSH                       (0x04101030)

  #define DDRDATA8CH0_CR_TXPERBITRANK0_Lane5_OFF                       (20)
  #define DDRDATA8CH0_CR_TXPERBITRANK0_Lane5_WID                       ( 4)
  #define DDRDATA8CH0_CR_TXPERBITRANK0_Lane5_MSK                       (0x00F00000)
  #define DDRDATA8CH0_CR_TXPERBITRANK0_Lane5_MIN                       (0)
  #define DDRDATA8CH0_CR_TXPERBITRANK0_Lane5_MAX                       (15) // 0x0000000F
  #define DDRDATA8CH0_CR_TXPERBITRANK0_Lane5_DEF                       (0x00000000)
  #define DDRDATA8CH0_CR_TXPERBITRANK0_Lane5_HSH                       (0x04141030)

  #define DDRDATA8CH0_CR_TXPERBITRANK0_Lane6_OFF                       (24)
  #define DDRDATA8CH0_CR_TXPERBITRANK0_Lane6_WID                       ( 4)
  #define DDRDATA8CH0_CR_TXPERBITRANK0_Lane6_MSK                       (0x0F000000)
  #define DDRDATA8CH0_CR_TXPERBITRANK0_Lane6_MIN                       (0)
  #define DDRDATA8CH0_CR_TXPERBITRANK0_Lane6_MAX                       (15) // 0x0000000F
  #define DDRDATA8CH0_CR_TXPERBITRANK0_Lane6_DEF                       (0x00000000)
  #define DDRDATA8CH0_CR_TXPERBITRANK0_Lane6_HSH                       (0x04181030)

  #define DDRDATA8CH0_CR_TXPERBITRANK0_Lane7_OFF                       (28)
  #define DDRDATA8CH0_CR_TXPERBITRANK0_Lane7_WID                       ( 4)
  #define DDRDATA8CH0_CR_TXPERBITRANK0_Lane7_MSK                       (0xF0000000)
  #define DDRDATA8CH0_CR_TXPERBITRANK0_Lane7_MIN                       (0)
  #define DDRDATA8CH0_CR_TXPERBITRANK0_Lane7_MAX                       (15) // 0x0000000F
  #define DDRDATA8CH0_CR_TXPERBITRANK0_Lane7_DEF                       (0x00000000)
  #define DDRDATA8CH0_CR_TXPERBITRANK0_Lane7_HSH                       (0x041C1030)

#define DDRDATA8CH0_CR_TXPERBITRANK1_REG                               (0x00001034)

  #define DDRDATA8CH0_CR_TXPERBITRANK1_Lane0_OFF                       ( 0)
  #define DDRDATA8CH0_CR_TXPERBITRANK1_Lane0_WID                       ( 4)
  #define DDRDATA8CH0_CR_TXPERBITRANK1_Lane0_MSK                       (0x0000000F)
  #define DDRDATA8CH0_CR_TXPERBITRANK1_Lane0_MIN                       (0)
  #define DDRDATA8CH0_CR_TXPERBITRANK1_Lane0_MAX                       (15) // 0x0000000F
  #define DDRDATA8CH0_CR_TXPERBITRANK1_Lane0_DEF                       (0x00000000)
  #define DDRDATA8CH0_CR_TXPERBITRANK1_Lane0_HSH                       (0x04001034)

  #define DDRDATA8CH0_CR_TXPERBITRANK1_Lane1_OFF                       ( 4)
  #define DDRDATA8CH0_CR_TXPERBITRANK1_Lane1_WID                       ( 4)
  #define DDRDATA8CH0_CR_TXPERBITRANK1_Lane1_MSK                       (0x000000F0)
  #define DDRDATA8CH0_CR_TXPERBITRANK1_Lane1_MIN                       (0)
  #define DDRDATA8CH0_CR_TXPERBITRANK1_Lane1_MAX                       (15) // 0x0000000F
  #define DDRDATA8CH0_CR_TXPERBITRANK1_Lane1_DEF                       (0x00000000)
  #define DDRDATA8CH0_CR_TXPERBITRANK1_Lane1_HSH                       (0x04041034)

  #define DDRDATA8CH0_CR_TXPERBITRANK1_Lane2_OFF                       ( 8)
  #define DDRDATA8CH0_CR_TXPERBITRANK1_Lane2_WID                       ( 4)
  #define DDRDATA8CH0_CR_TXPERBITRANK1_Lane2_MSK                       (0x00000F00)
  #define DDRDATA8CH0_CR_TXPERBITRANK1_Lane2_MIN                       (0)
  #define DDRDATA8CH0_CR_TXPERBITRANK1_Lane2_MAX                       (15) // 0x0000000F
  #define DDRDATA8CH0_CR_TXPERBITRANK1_Lane2_DEF                       (0x00000000)
  #define DDRDATA8CH0_CR_TXPERBITRANK1_Lane2_HSH                       (0x04081034)

  #define DDRDATA8CH0_CR_TXPERBITRANK1_Lane3_OFF                       (12)
  #define DDRDATA8CH0_CR_TXPERBITRANK1_Lane3_WID                       ( 4)
  #define DDRDATA8CH0_CR_TXPERBITRANK1_Lane3_MSK                       (0x0000F000)
  #define DDRDATA8CH0_CR_TXPERBITRANK1_Lane3_MIN                       (0)
  #define DDRDATA8CH0_CR_TXPERBITRANK1_Lane3_MAX                       (15) // 0x0000000F
  #define DDRDATA8CH0_CR_TXPERBITRANK1_Lane3_DEF                       (0x00000000)
  #define DDRDATA8CH0_CR_TXPERBITRANK1_Lane3_HSH                       (0x040C1034)

  #define DDRDATA8CH0_CR_TXPERBITRANK1_Lane4_OFF                       (16)
  #define DDRDATA8CH0_CR_TXPERBITRANK1_Lane4_WID                       ( 4)
  #define DDRDATA8CH0_CR_TXPERBITRANK1_Lane4_MSK                       (0x000F0000)
  #define DDRDATA8CH0_CR_TXPERBITRANK1_Lane4_MIN                       (0)
  #define DDRDATA8CH0_CR_TXPERBITRANK1_Lane4_MAX                       (15) // 0x0000000F
  #define DDRDATA8CH0_CR_TXPERBITRANK1_Lane4_DEF                       (0x00000000)
  #define DDRDATA8CH0_CR_TXPERBITRANK1_Lane4_HSH                       (0x04101034)

  #define DDRDATA8CH0_CR_TXPERBITRANK1_Lane5_OFF                       (20)
  #define DDRDATA8CH0_CR_TXPERBITRANK1_Lane5_WID                       ( 4)
  #define DDRDATA8CH0_CR_TXPERBITRANK1_Lane5_MSK                       (0x00F00000)
  #define DDRDATA8CH0_CR_TXPERBITRANK1_Lane5_MIN                       (0)
  #define DDRDATA8CH0_CR_TXPERBITRANK1_Lane5_MAX                       (15) // 0x0000000F
  #define DDRDATA8CH0_CR_TXPERBITRANK1_Lane5_DEF                       (0x00000000)
  #define DDRDATA8CH0_CR_TXPERBITRANK1_Lane5_HSH                       (0x04141034)

  #define DDRDATA8CH0_CR_TXPERBITRANK1_Lane6_OFF                       (24)
  #define DDRDATA8CH0_CR_TXPERBITRANK1_Lane6_WID                       ( 4)
  #define DDRDATA8CH0_CR_TXPERBITRANK1_Lane6_MSK                       (0x0F000000)
  #define DDRDATA8CH0_CR_TXPERBITRANK1_Lane6_MIN                       (0)
  #define DDRDATA8CH0_CR_TXPERBITRANK1_Lane6_MAX                       (15) // 0x0000000F
  #define DDRDATA8CH0_CR_TXPERBITRANK1_Lane6_DEF                       (0x00000000)
  #define DDRDATA8CH0_CR_TXPERBITRANK1_Lane6_HSH                       (0x04181034)

  #define DDRDATA8CH0_CR_TXPERBITRANK1_Lane7_OFF                       (28)
  #define DDRDATA8CH0_CR_TXPERBITRANK1_Lane7_WID                       ( 4)
  #define DDRDATA8CH0_CR_TXPERBITRANK1_Lane7_MSK                       (0xF0000000)
  #define DDRDATA8CH0_CR_TXPERBITRANK1_Lane7_MIN                       (0)
  #define DDRDATA8CH0_CR_TXPERBITRANK1_Lane7_MAX                       (15) // 0x0000000F
  #define DDRDATA8CH0_CR_TXPERBITRANK1_Lane7_DEF                       (0x00000000)
  #define DDRDATA8CH0_CR_TXPERBITRANK1_Lane7_HSH                       (0x041C1034)

#define DDRDATA8CH0_CR_TXPERBITRANK2_REG                               (0x00001038)

  #define DDRDATA8CH0_CR_TXPERBITRANK2_Lane0_OFF                       ( 0)
  #define DDRDATA8CH0_CR_TXPERBITRANK2_Lane0_WID                       ( 4)
  #define DDRDATA8CH0_CR_TXPERBITRANK2_Lane0_MSK                       (0x0000000F)
  #define DDRDATA8CH0_CR_TXPERBITRANK2_Lane0_MIN                       (0)
  #define DDRDATA8CH0_CR_TXPERBITRANK2_Lane0_MAX                       (15) // 0x0000000F
  #define DDRDATA8CH0_CR_TXPERBITRANK2_Lane0_DEF                       (0x00000000)
  #define DDRDATA8CH0_CR_TXPERBITRANK2_Lane0_HSH                       (0x04001038)

  #define DDRDATA8CH0_CR_TXPERBITRANK2_Lane1_OFF                       ( 4)
  #define DDRDATA8CH0_CR_TXPERBITRANK2_Lane1_WID                       ( 4)
  #define DDRDATA8CH0_CR_TXPERBITRANK2_Lane1_MSK                       (0x000000F0)
  #define DDRDATA8CH0_CR_TXPERBITRANK2_Lane1_MIN                       (0)
  #define DDRDATA8CH0_CR_TXPERBITRANK2_Lane1_MAX                       (15) // 0x0000000F
  #define DDRDATA8CH0_CR_TXPERBITRANK2_Lane1_DEF                       (0x00000000)
  #define DDRDATA8CH0_CR_TXPERBITRANK2_Lane1_HSH                       (0x04041038)

  #define DDRDATA8CH0_CR_TXPERBITRANK2_Lane2_OFF                       ( 8)
  #define DDRDATA8CH0_CR_TXPERBITRANK2_Lane2_WID                       ( 4)
  #define DDRDATA8CH0_CR_TXPERBITRANK2_Lane2_MSK                       (0x00000F00)
  #define DDRDATA8CH0_CR_TXPERBITRANK2_Lane2_MIN                       (0)
  #define DDRDATA8CH0_CR_TXPERBITRANK2_Lane2_MAX                       (15) // 0x0000000F
  #define DDRDATA8CH0_CR_TXPERBITRANK2_Lane2_DEF                       (0x00000000)
  #define DDRDATA8CH0_CR_TXPERBITRANK2_Lane2_HSH                       (0x04081038)

  #define DDRDATA8CH0_CR_TXPERBITRANK2_Lane3_OFF                       (12)
  #define DDRDATA8CH0_CR_TXPERBITRANK2_Lane3_WID                       ( 4)
  #define DDRDATA8CH0_CR_TXPERBITRANK2_Lane3_MSK                       (0x0000F000)
  #define DDRDATA8CH0_CR_TXPERBITRANK2_Lane3_MIN                       (0)
  #define DDRDATA8CH0_CR_TXPERBITRANK2_Lane3_MAX                       (15) // 0x0000000F
  #define DDRDATA8CH0_CR_TXPERBITRANK2_Lane3_DEF                       (0x00000000)
  #define DDRDATA8CH0_CR_TXPERBITRANK2_Lane3_HSH                       (0x040C1038)

  #define DDRDATA8CH0_CR_TXPERBITRANK2_Lane4_OFF                       (16)
  #define DDRDATA8CH0_CR_TXPERBITRANK2_Lane4_WID                       ( 4)
  #define DDRDATA8CH0_CR_TXPERBITRANK2_Lane4_MSK                       (0x000F0000)
  #define DDRDATA8CH0_CR_TXPERBITRANK2_Lane4_MIN                       (0)
  #define DDRDATA8CH0_CR_TXPERBITRANK2_Lane4_MAX                       (15) // 0x0000000F
  #define DDRDATA8CH0_CR_TXPERBITRANK2_Lane4_DEF                       (0x00000000)
  #define DDRDATA8CH0_CR_TXPERBITRANK2_Lane4_HSH                       (0x04101038)

  #define DDRDATA8CH0_CR_TXPERBITRANK2_Lane5_OFF                       (20)
  #define DDRDATA8CH0_CR_TXPERBITRANK2_Lane5_WID                       ( 4)
  #define DDRDATA8CH0_CR_TXPERBITRANK2_Lane5_MSK                       (0x00F00000)
  #define DDRDATA8CH0_CR_TXPERBITRANK2_Lane5_MIN                       (0)
  #define DDRDATA8CH0_CR_TXPERBITRANK2_Lane5_MAX                       (15) // 0x0000000F
  #define DDRDATA8CH0_CR_TXPERBITRANK2_Lane5_DEF                       (0x00000000)
  #define DDRDATA8CH0_CR_TXPERBITRANK2_Lane5_HSH                       (0x04141038)

  #define DDRDATA8CH0_CR_TXPERBITRANK2_Lane6_OFF                       (24)
  #define DDRDATA8CH0_CR_TXPERBITRANK2_Lane6_WID                       ( 4)
  #define DDRDATA8CH0_CR_TXPERBITRANK2_Lane6_MSK                       (0x0F000000)
  #define DDRDATA8CH0_CR_TXPERBITRANK2_Lane6_MIN                       (0)
  #define DDRDATA8CH0_CR_TXPERBITRANK2_Lane6_MAX                       (15) // 0x0000000F
  #define DDRDATA8CH0_CR_TXPERBITRANK2_Lane6_DEF                       (0x00000000)
  #define DDRDATA8CH0_CR_TXPERBITRANK2_Lane6_HSH                       (0x04181038)

  #define DDRDATA8CH0_CR_TXPERBITRANK2_Lane7_OFF                       (28)
  #define DDRDATA8CH0_CR_TXPERBITRANK2_Lane7_WID                       ( 4)
  #define DDRDATA8CH0_CR_TXPERBITRANK2_Lane7_MSK                       (0xF0000000)
  #define DDRDATA8CH0_CR_TXPERBITRANK2_Lane7_MIN                       (0)
  #define DDRDATA8CH0_CR_TXPERBITRANK2_Lane7_MAX                       (15) // 0x0000000F
  #define DDRDATA8CH0_CR_TXPERBITRANK2_Lane7_DEF                       (0x00000000)
  #define DDRDATA8CH0_CR_TXPERBITRANK2_Lane7_HSH                       (0x041C1038)

#define DDRDATA8CH0_CR_TXPERBITRANK3_REG                               (0x0000103C)

  #define DDRDATA8CH0_CR_TXPERBITRANK3_Lane0_OFF                       ( 0)
  #define DDRDATA8CH0_CR_TXPERBITRANK3_Lane0_WID                       ( 4)
  #define DDRDATA8CH0_CR_TXPERBITRANK3_Lane0_MSK                       (0x0000000F)
  #define DDRDATA8CH0_CR_TXPERBITRANK3_Lane0_MIN                       (0)
  #define DDRDATA8CH0_CR_TXPERBITRANK3_Lane0_MAX                       (15) // 0x0000000F
  #define DDRDATA8CH0_CR_TXPERBITRANK3_Lane0_DEF                       (0x00000000)
  #define DDRDATA8CH0_CR_TXPERBITRANK3_Lane0_HSH                       (0x0400103C)

  #define DDRDATA8CH0_CR_TXPERBITRANK3_Lane1_OFF                       ( 4)
  #define DDRDATA8CH0_CR_TXPERBITRANK3_Lane1_WID                       ( 4)
  #define DDRDATA8CH0_CR_TXPERBITRANK3_Lane1_MSK                       (0x000000F0)
  #define DDRDATA8CH0_CR_TXPERBITRANK3_Lane1_MIN                       (0)
  #define DDRDATA8CH0_CR_TXPERBITRANK3_Lane1_MAX                       (15) // 0x0000000F
  #define DDRDATA8CH0_CR_TXPERBITRANK3_Lane1_DEF                       (0x00000000)
  #define DDRDATA8CH0_CR_TXPERBITRANK3_Lane1_HSH                       (0x0404103C)

  #define DDRDATA8CH0_CR_TXPERBITRANK3_Lane2_OFF                       ( 8)
  #define DDRDATA8CH0_CR_TXPERBITRANK3_Lane2_WID                       ( 4)
  #define DDRDATA8CH0_CR_TXPERBITRANK3_Lane2_MSK                       (0x00000F00)
  #define DDRDATA8CH0_CR_TXPERBITRANK3_Lane2_MIN                       (0)
  #define DDRDATA8CH0_CR_TXPERBITRANK3_Lane2_MAX                       (15) // 0x0000000F
  #define DDRDATA8CH0_CR_TXPERBITRANK3_Lane2_DEF                       (0x00000000)
  #define DDRDATA8CH0_CR_TXPERBITRANK3_Lane2_HSH                       (0x0408103C)

  #define DDRDATA8CH0_CR_TXPERBITRANK3_Lane3_OFF                       (12)
  #define DDRDATA8CH0_CR_TXPERBITRANK3_Lane3_WID                       ( 4)
  #define DDRDATA8CH0_CR_TXPERBITRANK3_Lane3_MSK                       (0x0000F000)
  #define DDRDATA8CH0_CR_TXPERBITRANK3_Lane3_MIN                       (0)
  #define DDRDATA8CH0_CR_TXPERBITRANK3_Lane3_MAX                       (15) // 0x0000000F
  #define DDRDATA8CH0_CR_TXPERBITRANK3_Lane3_DEF                       (0x00000000)
  #define DDRDATA8CH0_CR_TXPERBITRANK3_Lane3_HSH                       (0x040C103C)

  #define DDRDATA8CH0_CR_TXPERBITRANK3_Lane4_OFF                       (16)
  #define DDRDATA8CH0_CR_TXPERBITRANK3_Lane4_WID                       ( 4)
  #define DDRDATA8CH0_CR_TXPERBITRANK3_Lane4_MSK                       (0x000F0000)
  #define DDRDATA8CH0_CR_TXPERBITRANK3_Lane4_MIN                       (0)
  #define DDRDATA8CH0_CR_TXPERBITRANK3_Lane4_MAX                       (15) // 0x0000000F
  #define DDRDATA8CH0_CR_TXPERBITRANK3_Lane4_DEF                       (0x00000000)
  #define DDRDATA8CH0_CR_TXPERBITRANK3_Lane4_HSH                       (0x0410103C)

  #define DDRDATA8CH0_CR_TXPERBITRANK3_Lane5_OFF                       (20)
  #define DDRDATA8CH0_CR_TXPERBITRANK3_Lane5_WID                       ( 4)
  #define DDRDATA8CH0_CR_TXPERBITRANK3_Lane5_MSK                       (0x00F00000)
  #define DDRDATA8CH0_CR_TXPERBITRANK3_Lane5_MIN                       (0)
  #define DDRDATA8CH0_CR_TXPERBITRANK3_Lane5_MAX                       (15) // 0x0000000F
  #define DDRDATA8CH0_CR_TXPERBITRANK3_Lane5_DEF                       (0x00000000)
  #define DDRDATA8CH0_CR_TXPERBITRANK3_Lane5_HSH                       (0x0414103C)

  #define DDRDATA8CH0_CR_TXPERBITRANK3_Lane6_OFF                       (24)
  #define DDRDATA8CH0_CR_TXPERBITRANK3_Lane6_WID                       ( 4)
  #define DDRDATA8CH0_CR_TXPERBITRANK3_Lane6_MSK                       (0x0F000000)
  #define DDRDATA8CH0_CR_TXPERBITRANK3_Lane6_MIN                       (0)
  #define DDRDATA8CH0_CR_TXPERBITRANK3_Lane6_MAX                       (15) // 0x0000000F
  #define DDRDATA8CH0_CR_TXPERBITRANK3_Lane6_DEF                       (0x00000000)
  #define DDRDATA8CH0_CR_TXPERBITRANK3_Lane6_HSH                       (0x0418103C)

  #define DDRDATA8CH0_CR_TXPERBITRANK3_Lane7_OFF                       (28)
  #define DDRDATA8CH0_CR_TXPERBITRANK3_Lane7_WID                       ( 4)
  #define DDRDATA8CH0_CR_TXPERBITRANK3_Lane7_MSK                       (0xF0000000)
  #define DDRDATA8CH0_CR_TXPERBITRANK3_Lane7_MIN                       (0)
  #define DDRDATA8CH0_CR_TXPERBITRANK3_Lane7_MAX                       (15) // 0x0000000F
  #define DDRDATA8CH0_CR_TXPERBITRANK3_Lane7_DEF                       (0x00000000)
  #define DDRDATA8CH0_CR_TXPERBITRANK3_Lane7_HSH                       (0x041C103C)

#define DDRDATA8CH0_CR_RCOMPDATA0_REG                                  (0x00001040)

  #define DDRDATA8CH0_CR_RCOMPDATA0_RcompDrvUp_OFF                     ( 0)
  #define DDRDATA8CH0_CR_RCOMPDATA0_RcompDrvUp_WID                     ( 6)
  #define DDRDATA8CH0_CR_RCOMPDATA0_RcompDrvUp_MSK                     (0x0000003F)
  #define DDRDATA8CH0_CR_RCOMPDATA0_RcompDrvUp_MIN                     (0)
  #define DDRDATA8CH0_CR_RCOMPDATA0_RcompDrvUp_MAX                     (63) // 0x0000003F
  #define DDRDATA8CH0_CR_RCOMPDATA0_RcompDrvUp_DEF                     (0x00000000)
  #define DDRDATA8CH0_CR_RCOMPDATA0_RcompDrvUp_HSH                     (0x06001040)

  #define DDRDATA8CH0_CR_RCOMPDATA0_Rsvd_OFF                           ( 6)
  #define DDRDATA8CH0_CR_RCOMPDATA0_Rsvd_WID                           ( 3)
  #define DDRDATA8CH0_CR_RCOMPDATA0_Rsvd_MSK                           (0x000001C0)
  #define DDRDATA8CH0_CR_RCOMPDATA0_Rsvd_MIN                           (0)
  #define DDRDATA8CH0_CR_RCOMPDATA0_Rsvd_MAX                           (7) // 0x00000007
  #define DDRDATA8CH0_CR_RCOMPDATA0_Rsvd_DEF                           (0x00000000)
  #define DDRDATA8CH0_CR_RCOMPDATA0_Rsvd_HSH                           (0x03061040)

  #define DDRDATA8CH0_CR_RCOMPDATA0_RcompDrvDown_OFF                   ( 9)
  #define DDRDATA8CH0_CR_RCOMPDATA0_RcompDrvDown_WID                   ( 6)
  #define DDRDATA8CH0_CR_RCOMPDATA0_RcompDrvDown_MSK                   (0x00007E00)
  #define DDRDATA8CH0_CR_RCOMPDATA0_RcompDrvDown_MIN                   (0)
  #define DDRDATA8CH0_CR_RCOMPDATA0_RcompDrvDown_MAX                   (63) // 0x0000003F
  #define DDRDATA8CH0_CR_RCOMPDATA0_RcompDrvDown_DEF                   (0x00000000)
  #define DDRDATA8CH0_CR_RCOMPDATA0_RcompDrvDown_HSH                   (0x06091040)

  #define DDRDATA8CH0_CR_RCOMPDATA0_VTComp_OFF                         (15)
  #define DDRDATA8CH0_CR_RCOMPDATA0_VTComp_WID                         ( 5)
  #define DDRDATA8CH0_CR_RCOMPDATA0_VTComp_MSK                         (0x000F8000)
  #define DDRDATA8CH0_CR_RCOMPDATA0_VTComp_MIN                         (0)
  #define DDRDATA8CH0_CR_RCOMPDATA0_VTComp_MAX                         (31) // 0x0000001F
  #define DDRDATA8CH0_CR_RCOMPDATA0_VTComp_DEF                         (0x00000000)
  #define DDRDATA8CH0_CR_RCOMPDATA0_VTComp_HSH                         (0x050F1040)

  #define DDRDATA8CH0_CR_RCOMPDATA0_SlewRateComp_OFF                   (20)
  #define DDRDATA8CH0_CR_RCOMPDATA0_SlewRateComp_WID                   ( 5)
  #define DDRDATA8CH0_CR_RCOMPDATA0_SlewRateComp_MSK                   (0x01F00000)
  #define DDRDATA8CH0_CR_RCOMPDATA0_SlewRateComp_MIN                   (0)
  #define DDRDATA8CH0_CR_RCOMPDATA0_SlewRateComp_MAX                   (31) // 0x0000001F
  #define DDRDATA8CH0_CR_RCOMPDATA0_SlewRateComp_DEF                   (0x00000000)
  #define DDRDATA8CH0_CR_RCOMPDATA0_SlewRateComp_HSH                   (0x05141040)

  #define DDRDATA8CH0_CR_RCOMPDATA0_Spare0_OFF                         (25)
  #define DDRDATA8CH0_CR_RCOMPDATA0_Spare0_WID                         ( 1)
  #define DDRDATA8CH0_CR_RCOMPDATA0_Spare0_MSK                         (0x02000000)
  #define DDRDATA8CH0_CR_RCOMPDATA0_Spare0_MIN                         (0)
  #define DDRDATA8CH0_CR_RCOMPDATA0_Spare0_MAX                         (1) // 0x00000001
  #define DDRDATA8CH0_CR_RCOMPDATA0_Spare0_DEF                         (0x00000000)
  #define DDRDATA8CH0_CR_RCOMPDATA0_Spare0_HSH                         (0x01191040)

  #define DDRDATA8CH0_CR_RCOMPDATA0_TcoComp_OFF                        (26)
  #define DDRDATA8CH0_CR_RCOMPDATA0_TcoComp_WID                        ( 6)
  #define DDRDATA8CH0_CR_RCOMPDATA0_TcoComp_MSK                        (0xFC000000)
  #define DDRDATA8CH0_CR_RCOMPDATA0_TcoComp_MIN                        (0)
  #define DDRDATA8CH0_CR_RCOMPDATA0_TcoComp_MAX                        (63) // 0x0000003F
  #define DDRDATA8CH0_CR_RCOMPDATA0_TcoComp_DEF                        (0x00000000)
  #define DDRDATA8CH0_CR_RCOMPDATA0_TcoComp_HSH                        (0x061A1040)

#define DDRDATA8CH0_CR_RCOMPDATA1_REG                                  (0x00001044)

  #define DDRDATA8CH0_CR_RCOMPDATA1_RcompOdtUp_OFF                     ( 0)
  #define DDRDATA8CH0_CR_RCOMPDATA1_RcompOdtUp_WID                     ( 6)
  #define DDRDATA8CH0_CR_RCOMPDATA1_RcompOdtUp_MSK                     (0x0000003F)
  #define DDRDATA8CH0_CR_RCOMPDATA1_RcompOdtUp_MIN                     (0)
  #define DDRDATA8CH0_CR_RCOMPDATA1_RcompOdtUp_MAX                     (63) // 0x0000003F
  #define DDRDATA8CH0_CR_RCOMPDATA1_RcompOdtUp_DEF                     (0x00000000)
  #define DDRDATA8CH0_CR_RCOMPDATA1_RcompOdtUp_HSH                     (0x06001044)

  #define DDRDATA8CH0_CR_RCOMPDATA1_PanicDrvDn_OFF                     ( 6)
  #define DDRDATA8CH0_CR_RCOMPDATA1_PanicDrvDn_WID                     (10)
  #define DDRDATA8CH0_CR_RCOMPDATA1_PanicDrvDn_MSK                     (0x0000FFC0)
  #define DDRDATA8CH0_CR_RCOMPDATA1_PanicDrvDn_MIN                     (0)
  #define DDRDATA8CH0_CR_RCOMPDATA1_PanicDrvDn_MAX                     (1023) // 0x000003FF
  #define DDRDATA8CH0_CR_RCOMPDATA1_PanicDrvDn_DEF                     (0x00000000)
  #define DDRDATA8CH0_CR_RCOMPDATA1_PanicDrvDn_HSH                     (0x0A061044)

  #define DDRDATA8CH0_CR_RCOMPDATA1_PanicDrvUp_OFF                     (16)
  #define DDRDATA8CH0_CR_RCOMPDATA1_PanicDrvUp_WID                     (10)
  #define DDRDATA8CH0_CR_RCOMPDATA1_PanicDrvUp_MSK                     (0x03FF0000)
  #define DDRDATA8CH0_CR_RCOMPDATA1_PanicDrvUp_MIN                     (0)
  #define DDRDATA8CH0_CR_RCOMPDATA1_PanicDrvUp_MAX                     (1023) // 0x000003FF
  #define DDRDATA8CH0_CR_RCOMPDATA1_PanicDrvUp_DEF                     (0x00000000)
  #define DDRDATA8CH0_CR_RCOMPDATA1_PanicDrvUp_HSH                     (0x0A101044)

  #define DDRDATA8CH0_CR_RCOMPDATA1_RcompOdtDown_OFF                   (26)
  #define DDRDATA8CH0_CR_RCOMPDATA1_RcompOdtDown_WID                   ( 6)
  #define DDRDATA8CH0_CR_RCOMPDATA1_RcompOdtDown_MSK                   (0xFC000000)
  #define DDRDATA8CH0_CR_RCOMPDATA1_RcompOdtDown_MIN                   (0)
  #define DDRDATA8CH0_CR_RCOMPDATA1_RcompOdtDown_MAX                   (63) // 0x0000003F
  #define DDRDATA8CH0_CR_RCOMPDATA1_RcompOdtDown_DEF                   (0x00000000)
  #define DDRDATA8CH0_CR_RCOMPDATA1_RcompOdtDown_HSH                   (0x061A1044)

#define DDRDATA8CH0_CR_TXXTALK_REG                                     (0x00001048)

  #define DDRDATA8CH0_CR_TXXTALK_Lane0_OFF                             ( 0)
  #define DDRDATA8CH0_CR_TXXTALK_Lane0_WID                             ( 4)
  #define DDRDATA8CH0_CR_TXXTALK_Lane0_MSK                             (0x0000000F)
  #define DDRDATA8CH0_CR_TXXTALK_Lane0_MIN                             (-8)
  #define DDRDATA8CH0_CR_TXXTALK_Lane0_MAX                             (7) // 0x00000007
  #define DDRDATA8CH0_CR_TXXTALK_Lane0_DEF                             (0x00000000)
  #define DDRDATA8CH0_CR_TXXTALK_Lane0_HSH                             (0x84001048)

  #define DDRDATA8CH0_CR_TXXTALK_Lane1_OFF                             ( 4)
  #define DDRDATA8CH0_CR_TXXTALK_Lane1_WID                             ( 4)
  #define DDRDATA8CH0_CR_TXXTALK_Lane1_MSK                             (0x000000F0)
  #define DDRDATA8CH0_CR_TXXTALK_Lane1_MIN                             (-8)
  #define DDRDATA8CH0_CR_TXXTALK_Lane1_MAX                             (7) // 0x00000007
  #define DDRDATA8CH0_CR_TXXTALK_Lane1_DEF                             (0x00000000)
  #define DDRDATA8CH0_CR_TXXTALK_Lane1_HSH                             (0x84041048)

  #define DDRDATA8CH0_CR_TXXTALK_Lane2_OFF                             ( 8)
  #define DDRDATA8CH0_CR_TXXTALK_Lane2_WID                             ( 4)
  #define DDRDATA8CH0_CR_TXXTALK_Lane2_MSK                             (0x00000F00)
  #define DDRDATA8CH0_CR_TXXTALK_Lane2_MIN                             (-8)
  #define DDRDATA8CH0_CR_TXXTALK_Lane2_MAX                             (7) // 0x00000007
  #define DDRDATA8CH0_CR_TXXTALK_Lane2_DEF                             (0x00000000)
  #define DDRDATA8CH0_CR_TXXTALK_Lane2_HSH                             (0x84081048)

  #define DDRDATA8CH0_CR_TXXTALK_Lane3_OFF                             (12)
  #define DDRDATA8CH0_CR_TXXTALK_Lane3_WID                             ( 4)
  #define DDRDATA8CH0_CR_TXXTALK_Lane3_MSK                             (0x0000F000)
  #define DDRDATA8CH0_CR_TXXTALK_Lane3_MIN                             (-8)
  #define DDRDATA8CH0_CR_TXXTALK_Lane3_MAX                             (7) // 0x00000007
  #define DDRDATA8CH0_CR_TXXTALK_Lane3_DEF                             (0x00000000)
  #define DDRDATA8CH0_CR_TXXTALK_Lane3_HSH                             (0x840C1048)

  #define DDRDATA8CH0_CR_TXXTALK_Lane4_OFF                             (16)
  #define DDRDATA8CH0_CR_TXXTALK_Lane4_WID                             ( 4)
  #define DDRDATA8CH0_CR_TXXTALK_Lane4_MSK                             (0x000F0000)
  #define DDRDATA8CH0_CR_TXXTALK_Lane4_MIN                             (-8)
  #define DDRDATA8CH0_CR_TXXTALK_Lane4_MAX                             (7) // 0x00000007
  #define DDRDATA8CH0_CR_TXXTALK_Lane4_DEF                             (0x00000000)
  #define DDRDATA8CH0_CR_TXXTALK_Lane4_HSH                             (0x84101048)

  #define DDRDATA8CH0_CR_TXXTALK_Lane5_OFF                             (20)
  #define DDRDATA8CH0_CR_TXXTALK_Lane5_WID                             ( 4)
  #define DDRDATA8CH0_CR_TXXTALK_Lane5_MSK                             (0x00F00000)
  #define DDRDATA8CH0_CR_TXXTALK_Lane5_MIN                             (-8)
  #define DDRDATA8CH0_CR_TXXTALK_Lane5_MAX                             (7) // 0x00000007
  #define DDRDATA8CH0_CR_TXXTALK_Lane5_DEF                             (0x00000000)
  #define DDRDATA8CH0_CR_TXXTALK_Lane5_HSH                             (0x84141048)

  #define DDRDATA8CH0_CR_TXXTALK_Lane6_OFF                             (24)
  #define DDRDATA8CH0_CR_TXXTALK_Lane6_WID                             ( 4)
  #define DDRDATA8CH0_CR_TXXTALK_Lane6_MSK                             (0x0F000000)
  #define DDRDATA8CH0_CR_TXXTALK_Lane6_MIN                             (-8)
  #define DDRDATA8CH0_CR_TXXTALK_Lane6_MAX                             (7) // 0x00000007
  #define DDRDATA8CH0_CR_TXXTALK_Lane6_DEF                             (0x00000000)
  #define DDRDATA8CH0_CR_TXXTALK_Lane6_HSH                             (0x84181048)

  #define DDRDATA8CH0_CR_TXXTALK_Lane7_OFF                             (28)
  #define DDRDATA8CH0_CR_TXXTALK_Lane7_WID                             ( 4)
  #define DDRDATA8CH0_CR_TXXTALK_Lane7_MSK                             (0xF0000000)
  #define DDRDATA8CH0_CR_TXXTALK_Lane7_MIN                             (-8)
  #define DDRDATA8CH0_CR_TXXTALK_Lane7_MAX                             (7) // 0x00000007
  #define DDRDATA8CH0_CR_TXXTALK_Lane7_DEF                             (0x00000000)
  #define DDRDATA8CH0_CR_TXXTALK_Lane7_HSH                             (0x841C1048)

#define DDRDATA8CH0_CR_RCOMPDATA2_REG                                  (0x0000104C)

  #define DDRDATA8CH0_CR_RCOMPDATA2_VttPanicUp_OFF                     ( 0)
  #define DDRDATA8CH0_CR_RCOMPDATA2_VttPanicUp_WID                     ( 8)
  #define DDRDATA8CH0_CR_RCOMPDATA2_VttPanicUp_MSK                     (0x000000FF)
  #define DDRDATA8CH0_CR_RCOMPDATA2_VttPanicUp_MIN                     (0)
  #define DDRDATA8CH0_CR_RCOMPDATA2_VttPanicUp_MAX                     (255) // 0x000000FF
  #define DDRDATA8CH0_CR_RCOMPDATA2_VttPanicUp_DEF                     (0x00000000)
  #define DDRDATA8CH0_CR_RCOMPDATA2_VttPanicUp_HSH                     (0x0800104C)

  #define DDRDATA8CH0_CR_RCOMPDATA2_VttPanicDn_OFF                     ( 8)
  #define DDRDATA8CH0_CR_RCOMPDATA2_VttPanicDn_WID                     ( 8)
  #define DDRDATA8CH0_CR_RCOMPDATA2_VttPanicDn_MSK                     (0x0000FF00)
  #define DDRDATA8CH0_CR_RCOMPDATA2_VttPanicDn_MIN                     (0)
  #define DDRDATA8CH0_CR_RCOMPDATA2_VttPanicDn_MAX                     (255) // 0x000000FF
  #define DDRDATA8CH0_CR_RCOMPDATA2_VttPanicDn_DEF                     (0x00000000)
  #define DDRDATA8CH0_CR_RCOMPDATA2_VttPanicDn_HSH                     (0x0808104C)

  #define DDRDATA8CH0_CR_RCOMPDATA2_Spare_OFF                          (16)
  #define DDRDATA8CH0_CR_RCOMPDATA2_Spare_WID                          (16)
  #define DDRDATA8CH0_CR_RCOMPDATA2_Spare_MSK                          (0xFFFF0000)
  #define DDRDATA8CH0_CR_RCOMPDATA2_Spare_MIN                          (0)
  #define DDRDATA8CH0_CR_RCOMPDATA2_Spare_MAX                          (65535) // 0x0000FFFF
  #define DDRDATA8CH0_CR_RCOMPDATA2_Spare_DEF                          (0x00000000)
  #define DDRDATA8CH0_CR_RCOMPDATA2_Spare_HSH                          (0x1010104C)

#define DDRDATA8CH0_CR_RXOFFSETVDQRANK0_REG                            (0x00001050)

  #define DDRDATA8CH0_CR_RXOFFSETVDQRANK0_Lane0_OFF                    ( 0)
  #define DDRDATA8CH0_CR_RXOFFSETVDQRANK0_Lane0_WID                    ( 4)
  #define DDRDATA8CH0_CR_RXOFFSETVDQRANK0_Lane0_MSK                    (0x0000000F)
  #define DDRDATA8CH0_CR_RXOFFSETVDQRANK0_Lane0_MIN                    (0)
  #define DDRDATA8CH0_CR_RXOFFSETVDQRANK0_Lane0_MAX                    (15) // 0x0000000F
  #define DDRDATA8CH0_CR_RXOFFSETVDQRANK0_Lane0_DEF                    (0x00000000)
  #define DDRDATA8CH0_CR_RXOFFSETVDQRANK0_Lane0_HSH                    (0x04001050)

  #define DDRDATA8CH0_CR_RXOFFSETVDQRANK0_Lane1_OFF                    ( 4)
  #define DDRDATA8CH0_CR_RXOFFSETVDQRANK0_Lane1_WID                    ( 4)
  #define DDRDATA8CH0_CR_RXOFFSETVDQRANK0_Lane1_MSK                    (0x000000F0)
  #define DDRDATA8CH0_CR_RXOFFSETVDQRANK0_Lane1_MIN                    (0)
  #define DDRDATA8CH0_CR_RXOFFSETVDQRANK0_Lane1_MAX                    (15) // 0x0000000F
  #define DDRDATA8CH0_CR_RXOFFSETVDQRANK0_Lane1_DEF                    (0x00000000)
  #define DDRDATA8CH0_CR_RXOFFSETVDQRANK0_Lane1_HSH                    (0x04041050)

  #define DDRDATA8CH0_CR_RXOFFSETVDQRANK0_Lane2_OFF                    ( 8)
  #define DDRDATA8CH0_CR_RXOFFSETVDQRANK0_Lane2_WID                    ( 4)
  #define DDRDATA8CH0_CR_RXOFFSETVDQRANK0_Lane2_MSK                    (0x00000F00)
  #define DDRDATA8CH0_CR_RXOFFSETVDQRANK0_Lane2_MIN                    (0)
  #define DDRDATA8CH0_CR_RXOFFSETVDQRANK0_Lane2_MAX                    (15) // 0x0000000F
  #define DDRDATA8CH0_CR_RXOFFSETVDQRANK0_Lane2_DEF                    (0x00000000)
  #define DDRDATA8CH0_CR_RXOFFSETVDQRANK0_Lane2_HSH                    (0x04081050)

  #define DDRDATA8CH0_CR_RXOFFSETVDQRANK0_Lane3_OFF                    (12)
  #define DDRDATA8CH0_CR_RXOFFSETVDQRANK0_Lane3_WID                    ( 4)
  #define DDRDATA8CH0_CR_RXOFFSETVDQRANK0_Lane3_MSK                    (0x0000F000)
  #define DDRDATA8CH0_CR_RXOFFSETVDQRANK0_Lane3_MIN                    (0)
  #define DDRDATA8CH0_CR_RXOFFSETVDQRANK0_Lane3_MAX                    (15) // 0x0000000F
  #define DDRDATA8CH0_CR_RXOFFSETVDQRANK0_Lane3_DEF                    (0x00000000)
  #define DDRDATA8CH0_CR_RXOFFSETVDQRANK0_Lane3_HSH                    (0x040C1050)

  #define DDRDATA8CH0_CR_RXOFFSETVDQRANK0_Lane4_OFF                    (16)
  #define DDRDATA8CH0_CR_RXOFFSETVDQRANK0_Lane4_WID                    ( 4)
  #define DDRDATA8CH0_CR_RXOFFSETVDQRANK0_Lane4_MSK                    (0x000F0000)
  #define DDRDATA8CH0_CR_RXOFFSETVDQRANK0_Lane4_MIN                    (0)
  #define DDRDATA8CH0_CR_RXOFFSETVDQRANK0_Lane4_MAX                    (15) // 0x0000000F
  #define DDRDATA8CH0_CR_RXOFFSETVDQRANK0_Lane4_DEF                    (0x00000000)
  #define DDRDATA8CH0_CR_RXOFFSETVDQRANK0_Lane4_HSH                    (0x04101050)

  #define DDRDATA8CH0_CR_RXOFFSETVDQRANK0_Lane5_OFF                    (20)
  #define DDRDATA8CH0_CR_RXOFFSETVDQRANK0_Lane5_WID                    ( 4)
  #define DDRDATA8CH0_CR_RXOFFSETVDQRANK0_Lane5_MSK                    (0x00F00000)
  #define DDRDATA8CH0_CR_RXOFFSETVDQRANK0_Lane5_MIN                    (0)
  #define DDRDATA8CH0_CR_RXOFFSETVDQRANK0_Lane5_MAX                    (15) // 0x0000000F
  #define DDRDATA8CH0_CR_RXOFFSETVDQRANK0_Lane5_DEF                    (0x00000000)
  #define DDRDATA8CH0_CR_RXOFFSETVDQRANK0_Lane5_HSH                    (0x04141050)

  #define DDRDATA8CH0_CR_RXOFFSETVDQRANK0_Lane6_OFF                    (24)
  #define DDRDATA8CH0_CR_RXOFFSETVDQRANK0_Lane6_WID                    ( 4)
  #define DDRDATA8CH0_CR_RXOFFSETVDQRANK0_Lane6_MSK                    (0x0F000000)
  #define DDRDATA8CH0_CR_RXOFFSETVDQRANK0_Lane6_MIN                    (0)
  #define DDRDATA8CH0_CR_RXOFFSETVDQRANK0_Lane6_MAX                    (15) // 0x0000000F
  #define DDRDATA8CH0_CR_RXOFFSETVDQRANK0_Lane6_DEF                    (0x00000000)
  #define DDRDATA8CH0_CR_RXOFFSETVDQRANK0_Lane6_HSH                    (0x04181050)

  #define DDRDATA8CH0_CR_RXOFFSETVDQRANK0_Lane7_OFF                    (28)
  #define DDRDATA8CH0_CR_RXOFFSETVDQRANK0_Lane7_WID                    ( 4)
  #define DDRDATA8CH0_CR_RXOFFSETVDQRANK0_Lane7_MSK                    (0xF0000000)
  #define DDRDATA8CH0_CR_RXOFFSETVDQRANK0_Lane7_MIN                    (0)
  #define DDRDATA8CH0_CR_RXOFFSETVDQRANK0_Lane7_MAX                    (15) // 0x0000000F
  #define DDRDATA8CH0_CR_RXOFFSETVDQRANK0_Lane7_DEF                    (0x00000000)
  #define DDRDATA8CH0_CR_RXOFFSETVDQRANK0_Lane7_HSH                    (0x041C1050)

#define DDRDATA8CH0_CR_RXOFFSETVDQRANK1_REG                            (0x00001054)

  #define DDRDATA8CH0_CR_RXOFFSETVDQRANK1_Lane0_OFF                    ( 0)
  #define DDRDATA8CH0_CR_RXOFFSETVDQRANK1_Lane0_WID                    ( 4)
  #define DDRDATA8CH0_CR_RXOFFSETVDQRANK1_Lane0_MSK                    (0x0000000F)
  #define DDRDATA8CH0_CR_RXOFFSETVDQRANK1_Lane0_MIN                    (0)
  #define DDRDATA8CH0_CR_RXOFFSETVDQRANK1_Lane0_MAX                    (15) // 0x0000000F
  #define DDRDATA8CH0_CR_RXOFFSETVDQRANK1_Lane0_DEF                    (0x00000000)
  #define DDRDATA8CH0_CR_RXOFFSETVDQRANK1_Lane0_HSH                    (0x04001054)

  #define DDRDATA8CH0_CR_RXOFFSETVDQRANK1_Lane1_OFF                    ( 4)
  #define DDRDATA8CH0_CR_RXOFFSETVDQRANK1_Lane1_WID                    ( 4)
  #define DDRDATA8CH0_CR_RXOFFSETVDQRANK1_Lane1_MSK                    (0x000000F0)
  #define DDRDATA8CH0_CR_RXOFFSETVDQRANK1_Lane1_MIN                    (0)
  #define DDRDATA8CH0_CR_RXOFFSETVDQRANK1_Lane1_MAX                    (15) // 0x0000000F
  #define DDRDATA8CH0_CR_RXOFFSETVDQRANK1_Lane1_DEF                    (0x00000000)
  #define DDRDATA8CH0_CR_RXOFFSETVDQRANK1_Lane1_HSH                    (0x04041054)

  #define DDRDATA8CH0_CR_RXOFFSETVDQRANK1_Lane2_OFF                    ( 8)
  #define DDRDATA8CH0_CR_RXOFFSETVDQRANK1_Lane2_WID                    ( 4)
  #define DDRDATA8CH0_CR_RXOFFSETVDQRANK1_Lane2_MSK                    (0x00000F00)
  #define DDRDATA8CH0_CR_RXOFFSETVDQRANK1_Lane2_MIN                    (0)
  #define DDRDATA8CH0_CR_RXOFFSETVDQRANK1_Lane2_MAX                    (15) // 0x0000000F
  #define DDRDATA8CH0_CR_RXOFFSETVDQRANK1_Lane2_DEF                    (0x00000000)
  #define DDRDATA8CH0_CR_RXOFFSETVDQRANK1_Lane2_HSH                    (0x04081054)

  #define DDRDATA8CH0_CR_RXOFFSETVDQRANK1_Lane3_OFF                    (12)
  #define DDRDATA8CH0_CR_RXOFFSETVDQRANK1_Lane3_WID                    ( 4)
  #define DDRDATA8CH0_CR_RXOFFSETVDQRANK1_Lane3_MSK                    (0x0000F000)
  #define DDRDATA8CH0_CR_RXOFFSETVDQRANK1_Lane3_MIN                    (0)
  #define DDRDATA8CH0_CR_RXOFFSETVDQRANK1_Lane3_MAX                    (15) // 0x0000000F
  #define DDRDATA8CH0_CR_RXOFFSETVDQRANK1_Lane3_DEF                    (0x00000000)
  #define DDRDATA8CH0_CR_RXOFFSETVDQRANK1_Lane3_HSH                    (0x040C1054)

  #define DDRDATA8CH0_CR_RXOFFSETVDQRANK1_Lane4_OFF                    (16)
  #define DDRDATA8CH0_CR_RXOFFSETVDQRANK1_Lane4_WID                    ( 4)
  #define DDRDATA8CH0_CR_RXOFFSETVDQRANK1_Lane4_MSK                    (0x000F0000)
  #define DDRDATA8CH0_CR_RXOFFSETVDQRANK1_Lane4_MIN                    (0)
  #define DDRDATA8CH0_CR_RXOFFSETVDQRANK1_Lane4_MAX                    (15) // 0x0000000F
  #define DDRDATA8CH0_CR_RXOFFSETVDQRANK1_Lane4_DEF                    (0x00000000)
  #define DDRDATA8CH0_CR_RXOFFSETVDQRANK1_Lane4_HSH                    (0x04101054)

  #define DDRDATA8CH0_CR_RXOFFSETVDQRANK1_Lane5_OFF                    (20)
  #define DDRDATA8CH0_CR_RXOFFSETVDQRANK1_Lane5_WID                    ( 4)
  #define DDRDATA8CH0_CR_RXOFFSETVDQRANK1_Lane5_MSK                    (0x00F00000)
  #define DDRDATA8CH0_CR_RXOFFSETVDQRANK1_Lane5_MIN                    (0)
  #define DDRDATA8CH0_CR_RXOFFSETVDQRANK1_Lane5_MAX                    (15) // 0x0000000F
  #define DDRDATA8CH0_CR_RXOFFSETVDQRANK1_Lane5_DEF                    (0x00000000)
  #define DDRDATA8CH0_CR_RXOFFSETVDQRANK1_Lane5_HSH                    (0x04141054)

  #define DDRDATA8CH0_CR_RXOFFSETVDQRANK1_Lane6_OFF                    (24)
  #define DDRDATA8CH0_CR_RXOFFSETVDQRANK1_Lane6_WID                    ( 4)
  #define DDRDATA8CH0_CR_RXOFFSETVDQRANK1_Lane6_MSK                    (0x0F000000)
  #define DDRDATA8CH0_CR_RXOFFSETVDQRANK1_Lane6_MIN                    (0)
  #define DDRDATA8CH0_CR_RXOFFSETVDQRANK1_Lane6_MAX                    (15) // 0x0000000F
  #define DDRDATA8CH0_CR_RXOFFSETVDQRANK1_Lane6_DEF                    (0x00000000)
  #define DDRDATA8CH0_CR_RXOFFSETVDQRANK1_Lane6_HSH                    (0x04181054)

  #define DDRDATA8CH0_CR_RXOFFSETVDQRANK1_Lane7_OFF                    (28)
  #define DDRDATA8CH0_CR_RXOFFSETVDQRANK1_Lane7_WID                    ( 4)
  #define DDRDATA8CH0_CR_RXOFFSETVDQRANK1_Lane7_MSK                    (0xF0000000)
  #define DDRDATA8CH0_CR_RXOFFSETVDQRANK1_Lane7_MIN                    (0)
  #define DDRDATA8CH0_CR_RXOFFSETVDQRANK1_Lane7_MAX                    (15) // 0x0000000F
  #define DDRDATA8CH0_CR_RXOFFSETVDQRANK1_Lane7_DEF                    (0x00000000)
  #define DDRDATA8CH0_CR_RXOFFSETVDQRANK1_Lane7_HSH                    (0x041C1054)

#define DDRDATA8CH0_CR_RXOFFSETVDQRANK2_REG                            (0x00001058)

  #define DDRDATA8CH0_CR_RXOFFSETVDQRANK2_Lane0_OFF                    ( 0)
  #define DDRDATA8CH0_CR_RXOFFSETVDQRANK2_Lane0_WID                    ( 4)
  #define DDRDATA8CH0_CR_RXOFFSETVDQRANK2_Lane0_MSK                    (0x0000000F)
  #define DDRDATA8CH0_CR_RXOFFSETVDQRANK2_Lane0_MIN                    (0)
  #define DDRDATA8CH0_CR_RXOFFSETVDQRANK2_Lane0_MAX                    (15) // 0x0000000F
  #define DDRDATA8CH0_CR_RXOFFSETVDQRANK2_Lane0_DEF                    (0x00000000)
  #define DDRDATA8CH0_CR_RXOFFSETVDQRANK2_Lane0_HSH                    (0x04001058)

  #define DDRDATA8CH0_CR_RXOFFSETVDQRANK2_Lane1_OFF                    ( 4)
  #define DDRDATA8CH0_CR_RXOFFSETVDQRANK2_Lane1_WID                    ( 4)
  #define DDRDATA8CH0_CR_RXOFFSETVDQRANK2_Lane1_MSK                    (0x000000F0)
  #define DDRDATA8CH0_CR_RXOFFSETVDQRANK2_Lane1_MIN                    (0)
  #define DDRDATA8CH0_CR_RXOFFSETVDQRANK2_Lane1_MAX                    (15) // 0x0000000F
  #define DDRDATA8CH0_CR_RXOFFSETVDQRANK2_Lane1_DEF                    (0x00000000)
  #define DDRDATA8CH0_CR_RXOFFSETVDQRANK2_Lane1_HSH                    (0x04041058)

  #define DDRDATA8CH0_CR_RXOFFSETVDQRANK2_Lane2_OFF                    ( 8)
  #define DDRDATA8CH0_CR_RXOFFSETVDQRANK2_Lane2_WID                    ( 4)
  #define DDRDATA8CH0_CR_RXOFFSETVDQRANK2_Lane2_MSK                    (0x00000F00)
  #define DDRDATA8CH0_CR_RXOFFSETVDQRANK2_Lane2_MIN                    (0)
  #define DDRDATA8CH0_CR_RXOFFSETVDQRANK2_Lane2_MAX                    (15) // 0x0000000F
  #define DDRDATA8CH0_CR_RXOFFSETVDQRANK2_Lane2_DEF                    (0x00000000)
  #define DDRDATA8CH0_CR_RXOFFSETVDQRANK2_Lane2_HSH                    (0x04081058)

  #define DDRDATA8CH0_CR_RXOFFSETVDQRANK2_Lane3_OFF                    (12)
  #define DDRDATA8CH0_CR_RXOFFSETVDQRANK2_Lane3_WID                    ( 4)
  #define DDRDATA8CH0_CR_RXOFFSETVDQRANK2_Lane3_MSK                    (0x0000F000)
  #define DDRDATA8CH0_CR_RXOFFSETVDQRANK2_Lane3_MIN                    (0)
  #define DDRDATA8CH0_CR_RXOFFSETVDQRANK2_Lane3_MAX                    (15) // 0x0000000F
  #define DDRDATA8CH0_CR_RXOFFSETVDQRANK2_Lane3_DEF                    (0x00000000)
  #define DDRDATA8CH0_CR_RXOFFSETVDQRANK2_Lane3_HSH                    (0x040C1058)

  #define DDRDATA8CH0_CR_RXOFFSETVDQRANK2_Lane4_OFF                    (16)
  #define DDRDATA8CH0_CR_RXOFFSETVDQRANK2_Lane4_WID                    ( 4)
  #define DDRDATA8CH0_CR_RXOFFSETVDQRANK2_Lane4_MSK                    (0x000F0000)
  #define DDRDATA8CH0_CR_RXOFFSETVDQRANK2_Lane4_MIN                    (0)
  #define DDRDATA8CH0_CR_RXOFFSETVDQRANK2_Lane4_MAX                    (15) // 0x0000000F
  #define DDRDATA8CH0_CR_RXOFFSETVDQRANK2_Lane4_DEF                    (0x00000000)
  #define DDRDATA8CH0_CR_RXOFFSETVDQRANK2_Lane4_HSH                    (0x04101058)

  #define DDRDATA8CH0_CR_RXOFFSETVDQRANK2_Lane5_OFF                    (20)
  #define DDRDATA8CH0_CR_RXOFFSETVDQRANK2_Lane5_WID                    ( 4)
  #define DDRDATA8CH0_CR_RXOFFSETVDQRANK2_Lane5_MSK                    (0x00F00000)
  #define DDRDATA8CH0_CR_RXOFFSETVDQRANK2_Lane5_MIN                    (0)
  #define DDRDATA8CH0_CR_RXOFFSETVDQRANK2_Lane5_MAX                    (15) // 0x0000000F
  #define DDRDATA8CH0_CR_RXOFFSETVDQRANK2_Lane5_DEF                    (0x00000000)
  #define DDRDATA8CH0_CR_RXOFFSETVDQRANK2_Lane5_HSH                    (0x04141058)

  #define DDRDATA8CH0_CR_RXOFFSETVDQRANK2_Lane6_OFF                    (24)
  #define DDRDATA8CH0_CR_RXOFFSETVDQRANK2_Lane6_WID                    ( 4)
  #define DDRDATA8CH0_CR_RXOFFSETVDQRANK2_Lane6_MSK                    (0x0F000000)
  #define DDRDATA8CH0_CR_RXOFFSETVDQRANK2_Lane6_MIN                    (0)
  #define DDRDATA8CH0_CR_RXOFFSETVDQRANK2_Lane6_MAX                    (15) // 0x0000000F
  #define DDRDATA8CH0_CR_RXOFFSETVDQRANK2_Lane6_DEF                    (0x00000000)
  #define DDRDATA8CH0_CR_RXOFFSETVDQRANK2_Lane6_HSH                    (0x04181058)

  #define DDRDATA8CH0_CR_RXOFFSETVDQRANK2_Lane7_OFF                    (28)
  #define DDRDATA8CH0_CR_RXOFFSETVDQRANK2_Lane7_WID                    ( 4)
  #define DDRDATA8CH0_CR_RXOFFSETVDQRANK2_Lane7_MSK                    (0xF0000000)
  #define DDRDATA8CH0_CR_RXOFFSETVDQRANK2_Lane7_MIN                    (0)
  #define DDRDATA8CH0_CR_RXOFFSETVDQRANK2_Lane7_MAX                    (15) // 0x0000000F
  #define DDRDATA8CH0_CR_RXOFFSETVDQRANK2_Lane7_DEF                    (0x00000000)
  #define DDRDATA8CH0_CR_RXOFFSETVDQRANK2_Lane7_HSH                    (0x041C1058)

#define DDRDATA8CH0_CR_RXOFFSETVDQRANK3_REG                            (0x0000105C)

  #define DDRDATA8CH0_CR_RXOFFSETVDQRANK3_Lane0_OFF                    ( 0)
  #define DDRDATA8CH0_CR_RXOFFSETVDQRANK3_Lane0_WID                    ( 4)
  #define DDRDATA8CH0_CR_RXOFFSETVDQRANK3_Lane0_MSK                    (0x0000000F)
  #define DDRDATA8CH0_CR_RXOFFSETVDQRANK3_Lane0_MIN                    (0)
  #define DDRDATA8CH0_CR_RXOFFSETVDQRANK3_Lane0_MAX                    (15) // 0x0000000F
  #define DDRDATA8CH0_CR_RXOFFSETVDQRANK3_Lane0_DEF                    (0x00000000)
  #define DDRDATA8CH0_CR_RXOFFSETVDQRANK3_Lane0_HSH                    (0x0400105C)

  #define DDRDATA8CH0_CR_RXOFFSETVDQRANK3_Lane1_OFF                    ( 4)
  #define DDRDATA8CH0_CR_RXOFFSETVDQRANK3_Lane1_WID                    ( 4)
  #define DDRDATA8CH0_CR_RXOFFSETVDQRANK3_Lane1_MSK                    (0x000000F0)
  #define DDRDATA8CH0_CR_RXOFFSETVDQRANK3_Lane1_MIN                    (0)
  #define DDRDATA8CH0_CR_RXOFFSETVDQRANK3_Lane1_MAX                    (15) // 0x0000000F
  #define DDRDATA8CH0_CR_RXOFFSETVDQRANK3_Lane1_DEF                    (0x00000000)
  #define DDRDATA8CH0_CR_RXOFFSETVDQRANK3_Lane1_HSH                    (0x0404105C)

  #define DDRDATA8CH0_CR_RXOFFSETVDQRANK3_Lane2_OFF                    ( 8)
  #define DDRDATA8CH0_CR_RXOFFSETVDQRANK3_Lane2_WID                    ( 4)
  #define DDRDATA8CH0_CR_RXOFFSETVDQRANK3_Lane2_MSK                    (0x00000F00)
  #define DDRDATA8CH0_CR_RXOFFSETVDQRANK3_Lane2_MIN                    (0)
  #define DDRDATA8CH0_CR_RXOFFSETVDQRANK3_Lane2_MAX                    (15) // 0x0000000F
  #define DDRDATA8CH0_CR_RXOFFSETVDQRANK3_Lane2_DEF                    (0x00000000)
  #define DDRDATA8CH0_CR_RXOFFSETVDQRANK3_Lane2_HSH                    (0x0408105C)

  #define DDRDATA8CH0_CR_RXOFFSETVDQRANK3_Lane3_OFF                    (12)
  #define DDRDATA8CH0_CR_RXOFFSETVDQRANK3_Lane3_WID                    ( 4)
  #define DDRDATA8CH0_CR_RXOFFSETVDQRANK3_Lane3_MSK                    (0x0000F000)
  #define DDRDATA8CH0_CR_RXOFFSETVDQRANK3_Lane3_MIN                    (0)
  #define DDRDATA8CH0_CR_RXOFFSETVDQRANK3_Lane3_MAX                    (15) // 0x0000000F
  #define DDRDATA8CH0_CR_RXOFFSETVDQRANK3_Lane3_DEF                    (0x00000000)
  #define DDRDATA8CH0_CR_RXOFFSETVDQRANK3_Lane3_HSH                    (0x040C105C)

  #define DDRDATA8CH0_CR_RXOFFSETVDQRANK3_Lane4_OFF                    (16)
  #define DDRDATA8CH0_CR_RXOFFSETVDQRANK3_Lane4_WID                    ( 4)
  #define DDRDATA8CH0_CR_RXOFFSETVDQRANK3_Lane4_MSK                    (0x000F0000)
  #define DDRDATA8CH0_CR_RXOFFSETVDQRANK3_Lane4_MIN                    (0)
  #define DDRDATA8CH0_CR_RXOFFSETVDQRANK3_Lane4_MAX                    (15) // 0x0000000F
  #define DDRDATA8CH0_CR_RXOFFSETVDQRANK3_Lane4_DEF                    (0x00000000)
  #define DDRDATA8CH0_CR_RXOFFSETVDQRANK3_Lane4_HSH                    (0x0410105C)

  #define DDRDATA8CH0_CR_RXOFFSETVDQRANK3_Lane5_OFF                    (20)
  #define DDRDATA8CH0_CR_RXOFFSETVDQRANK3_Lane5_WID                    ( 4)
  #define DDRDATA8CH0_CR_RXOFFSETVDQRANK3_Lane5_MSK                    (0x00F00000)
  #define DDRDATA8CH0_CR_RXOFFSETVDQRANK3_Lane5_MIN                    (0)
  #define DDRDATA8CH0_CR_RXOFFSETVDQRANK3_Lane5_MAX                    (15) // 0x0000000F
  #define DDRDATA8CH0_CR_RXOFFSETVDQRANK3_Lane5_DEF                    (0x00000000)
  #define DDRDATA8CH0_CR_RXOFFSETVDQRANK3_Lane5_HSH                    (0x0414105C)

  #define DDRDATA8CH0_CR_RXOFFSETVDQRANK3_Lane6_OFF                    (24)
  #define DDRDATA8CH0_CR_RXOFFSETVDQRANK3_Lane6_WID                    ( 4)
  #define DDRDATA8CH0_CR_RXOFFSETVDQRANK3_Lane6_MSK                    (0x0F000000)
  #define DDRDATA8CH0_CR_RXOFFSETVDQRANK3_Lane6_MIN                    (0)
  #define DDRDATA8CH0_CR_RXOFFSETVDQRANK3_Lane6_MAX                    (15) // 0x0000000F
  #define DDRDATA8CH0_CR_RXOFFSETVDQRANK3_Lane6_DEF                    (0x00000000)
  #define DDRDATA8CH0_CR_RXOFFSETVDQRANK3_Lane6_HSH                    (0x0418105C)

  #define DDRDATA8CH0_CR_RXOFFSETVDQRANK3_Lane7_OFF                    (28)
  #define DDRDATA8CH0_CR_RXOFFSETVDQRANK3_Lane7_WID                    ( 4)
  #define DDRDATA8CH0_CR_RXOFFSETVDQRANK3_Lane7_MSK                    (0xF0000000)
  #define DDRDATA8CH0_CR_RXOFFSETVDQRANK3_Lane7_MIN                    (0)
  #define DDRDATA8CH0_CR_RXOFFSETVDQRANK3_Lane7_MAX                    (15) // 0x0000000F
  #define DDRDATA8CH0_CR_RXOFFSETVDQRANK3_Lane7_DEF                    (0x00000000)
  #define DDRDATA8CH0_CR_RXOFFSETVDQRANK3_Lane7_HSH                    (0x041C105C)

#define DDRDATA8CH0_CR_DATATRAINFEEDBACK_REG                           (0x00001060)

  #define DDRDATA8CH0_CR_DATATRAINFEEDBACK_DataTrainFeedback_OFF       ( 0)
  #define DDRDATA8CH0_CR_DATATRAINFEEDBACK_DataTrainFeedback_WID       ( 9)
  #define DDRDATA8CH0_CR_DATATRAINFEEDBACK_DataTrainFeedback_MSK       (0x000001FF)
  #define DDRDATA8CH0_CR_DATATRAINFEEDBACK_DataTrainFeedback_MIN       (0)
  #define DDRDATA8CH0_CR_DATATRAINFEEDBACK_DataTrainFeedback_MAX       (511) // 0x000001FF
  #define DDRDATA8CH0_CR_DATATRAINFEEDBACK_DataTrainFeedback_DEF       (0x00000000)
  #define DDRDATA8CH0_CR_DATATRAINFEEDBACK_DataTrainFeedback_HSH       (0x09001060)

  #define DDRDATA8CH0_CR_DATATRAINFEEDBACK_Spare_OFF                   ( 9)
  #define DDRDATA8CH0_CR_DATATRAINFEEDBACK_Spare_WID                   (23)
  #define DDRDATA8CH0_CR_DATATRAINFEEDBACK_Spare_MSK                   (0xFFFFFE00)
  #define DDRDATA8CH0_CR_DATATRAINFEEDBACK_Spare_MIN                   (0)
  #define DDRDATA8CH0_CR_DATATRAINFEEDBACK_Spare_MAX                   (8388607) // 0x007FFFFF
  #define DDRDATA8CH0_CR_DATATRAINFEEDBACK_Spare_DEF                   (0x00000000)
  #define DDRDATA8CH0_CR_DATATRAINFEEDBACK_Spare_HSH                   (0x17091060)

#define DDRDATA8CH0_CR_DLLPITESTANDADC_REG                             (0x00001064)

  #define DDRDATA8CH0_CR_DLLPITESTANDADC_RunTest_OFF                   ( 0)
  #define DDRDATA8CH0_CR_DLLPITESTANDADC_RunTest_WID                   ( 1)
  #define DDRDATA8CH0_CR_DLLPITESTANDADC_RunTest_MSK                   (0x00000001)
  #define DDRDATA8CH0_CR_DLLPITESTANDADC_RunTest_MIN                   (0)
  #define DDRDATA8CH0_CR_DLLPITESTANDADC_RunTest_MAX                   (1) // 0x00000001
  #define DDRDATA8CH0_CR_DLLPITESTANDADC_RunTest_DEF                   (0x00000000)
  #define DDRDATA8CH0_CR_DLLPITESTANDADC_RunTest_HSH                   (0x01001064)

  #define DDRDATA8CH0_CR_DLLPITESTANDADC_Load_OFF                      ( 1)
  #define DDRDATA8CH0_CR_DLLPITESTANDADC_Load_WID                      ( 1)
  #define DDRDATA8CH0_CR_DLLPITESTANDADC_Load_MSK                      (0x00000002)
  #define DDRDATA8CH0_CR_DLLPITESTANDADC_Load_MIN                      (0)
  #define DDRDATA8CH0_CR_DLLPITESTANDADC_Load_MAX                      (1) // 0x00000001
  #define DDRDATA8CH0_CR_DLLPITESTANDADC_Load_DEF                      (0x00000000)
  #define DDRDATA8CH0_CR_DLLPITESTANDADC_Load_HSH                      (0x01011064)

  #define DDRDATA8CH0_CR_DLLPITESTANDADC_ModeHVM_OFF                   ( 2)
  #define DDRDATA8CH0_CR_DLLPITESTANDADC_ModeHVM_WID                   ( 1)
  #define DDRDATA8CH0_CR_DLLPITESTANDADC_ModeHVM_MSK                   (0x00000004)
  #define DDRDATA8CH0_CR_DLLPITESTANDADC_ModeHVM_MIN                   (0)
  #define DDRDATA8CH0_CR_DLLPITESTANDADC_ModeHVM_MAX                   (1) // 0x00000001
  #define DDRDATA8CH0_CR_DLLPITESTANDADC_ModeHVM_DEF                   (0x00000000)
  #define DDRDATA8CH0_CR_DLLPITESTANDADC_ModeHVM_HSH                   (0x01021064)

  #define DDRDATA8CH0_CR_DLLPITESTANDADC_ModeDV_OFF                    ( 3)
  #define DDRDATA8CH0_CR_DLLPITESTANDADC_ModeDV_WID                    ( 1)
  #define DDRDATA8CH0_CR_DLLPITESTANDADC_ModeDV_MSK                    (0x00000008)
  #define DDRDATA8CH0_CR_DLLPITESTANDADC_ModeDV_MIN                    (0)
  #define DDRDATA8CH0_CR_DLLPITESTANDADC_ModeDV_MAX                    (1) // 0x00000001
  #define DDRDATA8CH0_CR_DLLPITESTANDADC_ModeDV_DEF                    (0x00000000)
  #define DDRDATA8CH0_CR_DLLPITESTANDADC_ModeDV_HSH                    (0x01031064)

  #define DDRDATA8CH0_CR_DLLPITESTANDADC_CalCfdl_OFF                   ( 4)
  #define DDRDATA8CH0_CR_DLLPITESTANDADC_CalCfdl_WID                   ( 1)
  #define DDRDATA8CH0_CR_DLLPITESTANDADC_CalCfdl_MSK                   (0x00000010)
  #define DDRDATA8CH0_CR_DLLPITESTANDADC_CalCfdl_MIN                   (0)
  #define DDRDATA8CH0_CR_DLLPITESTANDADC_CalCfdl_MAX                   (1) // 0x00000001
  #define DDRDATA8CH0_CR_DLLPITESTANDADC_CalCfdl_DEF                   (0x00000000)
  #define DDRDATA8CH0_CR_DLLPITESTANDADC_CalCfdl_HSH                   (0x01041064)

  #define DDRDATA8CH0_CR_DLLPITESTANDADC_LoadCount_OFF                 ( 5)
  #define DDRDATA8CH0_CR_DLLPITESTANDADC_LoadCount_WID                 (10)
  #define DDRDATA8CH0_CR_DLLPITESTANDADC_LoadCount_MSK                 (0x00007FE0)
  #define DDRDATA8CH0_CR_DLLPITESTANDADC_LoadCount_MIN                 (0)
  #define DDRDATA8CH0_CR_DLLPITESTANDADC_LoadCount_MAX                 (1023) // 0x000003FF
  #define DDRDATA8CH0_CR_DLLPITESTANDADC_LoadCount_DEF                 (0x00000000)
  #define DDRDATA8CH0_CR_DLLPITESTANDADC_LoadCount_HSH                 (0x0A051064)

  #define DDRDATA8CH0_CR_DLLPITESTANDADC_CountStatus_OFF               (15)
  #define DDRDATA8CH0_CR_DLLPITESTANDADC_CountStatus_WID               (10)
  #define DDRDATA8CH0_CR_DLLPITESTANDADC_CountStatus_MSK               (0x01FF8000)
  #define DDRDATA8CH0_CR_DLLPITESTANDADC_CountStatus_MIN               (0)
  #define DDRDATA8CH0_CR_DLLPITESTANDADC_CountStatus_MAX               (1023) // 0x000003FF
  #define DDRDATA8CH0_CR_DLLPITESTANDADC_CountStatus_DEF               (0x00000000)
  #define DDRDATA8CH0_CR_DLLPITESTANDADC_CountStatus_HSH               (0x0A0F1064)

  #define DDRDATA8CH0_CR_DLLPITESTANDADC_ModeADC_OFF                   (25)
  #define DDRDATA8CH0_CR_DLLPITESTANDADC_ModeADC_WID                   ( 1)
  #define DDRDATA8CH0_CR_DLLPITESTANDADC_ModeADC_MSK                   (0x02000000)
  #define DDRDATA8CH0_CR_DLLPITESTANDADC_ModeADC_MIN                   (0)
  #define DDRDATA8CH0_CR_DLLPITESTANDADC_ModeADC_MAX                   (1) // 0x00000001
  #define DDRDATA8CH0_CR_DLLPITESTANDADC_ModeADC_DEF                   (0x00000000)
  #define DDRDATA8CH0_CR_DLLPITESTANDADC_ModeADC_HSH                   (0x01191064)

  #define DDRDATA8CH0_CR_DLLPITESTANDADC_ADCClkDiv_OFF                 (26)
  #define DDRDATA8CH0_CR_DLLPITESTANDADC_ADCClkDiv_WID                 ( 2)
  #define DDRDATA8CH0_CR_DLLPITESTANDADC_ADCClkDiv_MSK                 (0x0C000000)
  #define DDRDATA8CH0_CR_DLLPITESTANDADC_ADCClkDiv_MIN                 (0)
  #define DDRDATA8CH0_CR_DLLPITESTANDADC_ADCClkDiv_MAX                 (3) // 0x00000003
  #define DDRDATA8CH0_CR_DLLPITESTANDADC_ADCClkDiv_DEF                 (0x00000000)
  #define DDRDATA8CH0_CR_DLLPITESTANDADC_ADCClkDiv_HSH                 (0x021A1064)

  #define DDRDATA8CH0_CR_DLLPITESTANDADC_ADCDdrChanSel_OFF             (28)
  #define DDRDATA8CH0_CR_DLLPITESTANDADC_ADCDdrChanSel_WID             ( 1)
  #define DDRDATA8CH0_CR_DLLPITESTANDADC_ADCDdrChanSel_MSK             (0x10000000)
  #define DDRDATA8CH0_CR_DLLPITESTANDADC_ADCDdrChanSel_MIN             (0)
  #define DDRDATA8CH0_CR_DLLPITESTANDADC_ADCDdrChanSel_MAX             (1) // 0x00000001
  #define DDRDATA8CH0_CR_DLLPITESTANDADC_ADCDdrChanSel_DEF             (0x00000000)
  #define DDRDATA8CH0_CR_DLLPITESTANDADC_ADCDdrChanSel_HSH             (0x011C1064)

  #define DDRDATA8CH0_CR_DLLPITESTANDADC_ADCChopEn_OFF                 (29)
  #define DDRDATA8CH0_CR_DLLPITESTANDADC_ADCChopEn_WID                 ( 1)
  #define DDRDATA8CH0_CR_DLLPITESTANDADC_ADCChopEn_MSK                 (0x20000000)
  #define DDRDATA8CH0_CR_DLLPITESTANDADC_ADCChopEn_MIN                 (0)
  #define DDRDATA8CH0_CR_DLLPITESTANDADC_ADCChopEn_MAX                 (1) // 0x00000001
  #define DDRDATA8CH0_CR_DLLPITESTANDADC_ADCChopEn_DEF                 (0x00000000)
  #define DDRDATA8CH0_CR_DLLPITESTANDADC_ADCChopEn_HSH                 (0x011D1064)

  #define DDRDATA8CH0_CR_DLLPITESTANDADC_ADCDone_OFF                   (30)
  #define DDRDATA8CH0_CR_DLLPITESTANDADC_ADCDone_WID                   ( 1)
  #define DDRDATA8CH0_CR_DLLPITESTANDADC_ADCDone_MSK                   (0x40000000)
  #define DDRDATA8CH0_CR_DLLPITESTANDADC_ADCDone_MIN                   (0)
  #define DDRDATA8CH0_CR_DLLPITESTANDADC_ADCDone_MAX                   (1) // 0x00000001
  #define DDRDATA8CH0_CR_DLLPITESTANDADC_ADCDone_DEF                   (0x00000000)
  #define DDRDATA8CH0_CR_DLLPITESTANDADC_ADCDone_HSH                   (0x011E1064)

  #define DDRDATA8CH0_CR_DLLPITESTANDADC_PhaseDrvPwrSavOn_OFF          (31)
  #define DDRDATA8CH0_CR_DLLPITESTANDADC_PhaseDrvPwrSavOn_WID          ( 1)
  #define DDRDATA8CH0_CR_DLLPITESTANDADC_PhaseDrvPwrSavOn_MSK          (0x80000000)
  #define DDRDATA8CH0_CR_DLLPITESTANDADC_PhaseDrvPwrSavOn_MIN          (0)
  #define DDRDATA8CH0_CR_DLLPITESTANDADC_PhaseDrvPwrSavOn_MAX          (1) // 0x00000001
  #define DDRDATA8CH0_CR_DLLPITESTANDADC_PhaseDrvPwrSavOn_DEF          (0x00000000)
  #define DDRDATA8CH0_CR_DLLPITESTANDADC_PhaseDrvPwrSavOn_HSH          (0x011F1064)

#define DDRDATA8CH0_CR_DDRCRDATAOFFSETCOMP_REG                         (0x00001068)

  #define DDRDATA8CH0_CR_DDRCRDATAOFFSETCOMP_DqDrvUpCompOffset_OFF     ( 0)
  #define DDRDATA8CH0_CR_DDRCRDATAOFFSETCOMP_DqDrvUpCompOffset_WID     ( 6)
  #define DDRDATA8CH0_CR_DDRCRDATAOFFSETCOMP_DqDrvUpCompOffset_MSK     (0x0000003F)
  #define DDRDATA8CH0_CR_DDRCRDATAOFFSETCOMP_DqDrvUpCompOffset_MIN     (-32)
  #define DDRDATA8CH0_CR_DDRCRDATAOFFSETCOMP_DqDrvUpCompOffset_MAX     (31) // 0x0000001F
  #define DDRDATA8CH0_CR_DDRCRDATAOFFSETCOMP_DqDrvUpCompOffset_DEF     (0x00000000)
  #define DDRDATA8CH0_CR_DDRCRDATAOFFSETCOMP_DqDrvUpCompOffset_HSH     (0x86001068)

  #define DDRDATA8CH0_CR_DDRCRDATAOFFSETCOMP_DqDrvDownCompOffset_OFF   ( 6)
  #define DDRDATA8CH0_CR_DDRCRDATAOFFSETCOMP_DqDrvDownCompOffset_WID   ( 6)
  #define DDRDATA8CH0_CR_DDRCRDATAOFFSETCOMP_DqDrvDownCompOffset_MSK   (0x00000FC0)
  #define DDRDATA8CH0_CR_DDRCRDATAOFFSETCOMP_DqDrvDownCompOffset_MIN   (-32)
  #define DDRDATA8CH0_CR_DDRCRDATAOFFSETCOMP_DqDrvDownCompOffset_MAX   (31) // 0x0000001F
  #define DDRDATA8CH0_CR_DDRCRDATAOFFSETCOMP_DqDrvDownCompOffset_DEF   (0x00000000)
  #define DDRDATA8CH0_CR_DDRCRDATAOFFSETCOMP_DqDrvDownCompOffset_HSH   (0x86061068)

  #define DDRDATA8CH0_CR_DDRCRDATAOFFSETCOMP_DqOdtUpCompOffset_OFF     (12)
  #define DDRDATA8CH0_CR_DDRCRDATAOFFSETCOMP_DqOdtUpCompOffset_WID     ( 5)
  #define DDRDATA8CH0_CR_DDRCRDATAOFFSETCOMP_DqOdtUpCompOffset_MSK     (0x0001F000)
  #define DDRDATA8CH0_CR_DDRCRDATAOFFSETCOMP_DqOdtUpCompOffset_MIN     (-16)
  #define DDRDATA8CH0_CR_DDRCRDATAOFFSETCOMP_DqOdtUpCompOffset_MAX     (15) // 0x0000000F
  #define DDRDATA8CH0_CR_DDRCRDATAOFFSETCOMP_DqOdtUpCompOffset_DEF     (0x00000000)
  #define DDRDATA8CH0_CR_DDRCRDATAOFFSETCOMP_DqOdtUpCompOffset_HSH     (0x850C1068)

  #define DDRDATA8CH0_CR_DDRCRDATAOFFSETCOMP_DqOdtDownCompOffset_OFF   (17)
  #define DDRDATA8CH0_CR_DDRCRDATAOFFSETCOMP_DqOdtDownCompOffset_WID   ( 5)
  #define DDRDATA8CH0_CR_DDRCRDATAOFFSETCOMP_DqOdtDownCompOffset_MSK   (0x003E0000)
  #define DDRDATA8CH0_CR_DDRCRDATAOFFSETCOMP_DqOdtDownCompOffset_MIN   (-16)
  #define DDRDATA8CH0_CR_DDRCRDATAOFFSETCOMP_DqOdtDownCompOffset_MAX   (15) // 0x0000000F
  #define DDRDATA8CH0_CR_DDRCRDATAOFFSETCOMP_DqOdtDownCompOffset_DEF   (0x00000000)
  #define DDRDATA8CH0_CR_DDRCRDATAOFFSETCOMP_DqOdtDownCompOffset_HSH   (0x85111068)

  #define DDRDATA8CH0_CR_DDRCRDATAOFFSETCOMP_DqTcoCompOffset_OFF       (22)
  #define DDRDATA8CH0_CR_DDRCRDATAOFFSETCOMP_DqTcoCompOffset_WID       ( 5)
  #define DDRDATA8CH0_CR_DDRCRDATAOFFSETCOMP_DqTcoCompOffset_MSK       (0x07C00000)
  #define DDRDATA8CH0_CR_DDRCRDATAOFFSETCOMP_DqTcoCompOffset_MIN       (-16)
  #define DDRDATA8CH0_CR_DDRCRDATAOFFSETCOMP_DqTcoCompOffset_MAX       (15) // 0x0000000F
  #define DDRDATA8CH0_CR_DDRCRDATAOFFSETCOMP_DqTcoCompOffset_DEF       (0x00000000)
  #define DDRDATA8CH0_CR_DDRCRDATAOFFSETCOMP_DqTcoCompOffset_HSH       (0x85161068)

  #define DDRDATA8CH0_CR_DDRCRDATAOFFSETCOMP_DqSlewRateCompOffset_OFF  (27)
  #define DDRDATA8CH0_CR_DDRCRDATAOFFSETCOMP_DqSlewRateCompOffset_WID  ( 5)
  #define DDRDATA8CH0_CR_DDRCRDATAOFFSETCOMP_DqSlewRateCompOffset_MSK  (0xF8000000)
  #define DDRDATA8CH0_CR_DDRCRDATAOFFSETCOMP_DqSlewRateCompOffset_MIN  (-16)
  #define DDRDATA8CH0_CR_DDRCRDATAOFFSETCOMP_DqSlewRateCompOffset_MAX  (15) // 0x0000000F
  #define DDRDATA8CH0_CR_DDRCRDATAOFFSETCOMP_DqSlewRateCompOffset_DEF  (0x00000000)
  #define DDRDATA8CH0_CR_DDRCRDATAOFFSETCOMP_DqSlewRateCompOffset_HSH  (0x851B1068)

#define DDRDATA8CH0_CR_DDRCRDATACONTROL1_REG                           (0x0000106C)

  #define DDRDATA8CH0_CR_DDRCRDATACONTROL1_RefPi_OFF                   ( 0)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL1_RefPi_WID                   ( 4)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL1_RefPi_MSK                   (0x0000000F)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL1_RefPi_MIN                   (-8)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL1_RefPi_MAX                   (7) // 0x00000007
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL1_RefPi_DEF                   (0x00000000)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL1_RefPi_HSH                   (0x8400106C)

  #define DDRDATA8CH0_CR_DDRCRDATACONTROL1_DllMask_OFF                 ( 4)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL1_DllMask_WID                 ( 2)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL1_DllMask_MSK                 (0x00000030)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL1_DllMask_MIN                 (0)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL1_DllMask_MAX                 (3) // 0x00000003
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL1_DllMask_DEF                 (0x00000000)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL1_DllMask_HSH                 (0x0204106C)

  #define DDRDATA8CH0_CR_DDRCRDATACONTROL1_DllWeakLock_OFF             ( 6)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL1_DllWeakLock_WID             ( 1)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL1_DllWeakLock_MSK             (0x00000040)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL1_DllWeakLock_MIN             (0)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL1_DllWeakLock_MAX             (1) // 0x00000001
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL1_DllWeakLock_DEF             (0x00000000)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL1_DllWeakLock_HSH             (0x0106106C)

  #define DDRDATA8CH0_CR_DDRCRDATACONTROL1_SdllSegmentDisable_OFF      ( 7)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL1_SdllSegmentDisable_WID      ( 3)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL1_SdllSegmentDisable_MSK      (0x00000380)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL1_SdllSegmentDisable_MIN      (0)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL1_SdllSegmentDisable_MAX      (7) // 0x00000007
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL1_SdllSegmentDisable_DEF      (0x00000000)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL1_SdllSegmentDisable_HSH      (0x0307106C)

  #define DDRDATA8CH0_CR_DDRCRDATACONTROL1_RxBiasCtl_OFF               (10)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL1_RxBiasCtl_WID               ( 4)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL1_RxBiasCtl_MSK               (0x00003C00)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL1_RxBiasCtl_MIN               (0)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL1_RxBiasCtl_MAX               (15) // 0x0000000F
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL1_RxBiasCtl_DEF               (0x00000008)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL1_RxBiasCtl_HSH               (0x040A106C)

  #define DDRDATA8CH0_CR_DDRCRDATACONTROL1_OdtDelay_OFF                (14)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL1_OdtDelay_WID                ( 4)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL1_OdtDelay_MSK                (0x0003C000)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL1_OdtDelay_MIN                (-8)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL1_OdtDelay_MAX                (7) // 0x00000007
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL1_OdtDelay_DEF                (0x00000000)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL1_OdtDelay_HSH                (0x840E106C)

  #define DDRDATA8CH0_CR_DDRCRDATACONTROL1_OdtDuration_OFF             (18)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL1_OdtDuration_WID             ( 3)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL1_OdtDuration_MSK             (0x001C0000)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL1_OdtDuration_MIN             (0)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL1_OdtDuration_MAX             (7) // 0x00000007
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL1_OdtDuration_DEF             (0x00000000)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL1_OdtDuration_HSH             (0x0312106C)

  #define DDRDATA8CH0_CR_DDRCRDATACONTROL1_SenseAmpDelay_OFF           (21)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL1_SenseAmpDelay_WID           ( 4)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL1_SenseAmpDelay_MSK           (0x01E00000)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL1_SenseAmpDelay_MIN           (-8)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL1_SenseAmpDelay_MAX           (7) // 0x00000007
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL1_SenseAmpDelay_DEF           (0x00000000)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL1_SenseAmpDelay_HSH           (0x8415106C)

  #define DDRDATA8CH0_CR_DDRCRDATACONTROL1_SenseAmpDuration_OFF        (25)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL1_SenseAmpDuration_WID        ( 3)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL1_SenseAmpDuration_MSK        (0x0E000000)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL1_SenseAmpDuration_MIN        (0)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL1_SenseAmpDuration_MAX        (7) // 0x00000007
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL1_SenseAmpDuration_DEF        (0x00000000)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL1_SenseAmpDuration_HSH        (0x0319106C)

  #define DDRDATA8CH0_CR_DDRCRDATACONTROL1_StrongWkLeaker_OFF          (28)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL1_StrongWkLeaker_WID          ( 3)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL1_StrongWkLeaker_MSK          (0x70000000)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL1_StrongWkLeaker_MIN          (0)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL1_StrongWkLeaker_MAX          (7) // 0x00000007
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL1_StrongWkLeaker_DEF          (0x00000000)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL1_StrongWkLeaker_HSH          (0x031C106C)

  #define DDRDATA8CH0_CR_DDRCRDATACONTROL1_LpDdrLongOdtEn_OFF          (31)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL1_LpDdrLongOdtEn_WID          ( 1)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL1_LpDdrLongOdtEn_MSK          (0x80000000)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL1_LpDdrLongOdtEn_MIN          (0)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL1_LpDdrLongOdtEn_MAX          (1) // 0x00000001
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL1_LpDdrLongOdtEn_DEF          (0x00000000)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL1_LpDdrLongOdtEn_HSH          (0x011F106C)

#define DDRDATA8CH0_CR_DDRCRDATACONTROL2_REG                           (0x00001070)

  #define DDRDATA8CH0_CR_DDRCRDATACONTROL2_RxStaggerCtl_OFF            ( 0)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL2_RxStaggerCtl_WID            ( 5)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL2_RxStaggerCtl_MSK            (0x0000001F)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL2_RxStaggerCtl_MIN            (0)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL2_RxStaggerCtl_MAX            (31) // 0x0000001F
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL2_RxStaggerCtl_DEF            (0x00000000)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL2_RxStaggerCtl_HSH            (0x05001070)

  #define DDRDATA8CH0_CR_DDRCRDATACONTROL2_ForceBiasOn_OFF             ( 5)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL2_ForceBiasOn_WID             ( 1)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL2_ForceBiasOn_MSK             (0x00000020)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL2_ForceBiasOn_MIN             (0)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL2_ForceBiasOn_MAX             (1) // 0x00000001
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL2_ForceBiasOn_DEF             (0x00000000)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL2_ForceBiasOn_HSH             (0x01051070)

  #define DDRDATA8CH0_CR_DDRCRDATACONTROL2_ForceRxOn_OFF               ( 6)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL2_ForceRxOn_WID               ( 1)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL2_ForceRxOn_MSK               (0x00000040)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL2_ForceRxOn_MIN               (0)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL2_ForceRxOn_MAX               (1) // 0x00000001
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL2_ForceRxOn_DEF               (0x00000000)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL2_ForceRxOn_HSH               (0x01061070)

  #define DDRDATA8CH0_CR_DDRCRDATACONTROL2_LeakerComp_OFF              ( 7)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL2_LeakerComp_WID              ( 2)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL2_LeakerComp_MSK              (0x00000180)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL2_LeakerComp_MIN              (0)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL2_LeakerComp_MAX              (3) // 0x00000003
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL2_LeakerComp_DEF              (0x00000000)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL2_LeakerComp_HSH              (0x02071070)

  #define DDRDATA8CH0_CR_DDRCRDATACONTROL2_RxDqsAmpOffset_OFF          ( 9)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL2_RxDqsAmpOffset_WID          ( 4)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL2_RxDqsAmpOffset_MSK          (0x00001E00)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL2_RxDqsAmpOffset_MIN          (0)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL2_RxDqsAmpOffset_MAX          (15) // 0x0000000F
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL2_RxDqsAmpOffset_DEF          (0x00000008)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL2_RxDqsAmpOffset_HSH          (0x04091070)

  #define DDRDATA8CH0_CR_DDRCRDATACONTROL2_RxClkStgNum_OFF             (13)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL2_RxClkStgNum_WID             ( 5)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL2_RxClkStgNum_MSK             (0x0003E000)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL2_RxClkStgNum_MIN             (0)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL2_RxClkStgNum_MAX             (31) // 0x0000001F
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL2_RxClkStgNum_DEF             (0x00000011)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL2_RxClkStgNum_HSH             (0x050D1070)

  #define DDRDATA8CH0_CR_DDRCRDATACONTROL2_WlLongDelEn_OFF             (18)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL2_WlLongDelEn_WID             ( 1)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL2_WlLongDelEn_MSK             (0x00040000)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL2_WlLongDelEn_MIN             (0)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL2_WlLongDelEn_MAX             (1) // 0x00000001
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL2_WlLongDelEn_DEF             (0x00000000)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL2_WlLongDelEn_HSH             (0x01121070)

  #define DDRDATA8CH0_CR_DDRCRDATACONTROL2_EnableVrefPwrDn_OFF         (19)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL2_EnableVrefPwrDn_WID         ( 1)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL2_EnableVrefPwrDn_MSK         (0x00080000)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL2_EnableVrefPwrDn_MIN         (0)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL2_EnableVrefPwrDn_MAX         (1) // 0x00000001
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL2_EnableVrefPwrDn_DEF         (0x00000000)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL2_EnableVrefPwrDn_HSH         (0x01131070)

  #define DDRDATA8CH0_CR_DDRCRDATACONTROL2_Ddr4Mode_OFF                (20)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL2_Ddr4Mode_WID                ( 1)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL2_Ddr4Mode_MSK                (0x00100000)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL2_Ddr4Mode_MIN                (0)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL2_Ddr4Mode_MAX                (1) // 0x00000001
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL2_Ddr4Mode_DEF                (0x00000000)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL2_Ddr4Mode_HSH                (0x01141070)

  #define DDRDATA8CH0_CR_DDRCRDATACONTROL2_EnVddqOdt_OFF               (21)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL2_EnVddqOdt_WID               ( 1)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL2_EnVddqOdt_MSK               (0x00200000)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL2_EnVddqOdt_MIN               (0)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL2_EnVddqOdt_MAX               (1) // 0x00000001
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL2_EnVddqOdt_DEF               (0x00000000)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL2_EnVddqOdt_HSH               (0x01151070)

  #define DDRDATA8CH0_CR_DDRCRDATACONTROL2_EnVttOdt_OFF                (22)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL2_EnVttOdt_WID                ( 1)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL2_EnVttOdt_MSK                (0x00400000)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL2_EnVttOdt_MIN                (0)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL2_EnVttOdt_MAX                (1) // 0x00000001
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL2_EnVttOdt_DEF                (0x00000000)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL2_EnVttOdt_HSH                (0x01161070)

  #define DDRDATA8CH0_CR_DDRCRDATACONTROL2_EnConstZEqTx_OFF            (23)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL2_EnConstZEqTx_WID            ( 1)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL2_EnConstZEqTx_MSK            (0x00800000)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL2_EnConstZEqTx_MIN            (0)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL2_EnConstZEqTx_MAX            (1) // 0x00000001
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL2_EnConstZEqTx_DEF            (0x00000000)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL2_EnConstZEqTx_HSH            (0x01171070)

  #define DDRDATA8CH0_CR_DDRCRDATACONTROL2_TxEqDis_OFF                 (24)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL2_TxEqDis_WID                 ( 1)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL2_TxEqDis_MSK                 (0x01000000)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL2_TxEqDis_MIN                 (0)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL2_TxEqDis_MAX                 (1) // 0x00000001
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL2_TxEqDis_DEF                 (0x00000000)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL2_TxEqDis_HSH                 (0x01181070)

  #define DDRDATA8CH0_CR_DDRCRDATACONTROL2_RxVrefProgMFC_OFF           (25)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL2_RxVrefProgMFC_WID           ( 1)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL2_RxVrefProgMFC_MSK           (0x02000000)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL2_RxVrefProgMFC_MIN           (0)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL2_RxVrefProgMFC_MAX           (1) // 0x00000001
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL2_RxVrefProgMFC_DEF           (0x00000000)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL2_RxVrefProgMFC_HSH           (0x01191070)

  #define DDRDATA8CH0_CR_DDRCRDATACONTROL2_Cben_OFF                    (26)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL2_Cben_WID                    ( 3)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL2_Cben_MSK                    (0x1C000000)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL2_Cben_MIN                    (0)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL2_Cben_MAX                    (7) // 0x00000007
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL2_Cben_DEF                    (0x00000000)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL2_Cben_HSH                    (0x031A1070)

  #define DDRDATA8CH0_CR_DDRCRDATACONTROL2_TxDeskewDisable_OFF         (29)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL2_TxDeskewDisable_WID         ( 1)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL2_TxDeskewDisable_MSK         (0x20000000)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL2_TxDeskewDisable_MIN         (0)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL2_TxDeskewDisable_MAX         (1) // 0x00000001
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL2_TxDeskewDisable_DEF         (0x00000000)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL2_TxDeskewDisable_HSH         (0x011D1070)

  #define DDRDATA8CH0_CR_DDRCRDATACONTROL2_RxDeskewDisable_OFF         (30)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL2_RxDeskewDisable_WID         ( 1)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL2_RxDeskewDisable_MSK         (0x40000000)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL2_RxDeskewDisable_MIN         (0)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL2_RxDeskewDisable_MAX         (1) // 0x00000001
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL2_RxDeskewDisable_DEF         (0x00000000)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL2_RxDeskewDisable_HSH         (0x011E1070)

  #define DDRDATA8CH0_CR_DDRCRDATACONTROL2_DqSlewDlyByPass_OFF         (31)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL2_DqSlewDlyByPass_WID         ( 1)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL2_DqSlewDlyByPass_MSK         (0x80000000)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL2_DqSlewDlyByPass_MIN         (0)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL2_DqSlewDlyByPass_MAX         (1) // 0x00000001
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL2_DqSlewDlyByPass_DEF         (0x00000000)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL2_DqSlewDlyByPass_HSH         (0x011F1070)

#define DDRDATA8CH0_CR_DDRCRVREFCONTROL_REG                            (0x00001074)

  #define DDRDATA8CH0_CR_DDRCRVREFCONTROL_VrefCtl_OFF                  ( 0)
  #define DDRDATA8CH0_CR_DDRCRVREFCONTROL_VrefCtl_WID                  (24)
  #define DDRDATA8CH0_CR_DDRCRVREFCONTROL_VrefCtl_MSK                  (0x00FFFFFF)
  #define DDRDATA8CH0_CR_DDRCRVREFCONTROL_VrefCtl_MIN                  (0)
  #define DDRDATA8CH0_CR_DDRCRVREFCONTROL_VrefCtl_MAX                  (16777215) // 0x00FFFFFF
  #define DDRDATA8CH0_CR_DDRCRVREFCONTROL_VrefCtl_DEF                  (0x000E453A)
  #define DDRDATA8CH0_CR_DDRCRVREFCONTROL_VrefCtl_HSH                  (0x18001074)

  #define DDRDATA8CH0_CR_DDRCRVREFCONTROL_OutputCode_OFF               (24)
  #define DDRDATA8CH0_CR_DDRCRVREFCONTROL_OutputCode_WID               ( 8)
  #define DDRDATA8CH0_CR_DDRCRVREFCONTROL_OutputCode_MSK               (0xFF000000)
  #define DDRDATA8CH0_CR_DDRCRVREFCONTROL_OutputCode_MIN               (0)
  #define DDRDATA8CH0_CR_DDRCRVREFCONTROL_OutputCode_MAX               (255) // 0x000000FF
  #define DDRDATA8CH0_CR_DDRCRVREFCONTROL_OutputCode_DEF               (0x00000000)
  #define DDRDATA8CH0_CR_DDRCRVREFCONTROL_OutputCode_HSH               (0x08181074)

#define DDRDATA8CH0_CR_DDRCRVSSHICONTROL_REG                           (0x00001078)

  #define DDRDATA8CH0_CR_DDRCRVSSHICONTROL_VssHiCtl_OFF                ( 0)
  #define DDRDATA8CH0_CR_DDRCRVSSHICONTROL_VssHiCtl_WID                (25)
  #define DDRDATA8CH0_CR_DDRCRVSSHICONTROL_VssHiCtl_MSK                (0x01FFFFFF)
  #define DDRDATA8CH0_CR_DDRCRVSSHICONTROL_VssHiCtl_MIN                (0)
  #define DDRDATA8CH0_CR_DDRCRVSSHICONTROL_VssHiCtl_MAX                (33554431) // 0x01FFFFFF
  #define DDRDATA8CH0_CR_DDRCRVSSHICONTROL_VssHiCtl_DEF                (0x014D8234)
  #define DDRDATA8CH0_CR_DDRCRVSSHICONTROL_VssHiCtl_HSH                (0x19001078)

  #define DDRDATA8CH0_CR_DDRCRVSSHICONTROL_OutputCode_OFF              (25)
  #define DDRDATA8CH0_CR_DDRCRVSSHICONTROL_OutputCode_WID              ( 7)
  #define DDRDATA8CH0_CR_DDRCRVSSHICONTROL_OutputCode_MSK              (0xFE000000)
  #define DDRDATA8CH0_CR_DDRCRVSSHICONTROL_OutputCode_MIN              (0)
  #define DDRDATA8CH0_CR_DDRCRVSSHICONTROL_OutputCode_MAX              (127) // 0x0000007F
  #define DDRDATA8CH0_CR_DDRCRVSSHICONTROL_OutputCode_DEF              (0x00000000)
  #define DDRDATA8CH0_CR_DDRCRVSSHICONTROL_OutputCode_HSH              (0x07191078)

#define DDRDATA8CH0_CR_DDRCRDATAOFFSETTRAIN_REG                        (0x0000107C)

  #define DDRDATA8CH0_CR_DDRCRDATAOFFSETTRAIN_RcvEnOffset_OFF          ( 0)
  #define DDRDATA8CH0_CR_DDRCRDATAOFFSETTRAIN_RcvEnOffset_WID          ( 6)
  #define DDRDATA8CH0_CR_DDRCRDATAOFFSETTRAIN_RcvEnOffset_MSK          (0x0000003F)
  #define DDRDATA8CH0_CR_DDRCRDATAOFFSETTRAIN_RcvEnOffset_MIN          (-32)
  #define DDRDATA8CH0_CR_DDRCRDATAOFFSETTRAIN_RcvEnOffset_MAX          (31) // 0x0000001F
  #define DDRDATA8CH0_CR_DDRCRDATAOFFSETTRAIN_RcvEnOffset_DEF          (0x00000000)
  #define DDRDATA8CH0_CR_DDRCRDATAOFFSETTRAIN_RcvEnOffset_HSH          (0x8600107C)

  #define DDRDATA8CH0_CR_DDRCRDATAOFFSETTRAIN_RxDqsOffset_OFF          ( 6)
  #define DDRDATA8CH0_CR_DDRCRDATAOFFSETTRAIN_RxDqsOffset_WID          ( 6)
  #define DDRDATA8CH0_CR_DDRCRDATAOFFSETTRAIN_RxDqsOffset_MSK          (0x00000FC0)
  #define DDRDATA8CH0_CR_DDRCRDATAOFFSETTRAIN_RxDqsOffset_MIN          (-32)
  #define DDRDATA8CH0_CR_DDRCRDATAOFFSETTRAIN_RxDqsOffset_MAX          (31) // 0x0000001F
  #define DDRDATA8CH0_CR_DDRCRDATAOFFSETTRAIN_RxDqsOffset_DEF          (0x00000000)
  #define DDRDATA8CH0_CR_DDRCRDATAOFFSETTRAIN_RxDqsOffset_HSH          (0x8606107C)

  #define DDRDATA8CH0_CR_DDRCRDATAOFFSETTRAIN_TxDqOffset_OFF           (12)
  #define DDRDATA8CH0_CR_DDRCRDATAOFFSETTRAIN_TxDqOffset_WID           ( 6)
  #define DDRDATA8CH0_CR_DDRCRDATAOFFSETTRAIN_TxDqOffset_MSK           (0x0003F000)
  #define DDRDATA8CH0_CR_DDRCRDATAOFFSETTRAIN_TxDqOffset_MIN           (-32)
  #define DDRDATA8CH0_CR_DDRCRDATAOFFSETTRAIN_TxDqOffset_MAX           (31) // 0x0000001F
  #define DDRDATA8CH0_CR_DDRCRDATAOFFSETTRAIN_TxDqOffset_DEF           (0x00000000)
  #define DDRDATA8CH0_CR_DDRCRDATAOFFSETTRAIN_TxDqOffset_HSH           (0x860C107C)

  #define DDRDATA8CH0_CR_DDRCRDATAOFFSETTRAIN_TxDqsOffset_OFF          (18)
  #define DDRDATA8CH0_CR_DDRCRDATAOFFSETTRAIN_TxDqsOffset_WID          ( 6)
  #define DDRDATA8CH0_CR_DDRCRDATAOFFSETTRAIN_TxDqsOffset_MSK          (0x00FC0000)
  #define DDRDATA8CH0_CR_DDRCRDATAOFFSETTRAIN_TxDqsOffset_MIN          (-32)
  #define DDRDATA8CH0_CR_DDRCRDATAOFFSETTRAIN_TxDqsOffset_MAX          (31) // 0x0000001F
  #define DDRDATA8CH0_CR_DDRCRDATAOFFSETTRAIN_TxDqsOffset_DEF          (0x00000000)
  #define DDRDATA8CH0_CR_DDRCRDATAOFFSETTRAIN_TxDqsOffset_HSH          (0x8612107C)

  #define DDRDATA8CH0_CR_DDRCRDATAOFFSETTRAIN_VrefOffset_OFF           (24)
  #define DDRDATA8CH0_CR_DDRCRDATAOFFSETTRAIN_VrefOffset_WID           ( 7)
  #define DDRDATA8CH0_CR_DDRCRDATAOFFSETTRAIN_VrefOffset_MSK           (0x7F000000)
  #define DDRDATA8CH0_CR_DDRCRDATAOFFSETTRAIN_VrefOffset_MIN           (-64)
  #define DDRDATA8CH0_CR_DDRCRDATAOFFSETTRAIN_VrefOffset_MAX           (63) // 0x0000003F
  #define DDRDATA8CH0_CR_DDRCRDATAOFFSETTRAIN_VrefOffset_DEF           (0x00000000)
  #define DDRDATA8CH0_CR_DDRCRDATAOFFSETTRAIN_VrefOffset_HSH           (0x8718107C)

  #define DDRDATA8CH0_CR_DDRCRDATAOFFSETTRAIN_Spare_OFF                (31)
  #define DDRDATA8CH0_CR_DDRCRDATAOFFSETTRAIN_Spare_WID                ( 1)
  #define DDRDATA8CH0_CR_DDRCRDATAOFFSETTRAIN_Spare_MSK                (0x80000000)
  #define DDRDATA8CH0_CR_DDRCRDATAOFFSETTRAIN_Spare_MIN                (0)
  #define DDRDATA8CH0_CR_DDRCRDATAOFFSETTRAIN_Spare_MAX                (1) // 0x00000001
  #define DDRDATA8CH0_CR_DDRCRDATAOFFSETTRAIN_Spare_DEF                (0x00000000)
  #define DDRDATA8CH0_CR_DDRCRDATAOFFSETTRAIN_Spare_HSH                (0x011F107C)

#define DDRDATA8CH0_CR_DDRCRDATACONTROL0_REG                           (0x00001080)

  #define DDRDATA8CH0_CR_DDRCRDATACONTROL0_RxTrainingMode_OFF          ( 0)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL0_RxTrainingMode_WID          ( 1)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL0_RxTrainingMode_MSK          (0x00000001)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL0_RxTrainingMode_MIN          (0)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL0_RxTrainingMode_MAX          (1) // 0x00000001
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL0_RxTrainingMode_DEF          (0x00000000)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL0_RxTrainingMode_HSH          (0x01001080)

  #define DDRDATA8CH0_CR_DDRCRDATACONTROL0_WLTrainingMode_OFF          ( 1)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL0_WLTrainingMode_WID          ( 1)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL0_WLTrainingMode_MSK          (0x00000002)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL0_WLTrainingMode_MIN          (0)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL0_WLTrainingMode_MAX          (1) // 0x00000001
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL0_WLTrainingMode_DEF          (0x00000000)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL0_WLTrainingMode_HSH          (0x01011080)

  #define DDRDATA8CH0_CR_DDRCRDATACONTROL0_RLTrainingMode_OFF          ( 2)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL0_RLTrainingMode_WID          ( 1)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL0_RLTrainingMode_MSK          (0x00000004)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL0_RLTrainingMode_MIN          (0)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL0_RLTrainingMode_MAX          (1) // 0x00000001
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL0_RLTrainingMode_DEF          (0x00000000)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL0_RLTrainingMode_HSH          (0x01021080)

  #define DDRDATA8CH0_CR_DDRCRDATACONTROL0_SenseampTrainingMode_OFF    ( 3)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL0_SenseampTrainingMode_WID    ( 1)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL0_SenseampTrainingMode_MSK    (0x00000008)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL0_SenseampTrainingMode_MIN    (0)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL0_SenseampTrainingMode_MAX    (1) // 0x00000001
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL0_SenseampTrainingMode_DEF    (0x00000000)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL0_SenseampTrainingMode_HSH    (0x01031080)

  #define DDRDATA8CH0_CR_DDRCRDATACONTROL0_TxOn_OFF                    ( 4)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL0_TxOn_WID                    ( 1)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL0_TxOn_MSK                    (0x00000010)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL0_TxOn_MIN                    (0)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL0_TxOn_MAX                    (1) // 0x00000001
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL0_TxOn_DEF                    (0x00000000)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL0_TxOn_HSH                    (0x01041080)

  #define DDRDATA8CH0_CR_DDRCRDATACONTROL0_RfOn_OFF                    ( 5)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL0_RfOn_WID                    ( 1)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL0_RfOn_MSK                    (0x00000020)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL0_RfOn_MIN                    (0)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL0_RfOn_MAX                    (1) // 0x00000001
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL0_RfOn_DEF                    (0x00000000)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL0_RfOn_HSH                    (0x01051080)

  #define DDRDATA8CH0_CR_DDRCRDATACONTROL0_RxPiOn_OFF                  ( 6)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL0_RxPiOn_WID                  ( 1)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL0_RxPiOn_MSK                  (0x00000040)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL0_RxPiOn_MIN                  (0)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL0_RxPiOn_MAX                  (1) // 0x00000001
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL0_RxPiOn_DEF                  (0x00000000)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL0_RxPiOn_HSH                  (0x01061080)

  #define DDRDATA8CH0_CR_DDRCRDATACONTROL0_TxPiOn_OFF                  ( 7)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL0_TxPiOn_WID                  ( 1)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL0_TxPiOn_MSK                  (0x00000080)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL0_TxPiOn_MIN                  (0)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL0_TxPiOn_MAX                  (1) // 0x00000001
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL0_TxPiOn_DEF                  (0x00000000)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL0_TxPiOn_HSH                  (0x01071080)

  #define DDRDATA8CH0_CR_DDRCRDATACONTROL0_InternalClocksOn_OFF        ( 8)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL0_InternalClocksOn_WID        ( 1)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL0_InternalClocksOn_MSK        (0x00000100)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL0_InternalClocksOn_MIN        (0)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL0_InternalClocksOn_MAX        (1) // 0x00000001
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL0_InternalClocksOn_DEF        (0x00000000)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL0_InternalClocksOn_HSH        (0x01081080)

  #define DDRDATA8CH0_CR_DDRCRDATACONTROL0_RepeaterClocksOn_OFF        ( 9)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL0_RepeaterClocksOn_WID        ( 1)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL0_RepeaterClocksOn_MSK        (0x00000200)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL0_RepeaterClocksOn_MIN        (0)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL0_RepeaterClocksOn_MAX        (1) // 0x00000001
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL0_RepeaterClocksOn_DEF        (0x00000000)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL0_RepeaterClocksOn_HSH        (0x01091080)

  #define DDRDATA8CH0_CR_DDRCRDATACONTROL0_TxDisable_OFF               (10)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL0_TxDisable_WID               ( 1)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL0_TxDisable_MSK               (0x00000400)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL0_TxDisable_MIN               (0)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL0_TxDisable_MAX               (1) // 0x00000001
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL0_TxDisable_DEF               (0x00000000)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL0_TxDisable_HSH               (0x010A1080)

  #define DDRDATA8CH0_CR_DDRCRDATACONTROL0_RxDisable_OFF               (11)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL0_RxDisable_WID               ( 1)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL0_RxDisable_MSK               (0x00000800)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL0_RxDisable_MIN               (0)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL0_RxDisable_MAX               (1) // 0x00000001
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL0_RxDisable_DEF               (0x00000000)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL0_RxDisable_HSH               (0x010B1080)

  #define DDRDATA8CH0_CR_DDRCRDATACONTROL0_TxLong_OFF                  (12)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL0_TxLong_WID                  ( 1)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL0_TxLong_MSK                  (0x00001000)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL0_TxLong_MIN                  (0)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL0_TxLong_MAX                  (1) // 0x00000001
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL0_TxLong_DEF                  (0x00000000)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL0_TxLong_HSH                  (0x010C1080)

  #define DDRDATA8CH0_CR_DDRCRDATACONTROL0_RxDqsCtle_OFF               (13)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL0_RxDqsCtle_WID               ( 2)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL0_RxDqsCtle_MSK               (0x00006000)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL0_RxDqsCtle_MIN               (0)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL0_RxDqsCtle_MAX               (3) // 0x00000003
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL0_RxDqsCtle_DEF               (0x00000000)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL0_RxDqsCtle_HSH               (0x020D1080)

  #define DDRDATA8CH0_CR_DDRCRDATACONTROL0_RxReadPointer_OFF           (15)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL0_RxReadPointer_WID           ( 3)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL0_RxReadPointer_MSK           (0x00038000)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL0_RxReadPointer_MIN           (0)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL0_RxReadPointer_MAX           (7) // 0x00000007
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL0_RxReadPointer_DEF           (0x00000000)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL0_RxReadPointer_HSH           (0x030F1080)

  #define DDRDATA8CH0_CR_DDRCRDATACONTROL0_LongOdtR2W_OFF              (18)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL0_LongOdtR2W_WID              ( 1)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL0_LongOdtR2W_MSK              (0x00040000)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL0_LongOdtR2W_MIN              (0)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL0_LongOdtR2W_MAX              (1) // 0x00000001
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL0_LongOdtR2W_DEF              (0x00000000)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL0_LongOdtR2W_HSH              (0x01121080)

  #define DDRDATA8CH0_CR_DDRCRDATACONTROL0_DataVccddqHi_OFF            (19)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL0_DataVccddqHi_WID            ( 1)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL0_DataVccddqHi_MSK            (0x00080000)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL0_DataVccddqHi_MIN            (0)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL0_DataVccddqHi_MAX            (1) // 0x00000001
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL0_DataVccddqHi_DEF            (0x00000000)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL0_DataVccddqHi_HSH            (0x01131080)

  #define DDRDATA8CH0_CR_DDRCRDATACONTROL0_ReadRFRd_OFF                (20)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL0_ReadRFRd_WID                ( 1)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL0_ReadRFRd_MSK                (0x00100000)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL0_ReadRFRd_MIN                (0)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL0_ReadRFRd_MAX                (1) // 0x00000001
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL0_ReadRFRd_DEF                (0x00000000)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL0_ReadRFRd_HSH                (0x01141080)

  #define DDRDATA8CH0_CR_DDRCRDATACONTROL0_ReadRFWr_OFF                (21)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL0_ReadRFWr_WID                ( 1)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL0_ReadRFWr_MSK                (0x00200000)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL0_ReadRFWr_MIN                (0)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL0_ReadRFWr_MAX                (1) // 0x00000001
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL0_ReadRFWr_DEF                (0x00000000)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL0_ReadRFWr_HSH                (0x01151080)

  #define DDRDATA8CH0_CR_DDRCRDATACONTROL0_ReadRFRank_OFF              (22)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL0_ReadRFRank_WID              ( 2)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL0_ReadRFRank_MSK              (0x00C00000)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL0_ReadRFRank_MIN              (0)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL0_ReadRFRank_MAX              (3) // 0x00000003
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL0_ReadRFRank_DEF              (0x00000000)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL0_ReadRFRank_HSH              (0x02161080)

  #define DDRDATA8CH0_CR_DDRCRDATACONTROL0_ForceOdtOn_OFF              (24)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL0_ForceOdtOn_WID              ( 1)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL0_ForceOdtOn_MSK              (0x01000000)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL0_ForceOdtOn_MIN              (0)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL0_ForceOdtOn_MAX              (1) // 0x00000001
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL0_ForceOdtOn_DEF              (0x00000000)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL0_ForceOdtOn_HSH              (0x01181080)

  #define DDRDATA8CH0_CR_DDRCRDATACONTROL0_OdtSampOff_OFF              (25)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL0_OdtSampOff_WID              ( 1)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL0_OdtSampOff_MSK              (0x02000000)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL0_OdtSampOff_MIN              (0)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL0_OdtSampOff_MAX              (1) // 0x00000001
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL0_OdtSampOff_DEF              (0x00000000)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL0_OdtSampOff_HSH              (0x01191080)

  #define DDRDATA8CH0_CR_DDRCRDATACONTROL0_DisableOdtStatic_OFF        (26)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL0_DisableOdtStatic_WID        ( 1)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL0_DisableOdtStatic_MSK        (0x04000000)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL0_DisableOdtStatic_MIN        (0)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL0_DisableOdtStatic_MAX        (1) // 0x00000001
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL0_DisableOdtStatic_DEF        (0x00000000)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL0_DisableOdtStatic_HSH        (0x011A1080)

  #define DDRDATA8CH0_CR_DDRCRDATACONTROL0_DdrCRForceODTOn_OFF         (27)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL0_DdrCRForceODTOn_WID         ( 1)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL0_DdrCRForceODTOn_MSK         (0x08000000)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL0_DdrCRForceODTOn_MIN         (0)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL0_DdrCRForceODTOn_MAX         (1) // 0x00000001
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL0_DdrCRForceODTOn_DEF         (0x00000000)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL0_DdrCRForceODTOn_HSH         (0x011B1080)

  #define DDRDATA8CH0_CR_DDRCRDATACONTROL0_LPDDR_Mode_OFF              (28)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL0_LPDDR_Mode_WID              ( 1)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL0_LPDDR_Mode_MSK              (0x10000000)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL0_LPDDR_Mode_MIN              (0)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL0_LPDDR_Mode_MAX              (1) // 0x00000001
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL0_LPDDR_Mode_DEF              (0x00000000)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL0_LPDDR_Mode_HSH              (0x011C1080)

  #define DDRDATA8CH0_CR_DDRCRDATACONTROL0_EnReadPreamble_OFF          (29)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL0_EnReadPreamble_WID          ( 1)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL0_EnReadPreamble_MSK          (0x20000000)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL0_EnReadPreamble_MIN          (0)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL0_EnReadPreamble_MAX          (1) // 0x00000001
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL0_EnReadPreamble_DEF          (0x00000000)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL0_EnReadPreamble_HSH          (0x011D1080)

  #define DDRDATA8CH0_CR_DDRCRDATACONTROL0_OdtSampExtendEn_OFF         (30)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL0_OdtSampExtendEn_WID         ( 1)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL0_OdtSampExtendEn_MSK         (0x40000000)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL0_OdtSampExtendEn_MIN         (0)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL0_OdtSampExtendEn_MAX         (1) // 0x00000001
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL0_OdtSampExtendEn_DEF         (0x00000000)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL0_OdtSampExtendEn_HSH         (0x011E1080)

  #define DDRDATA8CH0_CR_DDRCRDATACONTROL0_EarlyRleakEn_OFF            (31)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL0_EarlyRleakEn_WID            ( 1)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL0_EarlyRleakEn_MSK            (0x80000000)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL0_EarlyRleakEn_MIN            (0)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL0_EarlyRleakEn_MAX            (1) // 0x00000001
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL0_EarlyRleakEn_DEF            (0x00000000)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL0_EarlyRleakEn_HSH            (0x011F1080)

#define DDRDATA8CH0_CR_DDRCRVREFADJUST1_REG                            (0x00001084)

  #define DDRDATA8CH0_CR_DDRCRVREFADJUST1_CAVrefCtl_OFF                ( 0)
  #define DDRDATA8CH0_CR_DDRCRVREFADJUST1_CAVrefCtl_WID                ( 7)
  #define DDRDATA8CH0_CR_DDRCRVREFADJUST1_CAVrefCtl_MSK                (0x0000007F)
  #define DDRDATA8CH0_CR_DDRCRVREFADJUST1_CAVrefCtl_MIN                (-64)
  #define DDRDATA8CH0_CR_DDRCRVREFADJUST1_CAVrefCtl_MAX                (63) // 0x0000003F
  #define DDRDATA8CH0_CR_DDRCRVREFADJUST1_CAVrefCtl_DEF                (0x00000000)
  #define DDRDATA8CH0_CR_DDRCRVREFADJUST1_CAVrefCtl_HSH                (0x87001084)

  #define DDRDATA8CH0_CR_DDRCRVREFADJUST1_Ch1VrefCtl_OFF               ( 7)
  #define DDRDATA8CH0_CR_DDRCRVREFADJUST1_Ch1VrefCtl_WID               ( 7)
  #define DDRDATA8CH0_CR_DDRCRVREFADJUST1_Ch1VrefCtl_MSK               (0x00003F80)
  #define DDRDATA8CH0_CR_DDRCRVREFADJUST1_Ch1VrefCtl_MIN               (-64)
  #define DDRDATA8CH0_CR_DDRCRVREFADJUST1_Ch1VrefCtl_MAX               (63) // 0x0000003F
  #define DDRDATA8CH0_CR_DDRCRVREFADJUST1_Ch1VrefCtl_DEF               (0x00000000)
  #define DDRDATA8CH0_CR_DDRCRVREFADJUST1_Ch1VrefCtl_HSH               (0x87071084)

  #define DDRDATA8CH0_CR_DDRCRVREFADJUST1_Ch0VrefCtl_OFF               (14)
  #define DDRDATA8CH0_CR_DDRCRVREFADJUST1_Ch0VrefCtl_WID               ( 7)
  #define DDRDATA8CH0_CR_DDRCRVREFADJUST1_Ch0VrefCtl_MSK               (0x001FC000)
  #define DDRDATA8CH0_CR_DDRCRVREFADJUST1_Ch0VrefCtl_MIN               (-64)
  #define DDRDATA8CH0_CR_DDRCRVREFADJUST1_Ch0VrefCtl_MAX               (63) // 0x0000003F
  #define DDRDATA8CH0_CR_DDRCRVREFADJUST1_Ch0VrefCtl_DEF               (0x00000000)
  #define DDRDATA8CH0_CR_DDRCRVREFADJUST1_Ch0VrefCtl_HSH               (0x870E1084)

  #define DDRDATA8CH0_CR_DDRCRVREFADJUST1_EnDimmVrefCA_OFF             (21)
  #define DDRDATA8CH0_CR_DDRCRVREFADJUST1_EnDimmVrefCA_WID             ( 1)
  #define DDRDATA8CH0_CR_DDRCRVREFADJUST1_EnDimmVrefCA_MSK             (0x00200000)
  #define DDRDATA8CH0_CR_DDRCRVREFADJUST1_EnDimmVrefCA_MIN             (0)
  #define DDRDATA8CH0_CR_DDRCRVREFADJUST1_EnDimmVrefCA_MAX             (1) // 0x00000001
  #define DDRDATA8CH0_CR_DDRCRVREFADJUST1_EnDimmVrefCA_DEF             (0x00000000)
  #define DDRDATA8CH0_CR_DDRCRVREFADJUST1_EnDimmVrefCA_HSH             (0x01151084)

  #define DDRDATA8CH0_CR_DDRCRVREFADJUST1_EnDimmVrefCh1_OFF            (22)
  #define DDRDATA8CH0_CR_DDRCRVREFADJUST1_EnDimmVrefCh1_WID            ( 1)
  #define DDRDATA8CH0_CR_DDRCRVREFADJUST1_EnDimmVrefCh1_MSK            (0x00400000)
  #define DDRDATA8CH0_CR_DDRCRVREFADJUST1_EnDimmVrefCh1_MIN            (0)
  #define DDRDATA8CH0_CR_DDRCRVREFADJUST1_EnDimmVrefCh1_MAX            (1) // 0x00000001
  #define DDRDATA8CH0_CR_DDRCRVREFADJUST1_EnDimmVrefCh1_DEF            (0x00000000)
  #define DDRDATA8CH0_CR_DDRCRVREFADJUST1_EnDimmVrefCh1_HSH            (0x01161084)

  #define DDRDATA8CH0_CR_DDRCRVREFADJUST1_EnDimmVrefCh0_OFF            (23)
  #define DDRDATA8CH0_CR_DDRCRVREFADJUST1_EnDimmVrefCh0_WID            ( 1)
  #define DDRDATA8CH0_CR_DDRCRVREFADJUST1_EnDimmVrefCh0_MSK            (0x00800000)
  #define DDRDATA8CH0_CR_DDRCRVREFADJUST1_EnDimmVrefCh0_MIN            (0)
  #define DDRDATA8CH0_CR_DDRCRVREFADJUST1_EnDimmVrefCh0_MAX            (1) // 0x00000001
  #define DDRDATA8CH0_CR_DDRCRVREFADJUST1_EnDimmVrefCh0_DEF            (0x00000000)
  #define DDRDATA8CH0_CR_DDRCRVREFADJUST1_EnDimmVrefCh0_HSH            (0x01171084)

  #define DDRDATA8CH0_CR_DDRCRVREFADJUST1_HiZTimerCtrl_OFF             (24)
  #define DDRDATA8CH0_CR_DDRCRVREFADJUST1_HiZTimerCtrl_WID             ( 2)
  #define DDRDATA8CH0_CR_DDRCRVREFADJUST1_HiZTimerCtrl_MSK             (0x03000000)
  #define DDRDATA8CH0_CR_DDRCRVREFADJUST1_HiZTimerCtrl_MIN             (0)
  #define DDRDATA8CH0_CR_DDRCRVREFADJUST1_HiZTimerCtrl_MAX             (3) // 0x00000003
  #define DDRDATA8CH0_CR_DDRCRVREFADJUST1_HiZTimerCtrl_DEF             (0x00000000)
  #define DDRDATA8CH0_CR_DDRCRVREFADJUST1_HiZTimerCtrl_HSH             (0x02181084)

  #define DDRDATA8CH0_CR_DDRCRVREFADJUST1_VccddqHiQnnnH_OFF            (26)
  #define DDRDATA8CH0_CR_DDRCRVREFADJUST1_VccddqHiQnnnH_WID            ( 1)
  #define DDRDATA8CH0_CR_DDRCRVREFADJUST1_VccddqHiQnnnH_MSK            (0x04000000)
  #define DDRDATA8CH0_CR_DDRCRVREFADJUST1_VccddqHiQnnnH_MIN            (0)
  #define DDRDATA8CH0_CR_DDRCRVREFADJUST1_VccddqHiQnnnH_MAX            (1) // 0x00000001
  #define DDRDATA8CH0_CR_DDRCRVREFADJUST1_VccddqHiQnnnH_DEF            (0x00000000)
  #define DDRDATA8CH0_CR_DDRCRVREFADJUST1_VccddqHiQnnnH_HSH            (0x011A1084)

  #define DDRDATA8CH0_CR_DDRCRVREFADJUST1_Rsvd_OFF                     (27)
  #define DDRDATA8CH0_CR_DDRCRVREFADJUST1_Rsvd_WID                     ( 2)
  #define DDRDATA8CH0_CR_DDRCRVREFADJUST1_Rsvd_MSK                     (0x18000000)
  #define DDRDATA8CH0_CR_DDRCRVREFADJUST1_Rsvd_MIN                     (0)
  #define DDRDATA8CH0_CR_DDRCRVREFADJUST1_Rsvd_MAX                     (3) // 0x00000003
  #define DDRDATA8CH0_CR_DDRCRVREFADJUST1_Rsvd_DEF                     (0x00000000)
  #define DDRDATA8CH0_CR_DDRCRVREFADJUST1_Rsvd_HSH                     (0x021B1084)

  #define DDRDATA8CH0_CR_DDRCRVREFADJUST1_caSlowBW_OFF                 (29)
  #define DDRDATA8CH0_CR_DDRCRVREFADJUST1_caSlowBW_WID                 ( 1)
  #define DDRDATA8CH0_CR_DDRCRVREFADJUST1_caSlowBW_MSK                 (0x20000000)
  #define DDRDATA8CH0_CR_DDRCRVREFADJUST1_caSlowBW_MIN                 (0)
  #define DDRDATA8CH0_CR_DDRCRVREFADJUST1_caSlowBW_MAX                 (1) // 0x00000001
  #define DDRDATA8CH0_CR_DDRCRVREFADJUST1_caSlowBW_DEF                 (0x00000000)
  #define DDRDATA8CH0_CR_DDRCRVREFADJUST1_caSlowBW_HSH                 (0x011D1084)

  #define DDRDATA8CH0_CR_DDRCRVREFADJUST1_ch0SlowBW_OFF                (30)
  #define DDRDATA8CH0_CR_DDRCRVREFADJUST1_ch0SlowBW_WID                ( 1)
  #define DDRDATA8CH0_CR_DDRCRVREFADJUST1_ch0SlowBW_MSK                (0x40000000)
  #define DDRDATA8CH0_CR_DDRCRVREFADJUST1_ch0SlowBW_MIN                (0)
  #define DDRDATA8CH0_CR_DDRCRVREFADJUST1_ch0SlowBW_MAX                (1) // 0x00000001
  #define DDRDATA8CH0_CR_DDRCRVREFADJUST1_ch0SlowBW_DEF                (0x00000000)
  #define DDRDATA8CH0_CR_DDRCRVREFADJUST1_ch0SlowBW_HSH                (0x011E1084)

  #define DDRDATA8CH0_CR_DDRCRVREFADJUST1_ch1SlowBW_OFF                (31)
  #define DDRDATA8CH0_CR_DDRCRVREFADJUST1_ch1SlowBW_WID                ( 1)
  #define DDRDATA8CH0_CR_DDRCRVREFADJUST1_ch1SlowBW_MSK                (0x80000000)
  #define DDRDATA8CH0_CR_DDRCRVREFADJUST1_ch1SlowBW_MIN                (0)
  #define DDRDATA8CH0_CR_DDRCRVREFADJUST1_ch1SlowBW_MAX                (1) // 0x00000001
  #define DDRDATA8CH0_CR_DDRCRVREFADJUST1_ch1SlowBW_DEF                (0x00000000)
  #define DDRDATA8CH0_CR_DDRCRVREFADJUST1_ch1SlowBW_HSH                (0x011F1084)

#define DDRDATA8CH0_CR_DDRCRDATACONTROL3_REG                           (0x00001088)

  #define DDRDATA8CH0_CR_DDRCRDATACONTROL3_AttackerDataBit0_OFF        ( 0)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL3_AttackerDataBit0_WID        ( 3)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL3_AttackerDataBit0_MSK        (0x00000007)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL3_AttackerDataBit0_MIN        (0)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL3_AttackerDataBit0_MAX        (7) // 0x00000007
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL3_AttackerDataBit0_DEF        (0x00000000)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL3_AttackerDataBit0_HSH        (0x03001088)

  #define DDRDATA8CH0_CR_DDRCRDATACONTROL3_AttackerDataBit1_OFF        ( 3)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL3_AttackerDataBit1_WID        ( 3)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL3_AttackerDataBit1_MSK        (0x00000038)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL3_AttackerDataBit1_MIN        (0)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL3_AttackerDataBit1_MAX        (7) // 0x00000007
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL3_AttackerDataBit1_DEF        (0x00000000)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL3_AttackerDataBit1_HSH        (0x03031088)

  #define DDRDATA8CH0_CR_DDRCRDATACONTROL3_AttackerDataBit2_OFF        ( 6)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL3_AttackerDataBit2_WID        ( 3)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL3_AttackerDataBit2_MSK        (0x000001C0)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL3_AttackerDataBit2_MIN        (0)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL3_AttackerDataBit2_MAX        (7) // 0x00000007
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL3_AttackerDataBit2_DEF        (0x00000000)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL3_AttackerDataBit2_HSH        (0x03061088)

  #define DDRDATA8CH0_CR_DDRCRDATACONTROL3_AttackerDataBit3_OFF        ( 9)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL3_AttackerDataBit3_WID        ( 3)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL3_AttackerDataBit3_MSK        (0x00000E00)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL3_AttackerDataBit3_MIN        (0)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL3_AttackerDataBit3_MAX        (7) // 0x00000007
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL3_AttackerDataBit3_DEF        (0x00000000)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL3_AttackerDataBit3_HSH        (0x03091088)

  #define DDRDATA8CH0_CR_DDRCRDATACONTROL3_AttackerDataBit4_OFF        (12)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL3_AttackerDataBit4_WID        ( 3)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL3_AttackerDataBit4_MSK        (0x00007000)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL3_AttackerDataBit4_MIN        (0)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL3_AttackerDataBit4_MAX        (7) // 0x00000007
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL3_AttackerDataBit4_DEF        (0x00000000)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL3_AttackerDataBit4_HSH        (0x030C1088)

  #define DDRDATA8CH0_CR_DDRCRDATACONTROL3_AttackerDataBit5_OFF        (15)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL3_AttackerDataBit5_WID        ( 3)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL3_AttackerDataBit5_MSK        (0x00038000)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL3_AttackerDataBit5_MIN        (0)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL3_AttackerDataBit5_MAX        (7) // 0x00000007
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL3_AttackerDataBit5_DEF        (0x00000000)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL3_AttackerDataBit5_HSH        (0x030F1088)

  #define DDRDATA8CH0_CR_DDRCRDATACONTROL3_AttackerDataBit6_OFF        (18)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL3_AttackerDataBit6_WID        ( 3)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL3_AttackerDataBit6_MSK        (0x001C0000)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL3_AttackerDataBit6_MIN        (0)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL3_AttackerDataBit6_MAX        (7) // 0x00000007
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL3_AttackerDataBit6_DEF        (0x00000000)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL3_AttackerDataBit6_HSH        (0x03121088)

  #define DDRDATA8CH0_CR_DDRCRDATACONTROL3_AttackerDataBit7_OFF        (21)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL3_AttackerDataBit7_WID        ( 3)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL3_AttackerDataBit7_MSK        (0x00E00000)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL3_AttackerDataBit7_MIN        (0)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL3_AttackerDataBit7_MAX        (7) // 0x00000007
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL3_AttackerDataBit7_DEF        (0x00000000)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL3_AttackerDataBit7_HSH        (0x03151088)

  #define DDRDATA8CH0_CR_DDRCRDATACONTROL3_CBEnAmp2_OFF                (24)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL3_CBEnAmp2_WID                ( 3)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL3_CBEnAmp2_MSK                (0x07000000)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL3_CBEnAmp2_MIN                (0)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL3_CBEnAmp2_MAX                (7) // 0x00000007
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL3_CBEnAmp2_DEF                (0x00000003)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL3_CBEnAmp2_HSH                (0x03181088)

  #define DDRDATA8CH0_CR_DDRCRDATACONTROL3_CBpEnAmp2_b_OFF             (27)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL3_CBpEnAmp2_b_WID             ( 3)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL3_CBpEnAmp2_b_MSK             (0x38000000)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL3_CBpEnAmp2_b_MIN             (0)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL3_CBpEnAmp2_b_MAX             (7) // 0x00000007
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL3_CBpEnAmp2_b_DEF             (0x00000003)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL3_CBpEnAmp2_b_HSH             (0x031B1088)

  #define DDRDATA8CH0_CR_DDRCRDATACONTROL3_CBEnAmp1_OFF                (30)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL3_CBEnAmp1_WID                ( 2)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL3_CBEnAmp1_MSK                (0xC0000000)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL3_CBEnAmp1_MIN                (0)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL3_CBEnAmp1_MAX                (3) // 0x00000003
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL3_CBEnAmp1_DEF                (0x00000001)
  #define DDRDATA8CH0_CR_DDRCRDATACONTROL3_CBEnAmp1_HSH                (0x021E1088)

#define DDRDATA8CH0_CR_DDRCRVTTGENCONTROL_REG                          (0x0000108C)

  #define DDRDATA8CH0_CR_DDRCRVTTGENCONTROL_Target_OFF                 ( 0)
  #define DDRDATA8CH0_CR_DDRCRVTTGENCONTROL_Target_WID                 ( 4)
  #define DDRDATA8CH0_CR_DDRCRVTTGENCONTROL_Target_MSK                 (0x0000000F)
  #define DDRDATA8CH0_CR_DDRCRVTTGENCONTROL_Target_MIN                 (0)
  #define DDRDATA8CH0_CR_DDRCRVTTGENCONTROL_Target_MAX                 (15) // 0x0000000F
  #define DDRDATA8CH0_CR_DDRCRVTTGENCONTROL_Target_DEF                 (0x00000000)
  #define DDRDATA8CH0_CR_DDRCRVTTGENCONTROL_Target_HSH                 (0x0400108C)

  #define DDRDATA8CH0_CR_DDRCRVTTGENCONTROL_Panic_OFF                  ( 4)
  #define DDRDATA8CH0_CR_DDRCRVTTGENCONTROL_Panic_WID                  ( 5)
  #define DDRDATA8CH0_CR_DDRCRVTTGENCONTROL_Panic_MSK                  (0x000001F0)
  #define DDRDATA8CH0_CR_DDRCRVTTGENCONTROL_Panic_MIN                  (0)
  #define DDRDATA8CH0_CR_DDRCRVTTGENCONTROL_Panic_MAX                  (31) // 0x0000001F
  #define DDRDATA8CH0_CR_DDRCRVTTGENCONTROL_Panic_DEF                  (0x00000010)
  #define DDRDATA8CH0_CR_DDRCRVTTGENCONTROL_Panic_HSH                  (0x0504108C)

  #define DDRDATA8CH0_CR_DDRCRVTTGENCONTROL_DisPanicDrv_OFF            ( 9)
  #define DDRDATA8CH0_CR_DDRCRVTTGENCONTROL_DisPanicDrv_WID            ( 2)
  #define DDRDATA8CH0_CR_DDRCRVTTGENCONTROL_DisPanicDrv_MSK            (0x00000600)
  #define DDRDATA8CH0_CR_DDRCRVTTGENCONTROL_DisPanicDrv_MIN            (0)
  #define DDRDATA8CH0_CR_DDRCRVTTGENCONTROL_DisPanicDrv_MAX            (3) // 0x00000003
  #define DDRDATA8CH0_CR_DDRCRVTTGENCONTROL_DisPanicDrv_DEF            (0x00000000)
  #define DDRDATA8CH0_CR_DDRCRVTTGENCONTROL_DisPanicDrv_HSH            (0x0209108C)

  #define DDRDATA8CH0_CR_DDRCRVTTGENCONTROL_DisSensorPwrDn_OFF         (11)
  #define DDRDATA8CH0_CR_DDRCRVTTGENCONTROL_DisSensorPwrDn_WID         ( 1)
  #define DDRDATA8CH0_CR_DDRCRVTTGENCONTROL_DisSensorPwrDn_MSK         (0x00000800)
  #define DDRDATA8CH0_CR_DDRCRVTTGENCONTROL_DisSensorPwrDn_MIN         (0)
  #define DDRDATA8CH0_CR_DDRCRVTTGENCONTROL_DisSensorPwrDn_MAX         (1) // 0x00000001
  #define DDRDATA8CH0_CR_DDRCRVTTGENCONTROL_DisSensorPwrDn_DEF         (0x00000000)
  #define DDRDATA8CH0_CR_DDRCRVTTGENCONTROL_DisSensorPwrDn_HSH         (0x010B108C)

  #define DDRDATA8CH0_CR_DDRCRVTTGENCONTROL_OfstOvrdEn_OFF             (12)
  #define DDRDATA8CH0_CR_DDRCRVTTGENCONTROL_OfstOvrdEn_WID             ( 1)
  #define DDRDATA8CH0_CR_DDRCRVTTGENCONTROL_OfstOvrdEn_MSK             (0x00001000)
  #define DDRDATA8CH0_CR_DDRCRVTTGENCONTROL_OfstOvrdEn_MIN             (0)
  #define DDRDATA8CH0_CR_DDRCRVTTGENCONTROL_OfstOvrdEn_MAX             (1) // 0x00000001
  #define DDRDATA8CH0_CR_DDRCRVTTGENCONTROL_OfstOvrdEn_DEF             (0x00000000)
  #define DDRDATA8CH0_CR_DDRCRVTTGENCONTROL_OfstOvrdEn_HSH             (0x010C108C)

  #define DDRDATA8CH0_CR_DDRCRVTTGENCONTROL_ViewOfstsel_OFF            (13)
  #define DDRDATA8CH0_CR_DDRCRVTTGENCONTROL_ViewOfstsel_WID            ( 3)
  #define DDRDATA8CH0_CR_DDRCRVTTGENCONTROL_ViewOfstsel_MSK            (0x0000E000)
  #define DDRDATA8CH0_CR_DDRCRVTTGENCONTROL_ViewOfstsel_MIN            (0)
  #define DDRDATA8CH0_CR_DDRCRVTTGENCONTROL_ViewOfstsel_MAX            (7) // 0x00000007
  #define DDRDATA8CH0_CR_DDRCRVTTGENCONTROL_ViewOfstsel_DEF            (0x00000000)
  #define DDRDATA8CH0_CR_DDRCRVTTGENCONTROL_ViewOfstsel_HSH            (0x030D108C)

  #define DDRDATA8CH0_CR_DDRCRVTTGENCONTROL_EnVttCompforVsshi_OFF      (16)
  #define DDRDATA8CH0_CR_DDRCRVTTGENCONTROL_EnVttCompforVsshi_WID      ( 1)
  #define DDRDATA8CH0_CR_DDRCRVTTGENCONTROL_EnVttCompforVsshi_MSK      (0x00010000)
  #define DDRDATA8CH0_CR_DDRCRVTTGENCONTROL_EnVttCompforVsshi_MIN      (0)
  #define DDRDATA8CH0_CR_DDRCRVTTGENCONTROL_EnVttCompforVsshi_MAX      (1) // 0x00000001
  #define DDRDATA8CH0_CR_DDRCRVTTGENCONTROL_EnVttCompforVsshi_DEF      (0x00000000)
  #define DDRDATA8CH0_CR_DDRCRVTTGENCONTROL_EnVttCompforVsshi_HSH      (0x0110108C)

  #define DDRDATA8CH0_CR_DDRCRVTTGENCONTROL_Spares_OFF                 (17)
  #define DDRDATA8CH0_CR_DDRCRVTTGENCONTROL_Spares_WID                 ( 8)
  #define DDRDATA8CH0_CR_DDRCRVTTGENCONTROL_Spares_MSK                 (0x01FE0000)
  #define DDRDATA8CH0_CR_DDRCRVTTGENCONTROL_Spares_MIN                 (0)
  #define DDRDATA8CH0_CR_DDRCRVTTGENCONTROL_Spares_MAX                 (255) // 0x000000FF
  #define DDRDATA8CH0_CR_DDRCRVTTGENCONTROL_Spares_DEF                 (0x00000000)
  #define DDRDATA8CH0_CR_DDRCRVTTGENCONTROL_Spares_HSH                 (0x0811108C)

  #define DDRDATA8CH0_CR_DDRCRVTTGENCONTROL_Disable2Vt_OFF             (25)
  #define DDRDATA8CH0_CR_DDRCRVTTGENCONTROL_Disable2Vt_WID             ( 1)
  #define DDRDATA8CH0_CR_DDRCRVTTGENCONTROL_Disable2Vt_MSK             (0x02000000)
  #define DDRDATA8CH0_CR_DDRCRVTTGENCONTROL_Disable2Vt_MIN             (0)
  #define DDRDATA8CH0_CR_DDRCRVTTGENCONTROL_Disable2Vt_MAX             (1) // 0x00000001
  #define DDRDATA8CH0_CR_DDRCRVTTGENCONTROL_Disable2Vt_DEF             (0x00000000)
  #define DDRDATA8CH0_CR_DDRCRVTTGENCONTROL_Disable2Vt_HSH             (0x0119108C)

  #define DDRDATA8CH0_CR_DDRCRVTTGENCONTROL_OfstOvrdOrView_OFF         (26)
  #define DDRDATA8CH0_CR_DDRCRVTTGENCONTROL_OfstOvrdOrView_WID         ( 6)
  #define DDRDATA8CH0_CR_DDRCRVTTGENCONTROL_OfstOvrdOrView_MSK         (0xFC000000)
  #define DDRDATA8CH0_CR_DDRCRVTTGENCONTROL_OfstOvrdOrView_MIN         (0)
  #define DDRDATA8CH0_CR_DDRCRVTTGENCONTROL_OfstOvrdOrView_MAX         (63) // 0x0000003F
  #define DDRDATA8CH0_CR_DDRCRVTTGENCONTROL_OfstOvrdOrView_DEF         (0x00000000)
  #define DDRDATA8CH0_CR_DDRCRVTTGENCONTROL_OfstOvrdOrView_HSH         (0x061A108C)

#define DDRDATA8CH1_CR_RXTRAINRANK0_REG                                (0x00001100)

  #define DDRDATA8CH1_CR_RXTRAINRANK0_RxRcvEnPi_OFF                    ( 0)
  #define DDRDATA8CH1_CR_RXTRAINRANK0_RxRcvEnPi_WID                    ( 9)
  #define DDRDATA8CH1_CR_RXTRAINRANK0_RxRcvEnPi_MSK                    (0x000001FF)
  #define DDRDATA8CH1_CR_RXTRAINRANK0_RxRcvEnPi_MIN                    (0)
  #define DDRDATA8CH1_CR_RXTRAINRANK0_RxRcvEnPi_MAX                    (511) // 0x000001FF
  #define DDRDATA8CH1_CR_RXTRAINRANK0_RxRcvEnPi_DEF                    (0x00000000)
  #define DDRDATA8CH1_CR_RXTRAINRANK0_RxRcvEnPi_HSH                    (0x09001100)

  #define DDRDATA8CH1_CR_RXTRAINRANK0_RxDqsPPi_OFF                     ( 9)
  #define DDRDATA8CH1_CR_RXTRAINRANK0_RxDqsPPi_WID                     ( 6)
  #define DDRDATA8CH1_CR_RXTRAINRANK0_RxDqsPPi_MSK                     (0x00007E00)
  #define DDRDATA8CH1_CR_RXTRAINRANK0_RxDqsPPi_MIN                     (0)
  #define DDRDATA8CH1_CR_RXTRAINRANK0_RxDqsPPi_MAX                     (63) // 0x0000003F
  #define DDRDATA8CH1_CR_RXTRAINRANK0_RxDqsPPi_DEF                     (0x00000000)
  #define DDRDATA8CH1_CR_RXTRAINRANK0_RxDqsPPi_HSH                     (0x06091100)

  #define DDRDATA8CH1_CR_RXTRAINRANK0_RxEq_OFF                         (15)
  #define DDRDATA8CH1_CR_RXTRAINRANK0_RxEq_WID                         ( 5)
  #define DDRDATA8CH1_CR_RXTRAINRANK0_RxEq_MSK                         (0x000F8000)
  #define DDRDATA8CH1_CR_RXTRAINRANK0_RxEq_MIN                         (0)
  #define DDRDATA8CH1_CR_RXTRAINRANK0_RxEq_MAX                         (31) // 0x0000001F
  #define DDRDATA8CH1_CR_RXTRAINRANK0_RxEq_DEF                         (0x00000000)
  #define DDRDATA8CH1_CR_RXTRAINRANK0_RxEq_HSH                         (0x050F1100)

  #define DDRDATA8CH1_CR_RXTRAINRANK0_RxDqsNPi_OFF                     (20)
  #define DDRDATA8CH1_CR_RXTRAINRANK0_RxDqsNPi_WID                     ( 6)
  #define DDRDATA8CH1_CR_RXTRAINRANK0_RxDqsNPi_MSK                     (0x03F00000)
  #define DDRDATA8CH1_CR_RXTRAINRANK0_RxDqsNPi_MIN                     (0)
  #define DDRDATA8CH1_CR_RXTRAINRANK0_RxDqsNPi_MAX                     (63) // 0x0000003F
  #define DDRDATA8CH1_CR_RXTRAINRANK0_RxDqsNPi_DEF                     (0x00000000)
  #define DDRDATA8CH1_CR_RXTRAINRANK0_RxDqsNPi_HSH                     (0x06141100)

  #define DDRDATA8CH1_CR_RXTRAINRANK0_RxVref_OFF                       (26)
  #define DDRDATA8CH1_CR_RXTRAINRANK0_RxVref_WID                       ( 6)
  #define DDRDATA8CH1_CR_RXTRAINRANK0_RxVref_MSK                       (0xFC000000)
  #define DDRDATA8CH1_CR_RXTRAINRANK0_RxVref_MIN                       (-32)
  #define DDRDATA8CH1_CR_RXTRAINRANK0_RxVref_MAX                       (31) // 0x0000001F
  #define DDRDATA8CH1_CR_RXTRAINRANK0_RxVref_DEF                       (0x00000000)
  #define DDRDATA8CH1_CR_RXTRAINRANK0_RxVref_HSH                       (0x861A1100)

#define DDRDATA8CH1_CR_RXTRAINRANK1_REG                                (0x00001104)

  #define DDRDATA8CH1_CR_RXTRAINRANK1_RxRcvEnPi_OFF                    ( 0)
  #define DDRDATA8CH1_CR_RXTRAINRANK1_RxRcvEnPi_WID                    ( 9)
  #define DDRDATA8CH1_CR_RXTRAINRANK1_RxRcvEnPi_MSK                    (0x000001FF)
  #define DDRDATA8CH1_CR_RXTRAINRANK1_RxRcvEnPi_MIN                    (0)
  #define DDRDATA8CH1_CR_RXTRAINRANK1_RxRcvEnPi_MAX                    (511) // 0x000001FF
  #define DDRDATA8CH1_CR_RXTRAINRANK1_RxRcvEnPi_DEF                    (0x00000000)
  #define DDRDATA8CH1_CR_RXTRAINRANK1_RxRcvEnPi_HSH                    (0x09001104)

  #define DDRDATA8CH1_CR_RXTRAINRANK1_RxDqsPPi_OFF                     ( 9)
  #define DDRDATA8CH1_CR_RXTRAINRANK1_RxDqsPPi_WID                     ( 6)
  #define DDRDATA8CH1_CR_RXTRAINRANK1_RxDqsPPi_MSK                     (0x00007E00)
  #define DDRDATA8CH1_CR_RXTRAINRANK1_RxDqsPPi_MIN                     (0)
  #define DDRDATA8CH1_CR_RXTRAINRANK1_RxDqsPPi_MAX                     (63) // 0x0000003F
  #define DDRDATA8CH1_CR_RXTRAINRANK1_RxDqsPPi_DEF                     (0x00000000)
  #define DDRDATA8CH1_CR_RXTRAINRANK1_RxDqsPPi_HSH                     (0x06091104)

  #define DDRDATA8CH1_CR_RXTRAINRANK1_RxEq_OFF                         (15)
  #define DDRDATA8CH1_CR_RXTRAINRANK1_RxEq_WID                         ( 5)
  #define DDRDATA8CH1_CR_RXTRAINRANK1_RxEq_MSK                         (0x000F8000)
  #define DDRDATA8CH1_CR_RXTRAINRANK1_RxEq_MIN                         (0)
  #define DDRDATA8CH1_CR_RXTRAINRANK1_RxEq_MAX                         (31) // 0x0000001F
  #define DDRDATA8CH1_CR_RXTRAINRANK1_RxEq_DEF                         (0x00000000)
  #define DDRDATA8CH1_CR_RXTRAINRANK1_RxEq_HSH                         (0x050F1104)

  #define DDRDATA8CH1_CR_RXTRAINRANK1_RxDqsNPi_OFF                     (20)
  #define DDRDATA8CH1_CR_RXTRAINRANK1_RxDqsNPi_WID                     ( 6)
  #define DDRDATA8CH1_CR_RXTRAINRANK1_RxDqsNPi_MSK                     (0x03F00000)
  #define DDRDATA8CH1_CR_RXTRAINRANK1_RxDqsNPi_MIN                     (0)
  #define DDRDATA8CH1_CR_RXTRAINRANK1_RxDqsNPi_MAX                     (63) // 0x0000003F
  #define DDRDATA8CH1_CR_RXTRAINRANK1_RxDqsNPi_DEF                     (0x00000000)
  #define DDRDATA8CH1_CR_RXTRAINRANK1_RxDqsNPi_HSH                     (0x06141104)

  #define DDRDATA8CH1_CR_RXTRAINRANK1_RxVref_OFF                       (26)
  #define DDRDATA8CH1_CR_RXTRAINRANK1_RxVref_WID                       ( 6)
  #define DDRDATA8CH1_CR_RXTRAINRANK1_RxVref_MSK                       (0xFC000000)
  #define DDRDATA8CH1_CR_RXTRAINRANK1_RxVref_MIN                       (-32)
  #define DDRDATA8CH1_CR_RXTRAINRANK1_RxVref_MAX                       (31) // 0x0000001F
  #define DDRDATA8CH1_CR_RXTRAINRANK1_RxVref_DEF                       (0x00000000)
  #define DDRDATA8CH1_CR_RXTRAINRANK1_RxVref_HSH                       (0x861A1104)

#define DDRDATA8CH1_CR_RXTRAINRANK2_REG                                (0x00001108)

  #define DDRDATA8CH1_CR_RXTRAINRANK2_RxRcvEnPi_OFF                    ( 0)
  #define DDRDATA8CH1_CR_RXTRAINRANK2_RxRcvEnPi_WID                    ( 9)
  #define DDRDATA8CH1_CR_RXTRAINRANK2_RxRcvEnPi_MSK                    (0x000001FF)
  #define DDRDATA8CH1_CR_RXTRAINRANK2_RxRcvEnPi_MIN                    (0)
  #define DDRDATA8CH1_CR_RXTRAINRANK2_RxRcvEnPi_MAX                    (511) // 0x000001FF
  #define DDRDATA8CH1_CR_RXTRAINRANK2_RxRcvEnPi_DEF                    (0x00000000)
  #define DDRDATA8CH1_CR_RXTRAINRANK2_RxRcvEnPi_HSH                    (0x09001108)

  #define DDRDATA8CH1_CR_RXTRAINRANK2_RxDqsPPi_OFF                     ( 9)
  #define DDRDATA8CH1_CR_RXTRAINRANK2_RxDqsPPi_WID                     ( 6)
  #define DDRDATA8CH1_CR_RXTRAINRANK2_RxDqsPPi_MSK                     (0x00007E00)
  #define DDRDATA8CH1_CR_RXTRAINRANK2_RxDqsPPi_MIN                     (0)
  #define DDRDATA8CH1_CR_RXTRAINRANK2_RxDqsPPi_MAX                     (63) // 0x0000003F
  #define DDRDATA8CH1_CR_RXTRAINRANK2_RxDqsPPi_DEF                     (0x00000000)
  #define DDRDATA8CH1_CR_RXTRAINRANK2_RxDqsPPi_HSH                     (0x06091108)

  #define DDRDATA8CH1_CR_RXTRAINRANK2_RxEq_OFF                         (15)
  #define DDRDATA8CH1_CR_RXTRAINRANK2_RxEq_WID                         ( 5)
  #define DDRDATA8CH1_CR_RXTRAINRANK2_RxEq_MSK                         (0x000F8000)
  #define DDRDATA8CH1_CR_RXTRAINRANK2_RxEq_MIN                         (0)
  #define DDRDATA8CH1_CR_RXTRAINRANK2_RxEq_MAX                         (31) // 0x0000001F
  #define DDRDATA8CH1_CR_RXTRAINRANK2_RxEq_DEF                         (0x00000000)
  #define DDRDATA8CH1_CR_RXTRAINRANK2_RxEq_HSH                         (0x050F1108)

  #define DDRDATA8CH1_CR_RXTRAINRANK2_RxDqsNPi_OFF                     (20)
  #define DDRDATA8CH1_CR_RXTRAINRANK2_RxDqsNPi_WID                     ( 6)
  #define DDRDATA8CH1_CR_RXTRAINRANK2_RxDqsNPi_MSK                     (0x03F00000)
  #define DDRDATA8CH1_CR_RXTRAINRANK2_RxDqsNPi_MIN                     (0)
  #define DDRDATA8CH1_CR_RXTRAINRANK2_RxDqsNPi_MAX                     (63) // 0x0000003F
  #define DDRDATA8CH1_CR_RXTRAINRANK2_RxDqsNPi_DEF                     (0x00000000)
  #define DDRDATA8CH1_CR_RXTRAINRANK2_RxDqsNPi_HSH                     (0x06141108)

  #define DDRDATA8CH1_CR_RXTRAINRANK2_RxVref_OFF                       (26)
  #define DDRDATA8CH1_CR_RXTRAINRANK2_RxVref_WID                       ( 6)
  #define DDRDATA8CH1_CR_RXTRAINRANK2_RxVref_MSK                       (0xFC000000)
  #define DDRDATA8CH1_CR_RXTRAINRANK2_RxVref_MIN                       (-32)
  #define DDRDATA8CH1_CR_RXTRAINRANK2_RxVref_MAX                       (31) // 0x0000001F
  #define DDRDATA8CH1_CR_RXTRAINRANK2_RxVref_DEF                       (0x00000000)
  #define DDRDATA8CH1_CR_RXTRAINRANK2_RxVref_HSH                       (0x861A1108)

#define DDRDATA8CH1_CR_RXTRAINRANK3_REG                                (0x0000110C)

  #define DDRDATA8CH1_CR_RXTRAINRANK3_RxRcvEnPi_OFF                    ( 0)
  #define DDRDATA8CH1_CR_RXTRAINRANK3_RxRcvEnPi_WID                    ( 9)
  #define DDRDATA8CH1_CR_RXTRAINRANK3_RxRcvEnPi_MSK                    (0x000001FF)
  #define DDRDATA8CH1_CR_RXTRAINRANK3_RxRcvEnPi_MIN                    (0)
  #define DDRDATA8CH1_CR_RXTRAINRANK3_RxRcvEnPi_MAX                    (511) // 0x000001FF
  #define DDRDATA8CH1_CR_RXTRAINRANK3_RxRcvEnPi_DEF                    (0x00000000)
  #define DDRDATA8CH1_CR_RXTRAINRANK3_RxRcvEnPi_HSH                    (0x0900110C)

  #define DDRDATA8CH1_CR_RXTRAINRANK3_RxDqsPPi_OFF                     ( 9)
  #define DDRDATA8CH1_CR_RXTRAINRANK3_RxDqsPPi_WID                     ( 6)
  #define DDRDATA8CH1_CR_RXTRAINRANK3_RxDqsPPi_MSK                     (0x00007E00)
  #define DDRDATA8CH1_CR_RXTRAINRANK3_RxDqsPPi_MIN                     (0)
  #define DDRDATA8CH1_CR_RXTRAINRANK3_RxDqsPPi_MAX                     (63) // 0x0000003F
  #define DDRDATA8CH1_CR_RXTRAINRANK3_RxDqsPPi_DEF                     (0x00000000)
  #define DDRDATA8CH1_CR_RXTRAINRANK3_RxDqsPPi_HSH                     (0x0609110C)

  #define DDRDATA8CH1_CR_RXTRAINRANK3_RxEq_OFF                         (15)
  #define DDRDATA8CH1_CR_RXTRAINRANK3_RxEq_WID                         ( 5)
  #define DDRDATA8CH1_CR_RXTRAINRANK3_RxEq_MSK                         (0x000F8000)
  #define DDRDATA8CH1_CR_RXTRAINRANK3_RxEq_MIN                         (0)
  #define DDRDATA8CH1_CR_RXTRAINRANK3_RxEq_MAX                         (31) // 0x0000001F
  #define DDRDATA8CH1_CR_RXTRAINRANK3_RxEq_DEF                         (0x00000000)
  #define DDRDATA8CH1_CR_RXTRAINRANK3_RxEq_HSH                         (0x050F110C)

  #define DDRDATA8CH1_CR_RXTRAINRANK3_RxDqsNPi_OFF                     (20)
  #define DDRDATA8CH1_CR_RXTRAINRANK3_RxDqsNPi_WID                     ( 6)
  #define DDRDATA8CH1_CR_RXTRAINRANK3_RxDqsNPi_MSK                     (0x03F00000)
  #define DDRDATA8CH1_CR_RXTRAINRANK3_RxDqsNPi_MIN                     (0)
  #define DDRDATA8CH1_CR_RXTRAINRANK3_RxDqsNPi_MAX                     (63) // 0x0000003F
  #define DDRDATA8CH1_CR_RXTRAINRANK3_RxDqsNPi_DEF                     (0x00000000)
  #define DDRDATA8CH1_CR_RXTRAINRANK3_RxDqsNPi_HSH                     (0x0614110C)

  #define DDRDATA8CH1_CR_RXTRAINRANK3_RxVref_OFF                       (26)
  #define DDRDATA8CH1_CR_RXTRAINRANK3_RxVref_WID                       ( 6)
  #define DDRDATA8CH1_CR_RXTRAINRANK3_RxVref_MSK                       (0xFC000000)
  #define DDRDATA8CH1_CR_RXTRAINRANK3_RxVref_MIN                       (-32)
  #define DDRDATA8CH1_CR_RXTRAINRANK3_RxVref_MAX                       (31) // 0x0000001F
  #define DDRDATA8CH1_CR_RXTRAINRANK3_RxVref_DEF                       (0x00000000)
  #define DDRDATA8CH1_CR_RXTRAINRANK3_RxVref_HSH                       (0x861A110C)

#define DDRDATA8CH1_CR_RXPERBITRANK0_REG                               (0x00001110)

  #define DDRDATA8CH1_CR_RXPERBITRANK0_Lane0_OFF                       ( 0)
  #define DDRDATA8CH1_CR_RXPERBITRANK0_Lane0_WID                       ( 4)
  #define DDRDATA8CH1_CR_RXPERBITRANK0_Lane0_MSK                       (0x0000000F)
  #define DDRDATA8CH1_CR_RXPERBITRANK0_Lane0_MIN                       (0)
  #define DDRDATA8CH1_CR_RXPERBITRANK0_Lane0_MAX                       (15) // 0x0000000F
  #define DDRDATA8CH1_CR_RXPERBITRANK0_Lane0_DEF                       (0x00000000)
  #define DDRDATA8CH1_CR_RXPERBITRANK0_Lane0_HSH                       (0x04001110)

  #define DDRDATA8CH1_CR_RXPERBITRANK0_Lane1_OFF                       ( 4)
  #define DDRDATA8CH1_CR_RXPERBITRANK0_Lane1_WID                       ( 4)
  #define DDRDATA8CH1_CR_RXPERBITRANK0_Lane1_MSK                       (0x000000F0)
  #define DDRDATA8CH1_CR_RXPERBITRANK0_Lane1_MIN                       (0)
  #define DDRDATA8CH1_CR_RXPERBITRANK0_Lane1_MAX                       (15) // 0x0000000F
  #define DDRDATA8CH1_CR_RXPERBITRANK0_Lane1_DEF                       (0x00000000)
  #define DDRDATA8CH1_CR_RXPERBITRANK0_Lane1_HSH                       (0x04041110)

  #define DDRDATA8CH1_CR_RXPERBITRANK0_Lane2_OFF                       ( 8)
  #define DDRDATA8CH1_CR_RXPERBITRANK0_Lane2_WID                       ( 4)
  #define DDRDATA8CH1_CR_RXPERBITRANK0_Lane2_MSK                       (0x00000F00)
  #define DDRDATA8CH1_CR_RXPERBITRANK0_Lane2_MIN                       (0)
  #define DDRDATA8CH1_CR_RXPERBITRANK0_Lane2_MAX                       (15) // 0x0000000F
  #define DDRDATA8CH1_CR_RXPERBITRANK0_Lane2_DEF                       (0x00000000)
  #define DDRDATA8CH1_CR_RXPERBITRANK0_Lane2_HSH                       (0x04081110)

  #define DDRDATA8CH1_CR_RXPERBITRANK0_Lane3_OFF                       (12)
  #define DDRDATA8CH1_CR_RXPERBITRANK0_Lane3_WID                       ( 4)
  #define DDRDATA8CH1_CR_RXPERBITRANK0_Lane3_MSK                       (0x0000F000)
  #define DDRDATA8CH1_CR_RXPERBITRANK0_Lane3_MIN                       (0)
  #define DDRDATA8CH1_CR_RXPERBITRANK0_Lane3_MAX                       (15) // 0x0000000F
  #define DDRDATA8CH1_CR_RXPERBITRANK0_Lane3_DEF                       (0x00000000)
  #define DDRDATA8CH1_CR_RXPERBITRANK0_Lane3_HSH                       (0x040C1110)

  #define DDRDATA8CH1_CR_RXPERBITRANK0_Lane4_OFF                       (16)
  #define DDRDATA8CH1_CR_RXPERBITRANK0_Lane4_WID                       ( 4)
  #define DDRDATA8CH1_CR_RXPERBITRANK0_Lane4_MSK                       (0x000F0000)
  #define DDRDATA8CH1_CR_RXPERBITRANK0_Lane4_MIN                       (0)
  #define DDRDATA8CH1_CR_RXPERBITRANK0_Lane4_MAX                       (15) // 0x0000000F
  #define DDRDATA8CH1_CR_RXPERBITRANK0_Lane4_DEF                       (0x00000000)
  #define DDRDATA8CH1_CR_RXPERBITRANK0_Lane4_HSH                       (0x04101110)

  #define DDRDATA8CH1_CR_RXPERBITRANK0_Lane5_OFF                       (20)
  #define DDRDATA8CH1_CR_RXPERBITRANK0_Lane5_WID                       ( 4)
  #define DDRDATA8CH1_CR_RXPERBITRANK0_Lane5_MSK                       (0x00F00000)
  #define DDRDATA8CH1_CR_RXPERBITRANK0_Lane5_MIN                       (0)
  #define DDRDATA8CH1_CR_RXPERBITRANK0_Lane5_MAX                       (15) // 0x0000000F
  #define DDRDATA8CH1_CR_RXPERBITRANK0_Lane5_DEF                       (0x00000000)
  #define DDRDATA8CH1_CR_RXPERBITRANK0_Lane5_HSH                       (0x04141110)

  #define DDRDATA8CH1_CR_RXPERBITRANK0_Lane6_OFF                       (24)
  #define DDRDATA8CH1_CR_RXPERBITRANK0_Lane6_WID                       ( 4)
  #define DDRDATA8CH1_CR_RXPERBITRANK0_Lane6_MSK                       (0x0F000000)
  #define DDRDATA8CH1_CR_RXPERBITRANK0_Lane6_MIN                       (0)
  #define DDRDATA8CH1_CR_RXPERBITRANK0_Lane6_MAX                       (15) // 0x0000000F
  #define DDRDATA8CH1_CR_RXPERBITRANK0_Lane6_DEF                       (0x00000000)
  #define DDRDATA8CH1_CR_RXPERBITRANK0_Lane6_HSH                       (0x04181110)

  #define DDRDATA8CH1_CR_RXPERBITRANK0_Lane7_OFF                       (28)
  #define DDRDATA8CH1_CR_RXPERBITRANK0_Lane7_WID                       ( 4)
  #define DDRDATA8CH1_CR_RXPERBITRANK0_Lane7_MSK                       (0xF0000000)
  #define DDRDATA8CH1_CR_RXPERBITRANK0_Lane7_MIN                       (0)
  #define DDRDATA8CH1_CR_RXPERBITRANK0_Lane7_MAX                       (15) // 0x0000000F
  #define DDRDATA8CH1_CR_RXPERBITRANK0_Lane7_DEF                       (0x00000000)
  #define DDRDATA8CH1_CR_RXPERBITRANK0_Lane7_HSH                       (0x041C1110)

#define DDRDATA8CH1_CR_RXPERBITRANK1_REG                               (0x00001114)

  #define DDRDATA8CH1_CR_RXPERBITRANK1_Lane0_OFF                       ( 0)
  #define DDRDATA8CH1_CR_RXPERBITRANK1_Lane0_WID                       ( 4)
  #define DDRDATA8CH1_CR_RXPERBITRANK1_Lane0_MSK                       (0x0000000F)
  #define DDRDATA8CH1_CR_RXPERBITRANK1_Lane0_MIN                       (0)
  #define DDRDATA8CH1_CR_RXPERBITRANK1_Lane0_MAX                       (15) // 0x0000000F
  #define DDRDATA8CH1_CR_RXPERBITRANK1_Lane0_DEF                       (0x00000000)
  #define DDRDATA8CH1_CR_RXPERBITRANK1_Lane0_HSH                       (0x04001114)

  #define DDRDATA8CH1_CR_RXPERBITRANK1_Lane1_OFF                       ( 4)
  #define DDRDATA8CH1_CR_RXPERBITRANK1_Lane1_WID                       ( 4)
  #define DDRDATA8CH1_CR_RXPERBITRANK1_Lane1_MSK                       (0x000000F0)
  #define DDRDATA8CH1_CR_RXPERBITRANK1_Lane1_MIN                       (0)
  #define DDRDATA8CH1_CR_RXPERBITRANK1_Lane1_MAX                       (15) // 0x0000000F
  #define DDRDATA8CH1_CR_RXPERBITRANK1_Lane1_DEF                       (0x00000000)
  #define DDRDATA8CH1_CR_RXPERBITRANK1_Lane1_HSH                       (0x04041114)

  #define DDRDATA8CH1_CR_RXPERBITRANK1_Lane2_OFF                       ( 8)
  #define DDRDATA8CH1_CR_RXPERBITRANK1_Lane2_WID                       ( 4)
  #define DDRDATA8CH1_CR_RXPERBITRANK1_Lane2_MSK                       (0x00000F00)
  #define DDRDATA8CH1_CR_RXPERBITRANK1_Lane2_MIN                       (0)
  #define DDRDATA8CH1_CR_RXPERBITRANK1_Lane2_MAX                       (15) // 0x0000000F
  #define DDRDATA8CH1_CR_RXPERBITRANK1_Lane2_DEF                       (0x00000000)
  #define DDRDATA8CH1_CR_RXPERBITRANK1_Lane2_HSH                       (0x04081114)

  #define DDRDATA8CH1_CR_RXPERBITRANK1_Lane3_OFF                       (12)
  #define DDRDATA8CH1_CR_RXPERBITRANK1_Lane3_WID                       ( 4)
  #define DDRDATA8CH1_CR_RXPERBITRANK1_Lane3_MSK                       (0x0000F000)
  #define DDRDATA8CH1_CR_RXPERBITRANK1_Lane3_MIN                       (0)
  #define DDRDATA8CH1_CR_RXPERBITRANK1_Lane3_MAX                       (15) // 0x0000000F
  #define DDRDATA8CH1_CR_RXPERBITRANK1_Lane3_DEF                       (0x00000000)
  #define DDRDATA8CH1_CR_RXPERBITRANK1_Lane3_HSH                       (0x040C1114)

  #define DDRDATA8CH1_CR_RXPERBITRANK1_Lane4_OFF                       (16)
  #define DDRDATA8CH1_CR_RXPERBITRANK1_Lane4_WID                       ( 4)
  #define DDRDATA8CH1_CR_RXPERBITRANK1_Lane4_MSK                       (0x000F0000)
  #define DDRDATA8CH1_CR_RXPERBITRANK1_Lane4_MIN                       (0)
  #define DDRDATA8CH1_CR_RXPERBITRANK1_Lane4_MAX                       (15) // 0x0000000F
  #define DDRDATA8CH1_CR_RXPERBITRANK1_Lane4_DEF                       (0x00000000)
  #define DDRDATA8CH1_CR_RXPERBITRANK1_Lane4_HSH                       (0x04101114)

  #define DDRDATA8CH1_CR_RXPERBITRANK1_Lane5_OFF                       (20)
  #define DDRDATA8CH1_CR_RXPERBITRANK1_Lane5_WID                       ( 4)
  #define DDRDATA8CH1_CR_RXPERBITRANK1_Lane5_MSK                       (0x00F00000)
  #define DDRDATA8CH1_CR_RXPERBITRANK1_Lane5_MIN                       (0)
  #define DDRDATA8CH1_CR_RXPERBITRANK1_Lane5_MAX                       (15) // 0x0000000F
  #define DDRDATA8CH1_CR_RXPERBITRANK1_Lane5_DEF                       (0x00000000)
  #define DDRDATA8CH1_CR_RXPERBITRANK1_Lane5_HSH                       (0x04141114)

  #define DDRDATA8CH1_CR_RXPERBITRANK1_Lane6_OFF                       (24)
  #define DDRDATA8CH1_CR_RXPERBITRANK1_Lane6_WID                       ( 4)
  #define DDRDATA8CH1_CR_RXPERBITRANK1_Lane6_MSK                       (0x0F000000)
  #define DDRDATA8CH1_CR_RXPERBITRANK1_Lane6_MIN                       (0)
  #define DDRDATA8CH1_CR_RXPERBITRANK1_Lane6_MAX                       (15) // 0x0000000F
  #define DDRDATA8CH1_CR_RXPERBITRANK1_Lane6_DEF                       (0x00000000)
  #define DDRDATA8CH1_CR_RXPERBITRANK1_Lane6_HSH                       (0x04181114)

  #define DDRDATA8CH1_CR_RXPERBITRANK1_Lane7_OFF                       (28)
  #define DDRDATA8CH1_CR_RXPERBITRANK1_Lane7_WID                       ( 4)
  #define DDRDATA8CH1_CR_RXPERBITRANK1_Lane7_MSK                       (0xF0000000)
  #define DDRDATA8CH1_CR_RXPERBITRANK1_Lane7_MIN                       (0)
  #define DDRDATA8CH1_CR_RXPERBITRANK1_Lane7_MAX                       (15) // 0x0000000F
  #define DDRDATA8CH1_CR_RXPERBITRANK1_Lane7_DEF                       (0x00000000)
  #define DDRDATA8CH1_CR_RXPERBITRANK1_Lane7_HSH                       (0x041C1114)

#define DDRDATA8CH1_CR_RXPERBITRANK2_REG                               (0x00001118)

  #define DDRDATA8CH1_CR_RXPERBITRANK2_Lane0_OFF                       ( 0)
  #define DDRDATA8CH1_CR_RXPERBITRANK2_Lane0_WID                       ( 4)
  #define DDRDATA8CH1_CR_RXPERBITRANK2_Lane0_MSK                       (0x0000000F)
  #define DDRDATA8CH1_CR_RXPERBITRANK2_Lane0_MIN                       (0)
  #define DDRDATA8CH1_CR_RXPERBITRANK2_Lane0_MAX                       (15) // 0x0000000F
  #define DDRDATA8CH1_CR_RXPERBITRANK2_Lane0_DEF                       (0x00000000)
  #define DDRDATA8CH1_CR_RXPERBITRANK2_Lane0_HSH                       (0x04001118)

  #define DDRDATA8CH1_CR_RXPERBITRANK2_Lane1_OFF                       ( 4)
  #define DDRDATA8CH1_CR_RXPERBITRANK2_Lane1_WID                       ( 4)
  #define DDRDATA8CH1_CR_RXPERBITRANK2_Lane1_MSK                       (0x000000F0)
  #define DDRDATA8CH1_CR_RXPERBITRANK2_Lane1_MIN                       (0)
  #define DDRDATA8CH1_CR_RXPERBITRANK2_Lane1_MAX                       (15) // 0x0000000F
  #define DDRDATA8CH1_CR_RXPERBITRANK2_Lane1_DEF                       (0x00000000)
  #define DDRDATA8CH1_CR_RXPERBITRANK2_Lane1_HSH                       (0x04041118)

  #define DDRDATA8CH1_CR_RXPERBITRANK2_Lane2_OFF                       ( 8)
  #define DDRDATA8CH1_CR_RXPERBITRANK2_Lane2_WID                       ( 4)
  #define DDRDATA8CH1_CR_RXPERBITRANK2_Lane2_MSK                       (0x00000F00)
  #define DDRDATA8CH1_CR_RXPERBITRANK2_Lane2_MIN                       (0)
  #define DDRDATA8CH1_CR_RXPERBITRANK2_Lane2_MAX                       (15) // 0x0000000F
  #define DDRDATA8CH1_CR_RXPERBITRANK2_Lane2_DEF                       (0x00000000)
  #define DDRDATA8CH1_CR_RXPERBITRANK2_Lane2_HSH                       (0x04081118)

  #define DDRDATA8CH1_CR_RXPERBITRANK2_Lane3_OFF                       (12)
  #define DDRDATA8CH1_CR_RXPERBITRANK2_Lane3_WID                       ( 4)
  #define DDRDATA8CH1_CR_RXPERBITRANK2_Lane3_MSK                       (0x0000F000)
  #define DDRDATA8CH1_CR_RXPERBITRANK2_Lane3_MIN                       (0)
  #define DDRDATA8CH1_CR_RXPERBITRANK2_Lane3_MAX                       (15) // 0x0000000F
  #define DDRDATA8CH1_CR_RXPERBITRANK2_Lane3_DEF                       (0x00000000)
  #define DDRDATA8CH1_CR_RXPERBITRANK2_Lane3_HSH                       (0x040C1118)

  #define DDRDATA8CH1_CR_RXPERBITRANK2_Lane4_OFF                       (16)
  #define DDRDATA8CH1_CR_RXPERBITRANK2_Lane4_WID                       ( 4)
  #define DDRDATA8CH1_CR_RXPERBITRANK2_Lane4_MSK                       (0x000F0000)
  #define DDRDATA8CH1_CR_RXPERBITRANK2_Lane4_MIN                       (0)
  #define DDRDATA8CH1_CR_RXPERBITRANK2_Lane4_MAX                       (15) // 0x0000000F
  #define DDRDATA8CH1_CR_RXPERBITRANK2_Lane4_DEF                       (0x00000000)
  #define DDRDATA8CH1_CR_RXPERBITRANK2_Lane4_HSH                       (0x04101118)

  #define DDRDATA8CH1_CR_RXPERBITRANK2_Lane5_OFF                       (20)
  #define DDRDATA8CH1_CR_RXPERBITRANK2_Lane5_WID                       ( 4)
  #define DDRDATA8CH1_CR_RXPERBITRANK2_Lane5_MSK                       (0x00F00000)
  #define DDRDATA8CH1_CR_RXPERBITRANK2_Lane5_MIN                       (0)
  #define DDRDATA8CH1_CR_RXPERBITRANK2_Lane5_MAX                       (15) // 0x0000000F
  #define DDRDATA8CH1_CR_RXPERBITRANK2_Lane5_DEF                       (0x00000000)
  #define DDRDATA8CH1_CR_RXPERBITRANK2_Lane5_HSH                       (0x04141118)

  #define DDRDATA8CH1_CR_RXPERBITRANK2_Lane6_OFF                       (24)
  #define DDRDATA8CH1_CR_RXPERBITRANK2_Lane6_WID                       ( 4)
  #define DDRDATA8CH1_CR_RXPERBITRANK2_Lane6_MSK                       (0x0F000000)
  #define DDRDATA8CH1_CR_RXPERBITRANK2_Lane6_MIN                       (0)
  #define DDRDATA8CH1_CR_RXPERBITRANK2_Lane6_MAX                       (15) // 0x0000000F
  #define DDRDATA8CH1_CR_RXPERBITRANK2_Lane6_DEF                       (0x00000000)
  #define DDRDATA8CH1_CR_RXPERBITRANK2_Lane6_HSH                       (0x04181118)

  #define DDRDATA8CH1_CR_RXPERBITRANK2_Lane7_OFF                       (28)
  #define DDRDATA8CH1_CR_RXPERBITRANK2_Lane7_WID                       ( 4)
  #define DDRDATA8CH1_CR_RXPERBITRANK2_Lane7_MSK                       (0xF0000000)
  #define DDRDATA8CH1_CR_RXPERBITRANK2_Lane7_MIN                       (0)
  #define DDRDATA8CH1_CR_RXPERBITRANK2_Lane7_MAX                       (15) // 0x0000000F
  #define DDRDATA8CH1_CR_RXPERBITRANK2_Lane7_DEF                       (0x00000000)
  #define DDRDATA8CH1_CR_RXPERBITRANK2_Lane7_HSH                       (0x041C1118)

#define DDRDATA8CH1_CR_RXPERBITRANK3_REG                               (0x0000111C)

  #define DDRDATA8CH1_CR_RXPERBITRANK3_Lane0_OFF                       ( 0)
  #define DDRDATA8CH1_CR_RXPERBITRANK3_Lane0_WID                       ( 4)
  #define DDRDATA8CH1_CR_RXPERBITRANK3_Lane0_MSK                       (0x0000000F)
  #define DDRDATA8CH1_CR_RXPERBITRANK3_Lane0_MIN                       (0)
  #define DDRDATA8CH1_CR_RXPERBITRANK3_Lane0_MAX                       (15) // 0x0000000F
  #define DDRDATA8CH1_CR_RXPERBITRANK3_Lane0_DEF                       (0x00000000)
  #define DDRDATA8CH1_CR_RXPERBITRANK3_Lane0_HSH                       (0x0400111C)

  #define DDRDATA8CH1_CR_RXPERBITRANK3_Lane1_OFF                       ( 4)
  #define DDRDATA8CH1_CR_RXPERBITRANK3_Lane1_WID                       ( 4)
  #define DDRDATA8CH1_CR_RXPERBITRANK3_Lane1_MSK                       (0x000000F0)
  #define DDRDATA8CH1_CR_RXPERBITRANK3_Lane1_MIN                       (0)
  #define DDRDATA8CH1_CR_RXPERBITRANK3_Lane1_MAX                       (15) // 0x0000000F
  #define DDRDATA8CH1_CR_RXPERBITRANK3_Lane1_DEF                       (0x00000000)
  #define DDRDATA8CH1_CR_RXPERBITRANK3_Lane1_HSH                       (0x0404111C)

  #define DDRDATA8CH1_CR_RXPERBITRANK3_Lane2_OFF                       ( 8)
  #define DDRDATA8CH1_CR_RXPERBITRANK3_Lane2_WID                       ( 4)
  #define DDRDATA8CH1_CR_RXPERBITRANK3_Lane2_MSK                       (0x00000F00)
  #define DDRDATA8CH1_CR_RXPERBITRANK3_Lane2_MIN                       (0)
  #define DDRDATA8CH1_CR_RXPERBITRANK3_Lane2_MAX                       (15) // 0x0000000F
  #define DDRDATA8CH1_CR_RXPERBITRANK3_Lane2_DEF                       (0x00000000)
  #define DDRDATA8CH1_CR_RXPERBITRANK3_Lane2_HSH                       (0x0408111C)

  #define DDRDATA8CH1_CR_RXPERBITRANK3_Lane3_OFF                       (12)
  #define DDRDATA8CH1_CR_RXPERBITRANK3_Lane3_WID                       ( 4)
  #define DDRDATA8CH1_CR_RXPERBITRANK3_Lane3_MSK                       (0x0000F000)
  #define DDRDATA8CH1_CR_RXPERBITRANK3_Lane3_MIN                       (0)
  #define DDRDATA8CH1_CR_RXPERBITRANK3_Lane3_MAX                       (15) // 0x0000000F
  #define DDRDATA8CH1_CR_RXPERBITRANK3_Lane3_DEF                       (0x00000000)
  #define DDRDATA8CH1_CR_RXPERBITRANK3_Lane3_HSH                       (0x040C111C)

  #define DDRDATA8CH1_CR_RXPERBITRANK3_Lane4_OFF                       (16)
  #define DDRDATA8CH1_CR_RXPERBITRANK3_Lane4_WID                       ( 4)
  #define DDRDATA8CH1_CR_RXPERBITRANK3_Lane4_MSK                       (0x000F0000)
  #define DDRDATA8CH1_CR_RXPERBITRANK3_Lane4_MIN                       (0)
  #define DDRDATA8CH1_CR_RXPERBITRANK3_Lane4_MAX                       (15) // 0x0000000F
  #define DDRDATA8CH1_CR_RXPERBITRANK3_Lane4_DEF                       (0x00000000)
  #define DDRDATA8CH1_CR_RXPERBITRANK3_Lane4_HSH                       (0x0410111C)

  #define DDRDATA8CH1_CR_RXPERBITRANK3_Lane5_OFF                       (20)
  #define DDRDATA8CH1_CR_RXPERBITRANK3_Lane5_WID                       ( 4)
  #define DDRDATA8CH1_CR_RXPERBITRANK3_Lane5_MSK                       (0x00F00000)
  #define DDRDATA8CH1_CR_RXPERBITRANK3_Lane5_MIN                       (0)
  #define DDRDATA8CH1_CR_RXPERBITRANK3_Lane5_MAX                       (15) // 0x0000000F
  #define DDRDATA8CH1_CR_RXPERBITRANK3_Lane5_DEF                       (0x00000000)
  #define DDRDATA8CH1_CR_RXPERBITRANK3_Lane5_HSH                       (0x0414111C)

  #define DDRDATA8CH1_CR_RXPERBITRANK3_Lane6_OFF                       (24)
  #define DDRDATA8CH1_CR_RXPERBITRANK3_Lane6_WID                       ( 4)
  #define DDRDATA8CH1_CR_RXPERBITRANK3_Lane6_MSK                       (0x0F000000)
  #define DDRDATA8CH1_CR_RXPERBITRANK3_Lane6_MIN                       (0)
  #define DDRDATA8CH1_CR_RXPERBITRANK3_Lane6_MAX                       (15) // 0x0000000F
  #define DDRDATA8CH1_CR_RXPERBITRANK3_Lane6_DEF                       (0x00000000)
  #define DDRDATA8CH1_CR_RXPERBITRANK3_Lane6_HSH                       (0x0418111C)

  #define DDRDATA8CH1_CR_RXPERBITRANK3_Lane7_OFF                       (28)
  #define DDRDATA8CH1_CR_RXPERBITRANK3_Lane7_WID                       ( 4)
  #define DDRDATA8CH1_CR_RXPERBITRANK3_Lane7_MSK                       (0xF0000000)
  #define DDRDATA8CH1_CR_RXPERBITRANK3_Lane7_MIN                       (0)
  #define DDRDATA8CH1_CR_RXPERBITRANK3_Lane7_MAX                       (15) // 0x0000000F
  #define DDRDATA8CH1_CR_RXPERBITRANK3_Lane7_DEF                       (0x00000000)
  #define DDRDATA8CH1_CR_RXPERBITRANK3_Lane7_HSH                       (0x041C111C)

#define DDRDATA8CH1_CR_TXTRAINRANK0_REG                                (0x00001120)

  #define DDRDATA8CH1_CR_TXTRAINRANK0_TxDqDelay_OFF                    ( 0)
  #define DDRDATA8CH1_CR_TXTRAINRANK0_TxDqDelay_WID                    ( 9)
  #define DDRDATA8CH1_CR_TXTRAINRANK0_TxDqDelay_MSK                    (0x000001FF)
  #define DDRDATA8CH1_CR_TXTRAINRANK0_TxDqDelay_MIN                    (0)
  #define DDRDATA8CH1_CR_TXTRAINRANK0_TxDqDelay_MAX                    (511) // 0x000001FF
  #define DDRDATA8CH1_CR_TXTRAINRANK0_TxDqDelay_DEF                    (0x00000000)
  #define DDRDATA8CH1_CR_TXTRAINRANK0_TxDqDelay_HSH                    (0x09001120)

  #define DDRDATA8CH1_CR_TXTRAINRANK0_TxDqsDelay_OFF                   ( 9)
  #define DDRDATA8CH1_CR_TXTRAINRANK0_TxDqsDelay_WID                   ( 9)
  #define DDRDATA8CH1_CR_TXTRAINRANK0_TxDqsDelay_MSK                   (0x0003FE00)
  #define DDRDATA8CH1_CR_TXTRAINRANK0_TxDqsDelay_MIN                   (0)
  #define DDRDATA8CH1_CR_TXTRAINRANK0_TxDqsDelay_MAX                   (511) // 0x000001FF
  #define DDRDATA8CH1_CR_TXTRAINRANK0_TxDqsDelay_DEF                   (0x00000000)
  #define DDRDATA8CH1_CR_TXTRAINRANK0_TxDqsDelay_HSH                   (0x09091120)

  #define DDRDATA8CH1_CR_TXTRAINRANK0_Spare0_OFF                       (18)
  #define DDRDATA8CH1_CR_TXTRAINRANK0_Spare0_WID                       ( 2)
  #define DDRDATA8CH1_CR_TXTRAINRANK0_Spare0_MSK                       (0x000C0000)
  #define DDRDATA8CH1_CR_TXTRAINRANK0_Spare0_MIN                       (0)
  #define DDRDATA8CH1_CR_TXTRAINRANK0_Spare0_MAX                       (3) // 0x00000003
  #define DDRDATA8CH1_CR_TXTRAINRANK0_Spare0_DEF                       (0x00000000)
  #define DDRDATA8CH1_CR_TXTRAINRANK0_Spare0_HSH                       (0x02121120)

  #define DDRDATA8CH1_CR_TXTRAINRANK0_TxEqualization_OFF               (20)
  #define DDRDATA8CH1_CR_TXTRAINRANK0_TxEqualization_WID               ( 6)
  #define DDRDATA8CH1_CR_TXTRAINRANK0_TxEqualization_MSK               (0x03F00000)
  #define DDRDATA8CH1_CR_TXTRAINRANK0_TxEqualization_MIN               (0)
  #define DDRDATA8CH1_CR_TXTRAINRANK0_TxEqualization_MAX               (63) // 0x0000003F
  #define DDRDATA8CH1_CR_TXTRAINRANK0_TxEqualization_DEF               (0x00000000)
  #define DDRDATA8CH1_CR_TXTRAINRANK0_TxEqualization_HSH               (0x06141120)

  #define DDRDATA8CH1_CR_TXTRAINRANK0_Spare1_OFF                       (26)
  #define DDRDATA8CH1_CR_TXTRAINRANK0_Spare1_WID                       ( 6)
  #define DDRDATA8CH1_CR_TXTRAINRANK0_Spare1_MSK                       (0xFC000000)
  #define DDRDATA8CH1_CR_TXTRAINRANK0_Spare1_MIN                       (0)
  #define DDRDATA8CH1_CR_TXTRAINRANK0_Spare1_MAX                       (63) // 0x0000003F
  #define DDRDATA8CH1_CR_TXTRAINRANK0_Spare1_DEF                       (0x00000000)
  #define DDRDATA8CH1_CR_TXTRAINRANK0_Spare1_HSH                       (0x061A1120)

#define DDRDATA8CH1_CR_TXTRAINRANK1_REG                                (0x00001124)

  #define DDRDATA8CH1_CR_TXTRAINRANK1_TxDqDelay_OFF                    ( 0)
  #define DDRDATA8CH1_CR_TXTRAINRANK1_TxDqDelay_WID                    ( 9)
  #define DDRDATA8CH1_CR_TXTRAINRANK1_TxDqDelay_MSK                    (0x000001FF)
  #define DDRDATA8CH1_CR_TXTRAINRANK1_TxDqDelay_MIN                    (0)
  #define DDRDATA8CH1_CR_TXTRAINRANK1_TxDqDelay_MAX                    (511) // 0x000001FF
  #define DDRDATA8CH1_CR_TXTRAINRANK1_TxDqDelay_DEF                    (0x00000000)
  #define DDRDATA8CH1_CR_TXTRAINRANK1_TxDqDelay_HSH                    (0x09001124)

  #define DDRDATA8CH1_CR_TXTRAINRANK1_TxDqsDelay_OFF                   ( 9)
  #define DDRDATA8CH1_CR_TXTRAINRANK1_TxDqsDelay_WID                   ( 9)
  #define DDRDATA8CH1_CR_TXTRAINRANK1_TxDqsDelay_MSK                   (0x0003FE00)
  #define DDRDATA8CH1_CR_TXTRAINRANK1_TxDqsDelay_MIN                   (0)
  #define DDRDATA8CH1_CR_TXTRAINRANK1_TxDqsDelay_MAX                   (511) // 0x000001FF
  #define DDRDATA8CH1_CR_TXTRAINRANK1_TxDqsDelay_DEF                   (0x00000000)
  #define DDRDATA8CH1_CR_TXTRAINRANK1_TxDqsDelay_HSH                   (0x09091124)

  #define DDRDATA8CH1_CR_TXTRAINRANK1_Spare0_OFF                       (18)
  #define DDRDATA8CH1_CR_TXTRAINRANK1_Spare0_WID                       ( 2)
  #define DDRDATA8CH1_CR_TXTRAINRANK1_Spare0_MSK                       (0x000C0000)
  #define DDRDATA8CH1_CR_TXTRAINRANK1_Spare0_MIN                       (0)
  #define DDRDATA8CH1_CR_TXTRAINRANK1_Spare0_MAX                       (3) // 0x00000003
  #define DDRDATA8CH1_CR_TXTRAINRANK1_Spare0_DEF                       (0x00000000)
  #define DDRDATA8CH1_CR_TXTRAINRANK1_Spare0_HSH                       (0x02121124)

  #define DDRDATA8CH1_CR_TXTRAINRANK1_TxEqualization_OFF               (20)
  #define DDRDATA8CH1_CR_TXTRAINRANK1_TxEqualization_WID               ( 6)
  #define DDRDATA8CH1_CR_TXTRAINRANK1_TxEqualization_MSK               (0x03F00000)
  #define DDRDATA8CH1_CR_TXTRAINRANK1_TxEqualization_MIN               (0)
  #define DDRDATA8CH1_CR_TXTRAINRANK1_TxEqualization_MAX               (63) // 0x0000003F
  #define DDRDATA8CH1_CR_TXTRAINRANK1_TxEqualization_DEF               (0x00000000)
  #define DDRDATA8CH1_CR_TXTRAINRANK1_TxEqualization_HSH               (0x06141124)

  #define DDRDATA8CH1_CR_TXTRAINRANK1_Spare1_OFF                       (26)
  #define DDRDATA8CH1_CR_TXTRAINRANK1_Spare1_WID                       ( 6)
  #define DDRDATA8CH1_CR_TXTRAINRANK1_Spare1_MSK                       (0xFC000000)
  #define DDRDATA8CH1_CR_TXTRAINRANK1_Spare1_MIN                       (0)
  #define DDRDATA8CH1_CR_TXTRAINRANK1_Spare1_MAX                       (63) // 0x0000003F
  #define DDRDATA8CH1_CR_TXTRAINRANK1_Spare1_DEF                       (0x00000000)
  #define DDRDATA8CH1_CR_TXTRAINRANK1_Spare1_HSH                       (0x061A1124)

#define DDRDATA8CH1_CR_TXTRAINRANK2_REG                                (0x00001128)

  #define DDRDATA8CH1_CR_TXTRAINRANK2_TxDqDelay_OFF                    ( 0)
  #define DDRDATA8CH1_CR_TXTRAINRANK2_TxDqDelay_WID                    ( 9)
  #define DDRDATA8CH1_CR_TXTRAINRANK2_TxDqDelay_MSK                    (0x000001FF)
  #define DDRDATA8CH1_CR_TXTRAINRANK2_TxDqDelay_MIN                    (0)
  #define DDRDATA8CH1_CR_TXTRAINRANK2_TxDqDelay_MAX                    (511) // 0x000001FF
  #define DDRDATA8CH1_CR_TXTRAINRANK2_TxDqDelay_DEF                    (0x00000000)
  #define DDRDATA8CH1_CR_TXTRAINRANK2_TxDqDelay_HSH                    (0x09001128)

  #define DDRDATA8CH1_CR_TXTRAINRANK2_TxDqsDelay_OFF                   ( 9)
  #define DDRDATA8CH1_CR_TXTRAINRANK2_TxDqsDelay_WID                   ( 9)
  #define DDRDATA8CH1_CR_TXTRAINRANK2_TxDqsDelay_MSK                   (0x0003FE00)
  #define DDRDATA8CH1_CR_TXTRAINRANK2_TxDqsDelay_MIN                   (0)
  #define DDRDATA8CH1_CR_TXTRAINRANK2_TxDqsDelay_MAX                   (511) // 0x000001FF
  #define DDRDATA8CH1_CR_TXTRAINRANK2_TxDqsDelay_DEF                   (0x00000000)
  #define DDRDATA8CH1_CR_TXTRAINRANK2_TxDqsDelay_HSH                   (0x09091128)

  #define DDRDATA8CH1_CR_TXTRAINRANK2_Spare0_OFF                       (18)
  #define DDRDATA8CH1_CR_TXTRAINRANK2_Spare0_WID                       ( 2)
  #define DDRDATA8CH1_CR_TXTRAINRANK2_Spare0_MSK                       (0x000C0000)
  #define DDRDATA8CH1_CR_TXTRAINRANK2_Spare0_MIN                       (0)
  #define DDRDATA8CH1_CR_TXTRAINRANK2_Spare0_MAX                       (3) // 0x00000003
  #define DDRDATA8CH1_CR_TXTRAINRANK2_Spare0_DEF                       (0x00000000)
  #define DDRDATA8CH1_CR_TXTRAINRANK2_Spare0_HSH                       (0x02121128)

  #define DDRDATA8CH1_CR_TXTRAINRANK2_TxEqualization_OFF               (20)
  #define DDRDATA8CH1_CR_TXTRAINRANK2_TxEqualization_WID               ( 6)
  #define DDRDATA8CH1_CR_TXTRAINRANK2_TxEqualization_MSK               (0x03F00000)
  #define DDRDATA8CH1_CR_TXTRAINRANK2_TxEqualization_MIN               (0)
  #define DDRDATA8CH1_CR_TXTRAINRANK2_TxEqualization_MAX               (63) // 0x0000003F
  #define DDRDATA8CH1_CR_TXTRAINRANK2_TxEqualization_DEF               (0x00000000)
  #define DDRDATA8CH1_CR_TXTRAINRANK2_TxEqualization_HSH               (0x06141128)

  #define DDRDATA8CH1_CR_TXTRAINRANK2_Spare1_OFF                       (26)
  #define DDRDATA8CH1_CR_TXTRAINRANK2_Spare1_WID                       ( 6)
  #define DDRDATA8CH1_CR_TXTRAINRANK2_Spare1_MSK                       (0xFC000000)
  #define DDRDATA8CH1_CR_TXTRAINRANK2_Spare1_MIN                       (0)
  #define DDRDATA8CH1_CR_TXTRAINRANK2_Spare1_MAX                       (63) // 0x0000003F
  #define DDRDATA8CH1_CR_TXTRAINRANK2_Spare1_DEF                       (0x00000000)
  #define DDRDATA8CH1_CR_TXTRAINRANK2_Spare1_HSH                       (0x061A1128)

#define DDRDATA8CH1_CR_TXTRAINRANK3_REG                                (0x0000112C)

  #define DDRDATA8CH1_CR_TXTRAINRANK3_TxDqDelay_OFF                    ( 0)
  #define DDRDATA8CH1_CR_TXTRAINRANK3_TxDqDelay_WID                    ( 9)
  #define DDRDATA8CH1_CR_TXTRAINRANK3_TxDqDelay_MSK                    (0x000001FF)
  #define DDRDATA8CH1_CR_TXTRAINRANK3_TxDqDelay_MIN                    (0)
  #define DDRDATA8CH1_CR_TXTRAINRANK3_TxDqDelay_MAX                    (511) // 0x000001FF
  #define DDRDATA8CH1_CR_TXTRAINRANK3_TxDqDelay_DEF                    (0x00000000)
  #define DDRDATA8CH1_CR_TXTRAINRANK3_TxDqDelay_HSH                    (0x0900112C)

  #define DDRDATA8CH1_CR_TXTRAINRANK3_TxDqsDelay_OFF                   ( 9)
  #define DDRDATA8CH1_CR_TXTRAINRANK3_TxDqsDelay_WID                   ( 9)
  #define DDRDATA8CH1_CR_TXTRAINRANK3_TxDqsDelay_MSK                   (0x0003FE00)
  #define DDRDATA8CH1_CR_TXTRAINRANK3_TxDqsDelay_MIN                   (0)
  #define DDRDATA8CH1_CR_TXTRAINRANK3_TxDqsDelay_MAX                   (511) // 0x000001FF
  #define DDRDATA8CH1_CR_TXTRAINRANK3_TxDqsDelay_DEF                   (0x00000000)
  #define DDRDATA8CH1_CR_TXTRAINRANK3_TxDqsDelay_HSH                   (0x0909112C)

  #define DDRDATA8CH1_CR_TXTRAINRANK3_Spare0_OFF                       (18)
  #define DDRDATA8CH1_CR_TXTRAINRANK3_Spare0_WID                       ( 2)
  #define DDRDATA8CH1_CR_TXTRAINRANK3_Spare0_MSK                       (0x000C0000)
  #define DDRDATA8CH1_CR_TXTRAINRANK3_Spare0_MIN                       (0)
  #define DDRDATA8CH1_CR_TXTRAINRANK3_Spare0_MAX                       (3) // 0x00000003
  #define DDRDATA8CH1_CR_TXTRAINRANK3_Spare0_DEF                       (0x00000000)
  #define DDRDATA8CH1_CR_TXTRAINRANK3_Spare0_HSH                       (0x0212112C)

  #define DDRDATA8CH1_CR_TXTRAINRANK3_TxEqualization_OFF               (20)
  #define DDRDATA8CH1_CR_TXTRAINRANK3_TxEqualization_WID               ( 6)
  #define DDRDATA8CH1_CR_TXTRAINRANK3_TxEqualization_MSK               (0x03F00000)
  #define DDRDATA8CH1_CR_TXTRAINRANK3_TxEqualization_MIN               (0)
  #define DDRDATA8CH1_CR_TXTRAINRANK3_TxEqualization_MAX               (63) // 0x0000003F
  #define DDRDATA8CH1_CR_TXTRAINRANK3_TxEqualization_DEF               (0x00000000)
  #define DDRDATA8CH1_CR_TXTRAINRANK3_TxEqualization_HSH               (0x0614112C)

  #define DDRDATA8CH1_CR_TXTRAINRANK3_Spare1_OFF                       (26)
  #define DDRDATA8CH1_CR_TXTRAINRANK3_Spare1_WID                       ( 6)
  #define DDRDATA8CH1_CR_TXTRAINRANK3_Spare1_MSK                       (0xFC000000)
  #define DDRDATA8CH1_CR_TXTRAINRANK3_Spare1_MIN                       (0)
  #define DDRDATA8CH1_CR_TXTRAINRANK3_Spare1_MAX                       (63) // 0x0000003F
  #define DDRDATA8CH1_CR_TXTRAINRANK3_Spare1_DEF                       (0x00000000)
  #define DDRDATA8CH1_CR_TXTRAINRANK3_Spare1_HSH                       (0x061A112C)

#define DDRDATA8CH1_CR_TXPERBITRANK0_REG                               (0x00001130)

  #define DDRDATA8CH1_CR_TXPERBITRANK0_Lane0_OFF                       ( 0)
  #define DDRDATA8CH1_CR_TXPERBITRANK0_Lane0_WID                       ( 4)
  #define DDRDATA8CH1_CR_TXPERBITRANK0_Lane0_MSK                       (0x0000000F)
  #define DDRDATA8CH1_CR_TXPERBITRANK0_Lane0_MIN                       (0)
  #define DDRDATA8CH1_CR_TXPERBITRANK0_Lane0_MAX                       (15) // 0x0000000F
  #define DDRDATA8CH1_CR_TXPERBITRANK0_Lane0_DEF                       (0x00000000)
  #define DDRDATA8CH1_CR_TXPERBITRANK0_Lane0_HSH                       (0x04001130)

  #define DDRDATA8CH1_CR_TXPERBITRANK0_Lane1_OFF                       ( 4)
  #define DDRDATA8CH1_CR_TXPERBITRANK0_Lane1_WID                       ( 4)
  #define DDRDATA8CH1_CR_TXPERBITRANK0_Lane1_MSK                       (0x000000F0)
  #define DDRDATA8CH1_CR_TXPERBITRANK0_Lane1_MIN                       (0)
  #define DDRDATA8CH1_CR_TXPERBITRANK0_Lane1_MAX                       (15) // 0x0000000F
  #define DDRDATA8CH1_CR_TXPERBITRANK0_Lane1_DEF                       (0x00000000)
  #define DDRDATA8CH1_CR_TXPERBITRANK0_Lane1_HSH                       (0x04041130)

  #define DDRDATA8CH1_CR_TXPERBITRANK0_Lane2_OFF                       ( 8)
  #define DDRDATA8CH1_CR_TXPERBITRANK0_Lane2_WID                       ( 4)
  #define DDRDATA8CH1_CR_TXPERBITRANK0_Lane2_MSK                       (0x00000F00)
  #define DDRDATA8CH1_CR_TXPERBITRANK0_Lane2_MIN                       (0)
  #define DDRDATA8CH1_CR_TXPERBITRANK0_Lane2_MAX                       (15) // 0x0000000F
  #define DDRDATA8CH1_CR_TXPERBITRANK0_Lane2_DEF                       (0x00000000)
  #define DDRDATA8CH1_CR_TXPERBITRANK0_Lane2_HSH                       (0x04081130)

  #define DDRDATA8CH1_CR_TXPERBITRANK0_Lane3_OFF                       (12)
  #define DDRDATA8CH1_CR_TXPERBITRANK0_Lane3_WID                       ( 4)
  #define DDRDATA8CH1_CR_TXPERBITRANK0_Lane3_MSK                       (0x0000F000)
  #define DDRDATA8CH1_CR_TXPERBITRANK0_Lane3_MIN                       (0)
  #define DDRDATA8CH1_CR_TXPERBITRANK0_Lane3_MAX                       (15) // 0x0000000F
  #define DDRDATA8CH1_CR_TXPERBITRANK0_Lane3_DEF                       (0x00000000)
  #define DDRDATA8CH1_CR_TXPERBITRANK0_Lane3_HSH                       (0x040C1130)

  #define DDRDATA8CH1_CR_TXPERBITRANK0_Lane4_OFF                       (16)
  #define DDRDATA8CH1_CR_TXPERBITRANK0_Lane4_WID                       ( 4)
  #define DDRDATA8CH1_CR_TXPERBITRANK0_Lane4_MSK                       (0x000F0000)
  #define DDRDATA8CH1_CR_TXPERBITRANK0_Lane4_MIN                       (0)
  #define DDRDATA8CH1_CR_TXPERBITRANK0_Lane4_MAX                       (15) // 0x0000000F
  #define DDRDATA8CH1_CR_TXPERBITRANK0_Lane4_DEF                       (0x00000000)
  #define DDRDATA8CH1_CR_TXPERBITRANK0_Lane4_HSH                       (0x04101130)

  #define DDRDATA8CH1_CR_TXPERBITRANK0_Lane5_OFF                       (20)
  #define DDRDATA8CH1_CR_TXPERBITRANK0_Lane5_WID                       ( 4)
  #define DDRDATA8CH1_CR_TXPERBITRANK0_Lane5_MSK                       (0x00F00000)
  #define DDRDATA8CH1_CR_TXPERBITRANK0_Lane5_MIN                       (0)
  #define DDRDATA8CH1_CR_TXPERBITRANK0_Lane5_MAX                       (15) // 0x0000000F
  #define DDRDATA8CH1_CR_TXPERBITRANK0_Lane5_DEF                       (0x00000000)
  #define DDRDATA8CH1_CR_TXPERBITRANK0_Lane5_HSH                       (0x04141130)

  #define DDRDATA8CH1_CR_TXPERBITRANK0_Lane6_OFF                       (24)
  #define DDRDATA8CH1_CR_TXPERBITRANK0_Lane6_WID                       ( 4)
  #define DDRDATA8CH1_CR_TXPERBITRANK0_Lane6_MSK                       (0x0F000000)
  #define DDRDATA8CH1_CR_TXPERBITRANK0_Lane6_MIN                       (0)
  #define DDRDATA8CH1_CR_TXPERBITRANK0_Lane6_MAX                       (15) // 0x0000000F
  #define DDRDATA8CH1_CR_TXPERBITRANK0_Lane6_DEF                       (0x00000000)
  #define DDRDATA8CH1_CR_TXPERBITRANK0_Lane6_HSH                       (0x04181130)

  #define DDRDATA8CH1_CR_TXPERBITRANK0_Lane7_OFF                       (28)
  #define DDRDATA8CH1_CR_TXPERBITRANK0_Lane7_WID                       ( 4)
  #define DDRDATA8CH1_CR_TXPERBITRANK0_Lane7_MSK                       (0xF0000000)
  #define DDRDATA8CH1_CR_TXPERBITRANK0_Lane7_MIN                       (0)
  #define DDRDATA8CH1_CR_TXPERBITRANK0_Lane7_MAX                       (15) // 0x0000000F
  #define DDRDATA8CH1_CR_TXPERBITRANK0_Lane7_DEF                       (0x00000000)
  #define DDRDATA8CH1_CR_TXPERBITRANK0_Lane7_HSH                       (0x041C1130)

#define DDRDATA8CH1_CR_TXPERBITRANK1_REG                               (0x00001134)

  #define DDRDATA8CH1_CR_TXPERBITRANK1_Lane0_OFF                       ( 0)
  #define DDRDATA8CH1_CR_TXPERBITRANK1_Lane0_WID                       ( 4)
  #define DDRDATA8CH1_CR_TXPERBITRANK1_Lane0_MSK                       (0x0000000F)
  #define DDRDATA8CH1_CR_TXPERBITRANK1_Lane0_MIN                       (0)
  #define DDRDATA8CH1_CR_TXPERBITRANK1_Lane0_MAX                       (15) // 0x0000000F
  #define DDRDATA8CH1_CR_TXPERBITRANK1_Lane0_DEF                       (0x00000000)
  #define DDRDATA8CH1_CR_TXPERBITRANK1_Lane0_HSH                       (0x04001134)

  #define DDRDATA8CH1_CR_TXPERBITRANK1_Lane1_OFF                       ( 4)
  #define DDRDATA8CH1_CR_TXPERBITRANK1_Lane1_WID                       ( 4)
  #define DDRDATA8CH1_CR_TXPERBITRANK1_Lane1_MSK                       (0x000000F0)
  #define DDRDATA8CH1_CR_TXPERBITRANK1_Lane1_MIN                       (0)
  #define DDRDATA8CH1_CR_TXPERBITRANK1_Lane1_MAX                       (15) // 0x0000000F
  #define DDRDATA8CH1_CR_TXPERBITRANK1_Lane1_DEF                       (0x00000000)
  #define DDRDATA8CH1_CR_TXPERBITRANK1_Lane1_HSH                       (0x04041134)

  #define DDRDATA8CH1_CR_TXPERBITRANK1_Lane2_OFF                       ( 8)
  #define DDRDATA8CH1_CR_TXPERBITRANK1_Lane2_WID                       ( 4)
  #define DDRDATA8CH1_CR_TXPERBITRANK1_Lane2_MSK                       (0x00000F00)
  #define DDRDATA8CH1_CR_TXPERBITRANK1_Lane2_MIN                       (0)
  #define DDRDATA8CH1_CR_TXPERBITRANK1_Lane2_MAX                       (15) // 0x0000000F
  #define DDRDATA8CH1_CR_TXPERBITRANK1_Lane2_DEF                       (0x00000000)
  #define DDRDATA8CH1_CR_TXPERBITRANK1_Lane2_HSH                       (0x04081134)

  #define DDRDATA8CH1_CR_TXPERBITRANK1_Lane3_OFF                       (12)
  #define DDRDATA8CH1_CR_TXPERBITRANK1_Lane3_WID                       ( 4)
  #define DDRDATA8CH1_CR_TXPERBITRANK1_Lane3_MSK                       (0x0000F000)
  #define DDRDATA8CH1_CR_TXPERBITRANK1_Lane3_MIN                       (0)
  #define DDRDATA8CH1_CR_TXPERBITRANK1_Lane3_MAX                       (15) // 0x0000000F
  #define DDRDATA8CH1_CR_TXPERBITRANK1_Lane3_DEF                       (0x00000000)
  #define DDRDATA8CH1_CR_TXPERBITRANK1_Lane3_HSH                       (0x040C1134)

  #define DDRDATA8CH1_CR_TXPERBITRANK1_Lane4_OFF                       (16)
  #define DDRDATA8CH1_CR_TXPERBITRANK1_Lane4_WID                       ( 4)
  #define DDRDATA8CH1_CR_TXPERBITRANK1_Lane4_MSK                       (0x000F0000)
  #define DDRDATA8CH1_CR_TXPERBITRANK1_Lane4_MIN                       (0)
  #define DDRDATA8CH1_CR_TXPERBITRANK1_Lane4_MAX                       (15) // 0x0000000F
  #define DDRDATA8CH1_CR_TXPERBITRANK1_Lane4_DEF                       (0x00000000)
  #define DDRDATA8CH1_CR_TXPERBITRANK1_Lane4_HSH                       (0x04101134)

  #define DDRDATA8CH1_CR_TXPERBITRANK1_Lane5_OFF                       (20)
  #define DDRDATA8CH1_CR_TXPERBITRANK1_Lane5_WID                       ( 4)
  #define DDRDATA8CH1_CR_TXPERBITRANK1_Lane5_MSK                       (0x00F00000)
  #define DDRDATA8CH1_CR_TXPERBITRANK1_Lane5_MIN                       (0)
  #define DDRDATA8CH1_CR_TXPERBITRANK1_Lane5_MAX                       (15) // 0x0000000F
  #define DDRDATA8CH1_CR_TXPERBITRANK1_Lane5_DEF                       (0x00000000)
  #define DDRDATA8CH1_CR_TXPERBITRANK1_Lane5_HSH                       (0x04141134)

  #define DDRDATA8CH1_CR_TXPERBITRANK1_Lane6_OFF                       (24)
  #define DDRDATA8CH1_CR_TXPERBITRANK1_Lane6_WID                       ( 4)
  #define DDRDATA8CH1_CR_TXPERBITRANK1_Lane6_MSK                       (0x0F000000)
  #define DDRDATA8CH1_CR_TXPERBITRANK1_Lane6_MIN                       (0)
  #define DDRDATA8CH1_CR_TXPERBITRANK1_Lane6_MAX                       (15) // 0x0000000F
  #define DDRDATA8CH1_CR_TXPERBITRANK1_Lane6_DEF                       (0x00000000)
  #define DDRDATA8CH1_CR_TXPERBITRANK1_Lane6_HSH                       (0x04181134)

  #define DDRDATA8CH1_CR_TXPERBITRANK1_Lane7_OFF                       (28)
  #define DDRDATA8CH1_CR_TXPERBITRANK1_Lane7_WID                       ( 4)
  #define DDRDATA8CH1_CR_TXPERBITRANK1_Lane7_MSK                       (0xF0000000)
  #define DDRDATA8CH1_CR_TXPERBITRANK1_Lane7_MIN                       (0)
  #define DDRDATA8CH1_CR_TXPERBITRANK1_Lane7_MAX                       (15) // 0x0000000F
  #define DDRDATA8CH1_CR_TXPERBITRANK1_Lane7_DEF                       (0x00000000)
  #define DDRDATA8CH1_CR_TXPERBITRANK1_Lane7_HSH                       (0x041C1134)

#define DDRDATA8CH1_CR_TXPERBITRANK2_REG                               (0x00001138)

  #define DDRDATA8CH1_CR_TXPERBITRANK2_Lane0_OFF                       ( 0)
  #define DDRDATA8CH1_CR_TXPERBITRANK2_Lane0_WID                       ( 4)
  #define DDRDATA8CH1_CR_TXPERBITRANK2_Lane0_MSK                       (0x0000000F)
  #define DDRDATA8CH1_CR_TXPERBITRANK2_Lane0_MIN                       (0)
  #define DDRDATA8CH1_CR_TXPERBITRANK2_Lane0_MAX                       (15) // 0x0000000F
  #define DDRDATA8CH1_CR_TXPERBITRANK2_Lane0_DEF                       (0x00000000)
  #define DDRDATA8CH1_CR_TXPERBITRANK2_Lane0_HSH                       (0x04001138)

  #define DDRDATA8CH1_CR_TXPERBITRANK2_Lane1_OFF                       ( 4)
  #define DDRDATA8CH1_CR_TXPERBITRANK2_Lane1_WID                       ( 4)
  #define DDRDATA8CH1_CR_TXPERBITRANK2_Lane1_MSK                       (0x000000F0)
  #define DDRDATA8CH1_CR_TXPERBITRANK2_Lane1_MIN                       (0)
  #define DDRDATA8CH1_CR_TXPERBITRANK2_Lane1_MAX                       (15) // 0x0000000F
  #define DDRDATA8CH1_CR_TXPERBITRANK2_Lane1_DEF                       (0x00000000)
  #define DDRDATA8CH1_CR_TXPERBITRANK2_Lane1_HSH                       (0x04041138)

  #define DDRDATA8CH1_CR_TXPERBITRANK2_Lane2_OFF                       ( 8)
  #define DDRDATA8CH1_CR_TXPERBITRANK2_Lane2_WID                       ( 4)
  #define DDRDATA8CH1_CR_TXPERBITRANK2_Lane2_MSK                       (0x00000F00)
  #define DDRDATA8CH1_CR_TXPERBITRANK2_Lane2_MIN                       (0)
  #define DDRDATA8CH1_CR_TXPERBITRANK2_Lane2_MAX                       (15) // 0x0000000F
  #define DDRDATA8CH1_CR_TXPERBITRANK2_Lane2_DEF                       (0x00000000)
  #define DDRDATA8CH1_CR_TXPERBITRANK2_Lane2_HSH                       (0x04081138)

  #define DDRDATA8CH1_CR_TXPERBITRANK2_Lane3_OFF                       (12)
  #define DDRDATA8CH1_CR_TXPERBITRANK2_Lane3_WID                       ( 4)
  #define DDRDATA8CH1_CR_TXPERBITRANK2_Lane3_MSK                       (0x0000F000)
  #define DDRDATA8CH1_CR_TXPERBITRANK2_Lane3_MIN                       (0)
  #define DDRDATA8CH1_CR_TXPERBITRANK2_Lane3_MAX                       (15) // 0x0000000F
  #define DDRDATA8CH1_CR_TXPERBITRANK2_Lane3_DEF                       (0x00000000)
  #define DDRDATA8CH1_CR_TXPERBITRANK2_Lane3_HSH                       (0x040C1138)

  #define DDRDATA8CH1_CR_TXPERBITRANK2_Lane4_OFF                       (16)
  #define DDRDATA8CH1_CR_TXPERBITRANK2_Lane4_WID                       ( 4)
  #define DDRDATA8CH1_CR_TXPERBITRANK2_Lane4_MSK                       (0x000F0000)
  #define DDRDATA8CH1_CR_TXPERBITRANK2_Lane4_MIN                       (0)
  #define DDRDATA8CH1_CR_TXPERBITRANK2_Lane4_MAX                       (15) // 0x0000000F
  #define DDRDATA8CH1_CR_TXPERBITRANK2_Lane4_DEF                       (0x00000000)
  #define DDRDATA8CH1_CR_TXPERBITRANK2_Lane4_HSH                       (0x04101138)

  #define DDRDATA8CH1_CR_TXPERBITRANK2_Lane5_OFF                       (20)
  #define DDRDATA8CH1_CR_TXPERBITRANK2_Lane5_WID                       ( 4)
  #define DDRDATA8CH1_CR_TXPERBITRANK2_Lane5_MSK                       (0x00F00000)
  #define DDRDATA8CH1_CR_TXPERBITRANK2_Lane5_MIN                       (0)
  #define DDRDATA8CH1_CR_TXPERBITRANK2_Lane5_MAX                       (15) // 0x0000000F
  #define DDRDATA8CH1_CR_TXPERBITRANK2_Lane5_DEF                       (0x00000000)
  #define DDRDATA8CH1_CR_TXPERBITRANK2_Lane5_HSH                       (0x04141138)

  #define DDRDATA8CH1_CR_TXPERBITRANK2_Lane6_OFF                       (24)
  #define DDRDATA8CH1_CR_TXPERBITRANK2_Lane6_WID                       ( 4)
  #define DDRDATA8CH1_CR_TXPERBITRANK2_Lane6_MSK                       (0x0F000000)
  #define DDRDATA8CH1_CR_TXPERBITRANK2_Lane6_MIN                       (0)
  #define DDRDATA8CH1_CR_TXPERBITRANK2_Lane6_MAX                       (15) // 0x0000000F
  #define DDRDATA8CH1_CR_TXPERBITRANK2_Lane6_DEF                       (0x00000000)
  #define DDRDATA8CH1_CR_TXPERBITRANK2_Lane6_HSH                       (0x04181138)

  #define DDRDATA8CH1_CR_TXPERBITRANK2_Lane7_OFF                       (28)
  #define DDRDATA8CH1_CR_TXPERBITRANK2_Lane7_WID                       ( 4)
  #define DDRDATA8CH1_CR_TXPERBITRANK2_Lane7_MSK                       (0xF0000000)
  #define DDRDATA8CH1_CR_TXPERBITRANK2_Lane7_MIN                       (0)
  #define DDRDATA8CH1_CR_TXPERBITRANK2_Lane7_MAX                       (15) // 0x0000000F
  #define DDRDATA8CH1_CR_TXPERBITRANK2_Lane7_DEF                       (0x00000000)
  #define DDRDATA8CH1_CR_TXPERBITRANK2_Lane7_HSH                       (0x041C1138)

#define DDRDATA8CH1_CR_TXPERBITRANK3_REG                               (0x0000113C)

  #define DDRDATA8CH1_CR_TXPERBITRANK3_Lane0_OFF                       ( 0)
  #define DDRDATA8CH1_CR_TXPERBITRANK3_Lane0_WID                       ( 4)
  #define DDRDATA8CH1_CR_TXPERBITRANK3_Lane0_MSK                       (0x0000000F)
  #define DDRDATA8CH1_CR_TXPERBITRANK3_Lane0_MIN                       (0)
  #define DDRDATA8CH1_CR_TXPERBITRANK3_Lane0_MAX                       (15) // 0x0000000F
  #define DDRDATA8CH1_CR_TXPERBITRANK3_Lane0_DEF                       (0x00000000)
  #define DDRDATA8CH1_CR_TXPERBITRANK3_Lane0_HSH                       (0x0400113C)

  #define DDRDATA8CH1_CR_TXPERBITRANK3_Lane1_OFF                       ( 4)
  #define DDRDATA8CH1_CR_TXPERBITRANK3_Lane1_WID                       ( 4)
  #define DDRDATA8CH1_CR_TXPERBITRANK3_Lane1_MSK                       (0x000000F0)
  #define DDRDATA8CH1_CR_TXPERBITRANK3_Lane1_MIN                       (0)
  #define DDRDATA8CH1_CR_TXPERBITRANK3_Lane1_MAX                       (15) // 0x0000000F
  #define DDRDATA8CH1_CR_TXPERBITRANK3_Lane1_DEF                       (0x00000000)
  #define DDRDATA8CH1_CR_TXPERBITRANK3_Lane1_HSH                       (0x0404113C)

  #define DDRDATA8CH1_CR_TXPERBITRANK3_Lane2_OFF                       ( 8)
  #define DDRDATA8CH1_CR_TXPERBITRANK3_Lane2_WID                       ( 4)
  #define DDRDATA8CH1_CR_TXPERBITRANK3_Lane2_MSK                       (0x00000F00)
  #define DDRDATA8CH1_CR_TXPERBITRANK3_Lane2_MIN                       (0)
  #define DDRDATA8CH1_CR_TXPERBITRANK3_Lane2_MAX                       (15) // 0x0000000F
  #define DDRDATA8CH1_CR_TXPERBITRANK3_Lane2_DEF                       (0x00000000)
  #define DDRDATA8CH1_CR_TXPERBITRANK3_Lane2_HSH                       (0x0408113C)

  #define DDRDATA8CH1_CR_TXPERBITRANK3_Lane3_OFF                       (12)
  #define DDRDATA8CH1_CR_TXPERBITRANK3_Lane3_WID                       ( 4)
  #define DDRDATA8CH1_CR_TXPERBITRANK3_Lane3_MSK                       (0x0000F000)
  #define DDRDATA8CH1_CR_TXPERBITRANK3_Lane3_MIN                       (0)
  #define DDRDATA8CH1_CR_TXPERBITRANK3_Lane3_MAX                       (15) // 0x0000000F
  #define DDRDATA8CH1_CR_TXPERBITRANK3_Lane3_DEF                       (0x00000000)
  #define DDRDATA8CH1_CR_TXPERBITRANK3_Lane3_HSH                       (0x040C113C)

  #define DDRDATA8CH1_CR_TXPERBITRANK3_Lane4_OFF                       (16)
  #define DDRDATA8CH1_CR_TXPERBITRANK3_Lane4_WID                       ( 4)
  #define DDRDATA8CH1_CR_TXPERBITRANK3_Lane4_MSK                       (0x000F0000)
  #define DDRDATA8CH1_CR_TXPERBITRANK3_Lane4_MIN                       (0)
  #define DDRDATA8CH1_CR_TXPERBITRANK3_Lane4_MAX                       (15) // 0x0000000F
  #define DDRDATA8CH1_CR_TXPERBITRANK3_Lane4_DEF                       (0x00000000)
  #define DDRDATA8CH1_CR_TXPERBITRANK3_Lane4_HSH                       (0x0410113C)

  #define DDRDATA8CH1_CR_TXPERBITRANK3_Lane5_OFF                       (20)
  #define DDRDATA8CH1_CR_TXPERBITRANK3_Lane5_WID                       ( 4)
  #define DDRDATA8CH1_CR_TXPERBITRANK3_Lane5_MSK                       (0x00F00000)
  #define DDRDATA8CH1_CR_TXPERBITRANK3_Lane5_MIN                       (0)
  #define DDRDATA8CH1_CR_TXPERBITRANK3_Lane5_MAX                       (15) // 0x0000000F
  #define DDRDATA8CH1_CR_TXPERBITRANK3_Lane5_DEF                       (0x00000000)
  #define DDRDATA8CH1_CR_TXPERBITRANK3_Lane5_HSH                       (0x0414113C)

  #define DDRDATA8CH1_CR_TXPERBITRANK3_Lane6_OFF                       (24)
  #define DDRDATA8CH1_CR_TXPERBITRANK3_Lane6_WID                       ( 4)
  #define DDRDATA8CH1_CR_TXPERBITRANK3_Lane6_MSK                       (0x0F000000)
  #define DDRDATA8CH1_CR_TXPERBITRANK3_Lane6_MIN                       (0)
  #define DDRDATA8CH1_CR_TXPERBITRANK3_Lane6_MAX                       (15) // 0x0000000F
  #define DDRDATA8CH1_CR_TXPERBITRANK3_Lane6_DEF                       (0x00000000)
  #define DDRDATA8CH1_CR_TXPERBITRANK3_Lane6_HSH                       (0x0418113C)

  #define DDRDATA8CH1_CR_TXPERBITRANK3_Lane7_OFF                       (28)
  #define DDRDATA8CH1_CR_TXPERBITRANK3_Lane7_WID                       ( 4)
  #define DDRDATA8CH1_CR_TXPERBITRANK3_Lane7_MSK                       (0xF0000000)
  #define DDRDATA8CH1_CR_TXPERBITRANK3_Lane7_MIN                       (0)
  #define DDRDATA8CH1_CR_TXPERBITRANK3_Lane7_MAX                       (15) // 0x0000000F
  #define DDRDATA8CH1_CR_TXPERBITRANK3_Lane7_DEF                       (0x00000000)
  #define DDRDATA8CH1_CR_TXPERBITRANK3_Lane7_HSH                       (0x041C113C)

#define DDRDATA8CH1_CR_RCOMPDATA0_REG                                  (0x00001140)

  #define DDRDATA8CH1_CR_RCOMPDATA0_RcompDrvUp_OFF                     ( 0)
  #define DDRDATA8CH1_CR_RCOMPDATA0_RcompDrvUp_WID                     ( 6)
  #define DDRDATA8CH1_CR_RCOMPDATA0_RcompDrvUp_MSK                     (0x0000003F)
  #define DDRDATA8CH1_CR_RCOMPDATA0_RcompDrvUp_MIN                     (0)
  #define DDRDATA8CH1_CR_RCOMPDATA0_RcompDrvUp_MAX                     (63) // 0x0000003F
  #define DDRDATA8CH1_CR_RCOMPDATA0_RcompDrvUp_DEF                     (0x00000000)
  #define DDRDATA8CH1_CR_RCOMPDATA0_RcompDrvUp_HSH                     (0x06001140)

  #define DDRDATA8CH1_CR_RCOMPDATA0_Rsvd_OFF                           ( 6)
  #define DDRDATA8CH1_CR_RCOMPDATA0_Rsvd_WID                           ( 3)
  #define DDRDATA8CH1_CR_RCOMPDATA0_Rsvd_MSK                           (0x000001C0)
  #define DDRDATA8CH1_CR_RCOMPDATA0_Rsvd_MIN                           (0)
  #define DDRDATA8CH1_CR_RCOMPDATA0_Rsvd_MAX                           (7) // 0x00000007
  #define DDRDATA8CH1_CR_RCOMPDATA0_Rsvd_DEF                           (0x00000000)
  #define DDRDATA8CH1_CR_RCOMPDATA0_Rsvd_HSH                           (0x03061140)

  #define DDRDATA8CH1_CR_RCOMPDATA0_RcompDrvDown_OFF                   ( 9)
  #define DDRDATA8CH1_CR_RCOMPDATA0_RcompDrvDown_WID                   ( 6)
  #define DDRDATA8CH1_CR_RCOMPDATA0_RcompDrvDown_MSK                   (0x00007E00)
  #define DDRDATA8CH1_CR_RCOMPDATA0_RcompDrvDown_MIN                   (0)
  #define DDRDATA8CH1_CR_RCOMPDATA0_RcompDrvDown_MAX                   (63) // 0x0000003F
  #define DDRDATA8CH1_CR_RCOMPDATA0_RcompDrvDown_DEF                   (0x00000000)
  #define DDRDATA8CH1_CR_RCOMPDATA0_RcompDrvDown_HSH                   (0x06091140)

  #define DDRDATA8CH1_CR_RCOMPDATA0_VTComp_OFF                         (15)
  #define DDRDATA8CH1_CR_RCOMPDATA0_VTComp_WID                         ( 5)
  #define DDRDATA8CH1_CR_RCOMPDATA0_VTComp_MSK                         (0x000F8000)
  #define DDRDATA8CH1_CR_RCOMPDATA0_VTComp_MIN                         (0)
  #define DDRDATA8CH1_CR_RCOMPDATA0_VTComp_MAX                         (31) // 0x0000001F
  #define DDRDATA8CH1_CR_RCOMPDATA0_VTComp_DEF                         (0x00000000)
  #define DDRDATA8CH1_CR_RCOMPDATA0_VTComp_HSH                         (0x050F1140)

  #define DDRDATA8CH1_CR_RCOMPDATA0_SlewRateComp_OFF                   (20)
  #define DDRDATA8CH1_CR_RCOMPDATA0_SlewRateComp_WID                   ( 5)
  #define DDRDATA8CH1_CR_RCOMPDATA0_SlewRateComp_MSK                   (0x01F00000)
  #define DDRDATA8CH1_CR_RCOMPDATA0_SlewRateComp_MIN                   (0)
  #define DDRDATA8CH1_CR_RCOMPDATA0_SlewRateComp_MAX                   (31) // 0x0000001F
  #define DDRDATA8CH1_CR_RCOMPDATA0_SlewRateComp_DEF                   (0x00000000)
  #define DDRDATA8CH1_CR_RCOMPDATA0_SlewRateComp_HSH                   (0x05141140)

  #define DDRDATA8CH1_CR_RCOMPDATA0_Spare0_OFF                         (25)
  #define DDRDATA8CH1_CR_RCOMPDATA0_Spare0_WID                         ( 1)
  #define DDRDATA8CH1_CR_RCOMPDATA0_Spare0_MSK                         (0x02000000)
  #define DDRDATA8CH1_CR_RCOMPDATA0_Spare0_MIN                         (0)
  #define DDRDATA8CH1_CR_RCOMPDATA0_Spare0_MAX                         (1) // 0x00000001
  #define DDRDATA8CH1_CR_RCOMPDATA0_Spare0_DEF                         (0x00000000)
  #define DDRDATA8CH1_CR_RCOMPDATA0_Spare0_HSH                         (0x01191140)

  #define DDRDATA8CH1_CR_RCOMPDATA0_TcoComp_OFF                        (26)
  #define DDRDATA8CH1_CR_RCOMPDATA0_TcoComp_WID                        ( 6)
  #define DDRDATA8CH1_CR_RCOMPDATA0_TcoComp_MSK                        (0xFC000000)
  #define DDRDATA8CH1_CR_RCOMPDATA0_TcoComp_MIN                        (0)
  #define DDRDATA8CH1_CR_RCOMPDATA0_TcoComp_MAX                        (63) // 0x0000003F
  #define DDRDATA8CH1_CR_RCOMPDATA0_TcoComp_DEF                        (0x00000000)
  #define DDRDATA8CH1_CR_RCOMPDATA0_TcoComp_HSH                        (0x061A1140)

#define DDRDATA8CH1_CR_RCOMPDATA1_REG                                  (0x00001144)

  #define DDRDATA8CH1_CR_RCOMPDATA1_RcompOdtUp_OFF                     ( 0)
  #define DDRDATA8CH1_CR_RCOMPDATA1_RcompOdtUp_WID                     ( 6)
  #define DDRDATA8CH1_CR_RCOMPDATA1_RcompOdtUp_MSK                     (0x0000003F)
  #define DDRDATA8CH1_CR_RCOMPDATA1_RcompOdtUp_MIN                     (0)
  #define DDRDATA8CH1_CR_RCOMPDATA1_RcompOdtUp_MAX                     (63) // 0x0000003F
  #define DDRDATA8CH1_CR_RCOMPDATA1_RcompOdtUp_DEF                     (0x00000000)
  #define DDRDATA8CH1_CR_RCOMPDATA1_RcompOdtUp_HSH                     (0x06001144)

  #define DDRDATA8CH1_CR_RCOMPDATA1_PanicDrvDn_OFF                     ( 6)
  #define DDRDATA8CH1_CR_RCOMPDATA1_PanicDrvDn_WID                     (10)
  #define DDRDATA8CH1_CR_RCOMPDATA1_PanicDrvDn_MSK                     (0x0000FFC0)
  #define DDRDATA8CH1_CR_RCOMPDATA1_PanicDrvDn_MIN                     (0)
  #define DDRDATA8CH1_CR_RCOMPDATA1_PanicDrvDn_MAX                     (1023) // 0x000003FF
  #define DDRDATA8CH1_CR_RCOMPDATA1_PanicDrvDn_DEF                     (0x00000000)
  #define DDRDATA8CH1_CR_RCOMPDATA1_PanicDrvDn_HSH                     (0x0A061144)

  #define DDRDATA8CH1_CR_RCOMPDATA1_PanicDrvUp_OFF                     (16)
  #define DDRDATA8CH1_CR_RCOMPDATA1_PanicDrvUp_WID                     (10)
  #define DDRDATA8CH1_CR_RCOMPDATA1_PanicDrvUp_MSK                     (0x03FF0000)
  #define DDRDATA8CH1_CR_RCOMPDATA1_PanicDrvUp_MIN                     (0)
  #define DDRDATA8CH1_CR_RCOMPDATA1_PanicDrvUp_MAX                     (1023) // 0x000003FF
  #define DDRDATA8CH1_CR_RCOMPDATA1_PanicDrvUp_DEF                     (0x00000000)
  #define DDRDATA8CH1_CR_RCOMPDATA1_PanicDrvUp_HSH                     (0x0A101144)

  #define DDRDATA8CH1_CR_RCOMPDATA1_RcompOdtDown_OFF                   (26)
  #define DDRDATA8CH1_CR_RCOMPDATA1_RcompOdtDown_WID                   ( 6)
  #define DDRDATA8CH1_CR_RCOMPDATA1_RcompOdtDown_MSK                   (0xFC000000)
  #define DDRDATA8CH1_CR_RCOMPDATA1_RcompOdtDown_MIN                   (0)
  #define DDRDATA8CH1_CR_RCOMPDATA1_RcompOdtDown_MAX                   (63) // 0x0000003F
  #define DDRDATA8CH1_CR_RCOMPDATA1_RcompOdtDown_DEF                   (0x00000000)
  #define DDRDATA8CH1_CR_RCOMPDATA1_RcompOdtDown_HSH                   (0x061A1144)

#define DDRDATA8CH1_CR_TXXTALK_REG                                     (0x00001148)

  #define DDRDATA8CH1_CR_TXXTALK_Lane0_OFF                             ( 0)
  #define DDRDATA8CH1_CR_TXXTALK_Lane0_WID                             ( 4)
  #define DDRDATA8CH1_CR_TXXTALK_Lane0_MSK                             (0x0000000F)
  #define DDRDATA8CH1_CR_TXXTALK_Lane0_MIN                             (-8)
  #define DDRDATA8CH1_CR_TXXTALK_Lane0_MAX                             (7) // 0x00000007
  #define DDRDATA8CH1_CR_TXXTALK_Lane0_DEF                             (0x00000000)
  #define DDRDATA8CH1_CR_TXXTALK_Lane0_HSH                             (0x84001148)

  #define DDRDATA8CH1_CR_TXXTALK_Lane1_OFF                             ( 4)
  #define DDRDATA8CH1_CR_TXXTALK_Lane1_WID                             ( 4)
  #define DDRDATA8CH1_CR_TXXTALK_Lane1_MSK                             (0x000000F0)
  #define DDRDATA8CH1_CR_TXXTALK_Lane1_MIN                             (-8)
  #define DDRDATA8CH1_CR_TXXTALK_Lane1_MAX                             (7) // 0x00000007
  #define DDRDATA8CH1_CR_TXXTALK_Lane1_DEF                             (0x00000000)
  #define DDRDATA8CH1_CR_TXXTALK_Lane1_HSH                             (0x84041148)

  #define DDRDATA8CH1_CR_TXXTALK_Lane2_OFF                             ( 8)
  #define DDRDATA8CH1_CR_TXXTALK_Lane2_WID                             ( 4)
  #define DDRDATA8CH1_CR_TXXTALK_Lane2_MSK                             (0x00000F00)
  #define DDRDATA8CH1_CR_TXXTALK_Lane2_MIN                             (-8)
  #define DDRDATA8CH1_CR_TXXTALK_Lane2_MAX                             (7) // 0x00000007
  #define DDRDATA8CH1_CR_TXXTALK_Lane2_DEF                             (0x00000000)
  #define DDRDATA8CH1_CR_TXXTALK_Lane2_HSH                             (0x84081148)

  #define DDRDATA8CH1_CR_TXXTALK_Lane3_OFF                             (12)
  #define DDRDATA8CH1_CR_TXXTALK_Lane3_WID                             ( 4)
  #define DDRDATA8CH1_CR_TXXTALK_Lane3_MSK                             (0x0000F000)
  #define DDRDATA8CH1_CR_TXXTALK_Lane3_MIN                             (-8)
  #define DDRDATA8CH1_CR_TXXTALK_Lane3_MAX                             (7) // 0x00000007
  #define DDRDATA8CH1_CR_TXXTALK_Lane3_DEF                             (0x00000000)
  #define DDRDATA8CH1_CR_TXXTALK_Lane3_HSH                             (0x840C1148)

  #define DDRDATA8CH1_CR_TXXTALK_Lane4_OFF                             (16)
  #define DDRDATA8CH1_CR_TXXTALK_Lane4_WID                             ( 4)
  #define DDRDATA8CH1_CR_TXXTALK_Lane4_MSK                             (0x000F0000)
  #define DDRDATA8CH1_CR_TXXTALK_Lane4_MIN                             (-8)
  #define DDRDATA8CH1_CR_TXXTALK_Lane4_MAX                             (7) // 0x00000007
  #define DDRDATA8CH1_CR_TXXTALK_Lane4_DEF                             (0x00000000)
  #define DDRDATA8CH1_CR_TXXTALK_Lane4_HSH                             (0x84101148)

  #define DDRDATA8CH1_CR_TXXTALK_Lane5_OFF                             (20)
  #define DDRDATA8CH1_CR_TXXTALK_Lane5_WID                             ( 4)
  #define DDRDATA8CH1_CR_TXXTALK_Lane5_MSK                             (0x00F00000)
  #define DDRDATA8CH1_CR_TXXTALK_Lane5_MIN                             (-8)
  #define DDRDATA8CH1_CR_TXXTALK_Lane5_MAX                             (7) // 0x00000007
  #define DDRDATA8CH1_CR_TXXTALK_Lane5_DEF                             (0x00000000)
  #define DDRDATA8CH1_CR_TXXTALK_Lane5_HSH                             (0x84141148)

  #define DDRDATA8CH1_CR_TXXTALK_Lane6_OFF                             (24)
  #define DDRDATA8CH1_CR_TXXTALK_Lane6_WID                             ( 4)
  #define DDRDATA8CH1_CR_TXXTALK_Lane6_MSK                             (0x0F000000)
  #define DDRDATA8CH1_CR_TXXTALK_Lane6_MIN                             (-8)
  #define DDRDATA8CH1_CR_TXXTALK_Lane6_MAX                             (7) // 0x00000007
  #define DDRDATA8CH1_CR_TXXTALK_Lane6_DEF                             (0x00000000)
  #define DDRDATA8CH1_CR_TXXTALK_Lane6_HSH                             (0x84181148)

  #define DDRDATA8CH1_CR_TXXTALK_Lane7_OFF                             (28)
  #define DDRDATA8CH1_CR_TXXTALK_Lane7_WID                             ( 4)
  #define DDRDATA8CH1_CR_TXXTALK_Lane7_MSK                             (0xF0000000)
  #define DDRDATA8CH1_CR_TXXTALK_Lane7_MIN                             (-8)
  #define DDRDATA8CH1_CR_TXXTALK_Lane7_MAX                             (7) // 0x00000007
  #define DDRDATA8CH1_CR_TXXTALK_Lane7_DEF                             (0x00000000)
  #define DDRDATA8CH1_CR_TXXTALK_Lane7_HSH                             (0x841C1148)

#define DDRDATA8CH1_CR_RCOMPDATA2_REG                                  (0x0000114C)

  #define DDRDATA8CH1_CR_RCOMPDATA2_VttPanicUp_OFF                     ( 0)
  #define DDRDATA8CH1_CR_RCOMPDATA2_VttPanicUp_WID                     ( 8)
  #define DDRDATA8CH1_CR_RCOMPDATA2_VttPanicUp_MSK                     (0x000000FF)
  #define DDRDATA8CH1_CR_RCOMPDATA2_VttPanicUp_MIN                     (0)
  #define DDRDATA8CH1_CR_RCOMPDATA2_VttPanicUp_MAX                     (255) // 0x000000FF
  #define DDRDATA8CH1_CR_RCOMPDATA2_VttPanicUp_DEF                     (0x00000000)
  #define DDRDATA8CH1_CR_RCOMPDATA2_VttPanicUp_HSH                     (0x0800114C)

  #define DDRDATA8CH1_CR_RCOMPDATA2_VttPanicDn_OFF                     ( 8)
  #define DDRDATA8CH1_CR_RCOMPDATA2_VttPanicDn_WID                     ( 8)
  #define DDRDATA8CH1_CR_RCOMPDATA2_VttPanicDn_MSK                     (0x0000FF00)
  #define DDRDATA8CH1_CR_RCOMPDATA2_VttPanicDn_MIN                     (0)
  #define DDRDATA8CH1_CR_RCOMPDATA2_VttPanicDn_MAX                     (255) // 0x000000FF
  #define DDRDATA8CH1_CR_RCOMPDATA2_VttPanicDn_DEF                     (0x00000000)
  #define DDRDATA8CH1_CR_RCOMPDATA2_VttPanicDn_HSH                     (0x0808114C)

  #define DDRDATA8CH1_CR_RCOMPDATA2_Spare_OFF                          (16)
  #define DDRDATA8CH1_CR_RCOMPDATA2_Spare_WID                          (16)
  #define DDRDATA8CH1_CR_RCOMPDATA2_Spare_MSK                          (0xFFFF0000)
  #define DDRDATA8CH1_CR_RCOMPDATA2_Spare_MIN                          (0)
  #define DDRDATA8CH1_CR_RCOMPDATA2_Spare_MAX                          (65535) // 0x0000FFFF
  #define DDRDATA8CH1_CR_RCOMPDATA2_Spare_DEF                          (0x00000000)
  #define DDRDATA8CH1_CR_RCOMPDATA2_Spare_HSH                          (0x1010114C)

#define DDRDATA8CH1_CR_RXOFFSETVDQRANK0_REG                            (0x00001150)

  #define DDRDATA8CH1_CR_RXOFFSETVDQRANK0_Lane0_OFF                    ( 0)
  #define DDRDATA8CH1_CR_RXOFFSETVDQRANK0_Lane0_WID                    ( 4)
  #define DDRDATA8CH1_CR_RXOFFSETVDQRANK0_Lane0_MSK                    (0x0000000F)
  #define DDRDATA8CH1_CR_RXOFFSETVDQRANK0_Lane0_MIN                    (0)
  #define DDRDATA8CH1_CR_RXOFFSETVDQRANK0_Lane0_MAX                    (15) // 0x0000000F
  #define DDRDATA8CH1_CR_RXOFFSETVDQRANK0_Lane0_DEF                    (0x00000000)
  #define DDRDATA8CH1_CR_RXOFFSETVDQRANK0_Lane0_HSH                    (0x04001150)

  #define DDRDATA8CH1_CR_RXOFFSETVDQRANK0_Lane1_OFF                    ( 4)
  #define DDRDATA8CH1_CR_RXOFFSETVDQRANK0_Lane1_WID                    ( 4)
  #define DDRDATA8CH1_CR_RXOFFSETVDQRANK0_Lane1_MSK                    (0x000000F0)
  #define DDRDATA8CH1_CR_RXOFFSETVDQRANK0_Lane1_MIN                    (0)
  #define DDRDATA8CH1_CR_RXOFFSETVDQRANK0_Lane1_MAX                    (15) // 0x0000000F
  #define DDRDATA8CH1_CR_RXOFFSETVDQRANK0_Lane1_DEF                    (0x00000000)
  #define DDRDATA8CH1_CR_RXOFFSETVDQRANK0_Lane1_HSH                    (0x04041150)

  #define DDRDATA8CH1_CR_RXOFFSETVDQRANK0_Lane2_OFF                    ( 8)
  #define DDRDATA8CH1_CR_RXOFFSETVDQRANK0_Lane2_WID                    ( 4)
  #define DDRDATA8CH1_CR_RXOFFSETVDQRANK0_Lane2_MSK                    (0x00000F00)
  #define DDRDATA8CH1_CR_RXOFFSETVDQRANK0_Lane2_MIN                    (0)
  #define DDRDATA8CH1_CR_RXOFFSETVDQRANK0_Lane2_MAX                    (15) // 0x0000000F
  #define DDRDATA8CH1_CR_RXOFFSETVDQRANK0_Lane2_DEF                    (0x00000000)
  #define DDRDATA8CH1_CR_RXOFFSETVDQRANK0_Lane2_HSH                    (0x04081150)

  #define DDRDATA8CH1_CR_RXOFFSETVDQRANK0_Lane3_OFF                    (12)
  #define DDRDATA8CH1_CR_RXOFFSETVDQRANK0_Lane3_WID                    ( 4)
  #define DDRDATA8CH1_CR_RXOFFSETVDQRANK0_Lane3_MSK                    (0x0000F000)
  #define DDRDATA8CH1_CR_RXOFFSETVDQRANK0_Lane3_MIN                    (0)
  #define DDRDATA8CH1_CR_RXOFFSETVDQRANK0_Lane3_MAX                    (15) // 0x0000000F
  #define DDRDATA8CH1_CR_RXOFFSETVDQRANK0_Lane3_DEF                    (0x00000000)
  #define DDRDATA8CH1_CR_RXOFFSETVDQRANK0_Lane3_HSH                    (0x040C1150)

  #define DDRDATA8CH1_CR_RXOFFSETVDQRANK0_Lane4_OFF                    (16)
  #define DDRDATA8CH1_CR_RXOFFSETVDQRANK0_Lane4_WID                    ( 4)
  #define DDRDATA8CH1_CR_RXOFFSETVDQRANK0_Lane4_MSK                    (0x000F0000)
  #define DDRDATA8CH1_CR_RXOFFSETVDQRANK0_Lane4_MIN                    (0)
  #define DDRDATA8CH1_CR_RXOFFSETVDQRANK0_Lane4_MAX                    (15) // 0x0000000F
  #define DDRDATA8CH1_CR_RXOFFSETVDQRANK0_Lane4_DEF                    (0x00000000)
  #define DDRDATA8CH1_CR_RXOFFSETVDQRANK0_Lane4_HSH                    (0x04101150)

  #define DDRDATA8CH1_CR_RXOFFSETVDQRANK0_Lane5_OFF                    (20)
  #define DDRDATA8CH1_CR_RXOFFSETVDQRANK0_Lane5_WID                    ( 4)
  #define DDRDATA8CH1_CR_RXOFFSETVDQRANK0_Lane5_MSK                    (0x00F00000)
  #define DDRDATA8CH1_CR_RXOFFSETVDQRANK0_Lane5_MIN                    (0)
  #define DDRDATA8CH1_CR_RXOFFSETVDQRANK0_Lane5_MAX                    (15) // 0x0000000F
  #define DDRDATA8CH1_CR_RXOFFSETVDQRANK0_Lane5_DEF                    (0x00000000)
  #define DDRDATA8CH1_CR_RXOFFSETVDQRANK0_Lane5_HSH                    (0x04141150)

  #define DDRDATA8CH1_CR_RXOFFSETVDQRANK0_Lane6_OFF                    (24)
  #define DDRDATA8CH1_CR_RXOFFSETVDQRANK0_Lane6_WID                    ( 4)
  #define DDRDATA8CH1_CR_RXOFFSETVDQRANK0_Lane6_MSK                    (0x0F000000)
  #define DDRDATA8CH1_CR_RXOFFSETVDQRANK0_Lane6_MIN                    (0)
  #define DDRDATA8CH1_CR_RXOFFSETVDQRANK0_Lane6_MAX                    (15) // 0x0000000F
  #define DDRDATA8CH1_CR_RXOFFSETVDQRANK0_Lane6_DEF                    (0x00000000)
  #define DDRDATA8CH1_CR_RXOFFSETVDQRANK0_Lane6_HSH                    (0x04181150)

  #define DDRDATA8CH1_CR_RXOFFSETVDQRANK0_Lane7_OFF                    (28)
  #define DDRDATA8CH1_CR_RXOFFSETVDQRANK0_Lane7_WID                    ( 4)
  #define DDRDATA8CH1_CR_RXOFFSETVDQRANK0_Lane7_MSK                    (0xF0000000)
  #define DDRDATA8CH1_CR_RXOFFSETVDQRANK0_Lane7_MIN                    (0)
  #define DDRDATA8CH1_CR_RXOFFSETVDQRANK0_Lane7_MAX                    (15) // 0x0000000F
  #define DDRDATA8CH1_CR_RXOFFSETVDQRANK0_Lane7_DEF                    (0x00000000)
  #define DDRDATA8CH1_CR_RXOFFSETVDQRANK0_Lane7_HSH                    (0x041C1150)

#define DDRDATA8CH1_CR_RXOFFSETVDQRANK1_REG                            (0x00001154)

  #define DDRDATA8CH1_CR_RXOFFSETVDQRANK1_Lane0_OFF                    ( 0)
  #define DDRDATA8CH1_CR_RXOFFSETVDQRANK1_Lane0_WID                    ( 4)
  #define DDRDATA8CH1_CR_RXOFFSETVDQRANK1_Lane0_MSK                    (0x0000000F)
  #define DDRDATA8CH1_CR_RXOFFSETVDQRANK1_Lane0_MIN                    (0)
  #define DDRDATA8CH1_CR_RXOFFSETVDQRANK1_Lane0_MAX                    (15) // 0x0000000F
  #define DDRDATA8CH1_CR_RXOFFSETVDQRANK1_Lane0_DEF                    (0x00000000)
  #define DDRDATA8CH1_CR_RXOFFSETVDQRANK1_Lane0_HSH                    (0x04001154)

  #define DDRDATA8CH1_CR_RXOFFSETVDQRANK1_Lane1_OFF                    ( 4)
  #define DDRDATA8CH1_CR_RXOFFSETVDQRANK1_Lane1_WID                    ( 4)
  #define DDRDATA8CH1_CR_RXOFFSETVDQRANK1_Lane1_MSK                    (0x000000F0)
  #define DDRDATA8CH1_CR_RXOFFSETVDQRANK1_Lane1_MIN                    (0)
  #define DDRDATA8CH1_CR_RXOFFSETVDQRANK1_Lane1_MAX                    (15) // 0x0000000F
  #define DDRDATA8CH1_CR_RXOFFSETVDQRANK1_Lane1_DEF                    (0x00000000)
  #define DDRDATA8CH1_CR_RXOFFSETVDQRANK1_Lane1_HSH                    (0x04041154)

  #define DDRDATA8CH1_CR_RXOFFSETVDQRANK1_Lane2_OFF                    ( 8)
  #define DDRDATA8CH1_CR_RXOFFSETVDQRANK1_Lane2_WID                    ( 4)
  #define DDRDATA8CH1_CR_RXOFFSETVDQRANK1_Lane2_MSK                    (0x00000F00)
  #define DDRDATA8CH1_CR_RXOFFSETVDQRANK1_Lane2_MIN                    (0)
  #define DDRDATA8CH1_CR_RXOFFSETVDQRANK1_Lane2_MAX                    (15) // 0x0000000F
  #define DDRDATA8CH1_CR_RXOFFSETVDQRANK1_Lane2_DEF                    (0x00000000)
  #define DDRDATA8CH1_CR_RXOFFSETVDQRANK1_Lane2_HSH                    (0x04081154)

  #define DDRDATA8CH1_CR_RXOFFSETVDQRANK1_Lane3_OFF                    (12)
  #define DDRDATA8CH1_CR_RXOFFSETVDQRANK1_Lane3_WID                    ( 4)
  #define DDRDATA8CH1_CR_RXOFFSETVDQRANK1_Lane3_MSK                    (0x0000F000)
  #define DDRDATA8CH1_CR_RXOFFSETVDQRANK1_Lane3_MIN                    (0)
  #define DDRDATA8CH1_CR_RXOFFSETVDQRANK1_Lane3_MAX                    (15) // 0x0000000F
  #define DDRDATA8CH1_CR_RXOFFSETVDQRANK1_Lane3_DEF                    (0x00000000)
  #define DDRDATA8CH1_CR_RXOFFSETVDQRANK1_Lane3_HSH                    (0x040C1154)

  #define DDRDATA8CH1_CR_RXOFFSETVDQRANK1_Lane4_OFF                    (16)
  #define DDRDATA8CH1_CR_RXOFFSETVDQRANK1_Lane4_WID                    ( 4)
  #define DDRDATA8CH1_CR_RXOFFSETVDQRANK1_Lane4_MSK                    (0x000F0000)
  #define DDRDATA8CH1_CR_RXOFFSETVDQRANK1_Lane4_MIN                    (0)
  #define DDRDATA8CH1_CR_RXOFFSETVDQRANK1_Lane4_MAX                    (15) // 0x0000000F
  #define DDRDATA8CH1_CR_RXOFFSETVDQRANK1_Lane4_DEF                    (0x00000000)
  #define DDRDATA8CH1_CR_RXOFFSETVDQRANK1_Lane4_HSH                    (0x04101154)

  #define DDRDATA8CH1_CR_RXOFFSETVDQRANK1_Lane5_OFF                    (20)
  #define DDRDATA8CH1_CR_RXOFFSETVDQRANK1_Lane5_WID                    ( 4)
  #define DDRDATA8CH1_CR_RXOFFSETVDQRANK1_Lane5_MSK                    (0x00F00000)
  #define DDRDATA8CH1_CR_RXOFFSETVDQRANK1_Lane5_MIN                    (0)
  #define DDRDATA8CH1_CR_RXOFFSETVDQRANK1_Lane5_MAX                    (15) // 0x0000000F
  #define DDRDATA8CH1_CR_RXOFFSETVDQRANK1_Lane5_DEF                    (0x00000000)
  #define DDRDATA8CH1_CR_RXOFFSETVDQRANK1_Lane5_HSH                    (0x04141154)

  #define DDRDATA8CH1_CR_RXOFFSETVDQRANK1_Lane6_OFF                    (24)
  #define DDRDATA8CH1_CR_RXOFFSETVDQRANK1_Lane6_WID                    ( 4)
  #define DDRDATA8CH1_CR_RXOFFSETVDQRANK1_Lane6_MSK                    (0x0F000000)
  #define DDRDATA8CH1_CR_RXOFFSETVDQRANK1_Lane6_MIN                    (0)
  #define DDRDATA8CH1_CR_RXOFFSETVDQRANK1_Lane6_MAX                    (15) // 0x0000000F
  #define DDRDATA8CH1_CR_RXOFFSETVDQRANK1_Lane6_DEF                    (0x00000000)
  #define DDRDATA8CH1_CR_RXOFFSETVDQRANK1_Lane6_HSH                    (0x04181154)

  #define DDRDATA8CH1_CR_RXOFFSETVDQRANK1_Lane7_OFF                    (28)
  #define DDRDATA8CH1_CR_RXOFFSETVDQRANK1_Lane7_WID                    ( 4)
  #define DDRDATA8CH1_CR_RXOFFSETVDQRANK1_Lane7_MSK                    (0xF0000000)
  #define DDRDATA8CH1_CR_RXOFFSETVDQRANK1_Lane7_MIN                    (0)
  #define DDRDATA8CH1_CR_RXOFFSETVDQRANK1_Lane7_MAX                    (15) // 0x0000000F
  #define DDRDATA8CH1_CR_RXOFFSETVDQRANK1_Lane7_DEF                    (0x00000000)
  #define DDRDATA8CH1_CR_RXOFFSETVDQRANK1_Lane7_HSH                    (0x041C1154)

#define DDRDATA8CH1_CR_RXOFFSETVDQRANK2_REG                            (0x00001158)

  #define DDRDATA8CH1_CR_RXOFFSETVDQRANK2_Lane0_OFF                    ( 0)
  #define DDRDATA8CH1_CR_RXOFFSETVDQRANK2_Lane0_WID                    ( 4)
  #define DDRDATA8CH1_CR_RXOFFSETVDQRANK2_Lane0_MSK                    (0x0000000F)
  #define DDRDATA8CH1_CR_RXOFFSETVDQRANK2_Lane0_MIN                    (0)
  #define DDRDATA8CH1_CR_RXOFFSETVDQRANK2_Lane0_MAX                    (15) // 0x0000000F
  #define DDRDATA8CH1_CR_RXOFFSETVDQRANK2_Lane0_DEF                    (0x00000000)
  #define DDRDATA8CH1_CR_RXOFFSETVDQRANK2_Lane0_HSH                    (0x04001158)

  #define DDRDATA8CH1_CR_RXOFFSETVDQRANK2_Lane1_OFF                    ( 4)
  #define DDRDATA8CH1_CR_RXOFFSETVDQRANK2_Lane1_WID                    ( 4)
  #define DDRDATA8CH1_CR_RXOFFSETVDQRANK2_Lane1_MSK                    (0x000000F0)
  #define DDRDATA8CH1_CR_RXOFFSETVDQRANK2_Lane1_MIN                    (0)
  #define DDRDATA8CH1_CR_RXOFFSETVDQRANK2_Lane1_MAX                    (15) // 0x0000000F
  #define DDRDATA8CH1_CR_RXOFFSETVDQRANK2_Lane1_DEF                    (0x00000000)
  #define DDRDATA8CH1_CR_RXOFFSETVDQRANK2_Lane1_HSH                    (0x04041158)

  #define DDRDATA8CH1_CR_RXOFFSETVDQRANK2_Lane2_OFF                    ( 8)
  #define DDRDATA8CH1_CR_RXOFFSETVDQRANK2_Lane2_WID                    ( 4)
  #define DDRDATA8CH1_CR_RXOFFSETVDQRANK2_Lane2_MSK                    (0x00000F00)
  #define DDRDATA8CH1_CR_RXOFFSETVDQRANK2_Lane2_MIN                    (0)
  #define DDRDATA8CH1_CR_RXOFFSETVDQRANK2_Lane2_MAX                    (15) // 0x0000000F
  #define DDRDATA8CH1_CR_RXOFFSETVDQRANK2_Lane2_DEF                    (0x00000000)
  #define DDRDATA8CH1_CR_RXOFFSETVDQRANK2_Lane2_HSH                    (0x04081158)

  #define DDRDATA8CH1_CR_RXOFFSETVDQRANK2_Lane3_OFF                    (12)
  #define DDRDATA8CH1_CR_RXOFFSETVDQRANK2_Lane3_WID                    ( 4)
  #define DDRDATA8CH1_CR_RXOFFSETVDQRANK2_Lane3_MSK                    (0x0000F000)
  #define DDRDATA8CH1_CR_RXOFFSETVDQRANK2_Lane3_MIN                    (0)
  #define DDRDATA8CH1_CR_RXOFFSETVDQRANK2_Lane3_MAX                    (15) // 0x0000000F
  #define DDRDATA8CH1_CR_RXOFFSETVDQRANK2_Lane3_DEF                    (0x00000000)
  #define DDRDATA8CH1_CR_RXOFFSETVDQRANK2_Lane3_HSH                    (0x040C1158)

  #define DDRDATA8CH1_CR_RXOFFSETVDQRANK2_Lane4_OFF                    (16)
  #define DDRDATA8CH1_CR_RXOFFSETVDQRANK2_Lane4_WID                    ( 4)
  #define DDRDATA8CH1_CR_RXOFFSETVDQRANK2_Lane4_MSK                    (0x000F0000)
  #define DDRDATA8CH1_CR_RXOFFSETVDQRANK2_Lane4_MIN                    (0)
  #define DDRDATA8CH1_CR_RXOFFSETVDQRANK2_Lane4_MAX                    (15) // 0x0000000F
  #define DDRDATA8CH1_CR_RXOFFSETVDQRANK2_Lane4_DEF                    (0x00000000)
  #define DDRDATA8CH1_CR_RXOFFSETVDQRANK2_Lane4_HSH                    (0x04101158)

  #define DDRDATA8CH1_CR_RXOFFSETVDQRANK2_Lane5_OFF                    (20)
  #define DDRDATA8CH1_CR_RXOFFSETVDQRANK2_Lane5_WID                    ( 4)
  #define DDRDATA8CH1_CR_RXOFFSETVDQRANK2_Lane5_MSK                    (0x00F00000)
  #define DDRDATA8CH1_CR_RXOFFSETVDQRANK2_Lane5_MIN                    (0)
  #define DDRDATA8CH1_CR_RXOFFSETVDQRANK2_Lane5_MAX                    (15) // 0x0000000F
  #define DDRDATA8CH1_CR_RXOFFSETVDQRANK2_Lane5_DEF                    (0x00000000)
  #define DDRDATA8CH1_CR_RXOFFSETVDQRANK2_Lane5_HSH                    (0x04141158)

  #define DDRDATA8CH1_CR_RXOFFSETVDQRANK2_Lane6_OFF                    (24)
  #define DDRDATA8CH1_CR_RXOFFSETVDQRANK2_Lane6_WID                    ( 4)
  #define DDRDATA8CH1_CR_RXOFFSETVDQRANK2_Lane6_MSK                    (0x0F000000)
  #define DDRDATA8CH1_CR_RXOFFSETVDQRANK2_Lane6_MIN                    (0)
  #define DDRDATA8CH1_CR_RXOFFSETVDQRANK2_Lane6_MAX                    (15) // 0x0000000F
  #define DDRDATA8CH1_CR_RXOFFSETVDQRANK2_Lane6_DEF                    (0x00000000)
  #define DDRDATA8CH1_CR_RXOFFSETVDQRANK2_Lane6_HSH                    (0x04181158)

  #define DDRDATA8CH1_CR_RXOFFSETVDQRANK2_Lane7_OFF                    (28)
  #define DDRDATA8CH1_CR_RXOFFSETVDQRANK2_Lane7_WID                    ( 4)
  #define DDRDATA8CH1_CR_RXOFFSETVDQRANK2_Lane7_MSK                    (0xF0000000)
  #define DDRDATA8CH1_CR_RXOFFSETVDQRANK2_Lane7_MIN                    (0)
  #define DDRDATA8CH1_CR_RXOFFSETVDQRANK2_Lane7_MAX                    (15) // 0x0000000F
  #define DDRDATA8CH1_CR_RXOFFSETVDQRANK2_Lane7_DEF                    (0x00000000)
  #define DDRDATA8CH1_CR_RXOFFSETVDQRANK2_Lane7_HSH                    (0x041C1158)

#define DDRDATA8CH1_CR_RXOFFSETVDQRANK3_REG                            (0x0000115C)

  #define DDRDATA8CH1_CR_RXOFFSETVDQRANK3_Lane0_OFF                    ( 0)
  #define DDRDATA8CH1_CR_RXOFFSETVDQRANK3_Lane0_WID                    ( 4)
  #define DDRDATA8CH1_CR_RXOFFSETVDQRANK3_Lane0_MSK                    (0x0000000F)
  #define DDRDATA8CH1_CR_RXOFFSETVDQRANK3_Lane0_MIN                    (0)
  #define DDRDATA8CH1_CR_RXOFFSETVDQRANK3_Lane0_MAX                    (15) // 0x0000000F
  #define DDRDATA8CH1_CR_RXOFFSETVDQRANK3_Lane0_DEF                    (0x00000000)
  #define DDRDATA8CH1_CR_RXOFFSETVDQRANK3_Lane0_HSH                    (0x0400115C)

  #define DDRDATA8CH1_CR_RXOFFSETVDQRANK3_Lane1_OFF                    ( 4)
  #define DDRDATA8CH1_CR_RXOFFSETVDQRANK3_Lane1_WID                    ( 4)
  #define DDRDATA8CH1_CR_RXOFFSETVDQRANK3_Lane1_MSK                    (0x000000F0)
  #define DDRDATA8CH1_CR_RXOFFSETVDQRANK3_Lane1_MIN                    (0)
  #define DDRDATA8CH1_CR_RXOFFSETVDQRANK3_Lane1_MAX                    (15) // 0x0000000F
  #define DDRDATA8CH1_CR_RXOFFSETVDQRANK3_Lane1_DEF                    (0x00000000)
  #define DDRDATA8CH1_CR_RXOFFSETVDQRANK3_Lane1_HSH                    (0x0404115C)

  #define DDRDATA8CH1_CR_RXOFFSETVDQRANK3_Lane2_OFF                    ( 8)
  #define DDRDATA8CH1_CR_RXOFFSETVDQRANK3_Lane2_WID                    ( 4)
  #define DDRDATA8CH1_CR_RXOFFSETVDQRANK3_Lane2_MSK                    (0x00000F00)
  #define DDRDATA8CH1_CR_RXOFFSETVDQRANK3_Lane2_MIN                    (0)
  #define DDRDATA8CH1_CR_RXOFFSETVDQRANK3_Lane2_MAX                    (15) // 0x0000000F
  #define DDRDATA8CH1_CR_RXOFFSETVDQRANK3_Lane2_DEF                    (0x00000000)
  #define DDRDATA8CH1_CR_RXOFFSETVDQRANK3_Lane2_HSH                    (0x0408115C)

  #define DDRDATA8CH1_CR_RXOFFSETVDQRANK3_Lane3_OFF                    (12)
  #define DDRDATA8CH1_CR_RXOFFSETVDQRANK3_Lane3_WID                    ( 4)
  #define DDRDATA8CH1_CR_RXOFFSETVDQRANK3_Lane3_MSK                    (0x0000F000)
  #define DDRDATA8CH1_CR_RXOFFSETVDQRANK3_Lane3_MIN                    (0)
  #define DDRDATA8CH1_CR_RXOFFSETVDQRANK3_Lane3_MAX                    (15) // 0x0000000F
  #define DDRDATA8CH1_CR_RXOFFSETVDQRANK3_Lane3_DEF                    (0x00000000)
  #define DDRDATA8CH1_CR_RXOFFSETVDQRANK3_Lane3_HSH                    (0x040C115C)

  #define DDRDATA8CH1_CR_RXOFFSETVDQRANK3_Lane4_OFF                    (16)
  #define DDRDATA8CH1_CR_RXOFFSETVDQRANK3_Lane4_WID                    ( 4)
  #define DDRDATA8CH1_CR_RXOFFSETVDQRANK3_Lane4_MSK                    (0x000F0000)
  #define DDRDATA8CH1_CR_RXOFFSETVDQRANK3_Lane4_MIN                    (0)
  #define DDRDATA8CH1_CR_RXOFFSETVDQRANK3_Lane4_MAX                    (15) // 0x0000000F
  #define DDRDATA8CH1_CR_RXOFFSETVDQRANK3_Lane4_DEF                    (0x00000000)
  #define DDRDATA8CH1_CR_RXOFFSETVDQRANK3_Lane4_HSH                    (0x0410115C)

  #define DDRDATA8CH1_CR_RXOFFSETVDQRANK3_Lane5_OFF                    (20)
  #define DDRDATA8CH1_CR_RXOFFSETVDQRANK3_Lane5_WID                    ( 4)
  #define DDRDATA8CH1_CR_RXOFFSETVDQRANK3_Lane5_MSK                    (0x00F00000)
  #define DDRDATA8CH1_CR_RXOFFSETVDQRANK3_Lane5_MIN                    (0)
  #define DDRDATA8CH1_CR_RXOFFSETVDQRANK3_Lane5_MAX                    (15) // 0x0000000F
  #define DDRDATA8CH1_CR_RXOFFSETVDQRANK3_Lane5_DEF                    (0x00000000)
  #define DDRDATA8CH1_CR_RXOFFSETVDQRANK3_Lane5_HSH                    (0x0414115C)

  #define DDRDATA8CH1_CR_RXOFFSETVDQRANK3_Lane6_OFF                    (24)
  #define DDRDATA8CH1_CR_RXOFFSETVDQRANK3_Lane6_WID                    ( 4)
  #define DDRDATA8CH1_CR_RXOFFSETVDQRANK3_Lane6_MSK                    (0x0F000000)
  #define DDRDATA8CH1_CR_RXOFFSETVDQRANK3_Lane6_MIN                    (0)
  #define DDRDATA8CH1_CR_RXOFFSETVDQRANK3_Lane6_MAX                    (15) // 0x0000000F
  #define DDRDATA8CH1_CR_RXOFFSETVDQRANK3_Lane6_DEF                    (0x00000000)
  #define DDRDATA8CH1_CR_RXOFFSETVDQRANK3_Lane6_HSH                    (0x0418115C)

  #define DDRDATA8CH1_CR_RXOFFSETVDQRANK3_Lane7_OFF                    (28)
  #define DDRDATA8CH1_CR_RXOFFSETVDQRANK3_Lane7_WID                    ( 4)
  #define DDRDATA8CH1_CR_RXOFFSETVDQRANK3_Lane7_MSK                    (0xF0000000)
  #define DDRDATA8CH1_CR_RXOFFSETVDQRANK3_Lane7_MIN                    (0)
  #define DDRDATA8CH1_CR_RXOFFSETVDQRANK3_Lane7_MAX                    (15) // 0x0000000F
  #define DDRDATA8CH1_CR_RXOFFSETVDQRANK3_Lane7_DEF                    (0x00000000)
  #define DDRDATA8CH1_CR_RXOFFSETVDQRANK3_Lane7_HSH                    (0x041C115C)

#define DDRDATA8CH1_CR_DATATRAINFEEDBACK_REG                           (0x00001160)

  #define DDRDATA8CH1_CR_DATATRAINFEEDBACK_DataTrainFeedback_OFF       ( 0)
  #define DDRDATA8CH1_CR_DATATRAINFEEDBACK_DataTrainFeedback_WID       ( 9)
  #define DDRDATA8CH1_CR_DATATRAINFEEDBACK_DataTrainFeedback_MSK       (0x000001FF)
  #define DDRDATA8CH1_CR_DATATRAINFEEDBACK_DataTrainFeedback_MIN       (0)
  #define DDRDATA8CH1_CR_DATATRAINFEEDBACK_DataTrainFeedback_MAX       (511) // 0x000001FF
  #define DDRDATA8CH1_CR_DATATRAINFEEDBACK_DataTrainFeedback_DEF       (0x00000000)
  #define DDRDATA8CH1_CR_DATATRAINFEEDBACK_DataTrainFeedback_HSH       (0x09001160)

  #define DDRDATA8CH1_CR_DATATRAINFEEDBACK_Spare_OFF                   ( 9)
  #define DDRDATA8CH1_CR_DATATRAINFEEDBACK_Spare_WID                   (23)
  #define DDRDATA8CH1_CR_DATATRAINFEEDBACK_Spare_MSK                   (0xFFFFFE00)
  #define DDRDATA8CH1_CR_DATATRAINFEEDBACK_Spare_MIN                   (0)
  #define DDRDATA8CH1_CR_DATATRAINFEEDBACK_Spare_MAX                   (8388607) // 0x007FFFFF
  #define DDRDATA8CH1_CR_DATATRAINFEEDBACK_Spare_DEF                   (0x00000000)
  #define DDRDATA8CH1_CR_DATATRAINFEEDBACK_Spare_HSH                   (0x17091160)

#define DDRDATA8CH1_CR_DLLPITESTANDADC_REG                             (0x00001164)

  #define DDRDATA8CH1_CR_DLLPITESTANDADC_RunTest_OFF                   ( 0)
  #define DDRDATA8CH1_CR_DLLPITESTANDADC_RunTest_WID                   ( 1)
  #define DDRDATA8CH1_CR_DLLPITESTANDADC_RunTest_MSK                   (0x00000001)
  #define DDRDATA8CH1_CR_DLLPITESTANDADC_RunTest_MIN                   (0)
  #define DDRDATA8CH1_CR_DLLPITESTANDADC_RunTest_MAX                   (1) // 0x00000001
  #define DDRDATA8CH1_CR_DLLPITESTANDADC_RunTest_DEF                   (0x00000000)
  #define DDRDATA8CH1_CR_DLLPITESTANDADC_RunTest_HSH                   (0x01001164)

  #define DDRDATA8CH1_CR_DLLPITESTANDADC_Load_OFF                      ( 1)
  #define DDRDATA8CH1_CR_DLLPITESTANDADC_Load_WID                      ( 1)
  #define DDRDATA8CH1_CR_DLLPITESTANDADC_Load_MSK                      (0x00000002)
  #define DDRDATA8CH1_CR_DLLPITESTANDADC_Load_MIN                      (0)
  #define DDRDATA8CH1_CR_DLLPITESTANDADC_Load_MAX                      (1) // 0x00000001
  #define DDRDATA8CH1_CR_DLLPITESTANDADC_Load_DEF                      (0x00000000)
  #define DDRDATA8CH1_CR_DLLPITESTANDADC_Load_HSH                      (0x01011164)

  #define DDRDATA8CH1_CR_DLLPITESTANDADC_ModeHVM_OFF                   ( 2)
  #define DDRDATA8CH1_CR_DLLPITESTANDADC_ModeHVM_WID                   ( 1)
  #define DDRDATA8CH1_CR_DLLPITESTANDADC_ModeHVM_MSK                   (0x00000004)
  #define DDRDATA8CH1_CR_DLLPITESTANDADC_ModeHVM_MIN                   (0)
  #define DDRDATA8CH1_CR_DLLPITESTANDADC_ModeHVM_MAX                   (1) // 0x00000001
  #define DDRDATA8CH1_CR_DLLPITESTANDADC_ModeHVM_DEF                   (0x00000000)
  #define DDRDATA8CH1_CR_DLLPITESTANDADC_ModeHVM_HSH                   (0x01021164)

  #define DDRDATA8CH1_CR_DLLPITESTANDADC_ModeDV_OFF                    ( 3)
  #define DDRDATA8CH1_CR_DLLPITESTANDADC_ModeDV_WID                    ( 1)
  #define DDRDATA8CH1_CR_DLLPITESTANDADC_ModeDV_MSK                    (0x00000008)
  #define DDRDATA8CH1_CR_DLLPITESTANDADC_ModeDV_MIN                    (0)
  #define DDRDATA8CH1_CR_DLLPITESTANDADC_ModeDV_MAX                    (1) // 0x00000001
  #define DDRDATA8CH1_CR_DLLPITESTANDADC_ModeDV_DEF                    (0x00000000)
  #define DDRDATA8CH1_CR_DLLPITESTANDADC_ModeDV_HSH                    (0x01031164)

  #define DDRDATA8CH1_CR_DLLPITESTANDADC_CalCfdl_OFF                   ( 4)
  #define DDRDATA8CH1_CR_DLLPITESTANDADC_CalCfdl_WID                   ( 1)
  #define DDRDATA8CH1_CR_DLLPITESTANDADC_CalCfdl_MSK                   (0x00000010)
  #define DDRDATA8CH1_CR_DLLPITESTANDADC_CalCfdl_MIN                   (0)
  #define DDRDATA8CH1_CR_DLLPITESTANDADC_CalCfdl_MAX                   (1) // 0x00000001
  #define DDRDATA8CH1_CR_DLLPITESTANDADC_CalCfdl_DEF                   (0x00000000)
  #define DDRDATA8CH1_CR_DLLPITESTANDADC_CalCfdl_HSH                   (0x01041164)

  #define DDRDATA8CH1_CR_DLLPITESTANDADC_LoadCount_OFF                 ( 5)
  #define DDRDATA8CH1_CR_DLLPITESTANDADC_LoadCount_WID                 (10)
  #define DDRDATA8CH1_CR_DLLPITESTANDADC_LoadCount_MSK                 (0x00007FE0)
  #define DDRDATA8CH1_CR_DLLPITESTANDADC_LoadCount_MIN                 (0)
  #define DDRDATA8CH1_CR_DLLPITESTANDADC_LoadCount_MAX                 (1023) // 0x000003FF
  #define DDRDATA8CH1_CR_DLLPITESTANDADC_LoadCount_DEF                 (0x00000000)
  #define DDRDATA8CH1_CR_DLLPITESTANDADC_LoadCount_HSH                 (0x0A051164)

  #define DDRDATA8CH1_CR_DLLPITESTANDADC_CountStatus_OFF               (15)
  #define DDRDATA8CH1_CR_DLLPITESTANDADC_CountStatus_WID               (10)
  #define DDRDATA8CH1_CR_DLLPITESTANDADC_CountStatus_MSK               (0x01FF8000)
  #define DDRDATA8CH1_CR_DLLPITESTANDADC_CountStatus_MIN               (0)
  #define DDRDATA8CH1_CR_DLLPITESTANDADC_CountStatus_MAX               (1023) // 0x000003FF
  #define DDRDATA8CH1_CR_DLLPITESTANDADC_CountStatus_DEF               (0x00000000)
  #define DDRDATA8CH1_CR_DLLPITESTANDADC_CountStatus_HSH               (0x0A0F1164)

  #define DDRDATA8CH1_CR_DLLPITESTANDADC_ModeADC_OFF                   (25)
  #define DDRDATA8CH1_CR_DLLPITESTANDADC_ModeADC_WID                   ( 1)
  #define DDRDATA8CH1_CR_DLLPITESTANDADC_ModeADC_MSK                   (0x02000000)
  #define DDRDATA8CH1_CR_DLLPITESTANDADC_ModeADC_MIN                   (0)
  #define DDRDATA8CH1_CR_DLLPITESTANDADC_ModeADC_MAX                   (1) // 0x00000001
  #define DDRDATA8CH1_CR_DLLPITESTANDADC_ModeADC_DEF                   (0x00000000)
  #define DDRDATA8CH1_CR_DLLPITESTANDADC_ModeADC_HSH                   (0x01191164)

  #define DDRDATA8CH1_CR_DLLPITESTANDADC_ADCClkDiv_OFF                 (26)
  #define DDRDATA8CH1_CR_DLLPITESTANDADC_ADCClkDiv_WID                 ( 2)
  #define DDRDATA8CH1_CR_DLLPITESTANDADC_ADCClkDiv_MSK                 (0x0C000000)
  #define DDRDATA8CH1_CR_DLLPITESTANDADC_ADCClkDiv_MIN                 (0)
  #define DDRDATA8CH1_CR_DLLPITESTANDADC_ADCClkDiv_MAX                 (3) // 0x00000003
  #define DDRDATA8CH1_CR_DLLPITESTANDADC_ADCClkDiv_DEF                 (0x00000000)
  #define DDRDATA8CH1_CR_DLLPITESTANDADC_ADCClkDiv_HSH                 (0x021A1164)

  #define DDRDATA8CH1_CR_DLLPITESTANDADC_ADCDdrChanSel_OFF             (28)
  #define DDRDATA8CH1_CR_DLLPITESTANDADC_ADCDdrChanSel_WID             ( 1)
  #define DDRDATA8CH1_CR_DLLPITESTANDADC_ADCDdrChanSel_MSK             (0x10000000)
  #define DDRDATA8CH1_CR_DLLPITESTANDADC_ADCDdrChanSel_MIN             (0)
  #define DDRDATA8CH1_CR_DLLPITESTANDADC_ADCDdrChanSel_MAX             (1) // 0x00000001
  #define DDRDATA8CH1_CR_DLLPITESTANDADC_ADCDdrChanSel_DEF             (0x00000000)
  #define DDRDATA8CH1_CR_DLLPITESTANDADC_ADCDdrChanSel_HSH             (0x011C1164)

  #define DDRDATA8CH1_CR_DLLPITESTANDADC_ADCChopEn_OFF                 (29)
  #define DDRDATA8CH1_CR_DLLPITESTANDADC_ADCChopEn_WID                 ( 1)
  #define DDRDATA8CH1_CR_DLLPITESTANDADC_ADCChopEn_MSK                 (0x20000000)
  #define DDRDATA8CH1_CR_DLLPITESTANDADC_ADCChopEn_MIN                 (0)
  #define DDRDATA8CH1_CR_DLLPITESTANDADC_ADCChopEn_MAX                 (1) // 0x00000001
  #define DDRDATA8CH1_CR_DLLPITESTANDADC_ADCChopEn_DEF                 (0x00000000)
  #define DDRDATA8CH1_CR_DLLPITESTANDADC_ADCChopEn_HSH                 (0x011D1164)

  #define DDRDATA8CH1_CR_DLLPITESTANDADC_ADCDone_OFF                   (30)
  #define DDRDATA8CH1_CR_DLLPITESTANDADC_ADCDone_WID                   ( 1)
  #define DDRDATA8CH1_CR_DLLPITESTANDADC_ADCDone_MSK                   (0x40000000)
  #define DDRDATA8CH1_CR_DLLPITESTANDADC_ADCDone_MIN                   (0)
  #define DDRDATA8CH1_CR_DLLPITESTANDADC_ADCDone_MAX                   (1) // 0x00000001
  #define DDRDATA8CH1_CR_DLLPITESTANDADC_ADCDone_DEF                   (0x00000000)
  #define DDRDATA8CH1_CR_DLLPITESTANDADC_ADCDone_HSH                   (0x011E1164)

  #define DDRDATA8CH1_CR_DLLPITESTANDADC_PhaseDrvPwrSavOn_OFF          (31)
  #define DDRDATA8CH1_CR_DLLPITESTANDADC_PhaseDrvPwrSavOn_WID          ( 1)
  #define DDRDATA8CH1_CR_DLLPITESTANDADC_PhaseDrvPwrSavOn_MSK          (0x80000000)
  #define DDRDATA8CH1_CR_DLLPITESTANDADC_PhaseDrvPwrSavOn_MIN          (0)
  #define DDRDATA8CH1_CR_DLLPITESTANDADC_PhaseDrvPwrSavOn_MAX          (1) // 0x00000001
  #define DDRDATA8CH1_CR_DLLPITESTANDADC_PhaseDrvPwrSavOn_DEF          (0x00000000)
  #define DDRDATA8CH1_CR_DLLPITESTANDADC_PhaseDrvPwrSavOn_HSH          (0x011F1164)

#define DDRDATA8CH1_CR_DDRCRDATAOFFSETCOMP_REG                         (0x00001168)

  #define DDRDATA8CH1_CR_DDRCRDATAOFFSETCOMP_DqDrvUpCompOffset_OFF     ( 0)
  #define DDRDATA8CH1_CR_DDRCRDATAOFFSETCOMP_DqDrvUpCompOffset_WID     ( 6)
  #define DDRDATA8CH1_CR_DDRCRDATAOFFSETCOMP_DqDrvUpCompOffset_MSK     (0x0000003F)
  #define DDRDATA8CH1_CR_DDRCRDATAOFFSETCOMP_DqDrvUpCompOffset_MIN     (-32)
  #define DDRDATA8CH1_CR_DDRCRDATAOFFSETCOMP_DqDrvUpCompOffset_MAX     (31) // 0x0000001F
  #define DDRDATA8CH1_CR_DDRCRDATAOFFSETCOMP_DqDrvUpCompOffset_DEF     (0x00000000)
  #define DDRDATA8CH1_CR_DDRCRDATAOFFSETCOMP_DqDrvUpCompOffset_HSH     (0x86001168)

  #define DDRDATA8CH1_CR_DDRCRDATAOFFSETCOMP_DqDrvDownCompOffset_OFF   ( 6)
  #define DDRDATA8CH1_CR_DDRCRDATAOFFSETCOMP_DqDrvDownCompOffset_WID   ( 6)
  #define DDRDATA8CH1_CR_DDRCRDATAOFFSETCOMP_DqDrvDownCompOffset_MSK   (0x00000FC0)
  #define DDRDATA8CH1_CR_DDRCRDATAOFFSETCOMP_DqDrvDownCompOffset_MIN   (-32)
  #define DDRDATA8CH1_CR_DDRCRDATAOFFSETCOMP_DqDrvDownCompOffset_MAX   (31) // 0x0000001F
  #define DDRDATA8CH1_CR_DDRCRDATAOFFSETCOMP_DqDrvDownCompOffset_DEF   (0x00000000)
  #define DDRDATA8CH1_CR_DDRCRDATAOFFSETCOMP_DqDrvDownCompOffset_HSH   (0x86061168)

  #define DDRDATA8CH1_CR_DDRCRDATAOFFSETCOMP_DqOdtUpCompOffset_OFF     (12)
  #define DDRDATA8CH1_CR_DDRCRDATAOFFSETCOMP_DqOdtUpCompOffset_WID     ( 5)
  #define DDRDATA8CH1_CR_DDRCRDATAOFFSETCOMP_DqOdtUpCompOffset_MSK     (0x0001F000)
  #define DDRDATA8CH1_CR_DDRCRDATAOFFSETCOMP_DqOdtUpCompOffset_MIN     (-16)
  #define DDRDATA8CH1_CR_DDRCRDATAOFFSETCOMP_DqOdtUpCompOffset_MAX     (15) // 0x0000000F
  #define DDRDATA8CH1_CR_DDRCRDATAOFFSETCOMP_DqOdtUpCompOffset_DEF     (0x00000000)
  #define DDRDATA8CH1_CR_DDRCRDATAOFFSETCOMP_DqOdtUpCompOffset_HSH     (0x850C1168)

  #define DDRDATA8CH1_CR_DDRCRDATAOFFSETCOMP_DqOdtDownCompOffset_OFF   (17)
  #define DDRDATA8CH1_CR_DDRCRDATAOFFSETCOMP_DqOdtDownCompOffset_WID   ( 5)
  #define DDRDATA8CH1_CR_DDRCRDATAOFFSETCOMP_DqOdtDownCompOffset_MSK   (0x003E0000)
  #define DDRDATA8CH1_CR_DDRCRDATAOFFSETCOMP_DqOdtDownCompOffset_MIN   (-16)
  #define DDRDATA8CH1_CR_DDRCRDATAOFFSETCOMP_DqOdtDownCompOffset_MAX   (15) // 0x0000000F
  #define DDRDATA8CH1_CR_DDRCRDATAOFFSETCOMP_DqOdtDownCompOffset_DEF   (0x00000000)
  #define DDRDATA8CH1_CR_DDRCRDATAOFFSETCOMP_DqOdtDownCompOffset_HSH   (0x85111168)

  #define DDRDATA8CH1_CR_DDRCRDATAOFFSETCOMP_DqTcoCompOffset_OFF       (22)
  #define DDRDATA8CH1_CR_DDRCRDATAOFFSETCOMP_DqTcoCompOffset_WID       ( 5)
  #define DDRDATA8CH1_CR_DDRCRDATAOFFSETCOMP_DqTcoCompOffset_MSK       (0x07C00000)
  #define DDRDATA8CH1_CR_DDRCRDATAOFFSETCOMP_DqTcoCompOffset_MIN       (-16)
  #define DDRDATA8CH1_CR_DDRCRDATAOFFSETCOMP_DqTcoCompOffset_MAX       (15) // 0x0000000F
  #define DDRDATA8CH1_CR_DDRCRDATAOFFSETCOMP_DqTcoCompOffset_DEF       (0x00000000)
  #define DDRDATA8CH1_CR_DDRCRDATAOFFSETCOMP_DqTcoCompOffset_HSH       (0x85161168)

  #define DDRDATA8CH1_CR_DDRCRDATAOFFSETCOMP_DqSlewRateCompOffset_OFF  (27)
  #define DDRDATA8CH1_CR_DDRCRDATAOFFSETCOMP_DqSlewRateCompOffset_WID  ( 5)
  #define DDRDATA8CH1_CR_DDRCRDATAOFFSETCOMP_DqSlewRateCompOffset_MSK  (0xF8000000)
  #define DDRDATA8CH1_CR_DDRCRDATAOFFSETCOMP_DqSlewRateCompOffset_MIN  (-16)
  #define DDRDATA8CH1_CR_DDRCRDATAOFFSETCOMP_DqSlewRateCompOffset_MAX  (15) // 0x0000000F
  #define DDRDATA8CH1_CR_DDRCRDATAOFFSETCOMP_DqSlewRateCompOffset_DEF  (0x00000000)
  #define DDRDATA8CH1_CR_DDRCRDATAOFFSETCOMP_DqSlewRateCompOffset_HSH  (0x851B1168)

#define DDRDATA8CH1_CR_DDRCRDATACONTROL1_REG                           (0x0000116C)

  #define DDRDATA8CH1_CR_DDRCRDATACONTROL1_RefPi_OFF                   ( 0)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL1_RefPi_WID                   ( 4)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL1_RefPi_MSK                   (0x0000000F)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL1_RefPi_MIN                   (-8)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL1_RefPi_MAX                   (7) // 0x00000007
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL1_RefPi_DEF                   (0x00000000)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL1_RefPi_HSH                   (0x8400116C)

  #define DDRDATA8CH1_CR_DDRCRDATACONTROL1_DllMask_OFF                 ( 4)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL1_DllMask_WID                 ( 2)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL1_DllMask_MSK                 (0x00000030)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL1_DllMask_MIN                 (0)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL1_DllMask_MAX                 (3) // 0x00000003
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL1_DllMask_DEF                 (0x00000000)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL1_DllMask_HSH                 (0x0204116C)

  #define DDRDATA8CH1_CR_DDRCRDATACONTROL1_DllWeakLock_OFF             ( 6)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL1_DllWeakLock_WID             ( 1)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL1_DllWeakLock_MSK             (0x00000040)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL1_DllWeakLock_MIN             (0)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL1_DllWeakLock_MAX             (1) // 0x00000001
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL1_DllWeakLock_DEF             (0x00000000)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL1_DllWeakLock_HSH             (0x0106116C)

  #define DDRDATA8CH1_CR_DDRCRDATACONTROL1_SdllSegmentDisable_OFF      ( 7)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL1_SdllSegmentDisable_WID      ( 3)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL1_SdllSegmentDisable_MSK      (0x00000380)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL1_SdllSegmentDisable_MIN      (0)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL1_SdllSegmentDisable_MAX      (7) // 0x00000007
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL1_SdllSegmentDisable_DEF      (0x00000000)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL1_SdllSegmentDisable_HSH      (0x0307116C)

  #define DDRDATA8CH1_CR_DDRCRDATACONTROL1_RxBiasCtl_OFF               (10)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL1_RxBiasCtl_WID               ( 4)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL1_RxBiasCtl_MSK               (0x00003C00)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL1_RxBiasCtl_MIN               (0)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL1_RxBiasCtl_MAX               (15) // 0x0000000F
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL1_RxBiasCtl_DEF               (0x00000008)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL1_RxBiasCtl_HSH               (0x040A116C)

  #define DDRDATA8CH1_CR_DDRCRDATACONTROL1_OdtDelay_OFF                (14)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL1_OdtDelay_WID                ( 4)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL1_OdtDelay_MSK                (0x0003C000)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL1_OdtDelay_MIN                (-8)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL1_OdtDelay_MAX                (7) // 0x00000007
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL1_OdtDelay_DEF                (0x00000000)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL1_OdtDelay_HSH                (0x840E116C)

  #define DDRDATA8CH1_CR_DDRCRDATACONTROL1_OdtDuration_OFF             (18)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL1_OdtDuration_WID             ( 3)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL1_OdtDuration_MSK             (0x001C0000)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL1_OdtDuration_MIN             (0)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL1_OdtDuration_MAX             (7) // 0x00000007
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL1_OdtDuration_DEF             (0x00000000)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL1_OdtDuration_HSH             (0x0312116C)

  #define DDRDATA8CH1_CR_DDRCRDATACONTROL1_SenseAmpDelay_OFF           (21)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL1_SenseAmpDelay_WID           ( 4)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL1_SenseAmpDelay_MSK           (0x01E00000)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL1_SenseAmpDelay_MIN           (-8)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL1_SenseAmpDelay_MAX           (7) // 0x00000007
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL1_SenseAmpDelay_DEF           (0x00000000)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL1_SenseAmpDelay_HSH           (0x8415116C)

  #define DDRDATA8CH1_CR_DDRCRDATACONTROL1_SenseAmpDuration_OFF        (25)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL1_SenseAmpDuration_WID        ( 3)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL1_SenseAmpDuration_MSK        (0x0E000000)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL1_SenseAmpDuration_MIN        (0)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL1_SenseAmpDuration_MAX        (7) // 0x00000007
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL1_SenseAmpDuration_DEF        (0x00000000)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL1_SenseAmpDuration_HSH        (0x0319116C)

  #define DDRDATA8CH1_CR_DDRCRDATACONTROL1_StrongWkLeaker_OFF          (28)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL1_StrongWkLeaker_WID          ( 3)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL1_StrongWkLeaker_MSK          (0x70000000)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL1_StrongWkLeaker_MIN          (0)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL1_StrongWkLeaker_MAX          (7) // 0x00000007
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL1_StrongWkLeaker_DEF          (0x00000000)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL1_StrongWkLeaker_HSH          (0x031C116C)

  #define DDRDATA8CH1_CR_DDRCRDATACONTROL1_LpDdrLongOdtEn_OFF          (31)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL1_LpDdrLongOdtEn_WID          ( 1)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL1_LpDdrLongOdtEn_MSK          (0x80000000)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL1_LpDdrLongOdtEn_MIN          (0)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL1_LpDdrLongOdtEn_MAX          (1) // 0x00000001
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL1_LpDdrLongOdtEn_DEF          (0x00000000)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL1_LpDdrLongOdtEn_HSH          (0x011F116C)

#define DDRDATA8CH1_CR_DDRCRDATACONTROL2_REG                           (0x00001170)

  #define DDRDATA8CH1_CR_DDRCRDATACONTROL2_RxStaggerCtl_OFF            ( 0)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL2_RxStaggerCtl_WID            ( 5)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL2_RxStaggerCtl_MSK            (0x0000001F)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL2_RxStaggerCtl_MIN            (0)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL2_RxStaggerCtl_MAX            (31) // 0x0000001F
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL2_RxStaggerCtl_DEF            (0x00000000)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL2_RxStaggerCtl_HSH            (0x05001170)

  #define DDRDATA8CH1_CR_DDRCRDATACONTROL2_ForceBiasOn_OFF             ( 5)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL2_ForceBiasOn_WID             ( 1)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL2_ForceBiasOn_MSK             (0x00000020)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL2_ForceBiasOn_MIN             (0)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL2_ForceBiasOn_MAX             (1) // 0x00000001
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL2_ForceBiasOn_DEF             (0x00000000)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL2_ForceBiasOn_HSH             (0x01051170)

  #define DDRDATA8CH1_CR_DDRCRDATACONTROL2_ForceRxOn_OFF               ( 6)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL2_ForceRxOn_WID               ( 1)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL2_ForceRxOn_MSK               (0x00000040)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL2_ForceRxOn_MIN               (0)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL2_ForceRxOn_MAX               (1) // 0x00000001
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL2_ForceRxOn_DEF               (0x00000000)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL2_ForceRxOn_HSH               (0x01061170)

  #define DDRDATA8CH1_CR_DDRCRDATACONTROL2_LeakerComp_OFF              ( 7)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL2_LeakerComp_WID              ( 2)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL2_LeakerComp_MSK              (0x00000180)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL2_LeakerComp_MIN              (0)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL2_LeakerComp_MAX              (3) // 0x00000003
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL2_LeakerComp_DEF              (0x00000000)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL2_LeakerComp_HSH              (0x02071170)

  #define DDRDATA8CH1_CR_DDRCRDATACONTROL2_RxDqsAmpOffset_OFF          ( 9)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL2_RxDqsAmpOffset_WID          ( 4)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL2_RxDqsAmpOffset_MSK          (0x00001E00)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL2_RxDqsAmpOffset_MIN          (0)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL2_RxDqsAmpOffset_MAX          (15) // 0x0000000F
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL2_RxDqsAmpOffset_DEF          (0x00000008)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL2_RxDqsAmpOffset_HSH          (0x04091170)

  #define DDRDATA8CH1_CR_DDRCRDATACONTROL2_RxClkStgNum_OFF             (13)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL2_RxClkStgNum_WID             ( 5)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL2_RxClkStgNum_MSK             (0x0003E000)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL2_RxClkStgNum_MIN             (0)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL2_RxClkStgNum_MAX             (31) // 0x0000001F
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL2_RxClkStgNum_DEF             (0x00000011)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL2_RxClkStgNum_HSH             (0x050D1170)

  #define DDRDATA8CH1_CR_DDRCRDATACONTROL2_WlLongDelEn_OFF             (18)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL2_WlLongDelEn_WID             ( 1)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL2_WlLongDelEn_MSK             (0x00040000)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL2_WlLongDelEn_MIN             (0)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL2_WlLongDelEn_MAX             (1) // 0x00000001
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL2_WlLongDelEn_DEF             (0x00000000)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL2_WlLongDelEn_HSH             (0x01121170)

  #define DDRDATA8CH1_CR_DDRCRDATACONTROL2_EnableVrefPwrDn_OFF         (19)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL2_EnableVrefPwrDn_WID         ( 1)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL2_EnableVrefPwrDn_MSK         (0x00080000)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL2_EnableVrefPwrDn_MIN         (0)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL2_EnableVrefPwrDn_MAX         (1) // 0x00000001
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL2_EnableVrefPwrDn_DEF         (0x00000000)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL2_EnableVrefPwrDn_HSH         (0x01131170)

  #define DDRDATA8CH1_CR_DDRCRDATACONTROL2_Ddr4Mode_OFF                (20)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL2_Ddr4Mode_WID                ( 1)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL2_Ddr4Mode_MSK                (0x00100000)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL2_Ddr4Mode_MIN                (0)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL2_Ddr4Mode_MAX                (1) // 0x00000001
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL2_Ddr4Mode_DEF                (0x00000000)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL2_Ddr4Mode_HSH                (0x01141170)

  #define DDRDATA8CH1_CR_DDRCRDATACONTROL2_EnVddqOdt_OFF               (21)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL2_EnVddqOdt_WID               ( 1)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL2_EnVddqOdt_MSK               (0x00200000)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL2_EnVddqOdt_MIN               (0)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL2_EnVddqOdt_MAX               (1) // 0x00000001
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL2_EnVddqOdt_DEF               (0x00000000)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL2_EnVddqOdt_HSH               (0x01151170)

  #define DDRDATA8CH1_CR_DDRCRDATACONTROL2_EnVttOdt_OFF                (22)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL2_EnVttOdt_WID                ( 1)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL2_EnVttOdt_MSK                (0x00400000)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL2_EnVttOdt_MIN                (0)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL2_EnVttOdt_MAX                (1) // 0x00000001
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL2_EnVttOdt_DEF                (0x00000000)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL2_EnVttOdt_HSH                (0x01161170)

  #define DDRDATA8CH1_CR_DDRCRDATACONTROL2_EnConstZEqTx_OFF            (23)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL2_EnConstZEqTx_WID            ( 1)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL2_EnConstZEqTx_MSK            (0x00800000)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL2_EnConstZEqTx_MIN            (0)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL2_EnConstZEqTx_MAX            (1) // 0x00000001
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL2_EnConstZEqTx_DEF            (0x00000000)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL2_EnConstZEqTx_HSH            (0x01171170)

  #define DDRDATA8CH1_CR_DDRCRDATACONTROL2_TxEqDis_OFF                 (24)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL2_TxEqDis_WID                 ( 1)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL2_TxEqDis_MSK                 (0x01000000)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL2_TxEqDis_MIN                 (0)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL2_TxEqDis_MAX                 (1) // 0x00000001
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL2_TxEqDis_DEF                 (0x00000000)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL2_TxEqDis_HSH                 (0x01181170)

  #define DDRDATA8CH1_CR_DDRCRDATACONTROL2_RxVrefProgMFC_OFF           (25)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL2_RxVrefProgMFC_WID           ( 1)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL2_RxVrefProgMFC_MSK           (0x02000000)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL2_RxVrefProgMFC_MIN           (0)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL2_RxVrefProgMFC_MAX           (1) // 0x00000001
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL2_RxVrefProgMFC_DEF           (0x00000000)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL2_RxVrefProgMFC_HSH           (0x01191170)

  #define DDRDATA8CH1_CR_DDRCRDATACONTROL2_Cben_OFF                    (26)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL2_Cben_WID                    ( 3)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL2_Cben_MSK                    (0x1C000000)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL2_Cben_MIN                    (0)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL2_Cben_MAX                    (7) // 0x00000007
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL2_Cben_DEF                    (0x00000000)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL2_Cben_HSH                    (0x031A1170)

  #define DDRDATA8CH1_CR_DDRCRDATACONTROL2_TxDeskewDisable_OFF         (29)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL2_TxDeskewDisable_WID         ( 1)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL2_TxDeskewDisable_MSK         (0x20000000)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL2_TxDeskewDisable_MIN         (0)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL2_TxDeskewDisable_MAX         (1) // 0x00000001
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL2_TxDeskewDisable_DEF         (0x00000000)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL2_TxDeskewDisable_HSH         (0x011D1170)

  #define DDRDATA8CH1_CR_DDRCRDATACONTROL2_RxDeskewDisable_OFF         (30)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL2_RxDeskewDisable_WID         ( 1)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL2_RxDeskewDisable_MSK         (0x40000000)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL2_RxDeskewDisable_MIN         (0)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL2_RxDeskewDisable_MAX         (1) // 0x00000001
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL2_RxDeskewDisable_DEF         (0x00000000)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL2_RxDeskewDisable_HSH         (0x011E1170)

  #define DDRDATA8CH1_CR_DDRCRDATACONTROL2_DqSlewDlyByPass_OFF         (31)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL2_DqSlewDlyByPass_WID         ( 1)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL2_DqSlewDlyByPass_MSK         (0x80000000)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL2_DqSlewDlyByPass_MIN         (0)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL2_DqSlewDlyByPass_MAX         (1) // 0x00000001
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL2_DqSlewDlyByPass_DEF         (0x00000000)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL2_DqSlewDlyByPass_HSH         (0x011F1170)

#define DDRDATA8CH1_CR_DDRCRVREFCONTROL_REG                            (0x00001174)

  #define DDRDATA8CH1_CR_DDRCRVREFCONTROL_VrefCtl_OFF                  ( 0)
  #define DDRDATA8CH1_CR_DDRCRVREFCONTROL_VrefCtl_WID                  (24)
  #define DDRDATA8CH1_CR_DDRCRVREFCONTROL_VrefCtl_MSK                  (0x00FFFFFF)
  #define DDRDATA8CH1_CR_DDRCRVREFCONTROL_VrefCtl_MIN                  (0)
  #define DDRDATA8CH1_CR_DDRCRVREFCONTROL_VrefCtl_MAX                  (16777215) // 0x00FFFFFF
  #define DDRDATA8CH1_CR_DDRCRVREFCONTROL_VrefCtl_DEF                  (0x000E453A)
  #define DDRDATA8CH1_CR_DDRCRVREFCONTROL_VrefCtl_HSH                  (0x18001174)

  #define DDRDATA8CH1_CR_DDRCRVREFCONTROL_OutputCode_OFF               (24)
  #define DDRDATA8CH1_CR_DDRCRVREFCONTROL_OutputCode_WID               ( 8)
  #define DDRDATA8CH1_CR_DDRCRVREFCONTROL_OutputCode_MSK               (0xFF000000)
  #define DDRDATA8CH1_CR_DDRCRVREFCONTROL_OutputCode_MIN               (0)
  #define DDRDATA8CH1_CR_DDRCRVREFCONTROL_OutputCode_MAX               (255) // 0x000000FF
  #define DDRDATA8CH1_CR_DDRCRVREFCONTROL_OutputCode_DEF               (0x00000000)
  #define DDRDATA8CH1_CR_DDRCRVREFCONTROL_OutputCode_HSH               (0x08181174)

#define DDRDATA8CH1_CR_DDRCRVSSHICONTROL_REG                           (0x00001178)

  #define DDRDATA8CH1_CR_DDRCRVSSHICONTROL_VssHiCtl_OFF                ( 0)
  #define DDRDATA8CH1_CR_DDRCRVSSHICONTROL_VssHiCtl_WID                (25)
  #define DDRDATA8CH1_CR_DDRCRVSSHICONTROL_VssHiCtl_MSK                (0x01FFFFFF)
  #define DDRDATA8CH1_CR_DDRCRVSSHICONTROL_VssHiCtl_MIN                (0)
  #define DDRDATA8CH1_CR_DDRCRVSSHICONTROL_VssHiCtl_MAX                (33554431) // 0x01FFFFFF
  #define DDRDATA8CH1_CR_DDRCRVSSHICONTROL_VssHiCtl_DEF                (0x014D8234)
  #define DDRDATA8CH1_CR_DDRCRVSSHICONTROL_VssHiCtl_HSH                (0x19001178)

  #define DDRDATA8CH1_CR_DDRCRVSSHICONTROL_OutputCode_OFF              (25)
  #define DDRDATA8CH1_CR_DDRCRVSSHICONTROL_OutputCode_WID              ( 7)
  #define DDRDATA8CH1_CR_DDRCRVSSHICONTROL_OutputCode_MSK              (0xFE000000)
  #define DDRDATA8CH1_CR_DDRCRVSSHICONTROL_OutputCode_MIN              (0)
  #define DDRDATA8CH1_CR_DDRCRVSSHICONTROL_OutputCode_MAX              (127) // 0x0000007F
  #define DDRDATA8CH1_CR_DDRCRVSSHICONTROL_OutputCode_DEF              (0x00000000)
  #define DDRDATA8CH1_CR_DDRCRVSSHICONTROL_OutputCode_HSH              (0x07191178)

#define DDRDATA8CH1_CR_DDRCRDATAOFFSETTRAIN_REG                        (0x0000117C)

  #define DDRDATA8CH1_CR_DDRCRDATAOFFSETTRAIN_RcvEnOffset_OFF          ( 0)
  #define DDRDATA8CH1_CR_DDRCRDATAOFFSETTRAIN_RcvEnOffset_WID          ( 6)
  #define DDRDATA8CH1_CR_DDRCRDATAOFFSETTRAIN_RcvEnOffset_MSK          (0x0000003F)
  #define DDRDATA8CH1_CR_DDRCRDATAOFFSETTRAIN_RcvEnOffset_MIN          (-32)
  #define DDRDATA8CH1_CR_DDRCRDATAOFFSETTRAIN_RcvEnOffset_MAX          (31) // 0x0000001F
  #define DDRDATA8CH1_CR_DDRCRDATAOFFSETTRAIN_RcvEnOffset_DEF          (0x00000000)
  #define DDRDATA8CH1_CR_DDRCRDATAOFFSETTRAIN_RcvEnOffset_HSH          (0x8600117C)

  #define DDRDATA8CH1_CR_DDRCRDATAOFFSETTRAIN_RxDqsOffset_OFF          ( 6)
  #define DDRDATA8CH1_CR_DDRCRDATAOFFSETTRAIN_RxDqsOffset_WID          ( 6)
  #define DDRDATA8CH1_CR_DDRCRDATAOFFSETTRAIN_RxDqsOffset_MSK          (0x00000FC0)
  #define DDRDATA8CH1_CR_DDRCRDATAOFFSETTRAIN_RxDqsOffset_MIN          (-32)
  #define DDRDATA8CH1_CR_DDRCRDATAOFFSETTRAIN_RxDqsOffset_MAX          (31) // 0x0000001F
  #define DDRDATA8CH1_CR_DDRCRDATAOFFSETTRAIN_RxDqsOffset_DEF          (0x00000000)
  #define DDRDATA8CH1_CR_DDRCRDATAOFFSETTRAIN_RxDqsOffset_HSH          (0x8606117C)

  #define DDRDATA8CH1_CR_DDRCRDATAOFFSETTRAIN_TxDqOffset_OFF           (12)
  #define DDRDATA8CH1_CR_DDRCRDATAOFFSETTRAIN_TxDqOffset_WID           ( 6)
  #define DDRDATA8CH1_CR_DDRCRDATAOFFSETTRAIN_TxDqOffset_MSK           (0x0003F000)
  #define DDRDATA8CH1_CR_DDRCRDATAOFFSETTRAIN_TxDqOffset_MIN           (-32)
  #define DDRDATA8CH1_CR_DDRCRDATAOFFSETTRAIN_TxDqOffset_MAX           (31) // 0x0000001F
  #define DDRDATA8CH1_CR_DDRCRDATAOFFSETTRAIN_TxDqOffset_DEF           (0x00000000)
  #define DDRDATA8CH1_CR_DDRCRDATAOFFSETTRAIN_TxDqOffset_HSH           (0x860C117C)

  #define DDRDATA8CH1_CR_DDRCRDATAOFFSETTRAIN_TxDqsOffset_OFF          (18)
  #define DDRDATA8CH1_CR_DDRCRDATAOFFSETTRAIN_TxDqsOffset_WID          ( 6)
  #define DDRDATA8CH1_CR_DDRCRDATAOFFSETTRAIN_TxDqsOffset_MSK          (0x00FC0000)
  #define DDRDATA8CH1_CR_DDRCRDATAOFFSETTRAIN_TxDqsOffset_MIN          (-32)
  #define DDRDATA8CH1_CR_DDRCRDATAOFFSETTRAIN_TxDqsOffset_MAX          (31) // 0x0000001F
  #define DDRDATA8CH1_CR_DDRCRDATAOFFSETTRAIN_TxDqsOffset_DEF          (0x00000000)
  #define DDRDATA8CH1_CR_DDRCRDATAOFFSETTRAIN_TxDqsOffset_HSH          (0x8612117C)

  #define DDRDATA8CH1_CR_DDRCRDATAOFFSETTRAIN_VrefOffset_OFF           (24)
  #define DDRDATA8CH1_CR_DDRCRDATAOFFSETTRAIN_VrefOffset_WID           ( 7)
  #define DDRDATA8CH1_CR_DDRCRDATAOFFSETTRAIN_VrefOffset_MSK           (0x7F000000)
  #define DDRDATA8CH1_CR_DDRCRDATAOFFSETTRAIN_VrefOffset_MIN           (-64)
  #define DDRDATA8CH1_CR_DDRCRDATAOFFSETTRAIN_VrefOffset_MAX           (63) // 0x0000003F
  #define DDRDATA8CH1_CR_DDRCRDATAOFFSETTRAIN_VrefOffset_DEF           (0x00000000)
  #define DDRDATA8CH1_CR_DDRCRDATAOFFSETTRAIN_VrefOffset_HSH           (0x8718117C)

  #define DDRDATA8CH1_CR_DDRCRDATAOFFSETTRAIN_Spare_OFF                (31)
  #define DDRDATA8CH1_CR_DDRCRDATAOFFSETTRAIN_Spare_WID                ( 1)
  #define DDRDATA8CH1_CR_DDRCRDATAOFFSETTRAIN_Spare_MSK                (0x80000000)
  #define DDRDATA8CH1_CR_DDRCRDATAOFFSETTRAIN_Spare_MIN                (0)
  #define DDRDATA8CH1_CR_DDRCRDATAOFFSETTRAIN_Spare_MAX                (1) // 0x00000001
  #define DDRDATA8CH1_CR_DDRCRDATAOFFSETTRAIN_Spare_DEF                (0x00000000)
  #define DDRDATA8CH1_CR_DDRCRDATAOFFSETTRAIN_Spare_HSH                (0x011F117C)

#define DDRDATA8CH1_CR_DDRCRDATACONTROL0_REG                           (0x00001180)

  #define DDRDATA8CH1_CR_DDRCRDATACONTROL0_RxTrainingMode_OFF          ( 0)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL0_RxTrainingMode_WID          ( 1)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL0_RxTrainingMode_MSK          (0x00000001)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL0_RxTrainingMode_MIN          (0)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL0_RxTrainingMode_MAX          (1) // 0x00000001
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL0_RxTrainingMode_DEF          (0x00000000)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL0_RxTrainingMode_HSH          (0x01001180)

  #define DDRDATA8CH1_CR_DDRCRDATACONTROL0_WLTrainingMode_OFF          ( 1)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL0_WLTrainingMode_WID          ( 1)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL0_WLTrainingMode_MSK          (0x00000002)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL0_WLTrainingMode_MIN          (0)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL0_WLTrainingMode_MAX          (1) // 0x00000001
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL0_WLTrainingMode_DEF          (0x00000000)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL0_WLTrainingMode_HSH          (0x01011180)

  #define DDRDATA8CH1_CR_DDRCRDATACONTROL0_RLTrainingMode_OFF          ( 2)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL0_RLTrainingMode_WID          ( 1)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL0_RLTrainingMode_MSK          (0x00000004)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL0_RLTrainingMode_MIN          (0)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL0_RLTrainingMode_MAX          (1) // 0x00000001
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL0_RLTrainingMode_DEF          (0x00000000)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL0_RLTrainingMode_HSH          (0x01021180)

  #define DDRDATA8CH1_CR_DDRCRDATACONTROL0_SenseampTrainingMode_OFF    ( 3)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL0_SenseampTrainingMode_WID    ( 1)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL0_SenseampTrainingMode_MSK    (0x00000008)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL0_SenseampTrainingMode_MIN    (0)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL0_SenseampTrainingMode_MAX    (1) // 0x00000001
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL0_SenseampTrainingMode_DEF    (0x00000000)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL0_SenseampTrainingMode_HSH    (0x01031180)

  #define DDRDATA8CH1_CR_DDRCRDATACONTROL0_TxOn_OFF                    ( 4)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL0_TxOn_WID                    ( 1)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL0_TxOn_MSK                    (0x00000010)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL0_TxOn_MIN                    (0)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL0_TxOn_MAX                    (1) // 0x00000001
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL0_TxOn_DEF                    (0x00000000)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL0_TxOn_HSH                    (0x01041180)

  #define DDRDATA8CH1_CR_DDRCRDATACONTROL0_RfOn_OFF                    ( 5)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL0_RfOn_WID                    ( 1)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL0_RfOn_MSK                    (0x00000020)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL0_RfOn_MIN                    (0)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL0_RfOn_MAX                    (1) // 0x00000001
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL0_RfOn_DEF                    (0x00000000)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL0_RfOn_HSH                    (0x01051180)

  #define DDRDATA8CH1_CR_DDRCRDATACONTROL0_RxPiOn_OFF                  ( 6)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL0_RxPiOn_WID                  ( 1)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL0_RxPiOn_MSK                  (0x00000040)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL0_RxPiOn_MIN                  (0)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL0_RxPiOn_MAX                  (1) // 0x00000001
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL0_RxPiOn_DEF                  (0x00000000)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL0_RxPiOn_HSH                  (0x01061180)

  #define DDRDATA8CH1_CR_DDRCRDATACONTROL0_TxPiOn_OFF                  ( 7)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL0_TxPiOn_WID                  ( 1)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL0_TxPiOn_MSK                  (0x00000080)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL0_TxPiOn_MIN                  (0)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL0_TxPiOn_MAX                  (1) // 0x00000001
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL0_TxPiOn_DEF                  (0x00000000)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL0_TxPiOn_HSH                  (0x01071180)

  #define DDRDATA8CH1_CR_DDRCRDATACONTROL0_InternalClocksOn_OFF        ( 8)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL0_InternalClocksOn_WID        ( 1)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL0_InternalClocksOn_MSK        (0x00000100)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL0_InternalClocksOn_MIN        (0)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL0_InternalClocksOn_MAX        (1) // 0x00000001
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL0_InternalClocksOn_DEF        (0x00000000)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL0_InternalClocksOn_HSH        (0x01081180)

  #define DDRDATA8CH1_CR_DDRCRDATACONTROL0_RepeaterClocksOn_OFF        ( 9)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL0_RepeaterClocksOn_WID        ( 1)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL0_RepeaterClocksOn_MSK        (0x00000200)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL0_RepeaterClocksOn_MIN        (0)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL0_RepeaterClocksOn_MAX        (1) // 0x00000001
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL0_RepeaterClocksOn_DEF        (0x00000000)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL0_RepeaterClocksOn_HSH        (0x01091180)

  #define DDRDATA8CH1_CR_DDRCRDATACONTROL0_TxDisable_OFF               (10)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL0_TxDisable_WID               ( 1)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL0_TxDisable_MSK               (0x00000400)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL0_TxDisable_MIN               (0)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL0_TxDisable_MAX               (1) // 0x00000001
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL0_TxDisable_DEF               (0x00000000)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL0_TxDisable_HSH               (0x010A1180)

  #define DDRDATA8CH1_CR_DDRCRDATACONTROL0_RxDisable_OFF               (11)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL0_RxDisable_WID               ( 1)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL0_RxDisable_MSK               (0x00000800)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL0_RxDisable_MIN               (0)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL0_RxDisable_MAX               (1) // 0x00000001
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL0_RxDisable_DEF               (0x00000000)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL0_RxDisable_HSH               (0x010B1180)

  #define DDRDATA8CH1_CR_DDRCRDATACONTROL0_TxLong_OFF                  (12)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL0_TxLong_WID                  ( 1)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL0_TxLong_MSK                  (0x00001000)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL0_TxLong_MIN                  (0)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL0_TxLong_MAX                  (1) // 0x00000001
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL0_TxLong_DEF                  (0x00000000)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL0_TxLong_HSH                  (0x010C1180)

  #define DDRDATA8CH1_CR_DDRCRDATACONTROL0_RxDqsCtle_OFF               (13)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL0_RxDqsCtle_WID               ( 2)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL0_RxDqsCtle_MSK               (0x00006000)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL0_RxDqsCtle_MIN               (0)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL0_RxDqsCtle_MAX               (3) // 0x00000003
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL0_RxDqsCtle_DEF               (0x00000000)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL0_RxDqsCtle_HSH               (0x020D1180)

  #define DDRDATA8CH1_CR_DDRCRDATACONTROL0_RxReadPointer_OFF           (15)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL0_RxReadPointer_WID           ( 3)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL0_RxReadPointer_MSK           (0x00038000)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL0_RxReadPointer_MIN           (0)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL0_RxReadPointer_MAX           (7) // 0x00000007
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL0_RxReadPointer_DEF           (0x00000000)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL0_RxReadPointer_HSH           (0x030F1180)

  #define DDRDATA8CH1_CR_DDRCRDATACONTROL0_LongOdtR2W_OFF              (18)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL0_LongOdtR2W_WID              ( 1)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL0_LongOdtR2W_MSK              (0x00040000)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL0_LongOdtR2W_MIN              (0)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL0_LongOdtR2W_MAX              (1) // 0x00000001
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL0_LongOdtR2W_DEF              (0x00000000)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL0_LongOdtR2W_HSH              (0x01121180)

  #define DDRDATA8CH1_CR_DDRCRDATACONTROL0_DataVccddqHi_OFF            (19)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL0_DataVccddqHi_WID            ( 1)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL0_DataVccddqHi_MSK            (0x00080000)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL0_DataVccddqHi_MIN            (0)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL0_DataVccddqHi_MAX            (1) // 0x00000001
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL0_DataVccddqHi_DEF            (0x00000000)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL0_DataVccddqHi_HSH            (0x01131180)

  #define DDRDATA8CH1_CR_DDRCRDATACONTROL0_ReadRFRd_OFF                (20)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL0_ReadRFRd_WID                ( 1)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL0_ReadRFRd_MSK                (0x00100000)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL0_ReadRFRd_MIN                (0)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL0_ReadRFRd_MAX                (1) // 0x00000001
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL0_ReadRFRd_DEF                (0x00000000)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL0_ReadRFRd_HSH                (0x01141180)

  #define DDRDATA8CH1_CR_DDRCRDATACONTROL0_ReadRFWr_OFF                (21)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL0_ReadRFWr_WID                ( 1)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL0_ReadRFWr_MSK                (0x00200000)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL0_ReadRFWr_MIN                (0)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL0_ReadRFWr_MAX                (1) // 0x00000001
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL0_ReadRFWr_DEF                (0x00000000)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL0_ReadRFWr_HSH                (0x01151180)

  #define DDRDATA8CH1_CR_DDRCRDATACONTROL0_ReadRFRank_OFF              (22)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL0_ReadRFRank_WID              ( 2)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL0_ReadRFRank_MSK              (0x00C00000)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL0_ReadRFRank_MIN              (0)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL0_ReadRFRank_MAX              (3) // 0x00000003
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL0_ReadRFRank_DEF              (0x00000000)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL0_ReadRFRank_HSH              (0x02161180)

  #define DDRDATA8CH1_CR_DDRCRDATACONTROL0_ForceOdtOn_OFF              (24)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL0_ForceOdtOn_WID              ( 1)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL0_ForceOdtOn_MSK              (0x01000000)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL0_ForceOdtOn_MIN              (0)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL0_ForceOdtOn_MAX              (1) // 0x00000001
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL0_ForceOdtOn_DEF              (0x00000000)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL0_ForceOdtOn_HSH              (0x01181180)

  #define DDRDATA8CH1_CR_DDRCRDATACONTROL0_OdtSampOff_OFF              (25)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL0_OdtSampOff_WID              ( 1)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL0_OdtSampOff_MSK              (0x02000000)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL0_OdtSampOff_MIN              (0)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL0_OdtSampOff_MAX              (1) // 0x00000001
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL0_OdtSampOff_DEF              (0x00000000)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL0_OdtSampOff_HSH              (0x01191180)

  #define DDRDATA8CH1_CR_DDRCRDATACONTROL0_DisableOdtStatic_OFF        (26)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL0_DisableOdtStatic_WID        ( 1)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL0_DisableOdtStatic_MSK        (0x04000000)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL0_DisableOdtStatic_MIN        (0)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL0_DisableOdtStatic_MAX        (1) // 0x00000001
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL0_DisableOdtStatic_DEF        (0x00000000)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL0_DisableOdtStatic_HSH        (0x011A1180)

  #define DDRDATA8CH1_CR_DDRCRDATACONTROL0_DdrCRForceODTOn_OFF         (27)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL0_DdrCRForceODTOn_WID         ( 1)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL0_DdrCRForceODTOn_MSK         (0x08000000)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL0_DdrCRForceODTOn_MIN         (0)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL0_DdrCRForceODTOn_MAX         (1) // 0x00000001
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL0_DdrCRForceODTOn_DEF         (0x00000000)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL0_DdrCRForceODTOn_HSH         (0x011B1180)

  #define DDRDATA8CH1_CR_DDRCRDATACONTROL0_LPDDR_Mode_OFF              (28)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL0_LPDDR_Mode_WID              ( 1)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL0_LPDDR_Mode_MSK              (0x10000000)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL0_LPDDR_Mode_MIN              (0)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL0_LPDDR_Mode_MAX              (1) // 0x00000001
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL0_LPDDR_Mode_DEF              (0x00000000)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL0_LPDDR_Mode_HSH              (0x011C1180)

  #define DDRDATA8CH1_CR_DDRCRDATACONTROL0_EnReadPreamble_OFF          (29)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL0_EnReadPreamble_WID          ( 1)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL0_EnReadPreamble_MSK          (0x20000000)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL0_EnReadPreamble_MIN          (0)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL0_EnReadPreamble_MAX          (1) // 0x00000001
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL0_EnReadPreamble_DEF          (0x00000000)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL0_EnReadPreamble_HSH          (0x011D1180)

  #define DDRDATA8CH1_CR_DDRCRDATACONTROL0_OdtSampExtendEn_OFF         (30)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL0_OdtSampExtendEn_WID         ( 1)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL0_OdtSampExtendEn_MSK         (0x40000000)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL0_OdtSampExtendEn_MIN         (0)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL0_OdtSampExtendEn_MAX         (1) // 0x00000001
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL0_OdtSampExtendEn_DEF         (0x00000000)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL0_OdtSampExtendEn_HSH         (0x011E1180)

  #define DDRDATA8CH1_CR_DDRCRDATACONTROL0_EarlyRleakEn_OFF            (31)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL0_EarlyRleakEn_WID            ( 1)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL0_EarlyRleakEn_MSK            (0x80000000)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL0_EarlyRleakEn_MIN            (0)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL0_EarlyRleakEn_MAX            (1) // 0x00000001
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL0_EarlyRleakEn_DEF            (0x00000000)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL0_EarlyRleakEn_HSH            (0x011F1180)

#define DDRDATA8CH1_CR_DDRCRVREFADJUST1_REG                            (0x00001184)

  #define DDRDATA8CH1_CR_DDRCRVREFADJUST1_CAVrefCtl_OFF                ( 0)
  #define DDRDATA8CH1_CR_DDRCRVREFADJUST1_CAVrefCtl_WID                ( 7)
  #define DDRDATA8CH1_CR_DDRCRVREFADJUST1_CAVrefCtl_MSK                (0x0000007F)
  #define DDRDATA8CH1_CR_DDRCRVREFADJUST1_CAVrefCtl_MIN                (-64)
  #define DDRDATA8CH1_CR_DDRCRVREFADJUST1_CAVrefCtl_MAX                (63) // 0x0000003F
  #define DDRDATA8CH1_CR_DDRCRVREFADJUST1_CAVrefCtl_DEF                (0x00000000)
  #define DDRDATA8CH1_CR_DDRCRVREFADJUST1_CAVrefCtl_HSH                (0x87001184)

  #define DDRDATA8CH1_CR_DDRCRVREFADJUST1_Ch1VrefCtl_OFF               ( 7)
  #define DDRDATA8CH1_CR_DDRCRVREFADJUST1_Ch1VrefCtl_WID               ( 7)
  #define DDRDATA8CH1_CR_DDRCRVREFADJUST1_Ch1VrefCtl_MSK               (0x00003F80)
  #define DDRDATA8CH1_CR_DDRCRVREFADJUST1_Ch1VrefCtl_MIN               (-64)
  #define DDRDATA8CH1_CR_DDRCRVREFADJUST1_Ch1VrefCtl_MAX               (63) // 0x0000003F
  #define DDRDATA8CH1_CR_DDRCRVREFADJUST1_Ch1VrefCtl_DEF               (0x00000000)
  #define DDRDATA8CH1_CR_DDRCRVREFADJUST1_Ch1VrefCtl_HSH               (0x87071184)

  #define DDRDATA8CH1_CR_DDRCRVREFADJUST1_Ch0VrefCtl_OFF               (14)
  #define DDRDATA8CH1_CR_DDRCRVREFADJUST1_Ch0VrefCtl_WID               ( 7)
  #define DDRDATA8CH1_CR_DDRCRVREFADJUST1_Ch0VrefCtl_MSK               (0x001FC000)
  #define DDRDATA8CH1_CR_DDRCRVREFADJUST1_Ch0VrefCtl_MIN               (-64)
  #define DDRDATA8CH1_CR_DDRCRVREFADJUST1_Ch0VrefCtl_MAX               (63) // 0x0000003F
  #define DDRDATA8CH1_CR_DDRCRVREFADJUST1_Ch0VrefCtl_DEF               (0x00000000)
  #define DDRDATA8CH1_CR_DDRCRVREFADJUST1_Ch0VrefCtl_HSH               (0x870E1184)

  #define DDRDATA8CH1_CR_DDRCRVREFADJUST1_EnDimmVrefCA_OFF             (21)
  #define DDRDATA8CH1_CR_DDRCRVREFADJUST1_EnDimmVrefCA_WID             ( 1)
  #define DDRDATA8CH1_CR_DDRCRVREFADJUST1_EnDimmVrefCA_MSK             (0x00200000)
  #define DDRDATA8CH1_CR_DDRCRVREFADJUST1_EnDimmVrefCA_MIN             (0)
  #define DDRDATA8CH1_CR_DDRCRVREFADJUST1_EnDimmVrefCA_MAX             (1) // 0x00000001
  #define DDRDATA8CH1_CR_DDRCRVREFADJUST1_EnDimmVrefCA_DEF             (0x00000000)
  #define DDRDATA8CH1_CR_DDRCRVREFADJUST1_EnDimmVrefCA_HSH             (0x01151184)

  #define DDRDATA8CH1_CR_DDRCRVREFADJUST1_EnDimmVrefCh1_OFF            (22)
  #define DDRDATA8CH1_CR_DDRCRVREFADJUST1_EnDimmVrefCh1_WID            ( 1)
  #define DDRDATA8CH1_CR_DDRCRVREFADJUST1_EnDimmVrefCh1_MSK            (0x00400000)
  #define DDRDATA8CH1_CR_DDRCRVREFADJUST1_EnDimmVrefCh1_MIN            (0)
  #define DDRDATA8CH1_CR_DDRCRVREFADJUST1_EnDimmVrefCh1_MAX            (1) // 0x00000001
  #define DDRDATA8CH1_CR_DDRCRVREFADJUST1_EnDimmVrefCh1_DEF            (0x00000000)
  #define DDRDATA8CH1_CR_DDRCRVREFADJUST1_EnDimmVrefCh1_HSH            (0x01161184)

  #define DDRDATA8CH1_CR_DDRCRVREFADJUST1_EnDimmVrefCh0_OFF            (23)
  #define DDRDATA8CH1_CR_DDRCRVREFADJUST1_EnDimmVrefCh0_WID            ( 1)
  #define DDRDATA8CH1_CR_DDRCRVREFADJUST1_EnDimmVrefCh0_MSK            (0x00800000)
  #define DDRDATA8CH1_CR_DDRCRVREFADJUST1_EnDimmVrefCh0_MIN            (0)
  #define DDRDATA8CH1_CR_DDRCRVREFADJUST1_EnDimmVrefCh0_MAX            (1) // 0x00000001
  #define DDRDATA8CH1_CR_DDRCRVREFADJUST1_EnDimmVrefCh0_DEF            (0x00000000)
  #define DDRDATA8CH1_CR_DDRCRVREFADJUST1_EnDimmVrefCh0_HSH            (0x01171184)

  #define DDRDATA8CH1_CR_DDRCRVREFADJUST1_HiZTimerCtrl_OFF             (24)
  #define DDRDATA8CH1_CR_DDRCRVREFADJUST1_HiZTimerCtrl_WID             ( 2)
  #define DDRDATA8CH1_CR_DDRCRVREFADJUST1_HiZTimerCtrl_MSK             (0x03000000)
  #define DDRDATA8CH1_CR_DDRCRVREFADJUST1_HiZTimerCtrl_MIN             (0)
  #define DDRDATA8CH1_CR_DDRCRVREFADJUST1_HiZTimerCtrl_MAX             (3) // 0x00000003
  #define DDRDATA8CH1_CR_DDRCRVREFADJUST1_HiZTimerCtrl_DEF             (0x00000000)
  #define DDRDATA8CH1_CR_DDRCRVREFADJUST1_HiZTimerCtrl_HSH             (0x02181184)

  #define DDRDATA8CH1_CR_DDRCRVREFADJUST1_VccddqHiQnnnH_OFF            (26)
  #define DDRDATA8CH1_CR_DDRCRVREFADJUST1_VccddqHiQnnnH_WID            ( 1)
  #define DDRDATA8CH1_CR_DDRCRVREFADJUST1_VccddqHiQnnnH_MSK            (0x04000000)
  #define DDRDATA8CH1_CR_DDRCRVREFADJUST1_VccddqHiQnnnH_MIN            (0)
  #define DDRDATA8CH1_CR_DDRCRVREFADJUST1_VccddqHiQnnnH_MAX            (1) // 0x00000001
  #define DDRDATA8CH1_CR_DDRCRVREFADJUST1_VccddqHiQnnnH_DEF            (0x00000000)
  #define DDRDATA8CH1_CR_DDRCRVREFADJUST1_VccddqHiQnnnH_HSH            (0x011A1184)

  #define DDRDATA8CH1_CR_DDRCRVREFADJUST1_Rsvd_OFF                     (27)
  #define DDRDATA8CH1_CR_DDRCRVREFADJUST1_Rsvd_WID                     ( 2)
  #define DDRDATA8CH1_CR_DDRCRVREFADJUST1_Rsvd_MSK                     (0x18000000)
  #define DDRDATA8CH1_CR_DDRCRVREFADJUST1_Rsvd_MIN                     (0)
  #define DDRDATA8CH1_CR_DDRCRVREFADJUST1_Rsvd_MAX                     (3) // 0x00000003
  #define DDRDATA8CH1_CR_DDRCRVREFADJUST1_Rsvd_DEF                     (0x00000000)
  #define DDRDATA8CH1_CR_DDRCRVREFADJUST1_Rsvd_HSH                     (0x021B1184)

  #define DDRDATA8CH1_CR_DDRCRVREFADJUST1_caSlowBW_OFF                 (29)
  #define DDRDATA8CH1_CR_DDRCRVREFADJUST1_caSlowBW_WID                 ( 1)
  #define DDRDATA8CH1_CR_DDRCRVREFADJUST1_caSlowBW_MSK                 (0x20000000)
  #define DDRDATA8CH1_CR_DDRCRVREFADJUST1_caSlowBW_MIN                 (0)
  #define DDRDATA8CH1_CR_DDRCRVREFADJUST1_caSlowBW_MAX                 (1) // 0x00000001
  #define DDRDATA8CH1_CR_DDRCRVREFADJUST1_caSlowBW_DEF                 (0x00000000)
  #define DDRDATA8CH1_CR_DDRCRVREFADJUST1_caSlowBW_HSH                 (0x011D1184)

  #define DDRDATA8CH1_CR_DDRCRVREFADJUST1_ch0SlowBW_OFF                (30)
  #define DDRDATA8CH1_CR_DDRCRVREFADJUST1_ch0SlowBW_WID                ( 1)
  #define DDRDATA8CH1_CR_DDRCRVREFADJUST1_ch0SlowBW_MSK                (0x40000000)
  #define DDRDATA8CH1_CR_DDRCRVREFADJUST1_ch0SlowBW_MIN                (0)
  #define DDRDATA8CH1_CR_DDRCRVREFADJUST1_ch0SlowBW_MAX                (1) // 0x00000001
  #define DDRDATA8CH1_CR_DDRCRVREFADJUST1_ch0SlowBW_DEF                (0x00000000)
  #define DDRDATA8CH1_CR_DDRCRVREFADJUST1_ch0SlowBW_HSH                (0x011E1184)

  #define DDRDATA8CH1_CR_DDRCRVREFADJUST1_ch1SlowBW_OFF                (31)
  #define DDRDATA8CH1_CR_DDRCRVREFADJUST1_ch1SlowBW_WID                ( 1)
  #define DDRDATA8CH1_CR_DDRCRVREFADJUST1_ch1SlowBW_MSK                (0x80000000)
  #define DDRDATA8CH1_CR_DDRCRVREFADJUST1_ch1SlowBW_MIN                (0)
  #define DDRDATA8CH1_CR_DDRCRVREFADJUST1_ch1SlowBW_MAX                (1) // 0x00000001
  #define DDRDATA8CH1_CR_DDRCRVREFADJUST1_ch1SlowBW_DEF                (0x00000000)
  #define DDRDATA8CH1_CR_DDRCRVREFADJUST1_ch1SlowBW_HSH                (0x011F1184)

#define DDRDATA8CH1_CR_DDRCRDATACONTROL3_REG                           (0x00001188)

  #define DDRDATA8CH1_CR_DDRCRDATACONTROL3_AttackerDataBit0_OFF        ( 0)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL3_AttackerDataBit0_WID        ( 3)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL3_AttackerDataBit0_MSK        (0x00000007)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL3_AttackerDataBit0_MIN        (0)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL3_AttackerDataBit0_MAX        (7) // 0x00000007
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL3_AttackerDataBit0_DEF        (0x00000000)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL3_AttackerDataBit0_HSH        (0x03001188)

  #define DDRDATA8CH1_CR_DDRCRDATACONTROL3_AttackerDataBit1_OFF        ( 3)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL3_AttackerDataBit1_WID        ( 3)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL3_AttackerDataBit1_MSK        (0x00000038)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL3_AttackerDataBit1_MIN        (0)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL3_AttackerDataBit1_MAX        (7) // 0x00000007
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL3_AttackerDataBit1_DEF        (0x00000000)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL3_AttackerDataBit1_HSH        (0x03031188)

  #define DDRDATA8CH1_CR_DDRCRDATACONTROL3_AttackerDataBit2_OFF        ( 6)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL3_AttackerDataBit2_WID        ( 3)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL3_AttackerDataBit2_MSK        (0x000001C0)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL3_AttackerDataBit2_MIN        (0)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL3_AttackerDataBit2_MAX        (7) // 0x00000007
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL3_AttackerDataBit2_DEF        (0x00000000)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL3_AttackerDataBit2_HSH        (0x03061188)

  #define DDRDATA8CH1_CR_DDRCRDATACONTROL3_AttackerDataBit3_OFF        ( 9)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL3_AttackerDataBit3_WID        ( 3)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL3_AttackerDataBit3_MSK        (0x00000E00)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL3_AttackerDataBit3_MIN        (0)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL3_AttackerDataBit3_MAX        (7) // 0x00000007
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL3_AttackerDataBit3_DEF        (0x00000000)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL3_AttackerDataBit3_HSH        (0x03091188)

  #define DDRDATA8CH1_CR_DDRCRDATACONTROL3_AttackerDataBit4_OFF        (12)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL3_AttackerDataBit4_WID        ( 3)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL3_AttackerDataBit4_MSK        (0x00007000)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL3_AttackerDataBit4_MIN        (0)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL3_AttackerDataBit4_MAX        (7) // 0x00000007
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL3_AttackerDataBit4_DEF        (0x00000000)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL3_AttackerDataBit4_HSH        (0x030C1188)

  #define DDRDATA8CH1_CR_DDRCRDATACONTROL3_AttackerDataBit5_OFF        (15)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL3_AttackerDataBit5_WID        ( 3)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL3_AttackerDataBit5_MSK        (0x00038000)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL3_AttackerDataBit5_MIN        (0)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL3_AttackerDataBit5_MAX        (7) // 0x00000007
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL3_AttackerDataBit5_DEF        (0x00000000)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL3_AttackerDataBit5_HSH        (0x030F1188)

  #define DDRDATA8CH1_CR_DDRCRDATACONTROL3_AttackerDataBit6_OFF        (18)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL3_AttackerDataBit6_WID        ( 3)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL3_AttackerDataBit6_MSK        (0x001C0000)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL3_AttackerDataBit6_MIN        (0)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL3_AttackerDataBit6_MAX        (7) // 0x00000007
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL3_AttackerDataBit6_DEF        (0x00000000)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL3_AttackerDataBit6_HSH        (0x03121188)

  #define DDRDATA8CH1_CR_DDRCRDATACONTROL3_AttackerDataBit7_OFF        (21)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL3_AttackerDataBit7_WID        ( 3)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL3_AttackerDataBit7_MSK        (0x00E00000)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL3_AttackerDataBit7_MIN        (0)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL3_AttackerDataBit7_MAX        (7) // 0x00000007
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL3_AttackerDataBit7_DEF        (0x00000000)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL3_AttackerDataBit7_HSH        (0x03151188)

  #define DDRDATA8CH1_CR_DDRCRDATACONTROL3_CBEnAmp2_OFF                (24)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL3_CBEnAmp2_WID                ( 3)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL3_CBEnAmp2_MSK                (0x07000000)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL3_CBEnAmp2_MIN                (0)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL3_CBEnAmp2_MAX                (7) // 0x00000007
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL3_CBEnAmp2_DEF                (0x00000003)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL3_CBEnAmp2_HSH                (0x03181188)

  #define DDRDATA8CH1_CR_DDRCRDATACONTROL3_CBpEnAmp2_b_OFF             (27)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL3_CBpEnAmp2_b_WID             ( 3)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL3_CBpEnAmp2_b_MSK             (0x38000000)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL3_CBpEnAmp2_b_MIN             (0)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL3_CBpEnAmp2_b_MAX             (7) // 0x00000007
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL3_CBpEnAmp2_b_DEF             (0x00000003)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL3_CBpEnAmp2_b_HSH             (0x031B1188)

  #define DDRDATA8CH1_CR_DDRCRDATACONTROL3_CBEnAmp1_OFF                (30)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL3_CBEnAmp1_WID                ( 2)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL3_CBEnAmp1_MSK                (0xC0000000)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL3_CBEnAmp1_MIN                (0)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL3_CBEnAmp1_MAX                (3) // 0x00000003
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL3_CBEnAmp1_DEF                (0x00000001)
  #define DDRDATA8CH1_CR_DDRCRDATACONTROL3_CBEnAmp1_HSH                (0x021E1188)

#define DDRDATA8CH1_CR_DDRCRVTTGENCONTROL_REG                          (0x0000118C)

  #define DDRDATA8CH1_CR_DDRCRVTTGENCONTROL_Target_OFF                 ( 0)
  #define DDRDATA8CH1_CR_DDRCRVTTGENCONTROL_Target_WID                 ( 4)
  #define DDRDATA8CH1_CR_DDRCRVTTGENCONTROL_Target_MSK                 (0x0000000F)
  #define DDRDATA8CH1_CR_DDRCRVTTGENCONTROL_Target_MIN                 (0)
  #define DDRDATA8CH1_CR_DDRCRVTTGENCONTROL_Target_MAX                 (15) // 0x0000000F
  #define DDRDATA8CH1_CR_DDRCRVTTGENCONTROL_Target_DEF                 (0x00000000)
  #define DDRDATA8CH1_CR_DDRCRVTTGENCONTROL_Target_HSH                 (0x0400118C)

  #define DDRDATA8CH1_CR_DDRCRVTTGENCONTROL_Panic_OFF                  ( 4)
  #define DDRDATA8CH1_CR_DDRCRVTTGENCONTROL_Panic_WID                  ( 5)
  #define DDRDATA8CH1_CR_DDRCRVTTGENCONTROL_Panic_MSK                  (0x000001F0)
  #define DDRDATA8CH1_CR_DDRCRVTTGENCONTROL_Panic_MIN                  (0)
  #define DDRDATA8CH1_CR_DDRCRVTTGENCONTROL_Panic_MAX                  (31) // 0x0000001F
  #define DDRDATA8CH1_CR_DDRCRVTTGENCONTROL_Panic_DEF                  (0x00000010)
  #define DDRDATA8CH1_CR_DDRCRVTTGENCONTROL_Panic_HSH                  (0x0504118C)

  #define DDRDATA8CH1_CR_DDRCRVTTGENCONTROL_DisPanicDrv_OFF            ( 9)
  #define DDRDATA8CH1_CR_DDRCRVTTGENCONTROL_DisPanicDrv_WID            ( 2)
  #define DDRDATA8CH1_CR_DDRCRVTTGENCONTROL_DisPanicDrv_MSK            (0x00000600)
  #define DDRDATA8CH1_CR_DDRCRVTTGENCONTROL_DisPanicDrv_MIN            (0)
  #define DDRDATA8CH1_CR_DDRCRVTTGENCONTROL_DisPanicDrv_MAX            (3) // 0x00000003
  #define DDRDATA8CH1_CR_DDRCRVTTGENCONTROL_DisPanicDrv_DEF            (0x00000000)
  #define DDRDATA8CH1_CR_DDRCRVTTGENCONTROL_DisPanicDrv_HSH            (0x0209118C)

  #define DDRDATA8CH1_CR_DDRCRVTTGENCONTROL_DisSensorPwrDn_OFF         (11)
  #define DDRDATA8CH1_CR_DDRCRVTTGENCONTROL_DisSensorPwrDn_WID         ( 1)
  #define DDRDATA8CH1_CR_DDRCRVTTGENCONTROL_DisSensorPwrDn_MSK         (0x00000800)
  #define DDRDATA8CH1_CR_DDRCRVTTGENCONTROL_DisSensorPwrDn_MIN         (0)
  #define DDRDATA8CH1_CR_DDRCRVTTGENCONTROL_DisSensorPwrDn_MAX         (1) // 0x00000001
  #define DDRDATA8CH1_CR_DDRCRVTTGENCONTROL_DisSensorPwrDn_DEF         (0x00000000)
  #define DDRDATA8CH1_CR_DDRCRVTTGENCONTROL_DisSensorPwrDn_HSH         (0x010B118C)

  #define DDRDATA8CH1_CR_DDRCRVTTGENCONTROL_OfstOvrdEn_OFF             (12)
  #define DDRDATA8CH1_CR_DDRCRVTTGENCONTROL_OfstOvrdEn_WID             ( 1)
  #define DDRDATA8CH1_CR_DDRCRVTTGENCONTROL_OfstOvrdEn_MSK             (0x00001000)
  #define DDRDATA8CH1_CR_DDRCRVTTGENCONTROL_OfstOvrdEn_MIN             (0)
  #define DDRDATA8CH1_CR_DDRCRVTTGENCONTROL_OfstOvrdEn_MAX             (1) // 0x00000001
  #define DDRDATA8CH1_CR_DDRCRVTTGENCONTROL_OfstOvrdEn_DEF             (0x00000000)
  #define DDRDATA8CH1_CR_DDRCRVTTGENCONTROL_OfstOvrdEn_HSH             (0x010C118C)

  #define DDRDATA8CH1_CR_DDRCRVTTGENCONTROL_ViewOfstsel_OFF            (13)
  #define DDRDATA8CH1_CR_DDRCRVTTGENCONTROL_ViewOfstsel_WID            ( 3)
  #define DDRDATA8CH1_CR_DDRCRVTTGENCONTROL_ViewOfstsel_MSK            (0x0000E000)
  #define DDRDATA8CH1_CR_DDRCRVTTGENCONTROL_ViewOfstsel_MIN            (0)
  #define DDRDATA8CH1_CR_DDRCRVTTGENCONTROL_ViewOfstsel_MAX            (7) // 0x00000007
  #define DDRDATA8CH1_CR_DDRCRVTTGENCONTROL_ViewOfstsel_DEF            (0x00000000)
  #define DDRDATA8CH1_CR_DDRCRVTTGENCONTROL_ViewOfstsel_HSH            (0x030D118C)

  #define DDRDATA8CH1_CR_DDRCRVTTGENCONTROL_EnVttCompforVsshi_OFF      (16)
  #define DDRDATA8CH1_CR_DDRCRVTTGENCONTROL_EnVttCompforVsshi_WID      ( 1)
  #define DDRDATA8CH1_CR_DDRCRVTTGENCONTROL_EnVttCompforVsshi_MSK      (0x00010000)
  #define DDRDATA8CH1_CR_DDRCRVTTGENCONTROL_EnVttCompforVsshi_MIN      (0)
  #define DDRDATA8CH1_CR_DDRCRVTTGENCONTROL_EnVttCompforVsshi_MAX      (1) // 0x00000001
  #define DDRDATA8CH1_CR_DDRCRVTTGENCONTROL_EnVttCompforVsshi_DEF      (0x00000000)
  #define DDRDATA8CH1_CR_DDRCRVTTGENCONTROL_EnVttCompforVsshi_HSH      (0x0110118C)

  #define DDRDATA8CH1_CR_DDRCRVTTGENCONTROL_Spares_OFF                 (17)
  #define DDRDATA8CH1_CR_DDRCRVTTGENCONTROL_Spares_WID                 ( 8)
  #define DDRDATA8CH1_CR_DDRCRVTTGENCONTROL_Spares_MSK                 (0x01FE0000)
  #define DDRDATA8CH1_CR_DDRCRVTTGENCONTROL_Spares_MIN                 (0)
  #define DDRDATA8CH1_CR_DDRCRVTTGENCONTROL_Spares_MAX                 (255) // 0x000000FF
  #define DDRDATA8CH1_CR_DDRCRVTTGENCONTROL_Spares_DEF                 (0x00000000)
  #define DDRDATA8CH1_CR_DDRCRVTTGENCONTROL_Spares_HSH                 (0x0811118C)

  #define DDRDATA8CH1_CR_DDRCRVTTGENCONTROL_Disable2Vt_OFF             (25)
  #define DDRDATA8CH1_CR_DDRCRVTTGENCONTROL_Disable2Vt_WID             ( 1)
  #define DDRDATA8CH1_CR_DDRCRVTTGENCONTROL_Disable2Vt_MSK             (0x02000000)
  #define DDRDATA8CH1_CR_DDRCRVTTGENCONTROL_Disable2Vt_MIN             (0)
  #define DDRDATA8CH1_CR_DDRCRVTTGENCONTROL_Disable2Vt_MAX             (1) // 0x00000001
  #define DDRDATA8CH1_CR_DDRCRVTTGENCONTROL_Disable2Vt_DEF             (0x00000000)
  #define DDRDATA8CH1_CR_DDRCRVTTGENCONTROL_Disable2Vt_HSH             (0x0119118C)

  #define DDRDATA8CH1_CR_DDRCRVTTGENCONTROL_OfstOvrdOrView_OFF         (26)
  #define DDRDATA8CH1_CR_DDRCRVTTGENCONTROL_OfstOvrdOrView_WID         ( 6)
  #define DDRDATA8CH1_CR_DDRCRVTTGENCONTROL_OfstOvrdOrView_MSK         (0xFC000000)
  #define DDRDATA8CH1_CR_DDRCRVTTGENCONTROL_OfstOvrdOrView_MIN         (0)
  #define DDRDATA8CH1_CR_DDRCRVTTGENCONTROL_OfstOvrdOrView_MAX         (63) // 0x0000003F
  #define DDRDATA8CH1_CR_DDRCRVTTGENCONTROL_OfstOvrdOrView_DEF         (0x00000000)
  #define DDRDATA8CH1_CR_DDRCRVTTGENCONTROL_OfstOvrdOrView_HSH         (0x061A118C)

#define DDRCKECH0_CR_DDRCRCMDCOMP_REG                                  (0x00001200)

  #define DDRCKECH0_CR_DDRCRCMDCOMP_Scomp_OFF                          ( 0)
  #define DDRCKECH0_CR_DDRCRCMDCOMP_Scomp_WID                          ( 6)
  #define DDRCKECH0_CR_DDRCRCMDCOMP_Scomp_MSK                          (0x0000003F)
  #define DDRCKECH0_CR_DDRCRCMDCOMP_Scomp_MIN                          (0)
  #define DDRCKECH0_CR_DDRCRCMDCOMP_Scomp_MAX                          (63) // 0x0000003F
  #define DDRCKECH0_CR_DDRCRCMDCOMP_Scomp_DEF                          (0x00000000)
  #define DDRCKECH0_CR_DDRCRCMDCOMP_Scomp_HSH                          (0x06001200)

  #define DDRCKECH0_CR_DDRCRCMDCOMP_TcoComp_OFF                        ( 6)
  #define DDRCKECH0_CR_DDRCRCMDCOMP_TcoComp_WID                        ( 6)
  #define DDRCKECH0_CR_DDRCRCMDCOMP_TcoComp_MSK                        (0x00000FC0)
  #define DDRCKECH0_CR_DDRCRCMDCOMP_TcoComp_MIN                        (0)
  #define DDRCKECH0_CR_DDRCRCMDCOMP_TcoComp_MAX                        (63) // 0x0000003F
  #define DDRCKECH0_CR_DDRCRCMDCOMP_TcoComp_DEF                        (0x00000000)
  #define DDRCKECH0_CR_DDRCRCMDCOMP_TcoComp_HSH                        (0x06061200)

  #define DDRCKECH0_CR_DDRCRCMDCOMP_RcompDrvUp_OFF                     (12)
  #define DDRCKECH0_CR_DDRCRCMDCOMP_RcompDrvUp_WID                     ( 6)
  #define DDRCKECH0_CR_DDRCRCMDCOMP_RcompDrvUp_MSK                     (0x0003F000)
  #define DDRCKECH0_CR_DDRCRCMDCOMP_RcompDrvUp_MIN                     (0)
  #define DDRCKECH0_CR_DDRCRCMDCOMP_RcompDrvUp_MAX                     (63) // 0x0000003F
  #define DDRCKECH0_CR_DDRCRCMDCOMP_RcompDrvUp_DEF                     (0x00000000)
  #define DDRCKECH0_CR_DDRCRCMDCOMP_RcompDrvUp_HSH                     (0x060C1200)

  #define DDRCKECH0_CR_DDRCRCMDCOMP_RcompDrvDown_OFF                   (18)
  #define DDRCKECH0_CR_DDRCRCMDCOMP_RcompDrvDown_WID                   ( 6)
  #define DDRCKECH0_CR_DDRCRCMDCOMP_RcompDrvDown_MSK                   (0x00FC0000)
  #define DDRCKECH0_CR_DDRCRCMDCOMP_RcompDrvDown_MIN                   (0)
  #define DDRCKECH0_CR_DDRCRCMDCOMP_RcompDrvDown_MAX                   (63) // 0x0000003F
  #define DDRCKECH0_CR_DDRCRCMDCOMP_RcompDrvDown_DEF                   (0x00000000)
  #define DDRCKECH0_CR_DDRCRCMDCOMP_RcompDrvDown_HSH                   (0x06121200)

  #define DDRCKECH0_CR_DDRCRCMDCOMP_Spare_OFF                          (24)
  #define DDRCKECH0_CR_DDRCRCMDCOMP_Spare_WID                          ( 8)
  #define DDRCKECH0_CR_DDRCRCMDCOMP_Spare_MSK                          (0xFF000000)
  #define DDRCKECH0_CR_DDRCRCMDCOMP_Spare_MIN                          (0)
  #define DDRCKECH0_CR_DDRCRCMDCOMP_Spare_MAX                          (255) // 0x000000FF
  #define DDRCKECH0_CR_DDRCRCMDCOMP_Spare_DEF                          (0x00000004)
  #define DDRCKECH0_CR_DDRCRCMDCOMP_Spare_HSH                          (0x08181200)

#define DDRCKECH0_CR_DDRCRCMDCOMPOFFSET_REG                            (0x00001204)

  #define DDRCKECH0_CR_DDRCRCMDCOMPOFFSET_ScompOffset_OFF              ( 0)
  #define DDRCKECH0_CR_DDRCRCMDCOMPOFFSET_ScompOffset_WID              ( 5)
  #define DDRCKECH0_CR_DDRCRCMDCOMPOFFSET_ScompOffset_MSK              (0x0000001F)
  #define DDRCKECH0_CR_DDRCRCMDCOMPOFFSET_ScompOffset_MIN              (-16)
  #define DDRCKECH0_CR_DDRCRCMDCOMPOFFSET_ScompOffset_MAX              (15) // 0x0000000F
  #define DDRCKECH0_CR_DDRCRCMDCOMPOFFSET_ScompOffset_DEF              (0x00000000)
  #define DDRCKECH0_CR_DDRCRCMDCOMPOFFSET_ScompOffset_HSH              (0x85001204)

  #define DDRCKECH0_CR_DDRCRCMDCOMPOFFSET_TcoCompOffset_OFF            ( 5)
  #define DDRCKECH0_CR_DDRCRCMDCOMPOFFSET_TcoCompOffset_WID            ( 4)
  #define DDRCKECH0_CR_DDRCRCMDCOMPOFFSET_TcoCompOffset_MSK            (0x000001E0)
  #define DDRCKECH0_CR_DDRCRCMDCOMPOFFSET_TcoCompOffset_MIN            (-8)
  #define DDRCKECH0_CR_DDRCRCMDCOMPOFFSET_TcoCompOffset_MAX            (7) // 0x00000007
  #define DDRCKECH0_CR_DDRCRCMDCOMPOFFSET_TcoCompOffset_DEF            (0x00000000)
  #define DDRCKECH0_CR_DDRCRCMDCOMPOFFSET_TcoCompOffset_HSH            (0x84051204)

  #define DDRCKECH0_CR_DDRCRCMDCOMPOFFSET_RcompDrvUpOffset_OFF         ( 9)
  #define DDRCKECH0_CR_DDRCRCMDCOMPOFFSET_RcompDrvUpOffset_WID         ( 4)
  #define DDRCKECH0_CR_DDRCRCMDCOMPOFFSET_RcompDrvUpOffset_MSK         (0x00001E00)
  #define DDRCKECH0_CR_DDRCRCMDCOMPOFFSET_RcompDrvUpOffset_MIN         (-8)
  #define DDRCKECH0_CR_DDRCRCMDCOMPOFFSET_RcompDrvUpOffset_MAX         (7) // 0x00000007
  #define DDRCKECH0_CR_DDRCRCMDCOMPOFFSET_RcompDrvUpOffset_DEF         (0x00000000)
  #define DDRCKECH0_CR_DDRCRCMDCOMPOFFSET_RcompDrvUpOffset_HSH         (0x84091204)

  #define DDRCKECH0_CR_DDRCRCMDCOMPOFFSET_RcompDrvDownOffset_OFF       (13)
  #define DDRCKECH0_CR_DDRCRCMDCOMPOFFSET_RcompDrvDownOffset_WID       ( 4)
  #define DDRCKECH0_CR_DDRCRCMDCOMPOFFSET_RcompDrvDownOffset_MSK       (0x0001E000)
  #define DDRCKECH0_CR_DDRCRCMDCOMPOFFSET_RcompDrvDownOffset_MIN       (-8)
  #define DDRCKECH0_CR_DDRCRCMDCOMPOFFSET_RcompDrvDownOffset_MAX       (7) // 0x00000007
  #define DDRCKECH0_CR_DDRCRCMDCOMPOFFSET_RcompDrvDownOffset_DEF       (0x00000000)
  #define DDRCKECH0_CR_DDRCRCMDCOMPOFFSET_RcompDrvDownOffset_HSH       (0x840D1204)

  #define DDRCKECH0_CR_DDRCRCMDCOMPOFFSET_Spare_OFF                    (17)
  #define DDRCKECH0_CR_DDRCRCMDCOMPOFFSET_Spare_WID                    (15)
  #define DDRCKECH0_CR_DDRCRCMDCOMPOFFSET_Spare_MSK                    (0xFFFE0000)
  #define DDRCKECH0_CR_DDRCRCMDCOMPOFFSET_Spare_MIN                    (0)
  #define DDRCKECH0_CR_DDRCRCMDCOMPOFFSET_Spare_MAX                    (32767) // 0x00007FFF
  #define DDRCKECH0_CR_DDRCRCMDCOMPOFFSET_Spare_DEF                    (0x00000000)
  #define DDRCKECH0_CR_DDRCRCMDCOMPOFFSET_Spare_HSH                    (0x0F111204)

#define DDRCKECH0_CR_DDRCRCMDPICODING_REG                              (0x00001208)

  #define DDRCKECH0_CR_DDRCRCMDPICODING_CmdPi0Code_OFF                 ( 0)
  #define DDRCKECH0_CR_DDRCRCMDPICODING_CmdPi0Code_WID                 ( 7)
  #define DDRCKECH0_CR_DDRCRCMDPICODING_CmdPi0Code_MSK                 (0x0000007F)
  #define DDRCKECH0_CR_DDRCRCMDPICODING_CmdPi0Code_MIN                 (0)
  #define DDRCKECH0_CR_DDRCRCMDPICODING_CmdPi0Code_MAX                 (127) // 0x0000007F
  #define DDRCKECH0_CR_DDRCRCMDPICODING_CmdPi0Code_DEF                 (0x00000000)
  #define DDRCKECH0_CR_DDRCRCMDPICODING_CmdPi0Code_HSH                 (0x07001208)

  #define DDRCKECH0_CR_DDRCRCMDPICODING_CmdPi1Code_OFF                 ( 7)
  #define DDRCKECH0_CR_DDRCRCMDPICODING_CmdPi1Code_WID                 ( 7)
  #define DDRCKECH0_CR_DDRCRCMDPICODING_CmdPi1Code_MSK                 (0x00003F80)
  #define DDRCKECH0_CR_DDRCRCMDPICODING_CmdPi1Code_MIN                 (0)
  #define DDRCKECH0_CR_DDRCRCMDPICODING_CmdPi1Code_MAX                 (127) // 0x0000007F
  #define DDRCKECH0_CR_DDRCRCMDPICODING_CmdPi1Code_DEF                 (0x00000000)
  #define DDRCKECH0_CR_DDRCRCMDPICODING_CmdPi1Code_HSH                 (0x07071208)

  #define DDRCKECH0_CR_DDRCRCMDPICODING_Spare_OFF                      (14)
  #define DDRCKECH0_CR_DDRCRCMDPICODING_Spare_WID                      (18)
  #define DDRCKECH0_CR_DDRCRCMDPICODING_Spare_MSK                      (0xFFFFC000)
  #define DDRCKECH0_CR_DDRCRCMDPICODING_Spare_MIN                      (0)
  #define DDRCKECH0_CR_DDRCRCMDPICODING_Spare_MAX                      (262143) // 0x0003FFFF
  #define DDRCKECH0_CR_DDRCRCMDPICODING_Spare_DEF                      (0x00000000)
  #define DDRCKECH0_CR_DDRCRCMDPICODING_Spare_HSH                      (0x120E1208)

#define DDRCKECH0_CR_DDRCRCTLCOMP_REG                                  (0x00001210)

  #define DDRCKECH0_CR_DDRCRCTLCOMP_Scomp_OFF                          ( 0)
  #define DDRCKECH0_CR_DDRCRCTLCOMP_Scomp_WID                          ( 6)
  #define DDRCKECH0_CR_DDRCRCTLCOMP_Scomp_MSK                          (0x0000003F)
  #define DDRCKECH0_CR_DDRCRCTLCOMP_Scomp_MIN                          (0)
  #define DDRCKECH0_CR_DDRCRCTLCOMP_Scomp_MAX                          (63) // 0x0000003F
  #define DDRCKECH0_CR_DDRCRCTLCOMP_Scomp_DEF                          (0x00000000)
  #define DDRCKECH0_CR_DDRCRCTLCOMP_Scomp_HSH                          (0x06001210)

  #define DDRCKECH0_CR_DDRCRCTLCOMP_TcoComp_OFF                        ( 6)
  #define DDRCKECH0_CR_DDRCRCTLCOMP_TcoComp_WID                        ( 6)
  #define DDRCKECH0_CR_DDRCRCTLCOMP_TcoComp_MSK                        (0x00000FC0)
  #define DDRCKECH0_CR_DDRCRCTLCOMP_TcoComp_MIN                        (0)
  #define DDRCKECH0_CR_DDRCRCTLCOMP_TcoComp_MAX                        (63) // 0x0000003F
  #define DDRCKECH0_CR_DDRCRCTLCOMP_TcoComp_DEF                        (0x00000000)
  #define DDRCKECH0_CR_DDRCRCTLCOMP_TcoComp_HSH                        (0x06061210)

  #define DDRCKECH0_CR_DDRCRCTLCOMP_RcompDrvUp_OFF                     (12)
  #define DDRCKECH0_CR_DDRCRCTLCOMP_RcompDrvUp_WID                     ( 6)
  #define DDRCKECH0_CR_DDRCRCTLCOMP_RcompDrvUp_MSK                     (0x0003F000)
  #define DDRCKECH0_CR_DDRCRCTLCOMP_RcompDrvUp_MIN                     (0)
  #define DDRCKECH0_CR_DDRCRCTLCOMP_RcompDrvUp_MAX                     (63) // 0x0000003F
  #define DDRCKECH0_CR_DDRCRCTLCOMP_RcompDrvUp_DEF                     (0x00000000)
  #define DDRCKECH0_CR_DDRCRCTLCOMP_RcompDrvUp_HSH                     (0x060C1210)

  #define DDRCKECH0_CR_DDRCRCTLCOMP_RcompDrvDown_OFF                   (18)
  #define DDRCKECH0_CR_DDRCRCTLCOMP_RcompDrvDown_WID                   ( 6)
  #define DDRCKECH0_CR_DDRCRCTLCOMP_RcompDrvDown_MSK                   (0x00FC0000)
  #define DDRCKECH0_CR_DDRCRCTLCOMP_RcompDrvDown_MIN                   (0)
  #define DDRCKECH0_CR_DDRCRCTLCOMP_RcompDrvDown_MAX                   (63) // 0x0000003F
  #define DDRCKECH0_CR_DDRCRCTLCOMP_RcompDrvDown_DEF                   (0x00000000)
  #define DDRCKECH0_CR_DDRCRCTLCOMP_RcompDrvDown_HSH                   (0x06121210)

  #define DDRCKECH0_CR_DDRCRCTLCOMP_Spare_OFF                          (24)
  #define DDRCKECH0_CR_DDRCRCTLCOMP_Spare_WID                          ( 8)
  #define DDRCKECH0_CR_DDRCRCTLCOMP_Spare_MSK                          (0xFF000000)
  #define DDRCKECH0_CR_DDRCRCTLCOMP_Spare_MIN                          (0)
  #define DDRCKECH0_CR_DDRCRCTLCOMP_Spare_MAX                          (255) // 0x000000FF
  #define DDRCKECH0_CR_DDRCRCTLCOMP_Spare_DEF                          (0x00000000)
  #define DDRCKECH0_CR_DDRCRCTLCOMP_Spare_HSH                          (0x08181210)

#define DDRCKECH0_CR_DDRCRCTLCOMPOFFSET_REG                            (0x00001214)

  #define DDRCKECH0_CR_DDRCRCTLCOMPOFFSET_ScompOffset_OFF              ( 0)
  #define DDRCKECH0_CR_DDRCRCTLCOMPOFFSET_ScompOffset_WID              ( 5)
  #define DDRCKECH0_CR_DDRCRCTLCOMPOFFSET_ScompOffset_MSK              (0x0000001F)
  #define DDRCKECH0_CR_DDRCRCTLCOMPOFFSET_ScompOffset_MIN              (-16)
  #define DDRCKECH0_CR_DDRCRCTLCOMPOFFSET_ScompOffset_MAX              (15) // 0x0000000F
  #define DDRCKECH0_CR_DDRCRCTLCOMPOFFSET_ScompOffset_DEF              (0x00000000)
  #define DDRCKECH0_CR_DDRCRCTLCOMPOFFSET_ScompOffset_HSH              (0x85001214)

  #define DDRCKECH0_CR_DDRCRCTLCOMPOFFSET_TcoCompOffset_OFF            ( 5)
  #define DDRCKECH0_CR_DDRCRCTLCOMPOFFSET_TcoCompOffset_WID            ( 4)
  #define DDRCKECH0_CR_DDRCRCTLCOMPOFFSET_TcoCompOffset_MSK            (0x000001E0)
  #define DDRCKECH0_CR_DDRCRCTLCOMPOFFSET_TcoCompOffset_MIN            (-8)
  #define DDRCKECH0_CR_DDRCRCTLCOMPOFFSET_TcoCompOffset_MAX            (7) // 0x00000007
  #define DDRCKECH0_CR_DDRCRCTLCOMPOFFSET_TcoCompOffset_DEF            (0x00000000)
  #define DDRCKECH0_CR_DDRCRCTLCOMPOFFSET_TcoCompOffset_HSH            (0x84051214)

  #define DDRCKECH0_CR_DDRCRCTLCOMPOFFSET_RcompDrvUpOffset_OFF         ( 9)
  #define DDRCKECH0_CR_DDRCRCTLCOMPOFFSET_RcompDrvUpOffset_WID         ( 4)
  #define DDRCKECH0_CR_DDRCRCTLCOMPOFFSET_RcompDrvUpOffset_MSK         (0x00001E00)
  #define DDRCKECH0_CR_DDRCRCTLCOMPOFFSET_RcompDrvUpOffset_MIN         (-8)
  #define DDRCKECH0_CR_DDRCRCTLCOMPOFFSET_RcompDrvUpOffset_MAX         (7) // 0x00000007
  #define DDRCKECH0_CR_DDRCRCTLCOMPOFFSET_RcompDrvUpOffset_DEF         (0x00000000)
  #define DDRCKECH0_CR_DDRCRCTLCOMPOFFSET_RcompDrvUpOffset_HSH         (0x84091214)

  #define DDRCKECH0_CR_DDRCRCTLCOMPOFFSET_RcompDrvDownOffset_OFF       (13)
  #define DDRCKECH0_CR_DDRCRCTLCOMPOFFSET_RcompDrvDownOffset_WID       ( 4)
  #define DDRCKECH0_CR_DDRCRCTLCOMPOFFSET_RcompDrvDownOffset_MSK       (0x0001E000)
  #define DDRCKECH0_CR_DDRCRCTLCOMPOFFSET_RcompDrvDownOffset_MIN       (-8)
  #define DDRCKECH0_CR_DDRCRCTLCOMPOFFSET_RcompDrvDownOffset_MAX       (7) // 0x00000007
  #define DDRCKECH0_CR_DDRCRCTLCOMPOFFSET_RcompDrvDownOffset_DEF       (0x00000000)
  #define DDRCKECH0_CR_DDRCRCTLCOMPOFFSET_RcompDrvDownOffset_HSH       (0x840D1214)

  #define DDRCKECH0_CR_DDRCRCTLCOMPOFFSET_Spare_OFF                    (17)
  #define DDRCKECH0_CR_DDRCRCTLCOMPOFFSET_Spare_WID                    (15)
  #define DDRCKECH0_CR_DDRCRCTLCOMPOFFSET_Spare_MSK                    (0xFFFE0000)
  #define DDRCKECH0_CR_DDRCRCTLCOMPOFFSET_Spare_MIN                    (0)
  #define DDRCKECH0_CR_DDRCRCTLCOMPOFFSET_Spare_MAX                    (32767) // 0x00007FFF
  #define DDRCKECH0_CR_DDRCRCTLCOMPOFFSET_Spare_DEF                    (0x00000000)
  #define DDRCKECH0_CR_DDRCRCTLCOMPOFFSET_Spare_HSH                    (0x0F111214)

#define DDRCKECH0_CR_DDRCRCTLPICODING_REG                              (0x00001218)

  #define DDRCKECH0_CR_DDRCRCTLPICODING_CtlPiCode0_OFF                 ( 0)
  #define DDRCKECH0_CR_DDRCRCTLPICODING_CtlPiCode0_WID                 ( 7)
  #define DDRCKECH0_CR_DDRCRCTLPICODING_CtlPiCode0_MSK                 (0x0000007F)
  #define DDRCKECH0_CR_DDRCRCTLPICODING_CtlPiCode0_MIN                 (0)
  #define DDRCKECH0_CR_DDRCRCTLPICODING_CtlPiCode0_MAX                 (127) // 0x0000007F
  #define DDRCKECH0_CR_DDRCRCTLPICODING_CtlPiCode0_DEF                 (0x00000000)
  #define DDRCKECH0_CR_DDRCRCTLPICODING_CtlPiCode0_HSH                 (0x07001218)

  #define DDRCKECH0_CR_DDRCRCTLPICODING_CtlPiCode1_OFF                 ( 7)
  #define DDRCKECH0_CR_DDRCRCTLPICODING_CtlPiCode1_WID                 ( 7)
  #define DDRCKECH0_CR_DDRCRCTLPICODING_CtlPiCode1_MSK                 (0x00003F80)
  #define DDRCKECH0_CR_DDRCRCTLPICODING_CtlPiCode1_MIN                 (0)
  #define DDRCKECH0_CR_DDRCRCTLPICODING_CtlPiCode1_MAX                 (127) // 0x0000007F
  #define DDRCKECH0_CR_DDRCRCTLPICODING_CtlPiCode1_DEF                 (0x00000000)
  #define DDRCKECH0_CR_DDRCRCTLPICODING_CtlPiCode1_HSH                 (0x07071218)

  #define DDRCKECH0_CR_DDRCRCTLPICODING_CtlPiCode2_OFF                 (14)
  #define DDRCKECH0_CR_DDRCRCTLPICODING_CtlPiCode2_WID                 ( 7)
  #define DDRCKECH0_CR_DDRCRCTLPICODING_CtlPiCode2_MSK                 (0x001FC000)
  #define DDRCKECH0_CR_DDRCRCTLPICODING_CtlPiCode2_MIN                 (0)
  #define DDRCKECH0_CR_DDRCRCTLPICODING_CtlPiCode2_MAX                 (127) // 0x0000007F
  #define DDRCKECH0_CR_DDRCRCTLPICODING_CtlPiCode2_DEF                 (0x00000000)
  #define DDRCKECH0_CR_DDRCRCTLPICODING_CtlPiCode2_HSH                 (0x070E1218)

  #define DDRCKECH0_CR_DDRCRCTLPICODING_CtlPiCode3_OFF                 (21)
  #define DDRCKECH0_CR_DDRCRCTLPICODING_CtlPiCode3_WID                 ( 7)
  #define DDRCKECH0_CR_DDRCRCTLPICODING_CtlPiCode3_MSK                 (0x0FE00000)
  #define DDRCKECH0_CR_DDRCRCTLPICODING_CtlPiCode3_MIN                 (0)
  #define DDRCKECH0_CR_DDRCRCTLPICODING_CtlPiCode3_MAX                 (127) // 0x0000007F
  #define DDRCKECH0_CR_DDRCRCTLPICODING_CtlPiCode3_DEF                 (0x00000000)
  #define DDRCKECH0_CR_DDRCRCTLPICODING_CtlPiCode3_HSH                 (0x07151218)

  #define DDRCKECH0_CR_DDRCRCTLPICODING_CtlXoverEnable_OFF             (28)
  #define DDRCKECH0_CR_DDRCRCTLPICODING_CtlXoverEnable_WID             ( 1)
  #define DDRCKECH0_CR_DDRCRCTLPICODING_CtlXoverEnable_MSK             (0x10000000)
  #define DDRCKECH0_CR_DDRCRCTLPICODING_CtlXoverEnable_MIN             (0)
  #define DDRCKECH0_CR_DDRCRCTLPICODING_CtlXoverEnable_MAX             (1) // 0x00000001
  #define DDRCKECH0_CR_DDRCRCTLPICODING_CtlXoverEnable_DEF             (0x00000000)
  #define DDRCKECH0_CR_DDRCRCTLPICODING_CtlXoverEnable_HSH             (0x011C1218)

  #define DDRCKECH0_CR_DDRCRCTLPICODING_Spare_OFF                      (29)
  #define DDRCKECH0_CR_DDRCRCTLPICODING_Spare_WID                      ( 3)
  #define DDRCKECH0_CR_DDRCRCTLPICODING_Spare_MSK                      (0xE0000000)
  #define DDRCKECH0_CR_DDRCRCTLPICODING_Spare_MIN                      (0)
  #define DDRCKECH0_CR_DDRCRCTLPICODING_Spare_MAX                      (7) // 0x00000007
  #define DDRCKECH0_CR_DDRCRCTLPICODING_Spare_DEF                      (0x00000000)
  #define DDRCKECH0_CR_DDRCRCTLPICODING_Spare_HSH                      (0x031D1218)

#define DDRCKECH0_CR_DDRCRCTLCONTROLS_REG                              (0x0000121C)

  #define DDRCKECH0_CR_DDRCRCTLCONTROLS_RefPi_OFF                      ( 0)
  #define DDRCKECH0_CR_DDRCRCTLCONTROLS_RefPi_WID                      ( 4)
  #define DDRCKECH0_CR_DDRCRCTLCONTROLS_RefPi_MSK                      (0x0000000F)
  #define DDRCKECH0_CR_DDRCRCTLCONTROLS_RefPi_MIN                      (-8)
  #define DDRCKECH0_CR_DDRCRCTLCONTROLS_RefPi_MAX                      (7) // 0x00000007
  #define DDRCKECH0_CR_DDRCRCTLCONTROLS_RefPi_DEF                      (0x00000000)
  #define DDRCKECH0_CR_DDRCRCTLCONTROLS_RefPi_HSH                      (0x8400121C)

  #define DDRCKECH0_CR_DDRCRCTLCONTROLS_DllMask_OFF                    ( 4)
  #define DDRCKECH0_CR_DDRCRCTLCONTROLS_DllMask_WID                    ( 2)
  #define DDRCKECH0_CR_DDRCRCTLCONTROLS_DllMask_MSK                    (0x00000030)
  #define DDRCKECH0_CR_DDRCRCTLCONTROLS_DllMask_MIN                    (0)
  #define DDRCKECH0_CR_DDRCRCTLCONTROLS_DllMask_MAX                    (3) // 0x00000003
  #define DDRCKECH0_CR_DDRCRCTLCONTROLS_DllMask_DEF                    (0x00000000)
  #define DDRCKECH0_CR_DDRCRCTLCONTROLS_DllMask_HSH                    (0x0204121C)

  #define DDRCKECH0_CR_DDRCRCTLCONTROLS_ClkGateDisable_OFF             ( 6)
  #define DDRCKECH0_CR_DDRCRCTLCONTROLS_ClkGateDisable_WID             ( 1)
  #define DDRCKECH0_CR_DDRCRCTLCONTROLS_ClkGateDisable_MSK             (0x00000040)
  #define DDRCKECH0_CR_DDRCRCTLCONTROLS_ClkGateDisable_MIN             (0)
  #define DDRCKECH0_CR_DDRCRCTLCONTROLS_ClkGateDisable_MAX             (1) // 0x00000001
  #define DDRCKECH0_CR_DDRCRCTLCONTROLS_ClkGateDisable_DEF             (0x00000000)
  #define DDRCKECH0_CR_DDRCRCTLCONTROLS_ClkGateDisable_HSH             (0x0106121C)

  #define DDRCKECH0_CR_DDRCRCTLCONTROLS_TxOn_OFF                       ( 7)
  #define DDRCKECH0_CR_DDRCRCTLCONTROLS_TxOn_WID                       ( 1)
  #define DDRCKECH0_CR_DDRCRCTLCONTROLS_TxOn_MSK                       (0x00000080)
  #define DDRCKECH0_CR_DDRCRCTLCONTROLS_TxOn_MIN                       (0)
  #define DDRCKECH0_CR_DDRCRCTLCONTROLS_TxOn_MAX                       (1) // 0x00000001
  #define DDRCKECH0_CR_DDRCRCTLCONTROLS_TxOn_DEF                       (0x00000000)
  #define DDRCKECH0_CR_DDRCRCTLCONTROLS_TxOn_HSH                       (0x0107121C)

  #define DDRCKECH0_CR_DDRCRCTLCONTROLS_IntClkOn_OFF                   ( 8)
  #define DDRCKECH0_CR_DDRCRCTLCONTROLS_IntClkOn_WID                   ( 1)
  #define DDRCKECH0_CR_DDRCRCTLCONTROLS_IntClkOn_MSK                   (0x00000100)
  #define DDRCKECH0_CR_DDRCRCTLCONTROLS_IntClkOn_MIN                   (0)
  #define DDRCKECH0_CR_DDRCRCTLCONTROLS_IntClkOn_MAX                   (1) // 0x00000001
  #define DDRCKECH0_CR_DDRCRCTLCONTROLS_IntClkOn_DEF                   (0x00000000)
  #define DDRCKECH0_CR_DDRCRCTLCONTROLS_IntClkOn_HSH                   (0x0108121C)

  #define DDRCKECH0_CR_DDRCRCTLCONTROLS_RepClkOn_OFF                   ( 9)
  #define DDRCKECH0_CR_DDRCRCTLCONTROLS_RepClkOn_WID                   ( 1)
  #define DDRCKECH0_CR_DDRCRCTLCONTROLS_RepClkOn_MSK                   (0x00000200)
  #define DDRCKECH0_CR_DDRCRCTLCONTROLS_RepClkOn_MIN                   (0)
  #define DDRCKECH0_CR_DDRCRCTLCONTROLS_RepClkOn_MAX                   (1) // 0x00000001
  #define DDRCKECH0_CR_DDRCRCTLCONTROLS_RepClkOn_DEF                   (0x00000000)
  #define DDRCKECH0_CR_DDRCRCTLCONTROLS_RepClkOn_HSH                   (0x0109121C)

  #define DDRCKECH0_CR_DDRCRCTLCONTROLS_IolbOrMisr_OFF                 (10)
  #define DDRCKECH0_CR_DDRCRCTLCONTROLS_IolbOrMisr_WID                 ( 1)
  #define DDRCKECH0_CR_DDRCRCTLCONTROLS_IolbOrMisr_MSK                 (0x00000400)
  #define DDRCKECH0_CR_DDRCRCTLCONTROLS_IolbOrMisr_MIN                 (0)
  #define DDRCKECH0_CR_DDRCRCTLCONTROLS_IolbOrMisr_MAX                 (1) // 0x00000001
  #define DDRCKECH0_CR_DDRCRCTLCONTROLS_IolbOrMisr_DEF                 (0x00000000)
  #define DDRCKECH0_CR_DDRCRCTLCONTROLS_IolbOrMisr_HSH                 (0x010A121C)

  #define DDRCKECH0_CR_DDRCRCTLCONTROLS_IOLBHold_OFF                   (11)
  #define DDRCKECH0_CR_DDRCRCTLCONTROLS_IOLBHold_WID                   ( 1)
  #define DDRCKECH0_CR_DDRCRCTLCONTROLS_IOLBHold_MSK                   (0x00000800)
  #define DDRCKECH0_CR_DDRCRCTLCONTROLS_IOLBHold_MIN                   (0)
  #define DDRCKECH0_CR_DDRCRCTLCONTROLS_IOLBHold_MAX                   (1) // 0x00000001
  #define DDRCKECH0_CR_DDRCRCTLCONTROLS_IOLBHold_DEF                   (0x00000000)
  #define DDRCKECH0_CR_DDRCRCTLCONTROLS_IOLBHold_HSH                   (0x010B121C)

  #define DDRCKECH0_CR_DDRCRCTLCONTROLS_OdtMode_OFF                    (12)
  #define DDRCKECH0_CR_DDRCRCTLCONTROLS_OdtMode_WID                    ( 1)
  #define DDRCKECH0_CR_DDRCRCTLCONTROLS_OdtMode_MSK                    (0x00001000)
  #define DDRCKECH0_CR_DDRCRCTLCONTROLS_OdtMode_MIN                    (0)
  #define DDRCKECH0_CR_DDRCRCTLCONTROLS_OdtMode_MAX                    (1) // 0x00000001
  #define DDRCKECH0_CR_DDRCRCTLCONTROLS_OdtMode_DEF                    (0x00000000)
  #define DDRCKECH0_CR_DDRCRCTLCONTROLS_OdtMode_HSH                    (0x010C121C)

  #define DDRCKECH0_CR_DDRCRCTLCONTROLS_CmdTxEq_OFF                    (13)
  #define DDRCKECH0_CR_DDRCRCTLCONTROLS_CmdTxEq_WID                    ( 2)
  #define DDRCKECH0_CR_DDRCRCTLCONTROLS_CmdTxEq_MSK                    (0x00006000)
  #define DDRCKECH0_CR_DDRCRCTLCONTROLS_CmdTxEq_MIN                    (0)
  #define DDRCKECH0_CR_DDRCRCTLCONTROLS_CmdTxEq_MAX                    (3) // 0x00000003
  #define DDRCKECH0_CR_DDRCRCTLCONTROLS_CmdTxEq_DEF                    (0x00000000)
  #define DDRCKECH0_CR_DDRCRCTLCONTROLS_CmdTxEq_HSH                    (0x020D121C)

  #define DDRCKECH0_CR_DDRCRCTLCONTROLS_EarlyWeakDrive_OFF             (15)
  #define DDRCKECH0_CR_DDRCRCTLCONTROLS_EarlyWeakDrive_WID             ( 2)
  #define DDRCKECH0_CR_DDRCRCTLCONTROLS_EarlyWeakDrive_MSK             (0x00018000)
  #define DDRCKECH0_CR_DDRCRCTLCONTROLS_EarlyWeakDrive_MIN             (0)
  #define DDRCKECH0_CR_DDRCRCTLCONTROLS_EarlyWeakDrive_MAX             (3) // 0x00000003
  #define DDRCKECH0_CR_DDRCRCTLCONTROLS_EarlyWeakDrive_DEF             (0x00000000)
  #define DDRCKECH0_CR_DDRCRCTLCONTROLS_EarlyWeakDrive_HSH             (0x020F121C)

  #define DDRCKECH0_CR_DDRCRCTLCONTROLS_CtlTxEq_OFF                    (17)
  #define DDRCKECH0_CR_DDRCRCTLCONTROLS_CtlTxEq_WID                    ( 2)
  #define DDRCKECH0_CR_DDRCRCTLCONTROLS_CtlTxEq_MSK                    (0x00060000)
  #define DDRCKECH0_CR_DDRCRCTLCONTROLS_CtlTxEq_MIN                    (0)
  #define DDRCKECH0_CR_DDRCRCTLCONTROLS_CtlTxEq_MAX                    (3) // 0x00000003
  #define DDRCKECH0_CR_DDRCRCTLCONTROLS_CtlTxEq_DEF                    (0x00000000)
  #define DDRCKECH0_CR_DDRCRCTLCONTROLS_CtlTxEq_HSH                    (0x0211121C)

  #define DDRCKECH0_CR_DDRCRCTLCONTROLS_CtlSRDrv_OFF                   (19)
  #define DDRCKECH0_CR_DDRCRCTLCONTROLS_CtlSRDrv_WID                   ( 2)
  #define DDRCKECH0_CR_DDRCRCTLCONTROLS_CtlSRDrv_MSK                   (0x00180000)
  #define DDRCKECH0_CR_DDRCRCTLCONTROLS_CtlSRDrv_MIN                   (0)
  #define DDRCKECH0_CR_DDRCRCTLCONTROLS_CtlSRDrv_MAX                   (3) // 0x00000003
  #define DDRCKECH0_CR_DDRCRCTLCONTROLS_CtlSRDrv_DEF                   (0x00000000)
  #define DDRCKECH0_CR_DDRCRCTLCONTROLS_CtlSRDrv_HSH                   (0x0213121C)

  #define DDRCKECH0_CR_DDRCRCTLCONTROLS_RxVref_OFF                     (21)
  #define DDRCKECH0_CR_DDRCRCTLCONTROLS_RxVref_WID                     ( 6)
  #define DDRCKECH0_CR_DDRCRCTLCONTROLS_RxVref_MSK                     (0x07E00000)
  #define DDRCKECH0_CR_DDRCRCTLCONTROLS_RxVref_MIN                     (-32)
  #define DDRCKECH0_CR_DDRCRCTLCONTROLS_RxVref_MAX                     (31) // 0x0000001F
  #define DDRCKECH0_CR_DDRCRCTLCONTROLS_RxVref_DEF                     (0x00000000)
  #define DDRCKECH0_CR_DDRCRCTLCONTROLS_RxVref_HSH                     (0x8615121C)

  #define DDRCKECH0_CR_DDRCRCTLCONTROLS_VccddqHi_OFF                   (27)
  #define DDRCKECH0_CR_DDRCRCTLCONTROLS_VccddqHi_WID                   ( 1)
  #define DDRCKECH0_CR_DDRCRCTLCONTROLS_VccddqHi_MSK                   (0x08000000)
  #define DDRCKECH0_CR_DDRCRCTLCONTROLS_VccddqHi_MIN                   (0)
  #define DDRCKECH0_CR_DDRCRCTLCONTROLS_VccddqHi_MAX                   (1) // 0x00000001
  #define DDRCKECH0_CR_DDRCRCTLCONTROLS_VccddqHi_DEF                   (0x00000000)
  #define DDRCKECH0_CR_DDRCRCTLCONTROLS_VccddqHi_HSH                   (0x011B121C)

  #define DDRCKECH0_CR_DDRCRCTLCONTROLS_DllWeakLock_OFF                (28)
  #define DDRCKECH0_CR_DDRCRCTLCONTROLS_DllWeakLock_WID                ( 1)
  #define DDRCKECH0_CR_DDRCRCTLCONTROLS_DllWeakLock_MSK                (0x10000000)
  #define DDRCKECH0_CR_DDRCRCTLCONTROLS_DllWeakLock_MIN                (0)
  #define DDRCKECH0_CR_DDRCRCTLCONTROLS_DllWeakLock_MAX                (1) // 0x00000001
  #define DDRCKECH0_CR_DDRCRCTLCONTROLS_DllWeakLock_DEF                (0x00000000)
  #define DDRCKECH0_CR_DDRCRCTLCONTROLS_DllWeakLock_HSH                (0x011C121C)

  #define DDRCKECH0_CR_DDRCRCTLCONTROLS_LPDDR_Mode_OFF                 (29)
  #define DDRCKECH0_CR_DDRCRCTLCONTROLS_LPDDR_Mode_WID                 ( 1)
  #define DDRCKECH0_CR_DDRCRCTLCONTROLS_LPDDR_Mode_MSK                 (0x20000000)
  #define DDRCKECH0_CR_DDRCRCTLCONTROLS_LPDDR_Mode_MIN                 (0)
  #define DDRCKECH0_CR_DDRCRCTLCONTROLS_LPDDR_Mode_MAX                 (1) // 0x00000001
  #define DDRCKECH0_CR_DDRCRCTLCONTROLS_LPDDR_Mode_DEF                 (0x00000000)
  #define DDRCKECH0_CR_DDRCRCTLCONTROLS_LPDDR_Mode_HSH                 (0x011D121C)

  #define DDRCKECH0_CR_DDRCRCTLCONTROLS_LaDrvEnOvrd_OFF                (30)
  #define DDRCKECH0_CR_DDRCRCTLCONTROLS_LaDrvEnOvrd_WID                ( 1)
  #define DDRCKECH0_CR_DDRCRCTLCONTROLS_LaDrvEnOvrd_MSK                (0x40000000)
  #define DDRCKECH0_CR_DDRCRCTLCONTROLS_LaDrvEnOvrd_MIN                (0)
  #define DDRCKECH0_CR_DDRCRCTLCONTROLS_LaDrvEnOvrd_MAX                (1) // 0x00000001
  #define DDRCKECH0_CR_DDRCRCTLCONTROLS_LaDrvEnOvrd_DEF                (0x00000000)
  #define DDRCKECH0_CR_DDRCRCTLCONTROLS_LaDrvEnOvrd_HSH                (0x011E121C)

  #define DDRCKECH0_CR_DDRCRCTLCONTROLS_LPDdrCAA_Dis_OFF               (31)
  #define DDRCKECH0_CR_DDRCRCTLCONTROLS_LPDdrCAA_Dis_WID               ( 1)
  #define DDRCKECH0_CR_DDRCRCTLCONTROLS_LPDdrCAA_Dis_MSK               (0x80000000)
  #define DDRCKECH0_CR_DDRCRCTLCONTROLS_LPDdrCAA_Dis_MIN               (0)
  #define DDRCKECH0_CR_DDRCRCTLCONTROLS_LPDdrCAA_Dis_MAX               (1) // 0x00000001
  #define DDRCKECH0_CR_DDRCRCTLCONTROLS_LPDdrCAA_Dis_DEF               (0x00000000)
  #define DDRCKECH0_CR_DDRCRCTLCONTROLS_LPDdrCAA_Dis_HSH               (0x011F121C)

#define DDRCKECH0_CR_DDRCRCTLRANKSUSED_REG                             (0x00001220)

  #define DDRCKECH0_CR_DDRCRCTLRANKSUSED_RankEn_OFF                    ( 0)
  #define DDRCKECH0_CR_DDRCRCTLRANKSUSED_RankEn_WID                    ( 4)
  #define DDRCKECH0_CR_DDRCRCTLRANKSUSED_RankEn_MSK                    (0x0000000F)
  #define DDRCKECH0_CR_DDRCRCTLRANKSUSED_RankEn_MIN                    (0)
  #define DDRCKECH0_CR_DDRCRCTLRANKSUSED_RankEn_MAX                    (15) // 0x0000000F
  #define DDRCKECH0_CR_DDRCRCTLRANKSUSED_RankEn_DEF                    (0x0000000F)
  #define DDRCKECH0_CR_DDRCRCTLRANKSUSED_RankEn_HSH                    (0x04001220)

  #define DDRCKECH0_CR_DDRCRCTLRANKSUSED_OdtDisable_OFF                ( 4)
  #define DDRCKECH0_CR_DDRCRCTLRANKSUSED_OdtDisable_WID                ( 2)
  #define DDRCKECH0_CR_DDRCRCTLRANKSUSED_OdtDisable_MSK                (0x00000030)
  #define DDRCKECH0_CR_DDRCRCTLRANKSUSED_OdtDisable_MIN                (0)
  #define DDRCKECH0_CR_DDRCRCTLRANKSUSED_OdtDisable_MAX                (3) // 0x00000003
  #define DDRCKECH0_CR_DDRCRCTLRANKSUSED_OdtDisable_DEF                (0x00000000)
  #define DDRCKECH0_CR_DDRCRCTLRANKSUSED_OdtDisable_HSH                (0x02041220)

  #define DDRCKECH0_CR_DDRCRCTLRANKSUSED_DdrCkeCmdSlwDlyByp_OFF        ( 6)
  #define DDRCKECH0_CR_DDRCRCTLRANKSUSED_DdrCkeCmdSlwDlyByp_WID        ( 1)
  #define DDRCKECH0_CR_DDRCRCTLRANKSUSED_DdrCkeCmdSlwDlyByp_MSK        (0x00000040)
  #define DDRCKECH0_CR_DDRCRCTLRANKSUSED_DdrCkeCmdSlwDlyByp_MIN        (0)
  #define DDRCKECH0_CR_DDRCRCTLRANKSUSED_DdrCkeCmdSlwDlyByp_MAX        (1) // 0x00000001
  #define DDRCKECH0_CR_DDRCRCTLRANKSUSED_DdrCkeCmdSlwDlyByp_DEF        (0x00000000)
  #define DDRCKECH0_CR_DDRCRCTLRANKSUSED_DdrCkeCmdSlwDlyByp_HSH        (0x01061220)

  #define DDRCKECH0_CR_DDRCRCTLRANKSUSED_DdrCtlCkeSlwDlyByp_OFF        ( 7)
  #define DDRCKECH0_CR_DDRCRCTLRANKSUSED_DdrCtlCkeSlwDlyByp_WID        ( 1)
  #define DDRCKECH0_CR_DDRCRCTLRANKSUSED_DdrCtlCkeSlwDlyByp_MSK        (0x00000080)
  #define DDRCKECH0_CR_DDRCRCTLRANKSUSED_DdrCtlCkeSlwDlyByp_MIN        (0)
  #define DDRCKECH0_CR_DDRCRCTLRANKSUSED_DdrCtlCkeSlwDlyByp_MAX        (1) // 0x00000001
  #define DDRCKECH0_CR_DDRCRCTLRANKSUSED_DdrCtlCkeSlwDlyByp_DEF        (0x00000000)
  #define DDRCKECH0_CR_DDRCRCTLRANKSUSED_DdrCtlCkeSlwDlyByp_HSH        (0x01071220)

  #define DDRCKECH0_CR_DDRCRCTLRANKSUSED_CsPiClkGateEn_OFF             ( 8)
  #define DDRCKECH0_CR_DDRCRCTLRANKSUSED_CsPiClkGateEn_WID             ( 1)
  #define DDRCKECH0_CR_DDRCRCTLRANKSUSED_CsPiClkGateEn_MSK             (0x00000100)
  #define DDRCKECH0_CR_DDRCRCTLRANKSUSED_CsPiClkGateEn_MIN             (0)
  #define DDRCKECH0_CR_DDRCRCTLRANKSUSED_CsPiClkGateEn_MAX             (1) // 0x00000001
  #define DDRCKECH0_CR_DDRCRCTLRANKSUSED_CsPiClkGateEn_DEF             (0x00000000)
  #define DDRCKECH0_CR_DDRCRCTLRANKSUSED_CsPiClkGateEn_HSH             (0x01081220)

  #define DDRCKECH0_CR_DDRCRCTLRANKSUSED_CsClkGateDis_OFF              ( 9)
  #define DDRCKECH0_CR_DDRCRCTLRANKSUSED_CsClkGateDis_WID              ( 1)
  #define DDRCKECH0_CR_DDRCRCTLRANKSUSED_CsClkGateDis_MSK              (0x00000200)
  #define DDRCKECH0_CR_DDRCRCTLRANKSUSED_CsClkGateDis_MIN              (0)
  #define DDRCKECH0_CR_DDRCRCTLRANKSUSED_CsClkGateDis_MAX              (1) // 0x00000001
  #define DDRCKECH0_CR_DDRCRCTLRANKSUSED_CsClkGateDis_DEF              (0x00000000)
  #define DDRCKECH0_CR_DDRCRCTLRANKSUSED_CsClkGateDis_HSH              (0x01091220)

  #define DDRCKECH0_CR_DDRCRCTLRANKSUSED_Spare_OFF                     (10)
  #define DDRCKECH0_CR_DDRCRCTLRANKSUSED_Spare_WID                     (22)
  #define DDRCKECH0_CR_DDRCRCTLRANKSUSED_Spare_MSK                     (0xFFFFFC00)
  #define DDRCKECH0_CR_DDRCRCTLRANKSUSED_Spare_MIN                     (0)
  #define DDRCKECH0_CR_DDRCRCTLRANKSUSED_Spare_MAX                     (4194303) // 0x003FFFFF
  #define DDRCKECH0_CR_DDRCRCTLRANKSUSED_Spare_DEF                     (0x00000000)
  #define DDRCKECH0_CR_DDRCRCTLRANKSUSED_Spare_HSH                     (0x160A1220)

#define DDRCKECH0_CR_DLLPITESTANDADC_REG                               (0x00001224)

  #define DDRCKECH0_CR_DLLPITESTANDADC_RunTest_OFF                     ( 0)
  #define DDRCKECH0_CR_DLLPITESTANDADC_RunTest_WID                     ( 1)
  #define DDRCKECH0_CR_DLLPITESTANDADC_RunTest_MSK                     (0x00000001)
  #define DDRCKECH0_CR_DLLPITESTANDADC_RunTest_MIN                     (0)
  #define DDRCKECH0_CR_DLLPITESTANDADC_RunTest_MAX                     (1) // 0x00000001
  #define DDRCKECH0_CR_DLLPITESTANDADC_RunTest_DEF                     (0x00000000)
  #define DDRCKECH0_CR_DLLPITESTANDADC_RunTest_HSH                     (0x01001224)

  #define DDRCKECH0_CR_DLLPITESTANDADC_Load_OFF                        ( 1)
  #define DDRCKECH0_CR_DLLPITESTANDADC_Load_WID                        ( 1)
  #define DDRCKECH0_CR_DLLPITESTANDADC_Load_MSK                        (0x00000002)
  #define DDRCKECH0_CR_DLLPITESTANDADC_Load_MIN                        (0)
  #define DDRCKECH0_CR_DLLPITESTANDADC_Load_MAX                        (1) // 0x00000001
  #define DDRCKECH0_CR_DLLPITESTANDADC_Load_DEF                        (0x00000000)
  #define DDRCKECH0_CR_DLLPITESTANDADC_Load_HSH                        (0x01011224)

  #define DDRCKECH0_CR_DLLPITESTANDADC_ModeHVM_OFF                     ( 2)
  #define DDRCKECH0_CR_DLLPITESTANDADC_ModeHVM_WID                     ( 1)
  #define DDRCKECH0_CR_DLLPITESTANDADC_ModeHVM_MSK                     (0x00000004)
  #define DDRCKECH0_CR_DLLPITESTANDADC_ModeHVM_MIN                     (0)
  #define DDRCKECH0_CR_DLLPITESTANDADC_ModeHVM_MAX                     (1) // 0x00000001
  #define DDRCKECH0_CR_DLLPITESTANDADC_ModeHVM_DEF                     (0x00000000)
  #define DDRCKECH0_CR_DLLPITESTANDADC_ModeHVM_HSH                     (0x01021224)

  #define DDRCKECH0_CR_DLLPITESTANDADC_ModeDV_OFF                      ( 3)
  #define DDRCKECH0_CR_DLLPITESTANDADC_ModeDV_WID                      ( 1)
  #define DDRCKECH0_CR_DLLPITESTANDADC_ModeDV_MSK                      (0x00000008)
  #define DDRCKECH0_CR_DLLPITESTANDADC_ModeDV_MIN                      (0)
  #define DDRCKECH0_CR_DLLPITESTANDADC_ModeDV_MAX                      (1) // 0x00000001
  #define DDRCKECH0_CR_DLLPITESTANDADC_ModeDV_DEF                      (0x00000000)
  #define DDRCKECH0_CR_DLLPITESTANDADC_ModeDV_HSH                      (0x01031224)

  #define DDRCKECH0_CR_DLLPITESTANDADC_CalCfdl_OFF                     ( 4)
  #define DDRCKECH0_CR_DLLPITESTANDADC_CalCfdl_WID                     ( 1)
  #define DDRCKECH0_CR_DLLPITESTANDADC_CalCfdl_MSK                     (0x00000010)
  #define DDRCKECH0_CR_DLLPITESTANDADC_CalCfdl_MIN                     (0)
  #define DDRCKECH0_CR_DLLPITESTANDADC_CalCfdl_MAX                     (1) // 0x00000001
  #define DDRCKECH0_CR_DLLPITESTANDADC_CalCfdl_DEF                     (0x00000000)
  #define DDRCKECH0_CR_DLLPITESTANDADC_CalCfdl_HSH                     (0x01041224)

  #define DDRCKECH0_CR_DLLPITESTANDADC_LoadCount_OFF                   ( 5)
  #define DDRCKECH0_CR_DLLPITESTANDADC_LoadCount_WID                   (10)
  #define DDRCKECH0_CR_DLLPITESTANDADC_LoadCount_MSK                   (0x00007FE0)
  #define DDRCKECH0_CR_DLLPITESTANDADC_LoadCount_MIN                   (0)
  #define DDRCKECH0_CR_DLLPITESTANDADC_LoadCount_MAX                   (1023) // 0x000003FF
  #define DDRCKECH0_CR_DLLPITESTANDADC_LoadCount_DEF                   (0x00000000)
  #define DDRCKECH0_CR_DLLPITESTANDADC_LoadCount_HSH                   (0x0A051224)

  #define DDRCKECH0_CR_DLLPITESTANDADC_CountStatus_OFF                 (15)
  #define DDRCKECH0_CR_DLLPITESTANDADC_CountStatus_WID                 (10)
  #define DDRCKECH0_CR_DLLPITESTANDADC_CountStatus_MSK                 (0x01FF8000)
  #define DDRCKECH0_CR_DLLPITESTANDADC_CountStatus_MIN                 (0)
  #define DDRCKECH0_CR_DLLPITESTANDADC_CountStatus_MAX                 (1023) // 0x000003FF
  #define DDRCKECH0_CR_DLLPITESTANDADC_CountStatus_DEF                 (0x00000000)
  #define DDRCKECH0_CR_DLLPITESTANDADC_CountStatus_HSH                 (0x0A0F1224)

  #define DDRCKECH0_CR_DLLPITESTANDADC_PhaseDrvPwrSavOn_OFF            (25)
  #define DDRCKECH0_CR_DLLPITESTANDADC_PhaseDrvPwrSavOn_WID            ( 1)
  #define DDRCKECH0_CR_DLLPITESTANDADC_PhaseDrvPwrSavOn_MSK            (0x02000000)
  #define DDRCKECH0_CR_DLLPITESTANDADC_PhaseDrvPwrSavOn_MIN            (0)
  #define DDRCKECH0_CR_DLLPITESTANDADC_PhaseDrvPwrSavOn_MAX            (1) // 0x00000001
  #define DDRCKECH0_CR_DLLPITESTANDADC_PhaseDrvPwrSavOn_DEF            (0x00000000)
  #define DDRCKECH0_CR_DLLPITESTANDADC_PhaseDrvPwrSavOn_HSH            (0x01191224)

  #define DDRCKECH0_CR_DLLPITESTANDADC_Spare_OFF                       (26)
  #define DDRCKECH0_CR_DLLPITESTANDADC_Spare_WID                       ( 6)
  #define DDRCKECH0_CR_DLLPITESTANDADC_Spare_MSK                       (0xFC000000)
  #define DDRCKECH0_CR_DLLPITESTANDADC_Spare_MIN                       (0)
  #define DDRCKECH0_CR_DLLPITESTANDADC_Spare_MAX                       (63) // 0x0000003F
  #define DDRCKECH0_CR_DLLPITESTANDADC_Spare_DEF                       (0x00000000)
  #define DDRCKECH0_CR_DLLPITESTANDADC_Spare_HSH                       (0x061A1224)

#define DDRCKECH0_CR_DDRCMDMISR_REG                                    (0x00001228)

  #define DDRCKECH0_CR_DDRCMDMISR_shift_16_OFF                         ( 0)
  #define DDRCKECH0_CR_DDRCMDMISR_shift_16_WID                         ( 1)
  #define DDRCKECH0_CR_DDRCMDMISR_shift_16_MSK                         (0x00000001)
  #define DDRCKECH0_CR_DDRCMDMISR_shift_16_MIN                         (0)
  #define DDRCKECH0_CR_DDRCMDMISR_shift_16_MAX                         (1) // 0x00000001
  #define DDRCKECH0_CR_DDRCMDMISR_shift_16_DEF                         (0x00000000)
  #define DDRCKECH0_CR_DDRCMDMISR_shift_16_HSH                         (0x01001228)

  #define DDRCKECH0_CR_DDRCMDMISR_clken_pulse_mode_OFF                 ( 1)
  #define DDRCKECH0_CR_DDRCMDMISR_clken_pulse_mode_WID                 ( 1)
  #define DDRCKECH0_CR_DDRCMDMISR_clken_pulse_mode_MSK                 (0x00000002)
  #define DDRCKECH0_CR_DDRCMDMISR_clken_pulse_mode_MIN                 (0)
  #define DDRCKECH0_CR_DDRCMDMISR_clken_pulse_mode_MAX                 (1) // 0x00000001
  #define DDRCKECH0_CR_DDRCMDMISR_clken_pulse_mode_DEF                 (0x00000000)
  #define DDRCKECH0_CR_DDRCMDMISR_clken_pulse_mode_HSH                 (0x01011228)

  #define DDRCKECH0_CR_DDRCMDMISR_reg_clken_mode_OFF                   ( 2)
  #define DDRCKECH0_CR_DDRCMDMISR_reg_clken_mode_WID                   ( 1)
  #define DDRCKECH0_CR_DDRCMDMISR_reg_clken_mode_MSK                   (0x00000004)
  #define DDRCKECH0_CR_DDRCMDMISR_reg_clken_mode_MIN                   (0)
  #define DDRCKECH0_CR_DDRCMDMISR_reg_clken_mode_MAX                   (1) // 0x00000001
  #define DDRCKECH0_CR_DDRCMDMISR_reg_clken_mode_DEF                   (0x00000000)
  #define DDRCKECH0_CR_DDRCMDMISR_reg_clken_mode_HSH                   (0x01021228)

  #define DDRCKECH0_CR_DDRCMDMISR_reg_clken_OFF                        ( 3)
  #define DDRCKECH0_CR_DDRCMDMISR_reg_clken_WID                        ( 1)
  #define DDRCKECH0_CR_DDRCMDMISR_reg_clken_MSK                        (0x00000008)
  #define DDRCKECH0_CR_DDRCMDMISR_reg_clken_MIN                        (0)
  #define DDRCKECH0_CR_DDRCMDMISR_reg_clken_MAX                        (1) // 0x00000001
  #define DDRCKECH0_CR_DDRCMDMISR_reg_clken_DEF                        (0x00000000)
  #define DDRCKECH0_CR_DDRCMDMISR_reg_clken_HSH                        (0x01031228)

  #define DDRCKECH0_CR_DDRCMDMISR_feedback_en_OFF                      ( 4)
  #define DDRCKECH0_CR_DDRCMDMISR_feedback_en_WID                      ( 1)
  #define DDRCKECH0_CR_DDRCMDMISR_feedback_en_MSK                      (0x00000010)
  #define DDRCKECH0_CR_DDRCMDMISR_feedback_en_MIN                      (0)
  #define DDRCKECH0_CR_DDRCMDMISR_feedback_en_MAX                      (1) // 0x00000001
  #define DDRCKECH0_CR_DDRCMDMISR_feedback_en_DEF                      (0x00000000)
  #define DDRCKECH0_CR_DDRCMDMISR_feedback_en_HSH                      (0x01041228)

  #define DDRCKECH0_CR_DDRCMDMISR_event_mode_OFF                       ( 5)
  #define DDRCKECH0_CR_DDRCMDMISR_event_mode_WID                       ( 1)
  #define DDRCKECH0_CR_DDRCMDMISR_event_mode_MSK                       (0x00000020)
  #define DDRCKECH0_CR_DDRCMDMISR_event_mode_MIN                       (0)
  #define DDRCKECH0_CR_DDRCMDMISR_event_mode_MAX                       (1) // 0x00000001
  #define DDRCKECH0_CR_DDRCMDMISR_event_mode_DEF                       (0x00000000)
  #define DDRCKECH0_CR_DDRCMDMISR_event_mode_HSH                       (0x01051228)

  #define DDRCKECH0_CR_DDRCMDMISR_lfsr_reset_OFF                       ( 6)
  #define DDRCKECH0_CR_DDRCMDMISR_lfsr_reset_WID                       ( 1)
  #define DDRCKECH0_CR_DDRCMDMISR_lfsr_reset_MSK                       (0x00000040)
  #define DDRCKECH0_CR_DDRCMDMISR_lfsr_reset_MIN                       (0)
  #define DDRCKECH0_CR_DDRCMDMISR_lfsr_reset_MAX                       (1) // 0x00000001
  #define DDRCKECH0_CR_DDRCMDMISR_lfsr_reset_DEF                       (0x00000000)
  #define DDRCKECH0_CR_DDRCMDMISR_lfsr_reset_HSH                       (0x01061228)

  #define DDRCKECH0_CR_DDRCMDMISR_sdo_en_OFF                           ( 7)
  #define DDRCKECH0_CR_DDRCMDMISR_sdo_en_WID                           ( 1)
  #define DDRCKECH0_CR_DDRCMDMISR_sdo_en_MSK                           (0x00000080)
  #define DDRCKECH0_CR_DDRCMDMISR_sdo_en_MIN                           (0)
  #define DDRCKECH0_CR_DDRCMDMISR_sdo_en_MAX                           (1) // 0x00000001
  #define DDRCKECH0_CR_DDRCMDMISR_sdo_en_DEF                           (0x00000000)
  #define DDRCKECH0_CR_DDRCMDMISR_sdo_en_HSH                           (0x01071228)

  #define DDRCKECH0_CR_DDRCMDMISR_cr_rd_data_OFF                       (16)
  #define DDRCKECH0_CR_DDRCMDMISR_cr_rd_data_WID                       (16)
  #define DDRCKECH0_CR_DDRCMDMISR_cr_rd_data_MSK                       (0xFFFF0000)
  #define DDRCKECH0_CR_DDRCMDMISR_cr_rd_data_MIN                       (0)
  #define DDRCKECH0_CR_DDRCMDMISR_cr_rd_data_MAX                       (65535) // 0x0000FFFF
  #define DDRCKECH0_CR_DDRCMDMISR_cr_rd_data_DEF                       (0x00000000)
  #define DDRCKECH0_CR_DDRCMDMISR_cr_rd_data_HSH                       (0x10101228)

#define DDRCKECH1_CR_DDRCRCMDCOMP_REG                                  (0x00001300)

  #define DDRCKECH1_CR_DDRCRCMDCOMP_Scomp_OFF                          ( 0)
  #define DDRCKECH1_CR_DDRCRCMDCOMP_Scomp_WID                          ( 6)
  #define DDRCKECH1_CR_DDRCRCMDCOMP_Scomp_MSK                          (0x0000003F)
  #define DDRCKECH1_CR_DDRCRCMDCOMP_Scomp_MIN                          (0)
  #define DDRCKECH1_CR_DDRCRCMDCOMP_Scomp_MAX                          (63) // 0x0000003F
  #define DDRCKECH1_CR_DDRCRCMDCOMP_Scomp_DEF                          (0x00000000)
  #define DDRCKECH1_CR_DDRCRCMDCOMP_Scomp_HSH                          (0x06001300)

  #define DDRCKECH1_CR_DDRCRCMDCOMP_TcoComp_OFF                        ( 6)
  #define DDRCKECH1_CR_DDRCRCMDCOMP_TcoComp_WID                        ( 6)
  #define DDRCKECH1_CR_DDRCRCMDCOMP_TcoComp_MSK                        (0x00000FC0)
  #define DDRCKECH1_CR_DDRCRCMDCOMP_TcoComp_MIN                        (0)
  #define DDRCKECH1_CR_DDRCRCMDCOMP_TcoComp_MAX                        (63) // 0x0000003F
  #define DDRCKECH1_CR_DDRCRCMDCOMP_TcoComp_DEF                        (0x00000000)
  #define DDRCKECH1_CR_DDRCRCMDCOMP_TcoComp_HSH                        (0x06061300)

  #define DDRCKECH1_CR_DDRCRCMDCOMP_RcompDrvUp_OFF                     (12)
  #define DDRCKECH1_CR_DDRCRCMDCOMP_RcompDrvUp_WID                     ( 6)
  #define DDRCKECH1_CR_DDRCRCMDCOMP_RcompDrvUp_MSK                     (0x0003F000)
  #define DDRCKECH1_CR_DDRCRCMDCOMP_RcompDrvUp_MIN                     (0)
  #define DDRCKECH1_CR_DDRCRCMDCOMP_RcompDrvUp_MAX                     (63) // 0x0000003F
  #define DDRCKECH1_CR_DDRCRCMDCOMP_RcompDrvUp_DEF                     (0x00000000)
  #define DDRCKECH1_CR_DDRCRCMDCOMP_RcompDrvUp_HSH                     (0x060C1300)

  #define DDRCKECH1_CR_DDRCRCMDCOMP_RcompDrvDown_OFF                   (18)
  #define DDRCKECH1_CR_DDRCRCMDCOMP_RcompDrvDown_WID                   ( 6)
  #define DDRCKECH1_CR_DDRCRCMDCOMP_RcompDrvDown_MSK                   (0x00FC0000)
  #define DDRCKECH1_CR_DDRCRCMDCOMP_RcompDrvDown_MIN                   (0)
  #define DDRCKECH1_CR_DDRCRCMDCOMP_RcompDrvDown_MAX                   (63) // 0x0000003F
  #define DDRCKECH1_CR_DDRCRCMDCOMP_RcompDrvDown_DEF                   (0x00000000)
  #define DDRCKECH1_CR_DDRCRCMDCOMP_RcompDrvDown_HSH                   (0x06121300)

  #define DDRCKECH1_CR_DDRCRCMDCOMP_Spare_OFF                          (24)
  #define DDRCKECH1_CR_DDRCRCMDCOMP_Spare_WID                          ( 8)
  #define DDRCKECH1_CR_DDRCRCMDCOMP_Spare_MSK                          (0xFF000000)
  #define DDRCKECH1_CR_DDRCRCMDCOMP_Spare_MIN                          (0)
  #define DDRCKECH1_CR_DDRCRCMDCOMP_Spare_MAX                          (255) // 0x000000FF
  #define DDRCKECH1_CR_DDRCRCMDCOMP_Spare_DEF                          (0x00000004)
  #define DDRCKECH1_CR_DDRCRCMDCOMP_Spare_HSH                          (0x08181300)

#define DDRCKECH1_CR_DDRCRCMDCOMPOFFSET_REG                            (0x00001304)

  #define DDRCKECH1_CR_DDRCRCMDCOMPOFFSET_ScompOffset_OFF              ( 0)
  #define DDRCKECH1_CR_DDRCRCMDCOMPOFFSET_ScompOffset_WID              ( 5)
  #define DDRCKECH1_CR_DDRCRCMDCOMPOFFSET_ScompOffset_MSK              (0x0000001F)
  #define DDRCKECH1_CR_DDRCRCMDCOMPOFFSET_ScompOffset_MIN              (-16)
  #define DDRCKECH1_CR_DDRCRCMDCOMPOFFSET_ScompOffset_MAX              (15) // 0x0000000F
  #define DDRCKECH1_CR_DDRCRCMDCOMPOFFSET_ScompOffset_DEF              (0x00000000)
  #define DDRCKECH1_CR_DDRCRCMDCOMPOFFSET_ScompOffset_HSH              (0x85001304)

  #define DDRCKECH1_CR_DDRCRCMDCOMPOFFSET_TcoCompOffset_OFF            ( 5)
  #define DDRCKECH1_CR_DDRCRCMDCOMPOFFSET_TcoCompOffset_WID            ( 4)
  #define DDRCKECH1_CR_DDRCRCMDCOMPOFFSET_TcoCompOffset_MSK            (0x000001E0)
  #define DDRCKECH1_CR_DDRCRCMDCOMPOFFSET_TcoCompOffset_MIN            (-8)
  #define DDRCKECH1_CR_DDRCRCMDCOMPOFFSET_TcoCompOffset_MAX            (7) // 0x00000007
  #define DDRCKECH1_CR_DDRCRCMDCOMPOFFSET_TcoCompOffset_DEF            (0x00000000)
  #define DDRCKECH1_CR_DDRCRCMDCOMPOFFSET_TcoCompOffset_HSH            (0x84051304)

  #define DDRCKECH1_CR_DDRCRCMDCOMPOFFSET_RcompDrvUpOffset_OFF         ( 9)
  #define DDRCKECH1_CR_DDRCRCMDCOMPOFFSET_RcompDrvUpOffset_WID         ( 4)
  #define DDRCKECH1_CR_DDRCRCMDCOMPOFFSET_RcompDrvUpOffset_MSK         (0x00001E00)
  #define DDRCKECH1_CR_DDRCRCMDCOMPOFFSET_RcompDrvUpOffset_MIN         (-8)
  #define DDRCKECH1_CR_DDRCRCMDCOMPOFFSET_RcompDrvUpOffset_MAX         (7) // 0x00000007
  #define DDRCKECH1_CR_DDRCRCMDCOMPOFFSET_RcompDrvUpOffset_DEF         (0x00000000)
  #define DDRCKECH1_CR_DDRCRCMDCOMPOFFSET_RcompDrvUpOffset_HSH         (0x84091304)

  #define DDRCKECH1_CR_DDRCRCMDCOMPOFFSET_RcompDrvDownOffset_OFF       (13)
  #define DDRCKECH1_CR_DDRCRCMDCOMPOFFSET_RcompDrvDownOffset_WID       ( 4)
  #define DDRCKECH1_CR_DDRCRCMDCOMPOFFSET_RcompDrvDownOffset_MSK       (0x0001E000)
  #define DDRCKECH1_CR_DDRCRCMDCOMPOFFSET_RcompDrvDownOffset_MIN       (-8)
  #define DDRCKECH1_CR_DDRCRCMDCOMPOFFSET_RcompDrvDownOffset_MAX       (7) // 0x00000007
  #define DDRCKECH1_CR_DDRCRCMDCOMPOFFSET_RcompDrvDownOffset_DEF       (0x00000000)
  #define DDRCKECH1_CR_DDRCRCMDCOMPOFFSET_RcompDrvDownOffset_HSH       (0x840D1304)

  #define DDRCKECH1_CR_DDRCRCMDCOMPOFFSET_Spare_OFF                    (17)
  #define DDRCKECH1_CR_DDRCRCMDCOMPOFFSET_Spare_WID                    (15)
  #define DDRCKECH1_CR_DDRCRCMDCOMPOFFSET_Spare_MSK                    (0xFFFE0000)
  #define DDRCKECH1_CR_DDRCRCMDCOMPOFFSET_Spare_MIN                    (0)
  #define DDRCKECH1_CR_DDRCRCMDCOMPOFFSET_Spare_MAX                    (32767) // 0x00007FFF
  #define DDRCKECH1_CR_DDRCRCMDCOMPOFFSET_Spare_DEF                    (0x00000000)
  #define DDRCKECH1_CR_DDRCRCMDCOMPOFFSET_Spare_HSH                    (0x0F111304)

#define DDRCKECH1_CR_DDRCRCMDPICODING_REG                              (0x00001308)

  #define DDRCKECH1_CR_DDRCRCMDPICODING_CmdPi0Code_OFF                 ( 0)
  #define DDRCKECH1_CR_DDRCRCMDPICODING_CmdPi0Code_WID                 ( 7)
  #define DDRCKECH1_CR_DDRCRCMDPICODING_CmdPi0Code_MSK                 (0x0000007F)
  #define DDRCKECH1_CR_DDRCRCMDPICODING_CmdPi0Code_MIN                 (0)
  #define DDRCKECH1_CR_DDRCRCMDPICODING_CmdPi0Code_MAX                 (127) // 0x0000007F
  #define DDRCKECH1_CR_DDRCRCMDPICODING_CmdPi0Code_DEF                 (0x00000000)
  #define DDRCKECH1_CR_DDRCRCMDPICODING_CmdPi0Code_HSH                 (0x07001308)

  #define DDRCKECH1_CR_DDRCRCMDPICODING_CmdPi1Code_OFF                 ( 7)
  #define DDRCKECH1_CR_DDRCRCMDPICODING_CmdPi1Code_WID                 ( 7)
  #define DDRCKECH1_CR_DDRCRCMDPICODING_CmdPi1Code_MSK                 (0x00003F80)
  #define DDRCKECH1_CR_DDRCRCMDPICODING_CmdPi1Code_MIN                 (0)
  #define DDRCKECH1_CR_DDRCRCMDPICODING_CmdPi1Code_MAX                 (127) // 0x0000007F
  #define DDRCKECH1_CR_DDRCRCMDPICODING_CmdPi1Code_DEF                 (0x00000000)
  #define DDRCKECH1_CR_DDRCRCMDPICODING_CmdPi1Code_HSH                 (0x07071308)

  #define DDRCKECH1_CR_DDRCRCMDPICODING_Spare_OFF                      (14)
  #define DDRCKECH1_CR_DDRCRCMDPICODING_Spare_WID                      (18)
  #define DDRCKECH1_CR_DDRCRCMDPICODING_Spare_MSK                      (0xFFFFC000)
  #define DDRCKECH1_CR_DDRCRCMDPICODING_Spare_MIN                      (0)
  #define DDRCKECH1_CR_DDRCRCMDPICODING_Spare_MAX                      (262143) // 0x0003FFFF
  #define DDRCKECH1_CR_DDRCRCMDPICODING_Spare_DEF                      (0x00000000)
  #define DDRCKECH1_CR_DDRCRCMDPICODING_Spare_HSH                      (0x120E1308)

#define DDRCKECH1_CR_DDRCRCTLCOMP_REG                                  (0x00001310)

  #define DDRCKECH1_CR_DDRCRCTLCOMP_Scomp_OFF                          ( 0)
  #define DDRCKECH1_CR_DDRCRCTLCOMP_Scomp_WID                          ( 6)
  #define DDRCKECH1_CR_DDRCRCTLCOMP_Scomp_MSK                          (0x0000003F)
  #define DDRCKECH1_CR_DDRCRCTLCOMP_Scomp_MIN                          (0)
  #define DDRCKECH1_CR_DDRCRCTLCOMP_Scomp_MAX                          (63) // 0x0000003F
  #define DDRCKECH1_CR_DDRCRCTLCOMP_Scomp_DEF                          (0x00000000)
  #define DDRCKECH1_CR_DDRCRCTLCOMP_Scomp_HSH                          (0x06001310)

  #define DDRCKECH1_CR_DDRCRCTLCOMP_TcoComp_OFF                        ( 6)
  #define DDRCKECH1_CR_DDRCRCTLCOMP_TcoComp_WID                        ( 6)
  #define DDRCKECH1_CR_DDRCRCTLCOMP_TcoComp_MSK                        (0x00000FC0)
  #define DDRCKECH1_CR_DDRCRCTLCOMP_TcoComp_MIN                        (0)
  #define DDRCKECH1_CR_DDRCRCTLCOMP_TcoComp_MAX                        (63) // 0x0000003F
  #define DDRCKECH1_CR_DDRCRCTLCOMP_TcoComp_DEF                        (0x00000000)
  #define DDRCKECH1_CR_DDRCRCTLCOMP_TcoComp_HSH                        (0x06061310)

  #define DDRCKECH1_CR_DDRCRCTLCOMP_RcompDrvUp_OFF                     (12)
  #define DDRCKECH1_CR_DDRCRCTLCOMP_RcompDrvUp_WID                     ( 6)
  #define DDRCKECH1_CR_DDRCRCTLCOMP_RcompDrvUp_MSK                     (0x0003F000)
  #define DDRCKECH1_CR_DDRCRCTLCOMP_RcompDrvUp_MIN                     (0)
  #define DDRCKECH1_CR_DDRCRCTLCOMP_RcompDrvUp_MAX                     (63) // 0x0000003F
  #define DDRCKECH1_CR_DDRCRCTLCOMP_RcompDrvUp_DEF                     (0x00000000)
  #define DDRCKECH1_CR_DDRCRCTLCOMP_RcompDrvUp_HSH                     (0x060C1310)

  #define DDRCKECH1_CR_DDRCRCTLCOMP_RcompDrvDown_OFF                   (18)
  #define DDRCKECH1_CR_DDRCRCTLCOMP_RcompDrvDown_WID                   ( 6)
  #define DDRCKECH1_CR_DDRCRCTLCOMP_RcompDrvDown_MSK                   (0x00FC0000)
  #define DDRCKECH1_CR_DDRCRCTLCOMP_RcompDrvDown_MIN                   (0)
  #define DDRCKECH1_CR_DDRCRCTLCOMP_RcompDrvDown_MAX                   (63) // 0x0000003F
  #define DDRCKECH1_CR_DDRCRCTLCOMP_RcompDrvDown_DEF                   (0x00000000)
  #define DDRCKECH1_CR_DDRCRCTLCOMP_RcompDrvDown_HSH                   (0x06121310)

  #define DDRCKECH1_CR_DDRCRCTLCOMP_Spare_OFF                          (24)
  #define DDRCKECH1_CR_DDRCRCTLCOMP_Spare_WID                          ( 8)
  #define DDRCKECH1_CR_DDRCRCTLCOMP_Spare_MSK                          (0xFF000000)
  #define DDRCKECH1_CR_DDRCRCTLCOMP_Spare_MIN                          (0)
  #define DDRCKECH1_CR_DDRCRCTLCOMP_Spare_MAX                          (255) // 0x000000FF
  #define DDRCKECH1_CR_DDRCRCTLCOMP_Spare_DEF                          (0x00000000)
  #define DDRCKECH1_CR_DDRCRCTLCOMP_Spare_HSH                          (0x08181310)

#define DDRCKECH1_CR_DDRCRCTLCOMPOFFSET_REG                            (0x00001314)

  #define DDRCKECH1_CR_DDRCRCTLCOMPOFFSET_ScompOffset_OFF              ( 0)
  #define DDRCKECH1_CR_DDRCRCTLCOMPOFFSET_ScompOffset_WID              ( 5)
  #define DDRCKECH1_CR_DDRCRCTLCOMPOFFSET_ScompOffset_MSK              (0x0000001F)
  #define DDRCKECH1_CR_DDRCRCTLCOMPOFFSET_ScompOffset_MIN              (-16)
  #define DDRCKECH1_CR_DDRCRCTLCOMPOFFSET_ScompOffset_MAX              (15) // 0x0000000F
  #define DDRCKECH1_CR_DDRCRCTLCOMPOFFSET_ScompOffset_DEF              (0x00000000)
  #define DDRCKECH1_CR_DDRCRCTLCOMPOFFSET_ScompOffset_HSH              (0x85001314)

  #define DDRCKECH1_CR_DDRCRCTLCOMPOFFSET_TcoCompOffset_OFF            ( 5)
  #define DDRCKECH1_CR_DDRCRCTLCOMPOFFSET_TcoCompOffset_WID            ( 4)
  #define DDRCKECH1_CR_DDRCRCTLCOMPOFFSET_TcoCompOffset_MSK            (0x000001E0)
  #define DDRCKECH1_CR_DDRCRCTLCOMPOFFSET_TcoCompOffset_MIN            (-8)
  #define DDRCKECH1_CR_DDRCRCTLCOMPOFFSET_TcoCompOffset_MAX            (7) // 0x00000007
  #define DDRCKECH1_CR_DDRCRCTLCOMPOFFSET_TcoCompOffset_DEF            (0x00000000)
  #define DDRCKECH1_CR_DDRCRCTLCOMPOFFSET_TcoCompOffset_HSH            (0x84051314)

  #define DDRCKECH1_CR_DDRCRCTLCOMPOFFSET_RcompDrvUpOffset_OFF         ( 9)
  #define DDRCKECH1_CR_DDRCRCTLCOMPOFFSET_RcompDrvUpOffset_WID         ( 4)
  #define DDRCKECH1_CR_DDRCRCTLCOMPOFFSET_RcompDrvUpOffset_MSK         (0x00001E00)
  #define DDRCKECH1_CR_DDRCRCTLCOMPOFFSET_RcompDrvUpOffset_MIN         (-8)
  #define DDRCKECH1_CR_DDRCRCTLCOMPOFFSET_RcompDrvUpOffset_MAX         (7) // 0x00000007
  #define DDRCKECH1_CR_DDRCRCTLCOMPOFFSET_RcompDrvUpOffset_DEF         (0x00000000)
  #define DDRCKECH1_CR_DDRCRCTLCOMPOFFSET_RcompDrvUpOffset_HSH         (0x84091314)

  #define DDRCKECH1_CR_DDRCRCTLCOMPOFFSET_RcompDrvDownOffset_OFF       (13)
  #define DDRCKECH1_CR_DDRCRCTLCOMPOFFSET_RcompDrvDownOffset_WID       ( 4)
  #define DDRCKECH1_CR_DDRCRCTLCOMPOFFSET_RcompDrvDownOffset_MSK       (0x0001E000)
  #define DDRCKECH1_CR_DDRCRCTLCOMPOFFSET_RcompDrvDownOffset_MIN       (-8)
  #define DDRCKECH1_CR_DDRCRCTLCOMPOFFSET_RcompDrvDownOffset_MAX       (7) // 0x00000007
  #define DDRCKECH1_CR_DDRCRCTLCOMPOFFSET_RcompDrvDownOffset_DEF       (0x00000000)
  #define DDRCKECH1_CR_DDRCRCTLCOMPOFFSET_RcompDrvDownOffset_HSH       (0x840D1314)

  #define DDRCKECH1_CR_DDRCRCTLCOMPOFFSET_Spare_OFF                    (17)
  #define DDRCKECH1_CR_DDRCRCTLCOMPOFFSET_Spare_WID                    (15)
  #define DDRCKECH1_CR_DDRCRCTLCOMPOFFSET_Spare_MSK                    (0xFFFE0000)
  #define DDRCKECH1_CR_DDRCRCTLCOMPOFFSET_Spare_MIN                    (0)
  #define DDRCKECH1_CR_DDRCRCTLCOMPOFFSET_Spare_MAX                    (32767) // 0x00007FFF
  #define DDRCKECH1_CR_DDRCRCTLCOMPOFFSET_Spare_DEF                    (0x00000000)
  #define DDRCKECH1_CR_DDRCRCTLCOMPOFFSET_Spare_HSH                    (0x0F111314)

#define DDRCKECH1_CR_DDRCRCTLPICODING_REG                              (0x00001318)

  #define DDRCKECH1_CR_DDRCRCTLPICODING_CtlPiCode0_OFF                 ( 0)
  #define DDRCKECH1_CR_DDRCRCTLPICODING_CtlPiCode0_WID                 ( 7)
  #define DDRCKECH1_CR_DDRCRCTLPICODING_CtlPiCode0_MSK                 (0x0000007F)
  #define DDRCKECH1_CR_DDRCRCTLPICODING_CtlPiCode0_MIN                 (0)
  #define DDRCKECH1_CR_DDRCRCTLPICODING_CtlPiCode0_MAX                 (127) // 0x0000007F
  #define DDRCKECH1_CR_DDRCRCTLPICODING_CtlPiCode0_DEF                 (0x00000000)
  #define DDRCKECH1_CR_DDRCRCTLPICODING_CtlPiCode0_HSH                 (0x07001318)

  #define DDRCKECH1_CR_DDRCRCTLPICODING_CtlPiCode1_OFF                 ( 7)
  #define DDRCKECH1_CR_DDRCRCTLPICODING_CtlPiCode1_WID                 ( 7)
  #define DDRCKECH1_CR_DDRCRCTLPICODING_CtlPiCode1_MSK                 (0x00003F80)
  #define DDRCKECH1_CR_DDRCRCTLPICODING_CtlPiCode1_MIN                 (0)
  #define DDRCKECH1_CR_DDRCRCTLPICODING_CtlPiCode1_MAX                 (127) // 0x0000007F
  #define DDRCKECH1_CR_DDRCRCTLPICODING_CtlPiCode1_DEF                 (0x00000000)
  #define DDRCKECH1_CR_DDRCRCTLPICODING_CtlPiCode1_HSH                 (0x07071318)

  #define DDRCKECH1_CR_DDRCRCTLPICODING_CtlPiCode2_OFF                 (14)
  #define DDRCKECH1_CR_DDRCRCTLPICODING_CtlPiCode2_WID                 ( 7)
  #define DDRCKECH1_CR_DDRCRCTLPICODING_CtlPiCode2_MSK                 (0x001FC000)
  #define DDRCKECH1_CR_DDRCRCTLPICODING_CtlPiCode2_MIN                 (0)
  #define DDRCKECH1_CR_DDRCRCTLPICODING_CtlPiCode2_MAX                 (127) // 0x0000007F
  #define DDRCKECH1_CR_DDRCRCTLPICODING_CtlPiCode2_DEF                 (0x00000000)
  #define DDRCKECH1_CR_DDRCRCTLPICODING_CtlPiCode2_HSH                 (0x070E1318)

  #define DDRCKECH1_CR_DDRCRCTLPICODING_CtlPiCode3_OFF                 (21)
  #define DDRCKECH1_CR_DDRCRCTLPICODING_CtlPiCode3_WID                 ( 7)
  #define DDRCKECH1_CR_DDRCRCTLPICODING_CtlPiCode3_MSK                 (0x0FE00000)
  #define DDRCKECH1_CR_DDRCRCTLPICODING_CtlPiCode3_MIN                 (0)
  #define DDRCKECH1_CR_DDRCRCTLPICODING_CtlPiCode3_MAX                 (127) // 0x0000007F
  #define DDRCKECH1_CR_DDRCRCTLPICODING_CtlPiCode3_DEF                 (0x00000000)
  #define DDRCKECH1_CR_DDRCRCTLPICODING_CtlPiCode3_HSH                 (0x07151318)

  #define DDRCKECH1_CR_DDRCRCTLPICODING_CtlXoverEnable_OFF             (28)
  #define DDRCKECH1_CR_DDRCRCTLPICODING_CtlXoverEnable_WID             ( 1)
  #define DDRCKECH1_CR_DDRCRCTLPICODING_CtlXoverEnable_MSK             (0x10000000)
  #define DDRCKECH1_CR_DDRCRCTLPICODING_CtlXoverEnable_MIN             (0)
  #define DDRCKECH1_CR_DDRCRCTLPICODING_CtlXoverEnable_MAX             (1) // 0x00000001
  #define DDRCKECH1_CR_DDRCRCTLPICODING_CtlXoverEnable_DEF             (0x00000000)
  #define DDRCKECH1_CR_DDRCRCTLPICODING_CtlXoverEnable_HSH             (0x011C1318)

  #define DDRCKECH1_CR_DDRCRCTLPICODING_Spare_OFF                      (29)
  #define DDRCKECH1_CR_DDRCRCTLPICODING_Spare_WID                      ( 3)
  #define DDRCKECH1_CR_DDRCRCTLPICODING_Spare_MSK                      (0xE0000000)
  #define DDRCKECH1_CR_DDRCRCTLPICODING_Spare_MIN                      (0)
  #define DDRCKECH1_CR_DDRCRCTLPICODING_Spare_MAX                      (7) // 0x00000007
  #define DDRCKECH1_CR_DDRCRCTLPICODING_Spare_DEF                      (0x00000000)
  #define DDRCKECH1_CR_DDRCRCTLPICODING_Spare_HSH                      (0x031D1318)

#define DDRCKECH1_CR_DDRCRCTLCONTROLS_REG                              (0x0000131C)

  #define DDRCKECH1_CR_DDRCRCTLCONTROLS_RefPi_OFF                      ( 0)
  #define DDRCKECH1_CR_DDRCRCTLCONTROLS_RefPi_WID                      ( 4)
  #define DDRCKECH1_CR_DDRCRCTLCONTROLS_RefPi_MSK                      (0x0000000F)
  #define DDRCKECH1_CR_DDRCRCTLCONTROLS_RefPi_MIN                      (-8)
  #define DDRCKECH1_CR_DDRCRCTLCONTROLS_RefPi_MAX                      (7) // 0x00000007
  #define DDRCKECH1_CR_DDRCRCTLCONTROLS_RefPi_DEF                      (0x00000000)
  #define DDRCKECH1_CR_DDRCRCTLCONTROLS_RefPi_HSH                      (0x8400131C)

  #define DDRCKECH1_CR_DDRCRCTLCONTROLS_DllMask_OFF                    ( 4)
  #define DDRCKECH1_CR_DDRCRCTLCONTROLS_DllMask_WID                    ( 2)
  #define DDRCKECH1_CR_DDRCRCTLCONTROLS_DllMask_MSK                    (0x00000030)
  #define DDRCKECH1_CR_DDRCRCTLCONTROLS_DllMask_MIN                    (0)
  #define DDRCKECH1_CR_DDRCRCTLCONTROLS_DllMask_MAX                    (3) // 0x00000003
  #define DDRCKECH1_CR_DDRCRCTLCONTROLS_DllMask_DEF                    (0x00000000)
  #define DDRCKECH1_CR_DDRCRCTLCONTROLS_DllMask_HSH                    (0x0204131C)

  #define DDRCKECH1_CR_DDRCRCTLCONTROLS_ClkGateDisable_OFF             ( 6)
  #define DDRCKECH1_CR_DDRCRCTLCONTROLS_ClkGateDisable_WID             ( 1)
  #define DDRCKECH1_CR_DDRCRCTLCONTROLS_ClkGateDisable_MSK             (0x00000040)
  #define DDRCKECH1_CR_DDRCRCTLCONTROLS_ClkGateDisable_MIN             (0)
  #define DDRCKECH1_CR_DDRCRCTLCONTROLS_ClkGateDisable_MAX             (1) // 0x00000001
  #define DDRCKECH1_CR_DDRCRCTLCONTROLS_ClkGateDisable_DEF             (0x00000000)
  #define DDRCKECH1_CR_DDRCRCTLCONTROLS_ClkGateDisable_HSH             (0x0106131C)

  #define DDRCKECH1_CR_DDRCRCTLCONTROLS_TxOn_OFF                       ( 7)
  #define DDRCKECH1_CR_DDRCRCTLCONTROLS_TxOn_WID                       ( 1)
  #define DDRCKECH1_CR_DDRCRCTLCONTROLS_TxOn_MSK                       (0x00000080)
  #define DDRCKECH1_CR_DDRCRCTLCONTROLS_TxOn_MIN                       (0)
  #define DDRCKECH1_CR_DDRCRCTLCONTROLS_TxOn_MAX                       (1) // 0x00000001
  #define DDRCKECH1_CR_DDRCRCTLCONTROLS_TxOn_DEF                       (0x00000000)
  #define DDRCKECH1_CR_DDRCRCTLCONTROLS_TxOn_HSH                       (0x0107131C)

  #define DDRCKECH1_CR_DDRCRCTLCONTROLS_IntClkOn_OFF                   ( 8)
  #define DDRCKECH1_CR_DDRCRCTLCONTROLS_IntClkOn_WID                   ( 1)
  #define DDRCKECH1_CR_DDRCRCTLCONTROLS_IntClkOn_MSK                   (0x00000100)
  #define DDRCKECH1_CR_DDRCRCTLCONTROLS_IntClkOn_MIN                   (0)
  #define DDRCKECH1_CR_DDRCRCTLCONTROLS_IntClkOn_MAX                   (1) // 0x00000001
  #define DDRCKECH1_CR_DDRCRCTLCONTROLS_IntClkOn_DEF                   (0x00000000)
  #define DDRCKECH1_CR_DDRCRCTLCONTROLS_IntClkOn_HSH                   (0x0108131C)

  #define DDRCKECH1_CR_DDRCRCTLCONTROLS_RepClkOn_OFF                   ( 9)
  #define DDRCKECH1_CR_DDRCRCTLCONTROLS_RepClkOn_WID                   ( 1)
  #define DDRCKECH1_CR_DDRCRCTLCONTROLS_RepClkOn_MSK                   (0x00000200)
  #define DDRCKECH1_CR_DDRCRCTLCONTROLS_RepClkOn_MIN                   (0)
  #define DDRCKECH1_CR_DDRCRCTLCONTROLS_RepClkOn_MAX                   (1) // 0x00000001
  #define DDRCKECH1_CR_DDRCRCTLCONTROLS_RepClkOn_DEF                   (0x00000000)
  #define DDRCKECH1_CR_DDRCRCTLCONTROLS_RepClkOn_HSH                   (0x0109131C)

  #define DDRCKECH1_CR_DDRCRCTLCONTROLS_IolbOrMisr_OFF                 (10)
  #define DDRCKECH1_CR_DDRCRCTLCONTROLS_IolbOrMisr_WID                 ( 1)
  #define DDRCKECH1_CR_DDRCRCTLCONTROLS_IolbOrMisr_MSK                 (0x00000400)
  #define DDRCKECH1_CR_DDRCRCTLCONTROLS_IolbOrMisr_MIN                 (0)
  #define DDRCKECH1_CR_DDRCRCTLCONTROLS_IolbOrMisr_MAX                 (1) // 0x00000001
  #define DDRCKECH1_CR_DDRCRCTLCONTROLS_IolbOrMisr_DEF                 (0x00000000)
  #define DDRCKECH1_CR_DDRCRCTLCONTROLS_IolbOrMisr_HSH                 (0x010A131C)

  #define DDRCKECH1_CR_DDRCRCTLCONTROLS_IOLBHold_OFF                   (11)
  #define DDRCKECH1_CR_DDRCRCTLCONTROLS_IOLBHold_WID                   ( 1)
  #define DDRCKECH1_CR_DDRCRCTLCONTROLS_IOLBHold_MSK                   (0x00000800)
  #define DDRCKECH1_CR_DDRCRCTLCONTROLS_IOLBHold_MIN                   (0)
  #define DDRCKECH1_CR_DDRCRCTLCONTROLS_IOLBHold_MAX                   (1) // 0x00000001
  #define DDRCKECH1_CR_DDRCRCTLCONTROLS_IOLBHold_DEF                   (0x00000000)
  #define DDRCKECH1_CR_DDRCRCTLCONTROLS_IOLBHold_HSH                   (0x010B131C)

  #define DDRCKECH1_CR_DDRCRCTLCONTROLS_OdtMode_OFF                    (12)
  #define DDRCKECH1_CR_DDRCRCTLCONTROLS_OdtMode_WID                    ( 1)
  #define DDRCKECH1_CR_DDRCRCTLCONTROLS_OdtMode_MSK                    (0x00001000)
  #define DDRCKECH1_CR_DDRCRCTLCONTROLS_OdtMode_MIN                    (0)
  #define DDRCKECH1_CR_DDRCRCTLCONTROLS_OdtMode_MAX                    (1) // 0x00000001
  #define DDRCKECH1_CR_DDRCRCTLCONTROLS_OdtMode_DEF                    (0x00000000)
  #define DDRCKECH1_CR_DDRCRCTLCONTROLS_OdtMode_HSH                    (0x010C131C)

  #define DDRCKECH1_CR_DDRCRCTLCONTROLS_CmdTxEq_OFF                    (13)
  #define DDRCKECH1_CR_DDRCRCTLCONTROLS_CmdTxEq_WID                    ( 2)
  #define DDRCKECH1_CR_DDRCRCTLCONTROLS_CmdTxEq_MSK                    (0x00006000)
  #define DDRCKECH1_CR_DDRCRCTLCONTROLS_CmdTxEq_MIN                    (0)
  #define DDRCKECH1_CR_DDRCRCTLCONTROLS_CmdTxEq_MAX                    (3) // 0x00000003
  #define DDRCKECH1_CR_DDRCRCTLCONTROLS_CmdTxEq_DEF                    (0x00000000)
  #define DDRCKECH1_CR_DDRCRCTLCONTROLS_CmdTxEq_HSH                    (0x020D131C)

  #define DDRCKECH1_CR_DDRCRCTLCONTROLS_EarlyWeakDrive_OFF             (15)
  #define DDRCKECH1_CR_DDRCRCTLCONTROLS_EarlyWeakDrive_WID             ( 2)
  #define DDRCKECH1_CR_DDRCRCTLCONTROLS_EarlyWeakDrive_MSK             (0x00018000)
  #define DDRCKECH1_CR_DDRCRCTLCONTROLS_EarlyWeakDrive_MIN             (0)
  #define DDRCKECH1_CR_DDRCRCTLCONTROLS_EarlyWeakDrive_MAX             (3) // 0x00000003
  #define DDRCKECH1_CR_DDRCRCTLCONTROLS_EarlyWeakDrive_DEF             (0x00000000)
  #define DDRCKECH1_CR_DDRCRCTLCONTROLS_EarlyWeakDrive_HSH             (0x020F131C)

  #define DDRCKECH1_CR_DDRCRCTLCONTROLS_CtlTxEq_OFF                    (17)
  #define DDRCKECH1_CR_DDRCRCTLCONTROLS_CtlTxEq_WID                    ( 2)
  #define DDRCKECH1_CR_DDRCRCTLCONTROLS_CtlTxEq_MSK                    (0x00060000)
  #define DDRCKECH1_CR_DDRCRCTLCONTROLS_CtlTxEq_MIN                    (0)
  #define DDRCKECH1_CR_DDRCRCTLCONTROLS_CtlTxEq_MAX                    (3) // 0x00000003
  #define DDRCKECH1_CR_DDRCRCTLCONTROLS_CtlTxEq_DEF                    (0x00000000)
  #define DDRCKECH1_CR_DDRCRCTLCONTROLS_CtlTxEq_HSH                    (0x0211131C)

  #define DDRCKECH1_CR_DDRCRCTLCONTROLS_CtlSRDrv_OFF                   (19)
  #define DDRCKECH1_CR_DDRCRCTLCONTROLS_CtlSRDrv_WID                   ( 2)
  #define DDRCKECH1_CR_DDRCRCTLCONTROLS_CtlSRDrv_MSK                   (0x00180000)
  #define DDRCKECH1_CR_DDRCRCTLCONTROLS_CtlSRDrv_MIN                   (0)
  #define DDRCKECH1_CR_DDRCRCTLCONTROLS_CtlSRDrv_MAX                   (3) // 0x00000003
  #define DDRCKECH1_CR_DDRCRCTLCONTROLS_CtlSRDrv_DEF                   (0x00000000)
  #define DDRCKECH1_CR_DDRCRCTLCONTROLS_CtlSRDrv_HSH                   (0x0213131C)

  #define DDRCKECH1_CR_DDRCRCTLCONTROLS_RxVref_OFF                     (21)
  #define DDRCKECH1_CR_DDRCRCTLCONTROLS_RxVref_WID                     ( 6)
  #define DDRCKECH1_CR_DDRCRCTLCONTROLS_RxVref_MSK                     (0x07E00000)
  #define DDRCKECH1_CR_DDRCRCTLCONTROLS_RxVref_MIN                     (-32)
  #define DDRCKECH1_CR_DDRCRCTLCONTROLS_RxVref_MAX                     (31) // 0x0000001F
  #define DDRCKECH1_CR_DDRCRCTLCONTROLS_RxVref_DEF                     (0x00000000)
  #define DDRCKECH1_CR_DDRCRCTLCONTROLS_RxVref_HSH                     (0x8615131C)

  #define DDRCKECH1_CR_DDRCRCTLCONTROLS_VccddqHi_OFF                   (27)
  #define DDRCKECH1_CR_DDRCRCTLCONTROLS_VccddqHi_WID                   ( 1)
  #define DDRCKECH1_CR_DDRCRCTLCONTROLS_VccddqHi_MSK                   (0x08000000)
  #define DDRCKECH1_CR_DDRCRCTLCONTROLS_VccddqHi_MIN                   (0)
  #define DDRCKECH1_CR_DDRCRCTLCONTROLS_VccddqHi_MAX                   (1) // 0x00000001
  #define DDRCKECH1_CR_DDRCRCTLCONTROLS_VccddqHi_DEF                   (0x00000000)
  #define DDRCKECH1_CR_DDRCRCTLCONTROLS_VccddqHi_HSH                   (0x011B131C)

  #define DDRCKECH1_CR_DDRCRCTLCONTROLS_DllWeakLock_OFF                (28)
  #define DDRCKECH1_CR_DDRCRCTLCONTROLS_DllWeakLock_WID                ( 1)
  #define DDRCKECH1_CR_DDRCRCTLCONTROLS_DllWeakLock_MSK                (0x10000000)
  #define DDRCKECH1_CR_DDRCRCTLCONTROLS_DllWeakLock_MIN                (0)
  #define DDRCKECH1_CR_DDRCRCTLCONTROLS_DllWeakLock_MAX                (1) // 0x00000001
  #define DDRCKECH1_CR_DDRCRCTLCONTROLS_DllWeakLock_DEF                (0x00000000)
  #define DDRCKECH1_CR_DDRCRCTLCONTROLS_DllWeakLock_HSH                (0x011C131C)

  #define DDRCKECH1_CR_DDRCRCTLCONTROLS_LPDDR_Mode_OFF                 (29)
  #define DDRCKECH1_CR_DDRCRCTLCONTROLS_LPDDR_Mode_WID                 ( 1)
  #define DDRCKECH1_CR_DDRCRCTLCONTROLS_LPDDR_Mode_MSK                 (0x20000000)
  #define DDRCKECH1_CR_DDRCRCTLCONTROLS_LPDDR_Mode_MIN                 (0)
  #define DDRCKECH1_CR_DDRCRCTLCONTROLS_LPDDR_Mode_MAX                 (1) // 0x00000001
  #define DDRCKECH1_CR_DDRCRCTLCONTROLS_LPDDR_Mode_DEF                 (0x00000000)
  #define DDRCKECH1_CR_DDRCRCTLCONTROLS_LPDDR_Mode_HSH                 (0x011D131C)

  #define DDRCKECH1_CR_DDRCRCTLCONTROLS_LaDrvEnOvrd_OFF                (30)
  #define DDRCKECH1_CR_DDRCRCTLCONTROLS_LaDrvEnOvrd_WID                ( 1)
  #define DDRCKECH1_CR_DDRCRCTLCONTROLS_LaDrvEnOvrd_MSK                (0x40000000)
  #define DDRCKECH1_CR_DDRCRCTLCONTROLS_LaDrvEnOvrd_MIN                (0)
  #define DDRCKECH1_CR_DDRCRCTLCONTROLS_LaDrvEnOvrd_MAX                (1) // 0x00000001
  #define DDRCKECH1_CR_DDRCRCTLCONTROLS_LaDrvEnOvrd_DEF                (0x00000000)
  #define DDRCKECH1_CR_DDRCRCTLCONTROLS_LaDrvEnOvrd_HSH                (0x011E131C)

  #define DDRCKECH1_CR_DDRCRCTLCONTROLS_LPDdrCAA_Dis_OFF               (31)
  #define DDRCKECH1_CR_DDRCRCTLCONTROLS_LPDdrCAA_Dis_WID               ( 1)
  #define DDRCKECH1_CR_DDRCRCTLCONTROLS_LPDdrCAA_Dis_MSK               (0x80000000)
  #define DDRCKECH1_CR_DDRCRCTLCONTROLS_LPDdrCAA_Dis_MIN               (0)
  #define DDRCKECH1_CR_DDRCRCTLCONTROLS_LPDdrCAA_Dis_MAX               (1) // 0x00000001
  #define DDRCKECH1_CR_DDRCRCTLCONTROLS_LPDdrCAA_Dis_DEF               (0x00000000)
  #define DDRCKECH1_CR_DDRCRCTLCONTROLS_LPDdrCAA_Dis_HSH               (0x011F131C)

#define DDRCKECH1_CR_DDRCRCTLRANKSUSED_REG                             (0x00001320)

  #define DDRCKECH1_CR_DDRCRCTLRANKSUSED_RankEn_OFF                    ( 0)
  #define DDRCKECH1_CR_DDRCRCTLRANKSUSED_RankEn_WID                    ( 4)
  #define DDRCKECH1_CR_DDRCRCTLRANKSUSED_RankEn_MSK                    (0x0000000F)
  #define DDRCKECH1_CR_DDRCRCTLRANKSUSED_RankEn_MIN                    (0)
  #define DDRCKECH1_CR_DDRCRCTLRANKSUSED_RankEn_MAX                    (15) // 0x0000000F
  #define DDRCKECH1_CR_DDRCRCTLRANKSUSED_RankEn_DEF                    (0x0000000F)
  #define DDRCKECH1_CR_DDRCRCTLRANKSUSED_RankEn_HSH                    (0x04001320)

  #define DDRCKECH1_CR_DDRCRCTLRANKSUSED_OdtDisable_OFF                ( 4)
  #define DDRCKECH1_CR_DDRCRCTLRANKSUSED_OdtDisable_WID                ( 2)
  #define DDRCKECH1_CR_DDRCRCTLRANKSUSED_OdtDisable_MSK                (0x00000030)
  #define DDRCKECH1_CR_DDRCRCTLRANKSUSED_OdtDisable_MIN                (0)
  #define DDRCKECH1_CR_DDRCRCTLRANKSUSED_OdtDisable_MAX                (3) // 0x00000003
  #define DDRCKECH1_CR_DDRCRCTLRANKSUSED_OdtDisable_DEF                (0x00000000)
  #define DDRCKECH1_CR_DDRCRCTLRANKSUSED_OdtDisable_HSH                (0x02041320)

  #define DDRCKECH1_CR_DDRCRCTLRANKSUSED_DdrCkeCmdSlwDlyByp_OFF        ( 6)
  #define DDRCKECH1_CR_DDRCRCTLRANKSUSED_DdrCkeCmdSlwDlyByp_WID        ( 1)
  #define DDRCKECH1_CR_DDRCRCTLRANKSUSED_DdrCkeCmdSlwDlyByp_MSK        (0x00000040)
  #define DDRCKECH1_CR_DDRCRCTLRANKSUSED_DdrCkeCmdSlwDlyByp_MIN        (0)
  #define DDRCKECH1_CR_DDRCRCTLRANKSUSED_DdrCkeCmdSlwDlyByp_MAX        (1) // 0x00000001
  #define DDRCKECH1_CR_DDRCRCTLRANKSUSED_DdrCkeCmdSlwDlyByp_DEF        (0x00000000)
  #define DDRCKECH1_CR_DDRCRCTLRANKSUSED_DdrCkeCmdSlwDlyByp_HSH        (0x01061320)

  #define DDRCKECH1_CR_DDRCRCTLRANKSUSED_DdrCtlCkeSlwDlyByp_OFF        ( 7)
  #define DDRCKECH1_CR_DDRCRCTLRANKSUSED_DdrCtlCkeSlwDlyByp_WID        ( 1)
  #define DDRCKECH1_CR_DDRCRCTLRANKSUSED_DdrCtlCkeSlwDlyByp_MSK        (0x00000080)
  #define DDRCKECH1_CR_DDRCRCTLRANKSUSED_DdrCtlCkeSlwDlyByp_MIN        (0)
  #define DDRCKECH1_CR_DDRCRCTLRANKSUSED_DdrCtlCkeSlwDlyByp_MAX        (1) // 0x00000001
  #define DDRCKECH1_CR_DDRCRCTLRANKSUSED_DdrCtlCkeSlwDlyByp_DEF        (0x00000000)
  #define DDRCKECH1_CR_DDRCRCTLRANKSUSED_DdrCtlCkeSlwDlyByp_HSH        (0x01071320)

  #define DDRCKECH1_CR_DDRCRCTLRANKSUSED_CsPiClkGateEn_OFF             ( 8)
  #define DDRCKECH1_CR_DDRCRCTLRANKSUSED_CsPiClkGateEn_WID             ( 1)
  #define DDRCKECH1_CR_DDRCRCTLRANKSUSED_CsPiClkGateEn_MSK             (0x00000100)
  #define DDRCKECH1_CR_DDRCRCTLRANKSUSED_CsPiClkGateEn_MIN             (0)
  #define DDRCKECH1_CR_DDRCRCTLRANKSUSED_CsPiClkGateEn_MAX             (1) // 0x00000001
  #define DDRCKECH1_CR_DDRCRCTLRANKSUSED_CsPiClkGateEn_DEF             (0x00000000)
  #define DDRCKECH1_CR_DDRCRCTLRANKSUSED_CsPiClkGateEn_HSH             (0x01081320)

  #define DDRCKECH1_CR_DDRCRCTLRANKSUSED_CsClkGateDis_OFF              ( 9)
  #define DDRCKECH1_CR_DDRCRCTLRANKSUSED_CsClkGateDis_WID              ( 1)
  #define DDRCKECH1_CR_DDRCRCTLRANKSUSED_CsClkGateDis_MSK              (0x00000200)
  #define DDRCKECH1_CR_DDRCRCTLRANKSUSED_CsClkGateDis_MIN              (0)
  #define DDRCKECH1_CR_DDRCRCTLRANKSUSED_CsClkGateDis_MAX              (1) // 0x00000001
  #define DDRCKECH1_CR_DDRCRCTLRANKSUSED_CsClkGateDis_DEF              (0x00000000)
  #define DDRCKECH1_CR_DDRCRCTLRANKSUSED_CsClkGateDis_HSH              (0x01091320)

  #define DDRCKECH1_CR_DDRCRCTLRANKSUSED_Spare_OFF                     (10)
  #define DDRCKECH1_CR_DDRCRCTLRANKSUSED_Spare_WID                     (22)
  #define DDRCKECH1_CR_DDRCRCTLRANKSUSED_Spare_MSK                     (0xFFFFFC00)
  #define DDRCKECH1_CR_DDRCRCTLRANKSUSED_Spare_MIN                     (0)
  #define DDRCKECH1_CR_DDRCRCTLRANKSUSED_Spare_MAX                     (4194303) // 0x003FFFFF
  #define DDRCKECH1_CR_DDRCRCTLRANKSUSED_Spare_DEF                     (0x00000000)
  #define DDRCKECH1_CR_DDRCRCTLRANKSUSED_Spare_HSH                     (0x160A1320)

#define DDRCKECH1_CR_DLLPITESTANDADC_REG                               (0x00001324)

  #define DDRCKECH1_CR_DLLPITESTANDADC_RunTest_OFF                     ( 0)
  #define DDRCKECH1_CR_DLLPITESTANDADC_RunTest_WID                     ( 1)
  #define DDRCKECH1_CR_DLLPITESTANDADC_RunTest_MSK                     (0x00000001)
  #define DDRCKECH1_CR_DLLPITESTANDADC_RunTest_MIN                     (0)
  #define DDRCKECH1_CR_DLLPITESTANDADC_RunTest_MAX                     (1) // 0x00000001
  #define DDRCKECH1_CR_DLLPITESTANDADC_RunTest_DEF                     (0x00000000)
  #define DDRCKECH1_CR_DLLPITESTANDADC_RunTest_HSH                     (0x01001324)

  #define DDRCKECH1_CR_DLLPITESTANDADC_Load_OFF                        ( 1)
  #define DDRCKECH1_CR_DLLPITESTANDADC_Load_WID                        ( 1)
  #define DDRCKECH1_CR_DLLPITESTANDADC_Load_MSK                        (0x00000002)
  #define DDRCKECH1_CR_DLLPITESTANDADC_Load_MIN                        (0)
  #define DDRCKECH1_CR_DLLPITESTANDADC_Load_MAX                        (1) // 0x00000001
  #define DDRCKECH1_CR_DLLPITESTANDADC_Load_DEF                        (0x00000000)
  #define DDRCKECH1_CR_DLLPITESTANDADC_Load_HSH                        (0x01011324)

  #define DDRCKECH1_CR_DLLPITESTANDADC_ModeHVM_OFF                     ( 2)
  #define DDRCKECH1_CR_DLLPITESTANDADC_ModeHVM_WID                     ( 1)
  #define DDRCKECH1_CR_DLLPITESTANDADC_ModeHVM_MSK                     (0x00000004)
  #define DDRCKECH1_CR_DLLPITESTANDADC_ModeHVM_MIN                     (0)
  #define DDRCKECH1_CR_DLLPITESTANDADC_ModeHVM_MAX                     (1) // 0x00000001
  #define DDRCKECH1_CR_DLLPITESTANDADC_ModeHVM_DEF                     (0x00000000)
  #define DDRCKECH1_CR_DLLPITESTANDADC_ModeHVM_HSH                     (0x01021324)

  #define DDRCKECH1_CR_DLLPITESTANDADC_ModeDV_OFF                      ( 3)
  #define DDRCKECH1_CR_DLLPITESTANDADC_ModeDV_WID                      ( 1)
  #define DDRCKECH1_CR_DLLPITESTANDADC_ModeDV_MSK                      (0x00000008)
  #define DDRCKECH1_CR_DLLPITESTANDADC_ModeDV_MIN                      (0)
  #define DDRCKECH1_CR_DLLPITESTANDADC_ModeDV_MAX                      (1) // 0x00000001
  #define DDRCKECH1_CR_DLLPITESTANDADC_ModeDV_DEF                      (0x00000000)
  #define DDRCKECH1_CR_DLLPITESTANDADC_ModeDV_HSH                      (0x01031324)

  #define DDRCKECH1_CR_DLLPITESTANDADC_CalCfdl_OFF                     ( 4)
  #define DDRCKECH1_CR_DLLPITESTANDADC_CalCfdl_WID                     ( 1)
  #define DDRCKECH1_CR_DLLPITESTANDADC_CalCfdl_MSK                     (0x00000010)
  #define DDRCKECH1_CR_DLLPITESTANDADC_CalCfdl_MIN                     (0)
  #define DDRCKECH1_CR_DLLPITESTANDADC_CalCfdl_MAX                     (1) // 0x00000001
  #define DDRCKECH1_CR_DLLPITESTANDADC_CalCfdl_DEF                     (0x00000000)
  #define DDRCKECH1_CR_DLLPITESTANDADC_CalCfdl_HSH                     (0x01041324)

  #define DDRCKECH1_CR_DLLPITESTANDADC_LoadCount_OFF                   ( 5)
  #define DDRCKECH1_CR_DLLPITESTANDADC_LoadCount_WID                   (10)
  #define DDRCKECH1_CR_DLLPITESTANDADC_LoadCount_MSK                   (0x00007FE0)
  #define DDRCKECH1_CR_DLLPITESTANDADC_LoadCount_MIN                   (0)
  #define DDRCKECH1_CR_DLLPITESTANDADC_LoadCount_MAX                   (1023) // 0x000003FF
  #define DDRCKECH1_CR_DLLPITESTANDADC_LoadCount_DEF                   (0x00000000)
  #define DDRCKECH1_CR_DLLPITESTANDADC_LoadCount_HSH                   (0x0A051324)

  #define DDRCKECH1_CR_DLLPITESTANDADC_CountStatus_OFF                 (15)
  #define DDRCKECH1_CR_DLLPITESTANDADC_CountStatus_WID                 (10)
  #define DDRCKECH1_CR_DLLPITESTANDADC_CountStatus_MSK                 (0x01FF8000)
  #define DDRCKECH1_CR_DLLPITESTANDADC_CountStatus_MIN                 (0)
  #define DDRCKECH1_CR_DLLPITESTANDADC_CountStatus_MAX                 (1023) // 0x000003FF
  #define DDRCKECH1_CR_DLLPITESTANDADC_CountStatus_DEF                 (0x00000000)
  #define DDRCKECH1_CR_DLLPITESTANDADC_CountStatus_HSH                 (0x0A0F1324)

  #define DDRCKECH1_CR_DLLPITESTANDADC_PhaseDrvPwrSavOn_OFF            (25)
  #define DDRCKECH1_CR_DLLPITESTANDADC_PhaseDrvPwrSavOn_WID            ( 1)
  #define DDRCKECH1_CR_DLLPITESTANDADC_PhaseDrvPwrSavOn_MSK            (0x02000000)
  #define DDRCKECH1_CR_DLLPITESTANDADC_PhaseDrvPwrSavOn_MIN            (0)
  #define DDRCKECH1_CR_DLLPITESTANDADC_PhaseDrvPwrSavOn_MAX            (1) // 0x00000001
  #define DDRCKECH1_CR_DLLPITESTANDADC_PhaseDrvPwrSavOn_DEF            (0x00000000)
  #define DDRCKECH1_CR_DLLPITESTANDADC_PhaseDrvPwrSavOn_HSH            (0x01191324)

  #define DDRCKECH1_CR_DLLPITESTANDADC_Spare_OFF                       (26)
  #define DDRCKECH1_CR_DLLPITESTANDADC_Spare_WID                       ( 6)
  #define DDRCKECH1_CR_DLLPITESTANDADC_Spare_MSK                       (0xFC000000)
  #define DDRCKECH1_CR_DLLPITESTANDADC_Spare_MIN                       (0)
  #define DDRCKECH1_CR_DLLPITESTANDADC_Spare_MAX                       (63) // 0x0000003F
  #define DDRCKECH1_CR_DLLPITESTANDADC_Spare_DEF                       (0x00000000)
  #define DDRCKECH1_CR_DLLPITESTANDADC_Spare_HSH                       (0x061A1324)

#define DDRCKECH1_CR_DDRCMDMISR_REG                                    (0x00001328)

  #define DDRCKECH1_CR_DDRCMDMISR_shift_16_OFF                         ( 0)
  #define DDRCKECH1_CR_DDRCMDMISR_shift_16_WID                         ( 1)
  #define DDRCKECH1_CR_DDRCMDMISR_shift_16_MSK                         (0x00000001)
  #define DDRCKECH1_CR_DDRCMDMISR_shift_16_MIN                         (0)
  #define DDRCKECH1_CR_DDRCMDMISR_shift_16_MAX                         (1) // 0x00000001
  #define DDRCKECH1_CR_DDRCMDMISR_shift_16_DEF                         (0x00000000)
  #define DDRCKECH1_CR_DDRCMDMISR_shift_16_HSH                         (0x01001328)

  #define DDRCKECH1_CR_DDRCMDMISR_clken_pulse_mode_OFF                 ( 1)
  #define DDRCKECH1_CR_DDRCMDMISR_clken_pulse_mode_WID                 ( 1)
  #define DDRCKECH1_CR_DDRCMDMISR_clken_pulse_mode_MSK                 (0x00000002)
  #define DDRCKECH1_CR_DDRCMDMISR_clken_pulse_mode_MIN                 (0)
  #define DDRCKECH1_CR_DDRCMDMISR_clken_pulse_mode_MAX                 (1) // 0x00000001
  #define DDRCKECH1_CR_DDRCMDMISR_clken_pulse_mode_DEF                 (0x00000000)
  #define DDRCKECH1_CR_DDRCMDMISR_clken_pulse_mode_HSH                 (0x01011328)

  #define DDRCKECH1_CR_DDRCMDMISR_reg_clken_mode_OFF                   ( 2)
  #define DDRCKECH1_CR_DDRCMDMISR_reg_clken_mode_WID                   ( 1)
  #define DDRCKECH1_CR_DDRCMDMISR_reg_clken_mode_MSK                   (0x00000004)
  #define DDRCKECH1_CR_DDRCMDMISR_reg_clken_mode_MIN                   (0)
  #define DDRCKECH1_CR_DDRCMDMISR_reg_clken_mode_MAX                   (1) // 0x00000001
  #define DDRCKECH1_CR_DDRCMDMISR_reg_clken_mode_DEF                   (0x00000000)
  #define DDRCKECH1_CR_DDRCMDMISR_reg_clken_mode_HSH                   (0x01021328)

  #define DDRCKECH1_CR_DDRCMDMISR_reg_clken_OFF                        ( 3)
  #define DDRCKECH1_CR_DDRCMDMISR_reg_clken_WID                        ( 1)
  #define DDRCKECH1_CR_DDRCMDMISR_reg_clken_MSK                        (0x00000008)
  #define DDRCKECH1_CR_DDRCMDMISR_reg_clken_MIN                        (0)
  #define DDRCKECH1_CR_DDRCMDMISR_reg_clken_MAX                        (1) // 0x00000001
  #define DDRCKECH1_CR_DDRCMDMISR_reg_clken_DEF                        (0x00000000)
  #define DDRCKECH1_CR_DDRCMDMISR_reg_clken_HSH                        (0x01031328)

  #define DDRCKECH1_CR_DDRCMDMISR_feedback_en_OFF                      ( 4)
  #define DDRCKECH1_CR_DDRCMDMISR_feedback_en_WID                      ( 1)
  #define DDRCKECH1_CR_DDRCMDMISR_feedback_en_MSK                      (0x00000010)
  #define DDRCKECH1_CR_DDRCMDMISR_feedback_en_MIN                      (0)
  #define DDRCKECH1_CR_DDRCMDMISR_feedback_en_MAX                      (1) // 0x00000001
  #define DDRCKECH1_CR_DDRCMDMISR_feedback_en_DEF                      (0x00000000)
  #define DDRCKECH1_CR_DDRCMDMISR_feedback_en_HSH                      (0x01041328)

  #define DDRCKECH1_CR_DDRCMDMISR_event_mode_OFF                       ( 5)
  #define DDRCKECH1_CR_DDRCMDMISR_event_mode_WID                       ( 1)
  #define DDRCKECH1_CR_DDRCMDMISR_event_mode_MSK                       (0x00000020)
  #define DDRCKECH1_CR_DDRCMDMISR_event_mode_MIN                       (0)
  #define DDRCKECH1_CR_DDRCMDMISR_event_mode_MAX                       (1) // 0x00000001
  #define DDRCKECH1_CR_DDRCMDMISR_event_mode_DEF                       (0x00000000)
  #define DDRCKECH1_CR_DDRCMDMISR_event_mode_HSH                       (0x01051328)

  #define DDRCKECH1_CR_DDRCMDMISR_lfsr_reset_OFF                       ( 6)
  #define DDRCKECH1_CR_DDRCMDMISR_lfsr_reset_WID                       ( 1)
  #define DDRCKECH1_CR_DDRCMDMISR_lfsr_reset_MSK                       (0x00000040)
  #define DDRCKECH1_CR_DDRCMDMISR_lfsr_reset_MIN                       (0)
  #define DDRCKECH1_CR_DDRCMDMISR_lfsr_reset_MAX                       (1) // 0x00000001
  #define DDRCKECH1_CR_DDRCMDMISR_lfsr_reset_DEF                       (0x00000000)
  #define DDRCKECH1_CR_DDRCMDMISR_lfsr_reset_HSH                       (0x01061328)

  #define DDRCKECH1_CR_DDRCMDMISR_sdo_en_OFF                           ( 7)
  #define DDRCKECH1_CR_DDRCMDMISR_sdo_en_WID                           ( 1)
  #define DDRCKECH1_CR_DDRCMDMISR_sdo_en_MSK                           (0x00000080)
  #define DDRCKECH1_CR_DDRCMDMISR_sdo_en_MIN                           (0)
  #define DDRCKECH1_CR_DDRCMDMISR_sdo_en_MAX                           (1) // 0x00000001
  #define DDRCKECH1_CR_DDRCMDMISR_sdo_en_DEF                           (0x00000000)
  #define DDRCKECH1_CR_DDRCMDMISR_sdo_en_HSH                           (0x01071328)

  #define DDRCKECH1_CR_DDRCMDMISR_cr_rd_data_OFF                       (16)
  #define DDRCKECH1_CR_DDRCMDMISR_cr_rd_data_WID                       (16)
  #define DDRCKECH1_CR_DDRCMDMISR_cr_rd_data_MSK                       (0xFFFF0000)
  #define DDRCKECH1_CR_DDRCMDMISR_cr_rd_data_MIN                       (0)
  #define DDRCKECH1_CR_DDRCMDMISR_cr_rd_data_MAX                       (65535) // 0x0000FFFF
  #define DDRCKECH1_CR_DDRCMDMISR_cr_rd_data_DEF                       (0x00000000)
  #define DDRCKECH1_CR_DDRCMDMISR_cr_rd_data_HSH                       (0x10101328)

#define DDRCMDNCH0_CR_DDRCRCMDCOMP_REG                                 (0x00001400)

  #define DDRCMDNCH0_CR_DDRCRCMDCOMP_Scomp_OFF                         ( 0)
  #define DDRCMDNCH0_CR_DDRCRCMDCOMP_Scomp_WID                         ( 6)
  #define DDRCMDNCH0_CR_DDRCRCMDCOMP_Scomp_MSK                         (0x0000003F)
  #define DDRCMDNCH0_CR_DDRCRCMDCOMP_Scomp_MIN                         (0)
  #define DDRCMDNCH0_CR_DDRCRCMDCOMP_Scomp_MAX                         (63) // 0x0000003F
  #define DDRCMDNCH0_CR_DDRCRCMDCOMP_Scomp_DEF                         (0x00000000)
  #define DDRCMDNCH0_CR_DDRCRCMDCOMP_Scomp_HSH                         (0x06001400)

  #define DDRCMDNCH0_CR_DDRCRCMDCOMP_TcoComp_OFF                       ( 6)
  #define DDRCMDNCH0_CR_DDRCRCMDCOMP_TcoComp_WID                       ( 6)
  #define DDRCMDNCH0_CR_DDRCRCMDCOMP_TcoComp_MSK                       (0x00000FC0)
  #define DDRCMDNCH0_CR_DDRCRCMDCOMP_TcoComp_MIN                       (0)
  #define DDRCMDNCH0_CR_DDRCRCMDCOMP_TcoComp_MAX                       (63) // 0x0000003F
  #define DDRCMDNCH0_CR_DDRCRCMDCOMP_TcoComp_DEF                       (0x00000000)
  #define DDRCMDNCH0_CR_DDRCRCMDCOMP_TcoComp_HSH                       (0x06061400)

  #define DDRCMDNCH0_CR_DDRCRCMDCOMP_RcompDrvUp_OFF                    (12)
  #define DDRCMDNCH0_CR_DDRCRCMDCOMP_RcompDrvUp_WID                    ( 6)
  #define DDRCMDNCH0_CR_DDRCRCMDCOMP_RcompDrvUp_MSK                    (0x0003F000)
  #define DDRCMDNCH0_CR_DDRCRCMDCOMP_RcompDrvUp_MIN                    (0)
  #define DDRCMDNCH0_CR_DDRCRCMDCOMP_RcompDrvUp_MAX                    (63) // 0x0000003F
  #define DDRCMDNCH0_CR_DDRCRCMDCOMP_RcompDrvUp_DEF                    (0x00000000)
  #define DDRCMDNCH0_CR_DDRCRCMDCOMP_RcompDrvUp_HSH                    (0x060C1400)

  #define DDRCMDNCH0_CR_DDRCRCMDCOMP_RcompDrvDown_OFF                  (18)
  #define DDRCMDNCH0_CR_DDRCRCMDCOMP_RcompDrvDown_WID                  ( 6)
  #define DDRCMDNCH0_CR_DDRCRCMDCOMP_RcompDrvDown_MSK                  (0x00FC0000)
  #define DDRCMDNCH0_CR_DDRCRCMDCOMP_RcompDrvDown_MIN                  (0)
  #define DDRCMDNCH0_CR_DDRCRCMDCOMP_RcompDrvDown_MAX                  (63) // 0x0000003F
  #define DDRCMDNCH0_CR_DDRCRCMDCOMP_RcompDrvDown_DEF                  (0x00000000)
  #define DDRCMDNCH0_CR_DDRCRCMDCOMP_RcompDrvDown_HSH                  (0x06121400)

  #define DDRCMDNCH0_CR_DDRCRCMDCOMP_Spare_OFF                         (24)
  #define DDRCMDNCH0_CR_DDRCRCMDCOMP_Spare_WID                         ( 8)
  #define DDRCMDNCH0_CR_DDRCRCMDCOMP_Spare_MSK                         (0xFF000000)
  #define DDRCMDNCH0_CR_DDRCRCMDCOMP_Spare_MIN                         (0)
  #define DDRCMDNCH0_CR_DDRCRCMDCOMP_Spare_MAX                         (255) // 0x000000FF
  #define DDRCMDNCH0_CR_DDRCRCMDCOMP_Spare_DEF                         (0x00000004)
  #define DDRCMDNCH0_CR_DDRCRCMDCOMP_Spare_HSH                         (0x08181400)

#define DDRCMDNCH0_CR_DDRCRCMDCOMPOFFSET_REG                           (0x00001404)

  #define DDRCMDNCH0_CR_DDRCRCMDCOMPOFFSET_ScompOffset_OFF             ( 0)
  #define DDRCMDNCH0_CR_DDRCRCMDCOMPOFFSET_ScompOffset_WID             ( 5)
  #define DDRCMDNCH0_CR_DDRCRCMDCOMPOFFSET_ScompOffset_MSK             (0x0000001F)
  #define DDRCMDNCH0_CR_DDRCRCMDCOMPOFFSET_ScompOffset_MIN             (-16)
  #define DDRCMDNCH0_CR_DDRCRCMDCOMPOFFSET_ScompOffset_MAX             (15) // 0x0000000F
  #define DDRCMDNCH0_CR_DDRCRCMDCOMPOFFSET_ScompOffset_DEF             (0x00000000)
  #define DDRCMDNCH0_CR_DDRCRCMDCOMPOFFSET_ScompOffset_HSH             (0x85001404)

  #define DDRCMDNCH0_CR_DDRCRCMDCOMPOFFSET_TcoCompOffset_OFF           ( 5)
  #define DDRCMDNCH0_CR_DDRCRCMDCOMPOFFSET_TcoCompOffset_WID           ( 4)
  #define DDRCMDNCH0_CR_DDRCRCMDCOMPOFFSET_TcoCompOffset_MSK           (0x000001E0)
  #define DDRCMDNCH0_CR_DDRCRCMDCOMPOFFSET_TcoCompOffset_MIN           (-8)
  #define DDRCMDNCH0_CR_DDRCRCMDCOMPOFFSET_TcoCompOffset_MAX           (7) // 0x00000007
  #define DDRCMDNCH0_CR_DDRCRCMDCOMPOFFSET_TcoCompOffset_DEF           (0x00000000)
  #define DDRCMDNCH0_CR_DDRCRCMDCOMPOFFSET_TcoCompOffset_HSH           (0x84051404)

  #define DDRCMDNCH0_CR_DDRCRCMDCOMPOFFSET_RcompDrvUpOffset_OFF        ( 9)
  #define DDRCMDNCH0_CR_DDRCRCMDCOMPOFFSET_RcompDrvUpOffset_WID        ( 4)
  #define DDRCMDNCH0_CR_DDRCRCMDCOMPOFFSET_RcompDrvUpOffset_MSK        (0x00001E00)
  #define DDRCMDNCH0_CR_DDRCRCMDCOMPOFFSET_RcompDrvUpOffset_MIN        (-8)
  #define DDRCMDNCH0_CR_DDRCRCMDCOMPOFFSET_RcompDrvUpOffset_MAX        (7) // 0x00000007
  #define DDRCMDNCH0_CR_DDRCRCMDCOMPOFFSET_RcompDrvUpOffset_DEF        (0x00000000)
  #define DDRCMDNCH0_CR_DDRCRCMDCOMPOFFSET_RcompDrvUpOffset_HSH        (0x84091404)

  #define DDRCMDNCH0_CR_DDRCRCMDCOMPOFFSET_RcompDrvDownOffset_OFF      (13)
  #define DDRCMDNCH0_CR_DDRCRCMDCOMPOFFSET_RcompDrvDownOffset_WID      ( 4)
  #define DDRCMDNCH0_CR_DDRCRCMDCOMPOFFSET_RcompDrvDownOffset_MSK      (0x0001E000)
  #define DDRCMDNCH0_CR_DDRCRCMDCOMPOFFSET_RcompDrvDownOffset_MIN      (-8)
  #define DDRCMDNCH0_CR_DDRCRCMDCOMPOFFSET_RcompDrvDownOffset_MAX      (7) // 0x00000007
  #define DDRCMDNCH0_CR_DDRCRCMDCOMPOFFSET_RcompDrvDownOffset_DEF      (0x00000000)
  #define DDRCMDNCH0_CR_DDRCRCMDCOMPOFFSET_RcompDrvDownOffset_HSH      (0x840D1404)

  #define DDRCMDNCH0_CR_DDRCRCMDCOMPOFFSET_Spare_OFF                   (17)
  #define DDRCMDNCH0_CR_DDRCRCMDCOMPOFFSET_Spare_WID                   (15)
  #define DDRCMDNCH0_CR_DDRCRCMDCOMPOFFSET_Spare_MSK                   (0xFFFE0000)
  #define DDRCMDNCH0_CR_DDRCRCMDCOMPOFFSET_Spare_MIN                   (0)
  #define DDRCMDNCH0_CR_DDRCRCMDCOMPOFFSET_Spare_MAX                   (32767) // 0x00007FFF
  #define DDRCMDNCH0_CR_DDRCRCMDCOMPOFFSET_Spare_DEF                   (0x00000000)
  #define DDRCMDNCH0_CR_DDRCRCMDCOMPOFFSET_Spare_HSH                   (0x0F111404)

#define DDRCMDNCH0_CR_DDRCRCMDPICODING_REG                             (0x00001408)

  #define DDRCMDNCH0_CR_DDRCRCMDPICODING_CmdPi0Code_OFF                ( 0)
  #define DDRCMDNCH0_CR_DDRCRCMDPICODING_CmdPi0Code_WID                ( 7)
  #define DDRCMDNCH0_CR_DDRCRCMDPICODING_CmdPi0Code_MSK                (0x0000007F)
  #define DDRCMDNCH0_CR_DDRCRCMDPICODING_CmdPi0Code_MIN                (0)
  #define DDRCMDNCH0_CR_DDRCRCMDPICODING_CmdPi0Code_MAX                (127) // 0x0000007F
  #define DDRCMDNCH0_CR_DDRCRCMDPICODING_CmdPi0Code_DEF                (0x00000000)
  #define DDRCMDNCH0_CR_DDRCRCMDPICODING_CmdPi0Code_HSH                (0x07001408)

  #define DDRCMDNCH0_CR_DDRCRCMDPICODING_CmdPi1Code_OFF                ( 7)
  #define DDRCMDNCH0_CR_DDRCRCMDPICODING_CmdPi1Code_WID                ( 7)
  #define DDRCMDNCH0_CR_DDRCRCMDPICODING_CmdPi1Code_MSK                (0x00003F80)
  #define DDRCMDNCH0_CR_DDRCRCMDPICODING_CmdPi1Code_MIN                (0)
  #define DDRCMDNCH0_CR_DDRCRCMDPICODING_CmdPi1Code_MAX                (127) // 0x0000007F
  #define DDRCMDNCH0_CR_DDRCRCMDPICODING_CmdPi1Code_DEF                (0x00000000)
  #define DDRCMDNCH0_CR_DDRCRCMDPICODING_CmdPi1Code_HSH                (0x07071408)

  #define DDRCMDNCH0_CR_DDRCRCMDPICODING_Spare_OFF                     (14)
  #define DDRCMDNCH0_CR_DDRCRCMDPICODING_Spare_WID                     (18)
  #define DDRCMDNCH0_CR_DDRCRCMDPICODING_Spare_MSK                     (0xFFFFC000)
  #define DDRCMDNCH0_CR_DDRCRCMDPICODING_Spare_MIN                     (0)
  #define DDRCMDNCH0_CR_DDRCRCMDPICODING_Spare_MAX                     (262143) // 0x0003FFFF
  #define DDRCMDNCH0_CR_DDRCRCMDPICODING_Spare_DEF                     (0x00000000)
  #define DDRCMDNCH0_CR_DDRCRCMDPICODING_Spare_HSH                     (0x120E1408)

#define DDRCMDNCH0_CR_DDRCRCMDCONTROLS_REG                             (0x0000140C)

  #define DDRCMDNCH0_CR_DDRCRCMDCONTROLS_RefPi_OFF                     ( 0)
  #define DDRCMDNCH0_CR_DDRCRCMDCONTROLS_RefPi_WID                     ( 4)
  #define DDRCMDNCH0_CR_DDRCRCMDCONTROLS_RefPi_MSK                     (0x0000000F)
  #define DDRCMDNCH0_CR_DDRCRCMDCONTROLS_RefPi_MIN                     (-8)
  #define DDRCMDNCH0_CR_DDRCRCMDCONTROLS_RefPi_MAX                     (7) // 0x00000007
  #define DDRCMDNCH0_CR_DDRCRCMDCONTROLS_RefPi_DEF                     (0x00000000)
  #define DDRCMDNCH0_CR_DDRCRCMDCONTROLS_RefPi_HSH                     (0x8400140C)

  #define DDRCMDNCH0_CR_DDRCRCMDCONTROLS_DllMask_OFF                   ( 4)
  #define DDRCMDNCH0_CR_DDRCRCMDCONTROLS_DllMask_WID                   ( 2)
  #define DDRCMDNCH0_CR_DDRCRCMDCONTROLS_DllMask_MSK                   (0x00000030)
  #define DDRCMDNCH0_CR_DDRCRCMDCONTROLS_DllMask_MIN                   (0)
  #define DDRCMDNCH0_CR_DDRCRCMDCONTROLS_DllMask_MAX                   (3) // 0x00000003
  #define DDRCMDNCH0_CR_DDRCRCMDCONTROLS_DllMask_DEF                   (0x00000000)
  #define DDRCMDNCH0_CR_DDRCRCMDCONTROLS_DllMask_HSH                   (0x0204140C)

  #define DDRCMDNCH0_CR_DDRCRCMDCONTROLS_ClkGateDisable_OFF            ( 6)
  #define DDRCMDNCH0_CR_DDRCRCMDCONTROLS_ClkGateDisable_WID            ( 1)
  #define DDRCMDNCH0_CR_DDRCRCMDCONTROLS_ClkGateDisable_MSK            (0x00000040)
  #define DDRCMDNCH0_CR_DDRCRCMDCONTROLS_ClkGateDisable_MIN            (0)
  #define DDRCMDNCH0_CR_DDRCRCMDCONTROLS_ClkGateDisable_MAX            (1) // 0x00000001
  #define DDRCMDNCH0_CR_DDRCRCMDCONTROLS_ClkGateDisable_DEF            (0x00000000)
  #define DDRCMDNCH0_CR_DDRCRCMDCONTROLS_ClkGateDisable_HSH            (0x0106140C)

  #define DDRCMDNCH0_CR_DDRCRCMDCONTROLS_TxOn_OFF                      ( 7)
  #define DDRCMDNCH0_CR_DDRCRCMDCONTROLS_TxOn_WID                      ( 1)
  #define DDRCMDNCH0_CR_DDRCRCMDCONTROLS_TxOn_MSK                      (0x00000080)
  #define DDRCMDNCH0_CR_DDRCRCMDCONTROLS_TxOn_MIN                      (0)
  #define DDRCMDNCH0_CR_DDRCRCMDCONTROLS_TxOn_MAX                      (1) // 0x00000001
  #define DDRCMDNCH0_CR_DDRCRCMDCONTROLS_TxOn_DEF                      (0x00000000)
  #define DDRCMDNCH0_CR_DDRCRCMDCONTROLS_TxOn_HSH                      (0x0107140C)

  #define DDRCMDNCH0_CR_DDRCRCMDCONTROLS_IntClkOn_OFF                  ( 8)
  #define DDRCMDNCH0_CR_DDRCRCMDCONTROLS_IntClkOn_WID                  ( 1)
  #define DDRCMDNCH0_CR_DDRCRCMDCONTROLS_IntClkOn_MSK                  (0x00000100)
  #define DDRCMDNCH0_CR_DDRCRCMDCONTROLS_IntClkOn_MIN                  (0)
  #define DDRCMDNCH0_CR_DDRCRCMDCONTROLS_IntClkOn_MAX                  (1) // 0x00000001
  #define DDRCMDNCH0_CR_DDRCRCMDCONTROLS_IntClkOn_DEF                  (0x00000000)
  #define DDRCMDNCH0_CR_DDRCRCMDCONTROLS_IntClkOn_HSH                  (0x0108140C)

  #define DDRCMDNCH0_CR_DDRCRCMDCONTROLS_RepClkOn_OFF                  ( 9)
  #define DDRCMDNCH0_CR_DDRCRCMDCONTROLS_RepClkOn_WID                  ( 1)
  #define DDRCMDNCH0_CR_DDRCRCMDCONTROLS_RepClkOn_MSK                  (0x00000200)
  #define DDRCMDNCH0_CR_DDRCRCMDCONTROLS_RepClkOn_MIN                  (0)
  #define DDRCMDNCH0_CR_DDRCRCMDCONTROLS_RepClkOn_MAX                  (1) // 0x00000001
  #define DDRCMDNCH0_CR_DDRCRCMDCONTROLS_RepClkOn_DEF                  (0x00000000)
  #define DDRCMDNCH0_CR_DDRCRCMDCONTROLS_RepClkOn_HSH                  (0x0109140C)

  #define DDRCMDNCH0_CR_DDRCRCMDCONTROLS_IolbOrMisr_OFF                (10)
  #define DDRCMDNCH0_CR_DDRCRCMDCONTROLS_IolbOrMisr_WID                ( 1)
  #define DDRCMDNCH0_CR_DDRCRCMDCONTROLS_IolbOrMisr_MSK                (0x00000400)
  #define DDRCMDNCH0_CR_DDRCRCMDCONTROLS_IolbOrMisr_MIN                (0)
  #define DDRCMDNCH0_CR_DDRCRCMDCONTROLS_IolbOrMisr_MAX                (1) // 0x00000001
  #define DDRCMDNCH0_CR_DDRCRCMDCONTROLS_IolbOrMisr_DEF                (0x00000000)
  #define DDRCMDNCH0_CR_DDRCRCMDCONTROLS_IolbOrMisr_HSH                (0x010A140C)

  #define DDRCMDNCH0_CR_DDRCRCMDCONTROLS_IolbHold_OFF                  (11)
  #define DDRCMDNCH0_CR_DDRCRCMDCONTROLS_IolbHold_WID                  ( 1)
  #define DDRCMDNCH0_CR_DDRCRCMDCONTROLS_IolbHold_MSK                  (0x00000800)
  #define DDRCMDNCH0_CR_DDRCRCMDCONTROLS_IolbHold_MIN                  (0)
  #define DDRCMDNCH0_CR_DDRCRCMDCONTROLS_IolbHold_MAX                  (1) // 0x00000001
  #define DDRCMDNCH0_CR_DDRCRCMDCONTROLS_IolbHold_DEF                  (0x00000000)
  #define DDRCMDNCH0_CR_DDRCRCMDCONTROLS_IolbHold_HSH                  (0x010B140C)

  #define DDRCMDNCH0_CR_DDRCRCMDCONTROLS_OdtMode_OFF                   (12)
  #define DDRCMDNCH0_CR_DDRCRCMDCONTROLS_OdtMode_WID                   ( 1)
  #define DDRCMDNCH0_CR_DDRCRCMDCONTROLS_OdtMode_MSK                   (0x00001000)
  #define DDRCMDNCH0_CR_DDRCRCMDCONTROLS_OdtMode_MIN                   (0)
  #define DDRCMDNCH0_CR_DDRCRCMDCONTROLS_OdtMode_MAX                   (1) // 0x00000001
  #define DDRCMDNCH0_CR_DDRCRCMDCONTROLS_OdtMode_DEF                   (0x00000000)
  #define DDRCMDNCH0_CR_DDRCRCMDCONTROLS_OdtMode_HSH                   (0x010C140C)

  #define DDRCMDNCH0_CR_DDRCRCMDCONTROLS_CmdTxEq_OFF                   (13)
  #define DDRCMDNCH0_CR_DDRCRCMDCONTROLS_CmdTxEq_WID                   ( 2)
  #define DDRCMDNCH0_CR_DDRCRCMDCONTROLS_CmdTxEq_MSK                   (0x00006000)
  #define DDRCMDNCH0_CR_DDRCRCMDCONTROLS_CmdTxEq_MIN                   (0)
  #define DDRCMDNCH0_CR_DDRCRCMDCONTROLS_CmdTxEq_MAX                   (3) // 0x00000003
  #define DDRCMDNCH0_CR_DDRCRCMDCONTROLS_CmdTxEq_DEF                   (0x00000000)
  #define DDRCMDNCH0_CR_DDRCRCMDCONTROLS_CmdTxEq_HSH                   (0x020D140C)

  #define DDRCMDNCH0_CR_DDRCRCMDCONTROLS_EarlyWeakDrive_OFF            (15)
  #define DDRCMDNCH0_CR_DDRCRCMDCONTROLS_EarlyWeakDrive_WID            ( 2)
  #define DDRCMDNCH0_CR_DDRCRCMDCONTROLS_EarlyWeakDrive_MSK            (0x00018000)
  #define DDRCMDNCH0_CR_DDRCRCMDCONTROLS_EarlyWeakDrive_MIN            (0)
  #define DDRCMDNCH0_CR_DDRCRCMDCONTROLS_EarlyWeakDrive_MAX            (3) // 0x00000003
  #define DDRCMDNCH0_CR_DDRCRCMDCONTROLS_EarlyWeakDrive_DEF            (0x00000000)
  #define DDRCMDNCH0_CR_DDRCRCMDCONTROLS_EarlyWeakDrive_HSH            (0x020F140C)

  #define DDRCMDNCH0_CR_DDRCRCMDCONTROLS_PrtEn_OFF                     (17)
  #define DDRCMDNCH0_CR_DDRCRCMDCONTROLS_PrtEn_WID                     ( 1)
  #define DDRCMDNCH0_CR_DDRCRCMDCONTROLS_PrtEn_MSK                     (0x00020000)
  #define DDRCMDNCH0_CR_DDRCRCMDCONTROLS_PrtEn_MIN                     (0)
  #define DDRCMDNCH0_CR_DDRCRCMDCONTROLS_PrtEn_MAX                     (1) // 0x00000001
  #define DDRCMDNCH0_CR_DDRCRCMDCONTROLS_PrtEn_DEF                     (0x00000000)
  #define DDRCMDNCH0_CR_DDRCRCMDCONTROLS_PrtEn_HSH                     (0x0111140C)

  #define DDRCMDNCH0_CR_DDRCRCMDCONTROLS_AlrtEn_OFF                    (18)
  #define DDRCMDNCH0_CR_DDRCRCMDCONTROLS_AlrtEn_WID                    ( 1)
  #define DDRCMDNCH0_CR_DDRCRCMDCONTROLS_AlrtEn_MSK                    (0x00040000)
  #define DDRCMDNCH0_CR_DDRCRCMDCONTROLS_AlrtEn_MIN                    (0)
  #define DDRCMDNCH0_CR_DDRCRCMDCONTROLS_AlrtEn_MAX                    (1) // 0x00000001
  #define DDRCMDNCH0_CR_DDRCRCMDCONTROLS_AlrtEn_DEF                    (0x00000000)
  #define DDRCMDNCH0_CR_DDRCRCMDCONTROLS_AlrtEn_HSH                    (0x0112140C)

  #define DDRCMDNCH0_CR_DDRCRCMDCONTROLS_LaDrvEnOvrd_OFF               (19)
  #define DDRCMDNCH0_CR_DDRCRCMDCONTROLS_LaDrvEnOvrd_WID               ( 1)
  #define DDRCMDNCH0_CR_DDRCRCMDCONTROLS_LaDrvEnOvrd_MSK               (0x00080000)
  #define DDRCMDNCH0_CR_DDRCRCMDCONTROLS_LaDrvEnOvrd_MIN               (0)
  #define DDRCMDNCH0_CR_DDRCRCMDCONTROLS_LaDrvEnOvrd_MAX               (1) // 0x00000001
  #define DDRCMDNCH0_CR_DDRCRCMDCONTROLS_LaDrvEnOvrd_DEF               (0x00000000)
  #define DDRCMDNCH0_CR_DDRCRCMDCONTROLS_LaDrvEnOvrd_HSH               (0x0113140C)

  #define DDRCMDNCH0_CR_DDRCRCMDCONTROLS_DdrCmdSlwDlyByp_OFF           (20)
  #define DDRCMDNCH0_CR_DDRCRCMDCONTROLS_DdrCmdSlwDlyByp_WID           ( 1)
  #define DDRCMDNCH0_CR_DDRCRCMDCONTROLS_DdrCmdSlwDlyByp_MSK           (0x00100000)
  #define DDRCMDNCH0_CR_DDRCRCMDCONTROLS_DdrCmdSlwDlyByp_MIN           (0)
  #define DDRCMDNCH0_CR_DDRCRCMDCONTROLS_DdrCmdSlwDlyByp_MAX           (1) // 0x00000001
  #define DDRCMDNCH0_CR_DDRCRCMDCONTROLS_DdrCmdSlwDlyByp_DEF           (0x00000000)
  #define DDRCMDNCH0_CR_DDRCRCMDCONTROLS_DdrCmdSlwDlyByp_HSH           (0x0114140C)

  #define DDRCMDNCH0_CR_DDRCRCMDCONTROLS_RxVref_OFF                    (21)
  #define DDRCMDNCH0_CR_DDRCRCMDCONTROLS_RxVref_WID                    ( 6)
  #define DDRCMDNCH0_CR_DDRCRCMDCONTROLS_RxVref_MSK                    (0x07E00000)
  #define DDRCMDNCH0_CR_DDRCRCMDCONTROLS_RxVref_MIN                    (-32)
  #define DDRCMDNCH0_CR_DDRCRCMDCONTROLS_RxVref_MAX                    (31) // 0x0000001F
  #define DDRCMDNCH0_CR_DDRCRCMDCONTROLS_RxVref_DEF                    (0x00000000)
  #define DDRCMDNCH0_CR_DDRCRCMDCONTROLS_RxVref_HSH                    (0x8615140C)

  #define DDRCMDNCH0_CR_DDRCRCMDCONTROLS_VccddqHi_OFF                  (27)
  #define DDRCMDNCH0_CR_DDRCRCMDCONTROLS_VccddqHi_WID                  ( 1)
  #define DDRCMDNCH0_CR_DDRCRCMDCONTROLS_VccddqHi_MSK                  (0x08000000)
  #define DDRCMDNCH0_CR_DDRCRCMDCONTROLS_VccddqHi_MIN                  (0)
  #define DDRCMDNCH0_CR_DDRCRCMDCONTROLS_VccddqHi_MAX                  (1) // 0x00000001
  #define DDRCMDNCH0_CR_DDRCRCMDCONTROLS_VccddqHi_DEF                  (0x00000000)
  #define DDRCMDNCH0_CR_DDRCRCMDCONTROLS_VccddqHi_HSH                  (0x011B140C)

  #define DDRCMDNCH0_CR_DDRCRCMDCONTROLS_DllWeakLock_OFF               (28)
  #define DDRCMDNCH0_CR_DDRCRCMDCONTROLS_DllWeakLock_WID               ( 1)
  #define DDRCMDNCH0_CR_DDRCRCMDCONTROLS_DllWeakLock_MSK               (0x10000000)
  #define DDRCMDNCH0_CR_DDRCRCMDCONTROLS_DllWeakLock_MIN               (0)
  #define DDRCMDNCH0_CR_DDRCRCMDCONTROLS_DllWeakLock_MAX               (1) // 0x00000001
  #define DDRCMDNCH0_CR_DDRCRCMDCONTROLS_DllWeakLock_DEF               (0x00000000)
  #define DDRCMDNCH0_CR_DDRCRCMDCONTROLS_DllWeakLock_HSH               (0x011C140C)

  #define DDRCMDNCH0_CR_DDRCRCMDCONTROLS_LPDDR_Mode_OFF                (29)
  #define DDRCMDNCH0_CR_DDRCRCMDCONTROLS_LPDDR_Mode_WID                ( 1)
  #define DDRCMDNCH0_CR_DDRCRCMDCONTROLS_LPDDR_Mode_MSK                (0x20000000)
  #define DDRCMDNCH0_CR_DDRCRCMDCONTROLS_LPDDR_Mode_MIN                (0)
  #define DDRCMDNCH0_CR_DDRCRCMDCONTROLS_LPDDR_Mode_MAX                (1) // 0x00000001
  #define DDRCMDNCH0_CR_DDRCRCMDCONTROLS_LPDDR_Mode_DEF                (0x00000000)
  #define DDRCMDNCH0_CR_DDRCRCMDCONTROLS_LPDDR_Mode_HSH                (0x011D140C)

  #define DDRCMDNCH0_CR_DDRCRCMDCONTROLS_LPDdrCAA_Dis_OFF              (30)
  #define DDRCMDNCH0_CR_DDRCRCMDCONTROLS_LPDdrCAA_Dis_WID              ( 1)
  #define DDRCMDNCH0_CR_DDRCRCMDCONTROLS_LPDdrCAA_Dis_MSK              (0x40000000)
  #define DDRCMDNCH0_CR_DDRCRCMDCONTROLS_LPDdrCAA_Dis_MIN              (0)
  #define DDRCMDNCH0_CR_DDRCRCMDCONTROLS_LPDdrCAA_Dis_MAX              (1) // 0x00000001
  #define DDRCMDNCH0_CR_DDRCRCMDCONTROLS_LPDdrCAA_Dis_DEF              (0x00000000)
  #define DDRCMDNCH0_CR_DDRCRCMDCONTROLS_LPDdrCAA_Dis_HSH              (0x011E140C)

  #define DDRCMDNCH0_CR_DDRCRCMDCONTROLS_LPDdrCAB_Dis_OFF              (31)
  #define DDRCMDNCH0_CR_DDRCRCMDCONTROLS_LPDdrCAB_Dis_WID              ( 1)
  #define DDRCMDNCH0_CR_DDRCRCMDCONTROLS_LPDdrCAB_Dis_MSK              (0x80000000)
  #define DDRCMDNCH0_CR_DDRCRCMDCONTROLS_LPDdrCAB_Dis_MIN              (0)
  #define DDRCMDNCH0_CR_DDRCRCMDCONTROLS_LPDdrCAB_Dis_MAX              (1) // 0x00000001
  #define DDRCMDNCH0_CR_DDRCRCMDCONTROLS_LPDdrCAB_Dis_DEF              (0x00000000)
  #define DDRCMDNCH0_CR_DDRCRCMDCONTROLS_LPDdrCAB_Dis_HSH              (0x011F140C)

#define DDRCMDNCH0_CR_DLLPITESTANDADC_REG                              (0x00001424)

  #define DDRCMDNCH0_CR_DLLPITESTANDADC_RunTest_OFF                    ( 0)
  #define DDRCMDNCH0_CR_DLLPITESTANDADC_RunTest_WID                    ( 1)
  #define DDRCMDNCH0_CR_DLLPITESTANDADC_RunTest_MSK                    (0x00000001)
  #define DDRCMDNCH0_CR_DLLPITESTANDADC_RunTest_MIN                    (0)
  #define DDRCMDNCH0_CR_DLLPITESTANDADC_RunTest_MAX                    (1) // 0x00000001
  #define DDRCMDNCH0_CR_DLLPITESTANDADC_RunTest_DEF                    (0x00000000)
  #define DDRCMDNCH0_CR_DLLPITESTANDADC_RunTest_HSH                    (0x01001424)

  #define DDRCMDNCH0_CR_DLLPITESTANDADC_Load_OFF                       ( 1)
  #define DDRCMDNCH0_CR_DLLPITESTANDADC_Load_WID                       ( 1)
  #define DDRCMDNCH0_CR_DLLPITESTANDADC_Load_MSK                       (0x00000002)
  #define DDRCMDNCH0_CR_DLLPITESTANDADC_Load_MIN                       (0)
  #define DDRCMDNCH0_CR_DLLPITESTANDADC_Load_MAX                       (1) // 0x00000001
  #define DDRCMDNCH0_CR_DLLPITESTANDADC_Load_DEF                       (0x00000000)
  #define DDRCMDNCH0_CR_DLLPITESTANDADC_Load_HSH                       (0x01011424)

  #define DDRCMDNCH0_CR_DLLPITESTANDADC_ModeHVM_OFF                    ( 2)
  #define DDRCMDNCH0_CR_DLLPITESTANDADC_ModeHVM_WID                    ( 1)
  #define DDRCMDNCH0_CR_DLLPITESTANDADC_ModeHVM_MSK                    (0x00000004)
  #define DDRCMDNCH0_CR_DLLPITESTANDADC_ModeHVM_MIN                    (0)
  #define DDRCMDNCH0_CR_DLLPITESTANDADC_ModeHVM_MAX                    (1) // 0x00000001
  #define DDRCMDNCH0_CR_DLLPITESTANDADC_ModeHVM_DEF                    (0x00000000)
  #define DDRCMDNCH0_CR_DLLPITESTANDADC_ModeHVM_HSH                    (0x01021424)

  #define DDRCMDNCH0_CR_DLLPITESTANDADC_ModeDV_OFF                     ( 3)
  #define DDRCMDNCH0_CR_DLLPITESTANDADC_ModeDV_WID                     ( 1)
  #define DDRCMDNCH0_CR_DLLPITESTANDADC_ModeDV_MSK                     (0x00000008)
  #define DDRCMDNCH0_CR_DLLPITESTANDADC_ModeDV_MIN                     (0)
  #define DDRCMDNCH0_CR_DLLPITESTANDADC_ModeDV_MAX                     (1) // 0x00000001
  #define DDRCMDNCH0_CR_DLLPITESTANDADC_ModeDV_DEF                     (0x00000000)
  #define DDRCMDNCH0_CR_DLLPITESTANDADC_ModeDV_HSH                     (0x01031424)

  #define DDRCMDNCH0_CR_DLLPITESTANDADC_CalCfdl_OFF                    ( 4)
  #define DDRCMDNCH0_CR_DLLPITESTANDADC_CalCfdl_WID                    ( 1)
  #define DDRCMDNCH0_CR_DLLPITESTANDADC_CalCfdl_MSK                    (0x00000010)
  #define DDRCMDNCH0_CR_DLLPITESTANDADC_CalCfdl_MIN                    (0)
  #define DDRCMDNCH0_CR_DLLPITESTANDADC_CalCfdl_MAX                    (1) // 0x00000001
  #define DDRCMDNCH0_CR_DLLPITESTANDADC_CalCfdl_DEF                    (0x00000000)
  #define DDRCMDNCH0_CR_DLLPITESTANDADC_CalCfdl_HSH                    (0x01041424)

  #define DDRCMDNCH0_CR_DLLPITESTANDADC_LoadCount_OFF                  ( 5)
  #define DDRCMDNCH0_CR_DLLPITESTANDADC_LoadCount_WID                  (10)
  #define DDRCMDNCH0_CR_DLLPITESTANDADC_LoadCount_MSK                  (0x00007FE0)
  #define DDRCMDNCH0_CR_DLLPITESTANDADC_LoadCount_MIN                  (0)
  #define DDRCMDNCH0_CR_DLLPITESTANDADC_LoadCount_MAX                  (1023) // 0x000003FF
  #define DDRCMDNCH0_CR_DLLPITESTANDADC_LoadCount_DEF                  (0x00000000)
  #define DDRCMDNCH0_CR_DLLPITESTANDADC_LoadCount_HSH                  (0x0A051424)

  #define DDRCMDNCH0_CR_DLLPITESTANDADC_CountStatus_OFF                (15)
  #define DDRCMDNCH0_CR_DLLPITESTANDADC_CountStatus_WID                (10)
  #define DDRCMDNCH0_CR_DLLPITESTANDADC_CountStatus_MSK                (0x01FF8000)
  #define DDRCMDNCH0_CR_DLLPITESTANDADC_CountStatus_MIN                (0)
  #define DDRCMDNCH0_CR_DLLPITESTANDADC_CountStatus_MAX                (1023) // 0x000003FF
  #define DDRCMDNCH0_CR_DLLPITESTANDADC_CountStatus_DEF                (0x00000000)
  #define DDRCMDNCH0_CR_DLLPITESTANDADC_CountStatus_HSH                (0x0A0F1424)

  #define DDRCMDNCH0_CR_DLLPITESTANDADC_PhaseDrvPwrSavOn_OFF           (25)
  #define DDRCMDNCH0_CR_DLLPITESTANDADC_PhaseDrvPwrSavOn_WID           ( 1)
  #define DDRCMDNCH0_CR_DLLPITESTANDADC_PhaseDrvPwrSavOn_MSK           (0x02000000)
  #define DDRCMDNCH0_CR_DLLPITESTANDADC_PhaseDrvPwrSavOn_MIN           (0)
  #define DDRCMDNCH0_CR_DLLPITESTANDADC_PhaseDrvPwrSavOn_MAX           (1) // 0x00000001
  #define DDRCMDNCH0_CR_DLLPITESTANDADC_PhaseDrvPwrSavOn_DEF           (0x00000000)
  #define DDRCMDNCH0_CR_DLLPITESTANDADC_PhaseDrvPwrSavOn_HSH           (0x01191424)

  #define DDRCMDNCH0_CR_DLLPITESTANDADC_Spare_OFF                      (26)
  #define DDRCMDNCH0_CR_DLLPITESTANDADC_Spare_WID                      ( 6)
  #define DDRCMDNCH0_CR_DLLPITESTANDADC_Spare_MSK                      (0xFC000000)
  #define DDRCMDNCH0_CR_DLLPITESTANDADC_Spare_MIN                      (0)
  #define DDRCMDNCH0_CR_DLLPITESTANDADC_Spare_MAX                      (63) // 0x0000003F
  #define DDRCMDNCH0_CR_DLLPITESTANDADC_Spare_DEF                      (0x00000000)
  #define DDRCMDNCH0_CR_DLLPITESTANDADC_Spare_HSH                      (0x061A1424)

#define DDRCMDNCH1_CR_DDRCRCMDCOMP_REG                                 (0x00001500)

  #define DDRCMDNCH1_CR_DDRCRCMDCOMP_Scomp_OFF                         ( 0)
  #define DDRCMDNCH1_CR_DDRCRCMDCOMP_Scomp_WID                         ( 6)
  #define DDRCMDNCH1_CR_DDRCRCMDCOMP_Scomp_MSK                         (0x0000003F)
  #define DDRCMDNCH1_CR_DDRCRCMDCOMP_Scomp_MIN                         (0)
  #define DDRCMDNCH1_CR_DDRCRCMDCOMP_Scomp_MAX                         (63) // 0x0000003F
  #define DDRCMDNCH1_CR_DDRCRCMDCOMP_Scomp_DEF                         (0x00000000)
  #define DDRCMDNCH1_CR_DDRCRCMDCOMP_Scomp_HSH                         (0x06001500)

  #define DDRCMDNCH1_CR_DDRCRCMDCOMP_TcoComp_OFF                       ( 6)
  #define DDRCMDNCH1_CR_DDRCRCMDCOMP_TcoComp_WID                       ( 6)
  #define DDRCMDNCH1_CR_DDRCRCMDCOMP_TcoComp_MSK                       (0x00000FC0)
  #define DDRCMDNCH1_CR_DDRCRCMDCOMP_TcoComp_MIN                       (0)
  #define DDRCMDNCH1_CR_DDRCRCMDCOMP_TcoComp_MAX                       (63) // 0x0000003F
  #define DDRCMDNCH1_CR_DDRCRCMDCOMP_TcoComp_DEF                       (0x00000000)
  #define DDRCMDNCH1_CR_DDRCRCMDCOMP_TcoComp_HSH                       (0x06061500)

  #define DDRCMDNCH1_CR_DDRCRCMDCOMP_RcompDrvUp_OFF                    (12)
  #define DDRCMDNCH1_CR_DDRCRCMDCOMP_RcompDrvUp_WID                    ( 6)
  #define DDRCMDNCH1_CR_DDRCRCMDCOMP_RcompDrvUp_MSK                    (0x0003F000)
  #define DDRCMDNCH1_CR_DDRCRCMDCOMP_RcompDrvUp_MIN                    (0)
  #define DDRCMDNCH1_CR_DDRCRCMDCOMP_RcompDrvUp_MAX                    (63) // 0x0000003F
  #define DDRCMDNCH1_CR_DDRCRCMDCOMP_RcompDrvUp_DEF                    (0x00000000)
  #define DDRCMDNCH1_CR_DDRCRCMDCOMP_RcompDrvUp_HSH                    (0x060C1500)

  #define DDRCMDNCH1_CR_DDRCRCMDCOMP_RcompDrvDown_OFF                  (18)
  #define DDRCMDNCH1_CR_DDRCRCMDCOMP_RcompDrvDown_WID                  ( 6)
  #define DDRCMDNCH1_CR_DDRCRCMDCOMP_RcompDrvDown_MSK                  (0x00FC0000)
  #define DDRCMDNCH1_CR_DDRCRCMDCOMP_RcompDrvDown_MIN                  (0)
  #define DDRCMDNCH1_CR_DDRCRCMDCOMP_RcompDrvDown_MAX                  (63) // 0x0000003F
  #define DDRCMDNCH1_CR_DDRCRCMDCOMP_RcompDrvDown_DEF                  (0x00000000)
  #define DDRCMDNCH1_CR_DDRCRCMDCOMP_RcompDrvDown_HSH                  (0x06121500)

  #define DDRCMDNCH1_CR_DDRCRCMDCOMP_Spare_OFF                         (24)
  #define DDRCMDNCH1_CR_DDRCRCMDCOMP_Spare_WID                         ( 8)
  #define DDRCMDNCH1_CR_DDRCRCMDCOMP_Spare_MSK                         (0xFF000000)
  #define DDRCMDNCH1_CR_DDRCRCMDCOMP_Spare_MIN                         (0)
  #define DDRCMDNCH1_CR_DDRCRCMDCOMP_Spare_MAX                         (255) // 0x000000FF
  #define DDRCMDNCH1_CR_DDRCRCMDCOMP_Spare_DEF                         (0x00000004)
  #define DDRCMDNCH1_CR_DDRCRCMDCOMP_Spare_HSH                         (0x08181500)

#define DDRCMDNCH1_CR_DDRCRCMDCOMPOFFSET_REG                           (0x00001504)

  #define DDRCMDNCH1_CR_DDRCRCMDCOMPOFFSET_ScompOffset_OFF             ( 0)
  #define DDRCMDNCH1_CR_DDRCRCMDCOMPOFFSET_ScompOffset_WID             ( 5)
  #define DDRCMDNCH1_CR_DDRCRCMDCOMPOFFSET_ScompOffset_MSK             (0x0000001F)
  #define DDRCMDNCH1_CR_DDRCRCMDCOMPOFFSET_ScompOffset_MIN             (-16)
  #define DDRCMDNCH1_CR_DDRCRCMDCOMPOFFSET_ScompOffset_MAX             (15) // 0x0000000F
  #define DDRCMDNCH1_CR_DDRCRCMDCOMPOFFSET_ScompOffset_DEF             (0x00000000)
  #define DDRCMDNCH1_CR_DDRCRCMDCOMPOFFSET_ScompOffset_HSH             (0x85001504)

  #define DDRCMDNCH1_CR_DDRCRCMDCOMPOFFSET_TcoCompOffset_OFF           ( 5)
  #define DDRCMDNCH1_CR_DDRCRCMDCOMPOFFSET_TcoCompOffset_WID           ( 4)
  #define DDRCMDNCH1_CR_DDRCRCMDCOMPOFFSET_TcoCompOffset_MSK           (0x000001E0)
  #define DDRCMDNCH1_CR_DDRCRCMDCOMPOFFSET_TcoCompOffset_MIN           (-8)
  #define DDRCMDNCH1_CR_DDRCRCMDCOMPOFFSET_TcoCompOffset_MAX           (7) // 0x00000007
  #define DDRCMDNCH1_CR_DDRCRCMDCOMPOFFSET_TcoCompOffset_DEF           (0x00000000)
  #define DDRCMDNCH1_CR_DDRCRCMDCOMPOFFSET_TcoCompOffset_HSH           (0x84051504)

  #define DDRCMDNCH1_CR_DDRCRCMDCOMPOFFSET_RcompDrvUpOffset_OFF        ( 9)
  #define DDRCMDNCH1_CR_DDRCRCMDCOMPOFFSET_RcompDrvUpOffset_WID        ( 4)
  #define DDRCMDNCH1_CR_DDRCRCMDCOMPOFFSET_RcompDrvUpOffset_MSK        (0x00001E00)
  #define DDRCMDNCH1_CR_DDRCRCMDCOMPOFFSET_RcompDrvUpOffset_MIN        (-8)
  #define DDRCMDNCH1_CR_DDRCRCMDCOMPOFFSET_RcompDrvUpOffset_MAX        (7) // 0x00000007
  #define DDRCMDNCH1_CR_DDRCRCMDCOMPOFFSET_RcompDrvUpOffset_DEF        (0x00000000)
  #define DDRCMDNCH1_CR_DDRCRCMDCOMPOFFSET_RcompDrvUpOffset_HSH        (0x84091504)

  #define DDRCMDNCH1_CR_DDRCRCMDCOMPOFFSET_RcompDrvDownOffset_OFF      (13)
  #define DDRCMDNCH1_CR_DDRCRCMDCOMPOFFSET_RcompDrvDownOffset_WID      ( 4)
  #define DDRCMDNCH1_CR_DDRCRCMDCOMPOFFSET_RcompDrvDownOffset_MSK      (0x0001E000)
  #define DDRCMDNCH1_CR_DDRCRCMDCOMPOFFSET_RcompDrvDownOffset_MIN      (-8)
  #define DDRCMDNCH1_CR_DDRCRCMDCOMPOFFSET_RcompDrvDownOffset_MAX      (7) // 0x00000007
  #define DDRCMDNCH1_CR_DDRCRCMDCOMPOFFSET_RcompDrvDownOffset_DEF      (0x00000000)
  #define DDRCMDNCH1_CR_DDRCRCMDCOMPOFFSET_RcompDrvDownOffset_HSH      (0x840D1504)

  #define DDRCMDNCH1_CR_DDRCRCMDCOMPOFFSET_Spare_OFF                   (17)
  #define DDRCMDNCH1_CR_DDRCRCMDCOMPOFFSET_Spare_WID                   (15)
  #define DDRCMDNCH1_CR_DDRCRCMDCOMPOFFSET_Spare_MSK                   (0xFFFE0000)
  #define DDRCMDNCH1_CR_DDRCRCMDCOMPOFFSET_Spare_MIN                   (0)
  #define DDRCMDNCH1_CR_DDRCRCMDCOMPOFFSET_Spare_MAX                   (32767) // 0x00007FFF
  #define DDRCMDNCH1_CR_DDRCRCMDCOMPOFFSET_Spare_DEF                   (0x00000000)
  #define DDRCMDNCH1_CR_DDRCRCMDCOMPOFFSET_Spare_HSH                   (0x0F111504)

#define DDRCMDNCH1_CR_DDRCRCMDPICODING_REG                             (0x00001508)

  #define DDRCMDNCH1_CR_DDRCRCMDPICODING_CmdPi0Code_OFF                ( 0)
  #define DDRCMDNCH1_CR_DDRCRCMDPICODING_CmdPi0Code_WID                ( 7)
  #define DDRCMDNCH1_CR_DDRCRCMDPICODING_CmdPi0Code_MSK                (0x0000007F)
  #define DDRCMDNCH1_CR_DDRCRCMDPICODING_CmdPi0Code_MIN                (0)
  #define DDRCMDNCH1_CR_DDRCRCMDPICODING_CmdPi0Code_MAX                (127) // 0x0000007F
  #define DDRCMDNCH1_CR_DDRCRCMDPICODING_CmdPi0Code_DEF                (0x00000000)
  #define DDRCMDNCH1_CR_DDRCRCMDPICODING_CmdPi0Code_HSH                (0x07001508)

  #define DDRCMDNCH1_CR_DDRCRCMDPICODING_CmdPi1Code_OFF                ( 7)
  #define DDRCMDNCH1_CR_DDRCRCMDPICODING_CmdPi1Code_WID                ( 7)
  #define DDRCMDNCH1_CR_DDRCRCMDPICODING_CmdPi1Code_MSK                (0x00003F80)
  #define DDRCMDNCH1_CR_DDRCRCMDPICODING_CmdPi1Code_MIN                (0)
  #define DDRCMDNCH1_CR_DDRCRCMDPICODING_CmdPi1Code_MAX                (127) // 0x0000007F
  #define DDRCMDNCH1_CR_DDRCRCMDPICODING_CmdPi1Code_DEF                (0x00000000)
  #define DDRCMDNCH1_CR_DDRCRCMDPICODING_CmdPi1Code_HSH                (0x07071508)

  #define DDRCMDNCH1_CR_DDRCRCMDPICODING_Spare_OFF                     (14)
  #define DDRCMDNCH1_CR_DDRCRCMDPICODING_Spare_WID                     (18)
  #define DDRCMDNCH1_CR_DDRCRCMDPICODING_Spare_MSK                     (0xFFFFC000)
  #define DDRCMDNCH1_CR_DDRCRCMDPICODING_Spare_MIN                     (0)
  #define DDRCMDNCH1_CR_DDRCRCMDPICODING_Spare_MAX                     (262143) // 0x0003FFFF
  #define DDRCMDNCH1_CR_DDRCRCMDPICODING_Spare_DEF                     (0x00000000)
  #define DDRCMDNCH1_CR_DDRCRCMDPICODING_Spare_HSH                     (0x120E1508)

#define DDRCMDNCH1_CR_DDRCRCMDCONTROLS_REG                             (0x0000150C)

  #define DDRCMDNCH1_CR_DDRCRCMDCONTROLS_RefPi_OFF                     ( 0)
  #define DDRCMDNCH1_CR_DDRCRCMDCONTROLS_RefPi_WID                     ( 4)
  #define DDRCMDNCH1_CR_DDRCRCMDCONTROLS_RefPi_MSK                     (0x0000000F)
  #define DDRCMDNCH1_CR_DDRCRCMDCONTROLS_RefPi_MIN                     (-8)
  #define DDRCMDNCH1_CR_DDRCRCMDCONTROLS_RefPi_MAX                     (7) // 0x00000007
  #define DDRCMDNCH1_CR_DDRCRCMDCONTROLS_RefPi_DEF                     (0x00000000)
  #define DDRCMDNCH1_CR_DDRCRCMDCONTROLS_RefPi_HSH                     (0x8400150C)

  #define DDRCMDNCH1_CR_DDRCRCMDCONTROLS_DllMask_OFF                   ( 4)
  #define DDRCMDNCH1_CR_DDRCRCMDCONTROLS_DllMask_WID                   ( 2)
  #define DDRCMDNCH1_CR_DDRCRCMDCONTROLS_DllMask_MSK                   (0x00000030)
  #define DDRCMDNCH1_CR_DDRCRCMDCONTROLS_DllMask_MIN                   (0)
  #define DDRCMDNCH1_CR_DDRCRCMDCONTROLS_DllMask_MAX                   (3) // 0x00000003
  #define DDRCMDNCH1_CR_DDRCRCMDCONTROLS_DllMask_DEF                   (0x00000000)
  #define DDRCMDNCH1_CR_DDRCRCMDCONTROLS_DllMask_HSH                   (0x0204150C)

  #define DDRCMDNCH1_CR_DDRCRCMDCONTROLS_ClkGateDisable_OFF            ( 6)
  #define DDRCMDNCH1_CR_DDRCRCMDCONTROLS_ClkGateDisable_WID            ( 1)
  #define DDRCMDNCH1_CR_DDRCRCMDCONTROLS_ClkGateDisable_MSK            (0x00000040)
  #define DDRCMDNCH1_CR_DDRCRCMDCONTROLS_ClkGateDisable_MIN            (0)
  #define DDRCMDNCH1_CR_DDRCRCMDCONTROLS_ClkGateDisable_MAX            (1) // 0x00000001
  #define DDRCMDNCH1_CR_DDRCRCMDCONTROLS_ClkGateDisable_DEF            (0x00000000)
  #define DDRCMDNCH1_CR_DDRCRCMDCONTROLS_ClkGateDisable_HSH            (0x0106150C)

  #define DDRCMDNCH1_CR_DDRCRCMDCONTROLS_TxOn_OFF                      ( 7)
  #define DDRCMDNCH1_CR_DDRCRCMDCONTROLS_TxOn_WID                      ( 1)
  #define DDRCMDNCH1_CR_DDRCRCMDCONTROLS_TxOn_MSK                      (0x00000080)
  #define DDRCMDNCH1_CR_DDRCRCMDCONTROLS_TxOn_MIN                      (0)
  #define DDRCMDNCH1_CR_DDRCRCMDCONTROLS_TxOn_MAX                      (1) // 0x00000001
  #define DDRCMDNCH1_CR_DDRCRCMDCONTROLS_TxOn_DEF                      (0x00000000)
  #define DDRCMDNCH1_CR_DDRCRCMDCONTROLS_TxOn_HSH                      (0x0107150C)

  #define DDRCMDNCH1_CR_DDRCRCMDCONTROLS_IntClkOn_OFF                  ( 8)
  #define DDRCMDNCH1_CR_DDRCRCMDCONTROLS_IntClkOn_WID                  ( 1)
  #define DDRCMDNCH1_CR_DDRCRCMDCONTROLS_IntClkOn_MSK                  (0x00000100)
  #define DDRCMDNCH1_CR_DDRCRCMDCONTROLS_IntClkOn_MIN                  (0)
  #define DDRCMDNCH1_CR_DDRCRCMDCONTROLS_IntClkOn_MAX                  (1) // 0x00000001
  #define DDRCMDNCH1_CR_DDRCRCMDCONTROLS_IntClkOn_DEF                  (0x00000000)
  #define DDRCMDNCH1_CR_DDRCRCMDCONTROLS_IntClkOn_HSH                  (0x0108150C)

  #define DDRCMDNCH1_CR_DDRCRCMDCONTROLS_RepClkOn_OFF                  ( 9)
  #define DDRCMDNCH1_CR_DDRCRCMDCONTROLS_RepClkOn_WID                  ( 1)
  #define DDRCMDNCH1_CR_DDRCRCMDCONTROLS_RepClkOn_MSK                  (0x00000200)
  #define DDRCMDNCH1_CR_DDRCRCMDCONTROLS_RepClkOn_MIN                  (0)
  #define DDRCMDNCH1_CR_DDRCRCMDCONTROLS_RepClkOn_MAX                  (1) // 0x00000001
  #define DDRCMDNCH1_CR_DDRCRCMDCONTROLS_RepClkOn_DEF                  (0x00000000)
  #define DDRCMDNCH1_CR_DDRCRCMDCONTROLS_RepClkOn_HSH                  (0x0109150C)

  #define DDRCMDNCH1_CR_DDRCRCMDCONTROLS_IolbOrMisr_OFF                (10)
  #define DDRCMDNCH1_CR_DDRCRCMDCONTROLS_IolbOrMisr_WID                ( 1)
  #define DDRCMDNCH1_CR_DDRCRCMDCONTROLS_IolbOrMisr_MSK                (0x00000400)
  #define DDRCMDNCH1_CR_DDRCRCMDCONTROLS_IolbOrMisr_MIN                (0)
  #define DDRCMDNCH1_CR_DDRCRCMDCONTROLS_IolbOrMisr_MAX                (1) // 0x00000001
  #define DDRCMDNCH1_CR_DDRCRCMDCONTROLS_IolbOrMisr_DEF                (0x00000000)
  #define DDRCMDNCH1_CR_DDRCRCMDCONTROLS_IolbOrMisr_HSH                (0x010A150C)

  #define DDRCMDNCH1_CR_DDRCRCMDCONTROLS_IolbHold_OFF                  (11)
  #define DDRCMDNCH1_CR_DDRCRCMDCONTROLS_IolbHold_WID                  ( 1)
  #define DDRCMDNCH1_CR_DDRCRCMDCONTROLS_IolbHold_MSK                  (0x00000800)
  #define DDRCMDNCH1_CR_DDRCRCMDCONTROLS_IolbHold_MIN                  (0)
  #define DDRCMDNCH1_CR_DDRCRCMDCONTROLS_IolbHold_MAX                  (1) // 0x00000001
  #define DDRCMDNCH1_CR_DDRCRCMDCONTROLS_IolbHold_DEF                  (0x00000000)
  #define DDRCMDNCH1_CR_DDRCRCMDCONTROLS_IolbHold_HSH                  (0x010B150C)

  #define DDRCMDNCH1_CR_DDRCRCMDCONTROLS_OdtMode_OFF                   (12)
  #define DDRCMDNCH1_CR_DDRCRCMDCONTROLS_OdtMode_WID                   ( 1)
  #define DDRCMDNCH1_CR_DDRCRCMDCONTROLS_OdtMode_MSK                   (0x00001000)
  #define DDRCMDNCH1_CR_DDRCRCMDCONTROLS_OdtMode_MIN                   (0)
  #define DDRCMDNCH1_CR_DDRCRCMDCONTROLS_OdtMode_MAX                   (1) // 0x00000001
  #define DDRCMDNCH1_CR_DDRCRCMDCONTROLS_OdtMode_DEF                   (0x00000000)
  #define DDRCMDNCH1_CR_DDRCRCMDCONTROLS_OdtMode_HSH                   (0x010C150C)

  #define DDRCMDNCH1_CR_DDRCRCMDCONTROLS_CmdTxEq_OFF                   (13)
  #define DDRCMDNCH1_CR_DDRCRCMDCONTROLS_CmdTxEq_WID                   ( 2)
  #define DDRCMDNCH1_CR_DDRCRCMDCONTROLS_CmdTxEq_MSK                   (0x00006000)
  #define DDRCMDNCH1_CR_DDRCRCMDCONTROLS_CmdTxEq_MIN                   (0)
  #define DDRCMDNCH1_CR_DDRCRCMDCONTROLS_CmdTxEq_MAX                   (3) // 0x00000003
  #define DDRCMDNCH1_CR_DDRCRCMDCONTROLS_CmdTxEq_DEF                   (0x00000000)
  #define DDRCMDNCH1_CR_DDRCRCMDCONTROLS_CmdTxEq_HSH                   (0x020D150C)

  #define DDRCMDNCH1_CR_DDRCRCMDCONTROLS_EarlyWeakDrive_OFF            (15)
  #define DDRCMDNCH1_CR_DDRCRCMDCONTROLS_EarlyWeakDrive_WID            ( 2)
  #define DDRCMDNCH1_CR_DDRCRCMDCONTROLS_EarlyWeakDrive_MSK            (0x00018000)
  #define DDRCMDNCH1_CR_DDRCRCMDCONTROLS_EarlyWeakDrive_MIN            (0)
  #define DDRCMDNCH1_CR_DDRCRCMDCONTROLS_EarlyWeakDrive_MAX            (3) // 0x00000003
  #define DDRCMDNCH1_CR_DDRCRCMDCONTROLS_EarlyWeakDrive_DEF            (0x00000000)
  #define DDRCMDNCH1_CR_DDRCRCMDCONTROLS_EarlyWeakDrive_HSH            (0x020F150C)

  #define DDRCMDNCH1_CR_DDRCRCMDCONTROLS_PrtEn_OFF                     (17)
  #define DDRCMDNCH1_CR_DDRCRCMDCONTROLS_PrtEn_WID                     ( 1)
  #define DDRCMDNCH1_CR_DDRCRCMDCONTROLS_PrtEn_MSK                     (0x00020000)
  #define DDRCMDNCH1_CR_DDRCRCMDCONTROLS_PrtEn_MIN                     (0)
  #define DDRCMDNCH1_CR_DDRCRCMDCONTROLS_PrtEn_MAX                     (1) // 0x00000001
  #define DDRCMDNCH1_CR_DDRCRCMDCONTROLS_PrtEn_DEF                     (0x00000000)
  #define DDRCMDNCH1_CR_DDRCRCMDCONTROLS_PrtEn_HSH                     (0x0111150C)

  #define DDRCMDNCH1_CR_DDRCRCMDCONTROLS_AlrtEn_OFF                    (18)
  #define DDRCMDNCH1_CR_DDRCRCMDCONTROLS_AlrtEn_WID                    ( 1)
  #define DDRCMDNCH1_CR_DDRCRCMDCONTROLS_AlrtEn_MSK                    (0x00040000)
  #define DDRCMDNCH1_CR_DDRCRCMDCONTROLS_AlrtEn_MIN                    (0)
  #define DDRCMDNCH1_CR_DDRCRCMDCONTROLS_AlrtEn_MAX                    (1) // 0x00000001
  #define DDRCMDNCH1_CR_DDRCRCMDCONTROLS_AlrtEn_DEF                    (0x00000000)
  #define DDRCMDNCH1_CR_DDRCRCMDCONTROLS_AlrtEn_HSH                    (0x0112150C)

  #define DDRCMDNCH1_CR_DDRCRCMDCONTROLS_LaDrvEnOvrd_OFF               (19)
  #define DDRCMDNCH1_CR_DDRCRCMDCONTROLS_LaDrvEnOvrd_WID               ( 1)
  #define DDRCMDNCH1_CR_DDRCRCMDCONTROLS_LaDrvEnOvrd_MSK               (0x00080000)
  #define DDRCMDNCH1_CR_DDRCRCMDCONTROLS_LaDrvEnOvrd_MIN               (0)
  #define DDRCMDNCH1_CR_DDRCRCMDCONTROLS_LaDrvEnOvrd_MAX               (1) // 0x00000001
  #define DDRCMDNCH1_CR_DDRCRCMDCONTROLS_LaDrvEnOvrd_DEF               (0x00000000)
  #define DDRCMDNCH1_CR_DDRCRCMDCONTROLS_LaDrvEnOvrd_HSH               (0x0113150C)

  #define DDRCMDNCH1_CR_DDRCRCMDCONTROLS_DdrCmdSlwDlyByp_OFF           (20)
  #define DDRCMDNCH1_CR_DDRCRCMDCONTROLS_DdrCmdSlwDlyByp_WID           ( 1)
  #define DDRCMDNCH1_CR_DDRCRCMDCONTROLS_DdrCmdSlwDlyByp_MSK           (0x00100000)
  #define DDRCMDNCH1_CR_DDRCRCMDCONTROLS_DdrCmdSlwDlyByp_MIN           (0)
  #define DDRCMDNCH1_CR_DDRCRCMDCONTROLS_DdrCmdSlwDlyByp_MAX           (1) // 0x00000001
  #define DDRCMDNCH1_CR_DDRCRCMDCONTROLS_DdrCmdSlwDlyByp_DEF           (0x00000000)
  #define DDRCMDNCH1_CR_DDRCRCMDCONTROLS_DdrCmdSlwDlyByp_HSH           (0x0114150C)

  #define DDRCMDNCH1_CR_DDRCRCMDCONTROLS_RxVref_OFF                    (21)
  #define DDRCMDNCH1_CR_DDRCRCMDCONTROLS_RxVref_WID                    ( 6)
  #define DDRCMDNCH1_CR_DDRCRCMDCONTROLS_RxVref_MSK                    (0x07E00000)
  #define DDRCMDNCH1_CR_DDRCRCMDCONTROLS_RxVref_MIN                    (-32)
  #define DDRCMDNCH1_CR_DDRCRCMDCONTROLS_RxVref_MAX                    (31) // 0x0000001F
  #define DDRCMDNCH1_CR_DDRCRCMDCONTROLS_RxVref_DEF                    (0x00000000)
  #define DDRCMDNCH1_CR_DDRCRCMDCONTROLS_RxVref_HSH                    (0x8615150C)

  #define DDRCMDNCH1_CR_DDRCRCMDCONTROLS_VccddqHi_OFF                  (27)
  #define DDRCMDNCH1_CR_DDRCRCMDCONTROLS_VccddqHi_WID                  ( 1)
  #define DDRCMDNCH1_CR_DDRCRCMDCONTROLS_VccddqHi_MSK                  (0x08000000)
  #define DDRCMDNCH1_CR_DDRCRCMDCONTROLS_VccddqHi_MIN                  (0)
  #define DDRCMDNCH1_CR_DDRCRCMDCONTROLS_VccddqHi_MAX                  (1) // 0x00000001
  #define DDRCMDNCH1_CR_DDRCRCMDCONTROLS_VccddqHi_DEF                  (0x00000000)
  #define DDRCMDNCH1_CR_DDRCRCMDCONTROLS_VccddqHi_HSH                  (0x011B150C)

  #define DDRCMDNCH1_CR_DDRCRCMDCONTROLS_DllWeakLock_OFF               (28)
  #define DDRCMDNCH1_CR_DDRCRCMDCONTROLS_DllWeakLock_WID               ( 1)
  #define DDRCMDNCH1_CR_DDRCRCMDCONTROLS_DllWeakLock_MSK               (0x10000000)
  #define DDRCMDNCH1_CR_DDRCRCMDCONTROLS_DllWeakLock_MIN               (0)
  #define DDRCMDNCH1_CR_DDRCRCMDCONTROLS_DllWeakLock_MAX               (1) // 0x00000001
  #define DDRCMDNCH1_CR_DDRCRCMDCONTROLS_DllWeakLock_DEF               (0x00000000)
  #define DDRCMDNCH1_CR_DDRCRCMDCONTROLS_DllWeakLock_HSH               (0x011C150C)

  #define DDRCMDNCH1_CR_DDRCRCMDCONTROLS_LPDDR_Mode_OFF                (29)
  #define DDRCMDNCH1_CR_DDRCRCMDCONTROLS_LPDDR_Mode_WID                ( 1)
  #define DDRCMDNCH1_CR_DDRCRCMDCONTROLS_LPDDR_Mode_MSK                (0x20000000)
  #define DDRCMDNCH1_CR_DDRCRCMDCONTROLS_LPDDR_Mode_MIN                (0)
  #define DDRCMDNCH1_CR_DDRCRCMDCONTROLS_LPDDR_Mode_MAX                (1) // 0x00000001
  #define DDRCMDNCH1_CR_DDRCRCMDCONTROLS_LPDDR_Mode_DEF                (0x00000000)
  #define DDRCMDNCH1_CR_DDRCRCMDCONTROLS_LPDDR_Mode_HSH                (0x011D150C)

  #define DDRCMDNCH1_CR_DDRCRCMDCONTROLS_LPDdrCAA_Dis_OFF              (30)
  #define DDRCMDNCH1_CR_DDRCRCMDCONTROLS_LPDdrCAA_Dis_WID              ( 1)
  #define DDRCMDNCH1_CR_DDRCRCMDCONTROLS_LPDdrCAA_Dis_MSK              (0x40000000)
  #define DDRCMDNCH1_CR_DDRCRCMDCONTROLS_LPDdrCAA_Dis_MIN              (0)
  #define DDRCMDNCH1_CR_DDRCRCMDCONTROLS_LPDdrCAA_Dis_MAX              (1) // 0x00000001
  #define DDRCMDNCH1_CR_DDRCRCMDCONTROLS_LPDdrCAA_Dis_DEF              (0x00000000)
  #define DDRCMDNCH1_CR_DDRCRCMDCONTROLS_LPDdrCAA_Dis_HSH              (0x011E150C)

  #define DDRCMDNCH1_CR_DDRCRCMDCONTROLS_LPDdrCAB_Dis_OFF              (31)
  #define DDRCMDNCH1_CR_DDRCRCMDCONTROLS_LPDdrCAB_Dis_WID              ( 1)
  #define DDRCMDNCH1_CR_DDRCRCMDCONTROLS_LPDdrCAB_Dis_MSK              (0x80000000)
  #define DDRCMDNCH1_CR_DDRCRCMDCONTROLS_LPDdrCAB_Dis_MIN              (0)
  #define DDRCMDNCH1_CR_DDRCRCMDCONTROLS_LPDdrCAB_Dis_MAX              (1) // 0x00000001
  #define DDRCMDNCH1_CR_DDRCRCMDCONTROLS_LPDdrCAB_Dis_DEF              (0x00000000)
  #define DDRCMDNCH1_CR_DDRCRCMDCONTROLS_LPDdrCAB_Dis_HSH              (0x011F150C)

#define DDRCMDNCH1_CR_DLLPITESTANDADC_REG                              (0x00001524)

  #define DDRCMDNCH1_CR_DLLPITESTANDADC_RunTest_OFF                    ( 0)
  #define DDRCMDNCH1_CR_DLLPITESTANDADC_RunTest_WID                    ( 1)
  #define DDRCMDNCH1_CR_DLLPITESTANDADC_RunTest_MSK                    (0x00000001)
  #define DDRCMDNCH1_CR_DLLPITESTANDADC_RunTest_MIN                    (0)
  #define DDRCMDNCH1_CR_DLLPITESTANDADC_RunTest_MAX                    (1) // 0x00000001
  #define DDRCMDNCH1_CR_DLLPITESTANDADC_RunTest_DEF                    (0x00000000)
  #define DDRCMDNCH1_CR_DLLPITESTANDADC_RunTest_HSH                    (0x01001524)

  #define DDRCMDNCH1_CR_DLLPITESTANDADC_Load_OFF                       ( 1)
  #define DDRCMDNCH1_CR_DLLPITESTANDADC_Load_WID                       ( 1)
  #define DDRCMDNCH1_CR_DLLPITESTANDADC_Load_MSK                       (0x00000002)
  #define DDRCMDNCH1_CR_DLLPITESTANDADC_Load_MIN                       (0)
  #define DDRCMDNCH1_CR_DLLPITESTANDADC_Load_MAX                       (1) // 0x00000001
  #define DDRCMDNCH1_CR_DLLPITESTANDADC_Load_DEF                       (0x00000000)
  #define DDRCMDNCH1_CR_DLLPITESTANDADC_Load_HSH                       (0x01011524)

  #define DDRCMDNCH1_CR_DLLPITESTANDADC_ModeHVM_OFF                    ( 2)
  #define DDRCMDNCH1_CR_DLLPITESTANDADC_ModeHVM_WID                    ( 1)
  #define DDRCMDNCH1_CR_DLLPITESTANDADC_ModeHVM_MSK                    (0x00000004)
  #define DDRCMDNCH1_CR_DLLPITESTANDADC_ModeHVM_MIN                    (0)
  #define DDRCMDNCH1_CR_DLLPITESTANDADC_ModeHVM_MAX                    (1) // 0x00000001
  #define DDRCMDNCH1_CR_DLLPITESTANDADC_ModeHVM_DEF                    (0x00000000)
  #define DDRCMDNCH1_CR_DLLPITESTANDADC_ModeHVM_HSH                    (0x01021524)

  #define DDRCMDNCH1_CR_DLLPITESTANDADC_ModeDV_OFF                     ( 3)
  #define DDRCMDNCH1_CR_DLLPITESTANDADC_ModeDV_WID                     ( 1)
  #define DDRCMDNCH1_CR_DLLPITESTANDADC_ModeDV_MSK                     (0x00000008)
  #define DDRCMDNCH1_CR_DLLPITESTANDADC_ModeDV_MIN                     (0)
  #define DDRCMDNCH1_CR_DLLPITESTANDADC_ModeDV_MAX                     (1) // 0x00000001
  #define DDRCMDNCH1_CR_DLLPITESTANDADC_ModeDV_DEF                     (0x00000000)
  #define DDRCMDNCH1_CR_DLLPITESTANDADC_ModeDV_HSH                     (0x01031524)

  #define DDRCMDNCH1_CR_DLLPITESTANDADC_CalCfdl_OFF                    ( 4)
  #define DDRCMDNCH1_CR_DLLPITESTANDADC_CalCfdl_WID                    ( 1)
  #define DDRCMDNCH1_CR_DLLPITESTANDADC_CalCfdl_MSK                    (0x00000010)
  #define DDRCMDNCH1_CR_DLLPITESTANDADC_CalCfdl_MIN                    (0)
  #define DDRCMDNCH1_CR_DLLPITESTANDADC_CalCfdl_MAX                    (1) // 0x00000001
  #define DDRCMDNCH1_CR_DLLPITESTANDADC_CalCfdl_DEF                    (0x00000000)
  #define DDRCMDNCH1_CR_DLLPITESTANDADC_CalCfdl_HSH                    (0x01041524)

  #define DDRCMDNCH1_CR_DLLPITESTANDADC_LoadCount_OFF                  ( 5)
  #define DDRCMDNCH1_CR_DLLPITESTANDADC_LoadCount_WID                  (10)
  #define DDRCMDNCH1_CR_DLLPITESTANDADC_LoadCount_MSK                  (0x00007FE0)
  #define DDRCMDNCH1_CR_DLLPITESTANDADC_LoadCount_MIN                  (0)
  #define DDRCMDNCH1_CR_DLLPITESTANDADC_LoadCount_MAX                  (1023) // 0x000003FF
  #define DDRCMDNCH1_CR_DLLPITESTANDADC_LoadCount_DEF                  (0x00000000)
  #define DDRCMDNCH1_CR_DLLPITESTANDADC_LoadCount_HSH                  (0x0A051524)

  #define DDRCMDNCH1_CR_DLLPITESTANDADC_CountStatus_OFF                (15)
  #define DDRCMDNCH1_CR_DLLPITESTANDADC_CountStatus_WID                (10)
  #define DDRCMDNCH1_CR_DLLPITESTANDADC_CountStatus_MSK                (0x01FF8000)
  #define DDRCMDNCH1_CR_DLLPITESTANDADC_CountStatus_MIN                (0)
  #define DDRCMDNCH1_CR_DLLPITESTANDADC_CountStatus_MAX                (1023) // 0x000003FF
  #define DDRCMDNCH1_CR_DLLPITESTANDADC_CountStatus_DEF                (0x00000000)
  #define DDRCMDNCH1_CR_DLLPITESTANDADC_CountStatus_HSH                (0x0A0F1524)

  #define DDRCMDNCH1_CR_DLLPITESTANDADC_PhaseDrvPwrSavOn_OFF           (25)
  #define DDRCMDNCH1_CR_DLLPITESTANDADC_PhaseDrvPwrSavOn_WID           ( 1)
  #define DDRCMDNCH1_CR_DLLPITESTANDADC_PhaseDrvPwrSavOn_MSK           (0x02000000)
  #define DDRCMDNCH1_CR_DLLPITESTANDADC_PhaseDrvPwrSavOn_MIN           (0)
  #define DDRCMDNCH1_CR_DLLPITESTANDADC_PhaseDrvPwrSavOn_MAX           (1) // 0x00000001
  #define DDRCMDNCH1_CR_DLLPITESTANDADC_PhaseDrvPwrSavOn_DEF           (0x00000000)
  #define DDRCMDNCH1_CR_DLLPITESTANDADC_PhaseDrvPwrSavOn_HSH           (0x01191524)

  #define DDRCMDNCH1_CR_DLLPITESTANDADC_Spare_OFF                      (26)
  #define DDRCMDNCH1_CR_DLLPITESTANDADC_Spare_WID                      ( 6)
  #define DDRCMDNCH1_CR_DLLPITESTANDADC_Spare_MSK                      (0xFC000000)
  #define DDRCMDNCH1_CR_DLLPITESTANDADC_Spare_MIN                      (0)
  #define DDRCMDNCH1_CR_DLLPITESTANDADC_Spare_MAX                      (63) // 0x0000003F
  #define DDRCMDNCH1_CR_DLLPITESTANDADC_Spare_DEF                      (0x00000000)
  #define DDRCMDNCH1_CR_DLLPITESTANDADC_Spare_HSH                      (0x061A1524)

#define DDRCLKCH0_CR_DDRCRCLKRANKSUSED_REG                             (0x00001800)

  #define DDRCLKCH0_CR_DDRCRCLKRANKSUSED_RankEn_OFF                    ( 0)
  #define DDRCLKCH0_CR_DDRCRCLKRANKSUSED_RankEn_WID                    ( 4)
  #define DDRCLKCH0_CR_DDRCRCLKRANKSUSED_RankEn_MSK                    (0x0000000F)
  #define DDRCLKCH0_CR_DDRCRCLKRANKSUSED_RankEn_MIN                    (0)
  #define DDRCLKCH0_CR_DDRCRCLKRANKSUSED_RankEn_MAX                    (15) // 0x0000000F
  #define DDRCLKCH0_CR_DDRCRCLKRANKSUSED_RankEn_DEF                    (0x0000000F)
  #define DDRCLKCH0_CR_DDRCRCLKRANKSUSED_RankEn_HSH                    (0x04001800)

  #define DDRCLKCH0_CR_DDRCRCLKRANKSUSED_Spare_OFF                     ( 4)
  #define DDRCLKCH0_CR_DDRCRCLKRANKSUSED_Spare_WID                     (28)
  #define DDRCLKCH0_CR_DDRCRCLKRANKSUSED_Spare_MSK                     (0xFFFFFFF0)
  #define DDRCLKCH0_CR_DDRCRCLKRANKSUSED_Spare_MIN                     (0)
  #define DDRCLKCH0_CR_DDRCRCLKRANKSUSED_Spare_MAX                     (268435455) // 0x0FFFFFFF
  #define DDRCLKCH0_CR_DDRCRCLKRANKSUSED_Spare_DEF                     (0x00000000)
  #define DDRCLKCH0_CR_DDRCRCLKRANKSUSED_Spare_HSH                     (0x1C041800)

#define DDRCLKCH0_CR_DDRCRCLKCOMP_REG                                  (0x00001804)

  #define DDRCLKCH0_CR_DDRCRCLKCOMP_Scomp_OFF                          ( 0)
  #define DDRCLKCH0_CR_DDRCRCLKCOMP_Scomp_WID                          ( 5)
  #define DDRCLKCH0_CR_DDRCRCLKCOMP_Scomp_MSK                          (0x0000001F)
  #define DDRCLKCH0_CR_DDRCRCLKCOMP_Scomp_MIN                          (0)
  #define DDRCLKCH0_CR_DDRCRCLKCOMP_Scomp_MAX                          (31) // 0x0000001F
  #define DDRCLKCH0_CR_DDRCRCLKCOMP_Scomp_DEF                          (0x00000000)
  #define DDRCLKCH0_CR_DDRCRCLKCOMP_Scomp_HSH                          (0x05001804)

  #define DDRCLKCH0_CR_DDRCRCLKCOMP_TcoComp_OFF                        ( 5)
  #define DDRCLKCH0_CR_DDRCRCLKCOMP_TcoComp_WID                        ( 6)
  #define DDRCLKCH0_CR_DDRCRCLKCOMP_TcoComp_MSK                        (0x000007E0)
  #define DDRCLKCH0_CR_DDRCRCLKCOMP_TcoComp_MIN                        (0)
  #define DDRCLKCH0_CR_DDRCRCLKCOMP_TcoComp_MAX                        (63) // 0x0000003F
  #define DDRCLKCH0_CR_DDRCRCLKCOMP_TcoComp_DEF                        (0x00000000)
  #define DDRCLKCH0_CR_DDRCRCLKCOMP_TcoComp_HSH                        (0x06051804)

  #define DDRCLKCH0_CR_DDRCRCLKCOMP_RcompDrvUp_OFF                     (11)
  #define DDRCLKCH0_CR_DDRCRCLKCOMP_RcompDrvUp_WID                     ( 6)
  #define DDRCLKCH0_CR_DDRCRCLKCOMP_RcompDrvUp_MSK                     (0x0001F800)
  #define DDRCLKCH0_CR_DDRCRCLKCOMP_RcompDrvUp_MIN                     (0)
  #define DDRCLKCH0_CR_DDRCRCLKCOMP_RcompDrvUp_MAX                     (63) // 0x0000003F
  #define DDRCLKCH0_CR_DDRCRCLKCOMP_RcompDrvUp_DEF                     (0x00000000)
  #define DDRCLKCH0_CR_DDRCRCLKCOMP_RcompDrvUp_HSH                     (0x060B1804)

  #define DDRCLKCH0_CR_DDRCRCLKCOMP_RcompDrvDown_OFF                   (17)
  #define DDRCLKCH0_CR_DDRCRCLKCOMP_RcompDrvDown_WID                   ( 6)
  #define DDRCLKCH0_CR_DDRCRCLKCOMP_RcompDrvDown_MSK                   (0x007E0000)
  #define DDRCLKCH0_CR_DDRCRCLKCOMP_RcompDrvDown_MIN                   (0)
  #define DDRCLKCH0_CR_DDRCRCLKCOMP_RcompDrvDown_MAX                   (63) // 0x0000003F
  #define DDRCLKCH0_CR_DDRCRCLKCOMP_RcompDrvDown_DEF                   (0x00000000)
  #define DDRCLKCH0_CR_DDRCRCLKCOMP_RcompDrvDown_HSH                   (0x06111804)

  #define DDRCLKCH0_CR_DDRCRCLKCOMP_Spare_OFF                          (23)
  #define DDRCLKCH0_CR_DDRCRCLKCOMP_Spare_WID                          ( 9)
  #define DDRCLKCH0_CR_DDRCRCLKCOMP_Spare_MSK                          (0xFF800000)
  #define DDRCLKCH0_CR_DDRCRCLKCOMP_Spare_MIN                          (0)
  #define DDRCLKCH0_CR_DDRCRCLKCOMP_Spare_MAX                          (511) // 0x000001FF
  #define DDRCLKCH0_CR_DDRCRCLKCOMP_Spare_DEF                          (0x00000003)
  #define DDRCLKCH0_CR_DDRCRCLKCOMP_Spare_HSH                          (0x09171804)

#define DDRCLKCH0_CR_DDRCRCLKCOMPOFFSET_REG                            (0x00001808)

  #define DDRCLKCH0_CR_DDRCRCLKCOMPOFFSET_ScompOffset_OFF              ( 0)
  #define DDRCLKCH0_CR_DDRCRCLKCOMPOFFSET_ScompOffset_WID              ( 4)
  #define DDRCLKCH0_CR_DDRCRCLKCOMPOFFSET_ScompOffset_MSK              (0x0000000F)
  #define DDRCLKCH0_CR_DDRCRCLKCOMPOFFSET_ScompOffset_MIN              (-8)
  #define DDRCLKCH0_CR_DDRCRCLKCOMPOFFSET_ScompOffset_MAX              (7) // 0x00000007
  #define DDRCLKCH0_CR_DDRCRCLKCOMPOFFSET_ScompOffset_DEF              (0x00000000)
  #define DDRCLKCH0_CR_DDRCRCLKCOMPOFFSET_ScompOffset_HSH              (0x84001808)

  #define DDRCLKCH0_CR_DDRCRCLKCOMPOFFSET_TcoCompOffset_OFF            ( 4)
  #define DDRCLKCH0_CR_DDRCRCLKCOMPOFFSET_TcoCompOffset_WID            ( 4)
  #define DDRCLKCH0_CR_DDRCRCLKCOMPOFFSET_TcoCompOffset_MSK            (0x000000F0)
  #define DDRCLKCH0_CR_DDRCRCLKCOMPOFFSET_TcoCompOffset_MIN            (-8)
  #define DDRCLKCH0_CR_DDRCRCLKCOMPOFFSET_TcoCompOffset_MAX            (7) // 0x00000007
  #define DDRCLKCH0_CR_DDRCRCLKCOMPOFFSET_TcoCompOffset_DEF            (0x00000000)
  #define DDRCLKCH0_CR_DDRCRCLKCOMPOFFSET_TcoCompOffset_HSH            (0x84041808)

  #define DDRCLKCH0_CR_DDRCRCLKCOMPOFFSET_RcompDrvUpOffset_OFF         ( 8)
  #define DDRCLKCH0_CR_DDRCRCLKCOMPOFFSET_RcompDrvUpOffset_WID         ( 4)
  #define DDRCLKCH0_CR_DDRCRCLKCOMPOFFSET_RcompDrvUpOffset_MSK         (0x00000F00)
  #define DDRCLKCH0_CR_DDRCRCLKCOMPOFFSET_RcompDrvUpOffset_MIN         (-8)
  #define DDRCLKCH0_CR_DDRCRCLKCOMPOFFSET_RcompDrvUpOffset_MAX         (7) // 0x00000007
  #define DDRCLKCH0_CR_DDRCRCLKCOMPOFFSET_RcompDrvUpOffset_DEF         (0x00000000)
  #define DDRCLKCH0_CR_DDRCRCLKCOMPOFFSET_RcompDrvUpOffset_HSH         (0x84081808)

  #define DDRCLKCH0_CR_DDRCRCLKCOMPOFFSET_RcompDrvDownOffset_OFF       (12)
  #define DDRCLKCH0_CR_DDRCRCLKCOMPOFFSET_RcompDrvDownOffset_WID       ( 4)
  #define DDRCLKCH0_CR_DDRCRCLKCOMPOFFSET_RcompDrvDownOffset_MSK       (0x0000F000)
  #define DDRCLKCH0_CR_DDRCRCLKCOMPOFFSET_RcompDrvDownOffset_MIN       (-8)
  #define DDRCLKCH0_CR_DDRCRCLKCOMPOFFSET_RcompDrvDownOffset_MAX       (7) // 0x00000007
  #define DDRCLKCH0_CR_DDRCRCLKCOMPOFFSET_RcompDrvDownOffset_DEF       (0x00000000)
  #define DDRCLKCH0_CR_DDRCRCLKCOMPOFFSET_RcompDrvDownOffset_HSH       (0x840C1808)

  #define DDRCLKCH0_CR_DDRCRCLKCOMPOFFSET_Spare_OFF                    (16)
  #define DDRCLKCH0_CR_DDRCRCLKCOMPOFFSET_Spare_WID                    (16)
  #define DDRCLKCH0_CR_DDRCRCLKCOMPOFFSET_Spare_MSK                    (0xFFFF0000)
  #define DDRCLKCH0_CR_DDRCRCLKCOMPOFFSET_Spare_MIN                    (0)
  #define DDRCLKCH0_CR_DDRCRCLKCOMPOFFSET_Spare_MAX                    (65535) // 0x0000FFFF
  #define DDRCLKCH0_CR_DDRCRCLKCOMPOFFSET_Spare_DEF                    (0x00000000)
  #define DDRCLKCH0_CR_DDRCRCLKCOMPOFFSET_Spare_HSH                    (0x10101808)

#define DDRCLKCH0_CR_DDRCRCLKPICODE_REG                                (0x0000180C)

  #define DDRCLKCH0_CR_DDRCRCLKPICODE_PiSettingRank0_OFF               ( 0)
  #define DDRCLKCH0_CR_DDRCRCLKPICODE_PiSettingRank0_WID               ( 7)
  #define DDRCLKCH0_CR_DDRCRCLKPICODE_PiSettingRank0_MSK               (0x0000007F)
  #define DDRCLKCH0_CR_DDRCRCLKPICODE_PiSettingRank0_MIN               (0)
  #define DDRCLKCH0_CR_DDRCRCLKPICODE_PiSettingRank0_MAX               (127) // 0x0000007F
  #define DDRCLKCH0_CR_DDRCRCLKPICODE_PiSettingRank0_DEF               (0x00000000)
  #define DDRCLKCH0_CR_DDRCRCLKPICODE_PiSettingRank0_HSH               (0x0700180C)

  #define DDRCLKCH0_CR_DDRCRCLKPICODE_PiSettingRank1_OFF               ( 7)
  #define DDRCLKCH0_CR_DDRCRCLKPICODE_PiSettingRank1_WID               ( 7)
  #define DDRCLKCH0_CR_DDRCRCLKPICODE_PiSettingRank1_MSK               (0x00003F80)
  #define DDRCLKCH0_CR_DDRCRCLKPICODE_PiSettingRank1_MIN               (0)
  #define DDRCLKCH0_CR_DDRCRCLKPICODE_PiSettingRank1_MAX               (127) // 0x0000007F
  #define DDRCLKCH0_CR_DDRCRCLKPICODE_PiSettingRank1_DEF               (0x00000000)
  #define DDRCLKCH0_CR_DDRCRCLKPICODE_PiSettingRank1_HSH               (0x0707180C)

  #define DDRCLKCH0_CR_DDRCRCLKPICODE_PiSettingRank2_OFF               (14)
  #define DDRCLKCH0_CR_DDRCRCLKPICODE_PiSettingRank2_WID               ( 7)
  #define DDRCLKCH0_CR_DDRCRCLKPICODE_PiSettingRank2_MSK               (0x001FC000)
  #define DDRCLKCH0_CR_DDRCRCLKPICODE_PiSettingRank2_MIN               (0)
  #define DDRCLKCH0_CR_DDRCRCLKPICODE_PiSettingRank2_MAX               (127) // 0x0000007F
  #define DDRCLKCH0_CR_DDRCRCLKPICODE_PiSettingRank2_DEF               (0x00000000)
  #define DDRCLKCH0_CR_DDRCRCLKPICODE_PiSettingRank2_HSH               (0x070E180C)

  #define DDRCLKCH0_CR_DDRCRCLKPICODE_PiSettingRank3_OFF               (21)
  #define DDRCLKCH0_CR_DDRCRCLKPICODE_PiSettingRank3_WID               ( 7)
  #define DDRCLKCH0_CR_DDRCRCLKPICODE_PiSettingRank3_MSK               (0x0FE00000)
  #define DDRCLKCH0_CR_DDRCRCLKPICODE_PiSettingRank3_MIN               (0)
  #define DDRCLKCH0_CR_DDRCRCLKPICODE_PiSettingRank3_MAX               (127) // 0x0000007F
  #define DDRCLKCH0_CR_DDRCRCLKPICODE_PiSettingRank3_DEF               (0x00000000)
  #define DDRCLKCH0_CR_DDRCRCLKPICODE_PiSettingRank3_HSH               (0x0715180C)

  #define DDRCLKCH0_CR_DDRCRCLKPICODE_Spare_OFF                        (28)
  #define DDRCLKCH0_CR_DDRCRCLKPICODE_Spare_WID                        ( 4)
  #define DDRCLKCH0_CR_DDRCRCLKPICODE_Spare_MSK                        (0xF0000000)
  #define DDRCLKCH0_CR_DDRCRCLKPICODE_Spare_MIN                        (0)
  #define DDRCLKCH0_CR_DDRCRCLKPICODE_Spare_MAX                        (15) // 0x0000000F
  #define DDRCLKCH0_CR_DDRCRCLKPICODE_Spare_DEF                        (0x00000000)
  #define DDRCLKCH0_CR_DDRCRCLKPICODE_Spare_HSH                        (0x041C180C)

#define DDRCLKCH0_CR_DDRCRCLKCONTROLS_REG                              (0x00001810)

  #define DDRCLKCH0_CR_DDRCRCLKCONTROLS_RefPi_OFF                      ( 0)
  #define DDRCLKCH0_CR_DDRCRCLKCONTROLS_RefPi_WID                      ( 4)
  #define DDRCLKCH0_CR_DDRCRCLKCONTROLS_RefPi_MSK                      (0x0000000F)
  #define DDRCLKCH0_CR_DDRCRCLKCONTROLS_RefPi_MIN                      (-8)
  #define DDRCLKCH0_CR_DDRCRCLKCONTROLS_RefPi_MAX                      (7) // 0x00000007
  #define DDRCLKCH0_CR_DDRCRCLKCONTROLS_RefPi_DEF                      (0x00000000)
  #define DDRCLKCH0_CR_DDRCRCLKCONTROLS_RefPi_HSH                      (0x84001810)

  #define DDRCLKCH0_CR_DDRCRCLKCONTROLS_DllMask_OFF                    ( 4)
  #define DDRCLKCH0_CR_DDRCRCLKCONTROLS_DllMask_WID                    ( 2)
  #define DDRCLKCH0_CR_DDRCRCLKCONTROLS_DllMask_MSK                    (0x00000030)
  #define DDRCLKCH0_CR_DDRCRCLKCONTROLS_DllMask_MIN                    (0)
  #define DDRCLKCH0_CR_DDRCRCLKCONTROLS_DllMask_MAX                    (3) // 0x00000003
  #define DDRCLKCH0_CR_DDRCRCLKCONTROLS_DllMask_DEF                    (0x00000000)
  #define DDRCLKCH0_CR_DDRCRCLKCONTROLS_DllMask_HSH                    (0x02041810)

  #define DDRCLKCH0_CR_DDRCRCLKCONTROLS_DllRsvd1_OFF                   ( 6)
  #define DDRCLKCH0_CR_DDRCRCLKCONTROLS_DllRsvd1_WID                   ( 1)
  #define DDRCLKCH0_CR_DDRCRCLKCONTROLS_DllRsvd1_MSK                   (0x00000040)
  #define DDRCLKCH0_CR_DDRCRCLKCONTROLS_DllRsvd1_MIN                   (0)
  #define DDRCLKCH0_CR_DDRCRCLKCONTROLS_DllRsvd1_MAX                   (1) // 0x00000001
  #define DDRCLKCH0_CR_DDRCRCLKCONTROLS_DllRsvd1_DEF                   (0x00000000)
  #define DDRCLKCH0_CR_DDRCRCLKCONTROLS_DllRsvd1_HSH                   (0x01061810)

  #define DDRCLKCH0_CR_DDRCRCLKCONTROLS_TxOn_OFF                       ( 7)
  #define DDRCLKCH0_CR_DDRCRCLKCONTROLS_TxOn_WID                       ( 1)
  #define DDRCLKCH0_CR_DDRCRCLKCONTROLS_TxOn_MSK                       (0x00000080)
  #define DDRCLKCH0_CR_DDRCRCLKCONTROLS_TxOn_MIN                       (0)
  #define DDRCLKCH0_CR_DDRCRCLKCONTROLS_TxOn_MAX                       (1) // 0x00000001
  #define DDRCLKCH0_CR_DDRCRCLKCONTROLS_TxOn_DEF                       (0x00000000)
  #define DDRCLKCH0_CR_DDRCRCLKCONTROLS_TxOn_HSH                       (0x01071810)

  #define DDRCLKCH0_CR_DDRCRCLKCONTROLS_IntClkOn_OFF                   ( 8)
  #define DDRCLKCH0_CR_DDRCRCLKCONTROLS_IntClkOn_WID                   ( 1)
  #define DDRCLKCH0_CR_DDRCRCLKCONTROLS_IntClkOn_MSK                   (0x00000100)
  #define DDRCLKCH0_CR_DDRCRCLKCONTROLS_IntClkOn_MIN                   (0)
  #define DDRCLKCH0_CR_DDRCRCLKCONTROLS_IntClkOn_MAX                   (1) // 0x00000001
  #define DDRCLKCH0_CR_DDRCRCLKCONTROLS_IntClkOn_DEF                   (0x00000000)
  #define DDRCLKCH0_CR_DDRCRCLKCONTROLS_IntClkOn_HSH                   (0x01081810)

  #define DDRCLKCH0_CR_DDRCRCLKCONTROLS_RepClkOn_OFF                   ( 9)
  #define DDRCLKCH0_CR_DDRCRCLKCONTROLS_RepClkOn_WID                   ( 1)
  #define DDRCLKCH0_CR_DDRCRCLKCONTROLS_RepClkOn_MSK                   (0x00000200)
  #define DDRCLKCH0_CR_DDRCRCLKCONTROLS_RepClkOn_MIN                   (0)
  #define DDRCLKCH0_CR_DDRCRCLKCONTROLS_RepClkOn_MAX                   (1) // 0x00000001
  #define DDRCLKCH0_CR_DDRCRCLKCONTROLS_RepClkOn_DEF                   (0x00000000)
  #define DDRCLKCH0_CR_DDRCRCLKCONTROLS_RepClkOn_HSH                   (0x01091810)

  #define DDRCLKCH0_CR_DDRCRCLKCONTROLS_IOLBCtl_OFF                    (10)
  #define DDRCLKCH0_CR_DDRCRCLKCONTROLS_IOLBCtl_WID                    ( 2)
  #define DDRCLKCH0_CR_DDRCRCLKCONTROLS_IOLBCtl_MSK                    (0x00000C00)
  #define DDRCLKCH0_CR_DDRCRCLKCONTROLS_IOLBCtl_MIN                    (0)
  #define DDRCLKCH0_CR_DDRCRCLKCONTROLS_IOLBCtl_MAX                    (3) // 0x00000003
  #define DDRCLKCH0_CR_DDRCRCLKCONTROLS_IOLBCtl_DEF                    (0x00000000)
  #define DDRCLKCH0_CR_DDRCRCLKCONTROLS_IOLBCtl_HSH                    (0x020A1810)

  #define DDRCLKCH0_CR_DDRCRCLKCONTROLS_OdtMode_OFF                    (12)
  #define DDRCLKCH0_CR_DDRCRCLKCONTROLS_OdtMode_WID                    ( 1)
  #define DDRCLKCH0_CR_DDRCRCLKCONTROLS_OdtMode_MSK                    (0x00001000)
  #define DDRCLKCH0_CR_DDRCRCLKCONTROLS_OdtMode_MIN                    (0)
  #define DDRCLKCH0_CR_DDRCRCLKCONTROLS_OdtMode_MAX                    (1) // 0x00000001
  #define DDRCLKCH0_CR_DDRCRCLKCONTROLS_OdtMode_DEF                    (0x00000000)
  #define DDRCLKCH0_CR_DDRCRCLKCONTROLS_OdtMode_HSH                    (0x010C1810)

  #define DDRCLKCH0_CR_DDRCRCLKCONTROLS_Reserved_OFF                   (13)
  #define DDRCLKCH0_CR_DDRCRCLKCONTROLS_Reserved_WID                   ( 8)
  #define DDRCLKCH0_CR_DDRCRCLKCONTROLS_Reserved_MSK                   (0x001FE000)
  #define DDRCLKCH0_CR_DDRCRCLKCONTROLS_Reserved_MIN                   (0)
  #define DDRCLKCH0_CR_DDRCRCLKCONTROLS_Reserved_MAX                   (255) // 0x000000FF
  #define DDRCLKCH0_CR_DDRCRCLKCONTROLS_Reserved_DEF                   (0x00000000)
  #define DDRCLKCH0_CR_DDRCRCLKCONTROLS_Reserved_HSH                   (0x080D1810)

  #define DDRCLKCH0_CR_DDRCRCLKCONTROLS_RxVref_OFF                     (21)
  #define DDRCLKCH0_CR_DDRCRCLKCONTROLS_RxVref_WID                     ( 6)
  #define DDRCLKCH0_CR_DDRCRCLKCONTROLS_RxVref_MSK                     (0x07E00000)
  #define DDRCLKCH0_CR_DDRCRCLKCONTROLS_RxVref_MIN                     (-32)
  #define DDRCLKCH0_CR_DDRCRCLKCONTROLS_RxVref_MAX                     (31) // 0x0000001F
  #define DDRCLKCH0_CR_DDRCRCLKCONTROLS_RxVref_DEF                     (0x00000000)
  #define DDRCLKCH0_CR_DDRCRCLKCONTROLS_RxVref_HSH                     (0x86151810)

  #define DDRCLKCH0_CR_DDRCRCLKCONTROLS_VccddqHi_OFF                   (27)
  #define DDRCLKCH0_CR_DDRCRCLKCONTROLS_VccddqHi_WID                   ( 1)
  #define DDRCLKCH0_CR_DDRCRCLKCONTROLS_VccddqHi_MSK                   (0x08000000)
  #define DDRCLKCH0_CR_DDRCRCLKCONTROLS_VccddqHi_MIN                   (0)
  #define DDRCLKCH0_CR_DDRCRCLKCONTROLS_VccddqHi_MAX                   (1) // 0x00000001
  #define DDRCLKCH0_CR_DDRCRCLKCONTROLS_VccddqHi_DEF                   (0x00000000)
  #define DDRCLKCH0_CR_DDRCRCLKCONTROLS_VccddqHi_HSH                   (0x011B1810)

  #define DDRCLKCH0_CR_DDRCRCLKCONTROLS_DllWeakLock_OFF                (28)
  #define DDRCLKCH0_CR_DDRCRCLKCONTROLS_DllWeakLock_WID                ( 1)
  #define DDRCLKCH0_CR_DDRCRCLKCONTROLS_DllWeakLock_MSK                (0x10000000)
  #define DDRCLKCH0_CR_DDRCRCLKCONTROLS_DllWeakLock_MIN                (0)
  #define DDRCLKCH0_CR_DDRCRCLKCONTROLS_DllWeakLock_MAX                (1) // 0x00000001
  #define DDRCLKCH0_CR_DDRCRCLKCONTROLS_DllWeakLock_DEF                (0x00000000)
  #define DDRCLKCH0_CR_DDRCRCLKCONTROLS_DllWeakLock_HSH                (0x011C1810)

  #define DDRCLKCH0_CR_DDRCRCLKCONTROLS_LPDDR_Mode_OFF                 (29)
  #define DDRCLKCH0_CR_DDRCRCLKCONTROLS_LPDDR_Mode_WID                 ( 1)
  #define DDRCLKCH0_CR_DDRCRCLKCONTROLS_LPDDR_Mode_MSK                 (0x20000000)
  #define DDRCLKCH0_CR_DDRCRCLKCONTROLS_LPDDR_Mode_MIN                 (0)
  #define DDRCLKCH0_CR_DDRCRCLKCONTROLS_LPDDR_Mode_MAX                 (1) // 0x00000001
  #define DDRCLKCH0_CR_DDRCRCLKCONTROLS_LPDDR_Mode_DEF                 (0x00000000)
  #define DDRCLKCH0_CR_DDRCRCLKCONTROLS_LPDDR_Mode_HSH                 (0x011D1810)

  #define DDRCLKCH0_CR_DDRCRCLKCONTROLS_LPDdrClkWeakDrv_OFF            (30)
  #define DDRCLKCH0_CR_DDRCRCLKCONTROLS_LPDdrClkWeakDrv_WID            ( 1)
  #define DDRCLKCH0_CR_DDRCRCLKCONTROLS_LPDdrClkWeakDrv_MSK            (0x40000000)
  #define DDRCLKCH0_CR_DDRCRCLKCONTROLS_LPDdrClkWeakDrv_MIN            (0)
  #define DDRCLKCH0_CR_DDRCRCLKCONTROLS_LPDdrClkWeakDrv_MAX            (1) // 0x00000001
  #define DDRCLKCH0_CR_DDRCRCLKCONTROLS_LPDdrClkWeakDrv_DEF            (0x00000000)
  #define DDRCLKCH0_CR_DDRCRCLKCONTROLS_LPDdrClkWeakDrv_HSH            (0x011E1810)

  #define DDRCLKCH0_CR_DDRCRCLKCONTROLS_ClkGateDisable_OFF             (31)
  #define DDRCLKCH0_CR_DDRCRCLKCONTROLS_ClkGateDisable_WID             ( 1)
  #define DDRCLKCH0_CR_DDRCRCLKCONTROLS_ClkGateDisable_MSK             (0x80000000)
  #define DDRCLKCH0_CR_DDRCRCLKCONTROLS_ClkGateDisable_MIN             (0)
  #define DDRCLKCH0_CR_DDRCRCLKCONTROLS_ClkGateDisable_MAX             (1) // 0x00000001
  #define DDRCLKCH0_CR_DDRCRCLKCONTROLS_ClkGateDisable_DEF             (0x00000000)
  #define DDRCLKCH0_CR_DDRCRCLKCONTROLS_ClkGateDisable_HSH             (0x011F1810)

#define DDRCLKCH0_CR_DLLPITESTANDADC_REG                               (0x00001814)

  #define DDRCLKCH0_CR_DLLPITESTANDADC_RunTest_OFF                     ( 0)
  #define DDRCLKCH0_CR_DLLPITESTANDADC_RunTest_WID                     ( 1)
  #define DDRCLKCH0_CR_DLLPITESTANDADC_RunTest_MSK                     (0x00000001)
  #define DDRCLKCH0_CR_DLLPITESTANDADC_RunTest_MIN                     (0)
  #define DDRCLKCH0_CR_DLLPITESTANDADC_RunTest_MAX                     (1) // 0x00000001
  #define DDRCLKCH0_CR_DLLPITESTANDADC_RunTest_DEF                     (0x00000000)
  #define DDRCLKCH0_CR_DLLPITESTANDADC_RunTest_HSH                     (0x01001814)

  #define DDRCLKCH0_CR_DLLPITESTANDADC_Load_OFF                        ( 1)
  #define DDRCLKCH0_CR_DLLPITESTANDADC_Load_WID                        ( 1)
  #define DDRCLKCH0_CR_DLLPITESTANDADC_Load_MSK                        (0x00000002)
  #define DDRCLKCH0_CR_DLLPITESTANDADC_Load_MIN                        (0)
  #define DDRCLKCH0_CR_DLLPITESTANDADC_Load_MAX                        (1) // 0x00000001
  #define DDRCLKCH0_CR_DLLPITESTANDADC_Load_DEF                        (0x00000000)
  #define DDRCLKCH0_CR_DLLPITESTANDADC_Load_HSH                        (0x01011814)

  #define DDRCLKCH0_CR_DLLPITESTANDADC_ModeHVM_OFF                     ( 2)
  #define DDRCLKCH0_CR_DLLPITESTANDADC_ModeHVM_WID                     ( 1)
  #define DDRCLKCH0_CR_DLLPITESTANDADC_ModeHVM_MSK                     (0x00000004)
  #define DDRCLKCH0_CR_DLLPITESTANDADC_ModeHVM_MIN                     (0)
  #define DDRCLKCH0_CR_DLLPITESTANDADC_ModeHVM_MAX                     (1) // 0x00000001
  #define DDRCLKCH0_CR_DLLPITESTANDADC_ModeHVM_DEF                     (0x00000000)
  #define DDRCLKCH0_CR_DLLPITESTANDADC_ModeHVM_HSH                     (0x01021814)

  #define DDRCLKCH0_CR_DLLPITESTANDADC_ModeDV_OFF                      ( 3)
  #define DDRCLKCH0_CR_DLLPITESTANDADC_ModeDV_WID                      ( 1)
  #define DDRCLKCH0_CR_DLLPITESTANDADC_ModeDV_MSK                      (0x00000008)
  #define DDRCLKCH0_CR_DLLPITESTANDADC_ModeDV_MIN                      (0)
  #define DDRCLKCH0_CR_DLLPITESTANDADC_ModeDV_MAX                      (1) // 0x00000001
  #define DDRCLKCH0_CR_DLLPITESTANDADC_ModeDV_DEF                      (0x00000000)
  #define DDRCLKCH0_CR_DLLPITESTANDADC_ModeDV_HSH                      (0x01031814)

  #define DDRCLKCH0_CR_DLLPITESTANDADC_CalCfdl_OFF                     ( 4)
  #define DDRCLKCH0_CR_DLLPITESTANDADC_CalCfdl_WID                     ( 1)
  #define DDRCLKCH0_CR_DLLPITESTANDADC_CalCfdl_MSK                     (0x00000010)
  #define DDRCLKCH0_CR_DLLPITESTANDADC_CalCfdl_MIN                     (0)
  #define DDRCLKCH0_CR_DLLPITESTANDADC_CalCfdl_MAX                     (1) // 0x00000001
  #define DDRCLKCH0_CR_DLLPITESTANDADC_CalCfdl_DEF                     (0x00000000)
  #define DDRCLKCH0_CR_DLLPITESTANDADC_CalCfdl_HSH                     (0x01041814)

  #define DDRCLKCH0_CR_DLLPITESTANDADC_LoadCount_OFF                   ( 5)
  #define DDRCLKCH0_CR_DLLPITESTANDADC_LoadCount_WID                   (10)
  #define DDRCLKCH0_CR_DLLPITESTANDADC_LoadCount_MSK                   (0x00007FE0)
  #define DDRCLKCH0_CR_DLLPITESTANDADC_LoadCount_MIN                   (0)
  #define DDRCLKCH0_CR_DLLPITESTANDADC_LoadCount_MAX                   (1023) // 0x000003FF
  #define DDRCLKCH0_CR_DLLPITESTANDADC_LoadCount_DEF                   (0x00000000)
  #define DDRCLKCH0_CR_DLLPITESTANDADC_LoadCount_HSH                   (0x0A051814)

  #define DDRCLKCH0_CR_DLLPITESTANDADC_CountStatus_OFF                 (15)
  #define DDRCLKCH0_CR_DLLPITESTANDADC_CountStatus_WID                 (10)
  #define DDRCLKCH0_CR_DLLPITESTANDADC_CountStatus_MSK                 (0x01FF8000)
  #define DDRCLKCH0_CR_DLLPITESTANDADC_CountStatus_MIN                 (0)
  #define DDRCLKCH0_CR_DLLPITESTANDADC_CountStatus_MAX                 (1023) // 0x000003FF
  #define DDRCLKCH0_CR_DLLPITESTANDADC_CountStatus_DEF                 (0x00000000)
  #define DDRCLKCH0_CR_DLLPITESTANDADC_CountStatus_HSH                 (0x0A0F1814)

  #define DDRCLKCH0_CR_DLLPITESTANDADC_PhaseDrvPwrSavOn_OFF            (25)
  #define DDRCLKCH0_CR_DLLPITESTANDADC_PhaseDrvPwrSavOn_WID            ( 1)
  #define DDRCLKCH0_CR_DLLPITESTANDADC_PhaseDrvPwrSavOn_MSK            (0x02000000)
  #define DDRCLKCH0_CR_DLLPITESTANDADC_PhaseDrvPwrSavOn_MIN            (0)
  #define DDRCLKCH0_CR_DLLPITESTANDADC_PhaseDrvPwrSavOn_MAX            (1) // 0x00000001
  #define DDRCLKCH0_CR_DLLPITESTANDADC_PhaseDrvPwrSavOn_DEF            (0x00000000)
  #define DDRCLKCH0_CR_DLLPITESTANDADC_PhaseDrvPwrSavOn_HSH            (0x01191814)

  #define DDRCLKCH0_CR_DLLPITESTANDADC_Spare_OFF                       (26)
  #define DDRCLKCH0_CR_DLLPITESTANDADC_Spare_WID                       ( 6)
  #define DDRCLKCH0_CR_DLLPITESTANDADC_Spare_MSK                       (0xFC000000)
  #define DDRCLKCH0_CR_DLLPITESTANDADC_Spare_MIN                       (0)
  #define DDRCLKCH0_CR_DLLPITESTANDADC_Spare_MAX                       (63) // 0x0000003F
  #define DDRCLKCH0_CR_DLLPITESTANDADC_Spare_DEF                       (0x00000000)
  #define DDRCLKCH0_CR_DLLPITESTANDADC_Spare_HSH                       (0x061A1814)

#define DDRCLKCH0_CR_DDRCBSTATUS_REG                                   (0x00001818)

  #define DDRCLKCH0_CR_DDRCBSTATUS_DllCB_OFF                           ( 0)
  #define DDRCLKCH0_CR_DDRCBSTATUS_DllCB_WID                           ( 2)
  #define DDRCLKCH0_CR_DDRCBSTATUS_DllCB_MSK                           (0x00000003)
  #define DDRCLKCH0_CR_DDRCBSTATUS_DllCB_MIN                           (0)
  #define DDRCLKCH0_CR_DDRCBSTATUS_DllCB_MAX                           (3) // 0x00000003
  #define DDRCLKCH0_CR_DDRCBSTATUS_DllCB_DEF                           (0x00000000)
  #define DDRCLKCH0_CR_DDRCBSTATUS_DllCB_HSH                           (0x02001818)

  #define DDRCLKCH0_CR_DDRCBSTATUS_Spare_OFF                           ( 2)
  #define DDRCLKCH0_CR_DDRCBSTATUS_Spare_WID                           (30)
  #define DDRCLKCH0_CR_DDRCBSTATUS_Spare_MSK                           (0xFFFFFFFC)
  #define DDRCLKCH0_CR_DDRCBSTATUS_Spare_MIN                           (0)
  #define DDRCLKCH0_CR_DDRCBSTATUS_Spare_MAX                           (1073741823) // 0x3FFFFFFF
  #define DDRCLKCH0_CR_DDRCBSTATUS_Spare_DEF                           (0x00000000)
  #define DDRCLKCH0_CR_DDRCBSTATUS_Spare_HSH                           (0x1E021818)

#define DDRCLKCH0_CR_DDR4CRBSCANDATA_REG                               (0x0000181C)

  #define DDRCLKCH0_CR_DDR4CRBSCANDATA_Ddr4BscanClockEnable_OFF        ( 0)
  #define DDRCLKCH0_CR_DDR4CRBSCANDATA_Ddr4BscanClockEnable_WID        ( 1)
  #define DDRCLKCH0_CR_DDR4CRBSCANDATA_Ddr4BscanClockEnable_MSK        (0x00000001)
  #define DDRCLKCH0_CR_DDR4CRBSCANDATA_Ddr4BscanClockEnable_MIN        (0)
  #define DDRCLKCH0_CR_DDR4CRBSCANDATA_Ddr4BscanClockEnable_MAX        (1) // 0x00000001
  #define DDRCLKCH0_CR_DDR4CRBSCANDATA_Ddr4BscanClockEnable_DEF        (0x00000000)
  #define DDRCLKCH0_CR_DDR4CRBSCANDATA_Ddr4BscanClockEnable_HSH        (0x0100181C)

  #define DDRCLKCH0_CR_DDR4CRBSCANDATA_Data_ClkP_OFF                   ( 1)
  #define DDRCLKCH0_CR_DDR4CRBSCANDATA_Data_ClkP_WID                   ( 4)
  #define DDRCLKCH0_CR_DDR4CRBSCANDATA_Data_ClkP_MSK                   (0x0000001E)
  #define DDRCLKCH0_CR_DDR4CRBSCANDATA_Data_ClkP_MIN                   (0)
  #define DDRCLKCH0_CR_DDR4CRBSCANDATA_Data_ClkP_MAX                   (15) // 0x0000000F
  #define DDRCLKCH0_CR_DDR4CRBSCANDATA_Data_ClkP_DEF                   (0x00000000)
  #define DDRCLKCH0_CR_DDR4CRBSCANDATA_Data_ClkP_HSH                   (0x0401181C)

  #define DDRCLKCH0_CR_DDR4CRBSCANDATA_Data_ClkN_OFF                   ( 5)
  #define DDRCLKCH0_CR_DDR4CRBSCANDATA_Data_ClkN_WID                   ( 4)
  #define DDRCLKCH0_CR_DDR4CRBSCANDATA_Data_ClkN_MSK                   (0x000001E0)
  #define DDRCLKCH0_CR_DDR4CRBSCANDATA_Data_ClkN_MIN                   (0)
  #define DDRCLKCH0_CR_DDR4CRBSCANDATA_Data_ClkN_MAX                   (15) // 0x0000000F
  #define DDRCLKCH0_CR_DDR4CRBSCANDATA_Data_ClkN_DEF                   (0x00000000)
  #define DDRCLKCH0_CR_DDR4CRBSCANDATA_Data_ClkN_HSH                   (0x0405181C)

  #define DDRCLKCH0_CR_DDR4CRBSCANDATA_Spare_OFF                       ( 9)
  #define DDRCLKCH0_CR_DDR4CRBSCANDATA_Spare_WID                       (23)
  #define DDRCLKCH0_CR_DDR4CRBSCANDATA_Spare_MSK                       (0xFFFFFE00)
  #define DDRCLKCH0_CR_DDR4CRBSCANDATA_Spare_MIN                       (0)
  #define DDRCLKCH0_CR_DDR4CRBSCANDATA_Spare_MAX                       (8388607) // 0x007FFFFF
  #define DDRCLKCH0_CR_DDR4CRBSCANDATA_Spare_DEF                       (0x00000000)
  #define DDRCLKCH0_CR_DDR4CRBSCANDATA_Spare_HSH                       (0x1709181C)

#define DDRCLKCH0_CR_DDRVSSHICOMPCTL_REG                               (0x00001820)

  #define DDRCLKCH0_CR_DDRVSSHICOMPCTL_Rsvd_OFF                        ( 0)
  #define DDRCLKCH0_CR_DDRVSSHICOMPCTL_Rsvd_WID                        (11)
  #define DDRCLKCH0_CR_DDRVSSHICOMPCTL_Rsvd_MSK                        (0x000007FF)
  #define DDRCLKCH0_CR_DDRVSSHICOMPCTL_Rsvd_MIN                        (0)
  #define DDRCLKCH0_CR_DDRVSSHICOMPCTL_Rsvd_MAX                        (2047) // 0x000007FF
  #define DDRCLKCH0_CR_DDRVSSHICOMPCTL_Rsvd_DEF                        (0x00000000)
  #define DDRCLKCH0_CR_DDRVSSHICOMPCTL_Rsvd_HSH                        (0x0B001820)

  #define DDRCLKCH0_CR_DDRVSSHICOMPCTL_DisSensorPwrDn_OFF              (11)
  #define DDRCLKCH0_CR_DDRVSSHICOMPCTL_DisSensorPwrDn_WID              ( 1)
  #define DDRCLKCH0_CR_DDRVSSHICOMPCTL_DisSensorPwrDn_MSK              (0x00000800)
  #define DDRCLKCH0_CR_DDRVSSHICOMPCTL_DisSensorPwrDn_MIN              (0)
  #define DDRCLKCH0_CR_DDRVSSHICOMPCTL_DisSensorPwrDn_MAX              (1) // 0x00000001
  #define DDRCLKCH0_CR_DDRVSSHICOMPCTL_DisSensorPwrDn_DEF              (0x00000000)
  #define DDRCLKCH0_CR_DDRVSSHICOMPCTL_DisSensorPwrDn_HSH              (0x010B1820)

  #define DDRCLKCH0_CR_DDRVSSHICOMPCTL_OfstOvrdEn_OFF                  (12)
  #define DDRCLKCH0_CR_DDRVSSHICOMPCTL_OfstOvrdEn_WID                  ( 1)
  #define DDRCLKCH0_CR_DDRVSSHICOMPCTL_OfstOvrdEn_MSK                  (0x00001000)
  #define DDRCLKCH0_CR_DDRVSSHICOMPCTL_OfstOvrdEn_MIN                  (0)
  #define DDRCLKCH0_CR_DDRVSSHICOMPCTL_OfstOvrdEn_MAX                  (1) // 0x00000001
  #define DDRCLKCH0_CR_DDRVSSHICOMPCTL_OfstOvrdEn_DEF                  (0x00000000)
  #define DDRCLKCH0_CR_DDRVSSHICOMPCTL_OfstOvrdEn_HSH                  (0x010C1820)

  #define DDRCLKCH0_CR_DDRVSSHICOMPCTL_ViewOfstsel_OFF                 (13)
  #define DDRCLKCH0_CR_DDRVSSHICOMPCTL_ViewOfstsel_WID                 ( 3)
  #define DDRCLKCH0_CR_DDRVSSHICOMPCTL_ViewOfstsel_MSK                 (0x0000E000)
  #define DDRCLKCH0_CR_DDRVSSHICOMPCTL_ViewOfstsel_MIN                 (0)
  #define DDRCLKCH0_CR_DDRVSSHICOMPCTL_ViewOfstsel_MAX                 (7) // 0x00000007
  #define DDRCLKCH0_CR_DDRVSSHICOMPCTL_ViewOfstsel_DEF                 (0x00000000)
  #define DDRCLKCH0_CR_DDRVSSHICOMPCTL_ViewOfstsel_HSH                 (0x030D1820)

  #define DDRCLKCH0_CR_DDRVSSHICOMPCTL_EnVttCompforVsshi_OFF           (16)
  #define DDRCLKCH0_CR_DDRVSSHICOMPCTL_EnVttCompforVsshi_WID           ( 1)
  #define DDRCLKCH0_CR_DDRVSSHICOMPCTL_EnVttCompforVsshi_MSK           (0x00010000)
  #define DDRCLKCH0_CR_DDRVSSHICOMPCTL_EnVttCompforVsshi_MIN           (0)
  #define DDRCLKCH0_CR_DDRVSSHICOMPCTL_EnVttCompforVsshi_MAX           (1) // 0x00000001
  #define DDRCLKCH0_CR_DDRVSSHICOMPCTL_EnVttCompforVsshi_DEF           (0x00000000)
  #define DDRCLKCH0_CR_DDRVSSHICOMPCTL_EnVttCompforVsshi_HSH           (0x01101820)

  #define DDRCLKCH0_CR_DDRVSSHICOMPCTL_Spares_OFF                      (17)
  #define DDRCLKCH0_CR_DDRVSSHICOMPCTL_Spares_WID                      ( 8)
  #define DDRCLKCH0_CR_DDRVSSHICOMPCTL_Spares_MSK                      (0x01FE0000)
  #define DDRCLKCH0_CR_DDRVSSHICOMPCTL_Spares_MIN                      (0)
  #define DDRCLKCH0_CR_DDRVSSHICOMPCTL_Spares_MAX                      (255) // 0x000000FF
  #define DDRCLKCH0_CR_DDRVSSHICOMPCTL_Spares_DEF                      (0x00000000)
  #define DDRCLKCH0_CR_DDRVSSHICOMPCTL_Spares_HSH                      (0x08111820)

  #define DDRCLKCH0_CR_DDRVSSHICOMPCTL_Disable2Vt_OFF                  (25)
  #define DDRCLKCH0_CR_DDRVSSHICOMPCTL_Disable2Vt_WID                  ( 1)
  #define DDRCLKCH0_CR_DDRVSSHICOMPCTL_Disable2Vt_MSK                  (0x02000000)
  #define DDRCLKCH0_CR_DDRVSSHICOMPCTL_Disable2Vt_MIN                  (0)
  #define DDRCLKCH0_CR_DDRVSSHICOMPCTL_Disable2Vt_MAX                  (1) // 0x00000001
  #define DDRCLKCH0_CR_DDRVSSHICOMPCTL_Disable2Vt_DEF                  (0x00000000)
  #define DDRCLKCH0_CR_DDRVSSHICOMPCTL_Disable2Vt_HSH                  (0x01191820)

  #define DDRCLKCH0_CR_DDRVSSHICOMPCTL_OfstOvrdOrView_OFF              (26)
  #define DDRCLKCH0_CR_DDRVSSHICOMPCTL_OfstOvrdOrView_WID              ( 6)
  #define DDRCLKCH0_CR_DDRVSSHICOMPCTL_OfstOvrdOrView_MSK              (0xFC000000)
  #define DDRCLKCH0_CR_DDRVSSHICOMPCTL_OfstOvrdOrView_MIN              (0)
  #define DDRCLKCH0_CR_DDRVSSHICOMPCTL_OfstOvrdOrView_MAX              (63) // 0x0000003F
  #define DDRCLKCH0_CR_DDRVSSHICOMPCTL_OfstOvrdOrView_DEF              (0x00000000)
  #define DDRCLKCH0_CR_DDRVSSHICOMPCTL_OfstOvrdOrView_HSH              (0x061A1820)

#define DDRCLKCH1_CR_DDRCRCLKRANKSUSED_REG                             (0x00001900)

  #define DDRCLKCH1_CR_DDRCRCLKRANKSUSED_RankEn_OFF                    ( 0)
  #define DDRCLKCH1_CR_DDRCRCLKRANKSUSED_RankEn_WID                    ( 4)
  #define DDRCLKCH1_CR_DDRCRCLKRANKSUSED_RankEn_MSK                    (0x0000000F)
  #define DDRCLKCH1_CR_DDRCRCLKRANKSUSED_RankEn_MIN                    (0)
  #define DDRCLKCH1_CR_DDRCRCLKRANKSUSED_RankEn_MAX                    (15) // 0x0000000F
  #define DDRCLKCH1_CR_DDRCRCLKRANKSUSED_RankEn_DEF                    (0x0000000F)
  #define DDRCLKCH1_CR_DDRCRCLKRANKSUSED_RankEn_HSH                    (0x04001900)

  #define DDRCLKCH1_CR_DDRCRCLKRANKSUSED_Spare_OFF                     ( 4)
  #define DDRCLKCH1_CR_DDRCRCLKRANKSUSED_Spare_WID                     (28)
  #define DDRCLKCH1_CR_DDRCRCLKRANKSUSED_Spare_MSK                     (0xFFFFFFF0)
  #define DDRCLKCH1_CR_DDRCRCLKRANKSUSED_Spare_MIN                     (0)
  #define DDRCLKCH1_CR_DDRCRCLKRANKSUSED_Spare_MAX                     (268435455) // 0x0FFFFFFF
  #define DDRCLKCH1_CR_DDRCRCLKRANKSUSED_Spare_DEF                     (0x00000000)
  #define DDRCLKCH1_CR_DDRCRCLKRANKSUSED_Spare_HSH                     (0x1C041900)

#define DDRCLKCH1_CR_DDRCRCLKCOMP_REG                                  (0x00001904)

  #define DDRCLKCH1_CR_DDRCRCLKCOMP_Scomp_OFF                          ( 0)
  #define DDRCLKCH1_CR_DDRCRCLKCOMP_Scomp_WID                          ( 5)
  #define DDRCLKCH1_CR_DDRCRCLKCOMP_Scomp_MSK                          (0x0000001F)
  #define DDRCLKCH1_CR_DDRCRCLKCOMP_Scomp_MIN                          (0)
  #define DDRCLKCH1_CR_DDRCRCLKCOMP_Scomp_MAX                          (31) // 0x0000001F
  #define DDRCLKCH1_CR_DDRCRCLKCOMP_Scomp_DEF                          (0x00000000)
  #define DDRCLKCH1_CR_DDRCRCLKCOMP_Scomp_HSH                          (0x05001904)

  #define DDRCLKCH1_CR_DDRCRCLKCOMP_TcoComp_OFF                        ( 5)
  #define DDRCLKCH1_CR_DDRCRCLKCOMP_TcoComp_WID                        ( 6)
  #define DDRCLKCH1_CR_DDRCRCLKCOMP_TcoComp_MSK                        (0x000007E0)
  #define DDRCLKCH1_CR_DDRCRCLKCOMP_TcoComp_MIN                        (0)
  #define DDRCLKCH1_CR_DDRCRCLKCOMP_TcoComp_MAX                        (63) // 0x0000003F
  #define DDRCLKCH1_CR_DDRCRCLKCOMP_TcoComp_DEF                        (0x00000000)
  #define DDRCLKCH1_CR_DDRCRCLKCOMP_TcoComp_HSH                        (0x06051904)

  #define DDRCLKCH1_CR_DDRCRCLKCOMP_RcompDrvUp_OFF                     (11)
  #define DDRCLKCH1_CR_DDRCRCLKCOMP_RcompDrvUp_WID                     ( 6)
  #define DDRCLKCH1_CR_DDRCRCLKCOMP_RcompDrvUp_MSK                     (0x0001F800)
  #define DDRCLKCH1_CR_DDRCRCLKCOMP_RcompDrvUp_MIN                     (0)
  #define DDRCLKCH1_CR_DDRCRCLKCOMP_RcompDrvUp_MAX                     (63) // 0x0000003F
  #define DDRCLKCH1_CR_DDRCRCLKCOMP_RcompDrvUp_DEF                     (0x00000000)
  #define DDRCLKCH1_CR_DDRCRCLKCOMP_RcompDrvUp_HSH                     (0x060B1904)

  #define DDRCLKCH1_CR_DDRCRCLKCOMP_RcompDrvDown_OFF                   (17)
  #define DDRCLKCH1_CR_DDRCRCLKCOMP_RcompDrvDown_WID                   ( 6)
  #define DDRCLKCH1_CR_DDRCRCLKCOMP_RcompDrvDown_MSK                   (0x007E0000)
  #define DDRCLKCH1_CR_DDRCRCLKCOMP_RcompDrvDown_MIN                   (0)
  #define DDRCLKCH1_CR_DDRCRCLKCOMP_RcompDrvDown_MAX                   (63) // 0x0000003F
  #define DDRCLKCH1_CR_DDRCRCLKCOMP_RcompDrvDown_DEF                   (0x00000000)
  #define DDRCLKCH1_CR_DDRCRCLKCOMP_RcompDrvDown_HSH                   (0x06111904)

  #define DDRCLKCH1_CR_DDRCRCLKCOMP_Spare_OFF                          (23)
  #define DDRCLKCH1_CR_DDRCRCLKCOMP_Spare_WID                          ( 9)
  #define DDRCLKCH1_CR_DDRCRCLKCOMP_Spare_MSK                          (0xFF800000)
  #define DDRCLKCH1_CR_DDRCRCLKCOMP_Spare_MIN                          (0)
  #define DDRCLKCH1_CR_DDRCRCLKCOMP_Spare_MAX                          (511) // 0x000001FF
  #define DDRCLKCH1_CR_DDRCRCLKCOMP_Spare_DEF                          (0x00000003)
  #define DDRCLKCH1_CR_DDRCRCLKCOMP_Spare_HSH                          (0x09171904)

#define DDRCLKCH1_CR_DDRCRCLKCOMPOFFSET_REG                            (0x00001908)

  #define DDRCLKCH1_CR_DDRCRCLKCOMPOFFSET_ScompOffset_OFF              ( 0)
  #define DDRCLKCH1_CR_DDRCRCLKCOMPOFFSET_ScompOffset_WID              ( 4)
  #define DDRCLKCH1_CR_DDRCRCLKCOMPOFFSET_ScompOffset_MSK              (0x0000000F)
  #define DDRCLKCH1_CR_DDRCRCLKCOMPOFFSET_ScompOffset_MIN              (-8)
  #define DDRCLKCH1_CR_DDRCRCLKCOMPOFFSET_ScompOffset_MAX              (7) // 0x00000007
  #define DDRCLKCH1_CR_DDRCRCLKCOMPOFFSET_ScompOffset_DEF              (0x00000000)
  #define DDRCLKCH1_CR_DDRCRCLKCOMPOFFSET_ScompOffset_HSH              (0x84001908)

  #define DDRCLKCH1_CR_DDRCRCLKCOMPOFFSET_TcoCompOffset_OFF            ( 4)
  #define DDRCLKCH1_CR_DDRCRCLKCOMPOFFSET_TcoCompOffset_WID            ( 4)
  #define DDRCLKCH1_CR_DDRCRCLKCOMPOFFSET_TcoCompOffset_MSK            (0x000000F0)
  #define DDRCLKCH1_CR_DDRCRCLKCOMPOFFSET_TcoCompOffset_MIN            (-8)
  #define DDRCLKCH1_CR_DDRCRCLKCOMPOFFSET_TcoCompOffset_MAX            (7) // 0x00000007
  #define DDRCLKCH1_CR_DDRCRCLKCOMPOFFSET_TcoCompOffset_DEF            (0x00000000)
  #define DDRCLKCH1_CR_DDRCRCLKCOMPOFFSET_TcoCompOffset_HSH            (0x84041908)

  #define DDRCLKCH1_CR_DDRCRCLKCOMPOFFSET_RcompDrvUpOffset_OFF         ( 8)
  #define DDRCLKCH1_CR_DDRCRCLKCOMPOFFSET_RcompDrvUpOffset_WID         ( 4)
  #define DDRCLKCH1_CR_DDRCRCLKCOMPOFFSET_RcompDrvUpOffset_MSK         (0x00000F00)
  #define DDRCLKCH1_CR_DDRCRCLKCOMPOFFSET_RcompDrvUpOffset_MIN         (-8)
  #define DDRCLKCH1_CR_DDRCRCLKCOMPOFFSET_RcompDrvUpOffset_MAX         (7) // 0x00000007
  #define DDRCLKCH1_CR_DDRCRCLKCOMPOFFSET_RcompDrvUpOffset_DEF         (0x00000000)
  #define DDRCLKCH1_CR_DDRCRCLKCOMPOFFSET_RcompDrvUpOffset_HSH         (0x84081908)

  #define DDRCLKCH1_CR_DDRCRCLKCOMPOFFSET_RcompDrvDownOffset_OFF       (12)
  #define DDRCLKCH1_CR_DDRCRCLKCOMPOFFSET_RcompDrvDownOffset_WID       ( 4)
  #define DDRCLKCH1_CR_DDRCRCLKCOMPOFFSET_RcompDrvDownOffset_MSK       (0x0000F000)
  #define DDRCLKCH1_CR_DDRCRCLKCOMPOFFSET_RcompDrvDownOffset_MIN       (-8)
  #define DDRCLKCH1_CR_DDRCRCLKCOMPOFFSET_RcompDrvDownOffset_MAX       (7) // 0x00000007
  #define DDRCLKCH1_CR_DDRCRCLKCOMPOFFSET_RcompDrvDownOffset_DEF       (0x00000000)
  #define DDRCLKCH1_CR_DDRCRCLKCOMPOFFSET_RcompDrvDownOffset_HSH       (0x840C1908)

  #define DDRCLKCH1_CR_DDRCRCLKCOMPOFFSET_Spare_OFF                    (16)
  #define DDRCLKCH1_CR_DDRCRCLKCOMPOFFSET_Spare_WID                    (16)
  #define DDRCLKCH1_CR_DDRCRCLKCOMPOFFSET_Spare_MSK                    (0xFFFF0000)
  #define DDRCLKCH1_CR_DDRCRCLKCOMPOFFSET_Spare_MIN                    (0)
  #define DDRCLKCH1_CR_DDRCRCLKCOMPOFFSET_Spare_MAX                    (65535) // 0x0000FFFF
  #define DDRCLKCH1_CR_DDRCRCLKCOMPOFFSET_Spare_DEF                    (0x00000000)
  #define DDRCLKCH1_CR_DDRCRCLKCOMPOFFSET_Spare_HSH                    (0x10101908)

#define DDRCLKCH1_CR_DDRCRCLKPICODE_REG                                (0x0000190C)

  #define DDRCLKCH1_CR_DDRCRCLKPICODE_PiSettingRank0_OFF               ( 0)
  #define DDRCLKCH1_CR_DDRCRCLKPICODE_PiSettingRank0_WID               ( 7)
  #define DDRCLKCH1_CR_DDRCRCLKPICODE_PiSettingRank0_MSK               (0x0000007F)
  #define DDRCLKCH1_CR_DDRCRCLKPICODE_PiSettingRank0_MIN               (0)
  #define DDRCLKCH1_CR_DDRCRCLKPICODE_PiSettingRank0_MAX               (127) // 0x0000007F
  #define DDRCLKCH1_CR_DDRCRCLKPICODE_PiSettingRank0_DEF               (0x00000000)
  #define DDRCLKCH1_CR_DDRCRCLKPICODE_PiSettingRank0_HSH               (0x0700190C)

  #define DDRCLKCH1_CR_DDRCRCLKPICODE_PiSettingRank1_OFF               ( 7)
  #define DDRCLKCH1_CR_DDRCRCLKPICODE_PiSettingRank1_WID               ( 7)
  #define DDRCLKCH1_CR_DDRCRCLKPICODE_PiSettingRank1_MSK               (0x00003F80)
  #define DDRCLKCH1_CR_DDRCRCLKPICODE_PiSettingRank1_MIN               (0)
  #define DDRCLKCH1_CR_DDRCRCLKPICODE_PiSettingRank1_MAX               (127) // 0x0000007F
  #define DDRCLKCH1_CR_DDRCRCLKPICODE_PiSettingRank1_DEF               (0x00000000)
  #define DDRCLKCH1_CR_DDRCRCLKPICODE_PiSettingRank1_HSH               (0x0707190C)

  #define DDRCLKCH1_CR_DDRCRCLKPICODE_PiSettingRank2_OFF               (14)
  #define DDRCLKCH1_CR_DDRCRCLKPICODE_PiSettingRank2_WID               ( 7)
  #define DDRCLKCH1_CR_DDRCRCLKPICODE_PiSettingRank2_MSK               (0x001FC000)
  #define DDRCLKCH1_CR_DDRCRCLKPICODE_PiSettingRank2_MIN               (0)
  #define DDRCLKCH1_CR_DDRCRCLKPICODE_PiSettingRank2_MAX               (127) // 0x0000007F
  #define DDRCLKCH1_CR_DDRCRCLKPICODE_PiSettingRank2_DEF               (0x00000000)
  #define DDRCLKCH1_CR_DDRCRCLKPICODE_PiSettingRank2_HSH               (0x070E190C)

  #define DDRCLKCH1_CR_DDRCRCLKPICODE_PiSettingRank3_OFF               (21)
  #define DDRCLKCH1_CR_DDRCRCLKPICODE_PiSettingRank3_WID               ( 7)
  #define DDRCLKCH1_CR_DDRCRCLKPICODE_PiSettingRank3_MSK               (0x0FE00000)
  #define DDRCLKCH1_CR_DDRCRCLKPICODE_PiSettingRank3_MIN               (0)
  #define DDRCLKCH1_CR_DDRCRCLKPICODE_PiSettingRank3_MAX               (127) // 0x0000007F
  #define DDRCLKCH1_CR_DDRCRCLKPICODE_PiSettingRank3_DEF               (0x00000000)
  #define DDRCLKCH1_CR_DDRCRCLKPICODE_PiSettingRank3_HSH               (0x0715190C)

  #define DDRCLKCH1_CR_DDRCRCLKPICODE_Spare_OFF                        (28)
  #define DDRCLKCH1_CR_DDRCRCLKPICODE_Spare_WID                        ( 4)
  #define DDRCLKCH1_CR_DDRCRCLKPICODE_Spare_MSK                        (0xF0000000)
  #define DDRCLKCH1_CR_DDRCRCLKPICODE_Spare_MIN                        (0)
  #define DDRCLKCH1_CR_DDRCRCLKPICODE_Spare_MAX                        (15) // 0x0000000F
  #define DDRCLKCH1_CR_DDRCRCLKPICODE_Spare_DEF                        (0x00000000)
  #define DDRCLKCH1_CR_DDRCRCLKPICODE_Spare_HSH                        (0x041C190C)

#define DDRCLKCH1_CR_DDRCRCLKCONTROLS_REG                              (0x00001910)

  #define DDRCLKCH1_CR_DDRCRCLKCONTROLS_RefPi_OFF                      ( 0)
  #define DDRCLKCH1_CR_DDRCRCLKCONTROLS_RefPi_WID                      ( 4)
  #define DDRCLKCH1_CR_DDRCRCLKCONTROLS_RefPi_MSK                      (0x0000000F)
  #define DDRCLKCH1_CR_DDRCRCLKCONTROLS_RefPi_MIN                      (-8)
  #define DDRCLKCH1_CR_DDRCRCLKCONTROLS_RefPi_MAX                      (7) // 0x00000007
  #define DDRCLKCH1_CR_DDRCRCLKCONTROLS_RefPi_DEF                      (0x00000000)
  #define DDRCLKCH1_CR_DDRCRCLKCONTROLS_RefPi_HSH                      (0x84001910)

  #define DDRCLKCH1_CR_DDRCRCLKCONTROLS_DllMask_OFF                    ( 4)
  #define DDRCLKCH1_CR_DDRCRCLKCONTROLS_DllMask_WID                    ( 2)
  #define DDRCLKCH1_CR_DDRCRCLKCONTROLS_DllMask_MSK                    (0x00000030)
  #define DDRCLKCH1_CR_DDRCRCLKCONTROLS_DllMask_MIN                    (0)
  #define DDRCLKCH1_CR_DDRCRCLKCONTROLS_DllMask_MAX                    (3) // 0x00000003
  #define DDRCLKCH1_CR_DDRCRCLKCONTROLS_DllMask_DEF                    (0x00000000)
  #define DDRCLKCH1_CR_DDRCRCLKCONTROLS_DllMask_HSH                    (0x02041910)

  #define DDRCLKCH1_CR_DDRCRCLKCONTROLS_DllRsvd1_OFF                   ( 6)
  #define DDRCLKCH1_CR_DDRCRCLKCONTROLS_DllRsvd1_WID                   ( 1)
  #define DDRCLKCH1_CR_DDRCRCLKCONTROLS_DllRsvd1_MSK                   (0x00000040)
  #define DDRCLKCH1_CR_DDRCRCLKCONTROLS_DllRsvd1_MIN                   (0)
  #define DDRCLKCH1_CR_DDRCRCLKCONTROLS_DllRsvd1_MAX                   (1) // 0x00000001
  #define DDRCLKCH1_CR_DDRCRCLKCONTROLS_DllRsvd1_DEF                   (0x00000000)
  #define DDRCLKCH1_CR_DDRCRCLKCONTROLS_DllRsvd1_HSH                   (0x01061910)

  #define DDRCLKCH1_CR_DDRCRCLKCONTROLS_TxOn_OFF                       ( 7)
  #define DDRCLKCH1_CR_DDRCRCLKCONTROLS_TxOn_WID                       ( 1)
  #define DDRCLKCH1_CR_DDRCRCLKCONTROLS_TxOn_MSK                       (0x00000080)
  #define DDRCLKCH1_CR_DDRCRCLKCONTROLS_TxOn_MIN                       (0)
  #define DDRCLKCH1_CR_DDRCRCLKCONTROLS_TxOn_MAX                       (1) // 0x00000001
  #define DDRCLKCH1_CR_DDRCRCLKCONTROLS_TxOn_DEF                       (0x00000000)
  #define DDRCLKCH1_CR_DDRCRCLKCONTROLS_TxOn_HSH                       (0x01071910)

  #define DDRCLKCH1_CR_DDRCRCLKCONTROLS_IntClkOn_OFF                   ( 8)
  #define DDRCLKCH1_CR_DDRCRCLKCONTROLS_IntClkOn_WID                   ( 1)
  #define DDRCLKCH1_CR_DDRCRCLKCONTROLS_IntClkOn_MSK                   (0x00000100)
  #define DDRCLKCH1_CR_DDRCRCLKCONTROLS_IntClkOn_MIN                   (0)
  #define DDRCLKCH1_CR_DDRCRCLKCONTROLS_IntClkOn_MAX                   (1) // 0x00000001
  #define DDRCLKCH1_CR_DDRCRCLKCONTROLS_IntClkOn_DEF                   (0x00000000)
  #define DDRCLKCH1_CR_DDRCRCLKCONTROLS_IntClkOn_HSH                   (0x01081910)

  #define DDRCLKCH1_CR_DDRCRCLKCONTROLS_RepClkOn_OFF                   ( 9)
  #define DDRCLKCH1_CR_DDRCRCLKCONTROLS_RepClkOn_WID                   ( 1)
  #define DDRCLKCH1_CR_DDRCRCLKCONTROLS_RepClkOn_MSK                   (0x00000200)
  #define DDRCLKCH1_CR_DDRCRCLKCONTROLS_RepClkOn_MIN                   (0)
  #define DDRCLKCH1_CR_DDRCRCLKCONTROLS_RepClkOn_MAX                   (1) // 0x00000001
  #define DDRCLKCH1_CR_DDRCRCLKCONTROLS_RepClkOn_DEF                   (0x00000000)
  #define DDRCLKCH1_CR_DDRCRCLKCONTROLS_RepClkOn_HSH                   (0x01091910)

  #define DDRCLKCH1_CR_DDRCRCLKCONTROLS_IOLBCtl_OFF                    (10)
  #define DDRCLKCH1_CR_DDRCRCLKCONTROLS_IOLBCtl_WID                    ( 2)
  #define DDRCLKCH1_CR_DDRCRCLKCONTROLS_IOLBCtl_MSK                    (0x00000C00)
  #define DDRCLKCH1_CR_DDRCRCLKCONTROLS_IOLBCtl_MIN                    (0)
  #define DDRCLKCH1_CR_DDRCRCLKCONTROLS_IOLBCtl_MAX                    (3) // 0x00000003
  #define DDRCLKCH1_CR_DDRCRCLKCONTROLS_IOLBCtl_DEF                    (0x00000000)
  #define DDRCLKCH1_CR_DDRCRCLKCONTROLS_IOLBCtl_HSH                    (0x020A1910)

  #define DDRCLKCH1_CR_DDRCRCLKCONTROLS_OdtMode_OFF                    (12)
  #define DDRCLKCH1_CR_DDRCRCLKCONTROLS_OdtMode_WID                    ( 1)
  #define DDRCLKCH1_CR_DDRCRCLKCONTROLS_OdtMode_MSK                    (0x00001000)
  #define DDRCLKCH1_CR_DDRCRCLKCONTROLS_OdtMode_MIN                    (0)
  #define DDRCLKCH1_CR_DDRCRCLKCONTROLS_OdtMode_MAX                    (1) // 0x00000001
  #define DDRCLKCH1_CR_DDRCRCLKCONTROLS_OdtMode_DEF                    (0x00000000)
  #define DDRCLKCH1_CR_DDRCRCLKCONTROLS_OdtMode_HSH                    (0x010C1910)

  #define DDRCLKCH1_CR_DDRCRCLKCONTROLS_Reserved_OFF                   (13)
  #define DDRCLKCH1_CR_DDRCRCLKCONTROLS_Reserved_WID                   ( 8)
  #define DDRCLKCH1_CR_DDRCRCLKCONTROLS_Reserved_MSK                   (0x001FE000)
  #define DDRCLKCH1_CR_DDRCRCLKCONTROLS_Reserved_MIN                   (0)
  #define DDRCLKCH1_CR_DDRCRCLKCONTROLS_Reserved_MAX                   (255) // 0x000000FF
  #define DDRCLKCH1_CR_DDRCRCLKCONTROLS_Reserved_DEF                   (0x00000000)
  #define DDRCLKCH1_CR_DDRCRCLKCONTROLS_Reserved_HSH                   (0x080D1910)

  #define DDRCLKCH1_CR_DDRCRCLKCONTROLS_RxVref_OFF                     (21)
  #define DDRCLKCH1_CR_DDRCRCLKCONTROLS_RxVref_WID                     ( 6)
  #define DDRCLKCH1_CR_DDRCRCLKCONTROLS_RxVref_MSK                     (0x07E00000)
  #define DDRCLKCH1_CR_DDRCRCLKCONTROLS_RxVref_MIN                     (-32)
  #define DDRCLKCH1_CR_DDRCRCLKCONTROLS_RxVref_MAX                     (31) // 0x0000001F
  #define DDRCLKCH1_CR_DDRCRCLKCONTROLS_RxVref_DEF                     (0x00000000)
  #define DDRCLKCH1_CR_DDRCRCLKCONTROLS_RxVref_HSH                     (0x86151910)

  #define DDRCLKCH1_CR_DDRCRCLKCONTROLS_VccddqHi_OFF                   (27)
  #define DDRCLKCH1_CR_DDRCRCLKCONTROLS_VccddqHi_WID                   ( 1)
  #define DDRCLKCH1_CR_DDRCRCLKCONTROLS_VccddqHi_MSK                   (0x08000000)
  #define DDRCLKCH1_CR_DDRCRCLKCONTROLS_VccddqHi_MIN                   (0)
  #define DDRCLKCH1_CR_DDRCRCLKCONTROLS_VccddqHi_MAX                   (1) // 0x00000001
  #define DDRCLKCH1_CR_DDRCRCLKCONTROLS_VccddqHi_DEF                   (0x00000000)
  #define DDRCLKCH1_CR_DDRCRCLKCONTROLS_VccddqHi_HSH                   (0x011B1910)

  #define DDRCLKCH1_CR_DDRCRCLKCONTROLS_DllWeakLock_OFF                (28)
  #define DDRCLKCH1_CR_DDRCRCLKCONTROLS_DllWeakLock_WID                ( 1)
  #define DDRCLKCH1_CR_DDRCRCLKCONTROLS_DllWeakLock_MSK                (0x10000000)
  #define DDRCLKCH1_CR_DDRCRCLKCONTROLS_DllWeakLock_MIN                (0)
  #define DDRCLKCH1_CR_DDRCRCLKCONTROLS_DllWeakLock_MAX                (1) // 0x00000001
  #define DDRCLKCH1_CR_DDRCRCLKCONTROLS_DllWeakLock_DEF                (0x00000000)
  #define DDRCLKCH1_CR_DDRCRCLKCONTROLS_DllWeakLock_HSH                (0x011C1910)

  #define DDRCLKCH1_CR_DDRCRCLKCONTROLS_LPDDR_Mode_OFF                 (29)
  #define DDRCLKCH1_CR_DDRCRCLKCONTROLS_LPDDR_Mode_WID                 ( 1)
  #define DDRCLKCH1_CR_DDRCRCLKCONTROLS_LPDDR_Mode_MSK                 (0x20000000)
  #define DDRCLKCH1_CR_DDRCRCLKCONTROLS_LPDDR_Mode_MIN                 (0)
  #define DDRCLKCH1_CR_DDRCRCLKCONTROLS_LPDDR_Mode_MAX                 (1) // 0x00000001
  #define DDRCLKCH1_CR_DDRCRCLKCONTROLS_LPDDR_Mode_DEF                 (0x00000000)
  #define DDRCLKCH1_CR_DDRCRCLKCONTROLS_LPDDR_Mode_HSH                 (0x011D1910)

  #define DDRCLKCH1_CR_DDRCRCLKCONTROLS_LPDdrClkWeakDrv_OFF            (30)
  #define DDRCLKCH1_CR_DDRCRCLKCONTROLS_LPDdrClkWeakDrv_WID            ( 1)
  #define DDRCLKCH1_CR_DDRCRCLKCONTROLS_LPDdrClkWeakDrv_MSK            (0x40000000)
  #define DDRCLKCH1_CR_DDRCRCLKCONTROLS_LPDdrClkWeakDrv_MIN            (0)
  #define DDRCLKCH1_CR_DDRCRCLKCONTROLS_LPDdrClkWeakDrv_MAX            (1) // 0x00000001
  #define DDRCLKCH1_CR_DDRCRCLKCONTROLS_LPDdrClkWeakDrv_DEF            (0x00000000)
  #define DDRCLKCH1_CR_DDRCRCLKCONTROLS_LPDdrClkWeakDrv_HSH            (0x011E1910)

  #define DDRCLKCH1_CR_DDRCRCLKCONTROLS_ClkGateDisable_OFF             (31)
  #define DDRCLKCH1_CR_DDRCRCLKCONTROLS_ClkGateDisable_WID             ( 1)
  #define DDRCLKCH1_CR_DDRCRCLKCONTROLS_ClkGateDisable_MSK             (0x80000000)
  #define DDRCLKCH1_CR_DDRCRCLKCONTROLS_ClkGateDisable_MIN             (0)
  #define DDRCLKCH1_CR_DDRCRCLKCONTROLS_ClkGateDisable_MAX             (1) // 0x00000001
  #define DDRCLKCH1_CR_DDRCRCLKCONTROLS_ClkGateDisable_DEF             (0x00000000)
  #define DDRCLKCH1_CR_DDRCRCLKCONTROLS_ClkGateDisable_HSH             (0x011F1910)

#define DDRCLKCH1_CR_DLLPITESTANDADC_REG                               (0x00001914)

  #define DDRCLKCH1_CR_DLLPITESTANDADC_RunTest_OFF                     ( 0)
  #define DDRCLKCH1_CR_DLLPITESTANDADC_RunTest_WID                     ( 1)
  #define DDRCLKCH1_CR_DLLPITESTANDADC_RunTest_MSK                     (0x00000001)
  #define DDRCLKCH1_CR_DLLPITESTANDADC_RunTest_MIN                     (0)
  #define DDRCLKCH1_CR_DLLPITESTANDADC_RunTest_MAX                     (1) // 0x00000001
  #define DDRCLKCH1_CR_DLLPITESTANDADC_RunTest_DEF                     (0x00000000)
  #define DDRCLKCH1_CR_DLLPITESTANDADC_RunTest_HSH                     (0x01001914)

  #define DDRCLKCH1_CR_DLLPITESTANDADC_Load_OFF                        ( 1)
  #define DDRCLKCH1_CR_DLLPITESTANDADC_Load_WID                        ( 1)
  #define DDRCLKCH1_CR_DLLPITESTANDADC_Load_MSK                        (0x00000002)
  #define DDRCLKCH1_CR_DLLPITESTANDADC_Load_MIN                        (0)
  #define DDRCLKCH1_CR_DLLPITESTANDADC_Load_MAX                        (1) // 0x00000001
  #define DDRCLKCH1_CR_DLLPITESTANDADC_Load_DEF                        (0x00000000)
  #define DDRCLKCH1_CR_DLLPITESTANDADC_Load_HSH                        (0x01011914)

  #define DDRCLKCH1_CR_DLLPITESTANDADC_ModeHVM_OFF                     ( 2)
  #define DDRCLKCH1_CR_DLLPITESTANDADC_ModeHVM_WID                     ( 1)
  #define DDRCLKCH1_CR_DLLPITESTANDADC_ModeHVM_MSK                     (0x00000004)
  #define DDRCLKCH1_CR_DLLPITESTANDADC_ModeHVM_MIN                     (0)
  #define DDRCLKCH1_CR_DLLPITESTANDADC_ModeHVM_MAX                     (1) // 0x00000001
  #define DDRCLKCH1_CR_DLLPITESTANDADC_ModeHVM_DEF                     (0x00000000)
  #define DDRCLKCH1_CR_DLLPITESTANDADC_ModeHVM_HSH                     (0x01021914)

  #define DDRCLKCH1_CR_DLLPITESTANDADC_ModeDV_OFF                      ( 3)
  #define DDRCLKCH1_CR_DLLPITESTANDADC_ModeDV_WID                      ( 1)
  #define DDRCLKCH1_CR_DLLPITESTANDADC_ModeDV_MSK                      (0x00000008)
  #define DDRCLKCH1_CR_DLLPITESTANDADC_ModeDV_MIN                      (0)
  #define DDRCLKCH1_CR_DLLPITESTANDADC_ModeDV_MAX                      (1) // 0x00000001
  #define DDRCLKCH1_CR_DLLPITESTANDADC_ModeDV_DEF                      (0x00000000)
  #define DDRCLKCH1_CR_DLLPITESTANDADC_ModeDV_HSH                      (0x01031914)

  #define DDRCLKCH1_CR_DLLPITESTANDADC_CalCfdl_OFF                     ( 4)
  #define DDRCLKCH1_CR_DLLPITESTANDADC_CalCfdl_WID                     ( 1)
  #define DDRCLKCH1_CR_DLLPITESTANDADC_CalCfdl_MSK                     (0x00000010)
  #define DDRCLKCH1_CR_DLLPITESTANDADC_CalCfdl_MIN                     (0)
  #define DDRCLKCH1_CR_DLLPITESTANDADC_CalCfdl_MAX                     (1) // 0x00000001
  #define DDRCLKCH1_CR_DLLPITESTANDADC_CalCfdl_DEF                     (0x00000000)
  #define DDRCLKCH1_CR_DLLPITESTANDADC_CalCfdl_HSH                     (0x01041914)

  #define DDRCLKCH1_CR_DLLPITESTANDADC_LoadCount_OFF                   ( 5)
  #define DDRCLKCH1_CR_DLLPITESTANDADC_LoadCount_WID                   (10)
  #define DDRCLKCH1_CR_DLLPITESTANDADC_LoadCount_MSK                   (0x00007FE0)
  #define DDRCLKCH1_CR_DLLPITESTANDADC_LoadCount_MIN                   (0)
  #define DDRCLKCH1_CR_DLLPITESTANDADC_LoadCount_MAX                   (1023) // 0x000003FF
  #define DDRCLKCH1_CR_DLLPITESTANDADC_LoadCount_DEF                   (0x00000000)
  #define DDRCLKCH1_CR_DLLPITESTANDADC_LoadCount_HSH                   (0x0A051914)

  #define DDRCLKCH1_CR_DLLPITESTANDADC_CountStatus_OFF                 (15)
  #define DDRCLKCH1_CR_DLLPITESTANDADC_CountStatus_WID                 (10)
  #define DDRCLKCH1_CR_DLLPITESTANDADC_CountStatus_MSK                 (0x01FF8000)
  #define DDRCLKCH1_CR_DLLPITESTANDADC_CountStatus_MIN                 (0)
  #define DDRCLKCH1_CR_DLLPITESTANDADC_CountStatus_MAX                 (1023) // 0x000003FF
  #define DDRCLKCH1_CR_DLLPITESTANDADC_CountStatus_DEF                 (0x00000000)
  #define DDRCLKCH1_CR_DLLPITESTANDADC_CountStatus_HSH                 (0x0A0F1914)

  #define DDRCLKCH1_CR_DLLPITESTANDADC_PhaseDrvPwrSavOn_OFF            (25)
  #define DDRCLKCH1_CR_DLLPITESTANDADC_PhaseDrvPwrSavOn_WID            ( 1)
  #define DDRCLKCH1_CR_DLLPITESTANDADC_PhaseDrvPwrSavOn_MSK            (0x02000000)
  #define DDRCLKCH1_CR_DLLPITESTANDADC_PhaseDrvPwrSavOn_MIN            (0)
  #define DDRCLKCH1_CR_DLLPITESTANDADC_PhaseDrvPwrSavOn_MAX            (1) // 0x00000001
  #define DDRCLKCH1_CR_DLLPITESTANDADC_PhaseDrvPwrSavOn_DEF            (0x00000000)
  #define DDRCLKCH1_CR_DLLPITESTANDADC_PhaseDrvPwrSavOn_HSH            (0x01191914)

  #define DDRCLKCH1_CR_DLLPITESTANDADC_Spare_OFF                       (26)
  #define DDRCLKCH1_CR_DLLPITESTANDADC_Spare_WID                       ( 6)
  #define DDRCLKCH1_CR_DLLPITESTANDADC_Spare_MSK                       (0xFC000000)
  #define DDRCLKCH1_CR_DLLPITESTANDADC_Spare_MIN                       (0)
  #define DDRCLKCH1_CR_DLLPITESTANDADC_Spare_MAX                       (63) // 0x0000003F
  #define DDRCLKCH1_CR_DLLPITESTANDADC_Spare_DEF                       (0x00000000)
  #define DDRCLKCH1_CR_DLLPITESTANDADC_Spare_HSH                       (0x061A1914)

#define DDRCLKCH1_CR_DDRCBSTATUS_REG                                   (0x00001918)

  #define DDRCLKCH1_CR_DDRCBSTATUS_DllCB_OFF                           ( 0)
  #define DDRCLKCH1_CR_DDRCBSTATUS_DllCB_WID                           ( 2)
  #define DDRCLKCH1_CR_DDRCBSTATUS_DllCB_MSK                           (0x00000003)
  #define DDRCLKCH1_CR_DDRCBSTATUS_DllCB_MIN                           (0)
  #define DDRCLKCH1_CR_DDRCBSTATUS_DllCB_MAX                           (3) // 0x00000003
  #define DDRCLKCH1_CR_DDRCBSTATUS_DllCB_DEF                           (0x00000000)
  #define DDRCLKCH1_CR_DDRCBSTATUS_DllCB_HSH                           (0x02001918)

  #define DDRCLKCH1_CR_DDRCBSTATUS_Spare_OFF                           ( 2)
  #define DDRCLKCH1_CR_DDRCBSTATUS_Spare_WID                           (30)
  #define DDRCLKCH1_CR_DDRCBSTATUS_Spare_MSK                           (0xFFFFFFFC)
  #define DDRCLKCH1_CR_DDRCBSTATUS_Spare_MIN                           (0)
  #define DDRCLKCH1_CR_DDRCBSTATUS_Spare_MAX                           (1073741823) // 0x3FFFFFFF
  #define DDRCLKCH1_CR_DDRCBSTATUS_Spare_DEF                           (0x00000000)
  #define DDRCLKCH1_CR_DDRCBSTATUS_Spare_HSH                           (0x1E021918)

#define DDRCLKCH1_CR_DDR4CRBSCANDATA_REG                               (0x0000191C)

  #define DDRCLKCH1_CR_DDR4CRBSCANDATA_Ddr4BscanClockEnable_OFF        ( 0)
  #define DDRCLKCH1_CR_DDR4CRBSCANDATA_Ddr4BscanClockEnable_WID        ( 1)
  #define DDRCLKCH1_CR_DDR4CRBSCANDATA_Ddr4BscanClockEnable_MSK        (0x00000001)
  #define DDRCLKCH1_CR_DDR4CRBSCANDATA_Ddr4BscanClockEnable_MIN        (0)
  #define DDRCLKCH1_CR_DDR4CRBSCANDATA_Ddr4BscanClockEnable_MAX        (1) // 0x00000001
  #define DDRCLKCH1_CR_DDR4CRBSCANDATA_Ddr4BscanClockEnable_DEF        (0x00000000)
  #define DDRCLKCH1_CR_DDR4CRBSCANDATA_Ddr4BscanClockEnable_HSH        (0x0100191C)

  #define DDRCLKCH1_CR_DDR4CRBSCANDATA_Data_ClkP_OFF                   ( 1)
  #define DDRCLKCH1_CR_DDR4CRBSCANDATA_Data_ClkP_WID                   ( 4)
  #define DDRCLKCH1_CR_DDR4CRBSCANDATA_Data_ClkP_MSK                   (0x0000001E)
  #define DDRCLKCH1_CR_DDR4CRBSCANDATA_Data_ClkP_MIN                   (0)
  #define DDRCLKCH1_CR_DDR4CRBSCANDATA_Data_ClkP_MAX                   (15) // 0x0000000F
  #define DDRCLKCH1_CR_DDR4CRBSCANDATA_Data_ClkP_DEF                   (0x00000000)
  #define DDRCLKCH1_CR_DDR4CRBSCANDATA_Data_ClkP_HSH                   (0x0401191C)

  #define DDRCLKCH1_CR_DDR4CRBSCANDATA_Data_ClkN_OFF                   ( 5)
  #define DDRCLKCH1_CR_DDR4CRBSCANDATA_Data_ClkN_WID                   ( 4)
  #define DDRCLKCH1_CR_DDR4CRBSCANDATA_Data_ClkN_MSK                   (0x000001E0)
  #define DDRCLKCH1_CR_DDR4CRBSCANDATA_Data_ClkN_MIN                   (0)
  #define DDRCLKCH1_CR_DDR4CRBSCANDATA_Data_ClkN_MAX                   (15) // 0x0000000F
  #define DDRCLKCH1_CR_DDR4CRBSCANDATA_Data_ClkN_DEF                   (0x00000000)
  #define DDRCLKCH1_CR_DDR4CRBSCANDATA_Data_ClkN_HSH                   (0x0405191C)

  #define DDRCLKCH1_CR_DDR4CRBSCANDATA_Spare_OFF                       ( 9)
  #define DDRCLKCH1_CR_DDR4CRBSCANDATA_Spare_WID                       (23)
  #define DDRCLKCH1_CR_DDR4CRBSCANDATA_Spare_MSK                       (0xFFFFFE00)
  #define DDRCLKCH1_CR_DDR4CRBSCANDATA_Spare_MIN                       (0)
  #define DDRCLKCH1_CR_DDR4CRBSCANDATA_Spare_MAX                       (8388607) // 0x007FFFFF
  #define DDRCLKCH1_CR_DDR4CRBSCANDATA_Spare_DEF                       (0x00000000)
  #define DDRCLKCH1_CR_DDR4CRBSCANDATA_Spare_HSH                       (0x1709191C)

#define DDRCLKCH1_CR_DDRVSSHICOMPCTL_REG                               (0x00001920)

  #define DDRCLKCH1_CR_DDRVSSHICOMPCTL_Rsvd_OFF                        ( 0)
  #define DDRCLKCH1_CR_DDRVSSHICOMPCTL_Rsvd_WID                        (11)
  #define DDRCLKCH1_CR_DDRVSSHICOMPCTL_Rsvd_MSK                        (0x000007FF)
  #define DDRCLKCH1_CR_DDRVSSHICOMPCTL_Rsvd_MIN                        (0)
  #define DDRCLKCH1_CR_DDRVSSHICOMPCTL_Rsvd_MAX                        (2047) // 0x000007FF
  #define DDRCLKCH1_CR_DDRVSSHICOMPCTL_Rsvd_DEF                        (0x00000000)
  #define DDRCLKCH1_CR_DDRVSSHICOMPCTL_Rsvd_HSH                        (0x0B001920)

  #define DDRCLKCH1_CR_DDRVSSHICOMPCTL_DisSensorPwrDn_OFF              (11)
  #define DDRCLKCH1_CR_DDRVSSHICOMPCTL_DisSensorPwrDn_WID              ( 1)
  #define DDRCLKCH1_CR_DDRVSSHICOMPCTL_DisSensorPwrDn_MSK              (0x00000800)
  #define DDRCLKCH1_CR_DDRVSSHICOMPCTL_DisSensorPwrDn_MIN              (0)
  #define DDRCLKCH1_CR_DDRVSSHICOMPCTL_DisSensorPwrDn_MAX              (1) // 0x00000001
  #define DDRCLKCH1_CR_DDRVSSHICOMPCTL_DisSensorPwrDn_DEF              (0x00000000)
  #define DDRCLKCH1_CR_DDRVSSHICOMPCTL_DisSensorPwrDn_HSH              (0x010B1920)

  #define DDRCLKCH1_CR_DDRVSSHICOMPCTL_OfstOvrdEn_OFF                  (12)
  #define DDRCLKCH1_CR_DDRVSSHICOMPCTL_OfstOvrdEn_WID                  ( 1)
  #define DDRCLKCH1_CR_DDRVSSHICOMPCTL_OfstOvrdEn_MSK                  (0x00001000)
  #define DDRCLKCH1_CR_DDRVSSHICOMPCTL_OfstOvrdEn_MIN                  (0)
  #define DDRCLKCH1_CR_DDRVSSHICOMPCTL_OfstOvrdEn_MAX                  (1) // 0x00000001
  #define DDRCLKCH1_CR_DDRVSSHICOMPCTL_OfstOvrdEn_DEF                  (0x00000000)
  #define DDRCLKCH1_CR_DDRVSSHICOMPCTL_OfstOvrdEn_HSH                  (0x010C1920)

  #define DDRCLKCH1_CR_DDRVSSHICOMPCTL_ViewOfstsel_OFF                 (13)
  #define DDRCLKCH1_CR_DDRVSSHICOMPCTL_ViewOfstsel_WID                 ( 3)
  #define DDRCLKCH1_CR_DDRVSSHICOMPCTL_ViewOfstsel_MSK                 (0x0000E000)
  #define DDRCLKCH1_CR_DDRVSSHICOMPCTL_ViewOfstsel_MIN                 (0)
  #define DDRCLKCH1_CR_DDRVSSHICOMPCTL_ViewOfstsel_MAX                 (7) // 0x00000007
  #define DDRCLKCH1_CR_DDRVSSHICOMPCTL_ViewOfstsel_DEF                 (0x00000000)
  #define DDRCLKCH1_CR_DDRVSSHICOMPCTL_ViewOfstsel_HSH                 (0x030D1920)

  #define DDRCLKCH1_CR_DDRVSSHICOMPCTL_EnVttCompforVsshi_OFF           (16)
  #define DDRCLKCH1_CR_DDRVSSHICOMPCTL_EnVttCompforVsshi_WID           ( 1)
  #define DDRCLKCH1_CR_DDRVSSHICOMPCTL_EnVttCompforVsshi_MSK           (0x00010000)
  #define DDRCLKCH1_CR_DDRVSSHICOMPCTL_EnVttCompforVsshi_MIN           (0)
  #define DDRCLKCH1_CR_DDRVSSHICOMPCTL_EnVttCompforVsshi_MAX           (1) // 0x00000001
  #define DDRCLKCH1_CR_DDRVSSHICOMPCTL_EnVttCompforVsshi_DEF           (0x00000000)
  #define DDRCLKCH1_CR_DDRVSSHICOMPCTL_EnVttCompforVsshi_HSH           (0x01101920)

  #define DDRCLKCH1_CR_DDRVSSHICOMPCTL_Spares_OFF                      (17)
  #define DDRCLKCH1_CR_DDRVSSHICOMPCTL_Spares_WID                      ( 8)
  #define DDRCLKCH1_CR_DDRVSSHICOMPCTL_Spares_MSK                      (0x01FE0000)
  #define DDRCLKCH1_CR_DDRVSSHICOMPCTL_Spares_MIN                      (0)
  #define DDRCLKCH1_CR_DDRVSSHICOMPCTL_Spares_MAX                      (255) // 0x000000FF
  #define DDRCLKCH1_CR_DDRVSSHICOMPCTL_Spares_DEF                      (0x00000000)
  #define DDRCLKCH1_CR_DDRVSSHICOMPCTL_Spares_HSH                      (0x08111920)

  #define DDRCLKCH1_CR_DDRVSSHICOMPCTL_Disable2Vt_OFF                  (25)
  #define DDRCLKCH1_CR_DDRVSSHICOMPCTL_Disable2Vt_WID                  ( 1)
  #define DDRCLKCH1_CR_DDRVSSHICOMPCTL_Disable2Vt_MSK                  (0x02000000)
  #define DDRCLKCH1_CR_DDRVSSHICOMPCTL_Disable2Vt_MIN                  (0)
  #define DDRCLKCH1_CR_DDRVSSHICOMPCTL_Disable2Vt_MAX                  (1) // 0x00000001
  #define DDRCLKCH1_CR_DDRVSSHICOMPCTL_Disable2Vt_DEF                  (0x00000000)
  #define DDRCLKCH1_CR_DDRVSSHICOMPCTL_Disable2Vt_HSH                  (0x01191920)

  #define DDRCLKCH1_CR_DDRVSSHICOMPCTL_OfstOvrdOrView_OFF              (26)
  #define DDRCLKCH1_CR_DDRVSSHICOMPCTL_OfstOvrdOrView_WID              ( 6)
  #define DDRCLKCH1_CR_DDRVSSHICOMPCTL_OfstOvrdOrView_MSK              (0xFC000000)
  #define DDRCLKCH1_CR_DDRVSSHICOMPCTL_OfstOvrdOrView_MIN              (0)
  #define DDRCLKCH1_CR_DDRVSSHICOMPCTL_OfstOvrdOrView_MAX              (63) // 0x0000003F
  #define DDRCLKCH1_CR_DDRVSSHICOMPCTL_OfstOvrdOrView_DEF              (0x00000000)
  #define DDRCLKCH1_CR_DDRVSSHICOMPCTL_OfstOvrdOrView_HSH              (0x061A1920)

#define DDRCMDSCH0_CR_DDRCRCMDCOMP_REG                                 (0x00001A00)

  #define DDRCMDSCH0_CR_DDRCRCMDCOMP_Scomp_OFF                         ( 0)
  #define DDRCMDSCH0_CR_DDRCRCMDCOMP_Scomp_WID                         ( 6)
  #define DDRCMDSCH0_CR_DDRCRCMDCOMP_Scomp_MSK                         (0x0000003F)
  #define DDRCMDSCH0_CR_DDRCRCMDCOMP_Scomp_MIN                         (0)
  #define DDRCMDSCH0_CR_DDRCRCMDCOMP_Scomp_MAX                         (63) // 0x0000003F
  #define DDRCMDSCH0_CR_DDRCRCMDCOMP_Scomp_DEF                         (0x00000000)
  #define DDRCMDSCH0_CR_DDRCRCMDCOMP_Scomp_HSH                         (0x06001A00)

  #define DDRCMDSCH0_CR_DDRCRCMDCOMP_TcoComp_OFF                       ( 6)
  #define DDRCMDSCH0_CR_DDRCRCMDCOMP_TcoComp_WID                       ( 6)
  #define DDRCMDSCH0_CR_DDRCRCMDCOMP_TcoComp_MSK                       (0x00000FC0)
  #define DDRCMDSCH0_CR_DDRCRCMDCOMP_TcoComp_MIN                       (0)
  #define DDRCMDSCH0_CR_DDRCRCMDCOMP_TcoComp_MAX                       (63) // 0x0000003F
  #define DDRCMDSCH0_CR_DDRCRCMDCOMP_TcoComp_DEF                       (0x00000000)
  #define DDRCMDSCH0_CR_DDRCRCMDCOMP_TcoComp_HSH                       (0x06061A00)

  #define DDRCMDSCH0_CR_DDRCRCMDCOMP_RcompDrvUp_OFF                    (12)
  #define DDRCMDSCH0_CR_DDRCRCMDCOMP_RcompDrvUp_WID                    ( 6)
  #define DDRCMDSCH0_CR_DDRCRCMDCOMP_RcompDrvUp_MSK                    (0x0003F000)
  #define DDRCMDSCH0_CR_DDRCRCMDCOMP_RcompDrvUp_MIN                    (0)
  #define DDRCMDSCH0_CR_DDRCRCMDCOMP_RcompDrvUp_MAX                    (63) // 0x0000003F
  #define DDRCMDSCH0_CR_DDRCRCMDCOMP_RcompDrvUp_DEF                    (0x00000000)
  #define DDRCMDSCH0_CR_DDRCRCMDCOMP_RcompDrvUp_HSH                    (0x060C1A00)

  #define DDRCMDSCH0_CR_DDRCRCMDCOMP_RcompDrvDown_OFF                  (18)
  #define DDRCMDSCH0_CR_DDRCRCMDCOMP_RcompDrvDown_WID                  ( 6)
  #define DDRCMDSCH0_CR_DDRCRCMDCOMP_RcompDrvDown_MSK                  (0x00FC0000)
  #define DDRCMDSCH0_CR_DDRCRCMDCOMP_RcompDrvDown_MIN                  (0)
  #define DDRCMDSCH0_CR_DDRCRCMDCOMP_RcompDrvDown_MAX                  (63) // 0x0000003F
  #define DDRCMDSCH0_CR_DDRCRCMDCOMP_RcompDrvDown_DEF                  (0x00000000)
  #define DDRCMDSCH0_CR_DDRCRCMDCOMP_RcompDrvDown_HSH                  (0x06121A00)

  #define DDRCMDSCH0_CR_DDRCRCMDCOMP_Spare_OFF                         (24)
  #define DDRCMDSCH0_CR_DDRCRCMDCOMP_Spare_WID                         ( 8)
  #define DDRCMDSCH0_CR_DDRCRCMDCOMP_Spare_MSK                         (0xFF000000)
  #define DDRCMDSCH0_CR_DDRCRCMDCOMP_Spare_MIN                         (0)
  #define DDRCMDSCH0_CR_DDRCRCMDCOMP_Spare_MAX                         (255) // 0x000000FF
  #define DDRCMDSCH0_CR_DDRCRCMDCOMP_Spare_DEF                         (0x00000004)
  #define DDRCMDSCH0_CR_DDRCRCMDCOMP_Spare_HSH                         (0x08181A00)

#define DDRCMDSCH0_CR_DDRCRCMDCOMPOFFSET_REG                           (0x00001A04)

  #define DDRCMDSCH0_CR_DDRCRCMDCOMPOFFSET_ScompOffset_OFF             ( 0)
  #define DDRCMDSCH0_CR_DDRCRCMDCOMPOFFSET_ScompOffset_WID             ( 5)
  #define DDRCMDSCH0_CR_DDRCRCMDCOMPOFFSET_ScompOffset_MSK             (0x0000001F)
  #define DDRCMDSCH0_CR_DDRCRCMDCOMPOFFSET_ScompOffset_MIN             (-16)
  #define DDRCMDSCH0_CR_DDRCRCMDCOMPOFFSET_ScompOffset_MAX             (15) // 0x0000000F
  #define DDRCMDSCH0_CR_DDRCRCMDCOMPOFFSET_ScompOffset_DEF             (0x00000000)
  #define DDRCMDSCH0_CR_DDRCRCMDCOMPOFFSET_ScompOffset_HSH             (0x85001A04)

  #define DDRCMDSCH0_CR_DDRCRCMDCOMPOFFSET_TcoCompOffset_OFF           ( 5)
  #define DDRCMDSCH0_CR_DDRCRCMDCOMPOFFSET_TcoCompOffset_WID           ( 4)
  #define DDRCMDSCH0_CR_DDRCRCMDCOMPOFFSET_TcoCompOffset_MSK           (0x000001E0)
  #define DDRCMDSCH0_CR_DDRCRCMDCOMPOFFSET_TcoCompOffset_MIN           (-8)
  #define DDRCMDSCH0_CR_DDRCRCMDCOMPOFFSET_TcoCompOffset_MAX           (7) // 0x00000007
  #define DDRCMDSCH0_CR_DDRCRCMDCOMPOFFSET_TcoCompOffset_DEF           (0x00000000)
  #define DDRCMDSCH0_CR_DDRCRCMDCOMPOFFSET_TcoCompOffset_HSH           (0x84051A04)

  #define DDRCMDSCH0_CR_DDRCRCMDCOMPOFFSET_RcompDrvUpOffset_OFF        ( 9)
  #define DDRCMDSCH0_CR_DDRCRCMDCOMPOFFSET_RcompDrvUpOffset_WID        ( 4)
  #define DDRCMDSCH0_CR_DDRCRCMDCOMPOFFSET_RcompDrvUpOffset_MSK        (0x00001E00)
  #define DDRCMDSCH0_CR_DDRCRCMDCOMPOFFSET_RcompDrvUpOffset_MIN        (-8)
  #define DDRCMDSCH0_CR_DDRCRCMDCOMPOFFSET_RcompDrvUpOffset_MAX        (7) // 0x00000007
  #define DDRCMDSCH0_CR_DDRCRCMDCOMPOFFSET_RcompDrvUpOffset_DEF        (0x00000000)
  #define DDRCMDSCH0_CR_DDRCRCMDCOMPOFFSET_RcompDrvUpOffset_HSH        (0x84091A04)

  #define DDRCMDSCH0_CR_DDRCRCMDCOMPOFFSET_RcompDrvDownOffset_OFF      (13)
  #define DDRCMDSCH0_CR_DDRCRCMDCOMPOFFSET_RcompDrvDownOffset_WID      ( 4)
  #define DDRCMDSCH0_CR_DDRCRCMDCOMPOFFSET_RcompDrvDownOffset_MSK      (0x0001E000)
  #define DDRCMDSCH0_CR_DDRCRCMDCOMPOFFSET_RcompDrvDownOffset_MIN      (-8)
  #define DDRCMDSCH0_CR_DDRCRCMDCOMPOFFSET_RcompDrvDownOffset_MAX      (7) // 0x00000007
  #define DDRCMDSCH0_CR_DDRCRCMDCOMPOFFSET_RcompDrvDownOffset_DEF      (0x00000000)
  #define DDRCMDSCH0_CR_DDRCRCMDCOMPOFFSET_RcompDrvDownOffset_HSH      (0x840D1A04)

  #define DDRCMDSCH0_CR_DDRCRCMDCOMPOFFSET_Spare_OFF                   (17)
  #define DDRCMDSCH0_CR_DDRCRCMDCOMPOFFSET_Spare_WID                   (15)
  #define DDRCMDSCH0_CR_DDRCRCMDCOMPOFFSET_Spare_MSK                   (0xFFFE0000)
  #define DDRCMDSCH0_CR_DDRCRCMDCOMPOFFSET_Spare_MIN                   (0)
  #define DDRCMDSCH0_CR_DDRCRCMDCOMPOFFSET_Spare_MAX                   (32767) // 0x00007FFF
  #define DDRCMDSCH0_CR_DDRCRCMDCOMPOFFSET_Spare_DEF                   (0x00000000)
  #define DDRCMDSCH0_CR_DDRCRCMDCOMPOFFSET_Spare_HSH                   (0x0F111A04)

#define DDRCMDSCH0_CR_DDRCRCMDPICODING_REG                             (0x00001A08)

  #define DDRCMDSCH0_CR_DDRCRCMDPICODING_CmdPi0Code_OFF                ( 0)
  #define DDRCMDSCH0_CR_DDRCRCMDPICODING_CmdPi0Code_WID                ( 7)
  #define DDRCMDSCH0_CR_DDRCRCMDPICODING_CmdPi0Code_MSK                (0x0000007F)
  #define DDRCMDSCH0_CR_DDRCRCMDPICODING_CmdPi0Code_MIN                (0)
  #define DDRCMDSCH0_CR_DDRCRCMDPICODING_CmdPi0Code_MAX                (127) // 0x0000007F
  #define DDRCMDSCH0_CR_DDRCRCMDPICODING_CmdPi0Code_DEF                (0x00000000)
  #define DDRCMDSCH0_CR_DDRCRCMDPICODING_CmdPi0Code_HSH                (0x07001A08)

  #define DDRCMDSCH0_CR_DDRCRCMDPICODING_CmdPi1Code_OFF                ( 7)
  #define DDRCMDSCH0_CR_DDRCRCMDPICODING_CmdPi1Code_WID                ( 7)
  #define DDRCMDSCH0_CR_DDRCRCMDPICODING_CmdPi1Code_MSK                (0x00003F80)
  #define DDRCMDSCH0_CR_DDRCRCMDPICODING_CmdPi1Code_MIN                (0)
  #define DDRCMDSCH0_CR_DDRCRCMDPICODING_CmdPi1Code_MAX                (127) // 0x0000007F
  #define DDRCMDSCH0_CR_DDRCRCMDPICODING_CmdPi1Code_DEF                (0x00000000)
  #define DDRCMDSCH0_CR_DDRCRCMDPICODING_CmdPi1Code_HSH                (0x07071A08)

  #define DDRCMDSCH0_CR_DDRCRCMDPICODING_Spare_OFF                     (14)
  #define DDRCMDSCH0_CR_DDRCRCMDPICODING_Spare_WID                     (18)
  #define DDRCMDSCH0_CR_DDRCRCMDPICODING_Spare_MSK                     (0xFFFFC000)
  #define DDRCMDSCH0_CR_DDRCRCMDPICODING_Spare_MIN                     (0)
  #define DDRCMDSCH0_CR_DDRCRCMDPICODING_Spare_MAX                     (262143) // 0x0003FFFF
  #define DDRCMDSCH0_CR_DDRCRCMDPICODING_Spare_DEF                     (0x00000000)
  #define DDRCMDSCH0_CR_DDRCRCMDPICODING_Spare_HSH                     (0x120E1A08)

#define DDRCMDSCH0_CR_DDRCRCMDCONTROLS_REG                             (0x00001A0C)

  #define DDRCMDSCH0_CR_DDRCRCMDCONTROLS_RefPi_OFF                     ( 0)
  #define DDRCMDSCH0_CR_DDRCRCMDCONTROLS_RefPi_WID                     ( 4)
  #define DDRCMDSCH0_CR_DDRCRCMDCONTROLS_RefPi_MSK                     (0x0000000F)
  #define DDRCMDSCH0_CR_DDRCRCMDCONTROLS_RefPi_MIN                     (-8)
  #define DDRCMDSCH0_CR_DDRCRCMDCONTROLS_RefPi_MAX                     (7) // 0x00000007
  #define DDRCMDSCH0_CR_DDRCRCMDCONTROLS_RefPi_DEF                     (0x00000000)
  #define DDRCMDSCH0_CR_DDRCRCMDCONTROLS_RefPi_HSH                     (0x84001A0C)

  #define DDRCMDSCH0_CR_DDRCRCMDCONTROLS_DllMask_OFF                   ( 4)
  #define DDRCMDSCH0_CR_DDRCRCMDCONTROLS_DllMask_WID                   ( 2)
  #define DDRCMDSCH0_CR_DDRCRCMDCONTROLS_DllMask_MSK                   (0x00000030)
  #define DDRCMDSCH0_CR_DDRCRCMDCONTROLS_DllMask_MIN                   (0)
  #define DDRCMDSCH0_CR_DDRCRCMDCONTROLS_DllMask_MAX                   (3) // 0x00000003
  #define DDRCMDSCH0_CR_DDRCRCMDCONTROLS_DllMask_DEF                   (0x00000000)
  #define DDRCMDSCH0_CR_DDRCRCMDCONTROLS_DllMask_HSH                   (0x02041A0C)

  #define DDRCMDSCH0_CR_DDRCRCMDCONTROLS_ClkGateDisable_OFF            ( 6)
  #define DDRCMDSCH0_CR_DDRCRCMDCONTROLS_ClkGateDisable_WID            ( 1)
  #define DDRCMDSCH0_CR_DDRCRCMDCONTROLS_ClkGateDisable_MSK            (0x00000040)
  #define DDRCMDSCH0_CR_DDRCRCMDCONTROLS_ClkGateDisable_MIN            (0)
  #define DDRCMDSCH0_CR_DDRCRCMDCONTROLS_ClkGateDisable_MAX            (1) // 0x00000001
  #define DDRCMDSCH0_CR_DDRCRCMDCONTROLS_ClkGateDisable_DEF            (0x00000000)
  #define DDRCMDSCH0_CR_DDRCRCMDCONTROLS_ClkGateDisable_HSH            (0x01061A0C)

  #define DDRCMDSCH0_CR_DDRCRCMDCONTROLS_TxOn_OFF                      ( 7)
  #define DDRCMDSCH0_CR_DDRCRCMDCONTROLS_TxOn_WID                      ( 1)
  #define DDRCMDSCH0_CR_DDRCRCMDCONTROLS_TxOn_MSK                      (0x00000080)
  #define DDRCMDSCH0_CR_DDRCRCMDCONTROLS_TxOn_MIN                      (0)
  #define DDRCMDSCH0_CR_DDRCRCMDCONTROLS_TxOn_MAX                      (1) // 0x00000001
  #define DDRCMDSCH0_CR_DDRCRCMDCONTROLS_TxOn_DEF                      (0x00000000)
  #define DDRCMDSCH0_CR_DDRCRCMDCONTROLS_TxOn_HSH                      (0x01071A0C)

  #define DDRCMDSCH0_CR_DDRCRCMDCONTROLS_IntClkOn_OFF                  ( 8)
  #define DDRCMDSCH0_CR_DDRCRCMDCONTROLS_IntClkOn_WID                  ( 1)
  #define DDRCMDSCH0_CR_DDRCRCMDCONTROLS_IntClkOn_MSK                  (0x00000100)
  #define DDRCMDSCH0_CR_DDRCRCMDCONTROLS_IntClkOn_MIN                  (0)
  #define DDRCMDSCH0_CR_DDRCRCMDCONTROLS_IntClkOn_MAX                  (1) // 0x00000001
  #define DDRCMDSCH0_CR_DDRCRCMDCONTROLS_IntClkOn_DEF                  (0x00000000)
  #define DDRCMDSCH0_CR_DDRCRCMDCONTROLS_IntClkOn_HSH                  (0x01081A0C)

  #define DDRCMDSCH0_CR_DDRCRCMDCONTROLS_RepClkOn_OFF                  ( 9)
  #define DDRCMDSCH0_CR_DDRCRCMDCONTROLS_RepClkOn_WID                  ( 1)
  #define DDRCMDSCH0_CR_DDRCRCMDCONTROLS_RepClkOn_MSK                  (0x00000200)
  #define DDRCMDSCH0_CR_DDRCRCMDCONTROLS_RepClkOn_MIN                  (0)
  #define DDRCMDSCH0_CR_DDRCRCMDCONTROLS_RepClkOn_MAX                  (1) // 0x00000001
  #define DDRCMDSCH0_CR_DDRCRCMDCONTROLS_RepClkOn_DEF                  (0x00000000)
  #define DDRCMDSCH0_CR_DDRCRCMDCONTROLS_RepClkOn_HSH                  (0x01091A0C)

  #define DDRCMDSCH0_CR_DDRCRCMDCONTROLS_IolbOrMisr_OFF                (10)
  #define DDRCMDSCH0_CR_DDRCRCMDCONTROLS_IolbOrMisr_WID                ( 1)
  #define DDRCMDSCH0_CR_DDRCRCMDCONTROLS_IolbOrMisr_MSK                (0x00000400)
  #define DDRCMDSCH0_CR_DDRCRCMDCONTROLS_IolbOrMisr_MIN                (0)
  #define DDRCMDSCH0_CR_DDRCRCMDCONTROLS_IolbOrMisr_MAX                (1) // 0x00000001
  #define DDRCMDSCH0_CR_DDRCRCMDCONTROLS_IolbOrMisr_DEF                (0x00000000)
  #define DDRCMDSCH0_CR_DDRCRCMDCONTROLS_IolbOrMisr_HSH                (0x010A1A0C)

  #define DDRCMDSCH0_CR_DDRCRCMDCONTROLS_IolbHold_OFF                  (11)
  #define DDRCMDSCH0_CR_DDRCRCMDCONTROLS_IolbHold_WID                  ( 1)
  #define DDRCMDSCH0_CR_DDRCRCMDCONTROLS_IolbHold_MSK                  (0x00000800)
  #define DDRCMDSCH0_CR_DDRCRCMDCONTROLS_IolbHold_MIN                  (0)
  #define DDRCMDSCH0_CR_DDRCRCMDCONTROLS_IolbHold_MAX                  (1) // 0x00000001
  #define DDRCMDSCH0_CR_DDRCRCMDCONTROLS_IolbHold_DEF                  (0x00000000)
  #define DDRCMDSCH0_CR_DDRCRCMDCONTROLS_IolbHold_HSH                  (0x010B1A0C)

  #define DDRCMDSCH0_CR_DDRCRCMDCONTROLS_OdtMode_OFF                   (12)
  #define DDRCMDSCH0_CR_DDRCRCMDCONTROLS_OdtMode_WID                   ( 1)
  #define DDRCMDSCH0_CR_DDRCRCMDCONTROLS_OdtMode_MSK                   (0x00001000)
  #define DDRCMDSCH0_CR_DDRCRCMDCONTROLS_OdtMode_MIN                   (0)
  #define DDRCMDSCH0_CR_DDRCRCMDCONTROLS_OdtMode_MAX                   (1) // 0x00000001
  #define DDRCMDSCH0_CR_DDRCRCMDCONTROLS_OdtMode_DEF                   (0x00000000)
  #define DDRCMDSCH0_CR_DDRCRCMDCONTROLS_OdtMode_HSH                   (0x010C1A0C)

  #define DDRCMDSCH0_CR_DDRCRCMDCONTROLS_CmdTxEq_OFF                   (13)
  #define DDRCMDSCH0_CR_DDRCRCMDCONTROLS_CmdTxEq_WID                   ( 2)
  #define DDRCMDSCH0_CR_DDRCRCMDCONTROLS_CmdTxEq_MSK                   (0x00006000)
  #define DDRCMDSCH0_CR_DDRCRCMDCONTROLS_CmdTxEq_MIN                   (0)
  #define DDRCMDSCH0_CR_DDRCRCMDCONTROLS_CmdTxEq_MAX                   (3) // 0x00000003
  #define DDRCMDSCH0_CR_DDRCRCMDCONTROLS_CmdTxEq_DEF                   (0x00000000)
  #define DDRCMDSCH0_CR_DDRCRCMDCONTROLS_CmdTxEq_HSH                   (0x020D1A0C)

  #define DDRCMDSCH0_CR_DDRCRCMDCONTROLS_EarlyWeakDrive_OFF            (15)
  #define DDRCMDSCH0_CR_DDRCRCMDCONTROLS_EarlyWeakDrive_WID            ( 2)
  #define DDRCMDSCH0_CR_DDRCRCMDCONTROLS_EarlyWeakDrive_MSK            (0x00018000)
  #define DDRCMDSCH0_CR_DDRCRCMDCONTROLS_EarlyWeakDrive_MIN            (0)
  #define DDRCMDSCH0_CR_DDRCRCMDCONTROLS_EarlyWeakDrive_MAX            (3) // 0x00000003
  #define DDRCMDSCH0_CR_DDRCRCMDCONTROLS_EarlyWeakDrive_DEF            (0x00000000)
  #define DDRCMDSCH0_CR_DDRCRCMDCONTROLS_EarlyWeakDrive_HSH            (0x020F1A0C)

  #define DDRCMDSCH0_CR_DDRCRCMDCONTROLS_PrtEn_OFF                     (17)
  #define DDRCMDSCH0_CR_DDRCRCMDCONTROLS_PrtEn_WID                     ( 1)
  #define DDRCMDSCH0_CR_DDRCRCMDCONTROLS_PrtEn_MSK                     (0x00020000)
  #define DDRCMDSCH0_CR_DDRCRCMDCONTROLS_PrtEn_MIN                     (0)
  #define DDRCMDSCH0_CR_DDRCRCMDCONTROLS_PrtEn_MAX                     (1) // 0x00000001
  #define DDRCMDSCH0_CR_DDRCRCMDCONTROLS_PrtEn_DEF                     (0x00000000)
  #define DDRCMDSCH0_CR_DDRCRCMDCONTROLS_PrtEn_HSH                     (0x01111A0C)

  #define DDRCMDSCH0_CR_DDRCRCMDCONTROLS_AlrtEn_OFF                    (18)
  #define DDRCMDSCH0_CR_DDRCRCMDCONTROLS_AlrtEn_WID                    ( 1)
  #define DDRCMDSCH0_CR_DDRCRCMDCONTROLS_AlrtEn_MSK                    (0x00040000)
  #define DDRCMDSCH0_CR_DDRCRCMDCONTROLS_AlrtEn_MIN                    (0)
  #define DDRCMDSCH0_CR_DDRCRCMDCONTROLS_AlrtEn_MAX                    (1) // 0x00000001
  #define DDRCMDSCH0_CR_DDRCRCMDCONTROLS_AlrtEn_DEF                    (0x00000000)
  #define DDRCMDSCH0_CR_DDRCRCMDCONTROLS_AlrtEn_HSH                    (0x01121A0C)

  #define DDRCMDSCH0_CR_DDRCRCMDCONTROLS_LaDrvEnOvrd_OFF               (19)
  #define DDRCMDSCH0_CR_DDRCRCMDCONTROLS_LaDrvEnOvrd_WID               ( 1)
  #define DDRCMDSCH0_CR_DDRCRCMDCONTROLS_LaDrvEnOvrd_MSK               (0x00080000)
  #define DDRCMDSCH0_CR_DDRCRCMDCONTROLS_LaDrvEnOvrd_MIN               (0)
  #define DDRCMDSCH0_CR_DDRCRCMDCONTROLS_LaDrvEnOvrd_MAX               (1) // 0x00000001
  #define DDRCMDSCH0_CR_DDRCRCMDCONTROLS_LaDrvEnOvrd_DEF               (0x00000000)
  #define DDRCMDSCH0_CR_DDRCRCMDCONTROLS_LaDrvEnOvrd_HSH               (0x01131A0C)

  #define DDRCMDSCH0_CR_DDRCRCMDCONTROLS_DdrCmdSlwDlyByp_OFF           (20)
  #define DDRCMDSCH0_CR_DDRCRCMDCONTROLS_DdrCmdSlwDlyByp_WID           ( 1)
  #define DDRCMDSCH0_CR_DDRCRCMDCONTROLS_DdrCmdSlwDlyByp_MSK           (0x00100000)
  #define DDRCMDSCH0_CR_DDRCRCMDCONTROLS_DdrCmdSlwDlyByp_MIN           (0)
  #define DDRCMDSCH0_CR_DDRCRCMDCONTROLS_DdrCmdSlwDlyByp_MAX           (1) // 0x00000001
  #define DDRCMDSCH0_CR_DDRCRCMDCONTROLS_DdrCmdSlwDlyByp_DEF           (0x00000000)
  #define DDRCMDSCH0_CR_DDRCRCMDCONTROLS_DdrCmdSlwDlyByp_HSH           (0x01141A0C)

  #define DDRCMDSCH0_CR_DDRCRCMDCONTROLS_RxVref_OFF                    (21)
  #define DDRCMDSCH0_CR_DDRCRCMDCONTROLS_RxVref_WID                    ( 6)
  #define DDRCMDSCH0_CR_DDRCRCMDCONTROLS_RxVref_MSK                    (0x07E00000)
  #define DDRCMDSCH0_CR_DDRCRCMDCONTROLS_RxVref_MIN                    (-32)
  #define DDRCMDSCH0_CR_DDRCRCMDCONTROLS_RxVref_MAX                    (31) // 0x0000001F
  #define DDRCMDSCH0_CR_DDRCRCMDCONTROLS_RxVref_DEF                    (0x00000000)
  #define DDRCMDSCH0_CR_DDRCRCMDCONTROLS_RxVref_HSH                    (0x86151A0C)

  #define DDRCMDSCH0_CR_DDRCRCMDCONTROLS_VccddqHi_OFF                  (27)
  #define DDRCMDSCH0_CR_DDRCRCMDCONTROLS_VccddqHi_WID                  ( 1)
  #define DDRCMDSCH0_CR_DDRCRCMDCONTROLS_VccddqHi_MSK                  (0x08000000)
  #define DDRCMDSCH0_CR_DDRCRCMDCONTROLS_VccddqHi_MIN                  (0)
  #define DDRCMDSCH0_CR_DDRCRCMDCONTROLS_VccddqHi_MAX                  (1) // 0x00000001
  #define DDRCMDSCH0_CR_DDRCRCMDCONTROLS_VccddqHi_DEF                  (0x00000000)
  #define DDRCMDSCH0_CR_DDRCRCMDCONTROLS_VccddqHi_HSH                  (0x011B1A0C)

  #define DDRCMDSCH0_CR_DDRCRCMDCONTROLS_DllWeakLock_OFF               (28)
  #define DDRCMDSCH0_CR_DDRCRCMDCONTROLS_DllWeakLock_WID               ( 1)
  #define DDRCMDSCH0_CR_DDRCRCMDCONTROLS_DllWeakLock_MSK               (0x10000000)
  #define DDRCMDSCH0_CR_DDRCRCMDCONTROLS_DllWeakLock_MIN               (0)
  #define DDRCMDSCH0_CR_DDRCRCMDCONTROLS_DllWeakLock_MAX               (1) // 0x00000001
  #define DDRCMDSCH0_CR_DDRCRCMDCONTROLS_DllWeakLock_DEF               (0x00000000)
  #define DDRCMDSCH0_CR_DDRCRCMDCONTROLS_DllWeakLock_HSH               (0x011C1A0C)

  #define DDRCMDSCH0_CR_DDRCRCMDCONTROLS_LPDDR_Mode_OFF                (29)
  #define DDRCMDSCH0_CR_DDRCRCMDCONTROLS_LPDDR_Mode_WID                ( 1)
  #define DDRCMDSCH0_CR_DDRCRCMDCONTROLS_LPDDR_Mode_MSK                (0x20000000)
  #define DDRCMDSCH0_CR_DDRCRCMDCONTROLS_LPDDR_Mode_MIN                (0)
  #define DDRCMDSCH0_CR_DDRCRCMDCONTROLS_LPDDR_Mode_MAX                (1) // 0x00000001
  #define DDRCMDSCH0_CR_DDRCRCMDCONTROLS_LPDDR_Mode_DEF                (0x00000000)
  #define DDRCMDSCH0_CR_DDRCRCMDCONTROLS_LPDDR_Mode_HSH                (0x011D1A0C)

  #define DDRCMDSCH0_CR_DDRCRCMDCONTROLS_LPDdrCAA_Dis_OFF              (30)
  #define DDRCMDSCH0_CR_DDRCRCMDCONTROLS_LPDdrCAA_Dis_WID              ( 1)
  #define DDRCMDSCH0_CR_DDRCRCMDCONTROLS_LPDdrCAA_Dis_MSK              (0x40000000)
  #define DDRCMDSCH0_CR_DDRCRCMDCONTROLS_LPDdrCAA_Dis_MIN              (0)
  #define DDRCMDSCH0_CR_DDRCRCMDCONTROLS_LPDdrCAA_Dis_MAX              (1) // 0x00000001
  #define DDRCMDSCH0_CR_DDRCRCMDCONTROLS_LPDdrCAA_Dis_DEF              (0x00000000)
  #define DDRCMDSCH0_CR_DDRCRCMDCONTROLS_LPDdrCAA_Dis_HSH              (0x011E1A0C)

  #define DDRCMDSCH0_CR_DDRCRCMDCONTROLS_LPDdrCAB_Dis_OFF              (31)
  #define DDRCMDSCH0_CR_DDRCRCMDCONTROLS_LPDdrCAB_Dis_WID              ( 1)
  #define DDRCMDSCH0_CR_DDRCRCMDCONTROLS_LPDdrCAB_Dis_MSK              (0x80000000)
  #define DDRCMDSCH0_CR_DDRCRCMDCONTROLS_LPDdrCAB_Dis_MIN              (0)
  #define DDRCMDSCH0_CR_DDRCRCMDCONTROLS_LPDdrCAB_Dis_MAX              (1) // 0x00000001
  #define DDRCMDSCH0_CR_DDRCRCMDCONTROLS_LPDdrCAB_Dis_DEF              (0x00000000)
  #define DDRCMDSCH0_CR_DDRCRCMDCONTROLS_LPDdrCAB_Dis_HSH              (0x011F1A0C)

#define DDRCMDSCH0_CR_DLLPITESTANDADC_REG                              (0x00001A24)

  #define DDRCMDSCH0_CR_DLLPITESTANDADC_RunTest_OFF                    ( 0)
  #define DDRCMDSCH0_CR_DLLPITESTANDADC_RunTest_WID                    ( 1)
  #define DDRCMDSCH0_CR_DLLPITESTANDADC_RunTest_MSK                    (0x00000001)
  #define DDRCMDSCH0_CR_DLLPITESTANDADC_RunTest_MIN                    (0)
  #define DDRCMDSCH0_CR_DLLPITESTANDADC_RunTest_MAX                    (1) // 0x00000001
  #define DDRCMDSCH0_CR_DLLPITESTANDADC_RunTest_DEF                    (0x00000000)
  #define DDRCMDSCH0_CR_DLLPITESTANDADC_RunTest_HSH                    (0x01001A24)

  #define DDRCMDSCH0_CR_DLLPITESTANDADC_Load_OFF                       ( 1)
  #define DDRCMDSCH0_CR_DLLPITESTANDADC_Load_WID                       ( 1)
  #define DDRCMDSCH0_CR_DLLPITESTANDADC_Load_MSK                       (0x00000002)
  #define DDRCMDSCH0_CR_DLLPITESTANDADC_Load_MIN                       (0)
  #define DDRCMDSCH0_CR_DLLPITESTANDADC_Load_MAX                       (1) // 0x00000001
  #define DDRCMDSCH0_CR_DLLPITESTANDADC_Load_DEF                       (0x00000000)
  #define DDRCMDSCH0_CR_DLLPITESTANDADC_Load_HSH                       (0x01011A24)

  #define DDRCMDSCH0_CR_DLLPITESTANDADC_ModeHVM_OFF                    ( 2)
  #define DDRCMDSCH0_CR_DLLPITESTANDADC_ModeHVM_WID                    ( 1)
  #define DDRCMDSCH0_CR_DLLPITESTANDADC_ModeHVM_MSK                    (0x00000004)
  #define DDRCMDSCH0_CR_DLLPITESTANDADC_ModeHVM_MIN                    (0)
  #define DDRCMDSCH0_CR_DLLPITESTANDADC_ModeHVM_MAX                    (1) // 0x00000001
  #define DDRCMDSCH0_CR_DLLPITESTANDADC_ModeHVM_DEF                    (0x00000000)
  #define DDRCMDSCH0_CR_DLLPITESTANDADC_ModeHVM_HSH                    (0x01021A24)

  #define DDRCMDSCH0_CR_DLLPITESTANDADC_ModeDV_OFF                     ( 3)
  #define DDRCMDSCH0_CR_DLLPITESTANDADC_ModeDV_WID                     ( 1)
  #define DDRCMDSCH0_CR_DLLPITESTANDADC_ModeDV_MSK                     (0x00000008)
  #define DDRCMDSCH0_CR_DLLPITESTANDADC_ModeDV_MIN                     (0)
  #define DDRCMDSCH0_CR_DLLPITESTANDADC_ModeDV_MAX                     (1) // 0x00000001
  #define DDRCMDSCH0_CR_DLLPITESTANDADC_ModeDV_DEF                     (0x00000000)
  #define DDRCMDSCH0_CR_DLLPITESTANDADC_ModeDV_HSH                     (0x01031A24)

  #define DDRCMDSCH0_CR_DLLPITESTANDADC_CalCfdl_OFF                    ( 4)
  #define DDRCMDSCH0_CR_DLLPITESTANDADC_CalCfdl_WID                    ( 1)
  #define DDRCMDSCH0_CR_DLLPITESTANDADC_CalCfdl_MSK                    (0x00000010)
  #define DDRCMDSCH0_CR_DLLPITESTANDADC_CalCfdl_MIN                    (0)
  #define DDRCMDSCH0_CR_DLLPITESTANDADC_CalCfdl_MAX                    (1) // 0x00000001
  #define DDRCMDSCH0_CR_DLLPITESTANDADC_CalCfdl_DEF                    (0x00000000)
  #define DDRCMDSCH0_CR_DLLPITESTANDADC_CalCfdl_HSH                    (0x01041A24)

  #define DDRCMDSCH0_CR_DLLPITESTANDADC_LoadCount_OFF                  ( 5)
  #define DDRCMDSCH0_CR_DLLPITESTANDADC_LoadCount_WID                  (10)
  #define DDRCMDSCH0_CR_DLLPITESTANDADC_LoadCount_MSK                  (0x00007FE0)
  #define DDRCMDSCH0_CR_DLLPITESTANDADC_LoadCount_MIN                  (0)
  #define DDRCMDSCH0_CR_DLLPITESTANDADC_LoadCount_MAX                  (1023) // 0x000003FF
  #define DDRCMDSCH0_CR_DLLPITESTANDADC_LoadCount_DEF                  (0x00000000)
  #define DDRCMDSCH0_CR_DLLPITESTANDADC_LoadCount_HSH                  (0x0A051A24)

  #define DDRCMDSCH0_CR_DLLPITESTANDADC_CountStatus_OFF                (15)
  #define DDRCMDSCH0_CR_DLLPITESTANDADC_CountStatus_WID                (10)
  #define DDRCMDSCH0_CR_DLLPITESTANDADC_CountStatus_MSK                (0x01FF8000)
  #define DDRCMDSCH0_CR_DLLPITESTANDADC_CountStatus_MIN                (0)
  #define DDRCMDSCH0_CR_DLLPITESTANDADC_CountStatus_MAX                (1023) // 0x000003FF
  #define DDRCMDSCH0_CR_DLLPITESTANDADC_CountStatus_DEF                (0x00000000)
  #define DDRCMDSCH0_CR_DLLPITESTANDADC_CountStatus_HSH                (0x0A0F1A24)

  #define DDRCMDSCH0_CR_DLLPITESTANDADC_PhaseDrvPwrSavOn_OFF           (25)
  #define DDRCMDSCH0_CR_DLLPITESTANDADC_PhaseDrvPwrSavOn_WID           ( 1)
  #define DDRCMDSCH0_CR_DLLPITESTANDADC_PhaseDrvPwrSavOn_MSK           (0x02000000)
  #define DDRCMDSCH0_CR_DLLPITESTANDADC_PhaseDrvPwrSavOn_MIN           (0)
  #define DDRCMDSCH0_CR_DLLPITESTANDADC_PhaseDrvPwrSavOn_MAX           (1) // 0x00000001
  #define DDRCMDSCH0_CR_DLLPITESTANDADC_PhaseDrvPwrSavOn_DEF           (0x00000000)
  #define DDRCMDSCH0_CR_DLLPITESTANDADC_PhaseDrvPwrSavOn_HSH           (0x01191A24)

  #define DDRCMDSCH0_CR_DLLPITESTANDADC_Spare_OFF                      (26)
  #define DDRCMDSCH0_CR_DLLPITESTANDADC_Spare_WID                      ( 6)
  #define DDRCMDSCH0_CR_DLLPITESTANDADC_Spare_MSK                      (0xFC000000)
  #define DDRCMDSCH0_CR_DLLPITESTANDADC_Spare_MIN                      (0)
  #define DDRCMDSCH0_CR_DLLPITESTANDADC_Spare_MAX                      (63) // 0x0000003F
  #define DDRCMDSCH0_CR_DLLPITESTANDADC_Spare_DEF                      (0x00000000)
  #define DDRCMDSCH0_CR_DLLPITESTANDADC_Spare_HSH                      (0x061A1A24)

#define DDRCMDSCH1_CR_DDRCRCMDCOMP_REG                                 (0x00001B00)

  #define DDRCMDSCH1_CR_DDRCRCMDCOMP_Scomp_OFF                         ( 0)
  #define DDRCMDSCH1_CR_DDRCRCMDCOMP_Scomp_WID                         ( 6)
  #define DDRCMDSCH1_CR_DDRCRCMDCOMP_Scomp_MSK                         (0x0000003F)
  #define DDRCMDSCH1_CR_DDRCRCMDCOMP_Scomp_MIN                         (0)
  #define DDRCMDSCH1_CR_DDRCRCMDCOMP_Scomp_MAX                         (63) // 0x0000003F
  #define DDRCMDSCH1_CR_DDRCRCMDCOMP_Scomp_DEF                         (0x00000000)
  #define DDRCMDSCH1_CR_DDRCRCMDCOMP_Scomp_HSH                         (0x06001B00)

  #define DDRCMDSCH1_CR_DDRCRCMDCOMP_TcoComp_OFF                       ( 6)
  #define DDRCMDSCH1_CR_DDRCRCMDCOMP_TcoComp_WID                       ( 6)
  #define DDRCMDSCH1_CR_DDRCRCMDCOMP_TcoComp_MSK                       (0x00000FC0)
  #define DDRCMDSCH1_CR_DDRCRCMDCOMP_TcoComp_MIN                       (0)
  #define DDRCMDSCH1_CR_DDRCRCMDCOMP_TcoComp_MAX                       (63) // 0x0000003F
  #define DDRCMDSCH1_CR_DDRCRCMDCOMP_TcoComp_DEF                       (0x00000000)
  #define DDRCMDSCH1_CR_DDRCRCMDCOMP_TcoComp_HSH                       (0x06061B00)

  #define DDRCMDSCH1_CR_DDRCRCMDCOMP_RcompDrvUp_OFF                    (12)
  #define DDRCMDSCH1_CR_DDRCRCMDCOMP_RcompDrvUp_WID                    ( 6)
  #define DDRCMDSCH1_CR_DDRCRCMDCOMP_RcompDrvUp_MSK                    (0x0003F000)
  #define DDRCMDSCH1_CR_DDRCRCMDCOMP_RcompDrvUp_MIN                    (0)
  #define DDRCMDSCH1_CR_DDRCRCMDCOMP_RcompDrvUp_MAX                    (63) // 0x0000003F
  #define DDRCMDSCH1_CR_DDRCRCMDCOMP_RcompDrvUp_DEF                    (0x00000000)
  #define DDRCMDSCH1_CR_DDRCRCMDCOMP_RcompDrvUp_HSH                    (0x060C1B00)

  #define DDRCMDSCH1_CR_DDRCRCMDCOMP_RcompDrvDown_OFF                  (18)
  #define DDRCMDSCH1_CR_DDRCRCMDCOMP_RcompDrvDown_WID                  ( 6)
  #define DDRCMDSCH1_CR_DDRCRCMDCOMP_RcompDrvDown_MSK                  (0x00FC0000)
  #define DDRCMDSCH1_CR_DDRCRCMDCOMP_RcompDrvDown_MIN                  (0)
  #define DDRCMDSCH1_CR_DDRCRCMDCOMP_RcompDrvDown_MAX                  (63) // 0x0000003F
  #define DDRCMDSCH1_CR_DDRCRCMDCOMP_RcompDrvDown_DEF                  (0x00000000)
  #define DDRCMDSCH1_CR_DDRCRCMDCOMP_RcompDrvDown_HSH                  (0x06121B00)

  #define DDRCMDSCH1_CR_DDRCRCMDCOMP_Spare_OFF                         (24)
  #define DDRCMDSCH1_CR_DDRCRCMDCOMP_Spare_WID                         ( 8)
  #define DDRCMDSCH1_CR_DDRCRCMDCOMP_Spare_MSK                         (0xFF000000)
  #define DDRCMDSCH1_CR_DDRCRCMDCOMP_Spare_MIN                         (0)
  #define DDRCMDSCH1_CR_DDRCRCMDCOMP_Spare_MAX                         (255) // 0x000000FF
  #define DDRCMDSCH1_CR_DDRCRCMDCOMP_Spare_DEF                         (0x00000004)
  #define DDRCMDSCH1_CR_DDRCRCMDCOMP_Spare_HSH                         (0x08181B00)

#define DDRCMDSCH1_CR_DDRCRCMDCOMPOFFSET_REG                           (0x00001B04)

  #define DDRCMDSCH1_CR_DDRCRCMDCOMPOFFSET_ScompOffset_OFF             ( 0)
  #define DDRCMDSCH1_CR_DDRCRCMDCOMPOFFSET_ScompOffset_WID             ( 5)
  #define DDRCMDSCH1_CR_DDRCRCMDCOMPOFFSET_ScompOffset_MSK             (0x0000001F)
  #define DDRCMDSCH1_CR_DDRCRCMDCOMPOFFSET_ScompOffset_MIN             (-16)
  #define DDRCMDSCH1_CR_DDRCRCMDCOMPOFFSET_ScompOffset_MAX             (15) // 0x0000000F
  #define DDRCMDSCH1_CR_DDRCRCMDCOMPOFFSET_ScompOffset_DEF             (0x00000000)
  #define DDRCMDSCH1_CR_DDRCRCMDCOMPOFFSET_ScompOffset_HSH             (0x85001B04)

  #define DDRCMDSCH1_CR_DDRCRCMDCOMPOFFSET_TcoCompOffset_OFF           ( 5)
  #define DDRCMDSCH1_CR_DDRCRCMDCOMPOFFSET_TcoCompOffset_WID           ( 4)
  #define DDRCMDSCH1_CR_DDRCRCMDCOMPOFFSET_TcoCompOffset_MSK           (0x000001E0)
  #define DDRCMDSCH1_CR_DDRCRCMDCOMPOFFSET_TcoCompOffset_MIN           (-8)
  #define DDRCMDSCH1_CR_DDRCRCMDCOMPOFFSET_TcoCompOffset_MAX           (7) // 0x00000007
  #define DDRCMDSCH1_CR_DDRCRCMDCOMPOFFSET_TcoCompOffset_DEF           (0x00000000)
  #define DDRCMDSCH1_CR_DDRCRCMDCOMPOFFSET_TcoCompOffset_HSH           (0x84051B04)

  #define DDRCMDSCH1_CR_DDRCRCMDCOMPOFFSET_RcompDrvUpOffset_OFF        ( 9)
  #define DDRCMDSCH1_CR_DDRCRCMDCOMPOFFSET_RcompDrvUpOffset_WID        ( 4)
  #define DDRCMDSCH1_CR_DDRCRCMDCOMPOFFSET_RcompDrvUpOffset_MSK        (0x00001E00)
  #define DDRCMDSCH1_CR_DDRCRCMDCOMPOFFSET_RcompDrvUpOffset_MIN        (-8)
  #define DDRCMDSCH1_CR_DDRCRCMDCOMPOFFSET_RcompDrvUpOffset_MAX        (7) // 0x00000007
  #define DDRCMDSCH1_CR_DDRCRCMDCOMPOFFSET_RcompDrvUpOffset_DEF        (0x00000000)
  #define DDRCMDSCH1_CR_DDRCRCMDCOMPOFFSET_RcompDrvUpOffset_HSH        (0x84091B04)

  #define DDRCMDSCH1_CR_DDRCRCMDCOMPOFFSET_RcompDrvDownOffset_OFF      (13)
  #define DDRCMDSCH1_CR_DDRCRCMDCOMPOFFSET_RcompDrvDownOffset_WID      ( 4)
  #define DDRCMDSCH1_CR_DDRCRCMDCOMPOFFSET_RcompDrvDownOffset_MSK      (0x0001E000)
  #define DDRCMDSCH1_CR_DDRCRCMDCOMPOFFSET_RcompDrvDownOffset_MIN      (-8)
  #define DDRCMDSCH1_CR_DDRCRCMDCOMPOFFSET_RcompDrvDownOffset_MAX      (7) // 0x00000007
  #define DDRCMDSCH1_CR_DDRCRCMDCOMPOFFSET_RcompDrvDownOffset_DEF      (0x00000000)
  #define DDRCMDSCH1_CR_DDRCRCMDCOMPOFFSET_RcompDrvDownOffset_HSH      (0x840D1B04)

  #define DDRCMDSCH1_CR_DDRCRCMDCOMPOFFSET_Spare_OFF                   (17)
  #define DDRCMDSCH1_CR_DDRCRCMDCOMPOFFSET_Spare_WID                   (15)
  #define DDRCMDSCH1_CR_DDRCRCMDCOMPOFFSET_Spare_MSK                   (0xFFFE0000)
  #define DDRCMDSCH1_CR_DDRCRCMDCOMPOFFSET_Spare_MIN                   (0)
  #define DDRCMDSCH1_CR_DDRCRCMDCOMPOFFSET_Spare_MAX                   (32767) // 0x00007FFF
  #define DDRCMDSCH1_CR_DDRCRCMDCOMPOFFSET_Spare_DEF                   (0x00000000)
  #define DDRCMDSCH1_CR_DDRCRCMDCOMPOFFSET_Spare_HSH                   (0x0F111B04)

#define DDRCMDSCH1_CR_DDRCRCMDPICODING_REG                             (0x00001B08)

  #define DDRCMDSCH1_CR_DDRCRCMDPICODING_CmdPi0Code_OFF                ( 0)
  #define DDRCMDSCH1_CR_DDRCRCMDPICODING_CmdPi0Code_WID                ( 7)
  #define DDRCMDSCH1_CR_DDRCRCMDPICODING_CmdPi0Code_MSK                (0x0000007F)
  #define DDRCMDSCH1_CR_DDRCRCMDPICODING_CmdPi0Code_MIN                (0)
  #define DDRCMDSCH1_CR_DDRCRCMDPICODING_CmdPi0Code_MAX                (127) // 0x0000007F
  #define DDRCMDSCH1_CR_DDRCRCMDPICODING_CmdPi0Code_DEF                (0x00000000)
  #define DDRCMDSCH1_CR_DDRCRCMDPICODING_CmdPi0Code_HSH                (0x07001B08)

  #define DDRCMDSCH1_CR_DDRCRCMDPICODING_CmdPi1Code_OFF                ( 7)
  #define DDRCMDSCH1_CR_DDRCRCMDPICODING_CmdPi1Code_WID                ( 7)
  #define DDRCMDSCH1_CR_DDRCRCMDPICODING_CmdPi1Code_MSK                (0x00003F80)
  #define DDRCMDSCH1_CR_DDRCRCMDPICODING_CmdPi1Code_MIN                (0)
  #define DDRCMDSCH1_CR_DDRCRCMDPICODING_CmdPi1Code_MAX                (127) // 0x0000007F
  #define DDRCMDSCH1_CR_DDRCRCMDPICODING_CmdPi1Code_DEF                (0x00000000)
  #define DDRCMDSCH1_CR_DDRCRCMDPICODING_CmdPi1Code_HSH                (0x07071B08)

  #define DDRCMDSCH1_CR_DDRCRCMDPICODING_Spare_OFF                     (14)
  #define DDRCMDSCH1_CR_DDRCRCMDPICODING_Spare_WID                     (18)
  #define DDRCMDSCH1_CR_DDRCRCMDPICODING_Spare_MSK                     (0xFFFFC000)
  #define DDRCMDSCH1_CR_DDRCRCMDPICODING_Spare_MIN                     (0)
  #define DDRCMDSCH1_CR_DDRCRCMDPICODING_Spare_MAX                     (262143) // 0x0003FFFF
  #define DDRCMDSCH1_CR_DDRCRCMDPICODING_Spare_DEF                     (0x00000000)
  #define DDRCMDSCH1_CR_DDRCRCMDPICODING_Spare_HSH                     (0x120E1B08)

#define DDRCMDSCH1_CR_DDRCRCMDCONTROLS_REG                             (0x00001B0C)

  #define DDRCMDSCH1_CR_DDRCRCMDCONTROLS_RefPi_OFF                     ( 0)
  #define DDRCMDSCH1_CR_DDRCRCMDCONTROLS_RefPi_WID                     ( 4)
  #define DDRCMDSCH1_CR_DDRCRCMDCONTROLS_RefPi_MSK                     (0x0000000F)
  #define DDRCMDSCH1_CR_DDRCRCMDCONTROLS_RefPi_MIN                     (-8)
  #define DDRCMDSCH1_CR_DDRCRCMDCONTROLS_RefPi_MAX                     (7) // 0x00000007
  #define DDRCMDSCH1_CR_DDRCRCMDCONTROLS_RefPi_DEF                     (0x00000000)
  #define DDRCMDSCH1_CR_DDRCRCMDCONTROLS_RefPi_HSH                     (0x84001B0C)

  #define DDRCMDSCH1_CR_DDRCRCMDCONTROLS_DllMask_OFF                   ( 4)
  #define DDRCMDSCH1_CR_DDRCRCMDCONTROLS_DllMask_WID                   ( 2)
  #define DDRCMDSCH1_CR_DDRCRCMDCONTROLS_DllMask_MSK                   (0x00000030)
  #define DDRCMDSCH1_CR_DDRCRCMDCONTROLS_DllMask_MIN                   (0)
  #define DDRCMDSCH1_CR_DDRCRCMDCONTROLS_DllMask_MAX                   (3) // 0x00000003
  #define DDRCMDSCH1_CR_DDRCRCMDCONTROLS_DllMask_DEF                   (0x00000000)
  #define DDRCMDSCH1_CR_DDRCRCMDCONTROLS_DllMask_HSH                   (0x02041B0C)

  #define DDRCMDSCH1_CR_DDRCRCMDCONTROLS_ClkGateDisable_OFF            ( 6)
  #define DDRCMDSCH1_CR_DDRCRCMDCONTROLS_ClkGateDisable_WID            ( 1)
  #define DDRCMDSCH1_CR_DDRCRCMDCONTROLS_ClkGateDisable_MSK            (0x00000040)
  #define DDRCMDSCH1_CR_DDRCRCMDCONTROLS_ClkGateDisable_MIN            (0)
  #define DDRCMDSCH1_CR_DDRCRCMDCONTROLS_ClkGateDisable_MAX            (1) // 0x00000001
  #define DDRCMDSCH1_CR_DDRCRCMDCONTROLS_ClkGateDisable_DEF            (0x00000000)
  #define DDRCMDSCH1_CR_DDRCRCMDCONTROLS_ClkGateDisable_HSH            (0x01061B0C)

  #define DDRCMDSCH1_CR_DDRCRCMDCONTROLS_TxOn_OFF                      ( 7)
  #define DDRCMDSCH1_CR_DDRCRCMDCONTROLS_TxOn_WID                      ( 1)
  #define DDRCMDSCH1_CR_DDRCRCMDCONTROLS_TxOn_MSK                      (0x00000080)
  #define DDRCMDSCH1_CR_DDRCRCMDCONTROLS_TxOn_MIN                      (0)
  #define DDRCMDSCH1_CR_DDRCRCMDCONTROLS_TxOn_MAX                      (1) // 0x00000001
  #define DDRCMDSCH1_CR_DDRCRCMDCONTROLS_TxOn_DEF                      (0x00000000)
  #define DDRCMDSCH1_CR_DDRCRCMDCONTROLS_TxOn_HSH                      (0x01071B0C)

  #define DDRCMDSCH1_CR_DDRCRCMDCONTROLS_IntClkOn_OFF                  ( 8)
  #define DDRCMDSCH1_CR_DDRCRCMDCONTROLS_IntClkOn_WID                  ( 1)
  #define DDRCMDSCH1_CR_DDRCRCMDCONTROLS_IntClkOn_MSK                  (0x00000100)
  #define DDRCMDSCH1_CR_DDRCRCMDCONTROLS_IntClkOn_MIN                  (0)
  #define DDRCMDSCH1_CR_DDRCRCMDCONTROLS_IntClkOn_MAX                  (1) // 0x00000001
  #define DDRCMDSCH1_CR_DDRCRCMDCONTROLS_IntClkOn_DEF                  (0x00000000)
  #define DDRCMDSCH1_CR_DDRCRCMDCONTROLS_IntClkOn_HSH                  (0x01081B0C)

  #define DDRCMDSCH1_CR_DDRCRCMDCONTROLS_RepClkOn_OFF                  ( 9)
  #define DDRCMDSCH1_CR_DDRCRCMDCONTROLS_RepClkOn_WID                  ( 1)
  #define DDRCMDSCH1_CR_DDRCRCMDCONTROLS_RepClkOn_MSK                  (0x00000200)
  #define DDRCMDSCH1_CR_DDRCRCMDCONTROLS_RepClkOn_MIN                  (0)
  #define DDRCMDSCH1_CR_DDRCRCMDCONTROLS_RepClkOn_MAX                  (1) // 0x00000001
  #define DDRCMDSCH1_CR_DDRCRCMDCONTROLS_RepClkOn_DEF                  (0x00000000)
  #define DDRCMDSCH1_CR_DDRCRCMDCONTROLS_RepClkOn_HSH                  (0x01091B0C)

  #define DDRCMDSCH1_CR_DDRCRCMDCONTROLS_IolbOrMisr_OFF                (10)
  #define DDRCMDSCH1_CR_DDRCRCMDCONTROLS_IolbOrMisr_WID                ( 1)
  #define DDRCMDSCH1_CR_DDRCRCMDCONTROLS_IolbOrMisr_MSK                (0x00000400)
  #define DDRCMDSCH1_CR_DDRCRCMDCONTROLS_IolbOrMisr_MIN                (0)
  #define DDRCMDSCH1_CR_DDRCRCMDCONTROLS_IolbOrMisr_MAX                (1) // 0x00000001
  #define DDRCMDSCH1_CR_DDRCRCMDCONTROLS_IolbOrMisr_DEF                (0x00000000)
  #define DDRCMDSCH1_CR_DDRCRCMDCONTROLS_IolbOrMisr_HSH                (0x010A1B0C)

  #define DDRCMDSCH1_CR_DDRCRCMDCONTROLS_IolbHold_OFF                  (11)
  #define DDRCMDSCH1_CR_DDRCRCMDCONTROLS_IolbHold_WID                  ( 1)
  #define DDRCMDSCH1_CR_DDRCRCMDCONTROLS_IolbHold_MSK                  (0x00000800)
  #define DDRCMDSCH1_CR_DDRCRCMDCONTROLS_IolbHold_MIN                  (0)
  #define DDRCMDSCH1_CR_DDRCRCMDCONTROLS_IolbHold_MAX                  (1) // 0x00000001
  #define DDRCMDSCH1_CR_DDRCRCMDCONTROLS_IolbHold_DEF                  (0x00000000)
  #define DDRCMDSCH1_CR_DDRCRCMDCONTROLS_IolbHold_HSH                  (0x010B1B0C)

  #define DDRCMDSCH1_CR_DDRCRCMDCONTROLS_OdtMode_OFF                   (12)
  #define DDRCMDSCH1_CR_DDRCRCMDCONTROLS_OdtMode_WID                   ( 1)
  #define DDRCMDSCH1_CR_DDRCRCMDCONTROLS_OdtMode_MSK                   (0x00001000)
  #define DDRCMDSCH1_CR_DDRCRCMDCONTROLS_OdtMode_MIN                   (0)
  #define DDRCMDSCH1_CR_DDRCRCMDCONTROLS_OdtMode_MAX                   (1) // 0x00000001
  #define DDRCMDSCH1_CR_DDRCRCMDCONTROLS_OdtMode_DEF                   (0x00000000)
  #define DDRCMDSCH1_CR_DDRCRCMDCONTROLS_OdtMode_HSH                   (0x010C1B0C)

  #define DDRCMDSCH1_CR_DDRCRCMDCONTROLS_CmdTxEq_OFF                   (13)
  #define DDRCMDSCH1_CR_DDRCRCMDCONTROLS_CmdTxEq_WID                   ( 2)
  #define DDRCMDSCH1_CR_DDRCRCMDCONTROLS_CmdTxEq_MSK                   (0x00006000)
  #define DDRCMDSCH1_CR_DDRCRCMDCONTROLS_CmdTxEq_MIN                   (0)
  #define DDRCMDSCH1_CR_DDRCRCMDCONTROLS_CmdTxEq_MAX                   (3) // 0x00000003
  #define DDRCMDSCH1_CR_DDRCRCMDCONTROLS_CmdTxEq_DEF                   (0x00000000)
  #define DDRCMDSCH1_CR_DDRCRCMDCONTROLS_CmdTxEq_HSH                   (0x020D1B0C)

  #define DDRCMDSCH1_CR_DDRCRCMDCONTROLS_EarlyWeakDrive_OFF            (15)
  #define DDRCMDSCH1_CR_DDRCRCMDCONTROLS_EarlyWeakDrive_WID            ( 2)
  #define DDRCMDSCH1_CR_DDRCRCMDCONTROLS_EarlyWeakDrive_MSK            (0x00018000)
  #define DDRCMDSCH1_CR_DDRCRCMDCONTROLS_EarlyWeakDrive_MIN            (0)
  #define DDRCMDSCH1_CR_DDRCRCMDCONTROLS_EarlyWeakDrive_MAX            (3) // 0x00000003
  #define DDRCMDSCH1_CR_DDRCRCMDCONTROLS_EarlyWeakDrive_DEF            (0x00000000)
  #define DDRCMDSCH1_CR_DDRCRCMDCONTROLS_EarlyWeakDrive_HSH            (0x020F1B0C)

  #define DDRCMDSCH1_CR_DDRCRCMDCONTROLS_PrtEn_OFF                     (17)
  #define DDRCMDSCH1_CR_DDRCRCMDCONTROLS_PrtEn_WID                     ( 1)
  #define DDRCMDSCH1_CR_DDRCRCMDCONTROLS_PrtEn_MSK                     (0x00020000)
  #define DDRCMDSCH1_CR_DDRCRCMDCONTROLS_PrtEn_MIN                     (0)
  #define DDRCMDSCH1_CR_DDRCRCMDCONTROLS_PrtEn_MAX                     (1) // 0x00000001
  #define DDRCMDSCH1_CR_DDRCRCMDCONTROLS_PrtEn_DEF                     (0x00000000)
  #define DDRCMDSCH1_CR_DDRCRCMDCONTROLS_PrtEn_HSH                     (0x01111B0C)

  #define DDRCMDSCH1_CR_DDRCRCMDCONTROLS_AlrtEn_OFF                    (18)
  #define DDRCMDSCH1_CR_DDRCRCMDCONTROLS_AlrtEn_WID                    ( 1)
  #define DDRCMDSCH1_CR_DDRCRCMDCONTROLS_AlrtEn_MSK                    (0x00040000)
  #define DDRCMDSCH1_CR_DDRCRCMDCONTROLS_AlrtEn_MIN                    (0)
  #define DDRCMDSCH1_CR_DDRCRCMDCONTROLS_AlrtEn_MAX                    (1) // 0x00000001
  #define DDRCMDSCH1_CR_DDRCRCMDCONTROLS_AlrtEn_DEF                    (0x00000000)
  #define DDRCMDSCH1_CR_DDRCRCMDCONTROLS_AlrtEn_HSH                    (0x01121B0C)

  #define DDRCMDSCH1_CR_DDRCRCMDCONTROLS_LaDrvEnOvrd_OFF               (19)
  #define DDRCMDSCH1_CR_DDRCRCMDCONTROLS_LaDrvEnOvrd_WID               ( 1)
  #define DDRCMDSCH1_CR_DDRCRCMDCONTROLS_LaDrvEnOvrd_MSK               (0x00080000)
  #define DDRCMDSCH1_CR_DDRCRCMDCONTROLS_LaDrvEnOvrd_MIN               (0)
  #define DDRCMDSCH1_CR_DDRCRCMDCONTROLS_LaDrvEnOvrd_MAX               (1) // 0x00000001
  #define DDRCMDSCH1_CR_DDRCRCMDCONTROLS_LaDrvEnOvrd_DEF               (0x00000000)
  #define DDRCMDSCH1_CR_DDRCRCMDCONTROLS_LaDrvEnOvrd_HSH               (0x01131B0C)

  #define DDRCMDSCH1_CR_DDRCRCMDCONTROLS_DdrCmdSlwDlyByp_OFF           (20)
  #define DDRCMDSCH1_CR_DDRCRCMDCONTROLS_DdrCmdSlwDlyByp_WID           ( 1)
  #define DDRCMDSCH1_CR_DDRCRCMDCONTROLS_DdrCmdSlwDlyByp_MSK           (0x00100000)
  #define DDRCMDSCH1_CR_DDRCRCMDCONTROLS_DdrCmdSlwDlyByp_MIN           (0)
  #define DDRCMDSCH1_CR_DDRCRCMDCONTROLS_DdrCmdSlwDlyByp_MAX           (1) // 0x00000001
  #define DDRCMDSCH1_CR_DDRCRCMDCONTROLS_DdrCmdSlwDlyByp_DEF           (0x00000000)
  #define DDRCMDSCH1_CR_DDRCRCMDCONTROLS_DdrCmdSlwDlyByp_HSH           (0x01141B0C)

  #define DDRCMDSCH1_CR_DDRCRCMDCONTROLS_RxVref_OFF                    (21)
  #define DDRCMDSCH1_CR_DDRCRCMDCONTROLS_RxVref_WID                    ( 6)
  #define DDRCMDSCH1_CR_DDRCRCMDCONTROLS_RxVref_MSK                    (0x07E00000)
  #define DDRCMDSCH1_CR_DDRCRCMDCONTROLS_RxVref_MIN                    (-32)
  #define DDRCMDSCH1_CR_DDRCRCMDCONTROLS_RxVref_MAX                    (31) // 0x0000001F
  #define DDRCMDSCH1_CR_DDRCRCMDCONTROLS_RxVref_DEF                    (0x00000000)
  #define DDRCMDSCH1_CR_DDRCRCMDCONTROLS_RxVref_HSH                    (0x86151B0C)

  #define DDRCMDSCH1_CR_DDRCRCMDCONTROLS_VccddqHi_OFF                  (27)
  #define DDRCMDSCH1_CR_DDRCRCMDCONTROLS_VccddqHi_WID                  ( 1)
  #define DDRCMDSCH1_CR_DDRCRCMDCONTROLS_VccddqHi_MSK                  (0x08000000)
  #define DDRCMDSCH1_CR_DDRCRCMDCONTROLS_VccddqHi_MIN                  (0)
  #define DDRCMDSCH1_CR_DDRCRCMDCONTROLS_VccddqHi_MAX                  (1) // 0x00000001
  #define DDRCMDSCH1_CR_DDRCRCMDCONTROLS_VccddqHi_DEF                  (0x00000000)
  #define DDRCMDSCH1_CR_DDRCRCMDCONTROLS_VccddqHi_HSH                  (0x011B1B0C)

  #define DDRCMDSCH1_CR_DDRCRCMDCONTROLS_DllWeakLock_OFF               (28)
  #define DDRCMDSCH1_CR_DDRCRCMDCONTROLS_DllWeakLock_WID               ( 1)
  #define DDRCMDSCH1_CR_DDRCRCMDCONTROLS_DllWeakLock_MSK               (0x10000000)
  #define DDRCMDSCH1_CR_DDRCRCMDCONTROLS_DllWeakLock_MIN               (0)
  #define DDRCMDSCH1_CR_DDRCRCMDCONTROLS_DllWeakLock_MAX               (1) // 0x00000001
  #define DDRCMDSCH1_CR_DDRCRCMDCONTROLS_DllWeakLock_DEF               (0x00000000)
  #define DDRCMDSCH1_CR_DDRCRCMDCONTROLS_DllWeakLock_HSH               (0x011C1B0C)

  #define DDRCMDSCH1_CR_DDRCRCMDCONTROLS_LPDDR_Mode_OFF                (29)
  #define DDRCMDSCH1_CR_DDRCRCMDCONTROLS_LPDDR_Mode_WID                ( 1)
  #define DDRCMDSCH1_CR_DDRCRCMDCONTROLS_LPDDR_Mode_MSK                (0x20000000)
  #define DDRCMDSCH1_CR_DDRCRCMDCONTROLS_LPDDR_Mode_MIN                (0)
  #define DDRCMDSCH1_CR_DDRCRCMDCONTROLS_LPDDR_Mode_MAX                (1) // 0x00000001
  #define DDRCMDSCH1_CR_DDRCRCMDCONTROLS_LPDDR_Mode_DEF                (0x00000000)
  #define DDRCMDSCH1_CR_DDRCRCMDCONTROLS_LPDDR_Mode_HSH                (0x011D1B0C)

  #define DDRCMDSCH1_CR_DDRCRCMDCONTROLS_LPDdrCAA_Dis_OFF              (30)
  #define DDRCMDSCH1_CR_DDRCRCMDCONTROLS_LPDdrCAA_Dis_WID              ( 1)
  #define DDRCMDSCH1_CR_DDRCRCMDCONTROLS_LPDdrCAA_Dis_MSK              (0x40000000)
  #define DDRCMDSCH1_CR_DDRCRCMDCONTROLS_LPDdrCAA_Dis_MIN              (0)
  #define DDRCMDSCH1_CR_DDRCRCMDCONTROLS_LPDdrCAA_Dis_MAX              (1) // 0x00000001
  #define DDRCMDSCH1_CR_DDRCRCMDCONTROLS_LPDdrCAA_Dis_DEF              (0x00000000)
  #define DDRCMDSCH1_CR_DDRCRCMDCONTROLS_LPDdrCAA_Dis_HSH              (0x011E1B0C)

  #define DDRCMDSCH1_CR_DDRCRCMDCONTROLS_LPDdrCAB_Dis_OFF              (31)
  #define DDRCMDSCH1_CR_DDRCRCMDCONTROLS_LPDdrCAB_Dis_WID              ( 1)
  #define DDRCMDSCH1_CR_DDRCRCMDCONTROLS_LPDdrCAB_Dis_MSK              (0x80000000)
  #define DDRCMDSCH1_CR_DDRCRCMDCONTROLS_LPDdrCAB_Dis_MIN              (0)
  #define DDRCMDSCH1_CR_DDRCRCMDCONTROLS_LPDdrCAB_Dis_MAX              (1) // 0x00000001
  #define DDRCMDSCH1_CR_DDRCRCMDCONTROLS_LPDdrCAB_Dis_DEF              (0x00000000)
  #define DDRCMDSCH1_CR_DDRCRCMDCONTROLS_LPDdrCAB_Dis_HSH              (0x011F1B0C)

#define DDRCMDSCH1_CR_DLLPITESTANDADC_REG                              (0x00001B24)

  #define DDRCMDSCH1_CR_DLLPITESTANDADC_RunTest_OFF                    ( 0)
  #define DDRCMDSCH1_CR_DLLPITESTANDADC_RunTest_WID                    ( 1)
  #define DDRCMDSCH1_CR_DLLPITESTANDADC_RunTest_MSK                    (0x00000001)
  #define DDRCMDSCH1_CR_DLLPITESTANDADC_RunTest_MIN                    (0)
  #define DDRCMDSCH1_CR_DLLPITESTANDADC_RunTest_MAX                    (1) // 0x00000001
  #define DDRCMDSCH1_CR_DLLPITESTANDADC_RunTest_DEF                    (0x00000000)
  #define DDRCMDSCH1_CR_DLLPITESTANDADC_RunTest_HSH                    (0x01001B24)

  #define DDRCMDSCH1_CR_DLLPITESTANDADC_Load_OFF                       ( 1)
  #define DDRCMDSCH1_CR_DLLPITESTANDADC_Load_WID                       ( 1)
  #define DDRCMDSCH1_CR_DLLPITESTANDADC_Load_MSK                       (0x00000002)
  #define DDRCMDSCH1_CR_DLLPITESTANDADC_Load_MIN                       (0)
  #define DDRCMDSCH1_CR_DLLPITESTANDADC_Load_MAX                       (1) // 0x00000001
  #define DDRCMDSCH1_CR_DLLPITESTANDADC_Load_DEF                       (0x00000000)
  #define DDRCMDSCH1_CR_DLLPITESTANDADC_Load_HSH                       (0x01011B24)

  #define DDRCMDSCH1_CR_DLLPITESTANDADC_ModeHVM_OFF                    ( 2)
  #define DDRCMDSCH1_CR_DLLPITESTANDADC_ModeHVM_WID                    ( 1)
  #define DDRCMDSCH1_CR_DLLPITESTANDADC_ModeHVM_MSK                    (0x00000004)
  #define DDRCMDSCH1_CR_DLLPITESTANDADC_ModeHVM_MIN                    (0)
  #define DDRCMDSCH1_CR_DLLPITESTANDADC_ModeHVM_MAX                    (1) // 0x00000001
  #define DDRCMDSCH1_CR_DLLPITESTANDADC_ModeHVM_DEF                    (0x00000000)
  #define DDRCMDSCH1_CR_DLLPITESTANDADC_ModeHVM_HSH                    (0x01021B24)

  #define DDRCMDSCH1_CR_DLLPITESTANDADC_ModeDV_OFF                     ( 3)
  #define DDRCMDSCH1_CR_DLLPITESTANDADC_ModeDV_WID                     ( 1)
  #define DDRCMDSCH1_CR_DLLPITESTANDADC_ModeDV_MSK                     (0x00000008)
  #define DDRCMDSCH1_CR_DLLPITESTANDADC_ModeDV_MIN                     (0)
  #define DDRCMDSCH1_CR_DLLPITESTANDADC_ModeDV_MAX                     (1) // 0x00000001
  #define DDRCMDSCH1_CR_DLLPITESTANDADC_ModeDV_DEF                     (0x00000000)
  #define DDRCMDSCH1_CR_DLLPITESTANDADC_ModeDV_HSH                     (0x01031B24)

  #define DDRCMDSCH1_CR_DLLPITESTANDADC_CalCfdl_OFF                    ( 4)
  #define DDRCMDSCH1_CR_DLLPITESTANDADC_CalCfdl_WID                    ( 1)
  #define DDRCMDSCH1_CR_DLLPITESTANDADC_CalCfdl_MSK                    (0x00000010)
  #define DDRCMDSCH1_CR_DLLPITESTANDADC_CalCfdl_MIN                    (0)
  #define DDRCMDSCH1_CR_DLLPITESTANDADC_CalCfdl_MAX                    (1) // 0x00000001
  #define DDRCMDSCH1_CR_DLLPITESTANDADC_CalCfdl_DEF                    (0x00000000)
  #define DDRCMDSCH1_CR_DLLPITESTANDADC_CalCfdl_HSH                    (0x01041B24)

  #define DDRCMDSCH1_CR_DLLPITESTANDADC_LoadCount_OFF                  ( 5)
  #define DDRCMDSCH1_CR_DLLPITESTANDADC_LoadCount_WID                  (10)
  #define DDRCMDSCH1_CR_DLLPITESTANDADC_LoadCount_MSK                  (0x00007FE0)
  #define DDRCMDSCH1_CR_DLLPITESTANDADC_LoadCount_MIN                  (0)
  #define DDRCMDSCH1_CR_DLLPITESTANDADC_LoadCount_MAX                  (1023) // 0x000003FF
  #define DDRCMDSCH1_CR_DLLPITESTANDADC_LoadCount_DEF                  (0x00000000)
  #define DDRCMDSCH1_CR_DLLPITESTANDADC_LoadCount_HSH                  (0x0A051B24)

  #define DDRCMDSCH1_CR_DLLPITESTANDADC_CountStatus_OFF                (15)
  #define DDRCMDSCH1_CR_DLLPITESTANDADC_CountStatus_WID                (10)
  #define DDRCMDSCH1_CR_DLLPITESTANDADC_CountStatus_MSK                (0x01FF8000)
  #define DDRCMDSCH1_CR_DLLPITESTANDADC_CountStatus_MIN                (0)
  #define DDRCMDSCH1_CR_DLLPITESTANDADC_CountStatus_MAX                (1023) // 0x000003FF
  #define DDRCMDSCH1_CR_DLLPITESTANDADC_CountStatus_DEF                (0x00000000)
  #define DDRCMDSCH1_CR_DLLPITESTANDADC_CountStatus_HSH                (0x0A0F1B24)

  #define DDRCMDSCH1_CR_DLLPITESTANDADC_PhaseDrvPwrSavOn_OFF           (25)
  #define DDRCMDSCH1_CR_DLLPITESTANDADC_PhaseDrvPwrSavOn_WID           ( 1)
  #define DDRCMDSCH1_CR_DLLPITESTANDADC_PhaseDrvPwrSavOn_MSK           (0x02000000)
  #define DDRCMDSCH1_CR_DLLPITESTANDADC_PhaseDrvPwrSavOn_MIN           (0)
  #define DDRCMDSCH1_CR_DLLPITESTANDADC_PhaseDrvPwrSavOn_MAX           (1) // 0x00000001
  #define DDRCMDSCH1_CR_DLLPITESTANDADC_PhaseDrvPwrSavOn_DEF           (0x00000000)
  #define DDRCMDSCH1_CR_DLLPITESTANDADC_PhaseDrvPwrSavOn_HSH           (0x01191B24)

  #define DDRCMDSCH1_CR_DLLPITESTANDADC_Spare_OFF                      (26)
  #define DDRCMDSCH1_CR_DLLPITESTANDADC_Spare_WID                      ( 6)
  #define DDRCMDSCH1_CR_DLLPITESTANDADC_Spare_MSK                      (0xFC000000)
  #define DDRCMDSCH1_CR_DLLPITESTANDADC_Spare_MIN                      (0)
  #define DDRCMDSCH1_CR_DLLPITESTANDADC_Spare_MAX                      (63) // 0x0000003F
  #define DDRCMDSCH1_CR_DLLPITESTANDADC_Spare_DEF                      (0x00000000)
  #define DDRCMDSCH1_CR_DLLPITESTANDADC_Spare_HSH                      (0x061A1B24)

#define DDRCTLCH0_CR_DDRCRCTLCOMP_REG                                  (0x00001C10)

  #define DDRCTLCH0_CR_DDRCRCTLCOMP_Scomp_OFF                          ( 0)
  #define DDRCTLCH0_CR_DDRCRCTLCOMP_Scomp_WID                          ( 6)
  #define DDRCTLCH0_CR_DDRCRCTLCOMP_Scomp_MSK                          (0x0000003F)
  #define DDRCTLCH0_CR_DDRCRCTLCOMP_Scomp_MIN                          (0)
  #define DDRCTLCH0_CR_DDRCRCTLCOMP_Scomp_MAX                          (63) // 0x0000003F
  #define DDRCTLCH0_CR_DDRCRCTLCOMP_Scomp_DEF                          (0x00000000)
  #define DDRCTLCH0_CR_DDRCRCTLCOMP_Scomp_HSH                          (0x06001C10)

  #define DDRCTLCH0_CR_DDRCRCTLCOMP_TcoComp_OFF                        ( 6)
  #define DDRCTLCH0_CR_DDRCRCTLCOMP_TcoComp_WID                        ( 6)
  #define DDRCTLCH0_CR_DDRCRCTLCOMP_TcoComp_MSK                        (0x00000FC0)
  #define DDRCTLCH0_CR_DDRCRCTLCOMP_TcoComp_MIN                        (0)
  #define DDRCTLCH0_CR_DDRCRCTLCOMP_TcoComp_MAX                        (63) // 0x0000003F
  #define DDRCTLCH0_CR_DDRCRCTLCOMP_TcoComp_DEF                        (0x00000000)
  #define DDRCTLCH0_CR_DDRCRCTLCOMP_TcoComp_HSH                        (0x06061C10)

  #define DDRCTLCH0_CR_DDRCRCTLCOMP_RcompDrvUp_OFF                     (12)
  #define DDRCTLCH0_CR_DDRCRCTLCOMP_RcompDrvUp_WID                     ( 6)
  #define DDRCTLCH0_CR_DDRCRCTLCOMP_RcompDrvUp_MSK                     (0x0003F000)
  #define DDRCTLCH0_CR_DDRCRCTLCOMP_RcompDrvUp_MIN                     (0)
  #define DDRCTLCH0_CR_DDRCRCTLCOMP_RcompDrvUp_MAX                     (63) // 0x0000003F
  #define DDRCTLCH0_CR_DDRCRCTLCOMP_RcompDrvUp_DEF                     (0x00000000)
  #define DDRCTLCH0_CR_DDRCRCTLCOMP_RcompDrvUp_HSH                     (0x060C1C10)

  #define DDRCTLCH0_CR_DDRCRCTLCOMP_RcompDrvDown_OFF                   (18)
  #define DDRCTLCH0_CR_DDRCRCTLCOMP_RcompDrvDown_WID                   ( 6)
  #define DDRCTLCH0_CR_DDRCRCTLCOMP_RcompDrvDown_MSK                   (0x00FC0000)
  #define DDRCTLCH0_CR_DDRCRCTLCOMP_RcompDrvDown_MIN                   (0)
  #define DDRCTLCH0_CR_DDRCRCTLCOMP_RcompDrvDown_MAX                   (63) // 0x0000003F
  #define DDRCTLCH0_CR_DDRCRCTLCOMP_RcompDrvDown_DEF                   (0x00000000)
  #define DDRCTLCH0_CR_DDRCRCTLCOMP_RcompDrvDown_HSH                   (0x06121C10)

  #define DDRCTLCH0_CR_DDRCRCTLCOMP_Spare_OFF                          (24)
  #define DDRCTLCH0_CR_DDRCRCTLCOMP_Spare_WID                          ( 8)
  #define DDRCTLCH0_CR_DDRCRCTLCOMP_Spare_MSK                          (0xFF000000)
  #define DDRCTLCH0_CR_DDRCRCTLCOMP_Spare_MIN                          (0)
  #define DDRCTLCH0_CR_DDRCRCTLCOMP_Spare_MAX                          (255) // 0x000000FF
  #define DDRCTLCH0_CR_DDRCRCTLCOMP_Spare_DEF                          (0x00000000)
  #define DDRCTLCH0_CR_DDRCRCTLCOMP_Spare_HSH                          (0x08181C10)

#define DDRCTLCH0_CR_DDRCRCTLCOMPOFFSET_REG                            (0x00001C14)

  #define DDRCTLCH0_CR_DDRCRCTLCOMPOFFSET_ScompOffset_OFF              ( 0)
  #define DDRCTLCH0_CR_DDRCRCTLCOMPOFFSET_ScompOffset_WID              ( 5)
  #define DDRCTLCH0_CR_DDRCRCTLCOMPOFFSET_ScompOffset_MSK              (0x0000001F)
  #define DDRCTLCH0_CR_DDRCRCTLCOMPOFFSET_ScompOffset_MIN              (-16)
  #define DDRCTLCH0_CR_DDRCRCTLCOMPOFFSET_ScompOffset_MAX              (15) // 0x0000000F
  #define DDRCTLCH0_CR_DDRCRCTLCOMPOFFSET_ScompOffset_DEF              (0x00000000)
  #define DDRCTLCH0_CR_DDRCRCTLCOMPOFFSET_ScompOffset_HSH              (0x85001C14)

  #define DDRCTLCH0_CR_DDRCRCTLCOMPOFFSET_TcoCompOffset_OFF            ( 5)
  #define DDRCTLCH0_CR_DDRCRCTLCOMPOFFSET_TcoCompOffset_WID            ( 4)
  #define DDRCTLCH0_CR_DDRCRCTLCOMPOFFSET_TcoCompOffset_MSK            (0x000001E0)
  #define DDRCTLCH0_CR_DDRCRCTLCOMPOFFSET_TcoCompOffset_MIN            (-8)
  #define DDRCTLCH0_CR_DDRCRCTLCOMPOFFSET_TcoCompOffset_MAX            (7) // 0x00000007
  #define DDRCTLCH0_CR_DDRCRCTLCOMPOFFSET_TcoCompOffset_DEF            (0x00000000)
  #define DDRCTLCH0_CR_DDRCRCTLCOMPOFFSET_TcoCompOffset_HSH            (0x84051C14)

  #define DDRCTLCH0_CR_DDRCRCTLCOMPOFFSET_RcompDrvUpOffset_OFF         ( 9)
  #define DDRCTLCH0_CR_DDRCRCTLCOMPOFFSET_RcompDrvUpOffset_WID         ( 4)
  #define DDRCTLCH0_CR_DDRCRCTLCOMPOFFSET_RcompDrvUpOffset_MSK         (0x00001E00)
  #define DDRCTLCH0_CR_DDRCRCTLCOMPOFFSET_RcompDrvUpOffset_MIN         (-8)
  #define DDRCTLCH0_CR_DDRCRCTLCOMPOFFSET_RcompDrvUpOffset_MAX         (7) // 0x00000007
  #define DDRCTLCH0_CR_DDRCRCTLCOMPOFFSET_RcompDrvUpOffset_DEF         (0x00000000)
  #define DDRCTLCH0_CR_DDRCRCTLCOMPOFFSET_RcompDrvUpOffset_HSH         (0x84091C14)

  #define DDRCTLCH0_CR_DDRCRCTLCOMPOFFSET_RcompDrvDownOffset_OFF       (13)
  #define DDRCTLCH0_CR_DDRCRCTLCOMPOFFSET_RcompDrvDownOffset_WID       ( 4)
  #define DDRCTLCH0_CR_DDRCRCTLCOMPOFFSET_RcompDrvDownOffset_MSK       (0x0001E000)
  #define DDRCTLCH0_CR_DDRCRCTLCOMPOFFSET_RcompDrvDownOffset_MIN       (-8)
  #define DDRCTLCH0_CR_DDRCRCTLCOMPOFFSET_RcompDrvDownOffset_MAX       (7) // 0x00000007
  #define DDRCTLCH0_CR_DDRCRCTLCOMPOFFSET_RcompDrvDownOffset_DEF       (0x00000000)
  #define DDRCTLCH0_CR_DDRCRCTLCOMPOFFSET_RcompDrvDownOffset_HSH       (0x840D1C14)

  #define DDRCTLCH0_CR_DDRCRCTLCOMPOFFSET_Spare_OFF                    (17)
  #define DDRCTLCH0_CR_DDRCRCTLCOMPOFFSET_Spare_WID                    (15)
  #define DDRCTLCH0_CR_DDRCRCTLCOMPOFFSET_Spare_MSK                    (0xFFFE0000)
  #define DDRCTLCH0_CR_DDRCRCTLCOMPOFFSET_Spare_MIN                    (0)
  #define DDRCTLCH0_CR_DDRCRCTLCOMPOFFSET_Spare_MAX                    (32767) // 0x00007FFF
  #define DDRCTLCH0_CR_DDRCRCTLCOMPOFFSET_Spare_DEF                    (0x00000000)
  #define DDRCTLCH0_CR_DDRCRCTLCOMPOFFSET_Spare_HSH                    (0x0F111C14)

#define DDRCTLCH0_CR_DDRCRCTLPICODING_REG                              (0x00001C18)

  #define DDRCTLCH0_CR_DDRCRCTLPICODING_CtlPiCode0_OFF                 ( 0)
  #define DDRCTLCH0_CR_DDRCRCTLPICODING_CtlPiCode0_WID                 ( 7)
  #define DDRCTLCH0_CR_DDRCRCTLPICODING_CtlPiCode0_MSK                 (0x0000007F)
  #define DDRCTLCH0_CR_DDRCRCTLPICODING_CtlPiCode0_MIN                 (0)
  #define DDRCTLCH0_CR_DDRCRCTLPICODING_CtlPiCode0_MAX                 (127) // 0x0000007F
  #define DDRCTLCH0_CR_DDRCRCTLPICODING_CtlPiCode0_DEF                 (0x00000000)
  #define DDRCTLCH0_CR_DDRCRCTLPICODING_CtlPiCode0_HSH                 (0x07001C18)

  #define DDRCTLCH0_CR_DDRCRCTLPICODING_CtlPiCode1_OFF                 ( 7)
  #define DDRCTLCH0_CR_DDRCRCTLPICODING_CtlPiCode1_WID                 ( 7)
  #define DDRCTLCH0_CR_DDRCRCTLPICODING_CtlPiCode1_MSK                 (0x00003F80)
  #define DDRCTLCH0_CR_DDRCRCTLPICODING_CtlPiCode1_MIN                 (0)
  #define DDRCTLCH0_CR_DDRCRCTLPICODING_CtlPiCode1_MAX                 (127) // 0x0000007F
  #define DDRCTLCH0_CR_DDRCRCTLPICODING_CtlPiCode1_DEF                 (0x00000000)
  #define DDRCTLCH0_CR_DDRCRCTLPICODING_CtlPiCode1_HSH                 (0x07071C18)

  #define DDRCTLCH0_CR_DDRCRCTLPICODING_CtlPiCode2_OFF                 (14)
  #define DDRCTLCH0_CR_DDRCRCTLPICODING_CtlPiCode2_WID                 ( 7)
  #define DDRCTLCH0_CR_DDRCRCTLPICODING_CtlPiCode2_MSK                 (0x001FC000)
  #define DDRCTLCH0_CR_DDRCRCTLPICODING_CtlPiCode2_MIN                 (0)
  #define DDRCTLCH0_CR_DDRCRCTLPICODING_CtlPiCode2_MAX                 (127) // 0x0000007F
  #define DDRCTLCH0_CR_DDRCRCTLPICODING_CtlPiCode2_DEF                 (0x00000000)
  #define DDRCTLCH0_CR_DDRCRCTLPICODING_CtlPiCode2_HSH                 (0x070E1C18)

  #define DDRCTLCH0_CR_DDRCRCTLPICODING_CtlPiCode3_OFF                 (21)
  #define DDRCTLCH0_CR_DDRCRCTLPICODING_CtlPiCode3_WID                 ( 7)
  #define DDRCTLCH0_CR_DDRCRCTLPICODING_CtlPiCode3_MSK                 (0x0FE00000)
  #define DDRCTLCH0_CR_DDRCRCTLPICODING_CtlPiCode3_MIN                 (0)
  #define DDRCTLCH0_CR_DDRCRCTLPICODING_CtlPiCode3_MAX                 (127) // 0x0000007F
  #define DDRCTLCH0_CR_DDRCRCTLPICODING_CtlPiCode3_DEF                 (0x00000000)
  #define DDRCTLCH0_CR_DDRCRCTLPICODING_CtlPiCode3_HSH                 (0x07151C18)

  #define DDRCTLCH0_CR_DDRCRCTLPICODING_CtlXoverEnable_OFF             (28)
  #define DDRCTLCH0_CR_DDRCRCTLPICODING_CtlXoverEnable_WID             ( 1)
  #define DDRCTLCH0_CR_DDRCRCTLPICODING_CtlXoverEnable_MSK             (0x10000000)
  #define DDRCTLCH0_CR_DDRCRCTLPICODING_CtlXoverEnable_MIN             (0)
  #define DDRCTLCH0_CR_DDRCRCTLPICODING_CtlXoverEnable_MAX             (1) // 0x00000001
  #define DDRCTLCH0_CR_DDRCRCTLPICODING_CtlXoverEnable_DEF             (0x00000000)
  #define DDRCTLCH0_CR_DDRCRCTLPICODING_CtlXoverEnable_HSH             (0x011C1C18)

  #define DDRCTLCH0_CR_DDRCRCTLPICODING_Spare_OFF                      (29)
  #define DDRCTLCH0_CR_DDRCRCTLPICODING_Spare_WID                      ( 3)
  #define DDRCTLCH0_CR_DDRCRCTLPICODING_Spare_MSK                      (0xE0000000)
  #define DDRCTLCH0_CR_DDRCRCTLPICODING_Spare_MIN                      (0)
  #define DDRCTLCH0_CR_DDRCRCTLPICODING_Spare_MAX                      (7) // 0x00000007
  #define DDRCTLCH0_CR_DDRCRCTLPICODING_Spare_DEF                      (0x00000000)
  #define DDRCTLCH0_CR_DDRCRCTLPICODING_Spare_HSH                      (0x031D1C18)

#define DDRCTLCH0_CR_DDRCRCTLCONTROLS_REG                              (0x00001C1C)

  #define DDRCTLCH0_CR_DDRCRCTLCONTROLS_RefPi_OFF                      ( 0)
  #define DDRCTLCH0_CR_DDRCRCTLCONTROLS_RefPi_WID                      ( 4)
  #define DDRCTLCH0_CR_DDRCRCTLCONTROLS_RefPi_MSK                      (0x0000000F)
  #define DDRCTLCH0_CR_DDRCRCTLCONTROLS_RefPi_MIN                      (-8)
  #define DDRCTLCH0_CR_DDRCRCTLCONTROLS_RefPi_MAX                      (7) // 0x00000007
  #define DDRCTLCH0_CR_DDRCRCTLCONTROLS_RefPi_DEF                      (0x00000000)
  #define DDRCTLCH0_CR_DDRCRCTLCONTROLS_RefPi_HSH                      (0x84001C1C)

  #define DDRCTLCH0_CR_DDRCRCTLCONTROLS_DllMask_OFF                    ( 4)
  #define DDRCTLCH0_CR_DDRCRCTLCONTROLS_DllMask_WID                    ( 2)
  #define DDRCTLCH0_CR_DDRCRCTLCONTROLS_DllMask_MSK                    (0x00000030)
  #define DDRCTLCH0_CR_DDRCRCTLCONTROLS_DllMask_MIN                    (0)
  #define DDRCTLCH0_CR_DDRCRCTLCONTROLS_DllMask_MAX                    (3) // 0x00000003
  #define DDRCTLCH0_CR_DDRCRCTLCONTROLS_DllMask_DEF                    (0x00000000)
  #define DDRCTLCH0_CR_DDRCRCTLCONTROLS_DllMask_HSH                    (0x02041C1C)

  #define DDRCTLCH0_CR_DDRCRCTLCONTROLS_ClkGateDisable_OFF             ( 6)
  #define DDRCTLCH0_CR_DDRCRCTLCONTROLS_ClkGateDisable_WID             ( 1)
  #define DDRCTLCH0_CR_DDRCRCTLCONTROLS_ClkGateDisable_MSK             (0x00000040)
  #define DDRCTLCH0_CR_DDRCRCTLCONTROLS_ClkGateDisable_MIN             (0)
  #define DDRCTLCH0_CR_DDRCRCTLCONTROLS_ClkGateDisable_MAX             (1) // 0x00000001
  #define DDRCTLCH0_CR_DDRCRCTLCONTROLS_ClkGateDisable_DEF             (0x00000000)
  #define DDRCTLCH0_CR_DDRCRCTLCONTROLS_ClkGateDisable_HSH             (0x01061C1C)

  #define DDRCTLCH0_CR_DDRCRCTLCONTROLS_TxOn_OFF                       ( 7)
  #define DDRCTLCH0_CR_DDRCRCTLCONTROLS_TxOn_WID                       ( 1)
  #define DDRCTLCH0_CR_DDRCRCTLCONTROLS_TxOn_MSK                       (0x00000080)
  #define DDRCTLCH0_CR_DDRCRCTLCONTROLS_TxOn_MIN                       (0)
  #define DDRCTLCH0_CR_DDRCRCTLCONTROLS_TxOn_MAX                       (1) // 0x00000001
  #define DDRCTLCH0_CR_DDRCRCTLCONTROLS_TxOn_DEF                       (0x00000000)
  #define DDRCTLCH0_CR_DDRCRCTLCONTROLS_TxOn_HSH                       (0x01071C1C)

  #define DDRCTLCH0_CR_DDRCRCTLCONTROLS_IntClkOn_OFF                   ( 8)
  #define DDRCTLCH0_CR_DDRCRCTLCONTROLS_IntClkOn_WID                   ( 1)
  #define DDRCTLCH0_CR_DDRCRCTLCONTROLS_IntClkOn_MSK                   (0x00000100)
  #define DDRCTLCH0_CR_DDRCRCTLCONTROLS_IntClkOn_MIN                   (0)
  #define DDRCTLCH0_CR_DDRCRCTLCONTROLS_IntClkOn_MAX                   (1) // 0x00000001
  #define DDRCTLCH0_CR_DDRCRCTLCONTROLS_IntClkOn_DEF                   (0x00000000)
  #define DDRCTLCH0_CR_DDRCRCTLCONTROLS_IntClkOn_HSH                   (0x01081C1C)

  #define DDRCTLCH0_CR_DDRCRCTLCONTROLS_RepClkOn_OFF                   ( 9)
  #define DDRCTLCH0_CR_DDRCRCTLCONTROLS_RepClkOn_WID                   ( 1)
  #define DDRCTLCH0_CR_DDRCRCTLCONTROLS_RepClkOn_MSK                   (0x00000200)
  #define DDRCTLCH0_CR_DDRCRCTLCONTROLS_RepClkOn_MIN                   (0)
  #define DDRCTLCH0_CR_DDRCRCTLCONTROLS_RepClkOn_MAX                   (1) // 0x00000001
  #define DDRCTLCH0_CR_DDRCRCTLCONTROLS_RepClkOn_DEF                   (0x00000000)
  #define DDRCTLCH0_CR_DDRCRCTLCONTROLS_RepClkOn_HSH                   (0x01091C1C)

  #define DDRCTLCH0_CR_DDRCRCTLCONTROLS_IolbOrMisr_OFF                 (10)
  #define DDRCTLCH0_CR_DDRCRCTLCONTROLS_IolbOrMisr_WID                 ( 1)
  #define DDRCTLCH0_CR_DDRCRCTLCONTROLS_IolbOrMisr_MSK                 (0x00000400)
  #define DDRCTLCH0_CR_DDRCRCTLCONTROLS_IolbOrMisr_MIN                 (0)
  #define DDRCTLCH0_CR_DDRCRCTLCONTROLS_IolbOrMisr_MAX                 (1) // 0x00000001
  #define DDRCTLCH0_CR_DDRCRCTLCONTROLS_IolbOrMisr_DEF                 (0x00000000)
  #define DDRCTLCH0_CR_DDRCRCTLCONTROLS_IolbOrMisr_HSH                 (0x010A1C1C)

  #define DDRCTLCH0_CR_DDRCRCTLCONTROLS_IOLBHold_OFF                   (11)
  #define DDRCTLCH0_CR_DDRCRCTLCONTROLS_IOLBHold_WID                   ( 1)
  #define DDRCTLCH0_CR_DDRCRCTLCONTROLS_IOLBHold_MSK                   (0x00000800)
  #define DDRCTLCH0_CR_DDRCRCTLCONTROLS_IOLBHold_MIN                   (0)
  #define DDRCTLCH0_CR_DDRCRCTLCONTROLS_IOLBHold_MAX                   (1) // 0x00000001
  #define DDRCTLCH0_CR_DDRCRCTLCONTROLS_IOLBHold_DEF                   (0x00000000)
  #define DDRCTLCH0_CR_DDRCRCTLCONTROLS_IOLBHold_HSH                   (0x010B1C1C)

  #define DDRCTLCH0_CR_DDRCRCTLCONTROLS_OdtMode_OFF                    (12)
  #define DDRCTLCH0_CR_DDRCRCTLCONTROLS_OdtMode_WID                    ( 1)
  #define DDRCTLCH0_CR_DDRCRCTLCONTROLS_OdtMode_MSK                    (0x00001000)
  #define DDRCTLCH0_CR_DDRCRCTLCONTROLS_OdtMode_MIN                    (0)
  #define DDRCTLCH0_CR_DDRCRCTLCONTROLS_OdtMode_MAX                    (1) // 0x00000001
  #define DDRCTLCH0_CR_DDRCRCTLCONTROLS_OdtMode_DEF                    (0x00000000)
  #define DDRCTLCH0_CR_DDRCRCTLCONTROLS_OdtMode_HSH                    (0x010C1C1C)

  #define DDRCTLCH0_CR_DDRCRCTLCONTROLS_CmdTxEq_OFF                    (13)
  #define DDRCTLCH0_CR_DDRCRCTLCONTROLS_CmdTxEq_WID                    ( 2)
  #define DDRCTLCH0_CR_DDRCRCTLCONTROLS_CmdTxEq_MSK                    (0x00006000)
  #define DDRCTLCH0_CR_DDRCRCTLCONTROLS_CmdTxEq_MIN                    (0)
  #define DDRCTLCH0_CR_DDRCRCTLCONTROLS_CmdTxEq_MAX                    (3) // 0x00000003
  #define DDRCTLCH0_CR_DDRCRCTLCONTROLS_CmdTxEq_DEF                    (0x00000000)
  #define DDRCTLCH0_CR_DDRCRCTLCONTROLS_CmdTxEq_HSH                    (0x020D1C1C)

  #define DDRCTLCH0_CR_DDRCRCTLCONTROLS_EarlyWeakDrive_OFF             (15)
  #define DDRCTLCH0_CR_DDRCRCTLCONTROLS_EarlyWeakDrive_WID             ( 2)
  #define DDRCTLCH0_CR_DDRCRCTLCONTROLS_EarlyWeakDrive_MSK             (0x00018000)
  #define DDRCTLCH0_CR_DDRCRCTLCONTROLS_EarlyWeakDrive_MIN             (0)
  #define DDRCTLCH0_CR_DDRCRCTLCONTROLS_EarlyWeakDrive_MAX             (3) // 0x00000003
  #define DDRCTLCH0_CR_DDRCRCTLCONTROLS_EarlyWeakDrive_DEF             (0x00000000)
  #define DDRCTLCH0_CR_DDRCRCTLCONTROLS_EarlyWeakDrive_HSH             (0x020F1C1C)

  #define DDRCTLCH0_CR_DDRCRCTLCONTROLS_CtlTxEq_OFF                    (17)
  #define DDRCTLCH0_CR_DDRCRCTLCONTROLS_CtlTxEq_WID                    ( 2)
  #define DDRCTLCH0_CR_DDRCRCTLCONTROLS_CtlTxEq_MSK                    (0x00060000)
  #define DDRCTLCH0_CR_DDRCRCTLCONTROLS_CtlTxEq_MIN                    (0)
  #define DDRCTLCH0_CR_DDRCRCTLCONTROLS_CtlTxEq_MAX                    (3) // 0x00000003
  #define DDRCTLCH0_CR_DDRCRCTLCONTROLS_CtlTxEq_DEF                    (0x00000000)
  #define DDRCTLCH0_CR_DDRCRCTLCONTROLS_CtlTxEq_HSH                    (0x02111C1C)

  #define DDRCTLCH0_CR_DDRCRCTLCONTROLS_CtlSRDrv_OFF                   (19)
  #define DDRCTLCH0_CR_DDRCRCTLCONTROLS_CtlSRDrv_WID                   ( 2)
  #define DDRCTLCH0_CR_DDRCRCTLCONTROLS_CtlSRDrv_MSK                   (0x00180000)
  #define DDRCTLCH0_CR_DDRCRCTLCONTROLS_CtlSRDrv_MIN                   (0)
  #define DDRCTLCH0_CR_DDRCRCTLCONTROLS_CtlSRDrv_MAX                   (3) // 0x00000003
  #define DDRCTLCH0_CR_DDRCRCTLCONTROLS_CtlSRDrv_DEF                   (0x00000000)
  #define DDRCTLCH0_CR_DDRCRCTLCONTROLS_CtlSRDrv_HSH                   (0x02131C1C)

  #define DDRCTLCH0_CR_DDRCRCTLCONTROLS_RxVref_OFF                     (21)
  #define DDRCTLCH0_CR_DDRCRCTLCONTROLS_RxVref_WID                     ( 6)
  #define DDRCTLCH0_CR_DDRCRCTLCONTROLS_RxVref_MSK                     (0x07E00000)
  #define DDRCTLCH0_CR_DDRCRCTLCONTROLS_RxVref_MIN                     (-32)
  #define DDRCTLCH0_CR_DDRCRCTLCONTROLS_RxVref_MAX                     (31) // 0x0000001F
  #define DDRCTLCH0_CR_DDRCRCTLCONTROLS_RxVref_DEF                     (0x00000000)
  #define DDRCTLCH0_CR_DDRCRCTLCONTROLS_RxVref_HSH                     (0x86151C1C)

  #define DDRCTLCH0_CR_DDRCRCTLCONTROLS_VccddqHi_OFF                   (27)
  #define DDRCTLCH0_CR_DDRCRCTLCONTROLS_VccddqHi_WID                   ( 1)
  #define DDRCTLCH0_CR_DDRCRCTLCONTROLS_VccddqHi_MSK                   (0x08000000)
  #define DDRCTLCH0_CR_DDRCRCTLCONTROLS_VccddqHi_MIN                   (0)
  #define DDRCTLCH0_CR_DDRCRCTLCONTROLS_VccddqHi_MAX                   (1) // 0x00000001
  #define DDRCTLCH0_CR_DDRCRCTLCONTROLS_VccddqHi_DEF                   (0x00000000)
  #define DDRCTLCH0_CR_DDRCRCTLCONTROLS_VccddqHi_HSH                   (0x011B1C1C)

  #define DDRCTLCH0_CR_DDRCRCTLCONTROLS_DllWeakLock_OFF                (28)
  #define DDRCTLCH0_CR_DDRCRCTLCONTROLS_DllWeakLock_WID                ( 1)
  #define DDRCTLCH0_CR_DDRCRCTLCONTROLS_DllWeakLock_MSK                (0x10000000)
  #define DDRCTLCH0_CR_DDRCRCTLCONTROLS_DllWeakLock_MIN                (0)
  #define DDRCTLCH0_CR_DDRCRCTLCONTROLS_DllWeakLock_MAX                (1) // 0x00000001
  #define DDRCTLCH0_CR_DDRCRCTLCONTROLS_DllWeakLock_DEF                (0x00000000)
  #define DDRCTLCH0_CR_DDRCRCTLCONTROLS_DllWeakLock_HSH                (0x011C1C1C)

  #define DDRCTLCH0_CR_DDRCRCTLCONTROLS_LPDDR_Mode_OFF                 (29)
  #define DDRCTLCH0_CR_DDRCRCTLCONTROLS_LPDDR_Mode_WID                 ( 1)
  #define DDRCTLCH0_CR_DDRCRCTLCONTROLS_LPDDR_Mode_MSK                 (0x20000000)
  #define DDRCTLCH0_CR_DDRCRCTLCONTROLS_LPDDR_Mode_MIN                 (0)
  #define DDRCTLCH0_CR_DDRCRCTLCONTROLS_LPDDR_Mode_MAX                 (1) // 0x00000001
  #define DDRCTLCH0_CR_DDRCRCTLCONTROLS_LPDDR_Mode_DEF                 (0x00000000)
  #define DDRCTLCH0_CR_DDRCRCTLCONTROLS_LPDDR_Mode_HSH                 (0x011D1C1C)

  #define DDRCTLCH0_CR_DDRCRCTLCONTROLS_LaDrvEnOvrd_OFF                (30)
  #define DDRCTLCH0_CR_DDRCRCTLCONTROLS_LaDrvEnOvrd_WID                ( 1)
  #define DDRCTLCH0_CR_DDRCRCTLCONTROLS_LaDrvEnOvrd_MSK                (0x40000000)
  #define DDRCTLCH0_CR_DDRCRCTLCONTROLS_LaDrvEnOvrd_MIN                (0)
  #define DDRCTLCH0_CR_DDRCRCTLCONTROLS_LaDrvEnOvrd_MAX                (1) // 0x00000001
  #define DDRCTLCH0_CR_DDRCRCTLCONTROLS_LaDrvEnOvrd_DEF                (0x00000000)
  #define DDRCTLCH0_CR_DDRCRCTLCONTROLS_LaDrvEnOvrd_HSH                (0x011E1C1C)

  #define DDRCTLCH0_CR_DDRCRCTLCONTROLS_LPDdrCAA_Dis_OFF               (31)
  #define DDRCTLCH0_CR_DDRCRCTLCONTROLS_LPDdrCAA_Dis_WID               ( 1)
  #define DDRCTLCH0_CR_DDRCRCTLCONTROLS_LPDdrCAA_Dis_MSK               (0x80000000)
  #define DDRCTLCH0_CR_DDRCRCTLCONTROLS_LPDdrCAA_Dis_MIN               (0)
  #define DDRCTLCH0_CR_DDRCRCTLCONTROLS_LPDdrCAA_Dis_MAX               (1) // 0x00000001
  #define DDRCTLCH0_CR_DDRCRCTLCONTROLS_LPDdrCAA_Dis_DEF               (0x00000000)
  #define DDRCTLCH0_CR_DDRCRCTLCONTROLS_LPDdrCAA_Dis_HSH               (0x011F1C1C)

#define DDRCTLCH0_CR_DDRCRCTLRANKSUSED_REG                             (0x00001C20)

  #define DDRCTLCH0_CR_DDRCRCTLRANKSUSED_RankEn_OFF                    ( 0)
  #define DDRCTLCH0_CR_DDRCRCTLRANKSUSED_RankEn_WID                    ( 4)
  #define DDRCTLCH0_CR_DDRCRCTLRANKSUSED_RankEn_MSK                    (0x0000000F)
  #define DDRCTLCH0_CR_DDRCRCTLRANKSUSED_RankEn_MIN                    (0)
  #define DDRCTLCH0_CR_DDRCRCTLRANKSUSED_RankEn_MAX                    (15) // 0x0000000F
  #define DDRCTLCH0_CR_DDRCRCTLRANKSUSED_RankEn_DEF                    (0x0000000F)
  #define DDRCTLCH0_CR_DDRCRCTLRANKSUSED_RankEn_HSH                    (0x04001C20)

  #define DDRCTLCH0_CR_DDRCRCTLRANKSUSED_OdtDisable_OFF                ( 4)
  #define DDRCTLCH0_CR_DDRCRCTLRANKSUSED_OdtDisable_WID                ( 2)
  #define DDRCTLCH0_CR_DDRCRCTLRANKSUSED_OdtDisable_MSK                (0x00000030)
  #define DDRCTLCH0_CR_DDRCRCTLRANKSUSED_OdtDisable_MIN                (0)
  #define DDRCTLCH0_CR_DDRCRCTLRANKSUSED_OdtDisable_MAX                (3) // 0x00000003
  #define DDRCTLCH0_CR_DDRCRCTLRANKSUSED_OdtDisable_DEF                (0x00000000)
  #define DDRCTLCH0_CR_DDRCRCTLRANKSUSED_OdtDisable_HSH                (0x02041C20)

  #define DDRCTLCH0_CR_DDRCRCTLRANKSUSED_DdrCkeCmdSlwDlyByp_OFF        ( 6)
  #define DDRCTLCH0_CR_DDRCRCTLRANKSUSED_DdrCkeCmdSlwDlyByp_WID        ( 1)
  #define DDRCTLCH0_CR_DDRCRCTLRANKSUSED_DdrCkeCmdSlwDlyByp_MSK        (0x00000040)
  #define DDRCTLCH0_CR_DDRCRCTLRANKSUSED_DdrCkeCmdSlwDlyByp_MIN        (0)
  #define DDRCTLCH0_CR_DDRCRCTLRANKSUSED_DdrCkeCmdSlwDlyByp_MAX        (1) // 0x00000001
  #define DDRCTLCH0_CR_DDRCRCTLRANKSUSED_DdrCkeCmdSlwDlyByp_DEF        (0x00000000)
  #define DDRCTLCH0_CR_DDRCRCTLRANKSUSED_DdrCkeCmdSlwDlyByp_HSH        (0x01061C20)

  #define DDRCTLCH0_CR_DDRCRCTLRANKSUSED_DdrCtlCkeSlwDlyByp_OFF        ( 7)
  #define DDRCTLCH0_CR_DDRCRCTLRANKSUSED_DdrCtlCkeSlwDlyByp_WID        ( 1)
  #define DDRCTLCH0_CR_DDRCRCTLRANKSUSED_DdrCtlCkeSlwDlyByp_MSK        (0x00000080)
  #define DDRCTLCH0_CR_DDRCRCTLRANKSUSED_DdrCtlCkeSlwDlyByp_MIN        (0)
  #define DDRCTLCH0_CR_DDRCRCTLRANKSUSED_DdrCtlCkeSlwDlyByp_MAX        (1) // 0x00000001
  #define DDRCTLCH0_CR_DDRCRCTLRANKSUSED_DdrCtlCkeSlwDlyByp_DEF        (0x00000000)
  #define DDRCTLCH0_CR_DDRCRCTLRANKSUSED_DdrCtlCkeSlwDlyByp_HSH        (0x01071C20)

  #define DDRCTLCH0_CR_DDRCRCTLRANKSUSED_CsPiClkGateEn_OFF             ( 8)
  #define DDRCTLCH0_CR_DDRCRCTLRANKSUSED_CsPiClkGateEn_WID             ( 1)
  #define DDRCTLCH0_CR_DDRCRCTLRANKSUSED_CsPiClkGateEn_MSK             (0x00000100)
  #define DDRCTLCH0_CR_DDRCRCTLRANKSUSED_CsPiClkGateEn_MIN             (0)
  #define DDRCTLCH0_CR_DDRCRCTLRANKSUSED_CsPiClkGateEn_MAX             (1) // 0x00000001
  #define DDRCTLCH0_CR_DDRCRCTLRANKSUSED_CsPiClkGateEn_DEF             (0x00000000)
  #define DDRCTLCH0_CR_DDRCRCTLRANKSUSED_CsPiClkGateEn_HSH             (0x01081C20)

  #define DDRCTLCH0_CR_DDRCRCTLRANKSUSED_CsClkGateDis_OFF              ( 9)
  #define DDRCTLCH0_CR_DDRCRCTLRANKSUSED_CsClkGateDis_WID              ( 1)
  #define DDRCTLCH0_CR_DDRCRCTLRANKSUSED_CsClkGateDis_MSK              (0x00000200)
  #define DDRCTLCH0_CR_DDRCRCTLRANKSUSED_CsClkGateDis_MIN              (0)
  #define DDRCTLCH0_CR_DDRCRCTLRANKSUSED_CsClkGateDis_MAX              (1) // 0x00000001
  #define DDRCTLCH0_CR_DDRCRCTLRANKSUSED_CsClkGateDis_DEF              (0x00000000)
  #define DDRCTLCH0_CR_DDRCRCTLRANKSUSED_CsClkGateDis_HSH              (0x01091C20)

  #define DDRCTLCH0_CR_DDRCRCTLRANKSUSED_Spare_OFF                     (10)
  #define DDRCTLCH0_CR_DDRCRCTLRANKSUSED_Spare_WID                     (22)
  #define DDRCTLCH0_CR_DDRCRCTLRANKSUSED_Spare_MSK                     (0xFFFFFC00)
  #define DDRCTLCH0_CR_DDRCRCTLRANKSUSED_Spare_MIN                     (0)
  #define DDRCTLCH0_CR_DDRCRCTLRANKSUSED_Spare_MAX                     (4194303) // 0x003FFFFF
  #define DDRCTLCH0_CR_DDRCRCTLRANKSUSED_Spare_DEF                     (0x00000000)
  #define DDRCTLCH0_CR_DDRCRCTLRANKSUSED_Spare_HSH                     (0x160A1C20)

#define DDRCTLCH0_CR_DLLPITESTANDADC_REG                               (0x00001C24)

  #define DDRCTLCH0_CR_DLLPITESTANDADC_RunTest_OFF                     ( 0)
  #define DDRCTLCH0_CR_DLLPITESTANDADC_RunTest_WID                     ( 1)
  #define DDRCTLCH0_CR_DLLPITESTANDADC_RunTest_MSK                     (0x00000001)
  #define DDRCTLCH0_CR_DLLPITESTANDADC_RunTest_MIN                     (0)
  #define DDRCTLCH0_CR_DLLPITESTANDADC_RunTest_MAX                     (1) // 0x00000001
  #define DDRCTLCH0_CR_DLLPITESTANDADC_RunTest_DEF                     (0x00000000)
  #define DDRCTLCH0_CR_DLLPITESTANDADC_RunTest_HSH                     (0x01001C24)

  #define DDRCTLCH0_CR_DLLPITESTANDADC_Load_OFF                        ( 1)
  #define DDRCTLCH0_CR_DLLPITESTANDADC_Load_WID                        ( 1)
  #define DDRCTLCH0_CR_DLLPITESTANDADC_Load_MSK                        (0x00000002)
  #define DDRCTLCH0_CR_DLLPITESTANDADC_Load_MIN                        (0)
  #define DDRCTLCH0_CR_DLLPITESTANDADC_Load_MAX                        (1) // 0x00000001
  #define DDRCTLCH0_CR_DLLPITESTANDADC_Load_DEF                        (0x00000000)
  #define DDRCTLCH0_CR_DLLPITESTANDADC_Load_HSH                        (0x01011C24)

  #define DDRCTLCH0_CR_DLLPITESTANDADC_ModeHVM_OFF                     ( 2)
  #define DDRCTLCH0_CR_DLLPITESTANDADC_ModeHVM_WID                     ( 1)
  #define DDRCTLCH0_CR_DLLPITESTANDADC_ModeHVM_MSK                     (0x00000004)
  #define DDRCTLCH0_CR_DLLPITESTANDADC_ModeHVM_MIN                     (0)
  #define DDRCTLCH0_CR_DLLPITESTANDADC_ModeHVM_MAX                     (1) // 0x00000001
  #define DDRCTLCH0_CR_DLLPITESTANDADC_ModeHVM_DEF                     (0x00000000)
  #define DDRCTLCH0_CR_DLLPITESTANDADC_ModeHVM_HSH                     (0x01021C24)

  #define DDRCTLCH0_CR_DLLPITESTANDADC_ModeDV_OFF                      ( 3)
  #define DDRCTLCH0_CR_DLLPITESTANDADC_ModeDV_WID                      ( 1)
  #define DDRCTLCH0_CR_DLLPITESTANDADC_ModeDV_MSK                      (0x00000008)
  #define DDRCTLCH0_CR_DLLPITESTANDADC_ModeDV_MIN                      (0)
  #define DDRCTLCH0_CR_DLLPITESTANDADC_ModeDV_MAX                      (1) // 0x00000001
  #define DDRCTLCH0_CR_DLLPITESTANDADC_ModeDV_DEF                      (0x00000000)
  #define DDRCTLCH0_CR_DLLPITESTANDADC_ModeDV_HSH                      (0x01031C24)

  #define DDRCTLCH0_CR_DLLPITESTANDADC_CalCfdl_OFF                     ( 4)
  #define DDRCTLCH0_CR_DLLPITESTANDADC_CalCfdl_WID                     ( 1)
  #define DDRCTLCH0_CR_DLLPITESTANDADC_CalCfdl_MSK                     (0x00000010)
  #define DDRCTLCH0_CR_DLLPITESTANDADC_CalCfdl_MIN                     (0)
  #define DDRCTLCH0_CR_DLLPITESTANDADC_CalCfdl_MAX                     (1) // 0x00000001
  #define DDRCTLCH0_CR_DLLPITESTANDADC_CalCfdl_DEF                     (0x00000000)
  #define DDRCTLCH0_CR_DLLPITESTANDADC_CalCfdl_HSH                     (0x01041C24)

  #define DDRCTLCH0_CR_DLLPITESTANDADC_LoadCount_OFF                   ( 5)
  #define DDRCTLCH0_CR_DLLPITESTANDADC_LoadCount_WID                   (10)
  #define DDRCTLCH0_CR_DLLPITESTANDADC_LoadCount_MSK                   (0x00007FE0)
  #define DDRCTLCH0_CR_DLLPITESTANDADC_LoadCount_MIN                   (0)
  #define DDRCTLCH0_CR_DLLPITESTANDADC_LoadCount_MAX                   (1023) // 0x000003FF
  #define DDRCTLCH0_CR_DLLPITESTANDADC_LoadCount_DEF                   (0x00000000)
  #define DDRCTLCH0_CR_DLLPITESTANDADC_LoadCount_HSH                   (0x0A051C24)

  #define DDRCTLCH0_CR_DLLPITESTANDADC_CountStatus_OFF                 (15)
  #define DDRCTLCH0_CR_DLLPITESTANDADC_CountStatus_WID                 (10)
  #define DDRCTLCH0_CR_DLLPITESTANDADC_CountStatus_MSK                 (0x01FF8000)
  #define DDRCTLCH0_CR_DLLPITESTANDADC_CountStatus_MIN                 (0)
  #define DDRCTLCH0_CR_DLLPITESTANDADC_CountStatus_MAX                 (1023) // 0x000003FF
  #define DDRCTLCH0_CR_DLLPITESTANDADC_CountStatus_DEF                 (0x00000000)
  #define DDRCTLCH0_CR_DLLPITESTANDADC_CountStatus_HSH                 (0x0A0F1C24)

  #define DDRCTLCH0_CR_DLLPITESTANDADC_PhaseDrvPwrSavOn_OFF            (25)
  #define DDRCTLCH0_CR_DLLPITESTANDADC_PhaseDrvPwrSavOn_WID            ( 1)
  #define DDRCTLCH0_CR_DLLPITESTANDADC_PhaseDrvPwrSavOn_MSK            (0x02000000)
  #define DDRCTLCH0_CR_DLLPITESTANDADC_PhaseDrvPwrSavOn_MIN            (0)
  #define DDRCTLCH0_CR_DLLPITESTANDADC_PhaseDrvPwrSavOn_MAX            (1) // 0x00000001
  #define DDRCTLCH0_CR_DLLPITESTANDADC_PhaseDrvPwrSavOn_DEF            (0x00000000)
  #define DDRCTLCH0_CR_DLLPITESTANDADC_PhaseDrvPwrSavOn_HSH            (0x01191C24)

  #define DDRCTLCH0_CR_DLLPITESTANDADC_Spare_OFF                       (26)
  #define DDRCTLCH0_CR_DLLPITESTANDADC_Spare_WID                       ( 6)
  #define DDRCTLCH0_CR_DLLPITESTANDADC_Spare_MSK                       (0xFC000000)
  #define DDRCTLCH0_CR_DLLPITESTANDADC_Spare_MIN                       (0)
  #define DDRCTLCH0_CR_DLLPITESTANDADC_Spare_MAX                       (63) // 0x0000003F
  #define DDRCTLCH0_CR_DLLPITESTANDADC_Spare_DEF                       (0x00000000)
  #define DDRCTLCH0_CR_DLLPITESTANDADC_Spare_HSH                       (0x061A1C24)

#define DDRCTLCH1_CR_DDRCRCTLCOMP_REG                                  (0x00001D10)

  #define DDRCTLCH1_CR_DDRCRCTLCOMP_Scomp_OFF                          ( 0)
  #define DDRCTLCH1_CR_DDRCRCTLCOMP_Scomp_WID                          ( 6)
  #define DDRCTLCH1_CR_DDRCRCTLCOMP_Scomp_MSK                          (0x0000003F)
  #define DDRCTLCH1_CR_DDRCRCTLCOMP_Scomp_MIN                          (0)
  #define DDRCTLCH1_CR_DDRCRCTLCOMP_Scomp_MAX                          (63) // 0x0000003F
  #define DDRCTLCH1_CR_DDRCRCTLCOMP_Scomp_DEF                          (0x00000000)
  #define DDRCTLCH1_CR_DDRCRCTLCOMP_Scomp_HSH                          (0x06001D10)

  #define DDRCTLCH1_CR_DDRCRCTLCOMP_TcoComp_OFF                        ( 6)
  #define DDRCTLCH1_CR_DDRCRCTLCOMP_TcoComp_WID                        ( 6)
  #define DDRCTLCH1_CR_DDRCRCTLCOMP_TcoComp_MSK                        (0x00000FC0)
  #define DDRCTLCH1_CR_DDRCRCTLCOMP_TcoComp_MIN                        (0)
  #define DDRCTLCH1_CR_DDRCRCTLCOMP_TcoComp_MAX                        (63) // 0x0000003F
  #define DDRCTLCH1_CR_DDRCRCTLCOMP_TcoComp_DEF                        (0x00000000)
  #define DDRCTLCH1_CR_DDRCRCTLCOMP_TcoComp_HSH                        (0x06061D10)

  #define DDRCTLCH1_CR_DDRCRCTLCOMP_RcompDrvUp_OFF                     (12)
  #define DDRCTLCH1_CR_DDRCRCTLCOMP_RcompDrvUp_WID                     ( 6)
  #define DDRCTLCH1_CR_DDRCRCTLCOMP_RcompDrvUp_MSK                     (0x0003F000)
  #define DDRCTLCH1_CR_DDRCRCTLCOMP_RcompDrvUp_MIN                     (0)
  #define DDRCTLCH1_CR_DDRCRCTLCOMP_RcompDrvUp_MAX                     (63) // 0x0000003F
  #define DDRCTLCH1_CR_DDRCRCTLCOMP_RcompDrvUp_DEF                     (0x00000000)
  #define DDRCTLCH1_CR_DDRCRCTLCOMP_RcompDrvUp_HSH                     (0x060C1D10)

  #define DDRCTLCH1_CR_DDRCRCTLCOMP_RcompDrvDown_OFF                   (18)
  #define DDRCTLCH1_CR_DDRCRCTLCOMP_RcompDrvDown_WID                   ( 6)
  #define DDRCTLCH1_CR_DDRCRCTLCOMP_RcompDrvDown_MSK                   (0x00FC0000)
  #define DDRCTLCH1_CR_DDRCRCTLCOMP_RcompDrvDown_MIN                   (0)
  #define DDRCTLCH1_CR_DDRCRCTLCOMP_RcompDrvDown_MAX                   (63) // 0x0000003F
  #define DDRCTLCH1_CR_DDRCRCTLCOMP_RcompDrvDown_DEF                   (0x00000000)
  #define DDRCTLCH1_CR_DDRCRCTLCOMP_RcompDrvDown_HSH                   (0x06121D10)

  #define DDRCTLCH1_CR_DDRCRCTLCOMP_Spare_OFF                          (24)
  #define DDRCTLCH1_CR_DDRCRCTLCOMP_Spare_WID                          ( 8)
  #define DDRCTLCH1_CR_DDRCRCTLCOMP_Spare_MSK                          (0xFF000000)
  #define DDRCTLCH1_CR_DDRCRCTLCOMP_Spare_MIN                          (0)
  #define DDRCTLCH1_CR_DDRCRCTLCOMP_Spare_MAX                          (255) // 0x000000FF
  #define DDRCTLCH1_CR_DDRCRCTLCOMP_Spare_DEF                          (0x00000000)
  #define DDRCTLCH1_CR_DDRCRCTLCOMP_Spare_HSH                          (0x08181D10)

#define DDRCTLCH1_CR_DDRCRCTLCOMPOFFSET_REG                            (0x00001D14)

  #define DDRCTLCH1_CR_DDRCRCTLCOMPOFFSET_ScompOffset_OFF              ( 0)
  #define DDRCTLCH1_CR_DDRCRCTLCOMPOFFSET_ScompOffset_WID              ( 5)
  #define DDRCTLCH1_CR_DDRCRCTLCOMPOFFSET_ScompOffset_MSK              (0x0000001F)
  #define DDRCTLCH1_CR_DDRCRCTLCOMPOFFSET_ScompOffset_MIN              (-16)
  #define DDRCTLCH1_CR_DDRCRCTLCOMPOFFSET_ScompOffset_MAX              (15) // 0x0000000F
  #define DDRCTLCH1_CR_DDRCRCTLCOMPOFFSET_ScompOffset_DEF              (0x00000000)
  #define DDRCTLCH1_CR_DDRCRCTLCOMPOFFSET_ScompOffset_HSH              (0x85001D14)

  #define DDRCTLCH1_CR_DDRCRCTLCOMPOFFSET_TcoCompOffset_OFF            ( 5)
  #define DDRCTLCH1_CR_DDRCRCTLCOMPOFFSET_TcoCompOffset_WID            ( 4)
  #define DDRCTLCH1_CR_DDRCRCTLCOMPOFFSET_TcoCompOffset_MSK            (0x000001E0)
  #define DDRCTLCH1_CR_DDRCRCTLCOMPOFFSET_TcoCompOffset_MIN            (-8)
  #define DDRCTLCH1_CR_DDRCRCTLCOMPOFFSET_TcoCompOffset_MAX            (7) // 0x00000007
  #define DDRCTLCH1_CR_DDRCRCTLCOMPOFFSET_TcoCompOffset_DEF            (0x00000000)
  #define DDRCTLCH1_CR_DDRCRCTLCOMPOFFSET_TcoCompOffset_HSH            (0x84051D14)

  #define DDRCTLCH1_CR_DDRCRCTLCOMPOFFSET_RcompDrvUpOffset_OFF         ( 9)
  #define DDRCTLCH1_CR_DDRCRCTLCOMPOFFSET_RcompDrvUpOffset_WID         ( 4)
  #define DDRCTLCH1_CR_DDRCRCTLCOMPOFFSET_RcompDrvUpOffset_MSK         (0x00001E00)
  #define DDRCTLCH1_CR_DDRCRCTLCOMPOFFSET_RcompDrvUpOffset_MIN         (-8)
  #define DDRCTLCH1_CR_DDRCRCTLCOMPOFFSET_RcompDrvUpOffset_MAX         (7) // 0x00000007
  #define DDRCTLCH1_CR_DDRCRCTLCOMPOFFSET_RcompDrvUpOffset_DEF         (0x00000000)
  #define DDRCTLCH1_CR_DDRCRCTLCOMPOFFSET_RcompDrvUpOffset_HSH         (0x84091D14)

  #define DDRCTLCH1_CR_DDRCRCTLCOMPOFFSET_RcompDrvDownOffset_OFF       (13)
  #define DDRCTLCH1_CR_DDRCRCTLCOMPOFFSET_RcompDrvDownOffset_WID       ( 4)
  #define DDRCTLCH1_CR_DDRCRCTLCOMPOFFSET_RcompDrvDownOffset_MSK       (0x0001E000)
  #define DDRCTLCH1_CR_DDRCRCTLCOMPOFFSET_RcompDrvDownOffset_MIN       (-8)
  #define DDRCTLCH1_CR_DDRCRCTLCOMPOFFSET_RcompDrvDownOffset_MAX       (7) // 0x00000007
  #define DDRCTLCH1_CR_DDRCRCTLCOMPOFFSET_RcompDrvDownOffset_DEF       (0x00000000)
  #define DDRCTLCH1_CR_DDRCRCTLCOMPOFFSET_RcompDrvDownOffset_HSH       (0x840D1D14)

  #define DDRCTLCH1_CR_DDRCRCTLCOMPOFFSET_Spare_OFF                    (17)
  #define DDRCTLCH1_CR_DDRCRCTLCOMPOFFSET_Spare_WID                    (15)
  #define DDRCTLCH1_CR_DDRCRCTLCOMPOFFSET_Spare_MSK                    (0xFFFE0000)
  #define DDRCTLCH1_CR_DDRCRCTLCOMPOFFSET_Spare_MIN                    (0)
  #define DDRCTLCH1_CR_DDRCRCTLCOMPOFFSET_Spare_MAX                    (32767) // 0x00007FFF
  #define DDRCTLCH1_CR_DDRCRCTLCOMPOFFSET_Spare_DEF                    (0x00000000)
  #define DDRCTLCH1_CR_DDRCRCTLCOMPOFFSET_Spare_HSH                    (0x0F111D14)

#define DDRCTLCH1_CR_DDRCRCTLPICODING_REG                              (0x00001D18)

  #define DDRCTLCH1_CR_DDRCRCTLPICODING_CtlPiCode0_OFF                 ( 0)
  #define DDRCTLCH1_CR_DDRCRCTLPICODING_CtlPiCode0_WID                 ( 7)
  #define DDRCTLCH1_CR_DDRCRCTLPICODING_CtlPiCode0_MSK                 (0x0000007F)
  #define DDRCTLCH1_CR_DDRCRCTLPICODING_CtlPiCode0_MIN                 (0)
  #define DDRCTLCH1_CR_DDRCRCTLPICODING_CtlPiCode0_MAX                 (127) // 0x0000007F
  #define DDRCTLCH1_CR_DDRCRCTLPICODING_CtlPiCode0_DEF                 (0x00000000)
  #define DDRCTLCH1_CR_DDRCRCTLPICODING_CtlPiCode0_HSH                 (0x07001D18)

  #define DDRCTLCH1_CR_DDRCRCTLPICODING_CtlPiCode1_OFF                 ( 7)
  #define DDRCTLCH1_CR_DDRCRCTLPICODING_CtlPiCode1_WID                 ( 7)
  #define DDRCTLCH1_CR_DDRCRCTLPICODING_CtlPiCode1_MSK                 (0x00003F80)
  #define DDRCTLCH1_CR_DDRCRCTLPICODING_CtlPiCode1_MIN                 (0)
  #define DDRCTLCH1_CR_DDRCRCTLPICODING_CtlPiCode1_MAX                 (127) // 0x0000007F
  #define DDRCTLCH1_CR_DDRCRCTLPICODING_CtlPiCode1_DEF                 (0x00000000)
  #define DDRCTLCH1_CR_DDRCRCTLPICODING_CtlPiCode1_HSH                 (0x07071D18)

  #define DDRCTLCH1_CR_DDRCRCTLPICODING_CtlPiCode2_OFF                 (14)
  #define DDRCTLCH1_CR_DDRCRCTLPICODING_CtlPiCode2_WID                 ( 7)
  #define DDRCTLCH1_CR_DDRCRCTLPICODING_CtlPiCode2_MSK                 (0x001FC000)
  #define DDRCTLCH1_CR_DDRCRCTLPICODING_CtlPiCode2_MIN                 (0)
  #define DDRCTLCH1_CR_DDRCRCTLPICODING_CtlPiCode2_MAX                 (127) // 0x0000007F
  #define DDRCTLCH1_CR_DDRCRCTLPICODING_CtlPiCode2_DEF                 (0x00000000)
  #define DDRCTLCH1_CR_DDRCRCTLPICODING_CtlPiCode2_HSH                 (0x070E1D18)

  #define DDRCTLCH1_CR_DDRCRCTLPICODING_CtlPiCode3_OFF                 (21)
  #define DDRCTLCH1_CR_DDRCRCTLPICODING_CtlPiCode3_WID                 ( 7)
  #define DDRCTLCH1_CR_DDRCRCTLPICODING_CtlPiCode3_MSK                 (0x0FE00000)
  #define DDRCTLCH1_CR_DDRCRCTLPICODING_CtlPiCode3_MIN                 (0)
  #define DDRCTLCH1_CR_DDRCRCTLPICODING_CtlPiCode3_MAX                 (127) // 0x0000007F
  #define DDRCTLCH1_CR_DDRCRCTLPICODING_CtlPiCode3_DEF                 (0x00000000)
  #define DDRCTLCH1_CR_DDRCRCTLPICODING_CtlPiCode3_HSH                 (0x07151D18)

  #define DDRCTLCH1_CR_DDRCRCTLPICODING_CtlXoverEnable_OFF             (28)
  #define DDRCTLCH1_CR_DDRCRCTLPICODING_CtlXoverEnable_WID             ( 1)
  #define DDRCTLCH1_CR_DDRCRCTLPICODING_CtlXoverEnable_MSK             (0x10000000)
  #define DDRCTLCH1_CR_DDRCRCTLPICODING_CtlXoverEnable_MIN             (0)
  #define DDRCTLCH1_CR_DDRCRCTLPICODING_CtlXoverEnable_MAX             (1) // 0x00000001
  #define DDRCTLCH1_CR_DDRCRCTLPICODING_CtlXoverEnable_DEF             (0x00000000)
  #define DDRCTLCH1_CR_DDRCRCTLPICODING_CtlXoverEnable_HSH             (0x011C1D18)

  #define DDRCTLCH1_CR_DDRCRCTLPICODING_Spare_OFF                      (29)
  #define DDRCTLCH1_CR_DDRCRCTLPICODING_Spare_WID                      ( 3)
  #define DDRCTLCH1_CR_DDRCRCTLPICODING_Spare_MSK                      (0xE0000000)
  #define DDRCTLCH1_CR_DDRCRCTLPICODING_Spare_MIN                      (0)
  #define DDRCTLCH1_CR_DDRCRCTLPICODING_Spare_MAX                      (7) // 0x00000007
  #define DDRCTLCH1_CR_DDRCRCTLPICODING_Spare_DEF                      (0x00000000)
  #define DDRCTLCH1_CR_DDRCRCTLPICODING_Spare_HSH                      (0x031D1D18)

#define DDRCTLCH1_CR_DDRCRCTLCONTROLS_REG                              (0x00001D1C)

  #define DDRCTLCH1_CR_DDRCRCTLCONTROLS_RefPi_OFF                      ( 0)
  #define DDRCTLCH1_CR_DDRCRCTLCONTROLS_RefPi_WID                      ( 4)
  #define DDRCTLCH1_CR_DDRCRCTLCONTROLS_RefPi_MSK                      (0x0000000F)
  #define DDRCTLCH1_CR_DDRCRCTLCONTROLS_RefPi_MIN                      (-8)
  #define DDRCTLCH1_CR_DDRCRCTLCONTROLS_RefPi_MAX                      (7) // 0x00000007
  #define DDRCTLCH1_CR_DDRCRCTLCONTROLS_RefPi_DEF                      (0x00000000)
  #define DDRCTLCH1_CR_DDRCRCTLCONTROLS_RefPi_HSH                      (0x84001D1C)

  #define DDRCTLCH1_CR_DDRCRCTLCONTROLS_DllMask_OFF                    ( 4)
  #define DDRCTLCH1_CR_DDRCRCTLCONTROLS_DllMask_WID                    ( 2)
  #define DDRCTLCH1_CR_DDRCRCTLCONTROLS_DllMask_MSK                    (0x00000030)
  #define DDRCTLCH1_CR_DDRCRCTLCONTROLS_DllMask_MIN                    (0)
  #define DDRCTLCH1_CR_DDRCRCTLCONTROLS_DllMask_MAX                    (3) // 0x00000003
  #define DDRCTLCH1_CR_DDRCRCTLCONTROLS_DllMask_DEF                    (0x00000000)
  #define DDRCTLCH1_CR_DDRCRCTLCONTROLS_DllMask_HSH                    (0x02041D1C)

  #define DDRCTLCH1_CR_DDRCRCTLCONTROLS_ClkGateDisable_OFF             ( 6)
  #define DDRCTLCH1_CR_DDRCRCTLCONTROLS_ClkGateDisable_WID             ( 1)
  #define DDRCTLCH1_CR_DDRCRCTLCONTROLS_ClkGateDisable_MSK             (0x00000040)
  #define DDRCTLCH1_CR_DDRCRCTLCONTROLS_ClkGateDisable_MIN             (0)
  #define DDRCTLCH1_CR_DDRCRCTLCONTROLS_ClkGateDisable_MAX             (1) // 0x00000001
  #define DDRCTLCH1_CR_DDRCRCTLCONTROLS_ClkGateDisable_DEF             (0x00000000)
  #define DDRCTLCH1_CR_DDRCRCTLCONTROLS_ClkGateDisable_HSH             (0x01061D1C)

  #define DDRCTLCH1_CR_DDRCRCTLCONTROLS_TxOn_OFF                       ( 7)
  #define DDRCTLCH1_CR_DDRCRCTLCONTROLS_TxOn_WID                       ( 1)
  #define DDRCTLCH1_CR_DDRCRCTLCONTROLS_TxOn_MSK                       (0x00000080)
  #define DDRCTLCH1_CR_DDRCRCTLCONTROLS_TxOn_MIN                       (0)
  #define DDRCTLCH1_CR_DDRCRCTLCONTROLS_TxOn_MAX                       (1) // 0x00000001
  #define DDRCTLCH1_CR_DDRCRCTLCONTROLS_TxOn_DEF                       (0x00000000)
  #define DDRCTLCH1_CR_DDRCRCTLCONTROLS_TxOn_HSH                       (0x01071D1C)

  #define DDRCTLCH1_CR_DDRCRCTLCONTROLS_IntClkOn_OFF                   ( 8)
  #define DDRCTLCH1_CR_DDRCRCTLCONTROLS_IntClkOn_WID                   ( 1)
  #define DDRCTLCH1_CR_DDRCRCTLCONTROLS_IntClkOn_MSK                   (0x00000100)
  #define DDRCTLCH1_CR_DDRCRCTLCONTROLS_IntClkOn_MIN                   (0)
  #define DDRCTLCH1_CR_DDRCRCTLCONTROLS_IntClkOn_MAX                   (1) // 0x00000001
  #define DDRCTLCH1_CR_DDRCRCTLCONTROLS_IntClkOn_DEF                   (0x00000000)
  #define DDRCTLCH1_CR_DDRCRCTLCONTROLS_IntClkOn_HSH                   (0x01081D1C)

  #define DDRCTLCH1_CR_DDRCRCTLCONTROLS_RepClkOn_OFF                   ( 9)
  #define DDRCTLCH1_CR_DDRCRCTLCONTROLS_RepClkOn_WID                   ( 1)
  #define DDRCTLCH1_CR_DDRCRCTLCONTROLS_RepClkOn_MSK                   (0x00000200)
  #define DDRCTLCH1_CR_DDRCRCTLCONTROLS_RepClkOn_MIN                   (0)
  #define DDRCTLCH1_CR_DDRCRCTLCONTROLS_RepClkOn_MAX                   (1) // 0x00000001
  #define DDRCTLCH1_CR_DDRCRCTLCONTROLS_RepClkOn_DEF                   (0x00000000)
  #define DDRCTLCH1_CR_DDRCRCTLCONTROLS_RepClkOn_HSH                   (0x01091D1C)

  #define DDRCTLCH1_CR_DDRCRCTLCONTROLS_IolbOrMisr_OFF                 (10)
  #define DDRCTLCH1_CR_DDRCRCTLCONTROLS_IolbOrMisr_WID                 ( 1)
  #define DDRCTLCH1_CR_DDRCRCTLCONTROLS_IolbOrMisr_MSK                 (0x00000400)
  #define DDRCTLCH1_CR_DDRCRCTLCONTROLS_IolbOrMisr_MIN                 (0)
  #define DDRCTLCH1_CR_DDRCRCTLCONTROLS_IolbOrMisr_MAX                 (1) // 0x00000001
  #define DDRCTLCH1_CR_DDRCRCTLCONTROLS_IolbOrMisr_DEF                 (0x00000000)
  #define DDRCTLCH1_CR_DDRCRCTLCONTROLS_IolbOrMisr_HSH                 (0x010A1D1C)

  #define DDRCTLCH1_CR_DDRCRCTLCONTROLS_IOLBHold_OFF                   (11)
  #define DDRCTLCH1_CR_DDRCRCTLCONTROLS_IOLBHold_WID                   ( 1)
  #define DDRCTLCH1_CR_DDRCRCTLCONTROLS_IOLBHold_MSK                   (0x00000800)
  #define DDRCTLCH1_CR_DDRCRCTLCONTROLS_IOLBHold_MIN                   (0)
  #define DDRCTLCH1_CR_DDRCRCTLCONTROLS_IOLBHold_MAX                   (1) // 0x00000001
  #define DDRCTLCH1_CR_DDRCRCTLCONTROLS_IOLBHold_DEF                   (0x00000000)
  #define DDRCTLCH1_CR_DDRCRCTLCONTROLS_IOLBHold_HSH                   (0x010B1D1C)

  #define DDRCTLCH1_CR_DDRCRCTLCONTROLS_OdtMode_OFF                    (12)
  #define DDRCTLCH1_CR_DDRCRCTLCONTROLS_OdtMode_WID                    ( 1)
  #define DDRCTLCH1_CR_DDRCRCTLCONTROLS_OdtMode_MSK                    (0x00001000)
  #define DDRCTLCH1_CR_DDRCRCTLCONTROLS_OdtMode_MIN                    (0)
  #define DDRCTLCH1_CR_DDRCRCTLCONTROLS_OdtMode_MAX                    (1) // 0x00000001
  #define DDRCTLCH1_CR_DDRCRCTLCONTROLS_OdtMode_DEF                    (0x00000000)
  #define DDRCTLCH1_CR_DDRCRCTLCONTROLS_OdtMode_HSH                    (0x010C1D1C)

  #define DDRCTLCH1_CR_DDRCRCTLCONTROLS_CmdTxEq_OFF                    (13)
  #define DDRCTLCH1_CR_DDRCRCTLCONTROLS_CmdTxEq_WID                    ( 2)
  #define DDRCTLCH1_CR_DDRCRCTLCONTROLS_CmdTxEq_MSK                    (0x00006000)
  #define DDRCTLCH1_CR_DDRCRCTLCONTROLS_CmdTxEq_MIN                    (0)
  #define DDRCTLCH1_CR_DDRCRCTLCONTROLS_CmdTxEq_MAX                    (3) // 0x00000003
  #define DDRCTLCH1_CR_DDRCRCTLCONTROLS_CmdTxEq_DEF                    (0x00000000)
  #define DDRCTLCH1_CR_DDRCRCTLCONTROLS_CmdTxEq_HSH                    (0x020D1D1C)

  #define DDRCTLCH1_CR_DDRCRCTLCONTROLS_EarlyWeakDrive_OFF             (15)
  #define DDRCTLCH1_CR_DDRCRCTLCONTROLS_EarlyWeakDrive_WID             ( 2)
  #define DDRCTLCH1_CR_DDRCRCTLCONTROLS_EarlyWeakDrive_MSK             (0x00018000)
  #define DDRCTLCH1_CR_DDRCRCTLCONTROLS_EarlyWeakDrive_MIN             (0)
  #define DDRCTLCH1_CR_DDRCRCTLCONTROLS_EarlyWeakDrive_MAX             (3) // 0x00000003
  #define DDRCTLCH1_CR_DDRCRCTLCONTROLS_EarlyWeakDrive_DEF             (0x00000000)
  #define DDRCTLCH1_CR_DDRCRCTLCONTROLS_EarlyWeakDrive_HSH             (0x020F1D1C)

  #define DDRCTLCH1_CR_DDRCRCTLCONTROLS_CtlTxEq_OFF                    (17)
  #define DDRCTLCH1_CR_DDRCRCTLCONTROLS_CtlTxEq_WID                    ( 2)
  #define DDRCTLCH1_CR_DDRCRCTLCONTROLS_CtlTxEq_MSK                    (0x00060000)
  #define DDRCTLCH1_CR_DDRCRCTLCONTROLS_CtlTxEq_MIN                    (0)
  #define DDRCTLCH1_CR_DDRCRCTLCONTROLS_CtlTxEq_MAX                    (3) // 0x00000003
  #define DDRCTLCH1_CR_DDRCRCTLCONTROLS_CtlTxEq_DEF                    (0x00000000)
  #define DDRCTLCH1_CR_DDRCRCTLCONTROLS_CtlTxEq_HSH                    (0x02111D1C)

  #define DDRCTLCH1_CR_DDRCRCTLCONTROLS_CtlSRDrv_OFF                   (19)
  #define DDRCTLCH1_CR_DDRCRCTLCONTROLS_CtlSRDrv_WID                   ( 2)
  #define DDRCTLCH1_CR_DDRCRCTLCONTROLS_CtlSRDrv_MSK                   (0x00180000)
  #define DDRCTLCH1_CR_DDRCRCTLCONTROLS_CtlSRDrv_MIN                   (0)
  #define DDRCTLCH1_CR_DDRCRCTLCONTROLS_CtlSRDrv_MAX                   (3) // 0x00000003
  #define DDRCTLCH1_CR_DDRCRCTLCONTROLS_CtlSRDrv_DEF                   (0x00000000)
  #define DDRCTLCH1_CR_DDRCRCTLCONTROLS_CtlSRDrv_HSH                   (0x02131D1C)

  #define DDRCTLCH1_CR_DDRCRCTLCONTROLS_RxVref_OFF                     (21)
  #define DDRCTLCH1_CR_DDRCRCTLCONTROLS_RxVref_WID                     ( 6)
  #define DDRCTLCH1_CR_DDRCRCTLCONTROLS_RxVref_MSK                     (0x07E00000)
  #define DDRCTLCH1_CR_DDRCRCTLCONTROLS_RxVref_MIN                     (-32)
  #define DDRCTLCH1_CR_DDRCRCTLCONTROLS_RxVref_MAX                     (31) // 0x0000001F
  #define DDRCTLCH1_CR_DDRCRCTLCONTROLS_RxVref_DEF                     (0x00000000)
  #define DDRCTLCH1_CR_DDRCRCTLCONTROLS_RxVref_HSH                     (0x86151D1C)

  #define DDRCTLCH1_CR_DDRCRCTLCONTROLS_VccddqHi_OFF                   (27)
  #define DDRCTLCH1_CR_DDRCRCTLCONTROLS_VccddqHi_WID                   ( 1)
  #define DDRCTLCH1_CR_DDRCRCTLCONTROLS_VccddqHi_MSK                   (0x08000000)
  #define DDRCTLCH1_CR_DDRCRCTLCONTROLS_VccddqHi_MIN                   (0)
  #define DDRCTLCH1_CR_DDRCRCTLCONTROLS_VccddqHi_MAX                   (1) // 0x00000001
  #define DDRCTLCH1_CR_DDRCRCTLCONTROLS_VccddqHi_DEF                   (0x00000000)
  #define DDRCTLCH1_CR_DDRCRCTLCONTROLS_VccddqHi_HSH                   (0x011B1D1C)

  #define DDRCTLCH1_CR_DDRCRCTLCONTROLS_DllWeakLock_OFF                (28)
  #define DDRCTLCH1_CR_DDRCRCTLCONTROLS_DllWeakLock_WID                ( 1)
  #define DDRCTLCH1_CR_DDRCRCTLCONTROLS_DllWeakLock_MSK                (0x10000000)
  #define DDRCTLCH1_CR_DDRCRCTLCONTROLS_DllWeakLock_MIN                (0)
  #define DDRCTLCH1_CR_DDRCRCTLCONTROLS_DllWeakLock_MAX                (1) // 0x00000001
  #define DDRCTLCH1_CR_DDRCRCTLCONTROLS_DllWeakLock_DEF                (0x00000000)
  #define DDRCTLCH1_CR_DDRCRCTLCONTROLS_DllWeakLock_HSH                (0x011C1D1C)

  #define DDRCTLCH1_CR_DDRCRCTLCONTROLS_LPDDR_Mode_OFF                 (29)
  #define DDRCTLCH1_CR_DDRCRCTLCONTROLS_LPDDR_Mode_WID                 ( 1)
  #define DDRCTLCH1_CR_DDRCRCTLCONTROLS_LPDDR_Mode_MSK                 (0x20000000)
  #define DDRCTLCH1_CR_DDRCRCTLCONTROLS_LPDDR_Mode_MIN                 (0)
  #define DDRCTLCH1_CR_DDRCRCTLCONTROLS_LPDDR_Mode_MAX                 (1) // 0x00000001
  #define DDRCTLCH1_CR_DDRCRCTLCONTROLS_LPDDR_Mode_DEF                 (0x00000000)
  #define DDRCTLCH1_CR_DDRCRCTLCONTROLS_LPDDR_Mode_HSH                 (0x011D1D1C)

  #define DDRCTLCH1_CR_DDRCRCTLCONTROLS_LaDrvEnOvrd_OFF                (30)
  #define DDRCTLCH1_CR_DDRCRCTLCONTROLS_LaDrvEnOvrd_WID                ( 1)
  #define DDRCTLCH1_CR_DDRCRCTLCONTROLS_LaDrvEnOvrd_MSK                (0x40000000)
  #define DDRCTLCH1_CR_DDRCRCTLCONTROLS_LaDrvEnOvrd_MIN                (0)
  #define DDRCTLCH1_CR_DDRCRCTLCONTROLS_LaDrvEnOvrd_MAX                (1) // 0x00000001
  #define DDRCTLCH1_CR_DDRCRCTLCONTROLS_LaDrvEnOvrd_DEF                (0x00000000)
  #define DDRCTLCH1_CR_DDRCRCTLCONTROLS_LaDrvEnOvrd_HSH                (0x011E1D1C)

  #define DDRCTLCH1_CR_DDRCRCTLCONTROLS_LPDdrCAA_Dis_OFF               (31)
  #define DDRCTLCH1_CR_DDRCRCTLCONTROLS_LPDdrCAA_Dis_WID               ( 1)
  #define DDRCTLCH1_CR_DDRCRCTLCONTROLS_LPDdrCAA_Dis_MSK               (0x80000000)
  #define DDRCTLCH1_CR_DDRCRCTLCONTROLS_LPDdrCAA_Dis_MIN               (0)
  #define DDRCTLCH1_CR_DDRCRCTLCONTROLS_LPDdrCAA_Dis_MAX               (1) // 0x00000001
  #define DDRCTLCH1_CR_DDRCRCTLCONTROLS_LPDdrCAA_Dis_DEF               (0x00000000)
  #define DDRCTLCH1_CR_DDRCRCTLCONTROLS_LPDdrCAA_Dis_HSH               (0x011F1D1C)

#define DDRCTLCH1_CR_DDRCRCTLRANKSUSED_REG                             (0x00001D20)

  #define DDRCTLCH1_CR_DDRCRCTLRANKSUSED_RankEn_OFF                    ( 0)
  #define DDRCTLCH1_CR_DDRCRCTLRANKSUSED_RankEn_WID                    ( 4)
  #define DDRCTLCH1_CR_DDRCRCTLRANKSUSED_RankEn_MSK                    (0x0000000F)
  #define DDRCTLCH1_CR_DDRCRCTLRANKSUSED_RankEn_MIN                    (0)
  #define DDRCTLCH1_CR_DDRCRCTLRANKSUSED_RankEn_MAX                    (15) // 0x0000000F
  #define DDRCTLCH1_CR_DDRCRCTLRANKSUSED_RankEn_DEF                    (0x0000000F)
  #define DDRCTLCH1_CR_DDRCRCTLRANKSUSED_RankEn_HSH                    (0x04001D20)

  #define DDRCTLCH1_CR_DDRCRCTLRANKSUSED_OdtDisable_OFF                ( 4)
  #define DDRCTLCH1_CR_DDRCRCTLRANKSUSED_OdtDisable_WID                ( 2)
  #define DDRCTLCH1_CR_DDRCRCTLRANKSUSED_OdtDisable_MSK                (0x00000030)
  #define DDRCTLCH1_CR_DDRCRCTLRANKSUSED_OdtDisable_MIN                (0)
  #define DDRCTLCH1_CR_DDRCRCTLRANKSUSED_OdtDisable_MAX                (3) // 0x00000003
  #define DDRCTLCH1_CR_DDRCRCTLRANKSUSED_OdtDisable_DEF                (0x00000000)
  #define DDRCTLCH1_CR_DDRCRCTLRANKSUSED_OdtDisable_HSH                (0x02041D20)

  #define DDRCTLCH1_CR_DDRCRCTLRANKSUSED_DdrCkeCmdSlwDlyByp_OFF        ( 6)
  #define DDRCTLCH1_CR_DDRCRCTLRANKSUSED_DdrCkeCmdSlwDlyByp_WID        ( 1)
  #define DDRCTLCH1_CR_DDRCRCTLRANKSUSED_DdrCkeCmdSlwDlyByp_MSK        (0x00000040)
  #define DDRCTLCH1_CR_DDRCRCTLRANKSUSED_DdrCkeCmdSlwDlyByp_MIN        (0)
  #define DDRCTLCH1_CR_DDRCRCTLRANKSUSED_DdrCkeCmdSlwDlyByp_MAX        (1) // 0x00000001
  #define DDRCTLCH1_CR_DDRCRCTLRANKSUSED_DdrCkeCmdSlwDlyByp_DEF        (0x00000000)
  #define DDRCTLCH1_CR_DDRCRCTLRANKSUSED_DdrCkeCmdSlwDlyByp_HSH        (0x01061D20)

  #define DDRCTLCH1_CR_DDRCRCTLRANKSUSED_DdrCtlCkeSlwDlyByp_OFF        ( 7)
  #define DDRCTLCH1_CR_DDRCRCTLRANKSUSED_DdrCtlCkeSlwDlyByp_WID        ( 1)
  #define DDRCTLCH1_CR_DDRCRCTLRANKSUSED_DdrCtlCkeSlwDlyByp_MSK        (0x00000080)
  #define DDRCTLCH1_CR_DDRCRCTLRANKSUSED_DdrCtlCkeSlwDlyByp_MIN        (0)
  #define DDRCTLCH1_CR_DDRCRCTLRANKSUSED_DdrCtlCkeSlwDlyByp_MAX        (1) // 0x00000001
  #define DDRCTLCH1_CR_DDRCRCTLRANKSUSED_DdrCtlCkeSlwDlyByp_DEF        (0x00000000)
  #define DDRCTLCH1_CR_DDRCRCTLRANKSUSED_DdrCtlCkeSlwDlyByp_HSH        (0x01071D20)

  #define DDRCTLCH1_CR_DDRCRCTLRANKSUSED_CsPiClkGateEn_OFF             ( 8)
  #define DDRCTLCH1_CR_DDRCRCTLRANKSUSED_CsPiClkGateEn_WID             ( 1)
  #define DDRCTLCH1_CR_DDRCRCTLRANKSUSED_CsPiClkGateEn_MSK             (0x00000100)
  #define DDRCTLCH1_CR_DDRCRCTLRANKSUSED_CsPiClkGateEn_MIN             (0)
  #define DDRCTLCH1_CR_DDRCRCTLRANKSUSED_CsPiClkGateEn_MAX             (1) // 0x00000001
  #define DDRCTLCH1_CR_DDRCRCTLRANKSUSED_CsPiClkGateEn_DEF             (0x00000000)
  #define DDRCTLCH1_CR_DDRCRCTLRANKSUSED_CsPiClkGateEn_HSH             (0x01081D20)

  #define DDRCTLCH1_CR_DDRCRCTLRANKSUSED_CsClkGateDis_OFF              ( 9)
  #define DDRCTLCH1_CR_DDRCRCTLRANKSUSED_CsClkGateDis_WID              ( 1)
  #define DDRCTLCH1_CR_DDRCRCTLRANKSUSED_CsClkGateDis_MSK              (0x00000200)
  #define DDRCTLCH1_CR_DDRCRCTLRANKSUSED_CsClkGateDis_MIN              (0)
  #define DDRCTLCH1_CR_DDRCRCTLRANKSUSED_CsClkGateDis_MAX              (1) // 0x00000001
  #define DDRCTLCH1_CR_DDRCRCTLRANKSUSED_CsClkGateDis_DEF              (0x00000000)
  #define DDRCTLCH1_CR_DDRCRCTLRANKSUSED_CsClkGateDis_HSH              (0x01091D20)

  #define DDRCTLCH1_CR_DDRCRCTLRANKSUSED_Spare_OFF                     (10)
  #define DDRCTLCH1_CR_DDRCRCTLRANKSUSED_Spare_WID                     (22)
  #define DDRCTLCH1_CR_DDRCRCTLRANKSUSED_Spare_MSK                     (0xFFFFFC00)
  #define DDRCTLCH1_CR_DDRCRCTLRANKSUSED_Spare_MIN                     (0)
  #define DDRCTLCH1_CR_DDRCRCTLRANKSUSED_Spare_MAX                     (4194303) // 0x003FFFFF
  #define DDRCTLCH1_CR_DDRCRCTLRANKSUSED_Spare_DEF                     (0x00000000)
  #define DDRCTLCH1_CR_DDRCRCTLRANKSUSED_Spare_HSH                     (0x160A1D20)

#define DDRCTLCH1_CR_DLLPITESTANDADC_REG                               (0x00001D24)

  #define DDRCTLCH1_CR_DLLPITESTANDADC_RunTest_OFF                     ( 0)
  #define DDRCTLCH1_CR_DLLPITESTANDADC_RunTest_WID                     ( 1)
  #define DDRCTLCH1_CR_DLLPITESTANDADC_RunTest_MSK                     (0x00000001)
  #define DDRCTLCH1_CR_DLLPITESTANDADC_RunTest_MIN                     (0)
  #define DDRCTLCH1_CR_DLLPITESTANDADC_RunTest_MAX                     (1) // 0x00000001
  #define DDRCTLCH1_CR_DLLPITESTANDADC_RunTest_DEF                     (0x00000000)
  #define DDRCTLCH1_CR_DLLPITESTANDADC_RunTest_HSH                     (0x01001D24)

  #define DDRCTLCH1_CR_DLLPITESTANDADC_Load_OFF                        ( 1)
  #define DDRCTLCH1_CR_DLLPITESTANDADC_Load_WID                        ( 1)
  #define DDRCTLCH1_CR_DLLPITESTANDADC_Load_MSK                        (0x00000002)
  #define DDRCTLCH1_CR_DLLPITESTANDADC_Load_MIN                        (0)
  #define DDRCTLCH1_CR_DLLPITESTANDADC_Load_MAX                        (1) // 0x00000001
  #define DDRCTLCH1_CR_DLLPITESTANDADC_Load_DEF                        (0x00000000)
  #define DDRCTLCH1_CR_DLLPITESTANDADC_Load_HSH                        (0x01011D24)

  #define DDRCTLCH1_CR_DLLPITESTANDADC_ModeHVM_OFF                     ( 2)
  #define DDRCTLCH1_CR_DLLPITESTANDADC_ModeHVM_WID                     ( 1)
  #define DDRCTLCH1_CR_DLLPITESTANDADC_ModeHVM_MSK                     (0x00000004)
  #define DDRCTLCH1_CR_DLLPITESTANDADC_ModeHVM_MIN                     (0)
  #define DDRCTLCH1_CR_DLLPITESTANDADC_ModeHVM_MAX                     (1) // 0x00000001
  #define DDRCTLCH1_CR_DLLPITESTANDADC_ModeHVM_DEF                     (0x00000000)
  #define DDRCTLCH1_CR_DLLPITESTANDADC_ModeHVM_HSH                     (0x01021D24)

  #define DDRCTLCH1_CR_DLLPITESTANDADC_ModeDV_OFF                      ( 3)
  #define DDRCTLCH1_CR_DLLPITESTANDADC_ModeDV_WID                      ( 1)
  #define DDRCTLCH1_CR_DLLPITESTANDADC_ModeDV_MSK                      (0x00000008)
  #define DDRCTLCH1_CR_DLLPITESTANDADC_ModeDV_MIN                      (0)
  #define DDRCTLCH1_CR_DLLPITESTANDADC_ModeDV_MAX                      (1) // 0x00000001
  #define DDRCTLCH1_CR_DLLPITESTANDADC_ModeDV_DEF                      (0x00000000)
  #define DDRCTLCH1_CR_DLLPITESTANDADC_ModeDV_HSH                      (0x01031D24)

  #define DDRCTLCH1_CR_DLLPITESTANDADC_CalCfdl_OFF                     ( 4)
  #define DDRCTLCH1_CR_DLLPITESTANDADC_CalCfdl_WID                     ( 1)
  #define DDRCTLCH1_CR_DLLPITESTANDADC_CalCfdl_MSK                     (0x00000010)
  #define DDRCTLCH1_CR_DLLPITESTANDADC_CalCfdl_MIN                     (0)
  #define DDRCTLCH1_CR_DLLPITESTANDADC_CalCfdl_MAX                     (1) // 0x00000001
  #define DDRCTLCH1_CR_DLLPITESTANDADC_CalCfdl_DEF                     (0x00000000)
  #define DDRCTLCH1_CR_DLLPITESTANDADC_CalCfdl_HSH                     (0x01041D24)

  #define DDRCTLCH1_CR_DLLPITESTANDADC_LoadCount_OFF                   ( 5)
  #define DDRCTLCH1_CR_DLLPITESTANDADC_LoadCount_WID                   (10)
  #define DDRCTLCH1_CR_DLLPITESTANDADC_LoadCount_MSK                   (0x00007FE0)
  #define DDRCTLCH1_CR_DLLPITESTANDADC_LoadCount_MIN                   (0)
  #define DDRCTLCH1_CR_DLLPITESTANDADC_LoadCount_MAX                   (1023) // 0x000003FF
  #define DDRCTLCH1_CR_DLLPITESTANDADC_LoadCount_DEF                   (0x00000000)
  #define DDRCTLCH1_CR_DLLPITESTANDADC_LoadCount_HSH                   (0x0A051D24)

  #define DDRCTLCH1_CR_DLLPITESTANDADC_CountStatus_OFF                 (15)
  #define DDRCTLCH1_CR_DLLPITESTANDADC_CountStatus_WID                 (10)
  #define DDRCTLCH1_CR_DLLPITESTANDADC_CountStatus_MSK                 (0x01FF8000)
  #define DDRCTLCH1_CR_DLLPITESTANDADC_CountStatus_MIN                 (0)
  #define DDRCTLCH1_CR_DLLPITESTANDADC_CountStatus_MAX                 (1023) // 0x000003FF
  #define DDRCTLCH1_CR_DLLPITESTANDADC_CountStatus_DEF                 (0x00000000)
  #define DDRCTLCH1_CR_DLLPITESTANDADC_CountStatus_HSH                 (0x0A0F1D24)

  #define DDRCTLCH1_CR_DLLPITESTANDADC_PhaseDrvPwrSavOn_OFF            (25)
  #define DDRCTLCH1_CR_DLLPITESTANDADC_PhaseDrvPwrSavOn_WID            ( 1)
  #define DDRCTLCH1_CR_DLLPITESTANDADC_PhaseDrvPwrSavOn_MSK            (0x02000000)
  #define DDRCTLCH1_CR_DLLPITESTANDADC_PhaseDrvPwrSavOn_MIN            (0)
  #define DDRCTLCH1_CR_DLLPITESTANDADC_PhaseDrvPwrSavOn_MAX            (1) // 0x00000001
  #define DDRCTLCH1_CR_DLLPITESTANDADC_PhaseDrvPwrSavOn_DEF            (0x00000000)
  #define DDRCTLCH1_CR_DLLPITESTANDADC_PhaseDrvPwrSavOn_HSH            (0x01191D24)

  #define DDRCTLCH1_CR_DLLPITESTANDADC_Spare_OFF                       (26)
  #define DDRCTLCH1_CR_DLLPITESTANDADC_Spare_WID                       ( 6)
  #define DDRCTLCH1_CR_DLLPITESTANDADC_Spare_MSK                       (0xFC000000)
  #define DDRCTLCH1_CR_DLLPITESTANDADC_Spare_MIN                       (0)
  #define DDRCTLCH1_CR_DLLPITESTANDADC_Spare_MAX                       (63) // 0x0000003F
  #define DDRCTLCH1_CR_DLLPITESTANDADC_Spare_DEF                       (0x00000000)
  #define DDRCTLCH1_CR_DLLPITESTANDADC_Spare_HSH                       (0x061A1D24)
#pragma pack(pop)
#endif
