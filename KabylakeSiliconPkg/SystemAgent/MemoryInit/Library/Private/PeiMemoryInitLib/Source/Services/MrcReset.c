/** @file
  The functions in this file implement the DDR3 reset sequence.

 @copyright
  INTEL CONFIDENTIAL
  Copyright 1999 - 2017 Intel Corporation.

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

#include "MrcReset.h"

/**
  Perform full JEDEC reset and init sequence.

  @param[in] MrcData - Include all MRC global data.

  @retval MrcStatus - mrcSuccess or reason for failure.
**/
MrcStatus
MrcResetSequence (
  IN MrcParameters *const MrcData
  )
{
  MrcStatus   Status;
  MrcInput    *Inputs;
  MrcOutput   *Outputs;
  MrcDebug    *Debug;
  MrcDdrType  DdrType;
  BOOLEAN     Lpddr;
  UINT8       Channel;
  UINT32      Offset;
  DDRCTLCH0_CR_DDRCRCTLRANKSUSED_STRUCT CtlDdrCrCtlRanksUsed;
  UINT8        Value;
  UINT8        tCCD_L;
  BOOLEAN      Restore;
  MrcFrequency DdrFreq;

  Inputs  = &MrcData->Inputs;
  Outputs = &MrcData->Outputs;
  Debug   = &Outputs->Debug;
  DdrType = Outputs->DdrType;

  //
  // Start with an IO reset
  //
  Status = IoReset (MrcData);
  if (mrcSuccess == Status) {
    //
    // Check if rcomp is done and the ddr ready to use
    //
    Status = CheckFirstRcompDone (MrcData);
    if (mrcSuccess == Status) {
      //
      // Perform jedec reset.
      //
      // If RTT_NOM is to be enabled in MR1, the ODT input signal must be statically held LOW
      // in our system RTT_NOM is always enable.
      // Force ODT low
      //
      MrcWriteCR (MrcData, MCSCHEDS_CR_REUT_CH_MISC_ODT_CTRL_REG, MCSCHEDS_CR_REUT_CH_MISC_ODT_CTRL_ODT_Override_MAX);

      //
      // Check if LPDDR3 memory is used
      //
      Lpddr = (DdrType == MRC_DDR_TYPE_LPDDR3);

      if (Lpddr) {
        Status = MrcJedecResetLpddr3 (MrcData);
        //
        // The rest of JEDEC init will be done in a separate step after Early Command Training,
        // and ECT will set the LpddrEctDone flag.
        //
        if (Outputs->LpddrEctDone) {
          Status = MrcJedecInitLpddr3 (MrcData);
        }
        MrcWriteCR (MrcData, MCSCHEDS_CR_REUT_CH_MISC_ODT_CTRL_REG, 0);
        return Status;
      }
      MrcJedecReset (MrcData);

      //
      // Initialize the DIMM MRS registers.
      //
#if (SUPPORT_DDR4 == SUPPORT)
      if (DdrType == MRC_DDR_TYPE_DDR4) {
        DdrFreq = Outputs->Frequency;
        //
        // MR3 A10:A9 Write Command Latency when CRC and DM are both enabled
        //
        if (DdrFreq <= f1600) {
          Value = 0;
        } else if (DdrFreq <= f2400) {
          Value = 1;
        } else {
          Value = 2;
        }
        //
        // Step 6 - Set the MR3 for each rank
        // MR3 A[3] = 0 = 1/2 Rate (Geardown Mode)
        // MR3 A[4] = 0 = Disable  (Per DRAM Addressability)
        //
        Status = MrcSetMR3_DDR4 (MrcData, 0, 0, 0, 0, 0, 0, 0, Value);
        if (Status == mrcSuccess) {

          Restore = Outputs->JedecInitDone;
          //
          // tCCD_L (0 = 4nCK, 1 = 5nCK...)
          //
          if (DdrFreq <= f1333) {
            tCCD_L = tCCD_L_1333_AND_LOWER;
          } else if (DdrFreq <= f1867) {
            tCCD_L = tCCD_L_1867;
          } else if (DdrFreq <= f2400) {
            tCCD_L = tCCD_L_2400;
          } else {
            tCCD_L = tCCD_L_ABOVE_2400;
          }
          tCCD_L -= 4;

          //
          // Step 7 - Set the MR6 for each rank
          //
          Status = MrcSetMR6_DDR4 (MrcData, 0, 0, 0, tCCD_L, Restore);
          if (Status == mrcSuccess) {
            //
            // Step 8 - Set the MR5 for each rank
            // MR5 A[2:0] = 000 = Disable (C/A Parity Latency Mode)
            //
            Status = MrcSetMR5_DDR4 (MrcData, 0, 0, 0, 1, 0, 0, 0, 0);
            if (Status == mrcSuccess) {
              //
              // Step 9 - Set the MR4 for each rank
              // MR4 A[1] = 0 = Disable     (Maximum Power Down Mode)
              // MR4 A[8:6] = 000 = Disable (CS to CMD/ADDR Latency)
              //
              Status = MrcSetMR4_DDR4 (MrcData, 0, 0, 0, 0, 0, 0, 0, 0, 0);
              if (Status == mrcSuccess) {
                //
                // Step 10 - Set the MR2 for each rank
                //
                Status = MrcSetMR2_DDR4 (MrcData, 0);
                if (Status == mrcSuccess) {
                  //
                  // Step 11 - Set the MR1 for each rank
                  //
                  Status = MrcSetMR1_DDR4 (MrcData, 1, DDR4_ODIC_34, 0, 0, 0);
                  if (Status == mrcSuccess) {
                    //
                    // Step 12 - Set the MR0 for each rank
                    //
                    Status = MrcSetMR0_DDR4 (MrcData, 0, 0, 0, 1);
                    if (Status == mrcSuccess) {
                      //
                      // Step 13 - Issue ZQCL command to start ZQ calibration
                      //
                      Status = MrcIssueZQ (MrcData, 0x3, MRC_ZQ_INIT);
                      if (Status == mrcSuccess) {
                        //
                        // Program DIMM Vref in MR6
                        //
                        if (!Outputs->RestoreMRs) { // program middle range - 68.45% Vdd = 820mV
                          MrcSetDefaultTxVrefDdr4 (MrcData);
                        } else { // restore
                          //
                          // First program average DQ Vref using non-PDA access.
                          // Then program the per-device DQ Vref using PDA
                          //
                          ChangeMargin (MrcData, WrV, 0, 0, 1, 0, 0, 0, 0, 0, 0, MrcRegFileCurrent);
                          ChangeMargin (MrcData, WrV, 0, 0, 1, 0, 0, 0x1FF, 0, 0, 0, MrcRegFileCurrent);
                        }
                      } //Step 13 - ZQCL
                    } //Step 12 - MR0
                  } //Step 11 - MR1
                } //Step 10 - MR2
              } //Step 9 - MR4
            } //Step 8 - MR5
          } //Step 7 - MR6
        } //Step 6 - MR3
      } else
#endif // SUPPORT_DDR4
      {
        //
        // Step 6 - Set the MR2 for each rank
        //
        Status = MrcSetMR2 (MrcData, 0);
        if (Status == mrcSuccess) {
          //
          // Step 7 - Set the MR3 for each rank
          //
          Status = MrcSetMR3 (MrcData, 0, 0);
          if (Status == mrcSuccess) {
            //
            // Step 8 - Set the MR1 for each rank
            //
            Status = MrcSetMR1 (MrcData, 0, DIMMRON, 0, 0, 0, 0);
            if (Status == mrcSuccess) {
              //
              // Step 9 - Set the MR0 for each rank
              //
              Status = MrcSetMR0 (MrcData, 0, 0, 0, 1);
              if (Status == mrcSuccess) {
                //
                // Step 10 - Issue ZQCL command to start ZQ calibration
                //
                Status = MrcIssueZQ (MrcData, 0x3, MRC_ZQ_INIT);

              }
            }
          }
        }
      }
      MrcWriteCR (MrcData, MCSCHEDS_CR_REUT_CH_MISC_ODT_CTRL_REG, 0);
      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        if (!MrcChannelExist (Outputs, Channel)) {
          continue;
        }

        if (!Outputs->JedecInitDone) {
          //
          // We can disable DIMM ODT at the end of the first JEDEC Init, if ODT is not used.
          // ODT pin must be stable 0 or 1 during JEDEC reset/init.
          //
          Offset = DDRCTLCH0_CR_DDRCRCTLRANKSUSED_REG +
            ((DDRCTLCH1_CR_DDRCRCTLRANKSUSED_REG - DDRCTLCH0_CR_DDRCRCTLRANKSUSED_REG) * Channel);
          CtlDdrCrCtlRanksUsed.Data = MrcReadCR (MrcData, Offset);
          if ((DdrType == MRC_DDR_TYPE_DDR3) && !Inputs->Ddr3DramOdt) {
            CtlDdrCrCtlRanksUsed.Bits.OdtDisable = 3;
          }
          if ((DdrType == MRC_DDR_TYPE_DDR4) && !Inputs->Ddr4DramOdt) {
            CtlDdrCrCtlRanksUsed.Bits.OdtDisable = 3;
          }
          MrcWriteCR (MrcData, Offset, CtlDdrCrCtlRanksUsed.Data);
          MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "DDRCTLCH%d_CR_DDRCRCTLRANKSUSED = 0x%X\n", Channel, CtlDdrCrCtlRanksUsed.Data);
        }
      } // for Channel
      Outputs->JedecInitDone = TRUE;
    }
  }
  //
  // Set flag to restore from host structure instead from look-up table
  //
  Outputs->RestoreMRs = TRUE;

  return Status;
}

