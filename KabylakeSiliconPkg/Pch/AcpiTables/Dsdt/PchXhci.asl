/**@file

 @copyright
  INTEL CONFIDENTIAL
  Copyright 2010 - 2018 Intel Corporation.

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


External(\_SB.PCI0.XHC.PS0X, MethodObj)
External(\_SB.PCI0.XHC.PS3X, MethodObj)
External(\_SB.PCI0.XHC.RHUB.PS0X, MethodObj)
External(\_SB.PCI0.XHC.RHUB.PS2X, MethodObj)
External(\_SB.PCI0.XHC.RHUB.PS3X, MethodObj)
External(\_SB.PCI0.XHC.RHUB.INIR, MethodObj)

Scope(\_SB_.PCI0) {
  Device(XHC) {

    Name(_ADR, 0x00140000)

    OperationRegion(XPRT,PCI_Config,0x00,0x100)
    Field(XPRT,AnyAcc,NoLock,Preserve)
    {
      DVID, 16,
      Offset(0x10),
      XADL,  32,
      XADH,  32,
      Offset(0x50), // XHCLKGTEN - Clock Gating
          ,  2,
      STGE,  1,     // Clock Gating Bit SSLTCGE
      #ifndef MINTREE_FLAG
      Offset(R_PCH_XHCI_PCE), // 0xA2
          ,  2,
      D3HE,  1,  // D3_hot_en
      #endif //MINTREE_FLAG
    }
    //
    // Byte access for PMCS field to avoid race condition on device D-state
    //
    Field(XPRT,ByteAcc,NoLock,Preserve)
    {
      Offset(R_PCH_XHCI_PWR_CNTL_STS), // 0x74
      D0D3,  2,  // 0x74 BIT[1:0]
          ,  6,
      PMEE,  1,  // PME Enable
          ,  6,
      PMES,  1,  // PME Status
    }

    //
    // Variable to store the maximum D state supported in S0.
    //
    Name (XFLT, 0)
    //
    // XHCI controller won't go into D3Hot during S0 until _DSM method is evaluated by filter driver.
    //
    Method(_DSM,4,serialized){
      ADBG("_DSM")
      ShiftLeft(XADH, 32, Local0)
      Or (Local0, XADL, Local0)
      And(Local0,0xFFFFFFFFFFFFFFF0,Local0)
      OperationRegion(XMIO,SystemMemory,Local0,0x9000)
      Field(XMIO,AnyAcc,Lock,Preserve)
      {
        Offset(R_PCH_LP_XHCI_PORTSC02USB3),  // PORTSCXUSB3 - Port X Status and Control USB3
        PCCS,  1,       // Current Connect Status
            ,  4,
        PPLS,  4,       // Port Link Status
        PTPP,  1,       // Port Power
        #ifndef MINTREE_FLAG
        Offset(R_PCH_XHCI_STRAP2), // 0x8420, USB3 Mode Strap
        PRTM,  2,       // USB3/SSIC Mode
        #endif //MINTREE_FLAG
      }

      If(PCIC(Arg0)) { return(PCID(Arg0,Arg1,Arg2,Arg3)) }
      //
      // Check GUID ac340cb7-e901-45bf-b7e6-2b34ec931e23
      //
      If(LEqual(Arg0, Buffer(0x10) { 0xb7, 0x0c, 0x34, 0xac, 0x01, 0xe9, 0xbf, 0x45, 0xb7, 0xe6, 0x2b, 0x34, 0xec, 0x93, 0x1e, 0x23 }))
      {
        //
        // Only Supported value is "0x3"
        //
        If(LEqual(Arg1, 0x3))
        {
          Store(Arg1,XFLT)
        }
        #ifndef MINTREE_FLAG
        //
        // If either USB3 Port1 or Port2 are configured as SSIC
        //
        If(LAnd(LGreater(PRTM,0),LOr(LEqual(Arg1, 0x5),LEqual(Arg1, 0x6)))) {
          ADBG("SSIC")
          If (LOr(LOr(LEqual(PCCS, 0), LEqual(PTPP, 0)), LAnd(LGreaterEqual (PPLS, 4), LLessEqual (PPLS, 15)))){
            If (LEqual(PPLS, 8)) {
              Store(One, D3HE)
            } else {
            Store(Zero, D3HE)
            }
          } else {
            Store(One, D3HE)
          }
        }
        #endif //MINTREE_FLAG
      }
      Return(Buffer() {0})
    }

    Method(_S3D, 0, NotSerialized)
    {
      Return(3)
    }
    Method(_S4D, 0, NotSerialized)
    {
      Return(3)
    }
    Method(_S3W, 0, NotSerialized)
    {
      Return(3)
    }
    Method(_S4W, 0, NotSerialized)
    {
      Return(3)
    }

    //
    // Once the filter driver is installed, D3 is allowed.
    //
    Method(_S0W, 0x0, NotSerialized)
    {
      If(LEqual(XFLT, Zero))
      {
        Return(0x0)
      }
      Else
      {
        Return(0x3)
      }
    }

    Method(_PRW, 0)
    {
      Return(GPRW(0x6D, 4)) // can wakeup from S4 state
    }

    Method(_DSW, 3)
    {
      Store(Arg0, PMEE)
    }

    Method(_INI) {
      If(CondRefOf(\_SB.PCI0.XHC.RHUB.INIR)) {      // _INI for RTD3
        \_SB.PCI0.XHC.RHUB.INIR()
      }
    }

    //
    // GPE handler for XHCI, this is part of _Lxx handler for bus 0 PME
    //
    Method(GPEH)
    {
      If(LEqual(DVID, 0xFFFF)) {
        Return()
      }
      Store(PMES, Local0)
      Store(1, PMES) // clear PME Status
      If(LAnd(PMEE, Local0)) {
        Notify(XHC, 0x02)
      }
    }

    OperationRegion(XHCP, SystemMemory, Add(\_SB.PCI0.GPCB(), 0xA0000), 0x100)
    Field(XHCP,AnyAcc,Lock,Preserve)
    {
      Offset(0x4),
      PDBM, 16,
      Offset(0x10),
      MEMB, 64
    }

    //
    // USRA (USbR port Address), method for calculating address of first USBR port in XHCI controller
    //
    Method(USRA,0,Serialized) {
      If(LEqual(PCHV, SPTH)) { // SPT-H
        Return (15)
      } Else {                 // SPT-LP
        Return (11)
      }
    }

    //
    // SSPA (SuperSpeed Port Address), method for calculating address of first SS port in XHCI controller
    //
    Method(SSPA,0,Serialized) {
      If(LEqual(PCHV, SPTH)) { // SPT-H
        Return (17)
      } Else {                 // SPT-LP
        Return (13)
      }
    }

    Name(XRST, Zero)

    Method(_PS0,0,Serialized)
    {

      If(LEqual(^DVID,0xFFFF))
      {
        Return()
      }

      Store(^MEMB,Local2)         // Save MBAR
      Store(^PDBM,Local1)         // Save CMD

      And(^PDBM,Not(0x06),^PDBM)  // Clear MSE/BME
      #ifndef MINTREE_FLAG
      Store(0,D3HE)
      #endif //MINTREE_FLAG
      Store(0,STGE)

      //
      // Switch to D0
      //
      Store(0,^D0D3)

      Store(\XWMB,^MEMB)          // Set MBAR
      Or(Local1,0x0002,^PDBM)     // Set MSE

      OperationRegion(MC11,SystemMemory,\XWMB,0x9000)
      Field(MC11,DWordAcc,Lock,Preserve)
      {
        Offset(R_PCH_XHCI_USB2PMCTRL),   // 0x81C4, USB2PMCTRL - USB2 Power Management Control
            ,  2,
        UPSW,  2,         // U2PSUSPGP
      }

      Store(0x0,UPSW)

      And(^PDBM,Not(0x02),^PDBM)  // Clear MSE

      Store(Local2,^MEMB)         // Restore MBAR
      Store(Local1,^PDBM)         // Restore CMD

      //
      // Call platform XHC PS0 method if present
      //
      If(CondRefOf(\_SB.PCI0.XHC.PS0X))
      {
        \_SB.PCI0.XHC.PS0X()
      }

      //
      //
      If(LAnd(UWAB,LOr(LEqual(D0D3,0),LEqual(\_SB.PCI0.XDCI.D0I3,0)))) {
        //
        // If the USB WA Bit is set and any XHCI or XDCI controller is in D0
        //
        //
        // USB2 PHPY Power Gating - SW WA
        //
        // 1. BIOS writes a new command to the MTPMC register to cause the PMC to disable power gating
        Store(1,MPMC)

        // 2. BIOS waits for PCH_PM_STS.MSG_FULL_STS to be 0
        //      In parallel and in response to the previous command from BIOS, PMC FW will:
        //         * Make the USB2 force common lane PG match the BIOS policy (common lane PG disallowed)
        //         * Disable SUS power gating in XHCI
        //         * Wait for USB2 PHY side_pok to be 1
        //         * Disable core power gating in USB2 PHY
        //         * Disable common lane power gating in USB2 PHY (probably not necessary, consider removal)
        //         * Wait for USB2 SUS restoration status to be set, and do USB2 SUS power gating restoration
        //         * Get the PHY in the correct state before allowing transition to D0.
        //        * Clear MSG_FULL_STS
        //    BIOS sees MSG_FULL_STS clear and exits the method
        //
        While(PMFS) {
          Sleep(10)
        }
      } // End If(UWAB)

    }

    Method(_PS3,0,Serialized)
    {

      If(LEqual(^DVID,0xFFFF))
      {
        Return()
      }

      Store(^MEMB,Local2)         // Save MBAR
      Store(^PDBM,Local1)         // Save CMD

      And(^PDBM,Not(0x06),^PDBM)  // Clear MSE/BME

      //
      // Switch back to D0
      //
      Store(0,^D0D3)

      Store(\XWMB,^MEMB)          // Set MBAR
      Or(Local1,0x0002,^PDBM)     // Set MSE

      OperationRegion(MC11,SystemMemory,\XWMB,0x9000)
      Field(MC11,DWordAcc,Lock,Preserve)
      {
        Offset(R_PCH_XHCI_LFPSPM),   // 0x81A0, 
        LFU3,  6,         // LFPS PM U3 Enable
                          // 0 = LFPS Receiver shall be kept enabled when the port is in U3
                          // 1 = LFPS Receiver whall be disabled when the port is in U3
        Offset(R_PCH_XHCI_USB2PMCTRL),   // 0x81C4, USB2PMCTRL - USB2 Power Management Control
            ,  2,
        UPSW,  2,         // U2PSUSPGP
      }

      Name(U3PS, Zero) // USB3 PortSC Port 1 offset

      If(LEqual(PCHV(), SPTL)) {
        Store(R_PCH_LP_XHCI_PORTSC01USB3, U3PS)
      } Else {
        Store(R_PCH_H_XHCI_PORTSC01USB3, U3PS)
      }

      // USB3 Port Status and Control memory region
      OperationRegion(UPSC,SystemMemory,\XWMB + U3PS,0x100)
      Field(UPSC,DwordAcc,Lock,Preserve)
      {
        Offset(0x0),
            ,  5,
        PLS1,  4,         //Port Link  State (PLS) USB3 Port 1 on KBL PCH  bits [8:5]
            , 13,
        PLC1,  1,         // Port Link  State Change (PLC) USB3 Port 1 on KBL PCH bit 22
            ,  1,
        CAS1,  1,         // Cold Attach Status (CAS) USB3 Port 1 on KBL PCH bit 24
        Offset(0x10),
            ,  5,
        PLS2,  4,         //Port Link  State (PLS) USB3 Port 2 on KBL PCH  bits [8:5]
            , 13,
        PLC2,  1,         // Port Link  State Change (PLC) USB3 Port 2 on KBL PCH bit 22
            ,  1,
        CAS2,  1,         // Cold Attach Status (CAS) USB3 Port 2 on KBL PCH bit 24
        Offset(0x20),
            ,  5,
        PLS3,  4,         //Port Link  State (PLS) USB3 Port 3 on KBL PCH  bits [8:5]
            , 13,
        PLC3,  1,         // Port Link  State Change (PLC) USB3 Port 3 on KBL PCH bit 22
            ,  1,
        CAS3,  1,         // Cold Attach Status (CAS) USB3 Port 3 on KBL PCH bit 24
        Offset(0x30),
            ,  5,
        PLS4,  4,         //Port Link  State (PLS) USB3 Port 4 on KBL PCH  bits [8:5]
            , 13,
        PLC4,  1,         // Port Link  State Change (PLC) USB3 Port 4 on KBL PCH bit 22
            ,  1,
        CAS4,  1,         // Cold Attach Status (CAS) USB3 Port 4 on KBL PCH bit 24
        Offset(0x40),
            ,  5,
        PLS5,  4,         //Port Link  State (PLS) USB3 Port 5 on KBL PCH  bits [8:5]
            , 13,
        PLC5,  1,         // Port Link  State Change (PLC) USB3 Port 5 on KBL PCH bit 22
            ,  1,
        CAS5,  1,         // Cold Attach Status (CAS) USB3 Port 5 on KBL PCH bit 24
        Offset(0x50),
            ,  5,
        PLS6,  4,         //Port Link  State (PLS) USB3 Port 6 on KBL PCH  bits [8:5]
            , 13,
        PLC6,  1,         // Port Link  State Change (PLC) USB3 Port 6 on KBL PCH bit 22
            ,  1,
        CAS6,  1,         // Cold Attach Status (CAS) USB3 Port 6 on KBL PCH bit 24
        Offset(0x60),
            , 24,
        CAS7,  1,         // Cold Attach Status (CAS) USB3 Port 7 on KBL PCH
        Offset(0x70),
            , 24,
        CAS8,  1,         // Cold Attach Status (CAS) USB3 Port 8 on KBL PCH
        Offset(0x80),
            , 24,
        CAS9,  1,         // Cold Attach Status (CAS) USB3 Port 9 on KBL PCH
        Offset(0x90),
            , 24,
        CASA,  1,         // Cold Attach Status (CAS) USB3 Port 10 on KBL PCH
      }

      // USB3 Port Status and Control memory region
      Field(UPSC,DwordAcc,Lock,Preserve)
      {
        Offset(0x0),
        PSC1,32,
        Offset(0x10),
        PSC2,32,
        Offset(0x20),
        PSC3,32,
        Offset(0x30),
        PSC4,32,
        Offset(0x40),
        PSC5,32,
        Offset(0x50),
        PSC6,32,
      }

      Store(0x3,UPSW)
      Store(1,STGE)

      Store(0x3F,LFU3) // LFPS Receiver whall be disabled when the port is in U3
      Name(PSCO,0xFFFFFFFF)
      Sleep(1)
      
      if((PLS1==0x3) && (PLC1))
      {
        And(0xFFFFFFFD,PSC1,PSCO)
        Or(0x400000,PSCO,PSCO)
        Store(PSCO,PSC1)
      }

      if((PLS2==0x3) && (PLC2))
      {
        And(0xFFFFFFFD,PSC2,PSCO)
        Or(0x400000,PSCO,PSCO)
        Store(PSCO,PSC2)
      }

      if((PLS3==0x3) && (PLC3))
      {
        And(0xFFFFFFFD,PSC3,PSCO)
        Or(0x400000,PSCO,PSCO)
        Store(PSCO,PSC3)
      }

      if((PLS4==0x3) && (PLC4))
      {
        And(0xFFFFFFFD,PSC4,PSCO)
        Or(0x400000,PSCO,PSCO)
        Store(PSCO,PSC4)
      }

      if((PLS5==0x3) && (PLC5))
      {
        And(0xFFFFFFFD,PSC5,PSCO)
        Or(0x400000,PSCO,PSCO)
        Store(PSCO,PSC5)
      }

      if((PLS6==0x3) && (PLC6))
      {
        And(0xFFFFFFFD,PSC6,PSCO)
        Or(0x400000,PSCO,PSCO)
        Store(PSCO,PSC6)
      }

      Store(1,STGE)
      #ifndef MINTREE_FLAG

      If ((CAS1 || CAS2 || CAS3 || CAS4 || CAS5 || CAS6) || ((PCHV() == SPTH) && (CAS7 || CAS8 || CAS9 || CASA)))
      {
        Store(0,D3HE)   // Clear D3HE
        Sleep(1)
      }
      Else
      {
        Store(1,D3HE)   // Set D3HE
      }
      #endif //MINTREE_FLAG

      Store(0,LFU3) // LFPS Receiver whall be kept enabled when the port is in U3

      And(^PDBM,Not(0x02),^PDBM)  // Clear MSE

      //
      // Switch back to D3
      //
      Store(3,^D0D3)

      Store(Local2,^MEMB)         // Restore MBAR
      Store(Local1,^PDBM)         // Restore CMD

      //
      // Call platform XHC PS3 method if present
      //
      If(CondRefOf(\_SB.PCI0.XHC.PS3X))
      {
        \_SB.PCI0.XHC.PS3X()
      }

      If(LAnd(UWAB,LAnd(LEqual(D0D3,3),LOr(LEqual(\_SB.PCI0.XDCI.D0I3,3),LEqual(\_SB.PCI0.XDCI.DVID,0xFFFF))))) {
        //
        // If the USB WA Bit is set and ((XHCI is in D3) AND ((XDCI is in D3) OR (XDCI is function disabled)))
        //
        // 1. BIOS writes a new command to the MTPMC register to enable power gating
        Store(3,MPMC)

        // 2. BIOS waits for PCH_PM_STS.MSG_FULL_STS to be 0
        //      In parallel and in response to the previous command from BIOS, PMC FW will:
        //        * Make the USB2 force common lane PG match the BIOS policy (common lane PG allowed)
        //        * Enable SUS power gating in XHCI
        //        * Enable core power gating in USB2 PHY
        //        * Enable common lane power gating in the USB2 PHY
        //        * Clear MSG_FULL_STS
        //    BIOS sees MSG_FULL_STS clear and exits the method
        //
        While(PMFS) {
          Sleep(10)
        }
      } // End If(UWAB)
    }

    //
    //
    // Check for XHCI switch UUID
    //
    // Arguments:
    //  Arg0 (Buffer) : UUID
    //
    // Returns:
    //  1: It's valid UUID
    //  0: Invalid UUID
    //
    Method(CUID,1,Serialized) {
      If(LEqual(Arg0,ToUUID("7c9512a9-1705-4cb4-af7d-506a2423ab71"))) {
        Return(1)
      }
      Return(0)
    }

    Device(RHUB)
    {
      Name(_ADR, Zero)

      // PS0 Method for xHCI Root Hub
      Method(_PS0,0,Serialized)
      {
        If(LEqual(\_SB.PCI0.XHC.DVID,0xFFFF))
        {
          Return()
        }
        //
        // Call platform XHC.RHUB PS0 method if present.
        //
        If(CondRefOf(\_SB.PCI0.XHC.RHUB.PS0X))
        {
          \_SB.PCI0.XHC.RHUB.PS0X()
        }
      }

      // PS2 Method for xHCI Root Hub
      Method(_PS2,0,Serialized)
      {
        If(LEqual(\_SB.PCI0.XHC.DVID,0xFFFF))
        {
          Return()
        }
        //
        // Call platform XHC.RHUB PS2 method if present.
        //
        If(CondRefOf(\_SB.PCI0.XHC.RHUB.PS2X))
        {
          \_SB.PCI0.XHC.RHUB.PS2X()
        }
      }

      // PS3 Method for xHCI Root Hub
      Method(_PS3,0,Serialized)
      {
        If(LEqual(\_SB.PCI0.XHC.DVID,0xFFFF))
        {
          Return()
        }
        //
        // Call platform XHC.RHUB PS3 method if present.
        //
        If(CondRefOf(\_SB.PCI0.XHC.RHUB.PS3X))
        {
          \_SB.PCI0.XHC.RHUB.PS3X()
        }
      }

      //
      // High Speed Ports (without USBR)
      //
      Device(HS01)
      {
        Name(_ADR, 0x01)
      }

      Device(HS02)
      {
        Name(_ADR, 0x02)
      }

      Device(HS03)
      {
        Name(_ADR, 0x03)
      }

      Device(HS04)
      {
        Name(_ADR, 0x04)
      }

      Device(HS05)
      {
        Name(_ADR, 0x05)
      }

      Device(HS06)
      {
        Name(_ADR, 0x06)
      }

      Device(HS07)
      {
        Name(_ADR, 0x07)
      }

      Device(HS08)
      {
        Name(_ADR, 0x08)
      }

      Device(HS09)
      {
        Name(_ADR, 0x09)
      }

      Device(HS10)
      {
        Name(_ADR, 0x0A)
      }

      //
      // USBR port will be known as USBR instead of HS09 / HS15
      //
      Device(USR1)
      {
        Method(_ADR) { Return (Add(USRA(),0)) }
      }

      //
      // USBR port 2 will be known as USBR instead of xxxx
      //
      Device(USR2)
      {
        Method(_ADR) { Return (Add(USRA(),1)) }
      }

      //
      // Super Speed Ports
      //
      Device(SS01)
      {
        Method(_ADR) { Return (Add(SSPA(),0)) }
      }

      Device(SS02)
      {
        Method(_ADR) { Return (Add(SSPA(),1)) }
      }

      Device(SS03)
      {
        Method(_ADR) { Return (Add(SSPA(),2)) }
      }

      Device(SS04)
      {
        Method(_ADR) { Return (Add(SSPA(),3)) }
      }

      Device(SS05)
      {
        Method(_ADR) { Return (Add(SSPA(),4)) }
      }

      Device(SS06)
      {
        Method(_ADR) { Return (Add(SSPA(),5)) }
      }

    } // device rhub
  } // device xhc
} //scope

//
// SPT-H
//
If(LEqual(PCHV(),SPTH)) {
  Scope(\_SB_.PCI0.XHC.RHUB) {

    Device(HS11)
    {
      Name(_ADR, 0xB)
    }

    Device(HS12)
    {
      Name(_ADR, 0xC)
    }

    Device(HS13)
    {
      Name(_ADR, 0xD)
    }

    Device(HS14)
    {
      Name(_ADR, 0xE)
    }

    Device(SS07)
    {
      Method(_ADR) { Return (Add(SSPA(),6)) }
    }

    Device(SS08)
    {
      Method(_ADR) { Return (Add(SSPA(),7)) }
    }

    Device(SS09)
    {
      Method(_ADR) { Return (Add(SSPA(),8)) }
    }

    Device(SS10)
    {
      Method(_ADR) { Return (Add(SSPA(),9)) }
    }

  } //scope
} // if
