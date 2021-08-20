/** @file
  This file contains define definitions specific to processor

 @copyright
  INTEL CONFIDENTIAL
  Copyright 1999 - 2019 Intel Corporation.

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
#ifndef _POWER_MGMT_DEFINITIONS_H_
#define _POWER_MGMT_DEFINITIONS_H_

#define CSTATE_SUPPORTED          0x1
#define ENHANCED_CSTATE_SUPPORTED 0x2
#define C6_C7_SHORT_LATENCY_SUPPORTED 0x01
#define C6_C7_LONG_LATENCY_SUPPORTED  0x02
#define C7s_SHORT_LATENCY_SUPPORTED   0x03
#define C7s_LONG_LATENCY_SUPPORTED    0x04
//
// Voltage offset definitions
//
#define OC_LIB_OFFSET_ADAPTIVE  0
#define OC_LIB_OFFSET_OVERRIDE  1
//
// Platform Power Management Flags Bit Definitions:
//   These defines are also used in CPU0CST.ASL to check platform configuration
//   and build C-state table accordingly.
//
#define PPM_EIST                BIT0   ///< Enhanced Intel Speed Step Technology.
#define PPM_C1                  BIT1   ///< C1 enabled, supported.
#define PPM_C1E                 BIT2   ///< C1E enabled.
#define PPM_C3                  BIT3   ///< C3 enabled, supported.
#define PPM_C6                  BIT4   ///< C6 enabled, supported.
#define PPM_C7                  BIT5   ///< C7 enabled, supported.
#define PPM_C7S                 BIT6   ///< C7S enabled, supported
#define PPM_TM                  BIT7   ///< Adaptive Thermal Monitor.
#define PPM_TURBO               BIT8   ///< Long duration turbo mode
#define PPM_CMP                 BIT9   ///< CMP.
#define PPM_TSTATES             BIT10  ///< CPU throttling states
#define PPM_MWAIT_EXT           BIT11  ///< MONITIOR/MWAIT Extensions supported.
#define PPM_EEPST               BIT12  ///< Energy efficient P-State Feature enabled
#define PPM_TSTATE_FINE_GRAINED BIT13  ///< Fine grained CPU Throttling states
#define PPM_CD                  BIT14  ///< Deep Cstate - C8/C9/C10
#define PPM_TIMED_MWAIT         BIT15  ///< Timed Mwait support
#define C6_LONG_LATENCY_ENABLE  BIT16  ///< 1=C6 Long and Short,0=C6 Short only
#define C7_LONG_LATENCY_ENABLE  BIT17  ///< 1=C7 Long and Short,0=C7 Short only
#define C7s_LONG_LATENCY_ENABLE BIT18  ///< 1=C7s Long and Short,0=C7s Short only
#define PPM_C8                  BIT19  ///< 1= C8 enabled/supported
#define PPM_C9                  BIT20  ///< 1= C9 enabled/supported
#define PPM_C10                 BIT21  ///< 1= C10 enabled/supported
#define PPM_HWP                 BIT22  ///< 1= HWP enabled/supported
#define PPM_HWP_LVT             BIT23  ///< 1= HWP LVT enabled/supported
#define PPM_OC_UNLOCKED         BIT24  ///< 1= Overclocking fully unlocked

#define PPM_C_STATES            0x7A    ///< PPM_C1 + PPM_C3 + PPM_C6 + PPM_C7 + PPM_C7S
#define C3_LATENCY              0x4E
#define C6_C7_SHORT_LATENCY     0x76
#define C6_C7_LONG_LATENCY      0x94
#define C8_LATENCY              0xFA
#define C9_LATENCY              0x14C
#define C10_LATENCY             0x3F2

//
// The following definitions are based on assumed location for the  ACPI
// Base Address.  Modify as necessary base on platform-specific requirements.
//
#define PCH_ACPI_PBLK 0x1810
#define PCH_ACPI_LV2  0x1814
#define PCH_ACPI_LV3  0x1815
#define PCH_ACPI_LV4  0x1816
#define PCH_ACPI_LV6  0x1818
#define PCH_ACPI_LV5  0x1817
#define PCH_ACPI_LV7  0x1819

//
// C-State Latency (us) and Power (mW) for C1
//
#define C1_LATENCY                        1
#define C1_POWER                          0x3E8
#define C3_POWER                          0x1F4
#define C6_POWER                          0x15E
#define C7_POWER                          0xC8
#define C8_POWER                          0xC8
#define C9_POWER                          0xC8
#define C10_POWER                         0xC8

#ifndef MINTREE_FLAG
#define MAX_POWER_LIMIT_1_TIME_IN_SECONDS 32767
#ifndef AUTO
#define AUTO                              0
#endif
#define END_OF_TABLE                      0xFF

#define CONFIG_TDP_DOWN                   1
#define CONFIG_TDP_UP                     2
#define CONFIG_TDP_DEACTIVATE             0xFF
//
// MMIO definitions
//
#define MMIO_DDR_RAPL_LIMIT     0x58e0
#define MMIO_TURBO_POWER_LIMIT  0x59A0

#define MAX_OVERCLOCKING_BINS   0x7

///
/// For Mobile and Halo, default PL1 time window value is 28 seconds
///
#define MB_POWER_LIMIT1_TIME_DEFAULT  28
///
/// For Desktop, default PL1 time window value is 8 second
///
#define DT_POWER_LIMIT1_TIME_DEFAULT  8

#define PROCESSOR_FLAVOR_MOBILE       0x04
#define PROCESSOR_FLAVOR_DESKTOP      0x00
#define PROCESSOR_FLAVOR_MASK         (BIT3 | BIT2)

//
// Power definitions (Based on EMTS V1.0 for standard voltage 2.4-2.6 GHz dual-core parts.)
//
#define FVID_MAX_POWER      35000
#define FVID_TURBO_POWER    35000
#define FVID_SUPERLFM_POWER 12000
//
// Power definitions for LFM and Turbo mode TBD.
//
#define FVID_MIN_POWER  15000

///
/// Limit the number of P-states for different generation OS.
///
#define TPSS_FVID_MAX_STATES                   40
#define LPSS_FVID_MAX_STATES                   16

#define READ_PL1_DUTY_CYCLE_CLAMP_ENABLE  0x00000015
#define WRITE_PL1_DUTY_CYCLE_CLAMP_ENABLE 0x00000016

//
//  VR mailbox commands
//
#define READ_VR_STRAP_CONFIG_CMD          0x80000018
#define READ_ACDC_LOADLINE_CMD            0x80000118
#define WRITE_ACDC_LOADLINE_CMD           0x80000218
#define WRITE_PSI_CUTOFF_CMD              0x80000318
#define WRITE_IMON_CONFIG_CMD             0x80000418
#define READ_VR_ICC_MAX_CMD               0x80000518
#define WRITE_VR_ICC_MAX_CMD              0x80000618
#define READ_VR_VOLTAGE_LIMIT_CMD         0x80000718
#define WRITE_VR_VOLTAGE_LIMIT_CMD        0x80000818
#define WRITE_PSYS_CONFIG_CMD             0x80000918
#define WRITE_PSYS_PMAX_CMD               0x80000B18
#define READ_VR_TDC_CONFIG_CMD            0x80000019
#define WRITE_VR_TDC_CONFIG_CMD           0x8000001A
#define WRITE_VOLTAGE_OPTIMIZATION_CMD    0x8000001F
#define READ_PLL_VOLTAGE_OFFSET_CMD       0x8000002C
#define WRITE_PLL_VOLTAGE_OFFSET_CMD      0x8000002D
#define WRITE_MPS_VR_IMPV8_CMD            0x80000E18
#define WRITE_PS4_EXIT_VR_CMD             0x80000034
#define WRITE_MPS_VR_DECAY_CMD            0x80000038
#define WRITE_ISL_VR_MBX_CMD              0x80000012
#define ISL_VR_IA_GT_CMD_REQUESTED        0x01
#define ISL_VR_IA_GT_CMD_DATA             0x00
#define ISL_VR_IA_GT_SA_CMD_REQUESTED     0x02
#define ISL_VR_IA_GT_SA_CMD_DATA          0x01
#define MPS_VR_CMD_REQUESTED              0x01
#define PS4_EXIT_VR_CMD_REQUESTED         0x02
#define MPS_VR_DECAY_CMD_REQUESTED        0x04

//
//  VR mailbox commands for Acoustic Noise Mitigation
//
#define WRITE_SVID_SET_VR_SLEW_RATE_CMD           0x80000C18
#define WRITE_SVID_SET_DISABLE_FAST_PKGC_RAMP_CMD 0x80000D18


#define VR_ADDRESS_MASK                   0xF
#define VR_ADDRESS_OFFSET                 16
#define VR_TDC_ADDRESS_OFFSET             8
#define DC_LOADLINE_OFFSET                16
#define AC_DC_LOADLINE_MAX                6249 ///< 62.49 mOhm max
#define AC_LOADLINE_MASK                  0xFFFF
#define DC_LOADLINE_MASK                  0xFFFF0000
#define PSI_THRESHOLD_MASK                0x3FF
#define PSI2_THRESHOLD_OFFSET             10
#define PSI3_THRESHOLD_OFFSET             20
#define PSI3_ENABLE_OFFSET                30
#define PSI4_ENABLE_OFFSET                31
#define VR_IMON_SLOPE_OFFSET              8
#define VR_IMON_OFFSET_HIGH_RES_OFFSET    18
#define VR_VOLTAGE_LIMIT_MASK             0xFFFF
#define PSYS_SLOPE_OFFSET                 8
#define VR_TDC_CURRENT_LIMIT_MASK         0x7FFF
#define VR_TDC_TIME_WINDOW_MASK           0x7F
#define VR_TDC_TIME_WINDOW_LOCATION_MASK  0xFE0000
#define VR_TDC_ENABLE_OFFSET              15
#define VR_TDC_TIME_WINDOW_OFFSET         17
#define VR_TDC_LOCK_OFFSET                31
#define VR_TDC_TIME_WINDOW_MAX            10

//
//  PID Tuning mailbox commands
//
#define WRITE_PID_RATL                    0x80000021
#define WRITE_PID_VR0_TDC                 0x81000021
#define WRITE_PID_VR1_TDC                 0x81010021
#define WRITE_PID_VR2_TDC                 0x81020021
#define WRITE_PID_VR3_TDC                 0x81030021
#define WRITE_PID_PSYS_PL1_MSR            0x82000021
#define WRITE_PID_PSYS_PL1_MMIO           0x82010021
#define WRITE_PID_PSYS_PL2_MSR            0x82020021
#define WRITE_PID_PSYS_PL2_MMIO           0x82030021
#define WRITE_PID_PKG_PL1_MSR             0x82040021
#define WRITE_PID_PKG_PL1_MMIO            0x82050021
#define WRITE_PID_PKG_PL2_MSR             0x82060021
#define WRITE_PID_PKG_PL2_MMIO            0x82070021
#define WRITE_PID_DDR_PL1_MSR             0x82080021
#define WRITE_PID_DDR_PL1_MMIO            0x82090021
#define WRITE_PID_DDR_PL2_MSR             0x820A0021
#define WRITE_PID_DDR_PL2_MMIO            0x820B0021
#endif  // MINTREE_FLAG

#define PID_DOMAIN_KP                     0
#define PID_DOMAIN_KI                     1
#define PID_DOMAIN_KD                     2
#define MAILBOX_PARAM_1_OFFSET            8

///
///  VR Domain Definitions
///
#define SKL_VR_DOMAIN_SA           0x0
#define SKL_VR_DOMAIN_IA           0x1
#define SKL_VR_DOMAIN_GTUS         0x2
#define SKL_VR_DOMAIN_GTS          0x3

///
///  AC/DC Loadline defaults
///

//
//  Skylake Y 2+2
//
#define IA_AC_LL_DEFAULT_SKL_Y_2_2    590
#define GTS_AC_LL_DEFAULT_SKL_Y_2_2   570
#define SA_AC_LL_DEFAULT_SKL_Y_2_2    1790

#define IA_DC_LL_DEFAULT_SKL_Y_2_2    470
#define GTS_DC_LL_DEFAULT_SKL_Y_2_2   420
#define SA_DC_LL_DEFAULT_SKL_Y_2_2    1400

#define PSYS_PMAX_DEFAULT_SKL_Y_2_2   280   // 35W

//
//  Skylake U 2+2
//
#define IA_AC_LL_DEFAULT_SKL_U_2_2    240
#define GTS_AC_LL_DEFAULT_SKL_U_2_2   310
#define SA_AC_LL_DEFAULT_SKL_U_2_2    1030

#define IA_DC_LL_DEFAULT_SKL_U_2_2    240
#define GTS_DC_LL_DEFAULT_SKL_U_2_2   310
#define SA_DC_LL_DEFAULT_SKL_U_2_2    1030

#define PSYS_PMAX_DEFAULT_SKL_U_2_2   544   //68W

//
//  Kabylake-R U 2+2/4+2
//
#define IA_AC_LL_DEFAULT_KBL_R_U_2_2    240
#define GTS_AC_LL_DEFAULT_KBL_R_U_2_2   310
#define SA_AC_LL_DEFAULT_KBL_R_U_2_2    1030

#define IA_DC_LL_DEFAULT_KBL_R_U_2_2    240
#define GTS_DC_LL_DEFAULT_KBL_R_U_2_2   310
#define SA_DC_LL_DEFAULT_KBL_R_U_2_2    1030

#define IA_TDC_LIMIT_DEFAULT_KBL_R_U_2_2  168 // 21A
#define GT_TDC_LIMIT_DEFAULT_KBL_R_U_2_2  144 // 18A

#define IA_TDC_LIMIT_DEFAULT_KBL_R_U_4_2  336 // 42A
#define GT_TDC_LIMIT_DEFAULT_KBL_R_U_4_2  144 // 18A

#define IA_ICC_MAX_DEFAULT_KBL_R_U_2_2  128 // 32A
#define GT_ICC_MAX_DEFAULT_KBL_R_U_2_2  124 // 31A
#define SA_ICC_MAX_DEFAULT_KBL_R_U_2_2  18  // 4.5A

#define IA_ICC_MAX_DEFAULT_KBL_R_U_4_2  256 // 64A
#define GT_ICC_MAX_DEFAULT_KBL_R_U_4_2  124 // 31A
#define SA_ICC_MAX_DEFAULT_KBL_R_U_4_2  24  // 6A

//
//  Skylake U 2+3e
//
#define IA_AC_LL_DEFAULT_SKL_U_2_3E   240
#define GTS_AC_LL_DEFAULT_SKL_U_2_3E  200
#define GTU_AC_LL_DEFAULT_SKL_U_2_3E  600
#define SA_AC_LL_DEFAULT_SKL_U_2_3E   1030

#define IA_DC_LL_DEFAULT_SKL_U_2_3E   240
#define GTS_DC_LL_DEFAULT_SKL_U_2_3E  200
#define GTU_DC_LL_DEFAULT_SKL_U_2_3E  600
#define SA_DC_LL_DEFAULT_SKL_U_2_3E   1030

#define PSYS_PMAX_DEFAULT_SKL_U_2_3E  896   // 112W


//
//  Skylake H 4+2
//
#define IA_AC_LL_DEFAULT_SKL_H_4_2    180
#define GTS_AC_LL_DEFAULT_SKL_H_4_2   270
#define SA_AC_LL_DEFAULT_SKL_H_4_2    1000

#define IA_DC_LL_DEFAULT_SKL_H_4_2    180
#define GTS_DC_LL_DEFAULT_SKL_H_4_2   270
#define SA_DC_LL_DEFAULT_SKL_H_4_2    1000

//
//  Skylake H 4+4e
//
#define IA_AC_LL_DEFAULT_SKL_H_4_4E   160
#define GTS_AC_LL_DEFAULT_SKL_H_4_4E  140
#define GTU_AC_LL_DEFAULT_SKL_H_4_4E  600
#define SA_AC_LL_DEFAULT_SKL_H_4_4E   600

#define IA_DC_LL_DEFAULT_SKL_H_4_4E   160
#define GTS_DC_LL_DEFAULT_SKL_H_4_4E  140
#define GTU_DC_LL_DEFAULT_SKL_H_4_4E  600
#define SA_DC_LL_DEFAULT_SKL_H_4_4E   600

//
//  Skylake-S 2+2/4+2
//
#define IA_AC_DC_LL_DEFAULT_SKL_S     210
#define GT_AC_DC_LL_DEFAULT_SKL_S     310
#define SA_AC_DC_LL_DEFAULT_SKL_S     0

//
//  CFL-S 62
//
#define IA_AC_DC_LL_DEFAULT_CFL_S_6_2    210
#define GT_AC_DC_LL_DEFAULT_CFL_S_6_2    310
#define SA_AC_DC_LL_DEFAULT_CFL_S_6_2    1000

#define SA_TDC_LIMIT_DEFAULT_CFL_S_6_2   80 // 10A
//
// 35 W part
//
#define IA_TDC_LIMIT_DEFAULT_CFL_S_6_2_TDP_35   592  // 74A
#define GT_TDC_LIMIT_DEFAULT_CFL_S_6_2_TDP_35   200  // 25A

#define IA_ICC_MAX_DEFAULT_CFL_S_6_2_TDP_35     416  // 104A
#define GT_ICC_MAX_DEFAULT_CFL_S_6_2_TDP_35     140  // 35A
#define SA_ICC_MAX_DEFAULT_CFL_S_6_2_TDP_35     44   // 11A

//
// 65 W part
//
#define IA_TDC_LIMIT_DEFAULT_CFL_S_6_2_TDP_65   728  // 91A
#define GT_TDC_LIMIT_DEFAULT_CFL_S_6_2_TDP_65   240  // 30A

#define IA_ICC_MAX_DEFAULT_CFL_S_6_2_TDP_65     532  // 133A
#define GT_ICC_MAX_DEFAULT_CFL_S_6_2_TDP_65     180  // 45A
#define SA_ICC_MAX_DEFAULT_CFL_S_6_2_TDP_65     44   // 11A

//
// 80 W part
//
#define IA_TDC_LIMIT_DEFAULT_CFL_S_6_2_TDP_80   712  // 89A
#define GT_TDC_LIMIT_DEFAULT_CFL_S_6_2_TDP_80   240  // 30A

#define IA_ICC_MAX_DEFAULT_CFL_S_6_2_TDP_80     532  // 133A
#define GT_ICC_MAX_DEFAULT_CFL_S_6_2_TDP_80     180  // 45A
#define SA_ICC_MAX_DEFAULT_CFL_S_6_2_TDP_80     44   // 11A

//
// 95 W part
//
#define IA_TDC_LIMIT_DEFAULT_CFL_S_6_2_TDP_95   800  // 100A
#define GT_TDC_LIMIT_DEFAULT_CFL_S_6_2_TDP_95   240  // 30A

#define IA_ICC_MAX_DEFAULT_CFL_S_6_2_TDP_95     552  // 138A
#define GT_ICC_MAX_DEFAULT_CFL_S_6_2_TDP_95     180  // 45A
#define SA_ICC_MAX_DEFAULT_CFL_S_6_2_TDP_95     44   // 11A


#define CFL_6_2_TDP_35_WATTS             3500
#define CFL_6_2_TDP_65_WATTS             6500
#define CFL_6_2_TDP_80_WATTS             8000
#define CFL_6_2_TDP_95_WATTS             9500

///
///  CPU TDP Wattage levels
///
#define CPU_TDP_4PT5_WATTS     450
#define CPU_TDP_5_WATTS        500
#define CPU_TDP_7_WATTS        700
#define CPU_TDP_15_WATTS       1500
#define CPU_TDP_28_WATTS       2800
#define CPU_TDP_35_WATTS       3500
#define CPU_TDP_45_WATTS       4500
#define CPU_TDP_51_WATTS       5100
#define CPU_TDP_54_WATTS       5400
#define CPU_TDP_58_WATTS       5800
#define CPU_TDP_60_WATTS       6000
#define CPU_TDP_62_WATTS       6200
#define CPU_TDP_65_WATTS       6500
#define CPU_TDP_91_WATTS       9100
#define CPU_TDP_95_WATTS       9500
#define CPU_TDP_99_WATTS       9900
#define CPU_TDP_120_WATTS      12000

///
/// CFL-S types
///
#define CFL_S_35_WATT_2_2       0x1
#define CFL_S_54_WATT_2_2       0x2
#define CFL_S_58_WATT_2_2       0x3
#define CFL_S_35_WATT_4_2       0x4
#define CFL_S_62_WATT_4_2       0x5
#define CFL_S_65_WATT_4_2       0x6
#define CFL_S_95_WATT_4_2       0x7
#define CFL_S_35_WATT_6_2       0x8
#define CFL_S_65_WATT_6_2       0x9
#define CFL_S_95_WATT_6_2       0xA
#define CFL_S_35_WATT_8_2       0xB
#define CFL_S_65_WATT_8_2       0xC
#define CFL_S_95_WATT_8_2       0xD
#define CFL_S_71_WATT_4_2       0xE   /// Workstation sku
#define CFL_S_80_WATT_6_2       0xF   /// Workstation sku
#define CFL_S_80_WATT_8_2       0x10  /// Workstation sku
#define KBL_Y_4PT5_WATT_2_2     0x11
#define AML_Y_5_WATT_2_2        0x12
#define AML_Y_7_WATT_2_2        0x13
#define KBL_S_60_WATT_2_2       0x14
#define KBL_S_35_WATT_4_2       0x15
#define KBL_S_65_WATT_4_2       0x16
#define KBL_S_95_WATT_4_2       0x17
#define KBL_S_99_WATT_4_2       0x18
#define AML_Y_7_WATT_4_2        0x19
#define KBL_S_35_WATT_2_2       0x1A
#define KBL_S_51_WATT_2_2       0x1B
#define KBL_S_54_WATT_2_2       0x1C
#define SKL_H_45_WATT_4_2       0x1D
#define AML_Y_7_WATT_2f_2        0x1E
///
/// Used to identify the CPU used for programming with the VR override table
///
typedef enum {
  EnumUnknownCpuId       = 0,
  EnumMinCpuId           = 1,

  ///
  /// CFL-S
  ///
  EnumCflSMinCpuId       = CFL_S_35_WATT_2_2,
  EnumCflS35Watt22CpuId  = CFL_S_35_WATT_2_2,
  EnumCflS54Watt22CpuId  = CFL_S_54_WATT_2_2,
  EnumCflS58Watt22CpuId  = CFL_S_58_WATT_2_2,
  EnumCflS35Watt42CpuId  = CFL_S_35_WATT_4_2,
  EnumCflS62Watt42CpuId  = CFL_S_62_WATT_4_2,
  EnumCflS65Watt42CpuId  = CFL_S_65_WATT_4_2,
  EnumCflS95Watt42CpuId  = CFL_S_95_WATT_4_2,
  EnumCflS35Watt62CpuId  = CFL_S_35_WATT_6_2,
  EnumCflS65Watt62CpuId  = CFL_S_65_WATT_6_2,
  EnumCflS95Watt62CpuId  = CFL_S_95_WATT_6_2,
  EnumCflS35Watt82CpuId  = CFL_S_35_WATT_8_2,
  EnumCflS65Watt82CpuId  = CFL_S_65_WATT_8_2,
  EnumCflS95Watt82CpuId  = CFL_S_95_WATT_8_2,
  EnumCflS71Watt42CpuId  = CFL_S_71_WATT_4_2, /// Workstation sku
  EnumCflS80Watt62CpuId  = CFL_S_80_WATT_6_2, /// Workstation sku
  EnumCflS80Watt82CpuId  = CFL_S_80_WATT_8_2, /// Workstation sku
  EnumCflSMaxCpuId       = CFL_S_80_WATT_8_2, /// Same as EnumCflS80Watt82CpuId

  ///
  /// KBL-Y
  ///
  EnumKblY4pt5Watt22CpuId  = KBL_Y_4PT5_WATT_2_2,

  ///
  /// AML-Y
  ///
  EnumAmlY5Watt22CpuId    = AML_Y_5_WATT_2_2,
  EnumAmlY7Watt22CpuId    = AML_Y_7_WATT_2_2,
  EnumAmlY7Watt2f2CpuId   = AML_Y_7_WATT_2f_2,
  EnumAmlY7Watt42CpuId    = AML_Y_7_WATT_4_2,

  ///
  /// KBL-S
  ///
  EnumKblS60Watt22Cpuid   = KBL_S_60_WATT_2_2,
  EnumKblS35Watt42Cpuid   = KBL_S_35_WATT_4_2,
  EnumKblS65Watt42Cpuid   = KBL_S_65_WATT_4_2,
  EnumKblS95Watt42Cpuid   = KBL_S_95_WATT_4_2,
  EnumKblS99Watt42Cpuid   = KBL_S_99_WATT_4_2,
  EnumKblS35Watt22Cpuid   = KBL_S_35_WATT_2_2,
  EnumKblS51Watt22Cpuid   = KBL_S_51_WATT_2_2,
  EnumKblS54Watt22Cpuid   = KBL_S_54_WATT_2_2,

  ///
  /// SKL-H
  ///
  EnumSklH45Watt42Cpuid   = SKL_H_45_WATT_4_2
} CPU_OVERRIDE_IDENTIFIER;

///
/// VR Override table structure
///
typedef struct {
  CPU_OVERRIDE_IDENTIFIER  CpuIdentifier;
  UINT16 IaIccMax;
  UINT16 GtIccMax;
  UINT16 SaIccMax;
  UINT16 IaTdclimit;
  UINT16 GtTdclimit;
  UINT16 SaTdclimit;
  UINT16 IaAcLoadLine;
  UINT16 IaDcLoadLine;
  UINT16 GtAcLoadLine;
  UINT16 GtDcLoadLine;
  UINT16 SaAcLoadLine;
  UINT16 SaDcLoadLine;
  UINT16 VrVoltageLimit;
} CPU_VR_OVERRIDE_TABLE;


//
// KblGBegin
//
#define IA_TDC_LIMIT_DEFAULT_KBL_G  400 // 50A
#define GT_TDC_LIMIT_DEFAULT_KBL_G  200 // 25A
#define SA_TDC_LIMIT_DEFAULT_KBL_G  80  // 10A

#define IA_ICC_MAX_DEFAULT_KBL_G    272 // 68A
#define GT_ICC_MAX_DEFAULT_KBL_G    220 // 55A
#define SA_ICC_MAX_DEFAULT_KBL_G    44  // 11A

#define IA_AC_LL_DEFAULT_KBL_G      180  // IA - 1.8mohm
#define GT_AC_LL_DEFAULT_KBL_G      270  // GT - 2.7 mOhom
#define SA_AC_LL_DEFAULT_KBL_G      1000 // SA - 10 mOhm

#define IA_DC_LL_DEFAULT_KBL_G      180
#define GT_DC_LL_DEFAULT_KBL_G      270
#define SA_DC_LL_DEFAULT_KBL_G      1000
//
// KblGEnd
//

#ifndef MINTREE_FLAG

///
/// HDC Definitions
///
#define N_HDC_SUPPORT                 0
#define B_HDC_SUPPORT                 BIT0
#endif  // MINTREE_FLAG
#endif
