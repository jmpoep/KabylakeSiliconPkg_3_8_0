/** @file
  PCH HSIO Initialization file

 @copyright
  INTEL CONFIDENTIAL
  Copyright 2014 - 2017 Intel Corporation.

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

#include <Library/PeiMeLib.h>
#include <BupMsgs.h>
#include "PchInitPei.h"
#include "PchHsioLaneLib.h"
#include <Library/PeiServicesTablePointerLib.h>
#include <Private/PchHsio.h>
#include <ChipsetInfoHob.h>
#include <Library/ConfigBlockLib.h>
#include <SaPolicyCommon.h>
#include <ConfigBlock/PciePeiPreMemConfig.h>
#include <Library/PchHsioLib.h>

/**
  The function is used to detemine if a ChipsetInitSync with ME is required and syncs with ME if required.

  @param[in] MeSync               Sync ME Settings

  @retval EFI_SUCCESS             BIOS and ME ChipsetInit settings are in sync
  @retval EFI_UNSUPPORTED         BIOS and ME ChipsetInit settings are not in sync
**/
EFI_STATUS
PchHsioChipsetInitProg (
  IN  BOOLEAN                      MeSync
  )
{
  EFI_STATUS                  Status;
  UINT16                      BiosChipInitCrc;
  CHIPSET_INIT_INFO           *ChipsetInitHob;
  EFI_PEI_HOB_POINTERS        HobList;
  CHIPSET_INIT_INFO           ChipsetInitHobStruct;
  SI_PREMEM_POLICY_PPI        *SiPreMemPolicyPpi;
  PCIE_PEI_PREMEM_CONFIG      *PciePeiPreMemConfig;
  PCH_HSIO_PREMEM_CONFIG      *HsioPreMemConfig;
  EFI_BOOT_MODE               BootMode;
  UINT32                      PchChipsetInitTableLength;
  UINT8                       *PchChipsetInitTable;

  ///
  /// Step 1
  /// GetBoodMode, do not perform ChipsetInit Sync check on S3 RESUME
  ///
  Status = PeiServicesGetBootMode (&BootMode);
  if (BootMode == BOOT_ON_S3_RESUME) {
    return EFI_SUCCESS;
  }

  ///
  /// Step 2
  /// Assign appropriate ChipsetInit table
  ///
  if (GetPchGeneration () == SklPch) {
    switch (PchStepping ()) {
      case PchLpB0:
      case PchLpB1:
        PchChipsetInitTable = PchLpChipsetInitTable_Bx;
        PchChipsetInitTableLength = sizeof (PchLpChipsetInitTable_Bx);
        break;
      case PchLpC0:
      case PchLpC1:
        PchChipsetInitTable = PchLpChipsetInitTable_Cx;
        PchChipsetInitTableLength = sizeof (PchLpChipsetInitTable_Cx);
        break;
      case PchHB0:
      case PchHC0:
        PchChipsetInitTable = PchHChipsetInitTable_Bx;
        PchChipsetInitTableLength = sizeof (PchHChipsetInitTable_Bx);
        break;
      case PchHD0:
      case PchHD1:
        PchChipsetInitTable = PchHChipsetInitTable_Dx;
        PchChipsetInitTableLength = sizeof (PchHChipsetInitTable_Dx);
        break;
      default:
        PchChipsetInitTable = NULL;
        PchChipsetInitTableLength   = 0;
        DEBUG ((DEBUG_ERROR, "Unsupported PCH Stepping\n"));
        return EFI_UNSUPPORTED;
    }
  } else {
    switch (PchStepping ()) {
      case KblPchHA0:
        PchChipsetInitTable = KblPchHChipsetInitTable_Ax;
        PchChipsetInitTableLength = sizeof (KblPchHChipsetInitTable_Ax);
        break;
      default:
        PchChipsetInitTable = NULL;
        PchChipsetInitTableLength   = 0;
        DEBUG ((DEBUG_ERROR, "Unsupported PCH Stepping\n"));
        return EFI_UNSUPPORTED;
    }
  }

  ///
  /// Step 3
  /// Send the HECI HSIO Message
  ///
  ///
  /// Get Policy settings through the SiPreMemPolicy PPI
  ///
  //
  // Set to NULL first in case some compiling environment failed with "potentially uninitialized local variable used"
  //
  HsioPreMemConfig = NULL;
  Status = PeiServicesLocatePpi (
             &gSiPreMemPolicyPpiGuid,
             0,
             NULL,
             (VOID **) &SiPreMemPolicyPpi
             );
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "SiPreMemPolicyPpi is not located! Error: %r\n", Status));
    return EFI_UNSUPPORTED;
  }
  Status = GetConfigBlock ((VOID *) SiPreMemPolicyPpi, &gHsioPreMemConfigGuid, (VOID *) &HsioPreMemConfig);
  ASSERT_EFI_ERROR (Status);

  if (HsioPreMemConfig->ChipsetInitMessage == 0) {
    DEBUG ((DEBUG_INFO, "HsioPreMemConfig->ChipsetInitMessage = 0, do not perform HSIO sync. \n"));
    return EFI_SUCCESS;
  }

  Status         = EFI_SUCCESS;
  ChipsetInitHob = NULL;

  HobList.Guid   = GetFirstGuidHob (&gChipsetInitHobGuid);
  if (HobList.Guid != NULL) {
    ChipsetInitHob = GET_GUID_HOB_DATA (HobList.Guid);
  }
  if (ChipsetInitHob == NULL) {

    UINT16  MeChipInitCrc = 0;

    DEBUG ((DEBUG_INFO, "(Hsio) ChipsetInitHob not found\n"));
    Status = PeiHeciHsioMsg (HSIO_REPORT_VERSION_REQ, &MeChipInitCrc);
    if (!EFI_ERROR (Status)) {
      DEBUG ((DEBUG_INFO, "(Hsio) Creating HOB to adjust Hsio settings in PchInit, if required\n"));
      //
      // Initialize ChipsetInitHob
      //
      ZeroMem (&ChipsetInitHobStruct, sizeof (CHIPSET_INIT_INFO));
      ChipsetInitHobStruct.Revision        = CHIPSET_INIT_INFO_REVISION;
      ChipsetInitHobStruct.MeChipInitCrc   = MeChipInitCrc;
      ChipsetInitHobStruct.BiosChipInitCrc = *((UINT16*) PchChipsetInitTable);

      ChipsetInitHob = BuildGuidDataHob (
                         &gChipsetInitHobGuid,
                         &ChipsetInitHobStruct,
                         sizeof (CHIPSET_INIT_INFO)
                         );
      if (ChipsetInitHob == NULL) {
        DEBUG ((DEBUG_ERROR, "(Hsio) ChipsetInitHob could not be created\n"));
        ASSERT (FALSE);
        return EFI_ABORTED;
      }
    }
  }

  if (Status == EFI_SUCCESS) {
    DEBUG ((DEBUG_INFO, "(Hsio) ME Reported CRC=0x%04X\n", ChipsetInitHob->MeChipInitCrc));
    //
    // Get ChipsetInit table indentifier from the one found in the code
    //
    BiosChipInitCrc = *((UINT16*) PchChipsetInitTable);
    DEBUG ((DEBUG_INFO, "(Hsio) BIOS Hsio CRC=0x%04X\n", BiosChipInitCrc));

    if (ChipsetInitHob->MeChipInitCrc != BiosChipInitCrc) {
      if (MeSync == TRUE) {
        Status = PeiHeciChipsetInitSyncMsg (PchChipsetInitTable, PchChipsetInitTableLength, (BOOLEAN) HsioPreMemConfig->BypassPhySyncReset);
        if (EFI_ERROR (Status)) {
          DEBUG ((DEBUG_ERROR, "ChipsetInit Sync Error: %r\n", Status));
          if (Status == EFI_UNSUPPORTED || Status == EFI_DEVICE_ERROR) {
            DEBUG ((DEBUG_ERROR, "Current Me Bios boot path doesn't support Chipset Init Sync message, continue to boot.\n", Status));
          } else {
            ASSERT_EFI_ERROR (Status);
            return EFI_UNSUPPORTED;
          }
        }
      } else {
        ///
        /// Get config block settings through the SiPreMemPolicy PPI
        ///
        Status = GetConfigBlock ((VOID *) SiPreMemPolicyPpi, &gSaPciePeiPreMemConfigGuid, (VOID *) &PciePeiPreMemConfig);
        ASSERT_EFI_ERROR (Status);

        //
        //  Skip the Hsio programming and set DMI's max link speed to Gen1 as default
        //  ChipsetInit settings may not be good enough to train DMI Link to speed > Gen1
        //
        PciePeiPreMemConfig->DmiMaxLinkSpeed = 1;

        DEBUG ((DEBUG_INFO, "(Hsio) Override DMI Max Gen Speed to 1\n"));

        return EFI_UNSUPPORTED;
      }
    }
  } else {
    DEBUG ((DEBUG_INFO, "(Hsio) Syncing ChipsetInit with ME failed! Error: %r\n", Status));
  }
  return EFI_SUCCESS;
}


