/** @file
  Policy definition for Internal Graphics Config Block (PostMem)

 @copyright
  INTEL CONFIDENTIAL
  Copyright 2014 - 2019 Intel Corporation.

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
#ifndef _GRAPHICS_PEI_CONFIG_H_
#define _GRAPHICS_PEI_CONFIG_H_
#pragma pack(push, 1)

#define GRAPHICS_PEI_CONFIG_REVISION 2

/**
  This configuration block is to configure IGD related variables used in PostMem PEI.
  If Intel Gfx Device is not supported, all policies can be ignored.
  <b>Revision 1</b>:
  - Initial version.
  <b>Revision 2</b>:
  - Added ProgramGtChickenBits.
**/
typedef struct {
  CONFIG_BLOCK_HEADER   Header;                   ///< Offset 0-27 Config Block Header
#ifndef MINTREE_FLAG
  UINT32                RenderStandby     : 1;    ///< Offset 28:0 :<b>(Test)</b> This field is used to enable or disable RC6 (Render Standby): 0=FALSE, <b>1=TRUE</b>
  UINT32                PmSupport         : 1;    ///< Offset 28:1 :<b>(Test)</b> IGD PM Support TRUE/FALSE: 0=FALSE, <b>1=TRUE</b>
  UINT32                PavpEnable        : 1;    ///< Offset 28:2 :IGD PAVP TRUE/FALSE: 0=FALSE, <b>1=TRUE</b>
  /**
    Offset 28:3
    CdClock Frequency select\n
    0   = 337.5 Mhz, 1 = 450 Mhz,\n
    2   = 540 Mhz,<b> 3 = 675 Mhz</b>,\n
  **/
  UINT32                CdClock            : 3;
#endif //MINTREE_FLAG
  UINT32                PeiGraphicsPeimInit: 1;   ///< Offset 28:6 :This policy is used to enable/disable Intel Gfx PEIM.<b>0- Disable</b>, 1- Enable
#ifndef MINTREE_FLAG
  UINT32                CdynmaxClampEnable : 1;   ///< Offset 28:7 : This policy is used to enable/disable CDynmax Clamping Feature (CCF) <b>1- Enable</b>, 0- Disable
  UINT32                GtFreqMax          : 8;   ///< Offset 28:8 : <b>(Test)</b> Max GT frequency limited by user in multiples of 50MHz: Default value which indicates normal frequency is <b>0xFF</b>
  UINT32                RsvdBits0          : 16;  ///< Offser 28:16 :Reserved for future use
#else
  UINT32                RsvdBits0          : 31;  ///< Offser 28:16 :Reserved for future use
#endif //MINTREE_FLAG
  VOID*                 LogoPtr;                  ///< Offset 32 Address of Logo to be displayed in PEI
  UINT32                LogoSize;                 ///< Offset 36 Logo Size
  VOID*                 GraphicsConfigPtr;        ///< Offset 40 Address of the Graphics Configuration Table
  UINT8                 ProgramGtChickenBits;     ///< Offser 52 Program GT Chicket bits in GTTMMADR + 0xD00 BITS [3:1].
  UINT8                 Reserved1[3];             ///< Offset 53 Reserved for future use.
} GRAPHICS_PEI_CONFIG;
#pragma pack(pop)

#endif // _GRAPHICS_PEI_CONFIG_H_
