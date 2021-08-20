/** @file
  Pause Refresh module definitions.

 @copyright
  INTEL CONFIDENTIAL
  Copyright 2011 - 2016 Intel Corporation.

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

@par Specification
**/

#ifndef _DCTT_PAUSE_REFRESH_H_
#define _DCTT_PAUSE_REFRESH_H_
#include "DcttCpgcFunctions.h"

typedef struct DelayTime {
  UINT32 oneRowDelayns;
  UINT32 memFrequencyMHz;
  UINT32 numCachelinesPerCol;
  UINT32 cachelineSizeBytes;
  UINT32 perRowExtraDelayns;
  UINT32 maxLCCachelineMult;
  UINT32 maxLCRowDelayMult;
  UINT32 maxTimeRowCachMult;
  UINT32 waitUnitfs;
  UINT32 waitUnitps;
  UINT32 waitUnitns;
} DelayTime;

UINT32
DelayTime_GetNumberWaitUnits (
  DelayTime* self,
  UINT32 waitTimens
  );

//This function assumes that the memory is being traversed Col then Row
UINT32
DelayTime_GetTimensFromLoopcount (
  DelayTime* self,
  UINT32 loopCount
  );

//This function assumes that the memory is being traversed Col then Row
UINT32
DelayTime_GetLoopcountFromTimens (
  DelayTime* self,
  UINT32 waitTimens
  );

VOID
DelayTime_Init (
  DelayTime *Self,
  UINT32    McFrequencyMhz,
  UINT16    ExtraRowDelayNs,
  UINT32    ColumnSize,
  UINT32    MinDelayFS
  );

VOID
DelayTime_UpdateCacheLinesPerCol (
  DelayTime *Self,
  UINT32     ColumnSize
  );
#endif // _DCTT_PAUSE_REFRESH_H_
