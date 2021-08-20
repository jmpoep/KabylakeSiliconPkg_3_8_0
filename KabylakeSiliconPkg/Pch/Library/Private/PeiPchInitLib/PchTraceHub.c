/** @file
  PCH TraceHub Initialization file

 @copyright
  INTEL CONFIDENTIAL
  Copyright 2013 - 2016 Intel Corporation.

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

#include "PchInitPei.h"
#include <Library/MtrrLib.h>
#include <CpuRegs.h>
#include <Library/PostCodeLib.h>

/**
  This function attempts to set allocated memory as UNCACHEABLE.

  @param[in] Address                Address of TraceHub MMIO.
  @param[in] Size                   Size of TraceHub MMIO.

  @retval EFI_SUCCESS               Memory has been successfuly set as uncacheable.
  @retval EFI_NOT_FOUND             The PPI descriptor is not found in the database.
  @retval EFI_LOAD_ERROR            No empty MTRRs to use.
  @retval EFI_INVALID_PARAMETER     The input parameter to SetCache is not valid.
**/
EFI_STATUS
PchTraceHubSetMemoryAsUncacheable (
  IN EFI_PHYSICAL_ADDRESS Address,
  IN UINT32               Size
  )
{
  UINT32 Status;

  Status = MtrrSetMemoryAttribute (Address , Size , CacheUncacheable);
  ASSERT_EFI_ERROR (Status);

  return Status;
}

