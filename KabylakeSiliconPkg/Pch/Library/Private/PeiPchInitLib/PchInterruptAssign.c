/** @file
  Initializes PCH interrupts.

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

#include "PchInitPei.h"

typedef struct {
  UINT8  DevNum;
  UINT8  FuncNum;
  UINT16 PciCfgCtrAddr;
} SERIAL_IO_CFGCTRL_DESCRIPTOR;

GLOBAL_REMOVE_IF_UNREFERENCED SERIAL_IO_CFGCTRL_DESCRIPTOR mSerialIoCfgCtrl [PCH_SERIALIO_MAX_CONTROLLERS] =
{
  {PCI_DEVICE_NUMBER_PCH_SERIAL_IO_I2C0,  PCI_FUNCTION_NUMBER_PCH_SERIAL_IO_I2C0,  R_PCH_PCR_SERIAL_IO_PCICFGCTRL1 },
  {PCI_DEVICE_NUMBER_PCH_SERIAL_IO_I2C1,  PCI_FUNCTION_NUMBER_PCH_SERIAL_IO_I2C1,  R_PCH_PCR_SERIAL_IO_PCICFGCTRL2 },
  {PCI_DEVICE_NUMBER_PCH_SERIAL_IO_I2C2,  PCI_FUNCTION_NUMBER_PCH_SERIAL_IO_I2C2,  R_PCH_PCR_SERIAL_IO_PCICFGCTRL3 },
  {PCI_DEVICE_NUMBER_PCH_SERIAL_IO_I2C3,  PCI_FUNCTION_NUMBER_PCH_SERIAL_IO_I2C3,  R_PCH_PCR_SERIAL_IO_PCICFGCTRL4 },
  {PCI_DEVICE_NUMBER_PCH_SERIAL_IO_I2C4,  PCI_FUNCTION_NUMBER_PCH_SERIAL_IO_I2C4,  R_PCH_PCR_SERIAL_IO_PCICFGCTRL5 },
  {PCI_DEVICE_NUMBER_PCH_SERIAL_IO_I2C5,  PCI_FUNCTION_NUMBER_PCH_SERIAL_IO_I2C5,  R_PCH_PCR_SERIAL_IO_PCICFGCTRL6 },
  {PCI_DEVICE_NUMBER_PCH_SERIAL_IO_SPI0,  PCI_FUNCTION_NUMBER_PCH_SERIAL_IO_SPI0,  R_PCH_PCR_SERIAL_IO_PCICFGCTRL13},
  {PCI_DEVICE_NUMBER_PCH_SERIAL_IO_SPI1,  PCI_FUNCTION_NUMBER_PCH_SERIAL_IO_SPI1,  R_PCH_PCR_SERIAL_IO_PCICFGCTRL14},
  {PCI_DEVICE_NUMBER_PCH_SERIAL_IO_UART0, PCI_FUNCTION_NUMBER_PCH_SERIAL_IO_UART0, R_PCH_PCR_SERIAL_IO_PCICFGCTRL9 },
  {PCI_DEVICE_NUMBER_PCH_SERIAL_IO_UART1, PCI_FUNCTION_NUMBER_PCH_SERIAL_IO_UART1, R_PCH_PCR_SERIAL_IO_PCICFGCTRL10},
  {PCI_DEVICE_NUMBER_PCH_SERIAL_IO_UART2, PCI_FUNCTION_NUMBER_PCH_SERIAL_IO_UART2, R_PCH_PCR_SERIAL_IO_PCICFGCTRL11},
};

typedef struct {
  UINT8   Device;
  UINT16  Register;
} PCH_PIRX_REGISTER;

GLOBAL_REMOVE_IF_UNREFERENCED PCH_PIRX_REGISTER mPirxRegister[] = {
//Dev, Reg
  {31, R_PCH_PCR_ITSS_PIR0},  // D31 LPC/eSPI, P2SB, PMC, cAVS, SMBUS, SPI, GbE, TraceHub
  {29, R_PCH_PCR_ITSS_PIR1},  // D29 PCIe
  {28, R_PCH_PCR_ITSS_PIR2},  // D28 PCIe
  {23, R_PCH_PCR_ITSS_PIR3},  // D23 SATA
  {22, R_PCH_PCR_ITSS_PIR4},  // D22 HECI,IDER,KT
  {20, R_PCH_PCR_ITSS_PIR5},  // D20 USB, Camera, Thermal Subsystem
  {27, R_PCH_PCR_ITSS_PIR6}   // D27 PCIe (PCH-H)
};

#define PCH_DEV_NUM_MIN 18
#define PCH_DEV_NUM_MAX 31

#ifndef MDEPKG_NDEBUG
#define VALID_DEV_NO    0  ///< Device does not exist
#define VALID_DEV_YES   1  ///< Device exists

#define INTERRUPT_NO    0  ///< Device doesn't generate interrupts
#define INTERRUPT_YES   1  ///< Device generates interrupts

#define USES_PIRQ_NO    0  ///< Device does not route its interrupt to PIRQ
#define USES_PIRQ_YES   1  ///< Device is under INTx->PIRQy mapping

#define INTP_NO_REQ     0  ///< There is no requirement regarding INTP programming
#define INTP_MUST_SET   1  ///< INTP is RWO and needs to be programmed
#define INTP_IS_INTA    2  ///< INTP is required to be set to INTA
#define INTP_IS_INTB    3  ///< INTP is required to be set to INTB
#define INTP_IS_INTC    4  ///< INTP is required to be set to INTC
#define INTP_IS_INTD    5  ///< INTP is required to be set to INTD

#define IRQ_UNIQUE_NO       0  ///< IRQx can be shareable for this device
#define IRQ_UNIQUE_SERIALIO 1  ///< SerialIo devices need unique IRQ
#define IRQ_UNIQUE_SCS      2  ///< SCS devices need unique IRQ
#define IRQ_UNIQUE_OTG      3  ///< OTG device need unique IRQ
#define IRQ_UNIQUE_ISH      4  ///< ISH device need unique IRQ

typedef struct {
  UINT32        Device           :5;  ///< Device number
  UINT32        Function         :3;  ///< Device function
  UINT32        ValidDevice      :1;  ///< Flag which will indicate if DxFy i a PCH device
  UINT32        UsesInterrupts   :1;  ///< Flag indicating if device is using interrupts
  UINT32        UsesPirq         :1;  ///< Flag indicating that device uses INTx->PIRQ mapping
  UINT32        IntPinRequirement:3;  ///< Setting on how INTP reg should be treated
  ///
  /// 0 - IRQ can be shareable, other - for IRQ>23 it needs to be unique among all devices
  /// or if IRQ <=23 it needs to be unique only between devices with the same PortID
  ///
  UINT32        IrqUnique        :3;
  UINT32        Rsvd             :15; ///< Reserved
} PCH_DEV_INT_INFO;

//
// mPchDeviceInterruptInfo consist of information for whole range of devices related to PCH. This table must cover
// all possible device and function number (even if they are not a valid device or do not generate an interrupt).
// Data in table must be arranged in asceding order to be correctly consumed by functions which use it.
//
GLOBAL_REMOVE_IF_UNREFERENCED PCH_DEV_INT_INFO mPchDeviceInterruptInfo[] = {
  {18, 0, VALID_DEV_YES, INTERRUPT_NO , 0            , 0            , 0              }, // CSME: KVMcc,  desn't use interrupts
  {18, 1, VALID_DEV_YES, INTERRUPT_NO , 0            , 0            , 0              }, // CSME: Clink,  desn't use interrupts
  {18, 2, VALID_DEV_YES, INTERRUPT_NO , 0            , 0            , 0              }, // CSME: PMT,  desn't use interrupts
  {18, 3, VALID_DEV_YES, INTERRUPT_NO , 0            , 0            , 0              }, // CSME: CSE UMA
  {18, 4, VALID_DEV_YES, INTERRUPT_NO , 0            , 0            , 0              }, // CSME: fTPM DMA
  {18, 5, VALID_DEV_NO , 0            , 0            , 0            , 0              }, // Not a valid PCH device
  {18, 6, VALID_DEV_NO , 0            , 0            , 0            , 0              }, // Not a valid PCH device
  {18, 7, VALID_DEV_NO , 0            , 0            , 0            , 0              }, // Not a valid PCH device
  {19, 0, VALID_DEV_YES, INTERRUPT_YES, USES_PIRQ_NO , INTP_NO_REQ  , IRQ_UNIQUE_ISH }, // Integrated Sensor Hub
  {19, 1, VALID_DEV_NO , 0            , 0            , 0            , 0              }, // Not a valid PCH device
  {19, 2, VALID_DEV_NO , 0            , 0            , 0            , 0              }, // Not a valid PCH device
  {19, 3, VALID_DEV_NO , 0            , 0            , 0            , 0              }, // Not a valid PCH device
  {19, 4, VALID_DEV_NO , 0            , 0            , 0            , 0              }, // Not a valid PCH device
  {19, 5, VALID_DEV_NO , 0            , 0            , 0            , 0              }, // Not a valid PCH device
  {19, 6, VALID_DEV_NO , 0            , 0            , 0            , 0              }, // Not a valid PCH device
  {19, 7, VALID_DEV_NO , 0            , 0            , 0            , 0              }, // Not a valid PCH device
  {20, 0, VALID_DEV_YES, INTERRUPT_YES, USES_PIRQ_YES, INTP_NO_REQ  , IRQ_UNIQUE_NO  }, // USB 3.0 xHCI Controller
  {20, 1, VALID_DEV_YES, INTERRUPT_YES, USES_PIRQ_NO , INTP_NO_REQ  , IRQ_UNIQUE_OTG }, // USB Device Controller (OTG)
  {20, 2, VALID_DEV_YES, INTERRUPT_YES, USES_PIRQ_YES, INTP_MUST_SET, IRQ_UNIQUE_NO  }, // Thermal Subsystem
  {20, 3, VALID_DEV_YES, INTERRUPT_YES, USES_PIRQ_YES, INTP_IS_INTA , IRQ_UNIQUE_NO  }, // Camera IO Host Controller
  {20, 4, VALID_DEV_NO , 0            , 0            , 0            , 0              }, // TraceHub Phantom (ACPI) Function
  {20, 5, VALID_DEV_NO , 0            , 0            , 0            , 0              }, // Not a valid PCH device
  {20, 6, VALID_DEV_NO , 0            , 0            , 0            , 0              }, // Not a valid PCH device
  {20, 7, VALID_DEV_NO , 0            , 0            , 0            , 0              }, // Not a valid PCH device
  {21, 0, VALID_DEV_YES, INTERRUPT_YES, USES_PIRQ_NO , INTP_NO_REQ  , IRQ_UNIQUE_SERIALIO}, // SerialIo I2C Controller #0
  {21, 1, VALID_DEV_YES, INTERRUPT_YES, USES_PIRQ_NO , INTP_NO_REQ  , IRQ_UNIQUE_SERIALIO}, // SerialIo I2C Controller #1
  {21, 2, VALID_DEV_YES, INTERRUPT_YES, USES_PIRQ_NO , INTP_NO_REQ  , IRQ_UNIQUE_SERIALIO}, // SerialIo I2C Controller #2
  {21, 3, VALID_DEV_YES, INTERRUPT_YES, USES_PIRQ_NO , INTP_NO_REQ  , IRQ_UNIQUE_SERIALIO}, // SerialIo I2C Controller #3
  {21, 4, VALID_DEV_NO , 0            , 0            , 0            , 0              }, // Not a valid PCH device
  {21, 5, VALID_DEV_NO , 0            , 0            , 0            , 0              }, // Not a valid PCH device
  {21, 6, VALID_DEV_NO , 0            , 0            , 0            , 0              }, // Not a valid PCH device
  {21, 7, VALID_DEV_NO , 0            , 0            , 0            , 0              }, // Not a valid PCH device
  {22, 0, VALID_DEV_YES, INTERRUPT_YES, USES_PIRQ_YES, INTP_NO_REQ  , IRQ_UNIQUE_NO  }, // CSME: HECI #1
  {22, 1, VALID_DEV_YES, INTERRUPT_YES, USES_PIRQ_YES, INTP_NO_REQ  , IRQ_UNIQUE_NO  }, // CSME: HECI #2
  {22, 2, VALID_DEV_YES, INTERRUPT_YES, USES_PIRQ_YES, INTP_NO_REQ  , IRQ_UNIQUE_NO  }, // CSME: IDE-Redirection (IDE-R)
  {22, 3, VALID_DEV_YES, INTERRUPT_YES, USES_PIRQ_YES, INTP_NO_REQ  , IRQ_UNIQUE_NO  }, // CSME: Keyboard and Text (KT) Redirection
  {22, 4, VALID_DEV_YES, INTERRUPT_YES, USES_PIRQ_YES, INTP_NO_REQ  , IRQ_UNIQUE_NO  }, // CSME: HECI #3
  {22, 5, VALID_DEV_NO , 0            , 0            , 0            , 0              }, // Not a valid PCH device
  {22, 6, VALID_DEV_NO , 0            , 0            , 0            , 0              }, // Not a valid PCH device
  {22, 7, VALID_DEV_YES, INTERRUPT_NO , 0            , 0            , 0              }, // CSME: WLAN
  {23, 0, VALID_DEV_YES, INTERRUPT_YES, USES_PIRQ_YES, INTP_MUST_SET, IRQ_UNIQUE_NO  }, // SATA Controller
  {23, 1, VALID_DEV_NO , 0            , 0            , 0            , 0              }, // Not a valid PCH device
  {23, 2, VALID_DEV_NO , 0            , 0            , 0            , 0              }, // Not a valid PCH device
  {23, 3, VALID_DEV_NO , 0            , 0            , 0            , 0              }, // Not a valid PCH device
  {23, 4, VALID_DEV_NO , 0            , 0            , 0            , 0              }, // Not a valid PCH device
  {23, 5, VALID_DEV_NO , 0            , 0            , 0            , 0              }, // Not a valid PCH device
  {23, 6, VALID_DEV_NO , 0            , 0            , 0            , 0              }, // Not a valid PCH device
  {23, 7, VALID_DEV_NO , 0            , 0            , 0            , 0              }, // Not a valid PCH device
  {24, 0, VALID_DEV_NO , 0            , 0            , 0            , 0              }, // Reserved (used by RST PCIe Storage Cycle Router)
  {24, 1, VALID_DEV_NO , 0            , 0            , 0            , 0              }, // Not a valid PCH device
  {24, 2, VALID_DEV_NO , 0            , 0            , 0            , 0              }, // Not a valid PCH device
  {24, 3, VALID_DEV_NO , 0            , 0            , 0            , 0              }, // Not a valid PCH device
  {24, 4, VALID_DEV_NO , 0            , 0            , 0            , 0              }, // Not a valid PCH device
  {24, 5, VALID_DEV_NO , 0            , 0            , 0            , 0              }, // Not a valid PCH device
  {24, 6, VALID_DEV_NO , 0            , 0            , 0            , 0              }, // Not a valid PCH device
  {24, 7, VALID_DEV_NO , 0            , 0            , 0            , 0              }, // Not a valid PCH device
  {25, 0, VALID_DEV_YES, INTERRUPT_YES, USES_PIRQ_NO , INTP_NO_REQ  , IRQ_UNIQUE_SERIALIO}, // SerialIo UART Controller #2
  {25, 1, VALID_DEV_YES, INTERRUPT_YES, USES_PIRQ_NO , INTP_NO_REQ  , IRQ_UNIQUE_SERIALIO}, // SerialIo I2C Controller #5
  {25, 2, VALID_DEV_YES, INTERRUPT_YES, USES_PIRQ_NO , INTP_NO_REQ  , IRQ_UNIQUE_SERIALIO}, // SerialIo I2C Controller #4
  {25, 3, VALID_DEV_NO , 0            , 0            , 0            , 0              }, // Not a valid PCH device
  {25, 4, VALID_DEV_NO , 0            , 0            , 0            , 0              }, // Not a valid PCH device
  {25, 5, VALID_DEV_NO , 0            , 0            , 0            , 0              }, // Not a valid PCH device
  {25, 6, VALID_DEV_NO , 0            , 0            , 0            , 0              }, // Not a valid PCH device
  {25, 7, VALID_DEV_NO , 0            , 0            , 0            , 0              }, // Not a valid PCH device
  {26, 0, VALID_DEV_NO , 0            , 0            , 0            , 0              }, // Not a valid PCH device
  {26, 1, VALID_DEV_NO , 0            , 0            , 0            , 0              }, // Not a valid PCH device
  {26, 2, VALID_DEV_NO , 0            , 0            , 0            , 0              }, // Not a valid PCH device
  {26, 3, VALID_DEV_NO , 0            , 0            , 0            , 0              }, // Not a valid PCH device
  {26, 4, VALID_DEV_NO , 0            , 0            , 0            , 0              }, // Not a valid PCH device
  {26, 5, VALID_DEV_NO , 0            , 0            , 0            , 0              }, // Not a valid PCH device
  {26, 6, VALID_DEV_NO , 0            , 0            , 0            , 0              }, // Not a valid PCH device
  {26, 7, VALID_DEV_NO , 0            , 0            , 0            , 0              }, // Not a valid PCH device
  {27, 0, VALID_DEV_YES, INTERRUPT_YES, USES_PIRQ_YES, INTP_IS_INTA , IRQ_UNIQUE_NO  }, // PCI Express Port 17
  {27, 1, VALID_DEV_YES, INTERRUPT_YES, USES_PIRQ_YES, INTP_IS_INTB , IRQ_UNIQUE_NO  }, // PCI Express Port 18
  {27, 2, VALID_DEV_YES, INTERRUPT_YES, USES_PIRQ_YES, INTP_IS_INTC , IRQ_UNIQUE_NO  }, // PCI Express Port 19
  {27, 3, VALID_DEV_YES, INTERRUPT_YES, USES_PIRQ_YES, INTP_IS_INTD , IRQ_UNIQUE_NO  }, // PCI Express Port 20
  {27, 4, VALID_DEV_YES, INTERRUPT_YES, USES_PIRQ_YES, INTP_IS_INTA , IRQ_UNIQUE_NO  }, // PCI Express Port 21
  {27, 5, VALID_DEV_YES, INTERRUPT_YES, USES_PIRQ_YES, INTP_IS_INTB , IRQ_UNIQUE_NO  }, // PCI Express Port 22
  {27, 6, VALID_DEV_YES, INTERRUPT_YES, USES_PIRQ_YES, INTP_IS_INTC , IRQ_UNIQUE_NO  }, // PCI Express Port 23
  {27, 7, VALID_DEV_YES, INTERRUPT_YES, USES_PIRQ_YES, INTP_IS_INTD , IRQ_UNIQUE_NO  }, // PCI Express Port 24
  {28, 0, VALID_DEV_YES, INTERRUPT_YES, USES_PIRQ_YES, INTP_IS_INTA , IRQ_UNIQUE_NO  }, // PCI Express Port 1
  {28, 1, VALID_DEV_YES, INTERRUPT_YES, USES_PIRQ_YES, INTP_IS_INTB , IRQ_UNIQUE_NO  }, // PCI Express Port 2
  {28, 2, VALID_DEV_YES, INTERRUPT_YES, USES_PIRQ_YES, INTP_IS_INTC , IRQ_UNIQUE_NO  }, // PCI Express Port 3
  {28, 3, VALID_DEV_YES, INTERRUPT_YES, USES_PIRQ_YES, INTP_IS_INTD , IRQ_UNIQUE_NO  }, // PCI Express Port 4
  {28, 4, VALID_DEV_YES, INTERRUPT_YES, USES_PIRQ_YES, INTP_IS_INTA , IRQ_UNIQUE_NO  }, // PCI Express Port 5
  {28, 5, VALID_DEV_YES, INTERRUPT_YES, USES_PIRQ_YES, INTP_IS_INTB , IRQ_UNIQUE_NO  }, // PCI Express Port 6
  {28, 6, VALID_DEV_YES, INTERRUPT_YES, USES_PIRQ_YES, INTP_IS_INTC , IRQ_UNIQUE_NO  }, // PCI Express Port 7
  {28, 7, VALID_DEV_YES, INTERRUPT_YES, USES_PIRQ_YES, INTP_IS_INTD , IRQ_UNIQUE_NO  }, // PCI Express Port 8
  {29, 0, VALID_DEV_YES, INTERRUPT_YES, USES_PIRQ_YES, INTP_IS_INTA , IRQ_UNIQUE_NO  }, // PCI Express Port 9
  {29, 1, VALID_DEV_YES, INTERRUPT_YES, USES_PIRQ_YES, INTP_IS_INTB , IRQ_UNIQUE_NO  }, // PCI Express Port 10
  {29, 2, VALID_DEV_YES, INTERRUPT_YES, USES_PIRQ_YES, INTP_IS_INTC , IRQ_UNIQUE_NO  }, // PCI Express Port 11
  {29, 3, VALID_DEV_YES, INTERRUPT_YES, USES_PIRQ_YES, INTP_IS_INTD , IRQ_UNIQUE_NO  }, // PCI Express Port 12
  {29, 4, VALID_DEV_YES, INTERRUPT_YES, USES_PIRQ_YES, INTP_IS_INTA , IRQ_UNIQUE_NO  }, // PCI Express Port 13
  {29, 5, VALID_DEV_YES, INTERRUPT_YES, USES_PIRQ_YES, INTP_IS_INTB , IRQ_UNIQUE_NO  }, // PCI Express Port 14
  {29, 6, VALID_DEV_YES, INTERRUPT_YES, USES_PIRQ_YES, INTP_IS_INTC , IRQ_UNIQUE_NO  }, // PCI Express Port 15
  {29, 7, VALID_DEV_YES, INTERRUPT_YES, USES_PIRQ_YES, INTP_IS_INTD , IRQ_UNIQUE_NO  }, // PCI Express Port 16
  {30, 0, VALID_DEV_YES, INTERRUPT_YES, USES_PIRQ_NO , INTP_NO_REQ  , IRQ_UNIQUE_SERIALIO}, // SerialIo: UART #0
  {30, 1, VALID_DEV_YES, INTERRUPT_YES, USES_PIRQ_NO , INTP_NO_REQ  , IRQ_UNIQUE_SERIALIO}, // SerialIo: UART #1
  {30, 2, VALID_DEV_YES, INTERRUPT_YES, USES_PIRQ_NO , INTP_NO_REQ  , IRQ_UNIQUE_SERIALIO}, // SerialIo: SPI #0
  {30, 3, VALID_DEV_YES, INTERRUPT_YES, USES_PIRQ_NO , INTP_NO_REQ  , IRQ_UNIQUE_SERIALIO}, // SerialIo: SPI #1
  {30, 4, VALID_DEV_YES, INTERRUPT_YES, USES_PIRQ_NO , INTP_NO_REQ  , IRQ_UNIQUE_SCS }, // SCS: eMMC (SKL PCH-LP Only)
  {30, 5, VALID_DEV_YES, INTERRUPT_YES, USES_PIRQ_NO , INTP_NO_REQ  , IRQ_UNIQUE_SCS }, // SCS: SDIO (SKL PCH-LP Only)
  {30, 6, VALID_DEV_YES, INTERRUPT_YES, USES_PIRQ_NO , INTP_NO_REQ  , IRQ_UNIQUE_SCS }, // SCS: SDCard (SKL PCH-LP Only)
  {30, 7, VALID_DEV_NO , 0            , 0            , 0            , 0              }, // Not a valid PCH device
  {31, 0, VALID_DEV_YES, INTERRUPT_NO , 0            , 0            , 0              }, // LPC/eSPI Interface, desn't use interrupts
  {31, 1, VALID_DEV_YES, INTERRUPT_NO , 0            , 0            , 0              }, // P2SB, desn't use interrupts
  {31, 2, VALID_DEV_YES, INTERRUPT_NO , 0            , 0            , 0              }, // PMC , desn't use interrupts
  {31, 3, VALID_DEV_YES, INTERRUPT_YES, USES_PIRQ_YES, INTP_NO_REQ  , IRQ_UNIQUE_NO  }, // cAVS(Audio, Voice, Speach)
  {31, 4, VALID_DEV_YES, INTERRUPT_YES, USES_PIRQ_YES, INTP_MUST_SET, IRQ_UNIQUE_NO  }, // SMBus Controller
  {31, 5, VALID_DEV_YES, INTERRUPT_NO , 0            , 0            , 0              }, // SPI , desn't use interrupts
  {31, 6, VALID_DEV_YES, INTERRUPT_YES, USES_PIRQ_YES, INTP_MUST_SET, IRQ_UNIQUE_NO  }, // GbE Controller
  {31, 7, VALID_DEV_YES, INTERRUPT_YES, USES_PIRQ_YES, INTP_IS_INTA , IRQ_UNIQUE_NO  }  // TraceHub
};
#endif // MDEPKG_NDEBUG

/**
  Configures CSME SOL interrupt pin assignment

  @param[in] InterruptPin    INTx

  @retval Status
**/
EFI_STATUS
CsmeKtIntSet (
  IN UINT8   InterruptPin
  )
{
  UINT8      Response;
  UINT32     Data32;
  EFI_STATUS Status;
  ///
  /// Configure SOL's interrupt pin
  ///
  Data32 = InterruptPin;
  Status = PchSbiExecutionEx (
             PID_CSME12,
             0,
             PrivateControlWrite,
             FALSE,
             0x000F,
             0x0000,
             V_ME_SOL_FID,
             &Data32,
             &Response
             );
  ASSERT_EFI_ERROR (Status);

  Data32 = 0;
  Status = PchSbiExecutionEx (
             PID_CSME12,
             0,
             PrivateControlRead,
             FALSE,
             0x000F,
             0x0000,
             V_ME_SOL_FID,
             &Data32,
             &Response
             );

  return Status;
}

