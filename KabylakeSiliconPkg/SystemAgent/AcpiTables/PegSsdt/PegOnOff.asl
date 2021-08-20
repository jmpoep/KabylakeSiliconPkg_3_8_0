/** @file
  This file contains the device definitions of the SystemAgent
  PCIE ACPI Reference Code.

 @copyright
  INTEL CONFIDENTIAL
  Copyright 1999 - 2018 Intel Corporation.

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

#include <PchAccess.h>


//GPE Event handling - Start
Scope(\_GPE) {
  //
  // _L6F Method call for PEG0/1/2 ports to handle 2-tier RTD3 GPE events
  //
  Method(P0L6,0)
  {
    // PEG0 Device Wake Event
    If (\_SB.ISME(P0WK))
    {
      \_SB.SHPO(P0WK, 1)             // set gpio ownership to driver(0=ACPI mode, 1=GPIO mode)
      Notify(\_SB.PCI0.PEG0, 0x02)   // device wake
      \_SB.CAGS(P0WK)                // Clear GPE status bit for PEG0 WAKE
    }
  }

  Method(P1L6,0)
  {
    // PEG1 Device Wake Event
    If (\_SB.ISME(P1WK))
    {
      \_SB.SHPO(P1WK, 1)             // set gpio ownership to driver(0=ACPI mode, 1=GPIO mode)
      Notify(\_SB.PCI0.PEG1, 0x02)   // device wake
      \_SB.CAGS(P1WK)                // Clear GPE status bit for PEG1 WAKE
    }
  }

  Method(P2L6,0)
  {
    // PEG2 Device Wake Event
    If (\_SB.ISME(P2WK))
    {
      \_SB.SHPO(P2WK, 1)             // set gpio ownership to driver(0=ACPI mode, 1=GPIO mode)
      Notify(\_SB.PCI0.PEG2, 0x02)   // device wake
      \_SB.CAGS(P2WK)                // Clear GPE status bit for PEG2 WAKE
    }
  }
} //Scope(\_GPE)

///
/// P.E.G. Root Port D1F0
///
Scope(\_SB.PCI0.PEG0) {
  Name(WKEN, 0)

  OperationRegion(PEGR,PCI_Config,0xC0,0x30)
  Field(PEGR,DWordAcc,NoLock,Preserve) {
    ,16,
    PSTS, 1,     // PME Status
    offset (44),
    GENG, 1,     // General Message GPE Enable
    ,1,          // Reserved
    PMEG, 1,     // PME GPE Enable
  }

  Method(_PRW, 0) { Return(GPRW(0x69, 4)) } // can wakeup from S4 state

  Method(HPME,0,Serialized) {
    //
    // Clear PME status bit
    //
    Store(1,PSTS)
  }
  Method(_PRT,0) {
    If(PICM) { Return(AR02) } // APIC mode
    Return (PR02)             // PIC Mode
  } // end _PRT
  //
  // Pass LTRx to LTRS so SaPcieDsm.asl can be reused for PEGs.
  //
  Method(_INI) {
    Store (LTRX, LTRS)
    Store (OBFX, OBFS)
  }
  include("SaPcieDsm.asl")

  /**-------------------------------------------------------
   Runtime Device Power Management for PEG0 slot - Begin
  -------------------------------------------------------
   Note:
        Runtime Device Power Management can be achieved by using _PRx or _PSx or both

   Name: PG00
   Description: Declare a PowerResource object for PEG0 slot device
  **/

  PowerResource(PG00, 0, 0) {
    Name(_STA, One)
    Method(_ON, 0, Serialized) {
      If(LGreater(OSYS,2009)) {
        PGON(0)
        Store(One, _STA)
      }
    }
    Method(_OFF, 0, Serialized) {
      If(LGreater(OSYS,2009)) {
        PGOF(0)
        Sleep(DLAO)   // KblGContent
        Store(Zero, _STA)
      }
    }
  } //End of PowerResource(PG00, 0, 0)

  Name(_PR0,Package(){PG00})
  Name(_PR2,Package(){PG00})
  Name(_PR3,Package(){PG00})


  ///
  /// This method is used to enable/disable wake from PEG0 (WKEN)
  ///
  Method(_DSW, 3)
  {
    If(Arg1)
    {
      Store(0, WKEN)        /// If entering Sx, need to disable WAKE# from generating runtime PME
    }
    Else
    { /// If Staying in S0
      If(LAnd(Arg0, Arg2))  ///- Check if Exiting D0 and arming for wake
      {
        Store(1, WKEN)      ///- Set PME
      } Else {
        Store(0, WKEN)    ///- Disable runtime PME, either because staying in D0 or disabling wake
      }
    }
  } // End _DSW

  ///
  /// This method is used to change the GPIO ownership back to ACPI and will be called in PEG OFF Method
  ///
  Method(P0EW, 0)
  {
    If(WKEN)
    {
      If(LNotEqual(SGGP, 0x0))
      {
        If(LEqual(SGGP, 0x1))      // GPIO mode
        {
          \_SB.SGOV(P0WK, 0x1)
          \_SB.SHPO(P0WK, 0x0)     // set gpio ownership to ACPI(0=ACPI mode, 1=GPIO mode)
        }
      }
    }
  } // End P0EW

  Method(_S0W, 0) {
    Return(4) //D3cold is supported
  }

  /**-------------------------------------------------------
   Runtime Device Power Management for PEG0 slot - End
  -------------------------------------------------------**/
} // end "P.E.G. Root Port D1F0"

///
/// P.E.G. Port Slot x16
///
Scope(\_SB.PCI0.PEG0.PEGP) {
  OperationRegion(PCIS, PCI_Config, 0x00, 0x100)
  Field(PCIS, AnyAcc, NoLock, Preserve) {
    Offset(0),
    PVID, 16,
    PDID, 16,
  }
  Method(_PRW, 0) { Return(GPRW(0x69, 4)) } // can wakeup from S4 state
} // end "P.E.G. Port Slot x16"

///
/// P.E.G. Root Port D1F1
///
Scope(\_SB.PCI0.PEG1) {
  Name(WKEN, 0)

  OperationRegion(PEGR,PCI_Config,0xC0,0x30)
  Field(PEGR,DWordAcc,NoLock,Preserve) {
    ,16,
    PSTS, 1,     // PME Status
    offset (44),
    GENG, 1,     // General Message GPE Enable
    ,1,          // Reserved
    PMEG, 1,     // PME GPE Enable
  }

  Method(_PRW, 0) { Return(GPRW(0x69, 4)) } // can wakeup from S4 state

  Method(HPME,0,Serialized) {
    //
    // Clear PME status bit
    //
    Store(1,PSTS)
  }
  Method(_PRT,0) {
    If(PICM) { Return(AR0A) }// APIC mode
    Return (PR0A)            // PIC Mode
  } // end _PRT

  Method(_INI) {
    Store (LTRY, LTRS)
    Store (OBFY, OBFS)
  }
  include("SaPcieDsm.asl")

  /**-------------------------------------------------------
   Runtime Device Power Management for PEG1 slot - Begin
     -------------------------------------------------------
   Note:
        Runtime Device Power Management can be achieved by using _PRx or _PSx or both

   Name: PG01
   Description: Declare a PowerResource object for PEG1 slot device
  **/

  PowerResource(PG01, 0, 0) {
    Name(_STA, One)
    Method(_ON, 0, Serialized)
    {
      If(LGreater(OSYS,2009)) {
        PGON(1)
        Store(One, _STA)
      }
    }

    Method(_OFF, 0, Serialized) {
      If(LGreater(OSYS,2009)) {
        PGOF(1)
        Store(Zero, _STA)
      }
    }
  } //End of PowerResource(PG01, 0, 0)


  Name(_PR0,Package(){PG01})
  Name(_PR2,Package(){PG01})
  Name(_PR3,Package(){PG01})


  ///
  /// This method is used to enable/disable wake from PEG1 (WKEN)
  ///
  Method(_DSW, 3)
  {
    If(Arg1)
    {
      Store(0, WKEN)        /// If entering Sx, need to disable WAKE# from generating runtime PME
    }
    Else
    { /// If Staying in S0
      If(LAnd(Arg0, Arg2))  ///- Check if Exiting D0 and arming for wake
      {
        Store(1, WKEN)      ///- Set PME
      } Else {
        Store(0, WKEN)    ///- Disable runtime PME, either because staying in D0 or disabling wake
      }
    }
  } // End _DSW

  ///
  /// This method is used to change the GPIO ownership back to ACPI and will be called in PEG OFF Method
  ///
  Method(P1EW, 0)
  {
    If(WKEN)
    {
      If(LNotEqual(P1GP, 0x0))
      {
        If(LEqual(P1GP, 0x1))      // GPIO mode
        {
          \_SB.SGOV(P1WK, 0x1)
          \_SB.SHPO(P1WK, 0x0)     // set gpio ownership to ACPI(0=ACPI mode, 1=GPIO mode)
        }
      }
    }
  } // End P1EW

  Method(_S0W, 0) {
    Return(4) //D3cold is supported
  }

  /**-------------------------------------------------------
   Runtime Device Power Management for PEG1 slot - End
  -------------------------------------------------------**/
} // end "P.E.G. Root Port D1F1"

///
/// P.E.G. Port Slot x8
///
Scope(\_SB.PCI0.PEG1.PEGP) {
  OperationRegion(PCIS, PCI_Config, 0x00, 0x100)
  Field(PCIS, AnyAcc, NoLock, Preserve) {
    Offset(0),
    PVID, 16,
    PDID, 16,
  }
  Method(_PRW, 0) { Return(GPRW(0x69, 4)) } // can wakeup from S4 state
} // end "P.E.G. Port Slot x8"

