/** @file
  Intel Processor Power Management IST ACPI Code.

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
  "APIST.aml",
  "SSDT",
  2,
  "PmRef",
  "ApIst",
  0x3000
  )
{
  External(\PC00, IntObj)
  External(\TCNT, FieldUnitObj)
  External(\_PR.PR00, DeviceObj)
  External(\_PR.PR01, DeviceObj)
  External(\_PR.PR02, DeviceObj)
  External(\_PR.PR03, DeviceObj)
  External(\_PR.PR04, DeviceObj)
  External(\_PR.PR05, DeviceObj)
  External(\_PR.PR06, DeviceObj)
  External(\_PR.PR07, DeviceObj)
  External(\_PR.PR08, DeviceObj)
  External(\_PR.PR09, DeviceObj)
  External(\_PR.PR10, DeviceObj)
  External(\_PR.PR11, DeviceObj)
  External(\_PR.PR12, DeviceObj)
  External(\_PR.PR13, DeviceObj)
  External(\_PR.PR14, DeviceObj)
  External(\_PR.PR15, DeviceObj)
  External(\_PR.PR00._PPC, MethodObj)
  External(\_PR.PR00._PCT, MethodObj)
  External(\_PR.PR00._PSS, MethodObj)

  Scope(\_PR.PR01)
  {
    Method(_PPC,0)
    {
      Return(\_PR.PR00._PPC)  // Return P0 _PPC value.
    }

    Method(_PCT,0)
    {
      Return(\_PR.PR00._PCT)  // Return P0 _PCT.
    }

    Method(_PSS,0)
    {
      //Return the same table as PR00 for CMP cases.
      Return(\_PR.PR00._PSS)
    }

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

  Scope(\_PR.PR02)
  {
    Method(_PPC,0)
    {
      Return(\_PR.PR00._PPC)  // Return PR00 _PPC value.
    }

    Method(_PCT,0)
    {
      Return(\_PR.PR00._PCT)  // Return PR00 _PCT value.
    }

    Method(_PSS,0)
    {
      Return(\_PR.PR00._PSS)  // Return PR00 _PSS.
    }

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


  Scope(\_PR.PR03)
  {
    Method(_PPC,0)
    {
      Return(\_PR.PR00._PPC)  // Return PR00 _PPC value.
    }

    Method(_PCT,0)
    {
      Return(\_PR.PR00._PCT)  // Return PR00 _PCT value.
    }

    Method(_PSS,0)
    {
      Return(\_PR.PR00._PSS)  // Return PR00 _PSS.
    }

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

  Scope(\_PR.PR04)
  {
    Method(_PPC,0)
    {
      Return(\_PR.PR00._PPC)  // Return PR00 _PPC value.
    }

    Method(_PCT,0)
    {
      Return(\_PR.PR00._PCT)  // Return PR00 _PCT value.
    }

    Method(_PSS,0)
    {
      Return(\_PR.PR00._PSS)  // Return PR00 _PSS.
    }

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

  Scope(\_PR.PR05)
  {
    Method(_PPC,0)
    {
      Return(\_PR.PR00._PPC)  // Return PR00 _PPC value.
    }

    Method(_PCT,0)
    {
      Return(\_PR.PR00._PCT)  // Return PR00 _PCT value.
    }

    Method(_PSS,0)
    {
      Return(\_PR.PR00._PSS)  // Return PR00 _PSS.
    }

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

  Scope(\_PR.PR06)
  {
    Method(_PPC,0)
    {
      Return(\_PR.PR00._PPC)  // Return PR00 _PPC value.
    }

    Method(_PCT,0)
    {
      Return(\_PR.PR00._PCT)  // Return PR00 _PCT value.
    }

    Method(_PSS,0)
    {
      Return(\_PR.PR00._PSS)  // Return PR00 _PSS.
    }

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

  Scope(\_PR.PR07)
  {
    Method(_PPC,0)
    {
      Return(\_PR.PR00._PPC)  // Return PR00 _PPC value.
    }

    Method(_PCT,0)
    {
      Return(\_PR.PR00._PCT)  // Return PR00 _PCT value.
    }

    Method(_PSS,0)
    {
      Return(\_PR.PR00._PSS)  // Return PR00 _PSS.
    }

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

  Scope(\_PR.PR08)
  {
    Method(_PPC,0)
    {
      Return(\_PR.PR00._PPC)  // Return PR00 _PPC value.
    }

    Method(_PCT,0)
    {
      Return(\_PR.PR00._PCT)  // Return PR00 _PCT value.
    }

    Method(_PSS,0)
    {
      Return(\_PR.PR00._PSS)  // Return PR00 _PSS.
    }

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

  Scope(\_PR.PR09)
  {
    Method(_PPC,0)
    {
      Return(\_PR.PR00._PPC)  // Return PR00 _PPC value.
    }

    Method(_PCT,0)
    {
      Return(\_PR.PR00._PCT)  // Return PR00 _PCT value.
    }

    Method(_PSS,0)
    {
      Return(\_PR.PR00._PSS)  // Return PR00 _PSS.
    }

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

  Scope(\_PR.PR10)
  {
    Method(_PPC,0)
    {
      Return(\_PR.PR00._PPC)  // Return PR00 _PPC value.
    }

    Method(_PCT,0)
    {
      Return(\_PR.PR00._PCT)  // Return PR00 _PCT value.
    }

    Method(_PSS,0)
    {
      Return(\_PR.PR00._PSS)  // Return PR00 _PSS.
    }

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

  Scope(\_PR.PR11)
  {
    Method(_PPC,0)
    {
      Return(\_PR.PR00._PPC)  // Return PR00 _PPC value.
    }

    Method(_PCT,0)
    {
      Return(\_PR.PR00._PCT)  // Return PR00 _PCT value.
    }

    Method(_PSS,0)
    {
      Return(\_PR.PR00._PSS)  // Return PR00 _PSS.
    }

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

  Scope(\_PR.PR12)
  {
    Method(_PPC,0)
    {
      Return(\_PR.PR00._PPC)  // Return PR00 _PPC value.
    }

    Method(_PCT,0)
    {
      Return(\_PR.PR00._PCT)  // Return PR00 _PCT value.
    }

    Method(_PSS,0)
    {
      Return(\_PR.PR00._PSS)  // Return PR00 _PSS.
    }

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

  Scope(\_PR.PR13)
  {
    Method(_PPC,0)
    {
      Return(\_PR.PR00._PPC)  // Return PR00 _PPC value.
    }

    Method(_PCT,0)
    {
      Return(\_PR.PR00._PCT)  // Return PR00 _PCT value.
    }

    Method(_PSS,0)
    {
      Return(\_PR.PR00._PSS)  // Return PR00 _PSS.
    }

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

  Scope(\_PR.PR14)
  {
    Method(_PPC,0)
    {
      Return(\_PR.PR00._PPC)  // Return PR00 _PPC value.
    }

    Method(_PCT,0)
    {
      Return(\_PR.PR00._PCT)  // Return PR00 _PCT value.
    }

    Method(_PSS,0)
    {
      Return(\_PR.PR00._PSS)  // Return PR00 _PSS.
    }

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

  Scope(\_PR.PR15)
  {
    Method(_PPC,0)
    {
      Return(\_PR.PR00._PPC)  // Return PR00 _PPC value.
    }

    Method(_PCT,0)
    {
      Return(\_PR.PR00._PCT)  // Return PR00 _PCT value.
    }

    Method(_PSS,0)
    {
      Return(\_PR.PR00._PSS)  // Return PR00 _PSS.
    }

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