/**
  The function indicates if at least one of the data lanes attached
  to a specific common lane is of a specific phymode.

  @param[in] Pid               Common Lane End Point ID
  @param[in] PhyMode           Phymode that needs to be checked
  @param[in] PchSeries         Indicates the Pch Series
  @param[in] Los1              Lane Owner Status 1 Value
  @param[in] Los2              Lane Owner Status 2 Value
  @param[in] Los3              Lane Owner Status 3 Value
  @param[in] Los4              Lane Owner Status 4 Value

  @retval EFI_SUCCESS          Phymode exists.
          EFI_UNSUPPORTED      Phymode does not exist.
**/
EFI_STATUS
PchLosPhyModeCheck (
  IN  PCH_SBI_PID                       Pid,
  IN  UINT8                             PhyMode,
  IN PCH_SERIES                         PchSeries,
  IN UINT32                             Los1,
  IN UINT32                             Los2,
  IN UINT32                             Los3,
  IN UINT32                             Los4
  )
{
  UINT8                       Shift;

  switch (Pid) {
    case PID_MODPHY0:
      if (PchSeries == PchLp) {
        for (Shift = PCH_MODPHY0_LP_LOS1_LANE_START; Shift <= PCH_MODPHY0_LP_LOS1_LANE_END; Shift++) {
          if (((Los1 >> (Shift * 4)) & 0xF) == PhyMode) {
            return EFI_SUCCESS;
          }
        }
      } else if (PchSeries == PchH) {
        for (Shift = PCH_MODPHY0_H_LOS1_LANE_START; Shift <= PCH_MODPHY0_H_LOS1_LANE_END; Shift++) {
          if (((Los1 >> (Shift * 4)) & 0xF) == PhyMode) {
            return EFI_SUCCESS;
          }
        }
      }
      break;
    case PID_MODPHY1:
      if (PchSeries == PchLp) {
        for (Shift = PCH_MODPHY1_LP_LOS1_LANE_START; Shift <= PCH_MODPHY1_LP_LOS1_LANE_END; Shift++) {
          if (((Los1 >> (Shift * 4)) & 0xF) == PhyMode) {
            return EFI_SUCCESS;
          }
        }
        for (Shift = PCH_MODPHY1_LP_LOS2_LANE_START; Shift <= PCH_MODPHY1_LP_LOS2_LANE_END; Shift++) {
          if (((Los2 >> (Shift * 4)) & 0xF) == PhyMode) {
            return EFI_SUCCESS;
          }
        }
      } else if (PchSeries == PchH) {
        for (Shift = PCH_MODPHY1_H_LOS1_LANE_START; Shift <= PCH_MODPHY1_H_LOS1_LANE_END; Shift++) {
          if (((Los1 >> (Shift * 4)) & 0xF) == PhyMode) {
            return EFI_SUCCESS;
          }
        }
        for (Shift = PCH_MODPHY1_H_LOS2_LANE_START; Shift <= PCH_MODPHY1_H_LOS2_LANE_END; Shift++) {
          if (((Los2 >> (Shift * 4)) & 0xF) == PhyMode) {
            return EFI_SUCCESS;
          }
        }
      }
      break;
    case PID_MODPHY2:
      if (PchSeries == PchLp) {
        for (Shift = PCH_MODPHY2_LP_LOS2_LANE_START; Shift <= PCH_MODPHY2_LP_LOS2_LANE_END; Shift++) {
          if (((Los2 >> (Shift * 4)) & 0xF) == PhyMode) {
            return EFI_SUCCESS;
          }
        }
      } else if (PchSeries == PchH) {
        for (Shift = PCH_MODPHY2_H_LOS2_LANE_START; Shift <= PCH_MODPHY2_H_LOS2_LANE_END; Shift++) {
          if (((Los2 >> (Shift * 4)) & 0xF) == PhyMode) {
            return EFI_SUCCESS;
          }
        }
        for (Shift = PCH_MODPHY2_H_LOS3_LANE_START; Shift <= PCH_MODPHY2_H_LOS3_LANE_END; Shift++) {
          if (((Los3 >> (Shift * 4)) & 0xF) == PhyMode) {
            return EFI_SUCCESS;
          }
        }
      }
      break;
    case PID_MODPHY3:
      if (PchSeries == PchLp) {
        //Nothing required for Common Lane 3 as this just has the SATA PLL
        return EFI_SUCCESS;
      } else if (PchSeries == PchH) {
        for (Shift = PCH_MODPHY3_H_LOS3_LANE_START; Shift <= PCH_MODPHY3_H_LOS3_LANE_END; Shift++) {
          if (((Los3 >> (Shift * 4)) & 0xF) == PhyMode) {
            return EFI_SUCCESS;
          }
        }
        for (Shift = PCH_MODPHY3_H_LOS4_LANE_START; Shift <= PCH_MODPHY3_H_LOS4_LANE_END; Shift++) {
          if (((Los4 >> (Shift * 4)) & 0xF) == PhyMode) {
            return EFI_SUCCESS;
          }
        }
      }
      break;
    case PID_MODPHY4:
      //
      // MODPHY4 contains only PCIE lanes
      //
      if (PhyMode == V_PCH_PCR_FIA_LANE_OWN_PCIEDMI) {
        return EFI_SUCCESS;
      } else {
        return EFI_UNSUPPORTED;
      }
    default:
      return EFI_SUCCESS;
      break;
  }
  return EFI_UNSUPPORTED;
}

