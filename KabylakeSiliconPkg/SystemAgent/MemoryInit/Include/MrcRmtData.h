/** @file
  Copies the memory related timing and configuration information into the
  Compatible BIOS data (BDAT) table.

 @copyright
  INTEL CONFIDENTIAL
  Copyright 2010 - 2018 Intel Corporation.

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
#ifndef _MrcRmtData_h_
#define _MrcRmtData_h_

#include "MrcTypes.h"

#define VDD_1_350             1350                      ///< VDD in millivolts
#define VDD_1_500             1500                      ///< VDD in millivolts
#define PI_STEP_BASE          2048                      ///< Magic number from spec
#define PI_STEP_INTERVAL      128                       ///< tCK is split into this amount of intervals
#define PI_STEP               ((PI_STEP_BASE) / (PI_STEP_INTERVAL))
#define VREF_STEP_BASE        100                       ///< Magic number from spec
#define TX_VREF_STEP          7800                      ///< TX Vref step in microvolts
#define TX_VREF(VDD)          (((TX_VREF_STEP) * (VREF_STEP_BASE)) / (VDD)) ///< VDD passed in is in millivolts
#define RX_VREF_STEP          8000                      ///< TX Vref step in microvolts
#define RX_VREF(VDD)          (((RX_VREF_STEP) * (VREF_STEP_BASE)) / (VDD)) ///< VDD passed in is in millivolts
#define CA_VREF_STEP          8000                      ///< TX Vref step in microvolts
#define CA_VREF(VDD)          (((CA_VREF_STEP) * (VREF_STEP_BASE)) / (VDD)) ///< VDD passed in is in millivolts

#define MAX_SPD_RMT           512                       ///< The maximum amount of data, in bytes, in an SPD structure.
#define RMT_PRIMARY_VERSION   6                         ///< The BDAT structure that is currently supported.
#define RMT_SECONDARY_VERSION 0                         ///< The BDAT structure that is currently supported.
#define MAX_MODE_REGISTER     7                         ///< Number of mode registers
#define MAX_DRAM_DEVICE       9                         ///< Maximum number of memory devices
#define MAX_2D_EYE_TYPE       2                         ///< Maximum number of supported Margin 2D Eye Types
#define MAX_2D_EYE_OFFSETS    7                         ///< Number of 2D Eye Offsets

//
// Warning: Bdat4.h has its own copy of this #define
// make sure to change it in both places
//
#define MAX_SCHEMA_LIST_LENGTH (10)

#ifdef BDAT_SUPPORT
/*
  Memory Data Schema 2 GUID
  {CE3F6794-4883-492C-8DBA-2FC098447710}
*/
extern EFI_GUID gEfiMemorySchemaGuid;
/*
  Memory Data Schema 6 GUID
  {8F4E928-0F5F-46D4-8410-479FDA279DB6}
*/
extern EFI_GUID gSsaBiosResultsGuid;
/*
  RMT Results Metadata GUID
  {02CB1552-D659-4232-B51F-CAB1E11FCA87}
*/
extern EFI_GUID gRmtResultMetadataGuid;
/*
  RMT Results Columns GUID
  {0E60A1EB-331F-42A1-9DE7-453E84761154}
*/
extern EFI_GUID gRmtResultColumnsGuid;
/*
  Margin2D Results Metadata GUID
  {48265582-8E49-4AC7-AA06-E1B9A74C9716}
*/
extern EFI_GUID gMargin2DResultMetadataGuid;
/*
  Margin2D Results Columns GUID
  {91A449EC-8A4A-4736-AD71-A3F6F6D752D9}
*/
extern EFI_GUID gMargin2DResultColumnsGuid;

#endif
/*
  GUID for Schema List HOB
  This is private GUID used by MemoryInit internally.
  {3047C2AC-5E8E-4C55-A1CB-EAAD0A88861B}
*/
extern EFI_GUID gMrcSchemaListHobGuid;


#pragma pack(push, 1)

