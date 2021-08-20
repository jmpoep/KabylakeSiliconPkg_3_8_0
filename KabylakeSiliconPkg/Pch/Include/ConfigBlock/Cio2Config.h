/** @file
  CIO2 policy

 @copyright
  INTEL CONFIDENTIAL
  Copyright 2015 - 2016 Intel Corporation.

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
#ifndef _CIO2_CONFIG_H_
#define _CIO2_CONFIG_H_

#define CIO2_CONFIG_REVISION 1
extern EFI_GUID gCio2ConfigGuid;

#pragma pack (push,1)

///
/// The PCH_SKYCAM_CIO2_CONFIG block describes SkyCam CIO2 device.
///
typedef struct {
  CONFIG_BLOCK_HEADER   Header;                   ///< Config Block Header
  /**
    NOTE: For SKL PCH, while CIO2 is enabled,
    RC will configure CIO2 controller as ACPI mode when PCH stepping < C0, and configure to PCI mode for C0 onwards.
  **/
  UINT32 DeviceEnable              :  2;          ///< 0: Disabled, <b>1: Enabled</b>

  UINT32 SkyCamPortATermOvrEnable  :  1;          ///< <b>0: Disable</b>, 1: Enable - Termination override on port A
  UINT32 SkyCamPortBTermOvrEnable  :  1;          ///< <b>0: Disable</b>, 1: Enable - Termination override on port B
  UINT32 SkyCamPortCTermOvrEnable  :  1;          ///< <b>0: Disable</b>, 1: Enable - Termination override on port C
  UINT32 SkyCamPortDTermOvrEnable  :  1;          ///< <b>0: Disable</b>, 1: Enable - Termination override on port D
  UINT32 RsvdBits                  : 26;

  //
  // CIO2 FLS registers configuration.
  //

  UINT32 PortATrimEnable     :  1;          ///< 0: Disable, <b>1: Enable</b> - Port A Clk Trim
  UINT32 PortBTrimEnable     :  1;          ///< 0: Disable, <b>1: Enable</b> - Port B Clk Trim
  UINT32 PortCTrimEnable     :  1;          ///< 0: Disable, <b>1: Enable</b> - Port C Clk Trim
  UINT32 PortDTrimEnable     :  1;          ///< 0: Disable, <b>1: Enable</b> - Port D Clk Trim
  UINT32 PortACtleEnable     :  1;          ///< 0: Disable, <b>1: Enable</b> - Port A Ctle
  UINT32 PortBCtleEnable     :  1;          ///< 0: Disable, <b>1: Enable</b> - Port B Ctle
  UINT32 PortCDCtleEnable    :  1;          ///< 0: Disable, <b>1: Enable</b> - Port C/D Ctle
  UINT32 RsvdBits0           : 25;

  UINT32 PortACtleCapValue   :  4;          /// Port A Ctle Cap Value. Default is <b>0xE</b>
  UINT32 PortBCtleCapValue   :  4;          /// Port B Ctle Cap Value. Default is <b>0xE</b>
  UINT32 PortCDCtleCapValue  :  4;          /// Port C/D Ctle Cap Value. Default is <b>0xE</b>
  UINT32 PortACtleResValue   :  5;          /// Port A Ctle Res Value. Default is <b>0xD</b>
  UINT32 PortBCtleResValue   :  5;          /// Port B Ctle Res Value. Default is <b>0xD</b>
  UINT32 PortCDCtleResValue  :  5;          /// Port C/D Ctle Res Value. Default is <b>0xD</b>
  UINT32 RsvdBits1           :  5;

  UINT32 PortAClkTrimValue   :  4;          /// Port A Clk Trim Value. Default is <b>0xA</b>
  UINT32 PortBClkTrimValue   :  4;          /// Port B Clk Trim Value. Default is <b>0xA</b>
  UINT32 PortCClkTrimValue   :  4;          /// Port C Clk Trim Value. Default is <b>0x9</b>
  UINT32 PortDClkTrimValue   :  4;          /// Port D Clk Trim Value. Default is <b>0xA</b>
  UINT32 PortADataTrimValue  : 16;          /// Port A Data Trim Value. Default is <b>0xBBBB</b>
  UINT32 PortBDataTrimValue  : 16;          /// Port B Data Trim Value. Default is <b>0xBBBB</b>
  UINT32 PortCDDataTrimValue : 16;          /// Port C/D Data Trim Value. Default is <b>0xCCCC</b>

} PCH_CIO2_CONFIG;

#pragma pack (pop)

#endif // _CIO2_CONFIG_H_
