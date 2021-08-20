/** @file
  Header file associated with the memory controller hardware abstraction layer.

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

#ifndef _MrcHalRegisterAccess_h_
#define _MrcHalRegisterAccess_h_
#pragma pack (push, 1)

#include "McAddress.h"
#include "MrcInterface.h"
#include "MrcDebugPrint.h"

///
/// Mode Parameters for MrcGetSet...()
///
#define GSM_READ_CSR      MRC_BIT0  ///< Set to force the read from hardware. Clear to read from cache.
#define GSM_READ_ONLY     MRC_BIT1  ///< Set to skip the write flow.
#define GSM_WRITE_OFFSET  MRC_BIT2  ///< Set to use the "value" input as an offset. Set to use the "value" input as an absolute.
#define GSM_FORCE_WRITE   MRC_BIT3  ///< Set to force a write even if the data to be written matches the cached value.
#define GSM_UPDATE_CACHE  MRC_BIT4  ///< Set to update cached value with the read or write value
#define GSM_CACHE_ONLY    MRC_BIT5  ///< Set to update cached value only, clear updates both cache and hardware.
#define GSM_COMBINE_EDGES MRC_BIT6  ///< Set to use value1 as left/low side edge and value2 as right/high side edge
                                    /// Clear to use value1 as center and don't use value2

#ifdef MRC_DEBUG_PRINT
#define MRC_PRINT_DDR_IO_GROUP(\
  MrcData,\
  Socket,\
  Channel,\
  Rank,\
  Strobe,\
  Bit,\
  FreqIndex,\
  Group\
  )\
MrcPrintDdrIoGroup (\
  MrcData,\
  Socket,\
  Channel,\
  Rank,\
  Strobe,\
  Bit,\
  FreqIndex,\
  Group\
  )
#else
#define MRC_PRINT_DDR_IO_GROUP(\
  MrcData,\
  Socket,\
  Channel,\
  Rank,\
  Strobe,\
  Bit,\
  FreqIndex,\
  Group\
  )
#endif

typedef enum {
  MrcHalGlobalStatusNotDone,
  MrcHalGlobalStatusDone,
  MrcHalGlobalStatusDoneMax
} MRC_HAL_GLOBAL_STATUS_DONE;

typedef enum {
  MrcHalGlobalStatusNoError,
  MrcHalGlobalStatusError,
  MrcHalGlobalStatusErrorMax
} MRC_HAL_GLOBAL_STATUS_ERROR;

typedef enum {
  MrcHalTestStatusRunning,
  MrcHalTestStatusStoppedNoError,
  MrcHalTestStatusStoppedWithError,
  MrcHalTestStatusStatusMax
} MRC_HAL_TEST_STATUS;

typedef struct {
  MRC_HAL_ENUM_SEQUENCE_WRAP_CONTROL         StopBaseSequenceOnWrapTrigger;
  MRC_HAL_ENUM_ADDRESS_UPDATE_RATE_CONTROL   AddressUpdateRateMode;
  MRC_HAL_ENUM_DUMMY_READ_CONTROL            EnableDummyReads;
  MRC_HAL_ENUM_OPPORTUNISTIC_REFRESH_CONTROL ReutAllowOppRefresh;
  MRC_HAL_ENUM_GLOBAL_CONTROL                GlobalControl;
  MRC_HAL_ENUM_INITIALIZATION_MODE           InitializationMode;
  MRC_HAL_ENUM_SUBSEQUENCE_POINTER_VALUE     SubsequenceStartPointer;
  MRC_HAL_ENUM_SUBSEQUENCE_POINTER_VALUE     SubsequenceEndPointer;
  UINT32                                     StartTestDelay;
  MRC_HAL_ENUM_CACHELINE_COUNTER_CONTROL     SubSequenceCachelineCounterMode;
} MRC_HAL_SEQUENCE_CONFIG_STRUCT;

typedef struct {
  UINT8  Rank;
  UINT8  Bank;
  UINT32 Row;
  UINT16 Column;
} MRC_HAL_SEQ_BASE_ADDRESS_STRUCT;

typedef struct {
  UINT8  NumberofCachelines;
  UINT8  NumberofCachelinesScale;
  UINT16 SubsequenceWait;
  UINT8  SubsequenceType;
  UINT8  SaveCurrentBaseAddressToStart;
  UINT8  ResetCurrentBaseAddressToStart;
  UINT8  DataandEccAddressInversion;
  UINT8  InvertDataandEcc;
  UINT8  StopBaseSubsequenceOnWrapTrigger;
} MRC_HAL_SUBSEQUENCE_CONTROL_STRUCT;

typedef struct {
  UINT8  OffsetAddressUpdateRate;
  UINT8  BaseSubsequenceRepeatRate;
  UINT8  ColumnOffsetWrapTriggerEnable;
  UINT8  RowOffsetWrapTriggerEnable;
  UINT8  BaseSubsequenceType;
  UINT8  CadbDeselectEnable;
  UINT8  CadbSelectEnable;
  UINT8  CadbSeedsSaveEnable;
  UINT8  ColumnIncrementOrder;
  UINT8  CadbSeedsReloadEnable;
  UINT8  ColumnIncrementEnable;
  UINT8  RowIncrementOrder;
  UINT8  RowIncrementEnable;
  UINT8  BaseInvertDataandEcc;
} MRC_HAL_SUBSEQUENCE_OFFSET_STRUCT;

typedef struct {
  UINT32                              Increment;
  UINT32                              Rate;
  MRC_HAL_ENUM_INCRMENT_SCALE_CONTROL Scale;
} MRC_HAL_REUT_BASE_ADDR_INC_CTL;

typedef struct {
  UINT32                              Order;
  MRC_HAL_ENUM_ADDRESS_INVERT_CONTROL InvertEnable;
  MRC_HAL_ENUM_ADDRESS_WRAP_TRIGGER   TriggerEnable;
  MRC_HAL_ENUM_ADDRESS_WRAP_CARRY     CarryEnable;
} MRC_HAL_REUT_BASE_ADDR_OCI_CTL;

/**
  This function sets the specified register bit field.

  @param[in] HashIn        - The bit field hash value.
  @param[in] BitFieldValue - The bit field value.
  @param[in] RegisterValue - The register value to write.

  @retval The value written to the register.
**/
extern
UINT32
MrcHalSetBitField32 (
  IN const UINT32 HashIn,
  IN const UINT32 BitfieldValue,
  IN const UINT32 RegisterValue
);

/**
  This function sets the specified register bit field.

  @param[in] HashIn        - The bit field hash value.
  @param[in] BitFieldValue - The bit field value.
  @param[in] RegisterValue - The register value to write.

  @retval The value written to the register.
**/
extern
UINT32
MrcHalSetBitFieldS32 (
  IN const UINT32 HashIn,
  IN const INT32  BitfieldValue,
  IN const UINT32 RegisterValue
);

/**
  This function gets the specified register bit field.

  @param[in] Group         - DDRIO group to access.
  @param[in] HashIn        - The bit field hash value.
  @param[in] RegisterValue - The register value to write.

  @retval The value written to the register.
**/
extern
INT32
MrcHalGsmGetBitField32 (
  IN const GSM_GT Group,
  IN const UINT32 HashIn,
  IN const UINT32 RegisterValue
);

/**
  This function gets the specified register bit field.

  @param[in] HashIn        - The bit field hash value.
  @param[in] RegisterValue - The register value to write.

  @retval The value written to the register.
**/
UINT32
MrcHalGetBitField32 (
  IN const UINT32 HashIn,
  IN const UINT32 RegisterValue
  );

/**
  This function gets the specified register bit field.

  @param[in] HashIn        - The bit field hash value.
  @param[in] RegisterValue - The register value to write.

  @retval The value written to the register.
**/
extern
INT32
MrcHalGetBitFieldS32 (
  IN const UINT32 HashIn,
  IN const UINT32 RegisterValue
);

/**
  This function sets the specified register bit field.

  @param[in] MrcData       - Include all MRC global data.
  @param[in] HashIn        - The bit field hash value.
  @param[in] BitFieldValue - The bit field value.
  @param[in] RegisterValue - The register value to write.

  @retval The value written to the register.
**/
extern
UINT64
MrcHalSetBitField64 (
  IN MrcParameters *const MrcData,
  IN const UINT32  HashIn,
  IN const UINT64  BitfieldValue,
  IN const UINT64  RegisterValue
);

/**
  This function sets the specified register bit field.

  @param[in] MrcData       - Include all MRC global data.
  @param[in] HashIn        - The bit field hash value.
  @param[in] BitFieldValue - The bit field value.
  @param[in] RegisterValue - The register value to write.

  @retval The value written to the register.
**/
extern
UINT64
MrcHalSetBitFieldS64 (
  IN MrcParameters *const MrcData,
  IN const UINT32  HashIn,
  IN const INT64   BitfieldValue,
  IN const UINT64  RegisterValue
);

/**
  This function gets the specified register bit field.

  @param[in] MrcData       - Include all MRC global data.
  @param[in] HashIn        - The bit field hash value.
  @param[in] RegisterValue - The register value to write.

  @retval The value written to the register.
**/
extern
UINT64
MrcHalGetBitField64 (
  IN MrcParameters *const MrcData,
  IN const UINT32  HashIn,
  IN const UINT64  RegisterValue
);

/**
  This function gets the specified register bit field.

  @param[in] MrcData       - Include all MRC global data.
  @param[in] HashIn        - The bit field hash value.
  @param[in] RegisterValue - The register value to write.

  @retval The value written to the register.
**/
extern
INT64
MrcHalGetBitFieldS64 (
  IN MrcParameters *const MrcData,
  IN const UINT32  HashIn,
  IN const UINT64  RegisterValue
);

/**
  This function sets the scheduler cbit disable ZQ control value.
  Note that no error checking is done so ensure to pass a correct value.

  @param[in] MrcData - Include all MRC global data.
  @param[in] Channel - Zero based channel number in the memory controller.
  @param[in] Value   - The value to set.
**/
extern
void
MrcHalRmwRegSchedCbitDisableZq (
  IN MrcParameters *const MrcData,
  IN const UINT32  Channel,
  IN const UINT32  Value
  );

/**
  This function gets the scheduler cbit disable ZQ control value.
  Note that no error checking is done so ensure to pass a correct value.

  @param[in] MrcData - Include all MRC global data.
  @param[in] Channel - Zero based channel number in the memory controller.

  @retval The value read from the register.
**/
extern
UINT32
MrcHalGetRegSchedCbitDisableZq (
  IN MrcParameters *const MrcData,
  IN const UINT32  Channel
  );

/**
  This function sets the rcomp disable control.
  Note that no error checking is done so ensure to pass a correct value.

  @param[in] MrcData - Include all MRC global data.
  @param[in] Value   - The value to set.

  @retval The value written to the register.
**/
extern
UINT32
MrcHalRmwRegDisableRcomp (
  IN MrcParameters *const MrcData,
  IN const UINT32  Value
  );

/**
  This function gets the rcomp disable control.
  Note that no error checking is done so ensure to pass a correct value.

  @param[in] MrcData - Include all MRC global data.

  @retval The value read from the register.
**/
extern
UINT32
MrcHalGetRegDisableRcomp (
  IN MrcParameters *const MrcData
  );

/**
  This function gets the address as data control register.
  Note that no error checking is done so ensure to pass a correct value.

  @param[in] MrcData - Include all MRC global data.
  @param[in] Channel - Zero based channel number in the memory controller.

  @retval The value read from the register.
**/
extern
UINT32
MrcHalGetReutChPatWdbAddressAsData (
  IN MrcParameters *const MrcData,
  IN const UINT32  Channel
  );

/**
  This function configures the data in 0 register.
  Note that no error checking is done so ensure to pass a correct value.

  @param[in] MrcData       - Include all MRC global data.
  @param[in] Channel       - Zero based channel number in the memory controller.
  @param[in] RegisterValue - The register value to write.

  @retval The value written to the register.
**/
extern
UINT32
MrcHalSetRegQclkLdatDatain0 (
  IN MrcParameters *const MrcData,
  IN const UINT32  Channel,
  IN const UINT32  RegisterValue
  );

/**
  This function gets the data in 0 register.
  Note that no error checking is done so ensure to pass a correct value.

  @param[in] MrcData       - Include all MRC global data.
  @param[in] Channel       - Zero based channel number in the memory controller.

  @retval The value read from the register.
**/
extern
UINT32
MrcHalGetRegQclkLdatDatain0 (
  IN MrcParameters *const MrcData,
  IN const UINT32  Channel
  );

/**
  This function configures the data in 1 register.
  Note that no error checking is done so ensure to pass a correct value.

  @param[in] MrcData       - Include all MRC global data.
  @param[in] Channel       - Zero based channel number in the memory controller.
  @param[in] RegisterValue - The register value to write.

  @retval The value written to the register.
**/
extern
UINT32
MrcHalSetRegQclkLdatDatain1 (
  IN MrcParameters *const MrcData,
  IN const UINT32  Channel,
  IN const UINT32  RegisterValue
  );

