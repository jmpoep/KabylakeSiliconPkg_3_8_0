/** @file
  Declarations for the header structures of a PE executable image.

 @copyright
  INTEL CONFIDENTIAL
  Copyright 2004 - 2016 Intel Corporation.

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

#ifndef _PECOFF_H
#define _PECOFF_H

#include <MrcTypes.h>

#ifdef _MSC_VER
// Disable warning for benign redefinition of type
#pragma warning(disable : 4142)
#endif

#pragma pack(push,1)
typedef struct {
  UINT16   u16Machine;
  UINT16   u16NumSections;
  UINT32   u32DateTimeStamp;
  UINT32   u32SymTblPtr;
  UINT32   u32NumSymbols;
  UINT16   u16PeHdrSize;
  UINT16   u16Characs;
} COFFHDR, *PCOFFHDR;

typedef struct {
  UINT16   u16MagicNum;
  UINT8    u8LinkerMajVer;
  UINT8    u8LinkerMinVer;
  UINT32   u32CodeSize;
  UINT32   u32IDataSize;
  UINT32   u32UDataSize;
  UINT32   u32EntryPoint;
  UINT32   u32CodeBase;
  UINT32   u32DataBase;
  UINT32   u32ImgBase;
  UINT32   u32SectionAlignment;
  UINT32   u32FileAlignment;
  UINT16   u16OSMajVer;
  UINT16   u16OSMinVer;
  UINT16   u16ImgMajVer;
  UINT16   u16ImgMinVer;
  UINT16   u16SubMajVer;
  UINT16   u16SubMinVer;
  UINT32   u32Rsvd;
  UINT32   u32ImgSize;
  UINT32   u32HdrSize;
  UINT32   u32Chksum;
  UINT16   u16Subsystem;
  UINT16   u16DLLChars;
  UINT32   u32StkRsrvSize;
  UINT32   u32StkCmmtSize;
  UINT32   u32HeapRsrvSize;
  UINT32   u32HeapCmmtSize;
  UINT32   u32LdrFlags;
  UINT32   u32NumDatDirs;
} PEHDR, *PPEHDR;

typedef struct {
  UINT32   u32Rva;
  UINT32   u32DataDirSize;
} DATADIR, *PDATADIR;

typedef struct {
  char     cName[8];
  UINT32   u32VirtualSize;
  UINT32   u32VirtualAddress;
  UINT32   u32RawDataSize;
  UINT32   u32RawDataPtr;
  UINT32   u32RelocPtr;
  UINT32   u32LineNumPtr;
  UINT16   u16NumRelocs;
  UINT16   u16NumLineNums;
  UINT32   u32Characs;
} SECTIONTBL, *PSECTIONTBL;

#pragma pack(pop)

#endif // _PECOFF_H
