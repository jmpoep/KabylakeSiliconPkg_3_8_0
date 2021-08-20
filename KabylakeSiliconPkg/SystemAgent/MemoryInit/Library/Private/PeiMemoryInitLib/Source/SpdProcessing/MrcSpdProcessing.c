/** @file
  By passing in a SPD data structure and platform support values, an output
  structure is populated with DIMM configuration information.

 @copyright
  INTEL CONFIDENTIAL
  Copyright 1999 - 2017 Intel Corporation.

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
#include "MrcSpdProcessing.h"
#include "MrcCommonTypes.h"

#ifdef MRC_DEBUG_PRINT
GLOBAL_REMOVE_IF_UNREFERENCED const char        UnknownString[]    = "unknown";
GLOBAL_REMOVE_IF_UNREFERENCED const char        Ddr3String[]       = "DDR3";
GLOBAL_REMOVE_IF_UNREFERENCED const char        Ddr4String[]       = "DDR4";
GLOBAL_REMOVE_IF_UNREFERENCED const char        RdimmString[]      = "RDIMM";
GLOBAL_REMOVE_IF_UNREFERENCED const char        UdimmString[]      = "UDIMM";
GLOBAL_REMOVE_IF_UNREFERENCED const char        SodimmString[]     = "SO-DIMM";
GLOBAL_REMOVE_IF_UNREFERENCED const char        Sodimm72String[]   = "72 bit SO-DIMM";
GLOBAL_REMOVE_IF_UNREFERENCED const char        StdString[]        = "Standard";
GLOBAL_REMOVE_IF_UNREFERENCED const char        Xmp1String[]       = "XMP1";
GLOBAL_REMOVE_IF_UNREFERENCED const char        Xmp2String[]       = "XMP2";
GLOBAL_REMOVE_IF_UNREFERENCED const char        XpString[]         = "  XMP profile %u is %sabled and recommended channel config: %u DIMM per channel\n";
GLOBAL_REMOVE_IF_UNREFERENCED const char        XmpDisableString[] = "Timing Profiles between DIMMs not identical, disabling XMP";
GLOBAL_REMOVE_IF_UNREFERENCED const char        ErrorString[]      = "ERROR: Unsupported ";
GLOBAL_REMOVE_IF_UNREFERENCED const char        SpdValString[]     = "SPD value: ";
GLOBAL_REMOVE_IF_UNREFERENCED const char        IsSupString[]      = " is supported";
GLOBAL_REMOVE_IF_UNREFERENCED const char        NotSupString[]     = " is not supported";
GLOBAL_REMOVE_IF_UNREFERENCED const char        TimeBaseString[]   = "Timebase (MTB/FTB)";
GLOBAL_REMOVE_IF_UNREFERENCED const char        tAAString[]        = "CAS Latency Time (tAAmin)";
GLOBAL_REMOVE_IF_UNREFERENCED const char        tCKString[]        = "SDRAM Cycle Time (tCKmin)";
GLOBAL_REMOVE_IF_UNREFERENCED const char        tWRString[]        = "Write recovery time (tWRmin)";
GLOBAL_REMOVE_IF_UNREFERENCED const char        tRCDString[]       = "RAS# to CAS# delay time (tRCDmin)";
GLOBAL_REMOVE_IF_UNREFERENCED const char        tRRDString[]       = "Row active to row active delay time (tRRDmin)";
GLOBAL_REMOVE_IF_UNREFERENCED const char        tRPString[]        = "Row precharge delay time (tRPmin)";
GLOBAL_REMOVE_IF_UNREFERENCED const char        Lpddr3String[]     = "LPDDR3";
GLOBAL_REMOVE_IF_UNREFERENCED const char        LpDimmString[]     = "LP-DIMM";
GLOBAL_REMOVE_IF_UNREFERENCED const char        MemoryDownString[] = "Memory Down";
GLOBAL_REMOVE_IF_UNREFERENCED const char        tRPabString[]      = "Row precharge delay time for all banks (tRPab)";
GLOBAL_REMOVE_IF_UNREFERENCED const char        tRASString[]       = "Active to precharge delay time (tRASmin)";
GLOBAL_REMOVE_IF_UNREFERENCED const char        tRCString[]        = "Active to active/refresh delay time (tRCmin)";
GLOBAL_REMOVE_IF_UNREFERENCED const char        tRFCString[]       = "Refresh recovery delay time (tRFCmin)";
GLOBAL_REMOVE_IF_UNREFERENCED const char        tWTRString[]       = "Internal write to read command delay time (tWTRmin)";
GLOBAL_REMOVE_IF_UNREFERENCED const char        tRTPString[]       = "Internal read to precharge delay time (tRTPmin)";
GLOBAL_REMOVE_IF_UNREFERENCED const char        tFAWString[]       = "Active to active/refresh delay time (tFAWmin)";
GLOBAL_REMOVE_IF_UNREFERENCED const char        tREFIString[]      = "Average Periodic Refresh Interval (tREFImin)";
GLOBAL_REMOVE_IF_UNREFERENCED const char        tCWLString[]       = "CAS Write Latency (tCWLmin)";
GLOBAL_REMOVE_IF_UNREFERENCED const char        NmodeString[]      = "Command rate mode (Nmode)";
GLOBAL_REMOVE_IF_UNREFERENCED const char        VddString[]        = "Module voltage VDD (mVolts)";
GLOBAL_REMOVE_IF_UNREFERENCED const char        BestCaseString[]   = "Best case value for profiles 0-";
GLOBAL_REMOVE_IF_UNREFERENCED const char        gProfileString[]   = "Profile";
GLOBAL_REMOVE_IF_UNREFERENCED const char        HeaderString[]     = "Profile Controller Channel Dimm Value";
GLOBAL_REMOVE_IF_UNREFERENCED const char        tRRDSString[]      = "Row active to row active delay time (tRRD_Smin)";
GLOBAL_REMOVE_IF_UNREFERENCED const char        tRRDLString[]      = "Row active to row active delay time (tRRD_Lmin)";
GLOBAL_REMOVE_IF_UNREFERENCED const char        tRFC2String[]      = "Refresh recovery delay time (tRFC2min)";
GLOBAL_REMOVE_IF_UNREFERENCED const char        tRFC4String[]      = "Refresh recovery delay time (tRFC4min)";
GLOBAL_REMOVE_IF_UNREFERENCED const char        tWTRLString[]      = "Internal write to read command delay time (tWTR_L)";
GLOBAL_REMOVE_IF_UNREFERENCED const char        tWTRSString[]      = "Internal write to read command delay time (tWTR_S)";
GLOBAL_REMOVE_IF_UNREFERENCED const char        RrcString[][3]     = {
                                     " A", " B", " C", " D", " E", " F", " G", " H", " J", " K",
                                     " L", " M", " N", " P", " R", " T", " U", " V", " W", " Y",
                                     "AA", "AB", "AC", "AD", "AE", "AF", "AG", "AH", "AJ", "AK",
                                     "AL", "ZZ", "AM", "AN", "AP", "AR", "AT", "AU", "AV", "AW",
                                     "AY", "BA", "BB", "BC", "BD", "BE", "BF", "BG", "BH", "BJ",
                                     "BK", "BL", "BM", "BN", "BP", "BR", "BT", "BU", "BV", "BW",
                                     "BY", "CA", "CB", "ZZ"};
#endif // MRC_DEBUG_PRINT

GLOBAL_REMOVE_IF_UNREFERENCED const UINT32 SdramCapacityTable[] = {
  (256 / 8), (512 / 8), (1024 / 8), (2048 / 8),
  (4096 / 8), (8192 / 8), (16384 / 8), (32768 / 8),
  (12288 / 8), (24576 / 8), (3072 / 8), (6144 / 8),
  (18432 / 8)
};
// Ratio | OddRatio  | Ratio | OddRatio
// 133   | 133       | 100   | 100
GLOBAL_REMOVE_IF_UNREFERENCED const TRangeTable FreqTable[] = {                                                 //       |(PLL ratio)|       |(PLL ratio)
  { 0xFFFFFFFF,           fInvalid, MRC_FREQ_INVALID                                                        }, //------------------------------------
  { MRC_DDR_800_TCK_MIN,  f800,     MRC_FREQ_133                       | MRC_FREQ_100                       }, //   3   |           |   4   |
  { MRC_DDR_1000_TCK_MIN, f1000,                                         MRC_FREQ_100                       }, //       |           |   5   |
  { MRC_DDR_1067_TCK_MIN, f1067,    MRC_FREQ_133                                                            }, //   4   |           |       |
  { MRC_DDR_1100_TCK_MIN, f1100,                                                     MRC_FREQ_100_ODD_RATIO }, //       |           |       |  5 (11)
  { MRC_DDR_1200_TCK_MIN, f1200,                MRC_FREQ_133_ODD_RATIO | MRC_FREQ_100                       }, //       |   4 (9)   |   6   |
  { MRC_DDR_1300_TCK_MIN, f1300,                                                     MRC_FREQ_100_ODD_RATIO }, //       |           |       |  6 (13)
  { MRC_DDR_1333_TCK_MIN, f1333,    MRC_FREQ_133                                                            }, //   5   |           |       |
  { MRC_DDR_1400_TCK_MIN, f1400,                                         MRC_FREQ_100                       }, //       |           |   7   |
  { MRC_DDR_1467_TCK_MIN, f1467,                MRC_FREQ_133_ODD_RATIO                                      }, //       |   5 (11)  |       |
  { MRC_DDR_1500_TCK_MIN, f1500,                                                     MRC_FREQ_100_ODD_RATIO }, //       |           |       |  7 (15)
  { MRC_DDR_1600_TCK_MIN, f1600,    MRC_FREQ_133                       | MRC_FREQ_100                       }, //   6   |           |   8   |
  { MRC_DDR_1700_TCK_MIN, f1700,                                                     MRC_FREQ_100_ODD_RATIO }, //       |           |       |  8 (17)
  { MRC_DDR_1733_TCK_MIN, f1733,                MRC_FREQ_133_ODD_RATIO                                      }, //       |   6 (13)  |       |
  { MRC_DDR_1800_TCK_MIN, f1800,                                         MRC_FREQ_100                       }, //       |           |   9   |
  { MRC_DDR_1867_TCK_MIN, f1867,    MRC_FREQ_133                                                            }, //   7   |           |       |
  { MRC_DDR_1900_TCK_MIN, f1900,                                                     MRC_FREQ_100_ODD_RATIO }, //       |           |       |  9 (19)
  { MRC_DDR_2000_TCK_MIN, f2000,                MRC_FREQ_133_ODD_RATIO | MRC_FREQ_100                       }, //       |   7 (15)  |  10   |
  { MRC_DDR_2100_TCK_MIN, f2100,                                                     MRC_FREQ_100_ODD_RATIO }, //       |           |       | 10 (21)
  { MRC_DDR_2133_TCK_MIN, f2133,    MRC_FREQ_133                                                            }, //   8   |           |       |
  { MRC_DDR_2200_TCK_MIN, f2200,                                         MRC_FREQ_100                       }, //       |           |  11   |
  { MRC_DDR_2267_TCK_MIN, f2267,                MRC_FREQ_133_ODD_RATIO                                      }, //       |   8 (17)  |       |
  { MRC_DDR_2300_TCK_MIN, f2300,                                                     MRC_FREQ_100_ODD_RATIO }, //       |           |       | 11 (23)
  { MRC_DDR_2400_TCK_MIN, f2400,    MRC_FREQ_133                       | MRC_FREQ_100                       }, //   9   |           |  12   |
  { MRC_DDR_2500_TCK_MIN, f2500,                                                     MRC_FREQ_100_ODD_RATIO }, //       |           |       | 12 (25)
  { MRC_DDR_2533_TCK_MIN, f2533,                MRC_FREQ_133_ODD_RATIO                                      }, //       |   9 (19)  |       |
  { MRC_DDR_2600_TCK_MIN, f2600,                                         MRC_FREQ_100                       }, //       |           |  13   |
  { MRC_DDR_2667_TCK_MIN, f2667,    MRC_FREQ_133                                                            }, //  10   |           |       |
  { MRC_DDR_2700_TCK_MIN, f2700,                                                     MRC_FREQ_100_ODD_RATIO }, //       |           |       | 13 (27)
  { MRC_DDR_2800_TCK_MIN, f2800,                MRC_FREQ_133_ODD_RATIO | MRC_FREQ_100                       }, //       |  10 (21)  |  14   |
  { MRC_DDR_2900_TCK_MIN, f2900,                                                     MRC_FREQ_100_ODD_RATIO }, //       |           |       | 14 (29)
  { MRC_DDR_2933_TCK_MIN, f2933,    MRC_FREQ_133                                                            }, //  11   |           |       |
  { MRC_DDR_3000_TCK_MIN, f3000,                                         MRC_FREQ_100                       }, //       |           |  15   |
  { MRC_DDR_3067_TCK_MIN, f3067,                MRC_FREQ_133_ODD_RATIO                                      }, //       |  11 (23)  |       |
  { MRC_DDR_3100_TCK_MIN, f3100,                                                     MRC_FREQ_100_ODD_RATIO }, //       |           |       | 15 (31)
  { MRC_DDR_3200_TCK_MIN, f3200,    MRC_FREQ_133                       | MRC_FREQ_100                       }, //  12   |           |  16   |
  { MRC_DDR_3300_TCK_MIN, f3300,                                                     MRC_FREQ_100_ODD_RATIO }, //       |           |       | 16 (33)
  { MRC_DDR_3333_TCK_MIN, f3333,                MRC_FREQ_133_ODD_RATIO                                      }, //       |  12 (25)  |       |
  { MRC_DDR_3400_TCK_MIN, f3400,                                         MRC_FREQ_100                       }, //       |           |  17   |
  { MRC_DDR_3467_TCK_MIN, f3467,    MRC_FREQ_133                                                            }, //  13   |           |       |
  { MRC_DDR_3500_TCK_MIN, f3500,                                                     MRC_FREQ_100_ODD_RATIO }, //       |           |       | 17 (35)
  { MRC_DDR_3600_TCK_MIN, f3600,                MRC_FREQ_133_ODD_RATIO | MRC_FREQ_100                       }, //       |  13 (27)  |  18   |
  { MRC_DDR_3700_TCK_MIN, f3700,                                                     MRC_FREQ_100_ODD_RATIO }, //       |           |       | 18 (37)
  { MRC_DDR_3733_TCK_MIN, f3733,    MRC_FREQ_133                                                            }, //  14   |           |       |
  { MRC_DDR_3800_TCK_MIN, f3800,                                         MRC_FREQ_100                       }, //       |           |  19   |
  { MRC_DDR_3867_TCK_MIN, f3867,                MRC_FREQ_133_ODD_RATIO                                      }, //       |  14 (29)  |       |
  { MRC_DDR_3900_TCK_MIN, f3900,                                                     MRC_FREQ_100_ODD_RATIO }, //       |           |       | 19 (39)
  { MRC_DDR_4000_TCK_MIN, f4000,    MRC_FREQ_133                       | MRC_FREQ_100                       }, //  15   |           |  20   |
  { MRC_DDR_4100_TCK_MIN, f4100,                                                     MRC_FREQ_100_ODD_RATIO }, //       |           |       | 20 (41)
  { MRC_DDR_4133_TCK_MIN, f4133,                MRC_FREQ_133_ODD_RATIO                                      }, //       |  15 (31)  |       |
  { MRC_DDR_4200_TCK_MIN, f4200,                                         MRC_FREQ_100                       }, //       |           |  21   |
  { MRC_DDR_4267_TCK_MIN, f4267,    MRC_FREQ_133                                                            }, //  16   |           |       |
  { MRC_DDR_4300_TCK_MIN, f4300,                                                     MRC_FREQ_100_ODD_RATIO }, //       |           |       | 21 (43)
  { MRC_DDR_4400_TCK_MIN, f4400,                MRC_FREQ_133_ODD_RATIO | MRC_FREQ_100                       }, //       |  16 (33)  |  22   |
  { MRC_DDR_4500_TCK_MIN, f4500,                                                     MRC_FREQ_100_ODD_RATIO }, //       |           |       | 22 (45)
  { MRC_DDR_4533_TCK_MIN, f4533,    MRC_FREQ_133                                                            }, //  17   |           |       |
  { MRC_DDR_4600_TCK_MIN, f4600,                                         MRC_FREQ_100                       }, //       |           |  23   |
  { MRC_DDR_4667_TCK_MIN, f4667,                MRC_FREQ_133_ODD_RATIO                                      }, //       |  17 (35)  |       |
  { MRC_DDR_4700_TCK_MIN, f4700,                                                     MRC_FREQ_100_ODD_RATIO }, //       |           |       | 23 (47)
  { MRC_DDR_4800_TCK_MIN, f4800,    MRC_FREQ_133                       | MRC_FREQ_100                       }, //  18   |           |  24   |
  { MRC_DDR_4900_TCK_MIN, f4900,                                                     MRC_FREQ_100_ODD_RATIO }, //       |           |       | 24 (49)
  { MRC_DDR_4933_TCK_MIN, f4933,                MRC_FREQ_133_ODD_RATIO                                      }, //       |  18 (37)  |       |
  { MRC_DDR_5000_TCK_MIN, f5000,                                         MRC_FREQ_100                       }, //       |           |  25   |
  { MRC_DDR_5067_TCK_MIN, f5067,    MRC_FREQ_133                                                            }, //  19   |           |       |
  { MRC_DDR_5100_TCK_MIN, f5100,                                                     MRC_FREQ_100_ODD_RATIO }, //       |           |       | 25 (51)
  { MRC_DDR_5200_TCK_MIN, f5200,                MRC_FREQ_133_ODD_RATIO | MRC_FREQ_100                       }, //       |  19 (39)  |  26   |
  { MRC_DDR_5300_TCK_MIN, f5300,                                                     MRC_FREQ_100_ODD_RATIO }, //       |           |       | 26 (53)
  { MRC_DDR_5333_TCK_MIN, f5333,    MRC_FREQ_133                                                            }, //  20   |           |       |
  { MRC_DDR_5400_TCK_MIN, f5400,                                         MRC_FREQ_100                       }, //       |           |  27   |
  { MRC_DDR_5467_TCK_MIN, f5467,                MRC_FREQ_133_ODD_RATIO                                      }, //       |  20 (41)  |       |
  { MRC_DDR_5500_TCK_MIN, f5500,                                                     MRC_FREQ_100_ODD_RATIO }, //       |           |       | 27 (55)
  { MRC_DDR_5600_TCK_MIN, f5600,    MRC_FREQ_133                       | MRC_FREQ_100                       }, //  21   |           |  28   |
  { MRC_DDR_5700_TCK_MIN, f5700,                                                     MRC_FREQ_100_ODD_RATIO }, //       |           |       | 28 (57)
  { MRC_DDR_5733_TCK_MIN, f5733,                MRC_FREQ_133_ODD_RATIO                                      }, //       |  21 (43)  |       |
  { MRC_DDR_5800_TCK_MIN, f5800,                                         MRC_FREQ_100                       }, //       |           |  29   |
  { MRC_DDR_5867_TCK_MIN, f5867,    MRC_FREQ_133                                                            }, //  22   |           |       |
  { MRC_DDR_5900_TCK_MIN, f5900,                                                     MRC_FREQ_100_ODD_RATIO }, //       |           |       | 29 (59)
  { MRC_DDR_6000_TCK_MIN, f6000,                MRC_FREQ_133_ODD_RATIO | MRC_FREQ_100                       }, //       |  22 (45)  |  30   |
  { MRC_DDR_6100_TCK_MIN, f6100,                                                     MRC_FREQ_100_ODD_RATIO }, //       |           |       | 30 (61)
  { MRC_DDR_6133_TCK_MIN, f6133,    MRC_FREQ_133                                                            }, //  23   |           |       |
  { MRC_DDR_6200_TCK_MIN, f6200,                                         MRC_FREQ_100                       }, //       |           |  31   |
  { MRC_DDR_6267_TCK_MIN, f6267,                MRC_FREQ_133_ODD_RATIO                                      }, //       |  23 (47)  |       |
  { MRC_DDR_6300_TCK_MIN, f6300,                                                     MRC_FREQ_100_ODD_RATIO }, //       |           |       | 31 (63)
  { MRC_DDR_6400_TCK_MIN, f6400,    MRC_FREQ_133                                                            }, //  24   |           |       |
  { MRC_DDR_6533_TCK_MIN, f6533,                MRC_FREQ_133_ODD_RATIO                                      }, //       |  24 (49)  |       |
  { MRC_DDR_6667_TCK_MIN, f6667,    MRC_FREQ_133                                                            }, //  25   |           |       |
  { MRC_DDR_6800_TCK_MIN, f6800,                MRC_FREQ_133_ODD_RATIO                                      }, //       |  25 (51)  |       |
  { MRC_DDR_6933_TCK_MIN, f6933,    MRC_FREQ_133                                                            }, //  26   |           |       |
  { MRC_DDR_7067_TCK_MIN, f7067,                MRC_FREQ_133_ODD_RATIO                                      }, //       |  26 (53)  |       |
  { MRC_DDR_7200_TCK_MIN, f7200,    MRC_FREQ_133                                                            }, //  27   |           |       |
  { MRC_DDR_7333_TCK_MIN, f7333,                MRC_FREQ_133_ODD_RATIO                                      }, //       |  27 (55)  |       |
  { MRC_DDR_7467_TCK_MIN, f7467,    MRC_FREQ_133                                                            }, //  28   |           |       |
  { MRC_DDR_7600_TCK_MIN, f7600,                MRC_FREQ_133_ODD_RATIO                                      }, //       |  28 (57)  |       |
  { MRC_DDR_7733_TCK_MIN, f7733,    MRC_FREQ_133                                                            }, //  29   |           |       |
  { MRC_DDR_7867_TCK_MIN, f7867,                MRC_FREQ_133_ODD_RATIO                                      }, //       |  29 (59)  |       |
  { MRC_DDR_8000_TCK_MIN, f8000,    MRC_FREQ_133                                                            }, //  30   |           |       |
  { MRC_DDR_8133_TCK_MIN, f8133,                MRC_FREQ_133_ODD_RATIO                                      }, //       |  30 (61)  |       |
  { MRC_DDR_8267_TCK_MIN, f8267,    MRC_FREQ_133                                                            }, //  31   |           |       |
  { MRC_DDR_8400_TCK_MIN, f8400,                MRC_FREQ_133_ODD_RATIO                                      }, //       |  31 (63)  |       |
  { 0,                    fNoInit,  MRC_FREQ_INVALID                                                        }
};

GLOBAL_REMOVE_IF_UNREFERENCED const SupportTable PlatformSupport = {
  {TRAD_SUPPORT_LPDDR3,    ULT_SUPPORT_LPDDR3,    BDW_SUPPORT_LPDDR3   },
  {TRAD_SUPPORT_COLUMN_10, ULT_SUPPORT_COLUMN_10, BDW_SUPPORT_COLUMN_10},
  {TRAD_SUPPORT_COLUMN_11, ULT_SUPPORT_COLUMN_11, BDW_SUPPORT_COLUMN_11},
  {TRAD_SUPPORT_COLUMN_12, ULT_SUPPORT_COLUMN_12, BDW_SUPPORT_COLUMN_12},
  {TRAD_VDDMINPOSSIBLE,    ULT_VDDMINPOSSIBLE,    ULT_VDDMINPOSSIBLE   },
  {TRAD_VDDMAXPOSSIBLE,    ULT_VDDMAXPOSSIBLE,    ULT_VDDMAXPOSSIBLE   }
};

/**
    Calculate the memory clock value from the current memory frequency.

    @param[in, out] MrcData     - Pointer to MrcData data structure.
    @param[in]      Frequency   - Memory frequency to convert.

    @retval Returns the tCK value in [fs] for the given frequency.
**/
UINT32
ConvertFreq2Clock (
  IN OUT MrcParameters *const MrcData,
  IN     const MrcFrequency   Frequency
  )
{
  UINT32 tCKminActual;
  UINT32 Index;

  tCKminActual = MRC_DDR_800_TCK_MIN;
  for (Index = 0; Index < ARRAY_COUNT (FreqTable); Index++) {
    if (Frequency == FreqTable[Index].Frequency) {
      tCKminActual = FreqTable[Index].tCK;
      break;
    }
  }
  return tCKminActual;
}

/**
  Calculate the memory frequency from the memory clock value.

    @param[in, out] MrcData       - Pointer to MrcData data structure.
    @param[in]      RefClk        - The memory reference clock.
    @param[in]      tCKmin        - The tCKmin value in [fs] to convert.
    @param[out]     tCKminIndex   - Pointer to the chosen table index.
    @param[out]     tCKminActual  - Pointer to the chosen tCK value.
    @param[out]     OddRatioMode  - Pointer to the chosen Odd Ratio mode.

    @retval Returns the frequency that matches the given tCK.
**/
static
UINT32
ConvertClock2Freq (
  IN OUT MrcParameters *const  MrcData,
  IN     const MrcRefClkSelect RefClk,
  IN     const UINT32          tCKmin,
  OUT    INT32         *const  tCKminIndex,
  OUT    UINT32        *const  tCKminActual,
  OUT    BOOLEAN       *const  OddRatioMode
  )
{
  MrcInput      *Inputs;
  MrcFrequency  Frequency;
  UINT32        Index;
  UINT32        tCKminPs;
  UINT32        FreqPs;
  UINT32        NextFreqPs;
  BOOLEAN       OddRatio;
  UINT8         FreqFlag;

  Inputs  = &MrcData->Inputs;
  OddRatio = MrcData->Outputs.OddRatioMode;

  //
  // Convert tCK value to the nearest frequency value.
  // Then find slowest valid frequency for the given reference clock.
  // Round to the [ps] resolution, because SPD FineTimeBase is 1ps.
  //
  Frequency = fNoInit;
  for (Index = 0; Index < ARRAY_COUNT (FreqTable) - 1; Index++) {
    tCKminPs    = UDIVIDEROUND (tCKmin, 1000);
    FreqPs      = UDIVIDEROUND (FreqTable[Index].tCK, 1000);
    NextFreqPs  = UDIVIDEROUND (FreqTable[Index + 1].tCK, 1000);
    if ((tCKminPs <= FreqPs) && (tCKminPs > NextFreqPs)) {
      Frequency = FreqTable[Index].Frequency;
      break;
    }
  }

  while (Index) {
    FreqFlag = FreqTable[Index].FreqFlag;
    if ((FreqFlag & (1 << RefClk)) != 0) {
      break;        // We can have this frequency at the given refclk
    }
    if ((FreqFlag & (MRC_BIT2 << RefClk)) != 0) {
      OddRatio = 1; // We can have this frequency at the given refclk using Odd Ratio mode
      break;
    }
    Frequency = FreqTable[--Index].Frequency;
  }
  if (tCKminIndex != NULL) {
    *tCKminIndex = Index;
  }
  if (tCKminActual != NULL) {
    *tCKminActual = FreqTable[Index].tCK;
  }
  if (OddRatioMode != NULL) {
    *OddRatioMode = OddRatio;
  }
  return Frequency;
}

/**
  Returns whether the specified XMP profile is enabled or not.

  @param[in] MrcData           - Include all MRC global data.
  @param[in] Profile           - Profile to test.  {0: STD_PROFILE,
                                                    1: USER_PROFILE,
                                                    2: XMP_PROFILE1,
                                                    3: XMP_PROFILE2}

  @retval TRUE  - if the specified XMP profile is enabled, or if STD_PROFILE or USER_PROFILE is passed in.
  @retval FALSE - if the specified XMP profile is disabled
**/
BOOLEAN
MrcXmpTimingProfileEnabled (
  IN MrcParameters *const MrcData,
  IN const MrcProfile     Profile
  )
{
  if (Profile < XMP_PROFILE1) {
    return TRUE;
  }
  return (MrcData->Outputs.XmpProfileEnable & ((Profile == XMP_PROFILE1) ? XMP1_PROFILE_ENABLE : XMP2_PROFILE_ENABLE)) != 0 ? TRUE : FALSE;
}

/**
  Returns whether the specified XMP profile is supported by the DIMM

  @param[in] DimmOut           - Pointer to structure containing DIMM information.
  @param[in] Profile           - Profile to test.  {0: STD_PROFILE,
                                                    1: USER_PROFILE,
                                                    2: XMP_PROFILE1,
                                                    3: XMP_PROFILE2}

  @retval TRUE  - if the specified XMP profile is supported, or if STD_PROFILE or USER_PROFILE is passed in.
  @retval FALSE - if the specified XMP profile is unsupported.
  **/
BOOLEAN
MrcDimmXmpProfileSupported (
  IN MrcDimmOut    *const DimmOut,
  IN const MrcProfile     Profile
  )
{
  if (Profile < XMP_PROFILE1) {
    return TRUE;
  }
  return (DimmOut->XmpSupport & ((Profile == XMP_PROFILE1) ? XMP1_PROFILE_ENABLE : XMP2_PROFILE_ENABLE)) != 0 ? TRUE : FALSE;
}

/**
  Determine if the DIMM slot is filled.
  If a valid DRAM device type and valid module package are found then a DIMM is present.

    @param[in] MrcData - Pointer to MrcData data structure.
    @param[in] Spd     - Pointer to Spd data structure.

    @retval TRUE on valid value, otherwise FALSE and the value is set to zero.
**/
MrcDimmSts
DimmPresence (
  IN MrcDebug      *const Debug,
  IN const MrcSpd  *const Spd
  )
{
  UINT8         DramType;
  UINT8         ModuleType;

  //
  // The following code will more closely identify memory instead of just searching for non-zero data.
  //

  //
  // Check for valid DRAM device type.
  //
  ModuleType = 0xFF;
  DramType = Spd->Ddr3.General.DramDeviceType.Bits.Type;
  if ((DramType == MRC_SPD_DDR3_SDRAM_TYPE_NUMBER) ||
      (DramType == MRC_SPD_LPDDR3_SDRAM_TYPE_NUMBER) ||
      (DramType == MRC_JEDEC_LPDDR3_SDRAM_TYPE_NUMBER) ||
      (DramType == MRC_SPD_DDR4_SDRAM_TYPE_NUMBER)) {
    //
    // Check for valid module package.
    //
    ModuleType = Spd->Ddr3.General.ModuleType.Bits.ModuleType;
    if ((ModuleType == UDimmMemoryPackage) ||
        (ModuleType == SoDimmMemoryPackage) ||
        (ModuleType == SoUDimmEccMemoryPackageDdr3) ||
        (ModuleType == SoUDimmEccMemoryPackageDdr4) ||
#if (SUPPORT_RDIMM == SUPPORT)
        (ModuleType == RDimmMemoryPackage) ||
#endif
        ((ModuleType == LpDimmMemoryPackage) && (DramType == MRC_JEDEC_LPDDR3_SDRAM_TYPE_NUMBER)) ||
        ((ModuleType == NonDimmMemoryPackage) && (DramType == MRC_JEDEC_LPDDR3_SDRAM_TYPE_NUMBER))
        ) {
      return DIMM_PRESENT;
    }
  }

#if (SUPPORT_RDIMM == UNSUPPORT)
  if (ModuleType == RDimmMemoryPackage) {
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "  ERROR: RDIMM detected - not supported!\n");
  }
#endif
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_WARNING, "  Warning: No supported DIMM detected in slot\n");
  return DIMM_NOT_PRESENT;
}

