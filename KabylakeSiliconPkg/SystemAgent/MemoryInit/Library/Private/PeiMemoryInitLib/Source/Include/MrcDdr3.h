/** @file
  This file includes all the DDR3 specific characteristic definitions.

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
#ifndef _MrcDdr3_h_
#define _MrcDdr3_h_

#include "MrcTypes.h"
#include "MrcApi.h"
#include "McAddress.h"
#include "MrcCommon.h"
#include "MrcDdr3Registers.h"
#include "MrcDdr4Registers.h"
#include "MrcIoControl.h"
#include "MrcPowerModes.h"
#include "MrcRefreshConfiguration.h"
#include "MrcMemoryScrub.h"
#include "MrcReset.h"
#include "MrcReadReceiveEnable.h"

#pragma pack (push, 1)
///
/// in write leveling mode Rtt_Nom = Rtt_Wr
///
typedef struct {
  UINT8  RttWr;  ///< Wa - Write ODT on active rank
  UINT8  RttNom; ///< Wp - ODT on one of the ranks on passive DIMM during Write operation
} TOdtValue;

typedef struct {
  UINT8  RttWr;   ///< Wa - Write ODT on active rank
  UINT8  RttNom;  ///< Wp - ODT on one of the ranks on passive DIMM during Write operation
  UINT8  RttPark;
} TOdtValueDdr4;

typedef enum {
  oi1DPC1R  = 0,
  oi1DPC2R,
  oi2DPC1R1R,
  oi2DPC1R2R,
  oi2DPC2R1R,
  oi2DPC2R2R,
  oiNotValid
} TOdtIndex;

typedef enum {
  ODIC_RZQ_6,
  ODIC_RZQ_7,
  ODIC_RSVD_0,
  ODIC_RSVD_1
} TOutputDriverImpedanceControl;

typedef enum {
  DDR4_ODIC_34,     // 0 - RZQ/7 = 34 Ohm
  DDR4_ODIC_48,     // 1 - RZQ/5 = 48 Ohm
  DDR4_ODIC_RSVD_0, // 2 - Reserved
  DDR4_ODIC_RSVD_1  // 3 - Reserved
} OutputDriverImpedanceControlDdr4;

///
/// ZQ Calibration types
///
typedef enum {
  MRC_ZQ_INIT,  ///< DDR3: ZQCL with tZQinit, LPDDR3: ZQ Init  with tZQinit
  MRC_ZQ_LONG,  ///< DDR3: ZQCL with tZQoper, LPDDR3: ZQ Long  with tZQCL
  MRC_ZQ_SHORT, ///< DDR3: ZQCS with tZQCS,   LPDDR3: ZQ Short with tZQCS
  MRC_ZQ_RESET  ///< DDR3: not used,          LPDDR3: ZQ Reset with tZQreset
} MrcZqType;

#ifndef tZQinit
#define tZQinit                     (512)   ///< define the tZQinit as define in jedec spec
#endif

#ifndef tWLMRD
#define tWLMRD                      (40)    ///< First DQS/DQS# rising edge after write leveling mode is programmed.
#endif

#ifndef tWLOE
#define tWLOE                       (40)    ///< Write leveling output error the time is 2ns ~ 2 nCK
#endif

#ifndef tZQCS_TIME
#define tZQCS_TIME                  (64)    ///< jedec timing
#endif

#define tVREFDQ_MIN                 (3 * HPET_MIN) ///< DDR4: tVREFDQ is 150 ns

#define MRC_DDR3_SDRAM_TYPE_NUMBER  (0x0B)  ///< use to know the DDR type that data came from Jedec SPD byte 2
#define MRC_DDR4_SDRAM_TYPE_NUMBER  (0x0C)  ///< use to know the DDR type that data came from Jedec SPD byte 2
#define MRC_UDIMM_TYPE_NUMBER       (0x02)  ///< use to know if the DIMM type is UDIMM define in Jedec SPD byte 3
#define MRC_SOIMM_TYPE_NUMBER       (0x03)  ///< use to know if the DIMM type is SO-DIMM define in Jedec SPD byte 3
#define MRC_SDRAM_DEVICE_WIDTH_8    (0x1)   ///< use to know if the DDRAM is 8 bits width
#define MRC_SDRAM_DEVICE_WIDTH_16   (0x2)   ///< use to know if the DDRAM is 16 bits width
#define MRC_PRIMARY_BUS_WIDTH_64    (0x3)   ///< use to know if the DIMM primary bus width is not 64
#define MRC_CL_MAX_OFFSET           (0xF)   ///< in the spd data include cl from bit 0 to bit 15 each bit represent different support CL
#define MRC_CL_IN_NANO_SEC          (20)    ///< define the nax CL value in nano second

#if (SUPPORT_DDR4 == SUPPORT)
#define tCCD_L_1333_AND_LOWER       (4)
#define tCCD_L_1867                 (5)
#define tCCD_L_2400                 (6)
#define tCCD_L_ABOVE_2400           (7)
#endif // SUPPORT_DDR4

/**
  this function reverses MA and BA bits for Rank1

  @param[in] MrcData         - include all the MRC data
  @param[in] Dimm            - current DIMM
  @param[in] BA              - MRS command to be sent
  @param[in] MA              - Value to be sent

  @retval Proper MA and BA BITS.
**/
UINT32
MrcMirror (
  IN MrcParameters *const MrcData,
  IN MrcDimmOut      *Dimm,
  IN UINT8           BA,
  IN UINT16          MA
  );

