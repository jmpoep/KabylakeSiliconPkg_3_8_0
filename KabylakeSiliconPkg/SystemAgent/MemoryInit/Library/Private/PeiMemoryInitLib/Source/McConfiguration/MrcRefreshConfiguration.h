/** @file
  This module include MRC_RefreshConfiguration external data

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
#ifndef _MrcRefreshConfiguration_h_
#define _MrcRefreshConfiguration_h_

#include "MrcTypes.h"
#include "MrcApi.h"
#include "McAddress.h"
#include "MrcCommon.h"
#include "MrcDdr3.h"
#include "MrcGlobal.h"

///
/// tDLLK values
///
#define tDLLK_VALUE_DDR3    512
#define tDLLK_DDR4_1867     597
#define tDLLK_DDR4_2400     768
#define tDLLK_DDR4_MAX      1024

///
/// tMOD values. max(12nCK,15ns)
///
#define tMOD_800            12
#define tMOD_1067           12
#define tMOD_1333           12
#define tMOD_1600           12
#define tMOD_1867           14
#define tMOD_2133           16
#define tMOD_2400           18
#define tMOD_2667           20
#define tMOD_2800           21
#define tMOD_2933           22
#define tMOD_3000           23
#define tMOD_3200           24

///
/// tZQOPER values.
///
#define tZQOPER_1600        256
#define tZQOPER_1867        299
#define tZQOPER_2133        342
#define tZQOPER_2400        384
#define tZQOPER_2667        427
#define tZQOPER_2933        470
#define tZQOPER_3200        512

//
// ZQCL and ZQCS values for LPDDR3, in [ps]
//
#define tZQCL_MIN           360000
#define tZQCS_MIN           90000

///
/// tZQCS values.
///
#define tZQCS_DDR3_FS     80000000
#define tZQCS_DDR3_CK     64
#define tZQCS_LPDDR3_FS   90000000

//
// ZQCS period values, in (tREFI * 128) units
//
#define ZQCS_PERIOD_DDR3    128   // tREFI * 128 = 7.8 us * 128 = 1ms
#define ZQCS_PERIOD_LPDDR3  256   // tREFI * 128 = 3.9 us * 128 = 0.5ms

#if (SUPPORT_DDR4 == SUPPORT)
///
/// tMOD values. max(24nCK,15ns) DDR4 (24nCK @ DDR4-3200 just matches 15ns)
///
#define tMOD_DDR4      24

///
/// tZQOPER values. DDR4 = 512nCK
///
#define tZQOPER_DDR4        512

///
/// tZQCS values. DDR4 = 128nCK
///
#define tZQCS_DDR4          128
#endif // SUPPORT_DDR4

/**
  This function returns the tZQOPER value.
  tZQOPER = Defines the period required for ZQCL after SR exit.

  @param[in] MrcData         - Include all MRC global data.
  @param[in] Frequency       - The memory frequency.

  @retval The tZQOPER value.
**/
extern
UINT32
tZQOPERGet (
  IN MrcParameters *const MrcData,
  IN const MrcFrequency Frequency
  );

/**
  This function returns the tMOD value.
  tMOD = max(12nCK, 15ns) nCK change by the frequency for DDR3
         max(24nCK, 15ns) nCK change by the frequency for DDR4

  @param[in] MrcData         - Include all MRC global data.
  @param[in] Frequency       - The memory frequency.

  @retval The tMOD value.
**/
UINT32
tMODGet (
  IN MrcParameters *const MrcData,
  IN const MrcFrequency Frequency
  );

/**
  This function returns the tZQCS value.

  @param[in] MrcData         - Include all MRC global data.
  @param[in] tCK             - DCLK period in femtoseconds.

  @retval The tZQCS value.
**/
extern
UINT32
tZQCSGet (
  IN MrcParameters *const MrcData,
  IN UINT32               tCK
  );

/**
  This function configures the TC_MR2_SHADDOW register and its fields.

  @param[in] MrcData         - Include all MRC global data.
  @param[in] Channel         - Channel to work on.
  @param[in] Dimm            - Dimm to work on.
  @param[in] Mr2Value        - The value of MR2 to setup.

  @retval Nothing.
**/
extern
void
SetTcMr2ShadowReg (
  IN MrcParameters *const MrcData,
  IN const UINT32         Channel,
  IN const UINT32         Dimm,
  IN UINT32               Mr2Value
  );

/**
  This function configures TC_RFP and TC_RFTP registers and their fields tREFI,
  tRFC, tREFIx9, OREF_RI.
  Note that TC_RFTP.tREFIx9 was moved to TC_RFP from SKL B0 onwards.

  @param[in] MrcData  - Include all MRC global data.
  @param[in] Channel  - Channel to work on.

  @retval Nothing.
**/
extern
void
SetTcRfpRftpReg (
  IN MrcParameters *const MrcData,
  IN const UINT32         Channel
  );

/**
  This function executes the refresh configuration process.

  @param[in] MrcData         - Include all MRC global data.

  @retval Nothing.
**/
extern
void
MrcRefreshConfiguration (
  IN MrcParameters *const MrcData
  );

#endif