/**
  Determine if the DIMM is valid and supported.

    @param[in, out] MrcData - Pointer to MrcData data structure.
    @param[in]      Spd     - Pointer to Spd data structure.
    @param[in, out] DimmOut - Pointer to structure containing DIMM information.

    @retval TRUE on valid value, otherwise FALSE.
**/
static
BOOLEAN
ValidDimm (
  IN OUT MrcParameters *const MrcData,
  IN     const MrcSpd  *const Spd,
  IN OUT MrcDimmOut    *const DimmOut
  )
{
  BOOLEAN                                      Ddr3;
  BOOLEAN                                      Ddr4;
  BOOLEAN                                      Lpddr;
  BOOLEAN                                      DimmValid;
  UINT8                                        DeviceType;
  MrcProfile                                   MemProfile;
  const SPD_EXTREME_MEMORY_PROFILE_HEADER      *Header3;
  const SPD_EXTREME_MEMORY_PROFILE_HEADER_2_0  *Header4;
  SpdVddFlag                                   VddFlag;
#ifdef MRC_DEBUG_PRINT
  static const UINT16                          BytesUsedConst[] = {0, 128, 176, 256};
  MrcDebug                                     *Debug;
  const char                                   *DramTypeString;
  const char                                   *ModuleTypeString;
  const char                                   *ProfileString;
  SPD_REVISION_STRUCT                          Revision;
  UINT16                                       BytesUsed;
  UINT16                                       BytesTotal;
  UINT16                                       CrcCoverage;

  Debug = &MrcData->Outputs.Debug;
  ModuleTypeString = UnknownString;
#endif // MRC_DEBUG_PRINT

  DimmValid  = TRUE;
  Ddr3       = FALSE;
  Ddr4       = FALSE;
  Lpddr      = FALSE;
  MemProfile = MrcData->Inputs.MemoryProfile;
  Header3    = &Spd->Ddr3.Xmp.Header;
  Header4    = &Spd->Ddr4.EndUser.Xmp.Header;

  //
  // The dram device type is at the same SPD offset for all types.
  //
  DeviceType = Spd->Ddr3.General.DramDeviceType.Bits.Type;

  VddFlag.Bits.Vdd1_35 = Spd->Ddr3.General.ModuleNominalVoltage.Bits.OperationAt1_35;

  switch (DeviceType) {
    case MRC_SPD_DDR3_SDRAM_TYPE_NUMBER:
      DimmOut->DdrType    = MRC_DDR_TYPE_DDR3;
      DimmOut->ModuleType = Spd->Ddr3.General.ModuleType.Bits.ModuleType;
      Ddr3                = TRUE;
      if (VddFlag.Bits.Vdd1_35 == 0) { // SKL doesn't support 1.5v DDR3
        DimmValid = FALSE;
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "  DDR3 memory does not support 1.35V operation\n");
      }
      break;

    case MRC_SPD_DDR4_SDRAM_TYPE_NUMBER:
      DimmOut->DdrType    = MRC_DDR_TYPE_DDR4;
      DimmOut->ModuleType = Spd->Ddr4.Base.ModuleType.Bits.ModuleType;
      Ddr4                = TRUE;
      break;

    case MRC_SPD_LPDDR3_SDRAM_TYPE_NUMBER:
    case MRC_JEDEC_LPDDR3_SDRAM_TYPE_NUMBER:
      DimmOut->DdrType    = MRC_DDR_TYPE_LPDDR3;
      DimmOut->ModuleType = (DeviceType == MRC_SPD_LPDDR3_SDRAM_TYPE_NUMBER) ? Spd->Ddr3.General.ModuleType.Bits.ModuleType : Spd->Lpddr.Base.ModuleType.Bits.ModuleType;
      Lpddr               = TRUE;
      break;

    default:
      DimmOut->DdrType    = MRC_DDR_TYPE_UNKNOWN;
      DimmOut->ModuleType = 0;
      DimmValid           = FALSE;
      break;
  }

  if (DimmValid) {
    switch (DimmOut->ModuleType) {
#if (SUPPORT_RDIMM == SUPPORT)
      case RDimmMemoryPackage:
#ifdef MRC_DEBUG_PRINT
        ModuleTypeString = RdimmString;
#endif // MRC_DEBUG_PRINT
        break;
#endif

#if (SUPPORT_UDIMM == SUPPORT)
      case UDimmMemoryPackage:
#ifdef MRC_DEBUG_PRINT
        ModuleTypeString = UdimmString;
#endif // MRC_DEBUG_PRINT
        break;
#endif

#if (SUPPORT_SODIMM == SUPPORT)
      case SoDimmMemoryPackage:
#ifdef MRC_DEBUG_PRINT
        ModuleTypeString = SodimmString;
#endif // MRC_DEBUG_PRINT
        break;

      case SoUDimmEccMemoryPackageDdr3:
        if (Ddr3) {
#ifdef MRC_DEBUG_PRINT
          ModuleTypeString = SodimmString;
#endif // MRC_DEBUG_PRINT
        } else {
          DimmValid = FALSE;
        }
        break;

      case SoUDimmEccMemoryPackageDdr4:
        if (Ddr4) {
#ifdef MRC_DEBUG_PRINT
          ModuleTypeString = SodimmString;
#endif // MRC_DEBUG_PRINT
        } else {
          DimmValid = FALSE;
        }
        break;
#endif // SUPPORT_SODIMM
#if (JEDEC_SUPPORT_LPDDR == SUPPORT)
      case LpDimmMemoryPackage:
        if (Lpddr) {
#ifdef MRC_DEBUG_PRINT
          ModuleTypeString = LpDimmString;
#endif // MRC_DEBUG_PRINT
        } else {
          DimmValid = FALSE;
        }
        break;
      case NonDimmMemoryPackage:
        if (Lpddr) {
#ifdef MRC_DEBUG_PRINT
          ModuleTypeString = MemoryDownString;
#endif // MRC_DEBUG_PRINT
        } else {
          DimmValid = FALSE;
        }
        break;
#endif // JEDEC_SUPPORT_LPDDR
      default:
        DimmValid = FALSE;
        break;
    }
  }

  DimmOut->XmpSupport = 0;
  if (DimmValid) {
    if (Ddr3) {
      if (XMP_ID_STRING == Header3->XmpId) {
        if (0x12 == (Header3->XmpRevision.Data & 0xFE)) {
          DimmOut->XmpRevision = Header3->XmpRevision.Data;
        }
        if (Header3->XmpOrgConf.Bits.ProfileEnable1 != 0) {
          DimmOut->XmpSupport |= 1;
        }
        if (Header3->XmpOrgConf.Bits.ProfileEnable2 != 0) {
          DimmOut->XmpSupport |= 2;
        }
      }
    }
    if (Ddr4) {
      if (XMP_ID_STRING == Header4->XmpId) {
        if (0x20 == (Header4->XmpRevision.Data)) {
          DimmOut->XmpRevision = Header4->XmpRevision.Data;
        }
        if (Header4->XmpOrgConf.Bits.ProfileEnable1 != 0) {
          DimmOut->XmpSupport |= 1;
        }
        if (Header4->XmpOrgConf.Bits.ProfileEnable2 != 0) {
          DimmOut->XmpSupport |= 2;
        }
      }
    }
  }

#ifdef MRC_DEBUG_PRINT
  switch (MemProfile) {
    case STD_PROFILE:
    case USER_PROFILE:
    default:
      ProfileString = StdString;
      break;
    case XMP_PROFILE1:
      ProfileString = Xmp1String;
      break;
    case XMP_PROFILE2:
      ProfileString = Xmp2String;
      break;
  }

  switch (DeviceType) {
    case MRC_SPD_DDR3_SDRAM_TYPE_NUMBER:
    case MRC_SPD_LPDDR3_SDRAM_TYPE_NUMBER:
      DramTypeString = (DeviceType == MRC_SPD_LPDDR3_SDRAM_TYPE_NUMBER) ? Lpddr3String : Ddr3String;
      BytesTotal    = 256 * Spd->Ddr3.General.Description.Bits.BytesTotal;
      BytesUsed     = BytesUsedConst[Spd->Ddr3.General.Description.Bits.BytesUsed & 3];
      CrcCoverage   = 125 - (9 * Spd->Ddr3.General.Description.Bits.CrcCoverage);
      Revision.Data = Spd->Ddr3.General.Revision.Data;
      break;

    case MRC_SPD_DDR4_SDRAM_TYPE_NUMBER:
      DramTypeString = Ddr4String;
      BytesTotal     = 256 * Spd->Ddr4.Base.Description.Bits.BytesTotal;
      BytesUsed      = BytesUsedConst[1] * Spd->Ddr4.Base.Description.Bits.BytesUsed;
      CrcCoverage    = 125;
      Revision.Data  = Spd->Ddr4.Base.Revision.Data;
      break;

    case MRC_JEDEC_LPDDR3_SDRAM_TYPE_NUMBER:
      DramTypeString = Lpddr3String;
      BytesTotal     = 256 * Spd->Lpddr.Base.Description.Bits.BytesTotal;
      BytesUsed      = BytesUsedConst[1] * Spd->Lpddr.Base.Description.Bits.BytesUsed;
      CrcCoverage    = 125;
      Revision.Data  = Spd->Lpddr.Base.Revision.Data;
      break;

    default:
      DramTypeString = UnknownString;
      BytesTotal     = 0;
      BytesUsed      = 0;
      CrcCoverage    = 0;
      Revision.Data  = 0;
      break;
  }

  if (DimmValid) {
    MRC_DEBUG_MSG (
      Debug,
      MSG_LEVEL_NOTE,
      "  %s %s detected, Rev: %u.%u, Size: %u used/%u total, CRC coverage: 0 - %u\n",
      DramTypeString,
      ModuleTypeString,
      Revision.Bits.Major,
      Revision.Bits.Minor,
      BytesUsed,
      BytesTotal,
      CrcCoverage
      );
  } else {
    MRC_DEBUG_MSG (
      Debug,
      MSG_LEVEL_ERROR,
      "  %s %s detected, SPD Dram type %Xh, module type %Xh\n",
      DramTypeString,
      ModuleTypeString,
      DeviceType,
      DimmOut->ModuleType
      );
  }

  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "  DIMM profile %s selected\n", ProfileString);
  if (Ddr3) {
    MRC_DEBUG_MSG (
      Debug,
      MSG_LEVEL_NOTE,
      "  XMP String: %Xh\n",
      Header3->XmpId
      );
    if (XMP_ID_STRING == Header3->XmpId) {
      MRC_DEBUG_MSG (
        Debug,
        MSG_LEVEL_NOTE,
        "  XMP Revision: %u.%u\n",
        Header3->XmpRevision.Bits.Major,
        Header3->XmpRevision.Bits.Minor
        );
      MRC_DEBUG_MSG (
        Debug,
        MSG_LEVEL_NOTE,
        XpString,
        1,
        Header3->XmpOrgConf.Bits.ProfileEnable1 ? "en" : "dis",
        Header3->XmpOrgConf.Bits.ProfileConfig1 + 1
        );
      MRC_DEBUG_MSG (
        Debug,
        MSG_LEVEL_NOTE,
        XpString,
        2,
        Header3->XmpOrgConf.Bits.ProfileEnable2 ? "en" : "dis",
        Header3->XmpOrgConf.Bits.ProfileConfig2 + 1
        );
    }
  }
  if (Ddr4) {
    MRC_DEBUG_MSG (
      Debug,
      MSG_LEVEL_NOTE,
      "  XMP String: %Xh\n",
      Header4->XmpId
      );
    if (XMP_ID_STRING == Header4->XmpId) {
      MRC_DEBUG_MSG (
        Debug,
        MSG_LEVEL_NOTE,
        "  XMP Revision: %u.%u\n",
        Header4->XmpRevision.Bits.Major,
        Header4->XmpRevision.Bits.Minor
        );
      MRC_DEBUG_MSG (
        Debug,
        MSG_LEVEL_NOTE,
        XpString,
        1,
        Header4->XmpOrgConf.Bits.ProfileEnable1 ? "en" : "dis",
        Header4->XmpOrgConf.Bits.ProfileConfig1 + 1
        );
      MRC_DEBUG_MSG (
        Debug,
        MSG_LEVEL_NOTE,
        XpString,
        2,
        Header4->XmpOrgConf.Bits.ProfileEnable2 ? "en" : "dis",
        Header4->XmpOrgConf.Bits.ProfileConfig2 + 1
        );
    }
  }

#endif // MRC_DEBUG_PRINT

  return DimmValid;
}

/**
  Determine if the DIMM SDRAM device width is valid and return the value.

    @param[in, out] MrcData - Pointer to MrcData data structure.
    @param[in]      Spd     - Pointer to Spd data structure.
    @param[in, out] DimmOut - Pointer to structure containing DIMM information.

    @retval TRUE on valid value, otherwise FALSE and the value is set to zero.
**/
static
BOOLEAN
ValidSdramDeviceWidth (
  IN OUT MrcParameters   *const MrcData,
  IN const MrcSpd        *const Spd,
  IN OUT MrcDimmOut      *const DimmOut
  )
{
  MrcDebug  *Debug;

  Debug = &MrcData->Outputs.Debug;

  if ((MRC_DDR_TYPE_DDR3 == DimmOut->DdrType) || (Spd->Ddr3.General.DramDeviceType.Bits.Type == MRC_SPD_LPDDR3_SDRAM_TYPE_NUMBER)) {
    DimmOut->SdramWidthIndex = Spd->Ddr3.General.ModuleOrganization.Bits.SdramDeviceWidth;
  } else if (MRC_DDR_TYPE_DDR4 == DimmOut->DdrType) {
    DimmOut->SdramWidthIndex = Spd->Ddr4.Base.ModuleOrganization.Bits.SdramDeviceWidth;
  } else {
    DimmOut->SdramWidthIndex = Spd->Lpddr.Base.ModuleOrganization.Bits.SdramDeviceWidth;
  }

  switch (DimmOut->SdramWidthIndex) {

    case MRC_SPD_SDRAM_DEVICE_WIDTH_4:
      DimmOut->SdramWidth = 4;
      break;

#if (SUPPORT_DEVWIDTH_8 == SUPPORT)
    case MRC_SPD_SDRAM_DEVICE_WIDTH_8:
      DimmOut->SdramWidth = 8;
      break;
#endif
#if (SUPPORT_DEVWIDTH_16 == SUPPORT)
    case MRC_SPD_SDRAM_DEVICE_WIDTH_16:
      DimmOut->SdramWidth = 16;
      break;
#endif
#if (SUPPORT_DEVWIDTH_32 == SUPPORT)
    case MRC_SPD_SDRAM_DEVICE_WIDTH_32:
      DimmOut->SdramWidth = 32;
      break;
#endif

    default:
      DimmOut->SdramWidth = 0;
      MRC_DEBUG_MSG (Debug,
        MSG_LEVEL_ERROR,
        "%sSDRAM device width, %s%Xh\n",
        ErrorString,
        SpdValString,
        DimmOut->SdramWidthIndex
        );
      return FALSE;
  }

  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "  SDRAM device width: %u\n", DimmOut->SdramWidth);
  return TRUE;
}

/**
  Determine if the DIMM SDRAM row address size is valid and return the value.

    @param[in, out] MrcData - Pointer to MrcData data structure.
    @param[in]      Spd     - Pointer to Spd data structure.
    @param[in, out] DimmOut - Pointer to structure containing DIMM information.

    @retval TRUE if the row address size is valid, otherwise FALSE and the value is set to zero.
**/
static
BOOLEAN
ValidRowSize (
  IN OUT MrcParameters   *const MrcData,
  IN const MrcSpd        *const Spd,
  IN OUT MrcDimmOut      *const DimmOut
  )
{
  UINT8        RowBits;
  UINT8        RowAddress;
  MrcDebug        *Debug;

  Debug = &MrcData->Outputs.Debug;

  if ((MRC_DDR_TYPE_DDR3 == DimmOut->DdrType) || (Spd->Ddr3.General.DramDeviceType.Bits.Type == MRC_SPD_LPDDR3_SDRAM_TYPE_NUMBER)) {
    RowAddress = Spd->Ddr3.General.SdramAddressing.Bits.RowAddress;
  } else if (MRC_DDR_TYPE_DDR4 == DimmOut->DdrType) {
    RowAddress = Spd->Ddr4.Base.SdramAddressing.Bits.RowAddress;
  } else {
    RowAddress = Spd->Lpddr.Base.SdramAddressing.Bits.RowAddress;
  }

  switch (RowAddress) {
#if (SUPPORT_ROW_12 == SUPPORT)
    case MRC_SPD_SDRAM_ROW_12:
      DimmOut->RowSize = MRC_BIT12;
      RowBits          = 12;
      break;
#endif
#if (SUPPORT_ROW_13 == SUPPORT)
    case MRC_SPD_SDRAM_ROW_13:
      DimmOut->RowSize = MRC_BIT13;
      RowBits          = 13;
      break;
#endif
#if (SUPPORT_ROW_14 == SUPPORT)
    case MRC_SPD_SDRAM_ROW_14:
      DimmOut->RowSize = MRC_BIT14;
      RowBits          = 14;
      break;
#endif
#if (SUPPORT_ROW_15 == SUPPORT)
    case MRC_SPD_SDRAM_ROW_15:
      DimmOut->RowSize = MRC_BIT15;
      RowBits          = 15;
      break;
#endif
#if (SUPPORT_ROW_16 == SUPPORT)
    case MRC_SPD_SDRAM_ROW_16:
      DimmOut->RowSize = MRC_BIT16;
      RowBits          = 16;
      break;
#endif
#if (SUPPORT_ROW_17 == SUPPORT)
    case MRC_SPD_SDRAM_ROW_17:
      DimmOut->RowSize = MRC_BIT17;
      RowBits          = 17;
      break;
#endif
#if (SUPPORT_ROW_18 == SUPPORT)
    case MRC_SPD_SDRAM_ROW_18:
      DimmOut->RowSize = MRC_BIT18;
      RowBits          = 18;
      break;
#endif
    default:
      DimmOut->RowSize = 0;
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "%sSDRAM row size, %s%Xh\n", ErrorString, SpdValString, RowAddress);
      return FALSE;
  }

  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "  Row bits: %u\n", RowBits);
  return TRUE;
}

/**
  Determine if the DIMM SDRAM column address size is valid and return the value.

    @param[in, out] MrcData - Pointer to MrcData data structure.
    @param[in]      Spd     - Pointer to Spd data structure.
    @param[in, out] DimmOut - Pointer to structure containing DIMM information.

    @retval TRUE if the column address size is valid, otherwise FALSE and the value is set to zero.
**/
static
BOOLEAN
ValidColumnSize (
  IN OUT MrcParameters   *const MrcData,
  IN const MrcSpd        *const Spd,
  IN OUT MrcDimmOut      *const DimmOut
  )
{
  MrcDebug     *Debug;
  UINT8        ColumnBits;
  UINT8        ColumnAddress;
  MrcCpuModel  CpuModel;
  BOOLEAN      UlxUlt;

  Debug    = &MrcData->Outputs.Debug;
  CpuModel = MrcData->Inputs.CpuModel;
  UlxUlt   = ((CpuModel == cmSKL_ULX_ULT) || (CpuModel == cmKBL_ULX_ULT));

  if ((MRC_DDR_TYPE_DDR3 == DimmOut->DdrType) || (Spd->Ddr3.General.DramDeviceType.Bits.Type == MRC_SPD_LPDDR3_SDRAM_TYPE_NUMBER)) {
    ColumnAddress = Spd->Ddr3.General.SdramAddressing.Bits.ColumnAddress;
  } else if (MRC_DDR_TYPE_DDR4 == DimmOut->DdrType) {
    ColumnAddress = Spd->Ddr4.Base.SdramAddressing.Bits.ColumnAddress;
  } else {
    ColumnAddress = Spd->Lpddr.Base.SdramAddressing.Bits.ColumnAddress;
  }

  switch (ColumnAddress) {
#if (SUPPORT_COLUMN_9 == SUPPORT)
    case MRC_SPD_SDRAM_COLUMN_9:
      DimmOut->ColumnSize = MRC_BIT9;
      ColumnBits          = 9;
      break;
#endif
    case MRC_SPD_SDRAM_COLUMN_10:
      DimmOut->ColumnSize = MRC_BIT10;
      ColumnBits          = 10;
      break;
#if (SUPPORT_COLUMN_11 == SUPPORT)
    case MRC_SPD_SDRAM_COLUMN_11:
      DimmOut->ColumnSize = MRC_BIT11;
      ColumnBits          = 11;
      break;
      // no break;
#endif
#if (SUPPORT_COLUMN_12 == SUPPORT)
    case MRC_SPD_SDRAM_COLUMN_12:
      if ((UlxUlt) && (PlatformSupport.Column12.UltSupport)) {
        DimmOut->ColumnSize = MRC_BIT12;
        ColumnBits          = 12;
        break;
      }
      // no break;
#endif
    default:
      DimmOut->ColumnSize = 0;
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "%sSDRAM column size, %s%Xh\n", ErrorString, SpdValString, ColumnAddress);
      return FALSE;
  }

  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "  Column bits: %u\n", ColumnBits);
  return TRUE;
}

/**
  Determine if the DIMM SDRAM primary bus width is valid and return the value.

    @param[in, out] MrcData - Pointer to MrcData data structure.
    @param[in]      Spd     - Pointer to Spd data structure.
    @param[in, out] DimmOut - Pointer to structure containing DIMM information.

    @retval TRUE on valid value, otherwise FALSE and the value is set to zero.
**/
static
BOOLEAN
ValidPrimaryWidth (
  IN OUT MrcParameters   *const MrcData,
  IN const MrcSpd        *const Spd,
  IN OUT MrcDimmOut      *const DimmOut
  )
{
  UINT8     Width;
  MrcDebug  *Debug;

  Debug = &MrcData->Outputs.Debug;

  if ((MRC_DDR_TYPE_DDR3 == DimmOut->DdrType) || (Spd->Ddr3.General.DramDeviceType.Bits.Type == MRC_SPD_LPDDR3_SDRAM_TYPE_NUMBER)) {
    Width = Spd->Ddr3.General.ModuleMemoryBusWidth.Bits.PrimaryBusWidth;
  } else if (MRC_DDR_TYPE_DDR4 == DimmOut->DdrType) {
    Width = Spd->Ddr4.Base.ModuleMemoryBusWidth.Bits.PrimaryBusWidth;
  } else {
    Width = Spd->Lpddr.Base.ModuleMemoryBusWidth.Bits.PrimaryBusWidth;
  }

  switch (Width) {
#if (SUPPORT_PRIWIDTH_8 == SUPPORT)
    case MRC_SPD_PRIMARY_BUS_WIDTH_8:
      DimmOut->PrimaryBusWidth = 8;
      break;
#endif
#if (SUPPORT_PRIWIDTH_16 == SUPPORT)
    case MRC_SPD_PRIMARY_BUS_WIDTH_16:
      DimmOut->PrimaryBusWidth = 16;
      break;
#endif
#if (SUPPORT_PRIWIDTH_32 == SUPPORT)
    case MRC_SPD_PRIMARY_BUS_WIDTH_32:
      DimmOut->PrimaryBusWidth = 32;
      break;
#endif
#if (SUPPORT_PRIWIDTH_64 == SUPPORT)
    case MRC_SPD_PRIMARY_BUS_WIDTH_64:
      DimmOut->PrimaryBusWidth = 64;
      break;
#endif
    default:
      DimmOut->PrimaryBusWidth = 0;
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "%sSDRAM primary bus width, %s%Xh\n", ErrorString, SpdValString, Width);
      return FALSE;
      break;
  }

  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "  Primary bus width: %u\n", DimmOut->PrimaryBusWidth);
  return TRUE;
}

/**
  Determines if the number of Bank are valid.
  Determines if the number of Bank Groups are valid.

    @param[in, out] MrcData - Pointer to MrcData data structure.
    @param[in]      Spd     - Pointer to Spd data structure.
    @param[in, out] DimmOut - Pointer to structure containing DIMM information.

    @retval TRUE on valid value, otherwise FALSE.
**/
static
BOOLEAN
ValidBank (
  IN OUT MrcParameters  *const MrcData,
  IN const MrcSpd       *const Spd,
  IN OUT MrcDimmOut     *const DimmOut
  )
{
  MrcDebug     *Debug;
  UINT8        BankAddress;
  UINT8        BankGroup;
  UINT8        ValidCheck;

  Debug       = &MrcData->Outputs.Debug;
  ValidCheck  = TRUE;

  if ((MRC_DDR_TYPE_DDR3 == DimmOut->DdrType) || (Spd->Ddr3.General.DramDeviceType.Bits.Type == MRC_SPD_LPDDR3_SDRAM_TYPE_NUMBER)) {
    DimmOut->DensityIndex = Spd->Ddr3.General.SdramDensityAndBanks.Bits.Density;
    BankAddress           = Spd->Ddr3.General.SdramDensityAndBanks.Bits.BankAddress;
    BankGroup             = 1;
    if (MRC_DDR_TYPE_LPDDR3 == DimmOut->DdrType) {
      MrcData->Outputs.BinnedLpddrDevices = (Spd->Ddr3.General.SdramDensityAndBanks.Data & 0x80) ? TRUE : FALSE;
    }
    switch (BankAddress) {
#if (SUPPORT_BANK_8 == SUPPORT)
      case MRC_SPD_DDR3_SDRAM_BANK_8:
#endif
#if (SUPPORT_BANK_16 == SUPPORT)
      case MRC_SPD_DDR3_SDRAM_BANK_16:
#endif
#if (SUPPORT_BANK_32 == SUPPORT)
      case MRC_SPD_DDR3_SDRAM_BANK_32:
#endif
#if (SUPPORT_BANK_64 == SUPPORT)
      case MRC_SPD_DDR3_SDRAM_BANK_64:
#endif
#if ((SUPPORT_BANK_8 == SUPPORT) || (SUPPORT_BANK_16 == SUPPORT) || (SUPPORT_BANK_32 == SUPPORT) || (SUPPORT_BANK_64 == SUPPORT))
        DimmOut->Banks      = MRC_BIT3 << BankAddress;
        DimmOut->BankGroups = BankGroup;
        break;
#endif
      default:
        MRC_DEBUG_MSG (
          Debug,
          MSG_LEVEL_ERROR,
          "%sSDRAM number of banks, %s%Xh\n",
          ErrorString,
          SpdValString,
          BankAddress
          );
        ValidCheck = FALSE;
    }
  } else {
    if (MRC_DDR_TYPE_DDR4 == DimmOut->DdrType) {
      DimmOut->DensityIndex = Spd->Ddr4.Base.SdramDensityAndBanks.Bits.Density;
      BankAddress           = Spd->Ddr4.Base.SdramDensityAndBanks.Bits.BankAddress;
      BankGroup             = Spd->Ddr4.Base.SdramDensityAndBanks.Bits.BankGroup;
    } else {
      DimmOut->DensityIndex = Spd->Lpddr.Base.SdramDensityAndBanks.Bits.Density;
      BankAddress           = Spd->Lpddr.Base.SdramDensityAndBanks.Bits.BankAddress;
      BankGroup             = Spd->Lpddr.Base.SdramDensityAndBanks.Bits.BankGroup;
    }

    switch (BankAddress) {
#if (SUPPORT_BANK_4 == SUPPORT)
      case MRC_SPD_DDR4_SDRAM_BANK_4:
#endif
#if (SUPPORT_BANK_8 == SUPPORT)
      case MRC_SPD_DDR4_SDRAM_BANK_8:
#endif
#if ((SUPPORT_BANK_4 == SUPPORT) || (SUPPORT_BANK_8 == SUPPORT))
        DimmOut->Banks      = MRC_BIT2 << BankAddress;
        break;
#endif

      default:
        MRC_DEBUG_MSG (
          Debug,
          MSG_LEVEL_ERROR,
          "%sSDRAM number of banks, %s%Xh\n",
          ErrorString,
          SpdValString,
          BankAddress
          );
        ValidCheck = FALSE;
    }

    if ((MRC_DDR_TYPE_DDR4 == DimmOut->DdrType) && (BankGroup == MRC_SPD_DDR4_SDRAM_BANK_GROUPS_0)) {
      MRC_DEBUG_MSG (
        Debug,
        MSG_LEVEL_ERROR,
        "%sSDRAM number of bank groups, %s%Xh\n",
        ErrorString,
        SpdValString,
        BankGroup
        );
      ValidCheck = FALSE;
    } else {
      DimmOut->BankGroups = MRC_BIT0 << BankGroup;
    }
  }
  MRC_DEBUG_MSG (
    Debug,
    MSG_LEVEL_NOTE,
    (TRUE == ValidCheck) ? "  %u Banks in %u groups\n" : "",
    DimmOut->Banks,
    DimmOut->BankGroups
    );

  if (DimmOut->DensityIndex < (sizeof (SdramCapacityTable) / sizeof (SdramCapacityTable[0]))) {
    MRC_DEBUG_MSG (
      Debug,
      MSG_LEVEL_NOTE,
      "  SDRAM Capacity: %u Mb\n",
      SdramCapacityTable[DimmOut->DensityIndex] * 8
      );
  } else {
    MRC_DEBUG_MSG (
      Debug,
      MSG_LEVEL_NOTE,
      "  ERROR: SDRAM Capacity is reserved value: 0x%02X\n",
      DimmOut->DensityIndex
      );
  }

  return ValidCheck;
}

/**
  Determine if the number of ranks in the DIMM is valid and return the value.

    @param[in, out] MrcData - Pointer to MrcData data structure.
    @param[in]      Spd     - Pointer to Spd data structure.
    @param[in, out] DimmOut - Pointer to structure containing DIMM information.

    @retval TRUE on valid value, otherwise FALSE and the value is set to zero.
**/
static
BOOLEAN
GetRankCount (
  IN OUT MrcParameters   *const MrcData,
  IN const MrcSpd        *const Spd,
  IN OUT MrcDimmOut      *const DimmOut
  )
{
  MrcDebug     *Debug;
  UINT8        RankCount;

  Debug       = &MrcData->Outputs.Debug;

  if ((MRC_DDR_TYPE_DDR3 == DimmOut->DdrType) || (Spd->Ddr3.General.DramDeviceType.Bits.Type == MRC_SPD_LPDDR3_SDRAM_TYPE_NUMBER)) {
    RankCount = Spd->Ddr3.General.ModuleOrganization.Bits.RankCount;
  } else if (MRC_DDR_TYPE_DDR4 == DimmOut->DdrType) {
    RankCount = Spd->Ddr4.Base.ModuleOrganization.Bits.RankCount;
  } else {
    RankCount = Spd->Lpddr.Base.ModuleOrganization.Bits.RankCount;
  }

  DimmOut->RankInDimm = RankCount + 1;
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "  Ranks: %u\n", DimmOut->RankInDimm);

  if (MrcData->Inputs.ForceSingleRank) {
    DimmOut->RankInDimm = 1;
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "  Forcing to Single Rank because ForceSingleRank is 1\n" );
  }

  if (DimmOut->RankInDimm > MAX_RANK_IN_DIMM) {
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "%snumber of ranks, %s%Xh\n", ErrorString, SpdValString, RankCount);
    DimmOut->RankInDimm = 0;
    return FALSE;
  }

  return TRUE;
}

/**
  Calculate the size of the DIMM, in MBytes.

    @param[in, out] MrcData - Pointer to MrcData data structure.
    @param[in]      Spd     - Pointer to Spd data structure.
    @param[in, out] DimmOut - Pointer to structure containing DIMM information.

    @retval TRUE on valid value, otherwise FALSE and the value is set to zero.
**/
static
BOOLEAN
GetDimmSize (
  IN OUT MrcParameters   *const MrcData,
  IN const MrcSpd        *const Spd,
  IN OUT MrcDimmOut      *const DimmOut
  )
{
  UINT32       DimmSize;
  MrcDebug     *Debug;

  Debug = &MrcData->Outputs.Debug;

  if ((DimmOut->SdramWidth > 0) && (DimmOut->DensityIndex < (sizeof (SdramCapacityTable) / sizeof (SdramCapacityTable[0])))) {
    DimmSize = (((SdramCapacityTable[DimmOut->DensityIndex] * DimmOut->PrimaryBusWidth) / DimmOut->SdramWidth) * DimmOut->RankInDimm);
    if ((DimmSize >= DIMMSIZEMIN) && (DimmSize <= DIMMSIZEMAX)) {
      if (MrcData->Outputs.BinnedLpddrDevices) {
        if (DimmOut->DensityIndex != MRC_SPD_SDRAM_DENSITY_8Gb) {
          //
          // Not 6Gb, unsupported
          //
          DimmSize = 0;
        }
      }
      if (DimmSize != 0) {
        DimmOut->DimmCapacity = DimmSize;
        MRC_DEBUG_MSG (
          Debug,
          MSG_LEVEL_NOTE,
          "  DIMM size: %u MByte\n",
          DimmSize
          );
        return TRUE;
      }
    }
    MRC_DEBUG_MSG (
      Debug,
      MSG_LEVEL_ERROR,
      "%sDIMM size: %u MB, valid range %u - %u MB ",
      ErrorString,
      DimmSize,
      DIMMSIZEMIN,
      DIMMSIZEMAX
      );
  }

  MRC_DEBUG_MSG (
    Debug,
    MSG_LEVEL_ERROR,
    "SDRAM capacity %s%Xh\n",
    SpdValString,
    DimmOut->DensityIndex
    );
  DimmOut->DimmCapacity = 0;
  return FALSE;
}

/**
  Obtain ECC support Status for this DIMM.

    @param[in, out] MrcData - Pointer to MrcData data structure.
    @param[in]      Spd     - Pointer to Spd data structure.
    @param[in, out] DimmOut - Pointer to structure containing DIMM information.

    @retval Returns TRUE.
**/
static
BOOLEAN
ValidEccSupport (
  IN OUT MrcParameters   *const MrcData,
  IN const MrcSpd        *const Spd,
  IN OUT MrcDimmOut      *const DimmOut
  )
{
#if (SUPPORT_ECC == SUPPORT)
  UINT8        BusWidthExtension;
#endif // SUPPORT_ECC
  MrcDebug        *Debug;

  Debug = &MrcData->Outputs.Debug;

#if (SUPPORT_ECC == SUPPORT)
  if ((MRC_DDR_TYPE_DDR3 == DimmOut->DdrType) || (Spd->Ddr3.General.DramDeviceType.Bits.Type == MRC_SPD_LPDDR3_SDRAM_TYPE_NUMBER)) {
    BusWidthExtension = Spd->Ddr3.General.ModuleMemoryBusWidth.Bits.BusWidthExtension;
  } else if (MRC_DDR_TYPE_DDR4 == DimmOut->DdrType) {
    BusWidthExtension = Spd->Ddr4.Base.ModuleMemoryBusWidth.Bits.BusWidthExtension;
  } else {
    BusWidthExtension = Spd->Lpddr.Base.ModuleMemoryBusWidth.Bits.BusWidthExtension;
  }
  if (MRC_SPD_BUS_WIDTH_EXTENSION_8 == BusWidthExtension) {
    DimmOut->EccSupport = TRUE;
  } else
#endif // SUPPORT_ECC
  {
    DimmOut->EccSupport = FALSE;
  }

  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "  ECC is %ssupported\n", (DimmOut->EccSupport == FALSE) ? "not " : "");
  return TRUE;
}

/**
  Obtain address mirroring Status for this DIMM.

    @param[in, out] MrcData - Pointer to MrcData data structure.
    @param[in]      Spd     - Pointer to Spd data structure.
    @param[in, out] DimmOut - Pointer to structure containing DIMM information.

    @retval Returns TRUE.
**/
static
BOOLEAN
GetAddressMirror (
  IN OUT MrcParameters   *const MrcData,
  IN const MrcSpd        *const Spd,
  IN OUT MrcDimmOut      *const DimmOut
  )
{
  MrcDebug  *Debug;
  UINT8  MappingRank1;

  Debug = &MrcData->Outputs.Debug;

  if ((MRC_DDR_TYPE_DDR3 == DimmOut->DdrType) || (Spd->Ddr3.General.DramDeviceType.Bits.Type == MRC_SPD_LPDDR3_SDRAM_TYPE_NUMBER)) {
    MappingRank1 = Spd->Ddr3.Module.Unbuffered.AddressMappingEdgeConn.Bits.MappingRank1;
  } else if (MRC_DDR_TYPE_DDR4 == DimmOut->DdrType) {
    MappingRank1 = Spd->Ddr4.Module.Unbuffered.AddressMappingEdgeConn.Bits.MappingRank1;
  } else {
    MappingRank1 = 0;
  }

  DimmOut->AddressMirrored = (MappingRank1 != 0) ? TRUE : FALSE;
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "  DIMM has %saddress mirroring\n", (DimmOut->AddressMirrored == FALSE) ? "no " : "");
  return TRUE;
}