typedef struct {
  UINT8                       RxDqLeft;                 ///< Units = piStep
  UINT8                       RxDqRight;
  UINT8                       TxDqLeft;
  UINT8                       TxDqRight;
  UINT8                       RxVrefLow;                ///< Units = rxVrefStep
  UINT8                       RxVrefHigh;
  UINT8                       TxVrefLow;                ///< Units = txVrefStep
  UINT8                       TxVrefHigh;
} BDAT_DQ_MARGIN_STRUCTURE;

typedef struct {
  UINT8                       RxDqLeft;                 ///< Units = piStep
  UINT8                       RxDqRight;
  UINT8                       TxDqLeft;
  UINT8                       TxDqRight;
  UINT8                       CmdLeft;
  UINT8                       CmdRight;
  UINT8                       RecvenLeft;               ///< Units = recvenStep
  UINT8                       RecvenRight;
  UINT8                       WrLevelLeft;              ///< Units = wrLevelStep
  UINT8                       WrLevelRight;
  UINT8                       RxVrefLow;                ///< Units = rxVrefStep
  UINT8                       RxVrefHigh;
  UINT8                       TxVrefLow;                ///< Units = txVrefStep
  UINT8                       TxVrefHigh;
  UINT8                       CmdVrefLow;               ///< Units = caVrefStep
  UINT8                       CmdVrefHigh;
} BDAT_RANK_MARGIN_STRUCTURE;

typedef struct {
  UINT16                      RecEnDelay[MAX_STROBE];
  UINT16                      WlDelay[MAX_STROBE];
  UINT8                       RxDqDelay[MAX_STROBE];
  UINT8                       TxDqDelay[MAX_STROBE];
  UINT8                       ClkDelay;
  UINT8                       CtlDelay;
  UINT8                       CmdDelay[3];
  UINT8                       IoLatency;
  UINT8                       Roundtrip;
} BDAT_RANK_TRAINING_STRUCTURE;

typedef struct {
  UINT16 ModeRegister[MAX_MODE_REGISTER];                  ///< Mode register settings
} BDAT_DRAM_MRS_STRUCTURE;

typedef struct {
  UINT8                       RankEnabled;              ///< 0 = Rank disabled
  UINT8                       RankMarginEnabled;        ///< 0 = Rank margin disabled
  UINT8                       DqMarginEnabled;          ///< 0 = Dq margin disabled
  BDAT_RANK_MARGIN_STRUCTURE  RankMargin;               ///< Rank margin data
  BDAT_DQ_MARGIN_STRUCTURE    DqMargin[MAX_DQ];         ///< Array of Dq margin data per rank
  BDAT_RANK_TRAINING_STRUCTURE RankTraining;            ///< Rank training settings
  BDAT_DRAM_MRS_STRUCTURE     RankMRS[MAX_DRAM_DEVICE]; ///< Rank MRS settings
} BDAT_RANK_STRUCTURE;

typedef struct {
  UINT8                       SpdValid[MAX_SPD_RMT / (CHAR_BITS * sizeof (UINT8))]; ///< Each valid bit maps to SPD byte
  UINT8                       SpdData[MAX_SPD_RMT];     ///< Array of raw SPD data bytes
} BDAT_SPD_STRUCTURE;

typedef struct {
  UINT8                       DimmEnabled;              ///< 0 = DIMM disabled
  BDAT_RANK_STRUCTURE         RankList[MAX_RANK_IN_DIMM]; ///< Array of ranks per DIMM
  BDAT_SPD_STRUCTURE          SpdBytes;                 ///< SPD data per DIMM
} BDAT_DIMM_STRUCTURE;

typedef struct {
  UINT8                       ChannelEnabled;           ///< 0 = Channel disabled
  UINT8                       NumDimmSlot;              ///< Number of slots per channel on the board
  BDAT_DIMM_STRUCTURE         DimmList[MAX_DIMMS_IN_CHANNEL]; ///< Array of DIMMs per channel
} BDAT_CHANNEL_STRUCTURE;

