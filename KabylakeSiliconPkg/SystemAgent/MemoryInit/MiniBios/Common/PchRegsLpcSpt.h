/** @file
  Register names for PCH LPC device

  Conventions:

  - Prefixes:
    Definitions beginning with "R_" are registers
    Definitions beginning with "B_" are bits within registers
    Definitions beginning with "V_" are meaningful values of bits within the registers
    Definitions beginning with "S_" are register sizes
    Definitions beginning with "N_" are the bit position
  - In general, PCH registers are denoted by "_PCH_" in register names
  - Registers / bits that are different between PCH generations are denoted by
    "_PCH_[generation_name]_" in register/bit names. e.g., "_PCH_"
  - Registers / bits that are different between SKUs are denoted by "_<SKU_name>"
    at the end of the register/bit names
  - Registers / bits of new devices introduced in a PCH generation will be just named
    as "_PCH_" without [generation_name] inserted.

 @copyright
  INTEL CONFIDENTIAL
  Copyright 1999 - 2016 Intel Corporation.

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
#ifndef _PCH_REGS_LPC_H_
#define _PCH_REGS_LPC_H_

#ifdef MRC_MINIBIOS_BUILD
typedef U64  UINT64;
typedef S64  INT64;
typedef U32  UINT32;
typedef U16  UINT16;
typedef U8   UINT8;
typedef S32  INT32;
typedef S16  INT16;
typedef S8   INT8;
typedef char CHAR8;
typedef void VOID;
#endif // MRC_MINIBIOS_BUILD

//
// PCI to LPC Bridge Registers (D31:F0)
//
#define PCI_DEVICE_NUMBER_PCH_LPC       31
#define PCI_FUNCTION_NUMBER_PCH_LPC     0

typedef enum {
  PchHB0 = 0x01,
  PchHC0,
  PchLpB0 = 0x23,
  PchLpB1,
  PchSteppingMax
} PCH_STEPPING;

#define PCH_H_MIN_SUPPORTED_STEPPING              PchHB0
#define PCH_LP_MIN_SUPPORTED_STEPPING             PchLpB0

#define R_PCH_LPC_VENDOR_ID                       0x00
#define V_PCH_LPC_VENDOR_ID                       V_PCH_INTEL_VENDOR_ID
#define R_PCH_LPC_DEVICE_ID                       0x02

//
// SKL PCH-H Desktop LPC Device IDs
//
#define V_PCH_H_LPC_DEVICE_ID_DT_SUPER_SKU      0xA141          ///< TBD SKU
#define V_PCH_H_LPC_DEVICE_ID_DT_0              0xA142          ///< 
#define V_PCH_H_LPC_DEVICE_ID_DT_1              0xA143          ///<
#define V_PCH_H_LPC_DEVICE_ID_DT_2              0xA144          ///<
#define V_PCH_H_LPC_DEVICE_ID_DT_3              0xA145          ///<
#define V_PCH_H_LPC_DEVICE_ID_DT_4              0xA146          ///<
#define V_PCH_H_LPC_DEVICE_ID_DT_5              0xA147          ///<

//
// SKL PCH-H Mobile LPC Device IDs
//
#define V_PCH_H_LPC_DEVICE_ID_MB_SUPER_SKU      0x8C41          ///< TBD SKU
#define V_PCH_H_LPC_DEVICE_ID_MB_0              0x8C49          ///< 
#define V_PCH_H_LPC_DEVICE_ID_MB_1              0x8C4B          ///< 
#define V_PCH_H_LPC_DEVICE_ID_MB_2              0x8C4F          ///< 

//
// SKL PCH-LP LPC Device IDs
//
#define V_PCH_LP_LPC_DEVICE_ID_MB_SUPER_SKU     0x9D41          ///< SKL PCH LP Mobile Super SKU
#define V_PCH_LP_LPC_DEVICE_ID_MB_0             0x9D42          ///< SKL PCH LP Mobile TBD SKU
#define V_PCH_LP_LPC_DEVICE_ID_MB_1             0x9D43          ///< SKL PCH LP Mobile Premium SKU
#define V_PCH_LP_LPC_DEVICE_ID_MB_2             0x9D44          ///< SKL PCH LP Mobile TBD SKU
#define V_PCH_LP_LPC_DEVICE_ID_MB_3             0x9D45          ///< SKL PCH LP Mobile Mainstream SKU
#define V_PCH_LP_LPC_DEVICE_ID_MB_4             0x9D46          ///< SKL PCH LP Mobile TBD SKU
#define V_PCH_LP_LPC_DEVICE_ID_MB_5             0x9D47          ///< SKL PCH LP Mobile Value SKU


#define R_PCH_LPC_COMMAND                         0x04
#define B_PCH_LPC_COMMAND_FBE                     0x0200
#define B_PCH_LPC_COMMAND_SERR_EN                 0x0100
#define B_PCH_LPC_COMMAND_WCC                     0x0080
#define B_PCH_LPC_COMMAND_PER                     0x0040
#define B_PCH_LPC_COMMAND_VPS                     0x0020
#define B_PCH_LPC_COMMAND_PMWE                    0x0010
#define B_PCH_LPC_COMMAND_SCE                     0x0008
#define B_PCH_LPC_COMMAND_BME                     0x0004
#define B_PCH_LPC_COMMAND_MSE                     0x0002
#define B_PCH_LPC_COMMAND_IOSE                    0x0001
#define R_PCH_LPC_DEV_STS                         0x06
#define B_PCH_LPC_DEV_STS_DPE                     0x8000
#define B_PCH_LPC_DEV_STS_SSE                     0x4000
#define B_PCH_LPC_DEV_STS_RMA                     0x2000
#define B_PCH_LPC_DEV_STS_RTA                     0x1000
#define B_PCH_LPC_DEV_STS_STA                     0x0800
#define B_PCH_LPC_DEV_STS_DEVT_STS                0x0600
#define B_PCH_LPC_DEV_STS_MDPED                   0x0100
#define B_PCH_LPC_DEV_STS_FB2B                    0x0080
#define B_PCH_LPC_DEV_STS_UDF                     0x0040
#define B_PCH_LPC_DEV_STS_66MHZ_CAP               0x0020
#define R_PCH_LPC_RID                             0x08
#define V_PCH_LPC_RID_0                           0x00
#define R_PCH_LPC_PI                              0x09
#define R_PCH_LPC_SCC                             0x0A
#define R_PCH_LPC_BCC                             0x0B
#define R_PCH_LPC_PLT                             0x0D
#define R_PCH_LPC_HEADTYP                         0x0E
#define B_PCH_LPC_HEADTYP_MFD                     BIT7
#define B_PCH_LPC_HEADTYP_HT                      0x7F
#define R_PCH_LPC_SS                              0x2C
#define B_PCH_LPC_SS_SSID                         0xFFFF0000
#define B_PCH_LPC_SS_SSVID                        0x0000FFFF
#define R_PCH_LPC_GPIO_BASE                       0x48
#define B_PCH_LPC_GPIO_BASE_BAR                   0xFFFC
#define R_PCH_LPC_GPIO_CNT                        0x4C
#define B_PCH_LPC_GPIO_CNT_GPIO_EN                0x10
#define B_PCH_LPC_GPIO_LOCKDOWN_EN                0x01
#define R_PCH_LPC_SERIRQ_CNT                      0x64
#define B_PCH_LPC_SERIRQ_CNT_SIRQEN               0x80
#define B_PCH_LPC_SERIRQ_CNT_SIRQMD               0x40
#define B_PCH_LPC_SERIRQ_CNT_SIRQSZ               0x3C
#define N_PCH_LPC_SERIRQ_CNT_SIRQSZ               2
#define B_PCH_LPC_SERIRQ_CNT_SFPW                 0x03
#define N_PCH_LPC_SERIRQ_CNT_SFPW                 0
#define V_PCH_LPC_SERIRQ_CNT_SFPW_4CLK            0x00
#define V_PCH_LPC_SERIRQ_CNT_SFPW_6CLK            0x01
#define V_PCH_LPC_SERIRQ_CNT_SFPW_8CLK            0x02
#define R_PCH_LPC_IO_DEC                          0x80
#define B_PCH_LPC_FDD_DEC                         0x1000
#define B_PCH_LPC_LPT_DEC                         0x0300
#define B_PCH_LPC_COMB_DEC                        0x0070
#define V_PCH_LPC_COMB_3F8                        0x00
#define V_PCH_LPC_COMB_2F8                        0x10
#define V_PCH_LPC_COMB_220                        0x20
#define V_PCH_LPC_COMB_228                        0x30
#define V_PCH_LPC_COMB_238                        0x40
#define V_PCH_LPC_COMB_2E8                        0x50
#define V_PCH_LPC_COMB_338                        0x60
#define V_PCH_LPC_COMB_3E8                        0x70
#define B_PCH_LPC_COMA_DEC                        0x0007
#define V_PCH_LPC_COMA_3F8                        0x00
#define V_PCH_LPC_COMA_2F8                        0x01
#define V_PCH_LPC_COMA_220                        0x02
#define V_PCH_LPC_COMA_228                        0x03
#define V_PCH_LPC_COMA_238                        0x04
#define V_PCH_LPC_COMA_2E8                        0x05
#define V_PCH_LPC_COMA_338                        0x06
#define V_PCH_LPC_COMA_3E8                        0x07
#define R_PCH_LPC_ENABLES                         0x82
#define B_PCH_LPC_ENABLES_CNF2_EN                 0x2000
#define B_PCH_LPC_ENABLES_CNF1_EN                 0x1000
#define B_PCH_LPC_ENABLES_MC_EN                   0x0800
#define B_PCH_LPC_ENABLES_KBC_EN                  0x0400
#define B_PCH_LPC_ENABLES_GAMEH_EN                0x0200
#define B_PCH_LPC_ENABLES_GAMEL_EN                0x0100
#define B_PCH_LPC_ENABLES_FDD_EN                  0x0008
#define B_PCH_LPC_ENABLES_LPT_EN                  0x0004
#define B_PCH_LPC_ENABLES_COMB_EN                 0x0002
#define B_PCH_LPC_ENABLES_COMA_EN                 0x0001
#define R_PCH_LPC_GEN1_DEC                        0x84
#define R_PCH_LPC_GEN2_DEC                        0x88
#define R_PCH_LPC_GEN3_DEC                        0x8C
#define R_PCH_LPC_GEN4_DEC                        0x90
#define B_PCH_LPC_GENX_DEC_IODRA                  0x00FC0000
#define B_PCH_LPC_GENX_DEC_IOBAR                  0x0000FFFC
#define B_PCH_LPC_GENX_DEC_EN                     0x00000001
#define R_PCH_LPC_ULKMC                           0x94
#define B_PCH_LPC_ULKMC_SMIBYENDPS                BIT15
#define B_PCH_LPC_ULKMC_TRAPBY64W                 BIT11
#define B_PCH_LPC_ULKMC_TRAPBY64R                 BIT10
#define B_PCH_LPC_ULKMC_TRAPBY60W                 BIT9
#define B_PCH_LPC_ULKMC_TRAPBY60R                 BIT8
#define B_PCH_LPC_ULKMC_SMIATENDPS                BIT7
#define B_PCH_LPC_ULKMC_PSTATE                    BIT6
#define B_PCH_LPC_ULKMC_A20PASSEN                 BIT5
#define B_PCH_LPC_ULKMC_USBSMIEN                  BIT4
#define B_PCH_LPC_ULKMC_64WEN                     BIT3
#define B_PCH_LPC_ULKMC_64REN                     BIT2
#define B_PCH_LPC_ULKMC_60WEN                     BIT1
#define B_PCH_LPC_ULKMC_60REN                     BIT0
#define R_PCH_LPC_LGMR                            0x98
#define B_PCH_LPC_LGMR_MA                         0xFFFF0000
#define B_PCH_LPC_LGMR_LMRD_EN                    BIT0

#define R_PCH_LPC_FWH_BIOS_SEL                    0xD0
#define B_PCH_LPC_FWH_BIOS_SEL_F8                 0xF0000000
#define B_PCH_LPC_FWH_BIOS_SEL_F0                 0x0F000000
#define B_PCH_LPC_FWH_BIOS_SEL_E8                 0x00F00000
#define B_PCH_LPC_FWH_BIOS_SEL_E0                 0x000F0000
#define B_PCH_LPC_FWH_BIOS_SEL_D8                 0x0000F000
#define B_PCH_LPC_FWH_BIOS_SEL_D0                 0x00000F00
#define B_PCH_LPC_FWH_BIOS_SEL_C8                 0x000000F0
#define B_PCH_LPC_FWH_BIOS_SEL_C0                 0x0000000F
#define R_PCH_LPC_FWH_BIOS_SEL2                   0xD4
#define B_PCH_LPC_FWH_BIOS_SEL2_70                0xF000
#define B_PCH_LPC_FWH_BIOS_SEL2_60                0x0F00
#define B_PCH_LPC_FWH_BIOS_SEL2_50                0x00F0
#define B_PCH_LPC_FWH_BIOS_SEL2_40                0x000F
#define R_PCH_LPC_BDE                             0xD8                          ///< BIOS decode enable
#define B_PCH_LPC_BDE_F8                          0x8000
#define B_PCH_LPC_BDE_F0                          0x4000
#define B_PCH_LPC_BDE_E8                          0x2000
#define B_PCH_LPC_BDE_E0                          0x1000
#define B_PCH_LPC_BDE_D8                          0x0800
#define B_PCH_LPC_BDE_D0                          0x0400
#define B_PCH_LPC_BDE_C8                          0x0200
#define B_PCH_LPC_BDE_C0                          0x0100
#define B_PCH_LPC_BDE_LEG_F                       0x0080
#define B_PCH_LPC_BDE_LEG_E                       0x0040
#define B_PCH_LPC_BDE_70                          0x0008
#define B_PCH_LPC_BDE_60                          0x0004
#define B_PCH_LPC_BDE_50                          0x0002
#define B_PCH_LPC_BDE_40                          0x0001
#define R_PCH_LPC_PCC                             0xE0
#define B_PCH_LPC_PCC_CLKRUN_EN                   0x0001
#define B_PCH_LPC_FVEC0_USB_PORT_CAP              0x00000C00
#define V_PCH_LPC_FVEC0_USB_14_PORT               0x00000000
#define V_PCH_LPC_FVEC0_USB_12_PORT               0x00000400
#define V_PCH_LPC_FVEC0_USB_10_PORT               0x00000800
#define B_PCH_LPC_FVEC0_SATA_RAID_CAP             0x00000080
#define B_PCH_LPC_FVEC0_SATA_PORT23_CAP           0x00000040
#define B_PCH_LPC_FVEC0_SATA_PORT1_6GB_CAP        0x00000008
#define B_PCH_LPC_FVEC0_SATA_PORT0_6GB_CAP        0x00000004
#define B_PCH_LPC_FVEC0_PCI_CAP                   0x00000002
#define R_PCH_LPC_FVEC1                           0x01
#define B_PCH_LPC_FVEC1_USB_R_CAP                 0x00400000
#define R_PCH_LPC_FVEC2                           0x02
#define V_PCH_LPC_FVEC2_PCIE_PORT78_CAP           0x00200000
#define V_PCH_LPC_FVEC2_PCH_IG_SUPPORT_CAP        0x00020000      ///< PCH Integrated Graphics Support Capability
#define R_PCH_LPC_FVEC3                           0x03
#define B_PCH_LPC_FVEC3_DCMI_CAP                  0x00002000      ///< Data Center Manageability Interface (DCMI) Capability
#define B_PCH_LPC_FVEC3_NM_CAP                    0x00001000      ///< Node Manager Capability

#define R_PCH_LPC_GPI_ROUT                        0xB8
#define B_PCH_LPC_GPI_ROUT_0                      (BIT1 | BIT0)
#define B_PCH_LPC_GPI_ROUT_1                      (BIT3 | BIT2)
#define B_PCH_LPC_GPI_ROUT_2                      (BIT5 | BIT4)
#define B_PCH_LPC_GPI_ROUT_3                      (BIT7 | BIT6)
#define B_PCH_LPC_GPI_ROUT_4                      (BIT9 | BIT8)
#define B_PCH_LPC_GPI_ROUT_5                      (BIT11 | BIT10)
#define B_PCH_LPC_GPI_ROUT_6                      (BIT13 | BIT12)
#define B_PCH_LPC_GPI_ROUT_7                      (BIT15 | BIT14)
#define B_PCH_LPC_GPI_ROUT_8                      (BIT17 | BIT16)
#define B_PCH_LPC_GPI_ROUT_9                      (BIT19 | BIT18)
#define B_PCH_LPC_GPI_ROUT_10                     (BIT21 | BIT20)
#define B_PCH_LPC_GPI_ROUT_11                     (BIT23 | BIT22)
#define B_PCH_LPC_GPI_ROUT_12                     (BIT25 | BIT24)
#define B_PCH_LPC_GPI_ROUT_13                     (BIT27 | BIT26)
#define B_PCH_LPC_GPI_ROUT_14                     (BIT29 | BIT28)
#define B_PCH_LPC_GPI_ROUT_15                     (BIT31 | BIT30)

#define R_PCH_LPC_GPI_ROUT2                       0xBC
#define B_PCH_LPC_GPI_ROUT2_17                    (BIT1 | BIT0)
#define B_PCH_LPC_GPI_ROUT2_19                    (BIT3 | BIT2)
#define B_PCH_LPC_GPI_ROUT2_21                    (BIT5 | BIT4)
#define B_PCH_LPC_GPI_ROUT2_22                    (BIT7 | BIT6)
#define B_PCH_LPC_GPI_ROUT2_43                    (BIT9 | BIT8)
#define B_PCH_LPC_GPI_ROUT2_56                    (BIT11 | BIT10)
#define B_PCH_LPC_GPI_ROUT2_57                    (BIT13 | BIT12)
#define B_PCH_LPC_GPI_ROUT2_60                    (BIT15 | BIT14)

#define R_PCH_LP_LPC_GPI_ROUT0                    0x30
#define R_PCH_LP_LPC_GPI_ROUT1                    0x34
#define R_PCH_LP_LPC_GPI_ROUT2                    0x38

#define R_PCH_LPC_MDAP                            0xC0
#define B_PCH_LPC_MDAP_POLICY_EN                  BIT31
#define B_PCH_LPC_MDAP_PDMA_EN                    BIT30
#define B_PCH_LPC_MDAP_VALUE                      0x0001FFFF

//
// APM Registers
//
#define R_PCH_APM_CNT                             0xB2
#define R_PCH_APM_STS                             0xB3


#define R_PCH_LPC_BIOS_CNTL                       0xDC
#define S_PCH_LPC_BIOS_CNTL                       1
#define B_PCH_LPC_BILD                            BIT7
#define B_PCH_LPC_BBS                             BIT6            ///< Boot BIOS strap
#define V_PCH_LPC_BBS_SPI                         0               ///< Boot BIOS strapped to SPI
#define V_PCH_LPC_BBS_LPC                         BIT6            ///< Boot BIOS strapped to LPC
#define B_PCH_LPC_BIOS_CNTL_EISS                  BIT5            ///< Enable InSMM.STS
#define B_PCH_LPC_BIOS_CNTL_TSS                   BIT4
#define V_PCH_LPC_BIOS_CNTL_SRC                   (BIT3 | BIT2)
#define V_PCH_SRC_PREF_EN_CACHE_EN                0x08
#define V_PCH_SRC_PREF_DIS_CACHE_DIS              0x04
#define V_PCH_SRC_PREF_DIS_CACHE_EN               0x00
#define B_PCH_LPC_BIOS_CNTL_BLE                   BIT1
#define B_PCH_LPC_BIOS_CNTL_BIOSWE                BIT0
#define N_PCH_LPC_BIOS_CNTL_BLE                   1
#define N_PCH_SPI_BIOS_CNTL_BIOSWE                0

//
// GPIO Init register offsets from GPIOBASE
//
#define R_PCH_GPIO_USE_SEL                        0x00
#define R_PCH_GPIO_IO_SEL                         0x04
#define R_PCH_GPIO_LVL                            0x0C
#define R_PCH_GPIO_IOAPIC_SEL                     0x10
#define V_PCH_GPIO_IOAPIC_SEL                     0xFFFF
#define R_PCH_GPIO_BLINK                          0x18
#define R_PCH_GPIO_SER_BLINK                      0x1C
#define R_PCH_GPIO_SB_CMDSTS                      0x20
#define B_PCH_GPIO_SB_CMDSTS_DLS_MASK             0x00C00000      ///< Data length select
#define B_PCH_GPIO_SB_CMDSTS_DRS_MASK             0x003F0000      ///< Data rate select
#define B_PCH_GPIO_SB_CMDSTS_BUSY                 BIT8
#define B_PCH_GPIO_SB_CMDSTS_GO                   BIT0
#define R_PCH_GPIO_SB_DATA                        0x24
#define R_PCH_GPIO_NMI_EN                         0x28
#define B_PCH_GPIO_NMI_EN                         0xFFFF
#define R_PCH_GPIO_NMI_STS                        0x2A
#define B_PCH_GPIO_NMI_STS                        0xFFFF
#define R_PCH_GPIO_GPI_INV                        0x2C
#define R_PCH_GPIO_USE_SEL2                       0x30
#define R_PCH_GPIO_IO_SEL2                        0x34
#define R_PCH_GPIO_LVL2                           0x38
#define R_PCH_GPIO_USE_SEL3                       0x40
#define R_PCH_GPIO_IO_SEL3                        0x44
#define R_PCH_GPIO_LVL3                           0x48

#define R_PCH_GP_RST_SEL                          0x60
#define S_PCH_GP_RST_SEL                          4
#define R_PCH_GP_RST_SEL2                         0x64
#define S_PCH_GP_RST_SEL2                         4
#define R_PCH_GP_RST_SEL3                         0x68
#define S_PCH_GP_RST_SEL3                         4

/**
  The data structure to describe GPIO definition
**/
typedef struct {
  UINT16 GpioOwn          : 1;
  UINT16 GpiRout          : 1;
  UINT16 GpiIe            : 1;
  UINT16 GpioUseSel       : 1;
  UINT16 GpioIoSel        : 1;
  UINT16 GpiInv           : 1;
  UINT16 GpiLxEb          : 1;
  UINT16 GpoLvl           : 1;
  UINT16 GpiWp            : 2;
  UINT16 GpinDis          : 1;
  UINT16 Reserved         : 5;
} PCH_GPIO_DEFINITION;