/**
  Obtain thermal and refresh support for this DIMM.

    @param[in, out] MrcData - Pointer to MrcData data structure.
    @param[in]      Spd     - Pointer to Spd data structure.
    @param[in, out] DimmOut - Pointer to structure containing DIMM information.

    @retval Returns TRUE.
**/
static
BOOLEAN
GetThermalRefreshSupport (
  IN OUT MrcParameters   *const MrcData,
  IN const MrcSpd        *const Spd,
  IN OUT MrcDimmOut      *const DimmOut
  )
{
  MrcDebug        *Debug;
  const MrcInput  *Inputs;

  Inputs = &MrcData->Inputs;
  Debug  = &MrcData->Outputs.Debug;

  if ((MRC_DDR_TYPE_DDR3 == DimmOut->DdrType) || (Spd->Ddr3.General.DramDeviceType.Bits.Type == MRC_SPD_LPDDR3_SDRAM_TYPE_NUMBER)) {
    DimmOut->PartialSelfRefresh    = Spd->Ddr3.General.ThermalAndRefreshOptions.Bits.PartialArraySelfRefresh;
    DimmOut->OnDieThermalSensor    = Spd->Ddr3.General.ThermalAndRefreshOptions.Bits.OnDieThermalSensor;
    DimmOut->AutoSelfRefresh       = Spd->Ddr3.General.ThermalAndRefreshOptions.Bits.AutoSelfRefresh && Inputs->AutoSelfRefreshSupport;
    DimmOut->ExtendedTemperRefresh = Spd->Ddr3.General.ThermalAndRefreshOptions.Bits.ExtendedTemperatureRefreshRate;
    DimmOut->ExtendedTemperRange   = Spd->Ddr3.General.ThermalAndRefreshOptions.Bits.ExtendedTemperatureRange;
  } else {
    DimmOut->PartialSelfRefresh    = 0;
    DimmOut->OnDieThermalSensor    = (MRC_DDR_TYPE_DDR4 == DimmOut->DdrType) ? 0 : Spd->Lpddr.Base.ModuleThermalSensor.Bits.ThermalSensorPresence;
    DimmOut->AutoSelfRefresh       = 0;
    DimmOut->ExtendedTemperRefresh = 0;
    DimmOut->ExtendedTemperRange   = 0;
  }

  DimmOut->SelfRefreshTemp = ((!DimmOut->AutoSelfRefresh) && (DimmOut->ExtendedTemperRange) && (Inputs->ExtTemperatureSupport)) ? TRUE : FALSE;

  MRC_DEBUG_MSG (Debug,
    MSG_LEVEL_NOTE,
    "  Partial Array Self Refresh%s\n",
    DimmOut->PartialSelfRefresh ? IsSupString : NotSupString);
  MRC_DEBUG_MSG (Debug,
    MSG_LEVEL_NOTE,
    "  On-Die Thermal Sensor Readout%s\n",
    DimmOut->OnDieThermalSensor ? IsSupString : NotSupString);
  MRC_DEBUG_MSG (Debug,
    MSG_LEVEL_NOTE,
    "  Auto Self Refresh%s\n",
    DimmOut->AutoSelfRefresh ? IsSupString : NotSupString);
  MRC_DEBUG_MSG (Debug,
    MSG_LEVEL_NOTE,
    "  Extended Temperature Refresh Rate%s\n",
    DimmOut->ExtendedTemperRefresh ? IsSupString : NotSupString);
  MRC_DEBUG_MSG (Debug,
    MSG_LEVEL_NOTE,
    "  Extended Temperature Range%s\n",
    DimmOut->ExtendedTemperRange ? IsSupString : NotSupString);
  return TRUE;
}

/**
  Obtain Pseudo TRR support for this DIMM.

    @param[in, out] MrcData - Pointer to MrcData data structure.
    @param[in]      Spd     - Pointer to Spd data structure.
    @param[in, out] DimmOut - Pointer to structure containing DIMM information.

    @retval Returns TRUE.
**/
static
BOOLEAN
GetpTRRsupport (
  IN OUT MrcParameters   *const MrcData,
  IN const MrcSpd        *const Spd,
  IN OUT MrcDimmOut      *const DimmOut
  )
{
  MrcDebug        *Debug;
  const MrcInput  *Inputs;
  MrcOutput       *Outputs;
  UINT32          tMAC;

  Inputs  = &MrcData->Inputs;
  Outputs = &MrcData->Outputs;
  Debug   = &Outputs->Debug;

  if ((MRC_DDR_TYPE_DDR3 == DimmOut->DdrType) || (Spd->Ddr3.General.DramDeviceType.Bits.Type == MRC_SPD_LPDDR3_SDRAM_TYPE_NUMBER)) {
    tMAC = Spd->Ddr3.General.pTRRsupport.Bits.tMACencoding;
  } else if (MRC_DDR_TYPE_DDR4 == DimmOut->DdrType) {
    tMAC = Spd->Ddr4.Base.pTRRsupport.Bits.tMACencoding;
  } else {
    tMAC = Spd->Lpddr.Base.pTRRsupport.Bits.tMACencoding;
  }

  switch (tMAC) {
    case MRC_TMAC_UNTESTED:
      DimmOut->tMAC = MRC_TMAC_UNTESTED;
      break;
    case MRC_TMAC_200K:
      DimmOut->tMAC = 2;
      break;
    case MRC_TMAC_300K:
      DimmOut->tMAC = 3;
      break;
    case MRC_TMAC_400K:
      DimmOut->tMAC = 4;
      break;
    case MRC_TMAC_500K:
      DimmOut->tMAC = 5;
      break;
    case MRC_TMAC_600K:
      DimmOut->tMAC = 6;
      break;
    case MRC_TMAC_700K:
      DimmOut->tMAC = 7;
      break;
    case MRC_TMAC_UNLIMITED:
      DimmOut->tMAC = MRC_TMAC_UNLIMITED;
      break;
    default:
      DimmOut->tMAC = 0;
      MRC_DEBUG_MSG (
        Debug,
        MSG_LEVEL_ERROR,
        "%stMAC value, %s%Xh\n",
        ErrorString,
        SpdValString,
        tMAC
        );
      return FALSE;
  }

  if (DimmOut->tMAC == MRC_TMAC_UNTESTED) {
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "  tMAC is untested\n");
  } else if (DimmOut->tMAC == MRC_TMAC_UNLIMITED) {
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "  tMAC is unlimited\n");
  } else {
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "  tMAC: %d00K\n", DimmOut->tMAC);
  }

  return TRUE;
}

/**
  Obtain which JEDEC reference design raw card was used as the basis for the DIMM assembly.

    @param[in, out] MrcData - Pointer to MrcData data structure.
    @param[in]      Spd     - Pointer to Spd data structure.
    @param[in, out] DimmOut - Pointer to structure containing DIMM information.

    @retval Returns TRUE.
**/
static
BOOLEAN
GetReferenceRawCardSupport (
  IN OUT MrcParameters   *const MrcData,
  IN const MrcSpd        *const Spd,
  IN OUT MrcDimmOut      *const DimmOut
  )
{
  MrcOutput *Outputs;
  MrcDebug  *Debug;

  Outputs = &MrcData->Outputs;
  Debug   = &Outputs->Debug;

  if ((MRC_DDR_TYPE_DDR3 == DimmOut->DdrType) || (Spd->Ddr3.General.DramDeviceType.Bits.Type == MRC_SPD_LPDDR3_SDRAM_TYPE_NUMBER)) {
    DimmOut->ReferenceRawCard = (Spd->Ddr3.Module.Unbuffered.ReferenceRawCardUsed.Bits.Extension << MRC_SPD_REF_RAW_CARD_SIZE) |
      Spd->Ddr3.Module.Unbuffered.ReferenceRawCardUsed.Bits.Card;
    DimmOut->ReferenceRawCardRevision = Spd->Ddr3.Module.Unbuffered.ReferenceRawCardUsed.Bits.Revision;
  } else if (MRC_DDR_TYPE_DDR4 == DimmOut->DdrType) {
    DimmOut->ReferenceRawCard = (Spd->Ddr4.Module.Unbuffered.ReferenceRawCardUsed.Bits.Extension << MRC_SPD_REF_RAW_CARD_SIZE) |
      Spd->Ddr4.Module.Unbuffered.ReferenceRawCardUsed.Bits.Card;
    DimmOut->ReferenceRawCardRevision = Spd->Ddr4.Module.Unbuffered.ReferenceRawCardUsed.Bits.Revision;
  } else {
    DimmOut->ReferenceRawCard = (Spd->Lpddr.Module.LpDimm.ReferenceRawCardUsed.Bits.Extension << MRC_SPD_REF_RAW_CARD_SIZE) |
      Spd->Lpddr.Module.LpDimm.ReferenceRawCardUsed.Bits.Card;
    DimmOut->ReferenceRawCardRevision = Spd->Lpddr.Module.LpDimm.ReferenceRawCardUsed.Bits.Revision;
  }

  MRC_DEBUG_MSG (
    Debug,
    MSG_LEVEL_NOTE,
    "  Reference raw card: %u '%s'\n",
    DimmOut->ReferenceRawCard,
    (DimmOut->ReferenceRawCard < (sizeof (RrcString) / sizeof (RrcString[0]))) ?
    RrcString[DimmOut->ReferenceRawCard] : UnknownString
    );
  return TRUE;
}

/**
  Calculate the CRC16 of the provided SPD data. CRC16 formula is the same
    one that is used for calculating the CRC16 stored at SPD bytes 126-127.
    This can be used to detect DIMM change.

    @param[in]  Buffer - Pointer to the start of the data.
    @param[in]  Size   - Amount of data in the buffer, in bytes.
    @param[out] Crc    - Pointer to location to write the calculated CRC16 value.

    @retval Returns TRUE.
**/
BOOLEAN
GetDimmCrc (
  IN  const UINT8 *const Buffer,
  IN  const UINT32       Size,
  OUT UINT16 *const      Crc
  )
{
  const UINT8 *Data;
  UINT32      Value;
  UINT32      Byte;
  UINT8       Bit;

  Data  = Buffer;
  Value = CRC_SEED;
  for (Byte = 0; Byte < Size; Byte++) {
    Value ^= (UINT32) *Data++ << 8;
    for (Bit = 0; Bit < 8; Bit++) {
      Value = (Value & MRC_BIT15) ? (Value << 1) ^ CRC_XOR_MASK : Value << 1;
    }
  }

  *Crc = (UINT16) Value;
  return TRUE;
}

/**
  Calculate the medium and fine timebases, using integer math.

    @param[in, out] MrcData - Pointer to MrcData data structure.

    @retval TRUE if medium timebase is valid, otherwise FALSE.
**/
static
BOOLEAN
GetChannelDimmTimeBase (
  IN OUT MrcParameters  *const MrcData
  )
{
  const MrcInput            *Inputs;
  const MrcControllerIn     *ControllerIn;
  const MrcChannelIn        *ChannelIn;
  const MrcDimmIn           *DimmIn;
  const MrcSpd              *Spd;
  MrcDebug                  *Debug;
  MrcOutput                 *Outputs;
  MrcControllerOut          *ControllerOut;
  MrcChannelOut             *ChannelOut;
  MrcDimmOut                *DimmOut;
  MrcTimeBase               *TimeBase;
  MrcProfile                Profile;
  UINT8                     Controller;
  UINT8                     Channel;
  UINT8                     Dimm;
  UINT8                     SpdMtbDividend;
  UINT8                     SpdMtbDivisor;
  UINT8                     SpdFtbDividend;
  UINT8                     SpdFtbDivisor;
  const SPD_MEDIUM_TIMEBASE *XmpMtb;
  UINT32                    Index;

  Inputs  = &MrcData->Inputs;
  Outputs = &MrcData->Outputs;
  Debug   = &Outputs->Debug;

  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "  %s:\n  %s\n", TimeBaseString, HeaderString);

  //
  // Find the smallest timing value for all the given DIMMs, for all the profiles.
  //
  for (Profile = STD_PROFILE; Profile < MAX_PROFILE; Profile++) {
    if (!(MrcXmpTimingProfileEnabled (MrcData, Profile))) {
      continue;
    }
    for (Controller = 0; Controller < MAX_CONTROLLERS; Controller++) {
      ControllerIn  = &Inputs->Controller[Controller];
      ControllerOut = &Outputs->Controller[Controller];
      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        ChannelIn   = &ControllerIn->Channel[Channel];
        ChannelOut  = &ControllerOut->Channel[Channel];
        for (Dimm = 0; Dimm < MAX_DIMMS_IN_CHANNEL; Dimm++) {
          DimmIn  = &ChannelIn->Dimm[Dimm];
          DimmOut = &ChannelOut->Dimm[Dimm];
          if (DIMM_PRESENT == DimmOut->Status) {
            Spd      = &DimmIn->Spd.Data;
            TimeBase = &ChannelOut->TimeBase[Dimm][Profile];
            switch (Profile) {
              case XMP_PROFILE1:
              case XMP_PROFILE2:
                if (MrcDimmXmpProfileSupported (DimmOut, Profile)) {
                  Index = Profile - XMP_PROFILE1;
                  if (MRC_DDR_TYPE_DDR3 == DimmOut->DdrType) {
                    SpdFtbDividend = Spd->Ddr3.Xmp.Header.FineTimeBase.Bits.Dividend;
                    SpdFtbDivisor  = Spd->Ddr3.Xmp.Header.FineTimeBase.Bits.Divisor;
                    XmpMtb         = &Spd->Ddr3.Xmp.Header.MediumTimeBase[Index];
                    SpdMtbDividend = XmpMtb->Dividend.Bits.Dividend;
                    SpdMtbDivisor  = XmpMtb->Divisor.Bits.Divisor;
                    TimeBase->Ftb  = ((DimmOut->XmpRevision == 0x12) || (SpdFtbDivisor == 0)) ? 0 : (SpdFtbDividend * MRC_FREQUENCY_FTB_OFFSET) / SpdFtbDivisor;
                    TimeBase->Mtb  = (SpdMtbDivisor == 0) ? 0 : (SpdMtbDividend * MRC_FREQUENCY_MTB_OFFSET) / SpdMtbDivisor;
                  } else {
                    switch (Spd->Ddr4.Base.Timebase.Bits.Medium) {
                      case 0:
                        TimeBase->Mtb = 125000;
                        break;
                      default:
                        TimeBase->Mtb = 0;
                        break;
                    }
                    switch (Spd->Ddr4.Base.Timebase.Bits.Fine) {
                      case 0:
                        TimeBase->Ftb = 1000;
                        break;
                      default:
                        TimeBase->Ftb = 0;
                        break;
                    }
                  }
                } else {
                  TimeBase->Ftb = 0;
                  TimeBase->Mtb = 0;
                }
                break;
              case USER_PROFILE:
              case STD_PROFILE:
              default:
                if ((MRC_DDR_TYPE_DDR3 == DimmOut->DdrType) || (Spd->Ddr3.General.DramDeviceType.Bits.Type == MRC_SPD_LPDDR3_SDRAM_TYPE_NUMBER)) {
                  SpdFtbDividend  = Spd->Ddr3.General.FineTimebase.Bits.Dividend;
                  SpdFtbDivisor   = Spd->Ddr3.General.FineTimebase.Bits.Divisor;
                  SpdMtbDividend  = Spd->Ddr3.General.MediumTimebase.Dividend.Bits.Dividend;
                  SpdMtbDivisor   = Spd->Ddr3.General.MediumTimebase.Divisor.Bits.Divisor;
                  TimeBase->Ftb = (SpdFtbDivisor == 0) ? 0 : (SpdFtbDividend * MRC_FREQUENCY_FTB_OFFSET) / SpdFtbDivisor;
                  TimeBase->Mtb = (SpdMtbDivisor == 0) ? 0 : (SpdMtbDividend * MRC_FREQUENCY_MTB_OFFSET) / SpdMtbDivisor;
                } else if (MRC_DDR_TYPE_DDR4 == DimmOut->DdrType) {
                  switch (Spd->Ddr4.Base.Timebase.Bits.Medium) {
                    case 0:
                      TimeBase->Mtb = 125000;
                      break;
                    default:
                      TimeBase->Mtb = 0;
                      break;
                  }
                  switch (Spd->Ddr4.Base.Timebase.Bits.Fine) {
                    case 0:
                      TimeBase->Ftb = 1000;
                      break;
                    default:
                      TimeBase->Ftb = 0;
                      break;
                  }
                } else {
                  switch (Spd->Lpddr.Base.Timebase.Bits.Medium) {
                    case 0:
                      TimeBase->Mtb = 125000;
                      break;
                    default:
                      TimeBase->Mtb = 0;
                      break;
                  }
                  switch (Spd->Lpddr.Base.Timebase.Bits.Fine) {
                    case 0:
                      TimeBase->Ftb = 1000;
                      break;
                    default:
                      TimeBase->Ftb = 0;
                      break;
                  }
                }
                break;
            } //switch

            MRC_DEBUG_MSG (
              Debug,
              MSG_LEVEL_NOTE,
              "  % 7u % 10u % 8u % 5u % 6u %u\n",
              Profile,
              Controller,
              Channel,
              Dimm,
              TimeBase->Mtb,
              TimeBase->Ftb
              );
          } //DimmOut->Status
        } //Dimm
      } //Channel
    } //Controller
  } //Profile

  return TRUE;
}

/**
  Calculate the SDRAM minimum cycle time (tCKmin) that this DIMM supports.
    Then use the lookup table to obtain the frequency closest to the clock multiple.

    @param[in, out] MrcData - Pointer to MrcData data structure.

    @retval TRUE if the DIMM frequency is supported, otherwise FALSE and the frequency is set to fInvalid.
**/
static
BOOLEAN
GetChannelDimmtCK (
  IN OUT MrcParameters  *const MrcData
  )
{
  MrcInput              *Inputs;
  const MrcControllerIn *ControllerIn;
  const MrcChannelIn    *ChannelIn;
  const MrcDimmIn       *DimmIn;
  const MrcSpd          *Spd;
  MrcDebug              *Debug;
  MrcOutput             *Outputs;
  MrcControllerOut      *ControllerOut;
  MrcChannelOut         *ChannelOut;
  MrcDimmOut            *DimmOut;
  MrcTimeBase           *TimeBase;
  MrcProfile            Profile;
  UINT8                 Controller;
  UINT8                 Channel;
  UINT8                 Dimm;
  INT32                 MediumTimebase;
  INT32                 FineTimebase;
  INT32                 tCKminMtb;
  INT32                 tCKminFine;
  UINT32                Actual[MAX_PROFILE];
  UINT32                Calculated;
  UINT32                tCKmin;
  UINT32                tCKmin100;
  INT32                 tCKminIndex;
  INT32                 tCKminIndex100;
  BOOLEAN               OddRatio;
  BOOLEAN               OddRatio100;
  UINT32                DefaultXmptCK[XMP_PROFILE1];
  UINT8                 LogicalXmpProfile;
  BOOLEAN               FirstProfile;

  const SPD_EXTREME_MEMORY_PROFILE_DATA      *Data1;
  const SPD_EXTREME_MEMORY_PROFILE_DATA_2_0  *Data2;

  Inputs  = &MrcData->Inputs;
  Outputs = &MrcData->Outputs;
  Debug   = &Outputs->Debug;
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "  %s:\n  %s (fs)\n", tCKString, HeaderString);

  //
  // Find the smallest timing value for all the given DIMMs, for all the profiles.
  //
  for (Profile = STD_PROFILE; Profile < MAX_PROFILE; Profile++) {
    if (!(MrcXmpTimingProfileEnabled (MrcData, Profile))) {
      continue;
    }
    FirstProfile    = TRUE;
    Actual[Profile] = fNoInit;
    if (Profile < XMP_PROFILE1) {
      // Initialize tCK value for the XMP profiles.
      // Use Profile as the logical array indecies for XMP1 and XMP2.
      DefaultXmptCK[Profile] = fNoInit;
    }
    for (Controller = 0; Controller < MAX_CONTROLLERS; Controller++) {
      ControllerIn  = &Inputs->Controller[Controller];
      ControllerOut = &Outputs->Controller[Controller];
      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        ChannelIn   = &ControllerIn->Channel[Channel];
        ChannelOut  = &ControllerOut->Channel[Channel];
        for (Dimm = 0; Dimm < MAX_DIMMS_IN_CHANNEL; Dimm++) {
          DimmIn  = &ChannelIn->Dimm[Dimm];
          DimmOut = &ChannelOut->Dimm[Dimm];
          if (DIMM_PRESENT == DimmOut->Status) {
            Spd            = &DimmIn->Spd.Data;
            TimeBase       = &ChannelOut->TimeBase[Dimm][Profile];
            MediumTimebase = TimeBase->Mtb;
            FineTimebase   = TimeBase->Ftb;
            Calculated     = 0;
            switch (Profile) {
              case XMP_PROFILE1:
              case XMP_PROFILE2:
                LogicalXmpProfile = (UINT8) Profile - XMP_PROFILE1;
                if (MrcDimmXmpProfileSupported (DimmOut, Profile)) {
                  if (MRC_DDR_TYPE_DDR3 == DimmOut->DdrType) {
                    Data1 = &Spd->Ddr3.Xmp.Data[LogicalXmpProfile];
                    tCKminMtb  = Data1->tCKmin.Bits.tCKmin;
                    tCKminFine = Data1->tCKminFine.Bits.tCKminFine;
                  } else {
                    Data2 = &Spd->Ddr4.EndUser.Xmp.Data[LogicalXmpProfile];
                    tCKminMtb  = Data2->tCKAVGmin.Bits.tCKmin;
                    tCKminFine = Data2->tCKAVGminFine.Bits.tCKminFine;
                  }
                  Calculated = (MediumTimebase * tCKminMtb) + (FineTimebase * tCKminFine);
                  // Save the Default tCK value for XMP profile
                  DefaultXmptCK[LogicalXmpProfile] = Calculated;
                  if (Inputs->MemoryProfile == Profile) {
                    Calculated = MAX (Outputs->MemoryClockMax, Calculated);
                  }
                } else {
                  DefaultXmptCK[LogicalXmpProfile] = 0;
                  Calculated = 0;
                }
                if (FirstProfile) {
                  Outputs->DefaultXmptCK[LogicalXmpProfile] = DefaultXmptCK[LogicalXmpProfile];
                  FirstProfile = FALSE;
                } else if (Outputs->DefaultXmptCK[LogicalXmpProfile] != DefaultXmptCK[LogicalXmpProfile]) {
                  Outputs->XmpProfileEnable = 0;
                  MRC_DEBUG_MSG (Debug, MSG_LEVEL_WARNING, "  %s\n", XmpDisableString);
                }
                break;
              case USER_PROFILE:
                if (Inputs->Ratio > 0) {
                  Calculated  = MrcRatioToClock (MrcData, Inputs->Ratio, Outputs->RefClk, Inputs->BClkFrequency);
                  Calculated = MAX (Outputs->MemoryClockMax, Calculated);
                  break;
                } else {
                  // In AUTO mode, so no break.
                }
              case STD_PROFILE:
              default:
                if ((MRC_DDR_TYPE_DDR3 == DimmOut->DdrType) || (Spd->Ddr3.General.DramDeviceType.Bits.Type == MRC_SPD_LPDDR3_SDRAM_TYPE_NUMBER)) {
                  tCKminMtb   = Spd->Ddr3.General.tCKmin.Bits.tCKmin;
                  tCKminFine  = Spd->Ddr3.General.tCKminFine.Bits.tCKminFine;
                } else if (MRC_DDR_TYPE_DDR4 == DimmOut->DdrType) {
                  tCKminMtb   = Spd->Ddr4.Base.tCKmin.Bits.tCKmin;
                  tCKminFine  = Spd->Ddr4.Base.tCKminFine.Bits.tCKminFine;
                } else {
                  tCKminMtb   = Spd->Lpddr.Base.tCKmin.Bits.tCKmin;
                  tCKminFine  = Spd->Lpddr.Base.tCKminFine.Bits.tCKminFine;
                }
                Calculated = (MediumTimebase * tCKminMtb) + (FineTimebase * tCKminFine);
                Calculated = MAX (Outputs->MemoryClockMax, Calculated);
                break;
            } //switch
            Actual[Profile] = MAX (Actual[Profile], Calculated);


            MRC_DEBUG_MSG (
              Debug,
              MSG_LEVEL_NOTE,
              "  % 7u % 10u % 8u % 5u % 6u\n",
              Profile,
              Controller,
              Channel,
              Dimm,
              Calculated
              );
          } //DimmOut->Status
        } //Dimm
      } //Channel
    } //Controller
  } //Profile

  //
  // Set the best case timing for all controllers/channels/dimms, for each profile.
  //
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "    %s%u:", BestCaseString, MAX_PROFILE - 1);
  for (Profile = STD_PROFILE; Profile < MAX_PROFILE; Profile++) {
    if (!(MrcXmpTimingProfileEnabled (MrcData, Profile))) {
      continue;
    }

    // Find the closest possible frequency using valid ratio / refclk combinations, and update tCK
    ConvertClock2Freq (MrcData, (Profile != STD_PROFILE) ? Outputs->RefClk : MRC_REF_CLOCK_133, Actual[Profile], &tCKminIndex, &tCKmin, &OddRatio);
    if ((Profile >= XMP_PROFILE1) && (Outputs->RefClk == MRC_REF_CLOCK_133) && (Outputs->Capable100)) {
      ConvertClock2Freq (MrcData, MRC_REF_CLOCK_100, Actual[Profile], &tCKminIndex100, &tCKmin100, &OddRatio100);
      if (tCKminIndex100 > tCKminIndex) {
        tCKminIndex = tCKminIndex100;
        tCKmin      = tCKmin100;
        OddRatio    = OddRatio100;
        if (Inputs->MemoryProfile == Profile) {
          Outputs->RefClk = MRC_REF_CLOCK_100;
          MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n  Profile%u is RefClk 100 capable, switching to RefClk 100\n", Profile);
        }
      }
    }
    if ((Profile != USER_PROFILE) && (Inputs->MemoryProfile == Profile) && (Outputs->OddRatioMode != OddRatio)) {
      Outputs->OddRatioMode = OddRatio;
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n  Profile%u: switching to OddRatio = %u\n", Profile, OddRatio);
    }

    Actual[Profile] = tCKmin;  // Updated value according to possible ratio / refclk combinations
    for (Controller = 0; Controller < MAX_CONTROLLERS; Controller++) {
      ControllerOut = &Outputs->Controller[Controller];
      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        ChannelOut = &ControllerOut->Channel[Channel];
        for (Dimm = 0; Dimm < MAX_DIMMS_IN_CHANNEL; Dimm++) {
          DimmOut = &ChannelOut->Dimm[Dimm];
          DimmOut->Timing[Profile].tCK    = tCKmin;
          ChannelOut->Timing[Profile].tCK = tCKmin;
        }
      }
    }
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, " %u", tCKmin);
  }
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n");

  Outputs->MemoryClock = Actual[Inputs->MemoryProfile];

  return TRUE;
}

/**
  Determine if the calculated CAS Latency is within the supported CAS Latency Mask

    @param[in] tAA         - the calculated CAS Latency in tCKs.
    @param[in] DdrType     - the SDRAM type number.
    @param[in] tCLMask     - the supported CAS Latency mask.
    @param[in] tCLLimitMin - the minimum supported CAS Latency

    @retval TRUE if the CAS latency has been found in supported mask, otherwise FALSE.
**/
static
BOOLEAN
ValidtCL (
  IN const UINT32     tAA,
  IN const UINT8      DeviceType,
  IN const UINT32     tCLMask,
  IN const UINT32     tCLLimitMin
  )
{
  BOOLEAN Valid;
  Valid = FALSE;

  switch (DeviceType) {
    case MRC_SPD_DDR3_SDRAM_TYPE_NUMBER:
    case MRC_SPD_DDR4_SDRAM_TYPE_NUMBER:
    case MRC_SPD_LPDDR3_SDRAM_TYPE_NUMBER:
    default:
      Valid = ((tCLMask >> (tAA - tCLLimitMin)) & MRC_BIT0);
      break;

    case MRC_JEDEC_LPDDR3_SDRAM_TYPE_NUMBER:
      if (tAA >= 12) {
        Valid = ((tCLMask >> (tAA / 2)) & MRC_BIT0);
      } else if (tAA >= 8) {
        Valid = ((tCLMask >> (tAA - 6)) & MRC_BIT0);
      } else if ((tAA == 6) || (tAA == 3)) {
        Valid = ((tCLMask >> ((tAA / 3) - 1)) & MRC_BIT0);
      }
      break;
  }
  return Valid;
}