///
/// P.E.G. Root Port D1F2
///
Scope(\_SB.PCI0.PEG2) {
  Name(WKEN, 0)

  OperationRegion(PEGR,PCI_Config,0xC0,0x30)
  Field(PEGR,DWordAcc,NoLock,Preserve) {
    ,16,
    PSTS, 1,     // PME Status
    offset (44),
    GENG, 1,     // General Message GPE Enable
    ,1,          // Reserved
    PMEG, 1,     // PME GPE Enable
  }

  Method(_PRW, 0) { Return(GPRW(0x69, 4)) } // can wakeup from S4 state

  Method(HPME,0,Serialized) {
    //
    // Clear PME status bit
    //
    Store(1,PSTS)
  }
  Method(_PRT,0) {
    If(PICM) { Return(AR0B) }// APIC mode
    Return (PR0B) // PIC Mode
  } // end _PRT

  Method(_INI) {
    Store (LTRZ, LTRS)
    Store (OBFZ, OBFS)
  }
  include("SaPcieDsm.asl")

  /**-------------------------------------------------------
   Runtime Device Power Management for PEG2 slot - Begin
     -------------------------------------------------------
   Note:
        Runtime Device Power Management can be achieved by using _PRx or _PSx or both

   Name: PG02
   Description: Declare a PowerResource object for PEG2 slot device
  **/

  PowerResource(PG02, 0, 0) {
    Name(_STA, One)
     Method(_ON, 0, Serialized) {
       If(LGreater(OSYS,2009)) {
         PGON(2)
         Store(One, _STA)
       }
     }
     Method(_OFF, 0, Serialized) {
       If(LGreater(OSYS,2009)) {
         PGOF(2)
         Store(Zero, _STA)
       }
     }
  } //End of PowerResource(PG02, 0, 0)


  Name(_PR0,Package(){PG02})
  Name(_PR2,Package(){PG02})
  Name(_PR3,Package(){PG02})


  ///
  /// This method is used to enable/disable wake from PEG2 (WKEN)
  ///
  Method(_DSW, 3)
  {
    If(Arg1)
    {
      Store(0, WKEN)        /// If entering Sx, need to disable WAKE# from generating runtime PME
    }
    Else
    { /// If Staying in S0
      If(LAnd(Arg0, Arg2))  ///- Check if Exiting D0 and arming for wake
      {
        Store(1, WKEN)      ///- Set PME
      } Else {
        Store(0, WKEN)    ///- Disable runtime PME, either because staying in D0 or disabling wake
      }
    }
  } // End _DSW

  ///
  /// This method is used to change the GPIO ownership back to ACPI and will be called in PEG OFF Method
  ///
  Method(P2EW, 0)
  {
    If(WKEN)
    {
      If(LNotEqual(P2GP, 0x0))
      {
        If(LEqual(P2GP, 0x1))      // GPIO mode
        {
          \_SB.SGOV(P2WK, 0x1)
          \_SB.SHPO(P2WK, 0x0)     // set gpio ownership to ACPI(0=ACPI mode, 1=GPIO mode)
        }
      }
    }
  } // End P2EW


  Method(_S0W, 0) {
    Return(4) //D3cold is supported
  }

  /**-------------------------------------------------------
     Runtime Device Power Management for PEG2 slot - End
  -------------------------------------------------------**/
} // end "P.E.G. Root Port D1F2"

///
/// P.E.G. Port Slot x4
///
Scope(\_SB.PCI0.PEG2.PEGP) {
  OperationRegion(PCIS, PCI_Config, 0x00, 0x100)
  Field(PCIS, AnyAcc, NoLock, Preserve) {
    Offset(0),
    PVID, 16,
    PDID, 16,
  }
  Method(_PRW, 0) { Return(GPRW(0x69, 4)) } // can wakeup from S4 state
} // end "P.E.G. Port Slot x4"