/**
  this function writes to CADB

  @param[in] MrcData         - include all the MRC data
  @param[in] Channel         - Channel to send command to
  @param[in] RankMask        - Rank mask for which command will be sent to.
  @param[in] CMD             - 0: MRS, 1: REF, 2: PRE, 3: ACT, 4: WR, 5: RD, 6: ZQ, 7: NOP
  @param[in] BA              - MRS command to be sent
  @param[in] MA              - Value to be sent
  @param[in] Delay           - Delay in Dclocks

  @retval MrcStatus
**/
extern
MrcStatus
MrcWriteCADBCmd (
  IN MrcParameters *const MrcData,
  IN const UINT8          Channel,
  IN const UINT8          RankMask,
  IN const UINT8          CMD,
  IN const UINT8          BA,
  IN const UINT16 *const  MA,
  IN const UINT8          Delay
  );

/**
  This function sends the proper MRS command for specific ranks as indicated by RankMask

  @param[in] MrcData         - include all the MRC data
  @param[in] Channel         - Channel to send command to
  @param[in] RankMask        - Rank mask for which command will be sent to
  @param[in] MR              - MRS command to be sent
  @param[in] DimmValue       - Dimm Values to be sent

  @retval MrcStatus
**/
extern
MrcStatus
MrcWriteMRSAll (
  IN MrcParameters *const MrcData,
  IN const UINT8          Channel,
  IN const UINT8          RankMask,
  IN const UINT8          MR,
  IN const UINT16 *const  DimmValue
  );

/**
  This function sends the proper MRS command for specific ranks as indicated by RankMask

  @param[in] MrcData         - Include all the MRC data
  @param[in] Channel         - Channel to send command to
  @param[in] RankMask        - Rank mask for which command will be sent to
  @param[in] MR              - MRS command to be sent
  @param[in] Value           - Value to be sent

  @retval MrcStatus
**/
extern
MrcStatus
MrcWriteMRS (
  IN MrcParameters *const MrcData,
  IN const UINT8          Channel,
  IN UINT8                RankMask,
  IN const UINT8          MR,
  IN const UINT16         Value
  );

/**
  Issue ZQ calibration command on all ranks.
  When done, wait appropriate delay depending on the ZQ type.

  @param[in] MrcData         - include all the MRC data
  @param[in] chBitMask       - Channel bit mask to be sent to.
  @param[in] ZqType          - Type of ZQ Calibration: see MrcZqType enum

  @retval MrcStatus - mrcSuccess if passes, otherwise an error status
**/
extern
MrcStatus
MrcIssueZQ (
  IN MrcParameters *const MrcData,
  IN const UINT8          chBitMask,
  IN const MrcZqType      ZqType
  );

