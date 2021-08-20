/** @file
  PEIM to initialize IGFX PM

 @copyright
  INTEL CONFIDENTIAL
  Copyright 1999 - 2019 Intel Corporation.

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
#include <Library/PeiServicesLib.h>
#include <Library/IoLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/DebugLib.h>
#include <Library/MmPciLib.h>
#include <IndustryStandard/Pci22.h>
#include <Private/Library/GraphicsInitLib.h>
#include <Private/Library/SaInitLib.h>
#include <Library/PciLib.h>
#include <Library/TimerLib.h>
#include <CpuRegs.h>
#include <Library/CpuPlatformLib.h>
#include <SaAccess.h>
#include <PchAccess.h>

///
/// Driver Consumed PPI Prototypes
///
#include <ConfigBlock/GraphicsPeiPreMemConfig.h>
#include <SaPolicyCommon.h>

GLOBAL_REMOVE_IF_UNREFERENCED BOOT_SCRIPT_REGISTER_SETTING  gSaGtRC6RegistersSkl[] = {
  {0x0,  0xA090,  0x7FFFFFFF,  0x0},
  //
  // RC1e - RC6/6p - RC6pp Wake Rate Limits
  //
  {0x0,  0xA098,  0x0,  0x03E80000},
  {0x0,  0xA09C,  0x0,  0x00280000},
  {0x0,  0xA0A8,  0x0,  0x0001E848},
  {0x0,  0xA0AC,  0x0,  0x00000019},
  //
  // Render/Video/Blitter Idle Max Count
  //
  {0x0,  0x2054,  0x0,  0xA},
  {0x0,  0x12054, 0x0,  0xA},
  {0x0,  0x22054, 0x0,  0xA},
  {0x0,  0x1A054, 0x0,  0xA},
  {0x0,  0x1C054, 0x0,  0xA},
  //
  // Enable Idle Messages
  //
  {0x0,  0x2050,  0x0,  0x00010000},
  {0x0,  0x12050, 0x0,  0x00010000},
  {0x0,  0x22050, 0x0,  0x00010000},
  {0x0,  0x1a050, 0x0,  0x00010000},
  {0x0,  0x1c050, 0x0,  0x00010000},
  {0x0,  0xC3E4,  0x0,  0xA},
  //
  // Unblock Ack to Busy
  //
  {0x0,  0xA0B0,  0x0,  0x0},
  //
  // RC Sleep / RCx Thresholds
  //
  {0x0,  0xA0B8,  0x0,  0x0000C350},
  //
  // RP Settings
  //
  {0x0,  0xA010,  0x0,  0x000F4240},
  {0x0,  0xA014,  0x0,  0x12060000},
  {0x0,  0xA02C,  0x0,  0x0000E808},
  {0x0,  0xA030,  0x0,  0x0003BD08},
  {0x0,  0xA068,  0x0,  0x000101D0},
  {0x0,  0xA06C,  0x0,  0x00055730},
  {0x0,  0xA070,  0x0,  0x0000000A},
  {0x0,  0xA168,  0x0,  0x00000006},
  {0x0,  0xA024,  0x0,  0x00000592}
};

GLOBAL_REMOVE_IF_UNREFERENCED UINT32 gSpcLock[] = {
  0x24608,
  0x2460C,
  0x24610,
  0x24688,
  0x2468C,
  0x24690,
  0x24708,
  0x2470C,
  0x24710,
  0x24788,
  0x2478C,
  0x24790,
  0x24008,
  0x24088,
  0x2408C,
  0x24090,
  0x24108,
  0x2410C,
  0x24110,
  0x24188,
  0x2418C,
  0x24190,
  0x24408,
  0x2440C,
  0x24410,
  0x24488,
  0x2448C,
  0x24490,
  0x24508,
  0x2450C,
  0x24510,
  0x24208,
  0x2420C,
  0x24210,
  0x24288,
  0x2428C,
  0x24290
};

/**
  Initialize GT PowerManagement of SystemAgent for SKL.

  @param[in] GtConfig         - Instance of GRAPHICS_PEI_CONFIG
  @param[in] GttMmAdr            - Base Address of IGFX MMIO BAR
  @param[in] MchBarBase          - Base Address of MCH_BAR

  @retval EFI_SUCCESS           - GT Power Management initialization complete
  @retval EFI_INVALID_PARAMETER - The input parameter is invalid
**/
EFI_STATUS
PmInitSKL (
  IN       GRAPHICS_PEI_CONFIG          *GtConfig,
  IN       UINT32                       GttMmAdr,
  IN       UINT32                       MchBarBase
  )
{
  UINT32            RegOffset;
  UINT32            Data32;
  UINT32            Data32Mask;
  UINT32            Result;
  UINT8             i;
  UINT32            Data32And;
  UINT32            Data32Or;
  CPU_STEPPING      CpuSteppingId;
  UINT16            GtDid;
  CPU_GENERATION    CpuGeneration;

  CpuGeneration = GetCpuGeneration ();
  CpuSteppingId = GetCpuStepping ();
  GtDid = MmioRead16 (MmPciBase (SA_MC_BUS, 2, 0) + 0x2);

  if ((GttMmAdr == 0) || (MchBarBase == 0) || (GtConfig == NULL)) {
    DEBUG ((DEBUG_ERROR, "Invalid parameters for PmInitSKL\n"));
    return EFI_INVALID_PARAMETER;
  }

  if (GtConfig->PmSupport) {
    DEBUG ((DEBUG_INFO, "Initializing SKL GT PM Enabling, register configuration starting here...... \n"));

    ///
    /// Set RC6 Context Location
    ///
    RegOffset                     = 0xD40;
    Data32                        = 0x80000000;
    MmioWrite32 (GttMmAdr + RegOffset, Data32);

    ///
    /// Set Context Base
    ///
    RegOffset                     = 0xD48;
    Data32                        = 0x00000001;
    MmioWrite32 (GttMmAdr + RegOffset, Data32);


    ///
    /// Enable Force Wake
    ///
    RegOffset                     = 0xA188;
    Data32                        = 0x00010001;
    MmioWrite32 (GttMmAdr + RegOffset, Data32);

    ///
    /// Poll to verify Force Wake Acknowledge Bit
    ///
    RegOffset                     = 0x130044;
    Data32Mask                    = BIT0;
    Result                        = 1;
    PollGtReady (GttMmAdr, RegOffset, Data32Mask, Result);
    DEBUG ((DEBUG_INFO, "Poll to verify Force Wake Acknowledge Bit, Result = 1\n"));

    RegOffset                     = 0xD00;
    Data32Or                      = (GtConfig->ProgramGtChickenBits) & (BIT3 | BIT2 | BIT1);
    Data32And                     = (UINT32)~(BIT3 | BIT2 | BIT1);
    MmioAndThenOr32 (GttMmAdr + RegOffset, Data32And, Data32Or);

    ///
    /// When Frame Buffer Caching is disabled, need to set 0x9044[30] = 1 to avoid GT polling uncore unnecessarily
    ///
    MmioOr32 (GttMmAdr + 0x9044, BIT30);

    ///
    /// Enabling Push Bus Metric Control
    ///
    RegOffset                     = 0xA250;
    Data32                        = 0x000001FF;
    MmioWrite32 (GttMmAdr + RegOffset, Data32);

    ///
    /// Configuring Push Bus Shift
    ///
    RegOffset                     = 0xA25C;
    Data32                        = 0x00000010;
    MmioWrite32 (GttMmAdr + RegOffset, Data32);

    ///
    /// Pushbus Metric Control
    ///
    RegOffset                     = 0xA248;
    Data32                        = 0x80000004;
    MmioWrite32 (GttMmAdr + RegOffset, Data32);

    ///
    /// Program GfxPause Register
    ///
    RegOffset                     = 0xA000;
    if (CpuSteppingId <= EnumSklC0) {
      Data32                      = 0x000703FF;
    } else {
      Data32                      = 0x00070020;
    }
    MmioWrite32 (GttMmAdr + RegOffset, Data32);

    ///
    /// GPM Control
    ///
    RegOffset                     = 0xA180;
    Data32                        = 0xC5200000;
    MmioWrite32 (GttMmAdr + RegOffset, Data32);

    ///
    /// Disable Fence writes
    ///
    RegOffset                     = 0xA194;
    Data32Or                      = BIT5;
    Data32And                     = 0xFFFFFFFF;
    MmioAndThenOr32 (GttMmAdr + RegOffset, Data32And, Data32Or);

    ///
    /// Enable DOP clock gating.
    ///
    Data32 = 0x000007FD;

    RegOffset                     = 0x9424;
    MmioWrite32 (GttMmAdr + RegOffset, Data32);
    DEBUG ((DEBUG_INFO, "Enabled DOP clock gating \n"));

    ///
    /// Enable unit level clock gates
    ///
    RegOffset                     = 0x9400;
    Data32                        = 0x00000000;
    MmioWrite32 (GttMmAdr + RegOffset, Data32);

    RegOffset                     = 0x9404;
    Data32                        = 0x40401000;
    MmioWrite32 (GttMmAdr + RegOffset, Data32);

    RegOffset                     = 0x9408;
    Data32                        = 0x00000000;
    MmioWrite32 (GttMmAdr + RegOffset, Data32);

    RegOffset                     = 0x940C;
    Data32                        = 0x02000001;
    MmioWrite32 (GttMmAdr + RegOffset, Data32);

    ///
    /// Program GT Normal Frequency Request
    ///
    Data32 = 0x03018000;


    MmioWrite32 (GttMmAdr + 0xA008, Data32);

    ///
    /// Program Video Frequency Request
    ///
    Data32 = 0x0C800000;


    MmioWrite32 (GttMmAdr + 0xA00C, Data32);

    ///
    /// Program Media Force Wake. Set this before enabling power gating.
    ///
    Data32 = 0x00010001;
    MmioWrite32 (GttMmAdr + 0xA270, Data32);

    ///
    /// Poll for Media Force Wake acknowledge.
    ///
    RegOffset                     = 0x0D88;
    Data32Mask                    = BIT0;
    Result                        = 1;
    PollGtReady (GttMmAdr, RegOffset, Data32Mask, Result);

    ///
    /// Render Force Wake. Set this before enabling power gating.
    ///
    RegOffset                     = 0xA278;
    Data32                        = 0x00010001;
    MmioWrite32 (GttMmAdr + RegOffset, Data32);

    ///
    /// Poll for Render Force Wake acknowledge.
    ///
    RegOffset                     = 0x0D84;
    Data32Mask                    = BIT0;
    Result                        = 1;
    PollGtReady (GttMmAdr, RegOffset, Data32Mask, Result);


    ///
    /// CdynMax Clamping Feature for higher frequency for Gen9/Gen9.5 GT4 (4+4E) Halo parts.
    ///
    if (((GtDid == V_SA_PCI_DEV_2_GT4_SHALM_ID) || (GtDid == V_SA_PCI_DEV_2_GT4_SHALM_EMB_ID)|| (GtDid == V_SA_PCI_DEV_2_GT4_KHALM_ID)) && (GtConfig->CdynmaxClampEnable)) {
      ///
      /// a. Program the event weights into GT MMIO registers 0x8C04, 0x8C08 and 0x8C0C (Iccp_CDYNMAX_EVTWTx)
      /// b. Program the EI window in GT MMIO register 0x8C00 (CDYNMAX_CFG0)
      /// c. Program the clamping thresholds and the associated delta values in MMIO registers 0x8C10, 0x8C14, 0x8C18 and 0x8C1C (Iccp_CDYNA_CLAMP_THRx)
      /// d. Program the Panic threshold values in MMIO register 0x8C00.
      /// e. Program the threshold Compare Shift Value in MMIO register 0x8C1C
      /// f. Set the required clamping level (clamped/Unclamped) in register in GT MMIO register 0xA218 (Iccp_Request_level)
      /// g. Enable GT ICCP feature via GT MMIO register 0xA214 (Iccp_Feature_Enable). The below settings are of 86% Clamping Threshold
      ///
      DEBUG ((DEBUG_INFO, "Cdynmax Clamp Feature Enabled\n"));

      RegOffset                     = 0x8C04;
      Data32                        = 0x29609FFF;
      MmioWrite32 (GttMmAdr + RegOffset, Data32);
      DEBUG ((DEBUG_INFO, "0x8C04: 0x%x\n", MmioRead32 (GttMmAdr + RegOffset)));

      RegOffset                     = 0x8C08;
      Data32                        = 0x0603090F;
      MmioWrite32 (GttMmAdr + RegOffset, Data32);
      DEBUG ((DEBUG_INFO, "0x8C08: 0x%x\n", MmioRead32 (GttMmAdr + RegOffset)));

      RegOffset                     = 0x8C0C;
      Data32And                     = 0xFFFFFFC0;
      Data32Or                      = 0x18;
      MmioAndThenOr32 (GttMmAdr + RegOffset, Data32And, Data32Or);
      DEBUG ((DEBUG_INFO, "0x8C0C: 0x%x\n", MmioRead32 (GttMmAdr + RegOffset)));

      ///
      /// b. EI - Evaluation Interval 8C00[15:0]]= 13 (256ns/20 = 12.8)
      /// e.Panic Threshold value 8C00[31:24]= 160
      /// Progam ClampDis Threshold 8C00[23:16]= 84
      ///
      RegOffset                     = 0x8C00;
      Data32                        = 0xA054000D;
      MmioWrite32 (GttMmAdr + RegOffset, Data32);
      DEBUG ((DEBUG_INFO, "0x8C00: 0x%x\n", MmioRead32 (GttMmAdr + RegOffset)));

      ///
      /// c. Clamping Threshold and Deltas
      ///
      RegOffset                     = 0x8C10;
      Data32                        = 0xF078E051;
      MmioWrite32 (GttMmAdr + RegOffset, Data32);
      DEBUG ((DEBUG_INFO, "0x8C10: 0x%x\n", MmioRead32 (GttMmAdr + RegOffset)));

      RegOffset                     = 0x8C14;
      Data32                        = 0xFC9AF88C;
      MmioWrite32 (GttMmAdr + RegOffset, Data32);
      DEBUG ((DEBUG_INFO, "0x8C14: 0x%x\n", MmioRead32 (GttMmAdr + RegOffset)));

      RegOffset                     = 0x8C18;
      Data32                        = 0x08A300A0;
      MmioWrite32 (GttMmAdr + RegOffset, Data32);
      DEBUG ((DEBUG_INFO, "0x8C18: 0x%x\n", MmioRead32 (GttMmAdr + RegOffset)));

      ///
      /// d.Threshold Compare Shift Value in MMIO register 0x8C1C
      ///
      RegOffset                     = 0x8C1C;
      Data32And                     = 0xF8000000;
      Data32Or                      = 0x022010A9;
      MmioAndThenOr32 (GttMmAdr + RegOffset, Data32And, Data32Or);
      DEBUG ((DEBUG_INFO, "0x8C1C: 0x%x\n", MmioRead32 (GttMmAdr + RegOffset)));

      ///
      /// f. License Request Level - GT MMIO Regsiter address: 0xA218 [0:0] 1 - Clamped Mode; 0 - Non-Clamped Mode
      ///
      RegOffset                     = 0xA218;
      Data32And                     = 0xFFFFFFFE;
      Data32Or                      = BIT0;
      MmioAndThenOr32 (GttMmAdr + RegOffset, Data32And, Data32Or);
      DEBUG ((DEBUG_INFO, "0xA218: 0x%x\n", MmioRead32 (GttMmAdr + RegOffset)));

      ///
      /// g. Enabling the feature GT MMIO Regsiter address: 0xA214 [0:0] IccP Feature Enable 0b = Feature is disabled (default) 1b = Feature is enabled
      ///  [31:31]   IccP Lock Keep it locked for non-Halo for SPM and GPM unit Keep it unlocked for Halo

      RegOffset                     = 0xA214;
      Data32And                     = 0x7FFFFFFE;
      Data32Or                      = BIT0;
      MmioAndThenOr32 (GttMmAdr + RegOffset, Data32And, Data32Or);
      DEBUG ((DEBUG_INFO, "0xA214: 0x%x\n", MmioRead32 (GttMmAdr + RegOffset)));

      ///
      /// Programming for 50% CheckPoint
      /// a. Enable 50% CheckPoint 0x8C20[1] = 0
      /// b. 0x8C20[3:2] = 50% checkpoint programmable bubble count. 0x8C20[3:2] = 11b for 86% CT
      /// c. Enable Max Ratio to be 11/16 0x8C20[4] = 0
      /// d. Progam ClampDis Threshold 8C00[23:16]= 84 (done above)
      ///

      RegOffset                     = 0x8C20;
      Data32And                     = 0xFFFFFFE1;
      Data32Or                      = 0x0C;
      MmioAndThenOr32 (GttMmAdr + RegOffset, Data32And, Data32Or);
      DEBUG ((DEBUG_INFO, "0x8C20: 0x%x\n", MmioRead32 (GttMmAdr + RegOffset)));

    } else {
      ///
      /// For non-Halo 4+4e parts disable this feature and lock it
      /// Disable the feature 0xA214 [0:0]  0b = Feature is disabled 1b = Feature is enabled
      /// [31:31]   IccP Lock Keep it locked for non-Halo for SPM and GPM unit Keep it unlocked for Halo
      ///

      DEBUG ((DEBUG_INFO, "Cdynmax Clamp Feature Disabled\n"));
      RegOffset                     = 0xA214;
      Data32And                     = 0xFFFFFFFE;
      Data32Or                      = BIT31;
      MmioAndThenOr32 (GttMmAdr + RegOffset, Data32And, Data32Or);
      DEBUG ((DEBUG_INFO, "For non-Halo 4+4e 0xA214: 0x%x\n", MmioRead32 (GttMmAdr + RegOffset)));

      ///
      /// License Request Level - Non-Clamp Mode: 0xA218 [0:0] 1 - Clamped Mode; 0 - Non-Clamped Mode
      ///
      RegOffset                     = 0xA218;
      Data32And                     = (UINT32) ~(BIT0);
      Data32Or                      = 0;
      MmioAndThenOr32 (GttMmAdr + RegOffset, Data32And, Data32Or);
      DEBUG ((DEBUG_INFO, "0xA218: 0x%x\n", MmioRead32 (GttMmAdr + RegOffset)));
    }

    ///
    /// RC6 Settings
    ///
    for (i = 0; i < sizeof (gSaGtRC6RegistersSkl) / sizeof (BOOT_SCRIPT_REGISTER_SETTING); ++i) {
      RegOffset                     = gSaGtRC6RegistersSkl[i].Offset;
      Data32And                     = gSaGtRC6RegistersSkl[i].AndMask;
      Data32Or                      = gSaGtRC6RegistersSkl[i].OrMask;

      MmioAndThenOr32 (GttMmAdr + RegOffset, Data32And, Data32Or);
    }

    ///
    /// HW RC6 Control Settings
    ///
    Data32 = 0;

    if (GtConfig->RenderStandby) {
      Data32 = 0x88040000;
      if (CpuGeneration == EnumSklCpu) {
        MmioOr32 (GttMmAdr + 0x4090, BIT8);
      }
    }

    MmioWrite32 (GttMmAdr + 0xA090, Data32);

    ///
    /// RC6 Settings
    ///
    ///
    /// Wait for Mailbox ready
    ///
    Data32Mask  = BIT31;
    Result      = 0;

    PollGtReady (GttMmAdr, 0x138124, Data32Mask, Result);

    ///
    /// Mailbox Data  - RC6 VIDS
    ///
    Data32 = 0x0;
    MmioWrite32 (GttMmAdr + 0x138128, Data32);

    ///
    /// Mailbox Command
    ///
    Data32                      = 0x80000004;
    MmioWrite32 (GttMmAdr + 0x138124, Data32);

    ///
    /// Wait for Mailbox ready
    ///
    Data32Mask  = BIT31;
    Result      = 0;

    PollGtReady (GttMmAdr, 0x138124, Data32Mask, Result);

    ///
    /// Enable PM Interrupts
    ///
    Data32                      = 0x03000076;
    MmioWrite32 (GttMmAdr + 0x4402C, Data32);

    ///
    /// Enabling to enter RC6 state in idle mode.
    ///
    Data32 = 0;
    if (GtConfig->RenderStandby) {
      RegOffset                     = 0xA094;
      Data32                        = 0x00040000;
      if (CpuGeneration == EnumSklCpu) {
        MmioOr32 (GttMmAdr + 0x4090, BIT8);
      }
      MmioWrite32 (GttMmAdr + RegOffset, Data32);
      DEBUG ((DEBUG_INFO, "Entered RC6 state in idle mode\n"));
    }

      ///
      /// Media Force Wake
      ///
      RegOffset                     = 0xA270;
      Data32                        = 0x00010000;
      MmioWrite32 (GttMmAdr + RegOffset, Data32);

      ///
      /// Poll for Media Force Wake acknowledge.
      ///
      RegOffset                     = 0x0D88;
      Data32Mask                    = BIT0;
      Result                        = 0;
      PollGtReady (GttMmAdr, RegOffset, Data32Mask, Result);

      ///
      /// Render Force Wake
      ///
      RegOffset                     = 0xA278;
      Data32                        = 0x00010000;
      MmioWrite32 (GttMmAdr + RegOffset, Data32);

      ///
      /// Poll for Render Force Wake acknowledge.
      ///
      RegOffset                     = 0x0D84;
      Data32Mask                    = BIT0;
      Result                        = 0;
      PollGtReady (GttMmAdr, RegOffset, Data32Mask, Result);

      ///
      /// Clear offset 0xA188 [31:0] to clear the force wake enable
      ///
      RegOffset                     = 0xA188;
      Data32                        = 0x00010000;
      MmioWrite32 (GttMmAdr + RegOffset, Data32);

      ///
      /// Poll until clearing is cleared to verify the force wake acknowledge.
      ///
      RegOffset                     = 0x130044;
      Data32Mask                    = BIT0;
      Result                        = 0;
      PollGtReady (GttMmAdr, RegOffset, Data32Mask, Result);

    ///
    /// SPC Register Lock.
    ///
    Data32Or = 0x80000000;
      if ((MmioRead32 (GttMmAdr + 0x9120) & BIT25) == 0) {
        ///
        /// Slice 0 disabled, set 0xFDC to Slice 1
        ///
        Data32And = (UINT32) ~(BIT27 | BIT26);
        Data32Or = BIT26;
        MmioAndThenOr32 (GttMmAdr + 0x0FDC, Data32And, Data32Or);
      }
      if ((MmioRead32 (GttMmAdr + 0x9120) & BIT20) == BIT20) {
        ///
        /// SubSlice 0 disabled, set 0xFDC to SubSlice 1
        ///
        Data32And = (UINT32) ~(BIT25 | BIT24);
        Data32Or = BIT24;
        MmioAndThenOr32 (GttMmAdr + 0x0FDC, Data32And, Data32Or);
      }
      for (i = 0; i < sizeof(gSpcLock) / sizeof(UINT32); ++i) {
        RegOffset = gSpcLock[i];
        MmioOr32(GttMmAdr + RegOffset, Data32Or);
      }
  }

  DEBUG ((DEBUG_INFO, "All register programming done for GT PM Init for SKL. Exiting.\n"));
  return EFI_SUCCESS;
}

