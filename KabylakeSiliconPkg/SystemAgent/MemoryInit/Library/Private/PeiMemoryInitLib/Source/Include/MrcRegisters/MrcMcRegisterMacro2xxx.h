#ifndef __MrcMcRegisterMacro2xxx_h__
#define __MrcMcRegisterMacro2xxx_h__
/** @file
  This file was automatically generated. Modify at your own risk.
  Note that no error checking is done in these functions so ensure that the correct values are passed.

 @copyright
  INTEL CONFIDENTIAL
  Copyright 2010 - 2016 Intel Corporation.

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

#pragma pack(push, 1)


#define MrcHalSetRegDdrscramCrDdrscramblech0(MrcData, RegisterValue)   (MrcWriteCR (MrcData, DDRSCRAM_CR_DDRSCRAMBLECH0_REG, RegisterValue))
#define MrcHalGetRegDdrscramCrDdrscramblech0(MrcData)                  (MrcReadCR (MrcData, DDRSCRAM_CR_DDRSCRAMBLECH0_REG))
  #define MrcHalSetBfDdrscramCrDdrscramblech0Scramen(BitFieldValue, RegisterValue) (MrcHalSetBitField32 (DDRSCRAM_CR_DDRSCRAMBLECH0_ScramEn_HSH, BitFieldValue, RegisterValue))
  #define MrcHalGetBfDdrscramCrDdrscramblech0Scramen(RegisterValue)    (MrcHalGetBitField32 (DDRSCRAM_CR_DDRSCRAMBLECH0_ScramEn_HSH, RegisterValue))
  #define MrcHalSetBfDdrscramCrDdrscramblech0Scramkey(BitFieldValue, RegisterValue) (MrcHalSetBitField32 (DDRSCRAM_CR_DDRSCRAMBLECH0_ScramKey_HSH, BitFieldValue, RegisterValue))
  #define MrcHalGetBfDdrscramCrDdrscramblech0Scramkey(RegisterValue)   (MrcHalGetBitField32 (DDRSCRAM_CR_DDRSCRAMBLECH0_ScramKey_HSH, RegisterValue))
  #define MrcHalSetBfDdrscramCrDdrscramblech0Clockgateab(BitFieldValue, RegisterValue) (MrcHalSetBitField32 (DDRSCRAM_CR_DDRSCRAMBLECH0_ClockGateAB_HSH, BitFieldValue, RegisterValue))
  #define MrcHalGetBfDdrscramCrDdrscramblech0Clockgateab(RegisterValue) (MrcHalGetBitField32 (DDRSCRAM_CR_DDRSCRAMBLECH0_ClockGateAB_HSH, RegisterValue))
  #define MrcHalSetBfDdrscramCrDdrscramblech0Clockgatec(BitFieldValue, RegisterValue) (MrcHalSetBitField32 (DDRSCRAM_CR_DDRSCRAMBLECH0_ClockGateC_HSH, BitFieldValue, RegisterValue))
  #define MrcHalGetBfDdrscramCrDdrscramblech0Clockgatec(RegisterValue) (MrcHalGetBitField32 (DDRSCRAM_CR_DDRSCRAMBLECH0_ClockGateC_HSH, RegisterValue))
  #define MrcHalSetBfDdrscramCrDdrscramblech0Enabledbiab(BitFieldValue, RegisterValue) (MrcHalSetBitField32 (DDRSCRAM_CR_DDRSCRAMBLECH0_EnableDbiAB_HSH, BitFieldValue, RegisterValue))
  #define MrcHalGetBfDdrscramCrDdrscramblech0Enabledbiab(RegisterValue) (MrcHalGetBitField32 (DDRSCRAM_CR_DDRSCRAMBLECH0_EnableDbiAB_HSH, RegisterValue))
  #define MrcHalSetBfDdrscramCrDdrscramblech0Spare(BitFieldValue, RegisterValue) (MrcHalSetBitField32 (DDRSCRAM_CR_DDRSCRAMBLECH0_Spare_HSH, BitFieldValue, RegisterValue))
  #define MrcHalGetBfDdrscramCrDdrscramblech0Spare(RegisterValue)      (MrcHalGetBitField32 (DDRSCRAM_CR_DDRSCRAMBLECH0_Spare_HSH, RegisterValue))

#define MrcHalSetRegDdrscramCrDdrscramblech1(MrcData, RegisterValue)   (MrcWriteCR (MrcData, DDRSCRAM_CR_DDRSCRAMBLECH1_REG, RegisterValue))
#define MrcHalGetRegDdrscramCrDdrscramblech1(MrcData)                  (MrcReadCR (MrcData, DDRSCRAM_CR_DDRSCRAMBLECH1_REG))
  #define MrcHalSetBfDdrscramCrDdrscramblech1Scramen(BitFieldValue, RegisterValue) (MrcHalSetBitField32 (DDRSCRAM_CR_DDRSCRAMBLECH1_ScramEn_HSH, BitFieldValue, RegisterValue))
  #define MrcHalGetBfDdrscramCrDdrscramblech1Scramen(RegisterValue)    (MrcHalGetBitField32 (DDRSCRAM_CR_DDRSCRAMBLECH1_ScramEn_HSH, RegisterValue))
  #define MrcHalSetBfDdrscramCrDdrscramblech1Scramkey(BitFieldValue, RegisterValue) (MrcHalSetBitField32 (DDRSCRAM_CR_DDRSCRAMBLECH1_ScramKey_HSH, BitFieldValue, RegisterValue))
  #define MrcHalGetBfDdrscramCrDdrscramblech1Scramkey(RegisterValue)   (MrcHalGetBitField32 (DDRSCRAM_CR_DDRSCRAMBLECH1_ScramKey_HSH, RegisterValue))
  #define MrcHalSetBfDdrscramCrDdrscramblech1Clockgateab(BitFieldValue, RegisterValue) (MrcHalSetBitField32 (DDRSCRAM_CR_DDRSCRAMBLECH1_ClockGateAB_HSH, BitFieldValue, RegisterValue))
  #define MrcHalGetBfDdrscramCrDdrscramblech1Clockgateab(RegisterValue) (MrcHalGetBitField32 (DDRSCRAM_CR_DDRSCRAMBLECH1_ClockGateAB_HSH, RegisterValue))
  #define MrcHalSetBfDdrscramCrDdrscramblech1Clockgatec(BitFieldValue, RegisterValue) (MrcHalSetBitField32 (DDRSCRAM_CR_DDRSCRAMBLECH1_ClockGateC_HSH, BitFieldValue, RegisterValue))
  #define MrcHalGetBfDdrscramCrDdrscramblech1Clockgatec(RegisterValue) (MrcHalGetBitField32 (DDRSCRAM_CR_DDRSCRAMBLECH1_ClockGateC_HSH, RegisterValue))
  #define MrcHalSetBfDdrscramCrDdrscramblech1Enabledbiab(BitFieldValue, RegisterValue) (MrcHalSetBitField32 (DDRSCRAM_CR_DDRSCRAMBLECH1_EnableDbiAB_HSH, BitFieldValue, RegisterValue))
  #define MrcHalGetBfDdrscramCrDdrscramblech1Enabledbiab(RegisterValue) (MrcHalGetBitField32 (DDRSCRAM_CR_DDRSCRAMBLECH1_EnableDbiAB_HSH, RegisterValue))
  #define MrcHalSetBfDdrscramCrDdrscramblech1Spare(BitFieldValue, RegisterValue) (MrcHalSetBitField32 (DDRSCRAM_CR_DDRSCRAMBLECH1_Spare_HSH, BitFieldValue, RegisterValue))
  #define MrcHalGetBfDdrscramCrDdrscramblech1Spare(RegisterValue)      (MrcHalGetBitField32 (DDRSCRAM_CR_DDRSCRAMBLECH1_Spare_HSH, RegisterValue))

#define MrcHalSetRegDdrscramCrDdrmisccontrol0(MrcData, RegisterValue)  (MrcWriteCR (MrcData, DDRSCRAM_CR_DDRMISCCONTROL0_REG, RegisterValue))
#define MrcHalGetRegDdrscramCrDdrmisccontrol0(MrcData)                 (MrcReadCR (MrcData, DDRSCRAM_CR_DDRMISCCONTROL0_REG))
  #define MrcHalSetBfDdrscramCrDdrmisccontrol0WlWakecycles(BitFieldValue, RegisterValue) (MrcHalSetBitField32 (DDRSCRAM_CR_DDRMISCCONTROL0_WL_WakeCycles_HSH, BitFieldValue, RegisterValue))
  #define MrcHalGetBfDdrscramCrDdrmisccontrol0WlWakecycles(RegisterValue) (MrcHalGetBitField32 (DDRSCRAM_CR_DDRMISCCONTROL0_WL_WakeCycles_HSH, RegisterValue))
  #define MrcHalSetBfDdrscramCrDdrmisccontrol0WlSleepcycles(BitFieldValue, RegisterValue) (MrcHalSetBitField32 (DDRSCRAM_CR_DDRMISCCONTROL0_WL_SleepCycles_HSH, BitFieldValue, RegisterValue))
  #define MrcHalGetBfDdrscramCrDdrmisccontrol0WlSleepcycles(RegisterValue) (MrcHalGetBitField32 (DDRSCRAM_CR_DDRMISCCONTROL0_WL_SleepCycles_HSH, RegisterValue))
  #define MrcHalSetBfDdrscramCrDdrmisccontrol0Forcecompupdate(BitFieldValue, RegisterValue) (MrcHalSetBitField32 (DDRSCRAM_CR_DDRMISCCONTROL0_ForceCompUpdate_HSH, BitFieldValue, RegisterValue))
  #define MrcHalGetBfDdrscramCrDdrmisccontrol0Forcecompupdate(RegisterValue) (MrcHalGetBitField32 (DDRSCRAM_CR_DDRMISCCONTROL0_ForceCompUpdate_HSH, RegisterValue))
  #define MrcHalSetBfDdrscramCrDdrmisccontrol0WeaklockLatency(BitFieldValue, RegisterValue) (MrcHalSetBitField32 (DDRSCRAM_CR_DDRMISCCONTROL0_WeakLock_Latency_HSH, BitFieldValue, RegisterValue))
  #define MrcHalGetBfDdrscramCrDdrmisccontrol0WeaklockLatency(RegisterValue) (MrcHalGetBitField32 (DDRSCRAM_CR_DDRMISCCONTROL0_WeakLock_Latency_HSH, RegisterValue))
  #define MrcHalSetBfDdrscramCrDdrmisccontrol0Ddrnochinterleave(BitFieldValue, RegisterValue) (MrcHalSetBitField32 (DDRSCRAM_CR_DDRMISCCONTROL0_DdrNoChInterleave_HSH, BitFieldValue, RegisterValue))
  #define MrcHalGetBfDdrscramCrDdrmisccontrol0Ddrnochinterleave(RegisterValue) (MrcHalGetBitField32 (DDRSCRAM_CR_DDRMISCCONTROL0_DdrNoChInterleave_HSH, RegisterValue))
  #define MrcHalSetBfDdrscramCrDdrmisccontrol0LpddrMode(BitFieldValue, RegisterValue) (MrcHalSetBitField32 (DDRSCRAM_CR_DDRMISCCONTROL0_LPDDR_Mode_HSH, BitFieldValue, RegisterValue))
  #define MrcHalGetBfDdrscramCrDdrmisccontrol0LpddrMode(RegisterValue) (MrcHalGetBitField32 (DDRSCRAM_CR_DDRMISCCONTROL0_LPDDR_Mode_HSH, RegisterValue))
  #define MrcHalSetBfDdrscramCrDdrmisccontrol0Ckemappingch0(BitFieldValue, RegisterValue) (MrcHalSetBitField32 (DDRSCRAM_CR_DDRMISCCONTROL0_CKEMappingCh0_HSH, BitFieldValue, RegisterValue))
  #define MrcHalGetBfDdrscramCrDdrmisccontrol0Ckemappingch0(RegisterValue) (MrcHalGetBitField32 (DDRSCRAM_CR_DDRMISCCONTROL0_CKEMappingCh0_HSH, RegisterValue))
  #define MrcHalSetBfDdrscramCrDdrmisccontrol0Ckemappingch1(BitFieldValue, RegisterValue) (MrcHalSetBitField32 (DDRSCRAM_CR_DDRMISCCONTROL0_CKEMappingCh1_HSH, BitFieldValue, RegisterValue))
  #define MrcHalGetBfDdrscramCrDdrmisccontrol0Ckemappingch1(RegisterValue) (MrcHalGetBitField32 (DDRSCRAM_CR_DDRMISCCONTROL0_CKEMappingCh1_HSH, RegisterValue))
  #define MrcHalSetBfDdrscramCrDdrmisccontrol0Ddr4Mode(BitFieldValue, RegisterValue) (MrcHalSetBitField32 (DDRSCRAM_CR_DDRMISCCONTROL0_Ddr4_Mode_HSH, BitFieldValue, RegisterValue))
  #define MrcHalGetBfDdrscramCrDdrmisccontrol0Ddr4Mode(RegisterValue)  (MrcHalGetBitField32 (DDRSCRAM_CR_DDRMISCCONTROL0_Ddr4_Mode_HSH, RegisterValue))
  #define MrcHalSetBfDdrscramCrDdrmisccontrol0Clkgatedisable(BitFieldValue, RegisterValue) (MrcHalSetBitField32 (DDRSCRAM_CR_DDRMISCCONTROL0_ClkGateDisable_HSH, BitFieldValue, RegisterValue))
  #define MrcHalGetBfDdrscramCrDdrmisccontrol0Clkgatedisable(RegisterValue) (MrcHalGetBitField32 (DDRSCRAM_CR_DDRMISCCONTROL0_ClkGateDisable_HSH, RegisterValue))
  #define MrcHalSetBfDdrscramCrDdrmisccontrol0Dlldataweaklcken(BitFieldValue, RegisterValue) (MrcHalSetBitField32 (DDRSCRAM_CR_DDRMISCCONTROL0_DllDataWeakLckEn_HSH, BitFieldValue, RegisterValue))
  #define MrcHalGetBfDdrscramCrDdrmisccontrol0Dlldataweaklcken(RegisterValue) (MrcHalGetBitField32 (DDRSCRAM_CR_DDRMISCCONTROL0_DllDataWeakLckEn_HSH, RegisterValue))
  #define MrcHalSetBfDdrscramCrDdrmisccontrol0Dataclkgatedisatidle(BitFieldValue, RegisterValue) (MrcHalSetBitField32 (DDRSCRAM_CR_DDRMISCCONTROL0_DataClkGateDisAtIdle_HSH, BitFieldValue, RegisterValue))
  #define MrcHalGetBfDdrscramCrDdrmisccontrol0Dataclkgatedisatidle(RegisterValue) (MrcHalGetBitField32 (DDRSCRAM_CR_DDRMISCCONTROL0_DataClkGateDisAtIdle_HSH, RegisterValue))
  #define MrcHalSetBfDdrscramCrDdrmisccontrol0Spare(BitFieldValue, RegisterValue) (MrcHalSetBitField32 (DDRSCRAM_CR_DDRMISCCONTROL0_Spare_HSH, BitFieldValue, RegisterValue))
  #define MrcHalGetBfDdrscramCrDdrmisccontrol0Spare(RegisterValue)     (MrcHalGetBitField32 (DDRSCRAM_CR_DDRMISCCONTROL0_Spare_HSH, RegisterValue))
#pragma pack(pop)
#endif