#define R_PCH_GPIO_OWN0                           0x00
#define B_PCH_GPIO_OWN0_GPIO_USE_SEL              BIT0
#define B_PCH_GPIO_OWN0_GPIO_IO_SEL               BIT2
#define B_PCH_GPIO_OWN0_GPI_INV                   BIT3
#define B_PCH_GPIO_OWN0_GPI_LxEB                  BIT4
#define B_PCH_GPIO_OWN0_GPI_LVL                   BIT30
#define B_PCH_GPIO_OWN0_GPO_LVL                   BIT31

#define V_PCH_GPIO_OWN_GPIO                       0x01
#define V_PCH_GPIO_OWN_ACPI                       0x00

#define V_PCH_GPIO_USE_SEL_NATIVE                 0x00
#define V_PCH_GPIO_USE_SEL_GPIO                   0x01

#define V_PCH_GPIO_IO_SEL_OUT                     0x00
#define V_PCH_GPIO_IO_SEL_IN                      0x01

#define V_PCH_GPO_LVL_LOW                         0x00
#define V_PCH_GPO_LVL_HIGH                        0x01

#define V_PCH_GPI_LVL_NORMAL                      0x00
#define V_PCH_GPI_LVL_INVERTED                    0x01

#define V_PCH_GPI_LxEB_EDGE                       0x00
#define V_PCH_GPI_LxEB_LEVEL                      0x01

