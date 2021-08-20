/** @file
  This file contains the main entry point for the MRC mini-BIOS.

 @copyright
  INTEL CONFIDENTIAL
  Copyright 2013 - 2016 Intel Corporation.

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
#ifndef _MrcSsaInitialize_h_
#define _MrcSsaInitialize_h_

#include "MrcSsaServices.h"

#ifdef SSA_FLAG
typedef struct _SSA_BIOS_FUNCTION_RW {
#ifndef MRC_MINIBIOS_BUILD
  EFI_PEI_PPI_DESCRIPTOR SsaPpiDescriptor;
#endif
  SSA_BIOS_SERVICES_PPI  SsaBiosPointers;
  SSA_COMMON_CONFIG      SsaCommonConfig;
  SSA_RESULTS_CONFIG     SsaResultsConfig;
  SSA_MEMORY_CONFIG      SsaMemoryConfig;
} SSA_BIOS_FUNCTION_RW;

extern SSA_CONST SSA_BIOS_SERVICES_PPI SsaBiosServicesPpi;
extern SSA_CONST SSA_COMMON_CONFIG SsaCommonConfig;
extern SSA_CONST SSA_RESULTS_CONFIG SsaResultsConfig;
extern SSA_CONST SSA_MEMORY_CONFIG SsaMemoryConfig;
extern SSA_CONST SSA_MEMORY_CLIENT_CONFIG SsaMemoryClientConfig;
extern SSA_CONST SSA_MEMORY_SERVER_CONFIG SsaMemoryServerConfig;
extern SSA_CONST SSA_MEMORY_DDRT_CONFIG SsaMemoryDdrtConfig;

/**
  Initialize the SsaBiosServices data structure.

  @param[in] MrcData  - The MRC global data area.

  @retval Nothing
**/
extern
void
SsaBiosInitialize (
  IN MrcParameters *MrcData
  );

#endif
#endif