/**
  Initialize PAVP feature of SystemAgent.

  @param[in] GRAPHICS_PEI_CONFIG             *GtConfig
  @param[in] SA_MISC_PEI_CONFIG              *MiscPeiConfig

  @retval EFI_SUCCESS     - PAVP initialization complete
  @retval EFI_UNSUPPORTED - iGFX is not present so PAVP not supported
**/
EFI_STATUS
PavpInit (
  IN       GRAPHICS_PEI_CONFIG             *GtConfig,
  IN       SA_MISC_PEI_CONFIG              *MiscPeiConfig
  )
{

  UINT32       PcmBase = 0;
  UINTN        McD0BaseAddress;
  UINTN        McD2BaseAddress;
  UINT32       Pavpc;
  McD0BaseAddress = MmPciBase (SA_MC_BUS, SA_MC_DEV, SA_MC_FUN);
  Pavpc = MmioRead32 (McD0BaseAddress + R_SA_PAVPC);

  ///
  /// If device 0:2:0 (Internal Graphics Device, or GT) is not enabled, skip PAVP
  ///
  McD2BaseAddress = MmPciBase (SA_IGD_BUS, SA_IGD_DEV, SA_IGD_FUN_0);
  if ((MmioRead16 (McD2BaseAddress + R_SA_IGD_VID) != 0xFFFF) && (GtConfig->PavpEnable == 1)) {
    DEBUG ((DEBUG_INFO, "Initializing PAVP\n"));
    Pavpc &= (UINT32) ~(B_SA_PAVPC_HVYMODSEL_MASK | B_SA_PAVPC_PCMBASE_MASK | B_SA_PAVPC_PAVPE_MASK | B_SA_PAVPC_PCME_MASK);
    Pavpc &= (UINT32) ~(BIT8 | BIT7);
    PcmBase = ((UINT32) RShiftU64 ((MmioRead32 (McD0BaseAddress +R_SA_TOLUD)), 20)) - PAVP_PCM_SIZE_1_MB;
    Pavpc |= (UINT32) LShiftU64 (PcmBase, 20);
    Pavpc |= B_SA_PAVPC_PCME_MASK | B_SA_PAVPC_PAVPE_MASK;

    Pavpc |= BIT6;
  }
  ///
  /// Lock PAVPC Register
  ///
  Pavpc |= B_SA_PAVPC_PAVPLCK_MASK;
  MmioWrite32 (McD0BaseAddress + R_SA_PAVPC, Pavpc);
  return EFI_SUCCESS;
}