/**
  This function writes the MR2 register for all the ranks and channels

  @param[in, out] MrcData    - general data
  @param[in]      Pasr       - Partial array self refresh bit A0-A2

  @retval MrcStatus - mrcSuccess if passes, otherwise an error status
**/
extern
MrcStatus
MrcSetMR2 (
  IN OUT MrcParameters *const MrcData,
  IN     const UINT8          Pasr
  );

/**
  This function writes the MR3 register for all the ranks and channels

  @param[in] MrcData         - include all the MRC data
  @param[in] MPRLoc          - MPR Location bit A0-A1
  @param[in] Mpr             - MPR bit A2

  @retval MrcStatus - mrcSuccess if passes, otherwise an error status
**/
extern
MrcStatus
MrcSetMR3 (
  IN MrcParameters *const MrcData,
  IN const UINT8          MPRLoc,
  IN const UINT8          Mpr
  )
;

/**
  This function writes the MR1 register for all the ranks and channels

  @param[in, out] MrcData         - include all the MRC data
  @param[in]      DLLEnable       - DLL enable bit A0
  @param[in]      Odic            - Output driver impedance control A5, A1
  @param[in]      AdditiveLatency - Additive latency bit A3-A4
  @param[in]      WlEnable        - Write leveling enable bit A7
  @param[in]      Tdqs            - TDQS enable bit A11
  @param[in]      Qoff            - Qoff bit A12

  @retval MrcStatus - mrcSuccess if passes, otherwise an error status
**/
extern
MrcStatus
MrcSetMR1 (
  IN OUT MrcParameters *const MrcData,
  IN     const UINT8          DLLEnable,
  IN     const UINT8          Odic,
  IN     const UINT8          AdditiveLatency,
  IN     const UINT8          WlEnable,
  IN     const UINT8          Tdqs,
  IN     const UINT8          Qoff
  );

/**
  This function writes the MR0 register for all the ranks

  @param[in, out] MrcData         - include all the MRC data
  @param[in]      CommandControl  - include the command control params
  @param[in]      BurstLength     - Burst length bit A0-A1
  @param[in]      ReadBurstType   - Read burst type bit A3
  @param[in]      TestMode        - Test mode type bit A7
  @param[in]      DllReset        - DLL reset bit A8

  @retval MrcStatus - mrcSuccess if passes, otherwise an error status
**/
extern
MrcStatus
MrcSetMR0 (
  IN OUT MrcParameters *const MrcData,
  IN     const UINT8          Bl,
  IN     const UINT8          Rbt,
  IN     const UINT8          Tm,
  IN     const UINT8          Dll
  );

/**
  Return the ODT table index for the given Channel / DIMM.

  @param[in] MrcData         - Include all the mrc global data.
  @param[in] Channel         - Channel to work on.
  @param[in] Dimm            - DIMM to work on.

  @retval Pointer to the relevant ODT structure - (TOdtValue *) or (TOdtValueDdr4 *)
**/
extern
void *
GetOdtTableIndex (
  IN MrcParameters *const MrcData,
  IN const UINT8          Channel,
  IN const UINT8          Dimm
  );

/**
  This funtion takes the MR1 register value and updates the odt value
 inside the register.

  @param[in] MrcData          - Include all the MRC general data.
  @param[in] OdtValue         - Selected odt index.
  @param[in] Ddr3ModeRegister - Register to update.

  @retval Ddr3ModeRegister  - Updated register
**/
extern
DDR3_MODE_REGISTER_1_STRUCT
UpdateRttNomValue (
  IN MrcParameters *const        MrcData,
  IN const UINT8                 OdtValue,
  IN DDR3_MODE_REGISTER_1_STRUCT Register
  );

