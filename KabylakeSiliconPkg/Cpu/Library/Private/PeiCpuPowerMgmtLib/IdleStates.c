/** @file
  This file contains power management C State configuration functions for
  processors.

  Acronyms:
  - PPM: Processor Power Management
  - TM:  Thermal Monitor
  - IST: Intel(R) Speedstep technology
  - HT:  Hyper-Threading Technology

 @copyright
  INTEL CONFIDENTIAL
  Copyright 2012 - 2019 Intel Corporation.

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

@par Specification
**/

#include "PowerMgmtCommon.h"

/**
  Initializes C States Power management features

  @param[in] PeiServices    Pointer to PEI Services Table
**/
VOID
InitCState (
  IN CONST EFI_PEI_SERVICES   **PeiServices
  )
{
  UINT16     mAcpiBaseAddr;

  PchAcpiBaseGet (&mAcpiBaseAddr);

  ///
  /// Initialize C states, some are general, some are processor specific.
  ///
  EnableCStates (PeiServices, mAcpiBaseAddr + PM_CST_LVL2);

  InitCstatePreWake ();
}

/**
  Disable/Enable the CState Pre-Wake Feature
**/
VOID
InitCstatePreWake (
  VOID
  )
{
  MSR_REGISTER TempMsr;

  TempMsr.Qword = AsmReadMsr64 (MSR_POWER_CTL);
  TempMsr.Dwords.Low &= ~(B_MSR_POWER_CTL_CSTATE_PRE_WAKE_DISABLE);
  if (gCpuPowerMgmtTestConfig->CStatePreWake == FALSE) {
    TempMsr.Dwords.Low |= B_MSR_POWER_CTL_CSTATE_PRE_WAKE_DISABLE;
  }
  AsmWriteMsr64 (MSR_POWER_CTL, TempMsr.Qword);

  return;
}