/**
  Poll Run busy clear

  @param[in] Base    - Base address of MMIO
  @param[in] Timeout - Timeout value in microsecond

  @retval TRUE       - Run Busy bit is clear
  @retval FALSE      - Run Busy bit is still set
**/
BOOLEAN
PollRunBusyClear (
  IN    UINT64           Base,
  IN    UINT32           Timeout
  )
{
  UINT32  Value;
  BOOLEAN Status = FALSE;

  //
  // Make timeout an exact multiple of 10 to avoid infinite loop
  //
  if ((Timeout) % 10 != 0) {
    Timeout = (Timeout) + 10 - ((Timeout) % 10);
  }

  while (Timeout != 0) {
    Value = MmioRead32 ((UINTN) Base + 0x138124);
    if (Value & BIT31) {
      //
      // Wait for 10us and try again.
      //
      DEBUG ((DEBUG_INFO, "Interface register run busy bit is still set. Trying again \n"));
      MicroSecondDelay (MAILBOX_WAITTIME);
      Timeout = Timeout - MAILBOX_WAITTIME;
    } else {
      Status = TRUE;
      break;
    }
  }
  ASSERT ((Timeout != 0));

  return Status;
}

/**
  Initialize Cd Clock sequence

  @param[in] GtConfig            - Instance of GRAPHICS_PEI_CONFIG
  @param[in] GttMmAdr            - Base Address of IGFX MMIO BAR

  @retval EFI_SUCCESS           - GT Power Management initialization complete
  @retval EFI_INVALID_PARAMETER - The input parameter is invalid
**/
EFI_STATUS
CdClkInit (
  IN       GRAPHICS_PEI_CONFIG          *GtConfig,
  IN       UINT32                       GttMmAdr
  )
{
  UINT32                 Data32Or;
  UINT16                 WaitTime;
  EFI_BOOT_MODE          BootMode;
  EFI_STATUS             Status;

  WaitTime             = GT_CDCLK_TIMEOUT;
  ///
  /// CDCLK_CTL - GttMmAdr + 0x46000
  /// CdClock 1: [27:26] = 00b; 450    Mhz - [10:0] = 0x382
  /// CdClock 2: [27:26] = 01b; 540    Mhz - [10:0] = 0x436
  /// CdClock 0: [27:26] = 10b; 337.5  Mhz - [10:0] = 0x2A1
  /// CdClock 3: [27:26] = 11b; 675    Mhz - [10:0] = 0x544
  ///
  switch (GtConfig->CdClock) {
    case 0 :
      Data32Or = 0x080002A1;
      break;
    case 1 :
      Data32Or = 0x00000382;
      break;
    case 2 :
      Data32Or = 0x04000436;
      break;
    case 3 :
      Data32Or = 0x0C000544;
      break;
    default:
      return EFI_INVALID_PARAMETER;
  }
  MmioAndThenOr32 (GttMmAdr + 0x46000, 0xF3FFF800, Data32Or);

  //
  // Initialize full CDCLK sequence for S3 Resume flow , GOP takes care in other flows
  //
  Status = PeiServicesGetBootMode (&BootMode);
  if ((Status != EFI_SUCCESS) || (BootMode != BOOT_ON_S3_RESUME)) {
    return EFI_SUCCESS;
  }
  //
  // Enable PCH Reset Handshake
  //
  MmioOr32 ((GttMmAdr + 0x46408), BIT4);
  PollGtReady (GttMmAdr, 0x42000, BIT27, BIT27);
  //
  // Enable PG1
  //
  MmioOr32 (GttMmAdr + 0x45400, BIT29);
  PollGtReady (GttMmAdr, 0x45400, BIT28, BIT28);  // Poll for PG1 status
  PollGtReady (GttMmAdr, 0x42000, BIT26, BIT26);  // Poll Fuse PG1 distribution status

  //
  // Enable PG2
  //
  MmioOr32 (GttMmAdr + 0x45400, BIT31);
  PollGtReady (GttMmAdr, 0x45400, BIT30, BIT30);  // Poll for PG2 status
  PollGtReady (GttMmAdr, 0x42000, BIT25, BIT25);  // Poll Fuse PG2 distribution status
  //
  // Enable Misc IO Power
  //
  MmioOr32 (GttMmAdr + 0x45400, BIT1);
  PollGtReady (GttMmAdr, 0x45400, BIT0, BIT0);
  //
  //Inform Power controll of upcoming freq change
  //
  PollRunBusyClear (GttMmAdr, MAILBOX_TIMEOUT);     // Poll run-busy before start

  while (WaitTime != 0 ) { //3ms loop
    MmioWrite32 (GttMmAdr + 0x138128, 0x00000003);  // mailbox_low      = 0x00000003
    MmioWrite32 (GttMmAdr + 0x13812c, 0x00000000);  // mailbox_high     = 0x00000000
    MmioWrite32 (GttMmAdr + 0x138124, 0x80000007);  // mailbox Interface = 0x80000007
    PollRunBusyClear (GttMmAdr, MAILBOX_TIMEOUT);   // Poll Run Busy cleared
    //
    // Check for MailBox Data read status successful
    //
    if ((MmioRead32 (GttMmAdr + 0x138128) & BIT0) == 1 ) {
      DEBUG ((DEBUG_INFO, "Mailbox Data low read Successfull \n"));
      break;
    }
    MicroSecondDelay (MAILBOX_WAITTIME);
    WaitTime = WaitTime - MAILBOX_WAITTIME;
  }

  //
  // 3ms Timeout
  //
  if(WaitTime == 0) {
    DEBUG ((DEBUG_INFO, "CDCLK initialization failed , not changing CDCLK \n"));
  } else {
    DEBUG ((DEBUG_INFO, "Enabling CDCLK  \n"));
    //
    // Enable CDCLK PLL and change the CDCLK_CTL register
    //
    MmioOr32 (GttMmAdr + 0x46010, BIT31);
    PollGtReady (GttMmAdr, 0x46010, BIT30, BIT30);
    MmioAndThenOr32 (GttMmAdr + 0x46000, 0xF3FFF800, 0x0C000544); // Programming 675MHz.

    //
    //Inform Power controller of the selected freq (675MHZ)
    //
    MmioWrite32 (GttMmAdr + 0x138128, 0x00000003);
    MmioWrite32 (GttMmAdr + 0x13812c, 0x00000000);
    MmioWrite32 (GttMmAdr + 0x138124, 0x80000007);

    //
    //DBUF Power Well Control
    //
    MmioOr32 (GttMmAdr + 0x45008, BIT31);
    PollGtReady (GttMmAdr, 0x45008, BIT30, BIT30);
  }

  return EFI_SUCCESS;
}

