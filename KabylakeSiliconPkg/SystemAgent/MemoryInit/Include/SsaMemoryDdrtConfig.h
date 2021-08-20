/** @file
  This file contains the definition of the BIOS-SSA DDR-T Memory Configuration API.

  NOTE: This file is only intended to be included from MrcSsaServices.h.  It
  cannot be included separately.

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
#ifndef _SsaMemoryDdrtConfig_h_
#define _SsaMemoryDdrtConfig_h_

#ifdef SSA_FLAG

#pragma pack (push, 1)

///
/// Falcon Valley training mode.
///
typedef enum {
  // these are bit mask values
  TrainingModeEnable     = 0x01,
  EarlyCmdCkTraining     = 0x02,
  AdvCmdCkTraining       = 0x04,
  EridTraining           = 0x08,
  DqSwizzleTraining      = 0x10,
  RecenDqDqsMprTraining  = 0x20,
  BufferBacksideTraining = 0x40,
  ResetTrainingMode      = 0x1 << 31,
  // don't modify above values; add new entries below in bit mask format
  FnvTrainingModeDelim = INT32_MAX        ///< This value ensures the enum size is consistent on both sides of the PPI.
} FNV_TRAINING_MODE;

typedef enum {
  EridSignal0,
  EridSignal1,
  EridSignalMax,
  EridSignalDelim = INT32_MAX
} ERID_SIGNAL;

typedef enum {
  EridLfsrMode,
  EridBufferMode,
  EridPatternModeMax,
  EridPatternDelim = INT32_MAX
} ERID_PATTERN_MODE;

/**
  Function used to set the bit validation mask of Early Read ID.

  @param[in, out] This       - Interface pointer that implements the particular SSA_BIOS_SERVICES_PPI instance.
  @param[in]      Socket     - Zero based CPU socket number.
  @param[in]      Controller - Zero based controller number.
  @param[in]      Channel    - Zero based channel number.
  @param[in]      EridMask   - Early Read ID bitmask.

  @retval Nothing.
**/
typedef
VOID
(EFIAPI * SET_ERID_VALIDATION_MASK) (
  IN OUT SSA_BIOS_SERVICES_PPI *This,
  IN UINT8                     Socket,
  IN UINT8                     Controller,
  IN UINT8                     Channel,
  IN UINT8                     EridMask
  );

/**
  Function used to get the Early Read ID bit error status.

  @param[in, out] This       - Interface pointer that implements the particular SSA_BIOS_SERVICES_PPI instance.
  @param[in]      Socket     - Zero based CPU socket number.
  @param[in]      Controller - Zero based controller number.
  @param[in]      Channel    - Zero based channel number.
  @param[out]     Status     - Pointer to where the Early Read ID bit error status will be stored.  Bit value 1 = at least one error occurred; bit value 0 = no errors occurred.  Bit position 3: CKP Early Read ID (even).  Bit position 2: CKP Early Read ID (odd).  Bit position 1: CKN Early Read ID (even).  Bit position 0: CKN Early Read ID (odd).
  @param[out]     Count      - Pointer to where the error counter value will be stored.

  @retval Nothing.
**/
typedef
VOID
(EFIAPI * GET_ERID_ERROR_STATUS) (
  IN OUT SSA_BIOS_SERVICES_PPI *This,
  IN UINT8                     Socket,
  IN UINT8                     Controller,
  IN UINT8                     Channel,
  OUT UINT8                    *Status,
  OUT UINT8                    *Count
  );

/**
  Function used to clear the error status and count value of Early Read ID signals.

  @param[in, out] This       - Interface pointer that implements the particular SSA_BIOS_SERVICES_PPI instance.
  @param[in]      Socket     - Zero based CPU socket number.
  @param[in]      Controller - Zero based controller number.
  @param[in]      Channel    - Zero based channel number.

  @retval Nothing.
**/
typedef
VOID
(EFIAPI * CLEAR_ERID_ERROR_STATUS) (
  IN OUT SSA_BIOS_SERVICES_PPI *This,
  IN UINT8                     Socket,
  IN UINT8                     Controller,
  IN UINT8                     Channel
  );

