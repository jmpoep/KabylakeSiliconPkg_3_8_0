/** @file
  This file contains definitions of WDT functions.

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

@par Specification Reference:
**/

#ifndef _WDT_PEI_H_
#define _WDT_PEI_H_

/**
  This runtine clears status bits and disable watchdog, then lock the
  WDT registers.
  while WDT is designed to be disabled and locked by policy,
  bios should not enable WDT by WDT PPI. In such case, bios shows the
  warning message but not disable and lock WDT register to make sure
  WDT event trigger correctly.

  @param[in] DisableAndLock             Policy to disable and lock WDT register

  @retval    NONE
**/
VOID
WdtOnPolicyInstalled (
  BOOLEAN                               DisableAndLock
  );

/**
  Initializes watchdog failure bits.
  If there was an unexpected reset, enforces WDT expiration.
  Stores initial WDT state in a HOB, it is useful in flows with S3/S4 resume.
  Stops watchdog.
  Installs watchdog PPI for other modules to use.

  @retval EFI_SUCCESS             When everything is OK
**/
EFI_STATUS
EFIAPI
WdtEarlyInit (
  VOID
  );

/**
  Support for WDT in S3 resume.
  If WDT was enabled during S0->S3 transition, this function will turn on WDT
  just before waking OS. Timeout value will be overridden if it was too small.

  @retval EFI_SUCCESS             When everything is OK
  @retval EFI_NOT_FOUND           WdtHob is not found
**/
EFI_STATUS
WdtEndOfPeiCallback (
  VOID
  );
#endif // _WDTPEI_H_