/**
  The function programs HSIO Rx\Tx Eq policy registers.

  @param[in]  SiPreMemPolicyPpi  The SI PreMem Policy PPI instance
**/
VOID
PchHsioRxTxEqPolicyProg (
  IN  SI_PREMEM_POLICY_PPI       *SiPreMemPolicyPpi
  )
{
  HSIO_LANE                   HsioLane;
  UINT16                      Offset;
  UINT8                       Index;
  UINT8                       PortId;
  UINT8                       LaneOwner;
  UINT8                       MaxSataPorts;
  UINT8                       MaxPciePorts;
  UINT8                       LaneNum;
  UINTN                       RpBase;
  UINT32                      Data32;
  UINT32                      Data32And;
  UINT32                      Data32Or;
  UINT32                      RpToRetrain;
  UINT32                      TimeSpent;
  EFI_STATUS                  Status;
  PCH_HSIO_SATA_PREMEM_CONFIG *HsioSataPreMemConfig;
  PCH_HSIO_PCIE_PREMEM_CONFIG *HsioPciePreMemConfig;

  Status = GetConfigBlock ((VOID *) SiPreMemPolicyPpi, &gHsioSataPreMemConfigGuid, (VOID *) &HsioSataPreMemConfig);
  ASSERT_EFI_ERROR (Status);
  Status = GetConfigBlock ((VOID *) SiPreMemPolicyPpi, &gHsioPciePreMemConfigGuid, (VOID *) &HsioPciePreMemConfig);
  ASSERT_EFI_ERROR (Status);

  MaxSataPorts = GetPchMaxSataPortNum ();
  MaxPciePorts = GetPchMaxPciePortNum ();
  for (Index = 0; Index < MaxSataPorts; Index++) {
    Status = PchGetSataLaneNum (Index, &LaneNum);
    if (EFI_ERROR (Status)) {
      continue;
    }
    PchGetLaneInfo (LaneNum, &PortId, &LaneOwner);
    if (LaneOwner == V_PCH_PCR_FIA_LANE_OWN_SATA) {
      HsioGetLane (LaneNum, &HsioLane);

      if ((HsioSataPreMemConfig->PortLane[Index].HsioRxGen1EqBoostMagEnable == TRUE) ||
          (HsioSataPreMemConfig->PortLane[Index].HsioRxGen2EqBoostMagEnable == TRUE)) {
        Offset = HsioLane.Base + (UINT16) R_PCH_HSIO_RX_DWORD21;
        Data32Or  = 0;
        Data32And = 0xFFFFFFFF;
        if (HsioSataPreMemConfig->PortLane[Index].HsioRxGen1EqBoostMagEnable == TRUE) {
          Data32Or |= (UINT32) (HsioSataPreMemConfig->PortLane[Index].HsioRxGen1EqBoostMag << N_PCH_HSIO_RX_DWORD21_ICFGCTLEDATATAP_QUATRATE_5_0);
          Data32And &= (UINT32) ~B_PCH_HSIO_RX_DWORD21_ICFGCTLEDATATAP_QUATRATE_5_0;
        }

        if (HsioSataPreMemConfig->PortLane[Index].HsioRxGen2EqBoostMagEnable == TRUE) {
          Data32Or |= (UINT32) (HsioSataPreMemConfig->PortLane[Index].HsioRxGen2EqBoostMag << N_PCH_HSIO_RX_DWORD21_ICFGCTLEDATATAP_HALFRATE_5_0);
          Data32And &= (UINT32) ~B_PCH_HSIO_RX_DWORD21_ICFGCTLEDATATAP_HALFRATE_5_0;
        }

        PchPcrAndThenOr32 (
          (PCH_SBI_PID) PortId,
          (UINT16) Offset,
          Data32And,
          Data32Or);
        PchPcrRead32 ((PCH_SBI_PID) PortId, Offset, &Data32);
        DEBUG ((DEBUG_INFO, "HSIO : PortID = 0x%02x, Offset = 0x%04x, Value = 0x%08x\n", (PCH_SBI_PID) PortId, (UINT16) Offset, (UINT32) Data32));
      }

      if (HsioSataPreMemConfig->PortLane[Index].HsioRxGen3EqBoostMagEnable == TRUE) {
        Offset = HsioLane.Base + (UINT16) R_PCH_HSIO_RX_DWORD26;
        PchPcrAndThenOr32 (
          (PCH_SBI_PID) PortId,
          (UINT16) Offset,
          (UINT32) ~0,
          (UINT32) B_PCH_HSIO_RX_DWORD26_SATA_EQ_DIS);
        PchPcrRead32 ((PCH_SBI_PID) PortId, Offset, &Data32);
        DEBUG ((DEBUG_INFO, "HSIO : PortID = 0x%02x, Offset = 0x%04x, Value = 0x%08x\n", (PCH_SBI_PID) PortId, (UINT16) Offset, (UINT32) Data32));

        Offset = HsioLane.Base + (UINT16) R_PCH_HSIO_RX_DWORD20;
        PchPcrAndThenOr32 (
          (PCH_SBI_PID) PortId,
          (UINT16) Offset,
          (UINT32) ~B_PCH_HSIO_RX_DWORD20_ICFGCTLEDATATAP_FULLRATE_5_0,
          (UINT32) (HsioSataPreMemConfig->PortLane[Index].HsioRxGen3EqBoostMag << N_PCH_HSIO_RX_DWORD20_ICFGCTLEDATATAP_FULLRATE_5_0));
        PchPcrRead32 ((PCH_SBI_PID) PortId, Offset, &Data32);
        DEBUG ((DEBUG_INFO, "HSIO : PortID = 0x%02x, Offset = 0x%04x, Value = 0x%08x\n", (PCH_SBI_PID) PortId, (UINT16) Offset, (UINT32) Data32));
      }

      if ((HsioSataPreMemConfig->PortLane[Index].HsioTxGen1DownscaleAmpEnable == TRUE) ||
          (HsioSataPreMemConfig->PortLane[Index].HsioTxGen2DownscaleAmpEnable == TRUE) ||
          (HsioSataPreMemConfig->PortLane[Index].HsioTxGen3DownscaleAmpEnable == TRUE)) {

        Data32Or  = 0;
        Data32And = 0xFFFFFFFF;
        if (HsioSataPreMemConfig->PortLane[Index].HsioTxGen1DownscaleAmpEnable == TRUE) {
          Data32Or |= (UINT32) (HsioSataPreMemConfig->PortLane[Index].HsioTxGen1DownscaleAmp << N_PCH_HSIO_TX_DWORD8_ORATE00MARGIN_5_0);
          Data32And &= (UINT32) ~B_PCH_HSIO_TX_DWORD8_ORATE00MARGIN_5_0;
        }

        if (HsioSataPreMemConfig->PortLane[Index].HsioTxGen2DownscaleAmpEnable == TRUE) {
          Data32Or |= (UINT32) (HsioSataPreMemConfig->PortLane[Index].HsioTxGen2DownscaleAmp << N_PCH_HSIO_TX_DWORD8_ORATE01MARGIN_5_0);
          Data32And &= (UINT32) ~B_PCH_HSIO_TX_DWORD8_ORATE01MARGIN_5_0;
        }

        if (HsioSataPreMemConfig->PortLane[Index].HsioTxGen3DownscaleAmpEnable == TRUE) {
          Data32Or |= (UINT32) (HsioSataPreMemConfig->PortLane[Index].HsioTxGen3DownscaleAmp << N_PCH_HSIO_TX_DWORD8_ORATE10MARGIN_5_0);
          Data32And &= (UINT32) ~B_PCH_HSIO_TX_DWORD8_ORATE10MARGIN_5_0;
        }

        Offset = HsioLane.Base + (UINT16) R_PCH_HSIO_TX_DWORD8;
        PchPcrAndThenOr32 (
          (PCH_SBI_PID) PortId,
          (UINT16) Offset,
          Data32And,
          Data32Or);
        PchPcrRead32 ((PCH_SBI_PID) PortId, Offset, &Data32);
        DEBUG ((DEBUG_INFO, "HSIO : PortID = 0x%02x, Offset = 0x%04x, Value = 0x%08x\n", (PCH_SBI_PID) PortId, (UINT16) Offset, (UINT32) Data32));
      }

      if ((HsioSataPreMemConfig->PortLane[Index].HsioTxGen1DeEmphEnable == TRUE) ||
          (HsioSataPreMemConfig->PortLane[Index].HsioTxGen2DeEmphEnable == TRUE) ||
          (HsioSataPreMemConfig->PortLane[Index].HsioTxGen3DeEmphEnable == TRUE)) {
        Offset = HsioLane.Base + (UINT16) R_PCH_HSIO_TX_DWORD6;
        Data32Or  = 0;
        Data32And = 0xFFFFFFFF;
        if (HsioSataPreMemConfig->PortLane[Index].HsioTxGen1DeEmphEnable == TRUE) {
          Data32Or |= (UINT32) (HsioSataPreMemConfig->PortLane[Index].HsioTxGen1DeEmph);
          Data32And &= (UINT32) ~B_PCH_HSIO_TX_DWORD6_OW2TAPGEN1DEEMPH6P0_5_0;
        }

        if (HsioSataPreMemConfig->PortLane[Index].HsioTxGen2DeEmphEnable == TRUE) {
          Data32Or |= (UINT32) (HsioSataPreMemConfig->PortLane[Index].HsioTxGen2DeEmph << N_PCH_HSIO_TX_DWORD6_OW2TAPGEN2DEEMPH6P0_5_0);
          Data32And &= (UINT32) ~B_PCH_HSIO_TX_DWORD6_OW2TAPGEN2DEEMPH6P0_5_0;
        }

        if (HsioSataPreMemConfig->PortLane[Index].HsioTxGen3DeEmphEnable == TRUE) {
          Data32Or |= (UINT32) (HsioSataPreMemConfig->PortLane[Index].HsioTxGen3DeEmph << N_PCH_HSIO_TX_DWORD6_OW2TAPGEN3DEEMPH6P0_5_0);
          Data32And &= (UINT32) ~B_PCH_HSIO_TX_DWORD6_OW2TAPGEN3DEEMPH6P0_5_0;
        }

        PchPcrAndThenOr32 (
          (PCH_SBI_PID) PortId,
          (UINT16) Offset,
          Data32And,
          Data32Or);
        PchPcrRead32 ((PCH_SBI_PID) PortId, Offset, &Data32);
        DEBUG ((DEBUG_INFO, "HSIO : PortID = 0x%02x, Offset = 0x%04x, Value = 0x%08x\n", (PCH_SBI_PID) PortId, (UINT16) Offset, (UINT32) Data32));
      }
    }
  }
  RpToRetrain = 0;
  for (Index = 0; Index < MaxPciePorts; Index++) {
    RpBase = PchPcieBase (Index);
    Status = PchGetPcieLaneNum (Index, &LaneNum);
    if (EFI_ERROR (Status)) {
      continue;
    }
    PchGetLaneInfo (LaneNum, &PortId, &LaneOwner);
    if (LaneOwner == V_PCH_PCR_FIA_LANE_OWN_PCIEDMI) {
      HsioGetLane (LaneNum, &HsioLane);
      if (HsioPciePreMemConfig->Lane[Index].HsioRxSetCtleEnable == TRUE) {
        Offset = HsioLane.Base + (UINT16) R_PCH_HSIO_RX_DWORD25;
        PchPcrAndThenOr32 (
          (PCH_SBI_PID) PortId,
          (UINT16) Offset,
          (UINT32) ~B_PCH_HSIO_RX_DWORD25_CTLE_ADAPT_OFFSET_CFG_4_0,
          (UINT32) (HsioPciePreMemConfig->Lane[Index].HsioRxSetCtle << N_PCH_HSIO_RX_DWORD25_CTLE_ADAPT_OFFSET_CFG_4_0));
        PchPcrRead32 ((PCH_SBI_PID) PortId, Offset, &Data32);
        DEBUG ((DEBUG_INFO, "HSIO : PortID = 0x%02x, Offset = 0x%04x, Value = 0x%08x\n", (PCH_SBI_PID) PortId, (UINT16) Offset, (UINT32) Data32));
      }

      if ((HsioPciePreMemConfig->Lane[Index].HsioTxGen1DownscaleAmpEnable == TRUE) || (HsioPciePreMemConfig->Lane[Index].HsioTxGen1DeEmphEnable == TRUE)) {
        //
        // Remember which ports were populated before temporarily disabling them
        //
        if ((MmioRead32 (RpBase) != 0xFFFFFFFF) && (MmioRead16 (RpBase + R_PCH_PCIE_LSTS) & B_PCIE_LSTS_LA)) {
          RpToRetrain |= (BIT0 << Index);
        }
        MmioOr8 (RpBase + R_PCH_PCIE_LCTL, B_PCIE_LCTL_LD);
      }

      if ((HsioPciePreMemConfig->Lane[Index].HsioTxGen1DownscaleAmpEnable == TRUE) ||
          (HsioPciePreMemConfig->Lane[Index].HsioTxGen2DownscaleAmpEnable == TRUE) ||
          (HsioPciePreMemConfig->Lane[Index].HsioTxGen3DownscaleAmpEnable == TRUE)) {

        Data32Or  = 0;
        Data32And = 0xFFFFFFFF;
        if (HsioPciePreMemConfig->Lane[Index].HsioTxGen1DownscaleAmpEnable == TRUE) {
          Data32Or |= (UINT32) (HsioPciePreMemConfig->Lane[Index].HsioTxGen1DownscaleAmp << N_PCH_HSIO_TX_DWORD8_ORATE00MARGIN_5_0);
          Data32And &= (UINT32) ~B_PCH_HSIO_TX_DWORD8_ORATE00MARGIN_5_0;
        }

        if (HsioPciePreMemConfig->Lane[Index].HsioTxGen2DownscaleAmpEnable == TRUE) {
          Data32Or |= (UINT32) (HsioPciePreMemConfig->Lane[Index].HsioTxGen2DownscaleAmp << N_PCH_HSIO_TX_DWORD8_ORATE01MARGIN_5_0);
          Data32And &= (UINT32) ~B_PCH_HSIO_TX_DWORD8_ORATE01MARGIN_5_0;
        }

        if (HsioPciePreMemConfig->Lane[Index].HsioTxGen3DownscaleAmpEnable == TRUE) {
          Data32Or |= (UINT32) (HsioPciePreMemConfig->Lane[Index].HsioTxGen3DownscaleAmp << N_PCH_HSIO_TX_DWORD8_ORATE10MARGIN_5_0);
          Data32And &= (UINT32) ~B_PCH_HSIO_TX_DWORD8_ORATE10MARGIN_5_0;
        }

        Offset = HsioLane.Base + (UINT16) R_PCH_HSIO_TX_DWORD8;
        PchPcrAndThenOr32 (
          (PCH_SBI_PID) PortId,
          (UINT16) Offset,
          Data32And,
          Data32Or);
        PchPcrRead32 ((PCH_SBI_PID) PortId, Offset, &Data32);
        DEBUG ((DEBUG_INFO, "HSIO : PortID = 0x%02x, Offset = 0x%04x, Value = 0x%08x\n", (PCH_SBI_PID) PortId, (UINT16) Offset, (UINT32) Data32));
      }

      if ((HsioPciePreMemConfig->Lane[Index].HsioTxGen1DeEmphEnable == TRUE) ||
          (HsioPciePreMemConfig->Lane[Index].HsioTxGen2DeEmph3p5Enable == TRUE)) {

        Data32Or  = 0;
        Data32And = 0xFFFFFFFF;
        if (HsioPciePreMemConfig->Lane[Index].HsioTxGen1DeEmphEnable == TRUE) {
          Data32Or |= (UINT32) (HsioPciePreMemConfig->Lane[Index].HsioTxGen1DeEmph << N_PCH_HSIO_TX_DWORD5_OW2TAPGEN1DEEMPH3P5_5_0);
          Data32And &= (UINT32) ~B_PCH_HSIO_TX_DWORD5_OW2TAPGEN1DEEMPH3P5_5_0;
        }

        if (HsioPciePreMemConfig->Lane[Index].HsioTxGen2DeEmph3p5Enable == TRUE) {
          Data32Or |= (UINT32) (HsioPciePreMemConfig->Lane[Index].HsioTxGen2DeEmph3p5 << N_PCH_HSIO_TX_DWORD5_OW2TAPGEN2DEEMPH3P5_5_0);
          Data32And &= (UINT32) ~B_PCH_HSIO_TX_DWORD5_OW2TAPGEN2DEEMPH3P5_5_0;
        }

        Offset = HsioLane.Base + (UINT16) R_PCH_HSIO_TX_DWORD5;
        PchPcrAndThenOr32 (
          (PCH_SBI_PID) PortId,
          (UINT16) Offset,
          Data32And,
          Data32Or);
        PchPcrRead32 ((PCH_SBI_PID) PortId, Offset, &Data32);
        DEBUG ((DEBUG_INFO, "HSIO : PortID = 0x%02x, Offset = 0x%04x, Value = 0x%08x\n", (PCH_SBI_PID) PortId, (UINT16) Offset, (UINT32) Data32));
      }

      if (HsioPciePreMemConfig->Lane[Index].HsioTxGen2DeEmph6p0Enable == TRUE) {
        Offset = HsioLane.Base + (UINT16) R_PCH_HSIO_TX_DWORD6;
        PchPcrAndThenOr32 (
          (PCH_SBI_PID) PortId,
          (UINT16) Offset,
          (UINT32) ~B_PCH_HSIO_TX_DWORD6_OW2TAPGEN2DEEMPH6P0_5_0,
          (UINT32) (HsioPciePreMemConfig->Lane[Index].HsioTxGen2DeEmph6p0 << N_PCH_HSIO_TX_DWORD6_OW2TAPGEN2DEEMPH6P0_5_0));
        PchPcrRead32 ((PCH_SBI_PID) PortId, Offset, &Data32);
        DEBUG ((DEBUG_INFO, "HSIO : PortID = 0x%02x, Offset = 0x%04x, Value = 0x%08x\n", (PCH_SBI_PID) PortId, (UINT16) Offset, (UINT32) Data32));
      }

      if ((HsioPciePreMemConfig->Lane[Index].HsioTxGen1DownscaleAmpEnable == TRUE) || (HsioPciePreMemConfig->Lane[Index].HsioTxGen1DeEmphEnable == TRUE)) {
        MmioAnd8 (RpBase + R_PCH_PCIE_LCTL, (UINT8) ~(B_PCIE_LCTL_LD));
      }
    }
  }
  //
  // According to PCIE spec, following Link Disable PCIE device may take up to 100ms to become operational.
  // Wait until all ports are operational again or until 100ms passed
  //
  TimeSpent = 0;
  while ((TimeSpent < 100) && (RpToRetrain != 0)) {
    for (Index = 0; Index < MaxPciePorts; Index++) {
      if ((RpToRetrain & (BIT0 << Index)) == 0) {
        continue;
      }
      RpBase = PchPcieBase (Index);
      if (MmioRead16 (RpBase + R_PCH_PCIE_LSTS) & B_PCIE_LSTS_LA) {
        RpToRetrain &= ~(BIT0 << Index);
      }
    }
    MicroSecondDelay (1000);
    TimeSpent++;
  }

}

