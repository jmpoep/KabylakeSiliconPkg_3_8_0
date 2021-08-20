#ifndef __MrcMcRegisterStruct6xxx_h__
#define __MrcMcRegisterStruct6xxx_h__
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
    UINT32 VCPVTDLIM                               :  3;  // Bits 2:0
    UINT32                                         :  29;  // Bits 31:3
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MPVTDTRK_CR_VTDLIM_IMPH_STRUCT;

typedef union {
  struct {
    UINT32                                         :  3;  // Bits 2:0
    UINT32 DEVNUM                                  :  5;  // Bits 7:3
    UINT32 BUSNUM                                  :  8;  // Bits 15:8
    UINT32                                         :  15;  // Bits 30:16
    UINT32 HDAUD_EN                                :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MPVTDTRK_CR_HDAUDRID_IMPH_STRUCT;

typedef union {
  struct {
    UINT32                                         :  20;  // Bits 19:0
    UINT32 UMABLow                                 :  12;  // Bits 31:20
    UINT32 UMABHigh                                :  7;  // Bits 38:32
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} MPVTDTRK_CR_UMAGFXBASE_IMPH_STRUCT;

typedef union {
  struct {
    UINT32                                         :  20;  // Bits 19:0
    UINT32 UMALLow                                 :  12;  // Bits 31:20
    UINT32 UMALHigh                                :  7;  // Bits 38:32
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} MPVTDTRK_CR_UMAGFXLIMIT_IMPH_STRUCT;

typedef union {
  struct {
    UINT32 LCK                                     :  1;  // Bits 0:0
    UINT32                                         :  9;  // Bits 9:1
    UINT32 PEG10EN                                 :  1;  // Bits 10:10
    UINT32 PEG11EN                                 :  1;  // Bits 11:11
    UINT32 PEG12EN                                 :  1;  // Bits 12:12
    UINT32 DMIEN                                   :  1;  // Bits 13:13
    UINT32 PEG60EN                                 :  1;  // Bits 14:14
    UINT32                                         :  17;  // Bits 31:15
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MPVTDTRK_CR_UMAGFXCTL_IMPH_STRUCT;

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
} MPVTDTRK_CR_VISA_SLIDE_MPVTTRKS_IMPH_STRUCT;

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
} MPVTDTRK_CR_VISA_SLIDE_MPVTMISCS_IMPH_STRUCT;

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
} MPVTDTRK_CR_VDMBDFBARKVM_IMPH_STRUCT;

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
} MPVTDTRK_CR_VDMBDFBARPAVP_IMPH_STRUCT;

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
} MPVTDTRK_CR_VISA_SLIDE_MPVTDTLBS_IMPH_STRUCT;

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
} MPVTDTRK_CR_VISA_CTL_MPVTDTLBS_IMPH_STRUCT;

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
} MPVTDTRK_CR_VISA_XBAR_MPVTDTLBS_IMPH_STRUCT;

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
} MPVTDTRK_CR_VISA_CTL_MPVTMISCS_IMPH_STRUCT;

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
} MPVTDTRK_CR_VISA_CTL_MPVTTRKS_IMPH_STRUCT;

