/** @file
  Pei/Dxe/Smm TraceHub Init Lib.

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
#include <Library/TraceHubInitLib.h>
#include <Library/DebugLib.h>
#include <Library/IoLib.h>
#include <Library/MmPciLib.h>
#include <Library/PchCycleDecodingLib.h>
#include <Library/PchPcrLib.h>
#include <Library/CpuPlatformLib.h>
#include <Library/PchPsfLib.h>
#include <Library/PchInfoLib.h>
#include <Library/PchSbiAccessLib.h>
/**
  Set TraceHub base address.
  This cycle decoding is allowed to set when DMIC.SRL is 0.
  Programming steps:
  1. Program TraceHub PCI Offset 0x70~0x77 to the 64-bit base address.
  2. Program PCR[PSF3] + TraceHub RS0 offset 0x000 and 0x004 to TraceHub 64-bit base address.
  3. Manually write 1 to MSEN, PCR[PSF3] + TraceHub RS0 offset 0x01C[1] to activate the shadow.

  @param[in] AddressHi                   High 32-bits for TraceHub base address.
  @param[in] AddressLo                   Low 32-bits for TraceHub base address.

  @retval EFI_SUCCESS                   Successfully completed.
  @retval EFI_UNSUPPORTED               DMIC.SRL is set.
**/
EFI_STATUS
EFIAPI
TraceHubBaseSet (
  UINT32                                AddressHi,
  UINT32                                AddressLo
  )
{
  UINTN                                 TraceHubBase;
  UINT32                                Dmic;

  //
  // check address valid
  //
  if ((AddressLo & 0x0003FFFF) != 0) {
    DEBUG ((DEBUG_ERROR, "TraceHubBaseSet Error. Invalid Address: %x.\n", AddressLo));
    ASSERT (FALSE);
    return EFI_INVALID_PARAMETER;
  }
  PchPcrRead32 (PID_DMI, R_PCH_PCR_DMI_DMIC, &Dmic);
  if ((Dmic & B_PCH_PCR_DMI_DMIC_SRL) != 0) {
    DEBUG ((DEBUG_ERROR, "TraceHubBaseSet Error. DMIC.SRL is set.\n"));
    ASSERT (FALSE);
    return EFI_UNSUPPORTED;
  }

  TraceHubBase = MmPciBase (
                   DEFAULT_PCI_BUS_NUMBER_PCH,
                   PCI_DEVICE_NUMBER_PCH_TRACE_HUB,
                   PCI_FUNCTION_NUMBER_PCH_TRACE_HUB
                   );
  if (MmioRead16 (TraceHubBase) == 0xFFFF) {
    ASSERT (FALSE);
    return EFI_UNSUPPORTED;
  }
  //
  // Program TraceHub PCI Offset 0x70~0x77 to base address.
  //
  MmioWrite32 (TraceHubBase + R_PCH_TRACE_HUB_FW_LBAR, AddressLo);
  MmioWrite32 (TraceHubBase + R_PCH_TRACE_HUB_FW_UBAR, AddressHi);
  //
  // Program TraceHub ACPI BASE in PSF to TraceHub base address.
  //
  PsfSetTraceHubAcpiDeviceBarValue (0, AddressLo);
  PsfSetTraceHubAcpiDeviceBarValue (1, AddressHi);

  //
  // Enable TraceHub ACPI MSE to activate the shadow.
  //
  PsfEnableTraceHubAcpiDeviceMemorySpace ();

  return EFI_SUCCESS;
}

/**
  Used to program xHCI DCI MMIO registers via SBI.

  @param[in] Offset          DbC offset
  @param[in] Data            Data

**/
STATIC
VOID
SbiDbcSet (
  UINT16                     Offset,
  UINT32                     Data
  )
{
  UINT8                      Response;

  PchSbiExecutionEx (
    PID_XHCI,
    Offset,
    MemoryWrite,
    FALSE,
    0xf,
    0x5,
    (PCI_DEVICE_NUMBER_PCH_XHCI << 3) + PCI_FUNCTION_NUMBER_PCH_XHCI,
    &Data,
    &Response
    );
  DEBUG ((DEBUG_INFO, "[0x%x] = 0x%08x\n", Offset, Data));

  if (Response != SBI_SUCCESSFUL) {
    DEBUG ((DEBUG_INFO, "Write [0x%x] Failed!" , Offset));
  }
}

