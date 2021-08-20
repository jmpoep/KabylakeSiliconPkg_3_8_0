/** @file
  Header file for PchHsioLib.

 @copyright
  INTEL CONFIDENTIAL
  Copyright 2014 - 2016 Intel Corporation.

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
#ifndef _PCH_HSIO_LIB_H_
#define _PCH_HSIO_LIB_H_

/**
  Represents HSIO lane
**/
typedef struct {
  UINT8        Index; ///< Lane index
  UINT8        Pid;   ///< Sideband ID
  UINT16       Base;  ///< Sideband base address
} HSIO_LANE;

/**
  The function returns the Port Id and lane owner for the specified lane

  @param[in]  PhyMode             Phymode that needs to be checked
  @param[out] Pid                 Common Lane End Point ID
  @param[out] LaneOwner           Lane Owner

  @retval EFI_SUCCESS             Read success
  @retval EFI_INVALID_PARAMETER   Invalid lane number
**/
EFI_STATUS
EFIAPI
PchGetLaneInfo (
  IN  UINT32                            LaneNum,
  OUT UINT8                             *PortId,
  OUT UINT8                             *LaneOwner
  );

/**
  Get HSIO lane representation needed to perform any operation on the lane.

  @param[in]  LaneIndex  Number of the HSIO lane
  @param[out] HsioLane   HSIO lane representation
**/
VOID
HsioGetLane (
  IN   UINT8       LaneIndex,
  OUT  HSIO_LANE   *HsioLane
  );

/**
  Determine the lane number of a specified port

  @param[in]  PcieLaneIndex             PCIE Root Port Lane Index
  @param[out] LaneNum                   Lane Number

  @retval EFI_SUCCESS                   Lane number valid.
  @retval EFI_UNSUPPORTED               Incorrect input device port
**/
EFI_STATUS
PchGetPcieLaneNum (
  UINT32              PcieLaneIndex,
  UINT8               *LaneNum
  );

/**
  Determine the lane number of a specified port

  @param[in]  SataLaneIndex             Sata Lane Index
  @param[out] LaneNum                   Lane Number

  @retval EFI_SUCCESS                   Lane number valid.
  @retval EFI_UNSUPPORTED               Incorrect input device port
**/
EFI_STATUS
PchGetSataLaneNum (
  UINT32              SataLaneIndex,
  UINT8               *LaneNum
  );

/**
  Determine the lane number of a specified port

  @param[in]  Usb3LaneIndex             USB3 Lane Index
  @param[out] LaneNum                   Lane Number

  @retval EFI_SUCCESS                   Lane number valid.
  @retval EFI_UNSUPPORTED               Incorrect input device port
**/
EFI_STATUS
PchGetUsb3LaneNum (
  UINT32              Usb3LaneIndex,
  UINT8               *LaneNum
  );

/**
  Determine the lane number of a specified port

  @param[out] LaneNum                   GBE Lane Number

  @retval EFI_SUCCESS                   Lane number valid.
  @retval EFI_UNSUPPORTED               Incorrect input device port
**/
EFI_STATUS
PchGetGbeLaneNum (
  UINT8               *LaneNum
  );

#endif // _PCH_HSIO_LIB_H_
