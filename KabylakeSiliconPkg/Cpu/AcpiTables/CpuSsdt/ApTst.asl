/** @file
  Intel Processor AP TST ACPI Code.

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

DefinitionBlock(
  "APTST.aml",
  "SSDT",
  0x02,
  "PmRef",
  "ApTst",
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
  External(\_PR.PR00._TPC, MethodObj)
  External(\_PR.PR00._PTC, MethodObj)
  External(\_PR.PR00._TSS, MethodObj)

  Scope(\_PR.PR01)
  {
    //
    // Max T-state available
    //
    Method(_TPC, 0)
    {
      Return(\_PR.PR00._TPC)
    }

    //
    // T-State Control/Status interface
    //
    Method(_PTC, 0)
    {
      Return(\_PR.PR00._PTC)
    }

    Method(_TSS, 0)
    {
      Return(\_PR.PR00._TSS)
    }

    //
    // T-State Dependency
    //
    Method(_TSD, 0)
    {
      //
      // IF four cores are supported/enabled && !(direct access to MSR)
      //    Report 4 processors and SW_ANY as the coordination
      // IF two cores are supported/enabled && !(direct access to MSR)
      //    Report 2 processors and SW_ANY as the coordination type
      //  ELSE
      //    Report 1 processor and SW_ALL as the coordination type (domain 1)
      //
      //  PDCx[2] = OSPM is capable of direct access to On
      //    Demand throttling MSR
      //

      If(LNot(And(PC00,4)))
      {
        Return(Package(){ // SW_ANY
          Package(){
            5,            // # entries.
            0,            // Revision.
            0,            // Domain #.
            0xFD,         // Coord Type- SW_ANY
            TCNT          // # processors.
          }
        })
      }
      Return(Package(){   // SW_ALL
        Package(){
          5,              // # entries.
          0,              // Revision.
          1,              // Domain #.
          0xFC,           // Coord Type- SW_ALL
          1               // # processors.
        }
      })
    }
  }  // End of PR01


  Scope(\_PR.PR02)
  {
    //
    // Max T-state available
    //
    Method(_TPC, 0)
    {
      Return(\_PR.PR00._TPC)
    }

    //
    // T-State Control/Status interface
    //
    Method(_PTC, 0)
    {
      Return(\_PR.PR00._PTC)
    }

    Method(_TSS, 0)
    {
      Return(\_PR.PR00._TSS)
    }

    //
    // T-State Dependency
    //
    Method(_TSD, 0)
    {
      //
      // IF four cores are supported/enabled && !(direct access to MSR)
      //    Report 4 processors and SW_ANY as the coordination
      // IF two cores are supported/enabled && !(direct access to MSR)
      //    Report 2 processors and SW_ANY as the coordination type
      //  ELSE
      //    Report 1 processor and SW_ALL as the coordination type (domain 2)
      //
      //  PDCx[2] = OSPM is capable of direct access to On
      //    Demand throttling MSR
      //

      If(LNot(And(PC00,4)))
      {
        Return(Package(){ // SW_ANY
          Package(){
            5,            // # entries.
            0,            // Revision.
            0,            // Domain #.
            0xFD,         // Coord Type- SW_ANY
            TCNT          // # processors.
          }
        })
      }
      Return(Package(){   // SW_ALL
        Package(){
          5,              // # entries.
          0,              // Revision.
          2,              // Domain #.
          0xFC,           // Coord Type- SW_ALL
          1               // # processors.
        }
      })
    }
  }  // End of PR02


  Scope(\_PR.PR03)
  {
    //
    // Max T-state available
    //
    Method(_TPC, 0)
    {
      Return(\_PR.PR00._TPC)
    }

    //
    // T-State Control/Status interface
    //
    Method(_PTC, 0)
    {
      Return(\_PR.PR00._PTC)
    }

    Method(_TSS, 0)
    {
      Return(\_PR.PR00._TSS)
    }

    //
    // T-State Dependency
    //
    Method(_TSD, 0)
    {
      //
      // IF four cores are supported/enabled && !(direct access to MSR)
      //    Report 4 processors and SW_ANY as the coordination
      // IF two cores are supported/enabled && !(direct access to MSR)
      //    Report 2 processors and SW_ANY as the coordination type
      //  ELSE
      //    Report 1 processor and SW_ALL as the coordination type (domain 3)
      //
      //  PDCx[2] = OSPM is capable of direct access to On
      //    Demand throttling MSR
      //

      If(LNot(And(PC00,4)))
      {
        Return(Package(){ // SW_ANY
          Package(){
            5,            // # entries.
            0,            // Revision.
            0,            // Domain #.
            0xFD,         // Coord Type- SW_ANY
            TCNT          // # processors.
          }
        })
      }
      Return(Package(){   // SW_ALL
        Package(){
          5,              // # entries.
          0,              // Revision.
          3,              // Domain #.
          0xFC,           // Coord Type- SW_ALL
          1               // # processors.
        }
      })
    }
  }  // End of PR03

  Scope(\_PR.PR04)
  {
    //
    // Max T-state available
    //
    Method(_TPC, 0)
    {
      Return(\_PR.PR00._TPC)
    }

    //
    // T-State Control/Status interface
    //
    Method(_PTC, 0)
    {
      Return(\_PR.PR00._PTC)
    }

    Method(_TSS, 0)
    {
      Return(\_PR.PR00._TSS)
    }

    //
    // T-State Dependency
    //
    Method(_TSD, 0)
    {
      //
      // IF four cores are supported/enabled && !(direct access to MSR)
      //    Report 4 processors and SW_ANY as the coordination
      // IF two cores are supported/enabled && !(direct access to MSR)
      //    Report 2 processors and SW_ANY as the coordination type
      //  ELSE
      //    Report 1 processor and SW_ALL as the coordination type (domain 3)
      //
      //  PDCx[2] = OSPM is capable of direct access to On
      //    Demand throttling MSR
      //

      If(LNot(And(PC00,4)))
      {
        Return(Package(){ // SW_ANY
          Package(){
            5,            // # entries.
            0,            // Revision.
            0,            // Domain #.
            0xFD,         // Coord Type- SW_ANY
            TCNT          // # processors.
          }
        })
      }
      Return(Package(){   // SW_ALL
        Package(){
          5,              // # entries.
          0,              // Revision.
          4,              // Domain #.
          0xFC,           // Coord Type- SW_ALL
          1               // # processors.
        }
      })
    }
  }  // End of PR04

  Scope(\_PR.PR05)
  {
    //
    // Max T-state available
    //
    Method(_TPC, 0)
    {
      Return(\_PR.PR00._TPC)
    }

    //
    // T-State Control/Status interface
    //
    Method(_PTC, 0)
    {
      Return(\_PR.PR00._PTC)
    }

    Method(_TSS, 0)
    {
      Return(\_PR.PR00._TSS)
    }

    //
    // T-State Dependency
    //
    Method(_TSD, 0)
    {
      //
      // IF four cores are supported/enabled && !(direct access to MSR)
      //    Report 4 processors and SW_ANY as the coordination
      // IF two cores are supported/enabled && !(direct access to MSR)
      //    Report 2 processors and SW_ANY as the coordination type
      //  ELSE
      //    Report 1 processor and SW_ALL as the coordination type (domain 3)
      //
      //  PDCx[2] = OSPM is capable of direct access to On
      //    Demand throttling MSR
      //

      If(LNot(And(PC00,4)))
      {
        Return(Package(){ // SW_ANY
          Package(){
            5,            // # entries.
            0,            // Revision.
            0,            // Domain #.
            0xFD,         // Coord Type- SW_ANY
            TCNT          // # processors.
          }
        })
      }
      Return(Package(){   // SW_ALL
        Package(){
          5,              // # entries.
          0,              // Revision.
          5,              // Domain #.
          0xFC,           // Coord Type- SW_ALL
          1               // # processors.
        }
      })
    }
  }  // End of PR05

  Scope(\_PR.PR06)
  {
    //
    // Max T-state available
    //
    Method(_TPC, 0)
    {
      Return(\_PR.PR00._TPC)
    }

    //
    // T-State Control/Status interface
    //
    Method(_PTC, 0)
    {
      Return(\_PR.PR00._PTC)
    }

    Method(_TSS, 0)
    {
      Return(\_PR.PR00._TSS)
    }

    //
    // T-State Dependency
    //
    Method(_TSD, 0)
    {
      //
      // IF four cores are supported/enabled && !(direct access to MSR)
      //    Report 4 processors and SW_ANY as the coordination
      // IF two cores are supported/enabled && !(direct access to MSR)
      //    Report 2 processors and SW_ANY as the coordination type
      //  ELSE
      //    Report 1 processor and SW_ALL as the coordination type (domain 3)
      //
      //  PDCx[2] = OSPM is capable of direct access to On
      //    Demand throttling MSR
      //

      If(LNot(And(PC00,4)))
      {
        Return(Package(){ // SW_ANY
          Package(){
            5,            // # entries.
            0,            // Revision.
            0,            // Domain #.
            0xFD,         // Coord Type- SW_ANY
            TCNT          // # processors.
          }
        })
      }
      Return(Package(){   // SW_ALL
        Package(){
          5,              // # entries.
          0,              // Revision.
          6,              // Domain #.
          0xFC,           // Coord Type- SW_ALL
          1               // # processors.
        }
      })
    }
  }  // End of PR06

  Scope(\_PR.PR07)
  {
    //
    // Max T-state available
    //
    Method(_TPC, 0)
    {
      Return(\_PR.PR00._TPC)
    }

    //
    // T-State Control/Status interface
    //
    Method(_PTC, 0)
    {
      Return(\_PR.PR00._PTC)
    }

    Method(_TSS, 0)
    {
      Return(\_PR.PR00._TSS)
    }

    //
    // T-State Dependency
    //
    Method(_TSD, 0)
    {
      //
      // IF four cores are supported/enabled && !(direct access to MSR)
      //    Report 4 processors and SW_ANY as the coordination
      // IF two cores are supported/enabled && !(direct access to MSR)
      //    Report 2 processors and SW_ANY as the coordination type
      //  ELSE
      //    Report 1 processor and SW_ALL as the coordination type (domain 3)
      //
      //  PDCx[2] = OSPM is capable of direct access to On
      //    Demand throttling MSR
      //

      If(LNot(And(PC00,4)))
      {
        Return(Package(){ // SW_ANY
          Package(){
            5,            // # entries.
            0,            // Revision.
            0,            // Domain #.
            0xFD,         // Coord Type- SW_ANY
            TCNT          // # processors.
          }
        })
      }
      Return(Package(){   // SW_ALL
        Package(){
          5,              // # entries.
          0,              // Revision.
          7,              // Domain #.
          0xFC,           // Coord Type- SW_ALL
          1               // # processors.
        }
      })
    }
  }  // End of PR07

  Scope(\_PR.PR08)
  {
    //
    // Max T-state available
    //
    Method(_TPC, 0)
    {
      Return(\_PR.PR00._TPC)
    }

    //
    // T-State Control/Status interface
    //
    Method(_PTC, 0)
    {
      Return(\_PR.PR00._PTC)
    }

    Method(_TSS, 0)
    {
      Return(\_PR.PR00._TSS)
    }

    //
    // T-State Dependency
    //
    Method(_TSD, 0)
    {
      //
      // IF four cores are supported/enabled && !(direct access to MSR)
      //    Report 4 processors and SW_ANY as the coordination
      // IF two cores are supported/enabled && !(direct access to MSR)
      //    Report 2 processors and SW_ANY as the coordination type
      //  ELSE
      //    Report 1 processor and SW_ALL as the coordination type (domain 3)
      //
      //  PDCx[2] = OSPM is capable of direct access to On
      //    Demand throttling MSR
      //

      If(LNot(And(PC00,4)))
      {
        Return(Package(){ // SW_ANY
          Package(){
            5,            // # entries.
            0,            // Revision.
            0,            // Domain #.
            0xFD,         // Coord Type- SW_ANY
            TCNT          // # processors.
          }
        })
      }
      Return(Package(){   // SW_ALL
        Package(){
          5,              // # entries.
          0,              // Revision.
          8,              // Domain #.
          0xFC,           // Coord Type- SW_ALL
          1               // # processors.
        }
      })
    }
  }  // End of PR08

  Scope(\_PR.PR09)
  {
    //
    // Max T-state available
    //
    Method(_TPC, 0)
    {
      Return(\_PR.PR00._TPC)
    }

    //
    // T-State Control/Status interface
    //
    Method(_PTC, 0)
    {
      Return(\_PR.PR00._PTC)
    }

    Method(_TSS, 0)
    {
      Return(\_PR.PR00._TSS)
    }

    //
    // T-State Dependency
    //
    Method(_TSD, 0)
    {
      //
      // IF four cores are supported/enabled && !(direct access to MSR)
      //    Report 4 processors and SW_ANY as the coordination
      // IF two cores are supported/enabled && !(direct access to MSR)
      //    Report 2 processors and SW_ANY as the coordination type
      //  ELSE
      //    Report 1 processor and SW_ALL as the coordination type (domain 3)
      //
      //  PDCx[2] = OSPM is capable of direct access to On
      //    Demand throttling MSR
      //

      If(LNot(And(PC00,4)))
      {
        Return(Package(){ // SW_ANY
          Package(){
            5,            // # entries.
            0,            // Revision.
            0,            // Domain #.
            0xFD,         // Coord Type- SW_ANY
            TCNT          // # processors.
          }
        })
      }
      Return(Package(){   // SW_ALL
        Package(){
          5,              // # entries.
          0,              // Revision.
          9,              // Domain #.
          0xFC,           // Coord Type- SW_ALL
          1               // # processors.
        }
      })
    }
  }  // End of PR09

  Scope(\_PR.PR10)
  {
    //
    // Max T-state available
    //
    Method(_TPC, 0)
    {
      Return(\_PR.PR00._TPC)
    }

    //
    // T-State Control/Status interface
    //
    Method(_PTC, 0)
    {
      Return(\_PR.PR00._PTC)
    }

    Method(_TSS, 0)
    {
      Return(\_PR.PR00._TSS)
    }

    //
    // T-State Dependency
    //
    Method(_TSD, 0)
    {
      //
      // IF four cores are supported/enabled && !(direct access to MSR)
      //    Report 4 processors and SW_ANY as the coordination
      // IF two cores are supported/enabled && !(direct access to MSR)
      //    Report 2 processors and SW_ANY as the coordination type
      //  ELSE
      //    Report 1 processor and SW_ALL as the coordination type (domain 3)
      //
      //  PDCx[2] = OSPM is capable of direct access to On
      //    Demand throttling MSR
      //

      If(LNot(And(PC00,4)))
      {
        Return(Package(){ // SW_ANY
          Package(){
            5,            // # entries.
            0,            // Revision.
            0,            // Domain #.
            0xFD,         // Coord Type- SW_ANY
            TCNT          // # processors.
          }
        })
      }
      Return(Package(){   // SW_ALL
        Package(){
          5,              // # entries.
          0,              // Revision.
          10,              // Domain #.
          0xFC,           // Coord Type- SW_ALL
          1               // # processors.
        }
      })
    }
  }  // End of PR10

  Scope(\_PR.PR11)
  {
    //
    // Max T-state available
    //
    Method(_TPC, 0)
    {
      Return(\_PR.PR00._TPC)
    }

    //
    // T-State Control/Status interface
    //
    Method(_PTC, 0)
    {
      Return(\_PR.PR00._PTC)
    }

    Method(_TSS, 0)
    {
      Return(\_PR.PR00._TSS)
    }

    //
    // T-State Dependency
    //
    Method(_TSD, 0)
    {
      //
      // IF four cores are supported/enabled && !(direct access to MSR)
      //    Report 4 processors and SW_ANY as the coordination
      // IF two cores are supported/enabled && !(direct access to MSR)
      //    Report 2 processors and SW_ANY as the coordination type
      //  ELSE
      //    Report 1 processor and SW_ALL as the coordination type (domain 3)
      //
      //  PDCx[2] = OSPM is capable of direct access to On
      //    Demand throttling MSR
      //

      If(LNot(And(PC00,4)))
      {
        Return(Package(){ // SW_ANY
          Package(){
            5,            // # entries.
            0,            // Revision.
            0,            // Domain #.
            0xFD,         // Coord Type- SW_ANY
            TCNT          // # processors.
          }
        })
      }
      Return(Package(){   // SW_ALL
        Package(){
          5,              // # entries.
          0,              // Revision.
          11,              // Domain #.
          0xFC,           // Coord Type- SW_ALL
          1               // # processors.
        }
      })
    }
  }  // End of PR11

  Scope(\_PR.PR12)
  {
    //
    // Max T-state available
    //
    Method(_TPC, 0)
    {
      Return(\_PR.PR00._TPC)
    }

    //
    // T-State Control/Status interface
    //
    Method(_PTC, 0)
    {
      Return(\_PR.PR00._PTC)
    }

    Method(_TSS, 0)
    {
      Return(\_PR.PR00._TSS)
    }

    //
    // T-State Dependency
    //
    Method(_TSD, 0)
    {
      //
      // IF four cores are supported/enabled && !(direct access to MSR)
      //    Report 4 processors and SW_ANY as the coordination
      // IF two cores are supported/enabled && !(direct access to MSR)
      //    Report 2 processors and SW_ANY as the coordination type
      //  ELSE
      //    Report 1 processor and SW_ALL as the coordination type (domain 3)
      //
      //  PDCx[2] = OSPM is capable of direct access to On
      //    Demand throttling MSR
      //

      If(LNot(And(PC00,4)))
      {
        Return(Package(){ // SW_ANY
          Package(){
            5,            // # entries.
            0,            // Revision.
            0,            // Domain #.
            0xFD,         // Coord Type- SW_ANY
            TCNT          // # processors.
          }
        })
      }
      Return(Package(){   // SW_ALL
        Package(){
          5,              // # entries.
          0,              // Revision.
          12,              // Domain #.
          0xFC,           // Coord Type- SW_ALL
          1               // # processors.
        }
      })
    }
  }  // End of PR12

  Scope(\_PR.PR13)
  {
    //
    // Max T-state available
    //
    Method(_TPC, 0)
    {
      Return(\_PR.PR00._TPC)
    }

    //
    // T-State Control/Status interface
    //
    Method(_PTC, 0)
    {
      Return(\_PR.PR00._PTC)
    }

    Method(_TSS, 0)
    {
      Return(\_PR.PR00._TSS)
    }

    //
    // T-State Dependency
    //
    Method(_TSD, 0)
    {
      //
      // IF four cores are supported/enabled && !(direct access to MSR)
      //    Report 4 processors and SW_ANY as the coordination
      // IF two cores are supported/enabled && !(direct access to MSR)
      //    Report 2 processors and SW_ANY as the coordination type
      //  ELSE
      //    Report 1 processor and SW_ALL as the coordination type (domain 3)
      //
      //  PDCx[2] = OSPM is capable of direct access to On
      //    Demand throttling MSR
      //

      If(LNot(And(PC00,4)))
      {
        Return(Package(){ // SW_ANY
          Package(){
            5,            // # entries.
            0,            // Revision.
            0,            // Domain #.
            0xFD,         // Coord Type- SW_ANY
            TCNT          // # processors.
          }
        })
      }
      Return(Package(){   // SW_ALL
        Package(){
          5,              // # entries.
          0,              // Revision.
          13,              // Domain #.
          0xFC,           // Coord Type- SW_ALL
          1               // # processors.
        }
      })
    }
  }  // End of PR13

  Scope(\_PR.PR14)
  {
    //
    // Max T-state available
    //
    Method(_TPC, 0)
    {
      Return(\_PR.PR00._TPC)
    }

    //
    // T-State Control/Status interface
    //
    Method(_PTC, 0)
    {
      Return(\_PR.PR00._PTC)
    }

    Method(_TSS, 0)
    {
      Return(\_PR.PR00._TSS)
    }

    //
    // T-State Dependency
    //
    Method(_TSD, 0)
    {
      //
      // IF four cores are supported/enabled && !(direct access to MSR)
      //    Report 4 processors and SW_ANY as the coordination
      // IF two cores are supported/enabled && !(direct access to MSR)
      //    Report 2 processors and SW_ANY as the coordination type
      //  ELSE
      //    Report 1 processor and SW_ALL as the coordination type (domain 3)
      //
      //  PDCx[2] = OSPM is capable of direct access to On
      //    Demand throttling MSR
      //

      If(LNot(And(PC00,4)))
      {
        Return(Package(){ // SW_ANY
          Package(){
            5,            // # entries.
            0,            // Revision.
            0,            // Domain #.
            0xFD,         // Coord Type- SW_ANY
            TCNT          // # processors.
          }
        })
      }
      Return(Package(){   // SW_ALL
        Package(){
          5,              // # entries.
          0,              // Revision.
          14,              // Domain #.
          0xFC,           // Coord Type- SW_ALL
          1               // # processors.
        }
      })
    }
  }  // End of PR14

  Scope(\_PR.PR15)
  {
    //
    // Max T-state available
    //
    Method(_TPC, 0)
    {
      Return(\_PR.PR00._TPC)
    }

    //
    // T-State Control/Status interface
    //
    Method(_PTC, 0)
    {
      Return(\_PR.PR00._PTC)
    }

    Method(_TSS, 0)
    {
      Return(\_PR.PR00._TSS)
    }

    //
    // T-State Dependency
    //
    Method(_TSD, 0)
    {
      //
      // IF four cores are supported/enabled && !(direct access to MSR)
      //    Report 4 processors and SW_ANY as the coordination
      // IF two cores are supported/enabled && !(direct access to MSR)
      //    Report 2 processors and SW_ANY as the coordination type
      //  ELSE
      //    Report 1 processor and SW_ALL as the coordination type (domain 3)
      //
      //  PDCx[2] = OSPM is capable of direct access to On
      //    Demand throttling MSR
      //

      If(LNot(And(PC00,4)))
      {
        Return(Package(){ // SW_ANY
          Package(){
            5,            // # entries.
            0,            // Revision.
            0,            // Domain #.
            0xFD,         // Coord Type- SW_ANY
            TCNT          // # processors.
          }
        })
      }
      Return(Package(){   // SW_ALL
        Package(){
          5,              // # entries.
          0,              // Revision.
          15,              // Domain #.
          0xFC,           // Coord Type- SW_ALL
          1               // # processors.
        }
      })
    }
  }  // End of PR15
} // End of Definition Block