Scope (\_SB.PCI0) {

    Name(HBRB, 0)   //Host bridge bus no
    Name(HBRD, 0)   //Host bridge device no
    Name(HBRF, 0)   //Host bridge function no

    Name(IVID, 0xFFFF) //Invalid Vendor ID

    Name(PEBA, 0) //PCIE base address

    Name(PION, 0) //PEG index for ON Method
    Name(PIOF, 0) //PEG index for OFF Method

    Name(PBUS, 0) //PEG Rootport bus no
    Name(PDEV, 0) //PEG Rootport device no
    Name(PFUN, 0) //PEG Rootport function no

    Name(EBUS, 0) //Endpoint bus no
    Name(EDEV, 0) //Endpoint device no
    Name(EFN0, 0) //Endpoint function no 0
    Name(EFN1, 1) //Endpoint function no 1

    Name(LTRS, 0)
    Name(OBFS, 0)

    //Save-Restore variables
    Name(INDX, 0x0)
    Name(POFF, 0x0)
    Name(PLEN, 0x0)

    Name(VIOF, 0x00) //Vendor ID PCI offset
    Name(DSOF, 0x06) //Device status PCI offset
    Name(CPOF, 0x34) //Capabilities pointer PCI offset
    Name(SBOF, 0x19) //PCI-2-PCI Secondary Bus number

    // PEG0 Endpoint variable to save/restore Link Capability, Link control, Subsytem VendorId and Device Id
    Name (ELC0, 0x00000000)
    Name (ECP0, 0xffffffff)
    Name (H0VI, 0x0000)
    Name (H0DI, 0x0000)

    // PEG1 Endpoint variable to save/restore Link Capability, Link control, Subsytem VendorId and Device Id
    Name (ELC1, 0x00000000)
    Name (ECP1, 0xffffffff)
    Name (H1VI, 0x0000)
    Name (H1DI, 0x0000)

    // PEG2 Endpoint variable to save/restore Link Capability, Link control, Subsytem VendorId and Device Id
    Name (ELC2, 0x00000000)
    Name (ECP2, 0xffffffff)
    Name (H2VI, 0x0000)
    Name (H2DI, 0x0000)

    //One time save variables
    Name(TIDX, 0x0)
    Name(OTSD, 0) //One time save Controller/Endpoint information is done or not
    Name(MXPG, 3) //Max PEG count

    //Bundle power variables
    Name(FBDL, 0x0) //BndlPwrdnFirst
    Name(CBDL, 0x0) //BndlPwrdnCount
    Name(MBDL, 0x0) //MaxBndlPwrdnCount
    Name(HSTR, 0x0) //HwStrap
    Name(LREV, 0x0) //LaneReversal

    //Link waiting timeout variables
    Name(TCNT, 0)
    Name(LDLY, 300) //300 ms


    //
    // Define a Memory Region for PEG0 root port that will allow access to its
    // Register Block.
    //
    OperationRegion(OPG0, SystemMemory, Add(XBAS,0x8000), 0x1000)
    Field(OPG0, AnyAcc,NoLock,Preserve)
    {
      Offset(0),
      P0VI,   16,        //Vendor ID PCI offset
      P0DI,   16,        //Device ID PCI offset
      Offset(0x06),
      DSO0,   16,        //Device status PCI offset
      Offset(0x34),
      CPO0,   8,         //Capabilities pointer PCI offset
//
// KblGBegin
//
      Offset(0xAC),      //LCAP - Link Capabilities
      PMLS,   8,         //Peg Max Link Speed
//
// KblGEnd
//
      Offset(0x0B0),
      ,       4,
      P0LD,   1,         //Link Disable
      PLRT,   1,         //Peg Link Retrain   // KblGContent
      Offset(0x0BC),
      ,       5,
      P0L2,   1,         //L23_Rdy Entry Request for RTD3
      P0L0,   1,         //L23 to Detect Transition for RTD3
//
// KblGBegin
//
      Offset(0xD0),      //Link Control 2
      PTLS,   8,         //PEG Target Link Speed
//
// KblGEnd
//
      Offset(0x11A),
      ,       1,
      P0VC,   1,         //VC0RSTS.VC0NP
      Offset(0x214),
      ,       16,
      P0LS,   4,         //PEGSTS.LKS
      Offset(0x248),
      ,       7,
      Q0L2,   1,         //L23_Rdy Entry Request for RTD3
      Q0L0,   1,         //L23 to Detect Transition for RTD3
      Offset(0x504),
      HST0,  32,
      Offset(0x508),
      P0TR,   1,         //TRNEN.TREN
      Offset(0x91C),
      ,       31,
      BSP1,   1,
      Offset(0x93C),
      ,       31,
      BSP2,   1,
      Offset(0x95C),
      ,       31,
      BSP3,   1,
      Offset(0x97C),
      ,       31,
      BSP4,   1,
      Offset(0x99C),
      ,       31,
      BSP5,   1,
      Offset(0x9BC),
      ,       31,
      BSP6,   1,
      Offset(0x9DC),
      ,       31,
      BSP7,   1,
      Offset(0x9FC),
       ,       31,
      BSP8,   1,
      Offset(0xC20),
      ,       4,
      P0AP,   2,         //AFEOVR.RXSQDETOVR
      Offset(0xC38),
      ,       3,
      P0RM,   1,         //CMNSPARE.PCUNOTL1
      Offset(0xC74),
      P0LT,   4,         //LTSSM_FSM_RESTORE.LTSSM_FSM_PS
      Offset(0xD0C),
      LRV0,  32,
    }

    //
    // Define a Memory Region for Endpoint on PEG0 root port
    //
    OperationRegion (PCS0, SystemMemory, Add(XBAS,ShiftLeft(SBN0,20)), 0xF0)
    Field(PCS0, DWordAcc, Lock, Preserve)
    {
        Offset(0x0),
        D0VI, 16,
        Offset(0x2C),
        S0VI, 16,
        S0DI, 16,
    }

    OperationRegion(CAP0, SystemMemory, Add(Add(XBAS,ShiftLeft(SBN0,20)),EECP),0x14)
    Field(CAP0,DWordAcc, NoLock,Preserve)
    {
        Offset(0x0C),                    // Link Capabilities Register
        LCP0,   32,                      // Link Capabilities Register Data
        Offset(0x10),
        LCT0,   16,                      // Link Control register
    }

    //
    // Define a Memory Region for PEG1 root port that will allow access to its
    // Register Block.
    //
    OperationRegion(OPG1, SystemMemory, Add(XBAS,0x9000), 0x1000)
    Field(OPG1, AnyAcc,NoLock,Preserve)
    {
      Offset(0),
      P1VI,   16,        //Vendor ID PCI offset
      P1DI,   16,        //Device ID PCI offset
      Offset(0x06),
      DSO1,   16,        //Device status PCI offset
      Offset(0x34),
      CPO1,   8,         //Capabilities pointer PCI offset
      Offset(0x0B0),
      ,       4,
      P1LD,   1,         //Link Disable
      Offset(0x0BC),
      ,       5,
      P1L2,   1,         //L23_Rdy Entry Request for RTD3
      P1L0,   1,         //L23 to Detect Transition for RTD3
      Offset(0x11A),
      ,       1,
      P1VC,   1,         //VC0RSTS.VC0NP
      Offset(0x214),
      ,       16,
      P1LS,   4,         //PEGSTS.LKS
      Offset(0x248),
      ,       7,
      Q1L2,   1,         //L23_Rdy Entry Request for RTD3
      Q1L0,   1,         //L23 to Detect Transition for RTD3
      Offset(0x504),
      HST1,  32,
      Offset(0x508),
      P1TR,   1,         //TRNEN.TREN
      Offset(0xC20),
      ,       4,
      P1AP,   2,         //AFEOVR.RXSQDETOVR
      Offset(0xC38),
      ,       3,
      P1RM,   1,         //CMNSPARE.PCUNOTL1
      Offset(0xC74),
      P1LT,   4,         //LTSSM_FSM_RESTORE.LTSSM_FSM_PS
      Offset(0xD0C),
      LRV1,  32,
    }

    //
    // Define a Memory Region for Endpoint on PEG1 root port
    //
    OperationRegion (PCS1, SystemMemory, Add(XBAS,ShiftLeft(SBN1,20)), 0xF0)
    Field(PCS1, DWordAcc, Lock, Preserve)
    {
        Offset(0x0),
        D1VI, 16,
        Offset(0x2C),
        S1VI, 16,
        S1DI, 16,
    }

    OperationRegion(CAP1, SystemMemory, Add(Add(XBAS,ShiftLeft(SBN1,20)),EEC1),0x14)
    Field(CAP1,DWordAcc, NoLock,Preserve)
    {
        Offset(0x0C),    // Link Capabilities Register
        LCP1,   32,      // Link Capabilities Register Data
        Offset(0x10),
        LCT1,   16,      // Link Control register
    }


    //
    // Define a Memory Region for PEG2 root port that will allow access to its
    // Register Block.
    //
    OperationRegion(OPG2, SystemMemory, Add(XBAS,0xA000), 0x1000)
    Field(OPG2, AnyAcc,NoLock,Preserve)
    {
      Offset(0),
      P2VI,   16,        //Vendor ID PCI offset
      P2DI,   16,        //Device ID PCI offset
      Offset(0x06),
      DSO2,   16,        //Device status PCI offset
      Offset(0x34),
      CPO2,   8,         //Capabilities pointer PCI offset
      Offset(0x0B0),
      ,       4,
      P2LD,   1,         //Link Disable
      Offset(0x0BC),
      ,       5,
      P2L2,   1,         //L23_Rdy Entry Request for RTD3
      P2L0,   1,         //L23 to Detect Transition for RTD3
      Offset(0x11A),
      ,       1,
      P2VC,   1,         //VC0RSTS.VC0NP
      Offset(0x214),
      ,       16,
      P2LS,   4,         //PEGSTS.LKS
      Offset(0x248),
      ,       7,
      Q2L2,   1,         //L23_Rdy Entry Request for RTD3
      Q2L0,   1,         //L23 to Detect Transition for RTD3
      Offset(0x504),
      HST2,  32,
      Offset(0x508),
      P2TR,   1,         //TRNEN.TREN
      Offset(0xC20),
      ,       4,
      P2AP,   2,         //AFEOVR.RXSQDETOVR
      Offset(0xC38),
      ,       3,
      P2RM,   1,         //CMNSPARE.PCUNOTL1
      Offset(0xC74),
      P2LT,   4,         //LTSSM_FSM_RESTORE.LTSSM_FSM_PS
      Offset(0xD0C),
      LRV2,  32,
    }

    //
    // Define a Memory Region for Endpoint on PEG2 root port
    //
    OperationRegion (PCS2, SystemMemory, Add(XBAS,ShiftLeft(SBN2,20)), 0xF0)
    Field(PCS2, DWordAcc, Lock, Preserve)
    {
        Offset(0x0),
        D2VI, 16,
        Offset(0x2C),
        S2VI, 16,
        S2DI, 16,
    }

    OperationRegion(CAP2, SystemMemory, Add(Add(XBAS,ShiftLeft(SBN2,20)),EEC2),0x14)
    Field(CAP2,DWordAcc, NoLock,Preserve)
    {
        Offset(0x0C),    // Link Capabilities Register
        LCP2,   32,      // Link Capabilities Register Data
        Offset(0x10),
        LCT2,   16,      // Link Control register
    }

    //
    // Name: PGON
    // Description: Function to put the Pcie Endpoint in ON state
    // Input: Arg0 -> PEG index
    // Return: Nothing
    //
    Method(PGON,1,Serialized)
    {

      Store(Arg0, PION)
      Name(CKON, 0)

      //
      // Check for the GPIO support on PEG0/1/2 Configuration and Return if it is not supported.
      //
      If (LEqual(PION, 0))
      {
        If (LEqual(SGGP, 0x0))
        {
          Return ()
        }
      }
      ElseIf (LEqual(PION, 1))
      {
        If (LEqual(P1GP, 0x0))
        {
          Return ()
        }
      }
      ElseIf (LEqual(PION, 2))
      {
        If (LEqual(P2GP, 0x0))
        {
          Return ()
        }
      }

      Store(\XBAS, PEBA)
      Store(GDEV(PION), PDEV)
      Store(GFUN(PION), PFUN)

      // CLK_REQ   = Mask Enable of Mapped CLKREQ# for CLKOUT_SRC8 (MSKCRQSR)
      Name(SCLK, Package() {
              1,     // 0-disable, 1-enable
              CKON,  // MSKCRQSRC
              0      // assert polarity, ICC should be LOW-activated
            })
      // Assign ClkReq Mask values for PEG 0/1/2
      If (LEqual(Arg0, 0)) //PEG10
      {
        Store(CKM0, Index(SCLK, 1))
      }
      ElseIf (LEqual(Arg0, 1)) //PEG11
      {
        Store(CKM1, Index(SCLK, 1))
      }
      ElseIf (LEqual(Arg0, 2)) //PEG12
      {
        Store(CKM2, Index(SCLK, 1))
      }

      /// de-assert CLK_REQ MSK
      if(LNotEqual(DeRefOf(Index(SCLK, 0)),0)) { // if power gating enabled
        PCRA(PID_ICC,R_PCH_PCR_ICC_MSKCKRQ,Not(DeRefOf(Index(SCLK, 1))))  // And ~SCLK to clear bit
        Sleep(16)
      }

      If (LEqual(CCHK(PION, 1), 0))
      {

        Return ()
      }

      //Power on the Endpoint
      GPPR(PION, 1)

      If (
              LEqual(OSYS,2009)          //OS check for Win7 as it does not support RTD3.
         )
      {

        //PCIe link disable for Switchable GFx

        If (LEqual(PION, 0))
        {
          //Program AFEOVR.RXSQDETOVR : Additional Power savings: Set 0:1:0 0xc20 BIT4 = 0 & BIT5 = 0
          Store (0, P0AP)

          //Activate "robust squelch mechanism"
          Store (0, P0RM)
        }
        ElseIf (LEqual(PION, 1))
        {
          //Program AFEOVR.RXSQDETOVR : Additional Power savings: Set 0:1:0 0xc20 BIT4 = 0 & BIT5 = 0
          Store (0, P1AP)

          //Activate "robust squelch mechanism"
          Store (0, P1RM)
        }
        ElseIf (LEqual(PION, 2))
        {
          //Program AFEOVR.RXSQDETOVR : Additional Power savings: Set 0:1:0 0xc20 BIT4 = 0 & BIT5 = 0
          Store (0, P2AP)

          //Activate "robust squelch mechanism"
          Store (0, P2RM)
        }

        //Program BND*SPARE.BNDL_PWRDN
        //PowerOff unused bundles for PEGs
        If (LNotEqual(PBGE, 0))
        {
          If (SBDL(PION))
          {
            //PowerUpAllBundles
            PUAB(PION)

            //Get BndlPwrdnCount
            Store (GUBC(PION), CBDL) //BndlPwrdnCount

            //Get MaxBndlPwrdnCount
            Store(GMXB(PION), MBDL)

            If (LGreater(CBDL, MBDL))
            {
              Store(MBDL, CBDL)
            }

            //PowerDownUnusedBundles
            PDUB(PION, CBDL)
          }
        }

        If (LEqual(PION, 0))
        {
          //Enable x16 Link: This bit should already be set to 0 in the _Off method. But do it anyway.
          Store (0, P0LD)

          // Enable controller initial training
          Store (1, P0TR)

          // Wait until the VC negotiation is complete
          Store(0, TCNT)
          While(LLess(TCNT, LDLY))
          {
            If(LEqual(P0VC,0))
            {
              Break
            }
            Sleep(16) //In some OS one tick is equal to 1/64 second (15.625ms)
            Add(TCNT, 16, TCNT)
          }
        }
        ElseIf (LEqual(PION, 1))
        {
          //Enable x16 Link: This bit should already be set to 0 in the _Off method. But do it anyway.
          Store (0, P1LD)

          // Enable controller initial training
          Store (1, P1TR)

          // Wait until the VC negotiation is complete
          Store(0, TCNT)
          While(LLess(TCNT, LDLY))
          {
            If(LEqual(P1VC,0))
            {
              Break
            }
            Sleep(16) //In some OS one tick is equal to 1/64 second (15.625ms)
            Add(TCNT, 16, TCNT)
          }
        }
        ElseIf (LEqual(PION, 2))
        {
          //Enable x16 Link: This bit should already be set to 0 in the _Off method. But do it anyway.
          Store (0, P2LD)

          // Enable controller initial training
          Store (1, P2TR)

          // Wait until the VC negotiation is complete
          Store(0, TCNT)
          While(LLess(TCNT, LDLY))
          {
            If(LEqual(P2VC,0))
            {
              Break
            }
            Sleep(16) //In some OS one tick is equal to 1/64 second (15.625ms)
            Add(TCNT, 16, TCNT)
          }
        }
      }
      Else
      {
//
// KblGBegin
//
        // If Gen Speed Change W/A is needed, also use Robust Squelch Exit Mechanism.
        If (LEqual(GSCE, 1))
        {
          If (LEqual(PION, 0))
          {
            //Program AFEOVR.RXSQDETOVR : Additional Power savings: Set 0:1:0 0xc20 BIT4 = 0 & BIT5 = 0
            Store (0, P0AP)

            //Activate "robust squelch mechanism"
            Store (0, P0RM)
          }
          ElseIf (LEqual(PION, 1))
          {
            //Program AFEOVR.RXSQDETOVR : Additional Power savings: Set 0:1:0 0xc20 BIT4 = 0 & BIT5 = 0
            Store (0, P1AP)

            //Activate "robust squelch mechanism"
            Store (0, P1RM)
          }
          ElseIf (LEqual(PION, 2))
          {
            //Program AFEOVR.RXSQDETOVR : Additional Power savings: Set 0:1:0 0xc20 BIT4 = 0 & BIT5 = 0
            Store (0, P2AP)

            //Activate "robust squelch mechanism"
            Store (0, P2RM)
          }
        }
//
// KblGEnd
//
        LKEN(PION)  //Link Enable for RTD3
        CLSP(0x3)   //Set target link speed to Gen3   // KblGContent
      }

      // Re-store the DGPU Subsystem VendorID, DeviceID & Link control register data
      If (LEqual(PION, 0))
      {
        Store(H0VI, S0VI)
        Store(H0DI, S0DI)
        Or(And(ELC0,0x0043),And(LCT0,0xFFBC),LCT0)
      }
      ElseIf (LEqual(PION, 1))
      {
        Store(H1VI, S1VI)
        Store(H1DI, S1DI)
        Or(And(ELC1,0x0043),And(LCT1,0xFFBC),LCT1)
      }
      ElseIf (LEqual(PION, 2))
      {
        Store(H2VI, S2VI)
        Store(H2DI, S2DI)
        Or(And(ELC2,0x0043),And(LCT2,0xFFBC),LCT2)
      }

      Return ()
    } // End of Method(PGON,1,Serialized)

    //
    // Name: PGOF
    // Description: Function to put the Pcie Endpoint in OFF state
    // Input: Arg0 -> PEG index
    // Return: Nothing
    //
    Method(PGOF,1,Serialized)
    {

      Store(Arg0, PIOF)
      Name(CKOF,0)
      //
      // Check for the GPIO support on PEG0/1/2 Configuration and Return if it is not supported.
      //
      If (LEqual(PIOF, 0))
      {
        If (LEqual(SGGP, 0x0))
        {
          Return ()
        }
      }
      ElseIf (LEqual(PIOF, 1))
      {
        If (LEqual(P1GP, 0x0))
        {
          Return ()
        }
      }
      ElseIf (LEqual(PIOF, 2))
      {
        If (LEqual(P2GP, 0x0))
        {
          Return ()
        }
      }

      Store(\XBAS, PEBA)
      Store(GDEV(PIOF), PDEV)
      Store(GFUN(PIOF), PFUN)

      // CLK_REQ   = Mask Enable of Mapped CLKREQ# for CLKOUT_SRC8 (MSKCRQSRC)
      Name(SCLK, Package() {
              1,     // 0-disable, 1-enable
              CKOF,  // MSKCRQSRC
              0      // assert polarity, ICC should be LOW-activated
            })

      If (LEqual(CCHK(PIOF, 0), 0))
      {

        Return ()
      }

      // Save Endpoint Link Control register, Subsystem VendorID & Device ID, Link capability Data
      // and ClkReq Mask Value
      If (LEqual(Arg0, 0)) //PEG10
      {
        Store(LCT0, ELC0)
        Store(S0VI, H0VI)
        Store(S0DI, H0DI)
        Store(LCP0, ECP0)
        Store(CKM0, Index(SCLK, 1))
      }
      ElseIf (LEqual(Arg0, 1)) //PEG11
      {
        Store(LCT1, ELC1)
        Store(S1VI, H1VI)
        Store(S1DI, H1DI)
        Store(LCP1, ECP1)
        Store(CKM1, Index(SCLK, 1))
      }
      ElseIf (LEqual(Arg0, 2)) //PEG12
      {
        Store(LCT2, ELC2)
        Store(S2VI, H2VI)
        Store(S2DI, H2DI)
        Store(LCP2, ECP2)
        Store(CKM2, Index(SCLK, 1))
      }

      If (
              LEqual(OSYS,2009)          //OS check for Win7 as it does not support RTD3.
         )
      {

        If (LEqual(PIOF, 0))
        {
          //Force disable the x16 link
          Store (1, P0LD)

          //Poll LTSSM until it is disabled = 1000b
          Store(0, TCNT)
          While(LLess(TCNT, LDLY))
          {
            If(LEqual(P0LT,8))
            {
              Break
            }
            Sleep(16) //In some OS one tick is equal to 1/64 second (15.625ms)
            Add(TCNT, 16, TCNT)
          }

          //override "robust squelch mechanism"
          Store (1, P0RM)

          //Program AFEOVR.RXSQDETOVR: Set 0:1:0 0xc20 BIT4 = 1 & BIT5 = 1: 11 = Squelch detector output overridden to 1
          Store (3, P0AP)

        }
        ElseIf (LEqual(PIOF, 1))
        {
          //Force disable the x16 link
          Store (1, P1LD)

          //Poll LTSSM until it is disabled = 1000b
          Store(0, TCNT)
          While(LLess(TCNT, LDLY))
          {
            If(LEqual(P1LT,8))
            {
              Break
            }
            Sleep(16) //In some OS one tick is equal to 1/64 second (15.625ms)
            Add(TCNT, 16, TCNT)
          }

          //override "robust squelch mechanism"
          Store (1, P1RM)

          //Program AFEOVR.RXSQDETOVR: Set 0:1:0 0xc20 BIT4 = 1 & BIT5 = 1: 11 = Squelch detector output overridden to 1
          Store (3, P1AP)
        }
        ElseIf (LEqual(PIOF, 2))
        {
          //Force disable the x16 link
          Store (1, P2LD)

          //Poll LTSSM until it is disabled = 1000b
          Store(0, TCNT)
          While(LLess(TCNT, LDLY))
          {
            If(LEqual(P2LT,8))
            {
              Break
            }
            Sleep(16) //In some OS one tick is equal to 1/64 second (15.625ms)
            Add(TCNT, 16, TCNT)
          }

          //override "robust squelch mechanism"
          Store (1, P2RM)

          //Program AFEOVR.RXSQDETOVR: Set 0:1:0 0xc20 BIT4 = 1 & BIT5 = 1: 11 = Squelch detector output overridden to 1
          Store (3, P2AP)
        }

        // PowerOff all bundles for PEGs
        // Program BND*SPARE.BNDL_PWRDN
        If (LNotEqual(PBGE, 0))
        {
          If (SBDL(PIOF))
          {
            //Get MaxBndlPwrdnCount
            Store(GMXB(PIOF), MBDL)

            //PowerDownUnusedBundles
            PDUB(PIOF, MBDL)
          }
        }

      }
      Else
      {
        CLSP(0x1)   // Set target link speed to Gen1   // KblGContent
        LKDS(PIOF)  // Link Disable for RTD3
//
// KblGBegin
//
        // If Gen Speed Change W/A is needed, also use Robust Squelch Exit Mechanism.
        If (LEqual(GSCE, 1))
        {
          If (LEqual(PIOF, 0))
          {
            //override "robust squelch mechanism"
            Store (1, P0RM)

            //Program AFEOVR.RXSQDETOVR: Set 0:1:0 0xc20 BIT4 = 1 & BIT5 = 1: 11 = Squelch detector output overridden to 1
            Store (3, P0AP)
          }
          ElseIf (LEqual(PIOF, 1))
          {
            //override "robust squelch mechanism"
            Store (1, P1RM)

            //Program AFEOVR.RXSQDETOVR: Set 0:1:0 0xc20 BIT4 = 1 & BIT5 = 1: 11 = Squelch detector output overridden to 1
            Store (3, P1AP)
          }
          ElseIf (LEqual(PIOF, 2))
          {
            //override "robust squelch mechanism"
            Store (1, P2RM)

            //Program AFEOVR.RXSQDETOVR: Set 0:1:0 0xc20 BIT4 = 1 & BIT5 = 1: 11 = Squelch detector output overridden to 1
            Store (3, P2AP)
          }
        }
//
// KblGEnd
//
      }

      /// assert CLK_REQ MSK
      if(LNotEqual(DeRefOf(Index(SCLK, 0)),0)) { // if power gating enabled
        PCRO(PID_ICC,R_PCH_PCR_ICC_MSKCKRQ,DeRefOf(Index(SCLK, 1)))    // Or SCLK to set bit
        Sleep(16)
      }

      //Power-off the Endpoint
      GPPR(PIOF, 0)

      If (
              LNotEqual(OSYS,2009)          //OS check for Win7 as it does not support RTD3.
         )
      {
        //Method to set Wake GPIO ownership from GPIO to ACPI for Device Initiated RTD3
        DIWK(PIOF)
      }

      Return ()
    } // End of Method(PGOF,1,Serialized)


    //
    // Name: MMRB
    // Description: Function to read a Byte from PCIE-MMIO
    // Input: Arg0 -> PCIE base address
    //        Arg1 -> Bus
    //        Arg2 -> Device
    //        Arg3 -> Function
    //        Arg4 -> Register offset
    // Return: Byte data read from PCIE-MMIO
    //
    Method(MMRB,5)
    {
      Store(Arg0, Local7)
      Or(Local7, ShiftLeft(Arg1, 20), Local7)
      Or(Local7, ShiftLeft(Arg2, 15), Local7)
      Or(Local7, ShiftLeft(Arg3, 12), Local7)
      Or(Local7, Arg4, Local7)

      OperationRegion(PCI0, SystemMemory, Local7, 1)
      Field(PCI0, ByteAcc,NoLock,Preserve)
      {
        TEMP, 8
      }


      Return(TEMP)
    } // End of Method(MMRB,5)

    //
    // Name: MMWB
    // Description: Function to write a Byte into PCIE-MMIO
    // Input: Arg0 -> PCIE base address
    //        Arg1 -> Bus
    //        Arg2 -> Device
    //        Arg3 -> Function
    //        Arg4 -> Register offset
    //        Arg5 -> Data
    // Return: Nothing
    //
    Method(MMWB,6)
    {
      Store(Arg0, Local7)
      Or(Local7, ShiftLeft(Arg1, 20), Local7)
      Or(Local7, ShiftLeft(Arg2, 15), Local7)
      Or(Local7, ShiftLeft(Arg3, 12), Local7)
      Or(Local7, Arg4, Local7)

      OperationRegion(PCI0, SystemMemory, Local7, 1)
      Field(PCI0, ByteAcc,NoLock,Preserve)
      {
        TEMP, 8
      }


      Store(Arg5,TEMP)
    } // End of Method(MMWB,6)

    //
    // Name: MMRW
    // Description: Function to read a Word from PCIE-MMIO
    // Input: Arg0 -> PCIE base address
    //        Arg1 -> Bus
    //        Arg2 -> Device
    //        Arg3 -> Function
    //        Arg4 -> Register offset
    // Return: Word data read from PCIE-MMIO
    //
    Method(MMRW,5)
    {
      Store(Arg0, Local7)
      Or(Local7, ShiftLeft(Arg1, 20), Local7)
      Or(Local7, ShiftLeft(Arg2, 15), Local7)
      Or(Local7, ShiftLeft(Arg3, 12), Local7)
      Or(Local7, Arg4, Local7)

      OperationRegion(PCI0, SystemMemory, Local7, 2)
      Field(PCI0, ByteAcc,NoLock,Preserve)
      {
        TEMP, 16
      }


      Return(TEMP)
    } // End of Method(MMRW,5)

    //
    // Name: MMWW
    // Description: Function to write a Word into PCIE-MMIO
    // Input: Arg0 -> PCIE base address
    //        Arg1 -> Bus
    //        Arg2 -> Device
    //        Arg3 -> Function
    //        Arg4 -> Register offset
    //        Arg5 -> Data
    // Return: Nothing
    //
    Method(MMWW,6)
    {
      Store(Arg0, Local7)
      Or(Local7, ShiftLeft(Arg1, 20), Local7)
      Or(Local7, ShiftLeft(Arg2, 15), Local7)
      Or(Local7, ShiftLeft(Arg3, 12), Local7)
      Or(Local7, Arg4, Local7)

      OperationRegion(PCI0, SystemMemory, Local7, 2)
      Field(PCI0, ByteAcc,NoLock,Preserve)
      {
        TEMP, 16
      }


      Store(Arg5,TEMP)
    } // End of Method(MMWW,6)

    //
    // Name: MMRD
    // Description: Function to read a Dword from PCIE-MMIO
    // Input: Arg0 -> PCIE base address
    //        Arg1 -> Bus
    //        Arg2 -> Device
    //        Arg3 -> Function
    //        Arg4 -> Register offset
    // Return: Dword data read from PCIE-MMIO
    //
    Method(MMRD,5)
    {
      Store(Arg0, Local7)
      Or(Local7, ShiftLeft(Arg1, 20), Local7)
      Or(Local7, ShiftLeft(Arg2, 15), Local7)
      Or(Local7, ShiftLeft(Arg3, 12), Local7)
      Or(Local7, Arg4, Local7)

      OperationRegion(PCI0, SystemMemory, Local7, 4)
      Field(PCI0, ByteAcc,NoLock,Preserve)
      {
        TEMP, 32
      }


      Return(TEMP)
    } // End of Method(MMRD,5)

    //
    // Name: MMWD
    // Description: Function to write a Dword into PCIE-MMIO
    // Input: Arg0 -> PCIE base address
    //        Arg1 -> Bus
    //        Arg2 -> Device
    //        Arg3 -> Function
    //        Arg4 -> Register offset
    //        Arg5 -> Data
    // Return: Nothing
    //
    Method(MMWD,6)
    {
      Store(Arg0, Local7)
      Or(Local7, ShiftLeft(Arg1, 20), Local7)
      Or(Local7, ShiftLeft(Arg2, 15), Local7)
      Or(Local7, ShiftLeft(Arg3, 12), Local7)
      Or(Local7, Arg4, Local7)

      OperationRegion(PCI0, SystemMemory, Local7, 4)
      Field(PCI0, ByteAcc,NoLock,Preserve)
      {
        TEMP, 32
      }


      Store(Arg5,TEMP)
    } // End of Method(MMWD,6)

    //
    // Name: GULC
    // Description: Function to determine the Unused lanes
    //              To determine how many lanes we can shut-off to save power.
    //              For eg: if x4 card is plugged in x16 slot [16-4=12] we can shut-off 12 lanes to save power
    // Input: Arg0 -> Endpoint's Link Capabilities Register
    // Return: Number of lanes that is not used & can be shut-off to save power
    //
    Method(GULC,1)
    {
      Store(MMRD(PEBA, PBUS, PDEV, PFUN, 0x0AC), Local7)
      ShiftRight(Local7, 4, Local7)
      And(Local7,0x3F,Local7)

      Store(Arg0, Local6)
      ShiftRight(Local6, 4, Local6)
      And(Local6,0x3F,Local6)

      //Local7: PEG Controller's Maximum Link Width [LCAP.MLW]
      //Local6: Endpoint's Maximum Link Width
      If (LGreater(Local7, Local6))
      {
        Subtract (Local7, Local6, Local0)
      }
      Else
      {
        Store (0, Local0)
      }


      Return(Local0) //Unused lanes count
    } // End of Method(GULC,1)

    //
    // Name: GMXB
    // Description: Function to determine the max bundles supported in a given PEG controller
    //              For eg: x16 slot has 16 lanes [16/2 = 8 bundles]
    // Input: Arg0 -> PEG index
    // Return: Max bundles supported for the given PEG controller
    //
    Method(GMXB,1)
    {
      //HSTR: HwStrap [FUSESCMN.PEG1CFGSEL]
      If (LEqual(Arg0, 0))  {
        Store(HST0, HSTR)
      }
      ElseIf(LEqual(Arg0, 1)) {
        Store(HST1, HSTR)
      }
      ElseIf(LEqual(Arg0, 2)) {
        Store(HST2, HSTR)
      }

      ShiftRight(HSTR, 16, HSTR)
      And(HSTR, 0x3, HSTR)

      If (LEqual(Arg0, 0)) //PEG10
      {
        If (LEqual(HSTR, 3)) //SA_PEG_x16_x0_x0
        {
          Store (8, Local0)
        }
        Else
        {
          Store (4, Local0)
        }
      }
      ElseIf (LEqual(Arg0, 1)) //PEG11
      {
        If (LEqual(HSTR, 2)) //SA_PEG_x8_x8_x0
        {
          Store (4, Local0)
        }
        ElseIf (LEqual(HSTR, 0)) //SA_PEG_x8_x4_x4
        {
          Store (2, Local0)
        }
      }
      ElseIf (LEqual(Arg0, 2)) //PEG12
      {
        If (LEqual(HSTR, 0)) //SA_PEG_x8_x4_x4
        {
          Store (2, Local0)
        }
      }


      Return(Local0)
    } // End of Method(GMXB,1)

    //
    // Name: PUAB
    // Description: Function to Power Up all the bundles in a given PEG controller
    //              During _OFF call bundles will be powered down
    //              During _ON call bundles needs to be powered up
    // Input: Arg0 -> PEG index
    // Return: Nothing
    //
    Method(PUAB,1)
    {
      Store (0, FBDL) //BndlPwrdnFirst
      Store (0, CBDL) //BndlPwrdnCount

      //HSTR: HwStrap [FUSESCMN.PEG1CFGSEL]
      //LREV: LaneReversal [PEGTST.LANEREVSTS]
      If (LEqual(Arg0, 0))  {
        Store(HST0, HSTR)
        Store(LRV0, LREV)
      }
      ElseIf(LEqual(Arg0, 1)) {
        Store(HST1, HSTR)
        Store(LRV1, LREV)
      }
      ElseIf(LEqual(Arg0, 2)) {
        Store(HST2, HSTR)
        Store(LRV2, LREV)
      }

      ShiftRight(HSTR, 16, HSTR)
      And(HSTR, 0x3, HSTR)

      ShiftRight(LREV, 20, LREV)
      And(LREV, 0x1, LREV)

      If (LEqual(Arg0, 0)) //PEG10
      {
        If (LEqual(HSTR, 3)) //SA_PEG_x16_x0_x0
        {
          Store (0, FBDL)
          Store (8, CBDL)
        }
        Else
        {
          If(LEqual(LREV,0))
          {
            Store (0, FBDL)
            Store (4, CBDL)
          }
          Else
          {
            Store (4, FBDL)
            Store (4, CBDL)
          }
        }
      }
      ElseIf (LEqual(Arg0, 1)) //PEG11
      {
        If (LEqual(HSTR, 2)) //SA_PEG_x8_x8_x0
        {
          If(LEqual(LREV,0))
          {
            Store (4, FBDL)
            Store (4, CBDL)
          }
          Else
          {
            Store (0, FBDL)
            Store (4, CBDL)
          }
        }
        ElseIf (LEqual(HSTR, 0)) //SA_PEG_x8_x4_x4
        {
          If(LEqual(LREV,0))
          {
            Store (4, FBDL)
            Store (2, CBDL)
          }
          Else
          {
            Store (2, FBDL)
            Store (2, CBDL)
          }
        }
      }
      ElseIf (LEqual(Arg0, 2)) //PEG12
      {
        If (LEqual(HSTR, 0)) //SA_PEG_x8_x4_x4
        {
          If(LEqual(LREV,0))
          {
            Store (6, FBDL)
            Store (2, CBDL)
          }
          Else
          {
            Store (0, FBDL)
            Store (2, CBDL)
          }
        }
      }


      Store (1, INDX)
      If (LNotEqual(CBDL,0))
      {
        While(LLessEqual(INDX, CBDL))
        {
          If(LEqual(P0VI, IVID))
          {
          }
          ElseIf(LNotEqual(P0VI, IVID))
          {
            If(LEqual(FBDL,0))
            {
              Store (0, BSP1)
            }
            If(LEqual(FBDL,1))
            {
              Store (0, BSP2)
            }
            If(LEqual(FBDL,2))
            {
              Store (0, BSP3)
            }
            If(LEqual(FBDL,3))
            {
              Store (0, BSP4)
            }
            If(LEqual(FBDL,4))
            {
              Store (0, BSP5)
            }
            If(LEqual(FBDL,5))
            {
              Store (0, BSP6)
            }
            If(LEqual(FBDL,6))
            {
              Store (0, BSP7)
            }
            If(LEqual(FBDL,7))
            {
              Store (0, BSP8)
            }
          }
          Increment (FBDL)
          Increment (INDX)
        }
      }
    } // End of Method(PUAB,1)

    //
    // Name: PDUB
    // Description: Function to Power Down the unused bundles in a given PEG controller
    //              During _OFF call bundles will be powered down
    //              During _ON call bundles needs to be powered up [switch off only the unused bundles]
    // Input: Arg0 -> PEG index
    //        Arg1 -> BndlPwrdnCount
    // Return: Nothing
    //
    Method(PDUB,2)
    {
      Store (0, FBDL) //BndlPwrdnFirst
      Store (Arg1, CBDL) //BndlPwrdnCount

      If (LEqual(CBDL,0))
      {
        // All lanes are used. Do nothing
        Return ()
      }

      //HSTR: HwStrap [FUSESCMN.PEG1CFGSEL]
      //LREV: LaneReversal [PEGTST.LANEREVSTS]
      If (LEqual(Arg0, 0))  {
        Store(HST0, HSTR)
        Store(LRV0, LREV)
      }
      ElseIf(LEqual(Arg0, 1)) {
        Store(HST1, HSTR)
        Store(LRV1, LREV)
      }
      ElseIf(LEqual(Arg0, 2)) {
        Store(HST2, HSTR)
        Store(LRV2, LREV)
      }

      ShiftRight(HSTR, 16, HSTR)
      And(HSTR, 0x3, HSTR)

      ShiftRight(LREV, 20, LREV)
      And(LREV, 0x1, LREV)

      If (LEqual(Arg0, 0)) //PEG10
      {
        If (LEqual(HSTR, 3)) //SA_PEG_x16_x0_x0
        {
          If(LEqual(LREV,0))
          {
            Store (Subtract(8, CBDL), FBDL) //8 - (UnusedLanes / 2)
          }
          Else
          {
            Store (0, FBDL)
          }
        }
        Else
        {
          If(LEqual(LREV,0))
          {
            Store (Subtract(4, CBDL), FBDL) //4 - (UnusedLanes / 2)
          }
          Else
          {
            Store (4, FBDL)
          }
        }
      }
      ElseIf (LEqual(Arg0, 1)) //PEG11
      {
        If (LEqual(HSTR, 2)) //SA_PEG_x8_x8_x0
        {
          If(LEqual(LREV,0))
          {
            Store (Subtract(8, CBDL), FBDL) //8 - (UnusedLanes / 2)
          }
          Else
          {
            Store (0, FBDL)
          }
        }
        ElseIf (LEqual(HSTR, 0)) //SA_PEG_x8_x4_x4
        {
          If(LEqual(LREV,0))
          {
            Store (Subtract(6, CBDL), FBDL) //6 - (UnusedLanes / 2)
          }
          Else
          {
            Store (2, FBDL)
          }
        }
      }
      ElseIf (LEqual(Arg0, 2)) //PEG12
      {
        If (LEqual(HSTR, 0)) //SA_PEG_x8_x4_x4
        {
          If(LEqual(LREV,0))
          {
            Store (Subtract(8, CBDL), FBDL) //8 - (UnusedLanes / 2)
          }
          Else
          {
            Store (0, FBDL)
          }
        }
      }


      Store (1, INDX)
      While(LLessEqual(INDX, CBDL)) //< Check that bundles need to be powered down
      {
        If(LEqual(P0VI, IVID))
        {
        }
        ElseIf(LNotEqual(P0VI, IVID))
        {
          If(LEqual(FBDL,0))
          {
            Store (1, BSP1)
          }
          If(LEqual(FBDL,1))
          {
            Store (1, BSP2)
          }
          If(LEqual(FBDL,2))
          {
            Store (1, BSP3)
          }
          If(LEqual(FBDL,3))
          {
            Store (1, BSP4)
          }
          If(LEqual(FBDL,4))
          {
            Store (1, BSP5)
          }
          If(LEqual(FBDL,5))
          {
            Store (1, BSP6)
          }
          If(LEqual(FBDL,6))
          {
            Store (1, BSP7)
          }
          If(LEqual(FBDL,7))
          {
            Store (1, BSP8)
          }
        }
        Increment (FBDL)
        Increment (INDX)
      }
    } // End of Method(PDUB,2)

    //
    // Name: SBDL
    // Description: Function to check whether Bundle power down is enabled in setup or not
    // Input: Arg0 -> PEG index
    // Return: 0 - Disabled, 1 - Enabled
    //
    Method(SBDL,1)
    {

      If (LEqual(Arg0, 0))
      {
        If (LEqual(P0UB, 0x00))
        {

          Return(0)
        }
      }
      ElseIf (LEqual(Arg0, 1))
      {
        If (LEqual(P1UB, 0x00))
        {

          Return(0)
        }
      }
      ElseIf (LEqual(Arg0, 2))
      {
        If (LEqual(P2UB, 0x00))
        {

          Return(0)
        }
      }
      Else
      {

        Return(0)
      }


      Return(1)
    } // End of Method(SBDL,1)


    //
    // Name: GUBC
    // Description: Function to determine the Unused bundles
    //              To determine how many bundles we can shut-off to save power.
    //              For eg: if x4 card is plugged in x16 slot [16-4=12] we can shut-off 12/2=6 bundles to save power
    // Input: Arg0 -> PEG index
    // Return: Number of bundles that is not used & can be shut-off to save power
    //
    Method(GUBC,1)
    {
      //Local7: Unused bundle count
      //Local6: Endpoint's Link Capabilities Register data
      Store(0, Local7)

      //Re-store the Endpoint's Link Capabilities Register data
      If (LEqual(Arg0, 0))
      {
        Store(LCP0, Local6)
      }
      ElseIf (LEqual(Arg0, 1))
      {
        Store(LCP1, Local6)
      }
      ElseIf (LEqual(Arg0, 2))
      {
        Store(LCP2, Local6)
      }

      If (LEqual(Arg0, 0))
      {
        If (LEqual(P0UB, 0xFF)) //AUTO
        {
          Store (GULC(Local6), Local5) //UnusedLanes
          Store (Divide(Local5,2), Local7) //BndlPwrdnCount
        }
        ElseIf (LNotEqual (P0UB, 0x00)) //1...8 bundles
        {
          Store (P0UB, Local7) //BndlPwrdnCount
        }
      }
      ElseIf (LEqual(Arg0, 1))
      {
        If (LEqual(P1UB, 0xFF)) //AUTO
        {
          Store (GULC(Local6), Local5) //UnusedLanes
          Store (Divide(Local5,2), Local7) //BndlPwrdnCount
        }
        ElseIf (LNotEqual (P1UB, 0x00)) //1...8 bundles
        {
          Store (P1UB, Local7) //BndlPwrdnCount
        }
      }
      ElseIf (LEqual(Arg0, 2))
      {
        If (LEqual(P2UB, 0xFF)) //AUTO
        {
          Store (GULC(Local6), Local5) //UnusedLanes
          Store (Divide(Local5,2), Local7) //BndlPwrdnCount
        }
        ElseIf (LNotEqual (P2UB, 0x00)) //1...8 bundles
        {
          Store (P2UB, Local7) //BndlPwrdnCount
        }
      }


      Return(Local7) //Unused bundles count
    } // End of Method(GUBC,1)

    //
    // Name: LKEN
    // Description: Function to Enable the link for RTD3 [RCTL.L22DT]
    // Input: PEG Index
    // Return: Nothing
    //
    Method(LKEN,1)
    {
      // Get the CPU stepping
      And(CPEX, 0x0000000F, Local3)

      //
      // Check for P0 Stepping
      //
      If (LEqual(Local3, 0))
      {
        If (LEqual(Arg0, 0))
        {
          Store(1, P0L0) /// Set L23_Rdy to Detect Transition  (L23R2DT)
          Sleep(16)
          Store(0, Local0)
          /// Wait up to 12 ms for transition to Detect
          While(P0L0) {
            If(Lgreater(Local0, 4))
            {
              Break
            }
            Sleep(16)
            Increment(Local0)
          }
        }
        ElseIf (LEqual(Arg0, 1))
        {
          Store(1, P1L0) /// Set L23_Rdy to Detect Transition  (L23R2DT)
          Sleep(16)
          Store(0, Local0)
          /// Wait up to 12 ms for transition to Detect
          While(P1L0) {
            If(Lgreater(Local0, 4))
            {
              Break
            }
            Sleep(16)
            Increment(Local0)
          }
        }
        ElseIf (LEqual(Arg0, 2))
        {
          Store(1, P2L0) /// Set L23_Rdy to Detect Transition  (L23R2DT)
          Sleep(16)
          Store(0, Local0)
          /// Wait up to 12 ms for transition to Detect
          While(P2L0) {
            If(Lgreater(Local0, 4))
            {
              Break
            }
            Sleep(16)
            Increment(Local0)
          }
        }
      }
      //
      // Check if not a P0 Stepping
      //
      ElseIf (LNotEqual (Local3, 0))
      {
        If (LEqual(Arg0, 0))
        {
          Store(1, Q0L0) /// Set L23_Rdy to Detect Transition  (L23R2DT)
          Sleep(16)
          Store(0, Local0)
          /// Wait up to 12 ms for transition to Detect
          While(Q0L0) {
            If(Lgreater(Local0, 4))
            {
              Break
            }
            Sleep(16)
            Increment(Local0)
          }
        }
        ElseIf (LEqual(Arg0, 1))
        {
          Store(1, Q1L0) /// Set L23_Rdy to Detect Transition  (L23R2DT)
          Sleep(16)
          Store(0, Local0)
          /// Wait up to 12 ms for transition to Detect
          While(Q1L0) {
            If(Lgreater(Local0, 4))
            {
              Break
            }
            Sleep(16)
            Increment(Local0)
          }
        }
        ElseIf (LEqual(Arg0, 2))
        {
          Store(1, Q2L0) /// Set L23_Rdy to Detect Transition  (L23R2DT)
          Sleep(16)
          Store(0, Local0)
          /// Wait up to 12 ms for transition to Detect
          While(Q2L0) {
            If(Lgreater(Local0, 4))
            {
              Break
            }
            Sleep(16)
            Increment(Local0)
          }
        }
      }

      Sleep(DLAL)   // KblGContent
    } // End of Method(LKEN,1)

    //
    // Name: LKDS
    // Description: Function to Disable link for RTD3 [RCTL.L23ER]
    // Input: PEG Index
    // Return: Nothing
    //
    Method(LKDS,1)
    {
      // Get the CPU stepping
      And(CPEX, 0x0000000F, Local3)

      //
      // Check for P0 Stepping
      //
      If (LEqual(Local3, 0))
      {
        If (LEqual(Arg0, 0))
        {
          /// Set L23_Rdy Entry Request (L23ER)
          Store(1, P0L2)
          Sleep(16)
          Store(0, Local0)
          While(P0L2) {
            If(Lgreater(Local0, 4))
            {
              Break
            }
            Sleep(16)
            Increment(Local0)
          }
        }
        ElseIf (LEqual(Arg0, 1))
        {
          /// Set L23_Rdy Entry Request (L23ER)
          Store(1, P1L2)
          Sleep(16)
          Store(0, Local0)
          While(P1L2) {
            If(Lgreater(Local0, 4))
            {
              Break
            }
            Sleep(16)
            Increment(Local0)
          }
        }
        ElseIf (LEqual(Arg0, 2))
        {
          /// Set L23_Rdy Entry Request (L23ER)
          Store(1, P2L2)
          Sleep(16)
          Store(0, Local0)
          While(P2L2) {
            If(Lgreater(Local0, 4))
            {
              Break
            }
            Sleep(16)
            Increment(Local0)
          }
        }
      }
      //
      // Check if not a P0 Stepping
      //
      ElseIf (LNotEqual (Local3, 0))
      {
        If (LEqual(Arg0, 0))
        {
          /// Set L23_Rdy Entry Request (L23ER)
          Store(1, Q0L2)
          Sleep(16)
          Store(0, Local0)
          While(Q0L2) {
            If(Lgreater(Local0, 4))
            {
              Break
            }
            Sleep(16)
            Increment(Local0)
          }
        }
        ElseIf (LEqual(Arg0, 1))
        {
          /// Set L23_Rdy Entry Request (L23ER)
          Store(1, Q1L2)
          Sleep(16)
          Store(0, Local0)
          While(Q1L2) {
            If(Lgreater(Local0, 4))
            {
              Break
            }
            Sleep(16)
            Increment(Local0)
          }
        }
        ElseIf (LEqual(Arg0, 2))
        {
          /// Set L23_Rdy Entry Request (L23ER)
          Store(1, Q2L2)
          Sleep(16)
          Store(0, Local0)
          While(Q2L2) {
            If(Lgreater(Local0, 4))
            {
              Break
            }
            Sleep(16)
            Increment(Local0)
          }
        }
      }

    } // End of Method(LNKD,1)

//
// KblGBegin
//
    //
    // Name: CLSP
    // Description: Function to change the link speed
    // Input: Target Speed Gen
    // Return: Nothing
    //
    Method(CLSP,1,Serialized)
    // Change Link Speed
    {
      // Check if Gen Speed Changes are Enabled, if not return
      If (LEqual(GSCE, 0))
      {
        Return()
      }
      // If Target Speed is not Gen1, Gen2, or Gen3 exit the function
      If (LAnd(LNotEqual(Arg0, 1),
          LAnd(LNotEqual(Arg0, 2),
          LNotEqual(Arg0, 3))))
      {
        Return()
      }
      // Max Link Speed PMLS[3:0]
      Store(PMLS, Local0)
      And(Local0, 0xF0, Local0)
      Or(Local0, Arg0, Local0)
      Store(Local0, PMLS)
    
      // Target Link Speed PTLS[3:0]
      Store(PTLS, Local0)
      And(Local0, 0xF0, Local0)
      Or(Local0, Arg0, Local0)
      Store(Local0, PTLS)
    
      // Force Link Re-Train
      Store(0x1, PLRT)
    }
//
// KblGEnd
//
    //
    // Name: DIWK
    // Description: Function which set the GPIO ownership to ACPI for device initiated RTD3
    // Input: PEG Index
    // Return: Nothing
    //
    Method(DIWK,1)
    {
      If (LEqual(Arg0, 0))
      {
        \_SB.PCI0.PEG0.P0EW()
      }
      ElseIf (LEqual(Arg0, 1))
      {
        \_SB.PCI0.PEG1.P1EW()
      }
      ElseIf (LEqual(Arg0, 2))
      {
        \_SB.PCI0.PEG2.P2EW()
      }
    }


    //
    // Name: GDEV
    // Description: Function to return the PEG device no for the given PEG index
    // Input: Arg0 -> PEG index
    // Return: PEG device no for the given PEG index
    //
    Method(GDEV,1)
    {
      If(LEqual(Arg0, 0))
      {
        Store(0x1, Local0) //Device1-Function0 = 00001.000
      }
      ElseIf(LEqual(Arg0, 1))
      {
        Store(0x1, Local0) //Device1-Function1 = 00001.001
      }
      If(LEqual(Arg0, 2))
      {
        Store(0x1, Local0) //Device1-Function2 = 00001.010
      }


      Return(Local0)
    } // End of Method(GDEV,1)

    //
    // Name: GFUN
    // Description: Function to return the PEG function no for the given PEG index
    // Input: Arg0 -> PEG index
    // Return: PEG function no for the given PEG index
    //
    Method(GFUN,1)
    {
      If(LEqual(Arg0, 0))
      {
        Store(0x0, Local0) //Device1-Function0 = 00001.000
      }
      ElseIf(LEqual(Arg0, 1))
      {
        Store(0x1, Local0) //Device1-Function1 = 00001.001
      }
      If(LEqual(Arg0, 2))
      {
        Store(0x2, Local0) //Device1-Function2 = 00001.010
      }


      Return(Local0)
    } // End of Method(GFUN,1)

    //
    // Name: CCHK
    // Description: Function to check whether _ON/_OFF sequence is allowed to execute for the given PEG controller or not
    // Input: Arg0 -> PEG index
    //        Arg1 -> 0 means _OFF sequence, 1 means _ON sequence
    // Return: 0 - Don't execute the flow, 1 - Execute the flow
    //
    Method(CCHK,2)
    {

      //Check for Referenced PEG controller is present or not
      If(LEqual(Arg0, 0))
      {
        Store(P0VI, Local7)
      }
      ElseIf(LEqual(Arg0, 1))
      {
        Store(P1VI, Local7)
      }
      ElseIf(LEqual(Arg0, 2))
      {
        Store(P2VI, Local7)
      }
      If(LEqual(Local7, IVID))
      {

        Return(0)
      }

      If(LNotEqual(Arg0, 0))
      {
        //Check for PEG0 controller presence
        Store(P0VI, Local7)
        If(LEqual(Local7, IVID))
        {

          Return(0)
        }
      }

      //If Endpoint is not present[already disabled] before executing PGOF then don't call the PGOF method
      //If Endpoint is present[already enabled] before executing PGON then don't call the PGON method
      If(LEqual(Arg1, 0))
      {
        //_OFF sequence condition check
        If(LEqual(Arg0, 0))
        {
          If(LEqual(SGPI(SGGP, PWE0, PWG0, PWA0), 0))
          {

            Return(0)
          }
        }
        If(LEqual(Arg0, 1))
        {
          If(LEqual(SGPI(P1GP, PWE1, PWG1, PWA1), 0))
          {

            Return(0)
          }
        }
        If(LEqual(Arg0, 2))
        {
          If(LEqual(SGPI(P2GP, PWE2, PWG2, PWA2), 0))
          {

            Return(0)
          }
        }
      }
      ElseIf(LEqual(Arg1, 1))
      {
        //_ON sequence condition check
        If(LEqual(Arg0, 0))
        {
          If(LEqual(SGPI(SGGP, PWE0, PWG0, PWA0), 1))
          {

            Return(0)
          }
        }
        If(LEqual(Arg0, 1))
        {
          If(LEqual(SGPI(P1GP, PWE1, PWG1, PWA1), 1))
          {

            Return(0)
          }
        }
        If(LEqual(Arg0, 2))
        {
          If(LEqual(SGPI(P2GP, PWE2, PWG2, PWA2), 1))
          {

            Return(0)
          }
        }
      }


      Return(1)
    } // End of Method(CCHK,2)

    //
    // Name: NTFY
    // Description: Function to issue Notify command for the given PEG controller
    // Input: Arg0 -> PEG index
    //        Arg1 -> Notification value
    // Return: Nothing
    //
    Method(NTFY,2)
    {

      If (LEqual(Arg0, 0))
      {
        Notify(\_SB.PCI0.PEG0,Arg1)
      }
      ElseIf (LEqual(Arg0, 1))
      {
        Notify(\_SB.PCI0.PEG1,Arg1)
      }
      ElseIf (LEqual(Arg0, 2))
      {
        Notify(\_SB.PCI0.PEG2,Arg1)
      }
    } // End of Method(NTFY,2)

    //
    // Name: GPPR
    // Description: Function to do Endpoint ON/OFF using GPIOs
    //              There are two GPIOs currently used to control Third Party Vendor[TPV] DGPU Endpoint devices:
    //              (1) DGPU_PWR_EN [used for Power control]
    //              (2) DGPU_HOLD_RST[used for Reset control]
    // Input: Arg0 -> PEG index
    //        Arg1 -> 0 means _OFF sequence, 1 means _ON sequence
    // Return: Nothing
    //
    Method(GPPR,2)
    {

      If(LEqual(Arg1, 0))
      {
        //_OFF sequence GPIO programming
        If(LEqual(Arg0, 0))
        {
          SGPO(SGGP, HRE0, HRG0, HRA0, 1) // Assert PCIe0/dGPU_HOLD_RST# (PERST#)
          SGPO(SGGP, PWE0, PWG0, PWA0, 0) // Deassert PCIe0/dGPU_PWR_EN#
        }

        If(LEqual(Arg0, 1))
        {
          SGPO(P1GP, HRE1, HRG1, HRA1, 1) // Assert PCIe1_HOLD_RST# (PERST#)
          SGPO(P1GP, PWE1, PWG1, PWA1, 0) // Deassert PCIe1_PWR_EN#
        }

        If(LEqual(Arg0, 2))
        {
          SGPO(P2GP, HRE2, HRG2, HRA2, 1) // Assert PCIe2_HOLD_RST# (PERST#)
          SGPO(P2GP, PWE2, PWG2, PWA2, 0) // Deassert PCIe2_PWR_EN#
        }
      }
      ElseIf(LEqual(Arg1, 1))
      {
        //_ON sequence GPIO programming
        If(LEqual(Arg0, 0))
        {
          SGPO(SGGP, PWE0, PWG0, PWA0, 1) //Assert dGPU_PWR_EN#

          Sleep(DLPW) // Wait for 'given'ms if dGPU_PWROK has h/w issues
          SGPO(SGGP, HRE0, HRG0, HRA0, 0) //Deassert dGPU_HOLD_RST#

          Sleep(DLHR) // Wait for 'given'ms
        }

        If(LEqual(Arg0, 1))
        {
          SGPO(P1GP, HRE1, HRG1, HRA1, 1) //Assert dGPU_HOLD_RST#
          SGPO(P1GP, PWE1, PWG1, PWA1, 1) //Assert dGPU_PWR_EN#

          Sleep(DLPW) // Wait for 'given'ms if dGPU_PWROK has h/w issues
          SGPO(P1GP, HRE1, HRG1, HRA1, 0) //Deassert dGPU_HOLD_RST#

          Sleep(DLHR) // Wait for 'given'ms
        }

        If(LEqual(Arg0, 2))
        {
          SGPO(P2GP, HRE2, HRG2, HRA2, 1) //Assert dGPU_HOLD_RST#
          SGPO(P2GP, PWE2, PWG2, PWA2, 1) //Assert dGPU_PWR_EN#

          Sleep(DLPW) // Wait for 'given'ms if dGPU_PWROK has h/w issues
          SGPO(P2GP, HRE2, HRG2, HRA2, 0) //Deassert dGPU_HOLD_RST#

          Sleep(DLHR) // Wait for 'given'ms
        }
      }
    } // End of Method(GPPR,2)

    //
    // Name: SGPO [PCIe GPIO Write]
    // Description: Function to write into PCIe GPIO
    // Input: Arg0 -> Gpio Support
    //        Arg1 -> Expander Number
    //        Arg2 -> Gpio Number
    //        Arg3 -> Active Information
    //        Arg4 -> Value to write
    // Return: Nothing
    //
    Method(SGPO, 5, Serialized)
    {
      //
      // Invert if Active Low
      //
      If (LEqual(Arg3,0))
      {
        Not(Arg4, Arg4)
        And(Arg4, 0x01, Arg4)
      }
      If (LEqual(Arg0, 0x01))
      {
        //
        // PCH based GPIO
        //
        If (CondRefOf(\_SB.SGOV))
        {
          \_SB.SGOV(Arg2, Arg4)
        }
      }
    } // End of Method(SGPO)

    //
    // Name: SGPI [PCIe GPIO Read]
    // Description: Function to Read from PCIe GPIO
    // Input: Arg0 -> Gpio Support
    //        Arg1 -> Expander Number
    //        Arg2 -> Gpio Number
    //        Arg3 -> Active Information
    // Return: GPIO value
    //
    Method(SGPI, 4, Serialized)
    {
      If (LEqual(Arg0, 0x01))
      {
        //
        // PCH based GPIO
        //
        If (CondRefOf(\_SB.GGOV))
        {
          Store(\_SB.GGOV(Arg2), Local0)
        }
      }
      //
      // Invert if Active Low
      //
      If (LEqual(Arg3,0))
      {
        Not(Local0, Local0)
        And (Local0, 0x01, Local0)
      }

      Return(Local0)
    } // End of Method(SGPI)


} // End of Scope (\_SB.PCI0)
