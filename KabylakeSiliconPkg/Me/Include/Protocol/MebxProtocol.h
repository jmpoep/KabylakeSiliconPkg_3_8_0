/** @file
  EFI MEBx Protocol

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
#ifndef _MEBX_PROTOCOL_H
#define _MEBX_PROTOCOL_H

#define MEBX_CALLBACK_INFO_SIGNATURE    SIGNATURE_32 ('m', 'e', 'b', 'x')

#define MEBX_CALLBACK_INFO_FROM_THIS(a) CR (a, MEBX_CALLBACK_INFO, DriverCallback, MEBX_CALLBACK_INFO_SIGNATURE)


/**
  Function for invoking MEBX binary

  @param[in]  BiosParams          MebxBiosParams flat data
  @param[out] MebxReturnValue     MebxExitCode returned by Mebx

  @exception EFI_SUCCESS          Command succeeded
**/
typedef
EFI_STATUS
(EFIAPI *MEBX_API_ENTRY_POINT) (
  IN UINT32  BiosParams,
  OUT UINT32 *MebxReturnValue
  );

typedef struct _MEBX_VER {
  UINT16  Major;
  UINT16  Minor;
  UINT16  Hotfix;
  UINT16  Build;
} MEBX_VER;

typedef enum {
  MEBX_GRAPHICS_AUTO    = 0,
  MEBX_GRAPHICS_640X480,
  MEBX_GRAPHICS_800X600,
  MEBX_GRAPHICS_1024X768
} MEBX_GRAPHICS_MODE;

typedef enum {
  MEBX_TEXT_AUTO        = 0,
  MEBX_TEXT_80X25,
  MEBX_TEXT_100X31
} MEBX_TEXT_MODE;

/**
  MEBX protocol
  The interface for invoking MEBX binary
**/
typedef struct _MEBX_PROTOCOL {
  MEBX_VER                  MebxVersion;
  MEBX_API_ENTRY_POINT      CoreMebxEntry;
} MEBX_PROTOCOL;

typedef struct _MEBX_INSTANCE {
  EFI_HANDLE        Handle;
  MEBX_PROTOCOL     MebxProtocol;
} MEBX_INSTANCE;

extern EFI_GUID gMebxProtocolGuid;

#endif
