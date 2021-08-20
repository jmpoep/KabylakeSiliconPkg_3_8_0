#ifndef __MrcMcRegister2xxx_h__
#define __MrcMcRegister2xxx_h__
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


#define DDRSCRAM_CR_DDRSCRAMBLECH0_REG                                 (0x00002000)

  #define DDRSCRAM_CR_DDRSCRAMBLECH0_ScramEn_OFF                       ( 0)
  #define DDRSCRAM_CR_DDRSCRAMBLECH0_ScramEn_WID                       ( 1)
  #define DDRSCRAM_CR_DDRSCRAMBLECH0_ScramEn_MSK                       (0x00000001)
  #define DDRSCRAM_CR_DDRSCRAMBLECH0_ScramEn_MIN                       (0)
  #define DDRSCRAM_CR_DDRSCRAMBLECH0_ScramEn_MAX                       (1) // 0x00000001
  #define DDRSCRAM_CR_DDRSCRAMBLECH0_ScramEn_DEF                       (0x00000000)
  #define DDRSCRAM_CR_DDRSCRAMBLECH0_ScramEn_HSH                       (0x01002000)

  #define DDRSCRAM_CR_DDRSCRAMBLECH0_ScramKey_OFF                      ( 1)
  #define DDRSCRAM_CR_DDRSCRAMBLECH0_ScramKey_WID                      (16)
  #define DDRSCRAM_CR_DDRSCRAMBLECH0_ScramKey_MSK                      (0x0001FFFE)
  #define DDRSCRAM_CR_DDRSCRAMBLECH0_ScramKey_MIN                      (0)
  #define DDRSCRAM_CR_DDRSCRAMBLECH0_ScramKey_MAX                      (65535) // 0x0000FFFF
  #define DDRSCRAM_CR_DDRSCRAMBLECH0_ScramKey_DEF                      (0x00000000)
  #define DDRSCRAM_CR_DDRSCRAMBLECH0_ScramKey_HSH                      (0x10012000)

  #define DDRSCRAM_CR_DDRSCRAMBLECH0_ClockGateAB_OFF                   (17)
  #define DDRSCRAM_CR_DDRSCRAMBLECH0_ClockGateAB_WID                   ( 2)
  #define DDRSCRAM_CR_DDRSCRAMBLECH0_ClockGateAB_MSK                   (0x00060000)
  #define DDRSCRAM_CR_DDRSCRAMBLECH0_ClockGateAB_MIN                   (0)
  #define DDRSCRAM_CR_DDRSCRAMBLECH0_ClockGateAB_MAX                   (3) // 0x00000003
  #define DDRSCRAM_CR_DDRSCRAMBLECH0_ClockGateAB_DEF                   (0x00000000)
  #define DDRSCRAM_CR_DDRSCRAMBLECH0_ClockGateAB_HSH                   (0x02112000)

  #define DDRSCRAM_CR_DDRSCRAMBLECH0_ClockGateC_OFF                    (19)
  #define DDRSCRAM_CR_DDRSCRAMBLECH0_ClockGateC_WID                    ( 2)
  #define DDRSCRAM_CR_DDRSCRAMBLECH0_ClockGateC_MSK                    (0x00180000)
  #define DDRSCRAM_CR_DDRSCRAMBLECH0_ClockGateC_MIN                    (0)
  #define DDRSCRAM_CR_DDRSCRAMBLECH0_ClockGateC_MAX                    (3) // 0x00000003
  #define DDRSCRAM_CR_DDRSCRAMBLECH0_ClockGateC_DEF                    (0x00000000)
  #define DDRSCRAM_CR_DDRSCRAMBLECH0_ClockGateC_HSH                    (0x02132000)

  #define DDRSCRAM_CR_DDRSCRAMBLECH0_EnableDbiAB_OFF                   (21)
  #define DDRSCRAM_CR_DDRSCRAMBLECH0_EnableDbiAB_WID                   ( 1)
  #define DDRSCRAM_CR_DDRSCRAMBLECH0_EnableDbiAB_MSK                   (0x00200000)
  #define DDRSCRAM_CR_DDRSCRAMBLECH0_EnableDbiAB_MIN                   (0)
  #define DDRSCRAM_CR_DDRSCRAMBLECH0_EnableDbiAB_MAX                   (1) // 0x00000001
  #define DDRSCRAM_CR_DDRSCRAMBLECH0_EnableDbiAB_DEF                   (0x00000000)
  #define DDRSCRAM_CR_DDRSCRAMBLECH0_EnableDbiAB_HSH                   (0x01152000)

  #define DDRSCRAM_CR_DDRSCRAMBLECH0_Spare_OFF                         (22)
  #define DDRSCRAM_CR_DDRSCRAMBLECH0_Spare_WID                         (10)
  #define DDRSCRAM_CR_DDRSCRAMBLECH0_Spare_MSK                         (0xFFC00000)
  #define DDRSCRAM_CR_DDRSCRAMBLECH0_Spare_MIN                         (0)
  #define DDRSCRAM_CR_DDRSCRAMBLECH0_Spare_MAX                         (1023) // 0x000003FF
  #define DDRSCRAM_CR_DDRSCRAMBLECH0_Spare_DEF                         (0x00000000)
  #define DDRSCRAM_CR_DDRSCRAMBLECH0_Spare_HSH                         (0x0A162000)

