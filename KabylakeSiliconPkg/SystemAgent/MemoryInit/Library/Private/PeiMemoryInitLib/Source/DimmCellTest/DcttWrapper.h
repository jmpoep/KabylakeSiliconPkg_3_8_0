/** @file
  Dimm Cell Test Tool (DCTT) Wrapper abstracts platform specific defines
  to be used within the tool.  This must be updated for each platform.

 @copyright
  INTEL CONFIDENTIAL
  Copyright 2013 - 2016 Intel Corporation.

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

#ifndef _DCTT_WRAPPER_H_
#define _DCTT_WRAPPER_H_

///
/// Include Type Definition Headers
///
#include "MrcTypes.h"
#include "MrcApi.h"
#include "MrcDebugPrint.h"

///
/// Data Type Defines: These types are needed for DCTT library.
///
/*
  Expected types and defines:
    unsigned long long  UINT64;
    unsigned long       UINT32;
    unsigned short      UINT16;
    unsigned char       UINT8;
    unsigned char       BOOLEAN;
      FALSE = 0
      TRUE  = 1
    signed long long    INT64;
    signed long         INT32;
    signed short        INT16;
    signed char         INT8;
    void                VOID;
      NULL
*/

///
/// Debug Level Definition
/// See DcttDebug.h for debug compile levels.
/// See DCTT_LOG_LEVELS in DcttApi.h for runtime debug levels.
/// Note: Runtime Levels are limited to compile levels.
///
#ifdef MRC_DEBUG_PRINT
#define DCTT_DEBUG_LOG_LEVEL (1)
#endif // MRC_DEBUG_PRINT

#ifdef __GNUC__
#define DCTTINLINE static inline
#else
#define DCTTINLINE _inline
#endif

///
/// System information
///
#define DCTT_MAX_NUM_CHANNELS       (MAX_CHANNEL)
#define DCTT_MAX_RANK_IN_CHANNEL    (MAX_RANK_IN_CHANNEL)
#define DCTT_MAX_RANK_IN_DIMM       (MAX_RANK_IN_DIMM)
#define DCTT_MAX_NUM_SWIZZLE_LANES  (17)                  ///< How many row lanes can be swizzled.
#define DCTT_COL_GRANULARITY        (8)                   ///< Column increment on a single memory transaction
#define DCTT_SYS_MIN_DELAY_FS       (69841279)            ///< Minimum delay system can provide in femtoseconds via DcttSysWait()
#define DCTT_WAIT_1_US              (15)                  ///< 1us delay from DcttSysWait() in DCTT_SYS_MIN_DELAY_FS.
#endif // _DCTT_WRAPPER_H_
