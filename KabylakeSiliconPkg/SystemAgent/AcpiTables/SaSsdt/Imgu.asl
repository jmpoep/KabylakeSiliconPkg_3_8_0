/** @file
  This file contains the device definition of the System Agent
  ACPI reference code.
  Currently defines the device objects for the
  System Agent Sky Cam IMGU device

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

//
// Device SKC0 is the SkyCam AVStream virtual device and it appears under _SB
//
Scope (\_SB) {
  Device(SKC0)
  {
    Name (_HID, "INT3470") // This is an the ACPI ID of SkyCam AVStream device driver
    /*
      Allows OS to not yellow bang if Intel do not
      provide driver for that OS version, otherwise
      if we have driver for every OS, then no need
      for _CID at all.
    */
    Name(_CID, EISAID("PNP0C02"))
    /*
      The following is a technique that may be used (per OEM needs) to prevent
      the load of the camera device in one of the following cases:
      - Camera device and the CIO2 device are fused out
      - If the platform setup requires that in a secured boot the camera device
      should not be enabled
    */
    Method (_STA, 0, NotSerialized) {
      If(LEqual(IMTP,2)){ // ACPI need report ISP0 as available device
        Return (0xF)
      } Else{             // ACPI should NOT report ISP0 as available device
        Return (0x0)
      }
    }
  }
}

//
// Device SKC0 is the SkyCam AVStream virtual device and it appears under GFX0
//
Scope (\_SB.PCI0.GFX0)
{
  Device(SKC0) // SkyCam AVStream virtual device name
  {
    /*
      The identifier for this device (Same as in
      _DOD above). This is required so GFX driver can
      associate a matching device ID for the AVStream
      driver and provide it to PnP (this device ID
      should appear in the INF file of the AVStream
      driver).
    */
    Name(_ADR, 0x0000CA00)
    /*
      The following is a technique that may be used (per OEM needs) to prevent
      the load of the camera device in one of the following cases:
      - Camera device and the CIO2 device are fused out
      - If the platform setup requires that in a secured boot the camera device
      should not be enabled
    */
    Method (_STA, 0, NotSerialized) {
      If(LEqual(IMTP,1)){ // IGFX need report ISP0 as GFX0 child
        Return (0xF)
      } Else { // IGFX should NOT report ISP0 as GFX0 child
        Return (0x0)
      }
    }
  } // End SKC0
} // end I.G.D