VOID
PchHsioEnablePcieComplianceMode (
  VOID
  )
{
  UINT32     MaxPcieLanes;
  UINT32     PcieIndex;
  UINT8      HsioLaneNo;
  HSIO_LANE  HsioLane;

  MaxPcieLanes = GetPchMaxPciePortNum ();
  for (PcieIndex = 0; PcieIndex < MaxPcieLanes; ++PcieIndex) {
    if (PchGetPcieLaneNum (PcieIndex, &HsioLaneNo) == EFI_SUCCESS) {
      DEBUG ((DEBUG_INFO, "PCIe compliance mode for PCIe%d, HSIO%d\n", PcieIndex + 1, HsioLaneNo));
      HsioGetLane (HsioLaneNo, &HsioLane);
      HsioLaneAndThenOr32 (&HsioLane, R_PCH_HSIO_PCS_DWORD4, (UINT32) ~BIT23, 0);
    }
  }
}

/**
  This function programs DC wander bits if the DMI links are configured for AC coupling.

**/
VOID
PchProgDcWander (
  VOID
  )
{
  UINT32      Data32;
  UINT8       DmiLane;
  HSIO_LANE   HsioLane;
  UINT8       PortId;
  UINT16      Offset;

  DEBUG ((DEBUG_INFO, "PchProgDcWander() Start\n"));

  if (GetPchSeries () == PchH) {
    for (DmiLane = PCH_H_FIA_DMILANE_START; DmiLane <= PCH_H_FIA_DMILANE_END; DmiLane++) {
      HsioGetLane (DmiLane, &HsioLane);
      PortId = HsioLane.Pid;
      Offset = HsioLane.Base + (UINT16) R_PCH_HSIO_PCS_DWORD0;
      PchPcrRead32 (PortId, Offset, &Data32);
      DEBUG ((DEBUG_INFO, "DMI HSIO AC/DC coupling PCS_DWORD0: PortID = 0x%02x, Offset = 0x%04x, Value = 0x%08x\n", (PCH_SBI_PID) PortId, (UINT16) Offset, (UINT32) Data32));
      ///
      /// if DMI links are configured for "AC coupling" [bit 31] is set, then reset DC Wander bit "29" for DMI lanes 14 to 17 else set it 1
      ///
      Offset = HsioLane.Base + (UINT16) R_PCH_HSIO_RX_DWORD15;
      if (Data32 & BIT31) {
        PchPcrAndThenOr32 (PortId, Offset, (UINT32) ~BIT29, 0);
      } else {
        PchPcrAndThenOr32 (PortId, Offset, (UINT32) ~BIT29, BIT29);
      }
      PchPcrRead32 (PortId, Offset, &Data32);
      DEBUG ((DEBUG_INFO, "DMI HSIO AC/DC coupling RX_DWORD15: PortID = 0x%02x, Offset = 0x%04x, Value = 0x%08x\n", (PCH_SBI_PID) PortId, (UINT16) Offset, (UINT32) Data32));
    }
  }

  DEBUG ((DEBUG_INFO, "PchProgDcWander() End\n"));
}

