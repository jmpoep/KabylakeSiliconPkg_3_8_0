@REM @file
@REM
@REM @copyright
@REM  INTEL CONFIDENTIAL
@REM  Copyright 2014 - 2016 Intel Corporation.
@REM
@REM  The source code contained or described herein and all documents related to the
@REM  source code ("Material") are owned by Intel Corporation or its suppliers or
@REM  licensors. Title to the Material remains with Intel Corporation or its suppliers
@REM  and licensors. The Material may contain trade secrets and proprietary and
@REM  confidential information of Intel Corporation and its suppliers and licensors,
@REM  and is protected by worldwide copyright and trade secret laws and treaty
@REM  provisions. No part of the Material may be used, copied, reproduced, modified,
@REM  published, uploaded, posted, transmitted, distributed, or disclosed in any way
@REM  without Intel's prior express written permission.
@REM
@REM  No license under any patent, copyright, trade secret or other intellectual
@REM  property right is granted to or conferred upon you by disclosure or delivery
@REM  of the Materials, either expressly, by implication, inducement, estoppel or
@REM  otherwise. Any license under such intellectual property rights must be
@REM  express and approved by Intel in writing.
@REM
@REM  Unless otherwise agreed by Intel in writing, you may not remove or alter
@REM  this notice or any other notice embedded in Materials by Intel or
@REM  Intel's suppliers or licensors in any way.
@REM
@REM  This file contains an 'Intel Peripheral Driver' and is uniquely identified as
@REM  "Intel Reference Module" and is licensed for Intel CPUs and chipsets under
@REM  the terms of your license agreement with Intel or your vendor. This file may
@REM  be modified by the user, subject to additional terms of the license agreement.
@REM
@REM @par Specification
@REM

@call edksetup.bat

@if not defined TOOL_CHAIN_TAG (
  if defined VS140COMNTOOLS (
    echo.
    echo Prebuild:  Set the VS2015 environment.
    echo.
    if not defined VSINSTALLDIR call "%VS140COMNTOOLS%\vsvars32.bat"
    if /I "%VS140COMNTOOLS%" == "C:\Program Files\Microsoft Visual Studio 14.0\Common7\Tools\" (
      set TOOL_CHAIN_TAG=VS2015
    ) else (
      set TOOL_CHAIN_TAG=VS2015x86
    )
  )
)

@if not defined TOOL_CHAIN_TAG (
  if defined VS120COMNTOOLS (
    echo.
    echo Prebuild:  Set the VS2013 environment.
    echo.
    if not defined VSINSTALLDIR call "%VS120COMNTOOLS%\vsvars32.bat"
    if /I "%VS120COMNTOOLS%" == "C:\Program Files\Microsoft Visual Studio 12.0\Common7\Tools\" (
      set TOOL_CHAIN_TAG=VS2013
    ) else (
      set TOOL_CHAIN_TAG=VS2013x86
    )
  )
)

set TARGET=RELEASE

@echo.
@echo Set build environment.
@echo.
@if not exist Build\KabylakeSiliconPkg\%TARGET%_%TOOL_CHAIN_TAG% (
  mkdir Build\KabylakeSiliconPkg\%TARGET%_%TOOL_CHAIN_TAG%
)


@findstr /V "ACTIVE_PLATFORM TARGET TARGET_ARCH TOOL_CHAIN_TAG BUILD_RULE_CONF" Conf\target.txt > Build\%PLATFORM_PACKAGE%\%TARGET%_%TOOL_CHAIN_TAG%\target.txt
@echo ACTIVE_PLATFORM = KabylakeSiliconPkg/KabylakeSiliconPkg.dsc        >> Build\KabylakeSiliconPkg\%TARGET%_%TOOL_CHAIN_TAG%\target.txt
@echo TARGET          = %TARGET%                                 >> Build\KabylakeSiliconPkg\%TARGET%_%TOOL_CHAIN_TAG%\target.txt
@echo TARGET_ARCH     = IA32 X64                                  >> Build\KabylakeSiliconPkg\%TARGET%_%TOOL_CHAIN_TAG%\target.txt
@echo TOOL_CHAIN_TAG  = %TOOL_CHAIN_TAG%                          >> Build\KabylakeSiliconPkg\%TARGET%_%TOOL_CHAIN_TAG%\target.txt
@echo BUILD_RULE_CONF = Conf/build_rule.txt                       >> Build\KabylakeSiliconPkg\%TARGET%_%TOOL_CHAIN_TAG%\target.txt
@move /Y Build\KabylakeSiliconPkg\%TARGET%_%TOOL_CHAIN_TAG%\target.txt Conf

build

