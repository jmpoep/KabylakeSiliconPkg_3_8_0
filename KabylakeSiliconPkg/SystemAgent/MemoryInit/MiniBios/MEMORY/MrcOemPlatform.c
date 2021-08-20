/** @file
  This file contains platform related functions.

 @copyright
  INTEL CONFIDENTIAL
  Copyright 1999 - 2019 Intel Corporation.

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

//
// Include files
//

#include "MemoryUtils.h"
#include "MrcTypes.h"
#include "MrcApi.h"
#include "McAddress.h"
#include "MrcCommon.h"
#include "MrcInterface.h"
#include "crc.h"
#include "MrcOemPlatform.h"
#include "PlatformBoardId.h"

#include "PchRegsRcrb.h"
#include "PchRegsPcr.h"
#include "PchRegsPmc.h"
#include "PchRegsLpcLpt.h"
#include "PchRegsLpcSpt.h"
#include "MrcReset.h"

#ifdef SSA_FLAG
#include "MrcSsaInitialize.h"
#endif

//
// MrcSave data is stored here in Flash
//
#define MRC_SAVE_DATA_FLASH_PTR   0xFFD00000

#if (MRC_ALL_DDR_SUPPORTED)
#define MAX_SPD_PAGE_COUNT (2)
#else
#define MAX_SPD_PAGE_COUNT (1)
#endif
#define MAX_SPD_PAGE_SIZE  (256)
#define MAX_SPD_SIZE       (MAX_SPD_PAGE_SIZE * MAX_SPD_PAGE_COUNT)
#define SPD_PAGE_ADDRESS_0 (0x6C)
#define SPD_PAGE_ADDRESS_1 (0x6E)
#define isprint(a)         (((a) >= ' ') && ((a) <= '~') ? (a) : 0)

#ifdef MRC_DEBUG_PRINT
extern const char CcdString[];
#endif // MRC_DEBUG_PRINT
extern
void
MmioReadCount (
  void
  );
extern
void
MmioWriteCount (
  void
  );

#pragma pack (push, 1)
//
// The following section contains board-specific CMD/CTL/CLK and DQ/DQS mapping, needed for LPDDR3
//

//
// DQByteMap[0] - ClkDQByteMap:
//   If clock is per rank, program to [0xFF, 0xFF]
//   If clock is shared by 2 ranks, program to [0xFF, 0] or [0, 0xFF]
//   If clock is shared by 2 ranks but does not go to all bytes,
//           Entry[i] defines which DQ bytes Group i services
// DQByteMap[1] - CmdNDQByteMap: Entry[0] is CmdN/CAA and Entry[1] is CmdN/CAB
// DQByteMap[2] - CmdSDQByteMap: Entry[0] is CmdS/CAA and Entry[1] is CmdS/CAB
// DQByteMap[3] - CkeDQByteMap : Entry[0] is CKE /CAA and Entry[1] is CKE /CAB
//                For DDR, DQByteMap[3:1] = [0xFF, 0]
// DQByteMap[4] - CtlDQByteMap : Always program to [0xFF, 0] since we have 1 CTL / rank
//                               Variable only exists to make the code easier to use
// DQByteMap[5] - CmdVDQByteMap: Always program to [0xFF, 0] since we have 1 CA Vref
//                               Variable only exists to make the code easier to use
//
//
// DQ byte mapping to CMD/CTL/CLK, from the CPU side for SKL RVP1
//
const UINT8 DqByteMapSkl[2][6][2] = {
  // Channel 0:
  {
    { 0x0F, 0xF0 }, // CLK0 goes to package 0 - Bytes[3:0], CLK1 goes to package 1 - Bytes[7:4]
    { 0x00, 0xF0 }, // CmdN does not have CAA, CAB goes to Bytes[7:4]
    { 0x0F, 0xF0 }, // CmdS CAA goes to Bytes[3:0], CmdS CAB goes to Byte[7:4]
    { 0x0F, 0x00 }, // CKE CAA goes to Bytes[3:0], CKE does not have CAB
    { 0xFF, 0x00 }, // CTL (CS) goes to all bytes
    { 0xFF, 0x00 }  // CA Vref is one for all bytes
  },
  // Channel 1:
  {
    { 0x33, 0xCC }, // CLK0 goes to package 0 - Bytes[5:4][1:0], CLK1 goes to package 1 - Bytes[7:6][3:2]
    { 0x00, 0xCC }, // CmdN does not have CAA, CAB goes to Bytes[7:6][3:2]
    { 0x33, 0xCC }, // CmdS CAA goes to Bytes[5:4][1:0], CmdS CAB goes to Byte[7:6][3:2]
    { 0x33, 0x00 }, // CKE CAA goes to Bytes[5:4][1:0], CKE does not have CAB
    { 0xFF, 0x00 }, // CTL (CS) goes to all bytes
    { 0xFF, 0x00 }  // CA Vref is one for all bytes
  }
};

//
// DQ byte mapping to CMD/CTL/CLK, from the CPU side - for SKL RVP5 and RVP16
//
const UINT8 DqByteMapSklRvp5[2][6][2] = {
  // Channel 0:
  {
    { 0x0F, 0xF0 }, // CLK0 goes to package 0 - Bytes[3:0], CLK1 goes to package 1 - Bytes[7:4]
    { 0x00, 0xF0 }, // CmdN does not have CAA, CAB goes to Bytes[7:4]
    { 0x0F, 0xF0 }, // CmdS CAA goes to Bytes[3:0], CmdS CAB goes to Byte[7:4]
    { 0x0F, 0x00 }, // CKE CAA goes to Bytes[3:0], CKE does not have CAB
    { 0xFF, 0x00 }, // CTL (CS) goes to all bytes
    { 0xFF, 0x00 }  // CA Vref is one for all bytes
  },
  // Channel 1:
  {
    { 0x0F, 0xF0 }, // CLK0 goes to package 0 - Bytes[3:0], CLK1 goes to package 1 - Bytes[7:4]
    { 0x00, 0xF0 }, // CmdN does not have CAA, CAB goes to Bytes[7:4]
    { 0x0F, 0xF0 }, // CmdS CAA goes to Bytes[3:0], CmdS CAB goes to Byte[7:4]
    { 0x0F, 0x00 }, // CKE CAA goes to Bytes[3:0], CKE does not have CAB
    { 0xFF, 0x00 }, // CTL (CS) goes to all bytes
    { 0xFF, 0x00 }  // CA Vref is one for all bytes
  }
};

//
// DQ byte mapping to CMD/CTL/CLK, from the CPU side - for SKL DOE RVP
//
const UINT8 DqByteMapSklLpdimmDOE[2][6][2] = {
  // Channel 0:
  {
    { 0x0F, 0xF0 }, // CLK0 goes to package 0 - Bytes[3:0], CLK1 goes to package 1 - Bytes[7:4]
    { 0x00, 0xF0 }, // CmdN does not have CAA, CAB goes to Bytes[7:4]
    { 0x0F, 0xF0 }, // CmdS CAA goes to Bytes[3:0], CmdS CAB goes to Byte[7:4]
    { 0x0F, 0x00 }, // CKE CAA goes to Bytes[3:0], CKE does not have CAB
    { 0xFF, 0x00 }, // CTL (CS) goes to all bytes
    { 0xFF, 0x00 }  // CA Vref is one for all bytes
  },
  // Channel 1:
  {
    { 0x0F, 0xF0 }, // CLK0 goes to package 0 - Bytes[3:0], CLK1 goes to package 1 - Bytes[7:4]
    { 0x00, 0xF0 }, // CmdN does not have CAA, CAB goes to Bytes[7:4]
    { 0x0F, 0xF0 }, // CmdS CAA goes to Bytes[3:0], CmdS CAB goes to Byte[7:4]
    { 0x0F, 0x00 }, // CKE CAA goes to Bytes[3:0], CKE does not have CAB
    { 0xFF, 0x00 }, // CTL (CS) goes to all bytes
    { 0xFF, 0x00 }  // CA Vref is one for all bytes
  }
};

// DQ byte mapping to CMD/CTL/CLK, from the CPU side - for AML Y42 AEP
const UINT8 mDqByteMapAml42Lpddr3Cff[2][6][2] = {
  // Channel 0:
  {
    { 0xF0, 0x0F }, // CLK0 goes to package 0 - Bytes[3:0], CLK1 goes to package 1 - Bytes[7:4]
    { 0x00, 0x0F }, // CmdN does not have CAA, CAB goes to Bytes[7:4]
    { 0xF0, 0x0F }, // CmdS CAA goes to Bytes[3:0], CmdS CAB goes to Byte[7:4]
    { 0xF0, 0x00 }, // CKE CAA goes to Bytes[3:0], CKE does not have CAB
    { 0xFF, 0x00 }, // CTL (CS) goes to all bytes
    { 0xFF, 0x00 }  // CA Vref is one for all bytes
  },
  // Channel 1:
  {
    { 0x3C, 0xC3 }, // CLK0 goes to package 0 - Bytes[3:0], CLK1 goes to package 1 - Bytes[7:4]
    { 0x00, 0xC3 }, // CmdN does not have CAA, CAB goes to Bytes[7:4]
    { 0x3C, 0xC3 }, // CmdS CAA goes to Bytes[3:0], CmdS CAB goes to Byte[7:4]
    { 0x3C, 0x00 }, // CKE CAA goes to Bytes[3:0], CKE does not have CAB
    { 0xFF, 0x00 }, // CTL (CS) goes to all bytes
    { 0xFF, 0x00 }  // CA Vref is one for all bytes
  }
};

//
// DQS byte swizzling between CPU and DRAM - for SKL DOE RVP
//
/*
const UINT8 DqsMapCpu2ConnectorSklLpdimm3DOE[2][8] = {
  { 1, 2, 3, 0, 6, 7, 4, 5}, // Channel 0
  { 0, 1, 2, 3, 4, 5, 6, 7}  // Channel 1
};
const UINT8 DqsMapConnector2DramSklLpdimm3DOE[2][8] = {
  { 0, 2, 1, 3, 6, 4, 5, 7}, // Channel 0
  { 0, 2, 1, 3, 6, 4, 5, 7}  // Channel 1
};
*/
const UINT8 DqsMapCpu2DramSklLpdimmDOE[2][8] = {
  { 2, 1, 3, 0, 5, 7, 6, 4}, // Channel 0
  { 0, 2, 1, 3, 4, 5, 6, 7}  // Channel 1
};

//
// DQS byte swizzling between CPU and DRAM - for SKL RVP1, RVP3, RVP13
//
const UINT8 DqsMapCpu2DramSklRvp[2][8] = {
  { 0, 1, 3, 2, 4, 5, 6, 7 }, // Channel 0
  { 1, 0, 4, 5, 2, 3, 6, 7 }  // Channel 1
};

//
// DQS byte swizzling between CPU and DRAM - for SKL RVP5
//
const UINT8 DqsMapCpu2DramSklRvp5[2][8] = {
  { 1, 0, 3, 2, 5, 4, 6, 7 }, // Channel 0
  { 2, 3, 1, 0, 6, 4, 5, 7 }  // Channel 1
};

//
// DQS byte swizzling between CPU and DRAM - for SKL RVP16
//
const UINT8 DqsMapCpu2DramSklRvp16[2][8] = {
  { 0, 1, 2, 3, 4, 5, 6, 7 }, // Channel 0
  { 2, 1, 0, 3, 6, 5, 4, 7 }  // Channel 1
};

//
// DQS byte swizzling between CPU and DRAM - for SKL Phablet
//
const UINT8 DqsMapCpu2DramSklPhabletPoc[2][8] = {
  { 1, 2, 0, 3, 5, 6, 4, 7 }, // Channel 0
  { 2, 1, 5, 6, 0, 3, 7, 4 }  // Channel 1
};

// DQS byte swizzling between CPU and DRAM - for AML Y42 RVP
const UINT8 mDqsMapCpu2DramAml42Lpddr3Rvp[2][8] = {
  { 0, 1, 2, 3, 4, 5, 6, 7 }, // Channel 0
  { 3, 2, 1, 0, 6, 7, 4, 5 }  // Channel 1
};

// DQS byte swizzling between CPU and DRAM - for AML Y42 AEP
const UINT8 mDqsMapCpu2DramAml42Lpddr3Cff[2][8] = {
  { 4, 5, 7, 6, 0, 1, 2, 3 }, // Channel 0
  { 5, 4, 1, 0, 3, 2, 6, 7 }  // Channel 1
};

//
// Reference RCOMP resistors on motherboard - for SKL RVP1
//
const UINT16 RcompResistorSklRvp1[MAX_RCOMP] = { 200, 81, 162 };
//
// RCOMP target values for RdOdt, WrDS, WrDSCmd, WrDSCtl, WrDSClk - for SKL RVP1
//
const UINT16 RcompTargetSklRvp1[MAX_RCOMP_TARGETS] = { 100, 40, 40, 23, 40 };

//
// Reference RCOMP resistors on motherboard - for SKL RVP2
//
const UINT16 RcompResistorSklRvp2[MAX_RCOMP] = { 121, 81, 100 };
//
// RCOMP target values for RdOdt, WrDS, WrDSCmd, WrDSCtl, WrDSClk - for SKL RVP2
//
const UINT16 RcompTargetSklRvp2[MAX_RCOMP_TARGETS] = { 100, 40, 20, 20, 26 };

//
// Reference RCOMP resistors on motherboard - for SKL DT/Halo
//
const UINT16 RcompResistorSklDtHalo[MAX_RCOMP] = { 121, 75, 100 };
//
// RCOMP target values for RdOdt, WrDS, WrDSCmd, WrDSCtl, WrDSClk - for SKL DT/Halo
//
const UINT16 RcompTargetSklDtHalo[MAX_RCOMP_TARGETS] = { 60, 26, 20, 20, 26 };

//
// Reference RCOMP resistors on motherboard - for SKL DT Halo with LPDDR3
//
const UINT16 RcompResistorSklDtHaloLpddr3[MAX_RCOMP] = { 200, 121, 162 };
//
// RCOMP target values for RdOdt, WrDS, WrDSCmd, WrDSCtl, WrDSClk - for SKL DT Halo with LPDDR3
//
const UINT16 RcompTargetSklDtHaloLpddr3[MAX_RCOMP_TARGETS] = { 100, 40, 40, 23, 40 };


#ifdef NOSMBUS_BUILD
///
/// DDR3 1600 2GB single rank
///
const UINT8 SPDData[] =
  {0x92, 0x11, 0x0B, 0x02, 0x03, 0x19, 0x02, 0x01, 0x03, 0x11, 0x01, 0x08, 0x0A, 0x00, 0xFE, 0x00, /// 00-15
   0x69, 0x78, 0x69, 0x30, 0x69, 0x11, 0x18, 0x81, 0x00, 0x05, 0x3C, 0x3C, 0x00, 0xF0, 0x83, 0x01, /// 16-31
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /// 32-47
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0F, 0x11, 0x61, 0x00, /// 48-63
   0x00, 0x00, 0x00, 0x00, 0x00, 0xC0, 0x00, 0x00, 0x00, 0x80                                      /// 64-73
};
#endif
#pragma pack (pop)

/**
  Read the SPD data over the SMBus, at the specified SPD address, starting at
  the specified starting offset and read the given amount of data.

  @param[in, out] Inputs - Mrc Inputs structure
  @param[in] SpdAddress  - SPD SMBUS address
  @param[in, out] Buffer - Buffer to store the data.
  @param[in] Start       - Starting SPD offset
  @param[in] Size        - The number of bytes of data to read and also the size of the buffer.
  @param[in, out] Page   - The final page that is being pointed to.

  @retval mrcSuccess if the read is successful, otherwise mrcDimmNotExist, which
  @retval indicates that no slots are populated.
**/
static
MrcStatus
DoSpdRead (
  IN OUT MrcInput *const Inputs,
  IN     const UINT8     SpdAddress,
  IN OUT UINT8 *const    Buffer,
  IN     const UINT16    Start,
  IN           UINT16    Size,
  IN OUT UINT8           *Page
  )
{
  MrcStatus Status;
  BOOLEAN   PageUpdate;
  UINT16    Count;
  UINT16    Index;

  Status = mrcFail;
  if ((Buffer != NULL) && (Start < MAX_SPD_SIZE) && ((Start + Size) < MAX_SPD_SIZE)) {
    Count = 0;
    PageUpdate = FALSE;
    while (Size--) {
      Index = Start + Count;
      if ((Index / MAX_SPD_PAGE_SIZE) != *Page) {
        *Page = (UINT8) (Index / MAX_SPD_PAGE_SIZE);
        PageUpdate = TRUE;
      }
      Index %= MAX_SPD_PAGE_SIZE;
      if (PageUpdate == TRUE) {
        PageUpdate = FALSE;
        MrcOemSmbusWrite8 (Inputs->SmbusBaseAddress, (*Page == 0) ? SPD_PAGE_ADDRESS_0 : SPD_PAGE_ADDRESS_1, 0, 0);
      }
      Status = MrcOemSmbusRead8 (Inputs->SmbusBaseAddress, SpdAddress, (UINT8) Index, &Buffer[Count]);
      if (mrcSuccess != Status) {
        break;
      }
      Count++;
    }
  }
  return (Status);
}

/**
  See if there is valid XMP SPD data.

  @param[in] Debug    - Mrc debug structure.
  @param[in, out] Spd - Mrc SPD structure.
  @param[in] XmpStart - The current offset in the SPD.

  @retval TRUE if valid, FALSE in not.
**/
static
BOOLEAN
VerifyXmp (
  IN MrcDebug          *Debug,
  IN OUT MrcSpd *const Spd,
  IN const UINT16      XmpStart
  )
{
  SPD_EXTREME_MEMORY_PROFILE_HEADER      *Header1;
  SPD_EXTREME_MEMORY_PROFILE_HEADER_2_0  *Header2;
  BOOLEAN                                 Xmp;

  Xmp = FALSE;

  switch (((UINT8 *) Spd) [2]) {
    case MRC_SPD_DDR3_SDRAM_TYPE_NUMBER:
      Header1 = &Spd->Ddr3.Xmp.Header;
      if (XmpStart == ((UINT32) (Header1) - (UINT32) Spd)) {
        Xmp = TRUE;
        if ((Header1->XmpRevision.Data & 0xFE) == 0x12) {
          return (TRUE);
        } else {
          Header1->XmpId            = 0;
          Header1->XmpOrgConf.Data  = 0;
          Header1->XmpRevision.Data = 0;
        }
      }
      break;
    case MRC_SPD_DDR4_SDRAM_TYPE_NUMBER:
      Header2 = &Spd->Ddr4.EndUser.Xmp.Header;
      if (XmpStart == ((UINT32) (Header2) - (UINT32) Spd)) {
        Xmp = TRUE;
        if ((Header2->XmpRevision.Data) == 0x20) {
          return (TRUE);
        } else {
          Header2->XmpId            = 0;
          Header2->XmpOrgConf.Data  = 0;
          Header2->XmpRevision.Data = 0;
        }
      }
      break;
    case MRC_SPD_LPDDR3_SDRAM_TYPE_NUMBER:
    case MRC_JEDEC_LPDDR3_SDRAM_TYPE_NUMBER:
      return (TRUE);
    default:
      return (FALSE);
  }
  if (!Xmp) {
    return (TRUE);
  }
  return (FALSE);
}

