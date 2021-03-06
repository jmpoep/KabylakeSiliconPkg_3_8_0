/** @file
  GPIO pins for SKL-PCH-LP,

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
#ifndef _GPIO_PINS_SKL_LP_H_
#define _GPIO_PINS_SKL_LP_H_
///
/// This header file should be used together with
/// PCH GPIO lib in C and ASL. All defines used
/// must match both ASL/C syntax
///

///
/// SKL LP GPIO Groups
/// Use below for functions from PCH GPIO Lib which
/// require GpioGroup as argument
///
#define GPIO_SKL_LP_GROUP_GPP_A  0x0200
#define GPIO_SKL_LP_GROUP_GPP_B  0x0201
#define GPIO_SKL_LP_GROUP_GPP_C  0x0202
#define GPIO_SKL_LP_GROUP_GPP_D  0x0203
#define GPIO_SKL_LP_GROUP_GPP_E  0x0204
#define GPIO_SKL_LP_GROUP_GPP_F  0x0205
#define GPIO_SKL_LP_GROUP_GPP_G  0x0206
#define GPIO_SKL_LP_GROUP_GPD    0x0207

///
/// SKL LP GPIO pins
/// Use below for functions from PCH GPIO Lib which
/// require GpioPad as argument. Encoding used here
/// has all information required by library functions
///
#define GPIO_SKL_LP_GPP_A0      0x02000000
#define GPIO_SKL_LP_GPP_A1      0x02000001
#define GPIO_SKL_LP_GPP_A2      0x02000002
#define GPIO_SKL_LP_GPP_A3      0x02000003
#define GPIO_SKL_LP_GPP_A4      0x02000004
#define GPIO_SKL_LP_GPP_A5      0x02000005
#define GPIO_SKL_LP_GPP_A6      0x02000006
#define GPIO_SKL_LP_GPP_A7      0x02000007
#define GPIO_SKL_LP_GPP_A8      0x02000008
#define GPIO_SKL_LP_GPP_A9      0x02000009
#define GPIO_SKL_LP_GPP_A10     0x0200000A
#define GPIO_SKL_LP_GPP_A11     0x0200000B
#define GPIO_SKL_LP_GPP_A12     0x0200000C
#define GPIO_SKL_LP_GPP_A13     0x0200000D
#define GPIO_SKL_LP_GPP_A14     0x0200000E
#define GPIO_SKL_LP_GPP_A15     0x0200000F
#define GPIO_SKL_LP_GPP_A16     0x02000010
#define GPIO_SKL_LP_GPP_A17     0x02000011
#define GPIO_SKL_LP_GPP_A18     0x02000012
#define GPIO_SKL_LP_GPP_A19     0x02000013
#define GPIO_SKL_LP_GPP_A20     0x02000014
#define GPIO_SKL_LP_GPP_A21     0x02000015
#define GPIO_SKL_LP_GPP_A22     0x02000016
#define GPIO_SKL_LP_GPP_A23     0x02000017
#define GPIO_SKL_LP_GPP_B0      0x02010000
#define GPIO_SKL_LP_GPP_B1      0x02010001
#define GPIO_SKL_LP_GPP_B2      0x02010002
#define GPIO_SKL_LP_GPP_B3      0x02010003
#define GPIO_SKL_LP_GPP_B4      0x02010004
#define GPIO_SKL_LP_GPP_B5      0x02010005
#define GPIO_SKL_LP_GPP_B6      0x02010006
#define GPIO_SKL_LP_GPP_B7      0x02010007
#define GPIO_SKL_LP_GPP_B8      0x02010008
#define GPIO_SKL_LP_GPP_B9      0x02010009
#define GPIO_SKL_LP_GPP_B10     0x0201000A
#define GPIO_SKL_LP_GPP_B11     0x0201000B
#define GPIO_SKL_LP_GPP_B12     0x0201000C
#define GPIO_SKL_LP_GPP_B13     0x0201000D
#define GPIO_SKL_LP_GPP_B14     0x0201000E
#define GPIO_SKL_LP_GPP_B15     0x0201000F
#define GPIO_SKL_LP_GPP_B16     0x02010010
#define GPIO_SKL_LP_GPP_B17     0x02010011
#define GPIO_SKL_LP_GPP_B18     0x02010012
#define GPIO_SKL_LP_GPP_B19     0x02010013
#define GPIO_SKL_LP_GPP_B20     0x02010014
#define GPIO_SKL_LP_GPP_B21     0x02010015
#define GPIO_SKL_LP_GPP_B22     0x02010016
#define GPIO_SKL_LP_GPP_B23     0x02010017
#define GPIO_SKL_LP_GPP_C0      0x02020000
#define GPIO_SKL_LP_GPP_C1      0x02020001
#define GPIO_SKL_LP_GPP_C2      0x02020002
#define GPIO_SKL_LP_GPP_C3      0x02020003
#define GPIO_SKL_LP_GPP_C4      0x02020004
#define GPIO_SKL_LP_GPP_C5      0x02020005
#define GPIO_SKL_LP_GPP_C6      0x02020006
#define GPIO_SKL_LP_GPP_C7      0x02020007
#define GPIO_SKL_LP_GPP_C8      0x02020008
#define GPIO_SKL_LP_GPP_C9      0x02020009
#define GPIO_SKL_LP_GPP_C10     0x0202000A
#define GPIO_SKL_LP_GPP_C11     0x0202000B
#define GPIO_SKL_LP_GPP_C12     0x0202000C
#define GPIO_SKL_LP_GPP_C13     0x0202000D
#define GPIO_SKL_LP_GPP_C14     0x0202000E
#define GPIO_SKL_LP_GPP_C15     0x0202000F
#define GPIO_SKL_LP_GPP_C16     0x02020010
#define GPIO_SKL_LP_GPP_C17     0x02020011
#define GPIO_SKL_LP_GPP_C18     0x02020012
#define GPIO_SKL_LP_GPP_C19     0x02020013
#define GPIO_SKL_LP_GPP_C20     0x02020014
#define GPIO_SKL_LP_GPP_C21     0x02020015
#define GPIO_SKL_LP_GPP_C22     0x02020016
#define GPIO_SKL_LP_GPP_C23     0x02020017
#define GPIO_SKL_LP_GPP_D0      0x02030000
#define GPIO_SKL_LP_GPP_D1      0x02030001
#define GPIO_SKL_LP_GPP_D2      0x02030002
#define GPIO_SKL_LP_GPP_D3      0x02030003
#define GPIO_SKL_LP_GPP_D4      0x02030004
#define GPIO_SKL_LP_GPP_D5      0x02030005
#define GPIO_SKL_LP_GPP_D6      0x02030006
#define GPIO_SKL_LP_GPP_D7      0x02030007
#define GPIO_SKL_LP_GPP_D8      0x02030008
#define GPIO_SKL_LP_GPP_D9      0x02030009
#define GPIO_SKL_LP_GPP_D10     0x0203000A
#define GPIO_SKL_LP_GPP_D11     0x0203000B
#define GPIO_SKL_LP_GPP_D12     0x0203000C
#define GPIO_SKL_LP_GPP_D13     0x0203000D
#define GPIO_SKL_LP_GPP_D14     0x0203000E
#define GPIO_SKL_LP_GPP_D15     0x0203000F
#define GPIO_SKL_LP_GPP_D16     0x02030010
#define GPIO_SKL_LP_GPP_D17     0x02030011
#define GPIO_SKL_LP_GPP_D18     0x02030012
#define GPIO_SKL_LP_GPP_D19     0x02030013
#define GPIO_SKL_LP_GPP_D20     0x02030014
#define GPIO_SKL_LP_GPP_D21     0x02030015
#define GPIO_SKL_LP_GPP_D22     0x02030016
#define GPIO_SKL_LP_GPP_D23     0x02030017
#define GPIO_SKL_LP_GPP_E0      0x02040000
#define GPIO_SKL_LP_GPP_E1      0x02040001
#define GPIO_SKL_LP_GPP_E2      0x02040002
#define GPIO_SKL_LP_GPP_E3      0x02040003
#define GPIO_SKL_LP_GPP_E4      0x02040004
#define GPIO_SKL_LP_GPP_E5      0x02040005
#define GPIO_SKL_LP_GPP_E6      0x02040006
#define GPIO_SKL_LP_GPP_E7      0x02040007
#define GPIO_SKL_LP_GPP_E8      0x02040008
#define GPIO_SKL_LP_GPP_E9      0x02040009
#define GPIO_SKL_LP_GPP_E10     0x0204000A
#define GPIO_SKL_LP_GPP_E11     0x0204000B
#define GPIO_SKL_LP_GPP_E12     0x0204000C
#define GPIO_SKL_LP_GPP_E13     0x0204000D
#define GPIO_SKL_LP_GPP_E14     0x0204000E
#define GPIO_SKL_LP_GPP_E15     0x0204000F
#define GPIO_SKL_LP_GPP_E16     0x02040010
#define GPIO_SKL_LP_GPP_E17     0x02040011
#define GPIO_SKL_LP_GPP_E18     0x02040012
#define GPIO_SKL_LP_GPP_E19     0x02040013
#define GPIO_SKL_LP_GPP_E20     0x02040014
#define GPIO_SKL_LP_GPP_E21     0x02040015
#define GPIO_SKL_LP_GPP_E22     0x02040016
#define GPIO_SKL_LP_GPP_E23     0x02040017
#define GPIO_SKL_LP_GPP_F0      0x02050000
#define GPIO_SKL_LP_GPP_F1      0x02050001
#define GPIO_SKL_LP_GPP_F2      0x02050002
#define GPIO_SKL_LP_GPP_F3      0x02050003
#define GPIO_SKL_LP_GPP_F4      0x02050004
#define GPIO_SKL_LP_GPP_F5      0x02050005
#define GPIO_SKL_LP_GPP_F6      0x02050006
#define GPIO_SKL_LP_GPP_F7      0x02050007
#define GPIO_SKL_LP_GPP_F8      0x02050008
#define GPIO_SKL_LP_GPP_F9      0x02050009
#define GPIO_SKL_LP_GPP_F10     0x0205000A
#define GPIO_SKL_LP_GPP_F11     0x0205000B
#define GPIO_SKL_LP_GPP_F12     0x0205000C
#define GPIO_SKL_LP_GPP_F13     0x0205000D
#define GPIO_SKL_LP_GPP_F14     0x0205000E
#define GPIO_SKL_LP_GPP_F15     0x0205000F
#define GPIO_SKL_LP_GPP_F16     0x02050010
#define GPIO_SKL_LP_GPP_F17     0x02050011
#define GPIO_SKL_LP_GPP_F18     0x02050012
#define GPIO_SKL_LP_GPP_F19     0x02050013
#define GPIO_SKL_LP_GPP_F20     0x02050014
#define GPIO_SKL_LP_GPP_F21     0x02050015
#define GPIO_SKL_LP_GPP_F22     0x02050016
#define GPIO_SKL_LP_GPP_F23     0x02050017
#define GPIO_SKL_LP_GPP_G0      0x02060000
#define GPIO_SKL_LP_GPP_G1      0x02060001
#define GPIO_SKL_LP_GPP_G2      0x02060002
#define GPIO_SKL_LP_GPP_G3      0x02060003
#define GPIO_SKL_LP_GPP_G4      0x02060004
#define GPIO_SKL_LP_GPP_G5      0x02060005
#define GPIO_SKL_LP_GPP_G6      0x02060006
#define GPIO_SKL_LP_GPP_G7      0x02060007
#define GPIO_SKL_LP_GPD0        0x02070000
#define GPIO_SKL_LP_GPD1        0x02070001
#define GPIO_SKL_LP_GPD2        0x02070002
#define GPIO_SKL_LP_GPD3        0x02070003
#define GPIO_SKL_LP_GPD4        0x02070004
#define GPIO_SKL_LP_GPD5        0x02070005
#define GPIO_SKL_LP_GPD6        0x02070006
#define GPIO_SKL_LP_GPD7        0x02070007
#define GPIO_SKL_LP_GPD8        0x02070008
#define GPIO_SKL_LP_GPD9        0x02070009
#define GPIO_SKL_LP_GPD10       0x0207000A
#define GPIO_SKL_LP_GPD11       0x0207000B

#endif
