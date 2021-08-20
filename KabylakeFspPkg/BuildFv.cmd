@REM ## @file
@REM
@REM #@copyright
@REM #  Copyright (c) 2008 - 2017 Intel Corporation All rights reserved
@REM #  This software and associated documentation (if any) is furnished
@REM #  under a license and may only be used or copied in accordance
@REM #  with the terms of the license. Except as permitted by such
@REM #  license, no part of this software or documentation may be
@REM #  reproduced, stored in a retrieval system, or transmitted in any
@REM #  form or by any means without the express written consent of
@REM #  Intel Corporation.
@REM #  This file contains an 'Sample Driver' and is
@REM #  licensed for Intel CPUs and chipsets under the terms of your
@REM #  license agreement with Intel or your vendor.  This file may
@REM #  be modified by the user, subject to additional terms of the
@REM #  license agreement
@REM ##

@echo off
set CLIENT_SILICON_PKG_NAME=ClientSiliconPkg
set FSP_PKG_NAME=KabylakeFspPkg
set FSP_BIN_PKG_NAME=KabylakeFspBinPkg
@if /I "%1"=="/h" goto Usage
@if /I "%1"=="/?" goto Usage

@if not defined WORKSPACE (
  call %~dp0\..\EdkSetup.bat
)
set WORKSPACE_CORE=%WORKSPACE%

@if exist %WORKSPACE%\%CLIENT_SILICON_PKG_NAME%\Override\BaseTools\Conf\tools_def.template (
  copy %WORKSPACE%\%CLIENT_SILICON_PKG_NAME%\Override\BaseTools\Conf\tools_def.template %WORKSPACE%\Conf\tools_def.txt /Y
  )
@if exist %WORKSPACE%\%FSP_PKG_NAME%\Override\BaseTools\Conf\tools_def.template (
  copy %WORKSPACE%\%FSP_PKG_NAME%\Override\BaseTools\Conf\tools_def.template %WORKSPACE%\Conf\tools_def.txt /Y
  )
@if exist %WORKSPACE%\%FSP_PKG_NAME%\Override\BaseTools\Conf\build_rule.template (
  copy %WORKSPACE%\%FSP_PKG_NAME%\Override\BaseTools\Conf\build_rule.template %WORKSPACE%\Conf\build_rule.txt /Y
  )
@echo off
set OUT_DIR=Build
@REM clear the previous setting.
@if exist %WORKSPACE%\%FSP_PKG_NAME%\%FSP_PKG_NAME%ExtConfig.dsc attrib -r %WORKSPACE%\%FSP_PKG_NAME%\%FSP_PKG_NAME%ExtConfig.dsc
if /I "%1"=="/clean" goto Clean
if /I "%1"=="/r" goto ReleaseBuild
if /I "%1"=="/tr" goto ReleaseTypeTest
if /I "%1"=="/d" goto DebugBuild
if /I "%1"=="" (
  goto DebugBuild
) else (
  echo.
  echo  ERROR: "%1" is not valid parameter.
  goto Usage
)

:Clean
echo Removing Build and Conf directories ...
if exist Build rmdir Build /s /q
if exist Conf  rmdir Conf  /s /q
if exist *.log  del *.log /q /f
set WORKSPACE=
set EDK_TOOLS_PATH=
goto End


:ReleaseTypeTest
set  BD_TARGET=RELEASE
set  BD_MACRO=-D CFG_OUTDIR=%OUT_DIR% %EXT_BUILD_FLAGS%
set  BD_ARGS=-p %FSP_PKG_NAME%\%FSP_PKG_NAME%.dsc -b RELEASE %BD_MACRO% -a IA32 -n %NUMBER_OF_PROCESSORS% -t %TOOL_CHAIN_TAG% -y ReportRelease.log -Y PCD -Y LIBRARY %VAR_BUILD_FLAGS%
set  FSP_BUILD_TYPE=0x0001
set  FSP_RELEASE_TYPE=0x0000
goto Build

