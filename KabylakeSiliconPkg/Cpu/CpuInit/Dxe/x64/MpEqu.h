/** @file
  This is the equates file used in MpFuncs.S, for MP support.

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

#define VacantFlag    0x00
#define NotVacantFlag 0xff
#define BreakToRunApSignal             0x6E755200
#define MonitorFilterSize              0x40
#define WakeUpApCounterInit            0
#define WakeUpApPerHltLoop             1
#define WakeUpApPerMwaitLoop           2
#define WakeUpApPerRunLoop             3
#define WakeUpApPerMwaitLoop32         4
#define WakeUpApPerRunLoop32           5

#define LockLocation                   (0x1000 - 0x0400)
#define StackStartAddressLocation      (LockLocation + 0x08)
#define StackSizeLocation              (LockLocation + 0x10)
#define CProcedureLocation             (LockLocation + 0x18)
#define GdtrLocation                   (LockLocation + 0x20)
#define IdtrLocation                   (LockLocation + 0x2A)
#define BufferStartLocation            (LockLocation + 0x34)
#define Cr3OffsetLocation              (LockLocation + 0x38)
#define InitFlagLocation               (LockLocation + 0x3C)
#define WakeUpApManner                 (LockLocation + 0x40)
#define BistBuffer                     (LockLocation + 0x44)

//-------------------------------------------------------------------------------