/**
  This function updates the Rtt value in the MR2 value passed in.

  @param[in] MrcData          - Include all the MRC general data.
  @param[in] OdtValue         - Selected odt index.
  @param[in] Ddr3ModeRegister - Register to update.

  @retval Ddr3ModeRegister - Updated MR2 register
**/
extern
DDR3_MODE_REGISTER_2_STRUCT
UpdateRttWrValue (
  IN MrcParameters *const        MrcData,
  IN const UINT8                 OdtValue,
  IN DDR3_MODE_REGISTER_2_STRUCT Ddr3ModeRegister
  );

/**
  This function selects the ODT table according to the board type.

  @param[in] MrcData   - Include all the MRC general data.
  @param[in] Dimm      - Selected DIMM.
  @param[in] OdtIndex  - Selected ODT index.

  @retval TOdtValue * - Pointer to the relevant table or NULL if the table was not found.
**/
extern
TOdtValue *
SelectTable (
  IN MrcParameters *const MrcData,
  IN const UINT8          Dimm,
  IN const TOdtIndex      OdtIndex
  );

/**
  Issue LPDDR MRW (Mode Register Write) command using MRH (Mode Register Handler).

  @param[in] MrcData - Include all MRC global data.
  @param[in] Channel - the channel to work on
  @param[in] Rank    - the rank to work on
  @param[in] Address - MRW address
  @param[in] Data    - MRW Data
  @param[in] InitMrw - when TRUE, command is stretched (used before CA training is done)
  @param[in] ChipSelect2N - when TRUE, use 2N stretch mode for CS (used before CA training is done)
  @param[in] DebugPrint - when TRUE, will print debugging information

  @retval mrcSuccess    - MRW was sent successfully
  @retval mrcDeviceBusy - timed out waiting for MRH
**/
MrcStatus
MrcIssueMrw (
  IN MrcParameters *const MrcData,
  IN UINT32               Channel,
  IN UINT32               Rank,
  IN UINT32               Address,
  IN UINT32               Data,
  IN BOOLEAN              InitMrw,
  IN BOOLEAN              ChipSelect2N,
  IN BOOLEAN              DebugPrint
  );

/**
  Issue LPDDR MRR (Mode Register Read) command using MRH (Mode Register Handler).
  Use DQ mapping array to deswizzle the MR data.

  @param[in]  MrcData - Include all MRC global data.
  @param[in]  Channel - the channel to work on
  @param[in]  Rank    - the rank to work on
  @param[in]  Address - MRR address
  @param[out] Data    - MRR Data array per SDRAM device

  @retval mrcSuccess    - MRR was executed successfully
  @retval mrcDeviceBusy - timed out waiting for MRH
**/
extern
MrcStatus
MrcIssueMrr (
  IN MrcParameters *const MrcData,
  IN UINT32               Channel,
  IN UINT32               Rank,
  IN UINT32               Address,
  OUT UINT8               Data[4]
  );

/**
  Use MRS Burst FSM to program all relevant MR registers in one quick operation.
  Can only be used on ULT/ULX (up to 2 ranks, no ECC)

  @param[in]  MrcData - Include all MRC global data.

  @retval mrcSuccess    - MRS FSM was executed successfully
  @retval mrcDeviceBusy - timed out waiting for MRH or MRS FSM
**/
MrcStatus
MrcProgramMrsFsm (
  IN MrcParameters *const MrcData
  );

/**
  Issue LPDDR PRECHARGE ALL command using CADB.

  @param[in]  MrcData   - Include all MRC global data.
  @param[in]  Channel   - The channel to work on
  @param[in]  RankMask  - The rank(s) to work on

**/
void
MrcIssuePrechargeAll (
  IN MrcParameters *const MrcData,
  IN const UINT8          Channel,
  IN const UINT8          RankMask
  );