/**
  Configures PCI Express Port interrupt pin assignment

  @param[in] Device          Device number
  @param[in] Function        Function number
  @param[in] InterruptPin    INTx

  @retval Status
**/
EFI_STATUS
PciExpressIntSet (
  IN UINT8   Device,
  IN UINT8   Function,
  IN UINT8   InterruptPin
  )
{
  UINTN     Address;
  UINT32    Data32Or;
  UINT32    Data32And;

  //
  // Set Interrupt Pin
  //
  Address = MmPciBase (DEFAULT_PCI_BUS_NUMBER_PCH, Device, Function) + R_PCH_PCIE_STRPFUSECFG;
  Data32And = (UINT32) ~B_PCH_PCIE_STRPFUSECFG_PXIP;
  Data32Or = (UINT32) (InterruptPin) << N_PCH_PCIE_STRPFUSECFG_PXIP;
  MmioAndThenOr32 (Address, Data32And, Data32Or);
  return EFI_SUCCESS;
}

/**
  Configures SCS devices interrupt pin and IRQ assignment

  @param[in] Device          Device number
  @param[in] Function        Function number
  @param[in] InterruptPin    INTx
  @param[in] Irq             IRQ

  @retval Status
**/
EFI_STATUS
ScsDevicesIntSet (
  IN UINT8   Device,
  IN UINT8   Function,
  IN UINT8   InterruptPin,
  IN UINT8   Irq
  )
{
  UINT16    Offset;
  UINT32    Data32Or;
  UINT32    Data32And;
  UINT8     PortId;

  PortId = PID_SCS;
  Offset = R_PCH_PCR_SCS_PCICFGCTR_EMMC + (Function - 4)*0x4;

  //
  // Set Interrupt Pin and Irq number
  //
  Data32Or =  (UINT32) (InterruptPin) << N_PCH_PCR_SCS_PCICFGCTR_IPIN1;
  Data32And =~(UINT32) (B_PCH_PCR_SCS_PCICFGCTR_PCI_IRQ | B_PCH_PCR_SCS_PCICFGCTR_ACPI_IRQ | B_PCH_PCR_SCS_PCICFGCTR_IPIN1);

  //
  // ACPI interrupt number
  //
  Data32Or |= (UINT32) (Irq << N_PCH_PCR_SCS_PCICFGCTR_ACPI_IRQ);
  //
  // PCI interrupt number
  //
  Data32Or |= (UINT32) (Irq << N_PCH_PCR_SCS_PCICFGCTR_PCI_IRQ);

  PchPcrAndThenOr32 (PortId, Offset, Data32And, Data32Or);
  return EFI_SUCCESS;
}

