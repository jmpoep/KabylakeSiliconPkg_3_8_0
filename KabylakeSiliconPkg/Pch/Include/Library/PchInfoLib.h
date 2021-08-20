/** @file
  Header file for PchInfoLib.

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
#ifndef _PCH_INFO_LIB_H_
#define _PCH_INFO_LIB_H_

#include <PchAccess.h>

typedef enum {
  PchH          = 1,
  PchLp,
  PchUnknownSeries
} PCH_SERIES;

typedef enum {
  SklPch        = 1,
  KblPch,
  PchUnknownGeneration
} PCH_GENERATION;

typedef enum {
  RstUnsupported  = 0,
  RstPremium,
  RstOptane,
  RstMaxMode
} RST_MODE;

typedef enum {
  PchMobileSku = 0,
  PchDesktopSku,
  PchServerSku,
  PchUnknownSku,
  PchMaxSku
} PCH_SKU_TYPE;

/**
  Return Pch stepping type

  @retval PCH_STEPPING            Pch stepping type
**/
PCH_STEPPING
EFIAPI
PchStepping (
  VOID
  );

/**
  Determine if PCH is supported

  @retval TRUE                    PCH is supported
  @retval FALSE                   PCH is not supported
**/
BOOLEAN
IsPchSupported (
  VOID
  );

/**
  Return Pch Series

  @retval PCH_SERIES                Pch Series
**/
PCH_SERIES
EFIAPI
GetPchSeries (
  VOID
  );

/**
  Return Pch Generation

  @retval PCH_GENERATION            Pch Generation
**/
PCH_GENERATION
EFIAPI
GetPchGeneration (
  VOID
  );

/**
  Get PCH SKU type

  @retval PCH_SKU_TYPE  Type of PCH SKU
**/
PCH_SKU_TYPE
GetPchSkuType (
  VOID
  );

/**
  Get Lpc Did

  @retval  UINT16                    Lpc Did
**/
UINT16
EFIAPI
GetLpcDid (
  VOID
  );

/**
  Get Pch Maximum Pcie Root Port Number

  @retval PcieMaxRootPort         Pch Maximum Pcie Root Port Number
**/
UINT8
EFIAPI
GetPchMaxPciePortNum (
  VOID
  );

/**
  Get Pch Maximum Sata Port Number

  @retval Pch Maximum Sata Port Number
**/
UINT8
EFIAPI
GetPchMaxSataPortNum (
  VOID
  );

/**
  Get Pch Usb Maximum Physical Port Number

  @retval Pch Usb Maximum Physical Port Number
**/
UINT8
EFIAPI
GetPchUsbMaxPhysicalPortNum (
  VOID
  );

/**
  Get Pch Maximum Usb2 Port Number of XHCI Controller

  @retval Pch Maximum Usb2 Port Number of XHCI Controller
**/
UINT8
EFIAPI
GetPchXhciMaxUsb2PortNum (
  VOID
  );

/**
  Get Pch Maximum Usb3 Port Number of XHCI Controller

  @retval Pch Maximum Usb3 Port Number of XHCI Controller
**/
UINT8
EFIAPI
GetPchXhciMaxUsb3PortNum (
  VOID
  );

/**
  Get PCH stepping ASCII string
  The return string is zero terminated.

  @param [in]      PchStep              Pch stepping
  @param [out]     Buffer               Output buffer of string
  @param [in,out]  BufferSize           Size of input buffer,
                                        and return required string size when buffer is too small.

  @retval EFI_SUCCESS                   String copy successfully
  @retval EFI_INVALID_PARAMETER         The stepping is not supported, or parameters are NULL
  @retval EFI_BUFFER_TOO_SMALL          Input buffer size is too small
**/
EFI_STATUS
PchGetSteppingStr (
  IN     PCH_STEPPING                   PchStep,
  OUT    CHAR8                          *Buffer,
  IN OUT UINT32                         *BufferSize
  );

/**
  Get PCH series ASCII string
  The return string is zero terminated.

  @param [in]      PchSeries            Pch series
  @param [out]     Buffer               Output buffer of string
  @param [in,out]  BufferSize           Size of input buffer,
                                        and return required string size when buffer is too small.

  @retval EFI_SUCCESS                   String copy successfully
  @retval EFI_INVALID_PARAMETER         The series is not supported, or parameters are NULL
  @retval EFI_BUFFER_TOO_SMALL          Input buffer size is too small
**/
EFI_STATUS
PchGetSeriesStr (
  IN     PCH_SERIES                     PchSeries,
  OUT    CHAR8                          *Buffer,
  IN OUT UINT32                         *BufferSize
  );

/**
  Get PCH Sku ASCII string
  The return string is zero terminated.

  @param [in]      LpcDid               LPC device id
  @param [out]     Buffer               Output buffer of string
  @param [in,out]  BufferSize           Size of input buffer,
                                        and return required string size when buffer is too small.

  @retval EFI_SUCCESS                   String copy successfully
  @retval EFI_INVALID_PARAMETER         The series is not supported, or parameters are NULL
  @retval EFI_BUFFER_TOO_SMALL          Input buffer size is too small
**/
EFI_STATUS
PchGetSkuStr (
  IN     UINT16                         LpcDid,
  OUT    CHAR8                          *Buffer,
  IN OUT UINT32                         *BufferSize
  );

/**
  Get RST mode supported by the silicon

  @retval RST_MODE               RST mode supported by silicon
**/
RST_MODE
EFIAPI
GetSupportedRstMode (
  VOID
  );

/**
  Check if current SKU supports Optane mode

  @retval TRUE                   This SKU supports Optane mode
  @retval FALSE                  This SKU doesn't support Optane mode
**/
BOOLEAN
EFIAPI
IsOptaneModeSupported (
  VOID
  );

/**
  Check if current SKU supports RAID feature

  @retval TRUE                   This SKU supports RAID
  @retval FALSE                  This SKU doesn't support RAID
**/
BOOLEAN
EFIAPI
IsPchRaidSupported (
  VOID
  );
#endif // _PCH_INFO_LIB_H_
