/** @file
  PCIE DXE policy definitions

 @copyright
  INTEL CONFIDENTIAL
  Copyright 2015 - 2018 Intel Corporation.

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
#ifndef _PCIE_DXE_CONFIG_H_
#define _PCIE_DXE_CONFIG_H_

#pragma pack(push, 1)

#define PCIE_DXE_CONFIG_REVISION 2

///
/// Device List for special ASPM override
///
typedef struct {
  UINT16  VendorId;         ///< Offset 0 PCI Configuration space offset 0
  UINT16  DeviceId;         ///< Offset 2 PCI Configuration space offset 2
  UINT8   RevId;            ///< Offset 4 PCI Configuration space offset 8; 0xFF means all steppings
  UINT8   RootApmcMask;     ///< Offset 5 Root ASPM override bit mask <b>0=No override</b>
  UINT8   EndpointApmcMask; ///< Offset 6 Endpoint ASPM override bit mask <b>0=No override</b>
  UINT8   Rsvd;             ///< Offset 7 Reserved
} PCIE_ASPM_OVERRIDE_LIST;

typedef struct {
  UINT16  VendorId; ///< Offset 0 PCI Config space offset 0
  UINT16  DeviceId; ///< Offset 2 PCI Config space offset 2
/**
  Offset 4:
  SnoopLatency bit definition
  Note: All Reserved bits must be set to 0

  BIT[15]     - When set to 1b, indicates that the values in bits 9:0 are valid
                When clear values in bits 9:0 will be ignored
  BIT[14]     - Should be set to 0b
  BIT[13]     - Reserved
  BITS[12:10] - Value in bits 9:0 will be multiplied with the scale in these bits
                000b - 1 ns
                001b - 32 ns
                010b - 1024 ns
                011b - 32,768 ns
                100b - 1,048,576 ns
                101b - 33,554,432 ns
                110b - Reserved
                111b - Reserved
  BITS[9:0]   - Snoop Latency Value. The value in these bits will be multiplied with
                the scale in bits 12:10
**/
  UINT16  SnoopLatency;
/**
  Offset 6:
  NonSnoopLatency bit definition
  Note: All Reserved bits must be set to 0

  BIT[15]     - When set to 1b, indicates that the values in bits 9:0 are valid
                When clear values in bits 9:0 will be ignored
  BIT[14]     - Should be set to 0b
  BIT[13]     - Reserved
  BITS[12:10] - Value in bits 9:0 will be multiplied with the scale in these bits
                000b - 1 ns
                001b - 32 ns
                010b - 1024 ns
                011b - 32,768 ns
                100b - 1,048,576 ns
                101b - 33,554,432 ns
                110b - Reserved
                111b - Reserved
  BITS[9:0]   - Non Snoop Latency Value. The value in these bits will be multiplied with
                the scale in bits 12:10
**/
  UINT16  NonSnoopLatency;
  UINT8   RevId;    ///<   Offset 8 PCI Config space offset 8; 0xFF means all steppings
  UINT8   Rsvd0[3]; ///<   Offset 9
} PCIE_LTR_DEV_INFO;

///
/// PCIE Power Optimizer config
///
typedef struct {
  UINT16  LtrMaxSnoopLatency;   ///< Offset 0 LTR Maximum Snoop Latency: <b>0x0846=70us</b>
  UINT16  LtrMaxNoSnoopLatency; ///< Offset 2 LTR Maximum Non-Snoop Latency: <b>0x0846=70us</b>
  UINT8   ObffEnable;           ///< Offset 4 LTR enable/disable: 0=Disable, <b>1=Enable</b>
  UINT8   LtrEnable;            ///< Offset 5 LTR enable/disable: 0=Disable, <b>1=Enable</b>
  UINT8   Rsvd0[2];             ///< Offset 6 Reserved
} SA_PCIE_PWR_OPT;


/**
  The PCI Express Configuration info includes PCI Resources Range Base and Limits and the control
  for PEG ASPM.
  The data elements should be initialized by a Platform Module.\n
  @note <b>Optional.</b> These policies will be ignored if there is no PEG port present on board.
  <b>Revision 1</b>:
  - Initial version.  
  <b>Revision 2</b>:
  - Adding XConnectEnable to the structure.
**/
typedef struct {
  CONFIG_BLOCK_HEADER      Header;                         ///< Offset 0-27 Config Block Header
/**
  Offset 28: This field is used to describe the ASPM control for PEG Ports\n
  0=ASPM Disabled, 1=ASPM L0s Enabled, 2=ASPM L1 Enabled, 3=ASPM L0sL1 Enabled, <b>4=ASPM AUTO</b>
**/
  UINT8                    PegAspm[SA_PEG_MAX_FUN];
/**
  Offset 31: This field is used to describe the PEG L0s advanced control
  0=ASPM L0s disabled, 1=ASPM L0s enabled on RP, 2=ASPM L0s enabled on EP, <b>3=ASPM L0s enabled on both RP and EP</b>
**/
  UINT8                    PegAspmL0s[SA_PEG_MAX_FUN];
/**
  Offset 34: PCIe Hot Plug Enable/Disable. It has 2 policies.
   - <b>Disabled (0x0)</b>     : No hotplug.
   - Enabled (0x1)      : Bios assist hotplug.
**/
  UINT8                    PegRootPortHPE[SA_PEG_MAX_FUN];
  UINT8                    Rsvd0[3];                       ///< Offset 37
  UINT32                   C7Allowed    :1;                ///< Offset 40 Enable/Disable C7 allowed for PEG Ports [Run-time control]. <b>0=Disable</b>, 1=Enable
  UINT32                   PegRtd3      :1;                ///< Enable/Disable RTD3 Support for PEG Port. 0=Disable and 1=Enable (default)
  UINT32                   RsvdBits0    :30;
/**
  Offset 44: This field is used as a pointer to the ASPM device override table, default points to an\n
  existing table mPcieAspmDevsOverride\n
  Refer to DxeSaPolicyLib.c for the usage.
  Note:  This exclusion list helps avoid potential system hangs.
**/
  PCIE_ASPM_OVERRIDE_LIST  *PcieAspmDevsOverride;
/**
  Offset 52: This field is used as a pointer to the LTR device override table, default points to an existing
  table mPcieLtrDevsOverride.\n
  Refer to DxeSaPolicyLib.c for the usage.
**/
  PCIE_LTR_DEV_INFO        *PcieLtrDevsOverride;
  SA_PCIE_PWR_OPT          PegPwrOpt[SA_PEG_MAX_FUN];     ///< Offset 64: This field is used to describe the PCIe LTR/OBFF relevant settings

  UINT8                    XConnectEnable;
  UINT8                    Rsvd1[3];  ///< Offset 68
} PCIE_DXE_CONFIG;
#pragma pack(pop)

#endif // _PCIE_DXE_CONFIG_H_
