/** @file
  CPU Pei Gcc Support - Dummy functions

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

@par Specification
**/

///
/// Function declarations
///
/**
  This is dummy function equivelant to the asm function DoGlobalReset(), made for GCC build.
**/
VOID
DoGlobalReset (
  VOID
  )
{
  return;
}

/**
  This is dummy function equivelant to the asm function LaunchBiosAcmSclean(), made for GCC build.
**/
VOID
LaunchBiosAcmSclean (
  VOID
  )
{
  return;
}

/**
  This is dummy function equivelant to the asm function LaunchBiosAcmAcheck(), made for GCC build.
**/
VOID
LaunchBiosAcmAcheck (
  VOID
  )
{
  return;
}

/**
  This is dummy function equivelant to the asm function SaveApConfig(), made for GCC build.
**/
VOID
SaveApConfig (
  UINT64 *ApCfg
  )
{
  return;
}

/**
  This is dummy function equivelant to the asm function DoApInit(), made for GCC build.
**/
VOID
DoApInit (
  VOID *Param
  )
{
  return;
}

/**
  This is dummy function equivelant to the asm function StartupAllAPs(), made for GCC build.
**/
VOID
StartupAllAPs (
  VOID (*Function)(),
  UINT64 *Param
  )
{
}

/**
  This is dummy function equivelant to the asm function PutApsInWfs(), made for GCC build.
**/
VOID
PutApsInWfs (
  VOID
  )
{
  return;
}

/**
  This is dummy function equivelant to the asm function LaunchBiosAcmScheck(), made for GCC build.
**/
VOID
LaunchBiosAcmScheck (
  IN UINT64 *BiosAcAddr
  )
{
  return;
}

/**
  This is dummy function equivelant to the asm function RestoreApConfig(), made for GCC build.
**/
VOID
RestoreApConfig (
  UINT64 *ApCfg
  )
{
  return;
}

/**
  This is dummy function equivelant to the asm function RestoreMtrrProgramming(), made for GCC build.
**/
VOID
RestoreMtrrProgramming (
  UINT64 *ApCfg
  )
{
}