:ReleaseBuild
set  BD_TARGET=RELEASE
set  BD_MACRO=-D CFG_OUTDIR=%OUT_DIR% %EXT_BUILD_FLAGS%
set  BD_ARGS=-p %FSP_PKG_NAME%\%FSP_PKG_NAME%.dsc -b RELEASE %BD_MACRO% -a IA32 -n %NUMBER_OF_PROCESSORS% -t %TOOL_CHAIN_TAG% -y ReportRelease.log -Y PCD -Y LIBRARY %VAR_BUILD_FLAGS%
set  FSP_BUILD_TYPE=0x0001
set  FSP_RELEASE_TYPE=0x0002
goto Build

:DebugBuild
set  BD_TARGET=DEBUG
set  BD_MACRO=-D CFG_OUTDIR=%OUT_DIR% %EXT_BUILD_FLAGS%
set  BD_ARGS=-p %FSP_PKG_NAME%\%FSP_PKG_NAME%.dsc -b DEBUG  %BD_MACRO% -a IA32 -n %NUMBER_OF_PROCESSORS% -t %TOOL_CHAIN_TAG% -y ReportDebug.log -Y PCD -Y LIBRARY %VAR_BUILD_FLAGS%
set  FSP_BUILD_TYPE=0x0000
set  FSP_RELEASE_TYPE=0x0000
goto Build

:Build
build  -m %WORKSPACE%\%FSP_PKG_NAME%\FspHeader\FspHeader.inf %BD_ARGS%
if ERRORLEVEL 1 exit /b 1
call :PreBuild  CALL_RET
if "%CALL_RET%"=="1" exit /b 1
build  %BD_ARGS%
if ERRORLEVEL 1 exit /b 1
call :PostBuild
goto End

:Usage
echo.
echo  Usage: "%0 [/h | /? | /r | /tr | /d | /clean]"
echo.
exit /B 1

:CopyBin
@if exist %1\*.efi   xcopy %1\*.efi   %2 /D /U /Y > NUL
@if exist %1\*.inf   xcopy %1\*.inf   %2 /D /U /Y > NUL
@if exist %1\*.depex xcopy %1\*.depex %2 /D /U /Y > NUL
goto:EOF

:PreBuild
echo Start of PreBuild ...
if exist %WORKSPACE%\%FSP_PKG_NAME%\%FSP_PKG_NAME%.dsc attrib -r %WORKSPACE%\%FSP_PKG_NAME%\%FSP_PKG_NAME%.dsc
set %~1=1
set FSP_T_UPD_GUID=34686CA3-34F9-4901-B82A-BA630F0714C6
set FSP_M_UPD_GUID=39A250DB-E465-4DD1-A2AC-E2BD3C0E2385
set FSP_S_UPD_GUID=CAE3605B-5B34-4C85-B3D7-27D54273C40F
python %WORKSPACE%/%FSP_PKG_NAME%/Override/IntelFsp2Pkg/Tools/GenCfgOpt.py UPDTXT ^
     %WORKSPACE%\%FSP_PKG_NAME%\%FSP_PKG_NAME%.dsc ^
     %WORKSPACE%\%OUT_DIR%\%FSP_PKG_NAME%\%BD_TARGET%_%TOOL_CHAIN_TAG%\FV ^
     %BD_MACRO%
