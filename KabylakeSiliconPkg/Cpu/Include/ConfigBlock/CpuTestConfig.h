/** @file
  CPU Test Config Block.

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
#ifndef _CPU_TEST_CONFIG_H_
#define _CPU_TEST_CONFIG_H_

#define CPU_TEST_CONFIG_REVISION 2

extern EFI_GUID gCpuTestConfigGuid;

#pragma pack (push,1)

/**
  CPU Test Configuration Structure.

  <b>Revision 1</b>:
  - Initial version.

  <b>Revision 2</b>:
  - Deprecated and moved Hyperthreading to CPU_CONFIG_LIB_PREMEM_CONFIG
  - Deprecated and moved CpuRatioOverride to CPU_CONFIG_LIB_PREMEM_CONFIG
  - Deprecated and moved CpuRatio to CPU_CONFIG_LIB_PREMEM_CONFIG
  - Deprecated and moved ActiveCoreCount to CPU_CONFIG_LIB_PREMEM_CONFIG
  - Deprecated and moved JtagC10PowerGateDisable to CPU_CONFIG_LIB_PREMEM_CONFIG

**/
typedef struct {
  CONFIG_BLOCK_HEADER   Header;                   ///< Config Block Header
  UINT32 HyperThreading                  : 1;     ///< Enable or Disable Hyper Threading; 0: Disable; <b>1: Enable</b>.
  /**
   @deprecated since revision 2. Moved to CPU_CONFIG_LIB_PREMEM_CONFIG
   Enable or disable override of default max non-turbo ratio. If enabled, BIOS will take the value specified in
     CpuRatio policy and updates the max non-turbo ratio. See policy CpuRatio for more details.
   -    0: Disable
   - <b>1: Enable</b>
  **/
  UINT32 CpuRatioOverride                : 1;     ///< @deprecated since revision 2. Moved to CPU_CONFIG_LIB_PREMEM_CONFIG
  UINT32 MlcStreamerPrefetcher           : 1;     ///< Enable or Disable MLC Streamer Prefetcher; 0: Disable; <b>1: Enable</b>.
  UINT32 MlcSpatialPrefetcher            : 1;     ///< Enable or Disable MLC Spatial Prefetcher; 0: Disable; <b>1: Enable</b>.
  UINT32 MonitorMwaitEnable              : 1;     ///< Enable or Disable Monitor /MWAIT instructions; 0: Disable; <b>1: Enable</b>.
  UINT32 MachineCheckEnable              : 1;     ///< Enable or Disable initialization of machine check registers; 0: Disable; <b>1: Enable</b>.
  UINT32 DebugInterfaceEnable            : 1;     ///< Enable or Disable processor debug features; <b>0: Disable</b>; 1: Enable.
  UINT32 DebugInterfaceLockEnable        : 1;     ///< Lock or Unlock debug interface features; 0: Disable; <b>1: Enable</b>.
  /**
    AP Idle Manner of waiting - Manner of which APs are waiting to be tasked by MP Services
    -    1: HALT loop
    - <b>2: MWAIT loop</b>
    -    3: Run loop
  **/
  UINT32 ApIdleManner                    : 2;
  /**
    Settings for AP Handoff to OS - Type of loop AP is placed in before handing control to OS.
    -    1: HALT loop
    - <b>2: MWAIT loop</b>
  **/
  UINT32 ApHandoffManner                 : 2;
  /**
    @deprecated since revision 2. Moved to CPU_CONFIG_LIB_PREMEM_CONFIG
    Number of processor cores to enable.
    - <b> 0: All cores</b>
    -     1: 1 core
    -     2: 2 cores
    -     3: 3 cores
  **/
  UINT32 ActiveCoreCount                 : 3;     ///< @deprecated since revision 2. Moved to CPU_CONFIG_LIB_PREMEM_CONFIG
  UINT32 JtagC10PowerGateDisable         : 1;     ///< Power JTAG in C10 and deeper power states; <b>0: Disable</b>; 1: Enable.
  UINT32 ProcTraceOutputScheme           : 1;     ///< Control on Processor Trace output scheme; <b>0: Single Range Output</b>; 1: ToPA Output.
  UINT32 ProcTraceEnable                 : 1;     ///< Enable or Disable Processor Trace feature; <b>0: Disable</b>; 1: Enable.
  /**
     Memory region allocation for Processor Trace.
     Total memory required is equal to the requested value * 2 (for memory alignment) * number of active processor threads.
     Based on MEMORY_CONFIG_NO_CRC.PlatformMemorySize default, up to 2MB policy setting with up to 8 active threads is supported (32MB memory total).
     For larger size requests, MEMORY_CONFIG_NO_CRC.PlatformMemorySize needs to be increased.
     -      0: 4K
     -      1: 8K
     -      2: 16K
     -      3: 32K
     -      4: 64K
     -      5: 128K
     -      6: 256K
     -      7: 512K
     -      8: 1M
     -      9: 2M
     -     10: 4M
     -     11: 8M
     -     12: 16M
     -     13: 32M
     -     14: 64M
     -     15: 128M
     - <b>255: Disable</b>
  **/
  UINT32 ProcTraceMemSize                : 8;
  UINT32 ThreeStrikeCounterDisable       : 1;     ///< Disable Three strike counter; <b>0: FALSE</b>; 1: TRUE.
  /**
    This policy should be used to enable or disable Voltage Optimization feature.
    Recommended defaults:
     Enable  - For Mobile SKUs(U/Y)
     Disable - Rest of all SKUs other than Mobile.
  **/
  UINT32 VoltageOptimization             : 1;
  UINT32 RsvdBits                        : 4;     ///< Reserved for future use
  /**
    @deprecated since revision 2. Moved to CPU_CONFIG_LIB_PREMEM_CONFIG
    CpuRatio - When CpuRatioOverride is enabled, max non-turbo ratio (Flexible Ratio Boot) is set to CpuRatio.
  **/
  UINT8  CpuRatio;
  UINT8  Rsvd[3];                                 ///< Reserved for future use
} CPU_TEST_CONFIG;

#pragma pack (pop)

#endif // _CPU_TEST_CONFIG_H_