/**
  Perform JEDEC DIMM reset sequence.

  @param[in] MrcData - Include all MRC global data.

  @retval - none
**/
void
MrcJedecReset (
  IN MrcParameters *const MrcData
  )
{
  MrcInput                                *Inputs;
  MRC_FUNCTION                            *MrcCall;
  MrcOutput                               *Outputs;
  MrcControllerOut                        *ControllerOut;
  MrcVddSelect                            VddVoltage;
  UINT32                                  Offset;
  UINT32                                  VddSettleWaitTime;
  UINT32                                  PciEBar;
  UINT8                                   Channel;
  MCDECS_CR_MC_INIT_STATE_G_MCMAIN_STRUCT McInitStateG;
  MCHBAR_CH0_CR_REUT_CH_MISC_CKE_CTRL_STRUCT MiscCkeCtrl;

  Inputs            = &MrcData->Inputs;
  MrcCall           = Inputs->Call.Func;
  Outputs           = &MrcData->Outputs;
  ControllerOut     = &Outputs->Controller[0];
  VddSettleWaitTime = 200; // 200us is the minimum w/o the delay needed to allow for DDR3L Change
  PciEBar           = Inputs->PciEBaseAddress;

  //
  // De-assert DRAM RESET# signal
  //
  MrcCall->MrcDramReset (PciEBar, 1);

  //
  // Force CKE low
  //
  MrcWriteCR (MrcData, MCSCHEDS_CR_REUT_CH_MISC_CKE_CTRL_REG, MCSCHEDS_CR_REUT_CH_MISC_CKE_CTRL_CKE_Override_MAX);

  //
  // Assert DIMM reset signal - step 1
  //
  MrcCall->MrcDramReset (PciEBar, 0);

  //
  // Check and Switch DDR3 voltage
  //
  VddVoltage = Outputs->VddVoltage[Inputs->MemoryProfile];
  if ((VddVoltage != VDD_INVALID) && (Outputs->VddVoltageDone == FALSE)) {
    MrcVDDVoltageCheckAndSwitch (MrcData, VddVoltage, &VddSettleWaitTime);
  }
  //
  // delay 200 micro sec as jedec ask
  //
  if (Outputs->JedecInitDone) {
    VddSettleWaitTime = 1;  // tPW_RESET = 1us
  }
  MrcWait (MrcData, VddSettleWaitTime * HPET_1US);

  //
  // De-assert DIMM reset signal - step 2
  //
  MrcCall->MrcDramReset (PciEBar, 1);

  //
  // delay 500 micro sec as jedec ask
  //
  MrcWait (MrcData, 500 * HPET_1US);


  //
  // Enable the DCLK - step 3
  //
  McInitStateG.Data = MrcReadCR (MrcData, MCDECS_CR_MC_INIT_STATE_G_MCMAIN_REG);
  McInitStateG.Bits.dclk_enable = 1;
  MrcWriteCR (MrcData, MCDECS_CR_MC_INIT_STATE_G_MCMAIN_REG, McInitStateG.Data);

  //
  // wait the 20 nano sec tCKSRX .
  //
  MrcWait (MrcData, 1 * HPET_MIN);  // Minimum is 69.84 ns

  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    if (MrcChannelExist (Outputs, Channel)) {

      //
      // Set the Valid CKE - step 4
      //
      Offset = MCHBAR_CH0_CR_REUT_CH_MISC_CKE_CTRL_REG +
        ((MCHBAR_CH1_CR_REUT_CH_MISC_CKE_CTRL_REG - MCHBAR_CH0_CR_REUT_CH_MISC_CKE_CTRL_REG) * Channel);
      MiscCkeCtrl.Data = MrcReadCR (MrcData, Offset);
      MiscCkeCtrl.Bits.CKE_On = ControllerOut->Channel[Channel].ValidRankBitMask;
      MrcWriteCR (MrcData, Offset, MiscCkeCtrl.Data);
    }
  }
  //
  // Wait minimum of Reset CKE Exit time, tXPR - Step 5
  // tXPR = max (5 tCK, tRFC(min) + 10ns)
  // tRFC is 350ns for 8Gb devices
  //
  MrcWait (MrcData, 1 * HPET_1US);

  return;
}