if "%ERRORLEVEL%"=="256" (
  REM  DSC is not changed, no need to recreate MAP and BIN file
) else (
  if ERRORLEVEL 1 goto:PreBuildFail
  echo UPD TXT file was generated successfully !

  echo Generate VPD Header File ...
  del /q /f %WORKSPACE%\%OUT_DIR%\%FSP_PKG_NAME%\%BD_TARGET%_%TOOL_CHAIN_TAG%\FV\%FSP_T_UPD_GUID%.bin ^
            %WORKSPACE%\%OUT_DIR%\%FSP_PKG_NAME%\%BD_TARGET%_%TOOL_CHAIN_TAG%\FV\%FSP_T_UPD_GUID%.map 2>nul

  del /q /f %WORKSPACE%\%OUT_DIR%\%FSP_PKG_NAME%\%BD_TARGET%_%TOOL_CHAIN_TAG%\FV\%FSP_M_UPD_GUID%.bin ^
            %WORKSPACE%\%OUT_DIR%\%FSP_PKG_NAME%\%BD_TARGET%_%TOOL_CHAIN_TAG%\FV\%FSP_M_UPD_GUID%.map 2>nul

  del /q /f %WORKSPACE%\%OUT_DIR%\%FSP_PKG_NAME%\%BD_TARGET%_%TOOL_CHAIN_TAG%\FV\%FSP_S_UPD_GUID%.bin ^
            %WORKSPACE%\%OUT_DIR%\%FSP_PKG_NAME%\%BD_TARGET%_%TOOL_CHAIN_TAG%\FV\%FSP_S_UPD_GUID%.map 2>nul

  %WORKSPACE%\BaseTools\Bin\Win32\BPDG.exe ^
       %WORKSPACE%\%OUT_DIR%\%FSP_PKG_NAME%\%BD_TARGET%_%TOOL_CHAIN_TAG%\FV\%FSP_T_UPD_GUID%.txt ^
       -o %WORKSPACE%\%OUT_DIR%\%FSP_PKG_NAME%\%BD_TARGET%_%TOOL_CHAIN_TAG%\FV\%FSP_T_UPD_GUID%.bin ^
       -m %WORKSPACE%\%OUT_DIR%\%FSP_PKG_NAME%\%BD_TARGET%_%TOOL_CHAIN_TAG%\FV\%FSP_T_UPD_GUID%.map
  if ERRORLEVEL 1 goto:PreBuildFail

  %WORKSPACE%\BaseTools\Bin\Win32\BPDG.exe ^
       %WORKSPACE%\%OUT_DIR%\%FSP_PKG_NAME%\%BD_TARGET%_%TOOL_CHAIN_TAG%\FV\%FSP_M_UPD_GUID%.txt ^
       -o %WORKSPACE%\%OUT_DIR%\%FSP_PKG_NAME%\%BD_TARGET%_%TOOL_CHAIN_TAG%\FV\%FSP_M_UPD_GUID%.bin ^
       -m %WORKSPACE%\%OUT_DIR%\%FSP_PKG_NAME%\%BD_TARGET%_%TOOL_CHAIN_TAG%\FV\%FSP_M_UPD_GUID%.map
  if ERRORLEVEL 1 goto:PreBuildFail

  %WORKSPACE%\BaseTools\Bin\Win32\BPDG.exe ^
       %WORKSPACE%\%OUT_DIR%\%FSP_PKG_NAME%\%BD_TARGET%_%TOOL_CHAIN_TAG%\FV\%FSP_S_UPD_GUID%.txt ^
       -o %WORKSPACE%\%OUT_DIR%\%FSP_PKG_NAME%\%BD_TARGET%_%TOOL_CHAIN_TAG%\FV\%FSP_S_UPD_GUID%.bin ^
       -m %WORKSPACE%\%OUT_DIR%\%FSP_PKG_NAME%\%BD_TARGET%_%TOOL_CHAIN_TAG%\FV\%FSP_S_UPD_GUID%.map
  if ERRORLEVEL 1 goto:PreBuildFail
)

python %WORKSPACE%/%FSP_PKG_NAME%/Override/IntelFsp2Pkg/Tools/GenCfgOpt.py HEADER ^
         %WORKSPACE%\%FSP_PKG_NAME%\%FSP_PKG_NAME%.dsc ^
         %WORKSPACE%\%OUT_DIR%\%FSP_PKG_NAME%\%BD_TARGET%_%TOOL_CHAIN_TAG%\FV ^
         %WORKSPACE%\%FSP_PKG_NAME%\Include\BootLoaderPlatformData.h ^
         %BD_MACRO%