/**
  For xHCI.DbC.Trace does not survive across Sx, that FW agent is responsible to resume tracing back or DbC3 would be suspended.
**/
STATIC
VOID
ConfigureXhciDbcTrace (
  VOID
  )
{
  UINTN                 TraceHubBaseAddress;
  UINT32                MtbBar;
  UINT32                MtbBarH;
  UINT32                Data32;

  Data32              = 0;
  TraceHubBaseAddress = MmPciBase (
                          DEFAULT_PCI_BUS_NUMBER_PCH,
                          PCI_DEVICE_NUMBER_PCH_TRACE_HUB,
                          PCI_FUNCTION_NUMBER_PCH_TRACE_HUB
                          );
  MtbBar = MmioRead32 (TraceHubBaseAddress + R_PCH_TRACE_HUB_CSR_MTB_LBAR) & B_PCH_TRACE_HUB_CSR_MTB_RBAL;
  //
  // Ensure MSE is set
  //
  if (!(MmioRead8 (TraceHubBaseAddress + PCI_COMMAND_OFFSET) & EFI_PCI_COMMAND_MEMORY_SPACE)) {
    MmioOr8 (TraceHubBaseAddress + PCI_COMMAND_OFFSET, EFI_PCI_COMMAND_MEMORY_SPACE);
  }
  //
  // Set DbC Trace in Payload and Status Base
  //
  SbiDbcSet (R_PCH_XHCI_DCI_DBC_TRACE_IN_PAYLOAD_BP_LOW, MtbBar + R_PCH_TRACE_HUB_MTB_80000);
  SbiDbcSet (R_PCH_XHCI_DCI_DBC_TRACE_IN_STATUS_BP_LOW, MtbBar + R_PCH_TRACE_HUB_MTB_DBCSTSCMD);

  MtbBarH = MmioRead32 (TraceHubBaseAddress + R_PCH_TRACE_HUB_CSR_MTB_UBAR);
  SbiDbcSet (R_PCH_XHCI_DCI_DBC_TRACE_IN_PAYLOAD_BP_HIGH, MtbBarH);
  SbiDbcSet (R_PCH_XHCI_DCI_DBC_TRACE_IN_STATUS_BP_HIGH, MtbBarH);
  //
  // Set DbC Trace in Payload and Status Qualifier
  //
  if (GetPchSeries () == PchLp) {
    Data32 = V_PCH_LP_XHCI_DCI_DBC_TRACE_QUALIFIERS;
  } else {
    Data32 = V_PCH_H_XHCI_DCI_DBC_TRACE_QUALIFIERS;
  }
  SbiDbcSet (R_PCH_XHCI_DCI_DBC_TRACE_IN_PAYLOAD_QUALIFIERS, Data32);
  SbiDbcSet (R_PCH_XHCI_DCI_DBC_TRACE_IN_STATUS_QUALIFIERS, Data32);
}