/**
  Perform JEDEC LPDDR3 DIMM reset sequence.

  @param[in] MrcData - Include all MRC global data.

  @retval mrcSuccess if succeeded
**/
MrcStatus
MrcJedecResetLpddr3 (
  IN MrcParameters *const MrcData
  )
{
  MrcStatus                               Status;
  MrcOutput                               *Outputs;
  MrcControllerOut                        *ControllerOut;
  UINT32                                  Offset;
  UINT32                                  tInit3;
  UINT32                                  tInit5;
  UINT8                                   Channel;
  UINT8                                   Rank;
  MCDECS_CR_MC_INIT_STATE_G_MCMAIN_STRUCT McInitStateG;
  MCHBAR_CH0_CR_REUT_CH_MISC_CKE_CTRL_STRUCT MiscCkeCtrl;
  MrcInput                                *Inputs;
  BOOLEAN                                 Cmd2nStretch;

  Outputs       = &MrcData->Outputs;
  ControllerOut = &Outputs->Controller[0];
  Inputs        = &MrcData->Inputs;
  Cmd2nStretch  = (Inputs->BootMode == bmFast) ? FALSE : TRUE;

  tInit3 = 200 * HPET_1US;
  tInit5 =  10 * HPET_1US;

  //
  // Force CKE low
  //
  MrcWriteCR (MrcData, MCSCHEDS_CR_REUT_CH_MISC_CKE_CTRL_REG, MCSCHEDS_CR_REUT_CH_MISC_CKE_CTRL_CKE_Override_MAX);

  //
  // Wait till voltages are stable
  // We don't change Vdd on LPDDR3, it's supposed to be 1.2v on the platform.
  //

  //
  // Enable the DCLK, disable refreshes
  //
  McInitStateG.Data = MrcReadCR (MrcData, MCDECS_CR_MC_INIT_STATE_G_MCMAIN_REG);
  McInitStateG.Bits.dclk_enable = 1;
  McInitStateG.Bits.refresh_enable = 0;
  MrcWriteCR (MrcData, MCDECS_CR_MC_INIT_STATE_G_MCMAIN_REG, McInitStateG.Data);

  //
  // Wait 20ns before CKE goes high
  //
  MrcWait (MrcData, 1 * HPET_MIN);  // Minimum is 69.84 ns

  //
  // Force CKE high on populated ranks
  //
  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    if (MrcChannelExist (Outputs, Channel)) {

      //
      // Set the Valid CKE
      //
      Offset = MCHBAR_CH0_CR_REUT_CH_MISC_CKE_CTRL_REG +
        ((MCHBAR_CH1_CR_REUT_CH_MISC_CKE_CTRL_REG - MCHBAR_CH0_CR_REUT_CH_MISC_CKE_CTRL_REG) * Channel);
      MiscCkeCtrl.Data = MrcReadCR (MrcData, Offset);
      MiscCkeCtrl.Bits.CKE_On = ControllerOut->Channel[Channel].ValidCkeBitMask;
      MrcWriteCR (MrcData, Offset, MiscCkeCtrl.Data);
    }
  }
  //
  // Delay 200 micro sec per JEDEC requirement
  // tINIT3 - minimum idle time after first CKE assertion
  //
  MrcWait (MrcData, tInit3);

  //
  // Send the RESET MRW command to populated ranks
  //
  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    if (MrcChannelExist (Outputs, Channel)) {
      for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
        if (MrcRankInChannelExist (MrcData, Rank, Channel)) {
          if (Outputs->LpddrEctDone) {
            //
            // Issue a PRECHARGE ALL command to put all banks to idle state.
            // MRW can only be issued when all banks are idle.
            //
            MrcIssuePrechargeAll (MrcData, Channel, 1 << Rank);
            MrcWait (MrcData, 1 * HPET_1US);
          }

          Status = MrcIssueMrw (
                     MrcData,
                     Channel,
                     Rank,
                     0x3F, // Address = 63
                     0xFC, // Data is selected so that High and Low phases of CA[9:0] are equal
                     TRUE, // InitMrw
                     Cmd2nStretch, // ChipSelect2N
                     TRUE  // DebugPrint
                     );
          if (Status != mrcSuccess) {
            return Status;
          }
        }
      }
    }
  }
  //
  // tINIT5 - Maximum duration of device auto initialization = 10 us
  //
  MrcWait (MrcData, tInit5);

  return mrcSuccess;
}

