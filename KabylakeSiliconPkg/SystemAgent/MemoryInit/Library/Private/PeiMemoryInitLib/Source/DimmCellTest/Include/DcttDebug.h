/** @file
  Contains macros and definitions for Error and Debug handling.

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

#ifndef _DCTT_DEBUG_H_
#define _DCTT_DEBUG_H_

#define CONTINUE            DCTT_SUCCESS
#define PARSER_ERROR_FOUND  2
#define PARSER_ERROR_RERUN  8

///
/// DcttLogDebug define controls release mode versus debug mode based on DCTT_DEBUG_LOG_LEVEL enumeration.
// @todo /// In addition, this define will remove the string based functions that support printing.
///   Not Defined - All Asserts, Debug Log, and Prints are removed.
///   Defined (See DcttApi.h - DCTT_LOG_LEVELS):
///     >= DCTT_LOG_NORMAL  - Enables DcttOutputPrint.
///     >= DCTT_LOG_VERBOSE - Enables DcttLogVerbose.
///     >= DCTT_LOG_DEBUG   - Enables DcttLogDebug, and DcttError_Assert.
///

///
/// Make sure DCTT_LOG_LEVELS enum in DcttApi.h matches these defines below.
///
#define DCTT_LOG_NORMAL   1
#define DCTT_LOG_VERBOSE  25
#define DCTT_LOG_DEBUG    50

#ifdef DCTT_DEBUG_LOG_LEVEL
  #if DCTT_DEBUG_LOG_LEVEL >= DCTT_LOG_NORMAL
    #define DcttOutputPrint(MainHandle, FormatString, ...) if ((MainHandle)->DebugLevel >= (DCTT_LOG_NORMAL)) \
      DcttPrintFunc (MainHandle, FormatString, ## __VA_ARGS__)
  #else
    #define DcttOutputPrint(MainHandle, FormatString, ...)
  #endif // DCTT_DEBUG_LOG_LEVEL >= DCTT_NORMAL_LEVEL

  #if DCTT_DEBUG_LOG_LEVEL >= DCTT_LOG_VERBOSE
    #define DcttLogVerbose(MainHandle, FormatString, ...) if ((MainHandle)->DebugLevel >= (DCTT_LOG_VERBOSE)) \
      DcttPrintFunc (MainHandle, FormatString, ## __VA_ARGS__)
  #else
    #define DcttLogVerbose(MainHandle, FormatString, ...)
  #endif // DCTT_DEBUG_LOG_LEVEL >= DcttLogVerbose

  #if DCTT_DEBUG_LOG_LEVEL >= DCTT_LOG_DEBUG
    #define DcttLogDebug(MainHandle, FormatString, ...) if ((MainHandle)->DebugLevel >= (DCTT_LOG_DEBUG)) \
      DcttPrintFunc (MainHandle, FormatString, ## __VA_ARGS__)
    #define DcttError_UAssert(Condition) while (!(Condition))
    #define DcttError_Assert(MainHandle, Condition, FormatString, ...) if (!(Condition)) {\
        DcttOutputPrint (MainHandle, "(File: %s, Line: %d): ", __FILE__, __LINE__); \
        DcttOutputPrint (MainHandle, FormatString, ## __VA_ARGS__);\
      }\
      DcttError_UAssert(Condition)
  #else
    #define DcttLogDebug(MainHandle, FormatString, ...)
    #define DcttError_UAssert(Condition)
    #define DcttError_Assert(MainHandle, Condition, FormatString, ...)
  #endif // DCTT_DEBUG_LOG_LEVEL >= DcttLogDebug
#else
  #define DcttError_UAssert(Condition)
  #define DcttError_Assert(MainHandle, Condition, FormatString, ...)
  #define DcttOutputPrint(MainHandle, FormatString, ...)
  #define DcttLogVerbose(MainHandle, FormatString, ...)
  #define DcttLogDebug(MainHandle, FormatString, ...)
#endif // DCTT_LOG_LEVEL
#endif // _DCTT_DEBUG_H_
