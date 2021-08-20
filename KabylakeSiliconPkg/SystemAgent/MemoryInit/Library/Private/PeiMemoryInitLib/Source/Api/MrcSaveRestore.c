/** @file

  Power state and boot mode save and restore data functions.

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

//
// Include files
//

#include "MrcTypes.h"
#include "MrcApi.h"
#include "MrcCommon.h"
#include "MrcGeneral.h"
#include "MrcGlobal.h"
#include "MrcSaveRestore.h"
#include "MrcSpdProcessing.h"

//
// ------- IMPORTANT NOTE --------
// MRC_REGISTER_COUNT_COMMON and MRC_REGISTER_COUNT_SAGV in MrcInterface.h should match these tables.
// Update these define's whenever you add/remove registers from the tables below.

//
// These registers must be saved only once, they don't depend on SA GV point.
// Total bytes to save = 936 + 128 + 36 + 128 + 92 + 56 = 1376
//

GLOBAL_REMOVE_IF_UNREFERENCED const SaveDataControlShort SaveDataCommonPerByte[] = {
  {0x08, 0x0C}, // RxTrainRank2/3
  {0x18, 0x1C}, // RxPerBitRank2/3
  {0x28, 0x2C}, // TxTrainRank2/3
  {0x38, 0x3C}, // TxPerBitRank2/3
  {0x58, 0x5C}, // RxOffsetVdqRank2/3
  {0x74, 0x78}, // VrefControl, VsshiControl
  {0x8C, 0x8C}, // VttGenControl
}; // 13 * 4 = 52 bytes, 9 bytes / 2 ch => 52 * 18 = 936 bytes

// Also need to save registers from SaveDataSaGvPerByte for the ECC Byte:
// 64 * 2ch = 128 bytes

GLOBAL_REMOVE_IF_UNREFERENCED const SaveDataControl SaveDataCommon[] = {
  {0x1800, 0x1800},  //  4  Ch0 CLK   ClkRanksUsed
  {0x1820, 0x1820},  //  4  Ch0 CLK   VssHiCompCtl
  {0x1900, 0x1900},  //  4  Ch1 CLK   ClkRanksUsed
  {0x1920, 0x1920},  //  4  Ch1 CLK   VssHiCompCtl
  {0x2000, 0x2004},  //  8      SCRAM ScrambleCh0/1
  {0x3A1C, 0x3A24},  //  12     COMP  CompVsshi, CompOvr, CompVsshiControl
                     //
                     //  Total DDRIO (without per-byte fubs): 9 * 4 = 36 bytes
                     //
  {0x4030, 0x4038},  //  12 Ch0 DftMisc, EccDft, ScPrCntConfig
  {0x4040, 0x4044},  //  8  Ch0 PmPdwnConfig, WmmReadConfig
  {0x4068, 0x406C},  //  8  Ch0 ScWdbwm
  {0x4078, 0x4078},  //  4  Ch0 McschedsSpare
  {0x4210, 0x4210},  //  4  Ch0 DdrMrParams
  {0x4230, 0x4234},  //  8  Ch0 DeswizzleLow, DeswizzleHigh
  {0x4254, 0x4254},  //  4  Ch0 McInitState
  {0x42B8, 0x42BC},  //  8  Ch0 RhLfsr
  {0x42C0, 0x42C0},  //  4  Ch0 RhControl
  {0x43FC, 0x43FC},  //  4  Ch0 McmntsSpare
                     //
  {0x4430, 0x4438},  //  12 Ch1 DftMisc, EccDft, ScPrCntConfig
  {0x4440, 0x4444},  //  8  Ch1 PmPdwnConfig, WmmReadConfig
  {0x4468, 0x446C},  //  8  Ch1 ScWdbwm
  {0x4478, 0x4478},  //  4  Ch1 McschedsSpare
  {0x4610, 0x4610},  //  4  Ch1 DdrMrParams
  {0x4630, 0x4634},  //  8  Ch1 DeswizzleLow, DeswizzleHigh
  {0x4654, 0x4654},  //  4  Ch1 McInitState
  {0x46B8, 0x46BC},  //  8  Ch1 RhLfsr
  {0x46C0, 0x46C0},  //  4  Ch1 RhControl
  {0x47FC, 0x47FC},  //  4  Ch1 McmntsSpare
                     //
                     //  Total MC Channel: ((12 * 1) + (8 * 4) + (4 * 5)) * 2ch = 128 bytes
                     //
  {0x5000, 0x5010},  //  20 MadInterChannel, MadIntraCh0/1, MadDimmCh0/1
  {0x501C, 0x501C},  //  4  McdecsCbit
  {0x5024, 0x5024},  //  4  ChannelHash
  {0x5030, 0x5034},  //  8  McInitStateG, MrcRevision
  {0x5060, 0x5060},  //  4  PmSrefConfig
  {0x5078, 0x5078},  //  4  IpcMcArb
  {0x50B0, 0x50CC},  //  32 BitErrorRecoverySourceSysaddr0/1/2/3
  {0x5138, 0x5144},  //  16 McGlobalDriverGateCfg, BitErrorRecoveryRangeSysaddr
                     //
                     //  Total MCDECS: 92 bytes
                     //
  {0x5880, 0x5880},  //  4  PCU DdrPtmCtl
  {0x5884, 0x5888},  //  8  PCU DdrEnergyScaleFactor, DdrRaplChannelPowerFloor,
  {0x5890, 0x589C},  //  16 PCU DdrWarmThresholdCh0/1, DdrHotThresholdCh0/1
  {0x58A4, 0x58A4},  //  4  PCU DdrVoltage
  {0x58D0, 0x58E4},  //  24 PCU DdrWarmBudgetCh0/1, DdrHotBudgetCh0/1, DdrRaplLimit
                     //
                     //  Total PCU: 56
};

//
// These registers must be saved for each SA GV point.
// Total bytes to save = 1024 + 172 + 328 + 4 = 1528 bytes
//

GLOBAL_REMOVE_IF_UNREFERENCED const SaveDataControlShort SaveDataSaGvPerByte[] = {
  {0x00, 0x04}, // RxTrainRank0/1
  {0x10, 0x14}, // RxPerBitRank0/1
  {0x20, 0x24}, // TxTrainRank0/1
  {0x30, 0x34}, // TxPerBitRank0/1
  {0x48, 0x48}, // TxXtalk
  {0x50, 0x54}, // RxOffsetVdqRank0/1
  {0x68, 0x70}, // DataOffsetComp, DataControl1, DataControl2
  {0x7c, 0x80}, // DataOffsetTrain, DataControl0
}; // 16 * 4 = 64 bytes, 8 bytes / 2 ch => 64 * 16 = 1024 bytes

GLOBAL_REMOVE_IF_UNREFERENCED const SaveDataControl SaveDataSaGv[] = {
  {0x0084, 0x0084},  //   4 Ch0 Byte0 DdrCrVrefAdjust1
  {0x1204, 0x1208},  //   8 Ch0 CKE   CmdCompOffset, CmdPiCoding
  {0x1214, 0x1220},  //  16 Ch0 CKE   CtlCompOffset, CtlPiCoding, CtlControls, CtlRanksUsed
  {0x1304, 0x1308},  //   8 Ch1 CKE   CmdCompOffset, CmdPiCoding
  {0x1314, 0x1320},  //  16 Ch1 CKE   CtlCompOffset, CtlPiCoding, CtlControls, CtlRanksUsed
  {0x1404, 0x140C},  //  12 Ch0 CMDN  CmdCompOffset, CmdPiCoding, CmdControls
  {0x1504, 0x150C},  //  12 Ch1 CMDN  CmdCompOffset, CmdPiCoding, CmdControls
  {0x1808, 0x1810},  //  12 Ch0 CLK   ClkCompOffset, ClkPiCoding, ClkControls
  {0x1908, 0x1910},  //  12 Ch1 CLK   ClkCompOffset, ClkPiCoding, ClkControls
  {0x1A04, 0x1A0C},  //  12 Ch0 CMDS  CmdCompOffset, CmdPiCoding, CmdControls
  {0x1B04, 0x1B0C},  //  12 Ch1 CMDS  CmdCompOffset, CmdPiCoding, CmdControls
  {0x1C14, 0x1C20},  //  16 Ch0 CTL   CtlCompoffset, CtlPiCoding, CtlControls, CtlRanksUsed
  {0x1D14, 0x1D20},  //  16 Ch1 CTL   CtlCompoffset, CtlPiCoding, CtlControls, CtlRanksUsed
  {0x2008, 0x2008},  //  4      SCRAM DdrMiscControl0
  {0x3A14, 0x3A18},  //  8      COMP  CompCtl0, CompCtl1
  {0x3A28, 0x3A28},  //  4      COMP  CompCtl2
                     //
                     //  Total DDR IO (without per-byte fubs): 43 * 4 = 172 bytes
                     //
  {0x4000, 0x402C},  //  48  Ch0 TcPre, TcAct, TcPwrdn, TcRdRd, TcRdWr, TcWrRd, TcWrWr, ScGsCfg, ScRoundtripLatency, ScIoLatency, SchedCbit, SchedSecondCbit
  {0x403C, 0x403C},  //  4   Ch0 ScPcit
  {0x4070, 0x4070},  //  4   Ch0 TcOdt
  {0x4080, 0x4080},  //  4   Ch0 ScOdtMatrix
  {0x4238, 0x4250},  //  28  Ch0 TcRfp, TcRftp, TcSrftp, McRefreshStagger, TcZqcal, TcMr2Shaddow, TcMr4Shaddow
  {0x4260, 0x4270},  //  20  Ch0 PmDimmIdleEnergy, PmDimmPdEnergy, PmDimmActEnergy, PmDimmRdEnergy, PmDimmWrEnergy
  {0x4278, 0x4278},  //  4   Ch0 ScWrAddDelay
  {0x43A0, 0x43CC},  //  48  Ch0 Ddr4Mr0Mr1Content, Ddr4Mr2Mr3Content, Ddr4Mr4Mr5Content, Ddr4Mr6Mr7Content, Ddr4Mr1OdicValues, Ddr4Mr2RttWrValues,
                     //          Ddr4Mr6VrefValues0, Ddr4Mr6VrefValues1, Lpddr3MrContent, MrsFsmControl
  {0x4400, 0x442C},  //  48  Ch1 TcPre, TcAct, TcPwrdn, TcRdRd, TcRdWr, TcWrRd, TcWrWr, ScGsCfg, ScRoundtripLatency, ScIoLatency, SchedCbit, SchedSecondCbit
  {0x443C, 0x443C},  //  4   Ch1 ScPcit
  {0x4470, 0x4470},  //  4   Ch1 TcOdt
  {0x4480, 0x4480},  //  4   Ch1 ScOdtMatrix
  {0x4638, 0x4650},  //  28  Ch1 TcRfp, TcRftp, TcSrftp, McRefreshStagger, TcZqcal, TcMr2Shaddow, TcMr4Shaddow
  {0x4660, 0x4670},  //  20  Ch1 PmDimmIdleEnergy, PmDimmPdEnergy, PmDimmActEnergy, PmDimmRdEnergy, PmDimmWrEnergy
  {0x4678, 0x4678},  //  4   Ch1 ScWrAddDelay
  {0x47A0, 0x47CC},  //  48  Ch1 Ddr4Mr0Mr1Content, Ddr4Mr2Mr3Content, Ddr4Mr4Mr5Content, Ddr4Mr6Mr7Content, Ddr4Mr1OdicValues, Ddr4Mr2RttWrValues,
                     //          Ddr4Mr6VrefValues0, Ddr4Mr6VrefValues1, Lpddr3MrContent, MrsFsmControl
  {0x5130, 0x5134},  //  8       ScQos
                     //
                     // Total MC: (36 * 4 + 2 * 8) * 2ch + (1 * 8) = 328 bytes
                     //
  {0x59B8, 0x59B8},  //  4  PCU MrcOdtPowerSaving
                     //
                     // Total PCU: 4
};

/**
  This function verifies that neither CPU fuses or DIMMs have changed.

  @param[in] MrcData - Include all MRC global data.

  @retval mrcSuccess if fast boot is allowed, otherwise mrcColdBootRequired.
**/
MrcStatus
MrcFastBootPermitted (
  IN     MrcParameters *const MrcData
  )
{
  const MrcInput            *Inputs;
  const MRC_FUNCTION        *MrcCall;
  const MrcControllerIn     *ControllerIn;
  const MrcChannelIn        *ChannelIn;
  const MrcDimmIn           *DimmIn;
  const UINT8               *CrcStart;
  MrcOutput                 *Outputs;
  MrcDebug                  *Debug;
  MrcSaveData               *Save;
  MrcContSave               *ControllerSave;
  MrcChannelSave            *ChannelSave;
  MrcDimmOut                *DimmSave;
  MrcCapabilityId           Capid0Reg;
  UINT32                    CrcSize;
  UINT8                     Controller;
  UINT8                     Channel;
  UINT8                     Dimm;
  UINT16                    DimmCrc;
  UINT32                    Offset;

  CrcStart = NULL;
  CrcSize  = 0;
  Inputs   = &MrcData->Inputs;
  MrcCall = Inputs->Call.Func;
  Save     = &MrcData->Save.Data;
  Outputs  = &MrcData->Outputs;
  Debug    = &Outputs->Debug;

  //
  // Obtain the capabilities of the memory controller and see if they have changed.
  //
  Offset = Inputs->PciEBaseAddress + MrcCall->MrcGetPcieDeviceAddress (0, 0, 0, UNCORE_CR_CAPID0_A_0_0_0_PCI_REG);
  Capid0Reg.Data32.A.Data = MrcCall->MrcMmioRead32 (Offset);
  Capid0Reg.Data32.B.Data = MrcCall->MrcMmioRead32 (Offset + 4);
  if (Capid0Reg.Data != Save->McCapId.Data) {
    MRC_DEBUG_MSG (
      Debug,
      MSG_LEVEL_NOTE,
      "Capabilities have changed, cold boot required\n '%X_%X' --> '%X_%X'\n",
      Save->McCapId.Data32.B.Data,
      Save->McCapId.Data32.A.Data,
      Capid0Reg.Data32.B.Data,
      Capid0Reg.Data32.A.Data
      );
    return mrcColdBootRequired;
  }
  //
  // See if any of the DIMMs have changed.
  //
  for (Controller = 0; Controller < MAX_CONTROLLERS; Controller++) {
    ControllerIn   = &Inputs->Controller[Controller];
    ControllerSave = &Save->Controller[Controller];
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      ChannelIn   = &ControllerIn->Channel[Channel];
      ChannelSave = &ControllerSave->Channel[Channel];
      for (Dimm = 0; Dimm < MAX_DIMMS_IN_CHANNEL; Dimm++) {
        DimmIn   = &ChannelIn->Dimm[Dimm];
        DimmSave = &ChannelSave->Dimm[Dimm];
        if (DimmIn->Status == DIMM_DISABLED) {
          DimmCrc = 0;
        } else {
          CrcStart = MrcSpdCrcArea (MrcData, Controller, Channel, Dimm, &CrcSize);
          GetDimmCrc ((const UINT8 *const) CrcStart, CrcSize, &DimmCrc);
        }

        MRC_DEBUG_MSG (
          Debug,
          MSG_LEVEL_NOTE,
          "Channel %u Dimm %u DimmCrc %Xh, DimmSave->Crc %Xh\n",
          Channel,
          Dimm,
          DimmCrc,
          DimmSave->Crc
          );
        if (DimmCrc != DimmSave->Crc) {
          MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Dimm has changed, cold boot required\n");
          return mrcColdBootRequired;
        }
      }
    }
  }
  //
  // Set RestoreMRs flag to use trained Opt Param Values for Power Savings.
  //
  Outputs->RestoreMRs = TRUE;

  return mrcSuccess;
}

