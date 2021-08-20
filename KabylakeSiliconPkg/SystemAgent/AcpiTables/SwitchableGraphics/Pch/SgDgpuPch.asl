/** @file
  This file contains the system BIOS switchable graphics code for
  PCH DGPU.

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
DefinitionBlock (
    "SgPch.aml",
    "SSDT",
    2,
    "SgRef",
    "SgPch",
    0x1000
    )
{
External(P8XH, MethodObj)
External(\_SB.PCI0, DeviceObj)
External(\_SB.PCI0.RP09._ADR, MethodObj)
External(\_SB.PCI0.RP01._ADR, MethodObj)
External(\_SB.SGOV, MethodObj)
External(\_SB.GGOV, MethodObj)
External(\RPA9)
External(\RPA1)
External(\EECP)
External(\XBAS)
External(\GBAS)
External(\SGMD)
External(\SGGP)
External(\DLPW)
External(\DLHR)
External(\HRE0)
External(\HRG0)
External(\HRA0)
External(\PWE0)
External(\PWG0)
External(\PWA0)

  Scope(\_SB.PCI0)
  {
    Name (IVID, 0xFFFF) //Invalid Vendor ID
    Name (ELCT, 0x00000000)
    Name (HVID, 0x0000)
    Name (HDID, 0x0000)
    Name (TCNT, 0)
    Name (LDLY, 100) //100 ms
    Name (RPIX, 0) //Root Port index

    //
    // Define a Memory Region that will allow access to the PCH root port 9
    // Register Block.
    //
    OperationRegion(RPC9,SystemMemory,Add(Add(\XBAS,ShiftLeft(ShiftRight(And(\_SB.PCI0.RP09._ADR(),0xFF0000),0x10),0xF)), ShiftLeft(And(\RPA9,0xF),12)),0x1000)
    Field(RPC9,DWordAcc,NoLock,Preserve)
    {
        Offset(0),
        PVI9,   16,
        PDI9,   16,
        Offset(0x18),
        PRB9,   8,                      // Primary Bus Number
        SCB9,   8,                      // Secondary Bus Number
        Offset(0x50),                   // LCTL - Link Control Register of (PCI Express* -> B00:D29:F00)
        ASP9,   2,                      // 1:0, ASPM //Not referenced in code
        ,       2,
        LKD9,   1,                      // Link Disable
        Offset(0x328),                  //PCIESTS1 - PCI Express Status 1
        ,       19,
        LKS9,   4,                      //Link Status (LNKSTAT) {22:19}
    }

    OperationRegion (RTP9, SystemMemory, Add(\XBAS,ShiftLeft(SCB9,20)), 0xF0)
    Field(RTP9, AnyAcc, Lock, Preserve)
    {
        Offset(0x0),
        DVI9, 16,
        Offset(0xB),
        CBC9, 8,
        Offset(0x2C),
        SVI9, 16,
        SDI9, 16,
    }

    OperationRegion(PCA9, SystemMemory, Add(Add(\XBAS,ShiftLeft(SCB9,20)),\EECP),0x14)
    Field(PCA9,DWordAcc, NoLock,Preserve)
    {
        Offset(0x10),
        LCT9,   16,                      // Link Control register
    }

    OperationRegion(PCB9, SystemMemory, Add(Add(Add(\XBAS,ShiftLeft(SCB9,20)),0x1000),\EECP),0x14)
    Field(PCB9,DWordAcc, NoLock,Preserve)
    {
        Offset(0x10),
        LCTX,   16,                      // Link Control register
    }


    //
    // Define a Memory Region that will allow access to the PCH root port 1
    // Register Block.
    //
    OperationRegion(RPC1,SystemMemory,Add(Add(\XBAS,ShiftLeft(ShiftRight(And(\_SB.PCI0.RP01._ADR(),0xFF0000),0x10),0xF)), ShiftLeft(And(\RPA1,0xF),12)),0x1000)
    Field(RPC1,DWordAcc,NoLock,Preserve)
    {
        Offset(0),
        PVI1,   16,
        PDI1,   16,
        Offset(0x18),
        PRB1,   8,                      // Primary Bus Number
        SCB1,   8,                      // Secondary Bus Number
        Offset(0x50),                   // LCTL - Link Control Register of (PCI Express* -> B00:D28:F00)
        ASP1,   2,                      // 1:0, ASPM //Not referenced in code
        ,       2,
        LKD1,   1,                      // Link Disable
        Offset(0x328),                  //PCIESTS1 - PCI Express Status 1
        ,       19,
        LKS1,   4,                      //Link Status (LNKSTAT) {22:19}
    }

    OperationRegion (RTP1, SystemMemory, Add(\XBAS,ShiftLeft(SCB1,20)), 0xF0)
    Field(RTP1, AnyAcc, Lock, Preserve)
    {
        Offset(0x0),
        DVI1, 16,
        Offset(0xB),
        CBC1, 8,
        Offset(0x2C),
        SVI1, 16,
        SDI1, 16,
    }

    OperationRegion(PCA1, SystemMemory, Add(Add(\XBAS,ShiftLeft(SCB1,20)),\EECP),0x14)
    Field(PCA1,DWordAcc, NoLock,Preserve)
    {
        Offset(0x10),
        LCT1,   16,                      // Link Control register
    }

    OperationRegion(PCB1, SystemMemory, Add(Add(Add(\XBAS,ShiftLeft(SCB1,20)),0x1000),\EECP),0x14)
    Field(PCB1,DWordAcc, NoLock,Preserve)
    {
        Offset(0x10),
        LCTY,   16,                      // Link Control register
    }

    //
    // Name: HGON
    // Description: Function to put the Pcie Endpoint in ON state
    // Input: Arg0 -> Root Port Number
    // Return: Nothing
    //
    Method(HGON,1,Serialized)
    {
        Store(Arg0, RPIX)

        If (LEqual(CCHK(1, RPIX), 0))
        {
          Return ()
        }

        //ACTION:
        //........................................................................................
        //While powering up the slot again, the only requirement is that the Reset# should be
        //de-asserted 100ms after the power to slot is up (Standard requirement as per PCIe spec).

        //Note:
        //Before power enable, and for 100ms after power enable, the reset should be in hold condition.
        //The 100 ms time is given for power rails and clocks to become stable.
        //So during this period, reset must not be released.
        //........................................................................................

        //Power on the dGPU card
        SGPO(HRE0, HRG0, HRA0, 1)                  //Assert dGPU_HOLD_RST# {Hold the dGPU Reset}
        SGPO(PWE0, PWG0, PWA0, 1)                  //Assert dGPU_PWR_EN# {Power on the dGPU}
        Sleep(DLPW)                                // Wait for 'given'ms if dGPU_PWROK has h/w issues
        SGPO(HRE0, HRG0, HRA0, 0)                  //Deassert dGPU_HOLD_RST# {Release the dGPU Reset}
        Sleep(DLHR)                                // Wait for 'given'ms

        //Enable x4 Link
        //This bit should already be set to 0 in the _Off method. But do it anyway.
        If (LEqual(RPIX, 1)) {
          Store(0,LKD1)
        } ElseIf (LEqual(RPIX, 9)) {
            Store(0,LKD9)
        }

        //Wait until link has trained to x4
        Store(0, TCNT)
        While(LLess(TCNT, LDLY))
        {
          If (LEqual(RPIX, 1)) {
            If(LGreaterEqual(LKS1,7)) {
              Break
            }
          } ElseIf (LEqual(RPIX, 9)) {
              If(LGreaterEqual(LKS9,7)) {
                Break
              }
          }
          Sleep(16) //In some OS one tick is equal to 1/64 second (15.625ms)
          Add(TCNT, 16, TCNT)
        }

        // Re-store the DGPU SSID &
        // Re-store the Link Control register - Common Clock Control and ASPM
        If (LEqual(RPIX, 1)) {
            Store(HVID,SVI1)
            Store(HDID,SDI1)
            Or(And(ELCT,0x0043),And(LCT1,0xFFBC),LCT1)
            Or(And(ELCT,0x0043),And(LCTY,0xFFBC),LCTY)
        } ElseIf (LEqual(RPIX, 9)) {
            Store(HVID,SVI9)
            Store(HDID,SDI9)
            Or(And(ELCT,0x0043),And(LCT9,0xFFBC),LCT9)
            Or(And(ELCT,0x0043),And(LCTX,0xFFBC),LCTX)
        }

        Return ()
    }

    //
    // Name: HGOF
    // Description: Function to put the Pcie Endpoint in OFF state
    // Input: Arg0 -> Root Port index
    // Return: Nothing
    //
    Method(HGOF,1,Serialized)
    {
        Store(Arg0, RPIX)

        If (LEqual(CCHK(0, RPIX), 0))
        {

          Return ()
        }

        //ACTION:
        //........................................................................................
        //To turn off the power to the slot, all you would need to do is assert the RESET#
        //and then take off the power using the power enable GPIO.
        //Once the power goes off, the clock request from the slot to the PCH is also turned off,
        //so no clocks will be going to the PCIe slot anymore.
        //........................................................................................

        // Save the Link Control register, DGPU SSID & Force disable the x4 link
        If (LEqual(RPIX, 1)) {
          Store(LCT1,ELCT)
          Store(SVI1,HVID)
          Store(SDI1,HDID)
          Store(1, LKD1)
        } ElseIf (LEqual(RPIX, 9)) {
            Store(LCT9,ELCT)
            Store(SVI9,HVID)
            Store(SDI9,HDID)
            Store(1, LKD9)
        }


        //Wait till link is actually in disabled state
        Store(0, TCNT)
        While(LLess(TCNT, LDLY))
        {
          If (LEqual(RPIX, 1)) {
            If(LGreaterEqual(LKS1,0)) {
              Break
            }
          } ElseIf (LEqual(RPIX, 9)) {
              If(LGreaterEqual(LKS9,0)) {
                Break
              }
          }
          Sleep(16) //In some OS one tick is equal to 1/64 second (15.625ms)
          Add(TCNT, 16, TCNT)
        }

        //Power-off the dGPU card
        SGPO(HRE0, HRG0, HRA0, 1)                   // Assert dGPU_HOLD_RST# (PERST#) {Hold the dGPU Reset}
        SGPO(PWE0, PWG0, PWA0, 0)                   // Deassert dGPU_PWR_EN#  {Power off the dGPU}

        Return ()
    }

    //
    // Name: SGPO [SG GPIO Write]
    // Description: Function to write into GPIO
    // Input: Arg0 -> Expander Number
    //        Arg1 -> Gpio Number
    //        Arg2 -> Active Information
    //        Arg3 -> Value to write
    // Return: Nothing
    //
    Method(SGPO, 4, Serialized)
    {
      // Invert if Active Low
      If (LEqual(Arg2,0))
      {
        Not(Arg3, Arg3)
        And(Arg3, 0x01, Arg3)
      }
      If (LEqual(SGGP, 0x01))
      {
       // PCH Based GPIO
        If (CondRefOf(\_SB.SGOV))
        {
          \_SB.SGOV(Arg1, Arg3)
        }
      }
    } // End of Method(SGPO)

    //
    // Name: SGPI [PCIe GPIO Read]
    // Description: Function to Read from GPIO
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
      }
      And(Local0, 0x01, Local0)

      Return(Local0)

    } // End of Method(SGPI)

    //
    // Name: CCHK
    // Description: Function to check whether _ON/_OFF sequence is allowed to execute for the given RP09 controller or not
    // Input: Arg0 -> 0 means _OFF sequence, 1 means _ON sequence
    // Input: Arg1 -> Root Port Index
    // Return: 0 - Don't execute the flow, 1 - Execute the flow
    //
    Method(CCHK,2)
    {

      //Check for RP09 controller presence
      If (LEqual(Arg1, 1)) {
        If(LEqual(PVI1, IVID)) {
          Return(0)
        }
      } ElseIf (LEqual(Arg1, 9)) {
          If(LEqual(PVI9, IVID)) {
            Return(0)
          }
      }
      //If Endpoint is not present[already disabled] before executing _OFF then don't call the _OFF method
      //If Endpoint is present[already enabled] before executing _ON then don't call the _ON method
      If(LEqual(Arg0, 0))
      {
        //_OFF sequence condition check
        If(LEqual(SGPI(SGGP, PWE0, PWG0, PWA0), 0))
        {
          Return(0)
        }
      }
      ElseIf(LEqual(Arg0, 1))
      {
        //_ON sequence condition check
        If(LEqual(SGPI(SGGP, PWE0, PWG0, PWA0), 1))
        {
          Return(0)
        }
      }

      Return(1)
    } // End of Method(CCHK,2)
  } // End of Scope
}

