#ifndef __MrcMcRegisterStruct7xxx_h__
#define __MrcMcRegisterStruct7xxx_h__
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
    UINT32 VCPNPLIM                                :  3;  // Bits 2:0
    UINT32                                         :  1;  // Bits 3:3
    UINT32 VCPPLIM                                 :  3;  // Bits 6:4
    UINT32                                         :  1;  // Bits 7:7
    UINT32 VCMNPLIM                                :  3;  // Bits 10:8
    UINT32                                         :  1;  // Bits 11:11
    UINT32 VCMPLIM                                 :  3;  // Bits 14:12
    UINT32                                         :  1;  // Bits 15:15
    UINT32 VCPCMPLIM                               :  3;  // Bits 18:16
    UINT32                                         :  1;  // Bits 19:19
    UINT32 VCMCMPLIM                               :  3;  // Bits 22:20
    UINT32                                         :  8;  // Bits 30:23
    UINT32 LOCK                                    :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} HUBS_CR_DMIVCLIM_HUBS_STRUCT;

typedef union {
  struct {
    UINT32 P0                                      :  1;  // Bits 0:0
    UINT32 P1                                      :  1;  // Bits 1:1
    UINT32 P2                                      :  1;  // Bits 2:2
    UINT32 P3                                      :  1;  // Bits 3:3
    UINT32 MSGCH_GATECLK_DISABLE                   :  1;  // Bits 4:4
    UINT32 MSGCH_NOPEG_AUTOCOM_ENABLE              :  1;  // Bits 5:5
    UINT32 RESERVED_RW                             :  16;  // Bits 21:6
    UINT32 RESERVED_VARIANT                        :  5;  // Bits 26:22
    UINT32 RESERVED_VARIANT_STICKY                 :  5;  // Bits 31:27
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} HUBS_CR_HUB0_PWRDN_OVRD_HUBS_STRUCT;

typedef union {
  struct {
    UINT32 P0                                      :  1;  // Bits 0:0
    UINT32 P1                                      :  1;  // Bits 1:1
    UINT32 P2                                      :  1;  // Bits 2:2
    UINT32 P3                                      :  1;  // Bits 3:3
    UINT32                                         :  1;  // Bits 4:4
    UINT32 MSGCH_GSA_AUTOCOM_ENABLE                :  1;  // Bits 5:5
    UINT32                                         :  16;  // Bits 21:6
    UINT32 RESERVED_VARIANT                        :  5;  // Bits 26:22
    UINT32 RESERVED_VARIANT_STICKY                 :  5;  // Bits 31:27
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} HUBS_CR_HUB1_PWRDN_OVRD_HUBS_STRUCT;

typedef union {
  struct {
    UINT32 P0                                      :  1;  // Bits 0:0
    UINT32 P1                                      :  1;  // Bits 1:1
    UINT32 P2                                      :  1;  // Bits 2:2
    UINT32 P3                                      :  1;  // Bits 3:3
    UINT32                                         :  1;  // Bits 4:4
    UINT32 MSGCH_GSA_AUTOCOM_ENABLE                :  1;  // Bits 5:5
    UINT32                                         :  16;  // Bits 21:6
    UINT32 RESERVED_VARIANT                        :  5;  // Bits 26:22
    UINT32 RESERVED_VARIANT_STICKY                 :  5;  // Bits 31:27
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} HUBS_CR_HUB2_PWRDN_OVRD_HUBS_STRUCT;

typedef union {
  struct {
    UINT32 BLK_GNT_P0                              :  1;  // Bits 0:0
    UINT32 BLK_GNT_P1                              :  1;  // Bits 1:1
    UINT32 BLK_GNT_P2                              :  1;  // Bits 2:2
    UINT32 BLK_GNT_P3                              :  1;  // Bits 3:3
    UINT32 BLK_PUT_P0                              :  1;  // Bits 4:4
    UINT32 BLK_PUT_P1                              :  1;  // Bits 5:5
    UINT32 BLK_PUT_P2                              :  1;  // Bits 6:6
    UINT32 BLK_PUT_P3                              :  1;  // Bits 7:7
    UINT32 NO_CHAIN_P0                             :  1;  // Bits 8:8
    UINT32 NO_CHAIN_P1                             :  1;  // Bits 9:9
    UINT32 NO_CHAIN_P2                             :  1;  // Bits 10:10
    UINT32 NO_CHAIN_P3                             :  1;  // Bits 11:11
    UINT32 SLOW_UP_P0                              :  1;  // Bits 12:12
    UINT32 SLOW_UP_P1                              :  1;  // Bits 13:13
    UINT32 SLOW_UP_P2                              :  1;  // Bits 14:14
    UINT32 SLOW_UP_P3                              :  1;  // Bits 15:15
    UINT32 SLOW_DN_P0                              :  1;  // Bits 16:16
    UINT32 SLOW_DN_P1                              :  1;  // Bits 17:17
    UINT32 SLOW_DN_P2                              :  1;  // Bits 18:18
    UINT32 SLOW_DN_P3                              :  1;  // Bits 19:19
    UINT32 SLOWER_CMD                              :  1;  // Bits 20:20
    UINT32 DMI_NOPUSH                              :  1;  // Bits 21:21
    UINT32 RO_PASS_NP                              :  1;  // Bits 22:22
    UINT32 RST_CRD_P3                              :  1;  // Bits 23:23
    UINT32 METAFLOP_EN                             :  1;  // Bits 24:24
    UINT32 RESERVED                                :  7;  // Bits 31:25
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} HUBS_CR_HUB0_DEFEATURE_HUBS_STRUCT;

typedef union {
  struct {
    UINT32 BLK_GNT_P2                              :  1;  // Bits 0:0
    UINT32 BLK_GNT_P3                              :  1;  // Bits 1:1
    UINT32 BLK_PUT_P0                              :  1;  // Bits 2:2
    UINT32 BLK_PUT_P1                              :  1;  // Bits 3:3
    UINT32 BLK_PUT_P2                              :  1;  // Bits 4:4
    UINT32 BLK_PUT_P3                              :  1;  // Bits 5:5
    UINT32 NO_CHAIN_P2                             :  1;  // Bits 6:6
    UINT32 NO_CHAIN_P3                             :  1;  // Bits 7:7
    UINT32 SLOW_UP_P0                              :  1;  // Bits 8:8
    UINT32 SLOW_UP_P2                              :  1;  // Bits 9:9
    UINT32 SLOW_UP_P3                              :  1;  // Bits 10:10
    UINT32 SLOW_DN_P1                              :  1;  // Bits 11:11
    UINT32 SLOW_DN_P2                              :  1;  // Bits 12:12
    UINT32 SLOW_DN_P3                              :  1;  // Bits 13:13
    UINT32 SLOWER_CMD                              :  1;  // Bits 14:14
    UINT32 RO_PASS_NP                              :  1;  // Bits 15:15
    UINT32 RST_CRD_P0                              :  1;  // Bits 16:16
    UINT32 RST_CRD_P1                              :  1;  // Bits 17:17
    UINT32                                         :  14;  // Bits 31:18
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} HUBS_CR_HUB1_DEFEATURE_HUBS_STRUCT;

typedef union {
  struct {
    UINT32 BLK_GNT_P1                              :  1;  // Bits 0:0
    UINT32 BLK_GNT_P2                              :  1;  // Bits 1:1
    UINT32 BLK_GNT_P3                              :  1;  // Bits 2:2
    UINT32 BLK_PUT_P0                              :  1;  // Bits 3:3
    UINT32 BLK_PUT_P1                              :  1;  // Bits 4:4
    UINT32 BLK_PUT_P2                              :  1;  // Bits 5:5
    UINT32 BLK_PUT_P3                              :  1;  // Bits 6:6
    UINT32 NO_CHAIN_P1                             :  1;  // Bits 7:7
    UINT32 NO_CHAIN_P2                             :  1;  // Bits 8:8
    UINT32 NO_CHAIN_P3                             :  1;  // Bits 9:9
    UINT32 SLOW_UP_P0                              :  1;  // Bits 10:10
    UINT32 SLOW_UP_P1                              :  1;  // Bits 11:11
    UINT32 SLOW_UP_P2                              :  1;  // Bits 12:12
    UINT32 SLOW_UP_P3                              :  1;  // Bits 13:13
    UINT32 SLOW_DN_P1                              :  1;  // Bits 14:14
    UINT32 SLOW_DN_P2                              :  1;  // Bits 15:15
    UINT32 SLOW_DN_P3                              :  1;  // Bits 16:16
    UINT32 SLOWER_CMD                              :  1;  // Bits 17:17
    UINT32 RST_CRD_P0                              :  1;  // Bits 18:18
    UINT32                                         :  13;  // Bits 31:19
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} HUBS_CR_HUB2_DEFEATURE_HUBS_STRUCT;

typedef union {
  struct {
    UINT32 PCIPWRGAT                               :  1;  // Bits 0:0
    UINT32                                         :  31;  // Bits 31:1
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} HUBS_CR_PEGCTL_HUBS_STRUCT;

typedef union {
  struct {
    UINT32 H0_EMPTY                                :  1;  // Bits 0:0
    UINT32 H1_EMPTY                                :  1;  // Bits 1:1
    UINT32 H2_EMPTY                                :  1;  // Bits 2:2
    UINT32                                         :  29;  // Bits 31:3
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} HUBS_CR_HUB_EMPTY_HUBS_STRUCT;

typedef union {
  struct {
    UINT32 REQ_VLD_P0                              :  1;  // Bits 0:0
    UINT32 REQ_VLD_P1                              :  1;  // Bits 1:1
    UINT32 REQ_VLD_P2                              :  1;  // Bits 2:2
    UINT32 REQ_VLD_P3                              :  1;  // Bits 3:3
    UINT32 TNX_VLD_P0                              :  1;  // Bits 4:4
    UINT32 TNX_VLD_P1                              :  1;  // Bits 5:5
    UINT32 TNX_VLD_P2                              :  1;  // Bits 6:6
    UINT32 TNX_VLD_P3                              :  1;  // Bits 7:7
    UINT32                                         :  24;  // Bits 31:8
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} HUBS_CR_HUB0_STATUS_HUBS_STRUCT;

typedef union {
  struct {
    UINT32 REQ_VLD_P0                              :  1;  // Bits 0:0
    UINT32 REQ_VLD_P1                              :  1;  // Bits 1:1
    UINT32 REQ_VLD_P2                              :  1;  // Bits 2:2
    UINT32 REQ_VLD_P3                              :  1;  // Bits 3:3
    UINT32 TNX_VLD_P0                              :  1;  // Bits 4:4
    UINT32 TNX_VLD_P1                              :  1;  // Bits 5:5
    UINT32 TNX_VLD_P2                              :  1;  // Bits 6:6
    UINT32 TNX_VLD_P3                              :  1;  // Bits 7:7
    UINT32                                         :  24;  // Bits 31:8
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} HUBS_CR_HUB1_STATUS_HUBS_STRUCT;

typedef union {
  struct {
    UINT32 REQ_VLD_P0                              :  1;  // Bits 0:0
    UINT32 REQ_VLD_P1                              :  1;  // Bits 1:1
    UINT32 REQ_VLD_P2                              :  1;  // Bits 2:2
    UINT32 REQ_VLD_P3                              :  1;  // Bits 3:3
    UINT32 TNX_VLD_P0                              :  1;  // Bits 4:4
    UINT32 TNX_VLD_P1                              :  1;  // Bits 5:5
    UINT32 TNX_VLD_P2                              :  1;  // Bits 6:6
    UINT32 TNX_VLD_P3                              :  1;  // Bits 7:7
    UINT32                                         :  24;  // Bits 31:8
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} HUBS_CR_HUB2_STATUS_HUBS_STRUCT;

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
} HUBS_CR_VISA_SLIDE_SABHUB0S_F_HUBS_STRUCT;

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
} HUBS_CR_VISA_SLIDE_SABHUB1S_F_HUBS_STRUCT;

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
} HUBS_CR_VISA_SLIDE_SABHUB2S_F_HUBS_STRUCT;

typedef union {
  struct {
    UINT32 DATA                                    :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} HUBS_CR_MBOX_WR_DATA_HUBS_STRUCT;

typedef union {
  struct {
    UINT32 DATA                                    :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} HUBS_CR_MBOX_RD_DATA_HUBS_STRUCT;

typedef union {
  struct {
    UINT32 ADDR                                    :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} HUBS_CR_MBOX_ADDR_LO_HUBS_STRUCT;

typedef union {
  struct {
    UINT32 ADDR                                    :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} HUBS_CR_MBOX_ADDR_HI_HUBS_STRUCT;

typedef union {
  struct {
    UINT32 FBE                                     :  4;  // Bits 3:0
    UINT32 LBE                                     :  4;  // Bits 7:4
    UINT32 TAG                                     :  8;  // Bits 15:8
    UINT32 RQID                                    :  16;  // Bits 31:16
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} HUBS_CR_MBOX_CMD_LO_HUBS_STRUCT;

typedef union {
  struct {
    UINT32 AT                                      :  2;  // Bits 1:0
    UINT32 POISON                                  :  1;  // Bits 2:2
    UINT32 LENGTH                                  :  5;  // Bits 7:3
    UINT32 RELAXED                                 :  1;  // Bits 8:8
    UINT32 NOSNOOP                                 :  1;  // Bits 9:9
    UINT32 CHAIN                                   :  1;  // Bits 10:10
    UINT32 CTYPE                                   :  5;  // Bits 15:11
    UINT32 FMT                                     :  2;  // Bits 17:16
    UINT32 TC                                      :  4;  // Bits 21:18
    UINT32 RESERVED                                :  2;  // Bits 23:22
    UINT32 DMI_PRIV                                :  1;  // Bits 24:24
    UINT32 CHID                                    :  4;  // Bits 28:25
    UINT32 RTYPE                                   :  2;  // Bits 30:29
    UINT32 START                                   :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} HUBS_CR_MBOX_CMD_HI_HUBS_STRUCT;

typedef union {
  struct {
    UINT32 ENABLE                                  :  1;  // Bits 0:0
    UINT32 LOCK_IA                                 :  1;  // Bits 1:1
    UINT32 RESET                                   :  1;  // Bits 2:2
    UINT32 BLK_CYCLES                              :  6;  // Bits 8:3
    UINT32 WR_DWORD_SEL                            :  4;  // Bits 12:9
    UINT32 RD_DWORD_SEL                            :  4;  // Bits 16:13
    UINT32 RPT_CMD_CNT                             :  6;  // Bits 22:17
    UINT32 RPT_NXT_ADDR                            :  1;  // Bits 23:23
    UINT32 RPT_NXT_PAGE                            :  1;  // Bits 24:24
    UINT32 DIS_CMP_INV                             :  1;  // Bits 25:25
    UINT32 FSM_STATE                               :  4;  // Bits 29:26
    UINT32 P2P_ALL                                 :  1;  // Bits 30:30
    UINT32 SPARE                                   :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} HUBS_CR_MBOX_CFG_HUBS_STRUCT;

typedef union {
  struct {
    UINT32 FSM_STATE                               :  4;  // Bits 3:0
    UINT32 RPT_CMD_CNT                             :  6;  // Bits 9:4
    UINT32 OPCODE                                  :  7;  // Bits 16:10
    UINT32 WR_DWORD_SEL                            :  4;  // Bits 20:17
    UINT32 RD_DWORD_SEL                            :  4;  // Bits 24:21
    UINT32 P2P_RD_UP                               :  1;  // Bits 25:25
    UINT32 P2P_RD_DN                               :  1;  // Bits 26:26
    UINT32 SPARE                                   :  5;  // Bits 31:27
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} HUBS_CR_MBOX_STATUS_HUBS_STRUCT;

typedef union {
  struct {
    UINT32 XTM_CHID                                :  11;  // Bits 10:0
    UINT32 NP                                      :  1;  // Bits 11:11
    UINT32 PC                                      :  1;  // Bits 12:12
    UINT32 RESERVED                                :  10;  // Bits 22:13
    UINT32                                         :  9;  // Bits 31:23
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} HUBS_CR_HUB0_BLOCK_UP_HUBS_STRUCT;

typedef union {
  struct {
    UINT32 MUL_READ_MODE                           :  1;  // Bits 0:0
    UINT32 ENABLE_ACTIVE_STORE                     :  1;  // Bits 1:1
    UINT32                                         :  30;  // Bits 31:2
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} HUBS_CR_MBOX_CFG_ENHANCE_HUBS_STRUCT;

typedef union {
  struct {
    UINT32 RX_FSM                                  :  3;  // Bits 2:0
    UINT32 CMD_COMPLETE                            :  6;  // Bits 8:3
    UINT32                                         :  23;  // Bits 31:9
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} HUBS_CR_MBOX_STATUS_ENHANCE_HUBS_STRUCT;

typedef union {
  struct {
    UINT32 MBOX_SEQUENCE                           :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} HUBS_CR_MBOX_SEQUENCE_HUBS_STRUCT;

typedef union {
  struct {
    UINT32 ADDR                                    :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} HUBS_CR_MBOX_ADDR2_LO_HUBS_STRUCT;

typedef union {
  struct {
    UINT32 ADDR                                    :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} HUBS_CR_MBOX_ADDR2_HI_HUBS_STRUCT;

typedef union {
  struct {
    UINT32 FBE                                     :  4;  // Bits 3:0
    UINT32 LBE                                     :  4;  // Bits 7:4
    UINT32 TAG                                     :  8;  // Bits 15:8
    UINT32 RQID                                    :  16;  // Bits 31:16
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} HUBS_CR_MBOX_CMD2_LO_HUBS_STRUCT;

typedef union {
  struct {
    UINT32 AT                                      :  2;  // Bits 1:0
    UINT32 POISON                                  :  1;  // Bits 2:2
    UINT32 LENGTH                                  :  5;  // Bits 7:3
    UINT32 RELAXED                                 :  1;  // Bits 8:8
    UINT32 NOSNOOP                                 :  1;  // Bits 9:9
    UINT32 CHAIN                                   :  1;  // Bits 10:10
    UINT32 CTYPE                                   :  5;  // Bits 15:11
    UINT32 FMT                                     :  2;  // Bits 17:16
    UINT32 TC                                      :  4;  // Bits 21:18
    UINT32 RESERVED                                :  2;  // Bits 23:22
    UINT32 DMI_PRIV                                :  1;  // Bits 24:24
    UINT32 CHID                                    :  4;  // Bits 28:25
    UINT32 RTYPE                                   :  2;  // Bits 30:29
    UINT32 START                                   :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} HUBS_CR_MBOX_CMD2_HI_HUBS_STRUCT;

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
} HUBS_CR_VISA_CTL_SABHUB0S_F_HUBS_STRUCT;

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
} HUBS_CR_VISA_CTL_SABHUB0S_L_HUBS_STRUCT;

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
} HUBS_CR_VISA_CTL_SABHUB1S_F_HUBS_STRUCT;

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
} HUBS_CR_VISA_CTL_SABHUB1S_L_HUBS_STRUCT;

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
} HUBS_CR_VISA_CTL_SABHUB2S_F_HUBS_STRUCT;

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
} HUBS_CR_VISA_XBAR_SABHUB1S_F_HUBS_STRUCT;

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
} HUBS_CR_VISA_XBAR_SABHUB2S_F_HUBS_STRUCT;

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
} HUBS_CR_VISA_XBAR_SABHUB0S_L_HUBS_STRUCT;

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
} HUBS_CR_VISA_XBAR_SABHUB1S_L_HUBS_STRUCT;

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
} HUBS_CR_VISA_XBAR_SABHUB2S_L_HUBS_STRUCT;

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
} HUBS_CR_VISA_CTL_SABHUB2S_L_HUBS_STRUCT;

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
} HUBS_CR_VISA_XBAR_SABHUB0S_F_HUBS_STRUCT;

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
} HUBS_CR_VISA_SLIDE_SABHUB1S_L_HUBS_STRUCT;

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
} HUBS_CR_VISA_SLIDE_SABHUB0S_L_HUBS_STRUCT;

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
} HUBS_CR_VISA_SLIDE_SABHUB2S_L_HUBS_STRUCT;

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
} HUBS_CR_VISA_XBAR_SABHUB1S_I_HUBS_STRUCT;

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
} HUBS_CR_VISA_CTL_SABHUB0S_I_HUBS_STRUCT;

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
} HUBS_CR_VISA_SLIDE_SABHUB0S_I_HUBS_STRUCT;

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
} HUBS_CR_VISA_XBAR_SABHUB0S_I_HUBS_STRUCT;

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
} HUBS_CR_VISA_CTL_SABHUB1S_I_HUBS_STRUCT;

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
} HUBS_CR_VISA_SLIDE_SABHUB1S_I_HUBS_STRUCT;

typedef union {
  struct {
    UINT32 DMI_VC0_NP                              :  3;  // Bits 2:0
    UINT32 DMI_VC0_PC                              :  3;  // Bits 5:3
    UINT32 P16_VC0_NP                              :  3;  // Bits 8:6
    UINT32 P16_VC0_PC                              :  3;  // Bits 11:9
    UINT32 P08_VC0_NP                              :  3;  // Bits 14:12
    UINT32 P08_VC0_PC                              :  3;  // Bits 17:15
    UINT32 P4A_VC0_NP                              :  3;  // Bits 20:18
    UINT32 P4A_VC0_PC                              :  3;  // Bits 23:21
    UINT32 DE_VC0_NP                               :  3;  // Bits 26:24
    UINT32 DE_VC0_PC                               :  3;  // Bits 29:27
    UINT32                                         :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} HUBS_CR_HUB0_UP_ARB_0_LIM_HUBS_STRUCT;

typedef union {
  struct {
    UINT32 DMI_VCM_NP                              :  3;  // Bits 2:0
    UINT32 DMI_VCM_PC                              :  3;  // Bits 5:3
    UINT32 GMM_VC0_NP                              :  3;  // Bits 8:6
    UINT32 GMM_VC0_PC                              :  3;  // Bits 11:9
    UINT32 RESERVED                                :  12;  // Bits 23:12
    UINT32                                         :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} HUBS_CR_HUB0_UP_ARB_1_LIM_HUBS_STRUCT;

typedef union {
  struct {
    UINT32 NON_VC1_THRESHOLD                       :  4;  // Bits 3:0
    UINT32 VC1_RD_THRESHOLD                        :  4;  // Bits 7:4
    UINT32 FIXED_RATEP_EN                          :  1;  // Bits 8:8
    UINT32 HIGH_PRIO_LIM                           :  3;  // Bits 11:9
    UINT32 LOW_PRIO_LIM                            :  3;  // Bits 14:12
    UINT32 RESERVED                                :  9;  // Bits 23:15
    UINT32                                         :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} HUBS_CR_HUB0_ARB_IPC_HUBS_STRUCT;

typedef union {
  struct {
    UINT32 DMI_VC0_NP                              :  3;  // Bits 2:0
    UINT32 DMI_VC0_PC                              :  3;  // Bits 5:3
    UINT32 P4A_VC0_NP                              :  3;  // Bits 8:6
    UINT32 P4A_VC0_PC                              :  3;  // Bits 11:9
    UINT32 DMI_VCM_NP                              :  3;  // Bits 14:12
    UINT32 DMI_VCM_PC                              :  3;  // Bits 17:15
    UINT32 GMM_VC0_NP                              :  3;  // Bits 20:18
    UINT32 GMM_VC0_PC                              :  3;  // Bits 23:21
    UINT32                                         :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} HUBS_CR_HUB1_UP_ARB_0_LIM_HUBS_STRUCT;

typedef union {
  struct {
    UINT32 NON_VC1_THRESHOLD                       :  4;  // Bits 3:0
    UINT32 VC1_RD_THRESHOLD                        :  4;  // Bits 7:4
    UINT32 FIXED_RATEP_EN                          :  1;  // Bits 8:8
    UINT32 HIGH_PRIO_LIM                           :  3;  // Bits 11:9
    UINT32 LOW_PRIO_LIM                            :  3;  // Bits 14:12
    UINT32                                         :  17;  // Bits 31:15
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} HUBS_CR_HUB1_ARB_IPC_HUBS_STRUCT;

typedef union {
  struct {
    UINT32 P16_VC0_NP                              :  3;  // Bits 2:0
    UINT32 P16_VC0_PC                              :  3;  // Bits 5:3
    UINT32 DE_VC0_NP                               :  3;  // Bits 8:6
    UINT32 DE_VC0_PC                               :  3;  // Bits 11:9
    UINT32                                         :  20;  // Bits 31:12
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} HUBS_CR_HUB2_UP_ARB_0_LIM_HUBS_STRUCT;

typedef union {
  struct {
    UINT32 NON_VC1_THRESHOLD                       :  4;  // Bits 3:0
    UINT32 VC1_RD_THRESHOLD                        :  4;  // Bits 7:4
    UINT32 FIXED_RATEP_EN                          :  1;  // Bits 8:8
    UINT32 HIGH_PRIO_LIM                           :  3;  // Bits 11:9
    UINT32 LOW_PRIO_LIM                            :  3;  // Bits 14:12
    UINT32                                         :  17;  // Bits 31:15
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} HUBS_CR_HUB2_ARB_IPC_HUBS_STRUCT;

typedef union {
  struct {
    UINT32 DMI_VC0_NP                              :  3;  // Bits 2:0
    UINT32 DMI_VC0_PC                              :  3;  // Bits 5:3
    UINT32 DE_VC0_NP                               :  3;  // Bits 8:6
    UINT32 DE_VC0_PC                               :  3;  // Bits 11:9
    UINT32 CAM_VC0_NP                              :  3;  // Bits 14:12
    UINT32 CAM_VC0_PC                              :  3;  // Bits 17:15
    UINT32 DMI_VCM_NP                              :  3;  // Bits 20:18
    UINT32 DMI_VCM_PC                              :  3;  // Bits 23:21
    UINT32 GMM_VC0_NP                              :  3;  // Bits 26:24
    UINT32 GMM_VC0_PC                              :  3;  // Bits 29:27
    UINT32                                         :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} HUBS_CR_HUB3_UP_ARB_0_LIM_HUBS_STRUCT;

typedef union {
  struct {
    UINT32 NON_VC1_THRESHOLD                       :  4;  // Bits 3:0
    UINT32 VC1_RD_THRESHOLD                        :  4;  // Bits 7:4
    UINT32 FIXED_RATEP_EN                          :  1;  // Bits 8:8
    UINT32 HIGH_PRIO_LIM                           :  3;  // Bits 11:9
    UINT32 LOW_PRIO_LIM                            :  3;  // Bits 14:12
    UINT32                                         :  17;  // Bits 31:15
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} HUBS_CR_HUB3_ARB_IPC_HUBS_STRUCT;

typedef union {
  struct {
    UINT32 DE_VC0_NP                               :  3;  // Bits 2:0
    UINT32 DE_VC0_PC                               :  3;  // Bits 5:3
    UINT32 GMM_VC0_NP                              :  3;  // Bits 8:6
    UINT32 GMM_VC0_PC                              :  3;  // Bits 11:9
    UINT32                                         :  20;  // Bits 31:12
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} HUBS_CR_HUB4_UP_ARB_0_LIM_HUBS_STRUCT;

typedef union {
  struct {
    UINT32 NON_VC1_THRESHOLD                       :  4;  // Bits 3:0
    UINT32 VC1_RD_THRESHOLD                        :  4;  // Bits 7:4
    UINT32 FIXED_RATEP_EN                          :  1;  // Bits 8:8
    UINT32 HIGH_PRIO_LIM                           :  3;  // Bits 11:9
    UINT32 LOW_PRIO_LIM                            :  3;  // Bits 14:12
    UINT32                                         :  17;  // Bits 31:15
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} HUBS_CR_HUB4_ARB_IPC_HUBS_STRUCT;

typedef union {
  struct {
    UINT32 DMI_VC0_MRG                             :  3;  // Bits 2:0
    UINT32 DMI_VC0_RLX                             :  3;  // Bits 5:3
    UINT32 P16_VC0_MRG                             :  3;  // Bits 8:6
    UINT32 P16_VC0_RLX                             :  3;  // Bits 11:9
    UINT32 P08_VC0_MRG                             :  3;  // Bits 14:12
    UINT32 P08_VC0_RLX                             :  3;  // Bits 17:15
    UINT32 P4A_VC0_MRG                             :  3;  // Bits 20:18
    UINT32 P4A_VC0_RLX                             :  3;  // Bits 23:21
    UINT32 DE_VC0_MRG                              :  3;  // Bits 26:24
    UINT32 DMI_VCM_MRG                             :  3;  // Bits 29:27
    UINT32                                         :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} HUBS_CR_HUB0_DN_ARB_0_LIM_HUBS_STRUCT;

typedef union {
  struct {
    UINT32 GMM_VC0_MRG                             :  3;  // Bits 2:0
    UINT32 RESERVED                                :  12;  // Bits 14:3
    UINT32                                         :  17;  // Bits 31:15
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} HUBS_CR_HUB0_DN_ARB_1_LIM_HUBS_STRUCT;

typedef union {
  struct {
    UINT32 DMI_VC0_MRG                             :  3;  // Bits 2:0
    UINT32 DMI_VC0_RLX                             :  3;  // Bits 5:3
    UINT32 P4A_VC0_MRG                             :  3;  // Bits 8:6
    UINT32 P4A_VC0_RLX                             :  3;  // Bits 11:9
    UINT32 DMI_VCM_MRG                             :  3;  // Bits 14:12
    UINT32 GMM_VC0_MRG                             :  3;  // Bits 17:15
    UINT32                                         :  14;  // Bits 31:18
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} HUBS_CR_HUB1_DN_ARB_0_LIM_HUBS_STRUCT;

typedef union {
  struct {
    UINT32 P16_VC0_MRG                             :  3;  // Bits 2:0
    UINT32 P16_VC0_RLX                             :  3;  // Bits 5:3
    UINT32 DE_VC0_MRG                              :  3;  // Bits 8:6
    UINT32                                         :  23;  // Bits 31:9
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} HUBS_CR_HUB2_DN_ARB_0_LIM_HUBS_STRUCT;

typedef union {
  struct {
    UINT32 DMI_VC0_MRG                             :  3;  // Bits 2:0
    UINT32 DMI_VC0_RLX                             :  3;  // Bits 5:3
    UINT32 DE_VC0_MRG                              :  3;  // Bits 8:6
    UINT32 CAM_VC0_MRG                             :  3;  // Bits 11:9
    UINT32 DMI_VCM_MRG                             :  3;  // Bits 14:12
    UINT32 GMM_VC0_MRG                             :  3;  // Bits 17:15
    UINT32                                         :  14;  // Bits 31:18
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} HUBS_CR_HUB3_DN_ARB_0_LIM_HUBS_STRUCT;

typedef union {
  struct {
    UINT32 DE_VC0_MRG                              :  3;  // Bits 2:0
    UINT32 GMM_VC0_MRG                             :  3;  // Bits 5:3
    UINT32                                         :  26;  // Bits 31:6
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} HUBS_CR_HUB4_DN_ARB_0_LIM_HUBS_STRUCT;

typedef union {
  struct {
    UINT32 SPARE                                   :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} HUBS_CR_H0_SPARE_HUBS_STRUCT;

typedef union {
  struct {
    UINT32 SPARE                                   :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} HUBS_CR_H1_SPARE_HUBS_STRUCT;

typedef union {
  struct {
    UINT32 DMIVC0_PMIN                             :  3;  // Bits 2:0
    UINT32 P10VC0_PMIN                             :  3;  // Bits 5:3
    UINT32 P11VC0_PMIN                             :  3;  // Bits 8:6
    UINT32 P12VC0_PMIN                             :  3;  // Bits 11:9
    UINT32 DEVC0_PMIN                              :  3;  // Bits 14:12
    UINT32 DMIVCP_PMIN                             :  3;  // Bits 17:15
    UINT32 DMIVCM_PMIN                             :  3;  // Bits 20:18
    UINT32 DMIVC1_PMIN                             :  3;  // Bits 23:21
    UINT32 CAMVC0_PMIN                             :  3;  // Bits 26:24
    UINT32 GMMVC0_PMIN                             :  3;  // Bits 29:27
    UINT32                                         :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MPRDRTRN_CR_CRDTCTL0_IMPH_STRUCT;

typedef union {
  struct {
    UINT32 DMIVC0_NPMIN                            :  3;  // Bits 2:0
    UINT32 P10VC0_NPMIN                            :  3;  // Bits 5:3
    UINT32 P11VC0_NPMIN                            :  3;  // Bits 8:6
    UINT32 P12VC0_NPMIN                            :  3;  // Bits 11:9
    UINT32 DEVC0_NPMIN                             :  3;  // Bits 14:12
    UINT32 DMIVCP_NPMIN                            :  3;  // Bits 17:15
    UINT32 DMIVCM_NPMIN                            :  3;  // Bits 20:18
    UINT32 DMIVC1_NPMIN                            :  3;  // Bits 23:21
    UINT32 CAMVC0_NPMIN                            :  3;  // Bits 26:24
    UINT32 GMMVC0_NPMIN                            :  3;  // Bits 29:27
    UINT32                                         :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MPRDRTRN_CR_CRDTCTL1_IMPH_STRUCT;

typedef union {
  struct {
    UINT32 DMIVC0_RRMIN                            :  3;  // Bits 2:0
    UINT32 P10VC0_RRMIN                            :  3;  // Bits 5:3
    UINT32 P11VC0_RRMIN                            :  3;  // Bits 8:6
    UINT32 P12VC0_RRMIN                            :  3;  // Bits 11:9
    UINT32 DEVC0_RRMIN                             :  3;  // Bits 14:12
    UINT32 DMIVCP_RRMIN                            :  3;  // Bits 17:15
    UINT32 DMIVCM_RRMIN                            :  3;  // Bits 20:18
    UINT32 DMIVC1_RRMIN                            :  3;  // Bits 23:21
    UINT32 DEVC1_RRMIN                             :  6;  // Bits 29:24
    UINT32                                         :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MPRDRTRN_CR_CRDTCTL2_IMPH_STRUCT;

typedef union {
  struct {
    UINT32 CAMVC0_RRMIN                            :  3;  // Bits 2:0
    UINT32 GMMVC0_RRMIN                            :  3;  // Bits 5:3
    UINT32                                         :  26;  // Bits 31:6
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MPRDRTRN_CR_CRDTCTL3_IMPH_STRUCT;

typedef union {
  struct {
    UINT32 IOTRK_SHRD                              :  6;  // Bits 5:0
    UINT32 RRTRK_SHRD                              :  6;  // Bits 11:6
    UINT32                                         :  20;  // Bits 31:12
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MPRDRTRN_CR_CRDTCTL4_IMPH_STRUCT;

typedef union {
  struct {
    UINT32 DMIVC0_PMAX                             :  5;  // Bits 4:0
    UINT32 P10VC0_PMAX                             :  5;  // Bits 9:5
    UINT32 P11VC0_PMAX                             :  5;  // Bits 14:10
    UINT32 P12VC0_PMAX                             :  5;  // Bits 19:15
    UINT32 DEVC0_PMAX                              :  5;  // Bits 24:20
    UINT32                                         :  7;  // Bits 31:25
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MPRDRTRN_CR_CRDTCTL5_IMPH_STRUCT;

typedef union {
  struct {
    UINT32 DMIVCP_PMAX                             :  5;  // Bits 4:0
    UINT32 DMIVCM_PMAX                             :  5;  // Bits 9:5
    UINT32 DMIVC1_PMAX                             :  5;  // Bits 14:10
    UINT32 CAMVC0_PMAX                             :  5;  // Bits 19:15
    UINT32 GMMVC0_PMAX                             :  5;  // Bits 24:20
    UINT32                                         :  7;  // Bits 31:25
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MPRDRTRN_CR_CRDTCTL6_IMPH_STRUCT;

typedef union {
  struct {
    UINT32 DMIVC0_NPMAX                            :  5;  // Bits 4:0
    UINT32 P10VC0_NPMAX                            :  5;  // Bits 9:5
    UINT32 P11VC0_NPMAX                            :  5;  // Bits 14:10
    UINT32 P12VC0_NPMAX                            :  5;  // Bits 19:15
    UINT32 DEVC0_NPMAX                             :  5;  // Bits 24:20
    UINT32                                         :  7;  // Bits 31:25
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MPRDRTRN_CR_CRDTCTL7_IMPH_STRUCT;

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
} MPRDRTRN_CR_VISA_CTL_MPIORDTRKS_IMPH_STRUCT;

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
} MPRDRTRN_CR_VISA_XBAR_MPIORDTRKS_IMPH_STRUCT;

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
} MPRDRTRN_CR_VISA_CTL_MPIOTRKS_IMPH_STRUCT;

typedef union {
  struct {
    UINT32 ILLCFGDROP                              :  1;  // Bits 0:0
    UINT32 UNSUCFULLCKRDDROP                       :  1;  // Bits 1:1
    UINT32                                         :  30;  // Bits 31:2
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MPRDRTRN_CR_ERR_LOG1_IMPH_STRUCT;

typedef union {
  struct {
    UINT32 VC                                      :  4;  // Bits 3:0
    UINT32 FMT_CMDTYPE                             :  6;  // Bits 9:4
    UINT32 TC                                      :  4;  // Bits 13:10
    UINT32 NS                                      :  1;  // Bits 14:14
    UINT32 RO                                      :  1;  // Bits 15:15
    UINT32 LENGTH                                  :  5;  // Bits 20:16
    UINT32 EP                                      :  1;  // Bits 21:21
    UINT32                                         :  10;  // Bits 31:22
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MPRDRTRN_CR_PRIMDN_MASK1_IMPH_STRUCT;

typedef union {
  struct {
    UINT32 RQID                                    :  16;  // Bits 15:0
    UINT32 TAG                                     :  8;  // Bits 23:16
    UINT32 LBEFBE_MSGTYPE                          :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MPRDRTRN_CR_PRIMDN_MASK2_IMPH_STRUCT;

typedef union {
  struct {
    UINT32 ADDR_31_0                               :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MPRDRTRN_CR_PRIMDN_MASK3_IMPH_STRUCT;

typedef union {
  struct {
    UINT32 ADDR_63_32                              :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MPRDRTRN_CR_PRIMDN_MASK4_IMPH_STRUCT;

typedef union {
  struct {
    UINT32 VC                                      :  4;  // Bits 3:0
    UINT32 FMT_CMDTYPE                             :  6;  // Bits 9:4
    UINT32 TC                                      :  4;  // Bits 13:10
    UINT32 EP                                      :  1;  // Bits 14:14
    UINT32 NS                                      :  1;  // Bits 15:15
    UINT32 RO                                      :  1;  // Bits 16:16
    UINT32 LENGTH                                  :  5;  // Bits 21:17
    UINT32                                         :  10;  // Bits 31:22
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MPRDRTRN_CR_PRIMDN_COMP1_IMPH_STRUCT;

typedef union {
  struct {
    UINT32 RQID                                    :  16;  // Bits 15:0
    UINT32 TAG                                     :  8;  // Bits 23:16
    UINT32 LBEFBE_MSGTYPE                          :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MPRDRTRN_CR_PRIMDN_COMP2_IMPH_STRUCT;

typedef union {
  struct {
    UINT32 ADDR_31_0                               :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MPRDRTRN_CR_PRIMDN_COMP3_IMPH_STRUCT;

typedef union {
  struct {
    UINT32 ADDR_63_32                              :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MPRDRTRN_CR_PRIMDN_COMP4_IMPH_STRUCT;

typedef union {
  struct {
    UINT32 ENABLE                                  :  1;  // Bits 0:0
    UINT32 TRIGGERED                               :  1;  // Bits 1:1
    UINT32 STALL_DNARB                             :  1;  // Bits 2:2
    UINT32                                         :  20;  // Bits 22:3
    UINT32 STALL_DELAY                             :  9;  // Bits 31:23
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MPRDRTRN_CR_PRIMDN_TRIGGER_IMPH_STRUCT;

typedef union {
  struct {
    UINT32 DMIVCP_NPMAX                            :  5;  // Bits 4:0
    UINT32 DMIVCM_NPMAX                            :  5;  // Bits 9:5
    UINT32 DMIVC1_NPMAX                            :  5;  // Bits 14:10
    UINT32 CAMVC0_NPMAX                            :  5;  // Bits 19:15
    UINT32 GMMVC0_NPMAX                            :  5;  // Bits 24:20
    UINT32                                         :  7;  // Bits 31:25
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MPRDRTRN_CR_CRDTCTL8_IMPH_STRUCT;

typedef union {
  struct {
    UINT32 DMIVC0_RRMAX                            :  6;  // Bits 5:0
    UINT32 P10VC0_RRMAX                            :  6;  // Bits 11:6
    UINT32 P11VC0_RRMAX                            :  6;  // Bits 17:12
    UINT32 P12VC0_RRMAX                            :  6;  // Bits 23:18
    UINT32 DEVC0_RRMAX                             :  6;  // Bits 29:24
    UINT32                                         :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MPRDRTRN_CR_CRDTCTL9_IMPH_STRUCT;

typedef union {
  struct {
    UINT32 CAMVC0_RRMAX                            :  6;  // Bits 5:0
    UINT32 GMMVC0_RRMAX                            :  6;  // Bits 11:6
    UINT32                                         :  20;  // Bits 31:12
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MPRDRTRN_CR_CRDTCTL10_IMPH_STRUCT;

typedef union {
  struct {
    UINT32 DMIVCP_RRMAX                            :  6;  // Bits 5:0
    UINT32 DMIVCM_RRMAX                            :  6;  // Bits 11:6
    UINT32 DMIVC1_RRMAX                            :  6;  // Bits 17:12
    UINT32 DEVC1_RRMAX                             :  6;  // Bits 23:18
    UINT32                                         :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MPRDRTRN_CR_CRDTCTL11_IMPH_STRUCT;

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
} MPRDRTRN_CR_VISA_SLIDE_MPIORDTRKS_IMPH_STRUCT;

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
} MPRDRTRN_CR_VISA_SLIDE_MPIOTRKS_IMPH_STRUCT;

typedef union {
  struct {
    UINT32 IOTRK_SHRD                              :  6;  // Bits 5:0
    UINT32 RRTRK_SHRD                              :  6;  // Bits 11:6
    UINT32                                         :  20;  // Bits 31:12
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MPRDRTRN_CR_CRDTCTL12_IMPH_STRUCT;

typedef union {
  struct {
    UINT32 DMIVC0_PINIT                            :  3;  // Bits 2:0
    UINT32 P10VC0_PINIT                            :  3;  // Bits 5:3
    UINT32 P11VC0_PINIT                            :  3;  // Bits 8:6
    UINT32 P12VC0_PINIT                            :  3;  // Bits 11:9
    UINT32 DEVC0_PINIT                             :  3;  // Bits 14:12
    UINT32 DMIVCP_PINIT                            :  3;  // Bits 17:15
    UINT32 DMIVCM_PINIT                            :  3;  // Bits 20:18
    UINT32 DMIVC1_PINIT                            :  3;  // Bits 23:21
    UINT32 CAMVC0_PINIT                            :  3;  // Bits 26:24
    UINT32 GMMVC0_PINIT                            :  3;  // Bits 29:27
    UINT32                                         :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MPRDRTRN_CR_CRDTCTL13_IMPH_STRUCT;

typedef union {
  struct {
    UINT32 DMIVC0_NPINIT                           :  3;  // Bits 2:0
    UINT32 P10VC0_NPINIT                           :  3;  // Bits 5:3
    UINT32 P11VC0_NPINIT                           :  3;  // Bits 8:6
    UINT32 P12VC0_NPINIT                           :  3;  // Bits 11:9
    UINT32 DEVC0_NPINIT                            :  3;  // Bits 14:12
    UINT32 DMIVCP_NPINIT                           :  3;  // Bits 17:15
    UINT32 DMIVCM_NPINIT                           :  3;  // Bits 20:18
    UINT32 DMIVC1_NPINIT                           :  3;  // Bits 23:21
    UINT32 CAMVC0_NPINIT                           :  3;  // Bits 26:24
    UINT32 GMMVC0_NPINIT                           :  3;  // Bits 29:27
    UINT32                                         :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MPRDRTRN_CR_CRDTCTL14_IMPH_STRUCT;

typedef union {
  struct {
    UINT32 LIM                                     :  16;  // Bits 15:0
    UINT32 MSK                                     :  3;  // Bits 18:16
    UINT32                                         :  13;  // Bits 31:19
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MPRDRTRN_CR_PCIE_POPUP_CTL_IMPH_STRUCT;

typedef union {
  struct {
    UINT32 FUNNUM                                  :  3;  // Bits 2:0
    UINT32 DEVNUM                                  :  5;  // Bits 7:3
    UINT32 BUSNUM                                  :  8;  // Bits 15:8
    UINT32 BARNUM                                  :  3;  // Bits 18:16
    UINT32                                         :  13;  // Bits 31:19
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MPRDRTRN_CR_VDMBDFBARSSKU_IMPH_STRUCT;

typedef union {
  struct {
    UINT32 NON_VC1_THRESHOLD                       :  4;  // Bits 3:0
    UINT32 VC1_RD_THRESHOLD                        :  4;  // Bits 7:4
    UINT32 FIXED_RATE_EN                           :  1;  // Bits 8:8
    UINT32 HIGH_PRIO_LIM                           :  3;  // Bits 11:9
    UINT32 LOW_PRIO_LIM                            :  3;  // Bits 14:12
    UINT32 SPARE                                   :  1;  // Bits 15:15
    UINT32                                         :  16;  // Bits 31:16
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MPRDRTRN_CR_IOTRK_CRDT_RTRN_IPC_IMPH_STRUCT;

typedef union {
  struct {
    UINT32 NON_VC1_THRESHOLD                       :  4;  // Bits 3:0
    UINT32 VC1_RD_THRESHOLD                        :  4;  // Bits 7:4
    UINT32 FIXED_RATE_EN                           :  1;  // Bits 8:8
    UINT32 HIGH_PRIO_LIM                           :  3;  // Bits 11:9
    UINT32 LOW_PRIO_LIM                            :  3;  // Bits 14:12
    UINT32 SPARE                                   :  1;  // Bits 15:15
    UINT32                                         :  16;  // Bits 31:16
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MPRDRTRN_CR_XTM_UPSTREAM_ARB_IPC_IMPH_STRUCT;

typedef union {
  struct {
    UINT32 NON_VC1_THRESHOLD                       :  4;  // Bits 3:0
    UINT32 VC1_RD_THRESHOLD                        :  4;  // Bits 7:4
    UINT32 FIXED_RATE_EN                           :  1;  // Bits 8:8
    UINT32 HIGH_PRIO_LIM                           :  3;  // Bits 11:9
    UINT32 LOW_PRIO_LIM                            :  3;  // Bits 14:12
    UINT32 SPARE                                   :  1;  // Bits 15:15
    UINT32                                         :  16;  // Bits 31:16
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MPRDRTRN_CR_XTM_DOWNSTREAM_ARB_IPC_IMPH_STRUCT;

typedef union {
  struct {
    UINT32 LOCK                                    :  1;  // Bits 0:0
    UINT32                                         :  31;  // Bits 31:1
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MPRDRTRN_CR_CRDTLCK_IMPH_STRUCT;

typedef union {
  struct {
    UINT32 VCPNPLIM                                :  3;  // Bits 2:0
    UINT32                                         :  1;  // Bits 3:3
    UINT32 VCPPLIM                                 :  3;  // Bits 6:4
    UINT32                                         :  1;  // Bits 7:7
    UINT32 VCMNPLIM                                :  3;  // Bits 10:8
    UINT32                                         :  1;  // Bits 11:11
    UINT32 VCMPLIM                                 :  3;  // Bits 14:12
    UINT32                                         :  1;  // Bits 15:15
    UINT32 VC0VTDLIM                               :  3;  // Bits 18:16
    UINT32                                         :  1;  // Bits 19:19
    UINT32 VCPVTDLIM                               :  3;  // Bits 22:20
    UINT32                                         :  9;  // Bits 31:23
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MPMCARB_CR_VCLIM0_IMPH_STRUCT;

typedef union {
  struct {
    UINT32                                         :  8;  // Bits 7:0
    UINT32 VTDL3                                   :  3;  // Bits 10:8
    UINT32                                         :  1;  // Bits 11:11
    UINT32 VTDNL3                                  :  3;  // Bits 14:12
    UINT32                                         :  17;  // Bits 31:15
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MPMCARB_CR_VCLIM1_IMPH_STRUCT;

typedef union {
  struct {
    UINT32 XTM_VC0_RD                              :  3;  // Bits 2:0
    UINT32                                         :  1;  // Bits 3:3
    UINT32 XTM_VC0_WR                              :  3;  // Bits 6:4
    UINT32                                         :  1;  // Bits 7:7
    UINT32 NTR_VC0_RD                              :  3;  // Bits 10:8
    UINT32                                         :  1;  // Bits 11:11
    UINT32 NTR_VC0_WR                              :  3;  // Bits 14:12
    UINT32                                         :  17;  // Bits 31:15
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MPMCARB_CR_XTM_NTR_REQ_LIM_IMPH_STRUCT;

typedef union {
  struct {
    UINT32 XTM_VC0_RD                              :  3;  // Bits 2:0
    UINT32                                         :  1;  // Bits 3:3
    UINT32 XTM_VC0_WR                              :  3;  // Bits 6:4
    UINT32                                         :  1;  // Bits 7:7
    UINT32 NTR_VC0_RD                              :  3;  // Bits 10:8
    UINT32                                         :  1;  // Bits 11:11
    UINT32 NTR_VC0_WR                              :  3;  // Bits 14:12
    UINT32                                         :  1;  // Bits 15:15
    UINT32 MEE_VC0_RD                              :  3;  // Bits 18:16
    UINT32                                         :  1;  // Bits 19:19
    UINT32 MEE_VC0_WR                              :  3;  // Bits 22:20
    UINT32                                         :  1;  // Bits 23:23
    UINT32 EFLOW_VC0_RD                            :  3;  // Bits 26:24
    UINT32                                         :  1;  // Bits 27:27
    UINT32 EFLOW_VC0_WR                            :  3;  // Bits 30:28
    UINT32                                         :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MPMCARB_CR_RCH_REQ_ARB_MC_MEE_LIM_IMPH_STRUCT;

typedef union {
  struct {
    UINT32 XTM_VC0_RD                              :  3;  // Bits 2:0
    UINT32                                         :  1;  // Bits 3:3
    UINT32 XTM_VC0_WR                              :  3;  // Bits 6:4
    UINT32                                         :  1;  // Bits 7:7
    UINT32 NTR_VC0_RD                              :  3;  // Bits 10:8
    UINT32                                         :  1;  // Bits 11:11
    UINT32 NTR_VC0_WR                              :  3;  // Bits 14:12
    UINT32                                         :  15;  // Bits 29:15
    UINT32 PARALLEL_UNBLOCK                        :  1;  // Bits 30:30
    UINT32 EFLOW_ENABLED                           :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MPMCARB_CR_RCH_REQ_ARB_EFLOW_LIM_IMPH_STRUCT;

typedef union {
  struct {
    UINT32 MC_VC0_RD_CMP                           :  3;  // Bits 2:0
    UINT32                                         :  1;  // Bits 3:3
    UINT32 MEE_VC0_RD_CMP                          :  3;  // Bits 6:4
    UINT32                                         :  1;  // Bits 7:7
    UINT32 EFLOW_VC0_RD_CMP                        :  3;  // Bits 10:8
    UINT32                                         :  21;  // Bits 31:11
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MPMCARB_CR_RCH_RD_CMP_ARB_NTR_XTM_LIM_IMPH_STRUCT;

typedef union {
  struct {
    UINT32 MC_VC0_RD_CMP                           :  3;  // Bits 2:0
    UINT32                                         :  1;  // Bits 3:3
    UINT32 MEE_VC0_RD_CMP                          :  3;  // Bits 6:4
    UINT32                                         :  25;  // Bits 31:7
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MPMCARB_CR_RCH_RD_CMP_ARB_EFLOW_LIM_IMPH_STRUCT;

typedef union {
  struct {
    UINT32 DMI_VC0_RD_FILL                         :  1;  // Bits 0:0
    UINT32 DMI_VC0_WR_FILL                         :  1;  // Bits 1:1
    UINT32 DMI_VCM_RD_FILL                         :  1;  // Bits 2:2
    UINT32 DMI_VCM_WR_FILL                         :  1;  // Bits 3:3
    UINT32 DMI_VC1_RD_FILL                         :  1;  // Bits 4:4
    UINT32 DMI_VC1_WR_FILL                         :  1;  // Bits 5:5
    UINT32 PEG10_RD_FILL                           :  1;  // Bits 6:6
    UINT32 PEG10_WR_FILL                           :  1;  // Bits 7:7
    UINT32 PEG11_RD_FILL                           :  1;  // Bits 8:8
    UINT32 PEG11_WR_FILL                           :  1;  // Bits 9:9
    UINT32 PEG12_RD_FILL                           :  1;  // Bits 10:10
    UINT32 PEG12_WR_FILL                           :  1;  // Bits 11:11
    UINT32 DE_VC0_RD_FILL                          :  1;  // Bits 12:12
    UINT32 DE_VC0_WR_FILL                          :  1;  // Bits 13:13
    UINT32 DE_VC1_RD_FILL                          :  1;  // Bits 14:14
    UINT32 CAM_RD_FILL                             :  1;  // Bits 15:15
    UINT32 CAM_WR_FILL                             :  1;  // Bits 16:16
    UINT32 GMM_RD_FILL                             :  1;  // Bits 17:17
    UINT32 GMM_WR_FILL                             :  1;  // Bits 18:18
    UINT32 MISC_FILL                               :  1;  // Bits 19:19
    UINT32                                         :  12;  // Bits 31:20
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MPMCARB_CR_XTM_EDRAM_FILL_POLICY_IMPH_STRUCT;

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
} MPMCARB_CR_VISA_CTL_MPMCARBS_F_IMPH_STRUCT;

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
} MPMCARB_CR_VISA_CTL_MPMCARBS_D_IMPH_STRUCT;

typedef union {
  struct {
    UINT32 noa_demux                               :  1;  // Bits 0:0
    UINT32 noa_countctrl                           :  1;  // Bits 1:1
    UINT32                                         :  30;  // Bits 31:2
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MPMCARB_CR_VISA_QD_DEMUX_MPMCARBS_IMPH_STRUCT;

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
} MPMCARB_CR_VISA_XBAR_MPMCARBS_D_IMPH_STRUCT;

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
} MPMCARB_CR_VISA_SLIDE_MPMCARBS_F_IMPH_STRUCT;

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
} MPMCARB_CR_VISA_SLIDE_MPMCARBS_D_IMPH_STRUCT;

typedef union {
  struct {
    UINT32 RDMARK                                  :  8;  // Bits 7:0
    UINT32 WRMARK                                  :  8;  // Bits 15:8
    UINT32                                         :  16;  // Bits 31:16
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MPMCARB_CR_RCH_RING_TRTL_IMPH_STRUCT;

typedef union {
  struct {
    UINT32 NON_VC1_THRESHOLD                       :  4;  // Bits 3:0
    UINT32 VC1_RD_THRESHOLD                        :  4;  // Bits 7:4
    UINT32 FIXED_RATE_EN                           :  1;  // Bits 8:8
    UINT32 HIGH_PRIO_LIM                           :  3;  // Bits 11:9
    UINT32 LOW_PRIO_LIM                            :  3;  // Bits 14:12
    UINT32 SPARE                                   :  1;  // Bits 15:15
    UINT32                                         :  16;  // Bits 31:16
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MPMCARB_CR_RCH_REQ_ARB_MC_MEE_IPC_IMPH_STRUCT;

typedef union {
  struct {
    UINT32 NON_VC1_THRESHOLD                       :  4;  // Bits 3:0
    UINT32 VC1_RD_THRESHOLD                        :  4;  // Bits 7:4
    UINT32 FIXED_RATE_EN                           :  1;  // Bits 8:8
    UINT32 HIGH_PRIO_LIM                           :  3;  // Bits 11:9
    UINT32 LOW_PRIO_LIM                            :  3;  // Bits 14:12
    UINT32 SPARE                                   :  1;  // Bits 15:15
    UINT32                                         :  16;  // Bits 31:16
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MPMCARB_CR_RCH_REQ_ARB_EFLOW_IPC_IMPH_STRUCT;

typedef union {
  struct {
    UINT32 NON_VC1_THRESHOLD                       :  4;  // Bits 3:0
    UINT32 VC1_RD_THRESHOLD                        :  4;  // Bits 7:4
    UINT32 FIXED_RATE_EN                           :  1;  // Bits 8:8
    UINT32 HIGH_PRIO_LIM                           :  3;  // Bits 11:9
    UINT32 LOW_PRIO_LIM                            :  3;  // Bits 14:12
    UINT32 SPARE                                   :  1;  // Bits 15:15
    UINT32                                         :  16;  // Bits 31:16
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MPMCARB_CR_RCH_RD_CMP_ARB_NTR_XTM_IPC_IMPH_STRUCT;

typedef union {
  struct {
    UINT32 NON_VC1_THRESHOLD                       :  4;  // Bits 3:0
    UINT32 VC1_RD_THRESHOLD                        :  4;  // Bits 7:4
    UINT32 FIXED_RATE_EN                           :  1;  // Bits 8:8
    UINT32 HIGH_PRIO_LIM                           :  3;  // Bits 11:9
    UINT32 LOW_PRIO_LIM                            :  3;  // Bits 14:12
    UINT32 SPARE                                   :  1;  // Bits 15:15
    UINT32                                         :  16;  // Bits 31:16
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MPMCARB_CR_XTM_NTR_REQ_IPC_IMPH_STRUCT;

typedef union {
  struct {
    UINT32 ISOCH_WINDOW_PH1                        :  5;  // Bits 4:0
    UINT32 ISOCH_WINDOW_PH2                        :  5;  // Bits 9:5
    UINT32 NON_ISOCH_WINDOW_PH1                    :  5;  // Bits 14:10
    UINT32 NON_ISOCH_WINDOW_PH2                    :  5;  // Bits 19:15
    UINT32 FORCE_DMI_VC1_DEMOTE                    :  1;  // Bits 20:20
    UINT32 IGNORE_IOSF_VC1_DEMOTE                  :  1;  // Bits 21:21
    UINT32 FORCE_VC1_DEMOTE                        :  1;  // Bits 22:22
    UINT32 IGNORE_VC1_DEMOTE                       :  1;  // Bits 23:23
    UINT32 SPARE                                   :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MPMCARB_CR_XTM_IPC_GLOBAL_PACER_IMPH_STRUCT;

typedef union {
  struct {
    UINT32 LOCK                                    :  1;  // Bits 0:0
    UINT32                                         :  31;  // Bits 31:1
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MPMCARB_CR_MCARBLCK_IMPH_STRUCT;

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
} MEECR_CR_VISA_CTL_MEDEC_MEE_STRUCT;

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
} MEECR_CR_VISA_XBAR_MEDEC_MEE_STRUCT;

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
} MEECR_CR_VISA_SLIDE_MEDEC_MEE_STRUCT;

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
} MEECR_CR_VISA_CTL_MEENC_MEE_STRUCT;

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
} MEECR_CR_VISA_XBAR_MEENC_MEE_STRUCT;

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
} MEECR_CR_VISA_SLIDE_MEENC_MEE_STRUCT;

typedef union {
  struct {
    UINT32 MEE_VC0_RD                              :  3;  // Bits 2:0
    UINT32 MEE_VC0_WR                              :  3;  // Bits 5:3
    UINT32                                         :  26;  // Bits 31:6
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MEECR_CR_MEE_REQ_RSP_LIM_MEE_STRUCT;

typedef union {
  struct {
    UINT32 NON_VC1_THRESHOLD                       :  4;  // Bits 3:0
    UINT32 VC1_RD_THRESHOLD                        :  4;  // Bits 7:4
    UINT32 FIXED_RATE_EN                           :  1;  // Bits 8:8
    UINT32 HIGH_PRIO_LIM                           :  3;  // Bits 11:9
    UINT32 LOW_PRIO_LIM                            :  3;  // Bits 14:12
    UINT32 SPARE                                   :  1;  // Bits 15:15
    UINT32                                         :  16;  // Bits 31:16
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MEECR_CR_RCH_RD_CMP_ARB_EFLOW_IPC_MEE_STRUCT;

typedef union {
  struct {
    UINT32 MC_VC1                                  :  3;  // Bits 2:0
    UINT32                                         :  1;  // Bits 3:3
    UINT32 MC_VC0                                  :  3;  // Bits 6:4
    UINT32                                         :  1;  // Bits 7:7
    UINT32 MEE_VC0                                 :  3;  // Bits 10:8
    UINT32                                         :  21;  // Bits 31:11
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MEECR_CR_RCH_RD_CMP_ARB_EFLOW_LIM_MEE_STRUCT;

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
} MEECR_CR_VISA_CTL_MEMAIN_MEE_STRUCT;

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
} MEECR_CR_VISA_XBAR_MEMAIN_MEE_STRUCT;

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
} MEECR_CR_VISA_SLIDE_MEMAIN_MEE_STRUCT;

#pragma pack(pop)
#endif