/**
  This function gets the data in 1 register.
  Note that no error checking is done so ensure to pass a correct value.

  @param[in] MrcData       - Include all MRC global data.
  @param[in] Channel       - Zero based channel number in the memory controller.

  @retval The value read from the register.
**/
extern
UINT32
MrcHalGetRegQclkLdatDatain1 (
  IN MrcParameters *const MrcData,
  IN const UINT32  Channel
  );

/**
  This function configures the ldat sdat register.
  Note that no error checking is done so ensure to pass a correct value.

  @param[in] MrcData       - Include all MRC global data.
  @param[in] Channel       - Zero based channel number in the memory controller.
  @param[in] RegisterValue - The register value to write.

  @retval The value written to the register.
**/
extern
UINT32
MrcHalSetRegQclkLdatSdat (
  IN MrcParameters *const MrcData,
  IN const UINT32  Channel,
  IN const UINT32  RegisterValue
  );

/**
  This function configures the ldat pdat register.
  Note that no error checking is done so ensure to pass a correct value.

  @param[in] MrcData       - Include all MRC global data.
  @param[in] Channel       - Zero based channel number in the memory controller.
  @param[in] RegisterValue - The register value to write.

  @retval The value written to the register.
**/
extern
UINT32
MrcHalSetRegQclkLdatPdat (
  IN MrcParameters *const MrcData,
  IN const UINT32  Channel,
  IN const UINT32  RegisterValue
  );

/**
  This function configures the WDB pattern control register.
  Note that no error checking is done so ensure to pass a correct value.

  @param[in] MrcData       - Include all MRC global data.
  @param[in] Channel       - Zero based channel number in the memory controller.
  @param[in] RegisterValue - The register value to write.

  @retval The value written to the register.
**/
extern
UINT32
MrcHalSetRegReutChPatWdbClCtrl (
  IN MrcParameters *const MrcData,
  IN const UINT32  Channel,
  IN const UINT32  RegisterValue
  );

/**
  This function configures the WDB pattern mux config register.
  Note that no error checking is done so ensure to pass a correct value.

  @param[in] MrcData       - Include all MRC global data.
  @param[in] Channel       - Zero based channel number in the memory controller.
  @param[in] RegisterValue - The register value to write.

  @retval The value written to the register.
**/
extern
UINT32
MrcHalSetRegReutChPatWdbClMuxCfg (
  IN MrcParameters *const MrcData,
  IN const UINT32  Channel,
  IN const UINT32  RegisterValue
  );

/**
  This function gets the WDB pattern mux config register.
  Note that no error checking is done so ensure to pass a correct value.

  @param[in] MrcData       - Include all MRC global data.
  @param[in] Channel       - Zero based channel number in the memory controller.

  @retval The value written to the register.
**/
extern
UINT32
MrcHalGetRegReutChPatWdbClMuxCfg (
  IN MrcParameters *const MrcData,
  IN const UINT32  Channel
  );

/**
  This function gets the WDB write pattern buffer register.
  Note that no error checking is done so ensure to pass a correct value.

  @param[in] MrcData - Include all MRC global data.
  @param[in] Channel - Zero based channel number in the memory controller.
  @param[in] Index   - Zero based pattern buffer index.

  @retval The value read from the register.
**/
extern
UINT32
MrcHalGetRegReutChPatWdbClMuxPbWr (
  IN MrcParameters *const MrcData,
  IN const UINT32  Channel,
  IN const UINT32  Index
  );

/**
  This function gets the WDB read pattern buffer register.
  Note that no error checking is done so ensure to pass a correct value.

  @param[in] MrcData - Include all MRC global data.
  @param[in] Channel - Zero based channel number in the memory controller.
  @param[in] Index   - Zero based pattern buffer index.

  @retval The value read from the register.
**/
extern
UINT32
MrcHalGetRegReutChPatWdbClMuxPbRd (
  IN MrcParameters *const MrcData,
  IN const UINT32  Channel,
  IN const UINT32  Index
  );

/**
  This function configures the WDB pattern mux LMN register.
  Note that no error checking is done so ensure to pass a correct value.

  @param[in] MrcData       - Include all MRC global data.
  @param[in] Channel       - Zero based channel number in the memory controller.
  @param[in] RegisterValue - The register value to write.

  @retval The value written to the register.
**/
extern
UINT32
MrcHalSetRegReutChPatWdbClMuxLmn (
  IN MrcParameters *const MrcData,
  IN const UINT32  Channel,
  IN const UINT32  RegisterValue
  );

/**
  This function configures the WDB invert dc register.
  Note that no error checking is done so ensure to pass a correct value.

  @param[in] MrcData       - Include all MRC global data.
  @param[in] Channel       - Zero based channel number in the memory controller.
  @param[in] RegisterValue - The register value to write.

  @retval The value written to the register.
**/
extern
UINT32
MrcHalSetRegReutChPatWdbInv (
  IN MrcParameters *const MrcData,
  IN const UINT32  Channel,
  IN const UINT32  RegisterValue
  );

/**
  This function gets the WDB invert dc register.
  Note that no error checking is done so ensure to pass a correct value.

  @param[in] MrcData       - Include all MRC global data.
  @param[in] Channel       - Zero based channel number in the memory controller.

  @retval The value written to the register.
**/
extern
UINT32
MrcHalGetRegReutChPatWdbInv (
  IN MrcParameters *const MrcData,
  IN const UINT32  Channel
  );

/**
  This function configures the WDB data invert register.
  Note that no error checking is done so ensure to pass a correct value.

  @param[in] MrcData       - Include all MRC global data.
  @param[in] Channel       - Zero based channel number in the memory controller.
  @param[in] RegisterValue - The register value to write.

  @retval The value written to the register.
**/
extern
UINT64
MrcHalSetRegReutChPatWdbDataInv (
  IN MrcParameters *const MrcData,
  IN const UINT32  Channel,
  IN const UINT64  RegisterValue
  );

/**
  This function configures the CADB control.
  Note that no error checking is done so ensure to pass a correct value.

  @param[in] MrcData       - Include all MRC global data.
  @param[in] Channel       - Zero based channel number in the memory controller.
  @param[in] RegisterValue - The register value to write.

  @retval The value written to the register.
**/
extern
UINT32
MrcHalSetRegReutChPatCadbCtrl (
  IN MrcParameters *const MrcData,
  IN const UINT32  Channel,
  IN const UINT32  RegisterValue
  );

/**
  This function gets the CADB control.
  Note that no error checking is done so ensure to pass a correct value.

  @param[in] MrcData       - Include all MRC global data.
  @param[in] Channel       - Zero based channel number in the memory controller.

  @retval The value written to the register.
**/
extern
UINT32
MrcHalGetRegReutChPatCadbCtrl (
  IN MrcParameters *const MrcData,
  IN const UINT32  Channel
  );

/**
  This function configures the CADB pattern write pointer.
  Note that no error checking is done so ensure to pass a correct value.

  @param[in] MrcData       - Include all MRC global data.
  @param[in] Channel       - Zero based channel number in the memory controller.
  @param[in] RegisterValue - The register value to write.

  @retval The value written to the register.
**/
extern
UINT32
MrcHalSetReutChPatCadbWritePointer (
  IN MrcParameters *const MrcData,
  IN const UINT32  Channel,
  IN const UINT32  RegisterValue
  );

/**
  This function gets the CADB pattern write pointer.
  Note that no error checking is done so ensure to pass a correct value.

  @param[in] MrcData       - Include all MRC global data.
  @param[in] Channel       - Zero based channel number in the memory controller.

  @retval The value read from the register.
**/
extern
UINT32
MrcHalGetReutChPatCadbWritePointer (
  IN MrcParameters *const MrcData,
  IN const UINT32  Channel
  );

/**
  This function configures the CADB pattern.
  Note that no error checking is done so ensure to pass a correct value.

  @param[in] MrcData       - Include all MRC global data.
  @param[in] Channel       - Zero based channel number in the memory controller.
  @param[in] RegisterValue - The register value to write.

  @retval The value written to the register.
**/
extern
UINT64
MrcHalSetReutChPatCadbProg (
  IN MrcParameters *const MrcData,
  IN const UINT32  Channel,
  IN const UINT64  RegisterValue
  );

/**
  This function gets the CADB pattern.
  Note that no error checking is done so ensure to pass a correct value.

  @param[in] MrcData       - Include all MRC global data.
  @param[in] Channel       - Zero based channel number in the memory controller.

  @retval The value read from sthe register.
**/
extern
UINT64
MrcHalGetReutChPatCadbProg (
  IN MrcParameters *const MrcData,
  IN const UINT32  Channel
  );

/**
  This function configures the CADB unisequencer mode.
  Note that no error checking is done so ensure to pass a correct value.

  @param[in] MrcData       - Include all MRC global data.
  @param[in] Channel       - Zero based channel number in the memory controller.
  @param[in] RegisterValue - The register value to write.

  @retval The value written to the register.
**/
extern
UINT32
MrcHalSetReutChPatCadbMuxCtrl (
  IN MrcParameters *const MrcData,
  IN const UINT32  Channel,
  IN const UINT32  RegisterValue
  );

/**
  This function gets the CADB unisequencer mode.
  Note that no error checking is done so ensure to pass a correct value.

  @param[in] MrcData       - Include all MRC global data.
  @param[in] Channel       - Zero based channel number in the memory controller.

  @retval The value written to the register.
**/
extern
UINT32
MrcHalGetReutChPatCadbMuxCtrl (
  IN MrcParameters *const MrcData,
  IN const UINT32  Channel
  );

/**
  This function configures the CADB deselect mux pattern buffer 0 register.
  Note that no error checking is done so ensure to pass a correct value.

  @param[in] MrcData       - Include all MRC global data.
  @param[in] Channel       - Zero based channel number in the memory controller.
  @param[in] RegisterValue - The register value to write.

  @retval The value written to the register.
**/
extern
UINT32
MrcHalSetRegReutChPatCadbMuxPb0 (
  IN MrcParameters *const MrcData,
  IN const UINT32  Channel,
  IN const UINT32  RegisterValue
  );

/**
  This function configures the CADB deselect mux pattern buffer 1 register.
  Note that no error checking is done so ensure to pass a correct value.

  @param[in] MrcData       - Include all MRC global data.
  @param[in] Channel       - Zero based channel number in the memory controller.
  @param[in] RegisterValue - The register value to write.

  @retval The value written to the register.
**/
extern
UINT32
MrcHalSetRegReutChPatCadbMuxPb1 (
  IN MrcParameters *const MrcData,
  IN const UINT32  Channel,
  IN const UINT32  RegisterValue
  );

/**
  This function configures the CADB deselect mux pattern buffer 2 register.
  Note that no error checking is done so ensure to pass a correct value.

  @param[in] MrcData       - Include all MRC global data.
  @param[in] Channel       - Zero based channel number in the memory controller.
  @param[in] RegisterValue - The register value to write.

  @retval The value written to the register.
**/
extern
UINT32
MrcHalSetRegReutChPatCadbMuxPb2 (
  IN MrcParameters *const MrcData,
  IN const UINT32  Channel,
  IN const UINT32  RegisterValue
  );

/**
  This function configures the CADB select mux pattern buffer 0 register.
  Note that no error checking is done so ensure to pass a correct value.

  @param[in] MrcData       - Include all MRC global data.
  @param[in] Channel       - Zero based channel number in the memory controller.
  @param[in] RegisterValue - The register value to write.

  @retval The value written to the register.
**/
extern
UINT32
MrcHalSetRegReutChPatCadbSelMuxPb0 (
  IN MrcParameters *const MrcData,
  IN const UINT32  Channel,
  IN const UINT32  RegisterValue
  );

/**
  This function configures the CADB select mux pattern buffer 1 register.
  Note that no error checking is done so ensure to pass a correct value.

  @param[in] MrcData       - Include all MRC global data.
  @param[in] Channel       - Zero based channel number in the memory controller.
  @param[in] RegisterValue - The register value to write.

  @retval The value written to the register.
**/
extern
UINT32
MrcHalSetRegReutChPatCadbSelMuxPb1 (
  IN MrcParameters *const MrcData,
  IN const UINT32  Channel,
  IN const UINT32  RegisterValue
  );

/**
  This function configures the CADB select mux pattern buffer 2 register.
  Note that no error checking is done so ensure to pass a correct value.

  @param[in] MrcData       - Include all MRC global data.
  @param[in] Channel       - Zero based channel number in the memory controller.
  @param[in] RegisterValue - The register value to write.

  @retval The value written to the register.
**/
extern
UINT32
MrcHalSetRegReutChPatCadbSelMuxPb2 (
  IN MrcParameters *const MrcData,
  IN const UINT32  Channel,
  IN const UINT32  RegisterValue
  );

/**
  This function configures the CADB pattern mux LMN register.
  Note that no error checking is done so ensure to pass a correct value.

  @param[in] MrcData       - Include all MRC global data.
  @param[in] Channel       - Zero based channel number in the memory controller.
  @param[in] RegisterValue - The register value to write.

  @retval The value written to the register.
**/
extern
UINT32
MrcHalSetRegReutChPatCadbClMuxLmn (
  IN MrcParameters *const MrcData,
  IN const UINT32  Channel,
  IN const UINT32  RegisterValue
  );

