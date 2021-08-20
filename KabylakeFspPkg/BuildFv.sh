## @file
# @copyright
#  Copyright (c) 2008 - 2019, Intel Corporation All rights reserved
#  This software and associated documentation (if any) is furnished
#  under a license and may only be used or copied in accordance
#  with the terms of the license. Except as permitted by such
#  license, no part of this software or documentation may be
#  reproduced, stored in a retrieval system, or transmitted in any
#  form or by any means without the express written consent of
#  Intel Corporation.
#  This file contains an 'Intel Peripheral Driver' and is
#  licensed for Intel CPUs and chipsets under the terms of your
#  license agreement with Intel or your vendor.  This file may
#  be modified by the user, subject to additional terms of the
#  license agreement
##
#!/bin/sh



FSP_PKG_NAME=KabylakeFspPkg
FSP_PKG_CONF_NAME=KabylakeFspPkgConfig
FSP_PKG_EXT_CONF_NAME=KabylakeFspPkgExtConfig
FSP_BIN_PKG_NAME=KabylakeFspBinPkg
Edksetup=edksetup.sh
FSP_T_UPD_GUID=34686CA3-34F9-4901-B82A-BA630F0714C6
FSP_M_UPD_GUID=39A250DB-E465-4DD1-A2AC-E2BD3C0E2385
FSP_S_UPD_GUID=CAE3605B-5B34-4C85-B3D7-27D54273C40F
ErrorCode=0

function USAGE()
{
  echo
  echo  "$0 \[-h \| -? \| -r32 \| -tr32 \| -d32 \| -clean\]"
  echo
  return 1
}

function Clean(){
  echo Removing Build and Conf directories ...
  if [ -d Build ]
   then 
    rm -r Build
  fi
  if [ -d Conf ]
    then 
     rm  -r Conf
  fi
  if [ -f *.log ]
   then 
    rm *.log
  fi
  WORKSPACE=
  EDK_TOOLS_PATH=
  return 0
}


function  PreBuildFail(){
  if [ -f $OUT_DIR/$FSP_PKG_NAME/$BD_TARGET"_"$TOOL_CHAIN/FV/FspUpd.h ]
   then
    rm  $OUT_DIR/$FSP_PKG_NAME/$BD_TARGET"_"$TOOL_CHAIN/FV/FspUpd.h
  fi
  if [ -f $OUT_DIR/$FSP_PKG_NAME/$BD_TARGET"_"$TOOL_CHAIN/FV/FsptUpd.h ]
   then
    rm  $OUT_DIR/$FSP_PKG_NAME/$BD_TARGET"_"$TOOL_CHAIN/FV/FsptUpd.h
  fi
  if [ -f $OUT_DIR/$FSP_PKG_NAME/$BD_TARGET"_"$TOOL_CHAIN/FV/FspmUpd.h ]
   then
    rm  $OUT_DIR/$FSP_PKG_NAME/$BD_TARGET"_"$TOOL_CHAIN/FV/FspmUpd.h
  fi
  if [ -f $OUT_DIR/$FSP_PKG_NAME/$BD_TARGET"_"$TOOL_CHAIN/FV/FspsUpd.h ]
   then
    rm  $OUT_DIR/$FSP_PKG_NAME/$BD_TARGET"_"$TOOL_CHAIN/FV/FspsUpd.h
  fi
  #/q /f
  return 0
}

function PreBuildRet(){
  set $1=0
  echo End of PreBuild ...
  echo
  return 0
}


