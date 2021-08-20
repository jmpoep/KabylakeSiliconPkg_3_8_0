/** @file
  The functions in this file initializes the physical memory map.

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
#include "MrcMemoryMap.h"
#include "PttPtpRegs.h"

/**
  After BIOS determines the total physical memory size.
  Determines TOM which is defined by the total physical memory size.
  Determines TOM minus the ME memory size. The ME memory size is calculated from MESEG_BASE and MESEG_MASK.
  Determines MMIO allocation, which is system configuration dependent.

  Determines TOLUD which is the minimum value by comparing between "4GB minus MMIO size" and "TOM minus ME size".
  Determines Graphics Stolen Base, BDSM by subtracting the graphics data stolen memory size from TOLUD.
  Graphics Data Stolen Memory size is given by GMS field in GGC register.  It must be define before this stage.
  Determines Graphics GTT Stolen Base, BGSM by subtracting the GTT graphics stolen memory size from BDSM.
  GTT Stolen Memory size is given by GGMS field in GGC register.  It must be define before this stage.
  Determines TSEG Base, TSEGMB by subtracting TSEG size from BGSM.
  TSEG should be defined.
  Remove the memory hole caused by aligning TSEG to a 8MB boundary.
  Determine whether Memory Reclaim is available.  If "TOM minus ME Stolem Memory Size" is greater than the value of TOLUD, then memory reclaim is available to enable.
  Determine REMAPBASE if reclaim is enabled.  This is the maximum value by comparing between 4GB and "TOM minus ME size".
  Determine REMAPLIMIT () if reclaim is enabled.  This is the value of REMAPBASE plus "the difference between the value in TOLUD register and the lower of either 4GB or 'TOM minus ME Stolen memory size", and then minus 1 boundary.
  Determine TOUUD. TOUUD indicates the address one byte above the maximum DRAM.  If relcaim is disabled, this value is calculated by "TOM minus ME stolen size".  Otherwise, this value is set to REMAPLIMIT plus 1MB.

  @param[in, out] MrcData - Include all MRC global data. include also the memory map data.

  @retval MrcStatus -  if the reset is succeded.
**/
MrcStatus
MrcSetMemoryMap (
  IN OUT MrcParameters *const MrcData
  )
{
  MrcDebug                *Debug;
  const MrcInput          *Inputs;
  const MRC_FUNCTION      *MrcCall;
  MrcOutput               *Outputs;
  MrcMemoryMap            *MemoryMap;
  MrcGfxDataSize          GraphicsStolenSize;
  UNCORE_CR_GGC_0_0_0_PCI_STRUCT  Ggc;
  UINT32                  Gms;
  UINT32                  Offset;
  UINT32                  TsegBaseOrg;
  UINT32                  PrmrrBaseOrg;
  UINT32                  PrmrrAlign;
  INT32                   TsegAlignment;
  UINT32                  GdxcTop;
  UINT32                  PttTop;
  UINT32                  MmioSize;
  UINT32                  LowestBase;
#ifdef PTT_FLAG
  UINT32                  TpmStsFtif;
#endif
  BOOLEAN                 GdxcLow;

  Inputs    = &MrcData->Inputs;
  MrcCall   = Inputs->Call.Func;
  Outputs   = &MrcData->Outputs;
  Debug     = &Outputs->Debug;
  MemoryMap = &Outputs->MemoryMapData;

  GdxcLow = FALSE;

  //
  // Find the total memory size
  //
  MrcTotalMemory (MrcData);

  //
  // Set TOM register
  //
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "TOM (Total physical memory size) = %u MB\n", MemoryMap->TotalPhysicalMemorySize);

  //
  // Find the TOM minus ME size only for internal calculations
  //
  MemoryMap->TomMinusMe = MemoryMap->TotalPhysicalMemorySize - Inputs->MeStolenSize;

  MmioSize = Inputs->MmioSize;
  if (Inputs->MemoryTrace) {
    if (MemoryMap->TotalPhysicalMemorySize <= MEM_4GB) {
      MmioSize = MAX (MmioSize, MEM_4GB - MemoryMap->TotalPhysicalMemorySize / 2);
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Adjusted MmioSize = %Xh\n", MmioSize);
    }
  }

  //
  // Find and set TOLUD.
  // TOLUD which is the minimum value by comparing between "4GB minus MMIO size" and "TOM minus ME size"
  //
  MemoryMap->ToludBase = MIN (MemoryMap->TomMinusMe, MEM_4GB - MmioSize);

  //
  // Find and set BDSM Graphics Stolen Base.
  // Graphics Stolen Base, BDSM by subtracting the graphics data stolen memory size from TOLUD.
  //
  GraphicsStolenSize = Outputs->GraphicsStolenSize;
  MemoryMap->BdsmBase = MemoryMap->ToludBase - GraphicsStolenSize;

  //
  // Graphics GTT Stolen Base
  // Graphics GTT Stolen Base, BGSM by subtracting the GTT graphics stolen memory size from BDSM.
  //
  MemoryMap->GttBase = MemoryMap->BdsmBase - Outputs->GraphicsGttSize;

  //
  // Graphics size register init.
  //
  Offset   = Inputs->PciEBaseAddress + MrcCall->MrcGetPcieDeviceAddress (0, 0, 0, UNCORE_CR_GGC_0_0_0_PCI_REG);
  Ggc.Data = (UINT16) MrcCall->MrcMmioRead32 (Offset);

  Ggc.Bits.VAMEN= (Inputs->GfxIsVersatileAcceleration == TRUE) ? 1 : 0;
  if (Outputs->GraphicsGttSize > 0) {
    Ggc.Bits.GGMS = MIN (UNCORE_CR_GGC_0_0_0_PCI_GGMS_MAX, MrcLog2 (Outputs->GraphicsGttSize) - 1);
  } else {
    Ggc.Bits.GGMS = 0;
  }

  //
  // Graphics Stolen Size below 64MB has a higher granularity and can be set in 4MB increments
  // For Sizes 4MB to 60MB sizes (excluding 32MB), GMS values range from 240-254 (240 + Size/4 - 1)
  // Graphics Stolen Size above 64MB has a granularity of 32MB increments
  // For Sizes 0, 32MB and above 64MB GMS values are Size/32
  //
  if ((GraphicsStolenSize == 32) || (GraphicsStolenSize == 0) || (GraphicsStolenSize >= 64)) {
    Gms = GraphicsStolenSize / 32;
  } else {
    Gms = 240 + (GraphicsStolenSize / 4 - 1);
  }
  Ggc.Bits.GMS = (UINT16) MIN (UNCORE_CR_GGC_0_0_0_PCI_GMS_MAX, Gms);

  MemoryMap->GraphicsControlRegister = Ggc.Data;
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "GGC value = %Xh\n", MemoryMap->GraphicsControlRegister);

  //
  // TSEG Base
  //
  MemoryMap->TsegBase = MemoryMap->GttBase - Inputs->TsegSize;
  LowestBase = MemoryMap->TsegBase;

  //
  // DPR is after TSEG.
  //
  MemoryMap->DprSize  = Inputs->DprSize;
  LowestBase         -= Inputs->DprSize;

  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Unaligned TSEG base = %Xh\n", MemoryMap->TsegBase);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Unaligned GTT base = %Xh\n", MemoryMap->GttBase);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Unaligned BDSM base = %Xh\n", MemoryMap->BdsmBase);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Unaligned TOLUD base = %Xh\n", MemoryMap->ToludBase);

  //
  // Reserve PRMRR region after the DPR region.
  // Must be aligned to 128 MB if PRMRR Size >= 32MB, Naturally aligned if PRMRR Size is 1MB.
  // PRMRR Sizes that are > 1MB and < 32MB are not supported and will fail out.
  //
  if (Inputs->PrmrrSize > 0) {
    PrmrrBaseOrg  = LowestBase - Inputs->PrmrrSize;

    if (Inputs->PrmrrSize >= 32) {
      //
      // 128 MB alignment
      //
      MemoryMap->PrmrrBase = PrmrrBaseOrg & ~(MAX_PRMRR - 1);

      //
      // Used to align other regions
      //
      PrmrrAlign = PrmrrBaseOrg - MemoryMap->PrmrrBase;
    } else if (Inputs->PrmrrSize == 1) {
      //
      // Natural alignment, find TsegAlignment to align PRMRR Base to this
      //
      TsegAlignment = ((INT32) (MemoryMap->TsegBase & ~(Inputs->TsegSize - 1))) - ((INT32) MemoryMap->TsegBase);

      MemoryMap->PrmrrBase = ((UINT32) (((INT32) (PrmrrBaseOrg)) + TsegAlignment));
      PrmrrAlign = 0;
    } else {
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "PRMRR Size requirement of %dMB is outside the allowed ranges of either 1MB or >= 32MB!\n", Inputs->PrmrrSize);
      return mrcFail;
    }

    LowestBase = MemoryMap->PrmrrBase;


    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "PRMRR base = %Xh\n", MemoryMap->PrmrrBase);

  } else {

    //
    // No shift for no PRMRR
    //
    PrmrrAlign = 0;
  }

  //
  //  Align TSEG to PRMRR.
  //
  MemoryMap->TsegBase = MemoryMap->TsegBase - PrmrrAlign;

  //
  //  Align TSEG to natural alignment.
  //
  if (MemoryMap->TsegBase != (MemoryMap->TsegBase & ~(Inputs->TsegSize - 1))) {
    TsegBaseOrg = MemoryMap->TsegBase;
    if (Inputs->PrmrrSize > 1) {
      //
      // If PRMRR is present, naturally align TSEG up.
      //
      MemoryMap->TsegBase = (MemoryMap->TsegBase & ~(Inputs->TsegSize - 1)) + Inputs->TsegSize;
    } else {
      //
      // No PRMRR alignment needed so naturally align TSEG down.
      //
      MemoryMap->TsegBase = (MemoryMap->TsegBase & ~(Inputs->TsegSize - 1));
    }

    //
    // Calculate the delta to shift BDSM, GTT, and TOLUD with TSEG.
    // DPR is always right below TSEG so it's shift is implied.
    //
    TsegAlignment = ((INT32) MemoryMap->TsegBase) - ((INT32) TsegBaseOrg);
  } else {

    //
    // TSEG is already aligned
    //
    TsegAlignment = 0;
  }

  //
  // Shift everything up through TOLUD.
  //
  MemoryMap->GttBase   = ((UINT32) (((INT32) (MemoryMap->GttBase - PrmrrAlign)) + TsegAlignment));
  MemoryMap->BdsmBase  = ((UINT32) (((INT32) (MemoryMap->BdsmBase - PrmrrAlign)) + TsegAlignment));
  MemoryMap->ToludBase = ((UINT32) (((INT32) (MemoryMap->ToludBase - PrmrrAlign)) + TsegAlignment));

  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "TSEG base = %Xh\n", MemoryMap->TsegBase);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "GTT base = %Xh\n", MemoryMap->GttBase);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "BDSM base = %Xh\n", MemoryMap->BdsmBase);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "TOLUD base = %Xh\n", MemoryMap->ToludBase);

  //
  // In order to avoid memory hole, assign LowestBase to new aligned DPRBASE when PRMRR is absent.
  //

  if (Inputs->PrmrrSize == 0) {
    LowestBase = MemoryMap->TsegBase - Inputs->DprSize;
  }
  //
  // test if Reclaim is available
  // If "TOM minus ME Stolem Memory Size" is greater than the value of TOLUD, then memory reclaim is available to enable
  //
  if (Inputs->RemapEnable && (MemoryMap->TomMinusMe > MemoryMap->ToludBase)) {
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Reclaim Enable\n");
    MemoryMap->ReclaimEnable = TRUE;
    //
    // Remap Base
    // This is the maximum value by comparing between 4GB and "TOM minus ME size".
    //
    MemoryMap->RemapBase = MAX (MEM_4GB, MemoryMap->TomMinusMe);
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Remap Base %Xh\n", MemoryMap->RemapBase);
    //
    // Remap Limit
    // This is the value of REMAPBASE plus "the difference between the value in TOLUD
    // register and the lower of either 4GB or 'TOM minus ME Stolen memory size", and
    // then minus 1MB boundary.
    //
    MemoryMap->RemapLimit = MemoryMap->RemapBase + (MIN (MEM_4GB, MemoryMap->TomMinusMe) - MemoryMap->ToludBase);

    MemoryMap->TouudBase = MemoryMap->RemapLimit;

    MemoryMap->RemapLimit -= 0x1;

    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Remap Limit %Xh\n", MemoryMap->RemapLimit);
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "TOUUD Base %Xh\n", MemoryMap->TouudBase);
  } else {
    MemoryMap->ReclaimEnable = FALSE;
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Reclaim disable \n");
    //
    // TOUUD Base
    // If relcaim is disabled, this value is calculated by "TOM minus ME stolen size".
    //
    MemoryMap->TouudBase = MemoryMap->TomMinusMe;
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "TOUUD Base %Xh\n", MemoryMap->TouudBase);
  }
  //
  // GDXC must be aligned to 8MB boundary. But PSMI must be 64MB alligned
  // GdxcBase by subtracting Gdxc from BGSM.
  // @todo: GDXC is below DPRBASE if TXT is enabled, which is below TSEG. Maybe it will be required to be placed anywhere below TOLUD.
  //
  if (Outputs->Gdxc.GdxcEnable) {
    if (Inputs->MemoryTrace) {
      //
      // Put GDXC at the top of the second channel
      //
      if (MemoryMap->TotalPhysicalMemorySize <= MEM_4GB) {
        GdxcTop = MemoryMap->TouudBase;
      } else {
        GdxcTop = MemoryMap->TomMinusMe;
      }
    } else {
      //
      // Put GDXC below PRMRR region.
      //
      GdxcTop = LowestBase;
      GdxcLow = TRUE;
    }
    MemoryMap->GdxcMotSize = Outputs->Gdxc.GdxcMotSize << (23 - 20); // In MB
    MemoryMap->GdxcMotBase = GdxcTop - MemoryMap->GdxcMotSize;
    MemoryMap->GdxcMotBase &= ~(PSMI_SIZE_MB - 1);  // Round down to natural boundary according to PSMI size
    if (GdxcLow == TRUE) {
      LowestBase = MemoryMap->GdxcMotBase;
    }
    MemoryMap->GdxcIotSize = Outputs->Gdxc.GdxcIotSize << (23 - 20); // In MB
    MemoryMap->GdxcIotBase = MemoryMap->GdxcMotBase - MemoryMap->GdxcIotSize;
    MemoryMap->GdxcIotBase -= PSMI_SIZE_MB;  //PSMI buffer area
    if (GdxcLow == TRUE) {
      LowestBase = MemoryMap->GdxcIotBase;
    }
    MRC_DEBUG_MSG (
      Debug,
      MSG_LEVEL_NOTE,
      "GDXC MOT base %Xh, size %d (%Xh) MB\n",
      MemoryMap->GdxcMotBase,
      MemoryMap->GdxcMotSize,
      MemoryMap->GdxcMotSize
      );
    MRC_DEBUG_MSG (
      Debug,
      MSG_LEVEL_NOTE,
      "GDXC IOT base %Xh, size %d (%Xh) MB\n",
      MemoryMap->GdxcIotBase,
      MemoryMap->GdxcIotSize,
      MemoryMap->GdxcIotSize
      );
    if (Inputs->MemoryTrace) {
      //
      // Put PTT below lowest entry.
      //
      PttTop = LowestBase;
    } else {
      //
      // Put PTT below GDXC.
      //
      PttTop = MemoryMap->GdxcIotBase;
    }
  } else {
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "GDXC DISABLED\n");
    PttTop = LowestBase;
  }
  //
  // Shift from MB's to actual address.
  //
  LowestBase = LowestBase << 20;