/**
  This function programs L1 substate for PCIe and DMI links for a given steppings.

**/
VOID
PchHsioDmiPciLaneProg (
  VOID
  )
{
  UINT32      Data32;
  UINT32      PrevData32;
  HSIO_LANE   HsioLane;
  UINT8       PortId;
  UINT16      Offset;
  UINT8       LaneOwner;
  UINT8       LaneNum;
  UINT16      LpcDeviceId;

  DEBUG ((DEBUG_INFO, "PchHsioDmiPciLaneProg() Start\n"));
  LpcDeviceId       = GetLpcDid ();

  //
  // PCH PCIe* TX Pin State During L1.0 and L1.1 Substate
  //
  if ((LpcDeviceId == V_SKL_PCH_H_LPC_DEVICE_ID_MB_4)
      || (LpcDeviceId == V_SKL_PCH_H_LPC_DEVICE_ID_MB_5)
      || (LpcDeviceId == V_SKL_PCH_H_LPC_DEVICE_ID_MB_6)
      || (LpcDeviceId == V_SKL_PCH_H_LPC_DEVICE_ID_MB_8)
      || (LpcDeviceId == V_PCH_LP_LPC_DEVICE_ID_MB_8)
      || (LpcDeviceId == V_PCH_LP_LPC_DEVICE_ID_MB_9)
      || (LpcDeviceId == V_PCH_LP_LPC_DEVICE_ID_MB_10)
      || (GetPchGeneration () == KblPch))
  {
    for (LaneNum = 0; LaneNum <= PCH_FIA_MAX_LANES; LaneNum++) {
      if (!EFI_ERROR (PchGetLaneInfo (LaneNum, &PortId, &LaneOwner))) {
        if (LaneOwner == V_PCH_PCR_FIA_LANE_OWN_PCIEDMI) {
          HsioGetLane (LaneNum, &HsioLane);
          Offset = HsioLane.Base + (UINT16) R_PCH_HSIO_PCS_DWORD1;
          PchPcrRead32 (PortId, Offset, &PrevData32);
          PchPcrAndThenOr32 (PortId, Offset, (UINT32) ~(BIT15 | BIT14), (BIT15 | BIT14));
          PchPcrRead32 (PortId, Offset, &Data32);
          DEBUG ((DEBUG_INFO, "PchHsioDmiPciLaneProg: PCS_DWORD1: PortID = 0x%02x, Lane =0x%02d, Offset = 0x%04x, Value = 0x%08x", (PCH_SBI_PID) PortId, LaneNum, (UINT16) Offset, (UINT32) Data32));
          DEBUG ((DEBUG_INFO, " [Prev Value = 0x%08x]\n", (UINT32) PrevData32));
          Offset = HsioLane.Base + (UINT16) R_PCH_HSIO_TX_DWORD23;
          PchPcrRead32 (PortId, Offset, &PrevData32);
          PchPcrAndThenOr32 (PortId, Offset, (UINT32) ~(BIT25), (BIT25));
          PchPcrRead32 (PortId, Offset, &Data32);
          DEBUG ((DEBUG_INFO, "PchHsioDmiPciLaneProg: TX_DWORD23: PortID = 0x%02x, Lane =0x%02d, Offset = 0x%04x, Value = 0x%08x", (PCH_SBI_PID) PortId, LaneNum, (UINT16) Offset, (UINT32) Data32));
          DEBUG ((DEBUG_INFO, " [Prev Value = 0x%08x]\n", (UINT32) PrevData32));
        }
      }
    }
  }
  DEBUG ((DEBUG_INFO, "PchHsioDmiPciLaneProg() End\n"));
}