/**
Initialize GT Power management

  @param[in] GRAPHICS_PEI_PREMEM_CONFIG      GtPreMemConfig
  @param[in] GRAPHICS_PEI_CONFIG             GtConfig

  @retval EFI_SUCCESS          - GT Power management initialization complete
**/
EFI_STATUS
GraphicsPmInit (
  IN       GRAPHICS_PEI_PREMEM_CONFIG      *GtPreMemConfig,
  IN       GRAPHICS_PEI_CONFIG             *GtConfig
  )
{
  UINT32                LoGTBaseAddress;
  UINT32                HiGTBaseAddress;
  UINTN                 McD2BaseAddress;
  EFI_STATUS            Status;
  UINT32                GttMmAdr;
  UINT32                GmAdr;
  UINT32                MchBarBase;
  UINT8                 Msac;
  UINT32                Data32Mask;
  UINT32                Data32;

  DEBUG ((DEBUG_INFO, " iGfx Power management start.\n"));

  GttMmAdr   = 0;
  MchBarBase = 0;
  Status     = EFI_SUCCESS;
  MchBarBase = MmioRead32 (MmPciBase(SA_MC_BUS, 0, 0) + 0x48) &~BIT0;

  ///
  /// If device 0:2:0 (Internal Graphics Device, or GT) is enabled, then Program GTTMMADR,
  ///
  McD2BaseAddress = MmPciBase (SA_IGD_BUS, SA_IGD_DEV, SA_IGD_FUN_0);
  if (MmioRead16 (McD2BaseAddress + R_SA_IGD_VID) != 0xFFFF) {
    ///
    /// Program GT PM Settings if GttMmAdr allocation is Successful
    ///
    GttMmAdr                          = GtPreMemConfig->GttMmAdr;
    LoGTBaseAddress                   = (UINT32) (GttMmAdr & 0xFFFFFFFF);
    HiGTBaseAddress                   = 0;
    MmioWrite32 (McD2BaseAddress + R_SA_IGD_GTTMMADR, LoGTBaseAddress);
    MmioWrite32 (McD2BaseAddress + R_SA_IGD_GTTMMADR + 4, HiGTBaseAddress);

    Msac = MmioRead8 (McD2BaseAddress + R_SA_IGD_MSAC_OFFSET);
    MmioAndThenOr8 (McD2BaseAddress + R_SA_IGD_MSAC_OFFSET, (UINT8) ~(BIT4 + BIT3 + BIT2 + BIT1 + BIT0), SA_GT_APERTURE_SIZE_256MB);

    GmAdr = GtPreMemConfig->GmAdr;
    MmioWrite32 (McD2BaseAddress + R_SA_IGD_GMADR, GmAdr);

    ///
    /// Enable Bus Master and Memory access on 0:2:0
    ///
    MmioOr16 (McD2BaseAddress + R_SA_IGD_CMD, (BIT2 | BIT1));

    ///
    /// Program GT frequency
    ///
    if (GtConfig->GtFreqMax != 0xFF) {
      MmioWrite8 ((MchBarBase + 0x5994), (UINT8) GtConfig->GtFreqMax);
      DEBUG ((DEBUG_INFO, "Max frequency programmed by user in MchBar 0x5994 is (to be multiplied by 50 for MHz): 0x%x  \n", MmioRead8 (MchBarBase + 0x5994)));
    }

    ///
    /// PmInit Initialization
    ///
    DEBUG ((DEBUG_INFO, "Initializing GT PowerManagement for SKL  \n"));
    PmInitSKL (GtConfig, GttMmAdr, MchBarBase);

    ///
    /// Copy MSR_PLATFORM_INFO.SAMPLE_PART(FUSE_PROD_PART) bit to CONFIG0 Address D00h, bit 30 and Lock bit
    ///
    Data32 = (UINT32) (AsmReadMsr64 (MSR_PLATFORM_INFO) & B_PLATFORM_INFO_SAMPLE_PART);
    Data32 = (UINT32) ((Data32 << 3) | BIT31);
    Data32Mask = (UINT32) ~(BIT31 | BIT30);
    MmioAndThenOr32 (GttMmAdr + 0xD00, Data32Mask, Data32);
    DEBUG ((DEBUG_INFO, "Update CONFIG0 Address D00 : %x\n", MmioRead32 (GttMmAdr + 0xD00)));

    CdClkInit (GtConfig, GttMmAdr);

    MmioAnd16 (McD2BaseAddress + R_SA_IGD_CMD, (UINT16) ~(BIT2 | BIT1));
    MmioWrite32 (McD2BaseAddress + R_SA_IGD_GTTMMADR, 0);
    MmioWrite32 (McD2BaseAddress + R_SA_IGD_GTTMMADR + 0x4, 0);
    MmioWrite8 (McD2BaseAddress + R_SA_IGD_MSAC_OFFSET, Msac);
    MmioWrite32 (McD2BaseAddress + R_SA_IGD_GMADR, 0x0);
  }
  DEBUG ((DEBUG_INFO, "iGfx Power management end.\n"));
  return EFI_SUCCESS;
}
