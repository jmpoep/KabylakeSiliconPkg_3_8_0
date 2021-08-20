#ifndef __MrcMcRegisterStruct4xxx_h__
#define __MrcMcRegisterStruct4xxx_h__
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
    UINT32 tRP                                     :  6;  // Bits 5:0
    UINT32 tRPab_ext                               :  2;  // Bits 7:6
    UINT32 tRAS                                    :  7;  // Bits 14:8
    UINT32                                         :  1;  // Bits 15:15
    UINT32 tRDPRE                                  :  4;  // Bits 19:16
    UINT32                                         :  4;  // Bits 23:20
    UINT32 tWRPRE                                  :  7;  // Bits 30:24
    UINT32                                         :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCHBAR_CH0_CR_TC_PRE_STRUCT;

typedef union {
  struct {
    UINT32 tFAW                                    :  6;  // Bits 5:0
    UINT32                                         :  2;  // Bits 7:6
    UINT32 tRRD_sg                                 :  4;  // Bits 11:8
    UINT32 tRRD_dg                                 :  4;  // Bits 15:12
    UINT32 derating_ext                            :  2;  // Bits 17:16
    UINT32                                         :  14;  // Bits 31:18
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCHBAR_CH0_CR_TC_ACT_STRUCT;

typedef union {
  struct {
    UINT32 tCKE                                    :  4;  // Bits 3:0
    UINT32 tXP                                     :  4;  // Bits 7:4
    UINT32 tXPDLL                                  :  6;  // Bits 13:8
    UINT32 tPRPDEN                                 :  2;  // Bits 15:14
    UINT32 tRDPDEN                                 :  7;  // Bits 22:16
    UINT32                                         :  1;  // Bits 23:23
    UINT32 tWRPDEN                                 :  7;  // Bits 30:24
    UINT32                                         :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCHBAR_CH0_CR_TC_PWRDN_STRUCT;

typedef union {
  struct {
    UINT32 tRDRD_sg                                :  6;  // Bits 5:0
    UINT32                                         :  2;  // Bits 7:6
    UINT32 tRDRD_dg                                :  6;  // Bits 13:8
    UINT32                                         :  2;  // Bits 15:14
    UINT32 tRDRD_dr                                :  6;  // Bits 21:16
    UINT32                                         :  2;  // Bits 23:22
    UINT32 tRDRD_dd                                :  6;  // Bits 29:24
    UINT32                                         :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCHBAR_CH0_CR_TC_RDRD_STRUCT;

typedef union {
  struct {
    UINT32 tRDWR_sg                                :  6;  // Bits 5:0
    UINT32                                         :  2;  // Bits 7:6
    UINT32 tRDWR_dg                                :  6;  // Bits 13:8
    UINT32                                         :  2;  // Bits 15:14
    UINT32 tRDWR_dr                                :  6;  // Bits 21:16
    UINT32                                         :  2;  // Bits 23:22
    UINT32 tRDWR_dd                                :  6;  // Bits 29:24
    UINT32                                         :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCHBAR_CH0_CR_TC_RDWR_STRUCT;

typedef union {
  struct {
    UINT32 tWRRD_sg                                :  7;  // Bits 6:0
    UINT32                                         :  1;  // Bits 7:7
    UINT32 tWRRD_dg                                :  6;  // Bits 13:8
    UINT32                                         :  2;  // Bits 15:14
    UINT32 tWRRD_dr                                :  6;  // Bits 21:16
    UINT32                                         :  2;  // Bits 23:22
    UINT32 tWRRD_dd                                :  6;  // Bits 29:24
    UINT32                                         :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCHBAR_CH0_CR_TC_WRRD_STRUCT;

typedef union {
  struct {
    UINT32 tWRWR_sg                                :  6;  // Bits 5:0
    UINT32                                         :  2;  // Bits 7:6
    UINT32 tWRWR_dg                                :  6;  // Bits 13:8
    UINT32                                         :  2;  // Bits 15:14
    UINT32 tWRWR_dr                                :  6;  // Bits 21:16
    UINT32                                         :  2;  // Bits 23:22
    UINT32 tWRWR_dd                                :  6;  // Bits 29:24
    UINT32                                         :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCHBAR_CH0_CR_TC_WRWR_STRUCT;

typedef union {
  struct {
    UINT32 DRAM_technology                         :  2;  // Bits 1:0
    UINT32 CMD_stretch                             :  2;  // Bits 3:2
    UINT32 N_to_1_ratio                            :  3;  // Bits 6:4
    UINT32                                         :  1;  // Bits 7:7
    UINT32 Address_mirror                          :  2;  // Bits 9:8
    UINT32 x8_device                               :  2;  // Bits 11:10
    UINT32 tCPDED                                  :  3;  // Bits 14:12
    UINT32 LPDDR_2N_CS_MRW                         :  1;  // Bits 15:15
    UINT32 reset_on_command                        :  4;  // Bits 19:16
    UINT32 reset_delay                             :  3;  // Bits 22:20
    UINT32 cmd_3st                                 :  1;  // Bits 23:23
    UINT32 ck_to_cke                               :  3;  // Bits 26:24
    UINT32 enable_odt_matrix                       :  1;  // Bits 27:27
    UINT32 ddr_probeless_low_frequency             :  1;  // Bits 28:28
    UINT32 tCAL                                    :  3;  // Bits 31:29
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCHBAR_CH0_CR_SC_GS_CFG_STRUCT;

typedef union {
  struct {
    UINT32 Rank_0_latency                          :  7;  // Bits 6:0
    UINT32                                         :  1;  // Bits 7:7
    UINT32 Rank_1_latency                          :  7;  // Bits 14:8
    UINT32                                         :  1;  // Bits 15:15
    UINT32 Rank_2_latency                          :  7;  // Bits 22:16
    UINT32                                         :  1;  // Bits 23:23
    UINT32 Rank_3_latency                          :  7;  // Bits 30:24
    UINT32                                         :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCHBAR_CH0_CR_SC_ROUNDTRIP_LATENCY_STRUCT;

typedef union {
  struct {
    UINT32 Rank_0_flyby                            :  4;  // Bits 3:0
    UINT32 Rank_1_flyby                            :  4;  // Bits 7:4
    UINT32 Rank_2_flyby                            :  4;  // Bits 11:8
    UINT32 Rank_3_flyby                            :  4;  // Bits 15:12
    UINT32 IO_Latency_offset                       :  7;  // Bits 22:16
    UINT32                                         :  1;  // Bits 23:23
    UINT32 RFR_delay                               :  7;  // Bits 30:24
    UINT32                                         :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCHBAR_CH0_CR_SC_IO_LATENCY_STRUCT;

typedef union {
  struct {
    UINT32 dis_opp_cas                             :  1;  // Bits 0:0
    UINT32 dis_opp_is_cas                          :  1;  // Bits 1:1
    UINT32 dis_opp_ras                             :  1;  // Bits 2:2
    UINT32 dis_opp_is_ras                          :  1;  // Bits 3:3
    UINT32 dis_2c_byp                              :  1;  // Bits 4:4
    UINT32 dis_deprd_opt                           :  1;  // Bits 5:5
    UINT32 dis_pt_it                               :  1;  // Bits 6:6
    UINT32 dis_prcnt_ring                          :  1;  // Bits 7:7
    UINT32 dis_prcnt_sa                            :  1;  // Bits 8:8
    UINT32 dis_blkr_ph                             :  1;  // Bits 9:9
    UINT32 dis_blkr_pe                             :  1;  // Bits 10:10
    UINT32 dis_blkr_pm                             :  1;  // Bits 11:11
    UINT32 dis_odt                                 :  1;  // Bits 12:12
    UINT32 OE_alw_off                              :  1;  // Bits 13:13
    UINT32 block_rpq                               :  1;  // Bits 14:14
    UINT32 block_ipq                               :  1;  // Bits 15:15
    UINT32 block_wpq                               :  1;  // Bits 16:16
    UINT32 dis_zq                                  :  1;  // Bits 17:17
    UINT32 dis_tt                                  :  1;  // Bits 18:18
    UINT32 dis_opp_ref                             :  1;  // Bits 19:19
    UINT32 long_zq                                 :  1;  // Bits 20:20
    UINT32 dis_srx_zq                              :  1;  // Bits 21:21
    UINT32 serialize_zq                            :  1;  // Bits 22:22
    UINT32 zq_fast_exec                            :  1;  // Bits 23:23
    UINT32 dis_DriveNop                            :  1;  // Bits 24:24
    UINT32 dis_idle_preempt                        :  1;  // Bits 25:25
    UINT32 spare                                   :  4;  // Bits 29:26
    UINT32 dis_5cyc_read_gap                       :  1;  // Bits 30:30
    UINT32 dis_clk_gate                            :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCHBAR_CH0_CR_SCHED_CBIT_STRUCT;

typedef union {
  struct {
    UINT32 dis_srx_mr4                             :  1;  // Bits 0:0
    UINT32 dis_ck_tristate                         :  1;  // Bits 1:1
    UINT32 dis_burst_ref_limit                     :  1;  // Bits 2:2
    UINT32 dis_bus_retain                          :  1;  // Bits 3:3
    UINT32 dis_async_odt                           :  1;  // Bits 4:4
    UINT32 dis_SRX_reset                           :  1;  // Bits 5:5
    UINT32 dis_tcwl5_2qclk_add                     :  1;  // Bits 6:6
    UINT32 dis_SRX_MRS_MR4                         :  1;  // Bits 7:7
    UINT32 dis_opp_ref_idle_delay                  :  1;  // Bits 8:8
    UINT32 dis_ignore_1st_trefi                    :  1;  // Bits 9:9
    UINT32 echo_mask                               :  6;  // Bits 15:10
    UINT32 spare                                   :  16;  // Bits 31:16
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCHBAR_CH0_CR_SCHED_SECOND_CBIT_STRUCT;

typedef union {
  struct {
    UINT32 WDAR                                    :  1;  // Bits 0:0
    UINT32 WDB_Block_En                            :  1;  // Bits 1:1
    UINT32                                         :  2;  // Bits 3:2
    UINT32 force_rcv_en                            :  1;  // Bits 4:4
    UINT32                                         :  3;  // Bits 7:5
    UINT32 DDR_QUAL                                :  2;  // Bits 9:8
    UINT32 QUAL_Delay                              :  5;  // Bits 14:10
    UINT32 QUAL_Length                             :  2;  // Bits 16:15
    UINT32 dft_block_enable                        :  1;  // Bits 17:17
    UINT32                                         :  6;  // Bits 23:18
    UINT32 Stretch_mode                            :  2;  // Bits 25:24
    UINT32 STF                                     :  3;  // Bits 28:26
    UINT32                                         :  3;  // Bits 31:29
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCHBAR_CH0_CR_DFT_MISC_STRUCT;

typedef union {
  struct {
    UINT32 ECC_Inject                              :  3;  // Bits 2:0
    UINT32                                         :  1;  // Bits 3:3
    UINT32 ECC_correction_disable                  :  1;  // Bits 4:4
    UINT32                                         :  3;  // Bits 7:5
    UINT32 DIS_MCA_LOG                             :  1;  // Bits 8:8
    UINT32 DIS_PCH_EVENT                           :  1;  // Bits 9:9
    UINT32 DIS_RCH_POISON                          :  1;  // Bits 10:10
    UINT32 DIS_RCH_ERROR                           :  1;  // Bits 11:11
    UINT32                                         :  4;  // Bits 15:12
    UINT32 ECC_trigger                             :  2;  // Bits 17:16
    UINT32                                         :  14;  // Bits 31:18
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCHBAR_CH0_CR_ECC_DFT_STRUCT;

typedef union {
  struct {
    UINT32 Ring                                    :  10;  // Bits 9:0
    UINT32                                         :  6;  // Bits 15:10
    UINT32 SA                                      :  10;  // Bits 25:16
    UINT32                                         :  6;  // Bits 31:26
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCHBAR_CH0_CR_SC_PR_CNT_CONFIG_STRUCT;

typedef union {
  struct {
    UINT32 PCIT                                    :  8;  // Bits 7:0
    UINT32                                         :  8;  // Bits 15:8
    UINT32 PCIT_GT                                 :  8;  // Bits 23:16
    UINT32                                         :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCHBAR_CH0_CR_SC_PCIT_STRUCT;

typedef union {
  struct {
    UINT32 PDWN_idle_counter                       :  12;  // Bits 11:0
    UINT32 APD                                     :  1;  // Bits 12:12
    UINT32 PPD                                     :  1;  // Bits 13:13
    UINT32 Slow_Exit                               :  1;  // Bits 14:14
    UINT32 Global_PD                               :  1;  // Bits 15:15
    UINT32 TT_idle_counter                         :  8;  // Bits 23:16
    UINT32 dis_cke_tt                              :  1;  // Bits 24:24
    UINT32                                         :  7;  // Bits 31:25
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCHBAR_CH0_CR_PM_PDWN_CONFIG_STRUCT;

typedef union {
  struct {
    UINT32 Dis_Opp_rd                              :  1;  // Bits 0:0
    UINT32 ACT_Enable                              :  1;  // Bits 1:1
    UINT32 PRE_Enable                              :  1;  // Bits 2:2
    UINT32 MAX_RPQ_CAS                             :  4;  // Bits 6:3
    UINT32                                         :  25;  // Bits 31:7
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCHBAR_CH0_CR_WMM_READ_CONFIG_STRUCT;

typedef union {
  struct {
    UINT32 CERRSTS                                 :  1;  // Bits 0:0
    UINT32 MERRSTS                                 :  1;  // Bits 1:1
    UINT32                                         :  14;  // Bits 15:2
    UINT32 ERRSYND                                 :  8;  // Bits 23:16
    UINT32 ERRCHUNK                                :  3;  // Bits 26:24
    UINT32 ERRRANK                                 :  2;  // Bits 28:27
    UINT32 ERRBANK                                 :  3;  // Bits 31:29
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCHBAR_CH0_CR_ECCERRLOG0_STRUCT;

typedef union {
  struct {
    UINT32 ERRROW                                  :  17;  // Bits 16:0
    UINT32 ERRCOL                                  :  11;  // Bits 27:17
    UINT32 ERRBANKGROUP                            :  2;  // Bits 29:28
    UINT32                                         :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCHBAR_CH0_CR_ECCERRLOG1_STRUCT;

typedef union {
  struct {
    UINT32 EN_CLK                                  :  1;  // Bits 0:0
    UINT32 L0_DATA_BYTE_SEL                        :  7;  // Bits 7:1
    UINT32 L0_BYP_SEL                              :  1;  // Bits 8:8
    UINT32 L1_DATA_BYTE_SEL                        :  7;  // Bits 15:9
    UINT32 L1_BYP_SEL                              :  1;  // Bits 16:16
    UINT32                                         :  10;  // Bits 26:17
    UINT32 PATGENMODE                              :  3;  // Bits 29:27
    UINT32                                         :  1;  // Bits 30:30
    UINT32 VORANGE                                 :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCHBAR_CH0_CR_VISA_CTL_MCSCHEDS_STRUCT;

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
} MCHBAR_CH0_CR_VISA_XBAR_MCSCHEDS_STRUCT;

typedef union {
  struct {
    UINT32 RPQ_disable                             :  22;  // Bits 21:0
    UINT32                                         :  10;  // Bits 31:22
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCHBAR_CH0_CR_QUEUE_ENTRY_DISABLE_RPQ_STRUCT;

typedef union {
  struct {
    UINT32 IPQ_disable                             :  10;  // Bits 9:0
    UINT32                                         :  22;  // Bits 31:10
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCHBAR_CH0_CR_QUEUE_ENTRY_DISABLE_IPQ_STRUCT;

typedef union {
  struct {
    UINT32 WPQ_disableLow                          :  32;  // Bits 31:0
    UINT32 WPQ_disableHigh                         :  32;  // Bits 63:32
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} MCHBAR_CH0_CR_QUEUE_ENTRY_DISABLE_WPQ_STRUCT;

typedef union {
  struct {
    UINT32 WMM_entry_wm                            :  7;  // Bits 6:0
    UINT32                                         :  1;  // Bits 7:7
    UINT32 WMM_exit_wm                             :  7;  // Bits 14:8
    UINT32                                         :  1;  // Bits 15:15
    UINT32 WIM_wm                                  :  7;  // Bits 22:16
    UINT32                                         :  1;  // Bits 23:23
    UINT32 EDRAM_scrub_wm                          :  7;  // Bits 30:24
    UINT32                                         :  1;  // Bits 31:31
    UINT32 Read_CAS_count                          :  8;  // Bits 39:32
    UINT32 Write_CAS_count                         :  8;  // Bits 47:40
    UINT32 Write_CAS_count_for_VC1                 :  8;  // Bits 55:48
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} MCHBAR_CH0_CR_SC_WDBWM_STRUCT;

typedef union {
  struct {
    UINT32 ODT_read_duration                       :  3;  // Bits 2:0
    UINT32                                         :  1;  // Bits 3:3
    UINT32 ODT_Read_Delay                          :  3;  // Bits 6:4
    UINT32                                         :  1;  // Bits 7:7
    UINT32 ODT_write_duration                      :  3;  // Bits 10:8
    UINT32                                         :  1;  // Bits 11:11
    UINT32 ODT_Write_Delay                         :  3;  // Bits 14:12
    UINT32 Write_Early_ODT                         :  1;  // Bits 15:15
    UINT32 tCL                                     :  5;  // Bits 20:16
    UINT32 tCWL                                    :  5;  // Bits 25:21
    UINT32 tAONPD                                  :  5;  // Bits 30:26
    UINT32 ODT_Always_Rank0                        :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCHBAR_CH0_CR_TC_ODT_STRUCT;

typedef union {
  struct {
    UINT32 Spare_RW                                :  6;  // Bits 5:0
    UINT32 cmd_delay_counter                       :  4;  // Bits 9:6
    UINT32 cmd_delay_disable                       :  1;  // Bits 10:10
    UINT32 cke_delay_counter                       :  4;  // Bits 14:11
    UINT32 cke_delay_disable                       :  1;  // Bits 15:15
    UINT32 Spare_RW_V                              :  16;  // Bits 31:16
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCHBAR_CH0_CR_MCSCHEDS_SPARE_STRUCT;

typedef union {
  struct {
    UINT32 shift_16                                :  1;  // Bits 0:0
    UINT32 clken_pulse_mode                        :  1;  // Bits 1:1
    UINT32 reg_clken_mode                          :  1;  // Bits 2:2
    UINT32 reg_clken                               :  1;  // Bits 3:3
    UINT32 feedback_en                             :  1;  // Bits 4:4
    UINT32 event_mode                              :  1;  // Bits 5:5
    UINT32 lfsr_reset                              :  1;  // Bits 6:6
    UINT32 sdo_en                                  :  1;  // Bits 7:7
    UINT32                                         :  8;  // Bits 15:8
    UINT32 cr_rd_data                              :  16;  // Bits 31:16
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCHBAR_CH0_CR_MC_MISR_STRUCT;

typedef union {
  struct {
    UINT32 Read_Rank_0                             :  4;  // Bits 3:0
    UINT32 Read_Rank_1                             :  4;  // Bits 7:4
    UINT32 Read_Rank_2                             :  4;  // Bits 11:8
    UINT32 Read_Rank_3                             :  4;  // Bits 15:12
    UINT32 Write_Rank_0                            :  4;  // Bits 19:16
    UINT32 Write_Rank_1                            :  4;  // Bits 23:20
    UINT32 Write_Rank_2                            :  4;  // Bits 27:24
    UINT32 Write_Rank_3                            :  4;  // Bits 31:28
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCHBAR_CH0_CR_SC_ODT_MATRIX_STRUCT;

typedef union {
  struct {
    UINT32 dft_block_cycles                        :  16;  // Bits 15:0
    UINT32 dft_nonblock_cycles                     :  16;  // Bits 31:16
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCHBAR_CH0_CR_DFT_BLOCK_STRUCT;

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
} MCHBAR_CH0_CR_VISA_SLIDE_MCSCHEDS_STRUCT;

typedef union {
  struct {
    UINT32 Mux0_Control                            :  2;  // Bits 1:0
    UINT32                                         :  1;  // Bits 2:2
    UINT32 Mux1_Control                            :  2;  // Bits 4:3
    UINT32                                         :  1;  // Bits 5:5
    UINT32 Mux2_Control                            :  2;  // Bits 7:6
    UINT32 LFSR_Type                               :  3;  // Bits 10:8
    UINT32 Chaining_LFSR                           :  1;  // Bits 11:11
    UINT32                                         :  2;  // Bits 13:12
    UINT32 ECC_Replace_Byte_Control                :  1;  // Bits 14:14
    UINT32 ECC_Data_Source_Sel                     :  1;  // Bits 15:15
    UINT32 Save_LFSR_Seed_Rate                     :  8;  // Bits 23:16
    UINT32 Reload_LFSR_Seed_Rate                   :  5;  // Bits 28:24
    UINT32                                         :  2;  // Bits 30:29
    UINT32 Reload_Save_LFSR_Seed_Rate_Mode         :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCHBAR_CH0_CR_REUT_CH_PAT_WDB_CL_MUX_CFG_STRUCT;

typedef union {
  struct {
    UINT32 Pattern_Buffer                          :  24;  // Bits 23:0
    UINT32                                         :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCHBAR_CH0_CR_REUT_CH_PAT_WDB_CL_MUX_PB_WR_0_STRUCT;

typedef union {
  struct {
    UINT32 Pattern_Buffer                          :  24;  // Bits 23:0
    UINT32                                         :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCHBAR_CH0_CR_REUT_CH_PAT_WDB_CL_MUX_PB_WR_1_STRUCT;

typedef union {
  struct {
    UINT32 Pattern_Buffer                          :  24;  // Bits 23:0
    UINT32                                         :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCHBAR_CH0_CR_REUT_CH_PAT_WDB_CL_MUX_PB_WR_2_STRUCT;

typedef union {
  struct {
    UINT32 Pattern_Buffer                          :  24;  // Bits 23:0
    UINT32                                         :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCHBAR_CH0_CR_REUT_CH_PAT_WDB_CL_MUX_PB_RD_0_STRUCT;

typedef union {
  struct {
    UINT32 Pattern_Buffer                          :  24;  // Bits 23:0
    UINT32                                         :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCHBAR_CH0_CR_REUT_CH_PAT_WDB_CL_MUX_PB_RD_1_STRUCT;

typedef union {
  struct {
    UINT32 Pattern_Buffer                          :  24;  // Bits 23:0
    UINT32                                         :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCHBAR_CH0_CR_REUT_CH_PAT_WDB_CL_MUX_PB_RD_2_STRUCT;

typedef union {
  struct {
    UINT32 Pattern_Buffer                          :  24;  // Bits 23:0
    UINT32                                         :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCHBAR_CH0_CR_REUT_CH_PAT_WDB_CL_MUX_PB_STATUS_WR_0_STRUCT;

typedef union {
  struct {
    UINT32 Pattern_Buffer                          :  24;  // Bits 23:0
    UINT32                                         :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCHBAR_CH0_CR_REUT_CH_PAT_WDB_CL_MUX_PB_STATUS_WR_1_STRUCT;

typedef union {
  struct {
    UINT32 Pattern_Buffer                          :  24;  // Bits 23:0
    UINT32                                         :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCHBAR_CH0_CR_REUT_CH_PAT_WDB_CL_MUX_PB_STATUS_WR_2_STRUCT;

typedef union {
  struct {
    UINT32 Pattern_Buffer                          :  24;  // Bits 23:0
    UINT32                                         :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCHBAR_CH0_CR_REUT_CH_PAT_WDB_CL_MUX_PB_STATUS_RD_0_STRUCT;

typedef union {
  struct {
    UINT32 Pattern_Buffer                          :  24;  // Bits 23:0
    UINT32                                         :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCHBAR_CH0_CR_REUT_CH_PAT_WDB_CL_MUX_PB_STATUS_RD_1_STRUCT;

typedef union {
  struct {
    UINT32 Pattern_Buffer                          :  24;  // Bits 23:0
    UINT32                                         :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCHBAR_CH0_CR_REUT_CH_PAT_WDB_CL_MUX_PB_STATUS_RD_2_STRUCT;

typedef union {
  struct {
    UINT32 L_data_select                           :  1;  // Bits 0:0
    UINT32 Enable_Sweep_Frequency                  :  1;  // Bits 1:1
    UINT32                                         :  6;  // Bits 7:2
    UINT32 L_counter                               :  8;  // Bits 15:8
    UINT32 M_counter                               :  8;  // Bits 23:16
    UINT32 N_counter                               :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCHBAR_CH0_CR_REUT_CH_PAT_WDB_CL_MUX_LMN_STRUCT;

typedef union {
  struct {
    UINT32 Write_Address_as_Data                   :  1;  // Bits 0:0
    UINT32 Read_Address_as_Data                    :  1;  // Bits 1:1
    UINT32                                         :  30;  // Bits 31:2
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCHBAR_CH0_CR_REUT_CH_PAT_WDB_ADDRESS_AS_DATA_CTRL_STRUCT;

typedef union {
  struct {
    UINT32 ECC_Inv_or_DC_Enable                    :  8;  // Bits 7:0
    UINT32                                         :  8;  // Bits 15:8
    UINT32 Inv_or_DC_Shift_Rate                    :  4;  // Bits 19:16
    UINT32 DC_Polarity_Control                     :  1;  // Bits 20:20
    UINT32                                         :  9;  // Bits 29:21
    UINT32 Inv_or_DC_Control                       :  1;  // Bits 30:30
    UINT32 Inv_or_DC_Shift_Enable                  :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCHBAR_CH0_CR_REUT_CH_PAT_WDB_INV_STRUCT;

typedef union {
  struct {
    UINT32 Data_Inv_or_DC_EnableLow                :  32;  // Bits 31:0
    UINT32 Data_Inv_or_DC_EnableHigh               :  32;  // Bits 63:32
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} MCHBAR_CH0_CR_REUT_CH_PAT_WDB_DATA_INV_STRUCT;

typedef union {
  struct {
    UINT32 CKE_Override                            :  4;  // Bits 3:0
    UINT32                                         :  4;  // Bits 7:4
    UINT32 CKE_En_Start_Test_Sync                  :  1;  // Bits 8:8
    UINT32                                         :  7;  // Bits 15:9
    UINT32 CKE_On                                  :  4;  // Bits 19:16
    UINT32                                         :  12;  // Bits 31:20
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCHBAR_CH0_CR_REUT_CH_MISC_CKE_CTRL_STRUCT;

typedef union {
  struct {
    UINT32 ODT_Override                            :  4;  // Bits 3:0
    UINT32                                         :  12;  // Bits 15:4
    UINT32 ODT_On                                  :  4;  // Bits 19:16
    UINT32                                         :  11;  // Bits 30:20
    UINT32 MPR_Train_DDR_On                        :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCHBAR_CH0_CR_REUT_CH_MISC_ODT_CTRL_STRUCT;

typedef union {
  struct {
    UINT32 Enable_CADB_on_Deselect                 :  1;  // Bits 0:0
    UINT32 Enable_CADB_Always_On                   :  1;  // Bits 1:1
    UINT32 CMD_Deselect_Start                      :  4;  // Bits 5:2
    UINT32 CMD_Deselect_Stop                       :  4;  // Bits 9:6
    UINT32 Lane_Deselect_Enable                    :  4;  // Bits 13:10
    UINT32 CAS_Select_Enable                       :  2;  // Bits 15:14
    UINT32 ACT_Select_Enable                       :  2;  // Bits 17:16
    UINT32 PRE_Select_Enable                       :  2;  // Bits 19:18
    UINT32 Save_Current_Seed                       :  4;  // Bits 23:20
    UINT32 Reload_Starting_Seed                    :  4;  // Bits 27:24
    UINT32                                         :  4;  // Bits 31:28
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCHBAR_CH0_CR_REUT_CH_PAT_CADB_CTRL_STRUCT;

typedef union {
  struct {
    UINT32 MRS_Gap                                 :  3;  // Bits 2:0
    UINT32                                         :  4;  // Bits 6:3
    UINT32 MRS_Gap_Scale                           :  1;  // Bits 7:7
    UINT32 CADB_MRS_Start_Pointer                  :  3;  // Bits 10:8
    UINT32                                         :  5;  // Bits 15:11
    UINT32 CADB_MRS_End_Pointer                    :  3;  // Bits 18:16
    UINT32                                         :  5;  // Bits 23:19
    UINT32 CADB_MRS_Current_Pointer                :  3;  // Bits 26:24
    UINT32                                         :  1;  // Bits 27:27
    UINT32 MRS_Wait_Scale                          :  1;  // Bits 28:28
    UINT32 MRS_Wait                                :  3;  // Bits 31:29
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCHBAR_CH0_CR_REUT_CH_PAT_CADB_MRS_STRUCT;

typedef union {
  struct {
    UINT32 Mux0_Control                            :  2;  // Bits 1:0
    UINT32                                         :  2;  // Bits 3:2
    UINT32 Mux1_Control                            :  2;  // Bits 5:4
    UINT32                                         :  2;  // Bits 7:6
    UINT32 Mux2_Control                            :  2;  // Bits 9:8
    UINT32                                         :  6;  // Bits 15:10
    UINT32 Select_Mux0_Control                     :  2;  // Bits 17:16
    UINT32                                         :  2;  // Bits 19:18
    UINT32 Select_Mux1_Control                     :  2;  // Bits 21:20
    UINT32                                         :  2;  // Bits 23:22
    UINT32 Select_Mux2_Control                     :  2;  // Bits 25:24
    UINT32                                         :  2;  // Bits 27:26
    UINT32 LFSR_Type                               :  3;  // Bits 30:28
    UINT32 Chaining_LFSR                           :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCHBAR_CH0_CR_REUT_CH_PAT_CADB_MUX_CTRL_STRUCT;

typedef union {
  struct {
    UINT32 Pattern_Buffer                          :  24;  // Bits 23:0
    UINT32                                         :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCHBAR_CH0_CR_REUT_CH_PAT_CADB_MUX_PB_0_STRUCT;

typedef union {
  struct {
    UINT32 Pattern_Buffer                          :  24;  // Bits 23:0
    UINT32                                         :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCHBAR_CH0_CR_REUT_CH_PAT_CADB_MUX_PB_1_STRUCT;

typedef union {
  struct {
    UINT32 Pattern_Buffer                          :  24;  // Bits 23:0
    UINT32                                         :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCHBAR_CH0_CR_REUT_CH_PAT_CADB_MUX_PB_2_STRUCT;

typedef union {
  struct {
    UINT32 Pattern_Buffer                          :  24;  // Bits 23:0
    UINT32                                         :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCHBAR_CH0_CR_REUT_CH_PAT_CADB_SEL_MUX_PB_0_STRUCT;

typedef union {
  struct {
    UINT32 Pattern_Buffer                          :  24;  // Bits 23:0
    UINT32                                         :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCHBAR_CH0_CR_REUT_CH_PAT_CADB_SEL_MUX_PB_1_STRUCT;

typedef union {
  struct {
    UINT32 Pattern_Buffer                          :  24;  // Bits 23:0
    UINT32                                         :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCHBAR_CH0_CR_REUT_CH_PAT_CADB_SEL_MUX_PB_2_STRUCT;

typedef union {
  struct {
    UINT32 L_data_select                           :  1;  // Bits 0:0
    UINT32 Enable_Sweep_Frequency                  :  1;  // Bits 1:1
    UINT32                                         :  6;  // Bits 7:2
    UINT32 L_counter                               :  8;  // Bits 15:8
    UINT32 M_counter                               :  8;  // Bits 23:16
    UINT32 N_counter                               :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCHBAR_CH0_CR_REUT_CH_PAT_CADB_CL_MUX_LMN_STRUCT;

typedef union {
  struct {
    UINT32 CADB_Write_Pointer                      :  3;  // Bits 2:0
    UINT32                                         :  1;  // Bits 3:3
    UINT32 Write_Enable                            :  1;  // Bits 4:4
    UINT32                                         :  27;  // Bits 31:5
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCHBAR_CH0_CR_REUT_CH_PAT_CADB_WRITE_POINTER_STRUCT;

typedef union {
  struct {
    UINT32 CADB_Data_Address                       :  17;  // Bits 16:0
    UINT32                                         :  7;  // Bits 23:17
    UINT32 CADB_Data_Bank                          :  4;  // Bits 27:24
    UINT32                                         :  4;  // Bits 31:28
    UINT32 CADB_Data_CS                            :  4;  // Bits 35:32
    UINT32                                         :  4;  // Bits 39:36
    UINT32 CADB_Data_Control                       :  4;  // Bits 43:40
    UINT32                                         :  4;  // Bits 47:44
    UINT32 CADB_Data_ODT                           :  4;  // Bits 51:48
    UINT32                                         :  4;  // Bits 55:52
    UINT32 CADB_Data_CKE                           :  4;  // Bits 59:56
    UINT32                                         :  3;  // Bits 62:60
    UINT32 CADB_Data_Parity_inv                    :  1;  // Bits 63:63
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} MCHBAR_CH0_CR_REUT_CH_PAT_CADB_PROG_STRUCT;

typedef union {
  struct {
    UINT32 Loopcount_Limit                         :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCHBAR_CH0_CR_REUT_CH_PAT_CADB_MRS_LOOPCOUNT_LIMIT_STRUCT;

typedef union {
  struct {
    UINT32 WDB_Increment_Rate                      :  6;  // Bits 5:0
    UINT32 WDB_Increment_Scale                     :  1;  // Bits 6:6
    UINT32                                         :  1;  // Bits 7:7
    UINT32 WDB_Start_Pointer                       :  6;  // Bits 13:8
    UINT32                                         :  2;  // Bits 15:14
    UINT32 WDB_End_Pointer                         :  6;  // Bits 21:16
    UINT32                                         :  10;  // Bits 31:22
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCHBAR_CH0_CR_REUT_CH_PAT_WDB_CL_CTRL_STRUCT;

typedef union {
  struct {
    UINT32 Refresh_Rank_Mask                       :  4;  // Bits 3:0
    UINT32                                         :  4;  // Bits 7:4
    UINT32 RefZQ_En_Start_Test_Sync                :  1;  // Bits 8:8
    UINT32                                         :  22;  // Bits 30:9
    UINT32 Panic_Refresh_Only                      :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCHBAR_CH0_CR_REUT_CH_MISC_REFRESH_CTRL_STRUCT;

typedef union {
  struct {
    UINT32 ZQ_Rank_Mask                            :  4;  // Bits 3:0
    UINT32                                         :  27;  // Bits 30:4
    UINT32 Always_Do_ZQ                            :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCHBAR_CH0_CR_REUT_CH_MISC_ZQ_CTRL_STRUCT;

typedef union {
  struct {
    UINT32 Rank_0_width                            :  2;  // Bits 1:0
    UINT32 Rank_1_width                            :  2;  // Bits 3:2
    UINT32 Rank_2_width                            :  2;  // Bits 5:4
    UINT32 Rank_3_width                            :  2;  // Bits 7:6
    UINT32 MR4_PERIOD                              :  16;  // Bits 23:8
    UINT32 DDR4_TS_readout_en                      :  1;  // Bits 24:24
    UINT32                                         :  7;  // Bits 31:25
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCHBAR_CH0_CR_DDR_MR_PARAMS_STRUCT;

typedef union {
  struct {
    UINT32 Address                                 :  8;  // Bits 7:0
    UINT32 Data                                    :  8;  // Bits 15:8
    UINT32 Rank                                    :  2;  // Bits 17:16
    UINT32 Command                                 :  2;  // Bits 19:18
    UINT32 DRAM_mask                               :  9;  // Bits 28:20
    UINT32 Assume_idle                             :  1;  // Bits 29:29
    UINT32 DDR4_MA13                               :  1;  // Bits 30:30
    UINT32 Busy                                    :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCHBAR_CH0_CR_DDR_MR_COMMAND_STRUCT;

typedef union {
  struct {
    UINT32 Device_0                                :  8;  // Bits 7:0
    UINT32 Device_1                                :  8;  // Bits 15:8
    UINT32 Device_2                                :  8;  // Bits 23:16
    UINT32 Device_3                                :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCHBAR_CH0_CR_DDR_MR_RESULT_0_STRUCT;

typedef union {
  struct {
    UINT32 Device_4                                :  8;  // Bits 7:0
    UINT32 Device_5                                :  8;  // Bits 15:8
    UINT32 Device_6                                :  8;  // Bits 23:16
    UINT32 Device_7                                :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCHBAR_CH0_CR_DDR_MR_RESULT_1_STRUCT;

typedef union {
  struct {
    UINT32 Device_8                                :  8;  // Bits 7:0
    UINT32                                         :  24;  // Bits 31:8
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCHBAR_CH0_CR_DDR_MR_RESULT_2_STRUCT;

typedef union {
  struct {
    UINT32 Rank_0                                  :  3;  // Bits 2:0
    UINT32                                         :  5;  // Bits 7:3
    UINT32 Rank_1                                  :  3;  // Bits 10:8
    UINT32                                         :  5;  // Bits 15:11
    UINT32 Rank_2                                  :  3;  // Bits 18:16
    UINT32                                         :  5;  // Bits 23:19
    UINT32 Rank_3                                  :  3;  // Bits 26:24
    UINT32                                         :  5;  // Bits 31:27
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCHBAR_CH0_CR_LPDDR_MR4_RANK_TEMPERATURE_STRUCT;

typedef union {
  struct {
    UINT32 Rank_0                                  :  2;  // Bits 1:0
    UINT32                                         :  6;  // Bits 7:2
    UINT32 Rank_1                                  :  2;  // Bits 9:8
    UINT32                                         :  6;  // Bits 15:10
    UINT32 Rank_2                                  :  2;  // Bits 17:16
    UINT32                                         :  6;  // Bits 23:18
    UINT32 Rank_3                                  :  2;  // Bits 25:24
    UINT32                                         :  6;  // Bits 31:26
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCHBAR_CH0_CR_DDR4_MPR_RANK_TEMPERATURE_STRUCT;

typedef union {
  struct {
    UINT32 Bit_0                                   :  3;  // Bits 2:0
    UINT32                                         :  1;  // Bits 3:3
    UINT32 Bit_1                                   :  3;  // Bits 6:4
    UINT32                                         :  1;  // Bits 7:7
    UINT32 Bit_2                                   :  3;  // Bits 10:8
    UINT32                                         :  1;  // Bits 11:11
    UINT32 Bit_16                                  :  3;  // Bits 14:12
    UINT32                                         :  1;  // Bits 15:15
    UINT32 Bit_17                                  :  3;  // Bits 18:16
    UINT32                                         :  1;  // Bits 19:19
    UINT32 Bit_18                                  :  3;  // Bits 22:20
    UINT32                                         :  1;  // Bits 23:23
    UINT32 Byte_0                                  :  3;  // Bits 26:24
    UINT32                                         :  1;  // Bits 27:27
    UINT32 Byte_2                                  :  3;  // Bits 30:28
    UINT32                                         :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCHBAR_CH0_CR_DESWIZZLE_LOW_STRUCT;

typedef union {
  struct {
    UINT32 Bit_32                                  :  3;  // Bits 2:0
    UINT32                                         :  1;  // Bits 3:3
    UINT32 Bit_33                                  :  3;  // Bits 6:4
    UINT32                                         :  1;  // Bits 7:7
    UINT32 Bit_34                                  :  3;  // Bits 10:8
    UINT32                                         :  1;  // Bits 11:11
    UINT32 Bit_48                                  :  3;  // Bits 14:12
    UINT32                                         :  1;  // Bits 15:15
    UINT32 Bit_49                                  :  3;  // Bits 18:16
    UINT32                                         :  1;  // Bits 19:19
    UINT32 Bit_50                                  :  3;  // Bits 22:20
    UINT32                                         :  1;  // Bits 23:23
    UINT32 Byte_4                                  :  3;  // Bits 26:24
    UINT32                                         :  1;  // Bits 27:27
    UINT32 Byte_6                                  :  3;  // Bits 30:28
    UINT32                                         :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCHBAR_CH0_CR_DESWIZZLE_HIGH_STRUCT;

typedef union {
  struct {
    UINT32 OREF_RI                                 :  8;  // Bits 7:0
    UINT32 Refresh_HP_WM                           :  4;  // Bits 11:8
    UINT32 Refresh_panic_wm                        :  4;  // Bits 15:12
    UINT32                                         :  9;  // Bits 24:16
    UINT32 tREFIx9                                 :  7;  // Bits 31:25
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCHBAR_CH0_CR_TC_RFP_STRUCT;

typedef union {
  struct {
    UINT32 tREFI                                   :  16;  // Bits 15:0
    UINT32 tRFC                                    :  10;  // Bits 25:16
    UINT32                                         :  6;  // Bits 31:26
  } Bits;
  struct {
    UINT32 tREFI                                   :  16;  // Bits 15:0
    UINT32 tRFC                                    :  9;  // Bits 24:16
    UINT32 tREFIx9                                 :  7;  // Bits 31:25
  } BitsA0;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCHBAR_CH0_CR_TC_RFTP_STRUCT;

typedef union {
  struct {
    UINT32 tXSDLL                                  :  12;  // Bits 11:0
    UINT32 tXS_offset                              :  4;  // Bits 15:12
    UINT32 tZQOPER                                 :  10;  // Bits 25:16
    UINT32 tMOD                                    :  5;  // Bits 30:26
    UINT32                                         :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCHBAR_CH0_CR_TC_SRFTP_STRUCT;

typedef union {
  struct {
    UINT32 Ref_Interval                            :  11;  // Bits 10:0
    UINT32 Ref_Stagger_En                          :  1;  // Bits 11:11
    UINT32 Ref_Stagger_Mode                        :  1;  // Bits 12:12
    UINT32 Disable_Stolen_Refresh                  :  1;  // Bits 13:13
    UINT32 En_Ref_Type_Display                     :  1;  // Bits 14:14
    UINT32                                         :  17;  // Bits 31:15
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCHBAR_CH0_CR_MC_REFRESH_STAGGER_STRUCT;

typedef union {
  struct {
    UINT32 ZQCS_period                             :  10;  // Bits 9:0
    UINT32 tZQCS                                   :  10;  // Bits 19:10
    UINT32                                         :  12;  // Bits 31:20
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCHBAR_CH0_CR_TC_ZQCAL_STRUCT;

typedef union {
  struct {
    UINT32 MR2_shaddow                             :  14;  // Bits 13:0
    UINT32 SRT_avail                               :  2;  // Bits 15:14
    UINT32                                         :  16;  // Bits 31:16
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCHBAR_CH0_CR_TC_MR2_SHADDOW_STRUCT;

typedef union {
  struct {
    UINT32 MR4_sh_low                              :  2;  // Bits 1:0
    UINT32                                         :  2;  // Bits 3:2
    UINT32 MR4_sh_high                             :  10;  // Bits 13:4
    UINT32                                         :  18;  // Bits 31:14
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCHBAR_CH0_CR_TC_MR4_SHADDOW_STRUCT;

typedef union {
  struct {
    UINT32 Rank_occupancy                          :  4;  // Bits 3:0
    UINT32 SRX_reset                               :  1;  // Bits 4:4
    UINT32                                         :  27;  // Bits 31:5
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCHBAR_CH0_CR_MC_INIT_STATE_STRUCT;

typedef union {
  struct {
    UINT32 VISAByteSel                             :  3;  // Bits 2:0
    UINT32                                         :  29;  // Bits 31:3
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCHBAR_CH0_CR_WDB_VISA_SEL_STRUCT;

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
} MCHBAR_CH0_CR_VISA_CTL_MCMNTS_STRUCT;

typedef union {
  struct {
    UINT32 DIMM0_IDLE_ENERGY                       :  6;  // Bits 5:0
    UINT32                                         :  2;  // Bits 7:6
    UINT32 DIMM1_IDLE_ENERGY                       :  6;  // Bits 13:8
    UINT32                                         :  18;  // Bits 31:14
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCHBAR_CH0_CR_PM_DIMM_IDLE_ENERGY_STRUCT;

typedef union {
  struct {
    UINT32 DIMM0_PD_ENERGY                         :  6;  // Bits 5:0
    UINT32                                         :  2;  // Bits 7:6
    UINT32 DIMM1_PD_ENERGY                         :  6;  // Bits 13:8
    UINT32                                         :  18;  // Bits 31:14
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCHBAR_CH0_CR_PM_DIMM_PD_ENERGY_STRUCT;

typedef union {
  struct {
    UINT32 DIMM0_ACT_ENERGY                        :  8;  // Bits 7:0
    UINT32 DIMM1_ACT_ENERGY                        :  8;  // Bits 15:8
    UINT32                                         :  16;  // Bits 31:16
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCHBAR_CH0_CR_PM_DIMM_ACT_ENERGY_STRUCT;

typedef union {
  struct {
    UINT32 DIMM0_RD_ENERGY                         :  8;  // Bits 7:0
    UINT32 DIMM1_RD_ENERGY                         :  8;  // Bits 15:8
    UINT32                                         :  16;  // Bits 31:16
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCHBAR_CH0_CR_PM_DIMM_RD_ENERGY_STRUCT;

typedef union {
  struct {
    UINT32 DIMM0_WR_ENERGY                         :  8;  // Bits 7:0
    UINT32 DIMM1_WR_ENERGY                         :  8;  // Bits 15:8
    UINT32                                         :  16;  // Bits 31:16
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCHBAR_CH0_CR_PM_DIMM_WR_ENERGY_STRUCT;

typedef union {
  struct {
    UINT32 Count                                   :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCHBAR_CH0_CR_ECC_INJECT_COUNT_STRUCT;

typedef union {
  struct {
    UINT32 D0R0                                    :  2;  // Bits 1:0
    UINT32 D0R1                                    :  2;  // Bits 3:2
    UINT32 D1R0                                    :  2;  // Bits 5:4
    UINT32 D1R1                                    :  2;  // Bits 7:6
    UINT32                                         :  23;  // Bits 30:8
    UINT32 Dec_WRD                                 :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCHBAR_CH0_CR_SC_WR_ADD_DELAY_STRUCT;

typedef union {
  struct {
    UINT32 ECC                                     :  8;  // Bits 7:0
    UINT32 RRD_DFT_Mode                            :  2;  // Bits 9:8
    UINT32 LFSR_Seed_Index                         :  5;  // Bits 14:10
    UINT32 Inversion_Mode                          :  1;  // Bits 15:15
    UINT32                                         :  16;  // Bits 31:16
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCHBAR_CH0_CR_READ_RETURN_DFT_STRUCT;

typedef union {
  struct {
    UINT32 FASTADDR                                :  12;  // Bits 11:0
    UINT32 RSVD                                    :  4;  // Bits 15:12
    UINT32 ADDREN                                  :  1;  // Bits 16:16
    UINT32 SEQEN                                   :  1;  // Bits 17:17
    UINT32 POL0                                    :  1;  // Bits 18:18
    UINT32 POL1                                    :  1;  // Bits 19:19
    UINT32 CMDA                                    :  4;  // Bits 23:20
    UINT32 CMDB                                    :  4;  // Bits 27:24
    UINT32 CMDDEL                                  :  4;  // Bits 31:28
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCHBAR_CH0_CR_DCLK_LDAT_PDAT_STRUCT;

typedef union {
  struct {
    UINT32 BANKSEL                                 :  4;  // Bits 3:0
    UINT32 ADDR_LIM                                :  1;  // Bits 4:4
    UINT32 ARRAYSEL                                :  5;  // Bits 9:5
    UINT32 CMP                                     :  1;  // Bits 10:10
    UINT32 REP                                     :  1;  // Bits 11:11
    UINT32 DWORD                                   :  4;  // Bits 15:12
    UINT32 MODE                                    :  2;  // Bits 17:16
    UINT32 MPMAP                                   :  4;  // Bits 21:18
    UINT32 RSVD                                    :  2;  // Bits 23:22
    UINT32 MPBOFFSET                               :  4;  // Bits 27:24
    UINT32 STAGE_EN                                :  1;  // Bits 28:28
    UINT32 SHADOW                                  :  2;  // Bits 30:29
    UINT32 RSVD1                                   :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCHBAR_CH0_CR_DCLK_LDAT_SDAT_STRUCT;

typedef union {
  struct {
    UINT32 DATOUT                                  :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCHBAR_CH0_CR_DCLK_LDAT_DATAOUT_STRUCT;

typedef union {
  struct {
    UINT32 DATIN                                   :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCHBAR_CH0_CR_DCLK_LDAT_DATAIN_0_STRUCT;

typedef union {
  struct {
    UINT32 FASTADDR                                :  12;  // Bits 11:0
    UINT32 RSVD                                    :  4;  // Bits 15:12
    UINT32 ADDREN                                  :  1;  // Bits 16:16
    UINT32 SEQEN                                   :  1;  // Bits 17:17
    UINT32 POL0                                    :  1;  // Bits 18:18
    UINT32 POL1                                    :  1;  // Bits 19:19
    UINT32 CMDA                                    :  4;  // Bits 23:20
    UINT32 CMDB                                    :  4;  // Bits 27:24
    UINT32 CMDDEL                                  :  4;  // Bits 31:28
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCHBAR_CH0_CR_QCLK_LDAT_PDAT_STRUCT;

typedef union {
  struct {
    UINT32 BANKSEL                                 :  4;  // Bits 3:0
    UINT32 ADDR_LIM                                :  1;  // Bits 4:4
    UINT32 ARRAYSEL                                :  5;  // Bits 9:5
    UINT32 CMP                                     :  1;  // Bits 10:10
    UINT32 REP                                     :  1;  // Bits 11:11
    UINT32 DWORD                                   :  4;  // Bits 15:12
    UINT32 MODE                                    :  2;  // Bits 17:16
    UINT32 MPMAP                                   :  4;  // Bits 21:18
    UINT32 RSVD                                    :  2;  // Bits 23:22
    UINT32 MPBOFFSET                               :  4;  // Bits 27:24
    UINT32 STAGE_EN                                :  1;  // Bits 28:28
    UINT32 SHADOW                                  :  2;  // Bits 30:29
    UINT32 RSVD1                                   :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCHBAR_CH0_CR_QCLK_LDAT_SDAT_STRUCT;

typedef union {
  struct {
    UINT32 DATOUT                                  :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCHBAR_CH0_CR_QCLK_LDAT_DATAOUT_STRUCT;

typedef union {
  struct {
    UINT32 DATIN                                   :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCHBAR_CH0_CR_QCLK_LDAT_DATAIN_0_STRUCT;

typedef union {
  struct {
    UINT32 DATIN                                   :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCHBAR_CH0_CR_QCLK_LDAT_DATAIN_1_STRUCT;

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
} MCHBAR_CH0_CR_VISA_SLIDE_MCMNTS_STRUCT;

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
} MCHBAR_CH0_CR_VISA_XBAR_MCMNTS_STRUCT;

typedef union {
  struct {
    UINT32 Count                                   :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCHBAR_CH0_CR_PM_ALL_RANKS_CKE_LOW_COUNT_STRUCT;

typedef union {
  struct {
    UINT32 Valid                                   :  1;  // Bits 0:0
    UINT32 Rank                                    :  2;  // Bits 2:1
    UINT32 Group                                   :  2;  // Bits 4:3
    UINT32 Bank                                    :  2;  // Bits 6:5
    UINT32 Row                                     :  17;  // Bits 23:7
    UINT32                                         :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCHBAR_CH0_CR_RH_ADDRESS_STRUCT;

typedef union {
  struct {
    UINT32 LFSR_0                                  :  32;  // Bits 31:0
    UINT32 LFSR_1                                  :  32;  // Bits 63:32
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} MCHBAR_CH0_CR_RH_LFSR_STRUCT;

typedef union {
  struct {
    UINT32 Mode                                    :  4;  // Bits 3:0
    UINT32 Always_block_rank                       :  1;  // Bits 4:4
    UINT32 Always_PREALL                           :  1;  // Bits 5:5
    UINT32 LFSR_0_MASK                             :  4;  // Bits 9:6
    UINT32 LFSR_1_MASK                             :  4;  // Bits 13:10
    UINT32 MA3_Swizzling                           :  2;  // Bits 15:14
    UINT32 TRR_wait_cycles                         :  6;  // Bits 21:16
    UINT32 Always_calc_victim_row                  :  1;  // Bits 22:22
    UINT32 MA0_Swizzling                           :  2;  // Bits 24:23
    UINT32                                         :  7;  // Bits 31:25
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCHBAR_CH0_CR_RH_CONTROL_STRUCT;

typedef union {
  struct {
    UINT32 Counter_Status                          :  23;  // Bits 22:0
    UINT32                                         :  9;  // Bits 31:23
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCHBAR_CH0_CR_REUT_CH_ERR_COUNTER_STATUS_0_STRUCT;

typedef union {
  struct {
    UINT32 Counter_Status                          :  23;  // Bits 22:0
    UINT32                                         :  9;  // Bits 31:23
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCHBAR_CH0_CR_REUT_CH_ERR_COUNTER_STATUS_1_STRUCT;

typedef union {
  struct {
    UINT32 Counter_Status                          :  23;  // Bits 22:0
    UINT32                                         :  9;  // Bits 31:23
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCHBAR_CH0_CR_REUT_CH_ERR_COUNTER_STATUS_2_STRUCT;

typedef union {
  struct {
    UINT32 Counter_Status                          :  23;  // Bits 22:0
    UINT32                                         :  9;  // Bits 31:23
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCHBAR_CH0_CR_REUT_CH_ERR_COUNTER_STATUS_3_STRUCT;

typedef union {
  struct {
    UINT32 Counter_Status                          :  23;  // Bits 22:0
    UINT32                                         :  9;  // Bits 31:23
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCHBAR_CH0_CR_REUT_CH_ERR_COUNTER_STATUS_4_STRUCT;

typedef union {
  struct {
    UINT32 Counter_Status                          :  23;  // Bits 22:0
    UINT32                                         :  9;  // Bits 31:23
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCHBAR_CH0_CR_REUT_CH_ERR_COUNTER_STATUS_5_STRUCT;

typedef union {
  struct {
    UINT32 Counter_Status                          :  23;  // Bits 22:0
    UINT32                                         :  9;  // Bits 31:23
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCHBAR_CH0_CR_REUT_CH_ERR_COUNTER_STATUS_6_STRUCT;

typedef union {
  struct {
    UINT32 Counter_Status                          :  23;  // Bits 22:0
    UINT32                                         :  9;  // Bits 31:23
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCHBAR_CH0_CR_REUT_CH_ERR_COUNTER_STATUS_7_STRUCT;

typedef union {
  struct {
    UINT32 Counter_Status                          :  23;  // Bits 22:0
    UINT32                                         :  9;  // Bits 31:23
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCHBAR_CH0_CR_REUT_CH_ERR_COUNTER_STATUS_8_STRUCT;

typedef union {
  struct {
    UINT32 Stop_on_Nth_Error                       :  6;  // Bits 5:0
    UINT32                                         :  2;  // Bits 7:6
    UINT32 Stop_on_CA_ALERT                        :  1;  // Bits 8:8
    UINT32                                         :  3;  // Bits 11:9
    UINT32 Stop_On_Error_Control                   :  2;  // Bits 13:12
    UINT32                                         :  2;  // Bits 15:14
    UINT32 Selective_Error_Enable_Chunk            :  8;  // Bits 23:16
    UINT32 Selective_Error_Enable_Cacheline        :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCHBAR_CH0_CR_REUT_CH_ERR_CTL_STRUCT;

typedef union {
  struct {
    UINT32 ECC_Error_Mask                          :  8;  // Bits 7:0
    UINT32                                         :  24;  // Bits 31:8
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCHBAR_CH0_CR_REUT_CH_ERR_ECC_MASK_STRUCT;

typedef union {
  struct {
    UINT32 Data_Error_MaskLow                      :  32;  // Bits 31:0
    UINT32 Data_Error_MaskHigh                     :  32;  // Bits 63:32
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} MCHBAR_CH0_CR_REUT_CH_ERR_DATA_MASK_STRUCT;

typedef union {
  struct {
    UINT32 Data_Error_StatusLow                    :  32;  // Bits 31:0
    UINT32 Data_Error_StatusHigh                   :  32;  // Bits 63:32
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} MCHBAR_CH0_CR_REUT_CH_ERR_DATA_STATUS_STRUCT;

typedef union {
  struct {
    UINT32 ECC_Error_Status                        :  8;  // Bits 7:0
    UINT32 Chunk_Error_Status                      :  8;  // Bits 15:8
    UINT32 Rank_Error_Status                       :  4;  // Bits 19:16
    UINT32 Alert_Error_Status                      :  1;  // Bits 20:20
    UINT32                                         :  11;  // Bits 31:21
    UINT32 Byte_Group_Error_Status                 :  9;  // Bits 40:32
    UINT32                                         :  11;  // Bits 51:41
    UINT32 WDB_Rd_Chunk_Num_Status                 :  3;  // Bits 54:52
    UINT32                                         :  1;  // Bits 55:55
    UINT32 Nth_Error                               :  6;  // Bits 61:56
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} MCHBAR_CH0_CR_REUT_CH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_STRUCT;

typedef union {
  struct {
    UINT32 Column_Address                          :  11;  // Bits 10:0
    UINT32                                         :  13;  // Bits 23:11
    UINT32 Row_AddressLow                          :  8;  // Bits 31:24
    UINT32 Row_AddressHigh                         :  9;  // Bits 40:32
    UINT32                                         :  7;  // Bits 47:41
    UINT32 Bank_Address                            :  4;  // Bits 51:48
    UINT32                                         :  4;  // Bits 55:52
    UINT32 Rank_Address                            :  2;  // Bits 57:56
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} MCHBAR_CH0_CR_REUT_CH_ERROR_ADDR_STRUCT;

typedef union {
  struct {
    UINT32 Enable_WDB_Capture                      :  1;  // Bits 0:0
    UINT32 WDB_Error_Sel_Capture                   :  1;  // Bits 1:1
    UINT32 WDB_Data_Sel_Capture                    :  1;  // Bits 2:2
    UINT32                                         :  5;  // Bits 7:3
    UINT32 WDB_Starting_Capture_Pointer            :  6;  // Bits 13:8
    UINT32                                         :  2;  // Bits 15:14
    UINT32 WDB_Ending_Capture_Pointer              :  6;  // Bits 21:16
    UINT32                                         :  10;  // Bits 31:22
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCHBAR_CH0_CR_REUT_CH_WDB_CAPTURE_CTL_STRUCT;

typedef union {
  struct {
    UINT32 WDB_Current_Capture_Pointer             :  6;  // Bits 5:0
    UINT32                                         :  26;  // Bits 31:6
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCHBAR_CH0_CR_REUT_CH_WDB_CAPTURE_STATUS_STRUCT;

typedef union {
  struct {
    UINT32 Counter_Pointer                         :  7;  // Bits 6:0
    UINT32 Counter_Control                         :  2;  // Bits 8:7
    UINT32                                         :  23;  // Bits 31:9
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCHBAR_CH0_CR_REUT_CH_ERR_COUNTER_CTL_0_STRUCT;

typedef union {
  struct {
    UINT32 Counter_Pointer                         :  7;  // Bits 6:0
    UINT32 Counter_Control                         :  2;  // Bits 8:7
    UINT32                                         :  23;  // Bits 31:9
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCHBAR_CH0_CR_REUT_CH_ERR_COUNTER_CTL_1_STRUCT;

typedef union {
  struct {
    UINT32 Counter_Pointer                         :  7;  // Bits 6:0
    UINT32 Counter_Control                         :  2;  // Bits 8:7
    UINT32                                         :  23;  // Bits 31:9
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCHBAR_CH0_CR_REUT_CH_ERR_COUNTER_CTL_2_STRUCT;

typedef union {
  struct {
    UINT32 Counter_Pointer                         :  7;  // Bits 6:0
    UINT32 Counter_Control                         :  2;  // Bits 8:7
    UINT32                                         :  23;  // Bits 31:9
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCHBAR_CH0_CR_REUT_CH_ERR_COUNTER_CTL_3_STRUCT;

typedef union {
  struct {
    UINT32 Counter_Pointer                         :  7;  // Bits 6:0
    UINT32 Counter_Control                         :  2;  // Bits 8:7
    UINT32                                         :  23;  // Bits 31:9
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCHBAR_CH0_CR_REUT_CH_ERR_COUNTER_CTL_4_STRUCT;

typedef union {
  struct {
    UINT32 Counter_Pointer                         :  7;  // Bits 6:0
    UINT32 Counter_Control                         :  2;  // Bits 8:7
    UINT32                                         :  23;  // Bits 31:9
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCHBAR_CH0_CR_REUT_CH_ERR_COUNTER_CTL_5_STRUCT;

typedef union {
  struct {
    UINT32 Counter_Pointer                         :  7;  // Bits 6:0
    UINT32 Counter_Control                         :  2;  // Bits 8:7
    UINT32                                         :  23;  // Bits 31:9
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCHBAR_CH0_CR_REUT_CH_ERR_COUNTER_CTL_6_STRUCT;

typedef union {
  struct {
    UINT32 Counter_Pointer                         :  7;  // Bits 6:0
    UINT32 Counter_Control                         :  2;  // Bits 8:7
    UINT32                                         :  23;  // Bits 31:9
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCHBAR_CH0_CR_REUT_CH_ERR_COUNTER_CTL_7_STRUCT;

typedef union {
  struct {
    UINT32 Counter_Pointer                         :  7;  // Bits 6:0
    UINT32 Counter_Control                         :  2;  // Bits 8:7
    UINT32                                         :  23;  // Bits 31:9
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCHBAR_CH0_CR_REUT_CH_ERR_COUNTER_CTL_8_STRUCT;

typedef union {
  struct {
    UINT32 Counter_Overflow_Status                 :  9;  // Bits 8:0
    UINT32                                         :  23;  // Bits 31:9
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCHBAR_CH0_CR_REUT_CH_ERR_COUNTER_OVERFLOW_STATUS_STRUCT;

typedef union {
  struct {
    UINT32 WDB_Current_Read_Pointer                :  6;  // Bits 5:0
    UINT32                                         :  26;  // Bits 31:6
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCHBAR_CH0_CR_REUT_CH_PAT_WDB_CL_RD_STATUS_STRUCT;

typedef union {
  struct {
    UINT32 MR0                                     :  14;  // Bits 13:0
    UINT32                                         :  2;  // Bits 15:14
    UINT32 MR1                                     :  14;  // Bits 29:16
    UINT32                                         :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCHBAR_CH0_CR_DDR4_MR0_MR1_CONTENT_STRUCT;

typedef union {
  struct {
    UINT32 MR2                                     :  14;  // Bits 13:0
    UINT32                                         :  2;  // Bits 15:14
    UINT32 MR3                                     :  14;  // Bits 29:16
    UINT32                                         :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCHBAR_CH0_CR_DDR4_MR2_MR3_CONTENT_STRUCT;

typedef union {
  struct {
    UINT32 MR4                                     :  14;  // Bits 13:0
    UINT32                                         :  2;  // Bits 15:14
    UINT32 MR5                                     :  14;  // Bits 29:16
    UINT32                                         :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCHBAR_CH0_CR_DDR4_MR4_MR5_CONTENT_STRUCT;

typedef union {
  struct {
    UINT32 MR6                                     :  14;  // Bits 13:0
    UINT32                                         :  2;  // Bits 15:14
    UINT32 MR7                                     :  14;  // Bits 29:16
    UINT32                                         :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCHBAR_CH0_CR_DDR4_MR6_MR7_CONTENT_STRUCT;

typedef union {
  struct {
    UINT32 Rank0_Byte0                             :  2;  // Bits 1:0
    UINT32 Rank0_Byte1                             :  2;  // Bits 3:2
    UINT32 Rank0_Byte2                             :  2;  // Bits 5:4
    UINT32 Rank0_Byte3                             :  2;  // Bits 7:6
    UINT32 Rank0_Byte4                             :  2;  // Bits 9:8
    UINT32 Rank0_Byte5                             :  2;  // Bits 11:10
    UINT32 Rank0_Byte6                             :  2;  // Bits 13:12
    UINT32 Rank0_Byte7                             :  2;  // Bits 15:14
    UINT32 Rank1_Byte0                             :  2;  // Bits 17:16
    UINT32 Rank1_Byte1                             :  2;  // Bits 19:18
    UINT32 Rank1_Byte2                             :  2;  // Bits 21:20
    UINT32 Rank1_Byte3                             :  2;  // Bits 23:22
    UINT32 Rank1_Byte4                             :  2;  // Bits 25:24
    UINT32 Rank1_Byte5                             :  2;  // Bits 27:26
    UINT32 Rank1_Byte6                             :  2;  // Bits 29:28
    UINT32 Rank1_Byte7                             :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCHBAR_CH0_CR_DDR4_MR1_ODIC_VALUES_STRUCT;

typedef union {
  struct {
    UINT32 Rank0_Byte0                             :  2;  // Bits 1:0
    UINT32 Rank0_Byte1                             :  2;  // Bits 3:2
    UINT32 Rank0_Byte2                             :  2;  // Bits 5:4
    UINT32 Rank0_Byte3                             :  2;  // Bits 7:6
    UINT32 Rank0_Byte4                             :  2;  // Bits 9:8
    UINT32 Rank0_Byte5                             :  2;  // Bits 11:10
    UINT32 Rank0_Byte6                             :  2;  // Bits 13:12
    UINT32 Rank0_Byte7                             :  2;  // Bits 15:14
    UINT32 Rank1_Byte0                             :  2;  // Bits 17:16
    UINT32 Rank1_Byte1                             :  2;  // Bits 19:18
    UINT32 Rank1_Byte2                             :  2;  // Bits 21:20
    UINT32 Rank1_Byte3                             :  2;  // Bits 23:22
    UINT32 Rank1_Byte4                             :  2;  // Bits 25:24
    UINT32 Rank1_Byte5                             :  2;  // Bits 27:26
    UINT32 Rank1_Byte6                             :  2;  // Bits 29:28
    UINT32 Rank1_Byte7                             :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCHBAR_CH0_CR_DDR4_MR2_RTT_WR_VALUES_STRUCT;

typedef union {
  struct {
    UINT32 Byte0                                   :  7;  // Bits 6:0
    UINT32                                         :  1;  // Bits 7:7
    UINT32 Byte1                                   :  7;  // Bits 14:8
    UINT32                                         :  1;  // Bits 15:15
    UINT32 Byte2                                   :  7;  // Bits 22:16
    UINT32                                         :  1;  // Bits 23:23
    UINT32 Byte3                                   :  7;  // Bits 30:24
    UINT32                                         :  1;  // Bits 31:31
    UINT32 Byte4                                   :  7;  // Bits 38:32
    UINT32                                         :  1;  // Bits 39:39
    UINT32 Byte5                                   :  7;  // Bits 46:40
    UINT32                                         :  1;  // Bits 47:47
    UINT32 Byte6                                   :  7;  // Bits 54:48
    UINT32                                         :  1;  // Bits 55:55
    UINT32 Byte7                                   :  7;  // Bits 62:56
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} MCHBAR_CH0_CR_DDR4_MR6_VREF_VALUES_0_STRUCT;

typedef union {
  struct {
    UINT32 Byte0                                   :  7;  // Bits 6:0
    UINT32                                         :  1;  // Bits 7:7
    UINT32 Byte1                                   :  7;  // Bits 14:8
    UINT32                                         :  1;  // Bits 15:15
    UINT32 Byte2                                   :  7;  // Bits 22:16
    UINT32                                         :  1;  // Bits 23:23
    UINT32 Byte3                                   :  7;  // Bits 30:24
    UINT32                                         :  1;  // Bits 31:31
    UINT32 Byte4                                   :  7;  // Bits 38:32
    UINT32                                         :  1;  // Bits 39:39
    UINT32 Byte5                                   :  7;  // Bits 46:40
    UINT32                                         :  1;  // Bits 47:47
    UINT32 Byte6                                   :  7;  // Bits 54:48
    UINT32                                         :  1;  // Bits 55:55
    UINT32 Byte7                                   :  7;  // Bits 62:56
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} MCHBAR_CH0_CR_DDR4_MR6_VREF_VALUES_1_STRUCT;

typedef union {
  struct {
    UINT32 MR1                                     :  8;  // Bits 7:0
    UINT32 MR2                                     :  8;  // Bits 15:8
    UINT32 MR3                                     :  8;  // Bits 23:16
    UINT32 MR11                                    :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCHBAR_CH0_CR_LPDDR3_MR_CONTENT_STRUCT;

typedef union {
  struct {
    UINT32 DDR4_Restore_MR                         :  8;  // Bits 7:0
    UINT32 DDR4_Restore_MR1_Per_Device             :  1;  // Bits 8:8
    UINT32 DDR4_Restore_MR2_Per_Device             :  1;  // Bits 9:9
    UINT32 DDR4_Restore_MR6_Per_Device             :  1;  // Bits 10:10
    UINT32                                         :  5;  // Bits 15:11
    UINT32 LPDDR3_Restore_MR                       :  4;  // Bits 19:16
    UINT32 do_ZQCL                                 :  1;  // Bits 20:20
    UINT32 zero_rank1_MR11                         :  1;  // Bits 21:21
    UINT32 vref_time_per_byte                      :  1;  // Bits 22:22
    UINT32                                         :  1;  // Bits 23:23
    UINT32 tVREFDQ                                 :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCHBAR_CH0_CR_MRS_FSM_CONTROL_STRUCT;

typedef union {
  struct {
    UINT32 Run                                     :  1;  // Bits 0:0
    UINT32                                         :  31;  // Bits 31:1
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCHBAR_CH0_CR_MRS_FSM_RUN_STRUCT;

typedef union {
  struct {
    UINT32 Spare_RW                                :  8;  // Bits 7:0
    UINT32 ForceX2Ref                              :  1;  // Bits 8:8
    UINT32 ForceX4Ref                              :  1;  // Bits 9:9
    UINT32 ForceTxAnalog                           :  1;  // Bits 10:10
    UINT32 TxAnalog_grace                          :  4;  // Bits 14:11
    UINT32 DisSREXcnt                              :  1;  // Bits 15:15
    UINT32 Spare_RW_V                              :  16;  // Bits 31:16
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCHBAR_CH0_CR_MCMNTS_SPARE_STRUCT;

typedef union {
  struct {
    UINT32 tRP                                     :  6;  // Bits 5:0
    UINT32 tRPab_ext                               :  2;  // Bits 7:6
    UINT32 tRAS                                    :  7;  // Bits 14:8
    UINT32                                         :  1;  // Bits 15:15
    UINT32 tRDPRE                                  :  4;  // Bits 19:16
    UINT32                                         :  4;  // Bits 23:20
    UINT32 tWRPRE                                  :  7;  // Bits 30:24
    UINT32                                         :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCHBAR_CH1_CR_TC_PRE_STRUCT;

typedef union {
  struct {
    UINT32 tFAW                                    :  6;  // Bits 5:0
    UINT32                                         :  2;  // Bits 7:6
    UINT32 tRRD_sg                                 :  4;  // Bits 11:8
    UINT32 tRRD_dg                                 :  4;  // Bits 15:12
    UINT32 derating_ext                            :  2;  // Bits 17:16
    UINT32                                         :  14;  // Bits 31:18
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCHBAR_CH1_CR_TC_ACT_STRUCT;

typedef union {
  struct {
    UINT32 tCKE                                    :  4;  // Bits 3:0
    UINT32 tXP                                     :  4;  // Bits 7:4
    UINT32 tXPDLL                                  :  6;  // Bits 13:8
    UINT32 tPRPDEN                                 :  2;  // Bits 15:14
    UINT32 tRDPDEN                                 :  7;  // Bits 22:16
    UINT32                                         :  1;  // Bits 23:23
    UINT32 tWRPDEN                                 :  7;  // Bits 30:24
    UINT32                                         :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCHBAR_CH1_CR_TC_PWRDN_STRUCT;

typedef union {
  struct {
    UINT32 tRDRD_sg                                :  6;  // Bits 5:0
    UINT32                                         :  2;  // Bits 7:6
    UINT32 tRDRD_dg                                :  6;  // Bits 13:8
    UINT32                                         :  2;  // Bits 15:14
    UINT32 tRDRD_dr                                :  6;  // Bits 21:16
    UINT32                                         :  2;  // Bits 23:22
    UINT32 tRDRD_dd                                :  6;  // Bits 29:24
    UINT32                                         :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCHBAR_CH1_CR_TC_RDRD_STRUCT;

typedef union {
  struct {
    UINT32 tRDWR_sg                                :  6;  // Bits 5:0
    UINT32                                         :  2;  // Bits 7:6
    UINT32 tRDWR_dg                                :  6;  // Bits 13:8
    UINT32                                         :  2;  // Bits 15:14
    UINT32 tRDWR_dr                                :  6;  // Bits 21:16
    UINT32                                         :  2;  // Bits 23:22
    UINT32 tRDWR_dd                                :  6;  // Bits 29:24
    UINT32                                         :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCHBAR_CH1_CR_TC_RDWR_STRUCT;

typedef union {
  struct {
    UINT32 tWRRD_sg                                :  7;  // Bits 6:0
    UINT32                                         :  1;  // Bits 7:7
    UINT32 tWRRD_dg                                :  6;  // Bits 13:8
    UINT32                                         :  2;  // Bits 15:14
    UINT32 tWRRD_dr                                :  6;  // Bits 21:16
    UINT32                                         :  2;  // Bits 23:22
    UINT32 tWRRD_dd                                :  6;  // Bits 29:24
    UINT32                                         :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCHBAR_CH1_CR_TC_WRRD_STRUCT;

typedef union {
  struct {
    UINT32 tWRWR_sg                                :  6;  // Bits 5:0
    UINT32                                         :  2;  // Bits 7:6
    UINT32 tWRWR_dg                                :  6;  // Bits 13:8
    UINT32                                         :  2;  // Bits 15:14
    UINT32 tWRWR_dr                                :  6;  // Bits 21:16
    UINT32                                         :  2;  // Bits 23:22
    UINT32 tWRWR_dd                                :  6;  // Bits 29:24
    UINT32                                         :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCHBAR_CH1_CR_TC_WRWR_STRUCT;

typedef union {
  struct {
    UINT32 DRAM_technology                         :  2;  // Bits 1:0
    UINT32 CMD_stretch                             :  2;  // Bits 3:2
    UINT32 N_to_1_ratio                            :  3;  // Bits 6:4
    UINT32                                         :  1;  // Bits 7:7
    UINT32 Address_mirror                          :  2;  // Bits 9:8
    UINT32 x8_device                               :  2;  // Bits 11:10
    UINT32 tCPDED                                  :  3;  // Bits 14:12
    UINT32 LPDDR_2N_CS_MRW                         :  1;  // Bits 15:15
    UINT32 reset_on_command                        :  4;  // Bits 19:16
    UINT32 reset_delay                             :  3;  // Bits 22:20
    UINT32 cmd_3st                                 :  1;  // Bits 23:23
    UINT32 ck_to_cke                               :  3;  // Bits 26:24
    UINT32 enable_odt_matrix                       :  1;  // Bits 27:27
    UINT32 ddr_probeless_low_frequency             :  1;  // Bits 28:28
    UINT32 tCAL                                    :  3;  // Bits 31:29
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCHBAR_CH1_CR_SC_GS_CFG_STRUCT;

typedef union {
  struct {
    UINT32 Rank_0_latency                          :  7;  // Bits 6:0
    UINT32                                         :  1;  // Bits 7:7
    UINT32 Rank_1_latency                          :  7;  // Bits 14:8
    UINT32                                         :  1;  // Bits 15:15
    UINT32 Rank_2_latency                          :  7;  // Bits 22:16
    UINT32                                         :  1;  // Bits 23:23
    UINT32 Rank_3_latency                          :  7;  // Bits 30:24
    UINT32                                         :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCHBAR_CH1_CR_SC_ROUNDTRIP_LATENCY_STRUCT;

typedef union {
  struct {
    UINT32 Rank_0_flyby                            :  4;  // Bits 3:0
    UINT32 Rank_1_flyby                            :  4;  // Bits 7:4
    UINT32 Rank_2_flyby                            :  4;  // Bits 11:8
    UINT32 Rank_3_flyby                            :  4;  // Bits 15:12
    UINT32 IO_Latency_offset                       :  7;  // Bits 22:16
    UINT32                                         :  1;  // Bits 23:23
    UINT32 RFR_delay                               :  7;  // Bits 30:24
    UINT32                                         :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCHBAR_CH1_CR_SC_IO_LATENCY_STRUCT;

typedef union {
  struct {
    UINT32 dis_opp_cas                             :  1;  // Bits 0:0
    UINT32 dis_opp_is_cas                          :  1;  // Bits 1:1
    UINT32 dis_opp_ras                             :  1;  // Bits 2:2
    UINT32 dis_opp_is_ras                          :  1;  // Bits 3:3
    UINT32 dis_2c_byp                              :  1;  // Bits 4:4
    UINT32 dis_deprd_opt                           :  1;  // Bits 5:5
    UINT32 dis_pt_it                               :  1;  // Bits 6:6
    UINT32 dis_prcnt_ring                          :  1;  // Bits 7:7
    UINT32 dis_prcnt_sa                            :  1;  // Bits 8:8
    UINT32 dis_blkr_ph                             :  1;  // Bits 9:9
    UINT32 dis_blkr_pe                             :  1;  // Bits 10:10
    UINT32 dis_blkr_pm                             :  1;  // Bits 11:11
    UINT32 dis_odt                                 :  1;  // Bits 12:12
    UINT32 OE_alw_off                              :  1;  // Bits 13:13
    UINT32 block_rpq                               :  1;  // Bits 14:14
    UINT32 block_ipq                               :  1;  // Bits 15:15
    UINT32 block_wpq                               :  1;  // Bits 16:16
    UINT32 dis_zq                                  :  1;  // Bits 17:17
    UINT32 dis_tt                                  :  1;  // Bits 18:18
    UINT32 dis_opp_ref                             :  1;  // Bits 19:19
    UINT32 long_zq                                 :  1;  // Bits 20:20
    UINT32 dis_srx_zq                              :  1;  // Bits 21:21
    UINT32 serialize_zq                            :  1;  // Bits 22:22
    UINT32 zq_fast_exec                            :  1;  // Bits 23:23
    UINT32 dis_DriveNop                            :  1;  // Bits 24:24
    UINT32 dis_idle_preempt                        :  1;  // Bits 25:25
    UINT32 spare                                   :  4;  // Bits 29:26
    UINT32 dis_5cyc_read_gap                       :  1;  // Bits 30:30
    UINT32 dis_clk_gate                            :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCHBAR_CH1_CR_SCHED_CBIT_STRUCT;

typedef union {
  struct {
    UINT32 dis_srx_mr4                             :  1;  // Bits 0:0
    UINT32 dis_ck_tristate                         :  1;  // Bits 1:1
    UINT32 dis_burst_ref_limit                     :  1;  // Bits 2:2
    UINT32 dis_bus_retain                          :  1;  // Bits 3:3
    UINT32 dis_async_odt                           :  1;  // Bits 4:4
    UINT32 dis_SRX_reset                           :  1;  // Bits 5:5
    UINT32 dis_tcwl5_2qclk_add                     :  1;  // Bits 6:6
    UINT32 dis_SRX_MRS_MR4                         :  1;  // Bits 7:7
    UINT32 dis_opp_ref_idle_delay                  :  1;  // Bits 8:8
    UINT32 dis_ignore_1st_trefi                    :  1;  // Bits 9:9
    UINT32 echo_mask                               :  6;  // Bits 15:10
    UINT32 spare                                   :  16;  // Bits 31:16
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCHBAR_CH1_CR_SCHED_SECOND_CBIT_STRUCT;

typedef union {
  struct {
    UINT32 WDAR                                    :  1;  // Bits 0:0
    UINT32 WDB_Block_En                            :  1;  // Bits 1:1
    UINT32                                         :  2;  // Bits 3:2
    UINT32 force_rcv_en                            :  1;  // Bits 4:4
    UINT32                                         :  3;  // Bits 7:5
    UINT32 DDR_QUAL                                :  2;  // Bits 9:8
    UINT32 QUAL_Delay                              :  5;  // Bits 14:10
    UINT32 QUAL_Length                             :  2;  // Bits 16:15
    UINT32 dft_block_enable                        :  1;  // Bits 17:17
    UINT32                                         :  6;  // Bits 23:18
    UINT32 Stretch_mode                            :  2;  // Bits 25:24
    UINT32 STF                                     :  3;  // Bits 28:26
    UINT32                                         :  3;  // Bits 31:29
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCHBAR_CH1_CR_DFT_MISC_STRUCT;

typedef union {
  struct {
    UINT32 ECC_Inject                              :  3;  // Bits 2:0
    UINT32                                         :  1;  // Bits 3:3
    UINT32 ECC_correction_disable                  :  1;  // Bits 4:4
    UINT32                                         :  3;  // Bits 7:5
    UINT32 DIS_MCA_LOG                             :  1;  // Bits 8:8
    UINT32 DIS_PCH_EVENT                           :  1;  // Bits 9:9
    UINT32 DIS_RCH_POISON                          :  1;  // Bits 10:10
    UINT32 DIS_RCH_ERROR                           :  1;  // Bits 11:11
    UINT32                                         :  4;  // Bits 15:12
    UINT32 ECC_trigger                             :  2;  // Bits 17:16
    UINT32                                         :  14;  // Bits 31:18
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCHBAR_CH1_CR_ECC_DFT_STRUCT;

typedef union {
  struct {
    UINT32 Ring                                    :  10;  // Bits 9:0
    UINT32                                         :  6;  // Bits 15:10
    UINT32 SA                                      :  10;  // Bits 25:16
    UINT32                                         :  6;  // Bits 31:26
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCHBAR_CH1_CR_SC_PR_CNT_CONFIG_STRUCT;

typedef union {
  struct {
    UINT32 PCIT                                    :  8;  // Bits 7:0
    UINT32                                         :  8;  // Bits 15:8
    UINT32 PCIT_GT                                 :  8;  // Bits 23:16
    UINT32                                         :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCHBAR_CH1_CR_SC_PCIT_STRUCT;

typedef union {
  struct {
    UINT32 PDWN_idle_counter                       :  12;  // Bits 11:0
    UINT32 APD                                     :  1;  // Bits 12:12
    UINT32 PPD                                     :  1;  // Bits 13:13
    UINT32 Slow_Exit                               :  1;  // Bits 14:14
    UINT32 Global_PD                               :  1;  // Bits 15:15
    UINT32 TT_idle_counter                         :  8;  // Bits 23:16
    UINT32 dis_cke_tt                              :  1;  // Bits 24:24
    UINT32                                         :  7;  // Bits 31:25
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCHBAR_CH1_CR_PM_PDWN_CONFIG_STRUCT;

typedef union {
  struct {
    UINT32 Dis_Opp_rd                              :  1;  // Bits 0:0
    UINT32 ACT_Enable                              :  1;  // Bits 1:1
    UINT32 PRE_Enable                              :  1;  // Bits 2:2
    UINT32 MAX_RPQ_CAS                             :  4;  // Bits 6:3
    UINT32                                         :  25;  // Bits 31:7
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCHBAR_CH1_CR_WMM_READ_CONFIG_STRUCT;

typedef union {
  struct {
    UINT32 CERRSTS                                 :  1;  // Bits 0:0
    UINT32 MERRSTS                                 :  1;  // Bits 1:1
    UINT32                                         :  14;  // Bits 15:2
    UINT32 ERRSYND                                 :  8;  // Bits 23:16
    UINT32 ERRCHUNK                                :  3;  // Bits 26:24
    UINT32 ERRRANK                                 :  2;  // Bits 28:27
    UINT32 ERRBANK                                 :  3;  // Bits 31:29
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCHBAR_CH1_CR_ECCERRLOG0_STRUCT;

typedef union {
  struct {
    UINT32 ERRROW                                  :  17;  // Bits 16:0
    UINT32 ERRCOL                                  :  11;  // Bits 27:17
    UINT32 ERRBANKGROUP                            :  2;  // Bits 29:28
    UINT32                                         :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCHBAR_CH1_CR_ECCERRLOG1_STRUCT;

typedef union {
  struct {
    UINT32 EN_CLK                                  :  1;  // Bits 0:0
    UINT32 L0_DATA_BYTE_SEL                        :  7;  // Bits 7:1
    UINT32 L0_BYP_SEL                              :  1;  // Bits 8:8
    UINT32 L1_DATA_BYTE_SEL                        :  7;  // Bits 15:9
    UINT32 L1_BYP_SEL                              :  1;  // Bits 16:16
    UINT32                                         :  10;  // Bits 26:17
    UINT32 PATGENMODE                              :  3;  // Bits 29:27
    UINT32                                         :  1;  // Bits 30:30
    UINT32 VORANGE                                 :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCHBAR_CH1_CR_VISA_CTL_MCSCHEDS_STRUCT;

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
} MCHBAR_CH1_CR_VISA_XBAR_MCSCHEDS_STRUCT;

typedef union {
  struct {
    UINT32 RPQ_disable                             :  22;  // Bits 21:0
    UINT32                                         :  10;  // Bits 31:22
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCHBAR_CH1_CR_QUEUE_ENTRY_DISABLE_RPQ_STRUCT;

typedef union {
  struct {
    UINT32 IPQ_disable                             :  10;  // Bits 9:0
    UINT32                                         :  22;  // Bits 31:10
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCHBAR_CH1_CR_QUEUE_ENTRY_DISABLE_IPQ_STRUCT;

typedef union {
  struct {
    UINT32 WPQ_disableLow                          :  32;  // Bits 31:0
    UINT32 WPQ_disableHigh                         :  32;  // Bits 63:32
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} MCHBAR_CH1_CR_QUEUE_ENTRY_DISABLE_WPQ_STRUCT;

typedef union {
  struct {
    UINT32 WMM_entry_wm                            :  7;  // Bits 6:0
    UINT32                                         :  1;  // Bits 7:7
    UINT32 WMM_exit_wm                             :  7;  // Bits 14:8
    UINT32                                         :  1;  // Bits 15:15
    UINT32 WIM_wm                                  :  7;  // Bits 22:16
    UINT32                                         :  1;  // Bits 23:23
    UINT32 EDRAM_scrub_wm                          :  7;  // Bits 30:24
    UINT32                                         :  1;  // Bits 31:31
    UINT32 Read_CAS_count                          :  8;  // Bits 39:32
    UINT32 Write_CAS_count                         :  8;  // Bits 47:40
    UINT32 Write_CAS_count_for_VC1                 :  8;  // Bits 55:48
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} MCHBAR_CH1_CR_SC_WDBWM_STRUCT;

typedef union {
  struct {
    UINT32 ODT_read_duration                       :  3;  // Bits 2:0
    UINT32                                         :  1;  // Bits 3:3
    UINT32 ODT_Read_Delay                          :  3;  // Bits 6:4
    UINT32                                         :  1;  // Bits 7:7
    UINT32 ODT_write_duration                      :  3;  // Bits 10:8
    UINT32                                         :  1;  // Bits 11:11
    UINT32 ODT_Write_Delay                         :  3;  // Bits 14:12
    UINT32 Write_Early_ODT                         :  1;  // Bits 15:15
    UINT32 tCL                                     :  5;  // Bits 20:16
    UINT32 tCWL                                    :  5;  // Bits 25:21
    UINT32 tAONPD                                  :  5;  // Bits 30:26
    UINT32 ODT_Always_Rank0                        :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCHBAR_CH1_CR_TC_ODT_STRUCT;

typedef union {
  struct {
    UINT32 Spare_RW                                :  6;  // Bits 5:0
    UINT32 cmd_delay_counter                       :  4;  // Bits 9:6
    UINT32 cmd_delay_disable                       :  1;  // Bits 10:10
    UINT32 cke_delay_counter                       :  4;  // Bits 14:11
    UINT32 cke_delay_disable                       :  1;  // Bits 15:15
    UINT32 Spare_RW_V                              :  16;  // Bits 31:16
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCHBAR_CH1_CR_MCSCHEDS_SPARE_STRUCT;

typedef union {
  struct {
    UINT32 shift_16                                :  1;  // Bits 0:0
    UINT32 clken_pulse_mode                        :  1;  // Bits 1:1
    UINT32 reg_clken_mode                          :  1;  // Bits 2:2
    UINT32 reg_clken                               :  1;  // Bits 3:3
    UINT32 feedback_en                             :  1;  // Bits 4:4
    UINT32 event_mode                              :  1;  // Bits 5:5
    UINT32 lfsr_reset                              :  1;  // Bits 6:6
    UINT32 sdo_en                                  :  1;  // Bits 7:7
    UINT32                                         :  8;  // Bits 15:8
    UINT32 cr_rd_data                              :  16;  // Bits 31:16
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCHBAR_CH1_CR_MC_MISR_STRUCT;

typedef union {
  struct {
    UINT32 Read_Rank_0                             :  4;  // Bits 3:0
    UINT32 Read_Rank_1                             :  4;  // Bits 7:4
    UINT32 Read_Rank_2                             :  4;  // Bits 11:8
    UINT32 Read_Rank_3                             :  4;  // Bits 15:12
    UINT32 Write_Rank_0                            :  4;  // Bits 19:16
    UINT32 Write_Rank_1                            :  4;  // Bits 23:20
    UINT32 Write_Rank_2                            :  4;  // Bits 27:24
    UINT32 Write_Rank_3                            :  4;  // Bits 31:28
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCHBAR_CH1_CR_SC_ODT_MATRIX_STRUCT;

typedef union {
  struct {
    UINT32 dft_block_cycles                        :  16;  // Bits 15:0
    UINT32 dft_nonblock_cycles                     :  16;  // Bits 31:16
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCHBAR_CH1_CR_DFT_BLOCK_STRUCT;

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
} MCHBAR_CH1_CR_VISA_SLIDE_MCSCHEDS_STRUCT;

typedef union {
  struct {
    UINT32 Mux0_Control                            :  2;  // Bits 1:0
    UINT32                                         :  1;  // Bits 2:2
    UINT32 Mux1_Control                            :  2;  // Bits 4:3
    UINT32                                         :  1;  // Bits 5:5
    UINT32 Mux2_Control                            :  2;  // Bits 7:6
    UINT32 LFSR_Type                               :  3;  // Bits 10:8
    UINT32 Chaining_LFSR                           :  1;  // Bits 11:11
    UINT32                                         :  2;  // Bits 13:12
    UINT32 ECC_Replace_Byte_Control                :  1;  // Bits 14:14
    UINT32 ECC_Data_Source_Sel                     :  1;  // Bits 15:15
    UINT32 Save_LFSR_Seed_Rate                     :  8;  // Bits 23:16
    UINT32 Reload_LFSR_Seed_Rate                   :  5;  // Bits 28:24
    UINT32                                         :  2;  // Bits 30:29
    UINT32 Reload_Save_LFSR_Seed_Rate_Mode         :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCHBAR_CH1_CR_REUT_CH_PAT_WDB_CL_MUX_CFG_STRUCT;

typedef union {
  struct {
    UINT32 Pattern_Buffer                          :  24;  // Bits 23:0
    UINT32                                         :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCHBAR_CH1_CR_REUT_CH_PAT_WDB_CL_MUX_PB_WR_0_STRUCT;

typedef union {
  struct {
    UINT32 Pattern_Buffer                          :  24;  // Bits 23:0
    UINT32                                         :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCHBAR_CH1_CR_REUT_CH_PAT_WDB_CL_MUX_PB_WR_1_STRUCT;

typedef union {
  struct {
    UINT32 Pattern_Buffer                          :  24;  // Bits 23:0
    UINT32                                         :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCHBAR_CH1_CR_REUT_CH_PAT_WDB_CL_MUX_PB_WR_2_STRUCT;

typedef union {
  struct {
    UINT32 Pattern_Buffer                          :  24;  // Bits 23:0
    UINT32                                         :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCHBAR_CH1_CR_REUT_CH_PAT_WDB_CL_MUX_PB_RD_0_STRUCT;

typedef union {
  struct {
    UINT32 Pattern_Buffer                          :  24;  // Bits 23:0
    UINT32                                         :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCHBAR_CH1_CR_REUT_CH_PAT_WDB_CL_MUX_PB_RD_1_STRUCT;

typedef union {
  struct {
    UINT32 Pattern_Buffer                          :  24;  // Bits 23:0
    UINT32                                         :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCHBAR_CH1_CR_REUT_CH_PAT_WDB_CL_MUX_PB_RD_2_STRUCT;

typedef union {
  struct {
    UINT32 Pattern_Buffer                          :  24;  // Bits 23:0
    UINT32                                         :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCHBAR_CH1_CR_REUT_CH_PAT_WDB_CL_MUX_PB_STATUS_WR_0_STRUCT;

typedef union {
  struct {
    UINT32 Pattern_Buffer                          :  24;  // Bits 23:0
    UINT32                                         :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCHBAR_CH1_CR_REUT_CH_PAT_WDB_CL_MUX_PB_STATUS_WR_1_STRUCT;

typedef union {
  struct {
    UINT32 Pattern_Buffer                          :  24;  // Bits 23:0
    UINT32                                         :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCHBAR_CH1_CR_REUT_CH_PAT_WDB_CL_MUX_PB_STATUS_WR_2_STRUCT;

typedef union {
  struct {
    UINT32 Pattern_Buffer                          :  24;  // Bits 23:0
    UINT32                                         :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCHBAR_CH1_CR_REUT_CH_PAT_WDB_CL_MUX_PB_STATUS_RD_0_STRUCT;

typedef union {
  struct {
    UINT32 Pattern_Buffer                          :  24;  // Bits 23:0
    UINT32                                         :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCHBAR_CH1_CR_REUT_CH_PAT_WDB_CL_MUX_PB_STATUS_RD_1_STRUCT;

typedef union {
  struct {
    UINT32 Pattern_Buffer                          :  24;  // Bits 23:0
    UINT32                                         :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCHBAR_CH1_CR_REUT_CH_PAT_WDB_CL_MUX_PB_STATUS_RD_2_STRUCT;

typedef union {
  struct {
    UINT32 L_data_select                           :  1;  // Bits 0:0
    UINT32 Enable_Sweep_Frequency                  :  1;  // Bits 1:1
    UINT32                                         :  6;  // Bits 7:2
    UINT32 L_counter                               :  8;  // Bits 15:8
    UINT32 M_counter                               :  8;  // Bits 23:16
    UINT32 N_counter                               :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCHBAR_CH1_CR_REUT_CH_PAT_WDB_CL_MUX_LMN_STRUCT;

typedef union {
  struct {
    UINT32 Write_Address_as_Data                   :  1;  // Bits 0:0
    UINT32 Read_Address_as_Data                    :  1;  // Bits 1:1
    UINT32                                         :  30;  // Bits 31:2
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCHBAR_CH1_CR_REUT_CH_PAT_WDB_ADDRESS_AS_DATA_CTRL_STRUCT;

typedef union {
  struct {
    UINT32 ECC_Inv_or_DC_Enable                    :  8;  // Bits 7:0
    UINT32                                         :  8;  // Bits 15:8
    UINT32 Inv_or_DC_Shift_Rate                    :  4;  // Bits 19:16
    UINT32 DC_Polarity_Control                     :  1;  // Bits 20:20
    UINT32                                         :  9;  // Bits 29:21
    UINT32 Inv_or_DC_Control                       :  1;  // Bits 30:30
    UINT32 Inv_or_DC_Shift_Enable                  :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCHBAR_CH1_CR_REUT_CH_PAT_WDB_INV_STRUCT;

typedef union {
  struct {
    UINT32 Data_Inv_or_DC_EnableLow                :  32;  // Bits 31:0
    UINT32 Data_Inv_or_DC_EnableHigh               :  32;  // Bits 63:32
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} MCHBAR_CH1_CR_REUT_CH_PAT_WDB_DATA_INV_STRUCT;

typedef union {
  struct {
    UINT32 CKE_Override                            :  4;  // Bits 3:0
    UINT32                                         :  4;  // Bits 7:4
    UINT32 CKE_En_Start_Test_Sync                  :  1;  // Bits 8:8
    UINT32                                         :  7;  // Bits 15:9
    UINT32 CKE_On                                  :  4;  // Bits 19:16
    UINT32                                         :  12;  // Bits 31:20
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCHBAR_CH1_CR_REUT_CH_MISC_CKE_CTRL_STRUCT;

typedef union {
  struct {
    UINT32 ODT_Override                            :  4;  // Bits 3:0
    UINT32                                         :  12;  // Bits 15:4
    UINT32 ODT_On                                  :  4;  // Bits 19:16
    UINT32                                         :  11;  // Bits 30:20
    UINT32 MPR_Train_DDR_On                        :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCHBAR_CH1_CR_REUT_CH_MISC_ODT_CTRL_STRUCT;

typedef union {
  struct {
    UINT32 Enable_CADB_on_Deselect                 :  1;  // Bits 0:0
    UINT32 Enable_CADB_Always_On                   :  1;  // Bits 1:1
    UINT32 CMD_Deselect_Start                      :  4;  // Bits 5:2
    UINT32 CMD_Deselect_Stop                       :  4;  // Bits 9:6
    UINT32 Lane_Deselect_Enable                    :  4;  // Bits 13:10
    UINT32 CAS_Select_Enable                       :  2;  // Bits 15:14
    UINT32 ACT_Select_Enable                       :  2;  // Bits 17:16
    UINT32 PRE_Select_Enable                       :  2;  // Bits 19:18
    UINT32 Save_Current_Seed                       :  4;  // Bits 23:20
    UINT32 Reload_Starting_Seed                    :  4;  // Bits 27:24
    UINT32                                         :  4;  // Bits 31:28
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCHBAR_CH1_CR_REUT_CH_PAT_CADB_CTRL_STRUCT;

typedef union {
  struct {
    UINT32 MRS_Gap                                 :  3;  // Bits 2:0
    UINT32                                         :  4;  // Bits 6:3
    UINT32 MRS_Gap_Scale                           :  1;  // Bits 7:7
    UINT32 CADB_MRS_Start_Pointer                  :  3;  // Bits 10:8
    UINT32                                         :  5;  // Bits 15:11
    UINT32 CADB_MRS_End_Pointer                    :  3;  // Bits 18:16
    UINT32                                         :  5;  // Bits 23:19
    UINT32 CADB_MRS_Current_Pointer                :  3;  // Bits 26:24
    UINT32                                         :  1;  // Bits 27:27
    UINT32 MRS_Wait_Scale                          :  1;  // Bits 28:28
    UINT32 MRS_Wait                                :  3;  // Bits 31:29
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCHBAR_CH1_CR_REUT_CH_PAT_CADB_MRS_STRUCT;

typedef union {
  struct {
    UINT32 Mux0_Control                            :  2;  // Bits 1:0
    UINT32                                         :  2;  // Bits 3:2
    UINT32 Mux1_Control                            :  2;  // Bits 5:4
    UINT32                                         :  2;  // Bits 7:6
    UINT32 Mux2_Control                            :  2;  // Bits 9:8
    UINT32                                         :  6;  // Bits 15:10
    UINT32 Select_Mux0_Control                     :  2;  // Bits 17:16
    UINT32                                         :  2;  // Bits 19:18
    UINT32 Select_Mux1_Control                     :  2;  // Bits 21:20
    UINT32                                         :  2;  // Bits 23:22
    UINT32 Select_Mux2_Control                     :  2;  // Bits 25:24
    UINT32                                         :  2;  // Bits 27:26
    UINT32 LFSR_Type                               :  3;  // Bits 30:28
    UINT32 Chaining_LFSR                           :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCHBAR_CH1_CR_REUT_CH_PAT_CADB_MUX_CTRL_STRUCT;

typedef union {
  struct {
    UINT32 Pattern_Buffer                          :  24;  // Bits 23:0
    UINT32                                         :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCHBAR_CH1_CR_REUT_CH_PAT_CADB_MUX_PB_0_STRUCT;

typedef union {
  struct {
    UINT32 Pattern_Buffer                          :  24;  // Bits 23:0
    UINT32                                         :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCHBAR_CH1_CR_REUT_CH_PAT_CADB_MUX_PB_1_STRUCT;

typedef union {
  struct {
    UINT32 Pattern_Buffer                          :  24;  // Bits 23:0
    UINT32                                         :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCHBAR_CH1_CR_REUT_CH_PAT_CADB_MUX_PB_2_STRUCT;

typedef union {
  struct {
    UINT32 Pattern_Buffer                          :  24;  // Bits 23:0
    UINT32                                         :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCHBAR_CH1_CR_REUT_CH_PAT_CADB_SEL_MUX_PB_0_STRUCT;

typedef union {
  struct {
    UINT32 Pattern_Buffer                          :  24;  // Bits 23:0
    UINT32                                         :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCHBAR_CH1_CR_REUT_CH_PAT_CADB_SEL_MUX_PB_1_STRUCT;

typedef union {
  struct {
    UINT32 Pattern_Buffer                          :  24;  // Bits 23:0
    UINT32                                         :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCHBAR_CH1_CR_REUT_CH_PAT_CADB_SEL_MUX_PB_2_STRUCT;

typedef union {
  struct {
    UINT32 L_data_select                           :  1;  // Bits 0:0
    UINT32 Enable_Sweep_Frequency                  :  1;  // Bits 1:1
    UINT32                                         :  6;  // Bits 7:2
    UINT32 L_counter                               :  8;  // Bits 15:8
    UINT32 M_counter                               :  8;  // Bits 23:16
    UINT32 N_counter                               :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCHBAR_CH1_CR_REUT_CH_PAT_CADB_CL_MUX_LMN_STRUCT;

typedef union {
  struct {
    UINT32 CADB_Write_Pointer                      :  3;  // Bits 2:0
    UINT32                                         :  1;  // Bits 3:3
    UINT32 Write_Enable                            :  1;  // Bits 4:4
    UINT32                                         :  27;  // Bits 31:5
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCHBAR_CH1_CR_REUT_CH_PAT_CADB_WRITE_POINTER_STRUCT;

typedef union {
  struct {
    UINT32 CADB_Data_Address                       :  17;  // Bits 16:0
    UINT32                                         :  7;  // Bits 23:17
    UINT32 CADB_Data_Bank                          :  4;  // Bits 27:24
    UINT32                                         :  4;  // Bits 31:28
    UINT32 CADB_Data_CS                            :  4;  // Bits 35:32
    UINT32                                         :  4;  // Bits 39:36
    UINT32 CADB_Data_Control                       :  4;  // Bits 43:40
    UINT32                                         :  4;  // Bits 47:44
    UINT32 CADB_Data_ODT                           :  4;  // Bits 51:48
    UINT32                                         :  4;  // Bits 55:52
    UINT32 CADB_Data_CKE                           :  4;  // Bits 59:56
    UINT32                                         :  3;  // Bits 62:60
    UINT32 CADB_Data_Parity_inv                    :  1;  // Bits 63:63
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} MCHBAR_CH1_CR_REUT_CH_PAT_CADB_PROG_STRUCT;

typedef union {
  struct {
    UINT32 Loopcount_Limit                         :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCHBAR_CH1_CR_REUT_CH_PAT_CADB_MRS_LOOPCOUNT_LIMIT_STRUCT;

typedef union {
  struct {
    UINT32 WDB_Increment_Rate                      :  6;  // Bits 5:0
    UINT32 WDB_Increment_Scale                     :  1;  // Bits 6:6
    UINT32                                         :  1;  // Bits 7:7
    UINT32 WDB_Start_Pointer                       :  6;  // Bits 13:8
    UINT32                                         :  2;  // Bits 15:14
    UINT32 WDB_End_Pointer                         :  6;  // Bits 21:16
    UINT32                                         :  10;  // Bits 31:22
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCHBAR_CH1_CR_REUT_CH_PAT_WDB_CL_CTRL_STRUCT;

typedef union {
  struct {
    UINT32 Refresh_Rank_Mask                       :  4;  // Bits 3:0
    UINT32                                         :  4;  // Bits 7:4
    UINT32 RefZQ_En_Start_Test_Sync                :  1;  // Bits 8:8
    UINT32                                         :  22;  // Bits 30:9
    UINT32 Panic_Refresh_Only                      :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCHBAR_CH1_CR_REUT_CH_MISC_REFRESH_CTRL_STRUCT;

typedef union {
  struct {
    UINT32 ZQ_Rank_Mask                            :  4;  // Bits 3:0
    UINT32                                         :  27;  // Bits 30:4
    UINT32 Always_Do_ZQ                            :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCHBAR_CH1_CR_REUT_CH_MISC_ZQ_CTRL_STRUCT;

typedef union {
  struct {
    UINT32 Rank_0_width                            :  2;  // Bits 1:0
    UINT32 Rank_1_width                            :  2;  // Bits 3:2
    UINT32 Rank_2_width                            :  2;  // Bits 5:4
    UINT32 Rank_3_width                            :  2;  // Bits 7:6
    UINT32 MR4_PERIOD                              :  16;  // Bits 23:8
    UINT32 DDR4_TS_readout_en                      :  1;  // Bits 24:24
    UINT32                                         :  7;  // Bits 31:25
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCHBAR_CH1_CR_DDR_MR_PARAMS_STRUCT;

typedef union {
  struct {
    UINT32 Address                                 :  8;  // Bits 7:0
    UINT32 Data                                    :  8;  // Bits 15:8
    UINT32 Rank                                    :  2;  // Bits 17:16
    UINT32 Command                                 :  2;  // Bits 19:18
    UINT32 DRAM_mask                               :  9;  // Bits 28:20
    UINT32 Assume_idle                             :  1;  // Bits 29:29
    UINT32 DDR4_MA13                               :  1;  // Bits 30:30
    UINT32 Busy                                    :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCHBAR_CH1_CR_DDR_MR_COMMAND_STRUCT;

typedef union {
  struct {
    UINT32 Device_0                                :  8;  // Bits 7:0
    UINT32 Device_1                                :  8;  // Bits 15:8
    UINT32 Device_2                                :  8;  // Bits 23:16
    UINT32 Device_3                                :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCHBAR_CH1_CR_DDR_MR_RESULT_0_STRUCT;

typedef union {
  struct {
    UINT32 Device_4                                :  8;  // Bits 7:0
    UINT32 Device_5                                :  8;  // Bits 15:8
    UINT32 Device_6                                :  8;  // Bits 23:16
    UINT32 Device_7                                :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCHBAR_CH1_CR_DDR_MR_RESULT_1_STRUCT;

typedef union {
  struct {
    UINT32 Device_8                                :  8;  // Bits 7:0
    UINT32                                         :  24;  // Bits 31:8
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCHBAR_CH1_CR_DDR_MR_RESULT_2_STRUCT;

typedef union {
  struct {
    UINT32 Rank_0                                  :  3;  // Bits 2:0
    UINT32                                         :  5;  // Bits 7:3
    UINT32 Rank_1                                  :  3;  // Bits 10:8
    UINT32                                         :  5;  // Bits 15:11
    UINT32 Rank_2                                  :  3;  // Bits 18:16
    UINT32                                         :  5;  // Bits 23:19
    UINT32 Rank_3                                  :  3;  // Bits 26:24
    UINT32                                         :  5;  // Bits 31:27
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCHBAR_CH1_CR_LPDDR_MR4_RANK_TEMPERATURE_STRUCT;

typedef union {
  struct {
    UINT32 Rank_0                                  :  2;  // Bits 1:0
    UINT32                                         :  6;  // Bits 7:2
    UINT32 Rank_1                                  :  2;  // Bits 9:8
    UINT32                                         :  6;  // Bits 15:10
    UINT32 Rank_2                                  :  2;  // Bits 17:16
    UINT32                                         :  6;  // Bits 23:18
    UINT32 Rank_3                                  :  2;  // Bits 25:24
    UINT32                                         :  6;  // Bits 31:26
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCHBAR_CH1_CR_DDR4_MPR_RANK_TEMPERATURE_STRUCT;

typedef union {
  struct {
    UINT32 Bit_0                                   :  3;  // Bits 2:0
    UINT32                                         :  1;  // Bits 3:3
    UINT32 Bit_1                                   :  3;  // Bits 6:4
    UINT32                                         :  1;  // Bits 7:7
    UINT32 Bit_2                                   :  3;  // Bits 10:8
    UINT32                                         :  1;  // Bits 11:11
    UINT32 Bit_16                                  :  3;  // Bits 14:12
    UINT32                                         :  1;  // Bits 15:15
    UINT32 Bit_17                                  :  3;  // Bits 18:16
    UINT32                                         :  1;  // Bits 19:19
    UINT32 Bit_18                                  :  3;  // Bits 22:20
    UINT32                                         :  1;  // Bits 23:23
    UINT32 Byte_0                                  :  3;  // Bits 26:24
    UINT32                                         :  1;  // Bits 27:27
    UINT32 Byte_2                                  :  3;  // Bits 30:28
    UINT32                                         :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCHBAR_CH1_CR_DESWIZZLE_LOW_STRUCT;

typedef union {
  struct {
    UINT32 Bit_32                                  :  3;  // Bits 2:0
    UINT32                                         :  1;  // Bits 3:3
    UINT32 Bit_33                                  :  3;  // Bits 6:4
    UINT32                                         :  1;  // Bits 7:7
    UINT32 Bit_34                                  :  3;  // Bits 10:8
    UINT32                                         :  1;  // Bits 11:11
    UINT32 Bit_48                                  :  3;  // Bits 14:12
    UINT32                                         :  1;  // Bits 15:15
    UINT32 Bit_49                                  :  3;  // Bits 18:16
    UINT32                                         :  1;  // Bits 19:19
    UINT32 Bit_50                                  :  3;  // Bits 22:20
    UINT32                                         :  1;  // Bits 23:23
    UINT32 Byte_4                                  :  3;  // Bits 26:24
    UINT32                                         :  1;  // Bits 27:27
    UINT32 Byte_6                                  :  3;  // Bits 30:28
    UINT32                                         :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCHBAR_CH1_CR_DESWIZZLE_HIGH_STRUCT;

typedef union {
  struct {
    UINT32 OREF_RI                                 :  8;  // Bits 7:0
    UINT32 Refresh_HP_WM                           :  4;  // Bits 11:8
    UINT32 Refresh_panic_wm                        :  4;  // Bits 15:12
    UINT32                                         :  9;  // Bits 24:16
    UINT32 tREFIx9                                 :  7;  // Bits 31:25
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCHBAR_CH1_CR_TC_RFP_STRUCT;

typedef union {
  struct {
    UINT32 tREFI                                   :  16;  // Bits 15:0
    UINT32 tRFC                                    :  10;  // Bits 25:16
    UINT32                                         :  6;  // Bits 31:26
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCHBAR_CH1_CR_TC_RFTP_STRUCT;

typedef union {
  struct {
    UINT32 tXSDLL                                  :  12;  // Bits 11:0
    UINT32 tXS_offset                              :  4;  // Bits 15:12
    UINT32 tZQOPER                                 :  10;  // Bits 25:16
    UINT32 tMOD                                    :  5;  // Bits 30:26
    UINT32                                         :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCHBAR_CH1_CR_TC_SRFTP_STRUCT;

typedef union {
  struct {
    UINT32 Ref_Interval                            :  11;  // Bits 10:0
    UINT32 Ref_Stagger_En                          :  1;  // Bits 11:11
    UINT32 Ref_Stagger_Mode                        :  1;  // Bits 12:12
    UINT32 Disable_Stolen_Refresh                  :  1;  // Bits 13:13
    UINT32 En_Ref_Type_Display                     :  1;  // Bits 14:14
    UINT32                                         :  17;  // Bits 31:15
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCHBAR_CH1_CR_MC_REFRESH_STAGGER_STRUCT;

typedef union {
  struct {
    UINT32 ZQCS_period                             :  10;  // Bits 9:0
    UINT32 tZQCS                                   :  10;  // Bits 19:10
    UINT32                                         :  12;  // Bits 31:20
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCHBAR_CH1_CR_TC_ZQCAL_STRUCT;

typedef union {
  struct {
    UINT32 MR2_shaddow                             :  14;  // Bits 13:0
    UINT32 SRT_avail                               :  2;  // Bits 15:14
    UINT32                                         :  16;  // Bits 31:16
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCHBAR_CH1_CR_TC_MR2_SHADDOW_STRUCT;

typedef union {
  struct {
    UINT32 MR4_sh_low                              :  2;  // Bits 1:0
    UINT32                                         :  2;  // Bits 3:2
    UINT32 MR4_sh_high                             :  10;  // Bits 13:4
    UINT32                                         :  18;  // Bits 31:14
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCHBAR_CH1_CR_TC_MR4_SHADDOW_STRUCT;

typedef union {
  struct {
    UINT32 Rank_occupancy                          :  4;  // Bits 3:0
    UINT32 SRX_reset                               :  1;  // Bits 4:4
    UINT32                                         :  27;  // Bits 31:5
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCHBAR_CH1_CR_MC_INIT_STATE_STRUCT;

typedef union {
  struct {
    UINT32 VISAByteSel                             :  3;  // Bits 2:0
    UINT32                                         :  29;  // Bits 31:3
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCHBAR_CH1_CR_WDB_VISA_SEL_STRUCT;

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
} MCHBAR_CH1_CR_VISA_CTL_MCMNTS_STRUCT;

typedef union {
  struct {
    UINT32 DIMM0_IDLE_ENERGY                       :  6;  // Bits 5:0
    UINT32                                         :  2;  // Bits 7:6
    UINT32 DIMM1_IDLE_ENERGY                       :  6;  // Bits 13:8
    UINT32                                         :  18;  // Bits 31:14
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCHBAR_CH1_CR_PM_DIMM_IDLE_ENERGY_STRUCT;

typedef union {
  struct {
    UINT32 DIMM0_PD_ENERGY                         :  6;  // Bits 5:0
    UINT32                                         :  2;  // Bits 7:6
    UINT32 DIMM1_PD_ENERGY                         :  6;  // Bits 13:8
    UINT32                                         :  18;  // Bits 31:14
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCHBAR_CH1_CR_PM_DIMM_PD_ENERGY_STRUCT;

typedef union {
  struct {
    UINT32 DIMM0_ACT_ENERGY                        :  8;  // Bits 7:0
    UINT32 DIMM1_ACT_ENERGY                        :  8;  // Bits 15:8
    UINT32                                         :  16;  // Bits 31:16
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCHBAR_CH1_CR_PM_DIMM_ACT_ENERGY_STRUCT;

typedef union {
  struct {
    UINT32 DIMM0_RD_ENERGY                         :  8;  // Bits 7:0
    UINT32 DIMM1_RD_ENERGY                         :  8;  // Bits 15:8
    UINT32                                         :  16;  // Bits 31:16
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCHBAR_CH1_CR_PM_DIMM_RD_ENERGY_STRUCT;

typedef union {
  struct {
    UINT32 DIMM0_WR_ENERGY                         :  8;  // Bits 7:0
    UINT32 DIMM1_WR_ENERGY                         :  8;  // Bits 15:8
    UINT32                                         :  16;  // Bits 31:16
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCHBAR_CH1_CR_PM_DIMM_WR_ENERGY_STRUCT;

typedef union {
  struct {
    UINT32 Count                                   :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCHBAR_CH1_CR_ECC_INJECT_COUNT_STRUCT;

typedef union {
  struct {
    UINT32 D0R0                                    :  2;  // Bits 1:0
    UINT32 D0R1                                    :  2;  // Bits 3:2
    UINT32 D1R0                                    :  2;  // Bits 5:4
    UINT32 D1R1                                    :  2;  // Bits 7:6
    UINT32                                         :  23;  // Bits 30:8
    UINT32 Dec_WRD                                 :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCHBAR_CH1_CR_SC_WR_ADD_DELAY_STRUCT;

typedef union {
  struct {
    UINT32 ECC                                     :  8;  // Bits 7:0
    UINT32 RRD_DFT_Mode                            :  2;  // Bits 9:8
    UINT32 LFSR_Seed_Index                         :  5;  // Bits 14:10
    UINT32 Inversion_Mode                          :  1;  // Bits 15:15
    UINT32                                         :  16;  // Bits 31:16
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCHBAR_CH1_CR_READ_RETURN_DFT_STRUCT;

typedef union {
  struct {
    UINT32 FASTADDR                                :  12;  // Bits 11:0
    UINT32 RSVD                                    :  4;  // Bits 15:12
    UINT32 ADDREN                                  :  1;  // Bits 16:16
    UINT32 SEQEN                                   :  1;  // Bits 17:17
    UINT32 POL0                                    :  1;  // Bits 18:18
    UINT32 POL1                                    :  1;  // Bits 19:19
    UINT32 CMDA                                    :  4;  // Bits 23:20
    UINT32 CMDB                                    :  4;  // Bits 27:24
    UINT32 CMDDEL                                  :  4;  // Bits 31:28
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCHBAR_CH1_CR_DCLK_LDAT_PDAT_STRUCT;

typedef union {
  struct {
    UINT32 BANKSEL                                 :  4;  // Bits 3:0
    UINT32 ADDR_LIM                                :  1;  // Bits 4:4
    UINT32 ARRAYSEL                                :  5;  // Bits 9:5
    UINT32 CMP                                     :  1;  // Bits 10:10
    UINT32 REP                                     :  1;  // Bits 11:11
    UINT32 DWORD                                   :  4;  // Bits 15:12
    UINT32 MODE                                    :  2;  // Bits 17:16
    UINT32 MPMAP                                   :  4;  // Bits 21:18
    UINT32 RSVD                                    :  2;  // Bits 23:22
    UINT32 MPBOFFSET                               :  4;  // Bits 27:24
    UINT32 STAGE_EN                                :  1;  // Bits 28:28
    UINT32 SHADOW                                  :  2;  // Bits 30:29
    UINT32 RSVD1                                   :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCHBAR_CH1_CR_DCLK_LDAT_SDAT_STRUCT;

typedef union {
  struct {
    UINT32 DATOUT                                  :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCHBAR_CH1_CR_DCLK_LDAT_DATAOUT_STRUCT;

typedef union {
  struct {
    UINT32 DATIN                                   :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCHBAR_CH1_CR_DCLK_LDAT_DATAIN_0_STRUCT;

typedef union {
  struct {
    UINT32 FASTADDR                                :  12;  // Bits 11:0
    UINT32 RSVD                                    :  4;  // Bits 15:12
    UINT32 ADDREN                                  :  1;  // Bits 16:16
    UINT32 SEQEN                                   :  1;  // Bits 17:17
    UINT32 POL0                                    :  1;  // Bits 18:18
    UINT32 POL1                                    :  1;  // Bits 19:19
    UINT32 CMDA                                    :  4;  // Bits 23:20
    UINT32 CMDB                                    :  4;  // Bits 27:24
    UINT32 CMDDEL                                  :  4;  // Bits 31:28
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCHBAR_CH1_CR_QCLK_LDAT_PDAT_STRUCT;

typedef union {
  struct {
    UINT32 BANKSEL                                 :  4;  // Bits 3:0
    UINT32 ADDR_LIM                                :  1;  // Bits 4:4
    UINT32 ARRAYSEL                                :  5;  // Bits 9:5
    UINT32 CMP                                     :  1;  // Bits 10:10
    UINT32 REP                                     :  1;  // Bits 11:11
    UINT32 DWORD                                   :  4;  // Bits 15:12
    UINT32 MODE                                    :  2;  // Bits 17:16
    UINT32 MPMAP                                   :  4;  // Bits 21:18
    UINT32 RSVD                                    :  2;  // Bits 23:22
    UINT32 MPBOFFSET                               :  4;  // Bits 27:24
    UINT32 STAGE_EN                                :  1;  // Bits 28:28
    UINT32 SHADOW                                  :  2;  // Bits 30:29
    UINT32 RSVD1                                   :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCHBAR_CH1_CR_QCLK_LDAT_SDAT_STRUCT;

typedef union {
  struct {
    UINT32 DATOUT                                  :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCHBAR_CH1_CR_QCLK_LDAT_DATAOUT_STRUCT;

typedef union {
  struct {
    UINT32 DATIN                                   :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCHBAR_CH1_CR_QCLK_LDAT_DATAIN_0_STRUCT;

typedef union {
  struct {
    UINT32 DATIN                                   :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCHBAR_CH1_CR_QCLK_LDAT_DATAIN_1_STRUCT;

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
} MCHBAR_CH1_CR_VISA_SLIDE_MCMNTS_STRUCT;

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
} MCHBAR_CH1_CR_VISA_XBAR_MCMNTS_STRUCT;

typedef union {
  struct {
    UINT32 Count                                   :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCHBAR_CH1_CR_PM_ALL_RANKS_CKE_LOW_COUNT_STRUCT;

typedef union {
  struct {
    UINT32 Valid                                   :  1;  // Bits 0:0
    UINT32 Rank                                    :  2;  // Bits 2:1
    UINT32 Group                                   :  2;  // Bits 4:3
    UINT32 Bank                                    :  2;  // Bits 6:5
    UINT32 Row                                     :  17;  // Bits 23:7
    UINT32                                         :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCHBAR_CH1_CR_RH_ADDRESS_STRUCT;

typedef union {
  struct {
    UINT32 LFSR_0                                  :  32;  // Bits 31:0
    UINT32 LFSR_1                                  :  32;  // Bits 63:32
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} MCHBAR_CH1_CR_RH_LFSR_STRUCT;

typedef union {
  struct {
    UINT32 Mode                                    :  4;  // Bits 3:0
    UINT32 Always_block_rank                       :  1;  // Bits 4:4
    UINT32 Always_PREALL                           :  1;  // Bits 5:5
    UINT32 LFSR_0_MASK                             :  4;  // Bits 9:6
    UINT32 LFSR_1_MASK                             :  4;  // Bits 13:10
    UINT32 MA3_Swizzling                           :  2;  // Bits 15:14
    UINT32 TRR_wait_cycles                         :  6;  // Bits 21:16
    UINT32 Always_calc_victim_row                  :  1;  // Bits 22:22
    UINT32 MA0_Swizzling                           :  2;  // Bits 24:23
    UINT32                                         :  7;  // Bits 31:25
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCHBAR_CH1_CR_RH_CONTROL_STRUCT;

typedef union {
  struct {
    UINT32 Counter_Status                          :  23;  // Bits 22:0
    UINT32                                         :  9;  // Bits 31:23
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCHBAR_CH1_CR_REUT_CH_ERR_COUNTER_STATUS_0_STRUCT;

typedef union {
  struct {
    UINT32 Counter_Status                          :  23;  // Bits 22:0
    UINT32                                         :  9;  // Bits 31:23
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCHBAR_CH1_CR_REUT_CH_ERR_COUNTER_STATUS_1_STRUCT;

typedef union {
  struct {
    UINT32 Counter_Status                          :  23;  // Bits 22:0
    UINT32                                         :  9;  // Bits 31:23
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCHBAR_CH1_CR_REUT_CH_ERR_COUNTER_STATUS_2_STRUCT;

typedef union {
  struct {
    UINT32 Counter_Status                          :  23;  // Bits 22:0
    UINT32                                         :  9;  // Bits 31:23
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCHBAR_CH1_CR_REUT_CH_ERR_COUNTER_STATUS_3_STRUCT;

typedef union {
  struct {
    UINT32 Counter_Status                          :  23;  // Bits 22:0
    UINT32                                         :  9;  // Bits 31:23
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCHBAR_CH1_CR_REUT_CH_ERR_COUNTER_STATUS_4_STRUCT;

typedef union {
  struct {
    UINT32 Counter_Status                          :  23;  // Bits 22:0
    UINT32                                         :  9;  // Bits 31:23
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCHBAR_CH1_CR_REUT_CH_ERR_COUNTER_STATUS_5_STRUCT;

typedef union {
  struct {
    UINT32 Counter_Status                          :  23;  // Bits 22:0
    UINT32                                         :  9;  // Bits 31:23
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCHBAR_CH1_CR_REUT_CH_ERR_COUNTER_STATUS_6_STRUCT;

typedef union {
  struct {
    UINT32 Counter_Status                          :  23;  // Bits 22:0
    UINT32                                         :  9;  // Bits 31:23
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCHBAR_CH1_CR_REUT_CH_ERR_COUNTER_STATUS_7_STRUCT;

typedef union {
  struct {
    UINT32 Counter_Status                          :  23;  // Bits 22:0
    UINT32                                         :  9;  // Bits 31:23
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCHBAR_CH1_CR_REUT_CH_ERR_COUNTER_STATUS_8_STRUCT;

typedef union {
  struct {
    UINT32 Stop_on_Nth_Error                       :  6;  // Bits 5:0
    UINT32                                         :  2;  // Bits 7:6
    UINT32 Stop_on_CA_ALERT                        :  1;  // Bits 8:8
    UINT32                                         :  3;  // Bits 11:9
    UINT32 Stop_On_Error_Control                   :  2;  // Bits 13:12
    UINT32                                         :  2;  // Bits 15:14
    UINT32 Selective_Error_Enable_Chunk            :  8;  // Bits 23:16
    UINT32 Selective_Error_Enable_Cacheline        :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCHBAR_CH1_CR_REUT_CH_ERR_CTL_STRUCT;

typedef union {
  struct {
    UINT32 ECC_Error_Mask                          :  8;  // Bits 7:0
    UINT32                                         :  24;  // Bits 31:8
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCHBAR_CH1_CR_REUT_CH_ERR_ECC_MASK_STRUCT;

typedef union {
  struct {
    UINT32 Data_Error_MaskLow                      :  32;  // Bits 31:0
    UINT32 Data_Error_MaskHigh                     :  32;  // Bits 63:32
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} MCHBAR_CH1_CR_REUT_CH_ERR_DATA_MASK_STRUCT;

typedef union {
  struct {
    UINT32 Data_Error_StatusLow                    :  32;  // Bits 31:0
    UINT32 Data_Error_StatusHigh                   :  32;  // Bits 63:32
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} MCHBAR_CH1_CR_REUT_CH_ERR_DATA_STATUS_STRUCT;

typedef union {
  struct {
    UINT32 ECC_Error_Status                        :  8;  // Bits 7:0
    UINT32 Chunk_Error_Status                      :  8;  // Bits 15:8
    UINT32 Rank_Error_Status                       :  4;  // Bits 19:16
    UINT32 Alert_Error_Status                      :  1;  // Bits 20:20
    UINT32                                         :  11;  // Bits 31:21
    UINT32 Byte_Group_Error_Status                 :  9;  // Bits 40:32
    UINT32                                         :  11;  // Bits 51:41
    UINT32 WDB_Rd_Chunk_Num_Status                 :  3;  // Bits 54:52
    UINT32                                         :  1;  // Bits 55:55
    UINT32 Nth_Error                               :  6;  // Bits 61:56
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} MCHBAR_CH1_CR_REUT_CH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_STRUCT;

typedef union {
  struct {
    UINT32 Column_Address                          :  11;  // Bits 10:0
    UINT32                                         :  13;  // Bits 23:11
    UINT32 Row_AddressLow                          :  8;  // Bits 31:24
    UINT32 Row_AddressHigh                         :  9;  // Bits 40:32
    UINT32                                         :  7;  // Bits 47:41
    UINT32 Bank_Address                            :  4;  // Bits 51:48
    UINT32                                         :  4;  // Bits 55:52
    UINT32 Rank_Address                            :  2;  // Bits 57:56
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} MCHBAR_CH1_CR_REUT_CH_ERROR_ADDR_STRUCT;

typedef union {
  struct {
    UINT32 Enable_WDB_Capture                      :  1;  // Bits 0:0
    UINT32 WDB_Error_Sel_Capture                   :  1;  // Bits 1:1
    UINT32 WDB_Data_Sel_Capture                    :  1;  // Bits 2:2
    UINT32                                         :  5;  // Bits 7:3
    UINT32 WDB_Starting_Capture_Pointer            :  6;  // Bits 13:8
    UINT32                                         :  2;  // Bits 15:14
    UINT32 WDB_Ending_Capture_Pointer              :  6;  // Bits 21:16
    UINT32                                         :  10;  // Bits 31:22
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCHBAR_CH1_CR_REUT_CH_WDB_CAPTURE_CTL_STRUCT;

typedef union {
  struct {
    UINT32 WDB_Current_Capture_Pointer             :  6;  // Bits 5:0
    UINT32                                         :  26;  // Bits 31:6
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCHBAR_CH1_CR_REUT_CH_WDB_CAPTURE_STATUS_STRUCT;

typedef union {
  struct {
    UINT32 Counter_Pointer                         :  7;  // Bits 6:0
    UINT32 Counter_Control                         :  2;  // Bits 8:7
    UINT32                                         :  23;  // Bits 31:9
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCHBAR_CH1_CR_REUT_CH_ERR_COUNTER_CTL_0_STRUCT;

typedef union {
  struct {
    UINT32 Counter_Pointer                         :  7;  // Bits 6:0
    UINT32 Counter_Control                         :  2;  // Bits 8:7
    UINT32                                         :  23;  // Bits 31:9
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCHBAR_CH1_CR_REUT_CH_ERR_COUNTER_CTL_1_STRUCT;

typedef union {
  struct {
    UINT32 Counter_Pointer                         :  7;  // Bits 6:0
    UINT32 Counter_Control                         :  2;  // Bits 8:7
    UINT32                                         :  23;  // Bits 31:9
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCHBAR_CH1_CR_REUT_CH_ERR_COUNTER_CTL_2_STRUCT;

typedef union {
  struct {
    UINT32 Counter_Pointer                         :  7;  // Bits 6:0
    UINT32 Counter_Control                         :  2;  // Bits 8:7
    UINT32                                         :  23;  // Bits 31:9
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCHBAR_CH1_CR_REUT_CH_ERR_COUNTER_CTL_3_STRUCT;

typedef union {
  struct {
    UINT32 Counter_Pointer                         :  7;  // Bits 6:0
    UINT32 Counter_Control                         :  2;  // Bits 8:7
    UINT32                                         :  23;  // Bits 31:9
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCHBAR_CH1_CR_REUT_CH_ERR_COUNTER_CTL_4_STRUCT;

typedef union {
  struct {
    UINT32 Counter_Pointer                         :  7;  // Bits 6:0
    UINT32 Counter_Control                         :  2;  // Bits 8:7
    UINT32                                         :  23;  // Bits 31:9
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCHBAR_CH1_CR_REUT_CH_ERR_COUNTER_CTL_5_STRUCT;

typedef union {
  struct {
    UINT32 Counter_Pointer                         :  7;  // Bits 6:0
    UINT32 Counter_Control                         :  2;  // Bits 8:7
    UINT32                                         :  23;  // Bits 31:9
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCHBAR_CH1_CR_REUT_CH_ERR_COUNTER_CTL_6_STRUCT;

typedef union {
  struct {
    UINT32 Counter_Pointer                         :  7;  // Bits 6:0
    UINT32 Counter_Control                         :  2;  // Bits 8:7
    UINT32                                         :  23;  // Bits 31:9
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCHBAR_CH1_CR_REUT_CH_ERR_COUNTER_CTL_7_STRUCT;

typedef union {
  struct {
    UINT32 Counter_Pointer                         :  7;  // Bits 6:0
    UINT32 Counter_Control                         :  2;  // Bits 8:7
    UINT32                                         :  23;  // Bits 31:9
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCHBAR_CH1_CR_REUT_CH_ERR_COUNTER_CTL_8_STRUCT;

typedef union {
  struct {
    UINT32 Counter_Overflow_Status                 :  9;  // Bits 8:0
    UINT32                                         :  23;  // Bits 31:9
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCHBAR_CH1_CR_REUT_CH_ERR_COUNTER_OVERFLOW_STATUS_STRUCT;

typedef union {
  struct {
    UINT32 WDB_Current_Read_Pointer                :  6;  // Bits 5:0
    UINT32                                         :  26;  // Bits 31:6
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCHBAR_CH1_CR_REUT_CH_PAT_WDB_CL_RD_STATUS_STRUCT;

typedef union {
  struct {
    UINT32 MR0                                     :  14;  // Bits 13:0
    UINT32                                         :  2;  // Bits 15:14
    UINT32 MR1                                     :  14;  // Bits 29:16
    UINT32                                         :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCHBAR_CH1_CR_DDR4_MR0_MR1_CONTENT_STRUCT;

typedef union {
  struct {
    UINT32 MR2                                     :  14;  // Bits 13:0
    UINT32                                         :  2;  // Bits 15:14
    UINT32 MR3                                     :  14;  // Bits 29:16
    UINT32                                         :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCHBAR_CH1_CR_DDR4_MR2_MR3_CONTENT_STRUCT;

typedef union {
  struct {
    UINT32 MR4                                     :  14;  // Bits 13:0
    UINT32                                         :  2;  // Bits 15:14
    UINT32 MR5                                     :  14;  // Bits 29:16
    UINT32                                         :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCHBAR_CH1_CR_DDR4_MR4_MR5_CONTENT_STRUCT;

typedef union {
  struct {
    UINT32 MR6                                     :  14;  // Bits 13:0
    UINT32                                         :  2;  // Bits 15:14
    UINT32 MR7                                     :  14;  // Bits 29:16
    UINT32                                         :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCHBAR_CH1_CR_DDR4_MR6_MR7_CONTENT_STRUCT;

typedef union {
  struct {
    UINT32 Rank0_Byte0                             :  2;  // Bits 1:0
    UINT32 Rank0_Byte1                             :  2;  // Bits 3:2
    UINT32 Rank0_Byte2                             :  2;  // Bits 5:4
    UINT32 Rank0_Byte3                             :  2;  // Bits 7:6
    UINT32 Rank0_Byte4                             :  2;  // Bits 9:8
    UINT32 Rank0_Byte5                             :  2;  // Bits 11:10
    UINT32 Rank0_Byte6                             :  2;  // Bits 13:12
    UINT32 Rank0_Byte7                             :  2;  // Bits 15:14
    UINT32 Rank1_Byte0                             :  2;  // Bits 17:16
    UINT32 Rank1_Byte1                             :  2;  // Bits 19:18
    UINT32 Rank1_Byte2                             :  2;  // Bits 21:20
    UINT32 Rank1_Byte3                             :  2;  // Bits 23:22
    UINT32 Rank1_Byte4                             :  2;  // Bits 25:24
    UINT32 Rank1_Byte5                             :  2;  // Bits 27:26
    UINT32 Rank1_Byte6                             :  2;  // Bits 29:28
    UINT32 Rank1_Byte7                             :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCHBAR_CH1_CR_DDR4_MR1_ODIC_VALUES_STRUCT;

typedef union {
  struct {
    UINT32 Rank0_Byte0                             :  2;  // Bits 1:0
    UINT32 Rank0_Byte1                             :  2;  // Bits 3:2
    UINT32 Rank0_Byte2                             :  2;  // Bits 5:4
    UINT32 Rank0_Byte3                             :  2;  // Bits 7:6
    UINT32 Rank0_Byte4                             :  2;  // Bits 9:8
    UINT32 Rank0_Byte5                             :  2;  // Bits 11:10
    UINT32 Rank0_Byte6                             :  2;  // Bits 13:12
    UINT32 Rank0_Byte7                             :  2;  // Bits 15:14
    UINT32 Rank1_Byte0                             :  2;  // Bits 17:16
    UINT32 Rank1_Byte1                             :  2;  // Bits 19:18
    UINT32 Rank1_Byte2                             :  2;  // Bits 21:20
    UINT32 Rank1_Byte3                             :  2;  // Bits 23:22
    UINT32 Rank1_Byte4                             :  2;  // Bits 25:24
    UINT32 Rank1_Byte5                             :  2;  // Bits 27:26
    UINT32 Rank1_Byte6                             :  2;  // Bits 29:28
    UINT32 Rank1_Byte7                             :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCHBAR_CH1_CR_DDR4_MR2_RTT_WR_VALUES_STRUCT;

typedef union {
  struct {
    UINT32 Byte0                                   :  7;  // Bits 6:0
    UINT32                                         :  1;  // Bits 7:7
    UINT32 Byte1                                   :  7;  // Bits 14:8
    UINT32                                         :  1;  // Bits 15:15
    UINT32 Byte2                                   :  7;  // Bits 22:16
    UINT32                                         :  1;  // Bits 23:23
    UINT32 Byte3                                   :  7;  // Bits 30:24
    UINT32                                         :  1;  // Bits 31:31
    UINT32 Byte4                                   :  7;  // Bits 38:32
    UINT32                                         :  1;  // Bits 39:39
    UINT32 Byte5                                   :  7;  // Bits 46:40
    UINT32                                         :  1;  // Bits 47:47
    UINT32 Byte6                                   :  7;  // Bits 54:48
    UINT32                                         :  1;  // Bits 55:55
    UINT32 Byte7                                   :  7;  // Bits 62:56
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} MCHBAR_CH1_CR_DDR4_MR6_VREF_VALUES_0_STRUCT;

typedef union {
  struct {
    UINT32 Byte0                                   :  7;  // Bits 6:0
    UINT32                                         :  1;  // Bits 7:7
    UINT32 Byte1                                   :  7;  // Bits 14:8
    UINT32                                         :  1;  // Bits 15:15
    UINT32 Byte2                                   :  7;  // Bits 22:16
    UINT32                                         :  1;  // Bits 23:23
    UINT32 Byte3                                   :  7;  // Bits 30:24
    UINT32                                         :  1;  // Bits 31:31
    UINT32 Byte4                                   :  7;  // Bits 38:32
    UINT32                                         :  1;  // Bits 39:39
    UINT32 Byte5                                   :  7;  // Bits 46:40
    UINT32                                         :  1;  // Bits 47:47
    UINT32 Byte6                                   :  7;  // Bits 54:48
    UINT32                                         :  1;  // Bits 55:55
    UINT32 Byte7                                   :  7;  // Bits 62:56
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} MCHBAR_CH1_CR_DDR4_MR6_VREF_VALUES_1_STRUCT;

typedef union {
  struct {
    UINT32 MR1                                     :  8;  // Bits 7:0
    UINT32 MR2                                     :  8;  // Bits 15:8
    UINT32 MR3                                     :  8;  // Bits 23:16
    UINT32 MR11                                    :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCHBAR_CH1_CR_LPDDR3_MR_CONTENT_STRUCT;

typedef union {
  struct {
    UINT32 DDR4_Restore_MR                         :  8;  // Bits 7:0
    UINT32 DDR4_Restore_MR1_Per_Device             :  1;  // Bits 8:8
    UINT32 DDR4_Restore_MR2_Per_Device             :  1;  // Bits 9:9
    UINT32 DDR4_Restore_MR6_Per_Device             :  1;  // Bits 10:10
    UINT32                                         :  5;  // Bits 15:11
    UINT32 LPDDR3_Restore_MR                       :  4;  // Bits 19:16
    UINT32 do_ZQCL                                 :  1;  // Bits 20:20
    UINT32 zero_rank1_MR11                         :  1;  // Bits 21:21
    UINT32 vref_time_per_byte                      :  1;  // Bits 22:22
    UINT32                                         :  1;  // Bits 23:23
    UINT32 tVREFDQ                                 :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCHBAR_CH1_CR_MRS_FSM_CONTROL_STRUCT;

typedef union {
  struct {
    UINT32 Run                                     :  1;  // Bits 0:0
    UINT32                                         :  31;  // Bits 31:1
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCHBAR_CH1_CR_MRS_FSM_RUN_STRUCT;

typedef union {
  struct {
    UINT32 Spare_RW                                :  8;  // Bits 7:0
    UINT32 ForceX2Ref                              :  1;  // Bits 8:8
    UINT32 ForceX4Ref                              :  1;  // Bits 9:9
    UINT32 ForceTxAnalog                           :  1;  // Bits 10:10
    UINT32 TxAnalog_grace                          :  4;  // Bits 14:11
    UINT32 DisSREXcnt                              :  1;  // Bits 15:15
    UINT32 Spare_RW_V                              :  16;  // Bits 31:16
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCHBAR_CH1_CR_MCMNTS_SPARE_STRUCT;

typedef union {
  struct {
    UINT32 Global_Start_Test                       :  1;  // Bits 0:0
    UINT32 Global_Stop_Test                        :  1;  // Bits 1:1
    UINT32 Global_Clear_Errors                     :  1;  // Bits 2:2
    UINT32                                         :  1;  // Bits 3:3
    UINT32 Global_Stop_Test_On_Any_Error           :  1;  // Bits 4:4
    UINT32                                         :  27;  // Bits 31:5
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCDFXS_CR_REUT_GLOBAL_CTL_MCMAIN_STRUCT;

typedef union {
  struct {
    UINT32 Channel_Error_Status_0                  :  1;  // Bits 0:0
    UINT32 Channel_Error_Status_1                  :  1;  // Bits 1:1
    UINT32                                         :  14;  // Bits 15:2
    UINT32 Channel_Test_Done_Status_0              :  1;  // Bits 16:16
    UINT32 Channel_Test_Done_Status_1              :  1;  // Bits 17:17
    UINT32                                         :  14;  // Bits 31:18
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCDFXS_CR_REUT_GLOBAL_ERR_MCMAIN_STRUCT;

typedef union {
  struct {
    UINT32 Number_of_Cachelines                    :  7;  // Bits 6:0
    UINT32 Number_of_Cachelines_Scale              :  1;  // Bits 7:7
    UINT32 Subsequence_Wait                        :  14;  // Bits 21:8
    UINT32 Subsequence_Type                        :  4;  // Bits 25:22
    UINT32 Save_Current_Base_Address_To_Start      :  1;  // Bits 26:26
    UINT32 Reset_Current_Base_Address_To_Start     :  1;  // Bits 27:27
    UINT32 Data_and_ECC_Address_Inversion          :  2;  // Bits 29:28
    UINT32 Invert_Data_and_ECC                     :  1;  // Bits 30:30
    UINT32 Stop_Base_Subsequence_On_Wrap_Trigger   :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCDFXS_CR_REUT_CH0_SUBSEQ_CTL_MCMAIN_0_STRUCT;

typedef union {
  struct {
    UINT32 Number_of_Cachelines                    :  7;  // Bits 6:0
    UINT32 Number_of_Cachelines_Scale              :  1;  // Bits 7:7
    UINT32 Subsequence_Wait                        :  14;  // Bits 21:8
    UINT32 Subsequence_Type                        :  4;  // Bits 25:22
    UINT32 Save_Current_Base_Address_To_Start      :  1;  // Bits 26:26
    UINT32 Reset_Current_Base_Address_To_Start     :  1;  // Bits 27:27
    UINT32 Data_and_ECC_Address_Inversion          :  2;  // Bits 29:28
    UINT32 Invert_Data_and_ECC                     :  1;  // Bits 30:30
    UINT32 Stop_Base_Subsequence_On_Wrap_Trigger   :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCDFXS_CR_REUT_CH0_SUBSEQ_CTL_MCMAIN_1_STRUCT;

typedef union {
  struct {
    UINT32 Number_of_Cachelines                    :  7;  // Bits 6:0
    UINT32 Number_of_Cachelines_Scale              :  1;  // Bits 7:7
    UINT32 Subsequence_Wait                        :  14;  // Bits 21:8
    UINT32 Subsequence_Type                        :  4;  // Bits 25:22
    UINT32 Save_Current_Base_Address_To_Start      :  1;  // Bits 26:26
    UINT32 Reset_Current_Base_Address_To_Start     :  1;  // Bits 27:27
    UINT32 Data_and_ECC_Address_Inversion          :  2;  // Bits 29:28
    UINT32 Invert_Data_and_ECC                     :  1;  // Bits 30:30
    UINT32 Stop_Base_Subsequence_On_Wrap_Trigger   :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCDFXS_CR_REUT_CH0_SUBSEQ_CTL_MCMAIN_2_STRUCT;

typedef union {
  struct {
    UINT32 Number_of_Cachelines                    :  7;  // Bits 6:0
    UINT32 Number_of_Cachelines_Scale              :  1;  // Bits 7:7
    UINT32 Subsequence_Wait                        :  14;  // Bits 21:8
    UINT32 Subsequence_Type                        :  4;  // Bits 25:22
    UINT32 Save_Current_Base_Address_To_Start      :  1;  // Bits 26:26
    UINT32 Reset_Current_Base_Address_To_Start     :  1;  // Bits 27:27
    UINT32 Data_and_ECC_Address_Inversion          :  2;  // Bits 29:28
    UINT32 Invert_Data_and_ECC                     :  1;  // Bits 30:30
    UINT32 Stop_Base_Subsequence_On_Wrap_Trigger   :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCDFXS_CR_REUT_CH0_SUBSEQ_CTL_MCMAIN_3_STRUCT;

typedef union {
  struct {
    UINT32 Number_of_Cachelines                    :  7;  // Bits 6:0
    UINT32 Number_of_Cachelines_Scale              :  1;  // Bits 7:7
    UINT32 Subsequence_Wait                        :  14;  // Bits 21:8
    UINT32 Subsequence_Type                        :  4;  // Bits 25:22
    UINT32 Save_Current_Base_Address_To_Start      :  1;  // Bits 26:26
    UINT32 Reset_Current_Base_Address_To_Start     :  1;  // Bits 27:27
    UINT32 Data_and_ECC_Address_Inversion          :  2;  // Bits 29:28
    UINT32 Invert_Data_and_ECC                     :  1;  // Bits 30:30
    UINT32 Stop_Base_Subsequence_On_Wrap_Trigger   :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCDFXS_CR_REUT_CH0_SUBSEQ_CTL_MCMAIN_4_STRUCT;

typedef union {
  struct {
    UINT32 Number_of_Cachelines                    :  7;  // Bits 6:0
    UINT32 Number_of_Cachelines_Scale              :  1;  // Bits 7:7
    UINT32 Subsequence_Wait                        :  14;  // Bits 21:8
    UINT32 Subsequence_Type                        :  4;  // Bits 25:22
    UINT32 Save_Current_Base_Address_To_Start      :  1;  // Bits 26:26
    UINT32 Reset_Current_Base_Address_To_Start     :  1;  // Bits 27:27
    UINT32 Data_and_ECC_Address_Inversion          :  2;  // Bits 29:28
    UINT32 Invert_Data_and_ECC                     :  1;  // Bits 30:30
    UINT32 Stop_Base_Subsequence_On_Wrap_Trigger   :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCDFXS_CR_REUT_CH0_SUBSEQ_CTL_MCMAIN_5_STRUCT;

typedef union {
  struct {
    UINT32 Number_of_Cachelines                    :  7;  // Bits 6:0
    UINT32 Number_of_Cachelines_Scale              :  1;  // Bits 7:7
    UINT32 Subsequence_Wait                        :  14;  // Bits 21:8
    UINT32 Subsequence_Type                        :  4;  // Bits 25:22
    UINT32 Save_Current_Base_Address_To_Start      :  1;  // Bits 26:26
    UINT32 Reset_Current_Base_Address_To_Start     :  1;  // Bits 27:27
    UINT32 Data_and_ECC_Address_Inversion          :  2;  // Bits 29:28
    UINT32 Invert_Data_and_ECC                     :  1;  // Bits 30:30
    UINT32 Stop_Base_Subsequence_On_Wrap_Trigger   :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCDFXS_CR_REUT_CH0_SUBSEQ_CTL_MCMAIN_6_STRUCT;

typedef union {
  struct {
    UINT32 Number_of_Cachelines                    :  7;  // Bits 6:0
    UINT32 Number_of_Cachelines_Scale              :  1;  // Bits 7:7
    UINT32 Subsequence_Wait                        :  14;  // Bits 21:8
    UINT32 Subsequence_Type                        :  4;  // Bits 25:22
    UINT32 Save_Current_Base_Address_To_Start      :  1;  // Bits 26:26
    UINT32 Reset_Current_Base_Address_To_Start     :  1;  // Bits 27:27
    UINT32 Data_and_ECC_Address_Inversion          :  2;  // Bits 29:28
    UINT32 Invert_Data_and_ECC                     :  1;  // Bits 30:30
    UINT32 Stop_Base_Subsequence_On_Wrap_Trigger   :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCDFXS_CR_REUT_CH0_SUBSEQ_CTL_MCMAIN_7_STRUCT;

typedef union {
  struct {
    UINT32 Number_of_Cachelines                    :  7;  // Bits 6:0
    UINT32 Number_of_Cachelines_Scale              :  1;  // Bits 7:7
    UINT32 Subsequence_Wait                        :  14;  // Bits 21:8
    UINT32 Subsequence_Type                        :  4;  // Bits 25:22
    UINT32 Save_Current_Base_Address_To_Start      :  1;  // Bits 26:26
    UINT32 Reset_Current_Base_Address_To_Start     :  1;  // Bits 27:27
    UINT32 Data_and_ECC_Address_Inversion          :  2;  // Bits 29:28
    UINT32 Invert_Data_and_ECC                     :  1;  // Bits 30:30
    UINT32 Stop_Base_Subsequence_On_Wrap_Trigger   :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCDFXS_CR_REUT_CH1_SUBSEQ_CTL_MCMAIN_0_STRUCT;

typedef union {
  struct {
    UINT32 Number_of_Cachelines                    :  7;  // Bits 6:0
    UINT32 Number_of_Cachelines_Scale              :  1;  // Bits 7:7
    UINT32 Subsequence_Wait                        :  14;  // Bits 21:8
    UINT32 Subsequence_Type                        :  4;  // Bits 25:22
    UINT32 Save_Current_Base_Address_To_Start      :  1;  // Bits 26:26
    UINT32 Reset_Current_Base_Address_To_Start     :  1;  // Bits 27:27
    UINT32 Data_and_ECC_Address_Inversion          :  2;  // Bits 29:28
    UINT32 Invert_Data_and_ECC                     :  1;  // Bits 30:30
    UINT32 Stop_Base_Subsequence_On_Wrap_Trigger   :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCDFXS_CR_REUT_CH1_SUBSEQ_CTL_MCMAIN_1_STRUCT;

typedef union {
  struct {
    UINT32 Number_of_Cachelines                    :  7;  // Bits 6:0
    UINT32 Number_of_Cachelines_Scale              :  1;  // Bits 7:7
    UINT32 Subsequence_Wait                        :  14;  // Bits 21:8
    UINT32 Subsequence_Type                        :  4;  // Bits 25:22
    UINT32 Save_Current_Base_Address_To_Start      :  1;  // Bits 26:26
    UINT32 Reset_Current_Base_Address_To_Start     :  1;  // Bits 27:27
    UINT32 Data_and_ECC_Address_Inversion          :  2;  // Bits 29:28
    UINT32 Invert_Data_and_ECC                     :  1;  // Bits 30:30
    UINT32 Stop_Base_Subsequence_On_Wrap_Trigger   :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCDFXS_CR_REUT_CH1_SUBSEQ_CTL_MCMAIN_2_STRUCT;

typedef union {
  struct {
    UINT32 Number_of_Cachelines                    :  7;  // Bits 6:0
    UINT32 Number_of_Cachelines_Scale              :  1;  // Bits 7:7
    UINT32 Subsequence_Wait                        :  14;  // Bits 21:8
    UINT32 Subsequence_Type                        :  4;  // Bits 25:22
    UINT32 Save_Current_Base_Address_To_Start      :  1;  // Bits 26:26
    UINT32 Reset_Current_Base_Address_To_Start     :  1;  // Bits 27:27
    UINT32 Data_and_ECC_Address_Inversion          :  2;  // Bits 29:28
    UINT32 Invert_Data_and_ECC                     :  1;  // Bits 30:30
    UINT32 Stop_Base_Subsequence_On_Wrap_Trigger   :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCDFXS_CR_REUT_CH1_SUBSEQ_CTL_MCMAIN_3_STRUCT;

typedef union {
  struct {
    UINT32 Number_of_Cachelines                    :  7;  // Bits 6:0
    UINT32 Number_of_Cachelines_Scale              :  1;  // Bits 7:7
    UINT32 Subsequence_Wait                        :  14;  // Bits 21:8
    UINT32 Subsequence_Type                        :  4;  // Bits 25:22
    UINT32 Save_Current_Base_Address_To_Start      :  1;  // Bits 26:26
    UINT32 Reset_Current_Base_Address_To_Start     :  1;  // Bits 27:27
    UINT32 Data_and_ECC_Address_Inversion          :  2;  // Bits 29:28
    UINT32 Invert_Data_and_ECC                     :  1;  // Bits 30:30
    UINT32 Stop_Base_Subsequence_On_Wrap_Trigger   :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCDFXS_CR_REUT_CH1_SUBSEQ_CTL_MCMAIN_4_STRUCT;

typedef union {
  struct {
    UINT32 Number_of_Cachelines                    :  7;  // Bits 6:0
    UINT32 Number_of_Cachelines_Scale              :  1;  // Bits 7:7
    UINT32 Subsequence_Wait                        :  14;  // Bits 21:8
    UINT32 Subsequence_Type                        :  4;  // Bits 25:22
    UINT32 Save_Current_Base_Address_To_Start      :  1;  // Bits 26:26
    UINT32 Reset_Current_Base_Address_To_Start     :  1;  // Bits 27:27
    UINT32 Data_and_ECC_Address_Inversion          :  2;  // Bits 29:28
    UINT32 Invert_Data_and_ECC                     :  1;  // Bits 30:30
    UINT32 Stop_Base_Subsequence_On_Wrap_Trigger   :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCDFXS_CR_REUT_CH1_SUBSEQ_CTL_MCMAIN_5_STRUCT;

typedef union {
  struct {
    UINT32 Number_of_Cachelines                    :  7;  // Bits 6:0
    UINT32 Number_of_Cachelines_Scale              :  1;  // Bits 7:7
    UINT32 Subsequence_Wait                        :  14;  // Bits 21:8
    UINT32 Subsequence_Type                        :  4;  // Bits 25:22
    UINT32 Save_Current_Base_Address_To_Start      :  1;  // Bits 26:26
    UINT32 Reset_Current_Base_Address_To_Start     :  1;  // Bits 27:27
    UINT32 Data_and_ECC_Address_Inversion          :  2;  // Bits 29:28
    UINT32 Invert_Data_and_ECC                     :  1;  // Bits 30:30
    UINT32 Stop_Base_Subsequence_On_Wrap_Trigger   :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCDFXS_CR_REUT_CH1_SUBSEQ_CTL_MCMAIN_6_STRUCT;

typedef union {
  struct {
    UINT32 Number_of_Cachelines                    :  7;  // Bits 6:0
    UINT32 Number_of_Cachelines_Scale              :  1;  // Bits 7:7
    UINT32 Subsequence_Wait                        :  14;  // Bits 21:8
    UINT32 Subsequence_Type                        :  4;  // Bits 25:22
    UINT32 Save_Current_Base_Address_To_Start      :  1;  // Bits 26:26
    UINT32 Reset_Current_Base_Address_To_Start     :  1;  // Bits 27:27
    UINT32 Data_and_ECC_Address_Inversion          :  2;  // Bits 29:28
    UINT32 Invert_Data_and_ECC                     :  1;  // Bits 30:30
    UINT32 Stop_Base_Subsequence_On_Wrap_Trigger   :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCDFXS_CR_REUT_CH1_SUBSEQ_CTL_MCMAIN_7_STRUCT;

typedef union {
  struct {
    UINT32 Offset_Address_Update_Rate              :  5;  // Bits 4:0
    UINT32                                         :  3;  // Bits 7:5
    UINT32 Base_Subsequence_Repeat_Rate            :  5;  // Bits 12:8
    UINT32                                         :  2;  // Bits 14:13
    UINT32 Column_Offset_Wrap_Trigger_Enable       :  1;  // Bits 15:15
    UINT32 Row_Offset_Wrap_Trigger_Enable          :  1;  // Bits 16:16
    UINT32                                         :  3;  // Bits 19:17
    UINT32 Base_Subsequence_Type                   :  1;  // Bits 20:20
    UINT32 CADB_Deselect_Enable                    :  1;  // Bits 21:21
    UINT32 CADB_Select_Enable                      :  1;  // Bits 22:22
    UINT32 CADB_Seeds_Save_Enable                  :  1;  // Bits 23:23
    UINT32 Column_Increment_Order                  :  1;  // Bits 24:24
    UINT32 CADB_Seeds_Reload_Enable                :  1;  // Bits 25:25
    UINT32 Column_Increment_Enable                 :  1;  // Bits 26:26
    UINT32 Row_Increment_Order                     :  1;  // Bits 27:27
    UINT32                                         :  1;  // Bits 28:28
    UINT32 Row_Increment_Enable                    :  1;  // Bits 29:29
    UINT32 Base_Invert_Data_and_ECC                :  1;  // Bits 30:30
    UINT32                                         :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCDFXS_CR_REUT_CH0_SUBSEQ_OFFSET_CTL_MCMAIN_0_STRUCT;

typedef union {
  struct {
    UINT32 Offset_Address_Update_Rate              :  5;  // Bits 4:0
    UINT32                                         :  3;  // Bits 7:5
    UINT32 Base_Subsequence_Repeat_Rate            :  5;  // Bits 12:8
    UINT32                                         :  2;  // Bits 14:13
    UINT32 Column_Offset_Wrap_Trigger_Enable       :  1;  // Bits 15:15
    UINT32 Row_Offset_Wrap_Trigger_Enable          :  1;  // Bits 16:16
    UINT32                                         :  3;  // Bits 19:17
    UINT32 Base_Subsequence_Type                   :  1;  // Bits 20:20
    UINT32 CADB_Deselect_Enable                    :  1;  // Bits 21:21
    UINT32 CADB_Select_Enable                      :  1;  // Bits 22:22
    UINT32 CADB_Seeds_Save_Enable                  :  1;  // Bits 23:23
    UINT32 Column_Increment_Order                  :  1;  // Bits 24:24
    UINT32 CADB_Seeds_Reload_Enable                :  1;  // Bits 25:25
    UINT32 Column_Increment_Enable                 :  1;  // Bits 26:26
    UINT32 Row_Increment_Order                     :  1;  // Bits 27:27
    UINT32                                         :  1;  // Bits 28:28
    UINT32 Row_Increment_Enable                    :  1;  // Bits 29:29
    UINT32 Base_Invert_Data_and_ECC                :  1;  // Bits 30:30
    UINT32                                         :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCDFXS_CR_REUT_CH0_SUBSEQ_OFFSET_CTL_MCMAIN_1_STRUCT;

typedef union {
  struct {
    UINT32 Offset_Address_Update_Rate              :  5;  // Bits 4:0
    UINT32                                         :  3;  // Bits 7:5
    UINT32 Base_Subsequence_Repeat_Rate            :  5;  // Bits 12:8
    UINT32                                         :  2;  // Bits 14:13
    UINT32 Column_Offset_Wrap_Trigger_Enable       :  1;  // Bits 15:15
    UINT32 Row_Offset_Wrap_Trigger_Enable          :  1;  // Bits 16:16
    UINT32                                         :  3;  // Bits 19:17
    UINT32 Base_Subsequence_Type                   :  1;  // Bits 20:20
    UINT32 CADB_Deselect_Enable                    :  1;  // Bits 21:21
    UINT32 CADB_Select_Enable                      :  1;  // Bits 22:22
    UINT32 CADB_Seeds_Save_Enable                  :  1;  // Bits 23:23
    UINT32 Column_Increment_Order                  :  1;  // Bits 24:24
    UINT32 CADB_Seeds_Reload_Enable                :  1;  // Bits 25:25
    UINT32 Column_Increment_Enable                 :  1;  // Bits 26:26
    UINT32 Row_Increment_Order                     :  1;  // Bits 27:27
    UINT32                                         :  1;  // Bits 28:28
    UINT32 Row_Increment_Enable                    :  1;  // Bits 29:29
    UINT32 Base_Invert_Data_and_ECC                :  1;  // Bits 30:30
    UINT32                                         :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCDFXS_CR_REUT_CH0_SUBSEQ_OFFSET_CTL_MCMAIN_2_STRUCT;

typedef union {
  struct {
    UINT32 Offset_Address_Update_Rate              :  5;  // Bits 4:0
    UINT32                                         :  3;  // Bits 7:5
    UINT32 Base_Subsequence_Repeat_Rate            :  5;  // Bits 12:8
    UINT32                                         :  2;  // Bits 14:13
    UINT32 Column_Offset_Wrap_Trigger_Enable       :  1;  // Bits 15:15
    UINT32 Row_Offset_Wrap_Trigger_Enable          :  1;  // Bits 16:16
    UINT32                                         :  3;  // Bits 19:17
    UINT32 Base_Subsequence_Type                   :  1;  // Bits 20:20
    UINT32 CADB_Deselect_Enable                    :  1;  // Bits 21:21
    UINT32 CADB_Select_Enable                      :  1;  // Bits 22:22
    UINT32 CADB_Seeds_Save_Enable                  :  1;  // Bits 23:23
    UINT32 Column_Increment_Order                  :  1;  // Bits 24:24
    UINT32 CADB_Seeds_Reload_Enable                :  1;  // Bits 25:25
    UINT32 Column_Increment_Enable                 :  1;  // Bits 26:26
    UINT32 Row_Increment_Order                     :  1;  // Bits 27:27
    UINT32                                         :  1;  // Bits 28:28
    UINT32 Row_Increment_Enable                    :  1;  // Bits 29:29
    UINT32 Base_Invert_Data_and_ECC                :  1;  // Bits 30:30
    UINT32                                         :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCDFXS_CR_REUT_CH0_SUBSEQ_OFFSET_CTL_MCMAIN_3_STRUCT;

typedef union {
  struct {
    UINT32 Offset_Address_Update_Rate              :  5;  // Bits 4:0
    UINT32                                         :  3;  // Bits 7:5
    UINT32 Base_Subsequence_Repeat_Rate            :  5;  // Bits 12:8
    UINT32                                         :  2;  // Bits 14:13
    UINT32 Column_Offset_Wrap_Trigger_Enable       :  1;  // Bits 15:15
    UINT32 Row_Offset_Wrap_Trigger_Enable          :  1;  // Bits 16:16
    UINT32                                         :  3;  // Bits 19:17
    UINT32 Base_Subsequence_Type                   :  1;  // Bits 20:20
    UINT32 CADB_Deselect_Enable                    :  1;  // Bits 21:21
    UINT32 CADB_Select_Enable                      :  1;  // Bits 22:22
    UINT32 CADB_Seeds_Save_Enable                  :  1;  // Bits 23:23
    UINT32 Column_Increment_Order                  :  1;  // Bits 24:24
    UINT32 CADB_Seeds_Reload_Enable                :  1;  // Bits 25:25
    UINT32 Column_Increment_Enable                 :  1;  // Bits 26:26
    UINT32 Row_Increment_Order                     :  1;  // Bits 27:27
    UINT32                                         :  1;  // Bits 28:28
    UINT32 Row_Increment_Enable                    :  1;  // Bits 29:29
    UINT32 Base_Invert_Data_and_ECC                :  1;  // Bits 30:30
    UINT32                                         :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCDFXS_CR_REUT_CH0_SUBSEQ_OFFSET_CTL_MCMAIN_4_STRUCT;

typedef union {
  struct {
    UINT32 Offset_Address_Update_Rate              :  5;  // Bits 4:0
    UINT32                                         :  3;  // Bits 7:5
    UINT32 Base_Subsequence_Repeat_Rate            :  5;  // Bits 12:8
    UINT32                                         :  2;  // Bits 14:13
    UINT32 Column_Offset_Wrap_Trigger_Enable       :  1;  // Bits 15:15
    UINT32 Row_Offset_Wrap_Trigger_Enable          :  1;  // Bits 16:16
    UINT32                                         :  3;  // Bits 19:17
    UINT32 Base_Subsequence_Type                   :  1;  // Bits 20:20
    UINT32 CADB_Deselect_Enable                    :  1;  // Bits 21:21
    UINT32 CADB_Select_Enable                      :  1;  // Bits 22:22
    UINT32 CADB_Seeds_Save_Enable                  :  1;  // Bits 23:23
    UINT32 Column_Increment_Order                  :  1;  // Bits 24:24
    UINT32 CADB_Seeds_Reload_Enable                :  1;  // Bits 25:25
    UINT32 Column_Increment_Enable                 :  1;  // Bits 26:26
    UINT32 Row_Increment_Order                     :  1;  // Bits 27:27
    UINT32                                         :  1;  // Bits 28:28
    UINT32 Row_Increment_Enable                    :  1;  // Bits 29:29
    UINT32 Base_Invert_Data_and_ECC                :  1;  // Bits 30:30
    UINT32                                         :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCDFXS_CR_REUT_CH0_SUBSEQ_OFFSET_CTL_MCMAIN_5_STRUCT;

typedef union {
  struct {
    UINT32 Offset_Address_Update_Rate              :  5;  // Bits 4:0
    UINT32                                         :  3;  // Bits 7:5
    UINT32 Base_Subsequence_Repeat_Rate            :  5;  // Bits 12:8
    UINT32                                         :  2;  // Bits 14:13
    UINT32 Column_Offset_Wrap_Trigger_Enable       :  1;  // Bits 15:15
    UINT32 Row_Offset_Wrap_Trigger_Enable          :  1;  // Bits 16:16
    UINT32                                         :  3;  // Bits 19:17
    UINT32 Base_Subsequence_Type                   :  1;  // Bits 20:20
    UINT32 CADB_Deselect_Enable                    :  1;  // Bits 21:21
    UINT32 CADB_Select_Enable                      :  1;  // Bits 22:22
    UINT32 CADB_Seeds_Save_Enable                  :  1;  // Bits 23:23
    UINT32 Column_Increment_Order                  :  1;  // Bits 24:24
    UINT32 CADB_Seeds_Reload_Enable                :  1;  // Bits 25:25
    UINT32 Column_Increment_Enable                 :  1;  // Bits 26:26
    UINT32 Row_Increment_Order                     :  1;  // Bits 27:27
    UINT32                                         :  1;  // Bits 28:28
    UINT32 Row_Increment_Enable                    :  1;  // Bits 29:29
    UINT32 Base_Invert_Data_and_ECC                :  1;  // Bits 30:30
    UINT32                                         :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCDFXS_CR_REUT_CH0_SUBSEQ_OFFSET_CTL_MCMAIN_6_STRUCT;

typedef union {
  struct {
    UINT32 Offset_Address_Update_Rate              :  5;  // Bits 4:0
    UINT32                                         :  3;  // Bits 7:5
    UINT32 Base_Subsequence_Repeat_Rate            :  5;  // Bits 12:8
    UINT32                                         :  2;  // Bits 14:13
    UINT32 Column_Offset_Wrap_Trigger_Enable       :  1;  // Bits 15:15
    UINT32 Row_Offset_Wrap_Trigger_Enable          :  1;  // Bits 16:16
    UINT32                                         :  3;  // Bits 19:17
    UINT32 Base_Subsequence_Type                   :  1;  // Bits 20:20
    UINT32 CADB_Deselect_Enable                    :  1;  // Bits 21:21
    UINT32 CADB_Select_Enable                      :  1;  // Bits 22:22
    UINT32 CADB_Seeds_Save_Enable                  :  1;  // Bits 23:23
    UINT32 Column_Increment_Order                  :  1;  // Bits 24:24
    UINT32 CADB_Seeds_Reload_Enable                :  1;  // Bits 25:25
    UINT32 Column_Increment_Enable                 :  1;  // Bits 26:26
    UINT32 Row_Increment_Order                     :  1;  // Bits 27:27
    UINT32                                         :  1;  // Bits 28:28
    UINT32 Row_Increment_Enable                    :  1;  // Bits 29:29
    UINT32 Base_Invert_Data_and_ECC                :  1;  // Bits 30:30
    UINT32                                         :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCDFXS_CR_REUT_CH0_SUBSEQ_OFFSET_CTL_MCMAIN_7_STRUCT;

typedef union {
  struct {
    UINT32 Offset_Address_Update_Rate              :  5;  // Bits 4:0
    UINT32                                         :  3;  // Bits 7:5
    UINT32 Base_Subsequence_Repeat_Rate            :  5;  // Bits 12:8
    UINT32                                         :  2;  // Bits 14:13
    UINT32 Column_Offset_Wrap_Trigger_Enable       :  1;  // Bits 15:15
    UINT32 Row_Offset_Wrap_Trigger_Enable          :  1;  // Bits 16:16
    UINT32                                         :  3;  // Bits 19:17
    UINT32 Base_Subsequence_Type                   :  1;  // Bits 20:20
    UINT32 CADB_Deselect_Enable                    :  1;  // Bits 21:21
    UINT32 CADB_Select_Enable                      :  1;  // Bits 22:22
    UINT32 CADB_Seeds_Save_Enable                  :  1;  // Bits 23:23
    UINT32 Column_Increment_Order                  :  1;  // Bits 24:24
    UINT32 CADB_Seeds_Reload_Enable                :  1;  // Bits 25:25
    UINT32 Column_Increment_Enable                 :  1;  // Bits 26:26
    UINT32 Row_Increment_Order                     :  1;  // Bits 27:27
    UINT32                                         :  1;  // Bits 28:28
    UINT32 Row_Increment_Enable                    :  1;  // Bits 29:29
    UINT32 Base_Invert_Data_and_ECC                :  1;  // Bits 30:30
    UINT32                                         :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCDFXS_CR_REUT_CH1_SUBSEQ_OFFSET_CTL_MCMAIN_0_STRUCT;

typedef union {
  struct {
    UINT32 Offset_Address_Update_Rate              :  5;  // Bits 4:0
    UINT32                                         :  3;  // Bits 7:5
    UINT32 Base_Subsequence_Repeat_Rate            :  5;  // Bits 12:8
    UINT32                                         :  2;  // Bits 14:13
    UINT32 Column_Offset_Wrap_Trigger_Enable       :  1;  // Bits 15:15
    UINT32 Row_Offset_Wrap_Trigger_Enable          :  1;  // Bits 16:16
    UINT32                                         :  3;  // Bits 19:17
    UINT32 Base_Subsequence_Type                   :  1;  // Bits 20:20
    UINT32 CADB_Deselect_Enable                    :  1;  // Bits 21:21
    UINT32 CADB_Select_Enable                      :  1;  // Bits 22:22
    UINT32 CADB_Seeds_Save_Enable                  :  1;  // Bits 23:23
    UINT32 Column_Increment_Order                  :  1;  // Bits 24:24
    UINT32 CADB_Seeds_Reload_Enable                :  1;  // Bits 25:25
    UINT32 Column_Increment_Enable                 :  1;  // Bits 26:26
    UINT32 Row_Increment_Order                     :  1;  // Bits 27:27
    UINT32                                         :  1;  // Bits 28:28
    UINT32 Row_Increment_Enable                    :  1;  // Bits 29:29
    UINT32 Base_Invert_Data_and_ECC                :  1;  // Bits 30:30
    UINT32                                         :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCDFXS_CR_REUT_CH1_SUBSEQ_OFFSET_CTL_MCMAIN_1_STRUCT;

typedef union {
  struct {
    UINT32 Offset_Address_Update_Rate              :  5;  // Bits 4:0
    UINT32                                         :  3;  // Bits 7:5
    UINT32 Base_Subsequence_Repeat_Rate            :  5;  // Bits 12:8
    UINT32                                         :  2;  // Bits 14:13
    UINT32 Column_Offset_Wrap_Trigger_Enable       :  1;  // Bits 15:15
    UINT32 Row_Offset_Wrap_Trigger_Enable          :  1;  // Bits 16:16
    UINT32                                         :  3;  // Bits 19:17
    UINT32 Base_Subsequence_Type                   :  1;  // Bits 20:20
    UINT32 CADB_Deselect_Enable                    :  1;  // Bits 21:21
    UINT32 CADB_Select_Enable                      :  1;  // Bits 22:22
    UINT32 CADB_Seeds_Save_Enable                  :  1;  // Bits 23:23
    UINT32 Column_Increment_Order                  :  1;  // Bits 24:24
    UINT32 CADB_Seeds_Reload_Enable                :  1;  // Bits 25:25
    UINT32 Column_Increment_Enable                 :  1;  // Bits 26:26
    UINT32 Row_Increment_Order                     :  1;  // Bits 27:27
    UINT32                                         :  1;  // Bits 28:28
    UINT32 Row_Increment_Enable                    :  1;  // Bits 29:29
    UINT32 Base_Invert_Data_and_ECC                :  1;  // Bits 30:30
    UINT32                                         :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCDFXS_CR_REUT_CH1_SUBSEQ_OFFSET_CTL_MCMAIN_2_STRUCT;

typedef union {
  struct {
    UINT32 Offset_Address_Update_Rate              :  5;  // Bits 4:0
    UINT32                                         :  3;  // Bits 7:5
    UINT32 Base_Subsequence_Repeat_Rate            :  5;  // Bits 12:8
    UINT32                                         :  2;  // Bits 14:13
    UINT32 Column_Offset_Wrap_Trigger_Enable       :  1;  // Bits 15:15
    UINT32 Row_Offset_Wrap_Trigger_Enable          :  1;  // Bits 16:16
    UINT32                                         :  3;  // Bits 19:17
    UINT32 Base_Subsequence_Type                   :  1;  // Bits 20:20
    UINT32 CADB_Deselect_Enable                    :  1;  // Bits 21:21
    UINT32 CADB_Select_Enable                      :  1;  // Bits 22:22
    UINT32 CADB_Seeds_Save_Enable                  :  1;  // Bits 23:23
    UINT32 Column_Increment_Order                  :  1;  // Bits 24:24
    UINT32 CADB_Seeds_Reload_Enable                :  1;  // Bits 25:25
    UINT32 Column_Increment_Enable                 :  1;  // Bits 26:26
    UINT32 Row_Increment_Order                     :  1;  // Bits 27:27
    UINT32                                         :  1;  // Bits 28:28
    UINT32 Row_Increment_Enable                    :  1;  // Bits 29:29
    UINT32 Base_Invert_Data_and_ECC                :  1;  // Bits 30:30
    UINT32                                         :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCDFXS_CR_REUT_CH1_SUBSEQ_OFFSET_CTL_MCMAIN_3_STRUCT;

typedef union {
  struct {
    UINT32 Offset_Address_Update_Rate              :  5;  // Bits 4:0
    UINT32                                         :  3;  // Bits 7:5
    UINT32 Base_Subsequence_Repeat_Rate            :  5;  // Bits 12:8
    UINT32                                         :  2;  // Bits 14:13
    UINT32 Column_Offset_Wrap_Trigger_Enable       :  1;  // Bits 15:15
    UINT32 Row_Offset_Wrap_Trigger_Enable          :  1;  // Bits 16:16
    UINT32                                         :  3;  // Bits 19:17
    UINT32 Base_Subsequence_Type                   :  1;  // Bits 20:20
    UINT32 CADB_Deselect_Enable                    :  1;  // Bits 21:21
    UINT32 CADB_Select_Enable                      :  1;  // Bits 22:22
    UINT32 CADB_Seeds_Save_Enable                  :  1;  // Bits 23:23
    UINT32 Column_Increment_Order                  :  1;  // Bits 24:24
    UINT32 CADB_Seeds_Reload_Enable                :  1;  // Bits 25:25
    UINT32 Column_Increment_Enable                 :  1;  // Bits 26:26
    UINT32 Row_Increment_Order                     :  1;  // Bits 27:27
    UINT32                                         :  1;  // Bits 28:28
    UINT32 Row_Increment_Enable                    :  1;  // Bits 29:29
    UINT32 Base_Invert_Data_and_ECC                :  1;  // Bits 30:30
    UINT32                                         :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCDFXS_CR_REUT_CH1_SUBSEQ_OFFSET_CTL_MCMAIN_4_STRUCT;

typedef union {
  struct {
    UINT32 Offset_Address_Update_Rate              :  5;  // Bits 4:0
    UINT32                                         :  3;  // Bits 7:5
    UINT32 Base_Subsequence_Repeat_Rate            :  5;  // Bits 12:8
    UINT32                                         :  2;  // Bits 14:13
    UINT32 Column_Offset_Wrap_Trigger_Enable       :  1;  // Bits 15:15
    UINT32 Row_Offset_Wrap_Trigger_Enable          :  1;  // Bits 16:16
    UINT32                                         :  3;  // Bits 19:17
    UINT32 Base_Subsequence_Type                   :  1;  // Bits 20:20
    UINT32 CADB_Deselect_Enable                    :  1;  // Bits 21:21
    UINT32 CADB_Select_Enable                      :  1;  // Bits 22:22
    UINT32 CADB_Seeds_Save_Enable                  :  1;  // Bits 23:23
    UINT32 Column_Increment_Order                  :  1;  // Bits 24:24
    UINT32 CADB_Seeds_Reload_Enable                :  1;  // Bits 25:25
    UINT32 Column_Increment_Enable                 :  1;  // Bits 26:26
    UINT32 Row_Increment_Order                     :  1;  // Bits 27:27
    UINT32                                         :  1;  // Bits 28:28
    UINT32 Row_Increment_Enable                    :  1;  // Bits 29:29
    UINT32 Base_Invert_Data_and_ECC                :  1;  // Bits 30:30
    UINT32                                         :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCDFXS_CR_REUT_CH1_SUBSEQ_OFFSET_CTL_MCMAIN_5_STRUCT;

typedef union {
  struct {
    UINT32 Offset_Address_Update_Rate              :  5;  // Bits 4:0
    UINT32                                         :  3;  // Bits 7:5
    UINT32 Base_Subsequence_Repeat_Rate            :  5;  // Bits 12:8
    UINT32                                         :  2;  // Bits 14:13
    UINT32 Column_Offset_Wrap_Trigger_Enable       :  1;  // Bits 15:15
    UINT32 Row_Offset_Wrap_Trigger_Enable          :  1;  // Bits 16:16
    UINT32                                         :  3;  // Bits 19:17
    UINT32 Base_Subsequence_Type                   :  1;  // Bits 20:20
    UINT32 CADB_Deselect_Enable                    :  1;  // Bits 21:21
    UINT32 CADB_Select_Enable                      :  1;  // Bits 22:22
    UINT32 CADB_Seeds_Save_Enable                  :  1;  // Bits 23:23
    UINT32 Column_Increment_Order                  :  1;  // Bits 24:24
    UINT32 CADB_Seeds_Reload_Enable                :  1;  // Bits 25:25
    UINT32 Column_Increment_Enable                 :  1;  // Bits 26:26
    UINT32 Row_Increment_Order                     :  1;  // Bits 27:27
    UINT32                                         :  1;  // Bits 28:28
    UINT32 Row_Increment_Enable                    :  1;  // Bits 29:29
    UINT32 Base_Invert_Data_and_ECC                :  1;  // Bits 30:30
    UINT32                                         :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCDFXS_CR_REUT_CH1_SUBSEQ_OFFSET_CTL_MCMAIN_6_STRUCT;

typedef union {
  struct {
    UINT32 Offset_Address_Update_Rate              :  5;  // Bits 4:0
    UINT32                                         :  3;  // Bits 7:5
    UINT32 Base_Subsequence_Repeat_Rate            :  5;  // Bits 12:8
    UINT32                                         :  2;  // Bits 14:13
    UINT32 Column_Offset_Wrap_Trigger_Enable       :  1;  // Bits 15:15
    UINT32 Row_Offset_Wrap_Trigger_Enable          :  1;  // Bits 16:16
    UINT32                                         :  3;  // Bits 19:17
    UINT32 Base_Subsequence_Type                   :  1;  // Bits 20:20
    UINT32 CADB_Deselect_Enable                    :  1;  // Bits 21:21
    UINT32 CADB_Select_Enable                      :  1;  // Bits 22:22
    UINT32 CADB_Seeds_Save_Enable                  :  1;  // Bits 23:23
    UINT32 Column_Increment_Order                  :  1;  // Bits 24:24
    UINT32 CADB_Seeds_Reload_Enable                :  1;  // Bits 25:25
    UINT32 Column_Increment_Enable                 :  1;  // Bits 26:26
    UINT32 Row_Increment_Order                     :  1;  // Bits 27:27
    UINT32                                         :  1;  // Bits 28:28
    UINT32 Row_Increment_Enable                    :  1;  // Bits 29:29
    UINT32 Base_Invert_Data_and_ECC                :  1;  // Bits 30:30
    UINT32                                         :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCDFXS_CR_REUT_CH1_SUBSEQ_OFFSET_CTL_MCMAIN_7_STRUCT;

typedef union {
  struct {
    UINT32                                         :  3;  // Bits 2:0
    UINT32 Stop_Base_Sequence_On_Wrap_Trigger      :  1;  // Bits 3:3
    UINT32                                         :  1;  // Bits 4:4
    UINT32 Address_Update_Rate_Mode                :  1;  // Bits 5:5
    UINT32                                         :  1;  // Bits 6:6
    UINT32 Enable_Dummy_Reads                      :  1;  // Bits 7:7
    UINT32                                         :  1;  // Bits 8:8
    UINT32 REUT_AllowOpp_Refresh                   :  1;  // Bits 9:9
    UINT32                                         :  1;  // Bits 10:10
    UINT32 Global_Control                          :  1;  // Bits 11:11
    UINT32 Initialization_Mode                     :  2;  // Bits 13:12
    UINT32                                         :  10;  // Bits 23:14
    UINT32 Subsequence_Start_Pointer               :  3;  // Bits 26:24
    UINT32                                         :  1;  // Bits 27:27
    UINT32 Subsequence_End_Pointer                 :  3;  // Bits 30:28
    UINT32                                         :  1;  // Bits 31:31
    UINT32 Start_Test_Delay                        :  10;  // Bits 41:32
    UINT32                                         :  6;  // Bits 47:42
    UINT32 SubSequence_Cacheline_Counter_Mode      :  1;  // Bits 48:48
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} MCDFXS_CR_REUT_CH_SEQ_CFG_MCMAIN_0_STRUCT;

typedef union {
  struct {
    UINT32                                         :  3;  // Bits 2:0
    UINT32 Stop_Base_Sequence_On_Wrap_Trigger      :  1;  // Bits 3:3
    UINT32                                         :  1;  // Bits 4:4
    UINT32 Address_Update_Rate_Mode                :  1;  // Bits 5:5
    UINT32                                         :  1;  // Bits 6:6
    UINT32 Enable_Dummy_Reads                      :  1;  // Bits 7:7
    UINT32                                         :  1;  // Bits 8:8
    UINT32 REUT_AllowOpp_Refresh                   :  1;  // Bits 9:9
    UINT32                                         :  1;  // Bits 10:10
    UINT32 Global_Control                          :  1;  // Bits 11:11
    UINT32 Initialization_Mode                     :  2;  // Bits 13:12
    UINT32                                         :  10;  // Bits 23:14
    UINT32 Subsequence_Start_Pointer               :  3;  // Bits 26:24
    UINT32                                         :  1;  // Bits 27:27
    UINT32 Subsequence_End_Pointer                 :  3;  // Bits 30:28
    UINT32                                         :  1;  // Bits 31:31
    UINT32 Start_Test_Delay                        :  10;  // Bits 41:32
    UINT32                                         :  6;  // Bits 47:42
    UINT32 SubSequence_Cacheline_Counter_Mode      :  1;  // Bits 48:48
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} MCDFXS_CR_REUT_CH_SEQ_CFG_MCMAIN_1_STRUCT;

typedef union {
  struct {
    UINT32 Local_Start_Test                        :  1;  // Bits 0:0
    UINT32 Local_Stop_Test                         :  1;  // Bits 1:1
    UINT32 Local_Clear_Errors                      :  1;  // Bits 2:2
    UINT32                                         :  29;  // Bits 31:3
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCDFXS_CR_REUT_CH_SEQ_CTL_MCMAIN_0_STRUCT;

typedef union {
  struct {
    UINT32 Local_Start_Test                        :  1;  // Bits 0:0
    UINT32 Local_Stop_Test                         :  1;  // Bits 1:1
    UINT32 Local_Clear_Errors                      :  1;  // Bits 2:2
    UINT32                                         :  29;  // Bits 31:3
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCDFXS_CR_REUT_CH_SEQ_CTL_MCMAIN_1_STRUCT;

typedef union {
  struct {
    UINT32 Current_Loopcount                       :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCDFXS_CR_REUT_CH_SEQ_LOOPCOUNT_STATUS_MCMAIN_0_STRUCT;

typedef union {
  struct {
    UINT32 Current_Loopcount                       :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCDFXS_CR_REUT_CH_SEQ_LOOPCOUNT_STATUS_MCMAIN_1_STRUCT;

typedef union {
  struct {
    UINT32 Current_Subsequence_Pointer             :  3;  // Bits 2:0
    UINT32                                         :  29;  // Bits 31:3
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCDFXS_CR_REUT_CH_SEQ_SUBSEQ_PNTR_MCMAIN_0_STRUCT;

typedef union {
  struct {
    UINT32 Current_Subsequence_Pointer             :  3;  // Bits 2:0
    UINT32                                         :  29;  // Bits 31:3
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCDFXS_CR_REUT_CH_SEQ_SUBSEQ_PNTR_MCMAIN_1_STRUCT;

typedef union {
  struct {
    UINT32 Current_Cacheline                       :  16;  // Bits 15:0
    UINT32                                         :  16;  // Bits 31:16
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCDFXS_CR_REUT_CH_SEQ_CACHELINE_STATUS_MCMAIN_0_STRUCT;

typedef union {
  struct {
    UINT32 Current_Cacheline                       :  16;  // Bits 15:0
    UINT32                                         :  16;  // Bits 31:16
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCDFXS_CR_REUT_CH_SEQ_CACHELINE_STATUS_MCMAIN_1_STRUCT;

typedef union {
  struct {
    UINT32                                         :  3;  // Bits 2:0
    UINT32 Column_Address                          :  8;  // Bits 10:3
    UINT32                                         :  13;  // Bits 23:11
    UINT32 Row_AddressLow                          :  8;  // Bits 31:24
    UINT32 Row_AddressHigh                         :  9;  // Bits 40:32
    UINT32                                         :  7;  // Bits 47:41
    UINT32 Bank_Address                            :  4;  // Bits 51:48
    UINT32                                         :  4;  // Bits 55:52
    UINT32 Rank_Address                            :  3;  // Bits 58:56
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} MCDFXS_CR_REUT_CH_SEQ_BASE_ADDR_START_MCMAIN_0_STRUCT;

typedef union {
  struct {
    UINT32                                         :  3;  // Bits 2:0
    UINT32 Column_Address                          :  8;  // Bits 10:3
    UINT32                                         :  13;  // Bits 23:11
    UINT32 Row_AddressLow                          :  8;  // Bits 31:24
    UINT32 Row_AddressHigh                         :  9;  // Bits 40:32
    UINT32                                         :  7;  // Bits 47:41
    UINT32 Bank_Address                            :  4;  // Bits 51:48
    UINT32                                         :  4;  // Bits 55:52
    UINT32 Rank_Address                            :  3;  // Bits 58:56
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} MCDFXS_CR_REUT_CH_SEQ_BASE_ADDR_START_MCMAIN_1_STRUCT;

typedef union {
  struct {
    UINT32                                         :  3;  // Bits 2:0
    UINT32 Column_Address                          :  9;  // Bits 11:3
    UINT32                                         :  12;  // Bits 23:12
    UINT32 Row_AddressLow                          :  8;  // Bits 31:24
    UINT32 Row_AddressHigh                         :  10;  // Bits 41:32
    UINT32                                         :  6;  // Bits 47:42
    UINT32 Bank_Address                            :  4;  // Bits 51:48
    UINT32                                         :  4;  // Bits 55:52
    UINT32 Rank_Address                            :  3;  // Bits 58:56
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} MCDFXS_CR_REUT_CH_SEQ_BASE_ADDR_WRAP_MCMAIN_0_STRUCT;

typedef union {
  struct {
    UINT32                                         :  3;  // Bits 2:0
    UINT32 Column_Address                          :  9;  // Bits 11:3
    UINT32                                         :  12;  // Bits 23:12
    UINT32 Row_AddressLow                          :  8;  // Bits 31:24
    UINT32 Row_AddressHigh                         :  10;  // Bits 41:32
    UINT32                                         :  6;  // Bits 47:42
    UINT32 Bank_Address                            :  4;  // Bits 51:48
    UINT32                                         :  4;  // Bits 55:52
    UINT32 Rank_Address                            :  3;  // Bits 58:56
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} MCDFXS_CR_REUT_CH_SEQ_BASE_ADDR_WRAP_MCMAIN_1_STRUCT;

typedef union {
  struct {
    UINT32                                         :  3;  // Bits 2:0
    UINT32 Column_Address                          :  8;  // Bits 10:3
    UINT32                                         :  13;  // Bits 23:11
    UINT32 Row_AddressLow                          :  8;  // Bits 31:24
    UINT32 Row_AddressHigh                         :  9;  // Bits 40:32
    UINT32                                         :  7;  // Bits 47:41
    UINT32 Bank_Address                            :  4;  // Bits 51:48
    UINT32                                         :  4;  // Bits 55:52
    UINT32 Rank_Address                            :  3;  // Bits 58:56
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} MCDFXS_CR_REUT_CH_SEQ_BASE_ADDR_CURRENT_MCMAIN_0_STRUCT;

typedef union {
  struct {
    UINT32                                         :  3;  // Bits 2:0
    UINT32 Column_Address                          :  8;  // Bits 10:3
    UINT32                                         :  13;  // Bits 23:11
    UINT32 Row_AddressLow                          :  8;  // Bits 31:24
    UINT32 Row_AddressHigh                         :  9;  // Bits 40:32
    UINT32                                         :  7;  // Bits 47:41
    UINT32 Bank_Address                            :  4;  // Bits 51:48
    UINT32                                         :  4;  // Bits 55:52
    UINT32 Rank_Address                            :  3;  // Bits 58:56
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} MCDFXS_CR_REUT_CH_SEQ_BASE_ADDR_CURRENT_MCMAIN_1_STRUCT;

typedef union {
  struct {
    UINT32 Base_Column_Address_Order               :  2;  // Bits 1:0
    UINT32 Base_Row_Address_Order                  :  2;  // Bits 3:2
    UINT32 Base_Bank_Address_Order                 :  2;  // Bits 5:4
    UINT32 Base_Rank_Address_Order                 :  2;  // Bits 7:6
    UINT32                                         :  5;  // Bits 12:8
    UINT32 Base_Address_Invert_Rate                :  3;  // Bits 15:13
    UINT32                                         :  4;  // Bits 19:16
    UINT32 Column_Base_Address_Invert_Enable       :  1;  // Bits 20:20
    UINT32 Row_Base_Address_Invert_Enable          :  1;  // Bits 21:21
    UINT32 Bank_Base_Address_Invert_Enable         :  1;  // Bits 22:22
    UINT32 Rank_Base_Address_Invert_Enable         :  1;  // Bits 23:23
    UINT32 Column_Base_Wrap_Trigger_Enable         :  1;  // Bits 24:24
    UINT32 Row_Base_Wrap_Trigger_Enable            :  1;  // Bits 25:25
    UINT32 Bank_Base_Wrap_Trigger_Enable           :  1;  // Bits 26:26
    UINT32 Rank_Base_Wrap_Trigger_Enable           :  1;  // Bits 27:27
    UINT32 Column_Base_Wrap_Carry_Enable           :  1;  // Bits 28:28
    UINT32 Row_Base_Wrap_Carry_Enable              :  1;  // Bits 29:29
    UINT32 Bank_Base_Wrap_Carry_Enable             :  1;  // Bits 30:30
    UINT32 Rank_Base_Wrap_Carry_Enable             :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCDFXS_CR_REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_MCMAIN_0_STRUCT;

typedef union {
  struct {
    UINT32 Base_Column_Address_Order               :  2;  // Bits 1:0
    UINT32 Base_Row_Address_Order                  :  2;  // Bits 3:2
    UINT32 Base_Bank_Address_Order                 :  2;  // Bits 5:4
    UINT32 Base_Rank_Address_Order                 :  2;  // Bits 7:6
    UINT32                                         :  5;  // Bits 12:8
    UINT32 Base_Address_Invert_Rate                :  3;  // Bits 15:13
    UINT32                                         :  4;  // Bits 19:16
    UINT32 Column_Base_Address_Invert_Enable       :  1;  // Bits 20:20
    UINT32 Row_Base_Address_Invert_Enable          :  1;  // Bits 21:21
    UINT32 Bank_Base_Address_Invert_Enable         :  1;  // Bits 22:22
    UINT32 Rank_Base_Address_Invert_Enable         :  1;  // Bits 23:23
    UINT32 Column_Base_Wrap_Trigger_Enable         :  1;  // Bits 24:24
    UINT32 Row_Base_Wrap_Trigger_Enable            :  1;  // Bits 25:25
    UINT32 Bank_Base_Wrap_Trigger_Enable           :  1;  // Bits 26:26
    UINT32 Rank_Base_Wrap_Trigger_Enable           :  1;  // Bits 27:27
    UINT32 Column_Base_Wrap_Carry_Enable           :  1;  // Bits 28:28
    UINT32 Row_Base_Wrap_Carry_Enable              :  1;  // Bits 29:29
    UINT32 Bank_Base_Wrap_Carry_Enable             :  1;  // Bits 30:30
    UINT32 Rank_Base_Wrap_Carry_Enable             :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCDFXS_CR_REUT_CH_SEQ_BASE_ADDR_ORDER_CARRY_INVERT_CTL_MCMAIN_1_STRUCT;

typedef union {
  struct {
    UINT32                                         :  3;  // Bits 2:0
    UINT32 Column_Base_Address_Increment           :  8;  // Bits 10:3
    UINT32                                         :  1;  // Bits 11:11
    UINT32 Column_Base_Address_Update_Rate         :  5;  // Bits 16:12
    UINT32                                         :  2;  // Bits 18:17
    UINT32 Column_Base_Address_Update_Scale        :  1;  // Bits 19:19
    UINT32 Row_Base_Address_Increment              :  12;  // Bits 31:20
    UINT32 Row_Base_Address_Update_Rate            :  4;  // Bits 35:32
    UINT32                                         :  1;  // Bits 36:36
    UINT32 Row_Base_Address_Update_Scale           :  1;  // Bits 37:37
    UINT32 Bank_Base_Address_Increment             :  4;  // Bits 41:38
    UINT32                                         :  2;  // Bits 43:42
    UINT32 Bank_Base_Address_Update_Rate           :  5;  // Bits 48:44
    UINT32                                         :  2;  // Bits 50:49
    UINT32 Bank_Base_Address_Update_Scale          :  1;  // Bits 51:51
    UINT32 Rank_Base_Address_Increment             :  3;  // Bits 54:52
    UINT32                                         :  1;  // Bits 55:55
    UINT32 Rank_Base_Address_Update_Rate           :  5;  // Bits 60:56
    UINT32                                         :  2;  // Bits 62:61
    UINT32 Rank_Base_Address_Update_Scale          :  1;  // Bits 63:63
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} MCDFXS_CR_REUT_CH_SEQ_BASE_ADDR_INC_CTL_MCMAIN_0_STRUCT;

typedef union {
  struct {
    UINT32                                         :  3;  // Bits 2:0
    UINT32 Column_Base_Address_Increment           :  8;  // Bits 10:3
    UINT32                                         :  1;  // Bits 11:11
    UINT32 Column_Base_Address_Update_Rate         :  5;  // Bits 16:12
    UINT32                                         :  2;  // Bits 18:17
    UINT32 Column_Base_Address_Update_Scale        :  1;  // Bits 19:19
    UINT32 Row_Base_Address_Increment              :  12;  // Bits 31:20
    UINT32 Row_Base_Address_Update_Rate            :  4;  // Bits 35:32
    UINT32                                         :  1;  // Bits 36:36
    UINT32 Row_Base_Address_Update_Scale           :  1;  // Bits 37:37
    UINT32 Bank_Base_Address_Increment             :  4;  // Bits 41:38
    UINT32                                         :  2;  // Bits 43:42
    UINT32 Bank_Base_Address_Update_Rate           :  5;  // Bits 48:44
    UINT32                                         :  2;  // Bits 50:49
    UINT32 Bank_Base_Address_Update_Scale          :  1;  // Bits 51:51
    UINT32 Rank_Base_Address_Increment             :  3;  // Bits 54:52
    UINT32                                         :  1;  // Bits 55:55
    UINT32 Rank_Base_Address_Update_Rate           :  5;  // Bits 60:56
    UINT32                                         :  2;  // Bits 62:61
    UINT32 Rank_Base_Address_Update_Scale          :  1;  // Bits 63:63
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} MCDFXS_CR_REUT_CH_SEQ_BASE_ADDR_INC_CTL_MCMAIN_1_STRUCT;

typedef union {
  struct {
    UINT32                                         :  3;  // Bits 2:0
    UINT32 Column_Address                          :  8;  // Bits 10:3
    UINT32                                         :  13;  // Bits 23:11
    UINT32 Row_AddressLow                          :  8;  // Bits 31:24
    UINT32 Row_AddressHigh                         :  9;  // Bits 40:32
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} MCDFXS_CR_REUT_CH_SEQ_OFFSET_ADDR_CURRENT_MCMAIN_0_STRUCT;

typedef union {
  struct {
    UINT32                                         :  3;  // Bits 2:0
    UINT32 Column_Address                          :  8;  // Bits 10:3
    UINT32                                         :  13;  // Bits 23:11
    UINT32 Row_AddressLow                          :  8;  // Bits 31:24
    UINT32 Row_AddressHigh                         :  9;  // Bits 40:32
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} MCDFXS_CR_REUT_CH_SEQ_OFFSET_ADDR_CURRENT_MCMAIN_1_STRUCT;

typedef union {
  struct {
    UINT32 Logical_to_Physical_Rank0_Mapping       :  2;  // Bits 1:0
    UINT32                                         :  2;  // Bits 3:2
    UINT32 Logical_to_Physical_Rank1_Mapping       :  2;  // Bits 5:4
    UINT32                                         :  2;  // Bits 7:6
    UINT32 Logical_to_Physical_Rank2_Mapping       :  2;  // Bits 9:8
    UINT32                                         :  2;  // Bits 11:10
    UINT32 Logical_to_Physical_Rank3_Mapping       :  2;  // Bits 13:12
    UINT32                                         :  2;  // Bits 15:14
    UINT32 Logical_to_Physical_Rank4_Mapping       :  2;  // Bits 17:16
    UINT32                                         :  2;  // Bits 19:18
    UINT32 Logical_to_Physical_Rank5_Mapping       :  2;  // Bits 21:20
    UINT32                                         :  2;  // Bits 23:22
    UINT32 Logical_to_Physical_Rank6_Mapping       :  2;  // Bits 25:24
    UINT32                                         :  2;  // Bits 27:26
    UINT32 Logical_to_Physical_Rank7_Mapping       :  2;  // Bits 29:28
    UINT32                                         :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCDFXS_CR_REUT_CH_SEQ_RANK_LOGICAL_TO_PHYSICAL_MAPPING_MCMAIN_0_STRUCT;

typedef union {
  struct {
    UINT32 Logical_to_Physical_Rank0_Mapping       :  2;  // Bits 1:0
    UINT32                                         :  2;  // Bits 3:2
    UINT32 Logical_to_Physical_Rank1_Mapping       :  2;  // Bits 5:4
    UINT32                                         :  2;  // Bits 7:6
    UINT32 Logical_to_Physical_Rank2_Mapping       :  2;  // Bits 9:8
    UINT32                                         :  2;  // Bits 11:10
    UINT32 Logical_to_Physical_Rank3_Mapping       :  2;  // Bits 13:12
    UINT32                                         :  2;  // Bits 15:14
    UINT32 Logical_to_Physical_Rank4_Mapping       :  2;  // Bits 17:16
    UINT32                                         :  2;  // Bits 19:18
    UINT32 Logical_to_Physical_Rank5_Mapping       :  2;  // Bits 21:20
    UINT32                                         :  2;  // Bits 23:22
    UINT32 Logical_to_Physical_Rank6_Mapping       :  2;  // Bits 25:24
    UINT32                                         :  2;  // Bits 27:26
    UINT32 Logical_to_Physical_Rank7_Mapping       :  2;  // Bits 29:28
    UINT32                                         :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCDFXS_CR_REUT_CH_SEQ_RANK_LOGICAL_TO_PHYSICAL_MAPPING_MCMAIN_1_STRUCT;

typedef union {
  struct {
    UINT32 Logical_to_Physical_Row0_Swizzle        :  5;  // Bits 4:0
    UINT32 Logical_to_Physical_Row1_Swizzle        :  5;  // Bits 9:5
    UINT32 Logical_to_Physical_Row2_Swizzle        :  5;  // Bits 14:10
    UINT32 Logical_to_Physical_Row3_Swizzle        :  5;  // Bits 19:15
    UINT32 Logical_to_Physical_Row4_Swizzle        :  5;  // Bits 24:20
    UINT32 Logical_to_Physical_Row5_Swizzle        :  5;  // Bits 29:25
    UINT32                                         :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCDFXS_CR_REUT_CH_SEQ_ROW_ADDR_SWIZZLE_LOWER_MCMAIN_0_STRUCT;

typedef union {
  struct {
    UINT32 Logical_to_Physical_Row0_Swizzle        :  5;  // Bits 4:0
    UINT32 Logical_to_Physical_Row1_Swizzle        :  5;  // Bits 9:5
    UINT32 Logical_to_Physical_Row2_Swizzle        :  5;  // Bits 14:10
    UINT32 Logical_to_Physical_Row3_Swizzle        :  5;  // Bits 19:15
    UINT32 Logical_to_Physical_Row4_Swizzle        :  5;  // Bits 24:20
    UINT32 Logical_to_Physical_Row5_Swizzle        :  5;  // Bits 29:25
    UINT32                                         :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCDFXS_CR_REUT_CH_SEQ_ROW_ADDR_SWIZZLE_LOWER_MCMAIN_1_STRUCT;

typedef union {
  struct {
    UINT32 Logical_to_Physical_Row6_Swizzle        :  5;  // Bits 4:0
    UINT32 Logical_to_Physical_Row7_Swizzle        :  5;  // Bits 9:5
    UINT32 Logical_to_Physical_Row8_Swizzle        :  5;  // Bits 14:10
    UINT32 Logical_to_Physical_Row9_Swizzle        :  5;  // Bits 19:15
    UINT32 Logical_to_Physical_Row10_Swizzle       :  5;  // Bits 24:20
    UINT32 Logical_to_Physical_Row11_Swizzle       :  5;  // Bits 29:25
    UINT32 Logical_to_Physical_Row12_SwizzleLow    :  2;  // Bits 31:30
    UINT32 Logical_to_Physical_Row12_SwizzleHigh   :  3;  // Bits 34:32
    UINT32 Logical_to_Physical_Row13_Swizzle       :  5;  // Bits 39:35
    UINT32 Logical_to_Physical_Row14_Swizzle       :  5;  // Bits 44:40
    UINT32 Logical_to_Physical_Row15_Swizzle       :  5;  // Bits 49:45
    UINT32 Logical_to_Physical_Row16_Swizzle       :  5;  // Bits 54:50
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} MCDFXS_CR_REUT_CH_SEQ_ROW_ADDR_SWIZZLE_UPPER_MCMAIN_0_STRUCT;

typedef union {
  struct {
    UINT32 Logical_to_Physical_Row6_Swizzle        :  5;  // Bits 4:0
    UINT32 Logical_to_Physical_Row7_Swizzle        :  5;  // Bits 9:5
    UINT32 Logical_to_Physical_Row8_Swizzle        :  5;  // Bits 14:10
    UINT32 Logical_to_Physical_Row9_Swizzle        :  5;  // Bits 19:15
    UINT32 Logical_to_Physical_Row10_Swizzle       :  5;  // Bits 24:20
    UINT32 Logical_to_Physical_Row11_Swizzle       :  5;  // Bits 29:25
    UINT32 Logical_to_Physical_Row12_SwizzleLow    :  2;  // Bits 31:30
    UINT32 Logical_to_Physical_Row12_SwizzleHigh   :  3;  // Bits 34:32
    UINT32 Logical_to_Physical_Row13_Swizzle       :  5;  // Bits 39:35
    UINT32 Logical_to_Physical_Row14_Swizzle       :  5;  // Bits 44:40
    UINT32 Logical_to_Physical_Row15_Swizzle       :  5;  // Bits 49:45
    UINT32 Logical_to_Physical_Row16_Swizzle       :  5;  // Bits 54:50
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} MCDFXS_CR_REUT_CH_SEQ_ROW_ADDR_SWIZZLE_UPPER_MCMAIN_1_STRUCT;

typedef union {
  struct {
    UINT32 Dummy_Read_Row_Current_Address          :  17;  // Bits 16:0
    UINT32                                         :  7;  // Bits 23:17
    UINT32 Dummy_Read_Bank_Current_Address         :  4;  // Bits 27:24
    UINT32                                         :  2;  // Bits 29:28
    UINT32 Dummy_Read_Rank_Current_Address         :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCDFXS_CR_REUT_CH_SEQ_DUMMYREAD_ADDRESS_MCMAIN_0_STRUCT;

typedef union {
  struct {
    UINT32 Dummy_Read_Row_Current_Address          :  17;  // Bits 16:0
    UINT32                                         :  7;  // Bits 23:17
    UINT32 Dummy_Read_Bank_Current_Address         :  4;  // Bits 27:24
    UINT32                                         :  2;  // Bits 29:28
    UINT32 Dummy_Read_Rank_Current_Address         :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCDFXS_CR_REUT_CH_SEQ_DUMMYREAD_ADDRESS_MCMAIN_1_STRUCT;

typedef union {
  struct {
    UINT32 Dummy_Read_Bank_Mask                    :  16;  // Bits 15:0
    UINT32                                         :  4;  // Bits 19:16
    UINT32 Dummy_Read_Rank_Mask                    :  4;  // Bits 23:20
    UINT32                                         :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCDFXS_CR_REUT_CH_SEQ_DUMMYREAD_MASK_MCMAIN_0_STRUCT;

typedef union {
  struct {
    UINT32 Dummy_Read_Bank_Mask                    :  16;  // Bits 15:0
    UINT32                                         :  4;  // Bits 19:16
    UINT32 Dummy_Read_Rank_Mask                    :  4;  // Bits 23:20
    UINT32                                         :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCDFXS_CR_REUT_CH_SEQ_DUMMYREAD_MASK_MCMAIN_1_STRUCT;

typedef union {
  struct {
    UINT32 L_DummyRead_Select                      :  1;  // Bits 0:0
    UINT32 Enable_Sweep_Frequency                  :  1;  // Bits 1:1
    UINT32                                         :  6;  // Bits 7:2
    UINT32 L_counter                               :  8;  // Bits 15:8
    UINT32 M_counter                               :  8;  // Bits 23:16
    UINT32 N_Counter                               :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCDFXS_CR_REUT_CH_SEQ_DUMMYREAD_CTL_MCMAIN_0_STRUCT;

typedef union {
  struct {
    UINT32 L_DummyRead_Select                      :  1;  // Bits 0:0
    UINT32 Enable_Sweep_Frequency                  :  1;  // Bits 1:1
    UINT32                                         :  6;  // Bits 7:2
    UINT32 L_counter                               :  8;  // Bits 15:8
    UINT32 M_counter                               :  8;  // Bits 23:16
    UINT32 N_Counter                               :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCDFXS_CR_REUT_CH_SEQ_DUMMYREAD_CTL_MCMAIN_1_STRUCT;

typedef union {
  struct {
    UINT32 EN_CLK                                  :  1;  // Bits 0:0
    UINT32 L0_DATA_BYTE_SEL                        :  7;  // Bits 7:1
    UINT32 L0_BYP_SEL                              :  1;  // Bits 8:8
    UINT32 L1_DATA_BYTE_SEL                        :  7;  // Bits 15:9
    UINT32 L1_BYP_SEL                              :  1;  // Bits 16:16
    UINT32                                         :  15;  // Bits 31:17
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCDFXS_CR_VISA_CTL_MCDFXS_MCMAIN_STRUCT;

typedef union {
  struct {
    UINT32 Trigger_In_Global_Start                 :  1;  // Bits 0:0
    UINT32 Trigger_Out_Global_Start                :  1;  // Bits 1:1
    UINT32                                         :  5;  // Bits 6:2
    UINT32 Trigger_Out_On_Error_0                  :  1;  // Bits 7:7
    UINT32 Trigger_Out_On_Error_1                  :  1;  // Bits 8:8
    UINT32                                         :  6;  // Bits 14:9
    UINT32 Trigger_Out_On_Channel_Test_Done_Status_0:  1;  // Bits 15:15
    UINT32 Trigger_Out_On_Channel_Test_Done_Status_1:  1;  // Bits 16:16
    UINT32                                         :  15;  // Bits 31:17
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCDFXS_CR_REUT_CH_ERR_TRIGGER_CTL_MCMAIN_STRUCT;

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
} MCDFXS_CR_VISA_SLIDE_MCDFXS_MCMAIN_STRUCT;

typedef union {
  struct {
    UINT32 Logical_to_Physical_Bank0_Mapping       :  4;  // Bits 3:0
    UINT32 Logical_to_Physical_Bank1_Mapping       :  4;  // Bits 7:4
    UINT32 Logical_to_Physical_Bank2_Mapping       :  4;  // Bits 11:8
    UINT32 Logical_to_Physical_Bank3_Mapping       :  4;  // Bits 15:12
    UINT32 Logical_to_Physical_Bank4_Mapping       :  4;  // Bits 19:16
    UINT32 Logical_to_Physical_Bank5_Mapping       :  4;  // Bits 23:20
    UINT32 Logical_to_Physical_Bank6_Mapping       :  4;  // Bits 27:24
    UINT32 Logical_to_Physical_Bank7_Mapping       :  4;  // Bits 31:28
    UINT32 Logical_to_Physical_Bank8_Mapping       :  4;  // Bits 35:32
    UINT32 Logical_to_Physical_Bank9_Mapping       :  4;  // Bits 39:36
    UINT32 Logical_to_Physical_Bank10_Mapping      :  4;  // Bits 43:40
    UINT32 Logical_to_Physical_Bank11_Mapping      :  4;  // Bits 47:44
    UINT32 Logical_to_Physical_Bank12_Mapping      :  4;  // Bits 51:48
    UINT32 Logical_to_Physical_Bank13_Mapping      :  4;  // Bits 55:52
    UINT32 Logical_to_Physical_Bank14_Mapping      :  4;  // Bits 59:56
    UINT32 Logical_to_Physical_Bank15_Mapping      :  4;  // Bits 63:60
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} MCDFXS_CR_REUT_CH_SEQ_BANK_LOGICAL_TO_PHYSICAL_MAPPING_MCMAIN_0_STRUCT;

typedef union {
  struct {
    UINT32 Logical_to_Physical_Bank0_Mapping       :  4;  // Bits 3:0
    UINT32 Logical_to_Physical_Bank1_Mapping       :  4;  // Bits 7:4
    UINT32 Logical_to_Physical_Bank2_Mapping       :  4;  // Bits 11:8
    UINT32 Logical_to_Physical_Bank3_Mapping       :  4;  // Bits 15:12
    UINT32 Logical_to_Physical_Bank4_Mapping       :  4;  // Bits 19:16
    UINT32 Logical_to_Physical_Bank5_Mapping       :  4;  // Bits 23:20
    UINT32 Logical_to_Physical_Bank6_Mapping       :  4;  // Bits 27:24
    UINT32 Logical_to_Physical_Bank7_Mapping       :  4;  // Bits 31:28
    UINT32 Logical_to_Physical_Bank8_Mapping       :  4;  // Bits 35:32
    UINT32 Logical_to_Physical_Bank9_Mapping       :  4;  // Bits 39:36
    UINT32 Logical_to_Physical_Bank10_Mapping      :  4;  // Bits 43:40
    UINT32 Logical_to_Physical_Bank11_Mapping      :  4;  // Bits 47:44
    UINT32 Logical_to_Physical_Bank12_Mapping      :  4;  // Bits 51:48
    UINT32 Logical_to_Physical_Bank13_Mapping      :  4;  // Bits 55:52
    UINT32 Logical_to_Physical_Bank14_Mapping      :  4;  // Bits 59:56
    UINT32 Logical_to_Physical_Bank15_Mapping      :  4;  // Bits 63:60
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} MCDFXS_CR_REUT_CH_SEQ_BANK_LOGICAL_TO_PHYSICAL_MAPPING_MCMAIN_1_STRUCT;

typedef union {
  struct {
    UINT32                                         :  3;  // Bits 2:0
    UINT32 Column_Address                          :  8;  // Bits 10:3
    UINT32                                         :  13;  // Bits 23:11
    UINT32 Row_AddressLow                          :  8;  // Bits 31:24
    UINT32 Row_AddressHigh                         :  9;  // Bits 40:32
    UINT32                                         :  7;  // Bits 47:41
    UINT32 Bank_Address                            :  4;  // Bits 51:48
    UINT32                                         :  4;  // Bits 55:52
    UINT32 Rank_Address                            :  3;  // Bits 58:56
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} MCDFXS_CR_REUT_CH_SEQ_BASE_ADDR_SAVE_MCMAIN_0_STRUCT;

typedef union {
  struct {
    UINT32                                         :  3;  // Bits 2:0
    UINT32 Column_Address                          :  8;  // Bits 10:3
    UINT32                                         :  13;  // Bits 23:11
    UINT32 Row_AddressLow                          :  8;  // Bits 31:24
    UINT32 Row_AddressHigh                         :  9;  // Bits 40:32
    UINT32                                         :  7;  // Bits 47:41
    UINT32 Bank_Address                            :  4;  // Bits 51:48
    UINT32                                         :  4;  // Bits 55:52
    UINT32 Rank_Address                            :  3;  // Bits 58:56
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} MCDFXS_CR_REUT_CH_SEQ_BASE_ADDR_SAVE_MCMAIN_1_STRUCT;

typedef union {
  struct {
    UINT32 Loopcount_Limit                         :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCDFXS_CR_REUT_CH_SEQ_LOOPCOUNT_LIMIT_MCMAIN_0_STRUCT;

typedef union {
  struct {
    UINT32 Loopcount_Limit                         :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCDFXS_CR_REUT_CH_SEQ_LOOPCOUNT_LIMIT_MCMAIN_1_STRUCT;

typedef union {
  struct {
    UINT32 Col_Enable                              :  8;  // Bits 7:0
    UINT32 Row_Enable                              :  17;  // Bits 24:8
    UINT32                                         :  7;  // Bits 31:25
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCDFXS_CR_REUT_CH_SEQ_ADDR_ENABLE_MCMAIN_0_STRUCT;

typedef union {
  struct {
    UINT32 Col_Enable                              :  8;  // Bits 7:0
    UINT32 Row_Enable                              :  17;  // Bits 24:8
    UINT32                                         :  7;  // Bits 31:25
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCDFXS_CR_REUT_CH_SEQ_ADDR_ENABLE_MCMAIN_1_STRUCT;

typedef union {
  struct {
    UINT32 tRP                                     :  6;  // Bits 5:0
    UINT32 tRPab_ext                               :  2;  // Bits 7:6
    UINT32 tRAS                                    :  7;  // Bits 14:8
    UINT32                                         :  1;  // Bits 15:15
    UINT32 tRDPRE                                  :  4;  // Bits 19:16
    UINT32                                         :  4;  // Bits 23:20
    UINT32 tWRPRE                                  :  7;  // Bits 30:24
    UINT32                                         :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCSCHEDS_CR_TC_PRE_STRUCT;

typedef union {
  struct {
    UINT32 tFAW                                    :  6;  // Bits 5:0
    UINT32                                         :  2;  // Bits 7:6
    UINT32 tRRD_sg                                 :  4;  // Bits 11:8
    UINT32 tRRD_dg                                 :  4;  // Bits 15:12
    UINT32 derating_ext                            :  2;  // Bits 17:16
    UINT32                                         :  14;  // Bits 31:18
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCSCHEDS_CR_TC_ACT_STRUCT;

typedef union {
  struct {
    UINT32 tCKE                                    :  4;  // Bits 3:0
    UINT32 tXP                                     :  4;  // Bits 7:4
    UINT32 tXPDLL                                  :  6;  // Bits 13:8
    UINT32 tPRPDEN                                 :  2;  // Bits 15:14
    UINT32 tRDPDEN                                 :  7;  // Bits 22:16
    UINT32                                         :  1;  // Bits 23:23
    UINT32 tWRPDEN                                 :  7;  // Bits 30:24
    UINT32                                         :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCSCHEDS_CR_TC_PWRDN_STRUCT;

typedef union {
  struct {
    UINT32 tRDRD_sg                                :  6;  // Bits 5:0
    UINT32                                         :  2;  // Bits 7:6
    UINT32 tRDRD_dg                                :  6;  // Bits 13:8
    UINT32                                         :  2;  // Bits 15:14
    UINT32 tRDRD_dr                                :  6;  // Bits 21:16
    UINT32                                         :  2;  // Bits 23:22
    UINT32 tRDRD_dd                                :  6;  // Bits 29:24
    UINT32                                         :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCSCHEDS_CR_TC_RDRD_STRUCT;

typedef union {
  struct {
    UINT32 tRDWR_sg                                :  6;  // Bits 5:0
    UINT32                                         :  2;  // Bits 7:6
    UINT32 tRDWR_dg                                :  6;  // Bits 13:8
    UINT32                                         :  2;  // Bits 15:14
    UINT32 tRDWR_dr                                :  6;  // Bits 21:16
    UINT32                                         :  2;  // Bits 23:22
    UINT32 tRDWR_dd                                :  6;  // Bits 29:24
    UINT32                                         :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCSCHEDS_CR_TC_RDWR_STRUCT;

typedef union {
  struct {
    UINT32 tWRRD_sg                                :  7;  // Bits 6:0
    UINT32                                         :  1;  // Bits 7:7
    UINT32 tWRRD_dg                                :  6;  // Bits 13:8
    UINT32                                         :  2;  // Bits 15:14
    UINT32 tWRRD_dr                                :  6;  // Bits 21:16
    UINT32                                         :  2;  // Bits 23:22
    UINT32 tWRRD_dd                                :  6;  // Bits 29:24
    UINT32                                         :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCSCHEDS_CR_TC_WRRD_STRUCT;

typedef union {
  struct {
    UINT32 tWRWR_sg                                :  6;  // Bits 5:0
    UINT32                                         :  2;  // Bits 7:6
    UINT32 tWRWR_dg                                :  6;  // Bits 13:8
    UINT32                                         :  2;  // Bits 15:14
    UINT32 tWRWR_dr                                :  6;  // Bits 21:16
    UINT32                                         :  2;  // Bits 23:22
    UINT32 tWRWR_dd                                :  6;  // Bits 29:24
    UINT32                                         :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCSCHEDS_CR_TC_WRWR_STRUCT;

typedef union {
  struct {
    UINT32 DRAM_technology                         :  2;  // Bits 1:0
    UINT32 CMD_stretch                             :  2;  // Bits 3:2
    UINT32 N_to_1_ratio                            :  3;  // Bits 6:4
    UINT32                                         :  1;  // Bits 7:7
    UINT32 Address_mirror                          :  2;  // Bits 9:8
    UINT32 x8_device                               :  2;  // Bits 11:10
    UINT32 tCPDED                                  :  3;  // Bits 14:12
    UINT32 LPDDR_2N_CS_MRW                         :  1;  // Bits 15:15
    UINT32 reset_on_command                        :  4;  // Bits 19:16
    UINT32 reset_delay                             :  3;  // Bits 22:20
    UINT32 cmd_3st                                 :  1;  // Bits 23:23
    UINT32 ck_to_cke                               :  3;  // Bits 26:24
    UINT32 enable_odt_matrix                       :  1;  // Bits 27:27
    UINT32 ddr_probeless_low_frequency             :  1;  // Bits 28:28
    UINT32 tCAL                                    :  3;  // Bits 31:29
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCSCHEDS_CR_SC_GS_CFG_STRUCT;

typedef union {
  struct {
    UINT32 Rank_0_latency                          :  7;  // Bits 6:0
    UINT32                                         :  1;  // Bits 7:7
    UINT32 Rank_1_latency                          :  7;  // Bits 14:8
    UINT32                                         :  1;  // Bits 15:15
    UINT32 Rank_2_latency                          :  7;  // Bits 22:16
    UINT32                                         :  1;  // Bits 23:23
    UINT32 Rank_3_latency                          :  7;  // Bits 30:24
    UINT32                                         :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCSCHEDS_CR_SC_ROUNDTRIP_LATENCY_STRUCT;

typedef union {
  struct {
    UINT32 Rank_0_flyby                            :  4;  // Bits 3:0
    UINT32 Rank_1_flyby                            :  4;  // Bits 7:4
    UINT32 Rank_2_flyby                            :  4;  // Bits 11:8
    UINT32 Rank_3_flyby                            :  4;  // Bits 15:12
    UINT32 IO_Latency_offset                       :  7;  // Bits 22:16
    UINT32                                         :  1;  // Bits 23:23
    UINT32 RFR_delay                               :  7;  // Bits 30:24
    UINT32                                         :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCSCHEDS_CR_SC_IO_LATENCY_STRUCT;

typedef union {
  struct {
    UINT32 dis_opp_cas                             :  1;  // Bits 0:0
    UINT32 dis_opp_is_cas                          :  1;  // Bits 1:1
    UINT32 dis_opp_ras                             :  1;  // Bits 2:2
    UINT32 dis_opp_is_ras                          :  1;  // Bits 3:3
    UINT32 dis_2c_byp                              :  1;  // Bits 4:4
    UINT32 dis_deprd_opt                           :  1;  // Bits 5:5
    UINT32 dis_pt_it                               :  1;  // Bits 6:6
    UINT32 dis_prcnt_ring                          :  1;  // Bits 7:7
    UINT32 dis_prcnt_sa                            :  1;  // Bits 8:8
    UINT32 dis_blkr_ph                             :  1;  // Bits 9:9
    UINT32 dis_blkr_pe                             :  1;  // Bits 10:10
    UINT32 dis_blkr_pm                             :  1;  // Bits 11:11
    UINT32 dis_odt                                 :  1;  // Bits 12:12
    UINT32 OE_alw_off                              :  1;  // Bits 13:13
    UINT32 block_rpq                               :  1;  // Bits 14:14
    UINT32 block_ipq                               :  1;  // Bits 15:15
    UINT32 block_wpq                               :  1;  // Bits 16:16
    UINT32 dis_zq                                  :  1;  // Bits 17:17
    UINT32 dis_tt                                  :  1;  // Bits 18:18
    UINT32 dis_opp_ref                             :  1;  // Bits 19:19
    UINT32 long_zq                                 :  1;  // Bits 20:20
    UINT32 dis_srx_zq                              :  1;  // Bits 21:21
    UINT32 serialize_zq                            :  1;  // Bits 22:22
    UINT32 zq_fast_exec                            :  1;  // Bits 23:23
    UINT32 dis_DriveNop                            :  1;  // Bits 24:24
    UINT32 dis_idle_preempt                        :  1;  // Bits 25:25
    UINT32 spare                                   :  4;  // Bits 29:26
    UINT32 dis_5cyc_read_gap                       :  1;  // Bits 30:30
    UINT32 dis_clk_gate                            :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCSCHEDS_CR_SCHED_CBIT_STRUCT;

typedef union {
  struct {
    UINT32 dis_srx_mr4                             :  1;  // Bits 0:0
    UINT32 dis_ck_tristate                         :  1;  // Bits 1:1
    UINT32 dis_burst_ref_limit                     :  1;  // Bits 2:2
    UINT32 dis_bus_retain                          :  1;  // Bits 3:3
    UINT32 dis_async_odt                           :  1;  // Bits 4:4
    UINT32 dis_SRX_reset                           :  1;  // Bits 5:5
    UINT32 dis_tcwl5_2qclk_add                     :  1;  // Bits 6:6
    UINT32 dis_SRX_MRS_MR4                         :  1;  // Bits 7:7
    UINT32 dis_opp_ref_idle_delay                  :  1;  // Bits 8:8
    UINT32 dis_ignore_1st_trefi                    :  1;  // Bits 9:9
    UINT32 echo_mask                               :  6;  // Bits 15:10
    UINT32 spare                                   :  16;  // Bits 31:16
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCSCHEDS_CR_SCHED_SECOND_CBIT_STRUCT;

typedef union {
  struct {
    UINT32 WDAR                                    :  1;  // Bits 0:0
    UINT32 WDB_Block_En                            :  1;  // Bits 1:1
    UINT32                                         :  2;  // Bits 3:2
    UINT32 force_rcv_en                            :  1;  // Bits 4:4
    UINT32                                         :  3;  // Bits 7:5
    UINT32 DDR_QUAL                                :  2;  // Bits 9:8
    UINT32 QUAL_Delay                              :  5;  // Bits 14:10
    UINT32 QUAL_Length                             :  2;  // Bits 16:15
    UINT32 dft_block_enable                        :  1;  // Bits 17:17
    UINT32                                         :  6;  // Bits 23:18
    UINT32 Stretch_mode                            :  2;  // Bits 25:24
    UINT32 STF                                     :  3;  // Bits 28:26
    UINT32                                         :  3;  // Bits 31:29
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCSCHEDS_CR_DFT_MISC_STRUCT;

typedef union {
  struct {
    UINT32 ECC_Inject                              :  3;  // Bits 2:0
    UINT32                                         :  1;  // Bits 3:3
    UINT32 ECC_correction_disable                  :  1;  // Bits 4:4
    UINT32                                         :  3;  // Bits 7:5
    UINT32 DIS_MCA_LOG                             :  1;  // Bits 8:8
    UINT32 DIS_PCH_EVENT                           :  1;  // Bits 9:9
    UINT32 DIS_RCH_POISON                          :  1;  // Bits 10:10
    UINT32 DIS_RCH_ERROR                           :  1;  // Bits 11:11
    UINT32                                         :  4;  // Bits 15:12
    UINT32 ECC_trigger                             :  2;  // Bits 17:16
    UINT32                                         :  14;  // Bits 31:18
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCSCHEDS_CR_ECC_DFT_STRUCT;

typedef union {
  struct {
    UINT32 Ring                                    :  10;  // Bits 9:0
    UINT32                                         :  6;  // Bits 15:10
    UINT32 SA                                      :  10;  // Bits 25:16
    UINT32                                         :  6;  // Bits 31:26
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCSCHEDS_CR_SC_PR_CNT_CONFIG_STRUCT;

typedef union {
  struct {
    UINT32 PCIT                                    :  8;  // Bits 7:0
    UINT32                                         :  8;  // Bits 15:8
    UINT32 PCIT_GT                                 :  8;  // Bits 23:16
    UINT32                                         :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCSCHEDS_CR_SC_PCIT_STRUCT;

typedef union {
  struct {
    UINT32 PDWN_idle_counter                       :  12;  // Bits 11:0
    UINT32 APD                                     :  1;  // Bits 12:12
    UINT32 PPD                                     :  1;  // Bits 13:13
    UINT32 Slow_Exit                               :  1;  // Bits 14:14
    UINT32 Global_PD                               :  1;  // Bits 15:15
    UINT32 TT_idle_counter                         :  8;  // Bits 23:16
    UINT32 dis_cke_tt                              :  1;  // Bits 24:24
    UINT32                                         :  7;  // Bits 31:25
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCSCHEDS_CR_PM_PDWN_CONFIG_STRUCT;

typedef union {
  struct {
    UINT32 Dis_Opp_rd                              :  1;  // Bits 0:0
    UINT32 ACT_Enable                              :  1;  // Bits 1:1
    UINT32 PRE_Enable                              :  1;  // Bits 2:2
    UINT32 MAX_RPQ_CAS                             :  4;  // Bits 6:3
    UINT32                                         :  25;  // Bits 31:7
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCSCHEDS_CR_WMM_READ_CONFIG_STRUCT;

typedef union {
  struct {
    UINT32 CERRSTS                                 :  1;  // Bits 0:0
    UINT32 MERRSTS                                 :  1;  // Bits 1:1
    UINT32                                         :  14;  // Bits 15:2
    UINT32 ERRSYND                                 :  8;  // Bits 23:16
    UINT32 ERRCHUNK                                :  3;  // Bits 26:24
    UINT32 ERRRANK                                 :  2;  // Bits 28:27
    UINT32 ERRBANK                                 :  3;  // Bits 31:29
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCSCHEDS_CR_ECCERRLOG0_STRUCT;

typedef union {
  struct {
    UINT32 ERRROW                                  :  17;  // Bits 16:0
    UINT32 ERRCOL                                  :  11;  // Bits 27:17
    UINT32 ERRBANKGROUP                            :  2;  // Bits 29:28
    UINT32                                         :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCSCHEDS_CR_ECCERRLOG1_STRUCT;

typedef union {
  struct {
    UINT32 EN_CLK                                  :  1;  // Bits 0:0
    UINT32 L0_DATA_BYTE_SEL                        :  7;  // Bits 7:1
    UINT32 L0_BYP_SEL                              :  1;  // Bits 8:8
    UINT32 L1_DATA_BYTE_SEL                        :  7;  // Bits 15:9
    UINT32 L1_BYP_SEL                              :  1;  // Bits 16:16
    UINT32                                         :  10;  // Bits 26:17
    UINT32 PATGENMODE                              :  3;  // Bits 29:27
    UINT32                                         :  1;  // Bits 30:30
    UINT32 VORANGE                                 :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCSCHEDS_CR_VISA_CTL_MCSCHEDS_STRUCT;

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
} MCSCHEDS_CR_VISA_XBAR_MCSCHEDS_STRUCT;

typedef union {
  struct {
    UINT32 RPQ_disable                             :  22;  // Bits 21:0
    UINT32                                         :  10;  // Bits 31:22
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCSCHEDS_CR_QUEUE_ENTRY_DISABLE_RPQ_STRUCT;

typedef union {
  struct {
    UINT32 IPQ_disable                             :  10;  // Bits 9:0
    UINT32                                         :  22;  // Bits 31:10
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCSCHEDS_CR_QUEUE_ENTRY_DISABLE_IPQ_STRUCT;

typedef union {
  struct {
    UINT32 WPQ_disableLow                          :  32;  // Bits 31:0
    UINT32 WPQ_disableHigh                         :  32;  // Bits 63:32
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} MCSCHEDS_CR_QUEUE_ENTRY_DISABLE_WPQ_STRUCT;

typedef union {
  struct {
    UINT32 WMM_entry_wm                            :  7;  // Bits 6:0
    UINT32                                         :  1;  // Bits 7:7
    UINT32 WMM_exit_wm                             :  7;  // Bits 14:8
    UINT32                                         :  1;  // Bits 15:15
    UINT32 WIM_wm                                  :  7;  // Bits 22:16
    UINT32                                         :  1;  // Bits 23:23
    UINT32 EDRAM_scrub_wm                          :  7;  // Bits 30:24
    UINT32                                         :  1;  // Bits 31:31
    UINT32 Read_CAS_count                          :  8;  // Bits 39:32
    UINT32 Write_CAS_count                         :  8;  // Bits 47:40
    UINT32 Write_CAS_count_for_VC1                 :  8;  // Bits 55:48
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} MCSCHEDS_CR_SC_WDBWM_STRUCT;

typedef union {
  struct {
    UINT32 ODT_read_duration                       :  3;  // Bits 2:0
    UINT32                                         :  1;  // Bits 3:3
    UINT32 ODT_Read_Delay                          :  3;  // Bits 6:4
    UINT32                                         :  1;  // Bits 7:7
    UINT32 ODT_write_duration                      :  3;  // Bits 10:8
    UINT32                                         :  1;  // Bits 11:11
    UINT32 ODT_Write_Delay                         :  3;  // Bits 14:12
    UINT32 Write_Early_ODT                         :  1;  // Bits 15:15
    UINT32 tCL                                     :  5;  // Bits 20:16
    UINT32 tCWL                                    :  5;  // Bits 25:21
    UINT32 tAONPD                                  :  5;  // Bits 30:26
    UINT32 ODT_Always_Rank0                        :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCSCHEDS_CR_TC_ODT_STRUCT;

typedef union {
  struct {
    UINT32 Spare_RW                                :  6;  // Bits 5:0
    UINT32 cmd_delay_counter                       :  4;  // Bits 9:6
    UINT32 cmd_delay_disable                       :  1;  // Bits 10:10
    UINT32 cke_delay_counter                       :  4;  // Bits 14:11
    UINT32 cke_delay_disable                       :  1;  // Bits 15:15
    UINT32 Spare_RW_V                              :  16;  // Bits 31:16
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCSCHEDS_CR_MCSCHEDS_SPARE_STRUCT;

typedef union {
  struct {
    UINT32 shift_16                                :  1;  // Bits 0:0
    UINT32 clken_pulse_mode                        :  1;  // Bits 1:1
    UINT32 reg_clken_mode                          :  1;  // Bits 2:2
    UINT32 reg_clken                               :  1;  // Bits 3:3
    UINT32 feedback_en                             :  1;  // Bits 4:4
    UINT32 event_mode                              :  1;  // Bits 5:5
    UINT32 lfsr_reset                              :  1;  // Bits 6:6
    UINT32 sdo_en                                  :  1;  // Bits 7:7
    UINT32                                         :  8;  // Bits 15:8
    UINT32 cr_rd_data                              :  16;  // Bits 31:16
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCSCHEDS_CR_MC_MISR_STRUCT;

typedef union {
  struct {
    UINT32 Read_Rank_0                             :  4;  // Bits 3:0
    UINT32 Read_Rank_1                             :  4;  // Bits 7:4
    UINT32 Read_Rank_2                             :  4;  // Bits 11:8
    UINT32 Read_Rank_3                             :  4;  // Bits 15:12
    UINT32 Write_Rank_0                            :  4;  // Bits 19:16
    UINT32 Write_Rank_1                            :  4;  // Bits 23:20
    UINT32 Write_Rank_2                            :  4;  // Bits 27:24
    UINT32 Write_Rank_3                            :  4;  // Bits 31:28
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCSCHEDS_CR_SC_ODT_MATRIX_STRUCT;

typedef union {
  struct {
    UINT32 dft_block_cycles                        :  16;  // Bits 15:0
    UINT32 dft_nonblock_cycles                     :  16;  // Bits 31:16
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCSCHEDS_CR_DFT_BLOCK_STRUCT;

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
} MCSCHEDS_CR_VISA_SLIDE_MCSCHEDS_STRUCT;

typedef union {
  struct {
    UINT32 Mux0_Control                            :  2;  // Bits 1:0
    UINT32                                         :  1;  // Bits 2:2
    UINT32 Mux1_Control                            :  2;  // Bits 4:3
    UINT32                                         :  1;  // Bits 5:5
    UINT32 Mux2_Control                            :  2;  // Bits 7:6
    UINT32 LFSR_Type                               :  3;  // Bits 10:8
    UINT32 Chaining_LFSR                           :  1;  // Bits 11:11
    UINT32                                         :  2;  // Bits 13:12
    UINT32 ECC_Replace_Byte_Control                :  1;  // Bits 14:14
    UINT32 ECC_Data_Source_Sel                     :  1;  // Bits 15:15
    UINT32 Save_LFSR_Seed_Rate                     :  8;  // Bits 23:16
    UINT32 Reload_LFSR_Seed_Rate                   :  5;  // Bits 28:24
    UINT32                                         :  2;  // Bits 30:29
    UINT32 Reload_Save_LFSR_Seed_Rate_Mode         :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCSCHEDS_CR_REUT_CH_PAT_WDB_CL_MUX_CFG_STRUCT;

typedef union {
  struct {
    UINT32 Pattern_Buffer                          :  24;  // Bits 23:0
    UINT32                                         :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCSCHEDS_CR_REUT_CH_PAT_WDB_CL_MUX_PB_WR_0_STRUCT;

typedef union {
  struct {
    UINT32 Pattern_Buffer                          :  24;  // Bits 23:0
    UINT32                                         :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCSCHEDS_CR_REUT_CH_PAT_WDB_CL_MUX_PB_WR_1_STRUCT;

typedef union {
  struct {
    UINT32 Pattern_Buffer                          :  24;  // Bits 23:0
    UINT32                                         :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCSCHEDS_CR_REUT_CH_PAT_WDB_CL_MUX_PB_WR_2_STRUCT;

typedef union {
  struct {
    UINT32 Pattern_Buffer                          :  24;  // Bits 23:0
    UINT32                                         :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCSCHEDS_CR_REUT_CH_PAT_WDB_CL_MUX_PB_RD_0_STRUCT;

typedef union {
  struct {
    UINT32 Pattern_Buffer                          :  24;  // Bits 23:0
    UINT32                                         :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCSCHEDS_CR_REUT_CH_PAT_WDB_CL_MUX_PB_RD_1_STRUCT;

typedef union {
  struct {
    UINT32 Pattern_Buffer                          :  24;  // Bits 23:0
    UINT32                                         :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCSCHEDS_CR_REUT_CH_PAT_WDB_CL_MUX_PB_RD_2_STRUCT;

typedef union {
  struct {
    UINT32 Pattern_Buffer                          :  24;  // Bits 23:0
    UINT32                                         :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCSCHEDS_CR_REUT_CH_PAT_WDB_CL_MUX_PB_STATUS_WR_0_STRUCT;

typedef union {
  struct {
    UINT32 Pattern_Buffer                          :  24;  // Bits 23:0
    UINT32                                         :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCSCHEDS_CR_REUT_CH_PAT_WDB_CL_MUX_PB_STATUS_WR_1_STRUCT;

typedef union {
  struct {
    UINT32 Pattern_Buffer                          :  24;  // Bits 23:0
    UINT32                                         :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCSCHEDS_CR_REUT_CH_PAT_WDB_CL_MUX_PB_STATUS_WR_2_STRUCT;

typedef union {
  struct {
    UINT32 Pattern_Buffer                          :  24;  // Bits 23:0
    UINT32                                         :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCSCHEDS_CR_REUT_CH_PAT_WDB_CL_MUX_PB_STATUS_RD_0_STRUCT;

typedef union {
  struct {
    UINT32 Pattern_Buffer                          :  24;  // Bits 23:0
    UINT32                                         :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCSCHEDS_CR_REUT_CH_PAT_WDB_CL_MUX_PB_STATUS_RD_1_STRUCT;

typedef union {
  struct {
    UINT32 Pattern_Buffer                          :  24;  // Bits 23:0
    UINT32                                         :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCSCHEDS_CR_REUT_CH_PAT_WDB_CL_MUX_PB_STATUS_RD_2_STRUCT;

typedef union {
  struct {
    UINT32 L_data_select                           :  1;  // Bits 0:0
    UINT32 Enable_Sweep_Frequency                  :  1;  // Bits 1:1
    UINT32                                         :  6;  // Bits 7:2
    UINT32 L_counter                               :  8;  // Bits 15:8
    UINT32 M_counter                               :  8;  // Bits 23:16
    UINT32 N_counter                               :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCSCHEDS_CR_REUT_CH_PAT_WDB_CL_MUX_LMN_STRUCT;

typedef union {
  struct {
    UINT32 Write_Address_as_Data                   :  1;  // Bits 0:0
    UINT32 Read_Address_as_Data                    :  1;  // Bits 1:1
    UINT32                                         :  30;  // Bits 31:2
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCSCHEDS_CR_REUT_CH_PAT_WDB_ADDRESS_AS_DATA_CTRL_STRUCT;

typedef union {
  struct {
    UINT32 ECC_Inv_or_DC_Enable                    :  8;  // Bits 7:0
    UINT32                                         :  8;  // Bits 15:8
    UINT32 Inv_or_DC_Shift_Rate                    :  4;  // Bits 19:16
    UINT32 DC_Polarity_Control                     :  1;  // Bits 20:20
    UINT32                                         :  9;  // Bits 29:21
    UINT32 Inv_or_DC_Control                       :  1;  // Bits 30:30
    UINT32 Inv_or_DC_Shift_Enable                  :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCSCHEDS_CR_REUT_CH_PAT_WDB_INV_STRUCT;

typedef union {
  struct {
    UINT32 Data_Inv_or_DC_EnableLow                :  32;  // Bits 31:0
    UINT32 Data_Inv_or_DC_EnableHigh               :  32;  // Bits 63:32
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} MCSCHEDS_CR_REUT_CH_PAT_WDB_DATA_INV_STRUCT;

typedef union {
  struct {
    UINT32 CKE_Override                            :  4;  // Bits 3:0
    UINT32                                         :  4;  // Bits 7:4
    UINT32 CKE_En_Start_Test_Sync                  :  1;  // Bits 8:8
    UINT32                                         :  7;  // Bits 15:9
    UINT32 CKE_On                                  :  4;  // Bits 19:16
    UINT32                                         :  12;  // Bits 31:20
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCSCHEDS_CR_REUT_CH_MISC_CKE_CTRL_STRUCT;

typedef union {
  struct {
    UINT32 ODT_Override                            :  4;  // Bits 3:0
    UINT32                                         :  12;  // Bits 15:4
    UINT32 ODT_On                                  :  4;  // Bits 19:16
    UINT32                                         :  11;  // Bits 30:20
    UINT32 MPR_Train_DDR_On                        :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCSCHEDS_CR_REUT_CH_MISC_ODT_CTRL_STRUCT;

typedef union {
  struct {
    UINT32 Enable_CADB_on_Deselect                 :  1;  // Bits 0:0
    UINT32 Enable_CADB_Always_On                   :  1;  // Bits 1:1
    UINT32 CMD_Deselect_Start                      :  4;  // Bits 5:2
    UINT32 CMD_Deselect_Stop                       :  4;  // Bits 9:6
    UINT32 Lane_Deselect_Enable                    :  4;  // Bits 13:10
    UINT32 CAS_Select_Enable                       :  2;  // Bits 15:14
    UINT32 ACT_Select_Enable                       :  2;  // Bits 17:16
    UINT32 PRE_Select_Enable                       :  2;  // Bits 19:18
    UINT32 Save_Current_Seed                       :  4;  // Bits 23:20
    UINT32 Reload_Starting_Seed                    :  4;  // Bits 27:24
    UINT32                                         :  4;  // Bits 31:28
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCSCHEDS_CR_REUT_CH_PAT_CADB_CTRL_STRUCT;

typedef union {
  struct {
    UINT32 MRS_Gap                                 :  3;  // Bits 2:0
    UINT32                                         :  4;  // Bits 6:3
    UINT32 MRS_Gap_Scale                           :  1;  // Bits 7:7
    UINT32 CADB_MRS_Start_Pointer                  :  3;  // Bits 10:8
    UINT32                                         :  5;  // Bits 15:11
    UINT32 CADB_MRS_End_Pointer                    :  3;  // Bits 18:16
    UINT32                                         :  5;  // Bits 23:19
    UINT32 CADB_MRS_Current_Pointer                :  3;  // Bits 26:24
    UINT32                                         :  1;  // Bits 27:27
    UINT32 MRS_Wait_Scale                          :  1;  // Bits 28:28
    UINT32 MRS_Wait                                :  3;  // Bits 31:29
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCSCHEDS_CR_REUT_CH_PAT_CADB_MRS_STRUCT;

typedef union {
  struct {
    UINT32 Mux0_Control                            :  2;  // Bits 1:0
    UINT32                                         :  2;  // Bits 3:2
    UINT32 Mux1_Control                            :  2;  // Bits 5:4
    UINT32                                         :  2;  // Bits 7:6
    UINT32 Mux2_Control                            :  2;  // Bits 9:8
    UINT32                                         :  6;  // Bits 15:10
    UINT32 Select_Mux0_Control                     :  2;  // Bits 17:16
    UINT32                                         :  2;  // Bits 19:18
    UINT32 Select_Mux1_Control                     :  2;  // Bits 21:20
    UINT32                                         :  2;  // Bits 23:22
    UINT32 Select_Mux2_Control                     :  2;  // Bits 25:24
    UINT32                                         :  2;  // Bits 27:26
    UINT32 LFSR_Type                               :  3;  // Bits 30:28
    UINT32 Chaining_LFSR                           :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCSCHEDS_CR_REUT_CH_PAT_CADB_MUX_CTRL_STRUCT;

typedef union {
  struct {
    UINT32 Pattern_Buffer                          :  24;  // Bits 23:0
    UINT32                                         :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCSCHEDS_CR_REUT_CH_PAT_CADB_MUX_PB_0_STRUCT;

typedef union {
  struct {
    UINT32 Pattern_Buffer                          :  24;  // Bits 23:0
    UINT32                                         :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCSCHEDS_CR_REUT_CH_PAT_CADB_MUX_PB_1_STRUCT;

typedef union {
  struct {
    UINT32 Pattern_Buffer                          :  24;  // Bits 23:0
    UINT32                                         :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCSCHEDS_CR_REUT_CH_PAT_CADB_MUX_PB_2_STRUCT;

typedef union {
  struct {
    UINT32 Pattern_Buffer                          :  24;  // Bits 23:0
    UINT32                                         :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCSCHEDS_CR_REUT_CH_PAT_CADB_SEL_MUX_PB_0_STRUCT;

typedef union {
  struct {
    UINT32 Pattern_Buffer                          :  24;  // Bits 23:0
    UINT32                                         :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCSCHEDS_CR_REUT_CH_PAT_CADB_SEL_MUX_PB_1_STRUCT;

typedef union {
  struct {
    UINT32 Pattern_Buffer                          :  24;  // Bits 23:0
    UINT32                                         :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCSCHEDS_CR_REUT_CH_PAT_CADB_SEL_MUX_PB_2_STRUCT;

typedef union {
  struct {
    UINT32 L_data_select                           :  1;  // Bits 0:0
    UINT32 Enable_Sweep_Frequency                  :  1;  // Bits 1:1
    UINT32                                         :  6;  // Bits 7:2
    UINT32 L_counter                               :  8;  // Bits 15:8
    UINT32 M_counter                               :  8;  // Bits 23:16
    UINT32 N_counter                               :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCSCHEDS_CR_REUT_CH_PAT_CADB_CL_MUX_LMN_STRUCT;

typedef union {
  struct {
    UINT32 CADB_Write_Pointer                      :  3;  // Bits 2:0
    UINT32                                         :  1;  // Bits 3:3
    UINT32 Write_Enable                            :  1;  // Bits 4:4
    UINT32                                         :  27;  // Bits 31:5
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCSCHEDS_CR_REUT_CH_PAT_CADB_WRITE_POINTER_STRUCT;

typedef union {
  struct {
    UINT32 CADB_Data_Address                       :  17;  // Bits 16:0
    UINT32                                         :  7;  // Bits 23:17
    UINT32 CADB_Data_Bank                          :  4;  // Bits 27:24
    UINT32                                         :  4;  // Bits 31:28
    UINT32 CADB_Data_CS                            :  4;  // Bits 35:32
    UINT32                                         :  4;  // Bits 39:36
    UINT32 CADB_Data_Control                       :  4;  // Bits 43:40
    UINT32                                         :  4;  // Bits 47:44
    UINT32 CADB_Data_ODT                           :  4;  // Bits 51:48
    UINT32                                         :  4;  // Bits 55:52
    UINT32 CADB_Data_CKE                           :  4;  // Bits 59:56
    UINT32                                         :  3;  // Bits 62:60
    UINT32 CADB_Data_Parity_inv                    :  1;  // Bits 63:63
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} MCSCHEDS_CR_REUT_CH_PAT_CADB_PROG_STRUCT;

typedef union {
  struct {
    UINT32 Loopcount_Limit                         :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCSCHEDS_CR_REUT_CH_PAT_CADB_MRS_LOOPCOUNT_LIMIT_STRUCT;

typedef union {
  struct {
    UINT32 WDB_Increment_Rate                      :  6;  // Bits 5:0
    UINT32 WDB_Increment_Scale                     :  1;  // Bits 6:6
    UINT32                                         :  1;  // Bits 7:7
    UINT32 WDB_Start_Pointer                       :  6;  // Bits 13:8
    UINT32                                         :  2;  // Bits 15:14
    UINT32 WDB_End_Pointer                         :  6;  // Bits 21:16
    UINT32                                         :  10;  // Bits 31:22
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCMNTS_CR_REUT_CH_PAT_WDB_CL_CTRL_STRUCT;

typedef union {
  struct {
    UINT32 Refresh_Rank_Mask                       :  4;  // Bits 3:0
    UINT32                                         :  4;  // Bits 7:4
    UINT32 RefZQ_En_Start_Test_Sync                :  1;  // Bits 8:8
    UINT32                                         :  22;  // Bits 30:9
    UINT32 Panic_Refresh_Only                      :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCMNTS_CR_REUT_CH_MISC_REFRESH_CTRL_STRUCT;

typedef union {
  struct {
    UINT32 ZQ_Rank_Mask                            :  4;  // Bits 3:0
    UINT32                                         :  27;  // Bits 30:4
    UINT32 Always_Do_ZQ                            :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCMNTS_CR_REUT_CH_MISC_ZQ_CTRL_STRUCT;

typedef union {
  struct {
    UINT32 Rank_0_width                            :  2;  // Bits 1:0
    UINT32 Rank_1_width                            :  2;  // Bits 3:2
    UINT32 Rank_2_width                            :  2;  // Bits 5:4
    UINT32 Rank_3_width                            :  2;  // Bits 7:6
    UINT32 MR4_PERIOD                              :  16;  // Bits 23:8
    UINT32 DDR4_TS_readout_en                      :  1;  // Bits 24:24
    UINT32                                         :  7;  // Bits 31:25
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCMNTS_CR_DDR_MR_PARAMS_STRUCT;

typedef union {
  struct {
    UINT32 Address                                 :  8;  // Bits 7:0
    UINT32 Data                                    :  8;  // Bits 15:8
    UINT32 Rank                                    :  2;  // Bits 17:16
    UINT32 Command                                 :  2;  // Bits 19:18
    UINT32 DRAM_mask                               :  9;  // Bits 28:20
    UINT32 Assume_idle                             :  1;  // Bits 29:29
    UINT32 DDR4_MA13                               :  1;  // Bits 30:30
    UINT32 Busy                                    :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCMNTS_CR_DDR_MR_COMMAND_STRUCT;

typedef union {
  struct {
    UINT32 Device_0                                :  8;  // Bits 7:0
    UINT32 Device_1                                :  8;  // Bits 15:8
    UINT32 Device_2                                :  8;  // Bits 23:16
    UINT32 Device_3                                :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCMNTS_CR_DDR_MR_RESULT_0_STRUCT;

typedef union {
  struct {
    UINT32 Device_4                                :  8;  // Bits 7:0
    UINT32 Device_5                                :  8;  // Bits 15:8
    UINT32 Device_6                                :  8;  // Bits 23:16
    UINT32 Device_7                                :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCMNTS_CR_DDR_MR_RESULT_1_STRUCT;

typedef union {
  struct {
    UINT32 Device_8                                :  8;  // Bits 7:0
    UINT32                                         :  24;  // Bits 31:8
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCMNTS_CR_DDR_MR_RESULT_2_STRUCT;

typedef union {
  struct {
    UINT32 Rank_0                                  :  3;  // Bits 2:0
    UINT32                                         :  5;  // Bits 7:3
    UINT32 Rank_1                                  :  3;  // Bits 10:8
    UINT32                                         :  5;  // Bits 15:11
    UINT32 Rank_2                                  :  3;  // Bits 18:16
    UINT32                                         :  5;  // Bits 23:19
    UINT32 Rank_3                                  :  3;  // Bits 26:24
    UINT32                                         :  5;  // Bits 31:27
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCMNTS_CR_LPDDR_MR4_RANK_TEMPERATURE_STRUCT;

typedef union {
  struct {
    UINT32 Rank_0                                  :  2;  // Bits 1:0
    UINT32                                         :  6;  // Bits 7:2
    UINT32 Rank_1                                  :  2;  // Bits 9:8
    UINT32                                         :  6;  // Bits 15:10
    UINT32 Rank_2                                  :  2;  // Bits 17:16
    UINT32                                         :  6;  // Bits 23:18
    UINT32 Rank_3                                  :  2;  // Bits 25:24
    UINT32                                         :  6;  // Bits 31:26
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCMNTS_CR_DDR4_MPR_RANK_TEMPERATURE_STRUCT;

typedef union {
  struct {
    UINT32 Bit_0                                   :  3;  // Bits 2:0
    UINT32                                         :  1;  // Bits 3:3
    UINT32 Bit_1                                   :  3;  // Bits 6:4
    UINT32                                         :  1;  // Bits 7:7
    UINT32 Bit_2                                   :  3;  // Bits 10:8
    UINT32                                         :  1;  // Bits 11:11
    UINT32 Bit_16                                  :  3;  // Bits 14:12
    UINT32                                         :  1;  // Bits 15:15
    UINT32 Bit_17                                  :  3;  // Bits 18:16
    UINT32                                         :  1;  // Bits 19:19
    UINT32 Bit_18                                  :  3;  // Bits 22:20
    UINT32                                         :  1;  // Bits 23:23
    UINT32 Byte_0                                  :  3;  // Bits 26:24
    UINT32                                         :  1;  // Bits 27:27
    UINT32 Byte_2                                  :  3;  // Bits 30:28
    UINT32                                         :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCMNTS_CR_DESWIZZLE_LOW_STRUCT;

typedef union {
  struct {
    UINT32 Bit_32                                  :  3;  // Bits 2:0
    UINT32                                         :  1;  // Bits 3:3
    UINT32 Bit_33                                  :  3;  // Bits 6:4
    UINT32                                         :  1;  // Bits 7:7
    UINT32 Bit_34                                  :  3;  // Bits 10:8
    UINT32                                         :  1;  // Bits 11:11
    UINT32 Bit_48                                  :  3;  // Bits 14:12
    UINT32                                         :  1;  // Bits 15:15
    UINT32 Bit_49                                  :  3;  // Bits 18:16
    UINT32                                         :  1;  // Bits 19:19
    UINT32 Bit_50                                  :  3;  // Bits 22:20
    UINT32                                         :  1;  // Bits 23:23
    UINT32 Byte_4                                  :  3;  // Bits 26:24
    UINT32                                         :  1;  // Bits 27:27
    UINT32 Byte_6                                  :  3;  // Bits 30:28
    UINT32                                         :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCMNTS_CR_DESWIZZLE_HIGH_STRUCT;

typedef union {
  struct {
    UINT32 OREF_RI                                 :  8;  // Bits 7:0
    UINT32 Refresh_HP_WM                           :  4;  // Bits 11:8
    UINT32 Refresh_panic_wm                        :  4;  // Bits 15:12
    UINT32                                         :  9;  // Bits 24:16
    UINT32 tREFIx9                                 :  7;  // Bits 31:25
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCMNTS_CR_TC_RFP_STRUCT;

typedef union {
  struct {
    UINT32 tREFI                                   :  16;  // Bits 15:0
    UINT32 tRFC                                    :  10;  // Bits 25:16
    UINT32                                         :  6;  // Bits 31:26
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCMNTS_CR_TC_RFTP_STRUCT;

typedef union {
  struct {
    UINT32 tXSDLL                                  :  12;  // Bits 11:0
    UINT32 tXS_offset                              :  4;  // Bits 15:12
    UINT32 tZQOPER                                 :  10;  // Bits 25:16
    UINT32 tMOD                                    :  5;  // Bits 30:26
    UINT32                                         :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCMNTS_CR_TC_SRFTP_STRUCT;

typedef union {
  struct {
    UINT32 Ref_Interval                            :  11;  // Bits 10:0
    UINT32 Ref_Stagger_En                          :  1;  // Bits 11:11
    UINT32 Ref_Stagger_Mode                        :  1;  // Bits 12:12
    UINT32 Disable_Stolen_Refresh                  :  1;  // Bits 13:13
    UINT32 En_Ref_Type_Display                     :  1;  // Bits 14:14
    UINT32                                         :  17;  // Bits 31:15
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCMNTS_CR_MC_REFRESH_STAGGER_STRUCT;

typedef union {
  struct {
    UINT32 ZQCS_period                             :  10;  // Bits 9:0
    UINT32 tZQCS                                   :  10;  // Bits 19:10
    UINT32                                         :  12;  // Bits 31:20
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCMNTS_CR_TC_ZQCAL_STRUCT;

typedef union {
  struct {
    UINT32 MR2_shaddow                             :  14;  // Bits 13:0
    UINT32 SRT_avail                               :  2;  // Bits 15:14
    UINT32                                         :  16;  // Bits 31:16
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCMNTS_CR_TC_MR2_SHADDOW_STRUCT;

typedef union {
  struct {
    UINT32 MR4_sh_low                              :  2;  // Bits 1:0
    UINT32                                         :  2;  // Bits 3:2
    UINT32 MR4_sh_high                             :  10;  // Bits 13:4
    UINT32                                         :  18;  // Bits 31:14
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCMNTS_CR_TC_MR4_SHADDOW_STRUCT;

typedef union {
  struct {
    UINT32 Rank_occupancy                          :  4;  // Bits 3:0
    UINT32 SRX_reset                               :  1;  // Bits 4:4
    UINT32                                         :  27;  // Bits 31:5
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCMNTS_CR_MC_INIT_STATE_STRUCT;

typedef union {
  struct {
    UINT32 VISAByteSel                             :  3;  // Bits 2:0
    UINT32                                         :  29;  // Bits 31:3
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCMNTS_CR_WDB_VISA_SEL_STRUCT;

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
} MCMNTS_CR_VISA_CTL_MCMNTS_STRUCT;

typedef union {
  struct {
    UINT32 DIMM0_IDLE_ENERGY                       :  6;  // Bits 5:0
    UINT32                                         :  2;  // Bits 7:6
    UINT32 DIMM1_IDLE_ENERGY                       :  6;  // Bits 13:8
    UINT32                                         :  18;  // Bits 31:14
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCMNTS_CR_PM_DIMM_IDLE_ENERGY_STRUCT;

typedef union {
  struct {
    UINT32 DIMM0_PD_ENERGY                         :  6;  // Bits 5:0
    UINT32                                         :  2;  // Bits 7:6
    UINT32 DIMM1_PD_ENERGY                         :  6;  // Bits 13:8
    UINT32                                         :  18;  // Bits 31:14
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCMNTS_CR_PM_DIMM_PD_ENERGY_STRUCT;

typedef union {
  struct {
    UINT32 DIMM0_ACT_ENERGY                        :  8;  // Bits 7:0
    UINT32 DIMM1_ACT_ENERGY                        :  8;  // Bits 15:8
    UINT32                                         :  16;  // Bits 31:16
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCMNTS_CR_PM_DIMM_ACT_ENERGY_STRUCT;

typedef union {
  struct {
    UINT32 DIMM0_RD_ENERGY                         :  8;  // Bits 7:0
    UINT32 DIMM1_RD_ENERGY                         :  8;  // Bits 15:8
    UINT32                                         :  16;  // Bits 31:16
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCMNTS_CR_PM_DIMM_RD_ENERGY_STRUCT;

typedef union {
  struct {
    UINT32 DIMM0_WR_ENERGY                         :  8;  // Bits 7:0
    UINT32 DIMM1_WR_ENERGY                         :  8;  // Bits 15:8
    UINT32                                         :  16;  // Bits 31:16
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCMNTS_CR_PM_DIMM_WR_ENERGY_STRUCT;

typedef union {
  struct {
    UINT32 Count                                   :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCMNTS_CR_ECC_INJECT_COUNT_STRUCT;

typedef union {
  struct {
    UINT32 D0R0                                    :  2;  // Bits 1:0
    UINT32 D0R1                                    :  2;  // Bits 3:2
    UINT32 D1R0                                    :  2;  // Bits 5:4
    UINT32 D1R1                                    :  2;  // Bits 7:6
    UINT32                                         :  23;  // Bits 30:8
    UINT32 Dec_WRD                                 :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCMNTS_CR_SC_WR_ADD_DELAY_STRUCT;

typedef union {
  struct {
    UINT32 ECC                                     :  8;  // Bits 7:0
    UINT32 RRD_DFT_Mode                            :  2;  // Bits 9:8
    UINT32 LFSR_Seed_Index                         :  5;  // Bits 14:10
    UINT32 Inversion_Mode                          :  1;  // Bits 15:15
    UINT32                                         :  16;  // Bits 31:16
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCMNTS_CR_READ_RETURN_DFT_STRUCT;

typedef union {
  struct {
    UINT32 FASTADDR                                :  12;  // Bits 11:0
    UINT32 RSVD                                    :  4;  // Bits 15:12
    UINT32 ADDREN                                  :  1;  // Bits 16:16
    UINT32 SEQEN                                   :  1;  // Bits 17:17
    UINT32 POL0                                    :  1;  // Bits 18:18
    UINT32 POL1                                    :  1;  // Bits 19:19
    UINT32 CMDA                                    :  4;  // Bits 23:20
    UINT32 CMDB                                    :  4;  // Bits 27:24
    UINT32 CMDDEL                                  :  4;  // Bits 31:28
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCMNTS_CR_DCLK_LDAT_PDAT_STRUCT;

typedef union {
  struct {
    UINT32 BANKSEL                                 :  4;  // Bits 3:0
    UINT32 ADDR_LIM                                :  1;  // Bits 4:4
    UINT32 ARRAYSEL                                :  5;  // Bits 9:5
    UINT32 CMP                                     :  1;  // Bits 10:10
    UINT32 REP                                     :  1;  // Bits 11:11
    UINT32 DWORD                                   :  4;  // Bits 15:12
    UINT32 MODE                                    :  2;  // Bits 17:16
    UINT32 MPMAP                                   :  4;  // Bits 21:18
    UINT32 RSVD                                    :  2;  // Bits 23:22
    UINT32 MPBOFFSET                               :  4;  // Bits 27:24
    UINT32 STAGE_EN                                :  1;  // Bits 28:28
    UINT32 SHADOW                                  :  2;  // Bits 30:29
    UINT32 RSVD1                                   :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCMNTS_CR_DCLK_LDAT_SDAT_STRUCT;

typedef union {
  struct {
    UINT32 DATOUT                                  :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCMNTS_CR_DCLK_LDAT_DATAOUT_STRUCT;

typedef union {
  struct {
    UINT32 DATIN                                   :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCMNTS_CR_DCLK_LDAT_DATAIN_0_STRUCT;

typedef union {
  struct {
    UINT32 FASTADDR                                :  12;  // Bits 11:0
    UINT32 RSVD                                    :  4;  // Bits 15:12
    UINT32 ADDREN                                  :  1;  // Bits 16:16
    UINT32 SEQEN                                   :  1;  // Bits 17:17
    UINT32 POL0                                    :  1;  // Bits 18:18
    UINT32 POL1                                    :  1;  // Bits 19:19
    UINT32 CMDA                                    :  4;  // Bits 23:20
    UINT32 CMDB                                    :  4;  // Bits 27:24
    UINT32 CMDDEL                                  :  4;  // Bits 31:28
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCMNTS_CR_QCLK_LDAT_PDAT_STRUCT;

typedef union {
  struct {
    UINT32 BANKSEL                                 :  4;  // Bits 3:0
    UINT32 ADDR_LIM                                :  1;  // Bits 4:4
    UINT32 ARRAYSEL                                :  5;  // Bits 9:5
    UINT32 CMP                                     :  1;  // Bits 10:10
    UINT32 REP                                     :  1;  // Bits 11:11
    UINT32 DWORD                                   :  4;  // Bits 15:12
    UINT32 MODE                                    :  2;  // Bits 17:16
    UINT32 MPMAP                                   :  4;  // Bits 21:18
    UINT32 RSVD                                    :  2;  // Bits 23:22
    UINT32 MPBOFFSET                               :  4;  // Bits 27:24
    UINT32 STAGE_EN                                :  1;  // Bits 28:28
    UINT32 SHADOW                                  :  2;  // Bits 30:29
    UINT32 RSVD1                                   :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCMNTS_CR_QCLK_LDAT_SDAT_STRUCT;

typedef union {
  struct {
    UINT32 DATOUT                                  :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCMNTS_CR_QCLK_LDAT_DATAOUT_STRUCT;

typedef union {
  struct {
    UINT32 DATIN                                   :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCMNTS_CR_QCLK_LDAT_DATAIN_0_STRUCT;

typedef union {
  struct {
    UINT32 DATIN                                   :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCMNTS_CR_QCLK_LDAT_DATAIN_1_STRUCT;

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
} MCMNTS_CR_VISA_SLIDE_MCMNTS_STRUCT;

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
} MCMNTS_CR_VISA_XBAR_MCMNTS_STRUCT;

typedef union {
  struct {
    UINT32 Count                                   :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCMNTS_CR_PM_ALL_RANKS_CKE_LOW_COUNT_STRUCT;

typedef union {
  struct {
    UINT32 Valid                                   :  1;  // Bits 0:0
    UINT32 Rank                                    :  2;  // Bits 2:1
    UINT32 Group                                   :  2;  // Bits 4:3
    UINT32 Bank                                    :  2;  // Bits 6:5
    UINT32 Row                                     :  17;  // Bits 23:7
    UINT32                                         :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCMNTS_CR_RH_ADDRESS_STRUCT;

typedef union {
  struct {
    UINT32 LFSR_0                                  :  32;  // Bits 31:0
    UINT32 LFSR_1                                  :  32;  // Bits 63:32
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} MCMNTS_CR_RH_LFSR_STRUCT;

typedef union {
  struct {
    UINT32 Mode                                    :  4;  // Bits 3:0
    UINT32 Always_block_rank                       :  1;  // Bits 4:4
    UINT32 Always_PREALL                           :  1;  // Bits 5:5
    UINT32 LFSR_0_MASK                             :  4;  // Bits 9:6
    UINT32 LFSR_1_MASK                             :  4;  // Bits 13:10
    UINT32 MA3_Swizzling                           :  2;  // Bits 15:14
    UINT32 TRR_wait_cycles                         :  6;  // Bits 21:16
    UINT32 Always_calc_victim_row                  :  1;  // Bits 22:22
    UINT32 MA0_Swizzling                           :  2;  // Bits 24:23
    UINT32                                         :  7;  // Bits 31:25
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCMNTS_CR_RH_CONTROL_STRUCT;

typedef union {
  struct {
    UINT32 Counter_Status                          :  23;  // Bits 22:0
    UINT32                                         :  9;  // Bits 31:23
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCMNTS_CR_REUT_CH_ERR_COUNTER_STATUS_0_STRUCT;

typedef union {
  struct {
    UINT32 Counter_Status                          :  23;  // Bits 22:0
    UINT32                                         :  9;  // Bits 31:23
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCMNTS_CR_REUT_CH_ERR_COUNTER_STATUS_1_STRUCT;

typedef union {
  struct {
    UINT32 Counter_Status                          :  23;  // Bits 22:0
    UINT32                                         :  9;  // Bits 31:23
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCMNTS_CR_REUT_CH_ERR_COUNTER_STATUS_2_STRUCT;

typedef union {
  struct {
    UINT32 Counter_Status                          :  23;  // Bits 22:0
    UINT32                                         :  9;  // Bits 31:23
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCMNTS_CR_REUT_CH_ERR_COUNTER_STATUS_3_STRUCT;

typedef union {
  struct {
    UINT32 Counter_Status                          :  23;  // Bits 22:0
    UINT32                                         :  9;  // Bits 31:23
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCMNTS_CR_REUT_CH_ERR_COUNTER_STATUS_4_STRUCT;

typedef union {
  struct {
    UINT32 Counter_Status                          :  23;  // Bits 22:0
    UINT32                                         :  9;  // Bits 31:23
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCMNTS_CR_REUT_CH_ERR_COUNTER_STATUS_5_STRUCT;

typedef union {
  struct {
    UINT32 Counter_Status                          :  23;  // Bits 22:0
    UINT32                                         :  9;  // Bits 31:23
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCMNTS_CR_REUT_CH_ERR_COUNTER_STATUS_6_STRUCT;

typedef union {
  struct {
    UINT32 Counter_Status                          :  23;  // Bits 22:0
    UINT32                                         :  9;  // Bits 31:23
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCMNTS_CR_REUT_CH_ERR_COUNTER_STATUS_7_STRUCT;

typedef union {
  struct {
    UINT32 Counter_Status                          :  23;  // Bits 22:0
    UINT32                                         :  9;  // Bits 31:23
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCMNTS_CR_REUT_CH_ERR_COUNTER_STATUS_8_STRUCT;

typedef union {
  struct {
    UINT32 Stop_on_Nth_Error                       :  6;  // Bits 5:0
    UINT32                                         :  2;  // Bits 7:6
    UINT32 Stop_on_CA_ALERT                        :  1;  // Bits 8:8
    UINT32                                         :  3;  // Bits 11:9
    UINT32 Stop_On_Error_Control                   :  2;  // Bits 13:12
    UINT32                                         :  2;  // Bits 15:14
    UINT32 Selective_Error_Enable_Chunk            :  8;  // Bits 23:16
    UINT32 Selective_Error_Enable_Cacheline        :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCMNTS_CR_REUT_CH_ERR_CTL_STRUCT;

typedef union {
  struct {
    UINT32 ECC_Error_Mask                          :  8;  // Bits 7:0
    UINT32                                         :  24;  // Bits 31:8
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCMNTS_CR_REUT_CH_ERR_ECC_MASK_STRUCT;

typedef union {
  struct {
    UINT32 Data_Error_MaskLow                      :  32;  // Bits 31:0
    UINT32 Data_Error_MaskHigh                     :  32;  // Bits 63:32
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} MCMNTS_CR_REUT_CH_ERR_DATA_MASK_STRUCT;

typedef union {
  struct {
    UINT32 Data_Error_StatusLow                    :  32;  // Bits 31:0
    UINT32 Data_Error_StatusHigh                   :  32;  // Bits 63:32
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} MCMNTS_CR_REUT_CH_ERR_DATA_STATUS_STRUCT;

typedef union {
  struct {
    UINT32 ECC_Error_Status                        :  8;  // Bits 7:0
    UINT32 Chunk_Error_Status                      :  8;  // Bits 15:8
    UINT32 Rank_Error_Status                       :  4;  // Bits 19:16
    UINT32 Alert_Error_Status                      :  1;  // Bits 20:20
    UINT32                                         :  11;  // Bits 31:21
    UINT32 Byte_Group_Error_Status                 :  9;  // Bits 40:32
    UINT32                                         :  11;  // Bits 51:41
    UINT32 WDB_Rd_Chunk_Num_Status                 :  3;  // Bits 54:52
    UINT32                                         :  1;  // Bits 55:55
    UINT32 Nth_Error                               :  6;  // Bits 61:56
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} MCMNTS_CR_REUT_CH_ERR_ECC_CHUNK_RANK_BYTE_NTH_STATUS_STRUCT;

typedef union {
  struct {
    UINT32 Column_Address                          :  11;  // Bits 10:0
    UINT32                                         :  13;  // Bits 23:11
    UINT32 Row_AddressLow                          :  8;  // Bits 31:24
    UINT32 Row_AddressHigh                         :  9;  // Bits 40:32
    UINT32                                         :  7;  // Bits 47:41
    UINT32 Bank_Address                            :  4;  // Bits 51:48
    UINT32                                         :  4;  // Bits 55:52
    UINT32 Rank_Address                            :  2;  // Bits 57:56
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} MCMNTS_CR_REUT_CH_ERROR_ADDR_STRUCT;

typedef union {
  struct {
    UINT32 Enable_WDB_Capture                      :  1;  // Bits 0:0
    UINT32 WDB_Error_Sel_Capture                   :  1;  // Bits 1:1
    UINT32 WDB_Data_Sel_Capture                    :  1;  // Bits 2:2
    UINT32                                         :  5;  // Bits 7:3
    UINT32 WDB_Starting_Capture_Pointer            :  6;  // Bits 13:8
    UINT32                                         :  2;  // Bits 15:14
    UINT32 WDB_Ending_Capture_Pointer              :  6;  // Bits 21:16
    UINT32                                         :  10;  // Bits 31:22
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCMNTS_CR_REUT_CH_WDB_CAPTURE_CTL_STRUCT;

typedef union {
  struct {
    UINT32 WDB_Current_Capture_Pointer             :  6;  // Bits 5:0
    UINT32                                         :  26;  // Bits 31:6
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCMNTS_CR_REUT_CH_WDB_CAPTURE_STATUS_STRUCT;

typedef union {
  struct {
    UINT32 Counter_Pointer                         :  7;  // Bits 6:0
    UINT32 Counter_Control                         :  2;  // Bits 8:7
    UINT32                                         :  23;  // Bits 31:9
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCMNTS_CR_REUT_CH_ERR_COUNTER_CTL_0_STRUCT;

typedef union {
  struct {
    UINT32 Counter_Pointer                         :  7;  // Bits 6:0
    UINT32 Counter_Control                         :  2;  // Bits 8:7
    UINT32                                         :  23;  // Bits 31:9
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCMNTS_CR_REUT_CH_ERR_COUNTER_CTL_1_STRUCT;

typedef union {
  struct {
    UINT32 Counter_Pointer                         :  7;  // Bits 6:0
    UINT32 Counter_Control                         :  2;  // Bits 8:7
    UINT32                                         :  23;  // Bits 31:9
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCMNTS_CR_REUT_CH_ERR_COUNTER_CTL_2_STRUCT;

typedef union {
  struct {
    UINT32 Counter_Pointer                         :  7;  // Bits 6:0
    UINT32 Counter_Control                         :  2;  // Bits 8:7
    UINT32                                         :  23;  // Bits 31:9
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCMNTS_CR_REUT_CH_ERR_COUNTER_CTL_3_STRUCT;

typedef union {
  struct {
    UINT32 Counter_Pointer                         :  7;  // Bits 6:0
    UINT32 Counter_Control                         :  2;  // Bits 8:7
    UINT32                                         :  23;  // Bits 31:9
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCMNTS_CR_REUT_CH_ERR_COUNTER_CTL_4_STRUCT;

typedef union {
  struct {
    UINT32 Counter_Pointer                         :  7;  // Bits 6:0
    UINT32 Counter_Control                         :  2;  // Bits 8:7
    UINT32                                         :  23;  // Bits 31:9
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCMNTS_CR_REUT_CH_ERR_COUNTER_CTL_5_STRUCT;

typedef union {
  struct {
    UINT32 Counter_Pointer                         :  7;  // Bits 6:0
    UINT32 Counter_Control                         :  2;  // Bits 8:7
    UINT32                                         :  23;  // Bits 31:9
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCMNTS_CR_REUT_CH_ERR_COUNTER_CTL_6_STRUCT;

typedef union {
  struct {
    UINT32 Counter_Pointer                         :  7;  // Bits 6:0
    UINT32 Counter_Control                         :  2;  // Bits 8:7
    UINT32                                         :  23;  // Bits 31:9
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCMNTS_CR_REUT_CH_ERR_COUNTER_CTL_7_STRUCT;

typedef union {
  struct {
    UINT32 Counter_Pointer                         :  7;  // Bits 6:0
    UINT32 Counter_Control                         :  2;  // Bits 8:7
    UINT32                                         :  23;  // Bits 31:9
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCMNTS_CR_REUT_CH_ERR_COUNTER_CTL_8_STRUCT;

typedef union {
  struct {
    UINT32 Counter_Overflow_Status                 :  9;  // Bits 8:0
    UINT32                                         :  23;  // Bits 31:9
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCMNTS_CR_REUT_CH_ERR_COUNTER_OVERFLOW_STATUS_STRUCT;

typedef union {
  struct {
    UINT32 WDB_Current_Read_Pointer                :  6;  // Bits 5:0
    UINT32                                         :  26;  // Bits 31:6
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCMNTS_CR_REUT_CH_PAT_WDB_CL_RD_STATUS_STRUCT;

typedef union {
  struct {
    UINT32 MR0                                     :  14;  // Bits 13:0
    UINT32                                         :  2;  // Bits 15:14
    UINT32 MR1                                     :  14;  // Bits 29:16
    UINT32                                         :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCMNTS_CR_DDR4_MR0_MR1_CONTENT_STRUCT;

typedef union {
  struct {
    UINT32 MR2                                     :  14;  // Bits 13:0
    UINT32                                         :  2;  // Bits 15:14
    UINT32 MR3                                     :  14;  // Bits 29:16
    UINT32                                         :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCMNTS_CR_DDR4_MR2_MR3_CONTENT_STRUCT;

typedef union {
  struct {
    UINT32 MR4                                     :  14;  // Bits 13:0
    UINT32                                         :  2;  // Bits 15:14
    UINT32 MR5                                     :  14;  // Bits 29:16
    UINT32                                         :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCMNTS_CR_DDR4_MR4_MR5_CONTENT_STRUCT;

typedef union {
  struct {
    UINT32 MR6                                     :  14;  // Bits 13:0
    UINT32                                         :  2;  // Bits 15:14
    UINT32 MR7                                     :  14;  // Bits 29:16
    UINT32                                         :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCMNTS_CR_DDR4_MR6_MR7_CONTENT_STRUCT;

typedef union {
  struct {
    UINT32 Rank0_Byte0                             :  2;  // Bits 1:0
    UINT32 Rank0_Byte1                             :  2;  // Bits 3:2
    UINT32 Rank0_Byte2                             :  2;  // Bits 5:4
    UINT32 Rank0_Byte3                             :  2;  // Bits 7:6
    UINT32 Rank0_Byte4                             :  2;  // Bits 9:8
    UINT32 Rank0_Byte5                             :  2;  // Bits 11:10
    UINT32 Rank0_Byte6                             :  2;  // Bits 13:12
    UINT32 Rank0_Byte7                             :  2;  // Bits 15:14
    UINT32 Rank1_Byte0                             :  2;  // Bits 17:16
    UINT32 Rank1_Byte1                             :  2;  // Bits 19:18
    UINT32 Rank1_Byte2                             :  2;  // Bits 21:20
    UINT32 Rank1_Byte3                             :  2;  // Bits 23:22
    UINT32 Rank1_Byte4                             :  2;  // Bits 25:24
    UINT32 Rank1_Byte5                             :  2;  // Bits 27:26
    UINT32 Rank1_Byte6                             :  2;  // Bits 29:28
    UINT32 Rank1_Byte7                             :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCMNTS_CR_DDR4_MR1_ODIC_VALUES_STRUCT;

typedef union {
  struct {
    UINT32 Rank0_Byte0                             :  2;  // Bits 1:0
    UINT32 Rank0_Byte1                             :  2;  // Bits 3:2
    UINT32 Rank0_Byte2                             :  2;  // Bits 5:4
    UINT32 Rank0_Byte3                             :  2;  // Bits 7:6
    UINT32 Rank0_Byte4                             :  2;  // Bits 9:8
    UINT32 Rank0_Byte5                             :  2;  // Bits 11:10
    UINT32 Rank0_Byte6                             :  2;  // Bits 13:12
    UINT32 Rank0_Byte7                             :  2;  // Bits 15:14
    UINT32 Rank1_Byte0                             :  2;  // Bits 17:16
    UINT32 Rank1_Byte1                             :  2;  // Bits 19:18
    UINT32 Rank1_Byte2                             :  2;  // Bits 21:20
    UINT32 Rank1_Byte3                             :  2;  // Bits 23:22
    UINT32 Rank1_Byte4                             :  2;  // Bits 25:24
    UINT32 Rank1_Byte5                             :  2;  // Bits 27:26
    UINT32 Rank1_Byte6                             :  2;  // Bits 29:28
    UINT32 Rank1_Byte7                             :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCMNTS_CR_DDR4_MR2_RTT_WR_VALUES_STRUCT;

typedef union {
  struct {
    UINT32 Byte0                                   :  7;  // Bits 6:0
    UINT32                                         :  1;  // Bits 7:7
    UINT32 Byte1                                   :  7;  // Bits 14:8
    UINT32                                         :  1;  // Bits 15:15
    UINT32 Byte2                                   :  7;  // Bits 22:16
    UINT32                                         :  1;  // Bits 23:23
    UINT32 Byte3                                   :  7;  // Bits 30:24
    UINT32                                         :  1;  // Bits 31:31
    UINT32 Byte4                                   :  7;  // Bits 38:32
    UINT32                                         :  1;  // Bits 39:39
    UINT32 Byte5                                   :  7;  // Bits 46:40
    UINT32                                         :  1;  // Bits 47:47
    UINT32 Byte6                                   :  7;  // Bits 54:48
    UINT32                                         :  1;  // Bits 55:55
    UINT32 Byte7                                   :  7;  // Bits 62:56
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} MCMNTS_CR_DDR4_MR6_VREF_VALUES_0_STRUCT;

typedef union {
  struct {
    UINT32 Byte0                                   :  7;  // Bits 6:0
    UINT32                                         :  1;  // Bits 7:7
    UINT32 Byte1                                   :  7;  // Bits 14:8
    UINT32                                         :  1;  // Bits 15:15
    UINT32 Byte2                                   :  7;  // Bits 22:16
    UINT32                                         :  1;  // Bits 23:23
    UINT32 Byte3                                   :  7;  // Bits 30:24
    UINT32                                         :  1;  // Bits 31:31
    UINT32 Byte4                                   :  7;  // Bits 38:32
    UINT32                                         :  1;  // Bits 39:39
    UINT32 Byte5                                   :  7;  // Bits 46:40
    UINT32                                         :  1;  // Bits 47:47
    UINT32 Byte6                                   :  7;  // Bits 54:48
    UINT32                                         :  1;  // Bits 55:55
    UINT32 Byte7                                   :  7;  // Bits 62:56
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} MCMNTS_CR_DDR4_MR6_VREF_VALUES_1_STRUCT;

typedef union {
  struct {
    UINT32 MR1                                     :  8;  // Bits 7:0
    UINT32 MR2                                     :  8;  // Bits 15:8
    UINT32 MR3                                     :  8;  // Bits 23:16
    UINT32 MR11                                    :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCMNTS_CR_LPDDR3_MR_CONTENT_STRUCT;

typedef union {
  struct {
    UINT32 DDR4_Restore_MR                         :  8;  // Bits 7:0
    UINT32 DDR4_Restore_MR1_Per_Device             :  1;  // Bits 8:8
    UINT32 DDR4_Restore_MR2_Per_Device             :  1;  // Bits 9:9
    UINT32 DDR4_Restore_MR6_Per_Device             :  1;  // Bits 10:10
    UINT32                                         :  5;  // Bits 15:11
    UINT32 LPDDR3_Restore_MR                       :  4;  // Bits 19:16
    UINT32 do_ZQCL                                 :  1;  // Bits 20:20
    UINT32 zero_rank1_MR11                         :  1;  // Bits 21:21
    UINT32 vref_time_per_byte                      :  1;  // Bits 22:22
    UINT32                                         :  1;  // Bits 23:23
    UINT32 tVREFDQ                                 :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCMNTS_CR_MRS_FSM_CONTROL_STRUCT;

typedef union {
  struct {
    UINT32 Run                                     :  1;  // Bits 0:0
    UINT32                                         :  31;  // Bits 31:1
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCMNTS_CR_MRS_FSM_RUN_STRUCT;

typedef union {
  struct {
    UINT32 Spare_RW                                :  8;  // Bits 7:0
    UINT32 ForceX2Ref                              :  1;  // Bits 8:8
    UINT32 ForceX4Ref                              :  1;  // Bits 9:9
    UINT32 ForceTxAnalog                           :  1;  // Bits 10:10
    UINT32 TxAnalog_grace                          :  4;  // Bits 14:11
    UINT32 DisSREXcnt                              :  1;  // Bits 15:15
    UINT32 Spare_RW_V                              :  16;  // Bits 31:16
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCMNTS_CR_MCMNTS_SPARE_STRUCT;

#pragma pack(pop)
#endif