typedef struct {
  UINT8                       ControllerEnabled;        ///< 0 = MC disabled
  UINT16                      ControllerDeviceId;       ///< MC device Id
  UINT8                       ControllerRevisionId;     ///< MC revision Id
  UINT16                      MemoryFrequency;          ///< Memory frequency in units of MHz / 10
                                                        ///< e.g. ddrFreq = 13333 for tCK = 1.5 ns
  UINT16                      MemoryVoltage;            ///< Memory Vdd in units of mV
                                                        ///< e.g. ddrVoltage = 1350 for Vdd = 1.35 V
  UINT8                       PiStep;                   ///< Step unit = piStep * tCK / 2048
                                                        ///< e.g. piStep = 16 for step = 11.7 ps (1/128 tCK)
  UINT16                      RxVrefStep;               ///< Step unit = rxVrefStep * Vdd / 100
                                                        ///< e.g. rxVrefStep = 520 for step = 7.02 mV
  UINT16                      TxVrefStep;               ///< Step unit = txVrefStep * Vdd / 100
  UINT16                      CaVrefStep;               ///< Step unit = caVrefStep * Vdd / 100
  UINT8                       RecvenStep;               ///< Step unit = recvenStep * tCK / 2048
  UINT8                       WrLevelStep;              ///< Step unit = wrLevelStep * tCK / 2048
  BDAT_CHANNEL_STRUCTURE      ChannelList[MAX_CHANNEL]; ///< Array of channels per memory controller
} BDAT_SOCKET_STRUCTURE;

typedef struct {
  union {
    UINT32                    Data32;                   ///< MRC version: Major.Minor.Revision.Build
    struct {
      UINT8                   Build;                    ///< MRC version: Build
      UINT8                   Revision;                 ///< MRC version: Revision
      UINT8                   Minor;                    ///< MRC version: Minor
      UINT8                   Major;                    ///< MRC version: Major
    } Version;
  }                           RefCodeRevision;          ///< Major.Minor.Revision.Build
  UINT8                       MaxController;            ///< Max controllers per system, e.g. 1
  UINT8                       MaxChannel;               ///< Max channels per memory controller, e.g. 2
  UINT8                       MaxDimm;                  ///< Max DIMM per channel, e.g. 2
  UINT8                       MaxRankDimm;              ///< Max ranks per DIMM, e.g. 2
  UINT8                       MaxStrobe;                ///< Number of Dqs used by the rank, e.g. 18
  UINT8                       MaxDq;                    ///< Number of Dq bits used by the rank, e.g. 72
  UINT32                      MarginLoopCount;          ///< Units of cache line
  BDAT_SOCKET_STRUCTURE       ControllerList[MAX_CONTROLLERS]; ///< Array of memory controllers per system
} BDAT_SYSTEM_STRUCTURE;

typedef struct {
  UINT32                      Data1;
  UINT16                      Data2;
  UINT16                      Data3;
  UINT8                       Data4[8];
} BDAT_EFI_GUID;

typedef struct {
  UINT16  HobType;
  UINT16  HobLength;
  UINT32  Reserved;
} BDAT_HOB_GENERIC_HEADER;

typedef struct {
  BDAT_HOB_GENERIC_HEADER  Header;
  BDAT_EFI_GUID            Name;
  ///
  /// Guid specific data goes here
  ///
} BDAT_HOB_GUID_TYPE;

typedef struct {
  BDAT_EFI_GUID               SchemaId;                         ///< The GUID uniquely identifies the format of the data contained within the structure.
  UINT32                      DataSize;                         ///< The total size of the memory block, including both the header as well as the schema specific data.
  UINT16                      Crc16;                            ///< Crc16 is computed in the same manner as the field in the BDAT_HEADER_STRUCTURE.
} MRC_BDAT_SCHEMA_HEADER_STRUCTURE;