#ifdef PTT_FLAG
  TpmStsFtif     = MrcCall->MrcMmioRead32 (R_PTT_TXT_STS_FTIF);
  if ((TpmStsFtif & V_FTIF_FTPM_PRESENT) == V_FTIF_FTPM_PRESENT) {
    //
    // PTT Stolen size is 4KB
    //
    MemoryMap->PttStolenBase = (PttTop << 20) - 0x1000;
    LowestBase = MemoryMap->PttStolenBase;
  }
#endif // PTT_FLAG

  MemoryMap->LowestBase = LowestBase;

  MemoryMap->MeStolenBase = MemoryMap->TomMinusMe;

  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "ME stolen base %Xh\n", MemoryMap->MeStolenBase);

  MemoryMap->MeStolenSize = Inputs->MeStolenSize;
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "ME stolen size %Xh\n", MemoryMap->MeStolenSize);

  UpdateMemoryMapRegisters (MrcData, Inputs->PciEBaseAddress, Inputs->GdxcBaseAddress, MemoryMap);
  return mrcSuccess;
}

/**
  This function find the total memory in the system.
  and write it to TotalPhysicalMemorySize in MrcData structure.

  @param[in, out] MrcData - Include all MRC global data.

  @retval Nothing
**/
void
MrcTotalMemory (
  IN OUT MrcParameters *const MrcData
  )
{
  MrcOutput         *Outputs;
  MrcControllerOut  *ControllerOut;
  MrcChannelOut     *ChannelOut;
  MrcDimmOut        *DimmOut;
  UINT8             Controller;
  UINT8             Channel;
  UINT8             Dimm;

  Outputs = &MrcData->Outputs;
  Outputs->MemoryMapData.TotalPhysicalMemorySize = 0;
  for (Controller = 0; Controller < MAX_CONTROLLERS; Controller++) {
    ControllerOut = &Outputs->Controller[Controller];
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      ChannelOut           = &ControllerOut->Channel[Channel];
      ChannelOut->Capacity = 0;
      if (MrcChannelExist (Outputs, Channel)) {
        for (Dimm = 0; Dimm < MAX_DIMMS_IN_CHANNEL; Dimm++) {
          DimmOut = &ChannelOut->Dimm[Dimm];
          if (DimmOut->Status == DIMM_PRESENT) {
            ChannelOut->Capacity += DimmOut->DimmCapacity;
          }
        }
        if (Outputs->BinnedLpddrDevices) {
          ChannelOut->Capacity = (ChannelOut->Capacity * 3) / 4;
        }
        ChannelOut->Capacity = MIN (ChannelOut->Capacity, Outputs->MrcTotalChannelLimit);
        Outputs->MemoryMapData.TotalPhysicalMemorySize += ChannelOut->Capacity;
      }
    }
  }

  return;
}