if "%ERRORLEVEL%"=="256" (
    REM  No need to recreate header file
) else (
    if ERRORLEVEL 1 goto:PreBuildFail
    echo Vpd header file was generated successfully !

    echo Generate BSF File ...

    if not exist %WORKSPACE%\%FSP_BIN_PKG_NAME% mkdir %WORKSPACE%\%FSP_BIN_PKG_NAME%
    if exist %WORKSPACE%\%FSP_BIN_PKG_NAME%\Fsp.bsf attrib -r %WORKSPACE%\%FSP_BIN_PKG_NAME%\Fsp.bsf
    python %WORKSPACE%/%FSP_PKG_NAME%/Override/IntelFsp2Pkg/Tools/GenCfgOpt.py GENBSF ^
         %WORKSPACE%\%FSP_PKG_NAME%\%FSP_PKG_NAME%.dsc ^
         %WORKSPACE%\%OUT_DIR%\%FSP_PKG_NAME%\%BD_TARGET%_%TOOL_CHAIN_TAG%\FV ^
         %WORKSPACE%\%FSP_BIN_PKG_NAME%\Fsp.bsf ^
         %BD_MACRO%

    if ERRORLEVEL 1 goto:PreBuildFail
    echo BSF file was generated successfully !
    if exist %WORKSPACE%\%FSP_PKG_NAME%\Include\FspUpd.h attrib -r %WORKSPACE%\%FSP_PKG_NAME%\Include\FspUpd.h
    if exist "%WORKSPACE%\%OUT_DIR%\%FSP_PKG_NAME%\%BD_TARGET%_%TOOL_CHAIN_TAG%\FV\FspUpd.h" (
      copy /y %WORKSPACE%\%OUT_DIR%\%FSP_PKG_NAME%\%BD_TARGET%_%TOOL_CHAIN_TAG%\FV\FspUpd.h %WORKSPACE%\%FSP_PKG_NAME%\Include\FspUpd.h
      )
    if exist %WORKSPACE%\%FSP_PKG_NAME%\Include\FsptUpd.h attrib -r %WORKSPACE%\%FSP_PKG_NAME%\Include\FsptUpd.h
    if exist "%WORKSPACE%\%OUT_DIR%\%FSP_PKG_NAME%\%BD_TARGET%_%TOOL_CHAIN_TAG%\FV\FsptUpd.h" (
      copy /y %WORKSPACE%\%OUT_DIR%\%FSP_PKG_NAME%\%BD_TARGET%_%TOOL_CHAIN_TAG%\FV\FsptUpd.h %WORKSPACE%\%FSP_PKG_NAME%\Include\FsptUpd.h
      )
    if exist %WORKSPACE%\%FSP_PKG_NAME%\Include\FspmUpd.h attrib -r %WORKSPACE%\%FSP_PKG_NAME%\Include\FspmUpd.h
    if exist "%WORKSPACE%\%OUT_DIR%\%FSP_PKG_NAME%\%BD_TARGET%_%TOOL_CHAIN_TAG%\FV\FspmUpd.h" (
      copy /y %WORKSPACE%\%OUT_DIR%\%FSP_PKG_NAME%\%BD_TARGET%_%TOOL_CHAIN_TAG%\FV\FspmUpd.h %WORKSPACE%\%FSP_PKG_NAME%\Include\FspmUpd.h
      )
    if exist %WORKSPACE%\%FSP_PKG_NAME%\Include\FspsUpd.h attrib -r %WORKSPACE%\%FSP_PKG_NAME%\Include\FspsUpd.h
    if exist "%WORKSPACE%\%OUT_DIR%\%FSP_PKG_NAME%\%BD_TARGET%_%TOOL_CHAIN_TAG%\FV\FspsUpd.h" (
      copy /y %WORKSPACE%\%OUT_DIR%\%FSP_PKG_NAME%\%BD_TARGET%_%TOOL_CHAIN_TAG%\FV\FspsUpd.h %WORKSPACE%\%FSP_PKG_NAME%\Include\FspsUpd.h
      )
)

:PreBuildRet
set %~1=0
echo End of PreBuild ...
echo.
goto:EOF

:PreBuildFail
del /q /f %OUT_DIR%\%FSP_PKG_NAME%\%BD_TARGET%_%TOOL_CHAIN_TAG%\FV\FspUpd.h
del /q /f %OUT_DIR%\%FSP_PKG_NAME%\%BD_TARGET%_%TOOL_CHAIN_TAG%\FV\FsptUpd.h
del /q /f %OUT_DIR%\%FSP_PKG_NAME%\%BD_TARGET%_%TOOL_CHAIN_TAG%\FV\FspmUpd.h
del /q /f %OUT_DIR%\%FSP_PKG_NAME%\%BD_TARGET%_%TOOL_CHAIN_TAG%\FV\FspsUpd.h
echo.
(goto) 2>nul & endlocal & exit /b 1
goto:EOF

:PostBuild
echo Start of PostBuild ...

