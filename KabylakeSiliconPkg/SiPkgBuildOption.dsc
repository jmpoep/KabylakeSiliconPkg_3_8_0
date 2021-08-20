## @file
# Silicon build option configuration file.
#
# Copyright (c) 2015 - 2017 Intel Corporation. All rights reserved.<BR>
# This software and associated documentation (if any) is furnished
# under a license and may only be used or copied in accordance
# with the terms of the license. Except as permitted by such
# license, no part of this software or documentation may be
# reproduced, stored in a retrieval system, or transmitted in any
# form or by any means without the express written consent of
# Intel Corporation.
# This file contains an 'Intel Peripheral Driver' and is
# licensed for Intel CPUs and chipsets under the terms of your
# license agreement with Intel or your vendor.  This file may
# be modified by the user, subject to additional terms of the
# license agreement
##
# @copyright
#  INTEL CONFIDENTIAL
#  Copyright 2015 - 2016 Intel Corporation.
#
#  The source code contained or described herein and all documents related to the
#  source code ("Material") are owned by Intel Corporation or its suppliers or
#  licensors. Title to the Material remains with Intel Corporation or its suppliers
#  and licensors. The Material may contain trade secrets and proprietary and
#  confidential information of Intel Corporation and its suppliers and licensors,
#  and is protected by worldwide copyright and trade secret laws and treaty
#  provisions. No part of the Material may be used, copied, reproduced, modified,
#  published, uploaded, posted, transmitted, distributed, or disclosed in any way
#  without Intel's prior express written permission.
#
#  No license under any patent, copyright, trade secret or other intellectual
#  property right is granted to or conferred upon you by disclosure or delivery
#  of the Materials, either expressly, by implication, inducement, estoppel or
#  otherwise. Any license under such intellectual property rights must be
#  express and approved by Intel in writing.
#
#  Unless otherwise agreed by Intel in writing, you may not remove or alter
#  this notice or any other notice embedded in Materials by Intel or
#  Intel's suppliers or licensors in any way.
#
#  This file contains an 'Intel Peripheral Driver' and is uniquely identified as
#  "Intel Reference Module" and is licensed for Intel CPUs and chipsets under
#  the terms of your license agreement with Intel or your vendor. This file may
#  be modified by the user, subject to additional terms of the license agreement.
#
# @par Specification
##

[BuildOptions]
# Define Build Options both for EDK and EDKII drivers.



# SA
!if gSiPkgTokenSpaceGuid.PcdPttEnable == TRUE
  DEFINE PTT_BUILD_OPTION = -DPTT_FLAG=1
!else
  DEFINE PTT_BUILD_OPTION =
!endif


  DEFINE SIMICS_BUILD_OPTIONS =

!if gSiPkgTokenSpaceGuid.PcdSgEnable == TRUE
  DEFINE DSC_SG_BUILD_OPTIONS = -DSG_SUPPORT=1
!else
  DEFINE DSC_SG_BUILD_OPTIONS =
!endif

!if gSiPkgTokenSpaceGuid.PcdBdatEnable == TRUE
  DEFINE BDAT_BUILD_OPTION = -DBDAT_SUPPORT=1
!else
  DEFINE BDAT_BUILD_OPTION =
!endif

!if gSiPkgTokenSpaceGuid.PcdSsaFlagEnable == TRUE
  DEFINE DSC_SSA_BUILD_OPTIONS = -DSSA_FLAG=1 -DSSA_CLIENT_FLAG=1
  DEFINE BDAT_BUILD_OPTION = -DBDAT_SUPPORT=1
!else
  DEFINE DSC_SSA_BUILD_OPTIONS =
!endif

!if gSiPkgTokenSpaceGuid.PcdAmtEnable == TRUE
  DEFINE DSC_AMT_BUILD_OPTIONS = -DAMT_SUPPORT=1
!else
  DEFINE DSC_AMT_BUILD_OPTIONS =
!endif

  DEFINE SLE_BUILD_OPTIONS =
!if $(TARGET) == RELEASE
!if gSiPkgTokenSpaceGuid.PcdSiCatalogDebugEnable == TRUE
  DEFINE DEBUG_BUILD_OPTIONS =
!else
  # MDEPKG_NDEBUG is introduced for the intention
  # of size reduction when compiler optimization is disabled. If MDEPKG_NDEBUG is
  # defined, then debug and assert related macros wrapped by it are the NULL implementations.
  DEFINE DEBUG_BUILD_OPTIONS = -DMDEPKG_NDEBUG
!endif
!else
  DEFINE DEBUG_BUILD_OPTIONS =
!endif

!if gSiPkgTokenSpaceGuid.PcdOptimizeCompilerEnable == FALSE
  DEFINE OPTIMIZE_DISABLE_OPTIONS = -Od -GL-
!else
  DEFINE OPTIMIZE_DISABLE_OPTIONS =
!endif