/**
  This function performs TraceHub PCH initialization stage on end of PEI phase, when DRAM is available.

  @param[in] SiPreMemPolicy         The SI PreMem Policy PPI instance

  @retval EFI_SUCCESS               Memory has been successfuly set as uncachable.
  @retval EFI_OUT_OF_RESOURCES      Requested amount of memory could not be allocated.
  @retval EFI_NOT_FOUND             The Cache PPI descriptor is not found in the database.
  @retval EFI_LOAD_ERROR            No empty MTRRs to use.
  @retval EFI_INVALID_PARAMETER     The input parameter to SetCache is not valid.
**/
EFI_STATUS
PchTraceHubOnEndOfPei (
  IN  SI_PREMEM_POLICY_PPI         *SiPreMemPolicy
  )
{
  UINTN                           TraceHubBaseAddress;
  UINT32                          MemSize = 0;
  EFI_PHYSICAL_ADDRESS            MemRegBuff = 0;
  EFI_PHYSICAL_ADDRESS            MemReg0Buff = 0;
  EFI_PHYSICAL_ADDRESS            MemReg1Buff = 0;
  EFI_BOOT_MODE                   BootMode;
  EFI_STATUS                      Status;
  UINT32                          ScratchpadReg;
  PCH_TRACE_HUB_PREMEM_CONFIG     *TraceHubPreMemConfig;

  DEBUG ((DEBUG_INFO, "PchTraceHubOnEndOfPei() Start\n"));

  TraceHubBaseAddress = MmPciBase (
                          DEFAULT_PCI_BUS_NUMBER_PCH,
                          PCI_DEVICE_NUMBER_PCH_TRACE_HUB,
                          PCI_FUNCTION_NUMBER_PCH_TRACE_HUB
                          );
  if (MmioRead16 (TraceHubBaseAddress) == 0xFFFF) {
    DEBUG ((DEBUG_INFO, "PchTraceHubOnEndOfPei() TraceHub Device not present\n"));
    return EFI_SUCCESS;
  }

  ///
  /// Step 1. On S3 resume skip the rest
  ///
  Status = PeiServicesGetBootMode (&BootMode);
  if (BootMode == BOOT_ON_S3_RESUME) {
    return EFI_SUCCESS;
  }

  ///
  /// Step 2. In case MSE is 0, skip the rest - if MSE = 0 it means Trace Hub has not been initialized earlier
  ///

  if ((MmioRead32 (TraceHubBaseAddress + PCI_COMMAND_OFFSET) & EFI_PCI_COMMAND_MEMORY_SPACE) == 0) {
    return EFI_SUCCESS;
  }

  Status = GetConfigBlock ((VOID *) SiPreMemPolicy, &gTraceHubPreMemConfigGuid, (VOID *) &TraceHubPreMemConfig);
  ASSERT_EFI_ERROR (Status);

  ScratchpadReg = MmioRead32 (PCH_TRACE_HUB_MTB_BASE_ADDRESS + R_PCH_TRACE_HUB_CSR_MTB_SCRATCHPAD0);
  DEBUG ((DEBUG_INFO, "PchTraceHubOnEndOfPei() - R_PCH_TRACE_HUB_CSR_MTB_SCRATCHPAD0 = 0x%08x\n", ScratchpadReg));

  if ((ScratchpadReg & BIT24) || (TraceHubPreMemConfig->EnableMode != TraceHubModeDisabled)) {
    DEBUG ((DEBUG_INFO, "PchTraceHubOnEndOfPei()- Trace Hub configured to Host Debugger or SCRATCHPAD0_BIT24 set\n"));
  }

  ///
  /// Step 3. In case we come here after G3/S5/warm reset, the MemReg0 needs to be allocated according to PchPolicy settings
  ///
  if (((BootMode != BOOT_ON_S4_RESUME) && ((MmioRead32 (PCH_TRACE_HUB_MTB_BASE_ADDRESS + R_PCH_TRACE_HUB_MTB_MSC0CTL) & B_PCH_TRACE_HUB_MTB_MSCNEN) == 0))
      || ((BootMode == BOOT_ON_S4_RESUME) && (MmioRead32 (PCH_TRACE_HUB_MTB_BASE_ADDRESS + R_PCH_TRACE_HUB_MTB_MSC0SIZE)))) {
    MemSize = TraceHubPreMemConfig->MemReg0Size + TraceHubPreMemConfig->MemReg1Size;
    if (MemSize > 0) {
      if (TraceHubPreMemConfig->MemReg0Size > TraceHubPreMemConfig->MemReg1Size && TraceHubPreMemConfig->MemReg1Size > 0) {
        MemSize = 2 * TraceHubPreMemConfig->MemReg0Size;
      }
      if (TraceHubPreMemConfig->MemReg1Size > TraceHubPreMemConfig->MemReg0Size && TraceHubPreMemConfig->MemReg0Size > 0) {
        MemSize = 2 * TraceHubPreMemConfig->MemReg1Size;
      }
      MemRegBuff = (EFI_PHYSICAL_ADDRESS) (UINTN) AllocateAlignedReservedPages (EFI_SIZE_TO_PAGES (MemSize), MemSize);
      if (MemRegBuff == 0) {
        DEBUG ((DEBUG_INFO, "PchTraceHubOnEndOfPei() Memory allocation failed!\n"));
        //ASSERT (FALSE);
        return EFI_OUT_OF_RESOURCES;
      } else {
        Status = PchTraceHubSetMemoryAsUncacheable (MemRegBuff, MemSize);
        if (EFI_ERROR (Status)) {
          DEBUG ((DEBUG_INFO, "PchTraceHubOnEndOfPei() Setting memory UNCACHEABLE failed!\n"));
          ASSERT_EFI_ERROR (Status);
          return Status;
        }

        ///     Write the base address and buffer size for Memory Region 0 to the the MSC0BAR and MSC0SIZE registers.
        ///     Write the base address and buffer size for Memory Region 1 to the the MSC1BAR and MSC1SIZE registers.
        ///     Note that BAR and Size are shifted left 12 bits by the hardware to arrive at physical starting address and size.
        ///     BIOS, therefore, should shift-right by 12 bits before writing a value to these registers.
        ///     This also forces the starting address and size to be on 4kB boundaries.
        ///
        if (TraceHubPreMemConfig->MemReg0Size) {
          MemReg0Buff = MemRegBuff;
          PostCode (0xB4E);
          MmioWrite32 (PCH_TRACE_HUB_MTB_BASE_ADDRESS + R_PCH_TRACE_HUB_MTB_MSC0BAR, ((UINT32) (MemReg0Buff)) >> 12);
          DEBUG ((DEBUG_INFO, "PchTraceHubOnEndOfPei() MTB_MSC0BAR  = 0x%08x\n", MmioRead32 (PCH_TRACE_HUB_MTB_BASE_ADDRESS + R_PCH_TRACE_HUB_MTB_MSC0BAR)));

          MmioWrite32 (PCH_TRACE_HUB_MTB_BASE_ADDRESS + R_PCH_TRACE_HUB_MTB_MSC0SIZE, (UINT32) (TraceHubPreMemConfig->MemReg0Size >> 12));
          DEBUG ((DEBUG_INFO, "PchTraceHubOnEndOfPei() MTB_MSC0SIZE  = 0x%08x\n", MmioRead32 (PCH_TRACE_HUB_MTB_BASE_ADDRESS + R_PCH_TRACE_HUB_MTB_MSC0SIZE)));
        }

        if (TraceHubPreMemConfig->MemReg1Size) {
          MemReg1Buff = MemRegBuff + TraceHubPreMemConfig->MemReg0Size;
          PostCode (0xB4F);
          MmioWrite32 (PCH_TRACE_HUB_MTB_BASE_ADDRESS + R_PCH_TRACE_HUB_MTB_MSC1BAR, ((UINT32) (MemReg1Buff)) >> 12);
          DEBUG ((DEBUG_INFO, "PchTraceHubOnEndOfPei() MTB_MSC1BAR  = 0x%08x\n", MmioRead32 (PCH_TRACE_HUB_MTB_BASE_ADDRESS + R_PCH_TRACE_HUB_MTB_MSC1BAR)));

          MmioWrite32 (PCH_TRACE_HUB_MTB_BASE_ADDRESS + R_PCH_TRACE_HUB_MTB_MSC1SIZE, (UINT32) (TraceHubPreMemConfig->MemReg1Size >> 12));
          DEBUG ((DEBUG_INFO, "PchTraceHubOnEndOfPei() MTB_MSC1SIZE  = 0x%08x\n", MmioRead32 (PCH_TRACE_HUB_MTB_BASE_ADDRESS + R_PCH_TRACE_HUB_MTB_MSC1SIZE)));
        }
      }
    }
  }

  ///
  /// Hide TraceHub Device using PSF (Config Disable)
  ///
  DEBUG ((DEBUG_INFO, "PchTraceHubOnEndOfPei() TraceHub Config Disable\n"));
  PsfHideTraceHubDevice ();

  DEBUG ((DEBUG_INFO, "PchTraceHubOnEndOfPei() End\n"));
  return Status;
}

