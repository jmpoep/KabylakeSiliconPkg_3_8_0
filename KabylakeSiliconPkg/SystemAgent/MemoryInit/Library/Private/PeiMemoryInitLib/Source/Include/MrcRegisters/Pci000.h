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
#ifndef __Pci000_h__
#define __Pci000_h__

#pragma pack(push, 1)
#include "MrcTypes.h"

typedef union {
  struct {
    UINT8  RID                                     :  4;  // Bits 3:0
    UINT8  RID_MSB                                 :  4;  // Bits 7:4
  } Bits;
  UINT8  Data;
} UNCORE_CR_RID_0_0_0_PCI_STRUCT;

typedef union {
  struct {
    UINT64 PXPEPBAREN                              :  1;  // Bits 0:0
    UINT64                                         :  11;  // Bits 11:1
    UINT64 PXPEPBAR                                :  27;  // Bits 38:12
    UINT64                                         :  25;  // Bits 63:39
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} UNCORE_CR_PXPEPBAR_0_0_0_PCI_STRUCT;

typedef union {
  struct {
    UINT64 MCHBAREN                                :  1;  // Bits 0:0
    UINT64                                         :  14;  // Bits 14:1
    UINT64 MCHBAR                                  :  24;  // Bits 38:15
    UINT64                                         :  25;  // Bits 63:39
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} UNCORE_CR_MCHBAR_0_0_0_PCI_STRUCT;

typedef union {
  struct {
    UINT16 GGCLCK                                  :  1;  // Bits 0:0
    UINT16 IVD                                     :  1;  // Bits 1:1
    UINT16 VAMEN                                   :  1;  // Bits 2:2
    UINT16                                         :  3;  // Bits 5:3
    UINT16 GGMS                                    :  2;  // Bits 7:6
    UINT16 GMS                                     :  8;  // Bits 15:8
  } Bits;
  UINT16 Data;
  UINT8  Data8[2];
} UNCORE_CR_GGC_0_0_0_PCI_STRUCT;

typedef union {
  struct {
    UINT32 D0EN                                    :  1;  // Bits 0:0
    UINT32 D1F2EN                                  :  1;  // Bits 1:1
    UINT32 D1F1EN                                  :  1;  // Bits 2:2
    UINT32 D1F0EN                                  :  1;  // Bits 3:3
    UINT32 D2EN                                    :  1;  // Bits 4:4
    UINT32 D3EN                                    :  1;  // Bits 5:5
    UINT32                                         :  1;  // Bits 6:6
    UINT32 D4EN                                    :  1;  // Bits 7:7
    UINT32                                         :  2;  // Bits 9:8
    UINT32 D5EN                                    :  1;  // Bits 10:10
    UINT32                                         :  2;  // Bits 12:11
    UINT32 D6EN                                    :  1;  // Bits 13:13
    UINT32 D7EN                                    :  1;  // Bits 14:14
    UINT32 D8EN                                    :  1;  // Bits 15:15
    UINT32                                         :  16;  // Bits 31:16
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} UNCORE_CR_DEVEN_0_0_0_PCI_STRUCT;

typedef union {
  struct {
    UINT32 PCME                                    :  1;  // Bits 0:0
    UINT32 PAVPE                                   :  1;  // Bits 1:1
    UINT32 PAVPLCK                                 :  1;  // Bits 2:2
    UINT32 HVYMODSEL                               :  1;  // Bits 3:3
    UINT32 OVTATTACK                               :  1;  // Bits 4:4
    UINT32 RSVD1                                   :  1;  // Bits 5:5
    UINT32 ASMFEN                                  :  1;  // Bits 6:6
    UINT32 RSVD2                                   :  13;  // Bits 19:7
    UINT32 PCMBASE                                 :  12;  // Bits 31:20
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} UNCORE_CR_PAVPC_0_0_0_PCI_STRUCT;

typedef union {
  struct {
    UINT32 LOCK                                    :  1;  // Bits 0:0
    UINT32 PRS                                     :  1;  // Bits 1:1
    UINT32 EPM                                     :  1;  // Bits 2:2
    UINT32                                         :  1;  // Bits 3:3
    UINT32 DPRSIZE                                 :  8;  // Bits 11:4
    UINT32                                         :  8;  // Bits 19:12
    UINT32 TopOfDPR                                :  12;  // Bits 31:20
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} UNCORE_CR_DPR_0_0_0_PCI_STRUCT;

typedef union {
  struct {
    UINT64 PCIEXBAREN                              :  1;  // Bits 0:0
    UINT64 LENGTH                                  :  2;  // Bits 2:1
    UINT64                                         :  23;  // Bits 25:3
    UINT64 ADMSK64                                 :  1;  // Bits 26:26
    UINT64 ADMSK128                                :  1;  // Bits 27:27
    UINT64 PCIEXBAR                                :  11;  // Bits 38:28
    UINT64                                         :  25;  // Bits 63:39
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} UNCORE_CR_PCIEXBAR_0_0_0_PCI_STRUCT;

typedef union {
  struct {
    UINT64 DMIBAREN                                :  1;  // Bits 0:0
    UINT64                                         :  11;  // Bits 11:1
    UINT64 DMIBAR                                  :  27;  // Bits 38:12
    UINT64                                         :  25;  // Bits 63:39
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} UNCORE_CR_DMIBAR_0_0_0_PCI_STRUCT;

typedef union {
  struct {
    UINT64                                         :  20;  // Bits 19:0
    UINT64 MEBASE                                  :  19;  // Bits 38:20
    UINT64                                         :  25;  // Bits 63:39
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} UNCORE_CR_MESEG_BASE_0_0_0_PCI_STRUCT;

typedef union {
  struct {
    UINT64                                         :  10;  // Bits 9:0
    UINT64 MELCK                                   :  1;  // Bits 10:10
    UINT64 ME_STLEN_EN                             :  1;  // Bits 11:11
    UINT64                                         :  8;  // Bits 19:12
    UINT64 MEMASK                                  :  19;  // Bits 38:20
    UINT64                                         :  25;  // Bits 63:39
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} UNCORE_CR_MESEG_MASK_0_0_0_PCI_STRUCT;

typedef union {
  struct {
    UINT8  Lock                                    :  1;  // Bits 0:0
    UINT8                                          :  3;  // Bits 3:1
    UINT8  HIENABLE                                :  2;  // Bits 5:4
    UINT8                                          :  2;  // Bits 7:6
  } Bits;
  UINT8  Data;
} UNCORE_CR_PAM0_0_0_0_PCI_STRUCT;

typedef union {
  struct {
    UINT8  LOENABLE                                :  2;  // Bits 1:0
    UINT8                                          :  2;  // Bits 3:2
    UINT8  HIENABLE                                :  2;  // Bits 5:4
    UINT8                                          :  2;  // Bits 7:6
  } Bits;
  UINT8  Data;
} UNCORE_CR_PAM1_0_0_0_PCI_STRUCT;

typedef union {
  struct {
    UINT8  LOENABLE                                :  2;  // Bits 1:0
    UINT8                                          :  2;  // Bits 3:2
    UINT8  HIENABLE                                :  2;  // Bits 5:4
    UINT8                                          :  2;  // Bits 7:6
  } Bits;
  UINT8  Data;
} UNCORE_CR_PAM2_0_0_0_PCI_STRUCT;

typedef union {
  struct {
    UINT8  LOENABLE                                :  2;  // Bits 1:0
    UINT8                                          :  2;  // Bits 3:2
    UINT8  HIENABLE                                :  2;  // Bits 5:4
    UINT8                                          :  2;  // Bits 7:6
  } Bits;
  UINT8  Data;
} UNCORE_CR_PAM3_0_0_0_PCI_STRUCT;

typedef union {
  struct {
    UINT8  LOENABLE                                :  2;  // Bits 1:0
    UINT8                                          :  2;  // Bits 3:2
    UINT8  HIENABLE                                :  2;  // Bits 5:4
    UINT8                                          :  2;  // Bits 7:6
  } Bits;
  UINT8  Data;
} UNCORE_CR_PAM4_0_0_0_PCI_STRUCT;

typedef union {
  struct {
    UINT8  LOENABLE                                :  2;  // Bits 1:0
    UINT8                                          :  2;  // Bits 3:2
    UINT8  HIENABLE                                :  2;  // Bits 5:4
    UINT8                                          :  2;  // Bits 7:6
  } Bits;
  UINT8  Data;
} UNCORE_CR_PAM5_0_0_0_PCI_STRUCT;

typedef union {
  struct {
    UINT8  LOENABLE                                :  2;  // Bits 1:0
    UINT8                                          :  2;  // Bits 3:2
    UINT8  HIENABLE                                :  2;  // Bits 5:4
    UINT8                                          :  2;  // Bits 7:6
  } Bits;
  UINT8  Data;
} UNCORE_CR_PAM6_0_0_0_PCI_STRUCT;

typedef union {
  struct {
    UINT8  MDAP10                                  :  1;  // Bits 0:0
    UINT8  MDAP11                                  :  1;  // Bits 1:1
    UINT8  MDAP12                                  :  1;  // Bits 2:2
    UINT8  MDAP60                                  :  1;  // Bits 3:3
    UINT8                                          :  3;  // Bits 6:4
    UINT8  HEN                                     :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} UNCORE_CR_LAC_0_0_0_PCI_STRUCT;

typedef union {
  struct {
    UINT8  C_BASE_SEG                              :  3;  // Bits 2:0
    UINT8  G_SMRAME                                :  1;  // Bits 3:3
    UINT8  D_LCK                                   :  1;  // Bits 4:4
    UINT8  D_CLS                                   :  1;  // Bits 5:5
    UINT8  D_OPEN                                  :  1;  // Bits 6:6
    UINT8                                          :  1;  // Bits 7:7
  } Bits;
  UINT8  Data;
} UNCORE_CR_SMRAMC_0_0_0_PCI_STRUCT;

typedef union {
  struct {
    UINT64 LOCK                                    :  1;  // Bits 0:0
    UINT64                                         :  19;  // Bits 19:1
    UINT64 REMAPBASE                               :  19;  // Bits 38:20
    UINT64                                         :  25;  // Bits 63:39
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} UNCORE_CR_REMAPBASE_0_0_0_PCI_STRUCT;

typedef union {
  struct {
    UINT64 LOCK                                    :  1;  // Bits 0:0
    UINT64                                         :  19;  // Bits 19:1
    UINT64 REMAPLMT                                :  19;  // Bits 38:20
    UINT64                                         :  25;  // Bits 63:39
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} UNCORE_CR_REMAPLIMIT_0_0_0_PCI_STRUCT;

typedef union {
  struct {
    UINT64 LOCK                                    :  1;  // Bits 0:0
    UINT64                                         :  19;  // Bits 19:1
    UINT64 TOM                                     :  19;  // Bits 38:20
    UINT64                                         :  25;  // Bits 63:39
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} UNCORE_CR_TOM_0_0_0_PCI_STRUCT;

typedef union {
  struct {
    UINT64 LOCK                                    :  1;  // Bits 0:0
    UINT64                                         :  19;  // Bits 19:1
    UINT64 TOUUD                                   :  19;  // Bits 38:20
    UINT64                                         :  25;  // Bits 63:39
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} UNCORE_CR_TOUUD_0_0_0_PCI_STRUCT;

typedef union {
  struct {
    UINT32 LOCK                                    :  1;  // Bits 0:0
    UINT32                                         :  19;  // Bits 19:1
    UINT32 BDSM                                    :  12;  // Bits 31:20
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} UNCORE_CR_BDSM_0_0_0_PCI_STRUCT;

typedef union {
  struct {
    UINT32 LOCK                                    :  1;  // Bits 0:0
    UINT32                                         :  19;  // Bits 19:1
    UINT32 BGSM                                    :  12;  // Bits 31:20
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} UNCORE_CR_BGSM_0_0_0_PCI_STRUCT;

typedef union {
  struct {
    UINT32 LOCK                                    :  1;  // Bits 0:0
    UINT32                                         :  19;  // Bits 19:1
    UINT32 TSEGMB                                  :  12;  // Bits 31:20
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} UNCORE_CR_TSEGMB_0_0_0_PCI_STRUCT;

typedef union {
  struct {
    UINT32 LOCK                                    :  1;  // Bits 0:0
    UINT32                                         :  19;  // Bits 19:1
    UINT32 TOLUD                                   :  12;  // Bits 31:20
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} UNCORE_CR_TOLUD_0_0_0_PCI_STRUCT;

typedef union {
  struct {
    UINT32 DID2OVR                                 :  8;  // Bits 7:0
    UINT32 OE2                                     :  1;  // Bits 8:8
    UINT32                                         :  7;  // Bits 15:9
    UINT32 DID0OVR                                 :  8;  // Bits 23:16
    UINT32 OE0                                     :  1;  // Bits 24:24
    UINT32                                         :  7;  // Bits 31:25
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} UNCORE_CR_DIDOVR_0_0_0_PCI_STRUCT;

typedef union {
  struct {
    UINT16 DSERR                                   :  1;  // Bits 0:0
    UINT16 DMERR                                   :  1;  // Bits 1:1
    UINT16                                         :  14;  // Bits 15:2
  } Bits;
  UINT16 Data;
  UINT8  Data8[2];
} UNCORE_CR_ERRSTS_0_0_0_PCI_STRUCT;

typedef union {
  struct {
    UINT16 DSERR                                   :  1;  // Bits 0:0
    UINT16 DMERR                                   :  1;  // Bits 1:1
    UINT16                                         :  14;  // Bits 15:2
  } Bits;
  UINT16 Data;
  UINT8  Data8[2];
} UNCORE_CR_ERRCMD_0_0_0_PCI_STRUCT;

typedef union {
  struct {
    UINT16 DSESMI                                  :  1;  // Bits 0:0
    UINT16 DMESMI                                  :  1;  // Bits 1:1
    UINT16                                         :  14;  // Bits 15:2
  } Bits;
  UINT16 Data;
  UINT8  Data8[2];
} UNCORE_CR_SMICMD_0_0_0_PCI_STRUCT;

typedef union {
  struct {
    UINT16 DSESCI                                  :  1;  // Bits 0:0
    UINT16 DMESCI                                  :  1;  // Bits 1:1
    UINT16                                         :  14;  // Bits 15:2
  } Bits;
  UINT16 Data;
  UINT8  Data8[2];
} UNCORE_CR_SCICMD_0_0_0_PCI_STRUCT;

typedef union {
  struct {
    UINT32 SKPD                                    :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} UNCORE_CR_SKPD_0_0_0_PCI_STRUCT;

typedef union {
  struct {
    UINT16 CAP_ID                                  :  8;  // Bits 7:0
    UINT16 NEXT_CAP                                :  8;  // Bits 15:8
  } Bits;
  UINT16 Data;
  UINT8  Data8[2];
} UNCORE_CR_CAPID0_0_0_0_PCI_STRUCT;

typedef union {
  struct {
    UINT16 CAPIDLEN                                :  8;  // Bits 7:0
    UINT16 CAPID_VER                               :  4;  // Bits 11:8
    UINT16                                         :  4;  // Bits 15:12
  } Bits;
  UINT16 Data;
  UINT8  Data8[2];
} UNCORE_CR_CAPCTRL0_0_0_0_PCI_STRUCT;

typedef union {
  struct {
    UINT32 DDR3L_EN                                :  1;  // Bits 0:0
    UINT32 DDR_WRTVREF                             :  1;  // Bits 1:1
    UINT32 OC_ENABLED_DSKU                         :  1;  // Bits 2:2
    UINT32 DDR_OVERCLOCK                           :  1;  // Bits 3:3
    UINT32 CRID                                    :  4;  // Bits 7:4
    UINT32 SPARE8                                  :  1;  // Bits 8:8
    UINT32 DID2OE                                  :  1;  // Bits 9:9
    UINT32 DID0OE                                  :  1;  // Bits 10:10
    UINT32 IGD                                     :  1;  // Bits 11:11
    UINT32 PDCD                                    :  1;  // Bits 12:12
    UINT32 X2APIC_EN                               :  1;  // Bits 13:13
    UINT32 DDPCD                                   :  1;  // Bits 14:14
    UINT32 CDD                                     :  1;  // Bits 15:15
    UINT32 FUFRD                                   :  1;  // Bits 16:16
    UINT32 D1NM                                    :  1;  // Bits 17:17
    UINT32 SPARE18                                 :  1;  // Bits 18:18
    UINT32 DDRSZ                                   :  2;  // Bits 20:19
    UINT32 PEGG2DIS                                :  1;  // Bits 21:21
    UINT32 DMIG2DIS                                :  1;  // Bits 22:22
    UINT32 VTDD                                    :  1;  // Bits 23:23
    UINT32 FDEE                                    :  1;  // Bits 24:24
    UINT32 ECCDIS                                  :  1;  // Bits 25:25
    UINT32 DW                                      :  1;  // Bits 26:26
    UINT32 PELWUD                                  :  1;  // Bits 27:27
    UINT32 PEG10D                                  :  1;  // Bits 28:28
    UINT32 PEG11D                                  :  1;  // Bits 29:29
    UINT32 PEG12D                                  :  1;  // Bits 30:30
    UINT32 DHDAD                                   :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} UNCORE_CR_CAPID0_A_0_0_0_PCI_STRUCT;

typedef union {
  struct {
    UINT32 SPEGFX1                                 :  1;  // Bits 0:0
    UINT32 DPEGFX1                                 :  1;  // Bits 1:1
    UINT32 LPDDR3_EN                               :  1;  // Bits 2:2
    UINT32 DDR4_EN                                 :  1;  // Bits 3:3
    UINT32 DMFC_DDR3                               :  3;  // Bits 6:4
    UINT32 DDD                                     :  1;  // Bits 7:7
    UINT32 GMM_DIS                                 :  1;  // Bits 8:8
    UINT32 SPARE10_9                               :  2;  // Bits 10:9
    UINT32 HDCPD                                   :  1;  // Bits 11:11
    UINT32 SPARE14_12                              :  3;  // Bits 14:12
    UINT32 DMIG3DIS                                :  1;  // Bits 15:15
    UINT32 PEGX16D                                 :  1;  // Bits 16:16
    UINT32 ADDGFXCAP                               :  1;  // Bits 17:17
    UINT32 ADDGFXEN                                :  1;  // Bits 18:18
    UINT32 PKGTYP                                  :  1;  // Bits 19:19
    UINT32 PEGG3_DIS                               :  1;  // Bits 20:20
    UINT32 PLL_REF100_CFG                          :  3;  // Bits 23:21
    UINT32 SPARE24                                 :  1;  // Bits 24:24
    UINT32 CACHESZ                                 :  3;  // Bits 27:25
    UINT32 SMT                                     :  1;  // Bits 28:28
    UINT32 OC_ENABLED                              :  1;  // Bits 29:29
    UINT32 SPARE30                                 :  1;  // Bits 30:30
    UINT32 IMGU_DIS                                :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} UNCORE_CR_CAPID0_B_0_0_0_PCI_STRUCT;

typedef union {
  struct {
    UINT32                                         :  14;  // Bits 13:0
    UINT32 DMFC_LPDDR3                             :  3;  // Bits 16:14
    UINT32 DMFC_DDR4                               :  3;  // Bits 19:17
    UINT32                                         :  12;  // Bits 31:20
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} UNCORE_CR_CAPID0_C_0_0_0_PCI_STRUCT;

typedef union {
  struct {
    UINT8                                          :  5;  // Bits 4:0
    UINT8  IGTLBF                                  :  1;  // Bits 5:5
    UINT8                                          :  2;  // Bits 7:6
  } Bits;
  UINT8  Data;
} UNCORE_CR_BCFC_0_0_0_PCI_STRUCT;

typedef union {
  struct {
    UINT32 DOT                                     :  3;  // Bits 2:0
    UINT32 PROC                                    :  5;  // Bits 7:3
    UINT32 FOUND                                   :  8;  // Bits 15:8
    UINT32 MSTEP                                   :  8;  // Bits 23:16
    UINT32                                         :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} UNCORE_CR_MID_0_0_0_PCI_STRUCT;

typedef union {
  struct {
    UINT32 RSVD_S0                                 :  3;  // Bits 2:0
    UINT32                                         :  1;  // Bits 3:3
    UINT32 RSVD_S1                                 :  3;  // Bits 6:4
    UINT32                                         :  1;  // Bits 7:7
    UINT32 RSVD_S2                                 :  3;  // Bits 10:8
    UINT32                                         :  1;  // Bits 11:11
    UINT32 RSVD_S3                                 :  3;  // Bits 14:12
    UINT32                                         :  1;  // Bits 15:15
    UINT32 RSVD_S4                                 :  3;  // Bits 18:16
    UINT32                                         :  1;  // Bits 19:19
    UINT32 RSVD_RW                                 :  12;  // Bits 31:20
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} UNCORE_CR_DEBUP0_0_0_0_PCI_STRUCT;

typedef union {
  struct {
    UINT32 RSVD0                                   :  3;  // Bits 2:0
    UINT32 RSVD1                                   :  1;  // Bits 3:3
    UINT32 RSVD2                                   :  3;  // Bits 6:4
    UINT32 RSVD3                                   :  1;  // Bits 7:7
    UINT32 RSVD4                                   :  3;  // Bits 10:8
    UINT32 RSVD5                                   :  1;  // Bits 11:11
    UINT32 RSVD6                                   :  3;  // Bits 14:12
    UINT32 RSVD7                                   :  1;  // Bits 15:15
    UINT32 RSVD8                                   :  3;  // Bits 18:16
    UINT32 RSVD9                                   :  1;  // Bits 19:19
    UINT32 RSVD10                                  :  12;  // Bits 31:20
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} UNCORE_CR_DEBUP1_0_0_0_PCI_STRUCT;


#define UNCORE_CR_RID_0_0_0_PCI_REG                                  (0x00000008)
  #define UNCORE_CR_RID_0_0_0_PCI_RID_OFF                              ( 0)
  #define UNCORE_CR_RID_0_0_0_PCI_RID_WID                              ( 4)
  #define UNCORE_CR_RID_0_0_0_PCI_RID_MSK                              (0x0000000F)
  #define UNCORE_CR_RID_0_0_0_PCI_RID_MAX                              (0x0000000F)
  #define UNCORE_CR_RID_0_0_0_PCI_RID_DEF                              (0x00000000)
  #define UNCORE_CR_RID_0_0_0_PCI_RID_MSB_OFF                          ( 4)
  #define UNCORE_CR_RID_0_0_0_PCI_RID_MSB_WID                          ( 4)
  #define UNCORE_CR_RID_0_0_0_PCI_RID_MSB_MSK                          (0x000000F0)
  #define UNCORE_CR_RID_0_0_0_PCI_RID_MSB_MAX                          (0x0000000F)
  #define UNCORE_CR_RID_0_0_0_PCI_RID_MSB_DEF                          (0x00000000)

#define UNCORE_CR_PXPEPBAR_0_0_0_PCI_REG                             (0x00000040)
  #define UNCORE_CR_PXPEPBAR_0_0_0_PCI_PXPEPBAREN_OFF                  ( 0)
  #define UNCORE_CR_PXPEPBAR_0_0_0_PCI_PXPEPBAREN_WID                  ( 1)
  #define UNCORE_CR_PXPEPBAR_0_0_0_PCI_PXPEPBAREN_MSK                  (0x00000001)
  #define UNCORE_CR_PXPEPBAR_0_0_0_PCI_PXPEPBAREN_MAX                  (0x00000001)
  #define UNCORE_CR_PXPEPBAR_0_0_0_PCI_PXPEPBAREN_DEF                  (0x00000000)
  #define UNCORE_CR_PXPEPBAR_0_0_0_PCI_PXPEPBAR_OFF                    (12)
  #define UNCORE_CR_PXPEPBAR_0_0_0_PCI_PXPEPBAR_WID                    (27)
  #define UNCORE_CR_PXPEPBAR_0_0_0_PCI_PXPEPBAR_MSK                    (0x7FFFFFF000)
  #define UNCORE_CR_PXPEPBAR_0_0_0_PCI_PXPEPBAR_MAX                    (0x07FFFFFF)
  #define UNCORE_CR_PXPEPBAR_0_0_0_PCI_PXPEPBAR_DEF                    (0x00000000)

#define UNCORE_CR_MCHBAR_0_0_0_PCI_REG                               (0x00000048)
  #define UNCORE_CR_MCHBAR_0_0_0_PCI_MCHBAREN_OFF                      ( 0)
  #define UNCORE_CR_MCHBAR_0_0_0_PCI_MCHBAREN_WID                      ( 1)
  #define UNCORE_CR_MCHBAR_0_0_0_PCI_MCHBAREN_MSK                      (0x00000001)
  #define UNCORE_CR_MCHBAR_0_0_0_PCI_MCHBAREN_MAX                      (0x00000001)
  #define UNCORE_CR_MCHBAR_0_0_0_PCI_MCHBAREN_DEF                      (0x00000000)
  #define UNCORE_CR_MCHBAR_0_0_0_PCI_MCHBAR_OFF                        (15)
  #define UNCORE_CR_MCHBAR_0_0_0_PCI_MCHBAR_WID                        (24)
  #define UNCORE_CR_MCHBAR_0_0_0_PCI_MCHBAR_MSK                        (0x7FFFFF8000)
  #define UNCORE_CR_MCHBAR_0_0_0_PCI_MCHBAR_MAX                        (0x00FFFFFF)
  #define UNCORE_CR_MCHBAR_0_0_0_PCI_MCHBAR_DEF                        (0x00000000)

#define UNCORE_CR_GGC_0_0_0_PCI_REG                                  (0x00000050)
  #define UNCORE_CR_GGC_0_0_0_PCI_GGCLCK_OFF                           ( 0)
  #define UNCORE_CR_GGC_0_0_0_PCI_GGCLCK_WID                           ( 1)
  #define UNCORE_CR_GGC_0_0_0_PCI_GGCLCK_MSK                           (0x00000001)
  #define UNCORE_CR_GGC_0_0_0_PCI_GGCLCK_MAX                           (0x00000001)
  #define UNCORE_CR_GGC_0_0_0_PCI_GGCLCK_DEF                           (0x00000000)
  #define UNCORE_CR_GGC_0_0_0_PCI_IVD_OFF                              ( 1)
  #define UNCORE_CR_GGC_0_0_0_PCI_IVD_WID                              ( 1)
  #define UNCORE_CR_GGC_0_0_0_PCI_IVD_MSK                              (0x00000002)
  #define UNCORE_CR_GGC_0_0_0_PCI_IVD_MAX                              (0x00000001)
  #define UNCORE_CR_GGC_0_0_0_PCI_IVD_DEF                              (0x00000000)
  #define UNCORE_CR_GGC_0_0_0_PCI_VAMEN_OFF                            ( 2)
  #define UNCORE_CR_GGC_0_0_0_PCI_VAMEN_WID                            ( 1)
  #define UNCORE_CR_GGC_0_0_0_PCI_VAMEN_MSK                            (0x00000004)
  #define UNCORE_CR_GGC_0_0_0_PCI_VAMEN_MAX                            (0x00000001)
  #define UNCORE_CR_GGC_0_0_0_PCI_VAMEN_DEF                            (0x00000000)
  #define UNCORE_CR_GGC_0_0_0_PCI_GGMS_OFF                             ( 6)
  #define UNCORE_CR_GGC_0_0_0_PCI_GGMS_WID                             ( 2)
  #define UNCORE_CR_GGC_0_0_0_PCI_GGMS_MSK                             (0x000000C0)
  #define UNCORE_CR_GGC_0_0_0_PCI_GGMS_MAX                             (0x00000003)
  #define UNCORE_CR_GGC_0_0_0_PCI_GGMS_DEF                             (0x00000000)
  #define UNCORE_CR_GGC_0_0_0_PCI_GMS_OFF                              ( 8)
  #define UNCORE_CR_GGC_0_0_0_PCI_GMS_WID                              ( 8)
  #define UNCORE_CR_GGC_0_0_0_PCI_GMS_MSK                              (0x0000FF00)
  #define UNCORE_CR_GGC_0_0_0_PCI_GMS_MAX                              (0x000000FF)
  #define UNCORE_CR_GGC_0_0_0_PCI_GMS_DEF                              (0x00000005)

#define UNCORE_CR_DEVEN_0_0_0_PCI_REG                                (0x00000054)
  #define UNCORE_CR_DEVEN_0_0_0_PCI_D0EN_OFF                           ( 0)
  #define UNCORE_CR_DEVEN_0_0_0_PCI_D0EN_WID                           ( 1)
  #define UNCORE_CR_DEVEN_0_0_0_PCI_D0EN_MSK                           (0x00000001)
  #define UNCORE_CR_DEVEN_0_0_0_PCI_D0EN_MAX                           (0x00000001)
  #define UNCORE_CR_DEVEN_0_0_0_PCI_D0EN_DEF                           (0x00000001)
  #define UNCORE_CR_DEVEN_0_0_0_PCI_D1F2EN_OFF                         ( 1)
  #define UNCORE_CR_DEVEN_0_0_0_PCI_D1F2EN_WID                         ( 1)
  #define UNCORE_CR_DEVEN_0_0_0_PCI_D1F2EN_MSK                         (0x00000002)
  #define UNCORE_CR_DEVEN_0_0_0_PCI_D1F2EN_MAX                         (0x00000001)
  #define UNCORE_CR_DEVEN_0_0_0_PCI_D1F2EN_DEF                         (0x00000001)
  #define UNCORE_CR_DEVEN_0_0_0_PCI_D1F1EN_OFF                         ( 2)
  #define UNCORE_CR_DEVEN_0_0_0_PCI_D1F1EN_WID                         ( 1)
  #define UNCORE_CR_DEVEN_0_0_0_PCI_D1F1EN_MSK                         (0x00000004)
  #define UNCORE_CR_DEVEN_0_0_0_PCI_D1F1EN_MAX                         (0x00000001)
  #define UNCORE_CR_DEVEN_0_0_0_PCI_D1F1EN_DEF                         (0x00000001)
  #define UNCORE_CR_DEVEN_0_0_0_PCI_D1F0EN_OFF                         ( 3)
  #define UNCORE_CR_DEVEN_0_0_0_PCI_D1F0EN_WID                         ( 1)
  #define UNCORE_CR_DEVEN_0_0_0_PCI_D1F0EN_MSK                         (0x00000008)
  #define UNCORE_CR_DEVEN_0_0_0_PCI_D1F0EN_MAX                         (0x00000001)
  #define UNCORE_CR_DEVEN_0_0_0_PCI_D1F0EN_DEF                         (0x00000001)
  #define UNCORE_CR_DEVEN_0_0_0_PCI_D2EN_OFF                           ( 4)
  #define UNCORE_CR_DEVEN_0_0_0_PCI_D2EN_WID                           ( 1)
  #define UNCORE_CR_DEVEN_0_0_0_PCI_D2EN_MSK                           (0x00000010)
  #define UNCORE_CR_DEVEN_0_0_0_PCI_D2EN_MAX                           (0x00000001)
  #define UNCORE_CR_DEVEN_0_0_0_PCI_D2EN_DEF                           (0x00000001)
  #define UNCORE_CR_DEVEN_0_0_0_PCI_D3EN_OFF                           ( 5)
  #define UNCORE_CR_DEVEN_0_0_0_PCI_D3EN_WID                           ( 1)
  #define UNCORE_CR_DEVEN_0_0_0_PCI_D3EN_MSK                           (0x00000020)
  #define UNCORE_CR_DEVEN_0_0_0_PCI_D3EN_MAX                           (0x00000001)
  #define UNCORE_CR_DEVEN_0_0_0_PCI_D3EN_DEF                           (0x00000001)
  #define UNCORE_CR_DEVEN_0_0_0_PCI_D4EN_OFF                           ( 7)
  #define UNCORE_CR_DEVEN_0_0_0_PCI_D4EN_WID                           ( 1)
  #define UNCORE_CR_DEVEN_0_0_0_PCI_D4EN_MSK                           (0x00000080)
  #define UNCORE_CR_DEVEN_0_0_0_PCI_D4EN_MAX                           (0x00000001)
  #define UNCORE_CR_DEVEN_0_0_0_PCI_D4EN_DEF                           (0x00000001)
  #define UNCORE_CR_DEVEN_0_0_0_PCI_D5EN_OFF                           (10)
  #define UNCORE_CR_DEVEN_0_0_0_PCI_D5EN_WID                           ( 1)
  #define UNCORE_CR_DEVEN_0_0_0_PCI_D5EN_MSK                           (0x00000400)
  #define UNCORE_CR_DEVEN_0_0_0_PCI_D5EN_MAX                           (0x00000001)
  #define UNCORE_CR_DEVEN_0_0_0_PCI_D5EN_DEF                           (0x00000001)
  #define UNCORE_CR_DEVEN_0_0_0_PCI_D6EN_OFF                           (13)
  #define UNCORE_CR_DEVEN_0_0_0_PCI_D6EN_WID                           ( 1)
  #define UNCORE_CR_DEVEN_0_0_0_PCI_D6EN_MSK                           (0x00002000)
  #define UNCORE_CR_DEVEN_0_0_0_PCI_D6EN_MAX                           (0x00000001)
  #define UNCORE_CR_DEVEN_0_0_0_PCI_D6EN_DEF                           (0x00000000)
  #define UNCORE_CR_DEVEN_0_0_0_PCI_D7EN_OFF                           (14)
  #define UNCORE_CR_DEVEN_0_0_0_PCI_D7EN_WID                           ( 1)
  #define UNCORE_CR_DEVEN_0_0_0_PCI_D7EN_MSK                           (0x00004000)
  #define UNCORE_CR_DEVEN_0_0_0_PCI_D7EN_MAX                           (0x00000001)
  #define UNCORE_CR_DEVEN_0_0_0_PCI_D7EN_DEF                           (0x00000000)
  #define UNCORE_CR_DEVEN_0_0_0_PCI_D8EN_OFF                           (15)
  #define UNCORE_CR_DEVEN_0_0_0_PCI_D8EN_WID                           ( 1)
  #define UNCORE_CR_DEVEN_0_0_0_PCI_D8EN_MSK                           (0x00008000)
  #define UNCORE_CR_DEVEN_0_0_0_PCI_D8EN_MAX                           (0x00000001)
  #define UNCORE_CR_DEVEN_0_0_0_PCI_D8EN_DEF                           (0x00000001)

#define UNCORE_CR_PAVPC_0_0_0_PCI_REG                                (0x00000058)
  #define UNCORE_CR_PAVPC_0_0_0_PCI_PCME_OFF                           ( 0)
  #define UNCORE_CR_PAVPC_0_0_0_PCI_PCME_WID                           ( 1)
  #define UNCORE_CR_PAVPC_0_0_0_PCI_PCME_MSK                           (0x00000001)
  #define UNCORE_CR_PAVPC_0_0_0_PCI_PCME_MAX                           (0x00000001)
  #define UNCORE_CR_PAVPC_0_0_0_PCI_PCME_DEF                           (0x00000000)
  #define UNCORE_CR_PAVPC_0_0_0_PCI_PAVPE_OFF                          ( 1)
  #define UNCORE_CR_PAVPC_0_0_0_PCI_PAVPE_WID                          ( 1)
  #define UNCORE_CR_PAVPC_0_0_0_PCI_PAVPE_MSK                          (0x00000002)
  #define UNCORE_CR_PAVPC_0_0_0_PCI_PAVPE_MAX                          (0x00000001)
  #define UNCORE_CR_PAVPC_0_0_0_PCI_PAVPE_DEF                          (0x00000000)
  #define UNCORE_CR_PAVPC_0_0_0_PCI_PAVPLCK_OFF                        ( 2)
  #define UNCORE_CR_PAVPC_0_0_0_PCI_PAVPLCK_WID                        ( 1)
  #define UNCORE_CR_PAVPC_0_0_0_PCI_PAVPLCK_MSK                        (0x00000004)
  #define UNCORE_CR_PAVPC_0_0_0_PCI_PAVPLCK_MAX                        (0x00000001)
  #define UNCORE_CR_PAVPC_0_0_0_PCI_PAVPLCK_DEF                        (0x00000000)
  #define UNCORE_CR_PAVPC_0_0_0_PCI_HVYMODSEL_OFF                      ( 3)
  #define UNCORE_CR_PAVPC_0_0_0_PCI_HVYMODSEL_WID                      ( 1)
  #define UNCORE_CR_PAVPC_0_0_0_PCI_HVYMODSEL_MSK                      (0x00000008)
  #define UNCORE_CR_PAVPC_0_0_0_PCI_HVYMODSEL_MAX                      (0x00000001)
  #define UNCORE_CR_PAVPC_0_0_0_PCI_HVYMODSEL_DEF                      (0x00000000)
  #define UNCORE_CR_PAVPC_0_0_0_PCI_OVTATTACK_OFF                      ( 4)
  #define UNCORE_CR_PAVPC_0_0_0_PCI_OVTATTACK_WID                      ( 1)
  #define UNCORE_CR_PAVPC_0_0_0_PCI_OVTATTACK_MSK                      (0x00000010)
  #define UNCORE_CR_PAVPC_0_0_0_PCI_OVTATTACK_MAX                      (0x00000001)
  #define UNCORE_CR_PAVPC_0_0_0_PCI_OVTATTACK_DEF                      (0x00000000)
  #define UNCORE_CR_PAVPC_0_0_0_PCI_RSVD1_OFF                          ( 5)
  #define UNCORE_CR_PAVPC_0_0_0_PCI_RSVD1_WID                          ( 1)
  #define UNCORE_CR_PAVPC_0_0_0_PCI_RSVD1_MSK                          (0x00000020)
  #define UNCORE_CR_PAVPC_0_0_0_PCI_RSVD1_MAX                          (0x00000001)
  #define UNCORE_CR_PAVPC_0_0_0_PCI_RSVD1_DEF                          (0x00000000)
  #define UNCORE_CR_PAVPC_0_0_0_PCI_ASMFEN_OFF                         ( 6)
  #define UNCORE_CR_PAVPC_0_0_0_PCI_ASMFEN_WID                         ( 1)
  #define UNCORE_CR_PAVPC_0_0_0_PCI_ASMFEN_MSK                         (0x00000040)
  #define UNCORE_CR_PAVPC_0_0_0_PCI_ASMFEN_MAX                         (0x00000001)
  #define UNCORE_CR_PAVPC_0_0_0_PCI_ASMFEN_DEF                         (0x00000000)
  #define UNCORE_CR_PAVPC_0_0_0_PCI_RSVD2_OFF                          ( 7)
  #define UNCORE_CR_PAVPC_0_0_0_PCI_RSVD2_WID                          (13)
  #define UNCORE_CR_PAVPC_0_0_0_PCI_RSVD2_MSK                          (0x000FFF80)
  #define UNCORE_CR_PAVPC_0_0_0_PCI_RSVD2_MAX                          (0x00001FFF)
  #define UNCORE_CR_PAVPC_0_0_0_PCI_RSVD2_DEF                          (0x00000000)
  #define UNCORE_CR_PAVPC_0_0_0_PCI_PCMBASE_OFF                        (20)
  #define UNCORE_CR_PAVPC_0_0_0_PCI_PCMBASE_WID                        (12)
  #define UNCORE_CR_PAVPC_0_0_0_PCI_PCMBASE_MSK                        (0xFFF00000)
  #define UNCORE_CR_PAVPC_0_0_0_PCI_PCMBASE_MAX                        (0x00000FFF)
  #define UNCORE_CR_PAVPC_0_0_0_PCI_PCMBASE_DEF                        (0x00000000)

#define UNCORE_CR_DPR_0_0_0_PCI_REG                                  (0x0000005C)
  #define UNCORE_CR_DPR_0_0_0_PCI_LOCK_OFF                             ( 0)
  #define UNCORE_CR_DPR_0_0_0_PCI_LOCK_WID                             ( 1)
  #define UNCORE_CR_DPR_0_0_0_PCI_LOCK_MSK                             (0x00000001)
  #define UNCORE_CR_DPR_0_0_0_PCI_LOCK_MAX                             (0x00000001)
  #define UNCORE_CR_DPR_0_0_0_PCI_LOCK_DEF                             (0x00000000)
  #define UNCORE_CR_DPR_0_0_0_PCI_PRS_OFF                              ( 1)
  #define UNCORE_CR_DPR_0_0_0_PCI_PRS_WID                              ( 1)
  #define UNCORE_CR_DPR_0_0_0_PCI_PRS_MSK                              (0x00000002)
  #define UNCORE_CR_DPR_0_0_0_PCI_PRS_MAX                              (0x00000001)
  #define UNCORE_CR_DPR_0_0_0_PCI_PRS_DEF                              (0x00000000)
  #define UNCORE_CR_DPR_0_0_0_PCI_EPM_OFF                              ( 2)
  #define UNCORE_CR_DPR_0_0_0_PCI_EPM_WID                              ( 1)
  #define UNCORE_CR_DPR_0_0_0_PCI_EPM_MSK                              (0x00000004)
  #define UNCORE_CR_DPR_0_0_0_PCI_EPM_MAX                              (0x00000001)
  #define UNCORE_CR_DPR_0_0_0_PCI_EPM_DEF                              (0x00000000)
  #define UNCORE_CR_DPR_0_0_0_PCI_DPRSIZE_OFF                          ( 4)
  #define UNCORE_CR_DPR_0_0_0_PCI_DPRSIZE_WID                          ( 8)
  #define UNCORE_CR_DPR_0_0_0_PCI_DPRSIZE_MSK                          (0x00000FF0)
  #define UNCORE_CR_DPR_0_0_0_PCI_DPRSIZE_MAX                          (0x000000FF)
  #define UNCORE_CR_DPR_0_0_0_PCI_DPRSIZE_DEF                          (0x00000000)
  #define UNCORE_CR_DPR_0_0_0_PCI_TopOfDPR_OFF                         (20)
  #define UNCORE_CR_DPR_0_0_0_PCI_TopOfDPR_WID                         (12)
  #define UNCORE_CR_DPR_0_0_0_PCI_TopOfDPR_MSK                         (0xFFF00000)
  #define UNCORE_CR_DPR_0_0_0_PCI_TopOfDPR_MAX                         (0x00000FFF)
  #define UNCORE_CR_DPR_0_0_0_PCI_TopOfDPR_DEF                         (0x00000000)

#define UNCORE_CR_PCIEXBAR_0_0_0_PCI_REG                             (0x00000060)
  #define UNCORE_CR_PCIEXBAR_0_0_0_PCI_PCIEXBAREN_OFF                  ( 0)
  #define UNCORE_CR_PCIEXBAR_0_0_0_PCI_PCIEXBAREN_WID                  ( 1)
  #define UNCORE_CR_PCIEXBAR_0_0_0_PCI_PCIEXBAREN_MSK                  (0x00000001)
  #define UNCORE_CR_PCIEXBAR_0_0_0_PCI_PCIEXBAREN_MAX                  (0x00000001)
  #define UNCORE_CR_PCIEXBAR_0_0_0_PCI_PCIEXBAREN_DEF                  (0x00000000)
  #define UNCORE_CR_PCIEXBAR_0_0_0_PCI_LENGTH_OFF                      ( 1)
  #define UNCORE_CR_PCIEXBAR_0_0_0_PCI_LENGTH_WID                      ( 2)
  #define UNCORE_CR_PCIEXBAR_0_0_0_PCI_LENGTH_MSK                      (0x00000006)
  #define UNCORE_CR_PCIEXBAR_0_0_0_PCI_LENGTH_MAX                      (0x00000003)
  #define UNCORE_CR_PCIEXBAR_0_0_0_PCI_LENGTH_DEF                      (0x00000000)
  #define UNCORE_CR_PCIEXBAR_0_0_0_PCI_ADMSK64_OFF                     (26)
  #define UNCORE_CR_PCIEXBAR_0_0_0_PCI_ADMSK64_WID                     ( 1)
  #define UNCORE_CR_PCIEXBAR_0_0_0_PCI_ADMSK64_MSK                     (0x04000000)
  #define UNCORE_CR_PCIEXBAR_0_0_0_PCI_ADMSK64_MAX                     (0x00000001)
  #define UNCORE_CR_PCIEXBAR_0_0_0_PCI_ADMSK64_DEF                     (0x00000000)
  #define UNCORE_CR_PCIEXBAR_0_0_0_PCI_ADMSK128_OFF                    (27)
  #define UNCORE_CR_PCIEXBAR_0_0_0_PCI_ADMSK128_WID                    ( 1)
  #define UNCORE_CR_PCIEXBAR_0_0_0_PCI_ADMSK128_MSK                    (0x08000000)
  #define UNCORE_CR_PCIEXBAR_0_0_0_PCI_ADMSK128_MAX                    (0x00000001)
  #define UNCORE_CR_PCIEXBAR_0_0_0_PCI_ADMSK128_DEF                    (0x00000000)
  #define UNCORE_CR_PCIEXBAR_0_0_0_PCI_PCIEXBAR_OFF                    (28)
  #define UNCORE_CR_PCIEXBAR_0_0_0_PCI_PCIEXBAR_WID                    (11)
  #define UNCORE_CR_PCIEXBAR_0_0_0_PCI_PCIEXBAR_MSK                    (0x7FF0000000)
  #define UNCORE_CR_PCIEXBAR_0_0_0_PCI_PCIEXBAR_MAX                    (0x000007FF)
  #define UNCORE_CR_PCIEXBAR_0_0_0_PCI_PCIEXBAR_DEF                    (0x00000000)

#define UNCORE_CR_DMIBAR_0_0_0_PCI_REG                               (0x00000068)
  #define UNCORE_CR_DMIBAR_0_0_0_PCI_DMIBAREN_OFF                      ( 0)
  #define UNCORE_CR_DMIBAR_0_0_0_PCI_DMIBAREN_WID                      ( 1)
  #define UNCORE_CR_DMIBAR_0_0_0_PCI_DMIBAREN_MSK                      (0x00000001)
  #define UNCORE_CR_DMIBAR_0_0_0_PCI_DMIBAREN_MAX                      (0x00000001)
  #define UNCORE_CR_DMIBAR_0_0_0_PCI_DMIBAREN_DEF                      (0x00000000)
  #define UNCORE_CR_DMIBAR_0_0_0_PCI_DMIBAR_OFF                        (12)
  #define UNCORE_CR_DMIBAR_0_0_0_PCI_DMIBAR_WID                        (27)
  #define UNCORE_CR_DMIBAR_0_0_0_PCI_DMIBAR_MSK                        (0x7FFFFFF000)
  #define UNCORE_CR_DMIBAR_0_0_0_PCI_DMIBAR_MAX                        (0x07FFFFFF)
  #define UNCORE_CR_DMIBAR_0_0_0_PCI_DMIBAR_DEF                        (0x00000000)

#define UNCORE_CR_MESEG_BASE_0_0_0_PCI_REG                           (0x00000070)
  #define UNCORE_CR_MESEG_BASE_0_0_0_PCI_MEBASE_OFF                    (20)
  #define UNCORE_CR_MESEG_BASE_0_0_0_PCI_MEBASE_WID                    (19)
  #define UNCORE_CR_MESEG_BASE_0_0_0_PCI_MEBASE_MSK                    (0x7FFFF00000)
  #define UNCORE_CR_MESEG_BASE_0_0_0_PCI_MEBASE_MAX                    (0x0007FFFF)
  #define UNCORE_CR_MESEG_BASE_0_0_0_PCI_MEBASE_DEF                    (0x0007FFFF)

#define UNCORE_CR_MESEG_MASK_0_0_0_PCI_REG                           (0x00000078)
  #define UNCORE_CR_MESEG_MASK_0_0_0_PCI_MELCK_OFF                     (10)
  #define UNCORE_CR_MESEG_MASK_0_0_0_PCI_MELCK_WID                     ( 1)
  #define UNCORE_CR_MESEG_MASK_0_0_0_PCI_MELCK_MSK                     (0x00000400)
  #define UNCORE_CR_MESEG_MASK_0_0_0_PCI_MELCK_MAX                     (0x00000001)
  #define UNCORE_CR_MESEG_MASK_0_0_0_PCI_MELCK_DEF                     (0x00000000)
  #define UNCORE_CR_MESEG_MASK_0_0_0_PCI_ME_STLEN_EN_OFF               (11)
  #define UNCORE_CR_MESEG_MASK_0_0_0_PCI_ME_STLEN_EN_WID               ( 1)
  #define UNCORE_CR_MESEG_MASK_0_0_0_PCI_ME_STLEN_EN_MSK               (0x00000800)
  #define UNCORE_CR_MESEG_MASK_0_0_0_PCI_ME_STLEN_EN_MAX               (0x00000001)
  #define UNCORE_CR_MESEG_MASK_0_0_0_PCI_ME_STLEN_EN_DEF               (0x00000000)
  #define UNCORE_CR_MESEG_MASK_0_0_0_PCI_MEMASK_OFF                    (20)
  #define UNCORE_CR_MESEG_MASK_0_0_0_PCI_MEMASK_WID                    (19)
  #define UNCORE_CR_MESEG_MASK_0_0_0_PCI_MEMASK_MSK                    (0x7FFFF00000)
  #define UNCORE_CR_MESEG_MASK_0_0_0_PCI_MEMASK_MAX                    (0x0007FFFF)
  #define UNCORE_CR_MESEG_MASK_0_0_0_PCI_MEMASK_DEF                    (0x00000000)

#define UNCORE_CR_PAM0_0_0_0_PCI_REG                                 (0x00000080)
  #define UNCORE_CR_PAM0_0_0_0_PCI_Lock_OFF                            ( 0)
  #define UNCORE_CR_PAM0_0_0_0_PCI_Lock_WID                            ( 1)
  #define UNCORE_CR_PAM0_0_0_0_PCI_Lock_MSK                            (0x00000001)
  #define UNCORE_CR_PAM0_0_0_0_PCI_Lock_MAX                            (0x00000001)
  #define UNCORE_CR_PAM0_0_0_0_PCI_Lock_DEF                            (0x00000000)
  #define UNCORE_CR_PAM0_0_0_0_PCI_HIENABLE_OFF                        ( 4)
  #define UNCORE_CR_PAM0_0_0_0_PCI_HIENABLE_WID                        ( 2)
  #define UNCORE_CR_PAM0_0_0_0_PCI_HIENABLE_MSK                        (0x00000030)
  #define UNCORE_CR_PAM0_0_0_0_PCI_HIENABLE_MAX                        (0x00000003)
  #define UNCORE_CR_PAM0_0_0_0_PCI_HIENABLE_DEF                        (0x00000000)

#define UNCORE_CR_PAM1_0_0_0_PCI_REG                                 (0x00000081)
  #define UNCORE_CR_PAM1_0_0_0_PCI_LOENABLE_OFF                        ( 0)
  #define UNCORE_CR_PAM1_0_0_0_PCI_LOENABLE_WID                        ( 2)
  #define UNCORE_CR_PAM1_0_0_0_PCI_LOENABLE_MSK                        (0x00000003)
  #define UNCORE_CR_PAM1_0_0_0_PCI_LOENABLE_MAX                        (0x00000003)
  #define UNCORE_CR_PAM1_0_0_0_PCI_LOENABLE_DEF                        (0x00000000)
  #define UNCORE_CR_PAM1_0_0_0_PCI_HIENABLE_OFF                        ( 4)
  #define UNCORE_CR_PAM1_0_0_0_PCI_HIENABLE_WID                        ( 2)
  #define UNCORE_CR_PAM1_0_0_0_PCI_HIENABLE_MSK                        (0x00000030)
  #define UNCORE_CR_PAM1_0_0_0_PCI_HIENABLE_MAX                        (0x00000003)
  #define UNCORE_CR_PAM1_0_0_0_PCI_HIENABLE_DEF                        (0x00000000)

#define UNCORE_CR_PAM2_0_0_0_PCI_REG                                 (0x00000082)
  #define UNCORE_CR_PAM2_0_0_0_PCI_LOENABLE_OFF                        ( 0)
  #define UNCORE_CR_PAM2_0_0_0_PCI_LOENABLE_WID                        ( 2)
  #define UNCORE_CR_PAM2_0_0_0_PCI_LOENABLE_MSK                        (0x00000003)
  #define UNCORE_CR_PAM2_0_0_0_PCI_LOENABLE_MAX                        (0x00000003)
  #define UNCORE_CR_PAM2_0_0_0_PCI_LOENABLE_DEF                        (0x00000000)
  #define UNCORE_CR_PAM2_0_0_0_PCI_HIENABLE_OFF                        ( 4)
  #define UNCORE_CR_PAM2_0_0_0_PCI_HIENABLE_WID                        ( 2)
  #define UNCORE_CR_PAM2_0_0_0_PCI_HIENABLE_MSK                        (0x00000030)
  #define UNCORE_CR_PAM2_0_0_0_PCI_HIENABLE_MAX                        (0x00000003)
  #define UNCORE_CR_PAM2_0_0_0_PCI_HIENABLE_DEF                        (0x00000000)

#define UNCORE_CR_PAM3_0_0_0_PCI_REG                                 (0x00000083)
  #define UNCORE_CR_PAM3_0_0_0_PCI_LOENABLE_OFF                        ( 0)
  #define UNCORE_CR_PAM3_0_0_0_PCI_LOENABLE_WID                        ( 2)
  #define UNCORE_CR_PAM3_0_0_0_PCI_LOENABLE_MSK                        (0x00000003)
  #define UNCORE_CR_PAM3_0_0_0_PCI_LOENABLE_MAX                        (0x00000003)
  #define UNCORE_CR_PAM3_0_0_0_PCI_LOENABLE_DEF                        (0x00000000)
  #define UNCORE_CR_PAM3_0_0_0_PCI_HIENABLE_OFF                        ( 4)
  #define UNCORE_CR_PAM3_0_0_0_PCI_HIENABLE_WID                        ( 2)
  #define UNCORE_CR_PAM3_0_0_0_PCI_HIENABLE_MSK                        (0x00000030)
  #define UNCORE_CR_PAM3_0_0_0_PCI_HIENABLE_MAX                        (0x00000003)
  #define UNCORE_CR_PAM3_0_0_0_PCI_HIENABLE_DEF                        (0x00000000)

#define UNCORE_CR_PAM4_0_0_0_PCI_REG                                 (0x00000084)
  #define UNCORE_CR_PAM4_0_0_0_PCI_LOENABLE_OFF                        ( 0)
  #define UNCORE_CR_PAM4_0_0_0_PCI_LOENABLE_WID                        ( 2)
  #define UNCORE_CR_PAM4_0_0_0_PCI_LOENABLE_MSK                        (0x00000003)
  #define UNCORE_CR_PAM4_0_0_0_PCI_LOENABLE_MAX                        (0x00000003)
  #define UNCORE_CR_PAM4_0_0_0_PCI_LOENABLE_DEF                        (0x00000000)
  #define UNCORE_CR_PAM4_0_0_0_PCI_HIENABLE_OFF                        ( 4)
  #define UNCORE_CR_PAM4_0_0_0_PCI_HIENABLE_WID                        ( 2)
  #define UNCORE_CR_PAM4_0_0_0_PCI_HIENABLE_MSK                        (0x00000030)
  #define UNCORE_CR_PAM4_0_0_0_PCI_HIENABLE_MAX                        (0x00000003)
  #define UNCORE_CR_PAM4_0_0_0_PCI_HIENABLE_DEF                        (0x00000000)

#define UNCORE_CR_PAM5_0_0_0_PCI_REG                                 (0x00000085)
  #define UNCORE_CR_PAM5_0_0_0_PCI_LOENABLE_OFF                        ( 0)
  #define UNCORE_CR_PAM5_0_0_0_PCI_LOENABLE_WID                        ( 2)
  #define UNCORE_CR_PAM5_0_0_0_PCI_LOENABLE_MSK                        (0x00000003)
  #define UNCORE_CR_PAM5_0_0_0_PCI_LOENABLE_MAX                        (0x00000003)
  #define UNCORE_CR_PAM5_0_0_0_PCI_LOENABLE_DEF                        (0x00000000)
  #define UNCORE_CR_PAM5_0_0_0_PCI_HIENABLE_OFF                        ( 4)
  #define UNCORE_CR_PAM5_0_0_0_PCI_HIENABLE_WID                        ( 2)
  #define UNCORE_CR_PAM5_0_0_0_PCI_HIENABLE_MSK                        (0x00000030)
  #define UNCORE_CR_PAM5_0_0_0_PCI_HIENABLE_MAX                        (0x00000003)
  #define UNCORE_CR_PAM5_0_0_0_PCI_HIENABLE_DEF                        (0x00000000)

#define UNCORE_CR_PAM6_0_0_0_PCI_REG                                 (0x00000086)
  #define UNCORE_CR_PAM6_0_0_0_PCI_LOENABLE_OFF                        ( 0)
  #define UNCORE_CR_PAM6_0_0_0_PCI_LOENABLE_WID                        ( 2)
  #define UNCORE_CR_PAM6_0_0_0_PCI_LOENABLE_MSK                        (0x00000003)
  #define UNCORE_CR_PAM6_0_0_0_PCI_LOENABLE_MAX                        (0x00000003)
  #define UNCORE_CR_PAM6_0_0_0_PCI_LOENABLE_DEF                        (0x00000000)
  #define UNCORE_CR_PAM6_0_0_0_PCI_HIENABLE_OFF                        ( 4)
  #define UNCORE_CR_PAM6_0_0_0_PCI_HIENABLE_WID                        ( 2)
  #define UNCORE_CR_PAM6_0_0_0_PCI_HIENABLE_MSK                        (0x00000030)
  #define UNCORE_CR_PAM6_0_0_0_PCI_HIENABLE_MAX                        (0x00000003)
  #define UNCORE_CR_PAM6_0_0_0_PCI_HIENABLE_DEF                        (0x00000000)

#define UNCORE_CR_LAC_0_0_0_PCI_REG                                  (0x00000087)
  #define UNCORE_CR_LAC_0_0_0_PCI_MDAP10_OFF                           ( 0)
  #define UNCORE_CR_LAC_0_0_0_PCI_MDAP10_WID                           ( 1)
  #define UNCORE_CR_LAC_0_0_0_PCI_MDAP10_MSK                           (0x00000001)
  #define UNCORE_CR_LAC_0_0_0_PCI_MDAP10_MAX                           (0x00000001)
  #define UNCORE_CR_LAC_0_0_0_PCI_MDAP10_DEF                           (0x00000000)
  #define UNCORE_CR_LAC_0_0_0_PCI_MDAP11_OFF                           ( 1)
  #define UNCORE_CR_LAC_0_0_0_PCI_MDAP11_WID                           ( 1)
  #define UNCORE_CR_LAC_0_0_0_PCI_MDAP11_MSK                           (0x00000002)
  #define UNCORE_CR_LAC_0_0_0_PCI_MDAP11_MAX                           (0x00000001)
  #define UNCORE_CR_LAC_0_0_0_PCI_MDAP11_DEF                           (0x00000000)
  #define UNCORE_CR_LAC_0_0_0_PCI_MDAP12_OFF                           ( 2)
  #define UNCORE_CR_LAC_0_0_0_PCI_MDAP12_WID                           ( 1)
  #define UNCORE_CR_LAC_0_0_0_PCI_MDAP12_MSK                           (0x00000004)
  #define UNCORE_CR_LAC_0_0_0_PCI_MDAP12_MAX                           (0x00000001)
  #define UNCORE_CR_LAC_0_0_0_PCI_MDAP12_DEF                           (0x00000000)
  #define UNCORE_CR_LAC_0_0_0_PCI_MDAP60_OFF                           ( 3)
  #define UNCORE_CR_LAC_0_0_0_PCI_MDAP60_WID                           ( 1)
  #define UNCORE_CR_LAC_0_0_0_PCI_MDAP60_MSK                           (0x00000008)
  #define UNCORE_CR_LAC_0_0_0_PCI_MDAP60_MAX                           (0x00000001)
  #define UNCORE_CR_LAC_0_0_0_PCI_MDAP60_DEF                           (0x00000000)
  #define UNCORE_CR_LAC_0_0_0_PCI_HEN_OFF                              ( 7)
  #define UNCORE_CR_LAC_0_0_0_PCI_HEN_WID                              ( 1)
  #define UNCORE_CR_LAC_0_0_0_PCI_HEN_MSK                              (0x00000080)
  #define UNCORE_CR_LAC_0_0_0_PCI_HEN_MAX                              (0x00000001)
  #define UNCORE_CR_LAC_0_0_0_PCI_HEN_DEF                              (0x00000000)

#define UNCORE_CR_SMRAMC_0_0_0_PCI_REG                               (0x00000088)
  #define UNCORE_CR_SMRAMC_0_0_0_PCI_C_BASE_SEG_OFF                    ( 0)
  #define UNCORE_CR_SMRAMC_0_0_0_PCI_C_BASE_SEG_WID                    ( 3)
  #define UNCORE_CR_SMRAMC_0_0_0_PCI_C_BASE_SEG_MSK                    (0x00000007)
  #define UNCORE_CR_SMRAMC_0_0_0_PCI_C_BASE_SEG_MAX                    (0x00000007)
  #define UNCORE_CR_SMRAMC_0_0_0_PCI_C_BASE_SEG_DEF                    (0x00000002)
  #define UNCORE_CR_SMRAMC_0_0_0_PCI_G_SMRAME_OFF                      ( 3)
  #define UNCORE_CR_SMRAMC_0_0_0_PCI_G_SMRAME_WID                      ( 1)
  #define UNCORE_CR_SMRAMC_0_0_0_PCI_G_SMRAME_MSK                      (0x00000008)
  #define UNCORE_CR_SMRAMC_0_0_0_PCI_G_SMRAME_MAX                      (0x00000001)
  #define UNCORE_CR_SMRAMC_0_0_0_PCI_G_SMRAME_DEF                      (0x00000000)
  #define UNCORE_CR_SMRAMC_0_0_0_PCI_D_LCK_OFF                         ( 4)
  #define UNCORE_CR_SMRAMC_0_0_0_PCI_D_LCK_WID                         ( 1)
  #define UNCORE_CR_SMRAMC_0_0_0_PCI_D_LCK_MSK                         (0x00000010)
  #define UNCORE_CR_SMRAMC_0_0_0_PCI_D_LCK_MAX                         (0x00000001)
  #define UNCORE_CR_SMRAMC_0_0_0_PCI_D_LCK_DEF                         (0x00000000)
  #define UNCORE_CR_SMRAMC_0_0_0_PCI_D_CLS_OFF                         ( 5)
  #define UNCORE_CR_SMRAMC_0_0_0_PCI_D_CLS_WID                         ( 1)
  #define UNCORE_CR_SMRAMC_0_0_0_PCI_D_CLS_MSK                         (0x00000020)
  #define UNCORE_CR_SMRAMC_0_0_0_PCI_D_CLS_MAX                         (0x00000001)
  #define UNCORE_CR_SMRAMC_0_0_0_PCI_D_CLS_DEF                         (0x00000000)
  #define UNCORE_CR_SMRAMC_0_0_0_PCI_D_OPEN_OFF                        ( 6)
  #define UNCORE_CR_SMRAMC_0_0_0_PCI_D_OPEN_WID                        ( 1)
  #define UNCORE_CR_SMRAMC_0_0_0_PCI_D_OPEN_MSK                        (0x00000040)
  #define UNCORE_CR_SMRAMC_0_0_0_PCI_D_OPEN_MAX                        (0x00000001)
  #define UNCORE_CR_SMRAMC_0_0_0_PCI_D_OPEN_DEF                        (0x00000000)

#define UNCORE_CR_REMAPBASE_0_0_0_PCI_REG                            (0x00000090)
  #define UNCORE_CR_REMAPBASE_0_0_0_PCI_LOCK_OFF                       ( 0)
  #define UNCORE_CR_REMAPBASE_0_0_0_PCI_LOCK_WID                       ( 1)
  #define UNCORE_CR_REMAPBASE_0_0_0_PCI_LOCK_MSK                       (0x00000001)
  #define UNCORE_CR_REMAPBASE_0_0_0_PCI_LOCK_MAX                       (0x00000001)
  #define UNCORE_CR_REMAPBASE_0_0_0_PCI_LOCK_DEF                       (0x00000000)
  #define UNCORE_CR_REMAPBASE_0_0_0_PCI_REMAPBASE_OFF                  (20)
  #define UNCORE_CR_REMAPBASE_0_0_0_PCI_REMAPBASE_WID                  (19)
  #define UNCORE_CR_REMAPBASE_0_0_0_PCI_REMAPBASE_MSK                  (0x7FFFF00000)
  #define UNCORE_CR_REMAPBASE_0_0_0_PCI_REMAPBASE_MAX                  (0x0007FFFF)
  #define UNCORE_CR_REMAPBASE_0_0_0_PCI_REMAPBASE_DEF                  (0x0007FFFF)

#define UNCORE_CR_REMAPLIMIT_0_0_0_PCI_REG                           (0x00000098)
  #define UNCORE_CR_REMAPLIMIT_0_0_0_PCI_LOCK_OFF                      ( 0)
  #define UNCORE_CR_REMAPLIMIT_0_0_0_PCI_LOCK_WID                      ( 1)
  #define UNCORE_CR_REMAPLIMIT_0_0_0_PCI_LOCK_MSK                      (0x00000001)
  #define UNCORE_CR_REMAPLIMIT_0_0_0_PCI_LOCK_MAX                      (0x00000001)
  #define UNCORE_CR_REMAPLIMIT_0_0_0_PCI_LOCK_DEF                      (0x00000000)
  #define UNCORE_CR_REMAPLIMIT_0_0_0_PCI_REMAPLMT_OFF                  (20)
  #define UNCORE_CR_REMAPLIMIT_0_0_0_PCI_REMAPLMT_WID                  (19)
  #define UNCORE_CR_REMAPLIMIT_0_0_0_PCI_REMAPLMT_MSK                  (0x7FFFF00000)
  #define UNCORE_CR_REMAPLIMIT_0_0_0_PCI_REMAPLMT_MAX                  (0x0007FFFF)
  #define UNCORE_CR_REMAPLIMIT_0_0_0_PCI_REMAPLMT_DEF                  (0x00000000)

#define UNCORE_CR_TOM_0_0_0_PCI_REG                                  (0x000000A0)
  #define UNCORE_CR_TOM_0_0_0_PCI_LOCK_OFF                             ( 0)
  #define UNCORE_CR_TOM_0_0_0_PCI_LOCK_WID                             ( 1)
  #define UNCORE_CR_TOM_0_0_0_PCI_LOCK_MSK                             (0x00000001)
  #define UNCORE_CR_TOM_0_0_0_PCI_LOCK_MAX                             (0x00000001)
  #define UNCORE_CR_TOM_0_0_0_PCI_LOCK_DEF                             (0x00000000)
  #define UNCORE_CR_TOM_0_0_0_PCI_TOM_OFF                              (20)
  #define UNCORE_CR_TOM_0_0_0_PCI_TOM_WID                              (19)
  #define UNCORE_CR_TOM_0_0_0_PCI_TOM_MSK                              (0x7FFFF00000)
  #define UNCORE_CR_TOM_0_0_0_PCI_TOM_MAX                              (0x0007FFFF)
  #define UNCORE_CR_TOM_0_0_0_PCI_TOM_DEF                              (0x0007FFFF)

#define UNCORE_CR_TOUUD_0_0_0_PCI_REG                                (0x000000A8)
  #define UNCORE_CR_TOUUD_0_0_0_PCI_LOCK_OFF                           ( 0)
  #define UNCORE_CR_TOUUD_0_0_0_PCI_LOCK_WID                           ( 1)
  #define UNCORE_CR_TOUUD_0_0_0_PCI_LOCK_MSK                           (0x00000001)
  #define UNCORE_CR_TOUUD_0_0_0_PCI_LOCK_MAX                           (0x00000001)
  #define UNCORE_CR_TOUUD_0_0_0_PCI_LOCK_DEF                           (0x00000000)
  #define UNCORE_CR_TOUUD_0_0_0_PCI_TOUUD_OFF                          (20)
  #define UNCORE_CR_TOUUD_0_0_0_PCI_TOUUD_WID                          (19)
  #define UNCORE_CR_TOUUD_0_0_0_PCI_TOUUD_MSK                          (0x7FFFF00000)
  #define UNCORE_CR_TOUUD_0_0_0_PCI_TOUUD_MAX                          (0x0007FFFF)
  #define UNCORE_CR_TOUUD_0_0_0_PCI_TOUUD_DEF                          (0x00000000)

#define UNCORE_CR_BDSM_0_0_0_PCI_REG                                 (0x000000B0)
  #define UNCORE_CR_BDSM_0_0_0_PCI_LOCK_OFF                            ( 0)
  #define UNCORE_CR_BDSM_0_0_0_PCI_LOCK_WID                            ( 1)
  #define UNCORE_CR_BDSM_0_0_0_PCI_LOCK_MSK                            (0x00000001)
  #define UNCORE_CR_BDSM_0_0_0_PCI_LOCK_MAX                            (0x00000001)
  #define UNCORE_CR_BDSM_0_0_0_PCI_LOCK_DEF                            (0x00000000)
  #define UNCORE_CR_BDSM_0_0_0_PCI_BDSM_OFF                            (20)
  #define UNCORE_CR_BDSM_0_0_0_PCI_BDSM_WID                            (12)
  #define UNCORE_CR_BDSM_0_0_0_PCI_BDSM_MSK                            (0xFFF00000)
  #define UNCORE_CR_BDSM_0_0_0_PCI_BDSM_MAX                            (0x00000FFF)
  #define UNCORE_CR_BDSM_0_0_0_PCI_BDSM_DEF                            (0x00000000)

#define UNCORE_CR_BGSM_0_0_0_PCI_REG                                 (0x000000B4)
  #define UNCORE_CR_BGSM_0_0_0_PCI_LOCK_OFF                            ( 0)
  #define UNCORE_CR_BGSM_0_0_0_PCI_LOCK_WID                            ( 1)
  #define UNCORE_CR_BGSM_0_0_0_PCI_LOCK_MSK                            (0x00000001)
  #define UNCORE_CR_BGSM_0_0_0_PCI_LOCK_MAX                            (0x00000001)
  #define UNCORE_CR_BGSM_0_0_0_PCI_LOCK_DEF                            (0x00000000)
  #define UNCORE_CR_BGSM_0_0_0_PCI_BGSM_OFF                            (20)
  #define UNCORE_CR_BGSM_0_0_0_PCI_BGSM_WID                            (12)
  #define UNCORE_CR_BGSM_0_0_0_PCI_BGSM_MSK                            (0xFFF00000)
  #define UNCORE_CR_BGSM_0_0_0_PCI_BGSM_MAX                            (0x00000FFF)
  #define UNCORE_CR_BGSM_0_0_0_PCI_BGSM_DEF                            (0x00000001)

#define UNCORE_CR_TSEGMB_0_0_0_PCI_REG                               (0x000000B8)
  #define UNCORE_CR_TSEGMB_0_0_0_PCI_LOCK_OFF                          ( 0)
  #define UNCORE_CR_TSEGMB_0_0_0_PCI_LOCK_WID                          ( 1)
  #define UNCORE_CR_TSEGMB_0_0_0_PCI_LOCK_MSK                          (0x00000001)
  #define UNCORE_CR_TSEGMB_0_0_0_PCI_LOCK_MAX                          (0x00000001)
  #define UNCORE_CR_TSEGMB_0_0_0_PCI_LOCK_DEF                          (0x00000000)
  #define UNCORE_CR_TSEGMB_0_0_0_PCI_TSEGMB_OFF                        (20)
  #define UNCORE_CR_TSEGMB_0_0_0_PCI_TSEGMB_WID                        (12)
  #define UNCORE_CR_TSEGMB_0_0_0_PCI_TSEGMB_MSK                        (0xFFF00000)
  #define UNCORE_CR_TSEGMB_0_0_0_PCI_TSEGMB_MAX                        (0x00000FFF)
  #define UNCORE_CR_TSEGMB_0_0_0_PCI_TSEGMB_DEF                        (0x00000000)

#define UNCORE_CR_TOLUD_0_0_0_PCI_REG                                (0x000000BC)
  #define UNCORE_CR_TOLUD_0_0_0_PCI_LOCK_OFF                           ( 0)
  #define UNCORE_CR_TOLUD_0_0_0_PCI_LOCK_WID                           ( 1)
  #define UNCORE_CR_TOLUD_0_0_0_PCI_LOCK_MSK                           (0x00000001)
  #define UNCORE_CR_TOLUD_0_0_0_PCI_LOCK_MAX                           (0x00000001)
  #define UNCORE_CR_TOLUD_0_0_0_PCI_LOCK_DEF                           (0x00000000)
  #define UNCORE_CR_TOLUD_0_0_0_PCI_TOLUD_OFF                          (20)
  #define UNCORE_CR_TOLUD_0_0_0_PCI_TOLUD_WID                          (12)
  #define UNCORE_CR_TOLUD_0_0_0_PCI_TOLUD_MSK                          (0xFFF00000)
  #define UNCORE_CR_TOLUD_0_0_0_PCI_TOLUD_MAX                          (0x00000FFF)
  #define UNCORE_CR_TOLUD_0_0_0_PCI_TOLUD_DEF                          (0x00000001)

#define UNCORE_CR_DIDOVR_0_0_0_PCI_REG                               (0x000000C0)
  #define UNCORE_CR_DIDOVR_0_0_0_PCI_DID2OVR_OFF                       ( 0)
  #define UNCORE_CR_DIDOVR_0_0_0_PCI_DID2OVR_WID                       ( 8)
  #define UNCORE_CR_DIDOVR_0_0_0_PCI_DID2OVR_MSK                       (0x000000FF)
  #define UNCORE_CR_DIDOVR_0_0_0_PCI_DID2OVR_MAX                       (0x000000FF)
  #define UNCORE_CR_DIDOVR_0_0_0_PCI_DID2OVR_DEF                       (0x00000000)
  #define UNCORE_CR_DIDOVR_0_0_0_PCI_OE2_OFF                           ( 8)
  #define UNCORE_CR_DIDOVR_0_0_0_PCI_OE2_WID                           ( 1)
  #define UNCORE_CR_DIDOVR_0_0_0_PCI_OE2_MSK                           (0x00000100)
  #define UNCORE_CR_DIDOVR_0_0_0_PCI_OE2_MAX                           (0x00000001)
  #define UNCORE_CR_DIDOVR_0_0_0_PCI_OE2_DEF                           (0x00000000)
  #define UNCORE_CR_DIDOVR_0_0_0_PCI_DID0OVR_OFF                       (16)
  #define UNCORE_CR_DIDOVR_0_0_0_PCI_DID0OVR_WID                       ( 8)
  #define UNCORE_CR_DIDOVR_0_0_0_PCI_DID0OVR_MSK                       (0x00FF0000)
  #define UNCORE_CR_DIDOVR_0_0_0_PCI_DID0OVR_MAX                       (0x000000FF)
  #define UNCORE_CR_DIDOVR_0_0_0_PCI_DID0OVR_DEF                       (0x00000000)
  #define UNCORE_CR_DIDOVR_0_0_0_PCI_OE0_OFF                           (24)
  #define UNCORE_CR_DIDOVR_0_0_0_PCI_OE0_WID                           ( 1)
  #define UNCORE_CR_DIDOVR_0_0_0_PCI_OE0_MSK                           (0x01000000)
  #define UNCORE_CR_DIDOVR_0_0_0_PCI_OE0_MAX                           (0x00000001)
  #define UNCORE_CR_DIDOVR_0_0_0_PCI_OE0_DEF                           (0x00000000)

#define UNCORE_CR_ERRSTS_0_0_0_PCI_REG                               (0x000000C8)
  #define UNCORE_CR_ERRSTS_0_0_0_PCI_DSERR_OFF                         ( 0)
  #define UNCORE_CR_ERRSTS_0_0_0_PCI_DSERR_WID                         ( 1)
  #define UNCORE_CR_ERRSTS_0_0_0_PCI_DSERR_MSK                         (0x00000001)
  #define UNCORE_CR_ERRSTS_0_0_0_PCI_DSERR_MAX                         (0x00000001)
  #define UNCORE_CR_ERRSTS_0_0_0_PCI_DSERR_DEF                         (0x00000000)
  #define UNCORE_CR_ERRSTS_0_0_0_PCI_DMERR_OFF                         ( 1)
  #define UNCORE_CR_ERRSTS_0_0_0_PCI_DMERR_WID                         ( 1)
  #define UNCORE_CR_ERRSTS_0_0_0_PCI_DMERR_MSK                         (0x00000002)
  #define UNCORE_CR_ERRSTS_0_0_0_PCI_DMERR_MAX                         (0x00000001)
  #define UNCORE_CR_ERRSTS_0_0_0_PCI_DMERR_DEF                         (0x00000000)

#define UNCORE_CR_ERRCMD_0_0_0_PCI_REG                               (0x000000CA)
  #define UNCORE_CR_ERRCMD_0_0_0_PCI_DSERR_OFF                         ( 0)
  #define UNCORE_CR_ERRCMD_0_0_0_PCI_DSERR_WID                         ( 1)
  #define UNCORE_CR_ERRCMD_0_0_0_PCI_DSERR_MSK                         (0x00000001)
  #define UNCORE_CR_ERRCMD_0_0_0_PCI_DSERR_MAX                         (0x00000001)
  #define UNCORE_CR_ERRCMD_0_0_0_PCI_DSERR_DEF                         (0x00000000)
  #define UNCORE_CR_ERRCMD_0_0_0_PCI_DMERR_OFF                         ( 1)
  #define UNCORE_CR_ERRCMD_0_0_0_PCI_DMERR_WID                         ( 1)
  #define UNCORE_CR_ERRCMD_0_0_0_PCI_DMERR_MSK                         (0x00000002)
  #define UNCORE_CR_ERRCMD_0_0_0_PCI_DMERR_MAX                         (0x00000001)
  #define UNCORE_CR_ERRCMD_0_0_0_PCI_DMERR_DEF                         (0x00000000)

#define UNCORE_CR_SMICMD_0_0_0_PCI_REG                               (0x000000CC)
  #define UNCORE_CR_SMICMD_0_0_0_PCI_DSESMI_OFF                        ( 0)
  #define UNCORE_CR_SMICMD_0_0_0_PCI_DSESMI_WID                        ( 1)
  #define UNCORE_CR_SMICMD_0_0_0_PCI_DSESMI_MSK                        (0x00000001)
  #define UNCORE_CR_SMICMD_0_0_0_PCI_DSESMI_MAX                        (0x00000001)
  #define UNCORE_CR_SMICMD_0_0_0_PCI_DSESMI_DEF                        (0x00000000)
  #define UNCORE_CR_SMICMD_0_0_0_PCI_DMESMI_OFF                        ( 1)
  #define UNCORE_CR_SMICMD_0_0_0_PCI_DMESMI_WID                        ( 1)
  #define UNCORE_CR_SMICMD_0_0_0_PCI_DMESMI_MSK                        (0x00000002)
  #define UNCORE_CR_SMICMD_0_0_0_PCI_DMESMI_MAX                        (0x00000001)
  #define UNCORE_CR_SMICMD_0_0_0_PCI_DMESMI_DEF                        (0x00000000)

#define UNCORE_CR_SCICMD_0_0_0_PCI_REG                               (0x000000CE)
  #define UNCORE_CR_SCICMD_0_0_0_PCI_DSESCI_OFF                        ( 0)
  #define UNCORE_CR_SCICMD_0_0_0_PCI_DSESCI_WID                        ( 1)
  #define UNCORE_CR_SCICMD_0_0_0_PCI_DSESCI_MSK                        (0x00000001)
  #define UNCORE_CR_SCICMD_0_0_0_PCI_DSESCI_MAX                        (0x00000001)
  #define UNCORE_CR_SCICMD_0_0_0_PCI_DSESCI_DEF                        (0x00000000)
  #define UNCORE_CR_SCICMD_0_0_0_PCI_DMESCI_OFF                        ( 1)
  #define UNCORE_CR_SCICMD_0_0_0_PCI_DMESCI_WID                        ( 1)
  #define UNCORE_CR_SCICMD_0_0_0_PCI_DMESCI_MSK                        (0x00000002)
  #define UNCORE_CR_SCICMD_0_0_0_PCI_DMESCI_MAX                        (0x00000001)
  #define UNCORE_CR_SCICMD_0_0_0_PCI_DMESCI_DEF                        (0x00000000)

#define UNCORE_CR_SKPD_0_0_0_PCI_REG                                 (0x000000DC)
  #define UNCORE_CR_SKPD_0_0_0_PCI_SKPD_OFF                            ( 0)
  #define UNCORE_CR_SKPD_0_0_0_PCI_SKPD_WID                            (32)
  #define UNCORE_CR_SKPD_0_0_0_PCI_SKPD_MSK                            (0xFFFFFFFF)
  #define UNCORE_CR_SKPD_0_0_0_PCI_SKPD_MAX                            (0xFFFFFFFF)
  #define UNCORE_CR_SKPD_0_0_0_PCI_SKPD_DEF                            (0x00000000)

#define UNCORE_CR_CAPID0_0_0_0_PCI_REG                               (0x000000E0)
  #define UNCORE_CR_CAPID0_0_0_0_PCI_CAP_ID_OFF                        ( 0)
  #define UNCORE_CR_CAPID0_0_0_0_PCI_CAP_ID_WID                        ( 8)
  #define UNCORE_CR_CAPID0_0_0_0_PCI_CAP_ID_MSK                        (0x000000FF)
  #define UNCORE_CR_CAPID0_0_0_0_PCI_CAP_ID_MAX                        (0x000000FF)
  #define UNCORE_CR_CAPID0_0_0_0_PCI_CAP_ID_DEF                        (0x00000009)
  #define UNCORE_CR_CAPID0_0_0_0_PCI_NEXT_CAP_OFF                      ( 8)
  #define UNCORE_CR_CAPID0_0_0_0_PCI_NEXT_CAP_WID                      ( 8)
  #define UNCORE_CR_CAPID0_0_0_0_PCI_NEXT_CAP_MSK                      (0x0000FF00)
  #define UNCORE_CR_CAPID0_0_0_0_PCI_NEXT_CAP_MAX                      (0x000000FF)
  #define UNCORE_CR_CAPID0_0_0_0_PCI_NEXT_CAP_DEF                      (0x00000000)

#define UNCORE_CR_CAPCTRL0_0_0_0_PCI_REG                             (0x000000E2)
  #define UNCORE_CR_CAPCTRL0_0_0_0_PCI_CAPIDLEN_OFF                    ( 0)
  #define UNCORE_CR_CAPCTRL0_0_0_0_PCI_CAPIDLEN_WID                    ( 8)
  #define UNCORE_CR_CAPCTRL0_0_0_0_PCI_CAPIDLEN_MSK                    (0x000000FF)
  #define UNCORE_CR_CAPCTRL0_0_0_0_PCI_CAPIDLEN_MAX                    (0x000000FF)
  #define UNCORE_CR_CAPCTRL0_0_0_0_PCI_CAPIDLEN_DEF                    (0x00000010)
  #define UNCORE_CR_CAPCTRL0_0_0_0_PCI_CAPID_VER_OFF                   ( 8)
  #define UNCORE_CR_CAPCTRL0_0_0_0_PCI_CAPID_VER_WID                   ( 4)
  #define UNCORE_CR_CAPCTRL0_0_0_0_PCI_CAPID_VER_MSK                   (0x00000F00)
  #define UNCORE_CR_CAPCTRL0_0_0_0_PCI_CAPID_VER_MAX                   (0x0000000F)
  #define UNCORE_CR_CAPCTRL0_0_0_0_PCI_CAPID_VER_DEF                   (0x00000001)

#define UNCORE_CR_CAPID0_A_0_0_0_PCI_REG                             (0x000000E4)
  #define UNCORE_CR_CAPID0_A_0_0_0_PCI_DDR3L_EN_OFF                    ( 0)
  #define UNCORE_CR_CAPID0_A_0_0_0_PCI_DDR3L_EN_WID                    ( 1)
  #define UNCORE_CR_CAPID0_A_0_0_0_PCI_DDR3L_EN_MSK                    (0x00000001)
  #define UNCORE_CR_CAPID0_A_0_0_0_PCI_DDR3L_EN_MAX                    (0x00000001)
  #define UNCORE_CR_CAPID0_A_0_0_0_PCI_DDR3L_EN_DEF                    (0x00000000)
  #define UNCORE_CR_CAPID0_A_0_0_0_PCI_DDR_WRTVREF_OFF                 ( 1)
  #define UNCORE_CR_CAPID0_A_0_0_0_PCI_DDR_WRTVREF_WID                 ( 1)
  #define UNCORE_CR_CAPID0_A_0_0_0_PCI_DDR_WRTVREF_MSK                 (0x00000002)
  #define UNCORE_CR_CAPID0_A_0_0_0_PCI_DDR_WRTVREF_MAX                 (0x00000001)
  #define UNCORE_CR_CAPID0_A_0_0_0_PCI_DDR_WRTVREF_DEF                 (0x00000000)
  #define UNCORE_CR_CAPID0_A_0_0_0_PCI_OC_ENABLED_DSKU_OFF             ( 2)
  #define UNCORE_CR_CAPID0_A_0_0_0_PCI_OC_ENABLED_DSKU_WID             ( 1)
  #define UNCORE_CR_CAPID0_A_0_0_0_PCI_OC_ENABLED_DSKU_MSK             (0x00000004)
  #define UNCORE_CR_CAPID0_A_0_0_0_PCI_OC_ENABLED_DSKU_MAX             (0x00000001)
  #define UNCORE_CR_CAPID0_A_0_0_0_PCI_OC_ENABLED_DSKU_DEF             (0x00000000)
  #define UNCORE_CR_CAPID0_A_0_0_0_PCI_DDR_OVERCLOCK_OFF               ( 3)
  #define UNCORE_CR_CAPID0_A_0_0_0_PCI_DDR_OVERCLOCK_WID               ( 1)
  #define UNCORE_CR_CAPID0_A_0_0_0_PCI_DDR_OVERCLOCK_MSK               (0x00000008)
  #define UNCORE_CR_CAPID0_A_0_0_0_PCI_DDR_OVERCLOCK_MAX               (0x00000001)
  #define UNCORE_CR_CAPID0_A_0_0_0_PCI_DDR_OVERCLOCK_DEF               (0x00000000)
  #define UNCORE_CR_CAPID0_A_0_0_0_PCI_CRID_OFF                        ( 4)
  #define UNCORE_CR_CAPID0_A_0_0_0_PCI_CRID_WID                        ( 4)
  #define UNCORE_CR_CAPID0_A_0_0_0_PCI_CRID_MSK                        (0x000000F0)
  #define UNCORE_CR_CAPID0_A_0_0_0_PCI_CRID_MAX                        (0x0000000F)
  #define UNCORE_CR_CAPID0_A_0_0_0_PCI_CRID_DEF                        (0x00000000)
  #define UNCORE_CR_CAPID0_A_0_0_0_PCI_SPARE8_OFF                      ( 8)
  #define UNCORE_CR_CAPID0_A_0_0_0_PCI_SPARE8_WID                      ( 1)
  #define UNCORE_CR_CAPID0_A_0_0_0_PCI_SPARE8_MSK                      (0x00000100)
  #define UNCORE_CR_CAPID0_A_0_0_0_PCI_SPARE8_MAX                      (0x00000001)
  #define UNCORE_CR_CAPID0_A_0_0_0_PCI_SPARE8_DEF                      (0x00000000)
  #define UNCORE_CR_CAPID0_A_0_0_0_PCI_DID2OE_OFF                      ( 9)
  #define UNCORE_CR_CAPID0_A_0_0_0_PCI_DID2OE_WID                      ( 1)
  #define UNCORE_CR_CAPID0_A_0_0_0_PCI_DID2OE_MSK                      (0x00000200)
  #define UNCORE_CR_CAPID0_A_0_0_0_PCI_DID2OE_MAX                      (0x00000001)
  #define UNCORE_CR_CAPID0_A_0_0_0_PCI_DID2OE_DEF                      (0x00000000)
  #define UNCORE_CR_CAPID0_A_0_0_0_PCI_DID0OE_OFF                      (10)
  #define UNCORE_CR_CAPID0_A_0_0_0_PCI_DID0OE_WID                      ( 1)
  #define UNCORE_CR_CAPID0_A_0_0_0_PCI_DID0OE_MSK                      (0x00000400)
  #define UNCORE_CR_CAPID0_A_0_0_0_PCI_DID0OE_MAX                      (0x00000001)
  #define UNCORE_CR_CAPID0_A_0_0_0_PCI_DID0OE_DEF                      (0x00000000)
  #define UNCORE_CR_CAPID0_A_0_0_0_PCI_IGD_OFF                         (11)
  #define UNCORE_CR_CAPID0_A_0_0_0_PCI_IGD_WID                         ( 1)
  #define UNCORE_CR_CAPID0_A_0_0_0_PCI_IGD_MSK                         (0x00000800)
  #define UNCORE_CR_CAPID0_A_0_0_0_PCI_IGD_MAX                         (0x00000001)
  #define UNCORE_CR_CAPID0_A_0_0_0_PCI_IGD_DEF                         (0x00000000)
  #define UNCORE_CR_CAPID0_A_0_0_0_PCI_PDCD_OFF                        (12)
  #define UNCORE_CR_CAPID0_A_0_0_0_PCI_PDCD_WID                        ( 1)
  #define UNCORE_CR_CAPID0_A_0_0_0_PCI_PDCD_MSK                        (0x00001000)
  #define UNCORE_CR_CAPID0_A_0_0_0_PCI_PDCD_MAX                        (0x00000001)
  #define UNCORE_CR_CAPID0_A_0_0_0_PCI_PDCD_DEF                        (0x00000000)
  #define UNCORE_CR_CAPID0_A_0_0_0_PCI_X2APIC_EN_OFF                   (13)
  #define UNCORE_CR_CAPID0_A_0_0_0_PCI_X2APIC_EN_WID                   ( 1)
  #define UNCORE_CR_CAPID0_A_0_0_0_PCI_X2APIC_EN_MSK                   (0x00002000)
  #define UNCORE_CR_CAPID0_A_0_0_0_PCI_X2APIC_EN_MAX                   (0x00000001)
  #define UNCORE_CR_CAPID0_A_0_0_0_PCI_X2APIC_EN_DEF                   (0x00000000)
  #define UNCORE_CR_CAPID0_A_0_0_0_PCI_DDPCD_OFF                       (14)
  #define UNCORE_CR_CAPID0_A_0_0_0_PCI_DDPCD_WID                       ( 1)
  #define UNCORE_CR_CAPID0_A_0_0_0_PCI_DDPCD_MSK                       (0x00004000)
  #define UNCORE_CR_CAPID0_A_0_0_0_PCI_DDPCD_MAX                       (0x00000001)
  #define UNCORE_CR_CAPID0_A_0_0_0_PCI_DDPCD_DEF                       (0x00000000)
  #define UNCORE_CR_CAPID0_A_0_0_0_PCI_CDD_OFF                         (15)
  #define UNCORE_CR_CAPID0_A_0_0_0_PCI_CDD_WID                         ( 1)
  #define UNCORE_CR_CAPID0_A_0_0_0_PCI_CDD_MSK                         (0x00008000)
  #define UNCORE_CR_CAPID0_A_0_0_0_PCI_CDD_MAX                         (0x00000001)
  #define UNCORE_CR_CAPID0_A_0_0_0_PCI_CDD_DEF                         (0x00000000)
  #define UNCORE_CR_CAPID0_A_0_0_0_PCI_FUFRD_OFF                       (16)
  #define UNCORE_CR_CAPID0_A_0_0_0_PCI_FUFRD_WID                       ( 1)
  #define UNCORE_CR_CAPID0_A_0_0_0_PCI_FUFRD_MSK                       (0x00010000)
  #define UNCORE_CR_CAPID0_A_0_0_0_PCI_FUFRD_MAX                       (0x00000001)
  #define UNCORE_CR_CAPID0_A_0_0_0_PCI_FUFRD_DEF                       (0x00000000)
  #define UNCORE_CR_CAPID0_A_0_0_0_PCI_D1NM_OFF                        (17)
  #define UNCORE_CR_CAPID0_A_0_0_0_PCI_D1NM_WID                        ( 1)
  #define UNCORE_CR_CAPID0_A_0_0_0_PCI_D1NM_MSK                        (0x00020000)
  #define UNCORE_CR_CAPID0_A_0_0_0_PCI_D1NM_MAX                        (0x00000001)
  #define UNCORE_CR_CAPID0_A_0_0_0_PCI_D1NM_DEF                        (0x00000000)
  #define UNCORE_CR_CAPID0_A_0_0_0_PCI_SPARE18_OFF                     (18)
  #define UNCORE_CR_CAPID0_A_0_0_0_PCI_SPARE18_WID                     ( 1)
  #define UNCORE_CR_CAPID0_A_0_0_0_PCI_SPARE18_MSK                     (0x00040000)
  #define UNCORE_CR_CAPID0_A_0_0_0_PCI_SPARE18_MAX                     (0x00000001)
  #define UNCORE_CR_CAPID0_A_0_0_0_PCI_SPARE18_DEF                     (0x00000000)
  #define UNCORE_CR_CAPID0_A_0_0_0_PCI_DDRSZ_OFF                       (19)
  #define UNCORE_CR_CAPID0_A_0_0_0_PCI_DDRSZ_WID                       ( 2)
  #define UNCORE_CR_CAPID0_A_0_0_0_PCI_DDRSZ_MSK                       (0x00180000)
  #define UNCORE_CR_CAPID0_A_0_0_0_PCI_DDRSZ_MAX                       (0x00000003)
  #define UNCORE_CR_CAPID0_A_0_0_0_PCI_DDRSZ_DEF                       (0x00000000)
  #define UNCORE_CR_CAPID0_A_0_0_0_PCI_PEGG2DIS_OFF                    (21)
  #define UNCORE_CR_CAPID0_A_0_0_0_PCI_PEGG2DIS_WID                    ( 1)
  #define UNCORE_CR_CAPID0_A_0_0_0_PCI_PEGG2DIS_MSK                    (0x00200000)
  #define UNCORE_CR_CAPID0_A_0_0_0_PCI_PEGG2DIS_MAX                    (0x00000001)
  #define UNCORE_CR_CAPID0_A_0_0_0_PCI_PEGG2DIS_DEF                    (0x00000000)
  #define UNCORE_CR_CAPID0_A_0_0_0_PCI_DMIG2DIS_OFF                    (22)
  #define UNCORE_CR_CAPID0_A_0_0_0_PCI_DMIG2DIS_WID                    ( 1)
  #define UNCORE_CR_CAPID0_A_0_0_0_PCI_DMIG2DIS_MSK                    (0x00400000)
  #define UNCORE_CR_CAPID0_A_0_0_0_PCI_DMIG2DIS_MAX                    (0x00000001)
  #define UNCORE_CR_CAPID0_A_0_0_0_PCI_DMIG2DIS_DEF                    (0x00000000)
  #define UNCORE_CR_CAPID0_A_0_0_0_PCI_VTDD_OFF                        (23)
  #define UNCORE_CR_CAPID0_A_0_0_0_PCI_VTDD_WID                        ( 1)
  #define UNCORE_CR_CAPID0_A_0_0_0_PCI_VTDD_MSK                        (0x00800000)
  #define UNCORE_CR_CAPID0_A_0_0_0_PCI_VTDD_MAX                        (0x00000001)
  #define UNCORE_CR_CAPID0_A_0_0_0_PCI_VTDD_DEF                        (0x00000000)
  #define UNCORE_CR_CAPID0_A_0_0_0_PCI_FDEE_OFF                        (24)
  #define UNCORE_CR_CAPID0_A_0_0_0_PCI_FDEE_WID                        ( 1)
  #define UNCORE_CR_CAPID0_A_0_0_0_PCI_FDEE_MSK                        (0x01000000)
  #define UNCORE_CR_CAPID0_A_0_0_0_PCI_FDEE_MAX                        (0x00000001)
  #define UNCORE_CR_CAPID0_A_0_0_0_PCI_FDEE_DEF                        (0x00000000)
  #define UNCORE_CR_CAPID0_A_0_0_0_PCI_ECCDIS_OFF                      (25)
  #define UNCORE_CR_CAPID0_A_0_0_0_PCI_ECCDIS_WID                      ( 1)
  #define UNCORE_CR_CAPID0_A_0_0_0_PCI_ECCDIS_MSK                      (0x02000000)
  #define UNCORE_CR_CAPID0_A_0_0_0_PCI_ECCDIS_MAX                      (0x00000001)
  #define UNCORE_CR_CAPID0_A_0_0_0_PCI_ECCDIS_DEF                      (0x00000000)
  #define UNCORE_CR_CAPID0_A_0_0_0_PCI_DW_OFF                          (26)
  #define UNCORE_CR_CAPID0_A_0_0_0_PCI_DW_WID                          ( 1)
  #define UNCORE_CR_CAPID0_A_0_0_0_PCI_DW_MSK                          (0x04000000)
  #define UNCORE_CR_CAPID0_A_0_0_0_PCI_DW_MAX                          (0x00000001)
  #define UNCORE_CR_CAPID0_A_0_0_0_PCI_DW_DEF                          (0x00000000)
  #define UNCORE_CR_CAPID0_A_0_0_0_PCI_PELWUD_OFF                      (27)
  #define UNCORE_CR_CAPID0_A_0_0_0_PCI_PELWUD_WID                      ( 1)
  #define UNCORE_CR_CAPID0_A_0_0_0_PCI_PELWUD_MSK                      (0x08000000)
  #define UNCORE_CR_CAPID0_A_0_0_0_PCI_PELWUD_MAX                      (0x00000001)
  #define UNCORE_CR_CAPID0_A_0_0_0_PCI_PELWUD_DEF                      (0x00000000)
  #define UNCORE_CR_CAPID0_A_0_0_0_PCI_PEG10D_OFF                      (28)
  #define UNCORE_CR_CAPID0_A_0_0_0_PCI_PEG10D_WID                      ( 1)
  #define UNCORE_CR_CAPID0_A_0_0_0_PCI_PEG10D_MSK                      (0x10000000)
  #define UNCORE_CR_CAPID0_A_0_0_0_PCI_PEG10D_MAX                      (0x00000001)
  #define UNCORE_CR_CAPID0_A_0_0_0_PCI_PEG10D_DEF                      (0x00000000)
  #define UNCORE_CR_CAPID0_A_0_0_0_PCI_PEG11D_OFF                      (29)
  #define UNCORE_CR_CAPID0_A_0_0_0_PCI_PEG11D_WID                      ( 1)
  #define UNCORE_CR_CAPID0_A_0_0_0_PCI_PEG11D_MSK                      (0x20000000)
  #define UNCORE_CR_CAPID0_A_0_0_0_PCI_PEG11D_MAX                      (0x00000001)
  #define UNCORE_CR_CAPID0_A_0_0_0_PCI_PEG11D_DEF                      (0x00000000)
  #define UNCORE_CR_CAPID0_A_0_0_0_PCI_PEG12D_OFF                      (30)
  #define UNCORE_CR_CAPID0_A_0_0_0_PCI_PEG12D_WID                      ( 1)
  #define UNCORE_CR_CAPID0_A_0_0_0_PCI_PEG12D_MSK                      (0x40000000)
  #define UNCORE_CR_CAPID0_A_0_0_0_PCI_PEG12D_MAX                      (0x00000001)
  #define UNCORE_CR_CAPID0_A_0_0_0_PCI_PEG12D_DEF                      (0x00000000)
  #define UNCORE_CR_CAPID0_A_0_0_0_PCI_DHDAD_OFF                       (31)
  #define UNCORE_CR_CAPID0_A_0_0_0_PCI_DHDAD_WID                       ( 1)
  #define UNCORE_CR_CAPID0_A_0_0_0_PCI_DHDAD_MSK                       (0x80000000)
  #define UNCORE_CR_CAPID0_A_0_0_0_PCI_DHDAD_MAX                       (0x00000001)
  #define UNCORE_CR_CAPID0_A_0_0_0_PCI_DHDAD_DEF                       (0x00000000)

#define UNCORE_CR_CAPID0_B_0_0_0_PCI_REG                             (0x000000E8)
  #define UNCORE_CR_CAPID0_B_0_0_0_PCI_SPEGFX1_OFF                     ( 0)
  #define UNCORE_CR_CAPID0_B_0_0_0_PCI_SPEGFX1_WID                     ( 1)
  #define UNCORE_CR_CAPID0_B_0_0_0_PCI_SPEGFX1_MSK                     (0x00000001)
  #define UNCORE_CR_CAPID0_B_0_0_0_PCI_SPEGFX1_MAX                     (0x00000001)
  #define UNCORE_CR_CAPID0_B_0_0_0_PCI_SPEGFX1_DEF                     (0x00000000)
  #define UNCORE_CR_CAPID0_B_0_0_0_PCI_DPEGFX1_OFF                     ( 1)
  #define UNCORE_CR_CAPID0_B_0_0_0_PCI_DPEGFX1_WID                     ( 1)
  #define UNCORE_CR_CAPID0_B_0_0_0_PCI_DPEGFX1_MSK                     (0x00000002)
  #define UNCORE_CR_CAPID0_B_0_0_0_PCI_DPEGFX1_MAX                     (0x00000001)
  #define UNCORE_CR_CAPID0_B_0_0_0_PCI_DPEGFX1_DEF                     (0x00000000)
  #define UNCORE_CR_CAPID0_B_0_0_0_PCI_LPDDR3_EN_OFF                   ( 2)
  #define UNCORE_CR_CAPID0_B_0_0_0_PCI_LPDDR3_EN_WID                   ( 1)
  #define UNCORE_CR_CAPID0_B_0_0_0_PCI_LPDDR3_EN_MSK                   (0x00000004)
  #define UNCORE_CR_CAPID0_B_0_0_0_PCI_LPDDR3_EN_MAX                   (0x00000001)
  #define UNCORE_CR_CAPID0_B_0_0_0_PCI_LPDDR3_EN_DEF                   (0x00000000)
  #define UNCORE_CR_CAPID0_B_0_0_0_PCI_DDR4_EN_OFF                     ( 3)
  #define UNCORE_CR_CAPID0_B_0_0_0_PCI_DDR4_EN_WID                     ( 1)
  #define UNCORE_CR_CAPID0_B_0_0_0_PCI_DDR4_EN_MSK                     (0x00000008)
  #define UNCORE_CR_CAPID0_B_0_0_0_PCI_DDR4_EN_MAX                     (0x00000001)
  #define UNCORE_CR_CAPID0_B_0_0_0_PCI_DDR4_EN_DEF                     (0x00000000)
  #define UNCORE_CR_CAPID0_B_0_0_0_PCI_DMFC_DDR3_OFF                   ( 4)
  #define UNCORE_CR_CAPID0_B_0_0_0_PCI_DMFC_DDR3_WID                   ( 3)
  #define UNCORE_CR_CAPID0_B_0_0_0_PCI_DMFC_DDR3_MSK                   (0x00000070)
  #define UNCORE_CR_CAPID0_B_0_0_0_PCI_DMFC_DDR3_MAX                   (0x00000007)
  #define UNCORE_CR_CAPID0_B_0_0_0_PCI_DMFC_DDR3_DEF                   (0x00000000)
  #define UNCORE_CR_CAPID0_B_0_0_0_PCI_DDD_OFF                         ( 7)
  #define UNCORE_CR_CAPID0_B_0_0_0_PCI_DDD_WID                         ( 1)
  #define UNCORE_CR_CAPID0_B_0_0_0_PCI_DDD_MSK                         (0x00000080)
  #define UNCORE_CR_CAPID0_B_0_0_0_PCI_DDD_MAX                         (0x00000001)
  #define UNCORE_CR_CAPID0_B_0_0_0_PCI_DDD_DEF                         (0x00000000)
  #define UNCORE_CR_CAPID0_B_0_0_0_PCI_GMM_DIS_OFF                     ( 8)
  #define UNCORE_CR_CAPID0_B_0_0_0_PCI_GMM_DIS_WID                     ( 1)
  #define UNCORE_CR_CAPID0_B_0_0_0_PCI_GMM_DIS_MSK                     (0x00000100)
  #define UNCORE_CR_CAPID0_B_0_0_0_PCI_GMM_DIS_MAX                     (0x00000001)
  #define UNCORE_CR_CAPID0_B_0_0_0_PCI_GMM_DIS_DEF                     (0x00000000)
  #define UNCORE_CR_CAPID0_B_0_0_0_PCI_SPARE10_9_OFF                   ( 9)
  #define UNCORE_CR_CAPID0_B_0_0_0_PCI_SPARE10_9_WID                   ( 2)
  #define UNCORE_CR_CAPID0_B_0_0_0_PCI_SPARE10_9_MSK                   (0x00000600)
  #define UNCORE_CR_CAPID0_B_0_0_0_PCI_SPARE10_9_MAX                   (0x00000003)
  #define UNCORE_CR_CAPID0_B_0_0_0_PCI_SPARE10_9_DEF                   (0x00000000)
  #define UNCORE_CR_CAPID0_B_0_0_0_PCI_HDCPD_OFF                       (11)
  #define UNCORE_CR_CAPID0_B_0_0_0_PCI_HDCPD_WID                       ( 1)
  #define UNCORE_CR_CAPID0_B_0_0_0_PCI_HDCPD_MSK                       (0x00000800)
  #define UNCORE_CR_CAPID0_B_0_0_0_PCI_HDCPD_MAX                       (0x00000001)
  #define UNCORE_CR_CAPID0_B_0_0_0_PCI_HDCPD_DEF                       (0x00000000)
  #define UNCORE_CR_CAPID0_B_0_0_0_PCI_SPARE14_12_OFF                  (12)
  #define UNCORE_CR_CAPID0_B_0_0_0_PCI_SPARE14_12_WID                  ( 3)
  #define UNCORE_CR_CAPID0_B_0_0_0_PCI_SPARE14_12_MSK                  (0x00007000)
  #define UNCORE_CR_CAPID0_B_0_0_0_PCI_SPARE14_12_MAX                  (0x00000007)
  #define UNCORE_CR_CAPID0_B_0_0_0_PCI_SPARE14_12_DEF                  (0x00000000)
  #define UNCORE_CR_CAPID0_B_0_0_0_PCI_DMIG3DIS_OFF                    (15)
  #define UNCORE_CR_CAPID0_B_0_0_0_PCI_DMIG3DIS_WID                    ( 1)
  #define UNCORE_CR_CAPID0_B_0_0_0_PCI_DMIG3DIS_MSK                    (0x00008000)
  #define UNCORE_CR_CAPID0_B_0_0_0_PCI_DMIG3DIS_MAX                    (0x00000001)
  #define UNCORE_CR_CAPID0_B_0_0_0_PCI_DMIG3DIS_DEF                    (0x00000000)
  #define UNCORE_CR_CAPID0_B_0_0_0_PCI_PEGX16D_OFF                     (16)
  #define UNCORE_CR_CAPID0_B_0_0_0_PCI_PEGX16D_WID                     ( 1)
  #define UNCORE_CR_CAPID0_B_0_0_0_PCI_PEGX16D_MSK                     (0x00010000)
  #define UNCORE_CR_CAPID0_B_0_0_0_PCI_PEGX16D_MAX                     (0x00000001)
  #define UNCORE_CR_CAPID0_B_0_0_0_PCI_PEGX16D_DEF                     (0x00000000)
  #define UNCORE_CR_CAPID0_B_0_0_0_PCI_ADDGFXCAP_OFF                   (17)
  #define UNCORE_CR_CAPID0_B_0_0_0_PCI_ADDGFXCAP_WID                   ( 1)
  #define UNCORE_CR_CAPID0_B_0_0_0_PCI_ADDGFXCAP_MSK                   (0x00020000)
  #define UNCORE_CR_CAPID0_B_0_0_0_PCI_ADDGFXCAP_MAX                   (0x00000001)
  #define UNCORE_CR_CAPID0_B_0_0_0_PCI_ADDGFXCAP_DEF                   (0x00000000)
  #define UNCORE_CR_CAPID0_B_0_0_0_PCI_ADDGFXEN_OFF                    (18)
  #define UNCORE_CR_CAPID0_B_0_0_0_PCI_ADDGFXEN_WID                    ( 1)
  #define UNCORE_CR_CAPID0_B_0_0_0_PCI_ADDGFXEN_MSK                    (0x00040000)
  #define UNCORE_CR_CAPID0_B_0_0_0_PCI_ADDGFXEN_MAX                    (0x00000001)
  #define UNCORE_CR_CAPID0_B_0_0_0_PCI_ADDGFXEN_DEF                    (0x00000000)
  #define UNCORE_CR_CAPID0_B_0_0_0_PCI_PKGTYP_OFF                      (19)
  #define UNCORE_CR_CAPID0_B_0_0_0_PCI_PKGTYP_WID                      ( 1)
  #define UNCORE_CR_CAPID0_B_0_0_0_PCI_PKGTYP_MSK                      (0x00080000)
  #define UNCORE_CR_CAPID0_B_0_0_0_PCI_PKGTYP_MAX                      (0x00000001)
  #define UNCORE_CR_CAPID0_B_0_0_0_PCI_PKGTYP_DEF                      (0x00000000)
  #define UNCORE_CR_CAPID0_B_0_0_0_PCI_PEGG3_DIS_OFF                   (20)
  #define UNCORE_CR_CAPID0_B_0_0_0_PCI_PEGG3_DIS_WID                   ( 1)
  #define UNCORE_CR_CAPID0_B_0_0_0_PCI_PEGG3_DIS_MSK                   (0x00100000)
  #define UNCORE_CR_CAPID0_B_0_0_0_PCI_PEGG3_DIS_MAX                   (0x00000001)
  #define UNCORE_CR_CAPID0_B_0_0_0_PCI_PEGG3_DIS_DEF                   (0x00000000)
  #define UNCORE_CR_CAPID0_B_0_0_0_PCI_PLL_REF100_CFG_OFF              (21)
  #define UNCORE_CR_CAPID0_B_0_0_0_PCI_PLL_REF100_CFG_WID              ( 3)
  #define UNCORE_CR_CAPID0_B_0_0_0_PCI_PLL_REF100_CFG_MSK              (0x00E00000)
  #define UNCORE_CR_CAPID0_B_0_0_0_PCI_PLL_REF100_CFG_MAX              (0x00000007)
  #define UNCORE_CR_CAPID0_B_0_0_0_PCI_PLL_REF100_CFG_DEF              (0x00000000)
  #define UNCORE_CR_CAPID0_B_0_0_0_PCI_SPARE24_OFF                     (24)
  #define UNCORE_CR_CAPID0_B_0_0_0_PCI_SPARE24_WID                     ( 1)
  #define UNCORE_CR_CAPID0_B_0_0_0_PCI_SPARE24_MSK                     (0x01000000)
  #define UNCORE_CR_CAPID0_B_0_0_0_PCI_SPARE24_MAX                     (0x00000001)
  #define UNCORE_CR_CAPID0_B_0_0_0_PCI_SPARE24_DEF                     (0x00000000)
  #define UNCORE_CR_CAPID0_B_0_0_0_PCI_CACHESZ_OFF                     (25)
  #define UNCORE_CR_CAPID0_B_0_0_0_PCI_CACHESZ_WID                     ( 3)
  #define UNCORE_CR_CAPID0_B_0_0_0_PCI_CACHESZ_MSK                     (0x0E000000)
  #define UNCORE_CR_CAPID0_B_0_0_0_PCI_CACHESZ_MAX                     (0x00000007)
  #define UNCORE_CR_CAPID0_B_0_0_0_PCI_CACHESZ_DEF                     (0x00000000)
  #define UNCORE_CR_CAPID0_B_0_0_0_PCI_SMT_OFF                         (28)
  #define UNCORE_CR_CAPID0_B_0_0_0_PCI_SMT_WID                         ( 1)
  #define UNCORE_CR_CAPID0_B_0_0_0_PCI_SMT_MSK                         (0x10000000)
  #define UNCORE_CR_CAPID0_B_0_0_0_PCI_SMT_MAX                         (0x00000001)
  #define UNCORE_CR_CAPID0_B_0_0_0_PCI_SMT_DEF                         (0x00000000)
  #define UNCORE_CR_CAPID0_B_0_0_0_PCI_OC_ENABLED_OFF                  (29)
  #define UNCORE_CR_CAPID0_B_0_0_0_PCI_OC_ENABLED_WID                  ( 1)
  #define UNCORE_CR_CAPID0_B_0_0_0_PCI_OC_ENABLED_MSK                  (0x20000000)
  #define UNCORE_CR_CAPID0_B_0_0_0_PCI_OC_ENABLED_MAX                  (0x00000001)
  #define UNCORE_CR_CAPID0_B_0_0_0_PCI_OC_ENABLED_DEF                  (0x00000000)
  #define UNCORE_CR_CAPID0_B_0_0_0_PCI_SPARE30_OFF                     (30)
  #define UNCORE_CR_CAPID0_B_0_0_0_PCI_SPARE30_WID                     ( 1)
  #define UNCORE_CR_CAPID0_B_0_0_0_PCI_SPARE30_MSK                     (0x40000000)
  #define UNCORE_CR_CAPID0_B_0_0_0_PCI_SPARE30_MAX                     (0x00000001)
  #define UNCORE_CR_CAPID0_B_0_0_0_PCI_SPARE30_DEF                     (0x00000000)
  #define UNCORE_CR_CAPID0_B_0_0_0_PCI_IMGU_DIS_OFF                    (31)
  #define UNCORE_CR_CAPID0_B_0_0_0_PCI_IMGU_DIS_WID                    ( 1)
  #define UNCORE_CR_CAPID0_B_0_0_0_PCI_IMGU_DIS_MSK                    (0x80000000)
  #define UNCORE_CR_CAPID0_B_0_0_0_PCI_IMGU_DIS_MAX                    (0x00000001)
  #define UNCORE_CR_CAPID0_B_0_0_0_PCI_IMGU_DIS_DEF                    (0x00000000)

#define UNCORE_CR_CAPID0_C_0_0_0_PCI_REG                             (0x000000EC)
  #define UNCORE_CR_CAPID0_C_0_0_0_PCI_DMFC_LPDDR3_OFF                 (14)
  #define UNCORE_CR_CAPID0_C_0_0_0_PCI_DMFC_LPDDR3_WID                 ( 3)
  #define UNCORE_CR_CAPID0_C_0_0_0_PCI_DMFC_LPDDR3_MSK                 (0x0001C000)
  #define UNCORE_CR_CAPID0_C_0_0_0_PCI_DMFC_LPDDR3_MAX                 (0x00000007)
  #define UNCORE_CR_CAPID0_C_0_0_0_PCI_DMFC_LPDDR3_DEF                 (0x00000000)
  #define UNCORE_CR_CAPID0_C_0_0_0_PCI_DMFC_DDR4_OFF                   (17)
  #define UNCORE_CR_CAPID0_C_0_0_0_PCI_DMFC_DDR4_WID                   ( 3)
  #define UNCORE_CR_CAPID0_C_0_0_0_PCI_DMFC_DDR4_MSK                   (0x000E0000)
  #define UNCORE_CR_CAPID0_C_0_0_0_PCI_DMFC_DDR4_MAX                   (0x00000007)
  #define UNCORE_CR_CAPID0_C_0_0_0_PCI_DMFC_DDR4_DEF                   (0x00000000)

#define UNCORE_CR_BCFC_0_0_0_PCI_REG                                 (0x000000F0)
  #define UNCORE_CR_BCFC_0_0_0_PCI_IGTLBF_OFF                          ( 5)
  #define UNCORE_CR_BCFC_0_0_0_PCI_IGTLBF_WID                          ( 1)
  #define UNCORE_CR_BCFC_0_0_0_PCI_IGTLBF_MSK                          (0x00000020)
  #define UNCORE_CR_BCFC_0_0_0_PCI_IGTLBF_MAX                          (0x00000001)
  #define UNCORE_CR_BCFC_0_0_0_PCI_IGTLBF_DEF                          (0x00000000)

#define UNCORE_CR_MID_0_0_0_PCI_REG                                  (0x000000F4)
  #define UNCORE_CR_MID_0_0_0_PCI_DOT_OFF                              ( 0)
  #define UNCORE_CR_MID_0_0_0_PCI_DOT_WID                              ( 3)
  #define UNCORE_CR_MID_0_0_0_PCI_DOT_MSK                              (0x00000007)
  #define UNCORE_CR_MID_0_0_0_PCI_DOT_MAX                              (0x00000007)
  #define UNCORE_CR_MID_0_0_0_PCI_DOT_DEF                              (0x00000000)
  #define UNCORE_CR_MID_0_0_0_PCI_PROC_OFF                             ( 3)
  #define UNCORE_CR_MID_0_0_0_PCI_PROC_WID                             ( 5)
  #define UNCORE_CR_MID_0_0_0_PCI_PROC_MSK                             (0x000000F8)
  #define UNCORE_CR_MID_0_0_0_PCI_PROC_MAX                             (0x0000001F)
  #define UNCORE_CR_MID_0_0_0_PCI_PROC_DEF                             (0x00000019)
  #define UNCORE_CR_MID_0_0_0_PCI_FOUND_OFF                            ( 8)
  #define UNCORE_CR_MID_0_0_0_PCI_FOUND_WID                            ( 8)
  #define UNCORE_CR_MID_0_0_0_PCI_FOUND_MSK                            (0x0000FF00)
  #define UNCORE_CR_MID_0_0_0_PCI_FOUND_MAX                            (0x000000FF)
  #define UNCORE_CR_MID_0_0_0_PCI_FOUND_DEF                            (0x0000000F)
  #define UNCORE_CR_MID_0_0_0_PCI_MSTEP_OFF                            (16)
  #define UNCORE_CR_MID_0_0_0_PCI_MSTEP_WID                            ( 8)
  #define UNCORE_CR_MID_0_0_0_PCI_MSTEP_MSK                            (0x00FF0000)
  #define UNCORE_CR_MID_0_0_0_PCI_MSTEP_MAX                            (0x000000FF)
  #define UNCORE_CR_MID_0_0_0_PCI_MSTEP_DEF                            (0x00000000)

#define UNCORE_CR_DEBUP0_0_0_0_PCI_REG                               (0x000000F8)
  #define UNCORE_CR_DEBUP0_0_0_0_PCI_RSVD_S0_OFF                       ( 0)
  #define UNCORE_CR_DEBUP0_0_0_0_PCI_RSVD_S0_WID                       ( 3)
  #define UNCORE_CR_DEBUP0_0_0_0_PCI_RSVD_S0_MSK                       (0x00000007)
  #define UNCORE_CR_DEBUP0_0_0_0_PCI_RSVD_S0_MAX                       (0x00000007)
  #define UNCORE_CR_DEBUP0_0_0_0_PCI_RSVD_S0_DEF                       (0x00000000)
  #define UNCORE_CR_DEBUP0_0_0_0_PCI_RSVD_S1_OFF                       ( 4)
  #define UNCORE_CR_DEBUP0_0_0_0_PCI_RSVD_S1_WID                       ( 3)
  #define UNCORE_CR_DEBUP0_0_0_0_PCI_RSVD_S1_MSK                       (0x00000070)
  #define UNCORE_CR_DEBUP0_0_0_0_PCI_RSVD_S1_MAX                       (0x00000007)
  #define UNCORE_CR_DEBUP0_0_0_0_PCI_RSVD_S1_DEF                       (0x00000000)
  #define UNCORE_CR_DEBUP0_0_0_0_PCI_RSVD_S2_OFF                       ( 8)
  #define UNCORE_CR_DEBUP0_0_0_0_PCI_RSVD_S2_WID                       ( 3)
  #define UNCORE_CR_DEBUP0_0_0_0_PCI_RSVD_S2_MSK                       (0x00000700)
  #define UNCORE_CR_DEBUP0_0_0_0_PCI_RSVD_S2_MAX                       (0x00000007)
  #define UNCORE_CR_DEBUP0_0_0_0_PCI_RSVD_S2_DEF                       (0x00000000)
  #define UNCORE_CR_DEBUP0_0_0_0_PCI_RSVD_S3_OFF                       (12)
  #define UNCORE_CR_DEBUP0_0_0_0_PCI_RSVD_S3_WID                       ( 3)
  #define UNCORE_CR_DEBUP0_0_0_0_PCI_RSVD_S3_MSK                       (0x00007000)
  #define UNCORE_CR_DEBUP0_0_0_0_PCI_RSVD_S3_MAX                       (0x00000007)
  #define UNCORE_CR_DEBUP0_0_0_0_PCI_RSVD_S3_DEF                       (0x00000000)
  #define UNCORE_CR_DEBUP0_0_0_0_PCI_RSVD_S4_OFF                       (16)
  #define UNCORE_CR_DEBUP0_0_0_0_PCI_RSVD_S4_WID                       ( 3)
  #define UNCORE_CR_DEBUP0_0_0_0_PCI_RSVD_S4_MSK                       (0x00070000)
  #define UNCORE_CR_DEBUP0_0_0_0_PCI_RSVD_S4_MAX                       (0x00000007)
  #define UNCORE_CR_DEBUP0_0_0_0_PCI_RSVD_S4_DEF                       (0x00000000)
  #define UNCORE_CR_DEBUP0_0_0_0_PCI_RSVD_RW_OFF                       (20)
  #define UNCORE_CR_DEBUP0_0_0_0_PCI_RSVD_RW_WID                       (12)
  #define UNCORE_CR_DEBUP0_0_0_0_PCI_RSVD_RW_MSK                       (0xFFF00000)
  #define UNCORE_CR_DEBUP0_0_0_0_PCI_RSVD_RW_MAX                       (0x00000FFF)
  #define UNCORE_CR_DEBUP0_0_0_0_PCI_RSVD_RW_DEF                       (0x00000000)

#define UNCORE_CR_DEBUP1_0_0_0_PCI_REG                               (0x000000FC)
  #define UNCORE_CR_DEBUP1_0_0_0_PCI_RSVD0_OFF                         ( 0)
  #define UNCORE_CR_DEBUP1_0_0_0_PCI_RSVD0_WID                         ( 3)
  #define UNCORE_CR_DEBUP1_0_0_0_PCI_RSVD0_MSK                         (0x00000007)
  #define UNCORE_CR_DEBUP1_0_0_0_PCI_RSVD0_MAX                         (0x00000007)
  #define UNCORE_CR_DEBUP1_0_0_0_PCI_RSVD0_DEF                         (0x00000000)
  #define UNCORE_CR_DEBUP1_0_0_0_PCI_RSVD1_OFF                         ( 3)
  #define UNCORE_CR_DEBUP1_0_0_0_PCI_RSVD1_WID                         ( 1)
  #define UNCORE_CR_DEBUP1_0_0_0_PCI_RSVD1_MSK                         (0x00000008)
  #define UNCORE_CR_DEBUP1_0_0_0_PCI_RSVD1_MAX                         (0x00000001)
  #define UNCORE_CR_DEBUP1_0_0_0_PCI_RSVD1_DEF                         (0x00000000)
  #define UNCORE_CR_DEBUP1_0_0_0_PCI_RSVD2_OFF                         ( 4)
  #define UNCORE_CR_DEBUP1_0_0_0_PCI_RSVD2_WID                         ( 3)
  #define UNCORE_CR_DEBUP1_0_0_0_PCI_RSVD2_MSK                         (0x00000070)
  #define UNCORE_CR_DEBUP1_0_0_0_PCI_RSVD2_MAX                         (0x00000007)
  #define UNCORE_CR_DEBUP1_0_0_0_PCI_RSVD2_DEF                         (0x00000000)
  #define UNCORE_CR_DEBUP1_0_0_0_PCI_RSVD3_OFF                         ( 7)
  #define UNCORE_CR_DEBUP1_0_0_0_PCI_RSVD3_WID                         ( 1)
  #define UNCORE_CR_DEBUP1_0_0_0_PCI_RSVD3_MSK                         (0x00000080)
  #define UNCORE_CR_DEBUP1_0_0_0_PCI_RSVD3_MAX                         (0x00000001)
  #define UNCORE_CR_DEBUP1_0_0_0_PCI_RSVD3_DEF                         (0x00000000)
  #define UNCORE_CR_DEBUP1_0_0_0_PCI_RSVD4_OFF                         ( 8)
  #define UNCORE_CR_DEBUP1_0_0_0_PCI_RSVD4_WID                         ( 3)
  #define UNCORE_CR_DEBUP1_0_0_0_PCI_RSVD4_MSK                         (0x00000700)
  #define UNCORE_CR_DEBUP1_0_0_0_PCI_RSVD4_MAX                         (0x00000007)
  #define UNCORE_CR_DEBUP1_0_0_0_PCI_RSVD4_DEF                         (0x00000000)
  #define UNCORE_CR_DEBUP1_0_0_0_PCI_RSVD5_OFF                         (11)
  #define UNCORE_CR_DEBUP1_0_0_0_PCI_RSVD5_WID                         ( 1)
  #define UNCORE_CR_DEBUP1_0_0_0_PCI_RSVD5_MSK                         (0x00000800)
  #define UNCORE_CR_DEBUP1_0_0_0_PCI_RSVD5_MAX                         (0x00000001)
  #define UNCORE_CR_DEBUP1_0_0_0_PCI_RSVD5_DEF                         (0x00000000)
  #define UNCORE_CR_DEBUP1_0_0_0_PCI_RSVD6_OFF                         (12)
  #define UNCORE_CR_DEBUP1_0_0_0_PCI_RSVD6_WID                         ( 3)
  #define UNCORE_CR_DEBUP1_0_0_0_PCI_RSVD6_MSK                         (0x00007000)
  #define UNCORE_CR_DEBUP1_0_0_0_PCI_RSVD6_MAX                         (0x00000007)
  #define UNCORE_CR_DEBUP1_0_0_0_PCI_RSVD6_DEF                         (0x00000000)
  #define UNCORE_CR_DEBUP1_0_0_0_PCI_RSVD7_OFF                         (15)
  #define UNCORE_CR_DEBUP1_0_0_0_PCI_RSVD7_WID                         ( 1)
  #define UNCORE_CR_DEBUP1_0_0_0_PCI_RSVD7_MSK                         (0x00008000)
  #define UNCORE_CR_DEBUP1_0_0_0_PCI_RSVD7_MAX                         (0x00000001)
  #define UNCORE_CR_DEBUP1_0_0_0_PCI_RSVD7_DEF                         (0x00000000)
  #define UNCORE_CR_DEBUP1_0_0_0_PCI_RSVD8_OFF                         (16)
  #define UNCORE_CR_DEBUP1_0_0_0_PCI_RSVD8_WID                         ( 3)
  #define UNCORE_CR_DEBUP1_0_0_0_PCI_RSVD8_MSK                         (0x00070000)
  #define UNCORE_CR_DEBUP1_0_0_0_PCI_RSVD8_MAX                         (0x00000007)
  #define UNCORE_CR_DEBUP1_0_0_0_PCI_RSVD8_DEF                         (0x00000000)
  #define UNCORE_CR_DEBUP1_0_0_0_PCI_RSVD9_OFF                         (19)
  #define UNCORE_CR_DEBUP1_0_0_0_PCI_RSVD9_WID                         ( 1)
  #define UNCORE_CR_DEBUP1_0_0_0_PCI_RSVD9_MSK                         (0x00080000)
  #define UNCORE_CR_DEBUP1_0_0_0_PCI_RSVD9_MAX                         (0x00000001)
  #define UNCORE_CR_DEBUP1_0_0_0_PCI_RSVD9_DEF                         (0x00000000)
  #define UNCORE_CR_DEBUP1_0_0_0_PCI_RSVD10_OFF                        (20)
  #define UNCORE_CR_DEBUP1_0_0_0_PCI_RSVD10_WID                        (12)
  #define UNCORE_CR_DEBUP1_0_0_0_PCI_RSVD10_MSK                        (0xFFF00000)
  #define UNCORE_CR_DEBUP1_0_0_0_PCI_RSVD10_MAX                        (0x00000FFF)
  #define UNCORE_CR_DEBUP1_0_0_0_PCI_RSVD10_DEF                        (0x00000000)

#pragma pack(pop)
#endif  // __Pci000_h__