typedef struct {
  MRC_BDAT_SCHEMA_HEADER_STRUCTURE SchemaHeader;                ///< The schema header.
  union {
    UINT32                    Data;                             ///< MRC version: Major.Minor.Revision.Build
    struct {
      UINT8                   Build;                            ///< MRC version: Build
      UINT8                   Revision;                         ///< MRC version: Revision
      UINT8                   Minor;                            ///< MRC version: Minor
      UINT8                   Major;                            ///< MRC version: Major
    } Version;
  }                           RefCodeRevision;                  ///< Major.Minor.Revision.Build
  UINT8                       MaxController;                    ///< Max controllers per system, e.g. 1
  UINT8                       MaxChannel;                       ///< Max channels per memory controller, e.g. 2
  UINT8                       MaxDimm;                          ///< Max DIMM per channel, e.g. 2
  UINT8                       MaxRankDimm;                      ///< Max ranks per DIMM, e.g. 2
  UINT8                       MaxStrobe;                        ///< Number of Dqs used by the rank, e.g. 18
  UINT8                       MaxDq;                            ///< Number of Dq bits used by the rank, e.g. 72
  UINT32                      MarginLoopCount;                  ///< Units of cache line
  BDAT_SOCKET_STRUCTURE       ControllerList[MAX_CONTROLLERS];  ///< Array of memory controllers per system
} BDAT_MEMORY_DATA_SCHEMA_2_RMT_STRUCTURE;

typedef struct {
  UINT32  Revision;
  BOOLEAN TransferMode;
  struct {
    VOID     *MetadataStart;
    UINT32   MetadataSize;
    EFI_GUID MetadataType;
  } MdBlock;
  struct {
    VOID     *ResultStart;
    EFI_GUID ResultType;
    UINT32   ResultElementSize;
    INT32    ResultCapacity;
    INT32    ResultElementCount;
  } RsBlock;
} RESULTS_DATA_HDR;

typedef enum {
  DisableScrambler = 0,
  EnableScrambler = 1,
  DontTouchScrambler = 2,
  SCRAMBLER_OVERRIDE_MODE_DELIM = MRC_INT32_MAX
} SCRAMBLER_OVERRIDE_MODE;

typedef struct _RMT_RESULT_METADATA {
  BOOLEAN EnableCtlAllMargin;
  UINT16 SinglesBurstLength;
  UINT32 SinglesLoopCount;
  UINT16 TurnaroundsBurstLength;
  UINT32 TurnaroundsLoopCount;
  SCRAMBLER_OVERRIDE_MODE ScramblerOverrideMode;
  UINT8 PiStepUnit[2];
  UINT16 RxVrefStepUnit[2];
  UINT16 TxVrefStepUnit[2][2];
  UINT16 CmdVrefStepUnit[2][2];
  UINT8 MajorVer;
  UINT8 MinorVer;
  UINT8 RevVer;
  UINT32 BuildVer;
  UINT16 ResultEleCount;
} RMT_RESULT_METADATA;

typedef enum {
  RankResultType0 = 0,
  RankResultType1 = 1,
  RankResultType2 = 2,
  RankResultType3 = 3,
  ByteResultType = 4,
  LaneResultType = 5,
  TurnaroundResultType = 6,
  ParamLimits0ResultType = 7,
  ParamLimits1ResultType = 8,
  ParamLimits2ResultType = 9,
  ParamLimits3ResultType = 10,
  ResultTypeMax = 31,
  RMT_RESULT_TYPE_DELIM = MRC_INT32_MAX
} RMT_RESULT_TYPE;

typedef struct _RMT_RESULT_ROW_HEADER {
  UINT32 ResultType : 5;
  UINT32 Socket : 3;
  UINT32 Controller : 2;
  UINT32 Channel : 3;
  UINT32 DimmA : 1;
  UINT32 RankA : 3;
  UINT32 DimmB : 1;
  UINT32 RankB : 3;
  UINT32 Lane : 8;
  UINT32 IoLevel : 1;
  UINT32 Reserved : 2;
} RMT_RESULT_ROW_HEADER;

typedef struct _RMT_RESULT_COLUMNS {
  RMT_RESULT_ROW_HEADER Header;
  UINT8 Margin[4][2];
} RMT_RESULT_COLUMNS;