/**
  Configures ISH device interrupt pin and IRQ assignment

  @param[in] InterruptPin    INTx
  @param[in] Irq             IRQ

  @retval Status
**/
EFI_STATUS
IshDevicesIntSet (
  IN UINT8   InterruptPin,
  IN UINT8   Irq
  )
{
  UINT32    Data32Or;
  UINT32    Data32And;

  //
  // Set Interrupt Pin and Irq number
  //
  Data32Or =  (UINT32) (InterruptPin) << N_PCH_PCR_ISH_PCICFGCTR_IPIN1;
  Data32And =~(UINT32) (B_PCH_PCR_ISH_PCICFGCTR_PCI_IRQ | B_PCH_PCR_ISH_PCICFGCTR_ACPI_IRQ | B_PCH_PCR_ISH_PCICFGCTR_IPIN1);

  //
  // ACPI interrupt number
  //
  Data32Or |= (UINT32) (Irq << N_PCH_PCR_ISH_PCICFGCTR_ACPI_IRQ);
  //
  // PCI interrupt number
  //
  Data32Or |= (UINT32) (Irq << N_PCH_PCR_ISH_PCICFGCTR_PCI_IRQ);

  PchPcrAndThenOr32 (PID_ISHBR, R_PCH_PCR_ISH_PCICFGCTRL, Data32And, Data32Or);
  return EFI_SUCCESS;
}

