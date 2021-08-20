/** @file
  This file includes all the data structures that the MRC considers "global data".

 @copyright
  INTEL CONFIDENTIAL
  Copyright 1999 - 2018 Intel Corporation.

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
#ifndef _MrcGlobal_h_
#define _MrcGlobal_h_
#include "MrcInterface.h"
#include "McAddress.h"
#ifdef MRC_MINIBIOS_BUILD
#include "MrcSsaInitialize.h"
#endif
#pragma pack (push, 1)

///
/// UPM PWR and Retrain Limits
///
#define MRC_NUMBER_UPM_PWR_RETRAIN_MARGINS (11)
#define MRC_NUMBER_OPT_PARAMS_TRAIN (12)
#define MAX_RCOMP         (3)
#define MAX_RCOMP_TARGETS (5)
#define MAX_REGISTER_CACHE_ENTRIES (3 * MAX_CHANNEL * MAX_RANK_IN_CHANNEL * MAX_SDRAM_IN_DIMM)

typedef struct {
  union {
    struct {
      UINT8 Valid   : 1;  // Bits 0:0
      UINT8 Write   : 1;  // Bits 1:1
      UINT8 Size    : 1;  // Bits 2:2
      UINT8 Pending : 1;  // Bits 3:3
      UINT8         : 4;  // Bits 7:4
    } Bits;
    UINT8 Data;
  } Flags;
  UINT16 Offset;
  UINT32 Data;
} REGISTER_CACHE_OFFSET_STRUCT;

typedef enum {
  CpuCellDelay,
  CpuRon,
  CpuTxEq,
  DimmWrOdtNT,
  MbLengthTx,
  SoDimmLenTx,
  MaxTxPowerParam
} TxPowerOptParam;

typedef enum {
  CpuOdt,
  DimmRdOdtNT,
  MbLengthRx,
  SoDimmLenRx,
  MaxRxPowerParam
} RxPowerOptParam;

typedef union {
  struct {
    UINT32 Frequency :  16;
    UINT32 DdrType   :  2;
    UINT32 RttWr     :  8;
    UINT32 Spare     :  6;
  } Bits;
  UINT32 Data;
} MRC_POWER_SYS_CONFIG;

typedef struct {
  INT32 Intercept;
  INT32 FirstOrder;
  INT32 SecondOrder;
  INT32 Interactions[MaxTxPowerParam];
} MRC_POWER_COEFF;

typedef struct {
  MRC_POWER_SYS_CONFIG  Config;
  UINT32                Intercept0;
  MRC_POWER_COEFF       Coeff[MaxTxPowerParam];
} MRC_RSM_POWER_FORMULA;

typedef enum {
  RefRateLowTempOOS,  // Not safe
  RefRateFourth,      // 4x tREFI - Not safe
  RefRateHalf,        // 2x tREFI
  RefRate1x,          // tREFI
  RefRate2x,          // 1/2 tREFI
  RefRate4x,          // 1/4 tREFI
  RefRate4xDeRateAc,  // 1/4 tREFI de-rate AC timing - Not safe
  RefRateHighTempOOS  // Not safe
} LpddrRefreshRates;

typedef struct {
  UINT8  Param;
  UINT16 ParamLimit[MarginLimitMax];
} MrcUpmPwrRetrainLimits;


typedef struct {
  UINT8  Param;
  INT8   Limits[2];         // Start,Stop
  INT8   SaGvLimits[2];     // Start,Stop (low frequency point)
  INT8   MaxPerfLimits[2];  // Start,Stop (DT/Halo - MAX Performance point)
} MrcOptParamsLimits;

extern const MrcUpmPwrRetrainLimits InitialLimits[MRC_NUMBER_UPM_PWR_RETRAIN_MARGINS];

typedef union {
  MrcUpmPwrRetrainLimits *Pointer;
  UINT64                 Data;
} MrcUPRLimitPtr;

///
///*****************************************
/// Output related "global data" structures.
///*****************************************
///
/// This data structure contains all the "global data" register cache values.
/// The following are memory controller level definitions.
///
typedef struct {
//  UINT32                       CurrentSequence;
//  UINT32                       NextSequence;
  UINT16                       MaxValid;
  BOOLEAN                      Overflow;
  REGISTER_CACHE_OFFSET_STRUCT Data[MAX_REGISTER_CACHE_ENTRIES];
} MRC_REGISTER_CACHE;

/// This data structure contains all the "global data" values that are considered output by the MRC.
/// The following are SDRAM level definitions. All ranks on a rank are set to these values.
///
/* Commented out until needed, in order to save space.
typedef struct {
} MrcIntSdramOut;

///
/// This data structure contains all the "global data" values that are considered output by the MRC.
/// The following are rank level definitions. All ranks on a DIMM are set to these values.
///
typedef struct {
  MrcIntSdramOut Sdram[MAX_SDRAM_IN_DIMM];
} MrcIntRankOut;
///
/// This data structure contains all the "global data" values that are considered output by the MRC.
/// The following are DIMM level definitions. All ranks on a DIMM are set to these values.
///
typedef struct {
  MrcIntRankOut Rank[MAX_RANK_IN_DIMM]; ///< Rank specific output variables.
} MrcIntDimmOut;
*/