/**
  This function saves any values that need to be used during non-cold boots.

  @param[in, out] MrcData - Include all the MRC global data.

  @retval mrcSuccess if the save occurred with no errors, otherwise returns an error code.
**/
MrcStatus
MrcSaveMCValues (
  IN OUT MrcParameters *const MrcData
  )
{
  const SaveDataControl       *SaveIt;
  const SaveDataControlShort  *SaveItShort;
  const MrcInput        *Inputs;
  const MrcControllerIn *ControllerIn;
  const MrcChannelIn    *ChannelIn;
  const MrcSpd          *SpdIn;
  const MRC_FUNCTION    *MrcCall;
  MrcIntOutput          *MrcIntData;
  MrcOutput             *Outputs;
  MrcDebug              *Debug;
  MrcSaveData           *SaveData;
  MrcSaveHeader         *SaveHeader;
  MrcControllerOut      *ControllerOut;
  MrcChannelOut         *ChannelOut;
  MrcContSave           *ControllerSave;
  MrcChannelSave        *ChannelSave;
  UINT32                *McRegister;
  UINT32                *McRegisterStart;
  UINT8                 *SpdBegin;
  MrcProfile            Profile;
  UINT32                Offset;
  UINT32                RegOffset;
  UINT32                Index;
  UINT32                Value;
  UINT8                 Controller;
  UINT8                 Channel;
  UINT8                 Dimm;
  UINT32                Byte;
  UNCORE_CR_CAPID0_A_0_0_0_PCI_STRUCT Capid0A;
  UNCORE_CR_CAPID0_B_0_0_0_PCI_STRUCT Capid0B;

  //
  // Copy channel and DIMM information to the data area that will be saved.
  //
  Inputs      = &MrcData->Inputs;
  MrcCall     = Inputs->Call.Func;
  Outputs     = &MrcData->Outputs;
  SaveData    = &MrcData->Save.Data;
  SaveHeader  = &MrcData->Save.Header;
  Debug       = &Outputs->Debug;
  MrcIntData  = ((MrcIntOutput *) (MrcData->IntOutputs.Internal));

  if ((Inputs->SaGv != MrcSaGvEnabled) || (MrcIntData->SaGvPoint == MrcSaGvPointLow)) {
    MrcCall->MrcSetMem ((UINT8 *) &MrcData->Save, sizeof (MrcSave), 0);
  }

  Offset       = Inputs->PciEBaseAddress + MrcCall->MrcGetPcieDeviceAddress (0, 0, 0, UNCORE_CR_CAPID0_A_0_0_0_PCI_REG);
  Capid0A.Data = MrcCall->MrcMmioRead32 (Offset);

  Offset       = Inputs->PciEBaseAddress + MrcCall->MrcGetPcieDeviceAddress (0, 0, 0, UNCORE_CR_CAPID0_B_0_0_0_PCI_REG);
  Capid0B.Data = MrcCall->MrcMmioRead32 (Offset);

  SaveData->McCapId.Data32.A.Data = Capid0A.Data;
  SaveData->McCapId.Data32.B.Data = Capid0B.Data;

  for (Controller = 0; Controller < MAX_CONTROLLERS; Controller++) {
    ControllerIn                  = &Inputs->Controller[Controller];
    ControllerOut                 = &Outputs->Controller[Controller];
    ControllerSave                = &SaveData->Controller[Controller];
    ControllerSave->ChannelCount  = ControllerOut->ChannelCount;
    ControllerSave->Status        = ControllerOut->Status;

    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      ChannelIn   = &ControllerIn->Channel[Channel];
      ChannelOut  = &ControllerOut->Channel[Channel];
      ChannelSave                   = &ControllerSave->Channel[Channel];
      ChannelSave->DimmCount        = ChannelOut->DimmCount;
      ChannelSave->ValidRankBitMask = ChannelOut->ValidRankBitMask;
      ChannelSave->Status           = ChannelOut->Status;
      for (Profile = STD_PROFILE; Profile < MAX_PROFILE; Profile++) {
        MrcCall->MrcCopyMem ((UINT8 *) &ChannelSave->Timing[Profile], (UINT8 *) &ChannelOut->Timing[Profile], sizeof (MrcTiming));
      }
      for (Dimm = 0; Dimm < MAX_DIMMS_IN_CHANNEL; Dimm++) {
        MrcCall->MrcCopyMem ((UINT8 *) &ChannelSave->Dimm[Dimm], (UINT8 *) &ChannelOut->Dimm[Dimm], sizeof (MrcDimmOut));
        SpdIn = &ChannelIn->Dimm[Dimm].Spd.Data;
        if ((Outputs->DdrType == MRC_DDR_TYPE_DDR3) || (SpdIn->Ddr3.General.DramDeviceType.Bits.Type == MRC_SPD_LPDDR3_SDRAM_TYPE_NUMBER)) {
          SpdBegin = (UINT8 *) &SpdIn->Ddr3.ModuleId;
          ChannelSave->DimmSave[Dimm].SpdDramDeviceType = SpdIn->Ddr3.General.DramDeviceType.Data;
          ChannelSave->DimmSave[Dimm].SpdModuleType = SpdIn->Ddr3.General.ModuleType.Data;
          ChannelSave->DimmSave[Dimm].SpdModuleMemoryBusWidth = SpdIn->Ddr3.General.ModuleMemoryBusWidth.Data;
        } else {
          SpdBegin = (UINT8 *) &SpdIn->Ddr4.ManufactureInfo;
          ChannelSave->DimmSave[Dimm].SpdDramDeviceType = SpdIn->Ddr4.Base.DramDeviceType.Data;
          ChannelSave->DimmSave[Dimm].SpdModuleType = SpdIn->Ddr4.Base.ModuleType.Data;
          ChannelSave->DimmSave[Dimm].SpdModuleMemoryBusWidth = SpdIn->Ddr4.Base.ModuleMemoryBusWidth.Data;
        }
        //
        // Save just enough SPD information so it can be restored during non-cold boot.
        //
        MrcCall->MrcCopyMem ((UINT8 *) &ChannelSave->DimmSave[Dimm].SpdSave[0], SpdBegin, sizeof (ChannelSave->DimmSave[Dimm].SpdSave));
      } // for Dimm
    } // for Channel
  } // for Controller

  for (Profile = STD_PROFILE; Profile < MAX_PROFILE; Profile++) {
    SaveData->VddVoltage[Profile] = Outputs->VddVoltage[Profile];
    if (Profile < XMP_PROFILE1) {
      // Store the tCK value read from SPD XMP profiles.
      // Use Profile as the logical array indecies for XMP1 and XMP2.
      SaveData->DefaultXmptCK[Profile] = Outputs->DefaultXmptCK[Profile];
    }
  }

  //
  // Copy specified memory controller MMIO registers to the data area that will be saved.
  // Start with the common section.
  //

  if ((Inputs->SaGv == MrcSaGvEnabled) && (MrcIntData->SaGvPoint == MrcSaGvPointLow)) {
    //
    // If SA GV is enabled, only save the Common registers at HIGH point.
    //
  } else {

    McRegister = SaveData->RegSaveCommon;

    for (Index = 0; Index < (sizeof (SaveDataCommon) / sizeof (SaveDataControl)); Index++) {
      SaveIt = &SaveDataCommon[Index];
      for (Offset = SaveIt->StartMchbarOffset; Offset <= SaveIt->EndMchbarOffset; Offset += sizeof (UINT32)) {
        Value         = MrcReadCR (MrcData, Offset);
        *McRegister++ = Value;
      }
    }
    //
    // Common per-byte registers
    //
    for (Index = 0; Index < (sizeof (SaveDataCommonPerByte) / sizeof (SaveDataControlShort)); Index++) {
      SaveItShort = &SaveDataCommonPerByte[Index];
      for (Offset = SaveItShort->StartMchbarOffset; Offset <= SaveItShort->EndMchbarOffset; Offset += sizeof (UINT32)) {
        for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
          for (Byte = 0; Byte < MAX_SDRAM_IN_DIMM; Byte++) {
            RegOffset =
              Offset + (DDRDATA0CH1_CR_TXTRAINRANK0_REG - DDRDATA0CH0_CR_TXTRAINRANK0_REG) * Channel +
              (DDRDATA1CH0_CR_TXTRAINRANK0_REG - DDRDATA0CH0_CR_TXTRAINRANK0_REG) * Byte;
            Value = MrcReadCR (MrcData, RegOffset);
            *McRegister++ = Value;
          }
        }
      }
    }
    //
    // Portion of the ECC byte, per channel
    //
    for (Index = 0; Index < (sizeof (SaveDataSaGvPerByte) / sizeof (SaveDataControlShort)); Index++) {
      SaveItShort = &SaveDataSaGvPerByte[Index];
      for (Offset = SaveItShort->StartMchbarOffset; Offset <= SaveItShort->EndMchbarOffset; Offset += sizeof (UINT32)) {
        for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
          RegOffset =
            Offset + (DDRDATA0CH1_CR_TXTRAINRANK0_REG - DDRDATA0CH0_CR_TXTRAINRANK0_REG) * Channel +
            (DDRDATA1CH0_CR_TXTRAINRANK0_REG - DDRDATA0CH0_CR_TXTRAINRANK0_REG) * 8;
          Value = MrcReadCR (MrcData, RegOffset);
          *McRegister++ = Value;
        }
      }
    }
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Common section: saved %d bytes\n", (McRegister - SaveData->RegSaveCommon) * 4);
    if ((UINT32) (McRegister - SaveData->RegSaveCommon) > MRC_REGISTER_COUNT_COMMON) {
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "ERROR: RegSaveCommon overflow!\n");
      return mrcFail;
    }
  } // if SAGV and Low point

  if ((Inputs->SaGv == MrcSaGvEnabled) && (MrcIntData->SaGvPoint == MrcSaGvPointHigh)) {
    McRegister = SaveData->RegSaveHigh;
  } else {
    McRegister = SaveData->RegSaveLow;
  }
  McRegisterStart = McRegister;

  for (Index = 0; Index < (sizeof (SaveDataSaGv) / sizeof (SaveDataControl)); Index++) {
    SaveIt = &SaveDataSaGv[Index];
    for (Offset = SaveIt->StartMchbarOffset; Offset <= SaveIt->EndMchbarOffset; Offset += sizeof (UINT32)) {
      Value         = MrcReadCR (MrcData, Offset);
      *McRegister++ = Value;
    }
  }

  //
  // Per-byte registers
  //
  for (Index = 0; Index < (sizeof (SaveDataSaGvPerByte) / sizeof (SaveDataControlShort)); Index++) {
    SaveItShort = &SaveDataSaGvPerByte[Index];
    for (Offset = SaveItShort->StartMchbarOffset; Offset <= SaveItShort->EndMchbarOffset; Offset += sizeof (UINT32)) {
      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        for (Byte = 0; Byte < MAX_SDRAM_IN_DIMM - 1; Byte++) {
          RegOffset =
            Offset + (DDRDATA0CH1_CR_TXTRAINRANK0_REG - DDRDATA0CH0_CR_TXTRAINRANK0_REG) * Channel +
            (DDRDATA1CH0_CR_TXTRAINRANK0_REG - DDRDATA0CH0_CR_TXTRAINRANK0_REG) * Byte;
          Value = MrcReadCR (MrcData, RegOffset);
          *McRegister++ = Value;
        }
      }
    }
  }

  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "SAGV section: saved %d bytes\n", (McRegister - McRegisterStart) * 4);
  if ((UINT32) (McRegister - McRegisterStart) > MRC_REGISTER_COUNT_SAGV) {
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "ERROR: RegSaveHigh/Low overflow!\n");
    return mrcFail;
  }

  //
  // ------- IMPORTANT NOTE --------
  // MeStolenSize should not be saved/restored.  There is no rule stating that ME FW cannot request a different
  // amount of ME UMA space from one boot to the next.  Also, if ME FW is updated/changed, the UMA Size requested
  // from the previous version should not be restored.
  //

  MrcVersionGet (MrcData, &SaveData->Version);
  SaveData->CpuModel               = Inputs->CpuModel;
  SaveData->CpuStepping            = Inputs->CpuStepping;
  SaveData->CpuFamily              = Inputs->CpuFamily;
  SaveData->Frequency              = Outputs->Frequency;
  SaveData->MemoryClock            = Outputs->MemoryClock;
  SaveData->Ratio                  = Outputs->Ratio;
  SaveData->RefClk                 = Outputs->RefClk;
  SaveData->EccSupport             = Outputs->EccSupport;
  SaveData->DdrType                = Outputs->DdrType;
  SaveData->TCRSensitiveHynixDDR4  = Outputs->TCRSensitiveHynixDDR4;
  SaveData->TCRSensitiveMicronDDR4 = Outputs->TCRSensitiveMicronDDR4;
  SaveData->XmpProfileEnable       = Outputs->XmpProfileEnable;
  SaveData->BerEnable              = Outputs->BerEnable;
  SaveData->LpddrEctDone           = Outputs->LpddrEctDone;
  SaveData->BinnedLpddrDevices     = Outputs->BinnedLpddrDevices;
  SaveData->MixedUDimmConfig2Dpc   = Outputs->MixedUDimmConfig2Dpc;
  SaveData->ExtendedDdrOverclock   = Outputs->ExtendedDdrOverclock;
  for (Index = 0; Index < 4; Index++) {
    SaveData->BerAddress[Index] = Outputs->BerAddress[Index];
  }
  if ((Inputs->SaGv == MrcSaGvEnabled) && (MrcIntData->SaGvPoint == MrcSaGvPointLow)) {
    SaveData->OddRatioModeLow   = Outputs->OddRatioMode;
  } else {
    SaveData->OddRatioModeHigh  = Outputs->OddRatioMode;
  }

