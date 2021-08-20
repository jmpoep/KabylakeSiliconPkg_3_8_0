#ifndef __MrcMcRegisterStruct1xxx_h__
#define __MrcMcRegisterStruct1xxx_h__
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
    UINT32 RxRcvEnPi                               :  9;  // Bits 8:0
    UINT32 RxDqsPPi                                :  6;  // Bits 14:9
    UINT32 RxEq                                    :  5;  // Bits 19:15
    UINT32 RxDqsNPi                                :  6;  // Bits 25:20
    INT32  RxVref                                  :  6;  // Bits 31:26
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA8CH0_CR_RXTRAINRANK0_STRUCT;

typedef union {
  struct {
    UINT32 RxRcvEnPi                               :  9;  // Bits 8:0
    UINT32 RxDqsPPi                                :  6;  // Bits 14:9
    UINT32 RxEq                                    :  5;  // Bits 19:15
    UINT32 RxDqsNPi                                :  6;  // Bits 25:20
    INT32  RxVref                                  :  6;  // Bits 31:26
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA8CH0_CR_RXTRAINRANK1_STRUCT;

typedef union {
  struct {
    UINT32 RxRcvEnPi                               :  9;  // Bits 8:0
    UINT32 RxDqsPPi                                :  6;  // Bits 14:9
    UINT32 RxEq                                    :  5;  // Bits 19:15
    UINT32 RxDqsNPi                                :  6;  // Bits 25:20
    INT32  RxVref                                  :  6;  // Bits 31:26
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA8CH0_CR_RXTRAINRANK2_STRUCT;

typedef union {
  struct {
    UINT32 RxRcvEnPi                               :  9;  // Bits 8:0
    UINT32 RxDqsPPi                                :  6;  // Bits 14:9
    UINT32 RxEq                                    :  5;  // Bits 19:15
    UINT32 RxDqsNPi                                :  6;  // Bits 25:20
    INT32  RxVref                                  :  6;  // Bits 31:26
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA8CH0_CR_RXTRAINRANK3_STRUCT;

typedef union {
  struct {
    UINT32 Lane0                                   :  4;  // Bits 3:0
    UINT32 Lane1                                   :  4;  // Bits 7:4
    UINT32 Lane2                                   :  4;  // Bits 11:8
    UINT32 Lane3                                   :  4;  // Bits 15:12
    UINT32 Lane4                                   :  4;  // Bits 19:16
    UINT32 Lane5                                   :  4;  // Bits 23:20
    UINT32 Lane6                                   :  4;  // Bits 27:24
    UINT32 Lane7                                   :  4;  // Bits 31:28
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA8CH0_CR_RXPERBITRANK0_STRUCT;

typedef union {
  struct {
    UINT32 Lane0                                   :  4;  // Bits 3:0
    UINT32 Lane1                                   :  4;  // Bits 7:4
    UINT32 Lane2                                   :  4;  // Bits 11:8
    UINT32 Lane3                                   :  4;  // Bits 15:12
    UINT32 Lane4                                   :  4;  // Bits 19:16
    UINT32 Lane5                                   :  4;  // Bits 23:20
    UINT32 Lane6                                   :  4;  // Bits 27:24
    UINT32 Lane7                                   :  4;  // Bits 31:28
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA8CH0_CR_RXPERBITRANK1_STRUCT;

typedef union {
  struct {
    UINT32 Lane0                                   :  4;  // Bits 3:0
    UINT32 Lane1                                   :  4;  // Bits 7:4
    UINT32 Lane2                                   :  4;  // Bits 11:8
    UINT32 Lane3                                   :  4;  // Bits 15:12
    UINT32 Lane4                                   :  4;  // Bits 19:16
    UINT32 Lane5                                   :  4;  // Bits 23:20
    UINT32 Lane6                                   :  4;  // Bits 27:24
    UINT32 Lane7                                   :  4;  // Bits 31:28
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA8CH0_CR_RXPERBITRANK2_STRUCT;

typedef union {
  struct {
    UINT32 Lane0                                   :  4;  // Bits 3:0
    UINT32 Lane1                                   :  4;  // Bits 7:4
    UINT32 Lane2                                   :  4;  // Bits 11:8
    UINT32 Lane3                                   :  4;  // Bits 15:12
    UINT32 Lane4                                   :  4;  // Bits 19:16
    UINT32 Lane5                                   :  4;  // Bits 23:20
    UINT32 Lane6                                   :  4;  // Bits 27:24
    UINT32 Lane7                                   :  4;  // Bits 31:28
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA8CH0_CR_RXPERBITRANK3_STRUCT;

typedef union {
  struct {
    UINT32 TxDqDelay                               :  9;  // Bits 8:0
    UINT32 TxDqsDelay                              :  9;  // Bits 17:9
    UINT32 Spare0                                  :  2;  // Bits 19:18
    UINT32 TxEqualization                          :  6;  // Bits 25:20
    UINT32 Spare1                                  :  6;  // Bits 31:26
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA8CH0_CR_TXTRAINRANK0_STRUCT;

typedef union {
  struct {
    UINT32 TxDqDelay                               :  9;  // Bits 8:0
    UINT32 TxDqsDelay                              :  9;  // Bits 17:9
    UINT32 Spare0                                  :  2;  // Bits 19:18
    UINT32 TxEqualization                          :  6;  // Bits 25:20
    UINT32 Spare1                                  :  6;  // Bits 31:26
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA8CH0_CR_TXTRAINRANK1_STRUCT;

typedef union {
  struct {
    UINT32 TxDqDelay                               :  9;  // Bits 8:0
    UINT32 TxDqsDelay                              :  9;  // Bits 17:9
    UINT32 Spare0                                  :  2;  // Bits 19:18
    UINT32 TxEqualization                          :  6;  // Bits 25:20
    UINT32 Spare1                                  :  6;  // Bits 31:26
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA8CH0_CR_TXTRAINRANK2_STRUCT;

typedef union {
  struct {
    UINT32 TxDqDelay                               :  9;  // Bits 8:0
    UINT32 TxDqsDelay                              :  9;  // Bits 17:9
    UINT32 Spare0                                  :  2;  // Bits 19:18
    UINT32 TxEqualization                          :  6;  // Bits 25:20
    UINT32 Spare1                                  :  6;  // Bits 31:26
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA8CH0_CR_TXTRAINRANK3_STRUCT;

typedef union {
  struct {
    UINT32 Lane0                                   :  4;  // Bits 3:0
    UINT32 Lane1                                   :  4;  // Bits 7:4
    UINT32 Lane2                                   :  4;  // Bits 11:8
    UINT32 Lane3                                   :  4;  // Bits 15:12
    UINT32 Lane4                                   :  4;  // Bits 19:16
    UINT32 Lane5                                   :  4;  // Bits 23:20
    UINT32 Lane6                                   :  4;  // Bits 27:24
    UINT32 Lane7                                   :  4;  // Bits 31:28
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA8CH0_CR_TXPERBITRANK0_STRUCT;

typedef union {
  struct {
    UINT32 Lane0                                   :  4;  // Bits 3:0
    UINT32 Lane1                                   :  4;  // Bits 7:4
    UINT32 Lane2                                   :  4;  // Bits 11:8
    UINT32 Lane3                                   :  4;  // Bits 15:12
    UINT32 Lane4                                   :  4;  // Bits 19:16
    UINT32 Lane5                                   :  4;  // Bits 23:20
    UINT32 Lane6                                   :  4;  // Bits 27:24
    UINT32 Lane7                                   :  4;  // Bits 31:28
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA8CH0_CR_TXPERBITRANK1_STRUCT;

typedef union {
  struct {
    UINT32 Lane0                                   :  4;  // Bits 3:0
    UINT32 Lane1                                   :  4;  // Bits 7:4
    UINT32 Lane2                                   :  4;  // Bits 11:8
    UINT32 Lane3                                   :  4;  // Bits 15:12
    UINT32 Lane4                                   :  4;  // Bits 19:16
    UINT32 Lane5                                   :  4;  // Bits 23:20
    UINT32 Lane6                                   :  4;  // Bits 27:24
    UINT32 Lane7                                   :  4;  // Bits 31:28
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA8CH0_CR_TXPERBITRANK2_STRUCT;

typedef union {
  struct {
    UINT32 Lane0                                   :  4;  // Bits 3:0
    UINT32 Lane1                                   :  4;  // Bits 7:4
    UINT32 Lane2                                   :  4;  // Bits 11:8
    UINT32 Lane3                                   :  4;  // Bits 15:12
    UINT32 Lane4                                   :  4;  // Bits 19:16
    UINT32 Lane5                                   :  4;  // Bits 23:20
    UINT32 Lane6                                   :  4;  // Bits 27:24
    UINT32 Lane7                                   :  4;  // Bits 31:28
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA8CH0_CR_TXPERBITRANK3_STRUCT;

typedef union {
  struct {
    UINT32 RcompDrvUp                              :  6;  // Bits 5:0
    UINT32 Rsvd                                    :  3;  // Bits 8:6
    UINT32 RcompDrvDown                            :  6;  // Bits 14:9
    UINT32 VTComp                                  :  5;  // Bits 19:15
    UINT32 SlewRateComp                            :  5;  // Bits 24:20
    UINT32 Spare0                                  :  1;  // Bits 25:25
    UINT32 TcoComp                                 :  6;  // Bits 31:26
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA8CH0_CR_RCOMPDATA0_STRUCT;

typedef union {
  struct {
    UINT32 RcompOdtUp                              :  6;  // Bits 5:0
    UINT32 PanicDrvDn                              :  10;  // Bits 15:6
    UINT32 PanicDrvUp                              :  10;  // Bits 25:16
    UINT32 RcompOdtDown                            :  6;  // Bits 31:26
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA8CH0_CR_RCOMPDATA1_STRUCT;

typedef union {
  struct {
    INT32  Lane0                                   :  4;  // Bits 3:0
    INT32  Lane1                                   :  4;  // Bits 7:4
    INT32  Lane2                                   :  4;  // Bits 11:8
    INT32  Lane3                                   :  4;  // Bits 15:12
    INT32  Lane4                                   :  4;  // Bits 19:16
    INT32  Lane5                                   :  4;  // Bits 23:20
    INT32  Lane6                                   :  4;  // Bits 27:24
    INT32  Lane7                                   :  4;  // Bits 31:28
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA8CH0_CR_TXXTALK_STRUCT;

typedef union {
  struct {
    UINT32 VttPanicUp                              :  8;  // Bits 7:0
    UINT32 VttPanicDn                              :  8;  // Bits 15:8
    UINT32 Spare                                   :  16;  // Bits 31:16
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA8CH0_CR_RCOMPDATA2_STRUCT;

typedef union {
  struct {
    UINT32 Lane0                                   :  4;  // Bits 3:0
    UINT32 Lane1                                   :  4;  // Bits 7:4
    UINT32 Lane2                                   :  4;  // Bits 11:8
    UINT32 Lane3                                   :  4;  // Bits 15:12
    UINT32 Lane4                                   :  4;  // Bits 19:16
    UINT32 Lane5                                   :  4;  // Bits 23:20
    UINT32 Lane6                                   :  4;  // Bits 27:24
    UINT32 Lane7                                   :  4;  // Bits 31:28
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA8CH0_CR_RXOFFSETVDQRANK0_STRUCT;

typedef union {
  struct {
    UINT32 Lane0                                   :  4;  // Bits 3:0
    UINT32 Lane1                                   :  4;  // Bits 7:4
    UINT32 Lane2                                   :  4;  // Bits 11:8
    UINT32 Lane3                                   :  4;  // Bits 15:12
    UINT32 Lane4                                   :  4;  // Bits 19:16
    UINT32 Lane5                                   :  4;  // Bits 23:20
    UINT32 Lane6                                   :  4;  // Bits 27:24
    UINT32 Lane7                                   :  4;  // Bits 31:28
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA8CH0_CR_RXOFFSETVDQRANK1_STRUCT;

typedef union {
  struct {
    UINT32 Lane0                                   :  4;  // Bits 3:0
    UINT32 Lane1                                   :  4;  // Bits 7:4
    UINT32 Lane2                                   :  4;  // Bits 11:8
    UINT32 Lane3                                   :  4;  // Bits 15:12
    UINT32 Lane4                                   :  4;  // Bits 19:16
    UINT32 Lane5                                   :  4;  // Bits 23:20
    UINT32 Lane6                                   :  4;  // Bits 27:24
    UINT32 Lane7                                   :  4;  // Bits 31:28
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA8CH0_CR_RXOFFSETVDQRANK2_STRUCT;

typedef union {
  struct {
    UINT32 Lane0                                   :  4;  // Bits 3:0
    UINT32 Lane1                                   :  4;  // Bits 7:4
    UINT32 Lane2                                   :  4;  // Bits 11:8
    UINT32 Lane3                                   :  4;  // Bits 15:12
    UINT32 Lane4                                   :  4;  // Bits 19:16
    UINT32 Lane5                                   :  4;  // Bits 23:20
    UINT32 Lane6                                   :  4;  // Bits 27:24
    UINT32 Lane7                                   :  4;  // Bits 31:28
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA8CH0_CR_RXOFFSETVDQRANK3_STRUCT;

typedef union {
  struct {
    UINT32 DataTrainFeedback                       :  9;  // Bits 8:0
    UINT32 Spare                                   :  23;  // Bits 31:9
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA8CH0_CR_DATATRAINFEEDBACK_STRUCT;

typedef union {
  struct {
    UINT32 RunTest                                 :  1;  // Bits 0:0
    UINT32 Load                                    :  1;  // Bits 1:1
    UINT32 ModeHVM                                 :  1;  // Bits 2:2
    UINT32 ModeDV                                  :  1;  // Bits 3:3
    UINT32 CalCfdl                                 :  1;  // Bits 4:4
    UINT32 LoadCount                               :  10;  // Bits 14:5
    UINT32 CountStatus                             :  10;  // Bits 24:15
    UINT32 ModeADC                                 :  1;  // Bits 25:25
    UINT32 ADCClkDiv                               :  2;  // Bits 27:26
    UINT32 ADCDdrChanSel                           :  1;  // Bits 28:28
    UINT32 ADCChopEn                               :  1;  // Bits 29:29
    UINT32 ADCDone                                 :  1;  // Bits 30:30
    UINT32 PhaseDrvPwrSavOn                        :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA8CH0_CR_DLLPITESTANDADC_STRUCT;

typedef union {
  struct {
    INT32  DqDrvUpCompOffset                       :  6;  // Bits 5:0
    INT32  DqDrvDownCompOffset                     :  6;  // Bits 11:6
    INT32  DqOdtUpCompOffset                       :  5;  // Bits 16:12
    INT32  DqOdtDownCompOffset                     :  5;  // Bits 21:17
    INT32  DqTcoCompOffset                         :  5;  // Bits 26:22
    INT32  DqSlewRateCompOffset                    :  5;  // Bits 31:27
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA8CH0_CR_DDRCRDATAOFFSETCOMP_STRUCT;

typedef union {
  struct {
    INT32  RefPi                                   :  4;  // Bits 3:0
    UINT32 DllMask                                 :  2;  // Bits 5:4
    UINT32 DllWeakLock                             :  1;  // Bits 6:6
    UINT32 SdllSegmentDisable                      :  3;  // Bits 9:7
    UINT32 RxBiasCtl                               :  4;  // Bits 13:10
    INT32  OdtDelay                                :  4;  // Bits 17:14
    UINT32 OdtDuration                             :  3;  // Bits 20:18
    INT32  SenseAmpDelay                           :  4;  // Bits 24:21
    UINT32 SenseAmpDuration                        :  3;  // Bits 27:25
    UINT32 StrongWkLeaker                          :  3;  // Bits 30:28
    UINT32 LpDdrLongOdtEn                          :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA8CH0_CR_DDRCRDATACONTROL1_STRUCT;

typedef union {
  struct {
    UINT32 RxStaggerCtl                            :  5;  // Bits 4:0
    UINT32 ForceBiasOn                             :  1;  // Bits 5:5
    UINT32 ForceRxOn                               :  1;  // Bits 6:6
    UINT32 LeakerComp                              :  2;  // Bits 8:7
    UINT32 RxDqsAmpOffset                          :  4;  // Bits 12:9
    UINT32 RxClkStgNum                             :  5;  // Bits 17:13
    UINT32 WlLongDelEn                             :  1;  // Bits 18:18
    UINT32 EnableVrefPwrDn                         :  1;  // Bits 19:19
    UINT32 Ddr4Mode                                :  1;  // Bits 20:20
    UINT32 EnVddqOdt                               :  1;  // Bits 21:21
    UINT32 EnVttOdt                                :  1;  // Bits 22:22
    UINT32 EnConstZEqTx                            :  1;  // Bits 23:23
    UINT32 TxEqDis                                 :  1;  // Bits 24:24
    UINT32 RxVrefProgMFC                           :  1;  // Bits 25:25
    UINT32 Cben                                    :  3;  // Bits 28:26
    UINT32 TxDeskewDisable                         :  1;  // Bits 29:29
    UINT32 RxDeskewDisable                         :  1;  // Bits 30:30
    UINT32 DqSlewDlyByPass                         :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA8CH0_CR_DDRCRDATACONTROL2_STRUCT;

typedef union {
  struct {
    UINT32 VrefCtl                                 :  24;  // Bits 23:0
    UINT32 OutputCode                              :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA8CH0_CR_DDRCRVREFCONTROL_STRUCT;

typedef union {
  struct {
    UINT32 VssHiCtl                                :  25;  // Bits 24:0
    UINT32 OutputCode                              :  7;  // Bits 31:25
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA8CH0_CR_DDRCRVSSHICONTROL_STRUCT;

typedef union {
  struct {
    INT32  RcvEnOffset                             :  6;  // Bits 5:0
    INT32  RxDqsOffset                             :  6;  // Bits 11:6
    INT32  TxDqOffset                              :  6;  // Bits 17:12
    INT32  TxDqsOffset                             :  6;  // Bits 23:18
    INT32  VrefOffset                              :  7;  // Bits 30:24
    UINT32 Spare                                   :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA8CH0_CR_DDRCRDATAOFFSETTRAIN_STRUCT;

typedef union {
  struct {
    UINT32 RxTrainingMode                          :  1;  // Bits 0:0
    UINT32 WLTrainingMode                          :  1;  // Bits 1:1
    UINT32 RLTrainingMode                          :  1;  // Bits 2:2
    UINT32 SenseampTrainingMode                    :  1;  // Bits 3:3
    UINT32 TxOn                                    :  1;  // Bits 4:4
    UINT32 RfOn                                    :  1;  // Bits 5:5
    UINT32 RxPiOn                                  :  1;  // Bits 6:6
    UINT32 TxPiOn                                  :  1;  // Bits 7:7
    UINT32 InternalClocksOn                        :  1;  // Bits 8:8
    UINT32 RepeaterClocksOn                        :  1;  // Bits 9:9
    UINT32 TxDisable                               :  1;  // Bits 10:10
    UINT32 RxDisable                               :  1;  // Bits 11:11
    UINT32 TxLong                                  :  1;  // Bits 12:12
    UINT32 RxDqsCtle                               :  2;  // Bits 14:13
    UINT32 RxReadPointer                           :  3;  // Bits 17:15
    UINT32 LongOdtR2W                              :  1;  // Bits 18:18
    UINT32 DataVccddqHi                            :  1;  // Bits 19:19
    UINT32 ReadRFRd                                :  1;  // Bits 20:20
    UINT32 ReadRFWr                                :  1;  // Bits 21:21
    UINT32 ReadRFRank                              :  2;  // Bits 23:22
    UINT32 ForceOdtOn                              :  1;  // Bits 24:24
    UINT32 OdtSampOff                              :  1;  // Bits 25:25
    UINT32 DisableOdtStatic                        :  1;  // Bits 26:26
    UINT32 DdrCRForceODTOn                         :  1;  // Bits 27:27
    UINT32 LPDDR_Mode                              :  1;  // Bits 28:28
    UINT32 EnReadPreamble                          :  1;  // Bits 29:29
    UINT32 OdtSampExtendEn                         :  1;  // Bits 30:30
    UINT32 EarlyRleakEn                            :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA8CH0_CR_DDRCRDATACONTROL0_STRUCT;

typedef union {
  struct {
    INT32  CAVrefCtl                               :  7;  // Bits 6:0
    INT32  Ch1VrefCtl                              :  7;  // Bits 13:7
    INT32  Ch0VrefCtl                              :  7;  // Bits 20:14
    UINT32 EnDimmVrefCA                            :  1;  // Bits 21:21
    UINT32 EnDimmVrefCh1                           :  1;  // Bits 22:22
    UINT32 EnDimmVrefCh0                           :  1;  // Bits 23:23
    UINT32 HiZTimerCtrl                            :  2;  // Bits 25:24
    UINT32 VccddqHiQnnnH                           :  1;  // Bits 26:26
    UINT32 Rsvd                                    :  2;  // Bits 28:27
    UINT32 caSlowBW                                :  1;  // Bits 29:29
    UINT32 ch0SlowBW                               :  1;  // Bits 30:30
    UINT32 ch1SlowBW                               :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA8CH0_CR_DDRCRVREFADJUST1_STRUCT;

typedef union {
  struct {
    UINT32 AttackerDataBit0                        :  3;  // Bits 2:0
    UINT32 AttackerDataBit1                        :  3;  // Bits 5:3
    UINT32 AttackerDataBit2                        :  3;  // Bits 8:6
    UINT32 AttackerDataBit3                        :  3;  // Bits 11:9
    UINT32 AttackerDataBit4                        :  3;  // Bits 14:12
    UINT32 AttackerDataBit5                        :  3;  // Bits 17:15
    UINT32 AttackerDataBit6                        :  3;  // Bits 20:18
    UINT32 AttackerDataBit7                        :  3;  // Bits 23:21
    UINT32 CBEnAmp2                                :  3;  // Bits 26:24
    UINT32 CBpEnAmp2_b                             :  3;  // Bits 29:27
    UINT32 CBEnAmp1                                :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA8CH0_CR_DDRCRDATACONTROL3_STRUCT;

typedef union {
  struct {
    UINT32 Target                                  :  4;  // Bits 3:0
    UINT32 Panic                                   :  5;  // Bits 8:4
    UINT32 DisPanicDrv                             :  2;  // Bits 10:9
    UINT32 DisSensorPwrDn                          :  1;  // Bits 11:11
    UINT32 OfstOvrdEn                              :  1;  // Bits 12:12
    UINT32 ViewOfstsel                             :  3;  // Bits 15:13
    UINT32 EnVttCompforVsshi                       :  1;  // Bits 16:16
    UINT32 Spares                                  :  8;  // Bits 24:17
    UINT32 Disable2Vt                              :  1;  // Bits 25:25
    UINT32 OfstOvrdOrView                          :  6;  // Bits 31:26
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA8CH0_CR_DDRCRVTTGENCONTROL_STRUCT;

typedef union {
  struct {
    UINT32 RxRcvEnPi                               :  9;  // Bits 8:0
    UINT32 RxDqsPPi                                :  6;  // Bits 14:9
    UINT32 RxEq                                    :  5;  // Bits 19:15
    UINT32 RxDqsNPi                                :  6;  // Bits 25:20
    INT32  RxVref                                  :  6;  // Bits 31:26
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA8CH1_CR_RXTRAINRANK0_STRUCT;

typedef union {
  struct {
    UINT32 RxRcvEnPi                               :  9;  // Bits 8:0
    UINT32 RxDqsPPi                                :  6;  // Bits 14:9
    UINT32 RxEq                                    :  5;  // Bits 19:15
    UINT32 RxDqsNPi                                :  6;  // Bits 25:20
    INT32  RxVref                                  :  6;  // Bits 31:26
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA8CH1_CR_RXTRAINRANK1_STRUCT;

typedef union {
  struct {
    UINT32 RxRcvEnPi                               :  9;  // Bits 8:0
    UINT32 RxDqsPPi                                :  6;  // Bits 14:9
    UINT32 RxEq                                    :  5;  // Bits 19:15
    UINT32 RxDqsNPi                                :  6;  // Bits 25:20
    INT32  RxVref                                  :  6;  // Bits 31:26
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA8CH1_CR_RXTRAINRANK2_STRUCT;

typedef union {
  struct {
    UINT32 RxRcvEnPi                               :  9;  // Bits 8:0
    UINT32 RxDqsPPi                                :  6;  // Bits 14:9
    UINT32 RxEq                                    :  5;  // Bits 19:15
    UINT32 RxDqsNPi                                :  6;  // Bits 25:20
    INT32  RxVref                                  :  6;  // Bits 31:26
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA8CH1_CR_RXTRAINRANK3_STRUCT;

typedef union {
  struct {
    UINT32 Lane0                                   :  4;  // Bits 3:0
    UINT32 Lane1                                   :  4;  // Bits 7:4
    UINT32 Lane2                                   :  4;  // Bits 11:8
    UINT32 Lane3                                   :  4;  // Bits 15:12
    UINT32 Lane4                                   :  4;  // Bits 19:16
    UINT32 Lane5                                   :  4;  // Bits 23:20
    UINT32 Lane6                                   :  4;  // Bits 27:24
    UINT32 Lane7                                   :  4;  // Bits 31:28
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA8CH1_CR_RXPERBITRANK0_STRUCT;

typedef union {
  struct {
    UINT32 Lane0                                   :  4;  // Bits 3:0
    UINT32 Lane1                                   :  4;  // Bits 7:4
    UINT32 Lane2                                   :  4;  // Bits 11:8
    UINT32 Lane3                                   :  4;  // Bits 15:12
    UINT32 Lane4                                   :  4;  // Bits 19:16
    UINT32 Lane5                                   :  4;  // Bits 23:20
    UINT32 Lane6                                   :  4;  // Bits 27:24
    UINT32 Lane7                                   :  4;  // Bits 31:28
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA8CH1_CR_RXPERBITRANK1_STRUCT;

typedef union {
  struct {
    UINT32 Lane0                                   :  4;  // Bits 3:0
    UINT32 Lane1                                   :  4;  // Bits 7:4
    UINT32 Lane2                                   :  4;  // Bits 11:8
    UINT32 Lane3                                   :  4;  // Bits 15:12
    UINT32 Lane4                                   :  4;  // Bits 19:16
    UINT32 Lane5                                   :  4;  // Bits 23:20
    UINT32 Lane6                                   :  4;  // Bits 27:24
    UINT32 Lane7                                   :  4;  // Bits 31:28
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA8CH1_CR_RXPERBITRANK2_STRUCT;

typedef union {
  struct {
    UINT32 Lane0                                   :  4;  // Bits 3:0
    UINT32 Lane1                                   :  4;  // Bits 7:4
    UINT32 Lane2                                   :  4;  // Bits 11:8
    UINT32 Lane3                                   :  4;  // Bits 15:12
    UINT32 Lane4                                   :  4;  // Bits 19:16
    UINT32 Lane5                                   :  4;  // Bits 23:20
    UINT32 Lane6                                   :  4;  // Bits 27:24
    UINT32 Lane7                                   :  4;  // Bits 31:28
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA8CH1_CR_RXPERBITRANK3_STRUCT;

typedef union {
  struct {
    UINT32 TxDqDelay                               :  9;  // Bits 8:0
    UINT32 TxDqsDelay                              :  9;  // Bits 17:9
    UINT32 Spare0                                  :  2;  // Bits 19:18
    UINT32 TxEqualization                          :  6;  // Bits 25:20
    UINT32 Spare1                                  :  6;  // Bits 31:26
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA8CH1_CR_TXTRAINRANK0_STRUCT;

typedef union {
  struct {
    UINT32 TxDqDelay                               :  9;  // Bits 8:0
    UINT32 TxDqsDelay                              :  9;  // Bits 17:9
    UINT32 Spare0                                  :  2;  // Bits 19:18
    UINT32 TxEqualization                          :  6;  // Bits 25:20
    UINT32 Spare1                                  :  6;  // Bits 31:26
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA8CH1_CR_TXTRAINRANK1_STRUCT;

typedef union {
  struct {
    UINT32 TxDqDelay                               :  9;  // Bits 8:0
    UINT32 TxDqsDelay                              :  9;  // Bits 17:9
    UINT32 Spare0                                  :  2;  // Bits 19:18
    UINT32 TxEqualization                          :  6;  // Bits 25:20
    UINT32 Spare1                                  :  6;  // Bits 31:26
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA8CH1_CR_TXTRAINRANK2_STRUCT;

typedef union {
  struct {
    UINT32 TxDqDelay                               :  9;  // Bits 8:0
    UINT32 TxDqsDelay                              :  9;  // Bits 17:9
    UINT32 Spare0                                  :  2;  // Bits 19:18
    UINT32 TxEqualization                          :  6;  // Bits 25:20
    UINT32 Spare1                                  :  6;  // Bits 31:26
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA8CH1_CR_TXTRAINRANK3_STRUCT;

typedef union {
  struct {
    UINT32 Lane0                                   :  4;  // Bits 3:0
    UINT32 Lane1                                   :  4;  // Bits 7:4
    UINT32 Lane2                                   :  4;  // Bits 11:8
    UINT32 Lane3                                   :  4;  // Bits 15:12
    UINT32 Lane4                                   :  4;  // Bits 19:16
    UINT32 Lane5                                   :  4;  // Bits 23:20
    UINT32 Lane6                                   :  4;  // Bits 27:24
    UINT32 Lane7                                   :  4;  // Bits 31:28
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA8CH1_CR_TXPERBITRANK0_STRUCT;

typedef union {
  struct {
    UINT32 Lane0                                   :  4;  // Bits 3:0
    UINT32 Lane1                                   :  4;  // Bits 7:4
    UINT32 Lane2                                   :  4;  // Bits 11:8
    UINT32 Lane3                                   :  4;  // Bits 15:12
    UINT32 Lane4                                   :  4;  // Bits 19:16
    UINT32 Lane5                                   :  4;  // Bits 23:20
    UINT32 Lane6                                   :  4;  // Bits 27:24
    UINT32 Lane7                                   :  4;  // Bits 31:28
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA8CH1_CR_TXPERBITRANK1_STRUCT;

typedef union {
  struct {
    UINT32 Lane0                                   :  4;  // Bits 3:0
    UINT32 Lane1                                   :  4;  // Bits 7:4
    UINT32 Lane2                                   :  4;  // Bits 11:8
    UINT32 Lane3                                   :  4;  // Bits 15:12
    UINT32 Lane4                                   :  4;  // Bits 19:16
    UINT32 Lane5                                   :  4;  // Bits 23:20
    UINT32 Lane6                                   :  4;  // Bits 27:24
    UINT32 Lane7                                   :  4;  // Bits 31:28
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA8CH1_CR_TXPERBITRANK2_STRUCT;

typedef union {
  struct {
    UINT32 Lane0                                   :  4;  // Bits 3:0
    UINT32 Lane1                                   :  4;  // Bits 7:4
    UINT32 Lane2                                   :  4;  // Bits 11:8
    UINT32 Lane3                                   :  4;  // Bits 15:12
    UINT32 Lane4                                   :  4;  // Bits 19:16
    UINT32 Lane5                                   :  4;  // Bits 23:20
    UINT32 Lane6                                   :  4;  // Bits 27:24
    UINT32 Lane7                                   :  4;  // Bits 31:28
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA8CH1_CR_TXPERBITRANK3_STRUCT;

typedef union {
  struct {
    UINT32 RcompDrvUp                              :  6;  // Bits 5:0
    UINT32 Rsvd                                    :  3;  // Bits 8:6
    UINT32 RcompDrvDown                            :  6;  // Bits 14:9
    UINT32 VTComp                                  :  5;  // Bits 19:15
    UINT32 SlewRateComp                            :  5;  // Bits 24:20
    UINT32 Spare0                                  :  1;  // Bits 25:25
    UINT32 TcoComp                                 :  6;  // Bits 31:26
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA8CH1_CR_RCOMPDATA0_STRUCT;

typedef union {
  struct {
    UINT32 RcompOdtUp                              :  6;  // Bits 5:0
    UINT32 PanicDrvDn                              :  10;  // Bits 15:6
    UINT32 PanicDrvUp                              :  10;  // Bits 25:16
    UINT32 RcompOdtDown                            :  6;  // Bits 31:26
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA8CH1_CR_RCOMPDATA1_STRUCT;

typedef union {
  struct {
    INT32  Lane0                                   :  4;  // Bits 3:0
    INT32  Lane1                                   :  4;  // Bits 7:4
    INT32  Lane2                                   :  4;  // Bits 11:8
    INT32  Lane3                                   :  4;  // Bits 15:12
    INT32  Lane4                                   :  4;  // Bits 19:16
    INT32  Lane5                                   :  4;  // Bits 23:20
    INT32  Lane6                                   :  4;  // Bits 27:24
    INT32  Lane7                                   :  4;  // Bits 31:28
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA8CH1_CR_TXXTALK_STRUCT;

typedef union {
  struct {
    UINT32 VttPanicUp                              :  8;  // Bits 7:0
    UINT32 VttPanicDn                              :  8;  // Bits 15:8
    UINT32 Spare                                   :  16;  // Bits 31:16
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA8CH1_CR_RCOMPDATA2_STRUCT;

typedef union {
  struct {
    UINT32 Lane0                                   :  4;  // Bits 3:0
    UINT32 Lane1                                   :  4;  // Bits 7:4
    UINT32 Lane2                                   :  4;  // Bits 11:8
    UINT32 Lane3                                   :  4;  // Bits 15:12
    UINT32 Lane4                                   :  4;  // Bits 19:16
    UINT32 Lane5                                   :  4;  // Bits 23:20
    UINT32 Lane6                                   :  4;  // Bits 27:24
    UINT32 Lane7                                   :  4;  // Bits 31:28
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA8CH1_CR_RXOFFSETVDQRANK0_STRUCT;

typedef union {
  struct {
    UINT32 Lane0                                   :  4;  // Bits 3:0
    UINT32 Lane1                                   :  4;  // Bits 7:4
    UINT32 Lane2                                   :  4;  // Bits 11:8
    UINT32 Lane3                                   :  4;  // Bits 15:12
    UINT32 Lane4                                   :  4;  // Bits 19:16
    UINT32 Lane5                                   :  4;  // Bits 23:20
    UINT32 Lane6                                   :  4;  // Bits 27:24
    UINT32 Lane7                                   :  4;  // Bits 31:28
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA8CH1_CR_RXOFFSETVDQRANK1_STRUCT;

typedef union {
  struct {
    UINT32 Lane0                                   :  4;  // Bits 3:0
    UINT32 Lane1                                   :  4;  // Bits 7:4
    UINT32 Lane2                                   :  4;  // Bits 11:8
    UINT32 Lane3                                   :  4;  // Bits 15:12
    UINT32 Lane4                                   :  4;  // Bits 19:16
    UINT32 Lane5                                   :  4;  // Bits 23:20
    UINT32 Lane6                                   :  4;  // Bits 27:24
    UINT32 Lane7                                   :  4;  // Bits 31:28
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA8CH1_CR_RXOFFSETVDQRANK2_STRUCT;

typedef union {
  struct {
    UINT32 Lane0                                   :  4;  // Bits 3:0
    UINT32 Lane1                                   :  4;  // Bits 7:4
    UINT32 Lane2                                   :  4;  // Bits 11:8
    UINT32 Lane3                                   :  4;  // Bits 15:12
    UINT32 Lane4                                   :  4;  // Bits 19:16
    UINT32 Lane5                                   :  4;  // Bits 23:20
    UINT32 Lane6                                   :  4;  // Bits 27:24
    UINT32 Lane7                                   :  4;  // Bits 31:28
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA8CH1_CR_RXOFFSETVDQRANK3_STRUCT;

typedef union {
  struct {
    UINT32 DataTrainFeedback                       :  9;  // Bits 8:0
    UINT32 Spare                                   :  23;  // Bits 31:9
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA8CH1_CR_DATATRAINFEEDBACK_STRUCT;

typedef union {
  struct {
    UINT32 RunTest                                 :  1;  // Bits 0:0
    UINT32 Load                                    :  1;  // Bits 1:1
    UINT32 ModeHVM                                 :  1;  // Bits 2:2
    UINT32 ModeDV                                  :  1;  // Bits 3:3
    UINT32 CalCfdl                                 :  1;  // Bits 4:4
    UINT32 LoadCount                               :  10;  // Bits 14:5
    UINT32 CountStatus                             :  10;  // Bits 24:15
    UINT32 ModeADC                                 :  1;  // Bits 25:25
    UINT32 ADCClkDiv                               :  2;  // Bits 27:26
    UINT32 ADCDdrChanSel                           :  1;  // Bits 28:28
    UINT32 ADCChopEn                               :  1;  // Bits 29:29
    UINT32 ADCDone                                 :  1;  // Bits 30:30
    UINT32 PhaseDrvPwrSavOn                        :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA8CH1_CR_DLLPITESTANDADC_STRUCT;

typedef union {
  struct {
    INT32  DqDrvUpCompOffset                       :  6;  // Bits 5:0
    INT32  DqDrvDownCompOffset                     :  6;  // Bits 11:6
    INT32  DqOdtUpCompOffset                       :  5;  // Bits 16:12
    INT32  DqOdtDownCompOffset                     :  5;  // Bits 21:17
    INT32  DqTcoCompOffset                         :  5;  // Bits 26:22
    INT32  DqSlewRateCompOffset                    :  5;  // Bits 31:27
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA8CH1_CR_DDRCRDATAOFFSETCOMP_STRUCT;

typedef union {
  struct {
    INT32  RefPi                                   :  4;  // Bits 3:0
    UINT32 DllMask                                 :  2;  // Bits 5:4
    UINT32 DllWeakLock                             :  1;  // Bits 6:6
    UINT32 SdllSegmentDisable                      :  3;  // Bits 9:7
    UINT32 RxBiasCtl                               :  4;  // Bits 13:10
    INT32  OdtDelay                                :  4;  // Bits 17:14
    UINT32 OdtDuration                             :  3;  // Bits 20:18
    INT32  SenseAmpDelay                           :  4;  // Bits 24:21
    UINT32 SenseAmpDuration                        :  3;  // Bits 27:25
    UINT32 StrongWkLeaker                          :  3;  // Bits 30:28
    UINT32 LpDdrLongOdtEn                          :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA8CH1_CR_DDRCRDATACONTROL1_STRUCT;

typedef union {
  struct {
    UINT32 RxStaggerCtl                            :  5;  // Bits 4:0
    UINT32 ForceBiasOn                             :  1;  // Bits 5:5
    UINT32 ForceRxOn                               :  1;  // Bits 6:6
    UINT32 LeakerComp                              :  2;  // Bits 8:7
    UINT32 RxDqsAmpOffset                          :  4;  // Bits 12:9
    UINT32 RxClkStgNum                             :  5;  // Bits 17:13
    UINT32 WlLongDelEn                             :  1;  // Bits 18:18
    UINT32 EnableVrefPwrDn                         :  1;  // Bits 19:19
    UINT32 Ddr4Mode                                :  1;  // Bits 20:20
    UINT32 EnVddqOdt                               :  1;  // Bits 21:21
    UINT32 EnVttOdt                                :  1;  // Bits 22:22
    UINT32 EnConstZEqTx                            :  1;  // Bits 23:23
    UINT32 TxEqDis                                 :  1;  // Bits 24:24
    UINT32 RxVrefProgMFC                           :  1;  // Bits 25:25
    UINT32 Cben                                    :  3;  // Bits 28:26
    UINT32 TxDeskewDisable                         :  1;  // Bits 29:29
    UINT32 RxDeskewDisable                         :  1;  // Bits 30:30
    UINT32 DqSlewDlyByPass                         :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA8CH1_CR_DDRCRDATACONTROL2_STRUCT;

typedef union {
  struct {
    UINT32 VrefCtl                                 :  24;  // Bits 23:0
    UINT32 OutputCode                              :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA8CH1_CR_DDRCRVREFCONTROL_STRUCT;

typedef union {
  struct {
    UINT32 VssHiCtl                                :  25;  // Bits 24:0
    UINT32 OutputCode                              :  7;  // Bits 31:25
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA8CH1_CR_DDRCRVSSHICONTROL_STRUCT;

typedef union {
  struct {
    INT32  RcvEnOffset                             :  6;  // Bits 5:0
    INT32  RxDqsOffset                             :  6;  // Bits 11:6
    INT32  TxDqOffset                              :  6;  // Bits 17:12
    INT32  TxDqsOffset                             :  6;  // Bits 23:18
    INT32  VrefOffset                              :  7;  // Bits 30:24
    UINT32 Spare                                   :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA8CH1_CR_DDRCRDATAOFFSETTRAIN_STRUCT;

typedef union {
  struct {
    UINT32 RxTrainingMode                          :  1;  // Bits 0:0
    UINT32 WLTrainingMode                          :  1;  // Bits 1:1
    UINT32 RLTrainingMode                          :  1;  // Bits 2:2
    UINT32 SenseampTrainingMode                    :  1;  // Bits 3:3
    UINT32 TxOn                                    :  1;  // Bits 4:4
    UINT32 RfOn                                    :  1;  // Bits 5:5
    UINT32 RxPiOn                                  :  1;  // Bits 6:6
    UINT32 TxPiOn                                  :  1;  // Bits 7:7
    UINT32 InternalClocksOn                        :  1;  // Bits 8:8
    UINT32 RepeaterClocksOn                        :  1;  // Bits 9:9
    UINT32 TxDisable                               :  1;  // Bits 10:10
    UINT32 RxDisable                               :  1;  // Bits 11:11
    UINT32 TxLong                                  :  1;  // Bits 12:12
    UINT32 RxDqsCtle                               :  2;  // Bits 14:13
    UINT32 RxReadPointer                           :  3;  // Bits 17:15
    UINT32 LongOdtR2W                              :  1;  // Bits 18:18
    UINT32 DataVccddqHi                            :  1;  // Bits 19:19
    UINT32 ReadRFRd                                :  1;  // Bits 20:20
    UINT32 ReadRFWr                                :  1;  // Bits 21:21
    UINT32 ReadRFRank                              :  2;  // Bits 23:22
    UINT32 ForceOdtOn                              :  1;  // Bits 24:24
    UINT32 OdtSampOff                              :  1;  // Bits 25:25
    UINT32 DisableOdtStatic                        :  1;  // Bits 26:26
    UINT32 DdrCRForceODTOn                         :  1;  // Bits 27:27
    UINT32 LPDDR_Mode                              :  1;  // Bits 28:28
    UINT32 EnReadPreamble                          :  1;  // Bits 29:29
    UINT32 OdtSampExtendEn                         :  1;  // Bits 30:30
    UINT32 EarlyRleakEn                            :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA8CH1_CR_DDRCRDATACONTROL0_STRUCT;

typedef union {
  struct {
    INT32  CAVrefCtl                               :  7;  // Bits 6:0
    INT32  Ch1VrefCtl                              :  7;  // Bits 13:7
    INT32  Ch0VrefCtl                              :  7;  // Bits 20:14
    UINT32 EnDimmVrefCA                            :  1;  // Bits 21:21
    UINT32 EnDimmVrefCh1                           :  1;  // Bits 22:22
    UINT32 EnDimmVrefCh0                           :  1;  // Bits 23:23
    UINT32 HiZTimerCtrl                            :  2;  // Bits 25:24
    UINT32 VccddqHiQnnnH                           :  1;  // Bits 26:26
    UINT32 Rsvd                                    :  2;  // Bits 28:27
    UINT32 caSlowBW                                :  1;  // Bits 29:29
    UINT32 ch0SlowBW                               :  1;  // Bits 30:30
    UINT32 ch1SlowBW                               :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA8CH1_CR_DDRCRVREFADJUST1_STRUCT;

typedef union {
  struct {
    UINT32 AttackerDataBit0                        :  3;  // Bits 2:0
    UINT32 AttackerDataBit1                        :  3;  // Bits 5:3
    UINT32 AttackerDataBit2                        :  3;  // Bits 8:6
    UINT32 AttackerDataBit3                        :  3;  // Bits 11:9
    UINT32 AttackerDataBit4                        :  3;  // Bits 14:12
    UINT32 AttackerDataBit5                        :  3;  // Bits 17:15
    UINT32 AttackerDataBit6                        :  3;  // Bits 20:18
    UINT32 AttackerDataBit7                        :  3;  // Bits 23:21
    UINT32 CBEnAmp2                                :  3;  // Bits 26:24
    UINT32 CBpEnAmp2_b                             :  3;  // Bits 29:27
    UINT32 CBEnAmp1                                :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA8CH1_CR_DDRCRDATACONTROL3_STRUCT;

typedef union {
  struct {
    UINT32 Target                                  :  4;  // Bits 3:0
    UINT32 Panic                                   :  5;  // Bits 8:4
    UINT32 DisPanicDrv                             :  2;  // Bits 10:9
    UINT32 DisSensorPwrDn                          :  1;  // Bits 11:11
    UINT32 OfstOvrdEn                              :  1;  // Bits 12:12
    UINT32 ViewOfstsel                             :  3;  // Bits 15:13
    UINT32 EnVttCompforVsshi                       :  1;  // Bits 16:16
    UINT32 Spares                                  :  8;  // Bits 24:17
    UINT32 Disable2Vt                              :  1;  // Bits 25:25
    UINT32 OfstOvrdOrView                          :  6;  // Bits 31:26
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA8CH1_CR_DDRCRVTTGENCONTROL_STRUCT;

typedef union {
  struct {
    UINT32 Scomp                                   :  6;  // Bits 5:0
    UINT32 TcoComp                                 :  6;  // Bits 11:6
    UINT32 RcompDrvUp                              :  6;  // Bits 17:12
    UINT32 RcompDrvDown                            :  6;  // Bits 23:18
    UINT32 Spare                                   :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRCKECH0_CR_DDRCRCMDCOMP_STRUCT;

typedef union {
  struct {
    INT32  ScompOffset                             :  5;  // Bits 4:0
    INT32  TcoCompOffset                           :  4;  // Bits 8:5
    INT32  RcompDrvUpOffset                        :  4;  // Bits 12:9
    INT32  RcompDrvDownOffset                      :  4;  // Bits 16:13
    UINT32 Spare                                   :  15;  // Bits 31:17
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRCKECH0_CR_DDRCRCMDCOMPOFFSET_STRUCT;

typedef union {
  struct {
    UINT32 CmdPi0Code                              :  7;  // Bits 6:0
    UINT32 CmdPi1Code                              :  7;  // Bits 13:7
    UINT32 Spare                                   :  18;  // Bits 31:14
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRCKECH0_CR_DDRCRCMDPICODING_STRUCT;

typedef union {
  struct {
    UINT32 Scomp                                   :  6;  // Bits 5:0
    UINT32 TcoComp                                 :  6;  // Bits 11:6
    UINT32 RcompDrvUp                              :  6;  // Bits 17:12
    UINT32 RcompDrvDown                            :  6;  // Bits 23:18
    UINT32 Spare                                   :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRCKECH0_CR_DDRCRCTLCOMP_STRUCT;

typedef union {
  struct {
    INT32  ScompOffset                             :  5;  // Bits 4:0
    INT32  TcoCompOffset                           :  4;  // Bits 8:5
    INT32  RcompDrvUpOffset                        :  4;  // Bits 12:9
    INT32  RcompDrvDownOffset                      :  4;  // Bits 16:13
    UINT32 Spare                                   :  15;  // Bits 31:17
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRCKECH0_CR_DDRCRCTLCOMPOFFSET_STRUCT;

typedef union {
  struct {
    UINT32 CtlPiCode0                              :  7;  // Bits 6:0
    UINT32 CtlPiCode1                              :  7;  // Bits 13:7
    UINT32 CtlPiCode2                              :  7;  // Bits 20:14
    UINT32 CtlPiCode3                              :  7;  // Bits 27:21
    UINT32 CtlXoverEnable                          :  1;  // Bits 28:28
    UINT32 Spare                                   :  3;  // Bits 31:29
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRCKECH0_CR_DDRCRCTLPICODING_STRUCT;

typedef union {
  struct {
    INT32  RefPi                                   :  4;  // Bits 3:0
    UINT32 DllMask                                 :  2;  // Bits 5:4
    UINT32 ClkGateDisable                          :  1;  // Bits 6:6
    UINT32 TxOn                                    :  1;  // Bits 7:7
    UINT32 IntClkOn                                :  1;  // Bits 8:8
    UINT32 RepClkOn                                :  1;  // Bits 9:9
    UINT32 IolbOrMisr                              :  1;  // Bits 10:10
    UINT32 IOLBHold                                :  1;  // Bits 11:11
    UINT32 OdtMode                                 :  1;  // Bits 12:12
    UINT32 CmdTxEq                                 :  2;  // Bits 14:13
    UINT32 EarlyWeakDrive                          :  2;  // Bits 16:15
    UINT32 CtlTxEq                                 :  2;  // Bits 18:17
    UINT32 CtlSRDrv                                :  2;  // Bits 20:19
    INT32  RxVref                                  :  6;  // Bits 26:21
    UINT32 VccddqHi                                :  1;  // Bits 27:27
    UINT32 DllWeakLock                             :  1;  // Bits 28:28
    UINT32 LPDDR_Mode                              :  1;  // Bits 29:29
    UINT32 LaDrvEnOvrd                             :  1;  // Bits 30:30
    UINT32 LPDdrCAA_Dis                            :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRCKECH0_CR_DDRCRCTLCONTROLS_STRUCT;

typedef union {
  struct {
    UINT32 RankEn                                  :  4;  // Bits 3:0
    UINT32 OdtDisable                              :  2;  // Bits 5:4
    UINT32 DdrCkeCmdSlwDlyByp                      :  1;  // Bits 6:6
    UINT32 DdrCtlCkeSlwDlyByp                      :  1;  // Bits 7:7
    UINT32 CsPiClkGateEn                           :  1;  // Bits 8:8
    UINT32 CsClkGateDis                            :  1;  // Bits 9:9
    UINT32 Spare                                   :  22;  // Bits 31:10
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRCKECH0_CR_DDRCRCTLRANKSUSED_STRUCT;

typedef union {
  struct {
    UINT32 RunTest                                 :  1;  // Bits 0:0
    UINT32 Load                                    :  1;  // Bits 1:1
    UINT32 ModeHVM                                 :  1;  // Bits 2:2
    UINT32 ModeDV                                  :  1;  // Bits 3:3
    UINT32 CalCfdl                                 :  1;  // Bits 4:4
    UINT32 LoadCount                               :  10;  // Bits 14:5
    UINT32 CountStatus                             :  10;  // Bits 24:15
    UINT32 PhaseDrvPwrSavOn                        :  1;  // Bits 25:25
    UINT32 Spare                                   :  6;  // Bits 31:26
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRCKECH0_CR_DLLPITESTANDADC_STRUCT;

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
} DDRCKECH0_CR_DDRCMDMISR_STRUCT;

typedef union {
  struct {
    UINT32 Scomp                                   :  6;  // Bits 5:0
    UINT32 TcoComp                                 :  6;  // Bits 11:6
    UINT32 RcompDrvUp                              :  6;  // Bits 17:12
    UINT32 RcompDrvDown                            :  6;  // Bits 23:18
    UINT32 Spare                                   :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRCKECH1_CR_DDRCRCMDCOMP_STRUCT;

typedef union {
  struct {
    INT32  ScompOffset                             :  5;  // Bits 4:0
    INT32  TcoCompOffset                           :  4;  // Bits 8:5
    INT32  RcompDrvUpOffset                        :  4;  // Bits 12:9
    INT32  RcompDrvDownOffset                      :  4;  // Bits 16:13
    UINT32 Spare                                   :  15;  // Bits 31:17
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRCKECH1_CR_DDRCRCMDCOMPOFFSET_STRUCT;

typedef union {
  struct {
    UINT32 CmdPi0Code                              :  7;  // Bits 6:0
    UINT32 CmdPi1Code                              :  7;  // Bits 13:7
    UINT32 Spare                                   :  18;  // Bits 31:14
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRCKECH1_CR_DDRCRCMDPICODING_STRUCT;

typedef union {
  struct {
    UINT32 Scomp                                   :  6;  // Bits 5:0
    UINT32 TcoComp                                 :  6;  // Bits 11:6
    UINT32 RcompDrvUp                              :  6;  // Bits 17:12
    UINT32 RcompDrvDown                            :  6;  // Bits 23:18
    UINT32 Spare                                   :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRCKECH1_CR_DDRCRCTLCOMP_STRUCT;

typedef union {
  struct {
    INT32  ScompOffset                             :  5;  // Bits 4:0
    INT32  TcoCompOffset                           :  4;  // Bits 8:5
    INT32  RcompDrvUpOffset                        :  4;  // Bits 12:9
    INT32  RcompDrvDownOffset                      :  4;  // Bits 16:13
    UINT32 Spare                                   :  15;  // Bits 31:17
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRCKECH1_CR_DDRCRCTLCOMPOFFSET_STRUCT;

typedef union {
  struct {
    UINT32 CtlPiCode0                              :  7;  // Bits 6:0
    UINT32 CtlPiCode1                              :  7;  // Bits 13:7
    UINT32 CtlPiCode2                              :  7;  // Bits 20:14
    UINT32 CtlPiCode3                              :  7;  // Bits 27:21
    UINT32 CtlXoverEnable                          :  1;  // Bits 28:28
    UINT32 Spare                                   :  3;  // Bits 31:29
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRCKECH1_CR_DDRCRCTLPICODING_STRUCT;

typedef union {
  struct {
    INT32  RefPi                                   :  4;  // Bits 3:0
    UINT32 DllMask                                 :  2;  // Bits 5:4
    UINT32 ClkGateDisable                          :  1;  // Bits 6:6
    UINT32 TxOn                                    :  1;  // Bits 7:7
    UINT32 IntClkOn                                :  1;  // Bits 8:8
    UINT32 RepClkOn                                :  1;  // Bits 9:9
    UINT32 IolbOrMisr                              :  1;  // Bits 10:10
    UINT32 IOLBHold                                :  1;  // Bits 11:11
    UINT32 OdtMode                                 :  1;  // Bits 12:12
    UINT32 CmdTxEq                                 :  2;  // Bits 14:13
    UINT32 EarlyWeakDrive                          :  2;  // Bits 16:15
    UINT32 CtlTxEq                                 :  2;  // Bits 18:17
    UINT32 CtlSRDrv                                :  2;  // Bits 20:19
    INT32  RxVref                                  :  6;  // Bits 26:21
    UINT32 VccddqHi                                :  1;  // Bits 27:27
    UINT32 DllWeakLock                             :  1;  // Bits 28:28
    UINT32 LPDDR_Mode                              :  1;  // Bits 29:29
    UINT32 LaDrvEnOvrd                             :  1;  // Bits 30:30
    UINT32 LPDdrCAA_Dis                            :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRCKECH1_CR_DDRCRCTLCONTROLS_STRUCT;

typedef union {
  struct {
    UINT32 RankEn                                  :  4;  // Bits 3:0
    UINT32 OdtDisable                              :  2;  // Bits 5:4
    UINT32 DdrCkeCmdSlwDlyByp                      :  1;  // Bits 6:6
    UINT32 DdrCtlCkeSlwDlyByp                      :  1;  // Bits 7:7
    UINT32 CsPiClkGateEn                           :  1;  // Bits 8:8
    UINT32 CsClkGateDis                            :  1;  // Bits 9:9
    UINT32 Spare                                   :  22;  // Bits 31:10
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRCKECH1_CR_DDRCRCTLRANKSUSED_STRUCT;

typedef union {
  struct {
    UINT32 RunTest                                 :  1;  // Bits 0:0
    UINT32 Load                                    :  1;  // Bits 1:1
    UINT32 ModeHVM                                 :  1;  // Bits 2:2
    UINT32 ModeDV                                  :  1;  // Bits 3:3
    UINT32 CalCfdl                                 :  1;  // Bits 4:4
    UINT32 LoadCount                               :  10;  // Bits 14:5
    UINT32 CountStatus                             :  10;  // Bits 24:15
    UINT32 PhaseDrvPwrSavOn                        :  1;  // Bits 25:25
    UINT32 Spare                                   :  6;  // Bits 31:26
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRCKECH1_CR_DLLPITESTANDADC_STRUCT;

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
} DDRCKECH1_CR_DDRCMDMISR_STRUCT;

typedef union {
  struct {
    UINT32 Scomp                                   :  6;  // Bits 5:0
    UINT32 TcoComp                                 :  6;  // Bits 11:6
    UINT32 RcompDrvUp                              :  6;  // Bits 17:12
    UINT32 RcompDrvDown                            :  6;  // Bits 23:18
    UINT32 Spare                                   :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRCMDNCH0_CR_DDRCRCMDCOMP_STRUCT;

typedef union {
  struct {
    INT32  ScompOffset                             :  5;  // Bits 4:0
    INT32  TcoCompOffset                           :  4;  // Bits 8:5
    INT32  RcompDrvUpOffset                        :  4;  // Bits 12:9
    INT32  RcompDrvDownOffset                      :  4;  // Bits 16:13
    UINT32 Spare                                   :  15;  // Bits 31:17
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRCMDNCH0_CR_DDRCRCMDCOMPOFFSET_STRUCT;

typedef union {
  struct {
    UINT32 CmdPi0Code                              :  7;  // Bits 6:0
    UINT32 CmdPi1Code                              :  7;  // Bits 13:7
    UINT32 Spare                                   :  18;  // Bits 31:14
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRCMDNCH0_CR_DDRCRCMDPICODING_STRUCT;

typedef union {
  struct {
    INT32  RefPi                                   :  4;  // Bits 3:0
    UINT32 DllMask                                 :  2;  // Bits 5:4
    UINT32 ClkGateDisable                          :  1;  // Bits 6:6
    UINT32 TxOn                                    :  1;  // Bits 7:7
    UINT32 IntClkOn                                :  1;  // Bits 8:8
    UINT32 RepClkOn                                :  1;  // Bits 9:9
    UINT32 IolbOrMisr                              :  1;  // Bits 10:10
    UINT32 IolbHold                                :  1;  // Bits 11:11
    UINT32 OdtMode                                 :  1;  // Bits 12:12
    UINT32 CmdTxEq                                 :  2;  // Bits 14:13
    UINT32 EarlyWeakDrive                          :  2;  // Bits 16:15
    UINT32 PrtEn                                   :  1;  // Bits 17:17
    UINT32 AlrtEn                                  :  1;  // Bits 18:18
    UINT32 LaDrvEnOvrd                             :  1;  // Bits 19:19
    UINT32 DdrCmdSlwDlyByp                         :  1;  // Bits 20:20
    INT32  RxVref                                  :  6;  // Bits 26:21
    UINT32 VccddqHi                                :  1;  // Bits 27:27
    UINT32 DllWeakLock                             :  1;  // Bits 28:28
    UINT32 LPDDR_Mode                              :  1;  // Bits 29:29
    UINT32 LPDdrCAA_Dis                            :  1;  // Bits 30:30
    UINT32 LPDdrCAB_Dis                            :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRCMDNCH0_CR_DDRCRCMDCONTROLS_STRUCT;

typedef union {
  struct {
    UINT32 RunTest                                 :  1;  // Bits 0:0
    UINT32 Load                                    :  1;  // Bits 1:1
    UINT32 ModeHVM                                 :  1;  // Bits 2:2
    UINT32 ModeDV                                  :  1;  // Bits 3:3
    UINT32 CalCfdl                                 :  1;  // Bits 4:4
    UINT32 LoadCount                               :  10;  // Bits 14:5
    UINT32 CountStatus                             :  10;  // Bits 24:15
    UINT32 PhaseDrvPwrSavOn                        :  1;  // Bits 25:25
    UINT32 Spare                                   :  6;  // Bits 31:26
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRCMDNCH0_CR_DLLPITESTANDADC_STRUCT;

typedef union {
  struct {
    UINT32 Scomp                                   :  6;  // Bits 5:0
    UINT32 TcoComp                                 :  6;  // Bits 11:6
    UINT32 RcompDrvUp                              :  6;  // Bits 17:12
    UINT32 RcompDrvDown                            :  6;  // Bits 23:18
    UINT32 Spare                                   :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRCMDNCH1_CR_DDRCRCMDCOMP_STRUCT;

typedef union {
  struct {
    INT32  ScompOffset                             :  5;  // Bits 4:0
    INT32  TcoCompOffset                           :  4;  // Bits 8:5
    INT32  RcompDrvUpOffset                        :  4;  // Bits 12:9
    INT32  RcompDrvDownOffset                      :  4;  // Bits 16:13
    UINT32 Spare                                   :  15;  // Bits 31:17
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRCMDNCH1_CR_DDRCRCMDCOMPOFFSET_STRUCT;

typedef union {
  struct {
    UINT32 CmdPi0Code                              :  7;  // Bits 6:0
    UINT32 CmdPi1Code                              :  7;  // Bits 13:7
    UINT32 Spare                                   :  18;  // Bits 31:14
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRCMDNCH1_CR_DDRCRCMDPICODING_STRUCT;

typedef union {
  struct {
    INT32  RefPi                                   :  4;  // Bits 3:0
    UINT32 DllMask                                 :  2;  // Bits 5:4
    UINT32 ClkGateDisable                          :  1;  // Bits 6:6
    UINT32 TxOn                                    :  1;  // Bits 7:7
    UINT32 IntClkOn                                :  1;  // Bits 8:8
    UINT32 RepClkOn                                :  1;  // Bits 9:9
    UINT32 IolbOrMisr                              :  1;  // Bits 10:10
    UINT32 IolbHold                                :  1;  // Bits 11:11
    UINT32 OdtMode                                 :  1;  // Bits 12:12
    UINT32 CmdTxEq                                 :  2;  // Bits 14:13
    UINT32 EarlyWeakDrive                          :  2;  // Bits 16:15
    UINT32 PrtEn                                   :  1;  // Bits 17:17
    UINT32 AlrtEn                                  :  1;  // Bits 18:18
    UINT32 LaDrvEnOvrd                             :  1;  // Bits 19:19
    UINT32 DdrCmdSlwDlyByp                         :  1;  // Bits 20:20
    INT32  RxVref                                  :  6;  // Bits 26:21
    UINT32 VccddqHi                                :  1;  // Bits 27:27
    UINT32 DllWeakLock                             :  1;  // Bits 28:28
    UINT32 LPDDR_Mode                              :  1;  // Bits 29:29
    UINT32 LPDdrCAA_Dis                            :  1;  // Bits 30:30
    UINT32 LPDdrCAB_Dis                            :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRCMDNCH1_CR_DDRCRCMDCONTROLS_STRUCT;

typedef union {
  struct {
    UINT32 RunTest                                 :  1;  // Bits 0:0
    UINT32 Load                                    :  1;  // Bits 1:1
    UINT32 ModeHVM                                 :  1;  // Bits 2:2
    UINT32 ModeDV                                  :  1;  // Bits 3:3
    UINT32 CalCfdl                                 :  1;  // Bits 4:4
    UINT32 LoadCount                               :  10;  // Bits 14:5
    UINT32 CountStatus                             :  10;  // Bits 24:15
    UINT32 PhaseDrvPwrSavOn                        :  1;  // Bits 25:25
    UINT32 Spare                                   :  6;  // Bits 31:26
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRCMDNCH1_CR_DLLPITESTANDADC_STRUCT;

typedef union {
  struct {
    UINT32 RankEn                                  :  4;  // Bits 3:0
    UINT32 Spare                                   :  28;  // Bits 31:4
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRCLKCH0_CR_DDRCRCLKRANKSUSED_STRUCT;

typedef union {
  struct {
    UINT32 Scomp                                   :  5;  // Bits 4:0
    UINT32 TcoComp                                 :  6;  // Bits 10:5
    UINT32 RcompDrvUp                              :  6;  // Bits 16:11
    UINT32 RcompDrvDown                            :  6;  // Bits 22:17
    UINT32 Spare                                   :  9;  // Bits 31:23
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRCLKCH0_CR_DDRCRCLKCOMP_STRUCT;

typedef union {
  struct {
    INT32  ScompOffset                             :  4;  // Bits 3:0
    INT32  TcoCompOffset                           :  4;  // Bits 7:4
    INT32  RcompDrvUpOffset                        :  4;  // Bits 11:8
    INT32  RcompDrvDownOffset                      :  4;  // Bits 15:12
    UINT32 Spare                                   :  16;  // Bits 31:16
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRCLKCH0_CR_DDRCRCLKCOMPOFFSET_STRUCT;

typedef union {
  struct {
    UINT32 PiSettingRank0                          :  7;  // Bits 6:0
    UINT32 PiSettingRank1                          :  7;  // Bits 13:7
    UINT32 PiSettingRank2                          :  7;  // Bits 20:14
    UINT32 PiSettingRank3                          :  7;  // Bits 27:21
    UINT32 Spare                                   :  4;  // Bits 31:28
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRCLKCH0_CR_DDRCRCLKPICODE_STRUCT;

typedef union {
  struct {
    INT32  RefPi                                   :  4;  // Bits 3:0
    UINT32 DllMask                                 :  2;  // Bits 5:4
    UINT32 DllRsvd1                                :  1;  // Bits 6:6
    UINT32 TxOn                                    :  1;  // Bits 7:7
    UINT32 IntClkOn                                :  1;  // Bits 8:8
    UINT32 RepClkOn                                :  1;  // Bits 9:9
    UINT32 IOLBCtl                                 :  2;  // Bits 11:10
    UINT32 OdtMode                                 :  1;  // Bits 12:12
    UINT32 Reserved                                :  8;  // Bits 20:13
    INT32  RxVref                                  :  6;  // Bits 26:21
    UINT32 VccddqHi                                :  1;  // Bits 27:27
    UINT32 DllWeakLock                             :  1;  // Bits 28:28
    UINT32 LPDDR_Mode                              :  1;  // Bits 29:29
    UINT32 LPDdrClkWeakDrv                         :  1;  // Bits 30:30
    UINT32 ClkGateDisable                          :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRCLKCH0_CR_DDRCRCLKCONTROLS_STRUCT;

typedef union {
  struct {
    UINT32 RunTest                                 :  1;  // Bits 0:0
    UINT32 Load                                    :  1;  // Bits 1:1
    UINT32 ModeHVM                                 :  1;  // Bits 2:2
    UINT32 ModeDV                                  :  1;  // Bits 3:3
    UINT32 CalCfdl                                 :  1;  // Bits 4:4
    UINT32 LoadCount                               :  10;  // Bits 14:5
    UINT32 CountStatus                             :  10;  // Bits 24:15
    UINT32 PhaseDrvPwrSavOn                        :  1;  // Bits 25:25
    UINT32 Spare                                   :  6;  // Bits 31:26
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRCLKCH0_CR_DLLPITESTANDADC_STRUCT;

typedef union {
  struct {
    UINT32 DllCB                                   :  2;  // Bits 1:0
    UINT32 Spare                                   :  30;  // Bits 31:2
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRCLKCH0_CR_DDRCBSTATUS_STRUCT;

typedef union {
  struct {
    UINT32 Ddr4BscanClockEnable                    :  1;  // Bits 0:0
    UINT32 Data_ClkP                               :  4;  // Bits 4:1
    UINT32 Data_ClkN                               :  4;  // Bits 8:5
    UINT32 Spare                                   :  23;  // Bits 31:9
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRCLKCH0_CR_DDR4CRBSCANDATA_STRUCT;

typedef union {
  struct {
    UINT32 Rsvd                                    :  11;  // Bits 10:0
    UINT32 DisSensorPwrDn                          :  1;  // Bits 11:11
    UINT32 OfstOvrdEn                              :  1;  // Bits 12:12
    UINT32 ViewOfstsel                             :  3;  // Bits 15:13
    UINT32 EnVttCompforVsshi                       :  1;  // Bits 16:16
    UINT32 Spares                                  :  8;  // Bits 24:17
    UINT32 Disable2Vt                              :  1;  // Bits 25:25
    UINT32 OfstOvrdOrView                          :  6;  // Bits 31:26
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRCLKCH0_CR_DDRVSSHICOMPCTL_STRUCT;

typedef union {
  struct {
    UINT32 RankEn                                  :  4;  // Bits 3:0
    UINT32 Spare                                   :  28;  // Bits 31:4
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRCLKCH1_CR_DDRCRCLKRANKSUSED_STRUCT;

typedef union {
  struct {
    UINT32 Scomp                                   :  5;  // Bits 4:0
    UINT32 TcoComp                                 :  6;  // Bits 10:5
    UINT32 RcompDrvUp                              :  6;  // Bits 16:11
    UINT32 RcompDrvDown                            :  6;  // Bits 22:17
    UINT32 Spare                                   :  9;  // Bits 31:23
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRCLKCH1_CR_DDRCRCLKCOMP_STRUCT;

typedef union {
  struct {
    INT32  ScompOffset                             :  4;  // Bits 3:0
    INT32  TcoCompOffset                           :  4;  // Bits 7:4
    INT32  RcompDrvUpOffset                        :  4;  // Bits 11:8
    INT32  RcompDrvDownOffset                      :  4;  // Bits 15:12
    UINT32 Spare                                   :  16;  // Bits 31:16
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRCLKCH1_CR_DDRCRCLKCOMPOFFSET_STRUCT;

typedef union {
  struct {
    UINT32 PiSettingRank0                          :  7;  // Bits 6:0
    UINT32 PiSettingRank1                          :  7;  // Bits 13:7
    UINT32 PiSettingRank2                          :  7;  // Bits 20:14
    UINT32 PiSettingRank3                          :  7;  // Bits 27:21
    UINT32 Spare                                   :  4;  // Bits 31:28
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRCLKCH1_CR_DDRCRCLKPICODE_STRUCT;

typedef union {
  struct {
    INT32  RefPi                                   :  4;  // Bits 3:0
    UINT32 DllMask                                 :  2;  // Bits 5:4
    UINT32 DllRsvd1                                :  1;  // Bits 6:6
    UINT32 TxOn                                    :  1;  // Bits 7:7
    UINT32 IntClkOn                                :  1;  // Bits 8:8
    UINT32 RepClkOn                                :  1;  // Bits 9:9
    UINT32 IOLBCtl                                 :  2;  // Bits 11:10
    UINT32 OdtMode                                 :  1;  // Bits 12:12
    UINT32 Reserved                                :  8;  // Bits 20:13
    INT32  RxVref                                  :  6;  // Bits 26:21
    UINT32 VccddqHi                                :  1;  // Bits 27:27
    UINT32 DllWeakLock                             :  1;  // Bits 28:28
    UINT32 LPDDR_Mode                              :  1;  // Bits 29:29
    UINT32 LPDdrClkWeakDrv                         :  1;  // Bits 30:30
    UINT32 ClkGateDisable                          :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRCLKCH1_CR_DDRCRCLKCONTROLS_STRUCT;

typedef union {
  struct {
    UINT32 RunTest                                 :  1;  // Bits 0:0
    UINT32 Load                                    :  1;  // Bits 1:1
    UINT32 ModeHVM                                 :  1;  // Bits 2:2
    UINT32 ModeDV                                  :  1;  // Bits 3:3
    UINT32 CalCfdl                                 :  1;  // Bits 4:4
    UINT32 LoadCount                               :  10;  // Bits 14:5
    UINT32 CountStatus                             :  10;  // Bits 24:15
    UINT32 PhaseDrvPwrSavOn                        :  1;  // Bits 25:25
    UINT32 Spare                                   :  6;  // Bits 31:26
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRCLKCH1_CR_DLLPITESTANDADC_STRUCT;

typedef union {
  struct {
    UINT32 DllCB                                   :  2;  // Bits 1:0
    UINT32 Spare                                   :  30;  // Bits 31:2
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRCLKCH1_CR_DDRCBSTATUS_STRUCT;

typedef union {
  struct {
    UINT32 Ddr4BscanClockEnable                    :  1;  // Bits 0:0
    UINT32 Data_ClkP                               :  4;  // Bits 4:1
    UINT32 Data_ClkN                               :  4;  // Bits 8:5
    UINT32 Spare                                   :  23;  // Bits 31:9
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRCLKCH1_CR_DDR4CRBSCANDATA_STRUCT;

typedef union {
  struct {
    UINT32 Rsvd                                    :  11;  // Bits 10:0
    UINT32 DisSensorPwrDn                          :  1;  // Bits 11:11
    UINT32 OfstOvrdEn                              :  1;  // Bits 12:12
    UINT32 ViewOfstsel                             :  3;  // Bits 15:13
    UINT32 EnVttCompforVsshi                       :  1;  // Bits 16:16
    UINT32 Spares                                  :  8;  // Bits 24:17
    UINT32 Disable2Vt                              :  1;  // Bits 25:25
    UINT32 OfstOvrdOrView                          :  6;  // Bits 31:26
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRCLKCH1_CR_DDRVSSHICOMPCTL_STRUCT;

typedef union {
  struct {
    UINT32 Scomp                                   :  6;  // Bits 5:0
    UINT32 TcoComp                                 :  6;  // Bits 11:6
    UINT32 RcompDrvUp                              :  6;  // Bits 17:12
    UINT32 RcompDrvDown                            :  6;  // Bits 23:18
    UINT32 Spare                                   :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRCMDSCH0_CR_DDRCRCMDCOMP_STRUCT;

typedef union {
  struct {
    INT32  ScompOffset                             :  5;  // Bits 4:0
    INT32  TcoCompOffset                           :  4;  // Bits 8:5
    INT32  RcompDrvUpOffset                        :  4;  // Bits 12:9
    INT32  RcompDrvDownOffset                      :  4;  // Bits 16:13
    UINT32 Spare                                   :  15;  // Bits 31:17
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRCMDSCH0_CR_DDRCRCMDCOMPOFFSET_STRUCT;

typedef union {
  struct {
    UINT32 CmdPi0Code                              :  7;  // Bits 6:0
    UINT32 CmdPi1Code                              :  7;  // Bits 13:7
    UINT32 Spare                                   :  18;  // Bits 31:14
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRCMDSCH0_CR_DDRCRCMDPICODING_STRUCT;

typedef union {
  struct {
    INT32  RefPi                                   :  4;  // Bits 3:0
    UINT32 DllMask                                 :  2;  // Bits 5:4
    UINT32 ClkGateDisable                          :  1;  // Bits 6:6
    UINT32 TxOn                                    :  1;  // Bits 7:7
    UINT32 IntClkOn                                :  1;  // Bits 8:8
    UINT32 RepClkOn                                :  1;  // Bits 9:9
    UINT32 IolbOrMisr                              :  1;  // Bits 10:10
    UINT32 IolbHold                                :  1;  // Bits 11:11
    UINT32 OdtMode                                 :  1;  // Bits 12:12
    UINT32 CmdTxEq                                 :  2;  // Bits 14:13
    UINT32 EarlyWeakDrive                          :  2;  // Bits 16:15
    UINT32 PrtEn                                   :  1;  // Bits 17:17
    UINT32 AlrtEn                                  :  1;  // Bits 18:18
    UINT32 LaDrvEnOvrd                             :  1;  // Bits 19:19
    UINT32 DdrCmdSlwDlyByp                         :  1;  // Bits 20:20
    INT32  RxVref                                  :  6;  // Bits 26:21
    UINT32 VccddqHi                                :  1;  // Bits 27:27
    UINT32 DllWeakLock                             :  1;  // Bits 28:28
    UINT32 LPDDR_Mode                              :  1;  // Bits 29:29
    UINT32 LPDdrCAA_Dis                            :  1;  // Bits 30:30
    UINT32 LPDdrCAB_Dis                            :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRCMDSCH0_CR_DDRCRCMDCONTROLS_STRUCT;

typedef union {
  struct {
    UINT32 RunTest                                 :  1;  // Bits 0:0
    UINT32 Load                                    :  1;  // Bits 1:1
    UINT32 ModeHVM                                 :  1;  // Bits 2:2
    UINT32 ModeDV                                  :  1;  // Bits 3:3
    UINT32 CalCfdl                                 :  1;  // Bits 4:4
    UINT32 LoadCount                               :  10;  // Bits 14:5
    UINT32 CountStatus                             :  10;  // Bits 24:15
    UINT32 PhaseDrvPwrSavOn                        :  1;  // Bits 25:25
    UINT32 Spare                                   :  6;  // Bits 31:26
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRCMDSCH0_CR_DLLPITESTANDADC_STRUCT;

typedef union {
  struct {
    UINT32 Scomp                                   :  6;  // Bits 5:0
    UINT32 TcoComp                                 :  6;  // Bits 11:6
    UINT32 RcompDrvUp                              :  6;  // Bits 17:12
    UINT32 RcompDrvDown                            :  6;  // Bits 23:18
    UINT32 Spare                                   :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRCMDSCH1_CR_DDRCRCMDCOMP_STRUCT;

typedef union {
  struct {
    INT32  ScompOffset                             :  5;  // Bits 4:0
    INT32  TcoCompOffset                           :  4;  // Bits 8:5
    INT32  RcompDrvUpOffset                        :  4;  // Bits 12:9
    INT32  RcompDrvDownOffset                      :  4;  // Bits 16:13
    UINT32 Spare                                   :  15;  // Bits 31:17
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRCMDSCH1_CR_DDRCRCMDCOMPOFFSET_STRUCT;

typedef union {
  struct {
    UINT32 CmdPi0Code                              :  7;  // Bits 6:0
    UINT32 CmdPi1Code                              :  7;  // Bits 13:7
    UINT32 Spare                                   :  18;  // Bits 31:14
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRCMDSCH1_CR_DDRCRCMDPICODING_STRUCT;

typedef union {
  struct {
    INT32  RefPi                                   :  4;  // Bits 3:0
    UINT32 DllMask                                 :  2;  // Bits 5:4
    UINT32 ClkGateDisable                          :  1;  // Bits 6:6
    UINT32 TxOn                                    :  1;  // Bits 7:7
    UINT32 IntClkOn                                :  1;  // Bits 8:8
    UINT32 RepClkOn                                :  1;  // Bits 9:9
    UINT32 IolbOrMisr                              :  1;  // Bits 10:10
    UINT32 IolbHold                                :  1;  // Bits 11:11
    UINT32 OdtMode                                 :  1;  // Bits 12:12
    UINT32 CmdTxEq                                 :  2;  // Bits 14:13
    UINT32 EarlyWeakDrive                          :  2;  // Bits 16:15
    UINT32 PrtEn                                   :  1;  // Bits 17:17
    UINT32 AlrtEn                                  :  1;  // Bits 18:18
    UINT32 LaDrvEnOvrd                             :  1;  // Bits 19:19
    UINT32 DdrCmdSlwDlyByp                         :  1;  // Bits 20:20
    INT32  RxVref                                  :  6;  // Bits 26:21
    UINT32 VccddqHi                                :  1;  // Bits 27:27
    UINT32 DllWeakLock                             :  1;  // Bits 28:28
    UINT32 LPDDR_Mode                              :  1;  // Bits 29:29
    UINT32 LPDdrCAA_Dis                            :  1;  // Bits 30:30
    UINT32 LPDdrCAB_Dis                            :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRCMDSCH1_CR_DDRCRCMDCONTROLS_STRUCT;

typedef union {
  struct {
    UINT32 RunTest                                 :  1;  // Bits 0:0
    UINT32 Load                                    :  1;  // Bits 1:1
    UINT32 ModeHVM                                 :  1;  // Bits 2:2
    UINT32 ModeDV                                  :  1;  // Bits 3:3
    UINT32 CalCfdl                                 :  1;  // Bits 4:4
    UINT32 LoadCount                               :  10;  // Bits 14:5
    UINT32 CountStatus                             :  10;  // Bits 24:15
    UINT32 PhaseDrvPwrSavOn                        :  1;  // Bits 25:25
    UINT32 Spare                                   :  6;  // Bits 31:26
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRCMDSCH1_CR_DLLPITESTANDADC_STRUCT;

typedef union {
  struct {
    UINT32 Scomp                                   :  6;  // Bits 5:0
    UINT32 TcoComp                                 :  6;  // Bits 11:6
    UINT32 RcompDrvUp                              :  6;  // Bits 17:12
    UINT32 RcompDrvDown                            :  6;  // Bits 23:18
    UINT32 Spare                                   :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRCTLCH0_CR_DDRCRCTLCOMP_STRUCT;

typedef union {
  struct {
    INT32  ScompOffset                             :  5;  // Bits 4:0
    INT32  TcoCompOffset                           :  4;  // Bits 8:5
    INT32  RcompDrvUpOffset                        :  4;  // Bits 12:9
    INT32  RcompDrvDownOffset                      :  4;  // Bits 16:13
    UINT32 Spare                                   :  15;  // Bits 31:17
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRCTLCH0_CR_DDRCRCTLCOMPOFFSET_STRUCT;

typedef union {
  struct {
    UINT32 CtlPiCode0                              :  7;  // Bits 6:0
    UINT32 CtlPiCode1                              :  7;  // Bits 13:7
    UINT32 CtlPiCode2                              :  7;  // Bits 20:14
    UINT32 CtlPiCode3                              :  7;  // Bits 27:21
    UINT32 CtlXoverEnable                          :  1;  // Bits 28:28
    UINT32 Spare                                   :  3;  // Bits 31:29
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRCTLCH0_CR_DDRCRCTLPICODING_STRUCT;

typedef union {
  struct {
    INT32  RefPi                                   :  4;  // Bits 3:0
    UINT32 DllMask                                 :  2;  // Bits 5:4
    UINT32 ClkGateDisable                          :  1;  // Bits 6:6
    UINT32 TxOn                                    :  1;  // Bits 7:7
    UINT32 IntClkOn                                :  1;  // Bits 8:8
    UINT32 RepClkOn                                :  1;  // Bits 9:9
    UINT32 IolbOrMisr                              :  1;  // Bits 10:10
    UINT32 IOLBHold                                :  1;  // Bits 11:11
    UINT32 OdtMode                                 :  1;  // Bits 12:12
    UINT32 CmdTxEq                                 :  2;  // Bits 14:13
    UINT32 EarlyWeakDrive                          :  2;  // Bits 16:15
    UINT32 CtlTxEq                                 :  2;  // Bits 18:17
    UINT32 CtlSRDrv                                :  2;  // Bits 20:19
    INT32  RxVref                                  :  6;  // Bits 26:21
    UINT32 VccddqHi                                :  1;  // Bits 27:27
    UINT32 DllWeakLock                             :  1;  // Bits 28:28
    UINT32 LPDDR_Mode                              :  1;  // Bits 29:29
    UINT32 LaDrvEnOvrd                             :  1;  // Bits 30:30
    UINT32 LPDdrCAA_Dis                            :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRCTLCH0_CR_DDRCRCTLCONTROLS_STRUCT;

typedef union {
  struct {
    UINT32 RankEn                                  :  4;  // Bits 3:0
    UINT32 OdtDisable                              :  2;  // Bits 5:4
    UINT32 DdrCkeCmdSlwDlyByp                      :  1;  // Bits 6:6
    UINT32 DdrCtlCkeSlwDlyByp                      :  1;  // Bits 7:7
    UINT32 CsPiClkGateEn                           :  1;  // Bits 8:8
    UINT32 CsClkGateDis                            :  1;  // Bits 9:9
    UINT32 Spare                                   :  22;  // Bits 31:10
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRCTLCH0_CR_DDRCRCTLRANKSUSED_STRUCT;

typedef union {
  struct {
    UINT32 RunTest                                 :  1;  // Bits 0:0
    UINT32 Load                                    :  1;  // Bits 1:1
    UINT32 ModeHVM                                 :  1;  // Bits 2:2
    UINT32 ModeDV                                  :  1;  // Bits 3:3
    UINT32 CalCfdl                                 :  1;  // Bits 4:4
    UINT32 LoadCount                               :  10;  // Bits 14:5
    UINT32 CountStatus                             :  10;  // Bits 24:15
    UINT32 PhaseDrvPwrSavOn                        :  1;  // Bits 25:25
    UINT32 Spare                                   :  6;  // Bits 31:26
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRCTLCH0_CR_DLLPITESTANDADC_STRUCT;

typedef union {
  struct {
    UINT32 Scomp                                   :  6;  // Bits 5:0
    UINT32 TcoComp                                 :  6;  // Bits 11:6
    UINT32 RcompDrvUp                              :  6;  // Bits 17:12
    UINT32 RcompDrvDown                            :  6;  // Bits 23:18
    UINT32 Spare                                   :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRCTLCH1_CR_DDRCRCTLCOMP_STRUCT;

typedef union {
  struct {
    INT32  ScompOffset                             :  5;  // Bits 4:0
    INT32  TcoCompOffset                           :  4;  // Bits 8:5
    INT32  RcompDrvUpOffset                        :  4;  // Bits 12:9
    INT32  RcompDrvDownOffset                      :  4;  // Bits 16:13
    UINT32 Spare                                   :  15;  // Bits 31:17
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRCTLCH1_CR_DDRCRCTLCOMPOFFSET_STRUCT;

typedef union {
  struct {
    UINT32 CtlPiCode0                              :  7;  // Bits 6:0
    UINT32 CtlPiCode1                              :  7;  // Bits 13:7
    UINT32 CtlPiCode2                              :  7;  // Bits 20:14
    UINT32 CtlPiCode3                              :  7;  // Bits 27:21
    UINT32 CtlXoverEnable                          :  1;  // Bits 28:28
    UINT32 Spare                                   :  3;  // Bits 31:29
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRCTLCH1_CR_DDRCRCTLPICODING_STRUCT;

typedef union {
  struct {
    INT32  RefPi                                   :  4;  // Bits 3:0
    UINT32 DllMask                                 :  2;  // Bits 5:4
    UINT32 ClkGateDisable                          :  1;  // Bits 6:6
    UINT32 TxOn                                    :  1;  // Bits 7:7
    UINT32 IntClkOn                                :  1;  // Bits 8:8
    UINT32 RepClkOn                                :  1;  // Bits 9:9
    UINT32 IolbOrMisr                              :  1;  // Bits 10:10
    UINT32 IOLBHold                                :  1;  // Bits 11:11
    UINT32 OdtMode                                 :  1;  // Bits 12:12
    UINT32 CmdTxEq                                 :  2;  // Bits 14:13
    UINT32 EarlyWeakDrive                          :  2;  // Bits 16:15
    UINT32 CtlTxEq                                 :  2;  // Bits 18:17
    UINT32 CtlSRDrv                                :  2;  // Bits 20:19
    INT32  RxVref                                  :  6;  // Bits 26:21
    UINT32 VccddqHi                                :  1;  // Bits 27:27
    UINT32 DllWeakLock                             :  1;  // Bits 28:28
    UINT32 LPDDR_Mode                              :  1;  // Bits 29:29
    UINT32 LaDrvEnOvrd                             :  1;  // Bits 30:30
    UINT32 LPDdrCAA_Dis                            :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRCTLCH1_CR_DDRCRCTLCONTROLS_STRUCT;

typedef union {
  struct {
    UINT32 RankEn                                  :  4;  // Bits 3:0
    UINT32 OdtDisable                              :  2;  // Bits 5:4
    UINT32 DdrCkeCmdSlwDlyByp                      :  1;  // Bits 6:6
    UINT32 DdrCtlCkeSlwDlyByp                      :  1;  // Bits 7:7
    UINT32 CsPiClkGateEn                           :  1;  // Bits 8:8
    UINT32 CsClkGateDis                            :  1;  // Bits 9:9
    UINT32 Spare                                   :  22;  // Bits 31:10
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRCTLCH1_CR_DDRCRCTLRANKSUSED_STRUCT;

typedef union {
  struct {
    UINT32 RunTest                                 :  1;  // Bits 0:0
    UINT32 Load                                    :  1;  // Bits 1:1
    UINT32 ModeHVM                                 :  1;  // Bits 2:2
    UINT32 ModeDV                                  :  1;  // Bits 3:3
    UINT32 CalCfdl                                 :  1;  // Bits 4:4
    UINT32 LoadCount                               :  10;  // Bits 14:5
    UINT32 CountStatus                             :  10;  // Bits 24:15
    UINT32 PhaseDrvPwrSavOn                        :  1;  // Bits 25:25
    UINT32 Spare                                   :  6;  // Bits 31:26
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRCTLCH1_CR_DLLPITESTANDADC_STRUCT;

#pragma pack(pop)
#endif