/**
  Read the SPD data over the SMBus, for all DIMM slots and copy the data to the MrcData structure.
  The SPD data locations read is controlled by the current boot mode.

  @param[in] BootMode     - Mrc Boot Mode
  @param[in, out] MrcData - Mrc global data structure

  @retval mrcSuccess if the read is successful, otherwise mrcDimmNotExist, which
  @retval indicates that no slots are populated.
**/
MrcStatus
GetSpdData (
  IN     const MrcBootMode    BootMode,
  IN OUT MrcParameters *const MrcData
  )
{
#pragma pack (push, 1)
  typedef struct {
    UINT16 Start;
    UINT16 End;
    UINT8  BootMode;
    UINT8  Profile;
  } SpdOffsetTable;
#pragma pack (pop)
  static const SpdOffsetTable Ddr3Table[] = {
    {   0,               1,           (1 << bmCold),                                   (1 << STD_PROFILE) | (1 << XMP_PROFILE1) | (1 << XMP_PROFILE2) | (1 << USER_PROFILE) },
    {   2,               2,           (1 << bmCold) | (1 << bmFast),                   (1 << STD_PROFILE) | (1 << XMP_PROFILE1) | (1 << XMP_PROFILE2) | (1 << USER_PROFILE) },
    {   3,              41,           (1 << bmCold),                                   (1 << STD_PROFILE) | (1 << XMP_PROFILE1) | (1 << XMP_PROFILE2) | (1 << USER_PROFILE) },
    {  60,              63,           (1 << bmCold),                                   (1 << STD_PROFILE) | (1 << XMP_PROFILE1) | (1 << XMP_PROFILE2) | (1 << USER_PROFILE) },
    { SPD3_MANUF_START, SPD3_MANUF_END, (1 << bmCold) | (1 << bmWarm) | (1 << bmFast), (1 << STD_PROFILE) | (1 << XMP_PROFILE1) | (1 << XMP_PROFILE2) | (1 << USER_PROFILE) },
    { 128,             145,           (1 << bmCold),                                   (1 << STD_PROFILE) | (1 << XMP_PROFILE1) | (1 << XMP_PROFILE2) | (1 << USER_PROFILE) },
#if (SUPPORT_SPD_CRC == SUPPORT)
    {  39,              59,           (1 << bmCold),                                   (1 << STD_PROFILE) | (1 << XMP_PROFILE1) | (1 << XMP_PROFILE2) | (1 << USER_PROFILE) },
    {  64,             125,           (1 << bmCold),                                   (1 << STD_PROFILE) | (1 << XMP_PROFILE1) | (1 << XMP_PROFILE2) | (1 << USER_PROFILE) },
#endif
    { 176,             179,           (1 << bmCold),                                   (1 << STD_PROFILE) | (1 << XMP_PROFILE1) | (1 << XMP_PROFILE2) | (1 << USER_PROFILE) },
    { 180,             184,           (1 << bmCold),                                   (1 << STD_PROFILE) | (1 << XMP_PROFILE1) | (1 << XMP_PROFILE2) | (1 << USER_PROFILE) },
    { 185,             215,           (1 << bmCold),                                   (1 << STD_PROFILE) | (1 << XMP_PROFILE1) | (1 << XMP_PROFILE2) | (1 << USER_PROFILE) },
    { 220,             250,           (1 << bmCold),                                   (1 << STD_PROFILE) | (1 << XMP_PROFILE1) | (1 << XMP_PROFILE2) | (1 << USER_PROFILE) },
  };
#if (MRC_ALL_DDR_SUPPORTED)
  static const SpdOffsetTable Ddr4Table[] = {
    {   0,               1,           (1 << bmCold),                                   (1 << STD_PROFILE) | (1 << XMP_PROFILE1) | (1 << XMP_PROFILE2) | (1 << USER_PROFILE) },
    {   2,               2,           (1 << bmCold) | (1 << bmFast),                   (1 << STD_PROFILE) | (1 << XMP_PROFILE1) | (1 << XMP_PROFILE2) | (1 << USER_PROFILE) },
    {   3,              40,           (1 << bmCold),                                   (1 << STD_PROFILE) | (1 << XMP_PROFILE1) | (1 << XMP_PROFILE2) | (1 << USER_PROFILE) },
    { 117,             131,           (1 << bmCold),                                   (1 << STD_PROFILE) | (1 << XMP_PROFILE1) | (1 << XMP_PROFILE2) | (1 << USER_PROFILE) },
    { SPD4_MANUF_START, SPD4_MANUF_END, (1 << bmCold) | (1 << bmWarm) | (1 << bmFast), (1 << STD_PROFILE) | (1 << XMP_PROFILE1) | (1 << XMP_PROFILE2) | (1 << USER_PROFILE) },
    { 329,             348,           (1 << bmCold),                                   (1 << STD_PROFILE) | (1 << XMP_PROFILE1) | (1 << XMP_PROFILE2) | (1 << USER_PROFILE) },
#if (SUPPORT_SPD_CRC == SUPPORT)
    {  32,             119,           (1 << bmCold),                                   (1 << STD_PROFILE) | (1 << XMP_PROFILE1) | (1 << XMP_PROFILE2) | (1 << USER_PROFILE) },
    { 126,             255,           (1 << bmCold),                                   (1 << STD_PROFILE) | (1 << XMP_PROFILE1) | (1 << XMP_PROFILE2) | (1 << USER_PROFILE) },
    { 349,             383,           (1 << bmCold),                                   (1 << STD_PROFILE) | (1 << XMP_PROFILE1) | (1 << XMP_PROFILE2) | (1 << USER_PROFILE) },
#endif
    { 384,             387,           (1 << bmCold),                                   (1 << STD_PROFILE) | (1 << XMP_PROFILE1) | (1 << XMP_PROFILE2) | (1 << USER_PROFILE) },
    { 388,             389,           (1 << bmCold),                                   (1 << STD_PROFILE) | (1 << XMP_PROFILE1) | (1 << XMP_PROFILE2) | (1 << USER_PROFILE) },
    { 393,             431,           (1 << bmCold),                                   (1 << STD_PROFILE) | (1 << XMP_PROFILE1) | (1 << XMP_PROFILE2) | (1 << USER_PROFILE) },
    { 440,             478,           (1 << bmCold),                                   (1 << STD_PROFILE) | (1 << XMP_PROFILE1) | (1 << XMP_PROFILE2) | (1 << USER_PROFILE) },
  };
  static const SpdOffsetTable LpddrTable[] = {
    {   0,               1,               (1 << bmCold),                                 (1 << STD_PROFILE) | (1 << XMP_PROFILE1) | (1 << XMP_PROFILE2) | (1 << USER_PROFILE) },
    {   2,               2,               (1 << bmCold) | (1 << bmFast),                 (1 << STD_PROFILE) | (1 << XMP_PROFILE1) | (1 << XMP_PROFILE2) | (1 << USER_PROFILE) },
    {   3,              32,               (1 << bmCold),                                 (1 << STD_PROFILE) | (1 << XMP_PROFILE1) | (1 << XMP_PROFILE2) | (1 << USER_PROFILE) },
    { 120,             130,               (1 << bmCold),                                 (1 << STD_PROFILE) | (1 << XMP_PROFILE1) | (1 << XMP_PROFILE2) | (1 << USER_PROFILE) },
    { SPDLP_MANUF_START, SPDLP_MANUF_END, (1 << bmCold) | (1 << bmWarm) | (1 << bmFast), (1 << STD_PROFILE) | (1 << XMP_PROFILE1) | (1 << XMP_PROFILE2) | (1 << USER_PROFILE) },
    { 329,             348,               (1 << bmCold),                                 (1 << STD_PROFILE) | (1 << XMP_PROFILE1) | (1 << XMP_PROFILE2) | (1 << USER_PROFILE) },
#if (SUPPORT_SPD_CRC == SUPPORT)
    {  31,             121,               (1 << bmCold),                                 (1 << STD_PROFILE) | (1 << XMP_PROFILE1) | (1 << XMP_PROFILE2) | (1 << USER_PROFILE) },
    { 126,             255,               (1 << bmCold),                                 (1 << STD_PROFILE) | (1 << XMP_PROFILE1) | (1 << XMP_PROFILE2) | (1 << USER_PROFILE) },
    { 349,             383,               (1 << bmCold),                                 (1 << STD_PROFILE) | (1 << XMP_PROFILE1) | (1 << XMP_PROFILE2) | (1 << USER_PROFILE) },
#endif
    { 384,             387,               (1 << bmCold),                                 (1 << STD_PROFILE) | (1 << XMP_PROFILE1) | (1 << XMP_PROFILE2) | (1 << USER_PROFILE) },
    { 388,             389,               (1 << bmCold),                                 (1 << STD_PROFILE) | (1 << XMP_PROFILE1) | (1 << XMP_PROFILE2) | (1 << USER_PROFILE) },
    { 393,             431,               (1 << bmCold),                                 (1 << STD_PROFILE) | (1 << XMP_PROFILE1) | (1 << XMP_PROFILE2) | (1 << USER_PROFILE) },
    { 440,             478,               (1 << bmCold),                                 (1 << STD_PROFILE) | (1 << XMP_PROFILE1) | (1 << XMP_PROFILE2) | (1 << USER_PROFILE) },
  };
#endif
  MrcInput              *Inputs;
  MrcDebug              *Debug;
  MrcControllerIn       *ControllerIn;
  MrcChannelIn          *ChannelIn;
  MrcDimmIn             *DimmIn;
  UINT8                 *Buffer;
  const SpdOffsetTable  *Tbl;
  const SpdOffsetTable  *TableSelect;
  MrcStatus             Status;
  UINT16                Offset;
  UINT8                 Controller;
  UINT8                 Channel;
  UINT8                 Dimm;
  UINT8                 Count;
  UINT8                 Index;
  UINT8                 Stop;
  UINT8                 Page;

  Inputs = &MrcData->Inputs;
  Debug  = &MrcData->Outputs.Debug;
  Count  = 0;
#if (MRC_ALL_DDR_SUPPORTED)
  Page   = (UINT8) (~0);
#else
  Page   = 0;
#endif
  for (Controller = 0; Controller < MAX_CONTROLLERS; Controller++) {
    ControllerIn = &Inputs->Controller[Controller];
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      ChannelIn = &ControllerIn->Channel[Channel];
      if (ChannelIn->Status == CHANNEL_PRESENT) {
        for (Dimm = 0; Dimm < MAX_DIMMS_IN_CHANNEL; Dimm++) {
          Status  = mrcSuccess;
          DimmIn  = &ChannelIn->Dimm[Dimm];
          if ((DimmIn->Status == DIMM_ENABLED) || (DimmIn->Status == DIMM_DISABLED)) {
            Buffer = (UINT8 *) &DimmIn->Spd.Data;
            if (DimmIn->SpdAddress > 0) {
#if (MRC_ALL_DDR_SUPPORTED)
              Status |= DoSpdRead (Inputs, DimmIn->SpdAddress, &Buffer[2], 2, 1, &Page);
              if (Status != mrcSuccess) {
                Buffer[2] = 0;
              }
              switch (Buffer[2]) {
                case MRC_SPD_DDR3_SDRAM_TYPE_NUMBER:
                case MRC_SPD_LPDDR3_SDRAM_TYPE_NUMBER:
                default:
#endif
                  TableSelect = Ddr3Table;
                  Stop = (sizeof (Ddr3Table) / sizeof (SpdOffsetTable));
#if (MRC_ALL_DDR_SUPPORTED)
                  break;

                case MRC_SPD_DDR4_SDRAM_TYPE_NUMBER:
                  TableSelect = Ddr4Table;
                  Stop = (sizeof (Ddr4Table) / sizeof (SpdOffsetTable));
                  break;

                case MRC_JEDEC_LPDDR3_SDRAM_TYPE_NUMBER:
                  TableSelect = LpddrTable;
                  Stop = (sizeof (LpddrTable) / sizeof (SpdOffsetTable));
                  break;
              }
#endif
              for (Index = 0; (Status == mrcSuccess) && (Index < Stop); Index++) {
                Tbl = &TableSelect[Index];
                if (((1 << BootMode) & Tbl->BootMode) && ((1 << Inputs->MemoryProfile) & Tbl->Profile)) {
                  Status = DoSpdRead (
                             Inputs,
                             DimmIn->SpdAddress,
                             &Buffer[Tbl->Start],
                             Tbl->Start,
                             Tbl->End - Tbl->Start + 1,
                             &Page
                             );
                  if (Status == mrcSuccess) {
                    for (Offset = Tbl->Start; Offset <= Tbl->End; Offset++) {
                      DimmIn->Spd.SpdValid[Offset / CHAR_BITS] |= 1 << (Offset % CHAR_BITS);
                    }
                    if (bmCold == BootMode) {
                      if (FALSE == VerifyXmp (Debug, (MrcSpd *) Buffer, Tbl->Start)) {
                        MRC_DEBUG_MSG (
                          Debug,
                          MSG_LEVEL_NOTE,
                          "VerifyXmp FALSE\n"
                          );
                        break;
                      }
                    }
                  } else {
                    MRC_DEBUG_MSG (
                      Debug,
                      MSG_LEVEL_WARNING,
                      "ERROR! Fail to read SMB DimmAddress %Xh Offset %Xh - %Xh\n",
                      DimmIn->SpdAddress,
                      Tbl->Start,
                      Tbl->End
                      );
                  } // if (Status...
                } // if (((1 << BootMode)...
              }  // for (Index...
            }  else { // if (DimmIn->SpdAddress > 0), 0 = MemoryDown, see EnableMemoryDown()
              Status = mrcSuccess;
            }

            if (Status == mrcSuccess) {
              Count++;
            } else {
              MRC_DEBUG_MSG (Debug, MSG_LEVEL_WARNING, "DIMM is not populated on channel %u, slot %u\n", Channel, Dimm);
            } // if (Status...
          }  // if (DimmIn->Status == DIMM_ENABLED)
        }  // for (Dimm...
      }  // if (ChannelIn->Status...
    }  // for (Channel...
  }  // for (Controller...
  return ((Count > 0) ? mrcSuccess : mrcDimmNotExist);
}

/*++

  8 bit I/O port read.

  @param[in] IoAddress - The I/O port read address.

  @retval The value read.
**/
UINT8
MrcOemInPort8 (
  IN const UINT32 IoAddress
  )
{
  return IoRead8 (IoAddress);
}

/**
  8 bit I/O port write.

  @param[in] IoAddress - The I/O port read address.
  @param[in] Data      - The value to write.

  @retval Nothing.
**/
void
MrcOemOutPort8 (
  IN const UINT32 IoAddress,
  IN const UINT8  Data
  )
{
  IoWrite8 (IoAddress, Data);
}

/**
  16 bit I/O port read.

  @param[in] IoAddress - The I/O port read address.

  @retval The value read.
**/
UINT16
MrcOemInPort16 (
  IN const UINT32 IoAddress
  )
{
  return IoRead16 (IoAddress);
}

/**
  16 bit I/O port write.

  @param[in] IoAddress - The I/O port read address.
  @param[in] Data      - The value to write.

  @retval Nothing.
**/
void
MrcOemOutPort16 (
  IN const UINT32 IoAddress,
  IN const UINT16 Data
  )
{
  IoWrite16 (IoAddress, Data);
}

/**
  32 bit I/O port read.

  @param[in] IoAddress - The I/O port read address.

  @retval The value read.
**/
UINT32
MrcOemInPort32 (
  IN const UINT32 IoAddress
  )
{
  return IoRead32 (IoAddress);
}

/**

  32 bit I/O port write.

  @param[in] IoAddress - The I/O port read address.
  @param[in] Data      - The value to write.

  @retval Nothing.
**/
void
MrcOemOutPort32 (
  IN const UINT32 IoAddress,
  IN const UINT32 Data
  )
{
  IoWrite32 (IoAddress, Data);
}

/**
  The PCI index address.

  @retval The PCI index address.
**/
UINT16
MrcOemPciIndex (
  void
  )
{
  return 0xCF8;
}

/**
  The PCI data address.

  @retval The PCI data address.
**/
UINT16
MrcOemPciData (
  void
  )
{
  return 0xCFC;
}

/**
  Calculate the PCI device address for the given Bus/Device/Function/Offset.

  @param[in] Bus      - PCI bus
  @param[in] Device   - PCI device
  @param[in] Function - PCI function
  @param[in] Offset   - Offset

  @retval The PCI device address.
**/
UINT32
GetPciDeviceAddress (
  IN const UINT8 Bus,
  IN const UINT8 Device,
  IN const UINT8 Function,
  IN const UINT8 Offset
  )
{
  return (
    ((UINT32) ((Bus)      & 0xFF) << 16) |
    ((UINT32) ((Device)   & 0x1F) << 11) |
    ((UINT32) ((Function) & 0x07) << 8)  |
    ((UINT32) ((Offset)   & 0xFF) << 0)  |
    (1UL << 31));
}

/**
  Calculate the PCIE device address for the given Bus/Device/Function/Offset.

  @param[in] Bus      - PCI bus
  @param[in] Device   - PCI device
  @param[in] Function - PCI function
  @param[in] Offset   - Offset

   The PCIE device address.

  @retval The PCIe device address
**/
UINT32
GetPcieDeviceAddress (
  IN const UINT8 Bus,
  IN const UINT8 Device,
  IN const UINT8 Function,
  IN const UINT8 Offset
  )
{
  return ((UINT32) Bus << 20) + ((UINT32) Device << 15) + ((UINT32) Function << 12) + ((UINT32) Offset << 0);
}

/**
  Check if RTC date and time update is in progress and wait util it's finished.
  We have at least 244us when "update in progress bit" is seen as low to
  perform an operation on the RTC.

  @retval Zero on timeout or non-zero and RTC is ready for transaction.
**/
UINT32
CheckUpdateComplete (
  void
  )
{
  UINT32 Timeout;

  //
  // Wait until RTC "update in progress" bit goes low.
  //
  Timeout = 0x0FFFFF;
  do {
    MrcOemOutPort8 (RTC_INDEX_REGISTER, CMOS_REGA);
    if ((MrcOemInPort8 (RTC_TARGET_REGISTER) & RTC_UPDATE_IN_PROGRESS) != RTC_UPDATE_IN_PROGRESS) {
      break;
    }
  } while (--Timeout > 0);

  return Timeout;
}

/**
  Initializes the RTC.

  @retval Nothing.
**/
void
InitRtc (
  void
  )
{
  MrcOemOutPort8 (RTC_INDEX_REGISTER, CMOS_REGB);
  MrcOemOutPort8 (RTC_TARGET_REGISTER, RTC_HOLD | RTC_MODE_24HOUR);

  MrcOemOutPort8 (RTC_INDEX_REGISTER, CMOS_REGA);
  MrcOemOutPort8 (RTC_TARGET_REGISTER, RTC_CLOCK_DIVIDER | RTC_RATE_SELECT);

  MrcOemOutPort8 (RTC_INDEX_REGISTER, CMOS_REGC);
  MrcOemInPort8 (RTC_TARGET_REGISTER);

  MrcOemOutPort8 (RTC_INDEX_REGISTER, CMOS_REGD);
  MrcOemInPort8 (RTC_TARGET_REGISTER);

  MrcOemOutPort8 (RTC_INDEX_REGISTER, CMOS_REGB);
  MrcOemOutPort8 (RTC_TARGET_REGISTER, RTC_MODE_24HOUR);

  return;
}

/**
  Read specific RTC/CMOS RAM

  @param[in] Location        Point to RTC/CMOS RAM offset for read

  @retval The data of specific location in RTC/CMOS RAM.
**/
UINT8
RtcRead (
  IN const UINT8 Location
  )
{
  UINT8  RtcIndexPort;
  UINT8  RtcDataPort;

  //
  // CMOS access registers (using alternative access not to handle NMI bit)
  //
  if (Location < RTC_BANK_SIZE) {
    //
    // First bank
    //
    RtcIndexPort  = R_PCH_RTC_INDEX_ALT;
    RtcDataPort   = R_PCH_RTC_TARGET_ALT;
  } else {
    //
    // Second bank
    //
    RtcIndexPort  = R_PCH_RTC_EXT_INDEX_ALT;
    RtcDataPort   = R_PCH_RTC_EXT_TARGET_ALT;
  }

  MrcOemOutPort8 (RtcIndexPort, Location & RTC_INDEX_MASK);
  return MrcOemInPort8 (RtcDataPort);
}

/**
  Returns the current time, as determined by reading the Real Time Clock (RTC) on the platform.
  Since RTC time is stored in BCD, convert each value to binary.

  @param[out] Seconds       - The current second (0-59).
  @param[out] Minutes       - The current minute (0-59).
  @param[out] Hours         - The current hour (0-23).
  @param[out] DayOfMonth    - The current day of the month (1-31).
  @param[out] Month         - The current month (1-12).
  @param[out] Year          - The current year (2000-2099).

  @retval Nothing.
**/
void
GetRtcTime (
  OUT UINT8  *const Seconds,
  OUT UINT8  *const Minutes,
  OUT UINT8  *const Hours,
  OUT UINT8  *const DayOfMonth,
  OUT UINT8  *const Month,
  OUT UINT16 *const Year
  )
{
  if (0 == CheckUpdateComplete ()) {
    InitRtc ();
  }
  //
  // Read seconds
  //
  MrcOemOutPort8 (RTC_INDEX_REGISTER, RTC_SECONDS);
  *Seconds = MrcOemInPort8 (RTC_TARGET_REGISTER);

  //
  // Read minutes
  //
  MrcOemOutPort8 (RTC_INDEX_REGISTER, RTC_MINUTES);
  *Minutes = MrcOemInPort8 (RTC_TARGET_REGISTER);

  //
  // Read hours
  //
  MrcOemOutPort8 (RTC_INDEX_REGISTER, RTC_HOURS);
  *Hours = MrcOemInPort8 (RTC_TARGET_REGISTER);

  //
  // Read day of month
  //
  MrcOemOutPort8 (RTC_INDEX_REGISTER, RTC_DAY_OF_MONTH);
  *DayOfMonth = MrcOemInPort8 (RTC_TARGET_REGISTER);

  //
  // Read month
  //
  MrcOemOutPort8 (RTC_INDEX_REGISTER, RTC_MONTH);
  *Month = MrcOemInPort8 (RTC_TARGET_REGISTER);

  //
  // Read year and add current century.
  //
  MrcOemOutPort8 (RTC_INDEX_REGISTER, RTC_YEAR);
  *Year = MrcOemInPort8 (RTC_TARGET_REGISTER);

  *Seconds    = BCD2BINARY (*Seconds);
  *Minutes    = BCD2BINARY (*Minutes);
  *Hours      = BCD2BINARY (*Hours);
  *DayOfMonth = BCD2BINARY (*DayOfMonth);
  *Month      = BCD2BINARY (*Month);
  *Year       = BCD2BINARY (*Year) + CENTURY_OFFSET;
}

/**
  Write specific RTC/CMOS RAM

  @param[in] Location        Point to RTC/CMOS RAM offset for write
  @param[in] Value           The data that will be written to RTC/CMOS RAM
**/
void
RtcWrite (
  IN const UINT8 Location,
  IN const UINT8 Value
  )
{
  UINT8  RtcIndexPort;
  UINT8  RtcDataPort;

  //
  // CMOS access registers (using alternative access not to handle NMI bit)
  //
  if (Location < RTC_BANK_SIZE) {
    //
    // First bank
    //
    RtcIndexPort  = R_PCH_RTC_INDEX_ALT;
    RtcDataPort   = R_PCH_RTC_TARGET_ALT;
  } else {
    //
    // Second bank
    //
    RtcIndexPort  = R_PCH_RTC_EXT_INDEX_ALT;
    RtcDataPort   = R_PCH_RTC_EXT_TARGET_ALT;
  }

  MrcOemOutPort8 (RtcIndexPort, Location & RTC_INDEX_MASK);
  MrcOemOutPort8 (RtcDataPort, Value);
}

/**
  Read word from specific RTC/CMOS RAM

  @param[in] Location        Point to RTC/CMOS RAM offset for read

  @retval The data of specific location in RTC/CMOS RAM.
**/
UINT16
RtcRead16 (
  IN const UINT8 Location
  )
{
  return RtcRead (Location) | (RtcRead (Location + 1) << 8);
}

/**
  Write word to specific RTC/CMOS RAM

  @param[in] Location        Point to RTC/CMOS RAM offset for write
  @param[in] Value           The data that will be written to RTC/CMOS RAM
**/
void
RtcWrite16 (
  IN const UINT8   Location,
  IN const UINT16  Value
  )
{
  RtcWrite (Location, (UINT8) Value);
  RtcWrite (Location + 1, (UINT8) (Value >> 8));
}

/**
  Gets CPU ratio

  @retval Cpu ratio.
**/
UINT32
MrcGetCpuRatio (
  void
  )
{
  PCU_CR_PLATFORM_INFO_STRUCT Msr;

  Msr.Data = AsmReadMsr64 (PCU_CR_PLATFORM_INFO);
  return (Msr.Bits.MAX_NON_TURBO_LIM_RATIO);
}

