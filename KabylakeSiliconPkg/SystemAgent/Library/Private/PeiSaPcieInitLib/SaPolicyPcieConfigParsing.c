/** @file
  PEI Function to initialize SA PciExpress.

 @copyright
  INTEL CONFIDENTIAL
  Copyright 2014 - 2016 Intel Corporation.

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

@par Specification
**/

#include <Private/Library/SaInitLib.h>
#include <Private/Library/SaPcieInitLib.h>

/**
  Determines if SA Policy enables Gen3 on any of the PEG root ports

  @param[in]  PciePeiPreMemConfig                  - SA Policy PCIe Config Block

  @retval TRUE  - At least 1 root port has Gen3 enabled
  @retval FALSE - otherwise
**/
BOOLEAN
SaPolicyEnablesGen3 (
  IN       PCIE_PEI_PREMEM_CONFIG     *PciePeiPreMemConfig
  )
{
  UINTN   PegMaxLinkSpeed;
  BOOLEAN Gen3Enabled;
  UINT8   Index;

  Gen3Enabled = FALSE;

  ///
  /// Check if Gen3 is enabled on PEG10/11/12
  ///
  for (Index = 0; Index < SA_PEG_MAX_FUN; Index++) {
    ///
    /// PegMaxLinkSpeed: 0 = Auto, 1 = Gen1, 2 = Gen2, 3 = Gen3
    ///
    switch (Index) {
      case 0:
        PegMaxLinkSpeed = PciePeiPreMemConfig->Peg0MaxLinkSpeed;
        break;
      case 1:
        PegMaxLinkSpeed = PciePeiPreMemConfig->Peg1MaxLinkSpeed;
        break;
      case 2:
        PegMaxLinkSpeed = PciePeiPreMemConfig->Peg2MaxLinkSpeed;
        break;
      default:
        PegMaxLinkSpeed = PEG_GEN1;
        break;
    }

    ///
    /// Check if the root port is present and the speed is not limited to Gen1/Gen2
    ///
    if ((PegMaxLinkSpeed == PEG_AUTO) || (PegMaxLinkSpeed == PEG_GEN3)) {
      Gen3Enabled = TRUE;
      break;
    }
  }
  return Gen3Enabled;
}

/**
  Determines the SA Policy Phase 3 Equalization Method for a given root port

  @param[in]  PegFunc                     - Function Number of the Root Port
  @param[in]  PciePeiPreMemConfig         - SA Policy PCIe Config Block

  @retval Equalization Phase 3 Method
**/
UINT8
SaPolicyGetEqPhase3Method (
  IN UINT8                  PegFunc,
  IN PCIE_PEI_PREMEM_CONFIG *PciePeiPreMemConfig
  )
{
  switch (PegFunc) {
    case 0:
      return (UINT8) PciePeiPreMemConfig->Peg0Gen3EqPh3Method;
    case 1:
      return (UINT8) PciePeiPreMemConfig->Peg1Gen3EqPh3Method;
    case 2:
      return (UINT8) PciePeiPreMemConfig->Peg2Gen3EqPh3Method;
    default:
      return 0;
  }
}

/**
  Determines if SA Policy enabled Phase 2 Equalization on a given root port

  @param[in]  PegFunc                     - Function Number of the Root Port
  @param[in]  PciePeiPreMemConfig         - SA Policy PCIe Config Block

  @retval TRUE  - Equalization Phase 2 is enabled
  @retval FALSE - Equalization Phase 2 is disabled
**/
BOOLEAN
SaPolicyGetEqPhase2Enable (
  IN UINT8                  PegFunc,
  IN PCIE_PEI_PREMEM_CONFIG *PciePeiPreMemConfig
  )
{
  UINT8 Phase2Enable;

  switch (PegFunc) {
    case 0:
      Phase2Enable = (UINT8) PciePeiPreMemConfig->Peg0Gen3EqPh2Enable;
      break;
    case 1:
      Phase2Enable = (UINT8) PciePeiPreMemConfig->Peg1Gen3EqPh2Enable;
      break;
    case 2:
      Phase2Enable = (UINT8) PciePeiPreMemConfig->Peg2Gen3EqPh2Enable;
      break;
    default:
      Phase2Enable = 1;
  }
  if (Phase2Enable == 0) {
    return FALSE;
  } else {
    return TRUE;
  }
}

/**
  Determines if SA Policy enables Phase 3 Software Equalization on a given root port

  @param[in]  PegFunc                     - Function Number of the Root Port
  @param[in]  PciePeiPreMemConfig         - SA Policy PCIe Config Block

  @retval TRUE  - Phase 3 Software Equalization is enabled
  @retval FALSE - Phase 3 Software Equalization is disabled
**/
BOOLEAN
SaPolicySwEqEnabledOnPort (
  IN UINT8                  PegFunc,
  IN PCIE_PEI_PREMEM_CONFIG *PciePeiPreMemConfig
  )
{
  UINT8 EqMethod;

  EqMethod = SaPolicyGetEqPhase3Method (PegFunc, PciePeiPreMemConfig);
  if (EqMethod == PH3_METHOD_SWEQ) {
    return TRUE;
  }
  return FALSE;
}

/**
  Determines if SA Policy enables Phase 3 Software Equalization any of the PEG ports

  @param[in]  PciePeiPreMemConfig                  - SA Policy PCIe Config Block

  @retval TRUE  - At least 1 root port has Phase 3 Software Equalization enabled
  @retval FALSE - Otherwise
**/
BOOLEAN
SaPolicyEnablesSwEq (
  IN  PCIE_PEI_PREMEM_CONFIG   *PciePeiPreMemConfig
  )
{
  UINT8  PegFunc;

  for (PegFunc = 0; PegFunc < SA_PEG_MAX_FUN; PegFunc++) {
    if (SaPolicySwEqEnabledOnPort (PegFunc, PciePeiPreMemConfig)) {
      return TRUE;
    }
  }
  return FALSE;
}