#define V_PCH_GPINDIS_ENABLE                      0x00
#define V_PCH_GPINDIS_DISABLE                     0x01

#define V_PCH_GPIWP_NONE                          0x00
#define V_PCH_GPIWP_DOWN                          0x01
#define V_PCH_GPIWP_UP                            0x02

#define R_PCH_GPIO_ROUT0                          0x30
#define V_PCH_GPIO_ROUT0_NMI_SMI                  0x01
#define V_PCH_GPIO_ROUT0_SCI                      0x00

#define R_PCH_GPIO_GC                             0x7C
#define R_PCH_GPI_IS0                             0x80
#define R_PCH_GPI_IS1                             0x84
#define R_PCH_GPI_IS2                             0x88
#define V_PCH_GPI_IS_CLEARALL                     0xFFFFFFFF

#define R_PCH_GPI_IE0                             0x90
#define V_PCH_GPI_IE_APIC_DISABLED                0x00
#define V_PCH_GPI_IE_APIC_ENABLED                 0x01

#define R_PCH_GPI_IE1                             0x94
#define R_PCH_GPI_IE2                             0x98
#define V_PCH_GPI_IE_CLEARALL                     0x00000000

#define R_PCH_GP_N_CONFIG0                        0x100
#define R_PCH_GP_X_CONFIG0(n)                     (R_PCH_GP_N_CONFIG0 + ((n) * 0x08))
#define R_PCH_GP_18_CONFIG0                       R_PCH_GP_X_CONFIG0(18)
#define R_PCH_GP_19_CONFIG0                       R_PCH_GP_X_CONFIG0(19)
#define R_PCH_GP_20_CONFIG0                       R_PCH_GP_X_CONFIG0(20)
#define R_PCH_GP_21_CONFIG0                       R_PCH_GP_X_CONFIG0(21)
#define R_PCH_GP_22_CONFIG0                       R_PCH_GP_X_CONFIG0(22)
#define R_PCH_GP_23_CONFIG0                       R_PCH_GP_X_CONFIG0(23)
#define R_PCH_GP_29_CONFIG0                       R_PCH_GP_X_CONFIG0(29)
#define R_PCH_GP_30_CONFIG0                       R_PCH_GP_X_CONFIG0(30)
#define R_PCH_GP_60_CONFIG0                       R_PCH_GP_X_CONFIG0(60)
#define R_PCH_GP_73_CONFIG0                       R_PCH_GP_X_CONFIG0(73)
#define R_PCH_GP_83_CONFIG0                       R_PCH_GP_X_CONFIG0(83) ///< SPI0
#define R_PCH_GP_87_CONFIG0                       R_PCH_GP_X_CONFIG0(87) ///< SPI1
#define R_PCH_GP_91_CONFIG0                       R_PCH_GP_X_CONFIG0(91) ///< UART0
#define V_PCH_GPIO_PIN_MAX                        95