/**
  Gets CPU current time.

  @param[in] GlobalData - Pointer to global MRC data struct.

  @retval The current CPU time in milliseconds.
**/
UINT64
GetCpuTime (
  IN VOID     *GlobalData
  )
{
  MrcParameters   *MrcData;
  UINT32          TimeBase;

  MrcData = (MrcParameters *) GlobalData;

  TimeBase = (MrcData->Inputs.BClkFrequency / 1000) * MrcGetCpuRatio (); //In Millisec
  return ((TimeBase == 0) ? 0 : MrcOemMemoryDivideU64ByU64 (AsmReadTsc (), TimeBase));
}

/**
  Copy the specified number of memory bytes, a byte at a time, from the
  specified source to the specified destination.

  @param[in, out] Dest            - Destination pointer.
  @param[in]      Src             - Source pointer.
  @param[in]      NumBytes        - The number of bytes to copy.

  @retval Nothing.
**/
void
MrcOemMemoryCpy (
  IN OUT UINT8 *Dest,
  IN UINT8     *Src,
  IN UINT32    NumBytes
  )
{
  CopyMem (Dest, Src, NumBytes);
}

/**
  Sets the specified number of memory bytes, a byte at a time, at the
  specified destination.

  @param[in, out] Dest            - Destination pointer.
  @param[in]      Value           - The value to set.
  @param[in]      NumBytes        - The number of bytes to set.

  @retval Nothing.
**/
void
MrcOemMemorySet (
  IN OUT UINT8 *Dest,
  IN UINT32    NumBytes,
  IN UINT32    Value
  )
{
  SetMem ((UINT8 *) Dest, NumBytes, (UINT8) Value);
}

/**
  Sets the specified number of memory dwords, a dword at a time, at the
  specified destination.

  @param[in, out] Dest            - Destination pointer.
  @param[in]      Value           - The value to set.
  @param[in]      NumWords        - The number of dwords to set.

  @retval Nothing.
**/
void
SetMemWord (
  IN OUT UINT16    *Dest,
  IN UINT32        NumWords,
  IN const UINT16  Value
  )
{
  while (0 != NumWords--) {
    *Dest++ = Value;
  }

  return;
}

/**
  Sets the specified number of memory dwords, a dword at a time, at the
  specified destination.

  @param[in, out] Dest            - Destination pointer.
  @param[in]      Value           - The value to set.
  @param[in]      NumDwords       - The number of dwords to set.

  @retval Nothing.
**/
void
SetMemDword (
  IN OUT UINT32    *Dest,
  IN UINT32        NumDwords,
  IN const UINT32  Value
  )
{
  while (0 != NumDwords--) {
    *Dest++ = Value;
  }

  return;
}

/**
  Read 64 bits from the Memory Mapped I/O space.
  Use MMX instruction for atomic access, because some MC registers have side effect.

  @param[in] Address - Memory mapped I/O address.

  @retval The 64 bit value read from the memory mapped I/O space.
**/
UINT64
SaMmioRead64 (
  IN  UINT32 Address
  )
{
  UINT64 *MmioOffset;
  UINT64 *Pointer;
  UINT64 MmxSave;
  UINT64 Value;

  MmxSave    = 0;
  MmioOffset = (UINT64 *) Address;
  Pointer    = &Value;
#if defined __GNUC__  // GCC compiler
  __asm__ __volatile__ (
   "movq   %%mm0,%[MmxSave]\n\
    mov    %[MmioOffset],%%edi\n\
    movq   %%ds:(%%edi),%%mm0\n\
    mov    %[Pointer],%%edi\n\
    movq   %%mm0,%%ds:(%%edi)\n\
    movq   %[MmxSave],%%mm0\n\
    emms"
  : [MmxSave]"=m"(MmxSave), [Pointer]"=m"(Pointer)
  : [MmioOffset]"m"(MmioOffset)
  : "%edi"
  );
#else // MSFT compiler
  ASM {
    ; Save mm0
    movq  MmxSave, mm0
    mov   edi, MmioOffset
    movq  mm0, QWORD PTR DS:[edi]
    mov   edi, Pointer
    movq  QWORD PTR DS:[edi], mm0

    ; Restore mm0
    movq  mm0, MmxSave
    emms                     ; Exit mmx Instruction
  }
#endif
  return (Value);
}

/**
  Write 64 bits to the Memory Mapped I/O space.
  Use MMX instruction for atomic access, because some MC registers have side effect.

  @param[in] Address - Memory mapped I/O address.
  @param[in] Value   - The value to write.

  @retval The 64 bit value written to the memory mapped I/O space.
**/
UINT64
SaMmioWrite64 (
  IN UINT32 Address,
  IN UINT64 Value
  )
{
  UINT64 MmxSave;
  UINT64 *MmioOffset;

  MmxSave    = 0;
  MmioOffset = (UINT64 *) (Address);

#if defined __GNUC__  // GCC compiler
  __asm__ __volatile__ (
   "movq   %%mm0,%[MmxSave]\n\
    mov    %[MmioOffset],%%edi\n\
    movq   %[Value],%%mm0\n\
    movq   %%mm0,%%ds:(%%edi)\n\
    movq   %[MmxSave],%%mm0\n\
    emms"
  :
  : [MmxSave]"m"(MmxSave), [MmioOffset]"m"(MmioOffset), [Value]"m"(Value)
  : "%edi"
  );
#else //MSFT compiler
  ASM {
    ; Save mm0
    movq  MmxSave, mm0
    mov   edi, MmioOffset
    movq  mm0, Value
    movq  QWORD PTR DS:[edi], mm0

    ; Restore mm0
    movq  mm0, MmxSave
    emms                     ; Exit mmx Instruction
  }
#endif
  return (Value);
}

/**
  Shift the specified data value left by the specified count.

  @param[in] Data            - 64 bit number to shift left.
  @param[in] Count           - Number of bits to shift (0..63)

  @retval The number of bits shifted left.
**/
UINT64
MrcOemMemoryLeftShiftU64 (
  IN const UINT64 Data,
  IN const UINT8  Count
  )
{
  return LShiftU64 (Data, Count);
}

/**
  Shift the specified data value Right by the specified count.

  @param[in] Data            - UINT64 number to shift
  @param[in] Count           - number of bits to shift (0..63)

  @retval Returns the shifted UINT64 value.
**/
UINT64
MrcOemMemoryRightShiftU64 (
  IN const UINT64 Data,
  IN const UINT8  Count
  )
{
  return RShiftU64 (Data, Count);
}

/**
  this function Multiply UINT64 with a UINT32 number. Result is <= 64 bits
  need to be port for OEM platform requirements.

  @param[in] Multiplicand  - UINT64 number to be multiplied with
  @param[in] Multiplier - UINT32 number to multiply

  @retval The input data value shifted right by count.
**/
UINT64
MrcOemMemoryMultiplyU64ByU32 (
  IN const UINT64 Multiplicand,
  IN const UINT32 Multiplier
  )
{
  return MultU64x32 (Multiplicand, Multiplier);
}

/**
  Divide UINT64 with a UINT64 number. Result is <= 32 bits

  @param[in] Dividend  - UINT64 number to be multiplied with
  @param[in] Divisor - UINT32 number to multiply

  @retval Returns the quotient result of UINT32 value.
**/
UINT64
MrcOemMemoryDivideU64ByU64 (
  IN const UINT64 Dividend,
  IN const UINT64 Divisor
  )
{
  return (DivU64x64Remainder (Dividend, Divisor, NULL));
}

/**
  Read 64 bits from the Memory Mapped I/O space.

  @param[in] Address - The address of the MMIO location.

  @retval The 64-bit value read from the Memory Mapped I/O space.
**/
UINT64
MrcOemMmioRead64 (
  IN  UINT32 Address
  )
{
  MmioReadCount ();
  return (SaMmioRead64 (Address));
}

/**
  Read 32 bits from the Memory Mapped I/O space.

  @param[in]  Offset      - Offset from the specified base address.

  @retval The 32 bit value read from the Memory Mapped I/O space.
**/
UINT32
MrcOemMmioRead32 (
  IN  UINT32 Offset
  )
{
  MmioReadCount ();
  return (*((volatile UINT32 *) (Offset)));
}

/**
  Read 16 bits from the Memory Mapped I/O space.

  @param[in]  Offset      - Offset from the specified base address.

  @retval The 16 bit value read from the Memory Mapped I/O space.
**/
UINT16
MrcOemMmioRead16 (
  IN  UINT32 Offset
  )
{
  MmioReadCount ();
  return (*((volatile UINT16 *) (Offset)));
}

/**
  Read 8 bits from the Memory Mapped I/O space.

  @param[in]  Offset      - Offset from the specified base address.

  @retval The 8 bit value read from the Memory Mapped I/O space.
**/
UINT8
MrcOemMmioRead8 (
  IN  UINT32 Offset
  )
{
  MmioReadCount ();
  return (*((volatile UINT8 *) (Offset)));
}

/**
  Write 64 bits to the Memory Mapped I/O space.

  @param[in] Address - The address of the MMIO location.
  @param[in] Value   - The value to write.

  @retval Nothing.
**/
UINT64
MrcOemMmioWrite64 (
  IN UINT32 Address,
  IN UINT64 Value
  )
{
  MmioWriteCount ();
  return (SaMmioWrite64 (Address, Value));
}

/**
  Write 32 bits to the Memory Mapped I/O space.

  @param[in] Offset      - Offset from the specified base address.
  @param[in] Value       - The value to write.

  @retval Nothing.
**/
UINT32
MrcOemMmioWrite32 (
  IN UINT32 Offset,
  IN UINT32 Value
  )
{
  (*((volatile UINT32 *) (Offset))) = Value;
  MmioWriteCount ();
  return (Value);
}

/**
  Write 16 bits to the Memory Mapped I/O space.

  @param[in] Offset      - Offset from the specified base address.
  @param[in] Value       - The value to write.

  @retval Nothing.
**/
UINT16
MrcOemMmioWrite16 (
  IN UINT32 Offset,
  IN UINT16 Value
  )
{
  (*((volatile UINT16 *) (Offset))) = Value;
  MmioWriteCount ();
  return (Value);
}

/**
  Write 8 bits to the Memory Mapped I/O space.

  @param[in] Offset      - Offset from the specified base address.
  @param[in] Value       - The value to write.

  @retval Nothing.
**/
UINT8
MrcOemMmioWrite8 (
  IN UINT32 Offset,
  IN UINT8  Value
  )
{
  (*((volatile UINT8 *) (Offset))) = Value;
  MmioWriteCount ();
  return (Value);
}

/**
  Sets CpuModel and CpuStepping in MrcData based on CpuModelStep.

  @param[out] MrcData     - The Mrc Host data structure
  @param[in]  CpuModel    - The CPU Family Model.
  @param[in]  CpuStepping - The CPU Stepping.

  @retval mrcSuccess if the model and stepping is found.  Otherwise mrcFail
**/
MrcStatus
MrcSetCpuInformation (
  OUT MrcParameters  *MrcData,
  IN  MrcCpuModel    CpuModel,
  IN  MrcCpuStepping CpuStepping
  )
{
  const MRC_FUNCTION  *MrcCall;
  MrcInput            *Inputs;
  MrcDebug            *Debug;
  MrcStatus           Status;
  char                *Step;
  UINT64              Revision;

  Inputs  = &MrcData->Inputs;
  MrcCall = Inputs->Call.Func;
  Debug   = &MrcData->Outputs.Debug;
  Status  = mrcFail;

  Inputs->CpuFamily = cfMax;
  Step = NULL;

  switch (CpuModel) {
    case cmKBL_ULX_ULT:
      Inputs->CpuModel = cmKBL_ULX_ULT;
      Inputs->CpuFamily = cfKbl;
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Kabylake ULT/ULX:");

      switch (CpuStepping) {
        case csKblH0:
          Inputs->CpuStepping = csKblH0;
          Step = "H0/J0";
          break;

        case csKblY0:
          Inputs->CpuStepping = csKblY0;
          Step = "Y0";
          break;

        case csAmlW0:
          Inputs->CpuStepping = csAmlW0;
          Step = "W0";
          break;

        case csAmlV0:
          Inputs->CpuStepping = csAmlV0;
          Step = "V0";
          break;

        default:
          Inputs->CpuStepping = csKblUlxUltLast;
          break;
      }
      Status = mrcSuccess;
      break;

    case cmSKL_ULX_ULT:
      Inputs->CpuModel = cmSKL_ULX_ULT;
      if (CpuStepping > csSklUlxUltLast) {
        Inputs->CpuFamily = cfKbl;
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Kabylake ULT/ULX:");

        switch (CpuStepping) {
          case csKblG0:
            Inputs->CpuStepping = csKblG0;
            Step = "G0";
            break;

          default:
            Inputs->CpuStepping = csKblUlxUltLast;
            break;
        }
      } else {
        Inputs->CpuFamily = cfSkl;
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Skylake ULT/ULX:");

        switch (CpuStepping) {
          case csSklB0:
            Inputs->CpuStepping = csSklB0;
            Step = "B0";
            break;

          case csSklC0:
            Inputs->CpuStepping = csSklC0;
            Step = "C0/J0";
            break;

          case csSklD0:
            Inputs->CpuStepping = csSklD0;
            Step = "D0/K0";
            break;

          default:
            Inputs->CpuStepping = csSklUlxUltLast;
            break;
        }
      }
      Status = mrcSuccess;
      break;


    case cmKBL_DT_HALO:
      Inputs->CpuModel = cmKBL_DT_HALO;
      Inputs->CpuFamily = cfKbl;
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Kabylake DT/Halo:");

      switch (CpuStepping) {
        case csKblB0:
          Inputs->CpuStepping = csKblB0;
          Step = "B0/S0/M0";
          break;

        case csKblN0:
          Inputs->CpuStepping = csKblN0;
          Step = "N0";
          break;

        case csCflB0:
          Inputs->CpuStepping = csCflB0;
          Step = "B0";
          break;

        case csCflP0:
          Inputs->CpuStepping = csCflP0;
          Step = "P0";
          break;

        case csCflR0:
          Inputs->CpuStepping = csCflR0;
          Step = "R0";
          break;

        default:
          Inputs->CpuStepping = csKblDtHaloLast;
          break;
      }
      Status = mrcSuccess;
      break;

    case cmSKL_DT_HALO:
      Inputs->CpuModel = cmSKL_DT_HALO;
      if (CpuStepping > csSklDtHaloLast) {
        Inputs->CpuFamily = cfKbl;
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Kabylake DT/Halo:");

        switch (CpuStepping) {
          case csKblA0:
            Inputs->CpuStepping = csKblA0;
            Step = "A0";
            break;

          default:
            Inputs->CpuStepping = csKblDtHaloLast;
            break;
        }
      } else {
        Inputs->CpuFamily = cfSkl;
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Skylake DT/Halo:");

        switch (CpuStepping) {
          case csSklP0:
            Inputs->CpuStepping = csSklP0;
            Step = "P0";
            break;

          case csSklQ0:
            Inputs->CpuStepping = csSklQ0;
            Step = "Q0";
            break;

          case csSklM0:
            Inputs->CpuStepping = csSklM0;
            Step = "M0";
            break;

          case csSklR0:
            Inputs->CpuStepping = csSklR0;
            Step = "R0/S0/N0";
            break;

          default:
            Inputs->CpuStepping = csSklDtHaloLast;
            break;
        }
      }
      Status = mrcSuccess;
      break;
  }

  if (Status == mrcSuccess) {
    if (Step != NULL) {
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, " Stepping %s\n", Step);
    } else {
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_WARNING, "\nWARNING: Unknown CPU stepping, using MRC for last known step = %Xh\n", Inputs->CpuStepping);
    }
  }

  Revision = MrcCall->MrcReadMsr64 (MSR_IA32_BIOS_SIGN_ID);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Microcode Update: 0x%08X\n", (UINT32) (MrcCall->MrcRightShift64 (Revision, 32)));

  return Status;
}

/**
  Gets a number from the CPU's random number generator.

  @param[in] Nothing

  @retval Random number or zero if random number is not generated or is invalid.
**/
static
UINT32
RandomNumber (
  void
  )
{
  UINT32 Random;

  //MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Generating Random number...\n");

  // Assembly instruction to read CPU's random number generator
  // Instruction is only available 100k cycles after reset
  // rdrand eax
  // db 0Fh, 0C7h, 0F0h
#if defined __GNUC__  // GCC compiler
  __asm__ __volatile__ (
    "\n\t clc"
    "\n\t 1:"
    "\n\t .byte 0x0F, 0xC7, 0xF0"
    "\n\t movl %%eax, %[Random]"
    "\n\t jnc 1b"
    : [Random] "=m" (Random)
    );
#else //MSFT compiler
  ASM {
    clc
tryAgain:
    _emit   0x0F
    _emit   0xC7
    _emit   0xF0
    mov     Random, eax
    jnc     tryAgain        ; CF will be set if valid number was generated
  }
#endif
  //MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Exiting Random number: %08Xh\n", Random);

  return (Random);
}

/**
  Generates a 32-bit random number.

  if Rand is NULL, then ASSERT().

  @param[out] Rand     Buffer pointer to store the 32-bit random value.

  @retval TRUE         Random number generated successfully.
  @retval FALSE        Failed to generate the random number.

**/
BOOLEAN
GetRandomNumber32 (
  OUT     UINT32                    *Rand
  )
{
  UINT32 Random;
  UINT32 Retry;

  Random = 0;
  ///
  /// Exclude zero case, although it is still valid, but not prefered for scrambler seed application
  ///
  for (Retry = 100000; ((Retry != 0) && (Random == 0)); --Retry) {
    Random = RandomNumber ();
  }

  *Rand = Random;

  if (Random == 0) {
    return FALSE;
  } else {
    return TRUE;
  }
}

/**
  Assembly code to read an MSR

  @param[in] Address

  @retval The MSR value.
**/
static
UINT64
AsmReadMsr (
  UINT32 Address
  )
{
#ifdef __GNUC__  // GCC compiler
  UINT32 LowData;
  UINT32 HighData;

  __asm__ __volatile__ (
    "rdmsr"
    : "=a" (LowData),   // %0
      "=d" (HighData)   // %1
    : "c"  (Address)    // %2
    );
    
  return (((UINT64) HighData) << 32) | LowData;
#else
  // Assembly instruction to read MSR
  union {
    UINT64 Data;
    UINT32 Data32[2];
  } Buffer;
  UINT32 DataEdx;
  UINT32 DataEax;

  ASM {
    mov     ecx, Address
    rdmsr
    mov     DataEax, eax
    mov     DataEdx, edx
  }
  Buffer.Data32[0] = DataEax;
  Buffer.Data32[1] = DataEdx;
  return (Buffer.Data);
#endif
}

/**
  Read an MSR

  @param[in] Address

  @retval The MSR value.
**/
UINT64
ReadMsr64 (
  UINT32 Address
  )
{
  return (AsmReadMsr (Address));
}

/**
  Assembly code to write an MSR

  @param[in] Address
  @param[in] Data

  @retval Nothing.
**/
static
void
AsmWriteMsr (
  UINT32 Address,
  UINT64 Data
  )
{
#ifdef __GNUC__  // GCC compiler
  UINT32 LowData;
  UINT32 HighData;

  LowData  = (UINT32) (Data);
  HighData = (UINT32) (Data >> 32);

  __asm__ __volatile__ (
    "wrmsr"
    :
    : "c" (Address),
      "a" (LowData),
      "d" (HighData)
    );
#else
  union {
    UINT64 Data;
    UINT32 Data32[2];
  } Buffer;
  UINT32 DataEdx;
  UINT32 DataEax;

  Buffer.Data = Data;
  DataEax = Buffer.Data32[0];
  DataEdx = Buffer.Data32[1];
  // Assembly instruction to read MSR
  ASM {
    mov     ecx, Address
    mov     eax, DataEax
    mov     edx, DataEdx
    wrmsr
  }
#endif
  return;
}

/**
  Write an MSR

  @param[in] Address
  @param[in] Data

  @retval Data written to MSR
**/
UINT64
WriteMsr64 (
  UINT32 Address,
  UINT64 Data
  )
{
  AsmWriteMsr (Address, Data);
  return Data;
}

/**
  Initialize GPIO

  @param[in]  MrcData - Include all MRC global data
**/
void
MrcOemGpioInit (
  MrcParameters *const  MrcData
  )
{
  const MrcInput  *Inputs;
  UINT32          PciEBaseAddress;
  UINT16          LpcDeviceId;
  UINT32          GpioBase;
  UINT32          Data32;
  UINT32          Offset;

  Inputs          = &MrcData->Inputs;
  PciEBaseAddress = Inputs->PciEBaseAddress;
  LpcDeviceId = MrcOemMmioRead16 (PciEBaseAddress + GetPcieDeviceAddress (0, PCI_DEVICE_NUMBER_PCH_LPC, PCI_FUNCTION_NUMBER_PCH_LPC, R_PCH_LPC_DEVICE_ID));
  if (MrcGetPchType () == PchTypeLpt) {
    if (IS_PCH_LPC_DEVICE_ID_DESKTOP (LpcDeviceId) || IS_PCH_LPTH_LPC_DEVICE_ID_MOBILE (LpcDeviceId)) {
      //
      // PineValley/RVP9/RVP10 with SKL use GP11 as DRAM_RESET#
      // Set it to GPIO/Output/High
      //
      Offset    = PciEBaseAddress + GetPcieDeviceAddress (0, PCI_DEVICE_NUMBER_PCH_LPC, PCI_FUNCTION_NUMBER_PCH_LPC, R_PCH_LPC_GPIO_BASE);
      GpioBase  = MrcOemMmioRead32 (Offset) & B_PCH_LPC_GPIO_BASE_BAR;

      Data32  = MrcOemInPort32 (GpioBase + R_PCH_GPIO_USE_SEL); // 0 - Native, 1 - GPIO
      Data32 |= MRC_BIT11;
      MrcOemOutPort32 (GpioBase + R_PCH_GPIO_USE_SEL, Data32);

      Data32  = MrcOemInPort32 (GpioBase + R_PCH_GPIO_IO_SEL); // 0 - Output, 1 - Input
      Data32 &= ~(MRC_BIT11);
      MrcOemOutPort32 (GpioBase + R_PCH_GPIO_IO_SEL, Data32);

      Data32  = MrcOemInPort32 (GpioBase + R_PCH_GPIO_LVL); // High - DRAM_RESET# deasserted
      Data32 |= MRC_BIT11;
      MrcOemOutPort32 (GpioBase + R_PCH_GPIO_LVL, Data32);
    }
  }
}