function CopyBin(){
 if [ -f $1/*.efi ]
  then 
   cp $1/*.efi   $2 
   #/D /U /Y > NUL
 fi
 if [ -f $1/*.inf ]
   then
     cp $1/*.inf   $2 
   #/D /U /Y > NUL
 fi
 if [ -f $1/*.depex ]
   then
    cp $1/*.depex $2 
   #/D /U /Y > NUL
 fi
}

function PreBuild(){

  cp KabylakeSiliconPkg/Pch/Include/GpioConfig.h $FSP_BIN_PKG_NAME/Include/GpioConfig.h

  cp KabylakeSiliconPkg/SystemAgent/Include/MemInfoHob.h $FSP_BIN_PKG_NAME/Include/MemInfoHob.h
  
  cp ClientSiliconPkg/Include/SmbiosCacheInfoHob.h $FSP_BIN_PKG_NAME/Include/SmbiosCacheInfoHob.h
  
  cp ClientSiliconPkg/Include/SmbiosProcessorInfoHob.h $FSP_BIN_PKG_NAME/Include/SmbiosProcessorInfoHob.h

  python $FSP_PKG_NAME/Override/IntelFsp2Pkg/Tools/GenCfgOpt.py UPDTXT \
     $FSP_PKG_NAME/$FSP_PKG_NAME.dsc \
     $OUT_DIR/$FSP_PKG_NAME/$BD_TARGET"_"$TOOL_CHAIN/FV \
     $BD_MACRO

  error=$?
  if [ $error -eq "256" ] 
   then
    echo  DSC is not changed, no need to recreate MAP and BIN file
  else
   if [ $error -eq "1" ]
    then
     echo Error in generating UPD TXT file
     return 1
   fi

  echo UPD TXT file was generated successfully !

  echo Generate VPD Header File ...
  rm  $OUT_DIR/$FSP_PKG_NAME/$BD_TARGET"_"$TOOL_CHAIN/FV/$FSP_T_UPD_GUID.bin \
            $OUT_DIR/$FSP_PKG_NAME/$BD_TARGET"_"$TOOL_CHAIN/FV/$FSP_T_UPD_GUID.map
 #2>nul

  rm  $OUT_DIR/$FSP_PKG_NAME/$BD_TARGET"_"$TOOL_CHAIN/FV/$FSP_M_UPD_GUID.bin \
            $OUT_DIR/$FSP_PKG_NAME/$BD_TARGET"_"$TOOL_CHAIN/FV/$FSP_M_UPD_GUID.map
 #2>nul

  rm  $OUT_DIR/$FSP_PKG_NAME/$BD_TARGET"_"$TOOL_CHAIN/FV/$FSP_S_UPD_GUID.bin \
            $OUT_DIR/$FSP_PKG_NAME/$BD_TARGET"_"$TOOL_CHAIN/FV/$FSP_S_UPD_GUID.map
 #2>nul

  BPDG -o $OUT_DIR/$FSP_PKG_NAME/$BD_TARGET"_"$TOOL_CHAIN/FV/$FSP_T_UPD_GUID.bin \
       -m $OUT_DIR/$FSP_PKG_NAME/$BD_TARGET"_"$TOOL_CHAIN/FV/$FSP_T_UPD_GUID.map \
        $OUT_DIR/$FSP_PKG_NAME/$BD_TARGET"_"$TOOL_CHAIN/FV/$FSP_T_UPD_GUID.txt
  
      if [ $? -eq "1" ] 
       then
       return 1
      fi

  BPDG -o $OUT_DIR/$FSP_PKG_NAME/$BD_TARGET"_"$TOOL_CHAIN/FV/$FSP_M_UPD_GUID.bin \
       -m $OUT_DIR/$FSP_PKG_NAME/$BD_TARGET"_"$TOOL_CHAIN/FV/$FSP_M_UPD_GUID.map \
        $OUT_DIR/$FSP_PKG_NAME/$BD_TARGET"_"$TOOL_CHAIN/FV/$FSP_M_UPD_GUID.txt
  
      if [ $? -eq "1" ] 
       then
       return 1
      fi

  BPDG -o $OUT_DIR/$FSP_PKG_NAME/$BD_TARGET"_"$TOOL_CHAIN/FV/$FSP_S_UPD_GUID.bin \
       -m $OUT_DIR/$FSP_PKG_NAME/$BD_TARGET"_"$TOOL_CHAIN/FV/$FSP_S_UPD_GUID.map \
        $OUT_DIR/$FSP_PKG_NAME/$BD_TARGET"_"$TOOL_CHAIN/FV/$FSP_S_UPD_GUID.txt
  
      if [ $? -eq "1" ] 
       then
       return 1
      fi
  fi

  python $FSP_PKG_NAME/Override/IntelFsp2Pkg/Tools/GenCfgOpt.py HEADER \
         $FSP_PKG_NAME/$FSP_PKG_NAME.dsc \
         $OUT_DIR/$FSP_PKG_NAME/$BD_TARGET"_"$TOOL_CHAIN/FV \
         $FSP_PKG_NAME/Include/BootLoaderPlatformData.h \
         $BD_MACRO

  error=$?
  if [ $error -eq "256" ]
   then 
    echo
    # No need to recreate header file
   else 
      if [ $error -eq "1" ] 
       then 
        echo Error in generating Header file
        return 1
      fi

    echo Vpd header file was generated successfully !

    echo Generate BSF File ...
    if [ ! -d $FSP_BIN_PKG_NAME ]
      then mkdir $FSP_BIN_PKG_NAME
    fi
    python $FSP_PKG_NAME/Override/IntelFsp2Pkg/Tools/GenCfgOpt.py GENBSF \
         $FSP_PKG_NAME/$FSP_PKG_NAME.dsc \
         $OUT_DIR/$FSP_PKG_NAME/$BD_TARGET"_"$TOOL_CHAIN/FV \
         $FSP_BIN_PKG_NAME/Fsp.bsf \
         $BD_MACRO

    if [ $? -eq "1" ] 
       then 
        echo Error in generating BSF file
        return 1
    fi
   
    echo BSF file was generated successfully !
    if [ -f $WORKSPACE/$FSP_PKG_NAME/Include/FspUpd.h ]
      then chmod +w $WORKSPACE/$FSP_PKG_NAME/Include/FspUpd.h
    fi
    if [ -f $WORKSPACE/$FSP_PKG_NAME/Include/FsptUpd.h ]
      then chmod +w $WORKSPACE/$FSP_PKG_NAME/Include/FsptUpd.h
    fi
    if [ -f $WORKSPACE/$FSP_PKG_NAME/Include/FspmUpd.h ]
      then chmod +w $WORKSPACE/$FSP_PKG_NAME/Include/FspmUpd.h
    fi
    if [ -f $WORKSPACE/$FSP_PKG_NAME/Include/FspsUpd.h ]
      then chmod +w $WORKSPACE/$FSP_PKG_NAME/Include/FspsUpd.h
    fi
    if [ -f $OUT_DIR/$FSP_PKG_NAME/$BD_TARGET"_"$TOOL_CHAIN/FV/FspUpd.h ]
     then
      cp $OUT_DIR/$FSP_PKG_NAME/$BD_TARGET"_"$TOOL_CHAIN/FV/FspUpd.h  $FSP_PKG_NAME/Include/FspUpd.h
    fi
    if [ -f $OUT_DIR/$FSP_PKG_NAME/$BD_TARGET"_"$TOOL_CHAIN/FV/FsptUpd.h ]
     then
      cp $OUT_DIR/$FSP_PKG_NAME/$BD_TARGET"_"$TOOL_CHAIN/FV/FsptUpd.h  $FSP_PKG_NAME/Include/FsptUpd.h
    fi
    if [ -f $OUT_DIR/$FSP_PKG_NAME/$BD_TARGET"_"$TOOL_CHAIN/FV/FspmUpd.h ]
     then
      cp $OUT_DIR/$FSP_PKG_NAME/$BD_TARGET"_"$TOOL_CHAIN/FV/FspmUpd.h  $FSP_PKG_NAME/Include/FspmUpd.h
    fi
    if [ -f $OUT_DIR/$FSP_PKG_NAME/$BD_TARGET"_"$TOOL_CHAIN/FV/FspsUpd.h ]
     then
      cp $OUT_DIR/$FSP_PKG_NAME/$BD_TARGET"_"$TOOL_CHAIN/FV/FspsUpd.h  $FSP_PKG_NAME/Include/FspsUpd.h
    fi
  fi
}


function PostBuild(){
  echo Start of PostBuild ...

  echo Patch FSP-T Image ...
   python IntelFsp2Pkg/Tools/PatchFv.py \
     $OUT_DIR/$FSP_PKG_NAME/$BD_TARGET"_"$TOOL_CHAIN/FV \
     FSP-T:KBLFSP \
     "0x0000,            _BASE_FSP-T_,                                                                                       @Temporary Base" \
     "<[0x0000]>+0x00AC, [<[0x0000]>+0x0020],                                                                                @FSP-T Size" \
     "<[0x0000]>+0x00B0, [0x0000],                                                                                           @FSP-T Base" \
     "<[0x0000]>+0x00B4, ([<[0x0000]>+0x00B4] & 0xFFFFFFFF) | 0x0001,                                                        @FSP-T Image Attribute" \
     "<[0x0000]>+0x00B6, ([<[0x0000]>+0x00B6] & 0xFFFF0FFC) | 0x1000 | $FSP_BUILD_TYPE | $FSP_RELEASE_TYPE,                  @FSP-T Component Attribute" \
     "<[0x0000]>+0x00B8, 70BCF6A5-FFB1-47D8-B1AE-EFE5508E23EA:0x1C - <[0x0000]>,                                             @FSP-T CFG Offset" \
     "<[0x0000]>+0x00BC, [70BCF6A5-FFB1-47D8-B1AE-EFE5508E23EA:0x14] & 0xFFFFFF - 0x001C,                                    @FSP-T CFG Size" \
     "<[0x0000]>+0x00C4, FspSecCoreT:_TempRamInitApi - [0x0000],                                                             @TempRamInit API" \
     "0x0000,            0x00000000,                                                                                         @Restore the value" \
     "FspSecCoreT:_FspInfoHeaderRelativeOff, FspSecCoreT:_AsmGetFspInfoHeader - {912740BE-2284-4734-B971-84B027353F0C:0x1C}, @FSP-T Header Offset"

  echo Patch FSP-M Image ...
   python IntelFsp2Pkg/Tools/PatchFv.py \
     $OUT_DIR/$FSP_PKG_NAME/$BD_TARGET"_"$TOOL_CHAIN/FV \
     FSP-M:KBLFSP \
     "0x0000,            _BASE_FSP-M_,                                                                                       @Temporary Base" \
     "<[0x0000]>+0x00AC, [<[0x0000]>+0x0020],                                                                                @FSP-M Size" \
     "<[0x0000]>+0x00B0, [0x0000],                                                                                           @FSP-M Base" \
     "<[0x0000]>+0x00B4, ([<[0x0000]>+0x00B4] & 0xFFFFFFFF) | 0x0001,                                                        @FSP-M Image Attribute" \
     "<[0x0000]>+0x00B6, ([<[0x0000]>+0x00B6] & 0xFFFF0FFC) | 0x2000 | $FSP_BUILD_TYPE | $FSP_RELEASE_TYPE,                  @FSP-M Component Attribute" \
     "<[0x0000]>+0x00B8, D5B86AEA-6AF7-40D4-8014-982301BC3D89:0x1C - <[0x0000]>,                                             @FSP-M CFG Offset" \
     "<[0x0000]>+0x00BC, [D5B86AEA-6AF7-40D4-8014-982301BC3D89:0x14] & 0xFFFFFF - 0x001C,                                    @FSP-M CFG Size" \
     "<[0x0000]>+0x00D0, FspSecCoreM:_FspMemoryInitApi - [0x0000],                                                           @MemoryInitApi API" \
     "<[0x0000]>+0x00D4, FspSecCoreM:_TempRamExitApi - [0x0000],                                                             @TempRamExit API" \
     "FspSecCoreM:_FspPeiCoreEntryOff, PeiCore:__ModuleEntryPoint - [0x0000],                                                @PeiCore Entry" \
     "0x0000,            0x00000000,                                                                                         @Restore the value" \
     "FspSecCoreM:_FspInfoHeaderRelativeOff, FspSecCoreM:_AsmGetFspInfoHeader - {912740BE-2284-4734-B971-84B027353F0C:0x1C}, @FSP-M Header Offset"


  echo Patch FSP-S Image ...
   python IntelFsp2Pkg/Tools/PatchFv.py \
     $OUT_DIR/$FSP_PKG_NAME/$BD_TARGET"_"$TOOL_CHAIN/FV \
     FSP-S:KBLFSP \
     "0x0000,            _BASE_FSP-S_,                                                                                       @Temporary Base" \
     "<[0x0000]>+0x00AC, [<[0x0000]>+0x0020],                                                                                @FSP-S Size" \
     "<[0x0000]>+0x00B0, [0x0000],                                                                                           @FSP-S Base" \
     "<[0x0000]>+0x00B4, ([<[0x0000]>+0x00B4] & 0xFFFFFFFF) | 0x0001,                                                        @FSP-S Image Attribute" \
     "<[0x0000]>+0x00B6, ([<[0x0000]>+0x00B6] & 0xFFFF0FFC) | 0x3000 | $FSP_BUILD_TYPE | $FSP_RELEASE_TYPE,                  @FSP-S Component Attribute" \
     "<[0x0000]>+0x00B8, E3CD9B18-998C-4F76-B65E-98B154E5446F:0x1C - <[0x0000]>,                                             @FSP-S CFG Offset" \
     "<[0x0000]>+0x00BC, [E3CD9B18-998C-4F76-B65E-98B154E5446F:0x14] & 0xFFFFFF - 0x001C,                                    @FSP-S CFG Size" \
     "<[0x0000]>+0x00D8, FspSecCoreS:_FspSiliconInitApi - [0x0000],                                                          @SiliconInit API" \
     "<[0x0000]>+0x00CC, FspSecCoreS:_NotifyPhaseApi - [0x0000],                                                             @NotifyPhase API" \
     "0x0000,            0x00000000,                                                                                         @Restore the value" \
     "FspSecCoreS:_FspInfoHeaderRelativeOff, FspSecCoreS:_AsmGetFspInfoHeader - {912740BE-2284-4734-B971-84B027353F0C:0x1C}, @FSP-S Header Offset"

}

function  Build32(){

   make -C ./BaseTools/Source/C
   chmod +w $FSP_PKG_NAME/$FSP_PKG_NAME.dsc
   OverrideBaseTools $* # ROYAL_PARK_OVERRIDE - RPCO-0057
   gcc -v
   build -m $FSP_PKG_NAME/FspHeader/FspHeader.inf $BD_ARGS -DCFG_PREBUILD
   if [ $? -ne 0 ]
   then 
     exit 1
   fi
 
   PreBuild $*

   if [ $? -eq 1 ]
   then
     exit 1 
   fi

   build $BD_ARGS
   if [ $? -ne 0 ]
   then 
     exit 1
   fi
   PostBuild
   if [ $? -ne 0 ]
   then 
     exit 1
   fi
}

function ReleaseTypeTest32(){
  BD_TARGET=RELEASE
  BD_MACRO="-D CFG_OUTDIR="$OUT_DIR
  DSCFILE="-p "$FSP_PKG_NAME/$FSP_PKG_NAME.dsc #" -y ReleaseBuild32Log.log"
  BD_ARGS=$DSCFILE" -b RELEASE "$BD_MACRO" -a IA32 -n 1 -t "$TOOL_CHAIN
  FSP_BUILD_TYPE=0x0001
  FSP_RELEASE_TYPE=0x0000
  Build32 $*
}

function ReleaseBuild32(){
  BD_TARGET=RELEASE
  BD_MACRO="-D CFG_OUTDIR="$OUT_DIR
  DSCFILE="-p "$FSP_PKG_NAME/$FSP_PKG_NAME.dsc #" -y ReleaseBuild32Log.log"
  BD_ARGS=$DSCFILE" -b RELEASE "$BD_MACRO" -a IA32 -n 1 -t "$TOOL_CHAIN
  FSP_BUILD_TYPE=0x0001
  FSP_RELEASE_TYPE=0x0002
  Build32 $*
}

function DebugBuild32(){
  BD_TARGET=DEBUG
  BD_MACRO="-D CFG_DEBUG=1 -D DEBUG_BIOS_ENABLE=TRUE -D CFG_OUTDIR="$OUT_DIR
  DSCFILE="-p "$FSP_PKG_NAME/$FSP_PKG_NAME.dsc   #" -y DebugBuild32Log.log"
  #echo $DSCFILE
  BD_ARGS=$DSCFILE" -b DEBUG "$BD_MACRO" -a IA32 -n 1 -t "$TOOL_CHAIN
  FSP_BUILD_TYPE=0x0000
  FSP_RELEASE_TYPE=0x0000
  Build32 $*
}

function CopyFspBinaryToBinPkg(){
    echo Copy FSP binary to KabylakeFspBinPkg

    if [ -f $WORKSPACE/$FSP_BIN_PKG_NAME/Fsp.bsf ]
      then chmod +w $WORKSPACE/$FSP_BIN_PKG_NAME/Fsp.bsf
    fi
    if [ -f $WORKSPACE/$FSP_BIN_PKG_NAME/Fsp.fd ]
      then chmod +w $WORKSPACE/$FSP_BIN_PKG_NAME/Fsp.fd
    fi
    
    cp $OUT_DIR/$FSP_PKG_NAME/$BD_TARGET"_"$TOOL_CHAIN/FV/KBLFSP.fd $WORKSPACE/$FSP_BIN_PKG_NAME/Fsp.fd

    if [ -f $WORKSPACE/$FSP_BIN_PKG_NAME/Include/FspUpd.h ]
      then chmod +w $WORKSPACE/$FSP_BIN_PKG_NAME/Include/FspUpd.h
    fi

    if [ ! -d $WORKSPACE/$FSP_BIN_PKG_NAME/Include ]
      then mkdir $WORKSPACE/$FSP_BIN_PKG_NAME/Include
    fi
    if [ -f $OUT_DIR/$FSP_PKG_NAME/$BD_TARGET"_"$TOOL_CHAIN/FV/FspUpd.h ]
      then cp $OUT_DIR/$FSP_PKG_NAME/$BD_TARGET"_"$TOOL_CHAIN/FV/FspUpd.h $WORKSPACE/$FSP_BIN_PKG_NAME/Include    
    fi
    if [ -f $WORKSPACE/$FSP_BIN_PKG_NAME/Include/FsptUpd.h ]
      then chmod +w $WORKSPACE/$FSP_BIN_PKG_NAME/Include/FsptUpd.h
    fi
    if [ -f $OUT_DIR/$FSP_PKG_NAME/$BD_TARGET"_"$TOOL_CHAIN/FV/FsptUpd.h ]
      then cp $OUT_DIR/$FSP_PKG_NAME/$BD_TARGET"_"$TOOL_CHAIN/FV/FsptUpd.h $WORKSPACE/$FSP_BIN_PKG_NAME/Include    
    fi
    if [ -f $WORKSPACE/$FSP_BIN_PKG_NAME/Include/FspmUpd.h ]
      then chmod +w $WORKSPACE/$FSP_BIN_PKG_NAME/Include/FspmUpd.h
    fi
    if [ -f $OUT_DIR/$FSP_PKG_NAME/$BD_TARGET"_"$TOOL_CHAIN/FV/FspmUpd.h ]
      then cp $OUT_DIR/$FSP_PKG_NAME/$BD_TARGET"_"$TOOL_CHAIN/FV/FspmUpd.h $WORKSPACE/$FSP_BIN_PKG_NAME/Include    
    fi
    if [ -f $WORKSPACE/$FSP_BIN_PKG_NAME/Include/FspsUpd.h ]
      then chmod +w $WORKSPACE/$FSP_BIN_PKG_NAME/Include/FspsUpd.h
    fi
    if [ -f $OUT_DIR/$FSP_PKG_NAME/$BD_TARGET"_"$TOOL_CHAIN/FV/FspsUpd.h ]
      then cp $OUT_DIR/$FSP_PKG_NAME/$BD_TARGET"_"$TOOL_CHAIN/FV/FspsUpd.h $WORKSPACE/$FSP_BIN_PKG_NAME/Include    
    fi
}
#
# ROYAL_PARK_OVERRIDE: RoyalParkOverrideBegin - RPPO-KBL-0035
#
function OverrideBaseTools() {
    if [ -e ClientCommonPkg/Override/BaseTools/Conf/tools_def.template ]
      then
      echo Overriding ClientCommonPkg tools_def.template...
      cp -f ClientCommonPkg/Override/BaseTools/Conf/tools_def.template Conf/tools_def.txt
    fi 

    if [ -e $FSP_PKG_NAME/Override/BaseTools/Conf/tools_def.template ]
      then
      echo Overriding KabylakePlatSamplePkg tools_def.template...
      cp -f $FSP_PKG_NAME/Override/BaseTools/Conf/tools_def.template Conf/tools_def.txt
    fi

    if [ -e $FSP_PKG_NAME/Override/BaseTools/Conf/build_rule.template ]
      then
      echo Overriding KabylakePlatSamplePkg build_rule.template...
      cp -f $FSP_PKG_NAME/Override/BaseTools/Conf/build_rule.template Conf/build_rule.txt
    fi
}  
#
# ROYAL_PARK_OVERRIDE: RoyalParkOverrideEnd
#

cd ..

if [ -d Conf ]
 then
   . ./$Edksetup
 else
   mkdir Conf
   . ./$Edksetup
fi


OUT_DIR=Build

#
# Detect GCC Tool Chain Version
#
GCC_VERSION=$(gcc -dumpversion|sed 's/^\([0-9]\.[0-9]\).*/\1/')
if [ "$GCC_VERSION" = "4.5" ]; then
  export TOOL_CHAIN=GCC45
elif [ "$GCC_VERSION" = "4.6" ]; then
  export TOOL_CHAIN=GCC46
elif [ "$GCC_VERSION" = "4.7" ]; then
  export TOOL_CHAIN=GCC47
elif [ "$GCC_VERSION" = "4.8" ]; then
  export TOOL_CHAIN=GCC48
elif [ "$GCC_VERSION" = "4.9" ]; then
  export TOOL_CHAIN=GCC49
elif [ "$GCC_VERSION" = "5.3" ]; then
  export TOOL_CHAIN=GCC5
elif [ "$GCC_VERSION" = "5.4" ]; then
  export TOOL_CHAIN=GCC5
else
  echo "Unsupported GCC version!"
  exit 1
fi

if [ "$1" = "-clean" ]
 then
  Clean
elif [ "$1" = "-r32" ]
 then
  ReleaseBuild32
  CopyFspBinaryToBinPkg
elif [ "$1" = "-tr32" ]
 then
  ReleaseTypeTest32
  CopyFspBinaryToBinPkg
elif [ "$1" = "-d32" ]
 then 
   DebugBuild32
   CopyFspBinaryToBinPkg 
elif [ -z "$1" ] 
 then
   DebugBuild32
else 
  echo
  echo  ERROR: $1 is not valid parameter.
  USAGE
fi
