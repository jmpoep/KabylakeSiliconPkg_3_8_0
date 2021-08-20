/** @file
  Memory test delay module.

 @copyright
  INTEL CONFIDENTIAL
  Copyright 2011 - 2015 Intel Corporation.

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
#include "DcttWrapper.h"
#include "DcttPauseRefresh.h"

UINT32
DelayTime_GetNumberWaitUnits (
  DelayTime *self,
  UINT32    waitTimens
  )
{
  // TODO: Check if its worth it to do this scaling or if setting the waitUnit to ns is enough.
  UINT32 numberWaitUnits;
  //Check if we can scale waitTime up to use integer math
  if (waitTimens < 4000) {
    //Scaling it up to fs
    waitTimens = waitTimens * 1000000;
    numberWaitUnits = waitTimens / self->waitUnitfs;
  } else if (waitTimens < 4000000) {
    //Scaling everything to ps
    waitTimens = waitTimens * 1000;
    //numberWaitUnits = waitTimens / (self->waitUnitfs / 1000);
    numberWaitUnits = waitTimens / self->waitUnitps;
  } else {
    //Scaling the wait units to ns
    //numberWaitUnits = waitTimens / (self->waitUnitfs / 1000000);
    numberWaitUnits = waitTimens / self->waitUnitns;
  }

  return numberWaitUnits;
}

/*
  This function calculates the time
  Function assumes that the memory is being traversed Col then Row.

  @param[in] self       - DelayTime struct pointer used for time calculation
  @param[in] loopcount  - Current loopcount of the test.

  @retval -
*/
UINT32
DelayTime_GetTimensFromLoopcount (
  DelayTime *self,
  UINT32    loopCount
  )
{
  UINT32 totalTime;

  ////totalTime = ((1000 * loopCount * self->cachelineSizeBytes) / self->memFrequencyMHz) +
  ////          (loopCount * self->oneRowDelayns)/self->numCachelineCols;

  if (loopCount < self->maxLCCachelineMult) {
    totalTime = (1000 * self->cachelineSizeBytes * loopCount) / self->memFrequencyMHz;
  } else {
    //If we multiply on this case we will overflow the register; divide instead
    ////TODO: theoretically there still could be an overflow here, see if we need to check for it
    totalTime = 1000 * self->cachelineSizeBytes * (loopCount / self->memFrequencyMHz);
  }

  totalTime = totalTime + (self->perRowExtraDelayns * (loopCount / self->numCachelinesPerCol));
  //totalTime = totalTime +  (self->oneRowDelayns * (loopCount / self->numCachelinesPerCol));
  ////if (loopCount < self->maxLCRowDelayMult)
  ////{
  ////  totalTime = totalTime + ((self->oneRowDelayns * loopCount)/self->numCachelinesPerCol);
  ////}
  ////else
  ////{
  ////  totalTime = totalTime +  (self->oneRowDelayns * (loopCount / self->numCachelinesPerCol));
  ////}

  return totalTime;
}

//This function assumes that the memory is being traversed Col then Row
UINT32
DelayTime_GetLoopcountFromTimens (
  DelayTime *self,
  UINT32    waitTimens
  )
{
  UINT32 desiredLC;

  if (waitTimens < self->oneRowDelayns) {
    //Delay is less than one column
    //This is not supported (at least not at this point).
    desiredLC = 0;
  } else {
    if (waitTimens < self->maxTimeRowCachMult) {
      desiredLC = (self->numCachelinesPerCol * waitTimens) / self->oneRowDelayns;
    } else {
      desiredLC = self->numCachelinesPerCol * (waitTimens / self->oneRowDelayns);
    }

  }

  return desiredLC;
}

VOID
DelayTime_Init (
  DelayTime *Self,
  UINT32    McFrequencyMhz,
  UINT16    ExtraRowDelayNs,
  UINT32    ColumnSize,
  UINT32    MinDelayFS
  )
{
  Self->memFrequencyMHz = McFrequencyMhz;
  Self->cachelineSizeBytes = CPGC_NUMBER_BYTES_CACHELINES;
  Self->perRowExtraDelayns = ExtraRowDelayNs;
  Self->maxLCCachelineMult = ((UINT32) -1) / (1000 * Self->cachelineSizeBytes);
  Self->waitUnitfs = MinDelayFS; //69841279;  // 69.841279ns = 69841279fs
  Self->waitUnitps = (MinDelayFS + 500) / 1000; //69841;
  Self->waitUnitns = (MinDelayFS + 500000) / 1000000; //70;
  DelayTime_UpdateCacheLinesPerCol (Self, ColumnSize);
}

VOID
DelayTime_UpdateCacheLinesPerCol (
  DelayTime *Self,
  UINT32     ColumnSize
  )
{
  if (ColumnSize != 0) {
    Self->numCachelinesPerCol = ColumnSize >> CPGC_NUMBER_BITS_CACHELINE;
    Self->oneRowDelayns =
      (((1000 * Self->numCachelinesPerCol * Self->cachelineSizeBytes) / Self->memFrequencyMHz)) +
      Self->perRowExtraDelayns;
    Self->maxTimeRowCachMult = ((UINT32) -1) / Self->numCachelinesPerCol;
    Self->maxLCRowDelayMult = ((UINT32) -1) / Self->oneRowDelayns;
  }
}