/**
  This function configures the CADB pattern mux LMN register.
  Note that no error checking is done so ensure to pass a correct value.

  @param[in] MrcData       - Include all MRC global data.
  @param[in] Channel       - Zero based channel number in the memory controller.
  @param[in] RegisterValue - The register value to write.

  @retval The value written to the register.
**/
extern
UINT32
MrcHalSetRegReutChSeqDummyreadCtlMcmain (
  IN MrcParameters *const MrcData,
  IN const UINT32  Channel,
  IN const UINT32  RegisterValue
  );

/**
  This function configures the CADB dummy read mask register.
  Note that no error checking is done so ensure to pass a correct value.

  @param[in] MrcData       - Include all MRC global data.
  @param[in] Channel       - Zero based channel number in the memory controller.
  @param[in] RegisterValue - The register value to write.

  @retval The value written to the register.
**/
extern
UINT32
MrcHalSetRegReutChSeqDummyreadMaskMcmain (
  IN MrcParameters *const MrcData,
  IN const UINT32  Channel,
  IN const UINT32  RegisterValue
  );

/**
  This function gets the CADB dummy read mask register.
  Note that no error checking is done so ensure to pass a correct value.

  @param[in] MrcData       - Include all MRC global data.
  @param[in] Channel       - Zero based channel number in the memory controller.

  @retval The value written to the register.
**/
extern
UINT32
MrcHalGetRegReutChSeqDummyreadMaskMcmain (
  IN MrcParameters *const MrcData,
  IN const UINT32  Channel
  );

/**
  This function configures the dummy read logical to physical mapping.
  Note that no error checking is done so ensure to pass a correct value.

  @param[in] MrcData       - Include all MRC global data.
  @param[in] Channel       - Zero based channel number in the memory controller.
  @param[in] RegisterValue - The register value to write.

  @retval The value written to the register.
**/
extern
UINT32
MrcHalSetRegReutChSeqRankLogicalToPhysicalMappingMcMain (
  IN MrcParameters *const MrcData,
  IN const UINT32  Channel,
  IN const UINT32  RegisterValue
  );

/**
  This function gets the dummy read logical to physical mapping.
  Note that no error checking is done so ensure to pass a correct value.

  @param[in] MrcData       - Include all MRC global data.
  @param[in] Channel       - Zero based channel number in the memory controller.

  @retval The value written to the register.
**/
extern
UINT32
MrcHalGetRegReutChSeqRankLogicalToPhysicalMappingMcMain (
  IN MrcParameters *const MrcData,
  IN const UINT32  Channel
  );

/**
  This function configures the bank logical to physical mapping.
  Note that no error checking is done so ensure to pass a correct value.

  @param[in] MrcData       - Include all MRC global data.
  @param[in] Channel       - Zero based channel number in the memory controller.
  @param[in] RegisterValue - The register value to write.

  @retval The value written to the register.
**/
extern
UINT64
MrcHalSetRegReutChSeqBankLogicalToPhysicalMappingMcMain (
  IN MrcParameters *const MrcData,
  IN const UINT32  Channel,
  IN const UINT64  RegisterValue
  );

/**
  This function gets the bank logical to physical mapping.
  Note that no error checking is done so ensure to pass a correct value.

  @param[in] MrcData       - Include all MRC global data.
  @param[in] Channel       - Zero based channel number in the memory controller.

  @retval The value read from the register.
**/
extern
UINT64
MrcHalGetRegReutChSeqBankLogicalToPhysicalMappingMcMain (
  IN MrcParameters *const MrcData,
  IN const UINT32  Channel
  );

/**
  This function configures the subsequence control.
  Note that no error checking is done so ensure to pass a correct value.

  @param[in] MrcData       - Include all MRC global data.
  @param[in] Channel       - Zero based channel number in the memory controller.
  @param[in] Index         - Zero based subsequence number in the memory controller.
  @param[in] RegisterValue - The register value to write.

  @retval The value written to the register.
**/
extern
UINT32
MrcHalSetRegReutChSubseqCtlMcmain (
  IN MrcParameters *const MrcData,
  IN const UINT32  Channel,
  IN const UINT32  Index,
  IN const UINT32  RegisterValue
  );

/**
  This function configures the subsequence offset control.
  Note that no error checking is done so ensure to pass a correct value.

  @param[in] MrcData       - Include all MRC global data.
  @param[in] Channel       - Zero based channel number in the memory controller.
  @param[in] Index         - Zero based subsequence number in the memory controller.
  @param[in] RegisterValue - The register value to write.

  @retval The value written to the register.
**/
extern
UINT32
MrcHalSetRegReutChSubseqOffsetCtlMcmain (
  IN MrcParameters *const MrcData,
  IN const UINT32  Channel,
  IN const UINT32  Index,
  IN const UINT32  RegisterValue
  );

/**
  This function sets the sequence configuration.
  Note that no error checking is done so ensure to pass a correct value.

  @param[in] MrcData       - Include all MRC global data.
  @param[in] Channel       - Zero based channel number in the memory controller.
  @param[in] RegisterValue - The register value to write.

  @retval The value written to the register.
**/
extern
UINT64
MrcHalSetRegReutChSeqCfgMcmain (
  IN MrcParameters *const MrcData,
  IN const UINT32  Channel,
  IN const UINT64  RegisterValue
  );

/**
  This function gets the sequence configuration.
  Note that no error checking is done so ensure to pass a correct value.

  @param[in] MrcData       - Include all MRC global data.
  @param[in] Channel       - Zero based channel number in the memory controller.

  @retval The value written to the register.
**/
extern
UINT64
MrcHalGetRegReutChSeqCfgMcmain (
  IN MrcParameters *const MrcData,
  IN const UINT32  Channel
  );

/**
  This function configures the sequence loop count limit.
  Note that no error checking is done so ensure to pass a correct value.

  @param[in] MrcData       - Include all MRC global data.
  @param[in] Channel       - Zero based channel number in the memory controller.
  @param[in] RegisterValue - The register value to write.

  @retval The value written to the register.
**/
extern
UINT32
MrcHalSetRegReutChSeqLoopcountLimitMcmain (
  IN MrcParameters *const MrcData,
  IN const UINT32  Channel,
  IN const UINT32  RegisterValue
  );

/**
  This function configures the sequence base address order carry invert control register.
  Note that no error checking is done so ensure to pass a correct value.

  @param[in] MrcData       - Include all MRC global data.
  @param[in] Channel       - Zero based channel number in the memory controller.
  @param[in] RegisterValue - The register value to write.

  @retval The value written to the register.
**/
extern
UINT32
MrcHalSetRegReutChSeqBaseAddrOrderCarryInvertCtlMcmain (
  IN MrcParameters *const MrcData,
  IN const UINT32  Channel,
  IN const UINT32  RegisterValue
  );

/**
  This function gets the sequence base address order carry invert control register.
  Note that no error checking is done so ensure to pass a correct value.

  @param[in] MrcData       - Include all MRC global data.
  @param[in] Channel       - Zero based channel number in the memory controller.

  @retval The value written to the register.
**/
extern
UINT32
MrcHalGetRegReutChSeqBaseAddrOrderCarryInvertCtlMcmain (
  IN MrcParameters *const MrcData,
  IN const UINT32  Channel
  );

/**
  This function configures the error control register.
  Note that no error checking is done so ensure to pass a correct value.

  @param[in] MrcData       - Include all MRC global data.
  @param[in] Channel       - Zero based channel number in the memory controller.
  @param[in] RegisterValue - The register value to write.

  @retval The value written to the register.
**/
extern
UINT32
MrcHalSetRegReutChErrCtl (
  IN MrcParameters *const MrcData,
  IN const UINT32  Channel,
  IN const UINT32  RegisterValue
  );

/**
  This function gets the error control register.
  Note that no error checking is done so ensure to pass a correct value.

  @param[in] MrcData       - Include all MRC global data.
  @param[in] Channel       - Zero based channel number in the memory controller.

  @retval The value written to the register.
**/
extern
UINT32
MrcHalGetRegReutChErrCtl (
  IN MrcParameters *const MrcData,
  IN const UINT32  Channel
  );

/**
  This function configures the error counter control register.
  Note that no error checking is done so ensure to pass a correct value.

  @param[in] MrcData       - Include all MRC global data.
  @param[in] Channel       - Zero based channel number in the memory controller.
  @param[in] Counter       - Zero based counter number in the memory controller.
  @param[in] RegisterValue - The register value to write.

  @retval The value written to the register.
**/
extern
UINT32
MrcHalSetRegReutChErrCounterCtl (
  IN MrcParameters *const MrcData,
  IN const UINT32  Channel,
  IN const UINT32  Counter,
  IN const UINT32  RegisterValue
  );

/**
  This function gets the error counter control register.
  Note that no error checking is done so ensure to pass a correct value.

  @param[in] MrcData       - Include all MRC global data.
  @param[in] Channel       - Zero based channel number in the memory controller.
  @param[in] Counter       - Zero based counter number in the memory controller.

  @retval The value written to the register.
**/
extern
UINT32
MrcHalGetRegReutChErrCounterCtl (
  IN MrcParameters *const MrcData,
  IN const UINT32  Channel,
  IN const UINT32  Counter
  );

/**
  This function configures the error data mask register.
  Note that no error checking is done so ensure to pass a correct value.

  @param[in] MrcData       - Include all MRC global data.
  @param[in] Channel       - Zero based channel number in the memory controller.
  @param[in] RegisterValue - The register value to write.

  @retval The value written to the register.
**/
extern
UINT64
MrcHalSetRegReutChErrDataMask (
  IN MrcParameters *const MrcData,
  IN const UINT32  Channel,
  IN const UINT64  RegisterValue
  );

/**
  This function configures the error ECC mask register.
  Note that no error checking is done so ensure to pass a correct value.

  @param[in] MrcData       - Include all MRC global data.
  @param[in] Channel       - Zero based channel number in the memory controller.
  @param[in] RegisterValue - The register value to write.

  @retval The value written to the register.
**/
extern
UINT32
MrcHalSetRegReutChErrEccMask (
  IN MrcParameters *const MrcData,
  IN const UINT32  Channel,
  IN const UINT32  RegisterValue
  );

/**
  This function gets the error counter status register.
  Note that no error checking is done so ensure to pass a correct value.

  @param[in] MrcData         - Include all MRC global data.
  @param[in] Channel         - Zero based channel number in the memory controller.
  @param[in] Counter         - Zero based counter number in the memory controller.
  @param[in, out] ErrorCount - The current error counter value.

  @retval TRUE if an overflow occurred, otherwise FALSE.
**/
BOOLEAN
MrcHalGetRegReutChErrCounterStatus (
  IN MrcParameters *const MrcData,
  IN const UINT32  Channel,
  IN const UINT32  Counter,
  IN OUT UINT32    *const ErrorCount
  );

/**
  This function gets the error counter overflow status register.
  Note that no error checking is done so ensure to pass a correct value.

  @param[in] MrcData - Include all MRC global data.
  @param[in] Channel - Zero based channel number in the memory controller.

  @retval The value written to the register.
**/
extern
UINT32
MrcHalGetRegReutChErrCounterOverflowStatus (
  IN MrcParameters *const MrcData,
  IN const UINT32  Channel
  );

/**
  This function gets the error status register.
  Note that no error checking is done so ensure to pass a correct value.

  @param[in] MrcData - Include all MRC global data.
  @param[in] Channel - Zero based channel number in the memory controller.

  @retval The value read from the register.
**/
extern
UINT64
MrcHalGetReutChErrChunkRankByteNthStatus (
  IN MrcParameters *const MrcData,
  IN const UINT32  Channel
  );

/**
  This function configures the sequence control register.
  Note that no error checking is done so ensure to pass a correct value.

  @param[in] MrcData       - Include all MRC global data.
  @param[in] Channel       - Zero based channel number in the memory controller.
  @param[in] RegisterValue - The register value to write.

  @retval The value written to the register.
**/
extern
UINT32
MrcHalSetRegReutChSeqCtlMcmain (
  IN MrcParameters *const MrcData,
  IN const UINT32  Channel,
  IN const UINT32  RegisterValue
  );

/**
  This function configures the scrambler register.
  Note that no error checking is done so ensure to pass a correct value.

  @param[in] MrcData       - Include all MRC global data.
  @param[in] Channel       - Zero based channel number in the memory controller.
  @param[in] RegisterValue - The register value to write.

  @retval The value written to the register.
**/
extern
UINT32
MrcHalSetRegDdrscramble (
  IN MrcParameters *const MrcData,
  IN const UINT32  Channel,
  IN const UINT32  RegisterValue
  );

/**
  This function gets the scrambler register.
  Note that no error checking is done so ensure to pass a correct value.

  @param[in] MrcData - Include all MRC global data.
  @param[in] Channel - Zero based channel number in the memory controller.

  @retval The value written to the register.
**/
extern
UINT32
MrcHalGetRegDdrscramble (
  IN MrcParameters *const MrcData,
  IN const UINT32  Channel
  );