/**
  The function programs common HSIO registers.

  @retval EFI_SUCCESS                   The HSIO settings have been programmed correctly
**/
EFI_STATUS
PchHsioCommonProg (
  VOID
  )
{
  PCH_SBI_HSIO_TABLE_STRUCT   *PchHsioTable;
  UINT8                       PhyModeNum;
  PCH_SERIES                  PchSeries;
  UINT16                      HsioSize;
  UINT8                       Entry;
  UINT32                      Los1;
  UINT32                      Los2;
  UINT32                      Los3;
  UINT32                      Los4;
  UINT32                      Data32;

  PchHsioTable = NULL;
  PhyModeNum = 0;
  HsioSize = 0;
  Entry = 0;
  Los3 = 0;
  Los4 = 0;

  PchSeries = GetPchSeries ();

  ///
  /// Step 1
  /// Read the LOS Registers
  ///
  PchPcrRead32 (PID_FIA, R_PCH_PCR_FIA_LOS1_REG_BASE, &Los1);
  DEBUG ((DEBUG_INFO, "FIA LOS1 = %08x\n", Los1));
  PchPcrRead32 (PID_FIA, R_PCH_PCR_FIA_LOS2_REG_BASE, &Los2);
  DEBUG ((DEBUG_INFO, "FIA LOS2 = %08x\n", Los2));
  if (PchSeries == PchH) {
    PchPcrRead32 (PID_FIA, R_PCH_PCR_FIA_LOS3_REG_BASE, &Los3);
    DEBUG ((DEBUG_INFO, "FIA LOS3 = %08x\n", Los3));
    PchPcrRead32 (PID_FIA, R_PCH_PCR_FIA_LOS4_REG_BASE, &Los4);
    DEBUG ((DEBUG_INFO, "FIA LOS4 = %08x\n", Los4));
  }

  ///
  /// Step 2
  /// Assign the appropriate BIOS HSIO table
  ///
  if (GetPchGeneration () == SklPch) {
    switch (PchStepping ()) {
      case PchLpB0:
      case PchLpB1:
        PchHsioTable = PchLpHsio_Bx;
        HsioSize = (UINT16) (sizeof (PchLpHsio_Bx) / sizeof (PCH_SBI_HSIO_TABLE_STRUCT));
        break;
      case PchLpC0:
      case PchLpC1:
        PchHsioTable = PchLpHsio_Cx;
        HsioSize = (UINT16) (sizeof (PchLpHsio_Cx) / sizeof (PCH_SBI_HSIO_TABLE_STRUCT));
        break;
      case PchHB0:
      case PchHC0:
        PchHsioTable = PchHHsio_Bx;
        HsioSize = (UINT16) (sizeof (PchHHsio_Bx) / sizeof (PCH_SBI_HSIO_TABLE_STRUCT));
        break;
      case PchHD0:
      case PchHD1:
        PchHsioTable = PchHHsio_Dx;
        HsioSize = (UINT16) (sizeof (PchHHsio_Dx) / sizeof (PCH_SBI_HSIO_TABLE_STRUCT));
        break;
      default:
        PchHsioTable = NULL;
        HsioSize = 0;
        DEBUG ((DEBUG_ERROR, "Unsupported PCH Stepping\n"));
    }
  } else {
    switch (PchStepping ()) {
      case KblPchHA0:
        PchHsioTable = KblPchHHsio_Ax;
        HsioSize = (UINT16) (sizeof (KblPchHHsio_Ax) / sizeof (PCH_SBI_HSIO_TABLE_STRUCT));
        break;
      default:
        PchHsioTable = NULL;
        HsioSize = 0;
        DEBUG ((DEBUG_ERROR, "Unsupported PCH Stepping\n"));
    }
  }

  ///
  /// Step 3
  /// Iterate through the HSIO table
  ///
  for (Entry = 0; Entry < HsioSize; Entry++) {
    if (((PchHsioTable[Entry].Offset & B_PCH_HSIO_ACCESS_TYPE) == V_PCH_HSIO_ACCESS_TYPE_MULCAST) &&
        ((PchHsioTable[Entry].Offset & B_PCH_HSIO_LANE_GROUP_NO) != PCH_HSIO_LANE_GROUP_COMMON_LANE)) {
      if (PchLosPhyModeCheck ((PCH_SBI_PID) PchHsioTable[Entry].PortId, PchHsioTable[Entry].LanePhyMode, PchSeries, Los1, Los2, Los3, Los4) == EFI_SUCCESS) {
        ///
        /// Step 3a
        /// If the HSIO offset is targeted to all the phymode specific data lanes attached to the common lane (MULCAST)
        /// then program the values only if the PhyModes actually exist on the platform based on FIA LOS
        ///
        DEBUG ((DEBUG_INFO, "Programming HSIO MULCAST : PortID = %02x, Offset = %04x, Value = %08x, LanePhyMode = %02x\n", (PCH_SBI_PID) PchHsioTable[Entry].PortId, (UINT16) PchHsioTable[Entry].Offset, (UINT32) PchHsioTable[Entry].Value, PchHsioTable[Entry].LanePhyMode));
        PchPcrWrite32 ((PCH_SBI_PID) PchHsioTable[Entry].PortId, (UINT16) PchHsioTable[Entry].Offset, (UINT32) PchHsioTable[Entry].Value);
      } else {
        DEBUG ((DEBUG_INFO, "Skipping HSIO MULCAST : PortID = %02x, Offset = %04x, Value = %08x, LanePhyMode = %02x\n", (PCH_SBI_PID) PchHsioTable[Entry].PortId, (UINT16) PchHsioTable[Entry].Offset, (UINT32) PchHsioTable[Entry].Value, PchHsioTable[Entry].LanePhyMode));
      }
    } else {
      ///
      /// Step 3b
      /// If the HSIO offset is targeted to all the data lanes attached to the common lane (BDCAST)
      /// or the offset target is the common lane then program without any checks
      ///
      DEBUG ((DEBUG_INFO, "HSIO : PortID = %02x, Offset = %04x, Value = %08x\n", (PCH_SBI_PID) PchHsioTable[Entry].PortId, (UINT16) PchHsioTable[Entry].Offset, (UINT32) PchHsioTable[Entry].Value));
      PchPcrWrite32 ((PCH_SBI_PID) PchHsioTable[Entry].PortId, (UINT16) PchHsioTable[Entry].Offset, (UINT32) PchHsioTable[Entry].Value);
    }
  }

  //
  // Additional programming for PCIe lanes of mPhy3 on KBP-H only.
  //
  if (GetPchGeneration () == KblPch) {
    PchPcrRead32 (PID_MODPHY3, 0x0038, &Data32);
    ASSERT ((Data32 & ~0x1F) == 0);

    PchPcrWrite32 (PID_MODPHY3, 0x8238, 0x7A);
  }

  //
  // Program DC wander bits if the DMI links are configured for AC coupling
  //
  PchProgDcWander ();

  //
  // PCH PCIe* TX Pin State During L1.0 and L1.1 Substate
  //
  PchHsioDmiPciLaneProg ();

  return EFI_SUCCESS;
}