/**
  Assert or deassert DRAM_RESET# pin; this is used in JEDEC Reset.

  @param[in] PciEBaseAddress  - PCI express base address.
  @param[in] ResetValue       - desired value of DRAM_RESET#. 1 - reset deasserted, 0 - reset asserted.
**/
void
MrcOemDramReset (
  UINT32 PciEBaseAddress,
  UINT32 ResetValue
  )
{
  UINT16                                  LpcDeviceId;
  UINT32                                  GpioBase;
  UINT32                                  Gpio31_0;
  UINT32                                  MmioBase;
  UINT32                                  PmCfg2;
  UINT32                                  Offset;


  if (MrcGetPchType () == PchTypeLpt) {
    LpcDeviceId = MrcOemMmioRead16 (PciEBaseAddress + GetPcieDeviceAddress (0, PCI_DEVICE_NUMBER_PCH_LPC, PCI_FUNCTION_NUMBER_PCH_LPC, R_PCH_LPC_DEVICE_ID));
    if (IS_PCH_LPC_DEVICE_ID_DESKTOP (LpcDeviceId) || IS_PCH_LPTH_LPC_DEVICE_ID_MOBILE (LpcDeviceId)) {
      //
      // On RVP10 ERB we have LPT-H interposer, so use GP15 as DRAM_RESET#
      // RVP10 with SKL uses GP11
      //
      Offset    = PciEBaseAddress + GetPcieDeviceAddress (0, PCI_DEVICE_NUMBER_PCH_LPC, PCI_FUNCTION_NUMBER_PCH_LPC, R_PCH_LPC_GPIO_BASE);
      GpioBase  = MrcOemMmioRead32 (Offset) & B_PCH_LPC_GPIO_BASE_BAR;
      Gpio31_0  = MrcOemInPort32 (GpioBase + R_PCH_GPIO_LVL);
      Gpio31_0 &= ~(MRC_BIT11);
      Gpio31_0 |= (ResetValue << 11);
      MrcOemOutPort32 (GpioBase + R_PCH_GPIO_LVL, Gpio31_0);
    } else {
      //
      // Get the PCH RCBA from 0:1F:0:F0, and clear the Enable bit
      //
      Offset = PciEBaseAddress + GetPcieDeviceAddress (0, PCI_DEVICE_NUMBER_PCH_LPC, PCI_FUNCTION_NUMBER_PCH_LPC, R_PCH_LPC_RCBA);
      MmioBase = MrcOemMmioRead32 (Offset) & ~(B_PCH_LPC_RCBA_EN);

      //
      // Set DRAM RESET# value via PCH register (LPT-LP)
      //
      PmCfg2 = MrcOemMmioRead32 (MmioBase + R_PCH_RCRB_PM_CFG2);
      PmCfg2 &= ~(B_PCH_RCRB_PM_CFG2_DRAM_RESET_CTL);
      PmCfg2 |= (ResetValue << 26);
      MrcOemMmioWrite32 (MmioBase + R_PCH_RCRB_PM_CFG2, PmCfg2);
    }
  } else { // SPT
    //
    // Get the PCH PWRM Base from 0:1F:2:48, and clear the Enable bit
    //
    Offset = PciEBaseAddress + GetPcieDeviceAddress (0, PCI_DEVICE_NUMBER_PCH_PMC, PCI_FUNCTION_NUMBER_PCH_PMC, R_PCH_PMC_PWRM_BASE);
    MmioBase = MrcOemMmioRead32 (Offset) & B_PCH_PMC_PWRM_BASE_BAR;
    //
    // Set DRAM RESET# value via PCH register (both SKL PCH-H and SKL PCH-LP)
    //
    PmCfg2 = MrcOemMmioRead32 (MmioBase + R_PCH_PWRM_CFG2);
    PmCfg2 &= ~(B_PCH_PWRM_CFG2_DRAM_RESET_CTL);
    PmCfg2 |= (ResetValue << 26);
    MrcOemMmioWrite32 (MmioBase + R_PCH_PWRM_CFG2, PmCfg2);
  }
  return;
}

/**
  Gets the current memory voltage (VDD).

  @param[in] GlobalData - Pointer to global MRC data struct.
  @param[in] DefaultVdd - Default Vdd for the given platform.

  @retval The current memory voltage (VDD), in millivolts. 0 means platform default.
**/
UINT32
GetMemoryVdd (
  IN VOID     *GlobalData,
  IN UINT32   DefaultVdd
  )
{
  MrcParameters   *MrcData;
  UINT32          CurrentVoltage;

  MrcData = (MrcParameters *) GlobalData;
  CurrentVoltage = DefaultVdd;

  return CurrentVoltage;
}

/**
  Sets the memory voltage (VDD) to the specified value.

  @param[in] GlobalData - Pointer to global MRC data struct.
  @param[in] DefaultVdd - Default Vdd for the given platform.
  @param[in] Voltage    - The new memory voltage to set.

  @retval The actual memory voltage (VDD), in millivolts, that is closest to what the caller passed in.
**/
UINT32
SetMemoryVdd (
  IN VOID     *GlobalData,
  IN UINT32   DefaultVdd,
  IN UINT32   Voltage
  )
{
  MrcParameters   *MrcData;

  MrcData = (MrcParameters *) GlobalData;

  return Voltage;
}

/**
  Hook before normal mode is enabled.

  @param[in, out] MrcData  - The MRC "global data" area.

  @retval Nothing.
**/
void
MrcOemBeforeNormalModeTestMenu (
  IN OUT MrcParameters *const MrcData
  )
{
  return;
}

/**
  This function is used by the Mini-BIOS to do dedicated task during the MRC.

  @param[in] MrcData           - include all the MRC data
  @param[in] OemStatusCommand  - A command that indicates the task to perform.
  @param[in] Pointer           - general ptr for general use.

  @retval The status of the task.
**/
MrcStatus
CheckPoint (
  IN MrcParameters        *MrcData,
  IN MrcOemStatusCommand OemStatusCommand,
  IN void                 *Pointer
  )
{
  MrcStatus Status;

  Status = mrcSuccess;

  switch (OemStatusCommand) {
    case OemAfterNormalMode:
      MrcThermalOverrides (MrcData);
      break;

    default:
      break;
  }

  return (Status);
}

/**
  This function display on port 80 number.
  It can be different debug interface.
  This function can be use for any debug ability according to OEM requirements.

  @param[in] MrcData            - Mrc Global Data
  @param[in] DisplayDebugNumber - the number to display on port 80.

  @retval Nothing
**/
void
MrcOemDebugHook (
  IN MrcParameters *MrcData,
  IN UINT16        DisplayDebugNumber
  )
{
  MrcDebug  *Debug;
  UINT16       BreakCmos;
  BOOLEAN      MessagePrinted;

  Debug                          = &MrcData->Outputs.Debug;
  Debug->PostCode[MRC_POST_CODE] = DisplayDebugNumber;
  MrcOemOutPort16 (0x80, DisplayDebugNumber);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Post Code: %Xh\n", DisplayDebugNumber);

  //
  // Put the Port80 code also here:
  // #define NCDECS_CR_SCRATCHPAD_NCU_0_REG          (0x00005428)
  //
  MrcWriteCR (MrcData, NCDECS_CR_SCRATCHPAD_NCU_0_REG, DisplayDebugNumber);

  //
  // Check if we should break on this post code.
  //
  MessagePrinted = FALSE;
  do {
    BreakCmos = (RtcRead (MRC_POST_CODE_HIGH_BYTE_ADDR) << 8) | RtcRead (MRC_POST_CODE_LOW_BYTE_ADDR);
    if ((DisplayDebugNumber == BreakCmos) && !MessagePrinted) {
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "------------------------------------------\n");
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "-- Stopped on CMOS POST code breakpoint --\n");
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "------------------------------------------\n");
      MessagePrinted = TRUE;
    }
  } while (DisplayDebugNumber == BreakCmos);

  return;
}

#if (defined MEMORY_DOWN_SUPPORT && (MEMORY_DOWN_SUPPORT > 0))

/******************************************************************************
  Memory down configuration code starts here.
  Add SPD, and channel/slot population settings here.

  Even though this is a memory down configuration, the MRC needs to know how
  the memory appears to the controller, so indicate here which channels are
  populated. Also, the MRC needs to know which slots are valid, even though
  there are technically no physical slots in a memory down configuration.
  The MRC also needs a valid SPD data for the configuration.
******************************************************************************/
///
/// Example board support
///
#define EXAMPLE_BOARD_SUPPORT 0
#if (defined EXAMPLE_BOARD_SUPPORT && (EXAMPLE_BOARD_SUPPORT > 0))
///
/// For this example board, we have a dual channel, single slot configuration
/// with the same memory configuration in each channel (DDR3).
///
const MemorySlotStatus ExampleSlotStatus[MAX_CHANNEL][MAX_DIMMS_IN_CHANNEL] = {
  MEMORY_DOWN_ONLY,                     ///< Channel 0, Slot 0
  MEMORY_ABSENT,                        ///< Channel 0, Slot 1
  MEMORY_DOWN_ONLY,                     ///< Channel 1, Slot 0
  MEMORY_ABSENT,                        ///< Channel 1, Slot 1
};

const UINT8 ExampleSpd[] = {
  0x92,                                 ///< 0   Number of Serial PD Bytes Written / SPD Device Size / CRC Coverage 1, 2
  0x10,                                 ///< 1   SPD Revision
  0x0B,                                 ///< 2   DRAM Device Type
  0x03,                                 ///< 3   Module Type
  0x02,                                 ///< 4   SDRAM Density and Banks
  0x11,                                 ///< 5   SDRAM Addressing
  0x00,                                 ///< 6   Module Nominal Voltage
  0x09,                                 ///< 7   Module Organization
  0x03,                                 ///< 8   Module Memory Bus Width
  0x52,                                 ///< 9   Fine Timebase (FTB) Dividend / Divisor
  0x01,                                 ///< 10  Medium Timebase (MTB) Dividend
  0x08,                                 ///< 11  Medium Timebase (MTB) Divisor
  0x0A,                                 ///< 12  SDRAM Minimum Cycle Time (tCKmin)
  0x00,                                 ///< 13  Reserved0
  0xFE,                                 ///< 14  CAS Latencies Supported, Least Significant Byte
  0x00,                                 ///< 15  CAS Latencies Supported, Most Significant Byte
  0x69,                                 ///< 16  Minimum CAS Latency Time (tAAmin)
  0x78,                                 ///< 17  Minimum Write Recovery Time (tWRmin)
  0x69,                                 ///< 18  Minimum RAS# to CAS# Delay Time (tRCDmin)
  0x30,                                 ///< 19  Minimum Row Active to Row Active Delay Time (tRRDmin)
  0x69,                                 ///< 20  Minimum Row Precharge Delay Time (tRPmin)
  0x11,                                 ///< 21  Upper Nibbles for tRAS and tRC
  0x18,                                 ///< 22  Minimum Active to Precharge Delay Time (tRASmin), Least Significant Byte
  0x81,                                 ///< 23  Minimum Active to Active/Refresh Delay Time (tRCmin), Least Significant Byte
  0x70,                                 ///< 24  Minimum Refresh Recovery Delay Time (tRFCmin), Least Significant Byte
  0x03,                                 ///< 25  Minimum Refresh Recovery Delay Time (tRFCmin), Most Significant Byte
  0x3C,                                 ///< 26  Minimum Internal Write to Read Command Delay Time (tWTRmin)
  0x3C,                                 ///< 27  Minimum Internal Read to Precharge Command Delay Time (tRTPmin)
  0x00,                                 ///< 28  Upper Nibble for tFAW
  0xF0,                                 ///< 29  Minimum Four Activate Window Delay Time (tFAWmin)
  0x83,                                 ///< 30  SDRAM Optional Features
  0x01,                                 ///< 31  SDRAMThermalAndRefreshOptions
  0x00,                                 ///< 32  ModuleThermalSensor
  0x00,                                 ///< 33  SDRAM Device Type
  0x00,                                 ///< 34  Fine Offset for SDRAM Minimum Cycle Time (tCKmin)
  0x00,                                 ///< 35  Fine Offset for Minimum CAS Latency Time (tAAmin)
  0x00,                                 ///< 36  Fine Offset for Minimum RAS# to CAS# Delay Time (tRCDmin)
  0x00,                                 ///< 37  Fine Offset for Minimum Row Precharge Delay Time (tRPmin)
  0x00,                                 ///< 38  Fine Offset for Minimum Active to Active/Refresh Delay Time (tRCmin)
  0x00,                                 ///< 39
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 40 - 49
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 50 - 59
  0, 0,                                 ///< 60 - 61
  0x45,                                 ///< 62  Reference Raw Card Used
  0x00,                                 ///< 63  Address Mapping from Edge Connector to DRAM
  0x00,                                 ///< 64  ThermalHeatSpreaderSolution
  0, 0, 0, 0, 0,                        ///< 65 - 69
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 70 - 79
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 80 - 89
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 90 - 99
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 100 - 109
  0, 0, 0, 0, 0, 0, 0,                  ///< 110 - 116
  0x80,                                 ///< 117 Module Manufacturer ID Code, Least Significant Byte
  0xCE,                                 ///< 118 Module Manufacturer ID Code, Most Significant Byte
  0x01,                                 ///< 119 Module Manufacturing Location
  0x11,                                 ///< 120 Module Manufacturing Date Year
  0x02,                                 ///< 121 Module Manufacturing Date creation work week
  0x44,                                 ///< 122 Module Serial Number A
  0x0A,                                 ///< 123 Module Serial Number B
  0x83,                                 ///< 124 Module Serial Number C
  0x0C,                                 ///< 125 Module Serial Number D
  0xA5,                                 ///< 126 CRC A
  0x50                                  ///< 127 CRC B
};

const UINT8 ExampleJedecLpddrSpd[] = {
  0x24,                                 ///< 0   Number of Serial PD Bytes Written / SPD Device Size / CRC Coverage 1, 2
  0x20,                                 ///< 1   SPD Revision
  0x0F,                                 ///< 2   DRAM Device Type
  0x0E,                                 ///< 3   Module Type
  0x15,                                 ///< 4   SDRAM Density and Banks
  0x11,                                 ///< 5   SDRAM Addressing
  0x94,                                 ///< 6   SDRAM Package Type
  0x00,                                 ///< 7   SDRAM Optional Features
  0x00,                                 ///< 8   SDRAM Thermal and Refresh Options
  0x00,                                 ///< 9   Other SDRAM Optional Features
  0x00,                                 ///< 10  Reserved - must be coded as 0x00
  0x0B,                                 ///< 11  Module Nominal Voltage, VDD
  0x0B,                                 ///< 12  Module Organization
  0x23,                                 ///< 13  Module Memory Bus Width
  0x00,                                 ///< 14  Module Thermal Sensor
  0x00,                                 ///< 15  Extended Module Type
  0x00,                                 ///< 16  Reserved - must be coded as 0x00
  0x00,                                 ///< 17  Timebases
  0x0A,                                 ///< 18  SDRAM Minimum Cycle Time (tCKmin)
  0x0C,                                 ///< 19  SDRAM Minimum Cycle Time (tCKmax)
  0xD0,                                 ///< 20  CAS Latencies Supported, First Byte
  0x01,                                 ///< 21  CAS Latencies Supported, Second Byte
  0x00,                                 ///< 22  CAS Latencies Supported, Third Byte
  0x00,                                 ///< 23  CAS Latencies Supported, Fourth Byte
  0x78,                                 ///< 24  Minimum CAS Latency Time (tAAmin)
  0x00,                                 ///< 25  Read and Write Latency Set Options
  0x90,                                 ///< 26  Minimum RAS# to CAS# Delay Time (tRCDmin)
  0xA8,                                 ///< 27  Minimum Row Precharge Delay Time for all banks (tRPab)
  0x90,                                 ///< 28  Minimum Row Precharge Delay Time per bank (tRPpb)
  0x10,                                 ///< 29  Minimum Refresh Recovery Delay Time for all banks (tRFCab), Least Significant Byte
  0x04,                                 ///< 30  Minimum Refresh Recovery Delay Time for all banks (tRFCab), Most Significant Byte
  0xE0,                                 ///< 31  Minimum Refresh Recovery Delay Time for per bank (tRFCpb), Least Significant Byte
  0x01,                                 ///< 32  Minimum Refresh Recovery Delay Time for per bank (tRFCpb), Most Significant Byte
  0, 0, 0, 0, 0, 0, 0,                  ///< 33 - 39
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 40 - 49
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 50 - 59
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 60 - 69 Connector to SDRAM Bit Mapping
  0, 0, 0, 0, 0, 0, 0, 0,               ///< 70 - 77 Connector to SDRAM Bit Mapping
  0, 0,                                 ///< 78 - 79
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 80 - 89
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 90 - 99
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 100 - 109
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 110 - 119
  0x00,                                 ///< 120 Fine Offset for Minimum Row Precharge Delay Time per bank (tRPpb)
  0x00,                                 ///< 121 Fine Offset for Minimum Row Precharge Delay Time for all banks (tRPab)
  0x00,                                 ///< 122 Fine Offset for Minimum RAS# to CAS# Delay Time (tRCDmin)
  0x00,                                 ///< 123 Fine Offset for Minimum CAS Latency Time (tAAmin)
  0x00,                                 ///< 124 Fine Offset for SDRAM Minimum Cycle Time (tCKmax)
  0x00,                                 ///< 125 Fine Offset for SDRAM Minimum Cycle Time (tCKmin)
  0x00,                                 ///< 126 CRC A
  0x00,                                 ///< 127 CRC B
  0, 0,                                 ///< 128 - 129
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 130 - 139
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 140 - 149
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 150 - 159
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 160 - 169
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 170 - 179
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 180 - 189
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 190 - 199
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 200 - 209
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 210 - 219
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 220 - 229
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 230 - 239
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 240 - 249
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 250 - 259
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 260 - 269
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 270 - 279
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 280 - 289
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 290 - 299
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 300 - 309
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 310 - 319
  0x00,                                 ///< 320 Module Manufacturer ID Code, Least Significant Byte
  0x00,                                 ///< 321 Module Manufacturer ID Code, Most Significant Byte
  0x00,                                 ///< 322 Module Manufacturing Location
  0x00,                                 ///< 323 Module Manufacturing Date Year
  0x00,                                 ///< 324 Module Manufacturing Date Week
  0x55,                                 ///< 325 Module Serial Number A
  0x00,                                 ///< 326 Module Serial Number B
  0x00,                                 ///< 327 Module Serial Number C
  0x00,                                 ///< 328 Module Serial Number D
  0x20, 0x20, 0x20, 0x20, 0x20,         ///< 329 - 333 Module Part Number: Unused bytes coded as ASCII Blanks (0x20)
  0x20, 0x20, 0x20, 0x20, 0x20,         ///< 334 - 338 Module Part Number
  0x20, 0x20, 0x20, 0x20, 0x20,         ///< 339 - 343 Module Part Number
  0x20, 0x20, 0x20, 0x20, 0x20,         ///< 344 - 348 Module Part Number
  0x00,                                 ///< 349 Module Revision Code
  0x00,                                 ///< 350 DRAM Manufacturer ID Code, Least Significant Byte
  0x00,                                 ///< 351 DRAM Manufacturer ID Code, Most Significant Byte
  0x00,                                 ///< 352 DRAM Stepping
  0, 0, 0, 0, 0, 0, 0,                  ///< 353 - 359
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 360 - 369
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 370 - 379
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 380 - 389
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 390 - 399
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 400 - 409
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 410 - 419
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 420 - 429
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 430 - 439
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 440 - 449
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 450 - 459
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 460 - 469
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 470 - 479
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 480 - 489
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 490 - 499
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 500 - 509
  0, 0                                  ///< 510 - 511
};
#endif // EXAMPLE_BOARD_SUPPORT

///
/// For Skylake SDS board, we have a dual channel, single slot configuration
/// with the same memory configuration in each channel.
///
const MemorySlotStatus SkylakeSdsSlotStatus[MAX_CHANNEL][MAX_DIMMS_IN_CHANNEL] = {
  MEMORY_DOWN_ONLY,                     ///< Channel 0, Slot 0
  MEMORY_ABSENT,                        ///< Channel 0, Slot 1
  MEMORY_DOWN_ONLY,                     ///< Channel 1, Slot 0
  MEMORY_ABSENT,                        ///< Channel 1, Slot 1
};

