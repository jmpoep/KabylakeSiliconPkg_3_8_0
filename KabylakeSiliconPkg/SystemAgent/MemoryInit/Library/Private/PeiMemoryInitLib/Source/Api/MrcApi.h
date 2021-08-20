/** @file
  Mrc definition of supported features.

 @copyright
  INTEL CONFIDENTIAL
  Copyright 1999 - 2018 Intel Corporation.

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
#ifndef _MrcApi_h_
#define _MrcApi_h_


#include "MrcTypes.h"

#define HPET_MIN          (1)  ///< Minimum is one HPET tick = 41.666667ns on SPT PCH
#define HPET_1US          (24)
#define HPET_1MS          (0x5DBF)

#define START_TEST_DELAY  (2 * HPET_MIN)
#define IO_RESET_DELAY    (2 * HPET_MIN)

#define COMP_INT          0x0A    ///< For 10ms
#define MAX_POSSIBLE_VREF 63      ///< Maximum possible margin for Vref
#define MAX_POSSIBLE_RX_VREF   31 ///< Maximum possible Rx margin for Vref
#define MAX_POSSIBLE_TIME 31      ///< Maximum possible margin for time
#define TXEQFULLDRV     (0x30)    ///< SKL - 15 Emphasize legs (not trained)
#define DIMMRON         (ODIC_RZQ_6)

///
/// Compile time configuration parameters - START.
/// The user must set these values for the system.
///
#define DIMMSIZEMIN            1024        ///< The minimum size of DIMM, in MBytes.
#define DIMMSIZEMAX            (32 * 1024) ///< The maximum size of DIMM, in MBytes.
#include "MrcInterface.h"

#define FREQMIN                f1067       ///< The minimum valid frequency.

#if (SUPPORT_DDR4 == SUPPORT)
#define MAX_POSSIBLE_DDR4_WRITE_VREF 36    ///< Maximum possible margin for DDR4 Write Vref
#define MIN_DDR4_WRITE_VREF_RANGE1   -13   ///< Minimum possible DDR4 Write Vref for Range1
#define MAX_DDR4_WRITE_VREF_RANGE2   14    ///< Maximum possible DDR4 Write Vref for Range2
#define DDR4_VREF_STEP_SIZE          7800  // in micro volt
#define DDR4_VREF_MIDDLE_RANGE       820   // DDR4 middle range in milli volt
#endif //SUPPORT_DDR4

#define SUPPORT_SPD_CRC        UNSUPPORT   ///< SUPPORT means that the CRC of the DIMMs SPD must match.
#define SUPPORT_FORCE          UNSUPPORT   ///< SUPPORT means to force tAA, tRCD, tRP to the same value.
#define SUPPORT_ALLDIMMS       UNSUPPORT   ///< SUPPORT means all timings across all DIMMs in the system.
                                           ///< UNSUPPORT means all timings across each memory channel's DIMMs.
#define SUPPORT_ECC            SUPPORT     ///< SUPPORT means ECC is suppported, else UNSUPPORT.
#define SUPPORT_UDIMM          SUPPORT     ///< SUPPORT means that unbuffered DIMMs are supported, else UNSUPPORT.
#define SUPPORT_SODIMM         SUPPORT     ///< SUPPORT means that SO-DIMMs are supported, else UNSUPPORT.
#define SUPPORT_RDIMM          UNSUPPORT   ///< SUPPORT means that registered DIMMs are supported, else UNSUPPORT.
#define SUPPORT_PRIWIDTH_8     UNSUPPORT   ///< SUPPORT means that SDRAM primary bus width of 8 is supported by the system.
#define SUPPORT_PRIWIDTH_16    UNSUPPORT   ///< SUPPORT means that SDRAM primary bus width of 16 is supported by the system.
#define SUPPORT_PRIWIDTH_32    UNSUPPORT   ///< SUPPORT means that SDRAM primary bus width of 32 is supported by the system.
#define SUPPORT_PRIWIDTH_64    SUPPORT     ///< SUPPORT means that SDRAM primary bus width of 64 is supported by the system.
#define SUPPORT_DEVWIDTH_4     UNSUPPORT   ///< SUPPORT means that SDRAM device width of 4 is supported by the system.
#define SUPPORT_DEVWIDTH_8     SUPPORT     ///< SUPPORT means that SDRAM device width of 8 is supported by the system.
#define SUPPORT_DEVWIDTH_16    SUPPORT     ///< SUPPORT means that SDRAM device width of 16 is supported by the system.
#define SUPPORT_DEVWIDTH_32    SUPPORT     ///< SUPPORT means that SDRAM device width of 32 is supported by the system.
#define SUPPORT_COLUMN_9       UNSUPPORT   ///< SUPPORT means that 9 bit size is supported by the system.

#define ULT_SUPPORT_COLUMN_10  SUPPORT     ///< SUPPORT means that 10 bit size is supported by the system.
#define ULT_SUPPORT_COLUMN_11  SUPPORT     ///< SUPPORT means that 11 bit size is supported by the system.
#define ULT_SUPPORT_COLUMN_12  SUPPORT     ///< SUPPORT means that 12 bit size is supported by the system.
#define TRAD_SUPPORT_COLUMN_10 SUPPORT     ///< SUPPORT means that 10 bit size is supported by the system.
#define TRAD_SUPPORT_COLUMN_11 UNSUPPORT   ///< SUPPORT means that 11 bit size is supported by the system.
#define TRAD_SUPPORT_COLUMN_12 UNSUPPORT   ///< SUPPORT means that 12 bit size is supported by the system.
#define BDW_SUPPORT_COLUMN_10  SUPPORT     ///< SUPPORT means that 10 bit size is supported by the system.
#define BDW_SUPPORT_COLUMN_11  SUPPORT     ///< SUPPORT means that 11 bit size is supported by the system.
#define BDW_SUPPORT_COLUMN_12  UNSUPPORT   ///< SUPPORT means that 12 bit size is supported by the system.

#define SUPPORT_ROW_12         SUPPORT     ///< SUPPORT means that 12 bit size is supported by the system.
#define SUPPORT_ROW_13         SUPPORT     ///< SUPPORT means that 13 bit size is supported by the system.
#define SUPPORT_ROW_14         SUPPORT     ///< SUPPORT means that 14 bit size is supported by the system.
#define SUPPORT_ROW_15         SUPPORT     ///< SUPPORT means that 15 bit size is supported by the system.
#define SUPPORT_ROW_16         SUPPORT     ///< SUPPORT means that 16 bit size is supported by the system.
#if (SUPPORT_DDR4 == SUPPORT) || (SUPPORT_LPDDR == SUPPORT)
#define SUPPORT_ROW_17         SUPPORT     ///< SUPPORT means that 17 bit size is supported by the system.
#define SUPPORT_ROW_18         UNSUPPORT   ///< SUPPORT means that 18 bit size is supported by the system.

#define SUPPORT_BANK_4         SUPPORT     ///< SUPPORT means that 4 banks is supported by the system.
#endif // SUPPORT_DDR4 || SUPPORT_LPDDR

#define SUPPORT_BANK_8         SUPPORT     ///< SUPPORT means that 8 banks is supported by the system.
#define SUPPORT_BANK_16        UNSUPPORT   ///< SUPPORT means that 16 banks is supported by the system.
#define SUPPORT_BANK_32        UNSUPPORT   ///< SUPPORT means that 32 banks is supported by the system.
#define SUPPORT_BANK_64        UNSUPPORT   ///< SUPPORT means that 64 banks is supported by the system.

#define TAAMINPOSSIBLE         4           ///< tAAmin possible range, in number of tCK cycles.
#define TAAMAXPOSSIBLE         24
#define TWRMINPOSSIBLE         5           ///< tWRmin possible range, in number of tCK cycles.
#define TWRMAXPOSSIBLE         16          ///< tWRmin values of 9, 11, 13 ,15 are not valid for DDR3.
#define TRCDMINPOSSIBLE        4           ///< tRCDmin possible range, in number of tCK cycles.
#define TRCDMAXPOSSIBLE        20
#define TRRDMINPOSSIBLE        4           ///< tRRDmin possible range, in number of tCK cycles.
#define TRRDSMINPOSSIBLE       4           ///< tRRD_Smin possible range, in number of tCK cycles.
#define TRRDSMAXPOSSIBLE       10
#define TRRDLMINPOSSIBLE       4           ///< tRRD_Lmin possible range, in number of tCK cycles.
#define TRRDLMAXPOSSIBLE       15
#define TRPMINPOSSIBLE         4           ///< tRPmin possible range, in number of tCK cycles.
#define TRPABMINPOSSIBLE       4           ///< tRPabmin possible range, in number of tCK cycles.
#define TRASMINPOSSIBLE        10          ///< tRASmin possible range, in number of tCK cycles.
#define TRASMAXPOSSIBLE        40
#define TRCMINPOSSIBLE         1           ///< tRCmin possible range, in number of tCK cycles.
#define TRCMAXPOSSIBLE         4095
#define TRFCMINPOSSIBLE        1           ///< tRFCmin possible range, in number of tCK cycles.
#define TRFCMAXPOSSIBLE        1023
#define TWTRMINPOSSIBLE        4           ///< tWTRmin possible range, in number of tCK cycles.
#define TWTRMAXPOSSIBLE        10
#define TWTRSMINPOSSIBLE       2           ///< tWTR_S possible range, in number of tCK cycles.
#define TWTRSMAXPOSSIBLE       4
#define TWTRLMINPOSSIBLE       4           ///< tWTR_L possible range, in number of tCK cycles.
#define TWTRLMAXPOSSIBLE       11
#define TRTPMINPOSSIBLE        4           ///< tRTPmin possible range, in number of tCK cycles.
#define TRTPMAXPOSSIBLE        15
#define TFAWMINPOSSIBLE        10          ///< tFAWmin possible range, in number of tCK cycles.
#define TFAWMAXPOSSIBLE        54
#define TCWLMINPOSSIBLE        5           ///< tCWLmin possible range, in number of tCK cycles.
#define TCWLMAXPOSSIBLE        12
#define TREFIMINPOSSIBLE       1           ///< tREFImin possible range, in number of tCK cycles.
#define TREFIMAXPOSSIBLE       65535
#define NMODEMINPOSSIBLE       1           ///< Command rate mode min possible range, in number of tCK cycles.
#define NMODEMAXPOSSIBLE       3

#define ULT_VDDMINPOSSIBLE     1200        ///< Vdd possible range, in milliVolts.
#define ULT_VDDMAXPOSSIBLE     1350
#define TRAD_VDDMINPOSSIBLE    1350        ///< Vdd possible range, in milliVolts.
#define TRAD_VDDMAXPOSSIBLE    1500

#if (SUPPORT_DDR4 == SUPPORT)
#define DDR4_TRTPMINPOSSIBLE   5           ///< tRTPmin possible range, in number of tCK cycles.
#define DDR4_TRTPMAXPOSSIBLE   12          ///< tRTPmin value of 11 is not valid for DDR4.
#define DDR4_TWRMINPOSSIBLE    10          ///< tWRmin possible range, in number of tCK cycles.
#define DDR4_TWRMAXPOSSIBLE    24          ///< tWRmin values of odd numbers and 22 not valid for DDR4.
#define DDR4_TCWLMINPOSSIBLE   9           ///< tCWLmin possible range, in number of tCK cycles.
#define DDR4_TCWLMAXPOSSIBLE   18
#endif // SUPPORT_DDR4
#if (JEDEC_SUPPORT_LPDDR == SUPPORT)
#define LPDDR3_TRTPMINPOSSIBLE  4           ///< tRTPmin possible range, in number of tCK cycles.
#define LPDDR3_TCWLMINPOSSIBLE  3           ///< tCWLmin possible range, in number of tCK cycles.
#define LPDDR3_TCWLMAXPOSSIBLE  13
#endif // JEDEC_SUPPORT_LPDDR
#define HOST_BRIDGE_BUS        0           ///< The host bridge bus number.
#define HOST_BRIDGE_DEVICE     0           ///< The host bridge device number.
#define HOST_BRIDGE_FUNCTION   0           ///< The host bridge function number.
#define HOST_BRIDGE_DEVID      0           ///< The host bridge device id offset.
#define HOST_BRIDGE_REVID      8           ///< The host bridge revision id offset.

#define MEMORY_RATIO_MIN       3           ///< The minimum DDR ratio value that the hardware supports.
#define MEMORY_RATIO_MAX       15          ///< The maximum DDR ratio value that the hardware supports.
#define MEMORY_EXTENDED_RATIO_MAX    31    ///< The extended maximum DDR ratio value that the hardware supports.

///
/// Compile time configuration parameters - END.
///
#define SUPPORT_COLUMN_10        (ULT_SUPPORT_COLUMN_10 || TRAD_SUPPORT_COLUMN_10 || BDW_SUPPORT_COLUMN_10)
#define SUPPORT_COLUMN_11        (ULT_SUPPORT_COLUMN_11 || TRAD_SUPPORT_COLUMN_11 || BDW_SUPPORT_COLUMN_11)
#define SUPPORT_COLUMN_12        (ULT_SUPPORT_COLUMN_12 || TRAD_SUPPORT_COLUMN_12 || BDW_SUPPORT_COLUMN_12)
#define VDDMINPOSSIBLE           MIN (ULT_VDDMINPOSSIBLE, TRAD_VDDMINPOSSIBLE)
#define VDDMAXPOSSIBLE           MAX (ULT_VDDMAXPOSSIBLE, TRAD_VDDMAXPOSSIBLE)
#define EYE_MARGIN_SUPPORT       0       ///< Include code to plot 2D eye diagrams
#define DATA_EYE_MARGIN_SUPPORT  0       ///<  plot 2D data eye diagrams in RMT
#define CMD_EYE_MARGIN_SUPPORT   0       ///<  plot 2D cmd eye diagrams in RMT

///
/// Exit mode
///
typedef enum {
  emSlow      = 0,
  emFast      = 1,
  emAuto      = 0xFF,
} MrcExitMode;

///
/// System definitions
///
#define MRC_SYSTEM_BCLK (100)

///
/// Register default values
///
#define MRC_DIMM_RANK_INTERLEAVE      (1)
#define MRC_ENHANCED_INTERLEAVE_MODE  (1)
#define MRC_HORI_MODE                 (1)

///
///  CPU Mailbox Related Definitions
///
#define MAILBOX_TYPE_PCODE              0x00000001
#define MAILBOX_TYPE_OC                 0x00000002
#define PCODE_MAILBOX_INTERFACE_OFFSET  PCU_CR_BIOS_MAILBOX_INTERFACE_PCU_REG
#define PCODE_MAILBOX_DATA_OFFSET       PCU_CR_BIOS_MAILBOX_DATA_PCU_REG
#define OC_MAILBOX_MSR                  0x00000150

//
// CPU Mailbox Commands
//
#define CPU_MAILBOX_CMD_READ_DLLBWEN      0x00000029
#define CPU_MAILBOX_CMD_WRITE_DLLBWEN     0x0000002A
#define CPU_MAILBOX_CMD_SAGV_SET_POLICY   0x00000122
#define SET_EPG_BIOS_POWER_OVERHEAD_0_CMD 0x00000020
#define SET_EPG_BIOS_POWER_OVERHEAD_1_CMD 0x00000120

//
// CPU Mailbox Completion Codes
//
#define PCODE_MAILBOX_CC_SUCCESS            0
#define PCODE_MAILBOX_DLLBWEN_ILLEGAL       1
#define PCODE_MAILBOX_DLLBWEN_DATA_INVALID  4
#define PCODE_MAILBOX_DLLBWEN_LOCKED        6

#pragma pack (push, 1)
typedef union {
  struct {
    UINT32 DllBwEn1067  :  3;  // Bits 2:0
    UINT32 DllBwEn1333  :  3;  // Bits 5:3
    UINT32 DllBwEn1600  :  3;  // Bits 8:6
    UINT32 DllBwEn1867  :  3;  // Bits 11:9
    UINT32              :  20; // Bits 31:12
  } Bits;
  UINT32 Data;
} MrcMailboxDllBwEn;
#pragma pack (pop)

#endif
