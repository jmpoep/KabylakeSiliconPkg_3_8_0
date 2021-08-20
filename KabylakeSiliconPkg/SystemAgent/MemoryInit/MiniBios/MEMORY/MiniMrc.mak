# @file
#  Makefile for Memory Reference Code (MRC) mini-BIOS.

#@copyright
#  Copyright (c) 2004 - 2016 Intel Corporation. All rights reserved.
#  This software and associated documentation (if any) is furnished
#  under a license and may only be used or copied in accordance
#  with the terms of the license. Except as permitted by such
#  license, no part of this software or documentation may be
#  reproduced, stored in a retrieval system, or transmitted in any
#  form or by any means without the express written consent of
#  Intel Corporation.

#  This file contains an 'Intel Peripheral Driver' and uniquely
#  identified as "Intel Reference Module" and is
#  licensed for Intel CPUs and chipsets under the terms of your
#  license agreement with Intel or your vendor.  This file may
#  be modified by the user, subject to additional terms of the
#  license agreement.

#--------------------------------------------------------------------
# A dummy pseudo-target just so it is the first in the file.
# Now, NMAKE is the same as NMAKE ALL. This is just for developer
# convenience, such that all source and object files appear at the
# top of this file for easy modification.
#--------------------------------------------------------------------
DUMMY: ALL


#--------------------------------------------------------------------
# Memory Reference Code Object Files.
#--------------------------------------------------------------------
MRCLINK32OBJS = \
        $(OUT32DIR)\MemoryAddressEncodeDecodeLib.obj \
        $(OUT32DIR)\MrcBdat.obj \
        $(OUT32DIR)\MrcDebugPrint.obj \
        $(OUT32DIR)\MrcGeneral.obj \
        $(OUT32DIR)\MrcInterpreter.obj \
        $(OUT32DIR)\MrcMemoryScrub.obj \
        $(OUT32DIR)\MrcSaveRestore.obj \
!IF "$(SSA_SUPPORT)" == "1"
        $(OUT32DIR)\BiosSsaCommonConfig.obj \
        $(OUT32DIR)\BiosSsaMemoryClientConfig.obj \
        $(OUT32DIR)\BiosSsaMemoryConfig.obj \
        $(OUT32DIR)\BiosSsaResultsConfig.obj \
        $(OUT32DIR)\MrcSsaCommon.obj \
        $(OUT32DIR)\MrcSsaInitialize.obj \
        $(OUT32DIR)\MrcSsaServices.obj \
!ENDIF
!IF "$(MRC_DCTT_SUPPORT)" == "1"
        $(OUT32DIR)\DcttAnalyzer.obj \
        $(OUT32DIR)\DcttCpgcFunctions.obj \
        $(OUT32DIR)\DcttHelpers.obj \
        $(OUT32DIR)\DcttInterpreter.obj \
        $(OUT32DIR)\DcttLexer.obj \
        $(OUT32DIR)\DcttMain.obj \
        $(OUT32DIR)\DcttMarginFunctions.obj \
        $(OUT32DIR)\DcttMcFunctions.obj \
        $(OUT32DIR)\DcttMString.obj \
        $(OUT32DIR)\DcttParametersCheck.obj \
        $(OUT32DIR)\DcttParser.obj \
        $(OUT32DIR)\DcttPauseRefresh.obj \
        $(OUT32DIR)\DcttPermutations.obj \
        $(OUT32DIR)\DcttPrintHelpers.obj \
        $(OUT32DIR)\DcttSetContainer.obj \
        $(OUT32DIR)\DcttSwizzleFunctions.obj \
        $(OUT32DIR)\DcttSymbol.obj \
        $(OUT32DIR)\DcttSysRestore.obj \
        $(OUT32DIR)\MrcDimmCellTest.obj \
!ENDIF
!IF "$(SSA_LOADER_ENABLE)" == "1"
        $(OUT32DIR)\String.obj \
        $(OUT32DIR)\ScratchPadReg.obj \
        $(OUT32DIR)\PeLoader.obj \
        $(OUT32DIR)\EvItpDownloadAgent.obj \
        $(OUT32DIR)\MrcMiniBiosLoaderEntryPoint.obj \
!ENDIF
        $(OUT32DIR)\MrcStartMemoryConfiguration.obj \
        $(OUT32DIR)\MrcHalMiddleLevel.obj \
        $(OUT32DIR)\MrcHalRegisterAccess.obj \
        $(OUT32DIR)\MrcAddressDecodeConfiguration.obj \
        $(OUT32DIR)\MrcPowerModes.obj \
        $(OUT32DIR)\MrcRefreshConfiguration.obj \
        $(OUT32DIR)\MrcSchedulerParameters.obj \
        $(OUT32DIR)\MrcTimingConfiguration.obj \
        $(OUT32DIR)\MrcReadDqDqs.obj \
        $(OUT32DIR)\MrcReadReceiveEnable.obj \
        $(OUT32DIR)\MrcCommandTraining.obj \
        $(OUT32DIR)\MrcCommon.obj \
        $(OUT32DIR)\MrcCrosser.obj \
        $(OUT32DIR)\MrcDdr3.obj \
        $(OUT32DIR)\MrcIoControl.obj \
        $(OUT32DIR)\MrcMalloc.obj \
        $(OUT32DIR)\MrcMcConfiguration.obj \
        $(OUT32DIR)\MrcMemoryMap.obj \
        $(OUT32DIR)\MrcReset.obj \
        $(OUT32DIR)\MrcWriteDqDqs.obj \
        $(OUT32DIR)\MrcWriteLeveling.obj\
        $(OUT32DIR)\MrcRegisterCache.obj \
        $(OUT32DIR)\MrcDdrIoDataOffsets.obj