/**
  Enables C-State support as specified by the input flags on all logical
  processors and sets associated timing requirements in the chipset.

  @param[in] PeiServices    Pointer to PEI Services Table
  @param[in] C3IoAddress  IO address to generate C3 states (PM base + 014 usually)
**/
VOID
EnableCStates (
  IN CONST EFI_PEI_SERVICES   **PeiServices,
  IN UINT16                   C3IoAddress
  )
{
  MSR_REGISTER PowerCtl;
  MSR_REGISTER TempMsr;
  UINT32       LCR0Latency;
  UINT32       LCR1Latency;
  UINT32       LCR2Latency;
  UINT32       LCR3Latency;
  UINT32       LCR4Latency;
  UINT32       LCR5Latency;
  UINT16       EnableCStateParameters;
  CPU_FAMILY   mCpuFamilyId;

  mCpuFamilyId = gCpuGlobalNvsAreaConfig->Area->Cpuid & CPUID_FULL_FAMILY_MODEL;
  ///
  /// Load the C-State parameters to pass to the core function.
  ///
  EnableCStateParameters = C3IoAddress;
  ///
  /// Enable C-States on all logical processors.
  ///
  ApSafeEnableCStates(&EnableCStateParameters);
  gMpServicesPpi->StartupAllAPs (
                    PeiServices,
                    gMpServicesPpi,
                    (EFI_AP_PROCEDURE) ApSafeEnableCStates,
                    FALSE,
                    0,
                    (VOID *) &EnableCStateParameters
                    );
  ///
  /// If C-states are disabled or not supported, Disable C1e  and retrun
  ///
  if ((gCpuGlobalNvsAreaConfig->Area->PpmFlags & PPM_C_STATES) == 0) {
    PowerCtl.Qword = AsmReadMsr64 (MSR_POWER_CTL);
    PowerCtl.Dwords.Low &= ~B_MSR_POWER_CTL_C1E;
    AsmWriteMsr64 (MSR_POWER_CTL, PowerCtl.Qword);
    DEBUG (
      (DEBUG_INFO,
       "Setup C state disabled.Disable C1e. MSR(1FC) : %X %X\n",
       PowerCtl.Dwords.High,
       PowerCtl.Dwords.Low)
      );
    return;
  }
  ///
  /// Configure supported enhanced C-states
  ///
  /// Read Power Ctl MSR
  ///
  PowerCtl.Qword = AsmReadMsr64 (MSR_POWER_CTL);
  DEBUG ((DEBUG_INFO, "MSR(1FC) before configuring C1E: %X %X\n", PowerCtl.Dwords.High, PowerCtl.Dwords.Low));
  ///
  /// Enable supported states
  ///
  if (gCpuGlobalNvsAreaConfig->Area->PpmFlags & PPM_C1E) {
    PowerCtl.Dwords.Low |= B_MSR_POWER_CTL_C1E;
  } else {
    PowerCtl.Dwords.Low &= ~B_MSR_POWER_CTL_C1E;
  }
  ///
  /// Update Power Control MSR
  ///
  AsmWriteMsr64 (MSR_POWER_CTL, PowerCtl.Qword);
  DEBUG ((DEBUG_INFO, "MSR(1FC) after configuring C1E: %X %X\n", PowerCtl.Dwords.High, PowerCtl.Dwords.Low));
  ///
  /// Program Interrupt response time limits used by processor to decided when to get into
  /// package C3, C6 and C7
  ///
  DEBUG ((DEBUG_INFO, "Programming the 0xC3/C6/C7 (MSR 0x60A, 0x60B ,0X60C Latencies \n"));
  //
  // Package C3 Interrupt response time
  //
  TempMsr.Qword = AsmReadMsr64 (MSR_C_STATE_LATENCY_CONTROL_0);
  DEBUG ((DEBUG_INFO, "MSR(60A) before configuring Latency: %X %X\n", TempMsr.Dwords.High, TempMsr.Dwords.Low));
  TempMsr.Dwords.Low &= ~(B_INTERRUPT_RESPONSE_TIME_LIMIT_MASK | B_TIME_UNIT_MASK | B_PKG_IRTL_VALID);
  ///
  /// Program Interrupt Response Time Unit and Latency for MSR 0x60A
  ///
  TempMsr.Dwords.Low |= (UINT32) gCpuPowerMgmtTestConfig->CstateLatencyControl0Irtl;
  TempMsr.Dwords.Low |= LShiftU64 (gCpuPowerMgmtTestConfig->CstateLatencyControl0TimeUnit, N_TIME_UNIT_OFFSET);
  TempMsr.Dwords.Low |= B_PKG_IRTL_VALID;
  AsmWriteMsr64 (MSR_C_STATE_LATENCY_CONTROL_0, TempMsr.Qword);
  //
  // Package C6/C7 short Interrupt response time
  //
  TempMsr.Qword = AsmReadMsr64 (MSR_C_STATE_LATENCY_CONTROL_1);
  DEBUG ((DEBUG_INFO, "MSR(60B) before configuring Latency: %X %X\n", TempMsr.Dwords.High, TempMsr.Dwords.Low));
  TempMsr.Dwords.Low &= ~(B_INTERRUPT_RESPONSE_TIME_LIMIT_MASK | B_TIME_UNIT_MASK | B_PKG_IRTL_VALID);
  ///
  /// Program Interrupt Response Time Unit and Latency for MSR 0x60B
  ///
  TempMsr.Dwords.Low |= (UINT32) gCpuPowerMgmtTestConfig->CstateLatencyControl1Irtl;
  TempMsr.Dwords.Low |= LShiftU64 (gCpuPowerMgmtTestConfig->CstateLatencyControl1TimeUnit, N_TIME_UNIT_OFFSET);
  TempMsr.Dwords.Low |= B_PKG_IRTL_VALID;
  AsmWriteMsr64 (MSR_C_STATE_LATENCY_CONTROL_1, TempMsr.Qword);
  //
  // Package C6/C7 long Interrupt response time
  //
  TempMsr.Qword = AsmReadMsr64 (MSR_C_STATE_LATENCY_CONTROL_2);
  DEBUG ((DEBUG_INFO, "MSR(60C) before configuring Latency: %X %X\n", TempMsr.Dwords.High, TempMsr.Dwords.Low));
  TempMsr.Dwords.Low &= ~(B_INTERRUPT_RESPONSE_TIME_LIMIT_MASK | B_TIME_UNIT_MASK | B_PKG_IRTL_VALID);
  ///
  /// Program Interrupt Response Time Unit and Latency for MSR 0x60C
  ///
  TempMsr.Dwords.Low |= (UINT32) gCpuPowerMgmtTestConfig->CstateLatencyControl2Irtl;
  TempMsr.Dwords.Low |= LShiftU64 (gCpuPowerMgmtTestConfig->CstateLatencyControl2TimeUnit, N_TIME_UNIT_OFFSET);
  TempMsr.Dwords.Low |= B_PKG_IRTL_VALID;
  AsmWriteMsr64 (MSR_C_STATE_LATENCY_CONTROL_2, TempMsr.Qword);

  //
  // Package C8 Interrupt response time
  //
  TempMsr.Qword = AsmReadMsr64 (MSR_C_STATE_LATENCY_CONTROL_3);
  DEBUG ((DEBUG_INFO, "MSR(633) before configuring Latency: %X %X\n", TempMsr.Dwords.High, TempMsr.Dwords.Low));
  TempMsr.Dwords.Low &= ~(B_INTERRUPT_RESPONSE_TIME_LIMIT_MASK | B_TIME_UNIT_MASK | B_PKG_IRTL_VALID);
  ///
  /// Program Interrupt Response Time Unit and Latency for MSR 0x633
  ///
  TempMsr.Dwords.Low |= (UINT32) gCpuPowerMgmtTestConfig->CstateLatencyControl3Irtl;
  TempMsr.Dwords.Low |= LShiftU64 (gCpuPowerMgmtTestConfig->CstateLatencyControl3TimeUnit, N_TIME_UNIT_OFFSET);
  TempMsr.Dwords.Low |= B_PKG_IRTL_VALID;
  AsmWriteMsr64 (MSR_C_STATE_LATENCY_CONTROL_3, TempMsr.Qword);
  //
  // Package C9 Interrupt response time
  //
  TempMsr.Qword = AsmReadMsr64 (MSR_C_STATE_LATENCY_CONTROL_4);
  DEBUG ((DEBUG_INFO, "MSR(634) before configuring Latency: %X %X\n", TempMsr.Dwords.High, TempMsr.Dwords.Low));
  TempMsr.Dwords.Low &= ~(B_INTERRUPT_RESPONSE_TIME_LIMIT_MASK | B_TIME_UNIT_MASK | B_PKG_IRTL_VALID);
  ///
  /// Program Interrupt Response Time Unit and Latency for MSR 0x634
  ///
  TempMsr.Dwords.Low |= (UINT32) gCpuPowerMgmtTestConfig->CstateLatencyControl4Irtl;
  TempMsr.Dwords.Low |= LShiftU64 (gCpuPowerMgmtTestConfig->CstateLatencyControl4TimeUnit, N_TIME_UNIT_OFFSET);
  TempMsr.Dwords.Low |= B_PKG_IRTL_VALID;
  AsmWriteMsr64 (MSR_C_STATE_LATENCY_CONTROL_4, TempMsr.Qword);
  //
  // Package C10 Interrupt response time
  //
  TempMsr.Qword = AsmReadMsr64 (MSR_C_STATE_LATENCY_CONTROL_5);
  DEBUG ((DEBUG_INFO, "MSR(635) before configuring Latency: %X %X\n", TempMsr.Dwords.High, TempMsr.Dwords.Low));
  TempMsr.Dwords.Low &= ~(B_INTERRUPT_RESPONSE_TIME_LIMIT_MASK | B_TIME_UNIT_MASK | B_PKG_IRTL_VALID);
  ///
  /// Program Interrupt Response Time Unit and Latency for MSR 0x635
  ///
  TempMsr.Dwords.Low |= (UINT32) gCpuPowerMgmtTestConfig->CstateLatencyControl5Irtl;
  TempMsr.Dwords.Low |= LShiftU64 (gCpuPowerMgmtTestConfig->CstateLatencyControl5TimeUnit, N_TIME_UNIT_OFFSET);
  TempMsr.Dwords.Low |= B_PKG_IRTL_VALID;
  AsmWriteMsr64 (MSR_C_STATE_LATENCY_CONTROL_5, TempMsr.Qword);

  ///
  /// Update the PPM Global NVS Area
  ///
  LCR0Latency = (1 << (gCpuPowerMgmtTestConfig->CstateLatencyControl0TimeUnit * 5));
  LCR0Latency = (LCR0Latency * gCpuPowerMgmtTestConfig->CstateLatencyControl0Irtl) / 1000;
  //
  // _CST Latency: WordConst, so limit the latency value to max 0xFFFF
  //
  if (LCR0Latency > 0xFFFF) {
    LCR0Latency = 0xFFFF;
  }
  LCR1Latency = (1 << (gCpuPowerMgmtTestConfig->CstateLatencyControl1TimeUnit * 5));
  LCR1Latency = (LCR1Latency * gCpuPowerMgmtTestConfig->CstateLatencyControl1Irtl) / 1000;
  if (LCR1Latency > 0xFFFF) {
    LCR1Latency = 0xFFFF;
  }
  LCR2Latency = (1 << (gCpuPowerMgmtTestConfig->CstateLatencyControl2TimeUnit * 5));
  LCR2Latency = (LCR2Latency * gCpuPowerMgmtTestConfig->CstateLatencyControl2Irtl) / 1000;
  if (LCR2Latency > 0xFFFF) {
    LCR2Latency = 0xFFFF;
  }

  LCR3Latency = (1 << (gCpuPowerMgmtTestConfig->CstateLatencyControl3TimeUnit * 5));
  LCR3Latency = (LCR3Latency * gCpuPowerMgmtTestConfig->CstateLatencyControl3Irtl) / 1000;
  if (LCR3Latency > 0xFFFF) {
    LCR3Latency = 0xFFFF;
  }

  LCR4Latency = (1 << (gCpuPowerMgmtTestConfig->CstateLatencyControl4TimeUnit * 5));
  LCR4Latency = (LCR4Latency * gCpuPowerMgmtTestConfig->CstateLatencyControl4Irtl) / 1000;
  if (LCR4Latency > 0xFFFF) {
    LCR4Latency = 0xFFFF;
  }

  LCR5Latency = (1 << (gCpuPowerMgmtTestConfig->CstateLatencyControl5TimeUnit * 5));
  LCR5Latency = (LCR5Latency * gCpuPowerMgmtTestConfig->CstateLatencyControl5Irtl) / 1000;
  if (LCR5Latency > 0xFFFF) {
    LCR5Latency = 0xFFFF;
  }

  ///
  /// Update the PPM Global NVS Area.
  /// Update the PPM NVRAM values for C3
  ///
  gCpuGlobalNvsAreaConfig->Area->C3MwaitValue = 0x10;
  gCpuGlobalNvsAreaConfig->Area->C3Latency    = (UINT16) LCR0Latency;
  ///
  /// Update PPM NVRAM Values for C6
  ///
  if (gCpuGlobalNvsAreaConfig->Area->PpmFlags & C6_LONG_LATENCY_ENABLE) {
    gCpuGlobalNvsAreaConfig->Area->C6MwaitValue = 0x21;
    gCpuGlobalNvsAreaConfig->Area->C6Latency    = (UINT16) LCR2Latency;
  } else {
    gCpuGlobalNvsAreaConfig->Area->C6MwaitValue = 0x20;
    gCpuGlobalNvsAreaConfig->Area->C6Latency    = (UINT16) LCR1Latency;
  }
  ///
  /// Update PPM NVRAM Values for C7 - select the C-state supported among- C7 / C7S
  ///
  if (gCpuGlobalNvsAreaConfig->Area->PpmFlags & PPM_C7) { // Is C7 supported ?
    if (gCpuGlobalNvsAreaConfig->Area->PpmFlags & C7_LONG_LATENCY_ENABLE) {
      gCpuGlobalNvsAreaConfig->Area->C7MwaitValue = 0x31;
      gCpuGlobalNvsAreaConfig->Area->C7Latency    = (UINT16) LCR2Latency;
    } else {
      gCpuGlobalNvsAreaConfig->Area->C7MwaitValue = 0x30;
      gCpuGlobalNvsAreaConfig->Area->C7Latency    = (UINT16) LCR1Latency;
    }
  }
  if (gCpuGlobalNvsAreaConfig->Area->PpmFlags & PPM_C7S) { // Is C7S supported ?
    if (gCpuGlobalNvsAreaConfig->Area->PpmFlags & C7s_LONG_LATENCY_ENABLE) {
      gCpuGlobalNvsAreaConfig->Area->C7MwaitValue = 0x33;
      gCpuGlobalNvsAreaConfig->Area->C7Latency    = (UINT16) LCR2Latency;
    } else {
      gCpuGlobalNvsAreaConfig->Area->C7MwaitValue = 0x32;
      gCpuGlobalNvsAreaConfig->Area->C7Latency    = (UINT16) LCR1Latency;
    }
  }
  ///
  /// Update PPM NVRAM Values for CD - select the deepest C-state supported among- C8 / C9 / C10
  ///
  if (gCpuGlobalNvsAreaConfig->Area->PpmFlags & PPM_C10) { // C10 supported
    gCpuGlobalNvsAreaConfig->Area->CDIOLevel    = PCH_ACPI_LV7;
    gCpuGlobalNvsAreaConfig->Area->CDPowerValue = C10_POWER;
    gCpuGlobalNvsAreaConfig->Area->CDMwaitValue = 0x60;
    gCpuGlobalNvsAreaConfig->Area->CDLatency    = (UINT16) LCR5Latency;
  } else if (gCpuGlobalNvsAreaConfig->Area->PpmFlags & PPM_C9) { // C9 supported
    gCpuGlobalNvsAreaConfig->Area->CDIOLevel    = PCH_ACPI_LV6;
    gCpuGlobalNvsAreaConfig->Area->CDPowerValue = C9_POWER;
    gCpuGlobalNvsAreaConfig->Area->CDMwaitValue = 0x50;
    gCpuGlobalNvsAreaConfig->Area->CDLatency    = (UINT16) LCR4Latency;
  } else if (gCpuGlobalNvsAreaConfig->Area->PpmFlags & PPM_C8) { // C8 supported
    gCpuGlobalNvsAreaConfig->Area->CDIOLevel    = PCH_ACPI_LV5;
    gCpuGlobalNvsAreaConfig->Area->CDPowerValue = C8_POWER;
    gCpuGlobalNvsAreaConfig->Area->CDMwaitValue = 0x40;
    gCpuGlobalNvsAreaConfig->Area->CDLatency    = (UINT16) LCR3Latency;
  }

  return;
}

