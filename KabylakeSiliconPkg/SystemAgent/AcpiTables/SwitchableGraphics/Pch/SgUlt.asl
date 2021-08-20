/** @file
  This file contains the system BIOS switchable graphics code for
  ULT.

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
    "SgUlt.aml",
    "SSDT",
    2,
    "SgRef",
    "SgUlt",
    0x1000
    )
{
External(\_SB.PCI0.RP09, DeviceObj)
External(\_SB.PCI0.RP09.PEGP, DeviceObj)
External(\_SB.PCI0.HGON, MethodObj)
External(\_SB.PCI0.HGOF, MethodObj)
External(GPRW, MethodObj)
External(OSYS)

  Scope(\_SB.PCI0.RP09)
  {
    //-----------------------------------------
    // Runtime Device Power Management - Begin
    //-----------------------------------------
    //
    // Name: PC09
    // Description: Declare a PowerResource object for RP09 slot device
    //
    PowerResource(PC09, 0, 0) {
      Name(_STA, One)
      Method(_ON, 0, Serialized) {
        If(LNotEqual(OSYS,2009)) {
          \_SB.PCI0.HGON(9)
          Store(One, _STA)
        }
      }
      Method(_OFF, 0, Serialized) {
        If(LNotEqual(OSYS,2009)) {
          \_SB.PCI0.HGOF(9)
          Store(Zero, _STA)
        }
      }
    } //End of PowerResource(PC09, 0, 0)

    Name(_PR0,Package(){PC09})
    Name(_PR2,Package(){PC09})
    Name(_PR3,Package(){PC09})

    Method(_S0W, 0) { Return(4) } //D3cold is supported

    //-----------------------------------------
    // Runtime Device Power Management - End
    //-----------------------------------------

    Device(PEGP) { // (PCI Express* -> B00:D29:F00) Slot Device D0F0
      Name(_ADR, 0x00000000)
      Method(_PRW, 0) { Return(GPRW(0x69, 4)) } // can wakeup from S4 state
    } // (PCI Express* -> B00:D29:F00) Slot Device D0F0

    Device(PEGA) { // (PCI Express* -> B00:D29:F01) Slot Device D0F1
      Name(_ADR, 0x00000001)
      Method(_PRW, 0) { Return(GPRW(0x69, 4)) } // can wakeup from S4 state
    } // (PCI Express* -> B00:D29:F01) Slot Device D0F1
  }

  Scope(\_SB.PCI0.RP09.PEGP)
  {

    Method (_INI)
    {
        Store (0x0, \_SB.PCI0.RP09.PEGP._ADR)
    }

    Method(_ON,0,Serialized)
    {
      \_SB.PCI0.HGON(9)

      //Ask OS to do a PnP rescan
      Notify(\_SB.PCI0.RP09,0)

      Return ()
    }

    Method(_OFF,0,Serialized)
    {
      \_SB.PCI0.HGOF(9)

      //Ask OS to do a PnP rescan
      Notify(\_SB.PCI0.RP09,0)

      Return ()
    }
  }
}