/*
Memory Down SPD data for Harris Beach FFRD, DRAM type:
  SPD_LPDDR3_Elpida_EDFA232A2MA-GD-F_QDP
  SPD_LPDDR3_Hynix_H9CCNNNBLTALAR-NTD_QDP
*/
const UINT8 SkylakeSdsSpd[] = {
  0x24,                                 ///< 0   Number of Serial PD Bytes Written / SPD Device Size
  0x20,                                 ///< 1   SPD Revision
  0x0F,                                 ///< 2   DRAM Device Type
  0x0E,                                 ///< 3   Module Type
  0x14,                                 ///< 4   SDRAM Density and Banks: 8 Banks, 4 Gb SDRAM density
  0x12,                                 ///< 5   SDRAM Addressing: 14 Rows, 11 Columns
  0xB5,                                 ///< 6   SDRAM Package Type: QDP, 1 Channel per die, Signal Loading Matrix 1
  0x00,                                 ///< 7   SDRAM Optional Features
  0x00,                                 ///< 8   SDRAM Thermal and Refresh Options
  0x00,                                 ///< 9   Other SDRAM Optional Features
  0x00,                                 ///< 10  Reserved - must be coded as 0x00
  0x03,                                 ///< 11  Module Nominal Voltage, VDD
  0x0A,                                 ///< 12  Module Organization, SDRAM width: 16 bits, 2 Ranks
  0x23,                                 ///< 13  Module Memory Bus Width: 2 channels, 64 bit channel bus width
  0x00,                                 ///< 14  Module Thermal Sensor
  0x00,                                 ///< 15  Extended Module Type
  0x00,                                 ///< 16  Reserved - must be coded as 0x00
  0x00,                                 ///< 17  Timebases
  0x0A,                                 ///< 18  SDRAM Minimum Cycle Time (tCKmin)
  0xFF,                                 ///< 19  SDRAM Minimum Cycle Time (tCKmax)
  0x54,                                 ///< 20  CAS Latencies Supported, First Byte (tCk): 12 10 8
  0x00,                                 ///< 21  CAS Latencies Supported, Second Byte
  0x00,                                 ///< 22  CAS Latencies Supported, Third Byte
  0x00,                                 ///< 23  CAS Latencies Supported, Fourth Byte
  0x78,                                 ///< 24  Minimum CAS Latency Time (tAAmin)
  0x00,                                 ///< 25  Read and Write Latency Set Options
  0x90,                                 ///< 26  Minimum RAS# to CAS# Delay Time (tRCDmin)
  0xA8,                                 ///< 27  Minimum Row Precharge Delay Time for all banks (tRPab)
  0x90,                                 ///< 28  Minimum Row Precharge Delay Time per bank (tRPpb)
  0x10,                                 ///< 29  Minimum Refresh Recovery Delay Time for all banks (tRFCab), Least Significant Byte
  0x04,                                 ///< 30  Minimum Refresh Recovery Delay Time for all banks (tRFCab), Most Significant Byte
  0xE0,                                 ///< 31  Minimum Refresh Recovery Delay Time for per bank (tRFCpb), Least Significant Byte
  0x01,                                 ///< 32  Minimum Refresh Recovery Delay Time for per bank (tRFCpb), Most Significant Byte
  0, 0, 0, 0, 0, 0, 0,                  ///< 33 - 39
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 40 - 49
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 50 - 59
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 60 - 69 Connector to SDRAM Bit Mapping
  0, 0, 0, 0, 0, 0, 0, 0,               ///< 70 - 77 Connector to SDRAM Bit Mapping
  0, 0,                                 ///< 78 - 79
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 80 - 89
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 90 - 99
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 100 - 109
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 110 - 119
  0x00,                                 ///< 120 Fine Offset for Minimum Row Precharge Delay Time per bank (tRPpb)
  0x00,                                 ///< 121 Fine Offset for Minimum Row Precharge Delay Time for all banks (tRPab)
  0x00,                                 ///< 122 Fine Offset for Minimum RAS# to CAS# Delay Time (tRCDmin)
  0x00,                                 ///< 123 Fine Offset for Minimum CAS Latency Time (tAAmin)
  0x7F,                                 ///< 124 Fine Offset for SDRAM Minimum Cycle Time (tCKmax)
  0x00,                                 ///< 125 Fine Offset for SDRAM Minimum Cycle Time (tCKmin)
  0x00,                                 ///< 126 CRC A
  0x00,                                 ///< 127 CRC B
  0, 0,                                 ///< 128 - 129
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 130 - 139
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 140 - 149
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 150 - 159
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 160 - 169
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 170 - 179
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 180 - 189
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 190 - 199
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 200 - 209
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 210 - 219
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 220 - 229
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 230 - 239
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 240 - 249
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 250 - 259
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 260 - 269
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 270 - 279
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 280 - 289
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 290 - 299
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 300 - 309
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 310 - 319
  0x00,                                 ///< 320 Module Manufacturer ID Code, Least Significant Byte
  0x00,                                 ///< 321 Module Manufacturer ID Code, Most Significant Byte
  0x00,                                 ///< 322 Module Manufacturing Location
  0x00,                                 ///< 323 Module Manufacturing Date Year
  0x00,                                 ///< 324 Module Manufacturing Date Week
  0x55,                                 ///< 325 Module Serial Number A
  0x00,                                 ///< 326 Module Serial Number B
  0x00,                                 ///< 327 Module Serial Number C
  0x00,                                 ///< 328 Module Serial Number D
  0x20, 0x20, 0x20, 0x20, 0x20,         ///< 329 - 333 Module Part Number: Unused bytes coded as ASCII Blanks (0x20)
  0x20, 0x20, 0x20, 0x20, 0x20,         ///< 334 - 338 Module Part Number
  0x20, 0x20, 0x20, 0x20, 0x20,         ///< 339 - 343 Module Part Number
  0x20, 0x20, 0x20, 0x20, 0x20,         ///< 344 - 348 Module Part Number
  0x00,                                 ///< 349 Module Revision Code
  0x00,                                 ///< 350 DRAM Manufacturer ID Code, Least Significant Byte
  0x00,                                 ///< 351 DRAM Manufacturer ID Code, Most Significant Byte
  0x00,                                 ///< 352 DRAM Stepping
  0, 0, 0, 0, 0, 0, 0,                  ///< 353 - 359
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 360 - 369
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 370 - 379
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 380 - 389
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 390 - 399
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 400 - 409
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 410 - 419
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 420 - 429
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 430 - 439
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 440 - 449
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 450 - 459
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 460 - 469
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 470 - 479
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 480 - 489
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 490 - 499
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 500 - 509
  0, 0                                  ///< 510 - 511
};

// Hynix H9CCNNN8JTMLAR-NTM_178b_DDP LPDDR3, 4Gb die (128Mx32), x32
// or Elpida  EDF8132A1MC-GD-F
// or Samsung K4E8E304EB-EGCE
// 1600, 12-15-15-34
// 2 rank per channel, 2 SDRAMs per rank, 4x4Gb = 2GB total per channel
const UINT8 SkylakeRvp3Spd[] = {
  0x24,                                 ///< 0   Number of Serial PD Bytes Written / SPD Device Size
  0x20,                                 ///< 1   SPD Revision
  0x0F,                                 ///< 2   DRAM Device Type
  0x0E,                                 ///< 3   Module Type
  0x14,                                 ///< 4   SDRAM Density and Banks: 8 Banks, 4 Gb SDRAM density
  0x11,                                 ///< 5   SDRAM Addressing: 14 Rows, 10 Columns
  0x95,                                 ///< 6   SDRAM Package Type: DDP, 1 Channel per die, Signal Loading Matrix 1
  0x00,                                 ///< 7   SDRAM Optional Features
  0x00,                                 ///< 8   SDRAM Thermal and Refresh Options
  0x00,                                 ///< 9   Other SDRAM Optional Features
  0x00,                                 ///< 10  Reserved - must be coded as 0x00
  0x03,                                 ///< 11  Module Nominal Voltage, VDD
  0x0B,                                 ///< 12  Module Organization, SDRAM width: 32 bits, 2 Ranks
  0x23,                                 ///< 13  Module Memory Bus Width: 2 channels, 64 bit channel bus width
  0x00,                                 ///< 14  Module Thermal Sensor
  0x00,                                 ///< 15  Extended Module Type
  0x00,                                 ///< 16  Reserved - must be coded as 0x00
  0x00,                                 ///< 17  Timebases
  0x0A,                                 ///< 18  SDRAM Minimum Cycle Time (tCKmin)
  0xFF,                                 ///< 19  SDRAM Minimum Cycle Time (tCKmax)
  0x54,                                 ///< 20  CAS Latencies Supported, First Byte (tCk): 12 10 8
  0x00,                                 ///< 21  CAS Latencies Supported, Second Byte
  0x00,                                 ///< 22  CAS Latencies Supported, Third Byte
  0x00,                                 ///< 23  CAS Latencies Supported, Fourth Byte
  0x78,                                 ///< 24  Minimum CAS Latency Time (tAAmin)
  0x00,                                 ///< 25  Read and Write Latency Set Options
  0x90,                                 ///< 26  Minimum RAS# to CAS# Delay Time (tRCDmin)
  0xA8,                                 ///< 27  Minimum Row Precharge Delay Time for all banks (tRPab)
  0x90,                                 ///< 28  Minimum Row Precharge Delay Time per bank (tRPpb)
  0x10,                                 ///< 29  Minimum Refresh Recovery Delay Time for all banks (tRFCab), Least Significant Byte
  0x04,                                 ///< 30  Minimum Refresh Recovery Delay Time for all banks (tRFCab), Most Significant Byte
  0xE0,                                 ///< 31  Minimum Refresh Recovery Delay Time for per bank (tRFCpb), Least Significant Byte
  0x01,                                 ///< 32  Minimum Refresh Recovery Delay Time for per bank (tRFCpb), Most Significant Byte
  0, 0, 0, 0, 0, 0, 0,                  ///< 33 - 39
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 40 - 49
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 50 - 59
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 60 - 69 Connector to SDRAM Bit Mapping
  0, 0, 0, 0, 0, 0, 0, 0,               ///< 70 - 77 Connector to SDRAM Bit Mapping
  0, 0,                                 ///< 78 - 79
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 80 - 89
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 90 - 99
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 100 - 109
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 110 - 119
  0x00,                                 ///< 120 Fine Offset for Minimum Row Precharge Delay Time per bank (tRPpb)
  0x00,                                 ///< 121 Fine Offset for Minimum Row Precharge Delay Time for all banks (tRPab)
  0x00,                                 ///< 122 Fine Offset for Minimum RAS# to CAS# Delay Time (tRCDmin)
  0x00,                                 ///< 123 Fine Offset for Minimum CAS Latency Time (tAAmin)
  0x7F,                                 ///< 124 Fine Offset for SDRAM Minimum Cycle Time (tCKmax)
  0x00,                                 ///< 125 Fine Offset for SDRAM Minimum Cycle Time (tCKmin)
  0x00,                                 ///< 126 CRC A
  0x00,                                 ///< 127 CRC B
  0, 0,                                 ///< 128 - 129
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 130 - 139
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 140 - 149
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 150 - 159
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 160 - 169
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 170 - 179
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 180 - 189
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 190 - 199
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 200 - 209
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 210 - 219
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 220 - 229
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 230 - 239
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 240 - 249
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 250 - 259
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 260 - 269
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 270 - 279
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 280 - 289
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 290 - 299
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 300 - 309
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 310 - 319
  0x00,                                 ///< 320 Module Manufacturer ID Code, Least Significant Byte
  0x00,                                 ///< 321 Module Manufacturer ID Code, Most Significant Byte
  0x00,                                 ///< 322 Module Manufacturing Location
  0x00,                                 ///< 323 Module Manufacturing Date Year
  0x00,                                 ///< 324 Module Manufacturing Date Week
  0x55,                                 ///< 325 Module Serial Number A
  0x00,                                 ///< 326 Module Serial Number B
  0x00,                                 ///< 327 Module Serial Number C
  0x00,                                 ///< 328 Module Serial Number D
  0x20, 0x20, 0x20, 0x20, 0x20,         ///< 329 - 333 Module Part Number: Unused bytes coded as ASCII Blanks (0x20)
  0x20, 0x20, 0x20, 0x20, 0x20,         ///< 334 - 338 Module Part Number
  0x20, 0x20, 0x20, 0x20, 0x20,         ///< 339 - 343 Module Part Number
  0x20, 0x20, 0x20, 0x20, 0x20,         ///< 344 - 348 Module Part Number
  0x00,                                 ///< 349 Module Revision Code
  0x00,                                 ///< 350 DRAM Manufacturer ID Code, Least Significant Byte
  0x00,                                 ///< 351 DRAM Manufacturer ID Code, Most Significant Byte
  0x00,                                 ///< 352 DRAM Stepping
  0, 0, 0, 0, 0, 0, 0,                  ///< 353 - 359
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 360 - 369
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 370 - 379
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 380 - 389
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 390 - 399
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 400 - 409
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 410 - 419
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 420 - 429
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 430 - 439
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 440 - 449
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 450 - 459
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 460 - 469
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 470 - 479
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 480 - 489
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 490 - 499
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 500 - 509
  0, 0                                  ///< 510 - 511
};

// Samsung K4E6E304ED-EGCF 178b QDP LPDDR3, 4Gb die (256Mx16), x16
// or Hynix H9CCNNNBLTALAR-NUD
// or similar
// 1867, 14-17-17-40
// 2 ranks per channel, 2 SDRAMs per rank, 8x4Gb = 4GB total per channel
const UINT8 SkylakeRvp16Spd[] = {
  0x24,                                 ///< 0   Number of Serial PD Bytes Written / SPD Device Size
  0x20,                                 ///< 1   SPD Revision
  0x0F,                                 ///< 2   DRAM Device Type
  0x0E,                                 ///< 3   Module Type
  0x14,                                 ///< 4   SDRAM Density and Banks: 8 Banks, 4 Gb SDRAM density
  0x12,                                 ///< 5   SDRAM Addressing: 14 Rows, 11 Columns
  0xB5,                                 ///< 6   SDRAM Package Type: QDP, 1 Channel per die, Signal Loading Matrix 1
  0x00,                                 ///< 7   SDRAM Optional Features
  0x00,                                 ///< 8   SDRAM Thermal and Refresh Options
  0x00,                                 ///< 9   Other SDRAM Optional Features
  0x00,                                 ///< 10  Reserved - must be coded as 0x00
  0x03,                                 ///< 11  Module Nominal Voltage, VDD
  0x0A,                                 ///< 12  Module Organization, SDRAM width: 16 bits, 2 Ranks
  0x23,                                 ///< 13  Module Memory Bus Width
  0x00,                                 ///< 14  Module Thermal Sensor
  0x00,                                 ///< 15  Extended Module Type
  0x00,                                 ///< 16  Reserved - must be coded as 0x00
  0x00,                                 ///< 17  Timebases
  0x09,                                 ///< 18  SDRAM Minimum Cycle Time (tCKmin): tCKmin = 1.071ns (LPDDR3-1867)
  0xFF,                                 ///< 19  SDRAM Minimum Cycle Time (tCKmax)
  0xD4,                                 ///< 20  CAS Latencies Supported, First Byte (tCK): 14, 12, 10, 8
  0x00,                                 ///< 21  CAS Latencies Supported, Second Byte
  0x00,                                 ///< 22  CAS Latencies Supported, Third Byte
  0x00,                                 ///< 23  CAS Latencies Supported, Fourth Byte
  0x78,                                 ///< 24  Minimum CAS Latency Time (tAAmin) = 14.994 ns
  0x00,                                 ///< 25  Read and Write Latency Set Options
  0x90,                                 ///< 26  Minimum RAS# to CAS# Delay Time (tRCDmin)
  0xA8,                                 ///< 27  Minimum Row Precharge Delay Time for all banks (tRPab)
  0x90,                                 ///< 28  Minimum Row Precharge Delay Time per bank (tRPpb)
  0x10,                                 ///< 29  Minimum Refresh Recovery Delay Time for all banks (tRFCab), Least Significant Byte
  0x04,                                 ///< 30  Minimum Refresh Recovery Delay Time for all banks (tRFCab), Most Significant Byte
  0xE0,                                 ///< 31  Minimum Refresh Recovery Delay Time for per bank (tRFCpb), Least Significant Byte
  0x01,                                 ///< 32  Minimum Refresh Recovery Delay Time for per bank (tRFCpb), Most Significant Byte
  0, 0, 0, 0, 0, 0, 0,                  ///< 33 - 39
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 40 - 49
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 50 - 59
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 60 - 69 Connector to SDRAM Bit Mapping
  0, 0, 0, 0, 0, 0, 0, 0,               ///< 70 - 77 Connector to SDRAM Bit Mapping
  0, 0,                                 ///< 78 - 79
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 80 - 89
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 90 - 99
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 100 - 109
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 110 - 119
  0x00,                                 ///< 120 Fine Offset for Minimum Row Precharge Delay Time per bank (tRPpb)
  0x00,                                 ///< 121 Fine Offset for Minimum Row Precharge Delay Time for all banks (tRPab)
  0x00,                                 ///< 122 Fine Offset for Minimum RAS# to CAS# Delay Time (tRCDmin)
  0xFA,                                 ///< 123 Fine Offset for Minimum CAS Latency Time (tAAmin): 14.994 ns (LPDDR3-1867)
  0x7F,                                 ///< 124 Fine Offset for SDRAM Minimum Cycle Time (tCKmax): 32.002 ns
  0xCA,                                 ///< 125 Fine Offset for SDRAM Minimum Cycle Time (tCKmin): 1.071 ns (LPDDR-1867)
  0x00,                                 ///< 126 CRC A
  0x00,                                 ///< 127 CRC B
  0, 0,                                 ///< 128 - 129
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 130 - 139
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 140 - 149
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 150 - 159
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 160 - 169
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 170 - 179
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 180 - 189
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 190 - 199
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 200 - 209
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 210 - 219
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 220 - 229
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 230 - 239
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 240 - 249
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 250 - 259
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 260 - 269
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 270 - 279
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 280 - 289
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 290 - 299
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 300 - 309
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 310 - 319
  0x00,                                 ///< 320 Module Manufacturer ID Code, Least Significant Byte
  0x00,                                 ///< 321 Module Manufacturer ID Code, Most Significant Byte
  0x00,                                 ///< 322 Module Manufacturing Location
  0x00,                                 ///< 323 Module Manufacturing Date Year
  0x00,                                 ///< 324 Module Manufacturing Date Week
  0x55,                                 ///< 325 Module Serial Number A
  0x00,                                 ///< 326 Module Serial Number B
  0x00,                                 ///< 327 Module Serial Number C
  0x00,                                 ///< 328 Module Serial Number D
  0x20, 0x20, 0x20, 0x20, 0x20,         ///< 329 - 333 Module Part Number: Unused bytes coded as ASCII Blanks (0x20)
  0x20, 0x20, 0x20, 0x20, 0x20,         ///< 334 - 338 Module Part Number
  0x20, 0x20, 0x20, 0x20, 0x20,         ///< 339 - 343 Module Part Number
  0x20, 0x20, 0x20, 0x20, 0x20,         ///< 344 - 348 Module Part Number
  0x00,                                 ///< 349 Module Revision Code
  0x00,                                 ///< 350 DRAM Manufacturer ID Code, Least Significant Byte
  0x00,                                 ///< 351 DRAM Manufacturer ID Code, Most Significant Byte
  0x00,                                 ///< 352 DRAM Stepping
  0, 0, 0, 0, 0, 0, 0,                  ///< 353 - 359
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 360 - 369
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 370 - 379
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 380 - 389
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 390 - 399
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 400 - 409
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 410 - 419
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 420 - 429
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 430 - 439
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 440 - 449
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 450 - 459
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 460 - 469
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 470 - 479
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 480 - 489
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 490 - 499
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 500 - 509
  0, 0                                  ///< 510 - 511
};

// Elpida EDFB164A1MA-JDF 253b QDP LPDDR3, 8Gb die (256Mx32), x32
// or similar
// 1867, 14-17-17-40
// 2 ranks per channel, 2 SDRAMs per rank, 4x8Gb = 4GB total per channel
GLOBAL_REMOVE_IF_UNREFERENCED const UINT8 PantherMountainSpd[] = {
  0x24,                                 ///< 0   Number of Serial PD Bytes Written / SPD Device Size
  0x20,                                 ///< 1   SPD Revision
  0x0F,                                 ///< 2   DRAM Device Type
  0x0E,                                 ///< 3   Module Type
  0x15,                                 ///< 4   SDRAM Density and Banks: 8 Banks, 8 Gb SDRAM density
  0x19,                                 ///< 5   SDRAM Addressing: 15 Rows, 10 Columns
  0xB5,                                 ///< 6   SDRAM Package Type: QDP, 1 Channel per die, Signal Loading Matrix 1
  0x00,                                 ///< 7   SDRAM Optional Features
  0x00,                                 ///< 8   SDRAM Thermal and Refresh Options
  0x00,                                 ///< 9   Other SDRAM Optional Features
  0x00,                                 ///< 10  Reserved - must be coded as 0x00
  0x03,                                 ///< 11  Module Nominal Voltage, VDD
  0x0B,                                 ///< 12  Module Organization, SDRAM width: 32 bits, 2 Ranks
  0x23,                                 ///< 13  Module Memory Bus Width: 2 channels, 64 bit channel bus width
  0x00,                                 ///< 14  Module Thermal Sensor
  0x00,                                 ///< 15  Extended Module Type
  0x00,                                 ///< 16  Reserved - must be coded as 0x00
  0x00,                                 ///< 17  Timebases
  0x09,                                 ///< 18  SDRAM Minimum Cycle Time (tCKmin)
  0xFF,                                 ///< 19  SDRAM Minimum Cycle Time (tCKmax)
  0xD4,                                 ///< 20  CAS Latencies Supported, First Byte
  0x00,                                 ///< 21  CAS Latencies Supported, Second Byte
  0x00,                                 ///< 22  CAS Latencies Supported, Third Byte
  0x00,                                 ///< 23  CAS Latencies Supported, Fourth Byte
  0x78,                                 ///< 24  Minimum CAS Latency Time (tAAmin)
  0x00,                                 ///< 25  Read and Write Latency Set Options
  0x90,                                 ///< 26  Minimum RAS# to CAS# Delay Time (tRCDmin)
  0xA8,                                 ///< 27  Minimum Row Precharge Delay Time for all banks (tRPab)
  0x90,                                 ///< 28  Minimum Row Precharge Delay Time per bank (tRPpb)
  0x10,                                 ///< 29  Minimum Refresh Recovery Delay Time for all banks (tRFCab), Least Significant Byte
  0x04,                                 ///< 30  Minimum Refresh Recovery Delay Time for all banks (tRFCab), Most Significant Byte
  0xE0,                                 ///< 31  Minimum Refresh Recovery Delay Time for per bank (tRFCpb), Least Significant Byte
  0x01,                                 ///< 32  Minimum Refresh Recovery Delay Time for per bank (tRFCpb), Most Significant Byte
  0, 0, 0, 0, 0, 0, 0,                  ///< 33 - 39
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 40 - 49
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 50 - 59
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 60 - 69 Connector to SDRAM Bit Mapping
  0, 0, 0, 0, 0, 0, 0, 0,               ///< 70 - 77 Connector to SDRAM Bit Mapping
  0, 0,                                 ///< 78 - 79
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 80 - 89
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 90 - 99
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 100 - 109
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 110 - 119
  0x00,                                 ///< 120 Fine Offset for Minimum Row Precharge Delay Time per bank (tRPpb)
  0x00,                                 ///< 121 Fine Offset for Minimum Row Precharge Delay Time for all banks (tRPab)
  0x00,                                 ///< 122 Fine Offset for Minimum RAS# to CAS# Delay Time (tRCDmin)
  0xFA,                                 ///< 123 Fine Offset for Minimum CAS Latency Time (tAAmin)
  0x7F,                                 ///< 124 Fine Offset for SDRAM Minimum Cycle Time (tCKmax)
  0xCA,                                 ///< 125 Fine Offset for SDRAM Minimum Cycle Time (tCKmin)
  0x00,                                 ///< 126 CRC A
  0x00,                                 ///< 127 CRC B
  0, 0,                                 ///< 128 - 129
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 130 - 139
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 140 - 149
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 150 - 159
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 160 - 169
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 170 - 179
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 180 - 189
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 190 - 199
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 200 - 209
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 210 - 219
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 220 - 229
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 230 - 239
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 240 - 249
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 250 - 259
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 260 - 269
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 270 - 279
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 280 - 289
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 290 - 299
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 300 - 309
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 310 - 319
  0x00,                                 ///< 320 Module Manufacturer ID Code, Least Significant Byte
  0x00,                                 ///< 321 Module Manufacturer ID Code, Most Significant Byte
  0x00,                                 ///< 322 Module Manufacturing Location
  0x00,                                 ///< 323 Module Manufacturing Date Year
  0x00,                                 ///< 324 Module Manufacturing Date Week
  0x55,                                 ///< 325 Module Serial Number A
  0x00,                                 ///< 326 Module Serial Number B
  0x00,                                 ///< 327 Module Serial Number C
  0x00,                                 ///< 328 Module Serial Number D
  0x20, 0x20, 0x20, 0x20, 0x20,         ///< 329 - 333 Module Part Number: Unused bytes coded as ASCII Blanks (0x20)
  0x20, 0x20, 0x20, 0x20, 0x20,         ///< 334 - 338 Module Part Number
  0x20, 0x20, 0x20, 0x20, 0x20,         ///< 339 - 343 Module Part Number
  0x20, 0x20, 0x20, 0x20, 0x20,         ///< 344 - 348 Module Part Number
  0x00,                                 ///< 349 Module Revision Code
  0x00,                                 ///< 350 DRAM Manufacturer ID Code, Least Significant Byte
  0x00,                                 ///< 351 DRAM Manufacturer ID Code, Most Significant Byte
  0x00,                                 ///< 352 DRAM Stepping
  0, 0, 0, 0, 0, 0, 0,                  ///< 353 - 359
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 360 - 369
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 370 - 379
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 380 - 389
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 390 - 399
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 400 - 409
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 410 - 419
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 420 - 429
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 430 - 439
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 440 - 449
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 450 - 459
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 460 - 469
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 470 - 479
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 480 - 489
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 490 - 499
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 500 - 509
  0, 0                                  ///< 510 - 511
};