/**
  Gets the SA Policy defined max link width for a given root port

  @param[in]  PegFunc                     - Function Number of the Root Port
  @param[in]  PciePeiPreMemConfig         - SA Policy PCIe Config Block

  @retval Max link width
**/
UINT8
SaPolicyGetPegMaxLinkWidth (
  IN UINT8                  PegFunc,
  IN PCIE_PEI_PREMEM_CONFIG *PciePeiPreMemConfig
  )
{
  UINT8   MaxLinkWidth;
  switch (PegFunc) {
    case 0:
      MaxLinkWidth = (UINT8) PciePeiPreMemConfig->Peg0MaxLinkWidth;
      break;
    case 1:
      MaxLinkWidth = (UINT8) PciePeiPreMemConfig->Peg1MaxLinkWidth;
      break;
    case 2:
      MaxLinkWidth = (UINT8) PciePeiPreMemConfig->Peg2MaxLinkWidth;
      break;
    default:
      return 0;
  }
  switch (MaxLinkWidth) {
    case 0:
      return 0;
    case 1:
      return 1;
    case 2:
      return 2;
    case 3:
      return 4;
    case 4:
      return 8;
    default:
      return 0;
  }
}

/**
  Gets the SA Policy defined max link speed for a given root port

  @param[in]  PegFunc                     - Function Number of the Root Port
  @param[in]  PciePeiPreMemConfig         - SA Policy PCIe Config Block

  @retval Max link speed
**/
UINT8
SaPolicyGetPegMaxLinkSpeed (
  IN UINT8                  PegFunc,
  IN PCIE_PEI_PREMEM_CONFIG *PciePeiPreMemConfig
  )
{
  UINT8   MaxLinkSpeed;
  switch (PegFunc) {
    case 0:
      MaxLinkSpeed = (UINT8) PciePeiPreMemConfig->Peg0MaxLinkSpeed;
      break;
    case 1:
      MaxLinkSpeed = (UINT8) PciePeiPreMemConfig->Peg1MaxLinkSpeed;
      break;
    case 2:
      MaxLinkSpeed = (UINT8) PciePeiPreMemConfig->Peg2MaxLinkSpeed;
      break;
    default:
      return PEG_AUTO;
  }
  return MaxLinkSpeed;
}

/**
  Determines if SA Policy forces a given root port to always be enabled

  @param[in]  PegFunc                     - Function Number of the Root Port
  @param[in]  PciePeiPreMemConfig         - SA Policy PCIe Config Block

  @retval TRUE  - SA Policy forces the root port to be enabled
  @retval FALSE - SA Policy does not force the root port to be enabled
**/
BOOLEAN
SaPolicyForceEnablesPort (
  IN UINT8                  PegFunc,
  IN PCIE_PEI_PREMEM_CONFIG *PciePeiPreMemConfig
  )
{
  switch (PegFunc) {
    case 0:
      if (PciePeiPreMemConfig->Peg0Enable == 1) {
        return TRUE;
      }
      break;
    case 1:
      if (PciePeiPreMemConfig->Peg1Enable == 1) {
        return TRUE;
      }
      break;
    case 2:
      if (PciePeiPreMemConfig->Peg2Enable == 1) {
        return TRUE;
      }
      break;
    default:
      break;
  }
  return FALSE;
}

/**
  Determines if SA Policy forces a given root port to always be disabled

  @param[in]  PegFunc                     - Function Number of the Root Port
  @param[in]  PciePeiPreMemConfig         - SA Policy PCIe Config Block

  @retval TRUE  - SA Policy forces the root port to be disabled
  @retval FALSE - SA Policy does not force the root port to be disabled
**/
BOOLEAN
SaPolicyForceDisablesPort (
  IN UINT8                  PegFunc,
  IN PCIE_PEI_PREMEM_CONFIG *PciePeiPreMemConfig
  )
{
  switch (PegFunc) {
    case 0:
      if (PciePeiPreMemConfig->Peg0Enable == 0) {
        return TRUE;
      }
      break;
    case 1:
      if (PciePeiPreMemConfig->Peg1Enable == 0) {
        return TRUE;
      }
      break;
    case 2:
      if (PciePeiPreMemConfig->Peg2Enable == 0) {
        return TRUE;
      }
      break;
    default:
      break;
  }
  return FALSE;
}

/**
  Determines if SA Policy allows unused lanes to be powered down

  @param[in]  PegFunc                     - Function Number of the Root Port
  @param[in]  PciePeiPreMemConfig         - SA Policy PCIe Config Block

  @retval 0x1 - SA Policy allows unused lanes to be powered down
  @retval 0x0 - SA Policy disallows unused lanes to be powered down
**/
UINT8
SaPolicyGetPowerDownUnusedLanes (
  IN UINT8                  PegFunc,
  IN PCIE_PEI_PREMEM_CONFIG *PciePeiPreMemConfig
  )
{
  switch (PegFunc) {
    case 0:
      return (UINT8) PciePeiPreMemConfig->Peg0PowerDownUnusedLanes;
      break;
    case 1:
      return (UINT8) PciePeiPreMemConfig->Peg1PowerDownUnusedLanes;
      break;
    case 2:
      return (UINT8) PciePeiPreMemConfig->Peg2PowerDownUnusedLanes;
      break;
    default:
      return 1;
      break;
  }
}