echo Patch FSP-T Image ...
python %WORKSPACE%\IntelFsp2Pkg\Tools\PatchFv.py ^
     %WORKSPACE%\%OUT_DIR%\%FSP_PKG_NAME%\%BD_TARGET%_%TOOL_CHAIN_TAG%\FV ^
     FSP-T:KBLFSP  ^
     "0x0000,            _BASE_FSP-T_,                                                                                       @Temporary Base" ^
     "<[0x0000]>+0x00AC, [<[0x0000]>+0x0020],                                                                                @FSP-T Size" ^
     "<[0x0000]>+0x00B0, [0x0000],                                                                                           @FSP-T Base" ^
     "<[0x0000]>+0x00B4, ([<[0x0000]>+0x00B4] & 0xFFFFFFFF) | 0x0001,                                                        @FSP-T Image Attribute" ^
     "<[0x0000]>+0x00B6, ([<[0x0000]>+0x00B6] & 0xFFFF0FFC) | 0x1000 | %FSP_BUILD_TYPE% | %FSP_RELEASE_TYPE%,                @FSP-T Component Attribute" ^
     "<[0x0000]>+0x00B8, 70BCF6A5-FFB1-47D8-B1AE-EFE5508E23EA:0x1C - <[0x0000]>,                                             @FSP-T CFG Offset" ^
     "<[0x0000]>+0x00BC, [70BCF6A5-FFB1-47D8-B1AE-EFE5508E23EA:0x14] & 0xFFFFFF - 0x001C,                                    @FSP-T CFG Size" ^
     "<[0x0000]>+0x00C4, FspSecCoreT:_TempRamInitApi - [0x0000],                                                             @TempRamInit API" ^
     "0x0000,            0x00000000,                                                                                         @Restore the value" ^
     "FspSecCoreT:_FspInfoHeaderRelativeOff, FspSecCoreT:_AsmGetFspInfoHeader - {912740BE-2284-4734-B971-84B027353F0C:0x1C}, @FSP-T Header Offset"
if ERRORLEVEL 1 goto:PreBuildFail

echo Patch FSP-M Image ...
python %WORKSPACE%\IntelFsp2Pkg\Tools\PatchFv.py ^
     %WORKSPACE%\%OUT_DIR%\%FSP_PKG_NAME%\%BD_TARGET%_%TOOL_CHAIN_TAG%\FV ^
     FSP-M:KBLFSP  ^
     "0x0000,            _BASE_FSP-M_,                                                                                       @Temporary Base" ^
     "<[0x0000]>+0x00AC, [<[0x0000]>+0x0020],                                                                                @FSP-M Size" ^
     "<[0x0000]>+0x00B0, [0x0000],                                                                                           @FSP-M Base" ^
     "<[0x0000]>+0x00B4, ([<[0x0000]>+0x00B4] & 0xFFFFFFFF) | 0x0001,                                                        @FSP-M Image Attribute" ^
     "<[0x0000]>+0x00B6, ([<[0x0000]>+0x00B6] & 0xFFFF0FFC) | 0x2000 | %FSP_BUILD_TYPE% | %FSP_RELEASE_TYPE%,                @FSP-M Component Attribute" ^
     "<[0x0000]>+0x00B8, D5B86AEA-6AF7-40D4-8014-982301BC3D89:0x1C - <[0x0000]>,                                             @FSP-M CFG Offset" ^
     "<[0x0000]>+0x00BC, [D5B86AEA-6AF7-40D4-8014-982301BC3D89:0x14] & 0xFFFFFF - 0x001C,                                    @FSP-M CFG Size" ^
     "<[0x0000]>+0x00D0, FspSecCoreM:_FspMemoryInitApi - [0x0000],                                                           @MemoryInitApi API" ^
     "<[0x0000]>+0x00D4, FspSecCoreM:_TempRamExitApi - [0x0000],                                                             @TempRamExit API" ^
     "FspSecCoreM:_FspPeiCoreEntryOff, PeiCore:__ModuleEntryPoint - [0x0000],                                                @PeiCore Entry" ^
     "0x0000,            0x00000000,                                                                                         @Restore the value" ^
     "FspSecCoreM:_FspInfoHeaderRelativeOff, FspSecCoreM:_AsmGetFspInfoHeader - {912740BE-2284-4734-B971-84B027353F0C:0x1C}, @FSP-M Header Offset"
if ERRORLEVEL 1 goto:PreBuildFail