#ifdef UP_SERVER_FLAG
  if (Inputs->BoardType == btUpServer) {
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Output UP CLTM TSOD Offset\nValue = c0d0:%xh\tcod1:%xh\tc1d0:%xh\tc1d1:%xh\n", Outputs->ThermOffset[0][0],Outputs->ThermOffset[0][1], Outputs->ThermOffset[1][0], Outputs->ThermOffset[1][1] );
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      for (Dimm = 0; Dimm < MAX_DIMMS_IN_CHANNEL; Dimm++) {
        SaveData->ThermOffset[Channel][Dimm] = Outputs->ThermOffset[Channel][Dimm];                        ///TSOD Thermal Offset
      }
    }
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Save UP CLTM TSOD Offset  \nValue = c0d0:%xh\tcod1:%xh\tc1d0:%xh\tc1d1:%xh\n", SaveData->ThermOffset[0][0],SaveData->ThermOffset[0][1], SaveData->ThermOffset[1][0], SaveData->ThermOffset[1][1] );
  }
#endif

  SaveData->SaMemCfgCrc = MrcCalculateCrc32 ((UINT8 *) Inputs->SaMemCfgAddress, Inputs->SaMemCfgSize);
  SaveHeader->Crc       = MrcCalculateCrc32 ((UINT8 *) SaveData, sizeof (MrcSaveData));
  MrcData->Save.Size    = sizeof (MrcSave);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Saved data CRC = %xh\n", SaveHeader->Crc);

  return mrcSuccess;
}