/**
  This function configures the miscellaneous refresh control register.
  Note that no error checking is done so ensure to pass a correct value.

  @param[in] MrcData       - Include all MRC global data.
  @param[in] Channel       - Zero based channel number in the memory controller.
  @param[in] RegisterValue - The register value to write.

  @retval The value written to the register.
**/
extern
UINT32
MrcHalSetRegReutChMiscRefreshCtrl (
  IN MrcParameters *const MrcData,
  IN const UINT32  Channel,
  IN const UINT32  RegisterValue
  );

/**
  This function configures the miscellaneous ZQ control register.
  Note that no error checking is done so ensure to pass a correct value.

  @param[in] MrcData       - Include all MRC global data.
  @param[in] Channel       - Zero based channel number in the memory controller.
  @param[in] RegisterValue - The register value to write.

  @retval The value written to the register.
**/
extern
UINT32
MrcHalSetRegReutChMiscZqCtrl (
  IN MrcParameters *const MrcData,
  IN const UINT32  Channel,
  IN const UINT32  RegisterValue
  );

/**
  This function configures the miscellaneous ODT control register.
  Note that no error checking is done so ensure to pass a correct value.

  @param[in] MrcData       - Include all MRC global data.
  @param[in] Channel       - Zero based channel number in the memory controller.
  @param[in] RegisterValue - The register value to write.

  @retval The value written to the register.
**/
extern
UINT32
MrcHalSetRegReutChMiscOdtCtrl (
  IN MrcParameters *const MrcData,
  IN const UINT32  Channel,
  IN const UINT32  RegisterValue
  );

/**
  This function configures the miscellaneous ODT control register.
  Note that no error checking is done so ensure to pass a correct value.

  @param[in] MrcData       - Include all MRC global data.
  @param[in] Channel       - Zero based channel number in the memory controller.
  @param[in] RegisterValue - The register value to write.

  @retval The value written to the register.
**/
extern
UINT32
MrcHalSetRegReutChMiscCkeCtrl (
  IN MrcParameters *const MrcData,
  IN const UINT32  Channel,
  IN const UINT32  RegisterValue
  );

/**
  This function configures the sequence row address swizzle lower register.
  Note that no error checking is done so ensure to pass a correct value.

  @param[in] MrcData       - Include all MRC global data.
  @param[in] Channel       - Zero based channel number in the memory controller.
  @param[in] RegisterValue - The register value to write.

  @retval The value written to the register.
**/
extern
UINT32
MrcHalSetRegReutChSeqRowAddrSwizzleLowerMcmain (
  IN MrcParameters *const MrcData,
  IN const UINT32  Channel,
  IN const UINT32  RegisterValue
  );

/**
  This function gets the sequence row address swizzle lower register.
  Note that no error checking is done so ensure to pass a correct value.

  @param[in] MrcData       - Include all MRC global data.
  @param[in] Channel       - Zero based channel number in the memory controller.

  @retval The value written to the register.
**/
extern
UINT32
MrcHalGetRegReutChSeqRowAddrSwizzleLowerMcmain (
  IN MrcParameters *const MrcData,
  IN const UINT32  Channel
  );

/**
  This function configures the sequence row address swizzle upper register.
  Note that no error checking is done so ensure to pass a correct value.

  @param[in] MrcData       - Include all MRC global data.
  @param[in] Channel       - Zero based channel number in the memory controller.
  @param[in] RegisterValue - The register value to write.

  @retval The value written to the register.
**/
extern
UINT64
MrcHalSetRegReutChSeqRowAddrSwizzleUpperMcmain (
  IN MrcParameters *const MrcData,
  IN const UINT32  Channel,
  IN const UINT64  RegisterValue
  );

/**
  This function gets the sequence row address swizzle upper register.
  Note that no error checking is done so ensure to pass a correct value.

  @param[in] MrcData       - Include all MRC global data.
  @param[in] Channel       - Zero based channel number in the memory controller.

  @retval The value written to the register.
**/
extern
UINT64
MrcHalGetRegReutChSeqRowAddrSwizzleUpperMcmain (
  IN MrcParameters *const MrcData,
  IN const UINT32  Channel
  );

/**
  This function sets the receive training per bit register.
  Note that no error checking is done so ensure to pass a correct value.

  @param[in] Bit           - Zero based bit number in the byte.
  @param[in] BitFieldValue - The register bitfield value.
  @param[in] RegisterValue - The starting register value.

  @retval The value written to the register.
**/
extern
UINT32
MrcHalSetRxperbitrankLane (
  IN const UINT32 Bit,
  IN const UINT32 BitFieldValue,
  IN const UINT32 RegisterValue
  );

/**
  This function sets the transmit training per bit register.
  Note that no error checking is done so ensure to pass a correct value.

  @param[in] MrcData       - Include all MRC global data.
  @param[in] Channel       - Zero based channel number in the memory controller.
  @param[in] Rank          - Zero based rank number in the channel.
  @param[in] Byte          - Zero based byte number in the rank.
  @param[in] RegisterValue - The starting register value.

  @retval The value written to the register.
**/
extern
UINT32
MrcHalSetRegTxperbitrank (
  IN MrcParameters *const MrcData,
  IN const UINT32  Channel,
  IN const UINT32  Rank,
  IN const UINT32  Byte,
  IN const UINT32  RegisterValue
  );

/**
  This function gets the transmit training per bit register.
  Note that no error checking is done so ensure to pass a correct value.

  @param[in] MrcData       - Include all MRC global data.
  @param[in] Channel       - Zero based channel number in the memory controller.
  @param[in] Rank          - Zero based rank number in the channel.
  @param[in] Byte          - Zero based byte number in the rank.
  @param[in] Bit           - Zero based bit number in the byte.

  @retval The value read from the register.
**/
extern
INT8
MrcHalGetRegTxperbitrank (
  IN MrcParameters *const MrcData,
  IN const UINT32  Channel,
  IN const UINT32  Rank,
  IN const UINT32  Byte,
  IN const UINT32  Bit
  );

/**
  This function sets the transmit training per bit register.
  Note that no error checking is done so ensure to pass a correct value.

  @param[in] Bit           - Zero based bit number in the byte.
  @param[in] BitFieldValue - The register bitfield value.
  @param[in] RegisterValue - The starting register value.

  @retval The value written to the register.
**/
extern
UINT32
MrcHalSetTxperbitrankLane (
  IN const UINT32 Bit,
  IN const UINT32 BitFieldValue,
  IN const UINT32 RegisterValue
  );

/**
  This function gets the transmit training register.
  Note that no error checking is done so ensure to pass a correct value.

  @param[in] MrcData     - Include all MRC global data.
  @param[in] Channel     - Zero based channel number in the memory controller.
  @param[in] Rank        - Zero based rank number in the channel.
  @param[in] Byte        - Zero based byte number in the rank.
  @param[in] MarginGroup - Margin group index.

  @retval The value read from the register.
**/
extern
INT16
MrcHalGetRegTxtrainrank (
  IN MrcParameters *const MrcData,
  IN const UINT32  Channel,
  IN const UINT32  Rank,
  IN const UINT32  Byte,
  IN const GSM_GT  MarginGroup
  );

/**
  This function sets the transmit Vref register.
  Note that no error checking is done so ensure to pass a correct value.

  @param[in] MrcData - Include all MRC global data.
  @param[in] Channel - Zero based channel number in the memory controller.
  @param[in] Value   - The new bitfield vref value.
  @param[in] Enable  - The new bitfield enable value.
**/
extern
void
MrcHalSetRegVrefadjust1 (
  IN MrcParameters *const MrcData,
  IN const UINT32  Channel,
  IN const UINT32  Value,
  IN const UINT32  Enable
  );

/**
  This function gets the transmit Vref register.
  Note that no error checking is done so ensure to pass a correct value.

  @param[in] MrcData     - Include all MRC global data.
  @param[in] Channel     - Zero based channel number in the memory controller or >= MAX_CHANNEL to get command voltage.
  @param[in, out] Enable - TRUE if enabled otherwise FALSE.

  @retval The value read from the register.
**/
extern
INT16
MrcHalGetRegVrefadjust1 (
  IN MrcParameters *const MrcData,
  IN const UINT32  Channel,
  IN OUT BOOLEAN   *const Enable
  );

/**
  This function sets the clock PI value.
  Note that no error checking is done so ensure to pass a correct value.

  @param[in] MrcData - Include all MRC global data.
  @param[in] Channel - Zero based channel number in the memory controller.
  @param[in] Rank    - Zero based rank number in the channel.
  @param[in] Value   - The new value.

  @retval The value written to the register.
**/
extern
UINT32
MrcHalRmwRegClkClkPiCode (
  IN MrcParameters *const MrcData,
  IN const UINT32  Channel,
  IN const UINT32  Rank,
  IN const UINT32  Value
  );

/**
  This function gets the clock PI value.
  Note that no error checking is done so ensure to pass a correct value.

  @param[in] MrcData - Include all MRC global data.
  @param[in] Channel - Zero based channel number in the memory controller.
  @param[in] Rank    - Zero based rank number in the channel.

  @retval The value read from the register.
**/
extern
UINT16
MrcHalGetRegClkClkPiCode (
  IN MrcParameters *const MrcData,
  IN const UINT32  Channel,
  IN const UINT32  Rank
  );

/**
  This function sets the command N PI value.
  Note that no error checking is done so ensure to pass a correct value.

  @param[in] MrcData       - Include all MRC global data.
  @param[in] Channel       - Zero based channel number in the memory controller.
  @param[in] PiOffset      - The PI code offset.
  @param[in] Value         - The starting register value.

  @retval The value read from the register.
**/
extern
UINT32
MrcHalRmwRegCmdnCmdPiCode (
  IN MrcParameters *const MrcData,
  IN const UINT32  Channel,
  IN const UINT32  PiOffset,
  IN const UINT32  Value
  );

/**
  This function gets the command N PI value.
  Note that no error checking is done so ensure to pass a correct value.

  @param[in] MrcData - Include all MRC global data.
  @param[in] Channel - Zero based channel number in the memory controller.
  @param[in] Offset  - Command PI code offset.

  @retval The value read from the register.
**/
extern
UINT16
MrcHalGetRegCmdnCmdPiCode (
  IN MrcParameters *const MrcData,
  IN const UINT32  Channel,
  IN const UINT32  Offset
  );

/**
  This function sets the command S PI value.
  Note that no error checking is done so ensure to pass a correct value.

  @param[in] MrcData       - Include all MRC global data.
  @param[in] Channel       - Zero based channel number in the memory controller.
  @param[in] PiOffset      - The PI code offset.
  @param[in] Value         - The starting register value.

  @retval The value read from the register.
**/
extern
UINT32
MrcHalRmwRegCmdsCmdPiCode (
  IN MrcParameters *const MrcData,
  IN const UINT32  Channel,
  IN const UINT32  PiOffset,
  IN const UINT32  Value
  );

/**
  This function gets the command S PI value.
  Note that no error checking is done so ensure to pass a correct value.

  @param[in] MrcData - Include all MRC global data.
  @param[in] Channel - Zero based channel number in the memory controller.
  @param[in] Offset  - Zero based channel number in the memory controller.

  @retval The value read from the register.
**/
extern
UINT16
MrcHalGetRegCmdsCmdPiCode (
  IN MrcParameters *const MrcData,
  IN const UINT32  Channel,
  IN const UINT32  Offset
  );

/**
  This function sets the command CKE PI value.
  Note that no error checking is done so ensure to pass a correct value.

  @param[in] MrcData       - Include all MRC global data.
  @param[in] Channel       - Zero based channel number in the memory controller.
  @param[in] PiOffset      - Zero based pi offset.
  @param[in] RegisterValue - The starting register value.

  @retval The value read from the register.
**/
extern
UINT32
MrcHalRmwRegCkeCmdPiCode (
  IN MrcParameters *const MrcData,
  IN const UINT32  Channel,
  IN const UINT32  PiOffset,
  IN const UINT32  RegisterValue
  );

/**
  This function gets the command CKE PI value.
  Note that no error checking is done so ensure to pass a correct value.

  @param[in] MrcData   - Include all MRC global data.
  @param[in] Channel   - Zero based channel number in the memory controller.
  @param[in] PiOffset  - Zero based pi offset.

  @retval The value read from the register.
**/
extern
INT16
MrcHalGetRegCkeCmdPiCode (
  IN MrcParameters *const MrcData,
  IN const UINT32  Channel,
  IN const UINT32  PiOffset
  );

/**
  This function sets the control command PI value.
  Note that no error checking is done so ensure to pass a correct value.

  @param[in] MrcData  - Include all MRC global data.
  @param[in] Channel  - Zero based channel number in the memory controller.
  @param[in] PiOffset - The PI code offset.
  @param[in] Value    - The starting register value.

  @retval The value read from the register.
**/
extern
UINT32
MrcHalRmwRegCtlCtlPiCode (
  IN MrcParameters *const MrcData,
  IN const UINT32  Channel,
  IN const UINT32  PiOffset,
  IN const UINT32  Value
  );