typedef struct _MRC_LPDDR_MR_DATA {
  UINT8 Address;
  UINT8 Data;
} MRC_LPDDR_MR_DATA;

/**
  Perform JEDEC LPDDR3 DIMM init sequence.
  1. ZQ Calibration
  2. Program MR2, MR1, MR3, MR11

  @param[in] MrcData - Include all MRC global data.

  @retval mrcSuccess if succeeded
**/
MrcStatus
MrcJedecInitLpddr3 (
  IN MrcParameters *const MrcData
  )
{
  MrcStatus         Status;
  MrcInput          *Inputs;
  MrcOutput         *Outputs;
  MrcDebug          *Debug;
  MrcControllerOut  *ControllerOut;
  MrcChannelOut     *ChannelOut;
  UINT8             Channel;
  UINT8             Rank;
  UINT32            MrIndex;
  UINT8             MrData;
  UINT32            Index;
  UINT32            Offset;
  UINT8             Mr11Temp;
  DDRCTLCH0_CR_DDRCRCTLRANKSUSED_STRUCT CtlDdrCrCtlRanksUsed;
  MRC_LPDDR_MR_DATA MrTable[] = {
    {  2, 0x40 }, // MR2:  nWRE = 1, RL & WL depend on frequency
    {  1, 0x43 }, // MR1:  BL = BL8, nWR = 12
    {  3, 0x01 }, // MR3:  DS = 34.3 Ohm
    { 11, 0x00 }  // MR11: ODT
  };

  Outputs       = &MrcData->Outputs;
  Inputs        = &MrcData->Inputs;
  Debug         = &Outputs->Debug;
  ControllerOut = &Outputs->Controller[0];

  //
  // Issue ZQ Init calibration on all channels / ranks
  //
  Status = MrcIssueZQ (MrcData, 0x3, MRC_ZQ_INIT);
  if (Status != mrcSuccess) {
    return Status;
  }

  //
  // At 1067 the TC_ODT.tCWL must be at least 5 on SKL,
  // so we start from RL=9 / WL=5 option in MR2 WL Set A (f1200).
  //
  // We will decrement WL on MC, so start from RL=10 / WL=6 option in MR2 WL Set A (f1333).

  //if (Outputs->Frequency <= f800) {
  //  MrData = 0x14;
  //} else if (Outputs->Frequency <= f1067) {
  //  MrData = 0x16;
  //} else  if (Outputs->Frequency <= f1200) {
  //  MrData = 0x17;
  //} else

  if (Outputs->Frequency <= f1333) {
    MrData = 0x18;
  } else if (Outputs->Frequency <= f1600) {
    MrData = 0x1A;
  } else if (Outputs->Frequency <= f1867) {
    MrData = 0x1C;
  } else if (Outputs->Frequency <= f2133) {
    MrData = 0x1E;
  } else {
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "MrcJedecInitLpddr3: Invalid LPDDR frequency!\n");
    return mrcFrequencyError;
  }
  if (Outputs->LpddrMemWriteLatencySet) {
    //WL Mem Set B
    MrData |= 0x40;
  }

  MrTable[0].Data = MrData;  // MR2

  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    if (!MrcChannelExist (Outputs, Channel)) {
      continue;
    }

    ChannelOut = &ControllerOut->Channel[Channel];
    for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
      if (MrcRankInChannelExist (MrcData, Rank, Channel) == 0) {
        continue;
      }

      if ((Rank == 0) && Outputs->LpddrDramOdt) {
        //
        // Enable PD Control on Rank 0 only if we have 2 ranks and ODT is used
        //
        if (MrcRankInChannelExist (MrcData, 1, Channel)) {
          Mr11Temp = 0x4 | MrTable[3].Data;  // MR11, ODT Enabled, PD Control = 1
        } else {
          Mr11Temp = MrTable[3].Data;  // MR11, ODT Enabled, PD Control = 0
        }
      } else {
        Mr11Temp = 0;       // MR11, ODT Disabled
      }

      //
      // Send out all the MR commands from the table
      //
      for (Index = 0; Index < sizeof (MrTable) / sizeof (MrTable[0]); ++Index) {
        MrIndex = MrTable[Index].Address;

        if (Outputs->RestoreMRs) {
          if (MrIndex < MAX_MR_IN_DIMM) {
            MrData = (UINT8) ChannelOut->Dimm[0].Rank[Rank % 2].MR[MrIndex];
          } else {
            MrData = (UINT8) ChannelOut->Dimm[0].Rank[Rank % 2].MR11;
          }
        } else {
          //
          // Save the MR value in the global struct
          //
          MrData  = MrTable[Index].Data;

          if (MrIndex < MAX_MR_IN_DIMM) {
            ChannelOut->Dimm[0].Rank[Rank % 2].MR[MrIndex] = MrData;
          } else if (MrIndex == mrMR11) {
            ChannelOut->Dimm[0].Rank[Rank % 2].MR11 = MrData = Mr11Temp;
          }
        }

        Status = MrcIssueMrw (
                   MrcData,
                   Channel,
                   Rank,
                   MrIndex,
                   MrData,
                   FALSE,  // InitMrw
                   FALSE,  // ChipSelect2N
                   TRUE    // DebugPrint
                   );
        if (Status != mrcSuccess) {
          return Status;
        }
      }
      //
      // @todo: Read MR8 (compare to SPD values) - optional step
      //
    }  // for Rank

    if (!Outputs->JedecInitDone) {
      //
      // We can disable DIMM ODT at the end of the first JEDEC Init, if ODT is not used.
      // ODT pin must be stable 0 or 1 during JEDEC reset/init.
      //
      Offset = DDRCTLCH0_CR_DDRCRCTLRANKSUSED_REG +
        ((DDRCTLCH1_CR_DDRCRCTLRANKSUSED_REG - DDRCTLCH0_CR_DDRCRCTLRANKSUSED_REG) * Channel);
      CtlDdrCrCtlRanksUsed.Data = MrcReadCR (MrcData, Offset);
      if (Outputs->LpddrDramOdt) {
        //
        // ODT is used on rank 0
        //
        CtlDdrCrCtlRanksUsed.Bits.OdtDisable = 2;
      } else {
        CtlDdrCrCtlRanksUsed.Bits.OdtDisable = 3;
      }
      MrcWriteCR (MrcData, Offset, CtlDdrCrCtlRanksUsed.Data);
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "DDRCTLCH%d_CR_DDRCRCTLRANKSUSED = 0x%X\n", Channel, CtlDdrCrCtlRanksUsed.Data);
    }
  } // for Channel

  Outputs->JedecInitDone = TRUE;
  Outputs->RestoreMRs    = TRUE;
  return Status;
}