#define DDRSCRAM_CR_DDRSCRAMBLECH1_REG                                 (0x00002004)

  #define DDRSCRAM_CR_DDRSCRAMBLECH1_ScramEn_OFF                       ( 0)
  #define DDRSCRAM_CR_DDRSCRAMBLECH1_ScramEn_WID                       ( 1)
  #define DDRSCRAM_CR_DDRSCRAMBLECH1_ScramEn_MSK                       (0x00000001)
  #define DDRSCRAM_CR_DDRSCRAMBLECH1_ScramEn_MIN                       (0)
  #define DDRSCRAM_CR_DDRSCRAMBLECH1_ScramEn_MAX                       (1) // 0x00000001
  #define DDRSCRAM_CR_DDRSCRAMBLECH1_ScramEn_DEF                       (0x00000000)
  #define DDRSCRAM_CR_DDRSCRAMBLECH1_ScramEn_HSH                       (0x01002004)

  #define DDRSCRAM_CR_DDRSCRAMBLECH1_ScramKey_OFF                      ( 1)
  #define DDRSCRAM_CR_DDRSCRAMBLECH1_ScramKey_WID                      (16)
  #define DDRSCRAM_CR_DDRSCRAMBLECH1_ScramKey_MSK                      (0x0001FFFE)
  #define DDRSCRAM_CR_DDRSCRAMBLECH1_ScramKey_MIN                      (0)
  #define DDRSCRAM_CR_DDRSCRAMBLECH1_ScramKey_MAX                      (65535) // 0x0000FFFF
  #define DDRSCRAM_CR_DDRSCRAMBLECH1_ScramKey_DEF                      (0x00000000)
  #define DDRSCRAM_CR_DDRSCRAMBLECH1_ScramKey_HSH                      (0x10012004)

  #define DDRSCRAM_CR_DDRSCRAMBLECH1_ClockGateAB_OFF                   (17)
  #define DDRSCRAM_CR_DDRSCRAMBLECH1_ClockGateAB_WID                   ( 2)
  #define DDRSCRAM_CR_DDRSCRAMBLECH1_ClockGateAB_MSK                   (0x00060000)
  #define DDRSCRAM_CR_DDRSCRAMBLECH1_ClockGateAB_MIN                   (0)
  #define DDRSCRAM_CR_DDRSCRAMBLECH1_ClockGateAB_MAX                   (3) // 0x00000003
  #define DDRSCRAM_CR_DDRSCRAMBLECH1_ClockGateAB_DEF                   (0x00000000)
  #define DDRSCRAM_CR_DDRSCRAMBLECH1_ClockGateAB_HSH                   (0x02112004)

  #define DDRSCRAM_CR_DDRSCRAMBLECH1_ClockGateC_OFF                    (19)
  #define DDRSCRAM_CR_DDRSCRAMBLECH1_ClockGateC_WID                    ( 2)
  #define DDRSCRAM_CR_DDRSCRAMBLECH1_ClockGateC_MSK                    (0x00180000)
  #define DDRSCRAM_CR_DDRSCRAMBLECH1_ClockGateC_MIN                    (0)
  #define DDRSCRAM_CR_DDRSCRAMBLECH1_ClockGateC_MAX                    (3) // 0x00000003
  #define DDRSCRAM_CR_DDRSCRAMBLECH1_ClockGateC_DEF                    (0x00000000)
  #define DDRSCRAM_CR_DDRSCRAMBLECH1_ClockGateC_HSH                    (0x02132004)

  #define DDRSCRAM_CR_DDRSCRAMBLECH1_EnableDbiAB_OFF                   (21)
  #define DDRSCRAM_CR_DDRSCRAMBLECH1_EnableDbiAB_WID                   ( 1)
  #define DDRSCRAM_CR_DDRSCRAMBLECH1_EnableDbiAB_MSK                   (0x00200000)
  #define DDRSCRAM_CR_DDRSCRAMBLECH1_EnableDbiAB_MIN                   (0)
  #define DDRSCRAM_CR_DDRSCRAMBLECH1_EnableDbiAB_MAX                   (1) // 0x00000001
  #define DDRSCRAM_CR_DDRSCRAMBLECH1_EnableDbiAB_DEF                   (0x00000000)
  #define DDRSCRAM_CR_DDRSCRAMBLECH1_EnableDbiAB_HSH                   (0x01152004)

  #define DDRSCRAM_CR_DDRSCRAMBLECH1_Spare_OFF                         (22)
  #define DDRSCRAM_CR_DDRSCRAMBLECH1_Spare_WID                         (10)
  #define DDRSCRAM_CR_DDRSCRAMBLECH1_Spare_MSK                         (0xFFC00000)
  #define DDRSCRAM_CR_DDRSCRAMBLECH1_Spare_MIN                         (0)
  #define DDRSCRAM_CR_DDRSCRAMBLECH1_Spare_MAX                         (1023) // 0x000003FF
  #define DDRSCRAM_CR_DDRSCRAMBLECH1_Spare_DEF                         (0x00000000)
  #define DDRSCRAM_CR_DDRSCRAMBLECH1_Spare_HSH                         (0x0A162004)