//
// Processor interface registers
//
#define R_PCH_NMI_SC                              0x61
#define B_PCH_NMI_SC_SERR_NMI_STS                 BIT7
#define B_PCH_NMI_SC_IOCHK_NMI_STS                BIT6
#define B_PCH_NMI_SC_TMR2_OUT_STS                 BIT5
#define B_PCH_NMI_SC_REF_TOGGLE                   BIT4
#define B_PCH_NMI_SC_IOCHK_NMI_EN                 BIT3
#define B_PCH_NMI_SC_PCI_SERR_EN                  BIT2
#define B_PCH_NMI_SC_SPKR_DAT_EN                  BIT1
#define B_PCH_NMI_SC_TIM_CNT2_EN                  BIT0
#define R_PCH_NMI_EN                              0x70
#define B_PCH_NMI_EN_NMI_EN                       BIT7

//
// RTC register
//
#define R_PCH_RTC_INDEX                           0x70
#define R_PCH_RTC_TARGET                          0x71
#define R_PCH_RTC_EXT_INDEX                       0x72
#define R_PCH_RTC_EXT_TARGET                      0x73
#define R_PCH_RTC_REGA                            0x0A
#define B_PCH_RTC_REGA_UIP                        0x80
#define R_PCH_RTC_REGB                            0x0B
#define B_PCH_RTC_REGB_SET                        0x80
#define B_PCH_RTC_REGB_PIE                        0x40
#define B_PCH_RTC_REGB_AIE                        0x20
#define B_PCH_RTC_REGB_UIE                        0x10
#define B_PCH_RTC_REGB_DM                         0x04
#define B_PCH_RTC_REGB_HOURFORM                   0x02
#define R_PCH_RTC_REGC                            0x0C
#define R_PCH_RTC_REGD                            0x0D

//
// Reset Generator I/O Port
//
#define R_PCH_RST_CNT                             0xCF9
#define B_PCH_RST_CNT_FULL_RST                    BIT3
#define B_PCH_RST_CNT_RST_CPU                     BIT2
#define B_PCH_RST_CNT_SYS_RST                     BIT1
#define V_PCH_RST_CNT_FULLRESET                   0x0E
#define V_PCH_RST_CNT_HARDRESET                   0x06
#define V_PCH_RST_CNT_SOFTRESET                   0x04
#define V_PCH_RST_CNT_HARDSTARTSTATE              0x02
#define V_PCH_RST_CNT_SOFTSTARTSTATE              0x00
#endif
