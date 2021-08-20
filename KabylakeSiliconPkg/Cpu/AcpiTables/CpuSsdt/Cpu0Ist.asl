/** @file
  Intel Processor Power Management ACPI Code.

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

DefinitionBlock (
  "CPU0IST.aml",
  "SSDT",
  0x02,
  "PmRef",
  "Cpu0Ist",
  0x3000
  )
{
  External(\_SB.OSCP, IntObj)
  External(\PC00, IntObj)
  External(\TCNT, FieldUnitObj)
  External(\_PR.CFGD, FieldUnitObj)
  External(\_PR.CPPC, FieldUnitObj)
  External(\_PR.PR00, DeviceObj)

  Scope(\_PR.PR00)
  {
    Method(_PPC, 0)
    {
      Return(\_PR.CPPC) // return max P-state available
    }

    //
    // NOTE:  For CMP systems; this table is not loaded unless
    //        the required driver support is present.
    //        So, we do not check for those cases here.
    //
    // CFGD[0]  = EIST Capable/Enabled
    // PDCx[0]  = OS Capable of Hardware P-State control
    //
    Name(_PCT, Package()  // Native Mode
    {
      ResourceTemplate(){Register(FfixedHW, 0, 0, 0)},
      ResourceTemplate(){Register(FfixedHW, 0, 0, 0)}
    })

    //
    // Returns a list of supported processor performance states.
    //
    // \_SB.OSCP[10] = Platform-Wide OS Capable for no limit 16 P-states
    //
    Method(_PSS,0)
    {
      If(And(\_SB.OSCP,0x0400))
      {
        Return (TPSS)
      }
      Else
      {
        Return (LPSS)
      }
    }

    //
    // LPSS is for OS to support limit 16 P-states
    //
    Name(LPSS,Package()
    {
      Package(){0x80000000, 0x80000000, 0x80000000, 0x80000000, 0x80000000, 0x80000000},
      Package(){0x80000000, 0x80000000, 0x80000000, 0x80000000, 0x80000000, 0x80000000},
      Package(){0x80000000, 0x80000000, 0x80000000, 0x80000000, 0x80000000, 0x80000000},
      Package(){0x80000000, 0x80000000, 0x80000000, 0x80000000, 0x80000000, 0x80000000},
      Package(){0x80000000, 0x80000000, 0x80000000, 0x80000000, 0x80000000, 0x80000000},
      Package(){0x80000000, 0x80000000, 0x80000000, 0x80000000, 0x80000000, 0x80000000},
      Package(){0x80000000, 0x80000000, 0x80000000, 0x80000000, 0x80000000, 0x80000000},
      Package(){0x80000000, 0x80000000, 0x80000000, 0x80000000, 0x80000000, 0x80000000},
      Package(){0x80000000, 0x80000000, 0x80000000, 0x80000000, 0x80000000, 0x80000000},
      Package(){0x80000000, 0x80000000, 0x80000000, 0x80000000, 0x80000000, 0x80000000},
      Package(){0x80000000, 0x80000000, 0x80000000, 0x80000000, 0x80000000, 0x80000000},
      Package(){0x80000000, 0x80000000, 0x80000000, 0x80000000, 0x80000000, 0x80000000},
      Package(){0x80000000, 0x80000000, 0x80000000, 0x80000000, 0x80000000, 0x80000000},
      Package(){0x80000000, 0x80000000, 0x80000000, 0x80000000, 0x80000000, 0x80000000},
      Package(){0x80000000, 0x80000000, 0x80000000, 0x80000000, 0x80000000, 0x80000000},
      Package(){0x80000000, 0x80000000, 0x80000000, 0x80000000, 0x80000000, 0x80000000}
    })

    //
    // TPSS is for ACPI 6.0 and beyond support 255 states for no limit 16 P-states.
    // @TODO : Here has limitation that namespace size only could up to 99, over 99 will cause CpuSsdt load fail and P-state no cycling issue.
    //
    Name(TPSS,Package()
    {
      Package(){0x80000000, 0x80000000, 0x80000000, 0x80000000, 0x80000000, 0x80000000},
      Package(){0x80000000, 0x80000000, 0x80000000, 0x80000000, 0x80000000, 0x80000000},
      Package(){0x80000000, 0x80000000, 0x80000000, 0x80000000, 0x80000000, 0x80000000},
      Package(){0x80000000, 0x80000000, 0x80000000, 0x80000000, 0x80000000, 0x80000000},
      Package(){0x80000000, 0x80000000, 0x80000000, 0x80000000, 0x80000000, 0x80000000},
      Package(){0x80000000, 0x80000000, 0x80000000, 0x80000000, 0x80000000, 0x80000000},
      Package(){0x80000000, 0x80000000, 0x80000000, 0x80000000, 0x80000000, 0x80000000},
      Package(){0x80000000, 0x80000000, 0x80000000, 0x80000000, 0x80000000, 0x80000000},
      Package(){0x80000000, 0x80000000, 0x80000000, 0x80000000, 0x80000000, 0x80000000},
      Package(){0x80000000, 0x80000000, 0x80000000, 0x80000000, 0x80000000, 0x80000000},
      Package(){0x80000000, 0x80000000, 0x80000000, 0x80000000, 0x80000000, 0x80000000},
      Package(){0x80000000, 0x80000000, 0x80000000, 0x80000000, 0x80000000, 0x80000000},
      Package(){0x80000000, 0x80000000, 0x80000000, 0x80000000, 0x80000000, 0x80000000},
      Package(){0x80000000, 0x80000000, 0x80000000, 0x80000000, 0x80000000, 0x80000000},
      Package(){0x80000000, 0x80000000, 0x80000000, 0x80000000, 0x80000000, 0x80000000},
      Package(){0x80000000, 0x80000000, 0x80000000, 0x80000000, 0x80000000, 0x80000000},
      Package(){0x80000000, 0x80000000, 0x80000000, 0x80000000, 0x80000000, 0x80000000},
      Package(){0x80000000, 0x80000000, 0x80000000, 0x80000000, 0x80000000, 0x80000000},
      Package(){0x80000000, 0x80000000, 0x80000000, 0x80000000, 0x80000000, 0x80000000},
      Package(){0x80000000, 0x80000000, 0x80000000, 0x80000000, 0x80000000, 0x80000000},
      Package(){0x80000000, 0x80000000, 0x80000000, 0x80000000, 0x80000000, 0x80000000},
      Package(){0x80000000, 0x80000000, 0x80000000, 0x80000000, 0x80000000, 0x80000000},
      Package(){0x80000000, 0x80000000, 0x80000000, 0x80000000, 0x80000000, 0x80000000},
      Package(){0x80000000, 0x80000000, 0x80000000, 0x80000000, 0x80000000, 0x80000000},
      Package(){0x80000000, 0x80000000, 0x80000000, 0x80000000, 0x80000000, 0x80000000},
      Package(){0x80000000, 0x80000000, 0x80000000, 0x80000000, 0x80000000, 0x80000000},
      Package(){0x80000000, 0x80000000, 0x80000000, 0x80000000, 0x80000000, 0x80000000},
      Package(){0x80000000, 0x80000000, 0x80000000, 0x80000000, 0x80000000, 0x80000000},
      Package(){0x80000000, 0x80000000, 0x80000000, 0x80000000, 0x80000000, 0x80000000},
      Package(){0x80000000, 0x80000000, 0x80000000, 0x80000000, 0x80000000, 0x80000000},
      Package(){0x80000000, 0x80000000, 0x80000000, 0x80000000, 0x80000000, 0x80000000},
      Package(){0x80000000, 0x80000000, 0x80000000, 0x80000000, 0x80000000, 0x80000000},
      Package(){0x80000000, 0x80000000, 0x80000000, 0x80000000, 0x80000000, 0x80000000},
      Package(){0x80000000, 0x80000000, 0x80000000, 0x80000000, 0x80000000, 0x80000000},
      Package(){0x80000000, 0x80000000, 0x80000000, 0x80000000, 0x80000000, 0x80000000},
      Package(){0x80000000, 0x80000000, 0x80000000, 0x80000000, 0x80000000, 0x80000000},
      Package(){0x80000000, 0x80000000, 0x80000000, 0x80000000, 0x80000000, 0x80000000},
      Package(){0x80000000, 0x80000000, 0x80000000, 0x80000000, 0x80000000, 0x80000000},
      Package(){0x80000000, 0x80000000, 0x80000000, 0x80000000, 0x80000000, 0x80000000},
      Package(){0x80000000, 0x80000000, 0x80000000, 0x80000000, 0x80000000, 0x80000000}
    })

    Name (PSDF, 0)
    //
    // The _PSD object provides information to the OSPM related
    // to P-State coordination between processors in a multi-processor
    // configurations.
    //
    Method(_PSD,0)
    {
      If ( LNot(PSDF) )
      {
        Store (TCNT, Index(DerefOf(Index(HPSD, 0)),4))
        Store (TCNT, Index(DerefOf(Index(SPSD, 0)),4))
        Store (Ones, PSDF)
      }

      If(And(PC00,0x0800))
      {
        Return(HPSD)
      }
      Return(SPSD)
    }
    Name(HPSD,Package() // HW_ALL
    {
      Package(){5, 0, 0, 0xFE, 0x80}
    })
    Name(SPSD,Package() // SW_ALL
    {
      Package(){5, 0, 0, 0xFC, 0x80}
    })
  }
} // End of Definition Block

