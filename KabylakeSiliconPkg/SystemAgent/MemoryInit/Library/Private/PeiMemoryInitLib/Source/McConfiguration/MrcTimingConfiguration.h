/** @file
  This module configures the memory controller timing parameters.

 @copyright
  INTEL CONFIDENTIAL
  Copyright 1999 - 2016 Intel Corporation.

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
#ifndef _MrcTimingConfiguration_h_
#define _MrcTimingConfiguration_h_

#include "MrcTypes.h"
#include "MrcApi.h"
#include "McAddress.h"
#include "MrcCommon.h"
#include "MrcCrosser.h"
#include "MrcDdr3.h"
#include "MrcGlobal.h"
#if SUPPORT_SODIMM == SUPPORT
#include "MrcSpdProcessing.h"
#endif //SUPPORT_SODIMM == SUPPORT

///
/// SKL HW limits of timing parameters
///
#define tRP_MIN     8   ///< minimum tRP (and tRCD) supported is 8 DCLK cycles
#define tRP_MAX     63  ///< maximum tRP (and tRCD) supoprted is 63 DCLK cycles

#define tRAS_MIN    28  ///< minimum tRAS (ACT->PRE) supported is 28 DCLK cycles
#define tRAS_MAX    64  ///< maximum tRAS (ACT->PRE) supported is 64 DCLK cycles

#define tRDPRE_MIN  6   ///< minimum tRDPRE (Read->PRE) supported is 6 DCLK cycles
#define tRDPRE_MAX  15  ///< maximum tRDPRE (Read->PRE) supported is 15 DCLK cycles

#define tWRPRE_MIN  23  ///< minimum tWRPRE (Write->PRE) supported is 23 DCLK cycles
#define tWRPRE_MAX  96  ///< maximum tWRPRE (Write->PRE) supported is 96 DCLK cycles

#define tFAW_MIN    16
#define tFAW_MAX    63

#define tRRD_MIN    4
#define tRRD_MAX    15

#define tCL_MIN     5
#define tCL_MAX     31

#define tCWL_MIN    4
#define tCWL_MAX    20

#define tCKE_MIN    4
#define tCKE_MAX    15

#define tXP_MIN     5
#define tXP_MAX     15

#define tXPDLL_MIN  4
#define tXPDLL_MAX  63

#define tPRPDEN_MIN 1
#define tPRPDEN_MAX 3

#define tRDPDEN_MIN 4
#define tRDPDEN_MAX 95

#define tWRPDEN_MIN 4
#define tWRPDEN_MAX 95

#define tRDRD_MAX     54
#define tRDWR_MAX     54
#define tWRRD_MAX     54
#define tWRRD_SG_MAX  86
#define tWRWR_MAX     54

///
/// tCCD values.
///
#define TCCD_ALL_FREQ (4) ///< tCCD is = 4 DCLK for all frequencies up to 1600.
///
/// tWPRE values.
///
#define TWPRE_ALL_FREQ  (1) ///< tWPRE is = 1 DCLK for all frequencies up to 1600.
///
/// tRPRE values.
///
#define TRPRE_ALL_FREQ  (1) ///< tRPRE is = 1 DCLK for all frequencies up to 1600.
///
/// tCKE values.
///
#define TCKE_800  (3)
#define TCKE_1067 (3)
#define TCKE_1333 (4)
#define TCKE_1600 (4)
#define TCKE_1867 (5)
#define TCKE_2133 (6)
#define TCKE_2400 (6)
#define TCKE_2667 (7)
#define TCKE_2800 (7)
#define TCKE_2933 (8)
#define TCKE_3000 (8)
#define TCKE_3200 (8)

///
/// tCKE values for LPDDR: max(7.5ns, 3nCK)
///
#define tCKE_LPDDR_FS 7500000

///
/// tXP values for LPDDR: max(7.5ns, 3nCK)
///
#define tXP_LPDDR_FS  7500000

///
/// tXP values for DDR4: max(6ns, 4nCK)
///
#define tXP_DDR4_1600 (5)
#define tXP_DDR4_1867 (6)
#define tXP_DDR4_2133 (7)

///
/// tXPDLL values for DDR3: 24ns for all frequencies
///
#define tXPDLL_FS   24000000

///
/// tAONPD values for DDR3: 8.5ns for all frequencies
///
#define tAONPD_FS 8500000

#define MC_tXP_1600_1N (5)
#define MC_tXP_1867_2N (6)
#define MC_tXP_1867_3N (7)
#define MC_tXP_2133_1N (7)
#define MC_tXP_MAX     (8) ///< The maximum value that the MC supports.

///
/// tODTon / tODToff values, in [ps]
///
#define tODT_ON_MIN   1750
#define tODT_ON_MAX   3500
#define tODT_OFF_MIN  1750
#define tODT_OFF_MAX  3500

///
/// tDQSCK values, in [ps]
///
#define tDQSCK_MIN    2500
#define tDQSCK_MAX    5500
///
/// Specified in PI-Ticks.  64 == 1 QClk
///
#define tDQSCK_DRIFT  64

///
/// tVrefDQ in [ps] - delay between each MR6 in DDR4 PDA mode
///
#define tVREF_DQ      150000

/**
  This function configures the memory controller timings.

  @param[in] MrcData - Include all MRC global data.

  @retval Nothing.
**/
extern
void
MrcTimingConfiguration (
  IN MrcParameters *const MrcData
  );