/**
  this function write to the memory init registers.

  @param[in] PciEBaseAddress - Address of the PCI Express BAR
  @param[in] GdxcBaseAddress - Address of the GDXC BAR
  @param[in] MemoryMap       - Include all the memory map definitions

  @retval Nothing
**/
void
UpdateMemoryMapRegisters (
  IN OUT MrcParameters  *const MrcData,
  IN const UINT32              PciEBaseAddress,
  IN const UINT32              GdxcBaseAddress,
  IN const MrcMemoryMap *const MemoryMap
  )
{
  MrcOutput                             *Outputs;
  const MRC_FUNCTION                    *MrcCall;
  UNCORE_CR_TOM_0_0_0_PCI_STRUCT        Tom;
  UNCORE_CR_TOLUD_0_0_0_PCI_STRUCT      Tolud;
  UNCORE_CR_TOUUD_0_0_0_PCI_STRUCT      Touud;
  UNCORE_CR_REMAPBASE_0_0_0_PCI_STRUCT  RemapBase;
  UNCORE_CR_REMAPLIMIT_0_0_0_PCI_STRUCT RemapLimit;
  UNCORE_CR_TSEGMB_0_0_0_PCI_STRUCT     Tsegmb;
  UNCORE_CR_BDSM_0_0_0_PCI_STRUCT       Bdsm;
  UNCORE_CR_BGSM_0_0_0_PCI_STRUCT       Bgsm;
  UNCORE_CR_MESEG_BASE_0_0_0_PCI_STRUCT MeSegBase;
  UNCORE_CR_MESEG_MASK_0_0_0_PCI_STRUCT MeSegMask;
  UNCORE_CR_DPR_0_0_0_PCI_STRUCT        Dpr;
  UINT32                                Offset;

  Outputs = &MrcData->Outputs;
  MrcCall = MrcData->Inputs.Call.Func;

  //
  // Write TOM register
  //
  Tom.Data     = MrcCall->MrcLeftShift64 (MemoryMap->TotalPhysicalMemorySize, UNCORE_CR_TOM_0_0_0_PCI_TOM_OFF);
  Offset       = PciEBaseAddress + MrcCall->MrcGetPcieDeviceAddress (0, 0, 0, UNCORE_CR_TOM_0_0_0_PCI_REG);
  MrcCall->MrcMmioWrite32 (Offset, Tom.Data32[0]);
  MrcCall->MrcMmioWrite32 (Offset  + 4, Tom.Data32[1]);

  //
  // Write TOLUD register
  //
  Tolud.Data       = 0;
  Tolud.Bits.TOLUD = MemoryMap->ToludBase;
  Offset           = PciEBaseAddress + MrcCall->MrcGetPcieDeviceAddress (0, 0, 0, UNCORE_CR_TOLUD_0_0_0_PCI_REG);
  MrcCall->MrcMmioWrite32 (Offset, Tolud.Data);

  //
  // Write TOUUD register
  //
  Touud.Data       = MrcCall->MrcLeftShift64 (MemoryMap->TouudBase, UNCORE_CR_TOUUD_0_0_0_PCI_TOUUD_OFF);
  Offset           = PciEBaseAddress + MrcCall->MrcGetPcieDeviceAddress (0, 0, 0, UNCORE_CR_TOUUD_0_0_0_PCI_REG);
  MrcCall->MrcMmioWrite32 (Offset, Touud.Data32[0]);
  MrcCall->MrcMmioWrite32 (Offset + 4, Touud.Data32[1]);

  if (MemoryMap->ReclaimEnable) {
    //
    // Write REMAPBASE register.
    //
    RemapBase.Data           = MrcCall->MrcLeftShift64 (MemoryMap->RemapBase, UNCORE_CR_REMAPBASE_0_0_0_PCI_REMAPBASE_OFF);
    Offset                   = PciEBaseAddress + MrcCall->MrcGetPcieDeviceAddress (0, 0, 0, UNCORE_CR_REMAPBASE_0_0_0_PCI_REG);
    MrcCall->MrcMmioWrite32 (Offset, RemapBase.Data32[0]);
    MrcCall->MrcMmioWrite32 (Offset + 4, RemapBase.Data32[1]);

    //
    // Write REMAPLIMIT register.
    //
    RemapLimit.Data          = MrcCall->MrcLeftShift64 (MemoryMap->RemapLimit, UNCORE_CR_REMAPLIMIT_0_0_0_PCI_REMAPLMT_OFF);
    Offset                   = PciEBaseAddress + MrcCall->MrcGetPcieDeviceAddress (0, 0, 0, UNCORE_CR_REMAPLIMIT_0_0_0_PCI_REG);
    MrcCall->MrcMmioWrite32 (Offset, RemapLimit.Data32[0]);
    MrcCall->MrcMmioWrite32 (Offset + 4, RemapLimit.Data32[1]);
  }
  //
  // Write TSEGMB register
  //
  Offset             = PciEBaseAddress + MrcCall->MrcGetPcieDeviceAddress (0, 0, 0, UNCORE_CR_TSEGMB_0_0_0_PCI_REG);
  Tsegmb.Data        = 0;
  Tsegmb.Bits.TSEGMB = MemoryMap->TsegBase;
  MrcCall->MrcMmioWrite32 (Offset, Tsegmb.Data);

  //
  // Program DPR Register with DPR size & DMA Protection Enabled
  //
  if (MemoryMap->DprSize != 0) {
    Offset           = PciEBaseAddress + MrcCall->MrcGetPcieDeviceAddress (0, 0, 0, UNCORE_CR_DPR_0_0_0_PCI_REG);
    Dpr.Data         = MrcCall->MrcMmioRead32 (Offset);
    Dpr.Bits.DPRSIZE = MemoryMap->DprSize;
    Dpr.Bits.EPM     = 1;
    MrcCall->MrcMmioWrite32 (Offset, Dpr.Data);
  }
  //
  // Write BDSM register
  //
  Offset          = PciEBaseAddress + MrcCall->MrcGetPcieDeviceAddress (0, 0, 0, UNCORE_CR_BDSM_0_0_0_PCI_REG);
  Bdsm.Data       = 0;
  Bdsm.Bits.BDSM  = MemoryMap->BdsmBase;
  MrcCall->MrcMmioWrite32 (Offset, Bdsm.Data);

  //
  // Write BGSM register
  //
  Offset          = PciEBaseAddress + MrcCall->MrcGetPcieDeviceAddress (0, 0, 0, UNCORE_CR_BGSM_0_0_0_PCI_REG);
  Bgsm.Data       = 0;
  Bgsm.Bits.BGSM  = MemoryMap->GttBase;
  MrcCall->MrcMmioWrite32 (Offset, Bgsm.Data);

  //
  // Enable ME Stolen Memory if the size is not zero
  //
  if (MemoryMap->MeStolenSize != 0) {
    //
    // Write MESEG_MASK register. Must be written before MESEG_BASE.
    //
    MeSegMask.Data                   = MrcCall->MrcLeftShift64 ((~(MemoryMap->MeStolenSize) + 1) & UNCORE_CR_MESEG_MASK_0_0_0_PCI_MEMASK_MAX, UNCORE_CR_MESEG_MASK_0_0_0_PCI_MEMASK_OFF);
    MeSegMask.Bits.ME_STLEN_EN       = 1;
    Offset                           = PciEBaseAddress + MrcCall->MrcGetPcieDeviceAddress (0, 0, 0, UNCORE_CR_MESEG_MASK_0_0_0_PCI_REG);
    MrcCall->MrcMmioWrite32 (Offset, MeSegMask.Data32[0]);
    MrcCall->MrcMmioWrite32 (Offset + 4, MeSegMask.Data32[1]);

    //
    // Write MESEG_BASE register
    //
    MeSegBase.Data        = MrcCall->MrcLeftShift64 (MemoryMap->MeStolenBase, UNCORE_CR_MESEG_BASE_0_0_0_PCI_MEBASE_OFF);
    Offset                = PciEBaseAddress + MrcCall->MrcGetPcieDeviceAddress (0, 0, 0, UNCORE_CR_MESEG_BASE_0_0_0_PCI_REG);
    MrcCall->MrcMmioWrite32 (Offset, MeSegBase.Data32[0]);
    MrcCall->MrcMmioWrite32 (Offset + 4, MeSegBase.Data32[1]);
  }

  //
  // Write graphics control register
  //
  Offset = PciEBaseAddress + MrcCall->MrcGetPcieDeviceAddress (0, 0, 0, UNCORE_CR_GGC_0_0_0_PCI_REG);
  MrcCall->MrcMmioWrite32 (Offset, MemoryMap->GraphicsControlRegister);

  if (Outputs->Gdxc.GdxcEnable) {
    //
    // Program GDXC Registers
    // 1st MOT: 0x10, 0x14 and 0x18 (Address Low, Address High and Region)
    // 2nd IOT: 0x20, 0x24 and 0x28 (Address Low, Address High and Region)
    // Program Address High last as it has lock bit
    //
    MrcCall->MrcMmioWrite32 (
               GdxcBaseAddress + MPCOHTRK_CR_GDXC_MOT_REGION_REG,
               MemoryMap->GdxcMotBase >> 3 |  // (GdxcMotBase << 20) >> 23, MOT_REGION.START_ADDRESS is bits [38:23]
               (((MemoryMap->GdxcMotBase + MemoryMap->GdxcMotSize) >> 3) << 16));

    MrcCall->MrcMmioWrite32 (
               GdxcBaseAddress + MPCOHTRK_CR_GDXC_MOT_ADDRESS_LO_REG,
               MemoryMap->GdxcMotBase << 14);   // (GdxcMotBase << 20) >> 6, Current Pointer in cache line units

    MrcCall->MrcMmioWrite32 (
               GdxcBaseAddress + MPCOHTRK_CR_GDXC_MOT_ADDRESS_HI_REG,
               (MemoryMap->GdxcMotBase & MRC_BIT18) >> 18); // Bit [18] will be bit [32], so it goes to MOT_ADDRESS_HI.MEM_PTR

    MrcCall->MrcMmioWrite32 (
               GdxcBaseAddress + MPCOHTRK_CR_GDXC_OCLA_REGION_REG,
               MemoryMap->GdxcIotBase >> 3 |  // (GdxcIotBase << 20) >> 23, OCLA_REGION.START_ADDRESS is bits [38:23]
               (((MemoryMap->GdxcIotBase + MemoryMap->GdxcIotSize) >> 3) << 16));

    MrcCall->MrcMmioWrite32 (
               GdxcBaseAddress + MPCOHTRK_CR_GDXC_OCLA_ADDRESS_LO_REG,
               MemoryMap->GdxcIotBase << 14);   // (GdxcIotBase << 20) >> 6, Current Pointer in cache line units

    MrcCall->MrcMmioWrite32 (
               GdxcBaseAddress + MPCOHTRK_CR_GDXC_OCLA_ADDRESS_HI_REG,
               MPCOHTRK_CR_GDXC_OCLA_ADDRESS_HI_LOCK_MSK | (MemoryMap->GdxcIotBase & MRC_BIT18) >> 18); // Bit [18] will be bit [32], goes to IOT_ADDRESS_HI.MEM_PTR
  } else {
    //
    // Must lock GDXC registers even when GDXC is disabled
    //
    MrcCall->MrcMmioWrite32 (GdxcBaseAddress + MPCOHTRK_CR_GDXC_OCLA_ADDRESS_HI_REG, MPCOHTRK_CR_GDXC_OCLA_ADDRESS_HI_LOCK_MSK);
  }

  return;
}