/**
  This function performs basic initialization for TraceHub
  This routine will consume address range 0xFE0C0000 - 0xFE3FFFFF for BARs usage.
  Although controller allows access to a 64bit address resource, PEI phase is a 32bit env,
  addresses greater than 4G is not allowed by CPU address space.
  So, the addresses must be limited to below 4G and UBARs should be set to 0.
  If this routine is called by platform code, it is expected EnableMode is passed in as PchTraceHubModeDisabled,
  relying on the Intel TH debugger to enable it through the "Scratchpad0 bit [24]".
  By this practice, it gives the validation team the capability to use single debug BIOS
  to validate the early trace functionality and code path that enable/disable Intel TH using BIOS policy.

  @param[in] EnableMode                 Trace Hub Enable Mode
**/
VOID
TraceHubInitialize (
  IN  UINT8                             EnableMode
  )
{
  UINTN                   TraceHubBaseAddress;
  UINT32                  PchPwrmBase;

  DEBUG ((DEBUG_INFO, "TraceHubInitialize() - Start\n"));

  PchPwrmBaseGet (&PchPwrmBase);
  ///
  /// Step 1. Disable power gating in case it was power gated in previous boot
  ///
  MmioWrite8 (PchPwrmBase + R_PCH_PWRM_HSWPGCR1, 0);
  MmioRead8 (PchPwrmBase + R_PCH_PWRM_HSWPGCR1);

  //
  // Check if Trace Hub Device is present
  //
  TraceHubBaseAddress = MmPciBase (
                          DEFAULT_PCI_BUS_NUMBER_PCH,
                          PCI_DEVICE_NUMBER_PCH_TRACE_HUB,
                          PCI_FUNCTION_NUMBER_PCH_TRACE_HUB
                          );

  if (MmioRead16 (TraceHubBaseAddress) == 0xFFFF) {
    DEBUG ((DEBUG_INFO, "TraceHubInitialize() - End. TraceHub device is not present \n"));
    return;
  }

  ///
  /// Step 2. Check MSE. Perform initialization only when it has not been set yet.
  ///
  if ((MmioRead32 (TraceHubBaseAddress + PCI_COMMAND_OFFSET) & EFI_PCI_COMMAND_MEMORY_SPACE) == EFI_PCI_COMMAND_MEMORY_SPACE) {
    DEBUG ((DEBUG_INFO, "TraceHubInitialize() - End. Early init done already \n"));
    DEBUG ((DEBUG_INFO, "TraceHubInitialize() - FW_LBAR  = 0x%08x\n", MmioRead32 (TraceHubBaseAddress + R_PCH_TRACE_HUB_FW_LBAR)));
    DEBUG ((DEBUG_INFO, "TraceHubInitialize() - MTB_LBAR = 0x%08x\n", MmioRead32 (TraceHubBaseAddress + R_PCH_TRACE_HUB_CSR_MTB_LBAR)));
    DEBUG ((DEBUG_INFO, "TraceHubInitialize() - SW_LBAR  = 0x%08x\n", MmioRead32 (TraceHubBaseAddress + R_PCH_TRACE_HUB_SW_LBAR)));
    if (MmioRead32 (PCH_TRACE_HUB_MTB_BASE_ADDRESS + R_PCH_TRACE_HUB_CSR_MTB_SCRATCHPAD0) & BIT24) {
      DEBUG ((DEBUG_INFO, "TraceHubInitialize() - Trace Hub enabled due to SCRPD0.24\n"));
    }
    return;
  }

  ///
  /// Step 3. Program the MTB Base Address Register fixed BAR and enable MSE
  ///
  // Set MTB_LBAR (PCI offset 0x10)
  DEBUG ((DEBUG_INFO, "TraceHubInitialize() - Setting MTB_BAR\n"));
  MmioWrite32 (TraceHubBaseAddress + R_PCH_TRACE_HUB_CSR_MTB_LBAR, PCH_TRACE_HUB_MTB_BASE_ADDRESS);

  //
  // Clear MTB_UBAR (PCI offset 0x14)
  //
  MmioWrite32 (TraceHubBaseAddress + R_PCH_TRACE_HUB_CSR_MTB_UBAR, 0);

  //
  // Enable TraceHub to claim memory accesses
  //
  MmioOr8 (TraceHubBaseAddress + PCI_COMMAND_OFFSET, EFI_PCI_COMMAND_MEMORY_SPACE);

  ///
  /// Step 4. Check if STT is disconnected and if user requested disabling of Trace Hub
  ///
  if (((MmioRead32 ((UINT32) (PCH_TRACE_HUB_MTB_BASE_ADDRESS + R_PCH_TRACE_HUB_CSR_MTB_SCRATCHPAD0)) & BIT24) == 0)
      && (EnableMode == TraceHubModeDisabled)) {
    ///
    /// Step 4.1 Clear MSE
    ///
    MmioWrite8 (TraceHubBaseAddress + PCI_COMMAND_OFFSET, 0);
    ///
    /// Step 4.2 Clear MTB_BAR
    ///
    //
    // Clear MTB_LBAR (PCI offset 0x10)
    //
    DEBUG ((DEBUG_INFO, "TraceHubInitialize() - Clearing MTB_BAR\n"));
    MmioWrite32 (TraceHubBaseAddress + R_PCH_TRACE_HUB_CSR_MTB_LBAR, 0);

    DEBUG ((DEBUG_INFO, "TraceHubInitialize() - End. STT disconnected and Trace Hub requested to be disable\n"));
    return;
  }
  //
  // Setup xHCI DbC for Trace Hub tracing
  //
  DEBUG ((DEBUG_INFO, "TraceHubInitialize() - Setup DbC3 Tracing\n"));
  ConfigureXhciDbcTrace ();

  //
  // Program GTH_FREQ to 357MHz
  //
  MmioWrite32 ((UINT32) (PCH_TRACE_HUB_MTB_BASE_ADDRESS + R_PCH_TRACE_HUB_MTB_GTH_FREQ), 0x15476340);

  ///
  /// Step. 5 Clear MSE
  ///
  MmioWrite8 (TraceHubBaseAddress + PCI_COMMAND_OFFSET, 0);

  ///
  /// Step 6. Program the SW Base Address Register with fixed BAR
  ///
  //
  // SW_LBAR (PCI offset 0x18)
  //
  DEBUG ((DEBUG_INFO, "TraceHubInitialize() - Setting SW_BAR\n"));
  MmioWrite32 (TraceHubBaseAddress + R_PCH_TRACE_HUB_SW_LBAR, PCH_TRACE_HUB_SW_BASE_ADDRESS);
  //
  // SW_UBAR (PCI offset 0x1C)
  //
  MmioWrite32 (TraceHubBaseAddress + R_PCH_TRACE_HUB_SW_UBAR, 0);

  ///
  /// Step 7. Program the FW BAR and Shadow PCI Device
  /// (PCI offset 0x70+0x74) - aka FTMR
  ///
  /// At this point, a shadow PCI device (0/20/4) within the backbone PSF needs to be programmed
  /// with the value of FW BAR, have its memory space enabled, and then hide the shadow device
  ///
  DEBUG ((DEBUG_INFO, "TraceHubInitialize() - Setting FW_BAR\n"));
  TraceHubBaseSet (0, (UINT32) PCH_TRACE_HUB_FW_BASE_ADDRESS);

  CpuWriteTraceHubAcpiBase ((UINT64) PCH_TRACE_HUB_FW_BASE_ADDRESS);

  ///
  /// Step 8. Enable MSE and BME
  ///
  DEBUG ((DEBUG_INFO, "TraceHubInitialize() - Enabling MSE and BME\n"));
  MmioOr8 (TraceHubBaseAddress + PCI_COMMAND_OFFSET, EFI_PCI_COMMAND_MEMORY_SPACE | EFI_PCI_COMMAND_BUS_MASTER);

  DEBUG ((DEBUG_INFO, "TraceHubInitialize () Assigned BARs:\n"));
  DEBUG ((DEBUG_INFO, "TraceHubInitialize () FW_LBAR  = 0x%08x\n", MmioRead32 (TraceHubBaseAddress + R_PCH_TRACE_HUB_FW_LBAR)));
  DEBUG ((DEBUG_INFO, "TraceHubInitialize () MTB_LBAR = 0x%08x\n", MmioRead32 (TraceHubBaseAddress + R_PCH_TRACE_HUB_CSR_MTB_LBAR)));
  DEBUG ((DEBUG_INFO, "TraceHubInitialize () SW_LBAR  = 0x%08x\n", MmioRead32 (TraceHubBaseAddress + R_PCH_TRACE_HUB_SW_LBAR)));

  ///
  /// Step 9. Set destination sources for BIOS debug messages
  ///
  MmioWrite32 ((UINT32) (PCH_TRACE_HUB_MTB_BASE_ADDRESS + R_PCH_TRACE_HUB_MTB_SWDEST_4), 0x88888888);

  DEBUG ((DEBUG_INFO, "TraceHubInitialize () - End\n"));
}