/**
  Configures SerilIo devices interrupt pin and IRQ assignment

  @param[in] Device          Device number
  @param[in] Function        Function number
  @param[in] InterruptPin    INTx
  @param[in] Irq             IRQ

  @retval Status
**/
EFI_STATUS
SerialIoIntSet (
  IN UINT8   Device,
  IN UINT8   Function,
  IN UINT8   InterruptPin,
  IN UINT8   Irq
  )
{
  UINT16    Offset;
  UINT32    Data32Or;
  UINT32    Data32And;
  UINTN     i;

  Offset = 0x0;

  //
  // Match SerialIo Dxx:Fx with appropriate PCICFGCTRLx register
  //
  for (i = 0; i < PCH_SERIALIO_MAX_CONTROLLERS; i++) {
    if (mSerialIoCfgCtrl[i].DevNum == Device && mSerialIoCfgCtrl[i].FuncNum == Function) {
      Offset = mSerialIoCfgCtrl[i].PciCfgCtrAddr;
    }
  }
  ASSERT (Offset != 0);
  //
  // Set Interrupt Pin and Irq number
  //
  Data32Or  = (UINT32) (InterruptPin) << N_PCH_PCR_SERIAL_IO_PCICFGCTRL_INT_PIN;
  Data32And =~(UINT32) (B_PCH_PCR_SERIAL_IO_PCICFGCTRL_PCI_IRQ | B_PCH_PCR_SERIAL_IO_PCICFGCTRL_ACPI_IRQ | B_PCH_PCR_SERIAL_IO_PCICFGCTRL_INT_PIN);

  //
  // ACPI interrupt number
  //
  Data32Or |= (UINT32) (Irq << N_PCH_PCR_SERIAL_IO_PCICFGCTRL_ACPI_IRQ);

  //
  // PCI interrupt number
  //
  Data32Or |= (UINT32) (Irq << N_PCH_PCR_SERIAL_IO_PCICFGCTRL_PCI_IRQ);

  PchPcrAndThenOr32 (PID_SERIALIO, Offset, Data32And, Data32Or);
  return EFI_SUCCESS;
}

/**
  Configures OTG device interrupt pin and IRQ assignment

  @param[in] Device          Device number
  @param[in] Function        Function number
  @param[in] InterruptPin    INTx
  @param[in] Irq             IRQ

  @retval Status
**/
EFI_STATUS
OtgIntSet (
  IN UINT8   Device,
  IN UINT8   Function,
  IN UINT8   InterruptPin,
  IN UINT8   Irq
  )
{
  UINT32    Data32Or;
  UINT32    Data32And;

  //
  // Set Interrupt Pin and Irq number
  //
  Data32Or =  (UINT32) (InterruptPin) << N_PCH_PCR_OTG_PCICFGCTRL_INT_PIN;
  Data32And =~(UINT32) (B_PCH_PCR_OTG_PCICFGCTRL_PCI_IRQ | B_PCH_PCR_OTG_PCICFGCTRL_ACPI_IRQ | B_PCH_PCR_OTG_PCICFGCTRL_INT_PIN | B_PCH_PCR_OTG_PCICFGCTRL_ACPI_INT_EN);

  //
  // ACPI interrupt number
  //
  Data32Or |= (UINT32) (Irq << N_PCH_PCR_OTG_PCICFGCTRL_ACPI_IRQ);

  //
  // PCI interrupt number
  //
  Data32Or |= (UINT32) (Irq << N_PCH_PCR_OTG_PCICFGCTRL_PCI_IRQ);

  PchPcrAndThenOr32 (PID_OTG, R_PCH_PCR_OTG_PCICFGCTRL1, Data32And, Data32Or);

  return EFI_SUCCESS;
}

/**
  Configures HD Audio interrupt pin and IRQ assignment

  @param[in] InterruptPin    INTx
  @param[in] Irq             IRQ

  @retval Status
**/

EFI_STATUS
HdAudioIntSet (
  IN UINT8   InterruptPin,
  IN UINT8   Irq
  )
{
  UINTN     Address;
  UINT32    Data32Or;
  UINT32    Data32And;
  //
  // Set Interrupt Pin
  //
  Address = MmPciBase (DEFAULT_PCI_BUS_NUMBER_PCH,PCI_DEVICE_NUMBER_PCH_HDA, PCI_FUNCTION_NUMBER_PCH_HDA) + PCI_INT_PIN_OFFSET;

  MmioWrite8 (Address, InterruptPin);
  //
  // Assign ACPI interrupt number
  //
  Data32And = ~(UINT32) (B_PCH_PCR_HDA_PCICDCCFG_ACPIIN);
  Data32Or = (UINT32) (Irq << N_PCH_PCR_HDA_PCICDCCFG_ACPIIN);
  PchPcrAndThenOr32 (PID_DSP, R_PCH_PCR_HDA_PCICDCCFG, Data32And, Data32Or);

  return EFI_SUCCESS;
}

/**
  Configures interrupt pin assignment for standard PCI device

  @param[in] Device          Device number
  @param[in] Function        Function number
  @param[in] InterruptPin    INTx

  @retval Status
**/
EFI_STATUS
StandardIntSet (
  IN UINT8   Device,
  IN UINT8   Function,
  IN UINT8   InterruptPin
  )
{
  UINTN     Address;

  Address = MmPciBase (DEFAULT_PCI_BUS_NUMBER_PCH,Device,Function) + PCI_INT_PIN_OFFSET;

  MmioWrite8 (Address, InterruptPin);

  return EFI_SUCCESS;
}

/**
  Configures interrupt number for SCI.
  Allowed values are IRQ9-11,20-23

  @param[in] Irq                 Irq number

  @retval Status
**/
EFI_STATUS
PchSciIrqSet (
  IN  UINT8          Irq
  )
{
  UINT32  Data32Or;
  UINTN   PciPmcRegBase;
  //
  // IRQx    Value to set in register
  // IRQ9    000b
  // IRQ10   001b
  // IRQ11   010b
  // IRQ20   100b
  // IRQ21   101b
  // IRQ22   110b
  // IRQ23   111b
  //
  switch (Irq) {
    case 9:  Data32Or = V_PCH_PMC_ACPI_CNT_SCIS_IRQ9;  break;
    case 10: Data32Or = V_PCH_PMC_ACPI_CNT_SCIS_IRQ10; break;
    case 11: Data32Or = V_PCH_PMC_ACPI_CNT_SCIS_IRQ11; break;
    case 20: Data32Or = V_PCH_PMC_ACPI_CNT_SCIS_IRQ20; break;
    case 21: Data32Or = V_PCH_PMC_ACPI_CNT_SCIS_IRQ21; break;
    case 22: Data32Or = V_PCH_PMC_ACPI_CNT_SCIS_IRQ22; break;
    case 23: Data32Or = V_PCH_PMC_ACPI_CNT_SCIS_IRQ23; break;
    default:
      ASSERT (FALSE);
      return EFI_INVALID_PARAMETER;
  }
  PciPmcRegBase   = MmPciBase (
                      DEFAULT_PCI_BUS_NUMBER_PCH,
                      PCI_DEVICE_NUMBER_PCH_PMC,
                      PCI_FUNCTION_NUMBER_PCH_PMC
                      );
  MmioAndThenOr32 (
    PciPmcRegBase + R_PCH_PMC_ACPI_CNT,
    ~(UINT32) B_PCH_PMC_ACPI_CNT_SCIS,
    Data32Or
    );

  return EFI_SUCCESS;
}