/**
  Input parameter for Bit Error Recovery Address compared against Memory Map

  @param[in, out] MrcData  - The MRC "global data" area.
  @param[in]      Address  - UINT64 Address to be compared against Memory Map

  @retval mrcSuccess if Address is within Memory Map and mrcFail if Address is outside Memory Map
**/
MrcStatus
MrcBitErrRecAddressCompare (
  IN OUT MrcParameters *const MrcData,
  IN     UINT64               Address
  )
{
  const MRC_FUNCTION                  *MrcCall;
  MrcInput                            *Inputs;
  MrcOutput                           *Outputs;
  MrcDebug                            *Debug;
  MrcStatus                           Status;
  UINT64                              AddressMB;
  MrcMemoryMap                        *MemoryMap;
  UINT32                              Tolud;
  UINT32                              Touud;

  Inputs    = &MrcData->Inputs;
  Outputs   = &MrcData->Outputs;
  MrcCall   = Inputs->Call.Func;
  Debug     = &Outputs->Debug;
  MemoryMap = &Outputs->MemoryMapData;

  AddressMB = MrcCall->MrcRightShift64 (Address, 20);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "BER Address 0x%x_%08x Compare, MB aligned 0x%x_%08x\n", (UINT32) (MrcCall->MrcRightShift64 (Address, 32)), (UINT32) (Address), (UINT32) (MrcCall->MrcRightShift64 (AddressMB, 32)), (UINT32) (AddressMB));

  Tolud = MemoryMap->ToludBase;
  Touud = MemoryMap->TouudBase;
  if ((AddressMB < Tolud) || ((AddressMB >= MEM_4GB) && (AddressMB < Touud))) {
    Status = mrcSuccess;
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Within Memory Map\n");
  } else {
    Status = mrcFail;
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Outside Memory Map, TOLUD_MB 0x%x, TOUUD_MB 0x%x\n", Tolud, Touud);
  }

  return Status;
}