/**
  Wait in a loop until the first RCOMP has been completed.
  MRC should wait until this bit is set before executing any DDR command.

  @param[in] MrcData - Include all MRC global data.

  @retval mrcDeviceBusy - On Rcomp completion timeout.
  @retval mrcSuccess    - On Rcomp completion.
**/
MrcStatus
CheckFirstRcompDone (
  IN MrcParameters *const MrcData
  )
{
  const MRC_FUNCTION                  *MrcCall;
  MCDECS_CR_RCOMP_TIMER_MCMAIN_STRUCT CrRcompTimer;
  BOOLEAN                             Busy;
  UINT64                              Timeout;

  MrcCall = MrcData->Inputs.Call.Func;
  Timeout = MrcCall->MrcGetCpuTime (MrcData) + 10000; // 10 seconds timeout

  do {
    CrRcompTimer.Data = MrcReadCR (MrcData, MCDECS_CR_RCOMP_TIMER_MCMAIN_REG);
    Busy              = (0 == CrRcompTimer.Bits.First_Rcomp_done) ? TRUE : FALSE;
  } while (Busy && (MrcCall->MrcGetCpuTime (MrcData) < Timeout));

  return ((Busy) ? mrcDeviceBusy : mrcSuccess);
}

/**
  Perform the required steps to exit self refresh in S3/Warm reset:
   1. Download the Read Reg File for all populated ranks.
   2. Set MCHBAR_CHx_CR_MC_INIT_STATE.SRX_reset to 1.
    - MRC does not need to pull DIMMs out of self-refresh by
      asserting CKE high, and issue ZQ Long.
    - MC will do these steps automatically when MRC will switch
      it to Normal mode.

  @param[in] MrcData - Include all MRC global data.

  @retval mrcSuccess
**/
MrcStatus
MrcSelfRefreshExit (
  IN MrcParameters *const MrcData
  )
{
  const MrcOutput *Outputs;
  MrcDdrType      DdrType;
  UINT32          Offset;
  UINT8           Channel;
  UINT8           Rank;
  BOOLEAN         Lpddr3;
  BOOLEAN         Ddr4;
  DDRDATACH0_CR_DDRCRDATACONTROL0_STRUCT            DdrCrDataControl0;
  MCHBAR_CH0_CR_MC_INIT_STATE_STRUCT                McInitState;
  MCHBAR_CH0_CR_LPDDR_MR4_RANK_TEMPERATURE_STRUCT   LpddrTemperature;
  MCHBAR_CH0_CR_DDR4_MPR_RANK_TEMPERATURE_STRUCT    Ddr4Temprature;

  Outputs = &MrcData->Outputs;
  DdrType = Outputs->DdrType;
  Ddr4    = (DdrType == MRC_DDR_TYPE_DDR4);
  Lpddr3  = (DdrType == MRC_DDR_TYPE_LPDDR3);

  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    if (!MrcChannelExist (Outputs, Channel)) {
      continue;
    }
    LpddrTemperature.Data = 0;
    Ddr4Temprature.Data = 0;
    //
    // Download Read Reg File for all populated ranks per channel
    //
    Offset = MrcGetOffsetDataControl0 (MrcData, Channel, 0);
    DdrCrDataControl0.Data = MrcReadCR (MrcData, Offset);

    Offset = MrcGetOffsetDataControl0 (MrcData, Channel, 0xFF);
    DdrCrDataControl0.Bits.ReadRFRd   = 1;
    for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
      if (MrcRankInChannelExist (MrcData, Rank, Channel)) {
        DdrCrDataControl0.Bits.ReadRFRank = Rank;
        MrcWriteCrMulticast (MrcData, Offset, DdrCrDataControl0.Data);
        if (Lpddr3) {
          LpddrTemperature.Data |= (RANK_TEMPERATURE_HOT_LPDDR3 << (8 * Rank));
        } else if (Ddr4) {
          Ddr4Temprature.Data |= (RANK_TEMPERATURE_HOT_DDR4 << (8 * Rank));
        }

      }
    }

    //
    // Indicate to MC that we are going to exit Self Refresh when we go to Normal Mode
    //
    Offset = MCHBAR_CH0_CR_MC_INIT_STATE_REG + (MCHBAR_CH1_CR_MC_INIT_STATE_REG - MCHBAR_CH0_CR_MC_INIT_STATE_REG) * Channel;
    McInitState.Data = MrcReadCR (MrcData, Offset);
    McInitState.Bits.SRX_reset = 1;
    MrcWriteCR (MrcData, Offset, McInitState.Data);

    //
    // SA:RestritedContent Permanent MRC W/A for SKL bug [5122603][Mc unaware of DRAM initial temperature may violate derating/refresh rate requirements]
    // Initialize MC to "hot" temperature until the first LPDDR3/DDR4 temperature read occurs.
    //
    if (Lpddr3) {
      Offset = OFFSET_CALC_CH (MCHBAR_CH0_CR_LPDDR_MR4_RANK_TEMPERATURE_REG, MCHBAR_CH1_CR_LPDDR_MR4_RANK_TEMPERATURE_REG, Channel);
      MrcWriteCR (MrcData, Offset, LpddrTemperature.Data);
    } else if (Ddr4) {
      Offset = OFFSET_CALC_CH (MCHBAR_CH0_CR_DDR4_MPR_RANK_TEMPERATURE_REG, MCHBAR_CH1_CR_DDR4_MPR_RANK_TEMPERATURE_REG, Channel);
      MrcWriteCR (MrcData, Offset, Ddr4Temprature.Data);
    }
  } // for Channel

  return mrcSuccess;
}