/**
  This function returns the tXP value for the specified frequency.

  @param[in] DdrType   - DDR type
  @param[in] Frequency - The memory frequency.
  @param[in] tCK       - DCLK period in femtoseconds.
  @param[in] NMode     - Command mode to lookup.

  @retval The tXP value for the specified frequency.
**/
UINT32
tXPValue (
  IN MrcDdrType         DdrType,
  IN const MrcFrequency Frequency,
  IN UINT32             tCK,
  IN UINT8              NMode
  );

/**
  This function sets up the Read ODTD values based on RawCard types and adjusts the tDRRD2RD, tDDRD2RD, tDRRD2WR and tDDRD2WR

  @param[in, out] MrcData - Include all MRC global data.

  @retval Nothing.
**/
extern
void
RdOdtStretch (
  IN OUT MrcParameters *const MrcData
  );

/**
  This function adjusts the relevant TAT when changing Read or Write ODT duration.
  TAT list rdOdt = { drrd2rd, ddrd2rd, drrd2wr, ddrd2wr, srrd2wr_sg, srrd2wr_dg };
  TAT list wrOdt = { drwr2wr, ddwr2wr, drwr2rd, ddwr2rd, srwr2rd_sg, srwr2rd_dg };

  @param[in, out] MrcData - Include all MRC global data.
  @param[in]      OdtType - rdodtd or wrodtd
  @param[in]      Offset  - signed offset
  @param[in]      UpdateHost - Switch to update the host struct with the new value.

  @retval Nothing.
**/
void
MrcTatStretch (
  IN OUT MrcParameters *const MrcData,
  IN UINT8                   Channel,
  IN UINT8                   OdtType,
  IN  INT8                   Offset,
  IN  BOOLEAN                UpdateHost
  );

/**
  This function updates the MRC Output structure with the values for turnaround times.
  If the turnaround values are different per channel, then the slowest turnaround will be placed in the output structure

  @param[in, out] MrcData  - The MRC "global data" area.

  @retval Nothing.
**/
void
MrcUpdateTatOutputs (
  IN OUT MrcParameters *const MrcData
  );

/**
  This function applies the turnaround timing overrides, if any, which are specified in the MRC Input structure.

  @param[in, out] MrcData  - The MRC "global data" area.

  @retval Nothing.
**/
void
MrcTurnaroundTimingOverrides (
  IN OUT MrcParameters *const MrcData
  );


#endif // _MrcTimingConfiguration_h_