#if (SUPPORT_DDR4 == SUPPORT)
/**
  This function writes the MR6 register for all the ranks and channels

  @param[in] MrcData         - include all the MRC data
  @param[in] VrefDQValue     - VrefDQ Training Value bit A0-A5
  @param[in] VrefDQRange     - VrefDQ Training Range bit A6
  @param[in] VrefDQEnable    - VrefDQ Training Enable bit A7
  @param[in] TccdL           - tCCD_L bit A10-A12
  @param[in] Restore         - 1 = Restore/ 0 = No Restore

  @retval MrcStatus - mrcSuccess if passes, otherwise an error status

**/
MrcStatus
MrcSetMR6_DDR4 (
  IN MrcParameters *const MrcData,
  IN const UINT8          VrefDQValue,
  IN const UINT8          VrefDQRange,
  IN const UINT8          VrefDQEnable,
  IN const UINT8          TccdL,
  IN const BOOLEAN        Restore
  );

/**
  This function writes the MR5 register for all the ranks and channels

  @param[in] MrcData         - include all the MRC data
  @param[in] CaParityLat     - C/A Parity Latency Mode bit A0-A2
  @param[in] CRCErrClr       - CRC Error Clear bit A3
  @param[in] CaParityErrSts  - C/A Parity Error Status bit A4
  @param[in] OdtBufferPD     - ODT Input Buffer for Power Down bit A5
  @param[in] CaParityPErr    - CA parity Persistent Error bit A9
  @param[in] DataMask        - Data Mask bit A10
  @param[in] WriteDbi        - Write DBI bit A11
  @param[in] ReadDbi         - Read DBI bit A12

  @retval MrcStatus - mrcSuccess if passes, otherwise an error status

**/
MrcStatus
MrcSetMR5_DDR4 (
  IN MrcParameters *const MrcData,
  IN const UINT8          CaParityLat,
  IN const UINT8          CRCErrClr,
  IN const UINT8          CaParityErrSts,
  IN const UINT8          OdtBufferPD,
  IN const UINT8          CaParityPErr,
  IN const UINT8          DataMask,
  IN const UINT8          WriteDbi,
  IN const UINT8          ReadDbi
  );

/**
  This function writes the MR4 register for all the ranks and channels

  @param[in] MrcData         - include all the MRC data
  @param[in] MaxPDMode       - Maximum Power Down Mode bit A1
  @param[in] TempRange       - Temperature Controlled Refresh Range bit A2
  @param[in] TempMode        - Temperature Controlled Refresh Mode bit A3
  @param[in] IntVref         - Internal Vref Monitor bit A4
  @param[in] CS2CALatency    - CS to CMD/ADDR Latency Mode (cycles) bit A6-A8
  @param[in] SelfRefAbort    - Self Refresh Abort bit A9
  @param[in] RdPreaMode      - Read Preamble Training Mode bit A10
  @param[in] RdPrea          - Read Preamble bit A11
  @param[in] WrPrea          - Write Preamble bit A12

  @retval MrcStatus - mrcSuccess if passes, otherwise an error status

**/
MrcStatus
MrcSetMR4_DDR4 (
  IN MrcParameters *const MrcData,
  IN const UINT8          MaxPDMode,
  IN const UINT8          TempRange,
  IN const UINT8          TempMode,
  IN const UINT8          IntVref,
  IN const UINT8          CS2CALatency,
  IN const UINT8          SelfRefAbort,
  IN const UINT8          RdPreaMode,
  IN const UINT8          RdPrea,
  IN const UINT8          WrPrea
  );