/**
  This function gets the control command PI value.
  Note that no error checking is done so ensure to pass a correct value.

  @param[in] MrcData       - Include all MRC global data.
  @param[in] Channel       - Zero based channel number in the memory controller.
  @param[in] PiOffset      - The PI code offset.

  @retval The value read from the register.
**/
extern
INT16
MrcHalGetRegCtlCtlPiCode (
  IN MrcParameters *const MrcData,
  IN const UINT32  Channel,
  IN const UINT32  PiOffset
  );

/**
  This function sets the CKE control PI value.
  Note that no error checking is done so ensure to pass a correct value.

  @param[in] MrcData  - Include all MRC global data.
  @param[in] Channel  - Zero based channel number in the memory controller.
  @param[in] PiOffset - The PI code offset.
  @param[in] Value    - The starting register value.

  @retval The value read from the register.
**/
extern
UINT32
MrcHalRmwRegCkeCtlPiCode (
  IN MrcParameters *const MrcData,
  IN const UINT32  Channel,
  IN const UINT32  PiOffset,
  IN const UINT32  Value
  );

/**
  This function gets the CKE control PI value.
  Note that no error checking is done so ensure to pass a correct value.

  @param[in] MrcData       - Include all MRC global data.
  @param[in] Channel       - Zero based channel number in the memory controller.
  @param[in] PiOffset      - The PI code offset.

  @retval The value read from the register.
**/
extern
INT16
MrcHalGetRegCkeCtlPiCode (
  IN MrcParameters *const MrcData,
  IN const UINT32  Channel,
  IN const UINT32  PiOffset
  );

/**
  Program MCHBAR_CHx_CR_SC_IO_LATENCY register using Host data.

  @param[in] MrcData  - Include all MRC global data.
  @param[in] Channel  - Channel to work on.
**/
void
MrcHalSetIoLatency (
  IN MrcParameters *const MrcData,
  IN const UINT32         Channel
  );

/**
  Program MCHBAR_CHx_CR_SC_ROUNDTRIP_LATENCY register using Host data.

  @param[in] MrcData  - Include all MRC global data.
  @param[in] Channel  - Channel to work on.
**/
void
MrcHalSetRoundtripLatency (
  IN MrcParameters *const MrcData,
  IN const UINT32         Channel
  );

/**
  Read MCHBAR_CHx_CR_SC_ROUNDTRIP_LATENCY register value.

  @param[in] MrcData  - Include all MRC global data.
  @param[in] Channel  - Channel to work on.

  @retval The value read from the register.
**/
UINT32
MrcHalGetRoundtripLatency (
  IN MrcParameters *const MrcData,
  IN const UINT32         Channel
  );

/**
  This function gets the date error status register.
  Note that no error checking is done so ensure to pass a correct value.

  @param[in] MrcData - Include all MRC global data.
  @param[in] Channel - Zero based channel number in the memory controller.

  @retval The value written to the register.
**/
extern
UINT64
MrcHalGetRegErrDataStatus (
  IN MrcParameters *const MrcData,
  IN const UINT32  Channel
  );

/**
  This function returns the current status of the REUT engine.

  @param[in]  MrcData   - Include all MRC global data.
  @param[out] TestDone  - Channel bit mask indicating which channels are done executing.
  @param[out] TestError - Channel bit mask indicating which channels have a test error.
**/
extern
void
MrcHalGetReutGlobalStatus (
  IN MrcParameters *const MrcData,
  OUT UINT32       *const TestDone,
  OUT UINT32       *const TestError
  );

/**
  This function gets the CKE mapping value for the selected channel.
  Note that no error checking is done so ensure to pass a correct value.

  @param[in] MrcData - Include all MRC global data.
  @param[in] Channel - Zero based channel number.

  @retval The register bitfield value.
**/
extern
UINT32
MrcHalGetCkeMapping (
  IN MrcParameters *const MrcData,
  IN const UINT32  Channel
  );

/**
  This function gets the current sequence loopcount value for the selected channel.
  Note that no error checking is done so ensure to pass a correct value.

  @param[in] MrcData - Include all MRC global data.
  @param[in] Channel - Zero based channel number.

  @retval The register bitfield value.
**/
extern
UINT32
MrcHalGetSeqLoopcountStatus (
  IN MrcParameters *const MrcData,
  IN const UINT32         Channel
  );

/**
  This function gets the current subsequence pointer value for the selected channel.
  Note that no error checking is done so ensure to pass a correct value.

  @param[in] MrcData - Include all MRC global data.
  @param[in] Channel - Zero based channel number.

  @retval The register bitfield value.
**/
extern
UINT32
MrcHalGetSeqPointer (
  IN MrcParameters *const MrcData,
  IN const UINT32         Channel
  );

/**
  This function gets the current subsequence cacheline value for the selected channel.
  Note that no error checking is done so ensure to pass a correct value.

  @param[in] MrcData - Include all MRC global data.
  @param[in] Channel - Zero based channel number.

  @retval The register bitfield value.
**/
extern
UINT32
MrcHalGetSeqCurrentCacheline (
  IN MrcParameters *const MrcData,
  IN const UINT32         Channel
  );

/**
  This function gets the value from the base address current register.
  Note that no error checking is done so ensure to pass a correct value.

  @param[in] MrcData - Include all MRC global data.
  @param[in] Channel - Zero based channel number.

  @retval The register value.
**/
extern
UINT64
MrcHalGetBaseAddressCurrent (
  IN MrcParameters *const MrcData,
  IN const UINT32         Channel
  );

/**
  This function gets the value from the offset address current register.
  Note that no error checking is done so ensure to pass a correct value.

  @param[in] MrcData - Include all MRC global data.
  @param[in] Channel - Zero based channel number.

  @retval The register value.
**/
extern
UINT64
MrcHalGetOffsetAddressCurrent (
  IN MrcParameters *const MrcData,
  IN const UINT32         Channel
  );

/**
  This function gets address of the most current error.

  @param[in]  MrcData - Include all MRC global data.
  @param[in]  Channel - Zero based channel number in the memory controller.
  @param[out] Rank    - Pointer to buffer containing rank address.
  @param[out] Bank    - Pointer to buffer containing bank address.
  @param[out] Row     - Pointer to buffer containing row address.
  @param[out] Col     - Pointer to buffer containing column address.

**/
extern
void
MrcHalGetReutChErrorAddress (
  IN MrcParameters *const MrcData,
  IN const UINT8          Channel,
  OUT UINT8               *Rank,
  OUT UINT8               *Bank,
  OUT UINT32              *Row,
  OUT UINT16              *Col
  );

/**
  This function gets the WDB capture control register.

  @param[in] MrcData       - Include all MRC global data.
  @param[in] Channel       - Zero based channel number in the memory controller.
  @param[in] RegisterValue - The register value to write.

  @retval The value written to the register.
**/
extern
UINT32
MrcHalGetReutWdbCaptureControl (
  IN MrcParameters *const MrcData,
  IN const UINT32         Channel
  );

/**
  This function configures the WDB capture control register.

  @param[in] MrcData       - Include all MRC global data.
  @param[in] Channel       - Zero based channel number in the memory controller.
  @param[in] RegisterValue - The register value to write.

  @retval The value written to the register.
**/
extern
UINT32
MrcHalSetReutWdbCaptureControl (
  IN MrcParameters *const MrcData,
  IN const UINT32         Channel,
  IN const UINT32         RegisterValue
  );

/**
  This function gets the current write data buffer capture pointer.

  @param[in] MrcData                   - Include all MRC global data.
  @param[in] Channel                   - Zero based channel number.

  @retval Value of current capture pointer bitfield
**/
extern
UINT8
MrcHalGetReutWdbCurrentCapturePointer (
  IN MrcParameters *const   MrcData,
  IN const UINT32           Channel
  );

/**
  This function sets the WDB address as data controls.

  @param[in] MrcData            - Include all MRC global data.
  @param[in] WriteAsDataControl - Write as data control.
  @param[in] ReadAsDataControl  - Read as data control.
**/
void
MrcHalRmwPatWdbAddressAsDataCtrl (
  IN MrcParameters *const MrcData,
  IN const BOOLEAN WriteAsDataControl,
  IN const BOOLEAN ReadAsDataControl
  );

/**
  This function sets the write data buffer pattern.

  @param[in] MrcData             - Include all MRC global data.
  @param[in] Channel             - Zero based channel number.
  @param[in] Pattern             - Pointer to buffer containing the DqDB pattern.
  @param[in] CachelineCount      - Size of the buffer pattern in number of cachelines.  Each cacheline has 8 UINT64 elements.  For example, if CachelineCount is 1 then the Pattern buffer size is 64 bytes.
  @param[in] StartCachelineIndex - Start offset on the DqDB.  The sum of the CachelineCount and StartCachelineIndex values must be less than or equal to the MaxNumberDqdbCachelines value from the GetCpgcInfo() function.
**/
extern
void
MrcHalSetWdbPattern (
  IN MrcParameters *const MrcData,
  IN const UINT32 Channel,
  IN const UINT64 *Pattern,
  IN const UINT32 CachelineCount,
  IN const UINT32 StartCachelineIndex
  );

/**
  This function gets the write data buffer pattern.

  @param[in] MrcData             - Include all MRC global data.
  @param[in] Channel             - Zero based channel number.
  @param[out] Pattern            - Pointer to buffer to be filled with the DqDB pattern.
  @param[in] CachelineCount      - Size of the buffer pattern in number of cachelines.  Each cacheline has 8 UINT64 elements.  For example, if CachelineCount is 1 then the Pattern buffer size is 64 bytes.
  @param[in] StartCachelineIndex - Start offset on the DqDB.  The sum of the CachelineCount and StartCachelineIndex values must be less than or equal to the MaxNumberDqdbCachelines value from the GetCpgcInfo() function.
**/
extern
void
MrcHalGetWdbPattern (
  IN  MrcParameters *const MrcData,
  IN  const UINT32 Channel,
  OUT const UINT64 *Pattern,
  IN  const UINT32 CachelineCount,
  IN  const UINT32 StartCachelineIndex
);

/**
  This function sets the write data buffer pattern controls.

  @param[in] MrcData     - Include all MRC global data.
  @param[in] Channel     - Zero based channel number.
  @param[in] StartIndex  - Starting index in the DqDB.  The value must be less than or equal to the MaxNumberDqdbCachelines value from the GetCpgcInfo() function.
  @param[in] EndIndex    - Ending index in the DqDB.  The value must be less than or equal to the StartIndex value and less than or equal to the MaxNumberDqdbCachelines value from the GetCpgcInfo() function.
  @param[in] IncRateMode - Increment rate scale control.
  @param[in] IncRate     - Increment rate value.  If the IncRateMode is ExponentialDqdbIncRateMode then the IncRate value must be less than or equal to the MaxDqdbIncRateExponentVal from the GetCpgcInfo() function.  If the IncRateMode is LinearDqdbIncRateMode then the IncRate value must be less than or equal to the MaxDqdbIncRateLinearVal from the GetCpgcInfo() function.
**/
extern
void
MrcHalRmwWdbPatternControl (
  IN MrcParameters                             *const MrcData,
  IN const UINT32                              Channel,
  IN const UINT32                              StartIndex,
  IN const UINT32                              EndIndex,
  IN const MRC_HAL_ENUM_INCRMENT_SCALE_CONTROL IncRateMode,
  IN const UINT32                              IncRate
  );

/**
  This function sets the write data buffer pattern mux controls.

  @param[in] MrcData                    - Include all MRC global data.
  @param[in] Channel                    - Zero based channel number.
  @param[in] MuxControl                 - Mux selector. LFSR, 24 bit buffer, or LMN value.
  @param[in] MuxControlCount            - The number of MuxControl elements.
  @param[in] LfsrType                   - LFSR type control.
  @param[in] ChainingLfsr               - LFSR chaining control.
  @param[in] EccReplaceByteControl      - ECC replace byte control.
  @param[in] EccDataSourceSel           - Indicates whether byte 0 or byte 7 is transmitted and compared for the ECC byte.
  @param[in] SaveLfsrSeedRate           - The rate at which the LFSR seed is saved.
  @param[in] ReloadLfsrSeedRate         - The rate at which the LFSR seed is reloaded.
  @param[in] ReloadSaveLfsrSeedRateMode - LFSR seed reload, save rate mode.
**/
extern
void
MrcHalRmwWdbPatternMuxControl (
  IN MrcParameters                            *const MrcData,
  IN const UINT32                             Channel,
  IN const MRC_HAL_ENUM_MUX_CONTROL           *const MuxControl,
  IN const UINT32                             MuxControlCount,
  IN const MRC_HAL_ENUM_LFSR_TYPE             LfsrType,
  IN const MRC_HAL_ENUM_LFSR_CHAINING_CONTROL ChainingLfsr,
  IN const MRC_HAL_ENUM_ECC_REPLACE_BYTE      EccReplaceByteControl,
  IN const MRC_HAL_ENUM_ECC_SOURCE_SELECT     EccDataSourceSel,
  IN const UINT32                             SaveLfsrSeedRate,
  IN const UINT32                             ReloadLfsrSeedRate,
  IN const MRC_HAL_ENUM_SEED_RATE_MODE        ReloadSaveLfsrSeedRateMode
  );