/**
  Calculate the Minimum CAS Latency Time (tAAmin) for the given DIMMs.
      Step 1: Determine the common set of supported CAS Latency values for all modules
              on the memory channel using the CAS Latencies Supported in SPD.
      Step 2: Determine tAAmin(all) which is the largest tAAmin value for all modules on the memory channel.
      Step 3: Determine tCKmin(all) which is the largest tCKmin value for all
              the modules on the memory channel (Done in function GetChannelDimmtCK).
      Step 4: For a proposed tCK value between tCKmin and tCKmax, determine the desired CAS Latency.
              If tCKproposed is not a standard JEDEC value then tCKproposed must be adjusted to the
              next lower standard tCK value for calculating CLdesired.
      Step 5: Chose an actual CAS Latency that is greater than or equal to CLdesired and is
              supported by all modules on the memory channel as determined in step 1. If no such value exists,
              choose a higher tCKproposed value and repeat steps 4 and 5 until a solution is found.
      Step 6: Once the calculation of CLactual is completed, the BIOS must also verify that this CAS
              Latency value does not exceed tAAmax, which is 20 ns for all DDR3 speed grades.
              If not, choose a lower CL value and repeat steps 5 and 6 until a solution is found.

    @param[in, out] MrcData - Pointer to MrcData data structure.

    @retval TRUE if the CAS latency has been calculated, otherwise FALSE and the returned value is set to zero.
**/
static
BOOLEAN
GetChannelDimmtAA (
  IN OUT MrcParameters  *const MrcData
  )
{
  const MrcInput        *Inputs;
  const MrcControllerIn *ControllerIn;
  const MrcChannelIn    *ChannelIn;
  const MrcDimmIn       *DimmIn;
  const MrcSpd          *Spd;
  MrcDebug              *Debug;
  MrcOutput             *Outputs;
  MrcControllerOut      *ControllerOut;
  MrcChannelOut         *ChannelOut;
  MrcDimmOut            *DimmOut;
  MrcProfile            Profile;
  BOOLEAN               Found[MAX_PROFILE];
  BOOLEAN               UserProfile;
  BOOLEAN               tCLOverride;
  BOOLEAN               Status;
  INT32                 MediumTimeBase;
  INT32                 FineTimeBase;
  INT32                 tCKminIndex;
  INT32                 tCKmin100;
  INT32                 tCKminIndexSave;
  INT32                 TimingFTB;
  UINT32                TimingMTB;
  UINT32                tCKmin;
  UINT32                CommonCasMask[MAX_PROFILE];
  UINT32                CasMask;
  UINT32                Actual[MAX_PROFILE];
  UINT32                Calculated;
  UINT32                tCLLimitMin;
  UINT32                tCLLimitMax;
  UINT32                tAAValue;
  UINT8                 Controller;
  UINT8                 Channel;
  UINT8                 Dimm;
  UINT8                 DeviceType;
  BOOLEAN               FirstProfile;

  const SPD_EXTREME_MEMORY_PROFILE_DATA      *Data1;
  const SPD_EXTREME_MEMORY_PROFILE_DATA_2_0  *Data2;
  UINT32                                     Index;

  Inputs         = &MrcData->Inputs;
  Outputs        = &MrcData->Outputs;
  Debug          = &Outputs->Debug;
  tCKmin         = 0;
  Calculated     = 0;
  Status         = FALSE;
  tCLOverride    = FALSE;
  MediumTimeBase = 0;
  FineTimeBase   = 0;
  TimingMTB      = 0;
  TimingFTB      = 0;
  DeviceType     = MRC_SPD_DDR3_SDRAM_TYPE_NUMBER;

  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "  %s:\n  %s tCL Mask\n", tAAString, HeaderString);

  for (Profile = STD_PROFILE; Profile < MAX_PROFILE; Profile++) {
    if (!(MrcXmpTimingProfileEnabled (MrcData, Profile))) {
      continue;
    }
    FirstProfile           = TRUE;
    tAAValue               = 0;
    UserProfile            = (Profile == USER_PROFILE) && (Inputs->MemoryProfile == USER_PROFILE);
    CommonCasMask[Profile] = ~(0UL);
    Actual[Profile]        = 0;
    tCLLimitMin            = 4;
    tCLLimitMax            = 18;
    for (Controller = 0; Controller < MAX_CONTROLLERS; Controller++) {
      ControllerIn  = &Inputs->Controller[Controller];
      ControllerOut = &Outputs->Controller[Controller];
      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        ChannelIn   = &ControllerIn->Channel[Channel];
        ChannelOut  = &ControllerOut->Channel[Channel];
        for (Dimm = 0; Dimm < MAX_DIMMS_IN_CHANNEL; Dimm++) {
          DimmIn  = &ChannelIn->Dimm[Dimm];
          DimmOut = &ChannelOut->Dimm[Dimm];
          if (DIMM_PRESENT == DimmOut->Status) {
            Spd            = &DimmIn->Spd.Data;
            tCKmin         = ChannelOut->Dimm[Dimm].Timing[Profile].tCK;
            MediumTimeBase = ChannelOut->TimeBase[Dimm][Profile].Mtb;
            FineTimeBase   = ChannelOut->TimeBase[Dimm][Profile].Ftb;
            CasMask        = 0;
            DeviceType     = Spd->Ddr3.General.DramDeviceType.Bits.Type;
            switch (Profile) {
              case XMP_PROFILE1:
              case XMP_PROFILE2:
                if (MrcDimmXmpProfileSupported (DimmOut, Profile)) {
                  Index = Profile - XMP_PROFILE1;
                  if (MRC_DDR_TYPE_DDR3 == DimmOut->DdrType) {
                    Data1       = &Spd->Ddr3.Xmp.Data[Index];
                    tCLLimitMin = 4;
                    tCLLimitMax = 18;
                    TimingMTB   = Data1->tAAmin.Bits.tAAmin;
                    TimingFTB   = Data1->tAAminFine.Bits.tAAminFine;
                    CasMask     = Data1->CasLatencies.Data & MRC_SPD_CL_SUPPORTED_MASK;
                  } else {
                    Data2       = &Spd->Ddr4.EndUser.Xmp.Data[Index];
                    tCLLimitMin = 7;
                    tCLLimitMax = 24;
                    TimingMTB   = Data2->tAAmin.Bits.tAAmin;
                    TimingFTB   = Data2->tAAminFine.Bits.tAAminFine;
                    CasMask     = Data2->CasLatencies.Data & MRC_SPD_DDR4_CL_SUPPORTED_MASK;
                  }
                  // Using 2.5% rounding here according to the latest JEDEC SPD spec
                  // @todo Update all other timings to use 2.5% instead of 1%
                  Calculated      = (tCKmin == 0) ? 0 : ((MediumTimeBase * TimingMTB) + (FineTimeBase * TimingFTB) - (tCKmin * 25 / 1000) + (tCKmin - 1)) / tCKmin;
                } else {
                  Calculated      = 0;
                }
                if (FirstProfile) {
                  tAAValue = Calculated;
                  FirstProfile = FALSE;
                } else if (tAAValue != Calculated) {
                  Outputs->XmpProfileEnable = 0;
                  MRC_DEBUG_MSG (Debug, MSG_LEVEL_WARNING, "  %s\n", XmpDisableString);
                }
                break;

              case USER_PROFILE:
                if (DimmIn->Timing.tCL > 0) {
                  CasMask         = ~(0UL);
                  Calculated      = DimmIn->Timing.tCL;
                  tCLOverride     = TRUE;
                  if (DimmOut->DdrType == MRC_DDR_TYPE_DDR4) {
                    tCLLimitMin = 7;
                    tCLLimitMax = 24;
                  }
                  break;
                } else {
                  // In AUTO mode, so no break.
                }

              case STD_PROFILE:
              default:
                switch (DeviceType) {
                  case MRC_SPD_DDR3_SDRAM_TYPE_NUMBER:
                  case MRC_SPD_LPDDR3_SDRAM_TYPE_NUMBER:
                  default:
                    tCLLimitMin = 4;
                    tCLLimitMax = 18;
                    TimingMTB   = Spd->Ddr3.General.tAAmin.Bits.tAAmin;
                    TimingFTB   = Spd->Ddr3.General.tAAminFine.Bits.tAAminFine;
                    CasMask     = Spd->Ddr3.General.CasLatencies.Data & MRC_SPD_CL_SUPPORTED_MASK;
                    break;
                  case MRC_SPD_DDR4_SDRAM_TYPE_NUMBER:
                    tCLLimitMin = 7;
                    tCLLimitMax = 24;
                    TimingMTB   = Spd->Ddr4.Base.tAAmin.Bits.tAAmin;
                    TimingFTB   = Spd->Ddr4.Base.tAAminFine.Bits.tAAminFine;
                    CasMask     = Spd->Ddr4.Base.CasLatencies.Data & MRC_SPD_DDR4_CL_SUPPORTED_MASK;
                    break;
                  case MRC_JEDEC_LPDDR3_SDRAM_TYPE_NUMBER:
                    tCLLimitMin = 3;
                    tCLLimitMax = 40;
                    TimingMTB   = Spd->Lpddr.Base.tAAmin.Bits.tAAmin;
                    TimingFTB   = Spd->Lpddr.Base.tAAminFine.Bits.tAAminFine;
                    CasMask     = Spd->Lpddr.Base.CasLatencies.Data & MRC_SPD_LPDDR_CL_SUPPORTED_MASK;
                    break;
                } //switch DeviceType
                // Using 2.5% rounding here according to the latest JEDEC SPD spec
                // @todo Update all other timings to use 2.5% instead of 1%
                Calculated      = (tCKmin == 0) ? 0 : ((MediumTimeBase * TimingMTB) + (FineTimeBase * TimingFTB) - (tCKmin * 25 / 1000) + (tCKmin - 1)) / tCKmin;
                break;
            } //end switch

            if (DimmOut->DdrType == MRC_DDR_TYPE_DDR4) {
              if (Calculated == 23) {
                Calculated = 24;                // 23 is not a valid DDR4 CAS value, use 24
              }
              if (UserProfile) {
                Calculated = MIN (Calculated, tCLLimitMax); // Enforce maximum allowed CAS value in User profile
              }
            }
            Actual[Profile] = MAX (Actual[Profile], Calculated);

            if (DimmOut->DdrType == MRC_DDR_TYPE_LPDDR3) {
              CasMask |= ((1 << 4) | (1 << 6)); // Add CL8 and CL10 in case LPDDR3 SPD image doesn't have them
            }
            CommonCasMask[Profile] &= CasMask;
            MRC_DEBUG_MSG (
              Debug,
              MSG_LEVEL_NOTE,
              "  % 7u % 10u % 8u % 5u %6u % 8Xh\n",
              Profile,
              Controller,
              Channel,
              Dimm,
              Calculated,
              CasMask
              );
          } //if DimmOut->Status
        } //for Dimm
      } //for Channel
    } //for Controller

    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "  Profile %u common set of supported CAS Latency values = %Xh\n", Profile, CommonCasMask[Profile]);

    if ((Profile >= XMP_PROFILE1) && (tCKmin == 0)) {
      continue;
    }

    Found[Profile] = FALSE;
    ConvertClock2Freq (MrcData, Outputs->RefClk, tCKmin, &tCKminIndex, NULL, NULL);
    if ((Profile >= XMP_PROFILE1) && (Outputs->RefClk == MRC_REF_CLOCK_133) && (Outputs->Capable100)) {
      ConvertClock2Freq (MrcData, MRC_REF_CLOCK_100, tCKmin, &tCKmin100, NULL, NULL);
      if (tCKmin100 > tCKminIndex) {
        tCKminIndex = tCKmin100;
        if (Inputs->MemoryProfile == Profile) {
          MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "  Profile%u is RefClk 100 capable, switching to RefClk 100\n", Profile);
          Outputs->RefClk = MRC_REF_CLOCK_100;
        }
      }
    }
    do {
      for (; !Found[Profile] && (Actual[Profile] <= tCLLimitMax); Actual[Profile]++) {
        if (UserProfile) {
          Found[Profile] = TRUE;
        } else if ((Actual[Profile] * tCKmin) <= MRC_TaaMAX) {
          Found[Profile] = ValidtCL (
                             Actual[Profile],
                             DeviceType,
                             CommonCasMask[Profile],
                             tCLLimitMin
                             );
        } // if
        if (Found[Profile]) {
          if (Profile == Inputs->MemoryProfile) {
            Outputs->MemoryClock = tCKmin;
            Status = TRUE;
          }
          for (Controller = 0; Controller < MAX_CONTROLLERS; Controller++) {
            ControllerOut = &Outputs->Controller[Controller];
            for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
              ChannelOut = &ControllerOut->Channel[Channel];
              for (Dimm = 0; Dimm < MAX_DIMMS_IN_CHANNEL; Dimm++) {
                DimmOut = &ChannelOut->Dimm[Dimm];
                if (DIMM_PRESENT == DimmOut->Status) {
                  DimmOut->Timing[Profile].tCL    = (UINT16) Actual[Profile];
                  ChannelOut->Timing[Profile].tCL = (UINT16) Actual[Profile];
                  DimmOut->Timing[Profile].tCK    = tCKmin;
                  ChannelOut->Timing[Profile].tCK = tCKmin;
                } //if
              } //for Dimm
            } //for Channel
          } //for Controller
          break;
        } //if Found[Profile]
      } //for Actual[Profile]
      if (!Found[Profile]) {
        if (UserProfile && ((Inputs->Ratio > 0) || (tCLOverride == TRUE))) {
          break;
        } else {
          tCKminIndexSave = tCKminIndex;
          while (--tCKminIndex > 0) {
            if (((FreqTable[tCKminIndex].FreqFlag & (1 << Outputs->RefClk)) != 0) ||
                (((FreqTable[tCKminIndex].FreqFlag & (MRC_BIT2 << Outputs->RefClk)) != 0) && Outputs->OddRatioMode)
                ) {
              tCKmin = FreqTable[tCKminIndex].tCK;
              ConvertClock2Freq (MrcData, Outputs->RefClk, tCKmin, &tCKminIndex, NULL, NULL);
              Actual[Profile] = (tCKmin == 0) ? 0 : ((MediumTimeBase * TimingMTB) + (FineTimeBase * TimingFTB) - (tCKmin / 100) + (tCKmin - 1)) / tCKmin;
              MRC_DEBUG_MSG (Debug,
                MSG_LEVEL_WARNING,
                "Warning: The memory frequency is being downgraded on profile %u, from %u to %u and the new tCL is %u\n",
                Profile,
                FreqTable[tCKminIndexSave].Frequency,
                FreqTable[tCKminIndex].Frequency,
                Actual[Profile]);
              break;
            }
          }
        }
      }
    } while (!Found[Profile] && (tCKminIndex > 0));
  } //for Profile

  Outputs->Frequency = ConvertClock2Freq (MrcData, Outputs->RefClk, Outputs->MemoryClock, NULL, NULL, NULL);

#ifdef MRC_DEBUG_PRINT
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "    %s%u:", BestCaseString, MAX_PROFILE - 1);
  for (Profile = STD_PROFILE; Profile < MAX_PROFILE; Profile++) {
    if (!(MrcXmpTimingProfileEnabled (MrcData, Profile))) {
      continue;
    }
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, " %u", Found[Profile] ? Actual[Profile] : 0);
  }
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n  Memory clock = %ufs\n", Outputs->MemoryClock);
#endif

  return (Status);
}

/**
  Calculate the minimum tCWL timing value for the given memory frequency.
    We calculate timings for all profiles so that this information can be passed out of MRC.

    @param[in, out] MrcData - Pointer to MrcData data structure.

    @retval TRUE if there are DIMMs present, otherwise FALSE.
**/
static
BOOLEAN
GetChannelDimmtCWL (
  IN OUT MrcParameters *const MrcData
  )
{
  const MrcInput        *Inputs;
  const MrcControllerIn *ControllerIn;
  const MrcChannelIn    *ChannelIn;
  const MrcDimmIn       *DimmIn;
  const MrcSpd          *Spd;
  MrcDebug              *Debug;
  MrcOutput             *Outputs;
  MrcControllerOut      *ControllerOut;
  MrcChannelOut         *ChannelOut;
  MrcDimmOut            *DimmOut;
  MrcTimeBase           *TimeBase;
  MrcProfile            Profile;
  UINT8                 Controller;
  UINT8                 Channel;
  UINT8                 Dimm;
  UINT32                tCKmin;
  INT32                 MediumTimebase;
  INT32                 FineTimebase;
  UINT32                Actual[MAX_PROFILE];
  UINT32                NewCL[MAX_PROFILE];
  UINT32                Calculated;
  UINT32                TimingMTB;
  UINT32                tCL;
  UINT32                tCWLValue;
  BOOLEAN               FirstProfile;

  Inputs      = &MrcData->Inputs;
  Outputs     = &MrcData->Outputs;
  Debug       = &Outputs->Debug;
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "  %s:\n  %s\n", tCWLString, HeaderString);

  //
  // Find the smallest timing value for all the given DIMMs, for all the profiles.
  //
  for (Profile = STD_PROFILE; Profile < MAX_PROFILE; Profile++) {
    if (!(MrcXmpTimingProfileEnabled (MrcData, Profile))) {
      continue;
    }
    FirstProfile    = TRUE;
    tCWLValue       = 0;
    Actual[Profile] = 0;
    NewCL[Profile]  = 0;
    for (Controller = 0; Controller < MAX_CONTROLLERS; Controller++) {
      ControllerIn  = &Inputs->Controller[Controller];
      ControllerOut = &Outputs->Controller[Controller];
      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        ChannelIn   = &ControllerIn->Channel[Channel];
        ChannelOut  = &ControllerOut->Channel[Channel];
        for (Dimm = 0; Dimm < MAX_DIMMS_IN_CHANNEL; Dimm++) {
          DimmIn  = &ChannelIn->Dimm[Dimm];
          DimmOut = &ChannelOut->Dimm[Dimm];
          if (DIMM_PRESENT == DimmOut->Status) {
            Spd            = &DimmIn->Spd.Data;
            tCKmin         = DimmOut->Timing[Profile].tCK;
            tCL            = DimmOut->Timing[Profile].tCL;
            TimeBase       = &ChannelOut->TimeBase[Dimm][Profile];
            MediumTimebase = TimeBase->Mtb;
            FineTimebase   = TimeBase->Ftb;
            Calculated     = 0;
            switch (Profile) {
              case XMP_PROFILE1:
              case XMP_PROFILE2:
                if (MrcDimmXmpProfileSupported (DimmOut, Profile)) {
                  if (MRC_DDR_TYPE_DDR3 == DimmOut->DdrType) {
                    TimingMTB = Spd->Ddr3.Xmp.Data[Profile - XMP_PROFILE1].tCWLmin.Bits.tCWLmin;
                    Calculated = (tCKmin == 0) ? 0 : ((MediumTimebase * TimingMTB) - (tCKmin / 100) + (tCKmin - 1)) / tCKmin;
                  } else {
                    //
                    // We pick up tCWL from the available list per frequency,
                    // so that it will be closest to tCL, for performance reasons.
                    //
                    if (tCKmin <= MRC_DDR_2600_TCK_MIN) {
                      Calculated = 18;
                    } else if (tCKmin <= MRC_DDR_2400_TCK_MIN) {
                      Calculated = (tCL >= 16) ? 16 : 14;
                    } else if (tCKmin <= MRC_DDR_2133_TCK_MIN) {
                      Calculated = 14;
                    } else if (tCKmin <= MRC_DDR_1867_TCK_MIN) {
                      Calculated = 12;
                    } else if (tCKmin <= MRC_DDR_1600_TCK_MIN) {
                      Calculated = (tCL >= 11) ? 11 : 9;
                    } else if (tCKmin <= MRC_DDR_1333_TCK_MIN) {
                      Calculated = 9;
                    }
                  }
                } else {
                  Calculated = 0;
                }
                if (FirstProfile) {
                  tCWLValue = Calculated;
                  FirstProfile = FALSE;
                } else if (tCWLValue != Calculated) {
                  Outputs->XmpProfileEnable = 0;
                  MRC_DEBUG_MSG (Debug, MSG_LEVEL_WARNING, "  %s\n", XmpDisableString);
                }
                break;
              case USER_PROFILE:
                if (DimmIn->Timing.tCWL > 0) {
                  Calculated = DimmIn->Timing.tCWL;
                  break;
                } else {
                  // In AUTO mode, so no break.
                }
              case STD_PROFILE:
              default:
                TimingMTB = 0;
                if (DimmOut->DdrType == MRC_DDR_TYPE_LPDDR3) {
                  //
                  // WL Set A from MR2 spec, adding 1 to take tDQSS into account.
                  // We will subtract this 1 when programming TC_ODT.tCWL
                  //
                  if (tCKmin <= MRC_DDR_1867_TCK_MIN) {
                    Calculated = 9;
                  } else if (tCKmin <= MRC_DDR_1333_TCK_MIN) {
                    Calculated = 7;
                  } else if (tCKmin <= MRC_DDR_1200_TCK_MIN) {
                    Calculated = 6;
                  } else if (tCKmin <= MRC_DDR_1067_TCK_MIN) {
                    Calculated = 5;
                  } else if (tCKmin <= MRC_DDR_800_TCK_MIN) {
                    Calculated = 4;
                  }
                  if (Calculated < 6) {
                    //
                    // At 1067 the TC_ODT.tCWL must be at least 5 on SKL,
                    // so need to update CL/CWL in this case to RL=9/WL=5 option from WL Set A.
                    //
                    // We will decrement WL on MC, so use RL=10/WL=6
                    Calculated = 7;
                    NewCL[Profile] = 10;
                  }
                } else if (DimmOut->DdrType == MRC_DDR_TYPE_DDR4) {
                  //
                  // We pick up tCWL from the available list per frequency,
                  // so that it will be closest to tCL, for performance reasons.
                  //
                  if (tCKmin <= MRC_DDR_2600_TCK_MIN) {
                    Calculated = 18;
                  } else if (tCKmin <= MRC_DDR_2400_TCK_MIN) {
                    Calculated = (tCL >= 16) ? 16 : 14;
                  } else if (tCKmin <= MRC_DDR_2133_TCK_MIN) {
                    Calculated = 14;
                  } else if (tCKmin <= MRC_DDR_1867_TCK_MIN) {
                    Calculated = 12;
                  } else if (tCKmin <= MRC_DDR_1600_TCK_MIN) {
                    Calculated = (tCL >= 11) ? 11 : 9;
                  } else if (tCKmin <= MRC_DDR_1333_TCK_MIN) {
                    Calculated = 9;
                  } else if (tCKmin <= MRC_DDR_1067_TCK_MIN) {
                    Calculated = 9;
                  }
                } else {
                  if (tCKmin <= MRC_DDR_2133_TCK_MIN) {
                    Calculated = 10;
                  } else if (tCKmin <= MRC_DDR_1867_TCK_MIN) {
                    Calculated = 9;
                  } else if (tCKmin <= MRC_DDR_1600_TCK_MIN) {
                    Calculated = 8;
                  } else if (tCKmin <= MRC_DDR_1333_TCK_MIN) {
                    Calculated = 7;
                  } else if (tCKmin <= MRC_DDR_1067_TCK_MIN) {
                    Calculated = 7;
                  } else if (tCKmin <= MRC_DDR_800_TCK_MIN) {
                    Calculated = 5;
                  }
                }
                break;
            } //switch

            Actual[Profile] = MAX (Actual[Profile], Calculated);
            MRC_DEBUG_MSG (
              Debug,
              MSG_LEVEL_NOTE,
              "  % 7u % 10u % 8u % 5u %6u\n",
              Profile,
              Controller,
              Channel,
              Dimm,
              Calculated
              );
          } //DimmOut->Status
        } //Dimm
      } //Channel
    } //Controller
  } //Profile

  //
  // Set the best case timing for all controllers/channels/dimms, for each profile.
  //
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "    %s%u:", BestCaseString, MAX_PROFILE - 1);
  for (Profile = STD_PROFILE; Profile < MAX_PROFILE; Profile++) {
    if (!(MrcXmpTimingProfileEnabled (MrcData, Profile))) {
      continue;
    }
    for (Controller = 0; Controller < MAX_CONTROLLERS; Controller++) {
      ControllerOut = &Outputs->Controller[Controller];
      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        ChannelOut = &ControllerOut->Channel[Channel];
        for (Dimm = 0; Dimm < MAX_DIMMS_IN_CHANNEL; Dimm++) {
          DimmOut = &ChannelOut->Dimm[Dimm];
          DimmOut->Timing[Profile].tCWL    = (UINT16) Actual[Profile];
          ChannelOut->Timing[Profile].tCWL = (UINT16) Actual[Profile];
          if (NewCL[Profile] != 0) {
            //
            // Update tCL as well
            //
            DimmOut->Timing[Profile].tCL    = (UINT16) NewCL[Profile];
            ChannelOut->Timing[Profile].tCL = (UINT16) NewCL[Profile];
          }
        }
      }
    }
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, " %u", Actual[Profile]);
  }
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n");

  for (Profile = STD_PROFILE; Profile < MAX_PROFILE; Profile++) {
    if (!(MrcXmpTimingProfileEnabled (MrcData, Profile))) {
      continue;
    }
    if (NewCL[Profile] != 0) {
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Profile  %u: tCL was updated to %u\n", Profile, NewCL[Profile]);
    }
  }

  return TRUE;
}


/**
  Calculate the minimum tFAW timing value for the given memory frequency.

    @param[in, out] MrcData - Pointer to MrcData data structure.

    @retval TRUE if there are DIMMs present, otherwise FALSE.
**/
static
BOOLEAN
GetChannelDimmtFAW (
  IN OUT MrcParameters *const MrcData
  )
{
  const MrcInput        *Inputs;
  const MrcControllerIn *ControllerIn;
  const MrcChannelIn    *ChannelIn;
  const MrcDimmIn       *DimmIn;
  const MrcSpd          *Spd;
  MrcDebug              *Debug;
  MrcOutput             *Outputs;
  MrcControllerOut      *ControllerOut;
  MrcChannelOut         *ChannelOut;
  MrcDimmOut            *DimmOut;
  MrcTimeBase           *TimeBase;
  MrcProfile            Profile;
  UINT8                 Controller;
  UINT8                 Channel;
  UINT8                 Dimm;
  UINT32                tCKmin;
  UINT32                TimingMTB;
  INT32                 MediumTimebase;
  INT32                 FineTimebase;
  UINT32                Actual[MAX_PROFILE];
  UINT32                Calculated;
  UINT32                tFAWValue;
  BOOLEAN               FirstProfile;

  const SPD_EXTREME_MEMORY_PROFILE_DATA      *Data1;
  const SPD_EXTREME_MEMORY_PROFILE_DATA_2_0  *Data2;

  Inputs  = &MrcData->Inputs;
  Outputs = &MrcData->Outputs;
  Debug   = &Outputs->Debug;
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "  %s:\n  %s\n", tFAWString, HeaderString);

  //
  // Find the smallest timing value for all the given DIMMs, for all the profiles.
  //
  for (Profile = STD_PROFILE; Profile < MAX_PROFILE; Profile++) {
    if (!(MrcXmpTimingProfileEnabled (MrcData, Profile))) {
      continue;
    }
    FirstProfile    = TRUE;
    tFAWValue       = 0;
    Actual[Profile] = 0;
    for (Controller = 0; Controller < MAX_CONTROLLERS; Controller++) {
      ControllerIn  = &Inputs->Controller[Controller];
      ControllerOut = &Outputs->Controller[Controller];
      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        ChannelIn   = &ControllerIn->Channel[Channel];
        ChannelOut  = &ControllerOut->Channel[Channel];
        for (Dimm = 0; Dimm < MAX_DIMMS_IN_CHANNEL; Dimm++) {
          DimmIn  = &ChannelIn->Dimm[Dimm];
          DimmOut = &ChannelOut->Dimm[Dimm];
          if (DIMM_PRESENT == DimmOut->Status) {
            Spd            = &DimmIn->Spd.Data;
            Calculated     = 0;
            tCKmin         = DimmOut->Timing[Profile].tCK;
            TimeBase       = &ChannelOut->TimeBase[Dimm][Profile];
            MediumTimebase = TimeBase->Mtb;
            FineTimebase   = TimeBase->Ftb;
            switch (Profile) {
              case XMP_PROFILE1:
              case XMP_PROFILE2:
                if (MrcDimmXmpProfileSupported (DimmOut, Profile)) {
                  if (MRC_DDR_TYPE_DDR3 == DimmOut->DdrType) {
                    Data1 = &Spd->Ddr3.Xmp.Data[Profile - XMP_PROFILE1];
                    TimingMTB  = ((UINT32) (Data1->tFAWMinUpper.Bits.tFAWminUpper) << 8) | (UINT32) (Data1->tFAWmin.Bits.tFAWmin);
                  } else {
                    Data2 = &Spd->Ddr4.EndUser.Xmp.Data[Profile - XMP_PROFILE1];
                    TimingMTB  = ((UINT32) (Data2->tFAWMinUpper.Bits.tFAWminUpper) << 8) | (UINT32) (Data2->tFAWmin.Bits.tFAWmin);
                  }
                  Calculated = (tCKmin == 0) ? 0 : ((MediumTimebase * TimingMTB) - (tCKmin / 100) + (tCKmin - 1)) / tCKmin;
                } else {
                  Calculated = 0;
                }
                if (FirstProfile) {
                  tFAWValue = Calculated;
                  FirstProfile = FALSE;
                } else if (tFAWValue != Calculated) {
                  Outputs->XmpProfileEnable = 0;
                  MRC_DEBUG_MSG (Debug, MSG_LEVEL_WARNING, "  %s\n", XmpDisableString);
                }
                break;
              case USER_PROFILE:
                if (DimmIn->Timing.tFAW > 0) {
                  Calculated = DimmIn->Timing.tFAW;
                  break;
                } else {
                  // In AUTO mode, so no break.
                }
              case STD_PROFILE:
              default:
                if (tCKmin > 0) {
                  if (MRC_DDR_TYPE_DDR3 == DimmOut->DdrType) {
                    TimingMTB = ((UINT32) (Spd->Ddr3.General.tFAWMinUpper.Bits.tFAWminUpper) << 8) | (UINT32) (Spd->Ddr3.General.tFAWmin.Bits.tFAWmin);
                  } else {
                    TimingMTB = ((UINT32) (Spd->Ddr4.Base.tFAWMinUpper.Bits.tFAWminUpper) << 8) | (UINT32) (Spd->Ddr4.Base.tFAWmin.Bits.tFAWmin);
                  }
                  if (DimmOut->DdrType == MRC_DDR_TYPE_LPDDR3) {
                    Calculated = DIVIDECEIL ((50000000 - (tCKmin / 100)), tCKmin); // 50ns
                  } else {
                    Calculated = ((MediumTimebase * TimingMTB) - (tCKmin / 100) + (tCKmin - 1)) / tCKmin;
                  }
                }
                break;
            } //switch

            Actual[Profile] = MAX (Actual[Profile], Calculated);
            MRC_DEBUG_MSG (
              Debug,
              MSG_LEVEL_NOTE,
              "  % 7u % 10u % 8u % 5u %6u\n",
              Profile,
              Controller,
              Channel,
              Dimm,
              Calculated
              );
          } //DimmOut->Status
        } //Dimm
      } //Channel
    } //Controller
  } //Profile

  //
  // Set the best case timing for all controllers/channels/dimms, for each profile.
  //
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "    %s%u:", BestCaseString, MAX_PROFILE - 1);
  for (Profile = STD_PROFILE; Profile < MAX_PROFILE; Profile++) {
    if (!(MrcXmpTimingProfileEnabled (MrcData, Profile))) {
      continue;
    }
    for (Controller = 0; Controller < MAX_CONTROLLERS; Controller++) {
      ControllerOut = &Outputs->Controller[Controller];
      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        ChannelOut = &ControllerOut->Channel[Channel];
        for (Dimm = 0; Dimm < MAX_DIMMS_IN_CHANNEL; Dimm++) {
          DimmOut = &ChannelOut->Dimm[Dimm];
          DimmOut->Timing[Profile].tFAW    = (UINT16) Actual[Profile];
          ChannelOut->Timing[Profile].tFAW = (UINT16) Actual[Profile];
        }
      }
    }
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, " %u", Actual[Profile]);
  }
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n");

  return TRUE;
}

/**
  Calculate the minimum tRAS timing value for the given memory frequency.

    @param[in, out] MrcData - Pointer to MrcData data structure.

    @retval TRUE if there are DIMMs present, otherwise FALSE.
**/
static
BOOLEAN
GetChannelDimmtRAS (
  IN OUT MrcParameters *const MrcData
  )
{
  const MrcInput        *Inputs;
  const MrcControllerIn *ControllerIn;
  const MrcChannelIn    *ChannelIn;
  const MrcDimmIn       *DimmIn;
  const MrcSpd          *Spd;
  MrcDebug              *Debug;
  MrcOutput             *Outputs;
  MrcControllerOut      *ControllerOut;
  MrcChannelOut         *ChannelOut;
  MrcDimmOut            *DimmOut;
  MrcTimeBase           *TimeBase;
  MrcProfile            Profile;
  UINT8                 Controller;
  UINT8                 Channel;
  UINT8                 Dimm;
  UINT32                tCKmin;
  UINT32                TimingMTB;
  INT32                 MediumTimebase;
  INT32                 FineTimebase;
  UINT32                Actual[MAX_PROFILE];
  UINT32                Calculated;
  UINT32                tRASValue;
  BOOLEAN               FirstProfile;

  const SPD_EXTREME_MEMORY_PROFILE_DATA      *Data1;
  const SPD_EXTREME_MEMORY_PROFILE_DATA_2_0  *Data2;
  UINT32                                     Index;

  Inputs  = &MrcData->Inputs;
  Outputs = &MrcData->Outputs;
  Debug   = &Outputs->Debug;

  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "  %s:\n  %s\n", tRASString, HeaderString);

  //
  // Find the smallest timing value for all the given DIMMs, for all the profiles.
  //
  for (Profile = STD_PROFILE; Profile < MAX_PROFILE; Profile++) {
    if (!(MrcXmpTimingProfileEnabled (MrcData, Profile))) {
      continue;
    }
    FirstProfile    = TRUE;
    tRASValue       = 0;
    Actual[Profile] = 0;
    for (Controller = 0; Controller < MAX_CONTROLLERS; Controller++) {
      ControllerIn  = &Inputs->Controller[Controller];
      ControllerOut = &Outputs->Controller[Controller];
      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        ChannelIn   = &ControllerIn->Channel[Channel];
        ChannelOut  = &ControllerOut->Channel[Channel];
        for (Dimm = 0; Dimm < MAX_DIMMS_IN_CHANNEL; Dimm++) {
          DimmIn  = &ChannelIn->Dimm[Dimm];
          DimmOut = &ChannelOut->Dimm[Dimm];
          if (DIMM_PRESENT == DimmOut->Status) {
            Spd            = &DimmIn->Spd.Data;
            Calculated     = 0;
            tCKmin         = DimmOut->Timing[Profile].tCK;
            TimeBase       = &ChannelOut->TimeBase[Dimm][Profile];
            MediumTimebase = TimeBase->Mtb;
            FineTimebase   = TimeBase->Ftb;
            switch (Profile) {
              case XMP_PROFILE1:
              case XMP_PROFILE2:
                if (MrcDimmXmpProfileSupported (DimmOut, Profile)) {
                  Index = Profile - XMP_PROFILE1;
                  if (MRC_DDR_TYPE_DDR3 == DimmOut->DdrType) {
                    Data1 = &Spd->Ddr3.Xmp.Data[Index];
                    TimingMTB = ((UINT32) (Data1->tRASMintRCMinUpper.Bits.tRASminUpper) << 8) | (UINT32) (Data1->tRASmin.Bits.tRASmin);
                  } else {
                    Data2 = &Spd->Ddr4.EndUser.Xmp.Data[Index];
                    TimingMTB = ((UINT32) (Data2->tRASMintRCMinUpper.Bits.tRASminUpper) << 8) | (UINT32) (Data2->tRASmin.Bits.tRASmin);
                  }
                  Calculated = (tCKmin == 0) ? 0 : ((MediumTimebase * TimingMTB) - (tCKmin / 100) + (tCKmin - 1)) / tCKmin;
                } else {
                  Calculated = 0;
                }
                if (FirstProfile) {
                  tRASValue = Calculated;
                  FirstProfile = FALSE;
                } else if (tRASValue != Calculated) {
                  Outputs->XmpProfileEnable = 0;
                  MRC_DEBUG_MSG (Debug, MSG_LEVEL_WARNING, "  %s\n", XmpDisableString);
                }
                break;
              case USER_PROFILE:
                if (DimmIn->Timing.tRAS > 0) {
                  Calculated = DimmIn->Timing.tRAS;
                  break;
                } else {
                  // In AUTO mode, so no break.
                }
              case STD_PROFILE:
              default:
                if (tCKmin > 0) {
                  if (MRC_DDR_TYPE_DDR3 == DimmOut->DdrType) {
                    TimingMTB = ((UINT32) (Spd->Ddr3.General.tRASMintRCMinUpper.Bits.tRASminUpper) << 8) | (UINT32) (Spd->Ddr3.General.tRASmin.Bits.tRASmin);
                  } else {
                    TimingMTB = ((UINT32) (Spd->Ddr4.Base.tRASMintRCMinUpper.Bits.tRASminUpper) << 8) | (UINT32) (Spd->Ddr4.Base.tRASmin.Bits.tRASmin);
                  }
                  if (MRC_DDR_TYPE_LPDDR3 == DimmOut->DdrType) {
                    Calculated = DIVIDECEIL ((42000000 - (tCKmin / 100)), tCKmin); // 42ns
                  } else {
                    Calculated = ((MediumTimebase * TimingMTB) - (tCKmin / 100) + (tCKmin - 1)) / tCKmin;
                  }
                }
                break;
            } //switch

            Actual[Profile] = MAX (Actual[Profile], Calculated);
            MRC_DEBUG_MSG (
              Debug,
              MSG_LEVEL_NOTE,
              "  % 7u % 10u % 8u % 5u %6u\n",
              Profile,
              Controller,
              Channel,
              Dimm,
              Calculated
              );
          } //DimmOut->Status
        } //Dimm
      } //Channel
    } //Controller
  } //Profile

  //
  // Set the best case timing for all controllers/channels/dimms, for each profile.
  //
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "    %s%u:", BestCaseString, MAX_PROFILE - 1);
  for (Profile = STD_PROFILE; Profile < MAX_PROFILE; Profile++) {
    if (!(MrcXmpTimingProfileEnabled (MrcData, Profile))) {
      continue;
    }
    for (Controller = 0; Controller < MAX_CONTROLLERS; Controller++) {
      ControllerOut = &Outputs->Controller[Controller];
      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        ChannelOut = &ControllerOut->Channel[Channel];
        for (Dimm = 0; Dimm < MAX_DIMMS_IN_CHANNEL; Dimm++) {
          DimmOut = &ChannelOut->Dimm[Dimm];
          DimmOut->Timing[Profile].tRAS    = (UINT16) Actual[Profile];
          ChannelOut->Timing[Profile].tRAS = (UINT16) Actual[Profile];
        }
      }
    }
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, " %u", Actual[Profile]);
  }
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n");

  return TRUE;
}