///
/// This data structure contains all the "global data" values that are considered output by the MRC.
/// The following are channel level definitions. All DIMMs on a memory channel are set to these values.
///
typedef struct {
  DDRDATA0CH0_CR_DDRCRDATACONTROL0_STRUCT DqControl0;                    ///< DqControl0 CR
  DDRDATA0CH0_CR_DDRCRDATACONTROL1_STRUCT DqControl1[MAX_SDRAM_IN_DIMM]; ///< DqControl1 CR
  DDRDATA0CH0_CR_DDRCRDATACONTROL2_STRUCT DqControl2[MAX_SDRAM_IN_DIMM]; ///< DqControl2 CR
  MCHBAR_CH0_CR_TC_PRE_STRUCT             MchbarTcPre;                   ///< tRP, tRAS, tRDPRE, tWRPRE values
  MCHBAR_CH0_CR_TC_ACT_STRUCT             MchbarTcAct;                   ///< tFAW, tRRD_sg, tRRD_dg values
  MCHBAR_CH0_CR_TC_ODT_STRUCT             MchbarTcOdt;                   ///< tCL, tCWL, ODT parameters
  MCHBAR_CH0_CR_TC_RDRD_STRUCT            MchbarTcRdRd;                  ///< Turnarounds: Read-to-Read
  MCHBAR_CH0_CR_TC_RDWR_STRUCT            MchbarTcRdWr;                  ///< Turnarounds: Read-to-Write
  MCHBAR_CH0_CR_TC_WRRD_STRUCT            MchbarTcWrRd;                  ///< Turnarounds: Write-to-Read
  MCHBAR_CH0_CR_TC_WRWR_STRUCT            MchbarTcWrWr;                  ///< Turnarounds: Write-to-Write
  MCHBAR_CH0_CR_SC_IO_LATENCY_STRUCT      ScIoLatency;
//  MrcIntDimmOut                           Dimm[MAX_DIMMS_IN_CHANNEL];    ///< DIMM specific output variables.
  UINT8                                   Ddr4TxDrVefRange; // 0 - Auto, 1 - Range1, 2 - Range2
} MrcIntChannelOut;

///
/// This data structure contains all the "global data" values that are considered output by the MRC.
/// The following are memory controller level definitions. All channels on a controller are set to these values.
///
typedef struct {
  DDRCOMP_CR_DDRCRCOMPCTL0_STRUCT        CompCtl0;             ///< CompCtl0 CR
  DDRCOMP_CR_DDRCRCOMPCTL1_STRUCT        CompCtl1;             ///< CompCtl1 CR
  DDRCOMP_CR_DDRCRCOMPCTL2_STRUCT        CompCtl2;             ///< CompCtl2 CR
  DDRDATA7CH1_CR_DDRCRVREFADJUST1_STRUCT VrefAdjust1;          ///< Dimm Vref register
  DDRSCRAM_CR_DDRMISCCONTROL0_STRUCT     MiscControl0;         ///< Misc control0 register
  MrcIntChannelOut                       Channel[MAX_CHANNEL]; ///< Channel specific output variables.
#ifdef SSA_FLAG
  MRC_REGISTER_CACHE                     RegisterCache;
#endif // SSA_FLAG
} MrcIntControllerOut;

///
/// This data structure contains all the "global data" values that are considered output by the MRC.
/// The following are system level definitions. All memory controllers in the system are set to these values.
///
typedef struct {
  UINT32                      Size;                        ///< The size of this structure. Must be the first entry in this structure.
  MrcUPRLimitPtr              UpmPwrRetrainLimits;         ///< Pointer to Global UPM/PWR/RETRAIN Limits on the stack the size of MRC_NUMBER_UPM_PWR_RETRAIN_MARGINS
  const MRC_RSM_POWER_FORMULA *SysTxPowerFormula;          ///< Pointer to System Tx Power Formula.
  const MRC_RSM_POWER_FORMULA *SysRxPowerFormula;          ///< Pointer to System Rx Power Formula.
  MrcSaGvPoint                SaGvPoint;                   ///< SA GV point - Low or High
  BOOLEAN                     SsaHasUsedCpcg;              ///< TRUE when SSA has executed a test using the CPCG.
  UINT32                      SsaBiosServicesPpi;          ///< BSSA services PPI
  UINT32                      PeiServices;
#ifdef SSA_FLAG
#ifdef MRC_MINIBIOS_BUILD
  SSA_BIOS_FUNCTION_RW        SsaBiosServicesBuffer;       ///< The buffer used to store the SSA function pointers.
#endif
#endif
  MrcIntControllerOut  Controller[MAX_CONTROLLERS]; ///< Memory controller specific output variables.
} MrcIntOutput;

#pragma pack (pop)
#endif