/**
  This function will program all present channels with the seeds passed in.

  @param[in] MrcData   - Global MRC data structure
  @param[in] ChannelIn - Zero based channel number.
  @param[in] Seeds     - Array of seeds programmed into PAT_WDB_CL_MUX_PB_RD/WR
  @param[in] Start     - Zero based starting seed location
  @param[in] SeedCount - Number of seeds in the array
  @param[in] ReadWrite - Read/Write buffer select bit field. Bit 0 = Read, Bit 1 = Write.
**/
extern
void
MrcHalProgramLfsr (
  IN MrcParameters                            *const MrcData,
  IN const UINT32                             ChannelIn,
  IN const UINT32                             *const Seeds,
  IN const UINT32                             Start,
  IN const UINT32                             SeedCount,
  IN const MRC_HAL_ENUM_PATTERN_BUFFER_SELECT ReadWrite
  );

/**
  Function used to set the DqDB unisequencer L/M/N values.

  @param[in] MrcData         - Global MRC data structure
  @param[in] Channel         - Zero based channel number.
  @param[in] LValue          - DqDB unisequencer L counter value.
  @param[in] MValue          - DqDB unisequencer M counter value.
  @param[in] NValue          - DqDB unisequencer N counter value.
  @param[in] LDataSel        - DqDB unisequencer L data select value.
  @param[in] EnableFreqSweep - Enables the Frequency Sweep feature.
**/
extern
void
MrcHalProgramLmnMux (
  IN MrcParameters                        *const MrcData,
  IN const UINT32                         Channel,
  IN const UINT32                         LValue,
  IN const UINT32                         MValue,
  IN const UINT32                         NValue,
  IN const MRC_HAL_ENUM_L_DATA_SELECT     LDataSel,
  IN const MRC_HAL_ENUM_ENABLE_SWEEP_FREQ EnableFreqSweep
  );

/**
  Function used to set the DqDB Invert/DC configuration.

  @param[in] MrcData           - Global MRC data structure
  @param[in] Channel           - Zero based channel number.
  @param[in] InvOrDcControl    - Invert/DC mode.
  @param[in] DcPolarity        - DC polarity (when operating in the DC mode). 0 = DC low. 1 = DC high.
  @param[in] ShiftRateExponent - Exponent of the bitmask shift rate.
**/
extern
void
MrcHalProgramDqDbInvertDc (
  IN MrcParameters                          *const MrcData,
  IN const UINT32                           Channel,
  IN const MRC_HAL_ENUM_INV_OR_DC_CONTROL   InvOrDcControl,
  IN const MRC_HAL_ENUM_DC_POLARITY_CONTROL DcPolarity,
  IN const UINT32                           ShiftRateExponent
  );

/**
  This function sets the command address data buffer pattern controls.

  @param[in] MrcData              - Include all MRC global data.
  @param[in] Channel              - Zero based channel number.
  @param[in] EnableCadbOnDeselect - Enable CADB on deselect control.
  @param[in] EnableCadbAlwaysOn   - Enable CADB always on control.
  @param[in] CmdDeselectStart     - Command deselect start value.
  @param[in] CmdDeselectStop      - Command deselect stop value.
  @param[in] LaneDeselectEnable   - Lane deselect control.
  @param[in] CasSelectEnable      - CAS select control.
  @param[in] ActSelectEnable      - Activate select control.
  @param[in] PreSelectEnable      - Preselect control.
  @param[in] SaveCurrentSeed      - Save current seed control.
  @param[in] ReloadStartingSeed   - Reload starting seed control.
**/
extern
void
MrcHalRmwCadbPatternControl (
  IN MrcParameters                         *const MrcData,
  IN const UINT32                          Channel,
  IN MRC_HAL_ENUM_CADB_ON_DESELECT_CONTROL EnableCadbOnDeselect,
  IN MRC_HAL_ENUM_CADB_ALWAYS_ON_CONTROL   EnableCadbAlwaysOn,
  IN MRC_HAL_ENUM_CMD_DESELECT_CONTROL     CmdDeselectStart,
  IN MRC_HAL_ENUM_CMD_DESELECT_CONTROL     CmdDeselectStop,
  IN MRC_HAL_ENUM_LANE_DESELECT_CONTROL    LaneDeselectEnable,
  IN MRC_HAL_ENUM_CAS_SELECT_CONTROL       CasSelectEnable,
  IN MRC_HAL_ENUM_ACT_SELECT_CONTROL       ActSelectEnable,
  IN MRC_HAL_ENUM_PRE_SELECT_CONTROL       PreSelectEnable,
  IN MRC_HAL_ENUM_SAVE_SEED_CONTROL        SaveCurrentSeed,
  IN MRC_HAL_ENUM_RELOAD_SEED_CONTROL      ReloadStartingSeed
  );

/**
  This function sets the command address data buffer pattern.

  @param[in] MrcData           - Include all MRC global data.
  @param[in] CadbDataAddress   - CADB data address value.
  @param[in] CadbDataBank      - CADB data bank value.
  @param[in] CadbDataCs        - CADB data chip select value.
  @param[in] CadbDataControl   - CADB data control value.
  @param[in] CadbDataOdt       - CADB data on die termination value.
  @param[in] CadbDataCke       - CADB data CKE value.
  @param[in] CadbDataParityInv - CADB data parity invert value.
**/
extern
UINT64
MrcHalSetCadbPatternBufferRecord (
  IN MrcParameters                            *const MrcData,
  IN const UINT32                             CadbDataAddress,
  IN const UINT32                             CadbDataBank,
  IN const UINT32                             CadbDataCs,
  IN const UINT32                             CadbDataControl,
  IN const UINT32                             CadbDataOdt,
  IN const UINT32                             CadbDataCke,
  IN const MRC_HAL_ENUM_PARITY_INVERT_CONTROL CadbDataParityInv
  );

/**
  This function sets the command address data buffer pattern.

  @param[in] MrcData       - Include all MRC global data.
  @param[in] Channel       - Zero based channel number.
  @param[in] Pattern       - Pointer to buffer containing the CADB pattern.
  @param[in] PatternCount  - Size of the buffer pattern in term of the count of CADB patterns.  Each row has 2 UINT32 elements.
  @param[in] StartPointer  - Start offset on the CADB.
**/
extern
void
MrcHalRmwCadbPatternBufferInit (
  IN MrcParameters       *const MrcData,
  IN const UINT32        Channel,
  IN const UINT64_STRUCT *Pattern,
  IN UINT32              PatternCount,
  IN const UINT32        StartPointer
  );

/**
  This function sets the write data buffer pattern mux controls.

  @param[in] MrcData               - Include all MRC global data.
  @param[in] Channel               - Zero based channel number.
  @param[in] MuxControl            - Mux control.
  @param[in] MuxControlCount       - Number of MuxControl entries.
  @param[in] SelectMuxControl      - Select mux control.
  @param[in] SelectMuxControlCount - Number of SelectMuxControl entries.
  @param[in] LfsrType              - LSFR type.
  @param[in] ChainingLfsr          - Chaining LFSR control.
**/
extern
void
MrcHalRmwCadbPatternMuxControl (
  IN MrcParameters                            *const MrcData,
  IN const UINT32                             Channel,
  IN const MRC_HAL_ENUM_MUX_CONTROL           *const MuxControl,
  IN const UINT32                             MuxControlCount,
  IN const MRC_HAL_ENUM_MUX_CONTROL           *const SelectMuxControl,
  IN const UINT32                             SelectMuxControlCount,
  IN const MRC_HAL_ENUM_LFSR_TYPE             LfsrType,
  IN const MRC_HAL_ENUM_LFSR_CHAINING_CONTROL ChainingLfsr
  );

/**
  This function sets the command address data buffer mux pattern.

  @param[in] MrcData            - Include all MRC global data.
  @param[in] Channel            - Zero based channel number.
  @param[in] PatternBuffer      - Pattern buffer values.
  @param[in] PatternBufferCount - Number of PatternBuffer entries.
**/
extern
void
MrcHalSetCadbMuxPatternBuffer (
  IN MrcParameters *const MrcData,
  IN const UINT32  Channel,
  IN const UINT32  *const PatternBuffer,
  IN const UINT32  PatternBufferCount
  );

/**
  This function sets the command address data buffer sel pattern.

  @param[in] MrcData            - Include all MRC global data.
  @param[in] Channel            - Zero based channel number.
  @param[in] PatternBuffer      - Pattern buffer values.
  @param[in] PatternBufferCount - Number of PatternBuffer entries.
**/
extern
void
MrcHalSetCadbSelMuxPatternBuffer (
  IN MrcParameters *const MrcData,
  IN const UINT32  Channel,
  IN const UINT32  *const PatternBuffer,
  IN const UINT32  PatternBufferCount
  );

/**
  This function sets the command address data buffer CL mux LMN.

  @param[in] MrcData         - Include all MRC global data.
  @param[in] Channel         - Zero based channel number.
  @param[in] LDataSel        - L data select value.
  @param[in] EnableFreqSweep - Frequency sweep control.
  @param[in] LCounter        - L counter value.
  @param[in] MCounter        - M counter value.
  @param[in] NCounter        - N counter value.
**/
extern
void
MrcHalSetCadbClMuxLmn (
  IN MrcParameters                        *const MrcData,
  IN const UINT32                         Channel,
  IN const MRC_HAL_ENUM_L_DATA_SELECT     LDataSel,
  IN const MRC_HAL_ENUM_ENABLE_SWEEP_FREQ EnableFreqSweep,
  IN const UINT32                         LCounter,
  IN const UINT32                         MCounter,
  IN const UINT32                         NCounter
  );

/**
  This function sets the dummy read control.

  @param[in] MrcData         - Include all MRC global data.
  @param[in] Channel         - Zero based channel number.
  @param[in] LDataSel        - L data select value.
  @param[in] EnableFreqSweep - Frequency sweep control.
  @param[in] LCounter        - L counter value.
  @param[in] MCounter        - M counter value.
  @param[in] NCounter        - N counter value.
**/
extern
void
MrcHalSetDummyReadControl (
  IN MrcParameters                        *const MrcData,
  IN const UINT32                         Channel,
  IN const MRC_HAL_ENUM_L_DATA_SELECT     LDataSel,
  IN const MRC_HAL_ENUM_ENABLE_SWEEP_FREQ EnableFreqSweep,
  IN const UINT32                         LCounter,
  IN const UINT32                         MCounter,
  IN const UINT32                         NCounter
  );

/**
  This function sets the dummy read rank and bank masks.

  @param[in] MrcData  - Include all MRC global data.
  @param[in] Channel  - Zero based channel number.
  @param[in] RankMask - Rank bit field mask.
  @param[in] BankMask - Bank bit field mask.
**/
extern
void
MrcHalRmwDummyReadRankBankMask (
  IN MrcParameters                        *const MrcData,
  IN const UINT32                         Channel,
  IN const MRC_HAL_ENUM_RANK_MASK_CONTROL RankMask,
  IN const MRC_HAL_ENUM_BANK_MASK_CONTROL BankMask
  );

/**
  This function sets the logical to physical mapping for the specified rank in the specified channel.

  @param[in] MrcData      - Include all MRC global data.
  @param[in] Channel      - Zero based channel number.
  @param[in] LogicalRank  - Zero based logical rank number.
  @param[in] PhysicalRank - The physical rank value.
**/
extern
void
MrcHalSetLogicalToPhysicalRankMapping (
  IN MrcParameters *const MrcData,
  IN const UINT32  Channel,
  IN const UINT32  LogicalRank,
  IN const UINT32  PhysicalRank
  );

/**
  This function gets the logical to physical mapping for the specified rank in the specified channel.

  @param[in] MrcData      - Include all MRC global data.
  @param[in] Channel      - Zero based channel number.
  @param[in] LogicalRank  - Zero based logical rank number.
**/
extern
UINT32
MrcHalGetLogicalToPhysicalRankMapping (
  IN MrcParameters *const MrcData,
  IN const UINT32  Channel,
  IN const UINT32  LogicalRank
  );

/**
  This function sets the logical to physical mapping for the specified bank in the specified channel.

  @param[in] MrcData      - Include all MRC global data.
  @param[in] Channel      - Zero based channel number.
  @param[in] LogicalBank  - Zero based logical rank number.
  @param[in] PhysicalBank - The physical rank value.
**/
extern
void
MrcHalSetLogicalToPhysicalBankMapping (
  IN MrcParameters *const MrcData,
  IN const UINT32  Channel,
  IN const UINT32  LogicalBank,
  IN const UINT32  PhysicalBank
  );