/**
  Calculate the minimum tRC timing value for the given memory frequency.
  SKL MC doesn't have a register for tRC, it uses (tRAS + tRP).
  Print the tRC values for each profile and issue a warning if tRC > (tRAS + tRP).

    @param[in, out] MrcData - Pointer to MrcData data structure.

    @retval TRUE if there are DIMMs present, otherwise FALSE.
**/
static
BOOLEAN
GetChannelDimmtRC (
  IN OUT MrcParameters *const MrcData
  )
{
  const MrcInput        *Inputs;
  const MrcControllerIn *ControllerIn;
  const MrcChannelIn    *ChannelIn;
  const MrcDimmIn       *DimmIn;
  const MrcSpd          *Spd;
  MrcDebug              *Debug;
  MrcOutput             *Outputs;
  MrcControllerOut      *ControllerOut;
  MrcChannelOut         *ChannelOut;
  MrcDimmOut            *DimmOut;
  MrcTimeBase           *TimeBase;
  MrcProfile            Profile;
  UINT8                 Controller;
  UINT8                 Channel;
  UINT8                 Dimm;
  UINT32                tCKmin;
  UINT32                TimingMTB;
  INT32                 TimingFTB;
  INT32                 MediumTimebase;
  INT32                 FineTimebase;
  UINT32                Actual[MAX_PROFILE];
  UINT32                Calculated;
  UINT32                tRCValue;
  BOOLEAN               FirstProfile;

  const SPD_EXTREME_MEMORY_PROFILE_DATA      *Data1;
  const SPD_EXTREME_MEMORY_PROFILE_DATA_2_0  *Data2;
  UINT32                                     Index;

  Inputs  = &MrcData->Inputs;
  Outputs = &MrcData->Outputs;
  Debug   = &Outputs->Debug;

  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "  %s:\n  %s\n", tRCString, HeaderString);

  //
  // Find the smallest timing value for all the given DIMMs, for all the profiles.
  //
  for (Profile = STD_PROFILE; Profile < MAX_PROFILE; Profile++) {
    if (!(MrcXmpTimingProfileEnabled (MrcData, Profile))) {
      continue;
    }
    FirstProfile    = TRUE;
    tRCValue        = 0;
    Actual[Profile] = 0;
    for (Controller = 0; Controller < MAX_CONTROLLERS; Controller++) {
      ControllerIn  = &Inputs->Controller[Controller];
      ControllerOut = &Outputs->Controller[Controller];
      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        ChannelIn   = &ControllerIn->Channel[Channel];
        ChannelOut  = &ControllerOut->Channel[Channel];
        for (Dimm = 0; Dimm < MAX_DIMMS_IN_CHANNEL; Dimm++) {
          DimmIn  = &ChannelIn->Dimm[Dimm];
          DimmOut = &ChannelOut->Dimm[Dimm];
          if (DIMM_PRESENT == DimmOut->Status) {
            Spd            = &DimmIn->Spd.Data;
            Calculated     = 0;
            tCKmin         = DimmOut->Timing[Profile].tCK;
            TimeBase       = &ChannelOut->TimeBase[Dimm][Profile];
            MediumTimebase = TimeBase->Mtb;
            FineTimebase   = TimeBase->Ftb;
            switch (Profile) {
              case XMP_PROFILE1:
              case XMP_PROFILE2:
                if (MrcDimmXmpProfileSupported (DimmOut, Profile)) {
                  Index = Profile - XMP_PROFILE1;
                  if (MRC_DDR_TYPE_DDR3 == DimmOut->DdrType) {
                    Data1 = &Spd->Ddr3.Xmp.Data[Index];
                    TimingMTB = ((UINT32) (Data1->tRASMintRCMinUpper.Bits.tRCminUpper) << 8) | (UINT32) (Data1->tRCmin.Bits.tRCmin);
                    TimingFTB = (DimmOut->XmpRevision == 0x13) ? Data1->tRCminFine.Bits.tRCminFine : 0;
                  } else {
                    Data2 = &Spd->Ddr4.EndUser.Xmp.Data[Index];
                    TimingMTB = ((UINT32) (Data2->tRASMintRCMinUpper.Bits.tRCminUpper) << 8) | (UINT32) (Data2->tRCmin.Bits.tRCmin);
                    TimingFTB = Data2->tRCminFine.Bits.tRCminFine;
                  }
                  Calculated = (tCKmin == 0) ? 0 : ((MediumTimebase * TimingMTB) + (FineTimebase * TimingFTB) - (tCKmin / 100) + (tCKmin - 1)) / tCKmin;
                } else {
                  Calculated = 0;
                }
                if (FirstProfile) {
                  tRCValue = Calculated;
                  FirstProfile = FALSE;
                } else if (tRCValue != Calculated) {
                  Outputs->XmpProfileEnable = 0;
                  MRC_DEBUG_MSG (Debug, MSG_LEVEL_WARNING, "  %s\n", XmpDisableString);
                }
                break;
              case USER_PROFILE:
              case STD_PROFILE:
              default:
                if (tCKmin > 0) {
                  if ((MRC_DDR_TYPE_DDR3 == DimmOut->DdrType) || (Spd->Ddr3.General.DramDeviceType.Bits.Type == MRC_SPD_LPDDR3_SDRAM_TYPE_NUMBER)) {
                    TimingMTB = ((UINT32) (Spd->Ddr3.General.tRASMintRCMinUpper.Bits.tRCminUpper) << 8) | (UINT32) (Spd->Ddr3.General.tRCmin.Bits.tRCmin);
                    TimingFTB = Spd->Ddr3.General.tRCminFine.Bits.tRCminFine;
                  } else {
                    TimingMTB = ((UINT32) (Spd->Ddr4.Base.tRASMintRCMinUpper.Bits.tRCminUpper) << 8) | (UINT32) (Spd->Ddr4.Base.tRCmin.Bits.tRCmin);
                    TimingFTB = Spd->Ddr4.Base.tRCminFine.Bits.tRCminFine;
                  }
                  if ((MRC_DDR_TYPE_LPDDR3 == DimmOut->DdrType) && (Spd->Ddr3.General.DramDeviceType.Bits.Type != MRC_SPD_LPDDR3_SDRAM_TYPE_NUMBER)) {
                    TimingMTB = (UINT32) (Spd->Lpddr.Base.tRPpb.Bits.tRPpb);
                    TimingFTB = Spd->Lpddr.Base.tRPpbFine.Bits.tRPpbFine;
                    Calculated = DIVIDECEIL (((MediumTimebase * TimingMTB) + (FineTimebase * TimingFTB) + 42000000 - (tCKmin / 100)), tCKmin); // 42ns
                  } else {
                    Calculated = ((MediumTimebase * TimingMTB) - (tCKmin / 100) + (tCKmin - 1)) / tCKmin;
                  }
                }
                break;
            } //switch

            Actual[Profile] = MAX (Actual[Profile], Calculated);
            MRC_DEBUG_MSG (
              Debug,
              MSG_LEVEL_NOTE,
              "  % 7u % 10u % 8u % 5u %6u\n",
              Profile,
              Controller,
              Channel,
              Dimm,
              Calculated
              );
          } //DimmOut->Status
        } //Dimm
      } //Channel
    } //Controller
  } //Profile

  //
  // Set the best case timing for all controllers/channels/dimms, for each profile.
  //
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "    %s%u:", BestCaseString, MAX_PROFILE - 1);
  for (Profile = STD_PROFILE; Profile < MAX_PROFILE; Profile++) {
    if (!(MrcXmpTimingProfileEnabled (MrcData, Profile))) {
      continue;
    }
    for (Controller = 0; Controller < MAX_CONTROLLERS; Controller++) {
      ControllerOut = &Outputs->Controller[Controller];
      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        ChannelOut = &ControllerOut->Channel[Channel];
        if (ChannelOut->Timing[Profile].tRAS + ChannelOut->Timing[Profile].tRCDtRP < (UINT16) Actual[Profile]) {
          MRC_DEBUG_MSG (Debug, MSG_LEVEL_WARNING, "\nWARNING: tRC is bigger than tRAS+tRP !\n");
        }
      }
    }
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, " %u", Actual[Profile]);
  }
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n");

  return TRUE;
}

/**
  Calculate the minimum tRCD timing value for the given memory frequency.

    @param[in, out] MrcData - Pointer to MrcData data structure.

    @retval TRUE if there are DIMMs present, otherwise FALSE.
**/
static
BOOLEAN
GetChannelDimmtRCD (
  IN OUT MrcParameters *const MrcData
  )
{
  const MrcInput        *Inputs;
  const MrcControllerIn *ControllerIn;
  const MrcChannelIn    *ChannelIn;
  const MrcDimmIn       *DimmIn;
  const MrcSpd          *Spd;
  MrcDebug              *Debug;
  MrcOutput             *Outputs;
  MrcControllerOut      *ControllerOut;
  MrcChannelOut         *ChannelOut;
  MrcDimmOut            *DimmOut;
  MrcTimeBase           *TimeBase;
  MrcProfile            Profile;
  UINT8                 Controller;
  UINT8                 Channel;
  UINT8                 Dimm;
  UINT32                tCKmin;
  UINT32                TimingMTB;
  INT32                 TimingFTB;
  INT32                 MediumTimebase;
  INT32                 FineTimebase;
  UINT32                Actual[MAX_PROFILE];
  UINT32                Calculated;
  UINT32                tRCDValue;
  BOOLEAN               FirstProfile;

  const SPD_EXTREME_MEMORY_PROFILE_DATA      *Data1;
  const SPD_EXTREME_MEMORY_PROFILE_DATA_2_0  *Data2;
  UINT32                                      Index;

  Inputs  = &MrcData->Inputs;
  Outputs = &MrcData->Outputs;
  Debug   = &Outputs->Debug;

  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "  %s:\n  %s\n", tRCDString, HeaderString);

  //
  // Find the smallest timing value for all the given DIMMs, for all the profiles.
  //
  for (Profile = STD_PROFILE; Profile < MAX_PROFILE; Profile++) {
    if (!(MrcXmpTimingProfileEnabled (MrcData, Profile))) {
      continue;
    }
    FirstProfile    = TRUE;
    tRCDValue       = 0;
    Actual[Profile] = 0;
    for (Controller = 0; Controller < MAX_CONTROLLERS; Controller++) {
      ControllerIn  = &Inputs->Controller[Controller];
      ControllerOut = &Outputs->Controller[Controller];
      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        ChannelIn   = &ControllerIn->Channel[Channel];
        ChannelOut  = &ControllerOut->Channel[Channel];
        for (Dimm = 0; Dimm < MAX_DIMMS_IN_CHANNEL; Dimm++) {
          DimmIn  = &ChannelIn->Dimm[Dimm];
          DimmOut = &ChannelOut->Dimm[Dimm];
          if (DIMM_PRESENT == DimmOut->Status) {
            Spd            = &DimmIn->Spd.Data;
            Calculated     = 0;
            tCKmin         = DimmOut->Timing[Profile].tCK;
            TimeBase       = &ChannelOut->TimeBase[Dimm][Profile];
            MediumTimebase = TimeBase->Mtb;
            FineTimebase   = TimeBase->Ftb;
            switch (Profile) {
              case XMP_PROFILE1:
              case XMP_PROFILE2:
                if (MrcDimmXmpProfileSupported (DimmOut, Profile)) {
                  Index = Profile - XMP_PROFILE1;
                  if (MRC_DDR_TYPE_DDR3 == DimmOut->DdrType) {
                    Data1 = &Spd->Ddr3.Xmp.Data[Index];
                    TimingMTB = Data1->tRCDmin.Bits.tRCDmin;
                    TimingFTB = Data1->tRCDminFine.Bits.tRCDminFine;
                  } else {
                    Data2 = &Spd->Ddr4.EndUser.Xmp.Data[Index];
                    TimingMTB = Data2->tRCDmin.Bits.tRCDmin;
                    TimingFTB = Data2->tRCDminFine.Bits.tRCDminFine;
                  }
                  Calculated = (tCKmin == 0) ? 0 : ((MediumTimebase * TimingMTB) + (FineTimebase * TimingFTB) - (tCKmin / 100) + (tCKmin - 1)) / tCKmin;
                } else {
                  Calculated = 0;
                }
                if (FirstProfile) {
                  tRCDValue = Calculated;
                  FirstProfile = FALSE;
                } else if (tRCDValue != Calculated) {
                  Outputs->XmpProfileEnable = 0;
                  MRC_DEBUG_MSG (Debug, MSG_LEVEL_WARNING, "  %s\n", XmpDisableString);
                }
                break;
              case USER_PROFILE:
                if (DimmIn->Timing.tRCDtRP > 0) {
                  Calculated = DimmIn->Timing.tRCDtRP;
                  break;
                } else {
                  // In AUTO mode, so no break.
                }
              case STD_PROFILE:
              default:
                if (tCKmin > 0) {
                  if ((MRC_DDR_TYPE_DDR3 == DimmOut->DdrType) || (Spd->Ddr3.General.DramDeviceType.Bits.Type == MRC_SPD_LPDDR3_SDRAM_TYPE_NUMBER))  {
                    TimingMTB = Spd->Ddr3.General.tRCDmin.Bits.tRCDmin;
                    TimingFTB = Spd->Ddr3.General.tRCDminFine.Bits.tRCDminFine;
                  } else if (MRC_DDR_TYPE_DDR4 == DimmOut->DdrType) {
                    TimingMTB = Spd->Ddr4.Base.tRCDmin.Bits.tRCDmin;
                    TimingFTB = Spd->Ddr4.Base.tRCDminFine.Bits.tRCDminFine;
                  } else {
                    TimingMTB = Spd->Lpddr.Base.tRCDmin.Bits.tRCDmin;
                    TimingFTB = Spd->Lpddr.Base.tRCDminFine.Bits.tRCDminFine;
                  }
                  Calculated = ((MediumTimebase * TimingMTB) + (FineTimebase * TimingFTB) - (tCKmin / 100) + (tCKmin - 1)) / tCKmin;
                }
                break;
            } //switch

            Actual[Profile] = MAX (Actual[Profile], Calculated);
            MRC_DEBUG_MSG (
              Debug,
              MSG_LEVEL_NOTE,
              "  % 7u % 10u % 8u % 5u %6u\n",
              Profile,
              Controller,
              Channel,
              Dimm,
              Calculated
              );
          } //DimmOut->Status
        } //Dimm
      } //Channel
    } //Controller
  } //Profile

  //
  // Set the best case timing for all controllers/channels/dimms, for each profile.
  //
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "    %s%u:", BestCaseString, MAX_PROFILE - 1);
  for (Profile = STD_PROFILE; Profile < MAX_PROFILE; Profile++) {
    if (!(MrcXmpTimingProfileEnabled (MrcData, Profile))) {
      continue;
    }
    for (Controller = 0; Controller < MAX_CONTROLLERS; Controller++) {
      ControllerOut = &Outputs->Controller[Controller];
      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        ChannelOut = &ControllerOut->Channel[Channel];
        for (Dimm = 0; Dimm < MAX_DIMMS_IN_CHANNEL; Dimm++) {
          DimmOut = &ChannelOut->Dimm[Dimm];
          DimmOut->Timing[Profile].tRCDtRP    = (UINT16) Actual[Profile];
          ChannelOut->Timing[Profile].tRCDtRP = (UINT16) Actual[Profile];
        }
      }
    }
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, " %u", Actual[Profile]);
  }
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n");

  return TRUE;
}

/**
  Calculate the minimum tREFI timing value for the given memory frequency.

    @param[in, out] MrcData - Pointer to MrcData data structure.

    @retval TRUE if there are DIMMs present, otherwise FALSE.
**/
static
BOOLEAN
GetChannelDimmtREFI (
  IN OUT MrcParameters *const MrcData
  )
{
  const MrcInput        *Inputs;
  const MrcControllerIn *ControllerIn;
  const MrcChannelIn    *ChannelIn;
  const MrcDimmIn       *DimmIn;
  const MrcSpd          *Spd;
  MrcDebug              *Debug;
  const MRC_FUNCTION    *MrcCall;
  MrcOutput             *Outputs;
  MrcControllerOut      *ControllerOut;
  MrcChannelOut         *ChannelOut;
  MrcDimmOut            *DimmOut;
  MrcTimeBase           *TimeBase;
  MrcProfile            Profile;
  UINT8                 Controller;
  UINT8                 Channel;
  UINT8                 Dimm;
  UINT32                tCKmin;
  INT32                 MediumTimebase;
  INT32                 FineTimebase;
  UINT32                Actual[MAX_PROFILE];
  UINT32                Calculated;
  UINT32                TimingMTB;
  UINT32                Index;
  UINT32                tREFIValue;
  BOOLEAN               FirstProfile;

  Inputs  = &MrcData->Inputs;
  Outputs = &MrcData->Outputs;
  Debug   = &Outputs->Debug;
  MrcCall = Inputs->Call.Func;

  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "  %s:\n  %s\n", tREFIString, HeaderString);

  //
  // Find the smallest timing value for all the given DIMMs, for all the profiles.
  //
  for (Profile = STD_PROFILE; Profile < MAX_PROFILE; Profile++) {
    if (!(MrcXmpTimingProfileEnabled (MrcData, Profile))) {
      continue;
    }
    FirstProfile    = TRUE;
    tREFIValue      = 0;
    Actual[Profile] = 0;
    for (Controller = 0; Controller < MAX_CONTROLLERS; Controller++) {
      ControllerIn  = &Inputs->Controller[Controller];
      ControllerOut = &Outputs->Controller[Controller];
      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        ChannelIn   = &ControllerIn->Channel[Channel];
        ChannelOut  = &ControllerOut->Channel[Channel];
        for (Dimm = 0; Dimm < MAX_DIMMS_IN_CHANNEL; Dimm++) {
          DimmIn  = &ChannelIn->Dimm[Dimm];
          DimmOut = &ChannelOut->Dimm[Dimm];
          if (DIMM_PRESENT == DimmOut->Status) {
            Spd            = &DimmIn->Spd.Data;
            Calculated     = 0;
            tCKmin         = DimmOut->Timing[Profile].tCK;
            TimeBase       = &ChannelOut->TimeBase[Dimm][Profile];
            MediumTimebase = TimeBase->Mtb;
            FineTimebase   = TimeBase->Ftb;
            switch (Profile) {
              case XMP_PROFILE1:
              case XMP_PROFILE2:
                if (MrcDimmXmpProfileSupported (DimmOut, Profile)) {
                  Index = Profile - XMP_PROFILE1;
                  if (MRC_DDR_TYPE_DDR3 == DimmOut->DdrType) {
                    TimingMTB = Spd->Ddr3.Xmp.Data[Index].tREFImin.Bits.tREFImin;
                    Calculated = (tCKmin == 0) ? 0 : (UINT32) (MrcCall->MrcDivU64x64 (
                                                                          ((MrcCall->MrcMultU64x32 (MediumTimebase, TimingMTB * TREFIMULTIPLIER)) - (tCKmin / 100) + (tCKmin - 1)),
                                                                          tCKmin,
                                                                          NULL));
                  } else {
                    TimingMTB = TREFIMIN_DDR4;
                    Calculated = (tCKmin == 0) ? 0 : ((TimingMTB + ((tCKmin / 1000) - 1)) / (tCKmin / 1000));
                  }
                } else {
                  Calculated = 0;
                }
                if (FirstProfile) {
                  tREFIValue = Calculated;
                  FirstProfile = FALSE;
                } else if (tREFIValue != Calculated) {
                  Outputs->XmpProfileEnable = 0;
                  MRC_DEBUG_MSG (Debug, MSG_LEVEL_WARNING, "  %s\n", XmpDisableString);
                }
                break;
              case USER_PROFILE:
                if (DimmIn->Timing.tREFI > 0) {
                  Calculated = DimmIn->Timing.tREFI;
                  break;
                } else {
                  // In AUTO mode, so no break.
                }
              case STD_PROFILE:
              default:
                if (tCKmin > 0) {
                  switch (DimmOut->DdrType) {
                    default:
                    case MRC_DDR_TYPE_DDR3:
                      TimingMTB = TREFIMIN_DDR3;
                      break;
                    case MRC_DDR_TYPE_LPDDR3:
                      TimingMTB = TREFIMIN_LPDDR3;
                      break;
                    case MRC_DDR_TYPE_DDR4:
                      TimingMTB = TREFIMIN_DDR4;
                      break;
                  }
                  Calculated = ((TimingMTB + ((tCKmin / 1000) - 1)) / (tCKmin / 1000));
                }
                break;
            } //switch

            Actual[Profile] = MAX (Actual[Profile], Calculated);
            MRC_DEBUG_MSG (
              Debug,
              MSG_LEVEL_NOTE,
              "  % 7u % 10u % 8u % 5u %6u\n",
              Profile,
              Controller,
              Channel,
              Dimm,
              Calculated
              );
          } //DimmOut->Status
        } //Dimm
      } //Channel
    } //Controller
  } //Profile

  //
  // Set the best case timing for all controllers/channels/dimms, for each profile.
  //
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "    %s%u:", BestCaseString, MAX_PROFILE - 1);
  for (Profile = STD_PROFILE; Profile < MAX_PROFILE; Profile++) {
    if (!(MrcXmpTimingProfileEnabled (MrcData, Profile))) {
      continue;
    }
    for (Controller = 0; Controller < MAX_CONTROLLERS; Controller++) {
      ControllerOut = &Outputs->Controller[Controller];
      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        ChannelOut = &ControllerOut->Channel[Channel];
        for (Dimm = 0; Dimm < MAX_DIMMS_IN_CHANNEL; Dimm++) {
          DimmOut = &ChannelOut->Dimm[Dimm];
          DimmOut->Timing[Profile].tREFI    = (UINT16) Actual[Profile];
          ChannelOut->Timing[Profile].tREFI = (UINT16) Actual[Profile];
        }
      }
    }
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, " %u", Actual[Profile]);
  }
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n");

  return TRUE;
}

/**
  Calculate the minimum tRFC timing value for the given memory frequency.

    @param[in, out] MrcData - Pointer to MrcData data structure.

    @retval TRUE if there are DIMMs present, otherwise FALSE.
**/
static
BOOLEAN
GetChannelDimmtRFC (
  IN OUT MrcParameters *const MrcData
  )
{
  const MrcInput        *Inputs;
  const MrcControllerIn *ControllerIn;
  const MrcChannelIn    *ChannelIn;
  const MrcDimmIn       *DimmIn;
  const MrcSpd          *Spd;
  MrcDebug              *Debug;
  MrcOutput             *Outputs;
  MrcControllerOut      *ControllerOut;
  MrcChannelOut         *ChannelOut;
  MrcDimmOut            *DimmOut;
  MrcTimeBase           *TimeBase;
  MrcProfile            Profile;
  UINT8                 Controller;
  UINT8                 Channel;
  UINT8                 Dimm;
  UINT32                tCKmin;
  UINT32                TimingMTB;
  INT32                 MediumTimebase;
  INT32                 FineTimebase;
  UINT32                Actual[MAX_PROFILE];
  UINT32                Calculated;
  UINT32                Index;
  UINT32                tRFCValue;
  BOOLEAN               FirstProfile;

  Inputs  = &MrcData->Inputs;
  Outputs = &MrcData->Outputs;
  Debug   = &Outputs->Debug;

  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "  %s:\n  %s\n", tRFCString, HeaderString);

  //
  // Find the smallest timing value for all the given DIMMs.
  //
  for (Profile = STD_PROFILE; Profile < MAX_PROFILE; Profile++) {
    if (!(MrcXmpTimingProfileEnabled (MrcData, Profile))) {
      continue;
    }
    FirstProfile    = TRUE;
    tRFCValue       = 0;
    Actual[Profile] = 0;
    for (Controller = 0; Controller < MAX_CONTROLLERS; Controller++) {
      ControllerIn  = &Inputs->Controller[Controller];
      ControllerOut = &Outputs->Controller[Controller];
      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        ChannelIn   = &ControllerIn->Channel[Channel];
        ChannelOut  = &ControllerOut->Channel[Channel];
        for (Dimm = 0; Dimm < MAX_DIMMS_IN_CHANNEL; Dimm++) {
          DimmIn  = &ChannelIn->Dimm[Dimm];
          DimmOut = &ChannelOut->Dimm[Dimm];
          if (DIMM_PRESENT == DimmOut->Status) {
            Spd            = &DimmIn->Spd.Data;
            Calculated     = 0;
            tCKmin         = DimmOut->Timing[Profile].tCK;
            TimeBase       = &ChannelOut->TimeBase[Dimm][Profile];
            MediumTimebase = TimeBase->Mtb;
            FineTimebase   = TimeBase->Ftb;
            switch (Profile) {
              case XMP_PROFILE1:
              case XMP_PROFILE2:
                if (MrcDimmXmpProfileSupported (DimmOut, Profile)) {
                  Index = Profile - XMP_PROFILE1;
                  if (MRC_DDR_TYPE_DDR3 == DimmOut->DdrType) {
                    TimingMTB = Spd->Ddr3.Xmp.Data[Index].tRFCmin.Bits.tRFCmin;
                  } else {
                    TimingMTB = Spd->Ddr4.EndUser.Xmp.Data[Index].tRFC1min.Bits.tRFCmin;
                  }
                  Calculated = (tCKmin == 0) ? 0 : ((MediumTimebase * TimingMTB) - (tCKmin / 100) + (tCKmin - 1)) / tCKmin;
                } else {
                  Calculated = 0;
                }
                if (FirstProfile) {
                  tRFCValue = Calculated;
                  FirstProfile = FALSE;
                } else if (tRFCValue != Calculated) {
                  Outputs->XmpProfileEnable = 0;
                  MRC_DEBUG_MSG (Debug, MSG_LEVEL_WARNING, "  %s\n", XmpDisableString);
                }
                break;
              case USER_PROFILE:
                if (DimmIn->Timing.tRFC > 0) {
                  Calculated = DimmIn->Timing.tRFC;
                  break;
                } else {
                  // In AUTO mode, so no break.
                }
              case STD_PROFILE:
              default:
                if (tCKmin > 0) {
                  if ((MRC_DDR_TYPE_DDR3 == DimmOut->DdrType) || (Spd->Ddr3.General.DramDeviceType.Bits.Type == MRC_SPD_LPDDR3_SDRAM_TYPE_NUMBER)) {
                    TimingMTB = Spd->Ddr3.General.tRFCmin.Bits.tRFCmin;
                    //
                    // @todo: Temp w/a for 8GB dimms
                    // if ((DimmOut->DimmCapacity == 8192) && (TimingMTB != 2400)) {
                    //   MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s %u/%u/%u tRFC MTB = %u .., W/A - changing it to 2400\n", CcdString, Controller, Channel, Dimm, TimingMTB);
                    //   TimingMTB = 2400;
                    // }
                    //
                  } else if (MRC_DDR_TYPE_DDR4 == DimmOut->DdrType) {
                    TimingMTB = Spd->Ddr4.Base.tRFC1min.Bits.tRFCmin;
                  } else {
                    TimingMTB = Spd->Lpddr.Base.tRFCab.Bits.tRFCab;
                  }
                  // @todo: Temp w/a for 8GB dimms
                  Calculated = ((MediumTimebase * TimingMTB) - (tCKmin / 100) + (tCKmin - 1)) / tCKmin;
                }
                break;
            } //switch

            Actual[Profile] = MAX (Actual[Profile], Calculated);
            MRC_DEBUG_MSG (
              Debug,
              MSG_LEVEL_NOTE,
              "  % 7u % 10u % 8u % 5u %6u\n",
              Profile,
              Controller,
              Channel,
              Dimm,
              Calculated
              );
          } //DimmOut->Status
        } //Dimm
      } //Channel
    } //Controller
  } //Profile

  //
  // Set the best case timing for all controllers/channels/dimms, for each profile.
  //
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "    %s%u:", BestCaseString, MAX_PROFILE - 1);
  for (Profile = STD_PROFILE; Profile < MAX_PROFILE; Profile++) {
    if (!(MrcXmpTimingProfileEnabled (MrcData, Profile))) {
      continue;
    }
    for (Controller = 0; Controller < MAX_CONTROLLERS; Controller++) {
      ControllerOut = &Outputs->Controller[Controller];
      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        ChannelOut = &ControllerOut->Channel[Channel];
        for (Dimm = 0; Dimm < MAX_DIMMS_IN_CHANNEL; Dimm++) {
          DimmOut = &ChannelOut->Dimm[Dimm];
          DimmOut->Timing[Profile].tRFC    = (UINT16) Actual[Profile];
          ChannelOut->Timing[Profile].tRFC = (UINT16) Actual[Profile];
        }
      }
    }
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, " %u", Actual[Profile]);
  }
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n");

  return TRUE;
}

/**
  Calculate the minimum tRFC2 timing value for the given memory frequency.

    @param[in, out] MrcData - Pointer to MrcData data structure.

    @retval TRUE if there are DIMMs present, otherwise FALSE.
**/
static
BOOLEAN
GetChannelDimmtRFC2 (
  IN OUT MrcParameters *const MrcData
  )
{
  const MrcInput        *Inputs;
  const MrcControllerIn *ControllerIn;
  const MrcChannelIn    *ChannelIn;
  const MrcDimmIn       *DimmIn;
  const MrcSpd          *Spd;
  MrcDebug              *Debug;
  MrcOutput             *Outputs;
  MrcControllerOut      *ControllerOut;
  MrcChannelOut         *ChannelOut;
  MrcDimmOut            *DimmOut;
  MrcTimeBase           *TimeBase;
  MrcProfile            Profile;
  UINT8                 Controller;
  UINT8                 Channel;
  UINT8                 Dimm;
  UINT32                tCKmin;
  UINT32                TimingMTB;
  INT32                 MediumTimebase;
  UINT32                Actual[MAX_PROFILE];
  UINT32                Calculated;
  UINT32                tRFC2Value;
  BOOLEAN               FirstProfile;

  Inputs  = &MrcData->Inputs;
  Outputs = &MrcData->Outputs;
  Debug   = &Outputs->Debug;

  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "  %s:\n  %s\n", tRFC2String, HeaderString);

  //
  // Find the smallest timing value for all the given DIMMs, for all the profiles.
  //
  for (Profile = STD_PROFILE; Profile < MAX_PROFILE; Profile++) {
    if (!(MrcXmpTimingProfileEnabled (MrcData, Profile))) {
      continue;
    }
    FirstProfile    = TRUE;
    tRFC2Value      = 0;
    Actual[Profile] = 0;
    for (Controller = 0; Controller < MAX_CONTROLLERS; Controller++) {
      ControllerIn  = &Inputs->Controller[Controller];
      ControllerOut = &Outputs->Controller[Controller];
      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        ChannelIn   = &ControllerIn->Channel[Channel];
        ChannelOut  = &ControllerOut->Channel[Channel];
        for (Dimm = 0; Dimm < MAX_DIMMS_IN_CHANNEL; Dimm++) {
          DimmIn  = &ChannelIn->Dimm[Dimm];
          DimmOut = &ChannelOut->Dimm[Dimm];
          if (DIMM_PRESENT == DimmOut->Status) {
            Spd            = &DimmIn->Spd.Data;
            Calculated     = 0;
            tCKmin         = DimmOut->Timing[Profile].tCK;
            TimeBase       = &ChannelOut->TimeBase[Dimm][Profile];
            MediumTimebase = TimeBase->Mtb;
            switch (Profile) {
              case XMP_PROFILE1:
              case XMP_PROFILE2:
                if (MRC_DDR_TYPE_DDR4 == DimmOut->DdrType) {
                  TimingMTB = Spd->Ddr4.EndUser.Xmp.Data[Profile - XMP_PROFILE1].tRFC2min.Bits.tRFCmin;
                  Calculated = (tCKmin == 0) ? 0 : ((MediumTimebase * TimingMTB) - (tCKmin / 100) + (tCKmin - 1)) / tCKmin;
                  if (FirstProfile) {
                    tRFC2Value = Calculated;
                    FirstProfile = FALSE;
                  } else if (tRFC2Value != Calculated) {
                    Outputs->XmpProfileEnable = 0;
                    MRC_DEBUG_MSG (Debug, MSG_LEVEL_WARNING, "  %s\n", XmpDisableString);
                  }
                }
                break;
              case USER_PROFILE:
                if (DimmIn->Timing.tRFC2 > 0) {
                  Calculated = DimmIn->Timing.tRFC2;
                  break;
                } else {
                  // In AUTO mode, so no break.
                }
              case STD_PROFILE:
              default:
                if (MRC_DDR_TYPE_DDR4 == DimmOut->DdrType) {
                  TimingMTB  = Spd->Ddr4.Base.tRFC2min.Bits.tRFCmin;
                  Calculated = (tCKmin == 0) ? 0 : ((MediumTimebase * TimingMTB) - (tCKmin / 100) + (tCKmin - 1)) / tCKmin;
                }
                break;
            } //switch

            Actual[Profile] = MAX (Actual[Profile], Calculated);
            MRC_DEBUG_MSG (
              Debug,
              MSG_LEVEL_NOTE,
              "  % 7u % 10u % 8u % 5u %6u\n",
              Profile,
              Controller,
              Channel,
              Dimm,
              Calculated
              );
          } //DimmOut->Status
        } //Dimm
      } //Channel
    } //Controller
  } //Profile

  //
  // Set the best case timing for all controllers/channels/dimms, for each profile.
  //
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "    %s%u:", BestCaseString, MAX_PROFILE - 1);
  for (Profile = STD_PROFILE; Profile < MAX_PROFILE; Profile++) {
    if (!(MrcXmpTimingProfileEnabled (MrcData, Profile))) {
      continue;
    }
    for (Controller = 0; Controller < MAX_CONTROLLERS; Controller++) {
      ControllerOut = &Outputs->Controller[Controller];
      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        ChannelOut = &ControllerOut->Channel[Channel];
        for (Dimm = 0; Dimm < MAX_DIMMS_IN_CHANNEL; Dimm++) {
          DimmOut = &ChannelOut->Dimm[Dimm];
          DimmOut->Timing[Profile].tRFC2    = (UINT16) Actual[Profile];
          ChannelOut->Timing[Profile].tRFC2 = (UINT16) Actual[Profile];
        }
      }
    }
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, " %u", Actual[Profile]);
  }
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n");

  return TRUE;
}

