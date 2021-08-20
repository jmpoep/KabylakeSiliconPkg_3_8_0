#ifndef __MrcMcRegister5xxx_h__
#define __MrcMcRegister5xxx_h__
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


#define MCDECS_CR_MAD_INTER_CHANNEL_MCMAIN_REG                         (0x00005000)

  #define MCDECS_CR_MAD_INTER_CHANNEL_MCMAIN_DDR_TYPE_OFF              ( 0)
  #define MCDECS_CR_MAD_INTER_CHANNEL_MCMAIN_DDR_TYPE_WID              ( 2)
  #define MCDECS_CR_MAD_INTER_CHANNEL_MCMAIN_DDR_TYPE_MSK              (0x00000003)
  #define MCDECS_CR_MAD_INTER_CHANNEL_MCMAIN_DDR_TYPE_MIN              (0)
  #define MCDECS_CR_MAD_INTER_CHANNEL_MCMAIN_DDR_TYPE_MAX              (3) // 0x00000003
  #define MCDECS_CR_MAD_INTER_CHANNEL_MCMAIN_DDR_TYPE_DEF              (0x00000000)
  #define MCDECS_CR_MAD_INTER_CHANNEL_MCMAIN_DDR_TYPE_HSH              (0x02005000)

  #define MCDECS_CR_MAD_INTER_CHANNEL_MCMAIN_CH_L_MAP_OFF              ( 4)
  #define MCDECS_CR_MAD_INTER_CHANNEL_MCMAIN_CH_L_MAP_WID              ( 1)
  #define MCDECS_CR_MAD_INTER_CHANNEL_MCMAIN_CH_L_MAP_MSK              (0x00000010)
  #define MCDECS_CR_MAD_INTER_CHANNEL_MCMAIN_CH_L_MAP_MIN              (0)
  #define MCDECS_CR_MAD_INTER_CHANNEL_MCMAIN_CH_L_MAP_MAX              (1) // 0x00000001
  #define MCDECS_CR_MAD_INTER_CHANNEL_MCMAIN_CH_L_MAP_DEF              (0x00000000)
  #define MCDECS_CR_MAD_INTER_CHANNEL_MCMAIN_CH_L_MAP_HSH              (0x01045000)

  #define MCDECS_CR_MAD_INTER_CHANNEL_MCMAIN_STKD_MODE_OFF             ( 8)
  #define MCDECS_CR_MAD_INTER_CHANNEL_MCMAIN_STKD_MODE_WID             ( 1)
  #define MCDECS_CR_MAD_INTER_CHANNEL_MCMAIN_STKD_MODE_MSK             (0x00000100)
  #define MCDECS_CR_MAD_INTER_CHANNEL_MCMAIN_STKD_MODE_MIN             (0)
  #define MCDECS_CR_MAD_INTER_CHANNEL_MCMAIN_STKD_MODE_MAX             (1) // 0x00000001
  #define MCDECS_CR_MAD_INTER_CHANNEL_MCMAIN_STKD_MODE_DEF             (0x00000000)
  #define MCDECS_CR_MAD_INTER_CHANNEL_MCMAIN_STKD_MODE_HSH             (0x01085000)

  #define MCDECS_CR_MAD_INTER_CHANNEL_MCMAIN_STKD_MODE_CH1_OFF         ( 9)
  #define MCDECS_CR_MAD_INTER_CHANNEL_MCMAIN_STKD_MODE_CH1_WID         ( 1)
  #define MCDECS_CR_MAD_INTER_CHANNEL_MCMAIN_STKD_MODE_CH1_MSK         (0x00000200)
  #define MCDECS_CR_MAD_INTER_CHANNEL_MCMAIN_STKD_MODE_CH1_MIN         (0)
  #define MCDECS_CR_MAD_INTER_CHANNEL_MCMAIN_STKD_MODE_CH1_MAX         (1) // 0x00000001
  #define MCDECS_CR_MAD_INTER_CHANNEL_MCMAIN_STKD_MODE_CH1_DEF         (0x00000000)
  #define MCDECS_CR_MAD_INTER_CHANNEL_MCMAIN_STKD_MODE_CH1_HSH         (0x01095000)

  #define MCDECS_CR_MAD_INTER_CHANNEL_MCMAIN_CH_S_SIZE_OFF             (12)
  #define MCDECS_CR_MAD_INTER_CHANNEL_MCMAIN_CH_S_SIZE_WID             ( 7)
  #define MCDECS_CR_MAD_INTER_CHANNEL_MCMAIN_CH_S_SIZE_MSK             (0x0007F000)
  #define MCDECS_CR_MAD_INTER_CHANNEL_MCMAIN_CH_S_SIZE_MIN             (0)
  #define MCDECS_CR_MAD_INTER_CHANNEL_MCMAIN_CH_S_SIZE_MAX             (127) // 0x0000007F
  #define MCDECS_CR_MAD_INTER_CHANNEL_MCMAIN_CH_S_SIZE_DEF             (0x00000000)
  #define MCDECS_CR_MAD_INTER_CHANNEL_MCMAIN_CH_S_SIZE_HSH             (0x070C5000)

  #define MCDECS_CR_MAD_INTER_CHANNEL_MCMAIN_STKD_MODE_CH_BITS_OFF     (24)
  #define MCDECS_CR_MAD_INTER_CHANNEL_MCMAIN_STKD_MODE_CH_BITS_WID     ( 3)
  #define MCDECS_CR_MAD_INTER_CHANNEL_MCMAIN_STKD_MODE_CH_BITS_MSK     (0x07000000)
  #define MCDECS_CR_MAD_INTER_CHANNEL_MCMAIN_STKD_MODE_CH_BITS_MIN     (0)
  #define MCDECS_CR_MAD_INTER_CHANNEL_MCMAIN_STKD_MODE_CH_BITS_MAX     (7) // 0x00000007
  #define MCDECS_CR_MAD_INTER_CHANNEL_MCMAIN_STKD_MODE_CH_BITS_DEF     (0x00000000)
  #define MCDECS_CR_MAD_INTER_CHANNEL_MCMAIN_STKD_MODE_CH_BITS_HSH     (0x03185000)

#define MCDECS_CR_MAD_INTRA_CH0_MCMAIN_REG                             (0x00005004)

  #define MCDECS_CR_MAD_INTRA_CH0_MCMAIN_DIMM_L_MAP_OFF                ( 0)
  #define MCDECS_CR_MAD_INTRA_CH0_MCMAIN_DIMM_L_MAP_WID                ( 1)
  #define MCDECS_CR_MAD_INTRA_CH0_MCMAIN_DIMM_L_MAP_MSK                (0x00000001)
  #define MCDECS_CR_MAD_INTRA_CH0_MCMAIN_DIMM_L_MAP_MIN                (0)
  #define MCDECS_CR_MAD_INTRA_CH0_MCMAIN_DIMM_L_MAP_MAX                (1) // 0x00000001
  #define MCDECS_CR_MAD_INTRA_CH0_MCMAIN_DIMM_L_MAP_DEF                (0x00000000)
  #define MCDECS_CR_MAD_INTRA_CH0_MCMAIN_DIMM_L_MAP_HSH                (0x01005004)

  #define MCDECS_CR_MAD_INTRA_CH0_MCMAIN_RI_OFF                        ( 4)
  #define MCDECS_CR_MAD_INTRA_CH0_MCMAIN_RI_WID                        ( 1)
  #define MCDECS_CR_MAD_INTRA_CH0_MCMAIN_RI_MSK                        (0x00000010)
  #define MCDECS_CR_MAD_INTRA_CH0_MCMAIN_RI_MIN                        (0)
  #define MCDECS_CR_MAD_INTRA_CH0_MCMAIN_RI_MAX                        (1) // 0x00000001
  #define MCDECS_CR_MAD_INTRA_CH0_MCMAIN_RI_DEF                        (0x00000000)
  #define MCDECS_CR_MAD_INTRA_CH0_MCMAIN_RI_HSH                        (0x01045004)

  #define MCDECS_CR_MAD_INTRA_CH0_MCMAIN_EIM_OFF                       ( 8)
  #define MCDECS_CR_MAD_INTRA_CH0_MCMAIN_EIM_WID                       ( 1)
  #define MCDECS_CR_MAD_INTRA_CH0_MCMAIN_EIM_MSK                       (0x00000100)
  #define MCDECS_CR_MAD_INTRA_CH0_MCMAIN_EIM_MIN                       (0)
  #define MCDECS_CR_MAD_INTRA_CH0_MCMAIN_EIM_MAX                       (1) // 0x00000001
  #define MCDECS_CR_MAD_INTRA_CH0_MCMAIN_EIM_DEF                       (0x00000000)
  #define MCDECS_CR_MAD_INTRA_CH0_MCMAIN_EIM_HSH                       (0x01085004)

  #define MCDECS_CR_MAD_INTRA_CH0_MCMAIN_ECC_OFF                       (12)
  #define MCDECS_CR_MAD_INTRA_CH0_MCMAIN_ECC_WID                       ( 2)
  #define MCDECS_CR_MAD_INTRA_CH0_MCMAIN_ECC_MSK                       (0x00003000)
  #define MCDECS_CR_MAD_INTRA_CH0_MCMAIN_ECC_MIN                       (0)
  #define MCDECS_CR_MAD_INTRA_CH0_MCMAIN_ECC_MAX                       (3) // 0x00000003
  #define MCDECS_CR_MAD_INTRA_CH0_MCMAIN_ECC_DEF                       (0x00000000)
  #define MCDECS_CR_MAD_INTRA_CH0_MCMAIN_ECC_HSH                       (0x020C5004)

  #define MCDECS_CR_MAD_INTRA_CH0_MCMAIN_HORI_OFF                      (24)
  #define MCDECS_CR_MAD_INTRA_CH0_MCMAIN_HORI_WID                      ( 1)
  #define MCDECS_CR_MAD_INTRA_CH0_MCMAIN_HORI_MSK                      (0x01000000)
  #define MCDECS_CR_MAD_INTRA_CH0_MCMAIN_HORI_MIN                      (0)
  #define MCDECS_CR_MAD_INTRA_CH0_MCMAIN_HORI_MAX                      (1) // 0x00000001
  #define MCDECS_CR_MAD_INTRA_CH0_MCMAIN_HORI_DEF                      (0x00000000)
  #define MCDECS_CR_MAD_INTRA_CH0_MCMAIN_HORI_HSH                      (0x01185004)

  #define MCDECS_CR_MAD_INTRA_CH0_MCMAIN_HORI_ADDR_OFF                 (28)
  #define MCDECS_CR_MAD_INTRA_CH0_MCMAIN_HORI_ADDR_WID                 ( 3)
  #define MCDECS_CR_MAD_INTRA_CH0_MCMAIN_HORI_ADDR_MSK                 (0x70000000)
  #define MCDECS_CR_MAD_INTRA_CH0_MCMAIN_HORI_ADDR_MIN                 (0)
  #define MCDECS_CR_MAD_INTRA_CH0_MCMAIN_HORI_ADDR_MAX                 (7) // 0x00000007
  #define MCDECS_CR_MAD_INTRA_CH0_MCMAIN_HORI_ADDR_DEF                 (0x00000000)
  #define MCDECS_CR_MAD_INTRA_CH0_MCMAIN_HORI_ADDR_HSH                 (0x031C5004)

#define MCDECS_CR_MAD_INTRA_CH1_MCMAIN_REG                             (0x00005008)

  #define MCDECS_CR_MAD_INTRA_CH1_MCMAIN_DIMM_L_MAP_OFF                ( 0)
  #define MCDECS_CR_MAD_INTRA_CH1_MCMAIN_DIMM_L_MAP_WID                ( 1)
  #define MCDECS_CR_MAD_INTRA_CH1_MCMAIN_DIMM_L_MAP_MSK                (0x00000001)
  #define MCDECS_CR_MAD_INTRA_CH1_MCMAIN_DIMM_L_MAP_MIN                (0)
  #define MCDECS_CR_MAD_INTRA_CH1_MCMAIN_DIMM_L_MAP_MAX                (1) // 0x00000001
  #define MCDECS_CR_MAD_INTRA_CH1_MCMAIN_DIMM_L_MAP_DEF                (0x00000000)
  #define MCDECS_CR_MAD_INTRA_CH1_MCMAIN_DIMM_L_MAP_HSH                (0x01005008)

  #define MCDECS_CR_MAD_INTRA_CH1_MCMAIN_RI_OFF                        ( 4)
  #define MCDECS_CR_MAD_INTRA_CH1_MCMAIN_RI_WID                        ( 1)
  #define MCDECS_CR_MAD_INTRA_CH1_MCMAIN_RI_MSK                        (0x00000010)
  #define MCDECS_CR_MAD_INTRA_CH1_MCMAIN_RI_MIN                        (0)
  #define MCDECS_CR_MAD_INTRA_CH1_MCMAIN_RI_MAX                        (1) // 0x00000001
  #define MCDECS_CR_MAD_INTRA_CH1_MCMAIN_RI_DEF                        (0x00000000)
  #define MCDECS_CR_MAD_INTRA_CH1_MCMAIN_RI_HSH                        (0x01045008)

  #define MCDECS_CR_MAD_INTRA_CH1_MCMAIN_EIM_OFF                       ( 8)
  #define MCDECS_CR_MAD_INTRA_CH1_MCMAIN_EIM_WID                       ( 1)
  #define MCDECS_CR_MAD_INTRA_CH1_MCMAIN_EIM_MSK                       (0x00000100)
  #define MCDECS_CR_MAD_INTRA_CH1_MCMAIN_EIM_MIN                       (0)
  #define MCDECS_CR_MAD_INTRA_CH1_MCMAIN_EIM_MAX                       (1) // 0x00000001
  #define MCDECS_CR_MAD_INTRA_CH1_MCMAIN_EIM_DEF                       (0x00000000)
  #define MCDECS_CR_MAD_INTRA_CH1_MCMAIN_EIM_HSH                       (0x01085008)

  #define MCDECS_CR_MAD_INTRA_CH1_MCMAIN_ECC_OFF                       (12)
  #define MCDECS_CR_MAD_INTRA_CH1_MCMAIN_ECC_WID                       ( 2)
  #define MCDECS_CR_MAD_INTRA_CH1_MCMAIN_ECC_MSK                       (0x00003000)
  #define MCDECS_CR_MAD_INTRA_CH1_MCMAIN_ECC_MIN                       (0)
  #define MCDECS_CR_MAD_INTRA_CH1_MCMAIN_ECC_MAX                       (3) // 0x00000003
  #define MCDECS_CR_MAD_INTRA_CH1_MCMAIN_ECC_DEF                       (0x00000000)
  #define MCDECS_CR_MAD_INTRA_CH1_MCMAIN_ECC_HSH                       (0x020C5008)

  #define MCDECS_CR_MAD_INTRA_CH1_MCMAIN_HORI_OFF                      (24)
  #define MCDECS_CR_MAD_INTRA_CH1_MCMAIN_HORI_WID                      ( 1)
  #define MCDECS_CR_MAD_INTRA_CH1_MCMAIN_HORI_MSK                      (0x01000000)
  #define MCDECS_CR_MAD_INTRA_CH1_MCMAIN_HORI_MIN                      (0)
  #define MCDECS_CR_MAD_INTRA_CH1_MCMAIN_HORI_MAX                      (1) // 0x00000001
  #define MCDECS_CR_MAD_INTRA_CH1_MCMAIN_HORI_DEF                      (0x00000000)
  #define MCDECS_CR_MAD_INTRA_CH1_MCMAIN_HORI_HSH                      (0x01185008)

  #define MCDECS_CR_MAD_INTRA_CH1_MCMAIN_HORI_ADDR_OFF                 (28)
  #define MCDECS_CR_MAD_INTRA_CH1_MCMAIN_HORI_ADDR_WID                 ( 3)
  #define MCDECS_CR_MAD_INTRA_CH1_MCMAIN_HORI_ADDR_MSK                 (0x70000000)
  #define MCDECS_CR_MAD_INTRA_CH1_MCMAIN_HORI_ADDR_MIN                 (0)
  #define MCDECS_CR_MAD_INTRA_CH1_MCMAIN_HORI_ADDR_MAX                 (7) // 0x00000007
  #define MCDECS_CR_MAD_INTRA_CH1_MCMAIN_HORI_ADDR_DEF                 (0x00000000)
  #define MCDECS_CR_MAD_INTRA_CH1_MCMAIN_HORI_ADDR_HSH                 (0x031C5008)

#define MCDECS_CR_MAD_DIMM_CH0_MCMAIN_REG                              (0x0000500C)

  #define MCDECS_CR_MAD_DIMM_CH0_MCMAIN_DIMM_L_SIZE_OFF                ( 0)
  #define MCDECS_CR_MAD_DIMM_CH0_MCMAIN_DIMM_L_SIZE_WID                ( 6)
  #define MCDECS_CR_MAD_DIMM_CH0_MCMAIN_DIMM_L_SIZE_MSK                (0x0000003F)
  #define MCDECS_CR_MAD_DIMM_CH0_MCMAIN_DIMM_L_SIZE_MIN                (0)
  #define MCDECS_CR_MAD_DIMM_CH0_MCMAIN_DIMM_L_SIZE_MAX                (63) // 0x0000003F
  #define MCDECS_CR_MAD_DIMM_CH0_MCMAIN_DIMM_L_SIZE_DEF                (0x00000000)
  #define MCDECS_CR_MAD_DIMM_CH0_MCMAIN_DIMM_L_SIZE_HSH                (0x0600500C)

  #define MCDECS_CR_MAD_DIMM_CH0_MCMAIN_DLW_OFF                        ( 8)
  #define MCDECS_CR_MAD_DIMM_CH0_MCMAIN_DLW_WID                        ( 2)
  #define MCDECS_CR_MAD_DIMM_CH0_MCMAIN_DLW_MSK                        (0x00000300)
  #define MCDECS_CR_MAD_DIMM_CH0_MCMAIN_DLW_MIN                        (0)
  #define MCDECS_CR_MAD_DIMM_CH0_MCMAIN_DLW_MAX                        (3) // 0x00000003
  #define MCDECS_CR_MAD_DIMM_CH0_MCMAIN_DLW_DEF                        (0x00000000)
  #define MCDECS_CR_MAD_DIMM_CH0_MCMAIN_DLW_HSH                        (0x0208500C)

  #define MCDECS_CR_MAD_DIMM_CH0_MCMAIN_DLNOR_OFF                      (10)
  #define MCDECS_CR_MAD_DIMM_CH0_MCMAIN_DLNOR_WID                      ( 1)
  #define MCDECS_CR_MAD_DIMM_CH0_MCMAIN_DLNOR_MSK                      (0x00000400)
  #define MCDECS_CR_MAD_DIMM_CH0_MCMAIN_DLNOR_MIN                      (0)
  #define MCDECS_CR_MAD_DIMM_CH0_MCMAIN_DLNOR_MAX                      (1) // 0x00000001
  #define MCDECS_CR_MAD_DIMM_CH0_MCMAIN_DLNOR_DEF                      (0x00000000)
  #define MCDECS_CR_MAD_DIMM_CH0_MCMAIN_DLNOR_HSH                      (0x010A500C)

  #define MCDECS_CR_MAD_DIMM_CH0_MCMAIN_DL8Gb_OFF                      (11)
  #define MCDECS_CR_MAD_DIMM_CH0_MCMAIN_DL8Gb_WID                      ( 1)
  #define MCDECS_CR_MAD_DIMM_CH0_MCMAIN_DL8Gb_MSK                      (0x00000800)
  #define MCDECS_CR_MAD_DIMM_CH0_MCMAIN_DL8Gb_MIN                      (0)
  #define MCDECS_CR_MAD_DIMM_CH0_MCMAIN_DL8Gb_MAX                      (1) // 0x00000001
  #define MCDECS_CR_MAD_DIMM_CH0_MCMAIN_DL8Gb_DEF                      (0x00000000)
  #define MCDECS_CR_MAD_DIMM_CH0_MCMAIN_DL8Gb_HSH                      (0x010B500C)

  #define MCDECS_CR_MAD_DIMM_CH0_MCMAIN_DIMM_S_SIZE_OFF                (16)
  #define MCDECS_CR_MAD_DIMM_CH0_MCMAIN_DIMM_S_SIZE_WID                ( 6)
  #define MCDECS_CR_MAD_DIMM_CH0_MCMAIN_DIMM_S_SIZE_MSK                (0x003F0000)
  #define MCDECS_CR_MAD_DIMM_CH0_MCMAIN_DIMM_S_SIZE_MIN                (0)
  #define MCDECS_CR_MAD_DIMM_CH0_MCMAIN_DIMM_S_SIZE_MAX                (63) // 0x0000003F
  #define MCDECS_CR_MAD_DIMM_CH0_MCMAIN_DIMM_S_SIZE_DEF                (0x00000000)
  #define MCDECS_CR_MAD_DIMM_CH0_MCMAIN_DIMM_S_SIZE_HSH                (0x0610500C)

  #define MCDECS_CR_MAD_DIMM_CH0_MCMAIN_DSW_OFF                        (24)
  #define MCDECS_CR_MAD_DIMM_CH0_MCMAIN_DSW_WID                        ( 2)
  #define MCDECS_CR_MAD_DIMM_CH0_MCMAIN_DSW_MSK                        (0x03000000)
  #define MCDECS_CR_MAD_DIMM_CH0_MCMAIN_DSW_MIN                        (0)
  #define MCDECS_CR_MAD_DIMM_CH0_MCMAIN_DSW_MAX                        (3) // 0x00000003
  #define MCDECS_CR_MAD_DIMM_CH0_MCMAIN_DSW_DEF                        (0x00000000)
  #define MCDECS_CR_MAD_DIMM_CH0_MCMAIN_DSW_HSH                        (0x0218500C)

  #define MCDECS_CR_MAD_DIMM_CH0_MCMAIN_DSNOR_OFF                      (26)
  #define MCDECS_CR_MAD_DIMM_CH0_MCMAIN_DSNOR_WID                      ( 1)
  #define MCDECS_CR_MAD_DIMM_CH0_MCMAIN_DSNOR_MSK                      (0x04000000)
  #define MCDECS_CR_MAD_DIMM_CH0_MCMAIN_DSNOR_MIN                      (0)
  #define MCDECS_CR_MAD_DIMM_CH0_MCMAIN_DSNOR_MAX                      (1) // 0x00000001
  #define MCDECS_CR_MAD_DIMM_CH0_MCMAIN_DSNOR_DEF                      (0x00000000)
  #define MCDECS_CR_MAD_DIMM_CH0_MCMAIN_DSNOR_HSH                      (0x011A500C)

  #define MCDECS_CR_MAD_DIMM_CH0_MCMAIN_DS8Gb_OFF                      (27)
  #define MCDECS_CR_MAD_DIMM_CH0_MCMAIN_DS8Gb_WID                      ( 1)
  #define MCDECS_CR_MAD_DIMM_CH0_MCMAIN_DS8Gb_MSK                      (0x08000000)
  #define MCDECS_CR_MAD_DIMM_CH0_MCMAIN_DS8Gb_MIN                      (0)
  #define MCDECS_CR_MAD_DIMM_CH0_MCMAIN_DS8Gb_MAX                      (1) // 0x00000001
  #define MCDECS_CR_MAD_DIMM_CH0_MCMAIN_DS8Gb_DEF                      (0x00000000)
  #define MCDECS_CR_MAD_DIMM_CH0_MCMAIN_DS8Gb_HSH                      (0x011B500C)

#define MCDECS_CR_MAD_DIMM_CH1_MCMAIN_REG                              (0x00005010)

  #define MCDECS_CR_MAD_DIMM_CH1_MCMAIN_DIMM_L_SIZE_OFF                ( 0)
  #define MCDECS_CR_MAD_DIMM_CH1_MCMAIN_DIMM_L_SIZE_WID                ( 6)
  #define MCDECS_CR_MAD_DIMM_CH1_MCMAIN_DIMM_L_SIZE_MSK                (0x0000003F)
  #define MCDECS_CR_MAD_DIMM_CH1_MCMAIN_DIMM_L_SIZE_MIN                (0)
  #define MCDECS_CR_MAD_DIMM_CH1_MCMAIN_DIMM_L_SIZE_MAX                (63) // 0x0000003F
  #define MCDECS_CR_MAD_DIMM_CH1_MCMAIN_DIMM_L_SIZE_DEF                (0x00000000)
  #define MCDECS_CR_MAD_DIMM_CH1_MCMAIN_DIMM_L_SIZE_HSH                (0x06005010)

  #define MCDECS_CR_MAD_DIMM_CH1_MCMAIN_DLW_OFF                        ( 8)
  #define MCDECS_CR_MAD_DIMM_CH1_MCMAIN_DLW_WID                        ( 2)
  #define MCDECS_CR_MAD_DIMM_CH1_MCMAIN_DLW_MSK                        (0x00000300)
  #define MCDECS_CR_MAD_DIMM_CH1_MCMAIN_DLW_MIN                        (0)
  #define MCDECS_CR_MAD_DIMM_CH1_MCMAIN_DLW_MAX                        (3) // 0x00000003
  #define MCDECS_CR_MAD_DIMM_CH1_MCMAIN_DLW_DEF                        (0x00000000)
  #define MCDECS_CR_MAD_DIMM_CH1_MCMAIN_DLW_HSH                        (0x02085010)

  #define MCDECS_CR_MAD_DIMM_CH1_MCMAIN_DLNOR_OFF                      (10)
  #define MCDECS_CR_MAD_DIMM_CH1_MCMAIN_DLNOR_WID                      ( 1)
  #define MCDECS_CR_MAD_DIMM_CH1_MCMAIN_DLNOR_MSK                      (0x00000400)
  #define MCDECS_CR_MAD_DIMM_CH1_MCMAIN_DLNOR_MIN                      (0)
  #define MCDECS_CR_MAD_DIMM_CH1_MCMAIN_DLNOR_MAX                      (1) // 0x00000001
  #define MCDECS_CR_MAD_DIMM_CH1_MCMAIN_DLNOR_DEF                      (0x00000000)
  #define MCDECS_CR_MAD_DIMM_CH1_MCMAIN_DLNOR_HSH                      (0x010A5010)

  #define MCDECS_CR_MAD_DIMM_CH1_MCMAIN_DL8Gb_OFF                      (11)
  #define MCDECS_CR_MAD_DIMM_CH1_MCMAIN_DL8Gb_WID                      ( 1)
  #define MCDECS_CR_MAD_DIMM_CH1_MCMAIN_DL8Gb_MSK                      (0x00000800)
  #define MCDECS_CR_MAD_DIMM_CH1_MCMAIN_DL8Gb_MIN                      (0)
  #define MCDECS_CR_MAD_DIMM_CH1_MCMAIN_DL8Gb_MAX                      (1) // 0x00000001
  #define MCDECS_CR_MAD_DIMM_CH1_MCMAIN_DL8Gb_DEF                      (0x00000000)
  #define MCDECS_CR_MAD_DIMM_CH1_MCMAIN_DL8Gb_HSH                      (0x010B5010)

  #define MCDECS_CR_MAD_DIMM_CH1_MCMAIN_DIMM_S_SIZE_OFF                (16)
  #define MCDECS_CR_MAD_DIMM_CH1_MCMAIN_DIMM_S_SIZE_WID                ( 6)
  #define MCDECS_CR_MAD_DIMM_CH1_MCMAIN_DIMM_S_SIZE_MSK                (0x003F0000)
  #define MCDECS_CR_MAD_DIMM_CH1_MCMAIN_DIMM_S_SIZE_MIN                (0)
  #define MCDECS_CR_MAD_DIMM_CH1_MCMAIN_DIMM_S_SIZE_MAX                (63) // 0x0000003F
  #define MCDECS_CR_MAD_DIMM_CH1_MCMAIN_DIMM_S_SIZE_DEF                (0x00000000)
  #define MCDECS_CR_MAD_DIMM_CH1_MCMAIN_DIMM_S_SIZE_HSH                (0x06105010)

  #define MCDECS_CR_MAD_DIMM_CH1_MCMAIN_DSW_OFF                        (24)
  #define MCDECS_CR_MAD_DIMM_CH1_MCMAIN_DSW_WID                        ( 2)
  #define MCDECS_CR_MAD_DIMM_CH1_MCMAIN_DSW_MSK                        (0x03000000)
  #define MCDECS_CR_MAD_DIMM_CH1_MCMAIN_DSW_MIN                        (0)
  #define MCDECS_CR_MAD_DIMM_CH1_MCMAIN_DSW_MAX                        (3) // 0x00000003
  #define MCDECS_CR_MAD_DIMM_CH1_MCMAIN_DSW_DEF                        (0x00000000)
  #define MCDECS_CR_MAD_DIMM_CH1_MCMAIN_DSW_HSH                        (0x02185010)

  #define MCDECS_CR_MAD_DIMM_CH1_MCMAIN_DSNOR_OFF                      (26)
  #define MCDECS_CR_MAD_DIMM_CH1_MCMAIN_DSNOR_WID                      ( 1)
  #define MCDECS_CR_MAD_DIMM_CH1_MCMAIN_DSNOR_MSK                      (0x04000000)
  #define MCDECS_CR_MAD_DIMM_CH1_MCMAIN_DSNOR_MIN                      (0)
  #define MCDECS_CR_MAD_DIMM_CH1_MCMAIN_DSNOR_MAX                      (1) // 0x00000001
  #define MCDECS_CR_MAD_DIMM_CH1_MCMAIN_DSNOR_DEF                      (0x00000000)
  #define MCDECS_CR_MAD_DIMM_CH1_MCMAIN_DSNOR_HSH                      (0x011A5010)

  #define MCDECS_CR_MAD_DIMM_CH1_MCMAIN_DS8Gb_OFF                      (27)
  #define MCDECS_CR_MAD_DIMM_CH1_MCMAIN_DS8Gb_WID                      ( 1)
  #define MCDECS_CR_MAD_DIMM_CH1_MCMAIN_DS8Gb_MSK                      (0x08000000)
  #define MCDECS_CR_MAD_DIMM_CH1_MCMAIN_DS8Gb_MIN                      (0)
  #define MCDECS_CR_MAD_DIMM_CH1_MCMAIN_DS8Gb_MAX                      (1) // 0x00000001
  #define MCDECS_CR_MAD_DIMM_CH1_MCMAIN_DS8Gb_DEF                      (0x00000000)
  #define MCDECS_CR_MAD_DIMM_CH1_MCMAIN_DS8Gb_HSH                      (0x011B5010)

#define MCDECS_CR_MCDECS_MISC_MCMAIN_REG                               (0x00005018)

  #define MCDECS_CR_MCDECS_MISC_MCMAIN_Spare_RW_OFF                    ( 0)
  #define MCDECS_CR_MCDECS_MISC_MCMAIN_Spare_RW_WID                    (16)
  #define MCDECS_CR_MCDECS_MISC_MCMAIN_Spare_RW_MSK                    (0x0000FFFF)
  #define MCDECS_CR_MCDECS_MISC_MCMAIN_Spare_RW_MIN                    (0)
  #define MCDECS_CR_MCDECS_MISC_MCMAIN_Spare_RW_MAX                    (65535) // 0x0000FFFF
  #define MCDECS_CR_MCDECS_MISC_MCMAIN_Spare_RW_DEF                    (0x00000000)
  #define MCDECS_CR_MCDECS_MISC_MCMAIN_Spare_RW_HSH                    (0x10005018)

  #define MCDECS_CR_MCDECS_MISC_MCMAIN_spare_RW_V_OFF                  (16)
  #define MCDECS_CR_MCDECS_MISC_MCMAIN_spare_RW_V_WID                  (16)
  #define MCDECS_CR_MCDECS_MISC_MCMAIN_spare_RW_V_MSK                  (0xFFFF0000)
  #define MCDECS_CR_MCDECS_MISC_MCMAIN_spare_RW_V_MIN                  (0)
  #define MCDECS_CR_MCDECS_MISC_MCMAIN_spare_RW_V_MAX                  (65535) // 0x0000FFFF
  #define MCDECS_CR_MCDECS_MISC_MCMAIN_spare_RW_V_DEF                  (0x00000000)
  #define MCDECS_CR_MCDECS_MISC_MCMAIN_spare_RW_V_HSH                  (0x10105018)

#define MCDECS_CR_MCDECS_CBIT_MCMAIN_REG                               (0x0000501C)

  #define MCDECS_CR_MCDECS_CBIT_MCMAIN_increase_rcomp_OFF              ( 0)
  #define MCDECS_CR_MCDECS_CBIT_MCMAIN_increase_rcomp_WID              ( 1)
  #define MCDECS_CR_MCDECS_CBIT_MCMAIN_increase_rcomp_MSK              (0x00000001)
  #define MCDECS_CR_MCDECS_CBIT_MCMAIN_increase_rcomp_MIN              (0)
  #define MCDECS_CR_MCDECS_CBIT_MCMAIN_increase_rcomp_MAX              (1) // 0x00000001
  #define MCDECS_CR_MCDECS_CBIT_MCMAIN_increase_rcomp_DEF              (0x00000000)
  #define MCDECS_CR_MCDECS_CBIT_MCMAIN_increase_rcomp_HSH              (0x0100501C)

  #define MCDECS_CR_MCDECS_CBIT_MCMAIN_rank2_to_rank1_OFF              ( 1)
  #define MCDECS_CR_MCDECS_CBIT_MCMAIN_rank2_to_rank1_WID              ( 1)
  #define MCDECS_CR_MCDECS_CBIT_MCMAIN_rank2_to_rank1_MSK              (0x00000002)
  #define MCDECS_CR_MCDECS_CBIT_MCMAIN_rank2_to_rank1_MIN              (0)
  #define MCDECS_CR_MCDECS_CBIT_MCMAIN_rank2_to_rank1_MAX              (1) // 0x00000001
  #define MCDECS_CR_MCDECS_CBIT_MCMAIN_rank2_to_rank1_DEF              (0x00000000)
  #define MCDECS_CR_MCDECS_CBIT_MCMAIN_rank2_to_rank1_HSH              (0x0101501C)

  #define MCDECS_CR_MCDECS_CBIT_MCMAIN_ovrd_pcu_sr_exit_OFF            ( 2)
  #define MCDECS_CR_MCDECS_CBIT_MCMAIN_ovrd_pcu_sr_exit_WID            ( 1)
  #define MCDECS_CR_MCDECS_CBIT_MCMAIN_ovrd_pcu_sr_exit_MSK            (0x00000004)
  #define MCDECS_CR_MCDECS_CBIT_MCMAIN_ovrd_pcu_sr_exit_MIN            (0)
  #define MCDECS_CR_MCDECS_CBIT_MCMAIN_ovrd_pcu_sr_exit_MAX            (1) // 0x00000001
  #define MCDECS_CR_MCDECS_CBIT_MCMAIN_ovrd_pcu_sr_exit_DEF            (0x00000000)
  #define MCDECS_CR_MCDECS_CBIT_MCMAIN_ovrd_pcu_sr_exit_HSH            (0x0102501C)

  #define MCDECS_CR_MCDECS_CBIT_MCMAIN_psmi_freeze_pwm_counters_OFF    ( 3)
  #define MCDECS_CR_MCDECS_CBIT_MCMAIN_psmi_freeze_pwm_counters_WID    ( 1)
  #define MCDECS_CR_MCDECS_CBIT_MCMAIN_psmi_freeze_pwm_counters_MSK    (0x00000008)
  #define MCDECS_CR_MCDECS_CBIT_MCMAIN_psmi_freeze_pwm_counters_MIN    (0)
  #define MCDECS_CR_MCDECS_CBIT_MCMAIN_psmi_freeze_pwm_counters_MAX    (1) // 0x00000001
  #define MCDECS_CR_MCDECS_CBIT_MCMAIN_psmi_freeze_pwm_counters_DEF    (0x00000000)
  #define MCDECS_CR_MCDECS_CBIT_MCMAIN_psmi_freeze_pwm_counters_HSH    (0x0103501C)

  #define MCDECS_CR_MCDECS_CBIT_MCMAIN_dis_single_ch_sr_OFF            ( 4)
  #define MCDECS_CR_MCDECS_CBIT_MCMAIN_dis_single_ch_sr_WID            ( 1)
  #define MCDECS_CR_MCDECS_CBIT_MCMAIN_dis_single_ch_sr_MSK            (0x00000010)
  #define MCDECS_CR_MCDECS_CBIT_MCMAIN_dis_single_ch_sr_MIN            (0)
  #define MCDECS_CR_MCDECS_CBIT_MCMAIN_dis_single_ch_sr_MAX            (1) // 0x00000001
  #define MCDECS_CR_MCDECS_CBIT_MCMAIN_dis_single_ch_sr_DEF            (0x00000001)
  #define MCDECS_CR_MCDECS_CBIT_MCMAIN_dis_single_ch_sr_HSH            (0x0104501C)

  #define MCDECS_CR_MCDECS_CBIT_MCMAIN_dis_other_ch_stolen_ref_OFF     ( 5)
  #define MCDECS_CR_MCDECS_CBIT_MCMAIN_dis_other_ch_stolen_ref_WID     ( 1)
  #define MCDECS_CR_MCDECS_CBIT_MCMAIN_dis_other_ch_stolen_ref_MSK     (0x00000020)
  #define MCDECS_CR_MCDECS_CBIT_MCMAIN_dis_other_ch_stolen_ref_MIN     (0)
  #define MCDECS_CR_MCDECS_CBIT_MCMAIN_dis_other_ch_stolen_ref_MAX     (1) // 0x00000001
  #define MCDECS_CR_MCDECS_CBIT_MCMAIN_dis_other_ch_stolen_ref_DEF     (0x00000001)
  #define MCDECS_CR_MCDECS_CBIT_MCMAIN_dis_other_ch_stolen_ref_HSH     (0x0105501C)

  #define MCDECS_CR_MCDECS_CBIT_MCMAIN_dis_iosf_sb_clk_gate_OFF        (27)
  #define MCDECS_CR_MCDECS_CBIT_MCMAIN_dis_iosf_sb_clk_gate_WID        ( 1)
  #define MCDECS_CR_MCDECS_CBIT_MCMAIN_dis_iosf_sb_clk_gate_MSK        (0x08000000)
  #define MCDECS_CR_MCDECS_CBIT_MCMAIN_dis_iosf_sb_clk_gate_MIN        (0)
  #define MCDECS_CR_MCDECS_CBIT_MCMAIN_dis_iosf_sb_clk_gate_MAX        (1) // 0x00000001
  #define MCDECS_CR_MCDECS_CBIT_MCMAIN_dis_iosf_sb_clk_gate_DEF        (0x00000000)
  #define MCDECS_CR_MCDECS_CBIT_MCMAIN_dis_iosf_sb_clk_gate_HSH        (0x011B501C)

  #define MCDECS_CR_MCDECS_CBIT_MCMAIN_dis_glbdrv_clk_gate_OFF         (28)
  #define MCDECS_CR_MCDECS_CBIT_MCMAIN_dis_glbdrv_clk_gate_WID         ( 1)
  #define MCDECS_CR_MCDECS_CBIT_MCMAIN_dis_glbdrv_clk_gate_MSK         (0x10000000)
  #define MCDECS_CR_MCDECS_CBIT_MCMAIN_dis_glbdrv_clk_gate_MIN         (0)
  #define MCDECS_CR_MCDECS_CBIT_MCMAIN_dis_glbdrv_clk_gate_MAX         (1) // 0x00000001
  #define MCDECS_CR_MCDECS_CBIT_MCMAIN_dis_glbdrv_clk_gate_DEF         (0x00000000)
  #define MCDECS_CR_MCDECS_CBIT_MCMAIN_dis_glbdrv_clk_gate_HSH         (0x011C501C)

  #define MCDECS_CR_MCDECS_CBIT_MCMAIN_dis_reg_clk_gate_OFF            (29)
  #define MCDECS_CR_MCDECS_CBIT_MCMAIN_dis_reg_clk_gate_WID            ( 1)
  #define MCDECS_CR_MCDECS_CBIT_MCMAIN_dis_reg_clk_gate_MSK            (0x20000000)
  #define MCDECS_CR_MCDECS_CBIT_MCMAIN_dis_reg_clk_gate_MIN            (0)
  #define MCDECS_CR_MCDECS_CBIT_MCMAIN_dis_reg_clk_gate_MAX            (1) // 0x00000001
  #define MCDECS_CR_MCDECS_CBIT_MCMAIN_dis_reg_clk_gate_DEF            (0x00000000)
  #define MCDECS_CR_MCDECS_CBIT_MCMAIN_dis_reg_clk_gate_HSH            (0x011D501C)

  #define MCDECS_CR_MCDECS_CBIT_MCMAIN_dis_msg_clk_gate_OFF            (30)
  #define MCDECS_CR_MCDECS_CBIT_MCMAIN_dis_msg_clk_gate_WID            ( 1)
  #define MCDECS_CR_MCDECS_CBIT_MCMAIN_dis_msg_clk_gate_MSK            (0x40000000)
  #define MCDECS_CR_MCDECS_CBIT_MCMAIN_dis_msg_clk_gate_MIN            (0)
  #define MCDECS_CR_MCDECS_CBIT_MCMAIN_dis_msg_clk_gate_MAX            (1) // 0x00000001
  #define MCDECS_CR_MCDECS_CBIT_MCMAIN_dis_msg_clk_gate_DEF            (0x00000000)
  #define MCDECS_CR_MCDECS_CBIT_MCMAIN_dis_msg_clk_gate_HSH            (0x011E501C)

  #define MCDECS_CR_MCDECS_CBIT_MCMAIN_dis_clk_gate_OFF                (31)
  #define MCDECS_CR_MCDECS_CBIT_MCMAIN_dis_clk_gate_WID                ( 1)
  #define MCDECS_CR_MCDECS_CBIT_MCMAIN_dis_clk_gate_MSK                (0x80000000)
  #define MCDECS_CR_MCDECS_CBIT_MCMAIN_dis_clk_gate_MIN                (0)
  #define MCDECS_CR_MCDECS_CBIT_MCMAIN_dis_clk_gate_MAX                (1) // 0x00000001
  #define MCDECS_CR_MCDECS_CBIT_MCMAIN_dis_clk_gate_DEF                (0x00000000)
  #define MCDECS_CR_MCDECS_CBIT_MCMAIN_dis_clk_gate_HSH                (0x011F501C)

#define MCDECS_CR_CHANNEL_HASH_MCMAIN_REG                              (0x00005024)

  #define MCDECS_CR_CHANNEL_HASH_MCMAIN_HASH_MASK_OFF                  ( 6)
  #define MCDECS_CR_CHANNEL_HASH_MCMAIN_HASH_MASK_WID                  (14)
  #define MCDECS_CR_CHANNEL_HASH_MCMAIN_HASH_MASK_MSK                  (0x000FFFC0)
  #define MCDECS_CR_CHANNEL_HASH_MCMAIN_HASH_MASK_MIN                  (0)
  #define MCDECS_CR_CHANNEL_HASH_MCMAIN_HASH_MASK_MAX                  (16383) // 0x00003FFF
  #define MCDECS_CR_CHANNEL_HASH_MCMAIN_HASH_MASK_DEF                  (0x00000000)
  #define MCDECS_CR_CHANNEL_HASH_MCMAIN_HASH_MASK_HSH                  (0x0E065024)

  #define MCDECS_CR_CHANNEL_HASH_MCMAIN_HASH_LSB_MASK_BIT_OFF          (24)
  #define MCDECS_CR_CHANNEL_HASH_MCMAIN_HASH_LSB_MASK_BIT_WID          ( 3)
  #define MCDECS_CR_CHANNEL_HASH_MCMAIN_HASH_LSB_MASK_BIT_MSK          (0x07000000)
  #define MCDECS_CR_CHANNEL_HASH_MCMAIN_HASH_LSB_MASK_BIT_MIN          (0)
  #define MCDECS_CR_CHANNEL_HASH_MCMAIN_HASH_LSB_MASK_BIT_MAX          (7) // 0x00000007
  #define MCDECS_CR_CHANNEL_HASH_MCMAIN_HASH_LSB_MASK_BIT_DEF          (0x00000000)
  #define MCDECS_CR_CHANNEL_HASH_MCMAIN_HASH_LSB_MASK_BIT_HSH          (0x03185024)

  #define MCDECS_CR_CHANNEL_HASH_MCMAIN_HASH_MODE_OFF                  (28)
  #define MCDECS_CR_CHANNEL_HASH_MCMAIN_HASH_MODE_WID                  ( 1)
  #define MCDECS_CR_CHANNEL_HASH_MCMAIN_HASH_MODE_MSK                  (0x10000000)
  #define MCDECS_CR_CHANNEL_HASH_MCMAIN_HASH_MODE_MIN                  (0)
  #define MCDECS_CR_CHANNEL_HASH_MCMAIN_HASH_MODE_MAX                  (1) // 0x00000001
  #define MCDECS_CR_CHANNEL_HASH_MCMAIN_HASH_MODE_DEF                  (0x00000000)
  #define MCDECS_CR_CHANNEL_HASH_MCMAIN_HASH_MODE_HSH                  (0x011C5024)

#define MCDECS_CR_MC_INIT_STATE_G_MCMAIN_REG                           (0x00005030)

  #define MCDECS_CR_MC_INIT_STATE_G_MCMAIN_pu_mrc_done_OFF             ( 0)
  #define MCDECS_CR_MC_INIT_STATE_G_MCMAIN_pu_mrc_done_WID             ( 1)
  #define MCDECS_CR_MC_INIT_STATE_G_MCMAIN_pu_mrc_done_MSK             (0x00000001)
  #define MCDECS_CR_MC_INIT_STATE_G_MCMAIN_pu_mrc_done_MIN             (0)
  #define MCDECS_CR_MC_INIT_STATE_G_MCMAIN_pu_mrc_done_MAX             (1) // 0x00000001
  #define MCDECS_CR_MC_INIT_STATE_G_MCMAIN_pu_mrc_done_DEF             (0x00000000)
  #define MCDECS_CR_MC_INIT_STATE_G_MCMAIN_pu_mrc_done_HSH             (0x01005030)

  #define MCDECS_CR_MC_INIT_STATE_G_MCMAIN_ddr_reset_OFF               ( 1)
  #define MCDECS_CR_MC_INIT_STATE_G_MCMAIN_ddr_reset_WID               ( 1)
  #define MCDECS_CR_MC_INIT_STATE_G_MCMAIN_ddr_reset_MSK               (0x00000002)
  #define MCDECS_CR_MC_INIT_STATE_G_MCMAIN_ddr_reset_MIN               (0)
  #define MCDECS_CR_MC_INIT_STATE_G_MCMAIN_ddr_reset_MAX               (1) // 0x00000001
  #define MCDECS_CR_MC_INIT_STATE_G_MCMAIN_ddr_reset_DEF               (0x00000001)
  #define MCDECS_CR_MC_INIT_STATE_G_MCMAIN_ddr_reset_HSH               (0x01015030)

  #define MCDECS_CR_MC_INIT_STATE_G_MCMAIN_refresh_enable_OFF          ( 3)
  #define MCDECS_CR_MC_INIT_STATE_G_MCMAIN_refresh_enable_WID          ( 1)
  #define MCDECS_CR_MC_INIT_STATE_G_MCMAIN_refresh_enable_MSK          (0x00000008)
  #define MCDECS_CR_MC_INIT_STATE_G_MCMAIN_refresh_enable_MIN          (0)
  #define MCDECS_CR_MC_INIT_STATE_G_MCMAIN_refresh_enable_MAX          (1) // 0x00000001
  #define MCDECS_CR_MC_INIT_STATE_G_MCMAIN_refresh_enable_DEF          (0x00000000)
  #define MCDECS_CR_MC_INIT_STATE_G_MCMAIN_refresh_enable_HSH          (0x01035030)

  #define MCDECS_CR_MC_INIT_STATE_G_MCMAIN_mc_init_done_ack_OFF        ( 5)
  #define MCDECS_CR_MC_INIT_STATE_G_MCMAIN_mc_init_done_ack_WID        ( 1)
  #define MCDECS_CR_MC_INIT_STATE_G_MCMAIN_mc_init_done_ack_MSK        (0x00000020)
  #define MCDECS_CR_MC_INIT_STATE_G_MCMAIN_mc_init_done_ack_MIN        (0)
  #define MCDECS_CR_MC_INIT_STATE_G_MCMAIN_mc_init_done_ack_MAX        (1) // 0x00000001
  #define MCDECS_CR_MC_INIT_STATE_G_MCMAIN_mc_init_done_ack_DEF        (0x00000000)
  #define MCDECS_CR_MC_INIT_STATE_G_MCMAIN_mc_init_done_ack_HSH        (0x01055030)

  #define MCDECS_CR_MC_INIT_STATE_G_MCMAIN_mrc_done_OFF                ( 7)
  #define MCDECS_CR_MC_INIT_STATE_G_MCMAIN_mrc_done_WID                ( 1)
  #define MCDECS_CR_MC_INIT_STATE_G_MCMAIN_mrc_done_MSK                (0x00000080)
  #define MCDECS_CR_MC_INIT_STATE_G_MCMAIN_mrc_done_MIN                (0)
  #define MCDECS_CR_MC_INIT_STATE_G_MCMAIN_mrc_done_MAX                (1) // 0x00000001
  #define MCDECS_CR_MC_INIT_STATE_G_MCMAIN_mrc_done_DEF                (0x00000000)
  #define MCDECS_CR_MC_INIT_STATE_G_MCMAIN_mrc_done_HSH                (0x01075030)

  #define MCDECS_CR_MC_INIT_STATE_G_MCMAIN_safe_sr_OFF                 ( 8)
  #define MCDECS_CR_MC_INIT_STATE_G_MCMAIN_safe_sr_WID                 ( 1)
  #define MCDECS_CR_MC_INIT_STATE_G_MCMAIN_safe_sr_MSK                 (0x00000100)
  #define MCDECS_CR_MC_INIT_STATE_G_MCMAIN_safe_sr_MIN                 (0)
  #define MCDECS_CR_MC_INIT_STATE_G_MCMAIN_safe_sr_MAX                 (1) // 0x00000001
  #define MCDECS_CR_MC_INIT_STATE_G_MCMAIN_safe_sr_DEF                 (0x00000001)
  #define MCDECS_CR_MC_INIT_STATE_G_MCMAIN_safe_sr_HSH                 (0x01085030)

  #define MCDECS_CR_MC_INIT_STATE_G_MCMAIN_HVM_Gate_DDR_Reset_OFF      (10)
  #define MCDECS_CR_MC_INIT_STATE_G_MCMAIN_HVM_Gate_DDR_Reset_WID      ( 1)
  #define MCDECS_CR_MC_INIT_STATE_G_MCMAIN_HVM_Gate_DDR_Reset_MSK      (0x00000400)
  #define MCDECS_CR_MC_INIT_STATE_G_MCMAIN_HVM_Gate_DDR_Reset_MIN      (0)
  #define MCDECS_CR_MC_INIT_STATE_G_MCMAIN_HVM_Gate_DDR_Reset_MAX      (1) // 0x00000001
  #define MCDECS_CR_MC_INIT_STATE_G_MCMAIN_HVM_Gate_DDR_Reset_DEF      (0x00000000)
  #define MCDECS_CR_MC_INIT_STATE_G_MCMAIN_HVM_Gate_DDR_Reset_HSH      (0x010A5030)

  #define MCDECS_CR_MC_INIT_STATE_G_MCMAIN_mrc_save_low_OFF            (11)
  #define MCDECS_CR_MC_INIT_STATE_G_MCMAIN_mrc_save_low_WID            ( 1)
  #define MCDECS_CR_MC_INIT_STATE_G_MCMAIN_mrc_save_low_MSK            (0x00000800)
  #define MCDECS_CR_MC_INIT_STATE_G_MCMAIN_mrc_save_low_MIN            (0)
  #define MCDECS_CR_MC_INIT_STATE_G_MCMAIN_mrc_save_low_MAX            (1) // 0x00000001
  #define MCDECS_CR_MC_INIT_STATE_G_MCMAIN_mrc_save_low_DEF            (0x00000000)
  #define MCDECS_CR_MC_INIT_STATE_G_MCMAIN_mrc_save_low_HSH            (0x010B5030)

  #define MCDECS_CR_MC_INIT_STATE_G_MCMAIN_mrc_save_high_OFF           (12)
  #define MCDECS_CR_MC_INIT_STATE_G_MCMAIN_mrc_save_high_WID           ( 1)
  #define MCDECS_CR_MC_INIT_STATE_G_MCMAIN_mrc_save_high_MSK           (0x00001000)
  #define MCDECS_CR_MC_INIT_STATE_G_MCMAIN_mrc_save_high_MIN           (0)
  #define MCDECS_CR_MC_INIT_STATE_G_MCMAIN_mrc_save_high_MAX           (1) // 0x00000001
  #define MCDECS_CR_MC_INIT_STATE_G_MCMAIN_mrc_save_high_DEF           (0x00000000)
  #define MCDECS_CR_MC_INIT_STATE_G_MCMAIN_mrc_save_high_HSH           (0x010C5030)

  #define MCDECS_CR_MC_INIT_STATE_G_MCMAIN_dclk_enable_OFF             (22)
  #define MCDECS_CR_MC_INIT_STATE_G_MCMAIN_dclk_enable_WID             ( 1)
  #define MCDECS_CR_MC_INIT_STATE_G_MCMAIN_dclk_enable_MSK             (0x00400000)
  #define MCDECS_CR_MC_INIT_STATE_G_MCMAIN_dclk_enable_MIN             (0)
  #define MCDECS_CR_MC_INIT_STATE_G_MCMAIN_dclk_enable_MAX             (1) // 0x00000001
  #define MCDECS_CR_MC_INIT_STATE_G_MCMAIN_dclk_enable_DEF             (0x00000000)
  #define MCDECS_CR_MC_INIT_STATE_G_MCMAIN_dclk_enable_HSH             (0x01165030)

  #define MCDECS_CR_MC_INIT_STATE_G_MCMAIN_reset_io_OFF                (23)
  #define MCDECS_CR_MC_INIT_STATE_G_MCMAIN_reset_io_WID                ( 1)
  #define MCDECS_CR_MC_INIT_STATE_G_MCMAIN_reset_io_MSK                (0x00800000)
  #define MCDECS_CR_MC_INIT_STATE_G_MCMAIN_reset_io_MIN                (0)
  #define MCDECS_CR_MC_INIT_STATE_G_MCMAIN_reset_io_MAX                (1) // 0x00000001
  #define MCDECS_CR_MC_INIT_STATE_G_MCMAIN_reset_io_DEF                (0x00000000)
  #define MCDECS_CR_MC_INIT_STATE_G_MCMAIN_reset_io_HSH                (0x01175030)

  #define MCDECS_CR_MC_INIT_STATE_G_MCMAIN_no_block_reset_io_OFF       (24)
  #define MCDECS_CR_MC_INIT_STATE_G_MCMAIN_no_block_reset_io_WID       ( 1)
  #define MCDECS_CR_MC_INIT_STATE_G_MCMAIN_no_block_reset_io_MSK       (0x01000000)
  #define MCDECS_CR_MC_INIT_STATE_G_MCMAIN_no_block_reset_io_MIN       (0)
  #define MCDECS_CR_MC_INIT_STATE_G_MCMAIN_no_block_reset_io_MAX       (1) // 0x00000001
  #define MCDECS_CR_MC_INIT_STATE_G_MCMAIN_no_block_reset_io_DEF       (0x00000000)
  #define MCDECS_CR_MC_INIT_STATE_G_MCMAIN_no_block_reset_io_HSH       (0x01185030)

#define MCDECS_CR_MRC_REVISION_MCMAIN_REG                              (0x00005034)

  #define MCDECS_CR_MRC_REVISION_MCMAIN_REVISION_OFF                   ( 0)
  #define MCDECS_CR_MRC_REVISION_MCMAIN_REVISION_WID                   (32)
  #define MCDECS_CR_MRC_REVISION_MCMAIN_REVISION_MSK                   (0xFFFFFFFF)
  #define MCDECS_CR_MRC_REVISION_MCMAIN_REVISION_MIN                   (0)
  #define MCDECS_CR_MRC_REVISION_MCMAIN_REVISION_MAX                   (4294967295) // 0xFFFFFFFF
  #define MCDECS_CR_MRC_REVISION_MCMAIN_REVISION_DEF                   (0x00000000)
  #define MCDECS_CR_MRC_REVISION_MCMAIN_REVISION_HSH                   (0x20005034)

#define MCDECS_CR_PWM_GT_REQCOUNT_MCMAIN_REG                           (0x00005040)

  #define MCDECS_CR_PWM_GT_REQCOUNT_MCMAIN_count_OFF                   ( 0)
  #define MCDECS_CR_PWM_GT_REQCOUNT_MCMAIN_count_WID                   (32)
  #define MCDECS_CR_PWM_GT_REQCOUNT_MCMAIN_count_MSK                   (0xFFFFFFFF)
  #define MCDECS_CR_PWM_GT_REQCOUNT_MCMAIN_count_MIN                   (0)
  #define MCDECS_CR_PWM_GT_REQCOUNT_MCMAIN_count_MAX                   (4294967295) // 0xFFFFFFFF
  #define MCDECS_CR_PWM_GT_REQCOUNT_MCMAIN_count_DEF                   (0x00000000)
  #define MCDECS_CR_PWM_GT_REQCOUNT_MCMAIN_count_HSH                   (0x20005040)

#define MCDECS_CR_PWM_IA_REQCOUNT_MCMAIN_REG                           (0x00005044)

  #define MCDECS_CR_PWM_IA_REQCOUNT_MCMAIN_count_OFF                   ( 0)
  #define MCDECS_CR_PWM_IA_REQCOUNT_MCMAIN_count_WID                   (32)
  #define MCDECS_CR_PWM_IA_REQCOUNT_MCMAIN_count_MSK                   (0xFFFFFFFF)
  #define MCDECS_CR_PWM_IA_REQCOUNT_MCMAIN_count_MIN                   (0)
  #define MCDECS_CR_PWM_IA_REQCOUNT_MCMAIN_count_MAX                   (4294967295) // 0xFFFFFFFF
  #define MCDECS_CR_PWM_IA_REQCOUNT_MCMAIN_count_DEF                   (0x00000000)
  #define MCDECS_CR_PWM_IA_REQCOUNT_MCMAIN_count_HSH                   (0x20005044)

#define MCDECS_CR_PWM_IO_REQCOUNT_MCMAIN_REG                           (0x00005048)

  #define MCDECS_CR_PWM_IO_REQCOUNT_MCMAIN_count_OFF                   ( 0)
  #define MCDECS_CR_PWM_IO_REQCOUNT_MCMAIN_count_WID                   (32)
  #define MCDECS_CR_PWM_IO_REQCOUNT_MCMAIN_count_MSK                   (0xFFFFFFFF)
  #define MCDECS_CR_PWM_IO_REQCOUNT_MCMAIN_count_MIN                   (0)
  #define MCDECS_CR_PWM_IO_REQCOUNT_MCMAIN_count_MAX                   (4294967295) // 0xFFFFFFFF
  #define MCDECS_CR_PWM_IO_REQCOUNT_MCMAIN_count_DEF                   (0x00000000)
  #define MCDECS_CR_PWM_IO_REQCOUNT_MCMAIN_count_HSH                   (0x20005048)

#define MCDECS_CR_PWM_RDDATA_COUNT_MCMAIN_REG                          (0x00005050)

  #define MCDECS_CR_PWM_RDDATA_COUNT_MCMAIN_count_OFF                  ( 0)
  #define MCDECS_CR_PWM_RDDATA_COUNT_MCMAIN_count_WID                  (32)
  #define MCDECS_CR_PWM_RDDATA_COUNT_MCMAIN_count_MSK                  (0xFFFFFFFF)
  #define MCDECS_CR_PWM_RDDATA_COUNT_MCMAIN_count_MIN                  (0)
  #define MCDECS_CR_PWM_RDDATA_COUNT_MCMAIN_count_MAX                  (4294967295) // 0xFFFFFFFF
  #define MCDECS_CR_PWM_RDDATA_COUNT_MCMAIN_count_DEF                  (0x00000000)
  #define MCDECS_CR_PWM_RDDATA_COUNT_MCMAIN_count_HSH                  (0x20005050)

#define MCDECS_CR_PWM_WRDATA_COUNT_MCMAIN_REG                          (0x00005054)

  #define MCDECS_CR_PWM_WRDATA_COUNT_MCMAIN_count_OFF                  ( 0)
  #define MCDECS_CR_PWM_WRDATA_COUNT_MCMAIN_count_WID                  (32)
  #define MCDECS_CR_PWM_WRDATA_COUNT_MCMAIN_count_MSK                  (0xFFFFFFFF)
  #define MCDECS_CR_PWM_WRDATA_COUNT_MCMAIN_count_MIN                  (0)
  #define MCDECS_CR_PWM_WRDATA_COUNT_MCMAIN_count_MAX                  (4294967295) // 0xFFFFFFFF
  #define MCDECS_CR_PWM_WRDATA_COUNT_MCMAIN_count_DEF                  (0x00000000)
  #define MCDECS_CR_PWM_WRDATA_COUNT_MCMAIN_count_HSH                  (0x20005054)

#define MCDECS_CR_PWM_COMMAND_COUNT_MCMAIN_REG                         (0x00005058)

  #define MCDECS_CR_PWM_COMMAND_COUNT_MCMAIN_count_OFF                 ( 0)
  #define MCDECS_CR_PWM_COMMAND_COUNT_MCMAIN_count_WID                 (32)
  #define MCDECS_CR_PWM_COMMAND_COUNT_MCMAIN_count_MSK                 (0xFFFFFFFF)
  #define MCDECS_CR_PWM_COMMAND_COUNT_MCMAIN_count_MIN                 (0)
  #define MCDECS_CR_PWM_COMMAND_COUNT_MCMAIN_count_MAX                 (4294967295) // 0xFFFFFFFF
  #define MCDECS_CR_PWM_COMMAND_COUNT_MCMAIN_count_DEF                 (0x00000000)
  #define MCDECS_CR_PWM_COMMAND_COUNT_MCMAIN_count_HSH                 (0x20005058)

#define MCDECS_CR_PWM_NON_SR_COUNT_MCMAIN_REG                          (0x0000505C)

  #define MCDECS_CR_PWM_NON_SR_COUNT_MCMAIN_count_OFF                  ( 0)
  #define MCDECS_CR_PWM_NON_SR_COUNT_MCMAIN_count_WID                  (32)
  #define MCDECS_CR_PWM_NON_SR_COUNT_MCMAIN_count_MSK                  (0xFFFFFFFF)
  #define MCDECS_CR_PWM_NON_SR_COUNT_MCMAIN_count_MIN                  (0)
  #define MCDECS_CR_PWM_NON_SR_COUNT_MCMAIN_count_MAX                  (4294967295) // 0xFFFFFFFF
  #define MCDECS_CR_PWM_NON_SR_COUNT_MCMAIN_count_DEF                  (0x00000000)
  #define MCDECS_CR_PWM_NON_SR_COUNT_MCMAIN_count_HSH                  (0x2000505C)

#define MCDECS_CR_PM_SREF_CONFIG_MCMAIN_REG                            (0x00005060)

  #define MCDECS_CR_PM_SREF_CONFIG_MCMAIN_Idle_timer_OFF               ( 0)
  #define MCDECS_CR_PM_SREF_CONFIG_MCMAIN_Idle_timer_WID               (16)
  #define MCDECS_CR_PM_SREF_CONFIG_MCMAIN_Idle_timer_MSK               (0x0000FFFF)
  #define MCDECS_CR_PM_SREF_CONFIG_MCMAIN_Idle_timer_MIN               (0)
  #define MCDECS_CR_PM_SREF_CONFIG_MCMAIN_Idle_timer_MAX               (65535) // 0x0000FFFF
  #define MCDECS_CR_PM_SREF_CONFIG_MCMAIN_Idle_timer_DEF               (0x00000200)
  #define MCDECS_CR_PM_SREF_CONFIG_MCMAIN_Idle_timer_HSH               (0x10005060)

  #define MCDECS_CR_PM_SREF_CONFIG_MCMAIN_SR_Enable_OFF                (16)
  #define MCDECS_CR_PM_SREF_CONFIG_MCMAIN_SR_Enable_WID                ( 1)
  #define MCDECS_CR_PM_SREF_CONFIG_MCMAIN_SR_Enable_MSK                (0x00010000)
  #define MCDECS_CR_PM_SREF_CONFIG_MCMAIN_SR_Enable_MIN                (0)
  #define MCDECS_CR_PM_SREF_CONFIG_MCMAIN_SR_Enable_MAX                (1) // 0x00000001
  #define MCDECS_CR_PM_SREF_CONFIG_MCMAIN_SR_Enable_DEF                (0x00000001)
  #define MCDECS_CR_PM_SREF_CONFIG_MCMAIN_SR_Enable_HSH                (0x01105060)

#define MCDECS_CR_ATMC_STS_MCMAIN_REG                                  (0x00005064)

  #define MCDECS_CR_ATMC_STS_MCMAIN_VC1_WR_CNFLT_OFF                   ( 0)
  #define MCDECS_CR_ATMC_STS_MCMAIN_VC1_WR_CNFLT_WID                   ( 1)
  #define MCDECS_CR_ATMC_STS_MCMAIN_VC1_WR_CNFLT_MSK                   (0x00000001)
  #define MCDECS_CR_ATMC_STS_MCMAIN_VC1_WR_CNFLT_MIN                   (0)
  #define MCDECS_CR_ATMC_STS_MCMAIN_VC1_WR_CNFLT_MAX                   (1) // 0x00000001
  #define MCDECS_CR_ATMC_STS_MCMAIN_VC1_WR_CNFLT_DEF                   (0x00000000)
  #define MCDECS_CR_ATMC_STS_MCMAIN_VC1_WR_CNFLT_HSH                   (0x01005064)

  #define MCDECS_CR_ATMC_STS_MCMAIN_VC1_RD_CNFLT_OFF                   ( 1)
  #define MCDECS_CR_ATMC_STS_MCMAIN_VC1_RD_CNFLT_WID                   ( 1)
  #define MCDECS_CR_ATMC_STS_MCMAIN_VC1_RD_CNFLT_MSK                   (0x00000002)
  #define MCDECS_CR_ATMC_STS_MCMAIN_VC1_RD_CNFLT_MIN                   (0)
  #define MCDECS_CR_ATMC_STS_MCMAIN_VC1_RD_CNFLT_MAX                   (1) // 0x00000001
  #define MCDECS_CR_ATMC_STS_MCMAIN_VC1_RD_CNFLT_DEF                   (0x00000000)
  #define MCDECS_CR_ATMC_STS_MCMAIN_VC1_RD_CNFLT_HSH                   (0x01015064)

#define MCDECS_CR_READ_OCCUPANCY_COUNT_MCMAIN_REG                      (0x00005068)

  #define MCDECS_CR_READ_OCCUPANCY_COUNT_MCMAIN_count_OFF              ( 0)
  #define MCDECS_CR_READ_OCCUPANCY_COUNT_MCMAIN_count_WID              (32)
  #define MCDECS_CR_READ_OCCUPANCY_COUNT_MCMAIN_count_MSK              (0xFFFFFFFF)
  #define MCDECS_CR_READ_OCCUPANCY_COUNT_MCMAIN_count_MIN              (0)
  #define MCDECS_CR_READ_OCCUPANCY_COUNT_MCMAIN_count_MAX              (4294967295) // 0xFFFFFFFF
  #define MCDECS_CR_READ_OCCUPANCY_COUNT_MCMAIN_count_DEF              (0x00000000)
  #define MCDECS_CR_READ_OCCUPANCY_COUNT_MCMAIN_count_HSH              (0x20005068)

#define MCDECS_CR_STALL_DRAIN_MCMAIN_REG                               (0x00005074)

  #define MCDECS_CR_STALL_DRAIN_MCMAIN_stall_until_drain_OFF           ( 0)
  #define MCDECS_CR_STALL_DRAIN_MCMAIN_stall_until_drain_WID           ( 1)
  #define MCDECS_CR_STALL_DRAIN_MCMAIN_stall_until_drain_MSK           (0x00000001)
  #define MCDECS_CR_STALL_DRAIN_MCMAIN_stall_until_drain_MIN           (0)
  #define MCDECS_CR_STALL_DRAIN_MCMAIN_stall_until_drain_MAX           (1) // 0x00000001
  #define MCDECS_CR_STALL_DRAIN_MCMAIN_stall_until_drain_DEF           (0x00000000)
  #define MCDECS_CR_STALL_DRAIN_MCMAIN_stall_until_drain_HSH           (0x01005074)

  #define MCDECS_CR_STALL_DRAIN_MCMAIN_stall_input_OFF                 ( 1)
  #define MCDECS_CR_STALL_DRAIN_MCMAIN_stall_input_WID                 ( 1)
  #define MCDECS_CR_STALL_DRAIN_MCMAIN_stall_input_MSK                 (0x00000002)
  #define MCDECS_CR_STALL_DRAIN_MCMAIN_stall_input_MIN                 (0)
  #define MCDECS_CR_STALL_DRAIN_MCMAIN_stall_input_MAX                 (1) // 0x00000001
  #define MCDECS_CR_STALL_DRAIN_MCMAIN_stall_input_DEF                 (0x00000000)
  #define MCDECS_CR_STALL_DRAIN_MCMAIN_stall_input_HSH                 (0x01015074)

  #define MCDECS_CR_STALL_DRAIN_MCMAIN_mc_drained_OFF                  ( 4)
  #define MCDECS_CR_STALL_DRAIN_MCMAIN_mc_drained_WID                  ( 1)
  #define MCDECS_CR_STALL_DRAIN_MCMAIN_mc_drained_MSK                  (0x00000010)
  #define MCDECS_CR_STALL_DRAIN_MCMAIN_mc_drained_MIN                  (0)
  #define MCDECS_CR_STALL_DRAIN_MCMAIN_mc_drained_MAX                  (1) // 0x00000001
  #define MCDECS_CR_STALL_DRAIN_MCMAIN_mc_drained_DEF                  (0x00000000)
  #define MCDECS_CR_STALL_DRAIN_MCMAIN_mc_drained_HSH                  (0x01045074)

  #define MCDECS_CR_STALL_DRAIN_MCMAIN_sr_state_OFF                    ( 8)
  #define MCDECS_CR_STALL_DRAIN_MCMAIN_sr_state_WID                    ( 1)
  #define MCDECS_CR_STALL_DRAIN_MCMAIN_sr_state_MSK                    (0x00000100)
  #define MCDECS_CR_STALL_DRAIN_MCMAIN_sr_state_MIN                    (0)
  #define MCDECS_CR_STALL_DRAIN_MCMAIN_sr_state_MAX                    (1) // 0x00000001
  #define MCDECS_CR_STALL_DRAIN_MCMAIN_sr_state_DEF                    (0x00000000)
  #define MCDECS_CR_STALL_DRAIN_MCMAIN_sr_state_HSH                    (0x01085074)

  #define MCDECS_CR_STALL_DRAIN_MCMAIN_stall_state_OFF                 (12)
  #define MCDECS_CR_STALL_DRAIN_MCMAIN_stall_state_WID                 ( 1)
  #define MCDECS_CR_STALL_DRAIN_MCMAIN_stall_state_MSK                 (0x00001000)
  #define MCDECS_CR_STALL_DRAIN_MCMAIN_stall_state_MIN                 (0)
  #define MCDECS_CR_STALL_DRAIN_MCMAIN_stall_state_MAX                 (1) // 0x00000001
  #define MCDECS_CR_STALL_DRAIN_MCMAIN_stall_state_DEF                 (0x00000000)
  #define MCDECS_CR_STALL_DRAIN_MCMAIN_stall_state_HSH                 (0x010C5074)

#define MCDECS_CR_IPC_MC_ARB_MCMAIN_REG                                (0x00005078)

  #define MCDECS_CR_IPC_MC_ARB_MCMAIN_NonVC1Threshold_OFF              ( 0)
  #define MCDECS_CR_IPC_MC_ARB_MCMAIN_NonVC1Threshold_WID              ( 4)
  #define MCDECS_CR_IPC_MC_ARB_MCMAIN_NonVC1Threshold_MSK              (0x0000000F)
  #define MCDECS_CR_IPC_MC_ARB_MCMAIN_NonVC1Threshold_MIN              (0)
  #define MCDECS_CR_IPC_MC_ARB_MCMAIN_NonVC1Threshold_MAX              (15) // 0x0000000F
  #define MCDECS_CR_IPC_MC_ARB_MCMAIN_NonVC1Threshold_DEF              (0x00000004)
  #define MCDECS_CR_IPC_MC_ARB_MCMAIN_NonVC1Threshold_HSH              (0x04005078)

  #define MCDECS_CR_IPC_MC_ARB_MCMAIN_VC1RdThreshold_OFF               ( 4)
  #define MCDECS_CR_IPC_MC_ARB_MCMAIN_VC1RdThreshold_WID               ( 4)
  #define MCDECS_CR_IPC_MC_ARB_MCMAIN_VC1RdThreshold_MSK               (0x000000F0)
  #define MCDECS_CR_IPC_MC_ARB_MCMAIN_VC1RdThreshold_MIN               (0)
  #define MCDECS_CR_IPC_MC_ARB_MCMAIN_VC1RdThreshold_MAX               (15) // 0x0000000F
  #define MCDECS_CR_IPC_MC_ARB_MCMAIN_VC1RdThreshold_DEF               (0x00000004)
  #define MCDECS_CR_IPC_MC_ARB_MCMAIN_VC1RdThreshold_HSH               (0x04045078)

  #define MCDECS_CR_IPC_MC_ARB_MCMAIN_FixedRateEn_OFF                  ( 8)
  #define MCDECS_CR_IPC_MC_ARB_MCMAIN_FixedRateEn_WID                  ( 1)
  #define MCDECS_CR_IPC_MC_ARB_MCMAIN_FixedRateEn_MSK                  (0x00000100)
  #define MCDECS_CR_IPC_MC_ARB_MCMAIN_FixedRateEn_MIN                  (0)
  #define MCDECS_CR_IPC_MC_ARB_MCMAIN_FixedRateEn_MAX                  (1) // 0x00000001
  #define MCDECS_CR_IPC_MC_ARB_MCMAIN_FixedRateEn_DEF                  (0x00000000)
  #define MCDECS_CR_IPC_MC_ARB_MCMAIN_FixedRateEn_HSH                  (0x01085078)

  #define MCDECS_CR_IPC_MC_ARB_MCMAIN_HIGH_PRIO_LIM_OFF                ( 9)
  #define MCDECS_CR_IPC_MC_ARB_MCMAIN_HIGH_PRIO_LIM_WID                ( 3)
  #define MCDECS_CR_IPC_MC_ARB_MCMAIN_HIGH_PRIO_LIM_MSK                (0x00000E00)
  #define MCDECS_CR_IPC_MC_ARB_MCMAIN_HIGH_PRIO_LIM_MIN                (0)
  #define MCDECS_CR_IPC_MC_ARB_MCMAIN_HIGH_PRIO_LIM_MAX                (7) // 0x00000007
  #define MCDECS_CR_IPC_MC_ARB_MCMAIN_HIGH_PRIO_LIM_DEF                (0x00000004)
  #define MCDECS_CR_IPC_MC_ARB_MCMAIN_HIGH_PRIO_LIM_HSH                (0x03095078)

  #define MCDECS_CR_IPC_MC_ARB_MCMAIN_LOW_PRIO_LIM_OFF                 (12)
  #define MCDECS_CR_IPC_MC_ARB_MCMAIN_LOW_PRIO_LIM_WID                 ( 3)
  #define MCDECS_CR_IPC_MC_ARB_MCMAIN_LOW_PRIO_LIM_MSK                 (0x00007000)
  #define MCDECS_CR_IPC_MC_ARB_MCMAIN_LOW_PRIO_LIM_MIN                 (0)
  #define MCDECS_CR_IPC_MC_ARB_MCMAIN_LOW_PRIO_LIM_MAX                 (7) // 0x00000007
  #define MCDECS_CR_IPC_MC_ARB_MCMAIN_LOW_PRIO_LIM_DEF                 (0x00000001)
  #define MCDECS_CR_IPC_MC_ARB_MCMAIN_LOW_PRIO_LIM_HSH                 (0x030C5078)

  #define MCDECS_CR_IPC_MC_ARB_MCMAIN_spare_OFF                        (15)
  #define MCDECS_CR_IPC_MC_ARB_MCMAIN_spare_WID                        ( 8)
  #define MCDECS_CR_IPC_MC_ARB_MCMAIN_spare_MSK                        (0x007F8000)
  #define MCDECS_CR_IPC_MC_ARB_MCMAIN_spare_MIN                        (0)
  #define MCDECS_CR_IPC_MC_ARB_MCMAIN_spare_MAX                        (255) // 0x000000FF
  #define MCDECS_CR_IPC_MC_ARB_MCMAIN_spare_DEF                        (0x00000000)
  #define MCDECS_CR_IPC_MC_ARB_MCMAIN_spare_HSH                        (0x080F5078)

#define MCDECS_CR_QUEUE_CREDIT_C_MCMAIN_REG                            (0x00005080)

  #define MCDECS_CR_QUEUE_CREDIT_C_MCMAIN_RPQ_count_OFF                ( 0)
  #define MCDECS_CR_QUEUE_CREDIT_C_MCMAIN_RPQ_count_WID                ( 5)
  #define MCDECS_CR_QUEUE_CREDIT_C_MCMAIN_RPQ_count_MSK                (0x0000001F)
  #define MCDECS_CR_QUEUE_CREDIT_C_MCMAIN_RPQ_count_MIN                (0)
  #define MCDECS_CR_QUEUE_CREDIT_C_MCMAIN_RPQ_count_MAX                (31) // 0x0000001F
  #define MCDECS_CR_QUEUE_CREDIT_C_MCMAIN_RPQ_count_DEF                (0x00000016)
  #define MCDECS_CR_QUEUE_CREDIT_C_MCMAIN_RPQ_count_HSH                (0x05005080)

  #define MCDECS_CR_QUEUE_CREDIT_C_MCMAIN_WPQ_count_OFF                ( 8)
  #define MCDECS_CR_QUEUE_CREDIT_C_MCMAIN_WPQ_count_WID                ( 7)
  #define MCDECS_CR_QUEUE_CREDIT_C_MCMAIN_WPQ_count_MSK                (0x00007F00)
  #define MCDECS_CR_QUEUE_CREDIT_C_MCMAIN_WPQ_count_MIN                (0)
  #define MCDECS_CR_QUEUE_CREDIT_C_MCMAIN_WPQ_count_MAX                (127) // 0x0000007F
  #define MCDECS_CR_QUEUE_CREDIT_C_MCMAIN_WPQ_count_DEF                (0x00000040)
  #define MCDECS_CR_QUEUE_CREDIT_C_MCMAIN_WPQ_count_HSH                (0x07085080)

  #define MCDECS_CR_QUEUE_CREDIT_C_MCMAIN_IPQ_count_OFF                (16)
  #define MCDECS_CR_QUEUE_CREDIT_C_MCMAIN_IPQ_count_WID                ( 4)
  #define MCDECS_CR_QUEUE_CREDIT_C_MCMAIN_IPQ_count_MSK                (0x000F0000)
  #define MCDECS_CR_QUEUE_CREDIT_C_MCMAIN_IPQ_count_MIN                (0)
  #define MCDECS_CR_QUEUE_CREDIT_C_MCMAIN_IPQ_count_MAX                (15) // 0x0000000F
  #define MCDECS_CR_QUEUE_CREDIT_C_MCMAIN_IPQ_count_DEF                (0x0000000A)
  #define MCDECS_CR_QUEUE_CREDIT_C_MCMAIN_IPQ_count_HSH                (0x04105080)

#define MCDECS_CR_RCOMP_TIMER_MCMAIN_REG                               (0x00005084)

  #define MCDECS_CR_RCOMP_TIMER_MCMAIN_count_OFF                       ( 0)
  #define MCDECS_CR_RCOMP_TIMER_MCMAIN_count_WID                       (16)
  #define MCDECS_CR_RCOMP_TIMER_MCMAIN_count_MSK                       (0x0000FFFF)
  #define MCDECS_CR_RCOMP_TIMER_MCMAIN_count_MIN                       (0)
  #define MCDECS_CR_RCOMP_TIMER_MCMAIN_count_MAX                       (65535) // 0x0000FFFF
  #define MCDECS_CR_RCOMP_TIMER_MCMAIN_count_DEF                       (0x00000CFF)
  #define MCDECS_CR_RCOMP_TIMER_MCMAIN_count_HSH                       (0x10005084)

  #define MCDECS_CR_RCOMP_TIMER_MCMAIN_First_Rcomp_done_OFF            (16)
  #define MCDECS_CR_RCOMP_TIMER_MCMAIN_First_Rcomp_done_WID            ( 1)
  #define MCDECS_CR_RCOMP_TIMER_MCMAIN_First_Rcomp_done_MSK            (0x00010000)
  #define MCDECS_CR_RCOMP_TIMER_MCMAIN_First_Rcomp_done_MIN            (0)
  #define MCDECS_CR_RCOMP_TIMER_MCMAIN_First_Rcomp_done_MAX            (1) // 0x00000001
  #define MCDECS_CR_RCOMP_TIMER_MCMAIN_First_Rcomp_done_DEF            (0x00000000)
  #define MCDECS_CR_RCOMP_TIMER_MCMAIN_First_Rcomp_done_HSH            (0x01105084)

#define MCDECS_CR_ECC_INJ_ADDR_COMPARE_MCMAIN_REG                      (0x00005090)

  #define MCDECS_CR_ECC_INJ_ADDR_COMPARE_MCMAIN_Address_OFF            ( 0)
  #define MCDECS_CR_ECC_INJ_ADDR_COMPARE_MCMAIN_Address_WID            (32)
  #define MCDECS_CR_ECC_INJ_ADDR_COMPARE_MCMAIN_Address_MSK            (0xFFFFFFFF)
  #define MCDECS_CR_ECC_INJ_ADDR_COMPARE_MCMAIN_Address_MIN            (0)
  #define MCDECS_CR_ECC_INJ_ADDR_COMPARE_MCMAIN_Address_MAX            (4294967295) // 0xFFFFFFFF
  #define MCDECS_CR_ECC_INJ_ADDR_COMPARE_MCMAIN_Address_DEF            (0x00000000)
  #define MCDECS_CR_ECC_INJ_ADDR_COMPARE_MCMAIN_Address_HSH            (0x20005090)

#define MCDECS_CR_ECC_INJ_ADDR_MASK_MCMAIN_REG                         (0x00005094)

  #define MCDECS_CR_ECC_INJ_ADDR_MASK_MCMAIN_Mask_OFF                  ( 0)
  #define MCDECS_CR_ECC_INJ_ADDR_MASK_MCMAIN_Mask_WID                  (32)
  #define MCDECS_CR_ECC_INJ_ADDR_MASK_MCMAIN_Mask_MSK                  (0xFFFFFFFF)
  #define MCDECS_CR_ECC_INJ_ADDR_MASK_MCMAIN_Mask_MIN                  (0)
  #define MCDECS_CR_ECC_INJ_ADDR_MASK_MCMAIN_Mask_MAX                  (4294967295) // 0xFFFFFFFF
  #define MCDECS_CR_ECC_INJ_ADDR_MASK_MCMAIN_Mask_DEF                  (0xFFFFFFFF)
  #define MCDECS_CR_ECC_INJ_ADDR_MASK_MCMAIN_Mask_HSH                  (0x20005094)

#define MCDECS_CR_VISA_CTL_MCDECS_MCMAIN_REG                           (0x000050A0)

  #define MCDECS_CR_VISA_CTL_MCDECS_MCMAIN_EN_CLK_OFF                  ( 0)
  #define MCDECS_CR_VISA_CTL_MCDECS_MCMAIN_EN_CLK_WID                  ( 1)
  #define MCDECS_CR_VISA_CTL_MCDECS_MCMAIN_EN_CLK_MSK                  (0x00000001)
  #define MCDECS_CR_VISA_CTL_MCDECS_MCMAIN_EN_CLK_MIN                  (0)
  #define MCDECS_CR_VISA_CTL_MCDECS_MCMAIN_EN_CLK_MAX                  (1) // 0x00000001
  #define MCDECS_CR_VISA_CTL_MCDECS_MCMAIN_EN_CLK_DEF                  (0x00000000)
  #define MCDECS_CR_VISA_CTL_MCDECS_MCMAIN_EN_CLK_HSH                  (0x010050A0)

  #define MCDECS_CR_VISA_CTL_MCDECS_MCMAIN_L0_DATA_BYTE_SEL_OFF        ( 1)
  #define MCDECS_CR_VISA_CTL_MCDECS_MCMAIN_L0_DATA_BYTE_SEL_WID        ( 7)
  #define MCDECS_CR_VISA_CTL_MCDECS_MCMAIN_L0_DATA_BYTE_SEL_MSK        (0x000000FE)
  #define MCDECS_CR_VISA_CTL_MCDECS_MCMAIN_L0_DATA_BYTE_SEL_MIN        (0)
  #define MCDECS_CR_VISA_CTL_MCDECS_MCMAIN_L0_DATA_BYTE_SEL_MAX        (127) // 0x0000007F
  #define MCDECS_CR_VISA_CTL_MCDECS_MCMAIN_L0_DATA_BYTE_SEL_DEF        (0x00000000)
  #define MCDECS_CR_VISA_CTL_MCDECS_MCMAIN_L0_DATA_BYTE_SEL_HSH        (0x070150A0)

  #define MCDECS_CR_VISA_CTL_MCDECS_MCMAIN_L0_BYP_SEL_OFF              ( 8)
  #define MCDECS_CR_VISA_CTL_MCDECS_MCMAIN_L0_BYP_SEL_WID              ( 1)
  #define MCDECS_CR_VISA_CTL_MCDECS_MCMAIN_L0_BYP_SEL_MSK              (0x00000100)
  #define MCDECS_CR_VISA_CTL_MCDECS_MCMAIN_L0_BYP_SEL_MIN              (0)
  #define MCDECS_CR_VISA_CTL_MCDECS_MCMAIN_L0_BYP_SEL_MAX              (1) // 0x00000001
  #define MCDECS_CR_VISA_CTL_MCDECS_MCMAIN_L0_BYP_SEL_DEF              (0x00000000)
  #define MCDECS_CR_VISA_CTL_MCDECS_MCMAIN_L0_BYP_SEL_HSH              (0x010850A0)

  #define MCDECS_CR_VISA_CTL_MCDECS_MCMAIN_L1_DATA_BYTE_SEL_OFF        ( 9)
  #define MCDECS_CR_VISA_CTL_MCDECS_MCMAIN_L1_DATA_BYTE_SEL_WID        ( 7)
  #define MCDECS_CR_VISA_CTL_MCDECS_MCMAIN_L1_DATA_BYTE_SEL_MSK        (0x0000FE00)
  #define MCDECS_CR_VISA_CTL_MCDECS_MCMAIN_L1_DATA_BYTE_SEL_MIN        (0)
  #define MCDECS_CR_VISA_CTL_MCDECS_MCMAIN_L1_DATA_BYTE_SEL_MAX        (127) // 0x0000007F
  #define MCDECS_CR_VISA_CTL_MCDECS_MCMAIN_L1_DATA_BYTE_SEL_DEF        (0x00000000)
  #define MCDECS_CR_VISA_CTL_MCDECS_MCMAIN_L1_DATA_BYTE_SEL_HSH        (0x070950A0)

  #define MCDECS_CR_VISA_CTL_MCDECS_MCMAIN_L1_BYP_SEL_OFF              (16)
  #define MCDECS_CR_VISA_CTL_MCDECS_MCMAIN_L1_BYP_SEL_WID              ( 1)
  #define MCDECS_CR_VISA_CTL_MCDECS_MCMAIN_L1_BYP_SEL_MSK              (0x00010000)
  #define MCDECS_CR_VISA_CTL_MCDECS_MCMAIN_L1_BYP_SEL_MIN              (0)
  #define MCDECS_CR_VISA_CTL_MCDECS_MCMAIN_L1_BYP_SEL_MAX              (1) // 0x00000001
  #define MCDECS_CR_VISA_CTL_MCDECS_MCMAIN_L1_BYP_SEL_DEF              (0x00000000)
  #define MCDECS_CR_VISA_CTL_MCDECS_MCMAIN_L1_BYP_SEL_HSH              (0x011050A0)

  #define MCDECS_CR_VISA_CTL_MCDECS_MCMAIN_VORANGE_OFF                 (31)
  #define MCDECS_CR_VISA_CTL_MCDECS_MCMAIN_VORANGE_WID                 ( 1)
  #define MCDECS_CR_VISA_CTL_MCDECS_MCMAIN_VORANGE_MSK                 (0x80000000)
  #define MCDECS_CR_VISA_CTL_MCDECS_MCMAIN_VORANGE_MIN                 (0)
  #define MCDECS_CR_VISA_CTL_MCDECS_MCMAIN_VORANGE_MAX                 (1) // 0x00000001
  #define MCDECS_CR_VISA_CTL_MCDECS_MCMAIN_VORANGE_DEF                 (0x00000000)
  #define MCDECS_CR_VISA_CTL_MCDECS_MCMAIN_VORANGE_HSH                 (0x011F50A0)

#define MCDECS_CR_VISA_XBAR_MCDECS_MCMAIN_REG                          (0x000050A4)

  #define MCDECS_CR_VISA_XBAR_MCDECS_MCMAIN_FXB_Li_BIT0_DATA_BIT_SEL_OFF ( 0)
  #define MCDECS_CR_VISA_XBAR_MCDECS_MCMAIN_FXB_Li_BIT0_DATA_BIT_SEL_WID ( 3)
  #define MCDECS_CR_VISA_XBAR_MCDECS_MCMAIN_FXB_Li_BIT0_DATA_BIT_SEL_MSK (0x00000007)
  #define MCDECS_CR_VISA_XBAR_MCDECS_MCMAIN_FXB_Li_BIT0_DATA_BIT_SEL_MIN (0)
  #define MCDECS_CR_VISA_XBAR_MCDECS_MCMAIN_FXB_Li_BIT0_DATA_BIT_SEL_MAX (7) // 0x00000007
  #define MCDECS_CR_VISA_XBAR_MCDECS_MCMAIN_FXB_Li_BIT0_DATA_BIT_SEL_DEF (0x00000000)
  #define MCDECS_CR_VISA_XBAR_MCDECS_MCMAIN_FXB_Li_BIT0_DATA_BIT_SEL_HSH (0x030050A4)

  #define MCDECS_CR_VISA_XBAR_MCDECS_MCMAIN_FXB_Li_BIT0_DATA_BYTE_SEL_OFF ( 3)
  #define MCDECS_CR_VISA_XBAR_MCDECS_MCMAIN_FXB_Li_BIT0_DATA_BYTE_SEL_WID ( 1)
  #define MCDECS_CR_VISA_XBAR_MCDECS_MCMAIN_FXB_Li_BIT0_DATA_BYTE_SEL_MSK (0x00000008)
  #define MCDECS_CR_VISA_XBAR_MCDECS_MCMAIN_FXB_Li_BIT0_DATA_BYTE_SEL_MIN (0)
  #define MCDECS_CR_VISA_XBAR_MCDECS_MCMAIN_FXB_Li_BIT0_DATA_BYTE_SEL_MAX (1) // 0x00000001
  #define MCDECS_CR_VISA_XBAR_MCDECS_MCMAIN_FXB_Li_BIT0_DATA_BYTE_SEL_DEF (0x00000000)
  #define MCDECS_CR_VISA_XBAR_MCDECS_MCMAIN_FXB_Li_BIT0_DATA_BYTE_SEL_HSH (0x010350A4)

  #define MCDECS_CR_VISA_XBAR_MCDECS_MCMAIN_FXB_Li_BIT1_DATA_BIT_SEL_OFF ( 4)
  #define MCDECS_CR_VISA_XBAR_MCDECS_MCMAIN_FXB_Li_BIT1_DATA_BIT_SEL_WID ( 3)
  #define MCDECS_CR_VISA_XBAR_MCDECS_MCMAIN_FXB_Li_BIT1_DATA_BIT_SEL_MSK (0x00000070)
  #define MCDECS_CR_VISA_XBAR_MCDECS_MCMAIN_FXB_Li_BIT1_DATA_BIT_SEL_MIN (0)
  #define MCDECS_CR_VISA_XBAR_MCDECS_MCMAIN_FXB_Li_BIT1_DATA_BIT_SEL_MAX (7) // 0x00000007
  #define MCDECS_CR_VISA_XBAR_MCDECS_MCMAIN_FXB_Li_BIT1_DATA_BIT_SEL_DEF (0x00000001)
  #define MCDECS_CR_VISA_XBAR_MCDECS_MCMAIN_FXB_Li_BIT1_DATA_BIT_SEL_HSH (0x030450A4)

  #define MCDECS_CR_VISA_XBAR_MCDECS_MCMAIN_FXB_Li_BIT1_DATA_BYTE_SEL_OFF ( 7)
  #define MCDECS_CR_VISA_XBAR_MCDECS_MCMAIN_FXB_Li_BIT1_DATA_BYTE_SEL_WID ( 1)
  #define MCDECS_CR_VISA_XBAR_MCDECS_MCMAIN_FXB_Li_BIT1_DATA_BYTE_SEL_MSK (0x00000080)
  #define MCDECS_CR_VISA_XBAR_MCDECS_MCMAIN_FXB_Li_BIT1_DATA_BYTE_SEL_MIN (0)
  #define MCDECS_CR_VISA_XBAR_MCDECS_MCMAIN_FXB_Li_BIT1_DATA_BYTE_SEL_MAX (1) // 0x00000001
  #define MCDECS_CR_VISA_XBAR_MCDECS_MCMAIN_FXB_Li_BIT1_DATA_BYTE_SEL_DEF (0x00000000)
  #define MCDECS_CR_VISA_XBAR_MCDECS_MCMAIN_FXB_Li_BIT1_DATA_BYTE_SEL_HSH (0x010750A4)

  #define MCDECS_CR_VISA_XBAR_MCDECS_MCMAIN_FXB_Li_BIT2_DATA_BIT_SEL_OFF ( 8)
  #define MCDECS_CR_VISA_XBAR_MCDECS_MCMAIN_FXB_Li_BIT2_DATA_BIT_SEL_WID ( 3)
  #define MCDECS_CR_VISA_XBAR_MCDECS_MCMAIN_FXB_Li_BIT2_DATA_BIT_SEL_MSK (0x00000700)
  #define MCDECS_CR_VISA_XBAR_MCDECS_MCMAIN_FXB_Li_BIT2_DATA_BIT_SEL_MIN (0)
  #define MCDECS_CR_VISA_XBAR_MCDECS_MCMAIN_FXB_Li_BIT2_DATA_BIT_SEL_MAX (7) // 0x00000007
  #define MCDECS_CR_VISA_XBAR_MCDECS_MCMAIN_FXB_Li_BIT2_DATA_BIT_SEL_DEF (0x00000002)
  #define MCDECS_CR_VISA_XBAR_MCDECS_MCMAIN_FXB_Li_BIT2_DATA_BIT_SEL_HSH (0x030850A4)

  #define MCDECS_CR_VISA_XBAR_MCDECS_MCMAIN_FXB_Li_BIT2_DATA_BYTE_SEL_OFF (11)
  #define MCDECS_CR_VISA_XBAR_MCDECS_MCMAIN_FXB_Li_BIT2_DATA_BYTE_SEL_WID ( 1)
  #define MCDECS_CR_VISA_XBAR_MCDECS_MCMAIN_FXB_Li_BIT2_DATA_BYTE_SEL_MSK (0x00000800)
  #define MCDECS_CR_VISA_XBAR_MCDECS_MCMAIN_FXB_Li_BIT2_DATA_BYTE_SEL_MIN (0)
  #define MCDECS_CR_VISA_XBAR_MCDECS_MCMAIN_FXB_Li_BIT2_DATA_BYTE_SEL_MAX (1) // 0x00000001
  #define MCDECS_CR_VISA_XBAR_MCDECS_MCMAIN_FXB_Li_BIT2_DATA_BYTE_SEL_DEF (0x00000000)
  #define MCDECS_CR_VISA_XBAR_MCDECS_MCMAIN_FXB_Li_BIT2_DATA_BYTE_SEL_HSH (0x010B50A4)

  #define MCDECS_CR_VISA_XBAR_MCDECS_MCMAIN_FXB_Li_BIT3_DATA_BIT_SEL_OFF (12)
  #define MCDECS_CR_VISA_XBAR_MCDECS_MCMAIN_FXB_Li_BIT3_DATA_BIT_SEL_WID ( 3)
  #define MCDECS_CR_VISA_XBAR_MCDECS_MCMAIN_FXB_Li_BIT3_DATA_BIT_SEL_MSK (0x00007000)
  #define MCDECS_CR_VISA_XBAR_MCDECS_MCMAIN_FXB_Li_BIT3_DATA_BIT_SEL_MIN (0)
  #define MCDECS_CR_VISA_XBAR_MCDECS_MCMAIN_FXB_Li_BIT3_DATA_BIT_SEL_MAX (7) // 0x00000007
  #define MCDECS_CR_VISA_XBAR_MCDECS_MCMAIN_FXB_Li_BIT3_DATA_BIT_SEL_DEF (0x00000003)
  #define MCDECS_CR_VISA_XBAR_MCDECS_MCMAIN_FXB_Li_BIT3_DATA_BIT_SEL_HSH (0x030C50A4)

  #define MCDECS_CR_VISA_XBAR_MCDECS_MCMAIN_FXB_Li_BIT3_DATA_BYTE_SEL_OFF (15)
  #define MCDECS_CR_VISA_XBAR_MCDECS_MCMAIN_FXB_Li_BIT3_DATA_BYTE_SEL_WID ( 1)
  #define MCDECS_CR_VISA_XBAR_MCDECS_MCMAIN_FXB_Li_BIT3_DATA_BYTE_SEL_MSK (0x00008000)
  #define MCDECS_CR_VISA_XBAR_MCDECS_MCMAIN_FXB_Li_BIT3_DATA_BYTE_SEL_MIN (0)
  #define MCDECS_CR_VISA_XBAR_MCDECS_MCMAIN_FXB_Li_BIT3_DATA_BYTE_SEL_MAX (1) // 0x00000001
  #define MCDECS_CR_VISA_XBAR_MCDECS_MCMAIN_FXB_Li_BIT3_DATA_BYTE_SEL_DEF (0x00000000)
  #define MCDECS_CR_VISA_XBAR_MCDECS_MCMAIN_FXB_Li_BIT3_DATA_BYTE_SEL_HSH (0x010F50A4)

  #define MCDECS_CR_VISA_XBAR_MCDECS_MCMAIN_FXB_Li_BIT4_DATA_BIT_SEL_OFF (16)
  #define MCDECS_CR_VISA_XBAR_MCDECS_MCMAIN_FXB_Li_BIT4_DATA_BIT_SEL_WID ( 3)
  #define MCDECS_CR_VISA_XBAR_MCDECS_MCMAIN_FXB_Li_BIT4_DATA_BIT_SEL_MSK (0x00070000)
  #define MCDECS_CR_VISA_XBAR_MCDECS_MCMAIN_FXB_Li_BIT4_DATA_BIT_SEL_MIN (0)
  #define MCDECS_CR_VISA_XBAR_MCDECS_MCMAIN_FXB_Li_BIT4_DATA_BIT_SEL_MAX (7) // 0x00000007
  #define MCDECS_CR_VISA_XBAR_MCDECS_MCMAIN_FXB_Li_BIT4_DATA_BIT_SEL_DEF (0x00000004)
  #define MCDECS_CR_VISA_XBAR_MCDECS_MCMAIN_FXB_Li_BIT4_DATA_BIT_SEL_HSH (0x031050A4)

  #define MCDECS_CR_VISA_XBAR_MCDECS_MCMAIN_FXB_Li_BIT4_DATA_BYTE_SEL_OFF (19)
  #define MCDECS_CR_VISA_XBAR_MCDECS_MCMAIN_FXB_Li_BIT4_DATA_BYTE_SEL_WID ( 1)
  #define MCDECS_CR_VISA_XBAR_MCDECS_MCMAIN_FXB_Li_BIT4_DATA_BYTE_SEL_MSK (0x00080000)
  #define MCDECS_CR_VISA_XBAR_MCDECS_MCMAIN_FXB_Li_BIT4_DATA_BYTE_SEL_MIN (0)
  #define MCDECS_CR_VISA_XBAR_MCDECS_MCMAIN_FXB_Li_BIT4_DATA_BYTE_SEL_MAX (1) // 0x00000001
  #define MCDECS_CR_VISA_XBAR_MCDECS_MCMAIN_FXB_Li_BIT4_DATA_BYTE_SEL_DEF (0x00000000)
  #define MCDECS_CR_VISA_XBAR_MCDECS_MCMAIN_FXB_Li_BIT4_DATA_BYTE_SEL_HSH (0x011350A4)

  #define MCDECS_CR_VISA_XBAR_MCDECS_MCMAIN_FXB_Li_BIT5_DATA_BIT_SEL_OFF (20)
  #define MCDECS_CR_VISA_XBAR_MCDECS_MCMAIN_FXB_Li_BIT5_DATA_BIT_SEL_WID ( 3)
  #define MCDECS_CR_VISA_XBAR_MCDECS_MCMAIN_FXB_Li_BIT5_DATA_BIT_SEL_MSK (0x00700000)
  #define MCDECS_CR_VISA_XBAR_MCDECS_MCMAIN_FXB_Li_BIT5_DATA_BIT_SEL_MIN (0)
  #define MCDECS_CR_VISA_XBAR_MCDECS_MCMAIN_FXB_Li_BIT5_DATA_BIT_SEL_MAX (7) // 0x00000007
  #define MCDECS_CR_VISA_XBAR_MCDECS_MCMAIN_FXB_Li_BIT5_DATA_BIT_SEL_DEF (0x00000005)
  #define MCDECS_CR_VISA_XBAR_MCDECS_MCMAIN_FXB_Li_BIT5_DATA_BIT_SEL_HSH (0x031450A4)

  #define MCDECS_CR_VISA_XBAR_MCDECS_MCMAIN_FXB_Li_BIT5_DATA_BYTE_SEL_OFF (23)
  #define MCDECS_CR_VISA_XBAR_MCDECS_MCMAIN_FXB_Li_BIT5_DATA_BYTE_SEL_WID ( 1)
  #define MCDECS_CR_VISA_XBAR_MCDECS_MCMAIN_FXB_Li_BIT5_DATA_BYTE_SEL_MSK (0x00800000)
  #define MCDECS_CR_VISA_XBAR_MCDECS_MCMAIN_FXB_Li_BIT5_DATA_BYTE_SEL_MIN (0)
  #define MCDECS_CR_VISA_XBAR_MCDECS_MCMAIN_FXB_Li_BIT5_DATA_BYTE_SEL_MAX (1) // 0x00000001
  #define MCDECS_CR_VISA_XBAR_MCDECS_MCMAIN_FXB_Li_BIT5_DATA_BYTE_SEL_DEF (0x00000000)
  #define MCDECS_CR_VISA_XBAR_MCDECS_MCMAIN_FXB_Li_BIT5_DATA_BYTE_SEL_HSH (0x011750A4)

  #define MCDECS_CR_VISA_XBAR_MCDECS_MCMAIN_FXB_Li_BIT6_DATA_BIT_SEL_OFF (24)
  #define MCDECS_CR_VISA_XBAR_MCDECS_MCMAIN_FXB_Li_BIT6_DATA_BIT_SEL_WID ( 3)
  #define MCDECS_CR_VISA_XBAR_MCDECS_MCMAIN_FXB_Li_BIT6_DATA_BIT_SEL_MSK (0x07000000)
  #define MCDECS_CR_VISA_XBAR_MCDECS_MCMAIN_FXB_Li_BIT6_DATA_BIT_SEL_MIN (0)
  #define MCDECS_CR_VISA_XBAR_MCDECS_MCMAIN_FXB_Li_BIT6_DATA_BIT_SEL_MAX (7) // 0x00000007
  #define MCDECS_CR_VISA_XBAR_MCDECS_MCMAIN_FXB_Li_BIT6_DATA_BIT_SEL_DEF (0x00000006)
  #define MCDECS_CR_VISA_XBAR_MCDECS_MCMAIN_FXB_Li_BIT6_DATA_BIT_SEL_HSH (0x031850A4)

  #define MCDECS_CR_VISA_XBAR_MCDECS_MCMAIN_FXB_Li_BIT6_DATA_BYTE_SEL_OFF (27)
  #define MCDECS_CR_VISA_XBAR_MCDECS_MCMAIN_FXB_Li_BIT6_DATA_BYTE_SEL_WID ( 1)
  #define MCDECS_CR_VISA_XBAR_MCDECS_MCMAIN_FXB_Li_BIT6_DATA_BYTE_SEL_MSK (0x08000000)
  #define MCDECS_CR_VISA_XBAR_MCDECS_MCMAIN_FXB_Li_BIT6_DATA_BYTE_SEL_MIN (0)
  #define MCDECS_CR_VISA_XBAR_MCDECS_MCMAIN_FXB_Li_BIT6_DATA_BYTE_SEL_MAX (1) // 0x00000001
  #define MCDECS_CR_VISA_XBAR_MCDECS_MCMAIN_FXB_Li_BIT6_DATA_BYTE_SEL_DEF (0x00000000)
  #define MCDECS_CR_VISA_XBAR_MCDECS_MCMAIN_FXB_Li_BIT6_DATA_BYTE_SEL_HSH (0x011B50A4)

  #define MCDECS_CR_VISA_XBAR_MCDECS_MCMAIN_FXB_Li_BIT7_DATA_BIT_SEL_OFF (28)
  #define MCDECS_CR_VISA_XBAR_MCDECS_MCMAIN_FXB_Li_BIT7_DATA_BIT_SEL_WID ( 3)
  #define MCDECS_CR_VISA_XBAR_MCDECS_MCMAIN_FXB_Li_BIT7_DATA_BIT_SEL_MSK (0x70000000)
  #define MCDECS_CR_VISA_XBAR_MCDECS_MCMAIN_FXB_Li_BIT7_DATA_BIT_SEL_MIN (0)
  #define MCDECS_CR_VISA_XBAR_MCDECS_MCMAIN_FXB_Li_BIT7_DATA_BIT_SEL_MAX (7) // 0x00000007
  #define MCDECS_CR_VISA_XBAR_MCDECS_MCMAIN_FXB_Li_BIT7_DATA_BIT_SEL_DEF (0x00000007)
  #define MCDECS_CR_VISA_XBAR_MCDECS_MCMAIN_FXB_Li_BIT7_DATA_BIT_SEL_HSH (0x031C50A4)

  #define MCDECS_CR_VISA_XBAR_MCDECS_MCMAIN_FXB_Li_BIT7_DATA_BYTE_SEL_OFF (31)
  #define MCDECS_CR_VISA_XBAR_MCDECS_MCMAIN_FXB_Li_BIT7_DATA_BYTE_SEL_WID ( 1)
  #define MCDECS_CR_VISA_XBAR_MCDECS_MCMAIN_FXB_Li_BIT7_DATA_BYTE_SEL_MSK (0x80000000)
  #define MCDECS_CR_VISA_XBAR_MCDECS_MCMAIN_FXB_Li_BIT7_DATA_BYTE_SEL_MIN (0)
  #define MCDECS_CR_VISA_XBAR_MCDECS_MCMAIN_FXB_Li_BIT7_DATA_BYTE_SEL_MAX (1) // 0x00000001
  #define MCDECS_CR_VISA_XBAR_MCDECS_MCMAIN_FXB_Li_BIT7_DATA_BYTE_SEL_DEF (0x00000000)
  #define MCDECS_CR_VISA_XBAR_MCDECS_MCMAIN_FXB_Li_BIT7_DATA_BYTE_SEL_HSH (0x011F50A4)

#define MCDECS_CR_VISA_SLIDE_MCDECS_MCMAIN_REG                         (0x000050A8)

  #define MCDECS_CR_VISA_SLIDE_MCDECS_MCMAIN_WINDOW_SLIDE_L0_OFF       ( 0)
  #define MCDECS_CR_VISA_SLIDE_MCDECS_MCMAIN_WINDOW_SLIDE_L0_WID       ( 3)
  #define MCDECS_CR_VISA_SLIDE_MCDECS_MCMAIN_WINDOW_SLIDE_L0_MSK       (0x00000007)
  #define MCDECS_CR_VISA_SLIDE_MCDECS_MCMAIN_WINDOW_SLIDE_L0_MIN       (0)
  #define MCDECS_CR_VISA_SLIDE_MCDECS_MCMAIN_WINDOW_SLIDE_L0_MAX       (7) // 0x00000007
  #define MCDECS_CR_VISA_SLIDE_MCDECS_MCMAIN_WINDOW_SLIDE_L0_DEF       (0x00000000)
  #define MCDECS_CR_VISA_SLIDE_MCDECS_MCMAIN_WINDOW_SLIDE_L0_HSH       (0x030050A8)

  #define MCDECS_CR_VISA_SLIDE_MCDECS_MCMAIN_ALT_L0_DATA_BYTE_SEL_OFF  ( 3)
  #define MCDECS_CR_VISA_SLIDE_MCDECS_MCMAIN_ALT_L0_DATA_BYTE_SEL_WID  ( 7)
  #define MCDECS_CR_VISA_SLIDE_MCDECS_MCMAIN_ALT_L0_DATA_BYTE_SEL_MSK  (0x000003F8)
  #define MCDECS_CR_VISA_SLIDE_MCDECS_MCMAIN_ALT_L0_DATA_BYTE_SEL_MIN  (0)
  #define MCDECS_CR_VISA_SLIDE_MCDECS_MCMAIN_ALT_L0_DATA_BYTE_SEL_MAX  (127) // 0x0000007F
  #define MCDECS_CR_VISA_SLIDE_MCDECS_MCMAIN_ALT_L0_DATA_BYTE_SEL_DEF  (0x00000000)
  #define MCDECS_CR_VISA_SLIDE_MCDECS_MCMAIN_ALT_L0_DATA_BYTE_SEL_HSH  (0x070350A8)

  #define MCDECS_CR_VISA_SLIDE_MCDECS_MCMAIN_WINDOW_SLIDE_L1_OFF       (10)
  #define MCDECS_CR_VISA_SLIDE_MCDECS_MCMAIN_WINDOW_SLIDE_L1_WID       ( 3)
  #define MCDECS_CR_VISA_SLIDE_MCDECS_MCMAIN_WINDOW_SLIDE_L1_MSK       (0x00001C00)
  #define MCDECS_CR_VISA_SLIDE_MCDECS_MCMAIN_WINDOW_SLIDE_L1_MIN       (0)
  #define MCDECS_CR_VISA_SLIDE_MCDECS_MCMAIN_WINDOW_SLIDE_L1_MAX       (7) // 0x00000007
  #define MCDECS_CR_VISA_SLIDE_MCDECS_MCMAIN_WINDOW_SLIDE_L1_DEF       (0x00000000)
  #define MCDECS_CR_VISA_SLIDE_MCDECS_MCMAIN_WINDOW_SLIDE_L1_HSH       (0x030A50A8)

  #define MCDECS_CR_VISA_SLIDE_MCDECS_MCMAIN_ALT_L1_DATA_BYTE_SEL_OFF  (13)
  #define MCDECS_CR_VISA_SLIDE_MCDECS_MCMAIN_ALT_L1_DATA_BYTE_SEL_WID  ( 7)
  #define MCDECS_CR_VISA_SLIDE_MCDECS_MCMAIN_ALT_L1_DATA_BYTE_SEL_MSK  (0x000FE000)
  #define MCDECS_CR_VISA_SLIDE_MCDECS_MCMAIN_ALT_L1_DATA_BYTE_SEL_MIN  (0)
  #define MCDECS_CR_VISA_SLIDE_MCDECS_MCMAIN_ALT_L1_DATA_BYTE_SEL_MAX  (127) // 0x0000007F
  #define MCDECS_CR_VISA_SLIDE_MCDECS_MCMAIN_ALT_L1_DATA_BYTE_SEL_DEF  (0x00000000)
  #define MCDECS_CR_VISA_SLIDE_MCDECS_MCMAIN_ALT_L1_DATA_BYTE_SEL_HSH  (0x070D50A8)

#define MCDECS_CR_BIT_ERROR_RECOVERY_SOURCE_SYSADDR_MCMAIN_0_REG       (0x000050B0)

  #define MCDECS_CR_BIT_ERROR_RECOVERY_SOURCE_SYSADDR_MCMAIN_0_sys_addr_OFF ( 6)
  #define MCDECS_CR_BIT_ERROR_RECOVERY_SOURCE_SYSADDR_MCMAIN_0_sys_addr_WID (33)
  #define MCDECS_CR_BIT_ERROR_RECOVERY_SOURCE_SYSADDR_MCMAIN_0_sys_addr_MSK (0x0000007FFFFFFFC0ULL)
  #define MCDECS_CR_BIT_ERROR_RECOVERY_SOURCE_SYSADDR_MCMAIN_0_sys_addr_MIN (0)
  #define MCDECS_CR_BIT_ERROR_RECOVERY_SOURCE_SYSADDR_MCMAIN_0_sys_addr_MAX (8589934591ULL) // 0x1FFFFFFFF
  #define MCDECS_CR_BIT_ERROR_RECOVERY_SOURCE_SYSADDR_MCMAIN_0_sys_addr_DEF (0x00000000)
  #define MCDECS_CR_BIT_ERROR_RECOVERY_SOURCE_SYSADDR_MCMAIN_0_sys_addr_HSH (0x610650B0)

  #define MCDECS_CR_BIT_ERROR_RECOVERY_SOURCE_SYSADDR_MCMAIN_0_is_tcm_OFF (62)
  #define MCDECS_CR_BIT_ERROR_RECOVERY_SOURCE_SYSADDR_MCMAIN_0_is_tcm_WID ( 1)
  #define MCDECS_CR_BIT_ERROR_RECOVERY_SOURCE_SYSADDR_MCMAIN_0_is_tcm_MSK (0x4000000000000000ULL)
  #define MCDECS_CR_BIT_ERROR_RECOVERY_SOURCE_SYSADDR_MCMAIN_0_is_tcm_MIN (0)
  #define MCDECS_CR_BIT_ERROR_RECOVERY_SOURCE_SYSADDR_MCMAIN_0_is_tcm_MAX (1) // 0x00000001
  #define MCDECS_CR_BIT_ERROR_RECOVERY_SOURCE_SYSADDR_MCMAIN_0_is_tcm_DEF (0x00000000)
  #define MCDECS_CR_BIT_ERROR_RECOVERY_SOURCE_SYSADDR_MCMAIN_0_is_tcm_HSH (0x413E50B0)

  #define MCDECS_CR_BIT_ERROR_RECOVERY_SOURCE_SYSADDR_MCMAIN_0_valid_OFF (63)
  #define MCDECS_CR_BIT_ERROR_RECOVERY_SOURCE_SYSADDR_MCMAIN_0_valid_WID ( 1)
  #define MCDECS_CR_BIT_ERROR_RECOVERY_SOURCE_SYSADDR_MCMAIN_0_valid_MSK (0x8000000000000000ULL)
  #define MCDECS_CR_BIT_ERROR_RECOVERY_SOURCE_SYSADDR_MCMAIN_0_valid_MIN (0)
  #define MCDECS_CR_BIT_ERROR_RECOVERY_SOURCE_SYSADDR_MCMAIN_0_valid_MAX (1) // 0x00000001
  #define MCDECS_CR_BIT_ERROR_RECOVERY_SOURCE_SYSADDR_MCMAIN_0_valid_DEF (0x00000000)
  #define MCDECS_CR_BIT_ERROR_RECOVERY_SOURCE_SYSADDR_MCMAIN_0_valid_HSH (0x413F50B0)

#define MCDECS_CR_BIT_ERROR_RECOVERY_SOURCE_SYSADDR_MCMAIN_1_REG       (0x000050B8)

  #define MCDECS_CR_BIT_ERROR_RECOVERY_SOURCE_SYSADDR_MCMAIN_1_sys_addr_OFF ( 6)
  #define MCDECS_CR_BIT_ERROR_RECOVERY_SOURCE_SYSADDR_MCMAIN_1_sys_addr_WID (33)
  #define MCDECS_CR_BIT_ERROR_RECOVERY_SOURCE_SYSADDR_MCMAIN_1_sys_addr_MSK (0x0000007FFFFFFFC0ULL)
  #define MCDECS_CR_BIT_ERROR_RECOVERY_SOURCE_SYSADDR_MCMAIN_1_sys_addr_MIN (0)
  #define MCDECS_CR_BIT_ERROR_RECOVERY_SOURCE_SYSADDR_MCMAIN_1_sys_addr_MAX (8589934591ULL) // 0x1FFFFFFFF
  #define MCDECS_CR_BIT_ERROR_RECOVERY_SOURCE_SYSADDR_MCMAIN_1_sys_addr_DEF (0x00000000)
  #define MCDECS_CR_BIT_ERROR_RECOVERY_SOURCE_SYSADDR_MCMAIN_1_sys_addr_HSH (0x610650B8)

  #define MCDECS_CR_BIT_ERROR_RECOVERY_SOURCE_SYSADDR_MCMAIN_1_is_tcm_OFF (62)
  #define MCDECS_CR_BIT_ERROR_RECOVERY_SOURCE_SYSADDR_MCMAIN_1_is_tcm_WID ( 1)
  #define MCDECS_CR_BIT_ERROR_RECOVERY_SOURCE_SYSADDR_MCMAIN_1_is_tcm_MSK (0x4000000000000000ULL)
  #define MCDECS_CR_BIT_ERROR_RECOVERY_SOURCE_SYSADDR_MCMAIN_1_is_tcm_MIN (0)
  #define MCDECS_CR_BIT_ERROR_RECOVERY_SOURCE_SYSADDR_MCMAIN_1_is_tcm_MAX (1) // 0x00000001
  #define MCDECS_CR_BIT_ERROR_RECOVERY_SOURCE_SYSADDR_MCMAIN_1_is_tcm_DEF (0x00000000)
  #define MCDECS_CR_BIT_ERROR_RECOVERY_SOURCE_SYSADDR_MCMAIN_1_is_tcm_HSH (0x413E50B8)

  #define MCDECS_CR_BIT_ERROR_RECOVERY_SOURCE_SYSADDR_MCMAIN_1_valid_OFF (63)
  #define MCDECS_CR_BIT_ERROR_RECOVERY_SOURCE_SYSADDR_MCMAIN_1_valid_WID ( 1)
  #define MCDECS_CR_BIT_ERROR_RECOVERY_SOURCE_SYSADDR_MCMAIN_1_valid_MSK (0x8000000000000000ULL)
  #define MCDECS_CR_BIT_ERROR_RECOVERY_SOURCE_SYSADDR_MCMAIN_1_valid_MIN (0)
  #define MCDECS_CR_BIT_ERROR_RECOVERY_SOURCE_SYSADDR_MCMAIN_1_valid_MAX (1) // 0x00000001
  #define MCDECS_CR_BIT_ERROR_RECOVERY_SOURCE_SYSADDR_MCMAIN_1_valid_DEF (0x00000000)
  #define MCDECS_CR_BIT_ERROR_RECOVERY_SOURCE_SYSADDR_MCMAIN_1_valid_HSH (0x413F50B8)

#define MCDECS_CR_BIT_ERROR_RECOVERY_SOURCE_SYSADDR_MCMAIN_2_REG       (0x000050C0)

  #define MCDECS_CR_BIT_ERROR_RECOVERY_SOURCE_SYSADDR_MCMAIN_2_sys_addr_OFF ( 6)
  #define MCDECS_CR_BIT_ERROR_RECOVERY_SOURCE_SYSADDR_MCMAIN_2_sys_addr_WID (33)
  #define MCDECS_CR_BIT_ERROR_RECOVERY_SOURCE_SYSADDR_MCMAIN_2_sys_addr_MSK (0x0000007FFFFFFFC0ULL)
  #define MCDECS_CR_BIT_ERROR_RECOVERY_SOURCE_SYSADDR_MCMAIN_2_sys_addr_MIN (0)
  #define MCDECS_CR_BIT_ERROR_RECOVERY_SOURCE_SYSADDR_MCMAIN_2_sys_addr_MAX (8589934591ULL) // 0x1FFFFFFFF
  #define MCDECS_CR_BIT_ERROR_RECOVERY_SOURCE_SYSADDR_MCMAIN_2_sys_addr_DEF (0x00000000)
  #define MCDECS_CR_BIT_ERROR_RECOVERY_SOURCE_SYSADDR_MCMAIN_2_sys_addr_HSH (0x610650C0)

  #define MCDECS_CR_BIT_ERROR_RECOVERY_SOURCE_SYSADDR_MCMAIN_2_is_tcm_OFF (62)
  #define MCDECS_CR_BIT_ERROR_RECOVERY_SOURCE_SYSADDR_MCMAIN_2_is_tcm_WID ( 1)
  #define MCDECS_CR_BIT_ERROR_RECOVERY_SOURCE_SYSADDR_MCMAIN_2_is_tcm_MSK (0x4000000000000000ULL)
  #define MCDECS_CR_BIT_ERROR_RECOVERY_SOURCE_SYSADDR_MCMAIN_2_is_tcm_MIN (0)
  #define MCDECS_CR_BIT_ERROR_RECOVERY_SOURCE_SYSADDR_MCMAIN_2_is_tcm_MAX (1) // 0x00000001
  #define MCDECS_CR_BIT_ERROR_RECOVERY_SOURCE_SYSADDR_MCMAIN_2_is_tcm_DEF (0x00000000)
  #define MCDECS_CR_BIT_ERROR_RECOVERY_SOURCE_SYSADDR_MCMAIN_2_is_tcm_HSH (0x413E50C0)

  #define MCDECS_CR_BIT_ERROR_RECOVERY_SOURCE_SYSADDR_MCMAIN_2_valid_OFF (63)
  #define MCDECS_CR_BIT_ERROR_RECOVERY_SOURCE_SYSADDR_MCMAIN_2_valid_WID ( 1)
  #define MCDECS_CR_BIT_ERROR_RECOVERY_SOURCE_SYSADDR_MCMAIN_2_valid_MSK (0x8000000000000000ULL)
  #define MCDECS_CR_BIT_ERROR_RECOVERY_SOURCE_SYSADDR_MCMAIN_2_valid_MIN (0)
  #define MCDECS_CR_BIT_ERROR_RECOVERY_SOURCE_SYSADDR_MCMAIN_2_valid_MAX (1) // 0x00000001
  #define MCDECS_CR_BIT_ERROR_RECOVERY_SOURCE_SYSADDR_MCMAIN_2_valid_DEF (0x00000000)
  #define MCDECS_CR_BIT_ERROR_RECOVERY_SOURCE_SYSADDR_MCMAIN_2_valid_HSH (0x413F50C0)

#define MCDECS_CR_BIT_ERROR_RECOVERY_SOURCE_SYSADDR_MCMAIN_3_REG       (0x000050C8)

  #define MCDECS_CR_BIT_ERROR_RECOVERY_SOURCE_SYSADDR_MCMAIN_3_sys_addr_OFF ( 6)
  #define MCDECS_CR_BIT_ERROR_RECOVERY_SOURCE_SYSADDR_MCMAIN_3_sys_addr_WID (33)
  #define MCDECS_CR_BIT_ERROR_RECOVERY_SOURCE_SYSADDR_MCMAIN_3_sys_addr_MSK (0x0000007FFFFFFFC0ULL)
  #define MCDECS_CR_BIT_ERROR_RECOVERY_SOURCE_SYSADDR_MCMAIN_3_sys_addr_MIN (0)
  #define MCDECS_CR_BIT_ERROR_RECOVERY_SOURCE_SYSADDR_MCMAIN_3_sys_addr_MAX (8589934591ULL) // 0x1FFFFFFFF
  #define MCDECS_CR_BIT_ERROR_RECOVERY_SOURCE_SYSADDR_MCMAIN_3_sys_addr_DEF (0x00000000)
  #define MCDECS_CR_BIT_ERROR_RECOVERY_SOURCE_SYSADDR_MCMAIN_3_sys_addr_HSH (0x610650C8)

  #define MCDECS_CR_BIT_ERROR_RECOVERY_SOURCE_SYSADDR_MCMAIN_3_is_tcm_OFF (62)
  #define MCDECS_CR_BIT_ERROR_RECOVERY_SOURCE_SYSADDR_MCMAIN_3_is_tcm_WID ( 1)
  #define MCDECS_CR_BIT_ERROR_RECOVERY_SOURCE_SYSADDR_MCMAIN_3_is_tcm_MSK (0x4000000000000000ULL)
  #define MCDECS_CR_BIT_ERROR_RECOVERY_SOURCE_SYSADDR_MCMAIN_3_is_tcm_MIN (0)
  #define MCDECS_CR_BIT_ERROR_RECOVERY_SOURCE_SYSADDR_MCMAIN_3_is_tcm_MAX (1) // 0x00000001
  #define MCDECS_CR_BIT_ERROR_RECOVERY_SOURCE_SYSADDR_MCMAIN_3_is_tcm_DEF (0x00000000)
  #define MCDECS_CR_BIT_ERROR_RECOVERY_SOURCE_SYSADDR_MCMAIN_3_is_tcm_HSH (0x413E50C8)

  #define MCDECS_CR_BIT_ERROR_RECOVERY_SOURCE_SYSADDR_MCMAIN_3_valid_OFF (63)
  #define MCDECS_CR_BIT_ERROR_RECOVERY_SOURCE_SYSADDR_MCMAIN_3_valid_WID ( 1)
  #define MCDECS_CR_BIT_ERROR_RECOVERY_SOURCE_SYSADDR_MCMAIN_3_valid_MSK (0x8000000000000000ULL)
  #define MCDECS_CR_BIT_ERROR_RECOVERY_SOURCE_SYSADDR_MCMAIN_3_valid_MIN (0)
  #define MCDECS_CR_BIT_ERROR_RECOVERY_SOURCE_SYSADDR_MCMAIN_3_valid_MAX (1) // 0x00000001
  #define MCDECS_CR_BIT_ERROR_RECOVERY_SOURCE_SYSADDR_MCMAIN_3_valid_DEF (0x00000000)
  #define MCDECS_CR_BIT_ERROR_RECOVERY_SOURCE_SYSADDR_MCMAIN_3_valid_HSH (0x413F50C8)

#define MCDECS_CR_MC_LOCK_MCMAIN_REG                                   (0x000050FC)

  #define MCDECS_CR_MC_LOCK_MCMAIN_lock_addr_map_OFF                   ( 0)
  #define MCDECS_CR_MC_LOCK_MCMAIN_lock_addr_map_WID                   ( 1)
  #define MCDECS_CR_MC_LOCK_MCMAIN_lock_addr_map_MSK                   (0x00000001)
  #define MCDECS_CR_MC_LOCK_MCMAIN_lock_addr_map_MIN                   (0)
  #define MCDECS_CR_MC_LOCK_MCMAIN_lock_addr_map_MAX                   (1) // 0x00000001
  #define MCDECS_CR_MC_LOCK_MCMAIN_lock_addr_map_DEF                   (0x00000000)
  #define MCDECS_CR_MC_LOCK_MCMAIN_lock_addr_map_HSH                   (0x010050FC)

  #define MCDECS_CR_MC_LOCK_MCMAIN_lock_mc_config_OFF                  ( 1)
  #define MCDECS_CR_MC_LOCK_MCMAIN_lock_mc_config_WID                  ( 1)
  #define MCDECS_CR_MC_LOCK_MCMAIN_lock_mc_config_MSK                  (0x00000002)
  #define MCDECS_CR_MC_LOCK_MCMAIN_lock_mc_config_MIN                  (0)
  #define MCDECS_CR_MC_LOCK_MCMAIN_lock_mc_config_MAX                  (1) // 0x00000001
  #define MCDECS_CR_MC_LOCK_MCMAIN_lock_mc_config_DEF                  (0x00000000)
  #define MCDECS_CR_MC_LOCK_MCMAIN_lock_mc_config_HSH                  (0x010150FC)

  #define MCDECS_CR_MC_LOCK_MCMAIN_lock_iosav_init_OFF                 ( 2)
  #define MCDECS_CR_MC_LOCK_MCMAIN_lock_iosav_init_WID                 ( 1)
  #define MCDECS_CR_MC_LOCK_MCMAIN_lock_iosav_init_MSK                 (0x00000004)
  #define MCDECS_CR_MC_LOCK_MCMAIN_lock_iosav_init_MIN                 (0)
  #define MCDECS_CR_MC_LOCK_MCMAIN_lock_iosav_init_MAX                 (1) // 0x00000001
  #define MCDECS_CR_MC_LOCK_MCMAIN_lock_iosav_init_DEF                 (0x00000000)
  #define MCDECS_CR_MC_LOCK_MCMAIN_lock_iosav_init_HSH                 (0x010250FC)

  #define MCDECS_CR_MC_LOCK_MCMAIN_lock_pwr_mngment_OFF                ( 3)
  #define MCDECS_CR_MC_LOCK_MCMAIN_lock_pwr_mngment_WID                ( 1)
  #define MCDECS_CR_MC_LOCK_MCMAIN_lock_pwr_mngment_MSK                (0x00000008)
  #define MCDECS_CR_MC_LOCK_MCMAIN_lock_pwr_mngment_MIN                (0)
  #define MCDECS_CR_MC_LOCK_MCMAIN_lock_pwr_mngment_MAX                (1) // 0x00000001
  #define MCDECS_CR_MC_LOCK_MCMAIN_lock_pwr_mngment_DEF                (0x00000000)
  #define MCDECS_CR_MC_LOCK_MCMAIN_lock_pwr_mngment_HSH                (0x010350FC)

  #define MCDECS_CR_MC_LOCK_MCMAIN_lock_mc_dft_OFF                     ( 7)
  #define MCDECS_CR_MC_LOCK_MCMAIN_lock_mc_dft_WID                     ( 1)
  #define MCDECS_CR_MC_LOCK_MCMAIN_lock_mc_dft_MSK                     (0x00000080)
  #define MCDECS_CR_MC_LOCK_MCMAIN_lock_mc_dft_MIN                     (0)
  #define MCDECS_CR_MC_LOCK_MCMAIN_lock_mc_dft_MAX                     (1) // 0x00000001
  #define MCDECS_CR_MC_LOCK_MCMAIN_lock_mc_dft_DEF                     (0x00000000)
  #define MCDECS_CR_MC_LOCK_MCMAIN_lock_mc_dft_HSH                     (0x010750FC)

#define MCDECS_CR_GDXC_DDR_SYS_ADD_FILTER_MASK_MCMAIN_0_REG            (0x00005100)

  #define MCDECS_CR_GDXC_DDR_SYS_ADD_FILTER_MASK_MCMAIN_0_sys_addr_OFF ( 6)
  #define MCDECS_CR_GDXC_DDR_SYS_ADD_FILTER_MASK_MCMAIN_0_sys_addr_WID (33)
  #define MCDECS_CR_GDXC_DDR_SYS_ADD_FILTER_MASK_MCMAIN_0_sys_addr_MSK (0x0000007FFFFFFFC0ULL)
  #define MCDECS_CR_GDXC_DDR_SYS_ADD_FILTER_MASK_MCMAIN_0_sys_addr_MIN (0)
  #define MCDECS_CR_GDXC_DDR_SYS_ADD_FILTER_MASK_MCMAIN_0_sys_addr_MAX (8589934591ULL) // 0x1FFFFFFFF
  #define MCDECS_CR_GDXC_DDR_SYS_ADD_FILTER_MASK_MCMAIN_0_sys_addr_DEF (0x00000000)
  #define MCDECS_CR_GDXC_DDR_SYS_ADD_FILTER_MASK_MCMAIN_0_sys_addr_HSH (0x61065100)

#define MCDECS_CR_GDXC_DDR_SYS_ADD_FILTER_MASK_MCMAIN_1_REG            (0x00005108)

  #define MCDECS_CR_GDXC_DDR_SYS_ADD_FILTER_MASK_MCMAIN_1_sys_addr_OFF ( 6)
  #define MCDECS_CR_GDXC_DDR_SYS_ADD_FILTER_MASK_MCMAIN_1_sys_addr_WID (33)
  #define MCDECS_CR_GDXC_DDR_SYS_ADD_FILTER_MASK_MCMAIN_1_sys_addr_MSK (0x0000007FFFFFFFC0ULL)
  #define MCDECS_CR_GDXC_DDR_SYS_ADD_FILTER_MASK_MCMAIN_1_sys_addr_MIN (0)
  #define MCDECS_CR_GDXC_DDR_SYS_ADD_FILTER_MASK_MCMAIN_1_sys_addr_MAX (8589934591ULL) // 0x1FFFFFFFF
  #define MCDECS_CR_GDXC_DDR_SYS_ADD_FILTER_MASK_MCMAIN_1_sys_addr_DEF (0x00000000)
  #define MCDECS_CR_GDXC_DDR_SYS_ADD_FILTER_MASK_MCMAIN_1_sys_addr_HSH (0x61065108)

#define MCDECS_CR_GDXC_DDR_SYS_ADD_FILTER_MATCH_MCMAIN_0_REG           (0x00005110)

  #define MCDECS_CR_GDXC_DDR_SYS_ADD_FILTER_MATCH_MCMAIN_0_sys_addr_OFF ( 6)
  #define MCDECS_CR_GDXC_DDR_SYS_ADD_FILTER_MATCH_MCMAIN_0_sys_addr_WID (33)
  #define MCDECS_CR_GDXC_DDR_SYS_ADD_FILTER_MATCH_MCMAIN_0_sys_addr_MSK (0x0000007FFFFFFFC0ULL)
  #define MCDECS_CR_GDXC_DDR_SYS_ADD_FILTER_MATCH_MCMAIN_0_sys_addr_MIN (0)
  #define MCDECS_CR_GDXC_DDR_SYS_ADD_FILTER_MATCH_MCMAIN_0_sys_addr_MAX (8589934591ULL) // 0x1FFFFFFFF
  #define MCDECS_CR_GDXC_DDR_SYS_ADD_FILTER_MATCH_MCMAIN_0_sys_addr_DEF (0x00000000)
  #define MCDECS_CR_GDXC_DDR_SYS_ADD_FILTER_MATCH_MCMAIN_0_sys_addr_HSH (0x61065110)

#define MCDECS_CR_GDXC_DDR_SYS_ADD_FILTER_MATCH_MCMAIN_1_REG           (0x00005118)

  #define MCDECS_CR_GDXC_DDR_SYS_ADD_FILTER_MATCH_MCMAIN_1_sys_addr_OFF ( 6)
  #define MCDECS_CR_GDXC_DDR_SYS_ADD_FILTER_MATCH_MCMAIN_1_sys_addr_WID (33)
  #define MCDECS_CR_GDXC_DDR_SYS_ADD_FILTER_MATCH_MCMAIN_1_sys_addr_MSK (0x0000007FFFFFFFC0ULL)
  #define MCDECS_CR_GDXC_DDR_SYS_ADD_FILTER_MATCH_MCMAIN_1_sys_addr_MIN (0)
  #define MCDECS_CR_GDXC_DDR_SYS_ADD_FILTER_MATCH_MCMAIN_1_sys_addr_MAX (8589934591ULL) // 0x1FFFFFFFF
  #define MCDECS_CR_GDXC_DDR_SYS_ADD_FILTER_MATCH_MCMAIN_1_sys_addr_DEF (0x00000000)
  #define MCDECS_CR_GDXC_DDR_SYS_ADD_FILTER_MATCH_MCMAIN_1_sys_addr_HSH (0x61065118)

#define MCDECS_CR_GDXC_DDR_SYS_ADD_TRIGGER_MASK_MCMAIN_REG             (0x00005120)

  #define MCDECS_CR_GDXC_DDR_SYS_ADD_TRIGGER_MASK_MCMAIN_sys_addr_OFF  ( 6)
  #define MCDECS_CR_GDXC_DDR_SYS_ADD_TRIGGER_MASK_MCMAIN_sys_addr_WID  (33)
  #define MCDECS_CR_GDXC_DDR_SYS_ADD_TRIGGER_MASK_MCMAIN_sys_addr_MSK  (0x0000007FFFFFFFC0ULL)
  #define MCDECS_CR_GDXC_DDR_SYS_ADD_TRIGGER_MASK_MCMAIN_sys_addr_MIN  (0)
  #define MCDECS_CR_GDXC_DDR_SYS_ADD_TRIGGER_MASK_MCMAIN_sys_addr_MAX  (8589934591ULL) // 0x1FFFFFFFF
  #define MCDECS_CR_GDXC_DDR_SYS_ADD_TRIGGER_MASK_MCMAIN_sys_addr_DEF  (0x00000000)
  #define MCDECS_CR_GDXC_DDR_SYS_ADD_TRIGGER_MASK_MCMAIN_sys_addr_HSH  (0x61065120)

#define MCDECS_CR_GDXC_DDR_SYS_ADD_TRIGGER_MATCH_MCMAIN_REG            (0x00005128)

  #define MCDECS_CR_GDXC_DDR_SYS_ADD_TRIGGER_MATCH_MCMAIN_sys_addr_OFF ( 6)
  #define MCDECS_CR_GDXC_DDR_SYS_ADD_TRIGGER_MATCH_MCMAIN_sys_addr_WID (33)
  #define MCDECS_CR_GDXC_DDR_SYS_ADD_TRIGGER_MATCH_MCMAIN_sys_addr_MSK (0x0000007FFFFFFFC0ULL)
  #define MCDECS_CR_GDXC_DDR_SYS_ADD_TRIGGER_MATCH_MCMAIN_sys_addr_MIN (0)
  #define MCDECS_CR_GDXC_DDR_SYS_ADD_TRIGGER_MATCH_MCMAIN_sys_addr_MAX (8589934591ULL) // 0x1FFFFFFFF
  #define MCDECS_CR_GDXC_DDR_SYS_ADD_TRIGGER_MATCH_MCMAIN_sys_addr_DEF (0x00000000)
  #define MCDECS_CR_GDXC_DDR_SYS_ADD_TRIGGER_MATCH_MCMAIN_sys_addr_HSH (0x61065128)

#define MCDECS_CR_SC_QOS_MCMAIN_REG                                    (0x00005130)

  #define MCDECS_CR_SC_QOS_MCMAIN_Isoch_time_window_OFF                ( 0)
  #define MCDECS_CR_SC_QOS_MCMAIN_Isoch_time_window_WID                (17)
  #define MCDECS_CR_SC_QOS_MCMAIN_Isoch_time_window_MSK                (0x0001FFFF)
  #define MCDECS_CR_SC_QOS_MCMAIN_Isoch_time_window_MIN                (0)
  #define MCDECS_CR_SC_QOS_MCMAIN_Isoch_time_window_MAX                (131071) // 0x0001FFFF
  #define MCDECS_CR_SC_QOS_MCMAIN_Isoch_time_window_DEF                (0x000001C2)
  #define MCDECS_CR_SC_QOS_MCMAIN_Isoch_time_window_HSH                (0x51005130)

  #define MCDECS_CR_SC_QOS_MCMAIN_Write_starvation_window_OFF          (17)
  #define MCDECS_CR_SC_QOS_MCMAIN_Write_starvation_window_WID          (11)
  #define MCDECS_CR_SC_QOS_MCMAIN_Write_starvation_window_MSK          (0x0FFE0000)
  #define MCDECS_CR_SC_QOS_MCMAIN_Write_starvation_window_MIN          (0)
  #define MCDECS_CR_SC_QOS_MCMAIN_Write_starvation_window_MAX          (2047) // 0x000007FF
  #define MCDECS_CR_SC_QOS_MCMAIN_Write_starvation_window_DEF          (0x0000005A)
  #define MCDECS_CR_SC_QOS_MCMAIN_Write_starvation_window_HSH          (0x4B115130)

  #define MCDECS_CR_SC_QOS_MCMAIN_Read_starvation_window_OFF           (28)
  #define MCDECS_CR_SC_QOS_MCMAIN_Read_starvation_window_WID           (11)
  #define MCDECS_CR_SC_QOS_MCMAIN_Read_starvation_window_MSK           (0x0000007FF0000000ULL)
  #define MCDECS_CR_SC_QOS_MCMAIN_Read_starvation_window_MIN           (0)
  #define MCDECS_CR_SC_QOS_MCMAIN_Read_starvation_window_MAX           (2047) // 0x000007FF
  #define MCDECS_CR_SC_QOS_MCMAIN_Read_starvation_window_DEF           (0x0000005A)
  #define MCDECS_CR_SC_QOS_MCMAIN_Read_starvation_window_HSH           (0x4B1C5130)

  #define MCDECS_CR_SC_QOS_MCMAIN_VC0_read_count_OFF                   (39)
  #define MCDECS_CR_SC_QOS_MCMAIN_VC0_read_count_WID                   ( 9)
  #define MCDECS_CR_SC_QOS_MCMAIN_VC0_read_count_MSK                   (0x0000FF8000000000ULL)
  #define MCDECS_CR_SC_QOS_MCMAIN_VC0_read_count_MIN                   (0)
  #define MCDECS_CR_SC_QOS_MCMAIN_VC0_read_count_MAX                   (511) // 0x000001FF
  #define MCDECS_CR_SC_QOS_MCMAIN_VC0_read_count_DEF                   (0x00000016)
  #define MCDECS_CR_SC_QOS_MCMAIN_VC0_read_count_HSH                   (0x49275130)

  #define MCDECS_CR_SC_QOS_MCMAIN_VC1_Read_starvation_en_OFF           (48)
  #define MCDECS_CR_SC_QOS_MCMAIN_VC1_Read_starvation_en_WID           ( 1)
  #define MCDECS_CR_SC_QOS_MCMAIN_VC1_Read_starvation_en_MSK           (0x0001000000000000ULL)
  #define MCDECS_CR_SC_QOS_MCMAIN_VC1_Read_starvation_en_MIN           (0)
  #define MCDECS_CR_SC_QOS_MCMAIN_VC1_Read_starvation_en_MAX           (1) // 0x00000001
  #define MCDECS_CR_SC_QOS_MCMAIN_VC1_Read_starvation_en_DEF           (0x00000001)
  #define MCDECS_CR_SC_QOS_MCMAIN_VC1_Read_starvation_en_HSH           (0x41305130)

  #define MCDECS_CR_SC_QOS_MCMAIN_Write_starvation_in_Isoc_en_OFF      (49)
  #define MCDECS_CR_SC_QOS_MCMAIN_Write_starvation_in_Isoc_en_WID      ( 1)
  #define MCDECS_CR_SC_QOS_MCMAIN_Write_starvation_in_Isoc_en_MSK      (0x0002000000000000ULL)
  #define MCDECS_CR_SC_QOS_MCMAIN_Write_starvation_in_Isoc_en_MIN      (0)
  #define MCDECS_CR_SC_QOS_MCMAIN_Write_starvation_in_Isoc_en_MAX      (1) // 0x00000001
  #define MCDECS_CR_SC_QOS_MCMAIN_Write_starvation_in_Isoc_en_DEF      (0x00000001)
  #define MCDECS_CR_SC_QOS_MCMAIN_Write_starvation_in_Isoc_en_HSH      (0x41315130)

  #define MCDECS_CR_SC_QOS_MCMAIN_Read_starvation_in_Isoch_en_OFF      (50)
  #define MCDECS_CR_SC_QOS_MCMAIN_Read_starvation_in_Isoch_en_WID      ( 1)
  #define MCDECS_CR_SC_QOS_MCMAIN_Read_starvation_in_Isoch_en_MSK      (0x0004000000000000ULL)
  #define MCDECS_CR_SC_QOS_MCMAIN_Read_starvation_in_Isoch_en_MIN      (0)
  #define MCDECS_CR_SC_QOS_MCMAIN_Read_starvation_in_Isoch_en_MAX      (1) // 0x00000001
  #define MCDECS_CR_SC_QOS_MCMAIN_Read_starvation_in_Isoch_en_DEF      (0x00000001)
  #define MCDECS_CR_SC_QOS_MCMAIN_Read_starvation_in_Isoch_en_HSH      (0x41325130)

  #define MCDECS_CR_SC_QOS_MCMAIN_VC0_counter_disable_OFF              (51)
  #define MCDECS_CR_SC_QOS_MCMAIN_VC0_counter_disable_WID              ( 1)
  #define MCDECS_CR_SC_QOS_MCMAIN_VC0_counter_disable_MSK              (0x0008000000000000ULL)
  #define MCDECS_CR_SC_QOS_MCMAIN_VC0_counter_disable_MIN              (0)
  #define MCDECS_CR_SC_QOS_MCMAIN_VC0_counter_disable_MAX              (1) // 0x00000001
  #define MCDECS_CR_SC_QOS_MCMAIN_VC0_counter_disable_DEF              (0x00000000)
  #define MCDECS_CR_SC_QOS_MCMAIN_VC0_counter_disable_HSH              (0x41335130)

  #define MCDECS_CR_SC_QOS_MCMAIN_Force_MCVC1Demote_OFF                (52)
  #define MCDECS_CR_SC_QOS_MCMAIN_Force_MCVC1Demote_WID                ( 1)
  #define MCDECS_CR_SC_QOS_MCMAIN_Force_MCVC1Demote_MSK                (0x0010000000000000ULL)
  #define MCDECS_CR_SC_QOS_MCMAIN_Force_MCVC1Demote_MIN                (0)
  #define MCDECS_CR_SC_QOS_MCMAIN_Force_MCVC1Demote_MAX                (1) // 0x00000001
  #define MCDECS_CR_SC_QOS_MCMAIN_Force_MCVC1Demote_DEF                (0x00000000)
  #define MCDECS_CR_SC_QOS_MCMAIN_Force_MCVC1Demote_HSH                (0x41345130)

  #define MCDECS_CR_SC_QOS_MCMAIN_Disable_MCVC1Demote_OFF              (53)
  #define MCDECS_CR_SC_QOS_MCMAIN_Disable_MCVC1Demote_WID              ( 1)
  #define MCDECS_CR_SC_QOS_MCMAIN_Disable_MCVC1Demote_MSK              (0x0020000000000000ULL)
  #define MCDECS_CR_SC_QOS_MCMAIN_Disable_MCVC1Demote_MIN              (0)
  #define MCDECS_CR_SC_QOS_MCMAIN_Disable_MCVC1Demote_MAX              (1) // 0x00000001
  #define MCDECS_CR_SC_QOS_MCMAIN_Disable_MCVC1Demote_DEF              (0x00000000)
  #define MCDECS_CR_SC_QOS_MCMAIN_Disable_MCVC1Demote_HSH              (0x41355130)

  #define MCDECS_CR_SC_QOS_MCMAIN_MC_Ignore_VC1Demote_OFF              (54)
  #define MCDECS_CR_SC_QOS_MCMAIN_MC_Ignore_VC1Demote_WID              ( 1)
  #define MCDECS_CR_SC_QOS_MCMAIN_MC_Ignore_VC1Demote_MSK              (0x0040000000000000ULL)
  #define MCDECS_CR_SC_QOS_MCMAIN_MC_Ignore_VC1Demote_MIN              (0)
  #define MCDECS_CR_SC_QOS_MCMAIN_MC_Ignore_VC1Demote_MAX              (1) // 0x00000001
  #define MCDECS_CR_SC_QOS_MCMAIN_MC_Ignore_VC1Demote_DEF              (0x00000000)
  #define MCDECS_CR_SC_QOS_MCMAIN_MC_Ignore_VC1Demote_HSH              (0x41365130)

#define MCDECS_CR_MC_GLOBAL_DRIVER_GATE_CFG_MCMAIN_REG                 (0x00005138)

  #define MCDECS_CR_MC_GLOBAL_DRIVER_GATE_CFG_MCMAIN_GLB_GRACE_CNT_OFF ( 0)
  #define MCDECS_CR_MC_GLOBAL_DRIVER_GATE_CFG_MCMAIN_GLB_GRACE_CNT_WID ( 5)
  #define MCDECS_CR_MC_GLOBAL_DRIVER_GATE_CFG_MCMAIN_GLB_GRACE_CNT_MSK (0x0000001F)
  #define MCDECS_CR_MC_GLOBAL_DRIVER_GATE_CFG_MCMAIN_GLB_GRACE_CNT_MIN (0)
  #define MCDECS_CR_MC_GLOBAL_DRIVER_GATE_CFG_MCMAIN_GLB_GRACE_CNT_MAX (31) // 0x0000001F
  #define MCDECS_CR_MC_GLOBAL_DRIVER_GATE_CFG_MCMAIN_GLB_GRACE_CNT_DEF (0x00000004)
  #define MCDECS_CR_MC_GLOBAL_DRIVER_GATE_CFG_MCMAIN_GLB_GRACE_CNT_HSH (0x05005138)

  #define MCDECS_CR_MC_GLOBAL_DRIVER_GATE_CFG_MCMAIN_MNT_GLB_GRACE_CNT_OFF ( 5)
  #define MCDECS_CR_MC_GLOBAL_DRIVER_GATE_CFG_MCMAIN_MNT_GLB_GRACE_CNT_WID ( 5)
  #define MCDECS_CR_MC_GLOBAL_DRIVER_GATE_CFG_MCMAIN_MNT_GLB_GRACE_CNT_MSK (0x000003E0)
  #define MCDECS_CR_MC_GLOBAL_DRIVER_GATE_CFG_MCMAIN_MNT_GLB_GRACE_CNT_MIN (0)
  #define MCDECS_CR_MC_GLOBAL_DRIVER_GATE_CFG_MCMAIN_MNT_GLB_GRACE_CNT_MAX (31) // 0x0000001F
  #define MCDECS_CR_MC_GLOBAL_DRIVER_GATE_CFG_MCMAIN_MNT_GLB_GRACE_CNT_DEF (0x00000004)
  #define MCDECS_CR_MC_GLOBAL_DRIVER_GATE_CFG_MCMAIN_MNT_GLB_GRACE_CNT_HSH (0x05055138)

  #define MCDECS_CR_MC_GLOBAL_DRIVER_GATE_CFG_MCMAIN_MNT_GLB_DRV_GATE_DIS_OFF (10)
  #define MCDECS_CR_MC_GLOBAL_DRIVER_GATE_CFG_MCMAIN_MNT_GLB_DRV_GATE_DIS_WID ( 1)
  #define MCDECS_CR_MC_GLOBAL_DRIVER_GATE_CFG_MCMAIN_MNT_GLB_DRV_GATE_DIS_MSK (0x00000400)
  #define MCDECS_CR_MC_GLOBAL_DRIVER_GATE_CFG_MCMAIN_MNT_GLB_DRV_GATE_DIS_MIN (0)
  #define MCDECS_CR_MC_GLOBAL_DRIVER_GATE_CFG_MCMAIN_MNT_GLB_DRV_GATE_DIS_MAX (1) // 0x00000001
  #define MCDECS_CR_MC_GLOBAL_DRIVER_GATE_CFG_MCMAIN_MNT_GLB_DRV_GATE_DIS_DEF (0x00000000)
  #define MCDECS_CR_MC_GLOBAL_DRIVER_GATE_CFG_MCMAIN_MNT_GLB_DRV_GATE_DIS_HSH (0x010A5138)

  #define MCDECS_CR_MC_GLOBAL_DRIVER_GATE_CFG_MCMAIN_SCHEDS_GLB_DRV_GATE_DIS_OFF (11)
  #define MCDECS_CR_MC_GLOBAL_DRIVER_GATE_CFG_MCMAIN_SCHEDS_GLB_DRV_GATE_DIS_WID ( 1)
  #define MCDECS_CR_MC_GLOBAL_DRIVER_GATE_CFG_MCMAIN_SCHEDS_GLB_DRV_GATE_DIS_MSK (0x00000800)
  #define MCDECS_CR_MC_GLOBAL_DRIVER_GATE_CFG_MCMAIN_SCHEDS_GLB_DRV_GATE_DIS_MIN (0)
  #define MCDECS_CR_MC_GLOBAL_DRIVER_GATE_CFG_MCMAIN_SCHEDS_GLB_DRV_GATE_DIS_MAX (1) // 0x00000001
  #define MCDECS_CR_MC_GLOBAL_DRIVER_GATE_CFG_MCMAIN_SCHEDS_GLB_DRV_GATE_DIS_DEF (0x00000000)
  #define MCDECS_CR_MC_GLOBAL_DRIVER_GATE_CFG_MCMAIN_SCHEDS_GLB_DRV_GATE_DIS_HSH (0x010B5138)

  #define MCDECS_CR_MC_GLOBAL_DRIVER_GATE_CFG_MCMAIN_WDB_GLB_DRV_GATE_DIS_OFF (12)
  #define MCDECS_CR_MC_GLOBAL_DRIVER_GATE_CFG_MCMAIN_WDB_GLB_DRV_GATE_DIS_WID ( 1)
  #define MCDECS_CR_MC_GLOBAL_DRIVER_GATE_CFG_MCMAIN_WDB_GLB_DRV_GATE_DIS_MSK (0x00001000)
  #define MCDECS_CR_MC_GLOBAL_DRIVER_GATE_CFG_MCMAIN_WDB_GLB_DRV_GATE_DIS_MIN (0)
  #define MCDECS_CR_MC_GLOBAL_DRIVER_GATE_CFG_MCMAIN_WDB_GLB_DRV_GATE_DIS_MAX (1) // 0x00000001
  #define MCDECS_CR_MC_GLOBAL_DRIVER_GATE_CFG_MCMAIN_WDB_GLB_DRV_GATE_DIS_DEF (0x00000000)
  #define MCDECS_CR_MC_GLOBAL_DRIVER_GATE_CFG_MCMAIN_WDB_GLB_DRV_GATE_DIS_HSH (0x010C5138)

  #define MCDECS_CR_MC_GLOBAL_DRIVER_GATE_CFG_MCMAIN_MAINS_GLB_DRV_GATE_DIS_OFF (13)
  #define MCDECS_CR_MC_GLOBAL_DRIVER_GATE_CFG_MCMAIN_MAINS_GLB_DRV_GATE_DIS_WID ( 1)
  #define MCDECS_CR_MC_GLOBAL_DRIVER_GATE_CFG_MCMAIN_MAINS_GLB_DRV_GATE_DIS_MSK (0x00002000)
  #define MCDECS_CR_MC_GLOBAL_DRIVER_GATE_CFG_MCMAIN_MAINS_GLB_DRV_GATE_DIS_MIN (0)
  #define MCDECS_CR_MC_GLOBAL_DRIVER_GATE_CFG_MCMAIN_MAINS_GLB_DRV_GATE_DIS_MAX (1) // 0x00000001
  #define MCDECS_CR_MC_GLOBAL_DRIVER_GATE_CFG_MCMAIN_MAINS_GLB_DRV_GATE_DIS_DEF (0x00000000)
  #define MCDECS_CR_MC_GLOBAL_DRIVER_GATE_CFG_MCMAIN_MAINS_GLB_DRV_GATE_DIS_HSH (0x010D5138)

  #define MCDECS_CR_MC_GLOBAL_DRIVER_GATE_CFG_MCMAIN_DDRPL_GLB_DRV_GATE_DIS_OFF (14)
  #define MCDECS_CR_MC_GLOBAL_DRIVER_GATE_CFG_MCMAIN_DDRPL_GLB_DRV_GATE_DIS_WID ( 1)
  #define MCDECS_CR_MC_GLOBAL_DRIVER_GATE_CFG_MCMAIN_DDRPL_GLB_DRV_GATE_DIS_MSK (0x00004000)
  #define MCDECS_CR_MC_GLOBAL_DRIVER_GATE_CFG_MCMAIN_DDRPL_GLB_DRV_GATE_DIS_MIN (0)
  #define MCDECS_CR_MC_GLOBAL_DRIVER_GATE_CFG_MCMAIN_DDRPL_GLB_DRV_GATE_DIS_MAX (1) // 0x00000001
  #define MCDECS_CR_MC_GLOBAL_DRIVER_GATE_CFG_MCMAIN_DDRPL_GLB_DRV_GATE_DIS_DEF (0x00000000)
  #define MCDECS_CR_MC_GLOBAL_DRIVER_GATE_CFG_MCMAIN_DDRPL_GLB_DRV_GATE_DIS_HSH (0x010E5138)

#define MCDECS_CR_BIT_ERROR_RECOVERY_RANGE_SYSADDR_MCMAIN_REG          (0x00005140)

  #define MCDECS_CR_BIT_ERROR_RECOVERY_RANGE_SYSADDR_MCMAIN_sys_addr_OFF (12)
  #define MCDECS_CR_BIT_ERROR_RECOVERY_RANGE_SYSADDR_MCMAIN_sys_addr_WID (27)
  #define MCDECS_CR_BIT_ERROR_RECOVERY_RANGE_SYSADDR_MCMAIN_sys_addr_MSK (0x0000007FFFFFF000ULL)
  #define MCDECS_CR_BIT_ERROR_RECOVERY_RANGE_SYSADDR_MCMAIN_sys_addr_MIN (0)
  #define MCDECS_CR_BIT_ERROR_RECOVERY_RANGE_SYSADDR_MCMAIN_sys_addr_MAX (134217727) // 0x07FFFFFF
  #define MCDECS_CR_BIT_ERROR_RECOVERY_RANGE_SYSADDR_MCMAIN_sys_addr_DEF (0x00000000)
  #define MCDECS_CR_BIT_ERROR_RECOVERY_RANGE_SYSADDR_MCMAIN_sys_addr_HSH (0x5B0C5140)

  #define MCDECS_CR_BIT_ERROR_RECOVERY_RANGE_SYSADDR_MCMAIN_valid_OFF  (63)
  #define MCDECS_CR_BIT_ERROR_RECOVERY_RANGE_SYSADDR_MCMAIN_valid_WID  ( 1)
  #define MCDECS_CR_BIT_ERROR_RECOVERY_RANGE_SYSADDR_MCMAIN_valid_MSK  (0x8000000000000000ULL)
  #define MCDECS_CR_BIT_ERROR_RECOVERY_RANGE_SYSADDR_MCMAIN_valid_MIN  (0)
  #define MCDECS_CR_BIT_ERROR_RECOVERY_RANGE_SYSADDR_MCMAIN_valid_MAX  (1) // 0x00000001
  #define MCDECS_CR_BIT_ERROR_RECOVERY_RANGE_SYSADDR_MCMAIN_valid_DEF  (0x00000000)
  #define MCDECS_CR_BIT_ERROR_RECOVERY_RANGE_SYSADDR_MCMAIN_valid_HSH  (0x413F5140)

#define NCDECS_CR_GFXVTBAR_NCU_REG                                     (0x00005400)

  #define NCDECS_CR_GFXVTBAR_NCU_GFXVTBAREN_OFF                        ( 0)
  #define NCDECS_CR_GFXVTBAR_NCU_GFXVTBAREN_WID                        ( 1)
  #define NCDECS_CR_GFXVTBAR_NCU_GFXVTBAREN_MSK                        (0x00000001)
  #define NCDECS_CR_GFXVTBAR_NCU_GFXVTBAREN_MIN                        (0)
  #define NCDECS_CR_GFXVTBAR_NCU_GFXVTBAREN_MAX                        (1) // 0x00000001
  #define NCDECS_CR_GFXVTBAR_NCU_GFXVTBAREN_DEF                        (0x00000000)
  #define NCDECS_CR_GFXVTBAR_NCU_GFXVTBAREN_HSH                        (0x41005400)

  #define NCDECS_CR_GFXVTBAR_NCU_GFXVTBAR_OFF                          (12)
  #define NCDECS_CR_GFXVTBAR_NCU_GFXVTBAR_WID                          (27)
  #define NCDECS_CR_GFXVTBAR_NCU_GFXVTBAR_MSK                          (0x0000007FFFFFF000ULL)
  #define NCDECS_CR_GFXVTBAR_NCU_GFXVTBAR_MIN                          (0)
  #define NCDECS_CR_GFXVTBAR_NCU_GFXVTBAR_MAX                          (134217727) // 0x07FFFFFF
  #define NCDECS_CR_GFXVTBAR_NCU_GFXVTBAR_DEF                          (0x00000000)
  #define NCDECS_CR_GFXVTBAR_NCU_GFXVTBAR_HSH                          (0x5B0C5400)

#define NCDECS_CR_EDRAMBAR_NCU_REG                                     (0x00005408)

  #define NCDECS_CR_EDRAMBAR_NCU_EDRAMBAREN_OFF                        ( 0)
  #define NCDECS_CR_EDRAMBAR_NCU_EDRAMBAREN_WID                        ( 1)
  #define NCDECS_CR_EDRAMBAR_NCU_EDRAMBAREN_MSK                        (0x00000001)
  #define NCDECS_CR_EDRAMBAR_NCU_EDRAMBAREN_MIN                        (0)
  #define NCDECS_CR_EDRAMBAR_NCU_EDRAMBAREN_MAX                        (1) // 0x00000001
  #define NCDECS_CR_EDRAMBAR_NCU_EDRAMBAREN_DEF                        (0x00000000)
  #define NCDECS_CR_EDRAMBAR_NCU_EDRAMBAREN_HSH                        (0x41005408)

  #define NCDECS_CR_EDRAMBAR_NCU_EDRAMBAR_OFF                          (14)
  #define NCDECS_CR_EDRAMBAR_NCU_EDRAMBAR_WID                          (25)
  #define NCDECS_CR_EDRAMBAR_NCU_EDRAMBAR_MSK                          (0x0000007FFFFFC000ULL)
  #define NCDECS_CR_EDRAMBAR_NCU_EDRAMBAR_MIN                          (0)
  #define NCDECS_CR_EDRAMBAR_NCU_EDRAMBAR_MAX                          (33554431) // 0x01FFFFFF
  #define NCDECS_CR_EDRAMBAR_NCU_EDRAMBAR_DEF                          (0x00000000)
  #define NCDECS_CR_EDRAMBAR_NCU_EDRAMBAR_HSH                          (0x590E5408)

#define NCDECS_CR_VTDPVC0BAR_NCU_REG                                   (0x00005410)

  #define NCDECS_CR_VTDPVC0BAR_NCU_VTVC0BAREN_OFF                      ( 0)
  #define NCDECS_CR_VTDPVC0BAR_NCU_VTVC0BAREN_WID                      ( 1)
  #define NCDECS_CR_VTDPVC0BAR_NCU_VTVC0BAREN_MSK                      (0x00000001)
  #define NCDECS_CR_VTDPVC0BAR_NCU_VTVC0BAREN_MIN                      (0)
  #define NCDECS_CR_VTDPVC0BAR_NCU_VTVC0BAREN_MAX                      (1) // 0x00000001
  #define NCDECS_CR_VTDPVC0BAR_NCU_VTVC0BAREN_DEF                      (0x00000000)
  #define NCDECS_CR_VTDPVC0BAR_NCU_VTVC0BAREN_HSH                      (0x41005410)

  #define NCDECS_CR_VTDPVC0BAR_NCU_VTVC0BAR_OFF                        (12)
  #define NCDECS_CR_VTDPVC0BAR_NCU_VTVC0BAR_WID                        (27)
  #define NCDECS_CR_VTDPVC0BAR_NCU_VTVC0BAR_MSK                        (0x0000007FFFFFF000ULL)
  #define NCDECS_CR_VTDPVC0BAR_NCU_VTVC0BAR_MIN                        (0)
  #define NCDECS_CR_VTDPVC0BAR_NCU_VTVC0BAR_MAX                        (134217727) // 0x07FFFFFF
  #define NCDECS_CR_VTDPVC0BAR_NCU_VTVC0BAR_DEF                        (0x00000000)
  #define NCDECS_CR_VTDPVC0BAR_NCU_VTVC0BAR_HSH                        (0x5B0C5410)

#define NCDECS_CR_INTRDIRCTL_NCU_REG                                   (0x00005418)

  #define NCDECS_CR_INTRDIRCTL_NCU_RdrModSel_OFF                       ( 0)
  #define NCDECS_CR_INTRDIRCTL_NCU_RdrModSel_WID                       ( 3)
  #define NCDECS_CR_INTRDIRCTL_NCU_RdrModSel_MSK                       (0x00000007)
  #define NCDECS_CR_INTRDIRCTL_NCU_RdrModSel_MIN                       (0)
  #define NCDECS_CR_INTRDIRCTL_NCU_RdrModSel_MAX                       (7) // 0x00000007
  #define NCDECS_CR_INTRDIRCTL_NCU_RdrModSel_DEF                       (0x00000000)
  #define NCDECS_CR_INTRDIRCTL_NCU_RdrModSel_HSH                       (0x03005418)

  #define NCDECS_CR_INTRDIRCTL_NCU_ClastChkSmpMod_OFF                  ( 3)
  #define NCDECS_CR_INTRDIRCTL_NCU_ClastChkSmpMod_WID                  ( 1)
  #define NCDECS_CR_INTRDIRCTL_NCU_ClastChkSmpMod_MSK                  (0x00000008)
  #define NCDECS_CR_INTRDIRCTL_NCU_ClastChkSmpMod_MIN                  (0)
  #define NCDECS_CR_INTRDIRCTL_NCU_ClastChkSmpMod_MAX                  (1) // 0x00000001
  #define NCDECS_CR_INTRDIRCTL_NCU_ClastChkSmpMod_DEF                  (0x00000000)
  #define NCDECS_CR_INTRDIRCTL_NCU_ClastChkSmpMod_HSH                  (0x01035418)

  #define NCDECS_CR_INTRDIRCTL_NCU_LogFltClustMod_OFF                  ( 4)
  #define NCDECS_CR_INTRDIRCTL_NCU_LogFltClustMod_WID                  ( 1)
  #define NCDECS_CR_INTRDIRCTL_NCU_LogFltClustMod_MSK                  (0x00000010)
  #define NCDECS_CR_INTRDIRCTL_NCU_LogFltClustMod_MIN                  (0)
  #define NCDECS_CR_INTRDIRCTL_NCU_LogFltClustMod_MAX                  (1) // 0x00000001
  #define NCDECS_CR_INTRDIRCTL_NCU_LogFltClustMod_DEF                  (0x00000000)
  #define NCDECS_CR_INTRDIRCTL_NCU_LogFltClustMod_HSH                  (0x01045418)

  #define NCDECS_CR_INTRDIRCTL_NCU_LogFlatClustOvrEn_OFF               ( 5)
  #define NCDECS_CR_INTRDIRCTL_NCU_LogFlatClustOvrEn_WID               ( 1)
  #define NCDECS_CR_INTRDIRCTL_NCU_LogFlatClustOvrEn_MSK               (0x00000020)
  #define NCDECS_CR_INTRDIRCTL_NCU_LogFlatClustOvrEn_MIN               (0)
  #define NCDECS_CR_INTRDIRCTL_NCU_LogFlatClustOvrEn_MAX               (1) // 0x00000001
  #define NCDECS_CR_INTRDIRCTL_NCU_LogFlatClustOvrEn_DEF               (0x00000000)
  #define NCDECS_CR_INTRDIRCTL_NCU_LogFlatClustOvrEn_HSH               (0x01055418)

  #define NCDECS_CR_INTRDIRCTL_NCU_HashModCtr_OFF                      ( 6)
  #define NCDECS_CR_INTRDIRCTL_NCU_HashModCtr_WID                      ( 3)
  #define NCDECS_CR_INTRDIRCTL_NCU_HashModCtr_MSK                      (0x000001C0)
  #define NCDECS_CR_INTRDIRCTL_NCU_HashModCtr_MIN                      (0)
  #define NCDECS_CR_INTRDIRCTL_NCU_HashModCtr_MAX                      (7) // 0x00000007
  #define NCDECS_CR_INTRDIRCTL_NCU_HashModCtr_DEF                      (0x00000000)
  #define NCDECS_CR_INTRDIRCTL_NCU_HashModCtr_HSH                      (0x03065418)

#define NCDECS_CR_NCUCTL0_NCU_REG                                      (0x0000541C)

  #define NCDECS_CR_NCUCTL0_NCU_PLIM_OFF                               (28)
  #define NCDECS_CR_NCUCTL0_NCU_PLIM_WID                               ( 3)
  #define NCDECS_CR_NCUCTL0_NCU_PLIM_MSK                               (0x70000000)
  #define NCDECS_CR_NCUCTL0_NCU_PLIM_MIN                               (0)
  #define NCDECS_CR_NCUCTL0_NCU_PLIM_MAX                               (7) // 0x00000007
  #define NCDECS_CR_NCUCTL0_NCU_PLIM_DEF                               (0x00000003)
  #define NCDECS_CR_NCUCTL0_NCU_PLIM_HSH                               (0x031C541C)

#define NCDECS_CR_GDXCBAR_NCU_REG                                      (0x00005420)

  #define NCDECS_CR_GDXCBAR_NCU_GDXCBAREN_OFF                          ( 0)
  #define NCDECS_CR_GDXCBAR_NCU_GDXCBAREN_WID                          ( 1)
  #define NCDECS_CR_GDXCBAR_NCU_GDXCBAREN_MSK                          (0x00000001)
  #define NCDECS_CR_GDXCBAR_NCU_GDXCBAREN_MIN                          (0)
  #define NCDECS_CR_GDXCBAR_NCU_GDXCBAREN_MAX                          (1) // 0x00000001
  #define NCDECS_CR_GDXCBAR_NCU_GDXCBAREN_DEF                          (0x00000000)
  #define NCDECS_CR_GDXCBAR_NCU_GDXCBAREN_HSH                          (0x41005420)

  #define NCDECS_CR_GDXCBAR_NCU_GDXCBAR_OFF                            (12)
  #define NCDECS_CR_GDXCBAR_NCU_GDXCBAR_WID                            (27)
  #define NCDECS_CR_GDXCBAR_NCU_GDXCBAR_MSK                            (0x0000007FFFFFF000ULL)
  #define NCDECS_CR_GDXCBAR_NCU_GDXCBAR_MIN                            (0)
  #define NCDECS_CR_GDXCBAR_NCU_GDXCBAR_MAX                            (134217727) // 0x07FFFFFF
  #define NCDECS_CR_GDXCBAR_NCU_GDXCBAR_DEF                            (0x00000000)
  #define NCDECS_CR_GDXCBAR_NCU_GDXCBAR_HSH                            (0x5B0C5420)

#define NCDECS_CR_SCRATCHPAD_NCU_0_REG                                 (0x00005428)

  #define NCDECS_CR_SCRATCHPAD_NCU_0_Data_OFF                          ( 0)
  #define NCDECS_CR_SCRATCHPAD_NCU_0_Data_WID                          (32)
  #define NCDECS_CR_SCRATCHPAD_NCU_0_Data_MSK                          (0xFFFFFFFF)
  #define NCDECS_CR_SCRATCHPAD_NCU_0_Data_MIN                          (0)
  #define NCDECS_CR_SCRATCHPAD_NCU_0_Data_MAX                          (4294967295) // 0xFFFFFFFF
  #define NCDECS_CR_SCRATCHPAD_NCU_0_Data_DEF                          (0x00000000)
  #define NCDECS_CR_SCRATCHPAD_NCU_0_Data_HSH                          (0x20005428)

#define NCDECS_CR_SCRATCHPAD_NCU_1_REG                                 (0x0000542C)

  #define NCDECS_CR_SCRATCHPAD_NCU_1_Data_OFF                          ( 0)
  #define NCDECS_CR_SCRATCHPAD_NCU_1_Data_WID                          (32)
  #define NCDECS_CR_SCRATCHPAD_NCU_1_Data_MSK                          (0xFFFFFFFF)
  #define NCDECS_CR_SCRATCHPAD_NCU_1_Data_MIN                          (0)
  #define NCDECS_CR_SCRATCHPAD_NCU_1_Data_MAX                          (4294967295) // 0xFFFFFFFF
  #define NCDECS_CR_SCRATCHPAD_NCU_1_Data_DEF                          (0x00000000)
  #define NCDECS_CR_SCRATCHPAD_NCU_1_Data_HSH                          (0x2000542C)

#define NCDECS_CR_SCRATCHPAD_NCU_2_REG                                 (0x00005430)

  #define NCDECS_CR_SCRATCHPAD_NCU_2_Data_OFF                          ( 0)
  #define NCDECS_CR_SCRATCHPAD_NCU_2_Data_WID                          (32)
  #define NCDECS_CR_SCRATCHPAD_NCU_2_Data_MSK                          (0xFFFFFFFF)
  #define NCDECS_CR_SCRATCHPAD_NCU_2_Data_MIN                          (0)
  #define NCDECS_CR_SCRATCHPAD_NCU_2_Data_MAX                          (4294967295) // 0xFFFFFFFF
  #define NCDECS_CR_SCRATCHPAD_NCU_2_Data_DEF                          (0x00000000)
  #define NCDECS_CR_SCRATCHPAD_NCU_2_Data_HSH                          (0x20005430)

#define NCDECS_CR_SCRATCHPAD_NCU_3_REG                                 (0x00005434)

  #define NCDECS_CR_SCRATCHPAD_NCU_3_Data_OFF                          ( 0)
  #define NCDECS_CR_SCRATCHPAD_NCU_3_Data_WID                          (32)
  #define NCDECS_CR_SCRATCHPAD_NCU_3_Data_MSK                          (0xFFFFFFFF)
  #define NCDECS_CR_SCRATCHPAD_NCU_3_Data_MIN                          (0)
  #define NCDECS_CR_SCRATCHPAD_NCU_3_Data_MAX                          (4294967295) // 0xFFFFFFFF
  #define NCDECS_CR_SCRATCHPAD_NCU_3_Data_DEF                          (0x00000000)
  #define NCDECS_CR_SCRATCHPAD_NCU_3_Data_HSH                          (0x20005434)

#define NCDECS_CR_PAVPMSGOFFST_NCU_REG                                 (0x00005500)

  #define NCDECS_CR_PAVPMSGOFFST_NCU_LOCK_OFF                          ( 0)
  #define NCDECS_CR_PAVPMSGOFFST_NCU_LOCK_WID                          ( 1)
  #define NCDECS_CR_PAVPMSGOFFST_NCU_LOCK_MSK                          (0x00000001)
  #define NCDECS_CR_PAVPMSGOFFST_NCU_LOCK_MIN                          (0)
  #define NCDECS_CR_PAVPMSGOFFST_NCU_LOCK_MAX                          (1) // 0x00000001
  #define NCDECS_CR_PAVPMSGOFFST_NCU_LOCK_DEF                          (0x00000000)
  #define NCDECS_CR_PAVPMSGOFFST_NCU_LOCK_HSH                          (0x01005500)

  #define NCDECS_CR_PAVPMSGOFFST_NCU_OFFSET_OFF                        (20)
  #define NCDECS_CR_PAVPMSGOFFST_NCU_OFFSET_WID                        (12)
  #define NCDECS_CR_PAVPMSGOFFST_NCU_OFFSET_MSK                        (0xFFF00000)
  #define NCDECS_CR_PAVPMSGOFFST_NCU_OFFSET_MIN                        (0)
  #define NCDECS_CR_PAVPMSGOFFST_NCU_OFFSET_MAX                        (4095) // 0x00000FFF
  #define NCDECS_CR_PAVPMSGOFFST_NCU_OFFSET_DEF                        (0x00000000)
  #define NCDECS_CR_PAVPMSGOFFST_NCU_OFFSET_HSH                        (0x0C145500)

#define PCU_CR_CAMARILLO_MAILBOX_DATA0_PCU_REG                         (0x00005810)

  #define PCU_CR_CAMARILLO_MAILBOX_DATA0_PCU_DATA_OFF                  ( 0)
  #define PCU_CR_CAMARILLO_MAILBOX_DATA0_PCU_DATA_WID                  (32)
  #define PCU_CR_CAMARILLO_MAILBOX_DATA0_PCU_DATA_MSK                  (0xFFFFFFFF)
  #define PCU_CR_CAMARILLO_MAILBOX_DATA0_PCU_DATA_MIN                  (0)
  #define PCU_CR_CAMARILLO_MAILBOX_DATA0_PCU_DATA_MAX                  (4294967295) // 0xFFFFFFFF
  #define PCU_CR_CAMARILLO_MAILBOX_DATA0_PCU_DATA_DEF                  (0x00000000)
  #define PCU_CR_CAMARILLO_MAILBOX_DATA0_PCU_DATA_HSH                  (0x20005810)

#define PCU_CR_CAMARILLO_MAILBOX_DATA1_PCU_REG                         (0x00005814)

  #define PCU_CR_CAMARILLO_MAILBOX_DATA1_PCU_DATA_OFF                  ( 0)
  #define PCU_CR_CAMARILLO_MAILBOX_DATA1_PCU_DATA_WID                  (32)
  #define PCU_CR_CAMARILLO_MAILBOX_DATA1_PCU_DATA_MSK                  (0xFFFFFFFF)
  #define PCU_CR_CAMARILLO_MAILBOX_DATA1_PCU_DATA_MIN                  (0)
  #define PCU_CR_CAMARILLO_MAILBOX_DATA1_PCU_DATA_MAX                  (4294967295) // 0xFFFFFFFF
  #define PCU_CR_CAMARILLO_MAILBOX_DATA1_PCU_DATA_DEF                  (0x00000000)
  #define PCU_CR_CAMARILLO_MAILBOX_DATA1_PCU_DATA_HSH                  (0x20005814)

#define PCU_CR_CAMARILLO_MAILBOX_INTERFACE_PCU_REG                     (0x00005818)

  #define PCU_CR_CAMARILLO_MAILBOX_INTERFACE_PCU_COMMAND_OFF           ( 0)
  #define PCU_CR_CAMARILLO_MAILBOX_INTERFACE_PCU_COMMAND_WID           ( 8)
  #define PCU_CR_CAMARILLO_MAILBOX_INTERFACE_PCU_COMMAND_MSK           (0x000000FF)
  #define PCU_CR_CAMARILLO_MAILBOX_INTERFACE_PCU_COMMAND_MIN           (0)
  #define PCU_CR_CAMARILLO_MAILBOX_INTERFACE_PCU_COMMAND_MAX           (255) // 0x000000FF
  #define PCU_CR_CAMARILLO_MAILBOX_INTERFACE_PCU_COMMAND_DEF           (0x00000000)
  #define PCU_CR_CAMARILLO_MAILBOX_INTERFACE_PCU_COMMAND_HSH           (0x08005818)

  #define PCU_CR_CAMARILLO_MAILBOX_INTERFACE_PCU_ADDR_CNTL_OFF         ( 8)
  #define PCU_CR_CAMARILLO_MAILBOX_INTERFACE_PCU_ADDR_CNTL_WID         (21)
  #define PCU_CR_CAMARILLO_MAILBOX_INTERFACE_PCU_ADDR_CNTL_MSK         (0x1FFFFF00)
  #define PCU_CR_CAMARILLO_MAILBOX_INTERFACE_PCU_ADDR_CNTL_MIN         (0)
  #define PCU_CR_CAMARILLO_MAILBOX_INTERFACE_PCU_ADDR_CNTL_MAX         (2097151) // 0x001FFFFF
  #define PCU_CR_CAMARILLO_MAILBOX_INTERFACE_PCU_ADDR_CNTL_DEF         (0x00000000)
  #define PCU_CR_CAMARILLO_MAILBOX_INTERFACE_PCU_ADDR_CNTL_HSH         (0x15085818)

  #define PCU_CR_CAMARILLO_MAILBOX_INTERFACE_PCU_RUN_BUSY_OFF          (31)
  #define PCU_CR_CAMARILLO_MAILBOX_INTERFACE_PCU_RUN_BUSY_WID          ( 1)
  #define PCU_CR_CAMARILLO_MAILBOX_INTERFACE_PCU_RUN_BUSY_MSK          (0x80000000)
  #define PCU_CR_CAMARILLO_MAILBOX_INTERFACE_PCU_RUN_BUSY_MIN          (0)
  #define PCU_CR_CAMARILLO_MAILBOX_INTERFACE_PCU_RUN_BUSY_MAX          (1) // 0x00000001
  #define PCU_CR_CAMARILLO_MAILBOX_INTERFACE_PCU_RUN_BUSY_DEF          (0x00000000)
  #define PCU_CR_CAMARILLO_MAILBOX_INTERFACE_PCU_RUN_BUSY_HSH          (0x011F5818)

#define PCU_CR_PACKAGE_THERM_CAMARILLO_INTERRUPT_PCU_REG               (0x00005820)

  #define PCU_CR_PACKAGE_THERM_CAMARILLO_INTERRUPT_PCU_HIGH_TEMP_INT_ENABLE_OFF ( 0)
  #define PCU_CR_PACKAGE_THERM_CAMARILLO_INTERRUPT_PCU_HIGH_TEMP_INT_ENABLE_WID ( 1)
  #define PCU_CR_PACKAGE_THERM_CAMARILLO_INTERRUPT_PCU_HIGH_TEMP_INT_ENABLE_MSK (0x00000001)
  #define PCU_CR_PACKAGE_THERM_CAMARILLO_INTERRUPT_PCU_HIGH_TEMP_INT_ENABLE_MIN (0)
  #define PCU_CR_PACKAGE_THERM_CAMARILLO_INTERRUPT_PCU_HIGH_TEMP_INT_ENABLE_MAX (1) // 0x00000001
  #define PCU_CR_PACKAGE_THERM_CAMARILLO_INTERRUPT_PCU_HIGH_TEMP_INT_ENABLE_DEF (0x00000000)
  #define PCU_CR_PACKAGE_THERM_CAMARILLO_INTERRUPT_PCU_HIGH_TEMP_INT_ENABLE_HSH (0x01005820)

  #define PCU_CR_PACKAGE_THERM_CAMARILLO_INTERRUPT_PCU_LOW_TEMP_INT_ENABLE_OFF ( 1)
  #define PCU_CR_PACKAGE_THERM_CAMARILLO_INTERRUPT_PCU_LOW_TEMP_INT_ENABLE_WID ( 1)
  #define PCU_CR_PACKAGE_THERM_CAMARILLO_INTERRUPT_PCU_LOW_TEMP_INT_ENABLE_MSK (0x00000002)
  #define PCU_CR_PACKAGE_THERM_CAMARILLO_INTERRUPT_PCU_LOW_TEMP_INT_ENABLE_MIN (0)
  #define PCU_CR_PACKAGE_THERM_CAMARILLO_INTERRUPT_PCU_LOW_TEMP_INT_ENABLE_MAX (1) // 0x00000001
  #define PCU_CR_PACKAGE_THERM_CAMARILLO_INTERRUPT_PCU_LOW_TEMP_INT_ENABLE_DEF (0x00000000)
  #define PCU_CR_PACKAGE_THERM_CAMARILLO_INTERRUPT_PCU_LOW_TEMP_INT_ENABLE_HSH (0x01015820)

  #define PCU_CR_PACKAGE_THERM_CAMARILLO_INTERRUPT_PCU_PROCHOT_INT_ENABLE_OFF ( 2)
  #define PCU_CR_PACKAGE_THERM_CAMARILLO_INTERRUPT_PCU_PROCHOT_INT_ENABLE_WID ( 1)
  #define PCU_CR_PACKAGE_THERM_CAMARILLO_INTERRUPT_PCU_PROCHOT_INT_ENABLE_MSK (0x00000004)
  #define PCU_CR_PACKAGE_THERM_CAMARILLO_INTERRUPT_PCU_PROCHOT_INT_ENABLE_MIN (0)
  #define PCU_CR_PACKAGE_THERM_CAMARILLO_INTERRUPT_PCU_PROCHOT_INT_ENABLE_MAX (1) // 0x00000001
  #define PCU_CR_PACKAGE_THERM_CAMARILLO_INTERRUPT_PCU_PROCHOT_INT_ENABLE_DEF (0x00000000)
  #define PCU_CR_PACKAGE_THERM_CAMARILLO_INTERRUPT_PCU_PROCHOT_INT_ENABLE_HSH (0x01025820)

  #define PCU_CR_PACKAGE_THERM_CAMARILLO_INTERRUPT_PCU_OUT_OF_SPEC_INT_ENABLE_OFF ( 4)
  #define PCU_CR_PACKAGE_THERM_CAMARILLO_INTERRUPT_PCU_OUT_OF_SPEC_INT_ENABLE_WID ( 1)
  #define PCU_CR_PACKAGE_THERM_CAMARILLO_INTERRUPT_PCU_OUT_OF_SPEC_INT_ENABLE_MSK (0x00000010)
  #define PCU_CR_PACKAGE_THERM_CAMARILLO_INTERRUPT_PCU_OUT_OF_SPEC_INT_ENABLE_MIN (0)
  #define PCU_CR_PACKAGE_THERM_CAMARILLO_INTERRUPT_PCU_OUT_OF_SPEC_INT_ENABLE_MAX (1) // 0x00000001
  #define PCU_CR_PACKAGE_THERM_CAMARILLO_INTERRUPT_PCU_OUT_OF_SPEC_INT_ENABLE_DEF (0x00000000)
  #define PCU_CR_PACKAGE_THERM_CAMARILLO_INTERRUPT_PCU_OUT_OF_SPEC_INT_ENABLE_HSH (0x01045820)

  #define PCU_CR_PACKAGE_THERM_CAMARILLO_INTERRUPT_PCU_THRESHOLD_1_REL_TEMP_OFF ( 8)
  #define PCU_CR_PACKAGE_THERM_CAMARILLO_INTERRUPT_PCU_THRESHOLD_1_REL_TEMP_WID ( 7)
  #define PCU_CR_PACKAGE_THERM_CAMARILLO_INTERRUPT_PCU_THRESHOLD_1_REL_TEMP_MSK (0x00007F00)
  #define PCU_CR_PACKAGE_THERM_CAMARILLO_INTERRUPT_PCU_THRESHOLD_1_REL_TEMP_MIN (0)
  #define PCU_CR_PACKAGE_THERM_CAMARILLO_INTERRUPT_PCU_THRESHOLD_1_REL_TEMP_MAX (127) // 0x0000007F
  #define PCU_CR_PACKAGE_THERM_CAMARILLO_INTERRUPT_PCU_THRESHOLD_1_REL_TEMP_DEF (0x00000000)
  #define PCU_CR_PACKAGE_THERM_CAMARILLO_INTERRUPT_PCU_THRESHOLD_1_REL_TEMP_HSH (0x07085820)

  #define PCU_CR_PACKAGE_THERM_CAMARILLO_INTERRUPT_PCU_THRESHOLD_1_INT_ENABLE_OFF (15)
  #define PCU_CR_PACKAGE_THERM_CAMARILLO_INTERRUPT_PCU_THRESHOLD_1_INT_ENABLE_WID ( 1)
  #define PCU_CR_PACKAGE_THERM_CAMARILLO_INTERRUPT_PCU_THRESHOLD_1_INT_ENABLE_MSK (0x00008000)
  #define PCU_CR_PACKAGE_THERM_CAMARILLO_INTERRUPT_PCU_THRESHOLD_1_INT_ENABLE_MIN (0)
  #define PCU_CR_PACKAGE_THERM_CAMARILLO_INTERRUPT_PCU_THRESHOLD_1_INT_ENABLE_MAX (1) // 0x00000001
  #define PCU_CR_PACKAGE_THERM_CAMARILLO_INTERRUPT_PCU_THRESHOLD_1_INT_ENABLE_DEF (0x00000000)
  #define PCU_CR_PACKAGE_THERM_CAMARILLO_INTERRUPT_PCU_THRESHOLD_1_INT_ENABLE_HSH (0x010F5820)

  #define PCU_CR_PACKAGE_THERM_CAMARILLO_INTERRUPT_PCU_THRESHOLD_2_REL_TEMP_OFF (16)
  #define PCU_CR_PACKAGE_THERM_CAMARILLO_INTERRUPT_PCU_THRESHOLD_2_REL_TEMP_WID ( 7)
  #define PCU_CR_PACKAGE_THERM_CAMARILLO_INTERRUPT_PCU_THRESHOLD_2_REL_TEMP_MSK (0x007F0000)
  #define PCU_CR_PACKAGE_THERM_CAMARILLO_INTERRUPT_PCU_THRESHOLD_2_REL_TEMP_MIN (0)
  #define PCU_CR_PACKAGE_THERM_CAMARILLO_INTERRUPT_PCU_THRESHOLD_2_REL_TEMP_MAX (127) // 0x0000007F
  #define PCU_CR_PACKAGE_THERM_CAMARILLO_INTERRUPT_PCU_THRESHOLD_2_REL_TEMP_DEF (0x00000000)
  #define PCU_CR_PACKAGE_THERM_CAMARILLO_INTERRUPT_PCU_THRESHOLD_2_REL_TEMP_HSH (0x07105820)

  #define PCU_CR_PACKAGE_THERM_CAMARILLO_INTERRUPT_PCU_THRESHOLD_2_INT_ENABLE_OFF (23)
  #define PCU_CR_PACKAGE_THERM_CAMARILLO_INTERRUPT_PCU_THRESHOLD_2_INT_ENABLE_WID ( 1)
  #define PCU_CR_PACKAGE_THERM_CAMARILLO_INTERRUPT_PCU_THRESHOLD_2_INT_ENABLE_MSK (0x00800000)
  #define PCU_CR_PACKAGE_THERM_CAMARILLO_INTERRUPT_PCU_THRESHOLD_2_INT_ENABLE_MIN (0)
  #define PCU_CR_PACKAGE_THERM_CAMARILLO_INTERRUPT_PCU_THRESHOLD_2_INT_ENABLE_MAX (1) // 0x00000001
  #define PCU_CR_PACKAGE_THERM_CAMARILLO_INTERRUPT_PCU_THRESHOLD_2_INT_ENABLE_DEF (0x00000000)
  #define PCU_CR_PACKAGE_THERM_CAMARILLO_INTERRUPT_PCU_THRESHOLD_2_INT_ENABLE_HSH (0x01175820)

  #define PCU_CR_PACKAGE_THERM_CAMARILLO_INTERRUPT_PCU_POWER_INT_ENABLE_OFF (24)
  #define PCU_CR_PACKAGE_THERM_CAMARILLO_INTERRUPT_PCU_POWER_INT_ENABLE_WID ( 1)
  #define PCU_CR_PACKAGE_THERM_CAMARILLO_INTERRUPT_PCU_POWER_INT_ENABLE_MSK (0x01000000)
  #define PCU_CR_PACKAGE_THERM_CAMARILLO_INTERRUPT_PCU_POWER_INT_ENABLE_MIN (0)
  #define PCU_CR_PACKAGE_THERM_CAMARILLO_INTERRUPT_PCU_POWER_INT_ENABLE_MAX (1) // 0x00000001
  #define PCU_CR_PACKAGE_THERM_CAMARILLO_INTERRUPT_PCU_POWER_INT_ENABLE_DEF (0x00000000)
  #define PCU_CR_PACKAGE_THERM_CAMARILLO_INTERRUPT_PCU_POWER_INT_ENABLE_HSH (0x01185820)

#define PCU_CR_PKG_IA_C0_ANY_SUM_PCU_REG                               (0x00005828)

  #define PCU_CR_PKG_IA_C0_ANY_SUM_PCU_DATA_OFF                        ( 0)
  #define PCU_CR_PKG_IA_C0_ANY_SUM_PCU_DATA_WID                        (64)
  #define PCU_CR_PKG_IA_C0_ANY_SUM_PCU_DATA_MSK                        (0xFFFFFFFFFFFFFFFFULL)
  #define PCU_CR_PKG_IA_C0_ANY_SUM_PCU_DATA_MIN                        (0)
  #define PCU_CR_PKG_IA_C0_ANY_SUM_PCU_DATA_MAX                        (18446744073709551615ULL) // 0xFFFFFFFFFFFFFFFF
  #define PCU_CR_PKG_IA_C0_ANY_SUM_PCU_DATA_DEF                        (0x00000000)
  #define PCU_CR_PKG_IA_C0_ANY_SUM_PCU_DATA_HSH                        (0x40005828)

#define PCU_CR_PKG_IA_C0_ANY_PCU_REG                                   (0x00005830)

  #define PCU_CR_PKG_IA_C0_ANY_PCU_DATA_OFF                            ( 0)
  #define PCU_CR_PKG_IA_C0_ANY_PCU_DATA_WID                            (64)
  #define PCU_CR_PKG_IA_C0_ANY_PCU_DATA_MSK                            (0xFFFFFFFFFFFFFFFFULL)
  #define PCU_CR_PKG_IA_C0_ANY_PCU_DATA_MIN                            (0)
  #define PCU_CR_PKG_IA_C0_ANY_PCU_DATA_MAX                            (18446744073709551615ULL) // 0xFFFFFFFFFFFFFFFF
  #define PCU_CR_PKG_IA_C0_ANY_PCU_DATA_DEF                            (0x00000000)
  #define PCU_CR_PKG_IA_C0_ANY_PCU_DATA_HSH                            (0x40005830)

#define PCU_CR_PKG_GT_C0_ANY_PCU_REG                                   (0x00005838)

  #define PCU_CR_PKG_GT_C0_ANY_PCU_DATA_OFF                            ( 0)
  #define PCU_CR_PKG_GT_C0_ANY_PCU_DATA_WID                            (64)
  #define PCU_CR_PKG_GT_C0_ANY_PCU_DATA_MSK                            (0xFFFFFFFFFFFFFFFFULL)
  #define PCU_CR_PKG_GT_C0_ANY_PCU_DATA_MIN                            (0)
  #define PCU_CR_PKG_GT_C0_ANY_PCU_DATA_MAX                            (18446744073709551615ULL) // 0xFFFFFFFFFFFFFFFF
  #define PCU_CR_PKG_GT_C0_ANY_PCU_DATA_DEF                            (0x00000000)
  #define PCU_CR_PKG_GT_C0_ANY_PCU_DATA_HSH                            (0x40005838)

#define PCU_CR_PKG_GT_AND_IA_OVERLAP_PCU_REG                           (0x00005840)

  #define PCU_CR_PKG_GT_AND_IA_OVERLAP_PCU_DATA_OFF                    ( 0)
  #define PCU_CR_PKG_GT_AND_IA_OVERLAP_PCU_DATA_WID                    (64)
  #define PCU_CR_PKG_GT_AND_IA_OVERLAP_PCU_DATA_MSK                    (0xFFFFFFFFFFFFFFFFULL)
  #define PCU_CR_PKG_GT_AND_IA_OVERLAP_PCU_DATA_MIN                    (0)
  #define PCU_CR_PKG_GT_AND_IA_OVERLAP_PCU_DATA_MAX                    (18446744073709551615ULL) // 0xFFFFFFFFFFFFFFFF
  #define PCU_CR_PKG_GT_AND_IA_OVERLAP_PCU_DATA_DEF                    (0x00000000)
  #define PCU_CR_PKG_GT_AND_IA_OVERLAP_PCU_DATA_HSH                    (0x40005840)

#define PCU_CR_DDR_PTM_CTL_PCU_REG                                     (0x00005880)

  #define PCU_CR_DDR_PTM_CTL_PCU_OLTM_ENABLE_OFF                       ( 0)
  #define PCU_CR_DDR_PTM_CTL_PCU_OLTM_ENABLE_WID                       ( 1)
  #define PCU_CR_DDR_PTM_CTL_PCU_OLTM_ENABLE_MSK                       (0x00000001)
  #define PCU_CR_DDR_PTM_CTL_PCU_OLTM_ENABLE_MIN                       (0)
  #define PCU_CR_DDR_PTM_CTL_PCU_OLTM_ENABLE_MAX                       (1) // 0x00000001
  #define PCU_CR_DDR_PTM_CTL_PCU_OLTM_ENABLE_DEF                       (0x00000000)
  #define PCU_CR_DDR_PTM_CTL_PCU_OLTM_ENABLE_HSH                       (0x01005880)

  #define PCU_CR_DDR_PTM_CTL_PCU_CLTM_ENABLE_OFF                       ( 1)
  #define PCU_CR_DDR_PTM_CTL_PCU_CLTM_ENABLE_WID                       ( 1)
  #define PCU_CR_DDR_PTM_CTL_PCU_CLTM_ENABLE_MSK                       (0x00000002)
  #define PCU_CR_DDR_PTM_CTL_PCU_CLTM_ENABLE_MIN                       (0)
  #define PCU_CR_DDR_PTM_CTL_PCU_CLTM_ENABLE_MAX                       (1) // 0x00000001
  #define PCU_CR_DDR_PTM_CTL_PCU_CLTM_ENABLE_DEF                       (0x00000000)
  #define PCU_CR_DDR_PTM_CTL_PCU_CLTM_ENABLE_HSH                       (0x01015880)

  #define PCU_CR_DDR_PTM_CTL_PCU_REFRESH_2X_MODE_OFF                   ( 2)
  #define PCU_CR_DDR_PTM_CTL_PCU_REFRESH_2X_MODE_WID                   ( 2)
  #define PCU_CR_DDR_PTM_CTL_PCU_REFRESH_2X_MODE_MSK                   (0x0000000C)
  #define PCU_CR_DDR_PTM_CTL_PCU_REFRESH_2X_MODE_MIN                   (0)
  #define PCU_CR_DDR_PTM_CTL_PCU_REFRESH_2X_MODE_MAX                   (3) // 0x00000003
  #define PCU_CR_DDR_PTM_CTL_PCU_REFRESH_2X_MODE_DEF                   (0x00000000)
  #define PCU_CR_DDR_PTM_CTL_PCU_REFRESH_2X_MODE_HSH                   (0x02025880)

  #define PCU_CR_DDR_PTM_CTL_PCU_EXTTS_ENABLE_OFF                      ( 4)
  #define PCU_CR_DDR_PTM_CTL_PCU_EXTTS_ENABLE_WID                      ( 1)
  #define PCU_CR_DDR_PTM_CTL_PCU_EXTTS_ENABLE_MSK                      (0x00000010)
  #define PCU_CR_DDR_PTM_CTL_PCU_EXTTS_ENABLE_MIN                      (0)
  #define PCU_CR_DDR_PTM_CTL_PCU_EXTTS_ENABLE_MAX                      (1) // 0x00000001
  #define PCU_CR_DDR_PTM_CTL_PCU_EXTTS_ENABLE_DEF                      (0x00000000)
  #define PCU_CR_DDR_PTM_CTL_PCU_EXTTS_ENABLE_HSH                      (0x01045880)

  #define PCU_CR_DDR_PTM_CTL_PCU_LOCK_PTM_REGS_PCU_OFF                 ( 5)
  #define PCU_CR_DDR_PTM_CTL_PCU_LOCK_PTM_REGS_PCU_WID                 ( 1)
  #define PCU_CR_DDR_PTM_CTL_PCU_LOCK_PTM_REGS_PCU_MSK                 (0x00000020)
  #define PCU_CR_DDR_PTM_CTL_PCU_LOCK_PTM_REGS_PCU_MIN                 (0)
  #define PCU_CR_DDR_PTM_CTL_PCU_LOCK_PTM_REGS_PCU_MAX                 (1) // 0x00000001
  #define PCU_CR_DDR_PTM_CTL_PCU_LOCK_PTM_REGS_PCU_DEF                 (0x00000000)
  #define PCU_CR_DDR_PTM_CTL_PCU_LOCK_PTM_REGS_PCU_HSH                 (0x01055880)

  #define PCU_CR_DDR_PTM_CTL_PCU_PDWN_CONFIG_CTL_OFF                   ( 6)
  #define PCU_CR_DDR_PTM_CTL_PCU_PDWN_CONFIG_CTL_WID                   ( 1)
  #define PCU_CR_DDR_PTM_CTL_PCU_PDWN_CONFIG_CTL_MSK                   (0x00000040)
  #define PCU_CR_DDR_PTM_CTL_PCU_PDWN_CONFIG_CTL_MIN                   (0)
  #define PCU_CR_DDR_PTM_CTL_PCU_PDWN_CONFIG_CTL_MAX                   (1) // 0x00000001
  #define PCU_CR_DDR_PTM_CTL_PCU_PDWN_CONFIG_CTL_DEF                   (0x00000000)
  #define PCU_CR_DDR_PTM_CTL_PCU_PDWN_CONFIG_CTL_HSH                   (0x01065880)

  #define PCU_CR_DDR_PTM_CTL_PCU_DISABLE_DRAM_TS_OFF                   ( 7)
  #define PCU_CR_DDR_PTM_CTL_PCU_DISABLE_DRAM_TS_WID                   ( 1)
  #define PCU_CR_DDR_PTM_CTL_PCU_DISABLE_DRAM_TS_MSK                   (0x00000080)
  #define PCU_CR_DDR_PTM_CTL_PCU_DISABLE_DRAM_TS_MIN                   (0)
  #define PCU_CR_DDR_PTM_CTL_PCU_DISABLE_DRAM_TS_MAX                   (1) // 0x00000001
  #define PCU_CR_DDR_PTM_CTL_PCU_DISABLE_DRAM_TS_DEF                   (0x00000000)
  #define PCU_CR_DDR_PTM_CTL_PCU_DISABLE_DRAM_TS_HSH                   (0x01075880)

  #define PCU_CR_DDR_PTM_CTL_PCU_DDR4_SKIP_REFRESH_EN_OFF              ( 8)
  #define PCU_CR_DDR_PTM_CTL_PCU_DDR4_SKIP_REFRESH_EN_WID              ( 1)
  #define PCU_CR_DDR_PTM_CTL_PCU_DDR4_SKIP_REFRESH_EN_MSK              (0x00000100)
  #define PCU_CR_DDR_PTM_CTL_PCU_DDR4_SKIP_REFRESH_EN_MIN              (0)
  #define PCU_CR_DDR_PTM_CTL_PCU_DDR4_SKIP_REFRESH_EN_MAX              (1) // 0x00000001
  #define PCU_CR_DDR_PTM_CTL_PCU_DDR4_SKIP_REFRESH_EN_DEF              (0x00000000)
  #define PCU_CR_DDR_PTM_CTL_PCU_DDR4_SKIP_REFRESH_EN_HSH              (0x01085880)

#define PCU_CR_DDR_ENERGY_SCALEFACTOR_PCU_REG                          (0x00005884)

  #define PCU_CR_DDR_ENERGY_SCALEFACTOR_PCU_SCALEFACTOR_OFF            ( 0)
  #define PCU_CR_DDR_ENERGY_SCALEFACTOR_PCU_SCALEFACTOR_WID            ( 3)
  #define PCU_CR_DDR_ENERGY_SCALEFACTOR_PCU_SCALEFACTOR_MSK            (0x00000007)
  #define PCU_CR_DDR_ENERGY_SCALEFACTOR_PCU_SCALEFACTOR_MIN            (0)
  #define PCU_CR_DDR_ENERGY_SCALEFACTOR_PCU_SCALEFACTOR_MAX            (7) // 0x00000007
  #define PCU_CR_DDR_ENERGY_SCALEFACTOR_PCU_SCALEFACTOR_DEF            (0x00000003)
  #define PCU_CR_DDR_ENERGY_SCALEFACTOR_PCU_SCALEFACTOR_HSH            (0x03005884)

#define PCU_CR_DDR_RAPL_CHANNEL_POWER_FLOOR_PCU_REG                    (0x00005888)

  #define PCU_CR_DDR_RAPL_CHANNEL_POWER_FLOOR_PCU_CH0_OFF              ( 0)
  #define PCU_CR_DDR_RAPL_CHANNEL_POWER_FLOOR_PCU_CH0_WID              ( 8)
  #define PCU_CR_DDR_RAPL_CHANNEL_POWER_FLOOR_PCU_CH0_MSK              (0x000000FF)
  #define PCU_CR_DDR_RAPL_CHANNEL_POWER_FLOOR_PCU_CH0_MIN              (0)
  #define PCU_CR_DDR_RAPL_CHANNEL_POWER_FLOOR_PCU_CH0_MAX              (255) // 0x000000FF
  #define PCU_CR_DDR_RAPL_CHANNEL_POWER_FLOOR_PCU_CH0_DEF              (0x00000000)
  #define PCU_CR_DDR_RAPL_CHANNEL_POWER_FLOOR_PCU_CH0_HSH              (0x08005888)

  #define PCU_CR_DDR_RAPL_CHANNEL_POWER_FLOOR_PCU_CH1_OFF              ( 8)
  #define PCU_CR_DDR_RAPL_CHANNEL_POWER_FLOOR_PCU_CH1_WID              ( 8)
  #define PCU_CR_DDR_RAPL_CHANNEL_POWER_FLOOR_PCU_CH1_MSK              (0x0000FF00)
  #define PCU_CR_DDR_RAPL_CHANNEL_POWER_FLOOR_PCU_CH1_MIN              (0)
  #define PCU_CR_DDR_RAPL_CHANNEL_POWER_FLOOR_PCU_CH1_MAX              (255) // 0x000000FF
  #define PCU_CR_DDR_RAPL_CHANNEL_POWER_FLOOR_PCU_CH1_DEF              (0x00000000)
  #define PCU_CR_DDR_RAPL_CHANNEL_POWER_FLOOR_PCU_CH1_HSH              (0x08085888)

#define PCU_CR_DDR_THERM_PERDIMM_STATUS_PCU_REG                        (0x0000588C)

  #define PCU_CR_DDR_THERM_PERDIMM_STATUS_PCU_CH0_DIMM0_OFF            ( 0)
  #define PCU_CR_DDR_THERM_PERDIMM_STATUS_PCU_CH0_DIMM0_WID            ( 2)
  #define PCU_CR_DDR_THERM_PERDIMM_STATUS_PCU_CH0_DIMM0_MSK            (0x00000003)
  #define PCU_CR_DDR_THERM_PERDIMM_STATUS_PCU_CH0_DIMM0_MIN            (0)
  #define PCU_CR_DDR_THERM_PERDIMM_STATUS_PCU_CH0_DIMM0_MAX            (3) // 0x00000003
  #define PCU_CR_DDR_THERM_PERDIMM_STATUS_PCU_CH0_DIMM0_DEF            (0x00000000)
  #define PCU_CR_DDR_THERM_PERDIMM_STATUS_PCU_CH0_DIMM0_HSH            (0x0200588C)

  #define PCU_CR_DDR_THERM_PERDIMM_STATUS_PCU_CH0_DIMM1_OFF            ( 2)
  #define PCU_CR_DDR_THERM_PERDIMM_STATUS_PCU_CH0_DIMM1_WID            ( 2)
  #define PCU_CR_DDR_THERM_PERDIMM_STATUS_PCU_CH0_DIMM1_MSK            (0x0000000C)
  #define PCU_CR_DDR_THERM_PERDIMM_STATUS_PCU_CH0_DIMM1_MIN            (0)
  #define PCU_CR_DDR_THERM_PERDIMM_STATUS_PCU_CH0_DIMM1_MAX            (3) // 0x00000003
  #define PCU_CR_DDR_THERM_PERDIMM_STATUS_PCU_CH0_DIMM1_DEF            (0x00000000)
  #define PCU_CR_DDR_THERM_PERDIMM_STATUS_PCU_CH0_DIMM1_HSH            (0x0202588C)

  #define PCU_CR_DDR_THERM_PERDIMM_STATUS_PCU_CH1_DIMM0_OFF            ( 8)
  #define PCU_CR_DDR_THERM_PERDIMM_STATUS_PCU_CH1_DIMM0_WID            ( 2)
  #define PCU_CR_DDR_THERM_PERDIMM_STATUS_PCU_CH1_DIMM0_MSK            (0x00000300)
  #define PCU_CR_DDR_THERM_PERDIMM_STATUS_PCU_CH1_DIMM0_MIN            (0)
  #define PCU_CR_DDR_THERM_PERDIMM_STATUS_PCU_CH1_DIMM0_MAX            (3) // 0x00000003
  #define PCU_CR_DDR_THERM_PERDIMM_STATUS_PCU_CH1_DIMM0_DEF            (0x00000000)
  #define PCU_CR_DDR_THERM_PERDIMM_STATUS_PCU_CH1_DIMM0_HSH            (0x0208588C)

  #define PCU_CR_DDR_THERM_PERDIMM_STATUS_PCU_CH1_DIMM1_OFF            (10)
  #define PCU_CR_DDR_THERM_PERDIMM_STATUS_PCU_CH1_DIMM1_WID            ( 2)
  #define PCU_CR_DDR_THERM_PERDIMM_STATUS_PCU_CH1_DIMM1_MSK            (0x00000C00)
  #define PCU_CR_DDR_THERM_PERDIMM_STATUS_PCU_CH1_DIMM1_MIN            (0)
  #define PCU_CR_DDR_THERM_PERDIMM_STATUS_PCU_CH1_DIMM1_MAX            (3) // 0x00000003
  #define PCU_CR_DDR_THERM_PERDIMM_STATUS_PCU_CH1_DIMM1_DEF            (0x00000000)
  #define PCU_CR_DDR_THERM_PERDIMM_STATUS_PCU_CH1_DIMM1_HSH            (0x020A588C)

#define PCU_CR_DDR_WARM_THRESHOLD_CH0_PCU_REG                          (0x00005890)

  #define PCU_CR_DDR_WARM_THRESHOLD_CH0_PCU_DIMM0_OFF                  ( 0)
  #define PCU_CR_DDR_WARM_THRESHOLD_CH0_PCU_DIMM0_WID                  ( 8)
  #define PCU_CR_DDR_WARM_THRESHOLD_CH0_PCU_DIMM0_MSK                  (0x000000FF)
  #define PCU_CR_DDR_WARM_THRESHOLD_CH0_PCU_DIMM0_MIN                  (0)
  #define PCU_CR_DDR_WARM_THRESHOLD_CH0_PCU_DIMM0_MAX                  (255) // 0x000000FF
  #define PCU_CR_DDR_WARM_THRESHOLD_CH0_PCU_DIMM0_DEF                  (0x000000FF)
  #define PCU_CR_DDR_WARM_THRESHOLD_CH0_PCU_DIMM0_HSH                  (0x08005890)

  #define PCU_CR_DDR_WARM_THRESHOLD_CH0_PCU_DIMM1_OFF                  ( 8)
  #define PCU_CR_DDR_WARM_THRESHOLD_CH0_PCU_DIMM1_WID                  ( 8)
  #define PCU_CR_DDR_WARM_THRESHOLD_CH0_PCU_DIMM1_MSK                  (0x0000FF00)
  #define PCU_CR_DDR_WARM_THRESHOLD_CH0_PCU_DIMM1_MIN                  (0)
  #define PCU_CR_DDR_WARM_THRESHOLD_CH0_PCU_DIMM1_MAX                  (255) // 0x000000FF
  #define PCU_CR_DDR_WARM_THRESHOLD_CH0_PCU_DIMM1_DEF                  (0x000000FF)
  #define PCU_CR_DDR_WARM_THRESHOLD_CH0_PCU_DIMM1_HSH                  (0x08085890)

#define PCU_CR_DDR_WARM_THRESHOLD_CH1_PCU_REG                          (0x00005894)

  #define PCU_CR_DDR_WARM_THRESHOLD_CH1_PCU_DIMM0_OFF                  ( 0)
  #define PCU_CR_DDR_WARM_THRESHOLD_CH1_PCU_DIMM0_WID                  ( 8)
  #define PCU_CR_DDR_WARM_THRESHOLD_CH1_PCU_DIMM0_MSK                  (0x000000FF)
  #define PCU_CR_DDR_WARM_THRESHOLD_CH1_PCU_DIMM0_MIN                  (0)
  #define PCU_CR_DDR_WARM_THRESHOLD_CH1_PCU_DIMM0_MAX                  (255) // 0x000000FF
  #define PCU_CR_DDR_WARM_THRESHOLD_CH1_PCU_DIMM0_DEF                  (0x000000FF)
  #define PCU_CR_DDR_WARM_THRESHOLD_CH1_PCU_DIMM0_HSH                  (0x08005894)

  #define PCU_CR_DDR_WARM_THRESHOLD_CH1_PCU_DIMM1_OFF                  ( 8)
  #define PCU_CR_DDR_WARM_THRESHOLD_CH1_PCU_DIMM1_WID                  ( 8)
  #define PCU_CR_DDR_WARM_THRESHOLD_CH1_PCU_DIMM1_MSK                  (0x0000FF00)
  #define PCU_CR_DDR_WARM_THRESHOLD_CH1_PCU_DIMM1_MIN                  (0)
  #define PCU_CR_DDR_WARM_THRESHOLD_CH1_PCU_DIMM1_MAX                  (255) // 0x000000FF
  #define PCU_CR_DDR_WARM_THRESHOLD_CH1_PCU_DIMM1_DEF                  (0x000000FF)
  #define PCU_CR_DDR_WARM_THRESHOLD_CH1_PCU_DIMM1_HSH                  (0x08085894)

#define PCU_CR_DDR_HOT_THRESHOLD_CH0_PCU_REG                           (0x00005898)

  #define PCU_CR_DDR_HOT_THRESHOLD_CH0_PCU_DIMM0_OFF                   ( 0)
  #define PCU_CR_DDR_HOT_THRESHOLD_CH0_PCU_DIMM0_WID                   ( 8)
  #define PCU_CR_DDR_HOT_THRESHOLD_CH0_PCU_DIMM0_MSK                   (0x000000FF)
  #define PCU_CR_DDR_HOT_THRESHOLD_CH0_PCU_DIMM0_MIN                   (0)
  #define PCU_CR_DDR_HOT_THRESHOLD_CH0_PCU_DIMM0_MAX                   (255) // 0x000000FF
  #define PCU_CR_DDR_HOT_THRESHOLD_CH0_PCU_DIMM0_DEF                   (0x000000FF)
  #define PCU_CR_DDR_HOT_THRESHOLD_CH0_PCU_DIMM0_HSH                   (0x08005898)

  #define PCU_CR_DDR_HOT_THRESHOLD_CH0_PCU_DIMM1_OFF                   ( 8)
  #define PCU_CR_DDR_HOT_THRESHOLD_CH0_PCU_DIMM1_WID                   ( 8)
  #define PCU_CR_DDR_HOT_THRESHOLD_CH0_PCU_DIMM1_MSK                   (0x0000FF00)
  #define PCU_CR_DDR_HOT_THRESHOLD_CH0_PCU_DIMM1_MIN                   (0)
  #define PCU_CR_DDR_HOT_THRESHOLD_CH0_PCU_DIMM1_MAX                   (255) // 0x000000FF
  #define PCU_CR_DDR_HOT_THRESHOLD_CH0_PCU_DIMM1_DEF                   (0x000000FF)
  #define PCU_CR_DDR_HOT_THRESHOLD_CH0_PCU_DIMM1_HSH                   (0x08085898)

#define PCU_CR_DDR_HOT_THRESHOLD_CH1_PCU_REG                           (0x0000589C)

  #define PCU_CR_DDR_HOT_THRESHOLD_CH1_PCU_DIMM0_OFF                   ( 0)
  #define PCU_CR_DDR_HOT_THRESHOLD_CH1_PCU_DIMM0_WID                   ( 8)
  #define PCU_CR_DDR_HOT_THRESHOLD_CH1_PCU_DIMM0_MSK                   (0x000000FF)
  #define PCU_CR_DDR_HOT_THRESHOLD_CH1_PCU_DIMM0_MIN                   (0)
  #define PCU_CR_DDR_HOT_THRESHOLD_CH1_PCU_DIMM0_MAX                   (255) // 0x000000FF
  #define PCU_CR_DDR_HOT_THRESHOLD_CH1_PCU_DIMM0_DEF                   (0x000000FF)
  #define PCU_CR_DDR_HOT_THRESHOLD_CH1_PCU_DIMM0_HSH                   (0x0800589C)

  #define PCU_CR_DDR_HOT_THRESHOLD_CH1_PCU_DIMM1_OFF                   ( 8)
  #define PCU_CR_DDR_HOT_THRESHOLD_CH1_PCU_DIMM1_WID                   ( 8)
  #define PCU_CR_DDR_HOT_THRESHOLD_CH1_PCU_DIMM1_MSK                   (0x0000FF00)
  #define PCU_CR_DDR_HOT_THRESHOLD_CH1_PCU_DIMM1_MIN                   (0)
  #define PCU_CR_DDR_HOT_THRESHOLD_CH1_PCU_DIMM1_MAX                   (255) // 0x000000FF
  #define PCU_CR_DDR_HOT_THRESHOLD_CH1_PCU_DIMM1_DEF                   (0x000000FF)
  #define PCU_CR_DDR_HOT_THRESHOLD_CH1_PCU_DIMM1_HSH                   (0x0808589C)

#define PCU_CR_DDR_THERM_CAMARILLO_INTERRUPT_PCU_REG                   (0x000058A0)

  #define PCU_CR_DDR_THERM_CAMARILLO_INTERRUPT_PCU_ENABLE_WARM_INTERRUPT_OFF ( 0)
  #define PCU_CR_DDR_THERM_CAMARILLO_INTERRUPT_PCU_ENABLE_WARM_INTERRUPT_WID ( 1)
  #define PCU_CR_DDR_THERM_CAMARILLO_INTERRUPT_PCU_ENABLE_WARM_INTERRUPT_MSK (0x00000001)
  #define PCU_CR_DDR_THERM_CAMARILLO_INTERRUPT_PCU_ENABLE_WARM_INTERRUPT_MIN (0)
  #define PCU_CR_DDR_THERM_CAMARILLO_INTERRUPT_PCU_ENABLE_WARM_INTERRUPT_MAX (1) // 0x00000001
  #define PCU_CR_DDR_THERM_CAMARILLO_INTERRUPT_PCU_ENABLE_WARM_INTERRUPT_DEF (0x00000000)
  #define PCU_CR_DDR_THERM_CAMARILLO_INTERRUPT_PCU_ENABLE_WARM_INTERRUPT_HSH (0x010058A0)

  #define PCU_CR_DDR_THERM_CAMARILLO_INTERRUPT_PCU_ENABLE_HOT_INTERRUPT_OFF ( 2)
  #define PCU_CR_DDR_THERM_CAMARILLO_INTERRUPT_PCU_ENABLE_HOT_INTERRUPT_WID ( 1)
  #define PCU_CR_DDR_THERM_CAMARILLO_INTERRUPT_PCU_ENABLE_HOT_INTERRUPT_MSK (0x00000004)
  #define PCU_CR_DDR_THERM_CAMARILLO_INTERRUPT_PCU_ENABLE_HOT_INTERRUPT_MIN (0)
  #define PCU_CR_DDR_THERM_CAMARILLO_INTERRUPT_PCU_ENABLE_HOT_INTERRUPT_MAX (1) // 0x00000001
  #define PCU_CR_DDR_THERM_CAMARILLO_INTERRUPT_PCU_ENABLE_HOT_INTERRUPT_DEF (0x00000000)
  #define PCU_CR_DDR_THERM_CAMARILLO_INTERRUPT_PCU_ENABLE_HOT_INTERRUPT_HSH (0x010258A0)

  #define PCU_CR_DDR_THERM_CAMARILLO_INTERRUPT_PCU_ENABLE_2X_REFRESH_INTERRUPT_OFF ( 4)
  #define PCU_CR_DDR_THERM_CAMARILLO_INTERRUPT_PCU_ENABLE_2X_REFRESH_INTERRUPT_WID ( 1)
  #define PCU_CR_DDR_THERM_CAMARILLO_INTERRUPT_PCU_ENABLE_2X_REFRESH_INTERRUPT_MSK (0x00000010)
  #define PCU_CR_DDR_THERM_CAMARILLO_INTERRUPT_PCU_ENABLE_2X_REFRESH_INTERRUPT_MIN (0)
  #define PCU_CR_DDR_THERM_CAMARILLO_INTERRUPT_PCU_ENABLE_2X_REFRESH_INTERRUPT_MAX (1) // 0x00000001
  #define PCU_CR_DDR_THERM_CAMARILLO_INTERRUPT_PCU_ENABLE_2X_REFRESH_INTERRUPT_DEF (0x00000000)
  #define PCU_CR_DDR_THERM_CAMARILLO_INTERRUPT_PCU_ENABLE_2X_REFRESH_INTERRUPT_HSH (0x010458A0)

  #define PCU_CR_DDR_THERM_CAMARILLO_INTERRUPT_PCU_ENABLE_OOS_TEMP_INTERRUPT_OFF ( 6)
  #define PCU_CR_DDR_THERM_CAMARILLO_INTERRUPT_PCU_ENABLE_OOS_TEMP_INTERRUPT_WID ( 1)
  #define PCU_CR_DDR_THERM_CAMARILLO_INTERRUPT_PCU_ENABLE_OOS_TEMP_INTERRUPT_MSK (0x00000040)
  #define PCU_CR_DDR_THERM_CAMARILLO_INTERRUPT_PCU_ENABLE_OOS_TEMP_INTERRUPT_MIN (0)
  #define PCU_CR_DDR_THERM_CAMARILLO_INTERRUPT_PCU_ENABLE_OOS_TEMP_INTERRUPT_MAX (1) // 0x00000001
  #define PCU_CR_DDR_THERM_CAMARILLO_INTERRUPT_PCU_ENABLE_OOS_TEMP_INTERRUPT_DEF (0x00000000)
  #define PCU_CR_DDR_THERM_CAMARILLO_INTERRUPT_PCU_ENABLE_OOS_TEMP_INTERRUPT_HSH (0x010658A0)

  #define PCU_CR_DDR_THERM_CAMARILLO_INTERRUPT_PCU_ENABLE_THRESHOLD1_INTERRUPT_OFF ( 8)
  #define PCU_CR_DDR_THERM_CAMARILLO_INTERRUPT_PCU_ENABLE_THRESHOLD1_INTERRUPT_WID ( 1)
  #define PCU_CR_DDR_THERM_CAMARILLO_INTERRUPT_PCU_ENABLE_THRESHOLD1_INTERRUPT_MSK (0x00000100)
  #define PCU_CR_DDR_THERM_CAMARILLO_INTERRUPT_PCU_ENABLE_THRESHOLD1_INTERRUPT_MIN (0)
  #define PCU_CR_DDR_THERM_CAMARILLO_INTERRUPT_PCU_ENABLE_THRESHOLD1_INTERRUPT_MAX (1) // 0x00000001
  #define PCU_CR_DDR_THERM_CAMARILLO_INTERRUPT_PCU_ENABLE_THRESHOLD1_INTERRUPT_DEF (0x00000000)
  #define PCU_CR_DDR_THERM_CAMARILLO_INTERRUPT_PCU_ENABLE_THRESHOLD1_INTERRUPT_HSH (0x010858A0)

  #define PCU_CR_DDR_THERM_CAMARILLO_INTERRUPT_PCU_ENABLE_THRESHOLD2_INTERRUPT_OFF (10)
  #define PCU_CR_DDR_THERM_CAMARILLO_INTERRUPT_PCU_ENABLE_THRESHOLD2_INTERRUPT_WID ( 1)
  #define PCU_CR_DDR_THERM_CAMARILLO_INTERRUPT_PCU_ENABLE_THRESHOLD2_INTERRUPT_MSK (0x00000400)
  #define PCU_CR_DDR_THERM_CAMARILLO_INTERRUPT_PCU_ENABLE_THRESHOLD2_INTERRUPT_MIN (0)
  #define PCU_CR_DDR_THERM_CAMARILLO_INTERRUPT_PCU_ENABLE_THRESHOLD2_INTERRUPT_MAX (1) // 0x00000001
  #define PCU_CR_DDR_THERM_CAMARILLO_INTERRUPT_PCU_ENABLE_THRESHOLD2_INTERRUPT_DEF (0x00000000)
  #define PCU_CR_DDR_THERM_CAMARILLO_INTERRUPT_PCU_ENABLE_THRESHOLD2_INTERRUPT_HSH (0x010A58A0)

  #define PCU_CR_DDR_THERM_CAMARILLO_INTERRUPT_PCU_POLICY_FREE_THRESHOLD1_OFF (16)
  #define PCU_CR_DDR_THERM_CAMARILLO_INTERRUPT_PCU_POLICY_FREE_THRESHOLD1_WID ( 8)
  #define PCU_CR_DDR_THERM_CAMARILLO_INTERRUPT_PCU_POLICY_FREE_THRESHOLD1_MSK (0x00FF0000)
  #define PCU_CR_DDR_THERM_CAMARILLO_INTERRUPT_PCU_POLICY_FREE_THRESHOLD1_MIN (0)
  #define PCU_CR_DDR_THERM_CAMARILLO_INTERRUPT_PCU_POLICY_FREE_THRESHOLD1_MAX (255) // 0x000000FF
  #define PCU_CR_DDR_THERM_CAMARILLO_INTERRUPT_PCU_POLICY_FREE_THRESHOLD1_DEF (0x00000000)
  #define PCU_CR_DDR_THERM_CAMARILLO_INTERRUPT_PCU_POLICY_FREE_THRESHOLD1_HSH (0x081058A0)

  #define PCU_CR_DDR_THERM_CAMARILLO_INTERRUPT_PCU_POLICY_FREE_THRESHOLD2_OFF (24)
  #define PCU_CR_DDR_THERM_CAMARILLO_INTERRUPT_PCU_POLICY_FREE_THRESHOLD2_WID ( 8)
  #define PCU_CR_DDR_THERM_CAMARILLO_INTERRUPT_PCU_POLICY_FREE_THRESHOLD2_MSK (0xFF000000)
  #define PCU_CR_DDR_THERM_CAMARILLO_INTERRUPT_PCU_POLICY_FREE_THRESHOLD2_MIN (0)
  #define PCU_CR_DDR_THERM_CAMARILLO_INTERRUPT_PCU_POLICY_FREE_THRESHOLD2_MAX (255) // 0x000000FF
  #define PCU_CR_DDR_THERM_CAMARILLO_INTERRUPT_PCU_POLICY_FREE_THRESHOLD2_DEF (0x00000000)
  #define PCU_CR_DDR_THERM_CAMARILLO_INTERRUPT_PCU_POLICY_FREE_THRESHOLD2_HSH (0x081858A0)

#define PCU_CR_DDR_VOLTAGE_PCU_REG                                     (0x000058A4)

  #define PCU_CR_DDR_VOLTAGE_PCU_DDR_VOLTAGE_OFF                       ( 0)
  #define PCU_CR_DDR_VOLTAGE_PCU_DDR_VOLTAGE_WID                       ( 3)
  #define PCU_CR_DDR_VOLTAGE_PCU_DDR_VOLTAGE_MSK                       (0x00000007)
  #define PCU_CR_DDR_VOLTAGE_PCU_DDR_VOLTAGE_MIN                       (0)
  #define PCU_CR_DDR_VOLTAGE_PCU_DDR_VOLTAGE_MAX                       (7) // 0x00000007
  #define PCU_CR_DDR_VOLTAGE_PCU_DDR_VOLTAGE_DEF                       (0x00000000)
  #define PCU_CR_DDR_VOLTAGE_PCU_DDR_VOLTAGE_HSH                       (0x030058A4)

#define PCU_CR_PACKAGE_THERM_MARGIN_PCU_REG                            (0x000058A8)

  #define PCU_CR_PACKAGE_THERM_MARGIN_PCU_THERM_MARGIN_OFF             ( 0)
  #define PCU_CR_PACKAGE_THERM_MARGIN_PCU_THERM_MARGIN_WID             (16)
  #define PCU_CR_PACKAGE_THERM_MARGIN_PCU_THERM_MARGIN_MSK             (0x0000FFFF)
  #define PCU_CR_PACKAGE_THERM_MARGIN_PCU_THERM_MARGIN_MIN             (-32768)
  #define PCU_CR_PACKAGE_THERM_MARGIN_PCU_THERM_MARGIN_MAX             (32767) // 0x00007FFF
  #define PCU_CR_PACKAGE_THERM_MARGIN_PCU_THERM_MARGIN_DEF             (0x00007F00)
  #define PCU_CR_PACKAGE_THERM_MARGIN_PCU_THERM_MARGIN_HSH             (0x900058A8)

#define PCU_CR_DDR_DIMM_TEMPERATURE_CH0_PCU_REG                        (0x000058B0)

  #define PCU_CR_DDR_DIMM_TEMPERATURE_CH0_PCU_DIMM0_OFF                ( 0)
  #define PCU_CR_DDR_DIMM_TEMPERATURE_CH0_PCU_DIMM0_WID                ( 8)
  #define PCU_CR_DDR_DIMM_TEMPERATURE_CH0_PCU_DIMM0_MSK                (0x000000FF)
  #define PCU_CR_DDR_DIMM_TEMPERATURE_CH0_PCU_DIMM0_MIN                (0)
  #define PCU_CR_DDR_DIMM_TEMPERATURE_CH0_PCU_DIMM0_MAX                (255) // 0x000000FF
  #define PCU_CR_DDR_DIMM_TEMPERATURE_CH0_PCU_DIMM0_DEF                (0x00000000)
  #define PCU_CR_DDR_DIMM_TEMPERATURE_CH0_PCU_DIMM0_HSH                (0x080058B0)

  #define PCU_CR_DDR_DIMM_TEMPERATURE_CH0_PCU_DIMM1_OFF                ( 8)
  #define PCU_CR_DDR_DIMM_TEMPERATURE_CH0_PCU_DIMM1_WID                ( 8)
  #define PCU_CR_DDR_DIMM_TEMPERATURE_CH0_PCU_DIMM1_MSK                (0x0000FF00)
  #define PCU_CR_DDR_DIMM_TEMPERATURE_CH0_PCU_DIMM1_MIN                (0)
  #define PCU_CR_DDR_DIMM_TEMPERATURE_CH0_PCU_DIMM1_MAX                (255) // 0x000000FF
  #define PCU_CR_DDR_DIMM_TEMPERATURE_CH0_PCU_DIMM1_DEF                (0x00000000)
  #define PCU_CR_DDR_DIMM_TEMPERATURE_CH0_PCU_DIMM1_HSH                (0x080858B0)

#define PCU_CR_DDR_DIMM_TEMPERATURE_CH1_PCU_REG                        (0x000058B4)

  #define PCU_CR_DDR_DIMM_TEMPERATURE_CH1_PCU_DIMM0_OFF                ( 0)
  #define PCU_CR_DDR_DIMM_TEMPERATURE_CH1_PCU_DIMM0_WID                ( 8)
  #define PCU_CR_DDR_DIMM_TEMPERATURE_CH1_PCU_DIMM0_MSK                (0x000000FF)
  #define PCU_CR_DDR_DIMM_TEMPERATURE_CH1_PCU_DIMM0_MIN                (0)
  #define PCU_CR_DDR_DIMM_TEMPERATURE_CH1_PCU_DIMM0_MAX                (255) // 0x000000FF
  #define PCU_CR_DDR_DIMM_TEMPERATURE_CH1_PCU_DIMM0_DEF                (0x00000000)
  #define PCU_CR_DDR_DIMM_TEMPERATURE_CH1_PCU_DIMM0_HSH                (0x080058B4)

  #define PCU_CR_DDR_DIMM_TEMPERATURE_CH1_PCU_DIMM1_OFF                ( 8)
  #define PCU_CR_DDR_DIMM_TEMPERATURE_CH1_PCU_DIMM1_WID                ( 8)
  #define PCU_CR_DDR_DIMM_TEMPERATURE_CH1_PCU_DIMM1_MSK                (0x0000FF00)
  #define PCU_CR_DDR_DIMM_TEMPERATURE_CH1_PCU_DIMM1_MIN                (0)
  #define PCU_CR_DDR_DIMM_TEMPERATURE_CH1_PCU_DIMM1_MAX                (255) // 0x000000FF
  #define PCU_CR_DDR_DIMM_TEMPERATURE_CH1_PCU_DIMM1_DEF                (0x00000000)
  #define PCU_CR_DDR_DIMM_TEMPERATURE_CH1_PCU_DIMM1_HSH                (0x080858B4)

#define PCU_CR_DDR_DIMM_HOTTEST_ABSOLUTE_PCU_REG                       (0x000058B8)

  #define PCU_CR_DDR_DIMM_HOTTEST_ABSOLUTE_PCU_TEMPERATURE_OFF         ( 0)
  #define PCU_CR_DDR_DIMM_HOTTEST_ABSOLUTE_PCU_TEMPERATURE_WID         ( 8)
  #define PCU_CR_DDR_DIMM_HOTTEST_ABSOLUTE_PCU_TEMPERATURE_MSK         (0x000000FF)
  #define PCU_CR_DDR_DIMM_HOTTEST_ABSOLUTE_PCU_TEMPERATURE_MIN         (0)
  #define PCU_CR_DDR_DIMM_HOTTEST_ABSOLUTE_PCU_TEMPERATURE_MAX         (255) // 0x000000FF
  #define PCU_CR_DDR_DIMM_HOTTEST_ABSOLUTE_PCU_TEMPERATURE_DEF         (0x00000000)
  #define PCU_CR_DDR_DIMM_HOTTEST_ABSOLUTE_PCU_TEMPERATURE_HSH         (0x080058B8)

#define PCU_CR_DDR_DIMM_HOTTEST_RELATIVE_PCU_REG                       (0x000058BC)

  #define PCU_CR_DDR_DIMM_HOTTEST_RELATIVE_PCU_TEMPERATURE_OFF         ( 0)
  #define PCU_CR_DDR_DIMM_HOTTEST_RELATIVE_PCU_TEMPERATURE_WID         ( 8)
  #define PCU_CR_DDR_DIMM_HOTTEST_RELATIVE_PCU_TEMPERATURE_MSK         (0x000000FF)
  #define PCU_CR_DDR_DIMM_HOTTEST_RELATIVE_PCU_TEMPERATURE_MIN         (0)
  #define PCU_CR_DDR_DIMM_HOTTEST_RELATIVE_PCU_TEMPERATURE_MAX         (255) // 0x000000FF
  #define PCU_CR_DDR_DIMM_HOTTEST_RELATIVE_PCU_TEMPERATURE_DEF         (0x0000007F)
  #define PCU_CR_DDR_DIMM_HOTTEST_RELATIVE_PCU_TEMPERATURE_HSH         (0x080058BC)

#define PCU_CR_DDR_THROTTLE_DURATION_CH0_PCU_REG                       (0x000058C0)

  #define PCU_CR_DDR_THROTTLE_DURATION_CH0_PCU_DIMM0_OFF               ( 0)
  #define PCU_CR_DDR_THROTTLE_DURATION_CH0_PCU_DIMM0_WID               (16)
  #define PCU_CR_DDR_THROTTLE_DURATION_CH0_PCU_DIMM0_MSK               (0x0000FFFF)
  #define PCU_CR_DDR_THROTTLE_DURATION_CH0_PCU_DIMM0_MIN               (0)
  #define PCU_CR_DDR_THROTTLE_DURATION_CH0_PCU_DIMM0_MAX               (65535) // 0x0000FFFF
  #define PCU_CR_DDR_THROTTLE_DURATION_CH0_PCU_DIMM0_DEF               (0x00000000)
  #define PCU_CR_DDR_THROTTLE_DURATION_CH0_PCU_DIMM0_HSH               (0x500058C0)

  #define PCU_CR_DDR_THROTTLE_DURATION_CH0_PCU_DIMM1_OFF               (16)
  #define PCU_CR_DDR_THROTTLE_DURATION_CH0_PCU_DIMM1_WID               (16)
  #define PCU_CR_DDR_THROTTLE_DURATION_CH0_PCU_DIMM1_MSK               (0xFFFF0000)
  #define PCU_CR_DDR_THROTTLE_DURATION_CH0_PCU_DIMM1_MIN               (0)
  #define PCU_CR_DDR_THROTTLE_DURATION_CH0_PCU_DIMM1_MAX               (65535) // 0x0000FFFF
  #define PCU_CR_DDR_THROTTLE_DURATION_CH0_PCU_DIMM1_DEF               (0x00000000)
  #define PCU_CR_DDR_THROTTLE_DURATION_CH0_PCU_DIMM1_HSH               (0x501058C0)

#define PCU_CR_DDR_THROTTLE_DURATION_CH1_PCU_REG                       (0x000058C8)

  #define PCU_CR_DDR_THROTTLE_DURATION_CH1_PCU_DIMM0_OFF               ( 0)
  #define PCU_CR_DDR_THROTTLE_DURATION_CH1_PCU_DIMM0_WID               (16)
  #define PCU_CR_DDR_THROTTLE_DURATION_CH1_PCU_DIMM0_MSK               (0x0000FFFF)
  #define PCU_CR_DDR_THROTTLE_DURATION_CH1_PCU_DIMM0_MIN               (0)
  #define PCU_CR_DDR_THROTTLE_DURATION_CH1_PCU_DIMM0_MAX               (65535) // 0x0000FFFF
  #define PCU_CR_DDR_THROTTLE_DURATION_CH1_PCU_DIMM0_DEF               (0x00000000)
  #define PCU_CR_DDR_THROTTLE_DURATION_CH1_PCU_DIMM0_HSH               (0x500058C8)

  #define PCU_CR_DDR_THROTTLE_DURATION_CH1_PCU_DIMM1_OFF               (16)
  #define PCU_CR_DDR_THROTTLE_DURATION_CH1_PCU_DIMM1_WID               (16)
  #define PCU_CR_DDR_THROTTLE_DURATION_CH1_PCU_DIMM1_MSK               (0xFFFF0000)
  #define PCU_CR_DDR_THROTTLE_DURATION_CH1_PCU_DIMM1_MIN               (0)
  #define PCU_CR_DDR_THROTTLE_DURATION_CH1_PCU_DIMM1_MAX               (65535) // 0x0000FFFF
  #define PCU_CR_DDR_THROTTLE_DURATION_CH1_PCU_DIMM1_DEF               (0x00000000)
  #define PCU_CR_DDR_THROTTLE_DURATION_CH1_PCU_DIMM1_HSH               (0x501058C8)

#define PCU_CR_DDR_WARM_BUDGET_CH0_PCU_REG                             (0x000058D0)

  #define PCU_CR_DDR_WARM_BUDGET_CH0_PCU_DIMM0_OFF                     ( 0)
  #define PCU_CR_DDR_WARM_BUDGET_CH0_PCU_DIMM0_WID                     ( 8)
  #define PCU_CR_DDR_WARM_BUDGET_CH0_PCU_DIMM0_MSK                     (0x000000FF)
  #define PCU_CR_DDR_WARM_BUDGET_CH0_PCU_DIMM0_MIN                     (0)
  #define PCU_CR_DDR_WARM_BUDGET_CH0_PCU_DIMM0_MAX                     (255) // 0x000000FF
  #define PCU_CR_DDR_WARM_BUDGET_CH0_PCU_DIMM0_DEF                     (0x000000FF)
  #define PCU_CR_DDR_WARM_BUDGET_CH0_PCU_DIMM0_HSH                     (0x080058D0)

  #define PCU_CR_DDR_WARM_BUDGET_CH0_PCU_DIMM1_OFF                     ( 8)
  #define PCU_CR_DDR_WARM_BUDGET_CH0_PCU_DIMM1_WID                     ( 8)
  #define PCU_CR_DDR_WARM_BUDGET_CH0_PCU_DIMM1_MSK                     (0x0000FF00)
  #define PCU_CR_DDR_WARM_BUDGET_CH0_PCU_DIMM1_MIN                     (0)
  #define PCU_CR_DDR_WARM_BUDGET_CH0_PCU_DIMM1_MAX                     (255) // 0x000000FF
  #define PCU_CR_DDR_WARM_BUDGET_CH0_PCU_DIMM1_DEF                     (0x000000FF)
  #define PCU_CR_DDR_WARM_BUDGET_CH0_PCU_DIMM1_HSH                     (0x080858D0)

#define PCU_CR_DDR_WARM_BUDGET_CH1_PCU_REG                             (0x000058D4)

  #define PCU_CR_DDR_WARM_BUDGET_CH1_PCU_DIMM0_OFF                     ( 0)
  #define PCU_CR_DDR_WARM_BUDGET_CH1_PCU_DIMM0_WID                     ( 8)
  #define PCU_CR_DDR_WARM_BUDGET_CH1_PCU_DIMM0_MSK                     (0x000000FF)
  #define PCU_CR_DDR_WARM_BUDGET_CH1_PCU_DIMM0_MIN                     (0)
  #define PCU_CR_DDR_WARM_BUDGET_CH1_PCU_DIMM0_MAX                     (255) // 0x000000FF
  #define PCU_CR_DDR_WARM_BUDGET_CH1_PCU_DIMM0_DEF                     (0x000000FF)
  #define PCU_CR_DDR_WARM_BUDGET_CH1_PCU_DIMM0_HSH                     (0x080058D4)

  #define PCU_CR_DDR_WARM_BUDGET_CH1_PCU_DIMM1_OFF                     ( 8)
  #define PCU_CR_DDR_WARM_BUDGET_CH1_PCU_DIMM1_WID                     ( 8)
  #define PCU_CR_DDR_WARM_BUDGET_CH1_PCU_DIMM1_MSK                     (0x0000FF00)
  #define PCU_CR_DDR_WARM_BUDGET_CH1_PCU_DIMM1_MIN                     (0)
  #define PCU_CR_DDR_WARM_BUDGET_CH1_PCU_DIMM1_MAX                     (255) // 0x000000FF
  #define PCU_CR_DDR_WARM_BUDGET_CH1_PCU_DIMM1_DEF                     (0x000000FF)
  #define PCU_CR_DDR_WARM_BUDGET_CH1_PCU_DIMM1_HSH                     (0x080858D4)

#define PCU_CR_DDR_HOT_BUDGET_CH0_PCU_REG                              (0x000058D8)

  #define PCU_CR_DDR_HOT_BUDGET_CH0_PCU_DIMM0_OFF                      ( 0)
  #define PCU_CR_DDR_HOT_BUDGET_CH0_PCU_DIMM0_WID                      ( 8)
  #define PCU_CR_DDR_HOT_BUDGET_CH0_PCU_DIMM0_MSK                      (0x000000FF)
  #define PCU_CR_DDR_HOT_BUDGET_CH0_PCU_DIMM0_MIN                      (0)
  #define PCU_CR_DDR_HOT_BUDGET_CH0_PCU_DIMM0_MAX                      (255) // 0x000000FF
  #define PCU_CR_DDR_HOT_BUDGET_CH0_PCU_DIMM0_DEF                      (0x000000FF)
  #define PCU_CR_DDR_HOT_BUDGET_CH0_PCU_DIMM0_HSH                      (0x080058D8)

  #define PCU_CR_DDR_HOT_BUDGET_CH0_PCU_DIMM1_OFF                      ( 8)
  #define PCU_CR_DDR_HOT_BUDGET_CH0_PCU_DIMM1_WID                      ( 8)
  #define PCU_CR_DDR_HOT_BUDGET_CH0_PCU_DIMM1_MSK                      (0x0000FF00)
  #define PCU_CR_DDR_HOT_BUDGET_CH0_PCU_DIMM1_MIN                      (0)
  #define PCU_CR_DDR_HOT_BUDGET_CH0_PCU_DIMM1_MAX                      (255) // 0x000000FF
  #define PCU_CR_DDR_HOT_BUDGET_CH0_PCU_DIMM1_DEF                      (0x000000FF)
  #define PCU_CR_DDR_HOT_BUDGET_CH0_PCU_DIMM1_HSH                      (0x080858D8)

#define PCU_CR_DDR_HOT_BUDGET_CH1_PCU_REG                              (0x000058DC)

  #define PCU_CR_DDR_HOT_BUDGET_CH1_PCU_DIMM0_OFF                      ( 0)
  #define PCU_CR_DDR_HOT_BUDGET_CH1_PCU_DIMM0_WID                      ( 8)
  #define PCU_CR_DDR_HOT_BUDGET_CH1_PCU_DIMM0_MSK                      (0x000000FF)
  #define PCU_CR_DDR_HOT_BUDGET_CH1_PCU_DIMM0_MIN                      (0)
  #define PCU_CR_DDR_HOT_BUDGET_CH1_PCU_DIMM0_MAX                      (255) // 0x000000FF
  #define PCU_CR_DDR_HOT_BUDGET_CH1_PCU_DIMM0_DEF                      (0x000000FF)
  #define PCU_CR_DDR_HOT_BUDGET_CH1_PCU_DIMM0_HSH                      (0x080058DC)

  #define PCU_CR_DDR_HOT_BUDGET_CH1_PCU_DIMM1_OFF                      ( 8)
  #define PCU_CR_DDR_HOT_BUDGET_CH1_PCU_DIMM1_WID                      ( 8)
  #define PCU_CR_DDR_HOT_BUDGET_CH1_PCU_DIMM1_MSK                      (0x0000FF00)
  #define PCU_CR_DDR_HOT_BUDGET_CH1_PCU_DIMM1_MIN                      (0)
  #define PCU_CR_DDR_HOT_BUDGET_CH1_PCU_DIMM1_MAX                      (255) // 0x000000FF
  #define PCU_CR_DDR_HOT_BUDGET_CH1_PCU_DIMM1_DEF                      (0x000000FF)
  #define PCU_CR_DDR_HOT_BUDGET_CH1_PCU_DIMM1_HSH                      (0x080858DC)

#define PCU_CR_DDR_RAPL_LIMIT_PCU_REG                                  (0x000058E0)

  #define PCU_CR_DDR_RAPL_LIMIT_PCU_LIMIT1_POWER_OFF                   ( 0)
  #define PCU_CR_DDR_RAPL_LIMIT_PCU_LIMIT1_POWER_WID                   (15)
  #define PCU_CR_DDR_RAPL_LIMIT_PCU_LIMIT1_POWER_MSK                   (0x00007FFF)
  #define PCU_CR_DDR_RAPL_LIMIT_PCU_LIMIT1_POWER_MIN                   (0)
  #define PCU_CR_DDR_RAPL_LIMIT_PCU_LIMIT1_POWER_MAX                   (32767) // 0x00007FFF
  #define PCU_CR_DDR_RAPL_LIMIT_PCU_LIMIT1_POWER_DEF                   (0x00000000)
  #define PCU_CR_DDR_RAPL_LIMIT_PCU_LIMIT1_POWER_HSH                   (0x4F0058E0)

  #define PCU_CR_DDR_RAPL_LIMIT_PCU_LIMIT1_ENABLE_OFF                  (15)
  #define PCU_CR_DDR_RAPL_LIMIT_PCU_LIMIT1_ENABLE_WID                  ( 1)
  #define PCU_CR_DDR_RAPL_LIMIT_PCU_LIMIT1_ENABLE_MSK                  (0x00008000)
  #define PCU_CR_DDR_RAPL_LIMIT_PCU_LIMIT1_ENABLE_MIN                  (0)
  #define PCU_CR_DDR_RAPL_LIMIT_PCU_LIMIT1_ENABLE_MAX                  (1) // 0x00000001
  #define PCU_CR_DDR_RAPL_LIMIT_PCU_LIMIT1_ENABLE_DEF                  (0x00000000)
  #define PCU_CR_DDR_RAPL_LIMIT_PCU_LIMIT1_ENABLE_HSH                  (0x410F58E0)

  #define PCU_CR_DDR_RAPL_LIMIT_PCU_LIMIT1_TIME_WINDOW_Y_OFF           (17)
  #define PCU_CR_DDR_RAPL_LIMIT_PCU_LIMIT1_TIME_WINDOW_Y_WID           ( 5)
  #define PCU_CR_DDR_RAPL_LIMIT_PCU_LIMIT1_TIME_WINDOW_Y_MSK           (0x003E0000)
  #define PCU_CR_DDR_RAPL_LIMIT_PCU_LIMIT1_TIME_WINDOW_Y_MIN           (0)
  #define PCU_CR_DDR_RAPL_LIMIT_PCU_LIMIT1_TIME_WINDOW_Y_MAX           (31) // 0x0000001F
  #define PCU_CR_DDR_RAPL_LIMIT_PCU_LIMIT1_TIME_WINDOW_Y_DEF           (0x00000000)
  #define PCU_CR_DDR_RAPL_LIMIT_PCU_LIMIT1_TIME_WINDOW_Y_HSH           (0x451158E0)

  #define PCU_CR_DDR_RAPL_LIMIT_PCU_LIMIT1_TIME_WINDOW_X_OFF           (22)
  #define PCU_CR_DDR_RAPL_LIMIT_PCU_LIMIT1_TIME_WINDOW_X_WID           ( 2)
  #define PCU_CR_DDR_RAPL_LIMIT_PCU_LIMIT1_TIME_WINDOW_X_MSK           (0x00C00000)
  #define PCU_CR_DDR_RAPL_LIMIT_PCU_LIMIT1_TIME_WINDOW_X_MIN           (0)
  #define PCU_CR_DDR_RAPL_LIMIT_PCU_LIMIT1_TIME_WINDOW_X_MAX           (3) // 0x00000003
  #define PCU_CR_DDR_RAPL_LIMIT_PCU_LIMIT1_TIME_WINDOW_X_DEF           (0x00000000)
  #define PCU_CR_DDR_RAPL_LIMIT_PCU_LIMIT1_TIME_WINDOW_X_HSH           (0x421658E0)

  #define PCU_CR_DDR_RAPL_LIMIT_PCU_LIMIT2_POWER_OFF                   (32)
  #define PCU_CR_DDR_RAPL_LIMIT_PCU_LIMIT2_POWER_WID                   (15)
  #define PCU_CR_DDR_RAPL_LIMIT_PCU_LIMIT2_POWER_MSK                   (0x00007FFF00000000ULL)
  #define PCU_CR_DDR_RAPL_LIMIT_PCU_LIMIT2_POWER_MIN                   (0)
  #define PCU_CR_DDR_RAPL_LIMIT_PCU_LIMIT2_POWER_MAX                   (32767) // 0x00007FFF
  #define PCU_CR_DDR_RAPL_LIMIT_PCU_LIMIT2_POWER_DEF                   (0x00000000)
  #define PCU_CR_DDR_RAPL_LIMIT_PCU_LIMIT2_POWER_HSH                   (0x4F2058E0)

  #define PCU_CR_DDR_RAPL_LIMIT_PCU_LIMIT2_ENABLE_OFF                  (47)
  #define PCU_CR_DDR_RAPL_LIMIT_PCU_LIMIT2_ENABLE_WID                  ( 1)
  #define PCU_CR_DDR_RAPL_LIMIT_PCU_LIMIT2_ENABLE_MSK                  (0x0000800000000000ULL)
  #define PCU_CR_DDR_RAPL_LIMIT_PCU_LIMIT2_ENABLE_MIN                  (0)
  #define PCU_CR_DDR_RAPL_LIMIT_PCU_LIMIT2_ENABLE_MAX                  (1) // 0x00000001
  #define PCU_CR_DDR_RAPL_LIMIT_PCU_LIMIT2_ENABLE_DEF                  (0x00000000)
  #define PCU_CR_DDR_RAPL_LIMIT_PCU_LIMIT2_ENABLE_HSH                  (0x412F58E0)

  #define PCU_CR_DDR_RAPL_LIMIT_PCU_LIMIT2_TIME_WINDOW_Y_OFF           (49)
  #define PCU_CR_DDR_RAPL_LIMIT_PCU_LIMIT2_TIME_WINDOW_Y_WID           ( 5)
  #define PCU_CR_DDR_RAPL_LIMIT_PCU_LIMIT2_TIME_WINDOW_Y_MSK           (0x003E000000000000ULL)
  #define PCU_CR_DDR_RAPL_LIMIT_PCU_LIMIT2_TIME_WINDOW_Y_MIN           (0)
  #define PCU_CR_DDR_RAPL_LIMIT_PCU_LIMIT2_TIME_WINDOW_Y_MAX           (31) // 0x0000001F
  #define PCU_CR_DDR_RAPL_LIMIT_PCU_LIMIT2_TIME_WINDOW_Y_DEF           (0x00000000)
  #define PCU_CR_DDR_RAPL_LIMIT_PCU_LIMIT2_TIME_WINDOW_Y_HSH           (0x453158E0)

  #define PCU_CR_DDR_RAPL_LIMIT_PCU_LIMIT2_TIME_WINDOW_X_OFF           (54)
  #define PCU_CR_DDR_RAPL_LIMIT_PCU_LIMIT2_TIME_WINDOW_X_WID           ( 2)
  #define PCU_CR_DDR_RAPL_LIMIT_PCU_LIMIT2_TIME_WINDOW_X_MSK           (0x00C0000000000000ULL)
  #define PCU_CR_DDR_RAPL_LIMIT_PCU_LIMIT2_TIME_WINDOW_X_MIN           (0)
  #define PCU_CR_DDR_RAPL_LIMIT_PCU_LIMIT2_TIME_WINDOW_X_MAX           (3) // 0x00000003
  #define PCU_CR_DDR_RAPL_LIMIT_PCU_LIMIT2_TIME_WINDOW_X_DEF           (0x00000000)
  #define PCU_CR_DDR_RAPL_LIMIT_PCU_LIMIT2_TIME_WINDOW_X_HSH           (0x423658E0)

  #define PCU_CR_DDR_RAPL_LIMIT_PCU_LOCKED_OFF                         (63)
  #define PCU_CR_DDR_RAPL_LIMIT_PCU_LOCKED_WID                         ( 1)
  #define PCU_CR_DDR_RAPL_LIMIT_PCU_LOCKED_MSK                         (0x8000000000000000ULL)
  #define PCU_CR_DDR_RAPL_LIMIT_PCU_LOCKED_MIN                         (0)
  #define PCU_CR_DDR_RAPL_LIMIT_PCU_LOCKED_MAX                         (1) // 0x00000001
  #define PCU_CR_DDR_RAPL_LIMIT_PCU_LOCKED_DEF                         (0x00000000)
  #define PCU_CR_DDR_RAPL_LIMIT_PCU_LOCKED_HSH                         (0x413F58E0)

#define PCU_CR_DDR_ENERGY_STATUS_PCU_REG                               (0x000058E8)

  #define PCU_CR_DDR_ENERGY_STATUS_PCU_JOULES_CONSUMED_OFF             ( 0)
  #define PCU_CR_DDR_ENERGY_STATUS_PCU_JOULES_CONSUMED_WID             (32)
  #define PCU_CR_DDR_ENERGY_STATUS_PCU_JOULES_CONSUMED_MSK             (0xFFFFFFFF)
  #define PCU_CR_DDR_ENERGY_STATUS_PCU_JOULES_CONSUMED_MIN             (0)
  #define PCU_CR_DDR_ENERGY_STATUS_PCU_JOULES_CONSUMED_MAX             (4294967295) // 0xFFFFFFFF
  #define PCU_CR_DDR_ENERGY_STATUS_PCU_JOULES_CONSUMED_DEF             (0x00000000)
  #define PCU_CR_DDR_ENERGY_STATUS_PCU_JOULES_CONSUMED_HSH             (0x200058E8)

#define PCU_CR_DDR_RAPL_PERF_STATUS_PCU_REG                            (0x000058EC)

  #define PCU_CR_DDR_RAPL_PERF_STATUS_PCU_DURATION_OFF                 ( 0)
  #define PCU_CR_DDR_RAPL_PERF_STATUS_PCU_DURATION_WID                 (32)
  #define PCU_CR_DDR_RAPL_PERF_STATUS_PCU_DURATION_MSK                 (0xFFFFFFFF)
  #define PCU_CR_DDR_RAPL_PERF_STATUS_PCU_DURATION_MIN                 (0)
  #define PCU_CR_DDR_RAPL_PERF_STATUS_PCU_DURATION_MAX                 (4294967295) // 0xFFFFFFFF
  #define PCU_CR_DDR_RAPL_PERF_STATUS_PCU_DURATION_DEF                 (0x00000000)
  #define PCU_CR_DDR_RAPL_PERF_STATUS_PCU_DURATION_HSH                 (0x200058EC)

#define PCU_CR_PACKAGE_RAPL_PERF_STATUS_PCU_REG                        (0x000058F0)

  #define PCU_CR_PACKAGE_RAPL_PERF_STATUS_PCU_COUNTS_OFF               ( 0)
  #define PCU_CR_PACKAGE_RAPL_PERF_STATUS_PCU_COUNTS_WID               (32)
  #define PCU_CR_PACKAGE_RAPL_PERF_STATUS_PCU_COUNTS_MSK               (0xFFFFFFFF)
  #define PCU_CR_PACKAGE_RAPL_PERF_STATUS_PCU_COUNTS_MIN               (0)
  #define PCU_CR_PACKAGE_RAPL_PERF_STATUS_PCU_COUNTS_MAX               (4294967295) // 0xFFFFFFFF
  #define PCU_CR_PACKAGE_RAPL_PERF_STATUS_PCU_COUNTS_DEF               (0x00000000)
  #define PCU_CR_PACKAGE_RAPL_PERF_STATUS_PCU_COUNTS_HSH               (0x200058F0)

#define PCU_CR_PKGC_LTR_LATENCY_MEASUREMENTS_PCU_REG                   (0x000058F8)

  #define PCU_CR_PKGC_LTR_LATENCY_MEASUREMENTS_PCU_DDR_ACCESS_TIME_OFF ( 0)
  #define PCU_CR_PKGC_LTR_LATENCY_MEASUREMENTS_PCU_DDR_ACCESS_TIME_WID (14)
  #define PCU_CR_PKGC_LTR_LATENCY_MEASUREMENTS_PCU_DDR_ACCESS_TIME_MSK (0x00003FFF)
  #define PCU_CR_PKGC_LTR_LATENCY_MEASUREMENTS_PCU_DDR_ACCESS_TIME_MIN (0)
  #define PCU_CR_PKGC_LTR_LATENCY_MEASUREMENTS_PCU_DDR_ACCESS_TIME_MAX (16383) // 0x00003FFF
  #define PCU_CR_PKGC_LTR_LATENCY_MEASUREMENTS_PCU_DDR_ACCESS_TIME_DEF (0x00000000)
  #define PCU_CR_PKGC_LTR_LATENCY_MEASUREMENTS_PCU_DDR_ACCESS_TIME_HSH (0x0E0058F8)

  #define PCU_CR_PKGC_LTR_LATENCY_MEASUREMENTS_PCU_RESERVED_OFF        (14)
  #define PCU_CR_PKGC_LTR_LATENCY_MEASUREMENTS_PCU_RESERVED_WID        ( 1)
  #define PCU_CR_PKGC_LTR_LATENCY_MEASUREMENTS_PCU_RESERVED_MSK        (0x00004000)
  #define PCU_CR_PKGC_LTR_LATENCY_MEASUREMENTS_PCU_RESERVED_MIN        (0)
  #define PCU_CR_PKGC_LTR_LATENCY_MEASUREMENTS_PCU_RESERVED_MAX        (1) // 0x00000001
  #define PCU_CR_PKGC_LTR_LATENCY_MEASUREMENTS_PCU_RESERVED_DEF        (0x00000000)
  #define PCU_CR_PKGC_LTR_LATENCY_MEASUREMENTS_PCU_RESERVED_HSH        (0x010E58F8)

  #define PCU_CR_PKGC_LTR_LATENCY_MEASUREMENTS_PCU_CLR_ACCESS_TIME_OFF (15)
  #define PCU_CR_PKGC_LTR_LATENCY_MEASUREMENTS_PCU_CLR_ACCESS_TIME_WID (14)
  #define PCU_CR_PKGC_LTR_LATENCY_MEASUREMENTS_PCU_CLR_ACCESS_TIME_MSK (0x1FFF8000)
  #define PCU_CR_PKGC_LTR_LATENCY_MEASUREMENTS_PCU_CLR_ACCESS_TIME_MIN (0)
  #define PCU_CR_PKGC_LTR_LATENCY_MEASUREMENTS_PCU_CLR_ACCESS_TIME_MAX (16383) // 0x00003FFF
  #define PCU_CR_PKGC_LTR_LATENCY_MEASUREMENTS_PCU_CLR_ACCESS_TIME_DEF (0x00000000)
  #define PCU_CR_PKGC_LTR_LATENCY_MEASUREMENTS_PCU_CLR_ACCESS_TIME_HSH (0x0E0F58F8)

  #define PCU_CR_PKGC_LTR_LATENCY_MEASUREMENTS_PCU_NON_SNOOP_THRESHOLD_RESOLUTION_OFF (29)
  #define PCU_CR_PKGC_LTR_LATENCY_MEASUREMENTS_PCU_NON_SNOOP_THRESHOLD_RESOLUTION_WID ( 1)
  #define PCU_CR_PKGC_LTR_LATENCY_MEASUREMENTS_PCU_NON_SNOOP_THRESHOLD_RESOLUTION_MSK (0x20000000)
  #define PCU_CR_PKGC_LTR_LATENCY_MEASUREMENTS_PCU_NON_SNOOP_THRESHOLD_RESOLUTION_MIN (0)
  #define PCU_CR_PKGC_LTR_LATENCY_MEASUREMENTS_PCU_NON_SNOOP_THRESHOLD_RESOLUTION_MAX (1) // 0x00000001
  #define PCU_CR_PKGC_LTR_LATENCY_MEASUREMENTS_PCU_NON_SNOOP_THRESHOLD_RESOLUTION_DEF (0x00000000)
  #define PCU_CR_PKGC_LTR_LATENCY_MEASUREMENTS_PCU_NON_SNOOP_THRESHOLD_RESOLUTION_HSH (0x011D58F8)

  #define PCU_CR_PKGC_LTR_LATENCY_MEASUREMENTS_PCU_SLOW_SNOOP_THRESHOLD_RESOLUTION_OFF (30)
  #define PCU_CR_PKGC_LTR_LATENCY_MEASUREMENTS_PCU_SLOW_SNOOP_THRESHOLD_RESOLUTION_WID ( 1)
  #define PCU_CR_PKGC_LTR_LATENCY_MEASUREMENTS_PCU_SLOW_SNOOP_THRESHOLD_RESOLUTION_MSK (0x40000000)
  #define PCU_CR_PKGC_LTR_LATENCY_MEASUREMENTS_PCU_SLOW_SNOOP_THRESHOLD_RESOLUTION_MIN (0)
  #define PCU_CR_PKGC_LTR_LATENCY_MEASUREMENTS_PCU_SLOW_SNOOP_THRESHOLD_RESOLUTION_MAX (1) // 0x00000001
  #define PCU_CR_PKGC_LTR_LATENCY_MEASUREMENTS_PCU_SLOW_SNOOP_THRESHOLD_RESOLUTION_DEF (0x00000000)
  #define PCU_CR_PKGC_LTR_LATENCY_MEASUREMENTS_PCU_SLOW_SNOOP_THRESHOLD_RESOLUTION_HSH (0x011E58F8)

  #define PCU_CR_PKGC_LTR_LATENCY_MEASUREMENTS_PCU_FAST_SNOOP_THRESHOLD_RESOLUTION_OFF (31)
  #define PCU_CR_PKGC_LTR_LATENCY_MEASUREMENTS_PCU_FAST_SNOOP_THRESHOLD_RESOLUTION_WID ( 1)
  #define PCU_CR_PKGC_LTR_LATENCY_MEASUREMENTS_PCU_FAST_SNOOP_THRESHOLD_RESOLUTION_MSK (0x80000000)
  #define PCU_CR_PKGC_LTR_LATENCY_MEASUREMENTS_PCU_FAST_SNOOP_THRESHOLD_RESOLUTION_MIN (0)
  #define PCU_CR_PKGC_LTR_LATENCY_MEASUREMENTS_PCU_FAST_SNOOP_THRESHOLD_RESOLUTION_MAX (1) // 0x00000001
  #define PCU_CR_PKGC_LTR_LATENCY_MEASUREMENTS_PCU_FAST_SNOOP_THRESHOLD_RESOLUTION_DEF (0x00000000)
  #define PCU_CR_PKGC_LTR_LATENCY_MEASUREMENTS_PCU_FAST_SNOOP_THRESHOLD_RESOLUTION_HSH (0x011F58F8)

#define PCU_CR_IA_PERF_LIMIT_REASONS_PCU_REG                           (0x000058FC)

  #define PCU_CR_IA_PERF_LIMIT_REASONS_PCU_PROCHOT_STATUS_OFF          ( 0)
  #define PCU_CR_IA_PERF_LIMIT_REASONS_PCU_PROCHOT_STATUS_WID          ( 1)
  #define PCU_CR_IA_PERF_LIMIT_REASONS_PCU_PROCHOT_STATUS_MSK          (0x00000001)
  #define PCU_CR_IA_PERF_LIMIT_REASONS_PCU_PROCHOT_STATUS_MIN          (0)
  #define PCU_CR_IA_PERF_LIMIT_REASONS_PCU_PROCHOT_STATUS_MAX          (1) // 0x00000001
  #define PCU_CR_IA_PERF_LIMIT_REASONS_PCU_PROCHOT_STATUS_DEF          (0x00000000)
  #define PCU_CR_IA_PERF_LIMIT_REASONS_PCU_PROCHOT_STATUS_HSH          (0x010058FC)

  #define PCU_CR_IA_PERF_LIMIT_REASONS_PCU_THERMAL_STATUS_OFF          ( 1)
  #define PCU_CR_IA_PERF_LIMIT_REASONS_PCU_THERMAL_STATUS_WID          ( 1)
  #define PCU_CR_IA_PERF_LIMIT_REASONS_PCU_THERMAL_STATUS_MSK          (0x00000002)
  #define PCU_CR_IA_PERF_LIMIT_REASONS_PCU_THERMAL_STATUS_MIN          (0)
  #define PCU_CR_IA_PERF_LIMIT_REASONS_PCU_THERMAL_STATUS_MAX          (1) // 0x00000001
  #define PCU_CR_IA_PERF_LIMIT_REASONS_PCU_THERMAL_STATUS_DEF          (0x00000000)
  #define PCU_CR_IA_PERF_LIMIT_REASONS_PCU_THERMAL_STATUS_HSH          (0x010158FC)

  #define PCU_CR_IA_PERF_LIMIT_REASONS_PCU_SPARE_IA_2_OFF              ( 2)
  #define PCU_CR_IA_PERF_LIMIT_REASONS_PCU_SPARE_IA_2_WID              ( 1)
  #define PCU_CR_IA_PERF_LIMIT_REASONS_PCU_SPARE_IA_2_MSK              (0x00000004)
  #define PCU_CR_IA_PERF_LIMIT_REASONS_PCU_SPARE_IA_2_MIN              (0)
  #define PCU_CR_IA_PERF_LIMIT_REASONS_PCU_SPARE_IA_2_MAX              (1) // 0x00000001
  #define PCU_CR_IA_PERF_LIMIT_REASONS_PCU_SPARE_IA_2_DEF              (0x00000000)
  #define PCU_CR_IA_PERF_LIMIT_REASONS_PCU_SPARE_IA_2_HSH              (0x010258FC)

  #define PCU_CR_IA_PERF_LIMIT_REASONS_PCU_RAPL_PL1_STATUS_OFF         ( 3)
  #define PCU_CR_IA_PERF_LIMIT_REASONS_PCU_RAPL_PL1_STATUS_WID         ( 1)
  #define PCU_CR_IA_PERF_LIMIT_REASONS_PCU_RAPL_PL1_STATUS_MSK         (0x00000008)
  #define PCU_CR_IA_PERF_LIMIT_REASONS_PCU_RAPL_PL1_STATUS_MIN         (0)
  #define PCU_CR_IA_PERF_LIMIT_REASONS_PCU_RAPL_PL1_STATUS_MAX         (1) // 0x00000001
  #define PCU_CR_IA_PERF_LIMIT_REASONS_PCU_RAPL_PL1_STATUS_DEF         (0x00000000)
  #define PCU_CR_IA_PERF_LIMIT_REASONS_PCU_RAPL_PL1_STATUS_HSH         (0x010358FC)

  #define PCU_CR_IA_PERF_LIMIT_REASONS_PCU_RAPL_PL2_STATUS_OFF         ( 4)
  #define PCU_CR_IA_PERF_LIMIT_REASONS_PCU_RAPL_PL2_STATUS_WID         ( 1)
  #define PCU_CR_IA_PERF_LIMIT_REASONS_PCU_RAPL_PL2_STATUS_MSK         (0x00000010)
  #define PCU_CR_IA_PERF_LIMIT_REASONS_PCU_RAPL_PL2_STATUS_MIN         (0)
  #define PCU_CR_IA_PERF_LIMIT_REASONS_PCU_RAPL_PL2_STATUS_MAX         (1) // 0x00000001
  #define PCU_CR_IA_PERF_LIMIT_REASONS_PCU_RAPL_PL2_STATUS_DEF         (0x00000000)
  #define PCU_CR_IA_PERF_LIMIT_REASONS_PCU_RAPL_PL2_STATUS_HSH         (0x010458FC)

  #define PCU_CR_IA_PERF_LIMIT_REASONS_PCU_RAPL_PL3_STATUS_OFF         ( 5)
  #define PCU_CR_IA_PERF_LIMIT_REASONS_PCU_RAPL_PL3_STATUS_WID         ( 1)
  #define PCU_CR_IA_PERF_LIMIT_REASONS_PCU_RAPL_PL3_STATUS_MSK         (0x00000020)
  #define PCU_CR_IA_PERF_LIMIT_REASONS_PCU_RAPL_PL3_STATUS_MIN         (0)
  #define PCU_CR_IA_PERF_LIMIT_REASONS_PCU_RAPL_PL3_STATUS_MAX         (1) // 0x00000001
  #define PCU_CR_IA_PERF_LIMIT_REASONS_PCU_RAPL_PL3_STATUS_DEF         (0x00000000)
  #define PCU_CR_IA_PERF_LIMIT_REASONS_PCU_RAPL_PL3_STATUS_HSH         (0x010558FC)

  #define PCU_CR_IA_PERF_LIMIT_REASONS_PCU_EE_STATUS_OFF               ( 6)
  #define PCU_CR_IA_PERF_LIMIT_REASONS_PCU_EE_STATUS_WID               ( 1)
  #define PCU_CR_IA_PERF_LIMIT_REASONS_PCU_EE_STATUS_MSK               (0x00000040)
  #define PCU_CR_IA_PERF_LIMIT_REASONS_PCU_EE_STATUS_MIN               (0)
  #define PCU_CR_IA_PERF_LIMIT_REASONS_PCU_EE_STATUS_MAX               (1) // 0x00000001
  #define PCU_CR_IA_PERF_LIMIT_REASONS_PCU_EE_STATUS_DEF               (0x00000000)
  #define PCU_CR_IA_PERF_LIMIT_REASONS_PCU_EE_STATUS_HSH               (0x010658FC)

  #define PCU_CR_IA_PERF_LIMIT_REASONS_PCU_GT_DRIVER_STATUS_OFF        ( 7)
  #define PCU_CR_IA_PERF_LIMIT_REASONS_PCU_GT_DRIVER_STATUS_WID        ( 1)
  #define PCU_CR_IA_PERF_LIMIT_REASONS_PCU_GT_DRIVER_STATUS_MSK        (0x00000080)
  #define PCU_CR_IA_PERF_LIMIT_REASONS_PCU_GT_DRIVER_STATUS_MIN        (0)
  #define PCU_CR_IA_PERF_LIMIT_REASONS_PCU_GT_DRIVER_STATUS_MAX        (1) // 0x00000001
  #define PCU_CR_IA_PERF_LIMIT_REASONS_PCU_GT_DRIVER_STATUS_DEF        (0x00000000)
  #define PCU_CR_IA_PERF_LIMIT_REASONS_PCU_GT_DRIVER_STATUS_HSH        (0x010758FC)

  #define PCU_CR_IA_PERF_LIMIT_REASONS_PCU_PKG_VR_THERM_ALERT_STATUS_OFF ( 8)
  #define PCU_CR_IA_PERF_LIMIT_REASONS_PCU_PKG_VR_THERM_ALERT_STATUS_WID ( 1)
  #define PCU_CR_IA_PERF_LIMIT_REASONS_PCU_PKG_VR_THERM_ALERT_STATUS_MSK (0x00000100)
  #define PCU_CR_IA_PERF_LIMIT_REASONS_PCU_PKG_VR_THERM_ALERT_STATUS_MIN (0)
  #define PCU_CR_IA_PERF_LIMIT_REASONS_PCU_PKG_VR_THERM_ALERT_STATUS_MAX (1) // 0x00000001
  #define PCU_CR_IA_PERF_LIMIT_REASONS_PCU_PKG_VR_THERM_ALERT_STATUS_DEF (0x00000000)
  #define PCU_CR_IA_PERF_LIMIT_REASONS_PCU_PKG_VR_THERM_ALERT_STATUS_HSH (0x010858FC)

  #define PCU_CR_IA_PERF_LIMIT_REASONS_PCU_FUSE_MAX_TURBO_LIMIT_STATUS_OFF ( 9)
  #define PCU_CR_IA_PERF_LIMIT_REASONS_PCU_FUSE_MAX_TURBO_LIMIT_STATUS_WID ( 1)
  #define PCU_CR_IA_PERF_LIMIT_REASONS_PCU_FUSE_MAX_TURBO_LIMIT_STATUS_MSK (0x00000200)
  #define PCU_CR_IA_PERF_LIMIT_REASONS_PCU_FUSE_MAX_TURBO_LIMIT_STATUS_MIN (0)
  #define PCU_CR_IA_PERF_LIMIT_REASONS_PCU_FUSE_MAX_TURBO_LIMIT_STATUS_MAX (1) // 0x00000001
  #define PCU_CR_IA_PERF_LIMIT_REASONS_PCU_FUSE_MAX_TURBO_LIMIT_STATUS_DEF (0x00000000)
  #define PCU_CR_IA_PERF_LIMIT_REASONS_PCU_FUSE_MAX_TURBO_LIMIT_STATUS_HSH (0x010958FC)

  #define PCU_CR_IA_PERF_LIMIT_REASONS_PCU_EPD_ICCMAX_STATUS_OFF       (10)
  #define PCU_CR_IA_PERF_LIMIT_REASONS_PCU_EPD_ICCMAX_STATUS_WID       ( 1)
  #define PCU_CR_IA_PERF_LIMIT_REASONS_PCU_EPD_ICCMAX_STATUS_MSK       (0x00000400)
  #define PCU_CR_IA_PERF_LIMIT_REASONS_PCU_EPD_ICCMAX_STATUS_MIN       (0)
  #define PCU_CR_IA_PERF_LIMIT_REASONS_PCU_EPD_ICCMAX_STATUS_MAX       (1) // 0x00000001
  #define PCU_CR_IA_PERF_LIMIT_REASONS_PCU_EPD_ICCMAX_STATUS_DEF       (0x00000000)
  #define PCU_CR_IA_PERF_LIMIT_REASONS_PCU_EPD_ICCMAX_STATUS_HSH       (0x010A58FC)

  #define PCU_CR_IA_PERF_LIMIT_REASONS_PCU_TURBO_TRANSITION_STATUS_STATUS_OFF (11)
  #define PCU_CR_IA_PERF_LIMIT_REASONS_PCU_TURBO_TRANSITION_STATUS_STATUS_WID ( 1)
  #define PCU_CR_IA_PERF_LIMIT_REASONS_PCU_TURBO_TRANSITION_STATUS_STATUS_MSK (0x00000800)
  #define PCU_CR_IA_PERF_LIMIT_REASONS_PCU_TURBO_TRANSITION_STATUS_STATUS_MIN (0)
  #define PCU_CR_IA_PERF_LIMIT_REASONS_PCU_TURBO_TRANSITION_STATUS_STATUS_MAX (1) // 0x00000001
  #define PCU_CR_IA_PERF_LIMIT_REASONS_PCU_TURBO_TRANSITION_STATUS_STATUS_DEF (0x00000000)
  #define PCU_CR_IA_PERF_LIMIT_REASONS_PCU_TURBO_TRANSITION_STATUS_STATUS_HSH (0x010B58FC)

  #define PCU_CR_IA_PERF_LIMIT_REASONS_PCU_SA_VR_THERM_ALERT_STATUS_OFF (12)
  #define PCU_CR_IA_PERF_LIMIT_REASONS_PCU_SA_VR_THERM_ALERT_STATUS_WID ( 1)
  #define PCU_CR_IA_PERF_LIMIT_REASONS_PCU_SA_VR_THERM_ALERT_STATUS_MSK (0x00001000)
  #define PCU_CR_IA_PERF_LIMIT_REASONS_PCU_SA_VR_THERM_ALERT_STATUS_MIN (0)
  #define PCU_CR_IA_PERF_LIMIT_REASONS_PCU_SA_VR_THERM_ALERT_STATUS_MAX (1) // 0x00000001
  #define PCU_CR_IA_PERF_LIMIT_REASONS_PCU_SA_VR_THERM_ALERT_STATUS_DEF (0x00000000)
  #define PCU_CR_IA_PERF_LIMIT_REASONS_PCU_SA_VR_THERM_ALERT_STATUS_HSH (0x010C58FC)

  #define PCU_CR_IA_PERF_LIMIT_REASONS_PCU_SPARE_IA_13_OFF             (13)
  #define PCU_CR_IA_PERF_LIMIT_REASONS_PCU_SPARE_IA_13_WID             ( 1)
  #define PCU_CR_IA_PERF_LIMIT_REASONS_PCU_SPARE_IA_13_MSK             (0x00002000)
  #define PCU_CR_IA_PERF_LIMIT_REASONS_PCU_SPARE_IA_13_MIN             (0)
  #define PCU_CR_IA_PERF_LIMIT_REASONS_PCU_SPARE_IA_13_MAX             (1) // 0x00000001
  #define PCU_CR_IA_PERF_LIMIT_REASONS_PCU_SPARE_IA_13_DEF             (0x00000000)
  #define PCU_CR_IA_PERF_LIMIT_REASONS_PCU_SPARE_IA_13_HSH             (0x010D58FC)

  #define PCU_CR_IA_PERF_LIMIT_REASONS_PCU_SPARE_IA_14_OFF             (14)
  #define PCU_CR_IA_PERF_LIMIT_REASONS_PCU_SPARE_IA_14_WID             ( 1)
  #define PCU_CR_IA_PERF_LIMIT_REASONS_PCU_SPARE_IA_14_MSK             (0x00004000)
  #define PCU_CR_IA_PERF_LIMIT_REASONS_PCU_SPARE_IA_14_MIN             (0)
  #define PCU_CR_IA_PERF_LIMIT_REASONS_PCU_SPARE_IA_14_MAX             (1) // 0x00000001
  #define PCU_CR_IA_PERF_LIMIT_REASONS_PCU_SPARE_IA_14_DEF             (0x00000000)
  #define PCU_CR_IA_PERF_LIMIT_REASONS_PCU_SPARE_IA_14_HSH             (0x010E58FC)

  #define PCU_CR_IA_PERF_LIMIT_REASONS_PCU_SPARE_IA_15_OFF             (15)
  #define PCU_CR_IA_PERF_LIMIT_REASONS_PCU_SPARE_IA_15_WID             ( 1)
  #define PCU_CR_IA_PERF_LIMIT_REASONS_PCU_SPARE_IA_15_MSK             (0x00008000)
  #define PCU_CR_IA_PERF_LIMIT_REASONS_PCU_SPARE_IA_15_MIN             (0)
  #define PCU_CR_IA_PERF_LIMIT_REASONS_PCU_SPARE_IA_15_MAX             (1) // 0x00000001
  #define PCU_CR_IA_PERF_LIMIT_REASONS_PCU_SPARE_IA_15_DEF             (0x00000000)
  #define PCU_CR_IA_PERF_LIMIT_REASONS_PCU_SPARE_IA_15_HSH             (0x010F58FC)

  #define PCU_CR_IA_PERF_LIMIT_REASONS_PCU_PROCHOT_LOG_OFF             (16)
  #define PCU_CR_IA_PERF_LIMIT_REASONS_PCU_PROCHOT_LOG_WID             ( 1)
  #define PCU_CR_IA_PERF_LIMIT_REASONS_PCU_PROCHOT_LOG_MSK             (0x00010000)
  #define PCU_CR_IA_PERF_LIMIT_REASONS_PCU_PROCHOT_LOG_MIN             (0)
  #define PCU_CR_IA_PERF_LIMIT_REASONS_PCU_PROCHOT_LOG_MAX             (1) // 0x00000001
  #define PCU_CR_IA_PERF_LIMIT_REASONS_PCU_PROCHOT_LOG_DEF             (0x00000000)
  #define PCU_CR_IA_PERF_LIMIT_REASONS_PCU_PROCHOT_LOG_HSH             (0x011058FC)

  #define PCU_CR_IA_PERF_LIMIT_REASONS_PCU_THERMAL_LOG_OFF             (17)
  #define PCU_CR_IA_PERF_LIMIT_REASONS_PCU_THERMAL_LOG_WID             ( 1)
  #define PCU_CR_IA_PERF_LIMIT_REASONS_PCU_THERMAL_LOG_MSK             (0x00020000)
  #define PCU_CR_IA_PERF_LIMIT_REASONS_PCU_THERMAL_LOG_MIN             (0)
  #define PCU_CR_IA_PERF_LIMIT_REASONS_PCU_THERMAL_LOG_MAX             (1) // 0x00000001
  #define PCU_CR_IA_PERF_LIMIT_REASONS_PCU_THERMAL_LOG_DEF             (0x00000000)
  #define PCU_CR_IA_PERF_LIMIT_REASONS_PCU_THERMAL_LOG_HSH             (0x011158FC)

  #define PCU_CR_IA_PERF_LIMIT_REASONS_PCU_SPARE_IA_LOG_2_OFF          (18)
  #define PCU_CR_IA_PERF_LIMIT_REASONS_PCU_SPARE_IA_LOG_2_WID          ( 1)
  #define PCU_CR_IA_PERF_LIMIT_REASONS_PCU_SPARE_IA_LOG_2_MSK          (0x00040000)
  #define PCU_CR_IA_PERF_LIMIT_REASONS_PCU_SPARE_IA_LOG_2_MIN          (0)
  #define PCU_CR_IA_PERF_LIMIT_REASONS_PCU_SPARE_IA_LOG_2_MAX          (1) // 0x00000001
  #define PCU_CR_IA_PERF_LIMIT_REASONS_PCU_SPARE_IA_LOG_2_DEF          (0x00000000)
  #define PCU_CR_IA_PERF_LIMIT_REASONS_PCU_SPARE_IA_LOG_2_HSH          (0x011258FC)

  #define PCU_CR_IA_PERF_LIMIT_REASONS_PCU_RAPL_PL1_LOG_OFF            (19)
  #define PCU_CR_IA_PERF_LIMIT_REASONS_PCU_RAPL_PL1_LOG_WID            ( 1)
  #define PCU_CR_IA_PERF_LIMIT_REASONS_PCU_RAPL_PL1_LOG_MSK            (0x00080000)
  #define PCU_CR_IA_PERF_LIMIT_REASONS_PCU_RAPL_PL1_LOG_MIN            (0)
  #define PCU_CR_IA_PERF_LIMIT_REASONS_PCU_RAPL_PL1_LOG_MAX            (1) // 0x00000001
  #define PCU_CR_IA_PERF_LIMIT_REASONS_PCU_RAPL_PL1_LOG_DEF            (0x00000000)
  #define PCU_CR_IA_PERF_LIMIT_REASONS_PCU_RAPL_PL1_LOG_HSH            (0x011358FC)

  #define PCU_CR_IA_PERF_LIMIT_REASONS_PCU_RAPL_PL2_LOG_OFF            (20)
  #define PCU_CR_IA_PERF_LIMIT_REASONS_PCU_RAPL_PL2_LOG_WID            ( 1)
  #define PCU_CR_IA_PERF_LIMIT_REASONS_PCU_RAPL_PL2_LOG_MSK            (0x00100000)
  #define PCU_CR_IA_PERF_LIMIT_REASONS_PCU_RAPL_PL2_LOG_MIN            (0)
  #define PCU_CR_IA_PERF_LIMIT_REASONS_PCU_RAPL_PL2_LOG_MAX            (1) // 0x00000001
  #define PCU_CR_IA_PERF_LIMIT_REASONS_PCU_RAPL_PL2_LOG_DEF            (0x00000000)
  #define PCU_CR_IA_PERF_LIMIT_REASONS_PCU_RAPL_PL2_LOG_HSH            (0x011458FC)

  #define PCU_CR_IA_PERF_LIMIT_REASONS_PCU_RAPL_PL3_LOG_OFF            (21)
  #define PCU_CR_IA_PERF_LIMIT_REASONS_PCU_RAPL_PL3_LOG_WID            ( 1)
  #define PCU_CR_IA_PERF_LIMIT_REASONS_PCU_RAPL_PL3_LOG_MSK            (0x00200000)
  #define PCU_CR_IA_PERF_LIMIT_REASONS_PCU_RAPL_PL3_LOG_MIN            (0)
  #define PCU_CR_IA_PERF_LIMIT_REASONS_PCU_RAPL_PL3_LOG_MAX            (1) // 0x00000001
  #define PCU_CR_IA_PERF_LIMIT_REASONS_PCU_RAPL_PL3_LOG_DEF            (0x00000000)
  #define PCU_CR_IA_PERF_LIMIT_REASONS_PCU_RAPL_PL3_LOG_HSH            (0x011558FC)

  #define PCU_CR_IA_PERF_LIMIT_REASONS_PCU_EE_LOG_OFF                  (22)
  #define PCU_CR_IA_PERF_LIMIT_REASONS_PCU_EE_LOG_WID                  ( 1)
  #define PCU_CR_IA_PERF_LIMIT_REASONS_PCU_EE_LOG_MSK                  (0x00400000)
  #define PCU_CR_IA_PERF_LIMIT_REASONS_PCU_EE_LOG_MIN                  (0)
  #define PCU_CR_IA_PERF_LIMIT_REASONS_PCU_EE_LOG_MAX                  (1) // 0x00000001
  #define PCU_CR_IA_PERF_LIMIT_REASONS_PCU_EE_LOG_DEF                  (0x00000000)
  #define PCU_CR_IA_PERF_LIMIT_REASONS_PCU_EE_LOG_HSH                  (0x011658FC)

  #define PCU_CR_IA_PERF_LIMIT_REASONS_PCU_GT_DRIVER_LOG_OFF           (23)
  #define PCU_CR_IA_PERF_LIMIT_REASONS_PCU_GT_DRIVER_LOG_WID           ( 1)
  #define PCU_CR_IA_PERF_LIMIT_REASONS_PCU_GT_DRIVER_LOG_MSK           (0x00800000)
  #define PCU_CR_IA_PERF_LIMIT_REASONS_PCU_GT_DRIVER_LOG_MIN           (0)
  #define PCU_CR_IA_PERF_LIMIT_REASONS_PCU_GT_DRIVER_LOG_MAX           (1) // 0x00000001
  #define PCU_CR_IA_PERF_LIMIT_REASONS_PCU_GT_DRIVER_LOG_DEF           (0x00000000)
  #define PCU_CR_IA_PERF_LIMIT_REASONS_PCU_GT_DRIVER_LOG_HSH           (0x011758FC)

  #define PCU_CR_IA_PERF_LIMIT_REASONS_PCU_PKG_VR_THERM_ALERT_LOG_OFF  (24)
  #define PCU_CR_IA_PERF_LIMIT_REASONS_PCU_PKG_VR_THERM_ALERT_LOG_WID  ( 1)
  #define PCU_CR_IA_PERF_LIMIT_REASONS_PCU_PKG_VR_THERM_ALERT_LOG_MSK  (0x01000000)
  #define PCU_CR_IA_PERF_LIMIT_REASONS_PCU_PKG_VR_THERM_ALERT_LOG_MIN  (0)
  #define PCU_CR_IA_PERF_LIMIT_REASONS_PCU_PKG_VR_THERM_ALERT_LOG_MAX  (1) // 0x00000001
  #define PCU_CR_IA_PERF_LIMIT_REASONS_PCU_PKG_VR_THERM_ALERT_LOG_DEF  (0x00000000)
  #define PCU_CR_IA_PERF_LIMIT_REASONS_PCU_PKG_VR_THERM_ALERT_LOG_HSH  (0x011858FC)

  #define PCU_CR_IA_PERF_LIMIT_REASONS_PCU_FUSE_MAX_TURBO_LIMIT_LOG_OFF (25)
  #define PCU_CR_IA_PERF_LIMIT_REASONS_PCU_FUSE_MAX_TURBO_LIMIT_LOG_WID ( 1)
  #define PCU_CR_IA_PERF_LIMIT_REASONS_PCU_FUSE_MAX_TURBO_LIMIT_LOG_MSK (0x02000000)
  #define PCU_CR_IA_PERF_LIMIT_REASONS_PCU_FUSE_MAX_TURBO_LIMIT_LOG_MIN (0)
  #define PCU_CR_IA_PERF_LIMIT_REASONS_PCU_FUSE_MAX_TURBO_LIMIT_LOG_MAX (1) // 0x00000001
  #define PCU_CR_IA_PERF_LIMIT_REASONS_PCU_FUSE_MAX_TURBO_LIMIT_LOG_DEF (0x00000000)
  #define PCU_CR_IA_PERF_LIMIT_REASONS_PCU_FUSE_MAX_TURBO_LIMIT_LOG_HSH (0x011958FC)

  #define PCU_CR_IA_PERF_LIMIT_REASONS_PCU_EDP_ICCMAX_LOG_OFF          (26)
  #define PCU_CR_IA_PERF_LIMIT_REASONS_PCU_EDP_ICCMAX_LOG_WID          ( 1)
  #define PCU_CR_IA_PERF_LIMIT_REASONS_PCU_EDP_ICCMAX_LOG_MSK          (0x04000000)
  #define PCU_CR_IA_PERF_LIMIT_REASONS_PCU_EDP_ICCMAX_LOG_MIN          (0)
  #define PCU_CR_IA_PERF_LIMIT_REASONS_PCU_EDP_ICCMAX_LOG_MAX          (1) // 0x00000001
  #define PCU_CR_IA_PERF_LIMIT_REASONS_PCU_EDP_ICCMAX_LOG_DEF          (0x00000000)
  #define PCU_CR_IA_PERF_LIMIT_REASONS_PCU_EDP_ICCMAX_LOG_HSH          (0x011A58FC)

  #define PCU_CR_IA_PERF_LIMIT_REASONS_PCU_TURBO_TRANSITION_LOG_OFF    (27)
  #define PCU_CR_IA_PERF_LIMIT_REASONS_PCU_TURBO_TRANSITION_LOG_WID    ( 1)
  #define PCU_CR_IA_PERF_LIMIT_REASONS_PCU_TURBO_TRANSITION_LOG_MSK    (0x08000000)
  #define PCU_CR_IA_PERF_LIMIT_REASONS_PCU_TURBO_TRANSITION_LOG_MIN    (0)
  #define PCU_CR_IA_PERF_LIMIT_REASONS_PCU_TURBO_TRANSITION_LOG_MAX    (1) // 0x00000001
  #define PCU_CR_IA_PERF_LIMIT_REASONS_PCU_TURBO_TRANSITION_LOG_DEF    (0x00000000)
  #define PCU_CR_IA_PERF_LIMIT_REASONS_PCU_TURBO_TRANSITION_LOG_HSH    (0x011B58FC)

  #define PCU_CR_IA_PERF_LIMIT_REASONS_PCU_SA_VR_THERM_ALERT_LOG_OFF   (28)
  #define PCU_CR_IA_PERF_LIMIT_REASONS_PCU_SA_VR_THERM_ALERT_LOG_WID   ( 1)
  #define PCU_CR_IA_PERF_LIMIT_REASONS_PCU_SA_VR_THERM_ALERT_LOG_MSK   (0x10000000)
  #define PCU_CR_IA_PERF_LIMIT_REASONS_PCU_SA_VR_THERM_ALERT_LOG_MIN   (0)
  #define PCU_CR_IA_PERF_LIMIT_REASONS_PCU_SA_VR_THERM_ALERT_LOG_MAX   (1) // 0x00000001
  #define PCU_CR_IA_PERF_LIMIT_REASONS_PCU_SA_VR_THERM_ALERT_LOG_DEF   (0x00000000)
  #define PCU_CR_IA_PERF_LIMIT_REASONS_PCU_SA_VR_THERM_ALERT_LOG_HSH   (0x011C58FC)

  #define PCU_CR_IA_PERF_LIMIT_REASONS_PCU_SPARE_IA_LOG_13_OFF         (29)
  #define PCU_CR_IA_PERF_LIMIT_REASONS_PCU_SPARE_IA_LOG_13_WID         ( 1)
  #define PCU_CR_IA_PERF_LIMIT_REASONS_PCU_SPARE_IA_LOG_13_MSK         (0x20000000)
  #define PCU_CR_IA_PERF_LIMIT_REASONS_PCU_SPARE_IA_LOG_13_MIN         (0)
  #define PCU_CR_IA_PERF_LIMIT_REASONS_PCU_SPARE_IA_LOG_13_MAX         (1) // 0x00000001
  #define PCU_CR_IA_PERF_LIMIT_REASONS_PCU_SPARE_IA_LOG_13_DEF         (0x00000000)
  #define PCU_CR_IA_PERF_LIMIT_REASONS_PCU_SPARE_IA_LOG_13_HSH         (0x011D58FC)

  #define PCU_CR_IA_PERF_LIMIT_REASONS_PCU_SPARE_IA_LOG_14_OFF         (30)
  #define PCU_CR_IA_PERF_LIMIT_REASONS_PCU_SPARE_IA_LOG_14_WID         ( 1)
  #define PCU_CR_IA_PERF_LIMIT_REASONS_PCU_SPARE_IA_LOG_14_MSK         (0x40000000)
  #define PCU_CR_IA_PERF_LIMIT_REASONS_PCU_SPARE_IA_LOG_14_MIN         (0)
  #define PCU_CR_IA_PERF_LIMIT_REASONS_PCU_SPARE_IA_LOG_14_MAX         (1) // 0x00000001
  #define PCU_CR_IA_PERF_LIMIT_REASONS_PCU_SPARE_IA_LOG_14_DEF         (0x00000000)
  #define PCU_CR_IA_PERF_LIMIT_REASONS_PCU_SPARE_IA_LOG_14_HSH         (0x011E58FC)

  #define PCU_CR_IA_PERF_LIMIT_REASONS_PCU_SPARE_IA_LOG_15_OFF         (31)
  #define PCU_CR_IA_PERF_LIMIT_REASONS_PCU_SPARE_IA_LOG_15_WID         ( 1)
  #define PCU_CR_IA_PERF_LIMIT_REASONS_PCU_SPARE_IA_LOG_15_MSK         (0x80000000)
  #define PCU_CR_IA_PERF_LIMIT_REASONS_PCU_SPARE_IA_LOG_15_MIN         (0)
  #define PCU_CR_IA_PERF_LIMIT_REASONS_PCU_SPARE_IA_LOG_15_MAX         (1) // 0x00000001
  #define PCU_CR_IA_PERF_LIMIT_REASONS_PCU_SPARE_IA_LOG_15_DEF         (0x00000000)
  #define PCU_CR_IA_PERF_LIMIT_REASONS_PCU_SPARE_IA_LOG_15_HSH         (0x011F58FC)

#define PCU_CR_GT_PERF_LIMIT_REASONS_PCU_REG                           (0x00005900)

  #define PCU_CR_GT_PERF_LIMIT_REASONS_PCU_PROCHOT_STATUS_OFF          ( 0)
  #define PCU_CR_GT_PERF_LIMIT_REASONS_PCU_PROCHOT_STATUS_WID          ( 1)
  #define PCU_CR_GT_PERF_LIMIT_REASONS_PCU_PROCHOT_STATUS_MSK          (0x00000001)
  #define PCU_CR_GT_PERF_LIMIT_REASONS_PCU_PROCHOT_STATUS_MIN          (0)
  #define PCU_CR_GT_PERF_LIMIT_REASONS_PCU_PROCHOT_STATUS_MAX          (1) // 0x00000001
  #define PCU_CR_GT_PERF_LIMIT_REASONS_PCU_PROCHOT_STATUS_DEF          (0x00000000)
  #define PCU_CR_GT_PERF_LIMIT_REASONS_PCU_PROCHOT_STATUS_HSH          (0x01005900)

  #define PCU_CR_GT_PERF_LIMIT_REASONS_PCU_THERMAL_STATUS_OFF          ( 1)
  #define PCU_CR_GT_PERF_LIMIT_REASONS_PCU_THERMAL_STATUS_WID          ( 1)
  #define PCU_CR_GT_PERF_LIMIT_REASONS_PCU_THERMAL_STATUS_MSK          (0x00000002)
  #define PCU_CR_GT_PERF_LIMIT_REASONS_PCU_THERMAL_STATUS_MIN          (0)
  #define PCU_CR_GT_PERF_LIMIT_REASONS_PCU_THERMAL_STATUS_MAX          (1) // 0x00000001
  #define PCU_CR_GT_PERF_LIMIT_REASONS_PCU_THERMAL_STATUS_DEF          (0x00000000)
  #define PCU_CR_GT_PERF_LIMIT_REASONS_PCU_THERMAL_STATUS_HSH          (0x01015900)

  #define PCU_CR_GT_PERF_LIMIT_REASONS_PCU_SPARE_GT_2_OFF              ( 2)
  #define PCU_CR_GT_PERF_LIMIT_REASONS_PCU_SPARE_GT_2_WID              ( 1)
  #define PCU_CR_GT_PERF_LIMIT_REASONS_PCU_SPARE_GT_2_MSK              (0x00000004)
  #define PCU_CR_GT_PERF_LIMIT_REASONS_PCU_SPARE_GT_2_MIN              (0)
  #define PCU_CR_GT_PERF_LIMIT_REASONS_PCU_SPARE_GT_2_MAX              (1) // 0x00000001
  #define PCU_CR_GT_PERF_LIMIT_REASONS_PCU_SPARE_GT_2_DEF              (0x00000000)
  #define PCU_CR_GT_PERF_LIMIT_REASONS_PCU_SPARE_GT_2_HSH              (0x01025900)

  #define PCU_CR_GT_PERF_LIMIT_REASONS_PCU_RAPL_PL1_STATUS_OFF         ( 3)
  #define PCU_CR_GT_PERF_LIMIT_REASONS_PCU_RAPL_PL1_STATUS_WID         ( 1)
  #define PCU_CR_GT_PERF_LIMIT_REASONS_PCU_RAPL_PL1_STATUS_MSK         (0x00000008)
  #define PCU_CR_GT_PERF_LIMIT_REASONS_PCU_RAPL_PL1_STATUS_MIN         (0)
  #define PCU_CR_GT_PERF_LIMIT_REASONS_PCU_RAPL_PL1_STATUS_MAX         (1) // 0x00000001
  #define PCU_CR_GT_PERF_LIMIT_REASONS_PCU_RAPL_PL1_STATUS_DEF         (0x00000000)
  #define PCU_CR_GT_PERF_LIMIT_REASONS_PCU_RAPL_PL1_STATUS_HSH         (0x01035900)

  #define PCU_CR_GT_PERF_LIMIT_REASONS_PCU_RAPL_PL2_STATUS_OFF         ( 4)
  #define PCU_CR_GT_PERF_LIMIT_REASONS_PCU_RAPL_PL2_STATUS_WID         ( 1)
  #define PCU_CR_GT_PERF_LIMIT_REASONS_PCU_RAPL_PL2_STATUS_MSK         (0x00000010)
  #define PCU_CR_GT_PERF_LIMIT_REASONS_PCU_RAPL_PL2_STATUS_MIN         (0)
  #define PCU_CR_GT_PERF_LIMIT_REASONS_PCU_RAPL_PL2_STATUS_MAX         (1) // 0x00000001
  #define PCU_CR_GT_PERF_LIMIT_REASONS_PCU_RAPL_PL2_STATUS_DEF         (0x00000000)
  #define PCU_CR_GT_PERF_LIMIT_REASONS_PCU_RAPL_PL2_STATUS_HSH         (0x01045900)

  #define PCU_CR_GT_PERF_LIMIT_REASONS_PCU_RAPL_PL3_STATUS_OFF         ( 5)
  #define PCU_CR_GT_PERF_LIMIT_REASONS_PCU_RAPL_PL3_STATUS_WID         ( 1)
  #define PCU_CR_GT_PERF_LIMIT_REASONS_PCU_RAPL_PL3_STATUS_MSK         (0x00000020)
  #define PCU_CR_GT_PERF_LIMIT_REASONS_PCU_RAPL_PL3_STATUS_MIN         (0)
  #define PCU_CR_GT_PERF_LIMIT_REASONS_PCU_RAPL_PL3_STATUS_MAX         (1) // 0x00000001
  #define PCU_CR_GT_PERF_LIMIT_REASONS_PCU_RAPL_PL3_STATUS_DEF         (0x00000000)
  #define PCU_CR_GT_PERF_LIMIT_REASONS_PCU_RAPL_PL3_STATUS_HSH         (0x01055900)

  #define PCU_CR_GT_PERF_LIMIT_REASONS_PCU_SPARE_GT_6_OFF              ( 6)
  #define PCU_CR_GT_PERF_LIMIT_REASONS_PCU_SPARE_GT_6_WID              ( 1)
  #define PCU_CR_GT_PERF_LIMIT_REASONS_PCU_SPARE_GT_6_MSK              (0x00000040)
  #define PCU_CR_GT_PERF_LIMIT_REASONS_PCU_SPARE_GT_6_MIN              (0)
  #define PCU_CR_GT_PERF_LIMIT_REASONS_PCU_SPARE_GT_6_MAX              (1) // 0x00000001
  #define PCU_CR_GT_PERF_LIMIT_REASONS_PCU_SPARE_GT_6_DEF              (0x00000000)
  #define PCU_CR_GT_PERF_LIMIT_REASONS_PCU_SPARE_GT_6_HSH              (0x01065900)

  #define PCU_CR_GT_PERF_LIMIT_REASONS_PCU_SPARE_GT_7_OFF              ( 7)
  #define PCU_CR_GT_PERF_LIMIT_REASONS_PCU_SPARE_GT_7_WID              ( 1)
  #define PCU_CR_GT_PERF_LIMIT_REASONS_PCU_SPARE_GT_7_MSK              (0x00000080)
  #define PCU_CR_GT_PERF_LIMIT_REASONS_PCU_SPARE_GT_7_MIN              (0)
  #define PCU_CR_GT_PERF_LIMIT_REASONS_PCU_SPARE_GT_7_MAX              (1) // 0x00000001
  #define PCU_CR_GT_PERF_LIMIT_REASONS_PCU_SPARE_GT_7_DEF              (0x00000000)
  #define PCU_CR_GT_PERF_LIMIT_REASONS_PCU_SPARE_GT_7_HSH              (0x01075900)

  #define PCU_CR_GT_PERF_LIMIT_REASONS_PCU_PKG_VR_THERM_ALERT_OFF      ( 8)
  #define PCU_CR_GT_PERF_LIMIT_REASONS_PCU_PKG_VR_THERM_ALERT_WID      ( 1)
  #define PCU_CR_GT_PERF_LIMIT_REASONS_PCU_PKG_VR_THERM_ALERT_MSK      (0x00000100)
  #define PCU_CR_GT_PERF_LIMIT_REASONS_PCU_PKG_VR_THERM_ALERT_MIN      (0)
  #define PCU_CR_GT_PERF_LIMIT_REASONS_PCU_PKG_VR_THERM_ALERT_MAX      (1) // 0x00000001
  #define PCU_CR_GT_PERF_LIMIT_REASONS_PCU_PKG_VR_THERM_ALERT_DEF      (0x00000000)
  #define PCU_CR_GT_PERF_LIMIT_REASONS_PCU_PKG_VR_THERM_ALERT_HSH      (0x01085900)

  #define PCU_CR_GT_PERF_LIMIT_REASONS_PCU_SA_VR_THERM_ALERT_STATUS_OFF ( 9)
  #define PCU_CR_GT_PERF_LIMIT_REASONS_PCU_SA_VR_THERM_ALERT_STATUS_WID ( 1)
  #define PCU_CR_GT_PERF_LIMIT_REASONS_PCU_SA_VR_THERM_ALERT_STATUS_MSK (0x00000200)
  #define PCU_CR_GT_PERF_LIMIT_REASONS_PCU_SA_VR_THERM_ALERT_STATUS_MIN (0)
  #define PCU_CR_GT_PERF_LIMIT_REASONS_PCU_SA_VR_THERM_ALERT_STATUS_MAX (1) // 0x00000001
  #define PCU_CR_GT_PERF_LIMIT_REASONS_PCU_SA_VR_THERM_ALERT_STATUS_DEF (0x00000000)
  #define PCU_CR_GT_PERF_LIMIT_REASONS_PCU_SA_VR_THERM_ALERT_STATUS_HSH (0x01095900)

  #define PCU_CR_GT_PERF_LIMIT_REASONS_PCU_EDP_ICC_STATUS_OFF          (10)
  #define PCU_CR_GT_PERF_LIMIT_REASONS_PCU_EDP_ICC_STATUS_WID          ( 1)
  #define PCU_CR_GT_PERF_LIMIT_REASONS_PCU_EDP_ICC_STATUS_MSK          (0x00000400)
  #define PCU_CR_GT_PERF_LIMIT_REASONS_PCU_EDP_ICC_STATUS_MIN          (0)
  #define PCU_CR_GT_PERF_LIMIT_REASONS_PCU_EDP_ICC_STATUS_MAX          (1) // 0x00000001
  #define PCU_CR_GT_PERF_LIMIT_REASONS_PCU_EDP_ICC_STATUS_DEF          (0x00000000)
  #define PCU_CR_GT_PERF_LIMIT_REASONS_PCU_EDP_ICC_STATUS_HSH          (0x010A5900)

  #define PCU_CR_GT_PERF_LIMIT_REASONS_PCU_SPARE_GT_11_OFF             (11)
  #define PCU_CR_GT_PERF_LIMIT_REASONS_PCU_SPARE_GT_11_WID             ( 1)
  #define PCU_CR_GT_PERF_LIMIT_REASONS_PCU_SPARE_GT_11_MSK             (0x00000800)
  #define PCU_CR_GT_PERF_LIMIT_REASONS_PCU_SPARE_GT_11_MIN             (0)
  #define PCU_CR_GT_PERF_LIMIT_REASONS_PCU_SPARE_GT_11_MAX             (1) // 0x00000001
  #define PCU_CR_GT_PERF_LIMIT_REASONS_PCU_SPARE_GT_11_DEF             (0x00000000)
  #define PCU_CR_GT_PERF_LIMIT_REASONS_PCU_SPARE_GT_11_HSH             (0x010B5900)

  #define PCU_CR_GT_PERF_LIMIT_REASONS_PCU_SPARE_GT_12_OFF             (12)
  #define PCU_CR_GT_PERF_LIMIT_REASONS_PCU_SPARE_GT_12_WID             ( 1)
  #define PCU_CR_GT_PERF_LIMIT_REASONS_PCU_SPARE_GT_12_MSK             (0x00001000)
  #define PCU_CR_GT_PERF_LIMIT_REASONS_PCU_SPARE_GT_12_MIN             (0)
  #define PCU_CR_GT_PERF_LIMIT_REASONS_PCU_SPARE_GT_12_MAX             (1) // 0x00000001
  #define PCU_CR_GT_PERF_LIMIT_REASONS_PCU_SPARE_GT_12_DEF             (0x00000000)
  #define PCU_CR_GT_PERF_LIMIT_REASONS_PCU_SPARE_GT_12_HSH             (0x010C5900)

  #define PCU_CR_GT_PERF_LIMIT_REASONS_PCU_SPARE_GT_13_OFF             (13)
  #define PCU_CR_GT_PERF_LIMIT_REASONS_PCU_SPARE_GT_13_WID             ( 1)
  #define PCU_CR_GT_PERF_LIMIT_REASONS_PCU_SPARE_GT_13_MSK             (0x00002000)
  #define PCU_CR_GT_PERF_LIMIT_REASONS_PCU_SPARE_GT_13_MIN             (0)
  #define PCU_CR_GT_PERF_LIMIT_REASONS_PCU_SPARE_GT_13_MAX             (1) // 0x00000001
  #define PCU_CR_GT_PERF_LIMIT_REASONS_PCU_SPARE_GT_13_DEF             (0x00000000)
  #define PCU_CR_GT_PERF_LIMIT_REASONS_PCU_SPARE_GT_13_HSH             (0x010D5900)

  #define PCU_CR_GT_PERF_LIMIT_REASONS_PCU_SPARE_GT_14_OFF             (14)
  #define PCU_CR_GT_PERF_LIMIT_REASONS_PCU_SPARE_GT_14_WID             ( 1)
  #define PCU_CR_GT_PERF_LIMIT_REASONS_PCU_SPARE_GT_14_MSK             (0x00004000)
  #define PCU_CR_GT_PERF_LIMIT_REASONS_PCU_SPARE_GT_14_MIN             (0)
  #define PCU_CR_GT_PERF_LIMIT_REASONS_PCU_SPARE_GT_14_MAX             (1) // 0x00000001
  #define PCU_CR_GT_PERF_LIMIT_REASONS_PCU_SPARE_GT_14_DEF             (0x00000000)
  #define PCU_CR_GT_PERF_LIMIT_REASONS_PCU_SPARE_GT_14_HSH             (0x010E5900)

  #define PCU_CR_GT_PERF_LIMIT_REASONS_PCU_SPARE_GT_15_OFF             (15)
  #define PCU_CR_GT_PERF_LIMIT_REASONS_PCU_SPARE_GT_15_WID             ( 1)
  #define PCU_CR_GT_PERF_LIMIT_REASONS_PCU_SPARE_GT_15_MSK             (0x00008000)
  #define PCU_CR_GT_PERF_LIMIT_REASONS_PCU_SPARE_GT_15_MIN             (0)
  #define PCU_CR_GT_PERF_LIMIT_REASONS_PCU_SPARE_GT_15_MAX             (1) // 0x00000001
  #define PCU_CR_GT_PERF_LIMIT_REASONS_PCU_SPARE_GT_15_DEF             (0x00000000)
  #define PCU_CR_GT_PERF_LIMIT_REASONS_PCU_SPARE_GT_15_HSH             (0x010F5900)

  #define PCU_CR_GT_PERF_LIMIT_REASONS_PCU_PROCHOT_LOG_OFF             (16)
  #define PCU_CR_GT_PERF_LIMIT_REASONS_PCU_PROCHOT_LOG_WID             ( 1)
  #define PCU_CR_GT_PERF_LIMIT_REASONS_PCU_PROCHOT_LOG_MSK             (0x00010000)
  #define PCU_CR_GT_PERF_LIMIT_REASONS_PCU_PROCHOT_LOG_MIN             (0)
  #define PCU_CR_GT_PERF_LIMIT_REASONS_PCU_PROCHOT_LOG_MAX             (1) // 0x00000001
  #define PCU_CR_GT_PERF_LIMIT_REASONS_PCU_PROCHOT_LOG_DEF             (0x00000000)
  #define PCU_CR_GT_PERF_LIMIT_REASONS_PCU_PROCHOT_LOG_HSH             (0x01105900)

  #define PCU_CR_GT_PERF_LIMIT_REASONS_PCU_THERMAL_LOG_OFF             (17)
  #define PCU_CR_GT_PERF_LIMIT_REASONS_PCU_THERMAL_LOG_WID             ( 1)
  #define PCU_CR_GT_PERF_LIMIT_REASONS_PCU_THERMAL_LOG_MSK             (0x00020000)
  #define PCU_CR_GT_PERF_LIMIT_REASONS_PCU_THERMAL_LOG_MIN             (0)
  #define PCU_CR_GT_PERF_LIMIT_REASONS_PCU_THERMAL_LOG_MAX             (1) // 0x00000001
  #define PCU_CR_GT_PERF_LIMIT_REASONS_PCU_THERMAL_LOG_DEF             (0x00000000)
  #define PCU_CR_GT_PERF_LIMIT_REASONS_PCU_THERMAL_LOG_HSH             (0x01115900)

  #define PCU_CR_GT_PERF_LIMIT_REASONS_PCU_SPARE_GT_LOG_2_OFF          (18)
  #define PCU_CR_GT_PERF_LIMIT_REASONS_PCU_SPARE_GT_LOG_2_WID          ( 1)
  #define PCU_CR_GT_PERF_LIMIT_REASONS_PCU_SPARE_GT_LOG_2_MSK          (0x00040000)
  #define PCU_CR_GT_PERF_LIMIT_REASONS_PCU_SPARE_GT_LOG_2_MIN          (0)
  #define PCU_CR_GT_PERF_LIMIT_REASONS_PCU_SPARE_GT_LOG_2_MAX          (1) // 0x00000001
  #define PCU_CR_GT_PERF_LIMIT_REASONS_PCU_SPARE_GT_LOG_2_DEF          (0x00000000)
  #define PCU_CR_GT_PERF_LIMIT_REASONS_PCU_SPARE_GT_LOG_2_HSH          (0x01125900)

  #define PCU_CR_GT_PERF_LIMIT_REASONS_PCU_RAPL_PL1_LOG_OFF            (19)
  #define PCU_CR_GT_PERF_LIMIT_REASONS_PCU_RAPL_PL1_LOG_WID            ( 1)
  #define PCU_CR_GT_PERF_LIMIT_REASONS_PCU_RAPL_PL1_LOG_MSK            (0x00080000)
  #define PCU_CR_GT_PERF_LIMIT_REASONS_PCU_RAPL_PL1_LOG_MIN            (0)
  #define PCU_CR_GT_PERF_LIMIT_REASONS_PCU_RAPL_PL1_LOG_MAX            (1) // 0x00000001
  #define PCU_CR_GT_PERF_LIMIT_REASONS_PCU_RAPL_PL1_LOG_DEF            (0x00000000)
  #define PCU_CR_GT_PERF_LIMIT_REASONS_PCU_RAPL_PL1_LOG_HSH            (0x01135900)

  #define PCU_CR_GT_PERF_LIMIT_REASONS_PCU_RAPL_PL2_LOG_OFF            (20)
  #define PCU_CR_GT_PERF_LIMIT_REASONS_PCU_RAPL_PL2_LOG_WID            ( 1)
  #define PCU_CR_GT_PERF_LIMIT_REASONS_PCU_RAPL_PL2_LOG_MSK            (0x00100000)
  #define PCU_CR_GT_PERF_LIMIT_REASONS_PCU_RAPL_PL2_LOG_MIN            (0)
  #define PCU_CR_GT_PERF_LIMIT_REASONS_PCU_RAPL_PL2_LOG_MAX            (1) // 0x00000001
  #define PCU_CR_GT_PERF_LIMIT_REASONS_PCU_RAPL_PL2_LOG_DEF            (0x00000000)
  #define PCU_CR_GT_PERF_LIMIT_REASONS_PCU_RAPL_PL2_LOG_HSH            (0x01145900)

  #define PCU_CR_GT_PERF_LIMIT_REASONS_PCU_RAPL_PL3_LOG_OFF            (21)
  #define PCU_CR_GT_PERF_LIMIT_REASONS_PCU_RAPL_PL3_LOG_WID            ( 1)
  #define PCU_CR_GT_PERF_LIMIT_REASONS_PCU_RAPL_PL3_LOG_MSK            (0x00200000)
  #define PCU_CR_GT_PERF_LIMIT_REASONS_PCU_RAPL_PL3_LOG_MIN            (0)
  #define PCU_CR_GT_PERF_LIMIT_REASONS_PCU_RAPL_PL3_LOG_MAX            (1) // 0x00000001
  #define PCU_CR_GT_PERF_LIMIT_REASONS_PCU_RAPL_PL3_LOG_DEF            (0x00000000)
  #define PCU_CR_GT_PERF_LIMIT_REASONS_PCU_RAPL_PL3_LOG_HSH            (0x01155900)

  #define PCU_CR_GT_PERF_LIMIT_REASONS_PCU_SPARE_GT_LOG_6_OFF          (22)
  #define PCU_CR_GT_PERF_LIMIT_REASONS_PCU_SPARE_GT_LOG_6_WID          ( 1)
  #define PCU_CR_GT_PERF_LIMIT_REASONS_PCU_SPARE_GT_LOG_6_MSK          (0x00400000)
  #define PCU_CR_GT_PERF_LIMIT_REASONS_PCU_SPARE_GT_LOG_6_MIN          (0)
  #define PCU_CR_GT_PERF_LIMIT_REASONS_PCU_SPARE_GT_LOG_6_MAX          (1) // 0x00000001
  #define PCU_CR_GT_PERF_LIMIT_REASONS_PCU_SPARE_GT_LOG_6_DEF          (0x00000000)
  #define PCU_CR_GT_PERF_LIMIT_REASONS_PCU_SPARE_GT_LOG_6_HSH          (0x01165900)

  #define PCU_CR_GT_PERF_LIMIT_REASONS_PCU_SPARE_GT_LOG_7_OFF          (23)
  #define PCU_CR_GT_PERF_LIMIT_REASONS_PCU_SPARE_GT_LOG_7_WID          ( 1)
  #define PCU_CR_GT_PERF_LIMIT_REASONS_PCU_SPARE_GT_LOG_7_MSK          (0x00800000)
  #define PCU_CR_GT_PERF_LIMIT_REASONS_PCU_SPARE_GT_LOG_7_MIN          (0)
  #define PCU_CR_GT_PERF_LIMIT_REASONS_PCU_SPARE_GT_LOG_7_MAX          (1) // 0x00000001
  #define PCU_CR_GT_PERF_LIMIT_REASONS_PCU_SPARE_GT_LOG_7_DEF          (0x00000000)
  #define PCU_CR_GT_PERF_LIMIT_REASONS_PCU_SPARE_GT_LOG_7_HSH          (0x01175900)

  #define PCU_CR_GT_PERF_LIMIT_REASONS_PCU_PKG_VR_THEM_ALERT_LOG_OFF   (24)
  #define PCU_CR_GT_PERF_LIMIT_REASONS_PCU_PKG_VR_THEM_ALERT_LOG_WID   ( 1)
  #define PCU_CR_GT_PERF_LIMIT_REASONS_PCU_PKG_VR_THEM_ALERT_LOG_MSK   (0x01000000)
  #define PCU_CR_GT_PERF_LIMIT_REASONS_PCU_PKG_VR_THEM_ALERT_LOG_MIN   (0)
  #define PCU_CR_GT_PERF_LIMIT_REASONS_PCU_PKG_VR_THEM_ALERT_LOG_MAX   (1) // 0x00000001
  #define PCU_CR_GT_PERF_LIMIT_REASONS_PCU_PKG_VR_THEM_ALERT_LOG_DEF   (0x00000000)
  #define PCU_CR_GT_PERF_LIMIT_REASONS_PCU_PKG_VR_THEM_ALERT_LOG_HSH   (0x01185900)

  #define PCU_CR_GT_PERF_LIMIT_REASONS_PCU_SA_VR_THERM_ALERT_LOG_OFF   (25)
  #define PCU_CR_GT_PERF_LIMIT_REASONS_PCU_SA_VR_THERM_ALERT_LOG_WID   ( 1)
  #define PCU_CR_GT_PERF_LIMIT_REASONS_PCU_SA_VR_THERM_ALERT_LOG_MSK   (0x02000000)
  #define PCU_CR_GT_PERF_LIMIT_REASONS_PCU_SA_VR_THERM_ALERT_LOG_MIN   (0)
  #define PCU_CR_GT_PERF_LIMIT_REASONS_PCU_SA_VR_THERM_ALERT_LOG_MAX   (1) // 0x00000001
  #define PCU_CR_GT_PERF_LIMIT_REASONS_PCU_SA_VR_THERM_ALERT_LOG_DEF   (0x00000000)
  #define PCU_CR_GT_PERF_LIMIT_REASONS_PCU_SA_VR_THERM_ALERT_LOG_HSH   (0x01195900)

  #define PCU_CR_GT_PERF_LIMIT_REASONS_PCU_EDP_ICC_LOG_OFF             (26)
  #define PCU_CR_GT_PERF_LIMIT_REASONS_PCU_EDP_ICC_LOG_WID             ( 1)
  #define PCU_CR_GT_PERF_LIMIT_REASONS_PCU_EDP_ICC_LOG_MSK             (0x04000000)
  #define PCU_CR_GT_PERF_LIMIT_REASONS_PCU_EDP_ICC_LOG_MIN             (0)
  #define PCU_CR_GT_PERF_LIMIT_REASONS_PCU_EDP_ICC_LOG_MAX             (1) // 0x00000001
  #define PCU_CR_GT_PERF_LIMIT_REASONS_PCU_EDP_ICC_LOG_DEF             (0x00000000)
  #define PCU_CR_GT_PERF_LIMIT_REASONS_PCU_EDP_ICC_LOG_HSH             (0x011A5900)

  #define PCU_CR_GT_PERF_LIMIT_REASONS_PCU_SPARE_GT_LOG_11_OFF         (27)
  #define PCU_CR_GT_PERF_LIMIT_REASONS_PCU_SPARE_GT_LOG_11_WID         ( 1)
  #define PCU_CR_GT_PERF_LIMIT_REASONS_PCU_SPARE_GT_LOG_11_MSK         (0x08000000)
  #define PCU_CR_GT_PERF_LIMIT_REASONS_PCU_SPARE_GT_LOG_11_MIN         (0)
  #define PCU_CR_GT_PERF_LIMIT_REASONS_PCU_SPARE_GT_LOG_11_MAX         (1) // 0x00000001
  #define PCU_CR_GT_PERF_LIMIT_REASONS_PCU_SPARE_GT_LOG_11_DEF         (0x00000000)
  #define PCU_CR_GT_PERF_LIMIT_REASONS_PCU_SPARE_GT_LOG_11_HSH         (0x011B5900)

  #define PCU_CR_GT_PERF_LIMIT_REASONS_PCU_SPARE_GT_LOG_12_OFF         (28)
  #define PCU_CR_GT_PERF_LIMIT_REASONS_PCU_SPARE_GT_LOG_12_WID         ( 1)
  #define PCU_CR_GT_PERF_LIMIT_REASONS_PCU_SPARE_GT_LOG_12_MSK         (0x10000000)
  #define PCU_CR_GT_PERF_LIMIT_REASONS_PCU_SPARE_GT_LOG_12_MIN         (0)
  #define PCU_CR_GT_PERF_LIMIT_REASONS_PCU_SPARE_GT_LOG_12_MAX         (1) // 0x00000001
  #define PCU_CR_GT_PERF_LIMIT_REASONS_PCU_SPARE_GT_LOG_12_DEF         (0x00000000)
  #define PCU_CR_GT_PERF_LIMIT_REASONS_PCU_SPARE_GT_LOG_12_HSH         (0x011C5900)

  #define PCU_CR_GT_PERF_LIMIT_REASONS_PCU_SPARE_GT_LOG_13_OFF         (29)
  #define PCU_CR_GT_PERF_LIMIT_REASONS_PCU_SPARE_GT_LOG_13_WID         ( 1)
  #define PCU_CR_GT_PERF_LIMIT_REASONS_PCU_SPARE_GT_LOG_13_MSK         (0x20000000)
  #define PCU_CR_GT_PERF_LIMIT_REASONS_PCU_SPARE_GT_LOG_13_MIN         (0)
  #define PCU_CR_GT_PERF_LIMIT_REASONS_PCU_SPARE_GT_LOG_13_MAX         (1) // 0x00000001
  #define PCU_CR_GT_PERF_LIMIT_REASONS_PCU_SPARE_GT_LOG_13_DEF         (0x00000000)
  #define PCU_CR_GT_PERF_LIMIT_REASONS_PCU_SPARE_GT_LOG_13_HSH         (0x011D5900)

  #define PCU_CR_GT_PERF_LIMIT_REASONS_PCU_SPARE_GT_LOG_14_OFF         (30)
  #define PCU_CR_GT_PERF_LIMIT_REASONS_PCU_SPARE_GT_LOG_14_WID         ( 1)
  #define PCU_CR_GT_PERF_LIMIT_REASONS_PCU_SPARE_GT_LOG_14_MSK         (0x40000000)
  #define PCU_CR_GT_PERF_LIMIT_REASONS_PCU_SPARE_GT_LOG_14_MIN         (0)
  #define PCU_CR_GT_PERF_LIMIT_REASONS_PCU_SPARE_GT_LOG_14_MAX         (1) // 0x00000001
  #define PCU_CR_GT_PERF_LIMIT_REASONS_PCU_SPARE_GT_LOG_14_DEF         (0x00000000)
  #define PCU_CR_GT_PERF_LIMIT_REASONS_PCU_SPARE_GT_LOG_14_HSH         (0x011E5900)

  #define PCU_CR_GT_PERF_LIMIT_REASONS_PCU_SPARE_GT_LOG_15_OFF         (31)
  #define PCU_CR_GT_PERF_LIMIT_REASONS_PCU_SPARE_GT_LOG_15_WID         ( 1)
  #define PCU_CR_GT_PERF_LIMIT_REASONS_PCU_SPARE_GT_LOG_15_MSK         (0x80000000)
  #define PCU_CR_GT_PERF_LIMIT_REASONS_PCU_SPARE_GT_LOG_15_MIN         (0)
  #define PCU_CR_GT_PERF_LIMIT_REASONS_PCU_SPARE_GT_LOG_15_MAX         (1) // 0x00000001
  #define PCU_CR_GT_PERF_LIMIT_REASONS_PCU_SPARE_GT_LOG_15_DEF         (0x00000000)
  #define PCU_CR_GT_PERF_LIMIT_REASONS_PCU_SPARE_GT_LOG_15_HSH         (0x011F5900)

#define PCU_CR_CLR_PERF_LIMIT_REASONS_PCU_REG                          (0x00005904)

  #define PCU_CR_CLR_PERF_LIMIT_REASONS_PCU_SPARE_CLR_0_OFF            ( 0)
  #define PCU_CR_CLR_PERF_LIMIT_REASONS_PCU_SPARE_CLR_0_WID            ( 1)
  #define PCU_CR_CLR_PERF_LIMIT_REASONS_PCU_SPARE_CLR_0_MSK            (0x00000001)
  #define PCU_CR_CLR_PERF_LIMIT_REASONS_PCU_SPARE_CLR_0_MIN            (0)
  #define PCU_CR_CLR_PERF_LIMIT_REASONS_PCU_SPARE_CLR_0_MAX            (1) // 0x00000001
  #define PCU_CR_CLR_PERF_LIMIT_REASONS_PCU_SPARE_CLR_0_DEF            (0x00000000)
  #define PCU_CR_CLR_PERF_LIMIT_REASONS_PCU_SPARE_CLR_0_HSH            (0x01005904)

  #define PCU_CR_CLR_PERF_LIMIT_REASONS_PCU_SPARE_CLR_1_OFF            ( 1)
  #define PCU_CR_CLR_PERF_LIMIT_REASONS_PCU_SPARE_CLR_1_WID            ( 1)
  #define PCU_CR_CLR_PERF_LIMIT_REASONS_PCU_SPARE_CLR_1_MSK            (0x00000002)
  #define PCU_CR_CLR_PERF_LIMIT_REASONS_PCU_SPARE_CLR_1_MIN            (0)
  #define PCU_CR_CLR_PERF_LIMIT_REASONS_PCU_SPARE_CLR_1_MAX            (1) // 0x00000001
  #define PCU_CR_CLR_PERF_LIMIT_REASONS_PCU_SPARE_CLR_1_DEF            (0x00000000)
  #define PCU_CR_CLR_PERF_LIMIT_REASONS_PCU_SPARE_CLR_1_HSH            (0x01015904)

  #define PCU_CR_CLR_PERF_LIMIT_REASONS_PCU_SPARE_CLR_2_OFF            ( 2)
  #define PCU_CR_CLR_PERF_LIMIT_REASONS_PCU_SPARE_CLR_2_WID            ( 1)
  #define PCU_CR_CLR_PERF_LIMIT_REASONS_PCU_SPARE_CLR_2_MSK            (0x00000004)
  #define PCU_CR_CLR_PERF_LIMIT_REASONS_PCU_SPARE_CLR_2_MIN            (0)
  #define PCU_CR_CLR_PERF_LIMIT_REASONS_PCU_SPARE_CLR_2_MAX            (1) // 0x00000001
  #define PCU_CR_CLR_PERF_LIMIT_REASONS_PCU_SPARE_CLR_2_DEF            (0x00000000)
  #define PCU_CR_CLR_PERF_LIMIT_REASONS_PCU_SPARE_CLR_2_HSH            (0x01025904)

  #define PCU_CR_CLR_PERF_LIMIT_REASONS_PCU_SPARE_CLR_3_OFF            ( 3)
  #define PCU_CR_CLR_PERF_LIMIT_REASONS_PCU_SPARE_CLR_3_WID            ( 1)
  #define PCU_CR_CLR_PERF_LIMIT_REASONS_PCU_SPARE_CLR_3_MSK            (0x00000008)
  #define PCU_CR_CLR_PERF_LIMIT_REASONS_PCU_SPARE_CLR_3_MIN            (0)
  #define PCU_CR_CLR_PERF_LIMIT_REASONS_PCU_SPARE_CLR_3_MAX            (1) // 0x00000001
  #define PCU_CR_CLR_PERF_LIMIT_REASONS_PCU_SPARE_CLR_3_DEF            (0x00000000)
  #define PCU_CR_CLR_PERF_LIMIT_REASONS_PCU_SPARE_CLR_3_HSH            (0x01035904)

  #define PCU_CR_CLR_PERF_LIMIT_REASONS_PCU_SPARE_CLR_4_OFF            ( 4)
  #define PCU_CR_CLR_PERF_LIMIT_REASONS_PCU_SPARE_CLR_4_WID            ( 1)
  #define PCU_CR_CLR_PERF_LIMIT_REASONS_PCU_SPARE_CLR_4_MSK            (0x00000010)
  #define PCU_CR_CLR_PERF_LIMIT_REASONS_PCU_SPARE_CLR_4_MIN            (0)
  #define PCU_CR_CLR_PERF_LIMIT_REASONS_PCU_SPARE_CLR_4_MAX            (1) // 0x00000001
  #define PCU_CR_CLR_PERF_LIMIT_REASONS_PCU_SPARE_CLR_4_DEF            (0x00000000)
  #define PCU_CR_CLR_PERF_LIMIT_REASONS_PCU_SPARE_CLR_4_HSH            (0x01045904)

  #define PCU_CR_CLR_PERF_LIMIT_REASONS_PCU_SPARE_CLR_5_OFF            ( 5)
  #define PCU_CR_CLR_PERF_LIMIT_REASONS_PCU_SPARE_CLR_5_WID            ( 1)
  #define PCU_CR_CLR_PERF_LIMIT_REASONS_PCU_SPARE_CLR_5_MSK            (0x00000020)
  #define PCU_CR_CLR_PERF_LIMIT_REASONS_PCU_SPARE_CLR_5_MIN            (0)
  #define PCU_CR_CLR_PERF_LIMIT_REASONS_PCU_SPARE_CLR_5_MAX            (1) // 0x00000001
  #define PCU_CR_CLR_PERF_LIMIT_REASONS_PCU_SPARE_CLR_5_DEF            (0x00000000)
  #define PCU_CR_CLR_PERF_LIMIT_REASONS_PCU_SPARE_CLR_5_HSH            (0x01055904)

  #define PCU_CR_CLR_PERF_LIMIT_REASONS_PCU_SPARE_CLR_6_OFF            ( 6)
  #define PCU_CR_CLR_PERF_LIMIT_REASONS_PCU_SPARE_CLR_6_WID            ( 1)
  #define PCU_CR_CLR_PERF_LIMIT_REASONS_PCU_SPARE_CLR_6_MSK            (0x00000040)
  #define PCU_CR_CLR_PERF_LIMIT_REASONS_PCU_SPARE_CLR_6_MIN            (0)
  #define PCU_CR_CLR_PERF_LIMIT_REASONS_PCU_SPARE_CLR_6_MAX            (1) // 0x00000001
  #define PCU_CR_CLR_PERF_LIMIT_REASONS_PCU_SPARE_CLR_6_DEF            (0x00000000)
  #define PCU_CR_CLR_PERF_LIMIT_REASONS_PCU_SPARE_CLR_6_HSH            (0x01065904)

  #define PCU_CR_CLR_PERF_LIMIT_REASONS_PCU_SPARE_CLR_7_OFF            ( 7)
  #define PCU_CR_CLR_PERF_LIMIT_REASONS_PCU_SPARE_CLR_7_WID            ( 1)
  #define PCU_CR_CLR_PERF_LIMIT_REASONS_PCU_SPARE_CLR_7_MSK            (0x00000080)
  #define PCU_CR_CLR_PERF_LIMIT_REASONS_PCU_SPARE_CLR_7_MIN            (0)
  #define PCU_CR_CLR_PERF_LIMIT_REASONS_PCU_SPARE_CLR_7_MAX            (1) // 0x00000001
  #define PCU_CR_CLR_PERF_LIMIT_REASONS_PCU_SPARE_CLR_7_DEF            (0x00000000)
  #define PCU_CR_CLR_PERF_LIMIT_REASONS_PCU_SPARE_CLR_7_HSH            (0x01075904)

  #define PCU_CR_CLR_PERF_LIMIT_REASONS_PCU_SPARE_CLR_8_OFF            ( 8)
  #define PCU_CR_CLR_PERF_LIMIT_REASONS_PCU_SPARE_CLR_8_WID            ( 1)
  #define PCU_CR_CLR_PERF_LIMIT_REASONS_PCU_SPARE_CLR_8_MSK            (0x00000100)
  #define PCU_CR_CLR_PERF_LIMIT_REASONS_PCU_SPARE_CLR_8_MIN            (0)
  #define PCU_CR_CLR_PERF_LIMIT_REASONS_PCU_SPARE_CLR_8_MAX            (1) // 0x00000001
  #define PCU_CR_CLR_PERF_LIMIT_REASONS_PCU_SPARE_CLR_8_DEF            (0x00000000)
  #define PCU_CR_CLR_PERF_LIMIT_REASONS_PCU_SPARE_CLR_8_HSH            (0x01085904)

  #define PCU_CR_CLR_PERF_LIMIT_REASONS_PCU_SPARE_CLR_9_OFF            ( 9)
  #define PCU_CR_CLR_PERF_LIMIT_REASONS_PCU_SPARE_CLR_9_WID            ( 1)
  #define PCU_CR_CLR_PERF_LIMIT_REASONS_PCU_SPARE_CLR_9_MSK            (0x00000200)
  #define PCU_CR_CLR_PERF_LIMIT_REASONS_PCU_SPARE_CLR_9_MIN            (0)
  #define PCU_CR_CLR_PERF_LIMIT_REASONS_PCU_SPARE_CLR_9_MAX            (1) // 0x00000001
  #define PCU_CR_CLR_PERF_LIMIT_REASONS_PCU_SPARE_CLR_9_DEF            (0x00000000)
  #define PCU_CR_CLR_PERF_LIMIT_REASONS_PCU_SPARE_CLR_9_HSH            (0x01095904)

  #define PCU_CR_CLR_PERF_LIMIT_REASONS_PCU_EDP_ICC_STATUS_OFF         (10)
  #define PCU_CR_CLR_PERF_LIMIT_REASONS_PCU_EDP_ICC_STATUS_WID         ( 1)
  #define PCU_CR_CLR_PERF_LIMIT_REASONS_PCU_EDP_ICC_STATUS_MSK         (0x00000400)
  #define PCU_CR_CLR_PERF_LIMIT_REASONS_PCU_EDP_ICC_STATUS_MIN         (0)
  #define PCU_CR_CLR_PERF_LIMIT_REASONS_PCU_EDP_ICC_STATUS_MAX         (1) // 0x00000001
  #define PCU_CR_CLR_PERF_LIMIT_REASONS_PCU_EDP_ICC_STATUS_DEF         (0x00000000)
  #define PCU_CR_CLR_PERF_LIMIT_REASONS_PCU_EDP_ICC_STATUS_HSH         (0x010A5904)

  #define PCU_CR_CLR_PERF_LIMIT_REASONS_PCU_SPARE_CLR_11_OFF           (11)
  #define PCU_CR_CLR_PERF_LIMIT_REASONS_PCU_SPARE_CLR_11_WID           ( 1)
  #define PCU_CR_CLR_PERF_LIMIT_REASONS_PCU_SPARE_CLR_11_MSK           (0x00000800)
  #define PCU_CR_CLR_PERF_LIMIT_REASONS_PCU_SPARE_CLR_11_MIN           (0)
  #define PCU_CR_CLR_PERF_LIMIT_REASONS_PCU_SPARE_CLR_11_MAX           (1) // 0x00000001
  #define PCU_CR_CLR_PERF_LIMIT_REASONS_PCU_SPARE_CLR_11_DEF           (0x00000000)
  #define PCU_CR_CLR_PERF_LIMIT_REASONS_PCU_SPARE_CLR_11_HSH           (0x010B5904)

  #define PCU_CR_CLR_PERF_LIMIT_REASONS_PCU_SPARE_CLR_12_OFF           (12)
  #define PCU_CR_CLR_PERF_LIMIT_REASONS_PCU_SPARE_CLR_12_WID           ( 1)
  #define PCU_CR_CLR_PERF_LIMIT_REASONS_PCU_SPARE_CLR_12_MSK           (0x00001000)
  #define PCU_CR_CLR_PERF_LIMIT_REASONS_PCU_SPARE_CLR_12_MIN           (0)
  #define PCU_CR_CLR_PERF_LIMIT_REASONS_PCU_SPARE_CLR_12_MAX           (1) // 0x00000001
  #define PCU_CR_CLR_PERF_LIMIT_REASONS_PCU_SPARE_CLR_12_DEF           (0x00000000)
  #define PCU_CR_CLR_PERF_LIMIT_REASONS_PCU_SPARE_CLR_12_HSH           (0x010C5904)

  #define PCU_CR_CLR_PERF_LIMIT_REASONS_PCU_SPARE_CLR_13_OFF           (13)
  #define PCU_CR_CLR_PERF_LIMIT_REASONS_PCU_SPARE_CLR_13_WID           ( 1)
  #define PCU_CR_CLR_PERF_LIMIT_REASONS_PCU_SPARE_CLR_13_MSK           (0x00002000)
  #define PCU_CR_CLR_PERF_LIMIT_REASONS_PCU_SPARE_CLR_13_MIN           (0)
  #define PCU_CR_CLR_PERF_LIMIT_REASONS_PCU_SPARE_CLR_13_MAX           (1) // 0x00000001
  #define PCU_CR_CLR_PERF_LIMIT_REASONS_PCU_SPARE_CLR_13_DEF           (0x00000000)
  #define PCU_CR_CLR_PERF_LIMIT_REASONS_PCU_SPARE_CLR_13_HSH           (0x010D5904)

  #define PCU_CR_CLR_PERF_LIMIT_REASONS_PCU_SPARE_CLR_14_OFF           (14)
  #define PCU_CR_CLR_PERF_LIMIT_REASONS_PCU_SPARE_CLR_14_WID           ( 1)
  #define PCU_CR_CLR_PERF_LIMIT_REASONS_PCU_SPARE_CLR_14_MSK           (0x00004000)
  #define PCU_CR_CLR_PERF_LIMIT_REASONS_PCU_SPARE_CLR_14_MIN           (0)
  #define PCU_CR_CLR_PERF_LIMIT_REASONS_PCU_SPARE_CLR_14_MAX           (1) // 0x00000001
  #define PCU_CR_CLR_PERF_LIMIT_REASONS_PCU_SPARE_CLR_14_DEF           (0x00000000)
  #define PCU_CR_CLR_PERF_LIMIT_REASONS_PCU_SPARE_CLR_14_HSH           (0x010E5904)

  #define PCU_CR_CLR_PERF_LIMIT_REASONS_PCU_SPARE_CLR_15_OFF           (15)
  #define PCU_CR_CLR_PERF_LIMIT_REASONS_PCU_SPARE_CLR_15_WID           ( 1)
  #define PCU_CR_CLR_PERF_LIMIT_REASONS_PCU_SPARE_CLR_15_MSK           (0x00008000)
  #define PCU_CR_CLR_PERF_LIMIT_REASONS_PCU_SPARE_CLR_15_MIN           (0)
  #define PCU_CR_CLR_PERF_LIMIT_REASONS_PCU_SPARE_CLR_15_MAX           (1) // 0x00000001
  #define PCU_CR_CLR_PERF_LIMIT_REASONS_PCU_SPARE_CLR_15_DEF           (0x00000000)
  #define PCU_CR_CLR_PERF_LIMIT_REASONS_PCU_SPARE_CLR_15_HSH           (0x010F5904)

  #define PCU_CR_CLR_PERF_LIMIT_REASONS_PCU_SPARE_CLR_LOG_0_OFF        (16)
  #define PCU_CR_CLR_PERF_LIMIT_REASONS_PCU_SPARE_CLR_LOG_0_WID        ( 1)
  #define PCU_CR_CLR_PERF_LIMIT_REASONS_PCU_SPARE_CLR_LOG_0_MSK        (0x00010000)
  #define PCU_CR_CLR_PERF_LIMIT_REASONS_PCU_SPARE_CLR_LOG_0_MIN        (0)
  #define PCU_CR_CLR_PERF_LIMIT_REASONS_PCU_SPARE_CLR_LOG_0_MAX        (1) // 0x00000001
  #define PCU_CR_CLR_PERF_LIMIT_REASONS_PCU_SPARE_CLR_LOG_0_DEF        (0x00000000)
  #define PCU_CR_CLR_PERF_LIMIT_REASONS_PCU_SPARE_CLR_LOG_0_HSH        (0x01105904)

  #define PCU_CR_CLR_PERF_LIMIT_REASONS_PCU_SPARE_CLR_LOG_1_OFF        (17)
  #define PCU_CR_CLR_PERF_LIMIT_REASONS_PCU_SPARE_CLR_LOG_1_WID        ( 1)
  #define PCU_CR_CLR_PERF_LIMIT_REASONS_PCU_SPARE_CLR_LOG_1_MSK        (0x00020000)
  #define PCU_CR_CLR_PERF_LIMIT_REASONS_PCU_SPARE_CLR_LOG_1_MIN        (0)
  #define PCU_CR_CLR_PERF_LIMIT_REASONS_PCU_SPARE_CLR_LOG_1_MAX        (1) // 0x00000001
  #define PCU_CR_CLR_PERF_LIMIT_REASONS_PCU_SPARE_CLR_LOG_1_DEF        (0x00000000)
  #define PCU_CR_CLR_PERF_LIMIT_REASONS_PCU_SPARE_CLR_LOG_1_HSH        (0x01115904)

  #define PCU_CR_CLR_PERF_LIMIT_REASONS_PCU_SPARE_CLR_LOG_2_OFF        (18)
  #define PCU_CR_CLR_PERF_LIMIT_REASONS_PCU_SPARE_CLR_LOG_2_WID        ( 1)
  #define PCU_CR_CLR_PERF_LIMIT_REASONS_PCU_SPARE_CLR_LOG_2_MSK        (0x00040000)
  #define PCU_CR_CLR_PERF_LIMIT_REASONS_PCU_SPARE_CLR_LOG_2_MIN        (0)
  #define PCU_CR_CLR_PERF_LIMIT_REASONS_PCU_SPARE_CLR_LOG_2_MAX        (1) // 0x00000001
  #define PCU_CR_CLR_PERF_LIMIT_REASONS_PCU_SPARE_CLR_LOG_2_DEF        (0x00000000)
  #define PCU_CR_CLR_PERF_LIMIT_REASONS_PCU_SPARE_CLR_LOG_2_HSH        (0x01125904)

  #define PCU_CR_CLR_PERF_LIMIT_REASONS_PCU_SPARE_CLR_LOG_3_OFF        (19)
  #define PCU_CR_CLR_PERF_LIMIT_REASONS_PCU_SPARE_CLR_LOG_3_WID        ( 1)
  #define PCU_CR_CLR_PERF_LIMIT_REASONS_PCU_SPARE_CLR_LOG_3_MSK        (0x00080000)
  #define PCU_CR_CLR_PERF_LIMIT_REASONS_PCU_SPARE_CLR_LOG_3_MIN        (0)
  #define PCU_CR_CLR_PERF_LIMIT_REASONS_PCU_SPARE_CLR_LOG_3_MAX        (1) // 0x00000001
  #define PCU_CR_CLR_PERF_LIMIT_REASONS_PCU_SPARE_CLR_LOG_3_DEF        (0x00000000)
  #define PCU_CR_CLR_PERF_LIMIT_REASONS_PCU_SPARE_CLR_LOG_3_HSH        (0x01135904)

  #define PCU_CR_CLR_PERF_LIMIT_REASONS_PCU_SPARE_CLR_LOG_4_OFF        (20)
  #define PCU_CR_CLR_PERF_LIMIT_REASONS_PCU_SPARE_CLR_LOG_4_WID        ( 1)
  #define PCU_CR_CLR_PERF_LIMIT_REASONS_PCU_SPARE_CLR_LOG_4_MSK        (0x00100000)
  #define PCU_CR_CLR_PERF_LIMIT_REASONS_PCU_SPARE_CLR_LOG_4_MIN        (0)
  #define PCU_CR_CLR_PERF_LIMIT_REASONS_PCU_SPARE_CLR_LOG_4_MAX        (1) // 0x00000001
  #define PCU_CR_CLR_PERF_LIMIT_REASONS_PCU_SPARE_CLR_LOG_4_DEF        (0x00000000)
  #define PCU_CR_CLR_PERF_LIMIT_REASONS_PCU_SPARE_CLR_LOG_4_HSH        (0x01145904)

  #define PCU_CR_CLR_PERF_LIMIT_REASONS_PCU_SPARE_CLR_LOG_5_OFF        (21)
  #define PCU_CR_CLR_PERF_LIMIT_REASONS_PCU_SPARE_CLR_LOG_5_WID        ( 1)
  #define PCU_CR_CLR_PERF_LIMIT_REASONS_PCU_SPARE_CLR_LOG_5_MSK        (0x00200000)
  #define PCU_CR_CLR_PERF_LIMIT_REASONS_PCU_SPARE_CLR_LOG_5_MIN        (0)
  #define PCU_CR_CLR_PERF_LIMIT_REASONS_PCU_SPARE_CLR_LOG_5_MAX        (1) // 0x00000001
  #define PCU_CR_CLR_PERF_LIMIT_REASONS_PCU_SPARE_CLR_LOG_5_DEF        (0x00000000)
  #define PCU_CR_CLR_PERF_LIMIT_REASONS_PCU_SPARE_CLR_LOG_5_HSH        (0x01155904)

  #define PCU_CR_CLR_PERF_LIMIT_REASONS_PCU_SPARE_CLR_LOG_6_OFF        (22)
  #define PCU_CR_CLR_PERF_LIMIT_REASONS_PCU_SPARE_CLR_LOG_6_WID        ( 1)
  #define PCU_CR_CLR_PERF_LIMIT_REASONS_PCU_SPARE_CLR_LOG_6_MSK        (0x00400000)
  #define PCU_CR_CLR_PERF_LIMIT_REASONS_PCU_SPARE_CLR_LOG_6_MIN        (0)
  #define PCU_CR_CLR_PERF_LIMIT_REASONS_PCU_SPARE_CLR_LOG_6_MAX        (1) // 0x00000001
  #define PCU_CR_CLR_PERF_LIMIT_REASONS_PCU_SPARE_CLR_LOG_6_DEF        (0x00000000)
  #define PCU_CR_CLR_PERF_LIMIT_REASONS_PCU_SPARE_CLR_LOG_6_HSH        (0x01165904)

  #define PCU_CR_CLR_PERF_LIMIT_REASONS_PCU_SPARE_CLR_LOG_7_OFF        (23)
  #define PCU_CR_CLR_PERF_LIMIT_REASONS_PCU_SPARE_CLR_LOG_7_WID        ( 1)
  #define PCU_CR_CLR_PERF_LIMIT_REASONS_PCU_SPARE_CLR_LOG_7_MSK        (0x00800000)
  #define PCU_CR_CLR_PERF_LIMIT_REASONS_PCU_SPARE_CLR_LOG_7_MIN        (0)
  #define PCU_CR_CLR_PERF_LIMIT_REASONS_PCU_SPARE_CLR_LOG_7_MAX        (1) // 0x00000001
  #define PCU_CR_CLR_PERF_LIMIT_REASONS_PCU_SPARE_CLR_LOG_7_DEF        (0x00000000)
  #define PCU_CR_CLR_PERF_LIMIT_REASONS_PCU_SPARE_CLR_LOG_7_HSH        (0x01175904)

  #define PCU_CR_CLR_PERF_LIMIT_REASONS_PCU_SPARE_CLR_LOG_8_OFF        (24)
  #define PCU_CR_CLR_PERF_LIMIT_REASONS_PCU_SPARE_CLR_LOG_8_WID        ( 1)
  #define PCU_CR_CLR_PERF_LIMIT_REASONS_PCU_SPARE_CLR_LOG_8_MSK        (0x01000000)
  #define PCU_CR_CLR_PERF_LIMIT_REASONS_PCU_SPARE_CLR_LOG_8_MIN        (0)
  #define PCU_CR_CLR_PERF_LIMIT_REASONS_PCU_SPARE_CLR_LOG_8_MAX        (1) // 0x00000001
  #define PCU_CR_CLR_PERF_LIMIT_REASONS_PCU_SPARE_CLR_LOG_8_DEF        (0x00000000)
  #define PCU_CR_CLR_PERF_LIMIT_REASONS_PCU_SPARE_CLR_LOG_8_HSH        (0x01185904)

  #define PCU_CR_CLR_PERF_LIMIT_REASONS_PCU_SPARE_CLR_LOG_9_OFF        (25)
  #define PCU_CR_CLR_PERF_LIMIT_REASONS_PCU_SPARE_CLR_LOG_9_WID        ( 1)
  #define PCU_CR_CLR_PERF_LIMIT_REASONS_PCU_SPARE_CLR_LOG_9_MSK        (0x02000000)
  #define PCU_CR_CLR_PERF_LIMIT_REASONS_PCU_SPARE_CLR_LOG_9_MIN        (0)
  #define PCU_CR_CLR_PERF_LIMIT_REASONS_PCU_SPARE_CLR_LOG_9_MAX        (1) // 0x00000001
  #define PCU_CR_CLR_PERF_LIMIT_REASONS_PCU_SPARE_CLR_LOG_9_DEF        (0x00000000)
  #define PCU_CR_CLR_PERF_LIMIT_REASONS_PCU_SPARE_CLR_LOG_9_HSH        (0x01195904)

  #define PCU_CR_CLR_PERF_LIMIT_REASONS_PCU_EDP_ICC_LOG_OFF            (26)
  #define PCU_CR_CLR_PERF_LIMIT_REASONS_PCU_EDP_ICC_LOG_WID            ( 1)
  #define PCU_CR_CLR_PERF_LIMIT_REASONS_PCU_EDP_ICC_LOG_MSK            (0x04000000)
  #define PCU_CR_CLR_PERF_LIMIT_REASONS_PCU_EDP_ICC_LOG_MIN            (0)
  #define PCU_CR_CLR_PERF_LIMIT_REASONS_PCU_EDP_ICC_LOG_MAX            (1) // 0x00000001
  #define PCU_CR_CLR_PERF_LIMIT_REASONS_PCU_EDP_ICC_LOG_DEF            (0x00000000)
  #define PCU_CR_CLR_PERF_LIMIT_REASONS_PCU_EDP_ICC_LOG_HSH            (0x011A5904)

  #define PCU_CR_CLR_PERF_LIMIT_REASONS_PCU_SPARE_CLR_LOG_11_OFF       (27)
  #define PCU_CR_CLR_PERF_LIMIT_REASONS_PCU_SPARE_CLR_LOG_11_WID       ( 1)
  #define PCU_CR_CLR_PERF_LIMIT_REASONS_PCU_SPARE_CLR_LOG_11_MSK       (0x08000000)
  #define PCU_CR_CLR_PERF_LIMIT_REASONS_PCU_SPARE_CLR_LOG_11_MIN       (0)
  #define PCU_CR_CLR_PERF_LIMIT_REASONS_PCU_SPARE_CLR_LOG_11_MAX       (1) // 0x00000001
  #define PCU_CR_CLR_PERF_LIMIT_REASONS_PCU_SPARE_CLR_LOG_11_DEF       (0x00000000)
  #define PCU_CR_CLR_PERF_LIMIT_REASONS_PCU_SPARE_CLR_LOG_11_HSH       (0x011B5904)

  #define PCU_CR_CLR_PERF_LIMIT_REASONS_PCU_SPARE_CLR_LOG_12_OFF       (28)
  #define PCU_CR_CLR_PERF_LIMIT_REASONS_PCU_SPARE_CLR_LOG_12_WID       ( 1)
  #define PCU_CR_CLR_PERF_LIMIT_REASONS_PCU_SPARE_CLR_LOG_12_MSK       (0x10000000)
  #define PCU_CR_CLR_PERF_LIMIT_REASONS_PCU_SPARE_CLR_LOG_12_MIN       (0)
  #define PCU_CR_CLR_PERF_LIMIT_REASONS_PCU_SPARE_CLR_LOG_12_MAX       (1) // 0x00000001
  #define PCU_CR_CLR_PERF_LIMIT_REASONS_PCU_SPARE_CLR_LOG_12_DEF       (0x00000000)
  #define PCU_CR_CLR_PERF_LIMIT_REASONS_PCU_SPARE_CLR_LOG_12_HSH       (0x011C5904)

  #define PCU_CR_CLR_PERF_LIMIT_REASONS_PCU_SPARE_CLR_LOG_13_OFF       (29)
  #define PCU_CR_CLR_PERF_LIMIT_REASONS_PCU_SPARE_CLR_LOG_13_WID       ( 1)
  #define PCU_CR_CLR_PERF_LIMIT_REASONS_PCU_SPARE_CLR_LOG_13_MSK       (0x20000000)
  #define PCU_CR_CLR_PERF_LIMIT_REASONS_PCU_SPARE_CLR_LOG_13_MIN       (0)
  #define PCU_CR_CLR_PERF_LIMIT_REASONS_PCU_SPARE_CLR_LOG_13_MAX       (1) // 0x00000001
  #define PCU_CR_CLR_PERF_LIMIT_REASONS_PCU_SPARE_CLR_LOG_13_DEF       (0x00000000)
  #define PCU_CR_CLR_PERF_LIMIT_REASONS_PCU_SPARE_CLR_LOG_13_HSH       (0x011D5904)

  #define PCU_CR_CLR_PERF_LIMIT_REASONS_PCU_SPARE_CLR_LOG_14_OFF       (30)
  #define PCU_CR_CLR_PERF_LIMIT_REASONS_PCU_SPARE_CLR_LOG_14_WID       ( 1)
  #define PCU_CR_CLR_PERF_LIMIT_REASONS_PCU_SPARE_CLR_LOG_14_MSK       (0x40000000)
  #define PCU_CR_CLR_PERF_LIMIT_REASONS_PCU_SPARE_CLR_LOG_14_MIN       (0)
  #define PCU_CR_CLR_PERF_LIMIT_REASONS_PCU_SPARE_CLR_LOG_14_MAX       (1) // 0x00000001
  #define PCU_CR_CLR_PERF_LIMIT_REASONS_PCU_SPARE_CLR_LOG_14_DEF       (0x00000000)
  #define PCU_CR_CLR_PERF_LIMIT_REASONS_PCU_SPARE_CLR_LOG_14_HSH       (0x011E5904)

  #define PCU_CR_CLR_PERF_LIMIT_REASONS_PCU_SPARE_CLR_LOG_15_OFF       (31)
  #define PCU_CR_CLR_PERF_LIMIT_REASONS_PCU_SPARE_CLR_LOG_15_WID       ( 1)
  #define PCU_CR_CLR_PERF_LIMIT_REASONS_PCU_SPARE_CLR_LOG_15_MSK       (0x80000000)
  #define PCU_CR_CLR_PERF_LIMIT_REASONS_PCU_SPARE_CLR_LOG_15_MIN       (0)
  #define PCU_CR_CLR_PERF_LIMIT_REASONS_PCU_SPARE_CLR_LOG_15_MAX       (1) // 0x00000001
  #define PCU_CR_CLR_PERF_LIMIT_REASONS_PCU_SPARE_CLR_LOG_15_DEF       (0x00000000)
  #define PCU_CR_CLR_PERF_LIMIT_REASONS_PCU_SPARE_CLR_LOG_15_HSH       (0x011F5904)

#define PCU_CR_PRIP_TURBO_PLCY_PCU_REG                                 (0x00005920)

  #define PCU_CR_PRIP_TURBO_PLCY_PCU_PRIPTP_OFF                        ( 0)
  #define PCU_CR_PRIP_TURBO_PLCY_PCU_PRIPTP_WID                        ( 5)
  #define PCU_CR_PRIP_TURBO_PLCY_PCU_PRIPTP_MSK                        (0x0000001F)
  #define PCU_CR_PRIP_TURBO_PLCY_PCU_PRIPTP_MIN                        (0)
  #define PCU_CR_PRIP_TURBO_PLCY_PCU_PRIPTP_MAX                        (31) // 0x0000001F
  #define PCU_CR_PRIP_TURBO_PLCY_PCU_PRIPTP_DEF                        (0x00000000)
  #define PCU_CR_PRIP_TURBO_PLCY_PCU_PRIPTP_HSH                        (0x05005920)

#define PCU_CR_SECP_TURBO_PLCY_PCU_REG                                 (0x00005924)

  #define PCU_CR_SECP_TURBO_PLCY_PCU_SECPTP_OFF                        ( 0)
  #define PCU_CR_SECP_TURBO_PLCY_PCU_SECPTP_WID                        ( 5)
  #define PCU_CR_SECP_TURBO_PLCY_PCU_SECPTP_MSK                        (0x0000001F)
  #define PCU_CR_SECP_TURBO_PLCY_PCU_SECPTP_MIN                        (0)
  #define PCU_CR_SECP_TURBO_PLCY_PCU_SECPTP_MAX                        (31) // 0x0000001F
  #define PCU_CR_SECP_TURBO_PLCY_PCU_SECPTP_DEF                        (0x00000010)
  #define PCU_CR_SECP_TURBO_PLCY_PCU_SECPTP_HSH                        (0x05005924)

#define PCU_CR_PRIP_NRG_STTS_PCU_REG                                   (0x00005928)

  #define PCU_CR_PRIP_NRG_STTS_PCU_DATA_OFF                            ( 0)
  #define PCU_CR_PRIP_NRG_STTS_PCU_DATA_WID                            (32)
  #define PCU_CR_PRIP_NRG_STTS_PCU_DATA_MSK                            (0xFFFFFFFF)
  #define PCU_CR_PRIP_NRG_STTS_PCU_DATA_MIN                            (0)
  #define PCU_CR_PRIP_NRG_STTS_PCU_DATA_MAX                            (4294967295) // 0xFFFFFFFF
  #define PCU_CR_PRIP_NRG_STTS_PCU_DATA_DEF                            (0x00000000)
  #define PCU_CR_PRIP_NRG_STTS_PCU_DATA_HSH                            (0x20005928)

#define PCU_CR_SECP_NRG_STTS_PCU_REG                                   (0x0000592C)

  #define PCU_CR_SECP_NRG_STTS_PCU_DATA_OFF                            ( 0)
  #define PCU_CR_SECP_NRG_STTS_PCU_DATA_WID                            (32)
  #define PCU_CR_SECP_NRG_STTS_PCU_DATA_MSK                            (0xFFFFFFFF)
  #define PCU_CR_SECP_NRG_STTS_PCU_DATA_MIN                            (0)
  #define PCU_CR_SECP_NRG_STTS_PCU_DATA_MAX                            (4294967295) // 0xFFFFFFFF
  #define PCU_CR_SECP_NRG_STTS_PCU_DATA_DEF                            (0x00000000)
  #define PCU_CR_SECP_NRG_STTS_PCU_DATA_HSH                            (0x2000592C)

#define PCU_CR_PACKAGE_POWER_SKU_PCU_REG                               (0x00005930)

  #define PCU_CR_PACKAGE_POWER_SKU_PCU_PKG_TDP_OFF                     ( 0)
  #define PCU_CR_PACKAGE_POWER_SKU_PCU_PKG_TDP_WID                     (15)
  #define PCU_CR_PACKAGE_POWER_SKU_PCU_PKG_TDP_MSK                     (0x00007FFF)
  #define PCU_CR_PACKAGE_POWER_SKU_PCU_PKG_TDP_MIN                     (0)
  #define PCU_CR_PACKAGE_POWER_SKU_PCU_PKG_TDP_MAX                     (32767) // 0x00007FFF
  #define PCU_CR_PACKAGE_POWER_SKU_PCU_PKG_TDP_DEF                     (0x00000118)
  #define PCU_CR_PACKAGE_POWER_SKU_PCU_PKG_TDP_HSH                     (0x4F005930)

  #define PCU_CR_PACKAGE_POWER_SKU_PCU_PKG_MIN_PWR_OFF                 (16)
  #define PCU_CR_PACKAGE_POWER_SKU_PCU_PKG_MIN_PWR_WID                 (15)
  #define PCU_CR_PACKAGE_POWER_SKU_PCU_PKG_MIN_PWR_MSK                 (0x7FFF0000)
  #define PCU_CR_PACKAGE_POWER_SKU_PCU_PKG_MIN_PWR_MIN                 (0)
  #define PCU_CR_PACKAGE_POWER_SKU_PCU_PKG_MIN_PWR_MAX                 (32767) // 0x00007FFF
  #define PCU_CR_PACKAGE_POWER_SKU_PCU_PKG_MIN_PWR_DEF                 (0x00000060)
  #define PCU_CR_PACKAGE_POWER_SKU_PCU_PKG_MIN_PWR_HSH                 (0x4F105930)

  #define PCU_CR_PACKAGE_POWER_SKU_PCU_PKG_MAX_PWR_OFF                 (32)
  #define PCU_CR_PACKAGE_POWER_SKU_PCU_PKG_MAX_PWR_WID                 (15)
  #define PCU_CR_PACKAGE_POWER_SKU_PCU_PKG_MAX_PWR_MSK                 (0x00007FFF00000000ULL)
  #define PCU_CR_PACKAGE_POWER_SKU_PCU_PKG_MAX_PWR_MIN                 (0)
  #define PCU_CR_PACKAGE_POWER_SKU_PCU_PKG_MAX_PWR_MAX                 (32767) // 0x00007FFF
  #define PCU_CR_PACKAGE_POWER_SKU_PCU_PKG_MAX_PWR_DEF                 (0x00000240)
  #define PCU_CR_PACKAGE_POWER_SKU_PCU_PKG_MAX_PWR_HSH                 (0x4F205930)

  #define PCU_CR_PACKAGE_POWER_SKU_PCU_PKG_MAX_WIN_OFF                 (48)
  #define PCU_CR_PACKAGE_POWER_SKU_PCU_PKG_MAX_WIN_WID                 ( 7)
  #define PCU_CR_PACKAGE_POWER_SKU_PCU_PKG_MAX_WIN_MSK                 (0x007F000000000000ULL)
  #define PCU_CR_PACKAGE_POWER_SKU_PCU_PKG_MAX_WIN_MIN                 (0)
  #define PCU_CR_PACKAGE_POWER_SKU_PCU_PKG_MAX_WIN_MAX                 (127) // 0x0000007F
  #define PCU_CR_PACKAGE_POWER_SKU_PCU_PKG_MAX_WIN_DEF                 (0x00000012)
  #define PCU_CR_PACKAGE_POWER_SKU_PCU_PKG_MAX_WIN_HSH                 (0x47305930)

#define PCU_CR_PACKAGE_POWER_SKU_UNIT_PCU_REG                          (0x00005938)

  #define PCU_CR_PACKAGE_POWER_SKU_UNIT_PCU_PWR_UNIT_OFF               ( 0)
  #define PCU_CR_PACKAGE_POWER_SKU_UNIT_PCU_PWR_UNIT_WID               ( 4)
  #define PCU_CR_PACKAGE_POWER_SKU_UNIT_PCU_PWR_UNIT_MSK               (0x0000000F)
  #define PCU_CR_PACKAGE_POWER_SKU_UNIT_PCU_PWR_UNIT_MIN               (0)
  #define PCU_CR_PACKAGE_POWER_SKU_UNIT_PCU_PWR_UNIT_MAX               (15) // 0x0000000F
  #define PCU_CR_PACKAGE_POWER_SKU_UNIT_PCU_PWR_UNIT_DEF               (0x00000003)
  #define PCU_CR_PACKAGE_POWER_SKU_UNIT_PCU_PWR_UNIT_HSH               (0x04005938)

  #define PCU_CR_PACKAGE_POWER_SKU_UNIT_PCU_ENERGY_UNIT_OFF            ( 8)
  #define PCU_CR_PACKAGE_POWER_SKU_UNIT_PCU_ENERGY_UNIT_WID            ( 5)
  #define PCU_CR_PACKAGE_POWER_SKU_UNIT_PCU_ENERGY_UNIT_MSK            (0x00001F00)
  #define PCU_CR_PACKAGE_POWER_SKU_UNIT_PCU_ENERGY_UNIT_MIN            (0)
  #define PCU_CR_PACKAGE_POWER_SKU_UNIT_PCU_ENERGY_UNIT_MAX            (31) // 0x0000001F
  #define PCU_CR_PACKAGE_POWER_SKU_UNIT_PCU_ENERGY_UNIT_DEF            (0x0000000E)
  #define PCU_CR_PACKAGE_POWER_SKU_UNIT_PCU_ENERGY_UNIT_HSH            (0x05085938)

  #define PCU_CR_PACKAGE_POWER_SKU_UNIT_PCU_TIME_UNIT_OFF              (16)
  #define PCU_CR_PACKAGE_POWER_SKU_UNIT_PCU_TIME_UNIT_WID              ( 4)
  #define PCU_CR_PACKAGE_POWER_SKU_UNIT_PCU_TIME_UNIT_MSK              (0x000F0000)
  #define PCU_CR_PACKAGE_POWER_SKU_UNIT_PCU_TIME_UNIT_MIN              (0)
  #define PCU_CR_PACKAGE_POWER_SKU_UNIT_PCU_TIME_UNIT_MAX              (15) // 0x0000000F
  #define PCU_CR_PACKAGE_POWER_SKU_UNIT_PCU_TIME_UNIT_DEF              (0x0000000A)
  #define PCU_CR_PACKAGE_POWER_SKU_UNIT_PCU_TIME_UNIT_HSH              (0x04105938)

#define PCU_CR_PACKAGE_ENERGY_STATUS_PCU_REG                           (0x0000593C)

  #define PCU_CR_PACKAGE_ENERGY_STATUS_PCU_DATA_OFF                    ( 0)
  #define PCU_CR_PACKAGE_ENERGY_STATUS_PCU_DATA_WID                    (32)
  #define PCU_CR_PACKAGE_ENERGY_STATUS_PCU_DATA_MSK                    (0xFFFFFFFF)
  #define PCU_CR_PACKAGE_ENERGY_STATUS_PCU_DATA_MIN                    (0)
  #define PCU_CR_PACKAGE_ENERGY_STATUS_PCU_DATA_MAX                    (4294967295) // 0xFFFFFFFF
  #define PCU_CR_PACKAGE_ENERGY_STATUS_PCU_DATA_DEF                    (0x00000000)
  #define PCU_CR_PACKAGE_ENERGY_STATUS_PCU_DATA_HSH                    (0x2000593C)

#define PCU_CR_GT_IO_BUSYNESS_PCU_REG                                  (0x00005940)

  #define PCU_CR_GT_IO_BUSYNESS_PCU_DATA_OFF                           ( 0)
  #define PCU_CR_GT_IO_BUSYNESS_PCU_DATA_WID                           (32)
  #define PCU_CR_GT_IO_BUSYNESS_PCU_DATA_MSK                           (0xFFFFFFFF)
  #define PCU_CR_GT_IO_BUSYNESS_PCU_DATA_MIN                           (0)
  #define PCU_CR_GT_IO_BUSYNESS_PCU_DATA_MAX                           (4294967295) // 0xFFFFFFFF
  #define PCU_CR_GT_IO_BUSYNESS_PCU_DATA_DEF                           (0x00000000)
  #define PCU_CR_GT_IO_BUSYNESS_PCU_DATA_HSH                           (0x20005940)

#define PCU_CR_GT_VIDEO_BUSYNESS_PCU_REG                               (0x00005944)

  #define PCU_CR_GT_VIDEO_BUSYNESS_PCU_DATA_OFF                        ( 0)
  #define PCU_CR_GT_VIDEO_BUSYNESS_PCU_DATA_WID                        (32)
  #define PCU_CR_GT_VIDEO_BUSYNESS_PCU_DATA_MSK                        (0xFFFFFFFF)
  #define PCU_CR_GT_VIDEO_BUSYNESS_PCU_DATA_MIN                        (0)
  #define PCU_CR_GT_VIDEO_BUSYNESS_PCU_DATA_MAX                        (4294967295) // 0xFFFFFFFF
  #define PCU_CR_GT_VIDEO_BUSYNESS_PCU_DATA_DEF                        (0x00000000)
  #define PCU_CR_GT_VIDEO_BUSYNESS_PCU_DATA_HSH                        (0x20005944)

#define PCU_CR_GT_PERF_STATUS_PCU_REG                                  (0x00005948)

  #define PCU_CR_GT_PERF_STATUS_PCU_RP_STATE_VOLTAGE_OFF               ( 0)
  #define PCU_CR_GT_PERF_STATUS_PCU_RP_STATE_VOLTAGE_WID               ( 8)
  #define PCU_CR_GT_PERF_STATUS_PCU_RP_STATE_VOLTAGE_MSK               (0x000000FF)
  #define PCU_CR_GT_PERF_STATUS_PCU_RP_STATE_VOLTAGE_MIN               (0)
  #define PCU_CR_GT_PERF_STATUS_PCU_RP_STATE_VOLTAGE_MAX               (255) // 0x000000FF
  #define PCU_CR_GT_PERF_STATUS_PCU_RP_STATE_VOLTAGE_DEF               (0x00000000)
  #define PCU_CR_GT_PERF_STATUS_PCU_RP_STATE_VOLTAGE_HSH               (0x08005948)

  #define PCU_CR_GT_PERF_STATUS_PCU_RP_STATE_RATIO_UNSLICE_OFF         ( 8)
  #define PCU_CR_GT_PERF_STATUS_PCU_RP_STATE_RATIO_UNSLICE_WID         ( 9)
  #define PCU_CR_GT_PERF_STATUS_PCU_RP_STATE_RATIO_UNSLICE_MSK         (0x0001FF00)
  #define PCU_CR_GT_PERF_STATUS_PCU_RP_STATE_RATIO_UNSLICE_MIN         (0)
  #define PCU_CR_GT_PERF_STATUS_PCU_RP_STATE_RATIO_UNSLICE_MAX         (511) // 0x000001FF
  #define PCU_CR_GT_PERF_STATUS_PCU_RP_STATE_RATIO_UNSLICE_DEF         (0x00000000)
  #define PCU_CR_GT_PERF_STATUS_PCU_RP_STATE_RATIO_UNSLICE_HSH         (0x09085948)

  #define PCU_CR_GT_PERF_STATUS_PCU_RP_STATE_RATIO_SLICE_OFF           (17)
  #define PCU_CR_GT_PERF_STATUS_PCU_RP_STATE_RATIO_SLICE_WID           ( 9)
  #define PCU_CR_GT_PERF_STATUS_PCU_RP_STATE_RATIO_SLICE_MSK           (0x03FE0000)
  #define PCU_CR_GT_PERF_STATUS_PCU_RP_STATE_RATIO_SLICE_MIN           (0)
  #define PCU_CR_GT_PERF_STATUS_PCU_RP_STATE_RATIO_SLICE_MAX           (511) // 0x000001FF
  #define PCU_CR_GT_PERF_STATUS_PCU_RP_STATE_RATIO_SLICE_DEF           (0x00000000)
  #define PCU_CR_GT_PERF_STATUS_PCU_RP_STATE_RATIO_SLICE_HSH           (0x09115948)

#define PCU_CR_SA_PERF_STATUS_PCU_REG                                  (0x0000594C)

  #define PCU_CR_SA_PERF_STATUS_PCU_QCLK_RATIO_OFF                     ( 0)
  #define PCU_CR_SA_PERF_STATUS_PCU_QCLK_RATIO_WID                     ( 7)
  #define PCU_CR_SA_PERF_STATUS_PCU_QCLK_RATIO_MSK                     (0x0000007F)
  #define PCU_CR_SA_PERF_STATUS_PCU_QCLK_RATIO_MIN                     (0)
  #define PCU_CR_SA_PERF_STATUS_PCU_QCLK_RATIO_MAX                     (127) // 0x0000007F
  #define PCU_CR_SA_PERF_STATUS_PCU_QCLK_RATIO_DEF                     (0x00000000)
  #define PCU_CR_SA_PERF_STATUS_PCU_QCLK_RATIO_HSH                     (0x0700594C)

  #define PCU_CR_SA_PERF_STATUS_PCU_QCLK_REFERENCE_OFF                 ( 7)
  #define PCU_CR_SA_PERF_STATUS_PCU_QCLK_REFERENCE_WID                 ( 1)
  #define PCU_CR_SA_PERF_STATUS_PCU_QCLK_REFERENCE_MSK                 (0x00000080)
  #define PCU_CR_SA_PERF_STATUS_PCU_QCLK_REFERENCE_MIN                 (0)
  #define PCU_CR_SA_PERF_STATUS_PCU_QCLK_REFERENCE_MAX                 (1) // 0x00000001
  #define PCU_CR_SA_PERF_STATUS_PCU_QCLK_REFERENCE_DEF                 (0x00000000)
  #define PCU_CR_SA_PERF_STATUS_PCU_QCLK_REFERENCE_HSH                 (0x0107594C)

  #define PCU_CR_SA_PERF_STATUS_PCU_FCLK_RATIO_OFF                     ( 8)
  #define PCU_CR_SA_PERF_STATUS_PCU_FCLK_RATIO_WID                     ( 8)
  #define PCU_CR_SA_PERF_STATUS_PCU_FCLK_RATIO_MSK                     (0x0000FF00)
  #define PCU_CR_SA_PERF_STATUS_PCU_FCLK_RATIO_MIN                     (0)
  #define PCU_CR_SA_PERF_STATUS_PCU_FCLK_RATIO_MAX                     (255) // 0x000000FF
  #define PCU_CR_SA_PERF_STATUS_PCU_FCLK_RATIO_DEF                     (0x00000000)
  #define PCU_CR_SA_PERF_STATUS_PCU_FCLK_RATIO_HSH                     (0x0808594C)

  #define PCU_CR_SA_PERF_STATUS_PCU_ICLK_RATIO_OFF                     (16)
  #define PCU_CR_SA_PERF_STATUS_PCU_ICLK_RATIO_WID                     ( 8)
  #define PCU_CR_SA_PERF_STATUS_PCU_ICLK_RATIO_MSK                     (0x00FF0000)
  #define PCU_CR_SA_PERF_STATUS_PCU_ICLK_RATIO_MIN                     (0)
  #define PCU_CR_SA_PERF_STATUS_PCU_ICLK_RATIO_MAX                     (255) // 0x000000FF
  #define PCU_CR_SA_PERF_STATUS_PCU_ICLK_RATIO_DEF                     (0x00000000)
  #define PCU_CR_SA_PERF_STATUS_PCU_ICLK_RATIO_HSH                     (0x0810594C)

  #define PCU_CR_SA_PERF_STATUS_PCU_UCLK_RATIO_OFF                     (24)
  #define PCU_CR_SA_PERF_STATUS_PCU_UCLK_RATIO_WID                     ( 8)
  #define PCU_CR_SA_PERF_STATUS_PCU_UCLK_RATIO_MSK                     (0xFF000000)
  #define PCU_CR_SA_PERF_STATUS_PCU_UCLK_RATIO_MIN                     (0)
  #define PCU_CR_SA_PERF_STATUS_PCU_UCLK_RATIO_MAX                     (255) // 0x000000FF
  #define PCU_CR_SA_PERF_STATUS_PCU_UCLK_RATIO_DEF                     (0x00000000)
  #define PCU_CR_SA_PERF_STATUS_PCU_UCLK_RATIO_HSH                     (0x0818594C)

#define PCU_CR_PLATFORM_ID_PCU_REG                                     (0x00005950)

  #define PCU_CR_PLATFORM_ID_PCU_PLATFORMID_OFF                        (50)
  #define PCU_CR_PLATFORM_ID_PCU_PLATFORMID_WID                        ( 3)
  #define PCU_CR_PLATFORM_ID_PCU_PLATFORMID_MSK                        (0x001C000000000000ULL)
  #define PCU_CR_PLATFORM_ID_PCU_PLATFORMID_MIN                        (0)
  #define PCU_CR_PLATFORM_ID_PCU_PLATFORMID_MAX                        (7) // 0x00000007
  #define PCU_CR_PLATFORM_ID_PCU_PLATFORMID_DEF                        (0x00000000)
  #define PCU_CR_PLATFORM_ID_PCU_PLATFORMID_HSH                        (0x43325950)

#define PCU_CR_PLATFORM_INFO_PCU_REG                                   (0x00005958)

  #define PCU_CR_PLATFORM_INFO_PCU_MAX_NON_TURBO_LIM_RATIO_OFF         ( 8)
  #define PCU_CR_PLATFORM_INFO_PCU_MAX_NON_TURBO_LIM_RATIO_WID         ( 8)
  #define PCU_CR_PLATFORM_INFO_PCU_MAX_NON_TURBO_LIM_RATIO_MSK         (0x0000FF00)
  #define PCU_CR_PLATFORM_INFO_PCU_MAX_NON_TURBO_LIM_RATIO_MIN         (0)
  #define PCU_CR_PLATFORM_INFO_PCU_MAX_NON_TURBO_LIM_RATIO_MAX         (255) // 0x000000FF
  #define PCU_CR_PLATFORM_INFO_PCU_MAX_NON_TURBO_LIM_RATIO_DEF         (0x00000000)
  #define PCU_CR_PLATFORM_INFO_PCU_MAX_NON_TURBO_LIM_RATIO_HSH         (0x48085958)

  #define PCU_CR_PLATFORM_INFO_PCU_SMM_SAVE_CAP_OFF                    (16)
  #define PCU_CR_PLATFORM_INFO_PCU_SMM_SAVE_CAP_WID                    ( 1)
  #define PCU_CR_PLATFORM_INFO_PCU_SMM_SAVE_CAP_MSK                    (0x00010000)
  #define PCU_CR_PLATFORM_INFO_PCU_SMM_SAVE_CAP_MIN                    (0)
  #define PCU_CR_PLATFORM_INFO_PCU_SMM_SAVE_CAP_MAX                    (1) // 0x00000001
  #define PCU_CR_PLATFORM_INFO_PCU_SMM_SAVE_CAP_DEF                    (0x00000001)
  #define PCU_CR_PLATFORM_INFO_PCU_SMM_SAVE_CAP_HSH                    (0x41105958)

  #define PCU_CR_PLATFORM_INFO_PCU_OCVOLT_OVRD_AVAIL_OFF               (24)
  #define PCU_CR_PLATFORM_INFO_PCU_OCVOLT_OVRD_AVAIL_WID               ( 1)
  #define PCU_CR_PLATFORM_INFO_PCU_OCVOLT_OVRD_AVAIL_MSK               (0x01000000)
  #define PCU_CR_PLATFORM_INFO_PCU_OCVOLT_OVRD_AVAIL_MIN               (0)
  #define PCU_CR_PLATFORM_INFO_PCU_OCVOLT_OVRD_AVAIL_MAX               (1) // 0x00000001
  #define PCU_CR_PLATFORM_INFO_PCU_OCVOLT_OVRD_AVAIL_DEF               (0x00000000)
  #define PCU_CR_PLATFORM_INFO_PCU_OCVOLT_OVRD_AVAIL_HSH               (0x41185958)

  #define PCU_CR_PLATFORM_INFO_PCU_DCU_16K_MODE_AVAIL_OFF              (26)
  #define PCU_CR_PLATFORM_INFO_PCU_DCU_16K_MODE_AVAIL_WID              ( 1)
  #define PCU_CR_PLATFORM_INFO_PCU_DCU_16K_MODE_AVAIL_MSK              (0x04000000)
  #define PCU_CR_PLATFORM_INFO_PCU_DCU_16K_MODE_AVAIL_MIN              (0)
  #define PCU_CR_PLATFORM_INFO_PCU_DCU_16K_MODE_AVAIL_MAX              (1) // 0x00000001
  #define PCU_CR_PLATFORM_INFO_PCU_DCU_16K_MODE_AVAIL_DEF              (0x00000000)
  #define PCU_CR_PLATFORM_INFO_PCU_DCU_16K_MODE_AVAIL_HSH              (0x411A5958)

  #define PCU_CR_PLATFORM_INFO_PCU_SAMPLE_PART_OFF                     (27)
  #define PCU_CR_PLATFORM_INFO_PCU_SAMPLE_PART_WID                     ( 1)
  #define PCU_CR_PLATFORM_INFO_PCU_SAMPLE_PART_MSK                     (0x08000000)
  #define PCU_CR_PLATFORM_INFO_PCU_SAMPLE_PART_MIN                     (0)
  #define PCU_CR_PLATFORM_INFO_PCU_SAMPLE_PART_MAX                     (1) // 0x00000001
  #define PCU_CR_PLATFORM_INFO_PCU_SAMPLE_PART_DEF                     (0x00000000)
  #define PCU_CR_PLATFORM_INFO_PCU_SAMPLE_PART_HSH                     (0x411B5958)

  #define PCU_CR_PLATFORM_INFO_PCU_PRG_TURBO_RATIO_EN_OFF              (28)
  #define PCU_CR_PLATFORM_INFO_PCU_PRG_TURBO_RATIO_EN_WID              ( 1)
  #define PCU_CR_PLATFORM_INFO_PCU_PRG_TURBO_RATIO_EN_MSK              (0x10000000)
  #define PCU_CR_PLATFORM_INFO_PCU_PRG_TURBO_RATIO_EN_MIN              (0)
  #define PCU_CR_PLATFORM_INFO_PCU_PRG_TURBO_RATIO_EN_MAX              (1) // 0x00000001
  #define PCU_CR_PLATFORM_INFO_PCU_PRG_TURBO_RATIO_EN_DEF              (0x00000001)
  #define PCU_CR_PLATFORM_INFO_PCU_PRG_TURBO_RATIO_EN_HSH              (0x411C5958)

  #define PCU_CR_PLATFORM_INFO_PCU_PRG_TDP_LIM_EN_OFF                  (29)
  #define PCU_CR_PLATFORM_INFO_PCU_PRG_TDP_LIM_EN_WID                  ( 1)
  #define PCU_CR_PLATFORM_INFO_PCU_PRG_TDP_LIM_EN_MSK                  (0x20000000)
  #define PCU_CR_PLATFORM_INFO_PCU_PRG_TDP_LIM_EN_MIN                  (0)
  #define PCU_CR_PLATFORM_INFO_PCU_PRG_TDP_LIM_EN_MAX                  (1) // 0x00000001
  #define PCU_CR_PLATFORM_INFO_PCU_PRG_TDP_LIM_EN_DEF                  (0x00000001)
  #define PCU_CR_PLATFORM_INFO_PCU_PRG_TDP_LIM_EN_HSH                  (0x411D5958)

  #define PCU_CR_PLATFORM_INFO_PCU_PRG_TJ_OFFSET_EN_OFF                (30)
  #define PCU_CR_PLATFORM_INFO_PCU_PRG_TJ_OFFSET_EN_WID                ( 1)
  #define PCU_CR_PLATFORM_INFO_PCU_PRG_TJ_OFFSET_EN_MSK                (0x40000000)
  #define PCU_CR_PLATFORM_INFO_PCU_PRG_TJ_OFFSET_EN_MIN                (0)
  #define PCU_CR_PLATFORM_INFO_PCU_PRG_TJ_OFFSET_EN_MAX                (1) // 0x00000001
  #define PCU_CR_PLATFORM_INFO_PCU_PRG_TJ_OFFSET_EN_DEF                (0x00000001)
  #define PCU_CR_PLATFORM_INFO_PCU_PRG_TJ_OFFSET_EN_HSH                (0x411E5958)

  #define PCU_CR_PLATFORM_INFO_PCU_CPUID_FAULTING_EN_OFF               (31)
  #define PCU_CR_PLATFORM_INFO_PCU_CPUID_FAULTING_EN_WID               ( 1)
  #define PCU_CR_PLATFORM_INFO_PCU_CPUID_FAULTING_EN_MSK               (0x80000000)
  #define PCU_CR_PLATFORM_INFO_PCU_CPUID_FAULTING_EN_MIN               (0)
  #define PCU_CR_PLATFORM_INFO_PCU_CPUID_FAULTING_EN_MAX               (1) // 0x00000001
  #define PCU_CR_PLATFORM_INFO_PCU_CPUID_FAULTING_EN_DEF               (0x00000001)
  #define PCU_CR_PLATFORM_INFO_PCU_CPUID_FAULTING_EN_HSH               (0x411F5958)

  #define PCU_CR_PLATFORM_INFO_PCU_LPM_SUPPORT_OFF                     (32)
  #define PCU_CR_PLATFORM_INFO_PCU_LPM_SUPPORT_WID                     ( 1)
  #define PCU_CR_PLATFORM_INFO_PCU_LPM_SUPPORT_MSK                     (0x0000000100000000ULL)
  #define PCU_CR_PLATFORM_INFO_PCU_LPM_SUPPORT_MIN                     (0)
  #define PCU_CR_PLATFORM_INFO_PCU_LPM_SUPPORT_MAX                     (1) // 0x00000001
  #define PCU_CR_PLATFORM_INFO_PCU_LPM_SUPPORT_DEF                     (0x00000000)
  #define PCU_CR_PLATFORM_INFO_PCU_LPM_SUPPORT_HSH                     (0x41205958)

  #define PCU_CR_PLATFORM_INFO_PCU_CONFIG_TDP_LEVELS_OFF               (33)
  #define PCU_CR_PLATFORM_INFO_PCU_CONFIG_TDP_LEVELS_WID               ( 2)
  #define PCU_CR_PLATFORM_INFO_PCU_CONFIG_TDP_LEVELS_MSK               (0x0000000600000000ULL)
  #define PCU_CR_PLATFORM_INFO_PCU_CONFIG_TDP_LEVELS_MIN               (0)
  #define PCU_CR_PLATFORM_INFO_PCU_CONFIG_TDP_LEVELS_MAX               (3) // 0x00000003
  #define PCU_CR_PLATFORM_INFO_PCU_CONFIG_TDP_LEVELS_DEF               (0x00000000)
  #define PCU_CR_PLATFORM_INFO_PCU_CONFIG_TDP_LEVELS_HSH               (0x42215958)

  #define PCU_CR_PLATFORM_INFO_PCU_PFAT_ENABLE_OFF                     (35)
  #define PCU_CR_PLATFORM_INFO_PCU_PFAT_ENABLE_WID                     ( 1)
  #define PCU_CR_PLATFORM_INFO_PCU_PFAT_ENABLE_MSK                     (0x0000000800000000ULL)
  #define PCU_CR_PLATFORM_INFO_PCU_PFAT_ENABLE_MIN                     (0)
  #define PCU_CR_PLATFORM_INFO_PCU_PFAT_ENABLE_MAX                     (1) // 0x00000001
  #define PCU_CR_PLATFORM_INFO_PCU_PFAT_ENABLE_DEF                     (0x00000000)
  #define PCU_CR_PLATFORM_INFO_PCU_PFAT_ENABLE_HSH                     (0x41235958)

  #define PCU_CR_PLATFORM_INFO_PCU_PEG2DMIDIS_EN_OFF                   (36)
  #define PCU_CR_PLATFORM_INFO_PCU_PEG2DMIDIS_EN_WID                   ( 1)
  #define PCU_CR_PLATFORM_INFO_PCU_PEG2DMIDIS_EN_MSK                   (0x0000001000000000ULL)
  #define PCU_CR_PLATFORM_INFO_PCU_PEG2DMIDIS_EN_MIN                   (0)
  #define PCU_CR_PLATFORM_INFO_PCU_PEG2DMIDIS_EN_MAX                   (1) // 0x00000001
  #define PCU_CR_PLATFORM_INFO_PCU_PEG2DMIDIS_EN_DEF                   (0x00000001)
  #define PCU_CR_PLATFORM_INFO_PCU_PEG2DMIDIS_EN_HSH                   (0x41245958)

  #define PCU_CR_PLATFORM_INFO_PCU_TIMED_MWAIT_ENABLE_OFF              (37)
  #define PCU_CR_PLATFORM_INFO_PCU_TIMED_MWAIT_ENABLE_WID              ( 1)
  #define PCU_CR_PLATFORM_INFO_PCU_TIMED_MWAIT_ENABLE_MSK              (0x0000002000000000ULL)
  #define PCU_CR_PLATFORM_INFO_PCU_TIMED_MWAIT_ENABLE_MIN              (0)
  #define PCU_CR_PLATFORM_INFO_PCU_TIMED_MWAIT_ENABLE_MAX              (1) // 0x00000001
  #define PCU_CR_PLATFORM_INFO_PCU_TIMED_MWAIT_ENABLE_DEF              (0x00000000)
  #define PCU_CR_PLATFORM_INFO_PCU_TIMED_MWAIT_ENABLE_HSH              (0x41255958)

  #define PCU_CR_PLATFORM_INFO_PCU_MAX_EFFICIENCY_RATIO_OFF            (40)
  #define PCU_CR_PLATFORM_INFO_PCU_MAX_EFFICIENCY_RATIO_WID            ( 8)
  #define PCU_CR_PLATFORM_INFO_PCU_MAX_EFFICIENCY_RATIO_MSK            (0x0000FF0000000000ULL)
  #define PCU_CR_PLATFORM_INFO_PCU_MAX_EFFICIENCY_RATIO_MIN            (0)
  #define PCU_CR_PLATFORM_INFO_PCU_MAX_EFFICIENCY_RATIO_MAX            (255) // 0x000000FF
  #define PCU_CR_PLATFORM_INFO_PCU_MAX_EFFICIENCY_RATIO_DEF            (0x00000000)
  #define PCU_CR_PLATFORM_INFO_PCU_MAX_EFFICIENCY_RATIO_HSH            (0x48285958)

  #define PCU_CR_PLATFORM_INFO_PCU_MIN_OPERATING_RATIO_OFF             (48)
  #define PCU_CR_PLATFORM_INFO_PCU_MIN_OPERATING_RATIO_WID             ( 8)
  #define PCU_CR_PLATFORM_INFO_PCU_MIN_OPERATING_RATIO_MSK             (0x00FF000000000000ULL)
  #define PCU_CR_PLATFORM_INFO_PCU_MIN_OPERATING_RATIO_MIN             (0)
  #define PCU_CR_PLATFORM_INFO_PCU_MIN_OPERATING_RATIO_MAX             (255) // 0x000000FF
  #define PCU_CR_PLATFORM_INFO_PCU_MIN_OPERATING_RATIO_DEF             (0x00000008)
  #define PCU_CR_PLATFORM_INFO_PCU_MIN_OPERATING_RATIO_HSH             (0x48305958)

  #define PCU_CR_PLATFORM_INFO_PCU_PushPatch_EN_OFF                    (56)
  #define PCU_CR_PLATFORM_INFO_PCU_PushPatch_EN_WID                    ( 1)
  #define PCU_CR_PLATFORM_INFO_PCU_PushPatch_EN_MSK                    (0x0100000000000000ULL)
  #define PCU_CR_PLATFORM_INFO_PCU_PushPatch_EN_MIN                    (0)
  #define PCU_CR_PLATFORM_INFO_PCU_PushPatch_EN_MAX                    (1) // 0x00000001
  #define PCU_CR_PLATFORM_INFO_PCU_PushPatch_EN_DEF                    (0x00000000)
  #define PCU_CR_PLATFORM_INFO_PCU_PushPatch_EN_HSH                    (0x41385958)

#define PCU_CR_PP1_C0_CORE_CLOCK_PCU_REG                               (0x00005960)

  #define PCU_CR_PP1_C0_CORE_CLOCK_PCU_DATA_OFF                        ( 0)
  #define PCU_CR_PP1_C0_CORE_CLOCK_PCU_DATA_WID                        (32)
  #define PCU_CR_PP1_C0_CORE_CLOCK_PCU_DATA_MSK                        (0xFFFFFFFF)
  #define PCU_CR_PP1_C0_CORE_CLOCK_PCU_DATA_MIN                        (0)
  #define PCU_CR_PP1_C0_CORE_CLOCK_PCU_DATA_MAX                        (4294967295) // 0xFFFFFFFF
  #define PCU_CR_PP1_C0_CORE_CLOCK_PCU_DATA_DEF                        (0x00000000)
  #define PCU_CR_PP1_C0_CORE_CLOCK_PCU_DATA_HSH                        (0x20005960)

#define PCU_CR_PP0_EFFICIENT_CYCLES_PCU_REG                            (0x00005968)

  #define PCU_CR_PP0_EFFICIENT_CYCLES_PCU_DATA_OFF                     ( 0)
  #define PCU_CR_PP0_EFFICIENT_CYCLES_PCU_DATA_WID                     (32)
  #define PCU_CR_PP0_EFFICIENT_CYCLES_PCU_DATA_MSK                     (0xFFFFFFFF)
  #define PCU_CR_PP0_EFFICIENT_CYCLES_PCU_DATA_MIN                     (0)
  #define PCU_CR_PP0_EFFICIENT_CYCLES_PCU_DATA_MAX                     (4294967295) // 0xFFFFFFFF
  #define PCU_CR_PP0_EFFICIENT_CYCLES_PCU_DATA_DEF                     (0x00000000)
  #define PCU_CR_PP0_EFFICIENT_CYCLES_PCU_DATA_HSH                     (0x20005968)

#define PCU_CR_PP0_THREAD_ACTIVITY_PCU_REG                             (0x0000596C)

  #define PCU_CR_PP0_THREAD_ACTIVITY_PCU_DATA_OFF                      ( 0)
  #define PCU_CR_PP0_THREAD_ACTIVITY_PCU_DATA_WID                      (32)
  #define PCU_CR_PP0_THREAD_ACTIVITY_PCU_DATA_MSK                      (0xFFFFFFFF)
  #define PCU_CR_PP0_THREAD_ACTIVITY_PCU_DATA_MIN                      (0)
  #define PCU_CR_PP0_THREAD_ACTIVITY_PCU_DATA_MAX                      (4294967295) // 0xFFFFFFFF
  #define PCU_CR_PP0_THREAD_ACTIVITY_PCU_DATA_DEF                      (0x00000000)
  #define PCU_CR_PP0_THREAD_ACTIVITY_PCU_DATA_HSH                      (0x2000596C)

#define PCU_CR_PP1_EFFICIENT_CYCLES_PCU_REG                            (0x00005974)

  #define PCU_CR_PP1_EFFICIENT_CYCLES_PCU_DATA_OFF                     ( 0)
  #define PCU_CR_PP1_EFFICIENT_CYCLES_PCU_DATA_WID                     (32)
  #define PCU_CR_PP1_EFFICIENT_CYCLES_PCU_DATA_MSK                     (0xFFFFFFFF)
  #define PCU_CR_PP1_EFFICIENT_CYCLES_PCU_DATA_MIN                     (0)
  #define PCU_CR_PP1_EFFICIENT_CYCLES_PCU_DATA_MAX                     (4294967295) // 0xFFFFFFFF
  #define PCU_CR_PP1_EFFICIENT_CYCLES_PCU_DATA_DEF                     (0x00000000)
  #define PCU_CR_PP1_EFFICIENT_CYCLES_PCU_DATA_HSH                     (0x20005974)

#define PCU_CR_PACKAGE_TEMPERATURE_PCU_REG                             (0x00005978)

  #define PCU_CR_PACKAGE_TEMPERATURE_PCU_DATA_OFF                      ( 0)
  #define PCU_CR_PACKAGE_TEMPERATURE_PCU_DATA_WID                      ( 8)
  #define PCU_CR_PACKAGE_TEMPERATURE_PCU_DATA_MSK                      (0x000000FF)
  #define PCU_CR_PACKAGE_TEMPERATURE_PCU_DATA_MIN                      (0)
  #define PCU_CR_PACKAGE_TEMPERATURE_PCU_DATA_MAX                      (255) // 0x000000FF
  #define PCU_CR_PACKAGE_TEMPERATURE_PCU_DATA_DEF                      (0x00000000)
  #define PCU_CR_PACKAGE_TEMPERATURE_PCU_DATA_HSH                      (0x08005978)

#define PCU_CR_PP0_TEMPERATURE_PCU_REG                                 (0x0000597C)

  #define PCU_CR_PP0_TEMPERATURE_PCU_DATA_OFF                          ( 0)
  #define PCU_CR_PP0_TEMPERATURE_PCU_DATA_WID                          ( 8)
  #define PCU_CR_PP0_TEMPERATURE_PCU_DATA_MSK                          (0x000000FF)
  #define PCU_CR_PP0_TEMPERATURE_PCU_DATA_MIN                          (0)
  #define PCU_CR_PP0_TEMPERATURE_PCU_DATA_MAX                          (255) // 0x000000FF
  #define PCU_CR_PP0_TEMPERATURE_PCU_DATA_DEF                          (0x00000000)
  #define PCU_CR_PP0_TEMPERATURE_PCU_DATA_HSH                          (0x0800597C)

#define PCU_CR_PP1_TEMPERATURE_PCU_REG                                 (0x00005980)

  #define PCU_CR_PP1_TEMPERATURE_PCU_DATA_OFF                          ( 0)
  #define PCU_CR_PP1_TEMPERATURE_PCU_DATA_WID                          ( 8)
  #define PCU_CR_PP1_TEMPERATURE_PCU_DATA_MSK                          (0x000000FF)
  #define PCU_CR_PP1_TEMPERATURE_PCU_DATA_MIN                          (0)
  #define PCU_CR_PP1_TEMPERATURE_PCU_DATA_MAX                          (255) // 0x000000FF
  #define PCU_CR_PP1_TEMPERATURE_PCU_DATA_DEF                          (0x00000000)
  #define PCU_CR_PP1_TEMPERATURE_PCU_DATA_HSH                          (0x08005980)

#define PCU_CR_PCU_REFERENCE_CLOCK_PCU_REG                             (0x00005984)

  #define PCU_CR_PCU_REFERENCE_CLOCK_PCU_TIME_VAL_OFF                  ( 0)
  #define PCU_CR_PCU_REFERENCE_CLOCK_PCU_TIME_VAL_WID                  (32)
  #define PCU_CR_PCU_REFERENCE_CLOCK_PCU_TIME_VAL_MSK                  (0xFFFFFFFF)
  #define PCU_CR_PCU_REFERENCE_CLOCK_PCU_TIME_VAL_MIN                  (0)
  #define PCU_CR_PCU_REFERENCE_CLOCK_PCU_TIME_VAL_MAX                  (4294967295) // 0xFFFFFFFF
  #define PCU_CR_PCU_REFERENCE_CLOCK_PCU_TIME_VAL_DEF                  (0x00000000)
  #define PCU_CR_PCU_REFERENCE_CLOCK_PCU_TIME_VAL_HSH                  (0x20005984)

#define PCU_CR_DEVICE_SHARED_IDLE_DURATION_PCU_REG                     (0x00005988)

  #define PCU_CR_DEVICE_SHARED_IDLE_DURATION_PCU_RESERVED_OFF          ( 0)
  #define PCU_CR_DEVICE_SHARED_IDLE_DURATION_PCU_RESERVED_WID          ( 1)
  #define PCU_CR_DEVICE_SHARED_IDLE_DURATION_PCU_RESERVED_MSK          (0x00000001)
  #define PCU_CR_DEVICE_SHARED_IDLE_DURATION_PCU_RESERVED_MIN          (0)
  #define PCU_CR_DEVICE_SHARED_IDLE_DURATION_PCU_RESERVED_MAX          (1) // 0x00000001
  #define PCU_CR_DEVICE_SHARED_IDLE_DURATION_PCU_RESERVED_DEF          (0x00000000)
  #define PCU_CR_DEVICE_SHARED_IDLE_DURATION_PCU_RESERVED_HSH          (0x01005988)

  #define PCU_CR_DEVICE_SHARED_IDLE_DURATION_PCU_VALID_OFF             ( 1)
  #define PCU_CR_DEVICE_SHARED_IDLE_DURATION_PCU_VALID_WID             ( 1)
  #define PCU_CR_DEVICE_SHARED_IDLE_DURATION_PCU_VALID_MSK             (0x00000002)
  #define PCU_CR_DEVICE_SHARED_IDLE_DURATION_PCU_VALID_MIN             (0)
  #define PCU_CR_DEVICE_SHARED_IDLE_DURATION_PCU_VALID_MAX             (1) // 0x00000001
  #define PCU_CR_DEVICE_SHARED_IDLE_DURATION_PCU_VALID_DEF             (0x00000000)
  #define PCU_CR_DEVICE_SHARED_IDLE_DURATION_PCU_VALID_HSH             (0x01015988)

  #define PCU_CR_DEVICE_SHARED_IDLE_DURATION_PCU_RESERVED_BITS_OFF     ( 2)
  #define PCU_CR_DEVICE_SHARED_IDLE_DURATION_PCU_RESERVED_BITS_WID     ( 4)
  #define PCU_CR_DEVICE_SHARED_IDLE_DURATION_PCU_RESERVED_BITS_MSK     (0x0000003C)
  #define PCU_CR_DEVICE_SHARED_IDLE_DURATION_PCU_RESERVED_BITS_MIN     (0)
  #define PCU_CR_DEVICE_SHARED_IDLE_DURATION_PCU_RESERVED_BITS_MAX     (15) // 0x0000000F
  #define PCU_CR_DEVICE_SHARED_IDLE_DURATION_PCU_RESERVED_BITS_DEF     (0x00000000)
  #define PCU_CR_DEVICE_SHARED_IDLE_DURATION_PCU_RESERVED_BITS_HSH     (0x04025988)

  #define PCU_CR_DEVICE_SHARED_IDLE_DURATION_PCU_OD_OFF                ( 6)
  #define PCU_CR_DEVICE_SHARED_IDLE_DURATION_PCU_OD_WID                ( 1)
  #define PCU_CR_DEVICE_SHARED_IDLE_DURATION_PCU_OD_MSK                (0x00000040)
  #define PCU_CR_DEVICE_SHARED_IDLE_DURATION_PCU_OD_MIN                (0)
  #define PCU_CR_DEVICE_SHARED_IDLE_DURATION_PCU_OD_MAX                (1) // 0x00000001
  #define PCU_CR_DEVICE_SHARED_IDLE_DURATION_PCU_OD_DEF                (0x00000000)
  #define PCU_CR_DEVICE_SHARED_IDLE_DURATION_PCU_OD_HSH                (0x01065988)

  #define PCU_CR_DEVICE_SHARED_IDLE_DURATION_PCU_IM_OFF                ( 7)
  #define PCU_CR_DEVICE_SHARED_IDLE_DURATION_PCU_IM_WID                ( 1)
  #define PCU_CR_DEVICE_SHARED_IDLE_DURATION_PCU_IM_MSK                (0x00000080)
  #define PCU_CR_DEVICE_SHARED_IDLE_DURATION_PCU_IM_MIN                (0)
  #define PCU_CR_DEVICE_SHARED_IDLE_DURATION_PCU_IM_MAX                (1) // 0x00000001
  #define PCU_CR_DEVICE_SHARED_IDLE_DURATION_PCU_IM_DEF                (0x00000000)
  #define PCU_CR_DEVICE_SHARED_IDLE_DURATION_PCU_IM_HSH                (0x01075988)

  #define PCU_CR_DEVICE_SHARED_IDLE_DURATION_PCU_NEXT_DEVICE_ACTIVITY_OFF ( 8)
  #define PCU_CR_DEVICE_SHARED_IDLE_DURATION_PCU_NEXT_DEVICE_ACTIVITY_WID (21)
  #define PCU_CR_DEVICE_SHARED_IDLE_DURATION_PCU_NEXT_DEVICE_ACTIVITY_MSK (0x1FFFFF00)
  #define PCU_CR_DEVICE_SHARED_IDLE_DURATION_PCU_NEXT_DEVICE_ACTIVITY_MIN (0)
  #define PCU_CR_DEVICE_SHARED_IDLE_DURATION_PCU_NEXT_DEVICE_ACTIVITY_MAX (2097151) // 0x001FFFFF
  #define PCU_CR_DEVICE_SHARED_IDLE_DURATION_PCU_NEXT_DEVICE_ACTIVITY_DEF (0x00000000)
  #define PCU_CR_DEVICE_SHARED_IDLE_DURATION_PCU_NEXT_DEVICE_ACTIVITY_HSH (0x15085988)

#define PCU_CR_DEVICE_DEDICATED_IDLE_DURATION_PCU_REG                  (0x0000598C)

  #define PCU_CR_DEVICE_DEDICATED_IDLE_DURATION_PCU_USED_OFF           ( 0)
  #define PCU_CR_DEVICE_DEDICATED_IDLE_DURATION_PCU_USED_WID           ( 1)
  #define PCU_CR_DEVICE_DEDICATED_IDLE_DURATION_PCU_USED_MSK           (0x00000001)
  #define PCU_CR_DEVICE_DEDICATED_IDLE_DURATION_PCU_USED_MIN           (0)
  #define PCU_CR_DEVICE_DEDICATED_IDLE_DURATION_PCU_USED_MAX           (1) // 0x00000001
  #define PCU_CR_DEVICE_DEDICATED_IDLE_DURATION_PCU_USED_DEF           (0x00000000)
  #define PCU_CR_DEVICE_DEDICATED_IDLE_DURATION_PCU_USED_HSH           (0x0100598C)

  #define PCU_CR_DEVICE_DEDICATED_IDLE_DURATION_PCU_VALID_OFF          ( 1)
  #define PCU_CR_DEVICE_DEDICATED_IDLE_DURATION_PCU_VALID_WID          ( 1)
  #define PCU_CR_DEVICE_DEDICATED_IDLE_DURATION_PCU_VALID_MSK          (0x00000002)
  #define PCU_CR_DEVICE_DEDICATED_IDLE_DURATION_PCU_VALID_MIN          (0)
  #define PCU_CR_DEVICE_DEDICATED_IDLE_DURATION_PCU_VALID_MAX          (1) // 0x00000001
  #define PCU_CR_DEVICE_DEDICATED_IDLE_DURATION_PCU_VALID_DEF          (0x00000000)
  #define PCU_CR_DEVICE_DEDICATED_IDLE_DURATION_PCU_VALID_HSH          (0x0101598C)

  #define PCU_CR_DEVICE_DEDICATED_IDLE_DURATION_PCU_RESERVED_BITS_OFF  ( 2)
  #define PCU_CR_DEVICE_DEDICATED_IDLE_DURATION_PCU_RESERVED_BITS_WID  ( 4)
  #define PCU_CR_DEVICE_DEDICATED_IDLE_DURATION_PCU_RESERVED_BITS_MSK  (0x0000003C)
  #define PCU_CR_DEVICE_DEDICATED_IDLE_DURATION_PCU_RESERVED_BITS_MIN  (0)
  #define PCU_CR_DEVICE_DEDICATED_IDLE_DURATION_PCU_RESERVED_BITS_MAX  (15) // 0x0000000F
  #define PCU_CR_DEVICE_DEDICATED_IDLE_DURATION_PCU_RESERVED_BITS_DEF  (0x00000000)
  #define PCU_CR_DEVICE_DEDICATED_IDLE_DURATION_PCU_RESERVED_BITS_HSH  (0x0402598C)

  #define PCU_CR_DEVICE_DEDICATED_IDLE_DURATION_PCU_OD_OFF             ( 6)
  #define PCU_CR_DEVICE_DEDICATED_IDLE_DURATION_PCU_OD_WID             ( 1)
  #define PCU_CR_DEVICE_DEDICATED_IDLE_DURATION_PCU_OD_MSK             (0x00000040)
  #define PCU_CR_DEVICE_DEDICATED_IDLE_DURATION_PCU_OD_MIN             (0)
  #define PCU_CR_DEVICE_DEDICATED_IDLE_DURATION_PCU_OD_MAX             (1) // 0x00000001
  #define PCU_CR_DEVICE_DEDICATED_IDLE_DURATION_PCU_OD_DEF             (0x00000000)
  #define PCU_CR_DEVICE_DEDICATED_IDLE_DURATION_PCU_OD_HSH             (0x0106598C)

  #define PCU_CR_DEVICE_DEDICATED_IDLE_DURATION_PCU_IM_OFF             ( 7)
  #define PCU_CR_DEVICE_DEDICATED_IDLE_DURATION_PCU_IM_WID             ( 1)
  #define PCU_CR_DEVICE_DEDICATED_IDLE_DURATION_PCU_IM_MSK             (0x00000080)
  #define PCU_CR_DEVICE_DEDICATED_IDLE_DURATION_PCU_IM_MIN             (0)
  #define PCU_CR_DEVICE_DEDICATED_IDLE_DURATION_PCU_IM_MAX             (1) // 0x00000001
  #define PCU_CR_DEVICE_DEDICATED_IDLE_DURATION_PCU_IM_DEF             (0x00000000)
  #define PCU_CR_DEVICE_DEDICATED_IDLE_DURATION_PCU_IM_HSH             (0x0107598C)

  #define PCU_CR_DEVICE_DEDICATED_IDLE_DURATION_PCU_NEXT_DEVICE_ACTIVITY_OFF ( 8)
  #define PCU_CR_DEVICE_DEDICATED_IDLE_DURATION_PCU_NEXT_DEVICE_ACTIVITY_WID (21)
  #define PCU_CR_DEVICE_DEDICATED_IDLE_DURATION_PCU_NEXT_DEVICE_ACTIVITY_MSK (0x1FFFFF00)
  #define PCU_CR_DEVICE_DEDICATED_IDLE_DURATION_PCU_NEXT_DEVICE_ACTIVITY_MIN (0)
  #define PCU_CR_DEVICE_DEDICATED_IDLE_DURATION_PCU_NEXT_DEVICE_ACTIVITY_MAX (2097151) // 0x001FFFFF
  #define PCU_CR_DEVICE_DEDICATED_IDLE_DURATION_PCU_NEXT_DEVICE_ACTIVITY_DEF (0x00000000)
  #define PCU_CR_DEVICE_DEDICATED_IDLE_DURATION_PCU_NEXT_DEVICE_ACTIVITY_HSH (0x1508598C)

#define PCU_CR_RP_STATE_LIMITS_PCU_REG                                 (0x00005994)

  #define PCU_CR_RP_STATE_LIMITS_PCU_RPSTT_LIM_OFF                     ( 0)
  #define PCU_CR_RP_STATE_LIMITS_PCU_RPSTT_LIM_WID                     ( 8)
  #define PCU_CR_RP_STATE_LIMITS_PCU_RPSTT_LIM_MSK                     (0x000000FF)
  #define PCU_CR_RP_STATE_LIMITS_PCU_RPSTT_LIM_MIN                     (0)
  #define PCU_CR_RP_STATE_LIMITS_PCU_RPSTT_LIM_MAX                     (255) // 0x000000FF
  #define PCU_CR_RP_STATE_LIMITS_PCU_RPSTT_LIM_DEF                     (0x000000FF)
  #define PCU_CR_RP_STATE_LIMITS_PCU_RPSTT_LIM_HSH                     (0x08005994)

#define PCU_CR_RP_STATE_CAP_PCU_REG                                    (0x00005998)

  #define PCU_CR_RP_STATE_CAP_PCU_RP0_CAP_OFF                          ( 0)
  #define PCU_CR_RP_STATE_CAP_PCU_RP0_CAP_WID                          ( 8)
  #define PCU_CR_RP_STATE_CAP_PCU_RP0_CAP_MSK                          (0x000000FF)
  #define PCU_CR_RP_STATE_CAP_PCU_RP0_CAP_MIN                          (0)
  #define PCU_CR_RP_STATE_CAP_PCU_RP0_CAP_MAX                          (255) // 0x000000FF
  #define PCU_CR_RP_STATE_CAP_PCU_RP0_CAP_DEF                          (0x00000000)
  #define PCU_CR_RP_STATE_CAP_PCU_RP0_CAP_HSH                          (0x08005998)

  #define PCU_CR_RP_STATE_CAP_PCU_RP1_CAP_OFF                          ( 8)
  #define PCU_CR_RP_STATE_CAP_PCU_RP1_CAP_WID                          ( 8)
  #define PCU_CR_RP_STATE_CAP_PCU_RP1_CAP_MSK                          (0x0000FF00)
  #define PCU_CR_RP_STATE_CAP_PCU_RP1_CAP_MIN                          (0)
  #define PCU_CR_RP_STATE_CAP_PCU_RP1_CAP_MAX                          (255) // 0x000000FF
  #define PCU_CR_RP_STATE_CAP_PCU_RP1_CAP_DEF                          (0x00000000)
  #define PCU_CR_RP_STATE_CAP_PCU_RP1_CAP_HSH                          (0x08085998)

  #define PCU_CR_RP_STATE_CAP_PCU_RPN_CAP_OFF                          (16)
  #define PCU_CR_RP_STATE_CAP_PCU_RPN_CAP_WID                          ( 8)
  #define PCU_CR_RP_STATE_CAP_PCU_RPN_CAP_MSK                          (0x00FF0000)
  #define PCU_CR_RP_STATE_CAP_PCU_RPN_CAP_MIN                          (0)
  #define PCU_CR_RP_STATE_CAP_PCU_RPN_CAP_MAX                          (255) // 0x000000FF
  #define PCU_CR_RP_STATE_CAP_PCU_RPN_CAP_DEF                          (0x00000000)
  #define PCU_CR_RP_STATE_CAP_PCU_RPN_CAP_HSH                          (0x08105998)

#define PCU_CR_TEMPERATURE_TARGET_PCU_REG                              (0x0000599C)

  #define PCU_CR_TEMPERATURE_TARGET_PCU_TCC_OFFSET_TIME_WINDOW_OFF     ( 0)
  #define PCU_CR_TEMPERATURE_TARGET_PCU_TCC_OFFSET_TIME_WINDOW_WID     ( 7)
  #define PCU_CR_TEMPERATURE_TARGET_PCU_TCC_OFFSET_TIME_WINDOW_MSK     (0x0000007F)
  #define PCU_CR_TEMPERATURE_TARGET_PCU_TCC_OFFSET_TIME_WINDOW_MIN     (0)
  #define PCU_CR_TEMPERATURE_TARGET_PCU_TCC_OFFSET_TIME_WINDOW_MAX     (127) // 0x0000007F
  #define PCU_CR_TEMPERATURE_TARGET_PCU_TCC_OFFSET_TIME_WINDOW_DEF     (0x00000000)
  #define PCU_CR_TEMPERATURE_TARGET_PCU_TCC_OFFSET_TIME_WINDOW_HSH     (0x0700599C)

  #define PCU_CR_TEMPERATURE_TARGET_PCU_TCC_OFFSET_CLAMPING_BIT_OFF    ( 7)
  #define PCU_CR_TEMPERATURE_TARGET_PCU_TCC_OFFSET_CLAMPING_BIT_WID    ( 1)
  #define PCU_CR_TEMPERATURE_TARGET_PCU_TCC_OFFSET_CLAMPING_BIT_MSK    (0x00000080)
  #define PCU_CR_TEMPERATURE_TARGET_PCU_TCC_OFFSET_CLAMPING_BIT_MIN    (0)
  #define PCU_CR_TEMPERATURE_TARGET_PCU_TCC_OFFSET_CLAMPING_BIT_MAX    (1) // 0x00000001
  #define PCU_CR_TEMPERATURE_TARGET_PCU_TCC_OFFSET_CLAMPING_BIT_DEF    (0x00000000)
  #define PCU_CR_TEMPERATURE_TARGET_PCU_TCC_OFFSET_CLAMPING_BIT_HSH    (0x0107599C)

  #define PCU_CR_TEMPERATURE_TARGET_PCU_FAN_TEMP_TARGET_OFST_OFF       ( 8)
  #define PCU_CR_TEMPERATURE_TARGET_PCU_FAN_TEMP_TARGET_OFST_WID       ( 8)
  #define PCU_CR_TEMPERATURE_TARGET_PCU_FAN_TEMP_TARGET_OFST_MSK       (0x0000FF00)
  #define PCU_CR_TEMPERATURE_TARGET_PCU_FAN_TEMP_TARGET_OFST_MIN       (0)
  #define PCU_CR_TEMPERATURE_TARGET_PCU_FAN_TEMP_TARGET_OFST_MAX       (255) // 0x000000FF
  #define PCU_CR_TEMPERATURE_TARGET_PCU_FAN_TEMP_TARGET_OFST_DEF       (0x00000000)
  #define PCU_CR_TEMPERATURE_TARGET_PCU_FAN_TEMP_TARGET_OFST_HSH       (0x0808599C)

  #define PCU_CR_TEMPERATURE_TARGET_PCU_REF_TEMP_OFF                   (16)
  #define PCU_CR_TEMPERATURE_TARGET_PCU_REF_TEMP_WID                   ( 8)
  #define PCU_CR_TEMPERATURE_TARGET_PCU_REF_TEMP_MSK                   (0x00FF0000)
  #define PCU_CR_TEMPERATURE_TARGET_PCU_REF_TEMP_MIN                   (0)
  #define PCU_CR_TEMPERATURE_TARGET_PCU_REF_TEMP_MAX                   (255) // 0x000000FF
  #define PCU_CR_TEMPERATURE_TARGET_PCU_REF_TEMP_DEF                   (0x00000000)
  #define PCU_CR_TEMPERATURE_TARGET_PCU_REF_TEMP_HSH                   (0x0810599C)

  #define PCU_CR_TEMPERATURE_TARGET_PCU_TJ_MAX_TCC_OFFSET_OFF          (24)
  #define PCU_CR_TEMPERATURE_TARGET_PCU_TJ_MAX_TCC_OFFSET_WID          ( 6)
  #define PCU_CR_TEMPERATURE_TARGET_PCU_TJ_MAX_TCC_OFFSET_MSK          (0x3F000000)
  #define PCU_CR_TEMPERATURE_TARGET_PCU_TJ_MAX_TCC_OFFSET_MIN          (0)
  #define PCU_CR_TEMPERATURE_TARGET_PCU_TJ_MAX_TCC_OFFSET_MAX          (63) // 0x0000003F
  #define PCU_CR_TEMPERATURE_TARGET_PCU_TJ_MAX_TCC_OFFSET_DEF          (0x00000000)
  #define PCU_CR_TEMPERATURE_TARGET_PCU_TJ_MAX_TCC_OFFSET_HSH          (0x0618599C)

#define PCU_CR_PACKAGE_RAPL_LIMIT_PCU_REG                              (0x000059A0)

  #define PCU_CR_PACKAGE_RAPL_LIMIT_PCU_PKG_PWR_LIM_1_OFF              ( 0)
  #define PCU_CR_PACKAGE_RAPL_LIMIT_PCU_PKG_PWR_LIM_1_WID              (15)
  #define PCU_CR_PACKAGE_RAPL_LIMIT_PCU_PKG_PWR_LIM_1_MSK              (0x00007FFF)
  #define PCU_CR_PACKAGE_RAPL_LIMIT_PCU_PKG_PWR_LIM_1_MIN              (0)
  #define PCU_CR_PACKAGE_RAPL_LIMIT_PCU_PKG_PWR_LIM_1_MAX              (32767) // 0x00007FFF
  #define PCU_CR_PACKAGE_RAPL_LIMIT_PCU_PKG_PWR_LIM_1_DEF              (0x00000000)
  #define PCU_CR_PACKAGE_RAPL_LIMIT_PCU_PKG_PWR_LIM_1_HSH              (0x4F0059A0)

  #define PCU_CR_PACKAGE_RAPL_LIMIT_PCU_PKG_PWR_LIM_1_EN_OFF           (15)
  #define PCU_CR_PACKAGE_RAPL_LIMIT_PCU_PKG_PWR_LIM_1_EN_WID           ( 1)
  #define PCU_CR_PACKAGE_RAPL_LIMIT_PCU_PKG_PWR_LIM_1_EN_MSK           (0x00008000)
  #define PCU_CR_PACKAGE_RAPL_LIMIT_PCU_PKG_PWR_LIM_1_EN_MIN           (0)
  #define PCU_CR_PACKAGE_RAPL_LIMIT_PCU_PKG_PWR_LIM_1_EN_MAX           (1) // 0x00000001
  #define PCU_CR_PACKAGE_RAPL_LIMIT_PCU_PKG_PWR_LIM_1_EN_DEF           (0x00000000)
  #define PCU_CR_PACKAGE_RAPL_LIMIT_PCU_PKG_PWR_LIM_1_EN_HSH           (0x410F59A0)

  #define PCU_CR_PACKAGE_RAPL_LIMIT_PCU_PKG_CLMP_LIM_1_OFF             (16)
  #define PCU_CR_PACKAGE_RAPL_LIMIT_PCU_PKG_CLMP_LIM_1_WID             ( 1)
  #define PCU_CR_PACKAGE_RAPL_LIMIT_PCU_PKG_CLMP_LIM_1_MSK             (0x00010000)
  #define PCU_CR_PACKAGE_RAPL_LIMIT_PCU_PKG_CLMP_LIM_1_MIN             (0)
  #define PCU_CR_PACKAGE_RAPL_LIMIT_PCU_PKG_CLMP_LIM_1_MAX             (1) // 0x00000001
  #define PCU_CR_PACKAGE_RAPL_LIMIT_PCU_PKG_CLMP_LIM_1_DEF             (0x00000000)
  #define PCU_CR_PACKAGE_RAPL_LIMIT_PCU_PKG_CLMP_LIM_1_HSH             (0x411059A0)

  #define PCU_CR_PACKAGE_RAPL_LIMIT_PCU_PKG_PWR_LIM_1_TIME_OFF         (17)
  #define PCU_CR_PACKAGE_RAPL_LIMIT_PCU_PKG_PWR_LIM_1_TIME_WID         ( 7)
  #define PCU_CR_PACKAGE_RAPL_LIMIT_PCU_PKG_PWR_LIM_1_TIME_MSK         (0x00FE0000)
  #define PCU_CR_PACKAGE_RAPL_LIMIT_PCU_PKG_PWR_LIM_1_TIME_MIN         (0)
  #define PCU_CR_PACKAGE_RAPL_LIMIT_PCU_PKG_PWR_LIM_1_TIME_MAX         (127) // 0x0000007F
  #define PCU_CR_PACKAGE_RAPL_LIMIT_PCU_PKG_PWR_LIM_1_TIME_DEF         (0x00000000)
  #define PCU_CR_PACKAGE_RAPL_LIMIT_PCU_PKG_PWR_LIM_1_TIME_HSH         (0x471159A0)

  #define PCU_CR_PACKAGE_RAPL_LIMIT_PCU_PKG_PWR_LIM_2_OFF              (32)
  #define PCU_CR_PACKAGE_RAPL_LIMIT_PCU_PKG_PWR_LIM_2_WID              (15)
  #define PCU_CR_PACKAGE_RAPL_LIMIT_PCU_PKG_PWR_LIM_2_MSK              (0x00007FFF00000000ULL)
  #define PCU_CR_PACKAGE_RAPL_LIMIT_PCU_PKG_PWR_LIM_2_MIN              (0)
  #define PCU_CR_PACKAGE_RAPL_LIMIT_PCU_PKG_PWR_LIM_2_MAX              (32767) // 0x00007FFF
  #define PCU_CR_PACKAGE_RAPL_LIMIT_PCU_PKG_PWR_LIM_2_DEF              (0x00000000)
  #define PCU_CR_PACKAGE_RAPL_LIMIT_PCU_PKG_PWR_LIM_2_HSH              (0x4F2059A0)

  #define PCU_CR_PACKAGE_RAPL_LIMIT_PCU_PKG_PWR_LIM_2_EN_OFF           (47)
  #define PCU_CR_PACKAGE_RAPL_LIMIT_PCU_PKG_PWR_LIM_2_EN_WID           ( 1)
  #define PCU_CR_PACKAGE_RAPL_LIMIT_PCU_PKG_PWR_LIM_2_EN_MSK           (0x0000800000000000ULL)
  #define PCU_CR_PACKAGE_RAPL_LIMIT_PCU_PKG_PWR_LIM_2_EN_MIN           (0)
  #define PCU_CR_PACKAGE_RAPL_LIMIT_PCU_PKG_PWR_LIM_2_EN_MAX           (1) // 0x00000001
  #define PCU_CR_PACKAGE_RAPL_LIMIT_PCU_PKG_PWR_LIM_2_EN_DEF           (0x00000000)
  #define PCU_CR_PACKAGE_RAPL_LIMIT_PCU_PKG_PWR_LIM_2_EN_HSH           (0x412F59A0)

  #define PCU_CR_PACKAGE_RAPL_LIMIT_PCU_PKG_CLMP_LIM_2_OFF             (48)
  #define PCU_CR_PACKAGE_RAPL_LIMIT_PCU_PKG_CLMP_LIM_2_WID             ( 1)
  #define PCU_CR_PACKAGE_RAPL_LIMIT_PCU_PKG_CLMP_LIM_2_MSK             (0x0001000000000000ULL)
  #define PCU_CR_PACKAGE_RAPL_LIMIT_PCU_PKG_CLMP_LIM_2_MIN             (0)
  #define PCU_CR_PACKAGE_RAPL_LIMIT_PCU_PKG_CLMP_LIM_2_MAX             (1) // 0x00000001
  #define PCU_CR_PACKAGE_RAPL_LIMIT_PCU_PKG_CLMP_LIM_2_DEF             (0x00000000)
  #define PCU_CR_PACKAGE_RAPL_LIMIT_PCU_PKG_CLMP_LIM_2_HSH             (0x413059A0)

  #define PCU_CR_PACKAGE_RAPL_LIMIT_PCU_PKG_PWR_LIM_2_TIME_OFF         (49)
  #define PCU_CR_PACKAGE_RAPL_LIMIT_PCU_PKG_PWR_LIM_2_TIME_WID         ( 7)
  #define PCU_CR_PACKAGE_RAPL_LIMIT_PCU_PKG_PWR_LIM_2_TIME_MSK         (0x00FE000000000000ULL)
  #define PCU_CR_PACKAGE_RAPL_LIMIT_PCU_PKG_PWR_LIM_2_TIME_MIN         (0)
  #define PCU_CR_PACKAGE_RAPL_LIMIT_PCU_PKG_PWR_LIM_2_TIME_MAX         (127) // 0x0000007F
  #define PCU_CR_PACKAGE_RAPL_LIMIT_PCU_PKG_PWR_LIM_2_TIME_DEF         (0x00000000)
  #define PCU_CR_PACKAGE_RAPL_LIMIT_PCU_PKG_PWR_LIM_2_TIME_HSH         (0x473159A0)

  #define PCU_CR_PACKAGE_RAPL_LIMIT_PCU_PKG_PWR_LIM_LOCK_OFF           (63)
  #define PCU_CR_PACKAGE_RAPL_LIMIT_PCU_PKG_PWR_LIM_LOCK_WID           ( 1)
  #define PCU_CR_PACKAGE_RAPL_LIMIT_PCU_PKG_PWR_LIM_LOCK_MSK           (0x8000000000000000ULL)
  #define PCU_CR_PACKAGE_RAPL_LIMIT_PCU_PKG_PWR_LIM_LOCK_MIN           (0)
  #define PCU_CR_PACKAGE_RAPL_LIMIT_PCU_PKG_PWR_LIM_LOCK_MAX           (1) // 0x00000001
  #define PCU_CR_PACKAGE_RAPL_LIMIT_PCU_PKG_PWR_LIM_LOCK_DEF           (0x00000000)
  #define PCU_CR_PACKAGE_RAPL_LIMIT_PCU_PKG_PWR_LIM_LOCK_HSH           (0x413F59A0)

#define PCU_CR_PRIP_TURBO_PWR_LIM_PCU_REG                              (0x000059A8)

  #define PCU_CR_PRIP_TURBO_PWR_LIM_PCU_IA_PP_PWR_LIM_OFF              ( 0)
  #define PCU_CR_PRIP_TURBO_PWR_LIM_PCU_IA_PP_PWR_LIM_WID              (15)
  #define PCU_CR_PRIP_TURBO_PWR_LIM_PCU_IA_PP_PWR_LIM_MSK              (0x00007FFF)
  #define PCU_CR_PRIP_TURBO_PWR_LIM_PCU_IA_PP_PWR_LIM_MIN              (0)
  #define PCU_CR_PRIP_TURBO_PWR_LIM_PCU_IA_PP_PWR_LIM_MAX              (32767) // 0x00007FFF
  #define PCU_CR_PRIP_TURBO_PWR_LIM_PCU_IA_PP_PWR_LIM_DEF              (0x00000000)
  #define PCU_CR_PRIP_TURBO_PWR_LIM_PCU_IA_PP_PWR_LIM_HSH              (0x0F0059A8)

  #define PCU_CR_PRIP_TURBO_PWR_LIM_PCU_PWR_LIM_CTRL_EN_OFF            (15)
  #define PCU_CR_PRIP_TURBO_PWR_LIM_PCU_PWR_LIM_CTRL_EN_WID            ( 1)
  #define PCU_CR_PRIP_TURBO_PWR_LIM_PCU_PWR_LIM_CTRL_EN_MSK            (0x00008000)
  #define PCU_CR_PRIP_TURBO_PWR_LIM_PCU_PWR_LIM_CTRL_EN_MIN            (0)
  #define PCU_CR_PRIP_TURBO_PWR_LIM_PCU_PWR_LIM_CTRL_EN_MAX            (1) // 0x00000001
  #define PCU_CR_PRIP_TURBO_PWR_LIM_PCU_PWR_LIM_CTRL_EN_DEF            (0x00000000)
  #define PCU_CR_PRIP_TURBO_PWR_LIM_PCU_PWR_LIM_CTRL_EN_HSH            (0x010F59A8)

  #define PCU_CR_PRIP_TURBO_PWR_LIM_PCU_PP_CLAMP_LIM_OFF               (16)
  #define PCU_CR_PRIP_TURBO_PWR_LIM_PCU_PP_CLAMP_LIM_WID               ( 1)
  #define PCU_CR_PRIP_TURBO_PWR_LIM_PCU_PP_CLAMP_LIM_MSK               (0x00010000)
  #define PCU_CR_PRIP_TURBO_PWR_LIM_PCU_PP_CLAMP_LIM_MIN               (0)
  #define PCU_CR_PRIP_TURBO_PWR_LIM_PCU_PP_CLAMP_LIM_MAX               (1) // 0x00000001
  #define PCU_CR_PRIP_TURBO_PWR_LIM_PCU_PP_CLAMP_LIM_DEF               (0x00000000)
  #define PCU_CR_PRIP_TURBO_PWR_LIM_PCU_PP_CLAMP_LIM_HSH               (0x011059A8)

  #define PCU_CR_PRIP_TURBO_PWR_LIM_PCU_CTRL_TIME_WIN_OFF              (17)
  #define PCU_CR_PRIP_TURBO_PWR_LIM_PCU_CTRL_TIME_WIN_WID              ( 7)
  #define PCU_CR_PRIP_TURBO_PWR_LIM_PCU_CTRL_TIME_WIN_MSK              (0x00FE0000)
  #define PCU_CR_PRIP_TURBO_PWR_LIM_PCU_CTRL_TIME_WIN_MIN              (0)
  #define PCU_CR_PRIP_TURBO_PWR_LIM_PCU_CTRL_TIME_WIN_MAX              (127) // 0x0000007F
  #define PCU_CR_PRIP_TURBO_PWR_LIM_PCU_CTRL_TIME_WIN_DEF              (0x00000000)
  #define PCU_CR_PRIP_TURBO_PWR_LIM_PCU_CTRL_TIME_WIN_HSH              (0x071159A8)

  #define PCU_CR_PRIP_TURBO_PWR_LIM_PCU_PP_PWR_LIM_LOCK_OFF            (31)
  #define PCU_CR_PRIP_TURBO_PWR_LIM_PCU_PP_PWR_LIM_LOCK_WID            ( 1)
  #define PCU_CR_PRIP_TURBO_PWR_LIM_PCU_PP_PWR_LIM_LOCK_MSK            (0x80000000)
  #define PCU_CR_PRIP_TURBO_PWR_LIM_PCU_PP_PWR_LIM_LOCK_MIN            (0)
  #define PCU_CR_PRIP_TURBO_PWR_LIM_PCU_PP_PWR_LIM_LOCK_MAX            (1) // 0x00000001
  #define PCU_CR_PRIP_TURBO_PWR_LIM_PCU_PP_PWR_LIM_LOCK_DEF            (0x00000000)
  #define PCU_CR_PRIP_TURBO_PWR_LIM_PCU_PP_PWR_LIM_LOCK_HSH            (0x011F59A8)

#define PCU_CR_SECP_TURBO_PWR_LIM_PCU_REG                              (0x000059AC)

  #define PCU_CR_SECP_TURBO_PWR_LIM_PCU_NON_IA_PP_PWR_LIM_OFF          ( 0)
  #define PCU_CR_SECP_TURBO_PWR_LIM_PCU_NON_IA_PP_PWR_LIM_WID          (15)
  #define PCU_CR_SECP_TURBO_PWR_LIM_PCU_NON_IA_PP_PWR_LIM_MSK          (0x00007FFF)
  #define PCU_CR_SECP_TURBO_PWR_LIM_PCU_NON_IA_PP_PWR_LIM_MIN          (0)
  #define PCU_CR_SECP_TURBO_PWR_LIM_PCU_NON_IA_PP_PWR_LIM_MAX          (32767) // 0x00007FFF
  #define PCU_CR_SECP_TURBO_PWR_LIM_PCU_NON_IA_PP_PWR_LIM_DEF          (0x00000000)
  #define PCU_CR_SECP_TURBO_PWR_LIM_PCU_NON_IA_PP_PWR_LIM_HSH          (0x0F0059AC)

  #define PCU_CR_SECP_TURBO_PWR_LIM_PCU_PWR_LIM_CTRL_EN_OFF            (15)
  #define PCU_CR_SECP_TURBO_PWR_LIM_PCU_PWR_LIM_CTRL_EN_WID            ( 1)
  #define PCU_CR_SECP_TURBO_PWR_LIM_PCU_PWR_LIM_CTRL_EN_MSK            (0x00008000)
  #define PCU_CR_SECP_TURBO_PWR_LIM_PCU_PWR_LIM_CTRL_EN_MIN            (0)
  #define PCU_CR_SECP_TURBO_PWR_LIM_PCU_PWR_LIM_CTRL_EN_MAX            (1) // 0x00000001
  #define PCU_CR_SECP_TURBO_PWR_LIM_PCU_PWR_LIM_CTRL_EN_DEF            (0x00000000)
  #define PCU_CR_SECP_TURBO_PWR_LIM_PCU_PWR_LIM_CTRL_EN_HSH            (0x010F59AC)

  #define PCU_CR_SECP_TURBO_PWR_LIM_PCU_PP_CLAMP_LIM_OFF               (16)
  #define PCU_CR_SECP_TURBO_PWR_LIM_PCU_PP_CLAMP_LIM_WID               ( 1)
  #define PCU_CR_SECP_TURBO_PWR_LIM_PCU_PP_CLAMP_LIM_MSK               (0x00010000)
  #define PCU_CR_SECP_TURBO_PWR_LIM_PCU_PP_CLAMP_LIM_MIN               (0)
  #define PCU_CR_SECP_TURBO_PWR_LIM_PCU_PP_CLAMP_LIM_MAX               (1) // 0x00000001
  #define PCU_CR_SECP_TURBO_PWR_LIM_PCU_PP_CLAMP_LIM_DEF               (0x00000000)
  #define PCU_CR_SECP_TURBO_PWR_LIM_PCU_PP_CLAMP_LIM_HSH               (0x011059AC)

  #define PCU_CR_SECP_TURBO_PWR_LIM_PCU_CTRL_TIME_WIN_OFF              (17)
  #define PCU_CR_SECP_TURBO_PWR_LIM_PCU_CTRL_TIME_WIN_WID              ( 7)
  #define PCU_CR_SECP_TURBO_PWR_LIM_PCU_CTRL_TIME_WIN_MSK              (0x00FE0000)
  #define PCU_CR_SECP_TURBO_PWR_LIM_PCU_CTRL_TIME_WIN_MIN              (0)
  #define PCU_CR_SECP_TURBO_PWR_LIM_PCU_CTRL_TIME_WIN_MAX              (127) // 0x0000007F
  #define PCU_CR_SECP_TURBO_PWR_LIM_PCU_CTRL_TIME_WIN_DEF              (0x00000000)
  #define PCU_CR_SECP_TURBO_PWR_LIM_PCU_CTRL_TIME_WIN_HSH              (0x071159AC)

  #define PCU_CR_SECP_TURBO_PWR_LIM_PCU_SP_PWR_LIM_LOCK_OFF            (31)
  #define PCU_CR_SECP_TURBO_PWR_LIM_PCU_SP_PWR_LIM_LOCK_WID            ( 1)
  #define PCU_CR_SECP_TURBO_PWR_LIM_PCU_SP_PWR_LIM_LOCK_MSK            (0x80000000)
  #define PCU_CR_SECP_TURBO_PWR_LIM_PCU_SP_PWR_LIM_LOCK_MIN            (0)
  #define PCU_CR_SECP_TURBO_PWR_LIM_PCU_SP_PWR_LIM_LOCK_MAX            (1) // 0x00000001
  #define PCU_CR_SECP_TURBO_PWR_LIM_PCU_SP_PWR_LIM_LOCK_DEF            (0x00000000)
  #define PCU_CR_SECP_TURBO_PWR_LIM_PCU_SP_PWR_LIM_LOCK_HSH            (0x011F59AC)

#define PCU_CR_VR_CURRENT_CONFIG_PCU_REG                               (0x000059B0)

  #define PCU_CR_VR_CURRENT_CONFIG_PCU_CURRENT_LIMIT_OFF               ( 0)
  #define PCU_CR_VR_CURRENT_CONFIG_PCU_CURRENT_LIMIT_WID               (13)
  #define PCU_CR_VR_CURRENT_CONFIG_PCU_CURRENT_LIMIT_MSK               (0x00001FFF)
  #define PCU_CR_VR_CURRENT_CONFIG_PCU_CURRENT_LIMIT_MIN               (0)
  #define PCU_CR_VR_CURRENT_CONFIG_PCU_CURRENT_LIMIT_MAX               (8191) // 0x00001FFF
  #define PCU_CR_VR_CURRENT_CONFIG_PCU_CURRENT_LIMIT_DEF               (0x00000190)
  #define PCU_CR_VR_CURRENT_CONFIG_PCU_CURRENT_LIMIT_HSH               (0x4D0059B0)

  #define PCU_CR_VR_CURRENT_CONFIG_PCU_LOCK_OFF                        (31)
  #define PCU_CR_VR_CURRENT_CONFIG_PCU_LOCK_WID                        ( 1)
  #define PCU_CR_VR_CURRENT_CONFIG_PCU_LOCK_MSK                        (0x80000000)
  #define PCU_CR_VR_CURRENT_CONFIG_PCU_LOCK_MIN                        (0)
  #define PCU_CR_VR_CURRENT_CONFIG_PCU_LOCK_MAX                        (1) // 0x00000001
  #define PCU_CR_VR_CURRENT_CONFIG_PCU_LOCK_DEF                        (0x00000000)
  #define PCU_CR_VR_CURRENT_CONFIG_PCU_LOCK_HSH                        (0x411F59B0)

  #define PCU_CR_VR_CURRENT_CONFIG_PCU_PSI1_THRESHOLD_OFF              (32)
  #define PCU_CR_VR_CURRENT_CONFIG_PCU_PSI1_THRESHOLD_WID              (10)
  #define PCU_CR_VR_CURRENT_CONFIG_PCU_PSI1_THRESHOLD_MSK              (0x000003FF00000000ULL)
  #define PCU_CR_VR_CURRENT_CONFIG_PCU_PSI1_THRESHOLD_MIN              (0)
  #define PCU_CR_VR_CURRENT_CONFIG_PCU_PSI1_THRESHOLD_MAX              (1023) // 0x000003FF
  #define PCU_CR_VR_CURRENT_CONFIG_PCU_PSI1_THRESHOLD_DEF              (0x00000000)
  #define PCU_CR_VR_CURRENT_CONFIG_PCU_PSI1_THRESHOLD_HSH              (0x4A2059B0)

  #define PCU_CR_VR_CURRENT_CONFIG_PCU_PSI2_THRESHOLD_OFF              (42)
  #define PCU_CR_VR_CURRENT_CONFIG_PCU_PSI2_THRESHOLD_WID              (10)
  #define PCU_CR_VR_CURRENT_CONFIG_PCU_PSI2_THRESHOLD_MSK              (0x000FFC0000000000ULL)
  #define PCU_CR_VR_CURRENT_CONFIG_PCU_PSI2_THRESHOLD_MIN              (0)
  #define PCU_CR_VR_CURRENT_CONFIG_PCU_PSI2_THRESHOLD_MAX              (1023) // 0x000003FF
  #define PCU_CR_VR_CURRENT_CONFIG_PCU_PSI2_THRESHOLD_DEF              (0x00000000)
  #define PCU_CR_VR_CURRENT_CONFIG_PCU_PSI2_THRESHOLD_HSH              (0x4A2A59B0)

  #define PCU_CR_VR_CURRENT_CONFIG_PCU_PSI3_THRESHOLD_OFF              (52)
  #define PCU_CR_VR_CURRENT_CONFIG_PCU_PSI3_THRESHOLD_WID              (10)
  #define PCU_CR_VR_CURRENT_CONFIG_PCU_PSI3_THRESHOLD_MSK              (0x3FF0000000000000ULL)
  #define PCU_CR_VR_CURRENT_CONFIG_PCU_PSI3_THRESHOLD_MIN              (0)
  #define PCU_CR_VR_CURRENT_CONFIG_PCU_PSI3_THRESHOLD_MAX              (1023) // 0x000003FF
  #define PCU_CR_VR_CURRENT_CONFIG_PCU_PSI3_THRESHOLD_DEF              (0x00000000)
  #define PCU_CR_VR_CURRENT_CONFIG_PCU_PSI3_THRESHOLD_HSH              (0x4A3459B0)

  #define PCU_CR_VR_CURRENT_CONFIG_PCU_PS4_ENABLE_OFF                  (62)
  #define PCU_CR_VR_CURRENT_CONFIG_PCU_PS4_ENABLE_WID                  ( 1)
  #define PCU_CR_VR_CURRENT_CONFIG_PCU_PS4_ENABLE_MSK                  (0x4000000000000000ULL)
  #define PCU_CR_VR_CURRENT_CONFIG_PCU_PS4_ENABLE_MIN                  (0)
  #define PCU_CR_VR_CURRENT_CONFIG_PCU_PS4_ENABLE_MAX                  (1) // 0x00000001
  #define PCU_CR_VR_CURRENT_CONFIG_PCU_PS4_ENABLE_DEF                  (0x00000000)
  #define PCU_CR_VR_CURRENT_CONFIG_PCU_PS4_ENABLE_HSH                  (0x413E59B0)

  #define PCU_CR_VR_CURRENT_CONFIG_PCU_RESERVED_OFF                    (63)
  #define PCU_CR_VR_CURRENT_CONFIG_PCU_RESERVED_WID                    ( 1)
  #define PCU_CR_VR_CURRENT_CONFIG_PCU_RESERVED_MSK                    (0x8000000000000000ULL)
  #define PCU_CR_VR_CURRENT_CONFIG_PCU_RESERVED_MIN                    (0)
  #define PCU_CR_VR_CURRENT_CONFIG_PCU_RESERVED_MAX                    (1) // 0x00000001
  #define PCU_CR_VR_CURRENT_CONFIG_PCU_RESERVED_DEF                    (0x00000000)
  #define PCU_CR_VR_CURRENT_CONFIG_PCU_RESERVED_HSH                    (0x413F59B0)

#define PCU_CR_MRC_ODT_POWER_SAVING_PCU_REG                            (0x000059B8)

  #define PCU_CR_MRC_ODT_POWER_SAVING_PCU_MRC_Saving_Rd_OFF            ( 0)
  #define PCU_CR_MRC_ODT_POWER_SAVING_PCU_MRC_Saving_Rd_WID            ( 8)
  #define PCU_CR_MRC_ODT_POWER_SAVING_PCU_MRC_Saving_Rd_MSK            (0x000000FF)
  #define PCU_CR_MRC_ODT_POWER_SAVING_PCU_MRC_Saving_Rd_MIN            (0)
  #define PCU_CR_MRC_ODT_POWER_SAVING_PCU_MRC_Saving_Rd_MAX            (255) // 0x000000FF
  #define PCU_CR_MRC_ODT_POWER_SAVING_PCU_MRC_Saving_Rd_DEF            (0x00000000)
  #define PCU_CR_MRC_ODT_POWER_SAVING_PCU_MRC_Saving_Rd_HSH            (0x080059B8)

  #define PCU_CR_MRC_ODT_POWER_SAVING_PCU_MRC_Saving_Wt_OFF            ( 8)
  #define PCU_CR_MRC_ODT_POWER_SAVING_PCU_MRC_Saving_Wt_WID            ( 8)
  #define PCU_CR_MRC_ODT_POWER_SAVING_PCU_MRC_Saving_Wt_MSK            (0x0000FF00)
  #define PCU_CR_MRC_ODT_POWER_SAVING_PCU_MRC_Saving_Wt_MIN            (0)
  #define PCU_CR_MRC_ODT_POWER_SAVING_PCU_MRC_Saving_Wt_MAX            (255) // 0x000000FF
  #define PCU_CR_MRC_ODT_POWER_SAVING_PCU_MRC_Saving_Wt_DEF            (0x00000000)
  #define PCU_CR_MRC_ODT_POWER_SAVING_PCU_MRC_Saving_Wt_HSH            (0x080859B8)

  #define PCU_CR_MRC_ODT_POWER_SAVING_PCU_MRC_Saving_Cmd_OFF           (16)
  #define PCU_CR_MRC_ODT_POWER_SAVING_PCU_MRC_Saving_Cmd_WID           ( 8)
  #define PCU_CR_MRC_ODT_POWER_SAVING_PCU_MRC_Saving_Cmd_MSK           (0x00FF0000)
  #define PCU_CR_MRC_ODT_POWER_SAVING_PCU_MRC_Saving_Cmd_MIN           (0)
  #define PCU_CR_MRC_ODT_POWER_SAVING_PCU_MRC_Saving_Cmd_MAX           (255) // 0x000000FF
  #define PCU_CR_MRC_ODT_POWER_SAVING_PCU_MRC_Saving_Cmd_DEF           (0x00000000)
  #define PCU_CR_MRC_ODT_POWER_SAVING_PCU_MRC_Saving_Cmd_HSH           (0x081059B8)

  #define PCU_CR_MRC_ODT_POWER_SAVING_PCU_RESERVED_OFF                 (24)
  #define PCU_CR_MRC_ODT_POWER_SAVING_PCU_RESERVED_WID                 ( 8)
  #define PCU_CR_MRC_ODT_POWER_SAVING_PCU_RESERVED_MSK                 (0xFF000000)
  #define PCU_CR_MRC_ODT_POWER_SAVING_PCU_RESERVED_MIN                 (0)
  #define PCU_CR_MRC_ODT_POWER_SAVING_PCU_RESERVED_MAX                 (255) // 0x000000FF
  #define PCU_CR_MRC_ODT_POWER_SAVING_PCU_RESERVED_DEF                 (0x00000000)
  #define PCU_CR_MRC_ODT_POWER_SAVING_PCU_RESERVED_HSH                 (0x081859B8)

#define PCU_CR_THERM_STATUS_GT_PCU_REG                                 (0x000059C0)

  #define PCU_CR_THERM_STATUS_GT_PCU_THERMAL_MONITOR_STATUS_OFF        ( 0)
  #define PCU_CR_THERM_STATUS_GT_PCU_THERMAL_MONITOR_STATUS_WID        ( 1)
  #define PCU_CR_THERM_STATUS_GT_PCU_THERMAL_MONITOR_STATUS_MSK        (0x00000001)
  #define PCU_CR_THERM_STATUS_GT_PCU_THERMAL_MONITOR_STATUS_MIN        (0)
  #define PCU_CR_THERM_STATUS_GT_PCU_THERMAL_MONITOR_STATUS_MAX        (1) // 0x00000001
  #define PCU_CR_THERM_STATUS_GT_PCU_THERMAL_MONITOR_STATUS_DEF        (0x00000000)
  #define PCU_CR_THERM_STATUS_GT_PCU_THERMAL_MONITOR_STATUS_HSH        (0x010059C0)

  #define PCU_CR_THERM_STATUS_GT_PCU_THERMAL_MONITOR_LOG_OFF           ( 1)
  #define PCU_CR_THERM_STATUS_GT_PCU_THERMAL_MONITOR_LOG_WID           ( 1)
  #define PCU_CR_THERM_STATUS_GT_PCU_THERMAL_MONITOR_LOG_MSK           (0x00000002)
  #define PCU_CR_THERM_STATUS_GT_PCU_THERMAL_MONITOR_LOG_MIN           (0)
  #define PCU_CR_THERM_STATUS_GT_PCU_THERMAL_MONITOR_LOG_MAX           (1) // 0x00000001
  #define PCU_CR_THERM_STATUS_GT_PCU_THERMAL_MONITOR_LOG_DEF           (0x00000000)
  #define PCU_CR_THERM_STATUS_GT_PCU_THERMAL_MONITOR_LOG_HSH           (0x010159C0)

  #define PCU_CR_THERM_STATUS_GT_PCU_PROCHOT_STATUS_OFF                ( 2)
  #define PCU_CR_THERM_STATUS_GT_PCU_PROCHOT_STATUS_WID                ( 1)
  #define PCU_CR_THERM_STATUS_GT_PCU_PROCHOT_STATUS_MSK                (0x00000004)
  #define PCU_CR_THERM_STATUS_GT_PCU_PROCHOT_STATUS_MIN                (0)
  #define PCU_CR_THERM_STATUS_GT_PCU_PROCHOT_STATUS_MAX                (1) // 0x00000001
  #define PCU_CR_THERM_STATUS_GT_PCU_PROCHOT_STATUS_DEF                (0x00000000)
  #define PCU_CR_THERM_STATUS_GT_PCU_PROCHOT_STATUS_HSH                (0x010259C0)

  #define PCU_CR_THERM_STATUS_GT_PCU_PROCHOT_LOG_OFF                   ( 3)
  #define PCU_CR_THERM_STATUS_GT_PCU_PROCHOT_LOG_WID                   ( 1)
  #define PCU_CR_THERM_STATUS_GT_PCU_PROCHOT_LOG_MSK                   (0x00000008)
  #define PCU_CR_THERM_STATUS_GT_PCU_PROCHOT_LOG_MIN                   (0)
  #define PCU_CR_THERM_STATUS_GT_PCU_PROCHOT_LOG_MAX                   (1) // 0x00000001
  #define PCU_CR_THERM_STATUS_GT_PCU_PROCHOT_LOG_DEF                   (0x00000000)
  #define PCU_CR_THERM_STATUS_GT_PCU_PROCHOT_LOG_HSH                   (0x010359C0)

  #define PCU_CR_THERM_STATUS_GT_PCU_OUT_OF_SPEC_STATUS_OFF            ( 4)
  #define PCU_CR_THERM_STATUS_GT_PCU_OUT_OF_SPEC_STATUS_WID            ( 1)
  #define PCU_CR_THERM_STATUS_GT_PCU_OUT_OF_SPEC_STATUS_MSK            (0x00000010)
  #define PCU_CR_THERM_STATUS_GT_PCU_OUT_OF_SPEC_STATUS_MIN            (0)
  #define PCU_CR_THERM_STATUS_GT_PCU_OUT_OF_SPEC_STATUS_MAX            (1) // 0x00000001
  #define PCU_CR_THERM_STATUS_GT_PCU_OUT_OF_SPEC_STATUS_DEF            (0x00000000)
  #define PCU_CR_THERM_STATUS_GT_PCU_OUT_OF_SPEC_STATUS_HSH            (0x010459C0)

  #define PCU_CR_THERM_STATUS_GT_PCU_OUT_OF_SPEC_LOG_OFF               ( 5)
  #define PCU_CR_THERM_STATUS_GT_PCU_OUT_OF_SPEC_LOG_WID               ( 1)
  #define PCU_CR_THERM_STATUS_GT_PCU_OUT_OF_SPEC_LOG_MSK               (0x00000020)
  #define PCU_CR_THERM_STATUS_GT_PCU_OUT_OF_SPEC_LOG_MIN               (0)
  #define PCU_CR_THERM_STATUS_GT_PCU_OUT_OF_SPEC_LOG_MAX               (1) // 0x00000001
  #define PCU_CR_THERM_STATUS_GT_PCU_OUT_OF_SPEC_LOG_DEF               (0x00000000)
  #define PCU_CR_THERM_STATUS_GT_PCU_OUT_OF_SPEC_LOG_HSH               (0x010559C0)

  #define PCU_CR_THERM_STATUS_GT_PCU_THRESHOLD1_STATUS_OFF             ( 6)
  #define PCU_CR_THERM_STATUS_GT_PCU_THRESHOLD1_STATUS_WID             ( 1)
  #define PCU_CR_THERM_STATUS_GT_PCU_THRESHOLD1_STATUS_MSK             (0x00000040)
  #define PCU_CR_THERM_STATUS_GT_PCU_THRESHOLD1_STATUS_MIN             (0)
  #define PCU_CR_THERM_STATUS_GT_PCU_THRESHOLD1_STATUS_MAX             (1) // 0x00000001
  #define PCU_CR_THERM_STATUS_GT_PCU_THRESHOLD1_STATUS_DEF             (0x00000000)
  #define PCU_CR_THERM_STATUS_GT_PCU_THRESHOLD1_STATUS_HSH             (0x010659C0)

  #define PCU_CR_THERM_STATUS_GT_PCU_THRESHOLD1_LOG_OFF                ( 7)
  #define PCU_CR_THERM_STATUS_GT_PCU_THRESHOLD1_LOG_WID                ( 1)
  #define PCU_CR_THERM_STATUS_GT_PCU_THRESHOLD1_LOG_MSK                (0x00000080)
  #define PCU_CR_THERM_STATUS_GT_PCU_THRESHOLD1_LOG_MIN                (0)
  #define PCU_CR_THERM_STATUS_GT_PCU_THRESHOLD1_LOG_MAX                (1) // 0x00000001
  #define PCU_CR_THERM_STATUS_GT_PCU_THRESHOLD1_LOG_DEF                (0x00000000)
  #define PCU_CR_THERM_STATUS_GT_PCU_THRESHOLD1_LOG_HSH                (0x010759C0)

  #define PCU_CR_THERM_STATUS_GT_PCU_THRESHOLD2_STATUS_OFF             ( 8)
  #define PCU_CR_THERM_STATUS_GT_PCU_THRESHOLD2_STATUS_WID             ( 1)
  #define PCU_CR_THERM_STATUS_GT_PCU_THRESHOLD2_STATUS_MSK             (0x00000100)
  #define PCU_CR_THERM_STATUS_GT_PCU_THRESHOLD2_STATUS_MIN             (0)
  #define PCU_CR_THERM_STATUS_GT_PCU_THRESHOLD2_STATUS_MAX             (1) // 0x00000001
  #define PCU_CR_THERM_STATUS_GT_PCU_THRESHOLD2_STATUS_DEF             (0x00000000)
  #define PCU_CR_THERM_STATUS_GT_PCU_THRESHOLD2_STATUS_HSH             (0x010859C0)

  #define PCU_CR_THERM_STATUS_GT_PCU_THRESHOLD2_LOG_OFF                ( 9)
  #define PCU_CR_THERM_STATUS_GT_PCU_THRESHOLD2_LOG_WID                ( 1)
  #define PCU_CR_THERM_STATUS_GT_PCU_THRESHOLD2_LOG_MSK                (0x00000200)
  #define PCU_CR_THERM_STATUS_GT_PCU_THRESHOLD2_LOG_MIN                (0)
  #define PCU_CR_THERM_STATUS_GT_PCU_THRESHOLD2_LOG_MAX                (1) // 0x00000001
  #define PCU_CR_THERM_STATUS_GT_PCU_THRESHOLD2_LOG_DEF                (0x00000000)
  #define PCU_CR_THERM_STATUS_GT_PCU_THRESHOLD2_LOG_HSH                (0x010959C0)

  #define PCU_CR_THERM_STATUS_GT_PCU_POWER_LIMITATION_STATUS_OFF       (10)
  #define PCU_CR_THERM_STATUS_GT_PCU_POWER_LIMITATION_STATUS_WID       ( 1)
  #define PCU_CR_THERM_STATUS_GT_PCU_POWER_LIMITATION_STATUS_MSK       (0x00000400)
  #define PCU_CR_THERM_STATUS_GT_PCU_POWER_LIMITATION_STATUS_MIN       (0)
  #define PCU_CR_THERM_STATUS_GT_PCU_POWER_LIMITATION_STATUS_MAX       (1) // 0x00000001
  #define PCU_CR_THERM_STATUS_GT_PCU_POWER_LIMITATION_STATUS_DEF       (0x00000000)
  #define PCU_CR_THERM_STATUS_GT_PCU_POWER_LIMITATION_STATUS_HSH       (0x010A59C0)

  #define PCU_CR_THERM_STATUS_GT_PCU_POWER_LIMITATION_LOG_OFF          (11)
  #define PCU_CR_THERM_STATUS_GT_PCU_POWER_LIMITATION_LOG_WID          ( 1)
  #define PCU_CR_THERM_STATUS_GT_PCU_POWER_LIMITATION_LOG_MSK          (0x00000800)
  #define PCU_CR_THERM_STATUS_GT_PCU_POWER_LIMITATION_LOG_MIN          (0)
  #define PCU_CR_THERM_STATUS_GT_PCU_POWER_LIMITATION_LOG_MAX          (1) // 0x00000001
  #define PCU_CR_THERM_STATUS_GT_PCU_POWER_LIMITATION_LOG_DEF          (0x00000000)
  #define PCU_CR_THERM_STATUS_GT_PCU_POWER_LIMITATION_LOG_HSH          (0x010B59C0)

  #define PCU_CR_THERM_STATUS_GT_PCU_CURRENT_LIMIT_STATUS_OFF          (12)
  #define PCU_CR_THERM_STATUS_GT_PCU_CURRENT_LIMIT_STATUS_WID          ( 1)
  #define PCU_CR_THERM_STATUS_GT_PCU_CURRENT_LIMIT_STATUS_MSK          (0x00001000)
  #define PCU_CR_THERM_STATUS_GT_PCU_CURRENT_LIMIT_STATUS_MIN          (0)
  #define PCU_CR_THERM_STATUS_GT_PCU_CURRENT_LIMIT_STATUS_MAX          (1) // 0x00000001
  #define PCU_CR_THERM_STATUS_GT_PCU_CURRENT_LIMIT_STATUS_DEF          (0x00000000)
  #define PCU_CR_THERM_STATUS_GT_PCU_CURRENT_LIMIT_STATUS_HSH          (0x010C59C0)

  #define PCU_CR_THERM_STATUS_GT_PCU_CURRENT_LIMIT_LOG_OFF             (13)
  #define PCU_CR_THERM_STATUS_GT_PCU_CURRENT_LIMIT_LOG_WID             ( 1)
  #define PCU_CR_THERM_STATUS_GT_PCU_CURRENT_LIMIT_LOG_MSK             (0x00002000)
  #define PCU_CR_THERM_STATUS_GT_PCU_CURRENT_LIMIT_LOG_MIN             (0)
  #define PCU_CR_THERM_STATUS_GT_PCU_CURRENT_LIMIT_LOG_MAX             (1) // 0x00000001
  #define PCU_CR_THERM_STATUS_GT_PCU_CURRENT_LIMIT_LOG_DEF             (0x00000000)
  #define PCU_CR_THERM_STATUS_GT_PCU_CURRENT_LIMIT_LOG_HSH             (0x010D59C0)

  #define PCU_CR_THERM_STATUS_GT_PCU_CROSS_DOMAIN_LIMIT_STATUS_OFF     (14)
  #define PCU_CR_THERM_STATUS_GT_PCU_CROSS_DOMAIN_LIMIT_STATUS_WID     ( 1)
  #define PCU_CR_THERM_STATUS_GT_PCU_CROSS_DOMAIN_LIMIT_STATUS_MSK     (0x00004000)
  #define PCU_CR_THERM_STATUS_GT_PCU_CROSS_DOMAIN_LIMIT_STATUS_MIN     (0)
  #define PCU_CR_THERM_STATUS_GT_PCU_CROSS_DOMAIN_LIMIT_STATUS_MAX     (1) // 0x00000001
  #define PCU_CR_THERM_STATUS_GT_PCU_CROSS_DOMAIN_LIMIT_STATUS_DEF     (0x00000000)
  #define PCU_CR_THERM_STATUS_GT_PCU_CROSS_DOMAIN_LIMIT_STATUS_HSH     (0x010E59C0)

  #define PCU_CR_THERM_STATUS_GT_PCU_CROSS_DOMAIN_LIMIT_LOG_OFF        (15)
  #define PCU_CR_THERM_STATUS_GT_PCU_CROSS_DOMAIN_LIMIT_LOG_WID        ( 1)
  #define PCU_CR_THERM_STATUS_GT_PCU_CROSS_DOMAIN_LIMIT_LOG_MSK        (0x00008000)
  #define PCU_CR_THERM_STATUS_GT_PCU_CROSS_DOMAIN_LIMIT_LOG_MIN        (0)
  #define PCU_CR_THERM_STATUS_GT_PCU_CROSS_DOMAIN_LIMIT_LOG_MAX        (1) // 0x00000001
  #define PCU_CR_THERM_STATUS_GT_PCU_CROSS_DOMAIN_LIMIT_LOG_DEF        (0x00000000)
  #define PCU_CR_THERM_STATUS_GT_PCU_CROSS_DOMAIN_LIMIT_LOG_HSH        (0x010F59C0)

  #define PCU_CR_THERM_STATUS_GT_PCU_TEMPERATURE_OFF                   (16)
  #define PCU_CR_THERM_STATUS_GT_PCU_TEMPERATURE_WID                   ( 7)
  #define PCU_CR_THERM_STATUS_GT_PCU_TEMPERATURE_MSK                   (0x007F0000)
  #define PCU_CR_THERM_STATUS_GT_PCU_TEMPERATURE_MIN                   (0)
  #define PCU_CR_THERM_STATUS_GT_PCU_TEMPERATURE_MAX                   (127) // 0x0000007F
  #define PCU_CR_THERM_STATUS_GT_PCU_TEMPERATURE_DEF                   (0x00000000)
  #define PCU_CR_THERM_STATUS_GT_PCU_TEMPERATURE_HSH                   (0x071059C0)

  #define PCU_CR_THERM_STATUS_GT_PCU_RESOLUTION_OFF                    (27)
  #define PCU_CR_THERM_STATUS_GT_PCU_RESOLUTION_WID                    ( 4)
  #define PCU_CR_THERM_STATUS_GT_PCU_RESOLUTION_MSK                    (0x78000000)
  #define PCU_CR_THERM_STATUS_GT_PCU_RESOLUTION_MIN                    (0)
  #define PCU_CR_THERM_STATUS_GT_PCU_RESOLUTION_MAX                    (15) // 0x0000000F
  #define PCU_CR_THERM_STATUS_GT_PCU_RESOLUTION_DEF                    (0x00000001)
  #define PCU_CR_THERM_STATUS_GT_PCU_RESOLUTION_HSH                    (0x041B59C0)

  #define PCU_CR_THERM_STATUS_GT_PCU_VALID_OFF                         (31)
  #define PCU_CR_THERM_STATUS_GT_PCU_VALID_WID                         ( 1)
  #define PCU_CR_THERM_STATUS_GT_PCU_VALID_MSK                         (0x80000000)
  #define PCU_CR_THERM_STATUS_GT_PCU_VALID_MIN                         (0)
  #define PCU_CR_THERM_STATUS_GT_PCU_VALID_MAX                         (1) // 0x00000001
  #define PCU_CR_THERM_STATUS_GT_PCU_VALID_DEF                         (0x00000000)
  #define PCU_CR_THERM_STATUS_GT_PCU_VALID_HSH                         (0x011F59C0)

#define PCU_CR_THERM_INTERRUPT_GT_PCU_REG                              (0x000059C4)

  #define PCU_CR_THERM_INTERRUPT_GT_PCU_HIGH_TEMP_INT_ENABLE_OFF       ( 0)
  #define PCU_CR_THERM_INTERRUPT_GT_PCU_HIGH_TEMP_INT_ENABLE_WID       ( 1)
  #define PCU_CR_THERM_INTERRUPT_GT_PCU_HIGH_TEMP_INT_ENABLE_MSK       (0x00000001)
  #define PCU_CR_THERM_INTERRUPT_GT_PCU_HIGH_TEMP_INT_ENABLE_MIN       (0)
  #define PCU_CR_THERM_INTERRUPT_GT_PCU_HIGH_TEMP_INT_ENABLE_MAX       (1) // 0x00000001
  #define PCU_CR_THERM_INTERRUPT_GT_PCU_HIGH_TEMP_INT_ENABLE_DEF       (0x00000000)
  #define PCU_CR_THERM_INTERRUPT_GT_PCU_HIGH_TEMP_INT_ENABLE_HSH       (0x010059C4)

  #define PCU_CR_THERM_INTERRUPT_GT_PCU_LOW_TEMP_INT_ENABLE_OFF        ( 1)
  #define PCU_CR_THERM_INTERRUPT_GT_PCU_LOW_TEMP_INT_ENABLE_WID        ( 1)
  #define PCU_CR_THERM_INTERRUPT_GT_PCU_LOW_TEMP_INT_ENABLE_MSK        (0x00000002)
  #define PCU_CR_THERM_INTERRUPT_GT_PCU_LOW_TEMP_INT_ENABLE_MIN        (0)
  #define PCU_CR_THERM_INTERRUPT_GT_PCU_LOW_TEMP_INT_ENABLE_MAX        (1) // 0x00000001
  #define PCU_CR_THERM_INTERRUPT_GT_PCU_LOW_TEMP_INT_ENABLE_DEF        (0x00000000)
  #define PCU_CR_THERM_INTERRUPT_GT_PCU_LOW_TEMP_INT_ENABLE_HSH        (0x010159C4)

  #define PCU_CR_THERM_INTERRUPT_GT_PCU_PROCHOT_INT_ENABLE_OFF         ( 2)
  #define PCU_CR_THERM_INTERRUPT_GT_PCU_PROCHOT_INT_ENABLE_WID         ( 1)
  #define PCU_CR_THERM_INTERRUPT_GT_PCU_PROCHOT_INT_ENABLE_MSK         (0x00000004)
  #define PCU_CR_THERM_INTERRUPT_GT_PCU_PROCHOT_INT_ENABLE_MIN         (0)
  #define PCU_CR_THERM_INTERRUPT_GT_PCU_PROCHOT_INT_ENABLE_MAX         (1) // 0x00000001
  #define PCU_CR_THERM_INTERRUPT_GT_PCU_PROCHOT_INT_ENABLE_DEF         (0x00000000)
  #define PCU_CR_THERM_INTERRUPT_GT_PCU_PROCHOT_INT_ENABLE_HSH         (0x010259C4)

  #define PCU_CR_THERM_INTERRUPT_GT_PCU_OUT_OF_SPEC_INT_ENABLE_OFF     ( 4)
  #define PCU_CR_THERM_INTERRUPT_GT_PCU_OUT_OF_SPEC_INT_ENABLE_WID     ( 1)
  #define PCU_CR_THERM_INTERRUPT_GT_PCU_OUT_OF_SPEC_INT_ENABLE_MSK     (0x00000010)
  #define PCU_CR_THERM_INTERRUPT_GT_PCU_OUT_OF_SPEC_INT_ENABLE_MIN     (0)
  #define PCU_CR_THERM_INTERRUPT_GT_PCU_OUT_OF_SPEC_INT_ENABLE_MAX     (1) // 0x00000001
  #define PCU_CR_THERM_INTERRUPT_GT_PCU_OUT_OF_SPEC_INT_ENABLE_DEF     (0x00000000)
  #define PCU_CR_THERM_INTERRUPT_GT_PCU_OUT_OF_SPEC_INT_ENABLE_HSH     (0x010459C4)

  #define PCU_CR_THERM_INTERRUPT_GT_PCU_THRESHOLD_1_REL_TEMP_OFF       ( 8)
  #define PCU_CR_THERM_INTERRUPT_GT_PCU_THRESHOLD_1_REL_TEMP_WID       ( 7)
  #define PCU_CR_THERM_INTERRUPT_GT_PCU_THRESHOLD_1_REL_TEMP_MSK       (0x00007F00)
  #define PCU_CR_THERM_INTERRUPT_GT_PCU_THRESHOLD_1_REL_TEMP_MIN       (0)
  #define PCU_CR_THERM_INTERRUPT_GT_PCU_THRESHOLD_1_REL_TEMP_MAX       (127) // 0x0000007F
  #define PCU_CR_THERM_INTERRUPT_GT_PCU_THRESHOLD_1_REL_TEMP_DEF       (0x00000000)
  #define PCU_CR_THERM_INTERRUPT_GT_PCU_THRESHOLD_1_REL_TEMP_HSH       (0x070859C4)

  #define PCU_CR_THERM_INTERRUPT_GT_PCU_THRESHOLD_1_INT_ENABLE_OFF     (15)
  #define PCU_CR_THERM_INTERRUPT_GT_PCU_THRESHOLD_1_INT_ENABLE_WID     ( 1)
  #define PCU_CR_THERM_INTERRUPT_GT_PCU_THRESHOLD_1_INT_ENABLE_MSK     (0x00008000)
  #define PCU_CR_THERM_INTERRUPT_GT_PCU_THRESHOLD_1_INT_ENABLE_MIN     (0)
  #define PCU_CR_THERM_INTERRUPT_GT_PCU_THRESHOLD_1_INT_ENABLE_MAX     (1) // 0x00000001
  #define PCU_CR_THERM_INTERRUPT_GT_PCU_THRESHOLD_1_INT_ENABLE_DEF     (0x00000000)
  #define PCU_CR_THERM_INTERRUPT_GT_PCU_THRESHOLD_1_INT_ENABLE_HSH     (0x010F59C4)

  #define PCU_CR_THERM_INTERRUPT_GT_PCU_THRESHOLD_2_REL_TEMP_OFF       (16)
  #define PCU_CR_THERM_INTERRUPT_GT_PCU_THRESHOLD_2_REL_TEMP_WID       ( 7)
  #define PCU_CR_THERM_INTERRUPT_GT_PCU_THRESHOLD_2_REL_TEMP_MSK       (0x007F0000)
  #define PCU_CR_THERM_INTERRUPT_GT_PCU_THRESHOLD_2_REL_TEMP_MIN       (0)
  #define PCU_CR_THERM_INTERRUPT_GT_PCU_THRESHOLD_2_REL_TEMP_MAX       (127) // 0x0000007F
  #define PCU_CR_THERM_INTERRUPT_GT_PCU_THRESHOLD_2_REL_TEMP_DEF       (0x00000000)
  #define PCU_CR_THERM_INTERRUPT_GT_PCU_THRESHOLD_2_REL_TEMP_HSH       (0x071059C4)

  #define PCU_CR_THERM_INTERRUPT_GT_PCU_THRESHOLD_2_INT_ENABLE_OFF     (23)
  #define PCU_CR_THERM_INTERRUPT_GT_PCU_THRESHOLD_2_INT_ENABLE_WID     ( 1)
  #define PCU_CR_THERM_INTERRUPT_GT_PCU_THRESHOLD_2_INT_ENABLE_MSK     (0x00800000)
  #define PCU_CR_THERM_INTERRUPT_GT_PCU_THRESHOLD_2_INT_ENABLE_MIN     (0)
  #define PCU_CR_THERM_INTERRUPT_GT_PCU_THRESHOLD_2_INT_ENABLE_MAX     (1) // 0x00000001
  #define PCU_CR_THERM_INTERRUPT_GT_PCU_THRESHOLD_2_INT_ENABLE_DEF     (0x00000000)
  #define PCU_CR_THERM_INTERRUPT_GT_PCU_THRESHOLD_2_INT_ENABLE_HSH     (0x011759C4)

  #define PCU_CR_THERM_INTERRUPT_GT_PCU_POWER_INT_ENABLE_OFF           (24)
  #define PCU_CR_THERM_INTERRUPT_GT_PCU_POWER_INT_ENABLE_WID           ( 1)
  #define PCU_CR_THERM_INTERRUPT_GT_PCU_POWER_INT_ENABLE_MSK           (0x01000000)
  #define PCU_CR_THERM_INTERRUPT_GT_PCU_POWER_INT_ENABLE_MIN           (0)
  #define PCU_CR_THERM_INTERRUPT_GT_PCU_POWER_INT_ENABLE_MAX           (1) // 0x00000001
  #define PCU_CR_THERM_INTERRUPT_GT_PCU_POWER_INT_ENABLE_DEF           (0x00000000)
  #define PCU_CR_THERM_INTERRUPT_GT_PCU_POWER_INT_ENABLE_HSH           (0x011859C4)

#define PCU_CR_DEVICE_IDLE_DURATION_OVERRIDE_PCU_REG                   (0x000059C8)

  #define PCU_CR_DEVICE_IDLE_DURATION_OVERRIDE_PCU_RESERVED_OFF        ( 0)
  #define PCU_CR_DEVICE_IDLE_DURATION_OVERRIDE_PCU_RESERVED_WID        ( 1)
  #define PCU_CR_DEVICE_IDLE_DURATION_OVERRIDE_PCU_RESERVED_MSK        (0x00000001)
  #define PCU_CR_DEVICE_IDLE_DURATION_OVERRIDE_PCU_RESERVED_MIN        (0)
  #define PCU_CR_DEVICE_IDLE_DURATION_OVERRIDE_PCU_RESERVED_MAX        (1) // 0x00000001
  #define PCU_CR_DEVICE_IDLE_DURATION_OVERRIDE_PCU_RESERVED_DEF        (0x00000000)
  #define PCU_CR_DEVICE_IDLE_DURATION_OVERRIDE_PCU_RESERVED_HSH        (0x010059C8)

  #define PCU_CR_DEVICE_IDLE_DURATION_OVERRIDE_PCU_VALID_OFF           ( 1)
  #define PCU_CR_DEVICE_IDLE_DURATION_OVERRIDE_PCU_VALID_WID           ( 1)
  #define PCU_CR_DEVICE_IDLE_DURATION_OVERRIDE_PCU_VALID_MSK           (0x00000002)
  #define PCU_CR_DEVICE_IDLE_DURATION_OVERRIDE_PCU_VALID_MIN           (0)
  #define PCU_CR_DEVICE_IDLE_DURATION_OVERRIDE_PCU_VALID_MAX           (1) // 0x00000001
  #define PCU_CR_DEVICE_IDLE_DURATION_OVERRIDE_PCU_VALID_DEF           (0x00000000)
  #define PCU_CR_DEVICE_IDLE_DURATION_OVERRIDE_PCU_VALID_HSH           (0x010159C8)

  #define PCU_CR_DEVICE_IDLE_DURATION_OVERRIDE_PCU_RESERVED_BITS_OFF   ( 2)
  #define PCU_CR_DEVICE_IDLE_DURATION_OVERRIDE_PCU_RESERVED_BITS_WID   ( 4)
  #define PCU_CR_DEVICE_IDLE_DURATION_OVERRIDE_PCU_RESERVED_BITS_MSK   (0x0000003C)
  #define PCU_CR_DEVICE_IDLE_DURATION_OVERRIDE_PCU_RESERVED_BITS_MIN   (0)
  #define PCU_CR_DEVICE_IDLE_DURATION_OVERRIDE_PCU_RESERVED_BITS_MAX   (15) // 0x0000000F
  #define PCU_CR_DEVICE_IDLE_DURATION_OVERRIDE_PCU_RESERVED_BITS_DEF   (0x00000000)
  #define PCU_CR_DEVICE_IDLE_DURATION_OVERRIDE_PCU_RESERVED_BITS_HSH   (0x040259C8)

  #define PCU_CR_DEVICE_IDLE_DURATION_OVERRIDE_PCU_OD_OFF              ( 6)
  #define PCU_CR_DEVICE_IDLE_DURATION_OVERRIDE_PCU_OD_WID              ( 1)
  #define PCU_CR_DEVICE_IDLE_DURATION_OVERRIDE_PCU_OD_MSK              (0x00000040)
  #define PCU_CR_DEVICE_IDLE_DURATION_OVERRIDE_PCU_OD_MIN              (0)
  #define PCU_CR_DEVICE_IDLE_DURATION_OVERRIDE_PCU_OD_MAX              (1) // 0x00000001
  #define PCU_CR_DEVICE_IDLE_DURATION_OVERRIDE_PCU_OD_DEF              (0x00000000)
  #define PCU_CR_DEVICE_IDLE_DURATION_OVERRIDE_PCU_OD_HSH              (0x010659C8)

  #define PCU_CR_DEVICE_IDLE_DURATION_OVERRIDE_PCU_IM_OFF              ( 7)
  #define PCU_CR_DEVICE_IDLE_DURATION_OVERRIDE_PCU_IM_WID              ( 1)
  #define PCU_CR_DEVICE_IDLE_DURATION_OVERRIDE_PCU_IM_MSK              (0x00000080)
  #define PCU_CR_DEVICE_IDLE_DURATION_OVERRIDE_PCU_IM_MIN              (0)
  #define PCU_CR_DEVICE_IDLE_DURATION_OVERRIDE_PCU_IM_MAX              (1) // 0x00000001
  #define PCU_CR_DEVICE_IDLE_DURATION_OVERRIDE_PCU_IM_DEF              (0x00000000)
  #define PCU_CR_DEVICE_IDLE_DURATION_OVERRIDE_PCU_IM_HSH              (0x010759C8)

  #define PCU_CR_DEVICE_IDLE_DURATION_OVERRIDE_PCU_NEXT_DEVICE_ACTIVITY_OFF ( 8)
  #define PCU_CR_DEVICE_IDLE_DURATION_OVERRIDE_PCU_NEXT_DEVICE_ACTIVITY_WID (21)
  #define PCU_CR_DEVICE_IDLE_DURATION_OVERRIDE_PCU_NEXT_DEVICE_ACTIVITY_MSK (0x1FFFFF00)
  #define PCU_CR_DEVICE_IDLE_DURATION_OVERRIDE_PCU_NEXT_DEVICE_ACTIVITY_MIN (0)
  #define PCU_CR_DEVICE_IDLE_DURATION_OVERRIDE_PCU_NEXT_DEVICE_ACTIVITY_MAX (2097151) // 0x001FFFFF
  #define PCU_CR_DEVICE_IDLE_DURATION_OVERRIDE_PCU_NEXT_DEVICE_ACTIVITY_DEF (0x00000000)
  #define PCU_CR_DEVICE_IDLE_DURATION_OVERRIDE_PCU_NEXT_DEVICE_ACTIVITY_HSH (0x150859C8)

  #define PCU_CR_DEVICE_IDLE_DURATION_OVERRIDE_PCU_DISABLE_MDID_EVALUATION_OFF (29)
  #define PCU_CR_DEVICE_IDLE_DURATION_OVERRIDE_PCU_DISABLE_MDID_EVALUATION_WID ( 1)
  #define PCU_CR_DEVICE_IDLE_DURATION_OVERRIDE_PCU_DISABLE_MDID_EVALUATION_MSK (0x20000000)
  #define PCU_CR_DEVICE_IDLE_DURATION_OVERRIDE_PCU_DISABLE_MDID_EVALUATION_MIN (0)
  #define PCU_CR_DEVICE_IDLE_DURATION_OVERRIDE_PCU_DISABLE_MDID_EVALUATION_MAX (1) // 0x00000001
  #define PCU_CR_DEVICE_IDLE_DURATION_OVERRIDE_PCU_DISABLE_MDID_EVALUATION_DEF (0x00000000)
  #define PCU_CR_DEVICE_IDLE_DURATION_OVERRIDE_PCU_DISABLE_MDID_EVALUATION_HSH (0x011D59C8)

  #define PCU_CR_DEVICE_IDLE_DURATION_OVERRIDE_PCU_FORCE_MDID_OVERRIDE_OFF (30)
  #define PCU_CR_DEVICE_IDLE_DURATION_OVERRIDE_PCU_FORCE_MDID_OVERRIDE_WID ( 1)
  #define PCU_CR_DEVICE_IDLE_DURATION_OVERRIDE_PCU_FORCE_MDID_OVERRIDE_MSK (0x40000000)
  #define PCU_CR_DEVICE_IDLE_DURATION_OVERRIDE_PCU_FORCE_MDID_OVERRIDE_MIN (0)
  #define PCU_CR_DEVICE_IDLE_DURATION_OVERRIDE_PCU_FORCE_MDID_OVERRIDE_MAX (1) // 0x00000001
  #define PCU_CR_DEVICE_IDLE_DURATION_OVERRIDE_PCU_FORCE_MDID_OVERRIDE_DEF (0x00000000)
  #define PCU_CR_DEVICE_IDLE_DURATION_OVERRIDE_PCU_FORCE_MDID_OVERRIDE_HSH (0x011E59C8)

#define PCU_CR_CHAP_CONFIG_PCU_REG                                     (0x00005A00)

  #define PCU_CR_CHAP_CONFIG_PCU_PECI_CMD_OFF                          ( 4)
  #define PCU_CR_CHAP_CONFIG_PCU_PECI_CMD_WID                          ( 8)
  #define PCU_CR_CHAP_CONFIG_PCU_PECI_CMD_MSK                          (0x00000FF0)
  #define PCU_CR_CHAP_CONFIG_PCU_PECI_CMD_MIN                          (0)
  #define PCU_CR_CHAP_CONFIG_PCU_PECI_CMD_MAX                          (255) // 0x000000FF
  #define PCU_CR_CHAP_CONFIG_PCU_PECI_CMD_DEF                          (0x00000000)
  #define PCU_CR_CHAP_CONFIG_PCU_PECI_CMD_HSH                          (0x08045A00)

#define PCU_CR_ENERGY_DEBUG_PCU_REG                                    (0x00005B04)

  #define PCU_CR_ENERGY_DEBUG_PCU_DEBUG_ENERGY_PP0_VALUE_OFF           ( 0)
  #define PCU_CR_ENERGY_DEBUG_PCU_DEBUG_ENERGY_PP0_VALUE_WID           (10)
  #define PCU_CR_ENERGY_DEBUG_PCU_DEBUG_ENERGY_PP0_VALUE_MSK           (0x000003FF)
  #define PCU_CR_ENERGY_DEBUG_PCU_DEBUG_ENERGY_PP0_VALUE_MIN           (0)
  #define PCU_CR_ENERGY_DEBUG_PCU_DEBUG_ENERGY_PP0_VALUE_MAX           (1023) // 0x000003FF
  #define PCU_CR_ENERGY_DEBUG_PCU_DEBUG_ENERGY_PP0_VALUE_DEF           (0x00000000)
  #define PCU_CR_ENERGY_DEBUG_PCU_DEBUG_ENERGY_PP0_VALUE_HSH           (0x0A005B04)

  #define PCU_CR_ENERGY_DEBUG_PCU_DEBUG_ENERGY_PP1_VALUE_OFF           (10)
  #define PCU_CR_ENERGY_DEBUG_PCU_DEBUG_ENERGY_PP1_VALUE_WID           (10)
  #define PCU_CR_ENERGY_DEBUG_PCU_DEBUG_ENERGY_PP1_VALUE_MSK           (0x000FFC00)
  #define PCU_CR_ENERGY_DEBUG_PCU_DEBUG_ENERGY_PP1_VALUE_MIN           (0)
  #define PCU_CR_ENERGY_DEBUG_PCU_DEBUG_ENERGY_PP1_VALUE_MAX           (1023) // 0x000003FF
  #define PCU_CR_ENERGY_DEBUG_PCU_DEBUG_ENERGY_PP1_VALUE_DEF           (0x00000000)
  #define PCU_CR_ENERGY_DEBUG_PCU_DEBUG_ENERGY_PP1_VALUE_HSH           (0x0A0A5B04)

  #define PCU_CR_ENERGY_DEBUG_PCU_DEBUG_ENERGY_SA_VALUE_OFF            (20)
  #define PCU_CR_ENERGY_DEBUG_PCU_DEBUG_ENERGY_SA_VALUE_WID            (10)
  #define PCU_CR_ENERGY_DEBUG_PCU_DEBUG_ENERGY_SA_VALUE_MSK            (0x3FF00000)
  #define PCU_CR_ENERGY_DEBUG_PCU_DEBUG_ENERGY_SA_VALUE_MIN            (0)
  #define PCU_CR_ENERGY_DEBUG_PCU_DEBUG_ENERGY_SA_VALUE_MAX            (1023) // 0x000003FF
  #define PCU_CR_ENERGY_DEBUG_PCU_DEBUG_ENERGY_SA_VALUE_DEF            (0x00000000)
  #define PCU_CR_ENERGY_DEBUG_PCU_DEBUG_ENERGY_SA_VALUE_HSH            (0x0A145B04)

#define PCU_CR_SSKPD_PCU_REG                                           (0x00005D10)

  #define PCU_CR_SSKPD_PCU_SKPD_OFF                                    ( 0)
  #define PCU_CR_SSKPD_PCU_SKPD_WID                                    (64)
  #define PCU_CR_SSKPD_PCU_SKPD_MSK                                    (0xFFFFFFFFFFFFFFFFULL)
  #define PCU_CR_SSKPD_PCU_SKPD_MIN                                    (0)
  #define PCU_CR_SSKPD_PCU_SKPD_MAX                                    (18446744073709551615ULL) // 0xFFFFFFFFFFFFFFFF
  #define PCU_CR_SSKPD_PCU_SKPD_DEF                                    (0x00000000)
  #define PCU_CR_SSKPD_PCU_SKPD_HSH                                    (0x40005D10)

#define PCU_CR_C2C3TT_PCU_REG                                          (0x00005D20)

  #define PCU_CR_C2C3TT_PCU_PPDN_INIT_OFF                              ( 0)
  #define PCU_CR_C2C3TT_PCU_PPDN_INIT_WID                              (12)
  #define PCU_CR_C2C3TT_PCU_PPDN_INIT_MSK                              (0x00000FFF)
  #define PCU_CR_C2C3TT_PCU_PPDN_INIT_MIN                              (0)
  #define PCU_CR_C2C3TT_PCU_PPDN_INIT_MAX                              (4095) // 0x00000FFF
  #define PCU_CR_C2C3TT_PCU_PPDN_INIT_DEF                              (0x00000005)
  #define PCU_CR_C2C3TT_PCU_PPDN_INIT_HSH                              (0x0C005D20)

#define PCU_CR_C2_DDR_TT_PCU_REG                                       (0x00005D24)

  #define PCU_CR_C2_DDR_TT_PCU_DDR_TIMER_VALUE_OFF                     ( 0)
  #define PCU_CR_C2_DDR_TT_PCU_DDR_TIMER_VALUE_WID                     (13)
  #define PCU_CR_C2_DDR_TT_PCU_DDR_TIMER_VALUE_MSK                     (0x00001FFF)
  #define PCU_CR_C2_DDR_TT_PCU_DDR_TIMER_VALUE_MIN                     (0)
  #define PCU_CR_C2_DDR_TT_PCU_DDR_TIMER_VALUE_MAX                     (8191) // 0x00001FFF
  #define PCU_CR_C2_DDR_TT_PCU_DDR_TIMER_VALUE_DEF                     (0x000001F4)
  #define PCU_CR_C2_DDR_TT_PCU_DDR_TIMER_VALUE_HSH                     (0x0D005D24)

#define PCU_CR_PCIE_ILTR_OVRD_PCU_REG                                  (0x00005D30)

  #define PCU_CR_PCIE_ILTR_OVRD_PCU_NSTL_OFF                           ( 0)
  #define PCU_CR_PCIE_ILTR_OVRD_PCU_NSTL_WID                           (10)
  #define PCU_CR_PCIE_ILTR_OVRD_PCU_NSTL_MSK                           (0x000003FF)
  #define PCU_CR_PCIE_ILTR_OVRD_PCU_NSTL_MIN                           (0)
  #define PCU_CR_PCIE_ILTR_OVRD_PCU_NSTL_MAX                           (1023) // 0x000003FF
  #define PCU_CR_PCIE_ILTR_OVRD_PCU_NSTL_DEF                           (0x00000000)
  #define PCU_CR_PCIE_ILTR_OVRD_PCU_NSTL_HSH                           (0x0A005D30)

  #define PCU_CR_PCIE_ILTR_OVRD_PCU_MULTIPLIER_OFF                     (10)
  #define PCU_CR_PCIE_ILTR_OVRD_PCU_MULTIPLIER_WID                     ( 3)
  #define PCU_CR_PCIE_ILTR_OVRD_PCU_MULTIPLIER_MSK                     (0x00001C00)
  #define PCU_CR_PCIE_ILTR_OVRD_PCU_MULTIPLIER_MIN                     (0)
  #define PCU_CR_PCIE_ILTR_OVRD_PCU_MULTIPLIER_MAX                     (7) // 0x00000007
  #define PCU_CR_PCIE_ILTR_OVRD_PCU_MULTIPLIER_DEF                     (0x00000000)
  #define PCU_CR_PCIE_ILTR_OVRD_PCU_MULTIPLIER_HSH                     (0x030A5D30)

  #define PCU_CR_PCIE_ILTR_OVRD_PCU_FORCE_NL_OFF                       (14)
  #define PCU_CR_PCIE_ILTR_OVRD_PCU_FORCE_NL_WID                       ( 1)
  #define PCU_CR_PCIE_ILTR_OVRD_PCU_FORCE_NL_MSK                       (0x00004000)
  #define PCU_CR_PCIE_ILTR_OVRD_PCU_FORCE_NL_MIN                       (0)
  #define PCU_CR_PCIE_ILTR_OVRD_PCU_FORCE_NL_MAX                       (1) // 0x00000001
  #define PCU_CR_PCIE_ILTR_OVRD_PCU_FORCE_NL_DEF                       (0x00000000)
  #define PCU_CR_PCIE_ILTR_OVRD_PCU_FORCE_NL_HSH                       (0x010E5D30)

  #define PCU_CR_PCIE_ILTR_OVRD_PCU_NL_V_OFF                           (15)
  #define PCU_CR_PCIE_ILTR_OVRD_PCU_NL_V_WID                           ( 1)
  #define PCU_CR_PCIE_ILTR_OVRD_PCU_NL_V_MSK                           (0x00008000)
  #define PCU_CR_PCIE_ILTR_OVRD_PCU_NL_V_MIN                           (0)
  #define PCU_CR_PCIE_ILTR_OVRD_PCU_NL_V_MAX                           (1) // 0x00000001
  #define PCU_CR_PCIE_ILTR_OVRD_PCU_NL_V_DEF                           (0x00000000)
  #define PCU_CR_PCIE_ILTR_OVRD_PCU_NL_V_HSH                           (0x010F5D30)

  #define PCU_CR_PCIE_ILTR_OVRD_PCU_SXL_OFF                            (16)
  #define PCU_CR_PCIE_ILTR_OVRD_PCU_SXL_WID                            (10)
  #define PCU_CR_PCIE_ILTR_OVRD_PCU_SXL_MSK                            (0x03FF0000)
  #define PCU_CR_PCIE_ILTR_OVRD_PCU_SXL_MIN                            (0)
  #define PCU_CR_PCIE_ILTR_OVRD_PCU_SXL_MAX                            (1023) // 0x000003FF
  #define PCU_CR_PCIE_ILTR_OVRD_PCU_SXL_DEF                            (0x00000000)
  #define PCU_CR_PCIE_ILTR_OVRD_PCU_SXL_HSH                            (0x0A105D30)

  #define PCU_CR_PCIE_ILTR_OVRD_PCU_SXLM_OFF                           (26)
  #define PCU_CR_PCIE_ILTR_OVRD_PCU_SXLM_WID                           ( 3)
  #define PCU_CR_PCIE_ILTR_OVRD_PCU_SXLM_MSK                           (0x1C000000)
  #define PCU_CR_PCIE_ILTR_OVRD_PCU_SXLM_MIN                           (0)
  #define PCU_CR_PCIE_ILTR_OVRD_PCU_SXLM_MAX                           (7) // 0x00000007
  #define PCU_CR_PCIE_ILTR_OVRD_PCU_SXLM_DEF                           (0x00000000)
  #define PCU_CR_PCIE_ILTR_OVRD_PCU_SXLM_HSH                           (0x031A5D30)

  #define PCU_CR_PCIE_ILTR_OVRD_PCU_FORCE_SXL_OFF                      (30)
  #define PCU_CR_PCIE_ILTR_OVRD_PCU_FORCE_SXL_WID                      ( 1)
  #define PCU_CR_PCIE_ILTR_OVRD_PCU_FORCE_SXL_MSK                      (0x40000000)
  #define PCU_CR_PCIE_ILTR_OVRD_PCU_FORCE_SXL_MIN                      (0)
  #define PCU_CR_PCIE_ILTR_OVRD_PCU_FORCE_SXL_MAX                      (1) // 0x00000001
  #define PCU_CR_PCIE_ILTR_OVRD_PCU_FORCE_SXL_DEF                      (0x00000000)
  #define PCU_CR_PCIE_ILTR_OVRD_PCU_FORCE_SXL_HSH                      (0x011E5D30)

  #define PCU_CR_PCIE_ILTR_OVRD_PCU_SXL_V_OFF                          (31)
  #define PCU_CR_PCIE_ILTR_OVRD_PCU_SXL_V_WID                          ( 1)
  #define PCU_CR_PCIE_ILTR_OVRD_PCU_SXL_V_MSK                          (0x80000000)
  #define PCU_CR_PCIE_ILTR_OVRD_PCU_SXL_V_MIN                          (0)
  #define PCU_CR_PCIE_ILTR_OVRD_PCU_SXL_V_MAX                          (1) // 0x00000001
  #define PCU_CR_PCIE_ILTR_OVRD_PCU_SXL_V_DEF                          (0x00000000)
  #define PCU_CR_PCIE_ILTR_OVRD_PCU_SXL_V_HSH                          (0x011F5D30)

#define PCU_CR_PCIE_ILTR_VAL_PCU_0_REG                                 (0x00005D34)

  #define PCU_CR_PCIE_ILTR_VAL_PCU_0_NL_VALUE_OFF                      ( 0)
  #define PCU_CR_PCIE_ILTR_VAL_PCU_0_NL_VALUE_WID                      (10)
  #define PCU_CR_PCIE_ILTR_VAL_PCU_0_NL_VALUE_MSK                      (0x000003FF)
  #define PCU_CR_PCIE_ILTR_VAL_PCU_0_NL_VALUE_MIN                      (0)
  #define PCU_CR_PCIE_ILTR_VAL_PCU_0_NL_VALUE_MAX                      (1023) // 0x000003FF
  #define PCU_CR_PCIE_ILTR_VAL_PCU_0_NL_VALUE_DEF                      (0x00000000)
  #define PCU_CR_PCIE_ILTR_VAL_PCU_0_NL_VALUE_HSH                      (0x0A005D34)

  #define PCU_CR_PCIE_ILTR_VAL_PCU_0_NL_SCALE_OFF                      (10)
  #define PCU_CR_PCIE_ILTR_VAL_PCU_0_NL_SCALE_WID                      ( 3)
  #define PCU_CR_PCIE_ILTR_VAL_PCU_0_NL_SCALE_MSK                      (0x00001C00)
  #define PCU_CR_PCIE_ILTR_VAL_PCU_0_NL_SCALE_MIN                      (0)
  #define PCU_CR_PCIE_ILTR_VAL_PCU_0_NL_SCALE_MAX                      (7) // 0x00000007
  #define PCU_CR_PCIE_ILTR_VAL_PCU_0_NL_SCALE_DEF                      (0x00000000)
  #define PCU_CR_PCIE_ILTR_VAL_PCU_0_NL_SCALE_HSH                      (0x030A5D34)

  #define PCU_CR_PCIE_ILTR_VAL_PCU_0_NL_RESERVED_OFF                   (13)
  #define PCU_CR_PCIE_ILTR_VAL_PCU_0_NL_RESERVED_WID                   ( 2)
  #define PCU_CR_PCIE_ILTR_VAL_PCU_0_NL_RESERVED_MSK                   (0x00006000)
  #define PCU_CR_PCIE_ILTR_VAL_PCU_0_NL_RESERVED_MIN                   (0)
  #define PCU_CR_PCIE_ILTR_VAL_PCU_0_NL_RESERVED_MAX                   (3) // 0x00000003
  #define PCU_CR_PCIE_ILTR_VAL_PCU_0_NL_RESERVED_DEF                   (0x00000000)
  #define PCU_CR_PCIE_ILTR_VAL_PCU_0_NL_RESERVED_HSH                   (0x020D5D34)

  #define PCU_CR_PCIE_ILTR_VAL_PCU_0_NL_VALID_OFF                      (15)
  #define PCU_CR_PCIE_ILTR_VAL_PCU_0_NL_VALID_WID                      ( 1)
  #define PCU_CR_PCIE_ILTR_VAL_PCU_0_NL_VALID_MSK                      (0x00008000)
  #define PCU_CR_PCIE_ILTR_VAL_PCU_0_NL_VALID_MIN                      (0)
  #define PCU_CR_PCIE_ILTR_VAL_PCU_0_NL_VALID_MAX                      (1) // 0x00000001
  #define PCU_CR_PCIE_ILTR_VAL_PCU_0_NL_VALID_DEF                      (0x00000000)
  #define PCU_CR_PCIE_ILTR_VAL_PCU_0_NL_VALID_HSH                      (0x010F5D34)

  #define PCU_CR_PCIE_ILTR_VAL_PCU_0_SXL_VALUE_OFF                     (16)
  #define PCU_CR_PCIE_ILTR_VAL_PCU_0_SXL_VALUE_WID                     (10)
  #define PCU_CR_PCIE_ILTR_VAL_PCU_0_SXL_VALUE_MSK                     (0x03FF0000)
  #define PCU_CR_PCIE_ILTR_VAL_PCU_0_SXL_VALUE_MIN                     (0)
  #define PCU_CR_PCIE_ILTR_VAL_PCU_0_SXL_VALUE_MAX                     (1023) // 0x000003FF
  #define PCU_CR_PCIE_ILTR_VAL_PCU_0_SXL_VALUE_DEF                     (0x00000000)
  #define PCU_CR_PCIE_ILTR_VAL_PCU_0_SXL_VALUE_HSH                     (0x0A105D34)

  #define PCU_CR_PCIE_ILTR_VAL_PCU_0_SXL_SCALE_OFF                     (26)
  #define PCU_CR_PCIE_ILTR_VAL_PCU_0_SXL_SCALE_WID                     ( 3)
  #define PCU_CR_PCIE_ILTR_VAL_PCU_0_SXL_SCALE_MSK                     (0x1C000000)
  #define PCU_CR_PCIE_ILTR_VAL_PCU_0_SXL_SCALE_MIN                     (0)
  #define PCU_CR_PCIE_ILTR_VAL_PCU_0_SXL_SCALE_MAX                     (7) // 0x00000007
  #define PCU_CR_PCIE_ILTR_VAL_PCU_0_SXL_SCALE_DEF                     (0x00000000)
  #define PCU_CR_PCIE_ILTR_VAL_PCU_0_SXL_SCALE_HSH                     (0x031A5D34)

  #define PCU_CR_PCIE_ILTR_VAL_PCU_0_SXL_RESERVED_OFF                  (29)
  #define PCU_CR_PCIE_ILTR_VAL_PCU_0_SXL_RESERVED_WID                  ( 2)
  #define PCU_CR_PCIE_ILTR_VAL_PCU_0_SXL_RESERVED_MSK                  (0x60000000)
  #define PCU_CR_PCIE_ILTR_VAL_PCU_0_SXL_RESERVED_MIN                  (0)
  #define PCU_CR_PCIE_ILTR_VAL_PCU_0_SXL_RESERVED_MAX                  (3) // 0x00000003
  #define PCU_CR_PCIE_ILTR_VAL_PCU_0_SXL_RESERVED_DEF                  (0x00000000)
  #define PCU_CR_PCIE_ILTR_VAL_PCU_0_SXL_RESERVED_HSH                  (0x021D5D34)

  #define PCU_CR_PCIE_ILTR_VAL_PCU_0_SXL_VALID_OFF                     (31)
  #define PCU_CR_PCIE_ILTR_VAL_PCU_0_SXL_VALID_WID                     ( 1)
  #define PCU_CR_PCIE_ILTR_VAL_PCU_0_SXL_VALID_MSK                     (0x80000000)
  #define PCU_CR_PCIE_ILTR_VAL_PCU_0_SXL_VALID_MIN                     (0)
  #define PCU_CR_PCIE_ILTR_VAL_PCU_0_SXL_VALID_MAX                     (1) // 0x00000001
  #define PCU_CR_PCIE_ILTR_VAL_PCU_0_SXL_VALID_DEF                     (0x00000000)
  #define PCU_CR_PCIE_ILTR_VAL_PCU_0_SXL_VALID_HSH                     (0x011F5D34)

#define PCU_CR_PCIE_ILTR_VAL_PCU_1_REG                                 (0x00005D38)

  #define PCU_CR_PCIE_ILTR_VAL_PCU_1_NL_VALUE_OFF                      ( 0)
  #define PCU_CR_PCIE_ILTR_VAL_PCU_1_NL_VALUE_WID                      (10)
  #define PCU_CR_PCIE_ILTR_VAL_PCU_1_NL_VALUE_MSK                      (0x000003FF)
  #define PCU_CR_PCIE_ILTR_VAL_PCU_1_NL_VALUE_MIN                      (0)
  #define PCU_CR_PCIE_ILTR_VAL_PCU_1_NL_VALUE_MAX                      (1023) // 0x000003FF
  #define PCU_CR_PCIE_ILTR_VAL_PCU_1_NL_VALUE_DEF                      (0x00000000)
  #define PCU_CR_PCIE_ILTR_VAL_PCU_1_NL_VALUE_HSH                      (0x0A005D38)

  #define PCU_CR_PCIE_ILTR_VAL_PCU_1_NL_SCALE_OFF                      (10)
  #define PCU_CR_PCIE_ILTR_VAL_PCU_1_NL_SCALE_WID                      ( 3)
  #define PCU_CR_PCIE_ILTR_VAL_PCU_1_NL_SCALE_MSK                      (0x00001C00)
  #define PCU_CR_PCIE_ILTR_VAL_PCU_1_NL_SCALE_MIN                      (0)
  #define PCU_CR_PCIE_ILTR_VAL_PCU_1_NL_SCALE_MAX                      (7) // 0x00000007
  #define PCU_CR_PCIE_ILTR_VAL_PCU_1_NL_SCALE_DEF                      (0x00000000)
  #define PCU_CR_PCIE_ILTR_VAL_PCU_1_NL_SCALE_HSH                      (0x030A5D38)

  #define PCU_CR_PCIE_ILTR_VAL_PCU_1_NL_RESERVED_OFF                   (13)
  #define PCU_CR_PCIE_ILTR_VAL_PCU_1_NL_RESERVED_WID                   ( 2)
  #define PCU_CR_PCIE_ILTR_VAL_PCU_1_NL_RESERVED_MSK                   (0x00006000)
  #define PCU_CR_PCIE_ILTR_VAL_PCU_1_NL_RESERVED_MIN                   (0)
  #define PCU_CR_PCIE_ILTR_VAL_PCU_1_NL_RESERVED_MAX                   (3) // 0x00000003
  #define PCU_CR_PCIE_ILTR_VAL_PCU_1_NL_RESERVED_DEF                   (0x00000000)
  #define PCU_CR_PCIE_ILTR_VAL_PCU_1_NL_RESERVED_HSH                   (0x020D5D38)

  #define PCU_CR_PCIE_ILTR_VAL_PCU_1_NL_VALID_OFF                      (15)
  #define PCU_CR_PCIE_ILTR_VAL_PCU_1_NL_VALID_WID                      ( 1)
  #define PCU_CR_PCIE_ILTR_VAL_PCU_1_NL_VALID_MSK                      (0x00008000)
  #define PCU_CR_PCIE_ILTR_VAL_PCU_1_NL_VALID_MIN                      (0)
  #define PCU_CR_PCIE_ILTR_VAL_PCU_1_NL_VALID_MAX                      (1) // 0x00000001
  #define PCU_CR_PCIE_ILTR_VAL_PCU_1_NL_VALID_DEF                      (0x00000000)
  #define PCU_CR_PCIE_ILTR_VAL_PCU_1_NL_VALID_HSH                      (0x010F5D38)

  #define PCU_CR_PCIE_ILTR_VAL_PCU_1_SXL_VALUE_OFF                     (16)
  #define PCU_CR_PCIE_ILTR_VAL_PCU_1_SXL_VALUE_WID                     (10)
  #define PCU_CR_PCIE_ILTR_VAL_PCU_1_SXL_VALUE_MSK                     (0x03FF0000)
  #define PCU_CR_PCIE_ILTR_VAL_PCU_1_SXL_VALUE_MIN                     (0)
  #define PCU_CR_PCIE_ILTR_VAL_PCU_1_SXL_VALUE_MAX                     (1023) // 0x000003FF
  #define PCU_CR_PCIE_ILTR_VAL_PCU_1_SXL_VALUE_DEF                     (0x00000000)
  #define PCU_CR_PCIE_ILTR_VAL_PCU_1_SXL_VALUE_HSH                     (0x0A105D38)

  #define PCU_CR_PCIE_ILTR_VAL_PCU_1_SXL_SCALE_OFF                     (26)
  #define PCU_CR_PCIE_ILTR_VAL_PCU_1_SXL_SCALE_WID                     ( 3)
  #define PCU_CR_PCIE_ILTR_VAL_PCU_1_SXL_SCALE_MSK                     (0x1C000000)
  #define PCU_CR_PCIE_ILTR_VAL_PCU_1_SXL_SCALE_MIN                     (0)
  #define PCU_CR_PCIE_ILTR_VAL_PCU_1_SXL_SCALE_MAX                     (7) // 0x00000007
  #define PCU_CR_PCIE_ILTR_VAL_PCU_1_SXL_SCALE_DEF                     (0x00000000)
  #define PCU_CR_PCIE_ILTR_VAL_PCU_1_SXL_SCALE_HSH                     (0x031A5D38)

  #define PCU_CR_PCIE_ILTR_VAL_PCU_1_SXL_RESERVED_OFF                  (29)
  #define PCU_CR_PCIE_ILTR_VAL_PCU_1_SXL_RESERVED_WID                  ( 2)
  #define PCU_CR_PCIE_ILTR_VAL_PCU_1_SXL_RESERVED_MSK                  (0x60000000)
  #define PCU_CR_PCIE_ILTR_VAL_PCU_1_SXL_RESERVED_MIN                  (0)
  #define PCU_CR_PCIE_ILTR_VAL_PCU_1_SXL_RESERVED_MAX                  (3) // 0x00000003
  #define PCU_CR_PCIE_ILTR_VAL_PCU_1_SXL_RESERVED_DEF                  (0x00000000)
  #define PCU_CR_PCIE_ILTR_VAL_PCU_1_SXL_RESERVED_HSH                  (0x021D5D38)

  #define PCU_CR_PCIE_ILTR_VAL_PCU_1_SXL_VALID_OFF                     (31)
  #define PCU_CR_PCIE_ILTR_VAL_PCU_1_SXL_VALID_WID                     ( 1)
  #define PCU_CR_PCIE_ILTR_VAL_PCU_1_SXL_VALID_MSK                     (0x80000000)
  #define PCU_CR_PCIE_ILTR_VAL_PCU_1_SXL_VALID_MIN                     (0)
  #define PCU_CR_PCIE_ILTR_VAL_PCU_1_SXL_VALID_MAX                     (1) // 0x00000001
  #define PCU_CR_PCIE_ILTR_VAL_PCU_1_SXL_VALID_DEF                     (0x00000000)
  #define PCU_CR_PCIE_ILTR_VAL_PCU_1_SXL_VALID_HSH                     (0x011F5D38)

#define PCU_CR_PCIE_ILTR_VAL_PCU_2_REG                                 (0x00005D3C)

  #define PCU_CR_PCIE_ILTR_VAL_PCU_2_NL_VALUE_OFF                      ( 0)
  #define PCU_CR_PCIE_ILTR_VAL_PCU_2_NL_VALUE_WID                      (10)
  #define PCU_CR_PCIE_ILTR_VAL_PCU_2_NL_VALUE_MSK                      (0x000003FF)
  #define PCU_CR_PCIE_ILTR_VAL_PCU_2_NL_VALUE_MIN                      (0)
  #define PCU_CR_PCIE_ILTR_VAL_PCU_2_NL_VALUE_MAX                      (1023) // 0x000003FF
  #define PCU_CR_PCIE_ILTR_VAL_PCU_2_NL_VALUE_DEF                      (0x00000000)
  #define PCU_CR_PCIE_ILTR_VAL_PCU_2_NL_VALUE_HSH                      (0x0A005D3C)

  #define PCU_CR_PCIE_ILTR_VAL_PCU_2_NL_SCALE_OFF                      (10)
  #define PCU_CR_PCIE_ILTR_VAL_PCU_2_NL_SCALE_WID                      ( 3)
  #define PCU_CR_PCIE_ILTR_VAL_PCU_2_NL_SCALE_MSK                      (0x00001C00)
  #define PCU_CR_PCIE_ILTR_VAL_PCU_2_NL_SCALE_MIN                      (0)
  #define PCU_CR_PCIE_ILTR_VAL_PCU_2_NL_SCALE_MAX                      (7) // 0x00000007
  #define PCU_CR_PCIE_ILTR_VAL_PCU_2_NL_SCALE_DEF                      (0x00000000)
  #define PCU_CR_PCIE_ILTR_VAL_PCU_2_NL_SCALE_HSH                      (0x030A5D3C)

  #define PCU_CR_PCIE_ILTR_VAL_PCU_2_NL_RESERVED_OFF                   (13)
  #define PCU_CR_PCIE_ILTR_VAL_PCU_2_NL_RESERVED_WID                   ( 2)
  #define PCU_CR_PCIE_ILTR_VAL_PCU_2_NL_RESERVED_MSK                   (0x00006000)
  #define PCU_CR_PCIE_ILTR_VAL_PCU_2_NL_RESERVED_MIN                   (0)
  #define PCU_CR_PCIE_ILTR_VAL_PCU_2_NL_RESERVED_MAX                   (3) // 0x00000003
  #define PCU_CR_PCIE_ILTR_VAL_PCU_2_NL_RESERVED_DEF                   (0x00000000)
  #define PCU_CR_PCIE_ILTR_VAL_PCU_2_NL_RESERVED_HSH                   (0x020D5D3C)

  #define PCU_CR_PCIE_ILTR_VAL_PCU_2_NL_VALID_OFF                      (15)
  #define PCU_CR_PCIE_ILTR_VAL_PCU_2_NL_VALID_WID                      ( 1)
  #define PCU_CR_PCIE_ILTR_VAL_PCU_2_NL_VALID_MSK                      (0x00008000)
  #define PCU_CR_PCIE_ILTR_VAL_PCU_2_NL_VALID_MIN                      (0)
  #define PCU_CR_PCIE_ILTR_VAL_PCU_2_NL_VALID_MAX                      (1) // 0x00000001
  #define PCU_CR_PCIE_ILTR_VAL_PCU_2_NL_VALID_DEF                      (0x00000000)
  #define PCU_CR_PCIE_ILTR_VAL_PCU_2_NL_VALID_HSH                      (0x010F5D3C)

  #define PCU_CR_PCIE_ILTR_VAL_PCU_2_SXL_VALUE_OFF                     (16)
  #define PCU_CR_PCIE_ILTR_VAL_PCU_2_SXL_VALUE_WID                     (10)
  #define PCU_CR_PCIE_ILTR_VAL_PCU_2_SXL_VALUE_MSK                     (0x03FF0000)
  #define PCU_CR_PCIE_ILTR_VAL_PCU_2_SXL_VALUE_MIN                     (0)
  #define PCU_CR_PCIE_ILTR_VAL_PCU_2_SXL_VALUE_MAX                     (1023) // 0x000003FF
  #define PCU_CR_PCIE_ILTR_VAL_PCU_2_SXL_VALUE_DEF                     (0x00000000)
  #define PCU_CR_PCIE_ILTR_VAL_PCU_2_SXL_VALUE_HSH                     (0x0A105D3C)

  #define PCU_CR_PCIE_ILTR_VAL_PCU_2_SXL_SCALE_OFF                     (26)
  #define PCU_CR_PCIE_ILTR_VAL_PCU_2_SXL_SCALE_WID                     ( 3)
  #define PCU_CR_PCIE_ILTR_VAL_PCU_2_SXL_SCALE_MSK                     (0x1C000000)
  #define PCU_CR_PCIE_ILTR_VAL_PCU_2_SXL_SCALE_MIN                     (0)
  #define PCU_CR_PCIE_ILTR_VAL_PCU_2_SXL_SCALE_MAX                     (7) // 0x00000007
  #define PCU_CR_PCIE_ILTR_VAL_PCU_2_SXL_SCALE_DEF                     (0x00000000)
  #define PCU_CR_PCIE_ILTR_VAL_PCU_2_SXL_SCALE_HSH                     (0x031A5D3C)

  #define PCU_CR_PCIE_ILTR_VAL_PCU_2_SXL_RESERVED_OFF                  (29)
  #define PCU_CR_PCIE_ILTR_VAL_PCU_2_SXL_RESERVED_WID                  ( 2)
  #define PCU_CR_PCIE_ILTR_VAL_PCU_2_SXL_RESERVED_MSK                  (0x60000000)
  #define PCU_CR_PCIE_ILTR_VAL_PCU_2_SXL_RESERVED_MIN                  (0)
  #define PCU_CR_PCIE_ILTR_VAL_PCU_2_SXL_RESERVED_MAX                  (3) // 0x00000003
  #define PCU_CR_PCIE_ILTR_VAL_PCU_2_SXL_RESERVED_DEF                  (0x00000000)
  #define PCU_CR_PCIE_ILTR_VAL_PCU_2_SXL_RESERVED_HSH                  (0x021D5D3C)

  #define PCU_CR_PCIE_ILTR_VAL_PCU_2_SXL_VALID_OFF                     (31)
  #define PCU_CR_PCIE_ILTR_VAL_PCU_2_SXL_VALID_WID                     ( 1)
  #define PCU_CR_PCIE_ILTR_VAL_PCU_2_SXL_VALID_MSK                     (0x80000000)
  #define PCU_CR_PCIE_ILTR_VAL_PCU_2_SXL_VALID_MIN                     (0)
  #define PCU_CR_PCIE_ILTR_VAL_PCU_2_SXL_VALID_MAX                     (1) // 0x00000001
  #define PCU_CR_PCIE_ILTR_VAL_PCU_2_SXL_VALID_DEF                     (0x00000000)
  #define PCU_CR_PCIE_ILTR_VAL_PCU_2_SXL_VALID_HSH                     (0x011F5D3C)

#define PCU_CR_VISA_CTL_PTPCFSMS_PCU_REG                               (0x00005D40)

  #define PCU_CR_VISA_CTL_PTPCFSMS_PCU_EN_CLK_OFF                      ( 0)
  #define PCU_CR_VISA_CTL_PTPCFSMS_PCU_EN_CLK_WID                      ( 1)
  #define PCU_CR_VISA_CTL_PTPCFSMS_PCU_EN_CLK_MSK                      (0x00000001)
  #define PCU_CR_VISA_CTL_PTPCFSMS_PCU_EN_CLK_MIN                      (0)
  #define PCU_CR_VISA_CTL_PTPCFSMS_PCU_EN_CLK_MAX                      (1) // 0x00000001
  #define PCU_CR_VISA_CTL_PTPCFSMS_PCU_EN_CLK_DEF                      (0x00000000)
  #define PCU_CR_VISA_CTL_PTPCFSMS_PCU_EN_CLK_HSH                      (0x01005D40)

  #define PCU_CR_VISA_CTL_PTPCFSMS_PCU_L0_DATA_BYTE_SEL_OFF            ( 1)
  #define PCU_CR_VISA_CTL_PTPCFSMS_PCU_L0_DATA_BYTE_SEL_WID            ( 7)
  #define PCU_CR_VISA_CTL_PTPCFSMS_PCU_L0_DATA_BYTE_SEL_MSK            (0x000000FE)
  #define PCU_CR_VISA_CTL_PTPCFSMS_PCU_L0_DATA_BYTE_SEL_MIN            (0)
  #define PCU_CR_VISA_CTL_PTPCFSMS_PCU_L0_DATA_BYTE_SEL_MAX            (127) // 0x0000007F
  #define PCU_CR_VISA_CTL_PTPCFSMS_PCU_L0_DATA_BYTE_SEL_DEF            (0x00000000)
  #define PCU_CR_VISA_CTL_PTPCFSMS_PCU_L0_DATA_BYTE_SEL_HSH            (0x07015D40)

  #define PCU_CR_VISA_CTL_PTPCFSMS_PCU_L0_BYP_SEL_OFF                  ( 8)
  #define PCU_CR_VISA_CTL_PTPCFSMS_PCU_L0_BYP_SEL_WID                  ( 1)
  #define PCU_CR_VISA_CTL_PTPCFSMS_PCU_L0_BYP_SEL_MSK                  (0x00000100)
  #define PCU_CR_VISA_CTL_PTPCFSMS_PCU_L0_BYP_SEL_MIN                  (0)
  #define PCU_CR_VISA_CTL_PTPCFSMS_PCU_L0_BYP_SEL_MAX                  (1) // 0x00000001
  #define PCU_CR_VISA_CTL_PTPCFSMS_PCU_L0_BYP_SEL_DEF                  (0x00000000)
  #define PCU_CR_VISA_CTL_PTPCFSMS_PCU_L0_BYP_SEL_HSH                  (0x01085D40)

  #define PCU_CR_VISA_CTL_PTPCFSMS_PCU_L1_DATA_BYTE_SEL_OFF            ( 9)
  #define PCU_CR_VISA_CTL_PTPCFSMS_PCU_L1_DATA_BYTE_SEL_WID            ( 7)
  #define PCU_CR_VISA_CTL_PTPCFSMS_PCU_L1_DATA_BYTE_SEL_MSK            (0x0000FE00)
  #define PCU_CR_VISA_CTL_PTPCFSMS_PCU_L1_DATA_BYTE_SEL_MIN            (0)
  #define PCU_CR_VISA_CTL_PTPCFSMS_PCU_L1_DATA_BYTE_SEL_MAX            (127) // 0x0000007F
  #define PCU_CR_VISA_CTL_PTPCFSMS_PCU_L1_DATA_BYTE_SEL_DEF            (0x00000000)
  #define PCU_CR_VISA_CTL_PTPCFSMS_PCU_L1_DATA_BYTE_SEL_HSH            (0x07095D40)

  #define PCU_CR_VISA_CTL_PTPCFSMS_PCU_L1_BYP_SEL_OFF                  (16)
  #define PCU_CR_VISA_CTL_PTPCFSMS_PCU_L1_BYP_SEL_WID                  ( 1)
  #define PCU_CR_VISA_CTL_PTPCFSMS_PCU_L1_BYP_SEL_MSK                  (0x00010000)
  #define PCU_CR_VISA_CTL_PTPCFSMS_PCU_L1_BYP_SEL_MIN                  (0)
  #define PCU_CR_VISA_CTL_PTPCFSMS_PCU_L1_BYP_SEL_MAX                  (1) // 0x00000001
  #define PCU_CR_VISA_CTL_PTPCFSMS_PCU_L1_BYP_SEL_DEF                  (0x00000000)
  #define PCU_CR_VISA_CTL_PTPCFSMS_PCU_L1_BYP_SEL_HSH                  (0x01105D40)

  #define PCU_CR_VISA_CTL_PTPCFSMS_PCU_VORANGE_OFF                     (31)
  #define PCU_CR_VISA_CTL_PTPCFSMS_PCU_VORANGE_WID                     ( 1)
  #define PCU_CR_VISA_CTL_PTPCFSMS_PCU_VORANGE_MSK                     (0x80000000)
  #define PCU_CR_VISA_CTL_PTPCFSMS_PCU_VORANGE_MIN                     (0)
  #define PCU_CR_VISA_CTL_PTPCFSMS_PCU_VORANGE_MAX                     (1) // 0x00000001
  #define PCU_CR_VISA_CTL_PTPCFSMS_PCU_VORANGE_DEF                     (0x00000000)
  #define PCU_CR_VISA_CTL_PTPCFSMS_PCU_VORANGE_HSH                     (0x011F5D40)

#define PCU_CR_VISA_XBAR_PTPCFSMS_PCU_REG                              (0x00005D44)

  #define PCU_CR_VISA_XBAR_PTPCFSMS_PCU_FXB_Li_BIT0_DATA_BIT_SEL_OFF   ( 0)
  #define PCU_CR_VISA_XBAR_PTPCFSMS_PCU_FXB_Li_BIT0_DATA_BIT_SEL_WID   ( 3)
  #define PCU_CR_VISA_XBAR_PTPCFSMS_PCU_FXB_Li_BIT0_DATA_BIT_SEL_MSK   (0x00000007)
  #define PCU_CR_VISA_XBAR_PTPCFSMS_PCU_FXB_Li_BIT0_DATA_BIT_SEL_MIN   (0)
  #define PCU_CR_VISA_XBAR_PTPCFSMS_PCU_FXB_Li_BIT0_DATA_BIT_SEL_MAX   (7) // 0x00000007
  #define PCU_CR_VISA_XBAR_PTPCFSMS_PCU_FXB_Li_BIT0_DATA_BIT_SEL_DEF   (0x00000000)
  #define PCU_CR_VISA_XBAR_PTPCFSMS_PCU_FXB_Li_BIT0_DATA_BIT_SEL_HSH   (0x03005D44)

  #define PCU_CR_VISA_XBAR_PTPCFSMS_PCU_FXB_Li_BIT0_DATA_BYTE_SEL_OFF  ( 3)
  #define PCU_CR_VISA_XBAR_PTPCFSMS_PCU_FXB_Li_BIT0_DATA_BYTE_SEL_WID  ( 1)
  #define PCU_CR_VISA_XBAR_PTPCFSMS_PCU_FXB_Li_BIT0_DATA_BYTE_SEL_MSK  (0x00000008)
  #define PCU_CR_VISA_XBAR_PTPCFSMS_PCU_FXB_Li_BIT0_DATA_BYTE_SEL_MIN  (0)
  #define PCU_CR_VISA_XBAR_PTPCFSMS_PCU_FXB_Li_BIT0_DATA_BYTE_SEL_MAX  (1) // 0x00000001
  #define PCU_CR_VISA_XBAR_PTPCFSMS_PCU_FXB_Li_BIT0_DATA_BYTE_SEL_DEF  (0x00000000)
  #define PCU_CR_VISA_XBAR_PTPCFSMS_PCU_FXB_Li_BIT0_DATA_BYTE_SEL_HSH  (0x01035D44)

  #define PCU_CR_VISA_XBAR_PTPCFSMS_PCU_FXB_Li_BIT1_DATA_BIT_SEL_OFF   ( 4)
  #define PCU_CR_VISA_XBAR_PTPCFSMS_PCU_FXB_Li_BIT1_DATA_BIT_SEL_WID   ( 3)
  #define PCU_CR_VISA_XBAR_PTPCFSMS_PCU_FXB_Li_BIT1_DATA_BIT_SEL_MSK   (0x00000070)
  #define PCU_CR_VISA_XBAR_PTPCFSMS_PCU_FXB_Li_BIT1_DATA_BIT_SEL_MIN   (0)
  #define PCU_CR_VISA_XBAR_PTPCFSMS_PCU_FXB_Li_BIT1_DATA_BIT_SEL_MAX   (7) // 0x00000007
  #define PCU_CR_VISA_XBAR_PTPCFSMS_PCU_FXB_Li_BIT1_DATA_BIT_SEL_DEF   (0x00000001)
  #define PCU_CR_VISA_XBAR_PTPCFSMS_PCU_FXB_Li_BIT1_DATA_BIT_SEL_HSH   (0x03045D44)

  #define PCU_CR_VISA_XBAR_PTPCFSMS_PCU_FXB_Li_BIT1_DATA_BYTE_SEL_OFF  ( 7)
  #define PCU_CR_VISA_XBAR_PTPCFSMS_PCU_FXB_Li_BIT1_DATA_BYTE_SEL_WID  ( 1)
  #define PCU_CR_VISA_XBAR_PTPCFSMS_PCU_FXB_Li_BIT1_DATA_BYTE_SEL_MSK  (0x00000080)
  #define PCU_CR_VISA_XBAR_PTPCFSMS_PCU_FXB_Li_BIT1_DATA_BYTE_SEL_MIN  (0)
  #define PCU_CR_VISA_XBAR_PTPCFSMS_PCU_FXB_Li_BIT1_DATA_BYTE_SEL_MAX  (1) // 0x00000001
  #define PCU_CR_VISA_XBAR_PTPCFSMS_PCU_FXB_Li_BIT1_DATA_BYTE_SEL_DEF  (0x00000000)
  #define PCU_CR_VISA_XBAR_PTPCFSMS_PCU_FXB_Li_BIT1_DATA_BYTE_SEL_HSH  (0x01075D44)

  #define PCU_CR_VISA_XBAR_PTPCFSMS_PCU_FXB_Li_BIT2_DATA_BIT_SEL_OFF   ( 8)
  #define PCU_CR_VISA_XBAR_PTPCFSMS_PCU_FXB_Li_BIT2_DATA_BIT_SEL_WID   ( 3)
  #define PCU_CR_VISA_XBAR_PTPCFSMS_PCU_FXB_Li_BIT2_DATA_BIT_SEL_MSK   (0x00000700)
  #define PCU_CR_VISA_XBAR_PTPCFSMS_PCU_FXB_Li_BIT2_DATA_BIT_SEL_MIN   (0)
  #define PCU_CR_VISA_XBAR_PTPCFSMS_PCU_FXB_Li_BIT2_DATA_BIT_SEL_MAX   (7) // 0x00000007
  #define PCU_CR_VISA_XBAR_PTPCFSMS_PCU_FXB_Li_BIT2_DATA_BIT_SEL_DEF   (0x00000002)
  #define PCU_CR_VISA_XBAR_PTPCFSMS_PCU_FXB_Li_BIT2_DATA_BIT_SEL_HSH   (0x03085D44)

  #define PCU_CR_VISA_XBAR_PTPCFSMS_PCU_FXB_Li_BIT2_DATA_BYTE_SEL_OFF  (11)
  #define PCU_CR_VISA_XBAR_PTPCFSMS_PCU_FXB_Li_BIT2_DATA_BYTE_SEL_WID  ( 1)
  #define PCU_CR_VISA_XBAR_PTPCFSMS_PCU_FXB_Li_BIT2_DATA_BYTE_SEL_MSK  (0x00000800)
  #define PCU_CR_VISA_XBAR_PTPCFSMS_PCU_FXB_Li_BIT2_DATA_BYTE_SEL_MIN  (0)
  #define PCU_CR_VISA_XBAR_PTPCFSMS_PCU_FXB_Li_BIT2_DATA_BYTE_SEL_MAX  (1) // 0x00000001
  #define PCU_CR_VISA_XBAR_PTPCFSMS_PCU_FXB_Li_BIT2_DATA_BYTE_SEL_DEF  (0x00000000)
  #define PCU_CR_VISA_XBAR_PTPCFSMS_PCU_FXB_Li_BIT2_DATA_BYTE_SEL_HSH  (0x010B5D44)

  #define PCU_CR_VISA_XBAR_PTPCFSMS_PCU_FXB_Li_BIT3_DATA_BIT_SEL_OFF   (12)
  #define PCU_CR_VISA_XBAR_PTPCFSMS_PCU_FXB_Li_BIT3_DATA_BIT_SEL_WID   ( 3)
  #define PCU_CR_VISA_XBAR_PTPCFSMS_PCU_FXB_Li_BIT3_DATA_BIT_SEL_MSK   (0x00007000)
  #define PCU_CR_VISA_XBAR_PTPCFSMS_PCU_FXB_Li_BIT3_DATA_BIT_SEL_MIN   (0)
  #define PCU_CR_VISA_XBAR_PTPCFSMS_PCU_FXB_Li_BIT3_DATA_BIT_SEL_MAX   (7) // 0x00000007
  #define PCU_CR_VISA_XBAR_PTPCFSMS_PCU_FXB_Li_BIT3_DATA_BIT_SEL_DEF   (0x00000003)
  #define PCU_CR_VISA_XBAR_PTPCFSMS_PCU_FXB_Li_BIT3_DATA_BIT_SEL_HSH   (0x030C5D44)

  #define PCU_CR_VISA_XBAR_PTPCFSMS_PCU_FXB_Li_BIT3_DATA_BYTE_SEL_OFF  (15)
  #define PCU_CR_VISA_XBAR_PTPCFSMS_PCU_FXB_Li_BIT3_DATA_BYTE_SEL_WID  ( 1)
  #define PCU_CR_VISA_XBAR_PTPCFSMS_PCU_FXB_Li_BIT3_DATA_BYTE_SEL_MSK  (0x00008000)
  #define PCU_CR_VISA_XBAR_PTPCFSMS_PCU_FXB_Li_BIT3_DATA_BYTE_SEL_MIN  (0)
  #define PCU_CR_VISA_XBAR_PTPCFSMS_PCU_FXB_Li_BIT3_DATA_BYTE_SEL_MAX  (1) // 0x00000001
  #define PCU_CR_VISA_XBAR_PTPCFSMS_PCU_FXB_Li_BIT3_DATA_BYTE_SEL_DEF  (0x00000000)
  #define PCU_CR_VISA_XBAR_PTPCFSMS_PCU_FXB_Li_BIT3_DATA_BYTE_SEL_HSH  (0x010F5D44)

  #define PCU_CR_VISA_XBAR_PTPCFSMS_PCU_FXB_Li_BIT4_DATA_BIT_SEL_OFF   (16)
  #define PCU_CR_VISA_XBAR_PTPCFSMS_PCU_FXB_Li_BIT4_DATA_BIT_SEL_WID   ( 3)
  #define PCU_CR_VISA_XBAR_PTPCFSMS_PCU_FXB_Li_BIT4_DATA_BIT_SEL_MSK   (0x00070000)
  #define PCU_CR_VISA_XBAR_PTPCFSMS_PCU_FXB_Li_BIT4_DATA_BIT_SEL_MIN   (0)
  #define PCU_CR_VISA_XBAR_PTPCFSMS_PCU_FXB_Li_BIT4_DATA_BIT_SEL_MAX   (7) // 0x00000007
  #define PCU_CR_VISA_XBAR_PTPCFSMS_PCU_FXB_Li_BIT4_DATA_BIT_SEL_DEF   (0x00000004)
  #define PCU_CR_VISA_XBAR_PTPCFSMS_PCU_FXB_Li_BIT4_DATA_BIT_SEL_HSH   (0x03105D44)

  #define PCU_CR_VISA_XBAR_PTPCFSMS_PCU_FXB_Li_BIT4_DATA_BYTE_SEL_OFF  (19)
  #define PCU_CR_VISA_XBAR_PTPCFSMS_PCU_FXB_Li_BIT4_DATA_BYTE_SEL_WID  ( 1)
  #define PCU_CR_VISA_XBAR_PTPCFSMS_PCU_FXB_Li_BIT4_DATA_BYTE_SEL_MSK  (0x00080000)
  #define PCU_CR_VISA_XBAR_PTPCFSMS_PCU_FXB_Li_BIT4_DATA_BYTE_SEL_MIN  (0)
  #define PCU_CR_VISA_XBAR_PTPCFSMS_PCU_FXB_Li_BIT4_DATA_BYTE_SEL_MAX  (1) // 0x00000001
  #define PCU_CR_VISA_XBAR_PTPCFSMS_PCU_FXB_Li_BIT4_DATA_BYTE_SEL_DEF  (0x00000000)
  #define PCU_CR_VISA_XBAR_PTPCFSMS_PCU_FXB_Li_BIT4_DATA_BYTE_SEL_HSH  (0x01135D44)

  #define PCU_CR_VISA_XBAR_PTPCFSMS_PCU_FXB_Li_BIT5_DATA_BIT_SEL_OFF   (20)
  #define PCU_CR_VISA_XBAR_PTPCFSMS_PCU_FXB_Li_BIT5_DATA_BIT_SEL_WID   ( 3)
  #define PCU_CR_VISA_XBAR_PTPCFSMS_PCU_FXB_Li_BIT5_DATA_BIT_SEL_MSK   (0x00700000)
  #define PCU_CR_VISA_XBAR_PTPCFSMS_PCU_FXB_Li_BIT5_DATA_BIT_SEL_MIN   (0)
  #define PCU_CR_VISA_XBAR_PTPCFSMS_PCU_FXB_Li_BIT5_DATA_BIT_SEL_MAX   (7) // 0x00000007
  #define PCU_CR_VISA_XBAR_PTPCFSMS_PCU_FXB_Li_BIT5_DATA_BIT_SEL_DEF   (0x00000005)
  #define PCU_CR_VISA_XBAR_PTPCFSMS_PCU_FXB_Li_BIT5_DATA_BIT_SEL_HSH   (0x03145D44)

  #define PCU_CR_VISA_XBAR_PTPCFSMS_PCU_FXB_Li_BIT5_DATA_BYTE_SEL_OFF  (23)
  #define PCU_CR_VISA_XBAR_PTPCFSMS_PCU_FXB_Li_BIT5_DATA_BYTE_SEL_WID  ( 1)
  #define PCU_CR_VISA_XBAR_PTPCFSMS_PCU_FXB_Li_BIT5_DATA_BYTE_SEL_MSK  (0x00800000)
  #define PCU_CR_VISA_XBAR_PTPCFSMS_PCU_FXB_Li_BIT5_DATA_BYTE_SEL_MIN  (0)
  #define PCU_CR_VISA_XBAR_PTPCFSMS_PCU_FXB_Li_BIT5_DATA_BYTE_SEL_MAX  (1) // 0x00000001
  #define PCU_CR_VISA_XBAR_PTPCFSMS_PCU_FXB_Li_BIT5_DATA_BYTE_SEL_DEF  (0x00000000)
  #define PCU_CR_VISA_XBAR_PTPCFSMS_PCU_FXB_Li_BIT5_DATA_BYTE_SEL_HSH  (0x01175D44)

  #define PCU_CR_VISA_XBAR_PTPCFSMS_PCU_FXB_Li_BIT6_DATA_BIT_SEL_OFF   (24)
  #define PCU_CR_VISA_XBAR_PTPCFSMS_PCU_FXB_Li_BIT6_DATA_BIT_SEL_WID   ( 3)
  #define PCU_CR_VISA_XBAR_PTPCFSMS_PCU_FXB_Li_BIT6_DATA_BIT_SEL_MSK   (0x07000000)
  #define PCU_CR_VISA_XBAR_PTPCFSMS_PCU_FXB_Li_BIT6_DATA_BIT_SEL_MIN   (0)
  #define PCU_CR_VISA_XBAR_PTPCFSMS_PCU_FXB_Li_BIT6_DATA_BIT_SEL_MAX   (7) // 0x00000007
  #define PCU_CR_VISA_XBAR_PTPCFSMS_PCU_FXB_Li_BIT6_DATA_BIT_SEL_DEF   (0x00000006)
  #define PCU_CR_VISA_XBAR_PTPCFSMS_PCU_FXB_Li_BIT6_DATA_BIT_SEL_HSH   (0x03185D44)

  #define PCU_CR_VISA_XBAR_PTPCFSMS_PCU_FXB_Li_BIT6_DATA_BYTE_SEL_OFF  (27)
  #define PCU_CR_VISA_XBAR_PTPCFSMS_PCU_FXB_Li_BIT6_DATA_BYTE_SEL_WID  ( 1)
  #define PCU_CR_VISA_XBAR_PTPCFSMS_PCU_FXB_Li_BIT6_DATA_BYTE_SEL_MSK  (0x08000000)
  #define PCU_CR_VISA_XBAR_PTPCFSMS_PCU_FXB_Li_BIT6_DATA_BYTE_SEL_MIN  (0)
  #define PCU_CR_VISA_XBAR_PTPCFSMS_PCU_FXB_Li_BIT6_DATA_BYTE_SEL_MAX  (1) // 0x00000001
  #define PCU_CR_VISA_XBAR_PTPCFSMS_PCU_FXB_Li_BIT6_DATA_BYTE_SEL_DEF  (0x00000000)
  #define PCU_CR_VISA_XBAR_PTPCFSMS_PCU_FXB_Li_BIT6_DATA_BYTE_SEL_HSH  (0x011B5D44)

  #define PCU_CR_VISA_XBAR_PTPCFSMS_PCU_FXB_Li_BIT7_DATA_BIT_SEL_OFF   (28)
  #define PCU_CR_VISA_XBAR_PTPCFSMS_PCU_FXB_Li_BIT7_DATA_BIT_SEL_WID   ( 3)
  #define PCU_CR_VISA_XBAR_PTPCFSMS_PCU_FXB_Li_BIT7_DATA_BIT_SEL_MSK   (0x70000000)
  #define PCU_CR_VISA_XBAR_PTPCFSMS_PCU_FXB_Li_BIT7_DATA_BIT_SEL_MIN   (0)
  #define PCU_CR_VISA_XBAR_PTPCFSMS_PCU_FXB_Li_BIT7_DATA_BIT_SEL_MAX   (7) // 0x00000007
  #define PCU_CR_VISA_XBAR_PTPCFSMS_PCU_FXB_Li_BIT7_DATA_BIT_SEL_DEF   (0x00000007)
  #define PCU_CR_VISA_XBAR_PTPCFSMS_PCU_FXB_Li_BIT7_DATA_BIT_SEL_HSH   (0x031C5D44)

  #define PCU_CR_VISA_XBAR_PTPCFSMS_PCU_FXB_Li_BIT7_DATA_BYTE_SEL_OFF  (31)
  #define PCU_CR_VISA_XBAR_PTPCFSMS_PCU_FXB_Li_BIT7_DATA_BYTE_SEL_WID  ( 1)
  #define PCU_CR_VISA_XBAR_PTPCFSMS_PCU_FXB_Li_BIT7_DATA_BYTE_SEL_MSK  (0x80000000)
  #define PCU_CR_VISA_XBAR_PTPCFSMS_PCU_FXB_Li_BIT7_DATA_BYTE_SEL_MIN  (0)
  #define PCU_CR_VISA_XBAR_PTPCFSMS_PCU_FXB_Li_BIT7_DATA_BYTE_SEL_MAX  (1) // 0x00000001
  #define PCU_CR_VISA_XBAR_PTPCFSMS_PCU_FXB_Li_BIT7_DATA_BYTE_SEL_DEF  (0x00000000)
  #define PCU_CR_VISA_XBAR_PTPCFSMS_PCU_FXB_Li_BIT7_DATA_BYTE_SEL_HSH  (0x011F5D44)

#define PCU_CR_VISA_CTL_PTPCIOREGS_PCU_REG                             (0x00005D48)

  #define PCU_CR_VISA_CTL_PTPCIOREGS_PCU_EN_CLK_OFF                    ( 0)
  #define PCU_CR_VISA_CTL_PTPCIOREGS_PCU_EN_CLK_WID                    ( 1)
  #define PCU_CR_VISA_CTL_PTPCIOREGS_PCU_EN_CLK_MSK                    (0x00000001)
  #define PCU_CR_VISA_CTL_PTPCIOREGS_PCU_EN_CLK_MIN                    (0)
  #define PCU_CR_VISA_CTL_PTPCIOREGS_PCU_EN_CLK_MAX                    (1) // 0x00000001
  #define PCU_CR_VISA_CTL_PTPCIOREGS_PCU_EN_CLK_DEF                    (0x00000000)
  #define PCU_CR_VISA_CTL_PTPCIOREGS_PCU_EN_CLK_HSH                    (0x01005D48)

  #define PCU_CR_VISA_CTL_PTPCIOREGS_PCU_L0_DATA_BYTE_SEL_OFF          ( 1)
  #define PCU_CR_VISA_CTL_PTPCIOREGS_PCU_L0_DATA_BYTE_SEL_WID          ( 7)
  #define PCU_CR_VISA_CTL_PTPCIOREGS_PCU_L0_DATA_BYTE_SEL_MSK          (0x000000FE)
  #define PCU_CR_VISA_CTL_PTPCIOREGS_PCU_L0_DATA_BYTE_SEL_MIN          (0)
  #define PCU_CR_VISA_CTL_PTPCIOREGS_PCU_L0_DATA_BYTE_SEL_MAX          (127) // 0x0000007F
  #define PCU_CR_VISA_CTL_PTPCIOREGS_PCU_L0_DATA_BYTE_SEL_DEF          (0x00000000)
  #define PCU_CR_VISA_CTL_PTPCIOREGS_PCU_L0_DATA_BYTE_SEL_HSH          (0x07015D48)

  #define PCU_CR_VISA_CTL_PTPCIOREGS_PCU_L0_BYP_SEL_OFF                ( 8)
  #define PCU_CR_VISA_CTL_PTPCIOREGS_PCU_L0_BYP_SEL_WID                ( 1)
  #define PCU_CR_VISA_CTL_PTPCIOREGS_PCU_L0_BYP_SEL_MSK                (0x00000100)
  #define PCU_CR_VISA_CTL_PTPCIOREGS_PCU_L0_BYP_SEL_MIN                (0)
  #define PCU_CR_VISA_CTL_PTPCIOREGS_PCU_L0_BYP_SEL_MAX                (1) // 0x00000001
  #define PCU_CR_VISA_CTL_PTPCIOREGS_PCU_L0_BYP_SEL_DEF                (0x00000000)
  #define PCU_CR_VISA_CTL_PTPCIOREGS_PCU_L0_BYP_SEL_HSH                (0x01085D48)

  #define PCU_CR_VISA_CTL_PTPCIOREGS_PCU_L1_DATA_BYTE_SEL_OFF          ( 9)
  #define PCU_CR_VISA_CTL_PTPCIOREGS_PCU_L1_DATA_BYTE_SEL_WID          ( 7)
  #define PCU_CR_VISA_CTL_PTPCIOREGS_PCU_L1_DATA_BYTE_SEL_MSK          (0x0000FE00)
  #define PCU_CR_VISA_CTL_PTPCIOREGS_PCU_L1_DATA_BYTE_SEL_MIN          (0)
  #define PCU_CR_VISA_CTL_PTPCIOREGS_PCU_L1_DATA_BYTE_SEL_MAX          (127) // 0x0000007F
  #define PCU_CR_VISA_CTL_PTPCIOREGS_PCU_L1_DATA_BYTE_SEL_DEF          (0x00000000)
  #define PCU_CR_VISA_CTL_PTPCIOREGS_PCU_L1_DATA_BYTE_SEL_HSH          (0x07095D48)

  #define PCU_CR_VISA_CTL_PTPCIOREGS_PCU_L1_BYP_SEL_OFF                (16)
  #define PCU_CR_VISA_CTL_PTPCIOREGS_PCU_L1_BYP_SEL_WID                ( 1)
  #define PCU_CR_VISA_CTL_PTPCIOREGS_PCU_L1_BYP_SEL_MSK                (0x00010000)
  #define PCU_CR_VISA_CTL_PTPCIOREGS_PCU_L1_BYP_SEL_MIN                (0)
  #define PCU_CR_VISA_CTL_PTPCIOREGS_PCU_L1_BYP_SEL_MAX                (1) // 0x00000001
  #define PCU_CR_VISA_CTL_PTPCIOREGS_PCU_L1_BYP_SEL_DEF                (0x00000000)
  #define PCU_CR_VISA_CTL_PTPCIOREGS_PCU_L1_BYP_SEL_HSH                (0x01105D48)

  #define PCU_CR_VISA_CTL_PTPCIOREGS_PCU_VORANGE_OFF                   (31)
  #define PCU_CR_VISA_CTL_PTPCIOREGS_PCU_VORANGE_WID                   ( 1)
  #define PCU_CR_VISA_CTL_PTPCIOREGS_PCU_VORANGE_MSK                   (0x80000000)
  #define PCU_CR_VISA_CTL_PTPCIOREGS_PCU_VORANGE_MIN                   (0)
  #define PCU_CR_VISA_CTL_PTPCIOREGS_PCU_VORANGE_MAX                   (1) // 0x00000001
  #define PCU_CR_VISA_CTL_PTPCIOREGS_PCU_VORANGE_DEF                   (0x00000000)
  #define PCU_CR_VISA_CTL_PTPCIOREGS_PCU_VORANGE_HSH                   (0x011F5D48)

#define PCU_CR_VISA_SLIDE_PTPCIOREGS_PCU_REG                           (0x00005D4C)

  #define PCU_CR_VISA_SLIDE_PTPCIOREGS_PCU_WINDOW_SLIDE_L0_OFF         ( 0)
  #define PCU_CR_VISA_SLIDE_PTPCIOREGS_PCU_WINDOW_SLIDE_L0_WID         ( 3)
  #define PCU_CR_VISA_SLIDE_PTPCIOREGS_PCU_WINDOW_SLIDE_L0_MSK         (0x00000007)
  #define PCU_CR_VISA_SLIDE_PTPCIOREGS_PCU_WINDOW_SLIDE_L0_MIN         (0)
  #define PCU_CR_VISA_SLIDE_PTPCIOREGS_PCU_WINDOW_SLIDE_L0_MAX         (7) // 0x00000007
  #define PCU_CR_VISA_SLIDE_PTPCIOREGS_PCU_WINDOW_SLIDE_L0_DEF         (0x00000000)
  #define PCU_CR_VISA_SLIDE_PTPCIOREGS_PCU_WINDOW_SLIDE_L0_HSH         (0x03005D4C)

  #define PCU_CR_VISA_SLIDE_PTPCIOREGS_PCU_ALT_L0_DATA_BYTE_SEL_OFF    ( 3)
  #define PCU_CR_VISA_SLIDE_PTPCIOREGS_PCU_ALT_L0_DATA_BYTE_SEL_WID    ( 7)
  #define PCU_CR_VISA_SLIDE_PTPCIOREGS_PCU_ALT_L0_DATA_BYTE_SEL_MSK    (0x000003F8)
  #define PCU_CR_VISA_SLIDE_PTPCIOREGS_PCU_ALT_L0_DATA_BYTE_SEL_MIN    (0)
  #define PCU_CR_VISA_SLIDE_PTPCIOREGS_PCU_ALT_L0_DATA_BYTE_SEL_MAX    (127) // 0x0000007F
  #define PCU_CR_VISA_SLIDE_PTPCIOREGS_PCU_ALT_L0_DATA_BYTE_SEL_DEF    (0x00000000)
  #define PCU_CR_VISA_SLIDE_PTPCIOREGS_PCU_ALT_L0_DATA_BYTE_SEL_HSH    (0x07035D4C)

  #define PCU_CR_VISA_SLIDE_PTPCIOREGS_PCU_WINDOW_SLIDE_L1_OFF         (10)
  #define PCU_CR_VISA_SLIDE_PTPCIOREGS_PCU_WINDOW_SLIDE_L1_WID         ( 3)
  #define PCU_CR_VISA_SLIDE_PTPCIOREGS_PCU_WINDOW_SLIDE_L1_MSK         (0x00001C00)
  #define PCU_CR_VISA_SLIDE_PTPCIOREGS_PCU_WINDOW_SLIDE_L1_MIN         (0)
  #define PCU_CR_VISA_SLIDE_PTPCIOREGS_PCU_WINDOW_SLIDE_L1_MAX         (7) // 0x00000007
  #define PCU_CR_VISA_SLIDE_PTPCIOREGS_PCU_WINDOW_SLIDE_L1_DEF         (0x00000000)
  #define PCU_CR_VISA_SLIDE_PTPCIOREGS_PCU_WINDOW_SLIDE_L1_HSH         (0x030A5D4C)

  #define PCU_CR_VISA_SLIDE_PTPCIOREGS_PCU_ALT_L1_DATA_BYTE_SEL_OFF    (13)
  #define PCU_CR_VISA_SLIDE_PTPCIOREGS_PCU_ALT_L1_DATA_BYTE_SEL_WID    ( 7)
  #define PCU_CR_VISA_SLIDE_PTPCIOREGS_PCU_ALT_L1_DATA_BYTE_SEL_MSK    (0x000FE000)
  #define PCU_CR_VISA_SLIDE_PTPCIOREGS_PCU_ALT_L1_DATA_BYTE_SEL_MIN    (0)
  #define PCU_CR_VISA_SLIDE_PTPCIOREGS_PCU_ALT_L1_DATA_BYTE_SEL_MAX    (127) // 0x0000007F
  #define PCU_CR_VISA_SLIDE_PTPCIOREGS_PCU_ALT_L1_DATA_BYTE_SEL_DEF    (0x00000000)
  #define PCU_CR_VISA_SLIDE_PTPCIOREGS_PCU_ALT_L1_DATA_BYTE_SEL_HSH    (0x070D5D4C)

#define PCU_CR_VISA_SLIDE_PTPCFSMS_PCU_REG                             (0x00005D50)

  #define PCU_CR_VISA_SLIDE_PTPCFSMS_PCU_WINDOW_SLIDE_L0_OFF           ( 0)
  #define PCU_CR_VISA_SLIDE_PTPCFSMS_PCU_WINDOW_SLIDE_L0_WID           ( 3)
  #define PCU_CR_VISA_SLIDE_PTPCFSMS_PCU_WINDOW_SLIDE_L0_MSK           (0x00000007)
  #define PCU_CR_VISA_SLIDE_PTPCFSMS_PCU_WINDOW_SLIDE_L0_MIN           (0)
  #define PCU_CR_VISA_SLIDE_PTPCFSMS_PCU_WINDOW_SLIDE_L0_MAX           (7) // 0x00000007
  #define PCU_CR_VISA_SLIDE_PTPCFSMS_PCU_WINDOW_SLIDE_L0_DEF           (0x00000000)
  #define PCU_CR_VISA_SLIDE_PTPCFSMS_PCU_WINDOW_SLIDE_L0_HSH           (0x03005D50)

  #define PCU_CR_VISA_SLIDE_PTPCFSMS_PCU_ALT_L0_DATA_BYTE_SEL_OFF      ( 3)
  #define PCU_CR_VISA_SLIDE_PTPCFSMS_PCU_ALT_L0_DATA_BYTE_SEL_WID      ( 7)
  #define PCU_CR_VISA_SLIDE_PTPCFSMS_PCU_ALT_L0_DATA_BYTE_SEL_MSK      (0x000003F8)
  #define PCU_CR_VISA_SLIDE_PTPCFSMS_PCU_ALT_L0_DATA_BYTE_SEL_MIN      (0)
  #define PCU_CR_VISA_SLIDE_PTPCFSMS_PCU_ALT_L0_DATA_BYTE_SEL_MAX      (127) // 0x0000007F
  #define PCU_CR_VISA_SLIDE_PTPCFSMS_PCU_ALT_L0_DATA_BYTE_SEL_DEF      (0x00000000)
  #define PCU_CR_VISA_SLIDE_PTPCFSMS_PCU_ALT_L0_DATA_BYTE_SEL_HSH      (0x07035D50)

  #define PCU_CR_VISA_SLIDE_PTPCFSMS_PCU_WINDOW_SLIDE_L1_OFF           (10)
  #define PCU_CR_VISA_SLIDE_PTPCFSMS_PCU_WINDOW_SLIDE_L1_WID           ( 3)
  #define PCU_CR_VISA_SLIDE_PTPCFSMS_PCU_WINDOW_SLIDE_L1_MSK           (0x00001C00)
  #define PCU_CR_VISA_SLIDE_PTPCFSMS_PCU_WINDOW_SLIDE_L1_MIN           (0)
  #define PCU_CR_VISA_SLIDE_PTPCFSMS_PCU_WINDOW_SLIDE_L1_MAX           (7) // 0x00000007
  #define PCU_CR_VISA_SLIDE_PTPCFSMS_PCU_WINDOW_SLIDE_L1_DEF           (0x00000000)
  #define PCU_CR_VISA_SLIDE_PTPCFSMS_PCU_WINDOW_SLIDE_L1_HSH           (0x030A5D50)

  #define PCU_CR_VISA_SLIDE_PTPCFSMS_PCU_ALT_L1_DATA_BYTE_SEL_OFF      (13)
  #define PCU_CR_VISA_SLIDE_PTPCFSMS_PCU_ALT_L1_DATA_BYTE_SEL_WID      ( 7)
  #define PCU_CR_VISA_SLIDE_PTPCFSMS_PCU_ALT_L1_DATA_BYTE_SEL_MSK      (0x000FE000)
  #define PCU_CR_VISA_SLIDE_PTPCFSMS_PCU_ALT_L1_DATA_BYTE_SEL_MIN      (0)
  #define PCU_CR_VISA_SLIDE_PTPCFSMS_PCU_ALT_L1_DATA_BYTE_SEL_MAX      (127) // 0x0000007F
  #define PCU_CR_VISA_SLIDE_PTPCFSMS_PCU_ALT_L1_DATA_BYTE_SEL_DEF      (0x00000000)
  #define PCU_CR_VISA_SLIDE_PTPCFSMS_PCU_ALT_L1_DATA_BYTE_SEL_HSH      (0x070D5D50)

#define PCU_CR_BIOS_MAILBOX_DATA_PCU_REG                               (0x00005DA0)

  #define PCU_CR_BIOS_MAILBOX_DATA_PCU_DATA_OFF                        ( 0)
  #define PCU_CR_BIOS_MAILBOX_DATA_PCU_DATA_WID                        (32)
  #define PCU_CR_BIOS_MAILBOX_DATA_PCU_DATA_MSK                        (0xFFFFFFFF)
  #define PCU_CR_BIOS_MAILBOX_DATA_PCU_DATA_MIN                        (0)
  #define PCU_CR_BIOS_MAILBOX_DATA_PCU_DATA_MAX                        (4294967295) // 0xFFFFFFFF
  #define PCU_CR_BIOS_MAILBOX_DATA_PCU_DATA_DEF                        (0x00000000)
  #define PCU_CR_BIOS_MAILBOX_DATA_PCU_DATA_HSH                        (0x20005DA0)

#define PCU_CR_BIOS_MAILBOX_INTERFACE_PCU_REG                          (0x00005DA4)

  #define PCU_CR_BIOS_MAILBOX_INTERFACE_PCU_COMMAND_OFF                ( 0)
  #define PCU_CR_BIOS_MAILBOX_INTERFACE_PCU_COMMAND_WID                ( 8)
  #define PCU_CR_BIOS_MAILBOX_INTERFACE_PCU_COMMAND_MSK                (0x000000FF)
  #define PCU_CR_BIOS_MAILBOX_INTERFACE_PCU_COMMAND_MIN                (0)
  #define PCU_CR_BIOS_MAILBOX_INTERFACE_PCU_COMMAND_MAX                (255) // 0x000000FF
  #define PCU_CR_BIOS_MAILBOX_INTERFACE_PCU_COMMAND_DEF                (0x00000000)
  #define PCU_CR_BIOS_MAILBOX_INTERFACE_PCU_COMMAND_HSH                (0x08005DA4)

  #define PCU_CR_BIOS_MAILBOX_INTERFACE_PCU_ADDR_OFF                   ( 8)
  #define PCU_CR_BIOS_MAILBOX_INTERFACE_PCU_ADDR_WID                   (21)
  #define PCU_CR_BIOS_MAILBOX_INTERFACE_PCU_ADDR_MSK                   (0x1FFFFF00)
  #define PCU_CR_BIOS_MAILBOX_INTERFACE_PCU_ADDR_MIN                   (0)
  #define PCU_CR_BIOS_MAILBOX_INTERFACE_PCU_ADDR_MAX                   (2097151) // 0x001FFFFF
  #define PCU_CR_BIOS_MAILBOX_INTERFACE_PCU_ADDR_DEF                   (0x00000000)
  #define PCU_CR_BIOS_MAILBOX_INTERFACE_PCU_ADDR_HSH                   (0x15085DA4)

  #define PCU_CR_BIOS_MAILBOX_INTERFACE_PCU_RUN_BUSY_OFF               (31)
  #define PCU_CR_BIOS_MAILBOX_INTERFACE_PCU_RUN_BUSY_WID               ( 1)
  #define PCU_CR_BIOS_MAILBOX_INTERFACE_PCU_RUN_BUSY_MSK               (0x80000000)
  #define PCU_CR_BIOS_MAILBOX_INTERFACE_PCU_RUN_BUSY_MIN               (0)
  #define PCU_CR_BIOS_MAILBOX_INTERFACE_PCU_RUN_BUSY_MAX               (1) // 0x00000001
  #define PCU_CR_BIOS_MAILBOX_INTERFACE_PCU_RUN_BUSY_DEF               (0x00000000)
  #define PCU_CR_BIOS_MAILBOX_INTERFACE_PCU_RUN_BUSY_HSH               (0x011F5DA4)

#define PCU_CR_BIOS_RESET_CPL_PCU_REG                                  (0x00005DA8)

  #define PCU_CR_BIOS_RESET_CPL_PCU_RST_CPL_OFF                        ( 0)
  #define PCU_CR_BIOS_RESET_CPL_PCU_RST_CPL_WID                        ( 1)
  #define PCU_CR_BIOS_RESET_CPL_PCU_RST_CPL_MSK                        (0x00000001)
  #define PCU_CR_BIOS_RESET_CPL_PCU_RST_CPL_MIN                        (0)
  #define PCU_CR_BIOS_RESET_CPL_PCU_RST_CPL_MAX                        (1) // 0x00000001
  #define PCU_CR_BIOS_RESET_CPL_PCU_RST_CPL_DEF                        (0x00000000)
  #define PCU_CR_BIOS_RESET_CPL_PCU_RST_CPL_HSH                        (0x01005DA8)

  #define PCU_CR_BIOS_RESET_CPL_PCU_PCIE_ENUMERATION_DONE_OFF          ( 1)
  #define PCU_CR_BIOS_RESET_CPL_PCU_PCIE_ENUMERATION_DONE_WID          ( 1)
  #define PCU_CR_BIOS_RESET_CPL_PCU_PCIE_ENUMERATION_DONE_MSK          (0x00000002)
  #define PCU_CR_BIOS_RESET_CPL_PCU_PCIE_ENUMERATION_DONE_MIN          (0)
  #define PCU_CR_BIOS_RESET_CPL_PCU_PCIE_ENUMERATION_DONE_MAX          (1) // 0x00000001
  #define PCU_CR_BIOS_RESET_CPL_PCU_PCIE_ENUMERATION_DONE_DEF          (0x00000000)
  #define PCU_CR_BIOS_RESET_CPL_PCU_PCIE_ENUMERATION_DONE_HSH          (0x01015DA8)

  #define PCU_CR_BIOS_RESET_CPL_PCU_C7_ALLOWED_OFF                     ( 2)
  #define PCU_CR_BIOS_RESET_CPL_PCU_C7_ALLOWED_WID                     ( 1)
  #define PCU_CR_BIOS_RESET_CPL_PCU_C7_ALLOWED_MSK                     (0x00000004)
  #define PCU_CR_BIOS_RESET_CPL_PCU_C7_ALLOWED_MIN                     (0)
  #define PCU_CR_BIOS_RESET_CPL_PCU_C7_ALLOWED_MAX                     (1) // 0x00000001
  #define PCU_CR_BIOS_RESET_CPL_PCU_C7_ALLOWED_DEF                     (0x00000000)
  #define PCU_CR_BIOS_RESET_CPL_PCU_C7_ALLOWED_HSH                     (0x01025DA8)

#define PCU_CR_MC_BIOS_REQ_PCU_REG                                     (0x00005E00)

  #define PCU_CR_MC_BIOS_REQ_PCU_REQ_DATA_OFF                          ( 0)
  #define PCU_CR_MC_BIOS_REQ_PCU_REQ_DATA_WID                          ( 4)
  #define PCU_CR_MC_BIOS_REQ_PCU_REQ_DATA_MSK                          (0x0000000F)
  #define PCU_CR_MC_BIOS_REQ_PCU_REQ_DATA_MIN                          (0)
  #define PCU_CR_MC_BIOS_REQ_PCU_REQ_DATA_MAX                          (15) // 0x0000000F
  #define PCU_CR_MC_BIOS_REQ_PCU_REQ_DATA_DEF                          (0x00000000)
  #define PCU_CR_MC_BIOS_REQ_PCU_REQ_DATA_HSH                          (0x04005E00)

  #define PCU_CR_MC_BIOS_REQ_PCU_REQ_TYPE_OFF                          ( 4)
  #define PCU_CR_MC_BIOS_REQ_PCU_REQ_TYPE_WID                          ( 1)
  #define PCU_CR_MC_BIOS_REQ_PCU_REQ_TYPE_MSK                          (0x00000010)
  #define PCU_CR_MC_BIOS_REQ_PCU_REQ_TYPE_MIN                          (0)
  #define PCU_CR_MC_BIOS_REQ_PCU_REQ_TYPE_MAX                          (1) // 0x00000001
  #define PCU_CR_MC_BIOS_REQ_PCU_REQ_TYPE_DEF                          (0x00000000)
  #define PCU_CR_MC_BIOS_REQ_PCU_REQ_TYPE_HSH                          (0x01045E00)

  #define PCU_CR_MC_BIOS_REQ_PCU_REQ_DATA_MSB_OFF                      ( 5)
  #define PCU_CR_MC_BIOS_REQ_PCU_REQ_DATA_MSB_WID                      ( 1)
  #define PCU_CR_MC_BIOS_REQ_PCU_REQ_DATA_MSB_MSK                      (0x00000020)
  #define PCU_CR_MC_BIOS_REQ_PCU_REQ_DATA_MSB_MIN                      (0)
  #define PCU_CR_MC_BIOS_REQ_PCU_REQ_DATA_MSB_MAX                      (1) // 0x00000001
  #define PCU_CR_MC_BIOS_REQ_PCU_REQ_DATA_MSB_DEF                      (0x00000000)
  #define PCU_CR_MC_BIOS_REQ_PCU_REQ_DATA_MSB_HSH                      (0x01055E00)

  #define PCU_CR_MC_BIOS_REQ_PCU_REQ_QCLK_ODD_RATIO_OFF                ( 8)
  #define PCU_CR_MC_BIOS_REQ_PCU_REQ_QCLK_ODD_RATIO_WID                ( 1)
  #define PCU_CR_MC_BIOS_REQ_PCU_REQ_QCLK_ODD_RATIO_MSK                (0x00000100)
  #define PCU_CR_MC_BIOS_REQ_PCU_REQ_QCLK_ODD_RATIO_MIN                (0)
  #define PCU_CR_MC_BIOS_REQ_PCU_REQ_QCLK_ODD_RATIO_MAX                (1) // 0x00000001
  #define PCU_CR_MC_BIOS_REQ_PCU_REQ_QCLK_ODD_RATIO_DEF                (0x00000000)
  #define PCU_CR_MC_BIOS_REQ_PCU_REQ_QCLK_ODD_RATIO_HSH                (0x01085E00)

  #define PCU_CR_MC_BIOS_REQ_PCU_RUN_BUSY_OFF                          (31)
  #define PCU_CR_MC_BIOS_REQ_PCU_RUN_BUSY_WID                          ( 1)
  #define PCU_CR_MC_BIOS_REQ_PCU_RUN_BUSY_MSK                          (0x80000000)
  #define PCU_CR_MC_BIOS_REQ_PCU_RUN_BUSY_MIN                          (0)
  #define PCU_CR_MC_BIOS_REQ_PCU_RUN_BUSY_MAX                          (1) // 0x00000001
  #define PCU_CR_MC_BIOS_REQ_PCU_RUN_BUSY_DEF                          (0x00000000)
  #define PCU_CR_MC_BIOS_REQ_PCU_RUN_BUSY_HSH                          (0x011F5E00)

#define PCU_CR_MC_BIOS_DATA_PCU_REG                                    (0x00005E04)

  #define PCU_CR_MC_BIOS_DATA_PCU_MC_FREQ_OFF                          ( 0)
  #define PCU_CR_MC_BIOS_DATA_PCU_MC_FREQ_WID                          ( 4)
  #define PCU_CR_MC_BIOS_DATA_PCU_MC_FREQ_MSK                          (0x0000000F)
  #define PCU_CR_MC_BIOS_DATA_PCU_MC_FREQ_MIN                          (0)
  #define PCU_CR_MC_BIOS_DATA_PCU_MC_FREQ_MAX                          (15) // 0x0000000F
  #define PCU_CR_MC_BIOS_DATA_PCU_MC_FREQ_DEF                          (0x00000000)
  #define PCU_CR_MC_BIOS_DATA_PCU_MC_FREQ_HSH                          (0x04005E04)

  #define PCU_CR_MC_BIOS_DATA_PCU_MC_FREQ_TYPE_OFF                     ( 4)
  #define PCU_CR_MC_BIOS_DATA_PCU_MC_FREQ_TYPE_WID                     ( 1)
  #define PCU_CR_MC_BIOS_DATA_PCU_MC_FREQ_TYPE_MSK                     (0x00000010)
  #define PCU_CR_MC_BIOS_DATA_PCU_MC_FREQ_TYPE_MIN                     (0)
  #define PCU_CR_MC_BIOS_DATA_PCU_MC_FREQ_TYPE_MAX                     (1) // 0x00000001
  #define PCU_CR_MC_BIOS_DATA_PCU_MC_FREQ_TYPE_DEF                     (0x00000000)
  #define PCU_CR_MC_BIOS_DATA_PCU_MC_FREQ_TYPE_HSH                     (0x01045E04)

  #define PCU_CR_MC_BIOS_DATA_PCU_MC_FREQ_MSB_OFF                      ( 5)
  #define PCU_CR_MC_BIOS_DATA_PCU_MC_FREQ_MSB_WID                      ( 1)
  #define PCU_CR_MC_BIOS_DATA_PCU_MC_FREQ_MSB_MSK                      (0x00000020)
  #define PCU_CR_MC_BIOS_DATA_PCU_MC_FREQ_MSB_MIN                      (0)
  #define PCU_CR_MC_BIOS_DATA_PCU_MC_FREQ_MSB_MAX                      (1) // 0x00000001
  #define PCU_CR_MC_BIOS_DATA_PCU_MC_FREQ_MSB_DEF                      (0x00000000)
  #define PCU_CR_MC_BIOS_DATA_PCU_MC_FREQ_MSB_HSH                      (0x01055E04)

  #define PCU_CR_MC_BIOS_DATA_PCU_QCLK_ODD_RATIO_OFF                   ( 8)
  #define PCU_CR_MC_BIOS_DATA_PCU_QCLK_ODD_RATIO_WID                   ( 1)
  #define PCU_CR_MC_BIOS_DATA_PCU_QCLK_ODD_RATIO_MSK                   (0x00000100)
  #define PCU_CR_MC_BIOS_DATA_PCU_QCLK_ODD_RATIO_MIN                   (0)
  #define PCU_CR_MC_BIOS_DATA_PCU_QCLK_ODD_RATIO_MAX                   (1) // 0x00000001
  #define PCU_CR_MC_BIOS_DATA_PCU_QCLK_ODD_RATIO_DEF                   (0x00000000)
  #define PCU_CR_MC_BIOS_DATA_PCU_QCLK_ODD_RATIO_HSH                   (0x01085E04)

#define PCU_CR_SAPMCTL_PCU_REG                                         (0x00005F00)

  #define PCU_CR_SAPMCTL_PCU_SACG_ENA_OFF                              ( 0)
  #define PCU_CR_SAPMCTL_PCU_SACG_ENA_WID                              ( 1)
  #define PCU_CR_SAPMCTL_PCU_SACG_ENA_MSK                              (0x00000001)
  #define PCU_CR_SAPMCTL_PCU_SACG_ENA_MIN                              (0)
  #define PCU_CR_SAPMCTL_PCU_SACG_ENA_MAX                              (1) // 0x00000001
  #define PCU_CR_SAPMCTL_PCU_SACG_ENA_DEF                              (0x00000000)
  #define PCU_CR_SAPMCTL_PCU_SACG_ENA_HSH                              (0x01005F00)

  #define PCU_CR_SAPMCTL_PCU_MPLL_OFF_ENA_OFF                          ( 1)
  #define PCU_CR_SAPMCTL_PCU_MPLL_OFF_ENA_WID                          ( 1)
  #define PCU_CR_SAPMCTL_PCU_MPLL_OFF_ENA_MSK                          (0x00000002)
  #define PCU_CR_SAPMCTL_PCU_MPLL_OFF_ENA_MIN                          (0)
  #define PCU_CR_SAPMCTL_PCU_MPLL_OFF_ENA_MAX                          (1) // 0x00000001
  #define PCU_CR_SAPMCTL_PCU_MPLL_OFF_ENA_DEF                          (0x00000001)
  #define PCU_CR_SAPMCTL_PCU_MPLL_OFF_ENA_HSH                          (0x01015F00)

  #define PCU_CR_SAPMCTL_PCU_PPLL_OFF_ENA_OFF                          ( 2)
  #define PCU_CR_SAPMCTL_PCU_PPLL_OFF_ENA_WID                          ( 1)
  #define PCU_CR_SAPMCTL_PCU_PPLL_OFF_ENA_MSK                          (0x00000004)
  #define PCU_CR_SAPMCTL_PCU_PPLL_OFF_ENA_MIN                          (0)
  #define PCU_CR_SAPMCTL_PCU_PPLL_OFF_ENA_MAX                          (1) // 0x00000001
  #define PCU_CR_SAPMCTL_PCU_PPLL_OFF_ENA_DEF                          (0x00000001)
  #define PCU_CR_SAPMCTL_PCU_PPLL_OFF_ENA_HSH                          (0x01025F00)

  #define PCU_CR_SAPMCTL_PCU_SACG_SEN_OFF                              ( 8)
  #define PCU_CR_SAPMCTL_PCU_SACG_SEN_WID                              ( 1)
  #define PCU_CR_SAPMCTL_PCU_SACG_SEN_MSK                              (0x00000100)
  #define PCU_CR_SAPMCTL_PCU_SACG_SEN_MIN                              (0)
  #define PCU_CR_SAPMCTL_PCU_SACG_SEN_MAX                              (1) // 0x00000001
  #define PCU_CR_SAPMCTL_PCU_SACG_SEN_DEF                              (0x00000001)
  #define PCU_CR_SAPMCTL_PCU_SACG_SEN_HSH                              (0x01085F00)

  #define PCU_CR_SAPMCTL_PCU_MPLL_OFF_SEN_OFF                          ( 9)
  #define PCU_CR_SAPMCTL_PCU_MPLL_OFF_SEN_WID                          ( 1)
  #define PCU_CR_SAPMCTL_PCU_MPLL_OFF_SEN_MSK                          (0x00000200)
  #define PCU_CR_SAPMCTL_PCU_MPLL_OFF_SEN_MIN                          (0)
  #define PCU_CR_SAPMCTL_PCU_MPLL_OFF_SEN_MAX                          (1) // 0x00000001
  #define PCU_CR_SAPMCTL_PCU_MPLL_OFF_SEN_DEF                          (0x00000000)
  #define PCU_CR_SAPMCTL_PCU_MPLL_OFF_SEN_HSH                          (0x01095F00)

  #define PCU_CR_SAPMCTL_PCU_MDLL_OFF_SEN_OFF                          (10)
  #define PCU_CR_SAPMCTL_PCU_MDLL_OFF_SEN_WID                          ( 1)
  #define PCU_CR_SAPMCTL_PCU_MDLL_OFF_SEN_MSK                          (0x00000400)
  #define PCU_CR_SAPMCTL_PCU_MDLL_OFF_SEN_MIN                          (0)
  #define PCU_CR_SAPMCTL_PCU_MDLL_OFF_SEN_MAX                          (1) // 0x00000001
  #define PCU_CR_SAPMCTL_PCU_MDLL_OFF_SEN_DEF                          (0x00000000)
  #define PCU_CR_SAPMCTL_PCU_MDLL_OFF_SEN_HSH                          (0x010A5F00)

  #define PCU_CR_SAPMCTL_PCU_SACG_SREXIT_OFF                           (11)
  #define PCU_CR_SAPMCTL_PCU_SACG_SREXIT_WID                           ( 1)
  #define PCU_CR_SAPMCTL_PCU_SACG_SREXIT_MSK                           (0x00000800)
  #define PCU_CR_SAPMCTL_PCU_SACG_SREXIT_MIN                           (0)
  #define PCU_CR_SAPMCTL_PCU_SACG_SREXIT_MAX                           (1) // 0x00000001
  #define PCU_CR_SAPMCTL_PCU_SACG_SREXIT_DEF                           (0x00000000)
  #define PCU_CR_SAPMCTL_PCU_SACG_SREXIT_HSH                           (0x010B5F00)

  #define PCU_CR_SAPMCTL_PCU_NSWAKE_SREXIT_OFF                         (12)
  #define PCU_CR_SAPMCTL_PCU_NSWAKE_SREXIT_WID                         ( 1)
  #define PCU_CR_SAPMCTL_PCU_NSWAKE_SREXIT_MSK                         (0x00001000)
  #define PCU_CR_SAPMCTL_PCU_NSWAKE_SREXIT_MIN                         (0)
  #define PCU_CR_SAPMCTL_PCU_NSWAKE_SREXIT_MAX                         (1) // 0x00000001
  #define PCU_CR_SAPMCTL_PCU_NSWAKE_SREXIT_DEF                         (0x00000000)
  #define PCU_CR_SAPMCTL_PCU_NSWAKE_SREXIT_HSH                         (0x010C5F00)

  #define PCU_CR_SAPMCTL_PCU_SACG_MPLL_OFF                             (13)
  #define PCU_CR_SAPMCTL_PCU_SACG_MPLL_WID                             ( 1)
  #define PCU_CR_SAPMCTL_PCU_SACG_MPLL_MSK                             (0x00002000)
  #define PCU_CR_SAPMCTL_PCU_SACG_MPLL_MIN                             (0)
  #define PCU_CR_SAPMCTL_PCU_SACG_MPLL_MAX                             (1) // 0x00000001
  #define PCU_CR_SAPMCTL_PCU_SACG_MPLL_DEF                             (0x00000001)
  #define PCU_CR_SAPMCTL_PCU_SACG_MPLL_HSH                             (0x010D5F00)

  #define PCU_CR_SAPMCTL_PCU_MPLL_ON_DE_OFF                            (14)
  #define PCU_CR_SAPMCTL_PCU_MPLL_ON_DE_WID                            ( 1)
  #define PCU_CR_SAPMCTL_PCU_MPLL_ON_DE_MSK                            (0x00004000)
  #define PCU_CR_SAPMCTL_PCU_MPLL_ON_DE_MIN                            (0)
  #define PCU_CR_SAPMCTL_PCU_MPLL_ON_DE_MAX                            (1) // 0x00000001
  #define PCU_CR_SAPMCTL_PCU_MPLL_ON_DE_DEF                            (0x00000000)
  #define PCU_CR_SAPMCTL_PCU_MPLL_ON_DE_HSH                            (0x010E5F00)

  #define PCU_CR_SAPMCTL_PCU_MDLL_ON_DE_OFF                            (15)
  #define PCU_CR_SAPMCTL_PCU_MDLL_ON_DE_WID                            ( 1)
  #define PCU_CR_SAPMCTL_PCU_MDLL_ON_DE_MSK                            (0x00008000)
  #define PCU_CR_SAPMCTL_PCU_MDLL_ON_DE_MIN                            (0)
  #define PCU_CR_SAPMCTL_PCU_MDLL_ON_DE_MAX                            (1) // 0x00000001
  #define PCU_CR_SAPMCTL_PCU_MDLL_ON_DE_DEF                            (0x00000000)
  #define PCU_CR_SAPMCTL_PCU_MDLL_ON_DE_HSH                            (0x010F5F00)

#define PCU_CR_P_COMP_PCU_REG                                          (0x00005F04)

  #define PCU_CR_P_COMP_PCU_COMP_DISABLE_OFF                           ( 0)
  #define PCU_CR_P_COMP_PCU_COMP_DISABLE_WID                           ( 1)
  #define PCU_CR_P_COMP_PCU_COMP_DISABLE_MSK                           (0x00000001)
  #define PCU_CR_P_COMP_PCU_COMP_DISABLE_MIN                           (0)
  #define PCU_CR_P_COMP_PCU_COMP_DISABLE_MAX                           (1) // 0x00000001
  #define PCU_CR_P_COMP_PCU_COMP_DISABLE_DEF                           (0x00000001)
  #define PCU_CR_P_COMP_PCU_COMP_DISABLE_HSH                           (0x01005F04)

  #define PCU_CR_P_COMP_PCU_COMP_INTERVAL_OFF                          ( 1)
  #define PCU_CR_P_COMP_PCU_COMP_INTERVAL_WID                          ( 4)
  #define PCU_CR_P_COMP_PCU_COMP_INTERVAL_MSK                          (0x0000001E)
  #define PCU_CR_P_COMP_PCU_COMP_INTERVAL_MIN                          (0)
  #define PCU_CR_P_COMP_PCU_COMP_INTERVAL_MAX                          (15) // 0x0000000F
  #define PCU_CR_P_COMP_PCU_COMP_INTERVAL_DEF                          (0x00000008)
  #define PCU_CR_P_COMP_PCU_COMP_INTERVAL_HSH                          (0x04015F04)

  #define PCU_CR_P_COMP_PCU_COMP_FORCE_OFF                             ( 8)
  #define PCU_CR_P_COMP_PCU_COMP_FORCE_WID                             ( 1)
  #define PCU_CR_P_COMP_PCU_COMP_FORCE_MSK                             (0x00000100)
  #define PCU_CR_P_COMP_PCU_COMP_FORCE_MIN                             (0)
  #define PCU_CR_P_COMP_PCU_COMP_FORCE_MAX                             (1) // 0x00000001
  #define PCU_CR_P_COMP_PCU_COMP_FORCE_DEF                             (0x00000000)
  #define PCU_CR_P_COMP_PCU_COMP_FORCE_HSH                             (0x01085F04)

#define PCU_CR_M_COMP_PCU_REG                                          (0x00005F08)

  #define PCU_CR_M_COMP_PCU_COMP_DISABLE_OFF                           ( 0)
  #define PCU_CR_M_COMP_PCU_COMP_DISABLE_WID                           ( 1)
  #define PCU_CR_M_COMP_PCU_COMP_DISABLE_MSK                           (0x00000001)
  #define PCU_CR_M_COMP_PCU_COMP_DISABLE_MIN                           (0)
  #define PCU_CR_M_COMP_PCU_COMP_DISABLE_MAX                           (1) // 0x00000001
  #define PCU_CR_M_COMP_PCU_COMP_DISABLE_DEF                           (0x00000000)
  #define PCU_CR_M_COMP_PCU_COMP_DISABLE_HSH                           (0x01005F08)

  #define PCU_CR_M_COMP_PCU_COMP_INTERVAL_OFF                          ( 1)
  #define PCU_CR_M_COMP_PCU_COMP_INTERVAL_WID                          ( 4)
  #define PCU_CR_M_COMP_PCU_COMP_INTERVAL_MSK                          (0x0000001E)
  #define PCU_CR_M_COMP_PCU_COMP_INTERVAL_MIN                          (0)
  #define PCU_CR_M_COMP_PCU_COMP_INTERVAL_MAX                          (15) // 0x0000000F
  #define PCU_CR_M_COMP_PCU_COMP_INTERVAL_DEF                          (0x0000000D)
  #define PCU_CR_M_COMP_PCU_COMP_INTERVAL_HSH                          (0x04015F08)

  #define PCU_CR_M_COMP_PCU_COMP_FORCE_OFF                             ( 8)
  #define PCU_CR_M_COMP_PCU_COMP_FORCE_WID                             ( 1)
  #define PCU_CR_M_COMP_PCU_COMP_FORCE_MSK                             (0x00000100)
  #define PCU_CR_M_COMP_PCU_COMP_FORCE_MIN                             (0)
  #define PCU_CR_M_COMP_PCU_COMP_FORCE_MAX                             (1) // 0x00000001
  #define PCU_CR_M_COMP_PCU_COMP_FORCE_DEF                             (0x00000000)
  #define PCU_CR_M_COMP_PCU_COMP_FORCE_HSH                             (0x01085F08)

#define PCU_CR_SAPM_PG_CONTROL_PCU_REG                                 (0x00005F14)

  #define PCU_CR_SAPM_PG_CONTROL_PCU_PCIE_PWR_CONTROL_OFF              ( 0)
  #define PCU_CR_SAPM_PG_CONTROL_PCU_PCIE_PWR_CONTROL_WID              ( 1)
  #define PCU_CR_SAPM_PG_CONTROL_PCU_PCIE_PWR_CONTROL_MSK              (0x00000001)
  #define PCU_CR_SAPM_PG_CONTROL_PCU_PCIE_PWR_CONTROL_MIN              (0)
  #define PCU_CR_SAPM_PG_CONTROL_PCU_PCIE_PWR_CONTROL_MAX              (1) // 0x00000001
  #define PCU_CR_SAPM_PG_CONTROL_PCU_PCIE_PWR_CONTROL_DEF              (0x00000001)
  #define PCU_CR_SAPM_PG_CONTROL_PCU_PCIE_PWR_CONTROL_HSH              (0x01005F14)

#define PCU_CR_SAPM_PG_STATUS_PCU_REG                                  (0x00005F18)

  #define PCU_CR_SAPM_PG_STATUS_PCU_PCIE_PWR_STATUS_OFF                ( 0)
  #define PCU_CR_SAPM_PG_STATUS_PCU_PCIE_PWR_STATUS_WID                ( 1)
  #define PCU_CR_SAPM_PG_STATUS_PCU_PCIE_PWR_STATUS_MSK                (0x00000001)
  #define PCU_CR_SAPM_PG_STATUS_PCU_PCIE_PWR_STATUS_MIN                (0)
  #define PCU_CR_SAPM_PG_STATUS_PCU_PCIE_PWR_STATUS_MAX                (1) // 0x00000001
  #define PCU_CR_SAPM_PG_STATUS_PCU_PCIE_PWR_STATUS_DEF                (0x00000001)
  #define PCU_CR_SAPM_PG_STATUS_PCU_PCIE_PWR_STATUS_HSH                (0x01005F18)

#define PCU_CR_CONFIG_TDP_NOMINAL_PCU_REG                              (0x00005F3C)

  #define PCU_CR_CONFIG_TDP_NOMINAL_PCU_TDP_RATIO_OFF                  ( 0)
  #define PCU_CR_CONFIG_TDP_NOMINAL_PCU_TDP_RATIO_WID                  ( 8)
  #define PCU_CR_CONFIG_TDP_NOMINAL_PCU_TDP_RATIO_MSK                  (0x000000FF)
  #define PCU_CR_CONFIG_TDP_NOMINAL_PCU_TDP_RATIO_MIN                  (0)
  #define PCU_CR_CONFIG_TDP_NOMINAL_PCU_TDP_RATIO_MAX                  (255) // 0x000000FF
  #define PCU_CR_CONFIG_TDP_NOMINAL_PCU_TDP_RATIO_DEF                  (0x00000000)
  #define PCU_CR_CONFIG_TDP_NOMINAL_PCU_TDP_RATIO_HSH                  (0x08005F3C)

#define PCU_CR_CONFIG_TDP_LEVEL1_PCU_REG                               (0x00005F40)

  #define PCU_CR_CONFIG_TDP_LEVEL1_PCU_PKG_TDP_OFF                     ( 0)
  #define PCU_CR_CONFIG_TDP_LEVEL1_PCU_PKG_TDP_WID                     (15)
  #define PCU_CR_CONFIG_TDP_LEVEL1_PCU_PKG_TDP_MSK                     (0x00007FFF)
  #define PCU_CR_CONFIG_TDP_LEVEL1_PCU_PKG_TDP_MIN                     (0)
  #define PCU_CR_CONFIG_TDP_LEVEL1_PCU_PKG_TDP_MAX                     (32767) // 0x00007FFF
  #define PCU_CR_CONFIG_TDP_LEVEL1_PCU_PKG_TDP_DEF                     (0x00000000)
  #define PCU_CR_CONFIG_TDP_LEVEL1_PCU_PKG_TDP_HSH                     (0x4F005F40)

  #define PCU_CR_CONFIG_TDP_LEVEL1_PCU_TDP_RATIO_OFF                   (16)
  #define PCU_CR_CONFIG_TDP_LEVEL1_PCU_TDP_RATIO_WID                   ( 8)
  #define PCU_CR_CONFIG_TDP_LEVEL1_PCU_TDP_RATIO_MSK                   (0x00FF0000)
  #define PCU_CR_CONFIG_TDP_LEVEL1_PCU_TDP_RATIO_MIN                   (0)
  #define PCU_CR_CONFIG_TDP_LEVEL1_PCU_TDP_RATIO_MAX                   (255) // 0x000000FF
  #define PCU_CR_CONFIG_TDP_LEVEL1_PCU_TDP_RATIO_DEF                   (0x00000000)
  #define PCU_CR_CONFIG_TDP_LEVEL1_PCU_TDP_RATIO_HSH                   (0x48105F40)

  #define PCU_CR_CONFIG_TDP_LEVEL1_PCU_PKG_MAX_PWR_OFF                 (32)
  #define PCU_CR_CONFIG_TDP_LEVEL1_PCU_PKG_MAX_PWR_WID                 (15)
  #define PCU_CR_CONFIG_TDP_LEVEL1_PCU_PKG_MAX_PWR_MSK                 (0x00007FFF00000000ULL)
  #define PCU_CR_CONFIG_TDP_LEVEL1_PCU_PKG_MAX_PWR_MIN                 (0)
  #define PCU_CR_CONFIG_TDP_LEVEL1_PCU_PKG_MAX_PWR_MAX                 (32767) // 0x00007FFF
  #define PCU_CR_CONFIG_TDP_LEVEL1_PCU_PKG_MAX_PWR_DEF                 (0x00000000)
  #define PCU_CR_CONFIG_TDP_LEVEL1_PCU_PKG_MAX_PWR_HSH                 (0x4F205F40)

  #define PCU_CR_CONFIG_TDP_LEVEL1_PCU_PKG_MIN_PWR_OFF                 (48)
  #define PCU_CR_CONFIG_TDP_LEVEL1_PCU_PKG_MIN_PWR_WID                 (15)
  #define PCU_CR_CONFIG_TDP_LEVEL1_PCU_PKG_MIN_PWR_MSK                 (0x7FFF000000000000ULL)
  #define PCU_CR_CONFIG_TDP_LEVEL1_PCU_PKG_MIN_PWR_MIN                 (0)
  #define PCU_CR_CONFIG_TDP_LEVEL1_PCU_PKG_MIN_PWR_MAX                 (32767) // 0x00007FFF
  #define PCU_CR_CONFIG_TDP_LEVEL1_PCU_PKG_MIN_PWR_DEF                 (0x00000000)
  #define PCU_CR_CONFIG_TDP_LEVEL1_PCU_PKG_MIN_PWR_HSH                 (0x4F305F40)

#define PCU_CR_CONFIG_TDP_LEVEL2_PCU_REG                               (0x00005F48)

  #define PCU_CR_CONFIG_TDP_LEVEL2_PCU_PKG_TDP_OFF                     ( 0)
  #define PCU_CR_CONFIG_TDP_LEVEL2_PCU_PKG_TDP_WID                     (15)
  #define PCU_CR_CONFIG_TDP_LEVEL2_PCU_PKG_TDP_MSK                     (0x00007FFF)
  #define PCU_CR_CONFIG_TDP_LEVEL2_PCU_PKG_TDP_MIN                     (0)
  #define PCU_CR_CONFIG_TDP_LEVEL2_PCU_PKG_TDP_MAX                     (32767) // 0x00007FFF
  #define PCU_CR_CONFIG_TDP_LEVEL2_PCU_PKG_TDP_DEF                     (0x00000000)
  #define PCU_CR_CONFIG_TDP_LEVEL2_PCU_PKG_TDP_HSH                     (0x4F005F48)

  #define PCU_CR_CONFIG_TDP_LEVEL2_PCU_TDP_RATIO_OFF                   (16)
  #define PCU_CR_CONFIG_TDP_LEVEL2_PCU_TDP_RATIO_WID                   ( 8)
  #define PCU_CR_CONFIG_TDP_LEVEL2_PCU_TDP_RATIO_MSK                   (0x00FF0000)
  #define PCU_CR_CONFIG_TDP_LEVEL2_PCU_TDP_RATIO_MIN                   (0)
  #define PCU_CR_CONFIG_TDP_LEVEL2_PCU_TDP_RATIO_MAX                   (255) // 0x000000FF
  #define PCU_CR_CONFIG_TDP_LEVEL2_PCU_TDP_RATIO_DEF                   (0x00000000)
  #define PCU_CR_CONFIG_TDP_LEVEL2_PCU_TDP_RATIO_HSH                   (0x48105F48)

  #define PCU_CR_CONFIG_TDP_LEVEL2_PCU_PKG_MAX_PWR_OFF                 (32)
  #define PCU_CR_CONFIG_TDP_LEVEL2_PCU_PKG_MAX_PWR_WID                 (15)
  #define PCU_CR_CONFIG_TDP_LEVEL2_PCU_PKG_MAX_PWR_MSK                 (0x00007FFF00000000ULL)
  #define PCU_CR_CONFIG_TDP_LEVEL2_PCU_PKG_MAX_PWR_MIN                 (0)
  #define PCU_CR_CONFIG_TDP_LEVEL2_PCU_PKG_MAX_PWR_MAX                 (32767) // 0x00007FFF
  #define PCU_CR_CONFIG_TDP_LEVEL2_PCU_PKG_MAX_PWR_DEF                 (0x00000000)
  #define PCU_CR_CONFIG_TDP_LEVEL2_PCU_PKG_MAX_PWR_HSH                 (0x4F205F48)

  #define PCU_CR_CONFIG_TDP_LEVEL2_PCU_PKG_MIN_PWR_OFF                 (48)
  #define PCU_CR_CONFIG_TDP_LEVEL2_PCU_PKG_MIN_PWR_WID                 (15)
  #define PCU_CR_CONFIG_TDP_LEVEL2_PCU_PKG_MIN_PWR_MSK                 (0x7FFF000000000000ULL)
  #define PCU_CR_CONFIG_TDP_LEVEL2_PCU_PKG_MIN_PWR_MIN                 (0)
  #define PCU_CR_CONFIG_TDP_LEVEL2_PCU_PKG_MIN_PWR_MAX                 (32767) // 0x00007FFF
  #define PCU_CR_CONFIG_TDP_LEVEL2_PCU_PKG_MIN_PWR_DEF                 (0x00000000)
  #define PCU_CR_CONFIG_TDP_LEVEL2_PCU_PKG_MIN_PWR_HSH                 (0x4F305F48)

#define PCU_CR_CONFIG_TDP_CONTROL_PCU_REG                              (0x00005F50)

  #define PCU_CR_CONFIG_TDP_CONTROL_PCU_TDP_LEVEL_OFF                  ( 0)
  #define PCU_CR_CONFIG_TDP_CONTROL_PCU_TDP_LEVEL_WID                  ( 2)
  #define PCU_CR_CONFIG_TDP_CONTROL_PCU_TDP_LEVEL_MSK                  (0x00000003)
  #define PCU_CR_CONFIG_TDP_CONTROL_PCU_TDP_LEVEL_MIN                  (0)
  #define PCU_CR_CONFIG_TDP_CONTROL_PCU_TDP_LEVEL_MAX                  (3) // 0x00000003
  #define PCU_CR_CONFIG_TDP_CONTROL_PCU_TDP_LEVEL_DEF                  (0x00000000)
  #define PCU_CR_CONFIG_TDP_CONTROL_PCU_TDP_LEVEL_HSH                  (0x02005F50)

  #define PCU_CR_CONFIG_TDP_CONTROL_PCU_CONFIG_TDP_LOCK_OFF            (31)
  #define PCU_CR_CONFIG_TDP_CONTROL_PCU_CONFIG_TDP_LOCK_WID            ( 1)
  #define PCU_CR_CONFIG_TDP_CONTROL_PCU_CONFIG_TDP_LOCK_MSK            (0x80000000)
  #define PCU_CR_CONFIG_TDP_CONTROL_PCU_CONFIG_TDP_LOCK_MIN            (0)
  #define PCU_CR_CONFIG_TDP_CONTROL_PCU_CONFIG_TDP_LOCK_MAX            (1) // 0x00000001
  #define PCU_CR_CONFIG_TDP_CONTROL_PCU_CONFIG_TDP_LOCK_DEF            (0x00000000)
  #define PCU_CR_CONFIG_TDP_CONTROL_PCU_CONFIG_TDP_LOCK_HSH            (0x011F5F50)

#define PCU_CR_TURBO_ACTIVATION_RATIO_PCU_REG                          (0x00005F54)

  #define PCU_CR_TURBO_ACTIVATION_RATIO_PCU_MAX_NON_TURBO_RATIO_OFF    ( 0)
  #define PCU_CR_TURBO_ACTIVATION_RATIO_PCU_MAX_NON_TURBO_RATIO_WID    ( 8)
  #define PCU_CR_TURBO_ACTIVATION_RATIO_PCU_MAX_NON_TURBO_RATIO_MSK    (0x000000FF)
  #define PCU_CR_TURBO_ACTIVATION_RATIO_PCU_MAX_NON_TURBO_RATIO_MIN    (0)
  #define PCU_CR_TURBO_ACTIVATION_RATIO_PCU_MAX_NON_TURBO_RATIO_MAX    (255) // 0x000000FF
  #define PCU_CR_TURBO_ACTIVATION_RATIO_PCU_MAX_NON_TURBO_RATIO_DEF    (0x00000000)
  #define PCU_CR_TURBO_ACTIVATION_RATIO_PCU_MAX_NON_TURBO_RATIO_HSH    (0x08005F54)

  #define PCU_CR_TURBO_ACTIVATION_RATIO_PCU_TURBO_ACTIVATION_RATIO_LOCK_OFF (31)
  #define PCU_CR_TURBO_ACTIVATION_RATIO_PCU_TURBO_ACTIVATION_RATIO_LOCK_WID ( 1)
  #define PCU_CR_TURBO_ACTIVATION_RATIO_PCU_TURBO_ACTIVATION_RATIO_LOCK_MSK (0x80000000)
  #define PCU_CR_TURBO_ACTIVATION_RATIO_PCU_TURBO_ACTIVATION_RATIO_LOCK_MIN (0)
  #define PCU_CR_TURBO_ACTIVATION_RATIO_PCU_TURBO_ACTIVATION_RATIO_LOCK_MAX (1) // 0x00000001
  #define PCU_CR_TURBO_ACTIVATION_RATIO_PCU_TURBO_ACTIVATION_RATIO_LOCK_DEF (0x00000000)
  #define PCU_CR_TURBO_ACTIVATION_RATIO_PCU_TURBO_ACTIVATION_RATIO_LOCK_HSH (0x011F5F54)
#pragma pack(pop)
#endif