/**
  This function sets the row address swizzle for the specified channel.

  @param[in] MrcData - Include all MRC global data.
  @param[in] Channel - Zero based channel number.
  @param[in] Row     - Zero based logical row bit number.
  @param[in] Value   - Zero based physical row address.
**/
extern
void
MrcHalSetRowAddressSwizzle (
  IN MrcParameters *const MrcData,
  IN const UINT32  Channel,
  IN const UINT32  Row,
  IN const UINT32  Value
  );

/**
  Function used to set the subsequence configuration.

  @param[in] MrcData      - Include all MRC global data.
  @param[in] Channel      - Zero based channel number.
  @param[in] SubseqStart  - Zero based starting subsequence number.
  @param[in] SubSeqCount  - Number of SubSequence entries in the SubSeqCtl and SubSeqOffset arrays.
  @param[in] SubSeqCtl    - Specifies whether address inversion enabled for this subsequence.
  @param[in] SubSeqOffset - Specifies whether data inversion enabled for this subsequence.
**/
extern
void
MrcHalSetReutSubsequence (
  IN MrcParameters                           *const MrcData,
  IN const UINT32                             Channel,
  IN const UINT32                             SubSeqStart,
  IN const UINT32                             SubSeqCount,
  IN const MRC_HAL_SUBSEQUENCE_CONTROL_STRUCT *const SubSeqCtl,
  IN const MRC_HAL_SUBSEQUENCE_OFFSET_STRUCT  *const SubSeqOffset
  );

/**
  This function sets the reut sequence configuration.

  @param[in] MrcData   - Include all MRC global data.
  @param[in] Channel   - Zero based channel number.
  @param[in] SeqConfig - Sequence configuration.

  @retval The previous setting of the sequence configuration register.
**/
extern
UINT64
MrcHalSetReutSequenceConfig (
  IN MrcParameters                        *const MrcData,
  IN const UINT32                         Channel,
  IN const MRC_HAL_SEQUENCE_CONFIG_STRUCT *const SeqConfig
  );

/**
  This function configures the sequence base address start register by doing a read/modify/write on those input
  fields that are valid.

  @param[in] MrcData - Include all MRC global data.
  @param[in] Channel - Zero based channel number.
  @param[in] Address - Address constructed using rank, bank, row, column.
**/
extern
void
MrcHalSetReutChSeqBaseAddrStart (
  IN MrcParameters                         *const MrcData,
  IN const UINT32                          Channel,
  IN const MRC_HAL_SEQ_BASE_ADDRESS_STRUCT *const Address
  );

/**
  This function configures the sequence base address wrap register by doing a read/modify/write on those input
  fields that are valid.

  @param[in] MrcData - Include all MRC global data.
  @param[in] Channel - Zero based channel number.
  @param[in] Address - Address constructed using rank, bank, row, column.

  @retval The value written to the register.
**/
extern
void
MrcHalSetReutChSeqBaseAddrWrap (
  IN MrcParameters                         *const MrcData,
  IN const UINT32                          Channel,
  IN const MRC_HAL_SEQ_BASE_ADDRESS_STRUCT *const Address
  );

/**
  This function configures the sequence base address increment control register by doing a read/modify/write on those input
  fields that are valid.

  @param[in] MrcData - Include all MRC global data.
  @param[in] Channel - Zero based channel number.
  @param[in] Count   - Zero based number of elements in the IncCtl array.
  @param[in] IncCtl  - Array containing increment control values.
**/
extern
void
MrcHalSetReutChSeqBaseAddrIncCtl (
  IN MrcParameters                        *const MrcData,
  IN const UINT32                         Channel,
  IN const UINT32                         Count,
  IN const MRC_HAL_REUT_BASE_ADDR_INC_CTL *IncCtlPtr
  );

/**
  This function configures the sequence base address order/carry/invert control register by doing a read/modify/write on those input
  fields that are valid.

  @param[in] MrcData    - Include all MRC global data.
  @param[in] Channel    - Zero based channel number.
  @param[in] InvertRate - The base address invert rate.
  @param[in] Count      - Zero based number of elements in the Ctl array.
  @param[in] Ctl        - Array containing order/carry/invert control values.
**/
extern
void
MrcHalSetReutChSeqBaseAddrOciCtl (
  IN MrcParameters                         *const MrcData,
  IN const UINT32                          Channel,
  IN const UINT32                          InvertRate,
  IN const UINT32                          Count,
  IN const MRC_HAL_REUT_BASE_ADDR_OCI_CTL  *CtlPtr
  );

/**
  This function gets the sequence base address start rank value.

  @param[in] MrcData - Include all MRC global data.
  @param[in] Channel - Zero based channel number.

  @retval The value from the register.
**/
extern
UINT32
MrcHalGetReutChSeqBaseAddrStartRank (
  IN MrcParameters                 *const MrcData,
  IN const UINT32                  Channel
  );

/**
  This function gets the sequence base address current rank value.

  @param[in] MrcData - Include all MRC global data.
  @param[in] Channel - Zero based channel number.

  @retval The value from the register.
**/
extern
UINT32
MrcHalGetReutChSeqBaseAddrCurrentRank (
  IN MrcParameters                 *const MrcData,
  IN const UINT32                  Channel
  );

/**
  This function configures the reut channel error control.

  @param[in] MrcData                       - Include all MRC global data.
  @param[in] Channel                       - Zero based channel number.
  @param[in] StopOnNthError                - Stop on Nth error control.
  @param[in] StopOnCaAlert                 - Stop on CA alert control.
  @param[in] StopOnErrorControl            - Stop on error control.
  @param[in] SelectiveErrorEnableChunk     - Selective error enable chunk control bit mask.
  @param[in] SelectiveErrorEnableCacheline - Selective error enable cacheline control bit mask.
**/
extern
void
MrcHalSetReutChannelErrorControl (
  IN MrcParameters                                       *const MrcData,
  IN const UINT32                                        Channel,
  IN const UINT32                                        StopOnNthError,
  IN const MRC_HAL_ENUM_STOP_ON_CA_ALERT                 StopOnCaAlert,
  IN const MRC_HAL_ENUM_STOP_ON_ERROR_CONTROL            StopOnErrorControl,
  IN const MRC_HAL_ENUM_SELECTIVE_ERROR_ENABLE_CHUNK     SelectiveErrorEnableChunk,
  IN const MRC_HAL_ENUM_SELECTIVE_ERROR_ENABLE_CACHELINE SelectiveErrorEnableCacheline
  );

/**
  This function gets the reut channel stop on error control.

  @param[in] MrcData - Include all MRC global data.
  @param[in] Channel - Zero based channel number.

  @retval The value read from the register.
**/
extern
MRC_HAL_ENUM_STOP_ON_ERROR_CONTROL
MrcHalGetReutChannelStopOnErrorControl (
  IN MrcParameters *const MrcData,
  IN const UINT32  Channel
  );

/**
  Function used to set the error counter mode.

  @param[in] MrcData - Include all MRC global data.
  @param[in] Channel - Zero based channel number. Pass MRC_CHANNEL_MULTICAST to do all channels.
  @param[in] Counter - Zero based counter number. Pass MRC_BYTE_MULTICAST to do all bytes.
  @param[in] Control - Error counter mode.
  @param[in] Pointer - Extra index used to provide additional information if needed by the mode selected. This indicates which lane, nibble, byte, or chunk has been selected.  If CounterMode value is LaneErrorCounterMode then the ModeIndex value must be less than the BusWidth value from the GetSystemInfo() function.  If CounterMode is NibbleErrorCounterMode then the ModeIndex value must be less than the BusWidth/4 value from the GetSystemInfo() function.  If CounterMode is ByteErrorCounterMode then the ModeIndex value must be less than the BusWidth/8 value from the GetSystemInfo() function.  If CounterMode is ChunkErrorCounterMode then the ModeIndex value must be less than 8.
**/
extern
void
MrcHalSetChannelErrorCounterControl (
  IN MrcParameters                            *const MrcData,
  IN const UINT32                             Channel,
  IN const UINT32                             Counter,
  IN const MRC_HAL_ENUM_ERROR_COUNTER_CONTROL Control,
  IN const UINT32                             Pointer
  );

/**
  Function used to get the data error status.

  @param[in]      MrcData     - Include all MRC global data.
  @param[in]      Channel     - Zero based channel number.
  @param[in, out] ErrorStatus - Error status value. This buffer must be at least MAX_SDRAM_IN_DIMM bytes in size. The ECC byte will always be provided, even if ECC is disabled.

  @retval TRUE if the data error status indicates all bit lanes failed, otherwise FALSE. The ECC byte will not be included if ECC is disabled.
**/
extern
BOOLEAN
MrcHalGetChannelErrorStatus (
  IN     MrcParameters *const MrcData,
  IN     const UINT32  Channel,
  IN OUT UINT8         *ErrorStatus
  );

/**
  Function used to get the data chunk error status.

  @param[in] MrcData - Include all MRC global data.
  @param[in] Channel - Zero based channel number.

  @retval TRUE if the data error status indicates all bit lanes failed, otherwise FALSE.
**/
extern
UINT32
MrcHalGetChannelChunkErrorStatus (
  IN MrcParameters *const MrcData,
  IN const UINT32  Channel
  );

/**
  Function used to get the data rank error status.

  @param[in] MrcData - Include all MRC global data.
  @param[in] Channel - Zero based channel number.

  @retval TRUE if the data error status indicates all bit lanes failed, otherwise FALSE.
**/
extern
UINT32
MrcHalGetChannelRankErrorStatus (
  IN     MrcParameters *const MrcData,
  IN     const UINT32  Channel
  );

/**
  Function used to get the data byte group error status.

  @param[in] MrcData - Include all MRC global data.
  @param[in] Channel - Zero based channel number.

  @retval TRUE if the data error status indicates all bit lanes failed, otherwise FALSE.
**/
extern
UINT32
MrcHalGetChannelByteGroupErrorStatus (
  IN     MrcParameters *const MrcData,
  IN     const UINT32  Channel
  );

/**
  This function configures the reut channel sequence control.

  @param[in] MrcData          - Include all MRC global data.
  @param[in] Channel          - Zero based channel number.
  @param[in] LocalStartTest   - Start the local test.
  @param[in] LocalStopTest    - Stop the local test.
  @param[in] LocalClearErrors - Clear local errors.
**/
extern
void
MrcHalSetReutChannelSequenceControl (
  IN MrcParameters                          *const MrcData,
  IN const UINT32                           Channel,
  IN const MRC_HAL_ENUM_TEST_CONTROL        TestControl,
  IN const MRC_HAL_ENUM_CLEAR_ERROR_CONTROL LocalClearErrors
  );

/**
  This function configures the reut global sequence control.

  @param[in] MrcData            - Include all MRC global data.
  @param[in] GlobalStartTest    - Start the global test.
  @param[in] GlobalStopTest     - Stop the global test.
  @param[in] GlobalClearErrors  - Clear global errors.
  @param[in] StopTestOnAnyError - Stop test on any error.
**/
extern
void
MrcHalSetReutGlobalSequenceControl (
  IN MrcParameters                            *const MrcData,
  IN const MRC_HAL_ENUM_TEST_CONTROL          TestControl,
  IN const MRC_HAL_ENUM_CLEAR_ERROR_CONTROL   GlobalClearErrors,
  IN const MRC_HAL_ENUM_STOP_ON_ERROR_CONTROL StopTestOnAnyError
  );

/**
  Function used to get the global stop test value.

  @param[in] MrcData - Include all MRC global data.

  @retval The global stop test value.
**/
extern
MRC_HAL_ENUM_TEST_CONTROL
MrcHalGetGlobalStopTest (
  IN MrcParameters *const MrcData
  );

/**
  This function configures the scrambler.

  @param[in] MrcData         - Include all MRC global data.
  @param[in] Channel         - Zero based channel number.
  @param[in] Enable          - Enable the scrambler.
  @param[in] Key             - Scrambler key.
  @param[in] ClockGateABMode - Clock gate AB mode.
  @param[in] ClockGateCMode  - Clock gate C mode.
  @param[in] EnableDbiAB     - DBI AB control.
**/
extern
void
MrcHalSetScramblerControl (
  IN MrcParameters                            *const MrcData,
  IN const UINT32                             Channel,
  IN const MRC_HAL_ENUM_SCRAMBLER_CONTROL     Control,
  IN const UINT32                             Key,
  IN const MRC_HAL_ENUM_CLOCK_GATE_AB_CONTROL ClockGateABMode,
  IN const MRC_HAL_ENUM_CLOCK_GATE_C_CONTROL  ClockGateCMode,
  IN const MRC_HAL_ENUM_DBI_AB_CONTROL        EnableDbiAB
  );

/**
  This function gets the scrambler configuration.

  @param[in]  MrcData         - Include all MRC global data.
  @param[in]  Channel         - Zero based channel number.
  @param[out] Enable          - Enable the scrambler.
  @param[out] Key             - Scrambler key.
  @param[out] ClockGateABMode - Clock gate AB mode.
  @param[out] ClockGateCMode  - Clock gate C mode.
  @param[out] EnableDbiAB     - Enable AB DBI.
**/
extern
void
MrcHalGetScramblerControl (
  IN MrcParameters *const MrcData,
  IN const UINT32  Channel,
  OUT UINT32       *const Enable,
  OUT UINT32       *const Key,
  OUT UINT32       *const ClockGateABMode,
  OUT UINT32       *const ClockGateCMode,
  OUT UINT32       *const EnableDbiAB
  );