/**
  Configures interrupt number and enables interrupt generation for TCO.

  @param[in] Irq                 IRQ number
  @param[in] IrqEnable           Enable/Disable TCO IRQ

  @retval Status
**/
EFI_STATUS
PchTcoIrqSet (
  IN  UINT8          Irq,
  IN  UINT8          IrqEnable
  )
{
  UINT32  Data32Or;
  //
  // IRQx    Value to set in register
  // IRQ9    000b
  // IRQ10   001b
  // IRQ11   010b
  // IRQ20   100b
  // IRQ21   101b
  // IRQ22   110b
  // IRQ23   111b
  //
  switch (Irq) {
    case 9:  Data32Or = V_PCH_PCR_SMBUS_TCOCFG_IRQ_9;  break;
    case 10: Data32Or = V_PCH_PCR_SMBUS_TCOCFG_IRQ_10; break;
    case 11: Data32Or = V_PCH_PCR_SMBUS_TCOCFG_IRQ_11; break;
    case 20: Data32Or = V_PCH_PCR_SMBUS_TCOCFG_IRQ_20; break;
    case 21: Data32Or = V_PCH_PCR_SMBUS_TCOCFG_IRQ_21; break;
    case 22: Data32Or = V_PCH_PCR_SMBUS_TCOCFG_IRQ_22; break;
    case 23: Data32Or = V_PCH_PCR_SMBUS_TCOCFG_IRQ_23; break;
    default:
      ASSERT (FALSE);
      return EFI_INVALID_PARAMETER;
  }

  if (IrqEnable != 0) {
    Data32Or |= B_PCH_PCR_SMBUS_TCOCFG_IE;
  }

  PchPcrAndThenOr32 (
    PID_SMB, R_PCH_PCR_SMBUS_TCOCFG,
    ~(UINT32) (B_PCH_PCR_SMBUS_TCOCFG_IS | B_PCH_PCR_SMBUS_TCOCFG_IE),
    Data32Or
    );

  return EFI_SUCCESS;
}

/**
  This function will configure ITSS.PIRx registers for INTx->PIRy routing
  based on devices interrupt pin (INTx) and choosen IRQ for it.

  @param[in] DevIntConfigEntry       Table with interrupt assignment
  @param[in] DevIntConfigEntrySize   Number of entries in interrupt assignment table

**/
VOID
UpdatePirxRegs (
  IN PCH_DEVICE_INTERRUPT_CONFIG     *DevIntConfigEntry,
  IN UINT8                           DevIntConfigEntrySize
  )
{
  UINT16      PirxIndex;
  UINT16      DevIndex;
  UINT16      Data16;

  for (PirxIndex = 0; PirxIndex < sizeof (mPirxRegister) /sizeof (PCH_PIRX_REGISTER); PirxIndex++) {
    //
    // Default value for each PIRx register is 3210h
    //
    Data16 = 0x3210;
    for (DevIndex = 0; DevIndex < DevIntConfigEntrySize; DevIndex++) {
      if (DevIntConfigEntry[DevIndex].Device == mPirxRegister[PirxIndex].Device) {
        if (DevIntConfigEntry[DevIndex].Device == PCI_DEVICE_NUMBER_PCH_XDCI &&
            DevIntConfigEntry[DevIndex].Function == PCI_FUNCTION_NUMBER_PCH_XDCI) {
          //
          // OTG device is not under INTx->PIRQy mapping so its interrupt setting
          // should not influence PIRx registers programming
          //
          continue;
        }

        Data16 &= ~(UINT16) (0xF << (4*(DevIntConfigEntry[DevIndex].IntX - PchIntA)));
        Data16 |= (UINT16) ((DevIntConfigEntry[DevIndex].Irq - 16) << (4*(DevIntConfigEntry[DevIndex].IntX - PchIntA)));
      }
    }
    PchPcrWrite16 (PID_ITSS, mPirxRegister[PirxIndex].Register, Data16);
  }
}

/**
  This function will configure ITSS.PxRC registers.

  @param[in] PxRcConfig      Table with legacy 8259 mapping (PIRQx -> IRQy)
  @param[in] PxRcConfigSize  Number of entries in PxRcConfig

  @retval None
**/
VOID
UpdatePxRcRegs (
  IN UINT8                      *PxRcConfig,
  IN UINT8                      PxRcConfigSize
  )
{
  UINT8       Index;

  //
  // Program PxRC registers
  //
  for (Index = 0; Index < PxRcConfigSize; Index++) {
    ASSERT (PxRcConfig[Index] < 16 && PxRcConfig[Index] > 2 && PxRcConfig[Index] != 8 && PxRcConfig[Index] != 13);
    PchPcrWrite8 (PID_ITSS, R_PCH_PCR_ITSS_PIRQA_ROUT + Index, PxRcConfig[Index]);
  }
}

