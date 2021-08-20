/**@file
  This is the code that initializes eSPI.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2017 Intel Corporation.

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

/**
  Configures PCH eSPI

  @param[in]  PCH_ESPI_CONFIG   The eSPI config block
**/
VOID
ConfigureEspi (
  IN  PCH_ESPI_CONFIG     *EspiConfig
  )
{
  UINT32            Data32;
  UINTN             EspiPciBase;

  DEBUG ((DEBUG_INFO, "[ConfigureEspi] Entry.\n"));

  if (!IsEspiEnabled ()) {
    DEBUG ((DEBUG_INFO, "[ConfigureEspi] eSPI is disabled through strap.\n"));
    goto Exit;
  }

  if (EspiConfig->BmeMasterSlaveEnabled == TRUE) {
    DEBUG ((DEBUG_INFO, "[ConfigureEspi] Setting BME for both Master and Slave devices.\n"));
    EspiPciBase = MmPciBase (
                    DEFAULT_PCI_BUS_NUMBER_PCH,
                    PCI_DEVICE_NUMBER_PCH_LPC,
                    PCI_FUNCTION_NUMBER_PCH_LPC
                    );

    //
    // Set the BME bit on eSPI-MC
    //
    MmioOr16 (EspiPciBase + PCI_COMMAND_OFFSET, (UINT32) EFI_PCI_COMMAND_BUS_MASTER);

    //
    // Set the BME bit on eSPI Slave 0 using the Tunneled Access
    //
    PchEspiSlaveGetConfig (0, R_ESPI_SLAVE_CHA_0_CAP_AND_CONF, &Data32);
    Data32 |= B_ESPI_SLAVE_CHA_0_CAP_AND_CONF_BME;
    PchEspiSlaveSetConfig (0, R_ESPI_SLAVE_CHA_0_CAP_AND_CONF, Data32);

    PchPcrRead32 (PID_ESPISPI, R_PCH_PCR_SPI_ESPI_SOFTSTRAPS, &Data32);
    if (Data32 & B_PCH_PCR_SPI_ESPI_SOFTSTRAPS_SLAVE) {
      //
      // Set the BME bit on eSPI Slave 1 using the Tunneled Access
      //
      PchEspiSlaveGetConfig (1, R_ESPI_SLAVE_CHA_0_CAP_AND_CONF, &Data32);
      Data32 |= B_ESPI_SLAVE_CHA_0_CAP_AND_CONF_BME;
      PchEspiSlaveSetConfig (1, R_ESPI_SLAVE_CHA_0_CAP_AND_CONF, Data32);
    }
  }

Exit:
  DEBUG ((DEBUG_INFO, "[ConfigureEspi] Exit.\n"));
}