/**
  The function programs the Pcie Pll SSC registers.

  @param[in]  SiPreMemPolicyPpi  The SI PreMem Policy PPI instance
**/
VOID
PchPciePllSscProg (
  IN  SI_PREMEM_POLICY_PPI       *SiPreMemPolicyPpi
  )
{
  UINT8                       PciePllSsc;
  UINT32                      Data32;
  EFI_STATUS                  Status;
  PCH_HSIO_PCIE_PREMEM_CONFIG *HsioPciePreMemConfig;
  STATIC UINT8 PciePllSscTable[] = {
          0x0,  // 0%
          0x6,  // 0.1%
          0xD,  // 0.2%
          0x14, // 0.3%
          0x1A, // 0.4%
          0x21, // 0.5%
          0x28, // 0.6%
          0x2E, // 0.7%
          0x35, // 0.8%
          0x3C, // 0.9%
          0x42, // 1.0%
          0x49, // 1.1%
          0x50, // 1.2%
          0x56, // 1.3%
          0x5D, // 1.4%
          0x64, // 1.5%
          0x6A, // 1.6%
          0x71, // 1.7%
          0x78, // 1.8%
          0x7E, // 1.9%
          0x85  // 2.0%
          };

  Status = GetConfigBlock ((VOID *) SiPreMemPolicyPpi, &gHsioPciePreMemConfigGuid, (VOID *) &HsioPciePreMemConfig);
  ASSERT_EFI_ERROR (Status);


  if (HsioPciePreMemConfig->PciePllSsc == PCIE_PLL_SSC_AUTO) {
    return;
  }

  PciePllSsc = HsioPciePreMemConfig->PciePllSsc;
  if (PciePllSsc > MAX_PCIE_PLL_SSC_PERCENT) {
    PciePllSsc = MAX_PCIE_PLL_SSC_PERCENT;
  }

  ///
  /// Step 1:  Clear i_sscen_h to 0b
  ///
  PchPcrAndThenOr32 (
    PID_MODPHY1,
    R_PCH_HSIO_PLL_SSC_DWORD2,
    (UINT32) ~B_PCH_HSIO_PLL_SSC_DWORD2_SSCSEN,
    0
    );

  ///
  /// Step 2:  Write the desired Down Spread % bit values in i_sscstepsize_7_0
  ///
  PchPcrAndThenOr32 (
    PID_MODPHY1,
    R_PCH_HSIO_PLL_SSC_DWORD2,
    (UINT32) ~B_PCH_HSIO_PLL_SSC_DWORD2_SSCSTEPSIZE_7_0,
    (UINT32) (PciePllSscTable[PciePllSsc] << N_PCH_HSIO_PLL_SSC_DWORD2_SSCSTEPSIZE_7_0)
    );

  ///
  /// Step 3:  Set i_ssc_propagate_h to 1b in the LCPLL_CFG1 register
  ///
  PchPcrAndThenOr32 (
    PID_MODPHY1,
    R_PCH_HSIO_PLL_SSC_DWORD3,
    (UINT32) ~B_PCH_HSIO_PLL_SSC_DWORD3_SSC_PROPAGATE,
    (UINT32) B_PCH_HSIO_PLL_SSC_DWORD3_SSC_PROPAGATE
    );

  ///
  /// Step 4:  Set i_sscen_h to 1b
  ///
  PchPcrAndThenOr32 (
    PID_MODPHY1,
    R_PCH_HSIO_PLL_SSC_DWORD2,
    (UINT32) ~B_PCH_HSIO_PLL_SSC_DWORD2_SSCSEN,
    (UINT32) B_PCH_HSIO_PLL_SSC_DWORD2_SSCSEN
    );

  PchPcrRead32 (PID_MODPHY1, R_PCH_HSIO_PLL_SSC_DWORD2, &Data32);
  DEBUG ((DEBUG_INFO, "HSIO : PortID = 0x%02x, Offset = 0x%04x, PciePllSsc = 0x%08x\n", PID_MODPHY1, R_PCH_HSIO_PLL_SSC_DWORD2, (UINT32) Data32));
}

