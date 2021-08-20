/** @file
  Intel Processor SSDT ACPI Code.

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

#include "CpuPowerMgmt.h"

DefinitionBlock (
  "CPUSSDT.aml",
  "SSDT",
  0x02,
  "CpuRef",
  "CpuSsdt",
  0x3000
  )
{
  External(\_SB.OSCP, IntObj)
  External(\_PR.PR00, DeviceObj)
  External(\_PR.PR01, DeviceObj)
  External(\_PR.PR02, DeviceObj)
  External(\_PR.PR03, DeviceObj)
  External(\_PR.PR04, DeviceObj)
  External(\_PR.PR05, DeviceObj)
  External(\_PR.PR06, DeviceObj)
  External(\_PR.PR07, DeviceObj)
  External(\_PR.PR08, DeviceObj)
  External(\_PR.PR09, DeviceObj)
  External(\_PR.PR10, DeviceObj)
  External(\_PR.PR11, DeviceObj)
  External(\_PR.PR12, DeviceObj)
  External(\_PR.PR13, DeviceObj)
  External(\_PR.PR14, DeviceObj)
  External(\_PR.PR15, DeviceObj)
  External(OSYS)

Scope(\)
{

  // Package of pointers to SSDT's
  //
  // First column is SSDT name, used for debug only.
  // (First column must be EXACTLY eight characters.)
  // Second column is physical address.
  // Third column is table length.
  //
  // IF modifying this file, see warnings listed in ppminit.asm.
  //
  Name(SSDT,Package()
  {
    "CPU0IST ", 0x80000000, 0x80000000,
    "APIST   ", 0x80000000, 0x80000000,
    "CPU0CST ", 0x80000000, 0x80000000,
    "APCST   ", 0x80000000, 0x80000000,
    "CPU0HWP ", 0x80000000, 0x80000000,
    "APHWP   ", 0x80000000, 0x80000000,
    "HWPLVT  ", 0x80000000, 0x80000000
  })

  Name(\PC00,0x80000000)  // PR00 _PDC Flags.
  Name(\PC01,0x80000000)  // PR01 _PDC Flags.
  Name(\PC02,0x80000000)  // PR02 _PDC Flags.
  Name(\PC03,0x80000000)  // PR03 _PDC Flags.
  Name(\PC04,0x80000000)  // PR04 _PDC Flags.
  Name(\PC05,0x80000000)  // PR05 _PDC Flags.
  Name(\PC06,0x80000000)  // PR06 _PDC Flags.
  Name(\PC07,0x80000000)  // PR07 _PDC Flags.
  Name(\PC08,0x80000000)  // PR08 _PDC Flags.
  Name(\PC09,0x80000000)  // PR09 _PDC Flags.
  Name(\PC10,0x80000000)  // PR10 _PDC Flags.
  Name(\PC11,0x80000000)  // PR11 _PDC Flags.
  Name(\PC12,0x80000000)  // PR12 _PDC Flags.
  Name(\PC13,0x80000000)  // PR13 _PDC Flags.
  Name(\PC14,0x80000000)  // PR14 _PDC Flags.
  Name(\PC15,0x80000000)  // PR15 _PDC Flags.

  Name(\SDTL,0x00)        // Loaded SSDT Flags.
  // SDTL[1]   = Cpu0Cst SSDT Loaded
  // SDTL[3]   = Cpu0Ist SSDT Loaded
  // SDTL[4]   = AP IST SSDT Loaded
  // SDTL[5]   = AP CST SSDT Loaded
  // SDTL[6]   = Cpu0Hwp SSDT Loaded
  // SDTL[7]   = Ap0Hwp SSDT Loaded
}

Scope(\_PR)
{
  Name(CTPC, 0 )        // Value for _TPC
  //
  // Define a Processor scope ACPI PPM GlobalNvs NVS Region
  //
  OperationRegion(PNVS,SystemMemory,0xFFFF0000,0xAA55)
  Field(PNVS,AnyAcc,Lock,Preserve)
  {
    PGRV,       8,      // (0) CPU GlobalNvs Revision
    //
    // PPM Flags Values
    //
    CFGD,      32,      // CFGD - PpmFlags
    Offset(6),          // (5) Reserved
    //
    // Thermal Configuration Values
    //
    ACRT,    8,        // (6) Auto Critical Trip Point
    APSV,    8,        // (7) Auto Passive Trip Point
    AAC0,    8,        // (8) Auto Active Trip Point
    CPID,    32,       // (9) CPUID
    //
    // ConfigTDP Value
    //
    CPPC,    8,        // (13) Boot Mode vlues for _PPC (ConfigurablePpc in CPU_GLOBAL_NVS_AREA)
    //
    // ConfigTDP Level settngs
    //
    CLVL,    8,        // (14) ConfigTdp Number Of Levels
    CBMI,    8,        // (15) CTDP Boot Mode Index
    PL10,    16,       // (16) CTDP Level 0 Power Limit1
    PL20,    16,       // (18) CTDP Level 0 Power Limit2
    PLW0,    8,        // (20) CTDP Level 0 Power Limit1 Time Window
    CTC0,    8,        // (21) CTDP Level 0 CTC
    TAR0,    8,        // (22) CTDP Level 0 TAR
    PPC0,    8,        // (23) CTDP Level 0 PPC
    PL11,    16,       // (24) CTDP Level 1 Power Limit1
    PL21,    16,       // (26) CTDP Level 1 Power Limit2
    PLW1,    8,        // (28) CTDP Level 1 Power Limit1 Time Window
    CTC1,    8,        // (29) CTDP Level 1 CTC
    TAR1,    8,        // (30) CTDP Level 1 TAR
    PPC1,    8,        // (31) CTDP Level 1 PPC
    PL12,    16,       // (32) CTDP Level 2 Power Limit1
    PL22,    16,       // (34) CTDP Level 2 Power Limit2
    PLW2,    8,        // (36) CTDP Level 2 Power Limit1 Time Window
    CTC2,    8,        // (37) CTDP Level 2 CTC
    TAR2,    8,        // (38) CTDP Level 2 TAR
    PPC2,    8,        // (39) CTDP Level 2 PPC
    //
    // Mwait Hints and Latency values for C3/C6/C7/C7S
    //
    C3MW,    8,        // (40) Mwait Hint value for C3
    C6MW,    8,        // (41) Mwait Hint value for C6
    C7MW,    8,        // (42) Mwait Hint value for C7/C7s
    CDMW,    8,        // (43) Mwait Hint value for C8/C9/C10
    C3LT,   16,        // (44-45) Latency value for C3
    C6LT,   16,        // (46-47) Latency Value for C6
    C7LT,   16,        // (48-49) Latency Value for C7/C7S
    CDLT,   16,        // (50-51) Latency Value for C8/C9/C10
    CDLV,   16,        // (52-53) IO LVL value for C8/C9/C10
    CDPW,   16,        // (54-55) Power value for C8/C9/C10
    MPMF,   8,         // (56) MiscPowerManagementFlags
    //
    // DTS
    //
    DTSE,   8,         // (57) Digital Thermal Sensor Enable
    DTS1,   8,         // (58) Digital Thermal Sensor 1 Reading
    DTS2,   8,         // (59) Digital Thermal Sensor 2 Reading
    DTSF,   8,         // (60) DTS SMI Function Call
    PDTS,   8,         // (61) Package Temperature
    PKGA,   8,         // (62) Package Temperature MSR available
    DTS3,   8,         // (63) Digital Thermal Sensor 3 Reading
    DTS4,   8,         // (64) Digital Thermal Sensor 4 Reading
    //
    // BIOS Guard
    //
    BGMA,   64,        // (65-72) BIOS Guard Memory Address for Tool Interface
    BGMS,   8,         // (73) BIOS Guard Memory Size for Tool Interface
    BGIA,   16,        // (74-75) BIOS Guard IoTrap Address for Tool Interface
    BGIL,   16,        // (76-77) BIOS Guard IoTrap Length for Tool Interface
    //
    // IO_D : DTS I/O Trap
    //
    DSIA,   16,        // (78-79) DTS IO trap Address
    DSIL,   8,         // (80)    DTS IO trap Length
    DSAE,   8,         // (81)    DTS is in ACPI Mode Enabled
    //
    // SGX
    //
    EPCS, 8,           // (82) SGX Status
    EMNA, 64,          // (83-90) EPC Base Address
    ELNG, 64,          // (91-98) EPC Length
    //
    // HWP
    //
    HWPV, 8,           // (99) HWP Version
    HWPA, 16,          // (100-101) IoTrap Address for HWP
    HWPL, 16,          // (102-103) IoTrap Length for HWP

    POWS, 8,           // (104) Power State
    HDCE, 8,           // (105) Hardware Duty Cycling Policy

    HWPI, 8,           // (106) HWP Interrupt Status
    DTSI, 8            // (107) DTS Interrupt Status
  }

  //
  // Define the IO Address 0810h-0813h as an ACPI Operating Region first, and
  // then it will be dynamically updated during initialization of DTS code.
  // The address presented here may not be the actual address used.
  // This address range is used as a DTS I/O Trap SMI so that ASL and SMI
  // can communicate when needed.
  //
  OperationRegion(IO_D, SystemIO, \_PR.DSIA, \_PR.DSIL)
  Field(IO_D,ByteAcc,NoLock,Preserve) {
    TRPD,  8  // 0x810 = DTS I/O Trap
  }

  //
  // Define the IO Address 1000h-1003h as an ACPI Operating Region first, and
  // then it will be dynamically updated during initialization of BIOS Guard code.
  // The address presented here may not be the actual address used.
  // This address range is used as a BIOS Guard Tools Interface I/O Trap so that the
  // update tool can trigger bios code to update the flash using the BIOS Guard flow.
  //
  OperationRegion (IO_P, SystemIO, \_PR.BGIA, \_PR.BGIL)
  Field (IO_P, ByteAcc, NoLock, Preserve) {
    TRPF, 8  // 0x1000 = BIOS Guard I/O Trap
  }
}

Scope(\_PR.PR00)
{
  //
  // Define handles for opregions (used by load.)
  //
  Name(HI0,0)    // Handle to CPU0IST
  Name(HC0,0)    // Handle to CPU0CST
  Name(HW0,0)    // Handle to CPU0HWP
  Name(HW2,0)    // Handle to HWPLVT

  Method(_PDC,1,Serialized)
  {
    //
    // Check and extract the _PDC information.
    //
    Store(CPDC(Arg0), Local0)
    //
    // Save the capability information and load tables as needed.
    //
    GCAP(Local0)
  }

  Method(_OSC,4,Serialized)
  {
    //
    // Check and extract the _OSC information.
    //
    Store(COSC(Arg0, Arg1, Arg2, Arg3), Local0)
    //
    // Save the capability information and load tables as needed.
    //
    GCAP(Local0)
    //
    // Return status.
    //
    Return (Local0)
  }

  //
  // Create the Status (STAT) buffer with the first DWORD = 0
  // This is required as per ACPI 3.0 Spec which says the
  // first DWORD is used to return errors defined by _OSC.
  //
  Name (STS0, Buffer () {0x00, 0x00, 0x00, 0x00})

  //
  // Implement a generic Method to check _PDC information which may be called
  // by any of the processor scopes.  (The use of _PDC is deprecated in ACPI 3.
  // in favor of _OSC. However, for backwards compatibility, _PDC may be
  // implemented using _OSC as follows:)
  //
  Method(CPDC,1,Serialized)
  {
    CreateDwordField (Arg0, 0, REVS)
    CreateDwordField (Arg0, 4, SIZE)

    //
    // Local0 = Number of bytes for Arg0
    //
    Store (SizeOf (Arg0), Local0)

    //
    // Local1 = Number of Capabilities bytes in Arg0
    //
    Store (Subtract (Local0, 8), Local1)

    //
    // TEMP = Temporary field holding Capability DWORDs
    //
    CreateField (Arg0, 64, Multiply (Local1, 8), TEMP)

    //
    // Concatenate the _PDC capabilities bytes to the STS0 Buffer
    // and store them in a local variable for calling OSC
    //
    Concatenate (STS0, TEMP, Local2)

    Return(COSC (ToUUID("4077A616-290C-47BE-9EBD-D87058713953"), REVS, SIZE, Local2))
  }

  //
  // UUID for COSC test
  //
  Name(UID0, ToUUID("4077A616-290C-47BE-9EBD-D87058713953"))

  //
  // Operational region for Smi port access
  //
  OperationRegion (SMIP, SystemIO, 0xB2, 1)
  Field (SMIP, ByteAcc, NoLock, Preserve)
  {
    IOB2, 8
  }

  //
  // Implement a generic Method to check _OSC information which may be called
  // by any of the processor scopes.
  //
  Method(COSC,4,Serialized)
  {
    //
    // Point to Status DWORD in the Arg3 buffer (STATUS)
    //
    CreateDWordField(Arg3, 0, STS0)
    //
    // Point to Caps DWORDs of the Arg3 buffer (CAPABILITIES)
    //
    CreateDwordField(Arg3, 4, CAP0)

    //
    // _OSC needs to validate the UUID and Revision.
    //
    // IF Unrecognized UUID
    //  Return Unrecognized UUID _OSC Failure
    // IF Unsupported Revision
    //  Return Unsupported Revision _OSC Failure
    //
    //    STS0[0] = Reserved
    //    STS0[1] = _OSC Failure
    //    STS0[2] = Unrecognized UUID
    //    STS0[3] = Unsupported Revision
    //    STS0[4] = Capabilities masked
    //
    // Note:  The comparison method used is necessary due to
    // limitations of certain OSes which cannot perform direct
    // buffer comparisons.
    //
    // Create a set of "Input" UUID fields.
    //
    CreateDwordField(Arg0, 0x0, IID0)
    CreateDwordField(Arg0, 0x4, IID1)
    CreateDwordField(Arg0, 0x8, IID2)
    CreateDwordField(Arg0, 0xC, IID3)
    //
    // Create a set of "Expected" UUID fields.
    //
    CreateDwordField(UID0, 0x0, EID0)
    CreateDwordField(UID0, 0x4, EID1)
    CreateDwordField(UID0, 0x8, EID2)
    CreateDwordField(UID0, 0xC, EID3)
    //
    // Verify the input UUID matches the expected UUID.
    //
    If(LNot(LAnd(LAnd(LEqual(IID0, EID0),LEqual(IID1, EID1)),LAnd(LEqual(IID2, EID2),LEqual(IID3, EID3)))))
    {
      //
      // Return Unrecognized UUID _OSC Failure
      //
      Store (0x6, STS0)
      Return (Arg3)
    }

    If(LNot(LEqual(Arg1,1)))
    {
      //
      // Return Unsupported Revision _OSC Failure
      //
      Store (0xA, STS0)
      Return (Arg3)
    }

    If(LNot(LGreaterEqual(Arg2, 2)))
    {
      //
      // Return Argument 3 Buffer Count not sufficient
      //
      Store (0x2, STS0)
      Return (Arg3)
    }

    If(Not(And(STS0, 0x01))) // Test Query Flag
    { // Not a query operation, so process the request
      If(And(CAP0, 0x2000))
      { // OSPM is capable of HDC, do not expose HDC in platform ACPI objects
        Store(0,\_PR.HDCE)
      } Else {  // Trigger SMI handler to write MSR to enable HDC Arch interface
        //
        //  Trigger SMI to setup HDC arch interface
        //
        Store (0x28, IOB2)
      }
    }

    Return (Arg3)
  }

  //
  // Get the capability information and load appropriate tables as needed.
  //
  Method(GCAP,1,Serialized)
  {
    //
    // Point to Status DWORD in the Arg0 buffer (STATUS)
    //
    CreateDWordField(Arg0, 0, STS0)
    //
    // Point to Caps DWORDs of the Arg0 buffer (CAPABILITIES)
    //
    CreateDwordField(Arg0, 4, CAP0)
    //
    // If the UUID was unrecognized or the _OSC revision was unsupported,
    // return without updating capabilities.
    //
    If(LOr(LEqual(STS0,0x6),LEqual(STS0,0xA)))
    {
      Return()
    }

    //
    // Check if this is a query (BIT0 of Status = 1).
    // If so, mask off the bits we support and return.
    //
    if (And(STS0, 1))
    {
      And(CAP0, 0xBFF, CAP0)
      Return()
    }

    //
    // Store result of PDC. (We clear out the MSB, which was just
    // used as a placeholder for the compiler; and then "OR" the
    // value in case we get multiple calls, each of which only
    // reports partial support.)
    //
    Or(And(PC00, 0x7FFFFFFF), CAP0, PC00)
    //
    // Check IF the CST SSDTs should be loaded.
    //   CFGD[5:1] = C7, C6, C3, C1E, C1 Capable/Enabled
    If(And(CFGD, PPM_C_STATES))
    {
      //
      // Load the CST SSDTs if:
      //   (1) CMP capable/enabled
      //   (2) Driver supports multi-processor configurations
      //   (3) CPU0 CST ISDT is not already loaded
      //
      //   CFGD[9] = Two or more cores enabled
      //   PCxx[3]  = OS supports C1 and P-states in MP systems
      //   PCxx[4]  = OS supports ind. C2/C3 in MP systems
      //   SDTL[1]  = CPU0 CST SSDT Loaded
      //
      If(LAnd(LAnd(And(CFGD, PPM_CMP),And(PC00,0x0018)),LNot(And(SDTL,0x02))))
      {
        //
        // Flag the CST SSDT as loaded for PR00
        //
        Or(SDTL, 0x02, SDTL)
        OperationRegion(CST0,SystemMemory,DeRefOf(Index(SSDT,7)),DeRefOf(Index(SSDT,8)))
        Load(CST0, HC0)  // Dynamically load the CPU0CST SSDT
      }
    }

    // Load the IST SSDTs if:
    //   (1) CMP capable/enabled
    //   (2) HWP not capable or enabled
    //   (3) Driver supports multi-processor configurations
    //   (4) CPU0 IST SSDT is not already loaded
    //
    //   CFGD[0]  = EIST Capable/Enabled
    //   SDTL[3]  = CPU0 IST SSDT Loaded
    //
    If(LAnd(And(CFGD,PPM_EIST),LNot(And(SDTL,0x08))))
    {
      //
      // Flag the IST SSDT as loaded for PR00
      //
      Or(SDTL, 0x08, SDTL)
      OperationRegion(IST0,SystemMemory,DeRefOf(Index(SSDT,1)),DeRefOf(Index(SSDT,2)))
      Load(IST0, HI0)  // Dynamically load the CPU1IST SSDT
    }

    // Dynamically load the Cpu0Hwp & HwpLvt  SSDT if:
    //   (1) If HWP capable and enabled
    //   (2) SSDT is not already loaded
    //
    // CFGD[22]  = HWP capable & enabled
    // CFGD[23]  = HWP LVT interrupt (SCI) enabled
    // SDTL[6]   = Cpu0Hwp SSDT Loaded
    // SB.OSC[5] = OS supports HWP v1
    // SB.OSC[6] = OS supports HWP v2
    //
    If ( LGreaterEqual(OSYS, 2015) ) {
     If(LAnd(And(CFGD, PPM_HWP),LNot(And(SDTL,0x40)))) {
        If(And(\_SB.OSCP,0x0040)) {
          //
          // Flag the Cpu0Hwp SSDT as loaded for PR00. We only support HWP v2.
          //
          Or(SDTL, 0x40, SDTL)
          OperationRegion(HWP0,SystemMemory,DeRefOf(Index(SSDT,13)),DeRefOf(Index(SSDT,14)))
          Load(HWP0, HW0)  // Dynamically load the Cpu0Hwp SSDT
          If(And(CFGD, PPM_HWP_LVT)) {
            OperationRegion(HWPL,SystemMemory,DeRefOf(Index(SSDT,19)),DeRefOf(Index(SSDT,20)))
            Load(HWPL, HW2)  // Dynamically load the HwpLvt SSDT
          }
        }
        //
        // Update HWP version
        //
        // If CAP0[5] = 1, CAP0[6] = 0 (HWP V1)
        // If CAP0[5] = 1, CAP0[6] = 1 (HWP V2)
        //
        If(And(\_SB.OSCP,0x0020)) {
          If(LNot(And(\_SB.OSCP,0x0040))) {
            //
            // HWP is not supported on Win 8.1, set HWPV = 0
            //
            Store(0x0, HWPV)
          }
        }
        If(And(\_SB.OSCP,0x0040)) {
          Store(0x2, HWPV)
        }
      }
    }

    //
    // Read _OSC object bit 12. If _OSC bit 12 is cleared on input, the platform must handle
    // the Thermal LVT interrupt
    //
    If(LNot(And(PC00,0x1000))) {
      //
      //  Trigger SMI to setup LVT interrupt and HWP Notifications
      //
      Store (0x27, IOB2)
    }
    Return ()
  }
}

Scope(\_PR.PR01)
{
  //
  // Define handles for opregions (used by load.)
  //
  Name(HI1,0)    // Handle to APIST
  Name(HC1,0)    // Handle to APCST
  Name(HW1,0)    // Handle to APHWP

  Method(_PDC,1,Serialized)
  {
    //
    // Refer to \_PR.PR00._PDC for description.
    //
    Store(\_PR.PR00.CPDC(Arg0), Local0)
    GCAP(Local0)
  }

  Method(_OSC,4,Serialized)
  {
    //
    // Refer to \_PR.PR00._OSC for description.
    //
    Store(\_PR.PR00.COSC(Arg0, Arg1, Arg2, Arg3), Local0)
    GCAP(Local0)
    Return (Local0)
  }

  //
  // Get the capability information and load appropriate tables as needed.
  //
  Method(GCAP,1,Serialized)
  {
    //
    // Point to Status DWORD in the Arg0 buffer (STATUS)
    //
    CreateDWordField(Arg0, 0, ST01)
    //
    // Point to Caps DWORDs of the Arg0 buffer (CAPABILITIES)
    //
    CreateDwordField(Arg0, 4, CP01)
    //
    // If the UUID was unrecognized or the _OSC revision was unsupported,
    // return without updating capabilities.
    //
    If(LOr(LEqual(ST01,0x6),LEqual(ST01,0xA)))
    {
      Return()
    }

    //
    // Check if this is a query (BIT0 of Status = 1).
    // If so, mask off the bits we support and return.
    //
    if (And(ST01, 1))
    {
      And(CP01, 0xBFF, CP01)
      Return()
    }

    //
    // Store result of PDC. (We clear out the MSB, which was just
    // used as a placeholder for the compiler; and then "OR" the
    // value in case we get multiple calls, each of which only
    // reports partial support.)
    //
    Or(And(PC01, 0x7FFFFFFF), CP01, PC01)
    //
    // Attempt to dynamically load the IST SSDTs if:
    //   (1) Driver supports P-States in MP configurations
    //   (2) Driver supports direct HW P-State control
    //
    //   PCxx[3]  = OS supports C1 and P-states in MP systems
    //   PCxx[0]  = OS supports direct access of the perf MSR
    //
    If(LEqual(And(PC01, 0x0009), 0x0009))
    {
      APPT()
    }

    //
    // Load Ap0Hwp SSDT
    // SB.OSC[5]   = OS supports CPPC from OSPM
    //
    if(And(\_SB.OSCP,0x0020)) {
      HWPT()
    }

    //
    // Load the CST SSDTs if:
    //   (1) Driver supports multi-processor configurations
    //
    //   PCxx[3]  = OS supports C1 and P-states in MP systems
    //   PCxx[4]  = OS supports ind. C2/C3 in MP systems
    //
    If(And(PC01,0x0018))
    {
      APCT()
    }

    Store (PC01, PC00)

    Return()
  }

  //
  // Dynamically load the CST SSDTs if:
  //   (1) C-States are enabled
  //   (2) SSDT is not already loaded
  //
  //   CFGD[5:1] = Basic C-States supported (C1, C1E, C3, C6, C7)
  //   SDTL[5]   = AP CST SSDT Loaded
  //
  Method(APCT,0,Serialized)
  {
    If(LAnd(And(CFGD,PPM_C_STATES),LNot(And(SDTL,0x20))))
    {
      //
      // Flag the CST SSDT as loaded for the AP's
      //
      Or(SDTL, 0x20, SDTL)
      //
      // Dynamically load the APCST SSDT
      //
      OperationRegion(CST1,SystemMemory,DeRefOf(Index(SSDT,10)),DeRefOf(Index(SSDT,11)))
      Load(CST1, HC1)
    }
  }

  //
  // Dynamically load the IST SSDTs if:
  //   (1) If EIST capable and enabled
  //   (2) SSDT is not already loaded
  //
  //   CFGD[0] = EIST Capable/Enabled
  //   SDTL[4] = AP IST SSDT Loaded
  //
  Method(APPT,0,Serialized)
  {
    If(LAnd(And(CFGD,PPM_EIST),LNot(And(SDTL,0x10))))
    {
      //
      // Flag the IST SSDT as loaded for PR00
      //
      Or(SDTL, 0x10, SDTL)
      OperationRegion(IST1,SystemMemory,DeRefOf(Index(SSDT,4)),DeRefOf(Index(SSDT,5)))
      Load(IST1, HI1)  // Dynamically load the CPU1IST SSDT
    }
  }

  //
  // Dynamically load the Ap0Hwp SSDT if:
  //   (1) If HWP capable and enabled
  //   (2) SSDT is not already loaded
  //
  // CFGD[22]  = HWP capable & enabled
  // SDTL[7]   = Ap0Hwp SSDT Loaded
  //
  Method(HWPT,0,Serialized)
  {
    If ( LGreaterEqual(OSYS, 2015) ) {
      If(LAnd(And(CFGD, PPM_HWP),LNot(And(SDTL,0x80)))) {
        //
        // Flag the Ap0Hwp SSDT as loaded for PR00
        //
        Or(SDTL, 0x80, SDTL)
        OperationRegion(HWP1,SystemMemory,DeRefOf(Index(SSDT,16)),DeRefOf(Index(SSDT,17)))
        Load(HWP1, HW1)  // Dynamically load the Ap0Hwp SSDT
      }
    }
  }
}  // End PR01


Scope(\_PR.PR02)
{
  Method(_PDC,1)
  {
    //
    // Call the _PDC for PR00.
    //
    Store(\_PR.PR00.CPDC(Arg0), Local0)
    GCAP(Local0)
  }

  Method(_OSC, 4)
  {
    //
    // Call the _OSC for PR01.
    //
    Store(\_PR.PR00.COSC(Arg0, Arg1, Arg2, Arg3), Local0)
    GCAP(Local0)
    Return (Local0)
  }

  Method(GCAP,1)
  {
    // Point to Status DWORD in the Arg0 buffer (STATUS)
    CreateDWordField(Arg0, 0, ST02)

    // Point to Caps DWORDs of the Arg0 buffer (CAPABILITIES)
    CreateDwordField(Arg0, 4, CP02)

    //
    // If the UUID was unrecognized or the _OSC revision was unsupported,
    // return without updating capabilities.
    //
    If(LOr(LEqual(ST02,0x6),LEqual(ST02,0xA)))
    {
      Return()
    }

    //
    // Check if this is a query (BIT0 of Status = 1).
    // If so, mask off the bits we support and return.
    //
    if (And(ST02, 1))
    {
      And(CP02, 0xBFF, CP02)
      Return()
    }

    //
    // Store result of PDC. (We clear out the MSB, which was just
    // used as a placeholder for the compiler; and then "OR" the
    // value in case we get multiple calls, each of which only
    // reports partial support.)
    //
    Or(And(PC02, 0x7FFFFFFF), CP02, PC02)
    //
    // Attempt to dynamically load the IST SSDTs if:
    //   (1) Driver supports P-States in MP configurations
    //   (2) Driver supports direct HW P-State control
    //
    //   PCxx[3]  = OS supports C1 and P-states in MP systems
    //   PCxx[0]  = OS supports direct access of the perf MSR
    //
    If(LEqual(And(PC02, 0x0009), 0x0009))
    {
      \_PR.PR01.APPT()
    }
    // Load Ap0Hwp SSDT
    // SB.OSC[5]   = OS supports CPPC from OSPM
    //
    if(And(\_SB.OSCP,0x0020)) {
      \_PR.PR01.HWPT()
    }
    //
    // Load the CST SSDTs if:
    //   (1) Driver supports multi-processor configurations
    //
    //   PCxx[3]  = OS supports C1 and P-states in MP systems
    //   PCxx[4]  = OS supports ind. C2/C3 in MP systems
    //
    If(And(PC02,0x0018))
    {
      \_PR.PR01.APCT()
    }

    Store (PC02, PC00)
    Return()
  }
}  // End PR02

Scope(\_PR.PR03)
{
  Method(_PDC,1)
  {
    //
    // Call the _PDC for PR00.
    //
    Store(\_PR.PR00.CPDC(Arg0), Local0)
    GCAP(Local0)
  }

  Method(_OSC, 4)
  {
    //
    // Call the _OSC for PR00.
    //
    Store(\_PR.PR00.COSC(Arg0, Arg1, Arg2, Arg3), Local0)
    GCAP(Local0)
    Return (Local0)
  }

  Method(GCAP,1)
  {
    // Point to Status DWORD in the Arg0 buffer (STATUS)
    CreateDWordField(Arg0, 0, ST03)

    // Point to Caps DWORDs of the Arg0 buffer (CAPABILITIES)
    CreateDwordField(Arg0, 4, CP03)

    //
    // If the UUID was unrecognized or the _OSC revision was unsupported,
    // return without updating capabilities.
    //
    If(LOr(LEqual(ST03,0x6),LEqual(ST03,0xA)))
    {
      Return()
    }

    //
    // Check if this is a query (BIT0 of Status = 1).
    // If so, mask off the bits we support and return.
    //
    if (And(ST03, 1))
    {
      And(CP03, 0xBFF, CP03)
      Return()
    }

    //
    // Store result of PDC. (We clear out the MSB, which was just
    // used as a placeholder for the compiler; and then "OR" the
    // value in case we get multiple calls, each of which only
    // reports partial support.)
    //
    Or(And(PC03, 0x7FFFFFFF), CP03, PC03)
    //
    // Attempt to dynamically load the IST SSDTs if:
    //   (1) Driver supports P-States in MP configurations
    //   (2) Driver supports direct HW P-State control
    //
    //   PCxx[3]  = OS supports C1 and P-states in MP systems
    //   PCxx[0]  = OS supports direct access of the perf MSR
    //
    If(LEqual(And(PC03, 0x0009), 0x0009))
    {
      \_PR.PR01.APPT()
    }
    // Load Ap0Hwp SSDT
    // SB.OSC[5]   = OS supports CPPC from OSPM
    //
    if(And(\_SB.OSCP,0x0020)) {
      \_PR.PR01.HWPT()
    }
    //
    // Load the CST SSDTs if:
    //   (1) Driver supports multi-processor configurations
    //
    //   PCxx[3]  = OS supports C1 and P-states in MP systems
    //   PCxx[4]  = OS supports ind. C2/C3 in MP systems
    //
    If(And(PC03,0x0018))
    {
      \_PR.PR01.APCT()
    }

    Store (PC03, PC00)
    Return()
  }
} // End PR03

Scope(\_PR.PR04)
{
  Method(_PDC,1)
  {
    //
    // Call the _PDC for PR00.
    //
    Store(\_PR.PR00.CPDC(Arg0), Local0)
    GCAP(Local0)
  }

  Method(_OSC, 4)
  {
    //
    // Call the _OSC for PR00.
    //
    Store(\_PR.PR00.COSC(Arg0, Arg1, Arg2, Arg3), Local0)
    GCAP(Local0)
    Return (Local0)
  }

  Method(GCAP,1)
  {
    // Point to Status DWORD in the Arg0 buffer (STATUS)
    CreateDWordField(Arg0, 0, ST04)

    // Point to Caps DWORDs of the Arg0 buffer (CAPABILITIES)
    CreateDwordField(Arg0, 4, CP04)

    //
    // If the UUID was unrecognized or the _OSC revision was unsupported,
    // return without updating capabilities.
    //
    If(LOr(LEqual(ST04,0x6),LEqual(ST04,0xA)))
    {
      Return()
    }

    //
    // Check if this is a query (BIT0 of Status = 1).
    // If so, mask off the bits we support and return.
    //
    if (And(ST04, 1))
    {
      And(CP04, 0xBFF, CP04)
      Return()
    }

    //
    // Store result of PDC. (We clear out the MSB, which was just
    // used as a placeholder for the compiler; and then "OR" the
    // value in case we get multiple calls, each of which only
    // reports partial support.)
    //
    Or(And(PC04, 0x7FFFFFFF), CP04, PC04)
    //
    // Attempt to dynamically load the IST SSDTs if:
    //   (1) Driver supports P-States in MP configurations
    //   (2) Driver supports direct HW P-State control
    //
    //   PCxx[3]  = OS supports C1 and P-states in MP systems
    //   PCxx[0]  = OS supports direct access of the perf MSR
    //
    If(LEqual(And(PC04, 0x0009), 0x0009))
    {
      \_PR.PR01.APPT()
    }
    // Load Ap0Hwp SSDT
    // SB.OSC[5]   = OS supports CPPC from OSPM
    //
    if(And(\_SB.OSCP,0x0020)) {
      \_PR.PR01.HWPT()
    }
    //
    // Load the CST SSDTs if:
    //   (1) Driver supports multi-processor configurations
    //
    //   PCxx[3]  = OS supports C1 and P-states in MP systems
    //   PCxx[4]  = OS supports ind. C2/C3 in MP systems
    //
    If(And(PC04,0x0018))
    {
      \_PR.PR01.APCT()
    }

    Store (PC04, PC00)
    Return()
  }
} // End PR04

Scope(\_PR.PR05)
{
  Method(_PDC,1)
  {
    //
    // Call the _PDC for PR00.
    //
    Store(\_PR.PR00.CPDC(Arg0), Local0)
    GCAP(Local0)
  }

  Method(_OSC, 4)
  {
    //
    // Call the _OSC for PR00.
    //
    Store(\_PR.PR00.COSC(Arg0, Arg1, Arg2, Arg3), Local0)
    GCAP(Local0)
    Return (Local0)
  }

  Method(GCAP,1)
  {
    // Point to Status DWORD in the Arg0 buffer (STATUS)
    CreateDWordField(Arg0, 0, ST05)

    // Point to Caps DWORDs of the Arg0 buffer (CAPABILITIES)
    CreateDwordField(Arg0, 4, CP05)

    //
    // If the UUID was unrecognized or the _OSC revision was unsupported,
    // return without updating capabilities.
    //
    If(LOr(LEqual(ST05,0x6),LEqual(ST05,0xA)))
    {
      Return()
    }

    //
    // Check if this is a query (BIT0 of Status = 1).
    // If so, mask off the bits we support and return.
    //
    if (And(ST05, 1))
    {
      And(CP05, 0xBFF, CP05)
      Return()
    }

    //
    // Store result of PDC. (We clear out the MSB, which was just
    // used as a placeholder for the compiler; and then "OR" the
    // value in case we get multiple calls, each of which only
    // reports partial support.)
    //
    Or(And(PC05, 0x7FFFFFFF), CP05, PC05)
    //
    // Attempt to dynamically load the IST SSDTs if:
    //   (1) Driver supports P-States in MP configurations
    //   (2) Driver supports direct HW P-State control
    //
    //   PCxx[3]  = OS supports C1 and P-states in MP systems
    //   PCxx[0]  = OS supports direct access of the perf MSR
    //
    If(LEqual(And(PC05, 0x0009), 0x0009))
    {
      \_PR.PR01.APPT()
    }
    // Load Ap0Hwp SSDT
    // SB.OSC[5]   = OS supports CPPC from OSPM
    //
    if(And(\_SB.OSCP,0x0020)) {
      \_PR.PR01.HWPT()
    }
    //
    // Load the CST SSDTs if:
    //   (1) Driver supports multi-processor configurations
    //
    //   PCxx[3]  = OS supports C1 and P-states in MP systems
    //   PCxx[4]  = OS supports ind. C2/C3 in MP systems
    //
    If(And(PC05,0x0018))
    {
      \_PR.PR01.APCT()
    }

    Store (PC05, PC00)
    Return()
  }
} // End PR05

Scope(\_PR.PR06)
{
  Method(_PDC,1)
  {
    //
    // Call the _PDC for PR00.
    //
    Store(\_PR.PR00.CPDC(Arg0), Local0)
    GCAP(Local0)
  }

  Method(_OSC, 4)
  {
    //
    // Call the _OSC for PR00.
    //
    Store(\_PR.PR00.COSC(Arg0, Arg1, Arg2, Arg3), Local0)
    GCAP(Local0)
    Return (Local0)
  }

  Method(GCAP,1)
  {
    // Point to Status DWORD in the Arg0 buffer (STATUS)
    CreateDWordField(Arg0, 0, ST06)

    // Point to Caps DWORDs of the Arg0 buffer (CAPABILITIES)
    CreateDwordField(Arg0, 4, CP06)

    //
    // If the UUID was unrecognized or the _OSC revision was unsupported,
    // return without updating capabilities.
    //
    If(LOr(LEqual(ST06,0x6),LEqual(ST06,0xA)))
    {
      Return()
    }

    //
    // Check if this is a query (BIT0 of Status = 1).
    // If so, mask off the bits we support and return.
    //
    if (And(ST06, 1))
    {
      And(CP06, 0xBFF, CP06)
      Return()
    }

    //
    // Store result of PDC. (We clear out the MSB, which was just
    // used as a placeholder for the compiler; and then "OR" the
    // value in case we get multiple calls, each of which only
    // reports partial support.)
    //
    Or(And(PC06, 0x7FFFFFFF), CP06, PC06)
    //
    // Attempt to dynamically load the IST SSDTs if:
    //   (1) Driver supports P-States in MP configurations
    //   (2) Driver supports direct HW P-State control
    //
    //   PCxx[3]  = OS supports C1 and P-states in MP systems
    //   PCxx[0]  = OS supports direct access of the perf MSR
    //
    If(LEqual(And(PC06, 0x0009), 0x0009))
    {
      \_PR.PR01.APPT()
    }
    // Load Ap0Hwp SSDT
    // SB.OSC[5]   = OS supports CPPC from OSPM
    //
    if(And(\_SB.OSCP,0x0020)) {
      \_PR.PR01.HWPT()
    }
    //
    // Load the CST SSDTs if:
    //   (1) Driver supports multi-processor configurations
    //
    //   PCxx[3]  = OS supports C1 and P-states in MP systems
    //   PCxx[4]  = OS supports ind. C2/C3 in MP systems
    //
    If(And(PC06,0x0018))
    {
      \_PR.PR01.APCT()
    }

    Store (PC06, PC00)
    Return()
  }
} // End PR06

Scope(\_PR.PR07)
{
  Method(_PDC,1)
  {
    //
    // Call the _PDC for PR00.
    //
    Store(\_PR.PR00.CPDC(Arg0), Local0)
    GCAP(Local0)
  }

  Method(_OSC, 4)
  {
    //
    // Call the _OSC for PR00.
    //
    Store(\_PR.PR00.COSC(Arg0, Arg1, Arg2, Arg3), Local0)
    GCAP(Local0)
    Return (Local0)
  }

  Method(GCAP,1)
  {
    // Point to Status DWORD in the Arg0 buffer (STATUS)
    CreateDWordField(Arg0, 0, ST07)

    // Point to Caps DWORDs of the Arg0 buffer (CAPABILITIES)
    CreateDwordField(Arg0, 4, CP07)

    //
    // If the UUID was unrecognized or the _OSC revision was unsupported,
    // return without updating capabilities.
    //
    If(LOr(LEqual(ST07,0x6),LEqual(ST07,0xA)))
    {
      Return()
    }

    //
    // Check if this is a query (BIT0 of Status = 1).
    // If so, mask off the bits we support and return.
    //
    if (And(ST07, 1))
    {
      And(CP07, 0xBFF, CP07)
      Return()
    }

    //
    // Store result of PDC. (We clear out the MSB, which was just
    // used as a placeholder for the compiler; and then "OR" the
    // value in case we get multiple calls, each of which only
    // reports partial support.)
    //
    Or(And(PC07, 0x7FFFFFFF), CP07, PC07)
    //
    // Attempt to dynamically load the IST SSDTs if:
    //   (1) Driver supports P-States in MP configurations
    //   (2) Driver supports direct HW P-State control
    //
    //   PCxx[3]  = OS supports C1 and P-states in MP systems
    //   PCxx[0]  = OS supports direct access of the perf MSR
    //
    If(LEqual(And(PC07, 0x0009), 0x0009))
    {
      \_PR.PR01.APPT()
    }
    // Load Ap0Hwp SSDT
    // SB.OSC[5]   = OS supports CPPC from OSPM
    //
    if(And(\_SB.OSCP,0x0020)) {
      \_PR.PR01.HWPT()
    }
    //
    // Load the CST SSDTs if:
    //   (1) Driver supports multi-processor configurations
    //
    //   PCxx[3]  = OS supports C1 and P-states in MP systems
    //   PCxx[4]  = OS supports ind. C2/C3 in MP systems
    //
    If(And(PC07,0x0018))
    {
      \_PR.PR01.APCT()
    }

    Store (PC07, PC00)
    Return()
  }
} // End PR07

Scope(\_PR.PR08)
{
  Method(_PDC,1)
  {
    //
    // Call the _PDC for PR00.
    //
    Store(\_PR.PR00.CPDC(Arg0), Local0)
    GCAP(Local0)
  }

  Method(_OSC, 4)
  {
    //
    // Call the _OSC for PR00.
    //
    Store(\_PR.PR00.COSC(Arg0, Arg1, Arg2, Arg3), Local0)
    GCAP(Local0)
    Return (Local0)
  }

  Method(GCAP,1)
  {
    // Point to Status DWORD in the Arg0 buffer (STATUS)
    CreateDWordField(Arg0, 0, ST08)

    // Point to Caps DWORDs of the Arg0 buffer (CAPABILITIES)
    CreateDwordField(Arg0, 4, CP08)

    //
    // If the UUID was unrecognized or the _OSC revision was unsupported,
    // return without updating capabilities.
    //
    If(LOr(LEqual(ST08,0x6),LEqual(ST08,0xA)))
    {
      Return()
    }

    //
    // Check if this is a query (BIT0 of Status = 1).
    // If so, mask off the bits we support and return.
    //
    if (And(ST08, 1))
    {
      And(CP08, 0xBFF, CP08)
      Return()
    }

    //
    // Store result of PDC. (We clear out the MSB, which was just
    // used as a placeholder for the compiler; and then "OR" the
    // value in case we get multiple calls, each of which only
    // reports partial support.)
    //
    Or(And(PC08, 0x7FFFFFFF), CP08, PC08)
    //
    // Attempt to dynamically load the IST SSDTs if:
    //   (1) Driver supports P-States in MP configurations
    //   (2) Driver supports direct HW P-State control
    //
    //   PCxx[3]  = OS supports C1 and P-states in MP systems
    //   PCxx[0]  = OS supports direct access of the perf MSR
    //
    If(LEqual(And(PC08, 0x0009), 0x0009))
    {
      \_PR.PR01.APPT()
    }
    // Load Ap0Hwp SSDT
    // SB.OSC[5]   = OS supports CPPC from OSPM
    //
    if(And(\_SB.OSCP,0x0020)) {
      \_PR.PR01.HWPT()
    }
    //
    // Load the CST SSDTs if:
    //   (1) Driver supports multi-processor configurations
    //
    //   PCxx[3]  = OS supports C1 and P-states in MP systems
    //   PCxx[4]  = OS supports ind. C2/C3 in MP systems
    //
    If(And(PC08,0x0018))
    {
      \_PR.PR01.APCT()
    }

    Store (PC08, PC00)
    Return()
  }
} // End PR08

Scope(\_PR.PR09)
{
  Method(_PDC,1)
  {
    //
    // Call the _PDC for PR00.
    //
    Store(\_PR.PR00.CPDC(Arg0), Local0)
    GCAP(Local0)
  }

  Method(_OSC, 4)
  {
    //
    // Call the _OSC for PR00.
    //
    Store(\_PR.PR00.COSC(Arg0, Arg1, Arg2, Arg3), Local0)
    GCAP(Local0)
    Return (Local0)
  }

  Method(GCAP,1)
  {
    // Point to Status DWORD in the Arg0 buffer (STATUS)
    CreateDWordField(Arg0, 0, ST09)

    // Point to Caps DWORDs of the Arg0 buffer (CAPABILITIES)
    CreateDwordField(Arg0, 4, CP09)

    //
    // If the UUID was unrecognized or the _OSC revision was unsupported,
    // return without updating capabilities.
    //
    If(LOr(LEqual(ST09,0x6),LEqual(ST09,0xA)))
    {
      Return()
    }

    //
    // Check if this is a query (BIT0 of Status = 1).
    // If so, mask off the bits we support and return.
    //
    if (And(ST09, 1))
    {
      And(CP09, 0xBFF, CP09)
      Return()
    }

    //
    // Store result of PDC. (We clear out the MSB, which was just
    // used as a placeholder for the compiler; and then "OR" the
    // value in case we get multiple calls, each of which only
    // reports partial support.)
    //
    Or(And(PC09, 0x7FFFFFFF), CP09, PC09)
    //
    // Attempt to dynamically load the IST SSDTs if:
    //   (1) Driver supports P-States in MP configurations
    //   (2) Driver supports direct HW P-State control
    //
    //   PCxx[3]  = OS supports C1 and P-states in MP systems
    //   PCxx[0]  = OS supports direct access of the perf MSR
    //
    If(LEqual(And(PC09, 0x0009), 0x0009))
    {
      \_PR.PR01.APPT()
    }
    // Load Ap0Hwp SSDT
    // SB.OSC[5]   = OS supports CPPC from OSPM
    //
    if(And(\_SB.OSCP,0x0020)) {
      \_PR.PR01.HWPT()
    }
    //
    // Load the CST SSDTs if:
    //   (1) Driver supports multi-processor configurations
    //
    //   PCxx[3]  = OS supports C1 and P-states in MP systems
    //   PCxx[4]  = OS supports ind. C2/C3 in MP systems
    //
    If(And(PC09,0x0018))
    {
      \_PR.PR01.APCT()
    }

    Store (PC09, PC00)
    Return()
  }
} // End PR09

Scope(\_PR.PR10)
{
  Method(_PDC,1)
  {
    //
    // Call the _PDC for PR00.
    //
    Store(\_PR.PR00.CPDC(Arg0), Local0)
    GCAP(Local0)
  }

  Method(_OSC, 4)
  {
    //
    // Call the _OSC for PR00.
    //
    Store(\_PR.PR00.COSC(Arg0, Arg1, Arg2, Arg3), Local0)
    GCAP(Local0)
    Return (Local0)
  }

  Method(GCAP,1)
  {
    // Point to Status DWORD in the Arg0 buffer (STATUS)
    CreateDWordField(Arg0, 0, ST10)

    // Point to Caps DWORDs of the Arg0 buffer (CAPABILITIES)
    CreateDwordField(Arg0, 4, CP10)

    //
    // If the UUID was unrecognized or the _OSC revision was unsupported,
    // return without updating capabilities.
    //
    If(LOr(LEqual(ST10,0x6),LEqual(ST10,0xA)))
    {
      Return()
    }

    //
    // Check if this is a query (BIT0 of Status = 1).
    // If so, mask off the bits we support and return.
    //
    if (And(ST10, 1))
    {
      And(ST10, 0xBFF, CP10)
      Return()
    }

    //
    // Store result of PDC. (We clear out the MSB, which was just
    // used as a placeholder for the compiler; and then "OR" the
    // value in case we get multiple calls, each of which only
    // reports partial support.)
    //
    Or(And(PC10, 0x7FFFFFFF), CP10, PC10)
    //
    // Attempt to dynamically load the IST SSDTs if:
    //   (1) Driver supports P-States in MP configurations
    //   (2) Driver supports direct HW P-State control
    //
    //   PCxx[3]  = OS supports C1 and P-states in MP systems
    //   PCxx[0]  = OS supports direct access of the perf MSR
    //
    If(LEqual(And(PC10, 0x0009), 0x0009))
    {
      \_PR.PR01.APPT()
    }
    // Load Ap0Hwp SSDT
    // SB.OSC[5]   = OS supports CPPC from OSPM
    //
    if(And(\_SB.OSCP,0x0020)) {
      \_PR.PR01.HWPT()
    }
    //
    // Load the CST SSDTs if:
    //   (1) Driver supports multi-processor configurations
    //
    //   PCxx[3]  = OS supports C1 and P-states in MP systems
    //   PCxx[4]  = OS supports ind. C2/C3 in MP systems
    //
    If(And(PC10,0x0018))
    {
      \_PR.PR01.APCT()
    }

    Store (PC10, PC00)
    Return()
  }
} // End PR10

Scope(\_PR.PR11)
{
  Method(_PDC,1)
  {
    //
    // Call the _PDC for PR00.
    //
    Store(\_PR.PR00.CPDC(Arg0), Local0)
    GCAP(Local0)
  }

  Method(_OSC, 4)
  {
    //
    // Call the _OSC for PR00.
    //
    Store(\_PR.PR00.COSC(Arg0, Arg1, Arg2, Arg3), Local0)
    GCAP(Local0)
    Return (Local0)
  }

  Method(GCAP,1)
  {
    // Point to Status DWORD in the Arg0 buffer (STATUS)
    CreateDWordField(Arg0, 0, ST11)

    // Point to Caps DWORDs of the Arg0 buffer (CAPABILITIES)
    CreateDwordField(Arg0, 4, CP11)

    //
    // If the UUID was unrecognized or the _OSC revision was unsupported,
    // return without updating capabilities.
    //
    If(LOr(LEqual(ST11,0x6),LEqual(ST11,0xA)))
    {
      Return()
    }

    //
    // Check if this is a query (BIT0 of Status = 1).
    // If so, mask off the bits we support and return.
    //
    if (And(ST11, 1))
    {
      And(ST11, 0xBFF, CP11)
      Return()
    }

    //
    // Store result of PDC. (We clear out the MSB, which was just
    // used as a placeholder for the compiler; and then "OR" the
    // value in case we get multiple calls, each of which only
    // reports partial support.)
    //
    Or(And(PC11, 0x7FFFFFFF), CP11, PC11)
    //
    // Attempt to dynamically load the IST SSDTs if:
    //   (1) Driver supports P-States in MP configurations
    //   (2) Driver supports direct HW P-State control
    //
    //   PCxx[3]  = OS supports C1 and P-states in MP systems
    //   PCxx[0]  = OS supports direct access of the perf MSR
    //
    If(LEqual(And(PC11, 0x0009), 0x0009))
    {
      \_PR.PR01.APPT()
    }
    // Load Ap0Hwp SSDT
    // SB.OSC[5]   = OS supports CPPC from OSPM
    //
    if(And(\_SB.OSCP,0x0020)) {
      \_PR.PR01.HWPT()
    }
    //
    // Load the CST SSDTs if:
    //   (1) Driver supports multi-processor configurations
    //
    //   PCxx[3]  = OS supports C1 and P-states in MP systems
    //   PCxx[4]  = OS supports ind. C2/C3 in MP systems
    //
    If(And(PC11,0x0018))
    {
      \_PR.PR01.APCT()
    }

    Store (PC11, PC00)
    Return()
  }
} // End PR11

Scope(\_PR.PR12)
{
  Method(_PDC,1)
  {
    //
    // Call the _PDC for PR00.
    //
    Store(\_PR.PR00.CPDC(Arg0), Local0)
    GCAP(Local0)
  }

  Method(_OSC, 4)
  {
    //
    // Call the _OSC for PR00.
    //
    Store(\_PR.PR00.COSC(Arg0, Arg1, Arg2, Arg3), Local0)
    GCAP(Local0)
    Return (Local0)
  }

  Method(GCAP,1)
  {
    // Point to Status DWORD in the Arg0 buffer (STATUS)
    CreateDWordField(Arg0, 0, ST12)

    // Point to Caps DWORDs of the Arg0 buffer (CAPABILITIES)
    CreateDwordField(Arg0, 4, CP12)

    //
    // If the UUID was unrecognized or the _OSC revision was unsupported,
    // return without updating capabilities.
    //
    If(LOr(LEqual(ST12,0x6),LEqual(ST12,0xA)))
    {
      Return()
    }

    //
    // Check if this is a query (BIT0 of Status = 1).
    // If so, mask off the bits we support and return.
    //
    if (And(ST12, 1))
    {
      And(ST12, 0xBFF, CP12)
      Return()
    }

    //
    // Store result of PDC. (We clear out the MSB, which was just
    // used as a placeholder for the compiler; and then "OR" the
    // value in case we get multiple calls, each of which only
    // reports partial support.)
    //
    Or(And(PC12, 0x7FFFFFFF), CP12, PC12)
    //
    // Attempt to dynamically load the IST SSDTs if:
    //   (1) Driver supports P-States in MP configurations
    //   (2) Driver supports direct HW P-State control
    //
    //   PCxx[3]  = OS supports C1 and P-states in MP systems
    //   PCxx[0]  = OS supports direct access of the perf MSR
    //
    If(LEqual(And(PC12, 0x0009), 0x0009))
    {
      \_PR.PR01.APPT()
    }
    // Load Ap0Hwp SSDT
    // SB.OSC[5]   = OS supports CPPC from OSPM
    //
    if(And(\_SB.OSCP,0x0020)) {
      \_PR.PR01.HWPT()
    }
    //
    // Load the CST SSDTs if:
    //   (1) Driver supports multi-processor configurations
    //
    //   PCxx[3]  = OS supports C1 and P-states in MP systems
    //   PCxx[4]  = OS supports ind. C2/C3 in MP systems
    //
    If(And(PC12,0x0018))
    {
      \_PR.PR01.APCT()
    }

    Store (PC12, PC00)
    Return()
  }
} // End PR12

Scope(\_PR.PR13)
{
  Method(_PDC,1)
  {
    //
    // Call the _PDC for PR00.
    //
    Store(\_PR.PR00.CPDC(Arg0), Local0)
    GCAP(Local0)
  }

  Method(_OSC, 4)
  {
    //
    // Call the _OSC for PR00.
    //
    Store(\_PR.PR00.COSC(Arg0, Arg1, Arg2, Arg3), Local0)
    GCAP(Local0)
    Return (Local0)
  }

  Method(GCAP,1)
  {
    // Point to Status DWORD in the Arg0 buffer (STATUS)
    CreateDWordField(Arg0, 0, ST13)

    // Point to Caps DWORDs of the Arg0 buffer (CAPABILITIES)
    CreateDwordField(Arg0, 4, CP13)

    //
    // If the UUID was unrecognized or the _OSC revision was unsupported,
    // return without updating capabilities.
    //
    If(LOr(LEqual(ST13,0x6),LEqual(ST13,0xA)))
    {
      Return()
    }

    //
    // Check if this is a query (BIT0 of Status = 1).
    // If so, mask off the bits we support and return.
    //
    if (And(ST13, 1))
    {
      And(ST13, 0xBFF, CP13)
      Return()
    }

    //
    // Store result of PDC. (We clear out the MSB, which was just
    // used as a placeholder for the compiler; and then "OR" the
    // value in case we get multiple calls, each of which only
    // reports partial support.)
    //
    Or(And(PC13, 0x7FFFFFFF), CP13, PC13)
    //
    // Attempt to dynamically load the IST SSDTs if:
    //   (1) Driver supports P-States in MP configurations
    //   (2) Driver supports direct HW P-State control
    //
    //   PCxx[3]  = OS supports C1 and P-states in MP systems
    //   PCxx[0]  = OS supports direct access of the perf MSR
    //
    If(LEqual(And(PC13, 0x0009), 0x0009))
    {
      \_PR.PR01.APPT()
    }
    // Load Ap0Hwp SSDT
    // SB.OSC[5]   = OS supports CPPC from OSPM
    //
    if(And(\_SB.OSCP,0x0020)) {
      \_PR.PR01.HWPT()
    }
    //
    // Load the CST SSDTs if:
    //   (1) Driver supports multi-processor configurations
    //
    //   PCxx[3]  = OS supports C1 and P-states in MP systems
    //   PCxx[4]  = OS supports ind. C2/C3 in MP systems
    //
    If(And(PC13,0x0018))
    {
      \_PR.PR01.APCT()
    }

    Store (PC13, PC00)
    Return()
  }
} // End PR13

Scope(\_PR.PR14)
{
  Method(_PDC,1)
  {
    //
    // Call the _PDC for PR00.
    //
    Store(\_PR.PR00.CPDC(Arg0), Local0)
    GCAP(Local0)
  }

  Method(_OSC, 4)
  {
    //
    // Call the _OSC for PR00.
    //
    Store(\_PR.PR00.COSC(Arg0, Arg1, Arg2, Arg3), Local0)
    GCAP(Local0)
    Return (Local0)
  }

  Method(GCAP,1)
  {
    // Point to Status DWORD in the Arg0 buffer (STATUS)
    CreateDWordField(Arg0, 0, ST14)

    // Point to Caps DWORDs of the Arg0 buffer (CAPABILITIES)
    CreateDwordField(Arg0, 4, CP14)

    //
    // If the UUID was unrecognized or the _OSC revision was unsupported,
    // return without updating capabilities.
    //
    If(LOr(LEqual(ST14,0x6),LEqual(ST14,0xA)))
    {
      Return()
    }

    //
    // Check if this is a query (BIT0 of Status = 1).
    // If so, mask off the bits we support and return.
    //
    if (And(ST14, 1))
    {
      And(ST14, 0xBFF, CP14)
      Return()
    }

    //
    // Store result of PDC. (We clear out the MSB, which was just
    // used as a placeholder for the compiler; and then "OR" the
    // value in case we get multiple calls, each of which only
    // reports partial support.)
    //
    Or(And(PC14, 0x7FFFFFFF), CP14, PC14)
    //
    // Attempt to dynamically load the IST SSDTs if:
    //   (1) Driver supports P-States in MP configurations
    //   (2) Driver supports direct HW P-State control
    //
    //   PCxx[3]  = OS supports C1 and P-states in MP systems
    //   PCxx[0]  = OS supports direct access of the perf MSR
    //
    If(LEqual(And(PC14, 0x0009), 0x0009))
    {
      \_PR.PR01.APPT()
    }
    // Load Ap0Hwp SSDT
    // SB.OSC[5]   = OS supports CPPC from OSPM
    //
    if(And(\_SB.OSCP,0x0020)) {
      \_PR.PR01.HWPT()
    }
    //
    // Load the CST SSDTs if:
    //   (1) Driver supports multi-processor configurations
    //
    //   PCxx[3]  = OS supports C1 and P-states in MP systems
    //   PCxx[4]  = OS supports ind. C2/C3 in MP systems
    //
    If(And(PC14,0x0018))
    {
      \_PR.PR01.APCT()
    }

    Store (PC14, PC00)
    Return()
  }
} // End PR14

Scope(\_PR.PR15)
{
  Method(_PDC,1)
  {
    //
    // Call the _PDC for PR00.
    //
    Store(\_PR.PR00.CPDC(Arg0), Local0)
    GCAP(Local0)
  }

  Method(_OSC, 4)
  {
    //
    // Call the _OSC for PR00.
    //
    Store(\_PR.PR00.COSC(Arg0, Arg1, Arg2, Arg3), Local0)
    GCAP(Local0)
    Return (Local0)
  }

  Method(GCAP,1)
  {
    // Point to Status DWORD in the Arg0 buffer (STATUS)
    CreateDWordField(Arg0, 0, ST15)

    // Point to Caps DWORDs of the Arg0 buffer (CAPABILITIES)
    CreateDwordField(Arg0, 4, CP15)

    //
    // If the UUID was unrecognized or the _OSC revision was unsupported,
    // return without updating capabilities.
    //
    If(LOr(LEqual(ST15,0x6),LEqual(ST15,0xA)))
    {
      Return()
    }

    //
    // Check if this is a query (BIT0 of Status = 1).
    // If so, mask off the bits we support and return.
    //
    if (And(ST15, 1))
    {
      And(ST15, 0xBFF, CP15)
      Return()
    }

    //
    // Store result of PDC. (We clear out the MSB, which was just
    // used as a placeholder for the compiler; and then "OR" the
    // value in case we get multiple calls, each of which only
    // reports partial support.)
    //
    Or(And(PC15, 0x7FFFFFFF), CP15, PC15)
    //
    // Attempt to dynamically load the IST SSDTs if:
    //   (1) Driver supports P-States in MP configurations
    //   (2) Driver supports direct HW P-State control
    //
    //   PCxx[3]  = OS supports C1 and P-states in MP systems
    //   PCxx[0]  = OS supports direct access of the perf MSR
    //
    If(LEqual(And(PC15, 0x0009), 0x0009))
    {
      \_PR.PR01.APPT()
    }
    // Load Ap0Hwp SSDT
    // SB.OSC[5]   = OS supports CPPC from OSPM
    //
    if(And(\_SB.OSCP,0x0020)) {
      \_PR.PR01.HWPT()
    }
    //
    // Load the CST SSDTs if:
    //   (1) Driver supports multi-processor configurations
    //
    //   PCxx[3]  = OS supports C1 and P-states in MP systems
    //   PCxx[4]  = OS supports ind. C2/C3 in MP systems
    //
    If(And(PC15,0x0018))
    {
      \_PR.PR01.APCT()
    }

    Store (PC15, PC00)
    Return()
  }
} // End PR15
} // End of Definition Block
