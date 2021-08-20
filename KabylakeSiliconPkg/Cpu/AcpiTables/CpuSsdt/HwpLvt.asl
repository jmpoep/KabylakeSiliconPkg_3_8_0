/** @file
  This file contains the HWP GPE Handler ASL code.
  Method HL62 should be called by platform ASL SW SCI event .

 @copyright
  INTEL CONFIDENTIAL
  Copyright 2012 - 2017 Intel Corporation.

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
  "HwpLvt.aml",
  "SSDT",
  2,
  "PmRef",
  "HwpLvt",
  0x3000
  )
{
External(\_PR.PR00, DeviceObj)
External(\_PR.PR01, ProcessorObj)
External(\_PR.PR02, ProcessorObj)
External(\_PR.PR03, ProcessorObj)
External(\_PR.PR04, ProcessorObj)
External(\_PR.PR05, ProcessorObj)
External(\_PR.PR06, ProcessorObj)
External(\_PR.PR07, ProcessorObj)
External(\_PR.PR08, ProcessorObj)
External(\_PR.PR09, ProcessorObj)
External(\_PR.PR10, ProcessorObj)
External(\_PR.PR11, ProcessorObj)
External(\_PR.PR12, ProcessorObj)
External(\_PR.PR13, ProcessorObj)
External(\_PR.PR14, ProcessorObj)
External(\_PR.PR15, ProcessorObj)
External(\TCNT, FieldUnitObj)

Scope(\_GPE) {
  Method(HLVT,0,Serialized) {
    Switch(ToInteger(TCNT)){
      Case(16){
        Notify(\_PR.PR00, 0x83)
        Notify(\_PR.PR01, 0x83)
        Notify(\_PR.PR02, 0x83)
        Notify(\_PR.PR03, 0x83)
        Notify(\_PR.PR04, 0x83)
        Notify(\_PR.PR05, 0x83)
        Notify(\_PR.PR06, 0x83)
        Notify(\_PR.PR07, 0x83)
        Notify(\_PR.PR08, 0x83)
        Notify(\_PR.PR09, 0x83)
        Notify(\_PR.PR10, 0x83)
        Notify(\_PR.PR11, 0x83)
        Notify(\_PR.PR12, 0x83)
        Notify(\_PR.PR13, 0x83)
        Notify(\_PR.PR14, 0x83)
        Notify(\_PR.PR15, 0x83)
      }
      Case(14){
        Notify(\_PR.PR00, 0x83)
        Notify(\_PR.PR01, 0x83)
        Notify(\_PR.PR02, 0x83)
        Notify(\_PR.PR03, 0x83)
        Notify(\_PR.PR04, 0x83)
        Notify(\_PR.PR05, 0x83)
        Notify(\_PR.PR06, 0x83)
        Notify(\_PR.PR07, 0x83)
        Notify(\_PR.PR08, 0x83)
        Notify(\_PR.PR09, 0x83)
        Notify(\_PR.PR10, 0x83)
        Notify(\_PR.PR11, 0x83)
        Notify(\_PR.PR12, 0x83)
        Notify(\_PR.PR13, 0x83)
      }
      Case(12){
        Notify(\_PR.PR00, 0x83)
        Notify(\_PR.PR01, 0x83)
        Notify(\_PR.PR02, 0x83)
        Notify(\_PR.PR03, 0x83)
        Notify(\_PR.PR04, 0x83)
        Notify(\_PR.PR05, 0x83)
        Notify(\_PR.PR06, 0x83)
        Notify(\_PR.PR07, 0x83)
        Notify(\_PR.PR08, 0x83)
        Notify(\_PR.PR09, 0x83)
        Notify(\_PR.PR10, 0x83)
        Notify(\_PR.PR11, 0x83)
      }
      Case(10){
        Notify(\_PR.PR00, 0x83)
        Notify(\_PR.PR01, 0x83)
        Notify(\_PR.PR02, 0x83)
        Notify(\_PR.PR03, 0x83)
        Notify(\_PR.PR04, 0x83)
        Notify(\_PR.PR05, 0x83)
        Notify(\_PR.PR06, 0x83)
        Notify(\_PR.PR07, 0x83)
        Notify(\_PR.PR08, 0x83)
        Notify(\_PR.PR09, 0x83)
      }
      Case(8){
        Notify(\_PR.PR00, 0x83)
        Notify(\_PR.PR01, 0x83)
        Notify(\_PR.PR02, 0x83)
        Notify(\_PR.PR03, 0x83)
        Notify(\_PR.PR04, 0x83)
        Notify(\_PR.PR05, 0x83)
        Notify(\_PR.PR06, 0x83)
        Notify(\_PR.PR07, 0x83)
      }
      Case(7){
        Notify(\_PR.PR00, 0x83)
        Notify(\_PR.PR01, 0x83)
        Notify(\_PR.PR02, 0x83)
        Notify(\_PR.PR03, 0x83)
        Notify(\_PR.PR04, 0x83)
        Notify(\_PR.PR05, 0x83)
        Notify(\_PR.PR06, 0x83)
      }
      Case(6){
        Notify(\_PR.PR00, 0x83)
        Notify(\_PR.PR01, 0x83)
        Notify(\_PR.PR02, 0x83)
        Notify(\_PR.PR03, 0x83)
        Notify(\_PR.PR04, 0x83)
        Notify(\_PR.PR05, 0x83)
      }
      Case(5){
        Notify(\_PR.PR00, 0x83)
        Notify(\_PR.PR01, 0x83)
        Notify(\_PR.PR02, 0x83)
        Notify(\_PR.PR03, 0x83)
        Notify(\_PR.PR04, 0x83)
      }
      Case(4){
        Notify(\_PR.PR00, 0x83)
        Notify(\_PR.PR01, 0x83)
        Notify(\_PR.PR02, 0x83)
        Notify(\_PR.PR03, 0x83)
      }
      Case(3){
        Notify(\_PR.PR00, 0x83)
        Notify(\_PR.PR01, 0x83)
        Notify(\_PR.PR02, 0x83)
      }
      Case(2){
        Notify(\_PR.PR00, 0x83)
        Notify(\_PR.PR01, 0x83)
      }
      Default{
        Notify(\_PR.PR00, 0x83)
      }
    }
  }
} //end Scope(\_GPE)
}// end of definition block
