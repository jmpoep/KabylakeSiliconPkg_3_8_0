/** @file
  Definitions for HECI driver

 @copyright
  INTEL CONFIDENTIAL
  Copyright 2006 - 2016 Intel Corporation.

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
#ifndef _HECI_CORE_H
#define _HECI_CORE_H

#include <CoreBiosMsg.h>
#include <MeChipset.h>

//
// Timeout values based on HPET
//
#define HECI_WAIT_DELAY             1000      ///< 1ms timeout for IO delay
#define HECI_INIT_TIMEOUT           15000000  ///< 15sec timeout in microseconds
#define HECI_READ_TIMEOUT           5000000   ///< 5sec timeout in microseconds
#define HECI_SEND_TIMEOUT           5000000   ///< 5sec timeout in microseconds
#define HECI_MAX_RETRY              3         ///< Value based off HECI HPS

//
// HECI bus function version
//
#define HBM_MINOR_VERSION 0
#define HBM_MAJOR_VERSION 1

//
// Prototypes
//
/**
  This function provides a standard way to verify the HECI cmd and MBAR regs
  in its PCI cfg space are setup properly and that the local mHeciContext
  variable matches this info.

  @param[out] HeciMemBar          HECI Memory BAR
**/
UINTN
CheckAndFixHeciForAccess (
  IN HECI_DEVICE                  HeciDev
  )
;

/**
  Waits for the ME to report that it is ready for communication over the HECI
  interface.

  @retval EFI_SUCCESS             ME is ready
  @retval EFI_TIMEOUT             ME is not ready
**/
EFI_STATUS
WaitForMEReady (
  IN HECI_DEVICE                  HeciDev
  )
;


/**
  Function to pull one messsage packet off the HECI circular buffer.
  Corresponds to HECI HPS (part of) section 4.2.4

  @param[in] Blocking             Used to determine if the read is BLOCKING or NON_BLOCKING.
  @param[out] MessageHeader       Pointer to a buffer for the message header.
  @param[in] MessageData          Pointer to a buffer to recieve the message in.
  @param[in][out] Length          On input is the size of the callers buffer in bytes. On
                                  output this is the size of the packet in bytes.

  @retval EFI_SUCCESS             One message packet read.
  @retval EFI_DEVICE_ERROR        The circular buffer is overflowed.
  @retval EFI_NO_RESPONSE         The circular buffer is empty
  @retval EFI_TIMEOUT             Failed to receive a full message
  @retval EFI_BUFFER_TOO_SMALL    Message packet is larger than caller's buffer
**/
EFI_STATUS
HeciPacketRead (
  IN      HECI_DEVICE             HeciDev,
  IN      UINT32                  Blocking,
  OUT     HECI_MESSAGE_HEADER     *MessageHeader,
  OUT     UINT32                  *MessageData,
  IN OUT  UINT32                  *Length
  )
;

/**
  Function sends one messsage packet through the HECI circular buffer
  Corresponds to HECI HPS (part of) section 4.2.3

  @param[in] MessageHeader        Pointer to the message header.
  @param[in] MessageData          Pointer to the actual message data.

  @retval EFI_SUCCESS             One message packet sent
  @retval EFI_DEVICE_ERROR        ME is not ready
  @retval EFI_TIMEOUT             HECI is not ready for communication
**/
EFI_STATUS
HeciPacketWrite (
  IN  HECI_DEVICE                 HeciDev,
  IN  HECI_MESSAGE_HEADER         *MessageHeader,
  IN  UINT32                      *MessageData
  )
;


#endif // _HECI_CORE_H

