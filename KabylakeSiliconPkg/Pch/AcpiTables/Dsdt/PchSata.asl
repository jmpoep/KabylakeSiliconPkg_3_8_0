/**@file

 @copyright
  INTEL CONFIDENTIAL
  Copyright 2013 - 2017 Intel Corporation.

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


#define ROOTPORT_READ           0
#define ROOTPORT_WRITE          1
#define ENDPOINT_READ           2
#define ENDPOINT_WRITE          3
#define GPIO_NO_CONTROL 0
#define GPIO_INTERNAL 1
#define GPIO_EXTERNAL 2
#define EXPANDER0 0
#define EXPENDER1 1
#define INDEX_CONTROL 0
#define INDEX_EXPANDER_NR 1
#define INDEX_PIN_NR 2
#define INDEX_POLARITY 3


External(\_SB.PCI0.SAT0.NVM1.RAID, MethodObj)
External(\_SB.PCI0.SAT0.NVM1.IR3E, MethodObj)
External(\_SB.PCI0.SAT0.NVM1.VLPM)
External(\_SB.PCI0.SAT0.NVM2.RAID, MethodObj)
External(\_SB.PCI0.SAT0.NVM2.IR3E, MethodObj)
External(\_SB.PCI0.SAT0.NVM2.VLPM)
External(\_SB.PCI0.SAT0.NVM3.RAID, MethodObj)
External(\_SB.PCI0.SAT0.NVM3.IR3E, MethodObj)
External(\_SB.PCI0.SAT0.NVM3.VLPM)


//
// SDSM is Device Specific Method supporting AHCI DEVSLP
// It is not guaranteed to be available on every boot
//
External(\_SB.PCI0.SAT0.SDSM, MethodObj)
External(\_SB.PCI0.RP05.PWRG)
External(\_SB.PCI0.RP05.RSTG)
External(\_SB.PCI0.RP05.SCLK)
External(\_SB.PCI0.RP09.PWRG)
External(\_SB.PCI0.RP09.RSTG)
External(\_SB.PCI0.RP09.SCLK)
External(\_SB.PCI0.RP13.PWRG)
External(\_SB.PCI0.RP13.RSTG)
External(\_SB.PCI0.RP13.SCLK)
External(\_SB.PCI0.RP17.PWRG)
External(\_SB.PCI0.RP17.RSTG)
External(\_SB.PCI0.RP17.SCLK)

  // PCH SATA Controller
  Device (SAT0)
  {
    //Bus 0x00, Device 0x17, Function 0x00
    Name(_ADR, 0x00170000)

    Method(_DSM,4,serialized){
      if(PCIC(Arg0)) { return(PCID(Arg0,Arg1,Arg2,Arg3)) };
      if(CondRefOf(\_SB.PCI0.SAT0.SDSM)) { return (\_SB.PCI0.SAT0.SDSM(Arg0,Arg1,Arg2,Arg3)) };
      Return(Buffer() {0})
    }

    Device(PRT0)
    {
      Name(_ADR,0x0000FFFF)  // Port 0
    }

    Device(PRT1)
    {
      Name(_ADR,0x0001FFFF)  // Port 1
    }

    Device(PRT2)
    {
      Name(_ADR,0x0002FFFF)  // Port 2
    }

    Device(PRT3)
    {
      Name(_ADR,0x0003FFFF)  // Port 3
    }

    Device(PRT4)
    {
      Name(_ADR,0x0004FFFF)  // Port 4
    }

    Device(PRT5)
    {
      Name(_ADR,0x0005FFFF)  // Port 5
    }
    Device(VOL0)
    {
      Name(_ADR,0x0080FFFF)  // RST Raid Volume 0 or SRT Cache
    }
    Device(VOL1)
    {
      Name(_ADR,0x0081FFFF)  // RST Raid Volume 1
    }
    Device(VOL2)
    {
      Name(_ADR,0x0082FFFF)  // RST Raid Volume 2
    }
    #ifndef MINTREE_FLAG
    //
    // Method to perform RST PCIe Storage Remapping read or write access to the remapped device / hidden root port configuration space
    // This method takes 5 parameters as below:
    // Arg0 - RST PCIe Storage Cycle Router#
    // Arg1 - PCI Offset
    // Arg2 - WriteData (AndMask)
    // Arg3 - WriteData (OrMask)
    // Arg4 - Access Methods: ROOTPORT_READ, ROOTPORT_WRITE, ENDPOINT_READ, ENDPOINT_WRITE
    //
    Method(RDCA, 5, Serialized)
    {
      //
      // Operation Region for Sata Extended Config Space for Hidden Root Port Access (0x100)
      //
      OperationRegion(RPAL, SystemMemory, Add(\_SB.PCI0.GPCB(), Add(Add(0xB8000, V_PCH_RST_PCIE_STORAGE_REMAP_RP_OFFSET),Arg1)), 0x4)
      Field(RPAL,DWordAcc,Lock,Preserve)
      {
        RPCD, 32,
      }


      //
      // Operation Region for Endpoint Index-Data Pair for Remapped Device Access (0x308)
      //
      OperationRegion(EPAC, SystemMemory, Add(\_SB.PCI0.GPCB(), Add(0xB8000, R_PCH_RST_PCIE_STORAGE_CAIR)), 0x8)
      Field(EPAC,DWordAcc,Lock,Preserve)
      {
        CAIR, 32,
        CADR, 32,
      }

      //
      // Operation Region for RST PCIe Storage Cycle Router Global configuration registers (0xFC0)
      //
      OperationRegion(NCRG, SystemMemory, Add(\_SB.PCI0.GPCB(), Add(0xB8000, R_PCH_RST_PCIE_STORAGE_CRGC)), 0x4)
      Field(NCRG,DWordAcc,Lock,Preserve)
      {
        CRGC, 32,
      }

      If (LGreater(Arg0, 2))     // Return if RST PCIe Storage Cycle Router# is invalid
      {
        Return(0)
      }
      Else                       // Set RST PCIe Storage Cycle Router Accessibility based on Arg0 - RST PCIe Storage Cycle Router#
      {
        Store(Arg0,CRGC)
      }

      Switch(ToInteger(Arg4))
      {
        Case(ROOTPORT_READ)     // Read access to the Hidden Root Port
        {
          Return(RPCD)
        }
        Case(ENDPOINT_READ)     // Read access to the Remapped Device
        {
          Store(Arg1,CAIR)
          Return(CADR)
        }
        Case(ROOTPORT_WRITE)     // Write access to the Hidden Root Port
        {
          And(Arg2,RPCD,Local0)
          Or(Arg3,Local0,Local0)
          Store(Local0,RPCD)
        }
        Case(ENDPOINT_WRITE)     // Write access to the Remapped Device
        {
          Store(Arg1,CAIR)
          And(Arg2,CADR,Local0)
          Or(Arg3,Local0,Local0)
          Store(Local0,CADR)
        }
        Default
        {
          Return(0)
        }
      }
      Return(0)
    }
    #endif //MINTREE_FLAG
    // Asign Root Port Configuration for remapped drive.
    // 4 arguments: NRPN, PWRG, RSTG, SCLK
    Method(ARPC, 4, Serialized,,, {FieldUnitObj, PkgObj, PkgObj, PkgObj})
    {
      ADBG(Concatenate("NRPN: ", ToHexString(Arg0)))
      Switch(ToInteger(Arg0))
      {
        Case(4)
        {
          if(condrefof(\_SB.PCI0.RP05.PWRG)) {CopyObject(\_SB.PCI0.RP05.PWRG,Arg1)}
          if(condrefof(\_SB.PCI0.RP05.RSTG)) {CopyObject(\_SB.PCI0.RP05.RSTG,Arg2)}
          if(condrefof(\_SB.PCI0.RP05.SCLK)) {CopyObject(\_SB.PCI0.RP05.SCLK,Arg3)}
        }
        Case(8)
        {
          if(condrefof(\_SB.PCI0.RP09.PWRG)) {CopyObject(\_SB.PCI0.RP09.PWRG,Arg1)}
          if(condrefof(\_SB.PCI0.RP09.RSTG)) {CopyObject(\_SB.PCI0.RP09.RSTG,Arg2)}
          if(condrefof(\_SB.PCI0.RP09.SCLK)) {CopyObject(\_SB.PCI0.RP09.SCLK,Arg3)}

        }
        Case(12)
        {
          if(condrefof(\_SB.PCI0.RP13.PWRG)) {CopyObject(\_SB.PCI0.RP13.PWRG,Arg1)}
          if(condrefof(\_SB.PCI0.RP13.RSTG)) {CopyObject(\_SB.PCI0.RP13.RSTG,Arg2)}
          if(condrefof(\_SB.PCI0.RP13.SCLK)) {CopyObject(\_SB.PCI0.RP13.SCLK,Arg3)}
        }
        Case(16)
        {
          if(condrefof(\_SB.PCI0.RP17.PWRG)) {CopyObject(\_SB.PCI0.RP17.PWRG,Arg1)}
          if(condrefof(\_SB.PCI0.RP17.RSTG)) {CopyObject(\_SB.PCI0.RP17.RSTG,Arg2)}
          if(condrefof(\_SB.PCI0.RP17.SCLK)) {CopyObject(\_SB.PCI0.RP17.SCLK,Arg3)}
        }
        Default
        {
            ADBG(Concatenate("ERR!NRPN: ", ToHexString(Arg0)))
        }
      }
    }



//
// AdvancedFeaturesBegin
//
    Device(NVM1)
    {
      Name(_ADR,0x00C1FFFF)

      Method(_INI)
      {
        Store (NIT1, NITV)
        Store (NPM1, NPMV)
        Store (NPC1, NPCV)
        Store (NL11, NL1V)
        Store (ND21, ND2V)
        Store (ND11, ND1V)
        Store (NLR1, NLRV)
        Store (NLD1, NLDV)
        Store (NEA1, NEAV)
        Store (NEB1, NEBV)
        Store (NEC1, NECV)
        Store (NRA1, NRAV)
        Store (NMB1, NMBV)
        Store (NMV1, NMVV)
        Store (NPB1, NPBV)
        Store (NPV1, NPVV)
        Store(NRP1, NRPN)
        Store (0, NCRN)

        ARPC(NRPN, RefOf(PWRG), RefOf(RSTG), RefOf(SCLK))
      }

      Include("PchRstPcieStorage.asl")
    }

    Device(NVM2)
    {
      Name(_ADR,0x00C2FFFF)

      Method(_INI)
      {
        Store (NIT2, NITV)
        Store (NPM2, NPMV)
        Store (NPC2, NPCV)
        Store (NL12, NL1V)
        Store (ND22, ND2V)
        Store (ND12, ND1V)
        Store (NLR2, NLRV)
        Store (NLD2, NLDV)
        Store (NEA2, NEAV)
        Store (NEB2, NEBV)
        Store (NEC2, NECV)
        Store (NRA2, NRAV)
        Store (NMB2, NMBV)
        Store (NMV2, NMVV)
        Store (NPB2, NPBV)
        Store (NPV2, NPVV)
        Store(NRP2, NRPN)
        Store (1, NCRN)

        ARPC(NRPN, RefOf(PWRG), RefOf(RSTG), RefOf(SCLK))
      }

      Include("PchRstPcieStorage.asl")
    }

    Device(NVM3)
    {

      Name(_ADR,0x00C3FFFF)
      Method(_INI)
      {
        Store (NIT3, NITV)
        Store (NPM3, NPMV)
        Store (NPC3, NPCV)
        Store (NL13, NL1V)
        Store (ND23, ND2V)
        Store (ND13, ND1V)
        Store (NLR3, NLRV)
        Store (NLD3, NLDV)
        Store (NEA3, NEAV)
        Store (NEB3, NEBV)
        Store (NEC3, NECV)
        Store (NRA3, NRAV)
        Store (NMB3, NMBV)
        Store (NMV3, NMVV)
        Store (NPB3, NPBV)
        Store (NPV3, NPVV)
        Store(NRP3, NRPN)
        Store (2, NCRN)

        ARPC(NRPN, RefOf(PWRG), RefOf(RSTG), RefOf(SCLK))

      }
       Include("PchRstPcieStorage.asl")
    }


    Method(PSTA,1,Serialized) {  //PowerCheck, Arg0=PWRG package
      If(LEqual(DeRefOf(Index(Arg0, INDEX_CONTROL)), GPIO_NO_CONTROL)) { Return(1) } // no power control means it's always enabled
      If(LEqual(DeRefOf(Index(Arg0, INDEX_CONTROL)), GPIO_INTERNAL)) {
        if(LEqual(\_SB.GGOV(DeRefOf(Index(Arg0, INDEX_PIN_NR))),DeRefOf(Index(Arg0, INDEX_POLARITY)))) {
          Return(0x01)
        }
        Return(0x00)
      }
      If(LEqual(DeRefOf(Index(Arg0, INDEX_CONTROL)),GPIO_EXTERNAL))  { // IOEX mode
        If(LEqual(\_SB.PCI0.GEXP.GEPS(DeRefOf(Index(Arg0, INDEX_EXPANDER_NR)),DeRefOf(Index(Arg0, INDEX_PIN_NR))),DeRefOf(Index(Arg0, INDEX_POLARITY)))) {
          Return(0x01)
        }
        Return(0x00)
      }
      Return (0)
    }
    Method(PON,1,Serialized) {  //PowerOn, Arg0=PWRG package
      If(LNotEqual(DeRefOf(Index(Arg0, 0)),0)) {     // if power gating enabled
        if(LEqual(DeRefOf(Index(Arg0, 0)),1)) {      // GPIO mode
          ADBG(Concatenate("PON GPIO=", ToHexString(DeRefOf(Index(Arg0, 2)))))
          \_SB.SGOV(DeRefOf(Index(Arg0, 2)),DeRefOf(Index(Arg0, 3)))
        }
        if(LEqual(DeRefOf(Index(Arg0, 0)),2))  {     // IOEX mode
         ADBG(Concatenate("PON IOEX=", ToHexString(DeRefOf(Index(Arg0, 2)))))
          \_SB.PCI0.GEXP.SGEP(DeRefOf(Index(Arg0, 1)),DeRefOf(Index(Arg0, 2)),DeRefOf(Index(Arg0, 3)))
        }
      }
    }
    Method(POFF,1,Serialized) {  //PowerOff, Arg0=PWRG package
      If(LNotEqual(DeRefOf(Index(Arg0, 0)),0)) { // if power gating enabled
        if(LEqual(DeRefOf(Index(Arg0, 0)),1)) { // GPIO mode
          ADBG(Concatenate("POFF GPIO=", ToHexString(DeRefOf(Index(Arg0, 2)))))
          \_SB.SGOV(DeRefOf(Index(Arg0, 2)),Xor(DeRefOf(Index(Arg0, 3)),1))
        }
        if(LEqual(DeRefOf(Index(Arg0, 0)),2))  { // IOEX mode
          ADBG(Concatenate("POFF IOEX=", ToHexString(DeRefOf(Index(Arg0, 2)))))
          \_SB.PCI0.GEXP.SGEP(DeRefOf(Index(Arg0, 1)),DeRefOf(Index(Arg0, 2)),Xor(DeRefOf(Index(Arg0, 3)),1))
        }
      }
    }
//
// AdvancedFeaturesEnd
//

  }
