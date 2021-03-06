/** @file
    SklPchH Bx HSIO C File

 @copyright
  INTEL CONFIDENTIAL
  Copyright 2014 - 2016 Intel Corporation.

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

#include <Uefi/UefiBaseType.h>
#include <PchAccess.h>
#include <Private/PchHsio.h>

UINT8 PchHChipsetInitTable_Bx[] = {
  0xD0, 0xEF, //CRC-16
  0x3e,       //Version
  0x91,       //Product/Stepping
  // Phy Data Group Table (Fixed table with 16 Entries)
  0x00, 0x00,
  0x02, 0xE3,
  0x00, 0x0F,
  0x00, 0x00,
  0x00, 0x00,
  0x00, 0x00,
  0x00, 0x00,
  0x00, 0x00,
  0x00, 0x00,
  0x00, 0x00,
  0x00, 0x00,
  0x00, 0x00,
  0x00, 0x00,
  0x00, 0x00,
  0x00, 0x00,
  0x00, 0x00,
  // HSIO Command Table
  0x28, 0xA9, 0x07, 0x00, 0x0F, 0x00, 0x64, 0x00, 0x05, 0x00, 0x15, 0xA0, //  {0xA9, 0xA0150005, 0x064, PCH_LANE_OWN_COMMON, LANE},
  0x28, 0xA9, 0x07, 0x00, 0x0F, 0x00, 0x64, 0x02, 0x05, 0x00, 0x15, 0xA0, //  {0xA9, 0xA0150005, 0x264, PCH_LANE_OWN_COMMON, LANE},
  0x28, 0xA9, 0x07, 0x00, 0x0F, 0x00, 0x64, 0x04, 0x05, 0x00, 0x15, 0xA0, //  {0xA9, 0xA0150005, 0x464, PCH_LANE_OWN_COMMON, LANE},
  0x28, 0xA9, 0x07, 0x00, 0x0F, 0x00, 0x64, 0x06, 0x05, 0x00, 0x15, 0xA0, //  {0xA9, 0xA0150005, 0x664, PCH_LANE_OWN_COMMON, LANE},
  0x28, 0xA9, 0x07, 0x00, 0x0F, 0x00, 0x00, 0x80, 0x3E, 0x00, 0x13, 0x00, //  {0xA9, 0x0013003E, 0x8000, PCH_LANE_OWN_COMMON, LANE},
  0x28, 0xA9, 0x07, 0x00, 0x0F, 0x00, 0x04, 0x80, 0xE0, 0x00, 0x00, 0x20, //  {0xA9, 0x200000E0, 0x8004, PCH_LANE_OWN_COMMON, LANE},
  0x28, 0xA9, 0x07, 0x00, 0x0F, 0x00, 0x10, 0x81, 0x02, 0x08, 0x01, 0x0A, //  {0xA9, 0x0A010802, 0x8110, PCH_LANE_OWN_COMMON, LANE},
  0x28, 0xA9, 0x07, 0x00, 0x0F, 0x00, 0x28, 0x81, 0x06, 0x00, 0x1F, 0x00, //  {0xA9, 0x001F0006, 0x8128, PCH_LANE_OWN_COMMON, LANE},
  0x28, 0xA9, 0x07, 0x00, 0x0F, 0x00, 0x30, 0x81, 0x00, 0x3C, 0x00, 0x78, //  {0xA9, 0x78003C00, 0x8130, PCH_LANE_OWN_COMMON, LANE},
  0x28, 0xE9, 0x07, 0x00, 0x0F, 0x00, 0x00, 0x80, 0x3E, 0x00, 0x13, 0x00, //  {0xE9, 0x0013003E, 0x8000, PCH_LANE_OWN_COMMON, LANE},
  0x28, 0xE9, 0x07, 0x00, 0x0F, 0x00, 0x04, 0x80, 0xE0, 0x00, 0x00, 0x20, //  {0xE9, 0x200000E0, 0x8004, PCH_LANE_OWN_COMMON, LANE},
  0x28, 0xE9, 0x07, 0x00, 0x0F, 0x00, 0x08, 0x81, 0x1C, 0x05, 0x1F, 0x00, //  {0xE9, 0x001F051C, 0x8108, PCH_LANE_OWN_COMMON, LANE},
  0x28, 0xE9, 0x07, 0x00, 0x0F, 0x00, 0x10, 0x81, 0x04, 0x07, 0x01, 0x08, //  {0xE9, 0x08010704, 0x8110, PCH_LANE_OWN_COMMON, LANE},
  0x28, 0xE9, 0x07, 0x00, 0x0F, 0x00, 0x30, 0x81, 0x00, 0x3C, 0x00, 0x78, //  {0xE9, 0x78003C00, 0x8130, PCH_LANE_OWN_COMMON, LANE},
  0x28, 0xEA, 0x07, 0x00, 0x0F, 0x00, 0x2C, 0x81, 0x0B, 0x03, 0x00, 0x00, //  {0xEA, 0x0000030B, 0x812C, PCH_LANE_OWN_COMMON, LANE},
  0x0F, 0x00, 0x00, 0x00,                                                 //  End Table Marker
  0x28, 0xEA, 0x07, 0x00, 0x0F, 0x00, 0x78, 0xC1, 0x60, 0x40, 0x83, 0x40, //  {0xEA, 0x40834060, 0xC178, PCH_LANE_BDCAST, BDCAST},
  0x28, 0xEA, 0x07, 0x00, 0x0F, 0x00, 0x04, 0xC1, 0x88, 0x09, 0x05, 0x00, //  {0xEA, 0x00050988, 0xC104, PCH_LANE_BDCAST, BDCAST},
  0x28, 0xEA, 0x07, 0x00, 0x0F, 0x00, 0x08, 0xC1, 0x50, 0x18, 0xE0, 0xFF, //  {0xEA, 0xFFE01850, 0xC108, PCH_LANE_BDCAST, BDCAST},
  0x28, 0xE9, 0x07, 0x00, 0x0F, 0x00, 0x78, 0xC1, 0x60, 0x40, 0x83, 0x40, //  {0xE9, 0x40834060, 0xC178, PCH_LANE_BDCAST, BDCAST},
  0x28, 0xE9, 0x07, 0x00, 0x0F, 0x00, 0x04, 0xC1, 0x88, 0x09, 0x05, 0x00, //  {0xE9, 0x00050988, 0xC104, PCH_LANE_BDCAST, BDCAST},
  0x28, 0xE9, 0x07, 0x00, 0x0F, 0x00, 0x08, 0xC1, 0x50, 0x18, 0xE0, 0xFF, //  {0xE9, 0xFFE01850, 0xC108, PCH_LANE_BDCAST, BDCAST},
  0x28, 0xA9, 0x07, 0x00, 0x0F, 0x00, 0x78, 0xC1, 0x60, 0x40, 0x83, 0x40, //  {0xA9, 0x40834060, 0xC178, PCH_LANE_BDCAST, BDCAST},
  0x28, 0xA9, 0x07, 0x00, 0x0F, 0x00, 0x04, 0xC1, 0x88, 0x09, 0x05, 0x00, //  {0xA9, 0x00050988, 0xC104, PCH_LANE_BDCAST, BDCAST},
  0x28, 0xA9, 0x07, 0x00, 0x0F, 0x00, 0x08, 0xC1, 0x50, 0x18, 0xE0, 0xFF, //  {0xA9, 0xFFE01850, 0xC108, PCH_LANE_BDCAST, BDCAST},
  0x28, 0xA8, 0x07, 0x00, 0x0F, 0x00, 0x78, 0xC1, 0x60, 0x40, 0x83, 0x40, //  {0xA8, 0x40834060, 0xC178, PCH_LANE_BDCAST, BDCAST},
  0x28, 0xA8, 0x07, 0x00, 0x0F, 0x00, 0x04, 0xC1, 0x88, 0x09, 0x05, 0x00, //  {0xA8, 0x00050988, 0xC104, PCH_LANE_BDCAST, BDCAST},
  0x28, 0xA8, 0x07, 0x00, 0x0F, 0x00, 0x08, 0xC1, 0x50, 0x18, 0xE0, 0xFF, //  {0xA8, 0xFFE01850, 0xC108, PCH_LANE_BDCAST, BDCAST},
  0x28, 0xA9, 0x07, 0x00, 0x0F, 0x00, 0x00, 0x84, 0x00, 0x01, 0x00, 0x00, //  {0xA9, 0x00000100, 0x8400, V_PCH_PCR_FIA_LANE_OWN_PCIEDMI, MULCAST},
  0x28, 0xA9, 0x07, 0x00, 0x0F, 0x00, 0x40, 0x85, 0x58, 0xCF, 0x05, 0x01, //  {0xA9, 0x0105CF58, 0x8540, V_PCH_PCR_FIA_LANE_OWN_PCIEDMI, MULCAST},
  0x28, 0xA9, 0x07, 0x00, 0x0F, 0x00, 0x40, 0x83, 0x58, 0xCF, 0x05, 0x01, //  {0xA9, 0x0105CF58, 0x8340, V_PCH_PCR_FIA_LANE_OWN_PCIEDMI, MULCAST},
  0x28, 0xA9, 0x07, 0x00, 0x0F, 0x00, 0x44, 0x85, 0x48, 0xD5, 0x05, 0x01, //  {0xA9, 0x0105D548, 0x8544, V_PCH_PCR_FIA_LANE_OWN_PCIEDMI, MULCAST},
  0x28, 0xA9, 0x07, 0x00, 0x0F, 0x00, 0x44, 0x83, 0x48, 0xD5, 0x05, 0x01, //  {0xA9, 0x0105D548, 0x8344, V_PCH_PCR_FIA_LANE_OWN_PCIEDMI, MULCAST},
  0x28, 0xA9, 0x07, 0x00, 0x0F, 0x00, 0x0C, 0x85, 0x00, 0x9B, 0x12, 0x00, //  {0xA9, 0x00129B00, 0x850C, V_PCH_PCR_FIA_LANE_OWN_PCIEDMI, MULCAST},
  0x28, 0xA9, 0x07, 0x00, 0x0F, 0x00, 0x0C, 0x83, 0x1F, 0x9B, 0x12, 0x00, //  {0xA9, 0x00129B1F, 0x830C, V_PCH_PCR_FIA_LANE_OWN_PCIEDMI, MULCAST},
  0x28, 0xA9, 0x07, 0x00, 0x0F, 0x00, 0x98, 0x82, 0x20, 0x1E, 0x1F, 0x15, //  {0xA9, 0x151F1E20, 0x8298, V_PCH_PCR_FIA_LANE_OWN_PCIEDMI, MULCAST},
  0x28, 0xA9, 0x07, 0x00, 0x0F, 0x00, 0x98, 0x84, 0x00, 0x29, 0x1F, 0x15, //  {0xA9, 0x151F2900, 0x8498, V_PCH_PCR_FIA_LANE_OWN_PCIEDMI, MULCAST},
  0x28, 0xA9, 0x07, 0x00, 0x0F, 0x00, 0xE8, 0x83, 0x00, 0x48, 0x17, 0x1A, //  {0xA9, 0x1A174800, 0x83E8, V_PCH_PCR_FIA_LANE_OWN_PCIEDMI, MULCAST},
  0x28, 0xA9, 0x07, 0x00, 0x0F, 0x00, 0x3C, 0x85, 0xE0, 0x00, 0x00, 0x20, //  {0xA9, 0x200000E0, 0x853C, V_PCH_PCR_FIA_LANE_OWN_PCIEDMI, MULCAST},
  0x28, 0xA9, 0x07, 0x00, 0x0F, 0x00, 0xCC, 0x84, 0x00, 0x08, 0x1F, 0x20, //  {0xA9, 0x201F0800, 0x84CC, V_PCH_PCR_FIA_LANE_OWN_PCIEDMI, MULCAST},
  0x28, 0xA9, 0x07, 0x00, 0x0F, 0x00, 0xCC, 0x82, 0x00, 0x08, 0x1F, 0x20, //  {0xA9, 0x201F0800, 0x82CC, V_PCH_PCR_FIA_LANE_OWN_PCIEDMI, MULCAST},
  0x28, 0xA9, 0x07, 0x00, 0x0F, 0x00, 0x18, 0x84, 0x7C, 0x00, 0x09, 0x02, //  {0xA9, 0x0209007C, 0x8418, V_PCH_PCR_FIA_LANE_OWN_PCIEDMI, MULCAST},
  0x28, 0xA9, 0x07, 0x00, 0x0F, 0x00, 0x18, 0x82, 0x7C, 0x00, 0x09, 0x02, //  {0xA9, 0x0209007C, 0x8218, V_PCH_PCR_FIA_LANE_OWN_PCIEDMI, MULCAST},
  0x28, 0xA9, 0x07, 0x00, 0x0F, 0x00, 0x94, 0x84, 0x06, 0x00, 0x29, 0x28, //  {0xA9, 0x28290006, 0x8494, V_PCH_PCR_FIA_LANE_OWN_PCIEDMI, MULCAST},
  0x28, 0xA9, 0x07, 0x00, 0x0F, 0x00, 0x94, 0x82, 0x06, 0x2A, 0x29, 0x28, //  {0xA9, 0x28292A06, 0x8294, V_PCH_PCR_FIA_LANE_OWN_PCIEDMI, MULCAST},
  0x28, 0xA9, 0x07, 0x00, 0x0F, 0x00, 0x70, 0x85, 0x5A, 0x25, 0x40, 0x33, //  {0xA9, 0x3340255A, 0x8570, V_PCH_PCR_FIA_LANE_OWN_PCIEDMI, MULCAST},
  0x28, 0xA9, 0x07, 0x00, 0x0F, 0x00, 0x70, 0x83, 0x5A, 0x25, 0x40, 0x33, //  {0xA9, 0x3340255A, 0x8370, V_PCH_PCR_FIA_LANE_OWN_PCIEDMI, MULCAST},
  0x28, 0xA9, 0x07, 0x00, 0x0F, 0x00, 0x1C, 0x85, 0x08, 0x10, 0x39, 0x00, //  {0xA9, 0x00391008, 0x851C, V_PCH_PCR_FIA_LANE_OWN_PCIEDMI, MULCAST},
  0x28, 0xA9, 0x07, 0x00, 0x0F, 0x00, 0x1C, 0x83, 0x08, 0x10, 0x39, 0x00, //  {0xA9, 0x00391008, 0x831C, V_PCH_PCR_FIA_LANE_OWN_PCIEDMI, MULCAST},
  0x28, 0xA9, 0x07, 0x00, 0x0F, 0x00, 0x50, 0x85, 0x3F, 0x3F, 0x3F, 0x04, //  {0xA9, 0x043F3F3F, 0x8550, V_PCH_PCR_FIA_LANE_OWN_PCIEDMI, MULCAST},
  0x28, 0xA9, 0x07, 0x00, 0x0F, 0x00, 0x50, 0x83, 0x3F, 0x3F, 0x3F, 0x04, //  {0xA9, 0x043F3F3F, 0x8350, V_PCH_PCR_FIA_LANE_OWN_PCIEDMI, MULCAST},
  0x28, 0xA9, 0x07, 0x00, 0x0F, 0x00, 0xE4, 0x85, 0x50, 0x05, 0x0B, 0x4B, //  {0xA9, 0x4B0B0550, 0x85E4, V_PCH_PCR_FIA_LANE_OWN_PCIEDMI, MULCAST},
  0x28, 0xA9, 0x07, 0x00, 0x0F, 0x00, 0xE4, 0x83, 0x50, 0x05, 0x0B, 0x4B, //  {0xA9, 0x4B0B0550, 0x83E4, V_PCH_PCR_FIA_LANE_OWN_PCIEDMI, MULCAST},
  0x28, 0xA9, 0x07, 0x00, 0x0F, 0x00, 0x08, 0x85, 0x50, 0x00, 0x00, 0x00, //  {0xA9, 0x00000050, 0x8508, V_PCH_PCR_FIA_LANE_OWN_PCIEDMI, MULCAST},
  0x28, 0xA9, 0x07, 0x00, 0x0F, 0x00, 0x1C, 0x84, 0x00, 0xC0, 0x00, 0x60, //  {0xA9, 0x6000C000, 0x841C, V_PCH_PCR_FIA_LANE_OWN_PCIEDMI, MULCAST},
  0x28, 0xA9, 0x07, 0x00, 0x0F, 0x00, 0x1C, 0x82, 0x00, 0xC0, 0x00, 0x60, //  {0xA9, 0x6000C000, 0x821C, V_PCH_PCR_FIA_LANE_OWN_PCIEDMI, MULCAST},
  0x28, 0xA9, 0x07, 0x00, 0x0F, 0x00, 0x04, 0x84, 0x64, 0x00, 0x00, 0x00, //  {0xA9, 0x00000064, 0x8404, V_PCH_PCR_FIA_LANE_OWN_PCIEDMI, MULCAST},
  0x28, 0xA9, 0x07, 0x00, 0x0F, 0x00, 0x04, 0x82, 0x64, 0x00, 0x00, 0x00, //  {0xA9, 0x00000064, 0x8204, V_PCH_PCR_FIA_LANE_OWN_PCIEDMI, MULCAST},
  0x28, 0xA9, 0x07, 0x00, 0x0F, 0x00, 0x10, 0x84, 0x00, 0x00, 0xBF, 0x72, //  {0xA9, 0x72BF0000, 0x8410, V_PCH_PCR_FIA_LANE_OWN_PCIEDMI, MULCAST},
  0x28, 0xA9, 0x07, 0x00, 0x0F, 0x00, 0x10, 0x82, 0x00, 0x00, 0xBF, 0x72, //  {0xA9, 0x72BF0000, 0x8210, V_PCH_PCR_FIA_LANE_OWN_PCIEDMI, MULCAST},
  0x28, 0xA9, 0x07, 0x00, 0x0F, 0x00, 0xC4, 0x84, 0x08, 0x0A, 0x00, 0x08, //  {0xA9, 0x08000A08, 0x84C4, V_PCH_PCR_FIA_LANE_OWN_PCIEDMI, MULCAST},
  0x28, 0xA9, 0x07, 0x00, 0x0F, 0x00, 0xC4, 0x82, 0x08, 0x0A, 0x00, 0x08, //  {0xA9, 0x08000A08, 0x82C4, V_PCH_PCR_FIA_LANE_OWN_PCIEDMI, MULCAST},
  0x28, 0xA9, 0x07, 0x00, 0x0F, 0x00, 0x8C, 0x85, 0x7C, 0x00, 0x08, 0x00, //  {0xA9, 0x0008007C, 0x858C, V_PCH_PCR_FIA_LANE_OWN_PCIEDMI, MULCAST},
  0x28, 0xA9, 0x07, 0x00, 0x0F, 0x00, 0x8C, 0x83, 0x7C, 0x00, 0x08, 0x00, //  {0xA9, 0x0008007C, 0x838C, V_PCH_PCR_FIA_LANE_OWN_PCIEDMI, MULCAST},
  0x28, 0xA9, 0x07, 0x00, 0x0F, 0x00, 0x54, 0x85, 0x02, 0x00, 0xC0, 0x80, //  {0xA9, 0x80C00002, 0x8554, V_PCH_PCR_FIA_LANE_OWN_PCIEDMI, MULCAST},
  0x28, 0xA9, 0x07, 0x00, 0x0F, 0x00, 0x54, 0x83, 0x02, 0x00, 0xC0, 0x80, //  {0xA9, 0x80C00002, 0x8354, V_PCH_PCR_FIA_LANE_OWN_PCIEDMI, MULCAST},
  0x28, 0xA9, 0x07, 0x00, 0x0F, 0x00, 0x58, 0x85, 0x08, 0xA0, 0x31, 0x81, //  {0xA9, 0x8131A008, 0x8558, V_PCH_PCR_FIA_LANE_OWN_PCIEDMI, MULCAST},
  0x28, 0xA9, 0x07, 0x00, 0x0F, 0x00, 0x58, 0x83, 0x08, 0xA0, 0x31, 0x81, //  {0xA9, 0x8131A008, 0x8358, V_PCH_PCR_FIA_LANE_OWN_PCIEDMI, MULCAST},
  0x28, 0xA9, 0x07, 0x00, 0x0F, 0x00, 0xD4, 0x85, 0xC0, 0x00, 0x82, 0x00, //  {0xA9, 0x008200C0, 0x85D4, V_PCH_PCR_FIA_LANE_OWN_PCIEDMI, MULCAST},
  0x28, 0xA9, 0x07, 0x00, 0x0F, 0x00, 0xD4, 0x83, 0xC0, 0x00, 0x82, 0x00, //  {0xA9, 0x008200C0, 0x83D4, V_PCH_PCR_FIA_LANE_OWN_PCIEDMI, MULCAST},
  0x28, 0xA9, 0x07, 0x00, 0x0F, 0x00, 0x00, 0x85, 0x10, 0xA9, 0x52, 0x09, //  {0xA9, 0x0952A910, 0x8500, V_PCH_PCR_FIA_LANE_OWN_PCIEDMI, MULCAST},
  0x28, 0xA9, 0x07, 0x00, 0x0F, 0x00, 0x00, 0x83, 0x10, 0xA9, 0x52, 0x09, //  {0xA9, 0x0952A910, 0x8300, V_PCH_PCR_FIA_LANE_OWN_PCIEDMI, MULCAST},
  0x28, 0xA9, 0x07, 0x00, 0x0F, 0x00, 0x3C, 0x84, 0x02, 0x9F, 0x00, 0x00, //  {0xA9, 0x00009F02, 0x843C, V_PCH_PCR_FIA_LANE_OWN_PCIEDMI, MULCAST},
  0x28, 0xA9, 0x07, 0x00, 0x0F, 0x00, 0x3C, 0x82, 0x02, 0x9F, 0x00, 0x00, //  {0xA9, 0x00009F02, 0x823C, V_PCH_PCR_FIA_LANE_OWN_PCIEDMI, MULCAST},
  0x28, 0xA9, 0x07, 0x00, 0x0F, 0x00, 0x20, 0x82, 0x25, 0x16, 0x07, 0x0D, //  {0xA9, 0x0D071625, 0x8220, V_PCH_PCR_FIA_LANE_OWN_PCIEDMI, MULCAST},
  0x28, 0xA9, 0x07, 0x00, 0x0F, 0x00, 0x40, 0x84, 0x00, 0x88, 0x02, 0xFF, //  {0xA9, 0xFF028800, 0x8440, V_PCH_PCR_FIA_LANE_OWN_PCIEDMI, MULCAST},
  0x28, 0xA9, 0x07, 0x00, 0x0F, 0x00, 0x40, 0x82, 0x00, 0xB0, 0x02, 0xFF, //  {0xA9, 0xFF02B000, 0x8240, V_PCH_PCR_FIA_LANE_OWN_PCIEDMI, MULCAST},
  0x28, 0xA8, 0x07, 0x00, 0x0F, 0x00, 0x40, 0x83, 0x58, 0xCF, 0x05, 0x01, //  {0xA8, 0x0105CF58, 0x8340, V_PCH_PCR_FIA_LANE_OWN_PCIEDMI, MULCAST},
  0x28, 0xA8, 0x07, 0x00, 0x0F, 0x00, 0x44, 0x83, 0x48, 0xD5, 0x05, 0x01, //  {0xA8, 0x0105D548, 0x8344, V_PCH_PCR_FIA_LANE_OWN_PCIEDMI, MULCAST},
  0x28, 0xA8, 0x07, 0x00, 0x0F, 0x00, 0x0C, 0x83, 0x1F, 0x9B, 0x12, 0x00, //  {0xA8, 0x00129B1F, 0x830C, V_PCH_PCR_FIA_LANE_OWN_PCIEDMI, MULCAST},
  0x28, 0xA8, 0x07, 0x00, 0x0F, 0x00, 0x98, 0x82, 0x20, 0x1E, 0x1F, 0x15, //  {0xA8, 0x151F1E20, 0x8298, V_PCH_PCR_FIA_LANE_OWN_PCIEDMI, MULCAST},
  0x28, 0xA8, 0x07, 0x00, 0x0F, 0x00, 0xE8, 0x83, 0x00, 0x48, 0x17, 0x1A, //  {0xA8, 0x1A174800, 0x83E8, V_PCH_PCR_FIA_LANE_OWN_PCIEDMI, MULCAST},
  0x28, 0xA8, 0x07, 0x00, 0x0F, 0x00, 0xCC, 0x82, 0x00, 0x08, 0x1F, 0x20, //  {0xA8, 0x201F0800, 0x82CC, V_PCH_PCR_FIA_LANE_OWN_PCIEDMI, MULCAST},
  0x28, 0xA8, 0x07, 0x00, 0x0F, 0x00, 0x18, 0x82, 0x7C, 0x00, 0x09, 0x02, //  {0xA8, 0x0209007C, 0x8218, V_PCH_PCR_FIA_LANE_OWN_PCIEDMI, MULCAST},
  0x28, 0xA8, 0x07, 0x00, 0x0F, 0x00, 0x94, 0x82, 0x06, 0x2A, 0x29, 0x28, //  {0xA8, 0x28292A06, 0x8294, V_PCH_PCR_FIA_LANE_OWN_PCIEDMI, MULCAST},
  0x28, 0xA8, 0x07, 0x00, 0x0F, 0x00, 0x70, 0x83, 0x5A, 0x25, 0x40, 0x33, //  {0xA8, 0x3340255A, 0x8370, V_PCH_PCR_FIA_LANE_OWN_PCIEDMI, MULCAST},
  0x28, 0xA8, 0x07, 0x00, 0x0F, 0x00, 0x1C, 0x83, 0x08, 0x10, 0x39, 0x00, //  {0xA8, 0x00391008, 0x831C, V_PCH_PCR_FIA_LANE_OWN_PCIEDMI, MULCAST},
  0x28, 0xA8, 0x07, 0x00, 0x0F, 0x00, 0x50, 0x83, 0x3F, 0x3F, 0x3F, 0x04, //  {0xA8, 0x043F3F3F, 0x8350, V_PCH_PCR_FIA_LANE_OWN_PCIEDMI, MULCAST},
  0x28, 0xA8, 0x07, 0x00, 0x0F, 0x00, 0xE4, 0x83, 0x50, 0x05, 0x0B, 0x4B, //  {0xA8, 0x4B0B0550, 0x83E4, V_PCH_PCR_FIA_LANE_OWN_PCIEDMI, MULCAST},
  0x28, 0xA8, 0x07, 0x00, 0x0F, 0x00, 0x1C, 0x82, 0x00, 0xC0, 0x00, 0x60, //  {0xA8, 0x6000C000, 0x821C, V_PCH_PCR_FIA_LANE_OWN_PCIEDMI, MULCAST},
  0x28, 0xA8, 0x07, 0x00, 0x0F, 0x00, 0x04, 0x82, 0x64, 0x00, 0x00, 0x00, //  {0xA8, 0x00000064, 0x8204, V_PCH_PCR_FIA_LANE_OWN_PCIEDMI, MULCAST},
  0x28, 0xA8, 0x07, 0x00, 0x0F, 0x00, 0x10, 0x82, 0x00, 0x00, 0xBF, 0x72, //  {0xA8, 0x72BF0000, 0x8210, V_PCH_PCR_FIA_LANE_OWN_PCIEDMI, MULCAST},
  0x28, 0xA8, 0x07, 0x00, 0x0F, 0x00, 0xC4, 0x82, 0x08, 0x0A, 0x00, 0x08, //  {0xA8, 0x08000A08, 0x82C4, V_PCH_PCR_FIA_LANE_OWN_PCIEDMI, MULCAST},
  0x28, 0xA8, 0x07, 0x00, 0x0F, 0x00, 0x8C, 0x83, 0x7C, 0x00, 0x08, 0x00, //  {0xA8, 0x0008007C, 0x838C, V_PCH_PCR_FIA_LANE_OWN_PCIEDMI, MULCAST},
  0x28, 0xA8, 0x07, 0x00, 0x0F, 0x00, 0x54, 0x83, 0x02, 0x00, 0xC0, 0x80, //  {0xA8, 0x80C00002, 0x8354, V_PCH_PCR_FIA_LANE_OWN_PCIEDMI, MULCAST},
  0x28, 0xA8, 0x07, 0x00, 0x0F, 0x00, 0x58, 0x83, 0x08, 0xA0, 0x31, 0x81, //  {0xA8, 0x8131A008, 0x8358, V_PCH_PCR_FIA_LANE_OWN_PCIEDMI, MULCAST},
  0x28, 0xA8, 0x07, 0x00, 0x0F, 0x00, 0xD4, 0x83, 0xC0, 0x00, 0x82, 0x00, //  {0xA8, 0x008200C0, 0x83D4, V_PCH_PCR_FIA_LANE_OWN_PCIEDMI, MULCAST},
  0x28, 0xA8, 0x07, 0x00, 0x0F, 0x00, 0x00, 0x83, 0x10, 0xA9, 0x52, 0x09, //  {0xA8, 0x0952A910, 0x8300, V_PCH_PCR_FIA_LANE_OWN_PCIEDMI, MULCAST},
  0x28, 0xA8, 0x07, 0x00, 0x0F, 0x00, 0x3C, 0x82, 0x02, 0x9F, 0x00, 0x00, //  {0xA8, 0x00009F02, 0x823C, V_PCH_PCR_FIA_LANE_OWN_PCIEDMI, MULCAST},
  0x28, 0xA8, 0x07, 0x00, 0x0F, 0x00, 0x20, 0x82, 0x25, 0x16, 0x07, 0x0D, //  {0xA8, 0x0D071625, 0x8220, V_PCH_PCR_FIA_LANE_OWN_PCIEDMI, MULCAST},
  0x28, 0xA8, 0x07, 0x00, 0x0F, 0x00, 0x40, 0x82, 0x00, 0xB0, 0x02, 0xFF, //  {0xA8, 0xFF02B000, 0x8240, V_PCH_PCR_FIA_LANE_OWN_PCIEDMI, MULCAST},
  0x28, 0xEA, 0x07, 0x00, 0x0F, 0x00, 0x40, 0x89, 0x4E, 0xCF, 0x18, 0x01, //  {0xEA, 0x0118CF4E, 0x8940, V_PCH_PCR_FIA_LANE_OWN_USB3, MULCAST},
  0x28, 0xEA, 0x07, 0x00, 0x0F, 0x00, 0x58, 0x89, 0x08, 0xA4, 0x32, 0x01, //  {0xEA, 0x0132A408, 0x8958, V_PCH_PCR_FIA_LANE_OWN_USB3, MULCAST},
  0x28, 0xEA, 0x07, 0x00, 0x0F, 0x00, 0xE8, 0x89, 0x00, 0x48, 0x17, 0x1E, //  {0xEA, 0x1E174800, 0x89E8, V_PCH_PCR_FIA_LANE_OWN_USB3, MULCAST},
  0x28, 0xEA, 0x07, 0x00, 0x0F, 0x00, 0xA0, 0x89, 0xEC, 0x10, 0x00, 0x28, //  {0xEA, 0x280010EC, 0x89A0, V_PCH_PCR_FIA_LANE_OWN_USB3, MULCAST},
  0x28, 0xEA, 0x07, 0x00, 0x0F, 0x00, 0xA4, 0x89, 0x28, 0x28, 0x28, 0x00, //  {0xEA, 0x00282828, 0x89A4, V_PCH_PCR_FIA_LANE_OWN_USB3, MULCAST},
  0x28, 0xEA, 0x07, 0x00, 0x0F, 0x00, 0x94, 0x88, 0x02, 0x2A, 0x29, 0x28, //  {0xEA, 0x28292A02, 0x8894, V_PCH_PCR_FIA_LANE_OWN_USB3, MULCAST},
  0x28, 0xEA, 0x07, 0x00, 0x0F, 0x00, 0x5C, 0x89, 0x2A, 0x08, 0x30, 0x00, //  {0xEA, 0x0030082A, 0x895C, V_PCH_PCR_FIA_LANE_OWN_USB3, MULCAST},
  0x28, 0xEA, 0x07, 0x00, 0x0F, 0x00, 0x70, 0x89, 0x58, 0x21, 0x40, 0x33, //  {0xEA, 0x33402158, 0x8970, V_PCH_PCR_FIA_LANE_OWN_USB3, MULCAST},
  0x28, 0xEA, 0x07, 0x00, 0x0F, 0x00, 0x6C, 0x89, 0x28, 0x24, 0x04, 0x48, //  {0xEA, 0x48042428, 0x896C, V_PCH_PCR_FIA_LANE_OWN_USB3, MULCAST},
  0x28, 0xEA, 0x07, 0x00, 0x0F, 0x00, 0xC8, 0x89, 0x50, 0x88, 0x6D, 0x60, //  {0xEA, 0x606D8850, 0x89C8, V_PCH_PCR_FIA_LANE_OWN_USB3, MULCAST},
  0x28, 0xEA, 0x07, 0x00, 0x0F, 0x00, 0x88, 0x89, 0x00, 0x30, 0x74, 0x64, //  {0xEA, 0x64743000, 0x8988, V_PCH_PCR_FIA_LANE_OWN_USB3, MULCAST},
  0x28, 0xEA, 0x07, 0x00, 0x0F, 0x00, 0x24, 0x88, 0x0F, 0x0C, 0x0C, 0x84, //  {0xEA, 0x840C0C0F, 0x8824, V_PCH_PCR_FIA_LANE_OWN_USB3, MULCAST},
  0x28, 0xEA, 0x07, 0x00, 0x0F, 0x00, 0x2C, 0x89, 0x5A, 0x50, 0x08, 0x00, //  {0xEA, 0x0008505A, 0x892C, V_PCH_PCR_FIA_LANE_OWN_USB3, MULCAST},
  0x28, 0xEA, 0x07, 0x00, 0x0F, 0x00, 0x68, 0x89, 0x3E, 0x82, 0x18, 0x8A, //  {0xEA, 0x8A18823E, 0x8968, V_PCH_PCR_FIA_LANE_OWN_USB3, MULCAST},
  0x28, 0xEA, 0x07, 0x00, 0x0F, 0x00, 0x8C, 0x89, 0x58, 0xC0, 0x08, 0x00, //  {0xEA, 0x0008C058, 0x898C, V_PCH_PCR_FIA_LANE_OWN_USB3, MULCAST},
  0x28, 0xEA, 0x07, 0x00, 0x0F, 0x00, 0x00, 0x89, 0x10, 0x29, 0x52, 0x09, //  {0xEA, 0x09522910, 0x8900, V_PCH_PCR_FIA_LANE_OWN_USB3, MULCAST},
  0x28, 0xEA, 0x07, 0x00, 0x0F, 0x00, 0x64, 0x89, 0x00, 0xA0, 0x00, 0x00, //  {0xEA, 0x0000A000, 0x8964, V_PCH_PCR_FIA_LANE_OWN_USB3, MULCAST},
  0x28, 0xEA, 0x07, 0x00, 0x0F, 0x00, 0x18, 0x89, 0xBF, 0x00, 0x00, 0x00, //  {0xEA, 0x000000BF, 0x8918, V_PCH_PCR_FIA_LANE_OWN_USB3, MULCAST},
  0x28, 0xEA, 0x07, 0x00, 0x0F, 0x00, 0x9C, 0x89, 0x00, 0x00, 0xC0, 0x00, //  {0xEA, 0x00C00000, 0x899C, V_PCH_PCR_FIA_LANE_OWN_USB3, MULCAST},
  0x28, 0xEA, 0x07, 0x00, 0x0F, 0x00, 0x20, 0x88, 0x26, 0x16, 0x07, 0x0D, //  {0xEA, 0x0D071626, 0x8820, V_PCH_PCR_FIA_LANE_OWN_USB3, MULCAST},
  0x28, 0xEA, 0x07, 0x00, 0x0F, 0x00, 0x80, 0x89, 0x60, 0x07, 0xE8, 0x00, //  {0xEA, 0x00E80760, 0x8980, V_PCH_PCR_FIA_LANE_OWN_USB3, MULCAST},
  0x28, 0xE9, 0x07, 0x00, 0x0F, 0x00, 0x40, 0x83, 0x58, 0xCF, 0x05, 0x01, //  {0xE9, 0x0105CF58, 0x8340, V_PCH_PCR_FIA_LANE_OWN_PCIEDMI, MULCAST},
  0x28, 0xE9, 0x07, 0x00, 0x0F, 0x00, 0x44, 0x83, 0x48, 0xD5, 0x05, 0x01, //  {0xE9, 0x0105D548, 0x8344, V_PCH_PCR_FIA_LANE_OWN_PCIEDMI, MULCAST},
  0x28, 0xE9, 0x07, 0x00, 0x0F, 0x00, 0x40, 0x89, 0x4E, 0xCF, 0x18, 0x01, //  {0xE9, 0x0118CF4E, 0x8940, V_PCH_PCR_FIA_LANE_OWN_USB3, MULCAST},
  0x28, 0xE9, 0x07, 0x00, 0x0F, 0x00, 0x0C, 0x83, 0x1F, 0x9B, 0x12, 0x00, //  {0xE9, 0x00129B1F, 0x830C, V_PCH_PCR_FIA_LANE_OWN_PCIEDMI, MULCAST},
  0x28, 0xE9, 0x07, 0x00, 0x0F, 0x00, 0x58, 0x89, 0x08, 0xA4, 0x32, 0x01, //  {0xE9, 0x0132A408, 0x8958, V_PCH_PCR_FIA_LANE_OWN_USB3, MULCAST},
  0x28, 0xE9, 0x07, 0x00, 0x0F, 0x00, 0x98, 0x82, 0x20, 0x1E, 0x1F, 0x15, //  {0xE9, 0x151F1E20, 0x8298, V_PCH_PCR_FIA_LANE_OWN_PCIEDMI, MULCAST},
  0x28, 0xE9, 0x07, 0x00, 0x0F, 0x00, 0xE8, 0x83, 0x00, 0x48, 0x17, 0x1A, //  {0xE9, 0x1A174800, 0x83E8, V_PCH_PCR_FIA_LANE_OWN_PCIEDMI, MULCAST},
  0x28, 0xE9, 0x07, 0x00, 0x0F, 0x00, 0xE8, 0x89, 0x00, 0x48, 0x17, 0x1E, //  {0xE9, 0x1E174800, 0x89E8, V_PCH_PCR_FIA_LANE_OWN_USB3, MULCAST},
  0x28, 0xE9, 0x07, 0x00, 0x0F, 0x00, 0xCC, 0x82, 0x00, 0x08, 0x1F, 0x20, //  {0xE9, 0x201F0800, 0x82CC, V_PCH_PCR_FIA_LANE_OWN_PCIEDMI, MULCAST},
  0x28, 0xE9, 0x07, 0x00, 0x0F, 0x00, 0x18, 0x82, 0x7C, 0x00, 0x09, 0x02, //  {0xE9, 0x0209007C, 0x8218, V_PCH_PCR_FIA_LANE_OWN_PCIEDMI, MULCAST},
  0x28, 0xE9, 0x07, 0x00, 0x0F, 0x00, 0xA0, 0x89, 0xEC, 0x10, 0x00, 0x28, //  {0xE9, 0x280010EC, 0x89A0, V_PCH_PCR_FIA_LANE_OWN_USB3, MULCAST},
  0x28, 0xE9, 0x07, 0x00, 0x0F, 0x00, 0xA4, 0x89, 0x28, 0x28, 0x28, 0x00, //  {0xE9, 0x00282828, 0x89A4, V_PCH_PCR_FIA_LANE_OWN_USB3, MULCAST},
  0x28, 0xE9, 0x07, 0x00, 0x0F, 0x00, 0x94, 0x88, 0x02, 0x2A, 0x29, 0x28, //  {0xE9, 0x28292A02, 0x8894, V_PCH_PCR_FIA_LANE_OWN_USB3, MULCAST},
  0x28, 0xE9, 0x07, 0x00, 0x0F, 0x00, 0x94, 0x82, 0x06, 0x2A, 0x29, 0x28, //  {0xE9, 0x28292A06, 0x8294, V_PCH_PCR_FIA_LANE_OWN_PCIEDMI, MULCAST},
  0x28, 0xE9, 0x07, 0x00, 0x0F, 0x00, 0x5C, 0x89, 0x2A, 0x08, 0x30, 0x00, //  {0xE9, 0x0030082A, 0x895C, V_PCH_PCR_FIA_LANE_OWN_USB3, MULCAST},
  0x28, 0xE9, 0x07, 0x00, 0x0F, 0x00, 0x70, 0x89, 0x58, 0x21, 0x40, 0x33, //  {0xE9, 0x33402158, 0x8970, V_PCH_PCR_FIA_LANE_OWN_USB3, MULCAST},
  0x28, 0xE9, 0x07, 0x00, 0x0F, 0x00, 0x70, 0x83, 0x5A, 0x25, 0x40, 0x33, //  {0xE9, 0x3340255A, 0x8370, V_PCH_PCR_FIA_LANE_OWN_PCIEDMI, MULCAST},
  0x28, 0xE9, 0x07, 0x00, 0x0F, 0x00, 0x1C, 0x83, 0x08, 0x10, 0x39, 0x00, //  {0xE9, 0x00391008, 0x831C, V_PCH_PCR_FIA_LANE_OWN_PCIEDMI, MULCAST},
  0x28, 0xE9, 0x07, 0x00, 0x0F, 0x00, 0x50, 0x83, 0x3F, 0x3F, 0x3F, 0x04, //  {0xE9, 0x043F3F3F, 0x8350, V_PCH_PCR_FIA_LANE_OWN_PCIEDMI, MULCAST},
  0x28, 0xE9, 0x07, 0x00, 0x0F, 0x00, 0x6C, 0x89, 0x28, 0x24, 0x04, 0x48, //  {0xE9, 0x48042428, 0x896C, V_PCH_PCR_FIA_LANE_OWN_USB3, MULCAST},
  0x28, 0xE9, 0x07, 0x00, 0x0F, 0x00, 0xE4, 0x83, 0x50, 0x05, 0x0B, 0x4B, //  {0xE9, 0x4B0B0550, 0x83E4, V_PCH_PCR_FIA_LANE_OWN_PCIEDMI, MULCAST},
  0x28, 0xE9, 0x07, 0x00, 0x0F, 0x00, 0x1C, 0x82, 0x00, 0xC0, 0x00, 0x60, //  {0xE9, 0x6000C000, 0x821C, V_PCH_PCR_FIA_LANE_OWN_PCIEDMI, MULCAST},
  0x28, 0xE9, 0x07, 0x00, 0x0F, 0x00, 0xC8, 0x89, 0x50, 0x88, 0x6D, 0x60, //  {0xE9, 0x606D8850, 0x89C8, V_PCH_PCR_FIA_LANE_OWN_USB3, MULCAST},
  0x28, 0xE9, 0x07, 0x00, 0x0F, 0x00, 0x04, 0x82, 0x64, 0x00, 0x00, 0x00, //  {0xE9, 0x00000064, 0x8204, V_PCH_PCR_FIA_LANE_OWN_PCIEDMI, MULCAST},
  0x28, 0xE9, 0x07, 0x00, 0x0F, 0x00, 0x88, 0x89, 0x00, 0x30, 0x74, 0x64, //  {0xE9, 0x64743000, 0x8988, V_PCH_PCR_FIA_LANE_OWN_USB3, MULCAST},
  0x28, 0xE9, 0x07, 0x00, 0x0F, 0x00, 0x10, 0x82, 0x00, 0x00, 0xBF, 0x72, //  {0xE9, 0x72BF0000, 0x8210, V_PCH_PCR_FIA_LANE_OWN_PCIEDMI, MULCAST},
  0x28, 0xE9, 0x07, 0x00, 0x0F, 0x00, 0xC4, 0x82, 0x08, 0x0A, 0x00, 0x08, //  {0xE9, 0x08000A08, 0x82C4, V_PCH_PCR_FIA_LANE_OWN_PCIEDMI, MULCAST},
  0x28, 0xE9, 0x07, 0x00, 0x0F, 0x00, 0x8C, 0x83, 0x7C, 0x00, 0x08, 0x00, //  {0xE9, 0x0008007C, 0x838C, V_PCH_PCR_FIA_LANE_OWN_PCIEDMI, MULCAST},
  0x28, 0xE9, 0x07, 0x00, 0x0F, 0x00, 0x54, 0x83, 0x02, 0x00, 0xC0, 0x80, //  {0xE9, 0x80C00002, 0x8354, V_PCH_PCR_FIA_LANE_OWN_PCIEDMI, MULCAST},
  0x28, 0xE9, 0x07, 0x00, 0x0F, 0x00, 0x58, 0x83, 0x08, 0xA0, 0x31, 0x81, //  {0xE9, 0x8131A008, 0x8358, V_PCH_PCR_FIA_LANE_OWN_PCIEDMI, MULCAST},
  0x28, 0xE9, 0x07, 0x00, 0x0F, 0x00, 0xD4, 0x83, 0xC0, 0x00, 0x82, 0x00, //  {0xE9, 0x008200C0, 0x83D4, V_PCH_PCR_FIA_LANE_OWN_PCIEDMI, MULCAST},
  0x28, 0xE9, 0x07, 0x00, 0x0F, 0x00, 0x24, 0x88, 0x0F, 0x0C, 0x0C, 0x84, //  {0xE9, 0x840C0C0F, 0x8824, V_PCH_PCR_FIA_LANE_OWN_USB3, MULCAST},
  0x28, 0xE9, 0x07, 0x00, 0x0F, 0x00, 0x2C, 0x89, 0x5A, 0x50, 0x08, 0x00, //  {0xE9, 0x0008505A, 0x892C, V_PCH_PCR_FIA_LANE_OWN_USB3, MULCAST},
  0x28, 0xE9, 0x07, 0x00, 0x0F, 0x00, 0x68, 0x89, 0x3E, 0x82, 0x18, 0x8A, //  {0xE9, 0x8A18823E, 0x8968, V_PCH_PCR_FIA_LANE_OWN_USB3, MULCAST},
  0x28, 0xE9, 0x07, 0x00, 0x0F, 0x00, 0x8C, 0x89, 0x58, 0xC0, 0x08, 0x00, //  {0xE9, 0x0008C058, 0x898C, V_PCH_PCR_FIA_LANE_OWN_USB3, MULCAST},
  0x28, 0xE9, 0x07, 0x00, 0x0F, 0x00, 0x00, 0x89, 0x10, 0x29, 0x52, 0x09, //  {0xE9, 0x09522910, 0x8900, V_PCH_PCR_FIA_LANE_OWN_USB3, MULCAST},
  0x28, 0xE9, 0x07, 0x00, 0x0F, 0x00, 0x00, 0x83, 0x10, 0xA9, 0x52, 0x09, //  {0xE9, 0x0952A910, 0x8300, V_PCH_PCR_FIA_LANE_OWN_PCIEDMI, MULCAST},
  0x28, 0xE9, 0x07, 0x00, 0x0F, 0x00, 0x3C, 0x82, 0x02, 0x9F, 0x00, 0x00, //  {0xE9, 0x00009F02, 0x823C, V_PCH_PCR_FIA_LANE_OWN_PCIEDMI, MULCAST},
  0x28, 0xE9, 0x07, 0x00, 0x0F, 0x00, 0x64, 0x89, 0x00, 0xA0, 0x00, 0x00, //  {0xE9, 0x0000A000, 0x8964, V_PCH_PCR_FIA_LANE_OWN_USB3, MULCAST},
  0x28, 0xE9, 0x07, 0x00, 0x0F, 0x00, 0x18, 0x89, 0xBF, 0x00, 0x00, 0x00, //  {0xE9, 0x000000BF, 0x8918, V_PCH_PCR_FIA_LANE_OWN_USB3, MULCAST},
  0x28, 0xE9, 0x07, 0x00, 0x0F, 0x00, 0x9C, 0x89, 0x00, 0x00, 0xC0, 0x00, //  {0xE9, 0x00C00000, 0x899C, V_PCH_PCR_FIA_LANE_OWN_USB3, MULCAST},
  0x28, 0xE9, 0x07, 0x00, 0x0F, 0x00, 0x20, 0x82, 0x25, 0x16, 0x07, 0x0D, //  {0xE9, 0x0D071625, 0x8220, V_PCH_PCR_FIA_LANE_OWN_PCIEDMI, MULCAST},
  0x28, 0xE9, 0x07, 0x00, 0x0F, 0x00, 0x20, 0x88, 0x26, 0x16, 0x07, 0x0D, //  {0xE9, 0x0D071626, 0x8820, V_PCH_PCR_FIA_LANE_OWN_USB3, MULCAST},
  0x28, 0xE9, 0x07, 0x00, 0x0F, 0x00, 0x80, 0x89, 0x60, 0x07, 0xE8, 0x00, //  {0xE9, 0x00E80760, 0x8980, V_PCH_PCR_FIA_LANE_OWN_USB3, MULCAST},
  0x28, 0xE9, 0x07, 0x00, 0x0F, 0x00, 0x40, 0x82, 0x00, 0xB0, 0x02, 0xFF, //  {0xE9, 0xFF02B000, 0x8240, V_PCH_PCR_FIA_LANE_OWN_PCIEDMI, MULCAST},
  0x28, 0xEA, 0x07, 0x00, 0x0F, 0x00, 0x64, 0x89, 0x08, 0xA0, 0x00, 0x00, //  {0xEA, 0x0000A008, 0x8964, V_PCH_PCR_FIA_LANE_OWN_USB3, MULCAST},
  0x28, 0xE9, 0x07, 0x00, 0x0F, 0x00, 0x64, 0x89, 0x08, 0xA0, 0x00, 0x00, //  {0xE9, 0x0000A008, 0x8964, V_PCH_PCR_FIA_LANE_OWN_USB3, MULCAST},
  0x0F, 0x00, 0x00, 0x00,                                                 //  End Table Marker
};

PCH_SBI_HSIO_TABLE_STRUCT PchHHsio_Bx[] = {
  {0xA8, 0x0013003E, 0x8000, PCH_LANE_OWN_COMMON}, //LANE
  {0xA8, 0x200000E0, 0x8004, PCH_LANE_OWN_COMMON}, //LANE
  {0xA8, 0x00000006, 0x803C, PCH_LANE_OWN_COMMON}, //LANE
  {0xA8, 0x0A020904, 0x8110, PCH_LANE_OWN_COMMON}, //LANE
  {0xA8, 0x001F0006, 0x8128, PCH_LANE_OWN_COMMON}, //LANE
  {0xA8, 0x78003C00, 0x8130, PCH_LANE_OWN_COMMON}, //LANE
  {0xA9, 0x00000006, 0x803C, PCH_LANE_OWN_COMMON}, //LANE
  {0xE9, 0x00000006, 0x803C, PCH_LANE_OWN_COMMON}, //LANE
  {0xEA, 0x0013003E, 0x8000, PCH_LANE_OWN_COMMON}, //LANE
  {0xEA, 0x200000E0, 0x8004, PCH_LANE_OWN_COMMON}, //LANE
  {0xEA, 0x00000006, 0x803C, PCH_LANE_OWN_COMMON}, //LANE
  {0xEA, 0x0000030A, 0x812C, PCH_LANE_OWN_COMMON}, //LANE
  {0xEA, 0x78003C00, 0x8130, PCH_LANE_OWN_COMMON}, //LANE
  {0xEA, 0x010201E0, 0xC028, PCH_LANE_BDCAST}, //BDCAST
  {0xE9, 0x010201E0, 0xC028, PCH_LANE_BDCAST}, //BDCAST
  {0xA9, 0x010201E0, 0xC028, PCH_LANE_BDCAST}, //BDCAST
  {0xA8, 0x010201E0, 0xC028, PCH_LANE_BDCAST}, //BDCAST
  {0xA9, 0x0102C907, 0x854C, V_PCH_PCR_FIA_LANE_OWN_PCIEDMI}, //MULCAST
  {0xA9, 0x0102C907, 0x834C, V_PCH_PCR_FIA_LANE_OWN_PCIEDMI}, //MULCAST
  {0xA9, 0x01051548, 0x8B44, V_PCH_PCR_FIA_LANE_OWN_SATA}, //MULCAST
  {0xA9, 0x0105154C, 0x8B48, V_PCH_PCR_FIA_LANE_OWN_SATA}, //MULCAST
  {0xA9, 0x0105194C, 0x8748, V_PCH_PCR_FIA_LANE_OWN_GBE}, //MULCAST
  {0xA9, 0x0108D15E, 0x8B40, V_PCH_PCR_FIA_LANE_OWN_SATA}, //MULCAST
  {0xA9, 0x00129B00, 0x830C, V_PCH_PCR_FIA_LANE_OWN_PCIEDMI}, //MULCAST
  {0xA9, 0x0132A008, 0x8B58, V_PCH_PCR_FIA_LANE_OWN_SATA}, //MULCAST
  {0xA9, 0x151F2800, 0x8A98, V_PCH_PCR_FIA_LANE_OWN_SATA}, //MULCAST
  {0xA9, 0x24740020, 0x8588, V_PCH_PCR_FIA_LANE_OWN_PCIEDMI}, //MULCAST
  {0xA9, 0x24740020, 0x8388, V_PCH_PCR_FIA_LANE_OWN_PCIEDMI}, //MULCAST
  {0xA9, 0x280010EC, 0x85A0, V_PCH_PCR_FIA_LANE_OWN_PCIEDMI}, //MULCAST
  {0xA9, 0x280010EC, 0x83A0, V_PCH_PCR_FIA_LANE_OWN_PCIEDMI}, //MULCAST
  {0xA9, 0x00282828, 0x85A4, V_PCH_PCR_FIA_LANE_OWN_PCIEDMI}, //MULCAST
  {0xA9, 0x00282828, 0x83A4, V_PCH_PCR_FIA_LANE_OWN_PCIEDMI}, //MULCAST
  {0xA9, 0x28292A06, 0x8A94, V_PCH_PCR_FIA_LANE_OWN_SATA}, //MULCAST
  {0xA9, 0x33402158, 0x8570, V_PCH_PCR_FIA_LANE_OWN_PCIEDMI}, //MULCAST
  {0xA9, 0x33402158, 0x8370, V_PCH_PCR_FIA_LANE_OWN_PCIEDMI}, //MULCAST
  {0xA9, 0x3340215A, 0x8770, V_PCH_PCR_FIA_LANE_OWN_GBE}, //MULCAST
  {0xA9, 0x3340215A, 0x8B70, V_PCH_PCR_FIA_LANE_OWN_SATA}, //MULCAST
  {0xA9, 0x04000045, 0x8A04, V_PCH_PCR_FIA_LANE_OWN_SATA}, //MULCAST
  {0xA9, 0x04391008, 0x851C, V_PCH_PCR_FIA_LANE_OWN_PCIEDMI}, //MULCAST
  {0xA9, 0x0004A000, 0x8564, V_PCH_PCR_FIA_LANE_OWN_PCIEDMI}, //MULCAST
  {0xA9, 0x00000050, 0x8308, V_PCH_PCR_FIA_LANE_OWN_PCIEDMI}, //MULCAST
  {0xA9, 0x600D8850, 0x85C8, V_PCH_PCR_FIA_LANE_OWN_PCIEDMI}, //MULCAST
  {0xA9, 0x600D8850, 0x83C8, V_PCH_PCR_FIA_LANE_OWN_PCIEDMI}, //MULCAST
  {0xA9, 0x00080058, 0x838C, V_PCH_PCR_FIA_LANE_OWN_PCIEDMI}, //MULCAST
  {0xA9, 0x80C00102, 0x8B54, V_PCH_PCR_FIA_LANE_OWN_SATA}, //MULCAST
  {0xA9, 0x0008105A, 0x852C, V_PCH_PCR_FIA_LANE_OWN_PCIEDMI}, //MULCAST
  {0xA9, 0x0008105A, 0x832C, V_PCH_PCR_FIA_LANE_OWN_PCIEDMI}, //MULCAST
  {0xA9, 0x8131A008, 0x8758, V_PCH_PCR_FIA_LANE_OWN_GBE}, //MULCAST
  {0xA9, 0x8131A408, 0x8558, V_PCH_PCR_FIA_LANE_OWN_PCIEDMI}, //MULCAST
  {0xA9, 0x8131A408, 0x8358, V_PCH_PCR_FIA_LANE_OWN_PCIEDMI}, //MULCAST
  {0xA9, 0x0008407C, 0x8B8C, V_PCH_PCR_FIA_LANE_OWN_SATA}, //MULCAST
  {0xA9, 0x0008807C, 0x878C, V_PCH_PCR_FIA_LANE_OWN_GBE}, //MULCAST
  {0xA9, 0x88188206, 0x8568, V_PCH_PCR_FIA_LANE_OWN_PCIEDMI}, //MULCAST
  {0xA9, 0x88188206, 0x8368, V_PCH_PCR_FIA_LANE_OWN_PCIEDMI}, //MULCAST
  {0xA9, 0x0008A000, 0x8364, V_PCH_PCR_FIA_LANE_OWN_PCIEDMI}, //MULCAST
  {0xA9, 0x09526910, 0x8700, V_PCH_PCR_FIA_LANE_OWN_GBE}, //MULCAST
  {0xA9, 0x0952A810, 0x8500, V_PCH_PCR_FIA_LANE_OWN_PCIEDMI}, //MULCAST
  {0xA9, 0x0952A810, 0x8300, V_PCH_PCR_FIA_LANE_OWN_PCIEDMI}, //MULCAST
  {0xA9, 0x0952A910, 0x8B00, V_PCH_PCR_FIA_LANE_OWN_SATA}, //MULCAST
  {0xA9, 0x00AC0000, 0x859C, V_PCH_PCR_FIA_LANE_OWN_PCIEDMI}, //MULCAST
  {0xA9, 0x00AC0000, 0x839C, V_PCH_PCR_FIA_LANE_OWN_PCIEDMI}, //MULCAST
  {0xA9, 0xB801822A, 0x8B68, V_PCH_PCR_FIA_LANE_OWN_SATA}, //MULCAST
  {0xA9, 0x000C0058, 0x858C, V_PCH_PCR_FIA_LANE_OWN_PCIEDMI}, //MULCAST
  {0xA9, 0xC0A80760, 0x8380, V_PCH_PCR_FIA_LANE_OWN_PCIEDMI}, //MULCAST
  {0xA9, 0xE0A80760, 0x8580, V_PCH_PCR_FIA_LANE_OWN_PCIEDMI}, //MULCAST
  {0xA8, 0x0102C907, 0x834C, V_PCH_PCR_FIA_LANE_OWN_PCIEDMI}, //MULCAST
  {0xA8, 0x01051548, 0x8B44, V_PCH_PCR_FIA_LANE_OWN_SATA}, //MULCAST
  {0xA8, 0x0105154C, 0x8B48, V_PCH_PCR_FIA_LANE_OWN_SATA}, //MULCAST
  {0xA8, 0x0105194C, 0x8748, V_PCH_PCR_FIA_LANE_OWN_GBE}, //MULCAST
  {0xA8, 0x0108D15E, 0x8B40, V_PCH_PCR_FIA_LANE_OWN_SATA}, //MULCAST
  {0xA8, 0x00129B00, 0x830C, V_PCH_PCR_FIA_LANE_OWN_PCIEDMI}, //MULCAST
  {0xA8, 0x0132A008, 0x8B58, V_PCH_PCR_FIA_LANE_OWN_SATA}, //MULCAST
  {0xA8, 0x151F2800, 0x8A98, V_PCH_PCR_FIA_LANE_OWN_SATA}, //MULCAST
  {0xA8, 0x24740020, 0x8388, V_PCH_PCR_FIA_LANE_OWN_PCIEDMI}, //MULCAST
  {0xA8, 0x280010EC, 0x83A0, V_PCH_PCR_FIA_LANE_OWN_PCIEDMI}, //MULCAST
  {0xA8, 0x00282828, 0x83A4, V_PCH_PCR_FIA_LANE_OWN_PCIEDMI}, //MULCAST
  {0xA8, 0x28292A06, 0x8A94, V_PCH_PCR_FIA_LANE_OWN_SATA}, //MULCAST
  {0xA8, 0x33402158, 0x8370, V_PCH_PCR_FIA_LANE_OWN_PCIEDMI}, //MULCAST
  {0xA8, 0x3340215A, 0x8770, V_PCH_PCR_FIA_LANE_OWN_GBE}, //MULCAST
  {0xA8, 0x3340215A, 0x8B70, V_PCH_PCR_FIA_LANE_OWN_SATA}, //MULCAST
  {0xA8, 0x04000045, 0x8A04, V_PCH_PCR_FIA_LANE_OWN_SATA}, //MULCAST
  {0xA8, 0x00000050, 0x8308, V_PCH_PCR_FIA_LANE_OWN_PCIEDMI}, //MULCAST
  {0xA8, 0x600D8850, 0x83C8, V_PCH_PCR_FIA_LANE_OWN_PCIEDMI}, //MULCAST
  {0xA8, 0x00080058, 0x838C, V_PCH_PCR_FIA_LANE_OWN_PCIEDMI}, //MULCAST
  {0xA8, 0x80C00102, 0x8B54, V_PCH_PCR_FIA_LANE_OWN_SATA}, //MULCAST
  {0xA8, 0x0008105A, 0x832C, V_PCH_PCR_FIA_LANE_OWN_PCIEDMI}, //MULCAST
  {0xA8, 0x8131A008, 0x8758, V_PCH_PCR_FIA_LANE_OWN_GBE}, //MULCAST
  {0xA8, 0x8131A408, 0x8358, V_PCH_PCR_FIA_LANE_OWN_PCIEDMI}, //MULCAST
  {0xA8, 0x0008407C, 0x8B8C, V_PCH_PCR_FIA_LANE_OWN_SATA}, //MULCAST
  {0xA8, 0x0008807C, 0x878C, V_PCH_PCR_FIA_LANE_OWN_GBE}, //MULCAST
  {0xA8, 0x88188206, 0x8368, V_PCH_PCR_FIA_LANE_OWN_PCIEDMI}, //MULCAST
  {0xA8, 0x0008A000, 0x8364, V_PCH_PCR_FIA_LANE_OWN_PCIEDMI}, //MULCAST
  {0xA8, 0x09526910, 0x8700, V_PCH_PCR_FIA_LANE_OWN_GBE}, //MULCAST
  {0xA8, 0x0952A810, 0x8300, V_PCH_PCR_FIA_LANE_OWN_PCIEDMI}, //MULCAST
  {0xA8, 0x0952A910, 0x8B00, V_PCH_PCR_FIA_LANE_OWN_SATA}, //MULCAST
  {0xA8, 0x00AC0000, 0x839C, V_PCH_PCR_FIA_LANE_OWN_PCIEDMI}, //MULCAST
  {0xA8, 0xB801822A, 0x8B68, V_PCH_PCR_FIA_LANE_OWN_SATA}, //MULCAST
  {0xA8, 0xC0A80760, 0x8380, V_PCH_PCR_FIA_LANE_OWN_PCIEDMI}, //MULCAST
  {0xEA, 0x0105174C, 0x8D44, V_PCH_PCR_FIA_LANE_OWN_SSIC}, //MULCAST
  {0xEA, 0x0105194C, 0x8D48, V_PCH_PCR_FIA_LANE_OWN_SSIC}, //MULCAST
  {0xEA, 0x1F1F0000, 0x885C, V_PCH_PCR_FIA_LANE_OWN_USB3}, //MULCAST
  {0xEA, 0x020019CD, 0x8DC4, V_PCH_PCR_FIA_LANE_OWN_SSIC}, //MULCAST
  {0xEA, 0x00003114, 0x8CA0, V_PCH_PCR_FIA_LANE_OWN_SSIC}, //MULCAST
  {0xEA, 0x0330831F, 0x8D14, V_PCH_PCR_FIA_LANE_OWN_SSIC}, //MULCAST
  {0xEA, 0x3340215A, 0x8D70, V_PCH_PCR_FIA_LANE_OWN_SSIC}, //MULCAST
  {0xEA, 0x80C00100, 0x8D54, V_PCH_PCR_FIA_LANE_OWN_SSIC}, //MULCAST
  {0xEA, 0x8131A008, 0x8D58, V_PCH_PCR_FIA_LANE_OWN_SSIC}, //MULCAST
  {0xEA, 0x0008807C, 0x8D8C, V_PCH_PCR_FIA_LANE_OWN_SSIC}, //MULCAST
  {0xEA, 0x09526910, 0x8D00, V_PCH_PCR_FIA_LANE_OWN_SSIC}, //MULCAST
  {0xEA, 0xC0000100, 0x8C00, V_PCH_PCR_FIA_LANE_OWN_SSIC}, //MULCAST
  {0xE9, 0x0102C907, 0x834C, V_PCH_PCR_FIA_LANE_OWN_PCIEDMI}, //MULCAST
  {0xE9, 0x0105194C, 0x8748, V_PCH_PCR_FIA_LANE_OWN_GBE}, //MULCAST
  {0xE9, 0x00129B00, 0x830C, V_PCH_PCR_FIA_LANE_OWN_PCIEDMI}, //MULCAST
  {0xE9, 0x1F1F0000, 0x885C, V_PCH_PCR_FIA_LANE_OWN_USB3}, //MULCAST
  {0xE9, 0x24740020, 0x8388, V_PCH_PCR_FIA_LANE_OWN_PCIEDMI}, //MULCAST
  {0xE9, 0x280010EC, 0x83A0, V_PCH_PCR_FIA_LANE_OWN_PCIEDMI}, //MULCAST
  {0xE9, 0x00282828, 0x83A4, V_PCH_PCR_FIA_LANE_OWN_PCIEDMI}, //MULCAST
  {0xE9, 0x33402158, 0x8370, V_PCH_PCR_FIA_LANE_OWN_PCIEDMI}, //MULCAST
  {0xE9, 0x3340215A, 0x8770, V_PCH_PCR_FIA_LANE_OWN_GBE}, //MULCAST
  {0xE9, 0x00000050, 0x8308, V_PCH_PCR_FIA_LANE_OWN_PCIEDMI}, //MULCAST
  {0xE9, 0x600D8850, 0x83C8, V_PCH_PCR_FIA_LANE_OWN_PCIEDMI}, //MULCAST
  {0xE9, 0x00080058, 0x838C, V_PCH_PCR_FIA_LANE_OWN_PCIEDMI}, //MULCAST
  {0xE9, 0x0008105A, 0x832C, V_PCH_PCR_FIA_LANE_OWN_PCIEDMI}, //MULCAST
  {0xE9, 0x8131A008, 0x8758, V_PCH_PCR_FIA_LANE_OWN_GBE}, //MULCAST
  {0xE9, 0x8131A408, 0x8358, V_PCH_PCR_FIA_LANE_OWN_PCIEDMI}, //MULCAST
  {0xE9, 0x0008807C, 0x878C, V_PCH_PCR_FIA_LANE_OWN_GBE}, //MULCAST
  {0xE9, 0x88188206, 0x8368, V_PCH_PCR_FIA_LANE_OWN_PCIEDMI}, //MULCAST
  {0xE9, 0x0008A000, 0x8364, V_PCH_PCR_FIA_LANE_OWN_PCIEDMI}, //MULCAST
  {0xE9, 0x09526910, 0x8700, V_PCH_PCR_FIA_LANE_OWN_GBE}, //MULCAST
  {0xE9, 0x0952A810, 0x8300, V_PCH_PCR_FIA_LANE_OWN_PCIEDMI}, //MULCAST
  {0xE9, 0x00AC0000, 0x839C, V_PCH_PCR_FIA_LANE_OWN_PCIEDMI}, //MULCAST
  {0xE9, 0xC0A80760, 0x8380, V_PCH_PCR_FIA_LANE_OWN_PCIEDMI}, //MULCAST
  {0xA9, 0x0004A008, 0x8564, V_PCH_PCR_FIA_LANE_OWN_PCIEDMI}, //MULCAST
  {0xA9, 0x0008A008, 0x8364, V_PCH_PCR_FIA_LANE_OWN_PCIEDMI}, //MULCAST
  {0xA8, 0x0008A008, 0x8364, V_PCH_PCR_FIA_LANE_OWN_PCIEDMI}, //MULCAST
  {0xE9, 0x0008A008, 0x8364, V_PCH_PCR_FIA_LANE_OWN_PCIEDMI}, //MULCAST
};