/**
  This function copies the non-training information that needs to be restored
  from the 'save' data structure to the 'Output' data structure.

  @param[in, out] MrcData - include all the MRC global data.

  @retval mrcSuccess if the copy completed with no errors, otherwise returns an error code.
**/
MrcStatus
MrcRestoreNonTrainingValues (
  IN OUT MrcParameters *const MrcData
  )
{
  MRC_FUNCTION      *MrcCall;
  MrcInput          *Inputs;
  MrcControllerIn   *ControllerIn;
  MrcChannelIn      *ChannelIn;
  MrcSaveData       *SaveData;
  MrcContSave       *ControllerSave;
  MrcChannelSave    *ChannelSave;
  MrcDimmOut        *DimmSave;
  MrcOutput         *Outputs;
  MrcDebug          *Debug;
  MrcIntOutput      *MrcIntData;
  MrcControllerOut  *ControllerOut;
  MrcChannelOut     *ChannelOut;
  MrcDimmOut        *DimmOut;
  MrcSpd            *SpdIn;
  UINT8             *SpdBegin;
  MrcProfile        Profile;
  UINT8             Controller;
  UINT8             Channel;
  UINT8             Dimm;
  UINT8             Index;

  SaveData = &MrcData->Save.Data;
  Outputs  = &MrcData->Outputs;
  Debug    = &Outputs->Debug;
  Inputs   = &MrcData->Inputs;
  MrcCall  = Inputs->Call.Func;
  MrcIntData = ((MrcIntOutput *) (MrcData->IntOutputs.Internal));

  for (Controller = 0; Controller < MAX_CONTROLLERS; Controller++) {
    ControllerIn                = &Inputs->Controller[Controller];
    ControllerSave              = &SaveData->Controller[Controller];
    ControllerOut               = &Outputs->Controller[Controller];
    ControllerOut->ChannelCount = ControllerSave->ChannelCount;
    ControllerOut->Status       = ControllerSave->Status;
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      ChannelIn                     = &ControllerIn->Channel[Channel];
      ChannelSave                   = &ControllerSave->Channel[Channel];
      ChannelOut                    = &ControllerOut->Channel[Channel];
      ChannelOut->DimmCount         = ChannelSave->DimmCount;
      ChannelOut->ValidRankBitMask  = ChannelSave->ValidRankBitMask;
      ChannelOut->Status            = ChannelSave->Status;
      for (Profile = STD_PROFILE; Profile < MAX_PROFILE; Profile++) {
        MrcCall->MrcCopyMem ((UINT8 *) &ChannelOut->Timing[Profile], (UINT8 *) &ChannelSave->Timing[Profile], sizeof (MrcTiming));
      }
      for (Dimm = 0; Dimm < MAX_DIMMS_IN_CHANNEL; Dimm++) {
        DimmSave = &ChannelSave->Dimm[Dimm];
        DimmOut  = &ChannelOut->Dimm[Dimm];
        if (DimmSave->Status == DIMM_PRESENT || DimmSave->Status == DIMM_DISABLED) {
          SpdIn   = &ChannelIn->Dimm[Dimm].Spd.Data;
          MrcCall->MrcCopyMem ((UINT8 *) DimmOut, (UINT8 *) DimmSave, sizeof (MrcDimmOut));
          if ((SaveData->DdrType == MRC_DDR_TYPE_DDR3) || (SpdIn->Ddr3.General.DramDeviceType.Bits.Type == MRC_SPD_LPDDR3_SDRAM_TYPE_NUMBER)) {
            SpdBegin = (UINT8 *) &SpdIn->Ddr3.ModuleId;
          } else {
            SpdBegin = (UINT8 *) &SpdIn->Ddr4.ManufactureInfo;
          }
          //
          // Restore just enough SPD information so it can be passed out in the HOB.
          // If SAGV enabled, only do this on the second pass, due to LPDDR3 VendorId patching.
          //
          if ((Inputs->SaGv != MrcSaGvEnabled) || (MrcIntData->SaGvPoint != MrcSaGvPointLow)) {
            MrcCall->MrcCopyMem (SpdBegin, (UINT8 *) &ChannelSave->DimmSave[Dimm].SpdSave[0], sizeof (ChannelSave->DimmSave[Dimm].SpdSave));
          }
        } else {
          DimmOut->Status = DimmSave->Status;
        }
      } // for Dimm
    } // for Channel
  } // for Controller

  for (Profile = STD_PROFILE; Profile < MAX_PROFILE; Profile++) {
    Outputs->VddVoltage[Profile] = SaveData->VddVoltage[Profile];
    if (Profile < XMP_PROFILE1) {
      // Restore the tCK value read from SPD XMP profiles.
      // Use Profile as the logical array indecies for XMP1 and XMP2.
      Outputs->DefaultXmptCK[Profile] = SaveData->DefaultXmptCK[Profile];
    }
  }

  //
  // ------- IMPORTANT NOTE --------
  // MeStolenSize should not be saved/restored.  There is no rule stating that ME FW cannot request a different
  // amount of ME UMA space from one boot to the next.  Also, if ME FW is updated/changed, the UMA Size requested
  // from the previous version should not be restored.
  //

  Inputs->CpuModel                = SaveData->CpuModel;
  Inputs->CpuStepping             = SaveData->CpuStepping;
  Inputs->CpuFamily               = SaveData->CpuFamily;
  Outputs->Frequency              = SaveData->Frequency;
  Outputs->MemoryClock            = SaveData->MemoryClock;
  Outputs->Ratio                  = SaveData->Ratio;
  Outputs->RefClk                 = SaveData->RefClk;
  Outputs->EccSupport             = SaveData->EccSupport;
  Outputs->DdrType                = SaveData->DdrType;
  Outputs->TCRSensitiveHynixDDR4  = SaveData->TCRSensitiveHynixDDR4;
  Outputs->TCRSensitiveMicronDDR4 = SaveData->TCRSensitiveMicronDDR4;
  Outputs->XmpProfileEnable       = SaveData->XmpProfileEnable;
  Outputs->MixedUDimmConfig2Dpc   = SaveData->MixedUDimmConfig2Dpc;
  Outputs->ExtendedDdrOverclock   = SaveData->ExtendedDdrOverclock;

  if ((Inputs->SaGv == MrcSaGvEnabled) && (MrcIntData->SaGvPoint == MrcSaGvPointLow)) {
    //
    // Set the LOW point for SA GV. On Cold flow this is done in SPD processing.
    //
    if (Inputs->FreqSaGvLow) {
      Outputs->Frequency = Inputs->FreqSaGvLow;
    } else {
      Outputs->Frequency = (Outputs->DdrType == MRC_DDR_TYPE_DDR4) ? f1333 : f1067;
    }
    Outputs->MemoryClock      = ConvertFreq2Clock (MrcData, Outputs->Frequency);
    Outputs->Ratio            = MrcFrequencyToRatio (MrcData, Outputs->Frequency, Outputs->RefClk, Inputs->BClkFrequency);
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "SAGV Low point: Frequency=%u, tCK=%ufs, Ratio=%u\n", Outputs->Frequency, Outputs->MemoryClock, Outputs->Ratio);

    Outputs->OddRatioMode = SaveData->OddRatioModeLow;
  } else {
    Outputs->OddRatioMode = SaveData->OddRatioModeHigh;
  }

  Outputs->LpddrEctDone       = SaveData->LpddrEctDone;
  Outputs->BinnedLpddrDevices = SaveData->BinnedLpddrDevices;
  Outputs->BerEnable          = SaveData->BerEnable;
  for (Index = 0; Index < 4; Index++) {
    Outputs->BerAddress[Index] = SaveData->BerAddress[Index];
  }

