/** @file
  Read receive enable training definitions.

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
#ifndef _MrcReadReceiveEnable_h_
#define _MrcReadReceiveEnable_h_

#include "MrcTypes.h"
#include "MrcApi.h"
#include "MrcCommon.h"
#include "MrcCrosser.h"
#include "MrcGlobal.h"
#include "MrcTimingConfiguration.h"
#include "MrcHalRegisterAccess.h"

#define HW_IOLATENCY_OFFSET_DELAY       (21)  // HW constant: io_lat offset (known before as io_comp)
#define HW_RFR_DELAY                    (14)  // HW constant: RFR delay for SKL
#define MRC_IO_LATENCY_INIT_VALUE       (4)   // SKL HW constraints
#define MRC_IO_LATENCY_INIT_VALUE_1067  (3)   // SKL HW constraints
#define MRC_ROUND_TRIP_INIT_VALUE       (100) // Initial Roundtrip Latency value
#define MRC_MC_FIFO_GUARDBAND           (5)   // This is added to the roundtrip

///
/// ReadReceiveEnable (RRE) parameters
/// Command training will reduce this by 64, so plan for that now in the ideal value
///
#define RRE_PI_IDEAL       (256 + 64)
#define RRE_ALL_RANKS_MASK (0x0F)
#define RRE_PI_TO_RESERVE  (64)

/**
  Perform receive enable training.
  Optimize RcvEn timing with MPR pattern

  @param[in, out] MrcData - Include all MRC global data.

  @retval MrcStatus -  if succeeded, return mrcSuccess
**/
extern
MrcStatus
MrcReadLevelingTraining (
  IN OUT MrcParameters *const MrcData
  );

/**
  Apply an signed offset to all selected bytes/ ranks in a channel to RcvEn timing
  Robustly handles any carries to/from the IO Latency vs. RcvEn FlyBy
  PiReserve will reserve a certain number of +/- PI ticks for margin purposes
  Routine also minimizes the difference in RcvEn settings across ranks

  @param[in,out] MrcData       - MRC Global Data
  @param[in]     Channel       - The channel to adjust
  @param[in]     RankMask      - Mask of Ranks to adjust
  @param[in]     ByteMask      - Mask of Bytes to adjust by the RcvEnOffset
  @param[in]     RcvEnOffset   - Amount to offset RcvEn
  @param[in]     PiReserve     - The number of PiTicks to reserve on each edge of RcvEn

  @retval MrcStatus - mrcSuccess if successfull
                      mrcWrongInputParameter if channel doesnt exist or a RankMask of 0 is provided
                      mrcReadLevelingError if we over/underflow RT_IOCOMP field.
**/
MrcStatus
MrcChangeRcvEnTiming (
  IN OUT MrcParameters *const MrcData,
  IN     const UINT8          Channel,
  IN     const UINT8          RankMask,
  IN     const UINT16         ByteMask,
  IN     const INT16          RcvEnOffset,
  IN     const INT16          PiReserve
  );

/**
  Once the DQS high phase has been found (for each DRAM) the next stage is to find out the round trip latency,
  by locating the preamble cycle. This is achieved by trying smaller and smaller roundtrip
  values until the strobe sampling is done on the preamble cycle.
  The following algorithm is used to find the preamble cycle:

  @param[in] MrcData         - all the global data

  @retval Nothing.
**/
extern
MrcStatus
MrcRoundTripLatency (
  IN     MrcParameters *const MrcData
  );

/**
  Perform Receive Enable Timing Centering.
  Center Receive Enable using moderate pattern with 1D eye

  @param[in] MrcData         - Include all MRC global data.

  @retval MrcStatus       - if it succeded returns mrcSuccess
**/
MrcStatus
MrcReceiveEnTimingCentering (
  IN MrcParameters *const MrcData
  );

#endif // _MrcReadReceiveEnable_h_