DEFINE DSC_SIPKG_FEATURE_BUILD_OPTIONS = $(BDAT_BUILD_OPTION) $(PTT_BUILD_OPTION) $(DEBUG_BUILD_OPTIONS) $(DSC_SSA_BUILD_OPTIONS) $(DSC_AMT_BUILD_OPTIONS)
DEFINE DSC_SIPKG_FEATURE_BUILD_OPTIONS = $(DSC_SIPKG_FEATURE_BUILD_OPTIONS) $(DSC_SG_BUILD_OPTIONS) $(SIMICS_BUILD_OPTIONS)

!if gSiPkgTokenSpaceGuid.PcdSourceDebugEnable == TRUE
  *_*_X64_GENFW_FLAGS = --keepexceptiontable
!endif

[BuildOptions.Common.EDKII]

#
# For IA32 Global Build Flag
#
       *_*_IA32_CC_FLAGS      = $(DSC_SIPKG_FEATURE_BUILD_OPTIONS) -D PI_SPECIFICATION_VERSION=0x00010015 -DASF_PEI
       *_*_IA32_VFRPP_FLAGS   = $(DSC_SIPKG_FEATURE_BUILD_OPTIONS)
       *_*_IA32_APP_FLAGS     = $(DSC_SIPKG_FEATURE_BUILD_OPTIONS)
       *_*_IA32_ASLPP_FLAGS   = $(DSC_SIPKG_FEATURE_BUILD_OPTIONS)
       *_*_IA32_ASLCC_FLAGS   = $(DSC_SIPKG_FEATURE_BUILD_OPTIONS)

#
# For IA32 Specific Build Flag
#
GCC:   *_*_IA32_PP_FLAGS      = $(DSC_SIPKG_FEATURE_BUILD_OPTIONS)
MSFT:  *_*_IA32_ASM_FLAGS     = $(DSC_SIPKG_FEATURE_BUILD_OPTIONS)
MSFT:  *_*_IA32_CC_FLAGS      = $(DSC_SIPKG_FEATURE_BUILD_OPTIONS) $(OPTIMIZE_DISABLE_OPTIONS) -D PI_SPECIFICATION_VERSION=0x00010015 -DASF_PEI
MSFT:  *_*_IA32_VFRPP_FLAGS   = $(DSC_SIPKG_FEATURE_BUILD_OPTIONS) $(OPTIMIZE_DISABLE_OPTIONS)
MSFT:  *_*_IA32_APP_FLAGS     = $(DSC_SIPKG_FEATURE_BUILD_OPTIONS) $(OPTIMIZE_DISABLE_OPTIONS)
MSFT:  *_*_IA32_ASLPP_FLAGS   = $(DSC_SIPKG_FEATURE_BUILD_OPTIONS) $(OPTIMIZE_DISABLE_OPTIONS)
MSFT:  *_*_IA32_ASLCC_FLAGS   = $(DSC_SIPKG_FEATURE_BUILD_OPTIONS) $(OPTIMIZE_DISABLE_OPTIONS)

#
# For X64 Global Build Flag
#
       *_*_X64_CC_FLAGS       = $(DSC_SIPKG_FEATURE_BUILD_OPTIONS) -D PI_SPECIFICATION_VERSION=0x00010015
       *_*_X64_VFRPP_FLAGS    = $(DSC_SIPKG_FEATURE_BUILD_OPTIONS)
       *_*_X64_APP_FLAGS      = $(DSC_SIPKG_FEATURE_BUILD_OPTIONS)
       *_*_X64_ASLPP_FLAGS    = $(DSC_SIPKG_FEATURE_BUILD_OPTIONS)
       *_*_X64_ASLCC_FLAGS    = $(DSC_SIPKG_FEATURE_BUILD_OPTIONS)

#
# For X64 Specific Build Flag
#
GCC:   *_*_X64_PP_FLAGS       = $(DSC_SIPKG_FEATURE_BUILD_OPTIONS)
MSFT:  *_*_X64_ASM_FLAGS      = $(DSC_SIPKG_FEATURE_BUILD_OPTIONS)
MSFT:  *_*_X64_CC_FLAGS       = $(DSC_SIPKG_FEATURE_BUILD_OPTIONS) $(OPTIMIZE_DISABLE_OPTIONS) -D PI_SPECIFICATION_VERSION=0x00010015
MSFT:  *_*_X64_VFRPP_FLAGS    = $(DSC_SIPKG_FEATURE_BUILD_OPTIONS) $(OPTIMIZE_DISABLE_OPTIONS)
MSFT:  *_*_X64_APP_FLAGS      = $(DSC_SIPKG_FEATURE_BUILD_OPTIONS) $(OPTIMIZE_DISABLE_OPTIONS)
MSFT:  *_*_X64_ASLPP_FLAGS    = $(DSC_SIPKG_FEATURE_BUILD_OPTIONS)
MSFT:  *_*_X64_ASLCC_FLAGS    = $(DSC_SIPKG_FEATURE_BUILD_OPTIONS)


[BuildOptions.common.EDKII.DXE_RUNTIME_DRIVER]
GCC:   *_*_*_DLINK_FLAGS      = -z common-page-size=0x1000
MSFT:  *_*_*_DLINK_FLAGS      = /ALIGN:4096
XCODE: *_*_*_DLINK_FLAGS      = -segalign 0x1000