/**
  This function sets the self refresh configuration.

  @param[in] MrcData   - Include all MRC global data.
  @param[in] IdleTimer - Self refresh idle timer value.
  @param[in] SrEnable  - Self refresh control.
**/
extern
void
MrcHalSetSelfRefreshConfiguration (
  IN MrcParameters                           *const MrcData,
  IN const UINT32                            IdleTimer,
  IN const MRC_HAL_ENUM_SELF_REFRESH_CONTROL SrEnable
  );

/**
  This function gets the self refresh configuration.

  @param[in]  MrcData   - Include all MRC global data.
  @param[out] IdleTimer - Self refresh idle timer value.
  @param[out] SrEnable  - Self refresh control.
**/
extern
void
MrcHalGetSelfRefreshConfiguration (
  IN MrcParameters                      *const MrcData,
  OUT UINT32                            *const IdleTimer,
  OUT MRC_HAL_ENUM_SELF_REFRESH_CONTROL *const SrEnable
  );

/**
  This function sets the self refresh override configuration.

  @param[in] MrcData          - Include all MRC global data.
  @param[in] Channel          - Zero based channel number.
  @param[in] RefreshRankMask  - Refresh disable rank mask.
  @param[in] EnStartTestSync  - RefZQ start test sync control.
  @param[in] PanicRefreshOnly - Panic refresh only control.
**/
extern
void
MrcHalSetSelfRefreshOverrideConfiguration (
  IN MrcParameters                            *const MrcData,
  IN const UINT32                             Channel,
  IN const MRC_HAL_ENUM_RANK_MASK_CONTROL     RefreshRankMask,
  IN const MRC_HAL_ENUM_START_TEST_SYNC       EnStartTestSync,
  IN const MRC_HAL_ENUM_PANIC_REFRESH_CONTROL PanicRefreshOnly
  );

/**
  This function sets the ZQ calibration override configuration.

  @param[in] MrcData    - Include all MRC global data.
  @param[in] Channel    - Zero based channel number.
  @param[in] RankMask   - Rank disable bit mask. Bit 0 = Rank 0. 1 = disable the rank.
  @param[in] AlwaysDoZq - Always do ZQ control.
**/
extern
void
MrcHalSetZqCalOverrideConfiguration (
  IN MrcParameters                           *const MrcData,
  IN const UINT32                            Channel,
  IN const MRC_HAL_ENUM_RANK_MASK_CONTROL    RankMask,
  IN const MRC_HAL_ENUM_ZQ_OPERATION_CONTROL AlwaysDoZq
  );

/**
  This function sets the ODT override configuration.

  @param[in] MrcData       - Include all MRC global data.
  @param[in] Channel       - Zero based channel number.
  @param[in] RankMask      - Rank bit mask.
  @param[in] OverrideMask  - Override bit mask.
  @param[in] MprTrainDdrOn - MPR train DDR control.
**/
extern
void
MrcHalSetOdtOverrideConfiguration (
  IN MrcParameters                        *const MrcData,
  IN const UINT32                         Channel,
  IN const MRC_HAL_ENUM_RANK_MASK_CONTROL RankMask,
  IN const MRC_HAL_ENUM_RANK_MASK_CONTROL OverrideMask,
  IN const MRC_HAL_ENUM_MPR_TRAIN_CONTROL MprTrainDdrOn
  );

/**
  This function sets the CKE override configuration.

  @param[in] MrcData       - Include all MRC global data.
  @param[in] Channel       - Zero based channel number.
  @param[in] RankMask      - Rank bit mask.
  @param[in] OverrideMask  - Override bit mask.
  @param[in] StartTestSync - Start test sync control.
**/
extern
void
MrcHalSetCkeOverrideConfiguration (
  IN MrcParameters                        *const MrcData,
  IN const UINT32                         Channel,
  IN const MRC_HAL_ENUM_RANK_MASK_CONTROL RankMask,
  IN const MRC_HAL_ENUM_RANK_MASK_CONTROL OverrideMask,
  IN const MRC_HAL_ENUM_START_TEST_SYNC   StartTestSync
  );

/**
  Function used to get the current sequence state.

  @param[in] MrcData      - Include all MRC global data.
  @param[in] Channel      - Zero based channel number.
  @param[out] LoopCount   - Pointer to buffer containing current loop count.
  @param[out] SubSeqIndex - Pointer to buffer containing current subsequence index.
  @param[out] Cacheline   - Pointer to buffer containing current cacheline.
  @param[out] BaseRank    - Pointer to buffer containing current base rank.
  @param[out] BaseBank    - Pointer to buffer containing current base bank.
  @param[out] BaseRow     - Pointer to buffer containing current base row.
  @param[out] BaseCol     - Pointer to buffer containing current base column.
  @param[out] OffsetRow   - Pointer to buffer containing current offset row.
  @param[out] OffsetCol   - Pointer to buffer containing current offset column.
**/
void
MrcHalGetCurrentSubSeqStatus (
  IN  MrcParameters *const MrcData,
  IN  const UINT32         Channel,
  OUT UINT32               *LoopCount,
  OUT UINT8                *SubSeqIndex,
  OUT UINT32               *Cacheline,
  OUT UINT8                *BaseRank,
  OUT UINT8                *BaseBank,
  OUT UINT32               *BaseRow,
  OUT UINT32               *BaseCol,
  OUT UINT32               *OffsetRow,
  OUT UINT32               *OffsetCol
  );

/**
  This function sets write data buffer capture controls.

  @param[in] MrcData                   - Include all MRC global data.
  @param[in] Channel                   - Zero based channel number.
  @param[in] EnableWdbCapture          - Write data buffer capture enable.
  @param[in] WdbErrorSelCapture        - Write data buffer error select capture control.
  @param[in] WdbDataSelCapture         - Write data buffer data select capture control.
  @param[in] WdbStartingCapturePointer - Write data buffer starting capture pointer.
  @param[in] WdbEndingCapturePointer   - Write data buffer ending capture pointer.
**/
void
MrcHalRmwWdbCaptureControl (
  IN MrcParameters *const   MrcData,
  IN const UINT32           Channel,
  IN const UINT32           EnableWdbCapture,
  IN const UINT32           WdbErrorSelCapture,
  IN const UINT32           WdbDataSelCapture,
  IN const UINT32           WdbStartingCapturePointer,
  IN const UINT32           WdbEndingCapturePointer
  );

/**
  Top level function used to interact with DDRIO parameters.
    NOTE: This assumes the max register size of DDRIO Group is 32-bits.

  @param[in]      MrcData   - Pointer to global data structure.
  @param[in]      Socket    - Processor socket in the system (0-based).  Not used in Core MRC.
  @param[in]      Channel   - DDR Channel Number within the processor socket (0-based)
  @param[in]      Dimm      - DIMM Number within the DDR Channel (0-based). Ignored as Rank is rank number in the channel.
  @param[in]      Rank      - Rank number within a channel (0-based).
  @param[in]      Strobe    - Dqs data group within the rank (0-based).
  @param[in]      Bit       - Bit index within the data group (0-based).
  @param[in]      FreqIndex - Index supporting multiple operating frequencies.
  @param[in]      Level     - DDRIO level to access.
  @param[in]      Group     - DDRIO group to access.
  @param[in]      Mode      - Bit-field flags controlling Get/Set.
  @param[in,out]  Value     - Pointer to value for Get/Set to operate on.  Can be offset or absolute value based on mode.

  @retval MrcStatus
**/
MrcStatus
MrcGetSetDdrIoGroup (
  IN      MrcParameters *const  MrcData,
  IN      UINT8         const   Socket,
  IN      UINT8         const   Channel,
  IN      UINT8         const   Dimm,
  IN      UINT8         const   Rank,
  IN      UINT8         const   Strobe,
  IN      UINT8         const   Bit,
  IN      UINT8         const   FreqIndex,
  IN      GSM_LT        const   Level,
  IN      GSM_GT        const   Group,
  IN      UINT8         const   Mode,
  IN OUT  INT64         *const  Value
  );

/**
  This function handles getting the register offset for the requested parameter.
  It will determine multicast by the parameter exceeding the MAX of the
  Socket/Channel/Rank/Strobe/Bit.

  @param[in]  MrcData   - Pointer to global data.
  @param[in]  Group     - Parameter to calculate MMIO offset.
  @param[in]  Socket    - Processor socket in the system (0-based).  Not used in Core MRC.
  @param[in]  Channel   - DDR Channel Number within the processor socket (0-based).
  @param[in]  Rank      - Rank number within a channel (0-based).
  @param[in]  Strobe    - Dqs data group within the rank (0-based).
  @param[in]  Bit       - Bit index within the data group (0-based).
  @param[in]  FreqIndex - Index supporting multiple operating frequencies. (Not used in Client CPU's)
  @param[out] Offset    - Pointer to return the MMIO Offset in.

  @retval MrcStatus.
**/
MrcStatus
MrcGetDdrIoRegOffset (
  IN  MrcParameters *const  MrcData,
  IN  GSM_GT  const   Group,
  IN  UINT8   const   Socket,
  IN  UINT8   const   Channel,
  IN  UINT8   const   Rank,
  IN  UINT8   const   Strobe,
  IN  UINT8   const   Bit,
  IN  UINT8   const   FreqIndex,
  OUT UINT32  *const  Offset
  );

/**
  This function returns the register limits.

  @param[in]  MrcData   - Pointer to global data.
  @param[in]  Socket    - Processor socket in the system (0-based).  Not used in Core MRC.
  @param[in]  Channel   - DDR Channel Number within the processor socket (0-based).
  @param[in]  Dimm      - DIMM index in the channel. (0-based).
  @param[in]  Level     - DDRIO level to access.
  @param[in]  Group     - DDRIO group to access.
  @param[out] MinVal    - Return pointer for Minimum Value supported.
  @param[out] MaxVal    - Return pointer for Maximum Value supported.
  @param[out] WaitTime  - Return pointer for settle time required in microseconds.

  @retval MrcStatus
**/
MrcStatus
MrcGetDdrIoGroupLimits (
  IN  MrcParameters *const MrcData,
  IN  UINT8   const   Socket,
  IN  UINT8   const   Channel,
  IN  UINT8   const   Dimm,
  IN  GSM_LT  const   Level,
  IN  GSM_GT  const   Group,
  OUT INT64   *const  MinVal,
  OUT INT64   *const  MaxVal,
  OUT UINT32  *const  WaitTime
  );

/**
  This function generates the hash used to execute the Get/Set function.
  The hash consists of: Register Offset, BitField start bit, BitField length.

  @param[in]  MrcData   - Pointer to global data.
  @param[in]  Group     - DDRIO group to access.
  @param[in]  Socket    - Processor socket in the system (0-based).  Not used in Core MRC.
  @param[in]  Channel   - DDR Channel Number within the processor socket (0-based).
  @param[in]  Rank      - Rank number within a channel (0-based).
  @param[in]  Strobe    - Dqs data group within the rank (0-based).
  @param[in]  Bit       - Bit index within the data group (0-based).
  @param[in]  FreqIndex - Index supporting multiple operating frequencies. (Not used in Client CPU's)
  @param[out] Offset    - Pointer to return the MMIO Offset in.

  @retval MrcStatus
**/
MrcStatus
MrcGetDdrIoHash (
  IN  MrcParameters *const  MrcData,
  IN  GSM_GT  const   Group,
  IN  UINT8   const   Socket,
  IN  UINT8   const   Channel,
  IN  UINT8   const   Rank,
  IN  UINT8   const   Strobe,
  IN  UINT8   const   Bit,
  IN  UINT8   const   FreqIndex,
  OUT UINT32  *const  HashVal
  );

#ifdef MRC_DEBUG_PRINT
/**
  This function outputs the specified group values to the debug print device.

  @param[in] MrcData   - Pointer to global data.
  @param[in] Group     - DDRIO group to access.
  @param[in] Socket    - Processor socket in the system (0-based).  Not used in Core MRC.
  @param[in] Channel   - DDR Channel Number within the processor socket (0-based).
  @param[in] Rank      - Rank number within a channel (0-based).
  @param[in] Strobe    - Dqs data group within the rank (0-based).
  @param[in] Bit       - Bit index within the data group (0-based).
  @param[in] FreqIndex - Index supporting multiple operating frequencies. (Not used in Client CPU's)

  @retval MrcStatus
**/
extern
MrcStatus
MrcPrintDdrIoGroup (
  IN MrcParameters *const  MrcData,
  IN UINT8   const Socket,
  IN UINT8   const Channel,
  IN UINT8   const Rank,
  IN UINT8   const Strobe,
  IN UINT8   const Bit,
  IN UINT8   const FreqIndex,
  IN GSM_GT  const Group
  );
#endif

#pragma pack (pop)
#endif
