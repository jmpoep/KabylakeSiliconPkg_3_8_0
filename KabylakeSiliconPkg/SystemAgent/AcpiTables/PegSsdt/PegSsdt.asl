/** @file
  This file contains the PEG SSDT Table ASL code.
  It defines a SSDT table for PEG ports which will be consumed by
  DT and HALO boards (PCH H series).

 @copyright
  INTEL CONFIDENTIAL
  Copyright 2015 - 2018 Intel Corporation.

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
  "PegSsdt.aml",
  "SSDT",
  2,
  "PegSsdt",
  "PegSsdt",
  0x1000
  )
{

  External(\SGMD)
  External(\SGGP)
  External(\HRE0)
  External(\HRG0)
  External(\HRA0)
  External(\PWE0)
  External(\PWG0)
  External(\PWA0)
  External(\P1GP)
  External(\HRE1)
  External(\HRG1)
  External(\HRA1)
  External(\PWE1)
  External(\PWG1)
  External(\PWA1)
  External(\P2GP)
  External(\HRE2)
  External(\HRG2)
  External(\HRA2)
  External(\PWE2)
  External(\PWG2)
  External(\PWA2)
  External(\DLPW)
  External(\DLHR)
  External(\EECP)
  External(\XBAS)
  External(\GBAS)
  External(\LTRX)
  External(\OBFX)
  External(\LTRY)
  External(\OBFY)
  External(\LTRZ)
  External(\OBFZ)
  External(\P0UB)
  External(\P1UB)
  External(\P2UB)
  External(\PCSL)
  External(\PBGE)
  External(\CPEX)
  External(\EEC1)
  External(\EEC2)
  External(\SBN0)
  External(\SBN1)
  External(\SBN2)
  External(\P0WK)
  External(\P1WK)
  External(\P2WK)
  External(\AR0A)
  External(\AR0B)
  External(\AR02)
  External(\PR0A)
  External(\PR0B)
  External(\PR02)
  External(\PICM)
  External(\SNSL)
  External(\SMSL)
  External(\OSYS)
  External(\ECR1)
  External(\CKM0)
  External(\CKM1)
  External(\CKM2)
//
// KblGBegin
//
  External(\DLAO)
  External(\DLAL)
  External(\GSCE)
//
// KblGEnd
//
  External(P8XH, MethodObj)
  External(PCRA,MethodObj)
  External(PCRO,MethodObj)
  External(\_SB.PCI0, DeviceObj)
  External(\_SB.PCI0.PEG0, DeviceObj)
  External(\_SB.PCI0.PEG0.PEGP, DeviceObj)
  External(\_SB.PCI0.PEG1, DeviceObj)
  External(\_SB.PCI0.PEG1.PEGP, DeviceObj)
  External(\_SB.PCI0.PEG2, DeviceObj)
  External(\_SB.PCI0.PEG2.PEGP, DeviceObj)
  External(\_SB.GGOV, MethodObj)
  External(\_SB.SHPO, MethodObj)
  External(\_SB.ISME, MethodObj)
  External(\_SB.CAGS, MethodObj)
  External(\_SB.SGOV, MethodObj)
  External(\GPRW, MethodObj)

  Include ("PegOnOff.asl")

}
