@REM Copyright (c) 2016, Intel Corporation. All rights reserved.
@REM This software and associated documentation (if any) is furnished
@REM under a license and may only be used or copied in accordance
@REM with the terms of the license. Except as permitted by such
@REM license, no part of this software or documentation may be
@REM reproduced, stored in a retrieval system, or transmitted in any
@REM form or by any means without the express written consent of
@REM Intel Corporation.

@echo off
setlocal enableextensions enabledelayedexpansion

@REM
@REM Remove shifted arguments by constructing BUILD_ARGS
@REM
set BUILD_ARGS=
set ROOT_DIR=%~dp0\..\
:CONSTRUCT_BUILD_ARGS_LOOP
  if "%~1"=="" goto CONSTRUCT_BUILD_ARGS_CONTINUE
  if "%~1" == "/?" goto USAGE
  if "%~1" == "/h" goto USAGE
  set BUILD_ARGS=%BUILD_ARGS% %1
  shift
  goto CONSTRUCT_BUILD_ARGS_LOOP
:CONSTRUCT_BUILD_ARGS_CONTINUE
call :BUILD
if not %ERRORLEVEL% == 0 goto DIE

goto END

@REM
@REM Pre-Build Section
@REM
:PREBUILD
  @REM Backward Compatibility Start
  set PLATFORM_DECOUPLED_FSP_BUILD=TRUE
  @REM Backward Compatibility End
  call %ROOT_DIR%\BuildFsp.cmd
  goto END

@REM
@REM Build Section
@REM
:BUILD
  @REM
  @REM Perform Pre-Build
  @REM
  pushd %ROOT_DIR%
  @echo Start Pre-Build procedure
  call :PREBUILD
  if not %ERRORLEVEL% == 0 goto DIE

  @REM
  @REM Perform Build
  @REM
  @echo Start Build procedure
  call %~dp0\BuildFv.cmd %BUILD_ARGS%
  if not %ERRORLEVEL% == 0 goto DIE

  @REM
  @REM Perform Post-Build
  @REM
  @echo Start Post-Build procedure
  call :POSTBUILD
  if not %ERRORLEVEL% == 0 goto DIE

  @REM
  @REM Done
  @REM
  popd
  goto END

@REM
@REM Post-Build Section
@REM
:POSTBUILD
  if /I "%1"=="/clean" goto END

  @REM
  @REM Copy Fsp images to RomImages\Fsp
  @REM
  @echo Copy Fsp images to RomImages\Fsp
  if not exist %WORKSPACE%\RomImages\Fsp @mkdir %WORKSPACE%\RomImages\Fsp
  if not exist %WORKSPACE%\RomImages\Fsp\Include @mkdir %WORKSPACE%\RomImages\Fsp\Include
  copy /y /b %WORKSPACE%\%OUT_DIR%\%FSP_PKG_NAME%\%BD_TARGET%_%TOOL_CHAIN_TAG%\FV\KBLFSP.fd %WORKSPACE%\RomImages\Fsp\FSP.fd
  @REM
  @REM Do binary copy for bsf file to avoid extra characters copy, which causes issue with BCT tool
  @REM
  copy /y /b %WORKSPACE%\%FSP_BIN_PKG_NAME%\*.bsf %WORKSPACE%\RomImages\Fsp\FSP.bsf
  copy /y %WORKSPACE%\%FSP_BIN_PKG_NAME%\Docs\*.chm %WORKSPACE%\RomImages\Fsp\
  copy /y %WORKSPACE%\%FSP_BIN_PKG_NAME%\Docs\*.pdf %WORKSPACE%\RomImages\Fsp\

  goto END

@REM
@REM Print usage and exit
@REM
:USAGE
  echo Usage: BuildFsp [/h^|/?^|/r^|/d^|/mr^|/md^|/clean]
  echo                 /h         To show usage.
  echo                 [/?]       To show usage.
  echo                 /r         To perform Release build.
  echo                 /d         To perform Debug build.
  echo                 /mr        To perform Release mini BIOS build.
  echo                 /md        To perform Release mini BIOS build.
  echo                 /clean     To remove Build and Conf directories.

  goto END

@REM
@REM Exit returning a failure error code
@REM
:DIE
  exit /B 1

@REM
@REM Exit returning a success error code
@REM
:END
  exit /B 0