SPDLINK32OBJS = \
        $(OUT32DIR)\MrcSpdProcessing.obj

LINK32OBJS = \
        $(OUT32DIR)\MrcOemPlatform.obj \
        $(OUT32DIR)\MrcSetup.obj \
        $(OUT32DIR)\Io.obj \
        $(OUT32DIR)\MemoryUtils.obj \
        $(OUT32DIR)\Smb.obj \
        $(OUT32DIR)\uart16550.obj

!IF "$(SSA_LOADER_ENABLE)" == "1"
SSA_LOADER_FOLDER               = ..\..\Library\Private\PeiEvLoaderLib
!ENDIF

#--------------------------------------------------------------------
# Some basic definitions.
#--------------------------------------------------------------------
ROOTPATH                        = ..
MRC_ROOTPATH                    = ..\..\Library\Private\PeiMemoryInitLib
MRC_ROOT_INCLUDE                = ..\..\Include
MRC_COMMON                      = ..\Common
MRC_MAIN                        = $(MRC_ROOTPATH)\Source
MRC_ADDR_DECODE                 = ..\..\Library\PeiDxeSmmMemoryAddressEncodeDecodeLib
MRC_ADDR_DECODE_INC             = $(MRC_ROOT_INCLUDE)\Library
MRC_API                         = $(MRC_MAIN)\Api
MRC_HAL                         = $(MRC_MAIN)\Hal
MRC_INCLUDES                    = $(MRC_MAIN)\Include
MRC_INCREGS                     = $(MRC_MAIN)\Include\MrcRegisters
MRC_MC_INIT                     = $(MRC_MAIN)\McConfiguration
MRC_READ_TRAINING               = $(MRC_MAIN)\ReadTraining
MRC_SERVICES                    = $(MRC_MAIN)\Services
MRC_SPD_PROCESSING              = $(MRC_MAIN)\SpdProcessing
MRC_SSA                         = $(MRC_MAIN)\Ssa
MRC_SSA_INCLUDES                = $(MRC_MAIN)\Ssa\Include
MRC_WRITE_TRAINING              = $(MRC_MAIN)\WriteTraining
MRC_DIMM_CELL_TEST              = $(MRC_MAIN)\DimmCellTest
MRC_DIMM_CELL_TEST_INC          = $(MRC_DIMM_CELL_TEST)\Include
MRC_DIMM_CELL_TEST_SRC          = $(MRC_DIMM_CELL_TEST)\Source

#--------------------------------------------------------------------
# Directory Declarations
#--------------------------------------------------------------------
MRCSRC32DIR                     = $(ROOTPATH)\MEMORY
OUT32DIR                        = $(ROOTPATH)\OUT32
CPUSRC32DIR                     = $(ROOTPATH)\CPU\SRC32

#--------------------------------------------------------------------
# Inference Rules
#--------------------------------------------------------------------

{$(MRCSRC32DIR)}.c{$(OUT32DIR)}.obj::
    $(C) $(CFLAGS) $<

{$(MRC_ROOTPATH)}.c{$(OUT32DIR)}.obj::
    $(C) $(CFLAGS) $<

{$(MRC_MC_INIT)}.c{$(OUT32DIR)}.obj::
    $(C) $(CFLAGS) $<

{$(MRC_READ_TRAINING)}.c{$(OUT32DIR)}.obj::
    $(C) $(CFLAGS) $<

{$(MRC_WRITE_TRAINING)}.c{$(OUT32DIR)}.obj::
    $(C) $(CFLAGS) $<

{$(MRC_SPD_PROCESSING)}.c{$(OUT32DIR)}.obj::
    $(C) $(CFLAGS) $<

{$(MRC_COMMON)}.c{$(OUT32DIR)}.obj::
    $(C) $(CFLAGS) $<

{$(MRC_API)}.c{$(OUT32DIR)}.obj::
    $(C) $(CFLAGS) $<

{$(MRC_HAL)}.c{$(OUT32DIR)}.obj::
    $(C) $(CFLAGS) $<

{$(MRC_ADDR_DECODE)}.c{$(OUT32DIR)}.obj::
    $(C) $(CFLAGS) $<

{$(MRC_SERVICES)}.c{$(OUT32DIR)}.obj::
    $(C) $(CFLAGS) $<

!IF "$(MRC_DCTT_SUPPORT)" == "1"
{$(MRC_DIMM_CELL_TEST)}.c{$(OUT32DIR)}.obj::
    $(C) $(CFLAGS) $<

