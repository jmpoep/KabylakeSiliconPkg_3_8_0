/** @file
  Functions to handle margining various DRAM parameters.

 @copyright
  INTEL CONFIDENTIAL
  Copyright 2011 - 2015 Intel Corporation.

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

#include "DcttApi.h"
#include "DcttRegList.h"
#include "DcttApiFunctions.h"
#include "DcttMarginFunctions.h"
#include "DcttMcFunctions.h"
#include "DcttDebug.h"


///
/// Local Globals
///
GLOBAL_REMOVE_IF_UNREFERENCED const char *MarginStrings[] = {
  "No Margin",
  "Pause Refresh",
  "tRCD",
  "tRP",
  "tRAS",
  "tRDPRE",
  "tWRPRE",
  "tCL",
  "tCWL",
  "VDD",
  "Invalid Margin Parameter"
};

UINT16
GetCl (
  DCTT_API            *DcttMain,
  UINT8               Channel
  )
{
  UINT16 RetVal;

  RetVal = DCTT_BAD_MARGIN_VALUE;

  RetVal = McFunctions_GetTcBankRankDField (
             DcttMain,
             Channel,
             DCTT_CH_TC_ODT_tCL_START,
             DCTT_CH_TC_ODT_tCL_LEN
             );

  return RetVal;
}

UINT16
GetCwl (
  DCTT_API            *DcttMain,
  UINT8               Channel
  )
{
  UINT16 RetVal;

  RetVal = DCTT_BAD_MARGIN_VALUE;

  RetVal = McFunctions_GetTcBankRankDField (
             DcttMain,
             Channel,
             DCTT_CH_TC_ODT_tCWL_START,
             DCTT_CH_TC_ODT_tCWL_LEN
             );

  return RetVal;
}

UINT16
GetRas (
  DCTT_API  *DcttMain,
  UINT8     Channel
  )
{
  UINT16 RetVal;

  RetVal = DCTT_BAD_MARGIN_VALUE;

  RetVal = McFunctions_GetTcBankField (
             DcttMain,
             Channel,
             DCTT_CH_TC_PRE_tRAS_START,
             DCTT_CH_TC_PRE_tRAS_LEN
             );

  return RetVal;
}

UINT16
GetRcd (
  DCTT_API              *DcttMain,
  UINT8                 Channel
  )
{
  UINT16 RetVal;

  RetVal = DCTT_BAD_MARGIN_VALUE;

  RetVal = McFunctions_GetTcBankField (
             DcttMain,
             Channel,
             DCTT_CH_TC_PRE_tRP_tRCD_START,
             DCTT_CH_TC_PRE_tRP_tRCD_LEN
             );

  return RetVal;
}

UINT16
GetRdPre (
  DCTT_API              *DcttMain,
  UINT8                 Channel
  )
{
  UINT16 RetVal;

  RetVal = DCTT_BAD_MARGIN_VALUE;

  RetVal = McFunctions_GetTcBankField (
             DcttMain,
             Channel,
             DCTT_CH_TC_PRE_tRDPRE_START,
             DCTT_CH_TC_PRE_tRDPRE_LEN
             );

  return RetVal;
}

UINT16
GetRp (
  DCTT_API              *DcttMain,
  UINT8                 Channel
  )
{
  UINT16 RetVal;

  RetVal = DCTT_BAD_MARGIN_VALUE;

  RetVal = McFunctions_GetTcBankField (
             DcttMain,
             Channel,
             DCTT_CH_TC_PRE_tRP_tRCD_START,
             DCTT_CH_TC_PRE_tRP_tRCD_LEN
             );

  return RetVal;
}

UINT16
GetVdd (
  DCTT_API              *DcttMain,
  DCTT_CONFIG_PARAMS *TestParams
  )
{
  UINT16 RetVal;

  RetVal = DCTT_BAD_MARGIN_VALUE;

  return RetVal;
}

UINT16
GetWrPre (
  DCTT_API              *DcttMain,
  UINT8                 Channel
  )
{
  UINT16 RetVal;

  RetVal = DCTT_BAD_MARGIN_VALUE;

  RetVal = McFunctions_GetTcBankField (
             DcttMain,
             Channel,
             DCTT_CH_TC_PRE_tWRPRE_START,
             DCTT_CH_TC_PRE_tWRPRE_LEN
             );

  return RetVal;
}

UINT8
SetCl (
  DCTT_API              *DcttMain,
  UINT8                 Channel,
  UINT8                 UpdateValue
  )
{
  UINT32  Status;
  UINT8   RetVal;

  RetVal = UpdateValue;
  if (RetVal < DCTT_CH_TC_ODT_tCL_MIN) {
    RetVal = DCTT_CH_TC_ODT_tCL_MIN;
  } else if (RetVal > DCTT_CH_TC_ODT_tCL_MAX) {
    RetVal = DCTT_CH_TC_ODT_tCL_MAX;
  }

  McFunctions_UpdateTcBankRankD (
    DcttMain,
    Channel,
    RetVal,
    DCTT_CH_TC_ODT_tCL_START,
    DCTT_CH_TC_ODT_tCL_LEN
    );

  Status = DcttSetClFunc (DcttMain, 0, Channel, RetVal);

  if (Status != DCTT_SUCCESS) {
    RetVal = 0;
  }

  return RetVal;
}

UINT8
SetCwl (
  DCTT_API              *DcttMain,
  UINT8                 Channel,
  UINT8                 UpdateValue
  )
{
  UINT32  Status;
  UINT8   RetVal;

  RetVal = UpdateValue;
  if (RetVal < DCTT_CH_TC_ODT_tCWL_MIN) {
    RetVal = DCTT_CH_TC_ODT_tCWL_MIN;
  } else if (RetVal > DCTT_CH_TC_ODT_tCWL_MAX) {
    RetVal = DCTT_CH_TC_ODT_tCWL_MAX;
  }

  McFunctions_UpdateTcBankRankD (
    DcttMain,
    Channel,
    RetVal,
    DCTT_CH_TC_ODT_tCWL_START,
    DCTT_CH_TC_ODT_tCWL_LEN
    );

  Status = DcttSetCwlFunc (DcttMain, 0, Channel, RetVal);

  if (Status != DCTT_SUCCESS) {
    RetVal = 0;
  }

  return RetVal;
}

UINT8
SetRas (
  DCTT_API              *DcttMain,
  UINT8                 Channel,
  UINT8                 UpdateValue
  )
{
  UINT8 RetVal;

  //
  // Constrain to the supported range by MC
  //
  // TODO: change to MRC version of MAX/MIN
  RetVal = UpdateValue;
  if (RetVal < DCTT_CH_TC_PRE_tRAS_MIN) {
    RetVal = DCTT_CH_TC_PRE_tRAS_MIN;
  } else if (RetVal > DCTT_CH_TC_PRE_tRAS_MAX) {
    RetVal = DCTT_CH_TC_PRE_tRAS_MAX;
  }

  McFunctions_UpdateTcBank (
    DcttMain,
    Channel,
    RetVal,
    DCTT_CH_TC_PRE_tRAS_START,
    DCTT_CH_TC_PRE_tRAS_LEN
    );

  return RetVal;
}

UINT8
SetRcd (
  DCTT_API              *DcttMain,
  UINT8                 Channel,
  UINT8                 UpdateValue
  )
{
  UINT8 RetVal;

  //
  // Constrain to the supported range by MC
  //
  // TODO: change to MRC version of MAX/MIN
  RetVal = UpdateValue;
  if (RetVal < DCTT_CH_TC_PRE_tRP_tRCD_MIN) {
    RetVal = DCTT_CH_TC_PRE_tRP_tRCD_MIN;
  } else if (RetVal > DCTT_CH_TC_PRE_tRP_tRCD_MAX) {
    RetVal = DCTT_CH_TC_PRE_tRP_tRCD_MAX;
  }

  McFunctions_UpdateTcBank (
    DcttMain,
    Channel,
    RetVal,
    DCTT_CH_TC_PRE_tRP_tRCD_START,
    DCTT_CH_TC_PRE_tRP_tRCD_LEN
    );

  return RetVal;
}

UINT8
SetRdPre (
  DCTT_API              *DcttMain,
  UINT8                 Channel,
  UINT8                 UpdateValue
  )
{
  UINT8 RetVal;

  //
  // Constrain to the supported range by MC
  //
  // TODO: change to MRC version of MAX/MIN
  RetVal = UpdateValue;
  if (RetVal < DCTT_CH_TC_PRE_tRDPRE_MIN) {
    RetVal = DCTT_CH_TC_PRE_tRDPRE_MIN;
  } else if (RetVal > DCTT_CH_TC_PRE_tRDPRE_MAX) {
    RetVal = DCTT_CH_TC_PRE_tRDPRE_MAX;
  }

  McFunctions_UpdateTcBank (
    DcttMain,
    Channel,
    RetVal,
    DCTT_CH_TC_PRE_tRDPRE_START,
    DCTT_CH_TC_PRE_tRDPRE_LEN
    );

  return RetVal;
}

UINT8
SetRp (
  DCTT_API              *DcttMain,
  UINT8                 Channel,
  UINT8                 UpdateValue
  )
{
  UINT8 RetVal;

  //
  // Constrain to the supported range by MC
  //
  // TODO: change to MRC version of MAX/MIN
  RetVal = UpdateValue;
  if (RetVal < DCTT_CH_TC_PRE_tRP_tRCD_MIN) {
    RetVal = DCTT_CH_TC_PRE_tRP_tRCD_MIN;
  } else if (RetVal > DCTT_CH_TC_PRE_tRP_tRCD_MAX) {
    RetVal = DCTT_CH_TC_PRE_tRP_tRCD_MAX;
  }

  McFunctions_UpdateTcBank (
    DcttMain,
    Channel,
    RetVal,
    DCTT_CH_TC_PRE_tRP_tRCD_START,
    DCTT_CH_TC_PRE_tRP_tRCD_LEN
    );

  return RetVal;
}

UINT8
SetVdd (
  DCTT_API              *DcttMain,
  UINT8                 UpdateValue
  )
{
  UINT8 RetVal;

  RetVal = UpdateValue;

  return RetVal;
}

UINT8
SetWrPre (
  DCTT_API              *DcttMain,
  UINT8                 Channel,
  UINT8                 UpdateValue
  )
{
  UINT8 RetVal;

  //
  // Constrain to the supported range by MC
  //
  // TODO: change to MRC version of MAX/MIN
  RetVal = UpdateValue;
  if (RetVal < DCTT_CH_TC_PRE_tWRPRE_MIN) {
    RetVal = DCTT_CH_TC_PRE_tWRPRE_MIN;
  } else if (RetVal > DCTT_CH_TC_PRE_tWRPRE_MAX) {
    RetVal = DCTT_CH_TC_PRE_tWRPRE_MAX;
  }

  McFunctions_UpdateTcBank (
    DcttMain,
    RetVal,
    Channel,
    DCTT_CH_TC_PRE_tWRPRE_START,
    DCTT_CH_TC_PRE_tWRPRE_LEN
    );

  return RetVal;
}

INT32
MarginFunctions_GetMarginParamValue (
  DCTT_API              *DcttMain,
  UINT8                 Channel,
  DCTT_MARGIN_OPERATION MarginParameter,
  UINT16                *SavePtr
  )
{
  INT32 Status;

  Status = DCTT_SUCCESS;

  switch (MarginParameter) {
    case NoMarginOperation:
      break;

    case ClMargin:
      *SavePtr = GetCl (DcttMain, Channel);
      break;

    case CwlMargin:
      *SavePtr = GetCwl (DcttMain, Channel);
      break;

    case PauseRefreshMargin:
      //
      // Pause Refresh doesn't adjust any parameter.  Returning parameter entry.
      //
      *SavePtr = (UINT16) DcttMain->DcttConfigData.pauseRefreshDelay;
      break;

    case RcdMargin:
      *SavePtr = GetRcd (DcttMain, Channel);
      break;

    case RpMargin:
      *SavePtr = GetRp (DcttMain, Channel);
      break;

    case RasMargin:
      *SavePtr = GetRas (DcttMain, Channel);
      break;

    case RdPreMargin:
      *SavePtr = GetRdPre (DcttMain, Channel);
      break;

    case WrPreMargin:
      *SavePtr = GetWrPre (DcttMain, Channel);
      break;

    case VddMargin:
      DcttOutputPrint (DcttMain, "%s margining is currently unsupported\n", MarginStrings[MarginParameter]);
      return DCTT_FAIL;
      break;

    default:
      DcttError_Assert (DcttMain, 1 == 0, "%s %d\n", MarginStrings[InvalidMargin], MarginParameter);
      Status = DCTT_FAIL;
      MarginParameter = InvalidMargin;
  }

  DcttOutputPrint (
    DcttMain,
    ((MarginParameter > NoMarginOperation) && (MarginParameter < MaxMarginOp)) ? "%s initial value: %d\n" : "",
    MarginStrings[MarginParameter],
    *SavePtr
    );

  return Status;
}

INT32
MarginFunctions_ChangeMargin (
  DCTT_API              *DcttMain,
  UINT8                 Channel,
  DCTT_MARGIN_OPERATION ParameterToChange,
  INT32                 ParameterValue
  )
{
  DCTT_CONFIG_PARAMS *DcttConfig;
  INT32 UpdatedValue;
  INT32 Status;

  DcttConfig    = &DcttMain->DcttConfigData;
  Status        = DCTT_SUCCESS;
  UpdatedValue  = -1;  // Start with a negative number.

  switch (ParameterToChange) {
    case NoMarginOperation:
      break;

    case ClMargin:
      UpdatedValue = SetCl (DcttMain, Channel, (UINT8) ParameterValue);
      DcttConfig->TimingParams.Cl = (UINT8) UpdatedValue;
      break;

    case CwlMargin:
      UpdatedValue = SetCwl (DcttMain, Channel, (UINT8) ParameterValue);
      DcttConfig->TimingParams.Cwl = (UINT8) UpdatedValue;
      break;

    case PauseRefreshMargin:
      //
      // Pause Refresh margining is done through CPGC functions.  Thus, this case does not update here
      //
      UpdatedValue = ParameterValue;
      DcttConfig->pauseRefreshDelay = (UINT32) ParameterValue;
      break;

    case RcdMargin:
      UpdatedValue = SetRcd (DcttMain, Channel, (UINT8) ParameterValue);
      DcttConfig->TimingParams.RcdValue = (UINT8) UpdatedValue;
      break;

    case RpMargin:
      UpdatedValue = SetRp (DcttMain, Channel, (UINT8) ParameterValue);
      DcttConfig->TimingParams.RpValue = (UINT8) UpdatedValue;
      break;

    case RasMargin:
      UpdatedValue = SetRas (DcttMain, Channel, (UINT8) ParameterValue);
      DcttConfig->TimingParams.RasValue = (UINT8) UpdatedValue;
      break;

    case RdPreMargin:
      UpdatedValue = SetRdPre (DcttMain, Channel, (UINT8) ParameterValue);
      DcttConfig->TimingParams.RdPre = (UINT8) UpdatedValue;
      break;

    case WrPreMargin:
      UpdatedValue = SetWrPre (DcttMain, Channel, (UINT8) ParameterValue);
      DcttConfig->TimingParams.WrPre = (UINT8) UpdatedValue;
      break;

    case VddMargin:
      DcttOutputPrint (DcttMain, "%s margining is currently unsupported\n", MarginStrings[ParameterToChange]);
      return DCTT_FAIL;
      break;

    default:
      DcttError_Assert (DcttMain, 1 == 0, "%s %d\n", MarginStrings[InvalidMargin], ParameterToChange);
      Status = DCTT_FAIL;
      ParameterToChange = InvalidMargin;
  }

  DcttOutputPrint (
    DcttMain,
    ((ParameterToChange > NoMarginOperation) && (ParameterToChange < MaxMarginOp)) ? "%s changed to: %d\n" : "",
    MarginStrings[ParameterToChange],
    UpdatedValue
    );

  if (UpdatedValue == 0) {
    Status = DCTT_FAIL;
  }

  return Status;
}
