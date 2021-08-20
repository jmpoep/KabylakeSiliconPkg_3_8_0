/**@file

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

#define PCI_CARD_BASE_ADDR0     0x10
#define PCI_CARD_BASE_ADDR1     0x14
#define PCI_CARD_BASE_ADDR2     0x18
#define PCI_CARD_BASE_ADDR3     0x1C
#define PCI_CARD_BASE_ADDR4     0x20
#define PCI_CARD_BASE_ADDR5     0x24

#define VDID_OFFSET 0x0 // 32bit value
#ifndef MINTREE_FLAG
#define L23E_OFFSET 0xE2 // bit 2 - L23_Rdy Entry Request (L23ER)
#define L23R_OFFSET 0xE2 // bit 3 - L23_Rdy to Detect Transition (L23R2DT)
#endif //MINTREE_FLAG
#define LEDM_OFFSET 0x324 // bit 3 - DMI L1 Entry Disable Mask (DMIL1EDM)
#define LDIS_OFFSET 0x50 //bit 4 - Link Disable (LD)
#define DPGE_OFFSET 0x420 // bit 30 - Disabled, Detect, L23_Rdy State and Un-Configured PHY Lane Power Gating Enable (DLSULPPGE)
#define LASX_OFFSET 0x52 // bit 13 - Link Active (LA)

#define ROOTPORT_READ           0
#define ROOTPORT_WRITE          1
#define ENDPOINT_READ           2
#define ENDPOINT_WRITE          3

  //RST Pcie Storage Remapped Base Address Index Value
  Name(PRBI, 0)

  //RST Pcie Storage Remapped Base Address Data Value
  Name(PRBD, 0)

  //RST Pcie Storage Endpoint Command Data
  Name(PCMD, 0)

  Name(RSTG, Package() { 0, 0, 0, 0 })
  Name(PWRG, Package() { 0, 0, 0, 0 })
  Name(SCLK, Package() { 0, 0, 0 })
   //RST Pcie Storage Cycle Router
  Name(NCRN, 0)

  //
  // Variables list to store corresponding value for different NVM device
  //
  Name(NITV, 0)  // Interface Type
  Name(NPMV, 0)  // Power Management Capability Pointer
  Name(NPCV, 0)  // PCIe Capabilities Pointer
  Name(NL1V, 0)  // L1SS Capability Pointer
  Name(ND2V, 0)  // Endpoint L1SS Control Data2
  Name(ND1V, 0)  // Endpoint L1SS Control Data1
  Name(NLRV, 0)  // LTR Capability Pointer
  Name(NLDV, 0)  // Endpoint LTR Data
  Name(NEAV, 0)  // Endpoint LCTL Data
  Name(NEBV, 0)  // Endpoint DCTL Data
  Name(NECV, 0)  // Endpoint DCTL2 Data
  Name(NRAV, 0)  // RootPort DCTL2 Data
  Name(NMBV, 0)  // Endpoint unique MSI-X Table BAR
  Name(NMVV, 0)  // Endpoint unique MSI-X Table BAR value
  Name(NPBV, 0)  // Endpoint unique MSI-X PBA BAR
  Name(NPVV, 0)  // Endpoint unique MSI-X PBA BAR value
  Name(NRPN, 0) //  Assigned Root Port number

  Name(MXIE, 0)

  Name(ISD3, 0)  // Is device in D3 state

  //
  // AdvancedFeaturesBegin
  //

  //
  // Remapped port power control. Serialized method
  // to prevent races between different threads trying to enable/disable
  // remapped drive.
  // Arg0 - true if power should be enabled, false if disabled
  //
  Method(RPPC, 1, Serialized) {
    If(LEqual(Arg0, 0)) {
      RPOF()
    } Else {
      RPON()
    }
  }

  // Remapped Port ON
  Method(RPON, 0, Serialized)
  {
    // If device was not set in D3 do not re-initiate.
    If(LEqual(ISD3 ,0)) { Return()}
    Store(0,ISD3)
    ADBG(Concatenate("RPONs: ", ToHexString(NRPN)))
    // Power Pin
      \_SB.PCI0.SAT0.PON(PWRG)

    // de-assert CLK_REQ MSK
    if(LNotEqual(DeRefOf(Index(SCLK, 0)),0)) { // if power gating enabled
      PCRA(PID_ICC,R_PCH_PCR_ICC_MSKCKRQ,Not(DeRefOf(Index(SCLK, 1))))  // And ~SCLK to clear bit
      Sleep(16)
    }

    \_SB.PCI0.SAT0.PON(RSTG)

    // Clear DLSULPPGE, then set L23_Rdy to Detect Transition  (L23R2DT)
    RDCA(NCRN,DPGE_OFFSET,0xBFFFFFFF,0x0,ROOTPORT_WRITE)  //Store(0, DPGE)
    RDCA(NCRN,L23R_OFFSET,0xFFFFFFFF,0x8,ROOTPORT_WRITE)  //Store(1, L23R)
    Sleep(16)
      Store(0, Local0)
    // Wait up to 12 ms for transition to Detect
    While(And(RDCA(NCRN,L23R_OFFSET,0x0,0x0,ROOTPORT_READ),0x8))  {  //While(L23R) {
      If(Lgreater(Local0, 4))    // Debug - Wait for 5 ms
      {
        Break
      }
      Sleep(16)
      Increment(Local0)
    }

    // Once in Detect, wait up to 124 ms for Link Active (typically happens in under 70ms)
    // Worst case per PCIe spec from Detect to Link Active is:
    // 24ms in Detect (12+12), 72ms in Polling (24+48), 28ms in Config (24+2+2+2+2)
    RDCA(NCRN,DPGE_OFFSET,0xFFFFFFFF,0x40000000,ROOTPORT_WRITE) //Store(1, DPGE)
    Store(0, Local0)
    While(LEqual(And(RDCA(NCRN,LASX_OFFSET,0x0,0x0,ROOTPORT_READ),0x2000),0)) { //While(LEqual(LASX,0)) {
      If(Lgreater(Local0, 8))
      {
        Break
      }
      Sleep(16)
      Increment(Local0)
    }

    RDCA(NCRN,LEDM_OFFSET,0xFFFFFFF7,0x0,ROOTPORT_WRITE) //Store(0, LEDM) // Set PCIEDBG.DMIL1EDM (324[3]) = 0
    // Wait for voltage stablization.
    Sleep(2000)
    NVD0()
    ADBG(Concatenate("RPONe: ", ToHexString(NRPN)))
  }

  // Remapped Port OFF
  Method(RPOF, 0, Serialized)
  {
    //Exit If D3hot is not successful
    If(LEqual(NVD3(),0)) { Return() }
    ADBG(Concatenate("POFF NRPN: ", ToHexString(NRPN)))
    // Set L23_Rdy Entry Request (L23ER)
    RDCA(NCRN,L23E_OFFSET,0xFFFFFFFF,0x4,ROOTPORT_WRITE) // Store(1, L23E)
    Sleep(16)
    Store(0, Local0)
    While(And(RDCA(NCRN,L23E_OFFSET,0x0,0x0,ROOTPORT_READ),0x4))  //While(L23E) {
    {
      If(Lgreater(Local0, 4))    // Debug - Wait for 5 ms
      {
          Break
      }
      Sleep(16)
      Increment(Local0)
    }
    RDCA(NCRN,LEDM_OFFSET,0xFFFFFFFF,0x8,ROOTPORT_WRITE)  //Store(1, LEDM) // PCIEDBG.DMIL1EDM (324[3]) = 1

    // Assert Reset Pin
    \_SB.PCI0.SAT0.POFF(RSTG)

    // assert CLK_REQ MSK
    if(LNotEqual(DeRefOf(Index(SCLK, 0)),0)) { // if power gating enabled
      PCRO(PID_ICC,R_PCH_PCR_ICC_MSKCKRQ,DeRefOf(Index(SCLK, 1)))    // Or SCLK to set bit
      Sleep(16)
    }

    // Power Pin
      \_SB.PCI0.SAT0.POFF(PWRG)

    RDCA(NCRN,LDIS_OFFSET,0xFFFFFFFF,0x10,ROOTPORT_WRITE)  // Store(1, LDIS) // Set Link Disable
    RDCA(NCRN,LDIS_OFFSET,0xFFFFFFEF,0x00,ROOTPORT_WRITE)  // Store(0, LDIS) // Toggle link disable
    // Internally inform that we put device into D3 state.
    Store(3, ISD3)
    //Wake pin not needed for storage.
  }

  //
  // Method to put remapped device NVMx to D3hot state.
  //
  Method(NVD3,0,Serialized)
  {
    //
    // Return if RST Pcie Storage Remapping is disabled
    //
    If(LEqual(NITV,0))
    {
      Return(0)
    }

    //
    // Store Endpoint CMD and remapped BAR for CNRS() restoration
    //
    Store(RDCA(NCRN,0x4,0x0,0x0,ENDPOINT_READ),PCMD)
    If(LEqual(NITV,1)) // Store BAR5 if Endpoint is AHCI Interface
    {
      Store(0x24,PRBI)
      Store(RDCA(NCRN,0x24,0x0,0x0,ENDPOINT_READ),PRBD)
    }
    ElseIf(LEqual(NITV,2)) // Store BAR0 if Endpoint is NVMe Interface
    {
      Store(0x10,PRBI)
      Store(RDCA(NCRN,0x10,0x0,0x0,ENDPOINT_READ),PRBD)
      #ifndef MINTREE_FLAG
      //Get MSI-X capability pointer (0x33C)
      OperationRegion(MCRC, SystemMemory, Add(\_SB.PCI0.GPCB(),Add(0xB8000, R_PCH_RST_PCIE_STORAGE_MXCRC)), 0x4)
      Field(MCRC,AnyAcc, NoLock, Preserve)
      {
        SCSO, 8,
        , 8,
        TCSO, 8,
        , 7,
        RE, 1,
      }
      Store(RDCA(NCRN,TCSO,0x0,0x0,ENDPOINT_READ), MXIE)
      #endif //MINTREE_FLAG
    }
    // Set endpoint device PM register to D3hot state.
    RDCA(NCRN,Add(NPMV,0x04),0xFFFFFFFC,0x3,ENDPOINT_WRITE)
    // Set root port PM register to D3hot state.
    RDCA(NCRN,0xA4,0xFFFFFFFC,0x3,ROOTPORT_WRITE)
    Return(1)
  }

  //
  // Method to put remapped device NVMx to D0 state.
  //
  Method(NVD0,0,Serialized)
  {
    //
    // Return if RST Pcie Storage Remapping is disabled
    //
    If(LEqual(NITV,0))
    {
      Return(0)
    }

    // Set root port PM register to D0 state..
    RDCA(NCRN,0xA4,0xFFFFFFFC,0x0,ROOTPORT_WRITE)

    // Set endpoint device PM register to D0 state.
    RDCA(NCRN,Add(NPMV,0x04),0xFFFFFFFC,0x0,ENDPOINT_WRITE)

    //
    // Check NSR bit in PMCS
    // If this bit is 0, invoke CNRS() to perform restoration on the remapped device and hidden root port
    //
    // Note: This does not work, value of PMC is 0x8 on boot time and in RTD3 scenario.
    // Store(RDCA(NCRN,Add(NPMV,0x04),0x0,0x0,ENDPOINT_READ),Local0)

    // We only allow CNRS to execute if NVD3 was executed previously.
    // (_PS0 also executes at OS startup, we don't want to execute CNRS at that point)

    CNRS()
    //Restore endpint interrupt bit
    If(LEqual(NITV,2)) // If Endpoint is NVMe Interface
    {
      #ifndef MINTREE_FLAG
      // offset 0x33C
      OperationRegion(MCRC, SystemMemory, Add(\_SB.PCI0.GPCB(), Add(0xB8000, R_PCH_RST_PCIE_STORAGE_MXCRC)), 0x4)
      Field(MCRC,AnyAcc, NoLock, Preserve)
      {
        SCSO, 8,
        , 8,
        TCSO, 8,
        , 7,
        RE, 1,
      }

      RDCA(NCRN,TCSO,0xFFFFFFFF,And(MXIE, 0x80000000),ENDPOINT_WRITE)
      ADBG("NVD0:  MSIXe")
      #endif //MINTREE_FLAG
    }
    Else
    {
    }
    Return(1)

  }
  //
  // AdvancedFeaturesEnd
  //


  //
  // Restore of Remapped Device and Hidden Root Port
  // This method is called after the endpoint is to be power ungated (D3-cold to D0 unitialized)
  //
  Method(CNRS, 0, Serialized)
  {
    Store("[ACPI RST] Restore Remapped Device and Hidden RP context |start", Debug)
    ADBG(Concatenate("CNRSs ", ToDecimalString(Timer())))
    //
    // Return if RST Pcie Storage Remapping is disabled
    //
    If(LEqual(NITV,0))
    {
       Return()
    }

    //
    // Clear all BARs in Remapped Device
    //
    RDCA(NCRN,PCI_CARD_BASE_ADDR0,0x0,0x0,ENDPOINT_WRITE)
    RDCA(NCRN,PCI_CARD_BASE_ADDR1,0x0,0x0,ENDPOINT_WRITE)
    RDCA(NCRN,PCI_CARD_BASE_ADDR2,0x0,0x0,ENDPOINT_WRITE)
    RDCA(NCRN,PCI_CARD_BASE_ADDR3,0x0,0x0,ENDPOINT_WRITE)
    RDCA(NCRN,PCI_CARD_BASE_ADDR4,0x0,0x0,ENDPOINT_WRITE)
    RDCA(NCRN,PCI_CARD_BASE_ADDR5,0x0,0x0,ENDPOINT_WRITE)

    //
    // Restore remapped BAR and Endpoint CMD
    //
    RDCA(NCRN,PRBI,0x0,PRBD,ENDPOINT_WRITE)
    RDCA(NCRN,0x4,0xFFFFFFF8,PCMD,ENDPOINT_WRITE)

    //
    // Restore of Remapped Device L1 Substate if this Capability is supported
    //
    If(LNotEqual(NL1V,0))
    {
      RDCA(NCRN,Add(NL1V,0x0C),0xFFFFFF00,ND2V,ENDPOINT_WRITE)
      RDCA(NCRN,Add(NL1V,0x08),0x0000000F,And(ND1V,0xFFFFFFF0),ENDPOINT_WRITE)
      RDCA(NCRN,Add(NL1V,0x08),0xFFFFFFFF,ND1V,ENDPOINT_WRITE)
    }

    //
    // Restore of Remapped Device LTR if this Capability is supported
    //
    If(LNotEqual(NLRV,0))
    {
      RDCA(NCRN,Add(NLRV,0x04),0xFFFFFFFF,NLDV,ENDPOINT_WRITE)
    }

    //
    // Restore of Remapped Device Link Control's "Enable Clock Power Management" field and "Common Clock Configuration" field
    //
    RDCA(NCRN,Add(NPCV,0x10),0xFFFFFEBF,And(NEAV,0xFFFC),ENDPOINT_WRITE)

    //
    // Restore of Remapped Device Device Control 2 field
    //
    RDCA(NCRN,Add(NPCV,0x28),0xFFFFFBFF,NECV,ENDPOINT_WRITE)

    //
    // Restore of Remapped Device Device Control field
    //
    RDCA(NCRN,Add(NPCV,0x8),0xFFFFFF1F,NEBV,ENDPOINT_WRITE)

    //
    // Restore of Hidden Root Port field
    //
    RDCA(NCRN,0x68,0xFFFFFBFF,NRAV,ROOTPORT_WRITE)

    //
    // Check CCC bit
    // If this bit is 1, perform link retrain by setting the "Retrain Link" bit
    //
    If(LEqual(And(NEAV,0x40),0x40))
    {
      RDCA(NCRN,0x50,0xFFFFFFDF,0x20,ROOTPORT_WRITE)
      //
      // Poll PCIe Link Active status till it is active
      //
      ADBG(Concatenate("CNRSw ", ToDecimalString(Timer())))
      while(LEqual(And(RDCA(NCRN,0x52,0x0,0x0,ROOTPORT_READ),0x2000),0))
      {
        Stall(10)
      }
    }
    ADBG(Concatenate("CNRSx ", ToDecimalString(Timer())))

    //
    // Restore of Remapped Device Link Control's "Active State Link PM Control" field
    //
    RDCA(NCRN,Add(NPCV,0x10),0xFFFFFFFC,And(NEAV,0x0003),ENDPOINT_WRITE)

    //
    // Restore of Remapped Device related device BAR for the MSI-X Table BAR if the device supports unique MSI-X Table BAR
    //
    If(LNotEqual(NMVV,0))
    {
      RDCA(NCRN,NMBV,0x0,NMVV,ENDPOINT_WRITE)
    }

    //
    // Restore of Remapped Device related device BAR for the MSI-X PBA BAR if the device supports unique MSI-X PBA BAR
    //
    If(LNotEqual(NPVV,0))
    {
      RDCA(NCRN,NPBV,0x0,NPVV,ENDPOINT_WRITE)
    }

    ADBG(Concatenate("CNRSe ", ToDecimalString(Timer())))
    Store("[ACPI RST] Restore Remapped Device and Hidden RP context |complete", Debug)
  }