//
// Micron MT52L512M32D2PF 78b DDP LPDDR3, 8Gb die (256Mx32), x32
//
GLOBAL_REMOVE_IF_UNREFERENCED const UINT8 mKblRSpdLpddr32133[] = {
    0x91,                                 ///< 0   128 SPD bytes used, 256 total, CRC covers 0..116
    0x20,                                 ///< 1   SPD Revision 2.0
    0xF1,                                 ///< 2   DRAM Type: LPDDR3 SDRAM
    0x03,                                 ///< 3   Module Type: SO-DIMM
    0x05,                                 ///< 4   8 Banks, 8 Gb SDRAM density
    0x19,                                 ///< 5   SDRAM Addressing: 15 Rows, 10 Columns
    0x05,                                 ///< 6   Module Nominal Voltage VDD: 1.2v
    0x0B,                                 ///< 7   SDRAM width: 32 bits, 2 Ranks
    0x03,                                 ///< 8   SDRAM bus width: 64 bits, no ECC
    0x11,                                 ///< 9   Fine Timebase (FTB) granularity: 1 ps
    0x01,                                 ///< 10  Medium Timebase (MTB) : 0.125 ns
    0x08,                                 ///< 11  Medium Timebase Divisor
    0x08,                                 ///< 12  tCKmin = 0.938 ns (LPDDR3-2133)
    0x00,                                 ///< 13  Reserved
    0x50,                                 ///< 14  CAS Latencies supported (tCK): 16, 14, 12, 10, 8 (LSB)
    0x15,                                 ///< 15  CAS Latencies supported (tCK): 16, 14, 12, 10, 8 (MSB)
    0x78,                                 ///< 16  Minimum CAS Latency (tAAmin) = 15.008 ns
    0x78,                                 ///< 17  tWR = 15 ns
    0x90,                                 ///< 18  Minimum RAS-to-CAS delay (tRCDmin) = 18 ns
    0x50,                                 ///< 19  tRRD = 10 ns
    0x90,                                 ///< 20  Minimum row precharge time (tRPmin) = 18 ns
    0x11,                                 ///< 21  Upper nibbles for tRAS and tRC
    0x50,                                 ///< 22  tRASmin = 42 ns
    0xE0,                                 ///< 23  tRCmin  = (tRASmin + tRPmin) = 60 ns
    0x90,                                 ///< 24  tRFCmin = (tRFCab) = 210 ns (8Gb)
    0x06,                                 ///< 25  tRFCmin MSB
    0x3C,                                 ///< 26  tWTRmin = 7.5 ns
    0x3C,                                 ///< 27  tRTPmin = 7.5 ns
    0x01,                                 ///< 28  tFAWmin upper nibble
    0x90,                                 ///< 29  tFAWmin = 50 ns
    0x00,                                 ///< 30  SDRAM Optional Features - none
    0x00,                                 ///< 31  SDRAM Thermal / Refresh options - none
    0x00,                                 ///< 32  ModuleThermalSensor
    0x00,                                 ///< 33  SDRAM Device Type
    0xC2,                                 ///< 34  FTB for tCKmin = 0.938 ns (LPDDR3-2133)
    0x08,                                 ///< 35  FTB for tAAmin = 15.008 ns (LPDDR3-2133)
    0x00,                                 ///< 36  Fine Offset for Minimum RAS# to CAS# Delay Time (tRCDmin)
    0x00,                                 ///< 37  Fine Offset for Minimum Row Precharge Delay Time (tRPmin)
    0x00,                                 ///< 38  Fine Offset for Minimum Active to Active/Refresh Delay Time (tRCmin)
    0xA8,                                 ///< 39  Row precharge time for all banks (tRPab)= 21 ns
    0x00,                                 ///< 40  FTB for Row precharge time for all banks (tRPab) = 0
    0, 0, 0, 0, 0, 0, 0, 0, 0,            ///< 41 - 49
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 50 - 59
    0, 0,                                 ///< 60 - 61
    0x00,                                 ///< 62  Reference Raw Card Used
    0x00,                                 ///< 63  Rank1 Mapping: Standard
    0x00,                                 ///< 64  ThermalHeatSpreaderSolution
    0, 0, 0, 0, 0,                        ///< 65 - 69
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 70 - 79
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 80 - 89
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 90 - 99
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 100 - 109
    0, 0, 0, 0, 0, 0, 0,                  ///< 110 - 116
    0x00,                                 ///< 117 Module Manufacturer ID Code, Least Significant Byte
    0x00,                                 ///< 118 Module Manufacturer ID Code, Most Significant Byte
    0x00,                                 ///< 119 Module Manufacturing Location
    0x00,                                 ///< 120 Module Manufacturing Date Year
    0x00,                                 ///< 121 Module Manufacturing Date creation work week
    0x55,                                 ///< 122 Module ID: Module Serial Number
    0x00,                                 ///< 123 Module Serial Number B
    0x00,                                 ///< 124 Module Serial Number C
    0x00,                                 ///< 125 Module Serial Number D
    0x00,                                 ///< 126 CRC A
    0x00                                  ///< 127 CRC B
};


// Hynix H9CCNNNBJTALAR-NVD DDP
// or similar
// 178b DDP LPDDR3, 8Gb die (256Mx32), x32
// 2133, 16-20-20-45
// 2 ranks per channel, 2 SDRAMs per rank, 4x8Gb = 4GB total per channel
GLOBAL_REMOVE_IF_UNREFERENCED const UINT8 mAmberLakeLpddr32133Spd[] = {
  0x24, // 512 SPD bytes used, 512 total
  0x01, // SPD Revision 0.1
  0x0F, // DRAM Type: LPDDR3 SDRAM
  0x0E, // Module Type: Non-DIMM Solution
  0x15, // 8 Banks, 8 Gb SDRAM density
  0x19, // 15 Rows, 10 Columns
  0x90, // SDRAM Package Type: DDP, 1 Channel per package
  0x00, // SDRAM Optional Features: none, tMAW = 8192 * tREFI
  0x00, // SDRAM Thermal / Refresh options: none
  0x00, // Other SDRAM Optional Features: none
  0x00, // Reserved
  0x0B, // Module Nominal Voltage, VDD = 1.2v
  0x0B, // SDRAM width: 32 bits, 2 Ranks
  0x03, // SDRAM bus width: 1 Channel, 64 bits channel width
  0x00, // Module Thermal Sensor: none
  0x00, // Extended Module Type: Reserved
  0x00, // Signal Loading: Unspecified
  0x00, // MTB = 0.125ns, FTB = 1 ps
  0x08, // tCKmin = 0.938 ns (LPDDR3-2133)
  0xFF, // tCKmax = 32.002 ns
  0xD4, // CAS Latencies supported (tCK): 16, 14, 12, 10, 8 (First Byte)
  0x01, // CAS Latencies supported (tCK): 16, 14, 12, 10, 8 (Second Byte)
  0x00, // CAS Latencies supported (tCK): 16, 14, 12, 10, 8 (Third Byte)
  0x00, // CAS Latencies supported (tCK): 16, 14, 12, 10, 8 (Fourth Byte)
  0x78, // Minimum CAS Latency (tAAmin) = 15.008 ns
  0x00, // Read and Write Latency Set options: none
  0x90, // Minimum RAS-to-CAS delay (tRCDmin) = 18 ns
  0xA8, // Row precharge time for all banks (tRPab) = 21 ns
  0x90, // Minimum row precharge time (tRPmin) = 18 ns
  0x90, // tRFCab = 210 ns (8 Gb)
  0x06, // tRFCab MSB
  0xD0, // tRFCpb = 90 ns (8 Gb)
  0x02, // tRFCpb MSB
  0, 0, 0, 0, 0, 0, 0,          // Bytes 33-39
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // Bytes 40-49
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // Bytes 50-59
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // Bytes 60-69
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // Bytes 70-79
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // Bytes 80-89
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // Bytes 90-99
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // Bytes 100-109
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // Bytes 110-119
  0x00, // FTB for Row precharge time per bank (tRPpb) = 18 ns
  0x00, // FTB for Row precharge time for all banks (tRPab) = 21 ns
  0x00, // FTB for Minimum RAS-to-CAS delay (tRCDmin) = 18 ns
  0x08, // FTB for tAAmin = 15.008 ns (LPDDR3-2133)
  0x7F, // FTB for tCKmax = 32.002 ns
  0xC2, // FTB for tCKmin = 0.938 ns (LPDDR3-2133)
  0, 0, 0, 0,                   // Bytes 126-129
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // Bytes 130-139
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // Bytes 140-149
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // Bytes 150-159
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // Bytes 160-169
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // Bytes 170-179
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // Bytes 180-189
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // Bytes 190-199
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // Bytes 200-209
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // Bytes 210-219
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // Bytes 220-229
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // Bytes 230-239
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // Bytes 240-249
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // Bytes 250-259
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // Bytes 260-269
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // Bytes 270-279
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // Bytes 280-289
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // Bytes 290-299
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // Bytes 300-309
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // Bytes 310-319
  0, 0, 0, 0, 0,                // Bytes 320-324
  0x55, 0, 0, 0,                // Bytes 325-328: Module ID: Module Serial Number
  0x20, 0x20, 0x20, 0x20, 0x20, // Byte  329-333: Module Part Number: Unused bytes coded as ASCII Blanks (0x20)
  0x20, 0x20, 0x20, 0x20, 0x20, // Bytes 334-338: Module Part Number
  0x20, 0x20, 0x20, 0x20, 0x20, // Bytes 339-343: Module Part Number
  0x20, 0x20, 0x20, 0x20, 0x20, // Bytes 344-348: Module Part Number
  0x00,                         // 349 Module Revision Code
  0x00,                         // 350 DRAM Manufacturer ID Code, Least Significant Byte
  0x00,                         // 351 DRAM Manufacturer ID Code, Most Significant Byte
  0x00,                         // 352 DRAM Stepping
  0, 0, 0, 0, 0, 0, 0,          // 353 - 359
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // 360 - 369
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // 370 - 379
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // 380 - 389
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // 390 - 399
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // 400 - 409
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // 410 - 419
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // 420 - 429
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // 430 - 439
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // 440 - 449
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // 450 - 459
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // 460 - 469
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // 470 - 479
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // 480 - 489
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // 490 - 499
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // 500 - 509
  0, 0                          // 510 - 511
};

// 253b ODP LPDDR3, 8Gb x16, eight dies per package
// Hynix H9CCNNNFAGMLLR-NVD
// or similar
// 2133, 16-20-20-45
// 2 ranks per channel, 1 SDRAMs per rank, 8x8Gb = 8GB total per channel
GLOBAL_REMOVE_IF_UNREFERENCED const UINT8 mAmberLakeLpddr3ODP2133Spd[] = {
  0x24, // 512 SPD bytes used, 512 total
  0x01, // SPD Revision 0.1
  0x0F, // DRAM Type: LPDDR3 SDRAM
  0x0E, // Module Type: Non-DIMM Solution
  0x15, // 8 Banks, 8 Gb SDRAM density
  0x1A, // 15 Rows, 11 Columns
  0xF4, // SDRAM Package Type: ODP, 2 Channels per package
  0x00, // SDRAM Optional Features: none, tMAW = 8192 * tREFI
  0x00, // SDRAM Thermal / Refresh options: none
  0x00, // Other SDRAM Optional Features: none
  0x00, // Reserved
  0x0B, // Module Nominal Voltage, VDD = 1.2v
  0x0A, // SDRAM width: 16 bits, 2 Ranks
  0x03, // SDRAM bus width: 1 Channel, 64 bits channel width
  0x00, // Module Thermal Sensor: none
  0x00, // Extended Module Type: Reserved
  0x00, // Signal Loading: Unspecified
  0x00, // MTB = 0.125ns, FTB = 1 ps
  0x08, // tCKmin = 0.938 ns (LPDDR3-2133)
  0xFF, // tCKmax = 32.002 ns
  0xD4, // CAS Latencies supported (tCK): 16, 14, 12, 10, 8 (First Byte)
  0x01, // CAS Latencies supported (tCK): 16, 14, 12, 10, 8 (Second Byte)
  0x00, // CAS Latencies supported (tCK): 16, 14, 12, 10, 8 (Third Byte)
  0x00, // CAS Latencies supported (tCK): 16, 14, 12, 10, 8 (Fourth Byte)
  0x78, // Minimum CAS Latency (tAAmin) = 15.008 ns
  0x00, // Read and Write Latency Set options: none
  0x90, // Minimum RAS-to-CAS delay (tRCDmin) = 18 ns
  0xA8, // Row precharge time for all banks (tRPab) = 21 ns
  0x90, // Minimum row precharge time (tRPmin) = 18 ns
  0x90, // tRFCab = 210 ns (8 Gb)
  0x06, // tRFCab MSB
  0xD0, // tRFCpb = 90 ns (8 Gb)
  0x02, // tRFCpb MSB
  0, 0, 0, 0, 0, 0, 0,          // Bytes 33-39
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // Bytes 40-49
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // Bytes 50-59
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // Bytes 60-69
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // Bytes 70-79
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // Bytes 80-89
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // Bytes 90-99
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // Bytes 100-109
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // Bytes 110-119
  0x00, // FTB for Row precharge time per bank (tRPpb) = 18 ns
  0x00, // FTB for Row precharge time for all banks (tRPab) = 21 ns
  0x00, // FTB for Minimum RAS-to-CAS delay (tRCDmin) = 18 ns
  0x08, // FTB for tAAmin = 15.008 ns (LPDDR3-2133)
  0x7F, // FTB for tCKmax = 32.002 ns
  0xC2, // FTB for tCKmin = 0.938 ns (LPDDR3-2133)
  0, 0, 0, 0,                   // Bytes 126-129
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // Bytes 130-139
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // Bytes 140-149
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // Bytes 150-159
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // Bytes 160-169
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // Bytes 170-179
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // Bytes 180-189
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // Bytes 190-199
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // Bytes 200-209
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // Bytes 210-219
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // Bytes 220-229
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // Bytes 230-239
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // Bytes 240-249
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // Bytes 250-259
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // Bytes 260-269
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // Bytes 270-279
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // Bytes 280-289
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // Bytes 290-299
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // Bytes 300-309
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // Bytes 310-319
  0, 0, 0, 0, 0,                // Bytes 320-324
  0x55, 0, 0, 0,                // Bytes 325-328: Module ID: Module Serial Number
  0x20, 0x20, 0x20, 0x20, 0x20, // Byte  329-333: Module Part Number: Unused bytes coded as ASCII Blanks (0x20)
  0x20, 0x20, 0x20, 0x20, 0x20, // Bytes 334-338: Module Part Number
  0x20, 0x20, 0x20, 0x20, 0x20, // Bytes 339-343: Module Part Number
  0x20, 0x20, 0x20, 0x20, 0x20, // Bytes 344-348: Module Part Number
  0x00,                         // 349 Module Revision Code
  0x00,                         // 350 DRAM Manufacturer ID Code, Least Significant Byte
  0x00,                         // 351 DRAM Manufacturer ID Code, Most Significant Byte
  0x00,                         // 352 DRAM Stepping
  0, 0, 0, 0, 0, 0, 0,          // 353 - 359
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // 360 - 369
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // 370 - 379
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // 380 - 389
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // 390 - 399
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // 400 - 409
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // 410 - 419
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // 420 - 429
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // 430 - 439
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // 440 - 449
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // 450 - 459
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // 460 - 469
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // 470 - 479
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // 480 - 489
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // 490 - 499
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // 500 - 509
  0, 0                          // 510 - 511
};

/**
  Copies information from the Memory Down SPD structure to the SPD Input structure
  in the Host structure.

  Setting the SpdBaseAddress to zero means this slot has a memory down configuration.
  For systems that have both memory down and slots, it is recommended to have the
  memory down in the slot position farthest from the controller.

  @param[in, out] MrcData - MRC Host Input structure.
  @param[in]      SpdIn   - Pointer to the Memory Down SPD structure to copy.
  @param[in]      Slot    - Pointer to the Memory Down MemorySlotStatus structure.
  @param[in]      SpdSize - Size of the SPD structure to limit MemoryCpy.

  @retval - Nothing.
**/
void
CopyMemoryDownSpd (
  IN OUT MrcParameters *const    MrcData,
  IN     const UINT8             *SpdIn[MAX_CHANNEL][MAX_DIMMS_IN_CHANNEL],
  IN     const MemorySlotStatus  *Slot,
  IN     UINT16                  SpdSize
  )
{
  MrcInput  *Inputs;
  MrcDimmIn *DimmIn;
  MrcOutput *Outputs;
  MrcDebug  *Debug;
  UINT8     Channel;
  UINT8     Dimm;

  if (SpdIn == NULL || Slot == NULL || SpdSize == 0) {
    return;
  }

  Inputs  = &MrcData->Inputs;
  Outputs = &MrcData->Outputs;
  Debug   = &Outputs->Debug;
  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    for (Dimm = 0; Dimm < MAX_DIMMS_IN_CHANNEL; Dimm++, Slot++) {
      DimmIn = &Inputs->Controller[0].Channel[Channel].Dimm[Dimm];
      switch (*Slot) {
        case MEMORY_DOWN_ONLY:
          DimmIn->SpdAddress  = 0;
          // Check user request to disable DIMM/rank pair.
          if (DimmIn->Status != DIMM_DISABLED) {
            DimmIn->Status = DIMM_ENABLED;
            MrcOemMemoryCpy ((UINT8 *) &DimmIn->Spd.Data, (UINT8 *) SpdIn[Channel][Dimm], SpdSize);
            MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Memory down present on channel %u, dimm %u\n", Channel, Dimm);
          } else {
            MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Memory down absent on channel %u, dimm %u\n", Channel, Dimm);
          }
          break;

        case MEMORY_ABSENT:
          DimmIn->Status      = DIMM_DISABLED;
          DimmIn->SpdAddress  = 0;
          MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Memory down absent on channel %u, dimm %u\n", Channel, Dimm);
          break;

        case MEMORY_SLOT_ONLY:
        default:
          break;
      }
    }
  }

  return;
}