#ifndef MDEPKG_NDEBUG
/**
  Check interrupt assignment, provide information if detected improper interrupt setting

  @param[in] DevIntConfigEntry        Table with interrupt assignment
  @param[in] DevIntConfigEntrySize    Number of entries in interrupt assignment table

  @retval Status
**/
EFI_STATUS
CheckInterruptSettings (
  IN PCH_DEVICE_INTERRUPT_CONFIG      *DevIntConfigEntry,
  IN UINT8                            DevIntConfigEntrySize
  )
{
  DEBUG_CODE_BEGIN ();
  //
  // Algorithm which will parse whole table and check it correctness, to prevent
  // users from trying to set PCH devices interrupt in non supported way.
  // Function is divided into few step, each verifying different cases:
  // Point 1.
  //  - Entry for certain DxFy appears more than once
  //  - Device is outside D18Fx-D31Fx range
  // Point 2.
  //  - InterruptConfig table contains invalid DxFy (does not generate interrupt or does not exist)
  //  - Device which falls under INTx->PIRQy mapping has its IRQ set outside IRQ16-23 range
  //  - Device uses IRQ 0, 2 or 8
  // Point 3.
  //  - Single function device does not use INTA
  // Point 4.
  //  - Within multifunctional devices same interrupt pin (INTx) is routed to different PIRQy (IRQ16-23)
  // Point 5.
  //  - Devices which have interrupt pin setting as RWO are not programmed
  //  - Devices which have requirement for interrupt pin configuration are not programmed correctly
  //  - InterruptConfig has InterruptPin setting not matching default value of INTP register when it is RO
  // Point 6.
  //  - PCI Express Root Ports mapping are recommended to be programmed only with one set of values:
  //     D(29/28/27)Fy -> INTP = (y % 4) , IRQ = 16 + (y % 4)
  //    otherwise _PRT methods in ACPI for RootPorts would require additional patching as
  //    PCIe Endpoint Device Interrupt is further subjected to INTx to PIRQy Mapping
  // Point 7.
  //  - Devices which should have unique interrupt share it
  // Point 8.
  //  - GPIO pads which are routed to IOxAPIC cause an IRQ which is already in use by other device or pad
  //
  // Note: this routine is not able to check if eSPI device is using IRQ >=24 and if it collides with other devices or GPIO pads IRQ usage
  //

  UINT8            PchDeviceIntInfoIndex;
  UINT8            PchDeviceIntInfoIndex2;
  UINT8            DevIntConfigIndex;
  UINT8            DevIntConfigIndex2;
  UINT8            Index;
  UINT8            PchDeviceIntInfoSize;
  BOOLEAN          DevExist;
  BOOLEAN          IrqError;
  BOOLEAN          SingleFunctionDev;
  UINT32           CurrentDevice;
  UINT8            FunctionNumber;
  UINT8            IntRouting[4];
  GPIO_GROUP       GroupMin;
  GPIO_GROUP       GroupMax;
  GPIO_GROUP       Group;
  UINT32           PadNumber;
  GPIO_PAD         GpioPad;
  UINT32           GpioIrqNumber;
  GPIO_CONFIG      GpioData;
  GPIO_PAD_OWN     PadOwnVal;

  ///
  /// Value of 1 on selected bit position indicates that IRQ is being used
  /// IrqUsage[0] - for IRQ0-31
  /// IrqUsage[1] - for IRQ31-63
  /// IrqUsage[2] - for IRQ64-95
  /// IrqUsage[3] - for IRQ96-127
  ///
  UINT32         IrqUsage[4];

  ZeroMem (IrqUsage, sizeof (IrqUsage));
  PchDeviceIntInfoSize = sizeof (mPchDeviceInterruptInfo) /sizeof (PCH_DEV_INT_INFO);
  //
  // 1.Check if for each DxFy there is only one entry and if none of devices is outside 18-31 range
  //
  for (DevIntConfigIndex = 0; DevIntConfigIndex < DevIntConfigEntrySize; DevIntConfigIndex++) {

    if ((DevIntConfigEntry[DevIntConfigIndex].Device < PCH_DEV_NUM_MIN) ||
        (DevIntConfigEntry[DevIntConfigIndex].Device > PCH_DEV_NUM_MAX)) {
      //
      // Report an error if device number is outside 18-31 range
      //
      DEBUG ((DEBUG_ERROR, "InterruptConfig ERROR: InterruptConfig has a device (D%dF%d) which is outside D18-D31 range!\n",
              DevIntConfigEntry[DevIntConfigIndex].Device,
              DevIntConfigEntry[DevIntConfigIndex].Function));
      ASSERT (FALSE);
      return EFI_INVALID_PARAMETER;
    }

    for (DevIntConfigIndex2 = DevIntConfigIndex + 1; DevIntConfigIndex2 < DevIntConfigEntrySize; DevIntConfigIndex2++) {

      if ((DevIntConfigEntry[DevIntConfigIndex].Device == DevIntConfigEntry[DevIntConfigIndex2].Device) &&
          (DevIntConfigEntry[DevIntConfigIndex].Function == DevIntConfigEntry[DevIntConfigIndex2].Function)) {
        //
        // Report an error if entry appears more than once
        //
        DEBUG ((DEBUG_ERROR, "InterruptConfig ERROR: Entry for D%dF%d appears more than once!\n",
                DevIntConfigEntry[DevIntConfigIndex].Device,
                DevIntConfigEntry[DevIntConfigIndex].Function));
        ASSERT (FALSE);
        return EFI_INVALID_PARAMETER;
      }
    }
  }

  //
  // 2.Check if for each DnFx selected IRQ is supported for device. If device uses INTx->PIRQy mapping
  //   must have IRQ  >= 16 and IRQ <= 23. Report an error if DevIntConfigEntry[] consist of
  //   device which does not generate interrupts, is not a valid device or uses IRQ0,2,8
  //
  for (DevIntConfigIndex = 0; DevIntConfigIndex < DevIntConfigEntrySize; DevIntConfigIndex++) {

    DevExist = FALSE;

    PchDeviceIntInfoIndex = (DevIntConfigEntry[DevIntConfigIndex].Device - PCH_DEV_NUM_MIN)*8 + DevIntConfigEntry[DevIntConfigIndex].Function;
    if (mPchDeviceInterruptInfo[PchDeviceIntInfoIndex].ValidDevice == VALID_DEV_YES) {

      DevExist = TRUE;
      //
      // Check if InterruptConfig consist of entry for device which does not generate interrupt
      //
      if (mPchDeviceInterruptInfo[PchDeviceIntInfoIndex].UsesInterrupts == INTERRUPT_NO) {
        DEBUG ((DEBUG_ERROR, "InterruptConfig ERROR: D%dF%d does not generate interrupts!\n",
                DevIntConfigEntry[DevIntConfigIndex].Device,
                DevIntConfigEntry[DevIntConfigIndex].Function));
        ASSERT (FALSE);
        return EFI_INVALID_PARAMETER;
      }

      //
      // Check if for device which uses INTx -> PIRQy mapping has its IRQ set outside 16 to 23 range
      // NOTE: If cAVS/HDa is going to be supported in ACPI mode then this check needs to be rewritten.
      // HDa in PCI mode is under INTx->PIRQy mapping but in ACPI mode can have its IRQ outside 16 to 23 range.
      //
      if (mPchDeviceInterruptInfo[PchDeviceIntInfoIndex].UsesPirq == USES_PIRQ_YES) {
        if (DevIntConfigEntry[DevIntConfigIndex].Irq < 16 || DevIntConfigEntry[DevIntConfigIndex].Irq > 23) {
          DEBUG ((DEBUG_ERROR, "InterruptConfig ERROR: D%dF%d has its IRQ outside 16 to 23 range!\n",
                  DevIntConfigEntry[DevIntConfigIndex].Device,
                  DevIntConfigEntry[DevIntConfigIndex].Function));
          ASSERT (FALSE);
          return EFI_INVALID_PARAMETER;
        }
      }

      //
      // Check if IRQ for device is not set to 0,2 or 8
      //
      if ((DevIntConfigEntry[DevIntConfigIndex].Irq == 0) ||
          (DevIntConfigEntry[DevIntConfigIndex].Irq == 2) ||
          (DevIntConfigEntry[DevIntConfigIndex].Irq == 8)) {
        DEBUG ((DEBUG_ERROR, "InterruptConfig ERROR: Device D%dF%d must not use IRQ%d!\n",
                DevIntConfigEntry[DevIntConfigIndex].Device,
                DevIntConfigEntry[DevIntConfigIndex].Function,
                DevIntConfigEntry[DevIntConfigIndex].Irq));
        ASSERT (FALSE);
        return EFI_INVALID_PARAMETER;
      }
    }

    //
    // If device from InterruptConfig was not found in mPchDeviceInterruptInfo[] table then
    // it it is not a valid entry.
    //
    if (DevExist == FALSE) {
      DEBUG ((DEBUG_ERROR, "InterruptConfig ERROR: D%dF%d is not a valid device!\n",
              DevIntConfigEntry[DevIntConfigIndex].Device,
              DevIntConfigEntry[DevIntConfigIndex].Function));
      ASSERT (FALSE);
      return EFI_INVALID_PARAMETER;
    }
  }

  //
  // 3.Check if single function device is set to use INTA
  //
  // Locate in mPchDeviceInterruptInfo table single function devices, if found one locate it in InterruptConfig
  // and check if it uses INTA.
  //
  for (PchDeviceIntInfoIndex = 0; PchDeviceIntInfoIndex < PchDeviceIntInfoSize; PchDeviceIntInfoIndex+=8) {
    if (mPchDeviceInterruptInfo[PchDeviceIntInfoIndex].ValidDevice == VALID_DEV_NO) {
      //
      // If DxF0 is not a valid device move to next one.
      //
      continue;
    }
    SingleFunctionDev = TRUE;

    for (PchDeviceIntInfoIndex2 = PchDeviceIntInfoIndex + 1; PchDeviceIntInfoIndex2 < PchDeviceIntInfoIndex + 8; PchDeviceIntInfoIndex2++) {
      //
      // Check other functions of this device (DxF1-DxF7)
      //
      if (mPchDeviceInterruptInfo[PchDeviceIntInfoIndex2].ValidDevice == VALID_DEV_YES) {
        //
        // If found another valid device for certain device number then this is not a signle function device.
        //
        SingleFunctionDev = FALSE;
        break;
      }
    }

    if (SingleFunctionDev == TRUE) {
      //
      // Found a single function device, try to locate it InterruptConfig
      //
      for (DevIntConfigIndex = 0; DevIntConfigIndex < DevIntConfigEntrySize; DevIntConfigIndex++) {

        if (DevIntConfigEntry[DevIntConfigIndex].Device == mPchDeviceInterruptInfo[PchDeviceIntInfoIndex].Device) {
          //
          // Found device in InterruptConfig, check its interrupt pin
          //
          if (DevIntConfigEntry[DevIntConfigIndex].IntX != PchIntA) {
            //
            // If single function device doesn't use INTA report an error
            //
            DEBUG ((DEBUG_ERROR, "InterruptConfig ERROR: Single function device %d isn't configured to use INTA!\n",DevIntConfigEntry[DevIntConfigIndex].Device));
            ASSERT (FALSE);
            return EFI_INVALID_PARAMETER;
          }
        }
      }
    }
  }

  //
  // 4.Check if for one device which uses INTx->PIRQy mapping different functions
  //   with the same INTx are routed to different PIRQs (IRQ16-23)
  //
  CurrentDevice = 0;
  for (PchDeviceIntInfoIndex = 0; PchDeviceIntInfoIndex < PchDeviceIntInfoSize; PchDeviceIntInfoIndex++) {
    if ((mPchDeviceInterruptInfo[PchDeviceIntInfoIndex].Device == CurrentDevice) ||
        (mPchDeviceInterruptInfo[PchDeviceIntInfoIndex].UsesPirq == USES_PIRQ_NO) ||
        (mPchDeviceInterruptInfo[PchDeviceIntInfoIndex].ValidDevice == VALID_DEV_NO)) {
      //
      // Skip to next device if current was already analyzed,
      // it doesn't use INTx->PIRQy mapping or it is not a PCH device
      //
      continue;
    }
    CurrentDevice = mPchDeviceInterruptInfo[PchDeviceIntInfoIndex].Device;
    ZeroMem (IntRouting, sizeof (IntRouting));

    for (DevIntConfigIndex = 0; DevIntConfigIndex < DevIntConfigEntrySize; DevIntConfigIndex++) {

      if (DevIntConfigEntry[DevIntConfigIndex].Device == CurrentDevice) {

        if ((DevIntConfigEntry[DevIntConfigIndex].IntX >= PchIntA) &&
            (DevIntConfigEntry[DevIntConfigIndex].IntX <= PchIntD)) {
          //
          // Check if INTx is mapped to the same PIRQy for all functions within one device.
          // NOTE: If cAVS/HDa is going to be supported in ACPI mode then this check needs to be rewritten.
          // HDa in PCI mode is under INTx->PIRQy mapping but when in ACPI mode it can have its IRQ set
          // outside 16 to 23 range and doesn't need to meet criteria analyzed here.
          //
          if (IntRouting[DevIntConfigEntry[DevIntConfigIndex].IntX - PchIntA] == 0) {
            IntRouting[DevIntConfigEntry[DevIntConfigIndex].IntX - PchIntA] = DevIntConfigEntry[DevIntConfigIndex].Irq;
          } else if (IntRouting[DevIntConfigEntry[DevIntConfigIndex].IntX - PchIntA] != DevIntConfigEntry[DevIntConfigIndex].Irq) {
            DEBUG ((DEBUG_ERROR, "InterruptConfig ERROR: For D%d INT%c is mapped to different IRQs!\n",
                    CurrentDevice,
                    DevIntConfigEntry[DevIntConfigIndex].IntX + 64));
            ASSERT (FALSE);
            return EFI_INVALID_PARAMETER;
          }
        }
      }
    }
  }

  //
  // 5. Check if devices which have special requirement regarding InterruptPin
  //    are properly configured in InterruptConfig table
  //
  for (PchDeviceIntInfoIndex = 0; PchDeviceIntInfoIndex < PchDeviceIntInfoSize; PchDeviceIntInfoIndex++) {
    if ((mPchDeviceInterruptInfo[PchDeviceIntInfoIndex].IntPinRequirement != INTP_NO_REQ) &&
        (mPchDeviceInterruptInfo[PchDeviceIntInfoIndex].ValidDevice == VALID_DEV_YES)) {
      //
      // Found a device which has special requirement regarding interrupt pin.
      // If devices requires its INTP register programmed then entry for this device must be included
      // in InterruptConfig.
      // If INTP is RO register, then either this device may be omitted in InterruptConfig or
      // if included then InterruptPin value must match the one preset in this register.
      //
      DevExist = FALSE;
      for (DevIntConfigIndex = 0; DevIntConfigIndex < DevIntConfigEntrySize; DevIntConfigIndex++) {

        if ((DevIntConfigEntry[DevIntConfigIndex].Device == mPchDeviceInterruptInfo[PchDeviceIntInfoIndex].Device) &&
            (DevIntConfigEntry[DevIntConfigIndex].Function == mPchDeviceInterruptInfo[PchDeviceIntInfoIndex].Function)) {

          if (mPchDeviceInterruptInfo[PchDeviceIntInfoIndex].IntPinRequirement == INTP_MUST_SET) {
            //
            // Device  which required its INTP to be set was found, move to next one
            //
            DevExist = TRUE;
            break;
          } else {
            //
            // If device has its INTP in RO register or there are other requirements for it,
            // then InterruptConfig must match expected configuration
            //
            if ((UINT32) (DevIntConfigEntry[DevIntConfigIndex].IntX - PchIntA) != (mPchDeviceInterruptInfo[PchDeviceIntInfoIndex].IntPinRequirement - INTP_IS_INTA)) {
              DEBUG ((DEBUG_ERROR, "InterruptConfig ERROR: Device D%dF%d can use only INT%c!\n",
                      mPchDeviceInterruptInfo[PchDeviceIntInfoIndex].Device,
                      mPchDeviceInterruptInfo[PchDeviceIntInfoIndex].Function,
                      mPchDeviceInterruptInfo[PchDeviceIntInfoIndex].IntPinRequirement - INTP_IS_INTA + 65));
              ASSERT (FALSE);
              return EFI_INVALID_PARAMETER;
            }
          }
        }
      }
      if ((DevExist == FALSE) &&
          (mPchDeviceInterruptInfo[PchDeviceIntInfoIndex].IntPinRequirement == INTP_MUST_SET)) {
        //
        // If after analyzing all entries in DevIntConfigEntry[] table
        // there is no required device, report an error
        //
        DEBUG ((DEBUG_ERROR, "InterruptConfig ERROR: Device D%dF%d is not included in InterruptConfig table!\n",
                mPchDeviceInterruptInfo[PchDeviceIntInfoIndex].Device,
                mPchDeviceInterruptInfo[PchDeviceIntInfoIndex].Function));
        ASSERT (FALSE);
        return EFI_INVALID_PARAMETER;
      }
    }
  }

  //
  // 6. Check if PCI Express Root Ports mapping is programmed in following way
  //    D(27-29)Fy -> INTP = (y % 4) , IRQ = 16 + (y % 4)
  //
  for (DevIntConfigIndex = 0; DevIntConfigIndex < DevIntConfigEntrySize; DevIntConfigIndex++) {
    if ((DevIntConfigEntry[DevIntConfigIndex].Device == PCI_DEVICE_NUMBER_PCH_PCIE_DEVICE_1) ||
        (DevIntConfigEntry[DevIntConfigIndex].Device == PCI_DEVICE_NUMBER_PCH_PCIE_DEVICE_2) ||
        (DevIntConfigEntry[DevIntConfigIndex].Device == PCI_DEVICE_NUMBER_PCH_PCIE_DEVICE_3)) {

      FunctionNumber = DevIntConfigEntry[DevIntConfigIndex].Function;
      if ((DevIntConfigEntry[DevIntConfigIndex].Irq != (16 + (FunctionNumber % 4))) ||
          ((DevIntConfigEntry[DevIntConfigIndex].IntX - PchIntA) != (FunctionNumber % 4))) {

        DEBUG ((DEBUG_ERROR, "InterruptConfig ERROR: RootPort Device D%dF%d is not programmed with recommended interrupt settings!\n",
                DevIntConfigEntry[DevIntConfigIndex].Device,
                DevIntConfigEntry[DevIntConfigIndex].Function));
        ASSERT (FALSE);
        return EFI_INVALID_PARAMETER;
      }
    }
  }

  //
  // 7. Check if devices which need unique IRQ do not share it with other devices.
  //
  IrqError = FALSE;
  for (DevIntConfigIndex = 0; DevIntConfigIndex < DevIntConfigEntrySize; DevIntConfigIndex++) {
    //
    // Save IRQ number used by this device. This information will be needed for Step 7
    // for GPIO interrupts check.
    //
    IrqUsage[DevIntConfigEntry[DevIntConfigIndex].Irq >> 5]|= 0x1 << (DevIntConfigEntry[DevIntConfigIndex].Irq % 32);

    PchDeviceIntInfoIndex = (DevIntConfigEntry[DevIntConfigIndex].Device - PCH_DEV_NUM_MIN) * 8 + DevIntConfigEntry[DevIntConfigIndex].Function;
    if (mPchDeviceInterruptInfo[PchDeviceIntInfoIndex].IrqUnique == IRQ_UNIQUE_NO) {
      //
      // IRQ can be shared, move to next device
      //
      continue;
    }
    //
    // Device which needs unique IRQ was found, now search for another device which uses the same IRQ
    //
    for (DevIntConfigIndex2 = DevIntConfigIndex + 1; DevIntConfigIndex2 < DevIntConfigEntrySize; DevIntConfigIndex2++) {
      if (DevIntConfigEntry[DevIntConfigIndex].Irq == DevIntConfigEntry[DevIntConfigIndex2].Irq) {
        //
        // If found device with the same IRQ check its number,
        // if IRQ > 23 it must be unique - report an error,
        // If IRQ <= 23 it can be shared but only between devices with different PortID
        //
        if (DevIntConfigEntry[DevIntConfigIndex].Irq > 23 ) {
          IrqError = TRUE;
        } else {
          //
          // Check if device which has the same IRQ (which is <=23) can share interrupt
          //
          PchDeviceIntInfoIndex2 = (DevIntConfigEntry[DevIntConfigIndex2].Device - PCH_DEV_NUM_MIN) * 8 + DevIntConfigEntry[DevIntConfigIndex2].Function;
          if (mPchDeviceInterruptInfo[PchDeviceIntInfoIndex].IrqUnique == mPchDeviceInterruptInfo[PchDeviceIntInfoIndex2].IrqUnique) {
            //
            // If both of these devices are the same type their IRQs must be unique
            //
            IrqError = TRUE;
            break;
          }
        }

        //
        // If found an IRQ sharing between devices which require unique interrupt then assert.
        //
        if (IrqError == TRUE) {
          DEBUG ((DEBUG_ERROR, "InterruptConfig ERROR: Device D%dF%d and D%dF%d share interrupt (IRQ%d)!\n",
                  DevIntConfigEntry[DevIntConfigIndex].Device,
                  DevIntConfigEntry[DevIntConfigIndex].Function,
                  DevIntConfigEntry[DevIntConfigIndex2].Device,
                  DevIntConfigEntry[DevIntConfigIndex2].Function,
                  DevIntConfigEntry[DevIntConfigIndex].Irq));
          ASSERT (FALSE);
          return EFI_INVALID_PARAMETER;
        }
      }
    }
  }

  //
  // 8. Check if any GPIO pad which is routed to IOxAPIC does not share it with
  //    other pads or any PCH device.
  //

  GroupMin = GpioGetLowestGroup ();
  GroupMax = GpioGetHighestGroup ();

  for (Group = GroupMin; Group <= GroupMax; Group++) {
    for (PadNumber = 0; PadNumber < GpioGetPadPerGroup (Group); PadNumber++) {

      GpioPad = GpioGetGpioPadFromGroupAndPadNumber (Group, PadNumber);

      GpioGetPadOwnership (GpioPad, &PadOwnVal);
      if (PadOwnVal != GpioPadOwnHost) {
        DEBUG ((DEBUG_ERROR, "GpioPad (Group=%x, Pad=%x) not owned by HOST, skip it.\n", GpioGetGroupIndexFromGroup (Group), PadNumber));
        continue;
      }

      GpioGetPadConfig (GpioPad, &GpioData);

      if ((GpioData.InterruptConfig & GpioIntApic) != GpioIntApic) {
        //
        // This pad is not routed to IOxAPIC, move to next one
        //
        continue;
      }

      GpioGetPadIoApicIrqNumber (GpioPad, &GpioIrqNumber);
      if (((IrqUsage[GpioIrqNumber >> 5] >> (GpioIrqNumber % 32)) & BIT0) == 0x0) {
        //
        // If IRQ is not yet used, update IrqUsage[] table
        //
        IrqUsage[GpioIrqNumber >> 5]|= 0x1 << (GpioIrqNumber  % 32);
      } else {
        //
        // If IRQ is reported to be used then assert, as those interrupts
        // cannot be shareable
        //
        DEBUG ((DEBUG_ERROR, "InterruptConfig ERROR: For GPP_%c_%d IRQ%d is already in use!\n",
                Group - GroupMin + 65,
                PadNumber,
                GpioIrqNumber));
        return EFI_INVALID_PARAMETER;
      }
    }
  }

  //
  // Dump IRQ usage
  //
  DEBUG ((DEBUG_INFO, "------------------ IRQ Usage ------------------\n"));
  DEBUG ((DEBUG_INFO, "  IRQxxx  USED\n"));
  for (Index = 0; Index < 127; Index++) {
    DEBUG ((DEBUG_INFO, "  IRQ%03d  %x\n",Index,((IrqUsage[Index >> 5] >> (Index % 32)) & BIT0)));
  }
  DEBUG_CODE_END ();
  return EFI_SUCCESS;
}
#endif // MDEPKG_NDEBUG