/**
  Calculate the minimum tRFC4 timing value for the given memory frequency.

    @param[in, out] MrcData - Pointer to MrcData data structure.

    @retval TRUE if there are DIMMs present, otherwise FALSE.
**/
static
BOOLEAN
GetChannelDimmtRFC4 (
  IN OUT MrcParameters *const MrcData
  )
{
  const MrcInput        *Inputs;
  const MrcControllerIn *ControllerIn;
  const MrcChannelIn    *ChannelIn;
  const MrcDimmIn       *DimmIn;
  const MrcSpd          *Spd;
  MrcDebug              *Debug;
  MrcOutput             *Outputs;
  MrcControllerOut      *ControllerOut;
  MrcChannelOut         *ChannelOut;
  MrcDimmOut            *DimmOut;
  MrcTimeBase           *TimeBase;
  MrcProfile            Profile;
  UINT8                 Controller;
  UINT8                 Channel;
  UINT8                 Dimm;
  UINT32                tCKmin;
  UINT32                TimingMTB;
  INT32                 MediumTimebase;
  UINT32                Actual[MAX_PROFILE];
  UINT32                Calculated;
  UINT32                tRFC4Value;
  BOOLEAN               FirstProfile;

  Inputs  = &MrcData->Inputs;
  Outputs = &MrcData->Outputs;
  Debug   = &Outputs->Debug;

  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "  %s:\n  %s\n", tRFC4String, HeaderString);

  //
  // Find the smallest timing value for all the given DIMMs, for all the profiles.
  //
  for (Profile = STD_PROFILE; Profile < MAX_PROFILE; Profile++) {
    if (!(MrcXmpTimingProfileEnabled (MrcData, Profile))) {
      continue;
    }
    FirstProfile    = TRUE;
    tRFC4Value      = 0;
    Actual[Profile] = 0;
    for (Controller = 0; Controller < MAX_CONTROLLERS; Controller++) {
      ControllerIn  = &Inputs->Controller[Controller];
      ControllerOut = &Outputs->Controller[Controller];
      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        ChannelIn   = &ControllerIn->Channel[Channel];
        ChannelOut  = &ControllerOut->Channel[Channel];
        for (Dimm = 0; Dimm < MAX_DIMMS_IN_CHANNEL; Dimm++) {
          DimmIn  = &ChannelIn->Dimm[Dimm];
          DimmOut = &ChannelOut->Dimm[Dimm];
          if (DIMM_PRESENT == DimmOut->Status) {
            Spd            = &DimmIn->Spd.Data;
            Calculated     = 0;
            tCKmin         = DimmOut->Timing[Profile].tCK;
            TimeBase       = &ChannelOut->TimeBase[Dimm][Profile];
            MediumTimebase = TimeBase->Mtb;
            switch (Profile) {
              case XMP_PROFILE1:
              case XMP_PROFILE2:
                if (MRC_DDR_TYPE_DDR4 == DimmOut->DdrType) {
                  TimingMTB = Spd->Ddr4.EndUser.Xmp.Data[Profile - XMP_PROFILE1].tRFC4min.Bits.tRFCmin;
                  Calculated = (tCKmin == 0) ? 0 : ((MediumTimebase * TimingMTB) - (tCKmin / 100) + (tCKmin - 1)) / tCKmin;
                  if (FirstProfile) {
                    tRFC4Value = Calculated;
                    FirstProfile = FALSE;
                  } else if (tRFC4Value != Calculated) {
                    Outputs->XmpProfileEnable = 0;
                    MRC_DEBUG_MSG (Debug, MSG_LEVEL_WARNING, "  %s\n", XmpDisableString);
                  }
                }
                break;
              case USER_PROFILE:
                if (DimmIn->Timing.tRFC4 > 0) {
                  Calculated = DimmIn->Timing.tRFC4;
                  break;
                } else {
                  // In AUTO mode, so no break.
                }
              case STD_PROFILE:
              default:
                if (MRC_DDR_TYPE_DDR4 == DimmOut->DdrType) {
                  TimingMTB  = Spd->Ddr4.Base.tRFC4min.Bits.tRFCmin;
                  Calculated = (tCKmin == 0) ? 0 : ((MediumTimebase * TimingMTB) - (tCKmin / 100) + (tCKmin - 1)) / tCKmin;
                }
                break;
            } //switch

            Actual[Profile] = MAX (Actual[Profile], Calculated);
            MRC_DEBUG_MSG (
              Debug,
              MSG_LEVEL_NOTE,
              "  % 7u % 10u % 8u % 5u %6u\n",
              Profile,
              Controller,
              Channel,
              Dimm,
              Calculated
              );
          } //DimmOut->Status
        } //Dimm
      } //Channel
    } //Controller
  } //Profile

  //
  // Set the best case timing for all controllers/channels/dimms, for each profile.
  //
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "    %s%u:", BestCaseString, MAX_PROFILE - 1);
  for (Profile = STD_PROFILE; Profile < MAX_PROFILE; Profile++) {
    if (!(MrcXmpTimingProfileEnabled (MrcData, Profile))) {
      continue;
    }
    for (Controller = 0; Controller < MAX_CONTROLLERS; Controller++) {
      ControllerOut = &Outputs->Controller[Controller];
      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        ChannelOut = &ControllerOut->Channel[Channel];
        for (Dimm = 0; Dimm < MAX_DIMMS_IN_CHANNEL; Dimm++) {
          DimmOut = &ChannelOut->Dimm[Dimm];
          DimmOut->Timing[Profile].tRFC4    = (UINT16) Actual[Profile];
          ChannelOut->Timing[Profile].tRFC4 = (UINT16) Actual[Profile];
        }
      }
    }
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, " %u", Actual[Profile]);
  }
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n");

  return TRUE;
}

/**
  Calculate the minimum tRP timing value for the given memory frequency.

    @param[in, out] MrcData - Pointer to MrcData data structure.

    @retval TRUE if there are DIMMs present, otherwise FALSE.
**/
static
BOOLEAN
GetChannelDimmtRP (
  IN OUT MrcParameters *const MrcData
  )
{
  const MrcInput        *Inputs;
  const MrcControllerIn *ControllerIn;
  const MrcChannelIn    *ChannelIn;
  const MrcDimmIn       *DimmIn;
  const MrcSpd          *Spd;
  MrcDebug              *Debug;
  MrcOutput             *Outputs;
  MrcControllerOut      *ControllerOut;
  MrcChannelOut         *ChannelOut;
  MrcDimmOut            *DimmOut;
  MrcTimeBase           *TimeBase;
  MrcProfile            Profile;
  UINT8                 Controller;
  UINT8                 Channel;
  UINT8                 Dimm;
  UINT32                tCKmin;
  INT32                 MediumTimebase;
  INT32                 FineTimebase;
  UINT32                TimingMTB;
  INT32                 TimingFTB;
  UINT32                Actual[MAX_PROFILE];
  UINT32                Calculated;
  UINT32                tRPValue;
  BOOLEAN               FirstProfile;

  const SPD_EXTREME_MEMORY_PROFILE_DATA      *Data1;
  const SPD_EXTREME_MEMORY_PROFILE_DATA_2_0  *Data2;
  UINT32                                      Index;

  Inputs  = &MrcData->Inputs;
  Outputs = &MrcData->Outputs;
  Debug   = &Outputs->Debug;

  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "  %s:\n  %s\n", tRPString, HeaderString);

  //
  // Find the smallest timing value for all the given DIMMs, for all the profiles.
  //
  for (Profile = STD_PROFILE; Profile < MAX_PROFILE; Profile++) {
    if (!(MrcXmpTimingProfileEnabled (MrcData, Profile))) {
      continue;
    }
    FirstProfile    = TRUE;
    tRPValue        = 0;
    Actual[Profile] = 0;
    for (Controller = 0; Controller < MAX_CONTROLLERS; Controller++) {
      ControllerIn  = &Inputs->Controller[Controller];
      ControllerOut = &Outputs->Controller[Controller];
      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        ChannelIn   = &ControllerIn->Channel[Channel];
        ChannelOut  = &ControllerOut->Channel[Channel];
        for (Dimm = 0; Dimm < MAX_DIMMS_IN_CHANNEL; Dimm++) {
          DimmIn  = &ChannelIn->Dimm[Dimm];
          DimmOut = &ChannelOut->Dimm[Dimm];
          if (DIMM_PRESENT == DimmOut->Status) {
            Spd            = &DimmIn->Spd.Data;
            Calculated     = 0;
            tCKmin         = DimmOut->Timing[Profile].tCK;
            TimeBase       = &ChannelOut->TimeBase[Dimm][Profile];
            MediumTimebase = TimeBase->Mtb;
            FineTimebase   = TimeBase->Ftb;
            switch (Profile) {
              case XMP_PROFILE1:
              case XMP_PROFILE2:
                if (MrcDimmXmpProfileSupported (DimmOut, Profile)) {
                  Index = Profile - XMP_PROFILE1;
                  if (MRC_DDR_TYPE_DDR3 == DimmOut->DdrType) {
                    Data1 = &Spd->Ddr3.Xmp.Data[Index];
                    TimingMTB = Data1->tRPmin.Bits.tRPmin;
                    TimingFTB = (DimmOut->XmpRevision == 0x13) ? Data1->tRPminFine.Bits.tRPminFine : 0;
                  } else {
                    Data2 = &Spd->Ddr4.EndUser.Xmp.Data[Index];
                    TimingMTB = Data2->tRPmin.Bits.tRPmin;
                    TimingFTB = Data2->tRPminFine.Bits.tRPminFine;
                  }
                  Calculated = (tCKmin == 0) ? 0 : ((MediumTimebase * TimingMTB) + (FineTimebase * TimingFTB) - (tCKmin / 100) + (tCKmin - 1)) / tCKmin;
                } else {
                  Calculated = 0;
                }
                if (FirstProfile) {
                  tRPValue = Calculated;
                  FirstProfile = FALSE;
                } else if (tRPValue != Calculated) {
                  Outputs->XmpProfileEnable = 0;
                  MRC_DEBUG_MSG (Debug, MSG_LEVEL_WARNING, "  %s\n", XmpDisableString);
                }
                break;
              case USER_PROFILE:
                if (DimmIn->Timing.tRCDtRP > 0) {
                  Calculated = DimmIn->Timing.tRCDtRP;
                  break;
                } else {
                  // In AUTO mode, so no break.
                }
              case STD_PROFILE:
              default:
                if (tCKmin > 0) {
                  if ((MRC_DDR_TYPE_DDR3 == DimmOut->DdrType) || (Spd->Ddr3.General.DramDeviceType.Bits.Type == MRC_SPD_LPDDR3_SDRAM_TYPE_NUMBER)) {
                    TimingMTB = Spd->Ddr3.General.tRPmin.Bits.tRPmin;
                    TimingFTB = Spd->Ddr3.General.tRPminFine.Bits.tRPminFine;
                  } else if (MRC_DDR_TYPE_DDR4 == DimmOut->DdrType) {
                    TimingMTB = Spd->Ddr4.Base.tRPmin.Bits.tRPmin;
                    TimingFTB = Spd->Ddr4.Base.tRPminFine.Bits.tRPminFine;
                  } else {
                    TimingMTB = Spd->Lpddr.Base.tRPpb.Bits.tRPpb;
                    TimingFTB = Spd->Lpddr.Base.tRPpbFine.Bits.tRPpbFine;
                  }
                  Calculated = ((MediumTimebase * TimingMTB) + (FineTimebase * TimingFTB) - (tCKmin / 100) + (tCKmin - 1)) / tCKmin;
                }
                break;
            } //switch

            Actual[Profile] = MAX (Actual[Profile], Calculated);
            //
            // Take MAX of tRCD and tRP if they are different in SPD.
            // This assumes that GetChannelDimmtRCD() was already called.
            //
            Actual[Profile] = MAX (Actual[Profile], DimmOut->Timing[Profile].tRCDtRP);
            MRC_DEBUG_MSG (
              Debug,
              MSG_LEVEL_NOTE,
              "  % 7u % 10u % 8u % 5u %6u\n",
              Profile,
              Controller,
              Channel,
              Dimm,
              Calculated
              );
          } //DimmOut->Status
        } //Dimm
      } //Channel
    } //Controller
  } //Profile

  //
  // Set the best case timing for all controllers/channels/dimms, for each profile.
  //
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "    %s%u:", BestCaseString, MAX_PROFILE - 1);
  for (Profile = STD_PROFILE; Profile < MAX_PROFILE; Profile++) {
    if (!(MrcXmpTimingProfileEnabled (MrcData, Profile))) {
      continue;
    }
    for (Controller = 0; Controller < MAX_CONTROLLERS; Controller++) {
      ControllerOut = &Outputs->Controller[Controller];
      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        ChannelOut = &ControllerOut->Channel[Channel];
        for (Dimm = 0; Dimm < MAX_DIMMS_IN_CHANNEL; Dimm++) {
          DimmOut = &ChannelOut->Dimm[Dimm];
          DimmOut->Timing[Profile].tRCDtRP    = (UINT16) Actual[Profile];
          ChannelOut->Timing[Profile].tRCDtRP = (UINT16) Actual[Profile];
        }
      }
    }
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, " %u", Actual[Profile]);
  }
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n");

  return TRUE;
}

/**
  Calculate the minimum tRPab timing value for the given memory frequency.

    @param[in, out] MrcData - Pointer to MrcData data structure.

    @retval TRUE if there are DIMMs present, otherwise FALSE.
**/
static
BOOLEAN
GetChannelDimmtRPab (
  IN OUT MrcParameters *const MrcData
  )
{
  const MrcInput        *Inputs;
  const MrcControllerIn *ControllerIn;
  const MrcChannelIn    *ChannelIn;
  const MrcDimmIn       *DimmIn;
  const MrcSpd          *Spd;
  MrcDebug              *Debug;
  MrcOutput             *Outputs;
  MrcControllerOut      *ControllerOut;
  MrcChannelOut         *ChannelOut;
  MrcDimmOut            *DimmOut;
  MrcTimeBase           *TimeBase;
  MrcProfile            Profile;
  BOOLEAN               Flag;
  UINT8                 Controller;
  UINT8                 Channel;
  UINT8                 Dimm;
  UINT32                tCKmin;
  INT32                 MediumTimebase;
  INT32                 FineTimebase;
  UINT32                TimingMTB;
  INT32                 TimingFTB;
  UINT32                Actual[MAX_PROFILE];
  UINT32                Calculated;

  Inputs  = &MrcData->Inputs;
  Outputs = &MrcData->Outputs;
  Debug   = &Outputs->Debug;
  Flag    = FALSE;

  //
  // Find the smallest timing value for all the given DIMMs, for all the profiles.
  //
  for (Profile = STD_PROFILE; Profile < MAX_PROFILE; Profile++) {
    if (!(MrcXmpTimingProfileEnabled (MrcData, Profile))) {
      continue;
    }
    Actual[Profile] = 0;
    for (Controller = 0; Controller < MAX_CONTROLLERS; Controller++) {
      ControllerIn  = &Inputs->Controller[Controller];
      ControllerOut = &Outputs->Controller[Controller];
      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        ChannelIn   = &ControllerIn->Channel[Channel];
        ChannelOut  = &ControllerOut->Channel[Channel];
        for (Dimm = 0; Dimm < MAX_DIMMS_IN_CHANNEL; Dimm++) {
          DimmIn  = &ChannelIn->Dimm[Dimm];
          DimmOut = &ChannelOut->Dimm[Dimm];
          if ((DIMM_PRESENT == DimmOut->Status) && (DimmOut->DdrType == MRC_DDR_TYPE_LPDDR3)) {
            Spd            = &DimmIn->Spd.Data;
            Calculated     = 0;
            tCKmin         = DimmOut->Timing[Profile].tCK;
            TimeBase       = &ChannelOut->TimeBase[Dimm][Profile];
            MediumTimebase = TimeBase->Mtb;
            FineTimebase   = TimeBase->Ftb;
            if (tCKmin > 0) {
              if (Spd->Ddr3.General.DramDeviceType.Bits.Type == MRC_SPD_LPDDR3_SDRAM_TYPE_NUMBER) {
                TimingMTB = Spd->Ddr3.General.tRPab.Bits.tRPab;
                TimingFTB = Spd->Ddr3.General.tRPabFine.Bits.tRPabFine;
              } else {
                TimingMTB  = Spd->Lpddr.Base.tRPab.Bits.tRPab;
                TimingFTB  = Spd->Lpddr.Base.tRPabFine.Bits.tRPabFine;
              }
              Calculated = ((MediumTimebase * TimingMTB) + (FineTimebase * TimingFTB) - (tCKmin / 100) + (tCKmin - 1)) / tCKmin;
            }

            if ((Calculated >= TRPABMINPOSSIBLE) && ((Calculated - DimmOut->Timing[Profile].tRCDtRP) <= 3)) {
              Actual[Profile] = MAX (Actual[Profile], Calculated);
            }
            if (!Flag) {
              Flag = TRUE;
              MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "  %s:\n  %s\n", tRPabString, HeaderString);
              MRC_DEBUG_MSG (
                Debug,
                MSG_LEVEL_NOTE,
                "  % 7u % 10u % 8u % 5u %6u\n",
                Profile,
                Controller,
                Channel,
                Dimm,
                Calculated
                );
            } //Flag
          } //DimmOut->Status
        } //Dimm
      } //Channel
    } //Controller
  } //Profile

  if (Flag) {
    //
    // Set the best case timing for all controllers/channels/dimms, for each profile.
    //
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "    %s%u:", BestCaseString, MAX_PROFILE - 1);
    for (Profile = STD_PROFILE; Profile < MAX_PROFILE; Profile++) {
    if (!(MrcXmpTimingProfileEnabled (MrcData, Profile))) {
        continue;
      }
      for (Controller = 0; Controller < MAX_CONTROLLERS; Controller++) {
        ControllerOut = &Outputs->Controller[Controller];
        for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
          ChannelOut = &ControllerOut->Channel[Channel];
          for (Dimm = 0; Dimm < MAX_DIMMS_IN_CHANNEL; Dimm++) {
            DimmOut = &ChannelOut->Dimm[Dimm];
            DimmOut->Timing[Profile].tRPab    = (UINT16) Actual[Profile];
            ChannelOut->Timing[Profile].tRPab = (UINT16) Actual[Profile];
          }
        }
      }
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, " %u", Actual[Profile]);
    }
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n");
  }

  return TRUE;

}

/**
  Calculate the minimum tRRD timing value for the given memory frequency.
    MRC should not set tRRD below 4nCK for all frequencies.

    @param[in, out] MrcData - Pointer to MrcData data structure.

    @retval TRUE
**/
static
BOOLEAN
GetChannelDimmtRRD (
  IN OUT MrcParameters *const MrcData
  )
{
  const MrcInput        *Inputs;
  const MrcControllerIn *ControllerIn;
  const MrcChannelIn    *ChannelIn;
  const MrcDimmIn       *DimmIn;
  const MrcSpd          *Spd;
  MrcDebug              *Debug;
  MrcOutput             *Outputs;
  MrcControllerOut      *ControllerOut;
  MrcChannelOut         *ChannelOut;
  MrcDimmOut            *DimmOut;
  MrcTimeBase           *TimeBase;
  MrcProfile            Profile;
  UINT8                 Controller;
  UINT8                 Channel;
  UINT8                 Dimm;
  UINT32                tCKmin;
  UINT32                TimingMTB;
  INT32                 MediumTimebase;
  INT32                 FineTimebase;
  UINT32                Actual[MAX_PROFILE];
  UINT32                Calculated;
  UINT32                Index;
  UINT32                tRRDValue;
  BOOLEAN               FirstProfile;

  Inputs  = &MrcData->Inputs;
  Outputs = &MrcData->Outputs;
  Debug   = &Outputs->Debug;

  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "  %s:\n  %s\n", tRRDString, HeaderString);

  //
  // Find the smallest timing value for all the given DIMMs, for all the profiles.
  //
  for (Profile = STD_PROFILE; Profile < MAX_PROFILE; Profile++) {
    if (!(MrcXmpTimingProfileEnabled (MrcData, Profile))) {
      continue;
    }
    FirstProfile    = TRUE;
    tRRDValue       = 0;
    Actual[Profile] = 0;
    for (Controller = 0; Controller < MAX_CONTROLLERS; Controller++) {
      ControllerIn  = &Inputs->Controller[Controller];
      ControllerOut = &Outputs->Controller[Controller];
      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        ChannelIn   = &ControllerIn->Channel[Channel];
        ChannelOut  = &ControllerOut->Channel[Channel];
        for (Dimm = 0; Dimm < MAX_DIMMS_IN_CHANNEL; Dimm++) {
          DimmIn  = &ChannelIn->Dimm[Dimm];
          DimmOut = &ChannelOut->Dimm[Dimm];
          if (DIMM_PRESENT == DimmOut->Status) {
            Spd            = &DimmIn->Spd.Data;
            Calculated     = 0;
            tCKmin         = DimmOut->Timing[Profile].tCK;
            TimeBase       = &ChannelOut->TimeBase[Dimm][Profile];
            MediumTimebase = TimeBase->Mtb;
            FineTimebase   = TimeBase->Ftb;
            switch (Profile) {
              case XMP_PROFILE1:
              case XMP_PROFILE2:
                if (MrcDimmXmpProfileSupported (DimmOut, Profile)) {
                  Index = Profile - XMP_PROFILE1;
                  TimingMTB = Spd->Ddr3.Xmp.Data[Index].tRRDmin.Bits.tRRDmin;
                  Calculated = (tCKmin == 0) ? 0 : ((MediumTimebase * TimingMTB) - (tCKmin / 100) + (tCKmin - 1)) / tCKmin;
                } else {
                  Calculated = 0;
                }
                if (FirstProfile) {
                  tRRDValue = Calculated;
                  FirstProfile = FALSE;
                } else if (tRRDValue != Calculated) {
                  MRC_DEBUG_MSG (Debug, MSG_LEVEL_WARNING, "  %s\n", XmpDisableString);
                }
                break;
              case USER_PROFILE:
                if (DimmIn->Timing.tRRD > 0) {
                  Calculated = DimmIn->Timing.tRRD;
                  break;
                } else {
                  // In AUTO mode, so no break.
                }
              case STD_PROFILE:
              default:
                if (tCKmin > 0) {
                  if ((MRC_DDR_TYPE_DDR3 == DimmOut->DdrType) || (Spd->Ddr3.General.DramDeviceType.Bits.Type == MRC_SPD_LPDDR3_SDRAM_TYPE_NUMBER)) {
                    TimingMTB = Spd->Ddr3.General.tRRDmin.Bits.tRRDmin;
                    Calculated = ((MediumTimebase * TimingMTB) - (tCKmin / 100) + (tCKmin - 1)) / tCKmin;
                  } else if (MRC_DDR_TYPE_DDR4 == DimmOut->DdrType) {
                    Calculated = 0; // tRRD isn't used for DDR4
                  } else { // LPDDR3
                    Calculated = DIVIDECEIL ((10000000 - (tCKmin / 100)), tCKmin); // 10ns
                  }
                }
                break;
            } //switch

            Calculated = MAX (Calculated, TRRDMINPOSSIBLE);  // Make sure tRRD is at least 4 tCK
            Actual[Profile] = MAX (Actual[Profile], Calculated);
            MRC_DEBUG_MSG (
              Debug,
              MSG_LEVEL_NOTE,
              "  % 7u % 10u % 8u % 5u %6u\n",
              Profile,
              Controller,
              Channel,
              Dimm,
              Calculated
              );
          } //DimmOut->Status
        } //Dimm
      } //Channel
    } //Controller
  } //Profile

  //
  // Set the best case timing for all controllers/channels/dimms, for each profile.
  //
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "    %s%u:", BestCaseString, MAX_PROFILE - 1);
  for (Profile = STD_PROFILE; Profile < MAX_PROFILE; Profile++) {
    if (!(MrcXmpTimingProfileEnabled (MrcData, Profile))) {
      continue;
    }
    for (Controller = 0; Controller < MAX_CONTROLLERS; Controller++) {
      ControllerOut = &Outputs->Controller[Controller];
      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        ChannelOut = &ControllerOut->Channel[Channel];
        for (Dimm = 0; Dimm < MAX_DIMMS_IN_CHANNEL; Dimm++) {
          DimmOut = &ChannelOut->Dimm[Dimm];
          DimmOut->Timing[Profile].tRRD    = (UINT16) Actual[Profile];
          ChannelOut->Timing[Profile].tRRD = (UINT16) Actual[Profile];
        }
      }
    }
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, " %u", Actual[Profile]);
  }
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n");

  return TRUE;
}

/**
  Calculate the minimum tRRD same bank group timing value for the given memory frequency.

    @param[in, out] MrcData - Pointer to MrcData data structure.

    @retval TRUE if there are DIMMs present, otherwise FALSE.
**/
static
BOOLEAN
GetChannelDimmtRRD_L (
  IN OUT MrcParameters *const MrcData
  )
{
  const MrcInput        *Inputs;
  const MrcControllerIn *ControllerIn;
  const MrcChannelIn    *ChannelIn;
  const MrcDimmIn       *DimmIn;
  const MrcSpd          *Spd;
  MrcDebug              *Debug;
  MrcOutput             *Outputs;
  MrcControllerOut      *ControllerOut;
  MrcChannelOut         *ChannelOut;
  MrcDimmOut            *DimmOut;
  MrcTimeBase           *TimeBase;
  MrcProfile            Profile;
  UINT8                 Controller;
  UINT8                 Channel;
  UINT8                 Dimm;
  UINT32                tCKmin;
  UINT32                TimingMTB;
  INT32                 TimingFTB;
  INT32                 MediumTimebase;
  INT32                 FineTimebase;
  UINT32                Actual[MAX_PROFILE];
  UINT32                Calculated;
  UINT32                tRRDLValue;
  BOOLEAN               FirstProfile;

  const SPD_EXTREME_MEMORY_PROFILE_DATA_2_0  *Data2;

  Inputs  = &MrcData->Inputs;
  Outputs = &MrcData->Outputs;
  Debug   = &Outputs->Debug;

  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "  %s:\n  %s\n", tRRDLString, HeaderString);

  //
  // Find the smallest timing value for all the given DIMMs, for all the profiles.
  //
  for (Profile = STD_PROFILE; Profile < MAX_PROFILE; Profile++) {
    if (!(MrcXmpTimingProfileEnabled (MrcData, Profile))) {
      continue;
    }
    FirstProfile    = TRUE;
    tRRDLValue      = 0;
    Actual[Profile] = 0;
    for (Controller = 0; Controller < MAX_CONTROLLERS; Controller++) {
      ControllerIn  = &Inputs->Controller[Controller];
      ControllerOut = &Outputs->Controller[Controller];
      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        ChannelIn   = &ControllerIn->Channel[Channel];
        ChannelOut  = &ControllerOut->Channel[Channel];
        for (Dimm = 0; Dimm < MAX_DIMMS_IN_CHANNEL; Dimm++) {
          DimmIn  = &ChannelIn->Dimm[Dimm];
          DimmOut = &ChannelOut->Dimm[Dimm];
          if (DIMM_PRESENT == DimmOut->Status) {
            Spd            = &DimmIn->Spd.Data;
            Calculated     = 0;
            tCKmin         = DimmOut->Timing[Profile].tCK;
            TimeBase       = &ChannelOut->TimeBase[Dimm][Profile];
            MediumTimebase = TimeBase->Mtb;
            FineTimebase   = TimeBase->Ftb;
            switch (Profile) {
              case XMP_PROFILE1:
              case XMP_PROFILE2:
                if (MrcDimmXmpProfileSupported (DimmOut, Profile)) {
                  Data2 = &Spd->Ddr4.EndUser.Xmp.Data[Profile - XMP_PROFILE1];
                  TimingMTB = Data2->tRRD_Lmin.Bits.tRRDmin;
                  TimingFTB = Data2->tRRD_LminFine.Bits.tRRDminFine;
                  Calculated = (tCKmin == 0) ? 0 : ((MediumTimebase * TimingMTB) + (FineTimebase * TimingFTB) - (tCKmin / 100) + (tCKmin - 1)) / tCKmin;
                } else {
                  Calculated = 0;
                }
                if (FirstProfile) {
                  tRRDLValue = Calculated;
                  FirstProfile = FALSE;
                } else if (tRRDLValue != Calculated) {
                  Outputs->XmpProfileEnable = 0;
                  MRC_DEBUG_MSG (Debug, MSG_LEVEL_WARNING, "  %s\n", XmpDisableString);
                }
                break;
              case USER_PROFILE:
                if (DimmIn->Timing.tRRD_L > 0) {
                  Calculated = DimmIn->Timing.tRRD_L;
                  break;
                } else {
                  // In AUTO mode, so no break.
                }
              case STD_PROFILE:
              default:
                if (MRC_DDR_TYPE_DDR4 == DimmOut->DdrType) {
                  TimingMTB = Spd->Ddr4.Base.tRRD_Lmin.Bits.tRRDmin;
                  TimingFTB = Spd->Ddr4.Base.tRRD_LminFine.Bits.tRRDminFine;
                  Calculated = (tCKmin == 0) ? 0 : ((MediumTimebase * TimingMTB) + (FineTimebase * TimingFTB) - (tCKmin / 100) + (tCKmin - 1)) / tCKmin;
                }
                break;
            } //switch

            Actual[Profile] = MAX (Actual[Profile], Calculated);
            MRC_DEBUG_MSG (
              Debug,
              MSG_LEVEL_NOTE,
              "  % 7u % 10u % 8u % 5u %6u\n",
              Profile,
              Controller,
              Channel,
              Dimm,
              Calculated
              );
          } //DimmOut->Status
        } //Dimm
      } //Channel
    } //Controller
  } //Profile

  //
  // Set the best case timing for all controllers/channels/dimms, for each profile.
  //
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "    %s%u:", BestCaseString, MAX_PROFILE - 1);
  for (Profile = STD_PROFILE; Profile < MAX_PROFILE; Profile++) {
    if (!(MrcXmpTimingProfileEnabled (MrcData, Profile))) {
      continue;
    }
    for (Controller = 0; Controller < MAX_CONTROLLERS; Controller++) {
      ControllerOut = &Outputs->Controller[Controller];
      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        ChannelOut = &ControllerOut->Channel[Channel];
        for (Dimm = 0; Dimm < MAX_DIMMS_IN_CHANNEL; Dimm++) {
          DimmOut = &ChannelOut->Dimm[Dimm];
          DimmOut->Timing[Profile].tRRD_L    = (UINT16) Actual[Profile];
          ChannelOut->Timing[Profile].tRRD_L = (UINT16) Actual[Profile];
        }
      }
    }
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, " %u", Actual[Profile]);
  }
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n");

  return TRUE;
}

/**
  Calculate the minimum tRRD different bank group timing value for the given memory frequency.

    @param[in, out] MrcData - Pointer to MrcData data structure.

    @retval TRUE if there are DIMMs present, otherwise FALSE.
**/
static
BOOLEAN
GetChannelDimmtRRD_S (
  IN OUT MrcParameters *const MrcData
  )
{
  const MrcInput        *Inputs;
  const MrcControllerIn *ControllerIn;
  const MrcChannelIn    *ChannelIn;
  const MrcDimmIn       *DimmIn;
  const MrcSpd          *Spd;
  MrcDebug              *Debug;
  MrcOutput             *Outputs;
  MrcControllerOut      *ControllerOut;
  MrcChannelOut         *ChannelOut;
  MrcDimmOut            *DimmOut;
  MrcTimeBase           *TimeBase;
  MrcProfile            Profile;
  UINT8                 Controller;
  UINT8                 Channel;
  UINT8                 Dimm;
  UINT32                tCKmin;
  UINT32                TimingMTB;
  INT32                 TimingFTB;
  INT32                 MediumTimebase;
  INT32                 FineTimebase;
  UINT32                Actual[MAX_PROFILE];
  UINT32                Calculated;
  UINT32                tRRDSValue;
  BOOLEAN               FirstProfile;

  const SPD_EXTREME_MEMORY_PROFILE_DATA_2_0  *Data2;

  Inputs  = &MrcData->Inputs;
  Outputs = &MrcData->Outputs;
  Debug   = &Outputs->Debug;

  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "  %s:\n  %s\n", tRRDSString, HeaderString);

  //
  // Find the smallest timing value for all the given DIMMs, for all the profiles.
  //
  for (Profile = STD_PROFILE; Profile < MAX_PROFILE; Profile++) {
    if (!(MrcXmpTimingProfileEnabled (MrcData, Profile))) {
      continue;
    }
    FirstProfile    = TRUE;
    tRRDSValue      = 0;
    Actual[Profile] = 0;
    for (Controller = 0; Controller < MAX_CONTROLLERS; Controller++) {
      ControllerIn  = &Inputs->Controller[Controller];
      ControllerOut = &Outputs->Controller[Controller];
      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        ChannelIn   = &ControllerIn->Channel[Channel];
        ChannelOut  = &ControllerOut->Channel[Channel];
        for (Dimm = 0; Dimm < MAX_DIMMS_IN_CHANNEL; Dimm++) {
          DimmIn  = &ChannelIn->Dimm[Dimm];
          DimmOut = &ChannelOut->Dimm[Dimm];
          if (DIMM_PRESENT == DimmOut->Status) {
            Spd            = &DimmIn->Spd.Data;
            Calculated     = 0;
            tCKmin         = DimmOut->Timing[Profile].tCK;
            TimeBase       = &ChannelOut->TimeBase[Dimm][Profile];
            MediumTimebase = TimeBase->Mtb;
            FineTimebase   = TimeBase->Ftb;
            switch (Profile) {
              case XMP_PROFILE1:
              case XMP_PROFILE2:
                if (MrcDimmXmpProfileSupported (DimmOut, Profile)) {
                  Data2 = &Spd->Ddr4.EndUser.Xmp.Data[Profile - XMP_PROFILE1];
                  TimingMTB = Data2->tRRD_Smin.Bits.tRRDmin;
                  TimingFTB = Data2->tRRD_SminFine.Bits.tRRDminFine;
                  Calculated = (tCKmin == 0) ? 0 : ((MediumTimebase * TimingMTB) + (FineTimebase * TimingFTB) - (tCKmin / 100) + (tCKmin - 1)) / tCKmin;
                } else {
                  Calculated = 0;
                }
                if (FirstProfile) {
                  tRRDSValue = Calculated;
                  FirstProfile = FALSE;
                } else if (tRRDSValue != Calculated) {
                  Outputs->XmpProfileEnable = 0;
                  MRC_DEBUG_MSG (Debug, MSG_LEVEL_WARNING, "  %s\n", XmpDisableString);
                }
                break;
              case USER_PROFILE:
                if (DimmIn->Timing.tRRD_S > 0) {
                  Calculated = DimmIn->Timing.tRRD_S;
                  break;
                } else {
                  // In AUTO mode, so no break.
                }
              case STD_PROFILE:
              default:
                if (MRC_DDR_TYPE_DDR4 == DimmOut->DdrType) {
                  TimingMTB = (UINT32) Spd->Ddr4.Base.tRRD_Smin.Bits.tRRDmin;
                  TimingFTB = (INT32) Spd->Ddr4.Base.tRRD_SminFine.Bits.tRRDminFine;
                  Calculated = (tCKmin == 0) ? 0 : ((MediumTimebase * TimingMTB) + (FineTimebase * TimingFTB) - (tCKmin / 100) + (tCKmin - 1)) / tCKmin;
                }
                break;
            } //switch

            Actual[Profile] = MAX (Actual[Profile], Calculated);
            MRC_DEBUG_MSG (
              Debug,
              MSG_LEVEL_NOTE,
              "  % 7u % 10u % 8u % 5u %6u\n",
              Profile,
              Controller,
              Channel,
              Dimm,
              Calculated
              );
          } //DimmOut->Status
        } //Dimm
      } //Channel
    } //Controller
  } //Profile

  //
  // Set the best case timing for all controllers/channels/dimms, for each profile.
  //
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "    %s%u:", BestCaseString, MAX_PROFILE - 1);
  for (Profile = STD_PROFILE; Profile < MAX_PROFILE; Profile++) {
    if (!(MrcXmpTimingProfileEnabled (MrcData, Profile))) {
      continue;
    }
    for (Controller = 0; Controller < MAX_CONTROLLERS; Controller++) {
      ControllerOut = &Outputs->Controller[Controller];
      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        ChannelOut = &ControllerOut->Channel[Channel];
        for (Dimm = 0; Dimm < MAX_DIMMS_IN_CHANNEL; Dimm++) {
          DimmOut = &ChannelOut->Dimm[Dimm];
          DimmOut->Timing[Profile].tRRD_S    = (UINT16) Actual[Profile];
          ChannelOut->Timing[Profile].tRRD_S = (UINT16) Actual[Profile];
        }
      }
    }
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, " %u", Actual[Profile]);
  }
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n");

  return TRUE;
}