typedef union {
  struct {
    UINT32 VC                                      :  4;  // Bits 3:0
    UINT32 FMT_CMDTYPE                             :  6;  // Bits 9:4
    UINT32 TC                                      :  4;  // Bits 13:10
    UINT32 CHAIN                                   :  1;  // Bits 14:14
    UINT32 NS                                      :  1;  // Bits 15:15
    UINT32 RO                                      :  1;  // Bits 16:16
    UINT32 LENGTH                                  :  5;  // Bits 21:17
    UINT32 EP                                      :  1;  // Bits 22:22
    UINT32 AT                                      :  2;  // Bits 24:23
    UINT32                                         :  7;  // Bits 31:25
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MPVTDTRK_CR_PRIMUP_MASK1_IMPH_STRUCT;

typedef union {
  struct {
    UINT32 RQID                                    :  16;  // Bits 15:0
    UINT32 TAG                                     :  8;  // Bits 23:16
    UINT32 LBEFBE_MSGTYPE                          :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MPVTDTRK_CR_PRIMUP_MASK2_IMPH_STRUCT;

typedef union {
  struct {
    UINT32 ADDR_31_0                               :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MPVTDTRK_CR_PRIMUP_MASK3_IMPH_STRUCT;

typedef union {
  struct {
    UINT32 ADDR_63_32                              :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MPVTDTRK_CR_PRIMUP_MASK4_IMPH_STRUCT;

typedef union {
  struct {
    UINT32 VC                                      :  4;  // Bits 3:0
    UINT32 FMT_CMDTYPE                             :  6;  // Bits 9:4
    UINT32 TC                                      :  4;  // Bits 13:10
    UINT32 CHAIN                                   :  1;  // Bits 14:14
    UINT32 NS                                      :  1;  // Bits 15:15
    UINT32 RO                                      :  1;  // Bits 16:16
    UINT32 LENGTH                                  :  5;  // Bits 21:17
    UINT32 EP                                      :  1;  // Bits 22:22
    UINT32 AT                                      :  2;  // Bits 24:23
    UINT32                                         :  7;  // Bits 31:25
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MPVTDTRK_CR_PRIMUP_COMP1_IMPH_STRUCT;

typedef union {
  struct {
    UINT32 RQID                                    :  16;  // Bits 15:0
    UINT32 TAG                                     :  8;  // Bits 23:16
    UINT32 LBEFBE_MSGTYPE                          :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MPVTDTRK_CR_PRIMUP_COMP2_IMPH_STRUCT;

typedef union {
  struct {
    UINT32 ADDR_31_0                               :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MPVTDTRK_CR_PRIMUP_COMP3_IMPH_STRUCT;

typedef union {
  struct {
    UINT32 ADDR_63_32                              :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MPVTDTRK_CR_PRIMUP_COMP4_IMPH_STRUCT;

typedef union {
  struct {
    UINT32 ENABLE                                  :  1;  // Bits 0:0
    UINT32 TRIGGERED                               :  1;  // Bits 1:1
    UINT32 STALL_DNARB                             :  1;  // Bits 2:2
    UINT32 STALL_UPARB                             :  1;  // Bits 3:3
    UINT32 STALL_SNPARB                            :  1;  // Bits 4:4
    UINT32                                         :  18;  // Bits 22:5
    UINT32 STALL_DELAY                             :  9;  // Bits 31:23
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MPVTDTRK_CR_PRIMUP_TRIGGER_IMPH_STRUCT;

typedef union {
  struct {
    UINT32 PEG2DMIDIS                              :  1;  // Bits 0:0
    UINT32 EOIB                                    :  1;  // Bits 1:1
    UINT32 MSIBYPDIS                               :  1;  // Bits 2:2
    UINT32                                         :  1;  // Bits 3:3
    UINT32 PHLDDIS                                 :  1;  // Bits 4:4
    UINT32                                         :  1;  // Bits 5:5
    UINT32 BKSNPDIS                                :  1;  // Bits 6:6
    UINT32 FRCVC0SNP                               :  1;  // Bits 7:7
    UINT32 FRCVCPSNP                               :  1;  // Bits 8:8
    UINT32 PHLDBLKDIS                              :  1;  // Bits 9:9
    UINT32 BLKWRPOSTVC1                            :  1;  // Bits 10:10
    UINT32 DIS_VLW_PEG                             :  1;  // Bits 11:11
    UINT32 SPECRDDIS                               :  1;  // Bits 12:12
    UINT32 IR_RSRV_CTL                             :  1;  // Bits 13:13
    UINT32 IMGU2DMIDIS                             :  1;  // Bits 14:14
    UINT32 GMM2DMIDIS                              :  1;  // Bits 15:15
    UINT32 FORCEREDISP                             :  1;  // Bits 16:16
    UINT32 RSVD                                    :  15;  // Bits 31:17
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MPVTDTRK_CR_HCTL0_IMPH_STRUCT;

typedef union {
  struct {
    UINT32                                         :  4;  // Bits 3:0
    UINT32 REGBARLow                               :  28;  // Bits 31:4
    UINT32 REGBARHigh                              :  7;  // Bits 38:32
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} MPVTDTRK_CR_REGBAR_IMPH_STRUCT;

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
    UINT32                                         :  4;  // Bits 15:12
    UINT32 Temperature                             :  7;  // Bits 22:16
    UINT32                                         :  4;  // Bits 26:23
    UINT32 Resolution                              :  4;  // Bits 30:27
    UINT32 Valid                                   :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MPVTDTRK_CR_PKG_THERM_CAMARILLO_STATUS_IMPH_STRUCT;

typedef union {
  struct {
    UINT32 WARM_THRESHOLD_STATUS                   :  1;  // Bits 0:0
    UINT32 WARM_THRESHOLD_LOG                      :  1;  // Bits 1:1
    UINT32 HOT_THRESHOLD_STATUS                    :  1;  // Bits 2:2
    UINT32 HOT_THRESHOLD_LOG                       :  1;  // Bits 3:3
    UINT32 REFRESH2X_STATUS                        :  1;  // Bits 4:4
    UINT32 REFRESH2X_LOG                           :  1;  // Bits 5:5
    UINT32 OOS_TEMP_STATUS                         :  1;  // Bits 6:6
    UINT32 OOS_TEMP_LOG                            :  1;  // Bits 7:7
    UINT32 THRESHOLD1_STATUS                       :  1;  // Bits 8:8
    UINT32 THRESHOLD1_LOG                          :  1;  // Bits 9:9
    UINT32 THRESHOLD2_STATUS                       :  1;  // Bits 10:10
    UINT32 THRESHOLD2_LOG                          :  1;  // Bits 11:11
    UINT32                                         :  20;  // Bits 31:12
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MPVTDTRK_CR_DDR_THERM_CAMARILLO_STATUS_IMPH_STRUCT;

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
} MPVTDTRK_CR_XTM_DEF_VTD1_ARB_IPC_IMPH_STRUCT;

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
} MPVTDTRK_CR_XTM_DEF_VTD2_ARB_IPC_IMPH_STRUCT;

typedef union {
  struct {
    UINT32 LOCK                                    :  1;  // Bits 0:0
    UINT32                                         :  31;  // Bits 31:1
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MPVTDTRK_CR_VTDTRKLCK_IMPH_STRUCT;

typedef union {
  struct {
    UINT32 NOAFinSel0                              :  3;  // Bits 2:0
    UINT32 DelayCtrl0                              :  5;  // Bits 7:3
    UINT32 NOAFinSel1                              :  3;  // Bits 10:8
    UINT32 DelayCtrl1                              :  5;  // Bits 15:11
    UINT32 NOAFinSel2                              :  3;  // Bits 18:16
    UINT32 DelayCtrl2                              :  5;  // Bits 23:19
    UINT32 NOAFinSel3                              :  3;  // Bits 26:24
    UINT32 DelayCtrl3                              :  5;  // Bits 31:27
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} NOA_CR_FIN_MUX_CFG_1_LO_NOA_STRUCT;

typedef union {
  struct {
    UINT32 NOAFinSel4                              :  3;  // Bits 2:0
    UINT32 DelayCtrl4                              :  5;  // Bits 7:3
    UINT32 NOAFinSel5                              :  3;  // Bits 10:8
    UINT32 DelayCtrl5                              :  5;  // Bits 15:11
    UINT32 NOAFinSel6                              :  3;  // Bits 18:16
    UINT32 DelayCtrl6                              :  5;  // Bits 23:19
    UINT32 NOAFinSel7                              :  3;  // Bits 26:24
    UINT32 DelayCtrl7                              :  5;  // Bits 31:27
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} NOA_CR_FIN_MUX_CFG_1_HI_NOA_STRUCT;

typedef union {
  struct {
    UINT32 NOAFinSel8                              :  3;  // Bits 2:0
    UINT32 DelayCtrl8                              :  5;  // Bits 7:3
    UINT32 NOAFinSel9                              :  3;  // Bits 10:8
    UINT32 DelayCtrl9                              :  5;  // Bits 15:11
    UINT32 NOAFinSel10                             :  3;  // Bits 18:16
    UINT32 DelayCtrl10                             :  5;  // Bits 23:19
    UINT32 NOAFinSel11                             :  3;  // Bits 26:24
    UINT32 DelayCtrl11                             :  5;  // Bits 31:27
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} NOA_CR_FIN_MUX_CFG_2_LO_NOA_STRUCT;

typedef union {
  struct {
    UINT32 NOAFinSel12                             :  3;  // Bits 2:0
    UINT32 DelayCtrl12                             :  5;  // Bits 7:3
    UINT32 NOAFinSel13                             :  3;  // Bits 10:8
    UINT32 DelayCtrl13                             :  5;  // Bits 15:11
    UINT32 NOAFinSel14                             :  3;  // Bits 18:16
    UINT32 DelayCtrl14                             :  5;  // Bits 23:19
    UINT32 NOAFinSel15                             :  3;  // Bits 26:24
    UINT32 DelayCtrl15                             :  5;  // Bits 31:27
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} NOA_CR_FIN_MUX_CFG_2_HI_NOA_STRUCT;

typedef union {
  struct {
    UINT32 NOA_1_CLK_SEL                           :  3;  // Bits 2:0
    UINT32 NOA_2_CLK_SEL                           :  3;  // Bits 5:3
    UINT32 NOA_FIN_SEL                             :  2;  // Bits 7:6
    UINT32 SPARE                                   :  8;  // Bits 15:8
    UINT32                                         :  16;  // Bits 31:16
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} NOA_CR_FIN_MUX_CFG_3_NOA_STRUCT;

typedef union {
  struct {
    UINT32 Data                                    :  16;  // Bits 15:0
    UINT32                                         :  16;  // Bits 31:16
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} NOA_CR_NOA_DEBUG_1_NOA_STRUCT;

typedef union {
  struct {
    UINT32 Data                                    :  16;  // Bits 15:0
    UINT32                                         :  16;  // Bits 31:16
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} NOA_CR_NOA_DEBUG_2_NOA_STRUCT;

typedef union {
  struct {
    UINT32 PAT_BIT0                                :  8;  // Bits 7:0
    UINT32 PAT_BIT1                                :  8;  // Bits 15:8
    UINT32 PAT_BIT2                                :  8;  // Bits 23:16
    UINT32 PAT_BIT3                                :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} NOA_CR_NOA_PAT_GEN_0_3_NOA_STRUCT;

typedef union {
  struct {
    UINT32 PAT_BIT4                                :  8;  // Bits 7:0
    UINT32 PAT_BIT5                                :  8;  // Bits 15:8
    UINT32 PAT_BIT6                                :  8;  // Bits 23:16
    UINT32 PAT_BIT7                                :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} NOA_CR_NOA_PAT_GEN_4_7_NOA_STRUCT;

typedef union {
  struct {
    UINT32 PAT_BIT8                                :  8;  // Bits 7:0
    UINT32 PAT_BIT9                                :  8;  // Bits 15:8
    UINT32 PAT_BIT10                               :  8;  // Bits 23:16
    UINT32 PAT_BIT11                               :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} NOA_CR_NOA_PAT_GEN_8_11_NOA_STRUCT;

typedef union {
  struct {
    UINT32 PAT_BIT12                               :  8;  // Bits 7:0
    UINT32 PAT_BIT13                               :  8;  // Bits 15:8
    UINT32 PAT_BIT14                               :  8;  // Bits 23:16
    UINT32 PAT_BIT15                               :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} NOA_CR_NOA_PAT_GEN_12_15_NOA_STRUCT;

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
} NOA_CR_VISA_CTL_SANOAS_L_NOA_STRUCT;

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
} NOA_CR_VISA_XBAR_SANOAS_L_NOA_STRUCT;

typedef union {
  struct {
    UINT32 Ln0Mask                                 :  8;  // Bits 7:0
    UINT32 Ln1Mask                                 :  8;  // Bits 15:8
    UINT32 AssertMode                              :  1;  // Bits 16:16
    UINT32 CompEn                                  :  1;  // Bits 17:17
    UINT32 Ln0Src                                  :  3;  // Bits 20:18
    UINT32 Ln1Src                                  :  3;  // Bits 23:21
    UINT32 OclaEn                                  :  1;  // Bits 24:24
    UINT32                                         :  7;  // Bits 31:25
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} NOA_CR_VISA2OCLA_CFG_FILTER_NOA_STRUCT;

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
} NOA_CR_VISA_SLIDE_SANOAS_L_NOA_STRUCT;

typedef union {
  struct {
    UINT32 BIT0_DELAY                              :  3;  // Bits 2:0
    UINT32 BIT1_DELAY                              :  3;  // Bits 5:3
    UINT32 BIT2_DELAY                              :  3;  // Bits 8:6
    UINT32 BIT3_DELAY                              :  3;  // Bits 11:9
    UINT32 BIT4_DELAY                              :  3;  // Bits 14:12
    UINT32 BIT5_DELAY                              :  3;  // Bits 17:15
    UINT32 BIT6_DELAY                              :  3;  // Bits 20:18
    UINT32 BIT7_DELAY                              :  3;  // Bits 23:21
    UINT32 BIT8_DELAY                              :  3;  // Bits 26:24
    UINT32 BIT9_DELAY                              :  3;  // Bits 29:27
    UINT32 BIT10_DELAYLow                          :  2;  // Bits 31:30
    UINT32 BIT10_DELAYHigh                         :  1;  // Bits 32:32
    UINT32 BIT11_DELAY                             :  3;  // Bits 35:33
    UINT32 BIT12_DELAY                             :  3;  // Bits 38:36
    UINT32 BIT13_DELAY                             :  3;  // Bits 41:39
    UINT32 BIT14_DELAY                             :  3;  // Bits 44:42
    UINT32 BIT15_DELAY                             :  3;  // Bits 47:45
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} NOA_CR_CHAP_DELAY_CTL_NOA_STRUCT;

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
} DRNG_CR_VISA_CTL_DRNGCTLS_DRNG_STRUCT;

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
} DRNG_CR_VISA_SLIDE_DRNGCTLS_DRNG_STRUCT;

typedef union {
  struct {
    UINT32 RDLIM                                   :  3;  // Bits 2:0
    UINT32                                         :  1;  // Bits 3:3
    UINT32 WRLIM                                   :  3;  // Bits 6:4
    UINT32                                         :  24;  // Bits 30:7
    UINT32 LOCK                                    :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MPCBOTRK_CR_REQLIM_IMPH_STRUCT;

typedef union {
  struct {
    UINT32 HOM0_IA_RD_FILL                         :  1;  // Bits 0:0
    UINT32 HOM0_IA_WR_FILL                         :  1;  // Bits 1:1
    UINT32 HOM0_GT_RD_FILL                         :  1;  // Bits 2:2
    UINT32 HOM0_GT_WR_FILL                         :  1;  // Bits 3:3
    UINT32 HOM0_EV_FILL                            :  1;  // Bits 4:4
    UINT32 HOM1_IWB_FILL                           :  1;  // Bits 5:5
    UINT32 NCS_RD_FILL                             :  1;  // Bits 6:6
    UINT32 NCB_WR_FILL                             :  1;  // Bits 7:7
    UINT32                                         :  8;  // Bits 15:8
    UINT32 HOM0_IA_RD_OVRD                         :  1;  // Bits 16:16
    UINT32 HOM0_IA_WR_OVRD                         :  1;  // Bits 17:17
    UINT32 HOM0_GT_RD_OVRD                         :  1;  // Bits 18:18
    UINT32 HOM0_GT_WR_OVRD                         :  1;  // Bits 19:19
    UINT32 HOM0_EV_OVRD                            :  1;  // Bits 20:20
    UINT32                                         :  10;  // Bits 30:21
    UINT32 LOCK                                    :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MPCBOTRK_CR_NTR_EDRAM_FILL_POLICY_IMPH_STRUCT;

typedef union {
  struct {
    UINT32 Opcode                                  :  16;  // Bits 15:0
    UINT32 Index                                   :  8;  // Bits 23:16
    UINT32                                         :  7;  // Bits 30:24
    UINT32 run_busy                                :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} VCU_CR_CSR_MAILBOX_INTERFACE_VCU_STRUCT;

typedef union {
  struct {
    UINT32 Data                                    :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} VCU_CR_CSR_MAILBOX_DATA_VCU_STRUCT;

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
} VCU_CR_VISA_CTL_VCUIOREGS_VCU_STRUCT;

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
} VCU_CR_VISA_SLIDE_VCUIOREGS_VCU_STRUCT;

#pragma pack(pop)
#endif
