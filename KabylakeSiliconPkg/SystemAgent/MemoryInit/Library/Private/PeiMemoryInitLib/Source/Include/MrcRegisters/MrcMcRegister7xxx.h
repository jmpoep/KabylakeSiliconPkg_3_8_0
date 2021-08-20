#ifndef __MrcMcRegister7xxx_h__
#define __MrcMcRegister7xxx_h__
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


#define HUBS_CR_DMIVCLIM_HUBS_REG                                      (0x00007000)

  #define HUBS_CR_DMIVCLIM_HUBS_VCPNPLIM_OFF                           ( 0)
  #define HUBS_CR_DMIVCLIM_HUBS_VCPNPLIM_WID                           ( 3)
  #define HUBS_CR_DMIVCLIM_HUBS_VCPNPLIM_MSK                           (0x00000007)
  #define HUBS_CR_DMIVCLIM_HUBS_VCPNPLIM_MIN                           (0)
  #define HUBS_CR_DMIVCLIM_HUBS_VCPNPLIM_MAX                           (7) // 0x00000007
  #define HUBS_CR_DMIVCLIM_HUBS_VCPNPLIM_DEF                           (0x00000004)
  #define HUBS_CR_DMIVCLIM_HUBS_VCPNPLIM_HSH                           (0x03007000)

  #define HUBS_CR_DMIVCLIM_HUBS_VCPPLIM_OFF                            ( 4)
  #define HUBS_CR_DMIVCLIM_HUBS_VCPPLIM_WID                            ( 3)
  #define HUBS_CR_DMIVCLIM_HUBS_VCPPLIM_MSK                            (0x00000070)
  #define HUBS_CR_DMIVCLIM_HUBS_VCPPLIM_MIN                            (0)
  #define HUBS_CR_DMIVCLIM_HUBS_VCPPLIM_MAX                            (7) // 0x00000007
  #define HUBS_CR_DMIVCLIM_HUBS_VCPPLIM_DEF                            (0x00000004)
  #define HUBS_CR_DMIVCLIM_HUBS_VCPPLIM_HSH                            (0x03047000)

  #define HUBS_CR_DMIVCLIM_HUBS_VCMNPLIM_OFF                           ( 8)
  #define HUBS_CR_DMIVCLIM_HUBS_VCMNPLIM_WID                           ( 3)
  #define HUBS_CR_DMIVCLIM_HUBS_VCMNPLIM_MSK                           (0x00000700)
  #define HUBS_CR_DMIVCLIM_HUBS_VCMNPLIM_MIN                           (0)
  #define HUBS_CR_DMIVCLIM_HUBS_VCMNPLIM_MAX                           (7) // 0x00000007
  #define HUBS_CR_DMIVCLIM_HUBS_VCMNPLIM_DEF                           (0x00000004)
  #define HUBS_CR_DMIVCLIM_HUBS_VCMNPLIM_HSH                           (0x03087000)

  #define HUBS_CR_DMIVCLIM_HUBS_VCMPLIM_OFF                            (12)
  #define HUBS_CR_DMIVCLIM_HUBS_VCMPLIM_WID                            ( 3)
  #define HUBS_CR_DMIVCLIM_HUBS_VCMPLIM_MSK                            (0x00007000)
  #define HUBS_CR_DMIVCLIM_HUBS_VCMPLIM_MIN                            (0)
  #define HUBS_CR_DMIVCLIM_HUBS_VCMPLIM_MAX                            (7) // 0x00000007
  #define HUBS_CR_DMIVCLIM_HUBS_VCMPLIM_DEF                            (0x00000004)
  #define HUBS_CR_DMIVCLIM_HUBS_VCMPLIM_HSH                            (0x030C7000)

  #define HUBS_CR_DMIVCLIM_HUBS_VCPCMPLIM_OFF                          (16)
  #define HUBS_CR_DMIVCLIM_HUBS_VCPCMPLIM_WID                          ( 3)
  #define HUBS_CR_DMIVCLIM_HUBS_VCPCMPLIM_MSK                          (0x00070000)
  #define HUBS_CR_DMIVCLIM_HUBS_VCPCMPLIM_MIN                          (0)
  #define HUBS_CR_DMIVCLIM_HUBS_VCPCMPLIM_MAX                          (7) // 0x00000007
  #define HUBS_CR_DMIVCLIM_HUBS_VCPCMPLIM_DEF                          (0x00000004)
  #define HUBS_CR_DMIVCLIM_HUBS_VCPCMPLIM_HSH                          (0x03107000)

  #define HUBS_CR_DMIVCLIM_HUBS_VCMCMPLIM_OFF                          (20)
  #define HUBS_CR_DMIVCLIM_HUBS_VCMCMPLIM_WID                          ( 3)
  #define HUBS_CR_DMIVCLIM_HUBS_VCMCMPLIM_MSK                          (0x00700000)
  #define HUBS_CR_DMIVCLIM_HUBS_VCMCMPLIM_MIN                          (0)
  #define HUBS_CR_DMIVCLIM_HUBS_VCMCMPLIM_MAX                          (7) // 0x00000007
  #define HUBS_CR_DMIVCLIM_HUBS_VCMCMPLIM_DEF                          (0x00000004)
  #define HUBS_CR_DMIVCLIM_HUBS_VCMCMPLIM_HSH                          (0x03147000)

  #define HUBS_CR_DMIVCLIM_HUBS_LOCK_OFF                               (31)
  #define HUBS_CR_DMIVCLIM_HUBS_LOCK_WID                               ( 1)
  #define HUBS_CR_DMIVCLIM_HUBS_LOCK_MSK                               (0x80000000)
  #define HUBS_CR_DMIVCLIM_HUBS_LOCK_MIN                               (0)
  #define HUBS_CR_DMIVCLIM_HUBS_LOCK_MAX                               (1) // 0x00000001
  #define HUBS_CR_DMIVCLIM_HUBS_LOCK_DEF                               (0x00000000)
  #define HUBS_CR_DMIVCLIM_HUBS_LOCK_HSH                               (0x011F7000)

#define HUBS_CR_HUB0_PWRDN_OVRD_HUBS_REG                               (0x00007010)

  #define HUBS_CR_HUB0_PWRDN_OVRD_HUBS_P0_OFF                          ( 0)
  #define HUBS_CR_HUB0_PWRDN_OVRD_HUBS_P0_WID                          ( 1)
  #define HUBS_CR_HUB0_PWRDN_OVRD_HUBS_P0_MSK                          (0x00000001)
  #define HUBS_CR_HUB0_PWRDN_OVRD_HUBS_P0_MIN                          (0)
  #define HUBS_CR_HUB0_PWRDN_OVRD_HUBS_P0_MAX                          (1) // 0x00000001
  #define HUBS_CR_HUB0_PWRDN_OVRD_HUBS_P0_DEF                          (0x00000000)
  #define HUBS_CR_HUB0_PWRDN_OVRD_HUBS_P0_HSH                          (0x01007010)

  #define HUBS_CR_HUB0_PWRDN_OVRD_HUBS_P1_OFF                          ( 1)
  #define HUBS_CR_HUB0_PWRDN_OVRD_HUBS_P1_WID                          ( 1)
  #define HUBS_CR_HUB0_PWRDN_OVRD_HUBS_P1_MSK                          (0x00000002)
  #define HUBS_CR_HUB0_PWRDN_OVRD_HUBS_P1_MIN                          (0)
  #define HUBS_CR_HUB0_PWRDN_OVRD_HUBS_P1_MAX                          (1) // 0x00000001
  #define HUBS_CR_HUB0_PWRDN_OVRD_HUBS_P1_DEF                          (0x00000000)
  #define HUBS_CR_HUB0_PWRDN_OVRD_HUBS_P1_HSH                          (0x01017010)

  #define HUBS_CR_HUB0_PWRDN_OVRD_HUBS_P2_OFF                          ( 2)
  #define HUBS_CR_HUB0_PWRDN_OVRD_HUBS_P2_WID                          ( 1)
  #define HUBS_CR_HUB0_PWRDN_OVRD_HUBS_P2_MSK                          (0x00000004)
  #define HUBS_CR_HUB0_PWRDN_OVRD_HUBS_P2_MIN                          (0)
  #define HUBS_CR_HUB0_PWRDN_OVRD_HUBS_P2_MAX                          (1) // 0x00000001
  #define HUBS_CR_HUB0_PWRDN_OVRD_HUBS_P2_DEF                          (0x00000000)
  #define HUBS_CR_HUB0_PWRDN_OVRD_HUBS_P2_HSH                          (0x01027010)

  #define HUBS_CR_HUB0_PWRDN_OVRD_HUBS_P3_OFF                          ( 3)
  #define HUBS_CR_HUB0_PWRDN_OVRD_HUBS_P3_WID                          ( 1)
  #define HUBS_CR_HUB0_PWRDN_OVRD_HUBS_P3_MSK                          (0x00000008)
  #define HUBS_CR_HUB0_PWRDN_OVRD_HUBS_P3_MIN                          (0)
  #define HUBS_CR_HUB0_PWRDN_OVRD_HUBS_P3_MAX                          (1) // 0x00000001
  #define HUBS_CR_HUB0_PWRDN_OVRD_HUBS_P3_DEF                          (0x00000000)
  #define HUBS_CR_HUB0_PWRDN_OVRD_HUBS_P3_HSH                          (0x01037010)

  #define HUBS_CR_HUB0_PWRDN_OVRD_HUBS_MSGCH_GATECLK_DISABLE_OFF       ( 4)
  #define HUBS_CR_HUB0_PWRDN_OVRD_HUBS_MSGCH_GATECLK_DISABLE_WID       ( 1)
  #define HUBS_CR_HUB0_PWRDN_OVRD_HUBS_MSGCH_GATECLK_DISABLE_MSK       (0x00000010)
  #define HUBS_CR_HUB0_PWRDN_OVRD_HUBS_MSGCH_GATECLK_DISABLE_MIN       (0)
  #define HUBS_CR_HUB0_PWRDN_OVRD_HUBS_MSGCH_GATECLK_DISABLE_MAX       (1) // 0x00000001
  #define HUBS_CR_HUB0_PWRDN_OVRD_HUBS_MSGCH_GATECLK_DISABLE_DEF       (0x00000000)
  #define HUBS_CR_HUB0_PWRDN_OVRD_HUBS_MSGCH_GATECLK_DISABLE_HSH       (0x01047010)

  #define HUBS_CR_HUB0_PWRDN_OVRD_HUBS_MSGCH_NOPEG_AUTOCOM_ENABLE_OFF  ( 5)
  #define HUBS_CR_HUB0_PWRDN_OVRD_HUBS_MSGCH_NOPEG_AUTOCOM_ENABLE_WID  ( 1)
  #define HUBS_CR_HUB0_PWRDN_OVRD_HUBS_MSGCH_NOPEG_AUTOCOM_ENABLE_MSK  (0x00000020)
  #define HUBS_CR_HUB0_PWRDN_OVRD_HUBS_MSGCH_NOPEG_AUTOCOM_ENABLE_MIN  (0)
  #define HUBS_CR_HUB0_PWRDN_OVRD_HUBS_MSGCH_NOPEG_AUTOCOM_ENABLE_MAX  (1) // 0x00000001
  #define HUBS_CR_HUB0_PWRDN_OVRD_HUBS_MSGCH_NOPEG_AUTOCOM_ENABLE_DEF  (0x00000000)
  #define HUBS_CR_HUB0_PWRDN_OVRD_HUBS_MSGCH_NOPEG_AUTOCOM_ENABLE_HSH  (0x01057010)

  #define HUBS_CR_HUB0_PWRDN_OVRD_HUBS_RESERVED_RW_OFF                 ( 6)
  #define HUBS_CR_HUB0_PWRDN_OVRD_HUBS_RESERVED_RW_WID                 (16)
  #define HUBS_CR_HUB0_PWRDN_OVRD_HUBS_RESERVED_RW_MSK                 (0x003FFFC0)
  #define HUBS_CR_HUB0_PWRDN_OVRD_HUBS_RESERVED_RW_MIN                 (0)
  #define HUBS_CR_HUB0_PWRDN_OVRD_HUBS_RESERVED_RW_MAX                 (65535) // 0x0000FFFF
  #define HUBS_CR_HUB0_PWRDN_OVRD_HUBS_RESERVED_RW_DEF                 (0x00000000)
  #define HUBS_CR_HUB0_PWRDN_OVRD_HUBS_RESERVED_RW_HSH                 (0x10067010)

  #define HUBS_CR_HUB0_PWRDN_OVRD_HUBS_RESERVED_VARIANT_OFF            (22)
  #define HUBS_CR_HUB0_PWRDN_OVRD_HUBS_RESERVED_VARIANT_WID            ( 5)
  #define HUBS_CR_HUB0_PWRDN_OVRD_HUBS_RESERVED_VARIANT_MSK            (0x07C00000)
  #define HUBS_CR_HUB0_PWRDN_OVRD_HUBS_RESERVED_VARIANT_MIN            (0)
  #define HUBS_CR_HUB0_PWRDN_OVRD_HUBS_RESERVED_VARIANT_MAX            (31) // 0x0000001F
  #define HUBS_CR_HUB0_PWRDN_OVRD_HUBS_RESERVED_VARIANT_DEF            (0x00000000)
  #define HUBS_CR_HUB0_PWRDN_OVRD_HUBS_RESERVED_VARIANT_HSH            (0x05167010)

  #define HUBS_CR_HUB0_PWRDN_OVRD_HUBS_RESERVED_VARIANT_STICKY_OFF     (27)
  #define HUBS_CR_HUB0_PWRDN_OVRD_HUBS_RESERVED_VARIANT_STICKY_WID     ( 5)
  #define HUBS_CR_HUB0_PWRDN_OVRD_HUBS_RESERVED_VARIANT_STICKY_MSK     (0xF8000000)
  #define HUBS_CR_HUB0_PWRDN_OVRD_HUBS_RESERVED_VARIANT_STICKY_MIN     (0)
  #define HUBS_CR_HUB0_PWRDN_OVRD_HUBS_RESERVED_VARIANT_STICKY_MAX     (31) // 0x0000001F
  #define HUBS_CR_HUB0_PWRDN_OVRD_HUBS_RESERVED_VARIANT_STICKY_DEF     (0x00000000)
  #define HUBS_CR_HUB0_PWRDN_OVRD_HUBS_RESERVED_VARIANT_STICKY_HSH     (0x051B7010)

#define HUBS_CR_HUB1_PWRDN_OVRD_HUBS_REG                               (0x00007014)

  #define HUBS_CR_HUB1_PWRDN_OVRD_HUBS_P0_OFF                          ( 0)
  #define HUBS_CR_HUB1_PWRDN_OVRD_HUBS_P0_WID                          ( 1)
  #define HUBS_CR_HUB1_PWRDN_OVRD_HUBS_P0_MSK                          (0x00000001)
  #define HUBS_CR_HUB1_PWRDN_OVRD_HUBS_P0_MIN                          (0)
  #define HUBS_CR_HUB1_PWRDN_OVRD_HUBS_P0_MAX                          (1) // 0x00000001
  #define HUBS_CR_HUB1_PWRDN_OVRD_HUBS_P0_DEF                          (0x00000000)
  #define HUBS_CR_HUB1_PWRDN_OVRD_HUBS_P0_HSH                          (0x01007014)

  #define HUBS_CR_HUB1_PWRDN_OVRD_HUBS_P1_OFF                          ( 1)
  #define HUBS_CR_HUB1_PWRDN_OVRD_HUBS_P1_WID                          ( 1)
  #define HUBS_CR_HUB1_PWRDN_OVRD_HUBS_P1_MSK                          (0x00000002)
  #define HUBS_CR_HUB1_PWRDN_OVRD_HUBS_P1_MIN                          (0)
  #define HUBS_CR_HUB1_PWRDN_OVRD_HUBS_P1_MAX                          (1) // 0x00000001
  #define HUBS_CR_HUB1_PWRDN_OVRD_HUBS_P1_DEF                          (0x00000000)
  #define HUBS_CR_HUB1_PWRDN_OVRD_HUBS_P1_HSH                          (0x01017014)

  #define HUBS_CR_HUB1_PWRDN_OVRD_HUBS_P2_OFF                          ( 2)
  #define HUBS_CR_HUB1_PWRDN_OVRD_HUBS_P2_WID                          ( 1)
  #define HUBS_CR_HUB1_PWRDN_OVRD_HUBS_P2_MSK                          (0x00000004)
  #define HUBS_CR_HUB1_PWRDN_OVRD_HUBS_P2_MIN                          (0)
  #define HUBS_CR_HUB1_PWRDN_OVRD_HUBS_P2_MAX                          (1) // 0x00000001
  #define HUBS_CR_HUB1_PWRDN_OVRD_HUBS_P2_DEF                          (0x00000000)
  #define HUBS_CR_HUB1_PWRDN_OVRD_HUBS_P2_HSH                          (0x01027014)

  #define HUBS_CR_HUB1_PWRDN_OVRD_HUBS_P3_OFF                          ( 3)
  #define HUBS_CR_HUB1_PWRDN_OVRD_HUBS_P3_WID                          ( 1)
  #define HUBS_CR_HUB1_PWRDN_OVRD_HUBS_P3_MSK                          (0x00000008)
  #define HUBS_CR_HUB1_PWRDN_OVRD_HUBS_P3_MIN                          (0)
  #define HUBS_CR_HUB1_PWRDN_OVRD_HUBS_P3_MAX                          (1) // 0x00000001
  #define HUBS_CR_HUB1_PWRDN_OVRD_HUBS_P3_DEF                          (0x00000000)
  #define HUBS_CR_HUB1_PWRDN_OVRD_HUBS_P3_HSH                          (0x01037014)

  #define HUBS_CR_HUB1_PWRDN_OVRD_HUBS_MSGCH_GSA_AUTOCOM_ENABLE_OFF    ( 5)
  #define HUBS_CR_HUB1_PWRDN_OVRD_HUBS_MSGCH_GSA_AUTOCOM_ENABLE_WID    ( 1)
  #define HUBS_CR_HUB1_PWRDN_OVRD_HUBS_MSGCH_GSA_AUTOCOM_ENABLE_MSK    (0x00000020)
  #define HUBS_CR_HUB1_PWRDN_OVRD_HUBS_MSGCH_GSA_AUTOCOM_ENABLE_MIN    (0)
  #define HUBS_CR_HUB1_PWRDN_OVRD_HUBS_MSGCH_GSA_AUTOCOM_ENABLE_MAX    (1) // 0x00000001
  #define HUBS_CR_HUB1_PWRDN_OVRD_HUBS_MSGCH_GSA_AUTOCOM_ENABLE_DEF    (0x00000000)
  #define HUBS_CR_HUB1_PWRDN_OVRD_HUBS_MSGCH_GSA_AUTOCOM_ENABLE_HSH    (0x01057014)

  #define HUBS_CR_HUB1_PWRDN_OVRD_HUBS_RESERVED_VARIANT_OFF            (22)
  #define HUBS_CR_HUB1_PWRDN_OVRD_HUBS_RESERVED_VARIANT_WID            ( 5)
  #define HUBS_CR_HUB1_PWRDN_OVRD_HUBS_RESERVED_VARIANT_MSK            (0x07C00000)
  #define HUBS_CR_HUB1_PWRDN_OVRD_HUBS_RESERVED_VARIANT_MIN            (0)
  #define HUBS_CR_HUB1_PWRDN_OVRD_HUBS_RESERVED_VARIANT_MAX            (31) // 0x0000001F
  #define HUBS_CR_HUB1_PWRDN_OVRD_HUBS_RESERVED_VARIANT_DEF            (0x00000000)
  #define HUBS_CR_HUB1_PWRDN_OVRD_HUBS_RESERVED_VARIANT_HSH            (0x05167014)

  #define HUBS_CR_HUB1_PWRDN_OVRD_HUBS_RESERVED_VARIANT_STICKY_OFF     (27)
  #define HUBS_CR_HUB1_PWRDN_OVRD_HUBS_RESERVED_VARIANT_STICKY_WID     ( 5)
  #define HUBS_CR_HUB1_PWRDN_OVRD_HUBS_RESERVED_VARIANT_STICKY_MSK     (0xF8000000)
  #define HUBS_CR_HUB1_PWRDN_OVRD_HUBS_RESERVED_VARIANT_STICKY_MIN     (0)
  #define HUBS_CR_HUB1_PWRDN_OVRD_HUBS_RESERVED_VARIANT_STICKY_MAX     (31) // 0x0000001F
  #define HUBS_CR_HUB1_PWRDN_OVRD_HUBS_RESERVED_VARIANT_STICKY_DEF     (0x00000000)
  #define HUBS_CR_HUB1_PWRDN_OVRD_HUBS_RESERVED_VARIANT_STICKY_HSH     (0x051B7014)

#define HUBS_CR_HUB2_PWRDN_OVRD_HUBS_REG                               (0x00007018)

  #define HUBS_CR_HUB2_PWRDN_OVRD_HUBS_P0_OFF                          ( 0)
  #define HUBS_CR_HUB2_PWRDN_OVRD_HUBS_P0_WID                          ( 1)
  #define HUBS_CR_HUB2_PWRDN_OVRD_HUBS_P0_MSK                          (0x00000001)
  #define HUBS_CR_HUB2_PWRDN_OVRD_HUBS_P0_MIN                          (0)
  #define HUBS_CR_HUB2_PWRDN_OVRD_HUBS_P0_MAX                          (1) // 0x00000001
  #define HUBS_CR_HUB2_PWRDN_OVRD_HUBS_P0_DEF                          (0x00000000)
  #define HUBS_CR_HUB2_PWRDN_OVRD_HUBS_P0_HSH                          (0x01007018)

  #define HUBS_CR_HUB2_PWRDN_OVRD_HUBS_P1_OFF                          ( 1)
  #define HUBS_CR_HUB2_PWRDN_OVRD_HUBS_P1_WID                          ( 1)
  #define HUBS_CR_HUB2_PWRDN_OVRD_HUBS_P1_MSK                          (0x00000002)
  #define HUBS_CR_HUB2_PWRDN_OVRD_HUBS_P1_MIN                          (0)
  #define HUBS_CR_HUB2_PWRDN_OVRD_HUBS_P1_MAX                          (1) // 0x00000001
  #define HUBS_CR_HUB2_PWRDN_OVRD_HUBS_P1_DEF                          (0x00000000)
  #define HUBS_CR_HUB2_PWRDN_OVRD_HUBS_P1_HSH                          (0x01017018)

  #define HUBS_CR_HUB2_PWRDN_OVRD_HUBS_P2_OFF                          ( 2)
  #define HUBS_CR_HUB2_PWRDN_OVRD_HUBS_P2_WID                          ( 1)
  #define HUBS_CR_HUB2_PWRDN_OVRD_HUBS_P2_MSK                          (0x00000004)
  #define HUBS_CR_HUB2_PWRDN_OVRD_HUBS_P2_MIN                          (0)
  #define HUBS_CR_HUB2_PWRDN_OVRD_HUBS_P2_MAX                          (1) // 0x00000001
  #define HUBS_CR_HUB2_PWRDN_OVRD_HUBS_P2_DEF                          (0x00000000)
  #define HUBS_CR_HUB2_PWRDN_OVRD_HUBS_P2_HSH                          (0x01027018)

  #define HUBS_CR_HUB2_PWRDN_OVRD_HUBS_P3_OFF                          ( 3)
  #define HUBS_CR_HUB2_PWRDN_OVRD_HUBS_P3_WID                          ( 1)
  #define HUBS_CR_HUB2_PWRDN_OVRD_HUBS_P3_MSK                          (0x00000008)
  #define HUBS_CR_HUB2_PWRDN_OVRD_HUBS_P3_MIN                          (0)
  #define HUBS_CR_HUB2_PWRDN_OVRD_HUBS_P3_MAX                          (1) // 0x00000001
  #define HUBS_CR_HUB2_PWRDN_OVRD_HUBS_P3_DEF                          (0x00000000)
  #define HUBS_CR_HUB2_PWRDN_OVRD_HUBS_P3_HSH                          (0x01037018)

  #define HUBS_CR_HUB2_PWRDN_OVRD_HUBS_MSGCH_GSA_AUTOCOM_ENABLE_OFF    ( 5)
  #define HUBS_CR_HUB2_PWRDN_OVRD_HUBS_MSGCH_GSA_AUTOCOM_ENABLE_WID    ( 1)
  #define HUBS_CR_HUB2_PWRDN_OVRD_HUBS_MSGCH_GSA_AUTOCOM_ENABLE_MSK    (0x00000020)
  #define HUBS_CR_HUB2_PWRDN_OVRD_HUBS_MSGCH_GSA_AUTOCOM_ENABLE_MIN    (0)
  #define HUBS_CR_HUB2_PWRDN_OVRD_HUBS_MSGCH_GSA_AUTOCOM_ENABLE_MAX    (1) // 0x00000001
  #define HUBS_CR_HUB2_PWRDN_OVRD_HUBS_MSGCH_GSA_AUTOCOM_ENABLE_DEF    (0x00000000)
  #define HUBS_CR_HUB2_PWRDN_OVRD_HUBS_MSGCH_GSA_AUTOCOM_ENABLE_HSH    (0x01057018)

  #define HUBS_CR_HUB2_PWRDN_OVRD_HUBS_RESERVED_VARIANT_OFF            (22)
  #define HUBS_CR_HUB2_PWRDN_OVRD_HUBS_RESERVED_VARIANT_WID            ( 5)
  #define HUBS_CR_HUB2_PWRDN_OVRD_HUBS_RESERVED_VARIANT_MSK            (0x07C00000)
  #define HUBS_CR_HUB2_PWRDN_OVRD_HUBS_RESERVED_VARIANT_MIN            (0)
  #define HUBS_CR_HUB2_PWRDN_OVRD_HUBS_RESERVED_VARIANT_MAX            (31) // 0x0000001F
  #define HUBS_CR_HUB2_PWRDN_OVRD_HUBS_RESERVED_VARIANT_DEF            (0x00000000)
  #define HUBS_CR_HUB2_PWRDN_OVRD_HUBS_RESERVED_VARIANT_HSH            (0x05167018)

  #define HUBS_CR_HUB2_PWRDN_OVRD_HUBS_RESERVED_VARIANT_STICKY_OFF     (27)
  #define HUBS_CR_HUB2_PWRDN_OVRD_HUBS_RESERVED_VARIANT_STICKY_WID     ( 5)
  #define HUBS_CR_HUB2_PWRDN_OVRD_HUBS_RESERVED_VARIANT_STICKY_MSK     (0xF8000000)
  #define HUBS_CR_HUB2_PWRDN_OVRD_HUBS_RESERVED_VARIANT_STICKY_MIN     (0)
  #define HUBS_CR_HUB2_PWRDN_OVRD_HUBS_RESERVED_VARIANT_STICKY_MAX     (31) // 0x0000001F
  #define HUBS_CR_HUB2_PWRDN_OVRD_HUBS_RESERVED_VARIANT_STICKY_DEF     (0x00000000)
  #define HUBS_CR_HUB2_PWRDN_OVRD_HUBS_RESERVED_VARIANT_STICKY_HSH     (0x051B7018)

#define HUBS_CR_HUB0_DEFEATURE_HUBS_REG                                (0x0000701C)

  #define HUBS_CR_HUB0_DEFEATURE_HUBS_BLK_GNT_P0_OFF                   ( 0)
  #define HUBS_CR_HUB0_DEFEATURE_HUBS_BLK_GNT_P0_WID                   ( 1)
  #define HUBS_CR_HUB0_DEFEATURE_HUBS_BLK_GNT_P0_MSK                   (0x00000001)
  #define HUBS_CR_HUB0_DEFEATURE_HUBS_BLK_GNT_P0_MIN                   (0)
  #define HUBS_CR_HUB0_DEFEATURE_HUBS_BLK_GNT_P0_MAX                   (1) // 0x00000001
  #define HUBS_CR_HUB0_DEFEATURE_HUBS_BLK_GNT_P0_DEF                   (0x00000000)
  #define HUBS_CR_HUB0_DEFEATURE_HUBS_BLK_GNT_P0_HSH                   (0x0100701C)

  #define HUBS_CR_HUB0_DEFEATURE_HUBS_BLK_GNT_P1_OFF                   ( 1)
  #define HUBS_CR_HUB0_DEFEATURE_HUBS_BLK_GNT_P1_WID                   ( 1)
  #define HUBS_CR_HUB0_DEFEATURE_HUBS_BLK_GNT_P1_MSK                   (0x00000002)
  #define HUBS_CR_HUB0_DEFEATURE_HUBS_BLK_GNT_P1_MIN                   (0)
  #define HUBS_CR_HUB0_DEFEATURE_HUBS_BLK_GNT_P1_MAX                   (1) // 0x00000001
  #define HUBS_CR_HUB0_DEFEATURE_HUBS_BLK_GNT_P1_DEF                   (0x00000000)
  #define HUBS_CR_HUB0_DEFEATURE_HUBS_BLK_GNT_P1_HSH                   (0x0101701C)

  #define HUBS_CR_HUB0_DEFEATURE_HUBS_BLK_GNT_P2_OFF                   ( 2)
  #define HUBS_CR_HUB0_DEFEATURE_HUBS_BLK_GNT_P2_WID                   ( 1)
  #define HUBS_CR_HUB0_DEFEATURE_HUBS_BLK_GNT_P2_MSK                   (0x00000004)
  #define HUBS_CR_HUB0_DEFEATURE_HUBS_BLK_GNT_P2_MIN                   (0)
  #define HUBS_CR_HUB0_DEFEATURE_HUBS_BLK_GNT_P2_MAX                   (1) // 0x00000001
  #define HUBS_CR_HUB0_DEFEATURE_HUBS_BLK_GNT_P2_DEF                   (0x00000000)
  #define HUBS_CR_HUB0_DEFEATURE_HUBS_BLK_GNT_P2_HSH                   (0x0102701C)

  #define HUBS_CR_HUB0_DEFEATURE_HUBS_BLK_GNT_P3_OFF                   ( 3)
  #define HUBS_CR_HUB0_DEFEATURE_HUBS_BLK_GNT_P3_WID                   ( 1)
  #define HUBS_CR_HUB0_DEFEATURE_HUBS_BLK_GNT_P3_MSK                   (0x00000008)
  #define HUBS_CR_HUB0_DEFEATURE_HUBS_BLK_GNT_P3_MIN                   (0)
  #define HUBS_CR_HUB0_DEFEATURE_HUBS_BLK_GNT_P3_MAX                   (1) // 0x00000001
  #define HUBS_CR_HUB0_DEFEATURE_HUBS_BLK_GNT_P3_DEF                   (0x00000000)
  #define HUBS_CR_HUB0_DEFEATURE_HUBS_BLK_GNT_P3_HSH                   (0x0103701C)

  #define HUBS_CR_HUB0_DEFEATURE_HUBS_BLK_PUT_P0_OFF                   ( 4)
  #define HUBS_CR_HUB0_DEFEATURE_HUBS_BLK_PUT_P0_WID                   ( 1)
  #define HUBS_CR_HUB0_DEFEATURE_HUBS_BLK_PUT_P0_MSK                   (0x00000010)
  #define HUBS_CR_HUB0_DEFEATURE_HUBS_BLK_PUT_P0_MIN                   (0)
  #define HUBS_CR_HUB0_DEFEATURE_HUBS_BLK_PUT_P0_MAX                   (1) // 0x00000001
  #define HUBS_CR_HUB0_DEFEATURE_HUBS_BLK_PUT_P0_DEF                   (0x00000000)
  #define HUBS_CR_HUB0_DEFEATURE_HUBS_BLK_PUT_P0_HSH                   (0x0104701C)

  #define HUBS_CR_HUB0_DEFEATURE_HUBS_BLK_PUT_P1_OFF                   ( 5)
  #define HUBS_CR_HUB0_DEFEATURE_HUBS_BLK_PUT_P1_WID                   ( 1)
  #define HUBS_CR_HUB0_DEFEATURE_HUBS_BLK_PUT_P1_MSK                   (0x00000020)
  #define HUBS_CR_HUB0_DEFEATURE_HUBS_BLK_PUT_P1_MIN                   (0)
  #define HUBS_CR_HUB0_DEFEATURE_HUBS_BLK_PUT_P1_MAX                   (1) // 0x00000001
  #define HUBS_CR_HUB0_DEFEATURE_HUBS_BLK_PUT_P1_DEF                   (0x00000000)
  #define HUBS_CR_HUB0_DEFEATURE_HUBS_BLK_PUT_P1_HSH                   (0x0105701C)

  #define HUBS_CR_HUB0_DEFEATURE_HUBS_BLK_PUT_P2_OFF                   ( 6)
  #define HUBS_CR_HUB0_DEFEATURE_HUBS_BLK_PUT_P2_WID                   ( 1)
  #define HUBS_CR_HUB0_DEFEATURE_HUBS_BLK_PUT_P2_MSK                   (0x00000040)
  #define HUBS_CR_HUB0_DEFEATURE_HUBS_BLK_PUT_P2_MIN                   (0)
  #define HUBS_CR_HUB0_DEFEATURE_HUBS_BLK_PUT_P2_MAX                   (1) // 0x00000001
  #define HUBS_CR_HUB0_DEFEATURE_HUBS_BLK_PUT_P2_DEF                   (0x00000000)
  #define HUBS_CR_HUB0_DEFEATURE_HUBS_BLK_PUT_P2_HSH                   (0x0106701C)

  #define HUBS_CR_HUB0_DEFEATURE_HUBS_BLK_PUT_P3_OFF                   ( 7)
  #define HUBS_CR_HUB0_DEFEATURE_HUBS_BLK_PUT_P3_WID                   ( 1)
  #define HUBS_CR_HUB0_DEFEATURE_HUBS_BLK_PUT_P3_MSK                   (0x00000080)
  #define HUBS_CR_HUB0_DEFEATURE_HUBS_BLK_PUT_P3_MIN                   (0)
  #define HUBS_CR_HUB0_DEFEATURE_HUBS_BLK_PUT_P3_MAX                   (1) // 0x00000001
  #define HUBS_CR_HUB0_DEFEATURE_HUBS_BLK_PUT_P3_DEF                   (0x00000000)
  #define HUBS_CR_HUB0_DEFEATURE_HUBS_BLK_PUT_P3_HSH                   (0x0107701C)

  #define HUBS_CR_HUB0_DEFEATURE_HUBS_NO_CHAIN_P0_OFF                  ( 8)
  #define HUBS_CR_HUB0_DEFEATURE_HUBS_NO_CHAIN_P0_WID                  ( 1)
  #define HUBS_CR_HUB0_DEFEATURE_HUBS_NO_CHAIN_P0_MSK                  (0x00000100)
  #define HUBS_CR_HUB0_DEFEATURE_HUBS_NO_CHAIN_P0_MIN                  (0)
  #define HUBS_CR_HUB0_DEFEATURE_HUBS_NO_CHAIN_P0_MAX                  (1) // 0x00000001
  #define HUBS_CR_HUB0_DEFEATURE_HUBS_NO_CHAIN_P0_DEF                  (0x00000000)
  #define HUBS_CR_HUB0_DEFEATURE_HUBS_NO_CHAIN_P0_HSH                  (0x0108701C)

  #define HUBS_CR_HUB0_DEFEATURE_HUBS_NO_CHAIN_P1_OFF                  ( 9)
  #define HUBS_CR_HUB0_DEFEATURE_HUBS_NO_CHAIN_P1_WID                  ( 1)
  #define HUBS_CR_HUB0_DEFEATURE_HUBS_NO_CHAIN_P1_MSK                  (0x00000200)
  #define HUBS_CR_HUB0_DEFEATURE_HUBS_NO_CHAIN_P1_MIN                  (0)
  #define HUBS_CR_HUB0_DEFEATURE_HUBS_NO_CHAIN_P1_MAX                  (1) // 0x00000001
  #define HUBS_CR_HUB0_DEFEATURE_HUBS_NO_CHAIN_P1_DEF                  (0x00000000)
  #define HUBS_CR_HUB0_DEFEATURE_HUBS_NO_CHAIN_P1_HSH                  (0x0109701C)

  #define HUBS_CR_HUB0_DEFEATURE_HUBS_NO_CHAIN_P2_OFF                  (10)
  #define HUBS_CR_HUB0_DEFEATURE_HUBS_NO_CHAIN_P2_WID                  ( 1)
  #define HUBS_CR_HUB0_DEFEATURE_HUBS_NO_CHAIN_P2_MSK                  (0x00000400)
  #define HUBS_CR_HUB0_DEFEATURE_HUBS_NO_CHAIN_P2_MIN                  (0)
  #define HUBS_CR_HUB0_DEFEATURE_HUBS_NO_CHAIN_P2_MAX                  (1) // 0x00000001
  #define HUBS_CR_HUB0_DEFEATURE_HUBS_NO_CHAIN_P2_DEF                  (0x00000000)
  #define HUBS_CR_HUB0_DEFEATURE_HUBS_NO_CHAIN_P2_HSH                  (0x010A701C)

  #define HUBS_CR_HUB0_DEFEATURE_HUBS_NO_CHAIN_P3_OFF                  (11)
  #define HUBS_CR_HUB0_DEFEATURE_HUBS_NO_CHAIN_P3_WID                  ( 1)
  #define HUBS_CR_HUB0_DEFEATURE_HUBS_NO_CHAIN_P3_MSK                  (0x00000800)
  #define HUBS_CR_HUB0_DEFEATURE_HUBS_NO_CHAIN_P3_MIN                  (0)
  #define HUBS_CR_HUB0_DEFEATURE_HUBS_NO_CHAIN_P3_MAX                  (1) // 0x00000001
  #define HUBS_CR_HUB0_DEFEATURE_HUBS_NO_CHAIN_P3_DEF                  (0x00000000)
  #define HUBS_CR_HUB0_DEFEATURE_HUBS_NO_CHAIN_P3_HSH                  (0x010B701C)

  #define HUBS_CR_HUB0_DEFEATURE_HUBS_SLOW_UP_P0_OFF                   (12)
  #define HUBS_CR_HUB0_DEFEATURE_HUBS_SLOW_UP_P0_WID                   ( 1)
  #define HUBS_CR_HUB0_DEFEATURE_HUBS_SLOW_UP_P0_MSK                   (0x00001000)
  #define HUBS_CR_HUB0_DEFEATURE_HUBS_SLOW_UP_P0_MIN                   (0)
  #define HUBS_CR_HUB0_DEFEATURE_HUBS_SLOW_UP_P0_MAX                   (1) // 0x00000001
  #define HUBS_CR_HUB0_DEFEATURE_HUBS_SLOW_UP_P0_DEF                   (0x00000000)
  #define HUBS_CR_HUB0_DEFEATURE_HUBS_SLOW_UP_P0_HSH                   (0x010C701C)

  #define HUBS_CR_HUB0_DEFEATURE_HUBS_SLOW_UP_P1_OFF                   (13)
  #define HUBS_CR_HUB0_DEFEATURE_HUBS_SLOW_UP_P1_WID                   ( 1)
  #define HUBS_CR_HUB0_DEFEATURE_HUBS_SLOW_UP_P1_MSK                   (0x00002000)
  #define HUBS_CR_HUB0_DEFEATURE_HUBS_SLOW_UP_P1_MIN                   (0)
  #define HUBS_CR_HUB0_DEFEATURE_HUBS_SLOW_UP_P1_MAX                   (1) // 0x00000001
  #define HUBS_CR_HUB0_DEFEATURE_HUBS_SLOW_UP_P1_DEF                   (0x00000000)
  #define HUBS_CR_HUB0_DEFEATURE_HUBS_SLOW_UP_P1_HSH                   (0x010D701C)

  #define HUBS_CR_HUB0_DEFEATURE_HUBS_SLOW_UP_P2_OFF                   (14)
  #define HUBS_CR_HUB0_DEFEATURE_HUBS_SLOW_UP_P2_WID                   ( 1)
  #define HUBS_CR_HUB0_DEFEATURE_HUBS_SLOW_UP_P2_MSK                   (0x00004000)
  #define HUBS_CR_HUB0_DEFEATURE_HUBS_SLOW_UP_P2_MIN                   (0)
  #define HUBS_CR_HUB0_DEFEATURE_HUBS_SLOW_UP_P2_MAX                   (1) // 0x00000001
  #define HUBS_CR_HUB0_DEFEATURE_HUBS_SLOW_UP_P2_DEF                   (0x00000000)
  #define HUBS_CR_HUB0_DEFEATURE_HUBS_SLOW_UP_P2_HSH                   (0x010E701C)

  #define HUBS_CR_HUB0_DEFEATURE_HUBS_SLOW_UP_P3_OFF                   (15)
  #define HUBS_CR_HUB0_DEFEATURE_HUBS_SLOW_UP_P3_WID                   ( 1)
  #define HUBS_CR_HUB0_DEFEATURE_HUBS_SLOW_UP_P3_MSK                   (0x00008000)
  #define HUBS_CR_HUB0_DEFEATURE_HUBS_SLOW_UP_P3_MIN                   (0)
  #define HUBS_CR_HUB0_DEFEATURE_HUBS_SLOW_UP_P3_MAX                   (1) // 0x00000001
  #define HUBS_CR_HUB0_DEFEATURE_HUBS_SLOW_UP_P3_DEF                   (0x00000000)
  #define HUBS_CR_HUB0_DEFEATURE_HUBS_SLOW_UP_P3_HSH                   (0x010F701C)

  #define HUBS_CR_HUB0_DEFEATURE_HUBS_SLOW_DN_P0_OFF                   (16)
  #define HUBS_CR_HUB0_DEFEATURE_HUBS_SLOW_DN_P0_WID                   ( 1)
  #define HUBS_CR_HUB0_DEFEATURE_HUBS_SLOW_DN_P0_MSK                   (0x00010000)
  #define HUBS_CR_HUB0_DEFEATURE_HUBS_SLOW_DN_P0_MIN                   (0)
  #define HUBS_CR_HUB0_DEFEATURE_HUBS_SLOW_DN_P0_MAX                   (1) // 0x00000001
  #define HUBS_CR_HUB0_DEFEATURE_HUBS_SLOW_DN_P0_DEF                   (0x00000000)
  #define HUBS_CR_HUB0_DEFEATURE_HUBS_SLOW_DN_P0_HSH                   (0x0110701C)

  #define HUBS_CR_HUB0_DEFEATURE_HUBS_SLOW_DN_P1_OFF                   (17)
  #define HUBS_CR_HUB0_DEFEATURE_HUBS_SLOW_DN_P1_WID                   ( 1)
  #define HUBS_CR_HUB0_DEFEATURE_HUBS_SLOW_DN_P1_MSK                   (0x00020000)
  #define HUBS_CR_HUB0_DEFEATURE_HUBS_SLOW_DN_P1_MIN                   (0)
  #define HUBS_CR_HUB0_DEFEATURE_HUBS_SLOW_DN_P1_MAX                   (1) // 0x00000001
  #define HUBS_CR_HUB0_DEFEATURE_HUBS_SLOW_DN_P1_DEF                   (0x00000000)
  #define HUBS_CR_HUB0_DEFEATURE_HUBS_SLOW_DN_P1_HSH                   (0x0111701C)

  #define HUBS_CR_HUB0_DEFEATURE_HUBS_SLOW_DN_P2_OFF                   (18)
  #define HUBS_CR_HUB0_DEFEATURE_HUBS_SLOW_DN_P2_WID                   ( 1)
  #define HUBS_CR_HUB0_DEFEATURE_HUBS_SLOW_DN_P2_MSK                   (0x00040000)
  #define HUBS_CR_HUB0_DEFEATURE_HUBS_SLOW_DN_P2_MIN                   (0)
  #define HUBS_CR_HUB0_DEFEATURE_HUBS_SLOW_DN_P2_MAX                   (1) // 0x00000001
  #define HUBS_CR_HUB0_DEFEATURE_HUBS_SLOW_DN_P2_DEF                   (0x00000000)
  #define HUBS_CR_HUB0_DEFEATURE_HUBS_SLOW_DN_P2_HSH                   (0x0112701C)

  #define HUBS_CR_HUB0_DEFEATURE_HUBS_SLOW_DN_P3_OFF                   (19)
  #define HUBS_CR_HUB0_DEFEATURE_HUBS_SLOW_DN_P3_WID                   ( 1)
  #define HUBS_CR_HUB0_DEFEATURE_HUBS_SLOW_DN_P3_MSK                   (0x00080000)
  #define HUBS_CR_HUB0_DEFEATURE_HUBS_SLOW_DN_P3_MIN                   (0)
  #define HUBS_CR_HUB0_DEFEATURE_HUBS_SLOW_DN_P3_MAX                   (1) // 0x00000001
  #define HUBS_CR_HUB0_DEFEATURE_HUBS_SLOW_DN_P3_DEF                   (0x00000000)
  #define HUBS_CR_HUB0_DEFEATURE_HUBS_SLOW_DN_P3_HSH                   (0x0113701C)

  #define HUBS_CR_HUB0_DEFEATURE_HUBS_SLOWER_CMD_OFF                   (20)
  #define HUBS_CR_HUB0_DEFEATURE_HUBS_SLOWER_CMD_WID                   ( 1)
  #define HUBS_CR_HUB0_DEFEATURE_HUBS_SLOWER_CMD_MSK                   (0x00100000)
  #define HUBS_CR_HUB0_DEFEATURE_HUBS_SLOWER_CMD_MIN                   (0)
  #define HUBS_CR_HUB0_DEFEATURE_HUBS_SLOWER_CMD_MAX                   (1) // 0x00000001
  #define HUBS_CR_HUB0_DEFEATURE_HUBS_SLOWER_CMD_DEF                   (0x00000000)
  #define HUBS_CR_HUB0_DEFEATURE_HUBS_SLOWER_CMD_HSH                   (0x0114701C)

  #define HUBS_CR_HUB0_DEFEATURE_HUBS_DMI_NOPUSH_OFF                   (21)
  #define HUBS_CR_HUB0_DEFEATURE_HUBS_DMI_NOPUSH_WID                   ( 1)
  #define HUBS_CR_HUB0_DEFEATURE_HUBS_DMI_NOPUSH_MSK                   (0x00200000)
  #define HUBS_CR_HUB0_DEFEATURE_HUBS_DMI_NOPUSH_MIN                   (0)
  #define HUBS_CR_HUB0_DEFEATURE_HUBS_DMI_NOPUSH_MAX                   (1) // 0x00000001
  #define HUBS_CR_HUB0_DEFEATURE_HUBS_DMI_NOPUSH_DEF                   (0x00000000)
  #define HUBS_CR_HUB0_DEFEATURE_HUBS_DMI_NOPUSH_HSH                   (0x0115701C)

  #define HUBS_CR_HUB0_DEFEATURE_HUBS_RO_PASS_NP_OFF                   (22)
  #define HUBS_CR_HUB0_DEFEATURE_HUBS_RO_PASS_NP_WID                   ( 1)
  #define HUBS_CR_HUB0_DEFEATURE_HUBS_RO_PASS_NP_MSK                   (0x00400000)
  #define HUBS_CR_HUB0_DEFEATURE_HUBS_RO_PASS_NP_MIN                   (0)
  #define HUBS_CR_HUB0_DEFEATURE_HUBS_RO_PASS_NP_MAX                   (1) // 0x00000001
  #define HUBS_CR_HUB0_DEFEATURE_HUBS_RO_PASS_NP_DEF                   (0x00000000)
  #define HUBS_CR_HUB0_DEFEATURE_HUBS_RO_PASS_NP_HSH                   (0x0116701C)

  #define HUBS_CR_HUB0_DEFEATURE_HUBS_RST_CRD_P3_OFF                   (23)
  #define HUBS_CR_HUB0_DEFEATURE_HUBS_RST_CRD_P3_WID                   ( 1)
  #define HUBS_CR_HUB0_DEFEATURE_HUBS_RST_CRD_P3_MSK                   (0x00800000)
  #define HUBS_CR_HUB0_DEFEATURE_HUBS_RST_CRD_P3_MIN                   (0)
  #define HUBS_CR_HUB0_DEFEATURE_HUBS_RST_CRD_P3_MAX                   (1) // 0x00000001
  #define HUBS_CR_HUB0_DEFEATURE_HUBS_RST_CRD_P3_DEF                   (0x00000000)
  #define HUBS_CR_HUB0_DEFEATURE_HUBS_RST_CRD_P3_HSH                   (0x0117701C)

  #define HUBS_CR_HUB0_DEFEATURE_HUBS_METAFLOP_EN_OFF                  (24)
  #define HUBS_CR_HUB0_DEFEATURE_HUBS_METAFLOP_EN_WID                  ( 1)
  #define HUBS_CR_HUB0_DEFEATURE_HUBS_METAFLOP_EN_MSK                  (0x01000000)
  #define HUBS_CR_HUB0_DEFEATURE_HUBS_METAFLOP_EN_MIN                  (0)
  #define HUBS_CR_HUB0_DEFEATURE_HUBS_METAFLOP_EN_MAX                  (1) // 0x00000001
  #define HUBS_CR_HUB0_DEFEATURE_HUBS_METAFLOP_EN_DEF                  (0x00000001)
  #define HUBS_CR_HUB0_DEFEATURE_HUBS_METAFLOP_EN_HSH                  (0x0118701C)

  #define HUBS_CR_HUB0_DEFEATURE_HUBS_RESERVED_OFF                     (25)
  #define HUBS_CR_HUB0_DEFEATURE_HUBS_RESERVED_WID                     ( 7)
  #define HUBS_CR_HUB0_DEFEATURE_HUBS_RESERVED_MSK                     (0xFE000000)
  #define HUBS_CR_HUB0_DEFEATURE_HUBS_RESERVED_MIN                     (0)
  #define HUBS_CR_HUB0_DEFEATURE_HUBS_RESERVED_MAX                     (127) // 0x0000007F
  #define HUBS_CR_HUB0_DEFEATURE_HUBS_RESERVED_DEF                     (0x00000000)
  #define HUBS_CR_HUB0_DEFEATURE_HUBS_RESERVED_HSH                     (0x0719701C)

#define HUBS_CR_HUB1_DEFEATURE_HUBS_REG                                (0x00007020)

  #define HUBS_CR_HUB1_DEFEATURE_HUBS_BLK_GNT_P2_OFF                   ( 0)
  #define HUBS_CR_HUB1_DEFEATURE_HUBS_BLK_GNT_P2_WID                   ( 1)
  #define HUBS_CR_HUB1_DEFEATURE_HUBS_BLK_GNT_P2_MSK                   (0x00000001)
  #define HUBS_CR_HUB1_DEFEATURE_HUBS_BLK_GNT_P2_MIN                   (0)
  #define HUBS_CR_HUB1_DEFEATURE_HUBS_BLK_GNT_P2_MAX                   (1) // 0x00000001
  #define HUBS_CR_HUB1_DEFEATURE_HUBS_BLK_GNT_P2_DEF                   (0x00000000)
  #define HUBS_CR_HUB1_DEFEATURE_HUBS_BLK_GNT_P2_HSH                   (0x01007020)

  #define HUBS_CR_HUB1_DEFEATURE_HUBS_BLK_GNT_P3_OFF                   ( 1)
  #define HUBS_CR_HUB1_DEFEATURE_HUBS_BLK_GNT_P3_WID                   ( 1)
  #define HUBS_CR_HUB1_DEFEATURE_HUBS_BLK_GNT_P3_MSK                   (0x00000002)
  #define HUBS_CR_HUB1_DEFEATURE_HUBS_BLK_GNT_P3_MIN                   (0)
  #define HUBS_CR_HUB1_DEFEATURE_HUBS_BLK_GNT_P3_MAX                   (1) // 0x00000001
  #define HUBS_CR_HUB1_DEFEATURE_HUBS_BLK_GNT_P3_DEF                   (0x00000000)
  #define HUBS_CR_HUB1_DEFEATURE_HUBS_BLK_GNT_P3_HSH                   (0x01017020)

  #define HUBS_CR_HUB1_DEFEATURE_HUBS_BLK_PUT_P0_OFF                   ( 2)
  #define HUBS_CR_HUB1_DEFEATURE_HUBS_BLK_PUT_P0_WID                   ( 1)
  #define HUBS_CR_HUB1_DEFEATURE_HUBS_BLK_PUT_P0_MSK                   (0x00000004)
  #define HUBS_CR_HUB1_DEFEATURE_HUBS_BLK_PUT_P0_MIN                   (0)
  #define HUBS_CR_HUB1_DEFEATURE_HUBS_BLK_PUT_P0_MAX                   (1) // 0x00000001
  #define HUBS_CR_HUB1_DEFEATURE_HUBS_BLK_PUT_P0_DEF                   (0x00000000)
  #define HUBS_CR_HUB1_DEFEATURE_HUBS_BLK_PUT_P0_HSH                   (0x01027020)

  #define HUBS_CR_HUB1_DEFEATURE_HUBS_BLK_PUT_P1_OFF                   ( 3)
  #define HUBS_CR_HUB1_DEFEATURE_HUBS_BLK_PUT_P1_WID                   ( 1)
  #define HUBS_CR_HUB1_DEFEATURE_HUBS_BLK_PUT_P1_MSK                   (0x00000008)
  #define HUBS_CR_HUB1_DEFEATURE_HUBS_BLK_PUT_P1_MIN                   (0)
  #define HUBS_CR_HUB1_DEFEATURE_HUBS_BLK_PUT_P1_MAX                   (1) // 0x00000001
  #define HUBS_CR_HUB1_DEFEATURE_HUBS_BLK_PUT_P1_DEF                   (0x00000000)
  #define HUBS_CR_HUB1_DEFEATURE_HUBS_BLK_PUT_P1_HSH                   (0x01037020)

  #define HUBS_CR_HUB1_DEFEATURE_HUBS_BLK_PUT_P2_OFF                   ( 4)
  #define HUBS_CR_HUB1_DEFEATURE_HUBS_BLK_PUT_P2_WID                   ( 1)
  #define HUBS_CR_HUB1_DEFEATURE_HUBS_BLK_PUT_P2_MSK                   (0x00000010)
  #define HUBS_CR_HUB1_DEFEATURE_HUBS_BLK_PUT_P2_MIN                   (0)
  #define HUBS_CR_HUB1_DEFEATURE_HUBS_BLK_PUT_P2_MAX                   (1) // 0x00000001
  #define HUBS_CR_HUB1_DEFEATURE_HUBS_BLK_PUT_P2_DEF                   (0x00000000)
  #define HUBS_CR_HUB1_DEFEATURE_HUBS_BLK_PUT_P2_HSH                   (0x01047020)

  #define HUBS_CR_HUB1_DEFEATURE_HUBS_BLK_PUT_P3_OFF                   ( 5)
  #define HUBS_CR_HUB1_DEFEATURE_HUBS_BLK_PUT_P3_WID                   ( 1)
  #define HUBS_CR_HUB1_DEFEATURE_HUBS_BLK_PUT_P3_MSK                   (0x00000020)
  #define HUBS_CR_HUB1_DEFEATURE_HUBS_BLK_PUT_P3_MIN                   (0)
  #define HUBS_CR_HUB1_DEFEATURE_HUBS_BLK_PUT_P3_MAX                   (1) // 0x00000001
  #define HUBS_CR_HUB1_DEFEATURE_HUBS_BLK_PUT_P3_DEF                   (0x00000000)
  #define HUBS_CR_HUB1_DEFEATURE_HUBS_BLK_PUT_P3_HSH                   (0x01057020)

  #define HUBS_CR_HUB1_DEFEATURE_HUBS_NO_CHAIN_P2_OFF                  ( 6)
  #define HUBS_CR_HUB1_DEFEATURE_HUBS_NO_CHAIN_P2_WID                  ( 1)
  #define HUBS_CR_HUB1_DEFEATURE_HUBS_NO_CHAIN_P2_MSK                  (0x00000040)
  #define HUBS_CR_HUB1_DEFEATURE_HUBS_NO_CHAIN_P2_MIN                  (0)
  #define HUBS_CR_HUB1_DEFEATURE_HUBS_NO_CHAIN_P2_MAX                  (1) // 0x00000001
  #define HUBS_CR_HUB1_DEFEATURE_HUBS_NO_CHAIN_P2_DEF                  (0x00000000)
  #define HUBS_CR_HUB1_DEFEATURE_HUBS_NO_CHAIN_P2_HSH                  (0x01067020)

  #define HUBS_CR_HUB1_DEFEATURE_HUBS_NO_CHAIN_P3_OFF                  ( 7)
  #define HUBS_CR_HUB1_DEFEATURE_HUBS_NO_CHAIN_P3_WID                  ( 1)
  #define HUBS_CR_HUB1_DEFEATURE_HUBS_NO_CHAIN_P3_MSK                  (0x00000080)
  #define HUBS_CR_HUB1_DEFEATURE_HUBS_NO_CHAIN_P3_MIN                  (0)
  #define HUBS_CR_HUB1_DEFEATURE_HUBS_NO_CHAIN_P3_MAX                  (1) // 0x00000001
  #define HUBS_CR_HUB1_DEFEATURE_HUBS_NO_CHAIN_P3_DEF                  (0x00000000)
  #define HUBS_CR_HUB1_DEFEATURE_HUBS_NO_CHAIN_P3_HSH                  (0x01077020)

  #define HUBS_CR_HUB1_DEFEATURE_HUBS_SLOW_UP_P0_OFF                   ( 8)
  #define HUBS_CR_HUB1_DEFEATURE_HUBS_SLOW_UP_P0_WID                   ( 1)
  #define HUBS_CR_HUB1_DEFEATURE_HUBS_SLOW_UP_P0_MSK                   (0x00000100)
  #define HUBS_CR_HUB1_DEFEATURE_HUBS_SLOW_UP_P0_MIN                   (0)
  #define HUBS_CR_HUB1_DEFEATURE_HUBS_SLOW_UP_P0_MAX                   (1) // 0x00000001
  #define HUBS_CR_HUB1_DEFEATURE_HUBS_SLOW_UP_P0_DEF                   (0x00000000)
  #define HUBS_CR_HUB1_DEFEATURE_HUBS_SLOW_UP_P0_HSH                   (0x01087020)

  #define HUBS_CR_HUB1_DEFEATURE_HUBS_SLOW_UP_P2_OFF                   ( 9)
  #define HUBS_CR_HUB1_DEFEATURE_HUBS_SLOW_UP_P2_WID                   ( 1)
  #define HUBS_CR_HUB1_DEFEATURE_HUBS_SLOW_UP_P2_MSK                   (0x00000200)
  #define HUBS_CR_HUB1_DEFEATURE_HUBS_SLOW_UP_P2_MIN                   (0)
  #define HUBS_CR_HUB1_DEFEATURE_HUBS_SLOW_UP_P2_MAX                   (1) // 0x00000001
  #define HUBS_CR_HUB1_DEFEATURE_HUBS_SLOW_UP_P2_DEF                   (0x00000000)
  #define HUBS_CR_HUB1_DEFEATURE_HUBS_SLOW_UP_P2_HSH                   (0x01097020)

  #define HUBS_CR_HUB1_DEFEATURE_HUBS_SLOW_UP_P3_OFF                   (10)
  #define HUBS_CR_HUB1_DEFEATURE_HUBS_SLOW_UP_P3_WID                   ( 1)
  #define HUBS_CR_HUB1_DEFEATURE_HUBS_SLOW_UP_P3_MSK                   (0x00000400)
  #define HUBS_CR_HUB1_DEFEATURE_HUBS_SLOW_UP_P3_MIN                   (0)
  #define HUBS_CR_HUB1_DEFEATURE_HUBS_SLOW_UP_P3_MAX                   (1) // 0x00000001
  #define HUBS_CR_HUB1_DEFEATURE_HUBS_SLOW_UP_P3_DEF                   (0x00000000)
  #define HUBS_CR_HUB1_DEFEATURE_HUBS_SLOW_UP_P3_HSH                   (0x010A7020)

  #define HUBS_CR_HUB1_DEFEATURE_HUBS_SLOW_DN_P1_OFF                   (11)
  #define HUBS_CR_HUB1_DEFEATURE_HUBS_SLOW_DN_P1_WID                   ( 1)
  #define HUBS_CR_HUB1_DEFEATURE_HUBS_SLOW_DN_P1_MSK                   (0x00000800)
  #define HUBS_CR_HUB1_DEFEATURE_HUBS_SLOW_DN_P1_MIN                   (0)
  #define HUBS_CR_HUB1_DEFEATURE_HUBS_SLOW_DN_P1_MAX                   (1) // 0x00000001
  #define HUBS_CR_HUB1_DEFEATURE_HUBS_SLOW_DN_P1_DEF                   (0x00000000)
  #define HUBS_CR_HUB1_DEFEATURE_HUBS_SLOW_DN_P1_HSH                   (0x010B7020)

  #define HUBS_CR_HUB1_DEFEATURE_HUBS_SLOW_DN_P2_OFF                   (12)
  #define HUBS_CR_HUB1_DEFEATURE_HUBS_SLOW_DN_P2_WID                   ( 1)
  #define HUBS_CR_HUB1_DEFEATURE_HUBS_SLOW_DN_P2_MSK                   (0x00001000)
  #define HUBS_CR_HUB1_DEFEATURE_HUBS_SLOW_DN_P2_MIN                   (0)
  #define HUBS_CR_HUB1_DEFEATURE_HUBS_SLOW_DN_P2_MAX                   (1) // 0x00000001
  #define HUBS_CR_HUB1_DEFEATURE_HUBS_SLOW_DN_P2_DEF                   (0x00000000)
  #define HUBS_CR_HUB1_DEFEATURE_HUBS_SLOW_DN_P2_HSH                   (0x010C7020)

  #define HUBS_CR_HUB1_DEFEATURE_HUBS_SLOW_DN_P3_OFF                   (13)
  #define HUBS_CR_HUB1_DEFEATURE_HUBS_SLOW_DN_P3_WID                   ( 1)
  #define HUBS_CR_HUB1_DEFEATURE_HUBS_SLOW_DN_P3_MSK                   (0x00002000)
  #define HUBS_CR_HUB1_DEFEATURE_HUBS_SLOW_DN_P3_MIN                   (0)
  #define HUBS_CR_HUB1_DEFEATURE_HUBS_SLOW_DN_P3_MAX                   (1) // 0x00000001
  #define HUBS_CR_HUB1_DEFEATURE_HUBS_SLOW_DN_P3_DEF                   (0x00000000)
  #define HUBS_CR_HUB1_DEFEATURE_HUBS_SLOW_DN_P3_HSH                   (0x010D7020)

  #define HUBS_CR_HUB1_DEFEATURE_HUBS_SLOWER_CMD_OFF                   (14)
  #define HUBS_CR_HUB1_DEFEATURE_HUBS_SLOWER_CMD_WID                   ( 1)
  #define HUBS_CR_HUB1_DEFEATURE_HUBS_SLOWER_CMD_MSK                   (0x00004000)
  #define HUBS_CR_HUB1_DEFEATURE_HUBS_SLOWER_CMD_MIN                   (0)
  #define HUBS_CR_HUB1_DEFEATURE_HUBS_SLOWER_CMD_MAX                   (1) // 0x00000001
  #define HUBS_CR_HUB1_DEFEATURE_HUBS_SLOWER_CMD_DEF                   (0x00000000)
  #define HUBS_CR_HUB1_DEFEATURE_HUBS_SLOWER_CMD_HSH                   (0x010E7020)

  #define HUBS_CR_HUB1_DEFEATURE_HUBS_RO_PASS_NP_OFF                   (15)
  #define HUBS_CR_HUB1_DEFEATURE_HUBS_RO_PASS_NP_WID                   ( 1)
  #define HUBS_CR_HUB1_DEFEATURE_HUBS_RO_PASS_NP_MSK                   (0x00008000)
  #define HUBS_CR_HUB1_DEFEATURE_HUBS_RO_PASS_NP_MIN                   (0)
  #define HUBS_CR_HUB1_DEFEATURE_HUBS_RO_PASS_NP_MAX                   (1) // 0x00000001
  #define HUBS_CR_HUB1_DEFEATURE_HUBS_RO_PASS_NP_DEF                   (0x00000000)
  #define HUBS_CR_HUB1_DEFEATURE_HUBS_RO_PASS_NP_HSH                   (0x010F7020)

  #define HUBS_CR_HUB1_DEFEATURE_HUBS_RST_CRD_P0_OFF                   (16)
  #define HUBS_CR_HUB1_DEFEATURE_HUBS_RST_CRD_P0_WID                   ( 1)
  #define HUBS_CR_HUB1_DEFEATURE_HUBS_RST_CRD_P0_MSK                   (0x00010000)
  #define HUBS_CR_HUB1_DEFEATURE_HUBS_RST_CRD_P0_MIN                   (0)
  #define HUBS_CR_HUB1_DEFEATURE_HUBS_RST_CRD_P0_MAX                   (1) // 0x00000001
  #define HUBS_CR_HUB1_DEFEATURE_HUBS_RST_CRD_P0_DEF                   (0x00000000)
  #define HUBS_CR_HUB1_DEFEATURE_HUBS_RST_CRD_P0_HSH                   (0x01107020)

  #define HUBS_CR_HUB1_DEFEATURE_HUBS_RST_CRD_P1_OFF                   (17)
  #define HUBS_CR_HUB1_DEFEATURE_HUBS_RST_CRD_P1_WID                   ( 1)
  #define HUBS_CR_HUB1_DEFEATURE_HUBS_RST_CRD_P1_MSK                   (0x00020000)
  #define HUBS_CR_HUB1_DEFEATURE_HUBS_RST_CRD_P1_MIN                   (0)
  #define HUBS_CR_HUB1_DEFEATURE_HUBS_RST_CRD_P1_MAX                   (1) // 0x00000001
  #define HUBS_CR_HUB1_DEFEATURE_HUBS_RST_CRD_P1_DEF                   (0x00000000)
  #define HUBS_CR_HUB1_DEFEATURE_HUBS_RST_CRD_P1_HSH                   (0x01117020)

#define HUBS_CR_HUB2_DEFEATURE_HUBS_REG                                (0x00007024)

  #define HUBS_CR_HUB2_DEFEATURE_HUBS_BLK_GNT_P1_OFF                   ( 0)
  #define HUBS_CR_HUB2_DEFEATURE_HUBS_BLK_GNT_P1_WID                   ( 1)
  #define HUBS_CR_HUB2_DEFEATURE_HUBS_BLK_GNT_P1_MSK                   (0x00000001)
  #define HUBS_CR_HUB2_DEFEATURE_HUBS_BLK_GNT_P1_MIN                   (0)
  #define HUBS_CR_HUB2_DEFEATURE_HUBS_BLK_GNT_P1_MAX                   (1) // 0x00000001
  #define HUBS_CR_HUB2_DEFEATURE_HUBS_BLK_GNT_P1_DEF                   (0x00000000)
  #define HUBS_CR_HUB2_DEFEATURE_HUBS_BLK_GNT_P1_HSH                   (0x01007024)

  #define HUBS_CR_HUB2_DEFEATURE_HUBS_BLK_GNT_P2_OFF                   ( 1)
  #define HUBS_CR_HUB2_DEFEATURE_HUBS_BLK_GNT_P2_WID                   ( 1)
  #define HUBS_CR_HUB2_DEFEATURE_HUBS_BLK_GNT_P2_MSK                   (0x00000002)
  #define HUBS_CR_HUB2_DEFEATURE_HUBS_BLK_GNT_P2_MIN                   (0)
  #define HUBS_CR_HUB2_DEFEATURE_HUBS_BLK_GNT_P2_MAX                   (1) // 0x00000001
  #define HUBS_CR_HUB2_DEFEATURE_HUBS_BLK_GNT_P2_DEF                   (0x00000000)
  #define HUBS_CR_HUB2_DEFEATURE_HUBS_BLK_GNT_P2_HSH                   (0x01017024)

  #define HUBS_CR_HUB2_DEFEATURE_HUBS_BLK_GNT_P3_OFF                   ( 2)
  #define HUBS_CR_HUB2_DEFEATURE_HUBS_BLK_GNT_P3_WID                   ( 1)
  #define HUBS_CR_HUB2_DEFEATURE_HUBS_BLK_GNT_P3_MSK                   (0x00000004)
  #define HUBS_CR_HUB2_DEFEATURE_HUBS_BLK_GNT_P3_MIN                   (0)
  #define HUBS_CR_HUB2_DEFEATURE_HUBS_BLK_GNT_P3_MAX                   (1) // 0x00000001
  #define HUBS_CR_HUB2_DEFEATURE_HUBS_BLK_GNT_P3_DEF                   (0x00000000)
  #define HUBS_CR_HUB2_DEFEATURE_HUBS_BLK_GNT_P3_HSH                   (0x01027024)

  #define HUBS_CR_HUB2_DEFEATURE_HUBS_BLK_PUT_P0_OFF                   ( 3)
  #define HUBS_CR_HUB2_DEFEATURE_HUBS_BLK_PUT_P0_WID                   ( 1)
  #define HUBS_CR_HUB2_DEFEATURE_HUBS_BLK_PUT_P0_MSK                   (0x00000008)
  #define HUBS_CR_HUB2_DEFEATURE_HUBS_BLK_PUT_P0_MIN                   (0)
  #define HUBS_CR_HUB2_DEFEATURE_HUBS_BLK_PUT_P0_MAX                   (1) // 0x00000001
  #define HUBS_CR_HUB2_DEFEATURE_HUBS_BLK_PUT_P0_DEF                   (0x00000000)
  #define HUBS_CR_HUB2_DEFEATURE_HUBS_BLK_PUT_P0_HSH                   (0x01037024)

  #define HUBS_CR_HUB2_DEFEATURE_HUBS_BLK_PUT_P1_OFF                   ( 4)
  #define HUBS_CR_HUB2_DEFEATURE_HUBS_BLK_PUT_P1_WID                   ( 1)
  #define HUBS_CR_HUB2_DEFEATURE_HUBS_BLK_PUT_P1_MSK                   (0x00000010)
  #define HUBS_CR_HUB2_DEFEATURE_HUBS_BLK_PUT_P1_MIN                   (0)
  #define HUBS_CR_HUB2_DEFEATURE_HUBS_BLK_PUT_P1_MAX                   (1) // 0x00000001
  #define HUBS_CR_HUB2_DEFEATURE_HUBS_BLK_PUT_P1_DEF                   (0x00000000)
  #define HUBS_CR_HUB2_DEFEATURE_HUBS_BLK_PUT_P1_HSH                   (0x01047024)

  #define HUBS_CR_HUB2_DEFEATURE_HUBS_BLK_PUT_P2_OFF                   ( 5)
  #define HUBS_CR_HUB2_DEFEATURE_HUBS_BLK_PUT_P2_WID                   ( 1)
  #define HUBS_CR_HUB2_DEFEATURE_HUBS_BLK_PUT_P2_MSK                   (0x00000020)
  #define HUBS_CR_HUB2_DEFEATURE_HUBS_BLK_PUT_P2_MIN                   (0)
  #define HUBS_CR_HUB2_DEFEATURE_HUBS_BLK_PUT_P2_MAX                   (1) // 0x00000001
  #define HUBS_CR_HUB2_DEFEATURE_HUBS_BLK_PUT_P2_DEF                   (0x00000000)
  #define HUBS_CR_HUB2_DEFEATURE_HUBS_BLK_PUT_P2_HSH                   (0x01057024)

  #define HUBS_CR_HUB2_DEFEATURE_HUBS_BLK_PUT_P3_OFF                   ( 6)
  #define HUBS_CR_HUB2_DEFEATURE_HUBS_BLK_PUT_P3_WID                   ( 1)
  #define HUBS_CR_HUB2_DEFEATURE_HUBS_BLK_PUT_P3_MSK                   (0x00000040)
  #define HUBS_CR_HUB2_DEFEATURE_HUBS_BLK_PUT_P3_MIN                   (0)
  #define HUBS_CR_HUB2_DEFEATURE_HUBS_BLK_PUT_P3_MAX                   (1) // 0x00000001
  #define HUBS_CR_HUB2_DEFEATURE_HUBS_BLK_PUT_P3_DEF                   (0x00000000)
  #define HUBS_CR_HUB2_DEFEATURE_HUBS_BLK_PUT_P3_HSH                   (0x01067024)

  #define HUBS_CR_HUB2_DEFEATURE_HUBS_NO_CHAIN_P1_OFF                  ( 7)
  #define HUBS_CR_HUB2_DEFEATURE_HUBS_NO_CHAIN_P1_WID                  ( 1)
  #define HUBS_CR_HUB2_DEFEATURE_HUBS_NO_CHAIN_P1_MSK                  (0x00000080)
  #define HUBS_CR_HUB2_DEFEATURE_HUBS_NO_CHAIN_P1_MIN                  (0)
  #define HUBS_CR_HUB2_DEFEATURE_HUBS_NO_CHAIN_P1_MAX                  (1) // 0x00000001
  #define HUBS_CR_HUB2_DEFEATURE_HUBS_NO_CHAIN_P1_DEF                  (0x00000000)
  #define HUBS_CR_HUB2_DEFEATURE_HUBS_NO_CHAIN_P1_HSH                  (0x01077024)

  #define HUBS_CR_HUB2_DEFEATURE_HUBS_NO_CHAIN_P2_OFF                  ( 8)
  #define HUBS_CR_HUB2_DEFEATURE_HUBS_NO_CHAIN_P2_WID                  ( 1)
  #define HUBS_CR_HUB2_DEFEATURE_HUBS_NO_CHAIN_P2_MSK                  (0x00000100)
  #define HUBS_CR_HUB2_DEFEATURE_HUBS_NO_CHAIN_P2_MIN                  (0)
  #define HUBS_CR_HUB2_DEFEATURE_HUBS_NO_CHAIN_P2_MAX                  (1) // 0x00000001
  #define HUBS_CR_HUB2_DEFEATURE_HUBS_NO_CHAIN_P2_DEF                  (0x00000000)
  #define HUBS_CR_HUB2_DEFEATURE_HUBS_NO_CHAIN_P2_HSH                  (0x01087024)

  #define HUBS_CR_HUB2_DEFEATURE_HUBS_NO_CHAIN_P3_OFF                  ( 9)
  #define HUBS_CR_HUB2_DEFEATURE_HUBS_NO_CHAIN_P3_WID                  ( 1)
  #define HUBS_CR_HUB2_DEFEATURE_HUBS_NO_CHAIN_P3_MSK                  (0x00000200)
  #define HUBS_CR_HUB2_DEFEATURE_HUBS_NO_CHAIN_P3_MIN                  (0)
  #define HUBS_CR_HUB2_DEFEATURE_HUBS_NO_CHAIN_P3_MAX                  (1) // 0x00000001
  #define HUBS_CR_HUB2_DEFEATURE_HUBS_NO_CHAIN_P3_DEF                  (0x00000000)
  #define HUBS_CR_HUB2_DEFEATURE_HUBS_NO_CHAIN_P3_HSH                  (0x01097024)

  #define HUBS_CR_HUB2_DEFEATURE_HUBS_SLOW_UP_P0_OFF                   (10)
  #define HUBS_CR_HUB2_DEFEATURE_HUBS_SLOW_UP_P0_WID                   ( 1)
  #define HUBS_CR_HUB2_DEFEATURE_HUBS_SLOW_UP_P0_MSK                   (0x00000400)
  #define HUBS_CR_HUB2_DEFEATURE_HUBS_SLOW_UP_P0_MIN                   (0)
  #define HUBS_CR_HUB2_DEFEATURE_HUBS_SLOW_UP_P0_MAX                   (1) // 0x00000001
  #define HUBS_CR_HUB2_DEFEATURE_HUBS_SLOW_UP_P0_DEF                   (0x00000000)
  #define HUBS_CR_HUB2_DEFEATURE_HUBS_SLOW_UP_P0_HSH                   (0x010A7024)

  #define HUBS_CR_HUB2_DEFEATURE_HUBS_SLOW_UP_P1_OFF                   (11)
  #define HUBS_CR_HUB2_DEFEATURE_HUBS_SLOW_UP_P1_WID                   ( 1)
  #define HUBS_CR_HUB2_DEFEATURE_HUBS_SLOW_UP_P1_MSK                   (0x00000800)
  #define HUBS_CR_HUB2_DEFEATURE_HUBS_SLOW_UP_P1_MIN                   (0)
  #define HUBS_CR_HUB2_DEFEATURE_HUBS_SLOW_UP_P1_MAX                   (1) // 0x00000001
  #define HUBS_CR_HUB2_DEFEATURE_HUBS_SLOW_UP_P1_DEF                   (0x00000000)
  #define HUBS_CR_HUB2_DEFEATURE_HUBS_SLOW_UP_P1_HSH                   (0x010B7024)

  #define HUBS_CR_HUB2_DEFEATURE_HUBS_SLOW_UP_P2_OFF                   (12)
  #define HUBS_CR_HUB2_DEFEATURE_HUBS_SLOW_UP_P2_WID                   ( 1)
  #define HUBS_CR_HUB2_DEFEATURE_HUBS_SLOW_UP_P2_MSK                   (0x00001000)
  #define HUBS_CR_HUB2_DEFEATURE_HUBS_SLOW_UP_P2_MIN                   (0)
  #define HUBS_CR_HUB2_DEFEATURE_HUBS_SLOW_UP_P2_MAX                   (1) // 0x00000001
  #define HUBS_CR_HUB2_DEFEATURE_HUBS_SLOW_UP_P2_DEF                   (0x00000000)
  #define HUBS_CR_HUB2_DEFEATURE_HUBS_SLOW_UP_P2_HSH                   (0x010C7024)

  #define HUBS_CR_HUB2_DEFEATURE_HUBS_SLOW_UP_P3_OFF                   (13)
  #define HUBS_CR_HUB2_DEFEATURE_HUBS_SLOW_UP_P3_WID                   ( 1)
  #define HUBS_CR_HUB2_DEFEATURE_HUBS_SLOW_UP_P3_MSK                   (0x00002000)
  #define HUBS_CR_HUB2_DEFEATURE_HUBS_SLOW_UP_P3_MIN                   (0)
  #define HUBS_CR_HUB2_DEFEATURE_HUBS_SLOW_UP_P3_MAX                   (1) // 0x00000001
  #define HUBS_CR_HUB2_DEFEATURE_HUBS_SLOW_UP_P3_DEF                   (0x00000000)
  #define HUBS_CR_HUB2_DEFEATURE_HUBS_SLOW_UP_P3_HSH                   (0x010D7024)

  #define HUBS_CR_HUB2_DEFEATURE_HUBS_SLOW_DN_P1_OFF                   (14)
  #define HUBS_CR_HUB2_DEFEATURE_HUBS_SLOW_DN_P1_WID                   ( 1)
  #define HUBS_CR_HUB2_DEFEATURE_HUBS_SLOW_DN_P1_MSK                   (0x00004000)
  #define HUBS_CR_HUB2_DEFEATURE_HUBS_SLOW_DN_P1_MIN                   (0)
  #define HUBS_CR_HUB2_DEFEATURE_HUBS_SLOW_DN_P1_MAX                   (1) // 0x00000001
  #define HUBS_CR_HUB2_DEFEATURE_HUBS_SLOW_DN_P1_DEF                   (0x00000000)
  #define HUBS_CR_HUB2_DEFEATURE_HUBS_SLOW_DN_P1_HSH                   (0x010E7024)

  #define HUBS_CR_HUB2_DEFEATURE_HUBS_SLOW_DN_P2_OFF                   (15)
  #define HUBS_CR_HUB2_DEFEATURE_HUBS_SLOW_DN_P2_WID                   ( 1)
  #define HUBS_CR_HUB2_DEFEATURE_HUBS_SLOW_DN_P2_MSK                   (0x00008000)
  #define HUBS_CR_HUB2_DEFEATURE_HUBS_SLOW_DN_P2_MIN                   (0)
  #define HUBS_CR_HUB2_DEFEATURE_HUBS_SLOW_DN_P2_MAX                   (1) // 0x00000001
  #define HUBS_CR_HUB2_DEFEATURE_HUBS_SLOW_DN_P2_DEF                   (0x00000000)
  #define HUBS_CR_HUB2_DEFEATURE_HUBS_SLOW_DN_P2_HSH                   (0x010F7024)

  #define HUBS_CR_HUB2_DEFEATURE_HUBS_SLOW_DN_P3_OFF                   (16)
  #define HUBS_CR_HUB2_DEFEATURE_HUBS_SLOW_DN_P3_WID                   ( 1)
  #define HUBS_CR_HUB2_DEFEATURE_HUBS_SLOW_DN_P3_MSK                   (0x00010000)
  #define HUBS_CR_HUB2_DEFEATURE_HUBS_SLOW_DN_P3_MIN                   (0)
  #define HUBS_CR_HUB2_DEFEATURE_HUBS_SLOW_DN_P3_MAX                   (1) // 0x00000001
  #define HUBS_CR_HUB2_DEFEATURE_HUBS_SLOW_DN_P3_DEF                   (0x00000000)
  #define HUBS_CR_HUB2_DEFEATURE_HUBS_SLOW_DN_P3_HSH                   (0x01107024)

  #define HUBS_CR_HUB2_DEFEATURE_HUBS_SLOWER_CMD_OFF                   (17)
  #define HUBS_CR_HUB2_DEFEATURE_HUBS_SLOWER_CMD_WID                   ( 1)
  #define HUBS_CR_HUB2_DEFEATURE_HUBS_SLOWER_CMD_MSK                   (0x00020000)
  #define HUBS_CR_HUB2_DEFEATURE_HUBS_SLOWER_CMD_MIN                   (0)
  #define HUBS_CR_HUB2_DEFEATURE_HUBS_SLOWER_CMD_MAX                   (1) // 0x00000001
  #define HUBS_CR_HUB2_DEFEATURE_HUBS_SLOWER_CMD_DEF                   (0x00000000)
  #define HUBS_CR_HUB2_DEFEATURE_HUBS_SLOWER_CMD_HSH                   (0x01117024)

  #define HUBS_CR_HUB2_DEFEATURE_HUBS_RST_CRD_P0_OFF                   (18)
  #define HUBS_CR_HUB2_DEFEATURE_HUBS_RST_CRD_P0_WID                   ( 1)
  #define HUBS_CR_HUB2_DEFEATURE_HUBS_RST_CRD_P0_MSK                   (0x00040000)
  #define HUBS_CR_HUB2_DEFEATURE_HUBS_RST_CRD_P0_MIN                   (0)
  #define HUBS_CR_HUB2_DEFEATURE_HUBS_RST_CRD_P0_MAX                   (1) // 0x00000001
  #define HUBS_CR_HUB2_DEFEATURE_HUBS_RST_CRD_P0_DEF                   (0x00000000)
  #define HUBS_CR_HUB2_DEFEATURE_HUBS_RST_CRD_P0_HSH                   (0x01127024)

#define HUBS_CR_PEGCTL_HUBS_REG                                        (0x00007028)

  #define HUBS_CR_PEGCTL_HUBS_PCIPWRGAT_OFF                            ( 0)
  #define HUBS_CR_PEGCTL_HUBS_PCIPWRGAT_WID                            ( 1)
  #define HUBS_CR_PEGCTL_HUBS_PCIPWRGAT_MSK                            (0x00000001)
  #define HUBS_CR_PEGCTL_HUBS_PCIPWRGAT_MIN                            (0)
  #define HUBS_CR_PEGCTL_HUBS_PCIPWRGAT_MAX                            (1) // 0x00000001
  #define HUBS_CR_PEGCTL_HUBS_PCIPWRGAT_DEF                            (0x00000000)
  #define HUBS_CR_PEGCTL_HUBS_PCIPWRGAT_HSH                            (0x01007028)

#define HUBS_CR_HUB_EMPTY_HUBS_REG                                     (0x0000702C)

  #define HUBS_CR_HUB_EMPTY_HUBS_H0_EMPTY_OFF                          ( 0)
  #define HUBS_CR_HUB_EMPTY_HUBS_H0_EMPTY_WID                          ( 1)
  #define HUBS_CR_HUB_EMPTY_HUBS_H0_EMPTY_MSK                          (0x00000001)
  #define HUBS_CR_HUB_EMPTY_HUBS_H0_EMPTY_MIN                          (0)
  #define HUBS_CR_HUB_EMPTY_HUBS_H0_EMPTY_MAX                          (1) // 0x00000001
  #define HUBS_CR_HUB_EMPTY_HUBS_H0_EMPTY_DEF                          (0x00000001)
  #define HUBS_CR_HUB_EMPTY_HUBS_H0_EMPTY_HSH                          (0x0100702C)

  #define HUBS_CR_HUB_EMPTY_HUBS_H1_EMPTY_OFF                          ( 1)
  #define HUBS_CR_HUB_EMPTY_HUBS_H1_EMPTY_WID                          ( 1)
  #define HUBS_CR_HUB_EMPTY_HUBS_H1_EMPTY_MSK                          (0x00000002)
  #define HUBS_CR_HUB_EMPTY_HUBS_H1_EMPTY_MIN                          (0)
  #define HUBS_CR_HUB_EMPTY_HUBS_H1_EMPTY_MAX                          (1) // 0x00000001
  #define HUBS_CR_HUB_EMPTY_HUBS_H1_EMPTY_DEF                          (0x00000001)
  #define HUBS_CR_HUB_EMPTY_HUBS_H1_EMPTY_HSH                          (0x0101702C)

  #define HUBS_CR_HUB_EMPTY_HUBS_H2_EMPTY_OFF                          ( 2)
  #define HUBS_CR_HUB_EMPTY_HUBS_H2_EMPTY_WID                          ( 1)
  #define HUBS_CR_HUB_EMPTY_HUBS_H2_EMPTY_MSK                          (0x00000004)
  #define HUBS_CR_HUB_EMPTY_HUBS_H2_EMPTY_MIN                          (0)
  #define HUBS_CR_HUB_EMPTY_HUBS_H2_EMPTY_MAX                          (1) // 0x00000001
  #define HUBS_CR_HUB_EMPTY_HUBS_H2_EMPTY_DEF                          (0x00000001)
  #define HUBS_CR_HUB_EMPTY_HUBS_H2_EMPTY_HSH                          (0x0102702C)

#define HUBS_CR_HUB0_STATUS_HUBS_REG                                   (0x00007030)

  #define HUBS_CR_HUB0_STATUS_HUBS_REQ_VLD_P0_OFF                      ( 0)
  #define HUBS_CR_HUB0_STATUS_HUBS_REQ_VLD_P0_WID                      ( 1)
  #define HUBS_CR_HUB0_STATUS_HUBS_REQ_VLD_P0_MSK                      (0x00000001)
  #define HUBS_CR_HUB0_STATUS_HUBS_REQ_VLD_P0_MIN                      (0)
  #define HUBS_CR_HUB0_STATUS_HUBS_REQ_VLD_P0_MAX                      (1) // 0x00000001
  #define HUBS_CR_HUB0_STATUS_HUBS_REQ_VLD_P0_DEF                      (0x00000000)
  #define HUBS_CR_HUB0_STATUS_HUBS_REQ_VLD_P0_HSH                      (0x01007030)

  #define HUBS_CR_HUB0_STATUS_HUBS_REQ_VLD_P1_OFF                      ( 1)
  #define HUBS_CR_HUB0_STATUS_HUBS_REQ_VLD_P1_WID                      ( 1)
  #define HUBS_CR_HUB0_STATUS_HUBS_REQ_VLD_P1_MSK                      (0x00000002)
  #define HUBS_CR_HUB0_STATUS_HUBS_REQ_VLD_P1_MIN                      (0)
  #define HUBS_CR_HUB0_STATUS_HUBS_REQ_VLD_P1_MAX                      (1) // 0x00000001
  #define HUBS_CR_HUB0_STATUS_HUBS_REQ_VLD_P1_DEF                      (0x00000000)
  #define HUBS_CR_HUB0_STATUS_HUBS_REQ_VLD_P1_HSH                      (0x01017030)

  #define HUBS_CR_HUB0_STATUS_HUBS_REQ_VLD_P2_OFF                      ( 2)
  #define HUBS_CR_HUB0_STATUS_HUBS_REQ_VLD_P2_WID                      ( 1)
  #define HUBS_CR_HUB0_STATUS_HUBS_REQ_VLD_P2_MSK                      (0x00000004)
  #define HUBS_CR_HUB0_STATUS_HUBS_REQ_VLD_P2_MIN                      (0)
  #define HUBS_CR_HUB0_STATUS_HUBS_REQ_VLD_P2_MAX                      (1) // 0x00000001
  #define HUBS_CR_HUB0_STATUS_HUBS_REQ_VLD_P2_DEF                      (0x00000000)
  #define HUBS_CR_HUB0_STATUS_HUBS_REQ_VLD_P2_HSH                      (0x01027030)

  #define HUBS_CR_HUB0_STATUS_HUBS_REQ_VLD_P3_OFF                      ( 3)
  #define HUBS_CR_HUB0_STATUS_HUBS_REQ_VLD_P3_WID                      ( 1)
  #define HUBS_CR_HUB0_STATUS_HUBS_REQ_VLD_P3_MSK                      (0x00000008)
  #define HUBS_CR_HUB0_STATUS_HUBS_REQ_VLD_P3_MIN                      (0)
  #define HUBS_CR_HUB0_STATUS_HUBS_REQ_VLD_P3_MAX                      (1) // 0x00000001
  #define HUBS_CR_HUB0_STATUS_HUBS_REQ_VLD_P3_DEF                      (0x00000000)
  #define HUBS_CR_HUB0_STATUS_HUBS_REQ_VLD_P3_HSH                      (0x01037030)

  #define HUBS_CR_HUB0_STATUS_HUBS_TNX_VLD_P0_OFF                      ( 4)
  #define HUBS_CR_HUB0_STATUS_HUBS_TNX_VLD_P0_WID                      ( 1)
  #define HUBS_CR_HUB0_STATUS_HUBS_TNX_VLD_P0_MSK                      (0x00000010)
  #define HUBS_CR_HUB0_STATUS_HUBS_TNX_VLD_P0_MIN                      (0)
  #define HUBS_CR_HUB0_STATUS_HUBS_TNX_VLD_P0_MAX                      (1) // 0x00000001
  #define HUBS_CR_HUB0_STATUS_HUBS_TNX_VLD_P0_DEF                      (0x00000000)
  #define HUBS_CR_HUB0_STATUS_HUBS_TNX_VLD_P0_HSH                      (0x01047030)

  #define HUBS_CR_HUB0_STATUS_HUBS_TNX_VLD_P1_OFF                      ( 5)
  #define HUBS_CR_HUB0_STATUS_HUBS_TNX_VLD_P1_WID                      ( 1)
  #define HUBS_CR_HUB0_STATUS_HUBS_TNX_VLD_P1_MSK                      (0x00000020)
  #define HUBS_CR_HUB0_STATUS_HUBS_TNX_VLD_P1_MIN                      (0)
  #define HUBS_CR_HUB0_STATUS_HUBS_TNX_VLD_P1_MAX                      (1) // 0x00000001
  #define HUBS_CR_HUB0_STATUS_HUBS_TNX_VLD_P1_DEF                      (0x00000000)
  #define HUBS_CR_HUB0_STATUS_HUBS_TNX_VLD_P1_HSH                      (0x01057030)

  #define HUBS_CR_HUB0_STATUS_HUBS_TNX_VLD_P2_OFF                      ( 6)
  #define HUBS_CR_HUB0_STATUS_HUBS_TNX_VLD_P2_WID                      ( 1)
  #define HUBS_CR_HUB0_STATUS_HUBS_TNX_VLD_P2_MSK                      (0x00000040)
  #define HUBS_CR_HUB0_STATUS_HUBS_TNX_VLD_P2_MIN                      (0)
  #define HUBS_CR_HUB0_STATUS_HUBS_TNX_VLD_P2_MAX                      (1) // 0x00000001
  #define HUBS_CR_HUB0_STATUS_HUBS_TNX_VLD_P2_DEF                      (0x00000000)
  #define HUBS_CR_HUB0_STATUS_HUBS_TNX_VLD_P2_HSH                      (0x01067030)

  #define HUBS_CR_HUB0_STATUS_HUBS_TNX_VLD_P3_OFF                      ( 7)
  #define HUBS_CR_HUB0_STATUS_HUBS_TNX_VLD_P3_WID                      ( 1)
  #define HUBS_CR_HUB0_STATUS_HUBS_TNX_VLD_P3_MSK                      (0x00000080)
  #define HUBS_CR_HUB0_STATUS_HUBS_TNX_VLD_P3_MIN                      (0)
  #define HUBS_CR_HUB0_STATUS_HUBS_TNX_VLD_P3_MAX                      (1) // 0x00000001
  #define HUBS_CR_HUB0_STATUS_HUBS_TNX_VLD_P3_DEF                      (0x00000000)
  #define HUBS_CR_HUB0_STATUS_HUBS_TNX_VLD_P3_HSH                      (0x01077030)

#define HUBS_CR_HUB1_STATUS_HUBS_REG                                   (0x00007034)

  #define HUBS_CR_HUB1_STATUS_HUBS_REQ_VLD_P0_OFF                      ( 0)
  #define HUBS_CR_HUB1_STATUS_HUBS_REQ_VLD_P0_WID                      ( 1)
  #define HUBS_CR_HUB1_STATUS_HUBS_REQ_VLD_P0_MSK                      (0x00000001)
  #define HUBS_CR_HUB1_STATUS_HUBS_REQ_VLD_P0_MIN                      (0)
  #define HUBS_CR_HUB1_STATUS_HUBS_REQ_VLD_P0_MAX                      (1) // 0x00000001
  #define HUBS_CR_HUB1_STATUS_HUBS_REQ_VLD_P0_DEF                      (0x00000000)
  #define HUBS_CR_HUB1_STATUS_HUBS_REQ_VLD_P0_HSH                      (0x01007034)

  #define HUBS_CR_HUB1_STATUS_HUBS_REQ_VLD_P1_OFF                      ( 1)
  #define HUBS_CR_HUB1_STATUS_HUBS_REQ_VLD_P1_WID                      ( 1)
  #define HUBS_CR_HUB1_STATUS_HUBS_REQ_VLD_P1_MSK                      (0x00000002)
  #define HUBS_CR_HUB1_STATUS_HUBS_REQ_VLD_P1_MIN                      (0)
  #define HUBS_CR_HUB1_STATUS_HUBS_REQ_VLD_P1_MAX                      (1) // 0x00000001
  #define HUBS_CR_HUB1_STATUS_HUBS_REQ_VLD_P1_DEF                      (0x00000000)
  #define HUBS_CR_HUB1_STATUS_HUBS_REQ_VLD_P1_HSH                      (0x01017034)

  #define HUBS_CR_HUB1_STATUS_HUBS_REQ_VLD_P2_OFF                      ( 2)
  #define HUBS_CR_HUB1_STATUS_HUBS_REQ_VLD_P2_WID                      ( 1)
  #define HUBS_CR_HUB1_STATUS_HUBS_REQ_VLD_P2_MSK                      (0x00000004)
  #define HUBS_CR_HUB1_STATUS_HUBS_REQ_VLD_P2_MIN                      (0)
  #define HUBS_CR_HUB1_STATUS_HUBS_REQ_VLD_P2_MAX                      (1) // 0x00000001
  #define HUBS_CR_HUB1_STATUS_HUBS_REQ_VLD_P2_DEF                      (0x00000000)
  #define HUBS_CR_HUB1_STATUS_HUBS_REQ_VLD_P2_HSH                      (0x01027034)

  #define HUBS_CR_HUB1_STATUS_HUBS_REQ_VLD_P3_OFF                      ( 3)
  #define HUBS_CR_HUB1_STATUS_HUBS_REQ_VLD_P3_WID                      ( 1)
  #define HUBS_CR_HUB1_STATUS_HUBS_REQ_VLD_P3_MSK                      (0x00000008)
  #define HUBS_CR_HUB1_STATUS_HUBS_REQ_VLD_P3_MIN                      (0)
  #define HUBS_CR_HUB1_STATUS_HUBS_REQ_VLD_P3_MAX                      (1) // 0x00000001
  #define HUBS_CR_HUB1_STATUS_HUBS_REQ_VLD_P3_DEF                      (0x00000000)
  #define HUBS_CR_HUB1_STATUS_HUBS_REQ_VLD_P3_HSH                      (0x01037034)

  #define HUBS_CR_HUB1_STATUS_HUBS_TNX_VLD_P0_OFF                      ( 4)
  #define HUBS_CR_HUB1_STATUS_HUBS_TNX_VLD_P0_WID                      ( 1)
  #define HUBS_CR_HUB1_STATUS_HUBS_TNX_VLD_P0_MSK                      (0x00000010)
  #define HUBS_CR_HUB1_STATUS_HUBS_TNX_VLD_P0_MIN                      (0)
  #define HUBS_CR_HUB1_STATUS_HUBS_TNX_VLD_P0_MAX                      (1) // 0x00000001
  #define HUBS_CR_HUB1_STATUS_HUBS_TNX_VLD_P0_DEF                      (0x00000000)
  #define HUBS_CR_HUB1_STATUS_HUBS_TNX_VLD_P0_HSH                      (0x01047034)

  #define HUBS_CR_HUB1_STATUS_HUBS_TNX_VLD_P1_OFF                      ( 5)
  #define HUBS_CR_HUB1_STATUS_HUBS_TNX_VLD_P1_WID                      ( 1)
  #define HUBS_CR_HUB1_STATUS_HUBS_TNX_VLD_P1_MSK                      (0x00000020)
  #define HUBS_CR_HUB1_STATUS_HUBS_TNX_VLD_P1_MIN                      (0)
  #define HUBS_CR_HUB1_STATUS_HUBS_TNX_VLD_P1_MAX                      (1) // 0x00000001
  #define HUBS_CR_HUB1_STATUS_HUBS_TNX_VLD_P1_DEF                      (0x00000000)
  #define HUBS_CR_HUB1_STATUS_HUBS_TNX_VLD_P1_HSH                      (0x01057034)

  #define HUBS_CR_HUB1_STATUS_HUBS_TNX_VLD_P2_OFF                      ( 6)
  #define HUBS_CR_HUB1_STATUS_HUBS_TNX_VLD_P2_WID                      ( 1)
  #define HUBS_CR_HUB1_STATUS_HUBS_TNX_VLD_P2_MSK                      (0x00000040)
  #define HUBS_CR_HUB1_STATUS_HUBS_TNX_VLD_P2_MIN                      (0)
  #define HUBS_CR_HUB1_STATUS_HUBS_TNX_VLD_P2_MAX                      (1) // 0x00000001
  #define HUBS_CR_HUB1_STATUS_HUBS_TNX_VLD_P2_DEF                      (0x00000000)
  #define HUBS_CR_HUB1_STATUS_HUBS_TNX_VLD_P2_HSH                      (0x01067034)

  #define HUBS_CR_HUB1_STATUS_HUBS_TNX_VLD_P3_OFF                      ( 7)
  #define HUBS_CR_HUB1_STATUS_HUBS_TNX_VLD_P3_WID                      ( 1)
  #define HUBS_CR_HUB1_STATUS_HUBS_TNX_VLD_P3_MSK                      (0x00000080)
  #define HUBS_CR_HUB1_STATUS_HUBS_TNX_VLD_P3_MIN                      (0)
  #define HUBS_CR_HUB1_STATUS_HUBS_TNX_VLD_P3_MAX                      (1) // 0x00000001
  #define HUBS_CR_HUB1_STATUS_HUBS_TNX_VLD_P3_DEF                      (0x00000000)
  #define HUBS_CR_HUB1_STATUS_HUBS_TNX_VLD_P3_HSH                      (0x01077034)

#define HUBS_CR_HUB2_STATUS_HUBS_REG                                   (0x00007038)

  #define HUBS_CR_HUB2_STATUS_HUBS_REQ_VLD_P0_OFF                      ( 0)
  #define HUBS_CR_HUB2_STATUS_HUBS_REQ_VLD_P0_WID                      ( 1)
  #define HUBS_CR_HUB2_STATUS_HUBS_REQ_VLD_P0_MSK                      (0x00000001)
  #define HUBS_CR_HUB2_STATUS_HUBS_REQ_VLD_P0_MIN                      (0)
  #define HUBS_CR_HUB2_STATUS_HUBS_REQ_VLD_P0_MAX                      (1) // 0x00000001
  #define HUBS_CR_HUB2_STATUS_HUBS_REQ_VLD_P0_DEF                      (0x00000000)
  #define HUBS_CR_HUB2_STATUS_HUBS_REQ_VLD_P0_HSH                      (0x01007038)

  #define HUBS_CR_HUB2_STATUS_HUBS_REQ_VLD_P1_OFF                      ( 1)
  #define HUBS_CR_HUB2_STATUS_HUBS_REQ_VLD_P1_WID                      ( 1)
  #define HUBS_CR_HUB2_STATUS_HUBS_REQ_VLD_P1_MSK                      (0x00000002)
  #define HUBS_CR_HUB2_STATUS_HUBS_REQ_VLD_P1_MIN                      (0)
  #define HUBS_CR_HUB2_STATUS_HUBS_REQ_VLD_P1_MAX                      (1) // 0x00000001
  #define HUBS_CR_HUB2_STATUS_HUBS_REQ_VLD_P1_DEF                      (0x00000000)
  #define HUBS_CR_HUB2_STATUS_HUBS_REQ_VLD_P1_HSH                      (0x01017038)

  #define HUBS_CR_HUB2_STATUS_HUBS_REQ_VLD_P2_OFF                      ( 2)
  #define HUBS_CR_HUB2_STATUS_HUBS_REQ_VLD_P2_WID                      ( 1)
  #define HUBS_CR_HUB2_STATUS_HUBS_REQ_VLD_P2_MSK                      (0x00000004)
  #define HUBS_CR_HUB2_STATUS_HUBS_REQ_VLD_P2_MIN                      (0)
  #define HUBS_CR_HUB2_STATUS_HUBS_REQ_VLD_P2_MAX                      (1) // 0x00000001
  #define HUBS_CR_HUB2_STATUS_HUBS_REQ_VLD_P2_DEF                      (0x00000000)
  #define HUBS_CR_HUB2_STATUS_HUBS_REQ_VLD_P2_HSH                      (0x01027038)

  #define HUBS_CR_HUB2_STATUS_HUBS_REQ_VLD_P3_OFF                      ( 3)
  #define HUBS_CR_HUB2_STATUS_HUBS_REQ_VLD_P3_WID                      ( 1)
  #define HUBS_CR_HUB2_STATUS_HUBS_REQ_VLD_P3_MSK                      (0x00000008)
  #define HUBS_CR_HUB2_STATUS_HUBS_REQ_VLD_P3_MIN                      (0)
  #define HUBS_CR_HUB2_STATUS_HUBS_REQ_VLD_P3_MAX                      (1) // 0x00000001
  #define HUBS_CR_HUB2_STATUS_HUBS_REQ_VLD_P3_DEF                      (0x00000000)
  #define HUBS_CR_HUB2_STATUS_HUBS_REQ_VLD_P3_HSH                      (0x01037038)

  #define HUBS_CR_HUB2_STATUS_HUBS_TNX_VLD_P0_OFF                      ( 4)
  #define HUBS_CR_HUB2_STATUS_HUBS_TNX_VLD_P0_WID                      ( 1)
  #define HUBS_CR_HUB2_STATUS_HUBS_TNX_VLD_P0_MSK                      (0x00000010)
  #define HUBS_CR_HUB2_STATUS_HUBS_TNX_VLD_P0_MIN                      (0)
  #define HUBS_CR_HUB2_STATUS_HUBS_TNX_VLD_P0_MAX                      (1) // 0x00000001
  #define HUBS_CR_HUB2_STATUS_HUBS_TNX_VLD_P0_DEF                      (0x00000000)
  #define HUBS_CR_HUB2_STATUS_HUBS_TNX_VLD_P0_HSH                      (0x01047038)

  #define HUBS_CR_HUB2_STATUS_HUBS_TNX_VLD_P1_OFF                      ( 5)
  #define HUBS_CR_HUB2_STATUS_HUBS_TNX_VLD_P1_WID                      ( 1)
  #define HUBS_CR_HUB2_STATUS_HUBS_TNX_VLD_P1_MSK                      (0x00000020)
  #define HUBS_CR_HUB2_STATUS_HUBS_TNX_VLD_P1_MIN                      (0)
  #define HUBS_CR_HUB2_STATUS_HUBS_TNX_VLD_P1_MAX                      (1) // 0x00000001
  #define HUBS_CR_HUB2_STATUS_HUBS_TNX_VLD_P1_DEF                      (0x00000000)
  #define HUBS_CR_HUB2_STATUS_HUBS_TNX_VLD_P1_HSH                      (0x01057038)

  #define HUBS_CR_HUB2_STATUS_HUBS_TNX_VLD_P2_OFF                      ( 6)
  #define HUBS_CR_HUB2_STATUS_HUBS_TNX_VLD_P2_WID                      ( 1)
  #define HUBS_CR_HUB2_STATUS_HUBS_TNX_VLD_P2_MSK                      (0x00000040)
  #define HUBS_CR_HUB2_STATUS_HUBS_TNX_VLD_P2_MIN                      (0)
  #define HUBS_CR_HUB2_STATUS_HUBS_TNX_VLD_P2_MAX                      (1) // 0x00000001
  #define HUBS_CR_HUB2_STATUS_HUBS_TNX_VLD_P2_DEF                      (0x00000000)
  #define HUBS_CR_HUB2_STATUS_HUBS_TNX_VLD_P2_HSH                      (0x01067038)

  #define HUBS_CR_HUB2_STATUS_HUBS_TNX_VLD_P3_OFF                      ( 7)
  #define HUBS_CR_HUB2_STATUS_HUBS_TNX_VLD_P3_WID                      ( 1)
  #define HUBS_CR_HUB2_STATUS_HUBS_TNX_VLD_P3_MSK                      (0x00000080)
  #define HUBS_CR_HUB2_STATUS_HUBS_TNX_VLD_P3_MIN                      (0)
  #define HUBS_CR_HUB2_STATUS_HUBS_TNX_VLD_P3_MAX                      (1) // 0x00000001
  #define HUBS_CR_HUB2_STATUS_HUBS_TNX_VLD_P3_DEF                      (0x00000000)
  #define HUBS_CR_HUB2_STATUS_HUBS_TNX_VLD_P3_HSH                      (0x01077038)

#define HUBS_CR_VISA_SLIDE_SABHUB0S_F_HUBS_REG                         (0x00007108)

  #define HUBS_CR_VISA_SLIDE_SABHUB0S_F_HUBS_WINDOW_SLIDE_L0_OFF       ( 0)
  #define HUBS_CR_VISA_SLIDE_SABHUB0S_F_HUBS_WINDOW_SLIDE_L0_WID       ( 3)
  #define HUBS_CR_VISA_SLIDE_SABHUB0S_F_HUBS_WINDOW_SLIDE_L0_MSK       (0x00000007)
  #define HUBS_CR_VISA_SLIDE_SABHUB0S_F_HUBS_WINDOW_SLIDE_L0_MIN       (0)
  #define HUBS_CR_VISA_SLIDE_SABHUB0S_F_HUBS_WINDOW_SLIDE_L0_MAX       (7) // 0x00000007
  #define HUBS_CR_VISA_SLIDE_SABHUB0S_F_HUBS_WINDOW_SLIDE_L0_DEF       (0x00000000)
  #define HUBS_CR_VISA_SLIDE_SABHUB0S_F_HUBS_WINDOW_SLIDE_L0_HSH       (0x03007108)

  #define HUBS_CR_VISA_SLIDE_SABHUB0S_F_HUBS_ALT_L0_DATA_BYTE_SEL_OFF  ( 3)
  #define HUBS_CR_VISA_SLIDE_SABHUB0S_F_HUBS_ALT_L0_DATA_BYTE_SEL_WID  ( 7)
  #define HUBS_CR_VISA_SLIDE_SABHUB0S_F_HUBS_ALT_L0_DATA_BYTE_SEL_MSK  (0x000003F8)
  #define HUBS_CR_VISA_SLIDE_SABHUB0S_F_HUBS_ALT_L0_DATA_BYTE_SEL_MIN  (0)
  #define HUBS_CR_VISA_SLIDE_SABHUB0S_F_HUBS_ALT_L0_DATA_BYTE_SEL_MAX  (127) // 0x0000007F
  #define HUBS_CR_VISA_SLIDE_SABHUB0S_F_HUBS_ALT_L0_DATA_BYTE_SEL_DEF  (0x00000000)
  #define HUBS_CR_VISA_SLIDE_SABHUB0S_F_HUBS_ALT_L0_DATA_BYTE_SEL_HSH  (0x07037108)

  #define HUBS_CR_VISA_SLIDE_SABHUB0S_F_HUBS_WINDOW_SLIDE_L1_OFF       (10)
  #define HUBS_CR_VISA_SLIDE_SABHUB0S_F_HUBS_WINDOW_SLIDE_L1_WID       ( 3)
  #define HUBS_CR_VISA_SLIDE_SABHUB0S_F_HUBS_WINDOW_SLIDE_L1_MSK       (0x00001C00)
  #define HUBS_CR_VISA_SLIDE_SABHUB0S_F_HUBS_WINDOW_SLIDE_L1_MIN       (0)
  #define HUBS_CR_VISA_SLIDE_SABHUB0S_F_HUBS_WINDOW_SLIDE_L1_MAX       (7) // 0x00000007
  #define HUBS_CR_VISA_SLIDE_SABHUB0S_F_HUBS_WINDOW_SLIDE_L1_DEF       (0x00000000)
  #define HUBS_CR_VISA_SLIDE_SABHUB0S_F_HUBS_WINDOW_SLIDE_L1_HSH       (0x030A7108)

  #define HUBS_CR_VISA_SLIDE_SABHUB0S_F_HUBS_ALT_L1_DATA_BYTE_SEL_OFF  (13)
  #define HUBS_CR_VISA_SLIDE_SABHUB0S_F_HUBS_ALT_L1_DATA_BYTE_SEL_WID  ( 7)
  #define HUBS_CR_VISA_SLIDE_SABHUB0S_F_HUBS_ALT_L1_DATA_BYTE_SEL_MSK  (0x000FE000)
  #define HUBS_CR_VISA_SLIDE_SABHUB0S_F_HUBS_ALT_L1_DATA_BYTE_SEL_MIN  (0)
  #define HUBS_CR_VISA_SLIDE_SABHUB0S_F_HUBS_ALT_L1_DATA_BYTE_SEL_MAX  (127) // 0x0000007F
  #define HUBS_CR_VISA_SLIDE_SABHUB0S_F_HUBS_ALT_L1_DATA_BYTE_SEL_DEF  (0x00000000)
  #define HUBS_CR_VISA_SLIDE_SABHUB0S_F_HUBS_ALT_L1_DATA_BYTE_SEL_HSH  (0x070D7108)

#define HUBS_CR_VISA_SLIDE_SABHUB1S_F_HUBS_REG                         (0x00007118)

  #define HUBS_CR_VISA_SLIDE_SABHUB1S_F_HUBS_WINDOW_SLIDE_L0_OFF       ( 0)
  #define HUBS_CR_VISA_SLIDE_SABHUB1S_F_HUBS_WINDOW_SLIDE_L0_WID       ( 3)
  #define HUBS_CR_VISA_SLIDE_SABHUB1S_F_HUBS_WINDOW_SLIDE_L0_MSK       (0x00000007)
  #define HUBS_CR_VISA_SLIDE_SABHUB1S_F_HUBS_WINDOW_SLIDE_L0_MIN       (0)
  #define HUBS_CR_VISA_SLIDE_SABHUB1S_F_HUBS_WINDOW_SLIDE_L0_MAX       (7) // 0x00000007
  #define HUBS_CR_VISA_SLIDE_SABHUB1S_F_HUBS_WINDOW_SLIDE_L0_DEF       (0x00000000)
  #define HUBS_CR_VISA_SLIDE_SABHUB1S_F_HUBS_WINDOW_SLIDE_L0_HSH       (0x03007118)

  #define HUBS_CR_VISA_SLIDE_SABHUB1S_F_HUBS_ALT_L0_DATA_BYTE_SEL_OFF  ( 3)
  #define HUBS_CR_VISA_SLIDE_SABHUB1S_F_HUBS_ALT_L0_DATA_BYTE_SEL_WID  ( 7)
  #define HUBS_CR_VISA_SLIDE_SABHUB1S_F_HUBS_ALT_L0_DATA_BYTE_SEL_MSK  (0x000003F8)
  #define HUBS_CR_VISA_SLIDE_SABHUB1S_F_HUBS_ALT_L0_DATA_BYTE_SEL_MIN  (0)
  #define HUBS_CR_VISA_SLIDE_SABHUB1S_F_HUBS_ALT_L0_DATA_BYTE_SEL_MAX  (127) // 0x0000007F
  #define HUBS_CR_VISA_SLIDE_SABHUB1S_F_HUBS_ALT_L0_DATA_BYTE_SEL_DEF  (0x00000000)
  #define HUBS_CR_VISA_SLIDE_SABHUB1S_F_HUBS_ALT_L0_DATA_BYTE_SEL_HSH  (0x07037118)

  #define HUBS_CR_VISA_SLIDE_SABHUB1S_F_HUBS_WINDOW_SLIDE_L1_OFF       (10)
  #define HUBS_CR_VISA_SLIDE_SABHUB1S_F_HUBS_WINDOW_SLIDE_L1_WID       ( 3)
  #define HUBS_CR_VISA_SLIDE_SABHUB1S_F_HUBS_WINDOW_SLIDE_L1_MSK       (0x00001C00)
  #define HUBS_CR_VISA_SLIDE_SABHUB1S_F_HUBS_WINDOW_SLIDE_L1_MIN       (0)
  #define HUBS_CR_VISA_SLIDE_SABHUB1S_F_HUBS_WINDOW_SLIDE_L1_MAX       (7) // 0x00000007
  #define HUBS_CR_VISA_SLIDE_SABHUB1S_F_HUBS_WINDOW_SLIDE_L1_DEF       (0x00000000)
  #define HUBS_CR_VISA_SLIDE_SABHUB1S_F_HUBS_WINDOW_SLIDE_L1_HSH       (0x030A7118)

  #define HUBS_CR_VISA_SLIDE_SABHUB1S_F_HUBS_ALT_L1_DATA_BYTE_SEL_OFF  (13)
  #define HUBS_CR_VISA_SLIDE_SABHUB1S_F_HUBS_ALT_L1_DATA_BYTE_SEL_WID  ( 7)
  #define HUBS_CR_VISA_SLIDE_SABHUB1S_F_HUBS_ALT_L1_DATA_BYTE_SEL_MSK  (0x000FE000)
  #define HUBS_CR_VISA_SLIDE_SABHUB1S_F_HUBS_ALT_L1_DATA_BYTE_SEL_MIN  (0)
  #define HUBS_CR_VISA_SLIDE_SABHUB1S_F_HUBS_ALT_L1_DATA_BYTE_SEL_MAX  (127) // 0x0000007F
  #define HUBS_CR_VISA_SLIDE_SABHUB1S_F_HUBS_ALT_L1_DATA_BYTE_SEL_DEF  (0x00000000)
  #define HUBS_CR_VISA_SLIDE_SABHUB1S_F_HUBS_ALT_L1_DATA_BYTE_SEL_HSH  (0x070D7118)

#define HUBS_CR_VISA_SLIDE_SABHUB2S_F_HUBS_REG                         (0x00007120)

  #define HUBS_CR_VISA_SLIDE_SABHUB2S_F_HUBS_WINDOW_SLIDE_L0_OFF       ( 0)
  #define HUBS_CR_VISA_SLIDE_SABHUB2S_F_HUBS_WINDOW_SLIDE_L0_WID       ( 3)
  #define HUBS_CR_VISA_SLIDE_SABHUB2S_F_HUBS_WINDOW_SLIDE_L0_MSK       (0x00000007)
  #define HUBS_CR_VISA_SLIDE_SABHUB2S_F_HUBS_WINDOW_SLIDE_L0_MIN       (0)
  #define HUBS_CR_VISA_SLIDE_SABHUB2S_F_HUBS_WINDOW_SLIDE_L0_MAX       (7) // 0x00000007
  #define HUBS_CR_VISA_SLIDE_SABHUB2S_F_HUBS_WINDOW_SLIDE_L0_DEF       (0x00000000)
  #define HUBS_CR_VISA_SLIDE_SABHUB2S_F_HUBS_WINDOW_SLIDE_L0_HSH       (0x03007120)

  #define HUBS_CR_VISA_SLIDE_SABHUB2S_F_HUBS_ALT_L0_DATA_BYTE_SEL_OFF  ( 3)
  #define HUBS_CR_VISA_SLIDE_SABHUB2S_F_HUBS_ALT_L0_DATA_BYTE_SEL_WID  ( 7)
  #define HUBS_CR_VISA_SLIDE_SABHUB2S_F_HUBS_ALT_L0_DATA_BYTE_SEL_MSK  (0x000003F8)
  #define HUBS_CR_VISA_SLIDE_SABHUB2S_F_HUBS_ALT_L0_DATA_BYTE_SEL_MIN  (0)
  #define HUBS_CR_VISA_SLIDE_SABHUB2S_F_HUBS_ALT_L0_DATA_BYTE_SEL_MAX  (127) // 0x0000007F
  #define HUBS_CR_VISA_SLIDE_SABHUB2S_F_HUBS_ALT_L0_DATA_BYTE_SEL_DEF  (0x00000000)
  #define HUBS_CR_VISA_SLIDE_SABHUB2S_F_HUBS_ALT_L0_DATA_BYTE_SEL_HSH  (0x07037120)

  #define HUBS_CR_VISA_SLIDE_SABHUB2S_F_HUBS_WINDOW_SLIDE_L1_OFF       (10)
  #define HUBS_CR_VISA_SLIDE_SABHUB2S_F_HUBS_WINDOW_SLIDE_L1_WID       ( 3)
  #define HUBS_CR_VISA_SLIDE_SABHUB2S_F_HUBS_WINDOW_SLIDE_L1_MSK       (0x00001C00)
  #define HUBS_CR_VISA_SLIDE_SABHUB2S_F_HUBS_WINDOW_SLIDE_L1_MIN       (0)
  #define HUBS_CR_VISA_SLIDE_SABHUB2S_F_HUBS_WINDOW_SLIDE_L1_MAX       (7) // 0x00000007
  #define HUBS_CR_VISA_SLIDE_SABHUB2S_F_HUBS_WINDOW_SLIDE_L1_DEF       (0x00000000)
  #define HUBS_CR_VISA_SLIDE_SABHUB2S_F_HUBS_WINDOW_SLIDE_L1_HSH       (0x030A7120)

  #define HUBS_CR_VISA_SLIDE_SABHUB2S_F_HUBS_ALT_L1_DATA_BYTE_SEL_OFF  (13)
  #define HUBS_CR_VISA_SLIDE_SABHUB2S_F_HUBS_ALT_L1_DATA_BYTE_SEL_WID  ( 7)
  #define HUBS_CR_VISA_SLIDE_SABHUB2S_F_HUBS_ALT_L1_DATA_BYTE_SEL_MSK  (0x000FE000)
  #define HUBS_CR_VISA_SLIDE_SABHUB2S_F_HUBS_ALT_L1_DATA_BYTE_SEL_MIN  (0)
  #define HUBS_CR_VISA_SLIDE_SABHUB2S_F_HUBS_ALT_L1_DATA_BYTE_SEL_MAX  (127) // 0x0000007F
  #define HUBS_CR_VISA_SLIDE_SABHUB2S_F_HUBS_ALT_L1_DATA_BYTE_SEL_DEF  (0x00000000)
  #define HUBS_CR_VISA_SLIDE_SABHUB2S_F_HUBS_ALT_L1_DATA_BYTE_SEL_HSH  (0x070D7120)

#define HUBS_CR_MBOX_WR_DATA_HUBS_REG                                  (0x00007124)

  #define HUBS_CR_MBOX_WR_DATA_HUBS_DATA_OFF                           ( 0)
  #define HUBS_CR_MBOX_WR_DATA_HUBS_DATA_WID                           (32)
  #define HUBS_CR_MBOX_WR_DATA_HUBS_DATA_MSK                           (0xFFFFFFFF)
  #define HUBS_CR_MBOX_WR_DATA_HUBS_DATA_MIN                           (0)
  #define HUBS_CR_MBOX_WR_DATA_HUBS_DATA_MAX                           (4294967295) // 0xFFFFFFFF
  #define HUBS_CR_MBOX_WR_DATA_HUBS_DATA_DEF                           (0x00000000)
  #define HUBS_CR_MBOX_WR_DATA_HUBS_DATA_HSH                           (0x20007124)

#define HUBS_CR_MBOX_RD_DATA_HUBS_REG                                  (0x00007128)

  #define HUBS_CR_MBOX_RD_DATA_HUBS_DATA_OFF                           ( 0)
  #define HUBS_CR_MBOX_RD_DATA_HUBS_DATA_WID                           (32)
  #define HUBS_CR_MBOX_RD_DATA_HUBS_DATA_MSK                           (0xFFFFFFFF)
  #define HUBS_CR_MBOX_RD_DATA_HUBS_DATA_MIN                           (0)
  #define HUBS_CR_MBOX_RD_DATA_HUBS_DATA_MAX                           (4294967295) // 0xFFFFFFFF
  #define HUBS_CR_MBOX_RD_DATA_HUBS_DATA_DEF                           (0x00000000)
  #define HUBS_CR_MBOX_RD_DATA_HUBS_DATA_HSH                           (0x20007128)

#define HUBS_CR_MBOX_ADDR_LO_HUBS_REG                                  (0x0000712C)

  #define HUBS_CR_MBOX_ADDR_LO_HUBS_ADDR_OFF                           ( 0)
  #define HUBS_CR_MBOX_ADDR_LO_HUBS_ADDR_WID                           (32)
  #define HUBS_CR_MBOX_ADDR_LO_HUBS_ADDR_MSK                           (0xFFFFFFFF)
  #define HUBS_CR_MBOX_ADDR_LO_HUBS_ADDR_MIN                           (0)
  #define HUBS_CR_MBOX_ADDR_LO_HUBS_ADDR_MAX                           (4294967295) // 0xFFFFFFFF
  #define HUBS_CR_MBOX_ADDR_LO_HUBS_ADDR_DEF                           (0x00000000)
  #define HUBS_CR_MBOX_ADDR_LO_HUBS_ADDR_HSH                           (0x2000712C)

#define HUBS_CR_MBOX_ADDR_HI_HUBS_REG                                  (0x00007130)

  #define HUBS_CR_MBOX_ADDR_HI_HUBS_ADDR_OFF                           ( 0)
  #define HUBS_CR_MBOX_ADDR_HI_HUBS_ADDR_WID                           (32)
  #define HUBS_CR_MBOX_ADDR_HI_HUBS_ADDR_MSK                           (0xFFFFFFFF)
  #define HUBS_CR_MBOX_ADDR_HI_HUBS_ADDR_MIN                           (0)
  #define HUBS_CR_MBOX_ADDR_HI_HUBS_ADDR_MAX                           (4294967295) // 0xFFFFFFFF
  #define HUBS_CR_MBOX_ADDR_HI_HUBS_ADDR_DEF                           (0x00000000)
  #define HUBS_CR_MBOX_ADDR_HI_HUBS_ADDR_HSH                           (0x20007130)

#define HUBS_CR_MBOX_CMD_LO_HUBS_REG                                   (0x00007134)

  #define HUBS_CR_MBOX_CMD_LO_HUBS_FBE_OFF                             ( 0)
  #define HUBS_CR_MBOX_CMD_LO_HUBS_FBE_WID                             ( 4)
  #define HUBS_CR_MBOX_CMD_LO_HUBS_FBE_MSK                             (0x0000000F)
  #define HUBS_CR_MBOX_CMD_LO_HUBS_FBE_MIN                             (0)
  #define HUBS_CR_MBOX_CMD_LO_HUBS_FBE_MAX                             (15) // 0x0000000F
  #define HUBS_CR_MBOX_CMD_LO_HUBS_FBE_DEF                             (0x00000000)
  #define HUBS_CR_MBOX_CMD_LO_HUBS_FBE_HSH                             (0x04007134)

  #define HUBS_CR_MBOX_CMD_LO_HUBS_LBE_OFF                             ( 4)
  #define HUBS_CR_MBOX_CMD_LO_HUBS_LBE_WID                             ( 4)
  #define HUBS_CR_MBOX_CMD_LO_HUBS_LBE_MSK                             (0x000000F0)
  #define HUBS_CR_MBOX_CMD_LO_HUBS_LBE_MIN                             (0)
  #define HUBS_CR_MBOX_CMD_LO_HUBS_LBE_MAX                             (15) // 0x0000000F
  #define HUBS_CR_MBOX_CMD_LO_HUBS_LBE_DEF                             (0x00000000)
  #define HUBS_CR_MBOX_CMD_LO_HUBS_LBE_HSH                             (0x04047134)

  #define HUBS_CR_MBOX_CMD_LO_HUBS_TAG_OFF                             ( 8)
  #define HUBS_CR_MBOX_CMD_LO_HUBS_TAG_WID                             ( 8)
  #define HUBS_CR_MBOX_CMD_LO_HUBS_TAG_MSK                             (0x0000FF00)
  #define HUBS_CR_MBOX_CMD_LO_HUBS_TAG_MIN                             (0)
  #define HUBS_CR_MBOX_CMD_LO_HUBS_TAG_MAX                             (255) // 0x000000FF
  #define HUBS_CR_MBOX_CMD_LO_HUBS_TAG_DEF                             (0x00000000)
  #define HUBS_CR_MBOX_CMD_LO_HUBS_TAG_HSH                             (0x08087134)

  #define HUBS_CR_MBOX_CMD_LO_HUBS_RQID_OFF                            (16)
  #define HUBS_CR_MBOX_CMD_LO_HUBS_RQID_WID                            (16)
  #define HUBS_CR_MBOX_CMD_LO_HUBS_RQID_MSK                            (0xFFFF0000)
  #define HUBS_CR_MBOX_CMD_LO_HUBS_RQID_MIN                            (0)
  #define HUBS_CR_MBOX_CMD_LO_HUBS_RQID_MAX                            (65535) // 0x0000FFFF
  #define HUBS_CR_MBOX_CMD_LO_HUBS_RQID_DEF                            (0x00000000)
  #define HUBS_CR_MBOX_CMD_LO_HUBS_RQID_HSH                            (0x10107134)

#define HUBS_CR_MBOX_CMD_HI_HUBS_REG                                   (0x00007138)

  #define HUBS_CR_MBOX_CMD_HI_HUBS_AT_OFF                              ( 0)
  #define HUBS_CR_MBOX_CMD_HI_HUBS_AT_WID                              ( 2)
  #define HUBS_CR_MBOX_CMD_HI_HUBS_AT_MSK                              (0x00000003)
  #define HUBS_CR_MBOX_CMD_HI_HUBS_AT_MIN                              (0)
  #define HUBS_CR_MBOX_CMD_HI_HUBS_AT_MAX                              (3) // 0x00000003
  #define HUBS_CR_MBOX_CMD_HI_HUBS_AT_DEF                              (0x00000000)
  #define HUBS_CR_MBOX_CMD_HI_HUBS_AT_HSH                              (0x02007138)

  #define HUBS_CR_MBOX_CMD_HI_HUBS_POISON_OFF                          ( 2)
  #define HUBS_CR_MBOX_CMD_HI_HUBS_POISON_WID                          ( 1)
  #define HUBS_CR_MBOX_CMD_HI_HUBS_POISON_MSK                          (0x00000004)
  #define HUBS_CR_MBOX_CMD_HI_HUBS_POISON_MIN                          (0)
  #define HUBS_CR_MBOX_CMD_HI_HUBS_POISON_MAX                          (1) // 0x00000001
  #define HUBS_CR_MBOX_CMD_HI_HUBS_POISON_DEF                          (0x00000000)
  #define HUBS_CR_MBOX_CMD_HI_HUBS_POISON_HSH                          (0x01027138)

  #define HUBS_CR_MBOX_CMD_HI_HUBS_LENGTH_OFF                          ( 3)
  #define HUBS_CR_MBOX_CMD_HI_HUBS_LENGTH_WID                          ( 5)
  #define HUBS_CR_MBOX_CMD_HI_HUBS_LENGTH_MSK                          (0x000000F8)
  #define HUBS_CR_MBOX_CMD_HI_HUBS_LENGTH_MIN                          (0)
  #define HUBS_CR_MBOX_CMD_HI_HUBS_LENGTH_MAX                          (31) // 0x0000001F
  #define HUBS_CR_MBOX_CMD_HI_HUBS_LENGTH_DEF                          (0x00000000)
  #define HUBS_CR_MBOX_CMD_HI_HUBS_LENGTH_HSH                          (0x05037138)

  #define HUBS_CR_MBOX_CMD_HI_HUBS_RELAXED_OFF                         ( 8)
  #define HUBS_CR_MBOX_CMD_HI_HUBS_RELAXED_WID                         ( 1)
  #define HUBS_CR_MBOX_CMD_HI_HUBS_RELAXED_MSK                         (0x00000100)
  #define HUBS_CR_MBOX_CMD_HI_HUBS_RELAXED_MIN                         (0)
  #define HUBS_CR_MBOX_CMD_HI_HUBS_RELAXED_MAX                         (1) // 0x00000001
  #define HUBS_CR_MBOX_CMD_HI_HUBS_RELAXED_DEF                         (0x00000000)
  #define HUBS_CR_MBOX_CMD_HI_HUBS_RELAXED_HSH                         (0x01087138)

  #define HUBS_CR_MBOX_CMD_HI_HUBS_NOSNOOP_OFF                         ( 9)
  #define HUBS_CR_MBOX_CMD_HI_HUBS_NOSNOOP_WID                         ( 1)
  #define HUBS_CR_MBOX_CMD_HI_HUBS_NOSNOOP_MSK                         (0x00000200)
  #define HUBS_CR_MBOX_CMD_HI_HUBS_NOSNOOP_MIN                         (0)
  #define HUBS_CR_MBOX_CMD_HI_HUBS_NOSNOOP_MAX                         (1) // 0x00000001
  #define HUBS_CR_MBOX_CMD_HI_HUBS_NOSNOOP_DEF                         (0x00000000)
  #define HUBS_CR_MBOX_CMD_HI_HUBS_NOSNOOP_HSH                         (0x01097138)

  #define HUBS_CR_MBOX_CMD_HI_HUBS_CHAIN_OFF                           (10)
  #define HUBS_CR_MBOX_CMD_HI_HUBS_CHAIN_WID                           ( 1)
  #define HUBS_CR_MBOX_CMD_HI_HUBS_CHAIN_MSK                           (0x00000400)
  #define HUBS_CR_MBOX_CMD_HI_HUBS_CHAIN_MIN                           (0)
  #define HUBS_CR_MBOX_CMD_HI_HUBS_CHAIN_MAX                           (1) // 0x00000001
  #define HUBS_CR_MBOX_CMD_HI_HUBS_CHAIN_DEF                           (0x00000000)
  #define HUBS_CR_MBOX_CMD_HI_HUBS_CHAIN_HSH                           (0x010A7138)

  #define HUBS_CR_MBOX_CMD_HI_HUBS_CTYPE_OFF                           (11)
  #define HUBS_CR_MBOX_CMD_HI_HUBS_CTYPE_WID                           ( 5)
  #define HUBS_CR_MBOX_CMD_HI_HUBS_CTYPE_MSK                           (0x0000F800)
  #define HUBS_CR_MBOX_CMD_HI_HUBS_CTYPE_MIN                           (0)
  #define HUBS_CR_MBOX_CMD_HI_HUBS_CTYPE_MAX                           (31) // 0x0000001F
  #define HUBS_CR_MBOX_CMD_HI_HUBS_CTYPE_DEF                           (0x00000000)
  #define HUBS_CR_MBOX_CMD_HI_HUBS_CTYPE_HSH                           (0x050B7138)

  #define HUBS_CR_MBOX_CMD_HI_HUBS_FMT_OFF                             (16)
  #define HUBS_CR_MBOX_CMD_HI_HUBS_FMT_WID                             ( 2)
  #define HUBS_CR_MBOX_CMD_HI_HUBS_FMT_MSK                             (0x00030000)
  #define HUBS_CR_MBOX_CMD_HI_HUBS_FMT_MIN                             (0)
  #define HUBS_CR_MBOX_CMD_HI_HUBS_FMT_MAX                             (3) // 0x00000003
  #define HUBS_CR_MBOX_CMD_HI_HUBS_FMT_DEF                             (0x00000000)
  #define HUBS_CR_MBOX_CMD_HI_HUBS_FMT_HSH                             (0x02107138)

  #define HUBS_CR_MBOX_CMD_HI_HUBS_TC_OFF                              (18)
  #define HUBS_CR_MBOX_CMD_HI_HUBS_TC_WID                              ( 4)
  #define HUBS_CR_MBOX_CMD_HI_HUBS_TC_MSK                              (0x003C0000)
  #define HUBS_CR_MBOX_CMD_HI_HUBS_TC_MIN                              (0)
  #define HUBS_CR_MBOX_CMD_HI_HUBS_TC_MAX                              (15) // 0x0000000F
  #define HUBS_CR_MBOX_CMD_HI_HUBS_TC_DEF                              (0x00000000)
  #define HUBS_CR_MBOX_CMD_HI_HUBS_TC_HSH                              (0x04127138)

  #define HUBS_CR_MBOX_CMD_HI_HUBS_RESERVED_OFF                        (22)
  #define HUBS_CR_MBOX_CMD_HI_HUBS_RESERVED_WID                        ( 2)
  #define HUBS_CR_MBOX_CMD_HI_HUBS_RESERVED_MSK                        (0x00C00000)
  #define HUBS_CR_MBOX_CMD_HI_HUBS_RESERVED_MIN                        (0)
  #define HUBS_CR_MBOX_CMD_HI_HUBS_RESERVED_MAX                        (3) // 0x00000003
  #define HUBS_CR_MBOX_CMD_HI_HUBS_RESERVED_DEF                        (0x00000000)
  #define HUBS_CR_MBOX_CMD_HI_HUBS_RESERVED_HSH                        (0x02167138)

  #define HUBS_CR_MBOX_CMD_HI_HUBS_DMI_PRIV_OFF                        (24)
  #define HUBS_CR_MBOX_CMD_HI_HUBS_DMI_PRIV_WID                        ( 1)
  #define HUBS_CR_MBOX_CMD_HI_HUBS_DMI_PRIV_MSK                        (0x01000000)
  #define HUBS_CR_MBOX_CMD_HI_HUBS_DMI_PRIV_MIN                        (0)
  #define HUBS_CR_MBOX_CMD_HI_HUBS_DMI_PRIV_MAX                        (1) // 0x00000001
  #define HUBS_CR_MBOX_CMD_HI_HUBS_DMI_PRIV_DEF                        (0x00000000)
  #define HUBS_CR_MBOX_CMD_HI_HUBS_DMI_PRIV_HSH                        (0x01187138)

  #define HUBS_CR_MBOX_CMD_HI_HUBS_CHID_OFF                            (25)
  #define HUBS_CR_MBOX_CMD_HI_HUBS_CHID_WID                            ( 4)
  #define HUBS_CR_MBOX_CMD_HI_HUBS_CHID_MSK                            (0x1E000000)
  #define HUBS_CR_MBOX_CMD_HI_HUBS_CHID_MIN                            (0)
  #define HUBS_CR_MBOX_CMD_HI_HUBS_CHID_MAX                            (15) // 0x0000000F
  #define HUBS_CR_MBOX_CMD_HI_HUBS_CHID_DEF                            (0x00000000)
  #define HUBS_CR_MBOX_CMD_HI_HUBS_CHID_HSH                            (0x04197138)

  #define HUBS_CR_MBOX_CMD_HI_HUBS_RTYPE_OFF                           (29)
  #define HUBS_CR_MBOX_CMD_HI_HUBS_RTYPE_WID                           ( 2)
  #define HUBS_CR_MBOX_CMD_HI_HUBS_RTYPE_MSK                           (0x60000000)
  #define HUBS_CR_MBOX_CMD_HI_HUBS_RTYPE_MIN                           (0)
  #define HUBS_CR_MBOX_CMD_HI_HUBS_RTYPE_MAX                           (3) // 0x00000003
  #define HUBS_CR_MBOX_CMD_HI_HUBS_RTYPE_DEF                           (0x00000000)
  #define HUBS_CR_MBOX_CMD_HI_HUBS_RTYPE_HSH                           (0x021D7138)

  #define HUBS_CR_MBOX_CMD_HI_HUBS_START_OFF                           (31)
  #define HUBS_CR_MBOX_CMD_HI_HUBS_START_WID                           ( 1)
  #define HUBS_CR_MBOX_CMD_HI_HUBS_START_MSK                           (0x80000000)
  #define HUBS_CR_MBOX_CMD_HI_HUBS_START_MIN                           (0)
  #define HUBS_CR_MBOX_CMD_HI_HUBS_START_MAX                           (1) // 0x00000001
  #define HUBS_CR_MBOX_CMD_HI_HUBS_START_DEF                           (0x00000000)
  #define HUBS_CR_MBOX_CMD_HI_HUBS_START_HSH                           (0x011F7138)

#define HUBS_CR_MBOX_CFG_HUBS_REG                                      (0x0000713C)

  #define HUBS_CR_MBOX_CFG_HUBS_ENABLE_OFF                             ( 0)
  #define HUBS_CR_MBOX_CFG_HUBS_ENABLE_WID                             ( 1)
  #define HUBS_CR_MBOX_CFG_HUBS_ENABLE_MSK                             (0x00000001)
  #define HUBS_CR_MBOX_CFG_HUBS_ENABLE_MIN                             (0)
  #define HUBS_CR_MBOX_CFG_HUBS_ENABLE_MAX                             (1) // 0x00000001
  #define HUBS_CR_MBOX_CFG_HUBS_ENABLE_DEF                             (0x00000000)
  #define HUBS_CR_MBOX_CFG_HUBS_ENABLE_HSH                             (0x0100713C)

  #define HUBS_CR_MBOX_CFG_HUBS_LOCK_IA_OFF                            ( 1)
  #define HUBS_CR_MBOX_CFG_HUBS_LOCK_IA_WID                            ( 1)
  #define HUBS_CR_MBOX_CFG_HUBS_LOCK_IA_MSK                            (0x00000002)
  #define HUBS_CR_MBOX_CFG_HUBS_LOCK_IA_MIN                            (0)
  #define HUBS_CR_MBOX_CFG_HUBS_LOCK_IA_MAX                            (1) // 0x00000001
  #define HUBS_CR_MBOX_CFG_HUBS_LOCK_IA_DEF                            (0x00000001)
  #define HUBS_CR_MBOX_CFG_HUBS_LOCK_IA_HSH                            (0x0101713C)

  #define HUBS_CR_MBOX_CFG_HUBS_RESET_OFF                              ( 2)
  #define HUBS_CR_MBOX_CFG_HUBS_RESET_WID                              ( 1)
  #define HUBS_CR_MBOX_CFG_HUBS_RESET_MSK                              (0x00000004)
  #define HUBS_CR_MBOX_CFG_HUBS_RESET_MIN                              (0)
  #define HUBS_CR_MBOX_CFG_HUBS_RESET_MAX                              (1) // 0x00000001
  #define HUBS_CR_MBOX_CFG_HUBS_RESET_DEF                              (0x00000000)
  #define HUBS_CR_MBOX_CFG_HUBS_RESET_HSH                              (0x0102713C)

  #define HUBS_CR_MBOX_CFG_HUBS_BLK_CYCLES_OFF                         ( 3)
  #define HUBS_CR_MBOX_CFG_HUBS_BLK_CYCLES_WID                         ( 6)
  #define HUBS_CR_MBOX_CFG_HUBS_BLK_CYCLES_MSK                         (0x000001F8)
  #define HUBS_CR_MBOX_CFG_HUBS_BLK_CYCLES_MIN                         (0)
  #define HUBS_CR_MBOX_CFG_HUBS_BLK_CYCLES_MAX                         (63) // 0x0000003F
  #define HUBS_CR_MBOX_CFG_HUBS_BLK_CYCLES_DEF                         (0x00000000)
  #define HUBS_CR_MBOX_CFG_HUBS_BLK_CYCLES_HSH                         (0x0603713C)

  #define HUBS_CR_MBOX_CFG_HUBS_WR_DWORD_SEL_OFF                       ( 9)
  #define HUBS_CR_MBOX_CFG_HUBS_WR_DWORD_SEL_WID                       ( 4)
  #define HUBS_CR_MBOX_CFG_HUBS_WR_DWORD_SEL_MSK                       (0x00001E00)
  #define HUBS_CR_MBOX_CFG_HUBS_WR_DWORD_SEL_MIN                       (0)
  #define HUBS_CR_MBOX_CFG_HUBS_WR_DWORD_SEL_MAX                       (15) // 0x0000000F
  #define HUBS_CR_MBOX_CFG_HUBS_WR_DWORD_SEL_DEF                       (0x00000000)
  #define HUBS_CR_MBOX_CFG_HUBS_WR_DWORD_SEL_HSH                       (0x0409713C)

  #define HUBS_CR_MBOX_CFG_HUBS_RD_DWORD_SEL_OFF                       (13)
  #define HUBS_CR_MBOX_CFG_HUBS_RD_DWORD_SEL_WID                       ( 4)
  #define HUBS_CR_MBOX_CFG_HUBS_RD_DWORD_SEL_MSK                       (0x0001E000)
  #define HUBS_CR_MBOX_CFG_HUBS_RD_DWORD_SEL_MIN                       (0)
  #define HUBS_CR_MBOX_CFG_HUBS_RD_DWORD_SEL_MAX                       (15) // 0x0000000F
  #define HUBS_CR_MBOX_CFG_HUBS_RD_DWORD_SEL_DEF                       (0x00000000)
  #define HUBS_CR_MBOX_CFG_HUBS_RD_DWORD_SEL_HSH                       (0x040D713C)

  #define HUBS_CR_MBOX_CFG_HUBS_RPT_CMD_CNT_OFF                        (17)
  #define HUBS_CR_MBOX_CFG_HUBS_RPT_CMD_CNT_WID                        ( 6)
  #define HUBS_CR_MBOX_CFG_HUBS_RPT_CMD_CNT_MSK                        (0x007E0000)
  #define HUBS_CR_MBOX_CFG_HUBS_RPT_CMD_CNT_MIN                        (0)
  #define HUBS_CR_MBOX_CFG_HUBS_RPT_CMD_CNT_MAX                        (63) // 0x0000003F
  #define HUBS_CR_MBOX_CFG_HUBS_RPT_CMD_CNT_DEF                        (0x00000000)
  #define HUBS_CR_MBOX_CFG_HUBS_RPT_CMD_CNT_HSH                        (0x0611713C)

  #define HUBS_CR_MBOX_CFG_HUBS_RPT_NXT_ADDR_OFF                       (23)
  #define HUBS_CR_MBOX_CFG_HUBS_RPT_NXT_ADDR_WID                       ( 1)
  #define HUBS_CR_MBOX_CFG_HUBS_RPT_NXT_ADDR_MSK                       (0x00800000)
  #define HUBS_CR_MBOX_CFG_HUBS_RPT_NXT_ADDR_MIN                       (0)
  #define HUBS_CR_MBOX_CFG_HUBS_RPT_NXT_ADDR_MAX                       (1) // 0x00000001
  #define HUBS_CR_MBOX_CFG_HUBS_RPT_NXT_ADDR_DEF                       (0x00000000)
  #define HUBS_CR_MBOX_CFG_HUBS_RPT_NXT_ADDR_HSH                       (0x0117713C)

  #define HUBS_CR_MBOX_CFG_HUBS_RPT_NXT_PAGE_OFF                       (24)
  #define HUBS_CR_MBOX_CFG_HUBS_RPT_NXT_PAGE_WID                       ( 1)
  #define HUBS_CR_MBOX_CFG_HUBS_RPT_NXT_PAGE_MSK                       (0x01000000)
  #define HUBS_CR_MBOX_CFG_HUBS_RPT_NXT_PAGE_MIN                       (0)
  #define HUBS_CR_MBOX_CFG_HUBS_RPT_NXT_PAGE_MAX                       (1) // 0x00000001
  #define HUBS_CR_MBOX_CFG_HUBS_RPT_NXT_PAGE_DEF                       (0x00000000)
  #define HUBS_CR_MBOX_CFG_HUBS_RPT_NXT_PAGE_HSH                       (0x0118713C)

  #define HUBS_CR_MBOX_CFG_HUBS_DIS_CMP_INV_OFF                        (25)
  #define HUBS_CR_MBOX_CFG_HUBS_DIS_CMP_INV_WID                        ( 1)
  #define HUBS_CR_MBOX_CFG_HUBS_DIS_CMP_INV_MSK                        (0x02000000)
  #define HUBS_CR_MBOX_CFG_HUBS_DIS_CMP_INV_MIN                        (0)
  #define HUBS_CR_MBOX_CFG_HUBS_DIS_CMP_INV_MAX                        (1) // 0x00000001
  #define HUBS_CR_MBOX_CFG_HUBS_DIS_CMP_INV_DEF                        (0x00000000)
  #define HUBS_CR_MBOX_CFG_HUBS_DIS_CMP_INV_HSH                        (0x0119713C)

  #define HUBS_CR_MBOX_CFG_HUBS_FSM_STATE_OFF                          (26)
  #define HUBS_CR_MBOX_CFG_HUBS_FSM_STATE_WID                          ( 4)
  #define HUBS_CR_MBOX_CFG_HUBS_FSM_STATE_MSK                          (0x3C000000)
  #define HUBS_CR_MBOX_CFG_HUBS_FSM_STATE_MIN                          (0)
  #define HUBS_CR_MBOX_CFG_HUBS_FSM_STATE_MAX                          (15) // 0x0000000F
  #define HUBS_CR_MBOX_CFG_HUBS_FSM_STATE_DEF                          (0x00000000)
  #define HUBS_CR_MBOX_CFG_HUBS_FSM_STATE_HSH                          (0x041A713C)

  #define HUBS_CR_MBOX_CFG_HUBS_P2P_ALL_OFF                            (30)
  #define HUBS_CR_MBOX_CFG_HUBS_P2P_ALL_WID                            ( 1)
  #define HUBS_CR_MBOX_CFG_HUBS_P2P_ALL_MSK                            (0x40000000)
  #define HUBS_CR_MBOX_CFG_HUBS_P2P_ALL_MIN                            (0)
  #define HUBS_CR_MBOX_CFG_HUBS_P2P_ALL_MAX                            (1) // 0x00000001
  #define HUBS_CR_MBOX_CFG_HUBS_P2P_ALL_DEF                            (0x00000000)
  #define HUBS_CR_MBOX_CFG_HUBS_P2P_ALL_HSH                            (0x011E713C)

  #define HUBS_CR_MBOX_CFG_HUBS_SPARE_OFF                              (31)
  #define HUBS_CR_MBOX_CFG_HUBS_SPARE_WID                              ( 1)
  #define HUBS_CR_MBOX_CFG_HUBS_SPARE_MSK                              (0x80000000)
  #define HUBS_CR_MBOX_CFG_HUBS_SPARE_MIN                              (0)
  #define HUBS_CR_MBOX_CFG_HUBS_SPARE_MAX                              (1) // 0x00000001
  #define HUBS_CR_MBOX_CFG_HUBS_SPARE_DEF                              (0x00000000)
  #define HUBS_CR_MBOX_CFG_HUBS_SPARE_HSH                              (0x011F713C)

#define HUBS_CR_MBOX_STATUS_HUBS_REG                                   (0x00007140)

  #define HUBS_CR_MBOX_STATUS_HUBS_FSM_STATE_OFF                       ( 0)
  #define HUBS_CR_MBOX_STATUS_HUBS_FSM_STATE_WID                       ( 4)
  #define HUBS_CR_MBOX_STATUS_HUBS_FSM_STATE_MSK                       (0x0000000F)
  #define HUBS_CR_MBOX_STATUS_HUBS_FSM_STATE_MIN                       (0)
  #define HUBS_CR_MBOX_STATUS_HUBS_FSM_STATE_MAX                       (15) // 0x0000000F
  #define HUBS_CR_MBOX_STATUS_HUBS_FSM_STATE_DEF                       (0x00000000)
  #define HUBS_CR_MBOX_STATUS_HUBS_FSM_STATE_HSH                       (0x04007140)

  #define HUBS_CR_MBOX_STATUS_HUBS_RPT_CMD_CNT_OFF                     ( 4)
  #define HUBS_CR_MBOX_STATUS_HUBS_RPT_CMD_CNT_WID                     ( 6)
  #define HUBS_CR_MBOX_STATUS_HUBS_RPT_CMD_CNT_MSK                     (0x000003F0)
  #define HUBS_CR_MBOX_STATUS_HUBS_RPT_CMD_CNT_MIN                     (0)
  #define HUBS_CR_MBOX_STATUS_HUBS_RPT_CMD_CNT_MAX                     (63) // 0x0000003F
  #define HUBS_CR_MBOX_STATUS_HUBS_RPT_CMD_CNT_DEF                     (0x00000000)
  #define HUBS_CR_MBOX_STATUS_HUBS_RPT_CMD_CNT_HSH                     (0x06047140)

  #define HUBS_CR_MBOX_STATUS_HUBS_OPCODE_OFF                          (10)
  #define HUBS_CR_MBOX_STATUS_HUBS_OPCODE_WID                          ( 7)
  #define HUBS_CR_MBOX_STATUS_HUBS_OPCODE_MSK                          (0x0001FC00)
  #define HUBS_CR_MBOX_STATUS_HUBS_OPCODE_MIN                          (0)
  #define HUBS_CR_MBOX_STATUS_HUBS_OPCODE_MAX                          (127) // 0x0000007F
  #define HUBS_CR_MBOX_STATUS_HUBS_OPCODE_DEF                          (0x00000000)
  #define HUBS_CR_MBOX_STATUS_HUBS_OPCODE_HSH                          (0x070A7140)

  #define HUBS_CR_MBOX_STATUS_HUBS_WR_DWORD_SEL_OFF                    (17)
  #define HUBS_CR_MBOX_STATUS_HUBS_WR_DWORD_SEL_WID                    ( 4)
  #define HUBS_CR_MBOX_STATUS_HUBS_WR_DWORD_SEL_MSK                    (0x001E0000)
  #define HUBS_CR_MBOX_STATUS_HUBS_WR_DWORD_SEL_MIN                    (0)
  #define HUBS_CR_MBOX_STATUS_HUBS_WR_DWORD_SEL_MAX                    (15) // 0x0000000F
  #define HUBS_CR_MBOX_STATUS_HUBS_WR_DWORD_SEL_DEF                    (0x00000000)
  #define HUBS_CR_MBOX_STATUS_HUBS_WR_DWORD_SEL_HSH                    (0x04117140)

  #define HUBS_CR_MBOX_STATUS_HUBS_RD_DWORD_SEL_OFF                    (21)
  #define HUBS_CR_MBOX_STATUS_HUBS_RD_DWORD_SEL_WID                    ( 4)
  #define HUBS_CR_MBOX_STATUS_HUBS_RD_DWORD_SEL_MSK                    (0x01E00000)
  #define HUBS_CR_MBOX_STATUS_HUBS_RD_DWORD_SEL_MIN                    (0)
  #define HUBS_CR_MBOX_STATUS_HUBS_RD_DWORD_SEL_MAX                    (15) // 0x0000000F
  #define HUBS_CR_MBOX_STATUS_HUBS_RD_DWORD_SEL_DEF                    (0x00000000)
  #define HUBS_CR_MBOX_STATUS_HUBS_RD_DWORD_SEL_HSH                    (0x04157140)

  #define HUBS_CR_MBOX_STATUS_HUBS_P2P_RD_UP_OFF                       (25)
  #define HUBS_CR_MBOX_STATUS_HUBS_P2P_RD_UP_WID                       ( 1)
  #define HUBS_CR_MBOX_STATUS_HUBS_P2P_RD_UP_MSK                       (0x02000000)
  #define HUBS_CR_MBOX_STATUS_HUBS_P2P_RD_UP_MIN                       (0)
  #define HUBS_CR_MBOX_STATUS_HUBS_P2P_RD_UP_MAX                       (1) // 0x00000001
  #define HUBS_CR_MBOX_STATUS_HUBS_P2P_RD_UP_DEF                       (0x00000000)
  #define HUBS_CR_MBOX_STATUS_HUBS_P2P_RD_UP_HSH                       (0x01197140)

  #define HUBS_CR_MBOX_STATUS_HUBS_P2P_RD_DN_OFF                       (26)
  #define HUBS_CR_MBOX_STATUS_HUBS_P2P_RD_DN_WID                       ( 1)
  #define HUBS_CR_MBOX_STATUS_HUBS_P2P_RD_DN_MSK                       (0x04000000)
  #define HUBS_CR_MBOX_STATUS_HUBS_P2P_RD_DN_MIN                       (0)
  #define HUBS_CR_MBOX_STATUS_HUBS_P2P_RD_DN_MAX                       (1) // 0x00000001
  #define HUBS_CR_MBOX_STATUS_HUBS_P2P_RD_DN_DEF                       (0x00000000)
  #define HUBS_CR_MBOX_STATUS_HUBS_P2P_RD_DN_HSH                       (0x011A7140)

  #define HUBS_CR_MBOX_STATUS_HUBS_SPARE_OFF                           (27)
  #define HUBS_CR_MBOX_STATUS_HUBS_SPARE_WID                           ( 5)
  #define HUBS_CR_MBOX_STATUS_HUBS_SPARE_MSK                           (0xF8000000)
  #define HUBS_CR_MBOX_STATUS_HUBS_SPARE_MIN                           (0)
  #define HUBS_CR_MBOX_STATUS_HUBS_SPARE_MAX                           (31) // 0x0000001F
  #define HUBS_CR_MBOX_STATUS_HUBS_SPARE_DEF                           (0x00000000)
  #define HUBS_CR_MBOX_STATUS_HUBS_SPARE_HSH                           (0x051B7140)

#define HUBS_CR_HUB0_BLOCK_UP_HUBS_REG                                 (0x00007144)

  #define HUBS_CR_HUB0_BLOCK_UP_HUBS_XTM_CHID_OFF                      ( 0)
  #define HUBS_CR_HUB0_BLOCK_UP_HUBS_XTM_CHID_WID                      (11)
  #define HUBS_CR_HUB0_BLOCK_UP_HUBS_XTM_CHID_MSK                      (0x000007FF)
  #define HUBS_CR_HUB0_BLOCK_UP_HUBS_XTM_CHID_MIN                      (0)
  #define HUBS_CR_HUB0_BLOCK_UP_HUBS_XTM_CHID_MAX                      (2047) // 0x000007FF
  #define HUBS_CR_HUB0_BLOCK_UP_HUBS_XTM_CHID_DEF                      (0x00000000)
  #define HUBS_CR_HUB0_BLOCK_UP_HUBS_XTM_CHID_HSH                      (0x0B007144)

  #define HUBS_CR_HUB0_BLOCK_UP_HUBS_NP_OFF                            (11)
  #define HUBS_CR_HUB0_BLOCK_UP_HUBS_NP_WID                            ( 1)
  #define HUBS_CR_HUB0_BLOCK_UP_HUBS_NP_MSK                            (0x00000800)
  #define HUBS_CR_HUB0_BLOCK_UP_HUBS_NP_MIN                            (0)
  #define HUBS_CR_HUB0_BLOCK_UP_HUBS_NP_MAX                            (1) // 0x00000001
  #define HUBS_CR_HUB0_BLOCK_UP_HUBS_NP_DEF                            (0x00000000)
  #define HUBS_CR_HUB0_BLOCK_UP_HUBS_NP_HSH                            (0x010B7144)

  #define HUBS_CR_HUB0_BLOCK_UP_HUBS_PC_OFF                            (12)
  #define HUBS_CR_HUB0_BLOCK_UP_HUBS_PC_WID                            ( 1)
  #define HUBS_CR_HUB0_BLOCK_UP_HUBS_PC_MSK                            (0x00001000)
  #define HUBS_CR_HUB0_BLOCK_UP_HUBS_PC_MIN                            (0)
  #define HUBS_CR_HUB0_BLOCK_UP_HUBS_PC_MAX                            (1) // 0x00000001
  #define HUBS_CR_HUB0_BLOCK_UP_HUBS_PC_DEF                            (0x00000000)
  #define HUBS_CR_HUB0_BLOCK_UP_HUBS_PC_HSH                            (0x010C7144)

  #define HUBS_CR_HUB0_BLOCK_UP_HUBS_RESERVED_OFF                      (13)
  #define HUBS_CR_HUB0_BLOCK_UP_HUBS_RESERVED_WID                      (10)
  #define HUBS_CR_HUB0_BLOCK_UP_HUBS_RESERVED_MSK                      (0x007FE000)
  #define HUBS_CR_HUB0_BLOCK_UP_HUBS_RESERVED_MIN                      (0)
  #define HUBS_CR_HUB0_BLOCK_UP_HUBS_RESERVED_MAX                      (1023) // 0x000003FF
  #define HUBS_CR_HUB0_BLOCK_UP_HUBS_RESERVED_DEF                      (0x00000000)
  #define HUBS_CR_HUB0_BLOCK_UP_HUBS_RESERVED_HSH                      (0x0A0D7144)

#define HUBS_CR_MBOX_CFG_ENHANCE_HUBS_REG                              (0x00007148)

  #define HUBS_CR_MBOX_CFG_ENHANCE_HUBS_MUL_READ_MODE_OFF              ( 0)
  #define HUBS_CR_MBOX_CFG_ENHANCE_HUBS_MUL_READ_MODE_WID              ( 1)
  #define HUBS_CR_MBOX_CFG_ENHANCE_HUBS_MUL_READ_MODE_MSK              (0x00000001)
  #define HUBS_CR_MBOX_CFG_ENHANCE_HUBS_MUL_READ_MODE_MIN              (0)
  #define HUBS_CR_MBOX_CFG_ENHANCE_HUBS_MUL_READ_MODE_MAX              (1) // 0x00000001
  #define HUBS_CR_MBOX_CFG_ENHANCE_HUBS_MUL_READ_MODE_DEF              (0x00000000)
  #define HUBS_CR_MBOX_CFG_ENHANCE_HUBS_MUL_READ_MODE_HSH              (0x01007148)

  #define HUBS_CR_MBOX_CFG_ENHANCE_HUBS_ENABLE_ACTIVE_STORE_OFF        ( 1)
  #define HUBS_CR_MBOX_CFG_ENHANCE_HUBS_ENABLE_ACTIVE_STORE_WID        ( 1)
  #define HUBS_CR_MBOX_CFG_ENHANCE_HUBS_ENABLE_ACTIVE_STORE_MSK        (0x00000002)
  #define HUBS_CR_MBOX_CFG_ENHANCE_HUBS_ENABLE_ACTIVE_STORE_MIN        (0)
  #define HUBS_CR_MBOX_CFG_ENHANCE_HUBS_ENABLE_ACTIVE_STORE_MAX        (1) // 0x00000001
  #define HUBS_CR_MBOX_CFG_ENHANCE_HUBS_ENABLE_ACTIVE_STORE_DEF        (0x00000000)
  #define HUBS_CR_MBOX_CFG_ENHANCE_HUBS_ENABLE_ACTIVE_STORE_HSH        (0x01017148)

#define HUBS_CR_MBOX_STATUS_ENHANCE_HUBS_REG                           (0x0000714C)

  #define HUBS_CR_MBOX_STATUS_ENHANCE_HUBS_RX_FSM_OFF                  ( 0)
  #define HUBS_CR_MBOX_STATUS_ENHANCE_HUBS_RX_FSM_WID                  ( 3)
  #define HUBS_CR_MBOX_STATUS_ENHANCE_HUBS_RX_FSM_MSK                  (0x00000007)
  #define HUBS_CR_MBOX_STATUS_ENHANCE_HUBS_RX_FSM_MIN                  (0)
  #define HUBS_CR_MBOX_STATUS_ENHANCE_HUBS_RX_FSM_MAX                  (7) // 0x00000007
  #define HUBS_CR_MBOX_STATUS_ENHANCE_HUBS_RX_FSM_DEF                  (0x00000000)
  #define HUBS_CR_MBOX_STATUS_ENHANCE_HUBS_RX_FSM_HSH                  (0x0300714C)

  #define HUBS_CR_MBOX_STATUS_ENHANCE_HUBS_CMD_COMPLETE_OFF            ( 3)
  #define HUBS_CR_MBOX_STATUS_ENHANCE_HUBS_CMD_COMPLETE_WID            ( 6)
  #define HUBS_CR_MBOX_STATUS_ENHANCE_HUBS_CMD_COMPLETE_MSK            (0x000001F8)
  #define HUBS_CR_MBOX_STATUS_ENHANCE_HUBS_CMD_COMPLETE_MIN            (0)
  #define HUBS_CR_MBOX_STATUS_ENHANCE_HUBS_CMD_COMPLETE_MAX            (63) // 0x0000003F
  #define HUBS_CR_MBOX_STATUS_ENHANCE_HUBS_CMD_COMPLETE_DEF            (0x00000000)
  #define HUBS_CR_MBOX_STATUS_ENHANCE_HUBS_CMD_COMPLETE_HSH            (0x0603714C)

#define HUBS_CR_MBOX_SEQUENCE_HUBS_REG                                 (0x00007150)

  #define HUBS_CR_MBOX_SEQUENCE_HUBS_MBOX_SEQUENCE_OFF                 ( 0)
  #define HUBS_CR_MBOX_SEQUENCE_HUBS_MBOX_SEQUENCE_WID                 (32)
  #define HUBS_CR_MBOX_SEQUENCE_HUBS_MBOX_SEQUENCE_MSK                 (0xFFFFFFFF)
  #define HUBS_CR_MBOX_SEQUENCE_HUBS_MBOX_SEQUENCE_MIN                 (0)
  #define HUBS_CR_MBOX_SEQUENCE_HUBS_MBOX_SEQUENCE_MAX                 (4294967295) // 0xFFFFFFFF
  #define HUBS_CR_MBOX_SEQUENCE_HUBS_MBOX_SEQUENCE_DEF                 (0x00000000)
  #define HUBS_CR_MBOX_SEQUENCE_HUBS_MBOX_SEQUENCE_HSH                 (0x20007150)

#define HUBS_CR_MBOX_ADDR2_LO_HUBS_REG                                 (0x00007154)

  #define HUBS_CR_MBOX_ADDR2_LO_HUBS_ADDR_OFF                          ( 0)
  #define HUBS_CR_MBOX_ADDR2_LO_HUBS_ADDR_WID                          (32)
  #define HUBS_CR_MBOX_ADDR2_LO_HUBS_ADDR_MSK                          (0xFFFFFFFF)
  #define HUBS_CR_MBOX_ADDR2_LO_HUBS_ADDR_MIN                          (0)
  #define HUBS_CR_MBOX_ADDR2_LO_HUBS_ADDR_MAX                          (4294967295) // 0xFFFFFFFF
  #define HUBS_CR_MBOX_ADDR2_LO_HUBS_ADDR_DEF                          (0x00000000)
  #define HUBS_CR_MBOX_ADDR2_LO_HUBS_ADDR_HSH                          (0x20007154)

#define HUBS_CR_MBOX_ADDR2_HI_HUBS_REG                                 (0x00007158)

  #define HUBS_CR_MBOX_ADDR2_HI_HUBS_ADDR_OFF                          ( 0)
  #define HUBS_CR_MBOX_ADDR2_HI_HUBS_ADDR_WID                          (32)
  #define HUBS_CR_MBOX_ADDR2_HI_HUBS_ADDR_MSK                          (0xFFFFFFFF)
  #define HUBS_CR_MBOX_ADDR2_HI_HUBS_ADDR_MIN                          (0)
  #define HUBS_CR_MBOX_ADDR2_HI_HUBS_ADDR_MAX                          (4294967295) // 0xFFFFFFFF
  #define HUBS_CR_MBOX_ADDR2_HI_HUBS_ADDR_DEF                          (0x00000000)
  #define HUBS_CR_MBOX_ADDR2_HI_HUBS_ADDR_HSH                          (0x20007158)

#define HUBS_CR_MBOX_CMD2_LO_HUBS_REG                                  (0x0000715C)

  #define HUBS_CR_MBOX_CMD2_LO_HUBS_FBE_OFF                            ( 0)
  #define HUBS_CR_MBOX_CMD2_LO_HUBS_FBE_WID                            ( 4)
  #define HUBS_CR_MBOX_CMD2_LO_HUBS_FBE_MSK                            (0x0000000F)
  #define HUBS_CR_MBOX_CMD2_LO_HUBS_FBE_MIN                            (0)
  #define HUBS_CR_MBOX_CMD2_LO_HUBS_FBE_MAX                            (15) // 0x0000000F
  #define HUBS_CR_MBOX_CMD2_LO_HUBS_FBE_DEF                            (0x00000000)
  #define HUBS_CR_MBOX_CMD2_LO_HUBS_FBE_HSH                            (0x0400715C)

  #define HUBS_CR_MBOX_CMD2_LO_HUBS_LBE_OFF                            ( 4)
  #define HUBS_CR_MBOX_CMD2_LO_HUBS_LBE_WID                            ( 4)
  #define HUBS_CR_MBOX_CMD2_LO_HUBS_LBE_MSK                            (0x000000F0)
  #define HUBS_CR_MBOX_CMD2_LO_HUBS_LBE_MIN                            (0)
  #define HUBS_CR_MBOX_CMD2_LO_HUBS_LBE_MAX                            (15) // 0x0000000F
  #define HUBS_CR_MBOX_CMD2_LO_HUBS_LBE_DEF                            (0x00000000)
  #define HUBS_CR_MBOX_CMD2_LO_HUBS_LBE_HSH                            (0x0404715C)

  #define HUBS_CR_MBOX_CMD2_LO_HUBS_TAG_OFF                            ( 8)
  #define HUBS_CR_MBOX_CMD2_LO_HUBS_TAG_WID                            ( 8)
  #define HUBS_CR_MBOX_CMD2_LO_HUBS_TAG_MSK                            (0x0000FF00)
  #define HUBS_CR_MBOX_CMD2_LO_HUBS_TAG_MIN                            (0)
  #define HUBS_CR_MBOX_CMD2_LO_HUBS_TAG_MAX                            (255) // 0x000000FF
  #define HUBS_CR_MBOX_CMD2_LO_HUBS_TAG_DEF                            (0x00000000)
  #define HUBS_CR_MBOX_CMD2_LO_HUBS_TAG_HSH                            (0x0808715C)

  #define HUBS_CR_MBOX_CMD2_LO_HUBS_RQID_OFF                           (16)
  #define HUBS_CR_MBOX_CMD2_LO_HUBS_RQID_WID                           (16)
  #define HUBS_CR_MBOX_CMD2_LO_HUBS_RQID_MSK                           (0xFFFF0000)
  #define HUBS_CR_MBOX_CMD2_LO_HUBS_RQID_MIN                           (0)
  #define HUBS_CR_MBOX_CMD2_LO_HUBS_RQID_MAX                           (65535) // 0x0000FFFF
  #define HUBS_CR_MBOX_CMD2_LO_HUBS_RQID_DEF                           (0x00000000)
  #define HUBS_CR_MBOX_CMD2_LO_HUBS_RQID_HSH                           (0x1010715C)

#define HUBS_CR_MBOX_CMD2_HI_HUBS_REG                                  (0x00007160)

  #define HUBS_CR_MBOX_CMD2_HI_HUBS_AT_OFF                             ( 0)
  #define HUBS_CR_MBOX_CMD2_HI_HUBS_AT_WID                             ( 2)
  #define HUBS_CR_MBOX_CMD2_HI_HUBS_AT_MSK                             (0x00000003)
  #define HUBS_CR_MBOX_CMD2_HI_HUBS_AT_MIN                             (0)
  #define HUBS_CR_MBOX_CMD2_HI_HUBS_AT_MAX                             (3) // 0x00000003
  #define HUBS_CR_MBOX_CMD2_HI_HUBS_AT_DEF                             (0x00000000)
  #define HUBS_CR_MBOX_CMD2_HI_HUBS_AT_HSH                             (0x02007160)

  #define HUBS_CR_MBOX_CMD2_HI_HUBS_POISON_OFF                         ( 2)
  #define HUBS_CR_MBOX_CMD2_HI_HUBS_POISON_WID                         ( 1)
  #define HUBS_CR_MBOX_CMD2_HI_HUBS_POISON_MSK                         (0x00000004)
  #define HUBS_CR_MBOX_CMD2_HI_HUBS_POISON_MIN                         (0)
  #define HUBS_CR_MBOX_CMD2_HI_HUBS_POISON_MAX                         (1) // 0x00000001
  #define HUBS_CR_MBOX_CMD2_HI_HUBS_POISON_DEF                         (0x00000000)
  #define HUBS_CR_MBOX_CMD2_HI_HUBS_POISON_HSH                         (0x01027160)

  #define HUBS_CR_MBOX_CMD2_HI_HUBS_LENGTH_OFF                         ( 3)
  #define HUBS_CR_MBOX_CMD2_HI_HUBS_LENGTH_WID                         ( 5)
  #define HUBS_CR_MBOX_CMD2_HI_HUBS_LENGTH_MSK                         (0x000000F8)
  #define HUBS_CR_MBOX_CMD2_HI_HUBS_LENGTH_MIN                         (0)
  #define HUBS_CR_MBOX_CMD2_HI_HUBS_LENGTH_MAX                         (31) // 0x0000001F
  #define HUBS_CR_MBOX_CMD2_HI_HUBS_LENGTH_DEF                         (0x00000000)
  #define HUBS_CR_MBOX_CMD2_HI_HUBS_LENGTH_HSH                         (0x05037160)

  #define HUBS_CR_MBOX_CMD2_HI_HUBS_RELAXED_OFF                        ( 8)
  #define HUBS_CR_MBOX_CMD2_HI_HUBS_RELAXED_WID                        ( 1)
  #define HUBS_CR_MBOX_CMD2_HI_HUBS_RELAXED_MSK                        (0x00000100)
  #define HUBS_CR_MBOX_CMD2_HI_HUBS_RELAXED_MIN                        (0)
  #define HUBS_CR_MBOX_CMD2_HI_HUBS_RELAXED_MAX                        (1) // 0x00000001
  #define HUBS_CR_MBOX_CMD2_HI_HUBS_RELAXED_DEF                        (0x00000000)
  #define HUBS_CR_MBOX_CMD2_HI_HUBS_RELAXED_HSH                        (0x01087160)

  #define HUBS_CR_MBOX_CMD2_HI_HUBS_NOSNOOP_OFF                        ( 9)
  #define HUBS_CR_MBOX_CMD2_HI_HUBS_NOSNOOP_WID                        ( 1)
  #define HUBS_CR_MBOX_CMD2_HI_HUBS_NOSNOOP_MSK                        (0x00000200)
  #define HUBS_CR_MBOX_CMD2_HI_HUBS_NOSNOOP_MIN                        (0)
  #define HUBS_CR_MBOX_CMD2_HI_HUBS_NOSNOOP_MAX                        (1) // 0x00000001
  #define HUBS_CR_MBOX_CMD2_HI_HUBS_NOSNOOP_DEF                        (0x00000000)
  #define HUBS_CR_MBOX_CMD2_HI_HUBS_NOSNOOP_HSH                        (0x01097160)

  #define HUBS_CR_MBOX_CMD2_HI_HUBS_CHAIN_OFF                          (10)
  #define HUBS_CR_MBOX_CMD2_HI_HUBS_CHAIN_WID                          ( 1)
  #define HUBS_CR_MBOX_CMD2_HI_HUBS_CHAIN_MSK                          (0x00000400)
  #define HUBS_CR_MBOX_CMD2_HI_HUBS_CHAIN_MIN                          (0)
  #define HUBS_CR_MBOX_CMD2_HI_HUBS_CHAIN_MAX                          (1) // 0x00000001
  #define HUBS_CR_MBOX_CMD2_HI_HUBS_CHAIN_DEF                          (0x00000000)
  #define HUBS_CR_MBOX_CMD2_HI_HUBS_CHAIN_HSH                          (0x010A7160)

  #define HUBS_CR_MBOX_CMD2_HI_HUBS_CTYPE_OFF                          (11)
  #define HUBS_CR_MBOX_CMD2_HI_HUBS_CTYPE_WID                          ( 5)
  #define HUBS_CR_MBOX_CMD2_HI_HUBS_CTYPE_MSK                          (0x0000F800)
  #define HUBS_CR_MBOX_CMD2_HI_HUBS_CTYPE_MIN                          (0)
  #define HUBS_CR_MBOX_CMD2_HI_HUBS_CTYPE_MAX                          (31) // 0x0000001F
  #define HUBS_CR_MBOX_CMD2_HI_HUBS_CTYPE_DEF                          (0x00000000)
  #define HUBS_CR_MBOX_CMD2_HI_HUBS_CTYPE_HSH                          (0x050B7160)

  #define HUBS_CR_MBOX_CMD2_HI_HUBS_FMT_OFF                            (16)
  #define HUBS_CR_MBOX_CMD2_HI_HUBS_FMT_WID                            ( 2)
  #define HUBS_CR_MBOX_CMD2_HI_HUBS_FMT_MSK                            (0x00030000)
  #define HUBS_CR_MBOX_CMD2_HI_HUBS_FMT_MIN                            (0)
  #define HUBS_CR_MBOX_CMD2_HI_HUBS_FMT_MAX                            (3) // 0x00000003
  #define HUBS_CR_MBOX_CMD2_HI_HUBS_FMT_DEF                            (0x00000000)
  #define HUBS_CR_MBOX_CMD2_HI_HUBS_FMT_HSH                            (0x02107160)

  #define HUBS_CR_MBOX_CMD2_HI_HUBS_TC_OFF                             (18)
  #define HUBS_CR_MBOX_CMD2_HI_HUBS_TC_WID                             ( 4)
  #define HUBS_CR_MBOX_CMD2_HI_HUBS_TC_MSK                             (0x003C0000)
  #define HUBS_CR_MBOX_CMD2_HI_HUBS_TC_MIN                             (0)
  #define HUBS_CR_MBOX_CMD2_HI_HUBS_TC_MAX                             (15) // 0x0000000F
  #define HUBS_CR_MBOX_CMD2_HI_HUBS_TC_DEF                             (0x00000000)
  #define HUBS_CR_MBOX_CMD2_HI_HUBS_TC_HSH                             (0x04127160)

  #define HUBS_CR_MBOX_CMD2_HI_HUBS_RESERVED_OFF                       (22)
  #define HUBS_CR_MBOX_CMD2_HI_HUBS_RESERVED_WID                       ( 2)
  #define HUBS_CR_MBOX_CMD2_HI_HUBS_RESERVED_MSK                       (0x00C00000)
  #define HUBS_CR_MBOX_CMD2_HI_HUBS_RESERVED_MIN                       (0)
  #define HUBS_CR_MBOX_CMD2_HI_HUBS_RESERVED_MAX                       (3) // 0x00000003
  #define HUBS_CR_MBOX_CMD2_HI_HUBS_RESERVED_DEF                       (0x00000000)
  #define HUBS_CR_MBOX_CMD2_HI_HUBS_RESERVED_HSH                       (0x02167160)

  #define HUBS_CR_MBOX_CMD2_HI_HUBS_DMI_PRIV_OFF                       (24)
  #define HUBS_CR_MBOX_CMD2_HI_HUBS_DMI_PRIV_WID                       ( 1)
  #define HUBS_CR_MBOX_CMD2_HI_HUBS_DMI_PRIV_MSK                       (0x01000000)
  #define HUBS_CR_MBOX_CMD2_HI_HUBS_DMI_PRIV_MIN                       (0)
  #define HUBS_CR_MBOX_CMD2_HI_HUBS_DMI_PRIV_MAX                       (1) // 0x00000001
  #define HUBS_CR_MBOX_CMD2_HI_HUBS_DMI_PRIV_DEF                       (0x00000000)
  #define HUBS_CR_MBOX_CMD2_HI_HUBS_DMI_PRIV_HSH                       (0x01187160)

  #define HUBS_CR_MBOX_CMD2_HI_HUBS_CHID_OFF                           (25)
  #define HUBS_CR_MBOX_CMD2_HI_HUBS_CHID_WID                           ( 4)
  #define HUBS_CR_MBOX_CMD2_HI_HUBS_CHID_MSK                           (0x1E000000)
  #define HUBS_CR_MBOX_CMD2_HI_HUBS_CHID_MIN                           (0)
  #define HUBS_CR_MBOX_CMD2_HI_HUBS_CHID_MAX                           (15) // 0x0000000F
  #define HUBS_CR_MBOX_CMD2_HI_HUBS_CHID_DEF                           (0x00000000)
  #define HUBS_CR_MBOX_CMD2_HI_HUBS_CHID_HSH                           (0x04197160)

  #define HUBS_CR_MBOX_CMD2_HI_HUBS_RTYPE_OFF                          (29)
  #define HUBS_CR_MBOX_CMD2_HI_HUBS_RTYPE_WID                          ( 2)
  #define HUBS_CR_MBOX_CMD2_HI_HUBS_RTYPE_MSK                          (0x60000000)
  #define HUBS_CR_MBOX_CMD2_HI_HUBS_RTYPE_MIN                          (0)
  #define HUBS_CR_MBOX_CMD2_HI_HUBS_RTYPE_MAX                          (3) // 0x00000003
  #define HUBS_CR_MBOX_CMD2_HI_HUBS_RTYPE_DEF                          (0x00000000)
  #define HUBS_CR_MBOX_CMD2_HI_HUBS_RTYPE_HSH                          (0x021D7160)

  #define HUBS_CR_MBOX_CMD2_HI_HUBS_START_OFF                          (31)
  #define HUBS_CR_MBOX_CMD2_HI_HUBS_START_WID                          ( 1)
  #define HUBS_CR_MBOX_CMD2_HI_HUBS_START_MSK                          (0x80000000)
  #define HUBS_CR_MBOX_CMD2_HI_HUBS_START_MIN                          (0)
  #define HUBS_CR_MBOX_CMD2_HI_HUBS_START_MAX                          (1) // 0x00000001
  #define HUBS_CR_MBOX_CMD2_HI_HUBS_START_DEF                          (0x00000000)
  #define HUBS_CR_MBOX_CMD2_HI_HUBS_START_HSH                          (0x011F7160)

#define HUBS_CR_VISA_CTL_SABHUB0S_F_HUBS_REG                           (0x00007164)

  #define HUBS_CR_VISA_CTL_SABHUB0S_F_HUBS_EN_CLK_OFF                  ( 0)
  #define HUBS_CR_VISA_CTL_SABHUB0S_F_HUBS_EN_CLK_WID                  ( 1)
  #define HUBS_CR_VISA_CTL_SABHUB0S_F_HUBS_EN_CLK_MSK                  (0x00000001)
  #define HUBS_CR_VISA_CTL_SABHUB0S_F_HUBS_EN_CLK_MIN                  (0)
  #define HUBS_CR_VISA_CTL_SABHUB0S_F_HUBS_EN_CLK_MAX                  (1) // 0x00000001
  #define HUBS_CR_VISA_CTL_SABHUB0S_F_HUBS_EN_CLK_DEF                  (0x00000000)
  #define HUBS_CR_VISA_CTL_SABHUB0S_F_HUBS_EN_CLK_HSH                  (0x01007164)

  #define HUBS_CR_VISA_CTL_SABHUB0S_F_HUBS_L0_DATA_BYTE_SEL_OFF        ( 1)
  #define HUBS_CR_VISA_CTL_SABHUB0S_F_HUBS_L0_DATA_BYTE_SEL_WID        ( 7)
  #define HUBS_CR_VISA_CTL_SABHUB0S_F_HUBS_L0_DATA_BYTE_SEL_MSK        (0x000000FE)
  #define HUBS_CR_VISA_CTL_SABHUB0S_F_HUBS_L0_DATA_BYTE_SEL_MIN        (0)
  #define HUBS_CR_VISA_CTL_SABHUB0S_F_HUBS_L0_DATA_BYTE_SEL_MAX        (127) // 0x0000007F
  #define HUBS_CR_VISA_CTL_SABHUB0S_F_HUBS_L0_DATA_BYTE_SEL_DEF        (0x00000000)
  #define HUBS_CR_VISA_CTL_SABHUB0S_F_HUBS_L0_DATA_BYTE_SEL_HSH        (0x07017164)

  #define HUBS_CR_VISA_CTL_SABHUB0S_F_HUBS_L0_BYP_SEL_OFF              ( 8)
  #define HUBS_CR_VISA_CTL_SABHUB0S_F_HUBS_L0_BYP_SEL_WID              ( 1)
  #define HUBS_CR_VISA_CTL_SABHUB0S_F_HUBS_L0_BYP_SEL_MSK              (0x00000100)
  #define HUBS_CR_VISA_CTL_SABHUB0S_F_HUBS_L0_BYP_SEL_MIN              (0)
  #define HUBS_CR_VISA_CTL_SABHUB0S_F_HUBS_L0_BYP_SEL_MAX              (1) // 0x00000001
  #define HUBS_CR_VISA_CTL_SABHUB0S_F_HUBS_L0_BYP_SEL_DEF              (0x00000000)
  #define HUBS_CR_VISA_CTL_SABHUB0S_F_HUBS_L0_BYP_SEL_HSH              (0x01087164)

  #define HUBS_CR_VISA_CTL_SABHUB0S_F_HUBS_L1_DATA_BYTE_SEL_OFF        ( 9)
  #define HUBS_CR_VISA_CTL_SABHUB0S_F_HUBS_L1_DATA_BYTE_SEL_WID        ( 7)
  #define HUBS_CR_VISA_CTL_SABHUB0S_F_HUBS_L1_DATA_BYTE_SEL_MSK        (0x0000FE00)
  #define HUBS_CR_VISA_CTL_SABHUB0S_F_HUBS_L1_DATA_BYTE_SEL_MIN        (0)
  #define HUBS_CR_VISA_CTL_SABHUB0S_F_HUBS_L1_DATA_BYTE_SEL_MAX        (127) // 0x0000007F
  #define HUBS_CR_VISA_CTL_SABHUB0S_F_HUBS_L1_DATA_BYTE_SEL_DEF        (0x00000000)
  #define HUBS_CR_VISA_CTL_SABHUB0S_F_HUBS_L1_DATA_BYTE_SEL_HSH        (0x07097164)

  #define HUBS_CR_VISA_CTL_SABHUB0S_F_HUBS_L1_BYP_SEL_OFF              (16)
  #define HUBS_CR_VISA_CTL_SABHUB0S_F_HUBS_L1_BYP_SEL_WID              ( 1)
  #define HUBS_CR_VISA_CTL_SABHUB0S_F_HUBS_L1_BYP_SEL_MSK              (0x00010000)
  #define HUBS_CR_VISA_CTL_SABHUB0S_F_HUBS_L1_BYP_SEL_MIN              (0)
  #define HUBS_CR_VISA_CTL_SABHUB0S_F_HUBS_L1_BYP_SEL_MAX              (1) // 0x00000001
  #define HUBS_CR_VISA_CTL_SABHUB0S_F_HUBS_L1_BYP_SEL_DEF              (0x00000000)
  #define HUBS_CR_VISA_CTL_SABHUB0S_F_HUBS_L1_BYP_SEL_HSH              (0x01107164)

  #define HUBS_CR_VISA_CTL_SABHUB0S_F_HUBS_VORANGE_OFF                 (31)
  #define HUBS_CR_VISA_CTL_SABHUB0S_F_HUBS_VORANGE_WID                 ( 1)
  #define HUBS_CR_VISA_CTL_SABHUB0S_F_HUBS_VORANGE_MSK                 (0x80000000)
  #define HUBS_CR_VISA_CTL_SABHUB0S_F_HUBS_VORANGE_MIN                 (0)
  #define HUBS_CR_VISA_CTL_SABHUB0S_F_HUBS_VORANGE_MAX                 (1) // 0x00000001
  #define HUBS_CR_VISA_CTL_SABHUB0S_F_HUBS_VORANGE_DEF                 (0x00000000)
  #define HUBS_CR_VISA_CTL_SABHUB0S_F_HUBS_VORANGE_HSH                 (0x011F7164)

#define HUBS_CR_VISA_CTL_SABHUB0S_L_HUBS_REG                           (0x00007168)

  #define HUBS_CR_VISA_CTL_SABHUB0S_L_HUBS_EN_CLK_OFF                  ( 0)
  #define HUBS_CR_VISA_CTL_SABHUB0S_L_HUBS_EN_CLK_WID                  ( 1)
  #define HUBS_CR_VISA_CTL_SABHUB0S_L_HUBS_EN_CLK_MSK                  (0x00000001)
  #define HUBS_CR_VISA_CTL_SABHUB0S_L_HUBS_EN_CLK_MIN                  (0)
  #define HUBS_CR_VISA_CTL_SABHUB0S_L_HUBS_EN_CLK_MAX                  (1) // 0x00000001
  #define HUBS_CR_VISA_CTL_SABHUB0S_L_HUBS_EN_CLK_DEF                  (0x00000000)
  #define HUBS_CR_VISA_CTL_SABHUB0S_L_HUBS_EN_CLK_HSH                  (0x01007168)

  #define HUBS_CR_VISA_CTL_SABHUB0S_L_HUBS_L0_DATA_BYTE_SEL_OFF        ( 1)
  #define HUBS_CR_VISA_CTL_SABHUB0S_L_HUBS_L0_DATA_BYTE_SEL_WID        ( 7)
  #define HUBS_CR_VISA_CTL_SABHUB0S_L_HUBS_L0_DATA_BYTE_SEL_MSK        (0x000000FE)
  #define HUBS_CR_VISA_CTL_SABHUB0S_L_HUBS_L0_DATA_BYTE_SEL_MIN        (0)
  #define HUBS_CR_VISA_CTL_SABHUB0S_L_HUBS_L0_DATA_BYTE_SEL_MAX        (127) // 0x0000007F
  #define HUBS_CR_VISA_CTL_SABHUB0S_L_HUBS_L0_DATA_BYTE_SEL_DEF        (0x00000000)
  #define HUBS_CR_VISA_CTL_SABHUB0S_L_HUBS_L0_DATA_BYTE_SEL_HSH        (0x07017168)

  #define HUBS_CR_VISA_CTL_SABHUB0S_L_HUBS_L0_BYP_SEL_OFF              ( 8)
  #define HUBS_CR_VISA_CTL_SABHUB0S_L_HUBS_L0_BYP_SEL_WID              ( 1)
  #define HUBS_CR_VISA_CTL_SABHUB0S_L_HUBS_L0_BYP_SEL_MSK              (0x00000100)
  #define HUBS_CR_VISA_CTL_SABHUB0S_L_HUBS_L0_BYP_SEL_MIN              (0)
  #define HUBS_CR_VISA_CTL_SABHUB0S_L_HUBS_L0_BYP_SEL_MAX              (1) // 0x00000001
  #define HUBS_CR_VISA_CTL_SABHUB0S_L_HUBS_L0_BYP_SEL_DEF              (0x00000000)
  #define HUBS_CR_VISA_CTL_SABHUB0S_L_HUBS_L0_BYP_SEL_HSH              (0x01087168)

  #define HUBS_CR_VISA_CTL_SABHUB0S_L_HUBS_L1_DATA_BYTE_SEL_OFF        ( 9)
  #define HUBS_CR_VISA_CTL_SABHUB0S_L_HUBS_L1_DATA_BYTE_SEL_WID        ( 7)
  #define HUBS_CR_VISA_CTL_SABHUB0S_L_HUBS_L1_DATA_BYTE_SEL_MSK        (0x0000FE00)
  #define HUBS_CR_VISA_CTL_SABHUB0S_L_HUBS_L1_DATA_BYTE_SEL_MIN        (0)
  #define HUBS_CR_VISA_CTL_SABHUB0S_L_HUBS_L1_DATA_BYTE_SEL_MAX        (127) // 0x0000007F
  #define HUBS_CR_VISA_CTL_SABHUB0S_L_HUBS_L1_DATA_BYTE_SEL_DEF        (0x00000000)
  #define HUBS_CR_VISA_CTL_SABHUB0S_L_HUBS_L1_DATA_BYTE_SEL_HSH        (0x07097168)

  #define HUBS_CR_VISA_CTL_SABHUB0S_L_HUBS_L1_BYP_SEL_OFF              (16)
  #define HUBS_CR_VISA_CTL_SABHUB0S_L_HUBS_L1_BYP_SEL_WID              ( 1)
  #define HUBS_CR_VISA_CTL_SABHUB0S_L_HUBS_L1_BYP_SEL_MSK              (0x00010000)
  #define HUBS_CR_VISA_CTL_SABHUB0S_L_HUBS_L1_BYP_SEL_MIN              (0)
  #define HUBS_CR_VISA_CTL_SABHUB0S_L_HUBS_L1_BYP_SEL_MAX              (1) // 0x00000001
  #define HUBS_CR_VISA_CTL_SABHUB0S_L_HUBS_L1_BYP_SEL_DEF              (0x00000000)
  #define HUBS_CR_VISA_CTL_SABHUB0S_L_HUBS_L1_BYP_SEL_HSH              (0x01107168)

  #define HUBS_CR_VISA_CTL_SABHUB0S_L_HUBS_VORANGE_OFF                 (31)
  #define HUBS_CR_VISA_CTL_SABHUB0S_L_HUBS_VORANGE_WID                 ( 1)
  #define HUBS_CR_VISA_CTL_SABHUB0S_L_HUBS_VORANGE_MSK                 (0x80000000)
  #define HUBS_CR_VISA_CTL_SABHUB0S_L_HUBS_VORANGE_MIN                 (0)
  #define HUBS_CR_VISA_CTL_SABHUB0S_L_HUBS_VORANGE_MAX                 (1) // 0x00000001
  #define HUBS_CR_VISA_CTL_SABHUB0S_L_HUBS_VORANGE_DEF                 (0x00000000)
  #define HUBS_CR_VISA_CTL_SABHUB0S_L_HUBS_VORANGE_HSH                 (0x011F7168)

#define HUBS_CR_VISA_CTL_SABHUB1S_F_HUBS_REG                           (0x0000716C)

  #define HUBS_CR_VISA_CTL_SABHUB1S_F_HUBS_EN_CLK_OFF                  ( 0)
  #define HUBS_CR_VISA_CTL_SABHUB1S_F_HUBS_EN_CLK_WID                  ( 1)
  #define HUBS_CR_VISA_CTL_SABHUB1S_F_HUBS_EN_CLK_MSK                  (0x00000001)
  #define HUBS_CR_VISA_CTL_SABHUB1S_F_HUBS_EN_CLK_MIN                  (0)
  #define HUBS_CR_VISA_CTL_SABHUB1S_F_HUBS_EN_CLK_MAX                  (1) // 0x00000001
  #define HUBS_CR_VISA_CTL_SABHUB1S_F_HUBS_EN_CLK_DEF                  (0x00000000)
  #define HUBS_CR_VISA_CTL_SABHUB1S_F_HUBS_EN_CLK_HSH                  (0x0100716C)

  #define HUBS_CR_VISA_CTL_SABHUB1S_F_HUBS_L0_DATA_BYTE_SEL_OFF        ( 1)
  #define HUBS_CR_VISA_CTL_SABHUB1S_F_HUBS_L0_DATA_BYTE_SEL_WID        ( 7)
  #define HUBS_CR_VISA_CTL_SABHUB1S_F_HUBS_L0_DATA_BYTE_SEL_MSK        (0x000000FE)
  #define HUBS_CR_VISA_CTL_SABHUB1S_F_HUBS_L0_DATA_BYTE_SEL_MIN        (0)
  #define HUBS_CR_VISA_CTL_SABHUB1S_F_HUBS_L0_DATA_BYTE_SEL_MAX        (127) // 0x0000007F
  #define HUBS_CR_VISA_CTL_SABHUB1S_F_HUBS_L0_DATA_BYTE_SEL_DEF        (0x00000000)
  #define HUBS_CR_VISA_CTL_SABHUB1S_F_HUBS_L0_DATA_BYTE_SEL_HSH        (0x0701716C)

  #define HUBS_CR_VISA_CTL_SABHUB1S_F_HUBS_L0_BYP_SEL_OFF              ( 8)
  #define HUBS_CR_VISA_CTL_SABHUB1S_F_HUBS_L0_BYP_SEL_WID              ( 1)
  #define HUBS_CR_VISA_CTL_SABHUB1S_F_HUBS_L0_BYP_SEL_MSK              (0x00000100)
  #define HUBS_CR_VISA_CTL_SABHUB1S_F_HUBS_L0_BYP_SEL_MIN              (0)
  #define HUBS_CR_VISA_CTL_SABHUB1S_F_HUBS_L0_BYP_SEL_MAX              (1) // 0x00000001
  #define HUBS_CR_VISA_CTL_SABHUB1S_F_HUBS_L0_BYP_SEL_DEF              (0x00000000)
  #define HUBS_CR_VISA_CTL_SABHUB1S_F_HUBS_L0_BYP_SEL_HSH              (0x0108716C)

  #define HUBS_CR_VISA_CTL_SABHUB1S_F_HUBS_L1_DATA_BYTE_SEL_OFF        ( 9)
  #define HUBS_CR_VISA_CTL_SABHUB1S_F_HUBS_L1_DATA_BYTE_SEL_WID        ( 7)
  #define HUBS_CR_VISA_CTL_SABHUB1S_F_HUBS_L1_DATA_BYTE_SEL_MSK        (0x0000FE00)
  #define HUBS_CR_VISA_CTL_SABHUB1S_F_HUBS_L1_DATA_BYTE_SEL_MIN        (0)
  #define HUBS_CR_VISA_CTL_SABHUB1S_F_HUBS_L1_DATA_BYTE_SEL_MAX        (127) // 0x0000007F
  #define HUBS_CR_VISA_CTL_SABHUB1S_F_HUBS_L1_DATA_BYTE_SEL_DEF        (0x00000000)
  #define HUBS_CR_VISA_CTL_SABHUB1S_F_HUBS_L1_DATA_BYTE_SEL_HSH        (0x0709716C)

  #define HUBS_CR_VISA_CTL_SABHUB1S_F_HUBS_L1_BYP_SEL_OFF              (16)
  #define HUBS_CR_VISA_CTL_SABHUB1S_F_HUBS_L1_BYP_SEL_WID              ( 1)
  #define HUBS_CR_VISA_CTL_SABHUB1S_F_HUBS_L1_BYP_SEL_MSK              (0x00010000)
  #define HUBS_CR_VISA_CTL_SABHUB1S_F_HUBS_L1_BYP_SEL_MIN              (0)
  #define HUBS_CR_VISA_CTL_SABHUB1S_F_HUBS_L1_BYP_SEL_MAX              (1) // 0x00000001
  #define HUBS_CR_VISA_CTL_SABHUB1S_F_HUBS_L1_BYP_SEL_DEF              (0x00000000)
  #define HUBS_CR_VISA_CTL_SABHUB1S_F_HUBS_L1_BYP_SEL_HSH              (0x0110716C)

  #define HUBS_CR_VISA_CTL_SABHUB1S_F_HUBS_VORANGE_OFF                 (31)
  #define HUBS_CR_VISA_CTL_SABHUB1S_F_HUBS_VORANGE_WID                 ( 1)
  #define HUBS_CR_VISA_CTL_SABHUB1S_F_HUBS_VORANGE_MSK                 (0x80000000)
  #define HUBS_CR_VISA_CTL_SABHUB1S_F_HUBS_VORANGE_MIN                 (0)
  #define HUBS_CR_VISA_CTL_SABHUB1S_F_HUBS_VORANGE_MAX                 (1) // 0x00000001
  #define HUBS_CR_VISA_CTL_SABHUB1S_F_HUBS_VORANGE_DEF                 (0x00000000)
  #define HUBS_CR_VISA_CTL_SABHUB1S_F_HUBS_VORANGE_HSH                 (0x011F716C)

#define HUBS_CR_VISA_CTL_SABHUB1S_L_HUBS_REG                           (0x00007170)

  #define HUBS_CR_VISA_CTL_SABHUB1S_L_HUBS_EN_CLK_OFF                  ( 0)
  #define HUBS_CR_VISA_CTL_SABHUB1S_L_HUBS_EN_CLK_WID                  ( 1)
  #define HUBS_CR_VISA_CTL_SABHUB1S_L_HUBS_EN_CLK_MSK                  (0x00000001)
  #define HUBS_CR_VISA_CTL_SABHUB1S_L_HUBS_EN_CLK_MIN                  (0)
  #define HUBS_CR_VISA_CTL_SABHUB1S_L_HUBS_EN_CLK_MAX                  (1) // 0x00000001
  #define HUBS_CR_VISA_CTL_SABHUB1S_L_HUBS_EN_CLK_DEF                  (0x00000000)
  #define HUBS_CR_VISA_CTL_SABHUB1S_L_HUBS_EN_CLK_HSH                  (0x01007170)

  #define HUBS_CR_VISA_CTL_SABHUB1S_L_HUBS_L0_DATA_BYTE_SEL_OFF        ( 1)
  #define HUBS_CR_VISA_CTL_SABHUB1S_L_HUBS_L0_DATA_BYTE_SEL_WID        ( 7)
  #define HUBS_CR_VISA_CTL_SABHUB1S_L_HUBS_L0_DATA_BYTE_SEL_MSK        (0x000000FE)
  #define HUBS_CR_VISA_CTL_SABHUB1S_L_HUBS_L0_DATA_BYTE_SEL_MIN        (0)
  #define HUBS_CR_VISA_CTL_SABHUB1S_L_HUBS_L0_DATA_BYTE_SEL_MAX        (127) // 0x0000007F
  #define HUBS_CR_VISA_CTL_SABHUB1S_L_HUBS_L0_DATA_BYTE_SEL_DEF        (0x00000000)
  #define HUBS_CR_VISA_CTL_SABHUB1S_L_HUBS_L0_DATA_BYTE_SEL_HSH        (0x07017170)

  #define HUBS_CR_VISA_CTL_SABHUB1S_L_HUBS_L0_BYP_SEL_OFF              ( 8)
  #define HUBS_CR_VISA_CTL_SABHUB1S_L_HUBS_L0_BYP_SEL_WID              ( 1)
  #define HUBS_CR_VISA_CTL_SABHUB1S_L_HUBS_L0_BYP_SEL_MSK              (0x00000100)
  #define HUBS_CR_VISA_CTL_SABHUB1S_L_HUBS_L0_BYP_SEL_MIN              (0)
  #define HUBS_CR_VISA_CTL_SABHUB1S_L_HUBS_L0_BYP_SEL_MAX              (1) // 0x00000001
  #define HUBS_CR_VISA_CTL_SABHUB1S_L_HUBS_L0_BYP_SEL_DEF              (0x00000000)
  #define HUBS_CR_VISA_CTL_SABHUB1S_L_HUBS_L0_BYP_SEL_HSH              (0x01087170)

  #define HUBS_CR_VISA_CTL_SABHUB1S_L_HUBS_L1_DATA_BYTE_SEL_OFF        ( 9)
  #define HUBS_CR_VISA_CTL_SABHUB1S_L_HUBS_L1_DATA_BYTE_SEL_WID        ( 7)
  #define HUBS_CR_VISA_CTL_SABHUB1S_L_HUBS_L1_DATA_BYTE_SEL_MSK        (0x0000FE00)
  #define HUBS_CR_VISA_CTL_SABHUB1S_L_HUBS_L1_DATA_BYTE_SEL_MIN        (0)
  #define HUBS_CR_VISA_CTL_SABHUB1S_L_HUBS_L1_DATA_BYTE_SEL_MAX        (127) // 0x0000007F
  #define HUBS_CR_VISA_CTL_SABHUB1S_L_HUBS_L1_DATA_BYTE_SEL_DEF        (0x00000000)
  #define HUBS_CR_VISA_CTL_SABHUB1S_L_HUBS_L1_DATA_BYTE_SEL_HSH        (0x07097170)

  #define HUBS_CR_VISA_CTL_SABHUB1S_L_HUBS_L1_BYP_SEL_OFF              (16)
  #define HUBS_CR_VISA_CTL_SABHUB1S_L_HUBS_L1_BYP_SEL_WID              ( 1)
  #define HUBS_CR_VISA_CTL_SABHUB1S_L_HUBS_L1_BYP_SEL_MSK              (0x00010000)
  #define HUBS_CR_VISA_CTL_SABHUB1S_L_HUBS_L1_BYP_SEL_MIN              (0)
  #define HUBS_CR_VISA_CTL_SABHUB1S_L_HUBS_L1_BYP_SEL_MAX              (1) // 0x00000001
  #define HUBS_CR_VISA_CTL_SABHUB1S_L_HUBS_L1_BYP_SEL_DEF              (0x00000000)
  #define HUBS_CR_VISA_CTL_SABHUB1S_L_HUBS_L1_BYP_SEL_HSH              (0x01107170)

  #define HUBS_CR_VISA_CTL_SABHUB1S_L_HUBS_VORANGE_OFF                 (31)
  #define HUBS_CR_VISA_CTL_SABHUB1S_L_HUBS_VORANGE_WID                 ( 1)
  #define HUBS_CR_VISA_CTL_SABHUB1S_L_HUBS_VORANGE_MSK                 (0x80000000)
  #define HUBS_CR_VISA_CTL_SABHUB1S_L_HUBS_VORANGE_MIN                 (0)
  #define HUBS_CR_VISA_CTL_SABHUB1S_L_HUBS_VORANGE_MAX                 (1) // 0x00000001
  #define HUBS_CR_VISA_CTL_SABHUB1S_L_HUBS_VORANGE_DEF                 (0x00000000)
  #define HUBS_CR_VISA_CTL_SABHUB1S_L_HUBS_VORANGE_HSH                 (0x011F7170)

#define HUBS_CR_VISA_CTL_SABHUB2S_F_HUBS_REG                           (0x00007174)

  #define HUBS_CR_VISA_CTL_SABHUB2S_F_HUBS_EN_CLK_OFF                  ( 0)
  #define HUBS_CR_VISA_CTL_SABHUB2S_F_HUBS_EN_CLK_WID                  ( 1)
  #define HUBS_CR_VISA_CTL_SABHUB2S_F_HUBS_EN_CLK_MSK                  (0x00000001)
  #define HUBS_CR_VISA_CTL_SABHUB2S_F_HUBS_EN_CLK_MIN                  (0)
  #define HUBS_CR_VISA_CTL_SABHUB2S_F_HUBS_EN_CLK_MAX                  (1) // 0x00000001
  #define HUBS_CR_VISA_CTL_SABHUB2S_F_HUBS_EN_CLK_DEF                  (0x00000000)
  #define HUBS_CR_VISA_CTL_SABHUB2S_F_HUBS_EN_CLK_HSH                  (0x01007174)

  #define HUBS_CR_VISA_CTL_SABHUB2S_F_HUBS_L0_DATA_BYTE_SEL_OFF        ( 1)
  #define HUBS_CR_VISA_CTL_SABHUB2S_F_HUBS_L0_DATA_BYTE_SEL_WID        ( 7)
  #define HUBS_CR_VISA_CTL_SABHUB2S_F_HUBS_L0_DATA_BYTE_SEL_MSK        (0x000000FE)
  #define HUBS_CR_VISA_CTL_SABHUB2S_F_HUBS_L0_DATA_BYTE_SEL_MIN        (0)
  #define HUBS_CR_VISA_CTL_SABHUB2S_F_HUBS_L0_DATA_BYTE_SEL_MAX        (127) // 0x0000007F
  #define HUBS_CR_VISA_CTL_SABHUB2S_F_HUBS_L0_DATA_BYTE_SEL_DEF        (0x00000000)
  #define HUBS_CR_VISA_CTL_SABHUB2S_F_HUBS_L0_DATA_BYTE_SEL_HSH        (0x07017174)

  #define HUBS_CR_VISA_CTL_SABHUB2S_F_HUBS_L0_BYP_SEL_OFF              ( 8)
  #define HUBS_CR_VISA_CTL_SABHUB2S_F_HUBS_L0_BYP_SEL_WID              ( 1)
  #define HUBS_CR_VISA_CTL_SABHUB2S_F_HUBS_L0_BYP_SEL_MSK              (0x00000100)
  #define HUBS_CR_VISA_CTL_SABHUB2S_F_HUBS_L0_BYP_SEL_MIN              (0)
  #define HUBS_CR_VISA_CTL_SABHUB2S_F_HUBS_L0_BYP_SEL_MAX              (1) // 0x00000001
  #define HUBS_CR_VISA_CTL_SABHUB2S_F_HUBS_L0_BYP_SEL_DEF              (0x00000000)
  #define HUBS_CR_VISA_CTL_SABHUB2S_F_HUBS_L0_BYP_SEL_HSH              (0x01087174)

  #define HUBS_CR_VISA_CTL_SABHUB2S_F_HUBS_L1_DATA_BYTE_SEL_OFF        ( 9)
  #define HUBS_CR_VISA_CTL_SABHUB2S_F_HUBS_L1_DATA_BYTE_SEL_WID        ( 7)
  #define HUBS_CR_VISA_CTL_SABHUB2S_F_HUBS_L1_DATA_BYTE_SEL_MSK        (0x0000FE00)
  #define HUBS_CR_VISA_CTL_SABHUB2S_F_HUBS_L1_DATA_BYTE_SEL_MIN        (0)
  #define HUBS_CR_VISA_CTL_SABHUB2S_F_HUBS_L1_DATA_BYTE_SEL_MAX        (127) // 0x0000007F
  #define HUBS_CR_VISA_CTL_SABHUB2S_F_HUBS_L1_DATA_BYTE_SEL_DEF        (0x00000000)
  #define HUBS_CR_VISA_CTL_SABHUB2S_F_HUBS_L1_DATA_BYTE_SEL_HSH        (0x07097174)

  #define HUBS_CR_VISA_CTL_SABHUB2S_F_HUBS_L1_BYP_SEL_OFF              (16)
  #define HUBS_CR_VISA_CTL_SABHUB2S_F_HUBS_L1_BYP_SEL_WID              ( 1)
  #define HUBS_CR_VISA_CTL_SABHUB2S_F_HUBS_L1_BYP_SEL_MSK              (0x00010000)
  #define HUBS_CR_VISA_CTL_SABHUB2S_F_HUBS_L1_BYP_SEL_MIN              (0)
  #define HUBS_CR_VISA_CTL_SABHUB2S_F_HUBS_L1_BYP_SEL_MAX              (1) // 0x00000001
  #define HUBS_CR_VISA_CTL_SABHUB2S_F_HUBS_L1_BYP_SEL_DEF              (0x00000000)
  #define HUBS_CR_VISA_CTL_SABHUB2S_F_HUBS_L1_BYP_SEL_HSH              (0x01107174)

  #define HUBS_CR_VISA_CTL_SABHUB2S_F_HUBS_PATGENMODE_OFF              (27)
  #define HUBS_CR_VISA_CTL_SABHUB2S_F_HUBS_PATGENMODE_WID              ( 3)
  #define HUBS_CR_VISA_CTL_SABHUB2S_F_HUBS_PATGENMODE_MSK              (0x38000000)
  #define HUBS_CR_VISA_CTL_SABHUB2S_F_HUBS_PATGENMODE_MIN              (0)
  #define HUBS_CR_VISA_CTL_SABHUB2S_F_HUBS_PATGENMODE_MAX              (7) // 0x00000007
  #define HUBS_CR_VISA_CTL_SABHUB2S_F_HUBS_PATGENMODE_DEF              (0x00000000)
  #define HUBS_CR_VISA_CTL_SABHUB2S_F_HUBS_PATGENMODE_HSH              (0x031B7174)

  #define HUBS_CR_VISA_CTL_SABHUB2S_F_HUBS_VORANGE_OFF                 (31)
  #define HUBS_CR_VISA_CTL_SABHUB2S_F_HUBS_VORANGE_WID                 ( 1)
  #define HUBS_CR_VISA_CTL_SABHUB2S_F_HUBS_VORANGE_MSK                 (0x80000000)
  #define HUBS_CR_VISA_CTL_SABHUB2S_F_HUBS_VORANGE_MIN                 (0)
  #define HUBS_CR_VISA_CTL_SABHUB2S_F_HUBS_VORANGE_MAX                 (1) // 0x00000001
  #define HUBS_CR_VISA_CTL_SABHUB2S_F_HUBS_VORANGE_DEF                 (0x00000000)
  #define HUBS_CR_VISA_CTL_SABHUB2S_F_HUBS_VORANGE_HSH                 (0x011F7174)

#define HUBS_CR_VISA_XBAR_SABHUB1S_F_HUBS_REG                          (0x00007178)

  #define HUBS_CR_VISA_XBAR_SABHUB1S_F_HUBS_FXB_Li_BIT0_DATA_BIT_SEL_OFF ( 0)
  #define HUBS_CR_VISA_XBAR_SABHUB1S_F_HUBS_FXB_Li_BIT0_DATA_BIT_SEL_WID ( 3)
  #define HUBS_CR_VISA_XBAR_SABHUB1S_F_HUBS_FXB_Li_BIT0_DATA_BIT_SEL_MSK (0x00000007)
  #define HUBS_CR_VISA_XBAR_SABHUB1S_F_HUBS_FXB_Li_BIT0_DATA_BIT_SEL_MIN (0)
  #define HUBS_CR_VISA_XBAR_SABHUB1S_F_HUBS_FXB_Li_BIT0_DATA_BIT_SEL_MAX (7) // 0x00000007
  #define HUBS_CR_VISA_XBAR_SABHUB1S_F_HUBS_FXB_Li_BIT0_DATA_BIT_SEL_DEF (0x00000000)
  #define HUBS_CR_VISA_XBAR_SABHUB1S_F_HUBS_FXB_Li_BIT0_DATA_BIT_SEL_HSH (0x03007178)

  #define HUBS_CR_VISA_XBAR_SABHUB1S_F_HUBS_FXB_Li_BIT0_DATA_BYTE_SEL_OFF ( 3)
  #define HUBS_CR_VISA_XBAR_SABHUB1S_F_HUBS_FXB_Li_BIT0_DATA_BYTE_SEL_WID ( 1)
  #define HUBS_CR_VISA_XBAR_SABHUB1S_F_HUBS_FXB_Li_BIT0_DATA_BYTE_SEL_MSK (0x00000008)
  #define HUBS_CR_VISA_XBAR_SABHUB1S_F_HUBS_FXB_Li_BIT0_DATA_BYTE_SEL_MIN (0)
  #define HUBS_CR_VISA_XBAR_SABHUB1S_F_HUBS_FXB_Li_BIT0_DATA_BYTE_SEL_MAX (1) // 0x00000001
  #define HUBS_CR_VISA_XBAR_SABHUB1S_F_HUBS_FXB_Li_BIT0_DATA_BYTE_SEL_DEF (0x00000000)
  #define HUBS_CR_VISA_XBAR_SABHUB1S_F_HUBS_FXB_Li_BIT0_DATA_BYTE_SEL_HSH (0x01037178)

  #define HUBS_CR_VISA_XBAR_SABHUB1S_F_HUBS_FXB_Li_BIT1_DATA_BIT_SEL_OFF ( 4)
  #define HUBS_CR_VISA_XBAR_SABHUB1S_F_HUBS_FXB_Li_BIT1_DATA_BIT_SEL_WID ( 3)
  #define HUBS_CR_VISA_XBAR_SABHUB1S_F_HUBS_FXB_Li_BIT1_DATA_BIT_SEL_MSK (0x00000070)
  #define HUBS_CR_VISA_XBAR_SABHUB1S_F_HUBS_FXB_Li_BIT1_DATA_BIT_SEL_MIN (0)
  #define HUBS_CR_VISA_XBAR_SABHUB1S_F_HUBS_FXB_Li_BIT1_DATA_BIT_SEL_MAX (7) // 0x00000007
  #define HUBS_CR_VISA_XBAR_SABHUB1S_F_HUBS_FXB_Li_BIT1_DATA_BIT_SEL_DEF (0x00000001)
  #define HUBS_CR_VISA_XBAR_SABHUB1S_F_HUBS_FXB_Li_BIT1_DATA_BIT_SEL_HSH (0x03047178)

  #define HUBS_CR_VISA_XBAR_SABHUB1S_F_HUBS_FXB_Li_BIT1_DATA_BYTE_SEL_OFF ( 7)
  #define HUBS_CR_VISA_XBAR_SABHUB1S_F_HUBS_FXB_Li_BIT1_DATA_BYTE_SEL_WID ( 1)
  #define HUBS_CR_VISA_XBAR_SABHUB1S_F_HUBS_FXB_Li_BIT1_DATA_BYTE_SEL_MSK (0x00000080)
  #define HUBS_CR_VISA_XBAR_SABHUB1S_F_HUBS_FXB_Li_BIT1_DATA_BYTE_SEL_MIN (0)
  #define HUBS_CR_VISA_XBAR_SABHUB1S_F_HUBS_FXB_Li_BIT1_DATA_BYTE_SEL_MAX (1) // 0x00000001
  #define HUBS_CR_VISA_XBAR_SABHUB1S_F_HUBS_FXB_Li_BIT1_DATA_BYTE_SEL_DEF (0x00000000)
  #define HUBS_CR_VISA_XBAR_SABHUB1S_F_HUBS_FXB_Li_BIT1_DATA_BYTE_SEL_HSH (0x01077178)

  #define HUBS_CR_VISA_XBAR_SABHUB1S_F_HUBS_FXB_Li_BIT2_DATA_BIT_SEL_OFF ( 8)
  #define HUBS_CR_VISA_XBAR_SABHUB1S_F_HUBS_FXB_Li_BIT2_DATA_BIT_SEL_WID ( 3)
  #define HUBS_CR_VISA_XBAR_SABHUB1S_F_HUBS_FXB_Li_BIT2_DATA_BIT_SEL_MSK (0x00000700)
  #define HUBS_CR_VISA_XBAR_SABHUB1S_F_HUBS_FXB_Li_BIT2_DATA_BIT_SEL_MIN (0)
  #define HUBS_CR_VISA_XBAR_SABHUB1S_F_HUBS_FXB_Li_BIT2_DATA_BIT_SEL_MAX (7) // 0x00000007
  #define HUBS_CR_VISA_XBAR_SABHUB1S_F_HUBS_FXB_Li_BIT2_DATA_BIT_SEL_DEF (0x00000002)
  #define HUBS_CR_VISA_XBAR_SABHUB1S_F_HUBS_FXB_Li_BIT2_DATA_BIT_SEL_HSH (0x03087178)

  #define HUBS_CR_VISA_XBAR_SABHUB1S_F_HUBS_FXB_Li_BIT2_DATA_BYTE_SEL_OFF (11)
  #define HUBS_CR_VISA_XBAR_SABHUB1S_F_HUBS_FXB_Li_BIT2_DATA_BYTE_SEL_WID ( 1)
  #define HUBS_CR_VISA_XBAR_SABHUB1S_F_HUBS_FXB_Li_BIT2_DATA_BYTE_SEL_MSK (0x00000800)
  #define HUBS_CR_VISA_XBAR_SABHUB1S_F_HUBS_FXB_Li_BIT2_DATA_BYTE_SEL_MIN (0)
  #define HUBS_CR_VISA_XBAR_SABHUB1S_F_HUBS_FXB_Li_BIT2_DATA_BYTE_SEL_MAX (1) // 0x00000001
  #define HUBS_CR_VISA_XBAR_SABHUB1S_F_HUBS_FXB_Li_BIT2_DATA_BYTE_SEL_DEF (0x00000000)
  #define HUBS_CR_VISA_XBAR_SABHUB1S_F_HUBS_FXB_Li_BIT2_DATA_BYTE_SEL_HSH (0x010B7178)

  #define HUBS_CR_VISA_XBAR_SABHUB1S_F_HUBS_FXB_Li_BIT3_DATA_BIT_SEL_OFF (12)
  #define HUBS_CR_VISA_XBAR_SABHUB1S_F_HUBS_FXB_Li_BIT3_DATA_BIT_SEL_WID ( 3)
  #define HUBS_CR_VISA_XBAR_SABHUB1S_F_HUBS_FXB_Li_BIT3_DATA_BIT_SEL_MSK (0x00007000)
  #define HUBS_CR_VISA_XBAR_SABHUB1S_F_HUBS_FXB_Li_BIT3_DATA_BIT_SEL_MIN (0)
  #define HUBS_CR_VISA_XBAR_SABHUB1S_F_HUBS_FXB_Li_BIT3_DATA_BIT_SEL_MAX (7) // 0x00000007
  #define HUBS_CR_VISA_XBAR_SABHUB1S_F_HUBS_FXB_Li_BIT3_DATA_BIT_SEL_DEF (0x00000003)
  #define HUBS_CR_VISA_XBAR_SABHUB1S_F_HUBS_FXB_Li_BIT3_DATA_BIT_SEL_HSH (0x030C7178)

  #define HUBS_CR_VISA_XBAR_SABHUB1S_F_HUBS_FXB_Li_BIT3_DATA_BYTE_SEL_OFF (15)
  #define HUBS_CR_VISA_XBAR_SABHUB1S_F_HUBS_FXB_Li_BIT3_DATA_BYTE_SEL_WID ( 1)
  #define HUBS_CR_VISA_XBAR_SABHUB1S_F_HUBS_FXB_Li_BIT3_DATA_BYTE_SEL_MSK (0x00008000)
  #define HUBS_CR_VISA_XBAR_SABHUB1S_F_HUBS_FXB_Li_BIT3_DATA_BYTE_SEL_MIN (0)
  #define HUBS_CR_VISA_XBAR_SABHUB1S_F_HUBS_FXB_Li_BIT3_DATA_BYTE_SEL_MAX (1) // 0x00000001
  #define HUBS_CR_VISA_XBAR_SABHUB1S_F_HUBS_FXB_Li_BIT3_DATA_BYTE_SEL_DEF (0x00000000)
  #define HUBS_CR_VISA_XBAR_SABHUB1S_F_HUBS_FXB_Li_BIT3_DATA_BYTE_SEL_HSH (0x010F7178)

  #define HUBS_CR_VISA_XBAR_SABHUB1S_F_HUBS_FXB_Li_BIT4_DATA_BIT_SEL_OFF (16)
  #define HUBS_CR_VISA_XBAR_SABHUB1S_F_HUBS_FXB_Li_BIT4_DATA_BIT_SEL_WID ( 3)
  #define HUBS_CR_VISA_XBAR_SABHUB1S_F_HUBS_FXB_Li_BIT4_DATA_BIT_SEL_MSK (0x00070000)
  #define HUBS_CR_VISA_XBAR_SABHUB1S_F_HUBS_FXB_Li_BIT4_DATA_BIT_SEL_MIN (0)
  #define HUBS_CR_VISA_XBAR_SABHUB1S_F_HUBS_FXB_Li_BIT4_DATA_BIT_SEL_MAX (7) // 0x00000007
  #define HUBS_CR_VISA_XBAR_SABHUB1S_F_HUBS_FXB_Li_BIT4_DATA_BIT_SEL_DEF (0x00000004)
  #define HUBS_CR_VISA_XBAR_SABHUB1S_F_HUBS_FXB_Li_BIT4_DATA_BIT_SEL_HSH (0x03107178)

  #define HUBS_CR_VISA_XBAR_SABHUB1S_F_HUBS_FXB_Li_BIT4_DATA_BYTE_SEL_OFF (19)
  #define HUBS_CR_VISA_XBAR_SABHUB1S_F_HUBS_FXB_Li_BIT4_DATA_BYTE_SEL_WID ( 1)
  #define HUBS_CR_VISA_XBAR_SABHUB1S_F_HUBS_FXB_Li_BIT4_DATA_BYTE_SEL_MSK (0x00080000)
  #define HUBS_CR_VISA_XBAR_SABHUB1S_F_HUBS_FXB_Li_BIT4_DATA_BYTE_SEL_MIN (0)
  #define HUBS_CR_VISA_XBAR_SABHUB1S_F_HUBS_FXB_Li_BIT4_DATA_BYTE_SEL_MAX (1) // 0x00000001
  #define HUBS_CR_VISA_XBAR_SABHUB1S_F_HUBS_FXB_Li_BIT4_DATA_BYTE_SEL_DEF (0x00000000)
  #define HUBS_CR_VISA_XBAR_SABHUB1S_F_HUBS_FXB_Li_BIT4_DATA_BYTE_SEL_HSH (0x01137178)

  #define HUBS_CR_VISA_XBAR_SABHUB1S_F_HUBS_FXB_Li_BIT5_DATA_BIT_SEL_OFF (20)
  #define HUBS_CR_VISA_XBAR_SABHUB1S_F_HUBS_FXB_Li_BIT5_DATA_BIT_SEL_WID ( 3)
  #define HUBS_CR_VISA_XBAR_SABHUB1S_F_HUBS_FXB_Li_BIT5_DATA_BIT_SEL_MSK (0x00700000)
  #define HUBS_CR_VISA_XBAR_SABHUB1S_F_HUBS_FXB_Li_BIT5_DATA_BIT_SEL_MIN (0)
  #define HUBS_CR_VISA_XBAR_SABHUB1S_F_HUBS_FXB_Li_BIT5_DATA_BIT_SEL_MAX (7) // 0x00000007
  #define HUBS_CR_VISA_XBAR_SABHUB1S_F_HUBS_FXB_Li_BIT5_DATA_BIT_SEL_DEF (0x00000005)
  #define HUBS_CR_VISA_XBAR_SABHUB1S_F_HUBS_FXB_Li_BIT5_DATA_BIT_SEL_HSH (0x03147178)

  #define HUBS_CR_VISA_XBAR_SABHUB1S_F_HUBS_FXB_Li_BIT5_DATA_BYTE_SEL_OFF (23)
  #define HUBS_CR_VISA_XBAR_SABHUB1S_F_HUBS_FXB_Li_BIT5_DATA_BYTE_SEL_WID ( 1)
  #define HUBS_CR_VISA_XBAR_SABHUB1S_F_HUBS_FXB_Li_BIT5_DATA_BYTE_SEL_MSK (0x00800000)
  #define HUBS_CR_VISA_XBAR_SABHUB1S_F_HUBS_FXB_Li_BIT5_DATA_BYTE_SEL_MIN (0)
  #define HUBS_CR_VISA_XBAR_SABHUB1S_F_HUBS_FXB_Li_BIT5_DATA_BYTE_SEL_MAX (1) // 0x00000001
  #define HUBS_CR_VISA_XBAR_SABHUB1S_F_HUBS_FXB_Li_BIT5_DATA_BYTE_SEL_DEF (0x00000000)
  #define HUBS_CR_VISA_XBAR_SABHUB1S_F_HUBS_FXB_Li_BIT5_DATA_BYTE_SEL_HSH (0x01177178)

  #define HUBS_CR_VISA_XBAR_SABHUB1S_F_HUBS_FXB_Li_BIT6_DATA_BIT_SEL_OFF (24)
  #define HUBS_CR_VISA_XBAR_SABHUB1S_F_HUBS_FXB_Li_BIT6_DATA_BIT_SEL_WID ( 3)
  #define HUBS_CR_VISA_XBAR_SABHUB1S_F_HUBS_FXB_Li_BIT6_DATA_BIT_SEL_MSK (0x07000000)
  #define HUBS_CR_VISA_XBAR_SABHUB1S_F_HUBS_FXB_Li_BIT6_DATA_BIT_SEL_MIN (0)
  #define HUBS_CR_VISA_XBAR_SABHUB1S_F_HUBS_FXB_Li_BIT6_DATA_BIT_SEL_MAX (7) // 0x00000007
  #define HUBS_CR_VISA_XBAR_SABHUB1S_F_HUBS_FXB_Li_BIT6_DATA_BIT_SEL_DEF (0x00000006)
  #define HUBS_CR_VISA_XBAR_SABHUB1S_F_HUBS_FXB_Li_BIT6_DATA_BIT_SEL_HSH (0x03187178)

  #define HUBS_CR_VISA_XBAR_SABHUB1S_F_HUBS_FXB_Li_BIT6_DATA_BYTE_SEL_OFF (27)
  #define HUBS_CR_VISA_XBAR_SABHUB1S_F_HUBS_FXB_Li_BIT6_DATA_BYTE_SEL_WID ( 1)
  #define HUBS_CR_VISA_XBAR_SABHUB1S_F_HUBS_FXB_Li_BIT6_DATA_BYTE_SEL_MSK (0x08000000)
  #define HUBS_CR_VISA_XBAR_SABHUB1S_F_HUBS_FXB_Li_BIT6_DATA_BYTE_SEL_MIN (0)
  #define HUBS_CR_VISA_XBAR_SABHUB1S_F_HUBS_FXB_Li_BIT6_DATA_BYTE_SEL_MAX (1) // 0x00000001
  #define HUBS_CR_VISA_XBAR_SABHUB1S_F_HUBS_FXB_Li_BIT6_DATA_BYTE_SEL_DEF (0x00000000)
  #define HUBS_CR_VISA_XBAR_SABHUB1S_F_HUBS_FXB_Li_BIT6_DATA_BYTE_SEL_HSH (0x011B7178)

  #define HUBS_CR_VISA_XBAR_SABHUB1S_F_HUBS_FXB_Li_BIT7_DATA_BIT_SEL_OFF (28)
  #define HUBS_CR_VISA_XBAR_SABHUB1S_F_HUBS_FXB_Li_BIT7_DATA_BIT_SEL_WID ( 3)
  #define HUBS_CR_VISA_XBAR_SABHUB1S_F_HUBS_FXB_Li_BIT7_DATA_BIT_SEL_MSK (0x70000000)
  #define HUBS_CR_VISA_XBAR_SABHUB1S_F_HUBS_FXB_Li_BIT7_DATA_BIT_SEL_MIN (0)
  #define HUBS_CR_VISA_XBAR_SABHUB1S_F_HUBS_FXB_Li_BIT7_DATA_BIT_SEL_MAX (7) // 0x00000007
  #define HUBS_CR_VISA_XBAR_SABHUB1S_F_HUBS_FXB_Li_BIT7_DATA_BIT_SEL_DEF (0x00000007)
  #define HUBS_CR_VISA_XBAR_SABHUB1S_F_HUBS_FXB_Li_BIT7_DATA_BIT_SEL_HSH (0x031C7178)

  #define HUBS_CR_VISA_XBAR_SABHUB1S_F_HUBS_FXB_Li_BIT7_DATA_BYTE_SEL_OFF (31)
  #define HUBS_CR_VISA_XBAR_SABHUB1S_F_HUBS_FXB_Li_BIT7_DATA_BYTE_SEL_WID ( 1)
  #define HUBS_CR_VISA_XBAR_SABHUB1S_F_HUBS_FXB_Li_BIT7_DATA_BYTE_SEL_MSK (0x80000000)
  #define HUBS_CR_VISA_XBAR_SABHUB1S_F_HUBS_FXB_Li_BIT7_DATA_BYTE_SEL_MIN (0)
  #define HUBS_CR_VISA_XBAR_SABHUB1S_F_HUBS_FXB_Li_BIT7_DATA_BYTE_SEL_MAX (1) // 0x00000001
  #define HUBS_CR_VISA_XBAR_SABHUB1S_F_HUBS_FXB_Li_BIT7_DATA_BYTE_SEL_DEF (0x00000000)
  #define HUBS_CR_VISA_XBAR_SABHUB1S_F_HUBS_FXB_Li_BIT7_DATA_BYTE_SEL_HSH (0x011F7178)

#define HUBS_CR_VISA_XBAR_SABHUB2S_F_HUBS_REG                          (0x0000717C)

  #define HUBS_CR_VISA_XBAR_SABHUB2S_F_HUBS_FXB_Li_BIT0_DATA_BIT_SEL_OFF ( 0)
  #define HUBS_CR_VISA_XBAR_SABHUB2S_F_HUBS_FXB_Li_BIT0_DATA_BIT_SEL_WID ( 3)
  #define HUBS_CR_VISA_XBAR_SABHUB2S_F_HUBS_FXB_Li_BIT0_DATA_BIT_SEL_MSK (0x00000007)
  #define HUBS_CR_VISA_XBAR_SABHUB2S_F_HUBS_FXB_Li_BIT0_DATA_BIT_SEL_MIN (0)
  #define HUBS_CR_VISA_XBAR_SABHUB2S_F_HUBS_FXB_Li_BIT0_DATA_BIT_SEL_MAX (7) // 0x00000007
  #define HUBS_CR_VISA_XBAR_SABHUB2S_F_HUBS_FXB_Li_BIT0_DATA_BIT_SEL_DEF (0x00000000)
  #define HUBS_CR_VISA_XBAR_SABHUB2S_F_HUBS_FXB_Li_BIT0_DATA_BIT_SEL_HSH (0x0300717C)

  #define HUBS_CR_VISA_XBAR_SABHUB2S_F_HUBS_FXB_Li_BIT0_DATA_BYTE_SEL_OFF ( 3)
  #define HUBS_CR_VISA_XBAR_SABHUB2S_F_HUBS_FXB_Li_BIT0_DATA_BYTE_SEL_WID ( 1)
  #define HUBS_CR_VISA_XBAR_SABHUB2S_F_HUBS_FXB_Li_BIT0_DATA_BYTE_SEL_MSK (0x00000008)
  #define HUBS_CR_VISA_XBAR_SABHUB2S_F_HUBS_FXB_Li_BIT0_DATA_BYTE_SEL_MIN (0)
  #define HUBS_CR_VISA_XBAR_SABHUB2S_F_HUBS_FXB_Li_BIT0_DATA_BYTE_SEL_MAX (1) // 0x00000001
  #define HUBS_CR_VISA_XBAR_SABHUB2S_F_HUBS_FXB_Li_BIT0_DATA_BYTE_SEL_DEF (0x00000000)
  #define HUBS_CR_VISA_XBAR_SABHUB2S_F_HUBS_FXB_Li_BIT0_DATA_BYTE_SEL_HSH (0x0103717C)

  #define HUBS_CR_VISA_XBAR_SABHUB2S_F_HUBS_FXB_Li_BIT1_DATA_BIT_SEL_OFF ( 4)
  #define HUBS_CR_VISA_XBAR_SABHUB2S_F_HUBS_FXB_Li_BIT1_DATA_BIT_SEL_WID ( 3)
  #define HUBS_CR_VISA_XBAR_SABHUB2S_F_HUBS_FXB_Li_BIT1_DATA_BIT_SEL_MSK (0x00000070)
  #define HUBS_CR_VISA_XBAR_SABHUB2S_F_HUBS_FXB_Li_BIT1_DATA_BIT_SEL_MIN (0)
  #define HUBS_CR_VISA_XBAR_SABHUB2S_F_HUBS_FXB_Li_BIT1_DATA_BIT_SEL_MAX (7) // 0x00000007
  #define HUBS_CR_VISA_XBAR_SABHUB2S_F_HUBS_FXB_Li_BIT1_DATA_BIT_SEL_DEF (0x00000001)
  #define HUBS_CR_VISA_XBAR_SABHUB2S_F_HUBS_FXB_Li_BIT1_DATA_BIT_SEL_HSH (0x0304717C)

  #define HUBS_CR_VISA_XBAR_SABHUB2S_F_HUBS_FXB_Li_BIT1_DATA_BYTE_SEL_OFF ( 7)
  #define HUBS_CR_VISA_XBAR_SABHUB2S_F_HUBS_FXB_Li_BIT1_DATA_BYTE_SEL_WID ( 1)
  #define HUBS_CR_VISA_XBAR_SABHUB2S_F_HUBS_FXB_Li_BIT1_DATA_BYTE_SEL_MSK (0x00000080)
  #define HUBS_CR_VISA_XBAR_SABHUB2S_F_HUBS_FXB_Li_BIT1_DATA_BYTE_SEL_MIN (0)
  #define HUBS_CR_VISA_XBAR_SABHUB2S_F_HUBS_FXB_Li_BIT1_DATA_BYTE_SEL_MAX (1) // 0x00000001
  #define HUBS_CR_VISA_XBAR_SABHUB2S_F_HUBS_FXB_Li_BIT1_DATA_BYTE_SEL_DEF (0x00000000)
  #define HUBS_CR_VISA_XBAR_SABHUB2S_F_HUBS_FXB_Li_BIT1_DATA_BYTE_SEL_HSH (0x0107717C)

  #define HUBS_CR_VISA_XBAR_SABHUB2S_F_HUBS_FXB_Li_BIT2_DATA_BIT_SEL_OFF ( 8)
  #define HUBS_CR_VISA_XBAR_SABHUB2S_F_HUBS_FXB_Li_BIT2_DATA_BIT_SEL_WID ( 3)
  #define HUBS_CR_VISA_XBAR_SABHUB2S_F_HUBS_FXB_Li_BIT2_DATA_BIT_SEL_MSK (0x00000700)
  #define HUBS_CR_VISA_XBAR_SABHUB2S_F_HUBS_FXB_Li_BIT2_DATA_BIT_SEL_MIN (0)
  #define HUBS_CR_VISA_XBAR_SABHUB2S_F_HUBS_FXB_Li_BIT2_DATA_BIT_SEL_MAX (7) // 0x00000007
  #define HUBS_CR_VISA_XBAR_SABHUB2S_F_HUBS_FXB_Li_BIT2_DATA_BIT_SEL_DEF (0x00000002)
  #define HUBS_CR_VISA_XBAR_SABHUB2S_F_HUBS_FXB_Li_BIT2_DATA_BIT_SEL_HSH (0x0308717C)

  #define HUBS_CR_VISA_XBAR_SABHUB2S_F_HUBS_FXB_Li_BIT2_DATA_BYTE_SEL_OFF (11)
  #define HUBS_CR_VISA_XBAR_SABHUB2S_F_HUBS_FXB_Li_BIT2_DATA_BYTE_SEL_WID ( 1)
  #define HUBS_CR_VISA_XBAR_SABHUB2S_F_HUBS_FXB_Li_BIT2_DATA_BYTE_SEL_MSK (0x00000800)
  #define HUBS_CR_VISA_XBAR_SABHUB2S_F_HUBS_FXB_Li_BIT2_DATA_BYTE_SEL_MIN (0)
  #define HUBS_CR_VISA_XBAR_SABHUB2S_F_HUBS_FXB_Li_BIT2_DATA_BYTE_SEL_MAX (1) // 0x00000001
  #define HUBS_CR_VISA_XBAR_SABHUB2S_F_HUBS_FXB_Li_BIT2_DATA_BYTE_SEL_DEF (0x00000000)
  #define HUBS_CR_VISA_XBAR_SABHUB2S_F_HUBS_FXB_Li_BIT2_DATA_BYTE_SEL_HSH (0x010B717C)

  #define HUBS_CR_VISA_XBAR_SABHUB2S_F_HUBS_FXB_Li_BIT3_DATA_BIT_SEL_OFF (12)
  #define HUBS_CR_VISA_XBAR_SABHUB2S_F_HUBS_FXB_Li_BIT3_DATA_BIT_SEL_WID ( 3)
  #define HUBS_CR_VISA_XBAR_SABHUB2S_F_HUBS_FXB_Li_BIT3_DATA_BIT_SEL_MSK (0x00007000)
  #define HUBS_CR_VISA_XBAR_SABHUB2S_F_HUBS_FXB_Li_BIT3_DATA_BIT_SEL_MIN (0)
  #define HUBS_CR_VISA_XBAR_SABHUB2S_F_HUBS_FXB_Li_BIT3_DATA_BIT_SEL_MAX (7) // 0x00000007
  #define HUBS_CR_VISA_XBAR_SABHUB2S_F_HUBS_FXB_Li_BIT3_DATA_BIT_SEL_DEF (0x00000003)
  #define HUBS_CR_VISA_XBAR_SABHUB2S_F_HUBS_FXB_Li_BIT3_DATA_BIT_SEL_HSH (0x030C717C)

  #define HUBS_CR_VISA_XBAR_SABHUB2S_F_HUBS_FXB_Li_BIT3_DATA_BYTE_SEL_OFF (15)
  #define HUBS_CR_VISA_XBAR_SABHUB2S_F_HUBS_FXB_Li_BIT3_DATA_BYTE_SEL_WID ( 1)
  #define HUBS_CR_VISA_XBAR_SABHUB2S_F_HUBS_FXB_Li_BIT3_DATA_BYTE_SEL_MSK (0x00008000)
  #define HUBS_CR_VISA_XBAR_SABHUB2S_F_HUBS_FXB_Li_BIT3_DATA_BYTE_SEL_MIN (0)
  #define HUBS_CR_VISA_XBAR_SABHUB2S_F_HUBS_FXB_Li_BIT3_DATA_BYTE_SEL_MAX (1) // 0x00000001
  #define HUBS_CR_VISA_XBAR_SABHUB2S_F_HUBS_FXB_Li_BIT3_DATA_BYTE_SEL_DEF (0x00000000)
  #define HUBS_CR_VISA_XBAR_SABHUB2S_F_HUBS_FXB_Li_BIT3_DATA_BYTE_SEL_HSH (0x010F717C)

  #define HUBS_CR_VISA_XBAR_SABHUB2S_F_HUBS_FXB_Li_BIT4_DATA_BIT_SEL_OFF (16)
  #define HUBS_CR_VISA_XBAR_SABHUB2S_F_HUBS_FXB_Li_BIT4_DATA_BIT_SEL_WID ( 3)
  #define HUBS_CR_VISA_XBAR_SABHUB2S_F_HUBS_FXB_Li_BIT4_DATA_BIT_SEL_MSK (0x00070000)
  #define HUBS_CR_VISA_XBAR_SABHUB2S_F_HUBS_FXB_Li_BIT4_DATA_BIT_SEL_MIN (0)
  #define HUBS_CR_VISA_XBAR_SABHUB2S_F_HUBS_FXB_Li_BIT4_DATA_BIT_SEL_MAX (7) // 0x00000007
  #define HUBS_CR_VISA_XBAR_SABHUB2S_F_HUBS_FXB_Li_BIT4_DATA_BIT_SEL_DEF (0x00000004)
  #define HUBS_CR_VISA_XBAR_SABHUB2S_F_HUBS_FXB_Li_BIT4_DATA_BIT_SEL_HSH (0x0310717C)

  #define HUBS_CR_VISA_XBAR_SABHUB2S_F_HUBS_FXB_Li_BIT4_DATA_BYTE_SEL_OFF (19)
  #define HUBS_CR_VISA_XBAR_SABHUB2S_F_HUBS_FXB_Li_BIT4_DATA_BYTE_SEL_WID ( 1)
  #define HUBS_CR_VISA_XBAR_SABHUB2S_F_HUBS_FXB_Li_BIT4_DATA_BYTE_SEL_MSK (0x00080000)
  #define HUBS_CR_VISA_XBAR_SABHUB2S_F_HUBS_FXB_Li_BIT4_DATA_BYTE_SEL_MIN (0)
  #define HUBS_CR_VISA_XBAR_SABHUB2S_F_HUBS_FXB_Li_BIT4_DATA_BYTE_SEL_MAX (1) // 0x00000001
  #define HUBS_CR_VISA_XBAR_SABHUB2S_F_HUBS_FXB_Li_BIT4_DATA_BYTE_SEL_DEF (0x00000000)
  #define HUBS_CR_VISA_XBAR_SABHUB2S_F_HUBS_FXB_Li_BIT4_DATA_BYTE_SEL_HSH (0x0113717C)

  #define HUBS_CR_VISA_XBAR_SABHUB2S_F_HUBS_FXB_Li_BIT5_DATA_BIT_SEL_OFF (20)
  #define HUBS_CR_VISA_XBAR_SABHUB2S_F_HUBS_FXB_Li_BIT5_DATA_BIT_SEL_WID ( 3)
  #define HUBS_CR_VISA_XBAR_SABHUB2S_F_HUBS_FXB_Li_BIT5_DATA_BIT_SEL_MSK (0x00700000)
  #define HUBS_CR_VISA_XBAR_SABHUB2S_F_HUBS_FXB_Li_BIT5_DATA_BIT_SEL_MIN (0)
  #define HUBS_CR_VISA_XBAR_SABHUB2S_F_HUBS_FXB_Li_BIT5_DATA_BIT_SEL_MAX (7) // 0x00000007
  #define HUBS_CR_VISA_XBAR_SABHUB2S_F_HUBS_FXB_Li_BIT5_DATA_BIT_SEL_DEF (0x00000005)
  #define HUBS_CR_VISA_XBAR_SABHUB2S_F_HUBS_FXB_Li_BIT5_DATA_BIT_SEL_HSH (0x0314717C)

  #define HUBS_CR_VISA_XBAR_SABHUB2S_F_HUBS_FXB_Li_BIT5_DATA_BYTE_SEL_OFF (23)
  #define HUBS_CR_VISA_XBAR_SABHUB2S_F_HUBS_FXB_Li_BIT5_DATA_BYTE_SEL_WID ( 1)
  #define HUBS_CR_VISA_XBAR_SABHUB2S_F_HUBS_FXB_Li_BIT5_DATA_BYTE_SEL_MSK (0x00800000)
  #define HUBS_CR_VISA_XBAR_SABHUB2S_F_HUBS_FXB_Li_BIT5_DATA_BYTE_SEL_MIN (0)
  #define HUBS_CR_VISA_XBAR_SABHUB2S_F_HUBS_FXB_Li_BIT5_DATA_BYTE_SEL_MAX (1) // 0x00000001
  #define HUBS_CR_VISA_XBAR_SABHUB2S_F_HUBS_FXB_Li_BIT5_DATA_BYTE_SEL_DEF (0x00000000)
  #define HUBS_CR_VISA_XBAR_SABHUB2S_F_HUBS_FXB_Li_BIT5_DATA_BYTE_SEL_HSH (0x0117717C)

  #define HUBS_CR_VISA_XBAR_SABHUB2S_F_HUBS_FXB_Li_BIT6_DATA_BIT_SEL_OFF (24)
  #define HUBS_CR_VISA_XBAR_SABHUB2S_F_HUBS_FXB_Li_BIT6_DATA_BIT_SEL_WID ( 3)
  #define HUBS_CR_VISA_XBAR_SABHUB2S_F_HUBS_FXB_Li_BIT6_DATA_BIT_SEL_MSK (0x07000000)
  #define HUBS_CR_VISA_XBAR_SABHUB2S_F_HUBS_FXB_Li_BIT6_DATA_BIT_SEL_MIN (0)
  #define HUBS_CR_VISA_XBAR_SABHUB2S_F_HUBS_FXB_Li_BIT6_DATA_BIT_SEL_MAX (7) // 0x00000007
  #define HUBS_CR_VISA_XBAR_SABHUB2S_F_HUBS_FXB_Li_BIT6_DATA_BIT_SEL_DEF (0x00000006)
  #define HUBS_CR_VISA_XBAR_SABHUB2S_F_HUBS_FXB_Li_BIT6_DATA_BIT_SEL_HSH (0x0318717C)

  #define HUBS_CR_VISA_XBAR_SABHUB2S_F_HUBS_FXB_Li_BIT6_DATA_BYTE_SEL_OFF (27)
  #define HUBS_CR_VISA_XBAR_SABHUB2S_F_HUBS_FXB_Li_BIT6_DATA_BYTE_SEL_WID ( 1)
  #define HUBS_CR_VISA_XBAR_SABHUB2S_F_HUBS_FXB_Li_BIT6_DATA_BYTE_SEL_MSK (0x08000000)
  #define HUBS_CR_VISA_XBAR_SABHUB2S_F_HUBS_FXB_Li_BIT6_DATA_BYTE_SEL_MIN (0)
  #define HUBS_CR_VISA_XBAR_SABHUB2S_F_HUBS_FXB_Li_BIT6_DATA_BYTE_SEL_MAX (1) // 0x00000001
  #define HUBS_CR_VISA_XBAR_SABHUB2S_F_HUBS_FXB_Li_BIT6_DATA_BYTE_SEL_DEF (0x00000000)
  #define HUBS_CR_VISA_XBAR_SABHUB2S_F_HUBS_FXB_Li_BIT6_DATA_BYTE_SEL_HSH (0x011B717C)

  #define HUBS_CR_VISA_XBAR_SABHUB2S_F_HUBS_FXB_Li_BIT7_DATA_BIT_SEL_OFF (28)
  #define HUBS_CR_VISA_XBAR_SABHUB2S_F_HUBS_FXB_Li_BIT7_DATA_BIT_SEL_WID ( 3)
  #define HUBS_CR_VISA_XBAR_SABHUB2S_F_HUBS_FXB_Li_BIT7_DATA_BIT_SEL_MSK (0x70000000)
  #define HUBS_CR_VISA_XBAR_SABHUB2S_F_HUBS_FXB_Li_BIT7_DATA_BIT_SEL_MIN (0)
  #define HUBS_CR_VISA_XBAR_SABHUB2S_F_HUBS_FXB_Li_BIT7_DATA_BIT_SEL_MAX (7) // 0x00000007
  #define HUBS_CR_VISA_XBAR_SABHUB2S_F_HUBS_FXB_Li_BIT7_DATA_BIT_SEL_DEF (0x00000007)
  #define HUBS_CR_VISA_XBAR_SABHUB2S_F_HUBS_FXB_Li_BIT7_DATA_BIT_SEL_HSH (0x031C717C)

  #define HUBS_CR_VISA_XBAR_SABHUB2S_F_HUBS_FXB_Li_BIT7_DATA_BYTE_SEL_OFF (31)
  #define HUBS_CR_VISA_XBAR_SABHUB2S_F_HUBS_FXB_Li_BIT7_DATA_BYTE_SEL_WID ( 1)
  #define HUBS_CR_VISA_XBAR_SABHUB2S_F_HUBS_FXB_Li_BIT7_DATA_BYTE_SEL_MSK (0x80000000)
  #define HUBS_CR_VISA_XBAR_SABHUB2S_F_HUBS_FXB_Li_BIT7_DATA_BYTE_SEL_MIN (0)
  #define HUBS_CR_VISA_XBAR_SABHUB2S_F_HUBS_FXB_Li_BIT7_DATA_BYTE_SEL_MAX (1) // 0x00000001
  #define HUBS_CR_VISA_XBAR_SABHUB2S_F_HUBS_FXB_Li_BIT7_DATA_BYTE_SEL_DEF (0x00000000)
  #define HUBS_CR_VISA_XBAR_SABHUB2S_F_HUBS_FXB_Li_BIT7_DATA_BYTE_SEL_HSH (0x011F717C)

#define HUBS_CR_VISA_XBAR_SABHUB0S_L_HUBS_REG                          (0x00007180)

  #define HUBS_CR_VISA_XBAR_SABHUB0S_L_HUBS_FXB_Li_BIT0_DATA_BIT_SEL_OFF ( 0)
  #define HUBS_CR_VISA_XBAR_SABHUB0S_L_HUBS_FXB_Li_BIT0_DATA_BIT_SEL_WID ( 3)
  #define HUBS_CR_VISA_XBAR_SABHUB0S_L_HUBS_FXB_Li_BIT0_DATA_BIT_SEL_MSK (0x00000007)
  #define HUBS_CR_VISA_XBAR_SABHUB0S_L_HUBS_FXB_Li_BIT0_DATA_BIT_SEL_MIN (0)
  #define HUBS_CR_VISA_XBAR_SABHUB0S_L_HUBS_FXB_Li_BIT0_DATA_BIT_SEL_MAX (7) // 0x00000007
  #define HUBS_CR_VISA_XBAR_SABHUB0S_L_HUBS_FXB_Li_BIT0_DATA_BIT_SEL_DEF (0x00000000)
  #define HUBS_CR_VISA_XBAR_SABHUB0S_L_HUBS_FXB_Li_BIT0_DATA_BIT_SEL_HSH (0x03007180)

  #define HUBS_CR_VISA_XBAR_SABHUB0S_L_HUBS_FXB_Li_BIT0_DATA_BYTE_SEL_OFF ( 3)
  #define HUBS_CR_VISA_XBAR_SABHUB0S_L_HUBS_FXB_Li_BIT0_DATA_BYTE_SEL_WID ( 1)
  #define HUBS_CR_VISA_XBAR_SABHUB0S_L_HUBS_FXB_Li_BIT0_DATA_BYTE_SEL_MSK (0x00000008)
  #define HUBS_CR_VISA_XBAR_SABHUB0S_L_HUBS_FXB_Li_BIT0_DATA_BYTE_SEL_MIN (0)
  #define HUBS_CR_VISA_XBAR_SABHUB0S_L_HUBS_FXB_Li_BIT0_DATA_BYTE_SEL_MAX (1) // 0x00000001
  #define HUBS_CR_VISA_XBAR_SABHUB0S_L_HUBS_FXB_Li_BIT0_DATA_BYTE_SEL_DEF (0x00000000)
  #define HUBS_CR_VISA_XBAR_SABHUB0S_L_HUBS_FXB_Li_BIT0_DATA_BYTE_SEL_HSH (0x01037180)

  #define HUBS_CR_VISA_XBAR_SABHUB0S_L_HUBS_FXB_Li_BIT1_DATA_BIT_SEL_OFF ( 4)
  #define HUBS_CR_VISA_XBAR_SABHUB0S_L_HUBS_FXB_Li_BIT1_DATA_BIT_SEL_WID ( 3)
  #define HUBS_CR_VISA_XBAR_SABHUB0S_L_HUBS_FXB_Li_BIT1_DATA_BIT_SEL_MSK (0x00000070)
  #define HUBS_CR_VISA_XBAR_SABHUB0S_L_HUBS_FXB_Li_BIT1_DATA_BIT_SEL_MIN (0)
  #define HUBS_CR_VISA_XBAR_SABHUB0S_L_HUBS_FXB_Li_BIT1_DATA_BIT_SEL_MAX (7) // 0x00000007
  #define HUBS_CR_VISA_XBAR_SABHUB0S_L_HUBS_FXB_Li_BIT1_DATA_BIT_SEL_DEF (0x00000001)
  #define HUBS_CR_VISA_XBAR_SABHUB0S_L_HUBS_FXB_Li_BIT1_DATA_BIT_SEL_HSH (0x03047180)

  #define HUBS_CR_VISA_XBAR_SABHUB0S_L_HUBS_FXB_Li_BIT1_DATA_BYTE_SEL_OFF ( 7)
  #define HUBS_CR_VISA_XBAR_SABHUB0S_L_HUBS_FXB_Li_BIT1_DATA_BYTE_SEL_WID ( 1)
  #define HUBS_CR_VISA_XBAR_SABHUB0S_L_HUBS_FXB_Li_BIT1_DATA_BYTE_SEL_MSK (0x00000080)
  #define HUBS_CR_VISA_XBAR_SABHUB0S_L_HUBS_FXB_Li_BIT1_DATA_BYTE_SEL_MIN (0)
  #define HUBS_CR_VISA_XBAR_SABHUB0S_L_HUBS_FXB_Li_BIT1_DATA_BYTE_SEL_MAX (1) // 0x00000001
  #define HUBS_CR_VISA_XBAR_SABHUB0S_L_HUBS_FXB_Li_BIT1_DATA_BYTE_SEL_DEF (0x00000000)
  #define HUBS_CR_VISA_XBAR_SABHUB0S_L_HUBS_FXB_Li_BIT1_DATA_BYTE_SEL_HSH (0x01077180)

  #define HUBS_CR_VISA_XBAR_SABHUB0S_L_HUBS_FXB_Li_BIT2_DATA_BIT_SEL_OFF ( 8)
  #define HUBS_CR_VISA_XBAR_SABHUB0S_L_HUBS_FXB_Li_BIT2_DATA_BIT_SEL_WID ( 3)
  #define HUBS_CR_VISA_XBAR_SABHUB0S_L_HUBS_FXB_Li_BIT2_DATA_BIT_SEL_MSK (0x00000700)
  #define HUBS_CR_VISA_XBAR_SABHUB0S_L_HUBS_FXB_Li_BIT2_DATA_BIT_SEL_MIN (0)
  #define HUBS_CR_VISA_XBAR_SABHUB0S_L_HUBS_FXB_Li_BIT2_DATA_BIT_SEL_MAX (7) // 0x00000007
  #define HUBS_CR_VISA_XBAR_SABHUB0S_L_HUBS_FXB_Li_BIT2_DATA_BIT_SEL_DEF (0x00000002)
  #define HUBS_CR_VISA_XBAR_SABHUB0S_L_HUBS_FXB_Li_BIT2_DATA_BIT_SEL_HSH (0x03087180)

  #define HUBS_CR_VISA_XBAR_SABHUB0S_L_HUBS_FXB_Li_BIT2_DATA_BYTE_SEL_OFF (11)
  #define HUBS_CR_VISA_XBAR_SABHUB0S_L_HUBS_FXB_Li_BIT2_DATA_BYTE_SEL_WID ( 1)
  #define HUBS_CR_VISA_XBAR_SABHUB0S_L_HUBS_FXB_Li_BIT2_DATA_BYTE_SEL_MSK (0x00000800)
  #define HUBS_CR_VISA_XBAR_SABHUB0S_L_HUBS_FXB_Li_BIT2_DATA_BYTE_SEL_MIN (0)
  #define HUBS_CR_VISA_XBAR_SABHUB0S_L_HUBS_FXB_Li_BIT2_DATA_BYTE_SEL_MAX (1) // 0x00000001
  #define HUBS_CR_VISA_XBAR_SABHUB0S_L_HUBS_FXB_Li_BIT2_DATA_BYTE_SEL_DEF (0x00000000)
  #define HUBS_CR_VISA_XBAR_SABHUB0S_L_HUBS_FXB_Li_BIT2_DATA_BYTE_SEL_HSH (0x010B7180)

  #define HUBS_CR_VISA_XBAR_SABHUB0S_L_HUBS_FXB_Li_BIT3_DATA_BIT_SEL_OFF (12)
  #define HUBS_CR_VISA_XBAR_SABHUB0S_L_HUBS_FXB_Li_BIT3_DATA_BIT_SEL_WID ( 3)
  #define HUBS_CR_VISA_XBAR_SABHUB0S_L_HUBS_FXB_Li_BIT3_DATA_BIT_SEL_MSK (0x00007000)
  #define HUBS_CR_VISA_XBAR_SABHUB0S_L_HUBS_FXB_Li_BIT3_DATA_BIT_SEL_MIN (0)
  #define HUBS_CR_VISA_XBAR_SABHUB0S_L_HUBS_FXB_Li_BIT3_DATA_BIT_SEL_MAX (7) // 0x00000007
  #define HUBS_CR_VISA_XBAR_SABHUB0S_L_HUBS_FXB_Li_BIT3_DATA_BIT_SEL_DEF (0x00000003)
  #define HUBS_CR_VISA_XBAR_SABHUB0S_L_HUBS_FXB_Li_BIT3_DATA_BIT_SEL_HSH (0x030C7180)

  #define HUBS_CR_VISA_XBAR_SABHUB0S_L_HUBS_FXB_Li_BIT3_DATA_BYTE_SEL_OFF (15)
  #define HUBS_CR_VISA_XBAR_SABHUB0S_L_HUBS_FXB_Li_BIT3_DATA_BYTE_SEL_WID ( 1)
  #define HUBS_CR_VISA_XBAR_SABHUB0S_L_HUBS_FXB_Li_BIT3_DATA_BYTE_SEL_MSK (0x00008000)
  #define HUBS_CR_VISA_XBAR_SABHUB0S_L_HUBS_FXB_Li_BIT3_DATA_BYTE_SEL_MIN (0)
  #define HUBS_CR_VISA_XBAR_SABHUB0S_L_HUBS_FXB_Li_BIT3_DATA_BYTE_SEL_MAX (1) // 0x00000001
  #define HUBS_CR_VISA_XBAR_SABHUB0S_L_HUBS_FXB_Li_BIT3_DATA_BYTE_SEL_DEF (0x00000000)
  #define HUBS_CR_VISA_XBAR_SABHUB0S_L_HUBS_FXB_Li_BIT3_DATA_BYTE_SEL_HSH (0x010F7180)

  #define HUBS_CR_VISA_XBAR_SABHUB0S_L_HUBS_FXB_Li_BIT4_DATA_BIT_SEL_OFF (16)
  #define HUBS_CR_VISA_XBAR_SABHUB0S_L_HUBS_FXB_Li_BIT4_DATA_BIT_SEL_WID ( 3)
  #define HUBS_CR_VISA_XBAR_SABHUB0S_L_HUBS_FXB_Li_BIT4_DATA_BIT_SEL_MSK (0x00070000)
  #define HUBS_CR_VISA_XBAR_SABHUB0S_L_HUBS_FXB_Li_BIT4_DATA_BIT_SEL_MIN (0)
  #define HUBS_CR_VISA_XBAR_SABHUB0S_L_HUBS_FXB_Li_BIT4_DATA_BIT_SEL_MAX (7) // 0x00000007
  #define HUBS_CR_VISA_XBAR_SABHUB0S_L_HUBS_FXB_Li_BIT4_DATA_BIT_SEL_DEF (0x00000004)
  #define HUBS_CR_VISA_XBAR_SABHUB0S_L_HUBS_FXB_Li_BIT4_DATA_BIT_SEL_HSH (0x03107180)

  #define HUBS_CR_VISA_XBAR_SABHUB0S_L_HUBS_FXB_Li_BIT4_DATA_BYTE_SEL_OFF (19)
  #define HUBS_CR_VISA_XBAR_SABHUB0S_L_HUBS_FXB_Li_BIT4_DATA_BYTE_SEL_WID ( 1)
  #define HUBS_CR_VISA_XBAR_SABHUB0S_L_HUBS_FXB_Li_BIT4_DATA_BYTE_SEL_MSK (0x00080000)
  #define HUBS_CR_VISA_XBAR_SABHUB0S_L_HUBS_FXB_Li_BIT4_DATA_BYTE_SEL_MIN (0)
  #define HUBS_CR_VISA_XBAR_SABHUB0S_L_HUBS_FXB_Li_BIT4_DATA_BYTE_SEL_MAX (1) // 0x00000001
  #define HUBS_CR_VISA_XBAR_SABHUB0S_L_HUBS_FXB_Li_BIT4_DATA_BYTE_SEL_DEF (0x00000000)
  #define HUBS_CR_VISA_XBAR_SABHUB0S_L_HUBS_FXB_Li_BIT4_DATA_BYTE_SEL_HSH (0x01137180)

  #define HUBS_CR_VISA_XBAR_SABHUB0S_L_HUBS_FXB_Li_BIT5_DATA_BIT_SEL_OFF (20)
  #define HUBS_CR_VISA_XBAR_SABHUB0S_L_HUBS_FXB_Li_BIT5_DATA_BIT_SEL_WID ( 3)
  #define HUBS_CR_VISA_XBAR_SABHUB0S_L_HUBS_FXB_Li_BIT5_DATA_BIT_SEL_MSK (0x00700000)
  #define HUBS_CR_VISA_XBAR_SABHUB0S_L_HUBS_FXB_Li_BIT5_DATA_BIT_SEL_MIN (0)
  #define HUBS_CR_VISA_XBAR_SABHUB0S_L_HUBS_FXB_Li_BIT5_DATA_BIT_SEL_MAX (7) // 0x00000007
  #define HUBS_CR_VISA_XBAR_SABHUB0S_L_HUBS_FXB_Li_BIT5_DATA_BIT_SEL_DEF (0x00000005)
  #define HUBS_CR_VISA_XBAR_SABHUB0S_L_HUBS_FXB_Li_BIT5_DATA_BIT_SEL_HSH (0x03147180)

  #define HUBS_CR_VISA_XBAR_SABHUB0S_L_HUBS_FXB_Li_BIT5_DATA_BYTE_SEL_OFF (23)
  #define HUBS_CR_VISA_XBAR_SABHUB0S_L_HUBS_FXB_Li_BIT5_DATA_BYTE_SEL_WID ( 1)
  #define HUBS_CR_VISA_XBAR_SABHUB0S_L_HUBS_FXB_Li_BIT5_DATA_BYTE_SEL_MSK (0x00800000)
  #define HUBS_CR_VISA_XBAR_SABHUB0S_L_HUBS_FXB_Li_BIT5_DATA_BYTE_SEL_MIN (0)
  #define HUBS_CR_VISA_XBAR_SABHUB0S_L_HUBS_FXB_Li_BIT5_DATA_BYTE_SEL_MAX (1) // 0x00000001
  #define HUBS_CR_VISA_XBAR_SABHUB0S_L_HUBS_FXB_Li_BIT5_DATA_BYTE_SEL_DEF (0x00000000)
  #define HUBS_CR_VISA_XBAR_SABHUB0S_L_HUBS_FXB_Li_BIT5_DATA_BYTE_SEL_HSH (0x01177180)

  #define HUBS_CR_VISA_XBAR_SABHUB0S_L_HUBS_FXB_Li_BIT6_DATA_BIT_SEL_OFF (24)
  #define HUBS_CR_VISA_XBAR_SABHUB0S_L_HUBS_FXB_Li_BIT6_DATA_BIT_SEL_WID ( 3)
  #define HUBS_CR_VISA_XBAR_SABHUB0S_L_HUBS_FXB_Li_BIT6_DATA_BIT_SEL_MSK (0x07000000)
  #define HUBS_CR_VISA_XBAR_SABHUB0S_L_HUBS_FXB_Li_BIT6_DATA_BIT_SEL_MIN (0)
  #define HUBS_CR_VISA_XBAR_SABHUB0S_L_HUBS_FXB_Li_BIT6_DATA_BIT_SEL_MAX (7) // 0x00000007
  #define HUBS_CR_VISA_XBAR_SABHUB0S_L_HUBS_FXB_Li_BIT6_DATA_BIT_SEL_DEF (0x00000006)
  #define HUBS_CR_VISA_XBAR_SABHUB0S_L_HUBS_FXB_Li_BIT6_DATA_BIT_SEL_HSH (0x03187180)

  #define HUBS_CR_VISA_XBAR_SABHUB0S_L_HUBS_FXB_Li_BIT6_DATA_BYTE_SEL_OFF (27)
  #define HUBS_CR_VISA_XBAR_SABHUB0S_L_HUBS_FXB_Li_BIT6_DATA_BYTE_SEL_WID ( 1)
  #define HUBS_CR_VISA_XBAR_SABHUB0S_L_HUBS_FXB_Li_BIT6_DATA_BYTE_SEL_MSK (0x08000000)
  #define HUBS_CR_VISA_XBAR_SABHUB0S_L_HUBS_FXB_Li_BIT6_DATA_BYTE_SEL_MIN (0)
  #define HUBS_CR_VISA_XBAR_SABHUB0S_L_HUBS_FXB_Li_BIT6_DATA_BYTE_SEL_MAX (1) // 0x00000001
  #define HUBS_CR_VISA_XBAR_SABHUB0S_L_HUBS_FXB_Li_BIT6_DATA_BYTE_SEL_DEF (0x00000000)
  #define HUBS_CR_VISA_XBAR_SABHUB0S_L_HUBS_FXB_Li_BIT6_DATA_BYTE_SEL_HSH (0x011B7180)

  #define HUBS_CR_VISA_XBAR_SABHUB0S_L_HUBS_FXB_Li_BIT7_DATA_BIT_SEL_OFF (28)
  #define HUBS_CR_VISA_XBAR_SABHUB0S_L_HUBS_FXB_Li_BIT7_DATA_BIT_SEL_WID ( 3)
  #define HUBS_CR_VISA_XBAR_SABHUB0S_L_HUBS_FXB_Li_BIT7_DATA_BIT_SEL_MSK (0x70000000)
  #define HUBS_CR_VISA_XBAR_SABHUB0S_L_HUBS_FXB_Li_BIT7_DATA_BIT_SEL_MIN (0)
  #define HUBS_CR_VISA_XBAR_SABHUB0S_L_HUBS_FXB_Li_BIT7_DATA_BIT_SEL_MAX (7) // 0x00000007
  #define HUBS_CR_VISA_XBAR_SABHUB0S_L_HUBS_FXB_Li_BIT7_DATA_BIT_SEL_DEF (0x00000007)
  #define HUBS_CR_VISA_XBAR_SABHUB0S_L_HUBS_FXB_Li_BIT7_DATA_BIT_SEL_HSH (0x031C7180)

  #define HUBS_CR_VISA_XBAR_SABHUB0S_L_HUBS_FXB_Li_BIT7_DATA_BYTE_SEL_OFF (31)
  #define HUBS_CR_VISA_XBAR_SABHUB0S_L_HUBS_FXB_Li_BIT7_DATA_BYTE_SEL_WID ( 1)
  #define HUBS_CR_VISA_XBAR_SABHUB0S_L_HUBS_FXB_Li_BIT7_DATA_BYTE_SEL_MSK (0x80000000)
  #define HUBS_CR_VISA_XBAR_SABHUB0S_L_HUBS_FXB_Li_BIT7_DATA_BYTE_SEL_MIN (0)
  #define HUBS_CR_VISA_XBAR_SABHUB0S_L_HUBS_FXB_Li_BIT7_DATA_BYTE_SEL_MAX (1) // 0x00000001
  #define HUBS_CR_VISA_XBAR_SABHUB0S_L_HUBS_FXB_Li_BIT7_DATA_BYTE_SEL_DEF (0x00000000)
  #define HUBS_CR_VISA_XBAR_SABHUB0S_L_HUBS_FXB_Li_BIT7_DATA_BYTE_SEL_HSH (0x011F7180)

#define HUBS_CR_VISA_XBAR_SABHUB1S_L_HUBS_REG                          (0x00007184)

  #define HUBS_CR_VISA_XBAR_SABHUB1S_L_HUBS_FXB_Li_BIT0_DATA_BIT_SEL_OFF ( 0)
  #define HUBS_CR_VISA_XBAR_SABHUB1S_L_HUBS_FXB_Li_BIT0_DATA_BIT_SEL_WID ( 3)
  #define HUBS_CR_VISA_XBAR_SABHUB1S_L_HUBS_FXB_Li_BIT0_DATA_BIT_SEL_MSK (0x00000007)
  #define HUBS_CR_VISA_XBAR_SABHUB1S_L_HUBS_FXB_Li_BIT0_DATA_BIT_SEL_MIN (0)
  #define HUBS_CR_VISA_XBAR_SABHUB1S_L_HUBS_FXB_Li_BIT0_DATA_BIT_SEL_MAX (7) // 0x00000007
  #define HUBS_CR_VISA_XBAR_SABHUB1S_L_HUBS_FXB_Li_BIT0_DATA_BIT_SEL_DEF (0x00000000)
  #define HUBS_CR_VISA_XBAR_SABHUB1S_L_HUBS_FXB_Li_BIT0_DATA_BIT_SEL_HSH (0x03007184)

  #define HUBS_CR_VISA_XBAR_SABHUB1S_L_HUBS_FXB_Li_BIT0_DATA_BYTE_SEL_OFF ( 3)
  #define HUBS_CR_VISA_XBAR_SABHUB1S_L_HUBS_FXB_Li_BIT0_DATA_BYTE_SEL_WID ( 1)
  #define HUBS_CR_VISA_XBAR_SABHUB1S_L_HUBS_FXB_Li_BIT0_DATA_BYTE_SEL_MSK (0x00000008)
  #define HUBS_CR_VISA_XBAR_SABHUB1S_L_HUBS_FXB_Li_BIT0_DATA_BYTE_SEL_MIN (0)
  #define HUBS_CR_VISA_XBAR_SABHUB1S_L_HUBS_FXB_Li_BIT0_DATA_BYTE_SEL_MAX (1) // 0x00000001
  #define HUBS_CR_VISA_XBAR_SABHUB1S_L_HUBS_FXB_Li_BIT0_DATA_BYTE_SEL_DEF (0x00000000)
  #define HUBS_CR_VISA_XBAR_SABHUB1S_L_HUBS_FXB_Li_BIT0_DATA_BYTE_SEL_HSH (0x01037184)

  #define HUBS_CR_VISA_XBAR_SABHUB1S_L_HUBS_FXB_Li_BIT1_DATA_BIT_SEL_OFF ( 4)
  #define HUBS_CR_VISA_XBAR_SABHUB1S_L_HUBS_FXB_Li_BIT1_DATA_BIT_SEL_WID ( 3)
  #define HUBS_CR_VISA_XBAR_SABHUB1S_L_HUBS_FXB_Li_BIT1_DATA_BIT_SEL_MSK (0x00000070)
  #define HUBS_CR_VISA_XBAR_SABHUB1S_L_HUBS_FXB_Li_BIT1_DATA_BIT_SEL_MIN (0)
  #define HUBS_CR_VISA_XBAR_SABHUB1S_L_HUBS_FXB_Li_BIT1_DATA_BIT_SEL_MAX (7) // 0x00000007
  #define HUBS_CR_VISA_XBAR_SABHUB1S_L_HUBS_FXB_Li_BIT1_DATA_BIT_SEL_DEF (0x00000001)
  #define HUBS_CR_VISA_XBAR_SABHUB1S_L_HUBS_FXB_Li_BIT1_DATA_BIT_SEL_HSH (0x03047184)

  #define HUBS_CR_VISA_XBAR_SABHUB1S_L_HUBS_FXB_Li_BIT1_DATA_BYTE_SEL_OFF ( 7)
  #define HUBS_CR_VISA_XBAR_SABHUB1S_L_HUBS_FXB_Li_BIT1_DATA_BYTE_SEL_WID ( 1)
  #define HUBS_CR_VISA_XBAR_SABHUB1S_L_HUBS_FXB_Li_BIT1_DATA_BYTE_SEL_MSK (0x00000080)
  #define HUBS_CR_VISA_XBAR_SABHUB1S_L_HUBS_FXB_Li_BIT1_DATA_BYTE_SEL_MIN (0)
  #define HUBS_CR_VISA_XBAR_SABHUB1S_L_HUBS_FXB_Li_BIT1_DATA_BYTE_SEL_MAX (1) // 0x00000001
  #define HUBS_CR_VISA_XBAR_SABHUB1S_L_HUBS_FXB_Li_BIT1_DATA_BYTE_SEL_DEF (0x00000000)
  #define HUBS_CR_VISA_XBAR_SABHUB1S_L_HUBS_FXB_Li_BIT1_DATA_BYTE_SEL_HSH (0x01077184)

  #define HUBS_CR_VISA_XBAR_SABHUB1S_L_HUBS_FXB_Li_BIT2_DATA_BIT_SEL_OFF ( 8)
  #define HUBS_CR_VISA_XBAR_SABHUB1S_L_HUBS_FXB_Li_BIT2_DATA_BIT_SEL_WID ( 3)
  #define HUBS_CR_VISA_XBAR_SABHUB1S_L_HUBS_FXB_Li_BIT2_DATA_BIT_SEL_MSK (0x00000700)
  #define HUBS_CR_VISA_XBAR_SABHUB1S_L_HUBS_FXB_Li_BIT2_DATA_BIT_SEL_MIN (0)
  #define HUBS_CR_VISA_XBAR_SABHUB1S_L_HUBS_FXB_Li_BIT2_DATA_BIT_SEL_MAX (7) // 0x00000007
  #define HUBS_CR_VISA_XBAR_SABHUB1S_L_HUBS_FXB_Li_BIT2_DATA_BIT_SEL_DEF (0x00000002)
  #define HUBS_CR_VISA_XBAR_SABHUB1S_L_HUBS_FXB_Li_BIT2_DATA_BIT_SEL_HSH (0x03087184)

  #define HUBS_CR_VISA_XBAR_SABHUB1S_L_HUBS_FXB_Li_BIT2_DATA_BYTE_SEL_OFF (11)
  #define HUBS_CR_VISA_XBAR_SABHUB1S_L_HUBS_FXB_Li_BIT2_DATA_BYTE_SEL_WID ( 1)
  #define HUBS_CR_VISA_XBAR_SABHUB1S_L_HUBS_FXB_Li_BIT2_DATA_BYTE_SEL_MSK (0x00000800)
  #define HUBS_CR_VISA_XBAR_SABHUB1S_L_HUBS_FXB_Li_BIT2_DATA_BYTE_SEL_MIN (0)
  #define HUBS_CR_VISA_XBAR_SABHUB1S_L_HUBS_FXB_Li_BIT2_DATA_BYTE_SEL_MAX (1) // 0x00000001
  #define HUBS_CR_VISA_XBAR_SABHUB1S_L_HUBS_FXB_Li_BIT2_DATA_BYTE_SEL_DEF (0x00000000)
  #define HUBS_CR_VISA_XBAR_SABHUB1S_L_HUBS_FXB_Li_BIT2_DATA_BYTE_SEL_HSH (0x010B7184)

  #define HUBS_CR_VISA_XBAR_SABHUB1S_L_HUBS_FXB_Li_BIT3_DATA_BIT_SEL_OFF (12)
  #define HUBS_CR_VISA_XBAR_SABHUB1S_L_HUBS_FXB_Li_BIT3_DATA_BIT_SEL_WID ( 3)
  #define HUBS_CR_VISA_XBAR_SABHUB1S_L_HUBS_FXB_Li_BIT3_DATA_BIT_SEL_MSK (0x00007000)
  #define HUBS_CR_VISA_XBAR_SABHUB1S_L_HUBS_FXB_Li_BIT3_DATA_BIT_SEL_MIN (0)
  #define HUBS_CR_VISA_XBAR_SABHUB1S_L_HUBS_FXB_Li_BIT3_DATA_BIT_SEL_MAX (7) // 0x00000007
  #define HUBS_CR_VISA_XBAR_SABHUB1S_L_HUBS_FXB_Li_BIT3_DATA_BIT_SEL_DEF (0x00000003)
  #define HUBS_CR_VISA_XBAR_SABHUB1S_L_HUBS_FXB_Li_BIT3_DATA_BIT_SEL_HSH (0x030C7184)

  #define HUBS_CR_VISA_XBAR_SABHUB1S_L_HUBS_FXB_Li_BIT3_DATA_BYTE_SEL_OFF (15)
  #define HUBS_CR_VISA_XBAR_SABHUB1S_L_HUBS_FXB_Li_BIT3_DATA_BYTE_SEL_WID ( 1)
  #define HUBS_CR_VISA_XBAR_SABHUB1S_L_HUBS_FXB_Li_BIT3_DATA_BYTE_SEL_MSK (0x00008000)
  #define HUBS_CR_VISA_XBAR_SABHUB1S_L_HUBS_FXB_Li_BIT3_DATA_BYTE_SEL_MIN (0)
  #define HUBS_CR_VISA_XBAR_SABHUB1S_L_HUBS_FXB_Li_BIT3_DATA_BYTE_SEL_MAX (1) // 0x00000001
  #define HUBS_CR_VISA_XBAR_SABHUB1S_L_HUBS_FXB_Li_BIT3_DATA_BYTE_SEL_DEF (0x00000000)
  #define HUBS_CR_VISA_XBAR_SABHUB1S_L_HUBS_FXB_Li_BIT3_DATA_BYTE_SEL_HSH (0x010F7184)

  #define HUBS_CR_VISA_XBAR_SABHUB1S_L_HUBS_FXB_Li_BIT4_DATA_BIT_SEL_OFF (16)
  #define HUBS_CR_VISA_XBAR_SABHUB1S_L_HUBS_FXB_Li_BIT4_DATA_BIT_SEL_WID ( 3)
  #define HUBS_CR_VISA_XBAR_SABHUB1S_L_HUBS_FXB_Li_BIT4_DATA_BIT_SEL_MSK (0x00070000)
  #define HUBS_CR_VISA_XBAR_SABHUB1S_L_HUBS_FXB_Li_BIT4_DATA_BIT_SEL_MIN (0)
  #define HUBS_CR_VISA_XBAR_SABHUB1S_L_HUBS_FXB_Li_BIT4_DATA_BIT_SEL_MAX (7) // 0x00000007
  #define HUBS_CR_VISA_XBAR_SABHUB1S_L_HUBS_FXB_Li_BIT4_DATA_BIT_SEL_DEF (0x00000004)
  #define HUBS_CR_VISA_XBAR_SABHUB1S_L_HUBS_FXB_Li_BIT4_DATA_BIT_SEL_HSH (0x03107184)

  #define HUBS_CR_VISA_XBAR_SABHUB1S_L_HUBS_FXB_Li_BIT4_DATA_BYTE_SEL_OFF (19)
  #define HUBS_CR_VISA_XBAR_SABHUB1S_L_HUBS_FXB_Li_BIT4_DATA_BYTE_SEL_WID ( 1)
  #define HUBS_CR_VISA_XBAR_SABHUB1S_L_HUBS_FXB_Li_BIT4_DATA_BYTE_SEL_MSK (0x00080000)
  #define HUBS_CR_VISA_XBAR_SABHUB1S_L_HUBS_FXB_Li_BIT4_DATA_BYTE_SEL_MIN (0)
  #define HUBS_CR_VISA_XBAR_SABHUB1S_L_HUBS_FXB_Li_BIT4_DATA_BYTE_SEL_MAX (1) // 0x00000001
  #define HUBS_CR_VISA_XBAR_SABHUB1S_L_HUBS_FXB_Li_BIT4_DATA_BYTE_SEL_DEF (0x00000000)
  #define HUBS_CR_VISA_XBAR_SABHUB1S_L_HUBS_FXB_Li_BIT4_DATA_BYTE_SEL_HSH (0x01137184)

  #define HUBS_CR_VISA_XBAR_SABHUB1S_L_HUBS_FXB_Li_BIT5_DATA_BIT_SEL_OFF (20)
  #define HUBS_CR_VISA_XBAR_SABHUB1S_L_HUBS_FXB_Li_BIT5_DATA_BIT_SEL_WID ( 3)
  #define HUBS_CR_VISA_XBAR_SABHUB1S_L_HUBS_FXB_Li_BIT5_DATA_BIT_SEL_MSK (0x00700000)
  #define HUBS_CR_VISA_XBAR_SABHUB1S_L_HUBS_FXB_Li_BIT5_DATA_BIT_SEL_MIN (0)
  #define HUBS_CR_VISA_XBAR_SABHUB1S_L_HUBS_FXB_Li_BIT5_DATA_BIT_SEL_MAX (7) // 0x00000007
  #define HUBS_CR_VISA_XBAR_SABHUB1S_L_HUBS_FXB_Li_BIT5_DATA_BIT_SEL_DEF (0x00000005)
  #define HUBS_CR_VISA_XBAR_SABHUB1S_L_HUBS_FXB_Li_BIT5_DATA_BIT_SEL_HSH (0x03147184)

  #define HUBS_CR_VISA_XBAR_SABHUB1S_L_HUBS_FXB_Li_BIT5_DATA_BYTE_SEL_OFF (23)
  #define HUBS_CR_VISA_XBAR_SABHUB1S_L_HUBS_FXB_Li_BIT5_DATA_BYTE_SEL_WID ( 1)
  #define HUBS_CR_VISA_XBAR_SABHUB1S_L_HUBS_FXB_Li_BIT5_DATA_BYTE_SEL_MSK (0x00800000)
  #define HUBS_CR_VISA_XBAR_SABHUB1S_L_HUBS_FXB_Li_BIT5_DATA_BYTE_SEL_MIN (0)
  #define HUBS_CR_VISA_XBAR_SABHUB1S_L_HUBS_FXB_Li_BIT5_DATA_BYTE_SEL_MAX (1) // 0x00000001
  #define HUBS_CR_VISA_XBAR_SABHUB1S_L_HUBS_FXB_Li_BIT5_DATA_BYTE_SEL_DEF (0x00000000)
  #define HUBS_CR_VISA_XBAR_SABHUB1S_L_HUBS_FXB_Li_BIT5_DATA_BYTE_SEL_HSH (0x01177184)

  #define HUBS_CR_VISA_XBAR_SABHUB1S_L_HUBS_FXB_Li_BIT6_DATA_BIT_SEL_OFF (24)
  #define HUBS_CR_VISA_XBAR_SABHUB1S_L_HUBS_FXB_Li_BIT6_DATA_BIT_SEL_WID ( 3)
  #define HUBS_CR_VISA_XBAR_SABHUB1S_L_HUBS_FXB_Li_BIT6_DATA_BIT_SEL_MSK (0x07000000)
  #define HUBS_CR_VISA_XBAR_SABHUB1S_L_HUBS_FXB_Li_BIT6_DATA_BIT_SEL_MIN (0)
  #define HUBS_CR_VISA_XBAR_SABHUB1S_L_HUBS_FXB_Li_BIT6_DATA_BIT_SEL_MAX (7) // 0x00000007
  #define HUBS_CR_VISA_XBAR_SABHUB1S_L_HUBS_FXB_Li_BIT6_DATA_BIT_SEL_DEF (0x00000006)
  #define HUBS_CR_VISA_XBAR_SABHUB1S_L_HUBS_FXB_Li_BIT6_DATA_BIT_SEL_HSH (0x03187184)

  #define HUBS_CR_VISA_XBAR_SABHUB1S_L_HUBS_FXB_Li_BIT6_DATA_BYTE_SEL_OFF (27)
  #define HUBS_CR_VISA_XBAR_SABHUB1S_L_HUBS_FXB_Li_BIT6_DATA_BYTE_SEL_WID ( 1)
  #define HUBS_CR_VISA_XBAR_SABHUB1S_L_HUBS_FXB_Li_BIT6_DATA_BYTE_SEL_MSK (0x08000000)
  #define HUBS_CR_VISA_XBAR_SABHUB1S_L_HUBS_FXB_Li_BIT6_DATA_BYTE_SEL_MIN (0)
  #define HUBS_CR_VISA_XBAR_SABHUB1S_L_HUBS_FXB_Li_BIT6_DATA_BYTE_SEL_MAX (1) // 0x00000001
  #define HUBS_CR_VISA_XBAR_SABHUB1S_L_HUBS_FXB_Li_BIT6_DATA_BYTE_SEL_DEF (0x00000000)
  #define HUBS_CR_VISA_XBAR_SABHUB1S_L_HUBS_FXB_Li_BIT6_DATA_BYTE_SEL_HSH (0x011B7184)

  #define HUBS_CR_VISA_XBAR_SABHUB1S_L_HUBS_FXB_Li_BIT7_DATA_BIT_SEL_OFF (28)
  #define HUBS_CR_VISA_XBAR_SABHUB1S_L_HUBS_FXB_Li_BIT7_DATA_BIT_SEL_WID ( 3)
  #define HUBS_CR_VISA_XBAR_SABHUB1S_L_HUBS_FXB_Li_BIT7_DATA_BIT_SEL_MSK (0x70000000)
  #define HUBS_CR_VISA_XBAR_SABHUB1S_L_HUBS_FXB_Li_BIT7_DATA_BIT_SEL_MIN (0)
  #define HUBS_CR_VISA_XBAR_SABHUB1S_L_HUBS_FXB_Li_BIT7_DATA_BIT_SEL_MAX (7) // 0x00000007
  #define HUBS_CR_VISA_XBAR_SABHUB1S_L_HUBS_FXB_Li_BIT7_DATA_BIT_SEL_DEF (0x00000007)
  #define HUBS_CR_VISA_XBAR_SABHUB1S_L_HUBS_FXB_Li_BIT7_DATA_BIT_SEL_HSH (0x031C7184)

  #define HUBS_CR_VISA_XBAR_SABHUB1S_L_HUBS_FXB_Li_BIT7_DATA_BYTE_SEL_OFF (31)
  #define HUBS_CR_VISA_XBAR_SABHUB1S_L_HUBS_FXB_Li_BIT7_DATA_BYTE_SEL_WID ( 1)
  #define HUBS_CR_VISA_XBAR_SABHUB1S_L_HUBS_FXB_Li_BIT7_DATA_BYTE_SEL_MSK (0x80000000)
  #define HUBS_CR_VISA_XBAR_SABHUB1S_L_HUBS_FXB_Li_BIT7_DATA_BYTE_SEL_MIN (0)
  #define HUBS_CR_VISA_XBAR_SABHUB1S_L_HUBS_FXB_Li_BIT7_DATA_BYTE_SEL_MAX (1) // 0x00000001
  #define HUBS_CR_VISA_XBAR_SABHUB1S_L_HUBS_FXB_Li_BIT7_DATA_BYTE_SEL_DEF (0x00000000)
  #define HUBS_CR_VISA_XBAR_SABHUB1S_L_HUBS_FXB_Li_BIT7_DATA_BYTE_SEL_HSH (0x011F7184)

#define HUBS_CR_VISA_XBAR_SABHUB2S_L_HUBS_REG                          (0x00007188)

  #define HUBS_CR_VISA_XBAR_SABHUB2S_L_HUBS_FXB_Li_BIT0_DATA_BIT_SEL_OFF ( 0)
  #define HUBS_CR_VISA_XBAR_SABHUB2S_L_HUBS_FXB_Li_BIT0_DATA_BIT_SEL_WID ( 3)
  #define HUBS_CR_VISA_XBAR_SABHUB2S_L_HUBS_FXB_Li_BIT0_DATA_BIT_SEL_MSK (0x00000007)
  #define HUBS_CR_VISA_XBAR_SABHUB2S_L_HUBS_FXB_Li_BIT0_DATA_BIT_SEL_MIN (0)
  #define HUBS_CR_VISA_XBAR_SABHUB2S_L_HUBS_FXB_Li_BIT0_DATA_BIT_SEL_MAX (7) // 0x00000007
  #define HUBS_CR_VISA_XBAR_SABHUB2S_L_HUBS_FXB_Li_BIT0_DATA_BIT_SEL_DEF (0x00000000)
  #define HUBS_CR_VISA_XBAR_SABHUB2S_L_HUBS_FXB_Li_BIT0_DATA_BIT_SEL_HSH (0x03007188)

  #define HUBS_CR_VISA_XBAR_SABHUB2S_L_HUBS_FXB_Li_BIT0_DATA_BYTE_SEL_OFF ( 3)
  #define HUBS_CR_VISA_XBAR_SABHUB2S_L_HUBS_FXB_Li_BIT0_DATA_BYTE_SEL_WID ( 1)
  #define HUBS_CR_VISA_XBAR_SABHUB2S_L_HUBS_FXB_Li_BIT0_DATA_BYTE_SEL_MSK (0x00000008)
  #define HUBS_CR_VISA_XBAR_SABHUB2S_L_HUBS_FXB_Li_BIT0_DATA_BYTE_SEL_MIN (0)
  #define HUBS_CR_VISA_XBAR_SABHUB2S_L_HUBS_FXB_Li_BIT0_DATA_BYTE_SEL_MAX (1) // 0x00000001
  #define HUBS_CR_VISA_XBAR_SABHUB2S_L_HUBS_FXB_Li_BIT0_DATA_BYTE_SEL_DEF (0x00000000)
  #define HUBS_CR_VISA_XBAR_SABHUB2S_L_HUBS_FXB_Li_BIT0_DATA_BYTE_SEL_HSH (0x01037188)

  #define HUBS_CR_VISA_XBAR_SABHUB2S_L_HUBS_FXB_Li_BIT1_DATA_BIT_SEL_OFF ( 4)
  #define HUBS_CR_VISA_XBAR_SABHUB2S_L_HUBS_FXB_Li_BIT1_DATA_BIT_SEL_WID ( 3)
  #define HUBS_CR_VISA_XBAR_SABHUB2S_L_HUBS_FXB_Li_BIT1_DATA_BIT_SEL_MSK (0x00000070)
  #define HUBS_CR_VISA_XBAR_SABHUB2S_L_HUBS_FXB_Li_BIT1_DATA_BIT_SEL_MIN (0)
  #define HUBS_CR_VISA_XBAR_SABHUB2S_L_HUBS_FXB_Li_BIT1_DATA_BIT_SEL_MAX (7) // 0x00000007
  #define HUBS_CR_VISA_XBAR_SABHUB2S_L_HUBS_FXB_Li_BIT1_DATA_BIT_SEL_DEF (0x00000001)
  #define HUBS_CR_VISA_XBAR_SABHUB2S_L_HUBS_FXB_Li_BIT1_DATA_BIT_SEL_HSH (0x03047188)

  #define HUBS_CR_VISA_XBAR_SABHUB2S_L_HUBS_FXB_Li_BIT1_DATA_BYTE_SEL_OFF ( 7)
  #define HUBS_CR_VISA_XBAR_SABHUB2S_L_HUBS_FXB_Li_BIT1_DATA_BYTE_SEL_WID ( 1)
  #define HUBS_CR_VISA_XBAR_SABHUB2S_L_HUBS_FXB_Li_BIT1_DATA_BYTE_SEL_MSK (0x00000080)
  #define HUBS_CR_VISA_XBAR_SABHUB2S_L_HUBS_FXB_Li_BIT1_DATA_BYTE_SEL_MIN (0)
  #define HUBS_CR_VISA_XBAR_SABHUB2S_L_HUBS_FXB_Li_BIT1_DATA_BYTE_SEL_MAX (1) // 0x00000001
  #define HUBS_CR_VISA_XBAR_SABHUB2S_L_HUBS_FXB_Li_BIT1_DATA_BYTE_SEL_DEF (0x00000000)
  #define HUBS_CR_VISA_XBAR_SABHUB2S_L_HUBS_FXB_Li_BIT1_DATA_BYTE_SEL_HSH (0x01077188)

  #define HUBS_CR_VISA_XBAR_SABHUB2S_L_HUBS_FXB_Li_BIT2_DATA_BIT_SEL_OFF ( 8)
  #define HUBS_CR_VISA_XBAR_SABHUB2S_L_HUBS_FXB_Li_BIT2_DATA_BIT_SEL_WID ( 3)
  #define HUBS_CR_VISA_XBAR_SABHUB2S_L_HUBS_FXB_Li_BIT2_DATA_BIT_SEL_MSK (0x00000700)
  #define HUBS_CR_VISA_XBAR_SABHUB2S_L_HUBS_FXB_Li_BIT2_DATA_BIT_SEL_MIN (0)
  #define HUBS_CR_VISA_XBAR_SABHUB2S_L_HUBS_FXB_Li_BIT2_DATA_BIT_SEL_MAX (7) // 0x00000007
  #define HUBS_CR_VISA_XBAR_SABHUB2S_L_HUBS_FXB_Li_BIT2_DATA_BIT_SEL_DEF (0x00000002)
  #define HUBS_CR_VISA_XBAR_SABHUB2S_L_HUBS_FXB_Li_BIT2_DATA_BIT_SEL_HSH (0x03087188)

  #define HUBS_CR_VISA_XBAR_SABHUB2S_L_HUBS_FXB_Li_BIT2_DATA_BYTE_SEL_OFF (11)
  #define HUBS_CR_VISA_XBAR_SABHUB2S_L_HUBS_FXB_Li_BIT2_DATA_BYTE_SEL_WID ( 1)
  #define HUBS_CR_VISA_XBAR_SABHUB2S_L_HUBS_FXB_Li_BIT2_DATA_BYTE_SEL_MSK (0x00000800)
  #define HUBS_CR_VISA_XBAR_SABHUB2S_L_HUBS_FXB_Li_BIT2_DATA_BYTE_SEL_MIN (0)
  #define HUBS_CR_VISA_XBAR_SABHUB2S_L_HUBS_FXB_Li_BIT2_DATA_BYTE_SEL_MAX (1) // 0x00000001
  #define HUBS_CR_VISA_XBAR_SABHUB2S_L_HUBS_FXB_Li_BIT2_DATA_BYTE_SEL_DEF (0x00000000)
  #define HUBS_CR_VISA_XBAR_SABHUB2S_L_HUBS_FXB_Li_BIT2_DATA_BYTE_SEL_HSH (0x010B7188)

  #define HUBS_CR_VISA_XBAR_SABHUB2S_L_HUBS_FXB_Li_BIT3_DATA_BIT_SEL_OFF (12)
  #define HUBS_CR_VISA_XBAR_SABHUB2S_L_HUBS_FXB_Li_BIT3_DATA_BIT_SEL_WID ( 3)
  #define HUBS_CR_VISA_XBAR_SABHUB2S_L_HUBS_FXB_Li_BIT3_DATA_BIT_SEL_MSK (0x00007000)
  #define HUBS_CR_VISA_XBAR_SABHUB2S_L_HUBS_FXB_Li_BIT3_DATA_BIT_SEL_MIN (0)
  #define HUBS_CR_VISA_XBAR_SABHUB2S_L_HUBS_FXB_Li_BIT3_DATA_BIT_SEL_MAX (7) // 0x00000007
  #define HUBS_CR_VISA_XBAR_SABHUB2S_L_HUBS_FXB_Li_BIT3_DATA_BIT_SEL_DEF (0x00000003)
  #define HUBS_CR_VISA_XBAR_SABHUB2S_L_HUBS_FXB_Li_BIT3_DATA_BIT_SEL_HSH (0x030C7188)

  #define HUBS_CR_VISA_XBAR_SABHUB2S_L_HUBS_FXB_Li_BIT3_DATA_BYTE_SEL_OFF (15)
  #define HUBS_CR_VISA_XBAR_SABHUB2S_L_HUBS_FXB_Li_BIT3_DATA_BYTE_SEL_WID ( 1)
  #define HUBS_CR_VISA_XBAR_SABHUB2S_L_HUBS_FXB_Li_BIT3_DATA_BYTE_SEL_MSK (0x00008000)
  #define HUBS_CR_VISA_XBAR_SABHUB2S_L_HUBS_FXB_Li_BIT3_DATA_BYTE_SEL_MIN (0)
  #define HUBS_CR_VISA_XBAR_SABHUB2S_L_HUBS_FXB_Li_BIT3_DATA_BYTE_SEL_MAX (1) // 0x00000001
  #define HUBS_CR_VISA_XBAR_SABHUB2S_L_HUBS_FXB_Li_BIT3_DATA_BYTE_SEL_DEF (0x00000000)
  #define HUBS_CR_VISA_XBAR_SABHUB2S_L_HUBS_FXB_Li_BIT3_DATA_BYTE_SEL_HSH (0x010F7188)

  #define HUBS_CR_VISA_XBAR_SABHUB2S_L_HUBS_FXB_Li_BIT4_DATA_BIT_SEL_OFF (16)
  #define HUBS_CR_VISA_XBAR_SABHUB2S_L_HUBS_FXB_Li_BIT4_DATA_BIT_SEL_WID ( 3)
  #define HUBS_CR_VISA_XBAR_SABHUB2S_L_HUBS_FXB_Li_BIT4_DATA_BIT_SEL_MSK (0x00070000)
  #define HUBS_CR_VISA_XBAR_SABHUB2S_L_HUBS_FXB_Li_BIT4_DATA_BIT_SEL_MIN (0)
  #define HUBS_CR_VISA_XBAR_SABHUB2S_L_HUBS_FXB_Li_BIT4_DATA_BIT_SEL_MAX (7) // 0x00000007
  #define HUBS_CR_VISA_XBAR_SABHUB2S_L_HUBS_FXB_Li_BIT4_DATA_BIT_SEL_DEF (0x00000004)
  #define HUBS_CR_VISA_XBAR_SABHUB2S_L_HUBS_FXB_Li_BIT4_DATA_BIT_SEL_HSH (0x03107188)

  #define HUBS_CR_VISA_XBAR_SABHUB2S_L_HUBS_FXB_Li_BIT4_DATA_BYTE_SEL_OFF (19)
  #define HUBS_CR_VISA_XBAR_SABHUB2S_L_HUBS_FXB_Li_BIT4_DATA_BYTE_SEL_WID ( 1)
  #define HUBS_CR_VISA_XBAR_SABHUB2S_L_HUBS_FXB_Li_BIT4_DATA_BYTE_SEL_MSK (0x00080000)
  #define HUBS_CR_VISA_XBAR_SABHUB2S_L_HUBS_FXB_Li_BIT4_DATA_BYTE_SEL_MIN (0)
  #define HUBS_CR_VISA_XBAR_SABHUB2S_L_HUBS_FXB_Li_BIT4_DATA_BYTE_SEL_MAX (1) // 0x00000001
  #define HUBS_CR_VISA_XBAR_SABHUB2S_L_HUBS_FXB_Li_BIT4_DATA_BYTE_SEL_DEF (0x00000000)
  #define HUBS_CR_VISA_XBAR_SABHUB2S_L_HUBS_FXB_Li_BIT4_DATA_BYTE_SEL_HSH (0x01137188)

  #define HUBS_CR_VISA_XBAR_SABHUB2S_L_HUBS_FXB_Li_BIT5_DATA_BIT_SEL_OFF (20)
  #define HUBS_CR_VISA_XBAR_SABHUB2S_L_HUBS_FXB_Li_BIT5_DATA_BIT_SEL_WID ( 3)
  #define HUBS_CR_VISA_XBAR_SABHUB2S_L_HUBS_FXB_Li_BIT5_DATA_BIT_SEL_MSK (0x00700000)
  #define HUBS_CR_VISA_XBAR_SABHUB2S_L_HUBS_FXB_Li_BIT5_DATA_BIT_SEL_MIN (0)
  #define HUBS_CR_VISA_XBAR_SABHUB2S_L_HUBS_FXB_Li_BIT5_DATA_BIT_SEL_MAX (7) // 0x00000007
  #define HUBS_CR_VISA_XBAR_SABHUB2S_L_HUBS_FXB_Li_BIT5_DATA_BIT_SEL_DEF (0x00000005)
  #define HUBS_CR_VISA_XBAR_SABHUB2S_L_HUBS_FXB_Li_BIT5_DATA_BIT_SEL_HSH (0x03147188)

  #define HUBS_CR_VISA_XBAR_SABHUB2S_L_HUBS_FXB_Li_BIT5_DATA_BYTE_SEL_OFF (23)
  #define HUBS_CR_VISA_XBAR_SABHUB2S_L_HUBS_FXB_Li_BIT5_DATA_BYTE_SEL_WID ( 1)
  #define HUBS_CR_VISA_XBAR_SABHUB2S_L_HUBS_FXB_Li_BIT5_DATA_BYTE_SEL_MSK (0x00800000)
  #define HUBS_CR_VISA_XBAR_SABHUB2S_L_HUBS_FXB_Li_BIT5_DATA_BYTE_SEL_MIN (0)
  #define HUBS_CR_VISA_XBAR_SABHUB2S_L_HUBS_FXB_Li_BIT5_DATA_BYTE_SEL_MAX (1) // 0x00000001
  #define HUBS_CR_VISA_XBAR_SABHUB2S_L_HUBS_FXB_Li_BIT5_DATA_BYTE_SEL_DEF (0x00000000)
  #define HUBS_CR_VISA_XBAR_SABHUB2S_L_HUBS_FXB_Li_BIT5_DATA_BYTE_SEL_HSH (0x01177188)

  #define HUBS_CR_VISA_XBAR_SABHUB2S_L_HUBS_FXB_Li_BIT6_DATA_BIT_SEL_OFF (24)
  #define HUBS_CR_VISA_XBAR_SABHUB2S_L_HUBS_FXB_Li_BIT6_DATA_BIT_SEL_WID ( 3)
  #define HUBS_CR_VISA_XBAR_SABHUB2S_L_HUBS_FXB_Li_BIT6_DATA_BIT_SEL_MSK (0x07000000)
  #define HUBS_CR_VISA_XBAR_SABHUB2S_L_HUBS_FXB_Li_BIT6_DATA_BIT_SEL_MIN (0)
  #define HUBS_CR_VISA_XBAR_SABHUB2S_L_HUBS_FXB_Li_BIT6_DATA_BIT_SEL_MAX (7) // 0x00000007
  #define HUBS_CR_VISA_XBAR_SABHUB2S_L_HUBS_FXB_Li_BIT6_DATA_BIT_SEL_DEF (0x00000006)
  #define HUBS_CR_VISA_XBAR_SABHUB2S_L_HUBS_FXB_Li_BIT6_DATA_BIT_SEL_HSH (0x03187188)

  #define HUBS_CR_VISA_XBAR_SABHUB2S_L_HUBS_FXB_Li_BIT6_DATA_BYTE_SEL_OFF (27)
  #define HUBS_CR_VISA_XBAR_SABHUB2S_L_HUBS_FXB_Li_BIT6_DATA_BYTE_SEL_WID ( 1)
  #define HUBS_CR_VISA_XBAR_SABHUB2S_L_HUBS_FXB_Li_BIT6_DATA_BYTE_SEL_MSK (0x08000000)
  #define HUBS_CR_VISA_XBAR_SABHUB2S_L_HUBS_FXB_Li_BIT6_DATA_BYTE_SEL_MIN (0)
  #define HUBS_CR_VISA_XBAR_SABHUB2S_L_HUBS_FXB_Li_BIT6_DATA_BYTE_SEL_MAX (1) // 0x00000001
  #define HUBS_CR_VISA_XBAR_SABHUB2S_L_HUBS_FXB_Li_BIT6_DATA_BYTE_SEL_DEF (0x00000000)
  #define HUBS_CR_VISA_XBAR_SABHUB2S_L_HUBS_FXB_Li_BIT6_DATA_BYTE_SEL_HSH (0x011B7188)

  #define HUBS_CR_VISA_XBAR_SABHUB2S_L_HUBS_FXB_Li_BIT7_DATA_BIT_SEL_OFF (28)
  #define HUBS_CR_VISA_XBAR_SABHUB2S_L_HUBS_FXB_Li_BIT7_DATA_BIT_SEL_WID ( 3)
  #define HUBS_CR_VISA_XBAR_SABHUB2S_L_HUBS_FXB_Li_BIT7_DATA_BIT_SEL_MSK (0x70000000)
  #define HUBS_CR_VISA_XBAR_SABHUB2S_L_HUBS_FXB_Li_BIT7_DATA_BIT_SEL_MIN (0)
  #define HUBS_CR_VISA_XBAR_SABHUB2S_L_HUBS_FXB_Li_BIT7_DATA_BIT_SEL_MAX (7) // 0x00000007
  #define HUBS_CR_VISA_XBAR_SABHUB2S_L_HUBS_FXB_Li_BIT7_DATA_BIT_SEL_DEF (0x00000007)
  #define HUBS_CR_VISA_XBAR_SABHUB2S_L_HUBS_FXB_Li_BIT7_DATA_BIT_SEL_HSH (0x031C7188)

  #define HUBS_CR_VISA_XBAR_SABHUB2S_L_HUBS_FXB_Li_BIT7_DATA_BYTE_SEL_OFF (31)
  #define HUBS_CR_VISA_XBAR_SABHUB2S_L_HUBS_FXB_Li_BIT7_DATA_BYTE_SEL_WID ( 1)
  #define HUBS_CR_VISA_XBAR_SABHUB2S_L_HUBS_FXB_Li_BIT7_DATA_BYTE_SEL_MSK (0x80000000)
  #define HUBS_CR_VISA_XBAR_SABHUB2S_L_HUBS_FXB_Li_BIT7_DATA_BYTE_SEL_MIN (0)
  #define HUBS_CR_VISA_XBAR_SABHUB2S_L_HUBS_FXB_Li_BIT7_DATA_BYTE_SEL_MAX (1) // 0x00000001
  #define HUBS_CR_VISA_XBAR_SABHUB2S_L_HUBS_FXB_Li_BIT7_DATA_BYTE_SEL_DEF (0x00000000)
  #define HUBS_CR_VISA_XBAR_SABHUB2S_L_HUBS_FXB_Li_BIT7_DATA_BYTE_SEL_HSH (0x011F7188)

#define HUBS_CR_VISA_CTL_SABHUB2S_L_HUBS_REG                           (0x0000718C)

  #define HUBS_CR_VISA_CTL_SABHUB2S_L_HUBS_EN_CLK_OFF                  ( 0)
  #define HUBS_CR_VISA_CTL_SABHUB2S_L_HUBS_EN_CLK_WID                  ( 1)
  #define HUBS_CR_VISA_CTL_SABHUB2S_L_HUBS_EN_CLK_MSK                  (0x00000001)
  #define HUBS_CR_VISA_CTL_SABHUB2S_L_HUBS_EN_CLK_MIN                  (0)
  #define HUBS_CR_VISA_CTL_SABHUB2S_L_HUBS_EN_CLK_MAX                  (1) // 0x00000001
  #define HUBS_CR_VISA_CTL_SABHUB2S_L_HUBS_EN_CLK_DEF                  (0x00000000)
  #define HUBS_CR_VISA_CTL_SABHUB2S_L_HUBS_EN_CLK_HSH                  (0x0100718C)

  #define HUBS_CR_VISA_CTL_SABHUB2S_L_HUBS_L0_DATA_BYTE_SEL_OFF        ( 1)
  #define HUBS_CR_VISA_CTL_SABHUB2S_L_HUBS_L0_DATA_BYTE_SEL_WID        ( 7)
  #define HUBS_CR_VISA_CTL_SABHUB2S_L_HUBS_L0_DATA_BYTE_SEL_MSK        (0x000000FE)
  #define HUBS_CR_VISA_CTL_SABHUB2S_L_HUBS_L0_DATA_BYTE_SEL_MIN        (0)
  #define HUBS_CR_VISA_CTL_SABHUB2S_L_HUBS_L0_DATA_BYTE_SEL_MAX        (127) // 0x0000007F
  #define HUBS_CR_VISA_CTL_SABHUB2S_L_HUBS_L0_DATA_BYTE_SEL_DEF        (0x00000000)
  #define HUBS_CR_VISA_CTL_SABHUB2S_L_HUBS_L0_DATA_BYTE_SEL_HSH        (0x0701718C)

  #define HUBS_CR_VISA_CTL_SABHUB2S_L_HUBS_L0_BYP_SEL_OFF              ( 8)
  #define HUBS_CR_VISA_CTL_SABHUB2S_L_HUBS_L0_BYP_SEL_WID              ( 1)
  #define HUBS_CR_VISA_CTL_SABHUB2S_L_HUBS_L0_BYP_SEL_MSK              (0x00000100)
  #define HUBS_CR_VISA_CTL_SABHUB2S_L_HUBS_L0_BYP_SEL_MIN              (0)
  #define HUBS_CR_VISA_CTL_SABHUB2S_L_HUBS_L0_BYP_SEL_MAX              (1) // 0x00000001
  #define HUBS_CR_VISA_CTL_SABHUB2S_L_HUBS_L0_BYP_SEL_DEF              (0x00000000)
  #define HUBS_CR_VISA_CTL_SABHUB2S_L_HUBS_L0_BYP_SEL_HSH              (0x0108718C)

  #define HUBS_CR_VISA_CTL_SABHUB2S_L_HUBS_L1_DATA_BYTE_SEL_OFF        ( 9)
  #define HUBS_CR_VISA_CTL_SABHUB2S_L_HUBS_L1_DATA_BYTE_SEL_WID        ( 7)
  #define HUBS_CR_VISA_CTL_SABHUB2S_L_HUBS_L1_DATA_BYTE_SEL_MSK        (0x0000FE00)
  #define HUBS_CR_VISA_CTL_SABHUB2S_L_HUBS_L1_DATA_BYTE_SEL_MIN        (0)
  #define HUBS_CR_VISA_CTL_SABHUB2S_L_HUBS_L1_DATA_BYTE_SEL_MAX        (127) // 0x0000007F
  #define HUBS_CR_VISA_CTL_SABHUB2S_L_HUBS_L1_DATA_BYTE_SEL_DEF        (0x00000000)
  #define HUBS_CR_VISA_CTL_SABHUB2S_L_HUBS_L1_DATA_BYTE_SEL_HSH        (0x0709718C)

  #define HUBS_CR_VISA_CTL_SABHUB2S_L_HUBS_L1_BYP_SEL_OFF              (16)
  #define HUBS_CR_VISA_CTL_SABHUB2S_L_HUBS_L1_BYP_SEL_WID              ( 1)
  #define HUBS_CR_VISA_CTL_SABHUB2S_L_HUBS_L1_BYP_SEL_MSK              (0x00010000)
  #define HUBS_CR_VISA_CTL_SABHUB2S_L_HUBS_L1_BYP_SEL_MIN              (0)
  #define HUBS_CR_VISA_CTL_SABHUB2S_L_HUBS_L1_BYP_SEL_MAX              (1) // 0x00000001
  #define HUBS_CR_VISA_CTL_SABHUB2S_L_HUBS_L1_BYP_SEL_DEF              (0x00000000)
  #define HUBS_CR_VISA_CTL_SABHUB2S_L_HUBS_L1_BYP_SEL_HSH              (0x0110718C)

  #define HUBS_CR_VISA_CTL_SABHUB2S_L_HUBS_VORANGE_OFF                 (31)
  #define HUBS_CR_VISA_CTL_SABHUB2S_L_HUBS_VORANGE_WID                 ( 1)
  #define HUBS_CR_VISA_CTL_SABHUB2S_L_HUBS_VORANGE_MSK                 (0x80000000)
  #define HUBS_CR_VISA_CTL_SABHUB2S_L_HUBS_VORANGE_MIN                 (0)
  #define HUBS_CR_VISA_CTL_SABHUB2S_L_HUBS_VORANGE_MAX                 (1) // 0x00000001
  #define HUBS_CR_VISA_CTL_SABHUB2S_L_HUBS_VORANGE_DEF                 (0x00000000)
  #define HUBS_CR_VISA_CTL_SABHUB2S_L_HUBS_VORANGE_HSH                 (0x011F718C)

#define HUBS_CR_VISA_XBAR_SABHUB0S_F_HUBS_REG                          (0x00007190)

  #define HUBS_CR_VISA_XBAR_SABHUB0S_F_HUBS_FXB_Li_BIT0_DATA_BIT_SEL_OFF ( 0)
  #define HUBS_CR_VISA_XBAR_SABHUB0S_F_HUBS_FXB_Li_BIT0_DATA_BIT_SEL_WID ( 3)
  #define HUBS_CR_VISA_XBAR_SABHUB0S_F_HUBS_FXB_Li_BIT0_DATA_BIT_SEL_MSK (0x00000007)
  #define HUBS_CR_VISA_XBAR_SABHUB0S_F_HUBS_FXB_Li_BIT0_DATA_BIT_SEL_MIN (0)
  #define HUBS_CR_VISA_XBAR_SABHUB0S_F_HUBS_FXB_Li_BIT0_DATA_BIT_SEL_MAX (7) // 0x00000007
  #define HUBS_CR_VISA_XBAR_SABHUB0S_F_HUBS_FXB_Li_BIT0_DATA_BIT_SEL_DEF (0x00000000)
  #define HUBS_CR_VISA_XBAR_SABHUB0S_F_HUBS_FXB_Li_BIT0_DATA_BIT_SEL_HSH (0x03007190)

  #define HUBS_CR_VISA_XBAR_SABHUB0S_F_HUBS_FXB_Li_BIT0_DATA_BYTE_SEL_OFF ( 3)
  #define HUBS_CR_VISA_XBAR_SABHUB0S_F_HUBS_FXB_Li_BIT0_DATA_BYTE_SEL_WID ( 1)
  #define HUBS_CR_VISA_XBAR_SABHUB0S_F_HUBS_FXB_Li_BIT0_DATA_BYTE_SEL_MSK (0x00000008)
  #define HUBS_CR_VISA_XBAR_SABHUB0S_F_HUBS_FXB_Li_BIT0_DATA_BYTE_SEL_MIN (0)
  #define HUBS_CR_VISA_XBAR_SABHUB0S_F_HUBS_FXB_Li_BIT0_DATA_BYTE_SEL_MAX (1) // 0x00000001
  #define HUBS_CR_VISA_XBAR_SABHUB0S_F_HUBS_FXB_Li_BIT0_DATA_BYTE_SEL_DEF (0x00000000)
  #define HUBS_CR_VISA_XBAR_SABHUB0S_F_HUBS_FXB_Li_BIT0_DATA_BYTE_SEL_HSH (0x01037190)

  #define HUBS_CR_VISA_XBAR_SABHUB0S_F_HUBS_FXB_Li_BIT1_DATA_BIT_SEL_OFF ( 4)
  #define HUBS_CR_VISA_XBAR_SABHUB0S_F_HUBS_FXB_Li_BIT1_DATA_BIT_SEL_WID ( 3)
  #define HUBS_CR_VISA_XBAR_SABHUB0S_F_HUBS_FXB_Li_BIT1_DATA_BIT_SEL_MSK (0x00000070)
  #define HUBS_CR_VISA_XBAR_SABHUB0S_F_HUBS_FXB_Li_BIT1_DATA_BIT_SEL_MIN (0)
  #define HUBS_CR_VISA_XBAR_SABHUB0S_F_HUBS_FXB_Li_BIT1_DATA_BIT_SEL_MAX (7) // 0x00000007
  #define HUBS_CR_VISA_XBAR_SABHUB0S_F_HUBS_FXB_Li_BIT1_DATA_BIT_SEL_DEF (0x00000001)
  #define HUBS_CR_VISA_XBAR_SABHUB0S_F_HUBS_FXB_Li_BIT1_DATA_BIT_SEL_HSH (0x03047190)

  #define HUBS_CR_VISA_XBAR_SABHUB0S_F_HUBS_FXB_Li_BIT1_DATA_BYTE_SEL_OFF ( 7)
  #define HUBS_CR_VISA_XBAR_SABHUB0S_F_HUBS_FXB_Li_BIT1_DATA_BYTE_SEL_WID ( 1)
  #define HUBS_CR_VISA_XBAR_SABHUB0S_F_HUBS_FXB_Li_BIT1_DATA_BYTE_SEL_MSK (0x00000080)
  #define HUBS_CR_VISA_XBAR_SABHUB0S_F_HUBS_FXB_Li_BIT1_DATA_BYTE_SEL_MIN (0)
  #define HUBS_CR_VISA_XBAR_SABHUB0S_F_HUBS_FXB_Li_BIT1_DATA_BYTE_SEL_MAX (1) // 0x00000001
  #define HUBS_CR_VISA_XBAR_SABHUB0S_F_HUBS_FXB_Li_BIT1_DATA_BYTE_SEL_DEF (0x00000000)
  #define HUBS_CR_VISA_XBAR_SABHUB0S_F_HUBS_FXB_Li_BIT1_DATA_BYTE_SEL_HSH (0x01077190)

  #define HUBS_CR_VISA_XBAR_SABHUB0S_F_HUBS_FXB_Li_BIT2_DATA_BIT_SEL_OFF ( 8)
  #define HUBS_CR_VISA_XBAR_SABHUB0S_F_HUBS_FXB_Li_BIT2_DATA_BIT_SEL_WID ( 3)
  #define HUBS_CR_VISA_XBAR_SABHUB0S_F_HUBS_FXB_Li_BIT2_DATA_BIT_SEL_MSK (0x00000700)
  #define HUBS_CR_VISA_XBAR_SABHUB0S_F_HUBS_FXB_Li_BIT2_DATA_BIT_SEL_MIN (0)
  #define HUBS_CR_VISA_XBAR_SABHUB0S_F_HUBS_FXB_Li_BIT2_DATA_BIT_SEL_MAX (7) // 0x00000007
  #define HUBS_CR_VISA_XBAR_SABHUB0S_F_HUBS_FXB_Li_BIT2_DATA_BIT_SEL_DEF (0x00000002)
  #define HUBS_CR_VISA_XBAR_SABHUB0S_F_HUBS_FXB_Li_BIT2_DATA_BIT_SEL_HSH (0x03087190)

  #define HUBS_CR_VISA_XBAR_SABHUB0S_F_HUBS_FXB_Li_BIT2_DATA_BYTE_SEL_OFF (11)
  #define HUBS_CR_VISA_XBAR_SABHUB0S_F_HUBS_FXB_Li_BIT2_DATA_BYTE_SEL_WID ( 1)
  #define HUBS_CR_VISA_XBAR_SABHUB0S_F_HUBS_FXB_Li_BIT2_DATA_BYTE_SEL_MSK (0x00000800)
  #define HUBS_CR_VISA_XBAR_SABHUB0S_F_HUBS_FXB_Li_BIT2_DATA_BYTE_SEL_MIN (0)
  #define HUBS_CR_VISA_XBAR_SABHUB0S_F_HUBS_FXB_Li_BIT2_DATA_BYTE_SEL_MAX (1) // 0x00000001
  #define HUBS_CR_VISA_XBAR_SABHUB0S_F_HUBS_FXB_Li_BIT2_DATA_BYTE_SEL_DEF (0x00000000)
  #define HUBS_CR_VISA_XBAR_SABHUB0S_F_HUBS_FXB_Li_BIT2_DATA_BYTE_SEL_HSH (0x010B7190)

  #define HUBS_CR_VISA_XBAR_SABHUB0S_F_HUBS_FXB_Li_BIT3_DATA_BIT_SEL_OFF (12)
  #define HUBS_CR_VISA_XBAR_SABHUB0S_F_HUBS_FXB_Li_BIT3_DATA_BIT_SEL_WID ( 3)
  #define HUBS_CR_VISA_XBAR_SABHUB0S_F_HUBS_FXB_Li_BIT3_DATA_BIT_SEL_MSK (0x00007000)
  #define HUBS_CR_VISA_XBAR_SABHUB0S_F_HUBS_FXB_Li_BIT3_DATA_BIT_SEL_MIN (0)
  #define HUBS_CR_VISA_XBAR_SABHUB0S_F_HUBS_FXB_Li_BIT3_DATA_BIT_SEL_MAX (7) // 0x00000007
  #define HUBS_CR_VISA_XBAR_SABHUB0S_F_HUBS_FXB_Li_BIT3_DATA_BIT_SEL_DEF (0x00000003)
  #define HUBS_CR_VISA_XBAR_SABHUB0S_F_HUBS_FXB_Li_BIT3_DATA_BIT_SEL_HSH (0x030C7190)

  #define HUBS_CR_VISA_XBAR_SABHUB0S_F_HUBS_FXB_Li_BIT3_DATA_BYTE_SEL_OFF (15)
  #define HUBS_CR_VISA_XBAR_SABHUB0S_F_HUBS_FXB_Li_BIT3_DATA_BYTE_SEL_WID ( 1)
  #define HUBS_CR_VISA_XBAR_SABHUB0S_F_HUBS_FXB_Li_BIT3_DATA_BYTE_SEL_MSK (0x00008000)
  #define HUBS_CR_VISA_XBAR_SABHUB0S_F_HUBS_FXB_Li_BIT3_DATA_BYTE_SEL_MIN (0)
  #define HUBS_CR_VISA_XBAR_SABHUB0S_F_HUBS_FXB_Li_BIT3_DATA_BYTE_SEL_MAX (1) // 0x00000001
  #define HUBS_CR_VISA_XBAR_SABHUB0S_F_HUBS_FXB_Li_BIT3_DATA_BYTE_SEL_DEF (0x00000000)
  #define HUBS_CR_VISA_XBAR_SABHUB0S_F_HUBS_FXB_Li_BIT3_DATA_BYTE_SEL_HSH (0x010F7190)

  #define HUBS_CR_VISA_XBAR_SABHUB0S_F_HUBS_FXB_Li_BIT4_DATA_BIT_SEL_OFF (16)
  #define HUBS_CR_VISA_XBAR_SABHUB0S_F_HUBS_FXB_Li_BIT4_DATA_BIT_SEL_WID ( 3)
  #define HUBS_CR_VISA_XBAR_SABHUB0S_F_HUBS_FXB_Li_BIT4_DATA_BIT_SEL_MSK (0x00070000)
  #define HUBS_CR_VISA_XBAR_SABHUB0S_F_HUBS_FXB_Li_BIT4_DATA_BIT_SEL_MIN (0)
  #define HUBS_CR_VISA_XBAR_SABHUB0S_F_HUBS_FXB_Li_BIT4_DATA_BIT_SEL_MAX (7) // 0x00000007
  #define HUBS_CR_VISA_XBAR_SABHUB0S_F_HUBS_FXB_Li_BIT4_DATA_BIT_SEL_DEF (0x00000004)
  #define HUBS_CR_VISA_XBAR_SABHUB0S_F_HUBS_FXB_Li_BIT4_DATA_BIT_SEL_HSH (0x03107190)

  #define HUBS_CR_VISA_XBAR_SABHUB0S_F_HUBS_FXB_Li_BIT4_DATA_BYTE_SEL_OFF (19)
  #define HUBS_CR_VISA_XBAR_SABHUB0S_F_HUBS_FXB_Li_BIT4_DATA_BYTE_SEL_WID ( 1)
  #define HUBS_CR_VISA_XBAR_SABHUB0S_F_HUBS_FXB_Li_BIT4_DATA_BYTE_SEL_MSK (0x00080000)
  #define HUBS_CR_VISA_XBAR_SABHUB0S_F_HUBS_FXB_Li_BIT4_DATA_BYTE_SEL_MIN (0)
  #define HUBS_CR_VISA_XBAR_SABHUB0S_F_HUBS_FXB_Li_BIT4_DATA_BYTE_SEL_MAX (1) // 0x00000001
  #define HUBS_CR_VISA_XBAR_SABHUB0S_F_HUBS_FXB_Li_BIT4_DATA_BYTE_SEL_DEF (0x00000000)
  #define HUBS_CR_VISA_XBAR_SABHUB0S_F_HUBS_FXB_Li_BIT4_DATA_BYTE_SEL_HSH (0x01137190)

  #define HUBS_CR_VISA_XBAR_SABHUB0S_F_HUBS_FXB_Li_BIT5_DATA_BIT_SEL_OFF (20)
  #define HUBS_CR_VISA_XBAR_SABHUB0S_F_HUBS_FXB_Li_BIT5_DATA_BIT_SEL_WID ( 3)
  #define HUBS_CR_VISA_XBAR_SABHUB0S_F_HUBS_FXB_Li_BIT5_DATA_BIT_SEL_MSK (0x00700000)
  #define HUBS_CR_VISA_XBAR_SABHUB0S_F_HUBS_FXB_Li_BIT5_DATA_BIT_SEL_MIN (0)
  #define HUBS_CR_VISA_XBAR_SABHUB0S_F_HUBS_FXB_Li_BIT5_DATA_BIT_SEL_MAX (7) // 0x00000007
  #define HUBS_CR_VISA_XBAR_SABHUB0S_F_HUBS_FXB_Li_BIT5_DATA_BIT_SEL_DEF (0x00000005)
  #define HUBS_CR_VISA_XBAR_SABHUB0S_F_HUBS_FXB_Li_BIT5_DATA_BIT_SEL_HSH (0x03147190)

  #define HUBS_CR_VISA_XBAR_SABHUB0S_F_HUBS_FXB_Li_BIT5_DATA_BYTE_SEL_OFF (23)
  #define HUBS_CR_VISA_XBAR_SABHUB0S_F_HUBS_FXB_Li_BIT5_DATA_BYTE_SEL_WID ( 1)
  #define HUBS_CR_VISA_XBAR_SABHUB0S_F_HUBS_FXB_Li_BIT5_DATA_BYTE_SEL_MSK (0x00800000)
  #define HUBS_CR_VISA_XBAR_SABHUB0S_F_HUBS_FXB_Li_BIT5_DATA_BYTE_SEL_MIN (0)
  #define HUBS_CR_VISA_XBAR_SABHUB0S_F_HUBS_FXB_Li_BIT5_DATA_BYTE_SEL_MAX (1) // 0x00000001
  #define HUBS_CR_VISA_XBAR_SABHUB0S_F_HUBS_FXB_Li_BIT5_DATA_BYTE_SEL_DEF (0x00000000)
  #define HUBS_CR_VISA_XBAR_SABHUB0S_F_HUBS_FXB_Li_BIT5_DATA_BYTE_SEL_HSH (0x01177190)

  #define HUBS_CR_VISA_XBAR_SABHUB0S_F_HUBS_FXB_Li_BIT6_DATA_BIT_SEL_OFF (24)
  #define HUBS_CR_VISA_XBAR_SABHUB0S_F_HUBS_FXB_Li_BIT6_DATA_BIT_SEL_WID ( 3)
  #define HUBS_CR_VISA_XBAR_SABHUB0S_F_HUBS_FXB_Li_BIT6_DATA_BIT_SEL_MSK (0x07000000)
  #define HUBS_CR_VISA_XBAR_SABHUB0S_F_HUBS_FXB_Li_BIT6_DATA_BIT_SEL_MIN (0)
  #define HUBS_CR_VISA_XBAR_SABHUB0S_F_HUBS_FXB_Li_BIT6_DATA_BIT_SEL_MAX (7) // 0x00000007
  #define HUBS_CR_VISA_XBAR_SABHUB0S_F_HUBS_FXB_Li_BIT6_DATA_BIT_SEL_DEF (0x00000006)
  #define HUBS_CR_VISA_XBAR_SABHUB0S_F_HUBS_FXB_Li_BIT6_DATA_BIT_SEL_HSH (0x03187190)

  #define HUBS_CR_VISA_XBAR_SABHUB0S_F_HUBS_FXB_Li_BIT6_DATA_BYTE_SEL_OFF (27)
  #define HUBS_CR_VISA_XBAR_SABHUB0S_F_HUBS_FXB_Li_BIT6_DATA_BYTE_SEL_WID ( 1)
  #define HUBS_CR_VISA_XBAR_SABHUB0S_F_HUBS_FXB_Li_BIT6_DATA_BYTE_SEL_MSK (0x08000000)
  #define HUBS_CR_VISA_XBAR_SABHUB0S_F_HUBS_FXB_Li_BIT6_DATA_BYTE_SEL_MIN (0)
  #define HUBS_CR_VISA_XBAR_SABHUB0S_F_HUBS_FXB_Li_BIT6_DATA_BYTE_SEL_MAX (1) // 0x00000001
  #define HUBS_CR_VISA_XBAR_SABHUB0S_F_HUBS_FXB_Li_BIT6_DATA_BYTE_SEL_DEF (0x00000000)
  #define HUBS_CR_VISA_XBAR_SABHUB0S_F_HUBS_FXB_Li_BIT6_DATA_BYTE_SEL_HSH (0x011B7190)

  #define HUBS_CR_VISA_XBAR_SABHUB0S_F_HUBS_FXB_Li_BIT7_DATA_BIT_SEL_OFF (28)
  #define HUBS_CR_VISA_XBAR_SABHUB0S_F_HUBS_FXB_Li_BIT7_DATA_BIT_SEL_WID ( 3)
  #define HUBS_CR_VISA_XBAR_SABHUB0S_F_HUBS_FXB_Li_BIT7_DATA_BIT_SEL_MSK (0x70000000)
  #define HUBS_CR_VISA_XBAR_SABHUB0S_F_HUBS_FXB_Li_BIT7_DATA_BIT_SEL_MIN (0)
  #define HUBS_CR_VISA_XBAR_SABHUB0S_F_HUBS_FXB_Li_BIT7_DATA_BIT_SEL_MAX (7) // 0x00000007
  #define HUBS_CR_VISA_XBAR_SABHUB0S_F_HUBS_FXB_Li_BIT7_DATA_BIT_SEL_DEF (0x00000007)
  #define HUBS_CR_VISA_XBAR_SABHUB0S_F_HUBS_FXB_Li_BIT7_DATA_BIT_SEL_HSH (0x031C7190)

  #define HUBS_CR_VISA_XBAR_SABHUB0S_F_HUBS_FXB_Li_BIT7_DATA_BYTE_SEL_OFF (31)
  #define HUBS_CR_VISA_XBAR_SABHUB0S_F_HUBS_FXB_Li_BIT7_DATA_BYTE_SEL_WID ( 1)
  #define HUBS_CR_VISA_XBAR_SABHUB0S_F_HUBS_FXB_Li_BIT7_DATA_BYTE_SEL_MSK (0x80000000)
  #define HUBS_CR_VISA_XBAR_SABHUB0S_F_HUBS_FXB_Li_BIT7_DATA_BYTE_SEL_MIN (0)
  #define HUBS_CR_VISA_XBAR_SABHUB0S_F_HUBS_FXB_Li_BIT7_DATA_BYTE_SEL_MAX (1) // 0x00000001
  #define HUBS_CR_VISA_XBAR_SABHUB0S_F_HUBS_FXB_Li_BIT7_DATA_BYTE_SEL_DEF (0x00000000)
  #define HUBS_CR_VISA_XBAR_SABHUB0S_F_HUBS_FXB_Li_BIT7_DATA_BYTE_SEL_HSH (0x011F7190)

#define HUBS_CR_VISA_SLIDE_SABHUB1S_L_HUBS_REG                         (0x00007194)

  #define HUBS_CR_VISA_SLIDE_SABHUB1S_L_HUBS_WINDOW_SLIDE_L0_OFF       ( 0)
  #define HUBS_CR_VISA_SLIDE_SABHUB1S_L_HUBS_WINDOW_SLIDE_L0_WID       ( 3)
  #define HUBS_CR_VISA_SLIDE_SABHUB1S_L_HUBS_WINDOW_SLIDE_L0_MSK       (0x00000007)
  #define HUBS_CR_VISA_SLIDE_SABHUB1S_L_HUBS_WINDOW_SLIDE_L0_MIN       (0)
  #define HUBS_CR_VISA_SLIDE_SABHUB1S_L_HUBS_WINDOW_SLIDE_L0_MAX       (7) // 0x00000007
  #define HUBS_CR_VISA_SLIDE_SABHUB1S_L_HUBS_WINDOW_SLIDE_L0_DEF       (0x00000000)
  #define HUBS_CR_VISA_SLIDE_SABHUB1S_L_HUBS_WINDOW_SLIDE_L0_HSH       (0x03007194)

  #define HUBS_CR_VISA_SLIDE_SABHUB1S_L_HUBS_ALT_L0_DATA_BYTE_SEL_OFF  ( 3)
  #define HUBS_CR_VISA_SLIDE_SABHUB1S_L_HUBS_ALT_L0_DATA_BYTE_SEL_WID  ( 7)
  #define HUBS_CR_VISA_SLIDE_SABHUB1S_L_HUBS_ALT_L0_DATA_BYTE_SEL_MSK  (0x000003F8)
  #define HUBS_CR_VISA_SLIDE_SABHUB1S_L_HUBS_ALT_L0_DATA_BYTE_SEL_MIN  (0)
  #define HUBS_CR_VISA_SLIDE_SABHUB1S_L_HUBS_ALT_L0_DATA_BYTE_SEL_MAX  (127) // 0x0000007F
  #define HUBS_CR_VISA_SLIDE_SABHUB1S_L_HUBS_ALT_L0_DATA_BYTE_SEL_DEF  (0x00000000)
  #define HUBS_CR_VISA_SLIDE_SABHUB1S_L_HUBS_ALT_L0_DATA_BYTE_SEL_HSH  (0x07037194)

  #define HUBS_CR_VISA_SLIDE_SABHUB1S_L_HUBS_WINDOW_SLIDE_L1_OFF       (10)
  #define HUBS_CR_VISA_SLIDE_SABHUB1S_L_HUBS_WINDOW_SLIDE_L1_WID       ( 3)
  #define HUBS_CR_VISA_SLIDE_SABHUB1S_L_HUBS_WINDOW_SLIDE_L1_MSK       (0x00001C00)
  #define HUBS_CR_VISA_SLIDE_SABHUB1S_L_HUBS_WINDOW_SLIDE_L1_MIN       (0)
  #define HUBS_CR_VISA_SLIDE_SABHUB1S_L_HUBS_WINDOW_SLIDE_L1_MAX       (7) // 0x00000007
  #define HUBS_CR_VISA_SLIDE_SABHUB1S_L_HUBS_WINDOW_SLIDE_L1_DEF       (0x00000000)
  #define HUBS_CR_VISA_SLIDE_SABHUB1S_L_HUBS_WINDOW_SLIDE_L1_HSH       (0x030A7194)

  #define HUBS_CR_VISA_SLIDE_SABHUB1S_L_HUBS_ALT_L1_DATA_BYTE_SEL_OFF  (13)
  #define HUBS_CR_VISA_SLIDE_SABHUB1S_L_HUBS_ALT_L1_DATA_BYTE_SEL_WID  ( 7)
  #define HUBS_CR_VISA_SLIDE_SABHUB1S_L_HUBS_ALT_L1_DATA_BYTE_SEL_MSK  (0x000FE000)
  #define HUBS_CR_VISA_SLIDE_SABHUB1S_L_HUBS_ALT_L1_DATA_BYTE_SEL_MIN  (0)
  #define HUBS_CR_VISA_SLIDE_SABHUB1S_L_HUBS_ALT_L1_DATA_BYTE_SEL_MAX  (127) // 0x0000007F
  #define HUBS_CR_VISA_SLIDE_SABHUB1S_L_HUBS_ALT_L1_DATA_BYTE_SEL_DEF  (0x00000000)
  #define HUBS_CR_VISA_SLIDE_SABHUB1S_L_HUBS_ALT_L1_DATA_BYTE_SEL_HSH  (0x070D7194)

#define HUBS_CR_VISA_SLIDE_SABHUB0S_L_HUBS_REG                         (0x00007198)

  #define HUBS_CR_VISA_SLIDE_SABHUB0S_L_HUBS_WINDOW_SLIDE_L0_OFF       ( 0)
  #define HUBS_CR_VISA_SLIDE_SABHUB0S_L_HUBS_WINDOW_SLIDE_L0_WID       ( 3)
  #define HUBS_CR_VISA_SLIDE_SABHUB0S_L_HUBS_WINDOW_SLIDE_L0_MSK       (0x00000007)
  #define HUBS_CR_VISA_SLIDE_SABHUB0S_L_HUBS_WINDOW_SLIDE_L0_MIN       (0)
  #define HUBS_CR_VISA_SLIDE_SABHUB0S_L_HUBS_WINDOW_SLIDE_L0_MAX       (7) // 0x00000007
  #define HUBS_CR_VISA_SLIDE_SABHUB0S_L_HUBS_WINDOW_SLIDE_L0_DEF       (0x00000000)
  #define HUBS_CR_VISA_SLIDE_SABHUB0S_L_HUBS_WINDOW_SLIDE_L0_HSH       (0x03007198)

  #define HUBS_CR_VISA_SLIDE_SABHUB0S_L_HUBS_ALT_L0_DATA_BYTE_SEL_OFF  ( 3)
  #define HUBS_CR_VISA_SLIDE_SABHUB0S_L_HUBS_ALT_L0_DATA_BYTE_SEL_WID  ( 7)
  #define HUBS_CR_VISA_SLIDE_SABHUB0S_L_HUBS_ALT_L0_DATA_BYTE_SEL_MSK  (0x000003F8)
  #define HUBS_CR_VISA_SLIDE_SABHUB0S_L_HUBS_ALT_L0_DATA_BYTE_SEL_MIN  (0)
  #define HUBS_CR_VISA_SLIDE_SABHUB0S_L_HUBS_ALT_L0_DATA_BYTE_SEL_MAX  (127) // 0x0000007F
  #define HUBS_CR_VISA_SLIDE_SABHUB0S_L_HUBS_ALT_L0_DATA_BYTE_SEL_DEF  (0x00000000)
  #define HUBS_CR_VISA_SLIDE_SABHUB0S_L_HUBS_ALT_L0_DATA_BYTE_SEL_HSH  (0x07037198)

  #define HUBS_CR_VISA_SLIDE_SABHUB0S_L_HUBS_WINDOW_SLIDE_L1_OFF       (10)
  #define HUBS_CR_VISA_SLIDE_SABHUB0S_L_HUBS_WINDOW_SLIDE_L1_WID       ( 3)
  #define HUBS_CR_VISA_SLIDE_SABHUB0S_L_HUBS_WINDOW_SLIDE_L1_MSK       (0x00001C00)
  #define HUBS_CR_VISA_SLIDE_SABHUB0S_L_HUBS_WINDOW_SLIDE_L1_MIN       (0)
  #define HUBS_CR_VISA_SLIDE_SABHUB0S_L_HUBS_WINDOW_SLIDE_L1_MAX       (7) // 0x00000007
  #define HUBS_CR_VISA_SLIDE_SABHUB0S_L_HUBS_WINDOW_SLIDE_L1_DEF       (0x00000000)
  #define HUBS_CR_VISA_SLIDE_SABHUB0S_L_HUBS_WINDOW_SLIDE_L1_HSH       (0x030A7198)

  #define HUBS_CR_VISA_SLIDE_SABHUB0S_L_HUBS_ALT_L1_DATA_BYTE_SEL_OFF  (13)
  #define HUBS_CR_VISA_SLIDE_SABHUB0S_L_HUBS_ALT_L1_DATA_BYTE_SEL_WID  ( 7)
  #define HUBS_CR_VISA_SLIDE_SABHUB0S_L_HUBS_ALT_L1_DATA_BYTE_SEL_MSK  (0x000FE000)
  #define HUBS_CR_VISA_SLIDE_SABHUB0S_L_HUBS_ALT_L1_DATA_BYTE_SEL_MIN  (0)
  #define HUBS_CR_VISA_SLIDE_SABHUB0S_L_HUBS_ALT_L1_DATA_BYTE_SEL_MAX  (127) // 0x0000007F
  #define HUBS_CR_VISA_SLIDE_SABHUB0S_L_HUBS_ALT_L1_DATA_BYTE_SEL_DEF  (0x00000000)
  #define HUBS_CR_VISA_SLIDE_SABHUB0S_L_HUBS_ALT_L1_DATA_BYTE_SEL_HSH  (0x070D7198)

#define HUBS_CR_VISA_SLIDE_SABHUB2S_L_HUBS_REG                         (0x0000719C)

  #define HUBS_CR_VISA_SLIDE_SABHUB2S_L_HUBS_WINDOW_SLIDE_L0_OFF       ( 0)
  #define HUBS_CR_VISA_SLIDE_SABHUB2S_L_HUBS_WINDOW_SLIDE_L0_WID       ( 3)
  #define HUBS_CR_VISA_SLIDE_SABHUB2S_L_HUBS_WINDOW_SLIDE_L0_MSK       (0x00000007)
  #define HUBS_CR_VISA_SLIDE_SABHUB2S_L_HUBS_WINDOW_SLIDE_L0_MIN       (0)
  #define HUBS_CR_VISA_SLIDE_SABHUB2S_L_HUBS_WINDOW_SLIDE_L0_MAX       (7) // 0x00000007
  #define HUBS_CR_VISA_SLIDE_SABHUB2S_L_HUBS_WINDOW_SLIDE_L0_DEF       (0x00000000)
  #define HUBS_CR_VISA_SLIDE_SABHUB2S_L_HUBS_WINDOW_SLIDE_L0_HSH       (0x0300719C)

  #define HUBS_CR_VISA_SLIDE_SABHUB2S_L_HUBS_ALT_L0_DATA_BYTE_SEL_OFF  ( 3)
  #define HUBS_CR_VISA_SLIDE_SABHUB2S_L_HUBS_ALT_L0_DATA_BYTE_SEL_WID  ( 7)
  #define HUBS_CR_VISA_SLIDE_SABHUB2S_L_HUBS_ALT_L0_DATA_BYTE_SEL_MSK  (0x000003F8)
  #define HUBS_CR_VISA_SLIDE_SABHUB2S_L_HUBS_ALT_L0_DATA_BYTE_SEL_MIN  (0)
  #define HUBS_CR_VISA_SLIDE_SABHUB2S_L_HUBS_ALT_L0_DATA_BYTE_SEL_MAX  (127) // 0x0000007F
  #define HUBS_CR_VISA_SLIDE_SABHUB2S_L_HUBS_ALT_L0_DATA_BYTE_SEL_DEF  (0x00000000)
  #define HUBS_CR_VISA_SLIDE_SABHUB2S_L_HUBS_ALT_L0_DATA_BYTE_SEL_HSH  (0x0703719C)

  #define HUBS_CR_VISA_SLIDE_SABHUB2S_L_HUBS_WINDOW_SLIDE_L1_OFF       (10)
  #define HUBS_CR_VISA_SLIDE_SABHUB2S_L_HUBS_WINDOW_SLIDE_L1_WID       ( 3)
  #define HUBS_CR_VISA_SLIDE_SABHUB2S_L_HUBS_WINDOW_SLIDE_L1_MSK       (0x00001C00)
  #define HUBS_CR_VISA_SLIDE_SABHUB2S_L_HUBS_WINDOW_SLIDE_L1_MIN       (0)
  #define HUBS_CR_VISA_SLIDE_SABHUB2S_L_HUBS_WINDOW_SLIDE_L1_MAX       (7) // 0x00000007
  #define HUBS_CR_VISA_SLIDE_SABHUB2S_L_HUBS_WINDOW_SLIDE_L1_DEF       (0x00000000)
  #define HUBS_CR_VISA_SLIDE_SABHUB2S_L_HUBS_WINDOW_SLIDE_L1_HSH       (0x030A719C)

  #define HUBS_CR_VISA_SLIDE_SABHUB2S_L_HUBS_ALT_L1_DATA_BYTE_SEL_OFF  (13)
  #define HUBS_CR_VISA_SLIDE_SABHUB2S_L_HUBS_ALT_L1_DATA_BYTE_SEL_WID  ( 7)
  #define HUBS_CR_VISA_SLIDE_SABHUB2S_L_HUBS_ALT_L1_DATA_BYTE_SEL_MSK  (0x000FE000)
  #define HUBS_CR_VISA_SLIDE_SABHUB2S_L_HUBS_ALT_L1_DATA_BYTE_SEL_MIN  (0)
  #define HUBS_CR_VISA_SLIDE_SABHUB2S_L_HUBS_ALT_L1_DATA_BYTE_SEL_MAX  (127) // 0x0000007F
  #define HUBS_CR_VISA_SLIDE_SABHUB2S_L_HUBS_ALT_L1_DATA_BYTE_SEL_DEF  (0x00000000)
  #define HUBS_CR_VISA_SLIDE_SABHUB2S_L_HUBS_ALT_L1_DATA_BYTE_SEL_HSH  (0x070D719C)

#define HUBS_CR_VISA_XBAR_SABHUB1S_I_HUBS_REG                          (0x000071A0)

  #define HUBS_CR_VISA_XBAR_SABHUB1S_I_HUBS_FXB_Li_BIT0_DATA_BIT_SEL_OFF ( 0)
  #define HUBS_CR_VISA_XBAR_SABHUB1S_I_HUBS_FXB_Li_BIT0_DATA_BIT_SEL_WID ( 3)
  #define HUBS_CR_VISA_XBAR_SABHUB1S_I_HUBS_FXB_Li_BIT0_DATA_BIT_SEL_MSK (0x00000007)
  #define HUBS_CR_VISA_XBAR_SABHUB1S_I_HUBS_FXB_Li_BIT0_DATA_BIT_SEL_MIN (0)
  #define HUBS_CR_VISA_XBAR_SABHUB1S_I_HUBS_FXB_Li_BIT0_DATA_BIT_SEL_MAX (7) // 0x00000007
  #define HUBS_CR_VISA_XBAR_SABHUB1S_I_HUBS_FXB_Li_BIT0_DATA_BIT_SEL_DEF (0x00000000)
  #define HUBS_CR_VISA_XBAR_SABHUB1S_I_HUBS_FXB_Li_BIT0_DATA_BIT_SEL_HSH (0x030071A0)

  #define HUBS_CR_VISA_XBAR_SABHUB1S_I_HUBS_FXB_Li_BIT0_DATA_BYTE_SEL_OFF ( 3)
  #define HUBS_CR_VISA_XBAR_SABHUB1S_I_HUBS_FXB_Li_BIT0_DATA_BYTE_SEL_WID ( 1)
  #define HUBS_CR_VISA_XBAR_SABHUB1S_I_HUBS_FXB_Li_BIT0_DATA_BYTE_SEL_MSK (0x00000008)
  #define HUBS_CR_VISA_XBAR_SABHUB1S_I_HUBS_FXB_Li_BIT0_DATA_BYTE_SEL_MIN (0)
  #define HUBS_CR_VISA_XBAR_SABHUB1S_I_HUBS_FXB_Li_BIT0_DATA_BYTE_SEL_MAX (1) // 0x00000001
  #define HUBS_CR_VISA_XBAR_SABHUB1S_I_HUBS_FXB_Li_BIT0_DATA_BYTE_SEL_DEF (0x00000000)
  #define HUBS_CR_VISA_XBAR_SABHUB1S_I_HUBS_FXB_Li_BIT0_DATA_BYTE_SEL_HSH (0x010371A0)

  #define HUBS_CR_VISA_XBAR_SABHUB1S_I_HUBS_FXB_Li_BIT1_DATA_BIT_SEL_OFF ( 4)
  #define HUBS_CR_VISA_XBAR_SABHUB1S_I_HUBS_FXB_Li_BIT1_DATA_BIT_SEL_WID ( 3)
  #define HUBS_CR_VISA_XBAR_SABHUB1S_I_HUBS_FXB_Li_BIT1_DATA_BIT_SEL_MSK (0x00000070)
  #define HUBS_CR_VISA_XBAR_SABHUB1S_I_HUBS_FXB_Li_BIT1_DATA_BIT_SEL_MIN (0)
  #define HUBS_CR_VISA_XBAR_SABHUB1S_I_HUBS_FXB_Li_BIT1_DATA_BIT_SEL_MAX (7) // 0x00000007
  #define HUBS_CR_VISA_XBAR_SABHUB1S_I_HUBS_FXB_Li_BIT1_DATA_BIT_SEL_DEF (0x00000001)
  #define HUBS_CR_VISA_XBAR_SABHUB1S_I_HUBS_FXB_Li_BIT1_DATA_BIT_SEL_HSH (0x030471A0)

  #define HUBS_CR_VISA_XBAR_SABHUB1S_I_HUBS_FXB_Li_BIT1_DATA_BYTE_SEL_OFF ( 7)
  #define HUBS_CR_VISA_XBAR_SABHUB1S_I_HUBS_FXB_Li_BIT1_DATA_BYTE_SEL_WID ( 1)
  #define HUBS_CR_VISA_XBAR_SABHUB1S_I_HUBS_FXB_Li_BIT1_DATA_BYTE_SEL_MSK (0x00000080)
  #define HUBS_CR_VISA_XBAR_SABHUB1S_I_HUBS_FXB_Li_BIT1_DATA_BYTE_SEL_MIN (0)
  #define HUBS_CR_VISA_XBAR_SABHUB1S_I_HUBS_FXB_Li_BIT1_DATA_BYTE_SEL_MAX (1) // 0x00000001
  #define HUBS_CR_VISA_XBAR_SABHUB1S_I_HUBS_FXB_Li_BIT1_DATA_BYTE_SEL_DEF (0x00000000)
  #define HUBS_CR_VISA_XBAR_SABHUB1S_I_HUBS_FXB_Li_BIT1_DATA_BYTE_SEL_HSH (0x010771A0)

  #define HUBS_CR_VISA_XBAR_SABHUB1S_I_HUBS_FXB_Li_BIT2_DATA_BIT_SEL_OFF ( 8)
  #define HUBS_CR_VISA_XBAR_SABHUB1S_I_HUBS_FXB_Li_BIT2_DATA_BIT_SEL_WID ( 3)
  #define HUBS_CR_VISA_XBAR_SABHUB1S_I_HUBS_FXB_Li_BIT2_DATA_BIT_SEL_MSK (0x00000700)
  #define HUBS_CR_VISA_XBAR_SABHUB1S_I_HUBS_FXB_Li_BIT2_DATA_BIT_SEL_MIN (0)
  #define HUBS_CR_VISA_XBAR_SABHUB1S_I_HUBS_FXB_Li_BIT2_DATA_BIT_SEL_MAX (7) // 0x00000007
  #define HUBS_CR_VISA_XBAR_SABHUB1S_I_HUBS_FXB_Li_BIT2_DATA_BIT_SEL_DEF (0x00000002)
  #define HUBS_CR_VISA_XBAR_SABHUB1S_I_HUBS_FXB_Li_BIT2_DATA_BIT_SEL_HSH (0x030871A0)

  #define HUBS_CR_VISA_XBAR_SABHUB1S_I_HUBS_FXB_Li_BIT2_DATA_BYTE_SEL_OFF (11)
  #define HUBS_CR_VISA_XBAR_SABHUB1S_I_HUBS_FXB_Li_BIT2_DATA_BYTE_SEL_WID ( 1)
  #define HUBS_CR_VISA_XBAR_SABHUB1S_I_HUBS_FXB_Li_BIT2_DATA_BYTE_SEL_MSK (0x00000800)
  #define HUBS_CR_VISA_XBAR_SABHUB1S_I_HUBS_FXB_Li_BIT2_DATA_BYTE_SEL_MIN (0)
  #define HUBS_CR_VISA_XBAR_SABHUB1S_I_HUBS_FXB_Li_BIT2_DATA_BYTE_SEL_MAX (1) // 0x00000001
  #define HUBS_CR_VISA_XBAR_SABHUB1S_I_HUBS_FXB_Li_BIT2_DATA_BYTE_SEL_DEF (0x00000000)
  #define HUBS_CR_VISA_XBAR_SABHUB1S_I_HUBS_FXB_Li_BIT2_DATA_BYTE_SEL_HSH (0x010B71A0)

  #define HUBS_CR_VISA_XBAR_SABHUB1S_I_HUBS_FXB_Li_BIT3_DATA_BIT_SEL_OFF (12)
  #define HUBS_CR_VISA_XBAR_SABHUB1S_I_HUBS_FXB_Li_BIT3_DATA_BIT_SEL_WID ( 3)
  #define HUBS_CR_VISA_XBAR_SABHUB1S_I_HUBS_FXB_Li_BIT3_DATA_BIT_SEL_MSK (0x00007000)
  #define HUBS_CR_VISA_XBAR_SABHUB1S_I_HUBS_FXB_Li_BIT3_DATA_BIT_SEL_MIN (0)
  #define HUBS_CR_VISA_XBAR_SABHUB1S_I_HUBS_FXB_Li_BIT3_DATA_BIT_SEL_MAX (7) // 0x00000007
  #define HUBS_CR_VISA_XBAR_SABHUB1S_I_HUBS_FXB_Li_BIT3_DATA_BIT_SEL_DEF (0x00000003)
  #define HUBS_CR_VISA_XBAR_SABHUB1S_I_HUBS_FXB_Li_BIT3_DATA_BIT_SEL_HSH (0x030C71A0)

  #define HUBS_CR_VISA_XBAR_SABHUB1S_I_HUBS_FXB_Li_BIT3_DATA_BYTE_SEL_OFF (15)
  #define HUBS_CR_VISA_XBAR_SABHUB1S_I_HUBS_FXB_Li_BIT3_DATA_BYTE_SEL_WID ( 1)
  #define HUBS_CR_VISA_XBAR_SABHUB1S_I_HUBS_FXB_Li_BIT3_DATA_BYTE_SEL_MSK (0x00008000)
  #define HUBS_CR_VISA_XBAR_SABHUB1S_I_HUBS_FXB_Li_BIT3_DATA_BYTE_SEL_MIN (0)
  #define HUBS_CR_VISA_XBAR_SABHUB1S_I_HUBS_FXB_Li_BIT3_DATA_BYTE_SEL_MAX (1) // 0x00000001
  #define HUBS_CR_VISA_XBAR_SABHUB1S_I_HUBS_FXB_Li_BIT3_DATA_BYTE_SEL_DEF (0x00000000)
  #define HUBS_CR_VISA_XBAR_SABHUB1S_I_HUBS_FXB_Li_BIT3_DATA_BYTE_SEL_HSH (0x010F71A0)

  #define HUBS_CR_VISA_XBAR_SABHUB1S_I_HUBS_FXB_Li_BIT4_DATA_BIT_SEL_OFF (16)
  #define HUBS_CR_VISA_XBAR_SABHUB1S_I_HUBS_FXB_Li_BIT4_DATA_BIT_SEL_WID ( 3)
  #define HUBS_CR_VISA_XBAR_SABHUB1S_I_HUBS_FXB_Li_BIT4_DATA_BIT_SEL_MSK (0x00070000)
  #define HUBS_CR_VISA_XBAR_SABHUB1S_I_HUBS_FXB_Li_BIT4_DATA_BIT_SEL_MIN (0)
  #define HUBS_CR_VISA_XBAR_SABHUB1S_I_HUBS_FXB_Li_BIT4_DATA_BIT_SEL_MAX (7) // 0x00000007
  #define HUBS_CR_VISA_XBAR_SABHUB1S_I_HUBS_FXB_Li_BIT4_DATA_BIT_SEL_DEF (0x00000004)
  #define HUBS_CR_VISA_XBAR_SABHUB1S_I_HUBS_FXB_Li_BIT4_DATA_BIT_SEL_HSH (0x031071A0)

  #define HUBS_CR_VISA_XBAR_SABHUB1S_I_HUBS_FXB_Li_BIT4_DATA_BYTE_SEL_OFF (19)
  #define HUBS_CR_VISA_XBAR_SABHUB1S_I_HUBS_FXB_Li_BIT4_DATA_BYTE_SEL_WID ( 1)
  #define HUBS_CR_VISA_XBAR_SABHUB1S_I_HUBS_FXB_Li_BIT4_DATA_BYTE_SEL_MSK (0x00080000)
  #define HUBS_CR_VISA_XBAR_SABHUB1S_I_HUBS_FXB_Li_BIT4_DATA_BYTE_SEL_MIN (0)
  #define HUBS_CR_VISA_XBAR_SABHUB1S_I_HUBS_FXB_Li_BIT4_DATA_BYTE_SEL_MAX (1) // 0x00000001
  #define HUBS_CR_VISA_XBAR_SABHUB1S_I_HUBS_FXB_Li_BIT4_DATA_BYTE_SEL_DEF (0x00000000)
  #define HUBS_CR_VISA_XBAR_SABHUB1S_I_HUBS_FXB_Li_BIT4_DATA_BYTE_SEL_HSH (0x011371A0)

  #define HUBS_CR_VISA_XBAR_SABHUB1S_I_HUBS_FXB_Li_BIT5_DATA_BIT_SEL_OFF (20)
  #define HUBS_CR_VISA_XBAR_SABHUB1S_I_HUBS_FXB_Li_BIT5_DATA_BIT_SEL_WID ( 3)
  #define HUBS_CR_VISA_XBAR_SABHUB1S_I_HUBS_FXB_Li_BIT5_DATA_BIT_SEL_MSK (0x00700000)
  #define HUBS_CR_VISA_XBAR_SABHUB1S_I_HUBS_FXB_Li_BIT5_DATA_BIT_SEL_MIN (0)
  #define HUBS_CR_VISA_XBAR_SABHUB1S_I_HUBS_FXB_Li_BIT5_DATA_BIT_SEL_MAX (7) // 0x00000007
  #define HUBS_CR_VISA_XBAR_SABHUB1S_I_HUBS_FXB_Li_BIT5_DATA_BIT_SEL_DEF (0x00000005)
  #define HUBS_CR_VISA_XBAR_SABHUB1S_I_HUBS_FXB_Li_BIT5_DATA_BIT_SEL_HSH (0x031471A0)

  #define HUBS_CR_VISA_XBAR_SABHUB1S_I_HUBS_FXB_Li_BIT5_DATA_BYTE_SEL_OFF (23)
  #define HUBS_CR_VISA_XBAR_SABHUB1S_I_HUBS_FXB_Li_BIT5_DATA_BYTE_SEL_WID ( 1)
  #define HUBS_CR_VISA_XBAR_SABHUB1S_I_HUBS_FXB_Li_BIT5_DATA_BYTE_SEL_MSK (0x00800000)
  #define HUBS_CR_VISA_XBAR_SABHUB1S_I_HUBS_FXB_Li_BIT5_DATA_BYTE_SEL_MIN (0)
  #define HUBS_CR_VISA_XBAR_SABHUB1S_I_HUBS_FXB_Li_BIT5_DATA_BYTE_SEL_MAX (1) // 0x00000001
  #define HUBS_CR_VISA_XBAR_SABHUB1S_I_HUBS_FXB_Li_BIT5_DATA_BYTE_SEL_DEF (0x00000000)
  #define HUBS_CR_VISA_XBAR_SABHUB1S_I_HUBS_FXB_Li_BIT5_DATA_BYTE_SEL_HSH (0x011771A0)

  #define HUBS_CR_VISA_XBAR_SABHUB1S_I_HUBS_FXB_Li_BIT6_DATA_BIT_SEL_OFF (24)
  #define HUBS_CR_VISA_XBAR_SABHUB1S_I_HUBS_FXB_Li_BIT6_DATA_BIT_SEL_WID ( 3)
  #define HUBS_CR_VISA_XBAR_SABHUB1S_I_HUBS_FXB_Li_BIT6_DATA_BIT_SEL_MSK (0x07000000)
  #define HUBS_CR_VISA_XBAR_SABHUB1S_I_HUBS_FXB_Li_BIT6_DATA_BIT_SEL_MIN (0)
  #define HUBS_CR_VISA_XBAR_SABHUB1S_I_HUBS_FXB_Li_BIT6_DATA_BIT_SEL_MAX (7) // 0x00000007
  #define HUBS_CR_VISA_XBAR_SABHUB1S_I_HUBS_FXB_Li_BIT6_DATA_BIT_SEL_DEF (0x00000006)
  #define HUBS_CR_VISA_XBAR_SABHUB1S_I_HUBS_FXB_Li_BIT6_DATA_BIT_SEL_HSH (0x031871A0)

  #define HUBS_CR_VISA_XBAR_SABHUB1S_I_HUBS_FXB_Li_BIT6_DATA_BYTE_SEL_OFF (27)
  #define HUBS_CR_VISA_XBAR_SABHUB1S_I_HUBS_FXB_Li_BIT6_DATA_BYTE_SEL_WID ( 1)
  #define HUBS_CR_VISA_XBAR_SABHUB1S_I_HUBS_FXB_Li_BIT6_DATA_BYTE_SEL_MSK (0x08000000)
  #define HUBS_CR_VISA_XBAR_SABHUB1S_I_HUBS_FXB_Li_BIT6_DATA_BYTE_SEL_MIN (0)
  #define HUBS_CR_VISA_XBAR_SABHUB1S_I_HUBS_FXB_Li_BIT6_DATA_BYTE_SEL_MAX (1) // 0x00000001
  #define HUBS_CR_VISA_XBAR_SABHUB1S_I_HUBS_FXB_Li_BIT6_DATA_BYTE_SEL_DEF (0x00000000)
  #define HUBS_CR_VISA_XBAR_SABHUB1S_I_HUBS_FXB_Li_BIT6_DATA_BYTE_SEL_HSH (0x011B71A0)

  #define HUBS_CR_VISA_XBAR_SABHUB1S_I_HUBS_FXB_Li_BIT7_DATA_BIT_SEL_OFF (28)
  #define HUBS_CR_VISA_XBAR_SABHUB1S_I_HUBS_FXB_Li_BIT7_DATA_BIT_SEL_WID ( 3)
  #define HUBS_CR_VISA_XBAR_SABHUB1S_I_HUBS_FXB_Li_BIT7_DATA_BIT_SEL_MSK (0x70000000)
  #define HUBS_CR_VISA_XBAR_SABHUB1S_I_HUBS_FXB_Li_BIT7_DATA_BIT_SEL_MIN (0)
  #define HUBS_CR_VISA_XBAR_SABHUB1S_I_HUBS_FXB_Li_BIT7_DATA_BIT_SEL_MAX (7) // 0x00000007
  #define HUBS_CR_VISA_XBAR_SABHUB1S_I_HUBS_FXB_Li_BIT7_DATA_BIT_SEL_DEF (0x00000007)
  #define HUBS_CR_VISA_XBAR_SABHUB1S_I_HUBS_FXB_Li_BIT7_DATA_BIT_SEL_HSH (0x031C71A0)

  #define HUBS_CR_VISA_XBAR_SABHUB1S_I_HUBS_FXB_Li_BIT7_DATA_BYTE_SEL_OFF (31)
  #define HUBS_CR_VISA_XBAR_SABHUB1S_I_HUBS_FXB_Li_BIT7_DATA_BYTE_SEL_WID ( 1)
  #define HUBS_CR_VISA_XBAR_SABHUB1S_I_HUBS_FXB_Li_BIT7_DATA_BYTE_SEL_MSK (0x80000000)
  #define HUBS_CR_VISA_XBAR_SABHUB1S_I_HUBS_FXB_Li_BIT7_DATA_BYTE_SEL_MIN (0)
  #define HUBS_CR_VISA_XBAR_SABHUB1S_I_HUBS_FXB_Li_BIT7_DATA_BYTE_SEL_MAX (1) // 0x00000001
  #define HUBS_CR_VISA_XBAR_SABHUB1S_I_HUBS_FXB_Li_BIT7_DATA_BYTE_SEL_DEF (0x00000000)
  #define HUBS_CR_VISA_XBAR_SABHUB1S_I_HUBS_FXB_Li_BIT7_DATA_BYTE_SEL_HSH (0x011F71A0)

#define HUBS_CR_VISA_CTL_SABHUB0S_I_HUBS_REG                           (0x000071A4)

  #define HUBS_CR_VISA_CTL_SABHUB0S_I_HUBS_EN_CLK_OFF                  ( 0)
  #define HUBS_CR_VISA_CTL_SABHUB0S_I_HUBS_EN_CLK_WID                  ( 1)
  #define HUBS_CR_VISA_CTL_SABHUB0S_I_HUBS_EN_CLK_MSK                  (0x00000001)
  #define HUBS_CR_VISA_CTL_SABHUB0S_I_HUBS_EN_CLK_MIN                  (0)
  #define HUBS_CR_VISA_CTL_SABHUB0S_I_HUBS_EN_CLK_MAX                  (1) // 0x00000001
  #define HUBS_CR_VISA_CTL_SABHUB0S_I_HUBS_EN_CLK_DEF                  (0x00000000)
  #define HUBS_CR_VISA_CTL_SABHUB0S_I_HUBS_EN_CLK_HSH                  (0x010071A4)

  #define HUBS_CR_VISA_CTL_SABHUB0S_I_HUBS_L0_DATA_BYTE_SEL_OFF        ( 1)
  #define HUBS_CR_VISA_CTL_SABHUB0S_I_HUBS_L0_DATA_BYTE_SEL_WID        ( 7)
  #define HUBS_CR_VISA_CTL_SABHUB0S_I_HUBS_L0_DATA_BYTE_SEL_MSK        (0x000000FE)
  #define HUBS_CR_VISA_CTL_SABHUB0S_I_HUBS_L0_DATA_BYTE_SEL_MIN        (0)
  #define HUBS_CR_VISA_CTL_SABHUB0S_I_HUBS_L0_DATA_BYTE_SEL_MAX        (127) // 0x0000007F
  #define HUBS_CR_VISA_CTL_SABHUB0S_I_HUBS_L0_DATA_BYTE_SEL_DEF        (0x00000000)
  #define HUBS_CR_VISA_CTL_SABHUB0S_I_HUBS_L0_DATA_BYTE_SEL_HSH        (0x070171A4)

  #define HUBS_CR_VISA_CTL_SABHUB0S_I_HUBS_L0_BYP_SEL_OFF              ( 8)
  #define HUBS_CR_VISA_CTL_SABHUB0S_I_HUBS_L0_BYP_SEL_WID              ( 1)
  #define HUBS_CR_VISA_CTL_SABHUB0S_I_HUBS_L0_BYP_SEL_MSK              (0x00000100)
  #define HUBS_CR_VISA_CTL_SABHUB0S_I_HUBS_L0_BYP_SEL_MIN              (0)
  #define HUBS_CR_VISA_CTL_SABHUB0S_I_HUBS_L0_BYP_SEL_MAX              (1) // 0x00000001
  #define HUBS_CR_VISA_CTL_SABHUB0S_I_HUBS_L0_BYP_SEL_DEF              (0x00000000)
  #define HUBS_CR_VISA_CTL_SABHUB0S_I_HUBS_L0_BYP_SEL_HSH              (0x010871A4)

  #define HUBS_CR_VISA_CTL_SABHUB0S_I_HUBS_L1_DATA_BYTE_SEL_OFF        ( 9)
  #define HUBS_CR_VISA_CTL_SABHUB0S_I_HUBS_L1_DATA_BYTE_SEL_WID        ( 7)
  #define HUBS_CR_VISA_CTL_SABHUB0S_I_HUBS_L1_DATA_BYTE_SEL_MSK        (0x0000FE00)
  #define HUBS_CR_VISA_CTL_SABHUB0S_I_HUBS_L1_DATA_BYTE_SEL_MIN        (0)
  #define HUBS_CR_VISA_CTL_SABHUB0S_I_HUBS_L1_DATA_BYTE_SEL_MAX        (127) // 0x0000007F
  #define HUBS_CR_VISA_CTL_SABHUB0S_I_HUBS_L1_DATA_BYTE_SEL_DEF        (0x00000000)
  #define HUBS_CR_VISA_CTL_SABHUB0S_I_HUBS_L1_DATA_BYTE_SEL_HSH        (0x070971A4)

  #define HUBS_CR_VISA_CTL_SABHUB0S_I_HUBS_L1_BYP_SEL_OFF              (16)
  #define HUBS_CR_VISA_CTL_SABHUB0S_I_HUBS_L1_BYP_SEL_WID              ( 1)
  #define HUBS_CR_VISA_CTL_SABHUB0S_I_HUBS_L1_BYP_SEL_MSK              (0x00010000)
  #define HUBS_CR_VISA_CTL_SABHUB0S_I_HUBS_L1_BYP_SEL_MIN              (0)
  #define HUBS_CR_VISA_CTL_SABHUB0S_I_HUBS_L1_BYP_SEL_MAX              (1) // 0x00000001
  #define HUBS_CR_VISA_CTL_SABHUB0S_I_HUBS_L1_BYP_SEL_DEF              (0x00000000)
  #define HUBS_CR_VISA_CTL_SABHUB0S_I_HUBS_L1_BYP_SEL_HSH              (0x011071A4)

  #define HUBS_CR_VISA_CTL_SABHUB0S_I_HUBS_VORANGE_OFF                 (31)
  #define HUBS_CR_VISA_CTL_SABHUB0S_I_HUBS_VORANGE_WID                 ( 1)
  #define HUBS_CR_VISA_CTL_SABHUB0S_I_HUBS_VORANGE_MSK                 (0x80000000)
  #define HUBS_CR_VISA_CTL_SABHUB0S_I_HUBS_VORANGE_MIN                 (0)
  #define HUBS_CR_VISA_CTL_SABHUB0S_I_HUBS_VORANGE_MAX                 (1) // 0x00000001
  #define HUBS_CR_VISA_CTL_SABHUB0S_I_HUBS_VORANGE_DEF                 (0x00000000)
  #define HUBS_CR_VISA_CTL_SABHUB0S_I_HUBS_VORANGE_HSH                 (0x011F71A4)

#define HUBS_CR_VISA_SLIDE_SABHUB0S_I_HUBS_REG                         (0x000071A8)

  #define HUBS_CR_VISA_SLIDE_SABHUB0S_I_HUBS_WINDOW_SLIDE_L0_OFF       ( 0)
  #define HUBS_CR_VISA_SLIDE_SABHUB0S_I_HUBS_WINDOW_SLIDE_L0_WID       ( 3)
  #define HUBS_CR_VISA_SLIDE_SABHUB0S_I_HUBS_WINDOW_SLIDE_L0_MSK       (0x00000007)
  #define HUBS_CR_VISA_SLIDE_SABHUB0S_I_HUBS_WINDOW_SLIDE_L0_MIN       (0)
  #define HUBS_CR_VISA_SLIDE_SABHUB0S_I_HUBS_WINDOW_SLIDE_L0_MAX       (7) // 0x00000007
  #define HUBS_CR_VISA_SLIDE_SABHUB0S_I_HUBS_WINDOW_SLIDE_L0_DEF       (0x00000000)
  #define HUBS_CR_VISA_SLIDE_SABHUB0S_I_HUBS_WINDOW_SLIDE_L0_HSH       (0x030071A8)

  #define HUBS_CR_VISA_SLIDE_SABHUB0S_I_HUBS_ALT_L0_DATA_BYTE_SEL_OFF  ( 3)
  #define HUBS_CR_VISA_SLIDE_SABHUB0S_I_HUBS_ALT_L0_DATA_BYTE_SEL_WID  ( 7)
  #define HUBS_CR_VISA_SLIDE_SABHUB0S_I_HUBS_ALT_L0_DATA_BYTE_SEL_MSK  (0x000003F8)
  #define HUBS_CR_VISA_SLIDE_SABHUB0S_I_HUBS_ALT_L0_DATA_BYTE_SEL_MIN  (0)
  #define HUBS_CR_VISA_SLIDE_SABHUB0S_I_HUBS_ALT_L0_DATA_BYTE_SEL_MAX  (127) // 0x0000007F
  #define HUBS_CR_VISA_SLIDE_SABHUB0S_I_HUBS_ALT_L0_DATA_BYTE_SEL_DEF  (0x00000000)
  #define HUBS_CR_VISA_SLIDE_SABHUB0S_I_HUBS_ALT_L0_DATA_BYTE_SEL_HSH  (0x070371A8)

  #define HUBS_CR_VISA_SLIDE_SABHUB0S_I_HUBS_WINDOW_SLIDE_L1_OFF       (10)
  #define HUBS_CR_VISA_SLIDE_SABHUB0S_I_HUBS_WINDOW_SLIDE_L1_WID       ( 3)
  #define HUBS_CR_VISA_SLIDE_SABHUB0S_I_HUBS_WINDOW_SLIDE_L1_MSK       (0x00001C00)
  #define HUBS_CR_VISA_SLIDE_SABHUB0S_I_HUBS_WINDOW_SLIDE_L1_MIN       (0)
  #define HUBS_CR_VISA_SLIDE_SABHUB0S_I_HUBS_WINDOW_SLIDE_L1_MAX       (7) // 0x00000007
  #define HUBS_CR_VISA_SLIDE_SABHUB0S_I_HUBS_WINDOW_SLIDE_L1_DEF       (0x00000000)
  #define HUBS_CR_VISA_SLIDE_SABHUB0S_I_HUBS_WINDOW_SLIDE_L1_HSH       (0x030A71A8)

  #define HUBS_CR_VISA_SLIDE_SABHUB0S_I_HUBS_ALT_L1_DATA_BYTE_SEL_OFF  (13)
  #define HUBS_CR_VISA_SLIDE_SABHUB0S_I_HUBS_ALT_L1_DATA_BYTE_SEL_WID  ( 7)
  #define HUBS_CR_VISA_SLIDE_SABHUB0S_I_HUBS_ALT_L1_DATA_BYTE_SEL_MSK  (0x000FE000)
  #define HUBS_CR_VISA_SLIDE_SABHUB0S_I_HUBS_ALT_L1_DATA_BYTE_SEL_MIN  (0)
  #define HUBS_CR_VISA_SLIDE_SABHUB0S_I_HUBS_ALT_L1_DATA_BYTE_SEL_MAX  (127) // 0x0000007F
  #define HUBS_CR_VISA_SLIDE_SABHUB0S_I_HUBS_ALT_L1_DATA_BYTE_SEL_DEF  (0x00000000)
  #define HUBS_CR_VISA_SLIDE_SABHUB0S_I_HUBS_ALT_L1_DATA_BYTE_SEL_HSH  (0x070D71A8)

#define HUBS_CR_VISA_XBAR_SABHUB0S_I_HUBS_REG                          (0x000071AC)

  #define HUBS_CR_VISA_XBAR_SABHUB0S_I_HUBS_FXB_Li_BIT0_DATA_BIT_SEL_OFF ( 0)
  #define HUBS_CR_VISA_XBAR_SABHUB0S_I_HUBS_FXB_Li_BIT0_DATA_BIT_SEL_WID ( 3)
  #define HUBS_CR_VISA_XBAR_SABHUB0S_I_HUBS_FXB_Li_BIT0_DATA_BIT_SEL_MSK (0x00000007)
  #define HUBS_CR_VISA_XBAR_SABHUB0S_I_HUBS_FXB_Li_BIT0_DATA_BIT_SEL_MIN (0)
  #define HUBS_CR_VISA_XBAR_SABHUB0S_I_HUBS_FXB_Li_BIT0_DATA_BIT_SEL_MAX (7) // 0x00000007
  #define HUBS_CR_VISA_XBAR_SABHUB0S_I_HUBS_FXB_Li_BIT0_DATA_BIT_SEL_DEF (0x00000000)
  #define HUBS_CR_VISA_XBAR_SABHUB0S_I_HUBS_FXB_Li_BIT0_DATA_BIT_SEL_HSH (0x030071AC)

  #define HUBS_CR_VISA_XBAR_SABHUB0S_I_HUBS_FXB_Li_BIT0_DATA_BYTE_SEL_OFF ( 3)
  #define HUBS_CR_VISA_XBAR_SABHUB0S_I_HUBS_FXB_Li_BIT0_DATA_BYTE_SEL_WID ( 1)
  #define HUBS_CR_VISA_XBAR_SABHUB0S_I_HUBS_FXB_Li_BIT0_DATA_BYTE_SEL_MSK (0x00000008)
  #define HUBS_CR_VISA_XBAR_SABHUB0S_I_HUBS_FXB_Li_BIT0_DATA_BYTE_SEL_MIN (0)
  #define HUBS_CR_VISA_XBAR_SABHUB0S_I_HUBS_FXB_Li_BIT0_DATA_BYTE_SEL_MAX (1) // 0x00000001
  #define HUBS_CR_VISA_XBAR_SABHUB0S_I_HUBS_FXB_Li_BIT0_DATA_BYTE_SEL_DEF (0x00000000)
  #define HUBS_CR_VISA_XBAR_SABHUB0S_I_HUBS_FXB_Li_BIT0_DATA_BYTE_SEL_HSH (0x010371AC)

  #define HUBS_CR_VISA_XBAR_SABHUB0S_I_HUBS_FXB_Li_BIT1_DATA_BIT_SEL_OFF ( 4)
  #define HUBS_CR_VISA_XBAR_SABHUB0S_I_HUBS_FXB_Li_BIT1_DATA_BIT_SEL_WID ( 3)
  #define HUBS_CR_VISA_XBAR_SABHUB0S_I_HUBS_FXB_Li_BIT1_DATA_BIT_SEL_MSK (0x00000070)
  #define HUBS_CR_VISA_XBAR_SABHUB0S_I_HUBS_FXB_Li_BIT1_DATA_BIT_SEL_MIN (0)
  #define HUBS_CR_VISA_XBAR_SABHUB0S_I_HUBS_FXB_Li_BIT1_DATA_BIT_SEL_MAX (7) // 0x00000007
  #define HUBS_CR_VISA_XBAR_SABHUB0S_I_HUBS_FXB_Li_BIT1_DATA_BIT_SEL_DEF (0x00000001)
  #define HUBS_CR_VISA_XBAR_SABHUB0S_I_HUBS_FXB_Li_BIT1_DATA_BIT_SEL_HSH (0x030471AC)

  #define HUBS_CR_VISA_XBAR_SABHUB0S_I_HUBS_FXB_Li_BIT1_DATA_BYTE_SEL_OFF ( 7)
  #define HUBS_CR_VISA_XBAR_SABHUB0S_I_HUBS_FXB_Li_BIT1_DATA_BYTE_SEL_WID ( 1)
  #define HUBS_CR_VISA_XBAR_SABHUB0S_I_HUBS_FXB_Li_BIT1_DATA_BYTE_SEL_MSK (0x00000080)
  #define HUBS_CR_VISA_XBAR_SABHUB0S_I_HUBS_FXB_Li_BIT1_DATA_BYTE_SEL_MIN (0)
  #define HUBS_CR_VISA_XBAR_SABHUB0S_I_HUBS_FXB_Li_BIT1_DATA_BYTE_SEL_MAX (1) // 0x00000001
  #define HUBS_CR_VISA_XBAR_SABHUB0S_I_HUBS_FXB_Li_BIT1_DATA_BYTE_SEL_DEF (0x00000000)
  #define HUBS_CR_VISA_XBAR_SABHUB0S_I_HUBS_FXB_Li_BIT1_DATA_BYTE_SEL_HSH (0x010771AC)

  #define HUBS_CR_VISA_XBAR_SABHUB0S_I_HUBS_FXB_Li_BIT2_DATA_BIT_SEL_OFF ( 8)
  #define HUBS_CR_VISA_XBAR_SABHUB0S_I_HUBS_FXB_Li_BIT2_DATA_BIT_SEL_WID ( 3)
  #define HUBS_CR_VISA_XBAR_SABHUB0S_I_HUBS_FXB_Li_BIT2_DATA_BIT_SEL_MSK (0x00000700)
  #define HUBS_CR_VISA_XBAR_SABHUB0S_I_HUBS_FXB_Li_BIT2_DATA_BIT_SEL_MIN (0)
  #define HUBS_CR_VISA_XBAR_SABHUB0S_I_HUBS_FXB_Li_BIT2_DATA_BIT_SEL_MAX (7) // 0x00000007
  #define HUBS_CR_VISA_XBAR_SABHUB0S_I_HUBS_FXB_Li_BIT2_DATA_BIT_SEL_DEF (0x00000002)
  #define HUBS_CR_VISA_XBAR_SABHUB0S_I_HUBS_FXB_Li_BIT2_DATA_BIT_SEL_HSH (0x030871AC)

  #define HUBS_CR_VISA_XBAR_SABHUB0S_I_HUBS_FXB_Li_BIT2_DATA_BYTE_SEL_OFF (11)
  #define HUBS_CR_VISA_XBAR_SABHUB0S_I_HUBS_FXB_Li_BIT2_DATA_BYTE_SEL_WID ( 1)
  #define HUBS_CR_VISA_XBAR_SABHUB0S_I_HUBS_FXB_Li_BIT2_DATA_BYTE_SEL_MSK (0x00000800)
  #define HUBS_CR_VISA_XBAR_SABHUB0S_I_HUBS_FXB_Li_BIT2_DATA_BYTE_SEL_MIN (0)
  #define HUBS_CR_VISA_XBAR_SABHUB0S_I_HUBS_FXB_Li_BIT2_DATA_BYTE_SEL_MAX (1) // 0x00000001
  #define HUBS_CR_VISA_XBAR_SABHUB0S_I_HUBS_FXB_Li_BIT2_DATA_BYTE_SEL_DEF (0x00000000)
  #define HUBS_CR_VISA_XBAR_SABHUB0S_I_HUBS_FXB_Li_BIT2_DATA_BYTE_SEL_HSH (0x010B71AC)

  #define HUBS_CR_VISA_XBAR_SABHUB0S_I_HUBS_FXB_Li_BIT3_DATA_BIT_SEL_OFF (12)
  #define HUBS_CR_VISA_XBAR_SABHUB0S_I_HUBS_FXB_Li_BIT3_DATA_BIT_SEL_WID ( 3)
  #define HUBS_CR_VISA_XBAR_SABHUB0S_I_HUBS_FXB_Li_BIT3_DATA_BIT_SEL_MSK (0x00007000)
  #define HUBS_CR_VISA_XBAR_SABHUB0S_I_HUBS_FXB_Li_BIT3_DATA_BIT_SEL_MIN (0)
  #define HUBS_CR_VISA_XBAR_SABHUB0S_I_HUBS_FXB_Li_BIT3_DATA_BIT_SEL_MAX (7) // 0x00000007
  #define HUBS_CR_VISA_XBAR_SABHUB0S_I_HUBS_FXB_Li_BIT3_DATA_BIT_SEL_DEF (0x00000003)
  #define HUBS_CR_VISA_XBAR_SABHUB0S_I_HUBS_FXB_Li_BIT3_DATA_BIT_SEL_HSH (0x030C71AC)

  #define HUBS_CR_VISA_XBAR_SABHUB0S_I_HUBS_FXB_Li_BIT3_DATA_BYTE_SEL_OFF (15)
  #define HUBS_CR_VISA_XBAR_SABHUB0S_I_HUBS_FXB_Li_BIT3_DATA_BYTE_SEL_WID ( 1)
  #define HUBS_CR_VISA_XBAR_SABHUB0S_I_HUBS_FXB_Li_BIT3_DATA_BYTE_SEL_MSK (0x00008000)
  #define HUBS_CR_VISA_XBAR_SABHUB0S_I_HUBS_FXB_Li_BIT3_DATA_BYTE_SEL_MIN (0)
  #define HUBS_CR_VISA_XBAR_SABHUB0S_I_HUBS_FXB_Li_BIT3_DATA_BYTE_SEL_MAX (1) // 0x00000001
  #define HUBS_CR_VISA_XBAR_SABHUB0S_I_HUBS_FXB_Li_BIT3_DATA_BYTE_SEL_DEF (0x00000000)
  #define HUBS_CR_VISA_XBAR_SABHUB0S_I_HUBS_FXB_Li_BIT3_DATA_BYTE_SEL_HSH (0x010F71AC)

  #define HUBS_CR_VISA_XBAR_SABHUB0S_I_HUBS_FXB_Li_BIT4_DATA_BIT_SEL_OFF (16)
  #define HUBS_CR_VISA_XBAR_SABHUB0S_I_HUBS_FXB_Li_BIT4_DATA_BIT_SEL_WID ( 3)
  #define HUBS_CR_VISA_XBAR_SABHUB0S_I_HUBS_FXB_Li_BIT4_DATA_BIT_SEL_MSK (0x00070000)
  #define HUBS_CR_VISA_XBAR_SABHUB0S_I_HUBS_FXB_Li_BIT4_DATA_BIT_SEL_MIN (0)
  #define HUBS_CR_VISA_XBAR_SABHUB0S_I_HUBS_FXB_Li_BIT4_DATA_BIT_SEL_MAX (7) // 0x00000007
  #define HUBS_CR_VISA_XBAR_SABHUB0S_I_HUBS_FXB_Li_BIT4_DATA_BIT_SEL_DEF (0x00000004)
  #define HUBS_CR_VISA_XBAR_SABHUB0S_I_HUBS_FXB_Li_BIT4_DATA_BIT_SEL_HSH (0x031071AC)

  #define HUBS_CR_VISA_XBAR_SABHUB0S_I_HUBS_FXB_Li_BIT4_DATA_BYTE_SEL_OFF (19)
  #define HUBS_CR_VISA_XBAR_SABHUB0S_I_HUBS_FXB_Li_BIT4_DATA_BYTE_SEL_WID ( 1)
  #define HUBS_CR_VISA_XBAR_SABHUB0S_I_HUBS_FXB_Li_BIT4_DATA_BYTE_SEL_MSK (0x00080000)
  #define HUBS_CR_VISA_XBAR_SABHUB0S_I_HUBS_FXB_Li_BIT4_DATA_BYTE_SEL_MIN (0)
  #define HUBS_CR_VISA_XBAR_SABHUB0S_I_HUBS_FXB_Li_BIT4_DATA_BYTE_SEL_MAX (1) // 0x00000001
  #define HUBS_CR_VISA_XBAR_SABHUB0S_I_HUBS_FXB_Li_BIT4_DATA_BYTE_SEL_DEF (0x00000000)
  #define HUBS_CR_VISA_XBAR_SABHUB0S_I_HUBS_FXB_Li_BIT4_DATA_BYTE_SEL_HSH (0x011371AC)

  #define HUBS_CR_VISA_XBAR_SABHUB0S_I_HUBS_FXB_Li_BIT5_DATA_BIT_SEL_OFF (20)
  #define HUBS_CR_VISA_XBAR_SABHUB0S_I_HUBS_FXB_Li_BIT5_DATA_BIT_SEL_WID ( 3)
  #define HUBS_CR_VISA_XBAR_SABHUB0S_I_HUBS_FXB_Li_BIT5_DATA_BIT_SEL_MSK (0x00700000)
  #define HUBS_CR_VISA_XBAR_SABHUB0S_I_HUBS_FXB_Li_BIT5_DATA_BIT_SEL_MIN (0)
  #define HUBS_CR_VISA_XBAR_SABHUB0S_I_HUBS_FXB_Li_BIT5_DATA_BIT_SEL_MAX (7) // 0x00000007
  #define HUBS_CR_VISA_XBAR_SABHUB0S_I_HUBS_FXB_Li_BIT5_DATA_BIT_SEL_DEF (0x00000005)
  #define HUBS_CR_VISA_XBAR_SABHUB0S_I_HUBS_FXB_Li_BIT5_DATA_BIT_SEL_HSH (0x031471AC)

  #define HUBS_CR_VISA_XBAR_SABHUB0S_I_HUBS_FXB_Li_BIT5_DATA_BYTE_SEL_OFF (23)
  #define HUBS_CR_VISA_XBAR_SABHUB0S_I_HUBS_FXB_Li_BIT5_DATA_BYTE_SEL_WID ( 1)
  #define HUBS_CR_VISA_XBAR_SABHUB0S_I_HUBS_FXB_Li_BIT5_DATA_BYTE_SEL_MSK (0x00800000)
  #define HUBS_CR_VISA_XBAR_SABHUB0S_I_HUBS_FXB_Li_BIT5_DATA_BYTE_SEL_MIN (0)
  #define HUBS_CR_VISA_XBAR_SABHUB0S_I_HUBS_FXB_Li_BIT5_DATA_BYTE_SEL_MAX (1) // 0x00000001
  #define HUBS_CR_VISA_XBAR_SABHUB0S_I_HUBS_FXB_Li_BIT5_DATA_BYTE_SEL_DEF (0x00000000)
  #define HUBS_CR_VISA_XBAR_SABHUB0S_I_HUBS_FXB_Li_BIT5_DATA_BYTE_SEL_HSH (0x011771AC)

  #define HUBS_CR_VISA_XBAR_SABHUB0S_I_HUBS_FXB_Li_BIT6_DATA_BIT_SEL_OFF (24)
  #define HUBS_CR_VISA_XBAR_SABHUB0S_I_HUBS_FXB_Li_BIT6_DATA_BIT_SEL_WID ( 3)
  #define HUBS_CR_VISA_XBAR_SABHUB0S_I_HUBS_FXB_Li_BIT6_DATA_BIT_SEL_MSK (0x07000000)
  #define HUBS_CR_VISA_XBAR_SABHUB0S_I_HUBS_FXB_Li_BIT6_DATA_BIT_SEL_MIN (0)
  #define HUBS_CR_VISA_XBAR_SABHUB0S_I_HUBS_FXB_Li_BIT6_DATA_BIT_SEL_MAX (7) // 0x00000007
  #define HUBS_CR_VISA_XBAR_SABHUB0S_I_HUBS_FXB_Li_BIT6_DATA_BIT_SEL_DEF (0x00000006)
  #define HUBS_CR_VISA_XBAR_SABHUB0S_I_HUBS_FXB_Li_BIT6_DATA_BIT_SEL_HSH (0x031871AC)

  #define HUBS_CR_VISA_XBAR_SABHUB0S_I_HUBS_FXB_Li_BIT6_DATA_BYTE_SEL_OFF (27)
  #define HUBS_CR_VISA_XBAR_SABHUB0S_I_HUBS_FXB_Li_BIT6_DATA_BYTE_SEL_WID ( 1)
  #define HUBS_CR_VISA_XBAR_SABHUB0S_I_HUBS_FXB_Li_BIT6_DATA_BYTE_SEL_MSK (0x08000000)
  #define HUBS_CR_VISA_XBAR_SABHUB0S_I_HUBS_FXB_Li_BIT6_DATA_BYTE_SEL_MIN (0)
  #define HUBS_CR_VISA_XBAR_SABHUB0S_I_HUBS_FXB_Li_BIT6_DATA_BYTE_SEL_MAX (1) // 0x00000001
  #define HUBS_CR_VISA_XBAR_SABHUB0S_I_HUBS_FXB_Li_BIT6_DATA_BYTE_SEL_DEF (0x00000000)
  #define HUBS_CR_VISA_XBAR_SABHUB0S_I_HUBS_FXB_Li_BIT6_DATA_BYTE_SEL_HSH (0x011B71AC)

  #define HUBS_CR_VISA_XBAR_SABHUB0S_I_HUBS_FXB_Li_BIT7_DATA_BIT_SEL_OFF (28)
  #define HUBS_CR_VISA_XBAR_SABHUB0S_I_HUBS_FXB_Li_BIT7_DATA_BIT_SEL_WID ( 3)
  #define HUBS_CR_VISA_XBAR_SABHUB0S_I_HUBS_FXB_Li_BIT7_DATA_BIT_SEL_MSK (0x70000000)
  #define HUBS_CR_VISA_XBAR_SABHUB0S_I_HUBS_FXB_Li_BIT7_DATA_BIT_SEL_MIN (0)
  #define HUBS_CR_VISA_XBAR_SABHUB0S_I_HUBS_FXB_Li_BIT7_DATA_BIT_SEL_MAX (7) // 0x00000007
  #define HUBS_CR_VISA_XBAR_SABHUB0S_I_HUBS_FXB_Li_BIT7_DATA_BIT_SEL_DEF (0x00000007)
  #define HUBS_CR_VISA_XBAR_SABHUB0S_I_HUBS_FXB_Li_BIT7_DATA_BIT_SEL_HSH (0x031C71AC)

  #define HUBS_CR_VISA_XBAR_SABHUB0S_I_HUBS_FXB_Li_BIT7_DATA_BYTE_SEL_OFF (31)
  #define HUBS_CR_VISA_XBAR_SABHUB0S_I_HUBS_FXB_Li_BIT7_DATA_BYTE_SEL_WID ( 1)
  #define HUBS_CR_VISA_XBAR_SABHUB0S_I_HUBS_FXB_Li_BIT7_DATA_BYTE_SEL_MSK (0x80000000)
  #define HUBS_CR_VISA_XBAR_SABHUB0S_I_HUBS_FXB_Li_BIT7_DATA_BYTE_SEL_MIN (0)
  #define HUBS_CR_VISA_XBAR_SABHUB0S_I_HUBS_FXB_Li_BIT7_DATA_BYTE_SEL_MAX (1) // 0x00000001
  #define HUBS_CR_VISA_XBAR_SABHUB0S_I_HUBS_FXB_Li_BIT7_DATA_BYTE_SEL_DEF (0x00000000)
  #define HUBS_CR_VISA_XBAR_SABHUB0S_I_HUBS_FXB_Li_BIT7_DATA_BYTE_SEL_HSH (0x011F71AC)

#define HUBS_CR_VISA_CTL_SABHUB1S_I_HUBS_REG                           (0x000071B0)

  #define HUBS_CR_VISA_CTL_SABHUB1S_I_HUBS_EN_CLK_OFF                  ( 0)
  #define HUBS_CR_VISA_CTL_SABHUB1S_I_HUBS_EN_CLK_WID                  ( 1)
  #define HUBS_CR_VISA_CTL_SABHUB1S_I_HUBS_EN_CLK_MSK                  (0x00000001)
  #define HUBS_CR_VISA_CTL_SABHUB1S_I_HUBS_EN_CLK_MIN                  (0)
  #define HUBS_CR_VISA_CTL_SABHUB1S_I_HUBS_EN_CLK_MAX                  (1) // 0x00000001
  #define HUBS_CR_VISA_CTL_SABHUB1S_I_HUBS_EN_CLK_DEF                  (0x00000000)
  #define HUBS_CR_VISA_CTL_SABHUB1S_I_HUBS_EN_CLK_HSH                  (0x010071B0)

  #define HUBS_CR_VISA_CTL_SABHUB1S_I_HUBS_L0_DATA_BYTE_SEL_OFF        ( 1)
  #define HUBS_CR_VISA_CTL_SABHUB1S_I_HUBS_L0_DATA_BYTE_SEL_WID        ( 7)
  #define HUBS_CR_VISA_CTL_SABHUB1S_I_HUBS_L0_DATA_BYTE_SEL_MSK        (0x000000FE)
  #define HUBS_CR_VISA_CTL_SABHUB1S_I_HUBS_L0_DATA_BYTE_SEL_MIN        (0)
  #define HUBS_CR_VISA_CTL_SABHUB1S_I_HUBS_L0_DATA_BYTE_SEL_MAX        (127) // 0x0000007F
  #define HUBS_CR_VISA_CTL_SABHUB1S_I_HUBS_L0_DATA_BYTE_SEL_DEF        (0x00000000)
  #define HUBS_CR_VISA_CTL_SABHUB1S_I_HUBS_L0_DATA_BYTE_SEL_HSH        (0x070171B0)

  #define HUBS_CR_VISA_CTL_SABHUB1S_I_HUBS_L0_BYP_SEL_OFF              ( 8)
  #define HUBS_CR_VISA_CTL_SABHUB1S_I_HUBS_L0_BYP_SEL_WID              ( 1)
  #define HUBS_CR_VISA_CTL_SABHUB1S_I_HUBS_L0_BYP_SEL_MSK              (0x00000100)
  #define HUBS_CR_VISA_CTL_SABHUB1S_I_HUBS_L0_BYP_SEL_MIN              (0)
  #define HUBS_CR_VISA_CTL_SABHUB1S_I_HUBS_L0_BYP_SEL_MAX              (1) // 0x00000001
  #define HUBS_CR_VISA_CTL_SABHUB1S_I_HUBS_L0_BYP_SEL_DEF              (0x00000000)
  #define HUBS_CR_VISA_CTL_SABHUB1S_I_HUBS_L0_BYP_SEL_HSH              (0x010871B0)

  #define HUBS_CR_VISA_CTL_SABHUB1S_I_HUBS_L1_DATA_BYTE_SEL_OFF        ( 9)
  #define HUBS_CR_VISA_CTL_SABHUB1S_I_HUBS_L1_DATA_BYTE_SEL_WID        ( 7)
  #define HUBS_CR_VISA_CTL_SABHUB1S_I_HUBS_L1_DATA_BYTE_SEL_MSK        (0x0000FE00)
  #define HUBS_CR_VISA_CTL_SABHUB1S_I_HUBS_L1_DATA_BYTE_SEL_MIN        (0)
  #define HUBS_CR_VISA_CTL_SABHUB1S_I_HUBS_L1_DATA_BYTE_SEL_MAX        (127) // 0x0000007F
  #define HUBS_CR_VISA_CTL_SABHUB1S_I_HUBS_L1_DATA_BYTE_SEL_DEF        (0x00000000)
  #define HUBS_CR_VISA_CTL_SABHUB1S_I_HUBS_L1_DATA_BYTE_SEL_HSH        (0x070971B0)

  #define HUBS_CR_VISA_CTL_SABHUB1S_I_HUBS_L1_BYP_SEL_OFF              (16)
  #define HUBS_CR_VISA_CTL_SABHUB1S_I_HUBS_L1_BYP_SEL_WID              ( 1)
  #define HUBS_CR_VISA_CTL_SABHUB1S_I_HUBS_L1_BYP_SEL_MSK              (0x00010000)
  #define HUBS_CR_VISA_CTL_SABHUB1S_I_HUBS_L1_BYP_SEL_MIN              (0)
  #define HUBS_CR_VISA_CTL_SABHUB1S_I_HUBS_L1_BYP_SEL_MAX              (1) // 0x00000001
  #define HUBS_CR_VISA_CTL_SABHUB1S_I_HUBS_L1_BYP_SEL_DEF              (0x00000000)
  #define HUBS_CR_VISA_CTL_SABHUB1S_I_HUBS_L1_BYP_SEL_HSH              (0x011071B0)

  #define HUBS_CR_VISA_CTL_SABHUB1S_I_HUBS_VORANGE_OFF                 (31)
  #define HUBS_CR_VISA_CTL_SABHUB1S_I_HUBS_VORANGE_WID                 ( 1)
  #define HUBS_CR_VISA_CTL_SABHUB1S_I_HUBS_VORANGE_MSK                 (0x80000000)
  #define HUBS_CR_VISA_CTL_SABHUB1S_I_HUBS_VORANGE_MIN                 (0)
  #define HUBS_CR_VISA_CTL_SABHUB1S_I_HUBS_VORANGE_MAX                 (1) // 0x00000001
  #define HUBS_CR_VISA_CTL_SABHUB1S_I_HUBS_VORANGE_DEF                 (0x00000000)
  #define HUBS_CR_VISA_CTL_SABHUB1S_I_HUBS_VORANGE_HSH                 (0x011F71B0)

#define HUBS_CR_VISA_SLIDE_SABHUB1S_I_HUBS_REG                         (0x000071B4)

  #define HUBS_CR_VISA_SLIDE_SABHUB1S_I_HUBS_WINDOW_SLIDE_L0_OFF       ( 0)
  #define HUBS_CR_VISA_SLIDE_SABHUB1S_I_HUBS_WINDOW_SLIDE_L0_WID       ( 3)
  #define HUBS_CR_VISA_SLIDE_SABHUB1S_I_HUBS_WINDOW_SLIDE_L0_MSK       (0x00000007)
  #define HUBS_CR_VISA_SLIDE_SABHUB1S_I_HUBS_WINDOW_SLIDE_L0_MIN       (0)
  #define HUBS_CR_VISA_SLIDE_SABHUB1S_I_HUBS_WINDOW_SLIDE_L0_MAX       (7) // 0x00000007
  #define HUBS_CR_VISA_SLIDE_SABHUB1S_I_HUBS_WINDOW_SLIDE_L0_DEF       (0x00000000)
  #define HUBS_CR_VISA_SLIDE_SABHUB1S_I_HUBS_WINDOW_SLIDE_L0_HSH       (0x030071B4)

  #define HUBS_CR_VISA_SLIDE_SABHUB1S_I_HUBS_ALT_L0_DATA_BYTE_SEL_OFF  ( 3)
  #define HUBS_CR_VISA_SLIDE_SABHUB1S_I_HUBS_ALT_L0_DATA_BYTE_SEL_WID  ( 7)
  #define HUBS_CR_VISA_SLIDE_SABHUB1S_I_HUBS_ALT_L0_DATA_BYTE_SEL_MSK  (0x000003F8)
  #define HUBS_CR_VISA_SLIDE_SABHUB1S_I_HUBS_ALT_L0_DATA_BYTE_SEL_MIN  (0)
  #define HUBS_CR_VISA_SLIDE_SABHUB1S_I_HUBS_ALT_L0_DATA_BYTE_SEL_MAX  (127) // 0x0000007F
  #define HUBS_CR_VISA_SLIDE_SABHUB1S_I_HUBS_ALT_L0_DATA_BYTE_SEL_DEF  (0x00000000)
  #define HUBS_CR_VISA_SLIDE_SABHUB1S_I_HUBS_ALT_L0_DATA_BYTE_SEL_HSH  (0x070371B4)

  #define HUBS_CR_VISA_SLIDE_SABHUB1S_I_HUBS_WINDOW_SLIDE_L1_OFF       (10)
  #define HUBS_CR_VISA_SLIDE_SABHUB1S_I_HUBS_WINDOW_SLIDE_L1_WID       ( 3)
  #define HUBS_CR_VISA_SLIDE_SABHUB1S_I_HUBS_WINDOW_SLIDE_L1_MSK       (0x00001C00)
  #define HUBS_CR_VISA_SLIDE_SABHUB1S_I_HUBS_WINDOW_SLIDE_L1_MIN       (0)
  #define HUBS_CR_VISA_SLIDE_SABHUB1S_I_HUBS_WINDOW_SLIDE_L1_MAX       (7) // 0x00000007
  #define HUBS_CR_VISA_SLIDE_SABHUB1S_I_HUBS_WINDOW_SLIDE_L1_DEF       (0x00000000)
  #define HUBS_CR_VISA_SLIDE_SABHUB1S_I_HUBS_WINDOW_SLIDE_L1_HSH       (0x030A71B4)

  #define HUBS_CR_VISA_SLIDE_SABHUB1S_I_HUBS_ALT_L1_DATA_BYTE_SEL_OFF  (13)
  #define HUBS_CR_VISA_SLIDE_SABHUB1S_I_HUBS_ALT_L1_DATA_BYTE_SEL_WID  ( 7)
  #define HUBS_CR_VISA_SLIDE_SABHUB1S_I_HUBS_ALT_L1_DATA_BYTE_SEL_MSK  (0x000FE000)
  #define HUBS_CR_VISA_SLIDE_SABHUB1S_I_HUBS_ALT_L1_DATA_BYTE_SEL_MIN  (0)
  #define HUBS_CR_VISA_SLIDE_SABHUB1S_I_HUBS_ALT_L1_DATA_BYTE_SEL_MAX  (127) // 0x0000007F
  #define HUBS_CR_VISA_SLIDE_SABHUB1S_I_HUBS_ALT_L1_DATA_BYTE_SEL_DEF  (0x00000000)
  #define HUBS_CR_VISA_SLIDE_SABHUB1S_I_HUBS_ALT_L1_DATA_BYTE_SEL_HSH  (0x070D71B4)

#define HUBS_CR_HUB0_UP_ARB_0_LIM_HUBS_REG                             (0x00007200)

  #define HUBS_CR_HUB0_UP_ARB_0_LIM_HUBS_DMI_VC0_NP_OFF                ( 0)
  #define HUBS_CR_HUB0_UP_ARB_0_LIM_HUBS_DMI_VC0_NP_WID                ( 3)
  #define HUBS_CR_HUB0_UP_ARB_0_LIM_HUBS_DMI_VC0_NP_MSK                (0x00000007)
  #define HUBS_CR_HUB0_UP_ARB_0_LIM_HUBS_DMI_VC0_NP_MIN                (0)
  #define HUBS_CR_HUB0_UP_ARB_0_LIM_HUBS_DMI_VC0_NP_MAX                (7) // 0x00000007
  #define HUBS_CR_HUB0_UP_ARB_0_LIM_HUBS_DMI_VC0_NP_DEF                (0x00000004)
  #define HUBS_CR_HUB0_UP_ARB_0_LIM_HUBS_DMI_VC0_NP_HSH                (0x03007200)

  #define HUBS_CR_HUB0_UP_ARB_0_LIM_HUBS_DMI_VC0_PC_OFF                ( 3)
  #define HUBS_CR_HUB0_UP_ARB_0_LIM_HUBS_DMI_VC0_PC_WID                ( 3)
  #define HUBS_CR_HUB0_UP_ARB_0_LIM_HUBS_DMI_VC0_PC_MSK                (0x00000038)
  #define HUBS_CR_HUB0_UP_ARB_0_LIM_HUBS_DMI_VC0_PC_MIN                (0)
  #define HUBS_CR_HUB0_UP_ARB_0_LIM_HUBS_DMI_VC0_PC_MAX                (7) // 0x00000007
  #define HUBS_CR_HUB0_UP_ARB_0_LIM_HUBS_DMI_VC0_PC_DEF                (0x00000004)
  #define HUBS_CR_HUB0_UP_ARB_0_LIM_HUBS_DMI_VC0_PC_HSH                (0x03037200)

  #define HUBS_CR_HUB0_UP_ARB_0_LIM_HUBS_P16_VC0_NP_OFF                ( 6)
  #define HUBS_CR_HUB0_UP_ARB_0_LIM_HUBS_P16_VC0_NP_WID                ( 3)
  #define HUBS_CR_HUB0_UP_ARB_0_LIM_HUBS_P16_VC0_NP_MSK                (0x000001C0)
  #define HUBS_CR_HUB0_UP_ARB_0_LIM_HUBS_P16_VC0_NP_MIN                (0)
  #define HUBS_CR_HUB0_UP_ARB_0_LIM_HUBS_P16_VC0_NP_MAX                (7) // 0x00000007
  #define HUBS_CR_HUB0_UP_ARB_0_LIM_HUBS_P16_VC0_NP_DEF                (0x00000004)
  #define HUBS_CR_HUB0_UP_ARB_0_LIM_HUBS_P16_VC0_NP_HSH                (0x03067200)

  #define HUBS_CR_HUB0_UP_ARB_0_LIM_HUBS_P16_VC0_PC_OFF                ( 9)
  #define HUBS_CR_HUB0_UP_ARB_0_LIM_HUBS_P16_VC0_PC_WID                ( 3)
  #define HUBS_CR_HUB0_UP_ARB_0_LIM_HUBS_P16_VC0_PC_MSK                (0x00000E00)
  #define HUBS_CR_HUB0_UP_ARB_0_LIM_HUBS_P16_VC0_PC_MIN                (0)
  #define HUBS_CR_HUB0_UP_ARB_0_LIM_HUBS_P16_VC0_PC_MAX                (7) // 0x00000007
  #define HUBS_CR_HUB0_UP_ARB_0_LIM_HUBS_P16_VC0_PC_DEF                (0x00000004)
  #define HUBS_CR_HUB0_UP_ARB_0_LIM_HUBS_P16_VC0_PC_HSH                (0x03097200)

  #define HUBS_CR_HUB0_UP_ARB_0_LIM_HUBS_P08_VC0_NP_OFF                (12)
  #define HUBS_CR_HUB0_UP_ARB_0_LIM_HUBS_P08_VC0_NP_WID                ( 3)
  #define HUBS_CR_HUB0_UP_ARB_0_LIM_HUBS_P08_VC0_NP_MSK                (0x00007000)
  #define HUBS_CR_HUB0_UP_ARB_0_LIM_HUBS_P08_VC0_NP_MIN                (0)
  #define HUBS_CR_HUB0_UP_ARB_0_LIM_HUBS_P08_VC0_NP_MAX                (7) // 0x00000007
  #define HUBS_CR_HUB0_UP_ARB_0_LIM_HUBS_P08_VC0_NP_DEF                (0x00000004)
  #define HUBS_CR_HUB0_UP_ARB_0_LIM_HUBS_P08_VC0_NP_HSH                (0x030C7200)

  #define HUBS_CR_HUB0_UP_ARB_0_LIM_HUBS_P08_VC0_PC_OFF                (15)
  #define HUBS_CR_HUB0_UP_ARB_0_LIM_HUBS_P08_VC0_PC_WID                ( 3)
  #define HUBS_CR_HUB0_UP_ARB_0_LIM_HUBS_P08_VC0_PC_MSK                (0x00038000)
  #define HUBS_CR_HUB0_UP_ARB_0_LIM_HUBS_P08_VC0_PC_MIN                (0)
  #define HUBS_CR_HUB0_UP_ARB_0_LIM_HUBS_P08_VC0_PC_MAX                (7) // 0x00000007
  #define HUBS_CR_HUB0_UP_ARB_0_LIM_HUBS_P08_VC0_PC_DEF                (0x00000004)
  #define HUBS_CR_HUB0_UP_ARB_0_LIM_HUBS_P08_VC0_PC_HSH                (0x030F7200)

  #define HUBS_CR_HUB0_UP_ARB_0_LIM_HUBS_P4A_VC0_NP_OFF                (18)
  #define HUBS_CR_HUB0_UP_ARB_0_LIM_HUBS_P4A_VC0_NP_WID                ( 3)
  #define HUBS_CR_HUB0_UP_ARB_0_LIM_HUBS_P4A_VC0_NP_MSK                (0x001C0000)
  #define HUBS_CR_HUB0_UP_ARB_0_LIM_HUBS_P4A_VC0_NP_MIN                (0)
  #define HUBS_CR_HUB0_UP_ARB_0_LIM_HUBS_P4A_VC0_NP_MAX                (7) // 0x00000007
  #define HUBS_CR_HUB0_UP_ARB_0_LIM_HUBS_P4A_VC0_NP_DEF                (0x00000004)
  #define HUBS_CR_HUB0_UP_ARB_0_LIM_HUBS_P4A_VC0_NP_HSH                (0x03127200)

  #define HUBS_CR_HUB0_UP_ARB_0_LIM_HUBS_P4A_VC0_PC_OFF                (21)
  #define HUBS_CR_HUB0_UP_ARB_0_LIM_HUBS_P4A_VC0_PC_WID                ( 3)
  #define HUBS_CR_HUB0_UP_ARB_0_LIM_HUBS_P4A_VC0_PC_MSK                (0x00E00000)
  #define HUBS_CR_HUB0_UP_ARB_0_LIM_HUBS_P4A_VC0_PC_MIN                (0)
  #define HUBS_CR_HUB0_UP_ARB_0_LIM_HUBS_P4A_VC0_PC_MAX                (7) // 0x00000007
  #define HUBS_CR_HUB0_UP_ARB_0_LIM_HUBS_P4A_VC0_PC_DEF                (0x00000004)
  #define HUBS_CR_HUB0_UP_ARB_0_LIM_HUBS_P4A_VC0_PC_HSH                (0x03157200)

  #define HUBS_CR_HUB0_UP_ARB_0_LIM_HUBS_DE_VC0_NP_OFF                 (24)
  #define HUBS_CR_HUB0_UP_ARB_0_LIM_HUBS_DE_VC0_NP_WID                 ( 3)
  #define HUBS_CR_HUB0_UP_ARB_0_LIM_HUBS_DE_VC0_NP_MSK                 (0x07000000)
  #define HUBS_CR_HUB0_UP_ARB_0_LIM_HUBS_DE_VC0_NP_MIN                 (0)
  #define HUBS_CR_HUB0_UP_ARB_0_LIM_HUBS_DE_VC0_NP_MAX                 (7) // 0x00000007
  #define HUBS_CR_HUB0_UP_ARB_0_LIM_HUBS_DE_VC0_NP_DEF                 (0x00000004)
  #define HUBS_CR_HUB0_UP_ARB_0_LIM_HUBS_DE_VC0_NP_HSH                 (0x03187200)

  #define HUBS_CR_HUB0_UP_ARB_0_LIM_HUBS_DE_VC0_PC_OFF                 (27)
  #define HUBS_CR_HUB0_UP_ARB_0_LIM_HUBS_DE_VC0_PC_WID                 ( 3)
  #define HUBS_CR_HUB0_UP_ARB_0_LIM_HUBS_DE_VC0_PC_MSK                 (0x38000000)
  #define HUBS_CR_HUB0_UP_ARB_0_LIM_HUBS_DE_VC0_PC_MIN                 (0)
  #define HUBS_CR_HUB0_UP_ARB_0_LIM_HUBS_DE_VC0_PC_MAX                 (7) // 0x00000007
  #define HUBS_CR_HUB0_UP_ARB_0_LIM_HUBS_DE_VC0_PC_DEF                 (0x00000004)
  #define HUBS_CR_HUB0_UP_ARB_0_LIM_HUBS_DE_VC0_PC_HSH                 (0x031B7200)

#define HUBS_CR_HUB0_UP_ARB_1_LIM_HUBS_REG                             (0x00007204)

  #define HUBS_CR_HUB0_UP_ARB_1_LIM_HUBS_DMI_VCM_NP_OFF                ( 0)
  #define HUBS_CR_HUB0_UP_ARB_1_LIM_HUBS_DMI_VCM_NP_WID                ( 3)
  #define HUBS_CR_HUB0_UP_ARB_1_LIM_HUBS_DMI_VCM_NP_MSK                (0x00000007)
  #define HUBS_CR_HUB0_UP_ARB_1_LIM_HUBS_DMI_VCM_NP_MIN                (0)
  #define HUBS_CR_HUB0_UP_ARB_1_LIM_HUBS_DMI_VCM_NP_MAX                (7) // 0x00000007
  #define HUBS_CR_HUB0_UP_ARB_1_LIM_HUBS_DMI_VCM_NP_DEF                (0x00000004)
  #define HUBS_CR_HUB0_UP_ARB_1_LIM_HUBS_DMI_VCM_NP_HSH                (0x03007204)

  #define HUBS_CR_HUB0_UP_ARB_1_LIM_HUBS_DMI_VCM_PC_OFF                ( 3)
  #define HUBS_CR_HUB0_UP_ARB_1_LIM_HUBS_DMI_VCM_PC_WID                ( 3)
  #define HUBS_CR_HUB0_UP_ARB_1_LIM_HUBS_DMI_VCM_PC_MSK                (0x00000038)
  #define HUBS_CR_HUB0_UP_ARB_1_LIM_HUBS_DMI_VCM_PC_MIN                (0)
  #define HUBS_CR_HUB0_UP_ARB_1_LIM_HUBS_DMI_VCM_PC_MAX                (7) // 0x00000007
  #define HUBS_CR_HUB0_UP_ARB_1_LIM_HUBS_DMI_VCM_PC_DEF                (0x00000004)
  #define HUBS_CR_HUB0_UP_ARB_1_LIM_HUBS_DMI_VCM_PC_HSH                (0x03037204)

  #define HUBS_CR_HUB0_UP_ARB_1_LIM_HUBS_GMM_VC0_NP_OFF                ( 6)
  #define HUBS_CR_HUB0_UP_ARB_1_LIM_HUBS_GMM_VC0_NP_WID                ( 3)
  #define HUBS_CR_HUB0_UP_ARB_1_LIM_HUBS_GMM_VC0_NP_MSK                (0x000001C0)
  #define HUBS_CR_HUB0_UP_ARB_1_LIM_HUBS_GMM_VC0_NP_MIN                (0)
  #define HUBS_CR_HUB0_UP_ARB_1_LIM_HUBS_GMM_VC0_NP_MAX                (7) // 0x00000007
  #define HUBS_CR_HUB0_UP_ARB_1_LIM_HUBS_GMM_VC0_NP_DEF                (0x00000004)
  #define HUBS_CR_HUB0_UP_ARB_1_LIM_HUBS_GMM_VC0_NP_HSH                (0x03067204)

  #define HUBS_CR_HUB0_UP_ARB_1_LIM_HUBS_GMM_VC0_PC_OFF                ( 9)
  #define HUBS_CR_HUB0_UP_ARB_1_LIM_HUBS_GMM_VC0_PC_WID                ( 3)
  #define HUBS_CR_HUB0_UP_ARB_1_LIM_HUBS_GMM_VC0_PC_MSK                (0x00000E00)
  #define HUBS_CR_HUB0_UP_ARB_1_LIM_HUBS_GMM_VC0_PC_MIN                (0)
  #define HUBS_CR_HUB0_UP_ARB_1_LIM_HUBS_GMM_VC0_PC_MAX                (7) // 0x00000007
  #define HUBS_CR_HUB0_UP_ARB_1_LIM_HUBS_GMM_VC0_PC_DEF                (0x00000004)
  #define HUBS_CR_HUB0_UP_ARB_1_LIM_HUBS_GMM_VC0_PC_HSH                (0x03097204)

  #define HUBS_CR_HUB0_UP_ARB_1_LIM_HUBS_RESERVED_OFF                  (12)
  #define HUBS_CR_HUB0_UP_ARB_1_LIM_HUBS_RESERVED_WID                  (12)
  #define HUBS_CR_HUB0_UP_ARB_1_LIM_HUBS_RESERVED_MSK                  (0x00FFF000)
  #define HUBS_CR_HUB0_UP_ARB_1_LIM_HUBS_RESERVED_MIN                  (0)
  #define HUBS_CR_HUB0_UP_ARB_1_LIM_HUBS_RESERVED_MAX                  (4095) // 0x00000FFF
  #define HUBS_CR_HUB0_UP_ARB_1_LIM_HUBS_RESERVED_DEF                  (0x00000924)
  #define HUBS_CR_HUB0_UP_ARB_1_LIM_HUBS_RESERVED_HSH                  (0x0C0C7204)

#define HUBS_CR_HUB0_ARB_IPC_HUBS_REG                                  (0x00007208)

  #define HUBS_CR_HUB0_ARB_IPC_HUBS_NON_VC1_THRESHOLD_OFF              ( 0)
  #define HUBS_CR_HUB0_ARB_IPC_HUBS_NON_VC1_THRESHOLD_WID              ( 4)
  #define HUBS_CR_HUB0_ARB_IPC_HUBS_NON_VC1_THRESHOLD_MSK              (0x0000000F)
  #define HUBS_CR_HUB0_ARB_IPC_HUBS_NON_VC1_THRESHOLD_MIN              (0)
  #define HUBS_CR_HUB0_ARB_IPC_HUBS_NON_VC1_THRESHOLD_MAX              (15) // 0x0000000F
  #define HUBS_CR_HUB0_ARB_IPC_HUBS_NON_VC1_THRESHOLD_DEF              (0x00000004)
  #define HUBS_CR_HUB0_ARB_IPC_HUBS_NON_VC1_THRESHOLD_HSH              (0x04007208)

  #define HUBS_CR_HUB0_ARB_IPC_HUBS_VC1_RD_THRESHOLD_OFF               ( 4)
  #define HUBS_CR_HUB0_ARB_IPC_HUBS_VC1_RD_THRESHOLD_WID               ( 4)
  #define HUBS_CR_HUB0_ARB_IPC_HUBS_VC1_RD_THRESHOLD_MSK               (0x000000F0)
  #define HUBS_CR_HUB0_ARB_IPC_HUBS_VC1_RD_THRESHOLD_MIN               (0)
  #define HUBS_CR_HUB0_ARB_IPC_HUBS_VC1_RD_THRESHOLD_MAX               (15) // 0x0000000F
  #define HUBS_CR_HUB0_ARB_IPC_HUBS_VC1_RD_THRESHOLD_DEF               (0x00000004)
  #define HUBS_CR_HUB0_ARB_IPC_HUBS_VC1_RD_THRESHOLD_HSH               (0x04047208)

  #define HUBS_CR_HUB0_ARB_IPC_HUBS_FIXED_RATEP_EN_OFF                 ( 8)
  #define HUBS_CR_HUB0_ARB_IPC_HUBS_FIXED_RATEP_EN_WID                 ( 1)
  #define HUBS_CR_HUB0_ARB_IPC_HUBS_FIXED_RATEP_EN_MSK                 (0x00000100)
  #define HUBS_CR_HUB0_ARB_IPC_HUBS_FIXED_RATEP_EN_MIN                 (0)
  #define HUBS_CR_HUB0_ARB_IPC_HUBS_FIXED_RATEP_EN_MAX                 (1) // 0x00000001
  #define HUBS_CR_HUB0_ARB_IPC_HUBS_FIXED_RATEP_EN_DEF                 (0x00000000)
  #define HUBS_CR_HUB0_ARB_IPC_HUBS_FIXED_RATEP_EN_HSH                 (0x01087208)

  #define HUBS_CR_HUB0_ARB_IPC_HUBS_HIGH_PRIO_LIM_OFF                  ( 9)
  #define HUBS_CR_HUB0_ARB_IPC_HUBS_HIGH_PRIO_LIM_WID                  ( 3)
  #define HUBS_CR_HUB0_ARB_IPC_HUBS_HIGH_PRIO_LIM_MSK                  (0x00000E00)
  #define HUBS_CR_HUB0_ARB_IPC_HUBS_HIGH_PRIO_LIM_MIN                  (0)
  #define HUBS_CR_HUB0_ARB_IPC_HUBS_HIGH_PRIO_LIM_MAX                  (7) // 0x00000007
  #define HUBS_CR_HUB0_ARB_IPC_HUBS_HIGH_PRIO_LIM_DEF                  (0x00000004)
  #define HUBS_CR_HUB0_ARB_IPC_HUBS_HIGH_PRIO_LIM_HSH                  (0x03097208)

  #define HUBS_CR_HUB0_ARB_IPC_HUBS_LOW_PRIO_LIM_OFF                   (12)
  #define HUBS_CR_HUB0_ARB_IPC_HUBS_LOW_PRIO_LIM_WID                   ( 3)
  #define HUBS_CR_HUB0_ARB_IPC_HUBS_LOW_PRIO_LIM_MSK                   (0x00007000)
  #define HUBS_CR_HUB0_ARB_IPC_HUBS_LOW_PRIO_LIM_MIN                   (0)
  #define HUBS_CR_HUB0_ARB_IPC_HUBS_LOW_PRIO_LIM_MAX                   (7) // 0x00000007
  #define HUBS_CR_HUB0_ARB_IPC_HUBS_LOW_PRIO_LIM_DEF                   (0x00000004)
  #define HUBS_CR_HUB0_ARB_IPC_HUBS_LOW_PRIO_LIM_HSH                   (0x030C7208)

  #define HUBS_CR_HUB0_ARB_IPC_HUBS_RESERVED_OFF                       (15)
  #define HUBS_CR_HUB0_ARB_IPC_HUBS_RESERVED_WID                       ( 9)
  #define HUBS_CR_HUB0_ARB_IPC_HUBS_RESERVED_MSK                       (0x00FF8000)
  #define HUBS_CR_HUB0_ARB_IPC_HUBS_RESERVED_MIN                       (0)
  #define HUBS_CR_HUB0_ARB_IPC_HUBS_RESERVED_MAX                       (511) // 0x000001FF
  #define HUBS_CR_HUB0_ARB_IPC_HUBS_RESERVED_DEF                       (0x00000124)
  #define HUBS_CR_HUB0_ARB_IPC_HUBS_RESERVED_HSH                       (0x090F7208)

#define HUBS_CR_HUB1_UP_ARB_0_LIM_HUBS_REG                             (0x0000720C)

  #define HUBS_CR_HUB1_UP_ARB_0_LIM_HUBS_DMI_VC0_NP_OFF                ( 0)
  #define HUBS_CR_HUB1_UP_ARB_0_LIM_HUBS_DMI_VC0_NP_WID                ( 3)
  #define HUBS_CR_HUB1_UP_ARB_0_LIM_HUBS_DMI_VC0_NP_MSK                (0x00000007)
  #define HUBS_CR_HUB1_UP_ARB_0_LIM_HUBS_DMI_VC0_NP_MIN                (0)
  #define HUBS_CR_HUB1_UP_ARB_0_LIM_HUBS_DMI_VC0_NP_MAX                (7) // 0x00000007
  #define HUBS_CR_HUB1_UP_ARB_0_LIM_HUBS_DMI_VC0_NP_DEF                (0x00000004)
  #define HUBS_CR_HUB1_UP_ARB_0_LIM_HUBS_DMI_VC0_NP_HSH                (0x0300720C)

  #define HUBS_CR_HUB1_UP_ARB_0_LIM_HUBS_DMI_VC0_PC_OFF                ( 3)
  #define HUBS_CR_HUB1_UP_ARB_0_LIM_HUBS_DMI_VC0_PC_WID                ( 3)
  #define HUBS_CR_HUB1_UP_ARB_0_LIM_HUBS_DMI_VC0_PC_MSK                (0x00000038)
  #define HUBS_CR_HUB1_UP_ARB_0_LIM_HUBS_DMI_VC0_PC_MIN                (0)
  #define HUBS_CR_HUB1_UP_ARB_0_LIM_HUBS_DMI_VC0_PC_MAX                (7) // 0x00000007
  #define HUBS_CR_HUB1_UP_ARB_0_LIM_HUBS_DMI_VC0_PC_DEF                (0x00000004)
  #define HUBS_CR_HUB1_UP_ARB_0_LIM_HUBS_DMI_VC0_PC_HSH                (0x0303720C)

  #define HUBS_CR_HUB1_UP_ARB_0_LIM_HUBS_P4A_VC0_NP_OFF                ( 6)
  #define HUBS_CR_HUB1_UP_ARB_0_LIM_HUBS_P4A_VC0_NP_WID                ( 3)
  #define HUBS_CR_HUB1_UP_ARB_0_LIM_HUBS_P4A_VC0_NP_MSK                (0x000001C0)
  #define HUBS_CR_HUB1_UP_ARB_0_LIM_HUBS_P4A_VC0_NP_MIN                (0)
  #define HUBS_CR_HUB1_UP_ARB_0_LIM_HUBS_P4A_VC0_NP_MAX                (7) // 0x00000007
  #define HUBS_CR_HUB1_UP_ARB_0_LIM_HUBS_P4A_VC0_NP_DEF                (0x00000004)
  #define HUBS_CR_HUB1_UP_ARB_0_LIM_HUBS_P4A_VC0_NP_HSH                (0x0306720C)

  #define HUBS_CR_HUB1_UP_ARB_0_LIM_HUBS_P4A_VC0_PC_OFF                ( 9)
  #define HUBS_CR_HUB1_UP_ARB_0_LIM_HUBS_P4A_VC0_PC_WID                ( 3)
  #define HUBS_CR_HUB1_UP_ARB_0_LIM_HUBS_P4A_VC0_PC_MSK                (0x00000E00)
  #define HUBS_CR_HUB1_UP_ARB_0_LIM_HUBS_P4A_VC0_PC_MIN                (0)
  #define HUBS_CR_HUB1_UP_ARB_0_LIM_HUBS_P4A_VC0_PC_MAX                (7) // 0x00000007
  #define HUBS_CR_HUB1_UP_ARB_0_LIM_HUBS_P4A_VC0_PC_DEF                (0x00000004)
  #define HUBS_CR_HUB1_UP_ARB_0_LIM_HUBS_P4A_VC0_PC_HSH                (0x0309720C)

  #define HUBS_CR_HUB1_UP_ARB_0_LIM_HUBS_DMI_VCM_NP_OFF                (12)
  #define HUBS_CR_HUB1_UP_ARB_0_LIM_HUBS_DMI_VCM_NP_WID                ( 3)
  #define HUBS_CR_HUB1_UP_ARB_0_LIM_HUBS_DMI_VCM_NP_MSK                (0x00007000)
  #define HUBS_CR_HUB1_UP_ARB_0_LIM_HUBS_DMI_VCM_NP_MIN                (0)
  #define HUBS_CR_HUB1_UP_ARB_0_LIM_HUBS_DMI_VCM_NP_MAX                (7) // 0x00000007
  #define HUBS_CR_HUB1_UP_ARB_0_LIM_HUBS_DMI_VCM_NP_DEF                (0x00000004)
  #define HUBS_CR_HUB1_UP_ARB_0_LIM_HUBS_DMI_VCM_NP_HSH                (0x030C720C)

  #define HUBS_CR_HUB1_UP_ARB_0_LIM_HUBS_DMI_VCM_PC_OFF                (15)
  #define HUBS_CR_HUB1_UP_ARB_0_LIM_HUBS_DMI_VCM_PC_WID                ( 3)
  #define HUBS_CR_HUB1_UP_ARB_0_LIM_HUBS_DMI_VCM_PC_MSK                (0x00038000)
  #define HUBS_CR_HUB1_UP_ARB_0_LIM_HUBS_DMI_VCM_PC_MIN                (0)
  #define HUBS_CR_HUB1_UP_ARB_0_LIM_HUBS_DMI_VCM_PC_MAX                (7) // 0x00000007
  #define HUBS_CR_HUB1_UP_ARB_0_LIM_HUBS_DMI_VCM_PC_DEF                (0x00000004)
  #define HUBS_CR_HUB1_UP_ARB_0_LIM_HUBS_DMI_VCM_PC_HSH                (0x030F720C)

  #define HUBS_CR_HUB1_UP_ARB_0_LIM_HUBS_GMM_VC0_NP_OFF                (18)
  #define HUBS_CR_HUB1_UP_ARB_0_LIM_HUBS_GMM_VC0_NP_WID                ( 3)
  #define HUBS_CR_HUB1_UP_ARB_0_LIM_HUBS_GMM_VC0_NP_MSK                (0x001C0000)
  #define HUBS_CR_HUB1_UP_ARB_0_LIM_HUBS_GMM_VC0_NP_MIN                (0)
  #define HUBS_CR_HUB1_UP_ARB_0_LIM_HUBS_GMM_VC0_NP_MAX                (7) // 0x00000007
  #define HUBS_CR_HUB1_UP_ARB_0_LIM_HUBS_GMM_VC0_NP_DEF                (0x00000004)
  #define HUBS_CR_HUB1_UP_ARB_0_LIM_HUBS_GMM_VC0_NP_HSH                (0x0312720C)

  #define HUBS_CR_HUB1_UP_ARB_0_LIM_HUBS_GMM_VC0_PC_OFF                (21)
  #define HUBS_CR_HUB1_UP_ARB_0_LIM_HUBS_GMM_VC0_PC_WID                ( 3)
  #define HUBS_CR_HUB1_UP_ARB_0_LIM_HUBS_GMM_VC0_PC_MSK                (0x00E00000)
  #define HUBS_CR_HUB1_UP_ARB_0_LIM_HUBS_GMM_VC0_PC_MIN                (0)
  #define HUBS_CR_HUB1_UP_ARB_0_LIM_HUBS_GMM_VC0_PC_MAX                (7) // 0x00000007
  #define HUBS_CR_HUB1_UP_ARB_0_LIM_HUBS_GMM_VC0_PC_DEF                (0x00000004)
  #define HUBS_CR_HUB1_UP_ARB_0_LIM_HUBS_GMM_VC0_PC_HSH                (0x0315720C)

#define HUBS_CR_HUB1_ARB_IPC_HUBS_REG                                  (0x00007210)

  #define HUBS_CR_HUB1_ARB_IPC_HUBS_NON_VC1_THRESHOLD_OFF              ( 0)
  #define HUBS_CR_HUB1_ARB_IPC_HUBS_NON_VC1_THRESHOLD_WID              ( 4)
  #define HUBS_CR_HUB1_ARB_IPC_HUBS_NON_VC1_THRESHOLD_MSK              (0x0000000F)
  #define HUBS_CR_HUB1_ARB_IPC_HUBS_NON_VC1_THRESHOLD_MIN              (0)
  #define HUBS_CR_HUB1_ARB_IPC_HUBS_NON_VC1_THRESHOLD_MAX              (15) // 0x0000000F
  #define HUBS_CR_HUB1_ARB_IPC_HUBS_NON_VC1_THRESHOLD_DEF              (0x00000004)
  #define HUBS_CR_HUB1_ARB_IPC_HUBS_NON_VC1_THRESHOLD_HSH              (0x04007210)

  #define HUBS_CR_HUB1_ARB_IPC_HUBS_VC1_RD_THRESHOLD_OFF               ( 4)
  #define HUBS_CR_HUB1_ARB_IPC_HUBS_VC1_RD_THRESHOLD_WID               ( 4)
  #define HUBS_CR_HUB1_ARB_IPC_HUBS_VC1_RD_THRESHOLD_MSK               (0x000000F0)
  #define HUBS_CR_HUB1_ARB_IPC_HUBS_VC1_RD_THRESHOLD_MIN               (0)
  #define HUBS_CR_HUB1_ARB_IPC_HUBS_VC1_RD_THRESHOLD_MAX               (15) // 0x0000000F
  #define HUBS_CR_HUB1_ARB_IPC_HUBS_VC1_RD_THRESHOLD_DEF               (0x00000004)
  #define HUBS_CR_HUB1_ARB_IPC_HUBS_VC1_RD_THRESHOLD_HSH               (0x04047210)

  #define HUBS_CR_HUB1_ARB_IPC_HUBS_FIXED_RATEP_EN_OFF                 ( 8)
  #define HUBS_CR_HUB1_ARB_IPC_HUBS_FIXED_RATEP_EN_WID                 ( 1)
  #define HUBS_CR_HUB1_ARB_IPC_HUBS_FIXED_RATEP_EN_MSK                 (0x00000100)
  #define HUBS_CR_HUB1_ARB_IPC_HUBS_FIXED_RATEP_EN_MIN                 (0)
  #define HUBS_CR_HUB1_ARB_IPC_HUBS_FIXED_RATEP_EN_MAX                 (1) // 0x00000001
  #define HUBS_CR_HUB1_ARB_IPC_HUBS_FIXED_RATEP_EN_DEF                 (0x00000000)
  #define HUBS_CR_HUB1_ARB_IPC_HUBS_FIXED_RATEP_EN_HSH                 (0x01087210)

  #define HUBS_CR_HUB1_ARB_IPC_HUBS_HIGH_PRIO_LIM_OFF                  ( 9)
  #define HUBS_CR_HUB1_ARB_IPC_HUBS_HIGH_PRIO_LIM_WID                  ( 3)
  #define HUBS_CR_HUB1_ARB_IPC_HUBS_HIGH_PRIO_LIM_MSK                  (0x00000E00)
  #define HUBS_CR_HUB1_ARB_IPC_HUBS_HIGH_PRIO_LIM_MIN                  (0)
  #define HUBS_CR_HUB1_ARB_IPC_HUBS_HIGH_PRIO_LIM_MAX                  (7) // 0x00000007
  #define HUBS_CR_HUB1_ARB_IPC_HUBS_HIGH_PRIO_LIM_DEF                  (0x00000004)
  #define HUBS_CR_HUB1_ARB_IPC_HUBS_HIGH_PRIO_LIM_HSH                  (0x03097210)

  #define HUBS_CR_HUB1_ARB_IPC_HUBS_LOW_PRIO_LIM_OFF                   (12)
  #define HUBS_CR_HUB1_ARB_IPC_HUBS_LOW_PRIO_LIM_WID                   ( 3)
  #define HUBS_CR_HUB1_ARB_IPC_HUBS_LOW_PRIO_LIM_MSK                   (0x00007000)
  #define HUBS_CR_HUB1_ARB_IPC_HUBS_LOW_PRIO_LIM_MIN                   (0)
  #define HUBS_CR_HUB1_ARB_IPC_HUBS_LOW_PRIO_LIM_MAX                   (7) // 0x00000007
  #define HUBS_CR_HUB1_ARB_IPC_HUBS_LOW_PRIO_LIM_DEF                   (0x00000004)
  #define HUBS_CR_HUB1_ARB_IPC_HUBS_LOW_PRIO_LIM_HSH                   (0x030C7210)

#define HUBS_CR_HUB2_UP_ARB_0_LIM_HUBS_REG                             (0x00007214)

  #define HUBS_CR_HUB2_UP_ARB_0_LIM_HUBS_P16_VC0_NP_OFF                ( 0)
  #define HUBS_CR_HUB2_UP_ARB_0_LIM_HUBS_P16_VC0_NP_WID                ( 3)
  #define HUBS_CR_HUB2_UP_ARB_0_LIM_HUBS_P16_VC0_NP_MSK                (0x00000007)
  #define HUBS_CR_HUB2_UP_ARB_0_LIM_HUBS_P16_VC0_NP_MIN                (0)
  #define HUBS_CR_HUB2_UP_ARB_0_LIM_HUBS_P16_VC0_NP_MAX                (7) // 0x00000007
  #define HUBS_CR_HUB2_UP_ARB_0_LIM_HUBS_P16_VC0_NP_DEF                (0x00000004)
  #define HUBS_CR_HUB2_UP_ARB_0_LIM_HUBS_P16_VC0_NP_HSH                (0x03007214)

  #define HUBS_CR_HUB2_UP_ARB_0_LIM_HUBS_P16_VC0_PC_OFF                ( 3)
  #define HUBS_CR_HUB2_UP_ARB_0_LIM_HUBS_P16_VC0_PC_WID                ( 3)
  #define HUBS_CR_HUB2_UP_ARB_0_LIM_HUBS_P16_VC0_PC_MSK                (0x00000038)
  #define HUBS_CR_HUB2_UP_ARB_0_LIM_HUBS_P16_VC0_PC_MIN                (0)
  #define HUBS_CR_HUB2_UP_ARB_0_LIM_HUBS_P16_VC0_PC_MAX                (7) // 0x00000007
  #define HUBS_CR_HUB2_UP_ARB_0_LIM_HUBS_P16_VC0_PC_DEF                (0x00000004)
  #define HUBS_CR_HUB2_UP_ARB_0_LIM_HUBS_P16_VC0_PC_HSH                (0x03037214)

  #define HUBS_CR_HUB2_UP_ARB_0_LIM_HUBS_DE_VC0_NP_OFF                 ( 6)
  #define HUBS_CR_HUB2_UP_ARB_0_LIM_HUBS_DE_VC0_NP_WID                 ( 3)
  #define HUBS_CR_HUB2_UP_ARB_0_LIM_HUBS_DE_VC0_NP_MSK                 (0x000001C0)
  #define HUBS_CR_HUB2_UP_ARB_0_LIM_HUBS_DE_VC0_NP_MIN                 (0)
  #define HUBS_CR_HUB2_UP_ARB_0_LIM_HUBS_DE_VC0_NP_MAX                 (7) // 0x00000007
  #define HUBS_CR_HUB2_UP_ARB_0_LIM_HUBS_DE_VC0_NP_DEF                 (0x00000004)
  #define HUBS_CR_HUB2_UP_ARB_0_LIM_HUBS_DE_VC0_NP_HSH                 (0x03067214)

  #define HUBS_CR_HUB2_UP_ARB_0_LIM_HUBS_DE_VC0_PC_OFF                 ( 9)
  #define HUBS_CR_HUB2_UP_ARB_0_LIM_HUBS_DE_VC0_PC_WID                 ( 3)
  #define HUBS_CR_HUB2_UP_ARB_0_LIM_HUBS_DE_VC0_PC_MSK                 (0x00000E00)
  #define HUBS_CR_HUB2_UP_ARB_0_LIM_HUBS_DE_VC0_PC_MIN                 (0)
  #define HUBS_CR_HUB2_UP_ARB_0_LIM_HUBS_DE_VC0_PC_MAX                 (7) // 0x00000007
  #define HUBS_CR_HUB2_UP_ARB_0_LIM_HUBS_DE_VC0_PC_DEF                 (0x00000004)
  #define HUBS_CR_HUB2_UP_ARB_0_LIM_HUBS_DE_VC0_PC_HSH                 (0x03097214)

#define HUBS_CR_HUB2_ARB_IPC_HUBS_REG                                  (0x00007218)

  #define HUBS_CR_HUB2_ARB_IPC_HUBS_NON_VC1_THRESHOLD_OFF              ( 0)
  #define HUBS_CR_HUB2_ARB_IPC_HUBS_NON_VC1_THRESHOLD_WID              ( 4)
  #define HUBS_CR_HUB2_ARB_IPC_HUBS_NON_VC1_THRESHOLD_MSK              (0x0000000F)
  #define HUBS_CR_HUB2_ARB_IPC_HUBS_NON_VC1_THRESHOLD_MIN              (0)
  #define HUBS_CR_HUB2_ARB_IPC_HUBS_NON_VC1_THRESHOLD_MAX              (15) // 0x0000000F
  #define HUBS_CR_HUB2_ARB_IPC_HUBS_NON_VC1_THRESHOLD_DEF              (0x00000004)
  #define HUBS_CR_HUB2_ARB_IPC_HUBS_NON_VC1_THRESHOLD_HSH              (0x04007218)

  #define HUBS_CR_HUB2_ARB_IPC_HUBS_VC1_RD_THRESHOLD_OFF               ( 4)
  #define HUBS_CR_HUB2_ARB_IPC_HUBS_VC1_RD_THRESHOLD_WID               ( 4)
  #define HUBS_CR_HUB2_ARB_IPC_HUBS_VC1_RD_THRESHOLD_MSK               (0x000000F0)
  #define HUBS_CR_HUB2_ARB_IPC_HUBS_VC1_RD_THRESHOLD_MIN               (0)
  #define HUBS_CR_HUB2_ARB_IPC_HUBS_VC1_RD_THRESHOLD_MAX               (15) // 0x0000000F
  #define HUBS_CR_HUB2_ARB_IPC_HUBS_VC1_RD_THRESHOLD_DEF               (0x00000004)
  #define HUBS_CR_HUB2_ARB_IPC_HUBS_VC1_RD_THRESHOLD_HSH               (0x04047218)

  #define HUBS_CR_HUB2_ARB_IPC_HUBS_FIXED_RATEP_EN_OFF                 ( 8)
  #define HUBS_CR_HUB2_ARB_IPC_HUBS_FIXED_RATEP_EN_WID                 ( 1)
  #define HUBS_CR_HUB2_ARB_IPC_HUBS_FIXED_RATEP_EN_MSK                 (0x00000100)
  #define HUBS_CR_HUB2_ARB_IPC_HUBS_FIXED_RATEP_EN_MIN                 (0)
  #define HUBS_CR_HUB2_ARB_IPC_HUBS_FIXED_RATEP_EN_MAX                 (1) // 0x00000001
  #define HUBS_CR_HUB2_ARB_IPC_HUBS_FIXED_RATEP_EN_DEF                 (0x00000000)
  #define HUBS_CR_HUB2_ARB_IPC_HUBS_FIXED_RATEP_EN_HSH                 (0x01087218)

  #define HUBS_CR_HUB2_ARB_IPC_HUBS_HIGH_PRIO_LIM_OFF                  ( 9)
  #define HUBS_CR_HUB2_ARB_IPC_HUBS_HIGH_PRIO_LIM_WID                  ( 3)
  #define HUBS_CR_HUB2_ARB_IPC_HUBS_HIGH_PRIO_LIM_MSK                  (0x00000E00)
  #define HUBS_CR_HUB2_ARB_IPC_HUBS_HIGH_PRIO_LIM_MIN                  (0)
  #define HUBS_CR_HUB2_ARB_IPC_HUBS_HIGH_PRIO_LIM_MAX                  (7) // 0x00000007
  #define HUBS_CR_HUB2_ARB_IPC_HUBS_HIGH_PRIO_LIM_DEF                  (0x00000004)
  #define HUBS_CR_HUB2_ARB_IPC_HUBS_HIGH_PRIO_LIM_HSH                  (0x03097218)

  #define HUBS_CR_HUB2_ARB_IPC_HUBS_LOW_PRIO_LIM_OFF                   (12)
  #define HUBS_CR_HUB2_ARB_IPC_HUBS_LOW_PRIO_LIM_WID                   ( 3)
  #define HUBS_CR_HUB2_ARB_IPC_HUBS_LOW_PRIO_LIM_MSK                   (0x00007000)
  #define HUBS_CR_HUB2_ARB_IPC_HUBS_LOW_PRIO_LIM_MIN                   (0)
  #define HUBS_CR_HUB2_ARB_IPC_HUBS_LOW_PRIO_LIM_MAX                   (7) // 0x00000007
  #define HUBS_CR_HUB2_ARB_IPC_HUBS_LOW_PRIO_LIM_DEF                   (0x00000004)
  #define HUBS_CR_HUB2_ARB_IPC_HUBS_LOW_PRIO_LIM_HSH                   (0x030C7218)

#define HUBS_CR_HUB3_UP_ARB_0_LIM_HUBS_REG                             (0x0000721C)

  #define HUBS_CR_HUB3_UP_ARB_0_LIM_HUBS_DMI_VC0_NP_OFF                ( 0)
  #define HUBS_CR_HUB3_UP_ARB_0_LIM_HUBS_DMI_VC0_NP_WID                ( 3)
  #define HUBS_CR_HUB3_UP_ARB_0_LIM_HUBS_DMI_VC0_NP_MSK                (0x00000007)
  #define HUBS_CR_HUB3_UP_ARB_0_LIM_HUBS_DMI_VC0_NP_MIN                (0)
  #define HUBS_CR_HUB3_UP_ARB_0_LIM_HUBS_DMI_VC0_NP_MAX                (7) // 0x00000007
  #define HUBS_CR_HUB3_UP_ARB_0_LIM_HUBS_DMI_VC0_NP_DEF                (0x00000004)
  #define HUBS_CR_HUB3_UP_ARB_0_LIM_HUBS_DMI_VC0_NP_HSH                (0x0300721C)

  #define HUBS_CR_HUB3_UP_ARB_0_LIM_HUBS_DMI_VC0_PC_OFF                ( 3)
  #define HUBS_CR_HUB3_UP_ARB_0_LIM_HUBS_DMI_VC0_PC_WID                ( 3)
  #define HUBS_CR_HUB3_UP_ARB_0_LIM_HUBS_DMI_VC0_PC_MSK                (0x00000038)
  #define HUBS_CR_HUB3_UP_ARB_0_LIM_HUBS_DMI_VC0_PC_MIN                (0)
  #define HUBS_CR_HUB3_UP_ARB_0_LIM_HUBS_DMI_VC0_PC_MAX                (7) // 0x00000007
  #define HUBS_CR_HUB3_UP_ARB_0_LIM_HUBS_DMI_VC0_PC_DEF                (0x00000004)
  #define HUBS_CR_HUB3_UP_ARB_0_LIM_HUBS_DMI_VC0_PC_HSH                (0x0303721C)

  #define HUBS_CR_HUB3_UP_ARB_0_LIM_HUBS_DE_VC0_NP_OFF                 ( 6)
  #define HUBS_CR_HUB3_UP_ARB_0_LIM_HUBS_DE_VC0_NP_WID                 ( 3)
  #define HUBS_CR_HUB3_UP_ARB_0_LIM_HUBS_DE_VC0_NP_MSK                 (0x000001C0)
  #define HUBS_CR_HUB3_UP_ARB_0_LIM_HUBS_DE_VC0_NP_MIN                 (0)
  #define HUBS_CR_HUB3_UP_ARB_0_LIM_HUBS_DE_VC0_NP_MAX                 (7) // 0x00000007
  #define HUBS_CR_HUB3_UP_ARB_0_LIM_HUBS_DE_VC0_NP_DEF                 (0x00000004)
  #define HUBS_CR_HUB3_UP_ARB_0_LIM_HUBS_DE_VC0_NP_HSH                 (0x0306721C)

  #define HUBS_CR_HUB3_UP_ARB_0_LIM_HUBS_DE_VC0_PC_OFF                 ( 9)
  #define HUBS_CR_HUB3_UP_ARB_0_LIM_HUBS_DE_VC0_PC_WID                 ( 3)
  #define HUBS_CR_HUB3_UP_ARB_0_LIM_HUBS_DE_VC0_PC_MSK                 (0x00000E00)
  #define HUBS_CR_HUB3_UP_ARB_0_LIM_HUBS_DE_VC0_PC_MIN                 (0)
  #define HUBS_CR_HUB3_UP_ARB_0_LIM_HUBS_DE_VC0_PC_MAX                 (7) // 0x00000007
  #define HUBS_CR_HUB3_UP_ARB_0_LIM_HUBS_DE_VC0_PC_DEF                 (0x00000004)
  #define HUBS_CR_HUB3_UP_ARB_0_LIM_HUBS_DE_VC0_PC_HSH                 (0x0309721C)

  #define HUBS_CR_HUB3_UP_ARB_0_LIM_HUBS_CAM_VC0_NP_OFF                (12)
  #define HUBS_CR_HUB3_UP_ARB_0_LIM_HUBS_CAM_VC0_NP_WID                ( 3)
  #define HUBS_CR_HUB3_UP_ARB_0_LIM_HUBS_CAM_VC0_NP_MSK                (0x00007000)
  #define HUBS_CR_HUB3_UP_ARB_0_LIM_HUBS_CAM_VC0_NP_MIN                (0)
  #define HUBS_CR_HUB3_UP_ARB_0_LIM_HUBS_CAM_VC0_NP_MAX                (7) // 0x00000007
  #define HUBS_CR_HUB3_UP_ARB_0_LIM_HUBS_CAM_VC0_NP_DEF                (0x00000004)
  #define HUBS_CR_HUB3_UP_ARB_0_LIM_HUBS_CAM_VC0_NP_HSH                (0x030C721C)

  #define HUBS_CR_HUB3_UP_ARB_0_LIM_HUBS_CAM_VC0_PC_OFF                (15)
  #define HUBS_CR_HUB3_UP_ARB_0_LIM_HUBS_CAM_VC0_PC_WID                ( 3)
  #define HUBS_CR_HUB3_UP_ARB_0_LIM_HUBS_CAM_VC0_PC_MSK                (0x00038000)
  #define HUBS_CR_HUB3_UP_ARB_0_LIM_HUBS_CAM_VC0_PC_MIN                (0)
  #define HUBS_CR_HUB3_UP_ARB_0_LIM_HUBS_CAM_VC0_PC_MAX                (7) // 0x00000007
  #define HUBS_CR_HUB3_UP_ARB_0_LIM_HUBS_CAM_VC0_PC_DEF                (0x00000004)
  #define HUBS_CR_HUB3_UP_ARB_0_LIM_HUBS_CAM_VC0_PC_HSH                (0x030F721C)

  #define HUBS_CR_HUB3_UP_ARB_0_LIM_HUBS_DMI_VCM_NP_OFF                (18)
  #define HUBS_CR_HUB3_UP_ARB_0_LIM_HUBS_DMI_VCM_NP_WID                ( 3)
  #define HUBS_CR_HUB3_UP_ARB_0_LIM_HUBS_DMI_VCM_NP_MSK                (0x001C0000)
  #define HUBS_CR_HUB3_UP_ARB_0_LIM_HUBS_DMI_VCM_NP_MIN                (0)
  #define HUBS_CR_HUB3_UP_ARB_0_LIM_HUBS_DMI_VCM_NP_MAX                (7) // 0x00000007
  #define HUBS_CR_HUB3_UP_ARB_0_LIM_HUBS_DMI_VCM_NP_DEF                (0x00000004)
  #define HUBS_CR_HUB3_UP_ARB_0_LIM_HUBS_DMI_VCM_NP_HSH                (0x0312721C)

  #define HUBS_CR_HUB3_UP_ARB_0_LIM_HUBS_DMI_VCM_PC_OFF                (21)
  #define HUBS_CR_HUB3_UP_ARB_0_LIM_HUBS_DMI_VCM_PC_WID                ( 3)
  #define HUBS_CR_HUB3_UP_ARB_0_LIM_HUBS_DMI_VCM_PC_MSK                (0x00E00000)
  #define HUBS_CR_HUB3_UP_ARB_0_LIM_HUBS_DMI_VCM_PC_MIN                (0)
  #define HUBS_CR_HUB3_UP_ARB_0_LIM_HUBS_DMI_VCM_PC_MAX                (7) // 0x00000007
  #define HUBS_CR_HUB3_UP_ARB_0_LIM_HUBS_DMI_VCM_PC_DEF                (0x00000004)
  #define HUBS_CR_HUB3_UP_ARB_0_LIM_HUBS_DMI_VCM_PC_HSH                (0x0315721C)

  #define HUBS_CR_HUB3_UP_ARB_0_LIM_HUBS_GMM_VC0_NP_OFF                (24)
  #define HUBS_CR_HUB3_UP_ARB_0_LIM_HUBS_GMM_VC0_NP_WID                ( 3)
  #define HUBS_CR_HUB3_UP_ARB_0_LIM_HUBS_GMM_VC0_NP_MSK                (0x07000000)
  #define HUBS_CR_HUB3_UP_ARB_0_LIM_HUBS_GMM_VC0_NP_MIN                (0)
  #define HUBS_CR_HUB3_UP_ARB_0_LIM_HUBS_GMM_VC0_NP_MAX                (7) // 0x00000007
  #define HUBS_CR_HUB3_UP_ARB_0_LIM_HUBS_GMM_VC0_NP_DEF                (0x00000004)
  #define HUBS_CR_HUB3_UP_ARB_0_LIM_HUBS_GMM_VC0_NP_HSH                (0x0318721C)

  #define HUBS_CR_HUB3_UP_ARB_0_LIM_HUBS_GMM_VC0_PC_OFF                (27)
  #define HUBS_CR_HUB3_UP_ARB_0_LIM_HUBS_GMM_VC0_PC_WID                ( 3)
  #define HUBS_CR_HUB3_UP_ARB_0_LIM_HUBS_GMM_VC0_PC_MSK                (0x38000000)
  #define HUBS_CR_HUB3_UP_ARB_0_LIM_HUBS_GMM_VC0_PC_MIN                (0)
  #define HUBS_CR_HUB3_UP_ARB_0_LIM_HUBS_GMM_VC0_PC_MAX                (7) // 0x00000007
  #define HUBS_CR_HUB3_UP_ARB_0_LIM_HUBS_GMM_VC0_PC_DEF                (0x00000004)
  #define HUBS_CR_HUB3_UP_ARB_0_LIM_HUBS_GMM_VC0_PC_HSH                (0x031B721C)

#define HUBS_CR_HUB3_ARB_IPC_HUBS_REG                                  (0x00007220)

  #define HUBS_CR_HUB3_ARB_IPC_HUBS_NON_VC1_THRESHOLD_OFF              ( 0)
  #define HUBS_CR_HUB3_ARB_IPC_HUBS_NON_VC1_THRESHOLD_WID              ( 4)
  #define HUBS_CR_HUB3_ARB_IPC_HUBS_NON_VC1_THRESHOLD_MSK              (0x0000000F)
  #define HUBS_CR_HUB3_ARB_IPC_HUBS_NON_VC1_THRESHOLD_MIN              (0)
  #define HUBS_CR_HUB3_ARB_IPC_HUBS_NON_VC1_THRESHOLD_MAX              (15) // 0x0000000F
  #define HUBS_CR_HUB3_ARB_IPC_HUBS_NON_VC1_THRESHOLD_DEF              (0x00000004)
  #define HUBS_CR_HUB3_ARB_IPC_HUBS_NON_VC1_THRESHOLD_HSH              (0x04007220)

  #define HUBS_CR_HUB3_ARB_IPC_HUBS_VC1_RD_THRESHOLD_OFF               ( 4)
  #define HUBS_CR_HUB3_ARB_IPC_HUBS_VC1_RD_THRESHOLD_WID               ( 4)
  #define HUBS_CR_HUB3_ARB_IPC_HUBS_VC1_RD_THRESHOLD_MSK               (0x000000F0)
  #define HUBS_CR_HUB3_ARB_IPC_HUBS_VC1_RD_THRESHOLD_MIN               (0)
  #define HUBS_CR_HUB3_ARB_IPC_HUBS_VC1_RD_THRESHOLD_MAX               (15) // 0x0000000F
  #define HUBS_CR_HUB3_ARB_IPC_HUBS_VC1_RD_THRESHOLD_DEF               (0x00000004)
  #define HUBS_CR_HUB3_ARB_IPC_HUBS_VC1_RD_THRESHOLD_HSH               (0x04047220)

  #define HUBS_CR_HUB3_ARB_IPC_HUBS_FIXED_RATEP_EN_OFF                 ( 8)
  #define HUBS_CR_HUB3_ARB_IPC_HUBS_FIXED_RATEP_EN_WID                 ( 1)
  #define HUBS_CR_HUB3_ARB_IPC_HUBS_FIXED_RATEP_EN_MSK                 (0x00000100)
  #define HUBS_CR_HUB3_ARB_IPC_HUBS_FIXED_RATEP_EN_MIN                 (0)
  #define HUBS_CR_HUB3_ARB_IPC_HUBS_FIXED_RATEP_EN_MAX                 (1) // 0x00000001
  #define HUBS_CR_HUB3_ARB_IPC_HUBS_FIXED_RATEP_EN_DEF                 (0x00000000)
  #define HUBS_CR_HUB3_ARB_IPC_HUBS_FIXED_RATEP_EN_HSH                 (0x01087220)

  #define HUBS_CR_HUB3_ARB_IPC_HUBS_HIGH_PRIO_LIM_OFF                  ( 9)
  #define HUBS_CR_HUB3_ARB_IPC_HUBS_HIGH_PRIO_LIM_WID                  ( 3)
  #define HUBS_CR_HUB3_ARB_IPC_HUBS_HIGH_PRIO_LIM_MSK                  (0x00000E00)
  #define HUBS_CR_HUB3_ARB_IPC_HUBS_HIGH_PRIO_LIM_MIN                  (0)
  #define HUBS_CR_HUB3_ARB_IPC_HUBS_HIGH_PRIO_LIM_MAX                  (7) // 0x00000007
  #define HUBS_CR_HUB3_ARB_IPC_HUBS_HIGH_PRIO_LIM_DEF                  (0x00000004)
  #define HUBS_CR_HUB3_ARB_IPC_HUBS_HIGH_PRIO_LIM_HSH                  (0x03097220)

  #define HUBS_CR_HUB3_ARB_IPC_HUBS_LOW_PRIO_LIM_OFF                   (12)
  #define HUBS_CR_HUB3_ARB_IPC_HUBS_LOW_PRIO_LIM_WID                   ( 3)
  #define HUBS_CR_HUB3_ARB_IPC_HUBS_LOW_PRIO_LIM_MSK                   (0x00007000)
  #define HUBS_CR_HUB3_ARB_IPC_HUBS_LOW_PRIO_LIM_MIN                   (0)
  #define HUBS_CR_HUB3_ARB_IPC_HUBS_LOW_PRIO_LIM_MAX                   (7) // 0x00000007
  #define HUBS_CR_HUB3_ARB_IPC_HUBS_LOW_PRIO_LIM_DEF                   (0x00000004)
  #define HUBS_CR_HUB3_ARB_IPC_HUBS_LOW_PRIO_LIM_HSH                   (0x030C7220)

#define HUBS_CR_HUB4_UP_ARB_0_LIM_HUBS_REG                             (0x00007224)

  #define HUBS_CR_HUB4_UP_ARB_0_LIM_HUBS_DE_VC0_NP_OFF                 ( 0)
  #define HUBS_CR_HUB4_UP_ARB_0_LIM_HUBS_DE_VC0_NP_WID                 ( 3)
  #define HUBS_CR_HUB4_UP_ARB_0_LIM_HUBS_DE_VC0_NP_MSK                 (0x00000007)
  #define HUBS_CR_HUB4_UP_ARB_0_LIM_HUBS_DE_VC0_NP_MIN                 (0)
  #define HUBS_CR_HUB4_UP_ARB_0_LIM_HUBS_DE_VC0_NP_MAX                 (7) // 0x00000007
  #define HUBS_CR_HUB4_UP_ARB_0_LIM_HUBS_DE_VC0_NP_DEF                 (0x00000004)
  #define HUBS_CR_HUB4_UP_ARB_0_LIM_HUBS_DE_VC0_NP_HSH                 (0x03007224)

  #define HUBS_CR_HUB4_UP_ARB_0_LIM_HUBS_DE_VC0_PC_OFF                 ( 3)
  #define HUBS_CR_HUB4_UP_ARB_0_LIM_HUBS_DE_VC0_PC_WID                 ( 3)
  #define HUBS_CR_HUB4_UP_ARB_0_LIM_HUBS_DE_VC0_PC_MSK                 (0x00000038)
  #define HUBS_CR_HUB4_UP_ARB_0_LIM_HUBS_DE_VC0_PC_MIN                 (0)
  #define HUBS_CR_HUB4_UP_ARB_0_LIM_HUBS_DE_VC0_PC_MAX                 (7) // 0x00000007
  #define HUBS_CR_HUB4_UP_ARB_0_LIM_HUBS_DE_VC0_PC_DEF                 (0x00000004)
  #define HUBS_CR_HUB4_UP_ARB_0_LIM_HUBS_DE_VC0_PC_HSH                 (0x03037224)

  #define HUBS_CR_HUB4_UP_ARB_0_LIM_HUBS_GMM_VC0_NP_OFF                ( 6)
  #define HUBS_CR_HUB4_UP_ARB_0_LIM_HUBS_GMM_VC0_NP_WID                ( 3)
  #define HUBS_CR_HUB4_UP_ARB_0_LIM_HUBS_GMM_VC0_NP_MSK                (0x000001C0)
  #define HUBS_CR_HUB4_UP_ARB_0_LIM_HUBS_GMM_VC0_NP_MIN                (0)
  #define HUBS_CR_HUB4_UP_ARB_0_LIM_HUBS_GMM_VC0_NP_MAX                (7) // 0x00000007
  #define HUBS_CR_HUB4_UP_ARB_0_LIM_HUBS_GMM_VC0_NP_DEF                (0x00000004)
  #define HUBS_CR_HUB4_UP_ARB_0_LIM_HUBS_GMM_VC0_NP_HSH                (0x03067224)

  #define HUBS_CR_HUB4_UP_ARB_0_LIM_HUBS_GMM_VC0_PC_OFF                ( 9)
  #define HUBS_CR_HUB4_UP_ARB_0_LIM_HUBS_GMM_VC0_PC_WID                ( 3)
  #define HUBS_CR_HUB4_UP_ARB_0_LIM_HUBS_GMM_VC0_PC_MSK                (0x00000E00)
  #define HUBS_CR_HUB4_UP_ARB_0_LIM_HUBS_GMM_VC0_PC_MIN                (0)
  #define HUBS_CR_HUB4_UP_ARB_0_LIM_HUBS_GMM_VC0_PC_MAX                (7) // 0x00000007
  #define HUBS_CR_HUB4_UP_ARB_0_LIM_HUBS_GMM_VC0_PC_DEF                (0x00000004)
  #define HUBS_CR_HUB4_UP_ARB_0_LIM_HUBS_GMM_VC0_PC_HSH                (0x03097224)

#define HUBS_CR_HUB4_ARB_IPC_HUBS_REG                                  (0x00007228)

  #define HUBS_CR_HUB4_ARB_IPC_HUBS_NON_VC1_THRESHOLD_OFF              ( 0)
  #define HUBS_CR_HUB4_ARB_IPC_HUBS_NON_VC1_THRESHOLD_WID              ( 4)
  #define HUBS_CR_HUB4_ARB_IPC_HUBS_NON_VC1_THRESHOLD_MSK              (0x0000000F)
  #define HUBS_CR_HUB4_ARB_IPC_HUBS_NON_VC1_THRESHOLD_MIN              (0)
  #define HUBS_CR_HUB4_ARB_IPC_HUBS_NON_VC1_THRESHOLD_MAX              (15) // 0x0000000F
  #define HUBS_CR_HUB4_ARB_IPC_HUBS_NON_VC1_THRESHOLD_DEF              (0x00000004)
  #define HUBS_CR_HUB4_ARB_IPC_HUBS_NON_VC1_THRESHOLD_HSH              (0x04007228)

  #define HUBS_CR_HUB4_ARB_IPC_HUBS_VC1_RD_THRESHOLD_OFF               ( 4)
  #define HUBS_CR_HUB4_ARB_IPC_HUBS_VC1_RD_THRESHOLD_WID               ( 4)
  #define HUBS_CR_HUB4_ARB_IPC_HUBS_VC1_RD_THRESHOLD_MSK               (0x000000F0)
  #define HUBS_CR_HUB4_ARB_IPC_HUBS_VC1_RD_THRESHOLD_MIN               (0)
  #define HUBS_CR_HUB4_ARB_IPC_HUBS_VC1_RD_THRESHOLD_MAX               (15) // 0x0000000F
  #define HUBS_CR_HUB4_ARB_IPC_HUBS_VC1_RD_THRESHOLD_DEF               (0x00000004)
  #define HUBS_CR_HUB4_ARB_IPC_HUBS_VC1_RD_THRESHOLD_HSH               (0x04047228)

  #define HUBS_CR_HUB4_ARB_IPC_HUBS_FIXED_RATEP_EN_OFF                 ( 8)
  #define HUBS_CR_HUB4_ARB_IPC_HUBS_FIXED_RATEP_EN_WID                 ( 1)
  #define HUBS_CR_HUB4_ARB_IPC_HUBS_FIXED_RATEP_EN_MSK                 (0x00000100)
  #define HUBS_CR_HUB4_ARB_IPC_HUBS_FIXED_RATEP_EN_MIN                 (0)
  #define HUBS_CR_HUB4_ARB_IPC_HUBS_FIXED_RATEP_EN_MAX                 (1) // 0x00000001
  #define HUBS_CR_HUB4_ARB_IPC_HUBS_FIXED_RATEP_EN_DEF                 (0x00000000)
  #define HUBS_CR_HUB4_ARB_IPC_HUBS_FIXED_RATEP_EN_HSH                 (0x01087228)

  #define HUBS_CR_HUB4_ARB_IPC_HUBS_HIGH_PRIO_LIM_OFF                  ( 9)
  #define HUBS_CR_HUB4_ARB_IPC_HUBS_HIGH_PRIO_LIM_WID                  ( 3)
  #define HUBS_CR_HUB4_ARB_IPC_HUBS_HIGH_PRIO_LIM_MSK                  (0x00000E00)
  #define HUBS_CR_HUB4_ARB_IPC_HUBS_HIGH_PRIO_LIM_MIN                  (0)
  #define HUBS_CR_HUB4_ARB_IPC_HUBS_HIGH_PRIO_LIM_MAX                  (7) // 0x00000007
  #define HUBS_CR_HUB4_ARB_IPC_HUBS_HIGH_PRIO_LIM_DEF                  (0x00000004)
  #define HUBS_CR_HUB4_ARB_IPC_HUBS_HIGH_PRIO_LIM_HSH                  (0x03097228)

  #define HUBS_CR_HUB4_ARB_IPC_HUBS_LOW_PRIO_LIM_OFF                   (12)
  #define HUBS_CR_HUB4_ARB_IPC_HUBS_LOW_PRIO_LIM_WID                   ( 3)
  #define HUBS_CR_HUB4_ARB_IPC_HUBS_LOW_PRIO_LIM_MSK                   (0x00007000)
  #define HUBS_CR_HUB4_ARB_IPC_HUBS_LOW_PRIO_LIM_MIN                   (0)
  #define HUBS_CR_HUB4_ARB_IPC_HUBS_LOW_PRIO_LIM_MAX                   (7) // 0x00000007
  #define HUBS_CR_HUB4_ARB_IPC_HUBS_LOW_PRIO_LIM_DEF                   (0x00000004)
  #define HUBS_CR_HUB4_ARB_IPC_HUBS_LOW_PRIO_LIM_HSH                   (0x030C7228)

#define HUBS_CR_HUB0_DN_ARB_0_LIM_HUBS_REG                             (0x0000722C)

  #define HUBS_CR_HUB0_DN_ARB_0_LIM_HUBS_DMI_VC0_MRG_OFF               ( 0)
  #define HUBS_CR_HUB0_DN_ARB_0_LIM_HUBS_DMI_VC0_MRG_WID               ( 3)
  #define HUBS_CR_HUB0_DN_ARB_0_LIM_HUBS_DMI_VC0_MRG_MSK               (0x00000007)
  #define HUBS_CR_HUB0_DN_ARB_0_LIM_HUBS_DMI_VC0_MRG_MIN               (0)
  #define HUBS_CR_HUB0_DN_ARB_0_LIM_HUBS_DMI_VC0_MRG_MAX               (7) // 0x00000007
  #define HUBS_CR_HUB0_DN_ARB_0_LIM_HUBS_DMI_VC0_MRG_DEF               (0x00000004)
  #define HUBS_CR_HUB0_DN_ARB_0_LIM_HUBS_DMI_VC0_MRG_HSH               (0x0300722C)

  #define HUBS_CR_HUB0_DN_ARB_0_LIM_HUBS_DMI_VC0_RLX_OFF               ( 3)
  #define HUBS_CR_HUB0_DN_ARB_0_LIM_HUBS_DMI_VC0_RLX_WID               ( 3)
  #define HUBS_CR_HUB0_DN_ARB_0_LIM_HUBS_DMI_VC0_RLX_MSK               (0x00000038)
  #define HUBS_CR_HUB0_DN_ARB_0_LIM_HUBS_DMI_VC0_RLX_MIN               (0)
  #define HUBS_CR_HUB0_DN_ARB_0_LIM_HUBS_DMI_VC0_RLX_MAX               (7) // 0x00000007
  #define HUBS_CR_HUB0_DN_ARB_0_LIM_HUBS_DMI_VC0_RLX_DEF               (0x00000004)
  #define HUBS_CR_HUB0_DN_ARB_0_LIM_HUBS_DMI_VC0_RLX_HSH               (0x0303722C)

  #define HUBS_CR_HUB0_DN_ARB_0_LIM_HUBS_P16_VC0_MRG_OFF               ( 6)
  #define HUBS_CR_HUB0_DN_ARB_0_LIM_HUBS_P16_VC0_MRG_WID               ( 3)
  #define HUBS_CR_HUB0_DN_ARB_0_LIM_HUBS_P16_VC0_MRG_MSK               (0x000001C0)
  #define HUBS_CR_HUB0_DN_ARB_0_LIM_HUBS_P16_VC0_MRG_MIN               (0)
  #define HUBS_CR_HUB0_DN_ARB_0_LIM_HUBS_P16_VC0_MRG_MAX               (7) // 0x00000007
  #define HUBS_CR_HUB0_DN_ARB_0_LIM_HUBS_P16_VC0_MRG_DEF               (0x00000004)
  #define HUBS_CR_HUB0_DN_ARB_0_LIM_HUBS_P16_VC0_MRG_HSH               (0x0306722C)

  #define HUBS_CR_HUB0_DN_ARB_0_LIM_HUBS_P16_VC0_RLX_OFF               ( 9)
  #define HUBS_CR_HUB0_DN_ARB_0_LIM_HUBS_P16_VC0_RLX_WID               ( 3)
  #define HUBS_CR_HUB0_DN_ARB_0_LIM_HUBS_P16_VC0_RLX_MSK               (0x00000E00)
  #define HUBS_CR_HUB0_DN_ARB_0_LIM_HUBS_P16_VC0_RLX_MIN               (0)
  #define HUBS_CR_HUB0_DN_ARB_0_LIM_HUBS_P16_VC0_RLX_MAX               (7) // 0x00000007
  #define HUBS_CR_HUB0_DN_ARB_0_LIM_HUBS_P16_VC0_RLX_DEF               (0x00000004)
  #define HUBS_CR_HUB0_DN_ARB_0_LIM_HUBS_P16_VC0_RLX_HSH               (0x0309722C)

  #define HUBS_CR_HUB0_DN_ARB_0_LIM_HUBS_P08_VC0_MRG_OFF               (12)
  #define HUBS_CR_HUB0_DN_ARB_0_LIM_HUBS_P08_VC0_MRG_WID               ( 3)
  #define HUBS_CR_HUB0_DN_ARB_0_LIM_HUBS_P08_VC0_MRG_MSK               (0x00007000)
  #define HUBS_CR_HUB0_DN_ARB_0_LIM_HUBS_P08_VC0_MRG_MIN               (0)
  #define HUBS_CR_HUB0_DN_ARB_0_LIM_HUBS_P08_VC0_MRG_MAX               (7) // 0x00000007
  #define HUBS_CR_HUB0_DN_ARB_0_LIM_HUBS_P08_VC0_MRG_DEF               (0x00000004)
  #define HUBS_CR_HUB0_DN_ARB_0_LIM_HUBS_P08_VC0_MRG_HSH               (0x030C722C)

  #define HUBS_CR_HUB0_DN_ARB_0_LIM_HUBS_P08_VC0_RLX_OFF               (15)
  #define HUBS_CR_HUB0_DN_ARB_0_LIM_HUBS_P08_VC0_RLX_WID               ( 3)
  #define HUBS_CR_HUB0_DN_ARB_0_LIM_HUBS_P08_VC0_RLX_MSK               (0x00038000)
  #define HUBS_CR_HUB0_DN_ARB_0_LIM_HUBS_P08_VC0_RLX_MIN               (0)
  #define HUBS_CR_HUB0_DN_ARB_0_LIM_HUBS_P08_VC0_RLX_MAX               (7) // 0x00000007
  #define HUBS_CR_HUB0_DN_ARB_0_LIM_HUBS_P08_VC0_RLX_DEF               (0x00000004)
  #define HUBS_CR_HUB0_DN_ARB_0_LIM_HUBS_P08_VC0_RLX_HSH               (0x030F722C)

  #define HUBS_CR_HUB0_DN_ARB_0_LIM_HUBS_P4A_VC0_MRG_OFF               (18)
  #define HUBS_CR_HUB0_DN_ARB_0_LIM_HUBS_P4A_VC0_MRG_WID               ( 3)
  #define HUBS_CR_HUB0_DN_ARB_0_LIM_HUBS_P4A_VC0_MRG_MSK               (0x001C0000)
  #define HUBS_CR_HUB0_DN_ARB_0_LIM_HUBS_P4A_VC0_MRG_MIN               (0)
  #define HUBS_CR_HUB0_DN_ARB_0_LIM_HUBS_P4A_VC0_MRG_MAX               (7) // 0x00000007
  #define HUBS_CR_HUB0_DN_ARB_0_LIM_HUBS_P4A_VC0_MRG_DEF               (0x00000004)
  #define HUBS_CR_HUB0_DN_ARB_0_LIM_HUBS_P4A_VC0_MRG_HSH               (0x0312722C)

  #define HUBS_CR_HUB0_DN_ARB_0_LIM_HUBS_P4A_VC0_RLX_OFF               (21)
  #define HUBS_CR_HUB0_DN_ARB_0_LIM_HUBS_P4A_VC0_RLX_WID               ( 3)
  #define HUBS_CR_HUB0_DN_ARB_0_LIM_HUBS_P4A_VC0_RLX_MSK               (0x00E00000)
  #define HUBS_CR_HUB0_DN_ARB_0_LIM_HUBS_P4A_VC0_RLX_MIN               (0)
  #define HUBS_CR_HUB0_DN_ARB_0_LIM_HUBS_P4A_VC0_RLX_MAX               (7) // 0x00000007
  #define HUBS_CR_HUB0_DN_ARB_0_LIM_HUBS_P4A_VC0_RLX_DEF               (0x00000004)
  #define HUBS_CR_HUB0_DN_ARB_0_LIM_HUBS_P4A_VC0_RLX_HSH               (0x0315722C)

  #define HUBS_CR_HUB0_DN_ARB_0_LIM_HUBS_DE_VC0_MRG_OFF                (24)
  #define HUBS_CR_HUB0_DN_ARB_0_LIM_HUBS_DE_VC0_MRG_WID                ( 3)
  #define HUBS_CR_HUB0_DN_ARB_0_LIM_HUBS_DE_VC0_MRG_MSK                (0x07000000)
  #define HUBS_CR_HUB0_DN_ARB_0_LIM_HUBS_DE_VC0_MRG_MIN                (0)
  #define HUBS_CR_HUB0_DN_ARB_0_LIM_HUBS_DE_VC0_MRG_MAX                (7) // 0x00000007
  #define HUBS_CR_HUB0_DN_ARB_0_LIM_HUBS_DE_VC0_MRG_DEF                (0x00000004)
  #define HUBS_CR_HUB0_DN_ARB_0_LIM_HUBS_DE_VC0_MRG_HSH                (0x0318722C)

  #define HUBS_CR_HUB0_DN_ARB_0_LIM_HUBS_DMI_VCM_MRG_OFF               (27)
  #define HUBS_CR_HUB0_DN_ARB_0_LIM_HUBS_DMI_VCM_MRG_WID               ( 3)
  #define HUBS_CR_HUB0_DN_ARB_0_LIM_HUBS_DMI_VCM_MRG_MSK               (0x38000000)
  #define HUBS_CR_HUB0_DN_ARB_0_LIM_HUBS_DMI_VCM_MRG_MIN               (0)
  #define HUBS_CR_HUB0_DN_ARB_0_LIM_HUBS_DMI_VCM_MRG_MAX               (7) // 0x00000007
  #define HUBS_CR_HUB0_DN_ARB_0_LIM_HUBS_DMI_VCM_MRG_DEF               (0x00000004)
  #define HUBS_CR_HUB0_DN_ARB_0_LIM_HUBS_DMI_VCM_MRG_HSH               (0x031B722C)

#define HUBS_CR_HUB0_DN_ARB_1_LIM_HUBS_REG                             (0x00007230)

  #define HUBS_CR_HUB0_DN_ARB_1_LIM_HUBS_GMM_VC0_MRG_OFF               ( 0)
  #define HUBS_CR_HUB0_DN_ARB_1_LIM_HUBS_GMM_VC0_MRG_WID               ( 3)
  #define HUBS_CR_HUB0_DN_ARB_1_LIM_HUBS_GMM_VC0_MRG_MSK               (0x00000007)
  #define HUBS_CR_HUB0_DN_ARB_1_LIM_HUBS_GMM_VC0_MRG_MIN               (0)
  #define HUBS_CR_HUB0_DN_ARB_1_LIM_HUBS_GMM_VC0_MRG_MAX               (7) // 0x00000007
  #define HUBS_CR_HUB0_DN_ARB_1_LIM_HUBS_GMM_VC0_MRG_DEF               (0x00000004)
  #define HUBS_CR_HUB0_DN_ARB_1_LIM_HUBS_GMM_VC0_MRG_HSH               (0x03007230)

  #define HUBS_CR_HUB0_DN_ARB_1_LIM_HUBS_RESERVED_OFF                  ( 3)
  #define HUBS_CR_HUB0_DN_ARB_1_LIM_HUBS_RESERVED_WID                  (12)
  #define HUBS_CR_HUB0_DN_ARB_1_LIM_HUBS_RESERVED_MSK                  (0x00007FF8)
  #define HUBS_CR_HUB0_DN_ARB_1_LIM_HUBS_RESERVED_MIN                  (0)
  #define HUBS_CR_HUB0_DN_ARB_1_LIM_HUBS_RESERVED_MAX                  (4095) // 0x00000FFF
  #define HUBS_CR_HUB0_DN_ARB_1_LIM_HUBS_RESERVED_DEF                  (0x00000924)
  #define HUBS_CR_HUB0_DN_ARB_1_LIM_HUBS_RESERVED_HSH                  (0x0C037230)

#define HUBS_CR_HUB1_DN_ARB_0_LIM_HUBS_REG                             (0x00007234)

  #define HUBS_CR_HUB1_DN_ARB_0_LIM_HUBS_DMI_VC0_MRG_OFF               ( 0)
  #define HUBS_CR_HUB1_DN_ARB_0_LIM_HUBS_DMI_VC0_MRG_WID               ( 3)
  #define HUBS_CR_HUB1_DN_ARB_0_LIM_HUBS_DMI_VC0_MRG_MSK               (0x00000007)
  #define HUBS_CR_HUB1_DN_ARB_0_LIM_HUBS_DMI_VC0_MRG_MIN               (0)
  #define HUBS_CR_HUB1_DN_ARB_0_LIM_HUBS_DMI_VC0_MRG_MAX               (7) // 0x00000007
  #define HUBS_CR_HUB1_DN_ARB_0_LIM_HUBS_DMI_VC0_MRG_DEF               (0x00000004)
  #define HUBS_CR_HUB1_DN_ARB_0_LIM_HUBS_DMI_VC0_MRG_HSH               (0x03007234)

  #define HUBS_CR_HUB1_DN_ARB_0_LIM_HUBS_DMI_VC0_RLX_OFF               ( 3)
  #define HUBS_CR_HUB1_DN_ARB_0_LIM_HUBS_DMI_VC0_RLX_WID               ( 3)
  #define HUBS_CR_HUB1_DN_ARB_0_LIM_HUBS_DMI_VC0_RLX_MSK               (0x00000038)
  #define HUBS_CR_HUB1_DN_ARB_0_LIM_HUBS_DMI_VC0_RLX_MIN               (0)
  #define HUBS_CR_HUB1_DN_ARB_0_LIM_HUBS_DMI_VC0_RLX_MAX               (7) // 0x00000007
  #define HUBS_CR_HUB1_DN_ARB_0_LIM_HUBS_DMI_VC0_RLX_DEF               (0x00000004)
  #define HUBS_CR_HUB1_DN_ARB_0_LIM_HUBS_DMI_VC0_RLX_HSH               (0x03037234)

  #define HUBS_CR_HUB1_DN_ARB_0_LIM_HUBS_P4A_VC0_MRG_OFF               ( 6)
  #define HUBS_CR_HUB1_DN_ARB_0_LIM_HUBS_P4A_VC0_MRG_WID               ( 3)
  #define HUBS_CR_HUB1_DN_ARB_0_LIM_HUBS_P4A_VC0_MRG_MSK               (0x000001C0)
  #define HUBS_CR_HUB1_DN_ARB_0_LIM_HUBS_P4A_VC0_MRG_MIN               (0)
  #define HUBS_CR_HUB1_DN_ARB_0_LIM_HUBS_P4A_VC0_MRG_MAX               (7) // 0x00000007
  #define HUBS_CR_HUB1_DN_ARB_0_LIM_HUBS_P4A_VC0_MRG_DEF               (0x00000004)
  #define HUBS_CR_HUB1_DN_ARB_0_LIM_HUBS_P4A_VC0_MRG_HSH               (0x03067234)

  #define HUBS_CR_HUB1_DN_ARB_0_LIM_HUBS_P4A_VC0_RLX_OFF               ( 9)
  #define HUBS_CR_HUB1_DN_ARB_0_LIM_HUBS_P4A_VC0_RLX_WID               ( 3)
  #define HUBS_CR_HUB1_DN_ARB_0_LIM_HUBS_P4A_VC0_RLX_MSK               (0x00000E00)
  #define HUBS_CR_HUB1_DN_ARB_0_LIM_HUBS_P4A_VC0_RLX_MIN               (0)
  #define HUBS_CR_HUB1_DN_ARB_0_LIM_HUBS_P4A_VC0_RLX_MAX               (7) // 0x00000007
  #define HUBS_CR_HUB1_DN_ARB_0_LIM_HUBS_P4A_VC0_RLX_DEF               (0x00000004)
  #define HUBS_CR_HUB1_DN_ARB_0_LIM_HUBS_P4A_VC0_RLX_HSH               (0x03097234)

  #define HUBS_CR_HUB1_DN_ARB_0_LIM_HUBS_DMI_VCM_MRG_OFF               (12)
  #define HUBS_CR_HUB1_DN_ARB_0_LIM_HUBS_DMI_VCM_MRG_WID               ( 3)
  #define HUBS_CR_HUB1_DN_ARB_0_LIM_HUBS_DMI_VCM_MRG_MSK               (0x00007000)
  #define HUBS_CR_HUB1_DN_ARB_0_LIM_HUBS_DMI_VCM_MRG_MIN               (0)
  #define HUBS_CR_HUB1_DN_ARB_0_LIM_HUBS_DMI_VCM_MRG_MAX               (7) // 0x00000007
  #define HUBS_CR_HUB1_DN_ARB_0_LIM_HUBS_DMI_VCM_MRG_DEF               (0x00000004)
  #define HUBS_CR_HUB1_DN_ARB_0_LIM_HUBS_DMI_VCM_MRG_HSH               (0x030C7234)

  #define HUBS_CR_HUB1_DN_ARB_0_LIM_HUBS_GMM_VC0_MRG_OFF               (15)
  #define HUBS_CR_HUB1_DN_ARB_0_LIM_HUBS_GMM_VC0_MRG_WID               ( 3)
  #define HUBS_CR_HUB1_DN_ARB_0_LIM_HUBS_GMM_VC0_MRG_MSK               (0x00038000)
  #define HUBS_CR_HUB1_DN_ARB_0_LIM_HUBS_GMM_VC0_MRG_MIN               (0)
  #define HUBS_CR_HUB1_DN_ARB_0_LIM_HUBS_GMM_VC0_MRG_MAX               (7) // 0x00000007
  #define HUBS_CR_HUB1_DN_ARB_0_LIM_HUBS_GMM_VC0_MRG_DEF               (0x00000004)
  #define HUBS_CR_HUB1_DN_ARB_0_LIM_HUBS_GMM_VC0_MRG_HSH               (0x030F7234)

#define HUBS_CR_HUB2_DN_ARB_0_LIM_HUBS_REG                             (0x00007238)

  #define HUBS_CR_HUB2_DN_ARB_0_LIM_HUBS_P16_VC0_MRG_OFF               ( 0)
  #define HUBS_CR_HUB2_DN_ARB_0_LIM_HUBS_P16_VC0_MRG_WID               ( 3)
  #define HUBS_CR_HUB2_DN_ARB_0_LIM_HUBS_P16_VC0_MRG_MSK               (0x00000007)
  #define HUBS_CR_HUB2_DN_ARB_0_LIM_HUBS_P16_VC0_MRG_MIN               (0)
  #define HUBS_CR_HUB2_DN_ARB_0_LIM_HUBS_P16_VC0_MRG_MAX               (7) // 0x00000007
  #define HUBS_CR_HUB2_DN_ARB_0_LIM_HUBS_P16_VC0_MRG_DEF               (0x00000004)
  #define HUBS_CR_HUB2_DN_ARB_0_LIM_HUBS_P16_VC0_MRG_HSH               (0x03007238)

  #define HUBS_CR_HUB2_DN_ARB_0_LIM_HUBS_P16_VC0_RLX_OFF               ( 3)
  #define HUBS_CR_HUB2_DN_ARB_0_LIM_HUBS_P16_VC0_RLX_WID               ( 3)
  #define HUBS_CR_HUB2_DN_ARB_0_LIM_HUBS_P16_VC0_RLX_MSK               (0x00000038)
  #define HUBS_CR_HUB2_DN_ARB_0_LIM_HUBS_P16_VC0_RLX_MIN               (0)
  #define HUBS_CR_HUB2_DN_ARB_0_LIM_HUBS_P16_VC0_RLX_MAX               (7) // 0x00000007
  #define HUBS_CR_HUB2_DN_ARB_0_LIM_HUBS_P16_VC0_RLX_DEF               (0x00000004)
  #define HUBS_CR_HUB2_DN_ARB_0_LIM_HUBS_P16_VC0_RLX_HSH               (0x03037238)

  #define HUBS_CR_HUB2_DN_ARB_0_LIM_HUBS_DE_VC0_MRG_OFF                ( 6)
  #define HUBS_CR_HUB2_DN_ARB_0_LIM_HUBS_DE_VC0_MRG_WID                ( 3)
  #define HUBS_CR_HUB2_DN_ARB_0_LIM_HUBS_DE_VC0_MRG_MSK                (0x000001C0)
  #define HUBS_CR_HUB2_DN_ARB_0_LIM_HUBS_DE_VC0_MRG_MIN                (0)
  #define HUBS_CR_HUB2_DN_ARB_0_LIM_HUBS_DE_VC0_MRG_MAX                (7) // 0x00000007
  #define HUBS_CR_HUB2_DN_ARB_0_LIM_HUBS_DE_VC0_MRG_DEF                (0x00000004)
  #define HUBS_CR_HUB2_DN_ARB_0_LIM_HUBS_DE_VC0_MRG_HSH                (0x03067238)

#define HUBS_CR_HUB3_DN_ARB_0_LIM_HUBS_REG                             (0x0000723C)

  #define HUBS_CR_HUB3_DN_ARB_0_LIM_HUBS_DMI_VC0_MRG_OFF               ( 0)
  #define HUBS_CR_HUB3_DN_ARB_0_LIM_HUBS_DMI_VC0_MRG_WID               ( 3)
  #define HUBS_CR_HUB3_DN_ARB_0_LIM_HUBS_DMI_VC0_MRG_MSK               (0x00000007)
  #define HUBS_CR_HUB3_DN_ARB_0_LIM_HUBS_DMI_VC0_MRG_MIN               (0)
  #define HUBS_CR_HUB3_DN_ARB_0_LIM_HUBS_DMI_VC0_MRG_MAX               (7) // 0x00000007
  #define HUBS_CR_HUB3_DN_ARB_0_LIM_HUBS_DMI_VC0_MRG_DEF               (0x00000004)
  #define HUBS_CR_HUB3_DN_ARB_0_LIM_HUBS_DMI_VC0_MRG_HSH               (0x0300723C)

  #define HUBS_CR_HUB3_DN_ARB_0_LIM_HUBS_DMI_VC0_RLX_OFF               ( 3)
  #define HUBS_CR_HUB3_DN_ARB_0_LIM_HUBS_DMI_VC0_RLX_WID               ( 3)
  #define HUBS_CR_HUB3_DN_ARB_0_LIM_HUBS_DMI_VC0_RLX_MSK               (0x00000038)
  #define HUBS_CR_HUB3_DN_ARB_0_LIM_HUBS_DMI_VC0_RLX_MIN               (0)
  #define HUBS_CR_HUB3_DN_ARB_0_LIM_HUBS_DMI_VC0_RLX_MAX               (7) // 0x00000007
  #define HUBS_CR_HUB3_DN_ARB_0_LIM_HUBS_DMI_VC0_RLX_DEF               (0x00000004)
  #define HUBS_CR_HUB3_DN_ARB_0_LIM_HUBS_DMI_VC0_RLX_HSH               (0x0303723C)

  #define HUBS_CR_HUB3_DN_ARB_0_LIM_HUBS_DE_VC0_MRG_OFF                ( 6)
  #define HUBS_CR_HUB3_DN_ARB_0_LIM_HUBS_DE_VC0_MRG_WID                ( 3)
  #define HUBS_CR_HUB3_DN_ARB_0_LIM_HUBS_DE_VC0_MRG_MSK                (0x000001C0)
  #define HUBS_CR_HUB3_DN_ARB_0_LIM_HUBS_DE_VC0_MRG_MIN                (0)
  #define HUBS_CR_HUB3_DN_ARB_0_LIM_HUBS_DE_VC0_MRG_MAX                (7) // 0x00000007
  #define HUBS_CR_HUB3_DN_ARB_0_LIM_HUBS_DE_VC0_MRG_DEF                (0x00000004)
  #define HUBS_CR_HUB3_DN_ARB_0_LIM_HUBS_DE_VC0_MRG_HSH                (0x0306723C)

  #define HUBS_CR_HUB3_DN_ARB_0_LIM_HUBS_CAM_VC0_MRG_OFF               ( 9)
  #define HUBS_CR_HUB3_DN_ARB_0_LIM_HUBS_CAM_VC0_MRG_WID               ( 3)
  #define HUBS_CR_HUB3_DN_ARB_0_LIM_HUBS_CAM_VC0_MRG_MSK               (0x00000E00)
  #define HUBS_CR_HUB3_DN_ARB_0_LIM_HUBS_CAM_VC0_MRG_MIN               (0)
  #define HUBS_CR_HUB3_DN_ARB_0_LIM_HUBS_CAM_VC0_MRG_MAX               (7) // 0x00000007
  #define HUBS_CR_HUB3_DN_ARB_0_LIM_HUBS_CAM_VC0_MRG_DEF               (0x00000004)
  #define HUBS_CR_HUB3_DN_ARB_0_LIM_HUBS_CAM_VC0_MRG_HSH               (0x0309723C)

  #define HUBS_CR_HUB3_DN_ARB_0_LIM_HUBS_DMI_VCM_MRG_OFF               (12)
  #define HUBS_CR_HUB3_DN_ARB_0_LIM_HUBS_DMI_VCM_MRG_WID               ( 3)
  #define HUBS_CR_HUB3_DN_ARB_0_LIM_HUBS_DMI_VCM_MRG_MSK               (0x00007000)
  #define HUBS_CR_HUB3_DN_ARB_0_LIM_HUBS_DMI_VCM_MRG_MIN               (0)
  #define HUBS_CR_HUB3_DN_ARB_0_LIM_HUBS_DMI_VCM_MRG_MAX               (7) // 0x00000007
  #define HUBS_CR_HUB3_DN_ARB_0_LIM_HUBS_DMI_VCM_MRG_DEF               (0x00000004)
  #define HUBS_CR_HUB3_DN_ARB_0_LIM_HUBS_DMI_VCM_MRG_HSH               (0x030C723C)

  #define HUBS_CR_HUB3_DN_ARB_0_LIM_HUBS_GMM_VC0_MRG_OFF               (15)
  #define HUBS_CR_HUB3_DN_ARB_0_LIM_HUBS_GMM_VC0_MRG_WID               ( 3)
  #define HUBS_CR_HUB3_DN_ARB_0_LIM_HUBS_GMM_VC0_MRG_MSK               (0x00038000)
  #define HUBS_CR_HUB3_DN_ARB_0_LIM_HUBS_GMM_VC0_MRG_MIN               (0)
  #define HUBS_CR_HUB3_DN_ARB_0_LIM_HUBS_GMM_VC0_MRG_MAX               (7) // 0x00000007
  #define HUBS_CR_HUB3_DN_ARB_0_LIM_HUBS_GMM_VC0_MRG_DEF               (0x00000004)
  #define HUBS_CR_HUB3_DN_ARB_0_LIM_HUBS_GMM_VC0_MRG_HSH               (0x030F723C)

#define HUBS_CR_HUB4_DN_ARB_0_LIM_HUBS_REG                             (0x00007240)

  #define HUBS_CR_HUB4_DN_ARB_0_LIM_HUBS_DE_VC0_MRG_OFF                ( 0)
  #define HUBS_CR_HUB4_DN_ARB_0_LIM_HUBS_DE_VC0_MRG_WID                ( 3)
  #define HUBS_CR_HUB4_DN_ARB_0_LIM_HUBS_DE_VC0_MRG_MSK                (0x00000007)
  #define HUBS_CR_HUB4_DN_ARB_0_LIM_HUBS_DE_VC0_MRG_MIN                (0)
  #define HUBS_CR_HUB4_DN_ARB_0_LIM_HUBS_DE_VC0_MRG_MAX                (7) // 0x00000007
  #define HUBS_CR_HUB4_DN_ARB_0_LIM_HUBS_DE_VC0_MRG_DEF                (0x00000004)
  #define HUBS_CR_HUB4_DN_ARB_0_LIM_HUBS_DE_VC0_MRG_HSH                (0x03007240)

  #define HUBS_CR_HUB4_DN_ARB_0_LIM_HUBS_GMM_VC0_MRG_OFF               ( 3)
  #define HUBS_CR_HUB4_DN_ARB_0_LIM_HUBS_GMM_VC0_MRG_WID               ( 3)
  #define HUBS_CR_HUB4_DN_ARB_0_LIM_HUBS_GMM_VC0_MRG_MSK               (0x00000038)
  #define HUBS_CR_HUB4_DN_ARB_0_LIM_HUBS_GMM_VC0_MRG_MIN               (0)
  #define HUBS_CR_HUB4_DN_ARB_0_LIM_HUBS_GMM_VC0_MRG_MAX               (7) // 0x00000007
  #define HUBS_CR_HUB4_DN_ARB_0_LIM_HUBS_GMM_VC0_MRG_DEF               (0x00000004)
  #define HUBS_CR_HUB4_DN_ARB_0_LIM_HUBS_GMM_VC0_MRG_HSH               (0x03037240)

#define HUBS_CR_H0_SPARE_HUBS_REG                                      (0x00007244)

  #define HUBS_CR_H0_SPARE_HUBS_SPARE_OFF                              ( 0)
  #define HUBS_CR_H0_SPARE_HUBS_SPARE_WID                              (32)
  #define HUBS_CR_H0_SPARE_HUBS_SPARE_MSK                              (0xFFFFFFFF)
  #define HUBS_CR_H0_SPARE_HUBS_SPARE_MIN                              (0)
  #define HUBS_CR_H0_SPARE_HUBS_SPARE_MAX                              (4294967295) // 0xFFFFFFFF
  #define HUBS_CR_H0_SPARE_HUBS_SPARE_DEF                              (0x00000000)
  #define HUBS_CR_H0_SPARE_HUBS_SPARE_HSH                              (0x20007244)

#define HUBS_CR_H1_SPARE_HUBS_REG                                      (0x00007248)

  #define HUBS_CR_H1_SPARE_HUBS_SPARE_OFF                              ( 0)
  #define HUBS_CR_H1_SPARE_HUBS_SPARE_WID                              (32)
  #define HUBS_CR_H1_SPARE_HUBS_SPARE_MSK                              (0xFFFFFFFF)
  #define HUBS_CR_H1_SPARE_HUBS_SPARE_MIN                              (0)
  #define HUBS_CR_H1_SPARE_HUBS_SPARE_MAX                              (4294967295) // 0xFFFFFFFF
  #define HUBS_CR_H1_SPARE_HUBS_SPARE_DEF                              (0x00000000)
  #define HUBS_CR_H1_SPARE_HUBS_SPARE_HSH                              (0x20007248)

#define MPRDRTRN_CR_CRDTCTL0_IMPH_REG                                  (0x00007400)

  #define MPRDRTRN_CR_CRDTCTL0_IMPH_DMIVC0_PMIN_OFF                    ( 0)
  #define MPRDRTRN_CR_CRDTCTL0_IMPH_DMIVC0_PMIN_WID                    ( 3)
  #define MPRDRTRN_CR_CRDTCTL0_IMPH_DMIVC0_PMIN_MSK                    (0x00000007)
  #define MPRDRTRN_CR_CRDTCTL0_IMPH_DMIVC0_PMIN_MIN                    (0)
  #define MPRDRTRN_CR_CRDTCTL0_IMPH_DMIVC0_PMIN_MAX                    (7) // 0x00000007
  #define MPRDRTRN_CR_CRDTCTL0_IMPH_DMIVC0_PMIN_DEF                    (0x00000000)
  #define MPRDRTRN_CR_CRDTCTL0_IMPH_DMIVC0_PMIN_HSH                    (0x03007400)

  #define MPRDRTRN_CR_CRDTCTL0_IMPH_P10VC0_PMIN_OFF                    ( 3)
  #define MPRDRTRN_CR_CRDTCTL0_IMPH_P10VC0_PMIN_WID                    ( 3)
  #define MPRDRTRN_CR_CRDTCTL0_IMPH_P10VC0_PMIN_MSK                    (0x00000038)
  #define MPRDRTRN_CR_CRDTCTL0_IMPH_P10VC0_PMIN_MIN                    (0)
  #define MPRDRTRN_CR_CRDTCTL0_IMPH_P10VC0_PMIN_MAX                    (7) // 0x00000007
  #define MPRDRTRN_CR_CRDTCTL0_IMPH_P10VC0_PMIN_DEF                    (0x00000000)
  #define MPRDRTRN_CR_CRDTCTL0_IMPH_P10VC0_PMIN_HSH                    (0x03037400)

  #define MPRDRTRN_CR_CRDTCTL0_IMPH_P11VC0_PMIN_OFF                    ( 6)
  #define MPRDRTRN_CR_CRDTCTL0_IMPH_P11VC0_PMIN_WID                    ( 3)
  #define MPRDRTRN_CR_CRDTCTL0_IMPH_P11VC0_PMIN_MSK                    (0x000001C0)
  #define MPRDRTRN_CR_CRDTCTL0_IMPH_P11VC0_PMIN_MIN                    (0)
  #define MPRDRTRN_CR_CRDTCTL0_IMPH_P11VC0_PMIN_MAX                    (7) // 0x00000007
  #define MPRDRTRN_CR_CRDTCTL0_IMPH_P11VC0_PMIN_DEF                    (0x00000000)
  #define MPRDRTRN_CR_CRDTCTL0_IMPH_P11VC0_PMIN_HSH                    (0x03067400)

  #define MPRDRTRN_CR_CRDTCTL0_IMPH_P12VC0_PMIN_OFF                    ( 9)
  #define MPRDRTRN_CR_CRDTCTL0_IMPH_P12VC0_PMIN_WID                    ( 3)
  #define MPRDRTRN_CR_CRDTCTL0_IMPH_P12VC0_PMIN_MSK                    (0x00000E00)
  #define MPRDRTRN_CR_CRDTCTL0_IMPH_P12VC0_PMIN_MIN                    (0)
  #define MPRDRTRN_CR_CRDTCTL0_IMPH_P12VC0_PMIN_MAX                    (7) // 0x00000007
  #define MPRDRTRN_CR_CRDTCTL0_IMPH_P12VC0_PMIN_DEF                    (0x00000000)
  #define MPRDRTRN_CR_CRDTCTL0_IMPH_P12VC0_PMIN_HSH                    (0x03097400)

  #define MPRDRTRN_CR_CRDTCTL0_IMPH_DEVC0_PMIN_OFF                     (12)
  #define MPRDRTRN_CR_CRDTCTL0_IMPH_DEVC0_PMIN_WID                     ( 3)
  #define MPRDRTRN_CR_CRDTCTL0_IMPH_DEVC0_PMIN_MSK                     (0x00007000)
  #define MPRDRTRN_CR_CRDTCTL0_IMPH_DEVC0_PMIN_MIN                     (0)
  #define MPRDRTRN_CR_CRDTCTL0_IMPH_DEVC0_PMIN_MAX                     (7) // 0x00000007
  #define MPRDRTRN_CR_CRDTCTL0_IMPH_DEVC0_PMIN_DEF                     (0x00000000)
  #define MPRDRTRN_CR_CRDTCTL0_IMPH_DEVC0_PMIN_HSH                     (0x030C7400)

  #define MPRDRTRN_CR_CRDTCTL0_IMPH_DMIVCP_PMIN_OFF                    (15)
  #define MPRDRTRN_CR_CRDTCTL0_IMPH_DMIVCP_PMIN_WID                    ( 3)
  #define MPRDRTRN_CR_CRDTCTL0_IMPH_DMIVCP_PMIN_MSK                    (0x00038000)
  #define MPRDRTRN_CR_CRDTCTL0_IMPH_DMIVCP_PMIN_MIN                    (0)
  #define MPRDRTRN_CR_CRDTCTL0_IMPH_DMIVCP_PMIN_MAX                    (7) // 0x00000007
  #define MPRDRTRN_CR_CRDTCTL0_IMPH_DMIVCP_PMIN_DEF                    (0x00000000)
  #define MPRDRTRN_CR_CRDTCTL0_IMPH_DMIVCP_PMIN_HSH                    (0x030F7400)

  #define MPRDRTRN_CR_CRDTCTL0_IMPH_DMIVCM_PMIN_OFF                    (18)
  #define MPRDRTRN_CR_CRDTCTL0_IMPH_DMIVCM_PMIN_WID                    ( 3)
  #define MPRDRTRN_CR_CRDTCTL0_IMPH_DMIVCM_PMIN_MSK                    (0x001C0000)
  #define MPRDRTRN_CR_CRDTCTL0_IMPH_DMIVCM_PMIN_MIN                    (0)
  #define MPRDRTRN_CR_CRDTCTL0_IMPH_DMIVCM_PMIN_MAX                    (7) // 0x00000007
  #define MPRDRTRN_CR_CRDTCTL0_IMPH_DMIVCM_PMIN_DEF                    (0x00000000)
  #define MPRDRTRN_CR_CRDTCTL0_IMPH_DMIVCM_PMIN_HSH                    (0x03127400)

  #define MPRDRTRN_CR_CRDTCTL0_IMPH_DMIVC1_PMIN_OFF                    (21)
  #define MPRDRTRN_CR_CRDTCTL0_IMPH_DMIVC1_PMIN_WID                    ( 3)
  #define MPRDRTRN_CR_CRDTCTL0_IMPH_DMIVC1_PMIN_MSK                    (0x00E00000)
  #define MPRDRTRN_CR_CRDTCTL0_IMPH_DMIVC1_PMIN_MIN                    (0)
  #define MPRDRTRN_CR_CRDTCTL0_IMPH_DMIVC1_PMIN_MAX                    (7) // 0x00000007
  #define MPRDRTRN_CR_CRDTCTL0_IMPH_DMIVC1_PMIN_DEF                    (0x00000000)
  #define MPRDRTRN_CR_CRDTCTL0_IMPH_DMIVC1_PMIN_HSH                    (0x03157400)

  #define MPRDRTRN_CR_CRDTCTL0_IMPH_CAMVC0_PMIN_OFF                    (24)
  #define MPRDRTRN_CR_CRDTCTL0_IMPH_CAMVC0_PMIN_WID                    ( 3)
  #define MPRDRTRN_CR_CRDTCTL0_IMPH_CAMVC0_PMIN_MSK                    (0x07000000)
  #define MPRDRTRN_CR_CRDTCTL0_IMPH_CAMVC0_PMIN_MIN                    (0)
  #define MPRDRTRN_CR_CRDTCTL0_IMPH_CAMVC0_PMIN_MAX                    (7) // 0x00000007
  #define MPRDRTRN_CR_CRDTCTL0_IMPH_CAMVC0_PMIN_DEF                    (0x00000000)
  #define MPRDRTRN_CR_CRDTCTL0_IMPH_CAMVC0_PMIN_HSH                    (0x03187400)

  #define MPRDRTRN_CR_CRDTCTL0_IMPH_GMMVC0_PMIN_OFF                    (27)
  #define MPRDRTRN_CR_CRDTCTL0_IMPH_GMMVC0_PMIN_WID                    ( 3)
  #define MPRDRTRN_CR_CRDTCTL0_IMPH_GMMVC0_PMIN_MSK                    (0x38000000)
  #define MPRDRTRN_CR_CRDTCTL0_IMPH_GMMVC0_PMIN_MIN                    (0)
  #define MPRDRTRN_CR_CRDTCTL0_IMPH_GMMVC0_PMIN_MAX                    (7) // 0x00000007
  #define MPRDRTRN_CR_CRDTCTL0_IMPH_GMMVC0_PMIN_DEF                    (0x00000000)
  #define MPRDRTRN_CR_CRDTCTL0_IMPH_GMMVC0_PMIN_HSH                    (0x031B7400)

#define MPRDRTRN_CR_CRDTCTL1_IMPH_REG                                  (0x00007404)

  #define MPRDRTRN_CR_CRDTCTL1_IMPH_DMIVC0_NPMIN_OFF                   ( 0)
  #define MPRDRTRN_CR_CRDTCTL1_IMPH_DMIVC0_NPMIN_WID                   ( 3)
  #define MPRDRTRN_CR_CRDTCTL1_IMPH_DMIVC0_NPMIN_MSK                   (0x00000007)
  #define MPRDRTRN_CR_CRDTCTL1_IMPH_DMIVC0_NPMIN_MIN                   (0)
  #define MPRDRTRN_CR_CRDTCTL1_IMPH_DMIVC0_NPMIN_MAX                   (7) // 0x00000007
  #define MPRDRTRN_CR_CRDTCTL1_IMPH_DMIVC0_NPMIN_DEF                   (0x00000000)
  #define MPRDRTRN_CR_CRDTCTL1_IMPH_DMIVC0_NPMIN_HSH                   (0x03007404)

  #define MPRDRTRN_CR_CRDTCTL1_IMPH_P10VC0_NPMIN_OFF                   ( 3)
  #define MPRDRTRN_CR_CRDTCTL1_IMPH_P10VC0_NPMIN_WID                   ( 3)
  #define MPRDRTRN_CR_CRDTCTL1_IMPH_P10VC0_NPMIN_MSK                   (0x00000038)
  #define MPRDRTRN_CR_CRDTCTL1_IMPH_P10VC0_NPMIN_MIN                   (0)
  #define MPRDRTRN_CR_CRDTCTL1_IMPH_P10VC0_NPMIN_MAX                   (7) // 0x00000007
  #define MPRDRTRN_CR_CRDTCTL1_IMPH_P10VC0_NPMIN_DEF                   (0x00000000)
  #define MPRDRTRN_CR_CRDTCTL1_IMPH_P10VC0_NPMIN_HSH                   (0x03037404)

  #define MPRDRTRN_CR_CRDTCTL1_IMPH_P11VC0_NPMIN_OFF                   ( 6)
  #define MPRDRTRN_CR_CRDTCTL1_IMPH_P11VC0_NPMIN_WID                   ( 3)
  #define MPRDRTRN_CR_CRDTCTL1_IMPH_P11VC0_NPMIN_MSK                   (0x000001C0)
  #define MPRDRTRN_CR_CRDTCTL1_IMPH_P11VC0_NPMIN_MIN                   (0)
  #define MPRDRTRN_CR_CRDTCTL1_IMPH_P11VC0_NPMIN_MAX                   (7) // 0x00000007
  #define MPRDRTRN_CR_CRDTCTL1_IMPH_P11VC0_NPMIN_DEF                   (0x00000000)
  #define MPRDRTRN_CR_CRDTCTL1_IMPH_P11VC0_NPMIN_HSH                   (0x03067404)

  #define MPRDRTRN_CR_CRDTCTL1_IMPH_P12VC0_NPMIN_OFF                   ( 9)
  #define MPRDRTRN_CR_CRDTCTL1_IMPH_P12VC0_NPMIN_WID                   ( 3)
  #define MPRDRTRN_CR_CRDTCTL1_IMPH_P12VC0_NPMIN_MSK                   (0x00000E00)
  #define MPRDRTRN_CR_CRDTCTL1_IMPH_P12VC0_NPMIN_MIN                   (0)
  #define MPRDRTRN_CR_CRDTCTL1_IMPH_P12VC0_NPMIN_MAX                   (7) // 0x00000007
  #define MPRDRTRN_CR_CRDTCTL1_IMPH_P12VC0_NPMIN_DEF                   (0x00000000)
  #define MPRDRTRN_CR_CRDTCTL1_IMPH_P12VC0_NPMIN_HSH                   (0x03097404)

  #define MPRDRTRN_CR_CRDTCTL1_IMPH_DEVC0_NPMIN_OFF                    (12)
  #define MPRDRTRN_CR_CRDTCTL1_IMPH_DEVC0_NPMIN_WID                    ( 3)
  #define MPRDRTRN_CR_CRDTCTL1_IMPH_DEVC0_NPMIN_MSK                    (0x00007000)
  #define MPRDRTRN_CR_CRDTCTL1_IMPH_DEVC0_NPMIN_MIN                    (0)
  #define MPRDRTRN_CR_CRDTCTL1_IMPH_DEVC0_NPMIN_MAX                    (7) // 0x00000007
  #define MPRDRTRN_CR_CRDTCTL1_IMPH_DEVC0_NPMIN_DEF                    (0x00000000)
  #define MPRDRTRN_CR_CRDTCTL1_IMPH_DEVC0_NPMIN_HSH                    (0x030C7404)

  #define MPRDRTRN_CR_CRDTCTL1_IMPH_DMIVCP_NPMIN_OFF                   (15)
  #define MPRDRTRN_CR_CRDTCTL1_IMPH_DMIVCP_NPMIN_WID                   ( 3)
  #define MPRDRTRN_CR_CRDTCTL1_IMPH_DMIVCP_NPMIN_MSK                   (0x00038000)
  #define MPRDRTRN_CR_CRDTCTL1_IMPH_DMIVCP_NPMIN_MIN                   (0)
  #define MPRDRTRN_CR_CRDTCTL1_IMPH_DMIVCP_NPMIN_MAX                   (7) // 0x00000007
  #define MPRDRTRN_CR_CRDTCTL1_IMPH_DMIVCP_NPMIN_DEF                   (0x00000000)
  #define MPRDRTRN_CR_CRDTCTL1_IMPH_DMIVCP_NPMIN_HSH                   (0x030F7404)

  #define MPRDRTRN_CR_CRDTCTL1_IMPH_DMIVCM_NPMIN_OFF                   (18)
  #define MPRDRTRN_CR_CRDTCTL1_IMPH_DMIVCM_NPMIN_WID                   ( 3)
  #define MPRDRTRN_CR_CRDTCTL1_IMPH_DMIVCM_NPMIN_MSK                   (0x001C0000)
  #define MPRDRTRN_CR_CRDTCTL1_IMPH_DMIVCM_NPMIN_MIN                   (0)
  #define MPRDRTRN_CR_CRDTCTL1_IMPH_DMIVCM_NPMIN_MAX                   (7) // 0x00000007
  #define MPRDRTRN_CR_CRDTCTL1_IMPH_DMIVCM_NPMIN_DEF                   (0x00000000)
  #define MPRDRTRN_CR_CRDTCTL1_IMPH_DMIVCM_NPMIN_HSH                   (0x03127404)

  #define MPRDRTRN_CR_CRDTCTL1_IMPH_DMIVC1_NPMIN_OFF                   (21)
  #define MPRDRTRN_CR_CRDTCTL1_IMPH_DMIVC1_NPMIN_WID                   ( 3)
  #define MPRDRTRN_CR_CRDTCTL1_IMPH_DMIVC1_NPMIN_MSK                   (0x00E00000)
  #define MPRDRTRN_CR_CRDTCTL1_IMPH_DMIVC1_NPMIN_MIN                   (0)
  #define MPRDRTRN_CR_CRDTCTL1_IMPH_DMIVC1_NPMIN_MAX                   (7) // 0x00000007
  #define MPRDRTRN_CR_CRDTCTL1_IMPH_DMIVC1_NPMIN_DEF                   (0x00000000)
  #define MPRDRTRN_CR_CRDTCTL1_IMPH_DMIVC1_NPMIN_HSH                   (0x03157404)

  #define MPRDRTRN_CR_CRDTCTL1_IMPH_CAMVC0_NPMIN_OFF                   (24)
  #define MPRDRTRN_CR_CRDTCTL1_IMPH_CAMVC0_NPMIN_WID                   ( 3)
  #define MPRDRTRN_CR_CRDTCTL1_IMPH_CAMVC0_NPMIN_MSK                   (0x07000000)
  #define MPRDRTRN_CR_CRDTCTL1_IMPH_CAMVC0_NPMIN_MIN                   (0)
  #define MPRDRTRN_CR_CRDTCTL1_IMPH_CAMVC0_NPMIN_MAX                   (7) // 0x00000007
  #define MPRDRTRN_CR_CRDTCTL1_IMPH_CAMVC0_NPMIN_DEF                   (0x00000000)
  #define MPRDRTRN_CR_CRDTCTL1_IMPH_CAMVC0_NPMIN_HSH                   (0x03187404)

  #define MPRDRTRN_CR_CRDTCTL1_IMPH_GMMVC0_NPMIN_OFF                   (27)
  #define MPRDRTRN_CR_CRDTCTL1_IMPH_GMMVC0_NPMIN_WID                   ( 3)
  #define MPRDRTRN_CR_CRDTCTL1_IMPH_GMMVC0_NPMIN_MSK                   (0x38000000)
  #define MPRDRTRN_CR_CRDTCTL1_IMPH_GMMVC0_NPMIN_MIN                   (0)
  #define MPRDRTRN_CR_CRDTCTL1_IMPH_GMMVC0_NPMIN_MAX                   (7) // 0x00000007
  #define MPRDRTRN_CR_CRDTCTL1_IMPH_GMMVC0_NPMIN_DEF                   (0x00000000)
  #define MPRDRTRN_CR_CRDTCTL1_IMPH_GMMVC0_NPMIN_HSH                   (0x031B7404)

#define MPRDRTRN_CR_CRDTCTL2_IMPH_REG                                  (0x00007408)

  #define MPRDRTRN_CR_CRDTCTL2_IMPH_DMIVC0_RRMIN_OFF                   ( 0)
  #define MPRDRTRN_CR_CRDTCTL2_IMPH_DMIVC0_RRMIN_WID                   ( 3)
  #define MPRDRTRN_CR_CRDTCTL2_IMPH_DMIVC0_RRMIN_MSK                   (0x00000007)
  #define MPRDRTRN_CR_CRDTCTL2_IMPH_DMIVC0_RRMIN_MIN                   (0)
  #define MPRDRTRN_CR_CRDTCTL2_IMPH_DMIVC0_RRMIN_MAX                   (7) // 0x00000007
  #define MPRDRTRN_CR_CRDTCTL2_IMPH_DMIVC0_RRMIN_DEF                   (0x00000000)
  #define MPRDRTRN_CR_CRDTCTL2_IMPH_DMIVC0_RRMIN_HSH                   (0x03007408)

  #define MPRDRTRN_CR_CRDTCTL2_IMPH_P10VC0_RRMIN_OFF                   ( 3)
  #define MPRDRTRN_CR_CRDTCTL2_IMPH_P10VC0_RRMIN_WID                   ( 3)
  #define MPRDRTRN_CR_CRDTCTL2_IMPH_P10VC0_RRMIN_MSK                   (0x00000038)
  #define MPRDRTRN_CR_CRDTCTL2_IMPH_P10VC0_RRMIN_MIN                   (0)
  #define MPRDRTRN_CR_CRDTCTL2_IMPH_P10VC0_RRMIN_MAX                   (7) // 0x00000007
  #define MPRDRTRN_CR_CRDTCTL2_IMPH_P10VC0_RRMIN_DEF                   (0x00000000)
  #define MPRDRTRN_CR_CRDTCTL2_IMPH_P10VC0_RRMIN_HSH                   (0x03037408)

  #define MPRDRTRN_CR_CRDTCTL2_IMPH_P11VC0_RRMIN_OFF                   ( 6)
  #define MPRDRTRN_CR_CRDTCTL2_IMPH_P11VC0_RRMIN_WID                   ( 3)
  #define MPRDRTRN_CR_CRDTCTL2_IMPH_P11VC0_RRMIN_MSK                   (0x000001C0)
  #define MPRDRTRN_CR_CRDTCTL2_IMPH_P11VC0_RRMIN_MIN                   (0)
  #define MPRDRTRN_CR_CRDTCTL2_IMPH_P11VC0_RRMIN_MAX                   (7) // 0x00000007
  #define MPRDRTRN_CR_CRDTCTL2_IMPH_P11VC0_RRMIN_DEF                   (0x00000000)
  #define MPRDRTRN_CR_CRDTCTL2_IMPH_P11VC0_RRMIN_HSH                   (0x03067408)

  #define MPRDRTRN_CR_CRDTCTL2_IMPH_P12VC0_RRMIN_OFF                   ( 9)
  #define MPRDRTRN_CR_CRDTCTL2_IMPH_P12VC0_RRMIN_WID                   ( 3)
  #define MPRDRTRN_CR_CRDTCTL2_IMPH_P12VC0_RRMIN_MSK                   (0x00000E00)
  #define MPRDRTRN_CR_CRDTCTL2_IMPH_P12VC0_RRMIN_MIN                   (0)
  #define MPRDRTRN_CR_CRDTCTL2_IMPH_P12VC0_RRMIN_MAX                   (7) // 0x00000007
  #define MPRDRTRN_CR_CRDTCTL2_IMPH_P12VC0_RRMIN_DEF                   (0x00000000)
  #define MPRDRTRN_CR_CRDTCTL2_IMPH_P12VC0_RRMIN_HSH                   (0x03097408)

  #define MPRDRTRN_CR_CRDTCTL2_IMPH_DEVC0_RRMIN_OFF                    (12)
  #define MPRDRTRN_CR_CRDTCTL2_IMPH_DEVC0_RRMIN_WID                    ( 3)
  #define MPRDRTRN_CR_CRDTCTL2_IMPH_DEVC0_RRMIN_MSK                    (0x00007000)
  #define MPRDRTRN_CR_CRDTCTL2_IMPH_DEVC0_RRMIN_MIN                    (0)
  #define MPRDRTRN_CR_CRDTCTL2_IMPH_DEVC0_RRMIN_MAX                    (7) // 0x00000007
  #define MPRDRTRN_CR_CRDTCTL2_IMPH_DEVC0_RRMIN_DEF                    (0x00000000)
  #define MPRDRTRN_CR_CRDTCTL2_IMPH_DEVC0_RRMIN_HSH                    (0x030C7408)

  #define MPRDRTRN_CR_CRDTCTL2_IMPH_DMIVCP_RRMIN_OFF                   (15)
  #define MPRDRTRN_CR_CRDTCTL2_IMPH_DMIVCP_RRMIN_WID                   ( 3)
  #define MPRDRTRN_CR_CRDTCTL2_IMPH_DMIVCP_RRMIN_MSK                   (0x00038000)
  #define MPRDRTRN_CR_CRDTCTL2_IMPH_DMIVCP_RRMIN_MIN                   (0)
  #define MPRDRTRN_CR_CRDTCTL2_IMPH_DMIVCP_RRMIN_MAX                   (7) // 0x00000007
  #define MPRDRTRN_CR_CRDTCTL2_IMPH_DMIVCP_RRMIN_DEF                   (0x00000000)
  #define MPRDRTRN_CR_CRDTCTL2_IMPH_DMIVCP_RRMIN_HSH                   (0x030F7408)

  #define MPRDRTRN_CR_CRDTCTL2_IMPH_DMIVCM_RRMIN_OFF                   (18)
  #define MPRDRTRN_CR_CRDTCTL2_IMPH_DMIVCM_RRMIN_WID                   ( 3)
  #define MPRDRTRN_CR_CRDTCTL2_IMPH_DMIVCM_RRMIN_MSK                   (0x001C0000)
  #define MPRDRTRN_CR_CRDTCTL2_IMPH_DMIVCM_RRMIN_MIN                   (0)
  #define MPRDRTRN_CR_CRDTCTL2_IMPH_DMIVCM_RRMIN_MAX                   (7) // 0x00000007
  #define MPRDRTRN_CR_CRDTCTL2_IMPH_DMIVCM_RRMIN_DEF                   (0x00000000)
  #define MPRDRTRN_CR_CRDTCTL2_IMPH_DMIVCM_RRMIN_HSH                   (0x03127408)

  #define MPRDRTRN_CR_CRDTCTL2_IMPH_DMIVC1_RRMIN_OFF                   (21)
  #define MPRDRTRN_CR_CRDTCTL2_IMPH_DMIVC1_RRMIN_WID                   ( 3)
  #define MPRDRTRN_CR_CRDTCTL2_IMPH_DMIVC1_RRMIN_MSK                   (0x00E00000)
  #define MPRDRTRN_CR_CRDTCTL2_IMPH_DMIVC1_RRMIN_MIN                   (0)
  #define MPRDRTRN_CR_CRDTCTL2_IMPH_DMIVC1_RRMIN_MAX                   (7) // 0x00000007
  #define MPRDRTRN_CR_CRDTCTL2_IMPH_DMIVC1_RRMIN_DEF                   (0x00000000)
  #define MPRDRTRN_CR_CRDTCTL2_IMPH_DMIVC1_RRMIN_HSH                   (0x03157408)

  #define MPRDRTRN_CR_CRDTCTL2_IMPH_DEVC1_RRMIN_OFF                    (24)
  #define MPRDRTRN_CR_CRDTCTL2_IMPH_DEVC1_RRMIN_WID                    ( 6)
  #define MPRDRTRN_CR_CRDTCTL2_IMPH_DEVC1_RRMIN_MSK                    (0x3F000000)
  #define MPRDRTRN_CR_CRDTCTL2_IMPH_DEVC1_RRMIN_MIN                    (0)
  #define MPRDRTRN_CR_CRDTCTL2_IMPH_DEVC1_RRMIN_MAX                    (63) // 0x0000003F
  #define MPRDRTRN_CR_CRDTCTL2_IMPH_DEVC1_RRMIN_DEF                    (0x00000000)
  #define MPRDRTRN_CR_CRDTCTL2_IMPH_DEVC1_RRMIN_HSH                    (0x06187408)

#define MPRDRTRN_CR_CRDTCTL3_IMPH_REG                                  (0x0000740C)

  #define MPRDRTRN_CR_CRDTCTL3_IMPH_CAMVC0_RRMIN_OFF                   ( 0)
  #define MPRDRTRN_CR_CRDTCTL3_IMPH_CAMVC0_RRMIN_WID                   ( 3)
  #define MPRDRTRN_CR_CRDTCTL3_IMPH_CAMVC0_RRMIN_MSK                   (0x00000007)
  #define MPRDRTRN_CR_CRDTCTL3_IMPH_CAMVC0_RRMIN_MIN                   (0)
  #define MPRDRTRN_CR_CRDTCTL3_IMPH_CAMVC0_RRMIN_MAX                   (7) // 0x00000007
  #define MPRDRTRN_CR_CRDTCTL3_IMPH_CAMVC0_RRMIN_DEF                   (0x00000000)
  #define MPRDRTRN_CR_CRDTCTL3_IMPH_CAMVC0_RRMIN_HSH                   (0x0300740C)

  #define MPRDRTRN_CR_CRDTCTL3_IMPH_GMMVC0_RRMIN_OFF                   ( 3)
  #define MPRDRTRN_CR_CRDTCTL3_IMPH_GMMVC0_RRMIN_WID                   ( 3)
  #define MPRDRTRN_CR_CRDTCTL3_IMPH_GMMVC0_RRMIN_MSK                   (0x00000038)
  #define MPRDRTRN_CR_CRDTCTL3_IMPH_GMMVC0_RRMIN_MIN                   (0)
  #define MPRDRTRN_CR_CRDTCTL3_IMPH_GMMVC0_RRMIN_MAX                   (7) // 0x00000007
  #define MPRDRTRN_CR_CRDTCTL3_IMPH_GMMVC0_RRMIN_DEF                   (0x00000000)
  #define MPRDRTRN_CR_CRDTCTL3_IMPH_GMMVC0_RRMIN_HSH                   (0x0303740C)

#define MPRDRTRN_CR_CRDTCTL4_IMPH_REG                                  (0x00007410)

  #define MPRDRTRN_CR_CRDTCTL4_IMPH_IOTRK_SHRD_OFF                     ( 0)
  #define MPRDRTRN_CR_CRDTCTL4_IMPH_IOTRK_SHRD_WID                     ( 6)
  #define MPRDRTRN_CR_CRDTCTL4_IMPH_IOTRK_SHRD_MSK                     (0x0000003F)
  #define MPRDRTRN_CR_CRDTCTL4_IMPH_IOTRK_SHRD_MIN                     (0)
  #define MPRDRTRN_CR_CRDTCTL4_IMPH_IOTRK_SHRD_MAX                     (63) // 0x0000003F
  #define MPRDRTRN_CR_CRDTCTL4_IMPH_IOTRK_SHRD_DEF                     (0x00000000)
  #define MPRDRTRN_CR_CRDTCTL4_IMPH_IOTRK_SHRD_HSH                     (0x06007410)

  #define MPRDRTRN_CR_CRDTCTL4_IMPH_RRTRK_SHRD_OFF                     ( 6)
  #define MPRDRTRN_CR_CRDTCTL4_IMPH_RRTRK_SHRD_WID                     ( 6)
  #define MPRDRTRN_CR_CRDTCTL4_IMPH_RRTRK_SHRD_MSK                     (0x00000FC0)
  #define MPRDRTRN_CR_CRDTCTL4_IMPH_RRTRK_SHRD_MIN                     (0)
  #define MPRDRTRN_CR_CRDTCTL4_IMPH_RRTRK_SHRD_MAX                     (63) // 0x0000003F
  #define MPRDRTRN_CR_CRDTCTL4_IMPH_RRTRK_SHRD_DEF                     (0x00000000)
  #define MPRDRTRN_CR_CRDTCTL4_IMPH_RRTRK_SHRD_HSH                     (0x06067410)

#define MPRDRTRN_CR_CRDTCTL5_IMPH_REG                                  (0x00007414)

  #define MPRDRTRN_CR_CRDTCTL5_IMPH_DMIVC0_PMAX_OFF                    ( 0)
  #define MPRDRTRN_CR_CRDTCTL5_IMPH_DMIVC0_PMAX_WID                    ( 5)
  #define MPRDRTRN_CR_CRDTCTL5_IMPH_DMIVC0_PMAX_MSK                    (0x0000001F)
  #define MPRDRTRN_CR_CRDTCTL5_IMPH_DMIVC0_PMAX_MIN                    (0)
  #define MPRDRTRN_CR_CRDTCTL5_IMPH_DMIVC0_PMAX_MAX                    (31) // 0x0000001F
  #define MPRDRTRN_CR_CRDTCTL5_IMPH_DMIVC0_PMAX_DEF                    (0x00000000)
  #define MPRDRTRN_CR_CRDTCTL5_IMPH_DMIVC0_PMAX_HSH                    (0x05007414)

  #define MPRDRTRN_CR_CRDTCTL5_IMPH_P10VC0_PMAX_OFF                    ( 5)
  #define MPRDRTRN_CR_CRDTCTL5_IMPH_P10VC0_PMAX_WID                    ( 5)
  #define MPRDRTRN_CR_CRDTCTL5_IMPH_P10VC0_PMAX_MSK                    (0x000003E0)
  #define MPRDRTRN_CR_CRDTCTL5_IMPH_P10VC0_PMAX_MIN                    (0)
  #define MPRDRTRN_CR_CRDTCTL5_IMPH_P10VC0_PMAX_MAX                    (31) // 0x0000001F
  #define MPRDRTRN_CR_CRDTCTL5_IMPH_P10VC0_PMAX_DEF                    (0x00000000)
  #define MPRDRTRN_CR_CRDTCTL5_IMPH_P10VC0_PMAX_HSH                    (0x05057414)

  #define MPRDRTRN_CR_CRDTCTL5_IMPH_P11VC0_PMAX_OFF                    (10)
  #define MPRDRTRN_CR_CRDTCTL5_IMPH_P11VC0_PMAX_WID                    ( 5)
  #define MPRDRTRN_CR_CRDTCTL5_IMPH_P11VC0_PMAX_MSK                    (0x00007C00)
  #define MPRDRTRN_CR_CRDTCTL5_IMPH_P11VC0_PMAX_MIN                    (0)
  #define MPRDRTRN_CR_CRDTCTL5_IMPH_P11VC0_PMAX_MAX                    (31) // 0x0000001F
  #define MPRDRTRN_CR_CRDTCTL5_IMPH_P11VC0_PMAX_DEF                    (0x00000000)
  #define MPRDRTRN_CR_CRDTCTL5_IMPH_P11VC0_PMAX_HSH                    (0x050A7414)

  #define MPRDRTRN_CR_CRDTCTL5_IMPH_P12VC0_PMAX_OFF                    (15)
  #define MPRDRTRN_CR_CRDTCTL5_IMPH_P12VC0_PMAX_WID                    ( 5)
  #define MPRDRTRN_CR_CRDTCTL5_IMPH_P12VC0_PMAX_MSK                    (0x000F8000)
  #define MPRDRTRN_CR_CRDTCTL5_IMPH_P12VC0_PMAX_MIN                    (0)
  #define MPRDRTRN_CR_CRDTCTL5_IMPH_P12VC0_PMAX_MAX                    (31) // 0x0000001F
  #define MPRDRTRN_CR_CRDTCTL5_IMPH_P12VC0_PMAX_DEF                    (0x00000000)
  #define MPRDRTRN_CR_CRDTCTL5_IMPH_P12VC0_PMAX_HSH                    (0x050F7414)

  #define MPRDRTRN_CR_CRDTCTL5_IMPH_DEVC0_PMAX_OFF                     (20)
  #define MPRDRTRN_CR_CRDTCTL5_IMPH_DEVC0_PMAX_WID                     ( 5)
  #define MPRDRTRN_CR_CRDTCTL5_IMPH_DEVC0_PMAX_MSK                     (0x01F00000)
  #define MPRDRTRN_CR_CRDTCTL5_IMPH_DEVC0_PMAX_MIN                     (0)
  #define MPRDRTRN_CR_CRDTCTL5_IMPH_DEVC0_PMAX_MAX                     (31) // 0x0000001F
  #define MPRDRTRN_CR_CRDTCTL5_IMPH_DEVC0_PMAX_DEF                     (0x00000000)
  #define MPRDRTRN_CR_CRDTCTL5_IMPH_DEVC0_PMAX_HSH                     (0x05147414)

#define MPRDRTRN_CR_CRDTCTL6_IMPH_REG                                  (0x00007418)

  #define MPRDRTRN_CR_CRDTCTL6_IMPH_DMIVCP_PMAX_OFF                    ( 0)
  #define MPRDRTRN_CR_CRDTCTL6_IMPH_DMIVCP_PMAX_WID                    ( 5)
  #define MPRDRTRN_CR_CRDTCTL6_IMPH_DMIVCP_PMAX_MSK                    (0x0000001F)
  #define MPRDRTRN_CR_CRDTCTL6_IMPH_DMIVCP_PMAX_MIN                    (0)
  #define MPRDRTRN_CR_CRDTCTL6_IMPH_DMIVCP_PMAX_MAX                    (31) // 0x0000001F
  #define MPRDRTRN_CR_CRDTCTL6_IMPH_DMIVCP_PMAX_DEF                    (0x00000000)
  #define MPRDRTRN_CR_CRDTCTL6_IMPH_DMIVCP_PMAX_HSH                    (0x05007418)

  #define MPRDRTRN_CR_CRDTCTL6_IMPH_DMIVCM_PMAX_OFF                    ( 5)
  #define MPRDRTRN_CR_CRDTCTL6_IMPH_DMIVCM_PMAX_WID                    ( 5)
  #define MPRDRTRN_CR_CRDTCTL6_IMPH_DMIVCM_PMAX_MSK                    (0x000003E0)
  #define MPRDRTRN_CR_CRDTCTL6_IMPH_DMIVCM_PMAX_MIN                    (0)
  #define MPRDRTRN_CR_CRDTCTL6_IMPH_DMIVCM_PMAX_MAX                    (31) // 0x0000001F
  #define MPRDRTRN_CR_CRDTCTL6_IMPH_DMIVCM_PMAX_DEF                    (0x00000000)
  #define MPRDRTRN_CR_CRDTCTL6_IMPH_DMIVCM_PMAX_HSH                    (0x05057418)

  #define MPRDRTRN_CR_CRDTCTL6_IMPH_DMIVC1_PMAX_OFF                    (10)
  #define MPRDRTRN_CR_CRDTCTL6_IMPH_DMIVC1_PMAX_WID                    ( 5)
  #define MPRDRTRN_CR_CRDTCTL6_IMPH_DMIVC1_PMAX_MSK                    (0x00007C00)
  #define MPRDRTRN_CR_CRDTCTL6_IMPH_DMIVC1_PMAX_MIN                    (0)
  #define MPRDRTRN_CR_CRDTCTL6_IMPH_DMIVC1_PMAX_MAX                    (31) // 0x0000001F
  #define MPRDRTRN_CR_CRDTCTL6_IMPH_DMIVC1_PMAX_DEF                    (0x00000000)
  #define MPRDRTRN_CR_CRDTCTL6_IMPH_DMIVC1_PMAX_HSH                    (0x050A7418)

  #define MPRDRTRN_CR_CRDTCTL6_IMPH_CAMVC0_PMAX_OFF                    (15)
  #define MPRDRTRN_CR_CRDTCTL6_IMPH_CAMVC0_PMAX_WID                    ( 5)
  #define MPRDRTRN_CR_CRDTCTL6_IMPH_CAMVC0_PMAX_MSK                    (0x000F8000)
  #define MPRDRTRN_CR_CRDTCTL6_IMPH_CAMVC0_PMAX_MIN                    (0)
  #define MPRDRTRN_CR_CRDTCTL6_IMPH_CAMVC0_PMAX_MAX                    (31) // 0x0000001F
  #define MPRDRTRN_CR_CRDTCTL6_IMPH_CAMVC0_PMAX_DEF                    (0x00000000)
  #define MPRDRTRN_CR_CRDTCTL6_IMPH_CAMVC0_PMAX_HSH                    (0x050F7418)

  #define MPRDRTRN_CR_CRDTCTL6_IMPH_GMMVC0_PMAX_OFF                    (20)
  #define MPRDRTRN_CR_CRDTCTL6_IMPH_GMMVC0_PMAX_WID                    ( 5)
  #define MPRDRTRN_CR_CRDTCTL6_IMPH_GMMVC0_PMAX_MSK                    (0x01F00000)
  #define MPRDRTRN_CR_CRDTCTL6_IMPH_GMMVC0_PMAX_MIN                    (0)
  #define MPRDRTRN_CR_CRDTCTL6_IMPH_GMMVC0_PMAX_MAX                    (31) // 0x0000001F
  #define MPRDRTRN_CR_CRDTCTL6_IMPH_GMMVC0_PMAX_DEF                    (0x00000000)
  #define MPRDRTRN_CR_CRDTCTL6_IMPH_GMMVC0_PMAX_HSH                    (0x05147418)

#define MPRDRTRN_CR_CRDTCTL7_IMPH_REG                                  (0x0000741C)

  #define MPRDRTRN_CR_CRDTCTL7_IMPH_DMIVC0_NPMAX_OFF                   ( 0)
  #define MPRDRTRN_CR_CRDTCTL7_IMPH_DMIVC0_NPMAX_WID                   ( 5)
  #define MPRDRTRN_CR_CRDTCTL7_IMPH_DMIVC0_NPMAX_MSK                   (0x0000001F)
  #define MPRDRTRN_CR_CRDTCTL7_IMPH_DMIVC0_NPMAX_MIN                   (0)
  #define MPRDRTRN_CR_CRDTCTL7_IMPH_DMIVC0_NPMAX_MAX                   (31) // 0x0000001F
  #define MPRDRTRN_CR_CRDTCTL7_IMPH_DMIVC0_NPMAX_DEF                   (0x00000000)
  #define MPRDRTRN_CR_CRDTCTL7_IMPH_DMIVC0_NPMAX_HSH                   (0x0500741C)

  #define MPRDRTRN_CR_CRDTCTL7_IMPH_P10VC0_NPMAX_OFF                   ( 5)
  #define MPRDRTRN_CR_CRDTCTL7_IMPH_P10VC0_NPMAX_WID                   ( 5)
  #define MPRDRTRN_CR_CRDTCTL7_IMPH_P10VC0_NPMAX_MSK                   (0x000003E0)
  #define MPRDRTRN_CR_CRDTCTL7_IMPH_P10VC0_NPMAX_MIN                   (0)
  #define MPRDRTRN_CR_CRDTCTL7_IMPH_P10VC0_NPMAX_MAX                   (31) // 0x0000001F
  #define MPRDRTRN_CR_CRDTCTL7_IMPH_P10VC0_NPMAX_DEF                   (0x00000000)
  #define MPRDRTRN_CR_CRDTCTL7_IMPH_P10VC0_NPMAX_HSH                   (0x0505741C)

  #define MPRDRTRN_CR_CRDTCTL7_IMPH_P11VC0_NPMAX_OFF                   (10)
  #define MPRDRTRN_CR_CRDTCTL7_IMPH_P11VC0_NPMAX_WID                   ( 5)
  #define MPRDRTRN_CR_CRDTCTL7_IMPH_P11VC0_NPMAX_MSK                   (0x00007C00)
  #define MPRDRTRN_CR_CRDTCTL7_IMPH_P11VC0_NPMAX_MIN                   (0)
  #define MPRDRTRN_CR_CRDTCTL7_IMPH_P11VC0_NPMAX_MAX                   (31) // 0x0000001F
  #define MPRDRTRN_CR_CRDTCTL7_IMPH_P11VC0_NPMAX_DEF                   (0x00000000)
  #define MPRDRTRN_CR_CRDTCTL7_IMPH_P11VC0_NPMAX_HSH                   (0x050A741C)

  #define MPRDRTRN_CR_CRDTCTL7_IMPH_P12VC0_NPMAX_OFF                   (15)
  #define MPRDRTRN_CR_CRDTCTL7_IMPH_P12VC0_NPMAX_WID                   ( 5)
  #define MPRDRTRN_CR_CRDTCTL7_IMPH_P12VC0_NPMAX_MSK                   (0x000F8000)
  #define MPRDRTRN_CR_CRDTCTL7_IMPH_P12VC0_NPMAX_MIN                   (0)
  #define MPRDRTRN_CR_CRDTCTL7_IMPH_P12VC0_NPMAX_MAX                   (31) // 0x0000001F
  #define MPRDRTRN_CR_CRDTCTL7_IMPH_P12VC0_NPMAX_DEF                   (0x00000000)
  #define MPRDRTRN_CR_CRDTCTL7_IMPH_P12VC0_NPMAX_HSH                   (0x050F741C)

  #define MPRDRTRN_CR_CRDTCTL7_IMPH_DEVC0_NPMAX_OFF                    (20)
  #define MPRDRTRN_CR_CRDTCTL7_IMPH_DEVC0_NPMAX_WID                    ( 5)
  #define MPRDRTRN_CR_CRDTCTL7_IMPH_DEVC0_NPMAX_MSK                    (0x01F00000)
  #define MPRDRTRN_CR_CRDTCTL7_IMPH_DEVC0_NPMAX_MIN                    (0)
  #define MPRDRTRN_CR_CRDTCTL7_IMPH_DEVC0_NPMAX_MAX                    (31) // 0x0000001F
  #define MPRDRTRN_CR_CRDTCTL7_IMPH_DEVC0_NPMAX_DEF                    (0x00000000)
  #define MPRDRTRN_CR_CRDTCTL7_IMPH_DEVC0_NPMAX_HSH                    (0x0514741C)

#define MPRDRTRN_CR_VISA_CTL_MPIORDTRKS_IMPH_REG                       (0x00007420)

  #define MPRDRTRN_CR_VISA_CTL_MPIORDTRKS_IMPH_EN_CLK_OFF              ( 0)
  #define MPRDRTRN_CR_VISA_CTL_MPIORDTRKS_IMPH_EN_CLK_WID              ( 1)
  #define MPRDRTRN_CR_VISA_CTL_MPIORDTRKS_IMPH_EN_CLK_MSK              (0x00000001)
  #define MPRDRTRN_CR_VISA_CTL_MPIORDTRKS_IMPH_EN_CLK_MIN              (0)
  #define MPRDRTRN_CR_VISA_CTL_MPIORDTRKS_IMPH_EN_CLK_MAX              (1) // 0x00000001
  #define MPRDRTRN_CR_VISA_CTL_MPIORDTRKS_IMPH_EN_CLK_DEF              (0x00000000)
  #define MPRDRTRN_CR_VISA_CTL_MPIORDTRKS_IMPH_EN_CLK_HSH              (0x01007420)

  #define MPRDRTRN_CR_VISA_CTL_MPIORDTRKS_IMPH_L0_DATA_BYTE_SEL_OFF    ( 1)
  #define MPRDRTRN_CR_VISA_CTL_MPIORDTRKS_IMPH_L0_DATA_BYTE_SEL_WID    ( 7)
  #define MPRDRTRN_CR_VISA_CTL_MPIORDTRKS_IMPH_L0_DATA_BYTE_SEL_MSK    (0x000000FE)
  #define MPRDRTRN_CR_VISA_CTL_MPIORDTRKS_IMPH_L0_DATA_BYTE_SEL_MIN    (0)
  #define MPRDRTRN_CR_VISA_CTL_MPIORDTRKS_IMPH_L0_DATA_BYTE_SEL_MAX    (127) // 0x0000007F
  #define MPRDRTRN_CR_VISA_CTL_MPIORDTRKS_IMPH_L0_DATA_BYTE_SEL_DEF    (0x00000000)
  #define MPRDRTRN_CR_VISA_CTL_MPIORDTRKS_IMPH_L0_DATA_BYTE_SEL_HSH    (0x07017420)

  #define MPRDRTRN_CR_VISA_CTL_MPIORDTRKS_IMPH_L0_BYP_SEL_OFF          ( 8)
  #define MPRDRTRN_CR_VISA_CTL_MPIORDTRKS_IMPH_L0_BYP_SEL_WID          ( 1)
  #define MPRDRTRN_CR_VISA_CTL_MPIORDTRKS_IMPH_L0_BYP_SEL_MSK          (0x00000100)
  #define MPRDRTRN_CR_VISA_CTL_MPIORDTRKS_IMPH_L0_BYP_SEL_MIN          (0)
  #define MPRDRTRN_CR_VISA_CTL_MPIORDTRKS_IMPH_L0_BYP_SEL_MAX          (1) // 0x00000001
  #define MPRDRTRN_CR_VISA_CTL_MPIORDTRKS_IMPH_L0_BYP_SEL_DEF          (0x00000000)
  #define MPRDRTRN_CR_VISA_CTL_MPIORDTRKS_IMPH_L0_BYP_SEL_HSH          (0x01087420)

  #define MPRDRTRN_CR_VISA_CTL_MPIORDTRKS_IMPH_L1_DATA_BYTE_SEL_OFF    ( 9)
  #define MPRDRTRN_CR_VISA_CTL_MPIORDTRKS_IMPH_L1_DATA_BYTE_SEL_WID    ( 7)
  #define MPRDRTRN_CR_VISA_CTL_MPIORDTRKS_IMPH_L1_DATA_BYTE_SEL_MSK    (0x0000FE00)
  #define MPRDRTRN_CR_VISA_CTL_MPIORDTRKS_IMPH_L1_DATA_BYTE_SEL_MIN    (0)
  #define MPRDRTRN_CR_VISA_CTL_MPIORDTRKS_IMPH_L1_DATA_BYTE_SEL_MAX    (127) // 0x0000007F
  #define MPRDRTRN_CR_VISA_CTL_MPIORDTRKS_IMPH_L1_DATA_BYTE_SEL_DEF    (0x00000000)
  #define MPRDRTRN_CR_VISA_CTL_MPIORDTRKS_IMPH_L1_DATA_BYTE_SEL_HSH    (0x07097420)

  #define MPRDRTRN_CR_VISA_CTL_MPIORDTRKS_IMPH_L1_BYP_SEL_OFF          (16)
  #define MPRDRTRN_CR_VISA_CTL_MPIORDTRKS_IMPH_L1_BYP_SEL_WID          ( 1)
  #define MPRDRTRN_CR_VISA_CTL_MPIORDTRKS_IMPH_L1_BYP_SEL_MSK          (0x00010000)
  #define MPRDRTRN_CR_VISA_CTL_MPIORDTRKS_IMPH_L1_BYP_SEL_MIN          (0)
  #define MPRDRTRN_CR_VISA_CTL_MPIORDTRKS_IMPH_L1_BYP_SEL_MAX          (1) // 0x00000001
  #define MPRDRTRN_CR_VISA_CTL_MPIORDTRKS_IMPH_L1_BYP_SEL_DEF          (0x00000000)
  #define MPRDRTRN_CR_VISA_CTL_MPIORDTRKS_IMPH_L1_BYP_SEL_HSH          (0x01107420)

  #define MPRDRTRN_CR_VISA_CTL_MPIORDTRKS_IMPH_VORANGE_OFF             (31)
  #define MPRDRTRN_CR_VISA_CTL_MPIORDTRKS_IMPH_VORANGE_WID             ( 1)
  #define MPRDRTRN_CR_VISA_CTL_MPIORDTRKS_IMPH_VORANGE_MSK             (0x80000000)
  #define MPRDRTRN_CR_VISA_CTL_MPIORDTRKS_IMPH_VORANGE_MIN             (0)
  #define MPRDRTRN_CR_VISA_CTL_MPIORDTRKS_IMPH_VORANGE_MAX             (1) // 0x00000001
  #define MPRDRTRN_CR_VISA_CTL_MPIORDTRKS_IMPH_VORANGE_DEF             (0x00000000)
  #define MPRDRTRN_CR_VISA_CTL_MPIORDTRKS_IMPH_VORANGE_HSH             (0x011F7420)

#define MPRDRTRN_CR_VISA_XBAR_MPIORDTRKS_IMPH_REG                      (0x00007424)

  #define MPRDRTRN_CR_VISA_XBAR_MPIORDTRKS_IMPH_FXB_Li_BIT0_DATA_BIT_SEL_OFF ( 0)
  #define MPRDRTRN_CR_VISA_XBAR_MPIORDTRKS_IMPH_FXB_Li_BIT0_DATA_BIT_SEL_WID ( 3)
  #define MPRDRTRN_CR_VISA_XBAR_MPIORDTRKS_IMPH_FXB_Li_BIT0_DATA_BIT_SEL_MSK (0x00000007)
  #define MPRDRTRN_CR_VISA_XBAR_MPIORDTRKS_IMPH_FXB_Li_BIT0_DATA_BIT_SEL_MIN (0)
  #define MPRDRTRN_CR_VISA_XBAR_MPIORDTRKS_IMPH_FXB_Li_BIT0_DATA_BIT_SEL_MAX (7) // 0x00000007
  #define MPRDRTRN_CR_VISA_XBAR_MPIORDTRKS_IMPH_FXB_Li_BIT0_DATA_BIT_SEL_DEF (0x00000000)
  #define MPRDRTRN_CR_VISA_XBAR_MPIORDTRKS_IMPH_FXB_Li_BIT0_DATA_BIT_SEL_HSH (0x03007424)

  #define MPRDRTRN_CR_VISA_XBAR_MPIORDTRKS_IMPH_FXB_Li_BIT0_DATA_BYTE_SEL_OFF ( 3)
  #define MPRDRTRN_CR_VISA_XBAR_MPIORDTRKS_IMPH_FXB_Li_BIT0_DATA_BYTE_SEL_WID ( 1)
  #define MPRDRTRN_CR_VISA_XBAR_MPIORDTRKS_IMPH_FXB_Li_BIT0_DATA_BYTE_SEL_MSK (0x00000008)
  #define MPRDRTRN_CR_VISA_XBAR_MPIORDTRKS_IMPH_FXB_Li_BIT0_DATA_BYTE_SEL_MIN (0)
  #define MPRDRTRN_CR_VISA_XBAR_MPIORDTRKS_IMPH_FXB_Li_BIT0_DATA_BYTE_SEL_MAX (1) // 0x00000001
  #define MPRDRTRN_CR_VISA_XBAR_MPIORDTRKS_IMPH_FXB_Li_BIT0_DATA_BYTE_SEL_DEF (0x00000000)
  #define MPRDRTRN_CR_VISA_XBAR_MPIORDTRKS_IMPH_FXB_Li_BIT0_DATA_BYTE_SEL_HSH (0x01037424)

  #define MPRDRTRN_CR_VISA_XBAR_MPIORDTRKS_IMPH_FXB_Li_BIT1_DATA_BIT_SEL_OFF ( 4)
  #define MPRDRTRN_CR_VISA_XBAR_MPIORDTRKS_IMPH_FXB_Li_BIT1_DATA_BIT_SEL_WID ( 3)
  #define MPRDRTRN_CR_VISA_XBAR_MPIORDTRKS_IMPH_FXB_Li_BIT1_DATA_BIT_SEL_MSK (0x00000070)
  #define MPRDRTRN_CR_VISA_XBAR_MPIORDTRKS_IMPH_FXB_Li_BIT1_DATA_BIT_SEL_MIN (0)
  #define MPRDRTRN_CR_VISA_XBAR_MPIORDTRKS_IMPH_FXB_Li_BIT1_DATA_BIT_SEL_MAX (7) // 0x00000007
  #define MPRDRTRN_CR_VISA_XBAR_MPIORDTRKS_IMPH_FXB_Li_BIT1_DATA_BIT_SEL_DEF (0x00000001)
  #define MPRDRTRN_CR_VISA_XBAR_MPIORDTRKS_IMPH_FXB_Li_BIT1_DATA_BIT_SEL_HSH (0x03047424)

  #define MPRDRTRN_CR_VISA_XBAR_MPIORDTRKS_IMPH_FXB_Li_BIT1_DATA_BYTE_SEL_OFF ( 7)
  #define MPRDRTRN_CR_VISA_XBAR_MPIORDTRKS_IMPH_FXB_Li_BIT1_DATA_BYTE_SEL_WID ( 1)
  #define MPRDRTRN_CR_VISA_XBAR_MPIORDTRKS_IMPH_FXB_Li_BIT1_DATA_BYTE_SEL_MSK (0x00000080)
  #define MPRDRTRN_CR_VISA_XBAR_MPIORDTRKS_IMPH_FXB_Li_BIT1_DATA_BYTE_SEL_MIN (0)
  #define MPRDRTRN_CR_VISA_XBAR_MPIORDTRKS_IMPH_FXB_Li_BIT1_DATA_BYTE_SEL_MAX (1) // 0x00000001
  #define MPRDRTRN_CR_VISA_XBAR_MPIORDTRKS_IMPH_FXB_Li_BIT1_DATA_BYTE_SEL_DEF (0x00000000)
  #define MPRDRTRN_CR_VISA_XBAR_MPIORDTRKS_IMPH_FXB_Li_BIT1_DATA_BYTE_SEL_HSH (0x01077424)

  #define MPRDRTRN_CR_VISA_XBAR_MPIORDTRKS_IMPH_FXB_Li_BIT2_DATA_BIT_SEL_OFF ( 8)
  #define MPRDRTRN_CR_VISA_XBAR_MPIORDTRKS_IMPH_FXB_Li_BIT2_DATA_BIT_SEL_WID ( 3)
  #define MPRDRTRN_CR_VISA_XBAR_MPIORDTRKS_IMPH_FXB_Li_BIT2_DATA_BIT_SEL_MSK (0x00000700)
  #define MPRDRTRN_CR_VISA_XBAR_MPIORDTRKS_IMPH_FXB_Li_BIT2_DATA_BIT_SEL_MIN (0)
  #define MPRDRTRN_CR_VISA_XBAR_MPIORDTRKS_IMPH_FXB_Li_BIT2_DATA_BIT_SEL_MAX (7) // 0x00000007
  #define MPRDRTRN_CR_VISA_XBAR_MPIORDTRKS_IMPH_FXB_Li_BIT2_DATA_BIT_SEL_DEF (0x00000002)
  #define MPRDRTRN_CR_VISA_XBAR_MPIORDTRKS_IMPH_FXB_Li_BIT2_DATA_BIT_SEL_HSH (0x03087424)

  #define MPRDRTRN_CR_VISA_XBAR_MPIORDTRKS_IMPH_FXB_Li_BIT2_DATA_BYTE_SEL_OFF (11)
  #define MPRDRTRN_CR_VISA_XBAR_MPIORDTRKS_IMPH_FXB_Li_BIT2_DATA_BYTE_SEL_WID ( 1)
  #define MPRDRTRN_CR_VISA_XBAR_MPIORDTRKS_IMPH_FXB_Li_BIT2_DATA_BYTE_SEL_MSK (0x00000800)
  #define MPRDRTRN_CR_VISA_XBAR_MPIORDTRKS_IMPH_FXB_Li_BIT2_DATA_BYTE_SEL_MIN (0)
  #define MPRDRTRN_CR_VISA_XBAR_MPIORDTRKS_IMPH_FXB_Li_BIT2_DATA_BYTE_SEL_MAX (1) // 0x00000001
  #define MPRDRTRN_CR_VISA_XBAR_MPIORDTRKS_IMPH_FXB_Li_BIT2_DATA_BYTE_SEL_DEF (0x00000000)
  #define MPRDRTRN_CR_VISA_XBAR_MPIORDTRKS_IMPH_FXB_Li_BIT2_DATA_BYTE_SEL_HSH (0x010B7424)

  #define MPRDRTRN_CR_VISA_XBAR_MPIORDTRKS_IMPH_FXB_Li_BIT3_DATA_BIT_SEL_OFF (12)
  #define MPRDRTRN_CR_VISA_XBAR_MPIORDTRKS_IMPH_FXB_Li_BIT3_DATA_BIT_SEL_WID ( 3)
  #define MPRDRTRN_CR_VISA_XBAR_MPIORDTRKS_IMPH_FXB_Li_BIT3_DATA_BIT_SEL_MSK (0x00007000)
  #define MPRDRTRN_CR_VISA_XBAR_MPIORDTRKS_IMPH_FXB_Li_BIT3_DATA_BIT_SEL_MIN (0)
  #define MPRDRTRN_CR_VISA_XBAR_MPIORDTRKS_IMPH_FXB_Li_BIT3_DATA_BIT_SEL_MAX (7) // 0x00000007
  #define MPRDRTRN_CR_VISA_XBAR_MPIORDTRKS_IMPH_FXB_Li_BIT3_DATA_BIT_SEL_DEF (0x00000003)
  #define MPRDRTRN_CR_VISA_XBAR_MPIORDTRKS_IMPH_FXB_Li_BIT3_DATA_BIT_SEL_HSH (0x030C7424)

  #define MPRDRTRN_CR_VISA_XBAR_MPIORDTRKS_IMPH_FXB_Li_BIT3_DATA_BYTE_SEL_OFF (15)
  #define MPRDRTRN_CR_VISA_XBAR_MPIORDTRKS_IMPH_FXB_Li_BIT3_DATA_BYTE_SEL_WID ( 1)
  #define MPRDRTRN_CR_VISA_XBAR_MPIORDTRKS_IMPH_FXB_Li_BIT3_DATA_BYTE_SEL_MSK (0x00008000)
  #define MPRDRTRN_CR_VISA_XBAR_MPIORDTRKS_IMPH_FXB_Li_BIT3_DATA_BYTE_SEL_MIN (0)
  #define MPRDRTRN_CR_VISA_XBAR_MPIORDTRKS_IMPH_FXB_Li_BIT3_DATA_BYTE_SEL_MAX (1) // 0x00000001
  #define MPRDRTRN_CR_VISA_XBAR_MPIORDTRKS_IMPH_FXB_Li_BIT3_DATA_BYTE_SEL_DEF (0x00000000)
  #define MPRDRTRN_CR_VISA_XBAR_MPIORDTRKS_IMPH_FXB_Li_BIT3_DATA_BYTE_SEL_HSH (0x010F7424)

  #define MPRDRTRN_CR_VISA_XBAR_MPIORDTRKS_IMPH_FXB_Li_BIT4_DATA_BIT_SEL_OFF (16)
  #define MPRDRTRN_CR_VISA_XBAR_MPIORDTRKS_IMPH_FXB_Li_BIT4_DATA_BIT_SEL_WID ( 3)
  #define MPRDRTRN_CR_VISA_XBAR_MPIORDTRKS_IMPH_FXB_Li_BIT4_DATA_BIT_SEL_MSK (0x00070000)
  #define MPRDRTRN_CR_VISA_XBAR_MPIORDTRKS_IMPH_FXB_Li_BIT4_DATA_BIT_SEL_MIN (0)
  #define MPRDRTRN_CR_VISA_XBAR_MPIORDTRKS_IMPH_FXB_Li_BIT4_DATA_BIT_SEL_MAX (7) // 0x00000007
  #define MPRDRTRN_CR_VISA_XBAR_MPIORDTRKS_IMPH_FXB_Li_BIT4_DATA_BIT_SEL_DEF (0x00000004)
  #define MPRDRTRN_CR_VISA_XBAR_MPIORDTRKS_IMPH_FXB_Li_BIT4_DATA_BIT_SEL_HSH (0x03107424)

  #define MPRDRTRN_CR_VISA_XBAR_MPIORDTRKS_IMPH_FXB_Li_BIT4_DATA_BYTE_SEL_OFF (19)
  #define MPRDRTRN_CR_VISA_XBAR_MPIORDTRKS_IMPH_FXB_Li_BIT4_DATA_BYTE_SEL_WID ( 1)
  #define MPRDRTRN_CR_VISA_XBAR_MPIORDTRKS_IMPH_FXB_Li_BIT4_DATA_BYTE_SEL_MSK (0x00080000)
  #define MPRDRTRN_CR_VISA_XBAR_MPIORDTRKS_IMPH_FXB_Li_BIT4_DATA_BYTE_SEL_MIN (0)
  #define MPRDRTRN_CR_VISA_XBAR_MPIORDTRKS_IMPH_FXB_Li_BIT4_DATA_BYTE_SEL_MAX (1) // 0x00000001
  #define MPRDRTRN_CR_VISA_XBAR_MPIORDTRKS_IMPH_FXB_Li_BIT4_DATA_BYTE_SEL_DEF (0x00000000)
  #define MPRDRTRN_CR_VISA_XBAR_MPIORDTRKS_IMPH_FXB_Li_BIT4_DATA_BYTE_SEL_HSH (0x01137424)

  #define MPRDRTRN_CR_VISA_XBAR_MPIORDTRKS_IMPH_FXB_Li_BIT5_DATA_BIT_SEL_OFF (20)
  #define MPRDRTRN_CR_VISA_XBAR_MPIORDTRKS_IMPH_FXB_Li_BIT5_DATA_BIT_SEL_WID ( 3)
  #define MPRDRTRN_CR_VISA_XBAR_MPIORDTRKS_IMPH_FXB_Li_BIT5_DATA_BIT_SEL_MSK (0x00700000)
  #define MPRDRTRN_CR_VISA_XBAR_MPIORDTRKS_IMPH_FXB_Li_BIT5_DATA_BIT_SEL_MIN (0)
  #define MPRDRTRN_CR_VISA_XBAR_MPIORDTRKS_IMPH_FXB_Li_BIT5_DATA_BIT_SEL_MAX (7) // 0x00000007
  #define MPRDRTRN_CR_VISA_XBAR_MPIORDTRKS_IMPH_FXB_Li_BIT5_DATA_BIT_SEL_DEF (0x00000005)
  #define MPRDRTRN_CR_VISA_XBAR_MPIORDTRKS_IMPH_FXB_Li_BIT5_DATA_BIT_SEL_HSH (0x03147424)

  #define MPRDRTRN_CR_VISA_XBAR_MPIORDTRKS_IMPH_FXB_Li_BIT5_DATA_BYTE_SEL_OFF (23)
  #define MPRDRTRN_CR_VISA_XBAR_MPIORDTRKS_IMPH_FXB_Li_BIT5_DATA_BYTE_SEL_WID ( 1)
  #define MPRDRTRN_CR_VISA_XBAR_MPIORDTRKS_IMPH_FXB_Li_BIT5_DATA_BYTE_SEL_MSK (0x00800000)
  #define MPRDRTRN_CR_VISA_XBAR_MPIORDTRKS_IMPH_FXB_Li_BIT5_DATA_BYTE_SEL_MIN (0)
  #define MPRDRTRN_CR_VISA_XBAR_MPIORDTRKS_IMPH_FXB_Li_BIT5_DATA_BYTE_SEL_MAX (1) // 0x00000001
  #define MPRDRTRN_CR_VISA_XBAR_MPIORDTRKS_IMPH_FXB_Li_BIT5_DATA_BYTE_SEL_DEF (0x00000000)
  #define MPRDRTRN_CR_VISA_XBAR_MPIORDTRKS_IMPH_FXB_Li_BIT5_DATA_BYTE_SEL_HSH (0x01177424)

  #define MPRDRTRN_CR_VISA_XBAR_MPIORDTRKS_IMPH_FXB_Li_BIT6_DATA_BIT_SEL_OFF (24)
  #define MPRDRTRN_CR_VISA_XBAR_MPIORDTRKS_IMPH_FXB_Li_BIT6_DATA_BIT_SEL_WID ( 3)
  #define MPRDRTRN_CR_VISA_XBAR_MPIORDTRKS_IMPH_FXB_Li_BIT6_DATA_BIT_SEL_MSK (0x07000000)
  #define MPRDRTRN_CR_VISA_XBAR_MPIORDTRKS_IMPH_FXB_Li_BIT6_DATA_BIT_SEL_MIN (0)
  #define MPRDRTRN_CR_VISA_XBAR_MPIORDTRKS_IMPH_FXB_Li_BIT6_DATA_BIT_SEL_MAX (7) // 0x00000007
  #define MPRDRTRN_CR_VISA_XBAR_MPIORDTRKS_IMPH_FXB_Li_BIT6_DATA_BIT_SEL_DEF (0x00000006)
  #define MPRDRTRN_CR_VISA_XBAR_MPIORDTRKS_IMPH_FXB_Li_BIT6_DATA_BIT_SEL_HSH (0x03187424)

  #define MPRDRTRN_CR_VISA_XBAR_MPIORDTRKS_IMPH_FXB_Li_BIT6_DATA_BYTE_SEL_OFF (27)
  #define MPRDRTRN_CR_VISA_XBAR_MPIORDTRKS_IMPH_FXB_Li_BIT6_DATA_BYTE_SEL_WID ( 1)
  #define MPRDRTRN_CR_VISA_XBAR_MPIORDTRKS_IMPH_FXB_Li_BIT6_DATA_BYTE_SEL_MSK (0x08000000)
  #define MPRDRTRN_CR_VISA_XBAR_MPIORDTRKS_IMPH_FXB_Li_BIT6_DATA_BYTE_SEL_MIN (0)
  #define MPRDRTRN_CR_VISA_XBAR_MPIORDTRKS_IMPH_FXB_Li_BIT6_DATA_BYTE_SEL_MAX (1) // 0x00000001
  #define MPRDRTRN_CR_VISA_XBAR_MPIORDTRKS_IMPH_FXB_Li_BIT6_DATA_BYTE_SEL_DEF (0x00000000)
  #define MPRDRTRN_CR_VISA_XBAR_MPIORDTRKS_IMPH_FXB_Li_BIT6_DATA_BYTE_SEL_HSH (0x011B7424)

  #define MPRDRTRN_CR_VISA_XBAR_MPIORDTRKS_IMPH_FXB_Li_BIT7_DATA_BIT_SEL_OFF (28)
  #define MPRDRTRN_CR_VISA_XBAR_MPIORDTRKS_IMPH_FXB_Li_BIT7_DATA_BIT_SEL_WID ( 3)
  #define MPRDRTRN_CR_VISA_XBAR_MPIORDTRKS_IMPH_FXB_Li_BIT7_DATA_BIT_SEL_MSK (0x70000000)
  #define MPRDRTRN_CR_VISA_XBAR_MPIORDTRKS_IMPH_FXB_Li_BIT7_DATA_BIT_SEL_MIN (0)
  #define MPRDRTRN_CR_VISA_XBAR_MPIORDTRKS_IMPH_FXB_Li_BIT7_DATA_BIT_SEL_MAX (7) // 0x00000007
  #define MPRDRTRN_CR_VISA_XBAR_MPIORDTRKS_IMPH_FXB_Li_BIT7_DATA_BIT_SEL_DEF (0x00000007)
  #define MPRDRTRN_CR_VISA_XBAR_MPIORDTRKS_IMPH_FXB_Li_BIT7_DATA_BIT_SEL_HSH (0x031C7424)

  #define MPRDRTRN_CR_VISA_XBAR_MPIORDTRKS_IMPH_FXB_Li_BIT7_DATA_BYTE_SEL_OFF (31)
  #define MPRDRTRN_CR_VISA_XBAR_MPIORDTRKS_IMPH_FXB_Li_BIT7_DATA_BYTE_SEL_WID ( 1)
  #define MPRDRTRN_CR_VISA_XBAR_MPIORDTRKS_IMPH_FXB_Li_BIT7_DATA_BYTE_SEL_MSK (0x80000000)
  #define MPRDRTRN_CR_VISA_XBAR_MPIORDTRKS_IMPH_FXB_Li_BIT7_DATA_BYTE_SEL_MIN (0)
  #define MPRDRTRN_CR_VISA_XBAR_MPIORDTRKS_IMPH_FXB_Li_BIT7_DATA_BYTE_SEL_MAX (1) // 0x00000001
  #define MPRDRTRN_CR_VISA_XBAR_MPIORDTRKS_IMPH_FXB_Li_BIT7_DATA_BYTE_SEL_DEF (0x00000000)
  #define MPRDRTRN_CR_VISA_XBAR_MPIORDTRKS_IMPH_FXB_Li_BIT7_DATA_BYTE_SEL_HSH (0x011F7424)

#define MPRDRTRN_CR_VISA_CTL_MPIOTRKS_IMPH_REG                         (0x00007428)

  #define MPRDRTRN_CR_VISA_CTL_MPIOTRKS_IMPH_EN_CLK_OFF                ( 0)
  #define MPRDRTRN_CR_VISA_CTL_MPIOTRKS_IMPH_EN_CLK_WID                ( 1)
  #define MPRDRTRN_CR_VISA_CTL_MPIOTRKS_IMPH_EN_CLK_MSK                (0x00000001)
  #define MPRDRTRN_CR_VISA_CTL_MPIOTRKS_IMPH_EN_CLK_MIN                (0)
  #define MPRDRTRN_CR_VISA_CTL_MPIOTRKS_IMPH_EN_CLK_MAX                (1) // 0x00000001
  #define MPRDRTRN_CR_VISA_CTL_MPIOTRKS_IMPH_EN_CLK_DEF                (0x00000000)
  #define MPRDRTRN_CR_VISA_CTL_MPIOTRKS_IMPH_EN_CLK_HSH                (0x01007428)

  #define MPRDRTRN_CR_VISA_CTL_MPIOTRKS_IMPH_L0_DATA_BYTE_SEL_OFF      ( 1)
  #define MPRDRTRN_CR_VISA_CTL_MPIOTRKS_IMPH_L0_DATA_BYTE_SEL_WID      ( 7)
  #define MPRDRTRN_CR_VISA_CTL_MPIOTRKS_IMPH_L0_DATA_BYTE_SEL_MSK      (0x000000FE)
  #define MPRDRTRN_CR_VISA_CTL_MPIOTRKS_IMPH_L0_DATA_BYTE_SEL_MIN      (0)
  #define MPRDRTRN_CR_VISA_CTL_MPIOTRKS_IMPH_L0_DATA_BYTE_SEL_MAX      (127) // 0x0000007F
  #define MPRDRTRN_CR_VISA_CTL_MPIOTRKS_IMPH_L0_DATA_BYTE_SEL_DEF      (0x00000000)
  #define MPRDRTRN_CR_VISA_CTL_MPIOTRKS_IMPH_L0_DATA_BYTE_SEL_HSH      (0x07017428)

  #define MPRDRTRN_CR_VISA_CTL_MPIOTRKS_IMPH_L0_BYP_SEL_OFF            ( 8)
  #define MPRDRTRN_CR_VISA_CTL_MPIOTRKS_IMPH_L0_BYP_SEL_WID            ( 1)
  #define MPRDRTRN_CR_VISA_CTL_MPIOTRKS_IMPH_L0_BYP_SEL_MSK            (0x00000100)
  #define MPRDRTRN_CR_VISA_CTL_MPIOTRKS_IMPH_L0_BYP_SEL_MIN            (0)
  #define MPRDRTRN_CR_VISA_CTL_MPIOTRKS_IMPH_L0_BYP_SEL_MAX            (1) // 0x00000001
  #define MPRDRTRN_CR_VISA_CTL_MPIOTRKS_IMPH_L0_BYP_SEL_DEF            (0x00000000)
  #define MPRDRTRN_CR_VISA_CTL_MPIOTRKS_IMPH_L0_BYP_SEL_HSH            (0x01087428)

  #define MPRDRTRN_CR_VISA_CTL_MPIOTRKS_IMPH_L1_DATA_BYTE_SEL_OFF      ( 9)
  #define MPRDRTRN_CR_VISA_CTL_MPIOTRKS_IMPH_L1_DATA_BYTE_SEL_WID      ( 7)
  #define MPRDRTRN_CR_VISA_CTL_MPIOTRKS_IMPH_L1_DATA_BYTE_SEL_MSK      (0x0000FE00)
  #define MPRDRTRN_CR_VISA_CTL_MPIOTRKS_IMPH_L1_DATA_BYTE_SEL_MIN      (0)
  #define MPRDRTRN_CR_VISA_CTL_MPIOTRKS_IMPH_L1_DATA_BYTE_SEL_MAX      (127) // 0x0000007F
  #define MPRDRTRN_CR_VISA_CTL_MPIOTRKS_IMPH_L1_DATA_BYTE_SEL_DEF      (0x00000000)
  #define MPRDRTRN_CR_VISA_CTL_MPIOTRKS_IMPH_L1_DATA_BYTE_SEL_HSH      (0x07097428)

  #define MPRDRTRN_CR_VISA_CTL_MPIOTRKS_IMPH_L1_BYP_SEL_OFF            (16)
  #define MPRDRTRN_CR_VISA_CTL_MPIOTRKS_IMPH_L1_BYP_SEL_WID            ( 1)
  #define MPRDRTRN_CR_VISA_CTL_MPIOTRKS_IMPH_L1_BYP_SEL_MSK            (0x00010000)
  #define MPRDRTRN_CR_VISA_CTL_MPIOTRKS_IMPH_L1_BYP_SEL_MIN            (0)
  #define MPRDRTRN_CR_VISA_CTL_MPIOTRKS_IMPH_L1_BYP_SEL_MAX            (1) // 0x00000001
  #define MPRDRTRN_CR_VISA_CTL_MPIOTRKS_IMPH_L1_BYP_SEL_DEF            (0x00000000)
  #define MPRDRTRN_CR_VISA_CTL_MPIOTRKS_IMPH_L1_BYP_SEL_HSH            (0x01107428)

  #define MPRDRTRN_CR_VISA_CTL_MPIOTRKS_IMPH_PATGENMODE_OFF            (27)
  #define MPRDRTRN_CR_VISA_CTL_MPIOTRKS_IMPH_PATGENMODE_WID            ( 3)
  #define MPRDRTRN_CR_VISA_CTL_MPIOTRKS_IMPH_PATGENMODE_MSK            (0x38000000)
  #define MPRDRTRN_CR_VISA_CTL_MPIOTRKS_IMPH_PATGENMODE_MIN            (0)
  #define MPRDRTRN_CR_VISA_CTL_MPIOTRKS_IMPH_PATGENMODE_MAX            (7) // 0x00000007
  #define MPRDRTRN_CR_VISA_CTL_MPIOTRKS_IMPH_PATGENMODE_DEF            (0x00000000)
  #define MPRDRTRN_CR_VISA_CTL_MPIOTRKS_IMPH_PATGENMODE_HSH            (0x031B7428)

  #define MPRDRTRN_CR_VISA_CTL_MPIOTRKS_IMPH_VORANGE_OFF               (31)
  #define MPRDRTRN_CR_VISA_CTL_MPIOTRKS_IMPH_VORANGE_WID               ( 1)
  #define MPRDRTRN_CR_VISA_CTL_MPIOTRKS_IMPH_VORANGE_MSK               (0x80000000)
  #define MPRDRTRN_CR_VISA_CTL_MPIOTRKS_IMPH_VORANGE_MIN               (0)
  #define MPRDRTRN_CR_VISA_CTL_MPIOTRKS_IMPH_VORANGE_MAX               (1) // 0x00000001
  #define MPRDRTRN_CR_VISA_CTL_MPIOTRKS_IMPH_VORANGE_DEF               (0x00000000)
  #define MPRDRTRN_CR_VISA_CTL_MPIOTRKS_IMPH_VORANGE_HSH               (0x011F7428)

#define MPRDRTRN_CR_ERR_LOG1_IMPH_REG                                  (0x0000742C)

  #define MPRDRTRN_CR_ERR_LOG1_IMPH_ILLCFGDROP_OFF                     ( 0)
  #define MPRDRTRN_CR_ERR_LOG1_IMPH_ILLCFGDROP_WID                     ( 1)
  #define MPRDRTRN_CR_ERR_LOG1_IMPH_ILLCFGDROP_MSK                     (0x00000001)
  #define MPRDRTRN_CR_ERR_LOG1_IMPH_ILLCFGDROP_MIN                     (0)
  #define MPRDRTRN_CR_ERR_LOG1_IMPH_ILLCFGDROP_MAX                     (1) // 0x00000001
  #define MPRDRTRN_CR_ERR_LOG1_IMPH_ILLCFGDROP_DEF                     (0x00000000)
  #define MPRDRTRN_CR_ERR_LOG1_IMPH_ILLCFGDROP_HSH                     (0x0100742C)

  #define MPRDRTRN_CR_ERR_LOG1_IMPH_UNSUCFULLCKRDDROP_OFF              ( 1)
  #define MPRDRTRN_CR_ERR_LOG1_IMPH_UNSUCFULLCKRDDROP_WID              ( 1)
  #define MPRDRTRN_CR_ERR_LOG1_IMPH_UNSUCFULLCKRDDROP_MSK              (0x00000002)
  #define MPRDRTRN_CR_ERR_LOG1_IMPH_UNSUCFULLCKRDDROP_MIN              (0)
  #define MPRDRTRN_CR_ERR_LOG1_IMPH_UNSUCFULLCKRDDROP_MAX              (1) // 0x00000001
  #define MPRDRTRN_CR_ERR_LOG1_IMPH_UNSUCFULLCKRDDROP_DEF              (0x00000000)
  #define MPRDRTRN_CR_ERR_LOG1_IMPH_UNSUCFULLCKRDDROP_HSH              (0x0101742C)

#define MPRDRTRN_CR_PRIMDN_MASK1_IMPH_REG                              (0x00007430)

  #define MPRDRTRN_CR_PRIMDN_MASK1_IMPH_VC_OFF                         ( 0)
  #define MPRDRTRN_CR_PRIMDN_MASK1_IMPH_VC_WID                         ( 4)
  #define MPRDRTRN_CR_PRIMDN_MASK1_IMPH_VC_MSK                         (0x0000000F)
  #define MPRDRTRN_CR_PRIMDN_MASK1_IMPH_VC_MIN                         (0)
  #define MPRDRTRN_CR_PRIMDN_MASK1_IMPH_VC_MAX                         (15) // 0x0000000F
  #define MPRDRTRN_CR_PRIMDN_MASK1_IMPH_VC_DEF                         (0x00000000)
  #define MPRDRTRN_CR_PRIMDN_MASK1_IMPH_VC_HSH                         (0x04007430)

  #define MPRDRTRN_CR_PRIMDN_MASK1_IMPH_FMT_CMDTYPE_OFF                ( 4)
  #define MPRDRTRN_CR_PRIMDN_MASK1_IMPH_FMT_CMDTYPE_WID                ( 6)
  #define MPRDRTRN_CR_PRIMDN_MASK1_IMPH_FMT_CMDTYPE_MSK                (0x000003F0)
  #define MPRDRTRN_CR_PRIMDN_MASK1_IMPH_FMT_CMDTYPE_MIN                (0)
  #define MPRDRTRN_CR_PRIMDN_MASK1_IMPH_FMT_CMDTYPE_MAX                (63) // 0x0000003F
  #define MPRDRTRN_CR_PRIMDN_MASK1_IMPH_FMT_CMDTYPE_DEF                (0x00000000)
  #define MPRDRTRN_CR_PRIMDN_MASK1_IMPH_FMT_CMDTYPE_HSH                (0x06047430)

  #define MPRDRTRN_CR_PRIMDN_MASK1_IMPH_TC_OFF                         (10)
  #define MPRDRTRN_CR_PRIMDN_MASK1_IMPH_TC_WID                         ( 4)
  #define MPRDRTRN_CR_PRIMDN_MASK1_IMPH_TC_MSK                         (0x00003C00)
  #define MPRDRTRN_CR_PRIMDN_MASK1_IMPH_TC_MIN                         (0)
  #define MPRDRTRN_CR_PRIMDN_MASK1_IMPH_TC_MAX                         (15) // 0x0000000F
  #define MPRDRTRN_CR_PRIMDN_MASK1_IMPH_TC_DEF                         (0x00000000)
  #define MPRDRTRN_CR_PRIMDN_MASK1_IMPH_TC_HSH                         (0x040A7430)

  #define MPRDRTRN_CR_PRIMDN_MASK1_IMPH_NS_OFF                         (14)
  #define MPRDRTRN_CR_PRIMDN_MASK1_IMPH_NS_WID                         ( 1)
  #define MPRDRTRN_CR_PRIMDN_MASK1_IMPH_NS_MSK                         (0x00004000)
  #define MPRDRTRN_CR_PRIMDN_MASK1_IMPH_NS_MIN                         (0)
  #define MPRDRTRN_CR_PRIMDN_MASK1_IMPH_NS_MAX                         (1) // 0x00000001
  #define MPRDRTRN_CR_PRIMDN_MASK1_IMPH_NS_DEF                         (0x00000000)
  #define MPRDRTRN_CR_PRIMDN_MASK1_IMPH_NS_HSH                         (0x010E7430)

  #define MPRDRTRN_CR_PRIMDN_MASK1_IMPH_RO_OFF                         (15)
  #define MPRDRTRN_CR_PRIMDN_MASK1_IMPH_RO_WID                         ( 1)
  #define MPRDRTRN_CR_PRIMDN_MASK1_IMPH_RO_MSK                         (0x00008000)
  #define MPRDRTRN_CR_PRIMDN_MASK1_IMPH_RO_MIN                         (0)
  #define MPRDRTRN_CR_PRIMDN_MASK1_IMPH_RO_MAX                         (1) // 0x00000001
  #define MPRDRTRN_CR_PRIMDN_MASK1_IMPH_RO_DEF                         (0x00000000)
  #define MPRDRTRN_CR_PRIMDN_MASK1_IMPH_RO_HSH                         (0x010F7430)

  #define MPRDRTRN_CR_PRIMDN_MASK1_IMPH_LENGTH_OFF                     (16)
  #define MPRDRTRN_CR_PRIMDN_MASK1_IMPH_LENGTH_WID                     ( 5)
  #define MPRDRTRN_CR_PRIMDN_MASK1_IMPH_LENGTH_MSK                     (0x001F0000)
  #define MPRDRTRN_CR_PRIMDN_MASK1_IMPH_LENGTH_MIN                     (0)
  #define MPRDRTRN_CR_PRIMDN_MASK1_IMPH_LENGTH_MAX                     (31) // 0x0000001F
  #define MPRDRTRN_CR_PRIMDN_MASK1_IMPH_LENGTH_DEF                     (0x00000000)
  #define MPRDRTRN_CR_PRIMDN_MASK1_IMPH_LENGTH_HSH                     (0x05107430)

  #define MPRDRTRN_CR_PRIMDN_MASK1_IMPH_EP_OFF                         (21)
  #define MPRDRTRN_CR_PRIMDN_MASK1_IMPH_EP_WID                         ( 1)
  #define MPRDRTRN_CR_PRIMDN_MASK1_IMPH_EP_MSK                         (0x00200000)
  #define MPRDRTRN_CR_PRIMDN_MASK1_IMPH_EP_MIN                         (0)
  #define MPRDRTRN_CR_PRIMDN_MASK1_IMPH_EP_MAX                         (1) // 0x00000001
  #define MPRDRTRN_CR_PRIMDN_MASK1_IMPH_EP_DEF                         (0x00000000)
  #define MPRDRTRN_CR_PRIMDN_MASK1_IMPH_EP_HSH                         (0x01157430)

#define MPRDRTRN_CR_PRIMDN_MASK2_IMPH_REG                              (0x00007434)

  #define MPRDRTRN_CR_PRIMDN_MASK2_IMPH_RQID_OFF                       ( 0)
  #define MPRDRTRN_CR_PRIMDN_MASK2_IMPH_RQID_WID                       (16)
  #define MPRDRTRN_CR_PRIMDN_MASK2_IMPH_RQID_MSK                       (0x0000FFFF)
  #define MPRDRTRN_CR_PRIMDN_MASK2_IMPH_RQID_MIN                       (0)
  #define MPRDRTRN_CR_PRIMDN_MASK2_IMPH_RQID_MAX                       (65535) // 0x0000FFFF
  #define MPRDRTRN_CR_PRIMDN_MASK2_IMPH_RQID_DEF                       (0x00000000)
  #define MPRDRTRN_CR_PRIMDN_MASK2_IMPH_RQID_HSH                       (0x10007434)

  #define MPRDRTRN_CR_PRIMDN_MASK2_IMPH_TAG_OFF                        (16)
  #define MPRDRTRN_CR_PRIMDN_MASK2_IMPH_TAG_WID                        ( 8)
  #define MPRDRTRN_CR_PRIMDN_MASK2_IMPH_TAG_MSK                        (0x00FF0000)
  #define MPRDRTRN_CR_PRIMDN_MASK2_IMPH_TAG_MIN                        (0)
  #define MPRDRTRN_CR_PRIMDN_MASK2_IMPH_TAG_MAX                        (255) // 0x000000FF
  #define MPRDRTRN_CR_PRIMDN_MASK2_IMPH_TAG_DEF                        (0x00000000)
  #define MPRDRTRN_CR_PRIMDN_MASK2_IMPH_TAG_HSH                        (0x08107434)

  #define MPRDRTRN_CR_PRIMDN_MASK2_IMPH_LBEFBE_MSGTYPE_OFF             (24)
  #define MPRDRTRN_CR_PRIMDN_MASK2_IMPH_LBEFBE_MSGTYPE_WID             ( 8)
  #define MPRDRTRN_CR_PRIMDN_MASK2_IMPH_LBEFBE_MSGTYPE_MSK             (0xFF000000)
  #define MPRDRTRN_CR_PRIMDN_MASK2_IMPH_LBEFBE_MSGTYPE_MIN             (0)
  #define MPRDRTRN_CR_PRIMDN_MASK2_IMPH_LBEFBE_MSGTYPE_MAX             (255) // 0x000000FF
  #define MPRDRTRN_CR_PRIMDN_MASK2_IMPH_LBEFBE_MSGTYPE_DEF             (0x00000000)
  #define MPRDRTRN_CR_PRIMDN_MASK2_IMPH_LBEFBE_MSGTYPE_HSH             (0x08187434)

#define MPRDRTRN_CR_PRIMDN_MASK3_IMPH_REG                              (0x00007438)

  #define MPRDRTRN_CR_PRIMDN_MASK3_IMPH_ADDR_31_0_OFF                  ( 0)
  #define MPRDRTRN_CR_PRIMDN_MASK3_IMPH_ADDR_31_0_WID                  (32)
  #define MPRDRTRN_CR_PRIMDN_MASK3_IMPH_ADDR_31_0_MSK                  (0xFFFFFFFF)
  #define MPRDRTRN_CR_PRIMDN_MASK3_IMPH_ADDR_31_0_MIN                  (0)
  #define MPRDRTRN_CR_PRIMDN_MASK3_IMPH_ADDR_31_0_MAX                  (4294967295) // 0xFFFFFFFF
  #define MPRDRTRN_CR_PRIMDN_MASK3_IMPH_ADDR_31_0_DEF                  (0x00000000)
  #define MPRDRTRN_CR_PRIMDN_MASK3_IMPH_ADDR_31_0_HSH                  (0x20007438)

#define MPRDRTRN_CR_PRIMDN_MASK4_IMPH_REG                              (0x0000743C)

  #define MPRDRTRN_CR_PRIMDN_MASK4_IMPH_ADDR_63_32_OFF                 ( 0)
  #define MPRDRTRN_CR_PRIMDN_MASK4_IMPH_ADDR_63_32_WID                 (32)
  #define MPRDRTRN_CR_PRIMDN_MASK4_IMPH_ADDR_63_32_MSK                 (0xFFFFFFFF)
  #define MPRDRTRN_CR_PRIMDN_MASK4_IMPH_ADDR_63_32_MIN                 (0)
  #define MPRDRTRN_CR_PRIMDN_MASK4_IMPH_ADDR_63_32_MAX                 (4294967295) // 0xFFFFFFFF
  #define MPRDRTRN_CR_PRIMDN_MASK4_IMPH_ADDR_63_32_DEF                 (0x00000000)
  #define MPRDRTRN_CR_PRIMDN_MASK4_IMPH_ADDR_63_32_HSH                 (0x2000743C)

#define MPRDRTRN_CR_PRIMDN_COMP1_IMPH_REG                              (0x00007440)

  #define MPRDRTRN_CR_PRIMDN_COMP1_IMPH_VC_OFF                         ( 0)
  #define MPRDRTRN_CR_PRIMDN_COMP1_IMPH_VC_WID                         ( 4)
  #define MPRDRTRN_CR_PRIMDN_COMP1_IMPH_VC_MSK                         (0x0000000F)
  #define MPRDRTRN_CR_PRIMDN_COMP1_IMPH_VC_MIN                         (0)
  #define MPRDRTRN_CR_PRIMDN_COMP1_IMPH_VC_MAX                         (15) // 0x0000000F
  #define MPRDRTRN_CR_PRIMDN_COMP1_IMPH_VC_DEF                         (0x00000000)
  #define MPRDRTRN_CR_PRIMDN_COMP1_IMPH_VC_HSH                         (0x04007440)

  #define MPRDRTRN_CR_PRIMDN_COMP1_IMPH_FMT_CMDTYPE_OFF                ( 4)
  #define MPRDRTRN_CR_PRIMDN_COMP1_IMPH_FMT_CMDTYPE_WID                ( 6)
  #define MPRDRTRN_CR_PRIMDN_COMP1_IMPH_FMT_CMDTYPE_MSK                (0x000003F0)
  #define MPRDRTRN_CR_PRIMDN_COMP1_IMPH_FMT_CMDTYPE_MIN                (0)
  #define MPRDRTRN_CR_PRIMDN_COMP1_IMPH_FMT_CMDTYPE_MAX                (63) // 0x0000003F
  #define MPRDRTRN_CR_PRIMDN_COMP1_IMPH_FMT_CMDTYPE_DEF                (0x00000000)
  #define MPRDRTRN_CR_PRIMDN_COMP1_IMPH_FMT_CMDTYPE_HSH                (0x06047440)

  #define MPRDRTRN_CR_PRIMDN_COMP1_IMPH_TC_OFF                         (10)
  #define MPRDRTRN_CR_PRIMDN_COMP1_IMPH_TC_WID                         ( 4)
  #define MPRDRTRN_CR_PRIMDN_COMP1_IMPH_TC_MSK                         (0x00003C00)
  #define MPRDRTRN_CR_PRIMDN_COMP1_IMPH_TC_MIN                         (0)
  #define MPRDRTRN_CR_PRIMDN_COMP1_IMPH_TC_MAX                         (15) // 0x0000000F
  #define MPRDRTRN_CR_PRIMDN_COMP1_IMPH_TC_DEF                         (0x00000000)
  #define MPRDRTRN_CR_PRIMDN_COMP1_IMPH_TC_HSH                         (0x040A7440)

  #define MPRDRTRN_CR_PRIMDN_COMP1_IMPH_EP_OFF                         (14)
  #define MPRDRTRN_CR_PRIMDN_COMP1_IMPH_EP_WID                         ( 1)
  #define MPRDRTRN_CR_PRIMDN_COMP1_IMPH_EP_MSK                         (0x00004000)
  #define MPRDRTRN_CR_PRIMDN_COMP1_IMPH_EP_MIN                         (0)
  #define MPRDRTRN_CR_PRIMDN_COMP1_IMPH_EP_MAX                         (1) // 0x00000001
  #define MPRDRTRN_CR_PRIMDN_COMP1_IMPH_EP_DEF                         (0x00000000)
  #define MPRDRTRN_CR_PRIMDN_COMP1_IMPH_EP_HSH                         (0x010E7440)

  #define MPRDRTRN_CR_PRIMDN_COMP1_IMPH_NS_OFF                         (15)
  #define MPRDRTRN_CR_PRIMDN_COMP1_IMPH_NS_WID                         ( 1)
  #define MPRDRTRN_CR_PRIMDN_COMP1_IMPH_NS_MSK                         (0x00008000)
  #define MPRDRTRN_CR_PRIMDN_COMP1_IMPH_NS_MIN                         (0)
  #define MPRDRTRN_CR_PRIMDN_COMP1_IMPH_NS_MAX                         (1) // 0x00000001
  #define MPRDRTRN_CR_PRIMDN_COMP1_IMPH_NS_DEF                         (0x00000000)
  #define MPRDRTRN_CR_PRIMDN_COMP1_IMPH_NS_HSH                         (0x010F7440)

  #define MPRDRTRN_CR_PRIMDN_COMP1_IMPH_RO_OFF                         (16)
  #define MPRDRTRN_CR_PRIMDN_COMP1_IMPH_RO_WID                         ( 1)
  #define MPRDRTRN_CR_PRIMDN_COMP1_IMPH_RO_MSK                         (0x00010000)
  #define MPRDRTRN_CR_PRIMDN_COMP1_IMPH_RO_MIN                         (0)
  #define MPRDRTRN_CR_PRIMDN_COMP1_IMPH_RO_MAX                         (1) // 0x00000001
  #define MPRDRTRN_CR_PRIMDN_COMP1_IMPH_RO_DEF                         (0x00000000)
  #define MPRDRTRN_CR_PRIMDN_COMP1_IMPH_RO_HSH                         (0x01107440)

  #define MPRDRTRN_CR_PRIMDN_COMP1_IMPH_LENGTH_OFF                     (17)
  #define MPRDRTRN_CR_PRIMDN_COMP1_IMPH_LENGTH_WID                     ( 5)
  #define MPRDRTRN_CR_PRIMDN_COMP1_IMPH_LENGTH_MSK                     (0x003E0000)
  #define MPRDRTRN_CR_PRIMDN_COMP1_IMPH_LENGTH_MIN                     (0)
  #define MPRDRTRN_CR_PRIMDN_COMP1_IMPH_LENGTH_MAX                     (31) // 0x0000001F
  #define MPRDRTRN_CR_PRIMDN_COMP1_IMPH_LENGTH_DEF                     (0x00000000)
  #define MPRDRTRN_CR_PRIMDN_COMP1_IMPH_LENGTH_HSH                     (0x05117440)

#define MPRDRTRN_CR_PRIMDN_COMP2_IMPH_REG                              (0x00007444)

  #define MPRDRTRN_CR_PRIMDN_COMP2_IMPH_RQID_OFF                       ( 0)
  #define MPRDRTRN_CR_PRIMDN_COMP2_IMPH_RQID_WID                       (16)
  #define MPRDRTRN_CR_PRIMDN_COMP2_IMPH_RQID_MSK                       (0x0000FFFF)
  #define MPRDRTRN_CR_PRIMDN_COMP2_IMPH_RQID_MIN                       (0)
  #define MPRDRTRN_CR_PRIMDN_COMP2_IMPH_RQID_MAX                       (65535) // 0x0000FFFF
  #define MPRDRTRN_CR_PRIMDN_COMP2_IMPH_RQID_DEF                       (0x00000000)
  #define MPRDRTRN_CR_PRIMDN_COMP2_IMPH_RQID_HSH                       (0x10007444)

  #define MPRDRTRN_CR_PRIMDN_COMP2_IMPH_TAG_OFF                        (16)
  #define MPRDRTRN_CR_PRIMDN_COMP2_IMPH_TAG_WID                        ( 8)
  #define MPRDRTRN_CR_PRIMDN_COMP2_IMPH_TAG_MSK                        (0x00FF0000)
  #define MPRDRTRN_CR_PRIMDN_COMP2_IMPH_TAG_MIN                        (0)
  #define MPRDRTRN_CR_PRIMDN_COMP2_IMPH_TAG_MAX                        (255) // 0x000000FF
  #define MPRDRTRN_CR_PRIMDN_COMP2_IMPH_TAG_DEF                        (0x00000000)
  #define MPRDRTRN_CR_PRIMDN_COMP2_IMPH_TAG_HSH                        (0x08107444)

  #define MPRDRTRN_CR_PRIMDN_COMP2_IMPH_LBEFBE_MSGTYPE_OFF             (24)
  #define MPRDRTRN_CR_PRIMDN_COMP2_IMPH_LBEFBE_MSGTYPE_WID             ( 8)
  #define MPRDRTRN_CR_PRIMDN_COMP2_IMPH_LBEFBE_MSGTYPE_MSK             (0xFF000000)
  #define MPRDRTRN_CR_PRIMDN_COMP2_IMPH_LBEFBE_MSGTYPE_MIN             (0)
  #define MPRDRTRN_CR_PRIMDN_COMP2_IMPH_LBEFBE_MSGTYPE_MAX             (255) // 0x000000FF
  #define MPRDRTRN_CR_PRIMDN_COMP2_IMPH_LBEFBE_MSGTYPE_DEF             (0x00000000)
  #define MPRDRTRN_CR_PRIMDN_COMP2_IMPH_LBEFBE_MSGTYPE_HSH             (0x08187444)

#define MPRDRTRN_CR_PRIMDN_COMP3_IMPH_REG                              (0x00007448)

  #define MPRDRTRN_CR_PRIMDN_COMP3_IMPH_ADDR_31_0_OFF                  ( 0)
  #define MPRDRTRN_CR_PRIMDN_COMP3_IMPH_ADDR_31_0_WID                  (32)
  #define MPRDRTRN_CR_PRIMDN_COMP3_IMPH_ADDR_31_0_MSK                  (0xFFFFFFFF)
  #define MPRDRTRN_CR_PRIMDN_COMP3_IMPH_ADDR_31_0_MIN                  (0)
  #define MPRDRTRN_CR_PRIMDN_COMP3_IMPH_ADDR_31_0_MAX                  (4294967295) // 0xFFFFFFFF
  #define MPRDRTRN_CR_PRIMDN_COMP3_IMPH_ADDR_31_0_DEF                  (0x00000000)
  #define MPRDRTRN_CR_PRIMDN_COMP3_IMPH_ADDR_31_0_HSH                  (0x20007448)

#define MPRDRTRN_CR_PRIMDN_COMP4_IMPH_REG                              (0x0000744C)

  #define MPRDRTRN_CR_PRIMDN_COMP4_IMPH_ADDR_63_32_OFF                 ( 0)
  #define MPRDRTRN_CR_PRIMDN_COMP4_IMPH_ADDR_63_32_WID                 (32)
  #define MPRDRTRN_CR_PRIMDN_COMP4_IMPH_ADDR_63_32_MSK                 (0xFFFFFFFF)
  #define MPRDRTRN_CR_PRIMDN_COMP4_IMPH_ADDR_63_32_MIN                 (0)
  #define MPRDRTRN_CR_PRIMDN_COMP4_IMPH_ADDR_63_32_MAX                 (4294967295) // 0xFFFFFFFF
  #define MPRDRTRN_CR_PRIMDN_COMP4_IMPH_ADDR_63_32_DEF                 (0x00000000)
  #define MPRDRTRN_CR_PRIMDN_COMP4_IMPH_ADDR_63_32_HSH                 (0x2000744C)

#define MPRDRTRN_CR_PRIMDN_TRIGGER_IMPH_REG                            (0x00007450)

  #define MPRDRTRN_CR_PRIMDN_TRIGGER_IMPH_ENABLE_OFF                   ( 0)
  #define MPRDRTRN_CR_PRIMDN_TRIGGER_IMPH_ENABLE_WID                   ( 1)
  #define MPRDRTRN_CR_PRIMDN_TRIGGER_IMPH_ENABLE_MSK                   (0x00000001)
  #define MPRDRTRN_CR_PRIMDN_TRIGGER_IMPH_ENABLE_MIN                   (0)
  #define MPRDRTRN_CR_PRIMDN_TRIGGER_IMPH_ENABLE_MAX                   (1) // 0x00000001
  #define MPRDRTRN_CR_PRIMDN_TRIGGER_IMPH_ENABLE_DEF                   (0x00000000)
  #define MPRDRTRN_CR_PRIMDN_TRIGGER_IMPH_ENABLE_HSH                   (0x01007450)

  #define MPRDRTRN_CR_PRIMDN_TRIGGER_IMPH_TRIGGERED_OFF                ( 1)
  #define MPRDRTRN_CR_PRIMDN_TRIGGER_IMPH_TRIGGERED_WID                ( 1)
  #define MPRDRTRN_CR_PRIMDN_TRIGGER_IMPH_TRIGGERED_MSK                (0x00000002)
  #define MPRDRTRN_CR_PRIMDN_TRIGGER_IMPH_TRIGGERED_MIN                (0)
  #define MPRDRTRN_CR_PRIMDN_TRIGGER_IMPH_TRIGGERED_MAX                (1) // 0x00000001
  #define MPRDRTRN_CR_PRIMDN_TRIGGER_IMPH_TRIGGERED_DEF                (0x00000000)
  #define MPRDRTRN_CR_PRIMDN_TRIGGER_IMPH_TRIGGERED_HSH                (0x01017450)

  #define MPRDRTRN_CR_PRIMDN_TRIGGER_IMPH_STALL_DNARB_OFF              ( 2)
  #define MPRDRTRN_CR_PRIMDN_TRIGGER_IMPH_STALL_DNARB_WID              ( 1)
  #define MPRDRTRN_CR_PRIMDN_TRIGGER_IMPH_STALL_DNARB_MSK              (0x00000004)
  #define MPRDRTRN_CR_PRIMDN_TRIGGER_IMPH_STALL_DNARB_MIN              (0)
  #define MPRDRTRN_CR_PRIMDN_TRIGGER_IMPH_STALL_DNARB_MAX              (1) // 0x00000001
  #define MPRDRTRN_CR_PRIMDN_TRIGGER_IMPH_STALL_DNARB_DEF              (0x00000000)
  #define MPRDRTRN_CR_PRIMDN_TRIGGER_IMPH_STALL_DNARB_HSH              (0x01027450)

  #define MPRDRTRN_CR_PRIMDN_TRIGGER_IMPH_STALL_DELAY_OFF              (23)
  #define MPRDRTRN_CR_PRIMDN_TRIGGER_IMPH_STALL_DELAY_WID              ( 9)
  #define MPRDRTRN_CR_PRIMDN_TRIGGER_IMPH_STALL_DELAY_MSK              (0xFF800000)
  #define MPRDRTRN_CR_PRIMDN_TRIGGER_IMPH_STALL_DELAY_MIN              (0)
  #define MPRDRTRN_CR_PRIMDN_TRIGGER_IMPH_STALL_DELAY_MAX              (511) // 0x000001FF
  #define MPRDRTRN_CR_PRIMDN_TRIGGER_IMPH_STALL_DELAY_DEF              (0x00000000)
  #define MPRDRTRN_CR_PRIMDN_TRIGGER_IMPH_STALL_DELAY_HSH              (0x09177450)

#define MPRDRTRN_CR_CRDTCTL8_IMPH_REG                                  (0x00007454)

  #define MPRDRTRN_CR_CRDTCTL8_IMPH_DMIVCP_NPMAX_OFF                   ( 0)
  #define MPRDRTRN_CR_CRDTCTL8_IMPH_DMIVCP_NPMAX_WID                   ( 5)
  #define MPRDRTRN_CR_CRDTCTL8_IMPH_DMIVCP_NPMAX_MSK                   (0x0000001F)
  #define MPRDRTRN_CR_CRDTCTL8_IMPH_DMIVCP_NPMAX_MIN                   (0)
  #define MPRDRTRN_CR_CRDTCTL8_IMPH_DMIVCP_NPMAX_MAX                   (31) // 0x0000001F
  #define MPRDRTRN_CR_CRDTCTL8_IMPH_DMIVCP_NPMAX_DEF                   (0x00000000)
  #define MPRDRTRN_CR_CRDTCTL8_IMPH_DMIVCP_NPMAX_HSH                   (0x05007454)

  #define MPRDRTRN_CR_CRDTCTL8_IMPH_DMIVCM_NPMAX_OFF                   ( 5)
  #define MPRDRTRN_CR_CRDTCTL8_IMPH_DMIVCM_NPMAX_WID                   ( 5)
  #define MPRDRTRN_CR_CRDTCTL8_IMPH_DMIVCM_NPMAX_MSK                   (0x000003E0)
  #define MPRDRTRN_CR_CRDTCTL8_IMPH_DMIVCM_NPMAX_MIN                   (0)
  #define MPRDRTRN_CR_CRDTCTL8_IMPH_DMIVCM_NPMAX_MAX                   (31) // 0x0000001F
  #define MPRDRTRN_CR_CRDTCTL8_IMPH_DMIVCM_NPMAX_DEF                   (0x00000000)
  #define MPRDRTRN_CR_CRDTCTL8_IMPH_DMIVCM_NPMAX_HSH                   (0x05057454)

  #define MPRDRTRN_CR_CRDTCTL8_IMPH_DMIVC1_NPMAX_OFF                   (10)
  #define MPRDRTRN_CR_CRDTCTL8_IMPH_DMIVC1_NPMAX_WID                   ( 5)
  #define MPRDRTRN_CR_CRDTCTL8_IMPH_DMIVC1_NPMAX_MSK                   (0x00007C00)
  #define MPRDRTRN_CR_CRDTCTL8_IMPH_DMIVC1_NPMAX_MIN                   (0)
  #define MPRDRTRN_CR_CRDTCTL8_IMPH_DMIVC1_NPMAX_MAX                   (31) // 0x0000001F
  #define MPRDRTRN_CR_CRDTCTL8_IMPH_DMIVC1_NPMAX_DEF                   (0x00000000)
  #define MPRDRTRN_CR_CRDTCTL8_IMPH_DMIVC1_NPMAX_HSH                   (0x050A7454)

  #define MPRDRTRN_CR_CRDTCTL8_IMPH_CAMVC0_NPMAX_OFF                   (15)
  #define MPRDRTRN_CR_CRDTCTL8_IMPH_CAMVC0_NPMAX_WID                   ( 5)
  #define MPRDRTRN_CR_CRDTCTL8_IMPH_CAMVC0_NPMAX_MSK                   (0x000F8000)
  #define MPRDRTRN_CR_CRDTCTL8_IMPH_CAMVC0_NPMAX_MIN                   (0)
  #define MPRDRTRN_CR_CRDTCTL8_IMPH_CAMVC0_NPMAX_MAX                   (31) // 0x0000001F
  #define MPRDRTRN_CR_CRDTCTL8_IMPH_CAMVC0_NPMAX_DEF                   (0x00000000)
  #define MPRDRTRN_CR_CRDTCTL8_IMPH_CAMVC0_NPMAX_HSH                   (0x050F7454)

  #define MPRDRTRN_CR_CRDTCTL8_IMPH_GMMVC0_NPMAX_OFF                   (20)
  #define MPRDRTRN_CR_CRDTCTL8_IMPH_GMMVC0_NPMAX_WID                   ( 5)
  #define MPRDRTRN_CR_CRDTCTL8_IMPH_GMMVC0_NPMAX_MSK                   (0x01F00000)
  #define MPRDRTRN_CR_CRDTCTL8_IMPH_GMMVC0_NPMAX_MIN                   (0)
  #define MPRDRTRN_CR_CRDTCTL8_IMPH_GMMVC0_NPMAX_MAX                   (31) // 0x0000001F
  #define MPRDRTRN_CR_CRDTCTL8_IMPH_GMMVC0_NPMAX_DEF                   (0x00000000)
  #define MPRDRTRN_CR_CRDTCTL8_IMPH_GMMVC0_NPMAX_HSH                   (0x05147454)

#define MPRDRTRN_CR_CRDTCTL9_IMPH_REG                                  (0x00007458)

  #define MPRDRTRN_CR_CRDTCTL9_IMPH_DMIVC0_RRMAX_OFF                   ( 0)
  #define MPRDRTRN_CR_CRDTCTL9_IMPH_DMIVC0_RRMAX_WID                   ( 6)
  #define MPRDRTRN_CR_CRDTCTL9_IMPH_DMIVC0_RRMAX_MSK                   (0x0000003F)
  #define MPRDRTRN_CR_CRDTCTL9_IMPH_DMIVC0_RRMAX_MIN                   (0)
  #define MPRDRTRN_CR_CRDTCTL9_IMPH_DMIVC0_RRMAX_MAX                   (63) // 0x0000003F
  #define MPRDRTRN_CR_CRDTCTL9_IMPH_DMIVC0_RRMAX_DEF                   (0x00000000)
  #define MPRDRTRN_CR_CRDTCTL9_IMPH_DMIVC0_RRMAX_HSH                   (0x06007458)

  #define MPRDRTRN_CR_CRDTCTL9_IMPH_P10VC0_RRMAX_OFF                   ( 6)
  #define MPRDRTRN_CR_CRDTCTL9_IMPH_P10VC0_RRMAX_WID                   ( 6)
  #define MPRDRTRN_CR_CRDTCTL9_IMPH_P10VC0_RRMAX_MSK                   (0x00000FC0)
  #define MPRDRTRN_CR_CRDTCTL9_IMPH_P10VC0_RRMAX_MIN                   (0)
  #define MPRDRTRN_CR_CRDTCTL9_IMPH_P10VC0_RRMAX_MAX                   (63) // 0x0000003F
  #define MPRDRTRN_CR_CRDTCTL9_IMPH_P10VC0_RRMAX_DEF                   (0x00000000)
  #define MPRDRTRN_CR_CRDTCTL9_IMPH_P10VC0_RRMAX_HSH                   (0x06067458)

  #define MPRDRTRN_CR_CRDTCTL9_IMPH_P11VC0_RRMAX_OFF                   (12)
  #define MPRDRTRN_CR_CRDTCTL9_IMPH_P11VC0_RRMAX_WID                   ( 6)
  #define MPRDRTRN_CR_CRDTCTL9_IMPH_P11VC0_RRMAX_MSK                   (0x0003F000)
  #define MPRDRTRN_CR_CRDTCTL9_IMPH_P11VC0_RRMAX_MIN                   (0)
  #define MPRDRTRN_CR_CRDTCTL9_IMPH_P11VC0_RRMAX_MAX                   (63) // 0x0000003F
  #define MPRDRTRN_CR_CRDTCTL9_IMPH_P11VC0_RRMAX_DEF                   (0x00000000)
  #define MPRDRTRN_CR_CRDTCTL9_IMPH_P11VC0_RRMAX_HSH                   (0x060C7458)

  #define MPRDRTRN_CR_CRDTCTL9_IMPH_P12VC0_RRMAX_OFF                   (18)
  #define MPRDRTRN_CR_CRDTCTL9_IMPH_P12VC0_RRMAX_WID                   ( 6)
  #define MPRDRTRN_CR_CRDTCTL9_IMPH_P12VC0_RRMAX_MSK                   (0x00FC0000)
  #define MPRDRTRN_CR_CRDTCTL9_IMPH_P12VC0_RRMAX_MIN                   (0)
  #define MPRDRTRN_CR_CRDTCTL9_IMPH_P12VC0_RRMAX_MAX                   (63) // 0x0000003F
  #define MPRDRTRN_CR_CRDTCTL9_IMPH_P12VC0_RRMAX_DEF                   (0x00000000)
  #define MPRDRTRN_CR_CRDTCTL9_IMPH_P12VC0_RRMAX_HSH                   (0x06127458)

  #define MPRDRTRN_CR_CRDTCTL9_IMPH_DEVC0_RRMAX_OFF                    (24)
  #define MPRDRTRN_CR_CRDTCTL9_IMPH_DEVC0_RRMAX_WID                    ( 6)
  #define MPRDRTRN_CR_CRDTCTL9_IMPH_DEVC0_RRMAX_MSK                    (0x3F000000)
  #define MPRDRTRN_CR_CRDTCTL9_IMPH_DEVC0_RRMAX_MIN                    (0)
  #define MPRDRTRN_CR_CRDTCTL9_IMPH_DEVC0_RRMAX_MAX                    (63) // 0x0000003F
  #define MPRDRTRN_CR_CRDTCTL9_IMPH_DEVC0_RRMAX_DEF                    (0x00000000)
  #define MPRDRTRN_CR_CRDTCTL9_IMPH_DEVC0_RRMAX_HSH                    (0x06187458)

#define MPRDRTRN_CR_CRDTCTL10_IMPH_REG                                 (0x0000745C)

  #define MPRDRTRN_CR_CRDTCTL10_IMPH_CAMVC0_RRMAX_OFF                  ( 0)
  #define MPRDRTRN_CR_CRDTCTL10_IMPH_CAMVC0_RRMAX_WID                  ( 6)
  #define MPRDRTRN_CR_CRDTCTL10_IMPH_CAMVC0_RRMAX_MSK                  (0x0000003F)
  #define MPRDRTRN_CR_CRDTCTL10_IMPH_CAMVC0_RRMAX_MIN                  (0)
  #define MPRDRTRN_CR_CRDTCTL10_IMPH_CAMVC0_RRMAX_MAX                  (63) // 0x0000003F
  #define MPRDRTRN_CR_CRDTCTL10_IMPH_CAMVC0_RRMAX_DEF                  (0x00000000)
  #define MPRDRTRN_CR_CRDTCTL10_IMPH_CAMVC0_RRMAX_HSH                  (0x0600745C)

  #define MPRDRTRN_CR_CRDTCTL10_IMPH_GMMVC0_RRMAX_OFF                  ( 6)
  #define MPRDRTRN_CR_CRDTCTL10_IMPH_GMMVC0_RRMAX_WID                  ( 6)
  #define MPRDRTRN_CR_CRDTCTL10_IMPH_GMMVC0_RRMAX_MSK                  (0x00000FC0)
  #define MPRDRTRN_CR_CRDTCTL10_IMPH_GMMVC0_RRMAX_MIN                  (0)
  #define MPRDRTRN_CR_CRDTCTL10_IMPH_GMMVC0_RRMAX_MAX                  (63) // 0x0000003F
  #define MPRDRTRN_CR_CRDTCTL10_IMPH_GMMVC0_RRMAX_DEF                  (0x00000000)
  #define MPRDRTRN_CR_CRDTCTL10_IMPH_GMMVC0_RRMAX_HSH                  (0x0606745C)

#define MPRDRTRN_CR_CRDTCTL11_IMPH_REG                                 (0x00007460)

  #define MPRDRTRN_CR_CRDTCTL11_IMPH_DMIVCP_RRMAX_OFF                  ( 0)
  #define MPRDRTRN_CR_CRDTCTL11_IMPH_DMIVCP_RRMAX_WID                  ( 6)
  #define MPRDRTRN_CR_CRDTCTL11_IMPH_DMIVCP_RRMAX_MSK                  (0x0000003F)
  #define MPRDRTRN_CR_CRDTCTL11_IMPH_DMIVCP_RRMAX_MIN                  (0)
  #define MPRDRTRN_CR_CRDTCTL11_IMPH_DMIVCP_RRMAX_MAX                  (63) // 0x0000003F
  #define MPRDRTRN_CR_CRDTCTL11_IMPH_DMIVCP_RRMAX_DEF                  (0x00000000)
  #define MPRDRTRN_CR_CRDTCTL11_IMPH_DMIVCP_RRMAX_HSH                  (0x06007460)

  #define MPRDRTRN_CR_CRDTCTL11_IMPH_DMIVCM_RRMAX_OFF                  ( 6)
  #define MPRDRTRN_CR_CRDTCTL11_IMPH_DMIVCM_RRMAX_WID                  ( 6)
  #define MPRDRTRN_CR_CRDTCTL11_IMPH_DMIVCM_RRMAX_MSK                  (0x00000FC0)
  #define MPRDRTRN_CR_CRDTCTL11_IMPH_DMIVCM_RRMAX_MIN                  (0)
  #define MPRDRTRN_CR_CRDTCTL11_IMPH_DMIVCM_RRMAX_MAX                  (63) // 0x0000003F
  #define MPRDRTRN_CR_CRDTCTL11_IMPH_DMIVCM_RRMAX_DEF                  (0x00000000)
  #define MPRDRTRN_CR_CRDTCTL11_IMPH_DMIVCM_RRMAX_HSH                  (0x06067460)

  #define MPRDRTRN_CR_CRDTCTL11_IMPH_DMIVC1_RRMAX_OFF                  (12)
  #define MPRDRTRN_CR_CRDTCTL11_IMPH_DMIVC1_RRMAX_WID                  ( 6)
  #define MPRDRTRN_CR_CRDTCTL11_IMPH_DMIVC1_RRMAX_MSK                  (0x0003F000)
  #define MPRDRTRN_CR_CRDTCTL11_IMPH_DMIVC1_RRMAX_MIN                  (0)
  #define MPRDRTRN_CR_CRDTCTL11_IMPH_DMIVC1_RRMAX_MAX                  (63) // 0x0000003F
  #define MPRDRTRN_CR_CRDTCTL11_IMPH_DMIVC1_RRMAX_DEF                  (0x00000000)
  #define MPRDRTRN_CR_CRDTCTL11_IMPH_DMIVC1_RRMAX_HSH                  (0x060C7460)

  #define MPRDRTRN_CR_CRDTCTL11_IMPH_DEVC1_RRMAX_OFF                   (18)
  #define MPRDRTRN_CR_CRDTCTL11_IMPH_DEVC1_RRMAX_WID                   ( 6)
  #define MPRDRTRN_CR_CRDTCTL11_IMPH_DEVC1_RRMAX_MSK                   (0x00FC0000)
  #define MPRDRTRN_CR_CRDTCTL11_IMPH_DEVC1_RRMAX_MIN                   (0)
  #define MPRDRTRN_CR_CRDTCTL11_IMPH_DEVC1_RRMAX_MAX                   (63) // 0x0000003F
  #define MPRDRTRN_CR_CRDTCTL11_IMPH_DEVC1_RRMAX_DEF                   (0x00000000)
  #define MPRDRTRN_CR_CRDTCTL11_IMPH_DEVC1_RRMAX_HSH                   (0x06127460)

#define MPRDRTRN_CR_VISA_SLIDE_MPIORDTRKS_IMPH_REG                     (0x00007464)

  #define MPRDRTRN_CR_VISA_SLIDE_MPIORDTRKS_IMPH_WINDOW_SLIDE_L0_OFF   ( 0)
  #define MPRDRTRN_CR_VISA_SLIDE_MPIORDTRKS_IMPH_WINDOW_SLIDE_L0_WID   ( 3)
  #define MPRDRTRN_CR_VISA_SLIDE_MPIORDTRKS_IMPH_WINDOW_SLIDE_L0_MSK   (0x00000007)
  #define MPRDRTRN_CR_VISA_SLIDE_MPIORDTRKS_IMPH_WINDOW_SLIDE_L0_MIN   (0)
  #define MPRDRTRN_CR_VISA_SLIDE_MPIORDTRKS_IMPH_WINDOW_SLIDE_L0_MAX   (7) // 0x00000007
  #define MPRDRTRN_CR_VISA_SLIDE_MPIORDTRKS_IMPH_WINDOW_SLIDE_L0_DEF   (0x00000000)
  #define MPRDRTRN_CR_VISA_SLIDE_MPIORDTRKS_IMPH_WINDOW_SLIDE_L0_HSH   (0x03007464)

  #define MPRDRTRN_CR_VISA_SLIDE_MPIORDTRKS_IMPH_ALT_L0_DATA_BYTE_SEL_OFF ( 3)
  #define MPRDRTRN_CR_VISA_SLIDE_MPIORDTRKS_IMPH_ALT_L0_DATA_BYTE_SEL_WID ( 7)
  #define MPRDRTRN_CR_VISA_SLIDE_MPIORDTRKS_IMPH_ALT_L0_DATA_BYTE_SEL_MSK (0x000003F8)
  #define MPRDRTRN_CR_VISA_SLIDE_MPIORDTRKS_IMPH_ALT_L0_DATA_BYTE_SEL_MIN (0)
  #define MPRDRTRN_CR_VISA_SLIDE_MPIORDTRKS_IMPH_ALT_L0_DATA_BYTE_SEL_MAX (127) // 0x0000007F
  #define MPRDRTRN_CR_VISA_SLIDE_MPIORDTRKS_IMPH_ALT_L0_DATA_BYTE_SEL_DEF (0x00000000)
  #define MPRDRTRN_CR_VISA_SLIDE_MPIORDTRKS_IMPH_ALT_L0_DATA_BYTE_SEL_HSH (0x07037464)

  #define MPRDRTRN_CR_VISA_SLIDE_MPIORDTRKS_IMPH_WINDOW_SLIDE_L1_OFF   (10)
  #define MPRDRTRN_CR_VISA_SLIDE_MPIORDTRKS_IMPH_WINDOW_SLIDE_L1_WID   ( 3)
  #define MPRDRTRN_CR_VISA_SLIDE_MPIORDTRKS_IMPH_WINDOW_SLIDE_L1_MSK   (0x00001C00)
  #define MPRDRTRN_CR_VISA_SLIDE_MPIORDTRKS_IMPH_WINDOW_SLIDE_L1_MIN   (0)
  #define MPRDRTRN_CR_VISA_SLIDE_MPIORDTRKS_IMPH_WINDOW_SLIDE_L1_MAX   (7) // 0x00000007
  #define MPRDRTRN_CR_VISA_SLIDE_MPIORDTRKS_IMPH_WINDOW_SLIDE_L1_DEF   (0x00000000)
  #define MPRDRTRN_CR_VISA_SLIDE_MPIORDTRKS_IMPH_WINDOW_SLIDE_L1_HSH   (0x030A7464)

  #define MPRDRTRN_CR_VISA_SLIDE_MPIORDTRKS_IMPH_ALT_L1_DATA_BYTE_SEL_OFF (13)
  #define MPRDRTRN_CR_VISA_SLIDE_MPIORDTRKS_IMPH_ALT_L1_DATA_BYTE_SEL_WID ( 7)
  #define MPRDRTRN_CR_VISA_SLIDE_MPIORDTRKS_IMPH_ALT_L1_DATA_BYTE_SEL_MSK (0x000FE000)
  #define MPRDRTRN_CR_VISA_SLIDE_MPIORDTRKS_IMPH_ALT_L1_DATA_BYTE_SEL_MIN (0)
  #define MPRDRTRN_CR_VISA_SLIDE_MPIORDTRKS_IMPH_ALT_L1_DATA_BYTE_SEL_MAX (127) // 0x0000007F
  #define MPRDRTRN_CR_VISA_SLIDE_MPIORDTRKS_IMPH_ALT_L1_DATA_BYTE_SEL_DEF (0x00000000)
  #define MPRDRTRN_CR_VISA_SLIDE_MPIORDTRKS_IMPH_ALT_L1_DATA_BYTE_SEL_HSH (0x070D7464)

#define MPRDRTRN_CR_VISA_SLIDE_MPIOTRKS_IMPH_REG                       (0x00007468)

  #define MPRDRTRN_CR_VISA_SLIDE_MPIOTRKS_IMPH_WINDOW_SLIDE_L0_OFF     ( 0)
  #define MPRDRTRN_CR_VISA_SLIDE_MPIOTRKS_IMPH_WINDOW_SLIDE_L0_WID     ( 3)
  #define MPRDRTRN_CR_VISA_SLIDE_MPIOTRKS_IMPH_WINDOW_SLIDE_L0_MSK     (0x00000007)
  #define MPRDRTRN_CR_VISA_SLIDE_MPIOTRKS_IMPH_WINDOW_SLIDE_L0_MIN     (0)
  #define MPRDRTRN_CR_VISA_SLIDE_MPIOTRKS_IMPH_WINDOW_SLIDE_L0_MAX     (7) // 0x00000007
  #define MPRDRTRN_CR_VISA_SLIDE_MPIOTRKS_IMPH_WINDOW_SLIDE_L0_DEF     (0x00000000)
  #define MPRDRTRN_CR_VISA_SLIDE_MPIOTRKS_IMPH_WINDOW_SLIDE_L0_HSH     (0x03007468)

  #define MPRDRTRN_CR_VISA_SLIDE_MPIOTRKS_IMPH_ALT_L0_DATA_BYTE_SEL_OFF ( 3)
  #define MPRDRTRN_CR_VISA_SLIDE_MPIOTRKS_IMPH_ALT_L0_DATA_BYTE_SEL_WID ( 7)
  #define MPRDRTRN_CR_VISA_SLIDE_MPIOTRKS_IMPH_ALT_L0_DATA_BYTE_SEL_MSK (0x000003F8)
  #define MPRDRTRN_CR_VISA_SLIDE_MPIOTRKS_IMPH_ALT_L0_DATA_BYTE_SEL_MIN (0)
  #define MPRDRTRN_CR_VISA_SLIDE_MPIOTRKS_IMPH_ALT_L0_DATA_BYTE_SEL_MAX (127) // 0x0000007F
  #define MPRDRTRN_CR_VISA_SLIDE_MPIOTRKS_IMPH_ALT_L0_DATA_BYTE_SEL_DEF (0x00000000)
  #define MPRDRTRN_CR_VISA_SLIDE_MPIOTRKS_IMPH_ALT_L0_DATA_BYTE_SEL_HSH (0x07037468)

  #define MPRDRTRN_CR_VISA_SLIDE_MPIOTRKS_IMPH_WINDOW_SLIDE_L1_OFF     (10)
  #define MPRDRTRN_CR_VISA_SLIDE_MPIOTRKS_IMPH_WINDOW_SLIDE_L1_WID     ( 3)
  #define MPRDRTRN_CR_VISA_SLIDE_MPIOTRKS_IMPH_WINDOW_SLIDE_L1_MSK     (0x00001C00)
  #define MPRDRTRN_CR_VISA_SLIDE_MPIOTRKS_IMPH_WINDOW_SLIDE_L1_MIN     (0)
  #define MPRDRTRN_CR_VISA_SLIDE_MPIOTRKS_IMPH_WINDOW_SLIDE_L1_MAX     (7) // 0x00000007
  #define MPRDRTRN_CR_VISA_SLIDE_MPIOTRKS_IMPH_WINDOW_SLIDE_L1_DEF     (0x00000000)
  #define MPRDRTRN_CR_VISA_SLIDE_MPIOTRKS_IMPH_WINDOW_SLIDE_L1_HSH     (0x030A7468)

  #define MPRDRTRN_CR_VISA_SLIDE_MPIOTRKS_IMPH_ALT_L1_DATA_BYTE_SEL_OFF (13)
  #define MPRDRTRN_CR_VISA_SLIDE_MPIOTRKS_IMPH_ALT_L1_DATA_BYTE_SEL_WID ( 7)
  #define MPRDRTRN_CR_VISA_SLIDE_MPIOTRKS_IMPH_ALT_L1_DATA_BYTE_SEL_MSK (0x000FE000)
  #define MPRDRTRN_CR_VISA_SLIDE_MPIOTRKS_IMPH_ALT_L1_DATA_BYTE_SEL_MIN (0)
  #define MPRDRTRN_CR_VISA_SLIDE_MPIOTRKS_IMPH_ALT_L1_DATA_BYTE_SEL_MAX (127) // 0x0000007F
  #define MPRDRTRN_CR_VISA_SLIDE_MPIOTRKS_IMPH_ALT_L1_DATA_BYTE_SEL_DEF (0x00000000)
  #define MPRDRTRN_CR_VISA_SLIDE_MPIOTRKS_IMPH_ALT_L1_DATA_BYTE_SEL_HSH (0x070D7468)

#define MPRDRTRN_CR_CRDTCTL12_IMPH_REG                                 (0x0000746C)

  #define MPRDRTRN_CR_CRDTCTL12_IMPH_IOTRK_SHRD_OFF                    ( 0)
  #define MPRDRTRN_CR_CRDTCTL12_IMPH_IOTRK_SHRD_WID                    ( 6)
  #define MPRDRTRN_CR_CRDTCTL12_IMPH_IOTRK_SHRD_MSK                    (0x0000003F)
  #define MPRDRTRN_CR_CRDTCTL12_IMPH_IOTRK_SHRD_MIN                    (0)
  #define MPRDRTRN_CR_CRDTCTL12_IMPH_IOTRK_SHRD_MAX                    (63) // 0x0000003F
  #define MPRDRTRN_CR_CRDTCTL12_IMPH_IOTRK_SHRD_DEF                    (0x00000000)
  #define MPRDRTRN_CR_CRDTCTL12_IMPH_IOTRK_SHRD_HSH                    (0x0600746C)

  #define MPRDRTRN_CR_CRDTCTL12_IMPH_RRTRK_SHRD_OFF                    ( 6)
  #define MPRDRTRN_CR_CRDTCTL12_IMPH_RRTRK_SHRD_WID                    ( 6)
  #define MPRDRTRN_CR_CRDTCTL12_IMPH_RRTRK_SHRD_MSK                    (0x00000FC0)
  #define MPRDRTRN_CR_CRDTCTL12_IMPH_RRTRK_SHRD_MIN                    (0)
  #define MPRDRTRN_CR_CRDTCTL12_IMPH_RRTRK_SHRD_MAX                    (63) // 0x0000003F
  #define MPRDRTRN_CR_CRDTCTL12_IMPH_RRTRK_SHRD_DEF                    (0x00000000)
  #define MPRDRTRN_CR_CRDTCTL12_IMPH_RRTRK_SHRD_HSH                    (0x0606746C)

#define MPRDRTRN_CR_CRDTCTL13_IMPH_REG                                 (0x00007470)

  #define MPRDRTRN_CR_CRDTCTL13_IMPH_DMIVC0_PINIT_OFF                  ( 0)
  #define MPRDRTRN_CR_CRDTCTL13_IMPH_DMIVC0_PINIT_WID                  ( 3)
  #define MPRDRTRN_CR_CRDTCTL13_IMPH_DMIVC0_PINIT_MSK                  (0x00000007)
  #define MPRDRTRN_CR_CRDTCTL13_IMPH_DMIVC0_PINIT_MIN                  (0)
  #define MPRDRTRN_CR_CRDTCTL13_IMPH_DMIVC0_PINIT_MAX                  (7) // 0x00000007
  #define MPRDRTRN_CR_CRDTCTL13_IMPH_DMIVC0_PINIT_DEF                  (0x00000000)
  #define MPRDRTRN_CR_CRDTCTL13_IMPH_DMIVC0_PINIT_HSH                  (0x03007470)

  #define MPRDRTRN_CR_CRDTCTL13_IMPH_P10VC0_PINIT_OFF                  ( 3)
  #define MPRDRTRN_CR_CRDTCTL13_IMPH_P10VC0_PINIT_WID                  ( 3)
  #define MPRDRTRN_CR_CRDTCTL13_IMPH_P10VC0_PINIT_MSK                  (0x00000038)
  #define MPRDRTRN_CR_CRDTCTL13_IMPH_P10VC0_PINIT_MIN                  (0)
  #define MPRDRTRN_CR_CRDTCTL13_IMPH_P10VC0_PINIT_MAX                  (7) // 0x00000007
  #define MPRDRTRN_CR_CRDTCTL13_IMPH_P10VC0_PINIT_DEF                  (0x00000000)
  #define MPRDRTRN_CR_CRDTCTL13_IMPH_P10VC0_PINIT_HSH                  (0x03037470)

  #define MPRDRTRN_CR_CRDTCTL13_IMPH_P11VC0_PINIT_OFF                  ( 6)
  #define MPRDRTRN_CR_CRDTCTL13_IMPH_P11VC0_PINIT_WID                  ( 3)
  #define MPRDRTRN_CR_CRDTCTL13_IMPH_P11VC0_PINIT_MSK                  (0x000001C0)
  #define MPRDRTRN_CR_CRDTCTL13_IMPH_P11VC0_PINIT_MIN                  (0)
  #define MPRDRTRN_CR_CRDTCTL13_IMPH_P11VC0_PINIT_MAX                  (7) // 0x00000007
  #define MPRDRTRN_CR_CRDTCTL13_IMPH_P11VC0_PINIT_DEF                  (0x00000000)
  #define MPRDRTRN_CR_CRDTCTL13_IMPH_P11VC0_PINIT_HSH                  (0x03067470)

  #define MPRDRTRN_CR_CRDTCTL13_IMPH_P12VC0_PINIT_OFF                  ( 9)
  #define MPRDRTRN_CR_CRDTCTL13_IMPH_P12VC0_PINIT_WID                  ( 3)
  #define MPRDRTRN_CR_CRDTCTL13_IMPH_P12VC0_PINIT_MSK                  (0x00000E00)
  #define MPRDRTRN_CR_CRDTCTL13_IMPH_P12VC0_PINIT_MIN                  (0)
  #define MPRDRTRN_CR_CRDTCTL13_IMPH_P12VC0_PINIT_MAX                  (7) // 0x00000007
  #define MPRDRTRN_CR_CRDTCTL13_IMPH_P12VC0_PINIT_DEF                  (0x00000000)
  #define MPRDRTRN_CR_CRDTCTL13_IMPH_P12VC0_PINIT_HSH                  (0x03097470)

  #define MPRDRTRN_CR_CRDTCTL13_IMPH_DEVC0_PINIT_OFF                   (12)
  #define MPRDRTRN_CR_CRDTCTL13_IMPH_DEVC0_PINIT_WID                   ( 3)
  #define MPRDRTRN_CR_CRDTCTL13_IMPH_DEVC0_PINIT_MSK                   (0x00007000)
  #define MPRDRTRN_CR_CRDTCTL13_IMPH_DEVC0_PINIT_MIN                   (0)
  #define MPRDRTRN_CR_CRDTCTL13_IMPH_DEVC0_PINIT_MAX                   (7) // 0x00000007
  #define MPRDRTRN_CR_CRDTCTL13_IMPH_DEVC0_PINIT_DEF                   (0x00000000)
  #define MPRDRTRN_CR_CRDTCTL13_IMPH_DEVC0_PINIT_HSH                   (0x030C7470)

  #define MPRDRTRN_CR_CRDTCTL13_IMPH_DMIVCP_PINIT_OFF                  (15)
  #define MPRDRTRN_CR_CRDTCTL13_IMPH_DMIVCP_PINIT_WID                  ( 3)
  #define MPRDRTRN_CR_CRDTCTL13_IMPH_DMIVCP_PINIT_MSK                  (0x00038000)
  #define MPRDRTRN_CR_CRDTCTL13_IMPH_DMIVCP_PINIT_MIN                  (0)
  #define MPRDRTRN_CR_CRDTCTL13_IMPH_DMIVCP_PINIT_MAX                  (7) // 0x00000007
  #define MPRDRTRN_CR_CRDTCTL13_IMPH_DMIVCP_PINIT_DEF                  (0x00000000)
  #define MPRDRTRN_CR_CRDTCTL13_IMPH_DMIVCP_PINIT_HSH                  (0x030F7470)

  #define MPRDRTRN_CR_CRDTCTL13_IMPH_DMIVCM_PINIT_OFF                  (18)
  #define MPRDRTRN_CR_CRDTCTL13_IMPH_DMIVCM_PINIT_WID                  ( 3)
  #define MPRDRTRN_CR_CRDTCTL13_IMPH_DMIVCM_PINIT_MSK                  (0x001C0000)
  #define MPRDRTRN_CR_CRDTCTL13_IMPH_DMIVCM_PINIT_MIN                  (0)
  #define MPRDRTRN_CR_CRDTCTL13_IMPH_DMIVCM_PINIT_MAX                  (7) // 0x00000007
  #define MPRDRTRN_CR_CRDTCTL13_IMPH_DMIVCM_PINIT_DEF                  (0x00000000)
  #define MPRDRTRN_CR_CRDTCTL13_IMPH_DMIVCM_PINIT_HSH                  (0x03127470)

  #define MPRDRTRN_CR_CRDTCTL13_IMPH_DMIVC1_PINIT_OFF                  (21)
  #define MPRDRTRN_CR_CRDTCTL13_IMPH_DMIVC1_PINIT_WID                  ( 3)
  #define MPRDRTRN_CR_CRDTCTL13_IMPH_DMIVC1_PINIT_MSK                  (0x00E00000)
  #define MPRDRTRN_CR_CRDTCTL13_IMPH_DMIVC1_PINIT_MIN                  (0)
  #define MPRDRTRN_CR_CRDTCTL13_IMPH_DMIVC1_PINIT_MAX                  (7) // 0x00000007
  #define MPRDRTRN_CR_CRDTCTL13_IMPH_DMIVC1_PINIT_DEF                  (0x00000000)
  #define MPRDRTRN_CR_CRDTCTL13_IMPH_DMIVC1_PINIT_HSH                  (0x03157470)

  #define MPRDRTRN_CR_CRDTCTL13_IMPH_CAMVC0_PINIT_OFF                  (24)
  #define MPRDRTRN_CR_CRDTCTL13_IMPH_CAMVC0_PINIT_WID                  ( 3)
  #define MPRDRTRN_CR_CRDTCTL13_IMPH_CAMVC0_PINIT_MSK                  (0x07000000)
  #define MPRDRTRN_CR_CRDTCTL13_IMPH_CAMVC0_PINIT_MIN                  (0)
  #define MPRDRTRN_CR_CRDTCTL13_IMPH_CAMVC0_PINIT_MAX                  (7) // 0x00000007
  #define MPRDRTRN_CR_CRDTCTL13_IMPH_CAMVC0_PINIT_DEF                  (0x00000000)
  #define MPRDRTRN_CR_CRDTCTL13_IMPH_CAMVC0_PINIT_HSH                  (0x03187470)

  #define MPRDRTRN_CR_CRDTCTL13_IMPH_GMMVC0_PINIT_OFF                  (27)
  #define MPRDRTRN_CR_CRDTCTL13_IMPH_GMMVC0_PINIT_WID                  ( 3)
  #define MPRDRTRN_CR_CRDTCTL13_IMPH_GMMVC0_PINIT_MSK                  (0x38000000)
  #define MPRDRTRN_CR_CRDTCTL13_IMPH_GMMVC0_PINIT_MIN                  (0)
  #define MPRDRTRN_CR_CRDTCTL13_IMPH_GMMVC0_PINIT_MAX                  (7) // 0x00000007
  #define MPRDRTRN_CR_CRDTCTL13_IMPH_GMMVC0_PINIT_DEF                  (0x00000000)
  #define MPRDRTRN_CR_CRDTCTL13_IMPH_GMMVC0_PINIT_HSH                  (0x031B7470)

#define MPRDRTRN_CR_CRDTCTL14_IMPH_REG                                 (0x00007474)

  #define MPRDRTRN_CR_CRDTCTL14_IMPH_DMIVC0_NPINIT_OFF                 ( 0)
  #define MPRDRTRN_CR_CRDTCTL14_IMPH_DMIVC0_NPINIT_WID                 ( 3)
  #define MPRDRTRN_CR_CRDTCTL14_IMPH_DMIVC0_NPINIT_MSK                 (0x00000007)
  #define MPRDRTRN_CR_CRDTCTL14_IMPH_DMIVC0_NPINIT_MIN                 (0)
  #define MPRDRTRN_CR_CRDTCTL14_IMPH_DMIVC0_NPINIT_MAX                 (7) // 0x00000007
  #define MPRDRTRN_CR_CRDTCTL14_IMPH_DMIVC0_NPINIT_DEF                 (0x00000000)
  #define MPRDRTRN_CR_CRDTCTL14_IMPH_DMIVC0_NPINIT_HSH                 (0x03007474)

  #define MPRDRTRN_CR_CRDTCTL14_IMPH_P10VC0_NPINIT_OFF                 ( 3)
  #define MPRDRTRN_CR_CRDTCTL14_IMPH_P10VC0_NPINIT_WID                 ( 3)
  #define MPRDRTRN_CR_CRDTCTL14_IMPH_P10VC0_NPINIT_MSK                 (0x00000038)
  #define MPRDRTRN_CR_CRDTCTL14_IMPH_P10VC0_NPINIT_MIN                 (0)
  #define MPRDRTRN_CR_CRDTCTL14_IMPH_P10VC0_NPINIT_MAX                 (7) // 0x00000007
  #define MPRDRTRN_CR_CRDTCTL14_IMPH_P10VC0_NPINIT_DEF                 (0x00000000)
  #define MPRDRTRN_CR_CRDTCTL14_IMPH_P10VC0_NPINIT_HSH                 (0x03037474)

  #define MPRDRTRN_CR_CRDTCTL14_IMPH_P11VC0_NPINIT_OFF                 ( 6)
  #define MPRDRTRN_CR_CRDTCTL14_IMPH_P11VC0_NPINIT_WID                 ( 3)
  #define MPRDRTRN_CR_CRDTCTL14_IMPH_P11VC0_NPINIT_MSK                 (0x000001C0)
  #define MPRDRTRN_CR_CRDTCTL14_IMPH_P11VC0_NPINIT_MIN                 (0)
  #define MPRDRTRN_CR_CRDTCTL14_IMPH_P11VC0_NPINIT_MAX                 (7) // 0x00000007
  #define MPRDRTRN_CR_CRDTCTL14_IMPH_P11VC0_NPINIT_DEF                 (0x00000000)
  #define MPRDRTRN_CR_CRDTCTL14_IMPH_P11VC0_NPINIT_HSH                 (0x03067474)

  #define MPRDRTRN_CR_CRDTCTL14_IMPH_P12VC0_NPINIT_OFF                 ( 9)
  #define MPRDRTRN_CR_CRDTCTL14_IMPH_P12VC0_NPINIT_WID                 ( 3)
  #define MPRDRTRN_CR_CRDTCTL14_IMPH_P12VC0_NPINIT_MSK                 (0x00000E00)
  #define MPRDRTRN_CR_CRDTCTL14_IMPH_P12VC0_NPINIT_MIN                 (0)
  #define MPRDRTRN_CR_CRDTCTL14_IMPH_P12VC0_NPINIT_MAX                 (7) // 0x00000007
  #define MPRDRTRN_CR_CRDTCTL14_IMPH_P12VC0_NPINIT_DEF                 (0x00000000)
  #define MPRDRTRN_CR_CRDTCTL14_IMPH_P12VC0_NPINIT_HSH                 (0x03097474)

  #define MPRDRTRN_CR_CRDTCTL14_IMPH_DEVC0_NPINIT_OFF                  (12)
  #define MPRDRTRN_CR_CRDTCTL14_IMPH_DEVC0_NPINIT_WID                  ( 3)
  #define MPRDRTRN_CR_CRDTCTL14_IMPH_DEVC0_NPINIT_MSK                  (0x00007000)
  #define MPRDRTRN_CR_CRDTCTL14_IMPH_DEVC0_NPINIT_MIN                  (0)
  #define MPRDRTRN_CR_CRDTCTL14_IMPH_DEVC0_NPINIT_MAX                  (7) // 0x00000007
  #define MPRDRTRN_CR_CRDTCTL14_IMPH_DEVC0_NPINIT_DEF                  (0x00000000)
  #define MPRDRTRN_CR_CRDTCTL14_IMPH_DEVC0_NPINIT_HSH                  (0x030C7474)

  #define MPRDRTRN_CR_CRDTCTL14_IMPH_DMIVCP_NPINIT_OFF                 (15)
  #define MPRDRTRN_CR_CRDTCTL14_IMPH_DMIVCP_NPINIT_WID                 ( 3)
  #define MPRDRTRN_CR_CRDTCTL14_IMPH_DMIVCP_NPINIT_MSK                 (0x00038000)
  #define MPRDRTRN_CR_CRDTCTL14_IMPH_DMIVCP_NPINIT_MIN                 (0)
  #define MPRDRTRN_CR_CRDTCTL14_IMPH_DMIVCP_NPINIT_MAX                 (7) // 0x00000007
  #define MPRDRTRN_CR_CRDTCTL14_IMPH_DMIVCP_NPINIT_DEF                 (0x00000000)
  #define MPRDRTRN_CR_CRDTCTL14_IMPH_DMIVCP_NPINIT_HSH                 (0x030F7474)

  #define MPRDRTRN_CR_CRDTCTL14_IMPH_DMIVCM_NPINIT_OFF                 (18)
  #define MPRDRTRN_CR_CRDTCTL14_IMPH_DMIVCM_NPINIT_WID                 ( 3)
  #define MPRDRTRN_CR_CRDTCTL14_IMPH_DMIVCM_NPINIT_MSK                 (0x001C0000)
  #define MPRDRTRN_CR_CRDTCTL14_IMPH_DMIVCM_NPINIT_MIN                 (0)
  #define MPRDRTRN_CR_CRDTCTL14_IMPH_DMIVCM_NPINIT_MAX                 (7) // 0x00000007
  #define MPRDRTRN_CR_CRDTCTL14_IMPH_DMIVCM_NPINIT_DEF                 (0x00000000)
  #define MPRDRTRN_CR_CRDTCTL14_IMPH_DMIVCM_NPINIT_HSH                 (0x03127474)

  #define MPRDRTRN_CR_CRDTCTL14_IMPH_DMIVC1_NPINIT_OFF                 (21)
  #define MPRDRTRN_CR_CRDTCTL14_IMPH_DMIVC1_NPINIT_WID                 ( 3)
  #define MPRDRTRN_CR_CRDTCTL14_IMPH_DMIVC1_NPINIT_MSK                 (0x00E00000)
  #define MPRDRTRN_CR_CRDTCTL14_IMPH_DMIVC1_NPINIT_MIN                 (0)
  #define MPRDRTRN_CR_CRDTCTL14_IMPH_DMIVC1_NPINIT_MAX                 (7) // 0x00000007
  #define MPRDRTRN_CR_CRDTCTL14_IMPH_DMIVC1_NPINIT_DEF                 (0x00000000)
  #define MPRDRTRN_CR_CRDTCTL14_IMPH_DMIVC1_NPINIT_HSH                 (0x03157474)

  #define MPRDRTRN_CR_CRDTCTL14_IMPH_CAMVC0_NPINIT_OFF                 (24)
  #define MPRDRTRN_CR_CRDTCTL14_IMPH_CAMVC0_NPINIT_WID                 ( 3)
  #define MPRDRTRN_CR_CRDTCTL14_IMPH_CAMVC0_NPINIT_MSK                 (0x07000000)
  #define MPRDRTRN_CR_CRDTCTL14_IMPH_CAMVC0_NPINIT_MIN                 (0)
  #define MPRDRTRN_CR_CRDTCTL14_IMPH_CAMVC0_NPINIT_MAX                 (7) // 0x00000007
  #define MPRDRTRN_CR_CRDTCTL14_IMPH_CAMVC0_NPINIT_DEF                 (0x00000000)
  #define MPRDRTRN_CR_CRDTCTL14_IMPH_CAMVC0_NPINIT_HSH                 (0x03187474)

  #define MPRDRTRN_CR_CRDTCTL14_IMPH_GMMVC0_NPINIT_OFF                 (27)
  #define MPRDRTRN_CR_CRDTCTL14_IMPH_GMMVC0_NPINIT_WID                 ( 3)
  #define MPRDRTRN_CR_CRDTCTL14_IMPH_GMMVC0_NPINIT_MSK                 (0x38000000)
  #define MPRDRTRN_CR_CRDTCTL14_IMPH_GMMVC0_NPINIT_MIN                 (0)
  #define MPRDRTRN_CR_CRDTCTL14_IMPH_GMMVC0_NPINIT_MAX                 (7) // 0x00000007
  #define MPRDRTRN_CR_CRDTCTL14_IMPH_GMMVC0_NPINIT_DEF                 (0x00000000)
  #define MPRDRTRN_CR_CRDTCTL14_IMPH_GMMVC0_NPINIT_HSH                 (0x031B7474)

#define MPRDRTRN_CR_PCIE_POPUP_CTL_IMPH_REG                            (0x00007500)

  #define MPRDRTRN_CR_PCIE_POPUP_CTL_IMPH_LIM_OFF                      ( 0)
  #define MPRDRTRN_CR_PCIE_POPUP_CTL_IMPH_LIM_WID                      (16)
  #define MPRDRTRN_CR_PCIE_POPUP_CTL_IMPH_LIM_MSK                      (0x0000FFFF)
  #define MPRDRTRN_CR_PCIE_POPUP_CTL_IMPH_LIM_MIN                      (0)
  #define MPRDRTRN_CR_PCIE_POPUP_CTL_IMPH_LIM_MAX                      (65535) // 0x0000FFFF
  #define MPRDRTRN_CR_PCIE_POPUP_CTL_IMPH_LIM_DEF                      (0x00000000)
  #define MPRDRTRN_CR_PCIE_POPUP_CTL_IMPH_LIM_HSH                      (0x10007500)

  #define MPRDRTRN_CR_PCIE_POPUP_CTL_IMPH_MSK_OFF                      (16)
  #define MPRDRTRN_CR_PCIE_POPUP_CTL_IMPH_MSK_WID                      ( 3)
  #define MPRDRTRN_CR_PCIE_POPUP_CTL_IMPH_MSK_MSK                      (0x00070000)
  #define MPRDRTRN_CR_PCIE_POPUP_CTL_IMPH_MSK_MIN                      (0)
  #define MPRDRTRN_CR_PCIE_POPUP_CTL_IMPH_MSK_MAX                      (7) // 0x00000007
  #define MPRDRTRN_CR_PCIE_POPUP_CTL_IMPH_MSK_DEF                      (0x00000007)
  #define MPRDRTRN_CR_PCIE_POPUP_CTL_IMPH_MSK_HSH                      (0x03107500)

#define MPRDRTRN_CR_VDMBDFBARSSKU_IMPH_REG                             (0x00007504)

  #define MPRDRTRN_CR_VDMBDFBARSSKU_IMPH_FUNNUM_OFF                    ( 0)
  #define MPRDRTRN_CR_VDMBDFBARSSKU_IMPH_FUNNUM_WID                    ( 3)
  #define MPRDRTRN_CR_VDMBDFBARSSKU_IMPH_FUNNUM_MSK                    (0x00000007)
  #define MPRDRTRN_CR_VDMBDFBARSSKU_IMPH_FUNNUM_MIN                    (0)
  #define MPRDRTRN_CR_VDMBDFBARSSKU_IMPH_FUNNUM_MAX                    (7) // 0x00000007
  #define MPRDRTRN_CR_VDMBDFBARSSKU_IMPH_FUNNUM_DEF                    (0x00000000)
  #define MPRDRTRN_CR_VDMBDFBARSSKU_IMPH_FUNNUM_HSH                    (0x03007504)

  #define MPRDRTRN_CR_VDMBDFBARSSKU_IMPH_DEVNUM_OFF                    ( 3)
  #define MPRDRTRN_CR_VDMBDFBARSSKU_IMPH_DEVNUM_WID                    ( 5)
  #define MPRDRTRN_CR_VDMBDFBARSSKU_IMPH_DEVNUM_MSK                    (0x000000F8)
  #define MPRDRTRN_CR_VDMBDFBARSSKU_IMPH_DEVNUM_MIN                    (0)
  #define MPRDRTRN_CR_VDMBDFBARSSKU_IMPH_DEVNUM_MAX                    (31) // 0x0000001F
  #define MPRDRTRN_CR_VDMBDFBARSSKU_IMPH_DEVNUM_DEF                    (0x00000016)
  #define MPRDRTRN_CR_VDMBDFBARSSKU_IMPH_DEVNUM_HSH                    (0x05037504)

  #define MPRDRTRN_CR_VDMBDFBARSSKU_IMPH_BUSNUM_OFF                    ( 8)
  #define MPRDRTRN_CR_VDMBDFBARSSKU_IMPH_BUSNUM_WID                    ( 8)
  #define MPRDRTRN_CR_VDMBDFBARSSKU_IMPH_BUSNUM_MSK                    (0x0000FF00)
  #define MPRDRTRN_CR_VDMBDFBARSSKU_IMPH_BUSNUM_MIN                    (0)
  #define MPRDRTRN_CR_VDMBDFBARSSKU_IMPH_BUSNUM_MAX                    (255) // 0x000000FF
  #define MPRDRTRN_CR_VDMBDFBARSSKU_IMPH_BUSNUM_DEF                    (0x00000000)
  #define MPRDRTRN_CR_VDMBDFBARSSKU_IMPH_BUSNUM_HSH                    (0x08087504)

  #define MPRDRTRN_CR_VDMBDFBARSSKU_IMPH_BARNUM_OFF                    (16)
  #define MPRDRTRN_CR_VDMBDFBARSSKU_IMPH_BARNUM_WID                    ( 3)
  #define MPRDRTRN_CR_VDMBDFBARSSKU_IMPH_BARNUM_MSK                    (0x00070000)
  #define MPRDRTRN_CR_VDMBDFBARSSKU_IMPH_BARNUM_MIN                    (0)
  #define MPRDRTRN_CR_VDMBDFBARSSKU_IMPH_BARNUM_MAX                    (7) // 0x00000007
  #define MPRDRTRN_CR_VDMBDFBARSSKU_IMPH_BARNUM_DEF                    (0x00000007)
  #define MPRDRTRN_CR_VDMBDFBARSSKU_IMPH_BARNUM_HSH                    (0x03107504)

#define MPRDRTRN_CR_IOTRK_CRDT_RTRN_IPC_IMPH_REG                       (0x00007600)

  #define MPRDRTRN_CR_IOTRK_CRDT_RTRN_IPC_IMPH_NON_VC1_THRESHOLD_OFF   ( 0)
  #define MPRDRTRN_CR_IOTRK_CRDT_RTRN_IPC_IMPH_NON_VC1_THRESHOLD_WID   ( 4)
  #define MPRDRTRN_CR_IOTRK_CRDT_RTRN_IPC_IMPH_NON_VC1_THRESHOLD_MSK   (0x0000000F)
  #define MPRDRTRN_CR_IOTRK_CRDT_RTRN_IPC_IMPH_NON_VC1_THRESHOLD_MIN   (0)
  #define MPRDRTRN_CR_IOTRK_CRDT_RTRN_IPC_IMPH_NON_VC1_THRESHOLD_MAX   (15) // 0x0000000F
  #define MPRDRTRN_CR_IOTRK_CRDT_RTRN_IPC_IMPH_NON_VC1_THRESHOLD_DEF   (0x00000008)
  #define MPRDRTRN_CR_IOTRK_CRDT_RTRN_IPC_IMPH_NON_VC1_THRESHOLD_HSH   (0x04007600)

  #define MPRDRTRN_CR_IOTRK_CRDT_RTRN_IPC_IMPH_VC1_RD_THRESHOLD_OFF    ( 4)
  #define MPRDRTRN_CR_IOTRK_CRDT_RTRN_IPC_IMPH_VC1_RD_THRESHOLD_WID    ( 4)
  #define MPRDRTRN_CR_IOTRK_CRDT_RTRN_IPC_IMPH_VC1_RD_THRESHOLD_MSK    (0x000000F0)
  #define MPRDRTRN_CR_IOTRK_CRDT_RTRN_IPC_IMPH_VC1_RD_THRESHOLD_MIN    (0)
  #define MPRDRTRN_CR_IOTRK_CRDT_RTRN_IPC_IMPH_VC1_RD_THRESHOLD_MAX    (15) // 0x0000000F
  #define MPRDRTRN_CR_IOTRK_CRDT_RTRN_IPC_IMPH_VC1_RD_THRESHOLD_DEF    (0x00000008)
  #define MPRDRTRN_CR_IOTRK_CRDT_RTRN_IPC_IMPH_VC1_RD_THRESHOLD_HSH    (0x04047600)

  #define MPRDRTRN_CR_IOTRK_CRDT_RTRN_IPC_IMPH_FIXED_RATE_EN_OFF       ( 8)
  #define MPRDRTRN_CR_IOTRK_CRDT_RTRN_IPC_IMPH_FIXED_RATE_EN_WID       ( 1)
  #define MPRDRTRN_CR_IOTRK_CRDT_RTRN_IPC_IMPH_FIXED_RATE_EN_MSK       (0x00000100)
  #define MPRDRTRN_CR_IOTRK_CRDT_RTRN_IPC_IMPH_FIXED_RATE_EN_MIN       (0)
  #define MPRDRTRN_CR_IOTRK_CRDT_RTRN_IPC_IMPH_FIXED_RATE_EN_MAX       (1) // 0x00000001
  #define MPRDRTRN_CR_IOTRK_CRDT_RTRN_IPC_IMPH_FIXED_RATE_EN_DEF       (0x00000000)
  #define MPRDRTRN_CR_IOTRK_CRDT_RTRN_IPC_IMPH_FIXED_RATE_EN_HSH       (0x01087600)

  #define MPRDRTRN_CR_IOTRK_CRDT_RTRN_IPC_IMPH_HIGH_PRIO_LIM_OFF       ( 9)
  #define MPRDRTRN_CR_IOTRK_CRDT_RTRN_IPC_IMPH_HIGH_PRIO_LIM_WID       ( 3)
  #define MPRDRTRN_CR_IOTRK_CRDT_RTRN_IPC_IMPH_HIGH_PRIO_LIM_MSK       (0x00000E00)
  #define MPRDRTRN_CR_IOTRK_CRDT_RTRN_IPC_IMPH_HIGH_PRIO_LIM_MIN       (0)
  #define MPRDRTRN_CR_IOTRK_CRDT_RTRN_IPC_IMPH_HIGH_PRIO_LIM_MAX       (7) // 0x00000007
  #define MPRDRTRN_CR_IOTRK_CRDT_RTRN_IPC_IMPH_HIGH_PRIO_LIM_DEF       (0x00000004)
  #define MPRDRTRN_CR_IOTRK_CRDT_RTRN_IPC_IMPH_HIGH_PRIO_LIM_HSH       (0x03097600)

  #define MPRDRTRN_CR_IOTRK_CRDT_RTRN_IPC_IMPH_LOW_PRIO_LIM_OFF        (12)
  #define MPRDRTRN_CR_IOTRK_CRDT_RTRN_IPC_IMPH_LOW_PRIO_LIM_WID        ( 3)
  #define MPRDRTRN_CR_IOTRK_CRDT_RTRN_IPC_IMPH_LOW_PRIO_LIM_MSK        (0x00007000)
  #define MPRDRTRN_CR_IOTRK_CRDT_RTRN_IPC_IMPH_LOW_PRIO_LIM_MIN        (0)
  #define MPRDRTRN_CR_IOTRK_CRDT_RTRN_IPC_IMPH_LOW_PRIO_LIM_MAX        (7) // 0x00000007
  #define MPRDRTRN_CR_IOTRK_CRDT_RTRN_IPC_IMPH_LOW_PRIO_LIM_DEF        (0x00000001)
  #define MPRDRTRN_CR_IOTRK_CRDT_RTRN_IPC_IMPH_LOW_PRIO_LIM_HSH        (0x030C7600)

  #define MPRDRTRN_CR_IOTRK_CRDT_RTRN_IPC_IMPH_SPARE_OFF               (15)
  #define MPRDRTRN_CR_IOTRK_CRDT_RTRN_IPC_IMPH_SPARE_WID               ( 1)
  #define MPRDRTRN_CR_IOTRK_CRDT_RTRN_IPC_IMPH_SPARE_MSK               (0x00008000)
  #define MPRDRTRN_CR_IOTRK_CRDT_RTRN_IPC_IMPH_SPARE_MIN               (0)
  #define MPRDRTRN_CR_IOTRK_CRDT_RTRN_IPC_IMPH_SPARE_MAX               (1) // 0x00000001
  #define MPRDRTRN_CR_IOTRK_CRDT_RTRN_IPC_IMPH_SPARE_DEF               (0x00000000)
  #define MPRDRTRN_CR_IOTRK_CRDT_RTRN_IPC_IMPH_SPARE_HSH               (0x010F7600)

#define MPRDRTRN_CR_XTM_UPSTREAM_ARB_IPC_IMPH_REG                      (0x00007604)

  #define MPRDRTRN_CR_XTM_UPSTREAM_ARB_IPC_IMPH_NON_VC1_THRESHOLD_OFF  ( 0)
  #define MPRDRTRN_CR_XTM_UPSTREAM_ARB_IPC_IMPH_NON_VC1_THRESHOLD_WID  ( 4)
  #define MPRDRTRN_CR_XTM_UPSTREAM_ARB_IPC_IMPH_NON_VC1_THRESHOLD_MSK  (0x0000000F)
  #define MPRDRTRN_CR_XTM_UPSTREAM_ARB_IPC_IMPH_NON_VC1_THRESHOLD_MIN  (0)
  #define MPRDRTRN_CR_XTM_UPSTREAM_ARB_IPC_IMPH_NON_VC1_THRESHOLD_MAX  (15) // 0x0000000F
  #define MPRDRTRN_CR_XTM_UPSTREAM_ARB_IPC_IMPH_NON_VC1_THRESHOLD_DEF  (0x00000008)
  #define MPRDRTRN_CR_XTM_UPSTREAM_ARB_IPC_IMPH_NON_VC1_THRESHOLD_HSH  (0x04007604)

  #define MPRDRTRN_CR_XTM_UPSTREAM_ARB_IPC_IMPH_VC1_RD_THRESHOLD_OFF   ( 4)
  #define MPRDRTRN_CR_XTM_UPSTREAM_ARB_IPC_IMPH_VC1_RD_THRESHOLD_WID   ( 4)
  #define MPRDRTRN_CR_XTM_UPSTREAM_ARB_IPC_IMPH_VC1_RD_THRESHOLD_MSK   (0x000000F0)
  #define MPRDRTRN_CR_XTM_UPSTREAM_ARB_IPC_IMPH_VC1_RD_THRESHOLD_MIN   (0)
  #define MPRDRTRN_CR_XTM_UPSTREAM_ARB_IPC_IMPH_VC1_RD_THRESHOLD_MAX   (15) // 0x0000000F
  #define MPRDRTRN_CR_XTM_UPSTREAM_ARB_IPC_IMPH_VC1_RD_THRESHOLD_DEF   (0x00000008)
  #define MPRDRTRN_CR_XTM_UPSTREAM_ARB_IPC_IMPH_VC1_RD_THRESHOLD_HSH   (0x04047604)

  #define MPRDRTRN_CR_XTM_UPSTREAM_ARB_IPC_IMPH_FIXED_RATE_EN_OFF      ( 8)
  #define MPRDRTRN_CR_XTM_UPSTREAM_ARB_IPC_IMPH_FIXED_RATE_EN_WID      ( 1)
  #define MPRDRTRN_CR_XTM_UPSTREAM_ARB_IPC_IMPH_FIXED_RATE_EN_MSK      (0x00000100)
  #define MPRDRTRN_CR_XTM_UPSTREAM_ARB_IPC_IMPH_FIXED_RATE_EN_MIN      (0)
  #define MPRDRTRN_CR_XTM_UPSTREAM_ARB_IPC_IMPH_FIXED_RATE_EN_MAX      (1) // 0x00000001
  #define MPRDRTRN_CR_XTM_UPSTREAM_ARB_IPC_IMPH_FIXED_RATE_EN_DEF      (0x00000000)
  #define MPRDRTRN_CR_XTM_UPSTREAM_ARB_IPC_IMPH_FIXED_RATE_EN_HSH      (0x01087604)

  #define MPRDRTRN_CR_XTM_UPSTREAM_ARB_IPC_IMPH_HIGH_PRIO_LIM_OFF      ( 9)
  #define MPRDRTRN_CR_XTM_UPSTREAM_ARB_IPC_IMPH_HIGH_PRIO_LIM_WID      ( 3)
  #define MPRDRTRN_CR_XTM_UPSTREAM_ARB_IPC_IMPH_HIGH_PRIO_LIM_MSK      (0x00000E00)
  #define MPRDRTRN_CR_XTM_UPSTREAM_ARB_IPC_IMPH_HIGH_PRIO_LIM_MIN      (0)
  #define MPRDRTRN_CR_XTM_UPSTREAM_ARB_IPC_IMPH_HIGH_PRIO_LIM_MAX      (7) // 0x00000007
  #define MPRDRTRN_CR_XTM_UPSTREAM_ARB_IPC_IMPH_HIGH_PRIO_LIM_DEF      (0x00000004)
  #define MPRDRTRN_CR_XTM_UPSTREAM_ARB_IPC_IMPH_HIGH_PRIO_LIM_HSH      (0x03097604)

  #define MPRDRTRN_CR_XTM_UPSTREAM_ARB_IPC_IMPH_LOW_PRIO_LIM_OFF       (12)
  #define MPRDRTRN_CR_XTM_UPSTREAM_ARB_IPC_IMPH_LOW_PRIO_LIM_WID       ( 3)
  #define MPRDRTRN_CR_XTM_UPSTREAM_ARB_IPC_IMPH_LOW_PRIO_LIM_MSK       (0x00007000)
  #define MPRDRTRN_CR_XTM_UPSTREAM_ARB_IPC_IMPH_LOW_PRIO_LIM_MIN       (0)
  #define MPRDRTRN_CR_XTM_UPSTREAM_ARB_IPC_IMPH_LOW_PRIO_LIM_MAX       (7) // 0x00000007
  #define MPRDRTRN_CR_XTM_UPSTREAM_ARB_IPC_IMPH_LOW_PRIO_LIM_DEF       (0x00000001)
  #define MPRDRTRN_CR_XTM_UPSTREAM_ARB_IPC_IMPH_LOW_PRIO_LIM_HSH       (0x030C7604)

  #define MPRDRTRN_CR_XTM_UPSTREAM_ARB_IPC_IMPH_SPARE_OFF              (15)
  #define MPRDRTRN_CR_XTM_UPSTREAM_ARB_IPC_IMPH_SPARE_WID              ( 1)
  #define MPRDRTRN_CR_XTM_UPSTREAM_ARB_IPC_IMPH_SPARE_MSK              (0x00008000)
  #define MPRDRTRN_CR_XTM_UPSTREAM_ARB_IPC_IMPH_SPARE_MIN              (0)
  #define MPRDRTRN_CR_XTM_UPSTREAM_ARB_IPC_IMPH_SPARE_MAX              (1) // 0x00000001
  #define MPRDRTRN_CR_XTM_UPSTREAM_ARB_IPC_IMPH_SPARE_DEF              (0x00000000)
  #define MPRDRTRN_CR_XTM_UPSTREAM_ARB_IPC_IMPH_SPARE_HSH              (0x010F7604)

#define MPRDRTRN_CR_XTM_DOWNSTREAM_ARB_IPC_IMPH_REG                    (0x00007608)

  #define MPRDRTRN_CR_XTM_DOWNSTREAM_ARB_IPC_IMPH_NON_VC1_THRESHOLD_OFF ( 0)
  #define MPRDRTRN_CR_XTM_DOWNSTREAM_ARB_IPC_IMPH_NON_VC1_THRESHOLD_WID ( 4)
  #define MPRDRTRN_CR_XTM_DOWNSTREAM_ARB_IPC_IMPH_NON_VC1_THRESHOLD_MSK (0x0000000F)
  #define MPRDRTRN_CR_XTM_DOWNSTREAM_ARB_IPC_IMPH_NON_VC1_THRESHOLD_MIN (0)
  #define MPRDRTRN_CR_XTM_DOWNSTREAM_ARB_IPC_IMPH_NON_VC1_THRESHOLD_MAX (15) // 0x0000000F
  #define MPRDRTRN_CR_XTM_DOWNSTREAM_ARB_IPC_IMPH_NON_VC1_THRESHOLD_DEF (0x00000008)
  #define MPRDRTRN_CR_XTM_DOWNSTREAM_ARB_IPC_IMPH_NON_VC1_THRESHOLD_HSH (0x04007608)

  #define MPRDRTRN_CR_XTM_DOWNSTREAM_ARB_IPC_IMPH_VC1_RD_THRESHOLD_OFF ( 4)
  #define MPRDRTRN_CR_XTM_DOWNSTREAM_ARB_IPC_IMPH_VC1_RD_THRESHOLD_WID ( 4)
  #define MPRDRTRN_CR_XTM_DOWNSTREAM_ARB_IPC_IMPH_VC1_RD_THRESHOLD_MSK (0x000000F0)
  #define MPRDRTRN_CR_XTM_DOWNSTREAM_ARB_IPC_IMPH_VC1_RD_THRESHOLD_MIN (0)
  #define MPRDRTRN_CR_XTM_DOWNSTREAM_ARB_IPC_IMPH_VC1_RD_THRESHOLD_MAX (15) // 0x0000000F
  #define MPRDRTRN_CR_XTM_DOWNSTREAM_ARB_IPC_IMPH_VC1_RD_THRESHOLD_DEF (0x00000008)
  #define MPRDRTRN_CR_XTM_DOWNSTREAM_ARB_IPC_IMPH_VC1_RD_THRESHOLD_HSH (0x04047608)

  #define MPRDRTRN_CR_XTM_DOWNSTREAM_ARB_IPC_IMPH_FIXED_RATE_EN_OFF    ( 8)
  #define MPRDRTRN_CR_XTM_DOWNSTREAM_ARB_IPC_IMPH_FIXED_RATE_EN_WID    ( 1)
  #define MPRDRTRN_CR_XTM_DOWNSTREAM_ARB_IPC_IMPH_FIXED_RATE_EN_MSK    (0x00000100)
  #define MPRDRTRN_CR_XTM_DOWNSTREAM_ARB_IPC_IMPH_FIXED_RATE_EN_MIN    (0)
  #define MPRDRTRN_CR_XTM_DOWNSTREAM_ARB_IPC_IMPH_FIXED_RATE_EN_MAX    (1) // 0x00000001
  #define MPRDRTRN_CR_XTM_DOWNSTREAM_ARB_IPC_IMPH_FIXED_RATE_EN_DEF    (0x00000000)
  #define MPRDRTRN_CR_XTM_DOWNSTREAM_ARB_IPC_IMPH_FIXED_RATE_EN_HSH    (0x01087608)

  #define MPRDRTRN_CR_XTM_DOWNSTREAM_ARB_IPC_IMPH_HIGH_PRIO_LIM_OFF    ( 9)
  #define MPRDRTRN_CR_XTM_DOWNSTREAM_ARB_IPC_IMPH_HIGH_PRIO_LIM_WID    ( 3)
  #define MPRDRTRN_CR_XTM_DOWNSTREAM_ARB_IPC_IMPH_HIGH_PRIO_LIM_MSK    (0x00000E00)
  #define MPRDRTRN_CR_XTM_DOWNSTREAM_ARB_IPC_IMPH_HIGH_PRIO_LIM_MIN    (0)
  #define MPRDRTRN_CR_XTM_DOWNSTREAM_ARB_IPC_IMPH_HIGH_PRIO_LIM_MAX    (7) // 0x00000007
  #define MPRDRTRN_CR_XTM_DOWNSTREAM_ARB_IPC_IMPH_HIGH_PRIO_LIM_DEF    (0x00000004)
  #define MPRDRTRN_CR_XTM_DOWNSTREAM_ARB_IPC_IMPH_HIGH_PRIO_LIM_HSH    (0x03097608)

  #define MPRDRTRN_CR_XTM_DOWNSTREAM_ARB_IPC_IMPH_LOW_PRIO_LIM_OFF     (12)
  #define MPRDRTRN_CR_XTM_DOWNSTREAM_ARB_IPC_IMPH_LOW_PRIO_LIM_WID     ( 3)
  #define MPRDRTRN_CR_XTM_DOWNSTREAM_ARB_IPC_IMPH_LOW_PRIO_LIM_MSK     (0x00007000)
  #define MPRDRTRN_CR_XTM_DOWNSTREAM_ARB_IPC_IMPH_LOW_PRIO_LIM_MIN     (0)
  #define MPRDRTRN_CR_XTM_DOWNSTREAM_ARB_IPC_IMPH_LOW_PRIO_LIM_MAX     (7) // 0x00000007
  #define MPRDRTRN_CR_XTM_DOWNSTREAM_ARB_IPC_IMPH_LOW_PRIO_LIM_DEF     (0x00000001)
  #define MPRDRTRN_CR_XTM_DOWNSTREAM_ARB_IPC_IMPH_LOW_PRIO_LIM_HSH     (0x030C7608)

  #define MPRDRTRN_CR_XTM_DOWNSTREAM_ARB_IPC_IMPH_SPARE_OFF            (15)
  #define MPRDRTRN_CR_XTM_DOWNSTREAM_ARB_IPC_IMPH_SPARE_WID            ( 1)
  #define MPRDRTRN_CR_XTM_DOWNSTREAM_ARB_IPC_IMPH_SPARE_MSK            (0x00008000)
  #define MPRDRTRN_CR_XTM_DOWNSTREAM_ARB_IPC_IMPH_SPARE_MIN            (0)
  #define MPRDRTRN_CR_XTM_DOWNSTREAM_ARB_IPC_IMPH_SPARE_MAX            (1) // 0x00000001
  #define MPRDRTRN_CR_XTM_DOWNSTREAM_ARB_IPC_IMPH_SPARE_DEF            (0x00000000)
  #define MPRDRTRN_CR_XTM_DOWNSTREAM_ARB_IPC_IMPH_SPARE_HSH            (0x010F7608)

#define MPRDRTRN_CR_CRDTLCK_IMPH_REG                                   (0x000077FC)

  #define MPRDRTRN_CR_CRDTLCK_IMPH_LOCK_OFF                            ( 0)
  #define MPRDRTRN_CR_CRDTLCK_IMPH_LOCK_WID                            ( 1)
  #define MPRDRTRN_CR_CRDTLCK_IMPH_LOCK_MSK                            (0x00000001)
  #define MPRDRTRN_CR_CRDTLCK_IMPH_LOCK_MIN                            (0)
  #define MPRDRTRN_CR_CRDTLCK_IMPH_LOCK_MAX                            (1) // 0x00000001
  #define MPRDRTRN_CR_CRDTLCK_IMPH_LOCK_DEF                            (0x00000000)
  #define MPRDRTRN_CR_CRDTLCK_IMPH_LOCK_HSH                            (0x010077FC)

#define MPMCARB_CR_VCLIM0_IMPH_REG                                     (0x00007800)

  #define MPMCARB_CR_VCLIM0_IMPH_VCPNPLIM_OFF                          ( 0)
  #define MPMCARB_CR_VCLIM0_IMPH_VCPNPLIM_WID                          ( 3)
  #define MPMCARB_CR_VCLIM0_IMPH_VCPNPLIM_MSK                          (0x00000007)
  #define MPMCARB_CR_VCLIM0_IMPH_VCPNPLIM_MIN                          (0)
  #define MPMCARB_CR_VCLIM0_IMPH_VCPNPLIM_MAX                          (7) // 0x00000007
  #define MPMCARB_CR_VCLIM0_IMPH_VCPNPLIM_DEF                          (0x00000004)
  #define MPMCARB_CR_VCLIM0_IMPH_VCPNPLIM_HSH                          (0x03007800)

  #define MPMCARB_CR_VCLIM0_IMPH_VCPPLIM_OFF                           ( 4)
  #define MPMCARB_CR_VCLIM0_IMPH_VCPPLIM_WID                           ( 3)
  #define MPMCARB_CR_VCLIM0_IMPH_VCPPLIM_MSK                           (0x00000070)
  #define MPMCARB_CR_VCLIM0_IMPH_VCPPLIM_MIN                           (0)
  #define MPMCARB_CR_VCLIM0_IMPH_VCPPLIM_MAX                           (7) // 0x00000007
  #define MPMCARB_CR_VCLIM0_IMPH_VCPPLIM_DEF                           (0x00000004)
  #define MPMCARB_CR_VCLIM0_IMPH_VCPPLIM_HSH                           (0x03047800)

  #define MPMCARB_CR_VCLIM0_IMPH_VCMNPLIM_OFF                          ( 8)
  #define MPMCARB_CR_VCLIM0_IMPH_VCMNPLIM_WID                          ( 3)
  #define MPMCARB_CR_VCLIM0_IMPH_VCMNPLIM_MSK                          (0x00000700)
  #define MPMCARB_CR_VCLIM0_IMPH_VCMNPLIM_MIN                          (0)
  #define MPMCARB_CR_VCLIM0_IMPH_VCMNPLIM_MAX                          (7) // 0x00000007
  #define MPMCARB_CR_VCLIM0_IMPH_VCMNPLIM_DEF                          (0x00000004)
  #define MPMCARB_CR_VCLIM0_IMPH_VCMNPLIM_HSH                          (0x03087800)

  #define MPMCARB_CR_VCLIM0_IMPH_VCMPLIM_OFF                           (12)
  #define MPMCARB_CR_VCLIM0_IMPH_VCMPLIM_WID                           ( 3)
  #define MPMCARB_CR_VCLIM0_IMPH_VCMPLIM_MSK                           (0x00007000)
  #define MPMCARB_CR_VCLIM0_IMPH_VCMPLIM_MIN                           (0)
  #define MPMCARB_CR_VCLIM0_IMPH_VCMPLIM_MAX                           (7) // 0x00000007
  #define MPMCARB_CR_VCLIM0_IMPH_VCMPLIM_DEF                           (0x00000004)
  #define MPMCARB_CR_VCLIM0_IMPH_VCMPLIM_HSH                           (0x030C7800)

  #define MPMCARB_CR_VCLIM0_IMPH_VC0VTDLIM_OFF                         (16)
  #define MPMCARB_CR_VCLIM0_IMPH_VC0VTDLIM_WID                         ( 3)
  #define MPMCARB_CR_VCLIM0_IMPH_VC0VTDLIM_MSK                         (0x00070000)
  #define MPMCARB_CR_VCLIM0_IMPH_VC0VTDLIM_MIN                         (0)
  #define MPMCARB_CR_VCLIM0_IMPH_VC0VTDLIM_MAX                         (7) // 0x00000007
  #define MPMCARB_CR_VCLIM0_IMPH_VC0VTDLIM_DEF                         (0x00000004)
  #define MPMCARB_CR_VCLIM0_IMPH_VC0VTDLIM_HSH                         (0x03107800)

  #define MPMCARB_CR_VCLIM0_IMPH_VCPVTDLIM_OFF                         (20)
  #define MPMCARB_CR_VCLIM0_IMPH_VCPVTDLIM_WID                         ( 3)
  #define MPMCARB_CR_VCLIM0_IMPH_VCPVTDLIM_MSK                         (0x00700000)
  #define MPMCARB_CR_VCLIM0_IMPH_VCPVTDLIM_MIN                         (0)
  #define MPMCARB_CR_VCLIM0_IMPH_VCPVTDLIM_MAX                         (7) // 0x00000007
  #define MPMCARB_CR_VCLIM0_IMPH_VCPVTDLIM_DEF                         (0x00000004)
  #define MPMCARB_CR_VCLIM0_IMPH_VCPVTDLIM_HSH                         (0x03147800)

#define MPMCARB_CR_VCLIM1_IMPH_REG                                     (0x00007804)

  #define MPMCARB_CR_VCLIM1_IMPH_VTDL3_OFF                             ( 8)
  #define MPMCARB_CR_VCLIM1_IMPH_VTDL3_WID                             ( 3)
  #define MPMCARB_CR_VCLIM1_IMPH_VTDL3_MSK                             (0x00000700)
  #define MPMCARB_CR_VCLIM1_IMPH_VTDL3_MIN                             (0)
  #define MPMCARB_CR_VCLIM1_IMPH_VTDL3_MAX                             (7) // 0x00000007
  #define MPMCARB_CR_VCLIM1_IMPH_VTDL3_DEF                             (0x00000004)
  #define MPMCARB_CR_VCLIM1_IMPH_VTDL3_HSH                             (0x03087804)

  #define MPMCARB_CR_VCLIM1_IMPH_VTDNL3_OFF                            (12)
  #define MPMCARB_CR_VCLIM1_IMPH_VTDNL3_WID                            ( 3)
  #define MPMCARB_CR_VCLIM1_IMPH_VTDNL3_MSK                            (0x00007000)
  #define MPMCARB_CR_VCLIM1_IMPH_VTDNL3_MIN                            (0)
  #define MPMCARB_CR_VCLIM1_IMPH_VTDNL3_MAX                            (7) // 0x00000007
  #define MPMCARB_CR_VCLIM1_IMPH_VTDNL3_DEF                            (0x00000004)
  #define MPMCARB_CR_VCLIM1_IMPH_VTDNL3_HSH                            (0x030C7804)

#define MPMCARB_CR_XTM_NTR_REQ_LIM_IMPH_REG                            (0x00007808)

  #define MPMCARB_CR_XTM_NTR_REQ_LIM_IMPH_XTM_VC0_RD_OFF               ( 0)
  #define MPMCARB_CR_XTM_NTR_REQ_LIM_IMPH_XTM_VC0_RD_WID               ( 3)
  #define MPMCARB_CR_XTM_NTR_REQ_LIM_IMPH_XTM_VC0_RD_MSK               (0x00000007)
  #define MPMCARB_CR_XTM_NTR_REQ_LIM_IMPH_XTM_VC0_RD_MIN               (0)
  #define MPMCARB_CR_XTM_NTR_REQ_LIM_IMPH_XTM_VC0_RD_MAX               (7) // 0x00000007
  #define MPMCARB_CR_XTM_NTR_REQ_LIM_IMPH_XTM_VC0_RD_DEF               (0x00000004)
  #define MPMCARB_CR_XTM_NTR_REQ_LIM_IMPH_XTM_VC0_RD_HSH               (0x03007808)

  #define MPMCARB_CR_XTM_NTR_REQ_LIM_IMPH_XTM_VC0_WR_OFF               ( 4)
  #define MPMCARB_CR_XTM_NTR_REQ_LIM_IMPH_XTM_VC0_WR_WID               ( 3)
  #define MPMCARB_CR_XTM_NTR_REQ_LIM_IMPH_XTM_VC0_WR_MSK               (0x00000070)
  #define MPMCARB_CR_XTM_NTR_REQ_LIM_IMPH_XTM_VC0_WR_MIN               (0)
  #define MPMCARB_CR_XTM_NTR_REQ_LIM_IMPH_XTM_VC0_WR_MAX               (7) // 0x00000007
  #define MPMCARB_CR_XTM_NTR_REQ_LIM_IMPH_XTM_VC0_WR_DEF               (0x00000004)
  #define MPMCARB_CR_XTM_NTR_REQ_LIM_IMPH_XTM_VC0_WR_HSH               (0x03047808)

  #define MPMCARB_CR_XTM_NTR_REQ_LIM_IMPH_NTR_VC0_RD_OFF               ( 8)
  #define MPMCARB_CR_XTM_NTR_REQ_LIM_IMPH_NTR_VC0_RD_WID               ( 3)
  #define MPMCARB_CR_XTM_NTR_REQ_LIM_IMPH_NTR_VC0_RD_MSK               (0x00000700)
  #define MPMCARB_CR_XTM_NTR_REQ_LIM_IMPH_NTR_VC0_RD_MIN               (0)
  #define MPMCARB_CR_XTM_NTR_REQ_LIM_IMPH_NTR_VC0_RD_MAX               (7) // 0x00000007
  #define MPMCARB_CR_XTM_NTR_REQ_LIM_IMPH_NTR_VC0_RD_DEF               (0x00000004)
  #define MPMCARB_CR_XTM_NTR_REQ_LIM_IMPH_NTR_VC0_RD_HSH               (0x03087808)

  #define MPMCARB_CR_XTM_NTR_REQ_LIM_IMPH_NTR_VC0_WR_OFF               (12)
  #define MPMCARB_CR_XTM_NTR_REQ_LIM_IMPH_NTR_VC0_WR_WID               ( 3)
  #define MPMCARB_CR_XTM_NTR_REQ_LIM_IMPH_NTR_VC0_WR_MSK               (0x00007000)
  #define MPMCARB_CR_XTM_NTR_REQ_LIM_IMPH_NTR_VC0_WR_MIN               (0)
  #define MPMCARB_CR_XTM_NTR_REQ_LIM_IMPH_NTR_VC0_WR_MAX               (7) // 0x00000007
  #define MPMCARB_CR_XTM_NTR_REQ_LIM_IMPH_NTR_VC0_WR_DEF               (0x00000004)
  #define MPMCARB_CR_XTM_NTR_REQ_LIM_IMPH_NTR_VC0_WR_HSH               (0x030C7808)

#define MPMCARB_CR_RCH_REQ_ARB_MC_MEE_LIM_IMPH_REG                     (0x0000780C)

  #define MPMCARB_CR_RCH_REQ_ARB_MC_MEE_LIM_IMPH_XTM_VC0_RD_OFF        ( 0)
  #define MPMCARB_CR_RCH_REQ_ARB_MC_MEE_LIM_IMPH_XTM_VC0_RD_WID        ( 3)
  #define MPMCARB_CR_RCH_REQ_ARB_MC_MEE_LIM_IMPH_XTM_VC0_RD_MSK        (0x00000007)
  #define MPMCARB_CR_RCH_REQ_ARB_MC_MEE_LIM_IMPH_XTM_VC0_RD_MIN        (0)
  #define MPMCARB_CR_RCH_REQ_ARB_MC_MEE_LIM_IMPH_XTM_VC0_RD_MAX        (7) // 0x00000007
  #define MPMCARB_CR_RCH_REQ_ARB_MC_MEE_LIM_IMPH_XTM_VC0_RD_DEF        (0x00000004)
  #define MPMCARB_CR_RCH_REQ_ARB_MC_MEE_LIM_IMPH_XTM_VC0_RD_HSH        (0x0300780C)

  #define MPMCARB_CR_RCH_REQ_ARB_MC_MEE_LIM_IMPH_XTM_VC0_WR_OFF        ( 4)
  #define MPMCARB_CR_RCH_REQ_ARB_MC_MEE_LIM_IMPH_XTM_VC0_WR_WID        ( 3)
  #define MPMCARB_CR_RCH_REQ_ARB_MC_MEE_LIM_IMPH_XTM_VC0_WR_MSK        (0x00000070)
  #define MPMCARB_CR_RCH_REQ_ARB_MC_MEE_LIM_IMPH_XTM_VC0_WR_MIN        (0)
  #define MPMCARB_CR_RCH_REQ_ARB_MC_MEE_LIM_IMPH_XTM_VC0_WR_MAX        (7) // 0x00000007
  #define MPMCARB_CR_RCH_REQ_ARB_MC_MEE_LIM_IMPH_XTM_VC0_WR_DEF        (0x00000004)
  #define MPMCARB_CR_RCH_REQ_ARB_MC_MEE_LIM_IMPH_XTM_VC0_WR_HSH        (0x0304780C)

  #define MPMCARB_CR_RCH_REQ_ARB_MC_MEE_LIM_IMPH_NTR_VC0_RD_OFF        ( 8)
  #define MPMCARB_CR_RCH_REQ_ARB_MC_MEE_LIM_IMPH_NTR_VC0_RD_WID        ( 3)
  #define MPMCARB_CR_RCH_REQ_ARB_MC_MEE_LIM_IMPH_NTR_VC0_RD_MSK        (0x00000700)
  #define MPMCARB_CR_RCH_REQ_ARB_MC_MEE_LIM_IMPH_NTR_VC0_RD_MIN        (0)
  #define MPMCARB_CR_RCH_REQ_ARB_MC_MEE_LIM_IMPH_NTR_VC0_RD_MAX        (7) // 0x00000007
  #define MPMCARB_CR_RCH_REQ_ARB_MC_MEE_LIM_IMPH_NTR_VC0_RD_DEF        (0x00000004)
  #define MPMCARB_CR_RCH_REQ_ARB_MC_MEE_LIM_IMPH_NTR_VC0_RD_HSH        (0x0308780C)

  #define MPMCARB_CR_RCH_REQ_ARB_MC_MEE_LIM_IMPH_NTR_VC0_WR_OFF        (12)
  #define MPMCARB_CR_RCH_REQ_ARB_MC_MEE_LIM_IMPH_NTR_VC0_WR_WID        ( 3)
  #define MPMCARB_CR_RCH_REQ_ARB_MC_MEE_LIM_IMPH_NTR_VC0_WR_MSK        (0x00007000)
  #define MPMCARB_CR_RCH_REQ_ARB_MC_MEE_LIM_IMPH_NTR_VC0_WR_MIN        (0)
  #define MPMCARB_CR_RCH_REQ_ARB_MC_MEE_LIM_IMPH_NTR_VC0_WR_MAX        (7) // 0x00000007
  #define MPMCARB_CR_RCH_REQ_ARB_MC_MEE_LIM_IMPH_NTR_VC0_WR_DEF        (0x00000004)
  #define MPMCARB_CR_RCH_REQ_ARB_MC_MEE_LIM_IMPH_NTR_VC0_WR_HSH        (0x030C780C)

  #define MPMCARB_CR_RCH_REQ_ARB_MC_MEE_LIM_IMPH_MEE_VC0_RD_OFF        (16)
  #define MPMCARB_CR_RCH_REQ_ARB_MC_MEE_LIM_IMPH_MEE_VC0_RD_WID        ( 3)
  #define MPMCARB_CR_RCH_REQ_ARB_MC_MEE_LIM_IMPH_MEE_VC0_RD_MSK        (0x00070000)
  #define MPMCARB_CR_RCH_REQ_ARB_MC_MEE_LIM_IMPH_MEE_VC0_RD_MIN        (0)
  #define MPMCARB_CR_RCH_REQ_ARB_MC_MEE_LIM_IMPH_MEE_VC0_RD_MAX        (7) // 0x00000007
  #define MPMCARB_CR_RCH_REQ_ARB_MC_MEE_LIM_IMPH_MEE_VC0_RD_DEF        (0x00000004)
  #define MPMCARB_CR_RCH_REQ_ARB_MC_MEE_LIM_IMPH_MEE_VC0_RD_HSH        (0x0310780C)

  #define MPMCARB_CR_RCH_REQ_ARB_MC_MEE_LIM_IMPH_MEE_VC0_WR_OFF        (20)
  #define MPMCARB_CR_RCH_REQ_ARB_MC_MEE_LIM_IMPH_MEE_VC0_WR_WID        ( 3)
  #define MPMCARB_CR_RCH_REQ_ARB_MC_MEE_LIM_IMPH_MEE_VC0_WR_MSK        (0x00700000)
  #define MPMCARB_CR_RCH_REQ_ARB_MC_MEE_LIM_IMPH_MEE_VC0_WR_MIN        (0)
  #define MPMCARB_CR_RCH_REQ_ARB_MC_MEE_LIM_IMPH_MEE_VC0_WR_MAX        (7) // 0x00000007
  #define MPMCARB_CR_RCH_REQ_ARB_MC_MEE_LIM_IMPH_MEE_VC0_WR_DEF        (0x00000004)
  #define MPMCARB_CR_RCH_REQ_ARB_MC_MEE_LIM_IMPH_MEE_VC0_WR_HSH        (0x0314780C)

  #define MPMCARB_CR_RCH_REQ_ARB_MC_MEE_LIM_IMPH_EFLOW_VC0_RD_OFF      (24)
  #define MPMCARB_CR_RCH_REQ_ARB_MC_MEE_LIM_IMPH_EFLOW_VC0_RD_WID      ( 3)
  #define MPMCARB_CR_RCH_REQ_ARB_MC_MEE_LIM_IMPH_EFLOW_VC0_RD_MSK      (0x07000000)
  #define MPMCARB_CR_RCH_REQ_ARB_MC_MEE_LIM_IMPH_EFLOW_VC0_RD_MIN      (0)
  #define MPMCARB_CR_RCH_REQ_ARB_MC_MEE_LIM_IMPH_EFLOW_VC0_RD_MAX      (7) // 0x00000007
  #define MPMCARB_CR_RCH_REQ_ARB_MC_MEE_LIM_IMPH_EFLOW_VC0_RD_DEF      (0x00000004)
  #define MPMCARB_CR_RCH_REQ_ARB_MC_MEE_LIM_IMPH_EFLOW_VC0_RD_HSH      (0x0318780C)

  #define MPMCARB_CR_RCH_REQ_ARB_MC_MEE_LIM_IMPH_EFLOW_VC0_WR_OFF      (28)
  #define MPMCARB_CR_RCH_REQ_ARB_MC_MEE_LIM_IMPH_EFLOW_VC0_WR_WID      ( 3)
  #define MPMCARB_CR_RCH_REQ_ARB_MC_MEE_LIM_IMPH_EFLOW_VC0_WR_MSK      (0x70000000)
  #define MPMCARB_CR_RCH_REQ_ARB_MC_MEE_LIM_IMPH_EFLOW_VC0_WR_MIN      (0)
  #define MPMCARB_CR_RCH_REQ_ARB_MC_MEE_LIM_IMPH_EFLOW_VC0_WR_MAX      (7) // 0x00000007
  #define MPMCARB_CR_RCH_REQ_ARB_MC_MEE_LIM_IMPH_EFLOW_VC0_WR_DEF      (0x00000004)
  #define MPMCARB_CR_RCH_REQ_ARB_MC_MEE_LIM_IMPH_EFLOW_VC0_WR_HSH      (0x031C780C)

#define MPMCARB_CR_RCH_REQ_ARB_EFLOW_LIM_IMPH_REG                      (0x00007810)

  #define MPMCARB_CR_RCH_REQ_ARB_EFLOW_LIM_IMPH_XTM_VC0_RD_OFF         ( 0)
  #define MPMCARB_CR_RCH_REQ_ARB_EFLOW_LIM_IMPH_XTM_VC0_RD_WID         ( 3)
  #define MPMCARB_CR_RCH_REQ_ARB_EFLOW_LIM_IMPH_XTM_VC0_RD_MSK         (0x00000007)
  #define MPMCARB_CR_RCH_REQ_ARB_EFLOW_LIM_IMPH_XTM_VC0_RD_MIN         (0)
  #define MPMCARB_CR_RCH_REQ_ARB_EFLOW_LIM_IMPH_XTM_VC0_RD_MAX         (7) // 0x00000007
  #define MPMCARB_CR_RCH_REQ_ARB_EFLOW_LIM_IMPH_XTM_VC0_RD_DEF         (0x00000004)
  #define MPMCARB_CR_RCH_REQ_ARB_EFLOW_LIM_IMPH_XTM_VC0_RD_HSH         (0x03007810)

  #define MPMCARB_CR_RCH_REQ_ARB_EFLOW_LIM_IMPH_XTM_VC0_WR_OFF         ( 4)
  #define MPMCARB_CR_RCH_REQ_ARB_EFLOW_LIM_IMPH_XTM_VC0_WR_WID         ( 3)
  #define MPMCARB_CR_RCH_REQ_ARB_EFLOW_LIM_IMPH_XTM_VC0_WR_MSK         (0x00000070)
  #define MPMCARB_CR_RCH_REQ_ARB_EFLOW_LIM_IMPH_XTM_VC0_WR_MIN         (0)
  #define MPMCARB_CR_RCH_REQ_ARB_EFLOW_LIM_IMPH_XTM_VC0_WR_MAX         (7) // 0x00000007
  #define MPMCARB_CR_RCH_REQ_ARB_EFLOW_LIM_IMPH_XTM_VC0_WR_DEF         (0x00000004)
  #define MPMCARB_CR_RCH_REQ_ARB_EFLOW_LIM_IMPH_XTM_VC0_WR_HSH         (0x03047810)

  #define MPMCARB_CR_RCH_REQ_ARB_EFLOW_LIM_IMPH_NTR_VC0_RD_OFF         ( 8)
  #define MPMCARB_CR_RCH_REQ_ARB_EFLOW_LIM_IMPH_NTR_VC0_RD_WID         ( 3)
  #define MPMCARB_CR_RCH_REQ_ARB_EFLOW_LIM_IMPH_NTR_VC0_RD_MSK         (0x00000700)
  #define MPMCARB_CR_RCH_REQ_ARB_EFLOW_LIM_IMPH_NTR_VC0_RD_MIN         (0)
  #define MPMCARB_CR_RCH_REQ_ARB_EFLOW_LIM_IMPH_NTR_VC0_RD_MAX         (7) // 0x00000007
  #define MPMCARB_CR_RCH_REQ_ARB_EFLOW_LIM_IMPH_NTR_VC0_RD_DEF         (0x00000004)
  #define MPMCARB_CR_RCH_REQ_ARB_EFLOW_LIM_IMPH_NTR_VC0_RD_HSH         (0x03087810)

  #define MPMCARB_CR_RCH_REQ_ARB_EFLOW_LIM_IMPH_NTR_VC0_WR_OFF         (12)
  #define MPMCARB_CR_RCH_REQ_ARB_EFLOW_LIM_IMPH_NTR_VC0_WR_WID         ( 3)
  #define MPMCARB_CR_RCH_REQ_ARB_EFLOW_LIM_IMPH_NTR_VC0_WR_MSK         (0x00007000)
  #define MPMCARB_CR_RCH_REQ_ARB_EFLOW_LIM_IMPH_NTR_VC0_WR_MIN         (0)
  #define MPMCARB_CR_RCH_REQ_ARB_EFLOW_LIM_IMPH_NTR_VC0_WR_MAX         (7) // 0x00000007
  #define MPMCARB_CR_RCH_REQ_ARB_EFLOW_LIM_IMPH_NTR_VC0_WR_DEF         (0x00000004)
  #define MPMCARB_CR_RCH_REQ_ARB_EFLOW_LIM_IMPH_NTR_VC0_WR_HSH         (0x030C7810)

  #define MPMCARB_CR_RCH_REQ_ARB_EFLOW_LIM_IMPH_PARALLEL_UNBLOCK_OFF   (30)
  #define MPMCARB_CR_RCH_REQ_ARB_EFLOW_LIM_IMPH_PARALLEL_UNBLOCK_WID   ( 1)
  #define MPMCARB_CR_RCH_REQ_ARB_EFLOW_LIM_IMPH_PARALLEL_UNBLOCK_MSK   (0x40000000)
  #define MPMCARB_CR_RCH_REQ_ARB_EFLOW_LIM_IMPH_PARALLEL_UNBLOCK_MIN   (0)
  #define MPMCARB_CR_RCH_REQ_ARB_EFLOW_LIM_IMPH_PARALLEL_UNBLOCK_MAX   (1) // 0x00000001
  #define MPMCARB_CR_RCH_REQ_ARB_EFLOW_LIM_IMPH_PARALLEL_UNBLOCK_DEF   (0x00000001)
  #define MPMCARB_CR_RCH_REQ_ARB_EFLOW_LIM_IMPH_PARALLEL_UNBLOCK_HSH   (0x011E7810)

  #define MPMCARB_CR_RCH_REQ_ARB_EFLOW_LIM_IMPH_EFLOW_ENABLED_OFF      (31)
  #define MPMCARB_CR_RCH_REQ_ARB_EFLOW_LIM_IMPH_EFLOW_ENABLED_WID      ( 1)
  #define MPMCARB_CR_RCH_REQ_ARB_EFLOW_LIM_IMPH_EFLOW_ENABLED_MSK      (0x80000000)
  #define MPMCARB_CR_RCH_REQ_ARB_EFLOW_LIM_IMPH_EFLOW_ENABLED_MIN      (0)
  #define MPMCARB_CR_RCH_REQ_ARB_EFLOW_LIM_IMPH_EFLOW_ENABLED_MAX      (1) // 0x00000001
  #define MPMCARB_CR_RCH_REQ_ARB_EFLOW_LIM_IMPH_EFLOW_ENABLED_DEF      (0x00000000)
  #define MPMCARB_CR_RCH_REQ_ARB_EFLOW_LIM_IMPH_EFLOW_ENABLED_HSH      (0x011F7810)

#define MPMCARB_CR_RCH_RD_CMP_ARB_NTR_XTM_LIM_IMPH_REG                 (0x00007814)

  #define MPMCARB_CR_RCH_RD_CMP_ARB_NTR_XTM_LIM_IMPH_MC_VC0_RD_CMP_OFF ( 0)
  #define MPMCARB_CR_RCH_RD_CMP_ARB_NTR_XTM_LIM_IMPH_MC_VC0_RD_CMP_WID ( 3)
  #define MPMCARB_CR_RCH_RD_CMP_ARB_NTR_XTM_LIM_IMPH_MC_VC0_RD_CMP_MSK (0x00000007)
  #define MPMCARB_CR_RCH_RD_CMP_ARB_NTR_XTM_LIM_IMPH_MC_VC0_RD_CMP_MIN (0)
  #define MPMCARB_CR_RCH_RD_CMP_ARB_NTR_XTM_LIM_IMPH_MC_VC0_RD_CMP_MAX (7) // 0x00000007
  #define MPMCARB_CR_RCH_RD_CMP_ARB_NTR_XTM_LIM_IMPH_MC_VC0_RD_CMP_DEF (0x00000004)
  #define MPMCARB_CR_RCH_RD_CMP_ARB_NTR_XTM_LIM_IMPH_MC_VC0_RD_CMP_HSH (0x03007814)

  #define MPMCARB_CR_RCH_RD_CMP_ARB_NTR_XTM_LIM_IMPH_MEE_VC0_RD_CMP_OFF ( 4)
  #define MPMCARB_CR_RCH_RD_CMP_ARB_NTR_XTM_LIM_IMPH_MEE_VC0_RD_CMP_WID ( 3)
  #define MPMCARB_CR_RCH_RD_CMP_ARB_NTR_XTM_LIM_IMPH_MEE_VC0_RD_CMP_MSK (0x00000070)
  #define MPMCARB_CR_RCH_RD_CMP_ARB_NTR_XTM_LIM_IMPH_MEE_VC0_RD_CMP_MIN (0)
  #define MPMCARB_CR_RCH_RD_CMP_ARB_NTR_XTM_LIM_IMPH_MEE_VC0_RD_CMP_MAX (7) // 0x00000007
  #define MPMCARB_CR_RCH_RD_CMP_ARB_NTR_XTM_LIM_IMPH_MEE_VC0_RD_CMP_DEF (0x00000004)
  #define MPMCARB_CR_RCH_RD_CMP_ARB_NTR_XTM_LIM_IMPH_MEE_VC0_RD_CMP_HSH (0x03047814)

  #define MPMCARB_CR_RCH_RD_CMP_ARB_NTR_XTM_LIM_IMPH_EFLOW_VC0_RD_CMP_OFF ( 8)
  #define MPMCARB_CR_RCH_RD_CMP_ARB_NTR_XTM_LIM_IMPH_EFLOW_VC0_RD_CMP_WID ( 3)
  #define MPMCARB_CR_RCH_RD_CMP_ARB_NTR_XTM_LIM_IMPH_EFLOW_VC0_RD_CMP_MSK (0x00000700)
  #define MPMCARB_CR_RCH_RD_CMP_ARB_NTR_XTM_LIM_IMPH_EFLOW_VC0_RD_CMP_MIN (0)
  #define MPMCARB_CR_RCH_RD_CMP_ARB_NTR_XTM_LIM_IMPH_EFLOW_VC0_RD_CMP_MAX (7) // 0x00000007
  #define MPMCARB_CR_RCH_RD_CMP_ARB_NTR_XTM_LIM_IMPH_EFLOW_VC0_RD_CMP_DEF (0x00000004)
  #define MPMCARB_CR_RCH_RD_CMP_ARB_NTR_XTM_LIM_IMPH_EFLOW_VC0_RD_CMP_HSH (0x03087814)

#define MPMCARB_CR_RCH_RD_CMP_ARB_EFLOW_LIM_IMPH_REG                   (0x00007818)

  #define MPMCARB_CR_RCH_RD_CMP_ARB_EFLOW_LIM_IMPH_MC_VC0_RD_CMP_OFF   ( 0)
  #define MPMCARB_CR_RCH_RD_CMP_ARB_EFLOW_LIM_IMPH_MC_VC0_RD_CMP_WID   ( 3)
  #define MPMCARB_CR_RCH_RD_CMP_ARB_EFLOW_LIM_IMPH_MC_VC0_RD_CMP_MSK   (0x00000007)
  #define MPMCARB_CR_RCH_RD_CMP_ARB_EFLOW_LIM_IMPH_MC_VC0_RD_CMP_MIN   (0)
  #define MPMCARB_CR_RCH_RD_CMP_ARB_EFLOW_LIM_IMPH_MC_VC0_RD_CMP_MAX   (7) // 0x00000007
  #define MPMCARB_CR_RCH_RD_CMP_ARB_EFLOW_LIM_IMPH_MC_VC0_RD_CMP_DEF   (0x00000004)
  #define MPMCARB_CR_RCH_RD_CMP_ARB_EFLOW_LIM_IMPH_MC_VC0_RD_CMP_HSH   (0x03007818)

  #define MPMCARB_CR_RCH_RD_CMP_ARB_EFLOW_LIM_IMPH_MEE_VC0_RD_CMP_OFF  ( 4)
  #define MPMCARB_CR_RCH_RD_CMP_ARB_EFLOW_LIM_IMPH_MEE_VC0_RD_CMP_WID  ( 3)
  #define MPMCARB_CR_RCH_RD_CMP_ARB_EFLOW_LIM_IMPH_MEE_VC0_RD_CMP_MSK  (0x00000070)
  #define MPMCARB_CR_RCH_RD_CMP_ARB_EFLOW_LIM_IMPH_MEE_VC0_RD_CMP_MIN  (0)
  #define MPMCARB_CR_RCH_RD_CMP_ARB_EFLOW_LIM_IMPH_MEE_VC0_RD_CMP_MAX  (7) // 0x00000007
  #define MPMCARB_CR_RCH_RD_CMP_ARB_EFLOW_LIM_IMPH_MEE_VC0_RD_CMP_DEF  (0x00000004)
  #define MPMCARB_CR_RCH_RD_CMP_ARB_EFLOW_LIM_IMPH_MEE_VC0_RD_CMP_HSH  (0x03047818)

#define MPMCARB_CR_XTM_EDRAM_FILL_POLICY_IMPH_REG                      (0x0000781C)

  #define MPMCARB_CR_XTM_EDRAM_FILL_POLICY_IMPH_DMI_VC0_RD_FILL_OFF    ( 0)
  #define MPMCARB_CR_XTM_EDRAM_FILL_POLICY_IMPH_DMI_VC0_RD_FILL_WID    ( 1)
  #define MPMCARB_CR_XTM_EDRAM_FILL_POLICY_IMPH_DMI_VC0_RD_FILL_MSK    (0x00000001)
  #define MPMCARB_CR_XTM_EDRAM_FILL_POLICY_IMPH_DMI_VC0_RD_FILL_MIN    (0)
  #define MPMCARB_CR_XTM_EDRAM_FILL_POLICY_IMPH_DMI_VC0_RD_FILL_MAX    (1) // 0x00000001
  #define MPMCARB_CR_XTM_EDRAM_FILL_POLICY_IMPH_DMI_VC0_RD_FILL_DEF    (0x00000001)
  #define MPMCARB_CR_XTM_EDRAM_FILL_POLICY_IMPH_DMI_VC0_RD_FILL_HSH    (0x0100781C)

  #define MPMCARB_CR_XTM_EDRAM_FILL_POLICY_IMPH_DMI_VC0_WR_FILL_OFF    ( 1)
  #define MPMCARB_CR_XTM_EDRAM_FILL_POLICY_IMPH_DMI_VC0_WR_FILL_WID    ( 1)
  #define MPMCARB_CR_XTM_EDRAM_FILL_POLICY_IMPH_DMI_VC0_WR_FILL_MSK    (0x00000002)
  #define MPMCARB_CR_XTM_EDRAM_FILL_POLICY_IMPH_DMI_VC0_WR_FILL_MIN    (0)
  #define MPMCARB_CR_XTM_EDRAM_FILL_POLICY_IMPH_DMI_VC0_WR_FILL_MAX    (1) // 0x00000001
  #define MPMCARB_CR_XTM_EDRAM_FILL_POLICY_IMPH_DMI_VC0_WR_FILL_DEF    (0x00000001)
  #define MPMCARB_CR_XTM_EDRAM_FILL_POLICY_IMPH_DMI_VC0_WR_FILL_HSH    (0x0101781C)

  #define MPMCARB_CR_XTM_EDRAM_FILL_POLICY_IMPH_DMI_VCM_RD_FILL_OFF    ( 2)
  #define MPMCARB_CR_XTM_EDRAM_FILL_POLICY_IMPH_DMI_VCM_RD_FILL_WID    ( 1)
  #define MPMCARB_CR_XTM_EDRAM_FILL_POLICY_IMPH_DMI_VCM_RD_FILL_MSK    (0x00000004)
  #define MPMCARB_CR_XTM_EDRAM_FILL_POLICY_IMPH_DMI_VCM_RD_FILL_MIN    (0)
  #define MPMCARB_CR_XTM_EDRAM_FILL_POLICY_IMPH_DMI_VCM_RD_FILL_MAX    (1) // 0x00000001
  #define MPMCARB_CR_XTM_EDRAM_FILL_POLICY_IMPH_DMI_VCM_RD_FILL_DEF    (0x00000001)
  #define MPMCARB_CR_XTM_EDRAM_FILL_POLICY_IMPH_DMI_VCM_RD_FILL_HSH    (0x0102781C)

  #define MPMCARB_CR_XTM_EDRAM_FILL_POLICY_IMPH_DMI_VCM_WR_FILL_OFF    ( 3)
  #define MPMCARB_CR_XTM_EDRAM_FILL_POLICY_IMPH_DMI_VCM_WR_FILL_WID    ( 1)
  #define MPMCARB_CR_XTM_EDRAM_FILL_POLICY_IMPH_DMI_VCM_WR_FILL_MSK    (0x00000008)
  #define MPMCARB_CR_XTM_EDRAM_FILL_POLICY_IMPH_DMI_VCM_WR_FILL_MIN    (0)
  #define MPMCARB_CR_XTM_EDRAM_FILL_POLICY_IMPH_DMI_VCM_WR_FILL_MAX    (1) // 0x00000001
  #define MPMCARB_CR_XTM_EDRAM_FILL_POLICY_IMPH_DMI_VCM_WR_FILL_DEF    (0x00000001)
  #define MPMCARB_CR_XTM_EDRAM_FILL_POLICY_IMPH_DMI_VCM_WR_FILL_HSH    (0x0103781C)

  #define MPMCARB_CR_XTM_EDRAM_FILL_POLICY_IMPH_DMI_VC1_RD_FILL_OFF    ( 4)
  #define MPMCARB_CR_XTM_EDRAM_FILL_POLICY_IMPH_DMI_VC1_RD_FILL_WID    ( 1)
  #define MPMCARB_CR_XTM_EDRAM_FILL_POLICY_IMPH_DMI_VC1_RD_FILL_MSK    (0x00000010)
  #define MPMCARB_CR_XTM_EDRAM_FILL_POLICY_IMPH_DMI_VC1_RD_FILL_MIN    (0)
  #define MPMCARB_CR_XTM_EDRAM_FILL_POLICY_IMPH_DMI_VC1_RD_FILL_MAX    (1) // 0x00000001
  #define MPMCARB_CR_XTM_EDRAM_FILL_POLICY_IMPH_DMI_VC1_RD_FILL_DEF    (0x00000001)
  #define MPMCARB_CR_XTM_EDRAM_FILL_POLICY_IMPH_DMI_VC1_RD_FILL_HSH    (0x0104781C)

  #define MPMCARB_CR_XTM_EDRAM_FILL_POLICY_IMPH_DMI_VC1_WR_FILL_OFF    ( 5)
  #define MPMCARB_CR_XTM_EDRAM_FILL_POLICY_IMPH_DMI_VC1_WR_FILL_WID    ( 1)
  #define MPMCARB_CR_XTM_EDRAM_FILL_POLICY_IMPH_DMI_VC1_WR_FILL_MSK    (0x00000020)
  #define MPMCARB_CR_XTM_EDRAM_FILL_POLICY_IMPH_DMI_VC1_WR_FILL_MIN    (0)
  #define MPMCARB_CR_XTM_EDRAM_FILL_POLICY_IMPH_DMI_VC1_WR_FILL_MAX    (1) // 0x00000001
  #define MPMCARB_CR_XTM_EDRAM_FILL_POLICY_IMPH_DMI_VC1_WR_FILL_DEF    (0x00000001)
  #define MPMCARB_CR_XTM_EDRAM_FILL_POLICY_IMPH_DMI_VC1_WR_FILL_HSH    (0x0105781C)

  #define MPMCARB_CR_XTM_EDRAM_FILL_POLICY_IMPH_PEG10_RD_FILL_OFF      ( 6)
  #define MPMCARB_CR_XTM_EDRAM_FILL_POLICY_IMPH_PEG10_RD_FILL_WID      ( 1)
  #define MPMCARB_CR_XTM_EDRAM_FILL_POLICY_IMPH_PEG10_RD_FILL_MSK      (0x00000040)
  #define MPMCARB_CR_XTM_EDRAM_FILL_POLICY_IMPH_PEG10_RD_FILL_MIN      (0)
  #define MPMCARB_CR_XTM_EDRAM_FILL_POLICY_IMPH_PEG10_RD_FILL_MAX      (1) // 0x00000001
  #define MPMCARB_CR_XTM_EDRAM_FILL_POLICY_IMPH_PEG10_RD_FILL_DEF      (0x00000001)
  #define MPMCARB_CR_XTM_EDRAM_FILL_POLICY_IMPH_PEG10_RD_FILL_HSH      (0x0106781C)

  #define MPMCARB_CR_XTM_EDRAM_FILL_POLICY_IMPH_PEG10_WR_FILL_OFF      ( 7)
  #define MPMCARB_CR_XTM_EDRAM_FILL_POLICY_IMPH_PEG10_WR_FILL_WID      ( 1)
  #define MPMCARB_CR_XTM_EDRAM_FILL_POLICY_IMPH_PEG10_WR_FILL_MSK      (0x00000080)
  #define MPMCARB_CR_XTM_EDRAM_FILL_POLICY_IMPH_PEG10_WR_FILL_MIN      (0)
  #define MPMCARB_CR_XTM_EDRAM_FILL_POLICY_IMPH_PEG10_WR_FILL_MAX      (1) // 0x00000001
  #define MPMCARB_CR_XTM_EDRAM_FILL_POLICY_IMPH_PEG10_WR_FILL_DEF      (0x00000001)
  #define MPMCARB_CR_XTM_EDRAM_FILL_POLICY_IMPH_PEG10_WR_FILL_HSH      (0x0107781C)

  #define MPMCARB_CR_XTM_EDRAM_FILL_POLICY_IMPH_PEG11_RD_FILL_OFF      ( 8)
  #define MPMCARB_CR_XTM_EDRAM_FILL_POLICY_IMPH_PEG11_RD_FILL_WID      ( 1)
  #define MPMCARB_CR_XTM_EDRAM_FILL_POLICY_IMPH_PEG11_RD_FILL_MSK      (0x00000100)
  #define MPMCARB_CR_XTM_EDRAM_FILL_POLICY_IMPH_PEG11_RD_FILL_MIN      (0)
  #define MPMCARB_CR_XTM_EDRAM_FILL_POLICY_IMPH_PEG11_RD_FILL_MAX      (1) // 0x00000001
  #define MPMCARB_CR_XTM_EDRAM_FILL_POLICY_IMPH_PEG11_RD_FILL_DEF      (0x00000001)
  #define MPMCARB_CR_XTM_EDRAM_FILL_POLICY_IMPH_PEG11_RD_FILL_HSH      (0x0108781C)

  #define MPMCARB_CR_XTM_EDRAM_FILL_POLICY_IMPH_PEG11_WR_FILL_OFF      ( 9)
  #define MPMCARB_CR_XTM_EDRAM_FILL_POLICY_IMPH_PEG11_WR_FILL_WID      ( 1)
  #define MPMCARB_CR_XTM_EDRAM_FILL_POLICY_IMPH_PEG11_WR_FILL_MSK      (0x00000200)
  #define MPMCARB_CR_XTM_EDRAM_FILL_POLICY_IMPH_PEG11_WR_FILL_MIN      (0)
  #define MPMCARB_CR_XTM_EDRAM_FILL_POLICY_IMPH_PEG11_WR_FILL_MAX      (1) // 0x00000001
  #define MPMCARB_CR_XTM_EDRAM_FILL_POLICY_IMPH_PEG11_WR_FILL_DEF      (0x00000001)
  #define MPMCARB_CR_XTM_EDRAM_FILL_POLICY_IMPH_PEG11_WR_FILL_HSH      (0x0109781C)

  #define MPMCARB_CR_XTM_EDRAM_FILL_POLICY_IMPH_PEG12_RD_FILL_OFF      (10)
  #define MPMCARB_CR_XTM_EDRAM_FILL_POLICY_IMPH_PEG12_RD_FILL_WID      ( 1)
  #define MPMCARB_CR_XTM_EDRAM_FILL_POLICY_IMPH_PEG12_RD_FILL_MSK      (0x00000400)
  #define MPMCARB_CR_XTM_EDRAM_FILL_POLICY_IMPH_PEG12_RD_FILL_MIN      (0)
  #define MPMCARB_CR_XTM_EDRAM_FILL_POLICY_IMPH_PEG12_RD_FILL_MAX      (1) // 0x00000001
  #define MPMCARB_CR_XTM_EDRAM_FILL_POLICY_IMPH_PEG12_RD_FILL_DEF      (0x00000001)
  #define MPMCARB_CR_XTM_EDRAM_FILL_POLICY_IMPH_PEG12_RD_FILL_HSH      (0x010A781C)

  #define MPMCARB_CR_XTM_EDRAM_FILL_POLICY_IMPH_PEG12_WR_FILL_OFF      (11)
  #define MPMCARB_CR_XTM_EDRAM_FILL_POLICY_IMPH_PEG12_WR_FILL_WID      ( 1)
  #define MPMCARB_CR_XTM_EDRAM_FILL_POLICY_IMPH_PEG12_WR_FILL_MSK      (0x00000800)
  #define MPMCARB_CR_XTM_EDRAM_FILL_POLICY_IMPH_PEG12_WR_FILL_MIN      (0)
  #define MPMCARB_CR_XTM_EDRAM_FILL_POLICY_IMPH_PEG12_WR_FILL_MAX      (1) // 0x00000001
  #define MPMCARB_CR_XTM_EDRAM_FILL_POLICY_IMPH_PEG12_WR_FILL_DEF      (0x00000001)
  #define MPMCARB_CR_XTM_EDRAM_FILL_POLICY_IMPH_PEG12_WR_FILL_HSH      (0x010B781C)

  #define MPMCARB_CR_XTM_EDRAM_FILL_POLICY_IMPH_DE_VC0_RD_FILL_OFF     (12)
  #define MPMCARB_CR_XTM_EDRAM_FILL_POLICY_IMPH_DE_VC0_RD_FILL_WID     ( 1)
  #define MPMCARB_CR_XTM_EDRAM_FILL_POLICY_IMPH_DE_VC0_RD_FILL_MSK     (0x00001000)
  #define MPMCARB_CR_XTM_EDRAM_FILL_POLICY_IMPH_DE_VC0_RD_FILL_MIN     (0)
  #define MPMCARB_CR_XTM_EDRAM_FILL_POLICY_IMPH_DE_VC0_RD_FILL_MAX     (1) // 0x00000001
  #define MPMCARB_CR_XTM_EDRAM_FILL_POLICY_IMPH_DE_VC0_RD_FILL_DEF     (0x00000001)
  #define MPMCARB_CR_XTM_EDRAM_FILL_POLICY_IMPH_DE_VC0_RD_FILL_HSH     (0x010C781C)

  #define MPMCARB_CR_XTM_EDRAM_FILL_POLICY_IMPH_DE_VC0_WR_FILL_OFF     (13)
  #define MPMCARB_CR_XTM_EDRAM_FILL_POLICY_IMPH_DE_VC0_WR_FILL_WID     ( 1)
  #define MPMCARB_CR_XTM_EDRAM_FILL_POLICY_IMPH_DE_VC0_WR_FILL_MSK     (0x00002000)
  #define MPMCARB_CR_XTM_EDRAM_FILL_POLICY_IMPH_DE_VC0_WR_FILL_MIN     (0)
  #define MPMCARB_CR_XTM_EDRAM_FILL_POLICY_IMPH_DE_VC0_WR_FILL_MAX     (1) // 0x00000001
  #define MPMCARB_CR_XTM_EDRAM_FILL_POLICY_IMPH_DE_VC0_WR_FILL_DEF     (0x00000001)
  #define MPMCARB_CR_XTM_EDRAM_FILL_POLICY_IMPH_DE_VC0_WR_FILL_HSH     (0x010D781C)

  #define MPMCARB_CR_XTM_EDRAM_FILL_POLICY_IMPH_DE_VC1_RD_FILL_OFF     (14)
  #define MPMCARB_CR_XTM_EDRAM_FILL_POLICY_IMPH_DE_VC1_RD_FILL_WID     ( 1)
  #define MPMCARB_CR_XTM_EDRAM_FILL_POLICY_IMPH_DE_VC1_RD_FILL_MSK     (0x00004000)
  #define MPMCARB_CR_XTM_EDRAM_FILL_POLICY_IMPH_DE_VC1_RD_FILL_MIN     (0)
  #define MPMCARB_CR_XTM_EDRAM_FILL_POLICY_IMPH_DE_VC1_RD_FILL_MAX     (1) // 0x00000001
  #define MPMCARB_CR_XTM_EDRAM_FILL_POLICY_IMPH_DE_VC1_RD_FILL_DEF     (0x00000001)
  #define MPMCARB_CR_XTM_EDRAM_FILL_POLICY_IMPH_DE_VC1_RD_FILL_HSH     (0x010E781C)

  #define MPMCARB_CR_XTM_EDRAM_FILL_POLICY_IMPH_CAM_RD_FILL_OFF        (15)
  #define MPMCARB_CR_XTM_EDRAM_FILL_POLICY_IMPH_CAM_RD_FILL_WID        ( 1)
  #define MPMCARB_CR_XTM_EDRAM_FILL_POLICY_IMPH_CAM_RD_FILL_MSK        (0x00008000)
  #define MPMCARB_CR_XTM_EDRAM_FILL_POLICY_IMPH_CAM_RD_FILL_MIN        (0)
  #define MPMCARB_CR_XTM_EDRAM_FILL_POLICY_IMPH_CAM_RD_FILL_MAX        (1) // 0x00000001
  #define MPMCARB_CR_XTM_EDRAM_FILL_POLICY_IMPH_CAM_RD_FILL_DEF        (0x00000001)
  #define MPMCARB_CR_XTM_EDRAM_FILL_POLICY_IMPH_CAM_RD_FILL_HSH        (0x010F781C)

  #define MPMCARB_CR_XTM_EDRAM_FILL_POLICY_IMPH_CAM_WR_FILL_OFF        (16)
  #define MPMCARB_CR_XTM_EDRAM_FILL_POLICY_IMPH_CAM_WR_FILL_WID        ( 1)
  #define MPMCARB_CR_XTM_EDRAM_FILL_POLICY_IMPH_CAM_WR_FILL_MSK        (0x00010000)
  #define MPMCARB_CR_XTM_EDRAM_FILL_POLICY_IMPH_CAM_WR_FILL_MIN        (0)
  #define MPMCARB_CR_XTM_EDRAM_FILL_POLICY_IMPH_CAM_WR_FILL_MAX        (1) // 0x00000001
  #define MPMCARB_CR_XTM_EDRAM_FILL_POLICY_IMPH_CAM_WR_FILL_DEF        (0x00000001)
  #define MPMCARB_CR_XTM_EDRAM_FILL_POLICY_IMPH_CAM_WR_FILL_HSH        (0x0110781C)

  #define MPMCARB_CR_XTM_EDRAM_FILL_POLICY_IMPH_GMM_RD_FILL_OFF        (17)
  #define MPMCARB_CR_XTM_EDRAM_FILL_POLICY_IMPH_GMM_RD_FILL_WID        ( 1)
  #define MPMCARB_CR_XTM_EDRAM_FILL_POLICY_IMPH_GMM_RD_FILL_MSK        (0x00020000)
  #define MPMCARB_CR_XTM_EDRAM_FILL_POLICY_IMPH_GMM_RD_FILL_MIN        (0)
  #define MPMCARB_CR_XTM_EDRAM_FILL_POLICY_IMPH_GMM_RD_FILL_MAX        (1) // 0x00000001
  #define MPMCARB_CR_XTM_EDRAM_FILL_POLICY_IMPH_GMM_RD_FILL_DEF        (0x00000001)
  #define MPMCARB_CR_XTM_EDRAM_FILL_POLICY_IMPH_GMM_RD_FILL_HSH        (0x0111781C)

  #define MPMCARB_CR_XTM_EDRAM_FILL_POLICY_IMPH_GMM_WR_FILL_OFF        (18)
  #define MPMCARB_CR_XTM_EDRAM_FILL_POLICY_IMPH_GMM_WR_FILL_WID        ( 1)
  #define MPMCARB_CR_XTM_EDRAM_FILL_POLICY_IMPH_GMM_WR_FILL_MSK        (0x00040000)
  #define MPMCARB_CR_XTM_EDRAM_FILL_POLICY_IMPH_GMM_WR_FILL_MIN        (0)
  #define MPMCARB_CR_XTM_EDRAM_FILL_POLICY_IMPH_GMM_WR_FILL_MAX        (1) // 0x00000001
  #define MPMCARB_CR_XTM_EDRAM_FILL_POLICY_IMPH_GMM_WR_FILL_DEF        (0x00000001)
  #define MPMCARB_CR_XTM_EDRAM_FILL_POLICY_IMPH_GMM_WR_FILL_HSH        (0x0112781C)

  #define MPMCARB_CR_XTM_EDRAM_FILL_POLICY_IMPH_MISC_FILL_OFF          (19)
  #define MPMCARB_CR_XTM_EDRAM_FILL_POLICY_IMPH_MISC_FILL_WID          ( 1)
  #define MPMCARB_CR_XTM_EDRAM_FILL_POLICY_IMPH_MISC_FILL_MSK          (0x00080000)
  #define MPMCARB_CR_XTM_EDRAM_FILL_POLICY_IMPH_MISC_FILL_MIN          (0)
  #define MPMCARB_CR_XTM_EDRAM_FILL_POLICY_IMPH_MISC_FILL_MAX          (1) // 0x00000001
  #define MPMCARB_CR_XTM_EDRAM_FILL_POLICY_IMPH_MISC_FILL_DEF          (0x00000001)
  #define MPMCARB_CR_XTM_EDRAM_FILL_POLICY_IMPH_MISC_FILL_HSH          (0x0113781C)

#define MPMCARB_CR_VISA_CTL_MPMCARBS_F_IMPH_REG                        (0x00007820)

  #define MPMCARB_CR_VISA_CTL_MPMCARBS_F_IMPH_EN_CLK_OFF               ( 0)
  #define MPMCARB_CR_VISA_CTL_MPMCARBS_F_IMPH_EN_CLK_WID               ( 1)
  #define MPMCARB_CR_VISA_CTL_MPMCARBS_F_IMPH_EN_CLK_MSK               (0x00000001)
  #define MPMCARB_CR_VISA_CTL_MPMCARBS_F_IMPH_EN_CLK_MIN               (0)
  #define MPMCARB_CR_VISA_CTL_MPMCARBS_F_IMPH_EN_CLK_MAX               (1) // 0x00000001
  #define MPMCARB_CR_VISA_CTL_MPMCARBS_F_IMPH_EN_CLK_DEF               (0x00000000)
  #define MPMCARB_CR_VISA_CTL_MPMCARBS_F_IMPH_EN_CLK_HSH               (0x01007820)

  #define MPMCARB_CR_VISA_CTL_MPMCARBS_F_IMPH_L0_DATA_BYTE_SEL_OFF     ( 1)
  #define MPMCARB_CR_VISA_CTL_MPMCARBS_F_IMPH_L0_DATA_BYTE_SEL_WID     ( 7)
  #define MPMCARB_CR_VISA_CTL_MPMCARBS_F_IMPH_L0_DATA_BYTE_SEL_MSK     (0x000000FE)
  #define MPMCARB_CR_VISA_CTL_MPMCARBS_F_IMPH_L0_DATA_BYTE_SEL_MIN     (0)
  #define MPMCARB_CR_VISA_CTL_MPMCARBS_F_IMPH_L0_DATA_BYTE_SEL_MAX     (127) // 0x0000007F
  #define MPMCARB_CR_VISA_CTL_MPMCARBS_F_IMPH_L0_DATA_BYTE_SEL_DEF     (0x00000000)
  #define MPMCARB_CR_VISA_CTL_MPMCARBS_F_IMPH_L0_DATA_BYTE_SEL_HSH     (0x07017820)

  #define MPMCARB_CR_VISA_CTL_MPMCARBS_F_IMPH_L0_BYP_SEL_OFF           ( 8)
  #define MPMCARB_CR_VISA_CTL_MPMCARBS_F_IMPH_L0_BYP_SEL_WID           ( 1)
  #define MPMCARB_CR_VISA_CTL_MPMCARBS_F_IMPH_L0_BYP_SEL_MSK           (0x00000100)
  #define MPMCARB_CR_VISA_CTL_MPMCARBS_F_IMPH_L0_BYP_SEL_MIN           (0)
  #define MPMCARB_CR_VISA_CTL_MPMCARBS_F_IMPH_L0_BYP_SEL_MAX           (1) // 0x00000001
  #define MPMCARB_CR_VISA_CTL_MPMCARBS_F_IMPH_L0_BYP_SEL_DEF           (0x00000000)
  #define MPMCARB_CR_VISA_CTL_MPMCARBS_F_IMPH_L0_BYP_SEL_HSH           (0x01087820)

  #define MPMCARB_CR_VISA_CTL_MPMCARBS_F_IMPH_L1_DATA_BYTE_SEL_OFF     ( 9)
  #define MPMCARB_CR_VISA_CTL_MPMCARBS_F_IMPH_L1_DATA_BYTE_SEL_WID     ( 7)
  #define MPMCARB_CR_VISA_CTL_MPMCARBS_F_IMPH_L1_DATA_BYTE_SEL_MSK     (0x0000FE00)
  #define MPMCARB_CR_VISA_CTL_MPMCARBS_F_IMPH_L1_DATA_BYTE_SEL_MIN     (0)
  #define MPMCARB_CR_VISA_CTL_MPMCARBS_F_IMPH_L1_DATA_BYTE_SEL_MAX     (127) // 0x0000007F
  #define MPMCARB_CR_VISA_CTL_MPMCARBS_F_IMPH_L1_DATA_BYTE_SEL_DEF     (0x00000000)
  #define MPMCARB_CR_VISA_CTL_MPMCARBS_F_IMPH_L1_DATA_BYTE_SEL_HSH     (0x07097820)

  #define MPMCARB_CR_VISA_CTL_MPMCARBS_F_IMPH_L1_BYP_SEL_OFF           (16)
  #define MPMCARB_CR_VISA_CTL_MPMCARBS_F_IMPH_L1_BYP_SEL_WID           ( 1)
  #define MPMCARB_CR_VISA_CTL_MPMCARBS_F_IMPH_L1_BYP_SEL_MSK           (0x00010000)
  #define MPMCARB_CR_VISA_CTL_MPMCARBS_F_IMPH_L1_BYP_SEL_MIN           (0)
  #define MPMCARB_CR_VISA_CTL_MPMCARBS_F_IMPH_L1_BYP_SEL_MAX           (1) // 0x00000001
  #define MPMCARB_CR_VISA_CTL_MPMCARBS_F_IMPH_L1_BYP_SEL_DEF           (0x00000000)
  #define MPMCARB_CR_VISA_CTL_MPMCARBS_F_IMPH_L1_BYP_SEL_HSH           (0x01107820)

  #define MPMCARB_CR_VISA_CTL_MPMCARBS_F_IMPH_VORANGE_OFF              (31)
  #define MPMCARB_CR_VISA_CTL_MPMCARBS_F_IMPH_VORANGE_WID              ( 1)
  #define MPMCARB_CR_VISA_CTL_MPMCARBS_F_IMPH_VORANGE_MSK              (0x80000000)
  #define MPMCARB_CR_VISA_CTL_MPMCARBS_F_IMPH_VORANGE_MIN              (0)
  #define MPMCARB_CR_VISA_CTL_MPMCARBS_F_IMPH_VORANGE_MAX              (1) // 0x00000001
  #define MPMCARB_CR_VISA_CTL_MPMCARBS_F_IMPH_VORANGE_DEF              (0x00000000)
  #define MPMCARB_CR_VISA_CTL_MPMCARBS_F_IMPH_VORANGE_HSH              (0x011F7820)

#define MPMCARB_CR_VISA_CTL_MPMCARBS_D_IMPH_REG                        (0x00007824)

  #define MPMCARB_CR_VISA_CTL_MPMCARBS_D_IMPH_EN_CLK_OFF               ( 0)
  #define MPMCARB_CR_VISA_CTL_MPMCARBS_D_IMPH_EN_CLK_WID               ( 1)
  #define MPMCARB_CR_VISA_CTL_MPMCARBS_D_IMPH_EN_CLK_MSK               (0x00000001)
  #define MPMCARB_CR_VISA_CTL_MPMCARBS_D_IMPH_EN_CLK_MIN               (0)
  #define MPMCARB_CR_VISA_CTL_MPMCARBS_D_IMPH_EN_CLK_MAX               (1) // 0x00000001
  #define MPMCARB_CR_VISA_CTL_MPMCARBS_D_IMPH_EN_CLK_DEF               (0x00000000)
  #define MPMCARB_CR_VISA_CTL_MPMCARBS_D_IMPH_EN_CLK_HSH               (0x01007824)

  #define MPMCARB_CR_VISA_CTL_MPMCARBS_D_IMPH_L0_DATA_BYTE_SEL_OFF     ( 1)
  #define MPMCARB_CR_VISA_CTL_MPMCARBS_D_IMPH_L0_DATA_BYTE_SEL_WID     ( 7)
  #define MPMCARB_CR_VISA_CTL_MPMCARBS_D_IMPH_L0_DATA_BYTE_SEL_MSK     (0x000000FE)
  #define MPMCARB_CR_VISA_CTL_MPMCARBS_D_IMPH_L0_DATA_BYTE_SEL_MIN     (0)
  #define MPMCARB_CR_VISA_CTL_MPMCARBS_D_IMPH_L0_DATA_BYTE_SEL_MAX     (127) // 0x0000007F
  #define MPMCARB_CR_VISA_CTL_MPMCARBS_D_IMPH_L0_DATA_BYTE_SEL_DEF     (0x00000000)
  #define MPMCARB_CR_VISA_CTL_MPMCARBS_D_IMPH_L0_DATA_BYTE_SEL_HSH     (0x07017824)

  #define MPMCARB_CR_VISA_CTL_MPMCARBS_D_IMPH_L0_BYP_SEL_OFF           ( 8)
  #define MPMCARB_CR_VISA_CTL_MPMCARBS_D_IMPH_L0_BYP_SEL_WID           ( 1)
  #define MPMCARB_CR_VISA_CTL_MPMCARBS_D_IMPH_L0_BYP_SEL_MSK           (0x00000100)
  #define MPMCARB_CR_VISA_CTL_MPMCARBS_D_IMPH_L0_BYP_SEL_MIN           (0)
  #define MPMCARB_CR_VISA_CTL_MPMCARBS_D_IMPH_L0_BYP_SEL_MAX           (1) // 0x00000001
  #define MPMCARB_CR_VISA_CTL_MPMCARBS_D_IMPH_L0_BYP_SEL_DEF           (0x00000000)
  #define MPMCARB_CR_VISA_CTL_MPMCARBS_D_IMPH_L0_BYP_SEL_HSH           (0x01087824)

  #define MPMCARB_CR_VISA_CTL_MPMCARBS_D_IMPH_L1_DATA_BYTE_SEL_OFF     ( 9)
  #define MPMCARB_CR_VISA_CTL_MPMCARBS_D_IMPH_L1_DATA_BYTE_SEL_WID     ( 7)
  #define MPMCARB_CR_VISA_CTL_MPMCARBS_D_IMPH_L1_DATA_BYTE_SEL_MSK     (0x0000FE00)
  #define MPMCARB_CR_VISA_CTL_MPMCARBS_D_IMPH_L1_DATA_BYTE_SEL_MIN     (0)
  #define MPMCARB_CR_VISA_CTL_MPMCARBS_D_IMPH_L1_DATA_BYTE_SEL_MAX     (127) // 0x0000007F
  #define MPMCARB_CR_VISA_CTL_MPMCARBS_D_IMPH_L1_DATA_BYTE_SEL_DEF     (0x00000000)
  #define MPMCARB_CR_VISA_CTL_MPMCARBS_D_IMPH_L1_DATA_BYTE_SEL_HSH     (0x07097824)

  #define MPMCARB_CR_VISA_CTL_MPMCARBS_D_IMPH_L1_BYP_SEL_OFF           (16)
  #define MPMCARB_CR_VISA_CTL_MPMCARBS_D_IMPH_L1_BYP_SEL_WID           ( 1)
  #define MPMCARB_CR_VISA_CTL_MPMCARBS_D_IMPH_L1_BYP_SEL_MSK           (0x00010000)
  #define MPMCARB_CR_VISA_CTL_MPMCARBS_D_IMPH_L1_BYP_SEL_MIN           (0)
  #define MPMCARB_CR_VISA_CTL_MPMCARBS_D_IMPH_L1_BYP_SEL_MAX           (1) // 0x00000001
  #define MPMCARB_CR_VISA_CTL_MPMCARBS_D_IMPH_L1_BYP_SEL_DEF           (0x00000000)
  #define MPMCARB_CR_VISA_CTL_MPMCARBS_D_IMPH_L1_BYP_SEL_HSH           (0x01107824)

  #define MPMCARB_CR_VISA_CTL_MPMCARBS_D_IMPH_VORANGE_OFF              (31)
  #define MPMCARB_CR_VISA_CTL_MPMCARBS_D_IMPH_VORANGE_WID              ( 1)
  #define MPMCARB_CR_VISA_CTL_MPMCARBS_D_IMPH_VORANGE_MSK              (0x80000000)
  #define MPMCARB_CR_VISA_CTL_MPMCARBS_D_IMPH_VORANGE_MIN              (0)
  #define MPMCARB_CR_VISA_CTL_MPMCARBS_D_IMPH_VORANGE_MAX              (1) // 0x00000001
  #define MPMCARB_CR_VISA_CTL_MPMCARBS_D_IMPH_VORANGE_DEF              (0x00000000)
  #define MPMCARB_CR_VISA_CTL_MPMCARBS_D_IMPH_VORANGE_HSH              (0x011F7824)

#define MPMCARB_CR_VISA_QD_DEMUX_MPMCARBS_IMPH_REG                     (0x00007828)

  #define MPMCARB_CR_VISA_QD_DEMUX_MPMCARBS_IMPH_noa_demux_OFF         ( 0)
  #define MPMCARB_CR_VISA_QD_DEMUX_MPMCARBS_IMPH_noa_demux_WID         ( 1)
  #define MPMCARB_CR_VISA_QD_DEMUX_MPMCARBS_IMPH_noa_demux_MSK         (0x00000001)
  #define MPMCARB_CR_VISA_QD_DEMUX_MPMCARBS_IMPH_noa_demux_MIN         (0)
  #define MPMCARB_CR_VISA_QD_DEMUX_MPMCARBS_IMPH_noa_demux_MAX         (1) // 0x00000001
  #define MPMCARB_CR_VISA_QD_DEMUX_MPMCARBS_IMPH_noa_demux_DEF         (0x00000000)
  #define MPMCARB_CR_VISA_QD_DEMUX_MPMCARBS_IMPH_noa_demux_HSH         (0x01007828)

  #define MPMCARB_CR_VISA_QD_DEMUX_MPMCARBS_IMPH_noa_countctrl_OFF     ( 1)
  #define MPMCARB_CR_VISA_QD_DEMUX_MPMCARBS_IMPH_noa_countctrl_WID     ( 1)
  #define MPMCARB_CR_VISA_QD_DEMUX_MPMCARBS_IMPH_noa_countctrl_MSK     (0x00000002)
  #define MPMCARB_CR_VISA_QD_DEMUX_MPMCARBS_IMPH_noa_countctrl_MIN     (0)
  #define MPMCARB_CR_VISA_QD_DEMUX_MPMCARBS_IMPH_noa_countctrl_MAX     (1) // 0x00000001
  #define MPMCARB_CR_VISA_QD_DEMUX_MPMCARBS_IMPH_noa_countctrl_DEF     (0x00000000)
  #define MPMCARB_CR_VISA_QD_DEMUX_MPMCARBS_IMPH_noa_countctrl_HSH     (0x01017828)

#define MPMCARB_CR_VISA_XBAR_MPMCARBS_D_IMPH_REG                       (0x0000782C)

  #define MPMCARB_CR_VISA_XBAR_MPMCARBS_D_IMPH_FXB_Li_BIT0_DATA_BIT_SEL_OFF ( 0)
  #define MPMCARB_CR_VISA_XBAR_MPMCARBS_D_IMPH_FXB_Li_BIT0_DATA_BIT_SEL_WID ( 3)
  #define MPMCARB_CR_VISA_XBAR_MPMCARBS_D_IMPH_FXB_Li_BIT0_DATA_BIT_SEL_MSK (0x00000007)
  #define MPMCARB_CR_VISA_XBAR_MPMCARBS_D_IMPH_FXB_Li_BIT0_DATA_BIT_SEL_MIN (0)
  #define MPMCARB_CR_VISA_XBAR_MPMCARBS_D_IMPH_FXB_Li_BIT0_DATA_BIT_SEL_MAX (7) // 0x00000007
  #define MPMCARB_CR_VISA_XBAR_MPMCARBS_D_IMPH_FXB_Li_BIT0_DATA_BIT_SEL_DEF (0x00000000)
  #define MPMCARB_CR_VISA_XBAR_MPMCARBS_D_IMPH_FXB_Li_BIT0_DATA_BIT_SEL_HSH (0x0300782C)

  #define MPMCARB_CR_VISA_XBAR_MPMCARBS_D_IMPH_FXB_Li_BIT0_DATA_BYTE_SEL_OFF ( 3)
  #define MPMCARB_CR_VISA_XBAR_MPMCARBS_D_IMPH_FXB_Li_BIT0_DATA_BYTE_SEL_WID ( 1)
  #define MPMCARB_CR_VISA_XBAR_MPMCARBS_D_IMPH_FXB_Li_BIT0_DATA_BYTE_SEL_MSK (0x00000008)
  #define MPMCARB_CR_VISA_XBAR_MPMCARBS_D_IMPH_FXB_Li_BIT0_DATA_BYTE_SEL_MIN (0)
  #define MPMCARB_CR_VISA_XBAR_MPMCARBS_D_IMPH_FXB_Li_BIT0_DATA_BYTE_SEL_MAX (1) // 0x00000001
  #define MPMCARB_CR_VISA_XBAR_MPMCARBS_D_IMPH_FXB_Li_BIT0_DATA_BYTE_SEL_DEF (0x00000000)
  #define MPMCARB_CR_VISA_XBAR_MPMCARBS_D_IMPH_FXB_Li_BIT0_DATA_BYTE_SEL_HSH (0x0103782C)

  #define MPMCARB_CR_VISA_XBAR_MPMCARBS_D_IMPH_FXB_Li_BIT1_DATA_BIT_SEL_OFF ( 4)
  #define MPMCARB_CR_VISA_XBAR_MPMCARBS_D_IMPH_FXB_Li_BIT1_DATA_BIT_SEL_WID ( 3)
  #define MPMCARB_CR_VISA_XBAR_MPMCARBS_D_IMPH_FXB_Li_BIT1_DATA_BIT_SEL_MSK (0x00000070)
  #define MPMCARB_CR_VISA_XBAR_MPMCARBS_D_IMPH_FXB_Li_BIT1_DATA_BIT_SEL_MIN (0)
  #define MPMCARB_CR_VISA_XBAR_MPMCARBS_D_IMPH_FXB_Li_BIT1_DATA_BIT_SEL_MAX (7) // 0x00000007
  #define MPMCARB_CR_VISA_XBAR_MPMCARBS_D_IMPH_FXB_Li_BIT1_DATA_BIT_SEL_DEF (0x00000001)
  #define MPMCARB_CR_VISA_XBAR_MPMCARBS_D_IMPH_FXB_Li_BIT1_DATA_BIT_SEL_HSH (0x0304782C)

  #define MPMCARB_CR_VISA_XBAR_MPMCARBS_D_IMPH_FXB_Li_BIT1_DATA_BYTE_SEL_OFF ( 7)
  #define MPMCARB_CR_VISA_XBAR_MPMCARBS_D_IMPH_FXB_Li_BIT1_DATA_BYTE_SEL_WID ( 1)
  #define MPMCARB_CR_VISA_XBAR_MPMCARBS_D_IMPH_FXB_Li_BIT1_DATA_BYTE_SEL_MSK (0x00000080)
  #define MPMCARB_CR_VISA_XBAR_MPMCARBS_D_IMPH_FXB_Li_BIT1_DATA_BYTE_SEL_MIN (0)
  #define MPMCARB_CR_VISA_XBAR_MPMCARBS_D_IMPH_FXB_Li_BIT1_DATA_BYTE_SEL_MAX (1) // 0x00000001
  #define MPMCARB_CR_VISA_XBAR_MPMCARBS_D_IMPH_FXB_Li_BIT1_DATA_BYTE_SEL_DEF (0x00000000)
  #define MPMCARB_CR_VISA_XBAR_MPMCARBS_D_IMPH_FXB_Li_BIT1_DATA_BYTE_SEL_HSH (0x0107782C)

  #define MPMCARB_CR_VISA_XBAR_MPMCARBS_D_IMPH_FXB_Li_BIT2_DATA_BIT_SEL_OFF ( 8)
  #define MPMCARB_CR_VISA_XBAR_MPMCARBS_D_IMPH_FXB_Li_BIT2_DATA_BIT_SEL_WID ( 3)
  #define MPMCARB_CR_VISA_XBAR_MPMCARBS_D_IMPH_FXB_Li_BIT2_DATA_BIT_SEL_MSK (0x00000700)
  #define MPMCARB_CR_VISA_XBAR_MPMCARBS_D_IMPH_FXB_Li_BIT2_DATA_BIT_SEL_MIN (0)
  #define MPMCARB_CR_VISA_XBAR_MPMCARBS_D_IMPH_FXB_Li_BIT2_DATA_BIT_SEL_MAX (7) // 0x00000007
  #define MPMCARB_CR_VISA_XBAR_MPMCARBS_D_IMPH_FXB_Li_BIT2_DATA_BIT_SEL_DEF (0x00000002)
  #define MPMCARB_CR_VISA_XBAR_MPMCARBS_D_IMPH_FXB_Li_BIT2_DATA_BIT_SEL_HSH (0x0308782C)

  #define MPMCARB_CR_VISA_XBAR_MPMCARBS_D_IMPH_FXB_Li_BIT2_DATA_BYTE_SEL_OFF (11)
  #define MPMCARB_CR_VISA_XBAR_MPMCARBS_D_IMPH_FXB_Li_BIT2_DATA_BYTE_SEL_WID ( 1)
  #define MPMCARB_CR_VISA_XBAR_MPMCARBS_D_IMPH_FXB_Li_BIT2_DATA_BYTE_SEL_MSK (0x00000800)
  #define MPMCARB_CR_VISA_XBAR_MPMCARBS_D_IMPH_FXB_Li_BIT2_DATA_BYTE_SEL_MIN (0)
  #define MPMCARB_CR_VISA_XBAR_MPMCARBS_D_IMPH_FXB_Li_BIT2_DATA_BYTE_SEL_MAX (1) // 0x00000001
  #define MPMCARB_CR_VISA_XBAR_MPMCARBS_D_IMPH_FXB_Li_BIT2_DATA_BYTE_SEL_DEF (0x00000000)
  #define MPMCARB_CR_VISA_XBAR_MPMCARBS_D_IMPH_FXB_Li_BIT2_DATA_BYTE_SEL_HSH (0x010B782C)

  #define MPMCARB_CR_VISA_XBAR_MPMCARBS_D_IMPH_FXB_Li_BIT3_DATA_BIT_SEL_OFF (12)
  #define MPMCARB_CR_VISA_XBAR_MPMCARBS_D_IMPH_FXB_Li_BIT3_DATA_BIT_SEL_WID ( 3)
  #define MPMCARB_CR_VISA_XBAR_MPMCARBS_D_IMPH_FXB_Li_BIT3_DATA_BIT_SEL_MSK (0x00007000)
  #define MPMCARB_CR_VISA_XBAR_MPMCARBS_D_IMPH_FXB_Li_BIT3_DATA_BIT_SEL_MIN (0)
  #define MPMCARB_CR_VISA_XBAR_MPMCARBS_D_IMPH_FXB_Li_BIT3_DATA_BIT_SEL_MAX (7) // 0x00000007
  #define MPMCARB_CR_VISA_XBAR_MPMCARBS_D_IMPH_FXB_Li_BIT3_DATA_BIT_SEL_DEF (0x00000003)
  #define MPMCARB_CR_VISA_XBAR_MPMCARBS_D_IMPH_FXB_Li_BIT3_DATA_BIT_SEL_HSH (0x030C782C)

  #define MPMCARB_CR_VISA_XBAR_MPMCARBS_D_IMPH_FXB_Li_BIT3_DATA_BYTE_SEL_OFF (15)
  #define MPMCARB_CR_VISA_XBAR_MPMCARBS_D_IMPH_FXB_Li_BIT3_DATA_BYTE_SEL_WID ( 1)
  #define MPMCARB_CR_VISA_XBAR_MPMCARBS_D_IMPH_FXB_Li_BIT3_DATA_BYTE_SEL_MSK (0x00008000)
  #define MPMCARB_CR_VISA_XBAR_MPMCARBS_D_IMPH_FXB_Li_BIT3_DATA_BYTE_SEL_MIN (0)
  #define MPMCARB_CR_VISA_XBAR_MPMCARBS_D_IMPH_FXB_Li_BIT3_DATA_BYTE_SEL_MAX (1) // 0x00000001
  #define MPMCARB_CR_VISA_XBAR_MPMCARBS_D_IMPH_FXB_Li_BIT3_DATA_BYTE_SEL_DEF (0x00000000)
  #define MPMCARB_CR_VISA_XBAR_MPMCARBS_D_IMPH_FXB_Li_BIT3_DATA_BYTE_SEL_HSH (0x010F782C)

  #define MPMCARB_CR_VISA_XBAR_MPMCARBS_D_IMPH_FXB_Li_BIT4_DATA_BIT_SEL_OFF (16)
  #define MPMCARB_CR_VISA_XBAR_MPMCARBS_D_IMPH_FXB_Li_BIT4_DATA_BIT_SEL_WID ( 3)
  #define MPMCARB_CR_VISA_XBAR_MPMCARBS_D_IMPH_FXB_Li_BIT4_DATA_BIT_SEL_MSK (0x00070000)
  #define MPMCARB_CR_VISA_XBAR_MPMCARBS_D_IMPH_FXB_Li_BIT4_DATA_BIT_SEL_MIN (0)
  #define MPMCARB_CR_VISA_XBAR_MPMCARBS_D_IMPH_FXB_Li_BIT4_DATA_BIT_SEL_MAX (7) // 0x00000007
  #define MPMCARB_CR_VISA_XBAR_MPMCARBS_D_IMPH_FXB_Li_BIT4_DATA_BIT_SEL_DEF (0x00000004)
  #define MPMCARB_CR_VISA_XBAR_MPMCARBS_D_IMPH_FXB_Li_BIT4_DATA_BIT_SEL_HSH (0x0310782C)

  #define MPMCARB_CR_VISA_XBAR_MPMCARBS_D_IMPH_FXB_Li_BIT4_DATA_BYTE_SEL_OFF (19)
  #define MPMCARB_CR_VISA_XBAR_MPMCARBS_D_IMPH_FXB_Li_BIT4_DATA_BYTE_SEL_WID ( 1)
  #define MPMCARB_CR_VISA_XBAR_MPMCARBS_D_IMPH_FXB_Li_BIT4_DATA_BYTE_SEL_MSK (0x00080000)
  #define MPMCARB_CR_VISA_XBAR_MPMCARBS_D_IMPH_FXB_Li_BIT4_DATA_BYTE_SEL_MIN (0)
  #define MPMCARB_CR_VISA_XBAR_MPMCARBS_D_IMPH_FXB_Li_BIT4_DATA_BYTE_SEL_MAX (1) // 0x00000001
  #define MPMCARB_CR_VISA_XBAR_MPMCARBS_D_IMPH_FXB_Li_BIT4_DATA_BYTE_SEL_DEF (0x00000000)
  #define MPMCARB_CR_VISA_XBAR_MPMCARBS_D_IMPH_FXB_Li_BIT4_DATA_BYTE_SEL_HSH (0x0113782C)

  #define MPMCARB_CR_VISA_XBAR_MPMCARBS_D_IMPH_FXB_Li_BIT5_DATA_BIT_SEL_OFF (20)
  #define MPMCARB_CR_VISA_XBAR_MPMCARBS_D_IMPH_FXB_Li_BIT5_DATA_BIT_SEL_WID ( 3)
  #define MPMCARB_CR_VISA_XBAR_MPMCARBS_D_IMPH_FXB_Li_BIT5_DATA_BIT_SEL_MSK (0x00700000)
  #define MPMCARB_CR_VISA_XBAR_MPMCARBS_D_IMPH_FXB_Li_BIT5_DATA_BIT_SEL_MIN (0)
  #define MPMCARB_CR_VISA_XBAR_MPMCARBS_D_IMPH_FXB_Li_BIT5_DATA_BIT_SEL_MAX (7) // 0x00000007
  #define MPMCARB_CR_VISA_XBAR_MPMCARBS_D_IMPH_FXB_Li_BIT5_DATA_BIT_SEL_DEF (0x00000005)
  #define MPMCARB_CR_VISA_XBAR_MPMCARBS_D_IMPH_FXB_Li_BIT5_DATA_BIT_SEL_HSH (0x0314782C)

  #define MPMCARB_CR_VISA_XBAR_MPMCARBS_D_IMPH_FXB_Li_BIT5_DATA_BYTE_SEL_OFF (23)
  #define MPMCARB_CR_VISA_XBAR_MPMCARBS_D_IMPH_FXB_Li_BIT5_DATA_BYTE_SEL_WID ( 1)
  #define MPMCARB_CR_VISA_XBAR_MPMCARBS_D_IMPH_FXB_Li_BIT5_DATA_BYTE_SEL_MSK (0x00800000)
  #define MPMCARB_CR_VISA_XBAR_MPMCARBS_D_IMPH_FXB_Li_BIT5_DATA_BYTE_SEL_MIN (0)
  #define MPMCARB_CR_VISA_XBAR_MPMCARBS_D_IMPH_FXB_Li_BIT5_DATA_BYTE_SEL_MAX (1) // 0x00000001
  #define MPMCARB_CR_VISA_XBAR_MPMCARBS_D_IMPH_FXB_Li_BIT5_DATA_BYTE_SEL_DEF (0x00000000)
  #define MPMCARB_CR_VISA_XBAR_MPMCARBS_D_IMPH_FXB_Li_BIT5_DATA_BYTE_SEL_HSH (0x0117782C)

  #define MPMCARB_CR_VISA_XBAR_MPMCARBS_D_IMPH_FXB_Li_BIT6_DATA_BIT_SEL_OFF (24)
  #define MPMCARB_CR_VISA_XBAR_MPMCARBS_D_IMPH_FXB_Li_BIT6_DATA_BIT_SEL_WID ( 3)
  #define MPMCARB_CR_VISA_XBAR_MPMCARBS_D_IMPH_FXB_Li_BIT6_DATA_BIT_SEL_MSK (0x07000000)
  #define MPMCARB_CR_VISA_XBAR_MPMCARBS_D_IMPH_FXB_Li_BIT6_DATA_BIT_SEL_MIN (0)
  #define MPMCARB_CR_VISA_XBAR_MPMCARBS_D_IMPH_FXB_Li_BIT6_DATA_BIT_SEL_MAX (7) // 0x00000007
  #define MPMCARB_CR_VISA_XBAR_MPMCARBS_D_IMPH_FXB_Li_BIT6_DATA_BIT_SEL_DEF (0x00000006)
  #define MPMCARB_CR_VISA_XBAR_MPMCARBS_D_IMPH_FXB_Li_BIT6_DATA_BIT_SEL_HSH (0x0318782C)

  #define MPMCARB_CR_VISA_XBAR_MPMCARBS_D_IMPH_FXB_Li_BIT6_DATA_BYTE_SEL_OFF (27)
  #define MPMCARB_CR_VISA_XBAR_MPMCARBS_D_IMPH_FXB_Li_BIT6_DATA_BYTE_SEL_WID ( 1)
  #define MPMCARB_CR_VISA_XBAR_MPMCARBS_D_IMPH_FXB_Li_BIT6_DATA_BYTE_SEL_MSK (0x08000000)
  #define MPMCARB_CR_VISA_XBAR_MPMCARBS_D_IMPH_FXB_Li_BIT6_DATA_BYTE_SEL_MIN (0)
  #define MPMCARB_CR_VISA_XBAR_MPMCARBS_D_IMPH_FXB_Li_BIT6_DATA_BYTE_SEL_MAX (1) // 0x00000001
  #define MPMCARB_CR_VISA_XBAR_MPMCARBS_D_IMPH_FXB_Li_BIT6_DATA_BYTE_SEL_DEF (0x00000000)
  #define MPMCARB_CR_VISA_XBAR_MPMCARBS_D_IMPH_FXB_Li_BIT6_DATA_BYTE_SEL_HSH (0x011B782C)

  #define MPMCARB_CR_VISA_XBAR_MPMCARBS_D_IMPH_FXB_Li_BIT7_DATA_BIT_SEL_OFF (28)
  #define MPMCARB_CR_VISA_XBAR_MPMCARBS_D_IMPH_FXB_Li_BIT7_DATA_BIT_SEL_WID ( 3)
  #define MPMCARB_CR_VISA_XBAR_MPMCARBS_D_IMPH_FXB_Li_BIT7_DATA_BIT_SEL_MSK (0x70000000)
  #define MPMCARB_CR_VISA_XBAR_MPMCARBS_D_IMPH_FXB_Li_BIT7_DATA_BIT_SEL_MIN (0)
  #define MPMCARB_CR_VISA_XBAR_MPMCARBS_D_IMPH_FXB_Li_BIT7_DATA_BIT_SEL_MAX (7) // 0x00000007
  #define MPMCARB_CR_VISA_XBAR_MPMCARBS_D_IMPH_FXB_Li_BIT7_DATA_BIT_SEL_DEF (0x00000007)
  #define MPMCARB_CR_VISA_XBAR_MPMCARBS_D_IMPH_FXB_Li_BIT7_DATA_BIT_SEL_HSH (0x031C782C)

  #define MPMCARB_CR_VISA_XBAR_MPMCARBS_D_IMPH_FXB_Li_BIT7_DATA_BYTE_SEL_OFF (31)
  #define MPMCARB_CR_VISA_XBAR_MPMCARBS_D_IMPH_FXB_Li_BIT7_DATA_BYTE_SEL_WID ( 1)
  #define MPMCARB_CR_VISA_XBAR_MPMCARBS_D_IMPH_FXB_Li_BIT7_DATA_BYTE_SEL_MSK (0x80000000)
  #define MPMCARB_CR_VISA_XBAR_MPMCARBS_D_IMPH_FXB_Li_BIT7_DATA_BYTE_SEL_MIN (0)
  #define MPMCARB_CR_VISA_XBAR_MPMCARBS_D_IMPH_FXB_Li_BIT7_DATA_BYTE_SEL_MAX (1) // 0x00000001
  #define MPMCARB_CR_VISA_XBAR_MPMCARBS_D_IMPH_FXB_Li_BIT7_DATA_BYTE_SEL_DEF (0x00000000)
  #define MPMCARB_CR_VISA_XBAR_MPMCARBS_D_IMPH_FXB_Li_BIT7_DATA_BYTE_SEL_HSH (0x011F782C)

#define MPMCARB_CR_VISA_SLIDE_MPMCARBS_F_IMPH_REG                      (0x00007830)

  #define MPMCARB_CR_VISA_SLIDE_MPMCARBS_F_IMPH_WINDOW_SLIDE_L0_OFF    ( 0)
  #define MPMCARB_CR_VISA_SLIDE_MPMCARBS_F_IMPH_WINDOW_SLIDE_L0_WID    ( 3)
  #define MPMCARB_CR_VISA_SLIDE_MPMCARBS_F_IMPH_WINDOW_SLIDE_L0_MSK    (0x00000007)
  #define MPMCARB_CR_VISA_SLIDE_MPMCARBS_F_IMPH_WINDOW_SLIDE_L0_MIN    (0)
  #define MPMCARB_CR_VISA_SLIDE_MPMCARBS_F_IMPH_WINDOW_SLIDE_L0_MAX    (7) // 0x00000007
  #define MPMCARB_CR_VISA_SLIDE_MPMCARBS_F_IMPH_WINDOW_SLIDE_L0_DEF    (0x00000000)
  #define MPMCARB_CR_VISA_SLIDE_MPMCARBS_F_IMPH_WINDOW_SLIDE_L0_HSH    (0x03007830)

  #define MPMCARB_CR_VISA_SLIDE_MPMCARBS_F_IMPH_ALT_L0_DATA_BYTE_SEL_OFF ( 3)
  #define MPMCARB_CR_VISA_SLIDE_MPMCARBS_F_IMPH_ALT_L0_DATA_BYTE_SEL_WID ( 7)
  #define MPMCARB_CR_VISA_SLIDE_MPMCARBS_F_IMPH_ALT_L0_DATA_BYTE_SEL_MSK (0x000003F8)
  #define MPMCARB_CR_VISA_SLIDE_MPMCARBS_F_IMPH_ALT_L0_DATA_BYTE_SEL_MIN (0)
  #define MPMCARB_CR_VISA_SLIDE_MPMCARBS_F_IMPH_ALT_L0_DATA_BYTE_SEL_MAX (127) // 0x0000007F
  #define MPMCARB_CR_VISA_SLIDE_MPMCARBS_F_IMPH_ALT_L0_DATA_BYTE_SEL_DEF (0x00000000)
  #define MPMCARB_CR_VISA_SLIDE_MPMCARBS_F_IMPH_ALT_L0_DATA_BYTE_SEL_HSH (0x07037830)

  #define MPMCARB_CR_VISA_SLIDE_MPMCARBS_F_IMPH_WINDOW_SLIDE_L1_OFF    (10)
  #define MPMCARB_CR_VISA_SLIDE_MPMCARBS_F_IMPH_WINDOW_SLIDE_L1_WID    ( 3)
  #define MPMCARB_CR_VISA_SLIDE_MPMCARBS_F_IMPH_WINDOW_SLIDE_L1_MSK    (0x00001C00)
  #define MPMCARB_CR_VISA_SLIDE_MPMCARBS_F_IMPH_WINDOW_SLIDE_L1_MIN    (0)
  #define MPMCARB_CR_VISA_SLIDE_MPMCARBS_F_IMPH_WINDOW_SLIDE_L1_MAX    (7) // 0x00000007
  #define MPMCARB_CR_VISA_SLIDE_MPMCARBS_F_IMPH_WINDOW_SLIDE_L1_DEF    (0x00000000)
  #define MPMCARB_CR_VISA_SLIDE_MPMCARBS_F_IMPH_WINDOW_SLIDE_L1_HSH    (0x030A7830)

  #define MPMCARB_CR_VISA_SLIDE_MPMCARBS_F_IMPH_ALT_L1_DATA_BYTE_SEL_OFF (13)
  #define MPMCARB_CR_VISA_SLIDE_MPMCARBS_F_IMPH_ALT_L1_DATA_BYTE_SEL_WID ( 7)
  #define MPMCARB_CR_VISA_SLIDE_MPMCARBS_F_IMPH_ALT_L1_DATA_BYTE_SEL_MSK (0x000FE000)
  #define MPMCARB_CR_VISA_SLIDE_MPMCARBS_F_IMPH_ALT_L1_DATA_BYTE_SEL_MIN (0)
  #define MPMCARB_CR_VISA_SLIDE_MPMCARBS_F_IMPH_ALT_L1_DATA_BYTE_SEL_MAX (127) // 0x0000007F
  #define MPMCARB_CR_VISA_SLIDE_MPMCARBS_F_IMPH_ALT_L1_DATA_BYTE_SEL_DEF (0x00000000)
  #define MPMCARB_CR_VISA_SLIDE_MPMCARBS_F_IMPH_ALT_L1_DATA_BYTE_SEL_HSH (0x070D7830)

#define MPMCARB_CR_VISA_SLIDE_MPMCARBS_D_IMPH_REG                      (0x00007834)

  #define MPMCARB_CR_VISA_SLIDE_MPMCARBS_D_IMPH_WINDOW_SLIDE_L0_OFF    ( 0)
  #define MPMCARB_CR_VISA_SLIDE_MPMCARBS_D_IMPH_WINDOW_SLIDE_L0_WID    ( 3)
  #define MPMCARB_CR_VISA_SLIDE_MPMCARBS_D_IMPH_WINDOW_SLIDE_L0_MSK    (0x00000007)
  #define MPMCARB_CR_VISA_SLIDE_MPMCARBS_D_IMPH_WINDOW_SLIDE_L0_MIN    (0)
  #define MPMCARB_CR_VISA_SLIDE_MPMCARBS_D_IMPH_WINDOW_SLIDE_L0_MAX    (7) // 0x00000007
  #define MPMCARB_CR_VISA_SLIDE_MPMCARBS_D_IMPH_WINDOW_SLIDE_L0_DEF    (0x00000000)
  #define MPMCARB_CR_VISA_SLIDE_MPMCARBS_D_IMPH_WINDOW_SLIDE_L0_HSH    (0x03007834)

  #define MPMCARB_CR_VISA_SLIDE_MPMCARBS_D_IMPH_ALT_L0_DATA_BYTE_SEL_OFF ( 3)
  #define MPMCARB_CR_VISA_SLIDE_MPMCARBS_D_IMPH_ALT_L0_DATA_BYTE_SEL_WID ( 7)
  #define MPMCARB_CR_VISA_SLIDE_MPMCARBS_D_IMPH_ALT_L0_DATA_BYTE_SEL_MSK (0x000003F8)
  #define MPMCARB_CR_VISA_SLIDE_MPMCARBS_D_IMPH_ALT_L0_DATA_BYTE_SEL_MIN (0)
  #define MPMCARB_CR_VISA_SLIDE_MPMCARBS_D_IMPH_ALT_L0_DATA_BYTE_SEL_MAX (127) // 0x0000007F
  #define MPMCARB_CR_VISA_SLIDE_MPMCARBS_D_IMPH_ALT_L0_DATA_BYTE_SEL_DEF (0x00000000)
  #define MPMCARB_CR_VISA_SLIDE_MPMCARBS_D_IMPH_ALT_L0_DATA_BYTE_SEL_HSH (0x07037834)

  #define MPMCARB_CR_VISA_SLIDE_MPMCARBS_D_IMPH_WINDOW_SLIDE_L1_OFF    (10)
  #define MPMCARB_CR_VISA_SLIDE_MPMCARBS_D_IMPH_WINDOW_SLIDE_L1_WID    ( 3)
  #define MPMCARB_CR_VISA_SLIDE_MPMCARBS_D_IMPH_WINDOW_SLIDE_L1_MSK    (0x00001C00)
  #define MPMCARB_CR_VISA_SLIDE_MPMCARBS_D_IMPH_WINDOW_SLIDE_L1_MIN    (0)
  #define MPMCARB_CR_VISA_SLIDE_MPMCARBS_D_IMPH_WINDOW_SLIDE_L1_MAX    (7) // 0x00000007
  #define MPMCARB_CR_VISA_SLIDE_MPMCARBS_D_IMPH_WINDOW_SLIDE_L1_DEF    (0x00000000)
  #define MPMCARB_CR_VISA_SLIDE_MPMCARBS_D_IMPH_WINDOW_SLIDE_L1_HSH    (0x030A7834)

  #define MPMCARB_CR_VISA_SLIDE_MPMCARBS_D_IMPH_ALT_L1_DATA_BYTE_SEL_OFF (13)
  #define MPMCARB_CR_VISA_SLIDE_MPMCARBS_D_IMPH_ALT_L1_DATA_BYTE_SEL_WID ( 7)
  #define MPMCARB_CR_VISA_SLIDE_MPMCARBS_D_IMPH_ALT_L1_DATA_BYTE_SEL_MSK (0x000FE000)
  #define MPMCARB_CR_VISA_SLIDE_MPMCARBS_D_IMPH_ALT_L1_DATA_BYTE_SEL_MIN (0)
  #define MPMCARB_CR_VISA_SLIDE_MPMCARBS_D_IMPH_ALT_L1_DATA_BYTE_SEL_MAX (127) // 0x0000007F
  #define MPMCARB_CR_VISA_SLIDE_MPMCARBS_D_IMPH_ALT_L1_DATA_BYTE_SEL_DEF (0x00000000)
  #define MPMCARB_CR_VISA_SLIDE_MPMCARBS_D_IMPH_ALT_L1_DATA_BYTE_SEL_HSH (0x070D7834)

#define MPMCARB_CR_RCH_RING_TRTL_IMPH_REG                              (0x00007838)

  #define MPMCARB_CR_RCH_RING_TRTL_IMPH_RDMARK_OFF                     ( 0)
  #define MPMCARB_CR_RCH_RING_TRTL_IMPH_RDMARK_WID                     ( 8)
  #define MPMCARB_CR_RCH_RING_TRTL_IMPH_RDMARK_MSK                     (0x000000FF)
  #define MPMCARB_CR_RCH_RING_TRTL_IMPH_RDMARK_MIN                     (0)
  #define MPMCARB_CR_RCH_RING_TRTL_IMPH_RDMARK_MAX                     (255) // 0x000000FF
  #define MPMCARB_CR_RCH_RING_TRTL_IMPH_RDMARK_DEF                     (0x00000048)
  #define MPMCARB_CR_RCH_RING_TRTL_IMPH_RDMARK_HSH                     (0x08007838)

  #define MPMCARB_CR_RCH_RING_TRTL_IMPH_WRMARK_OFF                     ( 8)
  #define MPMCARB_CR_RCH_RING_TRTL_IMPH_WRMARK_WID                     ( 8)
  #define MPMCARB_CR_RCH_RING_TRTL_IMPH_WRMARK_MSK                     (0x0000FF00)
  #define MPMCARB_CR_RCH_RING_TRTL_IMPH_WRMARK_MIN                     (0)
  #define MPMCARB_CR_RCH_RING_TRTL_IMPH_WRMARK_MAX                     (255) // 0x000000FF
  #define MPMCARB_CR_RCH_RING_TRTL_IMPH_WRMARK_DEF                     (0x00000048)
  #define MPMCARB_CR_RCH_RING_TRTL_IMPH_WRMARK_HSH                     (0x08087838)

#define MPMCARB_CR_RCH_REQ_ARB_MC_MEE_IPC_IMPH_REG                     (0x00007840)

  #define MPMCARB_CR_RCH_REQ_ARB_MC_MEE_IPC_IMPH_NON_VC1_THRESHOLD_OFF ( 0)
  #define MPMCARB_CR_RCH_REQ_ARB_MC_MEE_IPC_IMPH_NON_VC1_THRESHOLD_WID ( 4)
  #define MPMCARB_CR_RCH_REQ_ARB_MC_MEE_IPC_IMPH_NON_VC1_THRESHOLD_MSK (0x0000000F)
  #define MPMCARB_CR_RCH_REQ_ARB_MC_MEE_IPC_IMPH_NON_VC1_THRESHOLD_MIN (0)
  #define MPMCARB_CR_RCH_REQ_ARB_MC_MEE_IPC_IMPH_NON_VC1_THRESHOLD_MAX (15) // 0x0000000F
  #define MPMCARB_CR_RCH_REQ_ARB_MC_MEE_IPC_IMPH_NON_VC1_THRESHOLD_DEF (0x00000008)
  #define MPMCARB_CR_RCH_REQ_ARB_MC_MEE_IPC_IMPH_NON_VC1_THRESHOLD_HSH (0x04007840)

  #define MPMCARB_CR_RCH_REQ_ARB_MC_MEE_IPC_IMPH_VC1_RD_THRESHOLD_OFF  ( 4)
  #define MPMCARB_CR_RCH_REQ_ARB_MC_MEE_IPC_IMPH_VC1_RD_THRESHOLD_WID  ( 4)
  #define MPMCARB_CR_RCH_REQ_ARB_MC_MEE_IPC_IMPH_VC1_RD_THRESHOLD_MSK  (0x000000F0)
  #define MPMCARB_CR_RCH_REQ_ARB_MC_MEE_IPC_IMPH_VC1_RD_THRESHOLD_MIN  (0)
  #define MPMCARB_CR_RCH_REQ_ARB_MC_MEE_IPC_IMPH_VC1_RD_THRESHOLD_MAX  (15) // 0x0000000F
  #define MPMCARB_CR_RCH_REQ_ARB_MC_MEE_IPC_IMPH_VC1_RD_THRESHOLD_DEF  (0x00000008)
  #define MPMCARB_CR_RCH_REQ_ARB_MC_MEE_IPC_IMPH_VC1_RD_THRESHOLD_HSH  (0x04047840)

  #define MPMCARB_CR_RCH_REQ_ARB_MC_MEE_IPC_IMPH_FIXED_RATE_EN_OFF     ( 8)
  #define MPMCARB_CR_RCH_REQ_ARB_MC_MEE_IPC_IMPH_FIXED_RATE_EN_WID     ( 1)
  #define MPMCARB_CR_RCH_REQ_ARB_MC_MEE_IPC_IMPH_FIXED_RATE_EN_MSK     (0x00000100)
  #define MPMCARB_CR_RCH_REQ_ARB_MC_MEE_IPC_IMPH_FIXED_RATE_EN_MIN     (0)
  #define MPMCARB_CR_RCH_REQ_ARB_MC_MEE_IPC_IMPH_FIXED_RATE_EN_MAX     (1) // 0x00000001
  #define MPMCARB_CR_RCH_REQ_ARB_MC_MEE_IPC_IMPH_FIXED_RATE_EN_DEF     (0x00000000)
  #define MPMCARB_CR_RCH_REQ_ARB_MC_MEE_IPC_IMPH_FIXED_RATE_EN_HSH     (0x01087840)

  #define MPMCARB_CR_RCH_REQ_ARB_MC_MEE_IPC_IMPH_HIGH_PRIO_LIM_OFF     ( 9)
  #define MPMCARB_CR_RCH_REQ_ARB_MC_MEE_IPC_IMPH_HIGH_PRIO_LIM_WID     ( 3)
  #define MPMCARB_CR_RCH_REQ_ARB_MC_MEE_IPC_IMPH_HIGH_PRIO_LIM_MSK     (0x00000E00)
  #define MPMCARB_CR_RCH_REQ_ARB_MC_MEE_IPC_IMPH_HIGH_PRIO_LIM_MIN     (0)
  #define MPMCARB_CR_RCH_REQ_ARB_MC_MEE_IPC_IMPH_HIGH_PRIO_LIM_MAX     (7) // 0x00000007
  #define MPMCARB_CR_RCH_REQ_ARB_MC_MEE_IPC_IMPH_HIGH_PRIO_LIM_DEF     (0x00000004)
  #define MPMCARB_CR_RCH_REQ_ARB_MC_MEE_IPC_IMPH_HIGH_PRIO_LIM_HSH     (0x03097840)

  #define MPMCARB_CR_RCH_REQ_ARB_MC_MEE_IPC_IMPH_LOW_PRIO_LIM_OFF      (12)
  #define MPMCARB_CR_RCH_REQ_ARB_MC_MEE_IPC_IMPH_LOW_PRIO_LIM_WID      ( 3)
  #define MPMCARB_CR_RCH_REQ_ARB_MC_MEE_IPC_IMPH_LOW_PRIO_LIM_MSK      (0x00007000)
  #define MPMCARB_CR_RCH_REQ_ARB_MC_MEE_IPC_IMPH_LOW_PRIO_LIM_MIN      (0)
  #define MPMCARB_CR_RCH_REQ_ARB_MC_MEE_IPC_IMPH_LOW_PRIO_LIM_MAX      (7) // 0x00000007
  #define MPMCARB_CR_RCH_REQ_ARB_MC_MEE_IPC_IMPH_LOW_PRIO_LIM_DEF      (0x00000001)
  #define MPMCARB_CR_RCH_REQ_ARB_MC_MEE_IPC_IMPH_LOW_PRIO_LIM_HSH      (0x030C7840)

  #define MPMCARB_CR_RCH_REQ_ARB_MC_MEE_IPC_IMPH_SPARE_OFF             (15)
  #define MPMCARB_CR_RCH_REQ_ARB_MC_MEE_IPC_IMPH_SPARE_WID             ( 1)
  #define MPMCARB_CR_RCH_REQ_ARB_MC_MEE_IPC_IMPH_SPARE_MSK             (0x00008000)
  #define MPMCARB_CR_RCH_REQ_ARB_MC_MEE_IPC_IMPH_SPARE_MIN             (0)
  #define MPMCARB_CR_RCH_REQ_ARB_MC_MEE_IPC_IMPH_SPARE_MAX             (1) // 0x00000001
  #define MPMCARB_CR_RCH_REQ_ARB_MC_MEE_IPC_IMPH_SPARE_DEF             (0x00000000)
  #define MPMCARB_CR_RCH_REQ_ARB_MC_MEE_IPC_IMPH_SPARE_HSH             (0x010F7840)

#define MPMCARB_CR_RCH_REQ_ARB_EFLOW_IPC_IMPH_REG                      (0x00007844)

  #define MPMCARB_CR_RCH_REQ_ARB_EFLOW_IPC_IMPH_NON_VC1_THRESHOLD_OFF  ( 0)
  #define MPMCARB_CR_RCH_REQ_ARB_EFLOW_IPC_IMPH_NON_VC1_THRESHOLD_WID  ( 4)
  #define MPMCARB_CR_RCH_REQ_ARB_EFLOW_IPC_IMPH_NON_VC1_THRESHOLD_MSK  (0x0000000F)
  #define MPMCARB_CR_RCH_REQ_ARB_EFLOW_IPC_IMPH_NON_VC1_THRESHOLD_MIN  (0)
  #define MPMCARB_CR_RCH_REQ_ARB_EFLOW_IPC_IMPH_NON_VC1_THRESHOLD_MAX  (15) // 0x0000000F
  #define MPMCARB_CR_RCH_REQ_ARB_EFLOW_IPC_IMPH_NON_VC1_THRESHOLD_DEF  (0x00000008)
  #define MPMCARB_CR_RCH_REQ_ARB_EFLOW_IPC_IMPH_NON_VC1_THRESHOLD_HSH  (0x04007844)

  #define MPMCARB_CR_RCH_REQ_ARB_EFLOW_IPC_IMPH_VC1_RD_THRESHOLD_OFF   ( 4)
  #define MPMCARB_CR_RCH_REQ_ARB_EFLOW_IPC_IMPH_VC1_RD_THRESHOLD_WID   ( 4)
  #define MPMCARB_CR_RCH_REQ_ARB_EFLOW_IPC_IMPH_VC1_RD_THRESHOLD_MSK   (0x000000F0)
  #define MPMCARB_CR_RCH_REQ_ARB_EFLOW_IPC_IMPH_VC1_RD_THRESHOLD_MIN   (0)
  #define MPMCARB_CR_RCH_REQ_ARB_EFLOW_IPC_IMPH_VC1_RD_THRESHOLD_MAX   (15) // 0x0000000F
  #define MPMCARB_CR_RCH_REQ_ARB_EFLOW_IPC_IMPH_VC1_RD_THRESHOLD_DEF   (0x00000008)
  #define MPMCARB_CR_RCH_REQ_ARB_EFLOW_IPC_IMPH_VC1_RD_THRESHOLD_HSH   (0x04047844)

  #define MPMCARB_CR_RCH_REQ_ARB_EFLOW_IPC_IMPH_FIXED_RATE_EN_OFF      ( 8)
  #define MPMCARB_CR_RCH_REQ_ARB_EFLOW_IPC_IMPH_FIXED_RATE_EN_WID      ( 1)
  #define MPMCARB_CR_RCH_REQ_ARB_EFLOW_IPC_IMPH_FIXED_RATE_EN_MSK      (0x00000100)
  #define MPMCARB_CR_RCH_REQ_ARB_EFLOW_IPC_IMPH_FIXED_RATE_EN_MIN      (0)
  #define MPMCARB_CR_RCH_REQ_ARB_EFLOW_IPC_IMPH_FIXED_RATE_EN_MAX      (1) // 0x00000001
  #define MPMCARB_CR_RCH_REQ_ARB_EFLOW_IPC_IMPH_FIXED_RATE_EN_DEF      (0x00000000)
  #define MPMCARB_CR_RCH_REQ_ARB_EFLOW_IPC_IMPH_FIXED_RATE_EN_HSH      (0x01087844)

  #define MPMCARB_CR_RCH_REQ_ARB_EFLOW_IPC_IMPH_HIGH_PRIO_LIM_OFF      ( 9)
  #define MPMCARB_CR_RCH_REQ_ARB_EFLOW_IPC_IMPH_HIGH_PRIO_LIM_WID      ( 3)
  #define MPMCARB_CR_RCH_REQ_ARB_EFLOW_IPC_IMPH_HIGH_PRIO_LIM_MSK      (0x00000E00)
  #define MPMCARB_CR_RCH_REQ_ARB_EFLOW_IPC_IMPH_HIGH_PRIO_LIM_MIN      (0)
  #define MPMCARB_CR_RCH_REQ_ARB_EFLOW_IPC_IMPH_HIGH_PRIO_LIM_MAX      (7) // 0x00000007
  #define MPMCARB_CR_RCH_REQ_ARB_EFLOW_IPC_IMPH_HIGH_PRIO_LIM_DEF      (0x00000004)
  #define MPMCARB_CR_RCH_REQ_ARB_EFLOW_IPC_IMPH_HIGH_PRIO_LIM_HSH      (0x03097844)

  #define MPMCARB_CR_RCH_REQ_ARB_EFLOW_IPC_IMPH_LOW_PRIO_LIM_OFF       (12)
  #define MPMCARB_CR_RCH_REQ_ARB_EFLOW_IPC_IMPH_LOW_PRIO_LIM_WID       ( 3)
  #define MPMCARB_CR_RCH_REQ_ARB_EFLOW_IPC_IMPH_LOW_PRIO_LIM_MSK       (0x00007000)
  #define MPMCARB_CR_RCH_REQ_ARB_EFLOW_IPC_IMPH_LOW_PRIO_LIM_MIN       (0)
  #define MPMCARB_CR_RCH_REQ_ARB_EFLOW_IPC_IMPH_LOW_PRIO_LIM_MAX       (7) // 0x00000007
  #define MPMCARB_CR_RCH_REQ_ARB_EFLOW_IPC_IMPH_LOW_PRIO_LIM_DEF       (0x00000001)
  #define MPMCARB_CR_RCH_REQ_ARB_EFLOW_IPC_IMPH_LOW_PRIO_LIM_HSH       (0x030C7844)

  #define MPMCARB_CR_RCH_REQ_ARB_EFLOW_IPC_IMPH_SPARE_OFF              (15)
  #define MPMCARB_CR_RCH_REQ_ARB_EFLOW_IPC_IMPH_SPARE_WID              ( 1)
  #define MPMCARB_CR_RCH_REQ_ARB_EFLOW_IPC_IMPH_SPARE_MSK              (0x00008000)
  #define MPMCARB_CR_RCH_REQ_ARB_EFLOW_IPC_IMPH_SPARE_MIN              (0)
  #define MPMCARB_CR_RCH_REQ_ARB_EFLOW_IPC_IMPH_SPARE_MAX              (1) // 0x00000001
  #define MPMCARB_CR_RCH_REQ_ARB_EFLOW_IPC_IMPH_SPARE_DEF              (0x00000000)
  #define MPMCARB_CR_RCH_REQ_ARB_EFLOW_IPC_IMPH_SPARE_HSH              (0x010F7844)

#define MPMCARB_CR_RCH_RD_CMP_ARB_NTR_XTM_IPC_IMPH_REG                 (0x00007848)

  #define MPMCARB_CR_RCH_RD_CMP_ARB_NTR_XTM_IPC_IMPH_NON_VC1_THRESHOLD_OFF ( 0)
  #define MPMCARB_CR_RCH_RD_CMP_ARB_NTR_XTM_IPC_IMPH_NON_VC1_THRESHOLD_WID ( 4)
  #define MPMCARB_CR_RCH_RD_CMP_ARB_NTR_XTM_IPC_IMPH_NON_VC1_THRESHOLD_MSK (0x0000000F)
  #define MPMCARB_CR_RCH_RD_CMP_ARB_NTR_XTM_IPC_IMPH_NON_VC1_THRESHOLD_MIN (0)
  #define MPMCARB_CR_RCH_RD_CMP_ARB_NTR_XTM_IPC_IMPH_NON_VC1_THRESHOLD_MAX (15) // 0x0000000F
  #define MPMCARB_CR_RCH_RD_CMP_ARB_NTR_XTM_IPC_IMPH_NON_VC1_THRESHOLD_DEF (0x00000008)
  #define MPMCARB_CR_RCH_RD_CMP_ARB_NTR_XTM_IPC_IMPH_NON_VC1_THRESHOLD_HSH (0x04007848)

  #define MPMCARB_CR_RCH_RD_CMP_ARB_NTR_XTM_IPC_IMPH_VC1_RD_THRESHOLD_OFF ( 4)
  #define MPMCARB_CR_RCH_RD_CMP_ARB_NTR_XTM_IPC_IMPH_VC1_RD_THRESHOLD_WID ( 4)
  #define MPMCARB_CR_RCH_RD_CMP_ARB_NTR_XTM_IPC_IMPH_VC1_RD_THRESHOLD_MSK (0x000000F0)
  #define MPMCARB_CR_RCH_RD_CMP_ARB_NTR_XTM_IPC_IMPH_VC1_RD_THRESHOLD_MIN (0)
  #define MPMCARB_CR_RCH_RD_CMP_ARB_NTR_XTM_IPC_IMPH_VC1_RD_THRESHOLD_MAX (15) // 0x0000000F
  #define MPMCARB_CR_RCH_RD_CMP_ARB_NTR_XTM_IPC_IMPH_VC1_RD_THRESHOLD_DEF (0x00000008)
  #define MPMCARB_CR_RCH_RD_CMP_ARB_NTR_XTM_IPC_IMPH_VC1_RD_THRESHOLD_HSH (0x04047848)

  #define MPMCARB_CR_RCH_RD_CMP_ARB_NTR_XTM_IPC_IMPH_FIXED_RATE_EN_OFF ( 8)
  #define MPMCARB_CR_RCH_RD_CMP_ARB_NTR_XTM_IPC_IMPH_FIXED_RATE_EN_WID ( 1)
  #define MPMCARB_CR_RCH_RD_CMP_ARB_NTR_XTM_IPC_IMPH_FIXED_RATE_EN_MSK (0x00000100)
  #define MPMCARB_CR_RCH_RD_CMP_ARB_NTR_XTM_IPC_IMPH_FIXED_RATE_EN_MIN (0)
  #define MPMCARB_CR_RCH_RD_CMP_ARB_NTR_XTM_IPC_IMPH_FIXED_RATE_EN_MAX (1) // 0x00000001
  #define MPMCARB_CR_RCH_RD_CMP_ARB_NTR_XTM_IPC_IMPH_FIXED_RATE_EN_DEF (0x00000000)
  #define MPMCARB_CR_RCH_RD_CMP_ARB_NTR_XTM_IPC_IMPH_FIXED_RATE_EN_HSH (0x01087848)

  #define MPMCARB_CR_RCH_RD_CMP_ARB_NTR_XTM_IPC_IMPH_HIGH_PRIO_LIM_OFF ( 9)
  #define MPMCARB_CR_RCH_RD_CMP_ARB_NTR_XTM_IPC_IMPH_HIGH_PRIO_LIM_WID ( 3)
  #define MPMCARB_CR_RCH_RD_CMP_ARB_NTR_XTM_IPC_IMPH_HIGH_PRIO_LIM_MSK (0x00000E00)
  #define MPMCARB_CR_RCH_RD_CMP_ARB_NTR_XTM_IPC_IMPH_HIGH_PRIO_LIM_MIN (0)
  #define MPMCARB_CR_RCH_RD_CMP_ARB_NTR_XTM_IPC_IMPH_HIGH_PRIO_LIM_MAX (7) // 0x00000007
  #define MPMCARB_CR_RCH_RD_CMP_ARB_NTR_XTM_IPC_IMPH_HIGH_PRIO_LIM_DEF (0x00000004)
  #define MPMCARB_CR_RCH_RD_CMP_ARB_NTR_XTM_IPC_IMPH_HIGH_PRIO_LIM_HSH (0x03097848)

  #define MPMCARB_CR_RCH_RD_CMP_ARB_NTR_XTM_IPC_IMPH_LOW_PRIO_LIM_OFF  (12)
  #define MPMCARB_CR_RCH_RD_CMP_ARB_NTR_XTM_IPC_IMPH_LOW_PRIO_LIM_WID  ( 3)
  #define MPMCARB_CR_RCH_RD_CMP_ARB_NTR_XTM_IPC_IMPH_LOW_PRIO_LIM_MSK  (0x00007000)
  #define MPMCARB_CR_RCH_RD_CMP_ARB_NTR_XTM_IPC_IMPH_LOW_PRIO_LIM_MIN  (0)
  #define MPMCARB_CR_RCH_RD_CMP_ARB_NTR_XTM_IPC_IMPH_LOW_PRIO_LIM_MAX  (7) // 0x00000007
  #define MPMCARB_CR_RCH_RD_CMP_ARB_NTR_XTM_IPC_IMPH_LOW_PRIO_LIM_DEF  (0x00000001)
  #define MPMCARB_CR_RCH_RD_CMP_ARB_NTR_XTM_IPC_IMPH_LOW_PRIO_LIM_HSH  (0x030C7848)

  #define MPMCARB_CR_RCH_RD_CMP_ARB_NTR_XTM_IPC_IMPH_SPARE_OFF         (15)
  #define MPMCARB_CR_RCH_RD_CMP_ARB_NTR_XTM_IPC_IMPH_SPARE_WID         ( 1)
  #define MPMCARB_CR_RCH_RD_CMP_ARB_NTR_XTM_IPC_IMPH_SPARE_MSK         (0x00008000)
  #define MPMCARB_CR_RCH_RD_CMP_ARB_NTR_XTM_IPC_IMPH_SPARE_MIN         (0)
  #define MPMCARB_CR_RCH_RD_CMP_ARB_NTR_XTM_IPC_IMPH_SPARE_MAX         (1) // 0x00000001
  #define MPMCARB_CR_RCH_RD_CMP_ARB_NTR_XTM_IPC_IMPH_SPARE_DEF         (0x00000000)
  #define MPMCARB_CR_RCH_RD_CMP_ARB_NTR_XTM_IPC_IMPH_SPARE_HSH         (0x010F7848)

#define MPMCARB_CR_XTM_NTR_REQ_IPC_IMPH_REG                            (0x00007850)

  #define MPMCARB_CR_XTM_NTR_REQ_IPC_IMPH_NON_VC1_THRESHOLD_OFF        ( 0)
  #define MPMCARB_CR_XTM_NTR_REQ_IPC_IMPH_NON_VC1_THRESHOLD_WID        ( 4)
  #define MPMCARB_CR_XTM_NTR_REQ_IPC_IMPH_NON_VC1_THRESHOLD_MSK        (0x0000000F)
  #define MPMCARB_CR_XTM_NTR_REQ_IPC_IMPH_NON_VC1_THRESHOLD_MIN        (0)
  #define MPMCARB_CR_XTM_NTR_REQ_IPC_IMPH_NON_VC1_THRESHOLD_MAX        (15) // 0x0000000F
  #define MPMCARB_CR_XTM_NTR_REQ_IPC_IMPH_NON_VC1_THRESHOLD_DEF        (0x00000008)
  #define MPMCARB_CR_XTM_NTR_REQ_IPC_IMPH_NON_VC1_THRESHOLD_HSH        (0x04007850)

  #define MPMCARB_CR_XTM_NTR_REQ_IPC_IMPH_VC1_RD_THRESHOLD_OFF         ( 4)
  #define MPMCARB_CR_XTM_NTR_REQ_IPC_IMPH_VC1_RD_THRESHOLD_WID         ( 4)
  #define MPMCARB_CR_XTM_NTR_REQ_IPC_IMPH_VC1_RD_THRESHOLD_MSK         (0x000000F0)
  #define MPMCARB_CR_XTM_NTR_REQ_IPC_IMPH_VC1_RD_THRESHOLD_MIN         (0)
  #define MPMCARB_CR_XTM_NTR_REQ_IPC_IMPH_VC1_RD_THRESHOLD_MAX         (15) // 0x0000000F
  #define MPMCARB_CR_XTM_NTR_REQ_IPC_IMPH_VC1_RD_THRESHOLD_DEF         (0x00000008)
  #define MPMCARB_CR_XTM_NTR_REQ_IPC_IMPH_VC1_RD_THRESHOLD_HSH         (0x04047850)

  #define MPMCARB_CR_XTM_NTR_REQ_IPC_IMPH_FIXED_RATE_EN_OFF            ( 8)
  #define MPMCARB_CR_XTM_NTR_REQ_IPC_IMPH_FIXED_RATE_EN_WID            ( 1)
  #define MPMCARB_CR_XTM_NTR_REQ_IPC_IMPH_FIXED_RATE_EN_MSK            (0x00000100)
  #define MPMCARB_CR_XTM_NTR_REQ_IPC_IMPH_FIXED_RATE_EN_MIN            (0)
  #define MPMCARB_CR_XTM_NTR_REQ_IPC_IMPH_FIXED_RATE_EN_MAX            (1) // 0x00000001
  #define MPMCARB_CR_XTM_NTR_REQ_IPC_IMPH_FIXED_RATE_EN_DEF            (0x00000000)
  #define MPMCARB_CR_XTM_NTR_REQ_IPC_IMPH_FIXED_RATE_EN_HSH            (0x01087850)

  #define MPMCARB_CR_XTM_NTR_REQ_IPC_IMPH_HIGH_PRIO_LIM_OFF            ( 9)
  #define MPMCARB_CR_XTM_NTR_REQ_IPC_IMPH_HIGH_PRIO_LIM_WID            ( 3)
  #define MPMCARB_CR_XTM_NTR_REQ_IPC_IMPH_HIGH_PRIO_LIM_MSK            (0x00000E00)
  #define MPMCARB_CR_XTM_NTR_REQ_IPC_IMPH_HIGH_PRIO_LIM_MIN            (0)
  #define MPMCARB_CR_XTM_NTR_REQ_IPC_IMPH_HIGH_PRIO_LIM_MAX            (7) // 0x00000007
  #define MPMCARB_CR_XTM_NTR_REQ_IPC_IMPH_HIGH_PRIO_LIM_DEF            (0x00000004)
  #define MPMCARB_CR_XTM_NTR_REQ_IPC_IMPH_HIGH_PRIO_LIM_HSH            (0x03097850)

  #define MPMCARB_CR_XTM_NTR_REQ_IPC_IMPH_LOW_PRIO_LIM_OFF             (12)
  #define MPMCARB_CR_XTM_NTR_REQ_IPC_IMPH_LOW_PRIO_LIM_WID             ( 3)
  #define MPMCARB_CR_XTM_NTR_REQ_IPC_IMPH_LOW_PRIO_LIM_MSK             (0x00007000)
  #define MPMCARB_CR_XTM_NTR_REQ_IPC_IMPH_LOW_PRIO_LIM_MIN             (0)
  #define MPMCARB_CR_XTM_NTR_REQ_IPC_IMPH_LOW_PRIO_LIM_MAX             (7) // 0x00000007
  #define MPMCARB_CR_XTM_NTR_REQ_IPC_IMPH_LOW_PRIO_LIM_DEF             (0x00000001)
  #define MPMCARB_CR_XTM_NTR_REQ_IPC_IMPH_LOW_PRIO_LIM_HSH             (0x030C7850)

  #define MPMCARB_CR_XTM_NTR_REQ_IPC_IMPH_SPARE_OFF                    (15)
  #define MPMCARB_CR_XTM_NTR_REQ_IPC_IMPH_SPARE_WID                    ( 1)
  #define MPMCARB_CR_XTM_NTR_REQ_IPC_IMPH_SPARE_MSK                    (0x00008000)
  #define MPMCARB_CR_XTM_NTR_REQ_IPC_IMPH_SPARE_MIN                    (0)
  #define MPMCARB_CR_XTM_NTR_REQ_IPC_IMPH_SPARE_MAX                    (1) // 0x00000001
  #define MPMCARB_CR_XTM_NTR_REQ_IPC_IMPH_SPARE_DEF                    (0x00000000)
  #define MPMCARB_CR_XTM_NTR_REQ_IPC_IMPH_SPARE_HSH                    (0x010F7850)

#define MPMCARB_CR_XTM_IPC_GLOBAL_PACER_IMPH_REG                       (0x00007854)

  #define MPMCARB_CR_XTM_IPC_GLOBAL_PACER_IMPH_ISOCH_WINDOW_PH1_OFF    ( 0)
  #define MPMCARB_CR_XTM_IPC_GLOBAL_PACER_IMPH_ISOCH_WINDOW_PH1_WID    ( 5)
  #define MPMCARB_CR_XTM_IPC_GLOBAL_PACER_IMPH_ISOCH_WINDOW_PH1_MSK    (0x0000001F)
  #define MPMCARB_CR_XTM_IPC_GLOBAL_PACER_IMPH_ISOCH_WINDOW_PH1_MIN    (0)
  #define MPMCARB_CR_XTM_IPC_GLOBAL_PACER_IMPH_ISOCH_WINDOW_PH1_MAX    (31) // 0x0000001F
  #define MPMCARB_CR_XTM_IPC_GLOBAL_PACER_IMPH_ISOCH_WINDOW_PH1_DEF    (0x00000008)
  #define MPMCARB_CR_XTM_IPC_GLOBAL_PACER_IMPH_ISOCH_WINDOW_PH1_HSH    (0x05007854)

  #define MPMCARB_CR_XTM_IPC_GLOBAL_PACER_IMPH_ISOCH_WINDOW_PH2_OFF    ( 5)
  #define MPMCARB_CR_XTM_IPC_GLOBAL_PACER_IMPH_ISOCH_WINDOW_PH2_WID    ( 5)
  #define MPMCARB_CR_XTM_IPC_GLOBAL_PACER_IMPH_ISOCH_WINDOW_PH2_MSK    (0x000003E0)
  #define MPMCARB_CR_XTM_IPC_GLOBAL_PACER_IMPH_ISOCH_WINDOW_PH2_MIN    (0)
  #define MPMCARB_CR_XTM_IPC_GLOBAL_PACER_IMPH_ISOCH_WINDOW_PH2_MAX    (31) // 0x0000001F
  #define MPMCARB_CR_XTM_IPC_GLOBAL_PACER_IMPH_ISOCH_WINDOW_PH2_DEF    (0x00000008)
  #define MPMCARB_CR_XTM_IPC_GLOBAL_PACER_IMPH_ISOCH_WINDOW_PH2_HSH    (0x05057854)

  #define MPMCARB_CR_XTM_IPC_GLOBAL_PACER_IMPH_NON_ISOCH_WINDOW_PH1_OFF (10)
  #define MPMCARB_CR_XTM_IPC_GLOBAL_PACER_IMPH_NON_ISOCH_WINDOW_PH1_WID ( 5)
  #define MPMCARB_CR_XTM_IPC_GLOBAL_PACER_IMPH_NON_ISOCH_WINDOW_PH1_MSK (0x00007C00)
  #define MPMCARB_CR_XTM_IPC_GLOBAL_PACER_IMPH_NON_ISOCH_WINDOW_PH1_MIN (0)
  #define MPMCARB_CR_XTM_IPC_GLOBAL_PACER_IMPH_NON_ISOCH_WINDOW_PH1_MAX (31) // 0x0000001F
  #define MPMCARB_CR_XTM_IPC_GLOBAL_PACER_IMPH_NON_ISOCH_WINDOW_PH1_DEF (0x00000008)
  #define MPMCARB_CR_XTM_IPC_GLOBAL_PACER_IMPH_NON_ISOCH_WINDOW_PH1_HSH (0x050A7854)

  #define MPMCARB_CR_XTM_IPC_GLOBAL_PACER_IMPH_NON_ISOCH_WINDOW_PH2_OFF (15)
  #define MPMCARB_CR_XTM_IPC_GLOBAL_PACER_IMPH_NON_ISOCH_WINDOW_PH2_WID ( 5)
  #define MPMCARB_CR_XTM_IPC_GLOBAL_PACER_IMPH_NON_ISOCH_WINDOW_PH2_MSK (0x000F8000)
  #define MPMCARB_CR_XTM_IPC_GLOBAL_PACER_IMPH_NON_ISOCH_WINDOW_PH2_MIN (0)
  #define MPMCARB_CR_XTM_IPC_GLOBAL_PACER_IMPH_NON_ISOCH_WINDOW_PH2_MAX (31) // 0x0000001F
  #define MPMCARB_CR_XTM_IPC_GLOBAL_PACER_IMPH_NON_ISOCH_WINDOW_PH2_DEF (0x00000008)
  #define MPMCARB_CR_XTM_IPC_GLOBAL_PACER_IMPH_NON_ISOCH_WINDOW_PH2_HSH (0x050F7854)

  #define MPMCARB_CR_XTM_IPC_GLOBAL_PACER_IMPH_FORCE_DMI_VC1_DEMOTE_OFF (20)
  #define MPMCARB_CR_XTM_IPC_GLOBAL_PACER_IMPH_FORCE_DMI_VC1_DEMOTE_WID ( 1)
  #define MPMCARB_CR_XTM_IPC_GLOBAL_PACER_IMPH_FORCE_DMI_VC1_DEMOTE_MSK (0x00100000)
  #define MPMCARB_CR_XTM_IPC_GLOBAL_PACER_IMPH_FORCE_DMI_VC1_DEMOTE_MIN (0)
  #define MPMCARB_CR_XTM_IPC_GLOBAL_PACER_IMPH_FORCE_DMI_VC1_DEMOTE_MAX (1) // 0x00000001
  #define MPMCARB_CR_XTM_IPC_GLOBAL_PACER_IMPH_FORCE_DMI_VC1_DEMOTE_DEF (0x00000000)
  #define MPMCARB_CR_XTM_IPC_GLOBAL_PACER_IMPH_FORCE_DMI_VC1_DEMOTE_HSH (0x01147854)

  #define MPMCARB_CR_XTM_IPC_GLOBAL_PACER_IMPH_IGNORE_IOSF_VC1_DEMOTE_OFF (21)
  #define MPMCARB_CR_XTM_IPC_GLOBAL_PACER_IMPH_IGNORE_IOSF_VC1_DEMOTE_WID ( 1)
  #define MPMCARB_CR_XTM_IPC_GLOBAL_PACER_IMPH_IGNORE_IOSF_VC1_DEMOTE_MSK (0x00200000)
  #define MPMCARB_CR_XTM_IPC_GLOBAL_PACER_IMPH_IGNORE_IOSF_VC1_DEMOTE_MIN (0)
  #define MPMCARB_CR_XTM_IPC_GLOBAL_PACER_IMPH_IGNORE_IOSF_VC1_DEMOTE_MAX (1) // 0x00000001
  #define MPMCARB_CR_XTM_IPC_GLOBAL_PACER_IMPH_IGNORE_IOSF_VC1_DEMOTE_DEF (0x00000000)
  #define MPMCARB_CR_XTM_IPC_GLOBAL_PACER_IMPH_IGNORE_IOSF_VC1_DEMOTE_HSH (0x01157854)

  #define MPMCARB_CR_XTM_IPC_GLOBAL_PACER_IMPH_FORCE_VC1_DEMOTE_OFF    (22)
  #define MPMCARB_CR_XTM_IPC_GLOBAL_PACER_IMPH_FORCE_VC1_DEMOTE_WID    ( 1)
  #define MPMCARB_CR_XTM_IPC_GLOBAL_PACER_IMPH_FORCE_VC1_DEMOTE_MSK    (0x00400000)
  #define MPMCARB_CR_XTM_IPC_GLOBAL_PACER_IMPH_FORCE_VC1_DEMOTE_MIN    (0)
  #define MPMCARB_CR_XTM_IPC_GLOBAL_PACER_IMPH_FORCE_VC1_DEMOTE_MAX    (1) // 0x00000001
  #define MPMCARB_CR_XTM_IPC_GLOBAL_PACER_IMPH_FORCE_VC1_DEMOTE_DEF    (0x00000000)
  #define MPMCARB_CR_XTM_IPC_GLOBAL_PACER_IMPH_FORCE_VC1_DEMOTE_HSH    (0x01167854)

  #define MPMCARB_CR_XTM_IPC_GLOBAL_PACER_IMPH_IGNORE_VC1_DEMOTE_OFF   (23)
  #define MPMCARB_CR_XTM_IPC_GLOBAL_PACER_IMPH_IGNORE_VC1_DEMOTE_WID   ( 1)
  #define MPMCARB_CR_XTM_IPC_GLOBAL_PACER_IMPH_IGNORE_VC1_DEMOTE_MSK   (0x00800000)
  #define MPMCARB_CR_XTM_IPC_GLOBAL_PACER_IMPH_IGNORE_VC1_DEMOTE_MIN   (0)
  #define MPMCARB_CR_XTM_IPC_GLOBAL_PACER_IMPH_IGNORE_VC1_DEMOTE_MAX   (1) // 0x00000001
  #define MPMCARB_CR_XTM_IPC_GLOBAL_PACER_IMPH_IGNORE_VC1_DEMOTE_DEF   (0x00000000)
  #define MPMCARB_CR_XTM_IPC_GLOBAL_PACER_IMPH_IGNORE_VC1_DEMOTE_HSH   (0x01177854)

  #define MPMCARB_CR_XTM_IPC_GLOBAL_PACER_IMPH_SPARE_OFF               (24)
  #define MPMCARB_CR_XTM_IPC_GLOBAL_PACER_IMPH_SPARE_WID               ( 8)
  #define MPMCARB_CR_XTM_IPC_GLOBAL_PACER_IMPH_SPARE_MSK               (0xFF000000)
  #define MPMCARB_CR_XTM_IPC_GLOBAL_PACER_IMPH_SPARE_MIN               (0)
  #define MPMCARB_CR_XTM_IPC_GLOBAL_PACER_IMPH_SPARE_MAX               (255) // 0x000000FF
  #define MPMCARB_CR_XTM_IPC_GLOBAL_PACER_IMPH_SPARE_DEF               (0x00000000)
  #define MPMCARB_CR_XTM_IPC_GLOBAL_PACER_IMPH_SPARE_HSH               (0x08187854)

#define MPMCARB_CR_MCARBLCK_IMPH_REG                                   (0x00007BFC)

  #define MPMCARB_CR_MCARBLCK_IMPH_LOCK_OFF                            ( 0)
  #define MPMCARB_CR_MCARBLCK_IMPH_LOCK_WID                            ( 1)
  #define MPMCARB_CR_MCARBLCK_IMPH_LOCK_MSK                            (0x00000001)
  #define MPMCARB_CR_MCARBLCK_IMPH_LOCK_MIN                            (0)
  #define MPMCARB_CR_MCARBLCK_IMPH_LOCK_MAX                            (1) // 0x00000001
  #define MPMCARB_CR_MCARBLCK_IMPH_LOCK_DEF                            (0x00000000)
  #define MPMCARB_CR_MCARBLCK_IMPH_LOCK_HSH                            (0x01007BFC)

#define MEECR_CR_VISA_CTL_MEDEC_MEE_REG                                (0x00007DB0)

  #define MEECR_CR_VISA_CTL_MEDEC_MEE_EN_CLK_OFF                       ( 0)
  #define MEECR_CR_VISA_CTL_MEDEC_MEE_EN_CLK_WID                       ( 1)
  #define MEECR_CR_VISA_CTL_MEDEC_MEE_EN_CLK_MSK                       (0x00000001)
  #define MEECR_CR_VISA_CTL_MEDEC_MEE_EN_CLK_MIN                       (0)
  #define MEECR_CR_VISA_CTL_MEDEC_MEE_EN_CLK_MAX                       (1) // 0x00000001
  #define MEECR_CR_VISA_CTL_MEDEC_MEE_EN_CLK_DEF                       (0x00000000)
  #define MEECR_CR_VISA_CTL_MEDEC_MEE_EN_CLK_HSH                       (0x01007DB0)

  #define MEECR_CR_VISA_CTL_MEDEC_MEE_L0_DATA_BYTE_SEL_OFF             ( 1)
  #define MEECR_CR_VISA_CTL_MEDEC_MEE_L0_DATA_BYTE_SEL_WID             ( 7)
  #define MEECR_CR_VISA_CTL_MEDEC_MEE_L0_DATA_BYTE_SEL_MSK             (0x000000FE)
  #define MEECR_CR_VISA_CTL_MEDEC_MEE_L0_DATA_BYTE_SEL_MIN             (0)
  #define MEECR_CR_VISA_CTL_MEDEC_MEE_L0_DATA_BYTE_SEL_MAX             (127) // 0x0000007F
  #define MEECR_CR_VISA_CTL_MEDEC_MEE_L0_DATA_BYTE_SEL_DEF             (0x00000000)
  #define MEECR_CR_VISA_CTL_MEDEC_MEE_L0_DATA_BYTE_SEL_HSH             (0x07017DB0)

  #define MEECR_CR_VISA_CTL_MEDEC_MEE_L0_BYP_SEL_OFF                   ( 8)
  #define MEECR_CR_VISA_CTL_MEDEC_MEE_L0_BYP_SEL_WID                   ( 1)
  #define MEECR_CR_VISA_CTL_MEDEC_MEE_L0_BYP_SEL_MSK                   (0x00000100)
  #define MEECR_CR_VISA_CTL_MEDEC_MEE_L0_BYP_SEL_MIN                   (0)
  #define MEECR_CR_VISA_CTL_MEDEC_MEE_L0_BYP_SEL_MAX                   (1) // 0x00000001
  #define MEECR_CR_VISA_CTL_MEDEC_MEE_L0_BYP_SEL_DEF                   (0x00000000)
  #define MEECR_CR_VISA_CTL_MEDEC_MEE_L0_BYP_SEL_HSH                   (0x01087DB0)

  #define MEECR_CR_VISA_CTL_MEDEC_MEE_L1_DATA_BYTE_SEL_OFF             ( 9)
  #define MEECR_CR_VISA_CTL_MEDEC_MEE_L1_DATA_BYTE_SEL_WID             ( 7)
  #define MEECR_CR_VISA_CTL_MEDEC_MEE_L1_DATA_BYTE_SEL_MSK             (0x0000FE00)
  #define MEECR_CR_VISA_CTL_MEDEC_MEE_L1_DATA_BYTE_SEL_MIN             (0)
  #define MEECR_CR_VISA_CTL_MEDEC_MEE_L1_DATA_BYTE_SEL_MAX             (127) // 0x0000007F
  #define MEECR_CR_VISA_CTL_MEDEC_MEE_L1_DATA_BYTE_SEL_DEF             (0x00000000)
  #define MEECR_CR_VISA_CTL_MEDEC_MEE_L1_DATA_BYTE_SEL_HSH             (0x07097DB0)

  #define MEECR_CR_VISA_CTL_MEDEC_MEE_L1_BYP_SEL_OFF                   (16)
  #define MEECR_CR_VISA_CTL_MEDEC_MEE_L1_BYP_SEL_WID                   ( 1)
  #define MEECR_CR_VISA_CTL_MEDEC_MEE_L1_BYP_SEL_MSK                   (0x00010000)
  #define MEECR_CR_VISA_CTL_MEDEC_MEE_L1_BYP_SEL_MIN                   (0)
  #define MEECR_CR_VISA_CTL_MEDEC_MEE_L1_BYP_SEL_MAX                   (1) // 0x00000001
  #define MEECR_CR_VISA_CTL_MEDEC_MEE_L1_BYP_SEL_DEF                   (0x00000000)
  #define MEECR_CR_VISA_CTL_MEDEC_MEE_L1_BYP_SEL_HSH                   (0x01107DB0)

  #define MEECR_CR_VISA_CTL_MEDEC_MEE_VORANGE_OFF                      (31)
  #define MEECR_CR_VISA_CTL_MEDEC_MEE_VORANGE_WID                      ( 1)
  #define MEECR_CR_VISA_CTL_MEDEC_MEE_VORANGE_MSK                      (0x80000000)
  #define MEECR_CR_VISA_CTL_MEDEC_MEE_VORANGE_MIN                      (0)
  #define MEECR_CR_VISA_CTL_MEDEC_MEE_VORANGE_MAX                      (1) // 0x00000001
  #define MEECR_CR_VISA_CTL_MEDEC_MEE_VORANGE_DEF                      (0x00000000)
  #define MEECR_CR_VISA_CTL_MEDEC_MEE_VORANGE_HSH                      (0x011F7DB0)

#define MEECR_CR_VISA_XBAR_MEDEC_MEE_REG                               (0x00007DB4)

  #define MEECR_CR_VISA_XBAR_MEDEC_MEE_FXB_Li_BIT0_DATA_BIT_SEL_OFF    ( 0)
  #define MEECR_CR_VISA_XBAR_MEDEC_MEE_FXB_Li_BIT0_DATA_BIT_SEL_WID    ( 3)
  #define MEECR_CR_VISA_XBAR_MEDEC_MEE_FXB_Li_BIT0_DATA_BIT_SEL_MSK    (0x00000007)
  #define MEECR_CR_VISA_XBAR_MEDEC_MEE_FXB_Li_BIT0_DATA_BIT_SEL_MIN    (0)
  #define MEECR_CR_VISA_XBAR_MEDEC_MEE_FXB_Li_BIT0_DATA_BIT_SEL_MAX    (7) // 0x00000007
  #define MEECR_CR_VISA_XBAR_MEDEC_MEE_FXB_Li_BIT0_DATA_BIT_SEL_DEF    (0x00000000)
  #define MEECR_CR_VISA_XBAR_MEDEC_MEE_FXB_Li_BIT0_DATA_BIT_SEL_HSH    (0x03007DB4)

  #define MEECR_CR_VISA_XBAR_MEDEC_MEE_FXB_Li_BIT0_DATA_BYTE_SEL_OFF   ( 3)
  #define MEECR_CR_VISA_XBAR_MEDEC_MEE_FXB_Li_BIT0_DATA_BYTE_SEL_WID   ( 1)
  #define MEECR_CR_VISA_XBAR_MEDEC_MEE_FXB_Li_BIT0_DATA_BYTE_SEL_MSK   (0x00000008)
  #define MEECR_CR_VISA_XBAR_MEDEC_MEE_FXB_Li_BIT0_DATA_BYTE_SEL_MIN   (0)
  #define MEECR_CR_VISA_XBAR_MEDEC_MEE_FXB_Li_BIT0_DATA_BYTE_SEL_MAX   (1) // 0x00000001
  #define MEECR_CR_VISA_XBAR_MEDEC_MEE_FXB_Li_BIT0_DATA_BYTE_SEL_DEF   (0x00000000)
  #define MEECR_CR_VISA_XBAR_MEDEC_MEE_FXB_Li_BIT0_DATA_BYTE_SEL_HSH   (0x01037DB4)

  #define MEECR_CR_VISA_XBAR_MEDEC_MEE_FXB_Li_BIT1_DATA_BIT_SEL_OFF    ( 4)
  #define MEECR_CR_VISA_XBAR_MEDEC_MEE_FXB_Li_BIT1_DATA_BIT_SEL_WID    ( 3)
  #define MEECR_CR_VISA_XBAR_MEDEC_MEE_FXB_Li_BIT1_DATA_BIT_SEL_MSK    (0x00000070)
  #define MEECR_CR_VISA_XBAR_MEDEC_MEE_FXB_Li_BIT1_DATA_BIT_SEL_MIN    (0)
  #define MEECR_CR_VISA_XBAR_MEDEC_MEE_FXB_Li_BIT1_DATA_BIT_SEL_MAX    (7) // 0x00000007
  #define MEECR_CR_VISA_XBAR_MEDEC_MEE_FXB_Li_BIT1_DATA_BIT_SEL_DEF    (0x00000001)
  #define MEECR_CR_VISA_XBAR_MEDEC_MEE_FXB_Li_BIT1_DATA_BIT_SEL_HSH    (0x03047DB4)

  #define MEECR_CR_VISA_XBAR_MEDEC_MEE_FXB_Li_BIT1_DATA_BYTE_SEL_OFF   ( 7)
  #define MEECR_CR_VISA_XBAR_MEDEC_MEE_FXB_Li_BIT1_DATA_BYTE_SEL_WID   ( 1)
  #define MEECR_CR_VISA_XBAR_MEDEC_MEE_FXB_Li_BIT1_DATA_BYTE_SEL_MSK   (0x00000080)
  #define MEECR_CR_VISA_XBAR_MEDEC_MEE_FXB_Li_BIT1_DATA_BYTE_SEL_MIN   (0)
  #define MEECR_CR_VISA_XBAR_MEDEC_MEE_FXB_Li_BIT1_DATA_BYTE_SEL_MAX   (1) // 0x00000001
  #define MEECR_CR_VISA_XBAR_MEDEC_MEE_FXB_Li_BIT1_DATA_BYTE_SEL_DEF   (0x00000000)
  #define MEECR_CR_VISA_XBAR_MEDEC_MEE_FXB_Li_BIT1_DATA_BYTE_SEL_HSH   (0x01077DB4)

  #define MEECR_CR_VISA_XBAR_MEDEC_MEE_FXB_Li_BIT2_DATA_BIT_SEL_OFF    ( 8)
  #define MEECR_CR_VISA_XBAR_MEDEC_MEE_FXB_Li_BIT2_DATA_BIT_SEL_WID    ( 3)
  #define MEECR_CR_VISA_XBAR_MEDEC_MEE_FXB_Li_BIT2_DATA_BIT_SEL_MSK    (0x00000700)
  #define MEECR_CR_VISA_XBAR_MEDEC_MEE_FXB_Li_BIT2_DATA_BIT_SEL_MIN    (0)
  #define MEECR_CR_VISA_XBAR_MEDEC_MEE_FXB_Li_BIT2_DATA_BIT_SEL_MAX    (7) // 0x00000007
  #define MEECR_CR_VISA_XBAR_MEDEC_MEE_FXB_Li_BIT2_DATA_BIT_SEL_DEF    (0x00000002)
  #define MEECR_CR_VISA_XBAR_MEDEC_MEE_FXB_Li_BIT2_DATA_BIT_SEL_HSH    (0x03087DB4)

  #define MEECR_CR_VISA_XBAR_MEDEC_MEE_FXB_Li_BIT2_DATA_BYTE_SEL_OFF   (11)
  #define MEECR_CR_VISA_XBAR_MEDEC_MEE_FXB_Li_BIT2_DATA_BYTE_SEL_WID   ( 1)
  #define MEECR_CR_VISA_XBAR_MEDEC_MEE_FXB_Li_BIT2_DATA_BYTE_SEL_MSK   (0x00000800)
  #define MEECR_CR_VISA_XBAR_MEDEC_MEE_FXB_Li_BIT2_DATA_BYTE_SEL_MIN   (0)
  #define MEECR_CR_VISA_XBAR_MEDEC_MEE_FXB_Li_BIT2_DATA_BYTE_SEL_MAX   (1) // 0x00000001
  #define MEECR_CR_VISA_XBAR_MEDEC_MEE_FXB_Li_BIT2_DATA_BYTE_SEL_DEF   (0x00000000)
  #define MEECR_CR_VISA_XBAR_MEDEC_MEE_FXB_Li_BIT2_DATA_BYTE_SEL_HSH   (0x010B7DB4)

  #define MEECR_CR_VISA_XBAR_MEDEC_MEE_FXB_Li_BIT3_DATA_BIT_SEL_OFF    (12)
  #define MEECR_CR_VISA_XBAR_MEDEC_MEE_FXB_Li_BIT3_DATA_BIT_SEL_WID    ( 3)
  #define MEECR_CR_VISA_XBAR_MEDEC_MEE_FXB_Li_BIT3_DATA_BIT_SEL_MSK    (0x00007000)
  #define MEECR_CR_VISA_XBAR_MEDEC_MEE_FXB_Li_BIT3_DATA_BIT_SEL_MIN    (0)
  #define MEECR_CR_VISA_XBAR_MEDEC_MEE_FXB_Li_BIT3_DATA_BIT_SEL_MAX    (7) // 0x00000007
  #define MEECR_CR_VISA_XBAR_MEDEC_MEE_FXB_Li_BIT3_DATA_BIT_SEL_DEF    (0x00000003)
  #define MEECR_CR_VISA_XBAR_MEDEC_MEE_FXB_Li_BIT3_DATA_BIT_SEL_HSH    (0x030C7DB4)

  #define MEECR_CR_VISA_XBAR_MEDEC_MEE_FXB_Li_BIT3_DATA_BYTE_SEL_OFF   (15)
  #define MEECR_CR_VISA_XBAR_MEDEC_MEE_FXB_Li_BIT3_DATA_BYTE_SEL_WID   ( 1)
  #define MEECR_CR_VISA_XBAR_MEDEC_MEE_FXB_Li_BIT3_DATA_BYTE_SEL_MSK   (0x00008000)
  #define MEECR_CR_VISA_XBAR_MEDEC_MEE_FXB_Li_BIT3_DATA_BYTE_SEL_MIN   (0)
  #define MEECR_CR_VISA_XBAR_MEDEC_MEE_FXB_Li_BIT3_DATA_BYTE_SEL_MAX   (1) // 0x00000001
  #define MEECR_CR_VISA_XBAR_MEDEC_MEE_FXB_Li_BIT3_DATA_BYTE_SEL_DEF   (0x00000000)
  #define MEECR_CR_VISA_XBAR_MEDEC_MEE_FXB_Li_BIT3_DATA_BYTE_SEL_HSH   (0x010F7DB4)

  #define MEECR_CR_VISA_XBAR_MEDEC_MEE_FXB_Li_BIT4_DATA_BIT_SEL_OFF    (16)
  #define MEECR_CR_VISA_XBAR_MEDEC_MEE_FXB_Li_BIT4_DATA_BIT_SEL_WID    ( 3)
  #define MEECR_CR_VISA_XBAR_MEDEC_MEE_FXB_Li_BIT4_DATA_BIT_SEL_MSK    (0x00070000)
  #define MEECR_CR_VISA_XBAR_MEDEC_MEE_FXB_Li_BIT4_DATA_BIT_SEL_MIN    (0)
  #define MEECR_CR_VISA_XBAR_MEDEC_MEE_FXB_Li_BIT4_DATA_BIT_SEL_MAX    (7) // 0x00000007
  #define MEECR_CR_VISA_XBAR_MEDEC_MEE_FXB_Li_BIT4_DATA_BIT_SEL_DEF    (0x00000004)
  #define MEECR_CR_VISA_XBAR_MEDEC_MEE_FXB_Li_BIT4_DATA_BIT_SEL_HSH    (0x03107DB4)

  #define MEECR_CR_VISA_XBAR_MEDEC_MEE_FXB_Li_BIT4_DATA_BYTE_SEL_OFF   (19)
  #define MEECR_CR_VISA_XBAR_MEDEC_MEE_FXB_Li_BIT4_DATA_BYTE_SEL_WID   ( 1)
  #define MEECR_CR_VISA_XBAR_MEDEC_MEE_FXB_Li_BIT4_DATA_BYTE_SEL_MSK   (0x00080000)
  #define MEECR_CR_VISA_XBAR_MEDEC_MEE_FXB_Li_BIT4_DATA_BYTE_SEL_MIN   (0)
  #define MEECR_CR_VISA_XBAR_MEDEC_MEE_FXB_Li_BIT4_DATA_BYTE_SEL_MAX   (1) // 0x00000001
  #define MEECR_CR_VISA_XBAR_MEDEC_MEE_FXB_Li_BIT4_DATA_BYTE_SEL_DEF   (0x00000000)
  #define MEECR_CR_VISA_XBAR_MEDEC_MEE_FXB_Li_BIT4_DATA_BYTE_SEL_HSH   (0x01137DB4)

  #define MEECR_CR_VISA_XBAR_MEDEC_MEE_FXB_Li_BIT5_DATA_BIT_SEL_OFF    (20)
  #define MEECR_CR_VISA_XBAR_MEDEC_MEE_FXB_Li_BIT5_DATA_BIT_SEL_WID    ( 3)
  #define MEECR_CR_VISA_XBAR_MEDEC_MEE_FXB_Li_BIT5_DATA_BIT_SEL_MSK    (0x00700000)
  #define MEECR_CR_VISA_XBAR_MEDEC_MEE_FXB_Li_BIT5_DATA_BIT_SEL_MIN    (0)
  #define MEECR_CR_VISA_XBAR_MEDEC_MEE_FXB_Li_BIT5_DATA_BIT_SEL_MAX    (7) // 0x00000007
  #define MEECR_CR_VISA_XBAR_MEDEC_MEE_FXB_Li_BIT5_DATA_BIT_SEL_DEF    (0x00000005)
  #define MEECR_CR_VISA_XBAR_MEDEC_MEE_FXB_Li_BIT5_DATA_BIT_SEL_HSH    (0x03147DB4)

  #define MEECR_CR_VISA_XBAR_MEDEC_MEE_FXB_Li_BIT5_DATA_BYTE_SEL_OFF   (23)
  #define MEECR_CR_VISA_XBAR_MEDEC_MEE_FXB_Li_BIT5_DATA_BYTE_SEL_WID   ( 1)
  #define MEECR_CR_VISA_XBAR_MEDEC_MEE_FXB_Li_BIT5_DATA_BYTE_SEL_MSK   (0x00800000)
  #define MEECR_CR_VISA_XBAR_MEDEC_MEE_FXB_Li_BIT5_DATA_BYTE_SEL_MIN   (0)
  #define MEECR_CR_VISA_XBAR_MEDEC_MEE_FXB_Li_BIT5_DATA_BYTE_SEL_MAX   (1) // 0x00000001
  #define MEECR_CR_VISA_XBAR_MEDEC_MEE_FXB_Li_BIT5_DATA_BYTE_SEL_DEF   (0x00000000)
  #define MEECR_CR_VISA_XBAR_MEDEC_MEE_FXB_Li_BIT5_DATA_BYTE_SEL_HSH   (0x01177DB4)

  #define MEECR_CR_VISA_XBAR_MEDEC_MEE_FXB_Li_BIT6_DATA_BIT_SEL_OFF    (24)
  #define MEECR_CR_VISA_XBAR_MEDEC_MEE_FXB_Li_BIT6_DATA_BIT_SEL_WID    ( 3)
  #define MEECR_CR_VISA_XBAR_MEDEC_MEE_FXB_Li_BIT6_DATA_BIT_SEL_MSK    (0x07000000)
  #define MEECR_CR_VISA_XBAR_MEDEC_MEE_FXB_Li_BIT6_DATA_BIT_SEL_MIN    (0)
  #define MEECR_CR_VISA_XBAR_MEDEC_MEE_FXB_Li_BIT6_DATA_BIT_SEL_MAX    (7) // 0x00000007
  #define MEECR_CR_VISA_XBAR_MEDEC_MEE_FXB_Li_BIT6_DATA_BIT_SEL_DEF    (0x00000006)
  #define MEECR_CR_VISA_XBAR_MEDEC_MEE_FXB_Li_BIT6_DATA_BIT_SEL_HSH    (0x03187DB4)

  #define MEECR_CR_VISA_XBAR_MEDEC_MEE_FXB_Li_BIT6_DATA_BYTE_SEL_OFF   (27)
  #define MEECR_CR_VISA_XBAR_MEDEC_MEE_FXB_Li_BIT6_DATA_BYTE_SEL_WID   ( 1)
  #define MEECR_CR_VISA_XBAR_MEDEC_MEE_FXB_Li_BIT6_DATA_BYTE_SEL_MSK   (0x08000000)
  #define MEECR_CR_VISA_XBAR_MEDEC_MEE_FXB_Li_BIT6_DATA_BYTE_SEL_MIN   (0)
  #define MEECR_CR_VISA_XBAR_MEDEC_MEE_FXB_Li_BIT6_DATA_BYTE_SEL_MAX   (1) // 0x00000001
  #define MEECR_CR_VISA_XBAR_MEDEC_MEE_FXB_Li_BIT6_DATA_BYTE_SEL_DEF   (0x00000000)
  #define MEECR_CR_VISA_XBAR_MEDEC_MEE_FXB_Li_BIT6_DATA_BYTE_SEL_HSH   (0x011B7DB4)

  #define MEECR_CR_VISA_XBAR_MEDEC_MEE_FXB_Li_BIT7_DATA_BIT_SEL_OFF    (28)
  #define MEECR_CR_VISA_XBAR_MEDEC_MEE_FXB_Li_BIT7_DATA_BIT_SEL_WID    ( 3)
  #define MEECR_CR_VISA_XBAR_MEDEC_MEE_FXB_Li_BIT7_DATA_BIT_SEL_MSK    (0x70000000)
  #define MEECR_CR_VISA_XBAR_MEDEC_MEE_FXB_Li_BIT7_DATA_BIT_SEL_MIN    (0)
  #define MEECR_CR_VISA_XBAR_MEDEC_MEE_FXB_Li_BIT7_DATA_BIT_SEL_MAX    (7) // 0x00000007
  #define MEECR_CR_VISA_XBAR_MEDEC_MEE_FXB_Li_BIT7_DATA_BIT_SEL_DEF    (0x00000007)
  #define MEECR_CR_VISA_XBAR_MEDEC_MEE_FXB_Li_BIT7_DATA_BIT_SEL_HSH    (0x031C7DB4)

  #define MEECR_CR_VISA_XBAR_MEDEC_MEE_FXB_Li_BIT7_DATA_BYTE_SEL_OFF   (31)
  #define MEECR_CR_VISA_XBAR_MEDEC_MEE_FXB_Li_BIT7_DATA_BYTE_SEL_WID   ( 1)
  #define MEECR_CR_VISA_XBAR_MEDEC_MEE_FXB_Li_BIT7_DATA_BYTE_SEL_MSK   (0x80000000)
  #define MEECR_CR_VISA_XBAR_MEDEC_MEE_FXB_Li_BIT7_DATA_BYTE_SEL_MIN   (0)
  #define MEECR_CR_VISA_XBAR_MEDEC_MEE_FXB_Li_BIT7_DATA_BYTE_SEL_MAX   (1) // 0x00000001
  #define MEECR_CR_VISA_XBAR_MEDEC_MEE_FXB_Li_BIT7_DATA_BYTE_SEL_DEF   (0x00000000)
  #define MEECR_CR_VISA_XBAR_MEDEC_MEE_FXB_Li_BIT7_DATA_BYTE_SEL_HSH   (0x011F7DB4)

#define MEECR_CR_VISA_SLIDE_MEDEC_MEE_REG                              (0x00007DB8)

  #define MEECR_CR_VISA_SLIDE_MEDEC_MEE_WINDOW_SLIDE_L0_OFF            ( 0)
  #define MEECR_CR_VISA_SLIDE_MEDEC_MEE_WINDOW_SLIDE_L0_WID            ( 3)
  #define MEECR_CR_VISA_SLIDE_MEDEC_MEE_WINDOW_SLIDE_L0_MSK            (0x00000007)
  #define MEECR_CR_VISA_SLIDE_MEDEC_MEE_WINDOW_SLIDE_L0_MIN            (0)
  #define MEECR_CR_VISA_SLIDE_MEDEC_MEE_WINDOW_SLIDE_L0_MAX            (7) // 0x00000007
  #define MEECR_CR_VISA_SLIDE_MEDEC_MEE_WINDOW_SLIDE_L0_DEF            (0x00000000)
  #define MEECR_CR_VISA_SLIDE_MEDEC_MEE_WINDOW_SLIDE_L0_HSH            (0x03007DB8)

  #define MEECR_CR_VISA_SLIDE_MEDEC_MEE_ALT_L0_DATA_BYTE_SEL_OFF       ( 3)
  #define MEECR_CR_VISA_SLIDE_MEDEC_MEE_ALT_L0_DATA_BYTE_SEL_WID       ( 7)
  #define MEECR_CR_VISA_SLIDE_MEDEC_MEE_ALT_L0_DATA_BYTE_SEL_MSK       (0x000003F8)
  #define MEECR_CR_VISA_SLIDE_MEDEC_MEE_ALT_L0_DATA_BYTE_SEL_MIN       (0)
  #define MEECR_CR_VISA_SLIDE_MEDEC_MEE_ALT_L0_DATA_BYTE_SEL_MAX       (127) // 0x0000007F
  #define MEECR_CR_VISA_SLIDE_MEDEC_MEE_ALT_L0_DATA_BYTE_SEL_DEF       (0x00000000)
  #define MEECR_CR_VISA_SLIDE_MEDEC_MEE_ALT_L0_DATA_BYTE_SEL_HSH       (0x07037DB8)

  #define MEECR_CR_VISA_SLIDE_MEDEC_MEE_WINDOW_SLIDE_L1_OFF            (10)
  #define MEECR_CR_VISA_SLIDE_MEDEC_MEE_WINDOW_SLIDE_L1_WID            ( 3)
  #define MEECR_CR_VISA_SLIDE_MEDEC_MEE_WINDOW_SLIDE_L1_MSK            (0x00001C00)
  #define MEECR_CR_VISA_SLIDE_MEDEC_MEE_WINDOW_SLIDE_L1_MIN            (0)
  #define MEECR_CR_VISA_SLIDE_MEDEC_MEE_WINDOW_SLIDE_L1_MAX            (7) // 0x00000007
  #define MEECR_CR_VISA_SLIDE_MEDEC_MEE_WINDOW_SLIDE_L1_DEF            (0x00000000)
  #define MEECR_CR_VISA_SLIDE_MEDEC_MEE_WINDOW_SLIDE_L1_HSH            (0x030A7DB8)

  #define MEECR_CR_VISA_SLIDE_MEDEC_MEE_ALT_L1_DATA_BYTE_SEL_OFF       (13)
  #define MEECR_CR_VISA_SLIDE_MEDEC_MEE_ALT_L1_DATA_BYTE_SEL_WID       ( 7)
  #define MEECR_CR_VISA_SLIDE_MEDEC_MEE_ALT_L1_DATA_BYTE_SEL_MSK       (0x000FE000)
  #define MEECR_CR_VISA_SLIDE_MEDEC_MEE_ALT_L1_DATA_BYTE_SEL_MIN       (0)
  #define MEECR_CR_VISA_SLIDE_MEDEC_MEE_ALT_L1_DATA_BYTE_SEL_MAX       (127) // 0x0000007F
  #define MEECR_CR_VISA_SLIDE_MEDEC_MEE_ALT_L1_DATA_BYTE_SEL_DEF       (0x00000000)
  #define MEECR_CR_VISA_SLIDE_MEDEC_MEE_ALT_L1_DATA_BYTE_SEL_HSH       (0x070D7DB8)

#define MEECR_CR_VISA_CTL_MEENC_MEE_REG                                (0x00007DC0)

  #define MEECR_CR_VISA_CTL_MEENC_MEE_EN_CLK_OFF                       ( 0)
  #define MEECR_CR_VISA_CTL_MEENC_MEE_EN_CLK_WID                       ( 1)
  #define MEECR_CR_VISA_CTL_MEENC_MEE_EN_CLK_MSK                       (0x00000001)
  #define MEECR_CR_VISA_CTL_MEENC_MEE_EN_CLK_MIN                       (0)
  #define MEECR_CR_VISA_CTL_MEENC_MEE_EN_CLK_MAX                       (1) // 0x00000001
  #define MEECR_CR_VISA_CTL_MEENC_MEE_EN_CLK_DEF                       (0x00000000)
  #define MEECR_CR_VISA_CTL_MEENC_MEE_EN_CLK_HSH                       (0x01007DC0)

  #define MEECR_CR_VISA_CTL_MEENC_MEE_L0_DATA_BYTE_SEL_OFF             ( 1)
  #define MEECR_CR_VISA_CTL_MEENC_MEE_L0_DATA_BYTE_SEL_WID             ( 7)
  #define MEECR_CR_VISA_CTL_MEENC_MEE_L0_DATA_BYTE_SEL_MSK             (0x000000FE)
  #define MEECR_CR_VISA_CTL_MEENC_MEE_L0_DATA_BYTE_SEL_MIN             (0)
  #define MEECR_CR_VISA_CTL_MEENC_MEE_L0_DATA_BYTE_SEL_MAX             (127) // 0x0000007F
  #define MEECR_CR_VISA_CTL_MEENC_MEE_L0_DATA_BYTE_SEL_DEF             (0x00000000)
  #define MEECR_CR_VISA_CTL_MEENC_MEE_L0_DATA_BYTE_SEL_HSH             (0x07017DC0)

  #define MEECR_CR_VISA_CTL_MEENC_MEE_L0_BYP_SEL_OFF                   ( 8)
  #define MEECR_CR_VISA_CTL_MEENC_MEE_L0_BYP_SEL_WID                   ( 1)
  #define MEECR_CR_VISA_CTL_MEENC_MEE_L0_BYP_SEL_MSK                   (0x00000100)
  #define MEECR_CR_VISA_CTL_MEENC_MEE_L0_BYP_SEL_MIN                   (0)
  #define MEECR_CR_VISA_CTL_MEENC_MEE_L0_BYP_SEL_MAX                   (1) // 0x00000001
  #define MEECR_CR_VISA_CTL_MEENC_MEE_L0_BYP_SEL_DEF                   (0x00000000)
  #define MEECR_CR_VISA_CTL_MEENC_MEE_L0_BYP_SEL_HSH                   (0x01087DC0)

  #define MEECR_CR_VISA_CTL_MEENC_MEE_L1_DATA_BYTE_SEL_OFF             ( 9)
  #define MEECR_CR_VISA_CTL_MEENC_MEE_L1_DATA_BYTE_SEL_WID             ( 7)
  #define MEECR_CR_VISA_CTL_MEENC_MEE_L1_DATA_BYTE_SEL_MSK             (0x0000FE00)
  #define MEECR_CR_VISA_CTL_MEENC_MEE_L1_DATA_BYTE_SEL_MIN             (0)
  #define MEECR_CR_VISA_CTL_MEENC_MEE_L1_DATA_BYTE_SEL_MAX             (127) // 0x0000007F
  #define MEECR_CR_VISA_CTL_MEENC_MEE_L1_DATA_BYTE_SEL_DEF             (0x00000000)
  #define MEECR_CR_VISA_CTL_MEENC_MEE_L1_DATA_BYTE_SEL_HSH             (0x07097DC0)

  #define MEECR_CR_VISA_CTL_MEENC_MEE_L1_BYP_SEL_OFF                   (16)
  #define MEECR_CR_VISA_CTL_MEENC_MEE_L1_BYP_SEL_WID                   ( 1)
  #define MEECR_CR_VISA_CTL_MEENC_MEE_L1_BYP_SEL_MSK                   (0x00010000)
  #define MEECR_CR_VISA_CTL_MEENC_MEE_L1_BYP_SEL_MIN                   (0)
  #define MEECR_CR_VISA_CTL_MEENC_MEE_L1_BYP_SEL_MAX                   (1) // 0x00000001
  #define MEECR_CR_VISA_CTL_MEENC_MEE_L1_BYP_SEL_DEF                   (0x00000000)
  #define MEECR_CR_VISA_CTL_MEENC_MEE_L1_BYP_SEL_HSH                   (0x01107DC0)

  #define MEECR_CR_VISA_CTL_MEENC_MEE_VORANGE_OFF                      (31)
  #define MEECR_CR_VISA_CTL_MEENC_MEE_VORANGE_WID                      ( 1)
  #define MEECR_CR_VISA_CTL_MEENC_MEE_VORANGE_MSK                      (0x80000000)
  #define MEECR_CR_VISA_CTL_MEENC_MEE_VORANGE_MIN                      (0)
  #define MEECR_CR_VISA_CTL_MEENC_MEE_VORANGE_MAX                      (1) // 0x00000001
  #define MEECR_CR_VISA_CTL_MEENC_MEE_VORANGE_DEF                      (0x00000000)
  #define MEECR_CR_VISA_CTL_MEENC_MEE_VORANGE_HSH                      (0x011F7DC0)

#define MEECR_CR_VISA_XBAR_MEENC_MEE_REG                               (0x00007DC4)

  #define MEECR_CR_VISA_XBAR_MEENC_MEE_FXB_Li_BIT0_DATA_BIT_SEL_OFF    ( 0)
  #define MEECR_CR_VISA_XBAR_MEENC_MEE_FXB_Li_BIT0_DATA_BIT_SEL_WID    ( 3)
  #define MEECR_CR_VISA_XBAR_MEENC_MEE_FXB_Li_BIT0_DATA_BIT_SEL_MSK    (0x00000007)
  #define MEECR_CR_VISA_XBAR_MEENC_MEE_FXB_Li_BIT0_DATA_BIT_SEL_MIN    (0)
  #define MEECR_CR_VISA_XBAR_MEENC_MEE_FXB_Li_BIT0_DATA_BIT_SEL_MAX    (7) // 0x00000007
  #define MEECR_CR_VISA_XBAR_MEENC_MEE_FXB_Li_BIT0_DATA_BIT_SEL_DEF    (0x00000000)
  #define MEECR_CR_VISA_XBAR_MEENC_MEE_FXB_Li_BIT0_DATA_BIT_SEL_HSH    (0x03007DC4)

  #define MEECR_CR_VISA_XBAR_MEENC_MEE_FXB_Li_BIT0_DATA_BYTE_SEL_OFF   ( 3)
  #define MEECR_CR_VISA_XBAR_MEENC_MEE_FXB_Li_BIT0_DATA_BYTE_SEL_WID   ( 1)
  #define MEECR_CR_VISA_XBAR_MEENC_MEE_FXB_Li_BIT0_DATA_BYTE_SEL_MSK   (0x00000008)
  #define MEECR_CR_VISA_XBAR_MEENC_MEE_FXB_Li_BIT0_DATA_BYTE_SEL_MIN   (0)
  #define MEECR_CR_VISA_XBAR_MEENC_MEE_FXB_Li_BIT0_DATA_BYTE_SEL_MAX   (1) // 0x00000001
  #define MEECR_CR_VISA_XBAR_MEENC_MEE_FXB_Li_BIT0_DATA_BYTE_SEL_DEF   (0x00000000)
  #define MEECR_CR_VISA_XBAR_MEENC_MEE_FXB_Li_BIT0_DATA_BYTE_SEL_HSH   (0x01037DC4)

  #define MEECR_CR_VISA_XBAR_MEENC_MEE_FXB_Li_BIT1_DATA_BIT_SEL_OFF    ( 4)
  #define MEECR_CR_VISA_XBAR_MEENC_MEE_FXB_Li_BIT1_DATA_BIT_SEL_WID    ( 3)
  #define MEECR_CR_VISA_XBAR_MEENC_MEE_FXB_Li_BIT1_DATA_BIT_SEL_MSK    (0x00000070)
  #define MEECR_CR_VISA_XBAR_MEENC_MEE_FXB_Li_BIT1_DATA_BIT_SEL_MIN    (0)
  #define MEECR_CR_VISA_XBAR_MEENC_MEE_FXB_Li_BIT1_DATA_BIT_SEL_MAX    (7) // 0x00000007
  #define MEECR_CR_VISA_XBAR_MEENC_MEE_FXB_Li_BIT1_DATA_BIT_SEL_DEF    (0x00000001)
  #define MEECR_CR_VISA_XBAR_MEENC_MEE_FXB_Li_BIT1_DATA_BIT_SEL_HSH    (0x03047DC4)

  #define MEECR_CR_VISA_XBAR_MEENC_MEE_FXB_Li_BIT1_DATA_BYTE_SEL_OFF   ( 7)
  #define MEECR_CR_VISA_XBAR_MEENC_MEE_FXB_Li_BIT1_DATA_BYTE_SEL_WID   ( 1)
  #define MEECR_CR_VISA_XBAR_MEENC_MEE_FXB_Li_BIT1_DATA_BYTE_SEL_MSK   (0x00000080)
  #define MEECR_CR_VISA_XBAR_MEENC_MEE_FXB_Li_BIT1_DATA_BYTE_SEL_MIN   (0)
  #define MEECR_CR_VISA_XBAR_MEENC_MEE_FXB_Li_BIT1_DATA_BYTE_SEL_MAX   (1) // 0x00000001
  #define MEECR_CR_VISA_XBAR_MEENC_MEE_FXB_Li_BIT1_DATA_BYTE_SEL_DEF   (0x00000000)
  #define MEECR_CR_VISA_XBAR_MEENC_MEE_FXB_Li_BIT1_DATA_BYTE_SEL_HSH   (0x01077DC4)

  #define MEECR_CR_VISA_XBAR_MEENC_MEE_FXB_Li_BIT2_DATA_BIT_SEL_OFF    ( 8)
  #define MEECR_CR_VISA_XBAR_MEENC_MEE_FXB_Li_BIT2_DATA_BIT_SEL_WID    ( 3)
  #define MEECR_CR_VISA_XBAR_MEENC_MEE_FXB_Li_BIT2_DATA_BIT_SEL_MSK    (0x00000700)
  #define MEECR_CR_VISA_XBAR_MEENC_MEE_FXB_Li_BIT2_DATA_BIT_SEL_MIN    (0)
  #define MEECR_CR_VISA_XBAR_MEENC_MEE_FXB_Li_BIT2_DATA_BIT_SEL_MAX    (7) // 0x00000007
  #define MEECR_CR_VISA_XBAR_MEENC_MEE_FXB_Li_BIT2_DATA_BIT_SEL_DEF    (0x00000002)
  #define MEECR_CR_VISA_XBAR_MEENC_MEE_FXB_Li_BIT2_DATA_BIT_SEL_HSH    (0x03087DC4)

  #define MEECR_CR_VISA_XBAR_MEENC_MEE_FXB_Li_BIT2_DATA_BYTE_SEL_OFF   (11)
  #define MEECR_CR_VISA_XBAR_MEENC_MEE_FXB_Li_BIT2_DATA_BYTE_SEL_WID   ( 1)
  #define MEECR_CR_VISA_XBAR_MEENC_MEE_FXB_Li_BIT2_DATA_BYTE_SEL_MSK   (0x00000800)
  #define MEECR_CR_VISA_XBAR_MEENC_MEE_FXB_Li_BIT2_DATA_BYTE_SEL_MIN   (0)
  #define MEECR_CR_VISA_XBAR_MEENC_MEE_FXB_Li_BIT2_DATA_BYTE_SEL_MAX   (1) // 0x00000001
  #define MEECR_CR_VISA_XBAR_MEENC_MEE_FXB_Li_BIT2_DATA_BYTE_SEL_DEF   (0x00000000)
  #define MEECR_CR_VISA_XBAR_MEENC_MEE_FXB_Li_BIT2_DATA_BYTE_SEL_HSH   (0x010B7DC4)

  #define MEECR_CR_VISA_XBAR_MEENC_MEE_FXB_Li_BIT3_DATA_BIT_SEL_OFF    (12)
  #define MEECR_CR_VISA_XBAR_MEENC_MEE_FXB_Li_BIT3_DATA_BIT_SEL_WID    ( 3)
  #define MEECR_CR_VISA_XBAR_MEENC_MEE_FXB_Li_BIT3_DATA_BIT_SEL_MSK    (0x00007000)
  #define MEECR_CR_VISA_XBAR_MEENC_MEE_FXB_Li_BIT3_DATA_BIT_SEL_MIN    (0)
  #define MEECR_CR_VISA_XBAR_MEENC_MEE_FXB_Li_BIT3_DATA_BIT_SEL_MAX    (7) // 0x00000007
  #define MEECR_CR_VISA_XBAR_MEENC_MEE_FXB_Li_BIT3_DATA_BIT_SEL_DEF    (0x00000003)
  #define MEECR_CR_VISA_XBAR_MEENC_MEE_FXB_Li_BIT3_DATA_BIT_SEL_HSH    (0x030C7DC4)

  #define MEECR_CR_VISA_XBAR_MEENC_MEE_FXB_Li_BIT3_DATA_BYTE_SEL_OFF   (15)
  #define MEECR_CR_VISA_XBAR_MEENC_MEE_FXB_Li_BIT3_DATA_BYTE_SEL_WID   ( 1)
  #define MEECR_CR_VISA_XBAR_MEENC_MEE_FXB_Li_BIT3_DATA_BYTE_SEL_MSK   (0x00008000)
  #define MEECR_CR_VISA_XBAR_MEENC_MEE_FXB_Li_BIT3_DATA_BYTE_SEL_MIN   (0)
  #define MEECR_CR_VISA_XBAR_MEENC_MEE_FXB_Li_BIT3_DATA_BYTE_SEL_MAX   (1) // 0x00000001
  #define MEECR_CR_VISA_XBAR_MEENC_MEE_FXB_Li_BIT3_DATA_BYTE_SEL_DEF   (0x00000000)
  #define MEECR_CR_VISA_XBAR_MEENC_MEE_FXB_Li_BIT3_DATA_BYTE_SEL_HSH   (0x010F7DC4)

  #define MEECR_CR_VISA_XBAR_MEENC_MEE_FXB_Li_BIT4_DATA_BIT_SEL_OFF    (16)
  #define MEECR_CR_VISA_XBAR_MEENC_MEE_FXB_Li_BIT4_DATA_BIT_SEL_WID    ( 3)
  #define MEECR_CR_VISA_XBAR_MEENC_MEE_FXB_Li_BIT4_DATA_BIT_SEL_MSK    (0x00070000)
  #define MEECR_CR_VISA_XBAR_MEENC_MEE_FXB_Li_BIT4_DATA_BIT_SEL_MIN    (0)
  #define MEECR_CR_VISA_XBAR_MEENC_MEE_FXB_Li_BIT4_DATA_BIT_SEL_MAX    (7) // 0x00000007
  #define MEECR_CR_VISA_XBAR_MEENC_MEE_FXB_Li_BIT4_DATA_BIT_SEL_DEF    (0x00000004)
  #define MEECR_CR_VISA_XBAR_MEENC_MEE_FXB_Li_BIT4_DATA_BIT_SEL_HSH    (0x03107DC4)

  #define MEECR_CR_VISA_XBAR_MEENC_MEE_FXB_Li_BIT4_DATA_BYTE_SEL_OFF   (19)
  #define MEECR_CR_VISA_XBAR_MEENC_MEE_FXB_Li_BIT4_DATA_BYTE_SEL_WID   ( 1)
  #define MEECR_CR_VISA_XBAR_MEENC_MEE_FXB_Li_BIT4_DATA_BYTE_SEL_MSK   (0x00080000)
  #define MEECR_CR_VISA_XBAR_MEENC_MEE_FXB_Li_BIT4_DATA_BYTE_SEL_MIN   (0)
  #define MEECR_CR_VISA_XBAR_MEENC_MEE_FXB_Li_BIT4_DATA_BYTE_SEL_MAX   (1) // 0x00000001
  #define MEECR_CR_VISA_XBAR_MEENC_MEE_FXB_Li_BIT4_DATA_BYTE_SEL_DEF   (0x00000000)
  #define MEECR_CR_VISA_XBAR_MEENC_MEE_FXB_Li_BIT4_DATA_BYTE_SEL_HSH   (0x01137DC4)

  #define MEECR_CR_VISA_XBAR_MEENC_MEE_FXB_Li_BIT5_DATA_BIT_SEL_OFF    (20)
  #define MEECR_CR_VISA_XBAR_MEENC_MEE_FXB_Li_BIT5_DATA_BIT_SEL_WID    ( 3)
  #define MEECR_CR_VISA_XBAR_MEENC_MEE_FXB_Li_BIT5_DATA_BIT_SEL_MSK    (0x00700000)
  #define MEECR_CR_VISA_XBAR_MEENC_MEE_FXB_Li_BIT5_DATA_BIT_SEL_MIN    (0)
  #define MEECR_CR_VISA_XBAR_MEENC_MEE_FXB_Li_BIT5_DATA_BIT_SEL_MAX    (7) // 0x00000007
  #define MEECR_CR_VISA_XBAR_MEENC_MEE_FXB_Li_BIT5_DATA_BIT_SEL_DEF    (0x00000005)
  #define MEECR_CR_VISA_XBAR_MEENC_MEE_FXB_Li_BIT5_DATA_BIT_SEL_HSH    (0x03147DC4)

  #define MEECR_CR_VISA_XBAR_MEENC_MEE_FXB_Li_BIT5_DATA_BYTE_SEL_OFF   (23)
  #define MEECR_CR_VISA_XBAR_MEENC_MEE_FXB_Li_BIT5_DATA_BYTE_SEL_WID   ( 1)
  #define MEECR_CR_VISA_XBAR_MEENC_MEE_FXB_Li_BIT5_DATA_BYTE_SEL_MSK   (0x00800000)
  #define MEECR_CR_VISA_XBAR_MEENC_MEE_FXB_Li_BIT5_DATA_BYTE_SEL_MIN   (0)
  #define MEECR_CR_VISA_XBAR_MEENC_MEE_FXB_Li_BIT5_DATA_BYTE_SEL_MAX   (1) // 0x00000001
  #define MEECR_CR_VISA_XBAR_MEENC_MEE_FXB_Li_BIT5_DATA_BYTE_SEL_DEF   (0x00000000)
  #define MEECR_CR_VISA_XBAR_MEENC_MEE_FXB_Li_BIT5_DATA_BYTE_SEL_HSH   (0x01177DC4)

  #define MEECR_CR_VISA_XBAR_MEENC_MEE_FXB_Li_BIT6_DATA_BIT_SEL_OFF    (24)
  #define MEECR_CR_VISA_XBAR_MEENC_MEE_FXB_Li_BIT6_DATA_BIT_SEL_WID    ( 3)
  #define MEECR_CR_VISA_XBAR_MEENC_MEE_FXB_Li_BIT6_DATA_BIT_SEL_MSK    (0x07000000)
  #define MEECR_CR_VISA_XBAR_MEENC_MEE_FXB_Li_BIT6_DATA_BIT_SEL_MIN    (0)
  #define MEECR_CR_VISA_XBAR_MEENC_MEE_FXB_Li_BIT6_DATA_BIT_SEL_MAX    (7) // 0x00000007
  #define MEECR_CR_VISA_XBAR_MEENC_MEE_FXB_Li_BIT6_DATA_BIT_SEL_DEF    (0x00000006)
  #define MEECR_CR_VISA_XBAR_MEENC_MEE_FXB_Li_BIT6_DATA_BIT_SEL_HSH    (0x03187DC4)

  #define MEECR_CR_VISA_XBAR_MEENC_MEE_FXB_Li_BIT6_DATA_BYTE_SEL_OFF   (27)
  #define MEECR_CR_VISA_XBAR_MEENC_MEE_FXB_Li_BIT6_DATA_BYTE_SEL_WID   ( 1)
  #define MEECR_CR_VISA_XBAR_MEENC_MEE_FXB_Li_BIT6_DATA_BYTE_SEL_MSK   (0x08000000)
  #define MEECR_CR_VISA_XBAR_MEENC_MEE_FXB_Li_BIT6_DATA_BYTE_SEL_MIN   (0)
  #define MEECR_CR_VISA_XBAR_MEENC_MEE_FXB_Li_BIT6_DATA_BYTE_SEL_MAX   (1) // 0x00000001
  #define MEECR_CR_VISA_XBAR_MEENC_MEE_FXB_Li_BIT6_DATA_BYTE_SEL_DEF   (0x00000000)
  #define MEECR_CR_VISA_XBAR_MEENC_MEE_FXB_Li_BIT6_DATA_BYTE_SEL_HSH   (0x011B7DC4)

  #define MEECR_CR_VISA_XBAR_MEENC_MEE_FXB_Li_BIT7_DATA_BIT_SEL_OFF    (28)
  #define MEECR_CR_VISA_XBAR_MEENC_MEE_FXB_Li_BIT7_DATA_BIT_SEL_WID    ( 3)
  #define MEECR_CR_VISA_XBAR_MEENC_MEE_FXB_Li_BIT7_DATA_BIT_SEL_MSK    (0x70000000)
  #define MEECR_CR_VISA_XBAR_MEENC_MEE_FXB_Li_BIT7_DATA_BIT_SEL_MIN    (0)
  #define MEECR_CR_VISA_XBAR_MEENC_MEE_FXB_Li_BIT7_DATA_BIT_SEL_MAX    (7) // 0x00000007
  #define MEECR_CR_VISA_XBAR_MEENC_MEE_FXB_Li_BIT7_DATA_BIT_SEL_DEF    (0x00000007)
  #define MEECR_CR_VISA_XBAR_MEENC_MEE_FXB_Li_BIT7_DATA_BIT_SEL_HSH    (0x031C7DC4)

  #define MEECR_CR_VISA_XBAR_MEENC_MEE_FXB_Li_BIT7_DATA_BYTE_SEL_OFF   (31)
  #define MEECR_CR_VISA_XBAR_MEENC_MEE_FXB_Li_BIT7_DATA_BYTE_SEL_WID   ( 1)
  #define MEECR_CR_VISA_XBAR_MEENC_MEE_FXB_Li_BIT7_DATA_BYTE_SEL_MSK   (0x80000000)
  #define MEECR_CR_VISA_XBAR_MEENC_MEE_FXB_Li_BIT7_DATA_BYTE_SEL_MIN   (0)
  #define MEECR_CR_VISA_XBAR_MEENC_MEE_FXB_Li_BIT7_DATA_BYTE_SEL_MAX   (1) // 0x00000001
  #define MEECR_CR_VISA_XBAR_MEENC_MEE_FXB_Li_BIT7_DATA_BYTE_SEL_DEF   (0x00000000)
  #define MEECR_CR_VISA_XBAR_MEENC_MEE_FXB_Li_BIT7_DATA_BYTE_SEL_HSH   (0x011F7DC4)

#define MEECR_CR_VISA_SLIDE_MEENC_MEE_REG                              (0x00007DC8)

  #define MEECR_CR_VISA_SLIDE_MEENC_MEE_WINDOW_SLIDE_L0_OFF            ( 0)
  #define MEECR_CR_VISA_SLIDE_MEENC_MEE_WINDOW_SLIDE_L0_WID            ( 3)
  #define MEECR_CR_VISA_SLIDE_MEENC_MEE_WINDOW_SLIDE_L0_MSK            (0x00000007)
  #define MEECR_CR_VISA_SLIDE_MEENC_MEE_WINDOW_SLIDE_L0_MIN            (0)
  #define MEECR_CR_VISA_SLIDE_MEENC_MEE_WINDOW_SLIDE_L0_MAX            (7) // 0x00000007
  #define MEECR_CR_VISA_SLIDE_MEENC_MEE_WINDOW_SLIDE_L0_DEF            (0x00000000)
  #define MEECR_CR_VISA_SLIDE_MEENC_MEE_WINDOW_SLIDE_L0_HSH            (0x03007DC8)

  #define MEECR_CR_VISA_SLIDE_MEENC_MEE_ALT_L0_DATA_BYTE_SEL_OFF       ( 3)
  #define MEECR_CR_VISA_SLIDE_MEENC_MEE_ALT_L0_DATA_BYTE_SEL_WID       ( 7)
  #define MEECR_CR_VISA_SLIDE_MEENC_MEE_ALT_L0_DATA_BYTE_SEL_MSK       (0x000003F8)
  #define MEECR_CR_VISA_SLIDE_MEENC_MEE_ALT_L0_DATA_BYTE_SEL_MIN       (0)
  #define MEECR_CR_VISA_SLIDE_MEENC_MEE_ALT_L0_DATA_BYTE_SEL_MAX       (127) // 0x0000007F
  #define MEECR_CR_VISA_SLIDE_MEENC_MEE_ALT_L0_DATA_BYTE_SEL_DEF       (0x00000000)
  #define MEECR_CR_VISA_SLIDE_MEENC_MEE_ALT_L0_DATA_BYTE_SEL_HSH       (0x07037DC8)

  #define MEECR_CR_VISA_SLIDE_MEENC_MEE_WINDOW_SLIDE_L1_OFF            (10)
  #define MEECR_CR_VISA_SLIDE_MEENC_MEE_WINDOW_SLIDE_L1_WID            ( 3)
  #define MEECR_CR_VISA_SLIDE_MEENC_MEE_WINDOW_SLIDE_L1_MSK            (0x00001C00)
  #define MEECR_CR_VISA_SLIDE_MEENC_MEE_WINDOW_SLIDE_L1_MIN            (0)
  #define MEECR_CR_VISA_SLIDE_MEENC_MEE_WINDOW_SLIDE_L1_MAX            (7) // 0x00000007
  #define MEECR_CR_VISA_SLIDE_MEENC_MEE_WINDOW_SLIDE_L1_DEF            (0x00000000)
  #define MEECR_CR_VISA_SLIDE_MEENC_MEE_WINDOW_SLIDE_L1_HSH            (0x030A7DC8)

  #define MEECR_CR_VISA_SLIDE_MEENC_MEE_ALT_L1_DATA_BYTE_SEL_OFF       (13)
  #define MEECR_CR_VISA_SLIDE_MEENC_MEE_ALT_L1_DATA_BYTE_SEL_WID       ( 7)
  #define MEECR_CR_VISA_SLIDE_MEENC_MEE_ALT_L1_DATA_BYTE_SEL_MSK       (0x000FE000)
  #define MEECR_CR_VISA_SLIDE_MEENC_MEE_ALT_L1_DATA_BYTE_SEL_MIN       (0)
  #define MEECR_CR_VISA_SLIDE_MEENC_MEE_ALT_L1_DATA_BYTE_SEL_MAX       (127) // 0x0000007F
  #define MEECR_CR_VISA_SLIDE_MEENC_MEE_ALT_L1_DATA_BYTE_SEL_DEF       (0x00000000)
  #define MEECR_CR_VISA_SLIDE_MEENC_MEE_ALT_L1_DATA_BYTE_SEL_HSH       (0x070D7DC8)

#define MEECR_CR_MEE_REQ_RSP_LIM_MEE_REG                               (0x00007DE0)

  #define MEECR_CR_MEE_REQ_RSP_LIM_MEE_MEE_VC0_RD_OFF                  ( 0)
  #define MEECR_CR_MEE_REQ_RSP_LIM_MEE_MEE_VC0_RD_WID                  ( 3)
  #define MEECR_CR_MEE_REQ_RSP_LIM_MEE_MEE_VC0_RD_MSK                  (0x00000007)
  #define MEECR_CR_MEE_REQ_RSP_LIM_MEE_MEE_VC0_RD_MIN                  (0)
  #define MEECR_CR_MEE_REQ_RSP_LIM_MEE_MEE_VC0_RD_MAX                  (7) // 0x00000007
  #define MEECR_CR_MEE_REQ_RSP_LIM_MEE_MEE_VC0_RD_DEF                  (0x00000004)
  #define MEECR_CR_MEE_REQ_RSP_LIM_MEE_MEE_VC0_RD_HSH                  (0x03007DE0)

  #define MEECR_CR_MEE_REQ_RSP_LIM_MEE_MEE_VC0_WR_OFF                  ( 3)
  #define MEECR_CR_MEE_REQ_RSP_LIM_MEE_MEE_VC0_WR_WID                  ( 3)
  #define MEECR_CR_MEE_REQ_RSP_LIM_MEE_MEE_VC0_WR_MSK                  (0x00000038)
  #define MEECR_CR_MEE_REQ_RSP_LIM_MEE_MEE_VC0_WR_MIN                  (0)
  #define MEECR_CR_MEE_REQ_RSP_LIM_MEE_MEE_VC0_WR_MAX                  (7) // 0x00000007
  #define MEECR_CR_MEE_REQ_RSP_LIM_MEE_MEE_VC0_WR_DEF                  (0x00000004)
  #define MEECR_CR_MEE_REQ_RSP_LIM_MEE_MEE_VC0_WR_HSH                  (0x03037DE0)

#define MEECR_CR_RCH_RD_CMP_ARB_EFLOW_IPC_MEE_REG                      (0x00007DE4)

  #define MEECR_CR_RCH_RD_CMP_ARB_EFLOW_IPC_MEE_NON_VC1_THRESHOLD_OFF  ( 0)
  #define MEECR_CR_RCH_RD_CMP_ARB_EFLOW_IPC_MEE_NON_VC1_THRESHOLD_WID  ( 4)
  #define MEECR_CR_RCH_RD_CMP_ARB_EFLOW_IPC_MEE_NON_VC1_THRESHOLD_MSK  (0x0000000F)
  #define MEECR_CR_RCH_RD_CMP_ARB_EFLOW_IPC_MEE_NON_VC1_THRESHOLD_MIN  (0)
  #define MEECR_CR_RCH_RD_CMP_ARB_EFLOW_IPC_MEE_NON_VC1_THRESHOLD_MAX  (15) // 0x0000000F
  #define MEECR_CR_RCH_RD_CMP_ARB_EFLOW_IPC_MEE_NON_VC1_THRESHOLD_DEF  (0x00000008)
  #define MEECR_CR_RCH_RD_CMP_ARB_EFLOW_IPC_MEE_NON_VC1_THRESHOLD_HSH  (0x04007DE4)

  #define MEECR_CR_RCH_RD_CMP_ARB_EFLOW_IPC_MEE_VC1_RD_THRESHOLD_OFF   ( 4)
  #define MEECR_CR_RCH_RD_CMP_ARB_EFLOW_IPC_MEE_VC1_RD_THRESHOLD_WID   ( 4)
  #define MEECR_CR_RCH_RD_CMP_ARB_EFLOW_IPC_MEE_VC1_RD_THRESHOLD_MSK   (0x000000F0)
  #define MEECR_CR_RCH_RD_CMP_ARB_EFLOW_IPC_MEE_VC1_RD_THRESHOLD_MIN   (0)
  #define MEECR_CR_RCH_RD_CMP_ARB_EFLOW_IPC_MEE_VC1_RD_THRESHOLD_MAX   (15) // 0x0000000F
  #define MEECR_CR_RCH_RD_CMP_ARB_EFLOW_IPC_MEE_VC1_RD_THRESHOLD_DEF   (0x00000008)
  #define MEECR_CR_RCH_RD_CMP_ARB_EFLOW_IPC_MEE_VC1_RD_THRESHOLD_HSH   (0x04047DE4)

  #define MEECR_CR_RCH_RD_CMP_ARB_EFLOW_IPC_MEE_FIXED_RATE_EN_OFF      ( 8)
  #define MEECR_CR_RCH_RD_CMP_ARB_EFLOW_IPC_MEE_FIXED_RATE_EN_WID      ( 1)
  #define MEECR_CR_RCH_RD_CMP_ARB_EFLOW_IPC_MEE_FIXED_RATE_EN_MSK      (0x00000100)
  #define MEECR_CR_RCH_RD_CMP_ARB_EFLOW_IPC_MEE_FIXED_RATE_EN_MIN      (0)
  #define MEECR_CR_RCH_RD_CMP_ARB_EFLOW_IPC_MEE_FIXED_RATE_EN_MAX      (1) // 0x00000001
  #define MEECR_CR_RCH_RD_CMP_ARB_EFLOW_IPC_MEE_FIXED_RATE_EN_DEF      (0x00000000)
  #define MEECR_CR_RCH_RD_CMP_ARB_EFLOW_IPC_MEE_FIXED_RATE_EN_HSH      (0x01087DE4)

  #define MEECR_CR_RCH_RD_CMP_ARB_EFLOW_IPC_MEE_HIGH_PRIO_LIM_OFF      ( 9)
  #define MEECR_CR_RCH_RD_CMP_ARB_EFLOW_IPC_MEE_HIGH_PRIO_LIM_WID      ( 3)
  #define MEECR_CR_RCH_RD_CMP_ARB_EFLOW_IPC_MEE_HIGH_PRIO_LIM_MSK      (0x00000E00)
  #define MEECR_CR_RCH_RD_CMP_ARB_EFLOW_IPC_MEE_HIGH_PRIO_LIM_MIN      (0)
  #define MEECR_CR_RCH_RD_CMP_ARB_EFLOW_IPC_MEE_HIGH_PRIO_LIM_MAX      (7) // 0x00000007
  #define MEECR_CR_RCH_RD_CMP_ARB_EFLOW_IPC_MEE_HIGH_PRIO_LIM_DEF      (0x00000004)
  #define MEECR_CR_RCH_RD_CMP_ARB_EFLOW_IPC_MEE_HIGH_PRIO_LIM_HSH      (0x03097DE4)

  #define MEECR_CR_RCH_RD_CMP_ARB_EFLOW_IPC_MEE_LOW_PRIO_LIM_OFF       (12)
  #define MEECR_CR_RCH_RD_CMP_ARB_EFLOW_IPC_MEE_LOW_PRIO_LIM_WID       ( 3)
  #define MEECR_CR_RCH_RD_CMP_ARB_EFLOW_IPC_MEE_LOW_PRIO_LIM_MSK       (0x00007000)
  #define MEECR_CR_RCH_RD_CMP_ARB_EFLOW_IPC_MEE_LOW_PRIO_LIM_MIN       (0)
  #define MEECR_CR_RCH_RD_CMP_ARB_EFLOW_IPC_MEE_LOW_PRIO_LIM_MAX       (7) // 0x00000007
  #define MEECR_CR_RCH_RD_CMP_ARB_EFLOW_IPC_MEE_LOW_PRIO_LIM_DEF       (0x00000001)
  #define MEECR_CR_RCH_RD_CMP_ARB_EFLOW_IPC_MEE_LOW_PRIO_LIM_HSH       (0x030C7DE4)

  #define MEECR_CR_RCH_RD_CMP_ARB_EFLOW_IPC_MEE_SPARE_OFF              (15)
  #define MEECR_CR_RCH_RD_CMP_ARB_EFLOW_IPC_MEE_SPARE_WID              ( 1)
  #define MEECR_CR_RCH_RD_CMP_ARB_EFLOW_IPC_MEE_SPARE_MSK              (0x00008000)
  #define MEECR_CR_RCH_RD_CMP_ARB_EFLOW_IPC_MEE_SPARE_MIN              (0)
  #define MEECR_CR_RCH_RD_CMP_ARB_EFLOW_IPC_MEE_SPARE_MAX              (1) // 0x00000001
  #define MEECR_CR_RCH_RD_CMP_ARB_EFLOW_IPC_MEE_SPARE_DEF              (0x00000000)
  #define MEECR_CR_RCH_RD_CMP_ARB_EFLOW_IPC_MEE_SPARE_HSH              (0x010F7DE4)

#define MEECR_CR_RCH_RD_CMP_ARB_EFLOW_LIM_MEE_REG                      (0x00007DE8)

  #define MEECR_CR_RCH_RD_CMP_ARB_EFLOW_LIM_MEE_MC_VC1_OFF             ( 0)
  #define MEECR_CR_RCH_RD_CMP_ARB_EFLOW_LIM_MEE_MC_VC1_WID             ( 3)
  #define MEECR_CR_RCH_RD_CMP_ARB_EFLOW_LIM_MEE_MC_VC1_MSK             (0x00000007)
  #define MEECR_CR_RCH_RD_CMP_ARB_EFLOW_LIM_MEE_MC_VC1_MIN             (0)
  #define MEECR_CR_RCH_RD_CMP_ARB_EFLOW_LIM_MEE_MC_VC1_MAX             (7) // 0x00000007
  #define MEECR_CR_RCH_RD_CMP_ARB_EFLOW_LIM_MEE_MC_VC1_DEF             (0x00000004)
  #define MEECR_CR_RCH_RD_CMP_ARB_EFLOW_LIM_MEE_MC_VC1_HSH             (0x03007DE8)

  #define MEECR_CR_RCH_RD_CMP_ARB_EFLOW_LIM_MEE_MC_VC0_OFF             ( 4)
  #define MEECR_CR_RCH_RD_CMP_ARB_EFLOW_LIM_MEE_MC_VC0_WID             ( 3)
  #define MEECR_CR_RCH_RD_CMP_ARB_EFLOW_LIM_MEE_MC_VC0_MSK             (0x00000070)
  #define MEECR_CR_RCH_RD_CMP_ARB_EFLOW_LIM_MEE_MC_VC0_MIN             (0)
  #define MEECR_CR_RCH_RD_CMP_ARB_EFLOW_LIM_MEE_MC_VC0_MAX             (7) // 0x00000007
  #define MEECR_CR_RCH_RD_CMP_ARB_EFLOW_LIM_MEE_MC_VC0_DEF             (0x00000004)
  #define MEECR_CR_RCH_RD_CMP_ARB_EFLOW_LIM_MEE_MC_VC0_HSH             (0x03047DE8)

  #define MEECR_CR_RCH_RD_CMP_ARB_EFLOW_LIM_MEE_MEE_VC0_OFF            ( 8)
  #define MEECR_CR_RCH_RD_CMP_ARB_EFLOW_LIM_MEE_MEE_VC0_WID            ( 3)
  #define MEECR_CR_RCH_RD_CMP_ARB_EFLOW_LIM_MEE_MEE_VC0_MSK            (0x00000700)
  #define MEECR_CR_RCH_RD_CMP_ARB_EFLOW_LIM_MEE_MEE_VC0_MIN            (0)
  #define MEECR_CR_RCH_RD_CMP_ARB_EFLOW_LIM_MEE_MEE_VC0_MAX            (7) // 0x00000007
  #define MEECR_CR_RCH_RD_CMP_ARB_EFLOW_LIM_MEE_MEE_VC0_DEF            (0x00000004)
  #define MEECR_CR_RCH_RD_CMP_ARB_EFLOW_LIM_MEE_MEE_VC0_HSH            (0x03087DE8)

#define MEECR_CR_VISA_CTL_MEMAIN_MEE_REG                               (0x00007E50)

  #define MEECR_CR_VISA_CTL_MEMAIN_MEE_EN_CLK_OFF                      ( 0)
  #define MEECR_CR_VISA_CTL_MEMAIN_MEE_EN_CLK_WID                      ( 1)
  #define MEECR_CR_VISA_CTL_MEMAIN_MEE_EN_CLK_MSK                      (0x00000001)
  #define MEECR_CR_VISA_CTL_MEMAIN_MEE_EN_CLK_MIN                      (0)
  #define MEECR_CR_VISA_CTL_MEMAIN_MEE_EN_CLK_MAX                      (1) // 0x00000001
  #define MEECR_CR_VISA_CTL_MEMAIN_MEE_EN_CLK_DEF                      (0x00000000)
  #define MEECR_CR_VISA_CTL_MEMAIN_MEE_EN_CLK_HSH                      (0x01007E50)

  #define MEECR_CR_VISA_CTL_MEMAIN_MEE_L0_DATA_BYTE_SEL_OFF            ( 1)
  #define MEECR_CR_VISA_CTL_MEMAIN_MEE_L0_DATA_BYTE_SEL_WID            ( 7)
  #define MEECR_CR_VISA_CTL_MEMAIN_MEE_L0_DATA_BYTE_SEL_MSK            (0x000000FE)
  #define MEECR_CR_VISA_CTL_MEMAIN_MEE_L0_DATA_BYTE_SEL_MIN            (0)
  #define MEECR_CR_VISA_CTL_MEMAIN_MEE_L0_DATA_BYTE_SEL_MAX            (127) // 0x0000007F
  #define MEECR_CR_VISA_CTL_MEMAIN_MEE_L0_DATA_BYTE_SEL_DEF            (0x00000000)
  #define MEECR_CR_VISA_CTL_MEMAIN_MEE_L0_DATA_BYTE_SEL_HSH            (0x07017E50)

  #define MEECR_CR_VISA_CTL_MEMAIN_MEE_L0_BYP_SEL_OFF                  ( 8)
  #define MEECR_CR_VISA_CTL_MEMAIN_MEE_L0_BYP_SEL_WID                  ( 1)
  #define MEECR_CR_VISA_CTL_MEMAIN_MEE_L0_BYP_SEL_MSK                  (0x00000100)
  #define MEECR_CR_VISA_CTL_MEMAIN_MEE_L0_BYP_SEL_MIN                  (0)
  #define MEECR_CR_VISA_CTL_MEMAIN_MEE_L0_BYP_SEL_MAX                  (1) // 0x00000001
  #define MEECR_CR_VISA_CTL_MEMAIN_MEE_L0_BYP_SEL_DEF                  (0x00000000)
  #define MEECR_CR_VISA_CTL_MEMAIN_MEE_L0_BYP_SEL_HSH                  (0x01087E50)

  #define MEECR_CR_VISA_CTL_MEMAIN_MEE_L1_DATA_BYTE_SEL_OFF            ( 9)
  #define MEECR_CR_VISA_CTL_MEMAIN_MEE_L1_DATA_BYTE_SEL_WID            ( 7)
  #define MEECR_CR_VISA_CTL_MEMAIN_MEE_L1_DATA_BYTE_SEL_MSK            (0x0000FE00)
  #define MEECR_CR_VISA_CTL_MEMAIN_MEE_L1_DATA_BYTE_SEL_MIN            (0)
  #define MEECR_CR_VISA_CTL_MEMAIN_MEE_L1_DATA_BYTE_SEL_MAX            (127) // 0x0000007F
  #define MEECR_CR_VISA_CTL_MEMAIN_MEE_L1_DATA_BYTE_SEL_DEF            (0x00000000)
  #define MEECR_CR_VISA_CTL_MEMAIN_MEE_L1_DATA_BYTE_SEL_HSH            (0x07097E50)

  #define MEECR_CR_VISA_CTL_MEMAIN_MEE_L1_BYP_SEL_OFF                  (16)
  #define MEECR_CR_VISA_CTL_MEMAIN_MEE_L1_BYP_SEL_WID                  ( 1)
  #define MEECR_CR_VISA_CTL_MEMAIN_MEE_L1_BYP_SEL_MSK                  (0x00010000)
  #define MEECR_CR_VISA_CTL_MEMAIN_MEE_L1_BYP_SEL_MIN                  (0)
  #define MEECR_CR_VISA_CTL_MEMAIN_MEE_L1_BYP_SEL_MAX                  (1) // 0x00000001
  #define MEECR_CR_VISA_CTL_MEMAIN_MEE_L1_BYP_SEL_DEF                  (0x00000000)
  #define MEECR_CR_VISA_CTL_MEMAIN_MEE_L1_BYP_SEL_HSH                  (0x01107E50)

  #define MEECR_CR_VISA_CTL_MEMAIN_MEE_VORANGE_OFF                     (31)
  #define MEECR_CR_VISA_CTL_MEMAIN_MEE_VORANGE_WID                     ( 1)
  #define MEECR_CR_VISA_CTL_MEMAIN_MEE_VORANGE_MSK                     (0x80000000)
  #define MEECR_CR_VISA_CTL_MEMAIN_MEE_VORANGE_MIN                     (0)
  #define MEECR_CR_VISA_CTL_MEMAIN_MEE_VORANGE_MAX                     (1) // 0x00000001
  #define MEECR_CR_VISA_CTL_MEMAIN_MEE_VORANGE_DEF                     (0x00000000)
  #define MEECR_CR_VISA_CTL_MEMAIN_MEE_VORANGE_HSH                     (0x011F7E50)

#define MEECR_CR_VISA_XBAR_MEMAIN_MEE_REG                              (0x00007E54)

  #define MEECR_CR_VISA_XBAR_MEMAIN_MEE_FXB_Li_BIT0_DATA_BIT_SEL_OFF   ( 0)
  #define MEECR_CR_VISA_XBAR_MEMAIN_MEE_FXB_Li_BIT0_DATA_BIT_SEL_WID   ( 3)
  #define MEECR_CR_VISA_XBAR_MEMAIN_MEE_FXB_Li_BIT0_DATA_BIT_SEL_MSK   (0x00000007)
  #define MEECR_CR_VISA_XBAR_MEMAIN_MEE_FXB_Li_BIT0_DATA_BIT_SEL_MIN   (0)
  #define MEECR_CR_VISA_XBAR_MEMAIN_MEE_FXB_Li_BIT0_DATA_BIT_SEL_MAX   (7) // 0x00000007
  #define MEECR_CR_VISA_XBAR_MEMAIN_MEE_FXB_Li_BIT0_DATA_BIT_SEL_DEF   (0x00000000)
  #define MEECR_CR_VISA_XBAR_MEMAIN_MEE_FXB_Li_BIT0_DATA_BIT_SEL_HSH   (0x03007E54)

  #define MEECR_CR_VISA_XBAR_MEMAIN_MEE_FXB_Li_BIT0_DATA_BYTE_SEL_OFF  ( 3)
  #define MEECR_CR_VISA_XBAR_MEMAIN_MEE_FXB_Li_BIT0_DATA_BYTE_SEL_WID  ( 1)
  #define MEECR_CR_VISA_XBAR_MEMAIN_MEE_FXB_Li_BIT0_DATA_BYTE_SEL_MSK  (0x00000008)
  #define MEECR_CR_VISA_XBAR_MEMAIN_MEE_FXB_Li_BIT0_DATA_BYTE_SEL_MIN  (0)
  #define MEECR_CR_VISA_XBAR_MEMAIN_MEE_FXB_Li_BIT0_DATA_BYTE_SEL_MAX  (1) // 0x00000001
  #define MEECR_CR_VISA_XBAR_MEMAIN_MEE_FXB_Li_BIT0_DATA_BYTE_SEL_DEF  (0x00000000)
  #define MEECR_CR_VISA_XBAR_MEMAIN_MEE_FXB_Li_BIT0_DATA_BYTE_SEL_HSH  (0x01037E54)

  #define MEECR_CR_VISA_XBAR_MEMAIN_MEE_FXB_Li_BIT1_DATA_BIT_SEL_OFF   ( 4)
  #define MEECR_CR_VISA_XBAR_MEMAIN_MEE_FXB_Li_BIT1_DATA_BIT_SEL_WID   ( 3)
  #define MEECR_CR_VISA_XBAR_MEMAIN_MEE_FXB_Li_BIT1_DATA_BIT_SEL_MSK   (0x00000070)
  #define MEECR_CR_VISA_XBAR_MEMAIN_MEE_FXB_Li_BIT1_DATA_BIT_SEL_MIN   (0)
  #define MEECR_CR_VISA_XBAR_MEMAIN_MEE_FXB_Li_BIT1_DATA_BIT_SEL_MAX   (7) // 0x00000007
  #define MEECR_CR_VISA_XBAR_MEMAIN_MEE_FXB_Li_BIT1_DATA_BIT_SEL_DEF   (0x00000001)
  #define MEECR_CR_VISA_XBAR_MEMAIN_MEE_FXB_Li_BIT1_DATA_BIT_SEL_HSH   (0x03047E54)

  #define MEECR_CR_VISA_XBAR_MEMAIN_MEE_FXB_Li_BIT1_DATA_BYTE_SEL_OFF  ( 7)
  #define MEECR_CR_VISA_XBAR_MEMAIN_MEE_FXB_Li_BIT1_DATA_BYTE_SEL_WID  ( 1)
  #define MEECR_CR_VISA_XBAR_MEMAIN_MEE_FXB_Li_BIT1_DATA_BYTE_SEL_MSK  (0x00000080)
  #define MEECR_CR_VISA_XBAR_MEMAIN_MEE_FXB_Li_BIT1_DATA_BYTE_SEL_MIN  (0)
  #define MEECR_CR_VISA_XBAR_MEMAIN_MEE_FXB_Li_BIT1_DATA_BYTE_SEL_MAX  (1) // 0x00000001
  #define MEECR_CR_VISA_XBAR_MEMAIN_MEE_FXB_Li_BIT1_DATA_BYTE_SEL_DEF  (0x00000000)
  #define MEECR_CR_VISA_XBAR_MEMAIN_MEE_FXB_Li_BIT1_DATA_BYTE_SEL_HSH  (0x01077E54)

  #define MEECR_CR_VISA_XBAR_MEMAIN_MEE_FXB_Li_BIT2_DATA_BIT_SEL_OFF   ( 8)
  #define MEECR_CR_VISA_XBAR_MEMAIN_MEE_FXB_Li_BIT2_DATA_BIT_SEL_WID   ( 3)
  #define MEECR_CR_VISA_XBAR_MEMAIN_MEE_FXB_Li_BIT2_DATA_BIT_SEL_MSK   (0x00000700)
  #define MEECR_CR_VISA_XBAR_MEMAIN_MEE_FXB_Li_BIT2_DATA_BIT_SEL_MIN   (0)
  #define MEECR_CR_VISA_XBAR_MEMAIN_MEE_FXB_Li_BIT2_DATA_BIT_SEL_MAX   (7) // 0x00000007
  #define MEECR_CR_VISA_XBAR_MEMAIN_MEE_FXB_Li_BIT2_DATA_BIT_SEL_DEF   (0x00000002)
  #define MEECR_CR_VISA_XBAR_MEMAIN_MEE_FXB_Li_BIT2_DATA_BIT_SEL_HSH   (0x03087E54)

  #define MEECR_CR_VISA_XBAR_MEMAIN_MEE_FXB_Li_BIT2_DATA_BYTE_SEL_OFF  (11)
  #define MEECR_CR_VISA_XBAR_MEMAIN_MEE_FXB_Li_BIT2_DATA_BYTE_SEL_WID  ( 1)
  #define MEECR_CR_VISA_XBAR_MEMAIN_MEE_FXB_Li_BIT2_DATA_BYTE_SEL_MSK  (0x00000800)
  #define MEECR_CR_VISA_XBAR_MEMAIN_MEE_FXB_Li_BIT2_DATA_BYTE_SEL_MIN  (0)
  #define MEECR_CR_VISA_XBAR_MEMAIN_MEE_FXB_Li_BIT2_DATA_BYTE_SEL_MAX  (1) // 0x00000001
  #define MEECR_CR_VISA_XBAR_MEMAIN_MEE_FXB_Li_BIT2_DATA_BYTE_SEL_DEF  (0x00000000)
  #define MEECR_CR_VISA_XBAR_MEMAIN_MEE_FXB_Li_BIT2_DATA_BYTE_SEL_HSH  (0x010B7E54)

  #define MEECR_CR_VISA_XBAR_MEMAIN_MEE_FXB_Li_BIT3_DATA_BIT_SEL_OFF   (12)
  #define MEECR_CR_VISA_XBAR_MEMAIN_MEE_FXB_Li_BIT3_DATA_BIT_SEL_WID   ( 3)
  #define MEECR_CR_VISA_XBAR_MEMAIN_MEE_FXB_Li_BIT3_DATA_BIT_SEL_MSK   (0x00007000)
  #define MEECR_CR_VISA_XBAR_MEMAIN_MEE_FXB_Li_BIT3_DATA_BIT_SEL_MIN   (0)
  #define MEECR_CR_VISA_XBAR_MEMAIN_MEE_FXB_Li_BIT3_DATA_BIT_SEL_MAX   (7) // 0x00000007
  #define MEECR_CR_VISA_XBAR_MEMAIN_MEE_FXB_Li_BIT3_DATA_BIT_SEL_DEF   (0x00000003)
  #define MEECR_CR_VISA_XBAR_MEMAIN_MEE_FXB_Li_BIT3_DATA_BIT_SEL_HSH   (0x030C7E54)

  #define MEECR_CR_VISA_XBAR_MEMAIN_MEE_FXB_Li_BIT3_DATA_BYTE_SEL_OFF  (15)
  #define MEECR_CR_VISA_XBAR_MEMAIN_MEE_FXB_Li_BIT3_DATA_BYTE_SEL_WID  ( 1)
  #define MEECR_CR_VISA_XBAR_MEMAIN_MEE_FXB_Li_BIT3_DATA_BYTE_SEL_MSK  (0x00008000)
  #define MEECR_CR_VISA_XBAR_MEMAIN_MEE_FXB_Li_BIT3_DATA_BYTE_SEL_MIN  (0)
  #define MEECR_CR_VISA_XBAR_MEMAIN_MEE_FXB_Li_BIT3_DATA_BYTE_SEL_MAX  (1) // 0x00000001
  #define MEECR_CR_VISA_XBAR_MEMAIN_MEE_FXB_Li_BIT3_DATA_BYTE_SEL_DEF  (0x00000000)
  #define MEECR_CR_VISA_XBAR_MEMAIN_MEE_FXB_Li_BIT3_DATA_BYTE_SEL_HSH  (0x010F7E54)

  #define MEECR_CR_VISA_XBAR_MEMAIN_MEE_FXB_Li_BIT4_DATA_BIT_SEL_OFF   (16)
  #define MEECR_CR_VISA_XBAR_MEMAIN_MEE_FXB_Li_BIT4_DATA_BIT_SEL_WID   ( 3)
  #define MEECR_CR_VISA_XBAR_MEMAIN_MEE_FXB_Li_BIT4_DATA_BIT_SEL_MSK   (0x00070000)
  #define MEECR_CR_VISA_XBAR_MEMAIN_MEE_FXB_Li_BIT4_DATA_BIT_SEL_MIN   (0)
  #define MEECR_CR_VISA_XBAR_MEMAIN_MEE_FXB_Li_BIT4_DATA_BIT_SEL_MAX   (7) // 0x00000007
  #define MEECR_CR_VISA_XBAR_MEMAIN_MEE_FXB_Li_BIT4_DATA_BIT_SEL_DEF   (0x00000004)
  #define MEECR_CR_VISA_XBAR_MEMAIN_MEE_FXB_Li_BIT4_DATA_BIT_SEL_HSH   (0x03107E54)

  #define MEECR_CR_VISA_XBAR_MEMAIN_MEE_FXB_Li_BIT4_DATA_BYTE_SEL_OFF  (19)
  #define MEECR_CR_VISA_XBAR_MEMAIN_MEE_FXB_Li_BIT4_DATA_BYTE_SEL_WID  ( 1)
  #define MEECR_CR_VISA_XBAR_MEMAIN_MEE_FXB_Li_BIT4_DATA_BYTE_SEL_MSK  (0x00080000)
  #define MEECR_CR_VISA_XBAR_MEMAIN_MEE_FXB_Li_BIT4_DATA_BYTE_SEL_MIN  (0)
  #define MEECR_CR_VISA_XBAR_MEMAIN_MEE_FXB_Li_BIT4_DATA_BYTE_SEL_MAX  (1) // 0x00000001
  #define MEECR_CR_VISA_XBAR_MEMAIN_MEE_FXB_Li_BIT4_DATA_BYTE_SEL_DEF  (0x00000000)
  #define MEECR_CR_VISA_XBAR_MEMAIN_MEE_FXB_Li_BIT4_DATA_BYTE_SEL_HSH  (0x01137E54)

  #define MEECR_CR_VISA_XBAR_MEMAIN_MEE_FXB_Li_BIT5_DATA_BIT_SEL_OFF   (20)
  #define MEECR_CR_VISA_XBAR_MEMAIN_MEE_FXB_Li_BIT5_DATA_BIT_SEL_WID   ( 3)
  #define MEECR_CR_VISA_XBAR_MEMAIN_MEE_FXB_Li_BIT5_DATA_BIT_SEL_MSK   (0x00700000)
  #define MEECR_CR_VISA_XBAR_MEMAIN_MEE_FXB_Li_BIT5_DATA_BIT_SEL_MIN   (0)
  #define MEECR_CR_VISA_XBAR_MEMAIN_MEE_FXB_Li_BIT5_DATA_BIT_SEL_MAX   (7) // 0x00000007
  #define MEECR_CR_VISA_XBAR_MEMAIN_MEE_FXB_Li_BIT5_DATA_BIT_SEL_DEF   (0x00000005)
  #define MEECR_CR_VISA_XBAR_MEMAIN_MEE_FXB_Li_BIT5_DATA_BIT_SEL_HSH   (0x03147E54)

  #define MEECR_CR_VISA_XBAR_MEMAIN_MEE_FXB_Li_BIT5_DATA_BYTE_SEL_OFF  (23)
  #define MEECR_CR_VISA_XBAR_MEMAIN_MEE_FXB_Li_BIT5_DATA_BYTE_SEL_WID  ( 1)
  #define MEECR_CR_VISA_XBAR_MEMAIN_MEE_FXB_Li_BIT5_DATA_BYTE_SEL_MSK  (0x00800000)
  #define MEECR_CR_VISA_XBAR_MEMAIN_MEE_FXB_Li_BIT5_DATA_BYTE_SEL_MIN  (0)
  #define MEECR_CR_VISA_XBAR_MEMAIN_MEE_FXB_Li_BIT5_DATA_BYTE_SEL_MAX  (1) // 0x00000001
  #define MEECR_CR_VISA_XBAR_MEMAIN_MEE_FXB_Li_BIT5_DATA_BYTE_SEL_DEF  (0x00000000)
  #define MEECR_CR_VISA_XBAR_MEMAIN_MEE_FXB_Li_BIT5_DATA_BYTE_SEL_HSH  (0x01177E54)

  #define MEECR_CR_VISA_XBAR_MEMAIN_MEE_FXB_Li_BIT6_DATA_BIT_SEL_OFF   (24)
  #define MEECR_CR_VISA_XBAR_MEMAIN_MEE_FXB_Li_BIT6_DATA_BIT_SEL_WID   ( 3)
  #define MEECR_CR_VISA_XBAR_MEMAIN_MEE_FXB_Li_BIT6_DATA_BIT_SEL_MSK   (0x07000000)
  #define MEECR_CR_VISA_XBAR_MEMAIN_MEE_FXB_Li_BIT6_DATA_BIT_SEL_MIN   (0)
  #define MEECR_CR_VISA_XBAR_MEMAIN_MEE_FXB_Li_BIT6_DATA_BIT_SEL_MAX   (7) // 0x00000007
  #define MEECR_CR_VISA_XBAR_MEMAIN_MEE_FXB_Li_BIT6_DATA_BIT_SEL_DEF   (0x00000006)
  #define MEECR_CR_VISA_XBAR_MEMAIN_MEE_FXB_Li_BIT6_DATA_BIT_SEL_HSH   (0x03187E54)

  #define MEECR_CR_VISA_XBAR_MEMAIN_MEE_FXB_Li_BIT6_DATA_BYTE_SEL_OFF  (27)
  #define MEECR_CR_VISA_XBAR_MEMAIN_MEE_FXB_Li_BIT6_DATA_BYTE_SEL_WID  ( 1)
  #define MEECR_CR_VISA_XBAR_MEMAIN_MEE_FXB_Li_BIT6_DATA_BYTE_SEL_MSK  (0x08000000)
  #define MEECR_CR_VISA_XBAR_MEMAIN_MEE_FXB_Li_BIT6_DATA_BYTE_SEL_MIN  (0)
  #define MEECR_CR_VISA_XBAR_MEMAIN_MEE_FXB_Li_BIT6_DATA_BYTE_SEL_MAX  (1) // 0x00000001
  #define MEECR_CR_VISA_XBAR_MEMAIN_MEE_FXB_Li_BIT6_DATA_BYTE_SEL_DEF  (0x00000000)
  #define MEECR_CR_VISA_XBAR_MEMAIN_MEE_FXB_Li_BIT6_DATA_BYTE_SEL_HSH  (0x011B7E54)

  #define MEECR_CR_VISA_XBAR_MEMAIN_MEE_FXB_Li_BIT7_DATA_BIT_SEL_OFF   (28)
  #define MEECR_CR_VISA_XBAR_MEMAIN_MEE_FXB_Li_BIT7_DATA_BIT_SEL_WID   ( 3)
  #define MEECR_CR_VISA_XBAR_MEMAIN_MEE_FXB_Li_BIT7_DATA_BIT_SEL_MSK   (0x70000000)
  #define MEECR_CR_VISA_XBAR_MEMAIN_MEE_FXB_Li_BIT7_DATA_BIT_SEL_MIN   (0)
  #define MEECR_CR_VISA_XBAR_MEMAIN_MEE_FXB_Li_BIT7_DATA_BIT_SEL_MAX   (7) // 0x00000007
  #define MEECR_CR_VISA_XBAR_MEMAIN_MEE_FXB_Li_BIT7_DATA_BIT_SEL_DEF   (0x00000007)
  #define MEECR_CR_VISA_XBAR_MEMAIN_MEE_FXB_Li_BIT7_DATA_BIT_SEL_HSH   (0x031C7E54)

  #define MEECR_CR_VISA_XBAR_MEMAIN_MEE_FXB_Li_BIT7_DATA_BYTE_SEL_OFF  (31)
  #define MEECR_CR_VISA_XBAR_MEMAIN_MEE_FXB_Li_BIT7_DATA_BYTE_SEL_WID  ( 1)
  #define MEECR_CR_VISA_XBAR_MEMAIN_MEE_FXB_Li_BIT7_DATA_BYTE_SEL_MSK  (0x80000000)
  #define MEECR_CR_VISA_XBAR_MEMAIN_MEE_FXB_Li_BIT7_DATA_BYTE_SEL_MIN  (0)
  #define MEECR_CR_VISA_XBAR_MEMAIN_MEE_FXB_Li_BIT7_DATA_BYTE_SEL_MAX  (1) // 0x00000001
  #define MEECR_CR_VISA_XBAR_MEMAIN_MEE_FXB_Li_BIT7_DATA_BYTE_SEL_DEF  (0x00000000)
  #define MEECR_CR_VISA_XBAR_MEMAIN_MEE_FXB_Li_BIT7_DATA_BYTE_SEL_HSH  (0x011F7E54)

#define MEECR_CR_VISA_SLIDE_MEMAIN_MEE_REG                             (0x00007E58)

  #define MEECR_CR_VISA_SLIDE_MEMAIN_MEE_WINDOW_SLIDE_L0_OFF           ( 0)
  #define MEECR_CR_VISA_SLIDE_MEMAIN_MEE_WINDOW_SLIDE_L0_WID           ( 3)
  #define MEECR_CR_VISA_SLIDE_MEMAIN_MEE_WINDOW_SLIDE_L0_MSK           (0x00000007)
  #define MEECR_CR_VISA_SLIDE_MEMAIN_MEE_WINDOW_SLIDE_L0_MIN           (0)
  #define MEECR_CR_VISA_SLIDE_MEMAIN_MEE_WINDOW_SLIDE_L0_MAX           (7) // 0x00000007
  #define MEECR_CR_VISA_SLIDE_MEMAIN_MEE_WINDOW_SLIDE_L0_DEF           (0x00000000)
  #define MEECR_CR_VISA_SLIDE_MEMAIN_MEE_WINDOW_SLIDE_L0_HSH           (0x03007E58)

  #define MEECR_CR_VISA_SLIDE_MEMAIN_MEE_ALT_L0_DATA_BYTE_SEL_OFF      ( 3)
  #define MEECR_CR_VISA_SLIDE_MEMAIN_MEE_ALT_L0_DATA_BYTE_SEL_WID      ( 7)
  #define MEECR_CR_VISA_SLIDE_MEMAIN_MEE_ALT_L0_DATA_BYTE_SEL_MSK      (0x000003F8)
  #define MEECR_CR_VISA_SLIDE_MEMAIN_MEE_ALT_L0_DATA_BYTE_SEL_MIN      (0)
  #define MEECR_CR_VISA_SLIDE_MEMAIN_MEE_ALT_L0_DATA_BYTE_SEL_MAX      (127) // 0x0000007F
  #define MEECR_CR_VISA_SLIDE_MEMAIN_MEE_ALT_L0_DATA_BYTE_SEL_DEF      (0x00000000)
  #define MEECR_CR_VISA_SLIDE_MEMAIN_MEE_ALT_L0_DATA_BYTE_SEL_HSH      (0x07037E58)

  #define MEECR_CR_VISA_SLIDE_MEMAIN_MEE_WINDOW_SLIDE_L1_OFF           (10)
  #define MEECR_CR_VISA_SLIDE_MEMAIN_MEE_WINDOW_SLIDE_L1_WID           ( 3)
  #define MEECR_CR_VISA_SLIDE_MEMAIN_MEE_WINDOW_SLIDE_L1_MSK           (0x00001C00)
  #define MEECR_CR_VISA_SLIDE_MEMAIN_MEE_WINDOW_SLIDE_L1_MIN           (0)
  #define MEECR_CR_VISA_SLIDE_MEMAIN_MEE_WINDOW_SLIDE_L1_MAX           (7) // 0x00000007
  #define MEECR_CR_VISA_SLIDE_MEMAIN_MEE_WINDOW_SLIDE_L1_DEF           (0x00000000)
  #define MEECR_CR_VISA_SLIDE_MEMAIN_MEE_WINDOW_SLIDE_L1_HSH           (0x030A7E58)

  #define MEECR_CR_VISA_SLIDE_MEMAIN_MEE_ALT_L1_DATA_BYTE_SEL_OFF      (13)
  #define MEECR_CR_VISA_SLIDE_MEMAIN_MEE_ALT_L1_DATA_BYTE_SEL_WID      ( 7)
  #define MEECR_CR_VISA_SLIDE_MEMAIN_MEE_ALT_L1_DATA_BYTE_SEL_MSK      (0x000FE000)
  #define MEECR_CR_VISA_SLIDE_MEMAIN_MEE_ALT_L1_DATA_BYTE_SEL_MIN      (0)
  #define MEECR_CR_VISA_SLIDE_MEMAIN_MEE_ALT_L1_DATA_BYTE_SEL_MAX      (127) // 0x0000007F
  #define MEECR_CR_VISA_SLIDE_MEMAIN_MEE_ALT_L1_DATA_BYTE_SEL_DEF      (0x00000000)
  #define MEECR_CR_VISA_SLIDE_MEMAIN_MEE_ALT_L1_DATA_BYTE_SEL_HSH      (0x070D7E58)
#pragma pack(pop)
#endif
