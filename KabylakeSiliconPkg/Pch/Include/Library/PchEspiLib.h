/** @file
  Header file for PchEspiLib.
  All function in this library is available for PEI, DXE, and SMM,

 @copyright
  INTEL CONFIDENTIAL
  Copyright 2014 - 2017 Intel Corporation.

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

#ifndef _PCH_ESPI_LIB_H_
#define _PCH_ESPI_LIB_H_

/**
  Is eSPI enabled in strap.

  @retval TRUE          Espi is enabled in strap
  @retval FALSE         Espi is disabled in strap
**/
BOOLEAN
IsEspiEnabled (
  VOID
  );

/**
  Get configuration from eSPI slave

  @param[in]  SlaveId       eSPI slave ID
  @param[in]  SlaveAddress  Slave Configuration Register Address
  @param[out] OutData       Configuration data read

  @retval EFI_SUCCESS           Operation succeed
  @retval EFI_INVALID_PARAMETER Slave ID is not supported
  @retval EFI_INVALID_PARAMETER Slave ID is not supported or SlaveId 1 is used in PchLp
  @retval EFI_INVALID_PARAMETER Slave configuration register address exceed maximum allowed
  @retval EFI_INVALID_PARAMETER Slave configuration register address is not DWord aligned
  @retval EFI_DEVICE_ERROR      Error in SCRS during polling stage of operation
**/
EFI_STATUS
PchEspiSlaveGetConfig (
  IN  UINT32 SlaveId,
  IN  UINT32 SlaveAddress,
  OUT UINT32 *OutData
  );

/**
  Set eSPI slave configuration

  @param[in]  SlaveId       eSPI slave ID
  @param[in]  SlaveAddress  Slave Configuration Register Address
  @param[in]  InData        Configuration data to write

  @retval EFI_SUCCESS           Operation succeed
  @retval EFI_INVALID_PARAMETER Slave ID is not supported or SlaveId 1 is used in PchLp
  @retval EFI_INVALID_PARAMETER Slave configuration register address exceed maximum allowed
  @retval EFI_INVALID_PARAMETER Slave configuration register address is not DWord aligned
  @retval EFI_ACCESS_DENIED     eSPI Slave write to address range 0 to 0x7FF has been locked
  @retval EFI_DEVICE_ERROR      Error in SCRS during polling stage of operation
**/
EFI_STATUS
PchEspiSlaveSetConfig (
  IN  UINT32 SlaveId,
  IN  UINT32 SlaveAddress,
  IN  UINT32 InData
  );

/**
  Get status from eSPI slave

  @param[in]  SlaveId       eSPI slave ID
  @param[out] OutData       Configuration data read

  @retval EFI_SUCCESS           Operation succeed
  @retval EFI_INVALID_PARAMETER Slave ID is not supported or SlaveId 1 is used in PchLp
  @retval EFI_DEVICE_ERROR      Error in SCRS during polling stage of operation
**/
EFI_STATUS
PchEspiSlaveGetStatus (
  IN  UINT32 SlaveId,
  OUT UINT16 *OutData
  );

/**
  eSPI slave in-band reset

  @param[in]  SlaveId       eSPI slave ID

  @retval EFI_SUCCESS           Operation succeed
  @retval EFI_INVALID_PARAMETER Slave ID is not supported or SlaveId 1 is used in PchLp
  @retval EFI_DEVICE_ERROR      Error in SCRS during polling stage of operation
**/
EFI_STATUS
PchEspiSlaveInBandReset (
  IN  UINT32 SlaveId
  );

#endif // _PEI_DXE_SMM_PCH_ESPI_LIB_H_
