/** @file
This file contains the BIOS SSA logging information.

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
#ifndef __BSSA_LOGGING_H__
#define __BSSA_LOGGING_H__

#include "MrcSsaServices.h"

#define BSSA_LOGGING_INTERNAL_DEBUG_LEVEL  50
#define BSSA_LOGGING_INTERNAL_NORMAL_LEVEL 25
#define BSSA_LOGGING_NORMAL_LEVEL          0

#ifndef BSSA_LOGGING_LEVEL
#define BSSA_LOGGING_LEVEL BSSA_LOGGING_INTERNAL_NORMAL_LEVEL
#endif

//PrintLevels
#define BSSA_LOGGING_WARNING SSA_D_WARN  ///< Warnings
#define BSSA_LOGGING_LOAD    SSA_D_LOAD  ///< Load events
#define BSSA_LOGGING_INFO    SSA_D_INFO  ///< Informational debug messages
#define BSSA_LOGGING_EVENT   SSA_D_EVENT ///< Event messages
#define BSSA_LOGGING_ERROR   SSA_D_ERROR ///< Error

/**
  BIOS hook handler function.

  @param[in, out] - SSA_BIOS_SERVICES_PPI *SsaBiosServices: Interface pointer that implements the particular SSA_BIOS_SERVICES_PPI instance.
  @param[in]      - PRINT_LEVEL newPrintLevel: Enum used to determine if the message should be output to debug print device.

  @retval Nothing.
**/
#define BSSA_LOGGING_CHANGE_LEVEL(SsaBiosServices, NewPrintLevel) (SsaBiosServices)->SsaCommonConfig->CurrentPrintLevel = (NewPrintLevel)

#ifndef BSSA_LOGGING_SILENT_MODE
/**
  Function used to log messages. Will be defined on all three logging levels(BSSA_LOGGING_INTERNAL_DEBUG_LEVEL,
  BSSA_LOGGING_INTERNAL_NORMAL_LEVEL or BSSA_LOGGING_NORMAL_LEVEL).

  @param[in, out] - SSA_BIOS_SERVICES_PPI *SsaBiosServices: Interface pointer that implements the particular SSA_BIOS_SERVICES_PPI instance.
  @param[in]      - PRINT_LEVEL newPrintLevel: Enum used to determine if the message should be output to debug print device.
  @param[in]      - CHAR* formatString: format string for the message to be output to debug print device.

  @retval Nothing.
**/
#if BSSA_LOGGING_LEVEL >= BSSA_LOGGING_INTERNAL_DEBUG_LEVEL
#define INTERNAL_DEBUG_LOG(SsaBiosServices, PrintLevel, formatString, ...) (SsaBiosServices)->SsaCommonConfig->DebugPrint((SsaBiosServices), (PrintLevel), (formatString), ## __VA_ARGS__)
#else
#define INTERNAL_DEBUG_LOG(SsaBiosServices, PrintLevel, formatString, ...)
#endif
/**
  Function used to log messages. Will be defined on BSSA_LOGGING_INTERNAL_NORMAL_LEVEL and BSSA_LOGGING_NORMAL_LEVEL

  @param[in, out] - SSA_BIOS_SERVICES_PPI *SsaBiosServices: Interface pointer that implements the particular SSA_BIOS_SERVICES_PPI instance.
  @param[in]      - PRINT_LEVEL newPrintLevel: Enum used to determine if the message should be output to debug print device.
  @param[in]      - CHAR* formatString: format string for the message to be output to debug print device.

  @retval Nothing.
**/
#if BSSA_LOGGING_LEVEL >= BSSA_LOGGING_INTERNAL_NORMAL_LEVEL
#define INTERNAL_NORMAL_LOG(SsaBiosServices, PrintLevel, formatString, ...) (SsaBiosServices)->SsaCommonConfig->DebugPrint((SsaBiosServices), (PrintLevel), (formatString), ## __VA_ARGS__)
#else
#define INTERNAL_NORMAL_LOG(SsaBiosServices, PrintLevel, formatString, ...)
#endif
/**
  Function used to log messages. Will only be defined on BSSA_LOGGING_NORMAL_LEVEL

  @param[in, out] - SSA_BIOS_SERVICES_PPI *SsaBiosServices: Interface pointer that implements the particular SSA_BIOS_SERVICES_PPI instance.
  @param[in]      - PRINT_LEVEL newPrintLevel: Enum used to determine if the message should be output to debug print device.
  @param[in]      - CHAR* formatString: format string for the message to be output to debug print device.

  @retval Nothing.
**/
#if BSSA_LOGGING_LEVEL >= BSSA_LOGGING_NORMAL_LEVEL
#define NORMAL_LOG(SsaBiosServices, PrintLevel, formatString, ...) (SsaBiosServices)->SsaCommonConfig->DebugPrint((SsaBiosServices), (PrintLevel), (formatString), ## __VA_ARGS__)
#else
#define NORMAL_LOG(SsaBiosServices, PrintLevel, formatString, ...)
#endif
#else
#define INTERNAL_DEBUG_LOG(SsaBiosServices, PrintLevel, formatString, ...)
#define INTERNAL_NORMAL_LOG(SsaBiosServices, PrintLevel, formatString, ...)
#define NORMAL_LOG(SsaBiosServices, PrintLevel, formatString, ...)
#endif

#endif