/**
  Configures interrupts polarity

  @param[in] PchInterruptConfig    PCH interrupt Configuration

  @retval Status
**/
EFI_STATUS
ConfigureInterruptsPolarity (
  IN      PCH_INTERRUPT_CONFIG    *InterruptConfig
  )
{
  UINTN   DevIntConfigIndex;
  UINT32  IpcXReg[4];
  UINTN   IpcXIndex;

  ZeroMem (IpcXReg, sizeof (IpcXReg));

  //
  // PIRQA-H (IRQ16-23) should always be set for ActiveLow
  //
  IpcXReg[0] = 0x00FF0000;

  //
  // Set GPIO controller interrupt to ActiveLow
  //
  ASSERT (InterruptConfig->GpioIrqRoute < 128);
  IpcXIndex = InterruptConfig->GpioIrqRoute / 32;
  if (IpcXIndex < 4) {
    IpcXReg[IpcXIndex] |= 0x1 << (InterruptConfig->GpioIrqRoute % 32);
  }

  //
  // Get all IRQ numbers used by devices and switch their interrupt
  // for ActiveLow
  //
  for (DevIntConfigIndex = 0; DevIntConfigIndex < InterruptConfig->NumOfDevIntConfig; DevIntConfigIndex++) {
    IpcXReg[InterruptConfig->DevIntConfig[DevIntConfigIndex].Irq >> 5] |= 0x1 << (InterruptConfig->DevIntConfig[DevIntConfigIndex].Irq % 32);
  }

  for (IpcXIndex = 0; IpcXIndex < 4; IpcXIndex++) {
    //
    // Program ITSS.IPC0-3 register
    //
    PchPcrWrite32 (PID_ITSS, R_PCH_PCR_ITSS_IPC0 + (UINT16) IpcXIndex * 4, IpcXReg[IpcXIndex]);
  }

  return EFI_SUCCESS;
}

