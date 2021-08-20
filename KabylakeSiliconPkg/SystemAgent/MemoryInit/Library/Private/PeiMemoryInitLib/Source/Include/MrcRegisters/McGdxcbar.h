/** @file
  This file was automatically generated. Modify at your own risk.

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
#ifndef __McGdxcbar_h__
#define __McGdxcbar_h__

#pragma pack(push, 1)
#include "MrcTypes.h"

typedef union {
  struct {
    UINT32                                         :  1;  // Bits 0:0
    UINT32 EN_RING_ADQ                             :  1;  // Bits 1:1
    UINT32 EN_RING_BLQ                             :  1;  // Bits 2:2
    UINT32 EN_RING_AKQ                             :  1;  // Bits 3:3
    UINT32 EN_RING_IVQ                             :  1;  // Bits 4:4
    UINT32 EN_IDIQ                                 :  1;  // Bits 5:5
    UINT32 EN_mc_UCLKQ                             :  1;  // Bits 6:6
    UINT32                                         :  1;  // Bits 7:7
    UINT32 UP_EN_ADQ                               :  1;  // Bits 8:8
    UINT32 DN_EN_ADQ                               :  1;  // Bits 9:9
    UINT32 UP_EN_BLQ                               :  1;  // Bits 10:10
    UINT32 DN_EN_BLQ                               :  1;  // Bits 11:11
    UINT32 UP_EN_AKQ                               :  1;  // Bits 12:12
    UINT32 DN_EN_AKQ                               :  1;  // Bits 13:13
    UINT32 MOTQ_TIMING_SELECT                      :  1;  // Bits 14:14
    UINT32 SPARE                                   :  5;  // Bits 19:15
    UINT32                                         :  12;  // Bits 31:20
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MPCOHTRK_CR_GDXC_SW_UCLK_SRC_CFG_STRUCT;

typedef union {
  struct {
    UINT32 EN_Core0_T0                             :  1;  // Bits 0:0
    UINT32 EN_Core0_T1                             :  1;  // Bits 1:1
    UINT32 EN_Core1_T0                             :  1;  // Bits 2:2
    UINT32 EN_Core1_T1                             :  1;  // Bits 3:3
    UINT32 EN_Core2_T0                             :  1;  // Bits 4:4
    UINT32 EN_Core2_T1                             :  1;  // Bits 5:5
    UINT32 EN_Core3_T0                             :  1;  // Bits 6:6
    UINT32 EN_Core3_T1                             :  1;  // Bits 7:7
    UINT32 EN_GT                                   :  1;  // Bits 8:8
    UINT32 MEM_CHR_RD                              :  1;  // Bits 9:9
    UINT32 MEM_CHR_WR                              :  1;  // Bits 10:10
    UINT32 MEM_NC                                  :  1;  // Bits 11:11
    UINT32 EN_CBO_Exp_WB                           :  1;  // Bits 12:12
    UINT32 SNP_Access                              :  1;  // Bits 13:13
    UINT32 SELECT_PRE                              :  1;  // Bits 14:14
    UINT32                                         :  17;  // Bits 31:15
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MPCOHTRK_CR_GDXC_QUALIFIER_GLOBAL_STRUCT;

typedef union {
  struct {
    UINT32 CR_CHR_RD                               :  3;  // Bits 2:0
    UINT32 CHR_RD_STAT_MOD                         :  1;  // Bits 3:3
    UINT32 CR_CHR_WR                               :  4;  // Bits 7:4
    UINT32 CR_NC_RD                                :  3;  // Bits 10:8
    UINT32 NC_RD_STAT_MOD                          :  1;  // Bits 11:11
    UINT32 CR_NC_WR                                :  4;  // Bits 15:12
    UINT32 NC_WR_STAT_MOD                          :  1;  // Bits 16:16
    UINT32 Data_Core0                              :  1;  // Bits 17:17
    UINT32 Data_Core1                              :  1;  // Bits 18:18
    UINT32 Data_Core2                              :  1;  // Bits 19:19
    UINT32 Data_Core3                              :  1;  // Bits 20:20
    UINT32 Data_CBO                                :  1;  // Bits 21:21
    UINT32 Data_GT                                 :  1;  // Bits 22:22
    UINT32                                         :  9;  // Bits 31:23
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MPCOHTRK_CR_GDXC_QUALIFIER_BL_STRUCT;

typedef union {
  struct {
    UINT32 OVF_Global                              :  1;  // Bits 0:0
    UINT32 OVF_Ring_AD                             :  1;  // Bits 1:1
    UINT32 OVF_Ring_BL                             :  1;  // Bits 2:2
    UINT32 OVF_Ring_AK                             :  1;  // Bits 3:3
    UINT32 OVF_Ring_IV                             :  1;  // Bits 4:4
    UINT32                                         :  5;  // Bits 9:5
    UINT32 OVF_mcUCLK                              :  1;  // Bits 10:10
    UINT32                                         :  21;  // Bits 31:11
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MPCOHTRK_CR_GDXC_OVF_STATUS_STRUCT;

typedef union {
  struct {
    UINT32 MEM_PTR                                 :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MPCOHTRK_CR_GDXC_MOT_ADDRESS_LO_STRUCT;

typedef union {
  struct {
    UINT32 MEM_PTR                                 :  1;  // Bits 0:0
    UINT32 BUFFER_WRAP                             :  1;  // Bits 1:1
    UINT32 SPARE                                   :  4;  // Bits 5:2
    UINT32                                         :  26;  // Bits 31:6
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MPCOHTRK_CR_GDXC_MOT_ADDRESS_HI_STRUCT;

typedef union {
  struct {
    UINT32 START_ADDRESS                           :  16;  // Bits 15:0
    UINT32 END_ADDRESS                             :  16;  // Bits 31:16
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MPCOHTRK_CR_GDXC_MOT_REGION_STRUCT;

typedef union {
  struct {
    UINT32 MEM_PTR                                 :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MPCOHTRK_CR_GDXC_OCLA_ADDRESS_LO_STRUCT;

typedef union {
  struct {
    UINT32 MEM_PTR                                 :  1;  // Bits 0:0
    UINT32 BUFFER_WRAP                             :  1;  // Bits 1:1
    UINT32 LOCK                                    :  1;  // Bits 2:2
    UINT32 SPARE                                   :  4;  // Bits 6:3
    UINT32                                         :  25;  // Bits 31:7
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MPCOHTRK_CR_GDXC_OCLA_ADDRESS_HI_STRUCT;

typedef union {
  struct {
    UINT32 START_ADDRESS                           :  16;  // Bits 15:0
    UINT32 END_ADDRESS                             :  16;  // Bits 31:16
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MPCOHTRK_CR_GDXC_OCLA_REGION_STRUCT;

typedef union {
  struct {
    UINT32 Mask_bits                               :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MPCOHTRK_CR_GDXC_MASK_ADDRESSL_STRUCT;

typedef union {
  struct {
    UINT32 Mask_bits                               :  7;  // Bits 6:0
    UINT32                                         :  25;  // Bits 31:7
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MPCOHTRK_CR_GDXC_MASK_ADDRESSH_STRUCT;

typedef union {
  struct {
    UINT32 ARM_bits                                :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MPCOHTRK_CR_GDXC_ARM_ADDRESSL_STRUCT;

typedef union {
  struct {
    UINT32 ARM_bits                                :  7;  // Bits 6:0
    UINT32                                         :  25;  // Bits 31:7
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MPCOHTRK_CR_GDXC_ARM_ADDRESSH_STRUCT;

typedef union {
  struct {
    UINT32 Trace_Source_Enable                     :  1;  // Bits 0:0
    UINT32 Channel_Select                          :  2;  // Bits 2:1
    UINT32 ACC_Trace_Element_Width                 :  1;  // Bits 3:3
    UINT32 ECC_Mode                                :  1;  // Bits 4:4
    UINT32 Final_Arbiter_Weight                    :  2;  // Bits 6:5
    UINT32 DDR_Trace_En                            :  1;  // Bits 7:7
    UINT32 DDR_Trig_En                             :  1;  // Bits 8:8
    UINT32 Clock_Gate_Ovr                          :  1;  // Bits 9:9
    UINT32 SO_X_OVRD                               :  1;  // Bits 10:10
    UINT32 DDR_Type                                :  2;  // Bits 12:11
    UINT32 Rd_Wr_Overlap                           :  1;  // Bits 13:13
    UINT32 Spare                                   :  7;  // Bits 20:14
    UINT32                                         :  10;  // Bits 30:21
    UINT32 QCLK_DOMAIN_UP                          :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRPL_CR_DDR_TRACE_SOURCE_CONFIG_STRUCT;

typedef union {
  struct {
    UINT32 Tx_Delay_R0                             :  8;  // Bits 7:0
    UINT32 Tx_Delay_R1                             :  8;  // Bits 15:8
    UINT32 Tx_Delay_R2                             :  8;  // Bits 23:16
    UINT32 Tx_Delay_R3                             :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRPL_CR_DDR_TX_DELAY_LOW_STRUCT;

typedef union {
  struct {
    UINT32 Tx_Latency_R0                           :  8;  // Bits 7:0
    UINT32 Tx_Latency_R1                           :  8;  // Bits 15:8
    UINT32 Tx_Latency_R2                           :  8;  // Bits 23:16
    UINT32 Tx_Latency_R3                           :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRPL_CR_DDR_TX_LATENCY_LOW_STRUCT;

typedef union {
  struct {
    UINT32 Rx_Latency_R0                           :  8;  // Bits 7:0
    UINT32 Rx_Latency_R1                           :  8;  // Bits 15:8
    UINT32 Rx_Latency_R2                           :  8;  // Bits 23:16
    UINT32 Rx_Latency_R3                           :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRPL_CR_DDR_RX_LATENCY_LOW_STRUCT;

typedef union {
  struct {
    UINT32 NOA_MUX_3_0                             :  2;  // Bits 1:0
    UINT32 NOA_MUX_7_4                             :  2;  // Bits 3:2
    UINT32 MaskMatch_MUX_0                         :  2;  // Bits 5:4
    UINT32 MaskMatch_MUX_1                         :  2;  // Bits 7:6
    UINT32 MaskMatch_MUX_2                         :  2;  // Bits 9:8
    UINT32 MaskMatch_MUX_3                         :  2;  // Bits 11:10
    UINT32 FINAL_MUX_3_0                           :  2;  // Bits 13:12
    UINT32 FINAL_MUX_7_4                           :  2;  // Bits 15:14
    UINT32 SYS_ADDR_RdWr                           :  2;  // Bits 17:16
    UINT32 Transaction_match                       :  1;  // Bits 18:18
    UINT32 DQ_Chunk_Num                            :  3;  // Bits 21:19
    UINT32                                         :  10;  // Bits 31:22
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRPL_CR_DDR_TRIGGER_CONFIG_STRUCT;

typedef union {
  struct {
    UINT32 ACC                                     :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRPL_CR_DDR_ACC_TRIG_MATCH0_STRUCT;

typedef union {
  struct {
    UINT32 ACC                                     :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRPL_CR_DDR_ACC_TRIG_MATCH1_STRUCT;

typedef union {
  struct {
    UINT32 ACC                                     :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRPL_CR_DDR_ACC_TRIG_MATCH2_STRUCT;

typedef union {
  struct {
    UINT32 ACC                                     :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRPL_CR_DDR_ACC_TRIG_MATCH3_STRUCT;

typedef union {
  struct {
    UINT32 ACC                                     :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRPL_CR_DDR_ACC_TRIG_MASK0_STRUCT;

typedef union {
  struct {
    UINT32 ACC                                     :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRPL_CR_DDR_ACC_TRIG_MASK1_STRUCT;

typedef union {
  struct {
    UINT32 ACC                                     :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRPL_CR_DDR_ACC_TRIG_MASK2_STRUCT;

typedef union {
  struct {
    UINT32 ACC                                     :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRPL_CR_DDR_ACC_TRIG_MASK3_STRUCT;

typedef union {
  struct {
    UINT32 DQ                                      :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRPL_CR_DDR_DQ_TRIG_MATCH_LOW_STRUCT;

typedef union {
  struct {
    UINT32 DQ                                      :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRPL_CR_DDR_DQ_TRIG_MASK_LOW_STRUCT;

typedef union {
  struct {
    UINT32 DQ                                      :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRPL_CR_DDR_DQ_TRIG_MATCH_HIGH_STRUCT;

typedef union {
  struct {
    UINT32 DQ                                      :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRPL_CR_DDR_DQ_TRIG_MASK_HIGH_STRUCT;

typedef union {
  struct {
    UINT32 ACC                                     :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRPL_CR_DDR_ACC_FILTER_MATCH0_STRUCT;

typedef union {
  struct {
    UINT32 ACC                                     :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRPL_CR_DDR_ACC_FILTER_MATCH1_STRUCT;

typedef union {
  struct {
    UINT32 ACC                                     :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRPL_CR_DDR_ACC_FILTER_MASK0_STRUCT;

typedef union {
  struct {
    UINT32 ACC                                     :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRPL_CR_DDR_ACC_FILTER_MASK1_STRUCT;

typedef union {
  struct {
    UINT32 ACC_Trace_Enable                        :  1;  // Bits 0:0
    UINT32 DQ_Data_Width                           :  2;  // Bits 2:1
    UINT32 ACC_Capture_Mode                        :  1;  // Bits 3:3
    UINT32 Read_Rank_Filter                        :  4;  // Bits 7:4
    UINT32 Write_Rank_Filter                       :  4;  // Bits 11:8
    UINT32 Filter_Window_Length                    :  8;  // Bits 19:12
    UINT32 Filter_ACC                              :  1;  // Bits 20:20
    UINT32 Filter_DQ_Data                          :  1;  // Bits 21:21
    UINT32 Quarter_Mode_Byte_Select                :  2;  // Bits 23:22
    UINT32 Half_Mode_Byte_Select                   :  1;  // Bits 24:24
    UINT32 Filter_Out                              :  1;  // Bits 25:25
    UINT32 Sys_addr_filter                         :  1;  // Bits 26:26
    UINT32 Sys_addr_mode                           :  1;  // Bits 27:27
    UINT32 CMD_Unforce                             :  1;  // Bits 28:28
    UINT32 ACC_qual_mode                           :  1;  // Bits 29:29
    UINT32                                         :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRPL_CR_DDR_TRACE_FILTER_CONFIG_STRUCT;

typedef union {
  struct {
    UINT32 CS_encode_en                            :  1;  // Bits 0:0
    UINT32 ODT_Xbar_0                              :  4;  // Bits 4:1
    UINT32 ODT_Xbar_1                              :  4;  // Bits 8:5
    UINT32 DDR4_ACC_31                             :  1;  // Bits 9:9
    UINT32 DDR4_ACC_30                             :  1;  // Bits 10:10
    UINT32 DDR4_ACC_29                             :  1;  // Bits 11:11
    UINT32 DDR4_ACC_28                             :  1;  // Bits 12:12
    UINT32 DDR4_ACC_27                             :  1;  // Bits 13:13
    UINT32 DDR4_ACC_25                             :  1;  // Bits 14:14
    UINT32                                         :  17;  // Bits 31:15
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRPL_CR_DDR_ACC_FORMAT_SELECT_STRUCT;

typedef union {
  struct {
    UINT32 Tx_Latency_R0                           :  8;  // Bits 7:0
    UINT32 Tx_Latency_R1                           :  8;  // Bits 15:8
    UINT32 Tx_Latency_R2                           :  8;  // Bits 23:16
    UINT32 Tx_Latency_R3                           :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRPL_CR_DDR_TX_LATENCY_HIGH_STRUCT;

typedef union {
  struct {
    UINT32 Rx_Latency_R0                           :  8;  // Bits 7:0
    UINT32 Rx_Latency_R1                           :  8;  // Bits 15:8
    UINT32 Rx_Latency_R2                           :  8;  // Bits 23:16
    UINT32 Rx_Latency_R3                           :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRPL_CR_DDR_RX_LATENCY_HIGH_STRUCT;

typedef union {
  struct {
    UINT32 Tx_Delay_R0                             :  8;  // Bits 7:0
    UINT32 Tx_Delay_R1                             :  8;  // Bits 15:8
    UINT32 Tx_Delay_R2                             :  8;  // Bits 23:16
    UINT32 Tx_Delay_R3                             :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRPL_CR_DDR_TX_DELAY_HIGH_STRUCT;

typedef union {
  struct {
    UINT32 Signal_In_mode                          :  4;  // Bits 3:0
    UINT32 Event_In_mode                           :  8;  // Bits 11:4
    UINT32                                         :  8;  // Bits 19:12
    UINT32 SCT0_match_mode                         :  1;  // Bits 20:20
    UINT32 SCT1_match_mode                         :  1;  // Bits 21:21
    UINT32 SCT2_match_mode                         :  1;  // Bits 22:22
    UINT32 SCT3_match_mode                         :  1;  // Bits 23:23
    UINT32 LCT0_match_mode                         :  1;  // Bits 24:24
    UINT32 LCT1_match_mode                         :  1;  // Bits 25:25
    UINT32                                         :  2;  // Bits 27:26
    UINT32 OP_Type                                 :  1;  // Bits 28:28
    UINT32                                         :  3;  // Bits 31:29
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM0_STRUCT;

typedef union {
  struct {
    UINT32 Signal_In_mode                          :  4;  // Bits 3:0
    UINT32 Event_In_mode                           :  8;  // Bits 11:4
    UINT32                                         :  8;  // Bits 19:12
    UINT32 SCT0_match_mode                         :  1;  // Bits 20:20
    UINT32 SCT1_match_mode                         :  1;  // Bits 21:21
    UINT32 SCT2_match_mode                         :  1;  // Bits 22:22
    UINT32 SCT3_match_mode                         :  1;  // Bits 23:23
    UINT32 LCT0_match_mode                         :  1;  // Bits 24:24
    UINT32 LCT1_match_mode                         :  1;  // Bits 25:25
    UINT32                                         :  2;  // Bits 27:26
    UINT32 OP_Type                                 :  1;  // Bits 28:28
    UINT32                                         :  3;  // Bits 31:29
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM1_STRUCT;

typedef union {
  struct {
    UINT32 Signal_In_mode                          :  4;  // Bits 3:0
    UINT32 Event_In_mode                           :  8;  // Bits 11:4
    UINT32                                         :  8;  // Bits 19:12
    UINT32 SCT0_match_mode                         :  1;  // Bits 20:20
    UINT32 SCT1_match_mode                         :  1;  // Bits 21:21
    UINT32 SCT2_match_mode                         :  1;  // Bits 22:22
    UINT32 SCT3_match_mode                         :  1;  // Bits 23:23
    UINT32 LCT0_match_mode                         :  1;  // Bits 24:24
    UINT32 LCT1_match_mode                         :  1;  // Bits 25:25
    UINT32                                         :  2;  // Bits 27:26
    UINT32 OP_Type                                 :  1;  // Bits 28:28
    UINT32                                         :  3;  // Bits 31:29
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM2_STRUCT;

typedef union {
  struct {
    UINT32 Signal_In_mode                          :  4;  // Bits 3:0
    UINT32 Event_In_mode                           :  8;  // Bits 11:4
    UINT32                                         :  8;  // Bits 19:12
    UINT32 SCT0_match_mode                         :  1;  // Bits 20:20
    UINT32 SCT1_match_mode                         :  1;  // Bits 21:21
    UINT32 SCT2_match_mode                         :  1;  // Bits 22:22
    UINT32 SCT3_match_mode                         :  1;  // Bits 23:23
    UINT32 LCT0_match_mode                         :  1;  // Bits 24:24
    UINT32 LCT1_match_mode                         :  1;  // Bits 25:25
    UINT32                                         :  2;  // Bits 27:26
    UINT32 OP_Type                                 :  1;  // Bits 28:28
    UINT32                                         :  3;  // Bits 31:29
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM3_STRUCT;

typedef union {
  struct {
    UINT32 Signal_In_mode                          :  4;  // Bits 3:0
    UINT32 Event_In_mode                           :  8;  // Bits 11:4
    UINT32                                         :  8;  // Bits 19:12
    UINT32 SCT0_match_mode                         :  1;  // Bits 20:20
    UINT32 SCT1_match_mode                         :  1;  // Bits 21:21
    UINT32 SCT2_match_mode                         :  1;  // Bits 22:22
    UINT32 SCT3_match_mode                         :  1;  // Bits 23:23
    UINT32 LCT0_match_mode                         :  1;  // Bits 24:24
    UINT32 LCT1_match_mode                         :  1;  // Bits 25:25
    UINT32                                         :  2;  // Bits 27:26
    UINT32 OP_Type                                 :  1;  // Bits 28:28
    UINT32                                         :  3;  // Bits 31:29
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM4_STRUCT;

typedef union {
  struct {
    UINT32 Signal_In_mode                          :  4;  // Bits 3:0
    UINT32 Event_In_mode                           :  8;  // Bits 11:4
    UINT32                                         :  8;  // Bits 19:12
    UINT32 SCT0_match_mode                         :  1;  // Bits 20:20
    UINT32 SCT1_match_mode                         :  1;  // Bits 21:21
    UINT32 SCT2_match_mode                         :  1;  // Bits 22:22
    UINT32 SCT3_match_mode                         :  1;  // Bits 23:23
    UINT32 LCT0_match_mode                         :  1;  // Bits 24:24
    UINT32 LCT1_match_mode                         :  1;  // Bits 25:25
    UINT32                                         :  2;  // Bits 27:26
    UINT32 OP_Type                                 :  1;  // Bits 28:28
    UINT32                                         :  3;  // Bits 31:29
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM5_STRUCT;

typedef union {
  struct {
    UINT32 Signal_In_mode                          :  4;  // Bits 3:0
    UINT32 Event_In_mode                           :  8;  // Bits 11:4
    UINT32                                         :  8;  // Bits 19:12
    UINT32 SCT0_match_mode                         :  1;  // Bits 20:20
    UINT32 SCT1_match_mode                         :  1;  // Bits 21:21
    UINT32 SCT2_match_mode                         :  1;  // Bits 22:22
    UINT32 SCT3_match_mode                         :  1;  // Bits 23:23
    UINT32 LCT0_match_mode                         :  1;  // Bits 24:24
    UINT32 LCT1_match_mode                         :  1;  // Bits 25:25
    UINT32                                         :  2;  // Bits 27:26
    UINT32 OP_Type                                 :  1;  // Bits 28:28
    UINT32                                         :  3;  // Bits 31:29
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM6_STRUCT;

typedef union {
  struct {
    UINT32 Signal_In_mode                          :  4;  // Bits 3:0
    UINT32 Event_In_mode                           :  8;  // Bits 11:4
    UINT32                                         :  8;  // Bits 19:12
    UINT32 SCT0_match_mode                         :  1;  // Bits 20:20
    UINT32 SCT1_match_mode                         :  1;  // Bits 21:21
    UINT32 SCT2_match_mode                         :  1;  // Bits 22:22
    UINT32 SCT3_match_mode                         :  1;  // Bits 23:23
    UINT32 LCT0_match_mode                         :  1;  // Bits 24:24
    UINT32 LCT1_match_mode                         :  1;  // Bits 25:25
    UINT32                                         :  2;  // Bits 27:26
    UINT32 OP_Type                                 :  1;  // Bits 28:28
    UINT32                                         :  3;  // Bits 31:29
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM7_STRUCT;

typedef union {
  struct {
    UINT32 Signal_In_mode                          :  4;  // Bits 3:0
    UINT32 Event_In_mode                           :  8;  // Bits 11:4
    UINT32                                         :  8;  // Bits 19:12
    UINT32 SCT0_match_mode                         :  1;  // Bits 20:20
    UINT32 SCT1_match_mode                         :  1;  // Bits 21:21
    UINT32 SCT2_match_mode                         :  1;  // Bits 22:22
    UINT32 SCT3_match_mode                         :  1;  // Bits 23:23
    UINT32 LCT0_match_mode                         :  1;  // Bits 24:24
    UINT32 LCT1_match_mode                         :  1;  // Bits 25:25
    UINT32                                         :  2;  // Bits 27:26
    UINT32 OP_Type                                 :  1;  // Bits 28:28
    UINT32                                         :  3;  // Bits 31:29
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM8_STRUCT;

typedef union {
  struct {
    UINT32 Signal_In_mode                          :  4;  // Bits 3:0
    UINT32 Event_In_mode                           :  8;  // Bits 11:4
    UINT32                                         :  8;  // Bits 19:12
    UINT32 SCT0_match_mode                         :  1;  // Bits 20:20
    UINT32 SCT1_match_mode                         :  1;  // Bits 21:21
    UINT32 SCT2_match_mode                         :  1;  // Bits 22:22
    UINT32 SCT3_match_mode                         :  1;  // Bits 23:23
    UINT32 LCT0_match_mode                         :  1;  // Bits 24:24
    UINT32 LCT1_match_mode                         :  1;  // Bits 25:25
    UINT32                                         :  2;  // Bits 27:26
    UINT32 OP_Type                                 :  1;  // Bits 28:28
    UINT32                                         :  3;  // Bits 31:29
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM9_STRUCT;

typedef union {
  struct {
    UINT32 Signal_In_mode                          :  4;  // Bits 3:0
    UINT32 Event_In_mode                           :  8;  // Bits 11:4
    UINT32                                         :  8;  // Bits 19:12
    UINT32 SCT0_match_mode                         :  1;  // Bits 20:20
    UINT32 SCT1_match_mode                         :  1;  // Bits 21:21
    UINT32 SCT2_match_mode                         :  1;  // Bits 22:22
    UINT32 SCT3_match_mode                         :  1;  // Bits 23:23
    UINT32 LCT0_match_mode                         :  1;  // Bits 24:24
    UINT32 LCT1_match_mode                         :  1;  // Bits 25:25
    UINT32                                         :  2;  // Bits 27:26
    UINT32 OP_Type                                 :  1;  // Bits 28:28
    UINT32                                         :  3;  // Bits 31:29
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM10_STRUCT;

typedef union {
  struct {
    UINT32 Signal_In_mode                          :  4;  // Bits 3:0
    UINT32 Event_In_mode                           :  8;  // Bits 11:4
    UINT32                                         :  8;  // Bits 19:12
    UINT32 SCT0_match_mode                         :  1;  // Bits 20:20
    UINT32 SCT1_match_mode                         :  1;  // Bits 21:21
    UINT32 SCT2_match_mode                         :  1;  // Bits 22:22
    UINT32 SCT3_match_mode                         :  1;  // Bits 23:23
    UINT32 LCT0_match_mode                         :  1;  // Bits 24:24
    UINT32 LCT1_match_mode                         :  1;  // Bits 25:25
    UINT32                                         :  2;  // Bits 27:26
    UINT32 OP_Type                                 :  1;  // Bits 28:28
    UINT32                                         :  3;  // Bits 31:29
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM11_STRUCT;

typedef union {
  struct {
    UINT32 Signal_In_mode                          :  4;  // Bits 3:0
    UINT32 Event_In_mode                           :  8;  // Bits 11:4
    UINT32                                         :  8;  // Bits 19:12
    UINT32 SCT0_match_mode                         :  1;  // Bits 20:20
    UINT32 SCT1_match_mode                         :  1;  // Bits 21:21
    UINT32 SCT2_match_mode                         :  1;  // Bits 22:22
    UINT32 SCT3_match_mode                         :  1;  // Bits 23:23
    UINT32 LCT0_match_mode                         :  1;  // Bits 24:24
    UINT32 LCT1_match_mode                         :  1;  // Bits 25:25
    UINT32                                         :  2;  // Bits 27:26
    UINT32 OP_Type                                 :  1;  // Bits 28:28
    UINT32                                         :  3;  // Bits 31:29
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM12_STRUCT;

typedef union {
  struct {
    UINT32 Signal_In_mode                          :  4;  // Bits 3:0
    UINT32 Event_In_mode                           :  8;  // Bits 11:4
    UINT32                                         :  8;  // Bits 19:12
    UINT32 SCT0_match_mode                         :  1;  // Bits 20:20
    UINT32 SCT1_match_mode                         :  1;  // Bits 21:21
    UINT32 SCT2_match_mode                         :  1;  // Bits 22:22
    UINT32 SCT3_match_mode                         :  1;  // Bits 23:23
    UINT32 LCT0_match_mode                         :  1;  // Bits 24:24
    UINT32 LCT1_match_mode                         :  1;  // Bits 25:25
    UINT32                                         :  2;  // Bits 27:26
    UINT32 OP_Type                                 :  1;  // Bits 28:28
    UINT32                                         :  3;  // Bits 31:29
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM13_STRUCT;

typedef union {
  struct {
    UINT32 Signal_In_mode                          :  4;  // Bits 3:0
    UINT32 Event_In_mode                           :  8;  // Bits 11:4
    UINT32                                         :  8;  // Bits 19:12
    UINT32 SCT0_match_mode                         :  1;  // Bits 20:20
    UINT32 SCT1_match_mode                         :  1;  // Bits 21:21
    UINT32 SCT2_match_mode                         :  1;  // Bits 22:22
    UINT32 SCT3_match_mode                         :  1;  // Bits 23:23
    UINT32 LCT0_match_mode                         :  1;  // Bits 24:24
    UINT32 LCT1_match_mode                         :  1;  // Bits 25:25
    UINT32                                         :  2;  // Bits 27:26
    UINT32 OP_Type                                 :  1;  // Bits 28:28
    UINT32                                         :  3;  // Bits 31:29
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM14_STRUCT;

typedef union {
  struct {
    UINT32 Signal_In_mode                          :  4;  // Bits 3:0
    UINT32 Event_In_mode                           :  8;  // Bits 11:4
    UINT32                                         :  8;  // Bits 19:12
    UINT32 SCT0_match_mode                         :  1;  // Bits 20:20
    UINT32 SCT1_match_mode                         :  1;  // Bits 21:21
    UINT32 SCT2_match_mode                         :  1;  // Bits 22:22
    UINT32 SCT3_match_mode                         :  1;  // Bits 23:23
    UINT32 LCT0_match_mode                         :  1;  // Bits 24:24
    UINT32 LCT1_match_mode                         :  1;  // Bits 25:25
    UINT32                                         :  2;  // Bits 27:26
    UINT32 OP_Type                                 :  1;  // Bits 28:28
    UINT32                                         :  3;  // Bits 31:29
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM15_STRUCT;

typedef union {
  struct {
    UINT32 Signal_In_select                        :  4;  // Bits 3:0
    UINT32 Event_In_select                         :  8;  // Bits 11:4
    UINT32                                         :  8;  // Bits 19:12
    UINT32 SCT0_select                             :  1;  // Bits 20:20
    UINT32 SCT1_select                             :  1;  // Bits 21:21
    UINT32 SCT2_select                             :  1;  // Bits 22:22
    UINT32 SCT3_select                             :  1;  // Bits 23:23
    UINT32 LCT0_select                             :  1;  // Bits 24:24
    UINT32 LCT1_select                             :  1;  // Bits 25:25
    UINT32                                         :  6;  // Bits 31:26
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM0_STRUCT;

typedef union {
  struct {
    UINT32 Signal_In_select                        :  4;  // Bits 3:0
    UINT32 Event_In_select                         :  8;  // Bits 11:4
    UINT32                                         :  8;  // Bits 19:12
    UINT32 SCT0_select                             :  1;  // Bits 20:20
    UINT32 SCT1_select                             :  1;  // Bits 21:21
    UINT32 SCT2_select                             :  1;  // Bits 22:22
    UINT32 SCT3_select                             :  1;  // Bits 23:23
    UINT32 LCT0_select                             :  1;  // Bits 24:24
    UINT32 LCT1_select                             :  1;  // Bits 25:25
    UINT32                                         :  6;  // Bits 31:26
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM1_STRUCT;

typedef union {
  struct {
    UINT32 Signal_In_select                        :  4;  // Bits 3:0
    UINT32 Event_In_select                         :  8;  // Bits 11:4
    UINT32                                         :  8;  // Bits 19:12
    UINT32 SCT0_select                             :  1;  // Bits 20:20
    UINT32 SCT1_select                             :  1;  // Bits 21:21
    UINT32 SCT2_select                             :  1;  // Bits 22:22
    UINT32 SCT3_select                             :  1;  // Bits 23:23
    UINT32 LCT0_select                             :  1;  // Bits 24:24
    UINT32 LCT1_select                             :  1;  // Bits 25:25
    UINT32                                         :  6;  // Bits 31:26
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM2_STRUCT;

typedef union {
  struct {
    UINT32 Signal_In_select                        :  4;  // Bits 3:0
    UINT32 Event_In_select                         :  8;  // Bits 11:4
    UINT32                                         :  8;  // Bits 19:12
    UINT32 SCT0_select                             :  1;  // Bits 20:20
    UINT32 SCT1_select                             :  1;  // Bits 21:21
    UINT32 SCT2_select                             :  1;  // Bits 22:22
    UINT32 SCT3_select                             :  1;  // Bits 23:23
    UINT32 LCT0_select                             :  1;  // Bits 24:24
    UINT32 LCT1_select                             :  1;  // Bits 25:25
    UINT32                                         :  6;  // Bits 31:26
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM3_STRUCT;

typedef union {
  struct {
    UINT32 Signal_In_select                        :  4;  // Bits 3:0
    UINT32 Event_In_select                         :  8;  // Bits 11:4
    UINT32                                         :  8;  // Bits 19:12
    UINT32 SCT0_select                             :  1;  // Bits 20:20
    UINT32 SCT1_select                             :  1;  // Bits 21:21
    UINT32 SCT2_select                             :  1;  // Bits 22:22
    UINT32 SCT3_select                             :  1;  // Bits 23:23
    UINT32 LCT0_select                             :  1;  // Bits 24:24
    UINT32 LCT1_select                             :  1;  // Bits 25:25
    UINT32                                         :  6;  // Bits 31:26
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM4_STRUCT;

typedef union {
  struct {
    UINT32 Signal_In_select                        :  4;  // Bits 3:0
    UINT32 Event_In_select                         :  8;  // Bits 11:4
    UINT32                                         :  8;  // Bits 19:12
    UINT32 SCT0_select                             :  1;  // Bits 20:20
    UINT32 SCT1_select                             :  1;  // Bits 21:21
    UINT32 SCT2_select                             :  1;  // Bits 22:22
    UINT32 SCT3_select                             :  1;  // Bits 23:23
    UINT32 LCT0_select                             :  1;  // Bits 24:24
    UINT32 LCT1_select                             :  1;  // Bits 25:25
    UINT32                                         :  6;  // Bits 31:26
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM5_STRUCT;

typedef union {
  struct {
    UINT32 Signal_In_select                        :  4;  // Bits 3:0
    UINT32 Event_In_select                         :  8;  // Bits 11:4
    UINT32                                         :  8;  // Bits 19:12
    UINT32 SCT0_select                             :  1;  // Bits 20:20
    UINT32 SCT1_select                             :  1;  // Bits 21:21
    UINT32 SCT2_select                             :  1;  // Bits 22:22
    UINT32 SCT3_select                             :  1;  // Bits 23:23
    UINT32 LCT0_select                             :  1;  // Bits 24:24
    UINT32 LCT1_select                             :  1;  // Bits 25:25
    UINT32                                         :  6;  // Bits 31:26
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM6_STRUCT;

typedef union {
  struct {
    UINT32 Signal_In_select                        :  4;  // Bits 3:0
    UINT32 Event_In_select                         :  8;  // Bits 11:4
    UINT32                                         :  8;  // Bits 19:12
    UINT32 SCT0_select                             :  1;  // Bits 20:20
    UINT32 SCT1_select                             :  1;  // Bits 21:21
    UINT32 SCT2_select                             :  1;  // Bits 22:22
    UINT32 SCT3_select                             :  1;  // Bits 23:23
    UINT32 LCT0_select                             :  1;  // Bits 24:24
    UINT32 LCT1_select                             :  1;  // Bits 25:25
    UINT32                                         :  6;  // Bits 31:26
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM7_STRUCT;

typedef union {
  struct {
    UINT32 Signal_In_select                        :  4;  // Bits 3:0
    UINT32 Event_In_select                         :  8;  // Bits 11:4
    UINT32                                         :  8;  // Bits 19:12
    UINT32 SCT0_select                             :  1;  // Bits 20:20
    UINT32 SCT1_select                             :  1;  // Bits 21:21
    UINT32 SCT2_select                             :  1;  // Bits 22:22
    UINT32 SCT3_select                             :  1;  // Bits 23:23
    UINT32 LCT0_select                             :  1;  // Bits 24:24
    UINT32 LCT1_select                             :  1;  // Bits 25:25
    UINT32                                         :  6;  // Bits 31:26
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM8_STRUCT;

typedef union {
  struct {
    UINT32 Signal_In_select                        :  4;  // Bits 3:0
    UINT32 Event_In_select                         :  8;  // Bits 11:4
    UINT32                                         :  8;  // Bits 19:12
    UINT32 SCT0_select                             :  1;  // Bits 20:20
    UINT32 SCT1_select                             :  1;  // Bits 21:21
    UINT32 SCT2_select                             :  1;  // Bits 22:22
    UINT32 SCT3_select                             :  1;  // Bits 23:23
    UINT32 LCT0_select                             :  1;  // Bits 24:24
    UINT32 LCT1_select                             :  1;  // Bits 25:25
    UINT32                                         :  6;  // Bits 31:26
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM9_STRUCT;

typedef union {
  struct {
    UINT32 Signal_In_select                        :  4;  // Bits 3:0
    UINT32 Event_In_select                         :  8;  // Bits 11:4
    UINT32                                         :  8;  // Bits 19:12
    UINT32 SCT0_select                             :  1;  // Bits 20:20
    UINT32 SCT1_select                             :  1;  // Bits 21:21
    UINT32 SCT2_select                             :  1;  // Bits 22:22
    UINT32 SCT3_select                             :  1;  // Bits 23:23
    UINT32 LCT0_select                             :  1;  // Bits 24:24
    UINT32 LCT1_select                             :  1;  // Bits 25:25
    UINT32                                         :  6;  // Bits 31:26
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM10_STRUCT;

typedef union {
  struct {
    UINT32 Signal_In_select                        :  4;  // Bits 3:0
    UINT32 Event_In_select                         :  8;  // Bits 11:4
    UINT32                                         :  8;  // Bits 19:12
    UINT32 SCT0_select                             :  1;  // Bits 20:20
    UINT32 SCT1_select                             :  1;  // Bits 21:21
    UINT32 SCT2_select                             :  1;  // Bits 22:22
    UINT32 SCT3_select                             :  1;  // Bits 23:23
    UINT32 LCT0_select                             :  1;  // Bits 24:24
    UINT32 LCT1_select                             :  1;  // Bits 25:25
    UINT32                                         :  6;  // Bits 31:26
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM11_STRUCT;

typedef union {
  struct {
    UINT32 Signal_In_select                        :  4;  // Bits 3:0
    UINT32 Event_In_select                         :  8;  // Bits 11:4
    UINT32                                         :  8;  // Bits 19:12
    UINT32 SCT0_select                             :  1;  // Bits 20:20
    UINT32 SCT1_select                             :  1;  // Bits 21:21
    UINT32 SCT2_select                             :  1;  // Bits 22:22
    UINT32 SCT3_select                             :  1;  // Bits 23:23
    UINT32 LCT0_select                             :  1;  // Bits 24:24
    UINT32 LCT1_select                             :  1;  // Bits 25:25
    UINT32                                         :  6;  // Bits 31:26
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM12_STRUCT;

typedef union {
  struct {
    UINT32 Signal_In_select                        :  4;  // Bits 3:0
    UINT32 Event_In_select                         :  8;  // Bits 11:4
    UINT32                                         :  8;  // Bits 19:12
    UINT32 SCT0_select                             :  1;  // Bits 20:20
    UINT32 SCT1_select                             :  1;  // Bits 21:21
    UINT32 SCT2_select                             :  1;  // Bits 22:22
    UINT32 SCT3_select                             :  1;  // Bits 23:23
    UINT32 LCT0_select                             :  1;  // Bits 24:24
    UINT32 LCT1_select                             :  1;  // Bits 25:25
    UINT32                                         :  6;  // Bits 31:26
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM13_STRUCT;

typedef union {
  struct {
    UINT32 Signal_In_select                        :  4;  // Bits 3:0
    UINT32 Event_In_select                         :  8;  // Bits 11:4
    UINT32                                         :  8;  // Bits 19:12
    UINT32 SCT0_select                             :  1;  // Bits 20:20
    UINT32 SCT1_select                             :  1;  // Bits 21:21
    UINT32 SCT2_select                             :  1;  // Bits 22:22
    UINT32 SCT3_select                             :  1;  // Bits 23:23
    UINT32 LCT0_select                             :  1;  // Bits 24:24
    UINT32 LCT1_select                             :  1;  // Bits 25:25
    UINT32                                         :  6;  // Bits 31:26
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM14_STRUCT;

typedef union {
  struct {
    UINT32 Signal_In_select                        :  4;  // Bits 3:0
    UINT32 Event_In_select                         :  8;  // Bits 11:4
    UINT32                                         :  8;  // Bits 19:12
    UINT32 SCT0_select                             :  1;  // Bits 20:20
    UINT32 SCT1_select                             :  1;  // Bits 21:21
    UINT32 SCT2_select                             :  1;  // Bits 22:22
    UINT32 SCT3_select                             :  1;  // Bits 23:23
    UINT32 LCT0_select                             :  1;  // Bits 24:24
    UINT32 LCT1_select                             :  1;  // Bits 25:25
    UINT32                                         :  6;  // Bits 31:26
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM15_STRUCT;

typedef union {
  struct {
    UINT32 Set_signal_out                          :  4;  // Bits 3:0
    UINT32 Set_trig_out                            :  1;  // Bits 4:4
    UINT32 Start_storage                           :  1;  // Bits 5:5
    UINT32 Stop_storage                            :  1;  // Bits 6:6
    UINT32 SCT0_start_inc                          :  1;  // Bits 7:7
    UINT32 SCT1_start_inc                          :  1;  // Bits 8:8
    UINT32 SCT2_start_inc                          :  1;  // Bits 9:9
    UINT32 SCT3_start_inc                          :  1;  // Bits 10:10
    UINT32 LCT0_start_inc                          :  1;  // Bits 11:11
    UINT32 LCT1_start_inc                          :  1;  // Bits 12:12
    UINT32                                         :  2;  // Bits 14:13
    UINT32 LCT0_stop                               :  1;  // Bits 15:15
    UINT32 LCT1_stop                               :  1;  // Bits 16:16
    UINT32                                         :  2;  // Bits 18:17
    UINT32 SCT0_clear                              :  1;  // Bits 19:19
    UINT32 SCT1_clear                              :  1;  // Bits 20:20
    UINT32 SCT2_clear                              :  1;  // Bits 21:21
    UINT32 SCT3_clear                              :  1;  // Bits 22:22
    UINT32 LCT0_clear                              :  1;  // Bits 23:23
    UINT32 LCT1_clear                              :  1;  // Bits 24:24
    UINT32                                         :  2;  // Bits 26:25
    UINT32 Set_state                               :  4;  // Bits 30:27
    UINT32 Set_Signal_value                        :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM0_STRUCT;

typedef union {
  struct {
    UINT32 Set_signal_out                          :  4;  // Bits 3:0
    UINT32 Set_trig_out                            :  1;  // Bits 4:4
    UINT32 Start_storage                           :  1;  // Bits 5:5
    UINT32 Stop_storage                            :  1;  // Bits 6:6
    UINT32 SCT0_start_inc                          :  1;  // Bits 7:7
    UINT32 SCT1_start_inc                          :  1;  // Bits 8:8
    UINT32 SCT2_start_inc                          :  1;  // Bits 9:9
    UINT32 SCT3_start_inc                          :  1;  // Bits 10:10
    UINT32 LCT0_start_inc                          :  1;  // Bits 11:11
    UINT32 LCT1_start_inc                          :  1;  // Bits 12:12
    UINT32                                         :  2;  // Bits 14:13
    UINT32 LCT0_stop                               :  1;  // Bits 15:15
    UINT32 LCT1_stop                               :  1;  // Bits 16:16
    UINT32                                         :  2;  // Bits 18:17
    UINT32 SCT0_clear                              :  1;  // Bits 19:19
    UINT32 SCT1_clear                              :  1;  // Bits 20:20
    UINT32 SCT2_clear                              :  1;  // Bits 21:21
    UINT32 SCT3_clear                              :  1;  // Bits 22:22
    UINT32 LCT0_clear                              :  1;  // Bits 23:23
    UINT32 LCT1_clear                              :  1;  // Bits 24:24
    UINT32                                         :  2;  // Bits 26:25
    UINT32 Set_state                               :  4;  // Bits 30:27
    UINT32 Set_Signal_value                        :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM1_STRUCT;

typedef union {
  struct {
    UINT32 Set_signal_out                          :  4;  // Bits 3:0
    UINT32 Set_trig_out                            :  1;  // Bits 4:4
    UINT32 Start_storage                           :  1;  // Bits 5:5
    UINT32 Stop_storage                            :  1;  // Bits 6:6
    UINT32 SCT0_start_inc                          :  1;  // Bits 7:7
    UINT32 SCT1_start_inc                          :  1;  // Bits 8:8
    UINT32 SCT2_start_inc                          :  1;  // Bits 9:9
    UINT32 SCT3_start_inc                          :  1;  // Bits 10:10
    UINT32 LCT0_start_inc                          :  1;  // Bits 11:11
    UINT32 LCT1_start_inc                          :  1;  // Bits 12:12
    UINT32                                         :  2;  // Bits 14:13
    UINT32 LCT0_stop                               :  1;  // Bits 15:15
    UINT32 LCT1_stop                               :  1;  // Bits 16:16
    UINT32                                         :  2;  // Bits 18:17
    UINT32 SCT0_clear                              :  1;  // Bits 19:19
    UINT32 SCT1_clear                              :  1;  // Bits 20:20
    UINT32 SCT2_clear                              :  1;  // Bits 21:21
    UINT32 SCT3_clear                              :  1;  // Bits 22:22
    UINT32 LCT0_clear                              :  1;  // Bits 23:23
    UINT32 LCT1_clear                              :  1;  // Bits 24:24
    UINT32                                         :  2;  // Bits 26:25
    UINT32 Set_state                               :  4;  // Bits 30:27
    UINT32 Set_Signal_value                        :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM2_STRUCT;

typedef union {
  struct {
    UINT32 Set_signal_out                          :  4;  // Bits 3:0
    UINT32 Set_trig_out                            :  1;  // Bits 4:4
    UINT32 Start_storage                           :  1;  // Bits 5:5
    UINT32 Stop_storage                            :  1;  // Bits 6:6
    UINT32 SCT0_start_inc                          :  1;  // Bits 7:7
    UINT32 SCT1_start_inc                          :  1;  // Bits 8:8
    UINT32 SCT2_start_inc                          :  1;  // Bits 9:9
    UINT32 SCT3_start_inc                          :  1;  // Bits 10:10
    UINT32 LCT0_start_inc                          :  1;  // Bits 11:11
    UINT32 LCT1_start_inc                          :  1;  // Bits 12:12
    UINT32                                         :  2;  // Bits 14:13
    UINT32 LCT0_stop                               :  1;  // Bits 15:15
    UINT32 LCT1_stop                               :  1;  // Bits 16:16
    UINT32                                         :  2;  // Bits 18:17
    UINT32 SCT0_clear                              :  1;  // Bits 19:19
    UINT32 SCT1_clear                              :  1;  // Bits 20:20
    UINT32 SCT2_clear                              :  1;  // Bits 21:21
    UINT32 SCT3_clear                              :  1;  // Bits 22:22
    UINT32 LCT0_clear                              :  1;  // Bits 23:23
    UINT32 LCT1_clear                              :  1;  // Bits 24:24
    UINT32                                         :  2;  // Bits 26:25
    UINT32 Set_state                               :  4;  // Bits 30:27
    UINT32 Set_Signal_value                        :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM3_STRUCT;

typedef union {
  struct {
    UINT32 Set_signal_out                          :  4;  // Bits 3:0
    UINT32 Set_trig_out                            :  1;  // Bits 4:4
    UINT32 Start_storage                           :  1;  // Bits 5:5
    UINT32 Stop_storage                            :  1;  // Bits 6:6
    UINT32 SCT0_start_inc                          :  1;  // Bits 7:7
    UINT32 SCT1_start_inc                          :  1;  // Bits 8:8
    UINT32 SCT2_start_inc                          :  1;  // Bits 9:9
    UINT32 SCT3_start_inc                          :  1;  // Bits 10:10
    UINT32 LCT0_start_inc                          :  1;  // Bits 11:11
    UINT32 LCT1_start_inc                          :  1;  // Bits 12:12
    UINT32                                         :  2;  // Bits 14:13
    UINT32 LCT0_stop                               :  1;  // Bits 15:15
    UINT32 LCT1_stop                               :  1;  // Bits 16:16
    UINT32                                         :  2;  // Bits 18:17
    UINT32 SCT0_clear                              :  1;  // Bits 19:19
    UINT32 SCT1_clear                              :  1;  // Bits 20:20
    UINT32 SCT2_clear                              :  1;  // Bits 21:21
    UINT32 SCT3_clear                              :  1;  // Bits 22:22
    UINT32 LCT0_clear                              :  1;  // Bits 23:23
    UINT32 LCT1_clear                              :  1;  // Bits 24:24
    UINT32                                         :  2;  // Bits 26:25
    UINT32 Set_state                               :  4;  // Bits 30:27
    UINT32 Set_Signal_value                        :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM4_STRUCT;

typedef union {
  struct {
    UINT32 Set_signal_out                          :  4;  // Bits 3:0
    UINT32 Set_trig_out                            :  1;  // Bits 4:4
    UINT32 Start_storage                           :  1;  // Bits 5:5
    UINT32 Stop_storage                            :  1;  // Bits 6:6
    UINT32 SCT0_start_inc                          :  1;  // Bits 7:7
    UINT32 SCT1_start_inc                          :  1;  // Bits 8:8
    UINT32 SCT2_start_inc                          :  1;  // Bits 9:9
    UINT32 SCT3_start_inc                          :  1;  // Bits 10:10
    UINT32 LCT0_start_inc                          :  1;  // Bits 11:11
    UINT32 LCT1_start_inc                          :  1;  // Bits 12:12
    UINT32                                         :  2;  // Bits 14:13
    UINT32 LCT0_stop                               :  1;  // Bits 15:15
    UINT32 LCT1_stop                               :  1;  // Bits 16:16
    UINT32                                         :  2;  // Bits 18:17
    UINT32 SCT0_clear                              :  1;  // Bits 19:19
    UINT32 SCT1_clear                              :  1;  // Bits 20:20
    UINT32 SCT2_clear                              :  1;  // Bits 21:21
    UINT32 SCT3_clear                              :  1;  // Bits 22:22
    UINT32 LCT0_clear                              :  1;  // Bits 23:23
    UINT32 LCT1_clear                              :  1;  // Bits 24:24
    UINT32                                         :  2;  // Bits 26:25
    UINT32 Set_state                               :  4;  // Bits 30:27
    UINT32 Set_Signal_value                        :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM5_STRUCT;

typedef union {
  struct {
    UINT32 Set_signal_out                          :  4;  // Bits 3:0
    UINT32 Set_trig_out                            :  1;  // Bits 4:4
    UINT32 Start_storage                           :  1;  // Bits 5:5
    UINT32 Stop_storage                            :  1;  // Bits 6:6
    UINT32 SCT0_start_inc                          :  1;  // Bits 7:7
    UINT32 SCT1_start_inc                          :  1;  // Bits 8:8
    UINT32 SCT2_start_inc                          :  1;  // Bits 9:9
    UINT32 SCT3_start_inc                          :  1;  // Bits 10:10
    UINT32 LCT0_start_inc                          :  1;  // Bits 11:11
    UINT32 LCT1_start_inc                          :  1;  // Bits 12:12
    UINT32                                         :  2;  // Bits 14:13
    UINT32 LCT0_stop                               :  1;  // Bits 15:15
    UINT32 LCT1_stop                               :  1;  // Bits 16:16
    UINT32                                         :  2;  // Bits 18:17
    UINT32 SCT0_clear                              :  1;  // Bits 19:19
    UINT32 SCT1_clear                              :  1;  // Bits 20:20
    UINT32 SCT2_clear                              :  1;  // Bits 21:21
    UINT32 SCT3_clear                              :  1;  // Bits 22:22
    UINT32 LCT0_clear                              :  1;  // Bits 23:23
    UINT32 LCT1_clear                              :  1;  // Bits 24:24
    UINT32                                         :  2;  // Bits 26:25
    UINT32 Set_state                               :  4;  // Bits 30:27
    UINT32 Set_Signal_value                        :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM6_STRUCT;

typedef union {
  struct {
    UINT32 Set_signal_out                          :  4;  // Bits 3:0
    UINT32 Set_trig_out                            :  1;  // Bits 4:4
    UINT32 Start_storage                           :  1;  // Bits 5:5
    UINT32 Stop_storage                            :  1;  // Bits 6:6
    UINT32 SCT0_start_inc                          :  1;  // Bits 7:7
    UINT32 SCT1_start_inc                          :  1;  // Bits 8:8
    UINT32 SCT2_start_inc                          :  1;  // Bits 9:9
    UINT32 SCT3_start_inc                          :  1;  // Bits 10:10
    UINT32 LCT0_start_inc                          :  1;  // Bits 11:11
    UINT32 LCT1_start_inc                          :  1;  // Bits 12:12
    UINT32                                         :  2;  // Bits 14:13
    UINT32 LCT0_stop                               :  1;  // Bits 15:15
    UINT32 LCT1_stop                               :  1;  // Bits 16:16
    UINT32                                         :  2;  // Bits 18:17
    UINT32 SCT0_clear                              :  1;  // Bits 19:19
    UINT32 SCT1_clear                              :  1;  // Bits 20:20
    UINT32 SCT2_clear                              :  1;  // Bits 21:21
    UINT32 SCT3_clear                              :  1;  // Bits 22:22
    UINT32 LCT0_clear                              :  1;  // Bits 23:23
    UINT32 LCT1_clear                              :  1;  // Bits 24:24
    UINT32                                         :  2;  // Bits 26:25
    UINT32 Set_state                               :  4;  // Bits 30:27
    UINT32 Set_Signal_value                        :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM7_STRUCT;

typedef union {
  struct {
    UINT32 Set_signal_out                          :  4;  // Bits 3:0
    UINT32 Set_trig_out                            :  1;  // Bits 4:4
    UINT32 Start_storage                           :  1;  // Bits 5:5
    UINT32 Stop_storage                            :  1;  // Bits 6:6
    UINT32 SCT0_start_inc                          :  1;  // Bits 7:7
    UINT32 SCT1_start_inc                          :  1;  // Bits 8:8
    UINT32 SCT2_start_inc                          :  1;  // Bits 9:9
    UINT32 SCT3_start_inc                          :  1;  // Bits 10:10
    UINT32 LCT0_start_inc                          :  1;  // Bits 11:11
    UINT32 LCT1_start_inc                          :  1;  // Bits 12:12
    UINT32                                         :  2;  // Bits 14:13
    UINT32 LCT0_stop                               :  1;  // Bits 15:15
    UINT32 LCT1_stop                               :  1;  // Bits 16:16
    UINT32                                         :  2;  // Bits 18:17
    UINT32 SCT0_clear                              :  1;  // Bits 19:19
    UINT32 SCT1_clear                              :  1;  // Bits 20:20
    UINT32 SCT2_clear                              :  1;  // Bits 21:21
    UINT32 SCT3_clear                              :  1;  // Bits 22:22
    UINT32 LCT0_clear                              :  1;  // Bits 23:23
    UINT32 LCT1_clear                              :  1;  // Bits 24:24
    UINT32                                         :  2;  // Bits 26:25
    UINT32 Set_state                               :  4;  // Bits 30:27
    UINT32 Set_Signal_value                        :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM8_STRUCT;

typedef union {
  struct {
    UINT32 Set_signal_out                          :  4;  // Bits 3:0
    UINT32 Set_trig_out                            :  1;  // Bits 4:4
    UINT32 Start_storage                           :  1;  // Bits 5:5
    UINT32 Stop_storage                            :  1;  // Bits 6:6
    UINT32 SCT0_start_inc                          :  1;  // Bits 7:7
    UINT32 SCT1_start_inc                          :  1;  // Bits 8:8
    UINT32 SCT2_start_inc                          :  1;  // Bits 9:9
    UINT32 SCT3_start_inc                          :  1;  // Bits 10:10
    UINT32 LCT0_start_inc                          :  1;  // Bits 11:11
    UINT32 LCT1_start_inc                          :  1;  // Bits 12:12
    UINT32                                         :  2;  // Bits 14:13
    UINT32 LCT0_stop                               :  1;  // Bits 15:15
    UINT32 LCT1_stop                               :  1;  // Bits 16:16
    UINT32                                         :  2;  // Bits 18:17
    UINT32 SCT0_clear                              :  1;  // Bits 19:19
    UINT32 SCT1_clear                              :  1;  // Bits 20:20
    UINT32 SCT2_clear                              :  1;  // Bits 21:21
    UINT32 SCT3_clear                              :  1;  // Bits 22:22
    UINT32 LCT0_clear                              :  1;  // Bits 23:23
    UINT32 LCT1_clear                              :  1;  // Bits 24:24
    UINT32                                         :  2;  // Bits 26:25
    UINT32 Set_state                               :  4;  // Bits 30:27
    UINT32 Set_Signal_value                        :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM9_STRUCT;

typedef union {
  struct {
    UINT32 Set_signal_out                          :  4;  // Bits 3:0
    UINT32 Set_trig_out                            :  1;  // Bits 4:4
    UINT32 Start_storage                           :  1;  // Bits 5:5
    UINT32 Stop_storage                            :  1;  // Bits 6:6
    UINT32 SCT0_start_inc                          :  1;  // Bits 7:7
    UINT32 SCT1_start_inc                          :  1;  // Bits 8:8
    UINT32 SCT2_start_inc                          :  1;  // Bits 9:9
    UINT32 SCT3_start_inc                          :  1;  // Bits 10:10
    UINT32 LCT0_start_inc                          :  1;  // Bits 11:11
    UINT32 LCT1_start_inc                          :  1;  // Bits 12:12
    UINT32                                         :  2;  // Bits 14:13
    UINT32 LCT0_stop                               :  1;  // Bits 15:15
    UINT32 LCT1_stop                               :  1;  // Bits 16:16
    UINT32                                         :  2;  // Bits 18:17
    UINT32 SCT0_clear                              :  1;  // Bits 19:19
    UINT32 SCT1_clear                              :  1;  // Bits 20:20
    UINT32 SCT2_clear                              :  1;  // Bits 21:21
    UINT32 SCT3_clear                              :  1;  // Bits 22:22
    UINT32 LCT0_clear                              :  1;  // Bits 23:23
    UINT32 LCT1_clear                              :  1;  // Bits 24:24
    UINT32                                         :  2;  // Bits 26:25
    UINT32 Set_state                               :  4;  // Bits 30:27
    UINT32 Set_Signal_value                        :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM10_STRUCT;

typedef union {
  struct {
    UINT32 Set_signal_out                          :  4;  // Bits 3:0
    UINT32 Set_trig_out                            :  1;  // Bits 4:4
    UINT32 Start_storage                           :  1;  // Bits 5:5
    UINT32 Stop_storage                            :  1;  // Bits 6:6
    UINT32 SCT0_start_inc                          :  1;  // Bits 7:7
    UINT32 SCT1_start_inc                          :  1;  // Bits 8:8
    UINT32 SCT2_start_inc                          :  1;  // Bits 9:9
    UINT32 SCT3_start_inc                          :  1;  // Bits 10:10
    UINT32 LCT0_start_inc                          :  1;  // Bits 11:11
    UINT32 LCT1_start_inc                          :  1;  // Bits 12:12
    UINT32                                         :  2;  // Bits 14:13
    UINT32 LCT0_stop                               :  1;  // Bits 15:15
    UINT32 LCT1_stop                               :  1;  // Bits 16:16
    UINT32                                         :  2;  // Bits 18:17
    UINT32 SCT0_clear                              :  1;  // Bits 19:19
    UINT32 SCT1_clear                              :  1;  // Bits 20:20
    UINT32 SCT2_clear                              :  1;  // Bits 21:21
    UINT32 SCT3_clear                              :  1;  // Bits 22:22
    UINT32 LCT0_clear                              :  1;  // Bits 23:23
    UINT32 LCT1_clear                              :  1;  // Bits 24:24
    UINT32                                         :  2;  // Bits 26:25
    UINT32 Set_state                               :  4;  // Bits 30:27
    UINT32 Set_Signal_value                        :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM11_STRUCT;

typedef union {
  struct {
    UINT32 Set_signal_out                          :  4;  // Bits 3:0
    UINT32 Set_trig_out                            :  1;  // Bits 4:4
    UINT32 Start_storage                           :  1;  // Bits 5:5
    UINT32 Stop_storage                            :  1;  // Bits 6:6
    UINT32 SCT0_start_inc                          :  1;  // Bits 7:7
    UINT32 SCT1_start_inc                          :  1;  // Bits 8:8
    UINT32 SCT2_start_inc                          :  1;  // Bits 9:9
    UINT32 SCT3_start_inc                          :  1;  // Bits 10:10
    UINT32 LCT0_start_inc                          :  1;  // Bits 11:11
    UINT32 LCT1_start_inc                          :  1;  // Bits 12:12
    UINT32                                         :  2;  // Bits 14:13
    UINT32 LCT0_stop                               :  1;  // Bits 15:15
    UINT32 LCT1_stop                               :  1;  // Bits 16:16
    UINT32                                         :  2;  // Bits 18:17
    UINT32 SCT0_clear                              :  1;  // Bits 19:19
    UINT32 SCT1_clear                              :  1;  // Bits 20:20
    UINT32 SCT2_clear                              :  1;  // Bits 21:21
    UINT32 SCT3_clear                              :  1;  // Bits 22:22
    UINT32 LCT0_clear                              :  1;  // Bits 23:23
    UINT32 LCT1_clear                              :  1;  // Bits 24:24
    UINT32                                         :  2;  // Bits 26:25
    UINT32 Set_state                               :  4;  // Bits 30:27
    UINT32 Set_Signal_value                        :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM12_STRUCT;

typedef union {
  struct {
    UINT32 Set_signal_out                          :  4;  // Bits 3:0
    UINT32 Set_trig_out                            :  1;  // Bits 4:4
    UINT32 Start_storage                           :  1;  // Bits 5:5
    UINT32 Stop_storage                            :  1;  // Bits 6:6
    UINT32 SCT0_start_inc                          :  1;  // Bits 7:7
    UINT32 SCT1_start_inc                          :  1;  // Bits 8:8
    UINT32 SCT2_start_inc                          :  1;  // Bits 9:9
    UINT32 SCT3_start_inc                          :  1;  // Bits 10:10
    UINT32 LCT0_start_inc                          :  1;  // Bits 11:11
    UINT32 LCT1_start_inc                          :  1;  // Bits 12:12
    UINT32                                         :  2;  // Bits 14:13
    UINT32 LCT0_stop                               :  1;  // Bits 15:15
    UINT32 LCT1_stop                               :  1;  // Bits 16:16
    UINT32                                         :  2;  // Bits 18:17
    UINT32 SCT0_clear                              :  1;  // Bits 19:19
    UINT32 SCT1_clear                              :  1;  // Bits 20:20
    UINT32 SCT2_clear                              :  1;  // Bits 21:21
    UINT32 SCT3_clear                              :  1;  // Bits 22:22
    UINT32 LCT0_clear                              :  1;  // Bits 23:23
    UINT32 LCT1_clear                              :  1;  // Bits 24:24
    UINT32                                         :  2;  // Bits 26:25
    UINT32 Set_state                               :  4;  // Bits 30:27
    UINT32 Set_Signal_value                        :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM13_STRUCT;

typedef union {
  struct {
    UINT32 Set_signal_out                          :  4;  // Bits 3:0
    UINT32 Set_trig_out                            :  1;  // Bits 4:4
    UINT32 Start_storage                           :  1;  // Bits 5:5
    UINT32 Stop_storage                            :  1;  // Bits 6:6
    UINT32 SCT0_start_inc                          :  1;  // Bits 7:7
    UINT32 SCT1_start_inc                          :  1;  // Bits 8:8
    UINT32 SCT2_start_inc                          :  1;  // Bits 9:9
    UINT32 SCT3_start_inc                          :  1;  // Bits 10:10
    UINT32 LCT0_start_inc                          :  1;  // Bits 11:11
    UINT32 LCT1_start_inc                          :  1;  // Bits 12:12
    UINT32                                         :  2;  // Bits 14:13
    UINT32 LCT0_stop                               :  1;  // Bits 15:15
    UINT32 LCT1_stop                               :  1;  // Bits 16:16
    UINT32                                         :  2;  // Bits 18:17
    UINT32 SCT0_clear                              :  1;  // Bits 19:19
    UINT32 SCT1_clear                              :  1;  // Bits 20:20
    UINT32 SCT2_clear                              :  1;  // Bits 21:21
    UINT32 SCT3_clear                              :  1;  // Bits 22:22
    UINT32 LCT0_clear                              :  1;  // Bits 23:23
    UINT32 LCT1_clear                              :  1;  // Bits 24:24
    UINT32                                         :  2;  // Bits 26:25
    UINT32 Set_state                               :  4;  // Bits 30:27
    UINT32 Set_Signal_value                        :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM14_STRUCT;

typedef union {
  struct {
    UINT32 Set_signal_out                          :  4;  // Bits 3:0
    UINT32 Set_trig_out                            :  1;  // Bits 4:4
    UINT32 Start_storage                           :  1;  // Bits 5:5
    UINT32 Stop_storage                            :  1;  // Bits 6:6
    UINT32 SCT0_start_inc                          :  1;  // Bits 7:7
    UINT32 SCT1_start_inc                          :  1;  // Bits 8:8
    UINT32 SCT2_start_inc                          :  1;  // Bits 9:9
    UINT32 SCT3_start_inc                          :  1;  // Bits 10:10
    UINT32 LCT0_start_inc                          :  1;  // Bits 11:11
    UINT32 LCT1_start_inc                          :  1;  // Bits 12:12
    UINT32                                         :  2;  // Bits 14:13
    UINT32 LCT0_stop                               :  1;  // Bits 15:15
    UINT32 LCT1_stop                               :  1;  // Bits 16:16
    UINT32                                         :  2;  // Bits 18:17
    UINT32 SCT0_clear                              :  1;  // Bits 19:19
    UINT32 SCT1_clear                              :  1;  // Bits 20:20
    UINT32 SCT2_clear                              :  1;  // Bits 21:21
    UINT32 SCT3_clear                              :  1;  // Bits 22:22
    UINT32 LCT0_clear                              :  1;  // Bits 23:23
    UINT32 LCT1_clear                              :  1;  // Bits 24:24
    UINT32                                         :  2;  // Bits 26:25
    UINT32 Set_state                               :  4;  // Bits 30:27
    UINT32 Set_Signal_value                        :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM15_STRUCT;

typedef union {
  struct {
    UINT32 SCT0_match_value                        :  20;  // Bits 19:0
    UINT32 SCT0_Mode                               :  1;  // Bits 20:20
    UINT32 SCT0_Timebase                           :  1;  // Bits 21:21
    UINT32 SCT0_Mode1                              :  1;  // Bits 22:22
    UINT32 SCT0_EventSel                           :  4;  // Bits 26:23
    UINT32                                         :  5;  // Bits 31:27
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRPL_CR_DDR_SCT0_CONTROL_STRUCT;

typedef union {
  struct {
    UINT32 SCT1_match_value                        :  20;  // Bits 19:0
    UINT32 SCT1_Mode                               :  1;  // Bits 20:20
    UINT32 SCT1_Timebase                           :  1;  // Bits 21:21
    UINT32 SCT1_Mode1                              :  1;  // Bits 22:22
    UINT32 SCT1_EventSel                           :  4;  // Bits 26:23
    UINT32                                         :  5;  // Bits 31:27
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRPL_CR_DDR_SCT1_CONTROL_STRUCT;

typedef union {
  struct {
    UINT32 SCT2_match_value                        :  20;  // Bits 19:0
    UINT32 SCT2_Mode                               :  1;  // Bits 20:20
    UINT32 SCT2_Timebase                           :  1;  // Bits 21:21
    UINT32 SCT2_Mode1                              :  1;  // Bits 22:22
    UINT32 SCT2_EventSel                           :  4;  // Bits 26:23
    UINT32                                         :  5;  // Bits 31:27
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRPL_CR_DDR_SCT2_CONTROL_STRUCT;

typedef union {
  struct {
    UINT32 SCT3_match_value                        :  20;  // Bits 19:0
    UINT32 SCT3_Mode                               :  1;  // Bits 20:20
    UINT32 SCT3_Timebase                           :  1;  // Bits 21:21
    UINT32 SCT3_Mode1                              :  1;  // Bits 22:22
    UINT32 SCT3_EventSel                           :  4;  // Bits 26:23
    UINT32                                         :  5;  // Bits 31:27
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRPL_CR_DDR_SCT3_CONTROL_STRUCT;

typedef union {
  struct {
    UINT32 LCT0_match_value                        :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRPL_CR_DDR_LCT0_LOWER_CONTROL_STRUCT;

typedef union {
  struct {
    UINT32 LCT0_match_value                        :  13;  // Bits 12:0
    UINT32 LCT0_Mode                               :  1;  // Bits 13:13
    UINT32 LCT0_Timebase                           :  1;  // Bits 14:14
    UINT32 LCT0_Mode1                              :  1;  // Bits 15:15
    UINT32                                         :  16;  // Bits 31:16
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRPL_CR_DDR_LCT0_UPPER_CONTROL_STRUCT;

typedef union {
  struct {
    UINT32 LCT1_match_value                        :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRPL_CR_DDR_LCT1_LOWER_CONTROL_STRUCT;

typedef union {
  struct {
    UINT32 LCT1_match_value                        :  13;  // Bits 12:0
    UINT32 LCT1_Mode                               :  1;  // Bits 13:13
    UINT32 LCT1_Timebase                           :  1;  // Bits 14:14
    UINT32 LCT1_Mode1                              :  1;  // Bits 15:15
    UINT32                                         :  16;  // Bits 31:16
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRPL_CR_DDR_LCT1_UPPER_CONTROL_STRUCT;

typedef union {
  struct {
    UINT32 SCT0_current_value                      :  20;  // Bits 19:0
    UINT32 SCT0_Running                            :  1;  // Bits 20:20
    UINT32                                         :  11;  // Bits 31:21
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRPL_CR_DDR_SCT0_CURRENT_STATUS_STRUCT;

typedef union {
  struct {
    UINT32 SCT1_current_value                      :  20;  // Bits 19:0
    UINT32 SCT1_Running                            :  1;  // Bits 20:20
    UINT32                                         :  11;  // Bits 31:21
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRPL_CR_DDR_SCT1_CURRENT_STATUS_STRUCT;

typedef union {
  struct {
    UINT32 SCT2_current_value                      :  20;  // Bits 19:0
    UINT32 SCT2_Running                            :  1;  // Bits 20:20
    UINT32                                         :  11;  // Bits 31:21
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRPL_CR_DDR_SCT2_CURRENT_STATUS_STRUCT;

typedef union {
  struct {
    UINT32 SCT3_current_value                      :  20;  // Bits 19:0
    UINT32 SCT3_Running                            :  1;  // Bits 20:20
    UINT32                                         :  11;  // Bits 31:21
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRPL_CR_DDR_SCT3_CURRENT_STATUS_STRUCT;

typedef union {
  struct {
    UINT32 LCT0_current_value                      :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRPL_CR_DDR_LCT0_LOWER_CURRENT_STATUS_STRUCT;

typedef union {
  struct {
    UINT32 LCT0_current_value                      :  13;  // Bits 12:0
    UINT32 LCT0_Running                            :  1;  // Bits 13:13
    UINT32                                         :  18;  // Bits 31:14
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRPL_CR_DDR_LCT0_UPPER_CURRENT_STATUS_STRUCT;

typedef union {
  struct {
    UINT32 LCT1_current_value                      :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRPL_CR_DDR_LCT1_LOWER_CURRENT_STATUS_STRUCT;

typedef union {
  struct {
    UINT32 LCT1_current_value                      :  13;  // Bits 12:0
    UINT32 LCT1_Running                            :  1;  // Bits 13:13
    UINT32                                         :  18;  // Bits 31:14
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRPL_CR_DDR_LCT1_UPPER_CURRENT_STATUS_STRUCT;

typedef union {
  struct {
    UINT32 Sequencer_State                         :  4;  // Bits 3:0
    UINT32 Sequencer_Trig                          :  1;  // Bits 4:4
    UINT32 Stor_Qual_Initial_Value                 :  1;  // Bits 5:5
    UINT32 Signal_Out_Status                       :  4;  // Bits 9:6
    UINT32 CTS_Revision                            :  3;  // Bits 12:10
    UINT32 CTS_Pipelined                           :  1;  // Bits 13:13
    UINT32                                         :  2;  // Bits 15:14
    UINT32 Stor_Qual_Initial_Value1                :  7;  // Bits 22:16
    UINT32                                         :  9;  // Bits 31:23
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRPL_CR_DDR_CTS_STATUS_STRUCT;

typedef union {
  struct {
    UINT32 Sequencer_Enable                        :  1;  // Bits 0:0
    UINT32 Event_In_edge_det                       :  16;  // Bits 16:1
    UINT32 Force_State                             :  1;  // Bits 17:17
    UINT32 Update_Status                           :  1;  // Bits 18:18
    UINT32 Signal_In_edge_det                      :  1;  // Bits 19:19
    UINT32 Signal_Out_mode                         :  2;  // Bits 21:20
    UINT32                                         :  9;  // Bits 30:22
    UINT32 CTS_triggered_once                      :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRPL_CR_DDR_CTS_CONTROL_STRUCT;

typedef union {
  struct {
    UINT32 Num_Stor_Qual                           :  3;  // Bits 2:0
    UINT32 Peak_Timer_Selected                     :  1;  // Bits 3:3
    UINT32 LCT_Size                                :  6;  // Bits 9:4
    UINT32 NUM_LCTs                                :  3;  // Bits 12:10
    UINT32 NUM_SCTs                                :  3;  // Bits 15:13
    UINT32 NUM_Signals                             :  2;  // Bits 17:16
    UINT32 NUM_Events                              :  4;  // Bits 21:18
    UINT32 NUM_Clauses                             :  3;  // Bits 24:22
    UINT32 NUM_States                              :  3;  // Bits 27:25
    UINT32                                         :  4;  // Bits 31:28
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRPL_CR_DDR_PARAMETER_STATUS_STRUCT;

typedef union {
  struct {
    UINT32 Reserved                                :  1;  // Bits 0:0
    UINT32                                         :  31;  // Bits 31:1
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRPL_CR_DDR_CTS_FW_UPDATE_STATUS_STRUCT;


#define MPCOHTRK_CR_GDXC_SW_UCLK_SRC_CFG_REG                         (0x00000000)
  #define MPCOHTRK_CR_GDXC_SW_UCLK_SRC_CFG_EN_RING_ADQ_OFF             ( 1)
  #define MPCOHTRK_CR_GDXC_SW_UCLK_SRC_CFG_EN_RING_ADQ_WID             ( 1)
  #define MPCOHTRK_CR_GDXC_SW_UCLK_SRC_CFG_EN_RING_ADQ_MSK             (0x00000002)
  #define MPCOHTRK_CR_GDXC_SW_UCLK_SRC_CFG_EN_RING_ADQ_MAX             (0x00000001)
  #define MPCOHTRK_CR_GDXC_SW_UCLK_SRC_CFG_EN_RING_ADQ_DEF             (0x00000001)
  #define MPCOHTRK_CR_GDXC_SW_UCLK_SRC_CFG_EN_RING_BLQ_OFF             ( 2)
  #define MPCOHTRK_CR_GDXC_SW_UCLK_SRC_CFG_EN_RING_BLQ_WID             ( 1)
  #define MPCOHTRK_CR_GDXC_SW_UCLK_SRC_CFG_EN_RING_BLQ_MSK             (0x00000004)
  #define MPCOHTRK_CR_GDXC_SW_UCLK_SRC_CFG_EN_RING_BLQ_MAX             (0x00000001)
  #define MPCOHTRK_CR_GDXC_SW_UCLK_SRC_CFG_EN_RING_BLQ_DEF             (0x00000001)
  #define MPCOHTRK_CR_GDXC_SW_UCLK_SRC_CFG_EN_RING_AKQ_OFF             ( 3)
  #define MPCOHTRK_CR_GDXC_SW_UCLK_SRC_CFG_EN_RING_AKQ_WID             ( 1)
  #define MPCOHTRK_CR_GDXC_SW_UCLK_SRC_CFG_EN_RING_AKQ_MSK             (0x00000008)
  #define MPCOHTRK_CR_GDXC_SW_UCLK_SRC_CFG_EN_RING_AKQ_MAX             (0x00000001)
  #define MPCOHTRK_CR_GDXC_SW_UCLK_SRC_CFG_EN_RING_AKQ_DEF             (0x00000001)
  #define MPCOHTRK_CR_GDXC_SW_UCLK_SRC_CFG_EN_RING_IVQ_OFF             ( 4)
  #define MPCOHTRK_CR_GDXC_SW_UCLK_SRC_CFG_EN_RING_IVQ_WID             ( 1)
  #define MPCOHTRK_CR_GDXC_SW_UCLK_SRC_CFG_EN_RING_IVQ_MSK             (0x00000010)
  #define MPCOHTRK_CR_GDXC_SW_UCLK_SRC_CFG_EN_RING_IVQ_MAX             (0x00000001)
  #define MPCOHTRK_CR_GDXC_SW_UCLK_SRC_CFG_EN_RING_IVQ_DEF             (0x00000001)
  #define MPCOHTRK_CR_GDXC_SW_UCLK_SRC_CFG_EN_IDIQ_OFF                 ( 5)
  #define MPCOHTRK_CR_GDXC_SW_UCLK_SRC_CFG_EN_IDIQ_WID                 ( 1)
  #define MPCOHTRK_CR_GDXC_SW_UCLK_SRC_CFG_EN_IDIQ_MSK                 (0x00000020)
  #define MPCOHTRK_CR_GDXC_SW_UCLK_SRC_CFG_EN_IDIQ_MAX                 (0x00000001)
  #define MPCOHTRK_CR_GDXC_SW_UCLK_SRC_CFG_EN_IDIQ_DEF                 (0x00000000)
  #define MPCOHTRK_CR_GDXC_SW_UCLK_SRC_CFG_EN_mc_UCLKQ_OFF             ( 6)
  #define MPCOHTRK_CR_GDXC_SW_UCLK_SRC_CFG_EN_mc_UCLKQ_WID             ( 1)
  #define MPCOHTRK_CR_GDXC_SW_UCLK_SRC_CFG_EN_mc_UCLKQ_MSK             (0x00000040)
  #define MPCOHTRK_CR_GDXC_SW_UCLK_SRC_CFG_EN_mc_UCLKQ_MAX             (0x00000001)
  #define MPCOHTRK_CR_GDXC_SW_UCLK_SRC_CFG_EN_mc_UCLKQ_DEF             (0x00000001)
  #define MPCOHTRK_CR_GDXC_SW_UCLK_SRC_CFG_UP_EN_ADQ_OFF               ( 8)
  #define MPCOHTRK_CR_GDXC_SW_UCLK_SRC_CFG_UP_EN_ADQ_WID               ( 1)
  #define MPCOHTRK_CR_GDXC_SW_UCLK_SRC_CFG_UP_EN_ADQ_MSK               (0x00000100)
  #define MPCOHTRK_CR_GDXC_SW_UCLK_SRC_CFG_UP_EN_ADQ_MAX               (0x00000001)
  #define MPCOHTRK_CR_GDXC_SW_UCLK_SRC_CFG_UP_EN_ADQ_DEF               (0x00000001)
  #define MPCOHTRK_CR_GDXC_SW_UCLK_SRC_CFG_DN_EN_ADQ_OFF               ( 9)
  #define MPCOHTRK_CR_GDXC_SW_UCLK_SRC_CFG_DN_EN_ADQ_WID               ( 1)
  #define MPCOHTRK_CR_GDXC_SW_UCLK_SRC_CFG_DN_EN_ADQ_MSK               (0x00000200)
  #define MPCOHTRK_CR_GDXC_SW_UCLK_SRC_CFG_DN_EN_ADQ_MAX               (0x00000001)
  #define MPCOHTRK_CR_GDXC_SW_UCLK_SRC_CFG_DN_EN_ADQ_DEF               (0x00000001)
  #define MPCOHTRK_CR_GDXC_SW_UCLK_SRC_CFG_UP_EN_BLQ_OFF               (10)
  #define MPCOHTRK_CR_GDXC_SW_UCLK_SRC_CFG_UP_EN_BLQ_WID               ( 1)
  #define MPCOHTRK_CR_GDXC_SW_UCLK_SRC_CFG_UP_EN_BLQ_MSK               (0x00000400)
  #define MPCOHTRK_CR_GDXC_SW_UCLK_SRC_CFG_UP_EN_BLQ_MAX               (0x00000001)
  #define MPCOHTRK_CR_GDXC_SW_UCLK_SRC_CFG_UP_EN_BLQ_DEF               (0x00000001)
  #define MPCOHTRK_CR_GDXC_SW_UCLK_SRC_CFG_DN_EN_BLQ_OFF               (11)
  #define MPCOHTRK_CR_GDXC_SW_UCLK_SRC_CFG_DN_EN_BLQ_WID               ( 1)
  #define MPCOHTRK_CR_GDXC_SW_UCLK_SRC_CFG_DN_EN_BLQ_MSK               (0x00000800)
  #define MPCOHTRK_CR_GDXC_SW_UCLK_SRC_CFG_DN_EN_BLQ_MAX               (0x00000001)
  #define MPCOHTRK_CR_GDXC_SW_UCLK_SRC_CFG_DN_EN_BLQ_DEF               (0x00000001)
  #define MPCOHTRK_CR_GDXC_SW_UCLK_SRC_CFG_UP_EN_AKQ_OFF               (12)
  #define MPCOHTRK_CR_GDXC_SW_UCLK_SRC_CFG_UP_EN_AKQ_WID               ( 1)
  #define MPCOHTRK_CR_GDXC_SW_UCLK_SRC_CFG_UP_EN_AKQ_MSK               (0x00001000)
  #define MPCOHTRK_CR_GDXC_SW_UCLK_SRC_CFG_UP_EN_AKQ_MAX               (0x00000001)
  #define MPCOHTRK_CR_GDXC_SW_UCLK_SRC_CFG_UP_EN_AKQ_DEF               (0x00000001)
  #define MPCOHTRK_CR_GDXC_SW_UCLK_SRC_CFG_DN_EN_AKQ_OFF               (13)
  #define MPCOHTRK_CR_GDXC_SW_UCLK_SRC_CFG_DN_EN_AKQ_WID               ( 1)
  #define MPCOHTRK_CR_GDXC_SW_UCLK_SRC_CFG_DN_EN_AKQ_MSK               (0x00002000)
  #define MPCOHTRK_CR_GDXC_SW_UCLK_SRC_CFG_DN_EN_AKQ_MAX               (0x00000001)
  #define MPCOHTRK_CR_GDXC_SW_UCLK_SRC_CFG_DN_EN_AKQ_DEF               (0x00000001)
  #define MPCOHTRK_CR_GDXC_SW_UCLK_SRC_CFG_MOTQ_TIMING_SELECT_OFF      (14)
  #define MPCOHTRK_CR_GDXC_SW_UCLK_SRC_CFG_MOTQ_TIMING_SELECT_WID      ( 1)
  #define MPCOHTRK_CR_GDXC_SW_UCLK_SRC_CFG_MOTQ_TIMING_SELECT_MSK      (0x00004000)
  #define MPCOHTRK_CR_GDXC_SW_UCLK_SRC_CFG_MOTQ_TIMING_SELECT_MAX      (0x00000001)
  #define MPCOHTRK_CR_GDXC_SW_UCLK_SRC_CFG_MOTQ_TIMING_SELECT_DEF      (0x00000000)
  #define MPCOHTRK_CR_GDXC_SW_UCLK_SRC_CFG_SPARE_OFF                   (15)
  #define MPCOHTRK_CR_GDXC_SW_UCLK_SRC_CFG_SPARE_WID                   ( 5)
  #define MPCOHTRK_CR_GDXC_SW_UCLK_SRC_CFG_SPARE_MSK                   (0x000F8000)
  #define MPCOHTRK_CR_GDXC_SW_UCLK_SRC_CFG_SPARE_MAX                   (0x0000001F)
  #define MPCOHTRK_CR_GDXC_SW_UCLK_SRC_CFG_SPARE_DEF                   (0x00000000)

#define MPCOHTRK_CR_GDXC_QUALIFIER_GLOBAL_REG                        (0x00000004)
  #define MPCOHTRK_CR_GDXC_QUALIFIER_GLOBAL_EN_Core0_T0_OFF            ( 0)
  #define MPCOHTRK_CR_GDXC_QUALIFIER_GLOBAL_EN_Core0_T0_WID            ( 1)
  #define MPCOHTRK_CR_GDXC_QUALIFIER_GLOBAL_EN_Core0_T0_MSK            (0x00000001)
  #define MPCOHTRK_CR_GDXC_QUALIFIER_GLOBAL_EN_Core0_T0_MAX            (0x00000001)
  #define MPCOHTRK_CR_GDXC_QUALIFIER_GLOBAL_EN_Core0_T0_DEF            (0x00000001)
  #define MPCOHTRK_CR_GDXC_QUALIFIER_GLOBAL_EN_Core0_T1_OFF            ( 1)
  #define MPCOHTRK_CR_GDXC_QUALIFIER_GLOBAL_EN_Core0_T1_WID            ( 1)
  #define MPCOHTRK_CR_GDXC_QUALIFIER_GLOBAL_EN_Core0_T1_MSK            (0x00000002)
  #define MPCOHTRK_CR_GDXC_QUALIFIER_GLOBAL_EN_Core0_T1_MAX            (0x00000001)
  #define MPCOHTRK_CR_GDXC_QUALIFIER_GLOBAL_EN_Core0_T1_DEF            (0x00000001)
  #define MPCOHTRK_CR_GDXC_QUALIFIER_GLOBAL_EN_Core1_T0_OFF            ( 2)
  #define MPCOHTRK_CR_GDXC_QUALIFIER_GLOBAL_EN_Core1_T0_WID            ( 1)
  #define MPCOHTRK_CR_GDXC_QUALIFIER_GLOBAL_EN_Core1_T0_MSK            (0x00000004)
  #define MPCOHTRK_CR_GDXC_QUALIFIER_GLOBAL_EN_Core1_T0_MAX            (0x00000001)
  #define MPCOHTRK_CR_GDXC_QUALIFIER_GLOBAL_EN_Core1_T0_DEF            (0x00000001)
  #define MPCOHTRK_CR_GDXC_QUALIFIER_GLOBAL_EN_Core1_T1_OFF            ( 3)
  #define MPCOHTRK_CR_GDXC_QUALIFIER_GLOBAL_EN_Core1_T1_WID            ( 1)
  #define MPCOHTRK_CR_GDXC_QUALIFIER_GLOBAL_EN_Core1_T1_MSK            (0x00000008)
  #define MPCOHTRK_CR_GDXC_QUALIFIER_GLOBAL_EN_Core1_T1_MAX            (0x00000001)
  #define MPCOHTRK_CR_GDXC_QUALIFIER_GLOBAL_EN_Core1_T1_DEF            (0x00000001)
  #define MPCOHTRK_CR_GDXC_QUALIFIER_GLOBAL_EN_Core2_T0_OFF            ( 4)
  #define MPCOHTRK_CR_GDXC_QUALIFIER_GLOBAL_EN_Core2_T0_WID            ( 1)
  #define MPCOHTRK_CR_GDXC_QUALIFIER_GLOBAL_EN_Core2_T0_MSK            (0x00000010)
  #define MPCOHTRK_CR_GDXC_QUALIFIER_GLOBAL_EN_Core2_T0_MAX            (0x00000001)
  #define MPCOHTRK_CR_GDXC_QUALIFIER_GLOBAL_EN_Core2_T0_DEF            (0x00000001)
  #define MPCOHTRK_CR_GDXC_QUALIFIER_GLOBAL_EN_Core2_T1_OFF            ( 5)
  #define MPCOHTRK_CR_GDXC_QUALIFIER_GLOBAL_EN_Core2_T1_WID            ( 1)
  #define MPCOHTRK_CR_GDXC_QUALIFIER_GLOBAL_EN_Core2_T1_MSK            (0x00000020)
  #define MPCOHTRK_CR_GDXC_QUALIFIER_GLOBAL_EN_Core2_T1_MAX            (0x00000001)
  #define MPCOHTRK_CR_GDXC_QUALIFIER_GLOBAL_EN_Core2_T1_DEF            (0x00000001)
  #define MPCOHTRK_CR_GDXC_QUALIFIER_GLOBAL_EN_Core3_T0_OFF            ( 6)
  #define MPCOHTRK_CR_GDXC_QUALIFIER_GLOBAL_EN_Core3_T0_WID            ( 1)
  #define MPCOHTRK_CR_GDXC_QUALIFIER_GLOBAL_EN_Core3_T0_MSK            (0x00000040)
  #define MPCOHTRK_CR_GDXC_QUALIFIER_GLOBAL_EN_Core3_T0_MAX            (0x00000001)
  #define MPCOHTRK_CR_GDXC_QUALIFIER_GLOBAL_EN_Core3_T0_DEF            (0x00000001)
  #define MPCOHTRK_CR_GDXC_QUALIFIER_GLOBAL_EN_Core3_T1_OFF            ( 7)
  #define MPCOHTRK_CR_GDXC_QUALIFIER_GLOBAL_EN_Core3_T1_WID            ( 1)
  #define MPCOHTRK_CR_GDXC_QUALIFIER_GLOBAL_EN_Core3_T1_MSK            (0x00000080)
  #define MPCOHTRK_CR_GDXC_QUALIFIER_GLOBAL_EN_Core3_T1_MAX            (0x00000001)
  #define MPCOHTRK_CR_GDXC_QUALIFIER_GLOBAL_EN_Core3_T1_DEF            (0x00000001)
  #define MPCOHTRK_CR_GDXC_QUALIFIER_GLOBAL_EN_GT_OFF                  ( 8)
  #define MPCOHTRK_CR_GDXC_QUALIFIER_GLOBAL_EN_GT_WID                  ( 1)
  #define MPCOHTRK_CR_GDXC_QUALIFIER_GLOBAL_EN_GT_MSK                  (0x00000100)
  #define MPCOHTRK_CR_GDXC_QUALIFIER_GLOBAL_EN_GT_MAX                  (0x00000001)
  #define MPCOHTRK_CR_GDXC_QUALIFIER_GLOBAL_EN_GT_DEF                  (0x00000000)
  #define MPCOHTRK_CR_GDXC_QUALIFIER_GLOBAL_MEM_CHR_RD_OFF             ( 9)
  #define MPCOHTRK_CR_GDXC_QUALIFIER_GLOBAL_MEM_CHR_RD_WID             ( 1)
  #define MPCOHTRK_CR_GDXC_QUALIFIER_GLOBAL_MEM_CHR_RD_MSK             (0x00000200)
  #define MPCOHTRK_CR_GDXC_QUALIFIER_GLOBAL_MEM_CHR_RD_MAX             (0x00000001)
  #define MPCOHTRK_CR_GDXC_QUALIFIER_GLOBAL_MEM_CHR_RD_DEF             (0x00000001)
  #define MPCOHTRK_CR_GDXC_QUALIFIER_GLOBAL_MEM_CHR_WR_OFF             (10)
  #define MPCOHTRK_CR_GDXC_QUALIFIER_GLOBAL_MEM_CHR_WR_WID             ( 1)
  #define MPCOHTRK_CR_GDXC_QUALIFIER_GLOBAL_MEM_CHR_WR_MSK             (0x00000400)
  #define MPCOHTRK_CR_GDXC_QUALIFIER_GLOBAL_MEM_CHR_WR_MAX             (0x00000001)
  #define MPCOHTRK_CR_GDXC_QUALIFIER_GLOBAL_MEM_CHR_WR_DEF             (0x00000001)
  #define MPCOHTRK_CR_GDXC_QUALIFIER_GLOBAL_MEM_NC_OFF                 (11)
  #define MPCOHTRK_CR_GDXC_QUALIFIER_GLOBAL_MEM_NC_WID                 ( 1)
  #define MPCOHTRK_CR_GDXC_QUALIFIER_GLOBAL_MEM_NC_MSK                 (0x00000800)
  #define MPCOHTRK_CR_GDXC_QUALIFIER_GLOBAL_MEM_NC_MAX                 (0x00000001)
  #define MPCOHTRK_CR_GDXC_QUALIFIER_GLOBAL_MEM_NC_DEF                 (0x00000001)
  #define MPCOHTRK_CR_GDXC_QUALIFIER_GLOBAL_EN_CBO_Exp_WB_OFF          (12)
  #define MPCOHTRK_CR_GDXC_QUALIFIER_GLOBAL_EN_CBO_Exp_WB_WID          ( 1)
  #define MPCOHTRK_CR_GDXC_QUALIFIER_GLOBAL_EN_CBO_Exp_WB_MSK          (0x00001000)
  #define MPCOHTRK_CR_GDXC_QUALIFIER_GLOBAL_EN_CBO_Exp_WB_MAX          (0x00000001)
  #define MPCOHTRK_CR_GDXC_QUALIFIER_GLOBAL_EN_CBO_Exp_WB_DEF          (0x00000000)
  #define MPCOHTRK_CR_GDXC_QUALIFIER_GLOBAL_SNP_Access_OFF             (13)
  #define MPCOHTRK_CR_GDXC_QUALIFIER_GLOBAL_SNP_Access_WID             ( 1)
  #define MPCOHTRK_CR_GDXC_QUALIFIER_GLOBAL_SNP_Access_MSK             (0x00002000)
  #define MPCOHTRK_CR_GDXC_QUALIFIER_GLOBAL_SNP_Access_MAX             (0x00000001)
  #define MPCOHTRK_CR_GDXC_QUALIFIER_GLOBAL_SNP_Access_DEF             (0x00000001)
  #define MPCOHTRK_CR_GDXC_QUALIFIER_GLOBAL_SELECT_PRE_OFF             (14)
  #define MPCOHTRK_CR_GDXC_QUALIFIER_GLOBAL_SELECT_PRE_WID             ( 1)
  #define MPCOHTRK_CR_GDXC_QUALIFIER_GLOBAL_SELECT_PRE_MSK             (0x00004000)
  #define MPCOHTRK_CR_GDXC_QUALIFIER_GLOBAL_SELECT_PRE_MAX             (0x00000001)
  #define MPCOHTRK_CR_GDXC_QUALIFIER_GLOBAL_SELECT_PRE_DEF             (0x00000000)

#define MPCOHTRK_CR_GDXC_QUALIFIER_BL_REG                            (0x00000008)
  #define MPCOHTRK_CR_GDXC_QUALIFIER_BL_CR_CHR_RD_OFF                  ( 0)
  #define MPCOHTRK_CR_GDXC_QUALIFIER_BL_CR_CHR_RD_WID                  ( 3)
  #define MPCOHTRK_CR_GDXC_QUALIFIER_BL_CR_CHR_RD_MSK                  (0x00000007)
  #define MPCOHTRK_CR_GDXC_QUALIFIER_BL_CR_CHR_RD_MAX                  (0x00000007)
  #define MPCOHTRK_CR_GDXC_QUALIFIER_BL_CR_CHR_RD_DEF                  (0x00000000)
  #define MPCOHTRK_CR_GDXC_QUALIFIER_BL_CHR_RD_STAT_MOD_OFF            ( 3)
  #define MPCOHTRK_CR_GDXC_QUALIFIER_BL_CHR_RD_STAT_MOD_WID            ( 1)
  #define MPCOHTRK_CR_GDXC_QUALIFIER_BL_CHR_RD_STAT_MOD_MSK            (0x00000008)
  #define MPCOHTRK_CR_GDXC_QUALIFIER_BL_CHR_RD_STAT_MOD_MAX            (0x00000001)
  #define MPCOHTRK_CR_GDXC_QUALIFIER_BL_CHR_RD_STAT_MOD_DEF            (0x00000001)
  #define MPCOHTRK_CR_GDXC_QUALIFIER_BL_CR_CHR_WR_OFF                  ( 4)
  #define MPCOHTRK_CR_GDXC_QUALIFIER_BL_CR_CHR_WR_WID                  ( 4)
  #define MPCOHTRK_CR_GDXC_QUALIFIER_BL_CR_CHR_WR_MSK                  (0x000000F0)
  #define MPCOHTRK_CR_GDXC_QUALIFIER_BL_CR_CHR_WR_MAX                  (0x0000000F)
  #define MPCOHTRK_CR_GDXC_QUALIFIER_BL_CR_CHR_WR_DEF                  (0x00000000)
  #define MPCOHTRK_CR_GDXC_QUALIFIER_BL_CR_NC_RD_OFF                   ( 8)
  #define MPCOHTRK_CR_GDXC_QUALIFIER_BL_CR_NC_RD_WID                   ( 3)
  #define MPCOHTRK_CR_GDXC_QUALIFIER_BL_CR_NC_RD_MSK                   (0x00000700)
  #define MPCOHTRK_CR_GDXC_QUALIFIER_BL_CR_NC_RD_MAX                   (0x00000007)
  #define MPCOHTRK_CR_GDXC_QUALIFIER_BL_CR_NC_RD_DEF                   (0x00000000)
  #define MPCOHTRK_CR_GDXC_QUALIFIER_BL_NC_RD_STAT_MOD_OFF             (11)
  #define MPCOHTRK_CR_GDXC_QUALIFIER_BL_NC_RD_STAT_MOD_WID             ( 1)
  #define MPCOHTRK_CR_GDXC_QUALIFIER_BL_NC_RD_STAT_MOD_MSK             (0x00000800)
  #define MPCOHTRK_CR_GDXC_QUALIFIER_BL_NC_RD_STAT_MOD_MAX             (0x00000001)
  #define MPCOHTRK_CR_GDXC_QUALIFIER_BL_NC_RD_STAT_MOD_DEF             (0x00000001)
  #define MPCOHTRK_CR_GDXC_QUALIFIER_BL_CR_NC_WR_OFF                   (12)
  #define MPCOHTRK_CR_GDXC_QUALIFIER_BL_CR_NC_WR_WID                   ( 4)
  #define MPCOHTRK_CR_GDXC_QUALIFIER_BL_CR_NC_WR_MSK                   (0x0000F000)
  #define MPCOHTRK_CR_GDXC_QUALIFIER_BL_CR_NC_WR_MAX                   (0x0000000F)
  #define MPCOHTRK_CR_GDXC_QUALIFIER_BL_CR_NC_WR_DEF                   (0x00000000)
  #define MPCOHTRK_CR_GDXC_QUALIFIER_BL_NC_WR_STAT_MOD_OFF             (16)
  #define MPCOHTRK_CR_GDXC_QUALIFIER_BL_NC_WR_STAT_MOD_WID             ( 1)
  #define MPCOHTRK_CR_GDXC_QUALIFIER_BL_NC_WR_STAT_MOD_MSK             (0x00010000)
  #define MPCOHTRK_CR_GDXC_QUALIFIER_BL_NC_WR_STAT_MOD_MAX             (0x00000001)
  #define MPCOHTRK_CR_GDXC_QUALIFIER_BL_NC_WR_STAT_MOD_DEF             (0x00000001)
  #define MPCOHTRK_CR_GDXC_QUALIFIER_BL_Data_Core0_OFF                 (17)
  #define MPCOHTRK_CR_GDXC_QUALIFIER_BL_Data_Core0_WID                 ( 1)
  #define MPCOHTRK_CR_GDXC_QUALIFIER_BL_Data_Core0_MSK                 (0x00020000)
  #define MPCOHTRK_CR_GDXC_QUALIFIER_BL_Data_Core0_MAX                 (0x00000001)
  #define MPCOHTRK_CR_GDXC_QUALIFIER_BL_Data_Core0_DEF                 (0x00000000)
  #define MPCOHTRK_CR_GDXC_QUALIFIER_BL_Data_Core1_OFF                 (18)
  #define MPCOHTRK_CR_GDXC_QUALIFIER_BL_Data_Core1_WID                 ( 1)
  #define MPCOHTRK_CR_GDXC_QUALIFIER_BL_Data_Core1_MSK                 (0x00040000)
  #define MPCOHTRK_CR_GDXC_QUALIFIER_BL_Data_Core1_MAX                 (0x00000001)
  #define MPCOHTRK_CR_GDXC_QUALIFIER_BL_Data_Core1_DEF                 (0x00000000)
  #define MPCOHTRK_CR_GDXC_QUALIFIER_BL_Data_Core2_OFF                 (19)
  #define MPCOHTRK_CR_GDXC_QUALIFIER_BL_Data_Core2_WID                 ( 1)
  #define MPCOHTRK_CR_GDXC_QUALIFIER_BL_Data_Core2_MSK                 (0x00080000)
  #define MPCOHTRK_CR_GDXC_QUALIFIER_BL_Data_Core2_MAX                 (0x00000001)
  #define MPCOHTRK_CR_GDXC_QUALIFIER_BL_Data_Core2_DEF                 (0x00000000)
  #define MPCOHTRK_CR_GDXC_QUALIFIER_BL_Data_Core3_OFF                 (20)
  #define MPCOHTRK_CR_GDXC_QUALIFIER_BL_Data_Core3_WID                 ( 1)
  #define MPCOHTRK_CR_GDXC_QUALIFIER_BL_Data_Core3_MSK                 (0x00100000)
  #define MPCOHTRK_CR_GDXC_QUALIFIER_BL_Data_Core3_MAX                 (0x00000001)
  #define MPCOHTRK_CR_GDXC_QUALIFIER_BL_Data_Core3_DEF                 (0x00000000)
  #define MPCOHTRK_CR_GDXC_QUALIFIER_BL_Data_CBO_OFF                   (21)
  #define MPCOHTRK_CR_GDXC_QUALIFIER_BL_Data_CBO_WID                   ( 1)
  #define MPCOHTRK_CR_GDXC_QUALIFIER_BL_Data_CBO_MSK                   (0x00200000)
  #define MPCOHTRK_CR_GDXC_QUALIFIER_BL_Data_CBO_MAX                   (0x00000001)
  #define MPCOHTRK_CR_GDXC_QUALIFIER_BL_Data_CBO_DEF                   (0x00000000)
  #define MPCOHTRK_CR_GDXC_QUALIFIER_BL_Data_GT_OFF                    (22)
  #define MPCOHTRK_CR_GDXC_QUALIFIER_BL_Data_GT_WID                    ( 1)
  #define MPCOHTRK_CR_GDXC_QUALIFIER_BL_Data_GT_MSK                    (0x00400000)
  #define MPCOHTRK_CR_GDXC_QUALIFIER_BL_Data_GT_MAX                    (0x00000001)
  #define MPCOHTRK_CR_GDXC_QUALIFIER_BL_Data_GT_DEF                    (0x00000000)

#define MPCOHTRK_CR_GDXC_OVF_STATUS_REG                              (0x0000000C)
  #define MPCOHTRK_CR_GDXC_OVF_STATUS_OVF_Global_OFF                   ( 0)
  #define MPCOHTRK_CR_GDXC_OVF_STATUS_OVF_Global_WID                   ( 1)
  #define MPCOHTRK_CR_GDXC_OVF_STATUS_OVF_Global_MSK                   (0x00000001)
  #define MPCOHTRK_CR_GDXC_OVF_STATUS_OVF_Global_MAX                   (0x00000001)
  #define MPCOHTRK_CR_GDXC_OVF_STATUS_OVF_Global_DEF                   (0x00000000)
  #define MPCOHTRK_CR_GDXC_OVF_STATUS_OVF_Ring_AD_OFF                  ( 1)
  #define MPCOHTRK_CR_GDXC_OVF_STATUS_OVF_Ring_AD_WID                  ( 1)
  #define MPCOHTRK_CR_GDXC_OVF_STATUS_OVF_Ring_AD_MSK                  (0x00000002)
  #define MPCOHTRK_CR_GDXC_OVF_STATUS_OVF_Ring_AD_MAX                  (0x00000001)
  #define MPCOHTRK_CR_GDXC_OVF_STATUS_OVF_Ring_AD_DEF                  (0x00000000)
  #define MPCOHTRK_CR_GDXC_OVF_STATUS_OVF_Ring_BL_OFF                  ( 2)
  #define MPCOHTRK_CR_GDXC_OVF_STATUS_OVF_Ring_BL_WID                  ( 1)
  #define MPCOHTRK_CR_GDXC_OVF_STATUS_OVF_Ring_BL_MSK                  (0x00000004)
  #define MPCOHTRK_CR_GDXC_OVF_STATUS_OVF_Ring_BL_MAX                  (0x00000001)
  #define MPCOHTRK_CR_GDXC_OVF_STATUS_OVF_Ring_BL_DEF                  (0x00000000)
  #define MPCOHTRK_CR_GDXC_OVF_STATUS_OVF_Ring_AK_OFF                  ( 3)
  #define MPCOHTRK_CR_GDXC_OVF_STATUS_OVF_Ring_AK_WID                  ( 1)
  #define MPCOHTRK_CR_GDXC_OVF_STATUS_OVF_Ring_AK_MSK                  (0x00000008)
  #define MPCOHTRK_CR_GDXC_OVF_STATUS_OVF_Ring_AK_MAX                  (0x00000001)
  #define MPCOHTRK_CR_GDXC_OVF_STATUS_OVF_Ring_AK_DEF                  (0x00000000)
  #define MPCOHTRK_CR_GDXC_OVF_STATUS_OVF_Ring_IV_OFF                  ( 4)
  #define MPCOHTRK_CR_GDXC_OVF_STATUS_OVF_Ring_IV_WID                  ( 1)
  #define MPCOHTRK_CR_GDXC_OVF_STATUS_OVF_Ring_IV_MSK                  (0x00000010)
  #define MPCOHTRK_CR_GDXC_OVF_STATUS_OVF_Ring_IV_MAX                  (0x00000001)
  #define MPCOHTRK_CR_GDXC_OVF_STATUS_OVF_Ring_IV_DEF                  (0x00000000)
  #define MPCOHTRK_CR_GDXC_OVF_STATUS_OVF_mcUCLK_OFF                   (10)
  #define MPCOHTRK_CR_GDXC_OVF_STATUS_OVF_mcUCLK_WID                   ( 1)
  #define MPCOHTRK_CR_GDXC_OVF_STATUS_OVF_mcUCLK_MSK                   (0x00000400)
  #define MPCOHTRK_CR_GDXC_OVF_STATUS_OVF_mcUCLK_MAX                   (0x00000001)
  #define MPCOHTRK_CR_GDXC_OVF_STATUS_OVF_mcUCLK_DEF                   (0x00000000)

#define MPCOHTRK_CR_GDXC_MOT_ADDRESS_LO_REG                          (0x00000010)
  #define MPCOHTRK_CR_GDXC_MOT_ADDRESS_LO_MEM_PTR_OFF                  ( 0)
  #define MPCOHTRK_CR_GDXC_MOT_ADDRESS_LO_MEM_PTR_WID                  (32)
  #define MPCOHTRK_CR_GDXC_MOT_ADDRESS_LO_MEM_PTR_MSK                  (0xFFFFFFFF)
  #define MPCOHTRK_CR_GDXC_MOT_ADDRESS_LO_MEM_PTR_MAX                  (0xFFFFFFFF)
  #define MPCOHTRK_CR_GDXC_MOT_ADDRESS_LO_MEM_PTR_DEF                  (0x00000000)

#define MPCOHTRK_CR_GDXC_MOT_ADDRESS_HI_REG                          (0x00000014)
  #define MPCOHTRK_CR_GDXC_MOT_ADDRESS_HI_MEM_PTR_OFF                  ( 0)
  #define MPCOHTRK_CR_GDXC_MOT_ADDRESS_HI_MEM_PTR_WID                  ( 1)
  #define MPCOHTRK_CR_GDXC_MOT_ADDRESS_HI_MEM_PTR_MSK                  (0x00000001)
  #define MPCOHTRK_CR_GDXC_MOT_ADDRESS_HI_MEM_PTR_MAX                  (0x00000001)
  #define MPCOHTRK_CR_GDXC_MOT_ADDRESS_HI_MEM_PTR_DEF                  (0x00000000)
  #define MPCOHTRK_CR_GDXC_MOT_ADDRESS_HI_BUFFER_WRAP_OFF              ( 1)
  #define MPCOHTRK_CR_GDXC_MOT_ADDRESS_HI_BUFFER_WRAP_WID              ( 1)
  #define MPCOHTRK_CR_GDXC_MOT_ADDRESS_HI_BUFFER_WRAP_MSK              (0x00000002)
  #define MPCOHTRK_CR_GDXC_MOT_ADDRESS_HI_BUFFER_WRAP_MAX              (0x00000001)
  #define MPCOHTRK_CR_GDXC_MOT_ADDRESS_HI_BUFFER_WRAP_DEF              (0x00000000)
  #define MPCOHTRK_CR_GDXC_MOT_ADDRESS_HI_SPARE_OFF                    ( 2)
  #define MPCOHTRK_CR_GDXC_MOT_ADDRESS_HI_SPARE_WID                    ( 4)
  #define MPCOHTRK_CR_GDXC_MOT_ADDRESS_HI_SPARE_MSK                    (0x0000003C)
  #define MPCOHTRK_CR_GDXC_MOT_ADDRESS_HI_SPARE_MAX                    (0x0000000F)
  #define MPCOHTRK_CR_GDXC_MOT_ADDRESS_HI_SPARE_DEF                    (0x00000000)

#define MPCOHTRK_CR_GDXC_MOT_REGION_REG                              (0x00000018)
  #define MPCOHTRK_CR_GDXC_MOT_REGION_START_ADDRESS_OFF                ( 0)
  #define MPCOHTRK_CR_GDXC_MOT_REGION_START_ADDRESS_WID                (16)
  #define MPCOHTRK_CR_GDXC_MOT_REGION_START_ADDRESS_MSK                (0x0000FFFF)
  #define MPCOHTRK_CR_GDXC_MOT_REGION_START_ADDRESS_MAX                (0x0000FFFF)
  #define MPCOHTRK_CR_GDXC_MOT_REGION_START_ADDRESS_DEF                (0x00000000)
  #define MPCOHTRK_CR_GDXC_MOT_REGION_END_ADDRESS_OFF                  (16)
  #define MPCOHTRK_CR_GDXC_MOT_REGION_END_ADDRESS_WID                  (16)
  #define MPCOHTRK_CR_GDXC_MOT_REGION_END_ADDRESS_MSK                  (0xFFFF0000)
  #define MPCOHTRK_CR_GDXC_MOT_REGION_END_ADDRESS_MAX                  (0x0000FFFF)
  #define MPCOHTRK_CR_GDXC_MOT_REGION_END_ADDRESS_DEF                  (0x00000001)

#define MPCOHTRK_CR_GDXC_OCLA_ADDRESS_LO_REG                         (0x00000020)
  #define MPCOHTRK_CR_GDXC_OCLA_ADDRESS_LO_MEM_PTR_OFF                 ( 0)
  #define MPCOHTRK_CR_GDXC_OCLA_ADDRESS_LO_MEM_PTR_WID                 (32)
  #define MPCOHTRK_CR_GDXC_OCLA_ADDRESS_LO_MEM_PTR_MSK                 (0xFFFFFFFF)
  #define MPCOHTRK_CR_GDXC_OCLA_ADDRESS_LO_MEM_PTR_MAX                 (0xFFFFFFFF)
  #define MPCOHTRK_CR_GDXC_OCLA_ADDRESS_LO_MEM_PTR_DEF                 (0x00000000)

#define MPCOHTRK_CR_GDXC_OCLA_ADDRESS_HI_REG                         (0x00000024)
  #define MPCOHTRK_CR_GDXC_OCLA_ADDRESS_HI_MEM_PTR_OFF                 ( 0)
  #define MPCOHTRK_CR_GDXC_OCLA_ADDRESS_HI_MEM_PTR_WID                 ( 1)
  #define MPCOHTRK_CR_GDXC_OCLA_ADDRESS_HI_MEM_PTR_MSK                 (0x00000001)
  #define MPCOHTRK_CR_GDXC_OCLA_ADDRESS_HI_MEM_PTR_MAX                 (0x00000001)
  #define MPCOHTRK_CR_GDXC_OCLA_ADDRESS_HI_MEM_PTR_DEF                 (0x00000000)
  #define MPCOHTRK_CR_GDXC_OCLA_ADDRESS_HI_BUFFER_WRAP_OFF             ( 1)
  #define MPCOHTRK_CR_GDXC_OCLA_ADDRESS_HI_BUFFER_WRAP_WID             ( 1)
  #define MPCOHTRK_CR_GDXC_OCLA_ADDRESS_HI_BUFFER_WRAP_MSK             (0x00000002)
  #define MPCOHTRK_CR_GDXC_OCLA_ADDRESS_HI_BUFFER_WRAP_MAX             (0x00000001)
  #define MPCOHTRK_CR_GDXC_OCLA_ADDRESS_HI_BUFFER_WRAP_DEF             (0x00000000)
  #define MPCOHTRK_CR_GDXC_OCLA_ADDRESS_HI_LOCK_OFF                    ( 2)
  #define MPCOHTRK_CR_GDXC_OCLA_ADDRESS_HI_LOCK_WID                    ( 1)
  #define MPCOHTRK_CR_GDXC_OCLA_ADDRESS_HI_LOCK_MSK                    (0x00000004)
  #define MPCOHTRK_CR_GDXC_OCLA_ADDRESS_HI_LOCK_MAX                    (0x00000001)
  #define MPCOHTRK_CR_GDXC_OCLA_ADDRESS_HI_LOCK_DEF                    (0x00000000)
  #define MPCOHTRK_CR_GDXC_OCLA_ADDRESS_HI_SPARE_OFF                   ( 3)
  #define MPCOHTRK_CR_GDXC_OCLA_ADDRESS_HI_SPARE_WID                   ( 4)
  #define MPCOHTRK_CR_GDXC_OCLA_ADDRESS_HI_SPARE_MSK                   (0x00000078)
  #define MPCOHTRK_CR_GDXC_OCLA_ADDRESS_HI_SPARE_MAX                   (0x0000000F)
  #define MPCOHTRK_CR_GDXC_OCLA_ADDRESS_HI_SPARE_DEF                   (0x00000000)

#define MPCOHTRK_CR_GDXC_OCLA_REGION_REG                             (0x00000028)
  #define MPCOHTRK_CR_GDXC_OCLA_REGION_START_ADDRESS_OFF               ( 0)
  #define MPCOHTRK_CR_GDXC_OCLA_REGION_START_ADDRESS_WID               (16)
  #define MPCOHTRK_CR_GDXC_OCLA_REGION_START_ADDRESS_MSK               (0x0000FFFF)
  #define MPCOHTRK_CR_GDXC_OCLA_REGION_START_ADDRESS_MAX               (0x0000FFFF)
  #define MPCOHTRK_CR_GDXC_OCLA_REGION_START_ADDRESS_DEF               (0x00000000)
  #define MPCOHTRK_CR_GDXC_OCLA_REGION_END_ADDRESS_OFF                 (16)
  #define MPCOHTRK_CR_GDXC_OCLA_REGION_END_ADDRESS_WID                 (16)
  #define MPCOHTRK_CR_GDXC_OCLA_REGION_END_ADDRESS_MSK                 (0xFFFF0000)
  #define MPCOHTRK_CR_GDXC_OCLA_REGION_END_ADDRESS_MAX                 (0x0000FFFF)
  #define MPCOHTRK_CR_GDXC_OCLA_REGION_END_ADDRESS_DEF                 (0x00000001)

#define MPCOHTRK_CR_GDXC_MASK_ADDRESSL_REG                           (0x00000030)
  #define MPCOHTRK_CR_GDXC_MASK_ADDRESSL_Mask_bits_OFF                 ( 0)
  #define MPCOHTRK_CR_GDXC_MASK_ADDRESSL_Mask_bits_WID                 (32)
  #define MPCOHTRK_CR_GDXC_MASK_ADDRESSL_Mask_bits_MSK                 (0xFFFFFFFF)
  #define MPCOHTRK_CR_GDXC_MASK_ADDRESSL_Mask_bits_MAX                 (0xFFFFFFFF)
  #define MPCOHTRK_CR_GDXC_MASK_ADDRESSL_Mask_bits_DEF                 (0x00000000)

#define MPCOHTRK_CR_GDXC_MASK_ADDRESSH_REG                           (0x00000034)
  #define MPCOHTRK_CR_GDXC_MASK_ADDRESSH_Mask_bits_OFF                 ( 0)
  #define MPCOHTRK_CR_GDXC_MASK_ADDRESSH_Mask_bits_WID                 ( 7)
  #define MPCOHTRK_CR_GDXC_MASK_ADDRESSH_Mask_bits_MSK                 (0x0000007F)
  #define MPCOHTRK_CR_GDXC_MASK_ADDRESSH_Mask_bits_MAX                 (0x0000007F)
  #define MPCOHTRK_CR_GDXC_MASK_ADDRESSH_Mask_bits_DEF                 (0x00000000)

#define MPCOHTRK_CR_GDXC_ARM_ADDRESSL_REG                            (0x00000038)
  #define MPCOHTRK_CR_GDXC_ARM_ADDRESSL_ARM_bits_OFF                   ( 0)
  #define MPCOHTRK_CR_GDXC_ARM_ADDRESSL_ARM_bits_WID                   (32)
  #define MPCOHTRK_CR_GDXC_ARM_ADDRESSL_ARM_bits_MSK                   (0xFFFFFFFF)
  #define MPCOHTRK_CR_GDXC_ARM_ADDRESSL_ARM_bits_MAX                   (0xFFFFFFFF)
  #define MPCOHTRK_CR_GDXC_ARM_ADDRESSL_ARM_bits_DEF                   (0x00000000)

#define MPCOHTRK_CR_GDXC_ARM_ADDRESSH_REG                            (0x0000003C)
  #define MPCOHTRK_CR_GDXC_ARM_ADDRESSH_ARM_bits_OFF                   ( 0)
  #define MPCOHTRK_CR_GDXC_ARM_ADDRESSH_ARM_bits_WID                   ( 7)
  #define MPCOHTRK_CR_GDXC_ARM_ADDRESSH_ARM_bits_MSK                   (0x0000007F)
  #define MPCOHTRK_CR_GDXC_ARM_ADDRESSH_ARM_bits_MAX                   (0x0000007F)
  #define MPCOHTRK_CR_GDXC_ARM_ADDRESSH_ARM_bits_DEF                   (0x00000000)

#define DDRPL_CR_DDR_TRACE_SOURCE_CONFIG_REG                         (0x00000C00)
  #define DDRPL_CR_DDR_TRACE_SOURCE_CONFIG_Trace_Source_Enable_OFF     ( 0)
  #define DDRPL_CR_DDR_TRACE_SOURCE_CONFIG_Trace_Source_Enable_WID     ( 1)
  #define DDRPL_CR_DDR_TRACE_SOURCE_CONFIG_Trace_Source_Enable_MSK     (0x00000001)
  #define DDRPL_CR_DDR_TRACE_SOURCE_CONFIG_Trace_Source_Enable_MAX     (0x00000001)
  #define DDRPL_CR_DDR_TRACE_SOURCE_CONFIG_Trace_Source_Enable_DEF     (0x00000000)
  #define DDRPL_CR_DDR_TRACE_SOURCE_CONFIG_Channel_Select_OFF          ( 1)
  #define DDRPL_CR_DDR_TRACE_SOURCE_CONFIG_Channel_Select_WID          ( 2)
  #define DDRPL_CR_DDR_TRACE_SOURCE_CONFIG_Channel_Select_MSK          (0x00000006)
  #define DDRPL_CR_DDR_TRACE_SOURCE_CONFIG_Channel_Select_MAX          (0x00000003)
  #define DDRPL_CR_DDR_TRACE_SOURCE_CONFIG_Channel_Select_DEF          (0x00000000)
  #define DDRPL_CR_DDR_TRACE_SOURCE_CONFIG_ACC_Trace_Element_Width_OFF ( 3)
  #define DDRPL_CR_DDR_TRACE_SOURCE_CONFIG_ACC_Trace_Element_Width_WID ( 1)
  #define DDRPL_CR_DDR_TRACE_SOURCE_CONFIG_ACC_Trace_Element_Width_MSK (0x00000008)
  #define DDRPL_CR_DDR_TRACE_SOURCE_CONFIG_ACC_Trace_Element_Width_MAX (0x00000001)
  #define DDRPL_CR_DDR_TRACE_SOURCE_CONFIG_ACC_Trace_Element_Width_DEF (0x00000000)
  #define DDRPL_CR_DDR_TRACE_SOURCE_CONFIG_ECC_Mode_OFF                ( 4)
  #define DDRPL_CR_DDR_TRACE_SOURCE_CONFIG_ECC_Mode_WID                ( 1)
  #define DDRPL_CR_DDR_TRACE_SOURCE_CONFIG_ECC_Mode_MSK                (0x00000010)
  #define DDRPL_CR_DDR_TRACE_SOURCE_CONFIG_ECC_Mode_MAX                (0x00000001)
  #define DDRPL_CR_DDR_TRACE_SOURCE_CONFIG_ECC_Mode_DEF                (0x00000000)
  #define DDRPL_CR_DDR_TRACE_SOURCE_CONFIG_Final_Arbiter_Weight_OFF    ( 5)
  #define DDRPL_CR_DDR_TRACE_SOURCE_CONFIG_Final_Arbiter_Weight_WID    ( 2)
  #define DDRPL_CR_DDR_TRACE_SOURCE_CONFIG_Final_Arbiter_Weight_MSK    (0x00000060)
  #define DDRPL_CR_DDR_TRACE_SOURCE_CONFIG_Final_Arbiter_Weight_MAX    (0x00000003)
  #define DDRPL_CR_DDR_TRACE_SOURCE_CONFIG_Final_Arbiter_Weight_DEF    (0x00000000)
  #define DDRPL_CR_DDR_TRACE_SOURCE_CONFIG_DDR_Trace_En_OFF            ( 7)
  #define DDRPL_CR_DDR_TRACE_SOURCE_CONFIG_DDR_Trace_En_WID            ( 1)
  #define DDRPL_CR_DDR_TRACE_SOURCE_CONFIG_DDR_Trace_En_MSK            (0x00000080)
  #define DDRPL_CR_DDR_TRACE_SOURCE_CONFIG_DDR_Trace_En_MAX            (0x00000001)
  #define DDRPL_CR_DDR_TRACE_SOURCE_CONFIG_DDR_Trace_En_DEF            (0x00000000)
  #define DDRPL_CR_DDR_TRACE_SOURCE_CONFIG_DDR_Trig_En_OFF             ( 8)
  #define DDRPL_CR_DDR_TRACE_SOURCE_CONFIG_DDR_Trig_En_WID             ( 1)
  #define DDRPL_CR_DDR_TRACE_SOURCE_CONFIG_DDR_Trig_En_MSK             (0x00000100)
  #define DDRPL_CR_DDR_TRACE_SOURCE_CONFIG_DDR_Trig_En_MAX             (0x00000001)
  #define DDRPL_CR_DDR_TRACE_SOURCE_CONFIG_DDR_Trig_En_DEF             (0x00000000)
  #define DDRPL_CR_DDR_TRACE_SOURCE_CONFIG_Clock_Gate_Ovr_OFF          ( 9)
  #define DDRPL_CR_DDR_TRACE_SOURCE_CONFIG_Clock_Gate_Ovr_WID          ( 1)
  #define DDRPL_CR_DDR_TRACE_SOURCE_CONFIG_Clock_Gate_Ovr_MSK          (0x00000200)
  #define DDRPL_CR_DDR_TRACE_SOURCE_CONFIG_Clock_Gate_Ovr_MAX          (0x00000001)
  #define DDRPL_CR_DDR_TRACE_SOURCE_CONFIG_Clock_Gate_Ovr_DEF          (0x00000000)
  #define DDRPL_CR_DDR_TRACE_SOURCE_CONFIG_SO_X_OVRD_OFF               (10)
  #define DDRPL_CR_DDR_TRACE_SOURCE_CONFIG_SO_X_OVRD_WID               ( 1)
  #define DDRPL_CR_DDR_TRACE_SOURCE_CONFIG_SO_X_OVRD_MSK               (0x00000400)
  #define DDRPL_CR_DDR_TRACE_SOURCE_CONFIG_SO_X_OVRD_MAX               (0x00000001)
  #define DDRPL_CR_DDR_TRACE_SOURCE_CONFIG_SO_X_OVRD_DEF               (0x00000001)
  #define DDRPL_CR_DDR_TRACE_SOURCE_CONFIG_DDR_Type_OFF                (11)
  #define DDRPL_CR_DDR_TRACE_SOURCE_CONFIG_DDR_Type_WID                ( 2)
  #define DDRPL_CR_DDR_TRACE_SOURCE_CONFIG_DDR_Type_MSK                (0x00001800)
  #define DDRPL_CR_DDR_TRACE_SOURCE_CONFIG_DDR_Type_MAX                (0x00000003)
  #define DDRPL_CR_DDR_TRACE_SOURCE_CONFIG_DDR_Type_DEF                (0x00000000)
  #define DDRPL_CR_DDR_TRACE_SOURCE_CONFIG_Rd_Wr_Overlap_OFF           (13)
  #define DDRPL_CR_DDR_TRACE_SOURCE_CONFIG_Rd_Wr_Overlap_WID           ( 1)
  #define DDRPL_CR_DDR_TRACE_SOURCE_CONFIG_Rd_Wr_Overlap_MSK           (0x00002000)
  #define DDRPL_CR_DDR_TRACE_SOURCE_CONFIG_Rd_Wr_Overlap_MAX           (0x00000001)
  #define DDRPL_CR_DDR_TRACE_SOURCE_CONFIG_Rd_Wr_Overlap_DEF           (0x00000000)
  #define DDRPL_CR_DDR_TRACE_SOURCE_CONFIG_Spare_OFF                   (14)
  #define DDRPL_CR_DDR_TRACE_SOURCE_CONFIG_Spare_WID                   ( 7)
  #define DDRPL_CR_DDR_TRACE_SOURCE_CONFIG_Spare_MSK                   (0x001FC000)
  #define DDRPL_CR_DDR_TRACE_SOURCE_CONFIG_Spare_MAX                   (0x0000007F)
  #define DDRPL_CR_DDR_TRACE_SOURCE_CONFIG_Spare_DEF                   (0x00000000)
  #define DDRPL_CR_DDR_TRACE_SOURCE_CONFIG_QCLK_DOMAIN_UP_OFF          (31)
  #define DDRPL_CR_DDR_TRACE_SOURCE_CONFIG_QCLK_DOMAIN_UP_WID          ( 1)
  #define DDRPL_CR_DDR_TRACE_SOURCE_CONFIG_QCLK_DOMAIN_UP_MSK          (0x80000000)
  #define DDRPL_CR_DDR_TRACE_SOURCE_CONFIG_QCLK_DOMAIN_UP_MAX          (0x00000001)
  #define DDRPL_CR_DDR_TRACE_SOURCE_CONFIG_QCLK_DOMAIN_UP_DEF          (0x00000000)

#define DDRPL_CR_DDR_TX_DELAY_LOW_REG                                (0x00000C04)
  #define DDRPL_CR_DDR_TX_DELAY_LOW_Tx_Delay_R0_OFF                    ( 0)
  #define DDRPL_CR_DDR_TX_DELAY_LOW_Tx_Delay_R0_WID                    ( 8)
  #define DDRPL_CR_DDR_TX_DELAY_LOW_Tx_Delay_R0_MSK                    (0x000000FF)
  #define DDRPL_CR_DDR_TX_DELAY_LOW_Tx_Delay_R0_MAX                    (0x000000FF)
  #define DDRPL_CR_DDR_TX_DELAY_LOW_Tx_Delay_R0_DEF                    (0x00000010)
  #define DDRPL_CR_DDR_TX_DELAY_LOW_Tx_Delay_R1_OFF                    ( 8)
  #define DDRPL_CR_DDR_TX_DELAY_LOW_Tx_Delay_R1_WID                    ( 8)
  #define DDRPL_CR_DDR_TX_DELAY_LOW_Tx_Delay_R1_MSK                    (0x0000FF00)
  #define DDRPL_CR_DDR_TX_DELAY_LOW_Tx_Delay_R1_MAX                    (0x000000FF)
  #define DDRPL_CR_DDR_TX_DELAY_LOW_Tx_Delay_R1_DEF                    (0x00000010)
  #define DDRPL_CR_DDR_TX_DELAY_LOW_Tx_Delay_R2_OFF                    (16)
  #define DDRPL_CR_DDR_TX_DELAY_LOW_Tx_Delay_R2_WID                    ( 8)
  #define DDRPL_CR_DDR_TX_DELAY_LOW_Tx_Delay_R2_MSK                    (0x00FF0000)
  #define DDRPL_CR_DDR_TX_DELAY_LOW_Tx_Delay_R2_MAX                    (0x000000FF)
  #define DDRPL_CR_DDR_TX_DELAY_LOW_Tx_Delay_R2_DEF                    (0x00000010)
  #define DDRPL_CR_DDR_TX_DELAY_LOW_Tx_Delay_R3_OFF                    (24)
  #define DDRPL_CR_DDR_TX_DELAY_LOW_Tx_Delay_R3_WID                    ( 8)
  #define DDRPL_CR_DDR_TX_DELAY_LOW_Tx_Delay_R3_MSK                    (0xFF000000)
  #define DDRPL_CR_DDR_TX_DELAY_LOW_Tx_Delay_R3_MAX                    (0x000000FF)
  #define DDRPL_CR_DDR_TX_DELAY_LOW_Tx_Delay_R3_DEF                    (0x00000010)

#define DDRPL_CR_DDR_TX_LATENCY_LOW_REG                              (0x00000C08)
  #define DDRPL_CR_DDR_TX_LATENCY_LOW_Tx_Latency_R0_OFF                ( 0)
  #define DDRPL_CR_DDR_TX_LATENCY_LOW_Tx_Latency_R0_WID                ( 8)
  #define DDRPL_CR_DDR_TX_LATENCY_LOW_Tx_Latency_R0_MSK                (0x000000FF)
  #define DDRPL_CR_DDR_TX_LATENCY_LOW_Tx_Latency_R0_MAX                (0x000000FF)
  #define DDRPL_CR_DDR_TX_LATENCY_LOW_Tx_Latency_R0_DEF                (0x00000008)
  #define DDRPL_CR_DDR_TX_LATENCY_LOW_Tx_Latency_R1_OFF                ( 8)
  #define DDRPL_CR_DDR_TX_LATENCY_LOW_Tx_Latency_R1_WID                ( 8)
  #define DDRPL_CR_DDR_TX_LATENCY_LOW_Tx_Latency_R1_MSK                (0x0000FF00)
  #define DDRPL_CR_DDR_TX_LATENCY_LOW_Tx_Latency_R1_MAX                (0x000000FF)
  #define DDRPL_CR_DDR_TX_LATENCY_LOW_Tx_Latency_R1_DEF                (0x00000008)
  #define DDRPL_CR_DDR_TX_LATENCY_LOW_Tx_Latency_R2_OFF                (16)
  #define DDRPL_CR_DDR_TX_LATENCY_LOW_Tx_Latency_R2_WID                ( 8)
  #define DDRPL_CR_DDR_TX_LATENCY_LOW_Tx_Latency_R2_MSK                (0x00FF0000)
  #define DDRPL_CR_DDR_TX_LATENCY_LOW_Tx_Latency_R2_MAX                (0x000000FF)
  #define DDRPL_CR_DDR_TX_LATENCY_LOW_Tx_Latency_R2_DEF                (0x00000008)
  #define DDRPL_CR_DDR_TX_LATENCY_LOW_Tx_Latency_R3_OFF                (24)
  #define DDRPL_CR_DDR_TX_LATENCY_LOW_Tx_Latency_R3_WID                ( 8)
  #define DDRPL_CR_DDR_TX_LATENCY_LOW_Tx_Latency_R3_MSK                (0xFF000000)
  #define DDRPL_CR_DDR_TX_LATENCY_LOW_Tx_Latency_R3_MAX                (0x000000FF)
  #define DDRPL_CR_DDR_TX_LATENCY_LOW_Tx_Latency_R3_DEF                (0x00000008)

#define DDRPL_CR_DDR_RX_LATENCY_LOW_REG                              (0x00000C0C)
  #define DDRPL_CR_DDR_RX_LATENCY_LOW_Rx_Latency_R0_OFF                ( 0)
  #define DDRPL_CR_DDR_RX_LATENCY_LOW_Rx_Latency_R0_WID                ( 8)
  #define DDRPL_CR_DDR_RX_LATENCY_LOW_Rx_Latency_R0_MSK                (0x000000FF)
  #define DDRPL_CR_DDR_RX_LATENCY_LOW_Rx_Latency_R0_MAX                (0x000000FF)
  #define DDRPL_CR_DDR_RX_LATENCY_LOW_Rx_Latency_R0_DEF                (0x00000008)
  #define DDRPL_CR_DDR_RX_LATENCY_LOW_Rx_Latency_R1_OFF                ( 8)
  #define DDRPL_CR_DDR_RX_LATENCY_LOW_Rx_Latency_R1_WID                ( 8)
  #define DDRPL_CR_DDR_RX_LATENCY_LOW_Rx_Latency_R1_MSK                (0x0000FF00)
  #define DDRPL_CR_DDR_RX_LATENCY_LOW_Rx_Latency_R1_MAX                (0x000000FF)
  #define DDRPL_CR_DDR_RX_LATENCY_LOW_Rx_Latency_R1_DEF                (0x00000008)
  #define DDRPL_CR_DDR_RX_LATENCY_LOW_Rx_Latency_R2_OFF                (16)
  #define DDRPL_CR_DDR_RX_LATENCY_LOW_Rx_Latency_R2_WID                ( 8)
  #define DDRPL_CR_DDR_RX_LATENCY_LOW_Rx_Latency_R2_MSK                (0x00FF0000)
  #define DDRPL_CR_DDR_RX_LATENCY_LOW_Rx_Latency_R2_MAX                (0x000000FF)
  #define DDRPL_CR_DDR_RX_LATENCY_LOW_Rx_Latency_R2_DEF                (0x00000008)
  #define DDRPL_CR_DDR_RX_LATENCY_LOW_Rx_Latency_R3_OFF                (24)
  #define DDRPL_CR_DDR_RX_LATENCY_LOW_Rx_Latency_R3_WID                ( 8)
  #define DDRPL_CR_DDR_RX_LATENCY_LOW_Rx_Latency_R3_MSK                (0xFF000000)
  #define DDRPL_CR_DDR_RX_LATENCY_LOW_Rx_Latency_R3_MAX                (0x000000FF)
  #define DDRPL_CR_DDR_RX_LATENCY_LOW_Rx_Latency_R3_DEF                (0x00000008)

#define DDRPL_CR_DDR_TRIGGER_CONFIG_REG                              (0x00000C10)
  #define DDRPL_CR_DDR_TRIGGER_CONFIG_NOA_MUX_3_0_OFF                  ( 0)
  #define DDRPL_CR_DDR_TRIGGER_CONFIG_NOA_MUX_3_0_WID                  ( 2)
  #define DDRPL_CR_DDR_TRIGGER_CONFIG_NOA_MUX_3_0_MSK                  (0x00000003)
  #define DDRPL_CR_DDR_TRIGGER_CONFIG_NOA_MUX_3_0_MAX                  (0x00000003)
  #define DDRPL_CR_DDR_TRIGGER_CONFIG_NOA_MUX_3_0_DEF                  (0x00000000)
  #define DDRPL_CR_DDR_TRIGGER_CONFIG_NOA_MUX_7_4_OFF                  ( 2)
  #define DDRPL_CR_DDR_TRIGGER_CONFIG_NOA_MUX_7_4_WID                  ( 2)
  #define DDRPL_CR_DDR_TRIGGER_CONFIG_NOA_MUX_7_4_MSK                  (0x0000000C)
  #define DDRPL_CR_DDR_TRIGGER_CONFIG_NOA_MUX_7_4_MAX                  (0x00000003)
  #define DDRPL_CR_DDR_TRIGGER_CONFIG_NOA_MUX_7_4_DEF                  (0x00000000)
  #define DDRPL_CR_DDR_TRIGGER_CONFIG_MaskMatch_MUX_0_OFF              ( 4)
  #define DDRPL_CR_DDR_TRIGGER_CONFIG_MaskMatch_MUX_0_WID              ( 2)
  #define DDRPL_CR_DDR_TRIGGER_CONFIG_MaskMatch_MUX_0_MSK              (0x00000030)
  #define DDRPL_CR_DDR_TRIGGER_CONFIG_MaskMatch_MUX_0_MAX              (0x00000003)
  #define DDRPL_CR_DDR_TRIGGER_CONFIG_MaskMatch_MUX_0_DEF              (0x00000000)
  #define DDRPL_CR_DDR_TRIGGER_CONFIG_MaskMatch_MUX_1_OFF              ( 6)
  #define DDRPL_CR_DDR_TRIGGER_CONFIG_MaskMatch_MUX_1_WID              ( 2)
  #define DDRPL_CR_DDR_TRIGGER_CONFIG_MaskMatch_MUX_1_MSK              (0x000000C0)
  #define DDRPL_CR_DDR_TRIGGER_CONFIG_MaskMatch_MUX_1_MAX              (0x00000003)
  #define DDRPL_CR_DDR_TRIGGER_CONFIG_MaskMatch_MUX_1_DEF              (0x00000000)
  #define DDRPL_CR_DDR_TRIGGER_CONFIG_MaskMatch_MUX_2_OFF              ( 8)
  #define DDRPL_CR_DDR_TRIGGER_CONFIG_MaskMatch_MUX_2_WID              ( 2)
  #define DDRPL_CR_DDR_TRIGGER_CONFIG_MaskMatch_MUX_2_MSK              (0x00000300)
  #define DDRPL_CR_DDR_TRIGGER_CONFIG_MaskMatch_MUX_2_MAX              (0x00000003)
  #define DDRPL_CR_DDR_TRIGGER_CONFIG_MaskMatch_MUX_2_DEF              (0x00000000)
  #define DDRPL_CR_DDR_TRIGGER_CONFIG_MaskMatch_MUX_3_OFF              (10)
  #define DDRPL_CR_DDR_TRIGGER_CONFIG_MaskMatch_MUX_3_WID              ( 2)
  #define DDRPL_CR_DDR_TRIGGER_CONFIG_MaskMatch_MUX_3_MSK              (0x00000C00)
  #define DDRPL_CR_DDR_TRIGGER_CONFIG_MaskMatch_MUX_3_MAX              (0x00000003)
  #define DDRPL_CR_DDR_TRIGGER_CONFIG_MaskMatch_MUX_3_DEF              (0x00000000)
  #define DDRPL_CR_DDR_TRIGGER_CONFIG_FINAL_MUX_3_0_OFF                (12)
  #define DDRPL_CR_DDR_TRIGGER_CONFIG_FINAL_MUX_3_0_WID                ( 2)
  #define DDRPL_CR_DDR_TRIGGER_CONFIG_FINAL_MUX_3_0_MSK                (0x00003000)
  #define DDRPL_CR_DDR_TRIGGER_CONFIG_FINAL_MUX_3_0_MAX                (0x00000003)
  #define DDRPL_CR_DDR_TRIGGER_CONFIG_FINAL_MUX_3_0_DEF                (0x00000000)
  #define DDRPL_CR_DDR_TRIGGER_CONFIG_FINAL_MUX_7_4_OFF                (14)
  #define DDRPL_CR_DDR_TRIGGER_CONFIG_FINAL_MUX_7_4_WID                ( 2)
  #define DDRPL_CR_DDR_TRIGGER_CONFIG_FINAL_MUX_7_4_MSK                (0x0000C000)
  #define DDRPL_CR_DDR_TRIGGER_CONFIG_FINAL_MUX_7_4_MAX                (0x00000003)
  #define DDRPL_CR_DDR_TRIGGER_CONFIG_FINAL_MUX_7_4_DEF                (0x00000000)
  #define DDRPL_CR_DDR_TRIGGER_CONFIG_SYS_ADDR_RdWr_OFF                (16)
  #define DDRPL_CR_DDR_TRIGGER_CONFIG_SYS_ADDR_RdWr_WID                ( 2)
  #define DDRPL_CR_DDR_TRIGGER_CONFIG_SYS_ADDR_RdWr_MSK                (0x00030000)
  #define DDRPL_CR_DDR_TRIGGER_CONFIG_SYS_ADDR_RdWr_MAX                (0x00000003)
  #define DDRPL_CR_DDR_TRIGGER_CONFIG_SYS_ADDR_RdWr_DEF                (0x00000000)
  #define DDRPL_CR_DDR_TRIGGER_CONFIG_Transaction_match_OFF            (18)
  #define DDRPL_CR_DDR_TRIGGER_CONFIG_Transaction_match_WID            ( 1)
  #define DDRPL_CR_DDR_TRIGGER_CONFIG_Transaction_match_MSK            (0x00040000)
  #define DDRPL_CR_DDR_TRIGGER_CONFIG_Transaction_match_MAX            (0x00000001)
  #define DDRPL_CR_DDR_TRIGGER_CONFIG_Transaction_match_DEF            (0x00000000)
  #define DDRPL_CR_DDR_TRIGGER_CONFIG_DQ_Chunk_Num_OFF                 (19)
  #define DDRPL_CR_DDR_TRIGGER_CONFIG_DQ_Chunk_Num_WID                 ( 3)
  #define DDRPL_CR_DDR_TRIGGER_CONFIG_DQ_Chunk_Num_MSK                 (0x00380000)
  #define DDRPL_CR_DDR_TRIGGER_CONFIG_DQ_Chunk_Num_MAX                 (0x00000007)
  #define DDRPL_CR_DDR_TRIGGER_CONFIG_DQ_Chunk_Num_DEF                 (0x00000000)

#define DDRPL_CR_DDR_ACC_TRIG_MATCH0_REG                             (0x00000C14)
  #define DDRPL_CR_DDR_ACC_TRIG_MATCH0_ACC_OFF                         ( 0)
  #define DDRPL_CR_DDR_ACC_TRIG_MATCH0_ACC_WID                         (32)
  #define DDRPL_CR_DDR_ACC_TRIG_MATCH0_ACC_MSK                         (0xFFFFFFFF)
  #define DDRPL_CR_DDR_ACC_TRIG_MATCH0_ACC_MAX                         (0xFFFFFFFF)
  #define DDRPL_CR_DDR_ACC_TRIG_MATCH0_ACC_DEF                         (0x00000000)

#define DDRPL_CR_DDR_ACC_TRIG_MATCH1_REG                             (0x00000C18)
  #define DDRPL_CR_DDR_ACC_TRIG_MATCH1_ACC_OFF                         ( 0)
  #define DDRPL_CR_DDR_ACC_TRIG_MATCH1_ACC_WID                         (32)
  #define DDRPL_CR_DDR_ACC_TRIG_MATCH1_ACC_MSK                         (0xFFFFFFFF)
  #define DDRPL_CR_DDR_ACC_TRIG_MATCH1_ACC_MAX                         (0xFFFFFFFF)
  #define DDRPL_CR_DDR_ACC_TRIG_MATCH1_ACC_DEF                         (0x00000000)

#define DDRPL_CR_DDR_ACC_TRIG_MATCH2_REG                             (0x00000C1C)
  #define DDRPL_CR_DDR_ACC_TRIG_MATCH2_ACC_OFF                         ( 0)
  #define DDRPL_CR_DDR_ACC_TRIG_MATCH2_ACC_WID                         (32)
  #define DDRPL_CR_DDR_ACC_TRIG_MATCH2_ACC_MSK                         (0xFFFFFFFF)
  #define DDRPL_CR_DDR_ACC_TRIG_MATCH2_ACC_MAX                         (0xFFFFFFFF)
  #define DDRPL_CR_DDR_ACC_TRIG_MATCH2_ACC_DEF                         (0x00000000)

#define DDRPL_CR_DDR_ACC_TRIG_MATCH3_REG                             (0x00000C20)
  #define DDRPL_CR_DDR_ACC_TRIG_MATCH3_ACC_OFF                         ( 0)
  #define DDRPL_CR_DDR_ACC_TRIG_MATCH3_ACC_WID                         (32)
  #define DDRPL_CR_DDR_ACC_TRIG_MATCH3_ACC_MSK                         (0xFFFFFFFF)
  #define DDRPL_CR_DDR_ACC_TRIG_MATCH3_ACC_MAX                         (0xFFFFFFFF)
  #define DDRPL_CR_DDR_ACC_TRIG_MATCH3_ACC_DEF                         (0x00000000)

#define DDRPL_CR_DDR_ACC_TRIG_MASK0_REG                              (0x00000C24)
  #define DDRPL_CR_DDR_ACC_TRIG_MASK0_ACC_OFF                          ( 0)
  #define DDRPL_CR_DDR_ACC_TRIG_MASK0_ACC_WID                          (32)
  #define DDRPL_CR_DDR_ACC_TRIG_MASK0_ACC_MSK                          (0xFFFFFFFF)
  #define DDRPL_CR_DDR_ACC_TRIG_MASK0_ACC_MAX                          (0xFFFFFFFF)
  #define DDRPL_CR_DDR_ACC_TRIG_MASK0_ACC_DEF                          (0x00000000)

#define DDRPL_CR_DDR_ACC_TRIG_MASK1_REG                              (0x00000C28)
  #define DDRPL_CR_DDR_ACC_TRIG_MASK1_ACC_OFF                          ( 0)
  #define DDRPL_CR_DDR_ACC_TRIG_MASK1_ACC_WID                          (32)
  #define DDRPL_CR_DDR_ACC_TRIG_MASK1_ACC_MSK                          (0xFFFFFFFF)
  #define DDRPL_CR_DDR_ACC_TRIG_MASK1_ACC_MAX                          (0xFFFFFFFF)
  #define DDRPL_CR_DDR_ACC_TRIG_MASK1_ACC_DEF                          (0x00000000)

#define DDRPL_CR_DDR_ACC_TRIG_MASK2_REG                              (0x00000C2C)
  #define DDRPL_CR_DDR_ACC_TRIG_MASK2_ACC_OFF                          ( 0)
  #define DDRPL_CR_DDR_ACC_TRIG_MASK2_ACC_WID                          (32)
  #define DDRPL_CR_DDR_ACC_TRIG_MASK2_ACC_MSK                          (0xFFFFFFFF)
  #define DDRPL_CR_DDR_ACC_TRIG_MASK2_ACC_MAX                          (0xFFFFFFFF)
  #define DDRPL_CR_DDR_ACC_TRIG_MASK2_ACC_DEF                          (0x00000000)

#define DDRPL_CR_DDR_ACC_TRIG_MASK3_REG                              (0x00000C30)
  #define DDRPL_CR_DDR_ACC_TRIG_MASK3_ACC_OFF                          ( 0)
  #define DDRPL_CR_DDR_ACC_TRIG_MASK3_ACC_WID                          (32)
  #define DDRPL_CR_DDR_ACC_TRIG_MASK3_ACC_MSK                          (0xFFFFFFFF)
  #define DDRPL_CR_DDR_ACC_TRIG_MASK3_ACC_MAX                          (0xFFFFFFFF)
  #define DDRPL_CR_DDR_ACC_TRIG_MASK3_ACC_DEF                          (0x00000000)

#define DDRPL_CR_DDR_DQ_TRIG_MATCH_LOW_REG                           (0x00000C54)
  #define DDRPL_CR_DDR_DQ_TRIG_MATCH_LOW_DQ_OFF                        ( 0)
  #define DDRPL_CR_DDR_DQ_TRIG_MATCH_LOW_DQ_WID                        (32)
  #define DDRPL_CR_DDR_DQ_TRIG_MATCH_LOW_DQ_MSK                        (0xFFFFFFFF)
  #define DDRPL_CR_DDR_DQ_TRIG_MATCH_LOW_DQ_MAX                        (0xFFFFFFFF)
  #define DDRPL_CR_DDR_DQ_TRIG_MATCH_LOW_DQ_DEF                        (0x00000000)

#define DDRPL_CR_DDR_DQ_TRIG_MASK_LOW_REG                            (0x00000C58)
  #define DDRPL_CR_DDR_DQ_TRIG_MASK_LOW_DQ_OFF                         ( 0)
  #define DDRPL_CR_DDR_DQ_TRIG_MASK_LOW_DQ_WID                         (32)
  #define DDRPL_CR_DDR_DQ_TRIG_MASK_LOW_DQ_MSK                         (0xFFFFFFFF)
  #define DDRPL_CR_DDR_DQ_TRIG_MASK_LOW_DQ_MAX                         (0xFFFFFFFF)
  #define DDRPL_CR_DDR_DQ_TRIG_MASK_LOW_DQ_DEF                         (0x00000000)

#define DDRPL_CR_DDR_DQ_TRIG_MATCH_HIGH_REG                          (0x00000C5C)
  #define DDRPL_CR_DDR_DQ_TRIG_MATCH_HIGH_DQ_OFF                       ( 0)
  #define DDRPL_CR_DDR_DQ_TRIG_MATCH_HIGH_DQ_WID                       (32)
  #define DDRPL_CR_DDR_DQ_TRIG_MATCH_HIGH_DQ_MSK                       (0xFFFFFFFF)
  #define DDRPL_CR_DDR_DQ_TRIG_MATCH_HIGH_DQ_MAX                       (0xFFFFFFFF)
  #define DDRPL_CR_DDR_DQ_TRIG_MATCH_HIGH_DQ_DEF                       (0x00000000)

#define DDRPL_CR_DDR_DQ_TRIG_MASK_HIGH_REG                           (0x00000C60)
  #define DDRPL_CR_DDR_DQ_TRIG_MASK_HIGH_DQ_OFF                        ( 0)
  #define DDRPL_CR_DDR_DQ_TRIG_MASK_HIGH_DQ_WID                        (32)
  #define DDRPL_CR_DDR_DQ_TRIG_MASK_HIGH_DQ_MSK                        (0xFFFFFFFF)
  #define DDRPL_CR_DDR_DQ_TRIG_MASK_HIGH_DQ_MAX                        (0xFFFFFFFF)
  #define DDRPL_CR_DDR_DQ_TRIG_MASK_HIGH_DQ_DEF                        (0x00000000)

#define DDRPL_CR_DDR_ACC_FILTER_MATCH0_REG                           (0x00000C64)
  #define DDRPL_CR_DDR_ACC_FILTER_MATCH0_ACC_OFF                       ( 0)
  #define DDRPL_CR_DDR_ACC_FILTER_MATCH0_ACC_WID                       (32)
  #define DDRPL_CR_DDR_ACC_FILTER_MATCH0_ACC_MSK                       (0xFFFFFFFF)
  #define DDRPL_CR_DDR_ACC_FILTER_MATCH0_ACC_MAX                       (0xFFFFFFFF)
  #define DDRPL_CR_DDR_ACC_FILTER_MATCH0_ACC_DEF                       (0x00000000)

#define DDRPL_CR_DDR_ACC_FILTER_MATCH1_REG                           (0x00000C68)
  #define DDRPL_CR_DDR_ACC_FILTER_MATCH1_ACC_OFF                       ( 0)
  #define DDRPL_CR_DDR_ACC_FILTER_MATCH1_ACC_WID                       (32)
  #define DDRPL_CR_DDR_ACC_FILTER_MATCH1_ACC_MSK                       (0xFFFFFFFF)
  #define DDRPL_CR_DDR_ACC_FILTER_MATCH1_ACC_MAX                       (0xFFFFFFFF)
  #define DDRPL_CR_DDR_ACC_FILTER_MATCH1_ACC_DEF                       (0x00000000)

#define DDRPL_CR_DDR_ACC_FILTER_MASK0_REG                            (0x00000C6C)
  #define DDRPL_CR_DDR_ACC_FILTER_MASK0_ACC_OFF                        ( 0)
  #define DDRPL_CR_DDR_ACC_FILTER_MASK0_ACC_WID                        (32)
  #define DDRPL_CR_DDR_ACC_FILTER_MASK0_ACC_MSK                        (0xFFFFFFFF)
  #define DDRPL_CR_DDR_ACC_FILTER_MASK0_ACC_MAX                        (0xFFFFFFFF)
  #define DDRPL_CR_DDR_ACC_FILTER_MASK0_ACC_DEF                        (0x00000000)

#define DDRPL_CR_DDR_ACC_FILTER_MASK1_REG                            (0x00000C70)
  #define DDRPL_CR_DDR_ACC_FILTER_MASK1_ACC_OFF                        ( 0)
  #define DDRPL_CR_DDR_ACC_FILTER_MASK1_ACC_WID                        (32)
  #define DDRPL_CR_DDR_ACC_FILTER_MASK1_ACC_MSK                        (0xFFFFFFFF)
  #define DDRPL_CR_DDR_ACC_FILTER_MASK1_ACC_MAX                        (0xFFFFFFFF)
  #define DDRPL_CR_DDR_ACC_FILTER_MASK1_ACC_DEF                        (0x00000000)

#define DDRPL_CR_DDR_TRACE_FILTER_CONFIG_REG                         (0x00000C84)
  #define DDRPL_CR_DDR_TRACE_FILTER_CONFIG_ACC_Trace_Enable_OFF        ( 0)
  #define DDRPL_CR_DDR_TRACE_FILTER_CONFIG_ACC_Trace_Enable_WID        ( 1)
  #define DDRPL_CR_DDR_TRACE_FILTER_CONFIG_ACC_Trace_Enable_MSK        (0x00000001)
  #define DDRPL_CR_DDR_TRACE_FILTER_CONFIG_ACC_Trace_Enable_MAX        (0x00000001)
  #define DDRPL_CR_DDR_TRACE_FILTER_CONFIG_ACC_Trace_Enable_DEF        (0x00000000)
  #define DDRPL_CR_DDR_TRACE_FILTER_CONFIG_DQ_Data_Width_OFF           ( 1)
  #define DDRPL_CR_DDR_TRACE_FILTER_CONFIG_DQ_Data_Width_WID           ( 2)
  #define DDRPL_CR_DDR_TRACE_FILTER_CONFIG_DQ_Data_Width_MSK           (0x00000006)
  #define DDRPL_CR_DDR_TRACE_FILTER_CONFIG_DQ_Data_Width_MAX           (0x00000003)
  #define DDRPL_CR_DDR_TRACE_FILTER_CONFIG_DQ_Data_Width_DEF           (0x00000000)
  #define DDRPL_CR_DDR_TRACE_FILTER_CONFIG_ACC_Capture_Mode_OFF        ( 3)
  #define DDRPL_CR_DDR_TRACE_FILTER_CONFIG_ACC_Capture_Mode_WID        ( 1)
  #define DDRPL_CR_DDR_TRACE_FILTER_CONFIG_ACC_Capture_Mode_MSK        (0x00000008)
  #define DDRPL_CR_DDR_TRACE_FILTER_CONFIG_ACC_Capture_Mode_MAX        (0x00000001)
  #define DDRPL_CR_DDR_TRACE_FILTER_CONFIG_ACC_Capture_Mode_DEF        (0x00000001)
  #define DDRPL_CR_DDR_TRACE_FILTER_CONFIG_Read_Rank_Filter_OFF        ( 4)
  #define DDRPL_CR_DDR_TRACE_FILTER_CONFIG_Read_Rank_Filter_WID        ( 4)
  #define DDRPL_CR_DDR_TRACE_FILTER_CONFIG_Read_Rank_Filter_MSK        (0x000000F0)
  #define DDRPL_CR_DDR_TRACE_FILTER_CONFIG_Read_Rank_Filter_MAX        (0x0000000F)
  #define DDRPL_CR_DDR_TRACE_FILTER_CONFIG_Read_Rank_Filter_DEF        (0x00000003)
  #define DDRPL_CR_DDR_TRACE_FILTER_CONFIG_Write_Rank_Filter_OFF       ( 8)
  #define DDRPL_CR_DDR_TRACE_FILTER_CONFIG_Write_Rank_Filter_WID       ( 4)
  #define DDRPL_CR_DDR_TRACE_FILTER_CONFIG_Write_Rank_Filter_MSK       (0x00000F00)
  #define DDRPL_CR_DDR_TRACE_FILTER_CONFIG_Write_Rank_Filter_MAX       (0x0000000F)
  #define DDRPL_CR_DDR_TRACE_FILTER_CONFIG_Write_Rank_Filter_DEF       (0x00000003)
  #define DDRPL_CR_DDR_TRACE_FILTER_CONFIG_Filter_Window_Length_OFF    (12)
  #define DDRPL_CR_DDR_TRACE_FILTER_CONFIG_Filter_Window_Length_WID    ( 8)
  #define DDRPL_CR_DDR_TRACE_FILTER_CONFIG_Filter_Window_Length_MSK    (0x000FF000)
  #define DDRPL_CR_DDR_TRACE_FILTER_CONFIG_Filter_Window_Length_MAX    (0x000000FF)
  #define DDRPL_CR_DDR_TRACE_FILTER_CONFIG_Filter_Window_Length_DEF    (0x00000040)
  #define DDRPL_CR_DDR_TRACE_FILTER_CONFIG_Filter_ACC_OFF              (20)
  #define DDRPL_CR_DDR_TRACE_FILTER_CONFIG_Filter_ACC_WID              ( 1)
  #define DDRPL_CR_DDR_TRACE_FILTER_CONFIG_Filter_ACC_MSK              (0x00100000)
  #define DDRPL_CR_DDR_TRACE_FILTER_CONFIG_Filter_ACC_MAX              (0x00000001)
  #define DDRPL_CR_DDR_TRACE_FILTER_CONFIG_Filter_ACC_DEF              (0x00000000)
  #define DDRPL_CR_DDR_TRACE_FILTER_CONFIG_Filter_DQ_Data_OFF          (21)
  #define DDRPL_CR_DDR_TRACE_FILTER_CONFIG_Filter_DQ_Data_WID          ( 1)
  #define DDRPL_CR_DDR_TRACE_FILTER_CONFIG_Filter_DQ_Data_MSK          (0x00200000)
  #define DDRPL_CR_DDR_TRACE_FILTER_CONFIG_Filter_DQ_Data_MAX          (0x00000001)
  #define DDRPL_CR_DDR_TRACE_FILTER_CONFIG_Filter_DQ_Data_DEF          (0x00000000)
  #define DDRPL_CR_DDR_TRACE_FILTER_CONFIG_Quarter_Mode_Byte_Select_OFF (22)
  #define DDRPL_CR_DDR_TRACE_FILTER_CONFIG_Quarter_Mode_Byte_Select_WID ( 2)
  #define DDRPL_CR_DDR_TRACE_FILTER_CONFIG_Quarter_Mode_Byte_Select_MSK (0x00C00000)
  #define DDRPL_CR_DDR_TRACE_FILTER_CONFIG_Quarter_Mode_Byte_Select_MAX (0x00000003)
  #define DDRPL_CR_DDR_TRACE_FILTER_CONFIG_Quarter_Mode_Byte_Select_DEF (0x00000000)
  #define DDRPL_CR_DDR_TRACE_FILTER_CONFIG_Half_Mode_Byte_Select_OFF   (24)
  #define DDRPL_CR_DDR_TRACE_FILTER_CONFIG_Half_Mode_Byte_Select_WID   ( 1)
  #define DDRPL_CR_DDR_TRACE_FILTER_CONFIG_Half_Mode_Byte_Select_MSK   (0x01000000)
  #define DDRPL_CR_DDR_TRACE_FILTER_CONFIG_Half_Mode_Byte_Select_MAX   (0x00000001)
  #define DDRPL_CR_DDR_TRACE_FILTER_CONFIG_Half_Mode_Byte_Select_DEF   (0x00000000)
  #define DDRPL_CR_DDR_TRACE_FILTER_CONFIG_Filter_Out_OFF              (25)
  #define DDRPL_CR_DDR_TRACE_FILTER_CONFIG_Filter_Out_WID              ( 1)
  #define DDRPL_CR_DDR_TRACE_FILTER_CONFIG_Filter_Out_MSK              (0x02000000)
  #define DDRPL_CR_DDR_TRACE_FILTER_CONFIG_Filter_Out_MAX              (0x00000001)
  #define DDRPL_CR_DDR_TRACE_FILTER_CONFIG_Filter_Out_DEF              (0x00000000)
  #define DDRPL_CR_DDR_TRACE_FILTER_CONFIG_Sys_addr_filter_OFF         (26)
  #define DDRPL_CR_DDR_TRACE_FILTER_CONFIG_Sys_addr_filter_WID         ( 1)
  #define DDRPL_CR_DDR_TRACE_FILTER_CONFIG_Sys_addr_filter_MSK         (0x04000000)
  #define DDRPL_CR_DDR_TRACE_FILTER_CONFIG_Sys_addr_filter_MAX         (0x00000001)
  #define DDRPL_CR_DDR_TRACE_FILTER_CONFIG_Sys_addr_filter_DEF         (0x00000000)
  #define DDRPL_CR_DDR_TRACE_FILTER_CONFIG_Sys_addr_mode_OFF           (27)
  #define DDRPL_CR_DDR_TRACE_FILTER_CONFIG_Sys_addr_mode_WID           ( 1)
  #define DDRPL_CR_DDR_TRACE_FILTER_CONFIG_Sys_addr_mode_MSK           (0x08000000)
  #define DDRPL_CR_DDR_TRACE_FILTER_CONFIG_Sys_addr_mode_MAX           (0x00000001)
  #define DDRPL_CR_DDR_TRACE_FILTER_CONFIG_Sys_addr_mode_DEF           (0x00000000)
  #define DDRPL_CR_DDR_TRACE_FILTER_CONFIG_CMD_Unforce_OFF             (28)
  #define DDRPL_CR_DDR_TRACE_FILTER_CONFIG_CMD_Unforce_WID             ( 1)
  #define DDRPL_CR_DDR_TRACE_FILTER_CONFIG_CMD_Unforce_MSK             (0x10000000)
  #define DDRPL_CR_DDR_TRACE_FILTER_CONFIG_CMD_Unforce_MAX             (0x00000001)
  #define DDRPL_CR_DDR_TRACE_FILTER_CONFIG_CMD_Unforce_DEF             (0x00000000)
  #define DDRPL_CR_DDR_TRACE_FILTER_CONFIG_ACC_qual_mode_OFF           (29)
  #define DDRPL_CR_DDR_TRACE_FILTER_CONFIG_ACC_qual_mode_WID           ( 1)
  #define DDRPL_CR_DDR_TRACE_FILTER_CONFIG_ACC_qual_mode_MSK           (0x20000000)
  #define DDRPL_CR_DDR_TRACE_FILTER_CONFIG_ACC_qual_mode_MAX           (0x00000001)
  #define DDRPL_CR_DDR_TRACE_FILTER_CONFIG_ACC_qual_mode_DEF           (0x00000000)

#define DDRPL_CR_DDR_ACC_FORMAT_SELECT_REG                           (0x00000C88)
  #define DDRPL_CR_DDR_ACC_FORMAT_SELECT_CS_encode_en_OFF              ( 0)
  #define DDRPL_CR_DDR_ACC_FORMAT_SELECT_CS_encode_en_WID              ( 1)
  #define DDRPL_CR_DDR_ACC_FORMAT_SELECT_CS_encode_en_MSK              (0x00000001)
  #define DDRPL_CR_DDR_ACC_FORMAT_SELECT_CS_encode_en_MAX              (0x00000001)
  #define DDRPL_CR_DDR_ACC_FORMAT_SELECT_CS_encode_en_DEF              (0x00000001)
  #define DDRPL_CR_DDR_ACC_FORMAT_SELECT_ODT_Xbar_0_OFF                ( 1)
  #define DDRPL_CR_DDR_ACC_FORMAT_SELECT_ODT_Xbar_0_WID                ( 4)
  #define DDRPL_CR_DDR_ACC_FORMAT_SELECT_ODT_Xbar_0_MSK                (0x0000001E)
  #define DDRPL_CR_DDR_ACC_FORMAT_SELECT_ODT_Xbar_0_MAX                (0x0000000F)
  #define DDRPL_CR_DDR_ACC_FORMAT_SELECT_ODT_Xbar_0_DEF                (0x00000001)
  #define DDRPL_CR_DDR_ACC_FORMAT_SELECT_ODT_Xbar_1_OFF                ( 5)
  #define DDRPL_CR_DDR_ACC_FORMAT_SELECT_ODT_Xbar_1_WID                ( 4)
  #define DDRPL_CR_DDR_ACC_FORMAT_SELECT_ODT_Xbar_1_MSK                (0x000001E0)
  #define DDRPL_CR_DDR_ACC_FORMAT_SELECT_ODT_Xbar_1_MAX                (0x0000000F)
  #define DDRPL_CR_DDR_ACC_FORMAT_SELECT_ODT_Xbar_1_DEF                (0x00000002)
  #define DDRPL_CR_DDR_ACC_FORMAT_SELECT_DDR4_ACC_31_OFF               ( 9)
  #define DDRPL_CR_DDR_ACC_FORMAT_SELECT_DDR4_ACC_31_WID               ( 1)
  #define DDRPL_CR_DDR_ACC_FORMAT_SELECT_DDR4_ACC_31_MSK               (0x00000200)
  #define DDRPL_CR_DDR_ACC_FORMAT_SELECT_DDR4_ACC_31_MAX               (0x00000001)
  #define DDRPL_CR_DDR_ACC_FORMAT_SELECT_DDR4_ACC_31_DEF               (0x00000000)
  #define DDRPL_CR_DDR_ACC_FORMAT_SELECT_DDR4_ACC_30_OFF               (10)
  #define DDRPL_CR_DDR_ACC_FORMAT_SELECT_DDR4_ACC_30_WID               ( 1)
  #define DDRPL_CR_DDR_ACC_FORMAT_SELECT_DDR4_ACC_30_MSK               (0x00000400)
  #define DDRPL_CR_DDR_ACC_FORMAT_SELECT_DDR4_ACC_30_MAX               (0x00000001)
  #define DDRPL_CR_DDR_ACC_FORMAT_SELECT_DDR4_ACC_30_DEF               (0x00000000)
  #define DDRPL_CR_DDR_ACC_FORMAT_SELECT_DDR4_ACC_29_OFF               (11)
  #define DDRPL_CR_DDR_ACC_FORMAT_SELECT_DDR4_ACC_29_WID               ( 1)
  #define DDRPL_CR_DDR_ACC_FORMAT_SELECT_DDR4_ACC_29_MSK               (0x00000800)
  #define DDRPL_CR_DDR_ACC_FORMAT_SELECT_DDR4_ACC_29_MAX               (0x00000001)
  #define DDRPL_CR_DDR_ACC_FORMAT_SELECT_DDR4_ACC_29_DEF               (0x00000000)
  #define DDRPL_CR_DDR_ACC_FORMAT_SELECT_DDR4_ACC_28_OFF               (12)
  #define DDRPL_CR_DDR_ACC_FORMAT_SELECT_DDR4_ACC_28_WID               ( 1)
  #define DDRPL_CR_DDR_ACC_FORMAT_SELECT_DDR4_ACC_28_MSK               (0x00001000)
  #define DDRPL_CR_DDR_ACC_FORMAT_SELECT_DDR4_ACC_28_MAX               (0x00000001)
  #define DDRPL_CR_DDR_ACC_FORMAT_SELECT_DDR4_ACC_28_DEF               (0x00000000)
  #define DDRPL_CR_DDR_ACC_FORMAT_SELECT_DDR4_ACC_27_OFF               (13)
  #define DDRPL_CR_DDR_ACC_FORMAT_SELECT_DDR4_ACC_27_WID               ( 1)
  #define DDRPL_CR_DDR_ACC_FORMAT_SELECT_DDR4_ACC_27_MSK               (0x00002000)
  #define DDRPL_CR_DDR_ACC_FORMAT_SELECT_DDR4_ACC_27_MAX               (0x00000001)
  #define DDRPL_CR_DDR_ACC_FORMAT_SELECT_DDR4_ACC_27_DEF               (0x00000000)
  #define DDRPL_CR_DDR_ACC_FORMAT_SELECT_DDR4_ACC_25_OFF               (14)
  #define DDRPL_CR_DDR_ACC_FORMAT_SELECT_DDR4_ACC_25_WID               ( 1)
  #define DDRPL_CR_DDR_ACC_FORMAT_SELECT_DDR4_ACC_25_MSK               (0x00004000)
  #define DDRPL_CR_DDR_ACC_FORMAT_SELECT_DDR4_ACC_25_MAX               (0x00000001)
  #define DDRPL_CR_DDR_ACC_FORMAT_SELECT_DDR4_ACC_25_DEF               (0x00000000)

#define DDRPL_CR_DDR_TX_LATENCY_HIGH_REG                             (0x00000C8C)
  #define DDRPL_CR_DDR_TX_LATENCY_HIGH_Tx_Latency_R0_OFF               ( 0)
  #define DDRPL_CR_DDR_TX_LATENCY_HIGH_Tx_Latency_R0_WID               ( 8)
  #define DDRPL_CR_DDR_TX_LATENCY_HIGH_Tx_Latency_R0_MSK               (0x000000FF)
  #define DDRPL_CR_DDR_TX_LATENCY_HIGH_Tx_Latency_R0_MAX               (0x000000FF)
  #define DDRPL_CR_DDR_TX_LATENCY_HIGH_Tx_Latency_R0_DEF               (0x00000008)
  #define DDRPL_CR_DDR_TX_LATENCY_HIGH_Tx_Latency_R1_OFF               ( 8)
  #define DDRPL_CR_DDR_TX_LATENCY_HIGH_Tx_Latency_R1_WID               ( 8)
  #define DDRPL_CR_DDR_TX_LATENCY_HIGH_Tx_Latency_R1_MSK               (0x0000FF00)
  #define DDRPL_CR_DDR_TX_LATENCY_HIGH_Tx_Latency_R1_MAX               (0x000000FF)
  #define DDRPL_CR_DDR_TX_LATENCY_HIGH_Tx_Latency_R1_DEF               (0x00000008)
  #define DDRPL_CR_DDR_TX_LATENCY_HIGH_Tx_Latency_R2_OFF               (16)
  #define DDRPL_CR_DDR_TX_LATENCY_HIGH_Tx_Latency_R2_WID               ( 8)
  #define DDRPL_CR_DDR_TX_LATENCY_HIGH_Tx_Latency_R2_MSK               (0x00FF0000)
  #define DDRPL_CR_DDR_TX_LATENCY_HIGH_Tx_Latency_R2_MAX               (0x000000FF)
  #define DDRPL_CR_DDR_TX_LATENCY_HIGH_Tx_Latency_R2_DEF               (0x00000008)
  #define DDRPL_CR_DDR_TX_LATENCY_HIGH_Tx_Latency_R3_OFF               (24)
  #define DDRPL_CR_DDR_TX_LATENCY_HIGH_Tx_Latency_R3_WID               ( 8)
  #define DDRPL_CR_DDR_TX_LATENCY_HIGH_Tx_Latency_R3_MSK               (0xFF000000)
  #define DDRPL_CR_DDR_TX_LATENCY_HIGH_Tx_Latency_R3_MAX               (0x000000FF)
  #define DDRPL_CR_DDR_TX_LATENCY_HIGH_Tx_Latency_R3_DEF               (0x00000008)

#define DDRPL_CR_DDR_RX_LATENCY_HIGH_REG                             (0x00000C90)
  #define DDRPL_CR_DDR_RX_LATENCY_HIGH_Rx_Latency_R0_OFF               ( 0)
  #define DDRPL_CR_DDR_RX_LATENCY_HIGH_Rx_Latency_R0_WID               ( 8)
  #define DDRPL_CR_DDR_RX_LATENCY_HIGH_Rx_Latency_R0_MSK               (0x000000FF)
  #define DDRPL_CR_DDR_RX_LATENCY_HIGH_Rx_Latency_R0_MAX               (0x000000FF)
  #define DDRPL_CR_DDR_RX_LATENCY_HIGH_Rx_Latency_R0_DEF               (0x00000008)
  #define DDRPL_CR_DDR_RX_LATENCY_HIGH_Rx_Latency_R1_OFF               ( 8)
  #define DDRPL_CR_DDR_RX_LATENCY_HIGH_Rx_Latency_R1_WID               ( 8)
  #define DDRPL_CR_DDR_RX_LATENCY_HIGH_Rx_Latency_R1_MSK               (0x0000FF00)
  #define DDRPL_CR_DDR_RX_LATENCY_HIGH_Rx_Latency_R1_MAX               (0x000000FF)
  #define DDRPL_CR_DDR_RX_LATENCY_HIGH_Rx_Latency_R1_DEF               (0x00000008)
  #define DDRPL_CR_DDR_RX_LATENCY_HIGH_Rx_Latency_R2_OFF               (16)
  #define DDRPL_CR_DDR_RX_LATENCY_HIGH_Rx_Latency_R2_WID               ( 8)
  #define DDRPL_CR_DDR_RX_LATENCY_HIGH_Rx_Latency_R2_MSK               (0x00FF0000)
  #define DDRPL_CR_DDR_RX_LATENCY_HIGH_Rx_Latency_R2_MAX               (0x000000FF)
  #define DDRPL_CR_DDR_RX_LATENCY_HIGH_Rx_Latency_R2_DEF               (0x00000008)
  #define DDRPL_CR_DDR_RX_LATENCY_HIGH_Rx_Latency_R3_OFF               (24)
  #define DDRPL_CR_DDR_RX_LATENCY_HIGH_Rx_Latency_R3_WID               ( 8)
  #define DDRPL_CR_DDR_RX_LATENCY_HIGH_Rx_Latency_R3_MSK               (0xFF000000)
  #define DDRPL_CR_DDR_RX_LATENCY_HIGH_Rx_Latency_R3_MAX               (0x000000FF)
  #define DDRPL_CR_DDR_RX_LATENCY_HIGH_Rx_Latency_R3_DEF               (0x00000008)

#define DDRPL_CR_DDR_TX_DELAY_HIGH_REG                               (0x00000C94)
  #define DDRPL_CR_DDR_TX_DELAY_HIGH_Tx_Delay_R0_OFF                   ( 0)
  #define DDRPL_CR_DDR_TX_DELAY_HIGH_Tx_Delay_R0_WID                   ( 8)
  #define DDRPL_CR_DDR_TX_DELAY_HIGH_Tx_Delay_R0_MSK                   (0x000000FF)
  #define DDRPL_CR_DDR_TX_DELAY_HIGH_Tx_Delay_R0_MAX                   (0x000000FF)
  #define DDRPL_CR_DDR_TX_DELAY_HIGH_Tx_Delay_R0_DEF                   (0x00000010)
  #define DDRPL_CR_DDR_TX_DELAY_HIGH_Tx_Delay_R1_OFF                   ( 8)
  #define DDRPL_CR_DDR_TX_DELAY_HIGH_Tx_Delay_R1_WID                   ( 8)
  #define DDRPL_CR_DDR_TX_DELAY_HIGH_Tx_Delay_R1_MSK                   (0x0000FF00)
  #define DDRPL_CR_DDR_TX_DELAY_HIGH_Tx_Delay_R1_MAX                   (0x000000FF)
  #define DDRPL_CR_DDR_TX_DELAY_HIGH_Tx_Delay_R1_DEF                   (0x00000010)
  #define DDRPL_CR_DDR_TX_DELAY_HIGH_Tx_Delay_R2_OFF                   (16)
  #define DDRPL_CR_DDR_TX_DELAY_HIGH_Tx_Delay_R2_WID                   ( 8)
  #define DDRPL_CR_DDR_TX_DELAY_HIGH_Tx_Delay_R2_MSK                   (0x00FF0000)
  #define DDRPL_CR_DDR_TX_DELAY_HIGH_Tx_Delay_R2_MAX                   (0x000000FF)
  #define DDRPL_CR_DDR_TX_DELAY_HIGH_Tx_Delay_R2_DEF                   (0x00000010)
  #define DDRPL_CR_DDR_TX_DELAY_HIGH_Tx_Delay_R3_OFF                   (24)
  #define DDRPL_CR_DDR_TX_DELAY_HIGH_Tx_Delay_R3_WID                   ( 8)
  #define DDRPL_CR_DDR_TX_DELAY_HIGH_Tx_Delay_R3_MSK                   (0xFF000000)
  #define DDRPL_CR_DDR_TX_DELAY_HIGH_Tx_Delay_R3_MAX                   (0x000000FF)
  #define DDRPL_CR_DDR_TX_DELAY_HIGH_Tx_Delay_R3_DEF                   (0x00000010)

#define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM0_REG                    (0x00000CC0)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM0_Signal_In_mode_OFF     ( 0)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM0_Signal_In_mode_WID     ( 4)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM0_Signal_In_mode_MSK     (0x0000000F)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM0_Signal_In_mode_MAX     (0x0000000F)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM0_Signal_In_mode_DEF     (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM0_Event_In_mode_OFF      ( 4)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM0_Event_In_mode_WID      ( 8)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM0_Event_In_mode_MSK      (0x00000FF0)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM0_Event_In_mode_MAX      (0x000000FF)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM0_Event_In_mode_DEF      (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM0_SCT0_match_mode_OFF    (20)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM0_SCT0_match_mode_WID    ( 1)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM0_SCT0_match_mode_MSK    (0x00100000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM0_SCT0_match_mode_MAX    (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM0_SCT0_match_mode_DEF    (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM0_SCT1_match_mode_OFF    (21)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM0_SCT1_match_mode_WID    ( 1)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM0_SCT1_match_mode_MSK    (0x00200000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM0_SCT1_match_mode_MAX    (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM0_SCT1_match_mode_DEF    (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM0_SCT2_match_mode_OFF    (22)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM0_SCT2_match_mode_WID    ( 1)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM0_SCT2_match_mode_MSK    (0x00400000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM0_SCT2_match_mode_MAX    (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM0_SCT2_match_mode_DEF    (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM0_SCT3_match_mode_OFF    (23)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM0_SCT3_match_mode_WID    ( 1)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM0_SCT3_match_mode_MSK    (0x00800000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM0_SCT3_match_mode_MAX    (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM0_SCT3_match_mode_DEF    (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM0_LCT0_match_mode_OFF    (24)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM0_LCT0_match_mode_WID    ( 1)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM0_LCT0_match_mode_MSK    (0x01000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM0_LCT0_match_mode_MAX    (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM0_LCT0_match_mode_DEF    (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM0_LCT1_match_mode_OFF    (25)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM0_LCT1_match_mode_WID    ( 1)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM0_LCT1_match_mode_MSK    (0x02000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM0_LCT1_match_mode_MAX    (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM0_LCT1_match_mode_DEF    (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM0_OP_Type_OFF            (28)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM0_OP_Type_WID            ( 1)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM0_OP_Type_MSK            (0x10000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM0_OP_Type_MAX            (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM0_OP_Type_DEF            (0x00000000)

#define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM1_REG                    (0x00000CC4)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM1_Signal_In_mode_OFF     ( 0)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM1_Signal_In_mode_WID     ( 4)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM1_Signal_In_mode_MSK     (0x0000000F)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM1_Signal_In_mode_MAX     (0x0000000F)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM1_Signal_In_mode_DEF     (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM1_Event_In_mode_OFF      ( 4)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM1_Event_In_mode_WID      ( 8)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM1_Event_In_mode_MSK      (0x00000FF0)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM1_Event_In_mode_MAX      (0x000000FF)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM1_Event_In_mode_DEF      (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM1_SCT0_match_mode_OFF    (20)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM1_SCT0_match_mode_WID    ( 1)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM1_SCT0_match_mode_MSK    (0x00100000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM1_SCT0_match_mode_MAX    (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM1_SCT0_match_mode_DEF    (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM1_SCT1_match_mode_OFF    (21)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM1_SCT1_match_mode_WID    ( 1)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM1_SCT1_match_mode_MSK    (0x00200000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM1_SCT1_match_mode_MAX    (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM1_SCT1_match_mode_DEF    (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM1_SCT2_match_mode_OFF    (22)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM1_SCT2_match_mode_WID    ( 1)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM1_SCT2_match_mode_MSK    (0x00400000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM1_SCT2_match_mode_MAX    (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM1_SCT2_match_mode_DEF    (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM1_SCT3_match_mode_OFF    (23)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM1_SCT3_match_mode_WID    ( 1)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM1_SCT3_match_mode_MSK    (0x00800000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM1_SCT3_match_mode_MAX    (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM1_SCT3_match_mode_DEF    (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM1_LCT0_match_mode_OFF    (24)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM1_LCT0_match_mode_WID    ( 1)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM1_LCT0_match_mode_MSK    (0x01000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM1_LCT0_match_mode_MAX    (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM1_LCT0_match_mode_DEF    (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM1_LCT1_match_mode_OFF    (25)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM1_LCT1_match_mode_WID    ( 1)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM1_LCT1_match_mode_MSK    (0x02000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM1_LCT1_match_mode_MAX    (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM1_LCT1_match_mode_DEF    (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM1_OP_Type_OFF            (28)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM1_OP_Type_WID            ( 1)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM1_OP_Type_MSK            (0x10000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM1_OP_Type_MAX            (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM1_OP_Type_DEF            (0x00000000)

#define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM2_REG                    (0x00000CC8)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM2_Signal_In_mode_OFF     ( 0)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM2_Signal_In_mode_WID     ( 4)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM2_Signal_In_mode_MSK     (0x0000000F)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM2_Signal_In_mode_MAX     (0x0000000F)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM2_Signal_In_mode_DEF     (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM2_Event_In_mode_OFF      ( 4)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM2_Event_In_mode_WID      ( 8)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM2_Event_In_mode_MSK      (0x00000FF0)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM2_Event_In_mode_MAX      (0x000000FF)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM2_Event_In_mode_DEF      (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM2_SCT0_match_mode_OFF    (20)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM2_SCT0_match_mode_WID    ( 1)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM2_SCT0_match_mode_MSK    (0x00100000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM2_SCT0_match_mode_MAX    (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM2_SCT0_match_mode_DEF    (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM2_SCT1_match_mode_OFF    (21)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM2_SCT1_match_mode_WID    ( 1)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM2_SCT1_match_mode_MSK    (0x00200000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM2_SCT1_match_mode_MAX    (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM2_SCT1_match_mode_DEF    (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM2_SCT2_match_mode_OFF    (22)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM2_SCT2_match_mode_WID    ( 1)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM2_SCT2_match_mode_MSK    (0x00400000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM2_SCT2_match_mode_MAX    (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM2_SCT2_match_mode_DEF    (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM2_SCT3_match_mode_OFF    (23)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM2_SCT3_match_mode_WID    ( 1)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM2_SCT3_match_mode_MSK    (0x00800000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM2_SCT3_match_mode_MAX    (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM2_SCT3_match_mode_DEF    (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM2_LCT0_match_mode_OFF    (24)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM2_LCT0_match_mode_WID    ( 1)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM2_LCT0_match_mode_MSK    (0x01000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM2_LCT0_match_mode_MAX    (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM2_LCT0_match_mode_DEF    (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM2_LCT1_match_mode_OFF    (25)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM2_LCT1_match_mode_WID    ( 1)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM2_LCT1_match_mode_MSK    (0x02000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM2_LCT1_match_mode_MAX    (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM2_LCT1_match_mode_DEF    (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM2_OP_Type_OFF            (28)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM2_OP_Type_WID            ( 1)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM2_OP_Type_MSK            (0x10000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM2_OP_Type_MAX            (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM2_OP_Type_DEF            (0x00000000)

#define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM3_REG                    (0x00000CCC)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM3_Signal_In_mode_OFF     ( 0)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM3_Signal_In_mode_WID     ( 4)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM3_Signal_In_mode_MSK     (0x0000000F)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM3_Signal_In_mode_MAX     (0x0000000F)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM3_Signal_In_mode_DEF     (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM3_Event_In_mode_OFF      ( 4)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM3_Event_In_mode_WID      ( 8)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM3_Event_In_mode_MSK      (0x00000FF0)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM3_Event_In_mode_MAX      (0x000000FF)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM3_Event_In_mode_DEF      (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM3_SCT0_match_mode_OFF    (20)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM3_SCT0_match_mode_WID    ( 1)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM3_SCT0_match_mode_MSK    (0x00100000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM3_SCT0_match_mode_MAX    (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM3_SCT0_match_mode_DEF    (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM3_SCT1_match_mode_OFF    (21)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM3_SCT1_match_mode_WID    ( 1)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM3_SCT1_match_mode_MSK    (0x00200000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM3_SCT1_match_mode_MAX    (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM3_SCT1_match_mode_DEF    (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM3_SCT2_match_mode_OFF    (22)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM3_SCT2_match_mode_WID    ( 1)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM3_SCT2_match_mode_MSK    (0x00400000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM3_SCT2_match_mode_MAX    (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM3_SCT2_match_mode_DEF    (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM3_SCT3_match_mode_OFF    (23)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM3_SCT3_match_mode_WID    ( 1)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM3_SCT3_match_mode_MSK    (0x00800000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM3_SCT3_match_mode_MAX    (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM3_SCT3_match_mode_DEF    (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM3_LCT0_match_mode_OFF    (24)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM3_LCT0_match_mode_WID    ( 1)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM3_LCT0_match_mode_MSK    (0x01000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM3_LCT0_match_mode_MAX    (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM3_LCT0_match_mode_DEF    (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM3_LCT1_match_mode_OFF    (25)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM3_LCT1_match_mode_WID    ( 1)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM3_LCT1_match_mode_MSK    (0x02000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM3_LCT1_match_mode_MAX    (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM3_LCT1_match_mode_DEF    (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM3_OP_Type_OFF            (28)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM3_OP_Type_WID            ( 1)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM3_OP_Type_MSK            (0x10000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM3_OP_Type_MAX            (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM3_OP_Type_DEF            (0x00000000)

#define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM4_REG                    (0x00000CD0)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM4_Signal_In_mode_OFF     ( 0)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM4_Signal_In_mode_WID     ( 4)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM4_Signal_In_mode_MSK     (0x0000000F)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM4_Signal_In_mode_MAX     (0x0000000F)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM4_Signal_In_mode_DEF     (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM4_Event_In_mode_OFF      ( 4)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM4_Event_In_mode_WID      ( 8)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM4_Event_In_mode_MSK      (0x00000FF0)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM4_Event_In_mode_MAX      (0x000000FF)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM4_Event_In_mode_DEF      (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM4_SCT0_match_mode_OFF    (20)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM4_SCT0_match_mode_WID    ( 1)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM4_SCT0_match_mode_MSK    (0x00100000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM4_SCT0_match_mode_MAX    (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM4_SCT0_match_mode_DEF    (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM4_SCT1_match_mode_OFF    (21)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM4_SCT1_match_mode_WID    ( 1)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM4_SCT1_match_mode_MSK    (0x00200000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM4_SCT1_match_mode_MAX    (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM4_SCT1_match_mode_DEF    (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM4_SCT2_match_mode_OFF    (22)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM4_SCT2_match_mode_WID    ( 1)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM4_SCT2_match_mode_MSK    (0x00400000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM4_SCT2_match_mode_MAX    (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM4_SCT2_match_mode_DEF    (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM4_SCT3_match_mode_OFF    (23)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM4_SCT3_match_mode_WID    ( 1)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM4_SCT3_match_mode_MSK    (0x00800000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM4_SCT3_match_mode_MAX    (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM4_SCT3_match_mode_DEF    (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM4_LCT0_match_mode_OFF    (24)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM4_LCT0_match_mode_WID    ( 1)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM4_LCT0_match_mode_MSK    (0x01000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM4_LCT0_match_mode_MAX    (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM4_LCT0_match_mode_DEF    (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM4_LCT1_match_mode_OFF    (25)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM4_LCT1_match_mode_WID    ( 1)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM4_LCT1_match_mode_MSK    (0x02000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM4_LCT1_match_mode_MAX    (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM4_LCT1_match_mode_DEF    (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM4_OP_Type_OFF            (28)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM4_OP_Type_WID            ( 1)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM4_OP_Type_MSK            (0x10000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM4_OP_Type_MAX            (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM4_OP_Type_DEF            (0x00000000)

#define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM5_REG                    (0x00000CD4)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM5_Signal_In_mode_OFF     ( 0)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM5_Signal_In_mode_WID     ( 4)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM5_Signal_In_mode_MSK     (0x0000000F)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM5_Signal_In_mode_MAX     (0x0000000F)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM5_Signal_In_mode_DEF     (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM5_Event_In_mode_OFF      ( 4)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM5_Event_In_mode_WID      ( 8)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM5_Event_In_mode_MSK      (0x00000FF0)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM5_Event_In_mode_MAX      (0x000000FF)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM5_Event_In_mode_DEF      (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM5_SCT0_match_mode_OFF    (20)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM5_SCT0_match_mode_WID    ( 1)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM5_SCT0_match_mode_MSK    (0x00100000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM5_SCT0_match_mode_MAX    (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM5_SCT0_match_mode_DEF    (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM5_SCT1_match_mode_OFF    (21)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM5_SCT1_match_mode_WID    ( 1)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM5_SCT1_match_mode_MSK    (0x00200000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM5_SCT1_match_mode_MAX    (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM5_SCT1_match_mode_DEF    (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM5_SCT2_match_mode_OFF    (22)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM5_SCT2_match_mode_WID    ( 1)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM5_SCT2_match_mode_MSK    (0x00400000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM5_SCT2_match_mode_MAX    (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM5_SCT2_match_mode_DEF    (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM5_SCT3_match_mode_OFF    (23)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM5_SCT3_match_mode_WID    ( 1)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM5_SCT3_match_mode_MSK    (0x00800000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM5_SCT3_match_mode_MAX    (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM5_SCT3_match_mode_DEF    (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM5_LCT0_match_mode_OFF    (24)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM5_LCT0_match_mode_WID    ( 1)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM5_LCT0_match_mode_MSK    (0x01000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM5_LCT0_match_mode_MAX    (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM5_LCT0_match_mode_DEF    (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM5_LCT1_match_mode_OFF    (25)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM5_LCT1_match_mode_WID    ( 1)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM5_LCT1_match_mode_MSK    (0x02000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM5_LCT1_match_mode_MAX    (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM5_LCT1_match_mode_DEF    (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM5_OP_Type_OFF            (28)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM5_OP_Type_WID            ( 1)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM5_OP_Type_MSK            (0x10000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM5_OP_Type_MAX            (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM5_OP_Type_DEF            (0x00000000)

#define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM6_REG                    (0x00000CD8)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM6_Signal_In_mode_OFF     ( 0)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM6_Signal_In_mode_WID     ( 4)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM6_Signal_In_mode_MSK     (0x0000000F)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM6_Signal_In_mode_MAX     (0x0000000F)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM6_Signal_In_mode_DEF     (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM6_Event_In_mode_OFF      ( 4)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM6_Event_In_mode_WID      ( 8)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM6_Event_In_mode_MSK      (0x00000FF0)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM6_Event_In_mode_MAX      (0x000000FF)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM6_Event_In_mode_DEF      (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM6_SCT0_match_mode_OFF    (20)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM6_SCT0_match_mode_WID    ( 1)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM6_SCT0_match_mode_MSK    (0x00100000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM6_SCT0_match_mode_MAX    (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM6_SCT0_match_mode_DEF    (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM6_SCT1_match_mode_OFF    (21)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM6_SCT1_match_mode_WID    ( 1)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM6_SCT1_match_mode_MSK    (0x00200000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM6_SCT1_match_mode_MAX    (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM6_SCT1_match_mode_DEF    (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM6_SCT2_match_mode_OFF    (22)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM6_SCT2_match_mode_WID    ( 1)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM6_SCT2_match_mode_MSK    (0x00400000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM6_SCT2_match_mode_MAX    (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM6_SCT2_match_mode_DEF    (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM6_SCT3_match_mode_OFF    (23)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM6_SCT3_match_mode_WID    ( 1)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM6_SCT3_match_mode_MSK    (0x00800000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM6_SCT3_match_mode_MAX    (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM6_SCT3_match_mode_DEF    (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM6_LCT0_match_mode_OFF    (24)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM6_LCT0_match_mode_WID    ( 1)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM6_LCT0_match_mode_MSK    (0x01000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM6_LCT0_match_mode_MAX    (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM6_LCT0_match_mode_DEF    (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM6_LCT1_match_mode_OFF    (25)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM6_LCT1_match_mode_WID    ( 1)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM6_LCT1_match_mode_MSK    (0x02000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM6_LCT1_match_mode_MAX    (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM6_LCT1_match_mode_DEF    (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM6_OP_Type_OFF            (28)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM6_OP_Type_WID            ( 1)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM6_OP_Type_MSK            (0x10000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM6_OP_Type_MAX            (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM6_OP_Type_DEF            (0x00000000)

#define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM7_REG                    (0x00000CDC)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM7_Signal_In_mode_OFF     ( 0)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM7_Signal_In_mode_WID     ( 4)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM7_Signal_In_mode_MSK     (0x0000000F)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM7_Signal_In_mode_MAX     (0x0000000F)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM7_Signal_In_mode_DEF     (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM7_Event_In_mode_OFF      ( 4)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM7_Event_In_mode_WID      ( 8)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM7_Event_In_mode_MSK      (0x00000FF0)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM7_Event_In_mode_MAX      (0x000000FF)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM7_Event_In_mode_DEF      (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM7_SCT0_match_mode_OFF    (20)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM7_SCT0_match_mode_WID    ( 1)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM7_SCT0_match_mode_MSK    (0x00100000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM7_SCT0_match_mode_MAX    (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM7_SCT0_match_mode_DEF    (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM7_SCT1_match_mode_OFF    (21)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM7_SCT1_match_mode_WID    ( 1)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM7_SCT1_match_mode_MSK    (0x00200000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM7_SCT1_match_mode_MAX    (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM7_SCT1_match_mode_DEF    (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM7_SCT2_match_mode_OFF    (22)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM7_SCT2_match_mode_WID    ( 1)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM7_SCT2_match_mode_MSK    (0x00400000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM7_SCT2_match_mode_MAX    (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM7_SCT2_match_mode_DEF    (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM7_SCT3_match_mode_OFF    (23)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM7_SCT3_match_mode_WID    ( 1)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM7_SCT3_match_mode_MSK    (0x00800000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM7_SCT3_match_mode_MAX    (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM7_SCT3_match_mode_DEF    (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM7_LCT0_match_mode_OFF    (24)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM7_LCT0_match_mode_WID    ( 1)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM7_LCT0_match_mode_MSK    (0x01000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM7_LCT0_match_mode_MAX    (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM7_LCT0_match_mode_DEF    (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM7_LCT1_match_mode_OFF    (25)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM7_LCT1_match_mode_WID    ( 1)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM7_LCT1_match_mode_MSK    (0x02000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM7_LCT1_match_mode_MAX    (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM7_LCT1_match_mode_DEF    (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM7_OP_Type_OFF            (28)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM7_OP_Type_WID            ( 1)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM7_OP_Type_MSK            (0x10000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM7_OP_Type_MAX            (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM7_OP_Type_DEF            (0x00000000)

#define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM8_REG                    (0x00000CE0)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM8_Signal_In_mode_OFF     ( 0)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM8_Signal_In_mode_WID     ( 4)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM8_Signal_In_mode_MSK     (0x0000000F)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM8_Signal_In_mode_MAX     (0x0000000F)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM8_Signal_In_mode_DEF     (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM8_Event_In_mode_OFF      ( 4)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM8_Event_In_mode_WID      ( 8)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM8_Event_In_mode_MSK      (0x00000FF0)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM8_Event_In_mode_MAX      (0x000000FF)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM8_Event_In_mode_DEF      (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM8_SCT0_match_mode_OFF    (20)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM8_SCT0_match_mode_WID    ( 1)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM8_SCT0_match_mode_MSK    (0x00100000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM8_SCT0_match_mode_MAX    (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM8_SCT0_match_mode_DEF    (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM8_SCT1_match_mode_OFF    (21)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM8_SCT1_match_mode_WID    ( 1)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM8_SCT1_match_mode_MSK    (0x00200000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM8_SCT1_match_mode_MAX    (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM8_SCT1_match_mode_DEF    (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM8_SCT2_match_mode_OFF    (22)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM8_SCT2_match_mode_WID    ( 1)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM8_SCT2_match_mode_MSK    (0x00400000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM8_SCT2_match_mode_MAX    (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM8_SCT2_match_mode_DEF    (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM8_SCT3_match_mode_OFF    (23)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM8_SCT3_match_mode_WID    ( 1)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM8_SCT3_match_mode_MSK    (0x00800000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM8_SCT3_match_mode_MAX    (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM8_SCT3_match_mode_DEF    (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM8_LCT0_match_mode_OFF    (24)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM8_LCT0_match_mode_WID    ( 1)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM8_LCT0_match_mode_MSK    (0x01000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM8_LCT0_match_mode_MAX    (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM8_LCT0_match_mode_DEF    (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM8_LCT1_match_mode_OFF    (25)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM8_LCT1_match_mode_WID    ( 1)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM8_LCT1_match_mode_MSK    (0x02000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM8_LCT1_match_mode_MAX    (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM8_LCT1_match_mode_DEF    (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM8_OP_Type_OFF            (28)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM8_OP_Type_WID            ( 1)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM8_OP_Type_MSK            (0x10000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM8_OP_Type_MAX            (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM8_OP_Type_DEF            (0x00000000)

#define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM9_REG                    (0x00000CE4)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM9_Signal_In_mode_OFF     ( 0)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM9_Signal_In_mode_WID     ( 4)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM9_Signal_In_mode_MSK     (0x0000000F)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM9_Signal_In_mode_MAX     (0x0000000F)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM9_Signal_In_mode_DEF     (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM9_Event_In_mode_OFF      ( 4)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM9_Event_In_mode_WID      ( 8)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM9_Event_In_mode_MSK      (0x00000FF0)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM9_Event_In_mode_MAX      (0x000000FF)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM9_Event_In_mode_DEF      (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM9_SCT0_match_mode_OFF    (20)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM9_SCT0_match_mode_WID    ( 1)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM9_SCT0_match_mode_MSK    (0x00100000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM9_SCT0_match_mode_MAX    (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM9_SCT0_match_mode_DEF    (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM9_SCT1_match_mode_OFF    (21)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM9_SCT1_match_mode_WID    ( 1)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM9_SCT1_match_mode_MSK    (0x00200000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM9_SCT1_match_mode_MAX    (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM9_SCT1_match_mode_DEF    (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM9_SCT2_match_mode_OFF    (22)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM9_SCT2_match_mode_WID    ( 1)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM9_SCT2_match_mode_MSK    (0x00400000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM9_SCT2_match_mode_MAX    (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM9_SCT2_match_mode_DEF    (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM9_SCT3_match_mode_OFF    (23)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM9_SCT3_match_mode_WID    ( 1)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM9_SCT3_match_mode_MSK    (0x00800000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM9_SCT3_match_mode_MAX    (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM9_SCT3_match_mode_DEF    (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM9_LCT0_match_mode_OFF    (24)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM9_LCT0_match_mode_WID    ( 1)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM9_LCT0_match_mode_MSK    (0x01000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM9_LCT0_match_mode_MAX    (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM9_LCT0_match_mode_DEF    (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM9_LCT1_match_mode_OFF    (25)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM9_LCT1_match_mode_WID    ( 1)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM9_LCT1_match_mode_MSK    (0x02000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM9_LCT1_match_mode_MAX    (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM9_LCT1_match_mode_DEF    (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM9_OP_Type_OFF            (28)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM9_OP_Type_WID            ( 1)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM9_OP_Type_MSK            (0x10000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM9_OP_Type_MAX            (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM9_OP_Type_DEF            (0x00000000)

#define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM10_REG                   (0x00000CE8)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM10_Signal_In_mode_OFF    ( 0)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM10_Signal_In_mode_WID    ( 4)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM10_Signal_In_mode_MSK    (0x0000000F)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM10_Signal_In_mode_MAX    (0x0000000F)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM10_Signal_In_mode_DEF    (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM10_Event_In_mode_OFF     ( 4)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM10_Event_In_mode_WID     ( 8)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM10_Event_In_mode_MSK     (0x00000FF0)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM10_Event_In_mode_MAX     (0x000000FF)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM10_Event_In_mode_DEF     (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM10_SCT0_match_mode_OFF   (20)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM10_SCT0_match_mode_WID   ( 1)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM10_SCT0_match_mode_MSK   (0x00100000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM10_SCT0_match_mode_MAX   (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM10_SCT0_match_mode_DEF   (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM10_SCT1_match_mode_OFF   (21)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM10_SCT1_match_mode_WID   ( 1)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM10_SCT1_match_mode_MSK   (0x00200000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM10_SCT1_match_mode_MAX   (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM10_SCT1_match_mode_DEF   (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM10_SCT2_match_mode_OFF   (22)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM10_SCT2_match_mode_WID   ( 1)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM10_SCT2_match_mode_MSK   (0x00400000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM10_SCT2_match_mode_MAX   (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM10_SCT2_match_mode_DEF   (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM10_SCT3_match_mode_OFF   (23)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM10_SCT3_match_mode_WID   ( 1)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM10_SCT3_match_mode_MSK   (0x00800000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM10_SCT3_match_mode_MAX   (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM10_SCT3_match_mode_DEF   (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM10_LCT0_match_mode_OFF   (24)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM10_LCT0_match_mode_WID   ( 1)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM10_LCT0_match_mode_MSK   (0x01000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM10_LCT0_match_mode_MAX   (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM10_LCT0_match_mode_DEF   (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM10_LCT1_match_mode_OFF   (25)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM10_LCT1_match_mode_WID   ( 1)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM10_LCT1_match_mode_MSK   (0x02000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM10_LCT1_match_mode_MAX   (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM10_LCT1_match_mode_DEF   (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM10_OP_Type_OFF           (28)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM10_OP_Type_WID           ( 1)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM10_OP_Type_MSK           (0x10000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM10_OP_Type_MAX           (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM10_OP_Type_DEF           (0x00000000)

#define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM11_REG                   (0x00000CEC)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM11_Signal_In_mode_OFF    ( 0)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM11_Signal_In_mode_WID    ( 4)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM11_Signal_In_mode_MSK    (0x0000000F)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM11_Signal_In_mode_MAX    (0x0000000F)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM11_Signal_In_mode_DEF    (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM11_Event_In_mode_OFF     ( 4)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM11_Event_In_mode_WID     ( 8)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM11_Event_In_mode_MSK     (0x00000FF0)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM11_Event_In_mode_MAX     (0x000000FF)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM11_Event_In_mode_DEF     (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM11_SCT0_match_mode_OFF   (20)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM11_SCT0_match_mode_WID   ( 1)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM11_SCT0_match_mode_MSK   (0x00100000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM11_SCT0_match_mode_MAX   (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM11_SCT0_match_mode_DEF   (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM11_SCT1_match_mode_OFF   (21)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM11_SCT1_match_mode_WID   ( 1)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM11_SCT1_match_mode_MSK   (0x00200000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM11_SCT1_match_mode_MAX   (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM11_SCT1_match_mode_DEF   (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM11_SCT2_match_mode_OFF   (22)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM11_SCT2_match_mode_WID   ( 1)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM11_SCT2_match_mode_MSK   (0x00400000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM11_SCT2_match_mode_MAX   (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM11_SCT2_match_mode_DEF   (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM11_SCT3_match_mode_OFF   (23)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM11_SCT3_match_mode_WID   ( 1)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM11_SCT3_match_mode_MSK   (0x00800000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM11_SCT3_match_mode_MAX   (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM11_SCT3_match_mode_DEF   (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM11_LCT0_match_mode_OFF   (24)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM11_LCT0_match_mode_WID   ( 1)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM11_LCT0_match_mode_MSK   (0x01000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM11_LCT0_match_mode_MAX   (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM11_LCT0_match_mode_DEF   (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM11_LCT1_match_mode_OFF   (25)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM11_LCT1_match_mode_WID   ( 1)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM11_LCT1_match_mode_MSK   (0x02000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM11_LCT1_match_mode_MAX   (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM11_LCT1_match_mode_DEF   (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM11_OP_Type_OFF           (28)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM11_OP_Type_WID           ( 1)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM11_OP_Type_MSK           (0x10000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM11_OP_Type_MAX           (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM11_OP_Type_DEF           (0x00000000)

#define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM12_REG                   (0x00000CF0)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM12_Signal_In_mode_OFF    ( 0)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM12_Signal_In_mode_WID    ( 4)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM12_Signal_In_mode_MSK    (0x0000000F)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM12_Signal_In_mode_MAX    (0x0000000F)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM12_Signal_In_mode_DEF    (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM12_Event_In_mode_OFF     ( 4)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM12_Event_In_mode_WID     ( 8)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM12_Event_In_mode_MSK     (0x00000FF0)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM12_Event_In_mode_MAX     (0x000000FF)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM12_Event_In_mode_DEF     (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM12_SCT0_match_mode_OFF   (20)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM12_SCT0_match_mode_WID   ( 1)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM12_SCT0_match_mode_MSK   (0x00100000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM12_SCT0_match_mode_MAX   (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM12_SCT0_match_mode_DEF   (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM12_SCT1_match_mode_OFF   (21)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM12_SCT1_match_mode_WID   ( 1)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM12_SCT1_match_mode_MSK   (0x00200000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM12_SCT1_match_mode_MAX   (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM12_SCT1_match_mode_DEF   (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM12_SCT2_match_mode_OFF   (22)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM12_SCT2_match_mode_WID   ( 1)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM12_SCT2_match_mode_MSK   (0x00400000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM12_SCT2_match_mode_MAX   (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM12_SCT2_match_mode_DEF   (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM12_SCT3_match_mode_OFF   (23)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM12_SCT3_match_mode_WID   ( 1)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM12_SCT3_match_mode_MSK   (0x00800000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM12_SCT3_match_mode_MAX   (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM12_SCT3_match_mode_DEF   (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM12_LCT0_match_mode_OFF   (24)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM12_LCT0_match_mode_WID   ( 1)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM12_LCT0_match_mode_MSK   (0x01000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM12_LCT0_match_mode_MAX   (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM12_LCT0_match_mode_DEF   (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM12_LCT1_match_mode_OFF   (25)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM12_LCT1_match_mode_WID   ( 1)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM12_LCT1_match_mode_MSK   (0x02000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM12_LCT1_match_mode_MAX   (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM12_LCT1_match_mode_DEF   (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM12_OP_Type_OFF           (28)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM12_OP_Type_WID           ( 1)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM12_OP_Type_MSK           (0x10000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM12_OP_Type_MAX           (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM12_OP_Type_DEF           (0x00000000)

#define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM13_REG                   (0x00000CF4)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM13_Signal_In_mode_OFF    ( 0)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM13_Signal_In_mode_WID    ( 4)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM13_Signal_In_mode_MSK    (0x0000000F)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM13_Signal_In_mode_MAX    (0x0000000F)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM13_Signal_In_mode_DEF    (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM13_Event_In_mode_OFF     ( 4)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM13_Event_In_mode_WID     ( 8)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM13_Event_In_mode_MSK     (0x00000FF0)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM13_Event_In_mode_MAX     (0x000000FF)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM13_Event_In_mode_DEF     (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM13_SCT0_match_mode_OFF   (20)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM13_SCT0_match_mode_WID   ( 1)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM13_SCT0_match_mode_MSK   (0x00100000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM13_SCT0_match_mode_MAX   (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM13_SCT0_match_mode_DEF   (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM13_SCT1_match_mode_OFF   (21)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM13_SCT1_match_mode_WID   ( 1)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM13_SCT1_match_mode_MSK   (0x00200000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM13_SCT1_match_mode_MAX   (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM13_SCT1_match_mode_DEF   (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM13_SCT2_match_mode_OFF   (22)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM13_SCT2_match_mode_WID   ( 1)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM13_SCT2_match_mode_MSK   (0x00400000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM13_SCT2_match_mode_MAX   (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM13_SCT2_match_mode_DEF   (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM13_SCT3_match_mode_OFF   (23)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM13_SCT3_match_mode_WID   ( 1)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM13_SCT3_match_mode_MSK   (0x00800000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM13_SCT3_match_mode_MAX   (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM13_SCT3_match_mode_DEF   (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM13_LCT0_match_mode_OFF   (24)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM13_LCT0_match_mode_WID   ( 1)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM13_LCT0_match_mode_MSK   (0x01000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM13_LCT0_match_mode_MAX   (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM13_LCT0_match_mode_DEF   (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM13_LCT1_match_mode_OFF   (25)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM13_LCT1_match_mode_WID   ( 1)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM13_LCT1_match_mode_MSK   (0x02000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM13_LCT1_match_mode_MAX   (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM13_LCT1_match_mode_DEF   (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM13_OP_Type_OFF           (28)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM13_OP_Type_WID           ( 1)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM13_OP_Type_MSK           (0x10000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM13_OP_Type_MAX           (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM13_OP_Type_DEF           (0x00000000)

#define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM14_REG                   (0x00000CF8)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM14_Signal_In_mode_OFF    ( 0)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM14_Signal_In_mode_WID    ( 4)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM14_Signal_In_mode_MSK    (0x0000000F)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM14_Signal_In_mode_MAX    (0x0000000F)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM14_Signal_In_mode_DEF    (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM14_Event_In_mode_OFF     ( 4)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM14_Event_In_mode_WID     ( 8)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM14_Event_In_mode_MSK     (0x00000FF0)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM14_Event_In_mode_MAX     (0x000000FF)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM14_Event_In_mode_DEF     (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM14_SCT0_match_mode_OFF   (20)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM14_SCT0_match_mode_WID   ( 1)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM14_SCT0_match_mode_MSK   (0x00100000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM14_SCT0_match_mode_MAX   (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM14_SCT0_match_mode_DEF   (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM14_SCT1_match_mode_OFF   (21)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM14_SCT1_match_mode_WID   ( 1)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM14_SCT1_match_mode_MSK   (0x00200000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM14_SCT1_match_mode_MAX   (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM14_SCT1_match_mode_DEF   (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM14_SCT2_match_mode_OFF   (22)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM14_SCT2_match_mode_WID   ( 1)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM14_SCT2_match_mode_MSK   (0x00400000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM14_SCT2_match_mode_MAX   (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM14_SCT2_match_mode_DEF   (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM14_SCT3_match_mode_OFF   (23)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM14_SCT3_match_mode_WID   ( 1)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM14_SCT3_match_mode_MSK   (0x00800000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM14_SCT3_match_mode_MAX   (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM14_SCT3_match_mode_DEF   (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM14_LCT0_match_mode_OFF   (24)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM14_LCT0_match_mode_WID   ( 1)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM14_LCT0_match_mode_MSK   (0x01000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM14_LCT0_match_mode_MAX   (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM14_LCT0_match_mode_DEF   (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM14_LCT1_match_mode_OFF   (25)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM14_LCT1_match_mode_WID   ( 1)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM14_LCT1_match_mode_MSK   (0x02000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM14_LCT1_match_mode_MAX   (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM14_LCT1_match_mode_DEF   (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM14_OP_Type_OFF           (28)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM14_OP_Type_WID           ( 1)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM14_OP_Type_MSK           (0x10000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM14_OP_Type_MAX           (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM14_OP_Type_DEF           (0x00000000)

#define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM15_REG                   (0x00000CFC)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM15_Signal_In_mode_OFF    ( 0)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM15_Signal_In_mode_WID    ( 4)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM15_Signal_In_mode_MSK    (0x0000000F)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM15_Signal_In_mode_MAX    (0x0000000F)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM15_Signal_In_mode_DEF    (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM15_Event_In_mode_OFF     ( 4)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM15_Event_In_mode_WID     ( 8)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM15_Event_In_mode_MSK     (0x00000FF0)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM15_Event_In_mode_MAX     (0x000000FF)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM15_Event_In_mode_DEF     (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM15_SCT0_match_mode_OFF   (20)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM15_SCT0_match_mode_WID   ( 1)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM15_SCT0_match_mode_MSK   (0x00100000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM15_SCT0_match_mode_MAX   (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM15_SCT0_match_mode_DEF   (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM15_SCT1_match_mode_OFF   (21)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM15_SCT1_match_mode_WID   ( 1)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM15_SCT1_match_mode_MSK   (0x00200000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM15_SCT1_match_mode_MAX   (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM15_SCT1_match_mode_DEF   (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM15_SCT2_match_mode_OFF   (22)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM15_SCT2_match_mode_WID   ( 1)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM15_SCT2_match_mode_MSK   (0x00400000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM15_SCT2_match_mode_MAX   (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM15_SCT2_match_mode_DEF   (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM15_SCT3_match_mode_OFF   (23)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM15_SCT3_match_mode_WID   ( 1)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM15_SCT3_match_mode_MSK   (0x00800000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM15_SCT3_match_mode_MAX   (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM15_SCT3_match_mode_DEF   (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM15_LCT0_match_mode_OFF   (24)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM15_LCT0_match_mode_WID   ( 1)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM15_LCT0_match_mode_MSK   (0x01000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM15_LCT0_match_mode_MAX   (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM15_LCT0_match_mode_DEF   (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM15_LCT1_match_mode_OFF   (25)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM15_LCT1_match_mode_WID   ( 1)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM15_LCT1_match_mode_MSK   (0x02000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM15_LCT1_match_mode_MAX   (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM15_LCT1_match_mode_DEF   (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM15_OP_Type_OFF           (28)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM15_OP_Type_WID           ( 1)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM15_OP_Type_MSK           (0x10000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM15_OP_Type_MAX           (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_MODE_CN_SM15_OP_Type_DEF           (0x00000000)

#define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM0_REG                  (0x00000D00)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM0_Signal_In_select_OFF ( 0)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM0_Signal_In_select_WID ( 4)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM0_Signal_In_select_MSK (0x0000000F)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM0_Signal_In_select_MAX (0x0000000F)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM0_Signal_In_select_DEF (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM0_Event_In_select_OFF  ( 4)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM0_Event_In_select_WID  ( 8)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM0_Event_In_select_MSK  (0x00000FF0)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM0_Event_In_select_MAX  (0x000000FF)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM0_Event_In_select_DEF  (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM0_SCT0_select_OFF      (20)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM0_SCT0_select_WID      ( 1)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM0_SCT0_select_MSK      (0x00100000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM0_SCT0_select_MAX      (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM0_SCT0_select_DEF      (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM0_SCT1_select_OFF      (21)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM0_SCT1_select_WID      ( 1)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM0_SCT1_select_MSK      (0x00200000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM0_SCT1_select_MAX      (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM0_SCT1_select_DEF      (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM0_SCT2_select_OFF      (22)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM0_SCT2_select_WID      ( 1)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM0_SCT2_select_MSK      (0x00400000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM0_SCT2_select_MAX      (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM0_SCT2_select_DEF      (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM0_SCT3_select_OFF      (23)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM0_SCT3_select_WID      ( 1)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM0_SCT3_select_MSK      (0x00800000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM0_SCT3_select_MAX      (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM0_SCT3_select_DEF      (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM0_LCT0_select_OFF      (24)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM0_LCT0_select_WID      ( 1)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM0_LCT0_select_MSK      (0x01000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM0_LCT0_select_MAX      (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM0_LCT0_select_DEF      (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM0_LCT1_select_OFF      (25)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM0_LCT1_select_WID      ( 1)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM0_LCT1_select_MSK      (0x02000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM0_LCT1_select_MAX      (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM0_LCT1_select_DEF      (0x00000000)

#define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM1_REG                  (0x00000D04)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM1_Signal_In_select_OFF ( 0)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM1_Signal_In_select_WID ( 4)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM1_Signal_In_select_MSK (0x0000000F)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM1_Signal_In_select_MAX (0x0000000F)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM1_Signal_In_select_DEF (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM1_Event_In_select_OFF  ( 4)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM1_Event_In_select_WID  ( 8)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM1_Event_In_select_MSK  (0x00000FF0)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM1_Event_In_select_MAX  (0x000000FF)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM1_Event_In_select_DEF  (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM1_SCT0_select_OFF      (20)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM1_SCT0_select_WID      ( 1)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM1_SCT0_select_MSK      (0x00100000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM1_SCT0_select_MAX      (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM1_SCT0_select_DEF      (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM1_SCT1_select_OFF      (21)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM1_SCT1_select_WID      ( 1)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM1_SCT1_select_MSK      (0x00200000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM1_SCT1_select_MAX      (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM1_SCT1_select_DEF      (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM1_SCT2_select_OFF      (22)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM1_SCT2_select_WID      ( 1)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM1_SCT2_select_MSK      (0x00400000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM1_SCT2_select_MAX      (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM1_SCT2_select_DEF      (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM1_SCT3_select_OFF      (23)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM1_SCT3_select_WID      ( 1)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM1_SCT3_select_MSK      (0x00800000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM1_SCT3_select_MAX      (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM1_SCT3_select_DEF      (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM1_LCT0_select_OFF      (24)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM1_LCT0_select_WID      ( 1)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM1_LCT0_select_MSK      (0x01000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM1_LCT0_select_MAX      (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM1_LCT0_select_DEF      (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM1_LCT1_select_OFF      (25)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM1_LCT1_select_WID      ( 1)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM1_LCT1_select_MSK      (0x02000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM1_LCT1_select_MAX      (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM1_LCT1_select_DEF      (0x00000000)

#define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM2_REG                  (0x00000D08)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM2_Signal_In_select_OFF ( 0)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM2_Signal_In_select_WID ( 4)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM2_Signal_In_select_MSK (0x0000000F)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM2_Signal_In_select_MAX (0x0000000F)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM2_Signal_In_select_DEF (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM2_Event_In_select_OFF  ( 4)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM2_Event_In_select_WID  ( 8)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM2_Event_In_select_MSK  (0x00000FF0)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM2_Event_In_select_MAX  (0x000000FF)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM2_Event_In_select_DEF  (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM2_SCT0_select_OFF      (20)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM2_SCT0_select_WID      ( 1)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM2_SCT0_select_MSK      (0x00100000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM2_SCT0_select_MAX      (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM2_SCT0_select_DEF      (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM2_SCT1_select_OFF      (21)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM2_SCT1_select_WID      ( 1)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM2_SCT1_select_MSK      (0x00200000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM2_SCT1_select_MAX      (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM2_SCT1_select_DEF      (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM2_SCT2_select_OFF      (22)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM2_SCT2_select_WID      ( 1)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM2_SCT2_select_MSK      (0x00400000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM2_SCT2_select_MAX      (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM2_SCT2_select_DEF      (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM2_SCT3_select_OFF      (23)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM2_SCT3_select_WID      ( 1)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM2_SCT3_select_MSK      (0x00800000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM2_SCT3_select_MAX      (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM2_SCT3_select_DEF      (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM2_LCT0_select_OFF      (24)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM2_LCT0_select_WID      ( 1)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM2_LCT0_select_MSK      (0x01000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM2_LCT0_select_MAX      (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM2_LCT0_select_DEF      (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM2_LCT1_select_OFF      (25)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM2_LCT1_select_WID      ( 1)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM2_LCT1_select_MSK      (0x02000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM2_LCT1_select_MAX      (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM2_LCT1_select_DEF      (0x00000000)

#define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM3_REG                  (0x00000D0C)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM3_Signal_In_select_OFF ( 0)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM3_Signal_In_select_WID ( 4)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM3_Signal_In_select_MSK (0x0000000F)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM3_Signal_In_select_MAX (0x0000000F)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM3_Signal_In_select_DEF (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM3_Event_In_select_OFF  ( 4)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM3_Event_In_select_WID  ( 8)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM3_Event_In_select_MSK  (0x00000FF0)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM3_Event_In_select_MAX  (0x000000FF)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM3_Event_In_select_DEF  (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM3_SCT0_select_OFF      (20)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM3_SCT0_select_WID      ( 1)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM3_SCT0_select_MSK      (0x00100000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM3_SCT0_select_MAX      (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM3_SCT0_select_DEF      (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM3_SCT1_select_OFF      (21)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM3_SCT1_select_WID      ( 1)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM3_SCT1_select_MSK      (0x00200000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM3_SCT1_select_MAX      (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM3_SCT1_select_DEF      (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM3_SCT2_select_OFF      (22)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM3_SCT2_select_WID      ( 1)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM3_SCT2_select_MSK      (0x00400000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM3_SCT2_select_MAX      (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM3_SCT2_select_DEF      (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM3_SCT3_select_OFF      (23)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM3_SCT3_select_WID      ( 1)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM3_SCT3_select_MSK      (0x00800000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM3_SCT3_select_MAX      (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM3_SCT3_select_DEF      (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM3_LCT0_select_OFF      (24)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM3_LCT0_select_WID      ( 1)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM3_LCT0_select_MSK      (0x01000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM3_LCT0_select_MAX      (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM3_LCT0_select_DEF      (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM3_LCT1_select_OFF      (25)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM3_LCT1_select_WID      ( 1)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM3_LCT1_select_MSK      (0x02000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM3_LCT1_select_MAX      (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM3_LCT1_select_DEF      (0x00000000)

#define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM4_REG                  (0x00000D10)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM4_Signal_In_select_OFF ( 0)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM4_Signal_In_select_WID ( 4)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM4_Signal_In_select_MSK (0x0000000F)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM4_Signal_In_select_MAX (0x0000000F)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM4_Signal_In_select_DEF (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM4_Event_In_select_OFF  ( 4)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM4_Event_In_select_WID  ( 8)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM4_Event_In_select_MSK  (0x00000FF0)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM4_Event_In_select_MAX  (0x000000FF)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM4_Event_In_select_DEF  (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM4_SCT0_select_OFF      (20)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM4_SCT0_select_WID      ( 1)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM4_SCT0_select_MSK      (0x00100000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM4_SCT0_select_MAX      (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM4_SCT0_select_DEF      (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM4_SCT1_select_OFF      (21)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM4_SCT1_select_WID      ( 1)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM4_SCT1_select_MSK      (0x00200000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM4_SCT1_select_MAX      (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM4_SCT1_select_DEF      (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM4_SCT2_select_OFF      (22)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM4_SCT2_select_WID      ( 1)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM4_SCT2_select_MSK      (0x00400000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM4_SCT2_select_MAX      (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM4_SCT2_select_DEF      (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM4_SCT3_select_OFF      (23)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM4_SCT3_select_WID      ( 1)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM4_SCT3_select_MSK      (0x00800000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM4_SCT3_select_MAX      (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM4_SCT3_select_DEF      (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM4_LCT0_select_OFF      (24)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM4_LCT0_select_WID      ( 1)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM4_LCT0_select_MSK      (0x01000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM4_LCT0_select_MAX      (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM4_LCT0_select_DEF      (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM4_LCT1_select_OFF      (25)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM4_LCT1_select_WID      ( 1)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM4_LCT1_select_MSK      (0x02000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM4_LCT1_select_MAX      (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM4_LCT1_select_DEF      (0x00000000)

#define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM5_REG                  (0x00000D14)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM5_Signal_In_select_OFF ( 0)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM5_Signal_In_select_WID ( 4)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM5_Signal_In_select_MSK (0x0000000F)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM5_Signal_In_select_MAX (0x0000000F)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM5_Signal_In_select_DEF (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM5_Event_In_select_OFF  ( 4)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM5_Event_In_select_WID  ( 8)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM5_Event_In_select_MSK  (0x00000FF0)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM5_Event_In_select_MAX  (0x000000FF)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM5_Event_In_select_DEF  (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM5_SCT0_select_OFF      (20)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM5_SCT0_select_WID      ( 1)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM5_SCT0_select_MSK      (0x00100000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM5_SCT0_select_MAX      (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM5_SCT0_select_DEF      (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM5_SCT1_select_OFF      (21)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM5_SCT1_select_WID      ( 1)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM5_SCT1_select_MSK      (0x00200000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM5_SCT1_select_MAX      (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM5_SCT1_select_DEF      (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM5_SCT2_select_OFF      (22)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM5_SCT2_select_WID      ( 1)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM5_SCT2_select_MSK      (0x00400000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM5_SCT2_select_MAX      (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM5_SCT2_select_DEF      (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM5_SCT3_select_OFF      (23)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM5_SCT3_select_WID      ( 1)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM5_SCT3_select_MSK      (0x00800000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM5_SCT3_select_MAX      (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM5_SCT3_select_DEF      (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM5_LCT0_select_OFF      (24)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM5_LCT0_select_WID      ( 1)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM5_LCT0_select_MSK      (0x01000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM5_LCT0_select_MAX      (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM5_LCT0_select_DEF      (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM5_LCT1_select_OFF      (25)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM5_LCT1_select_WID      ( 1)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM5_LCT1_select_MSK      (0x02000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM5_LCT1_select_MAX      (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM5_LCT1_select_DEF      (0x00000000)

#define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM6_REG                  (0x00000D18)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM6_Signal_In_select_OFF ( 0)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM6_Signal_In_select_WID ( 4)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM6_Signal_In_select_MSK (0x0000000F)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM6_Signal_In_select_MAX (0x0000000F)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM6_Signal_In_select_DEF (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM6_Event_In_select_OFF  ( 4)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM6_Event_In_select_WID  ( 8)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM6_Event_In_select_MSK  (0x00000FF0)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM6_Event_In_select_MAX  (0x000000FF)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM6_Event_In_select_DEF  (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM6_SCT0_select_OFF      (20)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM6_SCT0_select_WID      ( 1)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM6_SCT0_select_MSK      (0x00100000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM6_SCT0_select_MAX      (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM6_SCT0_select_DEF      (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM6_SCT1_select_OFF      (21)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM6_SCT1_select_WID      ( 1)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM6_SCT1_select_MSK      (0x00200000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM6_SCT1_select_MAX      (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM6_SCT1_select_DEF      (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM6_SCT2_select_OFF      (22)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM6_SCT2_select_WID      ( 1)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM6_SCT2_select_MSK      (0x00400000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM6_SCT2_select_MAX      (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM6_SCT2_select_DEF      (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM6_SCT3_select_OFF      (23)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM6_SCT3_select_WID      ( 1)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM6_SCT3_select_MSK      (0x00800000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM6_SCT3_select_MAX      (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM6_SCT3_select_DEF      (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM6_LCT0_select_OFF      (24)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM6_LCT0_select_WID      ( 1)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM6_LCT0_select_MSK      (0x01000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM6_LCT0_select_MAX      (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM6_LCT0_select_DEF      (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM6_LCT1_select_OFF      (25)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM6_LCT1_select_WID      ( 1)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM6_LCT1_select_MSK      (0x02000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM6_LCT1_select_MAX      (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM6_LCT1_select_DEF      (0x00000000)

#define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM7_REG                  (0x00000D1C)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM7_Signal_In_select_OFF ( 0)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM7_Signal_In_select_WID ( 4)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM7_Signal_In_select_MSK (0x0000000F)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM7_Signal_In_select_MAX (0x0000000F)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM7_Signal_In_select_DEF (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM7_Event_In_select_OFF  ( 4)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM7_Event_In_select_WID  ( 8)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM7_Event_In_select_MSK  (0x00000FF0)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM7_Event_In_select_MAX  (0x000000FF)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM7_Event_In_select_DEF  (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM7_SCT0_select_OFF      (20)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM7_SCT0_select_WID      ( 1)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM7_SCT0_select_MSK      (0x00100000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM7_SCT0_select_MAX      (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM7_SCT0_select_DEF      (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM7_SCT1_select_OFF      (21)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM7_SCT1_select_WID      ( 1)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM7_SCT1_select_MSK      (0x00200000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM7_SCT1_select_MAX      (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM7_SCT1_select_DEF      (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM7_SCT2_select_OFF      (22)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM7_SCT2_select_WID      ( 1)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM7_SCT2_select_MSK      (0x00400000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM7_SCT2_select_MAX      (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM7_SCT2_select_DEF      (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM7_SCT3_select_OFF      (23)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM7_SCT3_select_WID      ( 1)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM7_SCT3_select_MSK      (0x00800000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM7_SCT3_select_MAX      (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM7_SCT3_select_DEF      (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM7_LCT0_select_OFF      (24)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM7_LCT0_select_WID      ( 1)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM7_LCT0_select_MSK      (0x01000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM7_LCT0_select_MAX      (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM7_LCT0_select_DEF      (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM7_LCT1_select_OFF      (25)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM7_LCT1_select_WID      ( 1)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM7_LCT1_select_MSK      (0x02000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM7_LCT1_select_MAX      (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM7_LCT1_select_DEF      (0x00000000)

#define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM8_REG                  (0x00000D20)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM8_Signal_In_select_OFF ( 0)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM8_Signal_In_select_WID ( 4)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM8_Signal_In_select_MSK (0x0000000F)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM8_Signal_In_select_MAX (0x0000000F)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM8_Signal_In_select_DEF (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM8_Event_In_select_OFF  ( 4)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM8_Event_In_select_WID  ( 8)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM8_Event_In_select_MSK  (0x00000FF0)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM8_Event_In_select_MAX  (0x000000FF)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM8_Event_In_select_DEF  (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM8_SCT0_select_OFF      (20)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM8_SCT0_select_WID      ( 1)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM8_SCT0_select_MSK      (0x00100000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM8_SCT0_select_MAX      (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM8_SCT0_select_DEF      (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM8_SCT1_select_OFF      (21)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM8_SCT1_select_WID      ( 1)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM8_SCT1_select_MSK      (0x00200000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM8_SCT1_select_MAX      (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM8_SCT1_select_DEF      (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM8_SCT2_select_OFF      (22)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM8_SCT2_select_WID      ( 1)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM8_SCT2_select_MSK      (0x00400000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM8_SCT2_select_MAX      (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM8_SCT2_select_DEF      (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM8_SCT3_select_OFF      (23)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM8_SCT3_select_WID      ( 1)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM8_SCT3_select_MSK      (0x00800000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM8_SCT3_select_MAX      (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM8_SCT3_select_DEF      (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM8_LCT0_select_OFF      (24)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM8_LCT0_select_WID      ( 1)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM8_LCT0_select_MSK      (0x01000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM8_LCT0_select_MAX      (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM8_LCT0_select_DEF      (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM8_LCT1_select_OFF      (25)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM8_LCT1_select_WID      ( 1)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM8_LCT1_select_MSK      (0x02000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM8_LCT1_select_MAX      (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM8_LCT1_select_DEF      (0x00000000)

#define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM9_REG                  (0x00000D24)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM9_Signal_In_select_OFF ( 0)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM9_Signal_In_select_WID ( 4)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM9_Signal_In_select_MSK (0x0000000F)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM9_Signal_In_select_MAX (0x0000000F)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM9_Signal_In_select_DEF (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM9_Event_In_select_OFF  ( 4)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM9_Event_In_select_WID  ( 8)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM9_Event_In_select_MSK  (0x00000FF0)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM9_Event_In_select_MAX  (0x000000FF)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM9_Event_In_select_DEF  (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM9_SCT0_select_OFF      (20)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM9_SCT0_select_WID      ( 1)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM9_SCT0_select_MSK      (0x00100000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM9_SCT0_select_MAX      (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM9_SCT0_select_DEF      (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM9_SCT1_select_OFF      (21)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM9_SCT1_select_WID      ( 1)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM9_SCT1_select_MSK      (0x00200000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM9_SCT1_select_MAX      (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM9_SCT1_select_DEF      (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM9_SCT2_select_OFF      (22)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM9_SCT2_select_WID      ( 1)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM9_SCT2_select_MSK      (0x00400000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM9_SCT2_select_MAX      (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM9_SCT2_select_DEF      (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM9_SCT3_select_OFF      (23)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM9_SCT3_select_WID      ( 1)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM9_SCT3_select_MSK      (0x00800000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM9_SCT3_select_MAX      (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM9_SCT3_select_DEF      (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM9_LCT0_select_OFF      (24)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM9_LCT0_select_WID      ( 1)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM9_LCT0_select_MSK      (0x01000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM9_LCT0_select_MAX      (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM9_LCT0_select_DEF      (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM9_LCT1_select_OFF      (25)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM9_LCT1_select_WID      ( 1)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM9_LCT1_select_MSK      (0x02000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM9_LCT1_select_MAX      (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM9_LCT1_select_DEF      (0x00000000)

#define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM10_REG                 (0x00000D28)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM10_Signal_In_select_OFF ( 0)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM10_Signal_In_select_WID ( 4)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM10_Signal_In_select_MSK (0x0000000F)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM10_Signal_In_select_MAX (0x0000000F)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM10_Signal_In_select_DEF (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM10_Event_In_select_OFF ( 4)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM10_Event_In_select_WID ( 8)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM10_Event_In_select_MSK (0x00000FF0)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM10_Event_In_select_MAX (0x000000FF)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM10_Event_In_select_DEF (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM10_SCT0_select_OFF     (20)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM10_SCT0_select_WID     ( 1)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM10_SCT0_select_MSK     (0x00100000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM10_SCT0_select_MAX     (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM10_SCT0_select_DEF     (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM10_SCT1_select_OFF     (21)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM10_SCT1_select_WID     ( 1)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM10_SCT1_select_MSK     (0x00200000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM10_SCT1_select_MAX     (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM10_SCT1_select_DEF     (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM10_SCT2_select_OFF     (22)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM10_SCT2_select_WID     ( 1)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM10_SCT2_select_MSK     (0x00400000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM10_SCT2_select_MAX     (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM10_SCT2_select_DEF     (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM10_SCT3_select_OFF     (23)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM10_SCT3_select_WID     ( 1)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM10_SCT3_select_MSK     (0x00800000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM10_SCT3_select_MAX     (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM10_SCT3_select_DEF     (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM10_LCT0_select_OFF     (24)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM10_LCT0_select_WID     ( 1)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM10_LCT0_select_MSK     (0x01000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM10_LCT0_select_MAX     (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM10_LCT0_select_DEF     (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM10_LCT1_select_OFF     (25)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM10_LCT1_select_WID     ( 1)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM10_LCT1_select_MSK     (0x02000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM10_LCT1_select_MAX     (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM10_LCT1_select_DEF     (0x00000000)

#define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM11_REG                 (0x00000D2C)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM11_Signal_In_select_OFF ( 0)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM11_Signal_In_select_WID ( 4)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM11_Signal_In_select_MSK (0x0000000F)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM11_Signal_In_select_MAX (0x0000000F)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM11_Signal_In_select_DEF (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM11_Event_In_select_OFF ( 4)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM11_Event_In_select_WID ( 8)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM11_Event_In_select_MSK (0x00000FF0)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM11_Event_In_select_MAX (0x000000FF)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM11_Event_In_select_DEF (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM11_SCT0_select_OFF     (20)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM11_SCT0_select_WID     ( 1)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM11_SCT0_select_MSK     (0x00100000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM11_SCT0_select_MAX     (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM11_SCT0_select_DEF     (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM11_SCT1_select_OFF     (21)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM11_SCT1_select_WID     ( 1)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM11_SCT1_select_MSK     (0x00200000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM11_SCT1_select_MAX     (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM11_SCT1_select_DEF     (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM11_SCT2_select_OFF     (22)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM11_SCT2_select_WID     ( 1)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM11_SCT2_select_MSK     (0x00400000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM11_SCT2_select_MAX     (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM11_SCT2_select_DEF     (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM11_SCT3_select_OFF     (23)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM11_SCT3_select_WID     ( 1)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM11_SCT3_select_MSK     (0x00800000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM11_SCT3_select_MAX     (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM11_SCT3_select_DEF     (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM11_LCT0_select_OFF     (24)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM11_LCT0_select_WID     ( 1)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM11_LCT0_select_MSK     (0x01000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM11_LCT0_select_MAX     (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM11_LCT0_select_DEF     (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM11_LCT1_select_OFF     (25)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM11_LCT1_select_WID     ( 1)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM11_LCT1_select_MSK     (0x02000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM11_LCT1_select_MAX     (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM11_LCT1_select_DEF     (0x00000000)

#define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM12_REG                 (0x00000D30)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM12_Signal_In_select_OFF ( 0)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM12_Signal_In_select_WID ( 4)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM12_Signal_In_select_MSK (0x0000000F)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM12_Signal_In_select_MAX (0x0000000F)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM12_Signal_In_select_DEF (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM12_Event_In_select_OFF ( 4)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM12_Event_In_select_WID ( 8)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM12_Event_In_select_MSK (0x00000FF0)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM12_Event_In_select_MAX (0x000000FF)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM12_Event_In_select_DEF (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM12_SCT0_select_OFF     (20)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM12_SCT0_select_WID     ( 1)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM12_SCT0_select_MSK     (0x00100000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM12_SCT0_select_MAX     (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM12_SCT0_select_DEF     (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM12_SCT1_select_OFF     (21)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM12_SCT1_select_WID     ( 1)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM12_SCT1_select_MSK     (0x00200000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM12_SCT1_select_MAX     (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM12_SCT1_select_DEF     (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM12_SCT2_select_OFF     (22)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM12_SCT2_select_WID     ( 1)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM12_SCT2_select_MSK     (0x00400000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM12_SCT2_select_MAX     (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM12_SCT2_select_DEF     (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM12_SCT3_select_OFF     (23)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM12_SCT3_select_WID     ( 1)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM12_SCT3_select_MSK     (0x00800000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM12_SCT3_select_MAX     (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM12_SCT3_select_DEF     (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM12_LCT0_select_OFF     (24)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM12_LCT0_select_WID     ( 1)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM12_LCT0_select_MSK     (0x01000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM12_LCT0_select_MAX     (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM12_LCT0_select_DEF     (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM12_LCT1_select_OFF     (25)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM12_LCT1_select_WID     ( 1)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM12_LCT1_select_MSK     (0x02000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM12_LCT1_select_MAX     (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM12_LCT1_select_DEF     (0x00000000)

#define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM13_REG                 (0x00000D34)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM13_Signal_In_select_OFF ( 0)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM13_Signal_In_select_WID ( 4)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM13_Signal_In_select_MSK (0x0000000F)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM13_Signal_In_select_MAX (0x0000000F)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM13_Signal_In_select_DEF (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM13_Event_In_select_OFF ( 4)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM13_Event_In_select_WID ( 8)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM13_Event_In_select_MSK (0x00000FF0)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM13_Event_In_select_MAX (0x000000FF)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM13_Event_In_select_DEF (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM13_SCT0_select_OFF     (20)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM13_SCT0_select_WID     ( 1)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM13_SCT0_select_MSK     (0x00100000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM13_SCT0_select_MAX     (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM13_SCT0_select_DEF     (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM13_SCT1_select_OFF     (21)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM13_SCT1_select_WID     ( 1)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM13_SCT1_select_MSK     (0x00200000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM13_SCT1_select_MAX     (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM13_SCT1_select_DEF     (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM13_SCT2_select_OFF     (22)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM13_SCT2_select_WID     ( 1)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM13_SCT2_select_MSK     (0x00400000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM13_SCT2_select_MAX     (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM13_SCT2_select_DEF     (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM13_SCT3_select_OFF     (23)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM13_SCT3_select_WID     ( 1)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM13_SCT3_select_MSK     (0x00800000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM13_SCT3_select_MAX     (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM13_SCT3_select_DEF     (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM13_LCT0_select_OFF     (24)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM13_LCT0_select_WID     ( 1)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM13_LCT0_select_MSK     (0x01000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM13_LCT0_select_MAX     (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM13_LCT0_select_DEF     (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM13_LCT1_select_OFF     (25)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM13_LCT1_select_WID     ( 1)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM13_LCT1_select_MSK     (0x02000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM13_LCT1_select_MAX     (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM13_LCT1_select_DEF     (0x00000000)

#define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM14_REG                 (0x00000D38)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM14_Signal_In_select_OFF ( 0)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM14_Signal_In_select_WID ( 4)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM14_Signal_In_select_MSK (0x0000000F)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM14_Signal_In_select_MAX (0x0000000F)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM14_Signal_In_select_DEF (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM14_Event_In_select_OFF ( 4)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM14_Event_In_select_WID ( 8)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM14_Event_In_select_MSK (0x00000FF0)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM14_Event_In_select_MAX (0x000000FF)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM14_Event_In_select_DEF (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM14_SCT0_select_OFF     (20)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM14_SCT0_select_WID     ( 1)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM14_SCT0_select_MSK     (0x00100000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM14_SCT0_select_MAX     (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM14_SCT0_select_DEF     (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM14_SCT1_select_OFF     (21)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM14_SCT1_select_WID     ( 1)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM14_SCT1_select_MSK     (0x00200000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM14_SCT1_select_MAX     (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM14_SCT1_select_DEF     (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM14_SCT2_select_OFF     (22)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM14_SCT2_select_WID     ( 1)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM14_SCT2_select_MSK     (0x00400000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM14_SCT2_select_MAX     (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM14_SCT2_select_DEF     (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM14_SCT3_select_OFF     (23)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM14_SCT3_select_WID     ( 1)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM14_SCT3_select_MSK     (0x00800000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM14_SCT3_select_MAX     (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM14_SCT3_select_DEF     (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM14_LCT0_select_OFF     (24)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM14_LCT0_select_WID     ( 1)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM14_LCT0_select_MSK     (0x01000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM14_LCT0_select_MAX     (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM14_LCT0_select_DEF     (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM14_LCT1_select_OFF     (25)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM14_LCT1_select_WID     ( 1)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM14_LCT1_select_MSK     (0x02000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM14_LCT1_select_MAX     (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM14_LCT1_select_DEF     (0x00000000)

#define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM15_REG                 (0x00000D3C)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM15_Signal_In_select_OFF ( 0)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM15_Signal_In_select_WID ( 4)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM15_Signal_In_select_MSK (0x0000000F)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM15_Signal_In_select_MAX (0x0000000F)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM15_Signal_In_select_DEF (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM15_Event_In_select_OFF ( 4)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM15_Event_In_select_WID ( 8)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM15_Event_In_select_MSK (0x00000FF0)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM15_Event_In_select_MAX (0x000000FF)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM15_Event_In_select_DEF (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM15_SCT0_select_OFF     (20)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM15_SCT0_select_WID     ( 1)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM15_SCT0_select_MSK     (0x00100000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM15_SCT0_select_MAX     (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM15_SCT0_select_DEF     (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM15_SCT1_select_OFF     (21)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM15_SCT1_select_WID     ( 1)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM15_SCT1_select_MSK     (0x00200000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM15_SCT1_select_MAX     (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM15_SCT1_select_DEF     (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM15_SCT2_select_OFF     (22)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM15_SCT2_select_WID     ( 1)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM15_SCT2_select_MSK     (0x00400000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM15_SCT2_select_MAX     (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM15_SCT2_select_DEF     (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM15_SCT3_select_OFF     (23)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM15_SCT3_select_WID     ( 1)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM15_SCT3_select_MSK     (0x00800000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM15_SCT3_select_MAX     (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM15_SCT3_select_DEF     (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM15_LCT0_select_OFF     (24)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM15_LCT0_select_WID     ( 1)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM15_LCT0_select_MSK     (0x01000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM15_LCT0_select_MAX     (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM15_LCT0_select_DEF     (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM15_LCT1_select_OFF     (25)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM15_LCT1_select_WID     ( 1)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM15_LCT1_select_MSK     (0x02000000)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM15_LCT1_select_MAX     (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_EVENT_ENABLE_CN_SM15_LCT1_select_DEF     (0x00000000)

#define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM0_REG                (0x00000D40)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM0_Set_signal_out_OFF ( 0)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM0_Set_signal_out_WID ( 4)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM0_Set_signal_out_MSK (0x0000000F)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM0_Set_signal_out_MAX (0x0000000F)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM0_Set_signal_out_DEF (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM0_Set_trig_out_OFF   ( 4)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM0_Set_trig_out_WID   ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM0_Set_trig_out_MSK   (0x00000010)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM0_Set_trig_out_MAX   (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM0_Set_trig_out_DEF   (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM0_Start_storage_OFF  ( 5)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM0_Start_storage_WID  ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM0_Start_storage_MSK  (0x00000020)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM0_Start_storage_MAX  (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM0_Start_storage_DEF  (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM0_Stop_storage_OFF   ( 6)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM0_Stop_storage_WID   ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM0_Stop_storage_MSK   (0x00000040)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM0_Stop_storage_MAX   (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM0_Stop_storage_DEF   (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM0_SCT0_start_inc_OFF ( 7)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM0_SCT0_start_inc_WID ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM0_SCT0_start_inc_MSK (0x00000080)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM0_SCT0_start_inc_MAX (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM0_SCT0_start_inc_DEF (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM0_SCT1_start_inc_OFF ( 8)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM0_SCT1_start_inc_WID ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM0_SCT1_start_inc_MSK (0x00000100)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM0_SCT1_start_inc_MAX (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM0_SCT1_start_inc_DEF (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM0_SCT2_start_inc_OFF ( 9)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM0_SCT2_start_inc_WID ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM0_SCT2_start_inc_MSK (0x00000200)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM0_SCT2_start_inc_MAX (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM0_SCT2_start_inc_DEF (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM0_SCT3_start_inc_OFF (10)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM0_SCT3_start_inc_WID ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM0_SCT3_start_inc_MSK (0x00000400)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM0_SCT3_start_inc_MAX (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM0_SCT3_start_inc_DEF (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM0_LCT0_start_inc_OFF (11)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM0_LCT0_start_inc_WID ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM0_LCT0_start_inc_MSK (0x00000800)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM0_LCT0_start_inc_MAX (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM0_LCT0_start_inc_DEF (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM0_LCT1_start_inc_OFF (12)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM0_LCT1_start_inc_WID ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM0_LCT1_start_inc_MSK (0x00001000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM0_LCT1_start_inc_MAX (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM0_LCT1_start_inc_DEF (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM0_LCT0_stop_OFF      (15)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM0_LCT0_stop_WID      ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM0_LCT0_stop_MSK      (0x00008000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM0_LCT0_stop_MAX      (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM0_LCT0_stop_DEF      (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM0_LCT1_stop_OFF      (16)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM0_LCT1_stop_WID      ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM0_LCT1_stop_MSK      (0x00010000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM0_LCT1_stop_MAX      (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM0_LCT1_stop_DEF      (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM0_SCT0_clear_OFF     (19)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM0_SCT0_clear_WID     ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM0_SCT0_clear_MSK     (0x00080000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM0_SCT0_clear_MAX     (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM0_SCT0_clear_DEF     (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM0_SCT1_clear_OFF     (20)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM0_SCT1_clear_WID     ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM0_SCT1_clear_MSK     (0x00100000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM0_SCT1_clear_MAX     (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM0_SCT1_clear_DEF     (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM0_SCT2_clear_OFF     (21)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM0_SCT2_clear_WID     ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM0_SCT2_clear_MSK     (0x00200000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM0_SCT2_clear_MAX     (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM0_SCT2_clear_DEF     (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM0_SCT3_clear_OFF     (22)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM0_SCT3_clear_WID     ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM0_SCT3_clear_MSK     (0x00400000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM0_SCT3_clear_MAX     (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM0_SCT3_clear_DEF     (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM0_LCT0_clear_OFF     (23)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM0_LCT0_clear_WID     ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM0_LCT0_clear_MSK     (0x00800000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM0_LCT0_clear_MAX     (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM0_LCT0_clear_DEF     (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM0_LCT1_clear_OFF     (24)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM0_LCT1_clear_WID     ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM0_LCT1_clear_MSK     (0x01000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM0_LCT1_clear_MAX     (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM0_LCT1_clear_DEF     (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM0_Set_state_OFF      (27)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM0_Set_state_WID      ( 4)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM0_Set_state_MSK      (0x78000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM0_Set_state_MAX      (0x0000000F)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM0_Set_state_DEF      (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM0_Set_Signal_value_OFF (31)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM0_Set_Signal_value_WID ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM0_Set_Signal_value_MSK (0x80000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM0_Set_Signal_value_MAX (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM0_Set_Signal_value_DEF (0x00000000)

#define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM1_REG                (0x00000D44)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM1_Set_signal_out_OFF ( 0)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM1_Set_signal_out_WID ( 4)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM1_Set_signal_out_MSK (0x0000000F)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM1_Set_signal_out_MAX (0x0000000F)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM1_Set_signal_out_DEF (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM1_Set_trig_out_OFF   ( 4)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM1_Set_trig_out_WID   ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM1_Set_trig_out_MSK   (0x00000010)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM1_Set_trig_out_MAX   (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM1_Set_trig_out_DEF   (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM1_Start_storage_OFF  ( 5)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM1_Start_storage_WID  ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM1_Start_storage_MSK  (0x00000020)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM1_Start_storage_MAX  (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM1_Start_storage_DEF  (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM1_Stop_storage_OFF   ( 6)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM1_Stop_storage_WID   ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM1_Stop_storage_MSK   (0x00000040)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM1_Stop_storage_MAX   (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM1_Stop_storage_DEF   (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM1_SCT0_start_inc_OFF ( 7)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM1_SCT0_start_inc_WID ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM1_SCT0_start_inc_MSK (0x00000080)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM1_SCT0_start_inc_MAX (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM1_SCT0_start_inc_DEF (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM1_SCT1_start_inc_OFF ( 8)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM1_SCT1_start_inc_WID ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM1_SCT1_start_inc_MSK (0x00000100)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM1_SCT1_start_inc_MAX (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM1_SCT1_start_inc_DEF (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM1_SCT2_start_inc_OFF ( 9)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM1_SCT2_start_inc_WID ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM1_SCT2_start_inc_MSK (0x00000200)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM1_SCT2_start_inc_MAX (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM1_SCT2_start_inc_DEF (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM1_SCT3_start_inc_OFF (10)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM1_SCT3_start_inc_WID ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM1_SCT3_start_inc_MSK (0x00000400)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM1_SCT3_start_inc_MAX (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM1_SCT3_start_inc_DEF (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM1_LCT0_start_inc_OFF (11)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM1_LCT0_start_inc_WID ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM1_LCT0_start_inc_MSK (0x00000800)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM1_LCT0_start_inc_MAX (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM1_LCT0_start_inc_DEF (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM1_LCT1_start_inc_OFF (12)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM1_LCT1_start_inc_WID ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM1_LCT1_start_inc_MSK (0x00001000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM1_LCT1_start_inc_MAX (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM1_LCT1_start_inc_DEF (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM1_LCT0_stop_OFF      (15)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM1_LCT0_stop_WID      ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM1_LCT0_stop_MSK      (0x00008000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM1_LCT0_stop_MAX      (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM1_LCT0_stop_DEF      (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM1_LCT1_stop_OFF      (16)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM1_LCT1_stop_WID      ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM1_LCT1_stop_MSK      (0x00010000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM1_LCT1_stop_MAX      (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM1_LCT1_stop_DEF      (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM1_SCT0_clear_OFF     (19)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM1_SCT0_clear_WID     ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM1_SCT0_clear_MSK     (0x00080000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM1_SCT0_clear_MAX     (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM1_SCT0_clear_DEF     (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM1_SCT1_clear_OFF     (20)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM1_SCT1_clear_WID     ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM1_SCT1_clear_MSK     (0x00100000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM1_SCT1_clear_MAX     (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM1_SCT1_clear_DEF     (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM1_SCT2_clear_OFF     (21)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM1_SCT2_clear_WID     ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM1_SCT2_clear_MSK     (0x00200000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM1_SCT2_clear_MAX     (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM1_SCT2_clear_DEF     (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM1_SCT3_clear_OFF     (22)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM1_SCT3_clear_WID     ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM1_SCT3_clear_MSK     (0x00400000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM1_SCT3_clear_MAX     (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM1_SCT3_clear_DEF     (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM1_LCT0_clear_OFF     (23)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM1_LCT0_clear_WID     ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM1_LCT0_clear_MSK     (0x00800000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM1_LCT0_clear_MAX     (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM1_LCT0_clear_DEF     (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM1_LCT1_clear_OFF     (24)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM1_LCT1_clear_WID     ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM1_LCT1_clear_MSK     (0x01000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM1_LCT1_clear_MAX     (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM1_LCT1_clear_DEF     (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM1_Set_state_OFF      (27)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM1_Set_state_WID      ( 4)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM1_Set_state_MSK      (0x78000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM1_Set_state_MAX      (0x0000000F)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM1_Set_state_DEF      (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM1_Set_Signal_value_OFF (31)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM1_Set_Signal_value_WID ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM1_Set_Signal_value_MSK (0x80000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM1_Set_Signal_value_MAX (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM1_Set_Signal_value_DEF (0x00000000)

#define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM2_REG                (0x00000D48)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM2_Set_signal_out_OFF ( 0)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM2_Set_signal_out_WID ( 4)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM2_Set_signal_out_MSK (0x0000000F)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM2_Set_signal_out_MAX (0x0000000F)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM2_Set_signal_out_DEF (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM2_Set_trig_out_OFF   ( 4)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM2_Set_trig_out_WID   ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM2_Set_trig_out_MSK   (0x00000010)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM2_Set_trig_out_MAX   (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM2_Set_trig_out_DEF   (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM2_Start_storage_OFF  ( 5)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM2_Start_storage_WID  ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM2_Start_storage_MSK  (0x00000020)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM2_Start_storage_MAX  (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM2_Start_storage_DEF  (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM2_Stop_storage_OFF   ( 6)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM2_Stop_storage_WID   ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM2_Stop_storage_MSK   (0x00000040)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM2_Stop_storage_MAX   (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM2_Stop_storage_DEF   (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM2_SCT0_start_inc_OFF ( 7)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM2_SCT0_start_inc_WID ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM2_SCT0_start_inc_MSK (0x00000080)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM2_SCT0_start_inc_MAX (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM2_SCT0_start_inc_DEF (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM2_SCT1_start_inc_OFF ( 8)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM2_SCT1_start_inc_WID ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM2_SCT1_start_inc_MSK (0x00000100)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM2_SCT1_start_inc_MAX (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM2_SCT1_start_inc_DEF (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM2_SCT2_start_inc_OFF ( 9)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM2_SCT2_start_inc_WID ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM2_SCT2_start_inc_MSK (0x00000200)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM2_SCT2_start_inc_MAX (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM2_SCT2_start_inc_DEF (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM2_SCT3_start_inc_OFF (10)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM2_SCT3_start_inc_WID ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM2_SCT3_start_inc_MSK (0x00000400)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM2_SCT3_start_inc_MAX (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM2_SCT3_start_inc_DEF (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM2_LCT0_start_inc_OFF (11)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM2_LCT0_start_inc_WID ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM2_LCT0_start_inc_MSK (0x00000800)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM2_LCT0_start_inc_MAX (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM2_LCT0_start_inc_DEF (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM2_LCT1_start_inc_OFF (12)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM2_LCT1_start_inc_WID ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM2_LCT1_start_inc_MSK (0x00001000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM2_LCT1_start_inc_MAX (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM2_LCT1_start_inc_DEF (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM2_LCT0_stop_OFF      (15)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM2_LCT0_stop_WID      ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM2_LCT0_stop_MSK      (0x00008000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM2_LCT0_stop_MAX      (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM2_LCT0_stop_DEF      (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM2_LCT1_stop_OFF      (16)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM2_LCT1_stop_WID      ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM2_LCT1_stop_MSK      (0x00010000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM2_LCT1_stop_MAX      (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM2_LCT1_stop_DEF      (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM2_SCT0_clear_OFF     (19)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM2_SCT0_clear_WID     ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM2_SCT0_clear_MSK     (0x00080000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM2_SCT0_clear_MAX     (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM2_SCT0_clear_DEF     (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM2_SCT1_clear_OFF     (20)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM2_SCT1_clear_WID     ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM2_SCT1_clear_MSK     (0x00100000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM2_SCT1_clear_MAX     (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM2_SCT1_clear_DEF     (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM2_SCT2_clear_OFF     (21)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM2_SCT2_clear_WID     ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM2_SCT2_clear_MSK     (0x00200000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM2_SCT2_clear_MAX     (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM2_SCT2_clear_DEF     (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM2_SCT3_clear_OFF     (22)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM2_SCT3_clear_WID     ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM2_SCT3_clear_MSK     (0x00400000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM2_SCT3_clear_MAX     (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM2_SCT3_clear_DEF     (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM2_LCT0_clear_OFF     (23)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM2_LCT0_clear_WID     ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM2_LCT0_clear_MSK     (0x00800000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM2_LCT0_clear_MAX     (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM2_LCT0_clear_DEF     (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM2_LCT1_clear_OFF     (24)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM2_LCT1_clear_WID     ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM2_LCT1_clear_MSK     (0x01000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM2_LCT1_clear_MAX     (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM2_LCT1_clear_DEF     (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM2_Set_state_OFF      (27)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM2_Set_state_WID      ( 4)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM2_Set_state_MSK      (0x78000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM2_Set_state_MAX      (0x0000000F)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM2_Set_state_DEF      (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM2_Set_Signal_value_OFF (31)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM2_Set_Signal_value_WID ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM2_Set_Signal_value_MSK (0x80000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM2_Set_Signal_value_MAX (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM2_Set_Signal_value_DEF (0x00000000)

#define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM3_REG                (0x00000D4C)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM3_Set_signal_out_OFF ( 0)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM3_Set_signal_out_WID ( 4)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM3_Set_signal_out_MSK (0x0000000F)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM3_Set_signal_out_MAX (0x0000000F)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM3_Set_signal_out_DEF (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM3_Set_trig_out_OFF   ( 4)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM3_Set_trig_out_WID   ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM3_Set_trig_out_MSK   (0x00000010)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM3_Set_trig_out_MAX   (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM3_Set_trig_out_DEF   (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM3_Start_storage_OFF  ( 5)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM3_Start_storage_WID  ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM3_Start_storage_MSK  (0x00000020)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM3_Start_storage_MAX  (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM3_Start_storage_DEF  (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM3_Stop_storage_OFF   ( 6)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM3_Stop_storage_WID   ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM3_Stop_storage_MSK   (0x00000040)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM3_Stop_storage_MAX   (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM3_Stop_storage_DEF   (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM3_SCT0_start_inc_OFF ( 7)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM3_SCT0_start_inc_WID ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM3_SCT0_start_inc_MSK (0x00000080)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM3_SCT0_start_inc_MAX (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM3_SCT0_start_inc_DEF (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM3_SCT1_start_inc_OFF ( 8)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM3_SCT1_start_inc_WID ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM3_SCT1_start_inc_MSK (0x00000100)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM3_SCT1_start_inc_MAX (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM3_SCT1_start_inc_DEF (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM3_SCT2_start_inc_OFF ( 9)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM3_SCT2_start_inc_WID ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM3_SCT2_start_inc_MSK (0x00000200)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM3_SCT2_start_inc_MAX (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM3_SCT2_start_inc_DEF (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM3_SCT3_start_inc_OFF (10)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM3_SCT3_start_inc_WID ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM3_SCT3_start_inc_MSK (0x00000400)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM3_SCT3_start_inc_MAX (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM3_SCT3_start_inc_DEF (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM3_LCT0_start_inc_OFF (11)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM3_LCT0_start_inc_WID ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM3_LCT0_start_inc_MSK (0x00000800)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM3_LCT0_start_inc_MAX (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM3_LCT0_start_inc_DEF (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM3_LCT1_start_inc_OFF (12)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM3_LCT1_start_inc_WID ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM3_LCT1_start_inc_MSK (0x00001000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM3_LCT1_start_inc_MAX (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM3_LCT1_start_inc_DEF (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM3_LCT0_stop_OFF      (15)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM3_LCT0_stop_WID      ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM3_LCT0_stop_MSK      (0x00008000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM3_LCT0_stop_MAX      (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM3_LCT0_stop_DEF      (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM3_LCT1_stop_OFF      (16)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM3_LCT1_stop_WID      ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM3_LCT1_stop_MSK      (0x00010000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM3_LCT1_stop_MAX      (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM3_LCT1_stop_DEF      (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM3_SCT0_clear_OFF     (19)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM3_SCT0_clear_WID     ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM3_SCT0_clear_MSK     (0x00080000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM3_SCT0_clear_MAX     (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM3_SCT0_clear_DEF     (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM3_SCT1_clear_OFF     (20)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM3_SCT1_clear_WID     ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM3_SCT1_clear_MSK     (0x00100000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM3_SCT1_clear_MAX     (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM3_SCT1_clear_DEF     (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM3_SCT2_clear_OFF     (21)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM3_SCT2_clear_WID     ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM3_SCT2_clear_MSK     (0x00200000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM3_SCT2_clear_MAX     (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM3_SCT2_clear_DEF     (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM3_SCT3_clear_OFF     (22)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM3_SCT3_clear_WID     ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM3_SCT3_clear_MSK     (0x00400000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM3_SCT3_clear_MAX     (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM3_SCT3_clear_DEF     (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM3_LCT0_clear_OFF     (23)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM3_LCT0_clear_WID     ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM3_LCT0_clear_MSK     (0x00800000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM3_LCT0_clear_MAX     (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM3_LCT0_clear_DEF     (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM3_LCT1_clear_OFF     (24)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM3_LCT1_clear_WID     ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM3_LCT1_clear_MSK     (0x01000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM3_LCT1_clear_MAX     (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM3_LCT1_clear_DEF     (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM3_Set_state_OFF      (27)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM3_Set_state_WID      ( 4)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM3_Set_state_MSK      (0x78000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM3_Set_state_MAX      (0x0000000F)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM3_Set_state_DEF      (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM3_Set_Signal_value_OFF (31)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM3_Set_Signal_value_WID ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM3_Set_Signal_value_MSK (0x80000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM3_Set_Signal_value_MAX (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM3_Set_Signal_value_DEF (0x00000000)

#define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM4_REG                (0x00000D50)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM4_Set_signal_out_OFF ( 0)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM4_Set_signal_out_WID ( 4)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM4_Set_signal_out_MSK (0x0000000F)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM4_Set_signal_out_MAX (0x0000000F)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM4_Set_signal_out_DEF (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM4_Set_trig_out_OFF   ( 4)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM4_Set_trig_out_WID   ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM4_Set_trig_out_MSK   (0x00000010)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM4_Set_trig_out_MAX   (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM4_Set_trig_out_DEF   (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM4_Start_storage_OFF  ( 5)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM4_Start_storage_WID  ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM4_Start_storage_MSK  (0x00000020)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM4_Start_storage_MAX  (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM4_Start_storage_DEF  (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM4_Stop_storage_OFF   ( 6)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM4_Stop_storage_WID   ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM4_Stop_storage_MSK   (0x00000040)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM4_Stop_storage_MAX   (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM4_Stop_storage_DEF   (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM4_SCT0_start_inc_OFF ( 7)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM4_SCT0_start_inc_WID ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM4_SCT0_start_inc_MSK (0x00000080)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM4_SCT0_start_inc_MAX (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM4_SCT0_start_inc_DEF (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM4_SCT1_start_inc_OFF ( 8)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM4_SCT1_start_inc_WID ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM4_SCT1_start_inc_MSK (0x00000100)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM4_SCT1_start_inc_MAX (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM4_SCT1_start_inc_DEF (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM4_SCT2_start_inc_OFF ( 9)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM4_SCT2_start_inc_WID ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM4_SCT2_start_inc_MSK (0x00000200)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM4_SCT2_start_inc_MAX (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM4_SCT2_start_inc_DEF (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM4_SCT3_start_inc_OFF (10)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM4_SCT3_start_inc_WID ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM4_SCT3_start_inc_MSK (0x00000400)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM4_SCT3_start_inc_MAX (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM4_SCT3_start_inc_DEF (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM4_LCT0_start_inc_OFF (11)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM4_LCT0_start_inc_WID ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM4_LCT0_start_inc_MSK (0x00000800)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM4_LCT0_start_inc_MAX (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM4_LCT0_start_inc_DEF (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM4_LCT1_start_inc_OFF (12)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM4_LCT1_start_inc_WID ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM4_LCT1_start_inc_MSK (0x00001000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM4_LCT1_start_inc_MAX (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM4_LCT1_start_inc_DEF (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM4_LCT0_stop_OFF      (15)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM4_LCT0_stop_WID      ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM4_LCT0_stop_MSK      (0x00008000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM4_LCT0_stop_MAX      (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM4_LCT0_stop_DEF      (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM4_LCT1_stop_OFF      (16)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM4_LCT1_stop_WID      ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM4_LCT1_stop_MSK      (0x00010000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM4_LCT1_stop_MAX      (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM4_LCT1_stop_DEF      (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM4_SCT0_clear_OFF     (19)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM4_SCT0_clear_WID     ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM4_SCT0_clear_MSK     (0x00080000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM4_SCT0_clear_MAX     (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM4_SCT0_clear_DEF     (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM4_SCT1_clear_OFF     (20)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM4_SCT1_clear_WID     ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM4_SCT1_clear_MSK     (0x00100000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM4_SCT1_clear_MAX     (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM4_SCT1_clear_DEF     (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM4_SCT2_clear_OFF     (21)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM4_SCT2_clear_WID     ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM4_SCT2_clear_MSK     (0x00200000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM4_SCT2_clear_MAX     (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM4_SCT2_clear_DEF     (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM4_SCT3_clear_OFF     (22)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM4_SCT3_clear_WID     ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM4_SCT3_clear_MSK     (0x00400000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM4_SCT3_clear_MAX     (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM4_SCT3_clear_DEF     (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM4_LCT0_clear_OFF     (23)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM4_LCT0_clear_WID     ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM4_LCT0_clear_MSK     (0x00800000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM4_LCT0_clear_MAX     (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM4_LCT0_clear_DEF     (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM4_LCT1_clear_OFF     (24)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM4_LCT1_clear_WID     ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM4_LCT1_clear_MSK     (0x01000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM4_LCT1_clear_MAX     (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM4_LCT1_clear_DEF     (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM4_Set_state_OFF      (27)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM4_Set_state_WID      ( 4)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM4_Set_state_MSK      (0x78000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM4_Set_state_MAX      (0x0000000F)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM4_Set_state_DEF      (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM4_Set_Signal_value_OFF (31)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM4_Set_Signal_value_WID ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM4_Set_Signal_value_MSK (0x80000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM4_Set_Signal_value_MAX (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM4_Set_Signal_value_DEF (0x00000000)

#define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM5_REG                (0x00000D54)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM5_Set_signal_out_OFF ( 0)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM5_Set_signal_out_WID ( 4)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM5_Set_signal_out_MSK (0x0000000F)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM5_Set_signal_out_MAX (0x0000000F)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM5_Set_signal_out_DEF (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM5_Set_trig_out_OFF   ( 4)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM5_Set_trig_out_WID   ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM5_Set_trig_out_MSK   (0x00000010)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM5_Set_trig_out_MAX   (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM5_Set_trig_out_DEF   (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM5_Start_storage_OFF  ( 5)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM5_Start_storage_WID  ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM5_Start_storage_MSK  (0x00000020)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM5_Start_storage_MAX  (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM5_Start_storage_DEF  (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM5_Stop_storage_OFF   ( 6)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM5_Stop_storage_WID   ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM5_Stop_storage_MSK   (0x00000040)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM5_Stop_storage_MAX   (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM5_Stop_storage_DEF   (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM5_SCT0_start_inc_OFF ( 7)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM5_SCT0_start_inc_WID ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM5_SCT0_start_inc_MSK (0x00000080)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM5_SCT0_start_inc_MAX (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM5_SCT0_start_inc_DEF (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM5_SCT1_start_inc_OFF ( 8)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM5_SCT1_start_inc_WID ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM5_SCT1_start_inc_MSK (0x00000100)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM5_SCT1_start_inc_MAX (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM5_SCT1_start_inc_DEF (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM5_SCT2_start_inc_OFF ( 9)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM5_SCT2_start_inc_WID ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM5_SCT2_start_inc_MSK (0x00000200)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM5_SCT2_start_inc_MAX (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM5_SCT2_start_inc_DEF (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM5_SCT3_start_inc_OFF (10)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM5_SCT3_start_inc_WID ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM5_SCT3_start_inc_MSK (0x00000400)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM5_SCT3_start_inc_MAX (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM5_SCT3_start_inc_DEF (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM5_LCT0_start_inc_OFF (11)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM5_LCT0_start_inc_WID ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM5_LCT0_start_inc_MSK (0x00000800)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM5_LCT0_start_inc_MAX (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM5_LCT0_start_inc_DEF (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM5_LCT1_start_inc_OFF (12)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM5_LCT1_start_inc_WID ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM5_LCT1_start_inc_MSK (0x00001000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM5_LCT1_start_inc_MAX (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM5_LCT1_start_inc_DEF (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM5_LCT0_stop_OFF      (15)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM5_LCT0_stop_WID      ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM5_LCT0_stop_MSK      (0x00008000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM5_LCT0_stop_MAX      (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM5_LCT0_stop_DEF      (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM5_LCT1_stop_OFF      (16)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM5_LCT1_stop_WID      ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM5_LCT1_stop_MSK      (0x00010000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM5_LCT1_stop_MAX      (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM5_LCT1_stop_DEF      (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM5_SCT0_clear_OFF     (19)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM5_SCT0_clear_WID     ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM5_SCT0_clear_MSK     (0x00080000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM5_SCT0_clear_MAX     (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM5_SCT0_clear_DEF     (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM5_SCT1_clear_OFF     (20)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM5_SCT1_clear_WID     ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM5_SCT1_clear_MSK     (0x00100000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM5_SCT1_clear_MAX     (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM5_SCT1_clear_DEF     (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM5_SCT2_clear_OFF     (21)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM5_SCT2_clear_WID     ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM5_SCT2_clear_MSK     (0x00200000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM5_SCT2_clear_MAX     (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM5_SCT2_clear_DEF     (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM5_SCT3_clear_OFF     (22)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM5_SCT3_clear_WID     ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM5_SCT3_clear_MSK     (0x00400000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM5_SCT3_clear_MAX     (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM5_SCT3_clear_DEF     (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM5_LCT0_clear_OFF     (23)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM5_LCT0_clear_WID     ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM5_LCT0_clear_MSK     (0x00800000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM5_LCT0_clear_MAX     (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM5_LCT0_clear_DEF     (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM5_LCT1_clear_OFF     (24)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM5_LCT1_clear_WID     ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM5_LCT1_clear_MSK     (0x01000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM5_LCT1_clear_MAX     (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM5_LCT1_clear_DEF     (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM5_Set_state_OFF      (27)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM5_Set_state_WID      ( 4)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM5_Set_state_MSK      (0x78000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM5_Set_state_MAX      (0x0000000F)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM5_Set_state_DEF      (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM5_Set_Signal_value_OFF (31)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM5_Set_Signal_value_WID ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM5_Set_Signal_value_MSK (0x80000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM5_Set_Signal_value_MAX (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM5_Set_Signal_value_DEF (0x00000000)

#define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM6_REG                (0x00000D58)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM6_Set_signal_out_OFF ( 0)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM6_Set_signal_out_WID ( 4)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM6_Set_signal_out_MSK (0x0000000F)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM6_Set_signal_out_MAX (0x0000000F)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM6_Set_signal_out_DEF (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM6_Set_trig_out_OFF   ( 4)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM6_Set_trig_out_WID   ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM6_Set_trig_out_MSK   (0x00000010)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM6_Set_trig_out_MAX   (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM6_Set_trig_out_DEF   (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM6_Start_storage_OFF  ( 5)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM6_Start_storage_WID  ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM6_Start_storage_MSK  (0x00000020)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM6_Start_storage_MAX  (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM6_Start_storage_DEF  (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM6_Stop_storage_OFF   ( 6)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM6_Stop_storage_WID   ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM6_Stop_storage_MSK   (0x00000040)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM6_Stop_storage_MAX   (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM6_Stop_storage_DEF   (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM6_SCT0_start_inc_OFF ( 7)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM6_SCT0_start_inc_WID ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM6_SCT0_start_inc_MSK (0x00000080)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM6_SCT0_start_inc_MAX (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM6_SCT0_start_inc_DEF (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM6_SCT1_start_inc_OFF ( 8)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM6_SCT1_start_inc_WID ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM6_SCT1_start_inc_MSK (0x00000100)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM6_SCT1_start_inc_MAX (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM6_SCT1_start_inc_DEF (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM6_SCT2_start_inc_OFF ( 9)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM6_SCT2_start_inc_WID ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM6_SCT2_start_inc_MSK (0x00000200)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM6_SCT2_start_inc_MAX (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM6_SCT2_start_inc_DEF (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM6_SCT3_start_inc_OFF (10)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM6_SCT3_start_inc_WID ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM6_SCT3_start_inc_MSK (0x00000400)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM6_SCT3_start_inc_MAX (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM6_SCT3_start_inc_DEF (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM6_LCT0_start_inc_OFF (11)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM6_LCT0_start_inc_WID ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM6_LCT0_start_inc_MSK (0x00000800)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM6_LCT0_start_inc_MAX (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM6_LCT0_start_inc_DEF (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM6_LCT1_start_inc_OFF (12)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM6_LCT1_start_inc_WID ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM6_LCT1_start_inc_MSK (0x00001000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM6_LCT1_start_inc_MAX (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM6_LCT1_start_inc_DEF (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM6_LCT0_stop_OFF      (15)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM6_LCT0_stop_WID      ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM6_LCT0_stop_MSK      (0x00008000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM6_LCT0_stop_MAX      (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM6_LCT0_stop_DEF      (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM6_LCT1_stop_OFF      (16)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM6_LCT1_stop_WID      ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM6_LCT1_stop_MSK      (0x00010000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM6_LCT1_stop_MAX      (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM6_LCT1_stop_DEF      (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM6_SCT0_clear_OFF     (19)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM6_SCT0_clear_WID     ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM6_SCT0_clear_MSK     (0x00080000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM6_SCT0_clear_MAX     (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM6_SCT0_clear_DEF     (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM6_SCT1_clear_OFF     (20)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM6_SCT1_clear_WID     ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM6_SCT1_clear_MSK     (0x00100000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM6_SCT1_clear_MAX     (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM6_SCT1_clear_DEF     (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM6_SCT2_clear_OFF     (21)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM6_SCT2_clear_WID     ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM6_SCT2_clear_MSK     (0x00200000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM6_SCT2_clear_MAX     (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM6_SCT2_clear_DEF     (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM6_SCT3_clear_OFF     (22)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM6_SCT3_clear_WID     ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM6_SCT3_clear_MSK     (0x00400000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM6_SCT3_clear_MAX     (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM6_SCT3_clear_DEF     (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM6_LCT0_clear_OFF     (23)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM6_LCT0_clear_WID     ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM6_LCT0_clear_MSK     (0x00800000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM6_LCT0_clear_MAX     (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM6_LCT0_clear_DEF     (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM6_LCT1_clear_OFF     (24)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM6_LCT1_clear_WID     ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM6_LCT1_clear_MSK     (0x01000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM6_LCT1_clear_MAX     (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM6_LCT1_clear_DEF     (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM6_Set_state_OFF      (27)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM6_Set_state_WID      ( 4)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM6_Set_state_MSK      (0x78000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM6_Set_state_MAX      (0x0000000F)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM6_Set_state_DEF      (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM6_Set_Signal_value_OFF (31)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM6_Set_Signal_value_WID ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM6_Set_Signal_value_MSK (0x80000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM6_Set_Signal_value_MAX (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM6_Set_Signal_value_DEF (0x00000000)

#define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM7_REG                (0x00000D5C)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM7_Set_signal_out_OFF ( 0)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM7_Set_signal_out_WID ( 4)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM7_Set_signal_out_MSK (0x0000000F)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM7_Set_signal_out_MAX (0x0000000F)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM7_Set_signal_out_DEF (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM7_Set_trig_out_OFF   ( 4)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM7_Set_trig_out_WID   ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM7_Set_trig_out_MSK   (0x00000010)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM7_Set_trig_out_MAX   (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM7_Set_trig_out_DEF   (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM7_Start_storage_OFF  ( 5)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM7_Start_storage_WID  ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM7_Start_storage_MSK  (0x00000020)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM7_Start_storage_MAX  (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM7_Start_storage_DEF  (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM7_Stop_storage_OFF   ( 6)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM7_Stop_storage_WID   ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM7_Stop_storage_MSK   (0x00000040)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM7_Stop_storage_MAX   (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM7_Stop_storage_DEF   (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM7_SCT0_start_inc_OFF ( 7)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM7_SCT0_start_inc_WID ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM7_SCT0_start_inc_MSK (0x00000080)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM7_SCT0_start_inc_MAX (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM7_SCT0_start_inc_DEF (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM7_SCT1_start_inc_OFF ( 8)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM7_SCT1_start_inc_WID ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM7_SCT1_start_inc_MSK (0x00000100)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM7_SCT1_start_inc_MAX (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM7_SCT1_start_inc_DEF (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM7_SCT2_start_inc_OFF ( 9)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM7_SCT2_start_inc_WID ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM7_SCT2_start_inc_MSK (0x00000200)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM7_SCT2_start_inc_MAX (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM7_SCT2_start_inc_DEF (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM7_SCT3_start_inc_OFF (10)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM7_SCT3_start_inc_WID ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM7_SCT3_start_inc_MSK (0x00000400)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM7_SCT3_start_inc_MAX (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM7_SCT3_start_inc_DEF (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM7_LCT0_start_inc_OFF (11)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM7_LCT0_start_inc_WID ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM7_LCT0_start_inc_MSK (0x00000800)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM7_LCT0_start_inc_MAX (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM7_LCT0_start_inc_DEF (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM7_LCT1_start_inc_OFF (12)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM7_LCT1_start_inc_WID ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM7_LCT1_start_inc_MSK (0x00001000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM7_LCT1_start_inc_MAX (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM7_LCT1_start_inc_DEF (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM7_LCT0_stop_OFF      (15)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM7_LCT0_stop_WID      ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM7_LCT0_stop_MSK      (0x00008000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM7_LCT0_stop_MAX      (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM7_LCT0_stop_DEF      (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM7_LCT1_stop_OFF      (16)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM7_LCT1_stop_WID      ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM7_LCT1_stop_MSK      (0x00010000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM7_LCT1_stop_MAX      (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM7_LCT1_stop_DEF      (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM7_SCT0_clear_OFF     (19)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM7_SCT0_clear_WID     ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM7_SCT0_clear_MSK     (0x00080000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM7_SCT0_clear_MAX     (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM7_SCT0_clear_DEF     (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM7_SCT1_clear_OFF     (20)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM7_SCT1_clear_WID     ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM7_SCT1_clear_MSK     (0x00100000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM7_SCT1_clear_MAX     (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM7_SCT1_clear_DEF     (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM7_SCT2_clear_OFF     (21)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM7_SCT2_clear_WID     ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM7_SCT2_clear_MSK     (0x00200000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM7_SCT2_clear_MAX     (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM7_SCT2_clear_DEF     (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM7_SCT3_clear_OFF     (22)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM7_SCT3_clear_WID     ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM7_SCT3_clear_MSK     (0x00400000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM7_SCT3_clear_MAX     (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM7_SCT3_clear_DEF     (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM7_LCT0_clear_OFF     (23)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM7_LCT0_clear_WID     ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM7_LCT0_clear_MSK     (0x00800000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM7_LCT0_clear_MAX     (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM7_LCT0_clear_DEF     (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM7_LCT1_clear_OFF     (24)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM7_LCT1_clear_WID     ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM7_LCT1_clear_MSK     (0x01000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM7_LCT1_clear_MAX     (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM7_LCT1_clear_DEF     (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM7_Set_state_OFF      (27)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM7_Set_state_WID      ( 4)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM7_Set_state_MSK      (0x78000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM7_Set_state_MAX      (0x0000000F)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM7_Set_state_DEF      (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM7_Set_Signal_value_OFF (31)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM7_Set_Signal_value_WID ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM7_Set_Signal_value_MSK (0x80000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM7_Set_Signal_value_MAX (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM7_Set_Signal_value_DEF (0x00000000)

#define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM8_REG                (0x00000D60)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM8_Set_signal_out_OFF ( 0)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM8_Set_signal_out_WID ( 4)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM8_Set_signal_out_MSK (0x0000000F)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM8_Set_signal_out_MAX (0x0000000F)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM8_Set_signal_out_DEF (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM8_Set_trig_out_OFF   ( 4)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM8_Set_trig_out_WID   ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM8_Set_trig_out_MSK   (0x00000010)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM8_Set_trig_out_MAX   (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM8_Set_trig_out_DEF   (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM8_Start_storage_OFF  ( 5)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM8_Start_storage_WID  ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM8_Start_storage_MSK  (0x00000020)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM8_Start_storage_MAX  (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM8_Start_storage_DEF  (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM8_Stop_storage_OFF   ( 6)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM8_Stop_storage_WID   ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM8_Stop_storage_MSK   (0x00000040)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM8_Stop_storage_MAX   (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM8_Stop_storage_DEF   (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM8_SCT0_start_inc_OFF ( 7)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM8_SCT0_start_inc_WID ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM8_SCT0_start_inc_MSK (0x00000080)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM8_SCT0_start_inc_MAX (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM8_SCT0_start_inc_DEF (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM8_SCT1_start_inc_OFF ( 8)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM8_SCT1_start_inc_WID ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM8_SCT1_start_inc_MSK (0x00000100)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM8_SCT1_start_inc_MAX (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM8_SCT1_start_inc_DEF (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM8_SCT2_start_inc_OFF ( 9)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM8_SCT2_start_inc_WID ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM8_SCT2_start_inc_MSK (0x00000200)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM8_SCT2_start_inc_MAX (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM8_SCT2_start_inc_DEF (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM8_SCT3_start_inc_OFF (10)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM8_SCT3_start_inc_WID ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM8_SCT3_start_inc_MSK (0x00000400)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM8_SCT3_start_inc_MAX (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM8_SCT3_start_inc_DEF (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM8_LCT0_start_inc_OFF (11)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM8_LCT0_start_inc_WID ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM8_LCT0_start_inc_MSK (0x00000800)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM8_LCT0_start_inc_MAX (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM8_LCT0_start_inc_DEF (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM8_LCT1_start_inc_OFF (12)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM8_LCT1_start_inc_WID ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM8_LCT1_start_inc_MSK (0x00001000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM8_LCT1_start_inc_MAX (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM8_LCT1_start_inc_DEF (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM8_LCT0_stop_OFF      (15)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM8_LCT0_stop_WID      ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM8_LCT0_stop_MSK      (0x00008000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM8_LCT0_stop_MAX      (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM8_LCT0_stop_DEF      (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM8_LCT1_stop_OFF      (16)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM8_LCT1_stop_WID      ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM8_LCT1_stop_MSK      (0x00010000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM8_LCT1_stop_MAX      (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM8_LCT1_stop_DEF      (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM8_SCT0_clear_OFF     (19)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM8_SCT0_clear_WID     ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM8_SCT0_clear_MSK     (0x00080000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM8_SCT0_clear_MAX     (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM8_SCT0_clear_DEF     (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM8_SCT1_clear_OFF     (20)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM8_SCT1_clear_WID     ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM8_SCT1_clear_MSK     (0x00100000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM8_SCT1_clear_MAX     (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM8_SCT1_clear_DEF     (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM8_SCT2_clear_OFF     (21)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM8_SCT2_clear_WID     ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM8_SCT2_clear_MSK     (0x00200000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM8_SCT2_clear_MAX     (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM8_SCT2_clear_DEF     (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM8_SCT3_clear_OFF     (22)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM8_SCT3_clear_WID     ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM8_SCT3_clear_MSK     (0x00400000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM8_SCT3_clear_MAX     (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM8_SCT3_clear_DEF     (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM8_LCT0_clear_OFF     (23)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM8_LCT0_clear_WID     ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM8_LCT0_clear_MSK     (0x00800000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM8_LCT0_clear_MAX     (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM8_LCT0_clear_DEF     (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM8_LCT1_clear_OFF     (24)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM8_LCT1_clear_WID     ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM8_LCT1_clear_MSK     (0x01000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM8_LCT1_clear_MAX     (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM8_LCT1_clear_DEF     (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM8_Set_state_OFF      (27)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM8_Set_state_WID      ( 4)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM8_Set_state_MSK      (0x78000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM8_Set_state_MAX      (0x0000000F)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM8_Set_state_DEF      (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM8_Set_Signal_value_OFF (31)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM8_Set_Signal_value_WID ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM8_Set_Signal_value_MSK (0x80000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM8_Set_Signal_value_MAX (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM8_Set_Signal_value_DEF (0x00000000)

#define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM9_REG                (0x00000D64)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM9_Set_signal_out_OFF ( 0)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM9_Set_signal_out_WID ( 4)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM9_Set_signal_out_MSK (0x0000000F)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM9_Set_signal_out_MAX (0x0000000F)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM9_Set_signal_out_DEF (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM9_Set_trig_out_OFF   ( 4)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM9_Set_trig_out_WID   ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM9_Set_trig_out_MSK   (0x00000010)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM9_Set_trig_out_MAX   (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM9_Set_trig_out_DEF   (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM9_Start_storage_OFF  ( 5)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM9_Start_storage_WID  ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM9_Start_storage_MSK  (0x00000020)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM9_Start_storage_MAX  (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM9_Start_storage_DEF  (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM9_Stop_storage_OFF   ( 6)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM9_Stop_storage_WID   ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM9_Stop_storage_MSK   (0x00000040)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM9_Stop_storage_MAX   (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM9_Stop_storage_DEF   (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM9_SCT0_start_inc_OFF ( 7)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM9_SCT0_start_inc_WID ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM9_SCT0_start_inc_MSK (0x00000080)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM9_SCT0_start_inc_MAX (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM9_SCT0_start_inc_DEF (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM9_SCT1_start_inc_OFF ( 8)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM9_SCT1_start_inc_WID ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM9_SCT1_start_inc_MSK (0x00000100)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM9_SCT1_start_inc_MAX (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM9_SCT1_start_inc_DEF (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM9_SCT2_start_inc_OFF ( 9)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM9_SCT2_start_inc_WID ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM9_SCT2_start_inc_MSK (0x00000200)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM9_SCT2_start_inc_MAX (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM9_SCT2_start_inc_DEF (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM9_SCT3_start_inc_OFF (10)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM9_SCT3_start_inc_WID ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM9_SCT3_start_inc_MSK (0x00000400)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM9_SCT3_start_inc_MAX (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM9_SCT3_start_inc_DEF (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM9_LCT0_start_inc_OFF (11)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM9_LCT0_start_inc_WID ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM9_LCT0_start_inc_MSK (0x00000800)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM9_LCT0_start_inc_MAX (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM9_LCT0_start_inc_DEF (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM9_LCT1_start_inc_OFF (12)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM9_LCT1_start_inc_WID ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM9_LCT1_start_inc_MSK (0x00001000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM9_LCT1_start_inc_MAX (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM9_LCT1_start_inc_DEF (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM9_LCT0_stop_OFF      (15)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM9_LCT0_stop_WID      ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM9_LCT0_stop_MSK      (0x00008000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM9_LCT0_stop_MAX      (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM9_LCT0_stop_DEF      (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM9_LCT1_stop_OFF      (16)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM9_LCT1_stop_WID      ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM9_LCT1_stop_MSK      (0x00010000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM9_LCT1_stop_MAX      (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM9_LCT1_stop_DEF      (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM9_SCT0_clear_OFF     (19)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM9_SCT0_clear_WID     ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM9_SCT0_clear_MSK     (0x00080000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM9_SCT0_clear_MAX     (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM9_SCT0_clear_DEF     (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM9_SCT1_clear_OFF     (20)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM9_SCT1_clear_WID     ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM9_SCT1_clear_MSK     (0x00100000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM9_SCT1_clear_MAX     (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM9_SCT1_clear_DEF     (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM9_SCT2_clear_OFF     (21)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM9_SCT2_clear_WID     ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM9_SCT2_clear_MSK     (0x00200000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM9_SCT2_clear_MAX     (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM9_SCT2_clear_DEF     (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM9_SCT3_clear_OFF     (22)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM9_SCT3_clear_WID     ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM9_SCT3_clear_MSK     (0x00400000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM9_SCT3_clear_MAX     (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM9_SCT3_clear_DEF     (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM9_LCT0_clear_OFF     (23)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM9_LCT0_clear_WID     ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM9_LCT0_clear_MSK     (0x00800000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM9_LCT0_clear_MAX     (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM9_LCT0_clear_DEF     (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM9_LCT1_clear_OFF     (24)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM9_LCT1_clear_WID     ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM9_LCT1_clear_MSK     (0x01000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM9_LCT1_clear_MAX     (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM9_LCT1_clear_DEF     (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM9_Set_state_OFF      (27)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM9_Set_state_WID      ( 4)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM9_Set_state_MSK      (0x78000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM9_Set_state_MAX      (0x0000000F)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM9_Set_state_DEF      (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM9_Set_Signal_value_OFF (31)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM9_Set_Signal_value_WID ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM9_Set_Signal_value_MSK (0x80000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM9_Set_Signal_value_MAX (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM9_Set_Signal_value_DEF (0x00000000)

#define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM10_REG               (0x00000D68)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM10_Set_signal_out_OFF ( 0)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM10_Set_signal_out_WID ( 4)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM10_Set_signal_out_MSK (0x0000000F)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM10_Set_signal_out_MAX (0x0000000F)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM10_Set_signal_out_DEF (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM10_Set_trig_out_OFF  ( 4)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM10_Set_trig_out_WID  ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM10_Set_trig_out_MSK  (0x00000010)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM10_Set_trig_out_MAX  (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM10_Set_trig_out_DEF  (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM10_Start_storage_OFF ( 5)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM10_Start_storage_WID ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM10_Start_storage_MSK (0x00000020)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM10_Start_storage_MAX (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM10_Start_storage_DEF (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM10_Stop_storage_OFF  ( 6)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM10_Stop_storage_WID  ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM10_Stop_storage_MSK  (0x00000040)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM10_Stop_storage_MAX  (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM10_Stop_storage_DEF  (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM10_SCT0_start_inc_OFF ( 7)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM10_SCT0_start_inc_WID ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM10_SCT0_start_inc_MSK (0x00000080)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM10_SCT0_start_inc_MAX (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM10_SCT0_start_inc_DEF (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM10_SCT1_start_inc_OFF ( 8)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM10_SCT1_start_inc_WID ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM10_SCT1_start_inc_MSK (0x00000100)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM10_SCT1_start_inc_MAX (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM10_SCT1_start_inc_DEF (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM10_SCT2_start_inc_OFF ( 9)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM10_SCT2_start_inc_WID ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM10_SCT2_start_inc_MSK (0x00000200)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM10_SCT2_start_inc_MAX (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM10_SCT2_start_inc_DEF (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM10_SCT3_start_inc_OFF (10)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM10_SCT3_start_inc_WID ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM10_SCT3_start_inc_MSK (0x00000400)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM10_SCT3_start_inc_MAX (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM10_SCT3_start_inc_DEF (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM10_LCT0_start_inc_OFF (11)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM10_LCT0_start_inc_WID ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM10_LCT0_start_inc_MSK (0x00000800)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM10_LCT0_start_inc_MAX (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM10_LCT0_start_inc_DEF (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM10_LCT1_start_inc_OFF (12)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM10_LCT1_start_inc_WID ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM10_LCT1_start_inc_MSK (0x00001000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM10_LCT1_start_inc_MAX (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM10_LCT1_start_inc_DEF (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM10_LCT0_stop_OFF     (15)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM10_LCT0_stop_WID     ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM10_LCT0_stop_MSK     (0x00008000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM10_LCT0_stop_MAX     (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM10_LCT0_stop_DEF     (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM10_LCT1_stop_OFF     (16)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM10_LCT1_stop_WID     ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM10_LCT1_stop_MSK     (0x00010000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM10_LCT1_stop_MAX     (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM10_LCT1_stop_DEF     (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM10_SCT0_clear_OFF    (19)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM10_SCT0_clear_WID    ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM10_SCT0_clear_MSK    (0x00080000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM10_SCT0_clear_MAX    (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM10_SCT0_clear_DEF    (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM10_SCT1_clear_OFF    (20)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM10_SCT1_clear_WID    ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM10_SCT1_clear_MSK    (0x00100000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM10_SCT1_clear_MAX    (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM10_SCT1_clear_DEF    (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM10_SCT2_clear_OFF    (21)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM10_SCT2_clear_WID    ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM10_SCT2_clear_MSK    (0x00200000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM10_SCT2_clear_MAX    (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM10_SCT2_clear_DEF    (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM10_SCT3_clear_OFF    (22)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM10_SCT3_clear_WID    ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM10_SCT3_clear_MSK    (0x00400000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM10_SCT3_clear_MAX    (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM10_SCT3_clear_DEF    (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM10_LCT0_clear_OFF    (23)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM10_LCT0_clear_WID    ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM10_LCT0_clear_MSK    (0x00800000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM10_LCT0_clear_MAX    (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM10_LCT0_clear_DEF    (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM10_LCT1_clear_OFF    (24)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM10_LCT1_clear_WID    ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM10_LCT1_clear_MSK    (0x01000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM10_LCT1_clear_MAX    (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM10_LCT1_clear_DEF    (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM10_Set_state_OFF     (27)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM10_Set_state_WID     ( 4)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM10_Set_state_MSK     (0x78000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM10_Set_state_MAX     (0x0000000F)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM10_Set_state_DEF     (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM10_Set_Signal_value_OFF (31)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM10_Set_Signal_value_WID ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM10_Set_Signal_value_MSK (0x80000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM10_Set_Signal_value_MAX (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM10_Set_Signal_value_DEF (0x00000000)

#define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM11_REG               (0x00000D6C)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM11_Set_signal_out_OFF ( 0)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM11_Set_signal_out_WID ( 4)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM11_Set_signal_out_MSK (0x0000000F)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM11_Set_signal_out_MAX (0x0000000F)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM11_Set_signal_out_DEF (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM11_Set_trig_out_OFF  ( 4)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM11_Set_trig_out_WID  ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM11_Set_trig_out_MSK  (0x00000010)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM11_Set_trig_out_MAX  (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM11_Set_trig_out_DEF  (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM11_Start_storage_OFF ( 5)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM11_Start_storage_WID ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM11_Start_storage_MSK (0x00000020)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM11_Start_storage_MAX (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM11_Start_storage_DEF (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM11_Stop_storage_OFF  ( 6)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM11_Stop_storage_WID  ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM11_Stop_storage_MSK  (0x00000040)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM11_Stop_storage_MAX  (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM11_Stop_storage_DEF  (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM11_SCT0_start_inc_OFF ( 7)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM11_SCT0_start_inc_WID ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM11_SCT0_start_inc_MSK (0x00000080)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM11_SCT0_start_inc_MAX (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM11_SCT0_start_inc_DEF (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM11_SCT1_start_inc_OFF ( 8)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM11_SCT1_start_inc_WID ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM11_SCT1_start_inc_MSK (0x00000100)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM11_SCT1_start_inc_MAX (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM11_SCT1_start_inc_DEF (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM11_SCT2_start_inc_OFF ( 9)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM11_SCT2_start_inc_WID ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM11_SCT2_start_inc_MSK (0x00000200)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM11_SCT2_start_inc_MAX (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM11_SCT2_start_inc_DEF (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM11_SCT3_start_inc_OFF (10)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM11_SCT3_start_inc_WID ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM11_SCT3_start_inc_MSK (0x00000400)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM11_SCT3_start_inc_MAX (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM11_SCT3_start_inc_DEF (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM11_LCT0_start_inc_OFF (11)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM11_LCT0_start_inc_WID ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM11_LCT0_start_inc_MSK (0x00000800)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM11_LCT0_start_inc_MAX (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM11_LCT0_start_inc_DEF (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM11_LCT1_start_inc_OFF (12)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM11_LCT1_start_inc_WID ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM11_LCT1_start_inc_MSK (0x00001000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM11_LCT1_start_inc_MAX (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM11_LCT1_start_inc_DEF (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM11_LCT0_stop_OFF     (15)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM11_LCT0_stop_WID     ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM11_LCT0_stop_MSK     (0x00008000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM11_LCT0_stop_MAX     (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM11_LCT0_stop_DEF     (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM11_LCT1_stop_OFF     (16)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM11_LCT1_stop_WID     ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM11_LCT1_stop_MSK     (0x00010000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM11_LCT1_stop_MAX     (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM11_LCT1_stop_DEF     (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM11_SCT0_clear_OFF    (19)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM11_SCT0_clear_WID    ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM11_SCT0_clear_MSK    (0x00080000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM11_SCT0_clear_MAX    (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM11_SCT0_clear_DEF    (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM11_SCT1_clear_OFF    (20)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM11_SCT1_clear_WID    ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM11_SCT1_clear_MSK    (0x00100000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM11_SCT1_clear_MAX    (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM11_SCT1_clear_DEF    (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM11_SCT2_clear_OFF    (21)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM11_SCT2_clear_WID    ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM11_SCT2_clear_MSK    (0x00200000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM11_SCT2_clear_MAX    (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM11_SCT2_clear_DEF    (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM11_SCT3_clear_OFF    (22)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM11_SCT3_clear_WID    ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM11_SCT3_clear_MSK    (0x00400000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM11_SCT3_clear_MAX    (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM11_SCT3_clear_DEF    (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM11_LCT0_clear_OFF    (23)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM11_LCT0_clear_WID    ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM11_LCT0_clear_MSK    (0x00800000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM11_LCT0_clear_MAX    (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM11_LCT0_clear_DEF    (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM11_LCT1_clear_OFF    (24)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM11_LCT1_clear_WID    ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM11_LCT1_clear_MSK    (0x01000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM11_LCT1_clear_MAX    (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM11_LCT1_clear_DEF    (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM11_Set_state_OFF     (27)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM11_Set_state_WID     ( 4)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM11_Set_state_MSK     (0x78000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM11_Set_state_MAX     (0x0000000F)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM11_Set_state_DEF     (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM11_Set_Signal_value_OFF (31)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM11_Set_Signal_value_WID ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM11_Set_Signal_value_MSK (0x80000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM11_Set_Signal_value_MAX (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM11_Set_Signal_value_DEF (0x00000000)

#define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM12_REG               (0x00000D70)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM12_Set_signal_out_OFF ( 0)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM12_Set_signal_out_WID ( 4)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM12_Set_signal_out_MSK (0x0000000F)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM12_Set_signal_out_MAX (0x0000000F)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM12_Set_signal_out_DEF (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM12_Set_trig_out_OFF  ( 4)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM12_Set_trig_out_WID  ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM12_Set_trig_out_MSK  (0x00000010)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM12_Set_trig_out_MAX  (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM12_Set_trig_out_DEF  (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM12_Start_storage_OFF ( 5)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM12_Start_storage_WID ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM12_Start_storage_MSK (0x00000020)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM12_Start_storage_MAX (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM12_Start_storage_DEF (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM12_Stop_storage_OFF  ( 6)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM12_Stop_storage_WID  ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM12_Stop_storage_MSK  (0x00000040)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM12_Stop_storage_MAX  (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM12_Stop_storage_DEF  (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM12_SCT0_start_inc_OFF ( 7)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM12_SCT0_start_inc_WID ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM12_SCT0_start_inc_MSK (0x00000080)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM12_SCT0_start_inc_MAX (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM12_SCT0_start_inc_DEF (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM12_SCT1_start_inc_OFF ( 8)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM12_SCT1_start_inc_WID ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM12_SCT1_start_inc_MSK (0x00000100)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM12_SCT1_start_inc_MAX (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM12_SCT1_start_inc_DEF (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM12_SCT2_start_inc_OFF ( 9)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM12_SCT2_start_inc_WID ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM12_SCT2_start_inc_MSK (0x00000200)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM12_SCT2_start_inc_MAX (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM12_SCT2_start_inc_DEF (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM12_SCT3_start_inc_OFF (10)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM12_SCT3_start_inc_WID ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM12_SCT3_start_inc_MSK (0x00000400)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM12_SCT3_start_inc_MAX (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM12_SCT3_start_inc_DEF (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM12_LCT0_start_inc_OFF (11)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM12_LCT0_start_inc_WID ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM12_LCT0_start_inc_MSK (0x00000800)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM12_LCT0_start_inc_MAX (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM12_LCT0_start_inc_DEF (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM12_LCT1_start_inc_OFF (12)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM12_LCT1_start_inc_WID ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM12_LCT1_start_inc_MSK (0x00001000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM12_LCT1_start_inc_MAX (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM12_LCT1_start_inc_DEF (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM12_LCT0_stop_OFF     (15)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM12_LCT0_stop_WID     ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM12_LCT0_stop_MSK     (0x00008000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM12_LCT0_stop_MAX     (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM12_LCT0_stop_DEF     (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM12_LCT1_stop_OFF     (16)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM12_LCT1_stop_WID     ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM12_LCT1_stop_MSK     (0x00010000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM12_LCT1_stop_MAX     (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM12_LCT1_stop_DEF     (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM12_SCT0_clear_OFF    (19)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM12_SCT0_clear_WID    ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM12_SCT0_clear_MSK    (0x00080000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM12_SCT0_clear_MAX    (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM12_SCT0_clear_DEF    (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM12_SCT1_clear_OFF    (20)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM12_SCT1_clear_WID    ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM12_SCT1_clear_MSK    (0x00100000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM12_SCT1_clear_MAX    (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM12_SCT1_clear_DEF    (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM12_SCT2_clear_OFF    (21)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM12_SCT2_clear_WID    ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM12_SCT2_clear_MSK    (0x00200000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM12_SCT2_clear_MAX    (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM12_SCT2_clear_DEF    (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM12_SCT3_clear_OFF    (22)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM12_SCT3_clear_WID    ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM12_SCT3_clear_MSK    (0x00400000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM12_SCT3_clear_MAX    (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM12_SCT3_clear_DEF    (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM12_LCT0_clear_OFF    (23)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM12_LCT0_clear_WID    ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM12_LCT0_clear_MSK    (0x00800000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM12_LCT0_clear_MAX    (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM12_LCT0_clear_DEF    (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM12_LCT1_clear_OFF    (24)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM12_LCT1_clear_WID    ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM12_LCT1_clear_MSK    (0x01000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM12_LCT1_clear_MAX    (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM12_LCT1_clear_DEF    (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM12_Set_state_OFF     (27)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM12_Set_state_WID     ( 4)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM12_Set_state_MSK     (0x78000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM12_Set_state_MAX     (0x0000000F)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM12_Set_state_DEF     (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM12_Set_Signal_value_OFF (31)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM12_Set_Signal_value_WID ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM12_Set_Signal_value_MSK (0x80000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM12_Set_Signal_value_MAX (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM12_Set_Signal_value_DEF (0x00000000)

#define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM13_REG               (0x00000D74)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM13_Set_signal_out_OFF ( 0)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM13_Set_signal_out_WID ( 4)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM13_Set_signal_out_MSK (0x0000000F)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM13_Set_signal_out_MAX (0x0000000F)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM13_Set_signal_out_DEF (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM13_Set_trig_out_OFF  ( 4)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM13_Set_trig_out_WID  ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM13_Set_trig_out_MSK  (0x00000010)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM13_Set_trig_out_MAX  (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM13_Set_trig_out_DEF  (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM13_Start_storage_OFF ( 5)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM13_Start_storage_WID ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM13_Start_storage_MSK (0x00000020)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM13_Start_storage_MAX (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM13_Start_storage_DEF (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM13_Stop_storage_OFF  ( 6)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM13_Stop_storage_WID  ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM13_Stop_storage_MSK  (0x00000040)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM13_Stop_storage_MAX  (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM13_Stop_storage_DEF  (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM13_SCT0_start_inc_OFF ( 7)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM13_SCT0_start_inc_WID ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM13_SCT0_start_inc_MSK (0x00000080)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM13_SCT0_start_inc_MAX (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM13_SCT0_start_inc_DEF (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM13_SCT1_start_inc_OFF ( 8)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM13_SCT1_start_inc_WID ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM13_SCT1_start_inc_MSK (0x00000100)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM13_SCT1_start_inc_MAX (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM13_SCT1_start_inc_DEF (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM13_SCT2_start_inc_OFF ( 9)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM13_SCT2_start_inc_WID ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM13_SCT2_start_inc_MSK (0x00000200)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM13_SCT2_start_inc_MAX (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM13_SCT2_start_inc_DEF (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM13_SCT3_start_inc_OFF (10)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM13_SCT3_start_inc_WID ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM13_SCT3_start_inc_MSK (0x00000400)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM13_SCT3_start_inc_MAX (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM13_SCT3_start_inc_DEF (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM13_LCT0_start_inc_OFF (11)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM13_LCT0_start_inc_WID ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM13_LCT0_start_inc_MSK (0x00000800)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM13_LCT0_start_inc_MAX (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM13_LCT0_start_inc_DEF (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM13_LCT1_start_inc_OFF (12)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM13_LCT1_start_inc_WID ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM13_LCT1_start_inc_MSK (0x00001000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM13_LCT1_start_inc_MAX (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM13_LCT1_start_inc_DEF (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM13_LCT0_stop_OFF     (15)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM13_LCT0_stop_WID     ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM13_LCT0_stop_MSK     (0x00008000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM13_LCT0_stop_MAX     (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM13_LCT0_stop_DEF     (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM13_LCT1_stop_OFF     (16)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM13_LCT1_stop_WID     ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM13_LCT1_stop_MSK     (0x00010000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM13_LCT1_stop_MAX     (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM13_LCT1_stop_DEF     (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM13_SCT0_clear_OFF    (19)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM13_SCT0_clear_WID    ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM13_SCT0_clear_MSK    (0x00080000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM13_SCT0_clear_MAX    (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM13_SCT0_clear_DEF    (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM13_SCT1_clear_OFF    (20)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM13_SCT1_clear_WID    ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM13_SCT1_clear_MSK    (0x00100000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM13_SCT1_clear_MAX    (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM13_SCT1_clear_DEF    (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM13_SCT2_clear_OFF    (21)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM13_SCT2_clear_WID    ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM13_SCT2_clear_MSK    (0x00200000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM13_SCT2_clear_MAX    (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM13_SCT2_clear_DEF    (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM13_SCT3_clear_OFF    (22)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM13_SCT3_clear_WID    ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM13_SCT3_clear_MSK    (0x00400000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM13_SCT3_clear_MAX    (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM13_SCT3_clear_DEF    (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM13_LCT0_clear_OFF    (23)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM13_LCT0_clear_WID    ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM13_LCT0_clear_MSK    (0x00800000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM13_LCT0_clear_MAX    (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM13_LCT0_clear_DEF    (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM13_LCT1_clear_OFF    (24)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM13_LCT1_clear_WID    ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM13_LCT1_clear_MSK    (0x01000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM13_LCT1_clear_MAX    (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM13_LCT1_clear_DEF    (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM13_Set_state_OFF     (27)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM13_Set_state_WID     ( 4)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM13_Set_state_MSK     (0x78000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM13_Set_state_MAX     (0x0000000F)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM13_Set_state_DEF     (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM13_Set_Signal_value_OFF (31)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM13_Set_Signal_value_WID ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM13_Set_Signal_value_MSK (0x80000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM13_Set_Signal_value_MAX (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM13_Set_Signal_value_DEF (0x00000000)

#define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM14_REG               (0x00000D78)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM14_Set_signal_out_OFF ( 0)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM14_Set_signal_out_WID ( 4)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM14_Set_signal_out_MSK (0x0000000F)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM14_Set_signal_out_MAX (0x0000000F)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM14_Set_signal_out_DEF (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM14_Set_trig_out_OFF  ( 4)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM14_Set_trig_out_WID  ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM14_Set_trig_out_MSK  (0x00000010)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM14_Set_trig_out_MAX  (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM14_Set_trig_out_DEF  (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM14_Start_storage_OFF ( 5)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM14_Start_storage_WID ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM14_Start_storage_MSK (0x00000020)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM14_Start_storage_MAX (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM14_Start_storage_DEF (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM14_Stop_storage_OFF  ( 6)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM14_Stop_storage_WID  ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM14_Stop_storage_MSK  (0x00000040)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM14_Stop_storage_MAX  (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM14_Stop_storage_DEF  (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM14_SCT0_start_inc_OFF ( 7)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM14_SCT0_start_inc_WID ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM14_SCT0_start_inc_MSK (0x00000080)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM14_SCT0_start_inc_MAX (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM14_SCT0_start_inc_DEF (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM14_SCT1_start_inc_OFF ( 8)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM14_SCT1_start_inc_WID ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM14_SCT1_start_inc_MSK (0x00000100)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM14_SCT1_start_inc_MAX (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM14_SCT1_start_inc_DEF (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM14_SCT2_start_inc_OFF ( 9)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM14_SCT2_start_inc_WID ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM14_SCT2_start_inc_MSK (0x00000200)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM14_SCT2_start_inc_MAX (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM14_SCT2_start_inc_DEF (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM14_SCT3_start_inc_OFF (10)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM14_SCT3_start_inc_WID ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM14_SCT3_start_inc_MSK (0x00000400)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM14_SCT3_start_inc_MAX (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM14_SCT3_start_inc_DEF (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM14_LCT0_start_inc_OFF (11)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM14_LCT0_start_inc_WID ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM14_LCT0_start_inc_MSK (0x00000800)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM14_LCT0_start_inc_MAX (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM14_LCT0_start_inc_DEF (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM14_LCT1_start_inc_OFF (12)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM14_LCT1_start_inc_WID ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM14_LCT1_start_inc_MSK (0x00001000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM14_LCT1_start_inc_MAX (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM14_LCT1_start_inc_DEF (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM14_LCT0_stop_OFF     (15)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM14_LCT0_stop_WID     ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM14_LCT0_stop_MSK     (0x00008000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM14_LCT0_stop_MAX     (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM14_LCT0_stop_DEF     (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM14_LCT1_stop_OFF     (16)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM14_LCT1_stop_WID     ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM14_LCT1_stop_MSK     (0x00010000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM14_LCT1_stop_MAX     (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM14_LCT1_stop_DEF     (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM14_SCT0_clear_OFF    (19)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM14_SCT0_clear_WID    ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM14_SCT0_clear_MSK    (0x00080000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM14_SCT0_clear_MAX    (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM14_SCT0_clear_DEF    (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM14_SCT1_clear_OFF    (20)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM14_SCT1_clear_WID    ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM14_SCT1_clear_MSK    (0x00100000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM14_SCT1_clear_MAX    (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM14_SCT1_clear_DEF    (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM14_SCT2_clear_OFF    (21)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM14_SCT2_clear_WID    ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM14_SCT2_clear_MSK    (0x00200000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM14_SCT2_clear_MAX    (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM14_SCT2_clear_DEF    (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM14_SCT3_clear_OFF    (22)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM14_SCT3_clear_WID    ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM14_SCT3_clear_MSK    (0x00400000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM14_SCT3_clear_MAX    (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM14_SCT3_clear_DEF    (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM14_LCT0_clear_OFF    (23)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM14_LCT0_clear_WID    ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM14_LCT0_clear_MSK    (0x00800000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM14_LCT0_clear_MAX    (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM14_LCT0_clear_DEF    (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM14_LCT1_clear_OFF    (24)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM14_LCT1_clear_WID    ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM14_LCT1_clear_MSK    (0x01000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM14_LCT1_clear_MAX    (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM14_LCT1_clear_DEF    (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM14_Set_state_OFF     (27)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM14_Set_state_WID     ( 4)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM14_Set_state_MSK     (0x78000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM14_Set_state_MAX     (0x0000000F)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM14_Set_state_DEF     (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM14_Set_Signal_value_OFF (31)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM14_Set_Signal_value_WID ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM14_Set_Signal_value_MSK (0x80000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM14_Set_Signal_value_MAX (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM14_Set_Signal_value_DEF (0x00000000)

#define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM15_REG               (0x00000D7C)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM15_Set_signal_out_OFF ( 0)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM15_Set_signal_out_WID ( 4)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM15_Set_signal_out_MSK (0x0000000F)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM15_Set_signal_out_MAX (0x0000000F)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM15_Set_signal_out_DEF (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM15_Set_trig_out_OFF  ( 4)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM15_Set_trig_out_WID  ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM15_Set_trig_out_MSK  (0x00000010)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM15_Set_trig_out_MAX  (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM15_Set_trig_out_DEF  (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM15_Start_storage_OFF ( 5)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM15_Start_storage_WID ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM15_Start_storage_MSK (0x00000020)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM15_Start_storage_MAX (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM15_Start_storage_DEF (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM15_Stop_storage_OFF  ( 6)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM15_Stop_storage_WID  ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM15_Stop_storage_MSK  (0x00000040)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM15_Stop_storage_MAX  (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM15_Stop_storage_DEF  (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM15_SCT0_start_inc_OFF ( 7)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM15_SCT0_start_inc_WID ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM15_SCT0_start_inc_MSK (0x00000080)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM15_SCT0_start_inc_MAX (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM15_SCT0_start_inc_DEF (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM15_SCT1_start_inc_OFF ( 8)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM15_SCT1_start_inc_WID ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM15_SCT1_start_inc_MSK (0x00000100)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM15_SCT1_start_inc_MAX (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM15_SCT1_start_inc_DEF (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM15_SCT2_start_inc_OFF ( 9)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM15_SCT2_start_inc_WID ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM15_SCT2_start_inc_MSK (0x00000200)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM15_SCT2_start_inc_MAX (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM15_SCT2_start_inc_DEF (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM15_SCT3_start_inc_OFF (10)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM15_SCT3_start_inc_WID ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM15_SCT3_start_inc_MSK (0x00000400)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM15_SCT3_start_inc_MAX (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM15_SCT3_start_inc_DEF (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM15_LCT0_start_inc_OFF (11)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM15_LCT0_start_inc_WID ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM15_LCT0_start_inc_MSK (0x00000800)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM15_LCT0_start_inc_MAX (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM15_LCT0_start_inc_DEF (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM15_LCT1_start_inc_OFF (12)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM15_LCT1_start_inc_WID ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM15_LCT1_start_inc_MSK (0x00001000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM15_LCT1_start_inc_MAX (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM15_LCT1_start_inc_DEF (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM15_LCT0_stop_OFF     (15)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM15_LCT0_stop_WID     ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM15_LCT0_stop_MSK     (0x00008000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM15_LCT0_stop_MAX     (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM15_LCT0_stop_DEF     (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM15_LCT1_stop_OFF     (16)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM15_LCT1_stop_WID     ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM15_LCT1_stop_MSK     (0x00010000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM15_LCT1_stop_MAX     (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM15_LCT1_stop_DEF     (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM15_SCT0_clear_OFF    (19)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM15_SCT0_clear_WID    ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM15_SCT0_clear_MSK    (0x00080000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM15_SCT0_clear_MAX    (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM15_SCT0_clear_DEF    (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM15_SCT1_clear_OFF    (20)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM15_SCT1_clear_WID    ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM15_SCT1_clear_MSK    (0x00100000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM15_SCT1_clear_MAX    (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM15_SCT1_clear_DEF    (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM15_SCT2_clear_OFF    (21)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM15_SCT2_clear_WID    ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM15_SCT2_clear_MSK    (0x00200000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM15_SCT2_clear_MAX    (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM15_SCT2_clear_DEF    (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM15_SCT3_clear_OFF    (22)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM15_SCT3_clear_WID    ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM15_SCT3_clear_MSK    (0x00400000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM15_SCT3_clear_MAX    (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM15_SCT3_clear_DEF    (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM15_LCT0_clear_OFF    (23)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM15_LCT0_clear_WID    ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM15_LCT0_clear_MSK    (0x00800000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM15_LCT0_clear_MAX    (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM15_LCT0_clear_DEF    (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM15_LCT1_clear_OFF    (24)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM15_LCT1_clear_WID    ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM15_LCT1_clear_MSK    (0x01000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM15_LCT1_clear_MAX    (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM15_LCT1_clear_DEF    (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM15_Set_state_OFF     (27)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM15_Set_state_WID     ( 4)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM15_Set_state_MSK     (0x78000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM15_Set_state_MAX     (0x0000000F)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM15_Set_state_DEF     (0x00000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM15_Set_Signal_value_OFF (31)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM15_Set_Signal_value_WID ( 1)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM15_Set_Signal_value_MSK (0x80000000)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM15_Set_Signal_value_MAX (0x00000001)
  #define DDRPL_CR_DDR_CLAUSE_ACTION_CONTROL_CN_SM15_Set_Signal_value_DEF (0x00000000)

#define DDRPL_CR_DDR_SCT0_CONTROL_REG                                (0x00000D80)
  #define DDRPL_CR_DDR_SCT0_CONTROL_SCT0_match_value_OFF               ( 0)
  #define DDRPL_CR_DDR_SCT0_CONTROL_SCT0_match_value_WID               (20)
  #define DDRPL_CR_DDR_SCT0_CONTROL_SCT0_match_value_MSK               (0x000FFFFF)
  #define DDRPL_CR_DDR_SCT0_CONTROL_SCT0_match_value_MAX               (0x000FFFFF)
  #define DDRPL_CR_DDR_SCT0_CONTROL_SCT0_match_value_DEF               (0x00000000)
  #define DDRPL_CR_DDR_SCT0_CONTROL_SCT0_Mode_OFF                      (20)
  #define DDRPL_CR_DDR_SCT0_CONTROL_SCT0_Mode_WID                      ( 1)
  #define DDRPL_CR_DDR_SCT0_CONTROL_SCT0_Mode_MSK                      (0x00100000)
  #define DDRPL_CR_DDR_SCT0_CONTROL_SCT0_Mode_MAX                      (0x00000001)
  #define DDRPL_CR_DDR_SCT0_CONTROL_SCT0_Mode_DEF                      (0x00000000)
  #define DDRPL_CR_DDR_SCT0_CONTROL_SCT0_Timebase_OFF                  (21)
  #define DDRPL_CR_DDR_SCT0_CONTROL_SCT0_Timebase_WID                  ( 1)
  #define DDRPL_CR_DDR_SCT0_CONTROL_SCT0_Timebase_MSK                  (0x00200000)
  #define DDRPL_CR_DDR_SCT0_CONTROL_SCT0_Timebase_MAX                  (0x00000001)
  #define DDRPL_CR_DDR_SCT0_CONTROL_SCT0_Timebase_DEF                  (0x00000000)
  #define DDRPL_CR_DDR_SCT0_CONTROL_SCT0_Mode1_OFF                     (22)
  #define DDRPL_CR_DDR_SCT0_CONTROL_SCT0_Mode1_WID                     ( 1)
  #define DDRPL_CR_DDR_SCT0_CONTROL_SCT0_Mode1_MSK                     (0x00400000)
  #define DDRPL_CR_DDR_SCT0_CONTROL_SCT0_Mode1_MAX                     (0x00000001)
  #define DDRPL_CR_DDR_SCT0_CONTROL_SCT0_Mode1_DEF                     (0x00000000)
  #define DDRPL_CR_DDR_SCT0_CONTROL_SCT0_EventSel_OFF                  (23)
  #define DDRPL_CR_DDR_SCT0_CONTROL_SCT0_EventSel_WID                  ( 4)
  #define DDRPL_CR_DDR_SCT0_CONTROL_SCT0_EventSel_MSK                  (0x07800000)
  #define DDRPL_CR_DDR_SCT0_CONTROL_SCT0_EventSel_MAX                  (0x0000000F)
  #define DDRPL_CR_DDR_SCT0_CONTROL_SCT0_EventSel_DEF                  (0x00000000)

#define DDRPL_CR_DDR_SCT1_CONTROL_REG                                (0x00000D84)
  #define DDRPL_CR_DDR_SCT1_CONTROL_SCT1_match_value_OFF               ( 0)
  #define DDRPL_CR_DDR_SCT1_CONTROL_SCT1_match_value_WID               (20)
  #define DDRPL_CR_DDR_SCT1_CONTROL_SCT1_match_value_MSK               (0x000FFFFF)
  #define DDRPL_CR_DDR_SCT1_CONTROL_SCT1_match_value_MAX               (0x000FFFFF)
  #define DDRPL_CR_DDR_SCT1_CONTROL_SCT1_match_value_DEF               (0x00000000)
  #define DDRPL_CR_DDR_SCT1_CONTROL_SCT1_Mode_OFF                      (20)
  #define DDRPL_CR_DDR_SCT1_CONTROL_SCT1_Mode_WID                      ( 1)
  #define DDRPL_CR_DDR_SCT1_CONTROL_SCT1_Mode_MSK                      (0x00100000)
  #define DDRPL_CR_DDR_SCT1_CONTROL_SCT1_Mode_MAX                      (0x00000001)
  #define DDRPL_CR_DDR_SCT1_CONTROL_SCT1_Mode_DEF                      (0x00000000)
  #define DDRPL_CR_DDR_SCT1_CONTROL_SCT1_Timebase_OFF                  (21)
  #define DDRPL_CR_DDR_SCT1_CONTROL_SCT1_Timebase_WID                  ( 1)
  #define DDRPL_CR_DDR_SCT1_CONTROL_SCT1_Timebase_MSK                  (0x00200000)
  #define DDRPL_CR_DDR_SCT1_CONTROL_SCT1_Timebase_MAX                  (0x00000001)
  #define DDRPL_CR_DDR_SCT1_CONTROL_SCT1_Timebase_DEF                  (0x00000000)
  #define DDRPL_CR_DDR_SCT1_CONTROL_SCT1_Mode1_OFF                     (22)
  #define DDRPL_CR_DDR_SCT1_CONTROL_SCT1_Mode1_WID                     ( 1)
  #define DDRPL_CR_DDR_SCT1_CONTROL_SCT1_Mode1_MSK                     (0x00400000)
  #define DDRPL_CR_DDR_SCT1_CONTROL_SCT1_Mode1_MAX                     (0x00000001)
  #define DDRPL_CR_DDR_SCT1_CONTROL_SCT1_Mode1_DEF                     (0x00000000)
  #define DDRPL_CR_DDR_SCT1_CONTROL_SCT1_EventSel_OFF                  (23)
  #define DDRPL_CR_DDR_SCT1_CONTROL_SCT1_EventSel_WID                  ( 4)
  #define DDRPL_CR_DDR_SCT1_CONTROL_SCT1_EventSel_MSK                  (0x07800000)
  #define DDRPL_CR_DDR_SCT1_CONTROL_SCT1_EventSel_MAX                  (0x0000000F)
  #define DDRPL_CR_DDR_SCT1_CONTROL_SCT1_EventSel_DEF                  (0x00000000)

#define DDRPL_CR_DDR_SCT2_CONTROL_REG                                (0x00000D88)
  #define DDRPL_CR_DDR_SCT2_CONTROL_SCT2_match_value_OFF               ( 0)
  #define DDRPL_CR_DDR_SCT2_CONTROL_SCT2_match_value_WID               (20)
  #define DDRPL_CR_DDR_SCT2_CONTROL_SCT2_match_value_MSK               (0x000FFFFF)
  #define DDRPL_CR_DDR_SCT2_CONTROL_SCT2_match_value_MAX               (0x000FFFFF)
  #define DDRPL_CR_DDR_SCT2_CONTROL_SCT2_match_value_DEF               (0x00000000)
  #define DDRPL_CR_DDR_SCT2_CONTROL_SCT2_Mode_OFF                      (20)
  #define DDRPL_CR_DDR_SCT2_CONTROL_SCT2_Mode_WID                      ( 1)
  #define DDRPL_CR_DDR_SCT2_CONTROL_SCT2_Mode_MSK                      (0x00100000)
  #define DDRPL_CR_DDR_SCT2_CONTROL_SCT2_Mode_MAX                      (0x00000001)
  #define DDRPL_CR_DDR_SCT2_CONTROL_SCT2_Mode_DEF                      (0x00000000)
  #define DDRPL_CR_DDR_SCT2_CONTROL_SCT2_Timebase_OFF                  (21)
  #define DDRPL_CR_DDR_SCT2_CONTROL_SCT2_Timebase_WID                  ( 1)
  #define DDRPL_CR_DDR_SCT2_CONTROL_SCT2_Timebase_MSK                  (0x00200000)
  #define DDRPL_CR_DDR_SCT2_CONTROL_SCT2_Timebase_MAX                  (0x00000001)
  #define DDRPL_CR_DDR_SCT2_CONTROL_SCT2_Timebase_DEF                  (0x00000000)
  #define DDRPL_CR_DDR_SCT2_CONTROL_SCT2_Mode1_OFF                     (22)
  #define DDRPL_CR_DDR_SCT2_CONTROL_SCT2_Mode1_WID                     ( 1)
  #define DDRPL_CR_DDR_SCT2_CONTROL_SCT2_Mode1_MSK                     (0x00400000)
  #define DDRPL_CR_DDR_SCT2_CONTROL_SCT2_Mode1_MAX                     (0x00000001)
  #define DDRPL_CR_DDR_SCT2_CONTROL_SCT2_Mode1_DEF                     (0x00000000)
  #define DDRPL_CR_DDR_SCT2_CONTROL_SCT2_EventSel_OFF                  (23)
  #define DDRPL_CR_DDR_SCT2_CONTROL_SCT2_EventSel_WID                  ( 4)
  #define DDRPL_CR_DDR_SCT2_CONTROL_SCT2_EventSel_MSK                  (0x07800000)
  #define DDRPL_CR_DDR_SCT2_CONTROL_SCT2_EventSel_MAX                  (0x0000000F)
  #define DDRPL_CR_DDR_SCT2_CONTROL_SCT2_EventSel_DEF                  (0x00000000)

#define DDRPL_CR_DDR_SCT3_CONTROL_REG                                (0x00000D8C)
  #define DDRPL_CR_DDR_SCT3_CONTROL_SCT3_match_value_OFF               ( 0)
  #define DDRPL_CR_DDR_SCT3_CONTROL_SCT3_match_value_WID               (20)
  #define DDRPL_CR_DDR_SCT3_CONTROL_SCT3_match_value_MSK               (0x000FFFFF)
  #define DDRPL_CR_DDR_SCT3_CONTROL_SCT3_match_value_MAX               (0x000FFFFF)
  #define DDRPL_CR_DDR_SCT3_CONTROL_SCT3_match_value_DEF               (0x00000000)
  #define DDRPL_CR_DDR_SCT3_CONTROL_SCT3_Mode_OFF                      (20)
  #define DDRPL_CR_DDR_SCT3_CONTROL_SCT3_Mode_WID                      ( 1)
  #define DDRPL_CR_DDR_SCT3_CONTROL_SCT3_Mode_MSK                      (0x00100000)
  #define DDRPL_CR_DDR_SCT3_CONTROL_SCT3_Mode_MAX                      (0x00000001)
  #define DDRPL_CR_DDR_SCT3_CONTROL_SCT3_Mode_DEF                      (0x00000000)
  #define DDRPL_CR_DDR_SCT3_CONTROL_SCT3_Timebase_OFF                  (21)
  #define DDRPL_CR_DDR_SCT3_CONTROL_SCT3_Timebase_WID                  ( 1)
  #define DDRPL_CR_DDR_SCT3_CONTROL_SCT3_Timebase_MSK                  (0x00200000)
  #define DDRPL_CR_DDR_SCT3_CONTROL_SCT3_Timebase_MAX                  (0x00000001)
  #define DDRPL_CR_DDR_SCT3_CONTROL_SCT3_Timebase_DEF                  (0x00000000)
  #define DDRPL_CR_DDR_SCT3_CONTROL_SCT3_Mode1_OFF                     (22)
  #define DDRPL_CR_DDR_SCT3_CONTROL_SCT3_Mode1_WID                     ( 1)
  #define DDRPL_CR_DDR_SCT3_CONTROL_SCT3_Mode1_MSK                     (0x00400000)
  #define DDRPL_CR_DDR_SCT3_CONTROL_SCT3_Mode1_MAX                     (0x00000001)
  #define DDRPL_CR_DDR_SCT3_CONTROL_SCT3_Mode1_DEF                     (0x00000000)
  #define DDRPL_CR_DDR_SCT3_CONTROL_SCT3_EventSel_OFF                  (23)
  #define DDRPL_CR_DDR_SCT3_CONTROL_SCT3_EventSel_WID                  ( 4)
  #define DDRPL_CR_DDR_SCT3_CONTROL_SCT3_EventSel_MSK                  (0x07800000)
  #define DDRPL_CR_DDR_SCT3_CONTROL_SCT3_EventSel_MAX                  (0x0000000F)
  #define DDRPL_CR_DDR_SCT3_CONTROL_SCT3_EventSel_DEF                  (0x00000000)

#define DDRPL_CR_DDR_LCT0_LOWER_CONTROL_REG                          (0x00000D90)
  #define DDRPL_CR_DDR_LCT0_LOWER_CONTROL_LCT0_match_value_OFF         ( 0)
  #define DDRPL_CR_DDR_LCT0_LOWER_CONTROL_LCT0_match_value_WID         (32)
  #define DDRPL_CR_DDR_LCT0_LOWER_CONTROL_LCT0_match_value_MSK         (0xFFFFFFFF)
  #define DDRPL_CR_DDR_LCT0_LOWER_CONTROL_LCT0_match_value_MAX         (0xFFFFFFFF)
  #define DDRPL_CR_DDR_LCT0_LOWER_CONTROL_LCT0_match_value_DEF         (0x00000000)

#define DDRPL_CR_DDR_LCT0_UPPER_CONTROL_REG                          (0x00000D94)
  #define DDRPL_CR_DDR_LCT0_UPPER_CONTROL_LCT0_match_value_OFF         ( 0)
  #define DDRPL_CR_DDR_LCT0_UPPER_CONTROL_LCT0_match_value_WID         (13)
  #define DDRPL_CR_DDR_LCT0_UPPER_CONTROL_LCT0_match_value_MSK         (0x00001FFF)
  #define DDRPL_CR_DDR_LCT0_UPPER_CONTROL_LCT0_match_value_MAX         (0x00001FFF)
  #define DDRPL_CR_DDR_LCT0_UPPER_CONTROL_LCT0_match_value_DEF         (0x00000000)
  #define DDRPL_CR_DDR_LCT0_UPPER_CONTROL_LCT0_Mode_OFF                (13)
  #define DDRPL_CR_DDR_LCT0_UPPER_CONTROL_LCT0_Mode_WID                ( 1)
  #define DDRPL_CR_DDR_LCT0_UPPER_CONTROL_LCT0_Mode_MSK                (0x00002000)
  #define DDRPL_CR_DDR_LCT0_UPPER_CONTROL_LCT0_Mode_MAX                (0x00000001)
  #define DDRPL_CR_DDR_LCT0_UPPER_CONTROL_LCT0_Mode_DEF                (0x00000000)
  #define DDRPL_CR_DDR_LCT0_UPPER_CONTROL_LCT0_Timebase_OFF            (14)
  #define DDRPL_CR_DDR_LCT0_UPPER_CONTROL_LCT0_Timebase_WID            ( 1)
  #define DDRPL_CR_DDR_LCT0_UPPER_CONTROL_LCT0_Timebase_MSK            (0x00004000)
  #define DDRPL_CR_DDR_LCT0_UPPER_CONTROL_LCT0_Timebase_MAX            (0x00000001)
  #define DDRPL_CR_DDR_LCT0_UPPER_CONTROL_LCT0_Timebase_DEF            (0x00000000)
  #define DDRPL_CR_DDR_LCT0_UPPER_CONTROL_LCT0_Mode1_OFF               (15)
  #define DDRPL_CR_DDR_LCT0_UPPER_CONTROL_LCT0_Mode1_WID               ( 1)
  #define DDRPL_CR_DDR_LCT0_UPPER_CONTROL_LCT0_Mode1_MSK               (0x00008000)
  #define DDRPL_CR_DDR_LCT0_UPPER_CONTROL_LCT0_Mode1_MAX               (0x00000001)
  #define DDRPL_CR_DDR_LCT0_UPPER_CONTROL_LCT0_Mode1_DEF               (0x00000000)

#define DDRPL_CR_DDR_LCT1_LOWER_CONTROL_REG                          (0x00000D98)
  #define DDRPL_CR_DDR_LCT1_LOWER_CONTROL_LCT1_match_value_OFF         ( 0)
  #define DDRPL_CR_DDR_LCT1_LOWER_CONTROL_LCT1_match_value_WID         (32)
  #define DDRPL_CR_DDR_LCT1_LOWER_CONTROL_LCT1_match_value_MSK         (0xFFFFFFFF)
  #define DDRPL_CR_DDR_LCT1_LOWER_CONTROL_LCT1_match_value_MAX         (0xFFFFFFFF)
  #define DDRPL_CR_DDR_LCT1_LOWER_CONTROL_LCT1_match_value_DEF         (0x00000000)

#define DDRPL_CR_DDR_LCT1_UPPER_CONTROL_REG                          (0x00000D9C)
  #define DDRPL_CR_DDR_LCT1_UPPER_CONTROL_LCT1_match_value_OFF         ( 0)
  #define DDRPL_CR_DDR_LCT1_UPPER_CONTROL_LCT1_match_value_WID         (13)
  #define DDRPL_CR_DDR_LCT1_UPPER_CONTROL_LCT1_match_value_MSK         (0x00001FFF)
  #define DDRPL_CR_DDR_LCT1_UPPER_CONTROL_LCT1_match_value_MAX         (0x00001FFF)
  #define DDRPL_CR_DDR_LCT1_UPPER_CONTROL_LCT1_match_value_DEF         (0x00000000)
  #define DDRPL_CR_DDR_LCT1_UPPER_CONTROL_LCT1_Mode_OFF                (13)
  #define DDRPL_CR_DDR_LCT1_UPPER_CONTROL_LCT1_Mode_WID                ( 1)
  #define DDRPL_CR_DDR_LCT1_UPPER_CONTROL_LCT1_Mode_MSK                (0x00002000)
  #define DDRPL_CR_DDR_LCT1_UPPER_CONTROL_LCT1_Mode_MAX                (0x00000001)
  #define DDRPL_CR_DDR_LCT1_UPPER_CONTROL_LCT1_Mode_DEF                (0x00000000)
  #define DDRPL_CR_DDR_LCT1_UPPER_CONTROL_LCT1_Timebase_OFF            (14)
  #define DDRPL_CR_DDR_LCT1_UPPER_CONTROL_LCT1_Timebase_WID            ( 1)
  #define DDRPL_CR_DDR_LCT1_UPPER_CONTROL_LCT1_Timebase_MSK            (0x00004000)
  #define DDRPL_CR_DDR_LCT1_UPPER_CONTROL_LCT1_Timebase_MAX            (0x00000001)
  #define DDRPL_CR_DDR_LCT1_UPPER_CONTROL_LCT1_Timebase_DEF            (0x00000000)
  #define DDRPL_CR_DDR_LCT1_UPPER_CONTROL_LCT1_Mode1_OFF               (15)
  #define DDRPL_CR_DDR_LCT1_UPPER_CONTROL_LCT1_Mode1_WID               ( 1)
  #define DDRPL_CR_DDR_LCT1_UPPER_CONTROL_LCT1_Mode1_MSK               (0x00008000)
  #define DDRPL_CR_DDR_LCT1_UPPER_CONTROL_LCT1_Mode1_MAX               (0x00000001)
  #define DDRPL_CR_DDR_LCT1_UPPER_CONTROL_LCT1_Mode1_DEF               (0x00000000)

#define DDRPL_CR_DDR_SCT0_CURRENT_STATUS_REG                         (0x00000DA0)
  #define DDRPL_CR_DDR_SCT0_CURRENT_STATUS_SCT0_current_value_OFF      ( 0)
  #define DDRPL_CR_DDR_SCT0_CURRENT_STATUS_SCT0_current_value_WID      (20)
  #define DDRPL_CR_DDR_SCT0_CURRENT_STATUS_SCT0_current_value_MSK      (0x000FFFFF)
  #define DDRPL_CR_DDR_SCT0_CURRENT_STATUS_SCT0_current_value_MAX      (0x000FFFFF)
  #define DDRPL_CR_DDR_SCT0_CURRENT_STATUS_SCT0_current_value_DEF      (0x00000000)
  #define DDRPL_CR_DDR_SCT0_CURRENT_STATUS_SCT0_Running_OFF            (20)
  #define DDRPL_CR_DDR_SCT0_CURRENT_STATUS_SCT0_Running_WID            ( 1)
  #define DDRPL_CR_DDR_SCT0_CURRENT_STATUS_SCT0_Running_MSK            (0x00100000)
  #define DDRPL_CR_DDR_SCT0_CURRENT_STATUS_SCT0_Running_MAX            (0x00000001)
  #define DDRPL_CR_DDR_SCT0_CURRENT_STATUS_SCT0_Running_DEF            (0x00000000)

#define DDRPL_CR_DDR_SCT1_CURRENT_STATUS_REG                         (0x00000DA4)
  #define DDRPL_CR_DDR_SCT1_CURRENT_STATUS_SCT1_current_value_OFF      ( 0)
  #define DDRPL_CR_DDR_SCT1_CURRENT_STATUS_SCT1_current_value_WID      (20)
  #define DDRPL_CR_DDR_SCT1_CURRENT_STATUS_SCT1_current_value_MSK      (0x000FFFFF)
  #define DDRPL_CR_DDR_SCT1_CURRENT_STATUS_SCT1_current_value_MAX      (0x000FFFFF)
  #define DDRPL_CR_DDR_SCT1_CURRENT_STATUS_SCT1_current_value_DEF      (0x00000000)
  #define DDRPL_CR_DDR_SCT1_CURRENT_STATUS_SCT1_Running_OFF            (20)
  #define DDRPL_CR_DDR_SCT1_CURRENT_STATUS_SCT1_Running_WID            ( 1)
  #define DDRPL_CR_DDR_SCT1_CURRENT_STATUS_SCT1_Running_MSK            (0x00100000)
  #define DDRPL_CR_DDR_SCT1_CURRENT_STATUS_SCT1_Running_MAX            (0x00000001)
  #define DDRPL_CR_DDR_SCT1_CURRENT_STATUS_SCT1_Running_DEF            (0x00000000)

#define DDRPL_CR_DDR_SCT2_CURRENT_STATUS_REG                         (0x00000DA8)
  #define DDRPL_CR_DDR_SCT2_CURRENT_STATUS_SCT2_current_value_OFF      ( 0)
  #define DDRPL_CR_DDR_SCT2_CURRENT_STATUS_SCT2_current_value_WID      (20)
  #define DDRPL_CR_DDR_SCT2_CURRENT_STATUS_SCT2_current_value_MSK      (0x000FFFFF)
  #define DDRPL_CR_DDR_SCT2_CURRENT_STATUS_SCT2_current_value_MAX      (0x000FFFFF)
  #define DDRPL_CR_DDR_SCT2_CURRENT_STATUS_SCT2_current_value_DEF      (0x00000000)
  #define DDRPL_CR_DDR_SCT2_CURRENT_STATUS_SCT2_Running_OFF            (20)
  #define DDRPL_CR_DDR_SCT2_CURRENT_STATUS_SCT2_Running_WID            ( 1)
  #define DDRPL_CR_DDR_SCT2_CURRENT_STATUS_SCT2_Running_MSK            (0x00100000)
  #define DDRPL_CR_DDR_SCT2_CURRENT_STATUS_SCT2_Running_MAX            (0x00000001)
  #define DDRPL_CR_DDR_SCT2_CURRENT_STATUS_SCT2_Running_DEF            (0x00000000)

#define DDRPL_CR_DDR_SCT3_CURRENT_STATUS_REG                         (0x00000DAC)
  #define DDRPL_CR_DDR_SCT3_CURRENT_STATUS_SCT3_current_value_OFF      ( 0)
  #define DDRPL_CR_DDR_SCT3_CURRENT_STATUS_SCT3_current_value_WID      (20)
  #define DDRPL_CR_DDR_SCT3_CURRENT_STATUS_SCT3_current_value_MSK      (0x000FFFFF)
  #define DDRPL_CR_DDR_SCT3_CURRENT_STATUS_SCT3_current_value_MAX      (0x000FFFFF)
  #define DDRPL_CR_DDR_SCT3_CURRENT_STATUS_SCT3_current_value_DEF      (0x00000000)
  #define DDRPL_CR_DDR_SCT3_CURRENT_STATUS_SCT3_Running_OFF            (20)
  #define DDRPL_CR_DDR_SCT3_CURRENT_STATUS_SCT3_Running_WID            ( 1)
  #define DDRPL_CR_DDR_SCT3_CURRENT_STATUS_SCT3_Running_MSK            (0x00100000)
  #define DDRPL_CR_DDR_SCT3_CURRENT_STATUS_SCT3_Running_MAX            (0x00000001)
  #define DDRPL_CR_DDR_SCT3_CURRENT_STATUS_SCT3_Running_DEF            (0x00000000)

#define DDRPL_CR_DDR_LCT0_LOWER_CURRENT_STATUS_REG                   (0x00000DB0)
  #define DDRPL_CR_DDR_LCT0_LOWER_CURRENT_STATUS_LCT0_current_value_OFF ( 0)
  #define DDRPL_CR_DDR_LCT0_LOWER_CURRENT_STATUS_LCT0_current_value_WID (32)
  #define DDRPL_CR_DDR_LCT0_LOWER_CURRENT_STATUS_LCT0_current_value_MSK (0xFFFFFFFF)
  #define DDRPL_CR_DDR_LCT0_LOWER_CURRENT_STATUS_LCT0_current_value_MAX (0xFFFFFFFF)
  #define DDRPL_CR_DDR_LCT0_LOWER_CURRENT_STATUS_LCT0_current_value_DEF (0x00000000)

#define DDRPL_CR_DDR_LCT0_UPPER_CURRENT_STATUS_REG                   (0x00000DB4)
  #define DDRPL_CR_DDR_LCT0_UPPER_CURRENT_STATUS_LCT0_current_value_OFF ( 0)
  #define DDRPL_CR_DDR_LCT0_UPPER_CURRENT_STATUS_LCT0_current_value_WID (13)
  #define DDRPL_CR_DDR_LCT0_UPPER_CURRENT_STATUS_LCT0_current_value_MSK (0x00001FFF)
  #define DDRPL_CR_DDR_LCT0_UPPER_CURRENT_STATUS_LCT0_current_value_MAX (0x00001FFF)
  #define DDRPL_CR_DDR_LCT0_UPPER_CURRENT_STATUS_LCT0_current_value_DEF (0x00000000)
  #define DDRPL_CR_DDR_LCT0_UPPER_CURRENT_STATUS_LCT0_Running_OFF      (13)
  #define DDRPL_CR_DDR_LCT0_UPPER_CURRENT_STATUS_LCT0_Running_WID      ( 1)
  #define DDRPL_CR_DDR_LCT0_UPPER_CURRENT_STATUS_LCT0_Running_MSK      (0x00002000)
  #define DDRPL_CR_DDR_LCT0_UPPER_CURRENT_STATUS_LCT0_Running_MAX      (0x00000001)
  #define DDRPL_CR_DDR_LCT0_UPPER_CURRENT_STATUS_LCT0_Running_DEF      (0x00000000)

#define DDRPL_CR_DDR_LCT1_LOWER_CURRENT_STATUS_REG                   (0x00000DB8)
  #define DDRPL_CR_DDR_LCT1_LOWER_CURRENT_STATUS_LCT1_current_value_OFF ( 0)
  #define DDRPL_CR_DDR_LCT1_LOWER_CURRENT_STATUS_LCT1_current_value_WID (32)
  #define DDRPL_CR_DDR_LCT1_LOWER_CURRENT_STATUS_LCT1_current_value_MSK (0xFFFFFFFF)
  #define DDRPL_CR_DDR_LCT1_LOWER_CURRENT_STATUS_LCT1_current_value_MAX (0xFFFFFFFF)
  #define DDRPL_CR_DDR_LCT1_LOWER_CURRENT_STATUS_LCT1_current_value_DEF (0x00000000)

#define DDRPL_CR_DDR_LCT1_UPPER_CURRENT_STATUS_REG                   (0x00000DBC)
  #define DDRPL_CR_DDR_LCT1_UPPER_CURRENT_STATUS_LCT1_current_value_OFF ( 0)
  #define DDRPL_CR_DDR_LCT1_UPPER_CURRENT_STATUS_LCT1_current_value_WID (13)
  #define DDRPL_CR_DDR_LCT1_UPPER_CURRENT_STATUS_LCT1_current_value_MSK (0x00001FFF)
  #define DDRPL_CR_DDR_LCT1_UPPER_CURRENT_STATUS_LCT1_current_value_MAX (0x00001FFF)
  #define DDRPL_CR_DDR_LCT1_UPPER_CURRENT_STATUS_LCT1_current_value_DEF (0x00000000)
  #define DDRPL_CR_DDR_LCT1_UPPER_CURRENT_STATUS_LCT1_Running_OFF      (13)
  #define DDRPL_CR_DDR_LCT1_UPPER_CURRENT_STATUS_LCT1_Running_WID      ( 1)
  #define DDRPL_CR_DDR_LCT1_UPPER_CURRENT_STATUS_LCT1_Running_MSK      (0x00002000)
  #define DDRPL_CR_DDR_LCT1_UPPER_CURRENT_STATUS_LCT1_Running_MAX      (0x00000001)
  #define DDRPL_CR_DDR_LCT1_UPPER_CURRENT_STATUS_LCT1_Running_DEF      (0x00000000)

#define DDRPL_CR_DDR_CTS_STATUS_REG                                  (0x00000DC0)
  #define DDRPL_CR_DDR_CTS_STATUS_Sequencer_State_OFF                  ( 0)
  #define DDRPL_CR_DDR_CTS_STATUS_Sequencer_State_WID                  ( 4)
  #define DDRPL_CR_DDR_CTS_STATUS_Sequencer_State_MSK                  (0x0000000F)
  #define DDRPL_CR_DDR_CTS_STATUS_Sequencer_State_MAX                  (0x0000000F)
  #define DDRPL_CR_DDR_CTS_STATUS_Sequencer_State_DEF                  (0x00000000)
  #define DDRPL_CR_DDR_CTS_STATUS_Sequencer_Trig_OFF                   ( 4)
  #define DDRPL_CR_DDR_CTS_STATUS_Sequencer_Trig_WID                   ( 1)
  #define DDRPL_CR_DDR_CTS_STATUS_Sequencer_Trig_MSK                   (0x00000010)
  #define DDRPL_CR_DDR_CTS_STATUS_Sequencer_Trig_MAX                   (0x00000001)
  #define DDRPL_CR_DDR_CTS_STATUS_Sequencer_Trig_DEF                   (0x00000000)
  #define DDRPL_CR_DDR_CTS_STATUS_Stor_Qual_Initial_Value_OFF          ( 5)
  #define DDRPL_CR_DDR_CTS_STATUS_Stor_Qual_Initial_Value_WID          ( 1)
  #define DDRPL_CR_DDR_CTS_STATUS_Stor_Qual_Initial_Value_MSK          (0x00000020)
  #define DDRPL_CR_DDR_CTS_STATUS_Stor_Qual_Initial_Value_MAX          (0x00000001)
  #define DDRPL_CR_DDR_CTS_STATUS_Stor_Qual_Initial_Value_DEF          (0x00000000)
  #define DDRPL_CR_DDR_CTS_STATUS_Signal_Out_Status_OFF                ( 6)
  #define DDRPL_CR_DDR_CTS_STATUS_Signal_Out_Status_WID                ( 4)
  #define DDRPL_CR_DDR_CTS_STATUS_Signal_Out_Status_MSK                (0x000003C0)
  #define DDRPL_CR_DDR_CTS_STATUS_Signal_Out_Status_MAX                (0x0000000F)
  #define DDRPL_CR_DDR_CTS_STATUS_Signal_Out_Status_DEF                (0x00000000)
  #define DDRPL_CR_DDR_CTS_STATUS_CTS_Revision_OFF                     (10)
  #define DDRPL_CR_DDR_CTS_STATUS_CTS_Revision_WID                     ( 3)
  #define DDRPL_CR_DDR_CTS_STATUS_CTS_Revision_MSK                     (0x00001C00)
  #define DDRPL_CR_DDR_CTS_STATUS_CTS_Revision_MAX                     (0x00000007)
  #define DDRPL_CR_DDR_CTS_STATUS_CTS_Revision_DEF                     (0x00000001)
  #define DDRPL_CR_DDR_CTS_STATUS_CTS_Pipelined_OFF                    (13)
  #define DDRPL_CR_DDR_CTS_STATUS_CTS_Pipelined_WID                    ( 1)
  #define DDRPL_CR_DDR_CTS_STATUS_CTS_Pipelined_MSK                    (0x00002000)
  #define DDRPL_CR_DDR_CTS_STATUS_CTS_Pipelined_MAX                    (0x00000001)
  #define DDRPL_CR_DDR_CTS_STATUS_CTS_Pipelined_DEF                    (0x00000000)
  #define DDRPL_CR_DDR_CTS_STATUS_Stor_Qual_Initial_Value1_OFF         (16)
  #define DDRPL_CR_DDR_CTS_STATUS_Stor_Qual_Initial_Value1_WID         ( 7)
  #define DDRPL_CR_DDR_CTS_STATUS_Stor_Qual_Initial_Value1_MSK         (0x007F0000)
  #define DDRPL_CR_DDR_CTS_STATUS_Stor_Qual_Initial_Value1_MAX         (0x0000007F)
  #define DDRPL_CR_DDR_CTS_STATUS_Stor_Qual_Initial_Value1_DEF         (0x00000000)

#define DDRPL_CR_DDR_CTS_CONTROL_REG                                 (0x00000DC4)
  #define DDRPL_CR_DDR_CTS_CONTROL_Sequencer_Enable_OFF                ( 0)
  #define DDRPL_CR_DDR_CTS_CONTROL_Sequencer_Enable_WID                ( 1)
  #define DDRPL_CR_DDR_CTS_CONTROL_Sequencer_Enable_MSK                (0x00000001)
  #define DDRPL_CR_DDR_CTS_CONTROL_Sequencer_Enable_MAX                (0x00000001)
  #define DDRPL_CR_DDR_CTS_CONTROL_Sequencer_Enable_DEF                (0x00000000)
  #define DDRPL_CR_DDR_CTS_CONTROL_Event_In_edge_det_OFF               ( 1)
  #define DDRPL_CR_DDR_CTS_CONTROL_Event_In_edge_det_WID               (16)
  #define DDRPL_CR_DDR_CTS_CONTROL_Event_In_edge_det_MSK               (0x0001FFFE)
  #define DDRPL_CR_DDR_CTS_CONTROL_Event_In_edge_det_MAX               (0x0000FFFF)
  #define DDRPL_CR_DDR_CTS_CONTROL_Force_State_OFF                     (17)
  #define DDRPL_CR_DDR_CTS_CONTROL_Force_State_WID                     ( 1)
  #define DDRPL_CR_DDR_CTS_CONTROL_Force_State_MSK                     (0x00020000)
  #define DDRPL_CR_DDR_CTS_CONTROL_Force_State_MAX                     (0x00000001)
  #define DDRPL_CR_DDR_CTS_CONTROL_Force_State_DEF                     (0x00000000)
  #define DDRPL_CR_DDR_CTS_CONTROL_Update_Status_OFF                   (18)
  #define DDRPL_CR_DDR_CTS_CONTROL_Update_Status_WID                   ( 1)
  #define DDRPL_CR_DDR_CTS_CONTROL_Update_Status_MSK                   (0x00040000)
  #define DDRPL_CR_DDR_CTS_CONTROL_Update_Status_MAX                   (0x00000001)
  #define DDRPL_CR_DDR_CTS_CONTROL_Update_Status_DEF                   (0x00000000)
  #define DDRPL_CR_DDR_CTS_CONTROL_Signal_In_edge_det_OFF              (19)
  #define DDRPL_CR_DDR_CTS_CONTROL_Signal_In_edge_det_WID              ( 1)
  #define DDRPL_CR_DDR_CTS_CONTROL_Signal_In_edge_det_MSK              (0x00080000)
  #define DDRPL_CR_DDR_CTS_CONTROL_Signal_In_edge_det_MAX              (0x00000001)
  #define DDRPL_CR_DDR_CTS_CONTROL_Signal_In_edge_det_DEF              (0x00000000)
  #define DDRPL_CR_DDR_CTS_CONTROL_Signal_Out_mode_OFF                 (20)
  #define DDRPL_CR_DDR_CTS_CONTROL_Signal_Out_mode_WID                 ( 2)
  #define DDRPL_CR_DDR_CTS_CONTROL_Signal_Out_mode_MSK                 (0x00300000)
  #define DDRPL_CR_DDR_CTS_CONTROL_Signal_Out_mode_MAX                 (0x00000003)
  #define DDRPL_CR_DDR_CTS_CONTROL_Signal_Out_mode_DEF                 (0x00000000)
  #define DDRPL_CR_DDR_CTS_CONTROL_CTS_triggered_once_OFF              (31)
  #define DDRPL_CR_DDR_CTS_CONTROL_CTS_triggered_once_WID              ( 1)
  #define DDRPL_CR_DDR_CTS_CONTROL_CTS_triggered_once_MSK              (0x80000000)
  #define DDRPL_CR_DDR_CTS_CONTROL_CTS_triggered_once_MAX              (0x00000001)
  #define DDRPL_CR_DDR_CTS_CONTROL_CTS_triggered_once_DEF              (0x00000000)

#define DDRPL_CR_DDR_PARAMETER_STATUS_REG                            (0x00000DC8)
  #define DDRPL_CR_DDR_PARAMETER_STATUS_Num_Stor_Qual_OFF              ( 0)
  #define DDRPL_CR_DDR_PARAMETER_STATUS_Num_Stor_Qual_WID              ( 3)
  #define DDRPL_CR_DDR_PARAMETER_STATUS_Num_Stor_Qual_MSK              (0x00000007)
  #define DDRPL_CR_DDR_PARAMETER_STATUS_Num_Stor_Qual_MAX              (0x00000007)
  #define DDRPL_CR_DDR_PARAMETER_STATUS_Num_Stor_Qual_DEF              (0x00000000)
  #define DDRPL_CR_DDR_PARAMETER_STATUS_Peak_Timer_Selected_OFF        ( 3)
  #define DDRPL_CR_DDR_PARAMETER_STATUS_Peak_Timer_Selected_WID        ( 1)
  #define DDRPL_CR_DDR_PARAMETER_STATUS_Peak_Timer_Selected_MSK        (0x00000008)
  #define DDRPL_CR_DDR_PARAMETER_STATUS_Peak_Timer_Selected_MAX        (0x00000001)
  #define DDRPL_CR_DDR_PARAMETER_STATUS_Peak_Timer_Selected_DEF        (0x00000000)
  #define DDRPL_CR_DDR_PARAMETER_STATUS_LCT_Size_OFF                   ( 4)
  #define DDRPL_CR_DDR_PARAMETER_STATUS_LCT_Size_WID                   ( 6)
  #define DDRPL_CR_DDR_PARAMETER_STATUS_LCT_Size_MSK                   (0x000003F0)
  #define DDRPL_CR_DDR_PARAMETER_STATUS_LCT_Size_MAX                   (0x0000003F)
  #define DDRPL_CR_DDR_PARAMETER_STATUS_LCT_Size_DEF                   (0x00000000)
  #define DDRPL_CR_DDR_PARAMETER_STATUS_NUM_LCTs_OFF                   (10)
  #define DDRPL_CR_DDR_PARAMETER_STATUS_NUM_LCTs_WID                   ( 3)
  #define DDRPL_CR_DDR_PARAMETER_STATUS_NUM_LCTs_MSK                   (0x00001C00)
  #define DDRPL_CR_DDR_PARAMETER_STATUS_NUM_LCTs_MAX                   (0x00000007)
  #define DDRPL_CR_DDR_PARAMETER_STATUS_NUM_LCTs_DEF                   (0x00000000)
  #define DDRPL_CR_DDR_PARAMETER_STATUS_NUM_SCTs_OFF                   (13)
  #define DDRPL_CR_DDR_PARAMETER_STATUS_NUM_SCTs_WID                   ( 3)
  #define DDRPL_CR_DDR_PARAMETER_STATUS_NUM_SCTs_MSK                   (0x0000E000)
  #define DDRPL_CR_DDR_PARAMETER_STATUS_NUM_SCTs_MAX                   (0x00000007)
  #define DDRPL_CR_DDR_PARAMETER_STATUS_NUM_SCTs_DEF                   (0x00000000)
  #define DDRPL_CR_DDR_PARAMETER_STATUS_NUM_Signals_OFF                (16)
  #define DDRPL_CR_DDR_PARAMETER_STATUS_NUM_Signals_WID                ( 2)
  #define DDRPL_CR_DDR_PARAMETER_STATUS_NUM_Signals_MSK                (0x00030000)
  #define DDRPL_CR_DDR_PARAMETER_STATUS_NUM_Signals_MAX                (0x00000003)
  #define DDRPL_CR_DDR_PARAMETER_STATUS_NUM_Signals_DEF                (0x00000000)
  #define DDRPL_CR_DDR_PARAMETER_STATUS_NUM_Events_OFF                 (18)
  #define DDRPL_CR_DDR_PARAMETER_STATUS_NUM_Events_WID                 ( 4)
  #define DDRPL_CR_DDR_PARAMETER_STATUS_NUM_Events_MSK                 (0x003C0000)
  #define DDRPL_CR_DDR_PARAMETER_STATUS_NUM_Events_MAX                 (0x0000000F)
  #define DDRPL_CR_DDR_PARAMETER_STATUS_NUM_Events_DEF                 (0x00000000)
  #define DDRPL_CR_DDR_PARAMETER_STATUS_NUM_Clauses_OFF                (22)
  #define DDRPL_CR_DDR_PARAMETER_STATUS_NUM_Clauses_WID                ( 3)
  #define DDRPL_CR_DDR_PARAMETER_STATUS_NUM_Clauses_MSK                (0x01C00000)
  #define DDRPL_CR_DDR_PARAMETER_STATUS_NUM_Clauses_MAX                (0x00000007)
  #define DDRPL_CR_DDR_PARAMETER_STATUS_NUM_Clauses_DEF                (0x00000000)
  #define DDRPL_CR_DDR_PARAMETER_STATUS_NUM_States_OFF                 (25)
  #define DDRPL_CR_DDR_PARAMETER_STATUS_NUM_States_WID                 ( 3)
  #define DDRPL_CR_DDR_PARAMETER_STATUS_NUM_States_MSK                 (0x0E000000)
  #define DDRPL_CR_DDR_PARAMETER_STATUS_NUM_States_MAX                 (0x00000007)
  #define DDRPL_CR_DDR_PARAMETER_STATUS_NUM_States_DEF                 (0x00000000)

#define DDRPL_CR_DDR_CTS_FW_UPDATE_STATUS_REG                        (0x00000DCC)
  #define DDRPL_CR_DDR_CTS_FW_UPDATE_STATUS_Reserved_OFF               ( 0)
  #define DDRPL_CR_DDR_CTS_FW_UPDATE_STATUS_Reserved_WID               ( 1)
  #define DDRPL_CR_DDR_CTS_FW_UPDATE_STATUS_Reserved_MSK               (0x00000001)
  #define DDRPL_CR_DDR_CTS_FW_UPDATE_STATUS_Reserved_MAX               (0x00000001)
  #define DDRPL_CR_DDR_CTS_FW_UPDATE_STATUS_Reserved_DEF               (0x00000000)

#pragma pack(pop)
#endif  // __McGdxcbar_h__