#ifdef UP_SERVER_FLAG
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Save UP CLTM TSOD Offset  \nValue = c0d0:%xh\tcod1:%xh\tc1d0:%xh\tc1d1:%xh\n", SaveData->ThermOffset[0][0],SaveData->ThermOffset[0][1], SaveData->ThermOffset[1][0], SaveData->ThermOffset[1][1] );
  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    for (Dimm = 0; Dimm < MAX_DIMMS_IN_CHANNEL; Dimm++) {
      Outputs->ThermOffset[Channel][Dimm] = SaveData->ThermOffset[Channel][Dimm];                        ///TSOD Thermal Offset
    }
  }
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Output UP CLTM TSOD Offset\nValue = c0d0:%xh\tcod1:%xh\tc1d0:%xh\tc1d1:%xh\n", Outputs->ThermOffset[0][0],Outputs->ThermOffset[0][1], Outputs->ThermOffset[1][0], Outputs->ThermOffset[1][1] );
#endif

  return mrcSuccess;
}

/**
  This function writes the previously determined training values back to the memory controller,
  for the SAGV section

  @param[in] MrcData    - Include all the MRC global data.
  @param[in] McRegister - Data array to restore the values from.

  @retval mrcSuccess if the memory controller write back completed with no errors, otherwise returns an error code.
**/
MrcStatus
MrcRestoreTrainingSaGv (
  IN MrcParameters *const MrcData,
  IN UINT32               *McRegister
  )
{
  MrcIntOutput                *MrcIntData;
  MrcIntChannelOut            *IntChannelOut;
  const SaveDataControl       *RestoreIt;
  const SaveDataControlShort  *RestoreItShort;
  MrcDebug              *Debug;
  UINT32                *McRegisterStart;
  UINT32                Offset;
  UINT32                RegOffset;
  UINT32                Index;
  UINT32                Value;
  UINT32                Channel;
  UINT32                Byte;

  MrcIntData  = ((MrcIntOutput *) (MrcData->IntOutputs.Internal));
  Debug    = &MrcData->Outputs.Debug;

  McRegisterStart = McRegister;

  for (Index = 0; Index < (sizeof (SaveDataSaGv) / sizeof (SaveDataControl)); Index++) {
    RestoreIt = &SaveDataSaGv[Index];
    for (Offset = RestoreIt->StartMchbarOffset; Offset <= RestoreIt->EndMchbarOffset; Offset += sizeof (UINT32)) {
      Value = *McRegister++;
      MrcWriteCR (MrcData, Offset, Value);
      // Re-populate Turnaround timings in internal output structure.
      switch (Offset) {
        case MCHBAR_CH0_CR_TC_RDRD_REG:
        case MCHBAR_CH1_CR_TC_RDRD_REG:
          Channel = ((Offset - MCHBAR_CH0_CR_TC_RDRD_REG) > 0) ? 1 : 0;
          IntChannelOut = &MrcIntData->Controller[0].Channel[Channel];
          IntChannelOut->MchbarTcRdRd.Data = Value;
          break;

        case MCHBAR_CH0_CR_TC_RDWR_REG:
        case MCHBAR_CH1_CR_TC_RDWR_REG:
          Channel = ((Offset - MCHBAR_CH0_CR_TC_RDWR_REG) > 0) ? 1 : 0;
          IntChannelOut = &MrcIntData->Controller[0].Channel[Channel];
          IntChannelOut->MchbarTcRdWr.Data = Value;
          break;

        case MCHBAR_CH0_CR_TC_WRRD_REG:
        case MCHBAR_CH1_CR_TC_WRRD_REG:
          Channel = ((Offset - MCHBAR_CH0_CR_TC_WRRD_REG) > 0) ? 1 : 0;
          IntChannelOut = &MrcIntData->Controller[0].Channel[Channel];
          IntChannelOut->MchbarTcWrRd.Data = Value;

          break;

        case MCHBAR_CH0_CR_TC_WRWR_REG:
        case MCHBAR_CH1_CR_TC_WRWR_REG:
          Channel = ((Offset - MCHBAR_CH0_CR_TC_WRWR_REG) > 0) ? 1 : 0;
          IntChannelOut = &MrcIntData->Controller[0].Channel[Channel];
          IntChannelOut->MchbarTcWrWr.Data = Value;
          break;
        default:
          break;
      }
    }
  }

  // Apply Turnaround timings to ChannelOut structure from IntChannelOut
  MrcUpdateTatOutputs (MrcData);

  //
  // Per-byte registers
  //
  for (Index = 0; Index < (sizeof (SaveDataSaGvPerByte) / sizeof (SaveDataControlShort)); Index++) {
    RestoreItShort = &SaveDataSaGvPerByte[Index];
    for (Offset = RestoreItShort->StartMchbarOffset; Offset <= RestoreItShort->EndMchbarOffset; Offset += sizeof (UINT32)) {
      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        for (Byte = 0; Byte < MAX_SDRAM_IN_DIMM - 1; Byte++) {
          RegOffset =
            Offset + (DDRDATA0CH1_CR_TXTRAINRANK0_REG - DDRDATA0CH0_CR_TXTRAINRANK0_REG) * Channel +
            (DDRDATA1CH0_CR_TXTRAINRANK0_REG - DDRDATA0CH0_CR_TXTRAINRANK0_REG) * Byte;
          Value = *McRegister++;
          MrcWriteCR (MrcData, RegOffset, Value);
        }
      }
    }
  }

  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "SAGV section: Restored %d bytes\n", (McRegister - McRegisterStart) * 4);
  if ((UINT32) (McRegister - McRegisterStart) > MRC_REGISTER_COUNT_SAGV) {
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "ERROR: RegSaveHigh/Low overflow!\n");
    return mrcFail;
  }

  return mrcSuccess;
}