/**
  Enables Memory Down support and sets SPD data for all DIMMs needing support.

  @param[in] MrcData    - MRC global data structure.
  @param[in] BoardId    - The ID of the board.
  @param[in] SpdPresent - SPD is present or memory is down.

  @retval Nothing
**/
void
EnableMemoryDown (
  IN MrcParameters *const MrcData,
  IN const UINT16         BoardId,
  IN const BOOLEAN        SpdPresent
  )
{
  const UINT8             *SpdIn[MAX_CHANNEL][MAX_DIMMS_IN_CHANNEL];
  const MemorySlotStatus  *Slot;
  UINT16                  SpdSize;
  UINT8                   Channel;
  UINT8                   Dimm;

  Channel = 0;
  Dimm    = 0;
  SpdSize = 0;
  Slot    = NULL;

  switch (BoardId) {
#if (defined EXAMPLE_BOARD_SUPPORT && (EXAMPLE_BOARD_SUPPORT > 0))
    case 0:
      //
      // BoardIdExample:
      //
      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        for (Dimm = 0; Dimm < MAX_DIMMS_IN_CHANNEL; Dimm++) {
          SpdIn[Channel][Dimm] = ExampleSpd;
        }
      }

      Slot = (const MemorySlotStatus *) &ExampleSlotStatus[0][0];
      SpdSize = sizeof (ExampleSpd);
      break;
#endif // EXAMPLE_BOARD_SUPPORT

    //
    // Add additional boards that support memory down here.
    //
    case BoardIdSkylakeSds:
      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        for (Dimm = 0; Dimm < MAX_DIMMS_IN_CHANNEL; Dimm++) {
          SpdIn[Channel][Dimm] = SkylakeSdsSpd;
        }
      }

      Slot = (const MemorySlotStatus *) &SkylakeSdsSlotStatus[0][0];
      SpdSize = sizeof (SkylakeSdsSpd);
      break;

    case BoardIdSkylakeA0Rvp3:
    case BoardIdKabyLakeYLpddr3Rvp3:
    case BoardIdSkylakeA0Rvp3Ppv:
    case BoardIdSkylakeULpddr3Rvp5:
    case BoardIdSkylakeULpddr3Rvp5Ppv:
    case BoardIdSkylakeYRvp13:
      if (!SpdPresent) {
        for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
          for (Dimm = 0; Dimm < MAX_DIMMS_IN_CHANNEL; Dimm++) {
            SpdIn[Channel][Dimm] = SkylakeRvp3Spd;
          }
        }
        Slot = (const MemorySlotStatus *) &SkylakeSdsSlotStatus[0][0]; // Same slot population as Skylake Sds.
        SpdSize = sizeof (SkylakeRvp3Spd);
      }

      break;

    case BoardIdAmberLakeLpddr3Rvp3:
    case BoardIdAmberLakeY42Lpddr3Rvp3:
    case BoardIdAmberLakeLpddr3Rvp13:
    case BoardIdAmberLakeY42Lpddr3Cff:
    case BoardIdAmberLakeY42Lpddr3CffCc:
      if (!SpdPresent) {
        for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
          for (Dimm = 0; Dimm < MAX_DIMMS_IN_CHANNEL; Dimm++) {
            SpdIn[Channel][Dimm] = mAmberLakeLpddr3ODP2133Spd;
          }
        }
        Slot = (const MemorySlotStatus *) &SkylakeSdsSlotStatus[0][0]; // Same slot population as Skylake Sds.
        SpdSize = sizeof (mAmberLakeLpddr3ODP2133Spd);
      }

      break;

    case BoardIdSkylakeHaloLpddr3Rvp16:
      if (!SpdPresent) {
        for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
          for (Dimm = 0; Dimm < MAX_DIMMS_IN_CHANNEL; Dimm++) {
            SpdIn[Channel][Dimm] = SkylakeRvp16Spd;
          }
        }
        Slot = (const MemorySlotStatus *) &SkylakeSdsSlotStatus[0][0]; // Same slot population as Skylake Sds.
        SpdSize = sizeof (SkylakeRvp16Spd);
      }
      break;

    case BoardIdSkylakePantherMtn:
    case BoardIdSkylakePhabletPoc:
    case BoardIdKabylakeGrizzlyMtn:
      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        for (Dimm = 0; Dimm < MAX_DIMMS_IN_CHANNEL; Dimm++) {
          SpdIn[Channel][Dimm] = PantherMountainSpd;
        }
      }
      Slot = (const MemorySlotStatus *) &SkylakeSdsSlotStatus[0][0]; // Same slot population as Skylake Sds.
      SpdSize = sizeof (PantherMountainSpd);
      break;

    case BoardIdKabylakeRLpddr3:
      if (!SpdPresent) {
        for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
          for (Dimm = 0; Dimm < MAX_DIMMS_IN_CHANNEL; Dimm++) {
            SpdIn[Channel][Dimm] = mKblRSpdLpddr32133;
          }
        }
        Slot = (const MemorySlotStatus *) &SkylakeSdsSlotStatus[0][0]; // Same slot population as Skylake Sds.
        SpdSize = sizeof (mKblRSpdLpddr32133);
      }
      break;
      
    //
    // The default case means the board ID was not recognized.  Instead
    // we set Slot = NULL thus forcing us to read from the SPD.
    //
    default:
      Slot  = NULL;
  }

  CopyMemoryDownSpd (MrcData, SpdIn, Slot, SpdSize);

  return;
}
#endif // MEMORY_DOWN_SUPPORT

/**
  Initialize the board-specific CMD/CTL/CLK and DQ/DQS mapping for LPDDR3.

  @param[in, out] MrcData - MRC global data structure.
  @param[in]      BoardId - The ID of the board.

**/
void
MrcOemLpddrBoardMapping (
  IN MrcParameters *const MrcData,
  IN UINT16        BoardId
  )
{
  MrcDebug        *Debug;
  MrcInput        *Inputs;
  MrcControllerIn *ControllerIn;
  UINT8           *DqByteMapCh0;
  UINT8           *DqByteMapCh1;
  UINT8           *DqsMapCpu2DramCh0;
  UINT8           *DqsMapCpu2DramCh1;
  UINT8           *DqMapCpu2DramCh0;
  UINT8           *DqMapCpu2DramCh1;
  UINT32          Channel;
  UINT32          Byte;
  char            *BoardName;

  Inputs = &MrcData->Inputs;
  Debug  = &MrcData->Outputs.Debug;
  if (!((BoardId == BoardIdSkylakeA0Lpddr3Crb)     ||
        (BoardId == BoardIdSkylakeA0Rvp3)          ||
        (BoardId == BoardIdKabyLakeYLpddr3Rvp3)    ||
        (BoardId == BoardIdAmberLakeY42Lpddr3Rvp3) ||
        (BoardId == BoardIdAmberLakeLpddr3Rvp3)    ||
        (BoardId == BoardIdAmberLakeLpddr3Rvp13)   ||
        (BoardId == BoardIdSkylakeA0Rvp3Ppv)       ||
        (BoardId == BoardIdSkylakeULpddr3Rvp5)     ||
        (BoardId == BoardIdSkylakeULpddr3Rvp5Ppv)  ||
        (BoardId == BoardIdSkylakeHaloLpddr3Rvp16) ||
        (BoardId == BoardIdSkylakePhabletPoc)      ||
        (BoardId == BoardIdSkylakeYRvp13)          ||
        (BoardId == BoardIdSkylakeLpdimmDoe)       ||
        (BoardId == BoardIdKabylakeRLpddr3)        ||
        (BoardId == BoardIdAmberLakeY42Lpddr3Cff)  ||
        (BoardId == BoardIdAmberLakeY42Lpddr3CffCc)
       )) {
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "Not an LPDDR3 board! BoardId = 0x%x\n", BoardId);
    return;
  }

  ControllerIn      = &Inputs->Controller[0];
  DqByteMapCh0      = NULL;
  DqByteMapCh1      = NULL;
  DqsMapCpu2DramCh0 = NULL;
  DqsMapCpu2DramCh1 = NULL;
  DqMapCpu2DramCh0  = NULL;
  DqMapCpu2DramCh1  = NULL;

  //
  // CKE to Rank mapping:       CKE  | 0 1 2 3
  // (same on both channels)    --------------
  //                            Rank | 0 1 0 1
  //
  Inputs->CkeRankMapping = 0xAA;

  DqByteMapCh0      = (UINT8 *) DqByteMapSkl[0];
  DqByteMapCh1      = (UINT8 *) DqByteMapSkl[1];
  DqsMapCpu2DramCh0 = (UINT8 *) DqsMapCpu2DramSklRvp[0];
  DqsMapCpu2DramCh1 = (UINT8 *) DqsMapCpu2DramSklRvp[1];

  BoardName = "";
  switch (BoardId) {
    case BoardIdSkylakeA0Lpddr3Crb:
      BoardName = "RVP1";
      break;
    case BoardIdSkylakeA0Ddr4Rvp2:
      BoardName = "RVP2";
      break;
    case BoardIdSkylakeA0Rvp3:
    case BoardIdSkylakeA0Rvp3Ppv:
      BoardName = "RVP3";
      break;
    case BoardIdKabyLakeYLpddr3Rvp3:
      BoardName = "KBL RVP3";
      break;
    case BoardIdAmberLakeLpddr3Rvp3:
      BoardName = "Amber Lake RVP3";
      break;
    case BoardIdAmberLakeY42Lpddr3Rvp3:
      BoardName = "Amber Lake Y42 RVP3";
      break;
    case BoardIdAmberLakeY42Lpddr3Cff:
      BoardName = "Amber Lake Y42 AEP";
      break;
    case BoardIdAmberLakeY42Lpddr3CffCc:
      BoardName = "Amber Lake Y42 AEP CC";
      break;
    case BoardIdSkylakeULpddr3Rvp5:
    case BoardIdSkylakeULpddr3Rvp5Ppv:
      BoardName = "RVP5";
      break;
    case BoardIdKabylakeRLpddr3:
      BoardName = "RVP7";
      break;
    case BoardIdSkylakeYRvp13:
      BoardName = "RVP13";
      break;
    case BoardIdAmberLakeLpddr3Rvp13:
      BoardName = "Amber Lake RVP13";
      break;
    case BoardIdSkylakeHaloLpddr3Rvp16:
      BoardName = "RVP16";
      break;
    case BoardIdSkylakePhabletPoc:
      BoardName = "Phablet POC";
      break;
    case BoardIdSkylakeLpdimmDoe:
      BoardName = "LPDIMM DOE RVP";
      break;
    default:
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "Unknown board! BoardId = 0x%x\n", BoardId);
      MRC_DEADLOOP ();
  }
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "Detected board: %s\n", BoardName);

  switch (BoardId) {
    case BoardIdSkylakeULpddr3Rvp5:
    case BoardIdSkylakeULpddr3Rvp5Ppv:
    case BoardIdKabylakeRLpddr3:
      DqByteMapCh0      = (UINT8 *) DqByteMapSklRvp5[0];
      DqByteMapCh1      = (UINT8 *) DqByteMapSklRvp5[1];
      DqsMapCpu2DramCh0 = (UINT8 *) DqsMapCpu2DramSklRvp5[0];
      DqsMapCpu2DramCh1 = (UINT8 *) DqsMapCpu2DramSklRvp5[1];
      break;

    case BoardIdSkylakeHaloLpddr3Rvp16:
      DqByteMapCh0      = (UINT8 *) DqByteMapSklRvp5[0];
      DqByteMapCh1      = (UINT8 *) DqByteMapSklRvp5[1];
      DqsMapCpu2DramCh0 = (UINT8 *) DqsMapCpu2DramSklRvp16[0];
      DqsMapCpu2DramCh1 = (UINT8 *) DqsMapCpu2DramSklRvp16[1];
      break;

    case BoardIdSkylakePhabletPoc:
      DqsMapCpu2DramCh0 = (UINT8 *) DqsMapCpu2DramSklPhabletPoc[0];
      DqsMapCpu2DramCh1 = (UINT8 *) DqsMapCpu2DramSklPhabletPoc[1];
      break;

    case BoardIdSkylakeLpdimmDoe:
      DqsMapCpu2DramCh0 = (UINT8 *) DqsMapCpu2DramSklLpdimmDOE[0];
      DqsMapCpu2DramCh1 = (UINT8 *) DqsMapCpu2DramSklLpdimmDOE[1];
      DqByteMapCh0      = (UINT8 *) DqByteMapSklLpdimmDOE[0];
      DqByteMapCh1      = (UINT8 *) DqByteMapSklLpdimmDOE[1];
      break;

    case BoardIdAmberLakeY42Lpddr3Rvp3:
      DqsMapCpu2DramCh0 = (UINT8 *) mDqsMapCpu2DramAml42Lpddr3Rvp[0];
      DqsMapCpu2DramCh1 = (UINT8 *) mDqsMapCpu2DramAml42Lpddr3Rvp[1];
      DqByteMapCh0      = (UINT8 *) DqByteMapSklRvp5[0];
      DqByteMapCh1      = (UINT8 *) DqByteMapSklRvp5[1];
      break;

    case BoardIdAmberLakeY42Lpddr3Cff:
      DqsMapCpu2DramCh0 = (UINT8 *) mDqsMapCpu2DramAml42Lpddr3Cff[0];
      DqsMapCpu2DramCh1 = (UINT8 *) mDqsMapCpu2DramAml42Lpddr3Cff[1];
      DqByteMapCh0      = (UINT8 *) mDqByteMapAml42Lpddr3Cff[0];
      DqByteMapCh1      = (UINT8 *) mDqByteMapAml42Lpddr3Cff[1];
      break;
  }

  //
  // DQ byte mapping to CMD/CTL/CLK
  //
  MrcOemMemoryCpy ((UINT8 *) ControllerIn->Channel[0].DQByteMap, DqByteMapCh0, sizeof (DqByteMapSkl[0]));
  MrcOemMemoryCpy ((UINT8 *) ControllerIn->Channel[1].DQByteMap, DqByteMapCh1, sizeof (DqByteMapSkl[1]));

  //
  // DQS byte swizzling between CPU and DRAM
  //
  MrcOemMemoryCpy (ControllerIn->Channel[0].DqsMapCpu2Dram, DqsMapCpu2DramCh0, sizeof (DqsMapCpu2DramSklRvp[0]));
  MrcOemMemoryCpy (ControllerIn->Channel[1].DqsMapCpu2Dram, DqsMapCpu2DramCh1, sizeof (DqsMapCpu2DramSklRvp[1]));

  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "Ch %d DqsMapCpu2Dram: ", Channel);
    for (Byte = 0; Byte < 8; Byte++) {
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "%d ", ControllerIn->Channel[Channel].DqsMapCpu2Dram[Byte]);
    }
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "\n");
  }
}

/**
  Initialize the board-specific RCOMP values.

  @param[in, out] MrcData - MRC global data structure.
  @param[in]      BoardId - The ID of the board.
**/
void
MrcOemRcompValues (
  IN OUT MrcParameters *const MrcData,
  IN     UINT16               BoardId
  )
{
  MrcDebug  *Debug;
  MrcInput  *Inputs;
  const UINT16 *RcompResistor;       // Reference RCOMP resistors on motherboard
  const UINT16 *RcompTarget;         // RCOMP target values for DqOdt, DqDrv, CmdDrv, CtlDrv, ClkDrv

  Inputs = &MrcData->Inputs;
  Debug  = &MrcData->Outputs.Debug;

  RcompResistor = NULL;
  RcompTarget   = NULL;
  //
  // Set the on-board RCOMP resistors and RCOMP target values for DqOdt, DqDrv, CmdDrv, CtlDrv, ClkDrv
  // These values are for ULT/ULX LPDDR3
  //
  switch (BoardId) {
    case BoardIdSkylakeA0Lpddr3Crb:  // These values are for ULT/ULX LPDDR3
    case BoardIdSkylakeA0Rvp3:
    case BoardIdKabyLakeYLpddr3Rvp3:
    case BoardIdAmberLakeY42Lpddr3Rvp3:
    case BoardIdAmberLakeY42Lpddr3Cff:
    case BoardIdAmberLakeY42Lpddr3CffCc:
    case BoardIdAmberLakeLpddr3Rvp3:
    case BoardIdSkylakeA0Rvp3Ppv:
    case BoardIdSkylakeYRvp13:
    case BoardIdAmberLakeLpddr3Rvp13:
    case BoardIdSkylakePhabletPoc:
    default:
      RcompResistor = RcompResistorSklRvp1;
      RcompTarget   = RcompTargetSklRvp1;
      break;
  }
  MRC_ASSERT ((RcompResistor != NULL) && (RcompTarget != NULL), Debug, "Unknown BoardId = 0x%x !\n", BoardId);
  MrcOemMemoryCpy ((UINT8 *) Inputs->RcompResistor, (UINT8 *) RcompResistor, sizeof (Inputs->RcompResistor));
  MrcOemMemoryCpy ((UINT8 *) Inputs->RcompTarget,   (UINT8 *) RcompTarget,   sizeof (Inputs->RcompTarget));
}

/**
  Perform a byte read from the specified SMBus device address.

  @param[in] SmbusBaseAddress   - The SMBus base address.
  @param[in] SmBusDeviceAddress - SMBus device address to read from.
  @param[in] Offset             - Byte offset to read from.
  @param[out] Value             - Location to store read value.

  @retval mrcSuccess if the read is successful, otherwise mrcFail and the read data is set to zero.
**/
MrcStatus
MrcOemSmbusRead8 (
  IN const UINT32  SmbusBaseAddress,
  IN const UINT8   SmBusDeviceAddress,
  IN const UINT8   Offset,
  OUT UINT8 *const Value
  )
{
  MrcStatus     Status;
  RETURN_STATUS EfiStatus;

#ifdef NOSMBUS_BUILD
  if (SmBusDeviceAddress == 0xA0) {
    //
    // For CH0 - DIMM0 only
    //
    *Value  = SPDData[Offset];
    Status  = mrcSuccess;
  } else {
    Status = mrcFail;
  }

#else
  *Value = SmBusReadDataByte (SmBusDeviceAddress | ((UINT32) Offset << 8), &EfiStatus);
  if (EfiStatus == RETURN_SUCCESS) {
    Status = mrcSuccess;
  } else {
    Status = mrcFail;
  }
#endif // NOSMBUS_BUILD

  if (Status != mrcSuccess) {
    *Value = 0;
  }

  return Status;
}

/**
  Perform a byte write to the specified SMBus device address.

  @param[in] SmbusBaseAddress   - The SMBus base address.
  @param[in] SmBusDeviceAddress - SMBus device address to write to.
  @param[in] Offset             - Byte offset to write to.
  @param[in] Value              - The value to write.

  @retval mrcSuccess if the write is successful, otherwise mrcFail.
**/
MrcStatus
MrcOemSmbusWrite8 (
  IN const UINT32  SmbusBaseAddress,
  IN const UINT8   SmBusDeviceAddress,
  IN const UINT8   Offset,
  IN UINT8         Value
  )
{

  MrcStatus     Status;
  RETURN_STATUS EfiStatus;

  SmBusWriteDataByte (SmBusDeviceAddress | ((UINT32) Offset << 8), Value, &EfiStatus);
  Status = (EfiStatus == RETURN_SUCCESS) ? mrcSuccess : mrcFail;
  return Status;
}

/**
  Perform a word read from the specified SMBus device address.

  @param[in] SmbusBaseAddress   - The SMBus base address.
  @param[in] SmBusDeviceAddress - SMBus device address to read from.
  @param[in] Offset             - Offset to read from.
  @param[out] Value             - Location to store read value.

  @retval mrcSuccess if the read is successful, otherwise mrcFail and the read data is set to zero.
**/
MrcStatus
MrcOemSmbusRead16 (
  IN const UINT32   SmbusBaseAddress,
  IN const UINT8    SmBusDeviceAddress,
  IN const UINT8    Offset,
  OUT UINT16 *const Value
  )
{
  MrcStatus     Status;
  RETURN_STATUS EfiStatus;

#ifdef NOSMBUS_BUILD
  if (SmBusDeviceAddress == 0xA0) {
    //
    // For CH0 - DIMM0 only
    //
    *Value  = SPDData[Offset];
    Status  = mrcSuccess;
  } else {
    Status = mrcFail;
  }

#else
  *Value = SmBusReadDataWord (SmBusDeviceAddress | ((UINT32) Offset << 8), &EfiStatus);
  if (EfiStatus == RETURN_SUCCESS) {
    Status = mrcSuccess;
  } else {
    Status = mrcFail;
  }
#endif // NOSMBUS_BUILD

  if (Status != mrcSuccess) {
    *Value = 0;
  }

  return Status;
}

/**
  Perform a word write to the specified SMBus device address.

  @param[in] SmbusBaseAddress   - The SMBus base address.
  @param[in] SmBusDeviceAddress - SMBus device address to write to.
  @param[in] Offset             - Offset to write to.
  @param[in] Value              - The value to write.

  @retval mrcSuccess if the write is successful, otherwise mrcFail.
**/
MrcStatus
MrcOemSmbusWrite16 (
  IN const UINT32  SmbusBaseAddress,
  IN const UINT8   SmBusDeviceAddress,
  IN const UINT8   Offset,
  IN UINT16        Value
  )
{
  MrcStatus     Status;
  RETURN_STATUS EfiStatus;

  SmBusWriteDataWord (SmBusDeviceAddress | ((UINT32) Offset << 8), Value, &EfiStatus);
  Status = (EfiStatus == RETURN_SUCCESS) ? mrcSuccess : mrcFail;
  return Status;
}

/**
  Get the current PCH type.

  @retval MrcPchType enum
**/
MrcPchType
MrcGetPchType (
  void
  )
{
  MrcPchType  PchType;
  UINT16      LpcDeviceId;

  MrcOemOutPort32 (MrcOemPciIndex (), GetPciDeviceAddress (0, PCI_DEVICE_NUMBER_PCH_LPC, PCI_FUNCTION_NUMBER_PCH_LPC, 0));
  LpcDeviceId = (MrcOemInPort32 (MrcOemPciData ()) >> 16) & 0xFFFF;

  switch (LpcDeviceId & PCH_DEVICE_ID_MASK) {
    case PCH_LPTLP_DEVICE_ID_MASK:
    case PCH_LPTH_DEVICE_ID_MASK:
      PchType = PchTypeLpt;
      break;

    case PCH_SPTLP_DEVICE_ID_MASK:
    case PCH_SPTH_DEVICE_ID_MASK:
      PchType = PchTypeSpt;
      break;

    default:
      PchType = PchTypeUnknown;
  }
  return PchType;
}

/**
  Get the current PCH Series.

  @retval MrcPchSeries enum
**/
MrcPchSeries
MrcGetPchSeries (
  void
  )
{
  MrcPchSeries  PchSeries;
  UINT16        LpcDeviceId;

  MrcOemOutPort32 (MrcOemPciIndex (), GetPciDeviceAddress (0, PCI_DEVICE_NUMBER_PCH_LPC, PCI_FUNCTION_NUMBER_PCH_LPC, 0));
  LpcDeviceId = (MrcOemInPort32 (MrcOemPciData ()) >> 16) & 0xFFFF;

  switch (LpcDeviceId & PCH_DEVICE_ID_MASK) {
    case PCH_LPTLP_DEVICE_ID_MASK:
    case PCH_SPTLP_DEVICE_ID_MASK:
      PchSeries = PchSeriesLp;
      break;
    case PCH_LPTH_DEVICE_ID_MASK:
    case PCH_SPTH_DEVICE_ID_MASK:
      PchSeries = PchSeriesH;
      break;

    default:
      PchSeries = PchSeriesUnknown;
  }
  return PchSeries;
}