/**
  Calculate the tRTP value for DDR4.
  JEDEC Spec: tRTP = max (4nCK, 7.5ns)

    @param[in] tCK - the memory DCLK in femtoseconds.

    @retval DDR4 tRTP in DCLK units
**/
static
UINT32
GetDdr4tRTP (
  IN const UINT32 tCK
  )
{
  UINT32 tRTP;

  tRTP = (tCK == 0) ? 0 : DIVIDECEIL ((7500000 - (tCK / 100)), tCK); // 7.5ns
  tRTP = RANGE (tRTP, DDR4_TRTPMINPOSSIBLE, DDR4_TRTPMAXPOSSIBLE);   // JEDEC limits
  if (tRTP == 11) {
    tRTP++;         // 11 is not a valid value, use 12
  }
  return tRTP;
}

/**
  Calculate the tWR value for DDR4.
  JEDEC Spec: tWR = 15ns

    @param[in] tCK - the memory DCLK in femtoseconds.

    @retval DDR4 tWR in DCLK units
**/
static
UINT32
GetDdr4tWR (
  IN const UINT32 tCK
  )
{
  UINT32 tWR;

  tWR = (tCK == 0) ? 0 : DIVIDECEIL ((15000000 - (tCK / 100)), tCK); // 15ns
  if (tWR % 2) {
    tWR++;          // Calculated tWR is odd number, round up to next even number
  }
  tWR = RANGE (tWR, DDR4_TWRMINPOSSIBLE, DDR4_TWRMAXPOSSIBLE);  // JEDEC limits
  if (tWR == 22) {
    tWR = 24;       // tWR of 22 is not a valid value, use the next one
  }
  return tWR;
}

/**
  Calculate the tWR value for LPDDR3
  JEDEC Spec: tWR = 15ns

    @param[in] tCK     - the memory DCLK in femtoseconds.

    @retval LPDDR tWR in DCLK units
**/
static
UINT32
GetLpddrtWR (
  IN const UINT32     tCK
  )
{
  UINT32 tWR;

  tWR = (tCK == 0) ? 0 : DIVIDECEIL ((15000000 - (tCK / 100)), tCK); // 15ns
  if ((tWR > 12) && (tWR % 2)) {
    tWR++;
  }
  if (tWR > 16) {
    tWR = 16;
  }

  return tWR;
}

/**
  Calculate the minimum tRTP timing value for the given memory frequency.

    @param[in, out] MrcData - Pointer to MrcData data structure.

    @retval TRUE if there are DIMMs present, otherwise FALSE.
**/
static
BOOLEAN
GetChannelDimmtRTP (
  IN OUT MrcParameters *const MrcData
  )
{
  const MrcInput        *Inputs;
  const MrcControllerIn *ControllerIn;
  const MrcChannelIn    *ChannelIn;
  const MrcDimmIn       *DimmIn;
  const MrcSpd          *Spd;
  MrcDebug              *Debug;
  MrcOutput             *Outputs;
  MrcControllerOut      *ControllerOut;
  MrcChannelOut         *ChannelOut;
  MrcDimmOut            *DimmOut;
  MrcTimeBase           *TimeBase;
  MrcProfile            Profile;
  UINT8                 Controller;
  UINT8                 Channel;
  UINT8                 Dimm;
  UINT32                tCKmin;
  UINT32                TimingMTB;
  INT32                 MediumTimebase;
  INT32                 FineTimebase;
  UINT32                Actual[MAX_PROFILE];
  UINT32                Calculated;
  UINT32                tRTPValue;
  BOOLEAN               FirstProfile;

  const SPD_EXTREME_MEMORY_PROFILE_DATA  *Data1;
  UINT32                                  Index;

  Inputs      = &MrcData->Inputs;
  Outputs     = &MrcData->Outputs;
  Debug       = &Outputs->Debug;

  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "  %s:\n  %s\n", tRTPString, HeaderString);

  //
  // Find the smallest timing value for all the given DIMMs, for all the profiles.
  //
  for (Profile = STD_PROFILE; Profile < MAX_PROFILE; Profile++) {
    if (!(MrcXmpTimingProfileEnabled (MrcData, Profile))) {
      continue;
    }
    FirstProfile    = TRUE;
    tRTPValue       = 0;
    Actual[Profile] = 0;
    for (Controller = 0; Controller < MAX_CONTROLLERS; Controller++) {
      ControllerIn  = &Inputs->Controller[Controller];
      ControllerOut = &Outputs->Controller[Controller];
      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        ChannelIn   = &ControllerIn->Channel[Channel];
        ChannelOut  = &ControllerOut->Channel[Channel];
        for (Dimm = 0; Dimm < MAX_DIMMS_IN_CHANNEL; Dimm++) {
          DimmIn  = &ChannelIn->Dimm[Dimm];
          DimmOut = &ChannelOut->Dimm[Dimm];
          if (DIMM_PRESENT == DimmOut->Status) {
            Spd            = &DimmIn->Spd.Data;
            Calculated     = 0;
            tCKmin         = DimmOut->Timing[Profile].tCK;
            TimeBase       = &ChannelOut->TimeBase[Dimm][Profile];
            MediumTimebase = TimeBase->Mtb;
            FineTimebase   = TimeBase->Ftb;
            switch (Profile) {
              case XMP_PROFILE1:
              case XMP_PROFILE2:
                if (MrcDimmXmpProfileSupported (DimmOut, Profile)) {
                  Index = Profile - XMP_PROFILE1;
                  if (MRC_DDR_TYPE_DDR3 == DimmOut->DdrType) {
                    Data1 = &Spd->Ddr3.Xmp.Data[Index];
                    TimingMTB = Data1->tRTPmin.Bits.tRTPmin;
                    Calculated = (tCKmin == 0) ? 0 : ((MediumTimebase * TimingMTB) - (tCKmin / 100) + (tCKmin - 1)) / tCKmin;
                  } else {
                    Calculated = GetDdr4tRTP (tCKmin);
                  }
                } else {
                  Calculated = 0;
                }
                if (FirstProfile) {
                  tRTPValue = Calculated;
                  FirstProfile = FALSE;
                } else if (tRTPValue != Calculated) {
                  Outputs->XmpProfileEnable = 0;
                  MRC_DEBUG_MSG (Debug, MSG_LEVEL_WARNING, "  %s\n", XmpDisableString);
                }
                break;
              case USER_PROFILE:
                if (DimmIn->Timing.tRTP > 0) {
                  Calculated = DimmIn->Timing.tRTP;
                  break;
                } else {
                  // In AUTO mode, so no break.
                }
              case STD_PROFILE:
              default:
                if (tCKmin > 0) {
                  if (DimmOut->DdrType == MRC_DDR_TYPE_DDR4) {
                    Calculated = GetDdr4tRTP (tCKmin);
                  } else if ((DimmOut->DdrType == MRC_DDR_TYPE_LPDDR3) && (Spd->Ddr3.General.DramDeviceType.Bits.Type != MRC_SPD_LPDDR3_SDRAM_TYPE_NUMBER)) {
                    Calculated = DIVIDECEIL ((7500000 - (tCKmin / 100)), tCKmin); // 7.5ns
                  } else {
                    TimingMTB = Spd->Ddr3.General.tRTPmin.Bits.tRTPmin;
                    Calculated = ((MediumTimebase * TimingMTB) - (tCKmin / 100) + (tCKmin - 1)) / tCKmin;
                  }
                }
                break;
            } //switch

            if ((DimmOut->DdrType == MRC_DDR_TYPE_LPDDR3) && (Calculated < LPDDR3_TRTPMINPOSSIBLE)) {
              Calculated = LPDDR3_TRTPMINPOSSIBLE;
            }

            Actual[Profile] = MAX (Actual[Profile], Calculated);
            MRC_DEBUG_MSG (
              Debug,
              MSG_LEVEL_NOTE,
              "  % 7u % 10u % 8u % 5u %6u\n",
              Profile,
              Controller,
              Channel,
              Dimm,
              Calculated
              );
          } //DimmOut->Status
        } //Dimm
      } //Channel
    } //Controller
  } //Profile

  //
  // Set the best case timing for all controllers/channels/dimms, for each profile.
  //
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "    %s%u:", BestCaseString, MAX_PROFILE - 1);
  for (Profile = STD_PROFILE; Profile < MAX_PROFILE; Profile++) {
    if (!(MrcXmpTimingProfileEnabled (MrcData, Profile))) {
      continue;
    }
    for (Controller = 0; Controller < MAX_CONTROLLERS; Controller++) {
      ControllerOut = &Outputs->Controller[Controller];
      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        ChannelOut = &ControllerOut->Channel[Channel];
        for (Dimm = 0; Dimm < MAX_DIMMS_IN_CHANNEL; Dimm++) {
          DimmOut = &ChannelOut->Dimm[Dimm];
          DimmOut->Timing[Profile].tRTP    = (UINT16) Actual[Profile];
          ChannelOut->Timing[Profile].tRTP = (UINT16) Actual[Profile];
        }
      }
    }
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, " %u", Actual[Profile]);
  }
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n");

  return TRUE;
}

/**
  Calculate the minimum tWR timing value for the given memory frequency.

    @param[in, out] MrcData - Pointer to MrcData data structure.

    @retval TRUE if there are DIMMs present, otherwise FALSE.
**/
static
BOOLEAN
GetChannelDimmtWR (
  IN OUT MrcParameters *const MrcData
  )
{
  const MrcInput        *Inputs;
  const MrcControllerIn *ControllerIn;
  const MrcChannelIn    *ChannelIn;
  const MrcDimmIn       *DimmIn;
  const MrcSpd          *Spd;
  MrcDebug              *Debug;
  MrcOutput             *Outputs;
  MrcControllerOut      *ControllerOut;
  MrcChannelOut         *ChannelOut;
  MrcDimmOut            *DimmOut;
  MrcTimeBase           *TimeBase;
  MrcProfile            Profile;
  UINT8                 Controller;
  UINT8                 Channel;
  UINT8                 Dimm;
  UINT32                tCKmin;
  UINT32                TimingMTB;
  INT32                 MediumTimebase;
  INT32                 FineTimebase;
  UINT32                Actual[MAX_PROFILE];
  UINT32                Calculated;
  UINT32                tWRValue;
  BOOLEAN               FirstProfile;

  const SPD_EXTREME_MEMORY_PROFILE_DATA  *Data1;
  UINT32                                  Index;

  Inputs      = &MrcData->Inputs;
  Outputs     = &MrcData->Outputs;
  Debug       = &Outputs->Debug;

  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "  %s:\n  %s\n", tWRString, HeaderString);

  //
  // Find the smallest timing value for all the given DIMMs, for all the profiles.
  //
  for (Profile = STD_PROFILE; Profile < MAX_PROFILE; Profile++) {
    if (!(MrcXmpTimingProfileEnabled (MrcData, Profile))) {
      continue;
    }
    FirstProfile    = TRUE;
    tWRValue        = 0;
    Actual[Profile] = 0;
    for (Controller = 0; Controller < MAX_CONTROLLERS; Controller++) {
      ControllerIn  = &Inputs->Controller[Controller];
      ControllerOut = &Outputs->Controller[Controller];
      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        ChannelIn   = &ControllerIn->Channel[Channel];
        ChannelOut  = &ControllerOut->Channel[Channel];
        for (Dimm = 0; Dimm < MAX_DIMMS_IN_CHANNEL; Dimm++) {
          DimmIn  = &ChannelIn->Dimm[Dimm];
          DimmOut = &ChannelOut->Dimm[Dimm];
          if (DIMM_PRESENT == DimmOut->Status) {
            Spd            = &DimmIn->Spd.Data;
            Calculated     = 0;
            tCKmin         = DimmOut->Timing[Profile].tCK;
            TimeBase       = &ChannelOut->TimeBase[Dimm][Profile];
            MediumTimebase = TimeBase->Mtb;
            FineTimebase   = TimeBase->Ftb;
            switch (Profile) {
              case XMP_PROFILE1:
              case XMP_PROFILE2:
                if (MrcDimmXmpProfileSupported (DimmOut, Profile)) {
                  Index = Profile - XMP_PROFILE1;
                  if (MRC_DDR_TYPE_DDR3 == DimmOut->DdrType) {
                    Data1 = &Spd->Ddr3.Xmp.Data[Index];
                    TimingMTB = Data1->tWRmin.Bits.tWRmin;
                    Calculated = (tCKmin == 0) ? 0 : ((MediumTimebase * TimingMTB) - (tCKmin / 100) + (tCKmin - 1)) / tCKmin;
                  } else {
                    Calculated = GetDdr4tWR (tCKmin);
                  }
                } else {
                  Calculated = 0;
                }
                if (FirstProfile) {
                  tWRValue = Calculated;
                  FirstProfile = FALSE;
                } else if (tWRValue != Calculated) {
                  Outputs->XmpProfileEnable = 0;
                  MRC_DEBUG_MSG (Debug, MSG_LEVEL_WARNING, "  %s\n", XmpDisableString);
                }
                break;
              case USER_PROFILE:
                if (DimmIn->Timing.tWR > 0) {
                  Calculated = DimmIn->Timing.tWR;
                  break;
                } else {
                  // In AUTO mode, so no break.
                }
              case STD_PROFILE:
              default:
                if (tCKmin > 0) {
                  if (DimmOut->DdrType == MRC_DDR_TYPE_DDR4) {
                    Calculated = GetDdr4tWR (tCKmin);
                  } else if ((DimmOut->DdrType == MRC_DDR_TYPE_LPDDR3) && (Spd->Ddr3.General.DramDeviceType.Bits.Type != MRC_SPD_LPDDR3_SDRAM_TYPE_NUMBER)) {
                    Calculated = GetLpddrtWR (tCKmin);
                  } else {
                    TimingMTB = Spd->Ddr3.General.tWRmin.Bits.tWRmin;
                    Calculated = ((MediumTimebase * TimingMTB) - (tCKmin / 100) + (tCKmin - 1)) / tCKmin;
                  }
                }
                break;
            } //switch

            //
            // Special case, tWRmin values of 9, 11, 13, and 15 are not supported by DDR3 Mode Register 0 (MR0).
            // If we see one of these values, then add one clock to it in order to make it valid.
            //
            if ((DimmOut->DdrType == MRC_DDR_TYPE_DDR3) && ((9 == Calculated) || (11 == Calculated) || (13 == Calculated) || (15 == Calculated))) {
              Calculated++;
            }
            Actual[Profile] = MAX (Actual[Profile], Calculated);
            MRC_DEBUG_MSG (
              Debug,
              MSG_LEVEL_NOTE,
              "  % 7u % 10u % 8u % 5u %6u\n",
              Profile,
              Controller,
              Channel,
              Dimm,
              Calculated
              );
          } //DimmOut->Status
        } //Dimm
      } //Channel
    } //Controller
  } //Profile

  //
  // Set the best case timing for all controllers/channels/dimms, for each profile.
  //
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "    %s%u:", BestCaseString, MAX_PROFILE - 1);
  for (Profile = STD_PROFILE; Profile < MAX_PROFILE; Profile++) {
    if (!(MrcXmpTimingProfileEnabled (MrcData, Profile))) {
      continue;
    }
    for (Controller = 0; Controller < MAX_CONTROLLERS; Controller++) {
      ControllerOut = &Outputs->Controller[Controller];
      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        ChannelOut = &ControllerOut->Channel[Channel];
        for (Dimm = 0; Dimm < MAX_DIMMS_IN_CHANNEL; Dimm++) {
          DimmOut = &ChannelOut->Dimm[Dimm];
          DimmOut->Timing[Profile].tWR    = (UINT16) Actual[Profile];
          ChannelOut->Timing[Profile].tWR = (UINT16) Actual[Profile];
        }
      }
    }
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, " %u", Actual[Profile]);
  }
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n");

  return TRUE;
}

/**
  Calculate the minimum tWTR timing value for the given memory frequency.

    @param[in, out] MrcData - Pointer to MrcData data structure.

    @retval TRUE if there are DIMMs present, otherwise FALSE.
**/
static
BOOLEAN
GetChannelDimmtWTR (
  IN OUT MrcParameters *const MrcData
  )
{
  const MrcInput        *Inputs;
  const MrcControllerIn *ControllerIn;
  const MrcChannelIn    *ChannelIn;
  const MrcDimmIn       *DimmIn;
  const MrcSpd          *Spd;
  MrcDebug              *Debug;
  MrcOutput             *Outputs;
  MrcControllerOut      *ControllerOut;
  MrcChannelOut         *ChannelOut;
  MrcDimmOut            *DimmOut;
  MrcTimeBase           *TimeBase;
  MrcProfile            Profile;
  UINT8                 Controller;
  UINT8                 Channel;
  UINT8                 Dimm;
  UINT32                tCKmin;
  UINT32                TimingMTB;
  INT32                 MediumTimebase;
  INT32                 FineTimebase;
  UINT32                Actual[MAX_PROFILE];
  UINT32                Calculated;
  UINT32                Index;
  UINT32                tWTRValue;
  BOOLEAN               FirstProfile;

  Inputs  = &MrcData->Inputs;
  Outputs = &MrcData->Outputs;
  Debug   = &Outputs->Debug;

  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "  %s:\n  %s\n", tWTRString, HeaderString);

  //
  // Find the smallest timing value for all the given DIMMs, for all the profiles.
  //
  for (Profile = STD_PROFILE; Profile < MAX_PROFILE; Profile++) {
    if (!(MrcXmpTimingProfileEnabled (MrcData, Profile))) {
      continue;
    }
    FirstProfile    = TRUE;
    tWTRValue       = 0;
    Actual[Profile] = 0;
    for (Controller = 0; Controller < MAX_CONTROLLERS; Controller++) {
      ControllerIn  = &Inputs->Controller[Controller];
      ControllerOut = &Outputs->Controller[Controller];
      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        ChannelIn   = &ControllerIn->Channel[Channel];
        ChannelOut  = &ControllerOut->Channel[Channel];
        for (Dimm = 0; Dimm < MAX_DIMMS_IN_CHANNEL; Dimm++) {
          DimmIn  = &ChannelIn->Dimm[Dimm];
          DimmOut = &ChannelOut->Dimm[Dimm];
          if (DIMM_PRESENT == DimmOut->Status) {
            Spd            = &DimmIn->Spd.Data;
            Calculated     = 0;
            tCKmin         = DimmOut->Timing[Profile].tCK;
            TimeBase       = &ChannelOut->TimeBase[Dimm][Profile];
            MediumTimebase = TimeBase->Mtb;
            FineTimebase   = TimeBase->Ftb;
            switch (Profile) {
              case XMP_PROFILE1:
              case XMP_PROFILE2:
                if (MrcDimmXmpProfileSupported (DimmOut, Profile)) {
                  if (tCKmin > 0) {
                    if (MRC_DDR_TYPE_DDR3 == DimmOut->DdrType) {
                      Index = Profile - XMP_PROFILE1;
                      TimingMTB = Spd->Ddr3.Xmp.Data[Index].tWTRmin.Bits.tWTRmin;
                      Calculated = ((MediumTimebase * TimingMTB) - (tCKmin / 100) + (tCKmin - 1)) / tCKmin;
                    }
                  }
                }
                if (FirstProfile) {
                  tWTRValue = Calculated;
                  FirstProfile = FALSE;
                } else if (tWTRValue != Calculated) {
                  Outputs->XmpProfileEnable = 0;
                  MRC_DEBUG_MSG (Debug, MSG_LEVEL_WARNING, "  %s\n", XmpDisableString);
                }
                break;
              case USER_PROFILE:
                if (DimmIn->Timing.tWTR > 0) {
                  Calculated = DimmIn->Timing.tWTR;
                  break;
                } else {
                  // In AUTO mode, so no break.
                }
              case STD_PROFILE:
              default:
                if (tCKmin > 0) {
                  if ((MRC_DDR_TYPE_DDR3 == DimmOut->DdrType) || (Spd->Ddr3.General.DramDeviceType.Bits.Type == MRC_SPD_LPDDR3_SDRAM_TYPE_NUMBER)) {
                    TimingMTB = Spd->Ddr3.General.tWTRmin.Bits.tWTRmin;
                    Calculated = ((MediumTimebase * TimingMTB) - (tCKmin / 100) + (tCKmin - 1)) / tCKmin;
                  } else if (MRC_DDR_TYPE_LPDDR3 == DimmOut->DdrType) {
                    Calculated = DIVIDECEIL ((7500000 - (tCKmin / 100)), tCKmin); // 7.5ns
                  }
                }
                break;
            } //switch

            Actual[Profile] = MAX (Actual[Profile], Calculated);
            MRC_DEBUG_MSG (
              Debug,
              MSG_LEVEL_NOTE,
              "  % 7u % 10u % 8u % 5u %6u\n",
              Profile,
              Controller,
              Channel,
              Dimm,
              Calculated
              );
          } //DimmOut->Status
        } //Dimm
      } //Channel
    } //Controller
  } //Profile

  //
  // Set the best case timing for all controllers/channels/dimms, for each profile.
  //
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "    %s%u:", BestCaseString, MAX_PROFILE - 1);
  for (Profile = STD_PROFILE; Profile < MAX_PROFILE; Profile++) {
    if (!(MrcXmpTimingProfileEnabled (MrcData, Profile))) {
      continue;
    }
    for (Controller = 0; Controller < MAX_CONTROLLERS; Controller++) {
      ControllerOut = &Outputs->Controller[Controller];
      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        ChannelOut = &ControllerOut->Channel[Channel];
        for (Dimm = 0; Dimm < MAX_DIMMS_IN_CHANNEL; Dimm++) {
          DimmOut = &ChannelOut->Dimm[Dimm];
          DimmOut->Timing[Profile].tWTR    = (UINT16) Actual[Profile];
          ChannelOut->Timing[Profile].tWTR = (UINT16) Actual[Profile];
        }
      }
    }
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, " %u", Actual[Profile]);
  }
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n");

  return TRUE;
}

/**
  Calculate the tWTR_L timing value for the given memory frequency.

    @param[in, out] MrcData - Pointer to MrcData data structure.

    @retval TRUE if there are DIMMs present, otherwise FALSE.
**/
static
BOOLEAN
GetChannelDimmtWTR_L (
  IN OUT MrcParameters *const MrcData
  )
{
  const MrcInput        *Inputs;
  const MrcControllerIn *ControllerIn;
  const MrcChannelIn    *ChannelIn;
  const MrcDimmIn       *DimmIn;
  const MrcSpd          *Spd;
  MrcDebug              *Debug;
  MrcOutput             *Outputs;
  MrcControllerOut      *ControllerOut;
  MrcChannelOut         *ChannelOut;
  MrcDimmOut            *DimmOut;
  MrcProfile            Profile;
  UINT8                 Controller;
  UINT8                 Channel;
  UINT8                 Dimm;
  UINT32                tCKmin;
  UINT32                Actual[MAX_PROFILE];
  UINT32                Calculated;
  UINT32                tWTRLValue;
  BOOLEAN               FirstProfile;

  Inputs  = &MrcData->Inputs;
  Outputs = &MrcData->Outputs;
  Debug   = &Outputs->Debug;

  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "  %s:\n  %s\n", tWTRLString, HeaderString);

  //
  // Find the smallest timing value for all the given DIMMs, for all the profiles.
  //
  for (Profile = STD_PROFILE; Profile < MAX_PROFILE; Profile++) {
    if (!(MrcXmpTimingProfileEnabled (MrcData, Profile))) {
      continue;
    }
    FirstProfile    = TRUE;
    tWTRLValue      = 0;
    Actual[Profile] = 0;
    for (Controller = 0; Controller < MAX_CONTROLLERS; Controller++) {
      ControllerIn  = &Inputs->Controller[Controller];
      ControllerOut = &Outputs->Controller[Controller];
      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        ChannelIn   = &ControllerIn->Channel[Channel];
        ChannelOut  = &ControllerOut->Channel[Channel];
        for (Dimm = 0; Dimm < MAX_DIMMS_IN_CHANNEL; Dimm++) {
          DimmIn  = &ChannelIn->Dimm[Dimm];
          DimmOut = &ChannelOut->Dimm[Dimm];
          if (DIMM_PRESENT == DimmOut->Status) {
            Spd            = &DimmIn->Spd.Data;
            Calculated     = 0;
            tCKmin         = DimmOut->Timing[Profile].tCK;
            switch (Profile) {
              case XMP_PROFILE1:
              case XMP_PROFILE2:
                if (MRC_DDR_TYPE_DDR4 == DimmOut->DdrType) {
                  Calculated = (tCKmin == 0) ? 0 : (7500000 - (tCKmin / 100) + tCKmin - 1) / tCKmin; // 7.5ns
                }
                if (FirstProfile) {
                  tWTRLValue = Calculated;
                  FirstProfile = FALSE;
                } else if (tWTRLValue != Calculated) {
                  Outputs->XmpProfileEnable = 0;
                  MRC_DEBUG_MSG (Debug, MSG_LEVEL_WARNING, "  %s\n", XmpDisableString);
                }
                break;
              case USER_PROFILE:
                if (DimmIn->Timing.tWTR_L > 0) {
                  Calculated = DimmIn->Timing.tWTR_L;
                  break;
                } else {
                  // In AUTO mode, so no break.
                }
              case STD_PROFILE:
              default:
                if (MRC_DDR_TYPE_DDR4 == DimmOut->DdrType) {
                  Calculated = (tCKmin == 0) ? 0 : (7500000 - (tCKmin / 100) + tCKmin - 1) / tCKmin; // 7.5ns
                }
                break;
            } //switch

            Actual[Profile] = MAX (Actual[Profile], Calculated);
            MRC_DEBUG_MSG (
              Debug,
              MSG_LEVEL_NOTE,
              "  % 7u % 10u % 8u % 5u %6u\n",
              Profile,
              Controller,
              Channel,
              Dimm,
              Calculated
              );
          } //DimmOut->Status
        } //Dimm
      } //Channel
    } //Controller
  } //Profile

  //
  // Set the best case timing for all controllers/channels/dimms, for each profile.
  //
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "    %s%u:", BestCaseString, MAX_PROFILE - 1);
  for (Profile = STD_PROFILE; Profile < MAX_PROFILE; Profile++) {
    if (!(MrcXmpTimingProfileEnabled (MrcData, Profile))) {
      continue;
    }
    for (Controller = 0; Controller < MAX_CONTROLLERS; Controller++) {
      ControllerOut = &Outputs->Controller[Controller];
      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        ChannelOut = &ControllerOut->Channel[Channel];
        for (Dimm = 0; Dimm < MAX_DIMMS_IN_CHANNEL; Dimm++) {
          DimmOut = &ChannelOut->Dimm[Dimm];
          DimmOut->Timing[Profile].tWTR_L    = (UINT16) Actual[Profile];
          ChannelOut->Timing[Profile].tWTR_L = (UINT16) Actual[Profile];
        }
      }
    }
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, " %u", Actual[Profile]);
  }
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n");

  return TRUE;
}

/**
  Calculate the tWTR_S timing value for the given memory frequency.

    @param[in, out] MrcData - Pointer to MrcData data structure.

    @retval TRUE if there are DIMMs present, otherwise FALSE.
**/
static
BOOLEAN
GetChannelDimmtWTR_S (
  IN OUT MrcParameters *const MrcData
  )
{
  const MrcInput        *Inputs;
  const MrcControllerIn *ControllerIn;
  const MrcChannelIn    *ChannelIn;
  const MrcDimmIn       *DimmIn;
  const MrcSpd          *Spd;
  MrcDebug              *Debug;
  MrcOutput             *Outputs;
  MrcControllerOut      *ControllerOut;
  MrcChannelOut         *ChannelOut;
  MrcDimmOut            *DimmOut;
  MrcProfile            Profile;
  UINT8                 Controller;
  UINT8                 Channel;
  UINT8                 Dimm;
  UINT32                tCKmin;
  UINT32                Actual[MAX_PROFILE];
  UINT32                Calculated;
  UINT32                tWTRSValue;
  BOOLEAN               FirstProfile;

  Inputs  = &MrcData->Inputs;
  Outputs = &MrcData->Outputs;
  Debug   = &Outputs->Debug;

  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "  %s:\n  %s\n", tWTRSString, HeaderString);

  //
  // Find the smallest timing value for all the given DIMMs, for all the profiles.
  //
  for (Profile = STD_PROFILE; Profile < MAX_PROFILE; Profile++) {
    if (!(MrcXmpTimingProfileEnabled (MrcData, Profile))) {
      continue;
    }
    FirstProfile    = TRUE;
    tWTRSValue      = 0;
    Actual[Profile] = 0;
    for (Controller = 0; Controller < MAX_CONTROLLERS; Controller++) {
      ControllerIn  = &Inputs->Controller[Controller];
      ControllerOut = &Outputs->Controller[Controller];
      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        ChannelIn   = &ControllerIn->Channel[Channel];
        ChannelOut  = &ControllerOut->Channel[Channel];
        for (Dimm = 0; Dimm < MAX_DIMMS_IN_CHANNEL; Dimm++) {
          DimmIn  = &ChannelIn->Dimm[Dimm];
          DimmOut = &ChannelOut->Dimm[Dimm];
          if (DIMM_PRESENT == DimmOut->Status) {
            Spd            = &DimmIn->Spd.Data;
            Calculated     = 0;
            tCKmin         = DimmOut->Timing[Profile].tCK;
            switch (Profile) {
              case XMP_PROFILE1:
              case XMP_PROFILE2:
                if (MRC_DDR_TYPE_DDR4 == DimmOut->DdrType) {
                  Calculated = (tCKmin == 0) ? 0 : (2500000 - (tCKmin / 100) + tCKmin - 1) / tCKmin; // 2.5ns
                }
                if (FirstProfile) {
                  tWTRSValue = Calculated;
                  FirstProfile = FALSE;
                } else if (tWTRSValue != Calculated) {
                  Outputs->XmpProfileEnable = 0;
                  MRC_DEBUG_MSG (Debug, MSG_LEVEL_WARNING, "  %s\n", XmpDisableString);
                }
                break;
              case USER_PROFILE:
                if (DimmIn->Timing.tWTR_S > 0) {
                  Calculated = DimmIn->Timing.tWTR_S;
                  break;
                } else {
                  // In AUTO mode, so no break.
                }
              case STD_PROFILE:
              default:
                if (MRC_DDR_TYPE_DDR4 == DimmOut->DdrType) {
                  Calculated = (tCKmin == 0) ? 0 : (2500000 - (tCKmin / 100) + tCKmin - 1) / tCKmin; // 2.5ns
                }
                break;
            } //switch

            Actual[Profile] = MAX (Actual[Profile], Calculated);
            MRC_DEBUG_MSG (
              Debug,
              MSG_LEVEL_NOTE,
              "  % 7u % 10u % 8u % 5u %6u\n",
              Profile,
              Controller,
              Channel,
              Dimm,
              Calculated
              );
          } //DimmOut->Status
        } //Dimm
      } //Channel
    } //Controller
  } //Profile

  //
  // Set the best case timing for all controllers/channels/dimms, for each profile.
  //
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "    %s%u:", BestCaseString, MAX_PROFILE - 1);
  for (Profile = STD_PROFILE; Profile < MAX_PROFILE; Profile++) {
    if (!(MrcXmpTimingProfileEnabled (MrcData, Profile))) {
      continue;
    }
    for (Controller = 0; Controller < MAX_CONTROLLERS; Controller++) {
      ControllerOut = &Outputs->Controller[Controller];
      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        ChannelOut = &ControllerOut->Channel[Channel];
        for (Dimm = 0; Dimm < MAX_DIMMS_IN_CHANNEL; Dimm++) {
          DimmOut = &ChannelOut->Dimm[Dimm];
          DimmOut->Timing[Profile].tWTR_S    = (UINT16) Actual[Profile];
          ChannelOut->Timing[Profile].tWTR_S = (UINT16) Actual[Profile];
        }
      }
    }
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, " %u", Actual[Profile]);
  }
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n");

  return TRUE;
}