/**
  This function writes the previously determined training values back to the memory controller.
  We also have SAGV flow for S3/Warm/Fast boot here.

  @param[in] MrcData - Include all the MRC global data.

  @retval mrcSuccess if the memory controller write back completed with no errors, otherwise returns an error code.
**/
MrcStatus
MrcRestoreTrainingValues (
  IN     MrcParameters *const MrcData
  )
{
  const SaveDataControl       *RestoreIt;
  const SaveDataControlShort  *RestoreItShort;
  const MRC_FUNCTION    *MrcCall;
  const MrcInput        *Inputs;
  MrcDebug              *Debug;
  MrcIntOutput          *MrcIntData;
  MrcOutput             *Outputs;
  MrcSaveData           *SaveData;
  MrcStatus             Status;
  UINT32                *McRegister;
  UINT32                Offset;
  UINT32                RegOffset;
  UINT32                Index;
  UINT32                Value;
  UINT32                Channel;
  UINT32                Byte;

  Inputs   = &MrcData->Inputs;
  Outputs  = &MrcData->Outputs;
  Debug    = &Outputs->Debug;
  MrcCall  = Inputs->Call.Func;
  SaveData = &MrcData->Save.Data;
  MrcIntData  = ((MrcIntOutput *) (MrcData->IntOutputs.Internal));

  //
  // First restore the Common section
  //
  McRegister = SaveData->RegSaveCommon;
  for (Index = 0; Index < (sizeof (SaveDataCommon) / sizeof (SaveDataControl)); Index++) {
    RestoreIt = &SaveDataCommon[Index];
    for (Offset = RestoreIt->StartMchbarOffset; Offset <= RestoreIt->EndMchbarOffset; Offset += sizeof (UINT32)) {
      Value = *McRegister++;
      MrcWriteCR (MrcData, Offset, Value);
    }
  }
  //
  // Common per-byte registers
  //
  for (Index = 0; Index < (sizeof (SaveDataCommonPerByte) / sizeof (SaveDataControlShort)); Index++) {
    RestoreItShort = &SaveDataCommonPerByte[Index];
    for (Offset = RestoreItShort->StartMchbarOffset; Offset <= RestoreItShort->EndMchbarOffset; Offset += sizeof (UINT32)) {
      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        for (Byte = 0; Byte < MAX_SDRAM_IN_DIMM; Byte++) {
          RegOffset =
            Offset + (DDRDATA0CH1_CR_TXTRAINRANK0_REG - DDRDATA0CH0_CR_TXTRAINRANK0_REG) * Channel +
            (DDRDATA1CH0_CR_TXTRAINRANK0_REG - DDRDATA0CH0_CR_TXTRAINRANK0_REG) * Byte;
          Value = *McRegister++;
          MrcWriteCR (MrcData, RegOffset, Value);
        }
      }
    }
  }
  //
  // Portion of the ECC byte, per channel
  //
  for (Index = 0; Index < (sizeof (SaveDataSaGvPerByte) / sizeof (SaveDataControlShort)); Index++) {
    RestoreItShort = &SaveDataSaGvPerByte[Index];
    for (Offset = RestoreItShort->StartMchbarOffset; Offset <= RestoreItShort->EndMchbarOffset; Offset += sizeof (UINT32)) {
      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        RegOffset =
          Offset + (DDRDATA0CH1_CR_TXTRAINRANK0_REG - DDRDATA0CH0_CR_TXTRAINRANK0_REG) * Channel +
          (DDRDATA1CH0_CR_TXTRAINRANK0_REG - DDRDATA0CH0_CR_TXTRAINRANK0_REG) * 8;
        Value = *McRegister++;
        MrcWriteCR (MrcData, RegOffset, Value);
      }
    }
  }
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Common section: Restored %d bytes\n", (McRegister - SaveData->RegSaveCommon) * 4);
  if ((UINT32) (McRegister - SaveData->RegSaveCommon) > MRC_REGISTER_COUNT_COMMON) {
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "ERROR: RegSaveCommon overflow!\n");
    return mrcFail;
  }

  //
  // Now restore the SAGV section, RegSaveLow is used when SAGV is disabled
  //
  if ((Inputs->SaGv == MrcSaGvEnabled) && (MrcIntData->SaGvPoint == MrcSaGvPointHigh)) {
    McRegister = SaveData->RegSaveHigh;
  } else {
    McRegister = SaveData->RegSaveLow;
  }

  Status = MrcRestoreTrainingSaGv (MrcData, McRegister);
  if (Status != mrcSuccess) {
    return Status;
  }

  ForceRcomp (MrcData);