typedef struct _MARGIN_2D_RESULT_METADATA {
  UINT16 BurstLength;
  UINT32 LoopCount;
  UINT8 MajorVer;
  UINT8 MinorVer;
  UINT8 RevVer;
  UINT32 BuildVer;
  UINT16 ResultEleCount;
} MARGIN_2D_RESULT_METADATA;

typedef enum _MARGIN_2D_EYE_TYPE{
  RxDqsRxVrefEyeType = 0,
  TxDqTxVrefEyeType = 1,
  //CmdCmdVrefEyeType = 2,
  MARGIN_2D_EYE_TYPE_DELIM = MRC_INT32_MAX
} MARGIN_2D_EYE_TYPE;

typedef enum _MARGIN_PARAM_TYPE {
  TimingMarginParamType = 0,
  VotageMarginParamType = 1,
  MARGIN_PARAM_TYPE_DELIM = MRC_INT32_MAX
} MARGIN_PARAM_TYPE;

typedef struct _MARGIN_2D_RESULT_COLUMNS {
  UINT8 Controller;
  UINT8 Channel;
  UINT8 Dimm;
  UINT8 Rank;
  UINT8 Lane;
  UINT8 EyeType;
  UINT8 OuterMarginParamType;
  INT16 OuterOffset;
  UINT8 LeftMargin;
  UINT8 RightMargin;
} MARGIN_2D_RESULT_COLUMNS;

typedef struct _BASE_RMT_RESULT {
  RESULTS_DATA_HDR              ResultsHeader;
  RMT_RESULT_METADATA           Metadata;
  RMT_RESULT_COLUMNS            Rows[1];
} BDAT_SCHEMA_6B_BASE_RMT_RESULT;

typedef struct _BASE_MARGIN_2D_RESULT {
  RESULTS_DATA_HDR            ResultsHeader;
  MARGIN_2D_RESULT_METADATA   Metadata;
  MARGIN_2D_RESULT_COLUMNS    Rows[1];
} BDAT_MEMORY_DATA_SCHEMA_6B_MARGIN_2D_STRUCTURE;

typedef struct _BASE_COLUMN_RESULT {
  RESULTS_DATA_HDR              ResultsHeader;
  RMT_RESULT_METADATA           Metadata;
  RMT_RESULT_COLUMNS            Rows[1];
} BDAT_MEMORY_DATA_SCHEMA_6B_RMT_STRUCTURE;

typedef enum {
  RankMarginToolType = 0,
  RankMarginToolPerBitType = 1,
  Margin2DType = 2,
  MRC_BDAT_SCHEMA_TYPE_DELIMITER = MRC_INT32_MAX
} MRC_BDAT_SCHEMA_TYPE;

typedef enum {
  MrcBdatSchema2 = 0,
  MrcBdatSchema6B = 1,
  MRC_BDAT_SCHEMA_VERSION_DELIMITER = MRC_INT32_MAX
} MRC_BDAT_SCHEMA_VERSION;

typedef struct {
  MRC_BDAT_SCHEMA_HEADER_STRUCTURE SchemaHeader;                ///< The schema header.
  union {
    BDAT_MEMORY_DATA_SCHEMA_2_RMT_STRUCTURE          RmtSchema2;
    BDAT_MEMORY_DATA_SCHEMA_6B_RMT_STRUCTURE         RmtSchema6B;
    BDAT_MEMORY_DATA_SCHEMA_6B_MARGIN_2D_STRUCTURE   Margin2DSchema6B;
  } Schema;
} BDAT_MEMORY_DATA_STRUCTURE;

typedef struct {
  BDAT_HOB_GUID_TYPE          HobGuidType;
  BDAT_MEMORY_DATA_STRUCTURE  MemorySchema;
} BDAT_MEMORY_DATA_HOB;

#pragma pack (pop)

typedef struct {
  BDAT_HOB_GUID_TYPE          HobGuidType;
  UINT16                      SchemaHobCount;
  UINT16                      Reserved;
  BDAT_EFI_GUID               SchemaHobGuids[MAX_SCHEMA_LIST_LENGTH];
} MRC_BDAT_SCHEMA_LIST_HOB;

#endif //_MrcRmtData_h_