{$(MRC_DIMM_CELL_TEST_SRC)}.c{$(OUT32DIR)}.obj::
    $(C) $(CFLAGS) $<
!ENDIF

!IF "$(SSA_SUPPORT)" == "1"
{$(MRC_SSA)}.c{$(OUT32DIR)}.obj::
    $(C) $(CFLAGS) $<
!ENDIF

!IF "$(SSA_LOADER_ENABLE)" == "1"
{$(SSA_LOADER_FOLDER)}.c{$(OUT32DIR)}.obj::
    $(C) $(CFLAGS) $<
!ENDIF

#--------------------------------------------------------------------
# Compiler and Linker Flags
#--------------------------------------------------------------------
C = cl

CFLAGS = /Zp1 /Wall /WX /EHsc /GF /Gy /Gs131072 /c /Zi /MP /X /GS- /nologo /FAsc /wd4214 /wd4711

#
# Debug build:   compiler optimizations disabled
# Release build: compiler optimizations enabled
#
!IF "$(RELEASE)" == "1"
CFLAGS = $(CFLAGS) /O1ib2s
!ELSE
CFLAGS = $(CFLAGS) /Od
!ENDIF

CFLAGS = $(CFLAGS) /Fd$(OUT32DIR)\\ /Fo$(OUT32DIR)\\
CFLAGS = $(CFLAGS) /Fa$(OUT32DIR)\ASM\\ -I$(CPUSRC32DIR) -I$(MRCSRC32DIR) -I$(MRC_COMMON)
CFLAGS = $(CFLAGS) -I$(MRC_ROOT_INCLUDE) -I$(MRC_ADDR_DECODE) -I$(MRC_ADDR_DECODE_INC) -I$(MRC_API) -I$(MRC_HAL) -I$(MRC_INCLUDES) -I$(MRC_INCREGS) -I$(MRC_MC_INIT) -I$(MRC_READ_TRAINING) -I$(MRC_SERVICES) -I$(MRC_SPD_PROCESSING) -I$(MRC_SSA) -I$(MRC_SSA_INCLUDES) -I$(MRC_WRITE_TRAINING)
CFLAGS = $(CFLAGS) -I$(MRC_ROOTPATH)
CFLAGS = $(CFLAGS) /DMRC_MINIBIOS_BUILD

!IF "$(MRC_FLAG_DEBUG_MSG)" == "0"
CFLAGS = $(CFLAGS) /DMDEPKG_NDEBUG
!ENDIF

!IF "$(MRC_FLAG_BDAT_SUPPORT)" == "1"
CFLAGS = $(CFLAGS) /DBDAT_SUPPORT
!ENDIF

!IF "$(MEMORY_DOWN_SUPPORT)" == "1"
CFLAGS = $(CFLAGS) /DMEMORY_DOWN_SUPPORT=1
!ENDIF

!IF "$(SSA_SUPPORT)" == "1"
CFLAGS = $(CFLAGS) /DSSA_FLAG=1 /DSSA_CLIENT_FLAG=1
!ENDIF

!IF "$(SSA_LOADER_ENABLE)" == "1"
CFLAGS = $(CFLAGS) -I$(SSA_LOADER_FOLDER) /DSSA_LOADER_FLAG=1
!ENDIF

!IF "$(MRC_DCTT_SUPPORT)" == "1"
CFLAGS = $(CFLAGS) -I$(MRC_DIMM_CELL_TEST) -I$(MRC_DIMM_CELL_TEST_INC) /DDCTT_FLAG=1
!ENDIF

#--------------------------------------------------------------------
# Object File Dependencies List
#--------------------------------------------------------------------


#--------------------------------------------------------------------
# Library Flags
#--------------------------------------------------------------------
LIB = lib
LIBFLAGS =

#--------------------------------------------------------------------
# All the targets...
#--------------------------------------------------------------------
ALL:    TARGETDIRECTORIES $(LINK32OBJS) $(MRCLINK32OBJS) $(SPDLINK32OBJS)
        LIB $(LIBFLAGS) /OUT:$(OUT32DIR)\mrc.lib $(MRCLINK32OBJS)
        LIB $(LIBFLAGS) /OUT:$(OUT32DIR)\spd.lib $(SPDLINK32OBJS)

TARGETDIRECTORIES:
        @echo Creating Target Directories...
        @if not exist $(OUT32DIR) mkdir $(OUT32DIR)
        @if not exist $(OUT32DIR)\ASM mkdir $(OUT32DIR)\ASM

DEBUGSOURCE:
        @echo Copying $(MRCSRC32DIR) to $(OUT32DIR)
        @copy $(MRCSRC32DIR) $(OUT32DIR) > nul
        @echo MRC compilation end

CLEAN: 
        -@echo  Removing directory $(OUT32DIR)
        -@if exist $(OUT32DIR) rd $(OUT32DIR) /S /Q

        -@echo Removing .obj, .pdb and .idb files in the $(MRCSRC32DIR) directory...
        -@if exist vc*.pdb               erase vc*.pdb
        -@if exist vc*.idb               erase vc*.idb
        -@if exist $(MRCSRC32DIR)\*.obj  erase $(MRCSRC32DIR)\*.obj