/**
  The function program HSIO registers.

  @param[in] SiPreMemPolicyPpi         The SI PREMEM Policy PPI instance

  @retval EFI_SUCCESS                   The HSIO settings have been programmed correctly
**/
VOID
PchHsioBiosProgPreMem (
  IN  SI_PREMEM_POLICY_PPI             *SiPreMemPolicyPpi
  )
{
  DEBUG ((DEBUG_INFO, "PchHsioBiosProgPreMem() Start\n"));
  PchHsioCommonProg ();
  PchHsioRxTxEqPolicyProg (SiPreMemPolicyPpi);
  PchPciePllSscProg (SiPreMemPolicyPpi);
  DEBUG ((DEBUG_INFO, "PchHsioBiosProgPreMem() End\n"));
}

/**
  The function program HSIO registers.

  @param[in] SiPolicyPpi               The SI Policy PPI instance

**/
VOID
PchHsioBiosProg (
  IN  SI_POLICY_PPI    *SiPolicyPpi
  )
{
  EFI_STATUS                            Status;
  PCH_PCIE_CONFIG                       *PcieRpConfig;
  DEBUG ((DEBUG_INFO, "PchHsioBiosProg() Start\n"));

  Status = GetConfigBlock ((VOID *) SiPolicyPpi, &gPcieRpConfigGuid, (VOID *) &PcieRpConfig);
  ASSERT_EFI_ERROR (Status);

  if (PcieRpConfig->ComplianceTestMode) {
    PchHsioEnablePcieComplianceMode ();
  }
  DEBUG ((DEBUG_INFO, "PchHsioBiosProg() End\n"));
}