#ifdef UP_SERVER_FLAG
  if (Inputs->BoardType == btUpServer) {
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Restoring CLTM TSOD Values.\n");
    CltmTsodConfiguration (MrcData);
#ifdef MRC_DEBUG_PRINT
    MrcCltmPrintMchRegisters (MrcData);
#endif //MRC_DEBUG_PRINT
  }
#endif

#ifdef SSA_FLAG
  MrcSsaPopulateHostData (MrcData);
#endif // SSA_FLAG

  return mrcSuccess;
}

/**
  Calculates a CRC-32 of the specified data buffer.

  @param[in] Data     - Pointer to the data buffer.
  @param[in] DataSize - Size of the data buffer, in bytes.

  @retval The CRC-32 value.
**/
UINT32
MrcCalculateCrc32 (
  IN     const UINT8       *const Data,
  IN     const UINT32      DataSize
  )
{
  UINT32 i;
  UINT32 j;
  UINT32 crc;
  UINT32 CrcTable[256];

  crc = (UINT32) (-1);

  //
  // Initialize the CRC base table.
  //
  for (i = 0; i < 256; i++) {
    CrcTable[i] = i;
    for (j = 8; j > 0; j--) {
      CrcTable[i] = (CrcTable[i] & 1) ? (CrcTable[i] >> 1) ^ 0xEDB88320 : CrcTable[i] >> 1;
    }
  }
  //
  // Calculate the CRC.
  //
  for (i = 0; i < DataSize; i++) {
    crc = (crc >> 8) ^ CrcTable[ (UINT8) crc ^ (Data) [i]];
  }

  return ~crc;
}


#ifdef SSA_FLAG
/**
  Populates MRC host data from registers for SSA functions.

  @param[in, out] MrcData  - The MRC "global data" area.

  @retval Nothing.
**/
void
MrcSsaPopulateHostData (
  IN OUT MrcParameters *MrcData
  )
{
  MrcOutput           *Outputs;
  MrcControllerOut    *ControllerOut;
  MrcChannelOut       *ChannelOut;
  MrcIntOutput        *IntOutputs;
  MrcIntControllerOut *IntControllerOut;
  MrcIntChannelOut    *IntChannelOut;
  UINT8               Channel;
  UINT8               Group;
  UINT8               Rank;
  UINT8               Byte;
  UINT32              Offset;
  UINT32              RegValue;
  INT8                HostValue;
  DDRDATA0CH0_CR_RXTRAINRANK0_STRUCT         CrRxTrainRank;
  DDRDATA0CH0_CR_TXTRAINRANK0_STRUCT         CrTxTrainRank;
  DDRCLKCH0_CR_DDRCRCLKPICODE_STRUCT         ClkPiCode;

  Outputs          = &MrcData->Outputs;
  ControllerOut    = &Outputs->Controller[0];
  IntOutputs       = ((MrcIntOutput *) (MrcData->IntOutputs.Internal));
  IntControllerOut = &IntOutputs->Controller[0];

  //
  // CompCtl0, CompCtl1, DimmVref
  //
  Offset   = DDRCOMP_CR_DDRCRCOMPCTL0_REG;
  RegValue = MrcReadCR (MrcData, Offset);
  IntControllerOut->CompCtl0.Data = RegValue;

  Offset   = DDRCOMP_CR_DDRCRCOMPCTL1_REG;
  RegValue = MrcReadCR (MrcData, Offset);
  IntControllerOut->CompCtl1.Data = RegValue;

  Offset   = MrcGetOffsetVrefAdjust1 (MrcData, 0, 0);
  RegValue = MrcReadCR (MrcData, Offset);
  IntControllerOut->VrefAdjust1.Data = RegValue;

  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    ChannelOut    = &ControllerOut->Channel[Channel];
    IntChannelOut = &IntControllerOut->Channel[Channel];

    //
    // DqControl1, DqControl2, DataOffsetTrain, DataCompOffset
    //
    for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
      Offset   = MrcGetOffsetDataControl1 (MrcData, Channel, Byte);
      RegValue = MrcReadCR (MrcData, Offset);
      IntChannelOut->DqControl1[Byte].Data = RegValue;

      Offset   = MrcGetOffsetDataControl2 (MrcData, Channel, Byte);
      RegValue = MrcReadCR (MrcData, Offset);
      IntChannelOut->DqControl2[Byte].Data = RegValue;

      Offset   = MrcGetOffsetDataOffsetTrain (MrcData, Channel, Byte);
      RegValue = MrcReadCR (MrcData, Offset);
      ChannelOut->DataOffsetTrain[Byte] = RegValue;

      Offset   = MrcGetOffsetDataOffsetComp (MrcData, Channel, Byte);
      RegValue = MrcReadCR (MrcData, Offset);
      ChannelOut->DataCompOffset[Byte] = RegValue;
    }

    //
    // ClkPiCode
    //
    Offset =
      DDRCLKCH0_CR_DDRCRCLKPICODE_REG +
      ((DDRCLKCH1_CR_DDRCRCLKPICODE_REG - DDRCLKCH0_CR_DDRCRCLKPICODE_REG) * Channel);
    ClkPiCode.Data = MrcReadCR (MrcData, Offset);
    if (Outputs->DdrType == MRC_DDR_TYPE_LPDDR3) {
      for (Group = 0; Group < 2; Group++) {
        HostValue = (ClkPiCode.Data >> (DDRCLKCH0_CR_DDRCRCLKPICODE_PiSettingRank0_WID * Group)) &
          DDRCLKCH0_CR_DDRCRCLKPICODE_PiSettingRank0_MSK;
        ChannelOut->ClkPiCode[Group] = HostValue;
      }
    } else {
      for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
        HostValue = (ClkPiCode.Data >> (DDRCLKCH0_CR_DDRCRCLKPICODE_PiSettingRank0_WID * Rank)) &
          DDRCLKCH0_CR_DDRCRCLKPICODE_PiSettingRank0_MSK;
        ChannelOut->ClkPiCode[Rank] = HostValue;
      }
    }

    //
    // RcvEn, RxDqP, RxDqN, RxEq, RxVref, TxEq, TxDqs, TxDq
    //
    for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
      for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
        Offset = DDRDATA0CH0_CR_RXTRAINRANK0_REG +
          ((DDRDATA0CH1_CR_RXTRAINRANK0_REG - DDRDATA0CH0_CR_RXTRAINRANK0_REG) * Channel) +
          ((DDRDATA0CH0_CR_RXTRAINRANK1_REG - DDRDATA0CH0_CR_RXTRAINRANK0_REG) * Rank) +
          ((DDRDATA1CH0_CR_RXTRAINRANK0_REG - DDRDATA0CH0_CR_RXTRAINRANK0_REG) * Byte);
        CrRxTrainRank.Data = MrcReadCR (MrcData, Offset);
        ChannelOut->RcvEn[Rank][Byte]  = (UINT16) CrRxTrainRank.Bits.RxRcvEnPi;
        ChannelOut->RxDqsP[Rank][Byte] = (UINT8) CrRxTrainRank.Bits.RxDqsPPi;
        ChannelOut->RxDqsN[Rank][Byte] = (UINT8) CrRxTrainRank.Bits.RxDqsNPi;
        ChannelOut->RxEq[Rank][Byte]   = (UINT8) CrRxTrainRank.Bits.RxEq;
        if (MrcRankInChannelExist (MrcData, Rank, Channel)) {
          ChannelOut->RxVref[Byte] = (UINT8) CrRxTrainRank.Bits.RxVref;
        }

        Offset = DDRDATA0CH0_CR_TXTRAINRANK0_REG +
          ((DDRDATA0CH1_CR_TXTRAINRANK0_REG - DDRDATA0CH0_CR_TXTRAINRANK0_REG) * Channel) +
          ((DDRDATA0CH0_CR_TXTRAINRANK1_REG - DDRDATA0CH0_CR_TXTRAINRANK0_REG) * Rank) +
          ((DDRDATA1CH0_CR_TXTRAINRANK0_REG - DDRDATA0CH0_CR_TXTRAINRANK0_REG) * Byte);
        CrTxTrainRank.Data = MrcReadCR (MrcData, Offset);
        ChannelOut->TxEq[Rank][Byte]  = (UINT8) CrTxTrainRank.Bits.TxEqualization;
        ChannelOut->TxDqs[Rank][Byte] = (UINT16) CrTxTrainRank.Bits.TxDqsDelay;
        ChannelOut->TxDq[Rank][Byte]  = (UINT16) CrTxTrainRank.Bits.TxDqDelay;
      }
    }
  }

  return;
}
#endif // SSA_FLAG