echo Patch FSP-S Image ...
python %WORKSPACE%\IntelFsp2Pkg\Tools\PatchFv.py ^
     %WORKSPACE%\%OUT_DIR%\%FSP_PKG_NAME%\%BD_TARGET%_%TOOL_CHAIN_TAG%\FV ^
     FSP-S:KBLFSP  ^
     "0x0000,            _BASE_FSP-S_,                                                                                       @Temporary Base" ^
     "<[0x0000]>+0x00AC, [<[0x0000]>+0x0020],                                                                                @FSP-S Size" ^
     "<[0x0000]>+0x00B0, [0x0000],                                                                                           @FSP-S Base" ^
     "<[0x0000]>+0x00B4, ([<[0x0000]>+0x00B4] & 0xFFFFFFFF) | 0x0001,                                                        @FSP-S Image Attribute" ^
     "<[0x0000]>+0x00B6, ([<[0x0000]>+0x00B6] & 0xFFFF0FFC) | 0x3000 | %FSP_BUILD_TYPE% | %FSP_RELEASE_TYPE%,                @FSP-S Component Attribute" ^
     "<[0x0000]>+0x00B8, E3CD9B18-998C-4F76-B65E-98B154E5446F:0x1C - <[0x0000]>,                                             @FSP-S CFG Offset" ^
     "<[0x0000]>+0x00BC, [E3CD9B18-998C-4F76-B65E-98B154E5446F:0x14] & 0xFFFFFF - 0x001C,                                    @FSP-S CFG Size" ^
     "<[0x0000]>+0x00D8, FspSecCoreS:_FspSiliconInitApi - [0x0000],                                                          @SiliconInit API" ^
     "<[0x0000]>+0x00CC, FspSecCoreS:_NotifyPhaseApi - [0x0000],                                                             @NotifyPhase API" ^
     "0x0000,            0x00000000,                                                                                         @Restore the value" ^
     "FspSecCoreS:_FspInfoHeaderRelativeOff, FspSecCoreS:_AsmGetFspInfoHeader - {912740BE-2284-4734-B971-84B027353F0C:0x1C}, @FSP-S Header Offset"
if ERRORLEVEL 1 goto:PreBuildFail

@REM Copy FSP binary to KabylakeFspBinPkg
echo on
if exist %WORKSPACE%\%FSP_BIN_PKG_NAME%\Fsp.bsf attrib -r %WORKSPACE\%FSP_BIN_PKG_NAME%\Fsp.bsf
if exist %WORKSPACE%\%FSP_BIN_PKG_NAME%\Fsp.fd attrib -r %WORKSPACE%\%FSP_BIN_PKG_NAME%\Fsp.fd
copy /y %WORKSPACE%\%OUT_DIR%\%FSP_PKG_NAME%\%BD_TARGET%_%TOOL_CHAIN_TAG%\FV\KBLFSP.fd %WORKSPACE%\%FSP_BIN_PKG_NAME%\Fsp.fd
if not exist %WORKSPACE%\%FSP_BIN_PKG_NAME%\Include mkdir %WORKSPACE%\%FSP_BIN_PKG_NAME%\Include
if exist %WORKSPACE%\%FSP_BIN_PKG_NAME%\Include\FspUpd.h attrib -r %WORKSPACE%\%FSP_BIN_PKG_NAME%\Include\FspUpd.h
if exist "%WORKSPACE%\%OUT_DIR%\%FSP_PKG_NAME%\%BD_TARGET%_%TOOL_CHAIN_TAG%\FV\FspUpd.h" (
  copy /y %WORKSPACE%\%OUT_DIR%\%FSP_PKG_NAME%\%BD_TARGET%_%TOOL_CHAIN_TAG%\FV\FspUpd.h %WORKSPACE%\%FSP_BIN_PKG_NAME%\Include\
  )
if exist %WORKSPACE%\%FSP_BIN_PKG_NAME%\Include\FsptUpd.h attrib -r %WORKSPACE%\%FSP_BIN_PKG_NAME%\Include\FsptUpd.h
if exist "%WORKSPACE%\%OUT_DIR%\%FSP_PKG_NAME%\%BD_TARGET%_%TOOL_CHAIN_TAG%\FV\FsptUpd.h" (
  copy /y %WORKSPACE%\%OUT_DIR%\%FSP_PKG_NAME%\%BD_TARGET%_%TOOL_CHAIN_TAG%\FV\FsptUpd.h %WORKSPACE%\%FSP_BIN_PKG_NAME%\Include\
  )