/**
  This function writes the MR3 register for all the ranks and channels

  @param[in] MrcData         - include all the MRC data
  @param[in] MprPage         - MPR Page Selection bit A0-A1
  @param[in] MprOper         - MPR Operation bit A2
  @param[in] MprReadFormat   - MPR Read Format bit A11-A12
  @param[in] Geardown        - Geardown Mode bit A3
  @param[in] PDA             - Per DRAM Addressability bit A4
  @param[in] TempSensor      - Temperature Sensor Readout bit A5
  @param[in] RefreshRate     - Fine Granularity Refresh Mode bit A6-A8
  @param[in] WriteCMDLatency - Write CMD Latency when DM are enabled bit A9-A10

  @retval MrcStatus - mrcSuccess if passes, otherwise an error status

**/
MrcStatus
MrcSetMR3_DDR4 (
  IN MrcParameters *const MrcData,
  IN const UINT8          MprPage,
  IN const UINT8          MprOper,
  IN const UINT8          MprReadFormat,
  IN const UINT8          Geardown,
  IN const UINT8          PDA,
  IN const UINT8          TempSensor,
  IN const UINT8          RefreshRate,
  IN const UINT8          WriteCMDLatency
  );

/**
  This function writes the MR2 register for all the ranks and channels

  @param[in, out] MrcData    - general data
  @param[in]      WriteCRC   - Write CRC Enable bit (A12)

  @retval MrcStatus - mrcSuccess if passes, otherwise an error status

**/
MrcStatus
MrcSetMR2_DDR4 (
  IN OUT MrcParameters *const MrcData,
  IN     const UINT8          WriteCRC
  );

/**
  This function writes the MR1 register for all the ranks and channels

  @param[in, out] MrcData         - include all the MRC data
  @param[in]      DLLEnable       - DLL enable bit A0
  @param[in]      Odic            - Output driver impedance control A1-A2
  @param[in]      AdditiveLatency - Additive latency bit A3-A4
  @param[in]      WlEnable        - Write leveling enable bit A7
  @param[in]      Qoff            - Qoff bit A12

  @retval MrcStatus - mrcSuccess if passes, otherwise an error status

**/
MrcStatus
MrcSetMR1_DDR4 (
  IN OUT MrcParameters *const MrcData,
  IN     const UINT8          DLLEnable,
  IN     const UINT8          Odic,
  IN     const UINT8          AdditiveLatency,
  IN     const UINT8          WlEnable,
  IN     const UINT8          Qoff
  );

/**
  This function writes the MR0 register for all the ranks

  @param[in, out] MrcData         - include all the MRC data
  @param[in]      BurstLength     - Burst length bit A0-A1
  @param[in]      ReadBurstType   - Read burst type bit A3
  @param[in]      TestMode        - Test mode type bit A7
  @param[in]      DllReset        - DLL reset bit A8

  @retval MrcStatus - mrcSuccess if passes, otherwise an error status

**/
MrcStatus
MrcSetMR0_DDR4 (
  IN OUT MrcParameters *const MrcData,
  IN     const UINT8          BurstLength,
  IN     const UINT8          ReadBurstType,
  IN     const UINT8          TestMode,
  IN     const UINT8          DllReset
  );

/**
  This function updates the Rtt value in the MR2 value passed in.

  @param[in] MrcData          - Include all the MRC general data.
  @param[in] OdtValue         - Selected odt index.
  @param[in] Ddr4ModeRegister - Register to update.

  @retval Ddr4ModeRegister - Updated MR2 register

**/
DDR4_MODE_REGISTER_2_STRUCT
UpdateRttWrValue_DDR4 (
  MrcParameters *const        MrcData,
  const UINT8                 OdtValue,
  DDR4_MODE_REGISTER_2_STRUCT Ddr4ModeRegister
  );

/**
  This function updates the Rtt value in the MR5 value passed in.

  @param[in] MrcData          - Include all the MRC general data.
  @param[in] OdtValue         - Selected odt index.
  @param[in] Ddr4ModeRegister - Register to update.

  @retval Ddr4ModeRegister - Updated MR5 register

**/
DDR4_MODE_REGISTER_5_STRUCT
UpdateRttParkValue_DDR4 (
  MrcParameters *const        MrcData,
  const UINT8                 OdtValue,
  DDR4_MODE_REGISTER_5_STRUCT Ddr4ModeRegister
  );