/**
  This function completes power gating management for TraceHub and ensures locking of HSWPGCR1 register.
**/
VOID
TraceHubManagePowerGateControl (
  VOID
  )
{
  UINTN                   TraceHubBaseAddress;
  UINT32                  PchPwrmBase;

  ///
  /// Check if Trace Hub Device is present
  ///
  TraceHubBaseAddress = MmPciBase (
                          DEFAULT_PCI_BUS_NUMBER_PCH,
                          PCI_DEVICE_NUMBER_PCH_TRACE_HUB,
                          PCI_FUNCTION_NUMBER_PCH_TRACE_HUB
                          );

  if (MmioRead16 (TraceHubBaseAddress) == 0xFFFF) {
    DEBUG ((DEBUG_INFO, "TraceHubManagePowerGateControl() TraceHub device is not present \n"));
    return;
  }

  PchPwrmBaseGet (&PchPwrmBase);

  // If MSE is 0, it hints that the TraceHub is to be disabled
  if ((MmioRead32 (TraceHubBaseAddress + PCI_COMMAND_OFFSET) & EFI_PCI_COMMAND_MEMORY_SPACE) == 0) {
    //
    // Program the MTB BAR and set MSE to allow MMIO access
    //
    MmioWrite32 (TraceHubBaseAddress + R_PCH_TRACE_HUB_CSR_MTB_LBAR, PCH_TRACE_HUB_MTB_BASE_ADDRESS);
    MmioWrite32 (TraceHubBaseAddress + R_PCH_TRACE_HUB_CSR_MTB_UBAR, 0);
    MmioOr8 (TraceHubBaseAddress + PCI_COMMAND_OFFSET, EFI_PCI_COMMAND_MEMORY_SPACE);

    //
    // Set CTC resync on Tracehub function disable flow to avoid SLP_S0 issues
    //
    MmioOr32 (PCH_TRACE_HUB_MTB_BASE_ADDRESS + R_PCH_TRACE_HUB_CSR_MTB_TSUCTRL, B_PCH_TRACE_HUB_CSR_MTB_TSUCTRL_CTCRESYNC);
    //
    // Clear MTB BAR and MSE
    //
    MmioWrite8 (TraceHubBaseAddress + PCI_COMMAND_OFFSET, 0);
    MmioWrite32 (TraceHubBaseAddress + R_PCH_TRACE_HUB_CSR_MTB_LBAR, 0);

    ///
    /// Disable TraceHub Device using PSF
    /// Hide TraceHub Device using PSF
    ///
    DEBUG ((DEBUG_INFO, "TraceHubManagePowerGateControl() Disable and hide Trace Hub device\n"));
    PsfDisableTraceHubDevice ();

    /// If DCI has been enabled, HSWPGCR1 register has already been locked in PchDciConfiguration()
    if ((MmioRead32 (PchPwrmBase + R_PCH_PWRM_HSWPGCR1) & B_PCH_PWRM_SW_PG_CTRL_LOCK) == 0) {
      ///
      /// Set HSWPGCR1 (PWRMBASE + 0x5D0) [0] and [31] to power gate TraceHub and lock the register
      ///
      PostCode (0xB50);
      DEBUG ((DEBUG_INFO, "TraceHubManagePowerGateControl() Power gating Trace Hub device\n"));
      MmioOr32 (PchPwrmBase + R_PCH_PWRM_HSWPGCR1, (UINT32) (B_PCH_PWRM_DFX_SW_PG_CTRL | B_PCH_PWRM_SW_PG_CTRL_LOCK));
    }

  } else {
    //
    // Set CTC resync to avoid SLP_S0 issues
    //
    MmioOr32 (PCH_TRACE_HUB_MTB_BASE_ADDRESS + R_PCH_TRACE_HUB_CSR_MTB_TSUCTRL, B_PCH_TRACE_HUB_CSR_MTB_TSUCTRL_CTCRESYNC);
    /// If DCI has been enabled, HSWPGCR1 register has already been locked in PchDciConfiguration()
    if ((MmioRead32 (PchPwrmBase + R_PCH_PWRM_HSWPGCR1) & (UINT32) B_PCH_PWRM_SW_PG_CTRL_LOCK) == 0) {
      // Clear HSWPGCR1 (PWRMBASE+0x5D0)[0] to disable Trace Hub power gating and lock the register
      PostCode (0xB51);
      DEBUG ((DEBUG_INFO, "TraceHubManagePowerGateControl() Locking HSWPGCR1\n"));
      MmioWrite32 (PchPwrmBase + R_PCH_PWRM_HSWPGCR1, (UINT32) B_PCH_PWRM_SW_PG_CTRL_LOCK);
    }
  }
}


