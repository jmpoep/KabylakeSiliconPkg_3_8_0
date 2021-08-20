/** @file
  PCH Reset PPI

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

@par Specification Reference:
**/

#ifndef _PCH_RESET_PPI_H_
#define _PCH_RESET_PPI_H_

//
// Extern the GUID for PPI users.
//
extern EFI_GUID gPchResetPpiGuid;
extern EFI_GUID gPchResetCallbackPpiGuid;

//
// Forward reference for ANSI C compatibility
//
typedef struct _PCH_RESET_PPI          PCH_RESET_PPI;
typedef struct _PCH_RESET_CALLBACK_PPI PCH_RESET_CALLBACK_PPI;

//
// Related Definitions
//
//
// PCH Reset Types
//
typedef enum {
  PchColdReset     = 0,
  PchWarmReset     = 1,
  PchShutdownReset = 2,
  PchGlobalReset   = 4,
  PchResetTypeMax
} PCH_RESET_TYPE;

//
// Member functions
//
/**
  Execute Pch Reset from the host controller.

  @param[in] This                 Pointer to the PCH_RESET_PPI instance.
  @param[in] PchResetType         Pch Reset Types which includes ColdReset, WarmReset,
                                  ShutdownReset, GlobalReset

  @retval EFI_SUCCESS             Successfully completed.
  @retval EFI_INVALID_PARAMETER   If ResetType is invalid.
**/
typedef
EFI_STATUS
(EFIAPI *PCH_RESET_PPI_API) (
  IN  PCH_RESET_PPI  *This,
  IN  PCH_RESET_TYPE PchResetType
  );

/**
  Execute call back function for Pch Reset.

  @param[in] PchResetType         Pch Reset Types which includes PowerCycle, Globalreset.

  @retval EFI_SUCCESS             The callback function has been done successfully
  @retval EFI_NOT_FOUND           Failed to find Pch Reset Callback ppi. Or, none of
                                  callback ppi is installed.
  @retval Others                  Do not do any reset from PCH
**/
typedef
EFI_STATUS
(EFIAPI *PCH_RESET_CALLBACK) (
  IN     PCH_RESET_TYPE           PchResetType
  );

/**
  Interface structure to execute Pch Reset from the host controller.
**/
struct _PCH_RESET_PPI {
  PCH_RESET_PPI_API Reset;
};

/**
  This ppi is used to execute PCH Reset from the host controller.
  The PCH Reset protocol and PCH Reset PPI implement the Intel (R) PCH Reset Interface
  for DXE and PEI environments, respectively. If other drivers need to run their
  callback function right before issuing the reset, they can install PCH Reset
  Callback Protocol/PPI before PCH Reset DXE/PEI driver to achieve that.
**/
struct _PCH_RESET_CALLBACK_PPI {
  PCH_RESET_CALLBACK  ResetCallback;
};

#endif
