/** @file
  This file contains the UART 16550 related functions

 @copyright
  INTEL CONFIDENTIAL
  Copyright 1999 - 2015 Intel Corporation.

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
#include "uart16550.h"
#include "Io.h"
#include "PchRegsPcr.h"
#include "PchRegsDmi.h"

#define SMSC1007_PORT_INDEX (0x164E)
#define SMSC1007_PORT_DATA  (0x164F)
#define WPCN381U_PORT_INDEX (0x2E)
#define WPCN381U_PORT_DATA  (0x2F)
#define WPCN381U_CHIP_ID    (0xF4)
#define WDCP376_CHIP_ID     (0xF1)

typedef struct {
  UINT8 Addr;
  UINT8 Data;
} IO_DATA;

const IO_DATA Smsc1007SioInitTable[] = {
// Addr  Data
  {0x01, 0x80},    // CR Lock
  {0x02, 0x88},    // UART 1,2 Power
  {0x04, 0x00},    // UART Miscellaneous
  {0x07, 0x00},    // Auto Power Mgt
  {0x09, 0x00},    // Test 4
  {0x0A, 0x00},    // IR MUX
  {0x0C, 0x02},    // UART Mode
  {0x0F, 0x00},    // Test 1
  {0x10, 0x00},    // Test 2
  {0x11, 0x00},    // Test 3
  {0x24, 0xFE},    // UART1 Base Address
  {0x25, 0x00},    // UART2 Base Address
  {0x28, 0x40},    // UART IRQ Select
  {0x29, 0x80},    // IRQIN1/HPMODE/SIRQ_CLKRUN_En
  {0x2A, 0x00},    // IRQIN2
  {0x2B, 0x00},    // SCE (FIR) Base Address
  {0x2C, 0x0F},    // SCE (FIR) DMA Select
  {0x2D, 0x03},    // IR Half Duplex Timeout
  {0x2E, 0x00},    // Software Select A
  {0x2F, 0x00},    // Software Select B
  {0x30, 0x68},    // Runtime Register Block Address
  {0x31, 0x1F},
  {0x32, 0x00},
  {0x33, 0x04},
  {0x34, 0x01},    // Alternate Function Register
  {0x36, 0x0C},    // GPIO Polarity Register 3
  {0x35, 0xFE},    // GPIO Direction Register 3
  {0x37, 0xFE},    // GPIO OULLUP Register 3
  {0x38, 0xFB},    // GPIO OULLUP Register 1
  {0x39, 0x00},    // GPIO Output Type Register 1
  {0x3A, 0x0A},    // LPC Activate Power
  {0x3B, 0x06},    // LPC Docking Base Address Register High Byte
  {0x3C, 0x90}     // LPC Docking Base Address Register Low Byte
};

const UINT8 Smsc1007SioPmInitTable[] = {
  {0x00},  // ;PME_STS
  {0x00},  // ;PME_EN
  {0xDB},  // ;PME_STS1
  {0x00},  // ;PME_STS2
  {0xFF},  // ;PME_STS3
  {0x00},  // ;PME_EN1
  {0x00},  // ;PME_EN2
  {0x00},  // ;PME_EN3
  {0xDB},  // ;SMI_STS1
  {0x00},  // ;SMI_STS2
  {0x00},  // ;SMI_EN1
  {0x00},  // ;SMI_EN2
  {0xFF},  // ;GP1
  {0x00},  // ;GP2
  {0xC0},  // ;GP3
  {0x00}
};

const IO_DATA Pilot3SioInitTable[] = {
// Addr  Data
  // Program and initialize the Serial Port0 (COMA / UART0)
  {0x07, 0x02}, // Set logical device SP Serial port
  {0x61, 0xF8},  // Write Base Address LSB register
  {0x60, 0x03},  // Write Base Address MSB register
  {0x70, 0x04},  // Write IRQ value
  {0x30, 0x01},  // Enable serial port with Activation bit

  // Program and initialize the Serial Port1 (COMB / UART1)
  {0x07, 0x01},  // Set logical device SP Serial port
  {0x61, 0xF8},  // Write Base Address LSB register
  {0x60, 0x02},  // Write Base Address MSB register
  {0x70, 0x03},  // Write IRQ value
  {0x30, 0x01}   // Enable serial port with Activation bit
};

const IO_DATA Wpcn381uMobile[] = {
// Addr  Data
  {0x29, 0xA0},

  // Program and initialize the Serial Port0 (COMA / UART0)
  {0x07, 0x03},
  {0x61, 0xF8}, // Write Base Address LSB register
  {0x60, 0x03}, // Write Base Address MSB register
  {0x70, 0x04}, // Set to IRQ4
  {0x30, 0x01}, // Enable serial port with Activation bit

  // Program and initialize the Serial Port1 (COMB / UART1)
  {0x07, 0x02}, // Set logical device SP Serial port
  {0x61, 0x00}, // Write Base Address LSB register
  {0x60, 0x00}, // Write Base Address MSB register
  {0x30, 0x00}, // Disable serial port with Activation bit

  // Some Additional Programming needs to be done here
  // Select GPIO device
  {0x07, 0x07},

  // Program Base Addr
  {0x60, 0x0A},
  {0x61, 0x20},

  // If the enable bits are not set, the multi-function pins will perform the original functions.
  // If they are set, they will perform the GPIO functions.
  // These registers can be read from any LDN, but can only be written if LDN = 07h.

  {0x30, 0x01}, // Activate Device

  {0x21, 0x01}, // Global Device Enable

  {0x26, 0x00}
};

const IO_DATA Wpcn381uDesktop[] = {
// Addr  Data
  {0x29, 0xA0},

  // Program and initialize the Serial Port0 (COMA / UART0)
  {0x07, 0x03},
  {0x61, 0xF8}, // Write Base Address LSB register
  {0x60, 0x03}, // Write Base Address MSB register
  {0x70, 0x04}, // Set to IRQ4
  {0x30, 0x01}, // Enable serial port with Activation bit

  // Program and initialize the Serial Port1 (COMB / UART1)
  {0x07, 0x02}, // Set logical device SP Serial port
  {0x61, 0x00}, // Write Base Address LSB register
  {0x60, 0x00}, // Write Base Address MSB register
  {0x30, 0x00}, // Disable serial port with Activation bit

  // Some Additional Programming needs to be done here
  // Select GPIO device
  {0x07, 0x07},

  // Program Base Addr
  {0x60, 0x0A},
  {0x61, 0x20},

  // If the enable bits are not set, the multi-function pins will perform the original functions.
  // If they are set, they will perform the GPIO functions.
  // These registers can be read from any LDN, but can only be written if LDN = 07h.

  {0x30, 0x01}, // Activate Device

  {0x21, 0x01}, // Global Device Enable

  {0x26, 0x00},

  // Program and initialize the KB/MS controller
  {0x07, 0x06},
  {0x61, 0x60},
  {0x60, 0x00},
  {0x63, 0x64},
  {0x62, 0x00},
  {0x70, 0x01},
  {0xF0, 0x40},
  {0x30, 0x01},
  {0x07, 0x05},
  {0x70, 0x0C},
  {0x30, 0x01}
};

static
UINT8
Smsc1007SioInit (
  void
  )
{
  UINT16 Counter;
  UINT8  DeviceID;

  IoWrite8 (SMSC1007_PORT_INDEX, 0x55);
  IoWrite8 (SMSC1007_PORT_INDEX, 0x0D);
  DeviceID = IoRead8 (SMSC1007_PORT_DATA);
  if (DeviceID == 0x20) {
    for (Counter = 0; Counter < ((sizeof (Smsc1007SioInitTable)) / (sizeof (Smsc1007SioInitTable[0]))); Counter++) {
      IoWrite8 (SMSC1007_PORT_INDEX, Smsc1007SioInitTable[Counter].Addr);
      IoWrite8 (SMSC1007_PORT_DATA,  Smsc1007SioInitTable[Counter].Data);
    }
    IoWrite8 (SMSC1007_PORT_INDEX, 0xAA);

    for (Counter = 0; Counter < ((sizeof (Smsc1007SioPmInitTable)) / (sizeof (Smsc1007SioPmInitTable[0]))); Counter++) {
      IoWrite8 (0x680 + Counter, Smsc1007SioPmInitTable[Counter]);
    }
  }
  return (DeviceID);
}

static
UINT8
Pilot3SioInit (
  void
  )
{
  UINT16 Counter;
  UINT8  DeviceID;

  // Check if we have Pilot3 SIO.
  IoWrite8 (PILOT3_CONFIG_INDEX, PILOT3_ENTERCFG_VALUE); // Enter config mode.
  IoWrite8 (PILOT3_CONFIG_INDEX, PILOT3_DEV_ID_REG);
  DeviceID = IoRead8 (PILOT3_CONFIG_DATA);
  if (DeviceID == PILOT3_DEV_ID) {
    IoWrite8 (PILOT3_CONFIG_INDEX, PILOT3_ENTERCFG_VALUE); //  Enter config mode.
    for (Counter = 0; Counter < ((sizeof (Pilot3SioInitTable)) / (sizeof (Pilot3SioInitTable[0]))); Counter++) {
      IoWrite8 (PILOT3_CONFIG_INDEX, Pilot3SioInitTable[Counter].Addr);
      IoWrite8 (PILOT3_CONFIG_DATA,  Pilot3SioInitTable[Counter].Data);
    }
    IoWrite8 (PILOT3_CONFIG_INDEX, PILOT3_EXITCFG_VALUE); // Exit config mode.
  }

  return (DeviceID);
}

static
UINT8
Wpcn381uSioInit (
  void
  )
{
  const IO_DATA *Table;
  UINT16        Size;
  UINT16        Counter;
  UINT8         DeviceId;

  IoWrite8 (WPCN381U_PORT_INDEX, 0x20);
  DeviceId = IoRead8 (WPCN381U_PORT_DATA);

  switch (DeviceId) {
    case WPCN381U_CHIP_ID:
      Table = Wpcn381uMobile;
      Size  = sizeof (Wpcn381uMobile) / sizeof (Wpcn381uMobile[0]);
      break;

    case WDCP376_CHIP_ID:
      Table = Wpcn381uDesktop;
      Size  = sizeof (Wpcn381uDesktop) / sizeof (Wpcn381uDesktop[0]);
      break;

    default:
      Table = NULL;
      Size  = 0;
      break;
  }
  for (Counter = 0; Counter < Size; Counter++) {
    IoWrite8 (WPCN381U_PORT_INDEX, Table[Counter].Addr);
    IoWrite8 (WPCN381U_PORT_DATA,  Table[Counter].Data);
  }
  return (DeviceId);
}

int
putchar (
  int c
  )
/**

Routine Description:

  put char in the uart device.

Arguments:

  c   - char to put in the uart.


Returns:

  Returns the puted char.
**/
{
  UINT8 UartStatus;

  // Wait to uart empty
  do {
    UartStatus = MrcOemInPort8 (GLOBALCOMPORT + LINE_STATUS);
  } while ((UartStatus & TRANS_HOLDING_REG_EMPTY) != TRANS_HOLDING_REG_EMPTY);

  // Send the char
  MrcOemOutPort8 (GLOBALCOMPORT + TRANSMIT_HOLDING, (UINT8) c);

  return c;
}

