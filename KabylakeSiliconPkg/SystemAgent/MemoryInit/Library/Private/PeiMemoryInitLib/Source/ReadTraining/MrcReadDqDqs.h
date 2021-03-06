/** @file
  Read DQ/DQS training definitions.

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
#ifndef _MrcReadDqDqs_h_
#define _MrcReadDqDqs_h_

#include "MrcTypes.h"
#include "MrcApi.h"
#include "McAddress.h"
#include "MrcCommon.h"
#include "MrcGlobal.h"

#define RMPR_DQS_START (-31)
#define RMPR_DQS_STOP  (32)

    #define RMPR_DQS_STEP (1)

#define RMPR_MIN_WIDTH (12)

/**
  Perform Read MPR Training.
  Center read DQ-DQS with MPR pattern.

  @param[in, out] MrcData   - Include all MRC global data.

  @retval MrcStatus - mrcSuccess or reason for failure.
**/
extern
MrcStatus
MrcReadMprTraining (
  IN OUT MrcParameters *const MrcData
  );

/**
  Perform Read MPR Training.
  Center read DQ-DQS with MPR pattern.
  This is the HW method of the Read MPR algorithm.

  @param[in, out] MrcData   - Include all MRC global data.

  @retval MrcStatus - mrcSuccess or reason for failure.
**/
MrcStatus
ReadMprTraining (
  IN OUT MrcParameters *const MrcData,
  IN     BOOLEAN              Print
  );

/**
  Peform Read Timing Centering.
  Center Rx DQS-DQ using moderate pattern with 1D eye

  @param[in] MrcData         - Include all MRC global data.

  @retval MrcStatus       - if it succeded returns mrcSuccess
**/
extern
MrcStatus
MrcReadTimingCentering (
  IN     MrcParameters *const MrcData
  );

/**
  This function executes the read Voltage centering .
  Center Rx DQ Vref using moderate pattern with 1D eye.

  @param[in] MrcData         - Include all MRC global data.

  @retval MrcStatus      - if it succeded returns mrcSuccess
**/
extern
MrcStatus
MrcReadVoltageCentering (
  IN     MrcParameters *const MrcData
  );

/**
  Peform Read Timing Centering in 2D.
  Final read timing centering using 2D algorithm and per bit optimization

  @param[in] MrcData         - Include all MRC global data.

  @retval MrcStatus       - if it succeded returns mrcSuccess
**/
extern
MrcStatus
MrcReadTimingCentering2D (
  IN     MrcParameters *const MrcData
  );

/**
  Peform Read Voltage Centering in 2D.
  Note: This function currently only supports param = RdV

  @param[in] MrcData       - Include all MRC global data.

  @retval MrcStatus       - if it succeded return mrcSuccess
**/
extern
MrcStatus
MrcReadVoltageCentering2D (
  IN     MrcParameters *const MrcData
  );

/**
  Perform Read Timing Linear Centering in different Read Vref points using MPR mode.
  (Does not require Writes to be functional)

  @param[in] MrcData       - Include all MRC global data.

  @retval MrcStatus       - if it success return mrcSuccess
**/
MrcStatus
MrcEarlyReadMprTimingCentering2D (
  IN     MrcParameters *const MrcData
  );

/**
  Perform Early Read 2D centring Training.
  Center read DQ-DQS while testing differents RxVref points.

  @param[in, out] MrcData   - Include all MRC global data.
  @param[in]      Prints    - Debug prints enable/disable

  @retval MrcStatus - mrcSuccess or reason for failure.
**/
MrcStatus
  EarlyReadTimingCentering2D (
  IN     MrcParameters *const MrcData,
  IN     BOOLEAN              Prints
  );

/**
  Perform Early Read 2D centring Training.
  Center read DQ-DQS while testing differents RxVref points.

  @param[in, out] MrcData   - Include all MRC global data.

  @retval MrcStatus - mrcSuccess or reason for failure.
**/
MrcStatus
  MrcEarlyReadTimingCentering2D (
  IN     MrcParameters *const MrcData
  );
#endif // _MrcReadDqDqs_h_
