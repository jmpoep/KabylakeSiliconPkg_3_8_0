/**@file
  ACPI DSDT table for SCS Controllers

 @copyright
  INTEL CONFIDENTIAL
  Copyright 2014 - 2019 Intel Corporation.

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

#include <PchReservedResources.h>
#include <Register/PchRegsScs.h>
#include <PcieRegs.h>

External (\XBAS)

If(LEqual(PCHV(), SPTL)) { // SCS available on PCH-LP only

Scope(\_SB.PCI0) {

  //
  // DLL restore work around function.
  // When our integrated SD controllers exits D3 it will loose
  // the auto tuning settings it got after driver executed auto tuning
  // flow. Since OS drivers do not typically rerun the auto tuning flow on
  // D3 exit this could lead to potential problems with SD operation. To avoid
  // this BIOS saves the auto tuning DLL value and writes it to DLL value register
  // that is used when no auto tuning flow has been executed. This should guarantee correct
  // controller operation even if auto tuning has not been executed.
  // This function assumes:
  // 1. OS driver only runs the tuning once in the platform runtime
  // 2. The auto tune value that was established back then is good enough to
  //   suffice for entire platform runtime. Changes due to time and temperature are assumed to be insignificant
  // 3. The result of the auto tuning is not 0. 0 is used to identify D3 entries where OS driver didn't execute
  //    the tuning and restore should be skipped.
  //
  // @param[in] Arg0  SD controller bus number
  // @param[in] Arg1  SD controller device number
  // @param[in] Arg2  SD controller function number
  // @param[in] Arg3  MMIO address to use during restore flow
  // @param[in] Arg4  Size of the MMIO space
  //
  Method (DLLR, 5, Serialized) {
    ADBG ("SD DLL restore flow")

    Name (TEMP, 0)

    Name (EMPB, 0)
    Store (\XBAS, EMPB)
    Or(EMPB, ShiftLeft(Arg0, 20), EMPB)
    Or(EMPB, ShiftLeft(Arg1, 15), EMPB)
    Or(EMPB, ShiftLeft(Arg2, 12), EMPB)

    //
    // This is just a regular PCI access to SD controller.
    // We have to use SystemMemory region since PCI region access
    // can be blocked by OSPM if PCI_Config is used
    //
    OperationRegion (EMPC, SystemMemory, EMPB, 0x100)
    Field (EMPC, DWordAcc, NoLock, Preserve) {
      Offset(PCI_COMMAND_OFFSET),
         , 1,
      MSE, 1,
      Offset(PCI_BASE_ADDRESSREG_OFFSET),
      BAR0, 64,
      Offset(R_PCH_SCS_DEV_PCS),
      PSTA,32
    }

    Name (OPST, 0)
    Store (PSTA, OPST) // Save power status to restore it later

    //
    // At this point controller can be in D3Hot state and we have to transition it to D0 first.
    // to be able to access it's MMIO
    //
    And(PSTA, 0xFFFFFFFC, PSTA)
    Store(PSTA, TEMP) // Read back is neccessary for D-state transition to take effect

    Name (OMSE, 0)
    Store (MSE, OMSE) // Save MSE value to restore it later
    //
    // We can't assume that OSPM left a valid memory address for SD controller when it transitions it to D3
    // for that reason we save whatever value is in BAR0 and use one of our reserved ranges to run the restore flow.
    //
    Store (0, MSE)

    Name (OBAR, 0)
    Store (BAR0, OBAR) // Save BAR value to restore it later

    Store (Arg3, BAR0)
    Store (BAR0, TEMP) // Readback required to catch new BAR
    Store (1, MSE)

    //
    // @NOTE: Even though DLL registers are supposed to be
    // accessible via PCR space on real silicon access to that space
    // is failing and we have to do access via MMIO
    //
    OperationRegion (EMMI, SystemMemory, Arg3, Arg4)
    Field (EMMI, DWordAcc, NoLock, Preserve) {
      Offset(R_PCH_SCS_DEV_MEM_RX_CMD_DATA_DLL_CNTL2),
      FDLL, 8,
      Offset(R_PCH_SCS_DEV_MEM_AUTO_TUNING),
      ADLL, 8
    }

    Name (FDLV, 0)
    Name (ADLV, 0)

    Store (FDLL, FDLV)
    Store (ADLL, ADLV)

    ADBG (Concatenate ("Fixed DLL value ", ToHexString(FDLV)))
    ADBG (Concatenate ("Auto DLL Value ", ToHexString(ADLV)))

    //
    // Assume that if auto tuning DLL value is 0 the auto tuning flow
    // has not been executed and DLL restore should be skipped.
    //
    If(LNotEqual (ADLV, 0)) {
      ADBG ("Auto tuning executed, restoring values")

      //
      // We have to multiply auto tuned value by 2 to
      // adjust the value to the encoding of the fixed DLL
      // register.
      //
      Multiply (ADLV, 2, ADLV)
      Store (ADLV, FDLL)
    }

    Store (0, MSE)
    Store (OBAR, BAR0)
    Store (OMSE, MSE)
    Store (OPST, PSTA)
    Store(PSTA, TEMP) // Read back is neccessary for D-state transition to take effect
  }

  //
  // SCS eMMC (PCI Mode)
  //
  Device(PEMC) {
    Name(_ADR, 0x001E0004)


    // Memory Region to access to the eMMC PCI Configuration Space
    OperationRegion(SCSR, PCI_Config, 0x00, 0x100)
    Field(SCSR, WordAcc, NoLock, Preserve) {
      Offset(R_PCH_SCS_DEV_PCS),         // 0x84, PMCSR - Power Management Control and Status
      PSTA,32,
      Offset(R_PCH_SCS_DEV_PG_CONFIG),   // 0xA2, Device PG config
          , 2,
      PGEN, 1         // [BIT2] PGE - PG Enable
    }

    Method(_PS0, 0, Serialized) {
      Store(0, PGEN) // Disable PG
      // Register address: 0xFD000000 SB offset | 0xC0<<16 PID_SCS | 0x0600 GPPRVRW1
      PCRA(PID_SCS, R_PCH_PCR_SCS_GPPRVRW1, 0x7FFFFFBA) // Clear bits 31, 6, 2, 0
      Sleep(2) // Wait 2ms
      // Register address: 0xFD000000 SB offset | 0xC0<<16 PID_SCS | 0x0600 GPPRVRW1
      PCRO(PID_SCS, R_PCH_PCR_SCS_GPPRVRW1, 0x80000045) // Set bits 31, 6, 2, 0

      And(PSTA, 0xFFFFFFFC, PSTA) // Set BIT[1:0] = 00b - Power State D0
      Store(PSTA, TEMP) // Read Back PMCSR
    }

    Method(_PS3, 0, Serialized) {

      //
      // @NOTE: Run this work around before enabling power gating.
      //
      DLLR (
        0,
        PCI_DEVICE_NUMBER_PCH_SCS_EMMC,
        PCI_FUNCTION_NUMBER_PCH_SCS_EMMC,
        PCH_EMMC_BASE_ADDRESS,
        PCH_EMMC_MMIO_SIZE
        )

      Store(1, PGEN) // Enable PG

      Or(PSTA, 0x3, PSTA) // Set BIT[1:0] = 11b - Power State D3
      Store(PSTA, TEMP) // Read Back PMCSR
    }

    // _DSM x86 Device Specific Method
    // Arg0: UUID Unique function identifier
    // Arg1: Integer Revision Level
    // Arg2: Integer Function Index (0 = Return Supported Functions)
    // Arg3: Package Parameters
    Method (_DSM, 4, Serialized, 0, UnknownObj, {BuffObj, IntObj, IntObj, PkgObj}) {
      If(PCIC(Arg0)) { return(PCID(Arg0,Arg1,Arg2,Arg3)) }

      ADBG(Concatenate("EMH4=",ToDecimalString(EMH4)))
      // Check the UUID
      If(LEqual(Arg0, ToUUID("f6c13ea5-65cd-461f-ab7a-29f7e8d5bd61"))) {
        // Check the revision
        If(LGreaterEqual(Arg1, Zero)) {
          //Switch statement based on the function index.
          Switch(ToInteger(Arg2)) {
            //
            // Function Index 0 the return value is a buffer containing
            // one bit for each function index, starting with zero.
            // Bit 0 - Indicates whether there is support for any functions other than function 0.
            // Bit 1 - Indicates support to clear power control register
            // Bit 2 - Indicates support to set power control register
            // Bit 3 - Indicates support to set 1.8V signalling
            // Bit 4 - Indicates support to set 3.3V signalling
            // Bit 5 - Indicates support for HS200 mode
            // Bit 6 - Indicates support for HS400 mode
            // Bit 9 - Indicates eMMC I/O Driver Strength
            //
            // On SPT, for eMMC we have to support functions for
            // HS200 and HS400 and I/O Driver Strength
            //
            Case(0) {
              //
              // The return value 0x261 (BIT6 set) for HS400 enabled and
              // 0x221 (BIT6 not set) when HS400 is disabled in Setup menu.
              //
              If(LEqual(EMH4, 1)) {
                Return(Buffer() {0x61, 0x02}) // HS400 support enabled
              }
              Return(Buffer() {0x21, 0x02})   // HS400 support disabled
            }

            //
            // Function index 5 - corresponds to HS200 mode
            // Return value from this function is used to program
            // the UHS Mode Select bits in Host Control 2.
            // 011b - corresponds to SDR104 and according to the
            // SD Host Controller Spec and this value is overloaded
            // to program the controller to select HS200 mode for eMMC.
            //
            Case(5) {
              Return(Buffer() {0x3})
            }

            //
            // Function index 6 - corresponds to HS400 mode
            // Return value from this function is used to program
            // the UHS Mode Select bits in Host Control 2.
            // 101b is a reserved value according to the SD Host
            // Controller Spec and we use this value for HS400 mode
            // selection.
            //
            Case(6) {
              Return(Buffer() {0x5})
            }

            //
            // Function index 9 - corresponds to I/O Driver Strength
            // Return value from this function represents the values
            // of the Driver Strength selection
            // (eMMC 5.01 Specification JESD84-B50.1, Table 186)
            // that shall be programmed by the Host Driver (OS)
            // as part of the Initialization flows.
            //
            Case(9) {
              Switch(EMDS) {
                Case(0x0) { Return(Buffer() {0x0}) } // 50 Ohm
                Case(0x1) { Return(Buffer() {0x1}) } // 33 Ohm
                Case(0x4) { Return(Buffer() {0x4}) } // 40 Ohm
              }
            }
          } // End - Switch(Arg2)
        }
      } // End - UUID check
      Return(Buffer() {0x0})
    } // End - _DSM

    Device (CARD) {
      Name (_ADR, 0x00000008)
      Method(_RMV, 0x0, NotSerialized) { Return (0) } // Device cannot be removed
    }
  } // Device(PEMC)

  //
  // SCS SD Card (PCI Mode)
  //
  Device(PSDC) {
    Name(_ADR, 0x001E0006)


    Name(_S0W, 3) // D3hot capable

    // Memory Region to access to the SDHC PCI Configuration Space
    OperationRegion(SCSR, PCI_Config, 0x00, 0x100)
    Field(SCSR, WordAcc, NoLock, Preserve) {
      Offset(R_PCH_SCS_DEV_PCS),         // 0x84, PMCSR - Power Management Control and Status
      PSTA,32,
      Offset(R_PCH_SCS_DEV_PG_CONFIG),   // 0xA2, Device PG config
          , 2,
      PGEN, 1         // [BIT2] PGE - PG Enable
    }

    Method(_PS0, 0, Serialized) {
      Store(0, PGEN) // Disable PG
      // Register address: 0xFD000000 SB offset | 0xC0<<16 PID_SCS | 0x0600 GPPRVRW1
      PCRA(PID_SCS, R_PCH_PCR_SCS_GPPRVRW1, 0xFFFFFE7A) // Clear bits 8, 7, 2, 0
      Sleep(2) // Wait 2ms
      // Register address: 0xFD000000 SB offset | 0xC0<<16 PID_SCS | 0x0600 GPPRVRW1
      PCRO(PID_SCS, R_PCH_PCR_SCS_GPPRVRW1, 0x00000185) // Set bits 8, 7, 2, 0

      And(PSTA, 0xFFFFFFFC, PSTA) // Set BIT[1:0] = 00b - Power State D0
      Store(PSTA, TEMP) // Read Back PMCSR
    }

    Method(_PS3, 0, Serialized) {
      Store(1, PGEN) // Enable PG

      Or(PSTA, 0x3, PSTA) // Set BIT[1:0] = 11b - Power State D3
      Store(PSTA, TEMP) // Read Back PMCSR
    }

    // _DSM x86 Device Specific Method
    // Arg0: UUID Unique function identifier
    // Arg1: Integer Revision Level
    // Arg2: Integer Function Index (0 = Return Supported Functions)
    // Arg3: Package Parameters
    Method (_DSM, 4, Serialized, 0, UnknownObj, {BuffObj, IntObj, IntObj, PkgObj}) {
      If(PCIC(Arg0)) { return(PCID(Arg0,Arg1,Arg2,Arg3)) }

      // Check the UUID
      If(LEqual(Arg0, ToUUID("f6c13ea5-65cd-461f-ab7a-29f7e8d5bd61"))) {
        // Check the revision
        If(LGreaterEqual(Arg1, Zero)) {
          // Switch statement based on the function index.
          Switch(ToInteger(Arg2)) {
            //
            // Function Index 0 the return value is a buffer containing
            // one bit for each function index, starting with zero.
            // Bit 0 - Indicates whether there is support for any functions other than function 0.
            // Bit 1 - Indicates support to clear power control register
            // Bit 2 - Indicates support to set power control register
            // Bit 3 - Indicates support to set 1.8V signalling
            // Bit 4 - Indicates support to set 3.3V signalling
            // Bit 5 - Indicates support for HS200 mode
            // Bit 6 - Indicates support for HS400 mode
            // Bit 9 - Indicates eMMC I/O Driver Strength
            //
            // On SPT, for SD we have to support functions to
            // set 1.8V signalling and 3.3V signalling
            //
            Case(0) {
              Return (Buffer() {0x19})
            }

            //
            // Function Index 3: Set 1.8v signalling.
            // We put a sleep of 100ms in this method to
            // work around a known issue with detecting
            // UHS SD card on SPT. This is to compensate
            // for the SD VR slowness.
            //
            Case(3) {
              Sleep (100) // Sleep 100ms
              Return(Buffer(){0x00})
            }

            //
            // Function Index 4: Set 3.3v signalling.
            // We put a sleep of 100ms in this method to
            // work around a known issue with detecting
            // UHS SD card on SPT. This is to compensate
            // for the SD VR slowness.
            //
            Case(4) {
              Sleep (100) // Sleep 100ms
              Return(Buffer(){0x00})
            }
          } // End - Switch(Arg2)
        }
      } // End - UUID check
      Return(Buffer() {0x0})
    } // End _DSM
  }
}

}// End If(LEqual(PCHV(), SPTL)) - PCH-LP only

