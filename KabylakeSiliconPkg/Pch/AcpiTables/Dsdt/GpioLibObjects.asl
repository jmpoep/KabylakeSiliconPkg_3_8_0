/**@file

 @copyright
  INTEL CONFIDENTIAL
  Copyright 2016 Intel Corporation.

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

#define PCH_LP_GPIO_GET_FIELD(GpioGroupIndex,GpioFieldIndex) \
  ( \
    DeRefOf(Index( \
      DeRefOf(Index( \
        GPCL, \
        GpioGroupIndex)), \
      GpioFieldIndex)) \
  )

#define PCH_H_GPIO_GET_FIELD(GpioGroupIndex,GpioFieldIndex) \
  ( \
    DeRefOf(Index( \
      DeRefOf(Index( \
        GPCH, \
        GpioGroupIndex)), \
      GpioFieldIndex)) \
  )

//
// GPIO Library objects
//
Scope(\_SB)
{

  //
  // GPIO information data structure
  //
  // PCH-LP: GPCL
  // PCH-H:  GPCH
  //
  // GPCx[GroupIndex][Field]
  //   Field0 - Community
  //   Field1 - Pad number
  //   Field2 - PADCFG register offset
  //   Field3 - HOSTSW_OWN register offset
  //   Field4 - PAD_OWN register offset
  //   Field5 - GPI_GPE_STS register offset
  //
  //
  // GPIO information data structure for PCH-LP
  //
  Name(GPCL, Package(){
    Package(){ // GPP_A
      PCH_GPIO_COM0,
      V_PCH_GPIO_GPP_A_PAD_MAX,
      R_PCH_PCR_GPIO_GPP_A_PADCFG_OFFSET,
      R_PCH_PCR_GPIO_GPP_A_HOSTSW_OWN,
      R_PCH_LP_PCR_GPIO_GPP_A_PAD_OWN,
      R_PCH_PCR_GPIO_GPP_A_GPI_GPE_STS
    },
    Package(){ // GPP_B
      PCH_GPIO_COM0,
      V_PCH_GPIO_GPP_B_PAD_MAX,
      R_PCH_PCR_GPIO_GPP_B_PADCFG_OFFSET,
      R_PCH_PCR_GPIO_GPP_B_HOSTSW_OWN,
      R_PCH_LP_PCR_GPIO_GPP_B_PAD_OWN,
      R_PCH_PCR_GPIO_GPP_B_GPI_GPE_STS
    },
    Package(){ // GPP_C
      PCH_GPIO_COM1,
      V_PCH_GPIO_GPP_C_PAD_MAX,
      R_PCH_PCR_GPIO_GPP_C_PADCFG_OFFSET,
      R_PCH_PCR_GPIO_GPP_C_HOSTSW_OWN,
      R_PCH_LP_PCR_GPIO_GPP_C_PAD_OWN,
      R_PCH_PCR_GPIO_GPP_C_GPI_GPE_STS
    },
    Package(){ // GPP_D
      PCH_GPIO_COM1,
      V_PCH_GPIO_GPP_D_PAD_MAX,
      R_PCH_PCR_GPIO_GPP_D_PADCFG_OFFSET,
      R_PCH_PCR_GPIO_GPP_D_HOSTSW_OWN,
      R_PCH_LP_PCR_GPIO_GPP_D_PAD_OWN,
      R_PCH_PCR_GPIO_GPP_D_GPI_GPE_STS
    },
    Package(){ // GPP_E
      PCH_GPIO_COM1,
      V_PCH_LP_GPIO_GPP_E_PAD_MAX,
      R_PCH_PCR_GPIO_GPP_E_PADCFG_OFFSET,
      R_PCH_PCR_GPIO_GPP_E_HOSTSW_OWN,
      R_PCH_LP_PCR_GPIO_GPP_E_PAD_OWN,
      R_PCH_PCR_GPIO_GPP_E_GPI_GPE_STS
    },
    Package(){ // GPP_F
      PCH_GPIO_COM3,
      V_PCH_GPIO_GPP_F_PAD_MAX,
      R_PCH_LP_PCR_GPIO_GPP_F_PADCFG_OFFSET,
      R_PCH_LP_PCR_GPIO_GPP_F_HOSTSW_OWN,
      R_PCH_LP_PCR_GPIO_GPP_F_PAD_OWN,
      R_PCH_LP_PCR_GPIO_GPP_F_GPI_GPE_STS
    },
    Package(){ // GPP_G
      PCH_GPIO_COM3,
      V_PCH_LP_GPIO_GPP_G_PAD_MAX,
      R_PCH_LP_PCR_GPIO_GPP_G_PADCFG_OFFSET,
      R_PCH_LP_PCR_GPIO_GPP_G_HOSTSW_OWN,
      R_PCH_LP_PCR_GPIO_GPP_G_PAD_OWN,
      R_PCH_LP_PCR_GPIO_GPP_G_GPI_GPE_STS
    },
    Package(){ // GPD
      PCH_GPIO_COM2,
      V_PCH_GPIO_GPD_PAD_MAX,
      R_PCH_PCR_GPIO_GPD_PADCFG_OFFSET,
      R_PCH_PCR_GPIO_GPD_HOSTSW_OWN,
      R_PCH_LP_PCR_GPIO_GPD_PAD_OWN,
      R_PCH_PCR_GPIO_GPD_GPI_GPE_STS
    }
  })

  //
  // GPIO information data structure for PCH-H
  //
  Name(GPCH, Package(){
    Package(){ // GPP_A
      PCH_GPIO_COM0,
      V_PCH_GPIO_GPP_A_PAD_MAX,
      R_PCH_PCR_GPIO_GPP_A_PADCFG_OFFSET,
      R_PCH_PCR_GPIO_GPP_A_HOSTSW_OWN,
      R_PCH_H_PCR_GPIO_GPP_A_PAD_OWN,
      R_PCH_PCR_GPIO_GPP_A_GPI_GPE_STS
    },
    Package(){ // GPP_B
      PCH_GPIO_COM0,
      V_PCH_GPIO_GPP_B_PAD_MAX,
      R_PCH_PCR_GPIO_GPP_B_PADCFG_OFFSET,
      R_PCH_PCR_GPIO_GPP_B_HOSTSW_OWN,
      R_PCH_H_PCR_GPIO_GPP_B_PAD_OWN,
      R_PCH_PCR_GPIO_GPP_B_GPI_GPE_STS
    },
    Package(){ // GPP_C
      PCH_GPIO_COM1,
      V_PCH_GPIO_GPP_C_PAD_MAX,
      R_PCH_PCR_GPIO_GPP_C_PADCFG_OFFSET,
      R_PCH_PCR_GPIO_GPP_C_HOSTSW_OWN,
      R_PCH_H_PCR_GPIO_GPP_C_PAD_OWN,
      R_PCH_PCR_GPIO_GPP_C_GPI_GPE_STS
      },
    Package(){ // GPP_D
      PCH_GPIO_COM1,
      V_PCH_GPIO_GPP_D_PAD_MAX,
      R_PCH_PCR_GPIO_GPP_D_PADCFG_OFFSET,
      R_PCH_PCR_GPIO_GPP_D_HOSTSW_OWN,
      R_PCH_H_PCR_GPIO_GPP_D_PAD_OWN,
      R_PCH_PCR_GPIO_GPP_D_GPI_GPE_STS
    },
    Package(){ // GPP_E
      PCH_GPIO_COM1,
      V_PCH_H_GPIO_GPP_E_PAD_MAX,
      R_PCH_PCR_GPIO_GPP_E_PADCFG_OFFSET,
      R_PCH_PCR_GPIO_GPP_E_HOSTSW_OWN,
      R_PCH_H_PCR_GPIO_GPP_E_PAD_OWN,
      R_PCH_PCR_GPIO_GPP_E_GPI_GPE_STS
    },
    Package(){ // GPP_F
      PCH_GPIO_COM1,
      V_PCH_GPIO_GPP_F_PAD_MAX,
      R_PCH_H_PCR_GPIO_GPP_F_PADCFG_OFFSET,
      R_PCH_H_PCR_GPIO_GPP_F_HOSTSW_OWN,
      R_PCH_H_PCR_GPIO_GPP_F_PAD_OWN,
      R_PCH_H_PCR_GPIO_GPP_F_GPI_GPE_STS
    },
    Package(){ // GPP_G
      PCH_GPIO_COM1,
      V_PCH_H_GPIO_GPP_G_PAD_MAX,
      R_PCH_H_PCR_GPIO_GPP_G_PADCFG_OFFSET,
      R_PCH_H_PCR_GPIO_GPP_G_HOSTSW_OWN,
      R_PCH_H_PCR_GPIO_GPP_G_PAD_OWN,
      R_PCH_H_PCR_GPIO_GPP_G_GPI_GPE_STS
    },
    Package(){ // GPP_H
      PCH_GPIO_COM1,
      V_PCH_H_GPIO_GPP_H_PAD_MAX,
      R_PCH_H_PCR_GPIO_GPP_H_PADCFG_OFFSET,
      R_PCH_H_PCR_GPIO_GPP_H_HOSTSW_OWN,
      R_PCH_H_PCR_GPIO_GPP_H_PAD_OWN,
      R_PCH_H_PCR_GPIO_GPP_H_GPI_GPE_STS
    },
    Package(){ // GPP_I
      PCH_GPIO_COM3,
      V_PCH_H_GPIO_GPP_I_PAD_MAX,
      R_PCH_H_PCR_GPIO_GPP_I_PADCFG_OFFSET,
      R_PCH_H_PCR_GPIO_GPP_I_HOSTSW_OWN,
      R_PCH_H_PCR_GPIO_GPP_I_PAD_OWN,
      R_PCH_H_PCR_GPIO_GPP_I_GPI_GPE_STS
    },
    Package(){ // GPD
      PCH_GPIO_COM2,
      V_PCH_GPIO_GPD_PAD_MAX,
      R_PCH_PCR_GPIO_GPD_PADCFG_OFFSET,
      R_PCH_PCR_GPIO_GPD_HOSTSW_OWN,
      R_PCH_H_PCR_GPIO_GPD_PAD_OWN,
      R_PCH_PCR_GPIO_GPD_GPI_GPE_STS
    }
  })

  //
  // Object for storing RX Level/Edge Configuration for all pads.
  // One fields contains data for one pad.
  //   00b = Level
  //   01b = Edge (RxInv=0 for rising edge; 1 for falling edge)
  //   10b = Disabled
  //   11b = Either rising edge or falling edge
  //
  // Each row has data for one group. Buffer size needs
  // to equal to number of pads
  Name(RXEV, Package(){
    Buffer(V_PCH_GPIO_GPP_A_PAD_MAX){},   // GPP_A
    Buffer(V_PCH_GPIO_GPP_B_PAD_MAX){},   // GPP_B
    Buffer(V_PCH_GPIO_GPP_C_PAD_MAX){},   // GPP_C
    Buffer(V_PCH_GPIO_GPP_D_PAD_MAX){},   // GPP_D
    Buffer(V_PCH_GPIO_GPP_E_PAD_MAX){},   // GPP_E
    Buffer(V_PCH_GPIO_GPP_F_PAD_MAX){},   // GPP_F
    Buffer(V_PCH_GPIO_GPP_G_PAD_MAX){},   // GPP_G
    Buffer(V_PCH_H_GPIO_GPP_H_PAD_MAX){}, // PCH-H GPP_H, PCH-LP GPD
    Buffer(V_PCH_H_GPIO_GPP_I_PAD_MAX){}, // PCH-H GPP_I, PCH-LP not used
    Buffer(V_PCH_GPIO_GPD_PAD_MAX){}      // PCH-H GPD,   PCH-LP not used
  })
}