#ifdef UP_SERVER_FLAG
#ifdef MRC_DEBUG_PRINT
/**
  This function Print the CLTM related registers.

  @param MrcData - Include all the MRC global data.

  @retval None.
**/
void
MrcCltmPrintMchRegisters (
  MrcParameters          *MrcData
  )
{
  MrcOutput               *Outputs;
  MrcDebug                *Debug;

  Outputs                 = &MrcData->Outputs;
  Debug                   = &Outputs->Debug;

  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "UP Power weight Energy registers...\n");
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "DDR_ENERGY_SCALEFACTOR %Xh: %Xh \n", PCU_CR_DDR_ENERGY_SCALEFACTOR_PCU_REG, MrcReadCR (MrcData, PCU_CR_DDR_ENERGY_SCALEFACTOR_PCU_REG));
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "MCHBAR_CH0_CR_PM_DIMM_RD_ENERGY_REG %Xh: %Xh \n", MCHBAR_CH0_CR_PM_DIMM_RD_ENERGY_REG, MrcReadCR (MrcData, MCHBAR_CH0_CR_PM_DIMM_RD_ENERGY_REG));
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "MCHBAR_CH1_CR_PM_DIMM_RD_ENERGY_REG %Xh: %Xh \n", MCHBAR_CH1_CR_PM_DIMM_RD_ENERGY_REG, MrcReadCR (MrcData, MCHBAR_CH1_CR_PM_DIMM_RD_ENERGY_REG));
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "MCHBAR_CH0_CR_PM_DIMM_WR_ENERGY_REG %Xh: %Xh \n", MCHBAR_CH0_CR_PM_DIMM_WR_ENERGY_REG, MrcReadCR (MrcData, MCHBAR_CH0_CR_PM_DIMM_WR_ENERGY_REG));
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "MCHBAR_CH1_CR_PM_DIMM_WR_ENERGY_REG %Xh: %Xh \n", MCHBAR_CH1_CR_PM_DIMM_WR_ENERGY_REG, MrcReadCR (MrcData, MCHBAR_CH1_CR_PM_DIMM_WR_ENERGY_REG));
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "MCHBAR_CH0_CR_PM_DIMM_ACT_ENERGY_REG %Xh: %Xh \n", MCHBAR_CH0_CR_PM_DIMM_ACT_ENERGY_REG, MrcReadCR (MrcData, MCHBAR_CH0_CR_PM_DIMM_ACT_ENERGY_REG));
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "MCHBAR_CH1_CR_PM_DIMM_ACT_ENERGY_REG %Xh: %Xh \n", MCHBAR_CH1_CR_PM_DIMM_ACT_ENERGY_REG, MrcReadCR (MrcData, MCHBAR_CH1_CR_PM_DIMM_ACT_ENERGY_REG));
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "MCHBAR_CH0_CR_PM_DIMM_IDLE_ENERGY_REG %Xh: %Xh \n", MCHBAR_CH0_CR_PM_DIMM_IDLE_ENERGY_REG, MrcReadCR (MrcData, MCHBAR_CH0_CR_PM_DIMM_IDLE_ENERGY_REG));
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "MCHBAR_CH1_CR_PM_DIMM_IDLE_ENERGY_REG %Xh: %Xh \n", MCHBAR_CH1_CR_PM_DIMM_IDLE_ENERGY_REG, MrcReadCR (MrcData, MCHBAR_CH1_CR_PM_DIMM_IDLE_ENERGY_REG));
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "MCHBAR_CH0_CR_PM_DIMM_PD_ENERGY_REG %Xh: %Xh \n", MCHBAR_CH0_CR_PM_DIMM_PD_ENERGY_REG, MrcReadCR (MrcData, MCHBAR_CH0_CR_PM_DIMM_PD_ENERGY_REG));
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "MCHBAR_CH1_CR_PM_DIMM_PD_ENERGY_REG %Xh: %Xh \n", MCHBAR_CH1_CR_PM_DIMM_PD_ENERGY_REG, MrcReadCR (MrcData, MCHBAR_CH1_CR_PM_DIMM_PD_ENERGY_REG));

  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Power budget registers ...\n");

  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "DDR_WARM_BUDGET_CH0 %Xh: %Xh \n", PCU_CR_DDR_WARM_BUDGET_CH0_PCU_REG, MrcReadCR (MrcData, PCU_CR_DDR_WARM_BUDGET_CH0_PCU_REG));
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "DDR_WARM_BUDGET_CH1 %Xh: %Xh \n", PCU_CR_DDR_WARM_BUDGET_CH1_PCU_REG, MrcReadCR (MrcData, PCU_CR_DDR_WARM_BUDGET_CH1_PCU_REG));
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "DDR_HOT_BUDGET_CH0 %Xh: %Xh \n", PCU_CR_DDR_HOT_BUDGET_CH0_PCU_REG, MrcReadCR (MrcData, PCU_CR_DDR_HOT_BUDGET_CH0_PCU_REG));
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "DDR_HOT_BUDGET_CH1 %Xh: %Xh \n", PCU_CR_DDR_HOT_BUDGET_CH1_PCU_REG, MrcReadCR (MrcData, PCU_CR_DDR_HOT_BUDGET_CH1_PCU_REG));


  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Thermal Thresholds registers...\n");
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "DDR_WARM_THRESHOLD_CH0 %Xh: %Xh \n", PCU_CR_DDR_WARM_THRESHOLD_CH0_PCU_REG, MrcReadCR (MrcData, PCU_CR_DDR_WARM_THRESHOLD_CH0_PCU_REG));
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "DDR_WARM_THRESHOLD_CH1 %Xh: %Xh \n", PCU_CR_DDR_WARM_THRESHOLD_CH1_PCU_REG, MrcReadCR (MrcData, PCU_CR_DDR_WARM_THRESHOLD_CH1_PCU_REG));
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "DDR_HOT_THRESHOLD_CH0 %Xh: %Xh \n", PCU_CR_DDR_HOT_THRESHOLD_CH0_PCU_REG, MrcReadCR (MrcData, PCU_CR_DDR_HOT_THRESHOLD_CH0_PCU_REG));
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "DDR_HOT_THRESHOLD_CH1 %Xh: %Xh \n", PCU_CR_DDR_HOT_THRESHOLD_CH1_PCU_REG, MrcReadCR (MrcData, PCU_CR_DDR_HOT_THRESHOLD_CH1_PCU_REG));

  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "CLTM Configuration registers...\n");
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "DDR_PTM_CTL %Xh: %Xh \n", PCU_CR_DDR_PTM_CTL_PCU_REG, MrcReadCR (MrcData, PCU_CR_DDR_PTM_CTL_PCU_REG));
}
#endif //MRC_DEBUG_PRINT
#endif
