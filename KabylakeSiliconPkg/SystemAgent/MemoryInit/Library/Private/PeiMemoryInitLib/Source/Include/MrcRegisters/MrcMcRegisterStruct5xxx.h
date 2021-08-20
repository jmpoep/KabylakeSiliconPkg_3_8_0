#ifndef __MrcMcRegisterStruct5xxx_h__
#define __MrcMcRegisterStruct5xxx_h__
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
    UINT32 DDR_TYPE                                :  2;  // Bits 1:0
    UINT32                                         :  2;  // Bits 3:2
    UINT32 CH_L_MAP                                :  1;  // Bits 4:4
    UINT32                                         :  3;  // Bits 7:5
    UINT32 STKD_MODE                               :  1;  // Bits 8:8
    UINT32 STKD_MODE_CH1                           :  1;  // Bits 9:9
    UINT32                                         :  2;  // Bits 11:10
    UINT32 CH_S_SIZE                               :  7;  // Bits 18:12
    UINT32                                         :  5;  // Bits 23:19
    UINT32 STKD_MODE_CH_BITS                       :  3;  // Bits 26:24
    UINT32                                         :  5;  // Bits 31:27
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCDECS_CR_MAD_INTER_CHANNEL_MCMAIN_STRUCT;

typedef union {
  struct {
    UINT32 DIMM_L_MAP                              :  1;  // Bits 0:0
    UINT32                                         :  3;  // Bits 3:1
    UINT32 RI                                      :  1;  // Bits 4:4
    UINT32                                         :  3;  // Bits 7:5
    UINT32 EIM                                     :  1;  // Bits 8:8
    UINT32                                         :  3;  // Bits 11:9
    UINT32 ECC                                     :  2;  // Bits 13:12
    UINT32                                         :  10;  // Bits 23:14
    UINT32 HORI                                    :  1;  // Bits 24:24
    UINT32                                         :  3;  // Bits 27:25
    UINT32 HORI_ADDR                               :  3;  // Bits 30:28
    UINT32                                         :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCDECS_CR_MAD_INTRA_CH0_MCMAIN_STRUCT;

typedef union {
  struct {
    UINT32 DIMM_L_MAP                              :  1;  // Bits 0:0
    UINT32                                         :  3;  // Bits 3:1
    UINT32 RI                                      :  1;  // Bits 4:4
    UINT32                                         :  3;  // Bits 7:5
    UINT32 EIM                                     :  1;  // Bits 8:8
    UINT32                                         :  3;  // Bits 11:9
    UINT32 ECC                                     :  2;  // Bits 13:12
    UINT32                                         :  10;  // Bits 23:14
    UINT32 HORI                                    :  1;  // Bits 24:24
    UINT32                                         :  3;  // Bits 27:25
    UINT32 HORI_ADDR                               :  3;  // Bits 30:28
    UINT32                                         :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCDECS_CR_MAD_INTRA_CH1_MCMAIN_STRUCT;

typedef union {
  struct {
    UINT32 DIMM_L_SIZE                             :  6;  // Bits 5:0
    UINT32                                         :  2;  // Bits 7:6
    UINT32 DLW                                     :  2;  // Bits 9:8
    UINT32 DLNOR                                   :  1;  // Bits 10:10
    UINT32 DL8Gb                                   :  1;  // Bits 11:11
    UINT32                                         :  4;  // Bits 15:12
    UINT32 DIMM_S_SIZE                             :  6;  // Bits 21:16
    UINT32                                         :  2;  // Bits 23:22
    UINT32 DSW                                     :  2;  // Bits 25:24
    UINT32 DSNOR                                   :  1;  // Bits 26:26
    UINT32 DS8Gb                                   :  1;  // Bits 27:27
    UINT32                                         :  4;  // Bits 31:28
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCDECS_CR_MAD_DIMM_CH0_MCMAIN_STRUCT;

typedef union {
  struct {
    UINT32 DIMM_L_SIZE                             :  6;  // Bits 5:0
    UINT32                                         :  2;  // Bits 7:6
    UINT32 DLW                                     :  2;  // Bits 9:8
    UINT32 DLNOR                                   :  1;  // Bits 10:10
    UINT32 DL8Gb                                   :  1;  // Bits 11:11
    UINT32                                         :  4;  // Bits 15:12
    UINT32 DIMM_S_SIZE                             :  6;  // Bits 21:16
    UINT32                                         :  2;  // Bits 23:22
    UINT32 DSW                                     :  2;  // Bits 25:24
    UINT32 DSNOR                                   :  1;  // Bits 26:26
    UINT32 DS8Gb                                   :  1;  // Bits 27:27
    UINT32                                         :  4;  // Bits 31:28
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCDECS_CR_MAD_DIMM_CH1_MCMAIN_STRUCT;

typedef union {
  struct {
    UINT32 Spare_RW                                :  16;  // Bits 15:0
    UINT32 spare_RW_V                              :  16;  // Bits 31:16
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCDECS_CR_MCDECS_MISC_MCMAIN_STRUCT;

typedef union {
  struct {
    UINT32 increase_rcomp                          :  1;  // Bits 0:0
    UINT32 rank2_to_rank1                          :  1;  // Bits 1:1
    UINT32 ovrd_pcu_sr_exit                        :  1;  // Bits 2:2
    UINT32 psmi_freeze_pwm_counters                :  1;  // Bits 3:3
    UINT32 dis_single_ch_sr                        :  1;  // Bits 4:4
    UINT32 dis_other_ch_stolen_ref                 :  1;  // Bits 5:5
    UINT32                                         :  21;  // Bits 26:6
    UINT32 dis_iosf_sb_clk_gate                    :  1;  // Bits 27:27
    UINT32 dis_glbdrv_clk_gate                     :  1;  // Bits 28:28
    UINT32 dis_reg_clk_gate                        :  1;  // Bits 29:29
    UINT32 dis_msg_clk_gate                        :  1;  // Bits 30:30
    UINT32 dis_clk_gate                            :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCDECS_CR_MCDECS_CBIT_MCMAIN_STRUCT;

typedef union {
  struct {
    UINT32                                         :  6;  // Bits 5:0
    UINT32 HASH_MASK                               :  14;  // Bits 19:6
    UINT32                                         :  4;  // Bits 23:20
    UINT32 HASH_LSB_MASK_BIT                       :  3;  // Bits 26:24
    UINT32                                         :  1;  // Bits 27:27
    UINT32 HASH_MODE                               :  1;  // Bits 28:28
    UINT32                                         :  3;  // Bits 31:29
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCDECS_CR_CHANNEL_HASH_MCMAIN_STRUCT;

typedef union {
  struct {
    UINT32 pu_mrc_done                             :  1;  // Bits 0:0
    UINT32 ddr_reset                               :  1;  // Bits 1:1
    UINT32                                         :  1;  // Bits 2:2
    UINT32 refresh_enable                          :  1;  // Bits 3:3
    UINT32                                         :  1;  // Bits 4:4
    UINT32 mc_init_done_ack                        :  1;  // Bits 5:5
    UINT32                                         :  1;  // Bits 6:6
    UINT32 mrc_done                                :  1;  // Bits 7:7
    UINT32 safe_sr                                 :  1;  // Bits 8:8
    UINT32                                         :  1;  // Bits 9:9
    UINT32 HVM_Gate_DDR_Reset                      :  1;  // Bits 10:10
    UINT32 mrc_save_low                            :  1;  // Bits 11:11
    UINT32 mrc_save_high                           :  1;  // Bits 12:12
    UINT32                                         :  9;  // Bits 21:13
    UINT32 dclk_enable                             :  1;  // Bits 22:22
    UINT32 reset_io                                :  1;  // Bits 23:23
    UINT32 no_block_reset_io                       :  1;  // Bits 24:24
    UINT32                                         :  7;  // Bits 31:25
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCDECS_CR_MC_INIT_STATE_G_MCMAIN_STRUCT;

typedef union {
  struct {
    UINT32 REVISION                                :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCDECS_CR_MRC_REVISION_MCMAIN_STRUCT;

typedef union {
  struct {
    UINT32 count                                   :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCDECS_CR_PWM_GT_REQCOUNT_MCMAIN_STRUCT;

typedef union {
  struct {
    UINT32 count                                   :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCDECS_CR_PWM_IA_REQCOUNT_MCMAIN_STRUCT;

typedef union {
  struct {
    UINT32 count                                   :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCDECS_CR_PWM_IO_REQCOUNT_MCMAIN_STRUCT;

typedef union {
  struct {
    UINT32 count                                   :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCDECS_CR_PWM_RDDATA_COUNT_MCMAIN_STRUCT;

typedef union {
  struct {
    UINT32 count                                   :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCDECS_CR_PWM_WRDATA_COUNT_MCMAIN_STRUCT;

typedef union {
  struct {
    UINT32 count                                   :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCDECS_CR_PWM_COMMAND_COUNT_MCMAIN_STRUCT;

typedef union {
  struct {
    UINT32 count                                   :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCDECS_CR_PWM_NON_SR_COUNT_MCMAIN_STRUCT;

typedef union {
  struct {
    UINT32 Idle_timer                              :  16;  // Bits 15:0
    UINT32 SR_Enable                               :  1;  // Bits 16:16
    UINT32                                         :  15;  // Bits 31:17
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCDECS_CR_PM_SREF_CONFIG_MCMAIN_STRUCT;

typedef union {
  struct {
    UINT32 VC1_WR_CNFLT                            :  1;  // Bits 0:0
    UINT32 VC1_RD_CNFLT                            :  1;  // Bits 1:1
    UINT32                                         :  30;  // Bits 31:2
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCDECS_CR_ATMC_STS_MCMAIN_STRUCT;

typedef union {
  struct {
    UINT32 count                                   :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCDECS_CR_READ_OCCUPANCY_COUNT_MCMAIN_STRUCT;

typedef union {
  struct {
    UINT32 stall_until_drain                       :  1;  // Bits 0:0
    UINT32 stall_input                             :  1;  // Bits 1:1
    UINT32                                         :  2;  // Bits 3:2
    UINT32 mc_drained                              :  1;  // Bits 4:4
    UINT32                                         :  3;  // Bits 7:5
    UINT32 sr_state                                :  1;  // Bits 8:8
    UINT32                                         :  3;  // Bits 11:9
    UINT32 stall_state                             :  1;  // Bits 12:12
    UINT32                                         :  19;  // Bits 31:13
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCDECS_CR_STALL_DRAIN_MCMAIN_STRUCT;

typedef union {
  struct {
    UINT32 NonVC1Threshold                         :  4;  // Bits 3:0
    UINT32 VC1RdThreshold                          :  4;  // Bits 7:4
    UINT32 FixedRateEn                             :  1;  // Bits 8:8
    UINT32 HIGH_PRIO_LIM                           :  3;  // Bits 11:9
    UINT32 LOW_PRIO_LIM                            :  3;  // Bits 14:12
    UINT32 spare                                   :  8;  // Bits 22:15
    UINT32                                         :  9;  // Bits 31:23
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCDECS_CR_IPC_MC_ARB_MCMAIN_STRUCT;

typedef union {
  struct {
    UINT32 RPQ_count                               :  5;  // Bits 4:0
    UINT32                                         :  3;  // Bits 7:5
    UINT32 WPQ_count                               :  7;  // Bits 14:8
    UINT32                                         :  1;  // Bits 15:15
    UINT32 IPQ_count                               :  4;  // Bits 19:16
    UINT32                                         :  12;  // Bits 31:20
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCDECS_CR_QUEUE_CREDIT_C_MCMAIN_STRUCT;

typedef union {
  struct {
    UINT32 count                                   :  16;  // Bits 15:0
    UINT32 First_Rcomp_done                        :  1;  // Bits 16:16
    UINT32                                         :  15;  // Bits 31:17
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCDECS_CR_RCOMP_TIMER_MCMAIN_STRUCT;

typedef union {
  struct {
    UINT32 Address                                 :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCDECS_CR_ECC_INJ_ADDR_COMPARE_MCMAIN_STRUCT;

typedef union {
  struct {
    UINT32 Mask                                    :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCDECS_CR_ECC_INJ_ADDR_MASK_MCMAIN_STRUCT;

typedef union {
  struct {
    UINT32 EN_CLK                                  :  1;  // Bits 0:0
    UINT32 L0_DATA_BYTE_SEL                        :  7;  // Bits 7:1
    UINT32 L0_BYP_SEL                              :  1;  // Bits 8:8
    UINT32 L1_DATA_BYTE_SEL                        :  7;  // Bits 15:9
    UINT32 L1_BYP_SEL                              :  1;  // Bits 16:16
    UINT32                                         :  14;  // Bits 30:17
    UINT32 VORANGE                                 :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCDECS_CR_VISA_CTL_MCDECS_MCMAIN_STRUCT;

typedef union {
  struct {
    UINT32 FXB_Li_BIT0_DATA_BIT_SEL                :  3;  // Bits 2:0
    UINT32 FXB_Li_BIT0_DATA_BYTE_SEL               :  1;  // Bits 3:3
    UINT32 FXB_Li_BIT1_DATA_BIT_SEL                :  3;  // Bits 6:4
    UINT32 FXB_Li_BIT1_DATA_BYTE_SEL               :  1;  // Bits 7:7
    UINT32 FXB_Li_BIT2_DATA_BIT_SEL                :  3;  // Bits 10:8
    UINT32 FXB_Li_BIT2_DATA_BYTE_SEL               :  1;  // Bits 11:11
    UINT32 FXB_Li_BIT3_DATA_BIT_SEL                :  3;  // Bits 14:12
    UINT32 FXB_Li_BIT3_DATA_BYTE_SEL               :  1;  // Bits 15:15
    UINT32 FXB_Li_BIT4_DATA_BIT_SEL                :  3;  // Bits 18:16
    UINT32 FXB_Li_BIT4_DATA_BYTE_SEL               :  1;  // Bits 19:19
    UINT32 FXB_Li_BIT5_DATA_BIT_SEL                :  3;  // Bits 22:20
    UINT32 FXB_Li_BIT5_DATA_BYTE_SEL               :  1;  // Bits 23:23
    UINT32 FXB_Li_BIT6_DATA_BIT_SEL                :  3;  // Bits 26:24
    UINT32 FXB_Li_BIT6_DATA_BYTE_SEL               :  1;  // Bits 27:27
    UINT32 FXB_Li_BIT7_DATA_BIT_SEL                :  3;  // Bits 30:28
    UINT32 FXB_Li_BIT7_DATA_BYTE_SEL               :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCDECS_CR_VISA_XBAR_MCDECS_MCMAIN_STRUCT;

typedef union {
  struct {
    UINT32 WINDOW_SLIDE_L0                         :  3;  // Bits 2:0
    UINT32 ALT_L0_DATA_BYTE_SEL                    :  7;  // Bits 9:3
    UINT32 WINDOW_SLIDE_L1                         :  3;  // Bits 12:10
    UINT32 ALT_L1_DATA_BYTE_SEL                    :  7;  // Bits 19:13
    UINT32                                         :  12;  // Bits 31:20
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCDECS_CR_VISA_SLIDE_MCDECS_MCMAIN_STRUCT;

typedef union {
  struct {
    UINT32                                         :  6;  // Bits 5:0
    UINT32 sys_addrLow                             :  26;  // Bits 31:6
    UINT32 sys_addrHigh                            :  7;  // Bits 38:32
    UINT32                                         :  23;  // Bits 61:39
    UINT32 is_tcm                                  :  1;  // Bits 62:62
    UINT32 valid                                   :  1;  // Bits 63:63
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} MCDECS_CR_BIT_ERROR_RECOVERY_SOURCE_SYSADDR_MCMAIN_0_STRUCT;

typedef union {
  struct {
    UINT32                                         :  6;  // Bits 5:0
    UINT32 sys_addrLow                             :  26;  // Bits 31:6
    UINT32 sys_addrHigh                            :  7;  // Bits 38:32
    UINT32                                         :  23;  // Bits 61:39
    UINT32 is_tcm                                  :  1;  // Bits 62:62
    UINT32 valid                                   :  1;  // Bits 63:63
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} MCDECS_CR_BIT_ERROR_RECOVERY_SOURCE_SYSADDR_MCMAIN_1_STRUCT;

typedef union {
  struct {
    UINT32                                         :  6;  // Bits 5:0
    UINT32 sys_addrLow                             :  26;  // Bits 31:6
    UINT32 sys_addrHigh                            :  7;  // Bits 38:32
    UINT32                                         :  23;  // Bits 61:39
    UINT32 is_tcm                                  :  1;  // Bits 62:62
    UINT32 valid                                   :  1;  // Bits 63:63
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} MCDECS_CR_BIT_ERROR_RECOVERY_SOURCE_SYSADDR_MCMAIN_2_STRUCT;

typedef union {
  struct {
    UINT32                                         :  6;  // Bits 5:0
    UINT32 sys_addrLow                             :  26;  // Bits 31:6
    UINT32 sys_addrHigh                            :  7;  // Bits 38:32
    UINT32                                         :  23;  // Bits 61:39
    UINT32 is_tcm                                  :  1;  // Bits 62:62
    UINT32 valid                                   :  1;  // Bits 63:63
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} MCDECS_CR_BIT_ERROR_RECOVERY_SOURCE_SYSADDR_MCMAIN_3_STRUCT;

typedef union {
  struct {
    UINT32 lock_addr_map                           :  1;  // Bits 0:0
    UINT32 lock_mc_config                          :  1;  // Bits 1:1
    UINT32 lock_iosav_init                         :  1;  // Bits 2:2
    UINT32 lock_pwr_mngment                        :  1;  // Bits 3:3
    UINT32                                         :  3;  // Bits 6:4
    UINT32 lock_mc_dft                             :  1;  // Bits 7:7
    UINT32                                         :  24;  // Bits 31:8
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCDECS_CR_MC_LOCK_MCMAIN_STRUCT;

typedef union {
  struct {
    UINT32                                         :  6;  // Bits 5:0
    UINT32 sys_addrLow                             :  26;  // Bits 31:6
    UINT32 sys_addrHigh                            :  7;  // Bits 38:32
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} MCDECS_CR_GDXC_DDR_SYS_ADD_FILTER_MASK_MCMAIN_0_STRUCT;

typedef union {
  struct {
    UINT32                                         :  6;  // Bits 5:0
    UINT32 sys_addrLow                             :  26;  // Bits 31:6
    UINT32 sys_addrHigh                            :  7;  // Bits 38:32
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} MCDECS_CR_GDXC_DDR_SYS_ADD_FILTER_MASK_MCMAIN_1_STRUCT;

typedef union {
  struct {
    UINT32                                         :  6;  // Bits 5:0
    UINT32 sys_addrLow                             :  26;  // Bits 31:6
    UINT32 sys_addrHigh                            :  7;  // Bits 38:32
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} MCDECS_CR_GDXC_DDR_SYS_ADD_FILTER_MATCH_MCMAIN_0_STRUCT;

typedef union {
  struct {
    UINT32                                         :  6;  // Bits 5:0
    UINT32 sys_addrLow                             :  26;  // Bits 31:6
    UINT32 sys_addrHigh                            :  7;  // Bits 38:32
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} MCDECS_CR_GDXC_DDR_SYS_ADD_FILTER_MATCH_MCMAIN_1_STRUCT;

typedef union {
  struct {
    UINT32                                         :  6;  // Bits 5:0
    UINT32 sys_addrLow                             :  26;  // Bits 31:6
    UINT32 sys_addrHigh                            :  7;  // Bits 38:32
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} MCDECS_CR_GDXC_DDR_SYS_ADD_TRIGGER_MASK_MCMAIN_STRUCT;

typedef union {
  struct {
    UINT32                                         :  6;  // Bits 5:0
    UINT32 sys_addrLow                             :  26;  // Bits 31:6
    UINT32 sys_addrHigh                            :  7;  // Bits 38:32
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} MCDECS_CR_GDXC_DDR_SYS_ADD_TRIGGER_MATCH_MCMAIN_STRUCT;

typedef union {
  struct {
    UINT32 Isoch_time_window                       :  17;  // Bits 16:0
    UINT32 Write_starvation_window                 :  11;  // Bits 27:17
    UINT32 Read_starvation_windowLow               :  4;  // Bits 31:28
    UINT32 Read_starvation_windowHigh              :  7;  // Bits 38:32
    UINT32 VC0_read_count                          :  9;  // Bits 47:39
    UINT32 VC1_Read_starvation_en                  :  1;  // Bits 48:48
    UINT32 Write_starvation_in_Isoc_en             :  1;  // Bits 49:49
    UINT32 Read_starvation_in_Isoch_en             :  1;  // Bits 50:50
    UINT32 VC0_counter_disable                     :  1;  // Bits 51:51
    UINT32 Force_MCVC1Demote                       :  1;  // Bits 52:52
    UINT32 Disable_MCVC1Demote                     :  1;  // Bits 53:53
    UINT32 MC_Ignore_VC1Demote                     :  1;  // Bits 54:54
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} MCDECS_CR_SC_QOS_MCMAIN_STRUCT;

typedef union {
  struct {
    UINT32 GLB_GRACE_CNT                           :  5;  // Bits 4:0
    UINT32 MNT_GLB_GRACE_CNT                       :  5;  // Bits 9:5
    UINT32 MNT_GLB_DRV_GATE_DIS                    :  1;  // Bits 10:10
    UINT32 SCHEDS_GLB_DRV_GATE_DIS                 :  1;  // Bits 11:11
    UINT32 WDB_GLB_DRV_GATE_DIS                    :  1;  // Bits 12:12
    UINT32 MAINS_GLB_DRV_GATE_DIS                  :  1;  // Bits 13:13
    UINT32 DDRPL_GLB_DRV_GATE_DIS                  :  1;  // Bits 14:14
    UINT32                                         :  17;  // Bits 31:15
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCDECS_CR_MC_GLOBAL_DRIVER_GATE_CFG_MCMAIN_STRUCT;

typedef union {
  struct {
    UINT32                                         :  12;  // Bits 11:0
    UINT32 sys_addrLow                             :  20;  // Bits 31:12
    UINT32 sys_addrHigh                            :  7;  // Bits 38:32
    UINT32                                         :  24;  // Bits 62:39
    UINT32 valid                                   :  1;  // Bits 63:63
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} MCDECS_CR_BIT_ERROR_RECOVERY_RANGE_SYSADDR_MCMAIN_STRUCT;

typedef union {
  struct {
    UINT32 GFXVTBAREN                              :  1;  // Bits 0:0
    UINT32                                         :  11;  // Bits 11:1
    UINT32 GFXVTBARLow                             :  20;  // Bits 31:12
    UINT32 GFXVTBARHigh                            :  7;  // Bits 38:32
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} NCDECS_CR_GFXVTBAR_NCU_STRUCT;

typedef union {
  struct {
    UINT32 EDRAMBAREN                              :  1;  // Bits 0:0
    UINT32                                         :  13;  // Bits 13:1
    UINT32 EDRAMBARLow                             :  18;  // Bits 31:14
    UINT32 EDRAMBARHigh                            :  7;  // Bits 38:32
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} NCDECS_CR_EDRAMBAR_NCU_STRUCT;

typedef union {
  struct {
    UINT32 VTVC0BAREN                              :  1;  // Bits 0:0
    UINT32                                         :  11;  // Bits 11:1
    UINT32 VTVC0BARLow                             :  20;  // Bits 31:12
    UINT32 VTVC0BARHigh                            :  7;  // Bits 38:32
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} NCDECS_CR_VTDPVC0BAR_NCU_STRUCT;

typedef union {
  struct {
    UINT32 RdrModSel                               :  3;  // Bits 2:0
    UINT32 ClastChkSmpMod                          :  1;  // Bits 3:3
    UINT32 LogFltClustMod                          :  1;  // Bits 4:4
    UINT32 LogFlatClustOvrEn                       :  1;  // Bits 5:5
    UINT32 HashModCtr                              :  3;  // Bits 8:6
    UINT32                                         :  23;  // Bits 31:9
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} NCDECS_CR_INTRDIRCTL_NCU_STRUCT;

typedef union {
  struct {
    UINT32                                         :  28;  // Bits 27:0
    UINT32 PLIM                                    :  3;  // Bits 30:28
    UINT32                                         :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} NCDECS_CR_NCUCTL0_NCU_STRUCT;

typedef union {
  struct {
    UINT32 GDXCBAREN                               :  1;  // Bits 0:0
    UINT32                                         :  11;  // Bits 11:1
    UINT32 GDXCBARLow                              :  20;  // Bits 31:12
    UINT32 GDXCBARHigh                             :  7;  // Bits 38:32
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} NCDECS_CR_GDXCBAR_NCU_STRUCT;

typedef union {
  struct {
    UINT32 Data                                    :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} NCDECS_CR_SCRATCHPAD_NCU_0_STRUCT;

typedef union {
  struct {
    UINT32 Data                                    :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} NCDECS_CR_SCRATCHPAD_NCU_1_STRUCT;

typedef union {
  struct {
    UINT32 Data                                    :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} NCDECS_CR_SCRATCHPAD_NCU_2_STRUCT;

typedef union {
  struct {
    UINT32 Data                                    :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} NCDECS_CR_SCRATCHPAD_NCU_3_STRUCT;

typedef union {
  struct {
    UINT32 LOCK                                    :  1;  // Bits 0:0
    UINT32                                         :  19;  // Bits 19:1
    UINT32 OFFSET                                  :  12;  // Bits 31:20
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} NCDECS_CR_PAVPMSGOFFST_NCU_STRUCT;

typedef union {
  struct {
    UINT32 DATA                                    :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} PCU_CR_CAMARILLO_MAILBOX_DATA0_PCU_STRUCT;

typedef union {
  struct {
    UINT32 DATA                                    :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} PCU_CR_CAMARILLO_MAILBOX_DATA1_PCU_STRUCT;

typedef union {
  struct {
    UINT32 COMMAND                                 :  8;  // Bits 7:0
    UINT32 ADDR_CNTL                               :  21;  // Bits 28:8
    UINT32                                         :  2;  // Bits 30:29
    UINT32 RUN_BUSY                                :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} PCU_CR_CAMARILLO_MAILBOX_INTERFACE_PCU_STRUCT;

typedef union {
  struct {
    UINT32 HIGH_TEMP_INT_ENABLE                    :  1;  // Bits 0:0
    UINT32 LOW_TEMP_INT_ENABLE                     :  1;  // Bits 1:1
    UINT32 PROCHOT_INT_ENABLE                      :  1;  // Bits 2:2
    UINT32                                         :  1;  // Bits 3:3
    UINT32 OUT_OF_SPEC_INT_ENABLE                  :  1;  // Bits 4:4
    UINT32                                         :  3;  // Bits 7:5
    UINT32 THRESHOLD_1_REL_TEMP                    :  7;  // Bits 14:8
    UINT32 THRESHOLD_1_INT_ENABLE                  :  1;  // Bits 15:15
    UINT32 THRESHOLD_2_REL_TEMP                    :  7;  // Bits 22:16
    UINT32 THRESHOLD_2_INT_ENABLE                  :  1;  // Bits 23:23
    UINT32 POWER_INT_ENABLE                        :  1;  // Bits 24:24
    UINT32                                         :  7;  // Bits 31:25
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} PCU_CR_PACKAGE_THERM_CAMARILLO_INTERRUPT_PCU_STRUCT;

typedef union {
  struct {
    UINT32 DATALow                                 :  32;  // Bits 31:0
    UINT32 DATAHigh                                :  32;  // Bits 63:32
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} PCU_CR_PKG_IA_C0_ANY_SUM_PCU_STRUCT;

typedef union {
  struct {
    UINT32 DATALow                                 :  32;  // Bits 31:0
    UINT32 DATAHigh                                :  32;  // Bits 63:32
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} PCU_CR_PKG_IA_C0_ANY_PCU_STRUCT;

typedef union {
  struct {
    UINT32 DATALow                                 :  32;  // Bits 31:0
    UINT32 DATAHigh                                :  32;  // Bits 63:32
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} PCU_CR_PKG_GT_C0_ANY_PCU_STRUCT;

typedef union {
  struct {
    UINT32 DATALow                                 :  32;  // Bits 31:0
    UINT32 DATAHigh                                :  32;  // Bits 63:32
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} PCU_CR_PKG_GT_AND_IA_OVERLAP_PCU_STRUCT;

typedef union {
  struct {
    UINT32 OLTM_ENABLE                             :  1;  // Bits 0:0
    UINT32 CLTM_ENABLE                             :  1;  // Bits 1:1
    UINT32 REFRESH_2X_MODE                         :  2;  // Bits 3:2
    UINT32 EXTTS_ENABLE                            :  1;  // Bits 4:4
    UINT32 LOCK_PTM_REGS_PCU                       :  1;  // Bits 5:5
    UINT32 PDWN_CONFIG_CTL                         :  1;  // Bits 6:6
    UINT32 DISABLE_DRAM_TS                         :  1;  // Bits 7:7
    UINT32 DDR4_SKIP_REFRESH_EN                    :  1;  // Bits 8:8
    UINT32                                         :  23;  // Bits 31:9
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} PCU_CR_DDR_PTM_CTL_PCU_STRUCT;

typedef union {
  struct {
    UINT32 SCALEFACTOR                             :  3;  // Bits 2:0
    UINT32                                         :  29;  // Bits 31:3
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} PCU_CR_DDR_ENERGY_SCALEFACTOR_PCU_STRUCT;

typedef union {
  struct {
    UINT32 CH0                                     :  8;  // Bits 7:0
    UINT32 CH1                                     :  8;  // Bits 15:8
    UINT32                                         :  16;  // Bits 31:16
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} PCU_CR_DDR_RAPL_CHANNEL_POWER_FLOOR_PCU_STRUCT;

typedef union {
  struct {
    UINT32 CH0_DIMM0                               :  2;  // Bits 1:0
    UINT32 CH0_DIMM1                               :  2;  // Bits 3:2
    UINT32                                         :  4;  // Bits 7:4
    UINT32 CH1_DIMM0                               :  2;  // Bits 9:8
    UINT32 CH1_DIMM1                               :  2;  // Bits 11:10
    UINT32                                         :  20;  // Bits 31:12
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} PCU_CR_DDR_THERM_PERDIMM_STATUS_PCU_STRUCT;

typedef union {
  struct {
    UINT32 DIMM0                                   :  8;  // Bits 7:0
    UINT32 DIMM1                                   :  8;  // Bits 15:8
    UINT32                                         :  16;  // Bits 31:16
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} PCU_CR_DDR_WARM_THRESHOLD_CH0_PCU_STRUCT;

typedef union {
  struct {
    UINT32 DIMM0                                   :  8;  // Bits 7:0
    UINT32 DIMM1                                   :  8;  // Bits 15:8
    UINT32                                         :  16;  // Bits 31:16
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} PCU_CR_DDR_WARM_THRESHOLD_CH1_PCU_STRUCT;

typedef union {
  struct {
    UINT32 DIMM0                                   :  8;  // Bits 7:0
    UINT32 DIMM1                                   :  8;  // Bits 15:8
    UINT32                                         :  16;  // Bits 31:16
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} PCU_CR_DDR_HOT_THRESHOLD_CH0_PCU_STRUCT;

typedef union {
  struct {
    UINT32 DIMM0                                   :  8;  // Bits 7:0
    UINT32 DIMM1                                   :  8;  // Bits 15:8
    UINT32                                         :  16;  // Bits 31:16
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} PCU_CR_DDR_HOT_THRESHOLD_CH1_PCU_STRUCT;

typedef union {
  struct {
    UINT32 ENABLE_WARM_INTERRUPT                   :  1;  // Bits 0:0
    UINT32                                         :  1;  // Bits 1:1
    UINT32 ENABLE_HOT_INTERRUPT                    :  1;  // Bits 2:2
    UINT32                                         :  1;  // Bits 3:3
    UINT32 ENABLE_2X_REFRESH_INTERRUPT             :  1;  // Bits 4:4
    UINT32                                         :  1;  // Bits 5:5
    UINT32 ENABLE_OOS_TEMP_INTERRUPT               :  1;  // Bits 6:6
    UINT32                                         :  1;  // Bits 7:7
    UINT32 ENABLE_THRESHOLD1_INTERRUPT             :  1;  // Bits 8:8
    UINT32                                         :  1;  // Bits 9:9
    UINT32 ENABLE_THRESHOLD2_INTERRUPT             :  1;  // Bits 10:10
    UINT32                                         :  5;  // Bits 15:11
    UINT32 POLICY_FREE_THRESHOLD1                  :  8;  // Bits 23:16
    UINT32 POLICY_FREE_THRESHOLD2                  :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} PCU_CR_DDR_THERM_CAMARILLO_INTERRUPT_PCU_STRUCT;

typedef union {
  struct {
    UINT32 DDR_VOLTAGE                             :  3;  // Bits 2:0
    UINT32                                         :  29;  // Bits 31:3
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} PCU_CR_DDR_VOLTAGE_PCU_STRUCT;

typedef union {
  struct {
    INT32  THERM_MARGIN                            :  16;  // Bits 15:0
    UINT32                                         :  16;  // Bits 31:16
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} PCU_CR_PACKAGE_THERM_MARGIN_PCU_STRUCT;

typedef union {
  struct {
    UINT32 DIMM0                                   :  8;  // Bits 7:0
    UINT32 DIMM1                                   :  8;  // Bits 15:8
    UINT32                                         :  16;  // Bits 31:16
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} PCU_CR_DDR_DIMM_TEMPERATURE_CH0_PCU_STRUCT;

typedef union {
  struct {
    UINT32 DIMM0                                   :  8;  // Bits 7:0
    UINT32 DIMM1                                   :  8;  // Bits 15:8
    UINT32                                         :  16;  // Bits 31:16
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} PCU_CR_DDR_DIMM_TEMPERATURE_CH1_PCU_STRUCT;

typedef union {
  struct {
    UINT32 TEMPERATURE                             :  8;  // Bits 7:0
    UINT32                                         :  24;  // Bits 31:8
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} PCU_CR_DDR_DIMM_HOTTEST_ABSOLUTE_PCU_STRUCT;

typedef union {
  struct {
    UINT32 TEMPERATURE                             :  8;  // Bits 7:0
    UINT32                                         :  24;  // Bits 31:8
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} PCU_CR_DDR_DIMM_HOTTEST_RELATIVE_PCU_STRUCT;

typedef union {
  struct {
    UINT32 DIMM0                                   :  16;  // Bits 15:0
    UINT32 DIMM1                                   :  16;  // Bits 31:16
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} PCU_CR_DDR_THROTTLE_DURATION_CH0_PCU_STRUCT;

typedef union {
  struct {
    UINT32 DIMM0                                   :  16;  // Bits 15:0
    UINT32 DIMM1                                   :  16;  // Bits 31:16
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} PCU_CR_DDR_THROTTLE_DURATION_CH1_PCU_STRUCT;

typedef union {
  struct {
    UINT32 DIMM0                                   :  8;  // Bits 7:0
    UINT32 DIMM1                                   :  8;  // Bits 15:8
    UINT32                                         :  16;  // Bits 31:16
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} PCU_CR_DDR_WARM_BUDGET_CH0_PCU_STRUCT;

typedef union {
  struct {
    UINT32 DIMM0                                   :  8;  // Bits 7:0
    UINT32 DIMM1                                   :  8;  // Bits 15:8
    UINT32                                         :  16;  // Bits 31:16
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} PCU_CR_DDR_WARM_BUDGET_CH1_PCU_STRUCT;

typedef union {
  struct {
    UINT32 DIMM0                                   :  8;  // Bits 7:0
    UINT32 DIMM1                                   :  8;  // Bits 15:8
    UINT32                                         :  16;  // Bits 31:16
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} PCU_CR_DDR_HOT_BUDGET_CH0_PCU_STRUCT;

typedef union {
  struct {
    UINT32 DIMM0                                   :  8;  // Bits 7:0
    UINT32 DIMM1                                   :  8;  // Bits 15:8
    UINT32                                         :  16;  // Bits 31:16
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} PCU_CR_DDR_HOT_BUDGET_CH1_PCU_STRUCT;

typedef union {
  struct {
    UINT32 LIMIT1_POWER                            :  15;  // Bits 14:0
    UINT32 LIMIT1_ENABLE                           :  1;  // Bits 15:15
    UINT32                                         :  1;  // Bits 16:16
    UINT32 LIMIT1_TIME_WINDOW_Y                    :  5;  // Bits 21:17
    UINT32 LIMIT1_TIME_WINDOW_X                    :  2;  // Bits 23:22
    UINT32                                         :  8;  // Bits 31:24
    UINT32 LIMIT2_POWER                            :  15;  // Bits 46:32
    UINT32 LIMIT2_ENABLE                           :  1;  // Bits 47:47
    UINT32                                         :  1;  // Bits 48:48
    UINT32 LIMIT2_TIME_WINDOW_Y                    :  5;  // Bits 53:49
    UINT32 LIMIT2_TIME_WINDOW_X                    :  2;  // Bits 55:54
    UINT32                                         :  7;  // Bits 62:56
    UINT32 LOCKED                                  :  1;  // Bits 63:63
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} PCU_CR_DDR_RAPL_LIMIT_PCU_STRUCT;

typedef union {
  struct {
    UINT32 JOULES_CONSUMED                         :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} PCU_CR_DDR_ENERGY_STATUS_PCU_STRUCT;

typedef union {
  struct {
    UINT32 DURATION                                :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} PCU_CR_DDR_RAPL_PERF_STATUS_PCU_STRUCT;

typedef union {
  struct {
    UINT32 COUNTS                                  :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} PCU_CR_PACKAGE_RAPL_PERF_STATUS_PCU_STRUCT;

typedef union {
  struct {
    UINT32 DDR_ACCESS_TIME                         :  14;  // Bits 13:0
    UINT32 RESERVED                                :  1;  // Bits 14:14
    UINT32 CLR_ACCESS_TIME                         :  14;  // Bits 28:15
    UINT32 NON_SNOOP_THRESHOLD_RESOLUTION          :  1;  // Bits 29:29
    UINT32 SLOW_SNOOP_THRESHOLD_RESOLUTION         :  1;  // Bits 30:30
    UINT32 FAST_SNOOP_THRESHOLD_RESOLUTION         :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} PCU_CR_PKGC_LTR_LATENCY_MEASUREMENTS_PCU_STRUCT;

typedef union {
  struct {
    UINT32 PROCHOT_STATUS                          :  1;  // Bits 0:0
    UINT32 THERMAL_STATUS                          :  1;  // Bits 1:1
    UINT32 SPARE_IA_2                              :  1;  // Bits 2:2
    UINT32 RAPL_PL1_STATUS                         :  1;  // Bits 3:3
    UINT32 RAPL_PL2_STATUS                         :  1;  // Bits 4:4
    UINT32 RAPL_PL3_STATUS                         :  1;  // Bits 5:5
    UINT32 EE_STATUS                               :  1;  // Bits 6:6
    UINT32 GT_DRIVER_STATUS                        :  1;  // Bits 7:7
    UINT32 PKG_VR_THERM_ALERT_STATUS               :  1;  // Bits 8:8
    UINT32 FUSE_MAX_TURBO_LIMIT_STATUS             :  1;  // Bits 9:9
    UINT32 EPD_ICCMAX_STATUS                       :  1;  // Bits 10:10
    UINT32 TURBO_TRANSITION_STATUS_STATUS          :  1;  // Bits 11:11
    UINT32 SA_VR_THERM_ALERT_STATUS                :  1;  // Bits 12:12
    UINT32 SPARE_IA_13                             :  1;  // Bits 13:13
    UINT32 SPARE_IA_14                             :  1;  // Bits 14:14
    UINT32 SPARE_IA_15                             :  1;  // Bits 15:15
    UINT32 PROCHOT_LOG                             :  1;  // Bits 16:16
    UINT32 THERMAL_LOG                             :  1;  // Bits 17:17
    UINT32 SPARE_IA_LOG_2                          :  1;  // Bits 18:18
    UINT32 RAPL_PL1_LOG                            :  1;  // Bits 19:19
    UINT32 RAPL_PL2_LOG                            :  1;  // Bits 20:20
    UINT32 RAPL_PL3_LOG                            :  1;  // Bits 21:21
    UINT32 EE_LOG                                  :  1;  // Bits 22:22
    UINT32 GT_DRIVER_LOG                           :  1;  // Bits 23:23
    UINT32 PKG_VR_THERM_ALERT_LOG                  :  1;  // Bits 24:24
    UINT32 FUSE_MAX_TURBO_LIMIT_LOG                :  1;  // Bits 25:25
    UINT32 EDP_ICCMAX_LOG                          :  1;  // Bits 26:26
    UINT32 TURBO_TRANSITION_LOG                    :  1;  // Bits 27:27
    UINT32 SA_VR_THERM_ALERT_LOG                   :  1;  // Bits 28:28
    UINT32 SPARE_IA_LOG_13                         :  1;  // Bits 29:29
    UINT32 SPARE_IA_LOG_14                         :  1;  // Bits 30:30
    UINT32 SPARE_IA_LOG_15                         :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} PCU_CR_IA_PERF_LIMIT_REASONS_PCU_STRUCT;

typedef union {
  struct {
    UINT32 PROCHOT_STATUS                          :  1;  // Bits 0:0
    UINT32 THERMAL_STATUS                          :  1;  // Bits 1:1
    UINT32 SPARE_GT_2                              :  1;  // Bits 2:2
    UINT32 RAPL_PL1_STATUS                         :  1;  // Bits 3:3
    UINT32 RAPL_PL2_STATUS                         :  1;  // Bits 4:4
    UINT32 RAPL_PL3_STATUS                         :  1;  // Bits 5:5
    UINT32 SPARE_GT_6                              :  1;  // Bits 6:6
    UINT32 SPARE_GT_7                              :  1;  // Bits 7:7
    UINT32 PKG_VR_THERM_ALERT                      :  1;  // Bits 8:8
    UINT32 SA_VR_THERM_ALERT_STATUS                :  1;  // Bits 9:9
    UINT32 EDP_ICC_STATUS                          :  1;  // Bits 10:10
    UINT32 SPARE_GT_11                             :  1;  // Bits 11:11
    UINT32 SPARE_GT_12                             :  1;  // Bits 12:12
    UINT32 SPARE_GT_13                             :  1;  // Bits 13:13
    UINT32 SPARE_GT_14                             :  1;  // Bits 14:14
    UINT32 SPARE_GT_15                             :  1;  // Bits 15:15
    UINT32 PROCHOT_LOG                             :  1;  // Bits 16:16
    UINT32 THERMAL_LOG                             :  1;  // Bits 17:17
    UINT32 SPARE_GT_LOG_2                          :  1;  // Bits 18:18
    UINT32 RAPL_PL1_LOG                            :  1;  // Bits 19:19
    UINT32 RAPL_PL2_LOG                            :  1;  // Bits 20:20
    UINT32 RAPL_PL3_LOG                            :  1;  // Bits 21:21
    UINT32 SPARE_GT_LOG_6                          :  1;  // Bits 22:22
    UINT32 SPARE_GT_LOG_7                          :  1;  // Bits 23:23
    UINT32 PKG_VR_THEM_ALERT_LOG                   :  1;  // Bits 24:24
    UINT32 SA_VR_THERM_ALERT_LOG                   :  1;  // Bits 25:25
    UINT32 EDP_ICC_LOG                             :  1;  // Bits 26:26
    UINT32 SPARE_GT_LOG_11                         :  1;  // Bits 27:27
    UINT32 SPARE_GT_LOG_12                         :  1;  // Bits 28:28
    UINT32 SPARE_GT_LOG_13                         :  1;  // Bits 29:29
    UINT32 SPARE_GT_LOG_14                         :  1;  // Bits 30:30
    UINT32 SPARE_GT_LOG_15                         :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} PCU_CR_GT_PERF_LIMIT_REASONS_PCU_STRUCT;

typedef union {
  struct {
    UINT32 SPARE_CLR_0                             :  1;  // Bits 0:0
    UINT32 SPARE_CLR_1                             :  1;  // Bits 1:1
    UINT32 SPARE_CLR_2                             :  1;  // Bits 2:2
    UINT32 SPARE_CLR_3                             :  1;  // Bits 3:3
    UINT32 SPARE_CLR_4                             :  1;  // Bits 4:4
    UINT32 SPARE_CLR_5                             :  1;  // Bits 5:5
    UINT32 SPARE_CLR_6                             :  1;  // Bits 6:6
    UINT32 SPARE_CLR_7                             :  1;  // Bits 7:7
    UINT32 SPARE_CLR_8                             :  1;  // Bits 8:8
    UINT32 SPARE_CLR_9                             :  1;  // Bits 9:9
    UINT32 EDP_ICC_STATUS                          :  1;  // Bits 10:10
    UINT32 SPARE_CLR_11                            :  1;  // Bits 11:11
    UINT32 SPARE_CLR_12                            :  1;  // Bits 12:12
    UINT32 SPARE_CLR_13                            :  1;  // Bits 13:13
    UINT32 SPARE_CLR_14                            :  1;  // Bits 14:14
    UINT32 SPARE_CLR_15                            :  1;  // Bits 15:15
    UINT32 SPARE_CLR_LOG_0                         :  1;  // Bits 16:16
    UINT32 SPARE_CLR_LOG_1                         :  1;  // Bits 17:17
    UINT32 SPARE_CLR_LOG_2                         :  1;  // Bits 18:18
    UINT32 SPARE_CLR_LOG_3                         :  1;  // Bits 19:19
    UINT32 SPARE_CLR_LOG_4                         :  1;  // Bits 20:20
    UINT32 SPARE_CLR_LOG_5                         :  1;  // Bits 21:21
    UINT32 SPARE_CLR_LOG_6                         :  1;  // Bits 22:22
    UINT32 SPARE_CLR_LOG_7                         :  1;  // Bits 23:23
    UINT32 SPARE_CLR_LOG_8                         :  1;  // Bits 24:24
    UINT32 SPARE_CLR_LOG_9                         :  1;  // Bits 25:25
    UINT32 EDP_ICC_LOG                             :  1;  // Bits 26:26
    UINT32 SPARE_CLR_LOG_11                        :  1;  // Bits 27:27
    UINT32 SPARE_CLR_LOG_12                        :  1;  // Bits 28:28
    UINT32 SPARE_CLR_LOG_13                        :  1;  // Bits 29:29
    UINT32 SPARE_CLR_LOG_14                        :  1;  // Bits 30:30
    UINT32 SPARE_CLR_LOG_15                        :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} PCU_CR_CLR_PERF_LIMIT_REASONS_PCU_STRUCT;

typedef union {
  struct {
    UINT32 PRIPTP                                  :  5;  // Bits 4:0
    UINT32                                         :  27;  // Bits 31:5
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} PCU_CR_PRIP_TURBO_PLCY_PCU_STRUCT;

typedef union {
  struct {
    UINT32 SECPTP                                  :  5;  // Bits 4:0
    UINT32                                         :  27;  // Bits 31:5
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} PCU_CR_SECP_TURBO_PLCY_PCU_STRUCT;

typedef union {
  struct {
    UINT32 DATA                                    :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} PCU_CR_PRIP_NRG_STTS_PCU_STRUCT;

typedef union {
  struct {
    UINT32 DATA                                    :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} PCU_CR_SECP_NRG_STTS_PCU_STRUCT;

typedef union {
  struct {
    UINT32 PKG_TDP                                 :  15;  // Bits 14:0
    UINT32                                         :  1;  // Bits 15:15
    UINT32 PKG_MIN_PWR                             :  15;  // Bits 30:16
    UINT32                                         :  1;  // Bits 31:31
    UINT32 PKG_MAX_PWR                             :  15;  // Bits 46:32
    UINT32                                         :  1;  // Bits 47:47
    UINT32 PKG_MAX_WIN                             :  7;  // Bits 54:48
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} PCU_CR_PACKAGE_POWER_SKU_PCU_STRUCT;

typedef union {
  struct {
    UINT32 PWR_UNIT                                :  4;  // Bits 3:0
    UINT32                                         :  4;  // Bits 7:4
    UINT32 ENERGY_UNIT                             :  5;  // Bits 12:8
    UINT32                                         :  3;  // Bits 15:13
    UINT32 TIME_UNIT                               :  4;  // Bits 19:16
    UINT32                                         :  12;  // Bits 31:20
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} PCU_CR_PACKAGE_POWER_SKU_UNIT_PCU_STRUCT;

typedef union {
  struct {
    UINT32 DATA                                    :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} PCU_CR_PACKAGE_ENERGY_STATUS_PCU_STRUCT;

typedef union {
  struct {
    UINT32 DATA                                    :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} PCU_CR_GT_IO_BUSYNESS_PCU_STRUCT;

typedef union {
  struct {
    UINT32 DATA                                    :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} PCU_CR_GT_VIDEO_BUSYNESS_PCU_STRUCT;

typedef union {
  struct {
    UINT32 RP_STATE_VOLTAGE                        :  8;  // Bits 7:0
    UINT32 RP_STATE_RATIO_UNSLICE                  :  9;  // Bits 16:8
    UINT32 RP_STATE_RATIO_SLICE                    :  9;  // Bits 25:17
    UINT32                                         :  6;  // Bits 31:26
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} PCU_CR_GT_PERF_STATUS_PCU_STRUCT;

typedef union {
  struct {
    UINT32 QCLK_RATIO                              :  7;  // Bits 6:0
    UINT32 QCLK_REFERENCE                          :  1;  // Bits 7:7
    UINT32 FCLK_RATIO                              :  8;  // Bits 15:8
    UINT32 ICLK_RATIO                              :  8;  // Bits 23:16
    UINT32 UCLK_RATIO                              :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} PCU_CR_SA_PERF_STATUS_PCU_STRUCT;

typedef union {
  struct {
    UINT32                                         : 32;  // Bits 49:0
    UINT32                                         :  18;  // Bits 49:0
    UINT32 PLATFORMID                              :  3;  // Bits 52:50
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} PCU_CR_PLATFORM_ID_PCU_STRUCT;

typedef union {
  struct {
    UINT32                                         :  8;  // Bits 7:0
    UINT32 MAX_NON_TURBO_LIM_RATIO                 :  8;  // Bits 15:8
    UINT32 SMM_SAVE_CAP                            :  1;  // Bits 16:16
    UINT32                                         :  7;  // Bits 23:17
    UINT32 OCVOLT_OVRD_AVAIL                       :  1;  // Bits 24:24
    UINT32                                         :  1;  // Bits 25:25
    UINT32 DCU_16K_MODE_AVAIL                      :  1;  // Bits 26:26
    UINT32 SAMPLE_PART                             :  1;  // Bits 27:27
    UINT32 PRG_TURBO_RATIO_EN                      :  1;  // Bits 28:28
    UINT32 PRG_TDP_LIM_EN                          :  1;  // Bits 29:29
    UINT32 PRG_TJ_OFFSET_EN                        :  1;  // Bits 30:30
    UINT32 CPUID_FAULTING_EN                       :  1;  // Bits 31:31
    UINT32 LPM_SUPPORT                             :  1;  // Bits 32:32
    UINT32 CONFIG_TDP_LEVELS                       :  2;  // Bits 34:33
    UINT32 PFAT_ENABLE                             :  1;  // Bits 35:35
    UINT32 PEG2DMIDIS_EN                           :  1;  // Bits 36:36
    UINT32 TIMED_MWAIT_ENABLE                      :  1;  // Bits 37:37
    UINT32                                         :  2;  // Bits 39:38
    UINT32 MAX_EFFICIENCY_RATIO                    :  8;  // Bits 47:40
    UINT32 MIN_OPERATING_RATIO                     :  8;  // Bits 55:48
    UINT32 PushPatch_EN                            :  1;  // Bits 56:56
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} PCU_CR_PLATFORM_INFO_PCU_STRUCT;

typedef union {
  struct {
    UINT32 DATA                                    :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} PCU_CR_PP1_C0_CORE_CLOCK_PCU_STRUCT;

typedef union {
  struct {
    UINT32 DATA                                    :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} PCU_CR_PP0_EFFICIENT_CYCLES_PCU_STRUCT;

typedef union {
  struct {
    UINT32 DATA                                    :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} PCU_CR_PP0_THREAD_ACTIVITY_PCU_STRUCT;

typedef union {
  struct {
    UINT32 DATA                                    :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} PCU_CR_PP1_EFFICIENT_CYCLES_PCU_STRUCT;

typedef union {
  struct {
    UINT32 DATA                                    :  8;  // Bits 7:0
    UINT32                                         :  24;  // Bits 31:8
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} PCU_CR_PACKAGE_TEMPERATURE_PCU_STRUCT;

typedef union {
  struct {
    UINT32 DATA                                    :  8;  // Bits 7:0
    UINT32                                         :  24;  // Bits 31:8
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} PCU_CR_PP0_TEMPERATURE_PCU_STRUCT;

typedef union {
  struct {
    UINT32 DATA                                    :  8;  // Bits 7:0
    UINT32                                         :  24;  // Bits 31:8
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} PCU_CR_PP1_TEMPERATURE_PCU_STRUCT;

typedef union {
  struct {
    UINT32 TIME_VAL                                :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} PCU_CR_PCU_REFERENCE_CLOCK_PCU_STRUCT;

typedef union {
  struct {
    UINT32 RESERVED                                :  1;  // Bits 0:0
    UINT32 VALID                                   :  1;  // Bits 1:1
    UINT32 RESERVED_BITS                           :  4;  // Bits 5:2
    UINT32 OD                                      :  1;  // Bits 6:6
    UINT32 IM                                      :  1;  // Bits 7:7
    UINT32 NEXT_DEVICE_ACTIVITY                    :  21;  // Bits 28:8
    UINT32                                         :  3;  // Bits 31:29
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} PCU_CR_DEVICE_SHARED_IDLE_DURATION_PCU_STRUCT;

typedef union {
  struct {
    UINT32 USED                                    :  1;  // Bits 0:0
    UINT32 VALID                                   :  1;  // Bits 1:1
    UINT32 RESERVED_BITS                           :  4;  // Bits 5:2
    UINT32 OD                                      :  1;  // Bits 6:6
    UINT32 IM                                      :  1;  // Bits 7:7
    UINT32 NEXT_DEVICE_ACTIVITY                    :  21;  // Bits 28:8
    UINT32                                         :  3;  // Bits 31:29
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} PCU_CR_DEVICE_DEDICATED_IDLE_DURATION_PCU_STRUCT;

typedef union {
  struct {
    UINT32 RPSTT_LIM                               :  8;  // Bits 7:0
    UINT32                                         :  24;  // Bits 31:8
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} PCU_CR_RP_STATE_LIMITS_PCU_STRUCT;

typedef union {
  struct {
    UINT32 RP0_CAP                                 :  8;  // Bits 7:0
    UINT32 RP1_CAP                                 :  8;  // Bits 15:8
    UINT32 RPN_CAP                                 :  8;  // Bits 23:16
    UINT32                                         :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} PCU_CR_RP_STATE_CAP_PCU_STRUCT;

typedef union {
  struct {
    UINT32 TCC_OFFSET_TIME_WINDOW                  :  7;  // Bits 6:0
    UINT32 TCC_OFFSET_CLAMPING_BIT                 :  1;  // Bits 7:7
    UINT32 FAN_TEMP_TARGET_OFST                    :  8;  // Bits 15:8
    UINT32 REF_TEMP                                :  8;  // Bits 23:16
    UINT32 TJ_MAX_TCC_OFFSET                       :  6;  // Bits 29:24
    UINT32                                         :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} PCU_CR_TEMPERATURE_TARGET_PCU_STRUCT;

typedef union {
  struct {
    UINT32 PKG_PWR_LIM_1                           :  15;  // Bits 14:0
    UINT32 PKG_PWR_LIM_1_EN                        :  1;  // Bits 15:15
    UINT32 PKG_CLMP_LIM_1                          :  1;  // Bits 16:16
    UINT32 PKG_PWR_LIM_1_TIME                      :  7;  // Bits 23:17
    UINT32                                         :  8;  // Bits 31:24
    UINT32 PKG_PWR_LIM_2                           :  15;  // Bits 46:32
    UINT32 PKG_PWR_LIM_2_EN                        :  1;  // Bits 47:47
    UINT32 PKG_CLMP_LIM_2                          :  1;  // Bits 48:48
    UINT32 PKG_PWR_LIM_2_TIME                      :  7;  // Bits 55:49
    UINT32                                         :  7;  // Bits 62:56
    UINT32 PKG_PWR_LIM_LOCK                        :  1;  // Bits 63:63
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} PCU_CR_PACKAGE_RAPL_LIMIT_PCU_STRUCT;

typedef union {
  struct {
    UINT32 IA_PP_PWR_LIM                           :  15;  // Bits 14:0
    UINT32 PWR_LIM_CTRL_EN                         :  1;  // Bits 15:15
    UINT32 PP_CLAMP_LIM                            :  1;  // Bits 16:16
    UINT32 CTRL_TIME_WIN                           :  7;  // Bits 23:17
    UINT32                                         :  7;  // Bits 30:24
    UINT32 PP_PWR_LIM_LOCK                         :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} PCU_CR_PRIP_TURBO_PWR_LIM_PCU_STRUCT;

typedef union {
  struct {
    UINT32 NON_IA_PP_PWR_LIM                       :  15;  // Bits 14:0
    UINT32 PWR_LIM_CTRL_EN                         :  1;  // Bits 15:15
    UINT32 PP_CLAMP_LIM                            :  1;  // Bits 16:16
    UINT32 CTRL_TIME_WIN                           :  7;  // Bits 23:17
    UINT32                                         :  7;  // Bits 30:24
    UINT32 SP_PWR_LIM_LOCK                         :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} PCU_CR_SECP_TURBO_PWR_LIM_PCU_STRUCT;

typedef union {
  struct {
    UINT32 CURRENT_LIMIT                           :  13;  // Bits 12:0
    UINT32                                         :  18;  // Bits 30:13
    UINT32 LOCK                                    :  1;  // Bits 31:31
    UINT32 PSI1_THRESHOLD                          :  10;  // Bits 41:32
    UINT32 PSI2_THRESHOLD                          :  10;  // Bits 51:42
    UINT32 PSI3_THRESHOLD                          :  10;  // Bits 61:52
    UINT32 PS4_ENABLE                              :  1;  // Bits 62:62
    UINT32 RESERVED                                :  1;  // Bits 63:63
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} PCU_CR_VR_CURRENT_CONFIG_PCU_STRUCT;

typedef union {
  struct {
    UINT32 MRC_Saving_Rd                           :  8;  // Bits 7:0
    UINT32 MRC_Saving_Wt                           :  8;  // Bits 15:8
    UINT32 MRC_Saving_Cmd                          :  8;  // Bits 23:16
    UINT32 RESERVED                                :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} PCU_CR_MRC_ODT_POWER_SAVING_PCU_STRUCT;

typedef union {
  struct {
    UINT32 THERMAL_MONITOR_STATUS                  :  1;  // Bits 0:0
    UINT32 THERMAL_MONITOR_LOG                     :  1;  // Bits 1:1
    UINT32 PROCHOT_STATUS                          :  1;  // Bits 2:2
    UINT32 PROCHOT_LOG                             :  1;  // Bits 3:3
    UINT32 OUT_OF_SPEC_STATUS                      :  1;  // Bits 4:4
    UINT32 OUT_OF_SPEC_LOG                         :  1;  // Bits 5:5
    UINT32 THRESHOLD1_STATUS                       :  1;  // Bits 6:6
    UINT32 THRESHOLD1_LOG                          :  1;  // Bits 7:7
    UINT32 THRESHOLD2_STATUS                       :  1;  // Bits 8:8
    UINT32 THRESHOLD2_LOG                          :  1;  // Bits 9:9
    UINT32 POWER_LIMITATION_STATUS                 :  1;  // Bits 10:10
    UINT32 POWER_LIMITATION_LOG                    :  1;  // Bits 11:11
    UINT32 CURRENT_LIMIT_STATUS                    :  1;  // Bits 12:12
    UINT32 CURRENT_LIMIT_LOG                       :  1;  // Bits 13:13
    UINT32 CROSS_DOMAIN_LIMIT_STATUS               :  1;  // Bits 14:14
    UINT32 CROSS_DOMAIN_LIMIT_LOG                  :  1;  // Bits 15:15
    UINT32 TEMPERATURE                             :  7;  // Bits 22:16
    UINT32                                         :  4;  // Bits 26:23
    UINT32 RESOLUTION                              :  4;  // Bits 30:27
    UINT32 VALID                                   :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} PCU_CR_THERM_STATUS_GT_PCU_STRUCT;

typedef union {
  struct {
    UINT32 HIGH_TEMP_INT_ENABLE                    :  1;  // Bits 0:0
    UINT32 LOW_TEMP_INT_ENABLE                     :  1;  // Bits 1:1
    UINT32 PROCHOT_INT_ENABLE                      :  1;  // Bits 2:2
    UINT32                                         :  1;  // Bits 3:3
    UINT32 OUT_OF_SPEC_INT_ENABLE                  :  1;  // Bits 4:4
    UINT32                                         :  3;  // Bits 7:5
    UINT32 THRESHOLD_1_REL_TEMP                    :  7;  // Bits 14:8
    UINT32 THRESHOLD_1_INT_ENABLE                  :  1;  // Bits 15:15
    UINT32 THRESHOLD_2_REL_TEMP                    :  7;  // Bits 22:16
    UINT32 THRESHOLD_2_INT_ENABLE                  :  1;  // Bits 23:23
    UINT32 POWER_INT_ENABLE                        :  1;  // Bits 24:24
    UINT32                                         :  7;  // Bits 31:25
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} PCU_CR_THERM_INTERRUPT_GT_PCU_STRUCT;

typedef union {
  struct {
    UINT32 RESERVED                                :  1;  // Bits 0:0
    UINT32 VALID                                   :  1;  // Bits 1:1
    UINT32 RESERVED_BITS                           :  4;  // Bits 5:2
    UINT32 OD                                      :  1;  // Bits 6:6
    UINT32 IM                                      :  1;  // Bits 7:7
    UINT32 NEXT_DEVICE_ACTIVITY                    :  21;  // Bits 28:8
    UINT32 DISABLE_MDID_EVALUATION                 :  1;  // Bits 29:29
    UINT32 FORCE_MDID_OVERRIDE                     :  1;  // Bits 30:30
    UINT32                                         :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} PCU_CR_DEVICE_IDLE_DURATION_OVERRIDE_PCU_STRUCT;

typedef union {
  struct {
    UINT32                                         :  4;  // Bits 3:0
    UINT32 PECI_CMD                                :  8;  // Bits 11:4
    UINT32                                         :  20;  // Bits 31:12
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} PCU_CR_CHAP_CONFIG_PCU_STRUCT;

typedef union {
  struct {
    UINT32 DEBUG_ENERGY_PP0_VALUE                  :  10;  // Bits 9:0
    UINT32 DEBUG_ENERGY_PP1_VALUE                  :  10;  // Bits 19:10
    UINT32 DEBUG_ENERGY_SA_VALUE                   :  10;  // Bits 29:20
    UINT32                                         :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} PCU_CR_ENERGY_DEBUG_PCU_STRUCT;

typedef union {
  struct {
    UINT32 SKPDLow                                 :  32;  // Bits 31:0
    UINT32 SKPDHigh                                :  32;  // Bits 63:32
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} PCU_CR_SSKPD_PCU_STRUCT;

typedef union {
  struct {
    UINT32 PPDN_INIT                               :  12;  // Bits 11:0
    UINT32                                         :  20;  // Bits 31:12
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} PCU_CR_C2C3TT_PCU_STRUCT;

typedef union {
  struct {
    UINT32 DDR_TIMER_VALUE                         :  13;  // Bits 12:0
    UINT32                                         :  19;  // Bits 31:13
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} PCU_CR_C2_DDR_TT_PCU_STRUCT;

typedef union {
  struct {
    UINT32 NSTL                                    :  10;  // Bits 9:0
    UINT32 MULTIPLIER                              :  3;  // Bits 12:10
    UINT32                                         :  1;  // Bits 13:13
    UINT32 FORCE_NL                                :  1;  // Bits 14:14
    UINT32 NL_V                                    :  1;  // Bits 15:15
    UINT32 SXL                                     :  10;  // Bits 25:16
    UINT32 SXLM                                    :  3;  // Bits 28:26
    UINT32                                         :  1;  // Bits 29:29
    UINT32 FORCE_SXL                               :  1;  // Bits 30:30
    UINT32 SXL_V                                   :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} PCU_CR_PCIE_ILTR_OVRD_PCU_STRUCT;

typedef union {
  struct {
    UINT32 NL_VALUE                                :  10;  // Bits 9:0
    UINT32 NL_SCALE                                :  3;  // Bits 12:10
    UINT32 NL_RESERVED                             :  2;  // Bits 14:13
    UINT32 NL_VALID                                :  1;  // Bits 15:15
    UINT32 SXL_VALUE                               :  10;  // Bits 25:16
    UINT32 SXL_SCALE                               :  3;  // Bits 28:26
    UINT32 SXL_RESERVED                            :  2;  // Bits 30:29
    UINT32 SXL_VALID                               :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} PCU_CR_PCIE_ILTR_VAL_PCU_0_STRUCT;

typedef union {
  struct {
    UINT32 NL_VALUE                                :  10;  // Bits 9:0
    UINT32 NL_SCALE                                :  3;  // Bits 12:10
    UINT32 NL_RESERVED                             :  2;  // Bits 14:13
    UINT32 NL_VALID                                :  1;  // Bits 15:15
    UINT32 SXL_VALUE                               :  10;  // Bits 25:16
    UINT32 SXL_SCALE                               :  3;  // Bits 28:26
    UINT32 SXL_RESERVED                            :  2;  // Bits 30:29
    UINT32 SXL_VALID                               :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} PCU_CR_PCIE_ILTR_VAL_PCU_1_STRUCT;

typedef union {
  struct {
    UINT32 NL_VALUE                                :  10;  // Bits 9:0
    UINT32 NL_SCALE                                :  3;  // Bits 12:10
    UINT32 NL_RESERVED                             :  2;  // Bits 14:13
    UINT32 NL_VALID                                :  1;  // Bits 15:15
    UINT32 SXL_VALUE                               :  10;  // Bits 25:16
    UINT32 SXL_SCALE                               :  3;  // Bits 28:26
    UINT32 SXL_RESERVED                            :  2;  // Bits 30:29
    UINT32 SXL_VALID                               :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} PCU_CR_PCIE_ILTR_VAL_PCU_2_STRUCT;

typedef union {
  struct {
    UINT32 EN_CLK                                  :  1;  // Bits 0:0
    UINT32 L0_DATA_BYTE_SEL                        :  7;  // Bits 7:1
    UINT32 L0_BYP_SEL                              :  1;  // Bits 8:8
    UINT32 L1_DATA_BYTE_SEL                        :  7;  // Bits 15:9
    UINT32 L1_BYP_SEL                              :  1;  // Bits 16:16
    UINT32                                         :  14;  // Bits 30:17
    UINT32 VORANGE                                 :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} PCU_CR_VISA_CTL_PTPCFSMS_PCU_STRUCT;

typedef union {
  struct {
    UINT32 FXB_Li_BIT0_DATA_BIT_SEL                :  3;  // Bits 2:0
    UINT32 FXB_Li_BIT0_DATA_BYTE_SEL               :  1;  // Bits 3:3
    UINT32 FXB_Li_BIT1_DATA_BIT_SEL                :  3;  // Bits 6:4
    UINT32 FXB_Li_BIT1_DATA_BYTE_SEL               :  1;  // Bits 7:7
    UINT32 FXB_Li_BIT2_DATA_BIT_SEL                :  3;  // Bits 10:8
    UINT32 FXB_Li_BIT2_DATA_BYTE_SEL               :  1;  // Bits 11:11
    UINT32 FXB_Li_BIT3_DATA_BIT_SEL                :  3;  // Bits 14:12
    UINT32 FXB_Li_BIT3_DATA_BYTE_SEL               :  1;  // Bits 15:15
    UINT32 FXB_Li_BIT4_DATA_BIT_SEL                :  3;  // Bits 18:16
    UINT32 FXB_Li_BIT4_DATA_BYTE_SEL               :  1;  // Bits 19:19
    UINT32 FXB_Li_BIT5_DATA_BIT_SEL                :  3;  // Bits 22:20
    UINT32 FXB_Li_BIT5_DATA_BYTE_SEL               :  1;  // Bits 23:23
    UINT32 FXB_Li_BIT6_DATA_BIT_SEL                :  3;  // Bits 26:24
    UINT32 FXB_Li_BIT6_DATA_BYTE_SEL               :  1;  // Bits 27:27
    UINT32 FXB_Li_BIT7_DATA_BIT_SEL                :  3;  // Bits 30:28
    UINT32 FXB_Li_BIT7_DATA_BYTE_SEL               :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} PCU_CR_VISA_XBAR_PTPCFSMS_PCU_STRUCT;

typedef union {
  struct {
    UINT32 EN_CLK                                  :  1;  // Bits 0:0
    UINT32 L0_DATA_BYTE_SEL                        :  7;  // Bits 7:1
    UINT32 L0_BYP_SEL                              :  1;  // Bits 8:8
    UINT32 L1_DATA_BYTE_SEL                        :  7;  // Bits 15:9
    UINT32 L1_BYP_SEL                              :  1;  // Bits 16:16
    UINT32                                         :  14;  // Bits 30:17
    UINT32 VORANGE                                 :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} PCU_CR_VISA_CTL_PTPCIOREGS_PCU_STRUCT;

typedef union {
  struct {
    UINT32 WINDOW_SLIDE_L0                         :  3;  // Bits 2:0
    UINT32 ALT_L0_DATA_BYTE_SEL                    :  7;  // Bits 9:3
    UINT32 WINDOW_SLIDE_L1                         :  3;  // Bits 12:10
    UINT32 ALT_L1_DATA_BYTE_SEL                    :  7;  // Bits 19:13
    UINT32                                         :  12;  // Bits 31:20
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} PCU_CR_VISA_SLIDE_PTPCIOREGS_PCU_STRUCT;

typedef union {
  struct {
    UINT32 WINDOW_SLIDE_L0                         :  3;  // Bits 2:0
    UINT32 ALT_L0_DATA_BYTE_SEL                    :  7;  // Bits 9:3
    UINT32 WINDOW_SLIDE_L1                         :  3;  // Bits 12:10
    UINT32 ALT_L1_DATA_BYTE_SEL                    :  7;  // Bits 19:13
    UINT32                                         :  12;  // Bits 31:20
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} PCU_CR_VISA_SLIDE_PTPCFSMS_PCU_STRUCT;

typedef union {
  struct {
    UINT32 DATA                                    :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} PCU_CR_BIOS_MAILBOX_DATA_PCU_STRUCT;

typedef union {
  struct {
    UINT32 COMMAND                                 :  8;  // Bits 7:0
    UINT32 ADDR                                    :  21;  // Bits 28:8
    UINT32                                         :  2;  // Bits 30:29
    UINT32 RUN_BUSY                                :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} PCU_CR_BIOS_MAILBOX_INTERFACE_PCU_STRUCT;

typedef union {
  struct {
    UINT32 RST_CPL                                 :  1;  // Bits 0:0
    UINT32 PCIE_ENUMERATION_DONE                   :  1;  // Bits 1:1
    UINT32 C7_ALLOWED                              :  1;  // Bits 2:2
    UINT32                                         :  29;  // Bits 31:3
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} PCU_CR_BIOS_RESET_CPL_PCU_STRUCT;

typedef union {
  struct {
    UINT32 REQ_DATA                                :  4;  // Bits 3:0
    UINT32 REQ_TYPE                                :  1;  // Bits 4:4
    UINT32 REQ_DATA_MSB                            :  1;  // Bits 5:5
    UINT32                                         :  2;  // Bits 7:6
    UINT32 REQ_QCLK_ODD_RATIO                      :  1;  // Bits 8:8
    UINT32                                         :  22;  // Bits 30:9
    UINT32 RUN_BUSY                                :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} PCU_CR_MC_BIOS_REQ_PCU_STRUCT;

typedef union {
  struct {
    UINT32 MC_FREQ                                 :  4;  // Bits 3:0
    UINT32 MC_FREQ_TYPE                            :  1;  // Bits 4:4
    UINT32 MC_FREQ_MSB                             :  1;  // Bits 5:5
    UINT32                                         :  2;  // Bits 7:6
    UINT32 QCLK_ODD_RATIO                          :  1;  // Bits 8:8
    UINT32                                         :  23;  // Bits 31:9
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} PCU_CR_MC_BIOS_DATA_PCU_STRUCT;

typedef union {
  struct {
    UINT32 SACG_ENA                                :  1;  // Bits 0:0
    UINT32 MPLL_OFF_ENA                            :  1;  // Bits 1:1
    UINT32 PPLL_OFF_ENA                            :  1;  // Bits 2:2
    UINT32                                         :  5;  // Bits 7:3
    UINT32 SACG_SEN                                :  1;  // Bits 8:8
    UINT32 MPLL_OFF_SEN                            :  1;  // Bits 9:9
    UINT32 MDLL_OFF_SEN                            :  1;  // Bits 10:10
    UINT32 SACG_SREXIT                             :  1;  // Bits 11:11
    UINT32 NSWAKE_SREXIT                           :  1;  // Bits 12:12
    UINT32 SACG_MPLL                               :  1;  // Bits 13:13
    UINT32 MPLL_ON_DE                              :  1;  // Bits 14:14
    UINT32 MDLL_ON_DE                              :  1;  // Bits 15:15
    UINT32                                         :  16;  // Bits 31:16
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} PCU_CR_SAPMCTL_PCU_STRUCT;

typedef union {
  struct {
    UINT32 COMP_DISABLE                            :  1;  // Bits 0:0
    UINT32 COMP_INTERVAL                           :  4;  // Bits 4:1
    UINT32                                         :  3;  // Bits 7:5
    UINT32 COMP_FORCE                              :  1;  // Bits 8:8
    UINT32                                         :  23;  // Bits 31:9
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} PCU_CR_P_COMP_PCU_STRUCT;

typedef union {
  struct {
    UINT32 COMP_DISABLE                            :  1;  // Bits 0:0
    UINT32 COMP_INTERVAL                           :  4;  // Bits 4:1
    UINT32                                         :  3;  // Bits 7:5
    UINT32 COMP_FORCE                              :  1;  // Bits 8:8
    UINT32                                         :  23;  // Bits 31:9
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} PCU_CR_M_COMP_PCU_STRUCT;

typedef union {
  struct {
    UINT32 PCIE_PWR_CONTROL                        :  1;  // Bits 0:0
    UINT32                                         :  31;  // Bits 31:1
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} PCU_CR_SAPM_PG_CONTROL_PCU_STRUCT;

typedef union {
  struct {
    UINT32 PCIE_PWR_STATUS                         :  1;  // Bits 0:0
    UINT32                                         :  31;  // Bits 31:1
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} PCU_CR_SAPM_PG_STATUS_PCU_STRUCT;

typedef union {
  struct {
    UINT32 TDP_RATIO                               :  8;  // Bits 7:0
    UINT32                                         :  24;  // Bits 31:8
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} PCU_CR_CONFIG_TDP_NOMINAL_PCU_STRUCT;

typedef union {
  struct {
    UINT32 PKG_TDP                                 :  15;  // Bits 14:0
    UINT32                                         :  1;  // Bits 15:15
    UINT32 TDP_RATIO                               :  8;  // Bits 23:16
    UINT32                                         :  8;  // Bits 31:24
    UINT32 PKG_MAX_PWR                             :  15;  // Bits 46:32
    UINT32                                         :  1;  // Bits 47:47
    UINT32 PKG_MIN_PWR                             :  15;  // Bits 62:48
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} PCU_CR_CONFIG_TDP_LEVEL1_PCU_STRUCT;

typedef union {
  struct {
    UINT32 PKG_TDP                                 :  15;  // Bits 14:0
    UINT32                                         :  1;  // Bits 15:15
    UINT32 TDP_RATIO                               :  8;  // Bits 23:16
    UINT32                                         :  8;  // Bits 31:24
    UINT32 PKG_MAX_PWR                             :  15;  // Bits 46:32
    UINT32                                         :  1;  // Bits 47:47
    UINT32 PKG_MIN_PWR                             :  15;  // Bits 62:48
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} PCU_CR_CONFIG_TDP_LEVEL2_PCU_STRUCT;

typedef union {
  struct {
    UINT32 TDP_LEVEL                               :  2;  // Bits 1:0
    UINT32                                         :  29;  // Bits 30:2
    UINT32 CONFIG_TDP_LOCK                         :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} PCU_CR_CONFIG_TDP_CONTROL_PCU_STRUCT;

typedef union {
  struct {
    UINT32 MAX_NON_TURBO_RATIO                     :  8;  // Bits 7:0
    UINT32                                         :  23;  // Bits 30:8
    UINT32 TURBO_ACTIVATION_RATIO_LOCK             :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} PCU_CR_TURBO_ACTIVATION_RATIO_PCU_STRUCT;

#pragma pack(pop)
#endif