/**
  This funtion takes the MR1 register value and updates the odt value
 inside the register.

  @param[in] MrcData          - Include all the MRC general data.
  @param[in] OdtValue         - Selected odt index.
  @param[in] Ddr4ModeRegister - Register to update.

  @retval Ddr4ModeRegister  - Updated register

**/
DDR4_MODE_REGISTER_1_STRUCT
UpdateRttNomValue_DDR4 (
  IN MrcParameters *const        MrcData,
  IN const UINT8                 OdtValue,
  IN DDR4_MODE_REGISTER_1_STRUCT Ddr4ModeRegister
  );

/**
  This function selects the ODT table according to the board type.

  @param[in] MrcData         - Include all the MRC general data.
  @param[in] Dimm            - selected DIMM.
  @param[in] OdtIndex        - selected ODT index.

  @retval TOdtValueDdr4 * - Pointer to the relevant table or NULL if the table was not found.
**/
TOdtValueDdr4 *
SelectTable_DDR4 (
  IN MrcParameters *const MrcData,
  IN const UINT8          Dimm,
  IN const TOdtIndex      OdtIndex
  );

/**
  Issue DDR4 MRS command (PDA Mode)

  @param[in] MrcData         - Include all the MRC general data.
  @param[in] Channel         - Channel to send command to
  @param[in] Rank            - Rank to send command to
  @param[in] Address         - MRS data
  @param[in] MR              - MR # to change
  @param[in] DeviceMask      - Devices/Bytes to send MRS data to
  @param[in] PDAmode         - Per-DRAM-Addressability mode

  @retval mrcSuccess    - PDA command was sent successfully
  @retval mrcDeviceBusy - Timed out waiting for MRH
**/
MrcStatus
MrcDdr4PdaCmd (
  IN MrcParameters *const MrcData,
  IN UINT32               Channel,
  IN UINT32               Rank,
  IN UINT16               Address,
  IN UINT8                MR,
  IN UINT16               DeviceMask,
  IN BOOLEAN              PDAmode
  );

/**
  Offset to DDR4 VrefDQ Range/Value (MR6)

  @param[in]  MrcData  - Include all MRC global data.
  @param[in]  Offset   - Value to be converted to actual VrefDQ Range/Value.
  @param[in]  Channel  - Channel to be converted

  @retval DDR4 VrefDQ Range/Value
**/
UINT8
MrcOffsetToVrefDq (
  IN MrcParameters *const MrcData,
  IN INT8                 Offset,
  IN UINT8                Channel
  );

/**
  DDR4 VrefDQ Range/Value (MR6) to Offset

  @param[in] VrefDQ          - MR6 Bits A6:A0(Bit6 Range, Bit5:0 Value)

  @retval Offset
**/
INT8
MrcVrefDqToOffset (
  IN UINT8                VrefDQ
  );


/**
  Maps the bytes to their corresponding device

  @param[in] MrcData         - Include all the MRC general data.

  @retval mrcSuccess if successful or some type of failure due to checks
**/
MrcStatus
MrcDdr4DeviceMap (
  IN MrcParameters *const MrcData
  );
#endif //SUPPORT_DDR4

/**
  Setup for using Set B Latency (Read and Write) for LPDDR3

  @param[in]  MrcData   - Include all MRC global data.

  @retval mrcSuccess
**/
MrcStatus
MrcLpddrLatencySetB (
  IN MrcParameters *const MrcData
  );

/**
  This function ensures that DDR4 TxDq Vref Range values is the same across all ranks and bytes
  in a single channel.
  Function checks for each channel there are different ranges used. If no - nothing will happen.
  If there are different ranges it will check what is the most fitting range bit that fits all
  bytes. There should not be any need for different ranges in one channel, however if they do
  exist then it will choose the one that exceeds the range limit least.

  @param[in] MrcData         - Include all the MRC general data.

  @retval MrcStatus - Success if passed, Failure otherwise.
**/
MrcStatus
MrcTrainDdrTxDqVrefRange (
  IN MrcParameters  *const  MrcData
  );

#pragma pack (pop)
#endif // _MrcDdr3_h_