/**
  Calculate the minimum command rate mode value for the given channel.

    @param[in, out] MrcData - Pointer to MrcData data structure.

    @retval TRUE if there are DIMMs present, otherwise FALSE.
**/
static
BOOLEAN
GetChannelDimmNmode (
  IN OUT MrcParameters *const MrcData
  )
{
  const MrcInput        *Inputs;
  const MrcControllerIn *ControllerIn;
  const MrcChannelIn    *ChannelIn;
  const MrcDimmIn       *DimmIn;
  const MrcSpd          *Spd;
  MrcDebug              *Debug;
  MrcOutput             *Outputs;
  MrcControllerOut      *ControllerOut;
  MrcChannelOut         *ChannelOut;
  MrcDimmOut            *DimmOut;
  MrcTimeBase           *TimeBase;
  MrcProfile            Profile;
  UINT8                 Controller;
  UINT8                 Channel;
  UINT8                 Dimm;
  UINT32                tCKmin;
  INT32                 MediumTimebase;
  INT32                 FineTimebase;
  UINT32                Actual[MAX_PROFILE];
  UINT32                Calculated;
  UINT32                Index;
  UINT32                TimingMTB;

  Inputs  = &MrcData->Inputs;
  Outputs = &MrcData->Outputs;
  Debug   = &Outputs->Debug;

  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "  %s:\n  %s\n", NmodeString, HeaderString);

  //
  // Find the smallest timing value for all the given DIMMs, for all the profiles.
  //
  for (Profile = STD_PROFILE; Profile < MAX_PROFILE; Profile++) {
    if (!(MrcXmpTimingProfileEnabled (MrcData, Profile))) {
      continue;
    }
    Actual[Profile] = (Profile < XMP_PROFILE1) ? NMODEMINPOSSIBLE : 0;
    for (Controller = 0; Controller < MAX_CONTROLLERS; Controller++) {
      ControllerIn  = &Inputs->Controller[Controller];
      ControllerOut = &Outputs->Controller[Controller];
      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        ChannelIn   = &ControllerIn->Channel[Channel];
        ChannelOut  = &ControllerOut->Channel[Channel];
        for (Dimm = 0; Dimm < MAX_DIMMS_IN_CHANNEL; Dimm++) {
          DimmIn  = &ChannelIn->Dimm[Dimm];
          DimmOut = &ChannelOut->Dimm[Dimm];
          if (DIMM_PRESENT == DimmOut->Status) {
            Spd            = &DimmIn->Spd.Data;
            Calculated     = 2;
            tCKmin         = DimmOut->Timing[Profile].tCK;
            TimeBase       = &ChannelOut->TimeBase[Dimm][Profile];
            MediumTimebase = TimeBase->Mtb;
            FineTimebase   = TimeBase->Ftb;
            switch (Profile) {
              case XMP_PROFILE1:
              case XMP_PROFILE2:
                if (MrcDimmXmpProfileSupported (DimmOut, Profile)) {
                  Index = Profile - XMP_PROFILE1;
                  if (MRC_DDR_TYPE_DDR3 == DimmOut->DdrType) {
                    TimingMTB = Spd->Ddr3.Xmp.Data[Index].SystemCmdRate.Bits.NMode;
                    if (tCKmin == 0) {
                      Calculated = 0;
                    } else {
                      Calculated = ((MediumTimebase * TimingMTB) - (tCKmin / 100) + (tCKmin - 1)) / tCKmin;
                      if (Calculated == 0) {
                        Calculated = 2;
                      }
                    }
                  } else {
                    if (Inputs->NModeSupport > 0) {
                      Calculated = Inputs->NModeSupport;
                    } else {
                      Calculated = NMODEMINPOSSIBLE;
                    }
                  }
                } else {
                  Calculated = 0;
                }
                break;
              case USER_PROFILE:
              case STD_PROFILE:
              default:
                Calculated = (Inputs->NModeSupport > 0) ? Inputs->NModeSupport : NMODEMINPOSSIBLE;
                break;
            } //switch

            Actual[Profile] = MAX (Actual[Profile], Calculated);
            MRC_DEBUG_MSG (
              Debug,
              MSG_LEVEL_NOTE,
              "  % 7u % 10u % 8u % 5u %6u\n",
              Profile,
              Controller,
              Channel,
              Dimm,
              Calculated
              );
          } //DimmOut->Status
        } //Dimm
      } //Channel
    } //Controller
  } //Profile

  //
  // Set the best case timing for all controllers/channels/dimms, for each profile.
  //
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "    %s%u:", BestCaseString, MAX_PROFILE - 1);
  for (Profile = STD_PROFILE; Profile < MAX_PROFILE; Profile++) {
    if (!(MrcXmpTimingProfileEnabled (MrcData, Profile))) {
      continue;
    }
    for (Controller = 0; Controller < MAX_CONTROLLERS; Controller++) {
      ControllerOut = &Outputs->Controller[Controller];
      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        ChannelOut = &ControllerOut->Channel[Channel];
        for (Dimm = 0; Dimm < MAX_DIMMS_IN_CHANNEL; Dimm++) {
          DimmOut = &ChannelOut->Dimm[Dimm];
          DimmOut->Timing[Profile].NMode    = (UINT16) Actual[Profile];
          ChannelOut->Timing[Profile].NMode = (UINT16) Actual[Profile];
        }
      }
    }
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, " %u", Actual[Profile]);
  }
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n");

  return TRUE;
}

/**
  Calculate the VDD voltage value for the given channel.

    @param[in, out] MrcData - Pointer to MrcData data structure.

    @retval TRUE if there are DIMMs present, otherwise FALSE.
**/
static
BOOLEAN
GetChannelDimmVdd (
  IN OUT MrcParameters *const MrcData
  )
{
  const MrcInput                        *Inputs;
  const MrcControllerIn                 *ControllerIn;
  const MrcChannelIn                    *ChannelIn;
  const MrcDimmIn                       *DimmIn;
  const MrcSpd                          *Spd;
  MrcDebug                              *Debug;
  MrcOutput                             *Outputs;
  MrcControllerOut                      *ControllerOut;
  MrcChannelOut                         *ChannelOut;
  MrcDimmOut                            *DimmOut;
  MrcProfile                            Profile;
  SpdVddFlag                            VddFlag;
  MrcCpuModel                           CpuModel;
  UINT32                                Actual[MAX_PROFILE];
  UINT32                                Calculated;
  UINT8                                 Controller;
  UINT8                                 Channel;
  UINT8                                 Dimm;

  const SPD_EXTREME_MEMORY_PROFILE_DATA      *Data1;
  const SPD_EXTREME_MEMORY_PROFILE_DATA_2_0  *Data2;
  UINT32                                      Index;

  Inputs   = &MrcData->Inputs;
  Outputs  = &MrcData->Outputs;
  Debug    = &Outputs->Debug;
  CpuModel = Inputs->CpuModel;

  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "  %s:\n  %s\n", VddString, HeaderString);

  //
  // Find the best case voltage value for all the given DIMMs, for all the profiles.
  //
  for (Profile = STD_PROFILE; Profile < MAX_PROFILE; Profile++) {
    if (!(MrcXmpTimingProfileEnabled (MrcData, Profile))) {
      continue;
    }
    Actual[Profile] = (Profile < XMP_PROFILE1) ? VDD_1_10 : 0;
    for (Controller = 0; Controller < MAX_CONTROLLERS; Controller++) {
      ControllerIn  = &Inputs->Controller[Controller];
      ControllerOut = &Outputs->Controller[Controller];
      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        ChannelIn   = &ControllerIn->Channel[Channel];
        ChannelOut  = &ControllerOut->Channel[Channel];
        for (Dimm = 0; Dimm < MAX_DIMMS_IN_CHANNEL; Dimm++) {
          DimmIn  = &ChannelIn->Dimm[Dimm];
          DimmOut = &ChannelOut->Dimm[Dimm];
          if (DIMM_PRESENT == DimmOut->Status) {
            Spd        = &DimmIn->Spd.Data;
            Calculated = VDD_1_50;
            switch (Profile) {
              case XMP_PROFILE1:
              case XMP_PROFILE2:
                if (MrcDimmXmpProfileSupported (DimmOut, Profile)) {
                  Index = Profile - XMP_PROFILE1;
                  if (MRC_DDR_TYPE_DDR3 == DimmOut->DdrType) {
                    Data1 = &Spd->Ddr3.Xmp.Data[Index];
                    Calculated  = XMP_VDD_INCREMENT * Data1->Vdd.Bits.Decimal;
                    Calculated  = MIN (Calculated, XMP_VDD_INTEGER - 1);
                    Calculated += (XMP_VDD_INTEGER * Data1->Vdd.Bits.Integer);
                  } else {
                    Data2 = &Spd->Ddr4.EndUser.Xmp.Data[Index];
                    Calculated  = XMP_VDD_INCREMENT_2 * Data2->Vdd.Bits.Decimal;
                    Calculated  = MIN (Calculated, XMP_VDD_INTEGER - 1);
                    Calculated += (XMP_VDD_INTEGER * Data2->Vdd.Bits.Integer);
                  }
                  Calculated  = MAX (Calculated, XMP_VDD_MIN_POSSIBLE);
                  Calculated  = MIN (Calculated, XMP_VDD_MAX_POSSIBLE);
                } else {
                  Calculated = 0;
                }
                break;
              case USER_PROFILE:
                if (Inputs->VddVoltage > 0) {
                  Calculated = Inputs->VddVoltage;
                  break;
                } else {
                  // In AUTO mode, so no break.
                }
              case STD_PROFILE:
              default:
                if ((MRC_DDR_TYPE_DDR3 == DimmOut->DdrType) || (Spd->Ddr3.General.DramDeviceType.Bits.Type == MRC_SPD_LPDDR3_SDRAM_TYPE_NUMBER))  {
                  VddFlag.Bits.Vdd1_50 = ~(Spd->Ddr3.General.ModuleNominalVoltage.Bits.OperationAt1_50);
                  VddFlag.Bits.Vdd1_35 = Spd->Ddr3.General.ModuleNominalVoltage.Bits.OperationAt1_35;
                  VddFlag.Bits.Vdd1_25 = Spd->Ddr3.General.ModuleNominalVoltage.Bits.OperationAt1_25;
#if (VDDMINPOSSIBLE <= 1350)
                  if (PlatformSupport.VddMin.UltVdd <= 1350) {
                    if (VddFlag.Bits.Vdd1_35) {
                      Calculated = VDD_1_35;
                    }
                  }
#endif // VDDMINPOSSIBLE
#if (VDDMINPOSSIBLE <= 1200)
                  if (PlatformSupport.VddMin.UltVdd <= 1200) {
                    if (VddFlag.Bits.Vdd1_25) {
                      Calculated = VDD_1_20;
                    }
                  }
#endif // VDDMINPOSSIBLE
                } else if (MRC_DDR_TYPE_LPDDR3 == DimmOut->DdrType) {
                  VddFlag.Bits.Vdd1_20 = Spd->Lpddr.Base.ModuleNominalVoltage.Bits.OperationAt1_20;
                  VddFlag.Bits.Vdd1_10 = Spd->Lpddr.Base.ModuleNominalVoltage.Bits.OperationAt1_10;
#if (VDDMINPOSSIBLE <= 1200)
                  if (PlatformSupport.VddMin.UltVdd <= 1200) {
                    if (VddFlag.Bits.Vdd1_20) {
                      Calculated = VDD_1_20;
                    }
                  }
#endif // VDDMINPOSSIBLE
#if (VDDMINPOSSIBLE <= 1100)
                  if (PlatformSupport.VddMin.UltVdd <= 1100) {
                    if (VddFlag.Bits.Vdd1_10) {
                      Calculated = VDD_1_10;
                    }
                  }
#endif // VDDMINPOSSIBLE
                } else {
                  Calculated = VDD_1_20;
                }
                break;
            } //switch

            Actual[Profile] = MAX (Actual[Profile], Calculated);
            MRC_DEBUG_MSG (
              Debug,
              MSG_LEVEL_NOTE,
              "  % 7u % 10u % 8u % 5u %4u\n",
              Profile,
              Controller,
              Channel,
              Dimm,
              Calculated
            );
          } //DimmOut->Status
        } //Dimm
      } //Channel
    } //Controller
  } //Profile

  //
  // Set the best case voltage for all controllers/channels/dimms, for each profile.
  //
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "    %s%u:", BestCaseString, MAX_PROFILE - 1);
  for (Profile = STD_PROFILE; Profile < MAX_PROFILE; Profile++) {
    if (!(MrcXmpTimingProfileEnabled (MrcData, Profile))) {
      continue;
    }
    for (Controller = 0; Controller < MAX_CONTROLLERS; Controller++) {
      ControllerOut = &Outputs->Controller[Controller];
      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        ChannelOut = &ControllerOut->Channel[Channel];
        for (Dimm = 0; Dimm < MAX_DIMMS_IN_CHANNEL; Dimm++) {
          DimmOut = &ChannelOut->Dimm[Dimm];
          Outputs->VddVoltage[Profile] = (MrcVddSelect) Actual[Profile];
          DimmOut->VddVoltage[Profile] = (MrcVddSelect) Actual[Profile];
        }
      }
    }
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, " %u", Actual[Profile]);
  }
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n");

  return TRUE;
}

/**
  Analyze the given DIMM SPD data to determine DIMM presence and configuration.

    @param[in, out] MrcData - Pointer to MRC global data structure.
    @param[in] Controller   - Current controller number.
    @param[in] Channel      - Current channel number.
    @param[in] Dimm         - Current DIMM number.

    @retval mrcSuccess if DIMM is present otherwise mrcDimmNotExist.
**/
static
MrcStatus
SpdDimmRecognition (
  IN OUT MrcParameters *const MrcData,
  IN  const UINT8          Controller,
  IN  UINT8                Channel,
  IN  UINT8                Dimm
  )
{
    static const SpdRecogCallTable CallTable[] = {
    {ValidDimm},
    {ValidSdramDeviceWidth},
    {ValidPrimaryWidth},
    {GetRankCount},
    {ValidBank},
    {GetDimmSize},
    {ValidRowSize},
    {ValidColumnSize},
    {ValidEccSupport},
    {GetAddressMirror},
    {GetThermalRefreshSupport},
    {GetpTRRsupport},
    {GetReferenceRawCardSupport}
  };
  const MrcSpd *Spd;
  const UINT8  *CrcStart;
  MrcDimmOut   *DimmOut;
  MrcDimmIn    *DimmIn;
  BOOLEAN      Status;
  UINT32       CrcSize;
  UINT8        Index;

  DimmIn  = &MrcData->Inputs.Controller[Controller].Channel[Channel].Dimm[Dimm];
  Spd     = &DimmIn->Spd.Data;
  DimmOut = &MrcData->Outputs.Controller[Controller].Channel[Channel].Dimm[Dimm];
  DimmOut->Status = DIMM_NOT_PRESENT;
  if (DIMM_PRESENT == DimmPresence (&MrcData->Outputs.Debug, Spd)) {
    Status = TRUE;
    for (Index = 0; (Status == TRUE) && (Index < (sizeof (CallTable) / sizeof (CallTable[0]))); Index++) {
      Status &= CallTable[Index].mrc_task (MrcData, Spd, DimmOut);
    }
    if (Status == FALSE) {
      DimmOut->Status = DIMM_DISABLED;
      return mrcDimmNotExist;
    }
    DimmOut->Status = DIMM_PRESENT;
    CrcStart = MrcSpdCrcArea (MrcData, Controller, Channel, Dimm, &CrcSize);
    GetDimmCrc ((const UINT8*const) CrcStart, CrcSize, &DimmOut->Crc);
  } else {
#if (SUPPORT_RDIMM == UNSUPPORT)
    if (Spd->Ddr3.General.ModuleType.Bits.ModuleType == RDimmMemoryPackage) {
      return mrcUnsupportedTechnology;
    }
#endif
    return mrcDimmNotExist;
  }

  if (DIMM_DISABLED == DimmIn->Status) {
    DimmOut->Status = DIMM_DISABLED;
  }

  return mrcSuccess;
}

/**
  Calculate the timing of all DIMMs on all channels.

    @param[in, out] MrcData - The MRC "global data".

    @retval mrcSuccess on success, mrcDimmNotExist if no DIMMs found.
**/
static
MrcStatus
SpdTimingCalculation (
  IN OUT MrcParameters *const MrcData
  )
{
  static const SpdTimeCallTable CallTable[] = {
    {GetChannelDimmTimeBase}, // Note: This must be done first as all other calculations are based on this.
    {GetChannelDimmtCK},      // Note: This must be done second as all other calculations are based on this.
    {GetChannelDimmtAA},
    {GetChannelDimmtCWL},
    {GetChannelDimmtRAS},
    {GetChannelDimmtRCD},
    {GetChannelDimmtRC},      // Note: This must be done after GetChannelDimmtRAS and GetChannelDimmtRCD
    {GetChannelDimmtREFI},
    {GetChannelDimmtRFC},
    {GetChannelDimmtRP},      // Note: This must be done after GetChannelDimmtRCD
    {GetChannelDimmtRPab},    // Note: This must be done after GetChannelDimmtRP
    {GetChannelDimmtFAW},
    {GetChannelDimmtRRD},
    {GetChannelDimmtRTP},
    {GetChannelDimmtWR},
    {GetChannelDimmtWTR},
    {GetChannelDimmtRFC2},
    {GetChannelDimmtRFC4},
    {GetChannelDimmtRRD_L},
    {GetChannelDimmtRRD_S},
    {GetChannelDimmtWTR_L},
    {GetChannelDimmtWTR_S},
    {GetChannelDimmNmode},
    {GetChannelDimmVdd}
  };
  BOOLEAN    Status;
  UINT8      Index;
#if (SUPPORT_FORCE == SUPPORT)
  MrcChannelOut *ChannelOut;
  MrcDimmOut    *DimmOut;
  UINT16     Value;
  UINT8      Controller;
  UINT8      Channel;
  UINT8      Dimm;
#endif

  //
  // Find the "least common denominator" timing across the DIMMs.
  // tAA must be done first before any other timings are calculated.
  //
  Status = TRUE;
  for (Index = 0; (Status == TRUE) && (Index < (sizeof (CallTable) / sizeof (SpdTimeCallTable))); Index++) {
    Status &= CallTable[Index].mrc_task (MrcData);
  }

#if (SUPPORT_FORCE == SUPPORT)
  if (Status == TRUE) {
    //
    // Force tCLmin, tRCDmin, tRPmin to be the same "least common denominator" value.
    //
    Value = 0;
    for (Controller = 0; Controller < MAX_CONTROLLERS; Controller++) {
      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        for (Dimm = 0; Dimm < MAX_DIMMS_IN_CHANNEL; Dimm++) {
          DimmOut = &Outputs->Controller[Controller].Channel[Channel].Dimm[Dimm];
          if (DIMM_PRESENT == DimmOut->Status) {
            Value = MAX (Value, DimmOut->Timing.tRCDtRP);
            Value = MAX (Value, DimmOut->Timing.tCL);
          }
        }
      }
    }

    for (Controller = 0; Controller < MAX_CONTROLLERS; Controller++) {
      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        ChannelOut = &Outputs->Controller[Controller].Channel[Channel];
        for (Dimm = 0; Dimm < MAX_DIMMS_IN_CHANNEL; Dimm++) {
          DimmOut = &ChannelOut->Dimm[Dimm];
          if (DIMM_PRESENT == DimmOut->Status) {
            ChannelOut->Timing.tRCDtRP = Value;
            ChannelOut->Timing.tCL     = Value;
            DimmOut->Timing.tRCDtRP = Value;
            DimmOut->Timing.tCL     = Value;
          }
        }
      }
    }
  }
#endif
  return (Status == FALSE) ? mrcDimmNotExist : mrcSuccess;
}

/**
  Determine the starting address and size of the SPD area to generate a CRC.

    @param[in, out] MrcData    - The MRC "global data".
    @param[in]      Controller - Controller index.
    @param[in]      Channel    - Channel index.
    @param[in]      Dimm       - Dimm index.
    @param[out]     CrcSize    - Location to write CRC block size.

    @retval The starting address of the CRC block.
**/
const UINT8 *
MrcSpdCrcArea (
  IN OUT MrcParameters *const MrcData,
  IN     UINT8                Controller,
  IN     UINT8                Channel,
  IN     UINT8                Dimm,
  OUT    UINT32        *const CrcSize
  )
{
  const MrcDimmIn *DimmIn;
  const UINT8     *CrcStart;
  UINT8           DdrType;

  DimmIn   = &MrcData->Inputs.Controller[Controller].Channel[Channel].Dimm[Dimm];

  DdrType = DimmIn->Spd.Data.Ddr3.General.DramDeviceType.Bits.Type;
  if ((MRC_SPD_DDR3_SDRAM_TYPE_NUMBER == DdrType) || (MRC_SPD_LPDDR3_SDRAM_TYPE_NUMBER == DdrType)) {
    CrcStart = (const UINT8*) &DimmIn->Spd.Data.Ddr3.ModuleId;
    *CrcSize = SPD3_MANUF_SIZE;
  } else if (MRC_SPD_DDR4_SDRAM_TYPE_NUMBER == DdrType) {
    CrcStart = (void *) &DimmIn->Spd.Data.Ddr4.ManufactureInfo;
    *CrcSize = SPD4_MANUF_SIZE;
  } else if (MRC_JEDEC_LPDDR3_SDRAM_TYPE_NUMBER == DdrType) {
    CrcStart = (void *) &DimmIn->Spd.Data.Lpddr.ManufactureInfo;
    *CrcSize = SPDLP_MANUF_SIZE;
  } else {
    CrcStart = NULL;
    *CrcSize = 0;
  }
  return (CrcStart);
}

/**
  Check that DQByteMap and DqsMapCpu2Dram have valid values.

  @param[in, out] MrcData - The MRC "global data".

  @retval mrcSuccess on success, mrcWrongInputParameter if these tables have invalid values.
**/
MrcStatus
MrcCheckLpddrMapping (
  IN OUT MrcParameters *const MrcData
  )
{
  MrcDebug              *Debug;
  const MrcInput        *Inputs;
  const MrcChannelIn    *ChannelIn;
  MrcStatus             Status;
  MrcOutput             *Outputs;
  UINT8                 CpuByte;
  UINT8                 DramByte;
  UINT8                 Channel;
  const UINT8           (*DqByteMap)[2]; // Skip first dimension - this is a pointer to DQByteMap[MrcIterationMax][2]
  UINT8                 DqsMap;
  BOOLEAN               DqByteMapGood;
  BOOLEAN               DqsMapCpu2DramGood;

  Status  = mrcSuccess;
  Inputs  = &MrcData->Inputs;
  Outputs = &MrcData->Outputs;
  Debug   = &Outputs->Debug;
  DqByteMapGood = DqsMapCpu2DramGood = TRUE;

  if (Outputs->DdrType != MRC_DDR_TYPE_LPDDR3) {
    return mrcSuccess;
  }

  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    if (!MrcChannelExist (Outputs, Channel)) {
      continue;
    }
    ChannelIn = &Inputs->Controller[0].Channel[Channel];
    DqByteMap = ChannelIn->DQByteMap;
    if ((DqByteMap[MrcIterationClock][0] | DqByteMap[MrcIterationClock][1]) != 0xFF) {
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR,"ERROR: DqByteMap[%s][0] | DqByteMap[%s][1] should be 0xFF\n", "0", "0");
      DqByteMapGood = FALSE;  // CLK must go to all bytes
    } else if ((DqByteMap[MrcIterationCmdS][0] | DqByteMap[MrcIterationCmdS][1]) != 0xFF) {
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR,"ERROR: DqByteMap[%s][0] | DqByteMap[%s][1] should be 0xFF\n", "2", "2");
      DqByteMapGood = FALSE; // CmdS CAA/CAB must go to all bytes
    } else if (DqByteMap[MrcIterationCmdS][0] != DqByteMap[MrcIterationCke][0]) {
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR,"ERROR: DqByteMap[%s] should be equal to DqByteMap[%s]\n", "2][0", "3][0");
      DqByteMapGood = FALSE; // CmdS CAA and CKE CAA must be the same
    } else if (DqByteMap[MrcIterationCmdN][1] != DqByteMap[MrcIterationCmdS][1]) {
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR,"ERROR: DqByteMap[%s] should be equal to DqByteMap[%s]\n", "1][1", "2][1");
      DqByteMapGood = FALSE; // CmdN CAB and CmdS CAB must be the same
    }
    DqsMap = 0;
    for (CpuByte = 0; CpuByte < 8; CpuByte++) {
      DramByte = ChannelIn->DqsMapCpu2Dram[CpuByte];
      if (DramByte < 8) {
        DqsMap |= (1 << DramByte);
      }
    }
    if (DqsMap != 0xFF) {
      DqsMapCpu2DramGood = FALSE;
    }
  } // for Channel

  if (!DqByteMapGood) {
    Status = mrcWrongInputParameter;
  }
  if (!DqsMapCpu2DramGood) {
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR,"ERROR: input array %s has invalid values !\n", "DqsMapCpu2Dram");
    Status = mrcWrongInputParameter;
  }

  return Status;
}

/**
  Check that some MRC input parameters make sense for the current DDR type.

  @param[in] MrcData - The MRC "global data".

  @retval mrcSuccess on success, mrcWrongInputParameter if parameters have invalid values.
**/
MrcStatus
MrcCheckInputParams (
  IN OUT MrcParameters *const MrcData
  )
{
  MrcDebug              *Debug;
  const MrcInput        *Inputs;
  MrcOutput             *Outputs;
  MrcStatus             Status;
  BOOLEAN               Ddr4;

  Status  = mrcSuccess;
  Inputs  = &MrcData->Inputs;
  Outputs = &MrcData->Outputs;
  Debug   = &Outputs->Debug;
  Ddr4 = (Outputs->DdrType == MRC_DDR_TYPE_DDR4);

  if (!Ddr4) {
    if (Inputs->CaVrefConfig != 0) {
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR,"ERROR: CaVrefConfig must be 0 for DDR3L/LPDDR3 !\n");
      Status = mrcWrongInputParameter;
    }
  }
  return Status;
}

/**
  Process the SPD information for all DIMMs on all channels.

    @param[in, out] MrcData - The MRC "global data".

    @retval mrcSuccess on success, mrcDimmNotExist if no DIMMs found.
**/
MrcStatus
MrcSpdProcessing (
  IN OUT MrcParameters *const MrcData
  )
{
  MrcDebug                      *Debug;
  const MrcInput                *Inputs;
  const MrcControllerIn         *ControllerIn;
  const MrcChannelIn            *ChannelIn;
  const MrcDimmIn               *DimmIn;
  const MrcSpd                  *SpdIn;
  MrcStatus                     Status;
  MrcOutput                     *Outputs;
  MrcControllerOut              *ControllerOut;
  MrcChannelOut                 *ChannelOut;
  MrcDimmOut                    *DimmOut;
  UINT8                         Controller;
  UINT8                         Channel;
  UINT8                         Dimm;
  UINT32                        DimmCount;
  UINT8                         ValidRankBitMask;
  UINT16                        DateCode;
  const SPD4_MANUFACTURING_DATA *ManufactureData;
  UINT8                         DensityIndex;
  UINT8                         SdramWidthIndex;
  UINT8                         DimmPartNumber;
  BOOLEAN                       FirstDimm;

  Inputs  = &MrcData->Inputs;
  Outputs = &MrcData->Outputs;
  Debug   = &Outputs->Debug;
  Status  = mrcDimmNotExist;

  Outputs->DdrType = MRC_DDR_TYPE_UNKNOWN;
  Outputs->tMAC    = MRC_TMAC_UNLIMITED;
  Outputs->OddRatioMode = (BOOLEAN) Inputs->OddRatioMode;   // This may be overridden during SPD processing, see GetChannelDimmtCK()

  //
  // Scan thru each DIMM to see if it is a valid DIMM and to get its configuration.
  //
  DimmCount  = 0;
  FirstDimm = TRUE;
  for (Controller = 0; Controller < MAX_CONTROLLERS; Controller++) {
    ControllerIn  = &Inputs->Controller[Controller];
    ControllerOut = &Outputs->Controller[Controller];
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      ChannelIn   = &ControllerIn->Channel[Channel];
      ChannelOut  = &ControllerOut->Channel[Channel];
      ChannelOut->DimmCount = 0;
      for (Dimm = 0; Dimm < MAX_DIMMS_IN_CHANNEL; Dimm++) {
        DimmIn  = &ChannelIn->Dimm[Dimm];
        DimmOut = &ChannelOut->Dimm[Dimm];
        if (DimmIn->Status == DIMM_ENABLED || DimmIn->Status == DIMM_DISABLED) {
          MRC_DEBUG_MSG (
            Debug,
            MSG_LEVEL_NOTE,
            "SPD Dimm recognition, %s %u/%u/%u\n",
            CcdString,
            Controller,
            Channel,
            Dimm
            );
          Status = SpdDimmRecognition (MrcData, Controller, Channel, Dimm);
          if (Status == mrcSuccess) {
            DimmCount++;
            ChannelOut->DimmCount++;
            if (FirstDimm) {
              Outputs->XmpProfileEnable = DimmOut->XmpSupport;
              FirstDimm = FALSE;
            } else if (Outputs->XmpProfileEnable != DimmOut->XmpSupport) {
              MRC_DEBUG_MSG (Debug, MSG_LEVEL_WARNING, "%s\n", XmpDisableString);
              Outputs->XmpProfileEnable = 0;
            }
            if (MRC_DDR_TYPE_UNKNOWN == Outputs->DdrType) {
              Outputs->DdrType = DimmOut->DdrType;
            } else if (Outputs->DdrType != DimmOut->DdrType) {
              Status = mrcMixedDimmSystem;
            }
            if (Status == mrcMixedDimmSystem) {
              MRC_DEBUG_MSG (
                Debug,
                MSG_LEVEL_ERROR,
                "%s configuration, system contains a mix of memory types\n",
                ErrorString
                );
              return (Status);
            }
#if (SUPPORT_RDIMM == UNSUPPORT)
          } else if (Status == mrcUnsupportedTechnology) {
            return (Status);
#endif
          }
        }
      }
    }
  }

  //
  // Get the maximum allowed frequency / refclk
  //
  MrcMcCapabilityPreSpd (MrcData);

  if (DimmCount > 0) {
    Outputs->TCRSensitiveHynixDDR4  = FALSE;
    Outputs->TCRSensitiveMicronDDR4 = FALSE;
    //
    // Scan thru each channel to see if it is a valid channel and to get its configuration.
    //
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "SPD Dimm timing calculation\n");
    if (mrcSuccess == SpdTimingCalculation (MrcData)) {
      Outputs->EccSupport = TRUE;

      //
      // Count up the number of valid DIMMs.
      //
      ControllerOut = &Outputs->Controller[0];
      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        ChannelOut = &ControllerOut->Channel[Channel];
        for (Dimm = 0; Dimm < MAX_DIMMS_IN_CHANNEL; Dimm++) {
          DimmOut = &ChannelOut->Dimm[Dimm];
          if ((DIMM_PRESENT == DimmOut->Status) || (DIMM_DISABLED == DimmOut->Status)) {
            if ((Outputs->DdrType == MRC_DDR_TYPE_DDR4) && (Outputs->TCRSensitiveHynixDDR4 == FALSE) && (Outputs->TCRSensitiveMicronDDR4 == FALSE)) {
              SpdIn = &Inputs->Controller[0].Channel[Channel].Dimm[Dimm].Spd.Data;
              ManufactureData = &SpdIn->Ddr4.ManufactureInfo;
              if ((ManufactureData->DramIdCode.Data == 0xAD80) ||
                  (ManufactureData->ModuleId.IdCode.Data == 0xAD80)) { // Hynix
                DateCode = (ManufactureData->ModuleId.Date.Year << 8) | ManufactureData->ModuleId.Date.Week;
                if (DateCode < 0x1512) {
                  Outputs->TCRSensitiveHynixDDR4 = TRUE;
                }
              }
              else if ((ManufactureData->DramIdCode.Data == 0x2C80) ||
                       (ManufactureData->ModuleId.IdCode.Data == 0x2C80)) { // Micron
                DensityIndex = SpdIn->Ddr4.Base.SdramDensityAndBanks.Bits.Density;
                SdramWidthIndex = SpdIn->Ddr4.Base.ModuleOrganization.Bits.SdramDeviceWidth;
                if ((DensityIndex == MRC_SPD_SDRAM_DENSITY_4Gb) &&
                    (SdramWidthIndex == MRC_SPD_SDRAM_DEVICE_WIDTH_8)) { // DRAM Density = 4Gb and DRAM Width = x8
                  DimmPartNumber = ManufactureData->ModulePartNumber.ModulePartNumber[15];
                  if (DimmPartNumber == 0x41) { // DIMM Part# Byte[15] = A-Die
                    Outputs->TCRSensitiveMicronDDR4 = TRUE;
                  }
                }
              }
            }
          }
          if (DIMM_PRESENT == DimmOut->Status) {
#if (MAX_RANK_IN_CHANNEL > 8)
#error The next switch statement and ValidRankBitMask needs updated to support additional ranks.
#endif
            switch (DimmOut->RankInDimm) {
              case 1:
                ValidRankBitMask = 1;
                break;
#if (MAX_RANK_IN_DIMM > 1)

              case 2:
                ValidRankBitMask = 3;
                break;
#endif
#if (MAX_RANK_IN_DIMM > 2)

              case 3:
                ValidRankBitMask = 7;
                break;
#endif
#if (MAX_RANK_IN_DIMM > 3)

              case 4:
                ValidRankBitMask = 15;
                break;
#endif

              default:
                ValidRankBitMask = 0;
                break;
            }

            ChannelOut->ValidRankBitMask |= ValidRankBitMask << (Dimm * MAX_RANK_IN_DIMM);

            Outputs->EccSupport  &= DimmOut->EccSupport;
            Outputs->tMAC         = MIN (Outputs->tMAC, DimmOut->tMAC);
          }
        }

        if ((ChannelOut->DimmCount > 0) && (ChannelOut->ValidRankBitMask > 0)) {
          ControllerOut->ChannelCount++;
          ControllerOut->Channel[Channel].Status = CHANNEL_PRESENT;
        }
      }

      for (Controller = 0; Controller < MAX_CONTROLLERS; Controller++) {
        ControllerOut = &Outputs->Controller[Controller];
        if (ControllerOut->ChannelCount > 0) {
          ControllerOut->Status = CONTROLLER_PRESENT;
          Status                = mrcSuccess;
        }
      }
    }
  }

  if (Status != mrcSuccess) {
    return Status;
  }

  Status = MrcCheckLpddrMapping (MrcData);
  if (Status != mrcSuccess) {
    return Status;
  }

  Status = MrcCheckInputParams (MrcData);

  return Status;
}