/**
  Enable C-State support as specified by the input flags on a logical processor.
    Configure BIOS C1 Coordination (SMI coordination)
    Enable IO redirection coordination
    Choose proper coordination method
    Configure extended C-States

  This function must be MP safe.

  @param[in out] Buffer    Pointer to a ENABLE_CSTATE_PARAMS containing the necessary
                           information to enable C-States

  @retval EFI_SUCCESS  Processor C-State support configured successfully.
**/
VOID
EFIAPI
ApSafeEnableCStates (
  IN OUT VOID *Buffer
  )
{
  MSR_REGISTER                                  Ia32MiscEnable;
  MSR_BROADWELL_PKG_CST_CONFIG_CONTROL_REGISTER PmCfgCtrlMsr;
  MSR_REGISTER                                  IoCaptAddr;
  UINT16                                        C3IoAddress;
  CPU_STEPPING                                  mCpuSteppingId;
  CPU_FAMILY                                    mCpuFamilyId;

  mCpuFamilyId   = gCpuGlobalNvsAreaConfig->Area->Cpuid & CPUID_FULL_FAMILY_MODEL;
  mCpuSteppingId = gCpuGlobalNvsAreaConfig->Area->Cpuid & CPUID_FULL_STEPPING;
  ///
  /// Extract parameters from the buffer
  ///
  C3IoAddress = *((UINT16 *) Buffer);
  ///
  /// If C-states are disabled in setup, disable C-states
  ///
  if (!(gCpuGlobalNvsAreaConfig->Area->PpmFlags & PPM_C_STATES)) {
    PmCfgCtrlMsr.Uint64 = AsmReadMsr64 (MSR_BROADWELL_PKG_CST_CONFIG_CONTROL);
    PmCfgCtrlMsr.Bits.Limit = 0;
    AsmWriteMsr64 (MSR_BROADWELL_PKG_CST_CONFIG_CONTROL, PmCfgCtrlMsr.Uint64);
    return;
  }
  ///
  /// Set C-state package limit to the highest C-state enabled
  ///
  PmCfgCtrlMsr.Uint64 = AsmReadMsr64 (MSR_BROADWELL_PKG_CST_CONFIG_CONTROL);
  if (gCpuPowerMgmtTestConfig->PkgCStateLimit != PkgCpuDefault) {
    PmCfgCtrlMsr.Bits.Limit = 0;

    if (gCpuPowerMgmtTestConfig->PkgCStateLimit < PkgCMax) {
      PmCfgCtrlMsr.Bits.Limit = gCpuPowerMgmtTestConfig->PkgCStateLimit;
    } else if ((gCpuGlobalNvsAreaConfig->Area->PpmFlags & PPM_C10) && (gCpuPowerMgmtTestConfig->PkgCStateLimit == PkgAuto)) {
      PmCfgCtrlMsr.Bits.Limit = V_CSTATE_LIMIT_C10;
    } else if ((gCpuGlobalNvsAreaConfig->Area->PpmFlags & PPM_C9) && (gCpuPowerMgmtTestConfig->PkgCStateLimit == PkgAuto)) {
      PmCfgCtrlMsr.Bits.Limit = V_CSTATE_LIMIT_C9;
    } else if ((gCpuGlobalNvsAreaConfig->Area->PpmFlags & PPM_C8) && (gCpuPowerMgmtTestConfig->PkgCStateLimit == PkgAuto)) {
      PmCfgCtrlMsr.Bits.Limit = V_CSTATE_LIMIT_C8;
    } else if ((gCpuGlobalNvsAreaConfig->Area->PpmFlags & PPM_C7S) && (gCpuPowerMgmtTestConfig->PkgCStateLimit == PkgAuto)) {
      PmCfgCtrlMsr.Bits.Limit = V_CSTATE_LIMIT_C7S;
    } else if ((gCpuGlobalNvsAreaConfig->Area->PpmFlags & PPM_C7) && (gCpuPowerMgmtTestConfig->PkgCStateLimit == PkgAuto)) {
      PmCfgCtrlMsr.Bits.Limit = V_CSTATE_LIMIT_C7;
    } else if (gCpuGlobalNvsAreaConfig->Area->PpmFlags & PPM_C6) {
      PmCfgCtrlMsr.Bits.Limit = V_CSTATE_LIMIT_C6;
    } else if (gCpuGlobalNvsAreaConfig->Area->PpmFlags & PPM_C3) {
      PmCfgCtrlMsr.Bits.Limit = V_CSTATE_LIMIT_C3;
    } else if (gCpuGlobalNvsAreaConfig->Area->PpmFlags & PPM_C1) {
      PmCfgCtrlMsr.Bits.Limit = V_CSTATE_LIMIT_C1;
    }
  }

  ///
  /// Configure C State IO redirection
  ///
  if (gCpuPowerMgmtTestConfig->CstCfgCtrIoMwaitRedirection) {
    PmCfgCtrlMsr.Bits.IO_MWAIT = 1;
  }

  //
  // Enable TimedMwait
  //
  if (gCpuGlobalNvsAreaConfig->Area->PpmFlags & PPM_TIMED_MWAIT) {
    PmCfgCtrlMsr.Uint32 |= B_TIMED_MWAIT_ENABLE;                   ///< @todo Use bitfield definition when available.
  }

  ///
  /// Configure C-state auto-demotion
  ///
  PmCfgCtrlMsr.Bits.C3AutoDemotion = 0;
  PmCfgCtrlMsr.Bits.C1AutoDemotion = 0;
  if (gCpuPowerMgmtTestConfig->C3AutoDemotion) {
    ///
    /// Enable C6/C7 Auto-demotion to C3
    ///
    PmCfgCtrlMsr.Bits.C3AutoDemotion = 1;
  }
  if (gCpuPowerMgmtTestConfig->C1AutoDemotion) {
    ///
    /// Enable C3/C6/C7 Auto-demotion to C1
    ///
    PmCfgCtrlMsr.Bits.C1AutoDemotion = 1;
  }
  ///
  /// Configure C-state un-demotion
  ///
  PmCfgCtrlMsr.Bits.C3Undemotion = 0;
  PmCfgCtrlMsr.Bits.C1Undemotion = 0;
  if (gCpuPowerMgmtTestConfig->C3UnDemotion) {
    ///
    /// Enable un-demotion from demoted C3
    ///
    PmCfgCtrlMsr.Bits.C3Undemotion = 1;
  }
  if (gCpuPowerMgmtTestConfig->C1UnDemotion) {
    ///
    /// Enable un-demotion from demoted C1
    ///
    PmCfgCtrlMsr.Bits.C1Undemotion = 1;
  }
  ///
  /// Configure Package C-state Demotion / un-demotion
  ///
  PmCfgCtrlMsr.Bits.CStateAutoDemotion = 0;
  PmCfgCtrlMsr.Bits.CStateUndemotion = 0;
  if (gCpuPowerMgmtTestConfig->PkgCStateDemotion) {
    ///
    /// Enable Package C-state Demotion
    ///
    PmCfgCtrlMsr.Bits.CStateAutoDemotion = 1;
  }
  if (gCpuPowerMgmtTestConfig->PkgCStateUnDemotion) {
    ///
    /// Enable Package C-state un-demotion
    ///
    PmCfgCtrlMsr.Bits.CStateUndemotion = 1;
  }
  AsmWriteMsr64 (MSR_BROADWELL_PKG_CST_CONFIG_CONTROL, PmCfgCtrlMsr.Uint64);
  ///
  /// Enable MONITOR/MWAIT support
  /// (already done on BSP, but must be done on all components.)
  ///
  Ia32MiscEnable.Qword = AsmReadMsr64 (MSR_IA32_MISC_ENABLE);
  Ia32MiscEnable.Qword |= B_MSR_IA32_MISC_ENABLE_MONITOR;
  AsmWriteMsr64 (MSR_IA32_MISC_ENABLE, Ia32MiscEnable.Qword);
  ///
  /// Configuration of I/O capture and I/O coordination SMI MSR.
  /// Configure the base port and range in the MSR to match LVL_X settings in ACPI tables
  /// Set I/O capture base port and range
  ///
  IoCaptAddr.Qword = AsmReadMsr64 (MSR_PMG_IO_CAPTURE_BASE);
  ///
  /// Mask off CST range and set the CST range
  ///
  IoCaptAddr.Dwords.Low &= ~B_MSR_PMG_CST_RANGE;
  if (gCpuGlobalNvsAreaConfig->Area->PpmFlags & PPM_C10) {
    IoCaptAddr.Dwords.Low |= V_IO_CAPT_LVL7;
  } else if (gCpuGlobalNvsAreaConfig->Area->PpmFlags & PPM_C9) {
    IoCaptAddr.Dwords.Low |= V_IO_CAPT_LVL6;
  } else if (gCpuGlobalNvsAreaConfig->Area->PpmFlags & PPM_C8) {
    IoCaptAddr.Dwords.Low |= V_IO_CAPT_LVL5;
  } else if (gCpuGlobalNvsAreaConfig->Area->PpmFlags & PPM_C7) {
    IoCaptAddr.Dwords.Low |= V_IO_CAPT_LVL4;
  } else if (gCpuGlobalNvsAreaConfig->Area->PpmFlags & PPM_C6) {
    IoCaptAddr.Dwords.Low |= V_IO_CAPT_LVL3;
  } else if (gCpuGlobalNvsAreaConfig->Area->PpmFlags & PPM_C3) {
    IoCaptAddr.Dwords.Low |= V_IO_CAPT_LVL2;
  }
  ///
  /// Set the base CST address
  ///
  IoCaptAddr.Dwords.Low &= ~(V_IO_CAPT_LVL2_BASE_ADDR_MASK);
  IoCaptAddr.Dwords.Low |= (UINT32) C3IoAddress;
  AsmWriteMsr64 (MSR_PMG_IO_CAPTURE_BASE, IoCaptAddr.Qword);
  return;
}