#define DDRSCRAM_CR_DDRMISCCONTROL0_REG                                (0x00002008)

  #define DDRSCRAM_CR_DDRMISCCONTROL0_WL_WakeCycles_OFF                ( 0)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_WL_WakeCycles_WID                ( 2)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_WL_WakeCycles_MSK                (0x00000003)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_WL_WakeCycles_MIN                (0)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_WL_WakeCycles_MAX                (3) // 0x00000003
  #define DDRSCRAM_CR_DDRMISCCONTROL0_WL_WakeCycles_DEF                (0x00000000)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_WL_WakeCycles_HSH                (0x02002008)

  #define DDRSCRAM_CR_DDRMISCCONTROL0_WL_SleepCycles_OFF               ( 2)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_WL_SleepCycles_WID               ( 3)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_WL_SleepCycles_MSK               (0x0000001C)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_WL_SleepCycles_MIN               (0)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_WL_SleepCycles_MAX               (7) // 0x00000007
  #define DDRSCRAM_CR_DDRMISCCONTROL0_WL_SleepCycles_DEF               (0x00000000)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_WL_SleepCycles_HSH               (0x03022008)

  #define DDRSCRAM_CR_DDRMISCCONTROL0_ForceCompUpdate_OFF              ( 5)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_ForceCompUpdate_WID              ( 1)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_ForceCompUpdate_MSK              (0x00000020)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_ForceCompUpdate_MIN              (0)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_ForceCompUpdate_MAX              (1) // 0x00000001
  #define DDRSCRAM_CR_DDRMISCCONTROL0_ForceCompUpdate_DEF              (0x00000000)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_ForceCompUpdate_HSH              (0x01052008)

  #define DDRSCRAM_CR_DDRMISCCONTROL0_WeakLock_Latency_OFF             ( 6)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_WeakLock_Latency_WID             ( 4)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_WeakLock_Latency_MSK             (0x000003C0)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_WeakLock_Latency_MIN             (0)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_WeakLock_Latency_MAX             (15) // 0x0000000F
  #define DDRSCRAM_CR_DDRMISCCONTROL0_WeakLock_Latency_DEF             (0x0000000C)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_WeakLock_Latency_HSH             (0x04062008)

  #define DDRSCRAM_CR_DDRMISCCONTROL0_DdrNoChInterleave_OFF            (10)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_DdrNoChInterleave_WID            ( 1)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_DdrNoChInterleave_MSK            (0x00000400)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_DdrNoChInterleave_MIN            (0)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_DdrNoChInterleave_MAX            (1) // 0x00000001
  #define DDRSCRAM_CR_DDRMISCCONTROL0_DdrNoChInterleave_DEF            (0x00000000)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_DdrNoChInterleave_HSH            (0x010A2008)

  #define DDRSCRAM_CR_DDRMISCCONTROL0_LPDDR_Mode_OFF                   (11)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_LPDDR_Mode_WID                   ( 1)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_LPDDR_Mode_MSK                   (0x00000800)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_LPDDR_Mode_MIN                   (0)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_LPDDR_Mode_MAX                   (1) // 0x00000001
  #define DDRSCRAM_CR_DDRMISCCONTROL0_LPDDR_Mode_DEF                   (0x00000000)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_LPDDR_Mode_HSH                   (0x010B2008)

  #define DDRSCRAM_CR_DDRMISCCONTROL0_CKEMappingCh0_OFF                (12)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_CKEMappingCh0_WID                ( 4)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_CKEMappingCh0_MSK                (0x0000F000)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_CKEMappingCh0_MIN                (0)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_CKEMappingCh0_MAX                (15) // 0x0000000F
  #define DDRSCRAM_CR_DDRMISCCONTROL0_CKEMappingCh0_DEF                (0x0000000A)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_CKEMappingCh0_HSH                (0x040C2008)

  #define DDRSCRAM_CR_DDRMISCCONTROL0_CKEMappingCh1_OFF                (16)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_CKEMappingCh1_WID                ( 4)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_CKEMappingCh1_MSK                (0x000F0000)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_CKEMappingCh1_MIN                (0)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_CKEMappingCh1_MAX                (15) // 0x0000000F
  #define DDRSCRAM_CR_DDRMISCCONTROL0_CKEMappingCh1_DEF                (0x0000000A)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_CKEMappingCh1_HSH                (0x04102008)

  #define DDRSCRAM_CR_DDRMISCCONTROL0_Ddr4_Mode_OFF                    (20)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_Ddr4_Mode_WID                    ( 1)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_Ddr4_Mode_MSK                    (0x00100000)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_Ddr4_Mode_MIN                    (0)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_Ddr4_Mode_MAX                    (1) // 0x00000001
  #define DDRSCRAM_CR_DDRMISCCONTROL0_Ddr4_Mode_DEF                    (0x00000000)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_Ddr4_Mode_HSH                    (0x01142008)

  #define DDRSCRAM_CR_DDRMISCCONTROL0_ClkGateDisable_OFF               (21)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_ClkGateDisable_WID               ( 1)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_ClkGateDisable_MSK               (0x00200000)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_ClkGateDisable_MIN               (0)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_ClkGateDisable_MAX               (1) // 0x00000001
  #define DDRSCRAM_CR_DDRMISCCONTROL0_ClkGateDisable_DEF               (0x00000000)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_ClkGateDisable_HSH               (0x01152008)

  #define DDRSCRAM_CR_DDRMISCCONTROL0_DllDataWeakLckEn_OFF             (22)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_DllDataWeakLckEn_WID             ( 1)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_DllDataWeakLckEn_MSK             (0x00400000)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_DllDataWeakLckEn_MIN             (0)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_DllDataWeakLckEn_MAX             (1) // 0x00000001
  #define DDRSCRAM_CR_DDRMISCCONTROL0_DllDataWeakLckEn_DEF             (0x00000001)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_DllDataWeakLckEn_HSH             (0x01162008)

  #define DDRSCRAM_CR_DDRMISCCONTROL0_DataClkGateDisAtIdle_OFF         (23)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_DataClkGateDisAtIdle_WID         ( 1)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_DataClkGateDisAtIdle_MSK         (0x00800000)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_DataClkGateDisAtIdle_MIN         (0)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_DataClkGateDisAtIdle_MAX         (1) // 0x00000001
  #define DDRSCRAM_CR_DDRMISCCONTROL0_DataClkGateDisAtIdle_DEF         (0x00000000)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_DataClkGateDisAtIdle_HSH         (0x01172008)

  #define DDRSCRAM_CR_DDRMISCCONTROL0_Spare_OFF                        (24)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_Spare_WID                        ( 8)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_Spare_MSK                        (0xFF000000)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_Spare_MIN                        (0)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_Spare_MAX                        (255) // 0x000000FF
  #define DDRSCRAM_CR_DDRMISCCONTROL0_Spare_DEF                        (0x00000000)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_Spare_HSH                        (0x08182008)
#pragma pack(pop)
#endif