/**
  Function used to set up the Early Read ID pattern generator.

  @param[in, out] This          - Interface pointer that implements the particular SSA_BIOS_SERVICES_PPI instance.
  @param[in]      Socket        - Zero based CPU socket number.
  @param[in]      Controller    - Zero based controller number.
  @param[in]      Channel       - Zero based channel number.
  @param[in]      Signal        - Zero based ERID signal number.
  @param[in]      PatternMode   - ERID pattern mode, LFSR or pattern buffer modes.
  @param[in]      EnableReload  - Enable or disable seed reload for the Early Read ID.
  @param[in]      EnableReset   - Enable or disable seed reset for the Early Read ID.
  @param[in]      Seed          - Seed value for Early Read ID.

  @retval Nothing.
**/
typedef
VOID
(EFIAPI * SET_ERID_PATTERN) (
  IN OUT SSA_BIOS_SERVICES_PPI *This,
  IN UINT8                     Socket,
  IN UINT8                     Controller,
  IN UINT8                     Channel,
  IN ERID_SIGNAL               Signal,
  IN ERID_PATTERN_MODE         PatternMode,
  IN BOOLEAN                   EnableReload,
  IN BOOLEAN                   EnableReset,
  IN UINT32                    Seed
  );

/**
  Function used to set the Early Read ID coarse training configuration.

  @param[in, out] This            - Interface pointer that implements the particular SSA_BIOS_SERVICES_PPI instance.
  @param[in]      Socket          - Zero based CPU socket number.
  @param[in]      Controller      - Zero based controller number.
  @param[in]      Channel         - Zero based channel number.
  @param[in]      EnableTraining  - Specifies whether Early Read ID coarse training mode is enabled.

  @retval Nothing.
**/
typedef
VOID
(EFIAPI * SET_ERID_TRAINING_CONFIG) (
  IN OUT SSA_BIOS_SERVICES_PPI *This,
  IN UINT8                     Socket,
  IN UINT8                     Controller,
  IN UINT8                     Channel,
  IN BOOLEAN                   EnableTraining
  );

/**
  Function used to set the training mode of the controller chip of the AEP DIMM (FalconValley).

  @param[in, out] This             - Interface pointer that implements the particular SSA_BIOS_SERVICES_PPI instance.
  @param[in]      Socket           - Zero based CPU socket number.
  @param[in]      Controller       - Zero based controller number.
  @param[in]      Channel          - Zero based channel number.
  @param[in]      Dimm             - Zero based DIMM number.
  @param[in]      TrainingModeMask -

  @retval Nothing.
**/
typedef
VOID
(EFIAPI * SET_AEP_DIMM_TRAINING_MODE) (
  IN OUT SSA_BIOS_SERVICES_PPI *This,
  IN UINT8                     Socket,
  IN UINT8                     Controller,
  IN UINT8                     Channel,
  IN UINT8                     Dimm,
  IN UINT32                    TrainingModeMask
  );

/**
  BIOS-SSA DDR-T Memory Configuration
**/
typedef struct _SSA_MEMORY_DDRT_CONFIG {
  UINT32                     Revision;               ///< Incremented when a backwards compatible binary change is made to the PPI.
  SET_ERID_VALIDATION_MASK   SetEridValidationMask;  ///< Function used to set the bit validation mask of Early Read ID.
  GET_ERID_ERROR_STATUS      GetEridErrorStatus;     ///< Function used to get the Early Read ID bit error status.
  CLEAR_ERID_ERROR_STATUS    ClearEridErrorStatus;   ///< Function used to clear the error status and count value of Early Read ID signals.
  SET_ERID_PATTERN           SetEridPattern;         ///< Function used to set up the Early Read ID pattern generator.
  SET_ERID_TRAINING_CONFIG   SetEridTrainingConfig;  ///< Function used to set the Early Read ID coarse training configuration.
  SET_AEP_DIMM_TRAINING_MODE SetAepDimmTrainingMode; ///< Function used to set the training mode of the controller chip of the AEP DIMM (FalconValley).
} SSA_MEMORY_DDRT_CONFIG;

#pragma pack (pop)
#else
// Future placeholder: BSSA code intentionally left out for now
#endif //SSA_FLAG

#endif // _SsaMemoryDdrtConfig_h_