char
GetLineStatusRegister (
  void
  )
/**

Routine Description:

  read line status register from the uart device.

Arguments:

  N/A.

Returns:

  Returns the read status.
**/
{
  UINT8 UartStatus;

  UartStatus = MrcOemInPort8 (GLOBALCOMPORT + LINE_STATUS);
  return ((char) UartStatus);
}

char
GetBreak (
  void
  )
{
  UINT8 UartStatus;

  UartStatus = GetLineStatusRegister ();
  return ((UartStatus & BREAK_INTERRUPT) ? 1 : 0);
}

char
getchar (
  void
  )
/**

Routine Description:

  read char from the uart device.

Arguments:

  N/A.

Returns:

  Returns the read char.
**/
{
  return (((GetLineStatusRegister () & DATA_READY) == DATA_READY) ? (char) MrcOemInPort8 (GLOBALCOMPORT + RECEIVER_BUFFER) : EOF);
}

void
Init16550Uart (
  void
  )
/**

Routine Description:

  1. Enable UART and COM port decoding on PCH.
  2. Initialize UART chip
  3. Initialize COM1 port to 115200/8/N/1

Arguments:

  N/A.

Returns:

  none
**/
{
  UINT32  Divisor;
  UINT8   Data;

  //
  // Enable LPC decode
  // Enable SIO decoding on PCH at 164E/164F
  // Enable SB to decode SIO index/data registers
  //
  MrcOemOutPort32 (MrcOemPciIndex (), (UINT32) (ICH_LPC_CF8_ADDR (ICH_LPC_GEN2_DEC)));
  MrcOemOutPort32 (MrcOemPciData (),  0x000C1641);
  MrcOemMmioWrite32 (PCH_PCR_ADDRESS (PID_DMI, R_PCH_PCR_DMI_LPCLGIR2), 0x000C1641);

  //
  // Enable SIO decoding on PCH at [680..6FF]
  //
  MrcOemOutPort32 (MrcOemPciIndex (), (UINT32) (ICH_LPC_CF8_ADDR (ICH_LPC_GEN1_DEC)));
  MrcOemOutPort32 (MrcOemPciData (),  0x007C0681);
  MrcOemMmioWrite32 (PCH_PCR_ADDRESS (PID_DMI, R_PCH_PCR_DMI_LPCLGIR1), 0x007C0681);
  //
  // Enable COM1 decoding on PCH at 0x3F8 - register 82h[0]
  // Register 82h[13:12] = SIO 4Eh/4Fh, 2Eh/2Fh decoding
  //
  MrcOemOutPort32 (MrcOemPciIndex (), (UINT32) (ICH_LPC_CF8_ADDR (ICH_LPC_IO_DEC)));
  MrcOemOutPort32 (MrcOemPciData (),  0x30010000);
  MrcOemMmioWrite16 (PCH_PCR_ADDRESS (PID_DMI, R_PCH_PCR_DMI_LPCIOE), 0x3001);

  //
  // Init Smsc1007 SIO, if fails init WPCN381U SIO , if fails init PILOT3 SIO .
  //
  if (Smsc1007SioInit () != 0x20) {
    Data = Wpcn381uSioInit ();
    if ((Data != WPCN381U_CHIP_ID) && (Data != WDCP376_CHIP_ID)) {
      Pilot3SioInit ();
    }
  }

  //
  // Set Line Control Register (LCR)
  //
  MrcOemOutPort8 (GLOBALCOMPORT + LINE_CONTROL, (DLAB_BIT << 7) | (STOP_BIT << 2) | DATA_BITS);
  //
  // Set Baud rate to 115k in Divisor Latch
  //
  Divisor = (115200 / BAUD_RATE_DIVISOR);
  MrcOemOutPort8 (GLOBALCOMPORT + DIVISOR_LATCH_LOW, (((UINT8) Divisor) & 0xFF));
  MrcOemOutPort8 (GLOBALCOMPORT + DIVISOR_LATCH_HIGH, ((UINT8) (Divisor >> 8)) & 0xFF);


  //
  // Clear DLAB bit in LCR
  //
  Data = MrcOemInPort8 (GLOBALCOMPORT + LINE_CONTROL);
  Data &=  ~(DLAB_BIT << 7);
  MrcOemOutPort8 (GLOBALCOMPORT + LINE_CONTROL, Data);
  return;
}