/**
  Configures PCH devices interrupts

  @param[in] SiPolicy    Policy

  @retval Status
**/
EFI_STATUS
PchConfigureInterrupts (
  IN      SI_POLICY_PPI    *SiPolicy
  )
{
  UINT8                 Index;
  EFI_STATUS            Status;
  PCH_INTERRUPT_CONFIG  *InterruptConfig;

  Status = GetConfigBlock ((VOID *) SiPolicy, &gInterruptConfigGuid, (VOID *) &InterruptConfig);
  ASSERT_EFI_ERROR (Status);

#ifndef MDEPKG_NDEBUG
  //
  // Check interrupt settings
  //
  CheckInterruptSettings (
    InterruptConfig->DevIntConfig,
    InterruptConfig->NumOfDevIntConfig
    );
#endif //MDEPKG_NDEBUG
  //
  // Set PxRC legacy routing registers for 8259
  //
  UpdatePxRcRegs (
    InterruptConfig->PxRcConfig,
    PCH_MAX_PXRC_CONFIG
    );
  //
  // Set Pirx Interrupt routing register
  //
  if (InterruptConfig->NumOfDevIntConfig < PCH_MAX_DEVICE_INTERRUPT_CONFIG) {
    UpdatePirxRegs (
      InterruptConfig->DevIntConfig,
      InterruptConfig->NumOfDevIntConfig
      );
  }
  //
  // Configure interrupts polarity in ITSS
  //
  ConfigureInterruptsPolarity (InterruptConfig);

  //
  // Loop through whole interrupt table and program devices registers
  //
  for (Index = 0; Index < InterruptConfig->NumOfDevIntConfig; Index++) {
    //
    // Do not configure devices with Dxx < 16
    //
    if (InterruptConfig->DevIntConfig[Index].Device < 16) {
      continue;
    }

    switch (InterruptConfig->DevIntConfig[Index].Device) {
      case ME_DEVICE_NUMBER:
        //
        // CSME KT
        //
        if (InterruptConfig->DevIntConfig[Index].Function == SOL_FUNCTION_NUMBER) {
          CsmeKtIntSet (
            InterruptConfig->DevIntConfig[Index].IntX
            );
        } else {
          StandardIntSet (
            InterruptConfig->DevIntConfig[Index].Device,
            InterruptConfig->DevIntConfig[Index].Function,
            InterruptConfig->DevIntConfig[Index].IntX
            );
        }
        break;

      case PCI_DEVICE_NUMBER_PCH_HDA:
        if (InterruptConfig->DevIntConfig[Index].Function == PCI_FUNCTION_NUMBER_PCH_HDA) {
          //
          // HDAudio
          //
          HdAudioIntSet (
            InterruptConfig->DevIntConfig[Index].IntX,
            InterruptConfig->DevIntConfig[Index].Irq
            );
        } else {
          StandardIntSet (
            InterruptConfig->DevIntConfig[Index].Device,
            InterruptConfig->DevIntConfig[Index].Function,
            InterruptConfig->DevIntConfig[Index].IntX
            );
        }
        break;

      case PCI_DEVICE_NUMBER_PCH_PCIE_DEVICE_1:
      case PCI_DEVICE_NUMBER_PCH_PCIE_DEVICE_2:
      case PCI_DEVICE_NUMBER_PCH_PCIE_DEVICE_3:
        //
        // PCI Express Port
        //
        PciExpressIntSet (
          InterruptConfig->DevIntConfig[Index].Device,
          InterruptConfig->DevIntConfig[Index].Function,
          InterruptConfig->DevIntConfig[Index].IntX
          );
        break;

      case PCI_DEVICE_NUMBER_PCH_SERIAL_IO_UART0:
        if (InterruptConfig->DevIntConfig[Index].Function >= 4) {
          //
          // SCS Devices
          //
          ScsDevicesIntSet (
            InterruptConfig->DevIntConfig[Index].Device,
            InterruptConfig->DevIntConfig[Index].Function,
            InterruptConfig->DevIntConfig[Index].IntX,
            InterruptConfig->DevIntConfig[Index].Irq
            );
        } else {
          //
          // SerialIo Devices (UART0-1, SPI0-1)
          //
          SerialIoIntSet (
            InterruptConfig->DevIntConfig[Index].Device,
            InterruptConfig->DevIntConfig[Index].Function,
            InterruptConfig->DevIntConfig[Index].IntX,
            InterruptConfig->DevIntConfig[Index].Irq
            );
        }
        break;

      case PCI_DEVICE_NUMBER_PCH_SERIAL_IO_I2C4:
      case PCI_DEVICE_NUMBER_PCH_SERIAL_IO_I2C0:
        //
        // SerialIo Devices (I2C0-5, UART2)
        //
        SerialIoIntSet (
          InterruptConfig->DevIntConfig[Index].Device,
          InterruptConfig->DevIntConfig[Index].Function,
          InterruptConfig->DevIntConfig[Index].IntX,
          InterruptConfig->DevIntConfig[Index].Irq
          );
        break;

      case PCI_DEVICE_NUMBER_PCH_XDCI:
        if (InterruptConfig->DevIntConfig[Index].Function == PCI_FUNCTION_NUMBER_PCH_XDCI) {
          //
          // USB Device Controller (OTG)
          //
          OtgIntSet (
            InterruptConfig->DevIntConfig[Index].Device,
            InterruptConfig->DevIntConfig[Index].Function,
            InterruptConfig->DevIntConfig[Index].IntX,
            InterruptConfig->DevIntConfig[Index].Irq
            );
        } else {
          StandardIntSet (
            InterruptConfig->DevIntConfig[Index].Device,
            InterruptConfig->DevIntConfig[Index].Function,
            InterruptConfig->DevIntConfig[Index].IntX
            );
        }
        break;
      case PCI_DEVICE_NUMBER_PCH_ISH:
        //
        // Intel Sensor Hub
        //
        IshDevicesIntSet (
          InterruptConfig->DevIntConfig[Index].IntX,
          InterruptConfig->DevIntConfig[Index].Irq
          );
        break;

      default:
        //
        //Standard PCI Devices which have Interrupt Pin register under PciCfgSpace + 3Dh
        //
        StandardIntSet (
          InterruptConfig->DevIntConfig[Index].Device,
          InterruptConfig->DevIntConfig[Index].Function,
          InterruptConfig->DevIntConfig[Index].IntX
          );
        break;
    }
  }
  //
  // Configure GPIO interrupt to IRQ 14 or 15
  //
  GpioSetIrq (InterruptConfig->GpioIrqRoute);

  //
  // Select IRQ for TCO
  //
  PchTcoIrqSet (
    InterruptConfig->TcoIrqSelect,
    InterruptConfig->TcoIrqEnable
    );
  //
  // Select IRQ for SCI
  //
  PchSciIrqSet (InterruptConfig->SciIrqSelect);

  return EFI_SUCCESS;
}