if exist %WORKSPACE%\%FSP_BIN_PKG_NAME%\Include\FspmUpd.h attrib -r %WORKSPACE%\%FSP_BIN_PKG_NAME%\Include\FspmUpd.h
if exist "%WORKSPACE%\%OUT_DIR%\%FSP_PKG_NAME%\%BD_TARGET%_%TOOL_CHAIN_TAG%\FV\FspmUpd.h" (
  copy /y %WORKSPACE%\%OUT_DIR%\%FSP_PKG_NAME%\%BD_TARGET%_%TOOL_CHAIN_TAG%\FV\FspmUpd.h %WORKSPACE%\%FSP_BIN_PKG_NAME%\Include\
  )
if exist %WORKSPACE%\%FSP_BIN_PKG_NAME%\Include\FspsUpd.h attrib -r %WORKSPACE%\%FSP_BIN_PKG_NAME%\Include\FspsUpd.h
if exist "%WORKSPACE%\%OUT_DIR%\%FSP_PKG_NAME%\%BD_TARGET%_%TOOL_CHAIN_TAG%\FV\FspsUpd.h" (
  copy /y %WORKSPACE%\%OUT_DIR%\%FSP_PKG_NAME%\%BD_TARGET%_%TOOL_CHAIN_TAG%\FV\FspsUpd.h %WORKSPACE%\%FSP_BIN_PKG_NAME%\Include\
  )
if exist %WORKSPACE%\%FSP_BIN_PKG_NAME%\Include\MemInfoHob.h attrib -r %WORKSPACE%\%FSP_BIN_PKG_NAME%\Include\MemInfoHob.h
if exist "%WORKSPACE%\KabylakeSiliconPkg\SystemAgent\Include\MemInfoHob.h" (
  copy /y %WORKSPACE%\KabylakeSiliconPkg\SystemAgent\Include\MemInfoHob.h %WORKSPACE%\%FSP_BIN_PKG_NAME%\Include\
  )
if exist %WORKSPACE%\%FSP_BIN_PKG_NAME%\Include\SmbiosCacheInfoHob.h attrib -r %WORKSPACE%\%FSP_BIN_PKG_NAME%\Include\SmbiosCacheInfoHob.h
if exist "%WORKSPACE%\%CLIENT_SILICON_PKG_NAME%\Include\SmbiosCacheInfoHob.h" (
  copy /y %WORKSPACE%\%CLIENT_SILICON_PKG_NAME%\Include\SmbiosCacheInfoHob.h %WORKSPACE%\%FSP_BIN_PKG_NAME%\Include\
  )
if exist %WORKSPACE%\%FSP_BIN_PKG_NAME%\Include\SmbiosProcessorInfoHob.h attrib -r %WORKSPACE%\%FSP_BIN_PKG_NAME%\Include\SmbiosProcessorInfoHob.h
if exist "%WORKSPACE%\%CLIENT_SILICON_PKG_NAME%\Include\SmbiosProcessorInfoHob.h" (
  copy /y %WORKSPACE%\%CLIENT_SILICON_PKG_NAME%\Include\SmbiosProcessorInfoHob.h %WORKSPACE%\%FSP_BIN_PKG_NAME%\Include\
  )
if exist %WORKSPACE%\%FSP_BIN_PKG_NAME%\Include\ConfigBlock\CpuConfigFspData.h attrib -r %WORKSPACE%\%FSP_BIN_PKG_NAME%\Include\ConfigBlock\CpuConfigFspData.h
if not exist %WORKSPACE%\%FSP_BIN_PKG_NAME%\Include\ConfigBlock mkdir %WORKSPACE%\%FSP_BIN_PKG_NAME%\Include\ConfigBlock
if exist "%WORKSPACE%\KabylakeSiliconPkg\Cpu\Include\ConfigBlock\CpuConfigFspData.h" (
  copy /y %WORKSPACE%\KabylakeSiliconPkg\Cpu\Include\ConfigBlock\CpuConfigFspData.h %WORKSPACE%\%FSP_BIN_PKG_NAME%\Include\ConfigBlock\
  )
echo off

echo Patch is DONE

goto:EOF

:End
echo.