/**
  Disable PCIe root ports on PCH.
  See PchDisableRootPort() in PCH RC.

  @param[in] MrcData - Mrc global data structure
**/
VOID
MrcDisablePciePorts (
  IN MrcParameters *const MrcData
  )
{
  UINT32 Data32;
  UINT32 Offset;

  // PCIe RP IOSF Sideband register offset R_PCH_PCR_SPX_PCD 0x00[19:16], depending on the port that is Function Disabled
  // Access it by offset 0x02[4:0] to avoid RWO bit
  MrcOemMmioWrite8 (PCH_PCR_ADDRESS (PID_SPA, 0x02), 0x0F);
  MrcOemMmioWrite8 (PCH_PCR_ADDRESS (PID_SPB, 0x02), 0x0F);
  MrcOemMmioWrite8 (PCH_PCR_ADDRESS (PID_SPC, 0x02), 0x0F);
  MrcOemMmioWrite8 (PCH_PCR_ADDRESS (PID_SPD, 0x02), 0x0F);
  MrcOemMmioWrite8 (PCH_PCR_ADDRESS (PID_SPE, 0x02), 0x0F);

  // Then disable the ports in PSF
  // R_PCH_LP_PCR_PSF1_T1_SHDW_PCIE01_REG_BASE + R_PCH_PCR_PSFX_T1_SHDW_PCIEN, set bit [8] = B_PCH_PCR_PSFX_T1_SHDW_PCIEN_FUNDIS
  for (Offset = 0x203C; Offset <= 0x373C; Offset += 0x100) {
    Data32 = MrcOemMmioRead32 (PCH_PCR_ADDRESS (PID_PSF1, Offset));
    MrcOemMmioWrite32 (PCH_PCR_ADDRESS (PID_PSF1, Offset), Data32 | MRC_BIT8);
  }
}

/*
  Check on the processor if PRMRR is supported.

  @param[in]  Size  - PRMRR size requested in MB.  Must be natural size (2^x).

  @retval Size in MB.  0 if unsupported.
*/
UINT32
MrcCheckPrmrrSupport (
  MrcParameters *MrcData,
  UINT32        PrmrrSize
  )
{
  UINT32 ReturnSize  = 0;
  ///
  /// PRMRR configuration enabled, MSR IA32_MTRRCAP (FEh) [12] == 1
  ///
  MRC_DEBUG_MSG (&MrcData->Outputs.Debug, MSG_LEVEL_NOTE, "MSR_IA32_MTRRCAP: 0x%x\n", AsmReadMsr64 (MSR_IA32_MTRRCAP));
  if ((AsmReadMsr64 (MSR_IA32_MTRRCAP) & MRC_BIT12) != 0) {
    ///
    /// Check if PRMRR setup size is not supported.
    /// Bits 0 through 31 indicate which sizes are supported. Each bit represents one size.
    /// A bit at position n indicates whether size 2^(n+20) bytes is supported
    ///
    MRC_DEBUG_MSG (&MrcData->Outputs.Debug, MSG_LEVEL_NOTE, "MSR_PRMRR_VALID_CONFIG: 0x%x\n", AsmReadMsr64 (MSR_PRMRR_VALID_CONFIG));
    if ((AsmReadMsr64 (MSR_PRMRR_VALID_CONFIG) & PrmrrSize) != 0) {
      ReturnSize = PrmrrSize;
    }
  }
  return ReturnSize;
}

/**
  Sets PRMRR Uncore Lock & Valid bits, and PRMRR core MSR for
  BSP thread core

  @param[in] PrmrrBase - PRMRR base that was allocated
  @param[in] PrmrrSize - PRMRR size that was allocated
**/

VOID
MrcSetUncorePrmrr (
  UINT32 PrmrrBase,
  UINT32 PrmrrSize
  )
{
  UINT64 PrmrrMask;
  ///
  /// Mask setting have to be set in bits [39:12] other bits bits [64:40] need to be zero
  /// Setting bits [64:40] will cause the BIOS to hung
  ///
  PrmrrMask = V_MSR_PRMRR_MASK & (~((UINT64) (PrmrrSize - 1)));

  ///
  /// If PRMRR size is 0, only need to set bit lock on MSR 0x2f5
  ///
  if (PrmrrSize == 0) {
    if (!(AsmReadMsr64 (MSR_UNCORE_PRMRR_PHYS_MASK) & B_MSR_PRMRR_PHYS_MASK_LOCK)) {

      ///
      /// Need to lock mask MSRs even if PRMRR size is zero
      ///
      AsmWriteMsr64 (MSR_UNCORE_PRMRR_PHYS_MASK, B_MSR_PRMRR_PHYS_MASK_LOCK);
    }
  } else {

    ///
    /// Set the UNCORE PRMRR base and mask MSRs and set PRMRR mask lock and valid bits
    ///
    if (!(AsmReadMsr64 (MSR_UNCORE_PRMRR_PHYS_MASK) & B_MSR_PRMRR_PHYS_MASK_LOCK)) {
      AsmWriteMsr64 (MSR_UNCORE_PRMRR_PHYS_BASE, PrmrrBase | CACHE_UNCACHEABLE);
      AsmWriteMsr64 (MSR_UNCORE_PRMRR_PHYS_MASK, PrmrrMask | B_MSR_PRMRR_PHYS_MASK_LOCK | B_MSR_PRMRR_VALID_BIT);
    }
  }
}

/**
  Set a GPIO value to indicate "End of BIOS POST" to BMC on a UP server board (Zumba Beach).
  Otherwise BMC will shutdown the board after 7 minutes.

**/
VOID
MrcUpServerSendEndOfPost (
  VOID
  )
{
  //
  // Set GPIO_SKL_H_GPP_B20 "Low"
  // GpioPadModeGpio, GpioHostOwnDefault, GpioDirOut, GpioOutLow, GpioIntDis, GpioResetNormal, GpioTermNone
  //
  MrcOemMmioWrite32 (PCH_PCR_ADDRESS (PID_GPIOCOM0, 0x560), 0x80000200); // PADCFG DW0
  MrcOemMmioWrite32 (PCH_PCR_ADDRESS (PID_GPIOCOM0, 0x564), 0);          // PADCFG DW1
}

MrcStatus
PollMailboxReady (
  IN UINT32 MailboxType
  )
{
  MrcStatus               Status;
  UINT16                  StallCount;
  UINT8                   RunBusyBit;
  UINT64                  MsrData;
  UINT32                  MchBar;
  OC_MAILBOX_FULL         OcMailboxFull;
  PCODE_MAILBOX_INTERFACE PcodeMailboxInterface;
#ifdef MRC_MINIBIOS_BUILD
  UINT32                  Start;
  volatile UINT32         Value;
#endif

  Status = mrcSuccess;
  StallCount = 0;
  RunBusyBit = 1;

  MrcOemOutPort32 (0xCF8, GetPciDeviceAddress (0, 0, 0, UNCORE_CR_MCHBAR_0_0_0_PCI_REG));
  MchBar = MrcOemInPort32 (0xCFC) &~MRC_BIT0;

  do {
    switch (MailboxType) {
      case MAILBOX_TYPE_PCODE:
        ///
        /// Read the MMIO run/busy state
        ///
        PcodeMailboxInterface.InterfaceData = MrcOemMmioRead32 (MchBar + PCODE_MAILBOX_INTERFACE_OFFSET);
        RunBusyBit = (UINT8) PcodeMailboxInterface.Fields.RunBusy;
        break;

      case MAILBOX_TYPE_OC:
        ///
        /// Read the OC mailbox run/busy state
        ///
        MsrData = ReadMsr64 (OC_MAILBOX_MSR);
        CopyMem ((UINT8 *) &OcMailboxFull.Data, (UINT8 *) &MsrData, sizeof (OcMailboxFull));
        RunBusyBit = OcMailboxFull.Interface.Fields.RunBusy;
        break;
      default:
        break;
    }
    //
    // Wait for 1us
    //
#ifdef MRC_MINIBIOS_BUILD
    for (Start = 0; Start < (((MAILBOX_WAIT_STALL * HPET_1US) + HPET_MIN) / (2 * HPET_MIN)); Start++) {
      //
      // Just perform Dummy reads to CPU CR
      //
      Value = MrcOemMmioRead32 (MchBar + PCODE_MAILBOX_DATA_OFFSET);
    }
#else
    PchPmTimerStall (MAILBOX_WAIT_STALL);
#endif
    StallCount++;
  }
  while ((RunBusyBit == 1) && (StallCount < MAILBOX_WAIT_TIMEOUT));

  if ((RunBusyBit == 1) && (StallCount == MAILBOX_WAIT_TIMEOUT)) {
    Status = mrcFail;
  }

  return Status;
}

/*
  Write CPU Mailbox.

  @param[in]  MailboxType    - CPU mailbox type
  @param[in]  MailboxCommand - CPU mailbox command
  @param[in]  MailboxData    - CPU mailbox data
  @param[out] MailboxStatus  - Completion Code
*/
MrcStatus
MailboxWrite (
  IN UINT32  MailboxType,
  IN UINT32  MailboxCommand,
  IN UINT32  MailboxData,
  OUT UINT32 *MailboxStatus
  )
{
  MrcStatus          Status;
  UINT64             MsrData;
  UINT32             MchBar;
  OC_MAILBOX_FULL    OcMailboxFull;
  OC_MAILBOX_FULL    OcMailboxFullVerify;
  PCODE_MAILBOX_FULL PcodeMailboxFull;
  PCODE_MAILBOX_FULL PcodeMailboxFullVerify;
#ifdef MRC_MINIBIOS_BUILD
  UINT32             Start;
  volatile UINT32    Value;
#endif

  ///
  ///  Poll the run/busy to ensure the interface is available
  ///
  Status = PollMailboxReady (MailboxType);
  if (Status != mrcSuccess) {
    return Status;
  }

  MrcOemOutPort32 (0xCF8, GetPciDeviceAddress (0, 0, 0, UNCORE_CR_MCHBAR_0_0_0_PCI_REG));
  MchBar = MrcOemInPort32 (0xCFC) & ~MRC_BIT0;

  switch (MailboxType) {
    case MAILBOX_TYPE_PCODE:
      ///
      /// Copy in Mailbox data and write the PCODE mailbox DATA field
      ///
      PcodeMailboxFull.Interface.InterfaceData = MailboxCommand;
      PcodeMailboxFull.Data = MailboxData;
      MrcOemMmioWrite32 (MchBar + PCODE_MAILBOX_DATA_OFFSET, PcodeMailboxFull.Data);

      ///
      /// Set the Run/Busy bit to signal mailbox data is ready to process
      ///
      PcodeMailboxFull.Interface.Fields.RunBusy = 1;
      MrcOemMmioWrite32 (MchBar + PCODE_MAILBOX_INTERFACE_OFFSET, PcodeMailboxFull.Interface.InterfaceData);

      ///
      /// Poll run/busy to indicate the completion of write request
      ///
      PollMailboxReady (MailboxType);

      ///
      /// Read the BIOS PCODE mailbox to verify write completion success.
      /// Mailbox protocol requires software to read back the interface twice
      /// to ensure the read results are consistent.
      ///
      PcodeMailboxFull.Interface.InterfaceData = MrcOemMmioRead32 (MchBar + PCODE_MAILBOX_INTERFACE_OFFSET);
      PcodeMailboxFull.Data = MrcOemMmioRead32 (MchBar + PCODE_MAILBOX_DATA_OFFSET);

#ifdef MRC_MINIBIOS_BUILD
      for (Start = 0; Start < (((MAILBOX_READ_TIMEOUT * HPET_1US) + HPET_MIN) / (2 * HPET_MIN)); Start++) {
        //
        // Just perform Dummy reads to CPU CR
        //
        Value = MrcOemMmioRead32 (MchBar + PCODE_MAILBOX_DATA_OFFSET);
      }
#else
      PchPmTimerStall (MAILBOX_READ_TIMEOUT);
#endif
      ///
      /// Read twice to verify data is consitent
      ///
      PcodeMailboxFullVerify.Interface.InterfaceData = MrcOemMmioRead32 (MchBar + PCODE_MAILBOX_INTERFACE_OFFSET);
      PcodeMailboxFullVerify.Data = MrcOemMmioRead32 (MchBar + PCODE_MAILBOX_DATA_OFFSET);

      ///
      /// If the data is inconsistent, we cannot trust the results
      ///
      if (PcodeMailboxFull.Interface.InterfaceData != PcodeMailboxFullVerify.Interface.InterfaceData) {
        if (PcodeMailboxFull.Data  != PcodeMailboxFullVerify.Data) {
          return mrcFail;
        }
      }

      ///
      ///  Copy PCODE mailbox completion code
      ///
      *MailboxStatus = (UINT32) PcodeMailboxFull.Interface.Fields.Command;
      break;

    case MAILBOX_TYPE_OC:
      ///
      /// Set the Run/Busy bit to signal mailbox data is ready to process
      ///
      OcMailboxFull.Interface.InterfaceData = MailboxCommand;
      OcMailboxFull.Data = MailboxData;
      OcMailboxFull.Interface.Fields.RunBusy = 1;
      CopyMem ((UINT8 *) &MsrData, (UINT8 *) &OcMailboxFull, sizeof (MsrData));

      ///
      /// Write mailbox command to OC mailbox
      ///
      WriteMsr64 (OC_MAILBOX_MSR, MsrData);

      ///
      /// Poll run/busy to indicate the completion of write request
      ///
      PollMailboxReady (MailboxType);

      ///
      /// Read the mailbox command from OC mailbox. Read twice to ensure data.
      ///
      MsrData = ReadMsr64 (OC_MAILBOX_MSR);
      CopyMem ((UINT8 *) &OcMailboxFull, (UINT8 *) &MsrData, sizeof (OcMailboxFull));

#ifdef MRC_MINIBIOS_BUILD
      for (Start = 0; Start < (((MAILBOX_READ_TIMEOUT * HPET_1US) + HPET_MIN) / (2 * HPET_MIN)); Start++) {
        //
        // Just perform Dummy reads to CPU CR
        //
        Value = MrcOemMmioRead32 (MchBar + PCODE_MAILBOX_DATA_OFFSET);
      }
#else
      PchPmTimerStall (MAILBOX_READ_TIMEOUT);
#endif

      MsrData = ReadMsr64 (OC_MAILBOX_MSR);
      CopyMem ((UINT8 *) &OcMailboxFullVerify, (UINT8 *) &MsrData, sizeof (OcMailboxFullVerify));

      ///
      /// If the data is inconsistent, we cannot trust the results
      ///
      if (OcMailboxFull.Interface.InterfaceData != OcMailboxFullVerify.Interface.InterfaceData) {
        if (OcMailboxFull.Data != OcMailboxFullVerify.Data) {
          return mrcFail;
        }
      }

      ///
      ///  Copy Overclocking mailbox completion code and read results
      ///
      *MailboxStatus = OcMailboxFull.Interface.Fields.CommandCompletion;
      break;

    default:
      Status = mrcFail;
      break;
  }

  return mrcFail;
}

/*
  Read CPU Mailbox.

  @param[in]  MailboxType    - CPU mailbox type
  @param[in]  MailboxCommand - CPU mailbox command
  @param[out] MailboxDataPtr - CPU mailbox data pointer
  @param[out] MailboxStatus  - Completion Code
*/
MrcStatus
MailboxRead (
  IN  UINT32  MailboxType,
  IN  UINT32  MailboxCommand,
  OUT UINT32  *MailboxDataPtr,
  OUT UINT32  *MailboxStatus
  )
{
  MrcStatus          Status;
  UINT64             MsrData;
  UINT32             MchBar;
  PCODE_MAILBOX_FULL PcodeMailboxFull;
  PCODE_MAILBOX_FULL PcodeMailboxFullVerify;
  OC_MAILBOX_FULL    OcMailboxFull;
  OC_MAILBOX_FULL    OcMailboxFullVerify;
#ifdef MRC_MINIBIOS_BUILD
  UINT32             Start;
  volatile UINT32    Value;
#endif

  ///
  ///  Poll the run/busy to ensure the interface is available
  ///
  Status = PollMailboxReady (MailboxType);
  if (Status != mrcSuccess) {
    return Status;
  }

  MrcOemOutPort32 (0xCF8, GetPciDeviceAddress (0, 0, 0, UNCORE_CR_MCHBAR_0_0_0_PCI_REG));
  MchBar = MrcOemInPort32 (0xCFC) &~MRC_BIT0;

  switch (MailboxType) {
    case MAILBOX_TYPE_PCODE:
      ///
      /// Write the PCODE mailbox read request.
      /// Read requests only require a write to the PCODE interface mailbox.
      /// The read results will be updated in the data mailbox.
      ///
      PcodeMailboxFull.Interface.InterfaceData = MailboxCommand;
      PcodeMailboxFull.Interface.Fields.RunBusy = 1;
      MrcOemMmioWrite32 (MchBar + PCODE_MAILBOX_INTERFACE_OFFSET, PcodeMailboxFull.Interface.InterfaceData);

      ///
      /// Poll run/busy to indicate the completion of read request
      ///
      PollMailboxReady (MailboxType);

      ///
      /// Read the BIOS PCODE mailbox to verify read completion success.
      /// Mailbox protocol requires software to read back the interface twice
      /// to ensure the read results are consistent.
      ///
      PcodeMailboxFull.Interface.InterfaceData = MrcOemMmioRead32 (MchBar + PCODE_MAILBOX_INTERFACE_OFFSET);
      PcodeMailboxFull.Data = MrcOemMmioRead32 (MchBar + PCODE_MAILBOX_DATA_OFFSET);

#ifdef MRC_MINIBIOS_BUILD
      for (Start = 0; Start < (((MAILBOX_READ_TIMEOUT * HPET_1US) + HPET_MIN) / (2 * HPET_MIN)); Start++) {
        //
        // Just perform Dummy reads to CPU CR
        //
        Value = MrcOemMmioRead32 (MchBar + PCODE_MAILBOX_DATA_OFFSET);
      }
#else
      PchPmTimerStall (MAILBOX_READ_TIMEOUT);
#endif
      ///
      /// Read twice to verify data is consitent
      ///
      PcodeMailboxFullVerify.Interface.InterfaceData = MrcOemMmioRead32 (MchBar + PCODE_MAILBOX_INTERFACE_OFFSET);
      PcodeMailboxFullVerify.Data = MrcOemMmioRead32 (MchBar + PCODE_MAILBOX_DATA_OFFSET);

      ///
      /// If the data is inconsistent, we cannot trust the results
      ///
      if (PcodeMailboxFull.Interface.InterfaceData != PcodeMailboxFullVerify.Interface.InterfaceData) {
        if (PcodeMailboxFull.Data  != PcodeMailboxFullVerify.Data) {
          return mrcFail;
        }
      }

      ///
      ///  Copy PCODE mailbox completion code and read results
      ///
      *MailboxStatus = (UINT32) PcodeMailboxFull.Interface.InterfaceData;
      CopyMem ((UINT8 *) MailboxDataPtr, (UINT8 *) &PcodeMailboxFull.Data, sizeof (UINT32));
      break;

    case MAILBOX_TYPE_OC:
      ///
      /// Set the Run/Busy bit to signal mailbox data is ready to process
      ///
      OcMailboxFull.Interface.InterfaceData = MailboxCommand;
      OcMailboxFull.Data = *MailboxDataPtr;
      OcMailboxFull.Interface.Fields.RunBusy = 1;
      CopyMem ((UINT8 *)&MsrData, (UINT8 *) &OcMailboxFull, sizeof (MsrData));

      ///
      /// Write mailbox command to OC mailbox
      ///
      WriteMsr64 (OC_MAILBOX_MSR, MsrData);

      ///
      /// Poll run/busy to indicate the completion of write request
      ///
      PollMailboxReady (MailboxType);

      ///
      /// Read the OC mailbox to verify read completion success.
      /// Mailbox protocol requires software to read back the interface twice
      /// to ensure the read results are consistent.
      ///
      MsrData = ReadMsr64 (OC_MAILBOX_MSR);
      CopyMem ((UINT8 *) &OcMailboxFull, (UINT8 *) &MsrData, sizeof (OcMailboxFull));

#ifdef MRC_MINIBIOS_BUILD
      for (Start = 0; Start < (((MAILBOX_READ_TIMEOUT * HPET_1US) + HPET_MIN) / (2 * HPET_MIN)); Start++) {
        //
        // Just perform Dummy reads to CPU CR
        //
        Value = MrcOemMmioRead32 (MchBar + PCODE_MAILBOX_DATA_OFFSET);
      }
#else
      PchPmTimerStall (MAILBOX_READ_TIMEOUT);
#endif
      MsrData = ReadMsr64 (OC_MAILBOX_MSR);
      CopyMem ((UINT8 *) &OcMailboxFullVerify, (UINT8 *) &MsrData, sizeof (OcMailboxFullVerify));

      ///
      /// If the data is inconsistent, we cannot trust the results
      ///
      if (OcMailboxFull.Interface.InterfaceData != OcMailboxFullVerify.Interface.InterfaceData) {
        if (OcMailboxFull.Data != OcMailboxFullVerify.Data) {
          return mrcFail;
        }
      }

      ///
      ///  Copy Overclocking mailbox completion code and read results
      ///
      *MailboxStatus = OcMailboxFull.Interface.Fields.CommandCompletion;
      CopyMem ((UINT8 *) MailboxDataPtr, (UINT8 *) &OcMailboxFull.Data, sizeof (UINT32));
      break;

    default:
      Status = mrcFail;
      break;
  }

  return Status;
}

/**
  This function checks to see if the MrcSave was saved.

  @retval BOOLEAN - TRUE if MrcSave exists, otherwise FALSE.
**/
BOOLEAN
MrcSaveExists (
  void
  )
{
  return TRUE;
}

/**
  Get MrcSave data.
  Stub mode - get from file.
  MiniBios  - get from flash.

  @param[in, out] SavePtr     - MrcSave address
  @param[in]      BufferSize  - MrcSave size
**/
void
MrcGetMrcSaveData (
  OUT UINT8  *SavePtr,
  IN  UINT32 BufferSize
  )
{
  CopyMem (SavePtr, (UINT8 *) MRC_SAVE_DATA_FLASH_PTR, BufferSize);
}
