/** @file
  This file contains functions to access the register cacheing information.

 @copyright
  INTEL CONFIDENTIAL
  Copyright 2014 - 2017 Intel Corporation.

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

#include "MrcInterface.h"
#include "MrcCommon.h"
#include "MrcRegisterCache.h"
#include "MrcDdrIoDataOffsets.h"

#ifdef SSA_FLAG
typedef enum {
  RegCacheSuccess,
  RegCacheNextFree,
  RegCacheNextWrite,
  RegCacheFull,
  RegCacheMax
} RegCacheStatus;


/**
  Search the register cache for the specified MCHBAR register offset value.

  @param[in]  MrcData - Pointer to MRC global data.
  @param[out] Record  - The index into the register cache that contains the location to read or store data.
  @param[in]  Offset  - MCHBAR register offset.

  @retval 0 = Found, 1 = Not found but Record contains index to next available free location, 2 = Not found but Record contains index to next available location that has read only data, >2 = cache full.
**/
static
RegCacheStatus
SeekCacheLocation (
  MrcParameters *const MrcData,
  UINT16        *const Record,
  const UINT32  Offset
  )
{
  const MrcInput               *Inputs;
  const MRC_FUNCTION           *MrcCall;
  MrcIntOutput                 *MrcIntData;
  MRC_REGISTER_CACHE           *RegisterCache;
  REGISTER_CACHE_OFFSET_STRUCT *Cache;
  UINT16                       Index;
  UINT16                       FirstEmpty;
  UINT16                       FirstReadOnly;

  Inputs        = &MrcData->Inputs;
  MrcCall       = Inputs->Call.Func;
  MrcIntData    = (MrcIntOutput *) MrcData->IntOutputs.Internal;
  RegisterCache = &MrcIntData->Controller[0].RegisterCache;
  FirstEmpty    = MAX_REGISTER_CACHE_ENTRIES;
  FirstReadOnly = MAX_REGISTER_CACHE_ENTRIES;
  Cache         = &RegisterCache->Data[0];
  for (Index = 0; Index < MAX_REGISTER_CACHE_ENTRIES; Index++, Cache++) {
    if (Cache->Flags.Bits.Valid == TRUE) {
      if (Cache->Offset == (UINT16) Offset) {
        *Record = Index;
        return (RegCacheSuccess);
      }
    } else if (FirstEmpty == MAX_REGISTER_CACHE_ENTRIES) {
      FirstEmpty = Index;
    } else if (Cache->Flags.Bits.Write == FALSE) {
      if (FirstReadOnly == MAX_REGISTER_CACHE_ENTRIES) {
        FirstReadOnly = Index;
      }
    }
    if ((FirstEmpty < MAX_REGISTER_CACHE_ENTRIES) && (FirstReadOnly < MAX_REGISTER_CACHE_ENTRIES)) {
      RegisterCache->MaxValid = Index;
      break;
    }
  }

  if (FirstEmpty < MAX_REGISTER_CACHE_ENTRIES) {
    *Record = FirstEmpty;
    return (RegCacheNextFree);
  } else if (FirstReadOnly < MAX_REGISTER_CACHE_ENTRIES) {
    *Record = FirstReadOnly;
    return (RegCacheNextWrite);
  }

  return (RegCacheFull);
}

/**
  Set the current cached 32-bit data value for the specified MCHBAR register.

  @param[in] MrcData - Pointer to MRC global data.
  @param[in] Offset  - MCHBAR register offset.
  @param[in] RegSize - TRUE if Offset points to a 64-bit register, FALSE if Offset points to a 32-bit register.
  @param[in] Flag    - TRUE = read, FALSE = write.
  @param[in] Pending - TRUE = Data has not been written from cache location to hardware register.
  @param[in] Data    - The data.

  @retval The value written to the cache.
**/
static
UINT32
SetCache32 (
  MrcParameters *const MrcData,
  const UINT32  Offset,
  const BOOLEAN RegSize,
  const BOOLEAN Flag,
  const BOOLEAN Pending,
  const UINT32  Data
  )
{
  MrcIntOutput                 *MrcIntData;
  MRC_REGISTER_CACHE           *RegisterCache;
  REGISTER_CACHE_OFFSET_STRUCT *Cache;
  UINT16                       Index;

  MrcIntData    = (MrcIntOutput *) MrcData->IntOutputs.Internal;
  RegisterCache = &MrcIntData->Controller[0].RegisterCache;
  if (SeekCacheLocation (MrcData, &Index, Offset) < RegCacheFull) {
    Cache           = &RegisterCache->Data[Index];
    Cache->Offset   = (UINT16) Offset;
    Cache->Data     = Data;
    Cache->Flags.Bits.Size    = RegSize;
    Cache->Flags.Bits.Pending = Pending;
    Cache->Flags.Bits.Valid   = TRUE;
    if (Flag == FALSE) {
      Cache->Flags.Bits.Write = TRUE;
    }
  } else if (Flag == FALSE) {
    RegisterCache->Overflow = TRUE;
  }
  return (Data);
}

/**
  Get the current cached 64-bit data value for the specified MCHBAR register.
  If it is not in the cache, read it from MMIO space.

  @param[in]  MrcData - Pointer to MRC global data.
  @param[in]  Offset  - MCHBAR register offset.

  @retval The value read.
**/
static
UINT64
GetRegisterCachedData64 (
  MrcParameters *const MrcData,
  const UINT32  Offset
  )
{
  MRC_REGISTER_CACHE           *RegisterCache;
  UINT32                       Status;
  UINT32                       Reg[ (sizeof (UINT64) / sizeof (UINT32)) ];
  UINT16                       Index[ (sizeof (UINT64) / sizeof (UINT32)) ];
  UINT8                        Pass;
  UINT8                        Count;
  union {
    UINT64 Data;
    UINT32 Data32[2];
  } Value;

  RegisterCache = &((MrcIntOutput *) MrcData->IntOutputs.Internal)->Controller[0].RegisterCache;
  Value.Data    = 0;
  Count         = 0;
  Reg[0]        = Offset;
  Reg[1]        = Offset + sizeof (UINT32);

  for (Pass = 0; Pass < (sizeof (Index) / sizeof (Index[0])); Pass++) {
    Status = SeekCacheLocation (MrcData, &Index[Pass], Reg[Pass]);
    if (Status == RegCacheSuccess) {
      Count |= (1 << Pass);
    } else if (Status >= RegCacheFull) {
      RegisterCache->Overflow = TRUE;
    }
  }

  if (Count == 3) {
    for (Pass = 0; Pass < (sizeof (Index) / sizeof (Index[0])); Pass++) {
      Value.Data32[Pass] = RegisterCache->Data[Index[Pass]].Data;
    }
  } else {
    Value.Data = MrcReadCR64 (MrcData, Offset);
    for (Pass = 0; Pass < (sizeof (Index) / sizeof (Index[0])); Pass++) {
      SetCache32 (MrcData, Reg[Pass], TRUE, FALSE, FALSE, Value.Data32[Pass]);
    }
  }

  return (Value.Data);
}

/**
  Set the current cached 64-bit data value for the specified MCHBAR register.

  @param[in]  MrcData - Pointer to MRC global data.
  @param[in]  Offset  - MCHBAR register offset.
  @param[in]  Pending - TRUE = Data has not been written from cache location to hardware register.
  @param[out] Data    - The data.

  @retval The value written.
**/
static
UINT64
SetRegisterCachedData64 (
  MrcParameters *const MrcData,
  const UINT32  Offset,
  const BOOLEAN Pending,
  const UINT64  Data
  )
{
  UINT8                        Pass;
  union {
    UINT64 Data;
    UINT32 Data32[2];
  } Value;

  Value.Data = Data;
  for (Pass = 0; Pass < (sizeof (Value.Data32) / sizeof (Value.Data32[0])); Pass++) {
    SetCache32 (MrcData, Offset + (Pass * sizeof (Value.Data32[0])), TRUE, FALSE, Pending, Value.Data32[Pass]);
  }

  return (Data);
}

/**
  This function updates the current register value in the register cache.

  @param[in] MrcData - Pointer to global data.
  @param[in] RegSize - TRUE if Offset points to a 64-bit register, FALSE if Offset points to a 32-bit register.
  @param[in] Pending - TRUE = Data has not been written from cache location to hardware register.
  @param[in] Socket  - Processor socket in the system (0-based). Not used in Core MRC.
  @param[in] Group   - DDRIO group being accessed.
  @param[in] Channel - DDR Channel Number within the processor socket (0-based).
  @param[in] Rank    - Rank index in the channel. (0-based).
  @param[in] Strobe  - Dqs data group within the rank (0-based).
  @param[in] Value   - New register value.

  @retval The current register value, either from the cache or from hardware if either cache reads are disabled or doesn't exist.
**/
static
VOID
MrcCrCacheUpdate (
  IN MrcParameters *const MrcData,
  IN const BOOLEAN RegSize,
  IN const BOOLEAN Pending,
  IN const GSM_GT  Group,
  IN const UINT32  Socket,
  IN const UINT32  Channel,
  IN const UINT32  Rank,
  IN const UINT32  Strobe,
  IN const UINT64  Value
  )
{
  MrcControllerOut *ControllerOut;
  MrcChannelOut    *ChannelOut;
  UINT64_STRUCT    RegValue;
  UINT32           Offset;
  MRC_REG_OFFSETS  RegOffset;
  UINT32           ChannelStart;
  UINT32           ChannelEnd;
  UINT32           ChannelLoop;
  UINT32           RankStart;
  UINT32           RankEnd;
  UINT32           RankLoop;
  UINT32           StrobeStart;
  UINT32           StrobeEnd;
  UINT32           StrobeLoop;

  RegValue.Data = Value;
  Offset = GetDdrIoDataReadOffsets (Group, (UINT8) Socket, (UINT8) Channel, (UINT8) Rank, (UINT8) Strobe, MRC_IGNORE_ARG_8, MRC_IGNORE_ARG_8, &RegOffset);
  if (Offset == MRC_UINT32_MAX) {
    Offset = GetDdrIoDataWriteOffsets (Group, (UINT8) Socket, (UINT8) Channel, (UINT8) Rank, (UINT8) Strobe, MRC_IGNORE_ARG_8, MRC_IGNORE_ARG_8, &RegOffset);
    if (Offset == MRC_UINT32_MAX) {
      Offset = GetDdrIoDataTrainOffsets (Group, (UINT8) Socket, (UINT8) Channel, (UINT8) Rank, (UINT8) Strobe, MRC_IGNORE_ARG_8, MRC_IGNORE_ARG_8, &RegOffset);
      if (Offset == MRC_UINT32_MAX) {
        return;
      }
    }
  }
  if (RegOffset.BCastType == MrcBcastChannelStrobe) {
    ChannelStart = 0;
    ChannelEnd = MAX_CHANNEL - 1;
    StrobeStart = 0;
    StrobeEnd = MAX_SDRAM_IN_DIMM - 1;
  } else if (RegOffset.BCastType == MrcBcastStrobe) {
    ChannelStart = Channel;
    ChannelEnd = Channel;
    StrobeStart = 0;
    StrobeEnd = MAX_SDRAM_IN_DIMM - 1;
  } else if (RegOffset.BCastType == MrcBcastChannel) {
    ChannelStart = Channel;
    ChannelEnd = Channel;
    StrobeStart = 0;
    StrobeEnd = MAX_SDRAM_IN_DIMM - 1;
  } else if (RegOffset.BCastType == MrcBcastOverall) {
    ChannelStart = 0;
    ChannelEnd = MAX_CHANNEL - 1;
    StrobeStart = 0;
    StrobeEnd = MAX_SDRAM_IN_DIMM - 1;
  } else { // MrcBcastUnicast
    ChannelStart = Channel;
    ChannelEnd = Channel;
    StrobeStart = Strobe;
    StrobeEnd = Strobe;
  }
  RankStart = Rank;
  RankEnd = Rank;
  Offset = RegOffset.BOffset;

  ControllerOut = &MrcData->Outputs.Controller[0];
  for (ChannelLoop = ChannelStart; ChannelLoop <= ChannelEnd; ChannelLoop++) {
    ChannelOut = &ControllerOut->Channel[ChannelLoop];
    for (RankLoop = RankStart; RankLoop <= RankEnd; RankLoop++) {
      for (StrobeLoop = StrobeStart; StrobeLoop <= StrobeEnd; StrobeLoop++) {
        Offset = RegOffset.BOffset + (RegOffset.COffset * ChannelLoop) + (RegOffset.ROffset * RankLoop) + (RegOffset.SOffset * StrobeLoop);
        if (RegSize) {
          SetRegisterCachedData64 (MrcData, Offset, Pending, RegValue.Data);
        } else {
          SetCache32 (MrcData, Offset, FALSE, FALSE, Pending, RegValue.Data32.Low);
        }
      }
    }
  }
  return;
}


/**
  Invalidate the specified data in the register cache.

  @param[in]  MrcData - Pointer to MRC global data.
  @param[in]  Offset  - MCHBAR register offset.

  @retval mrcSuccess if found in the cache, otherwise mrcFail.
**/
MrcStatus
InvalidateRegisterCache (
  MrcParameters *const MrcData,
  const UINT32  Offset
  )
{
  MrcIntOutput                 *MrcIntData;
  MRC_REGISTER_CACHE           *RegisterCache;
  REGISTER_CACHE_OFFSET_STRUCT *Cache;
  UINT16                       Index;

  if (SeekCacheLocation (MrcData, &Index, Offset) == RegCacheSuccess) {
    MrcIntData              = (MrcIntOutput *) MrcData->IntOutputs.Internal;
    RegisterCache           = &MrcIntData->Controller[0].RegisterCache;
    Cache                   = &RegisterCache->Data[Index];
    Cache->Flags.Bits.Valid = FALSE;
    return (mrcSuccess);
  }

  return (mrcFail);
}

/**
  Initialize the register cache.

  @param[in] MrcData - Pointer to MRC global data.

  @retval mrcSuccess.
**/
MrcStatus
InitializeRegisterCache (
  MrcParameters *const MrcData
  )
{
  const MRC_FUNCTION *MrcCall;

  MrcCall = MrcData->Inputs.Call.Func;
  MrcCall->MrcSetMem ((UINT8 *) &((MrcIntOutput *) MrcData->IntOutputs.Internal)->Controller[0].RegisterCache, sizeof (MRC_REGISTER_CACHE), 0);
  return (mrcSuccess);
}

/**
  Flush the register data cache entries marked pending to hardware.

  @param[in]  MrcData - Pointer to MRC global data.

  @retval mrcSuccess.
**/
MrcStatus
FlushRegisterCachedData (
  MrcParameters *const MrcData
  )
{
  MrcIntOutput                 *MrcIntData;
  MRC_REGISTER_CACHE           *RegisterCache;
  REGISTER_CACHE_OFFSET_STRUCT *Cache;
  MrcDebug                     *Debug;
  UINT16                       Index;
  UINT64_STRUCT                Value64;

  Debug         = &MrcData->Outputs.Debug;
  MrcIntData    = ((MrcIntOutput *) (MrcData->IntOutputs.Internal));
  RegisterCache = &MrcIntData->Controller[0].RegisterCache;
  for (Index = 0; Index < MAX_REGISTER_CACHE_ENTRIES; Index++) {
    Cache = &RegisterCache->Data[Index];
    if ((Cache->Flags.Bits.Valid != 0) && (Cache->Flags.Bits.Pending != 0)) {
      if (Cache->Flags.Bits.Size != 0) {
        Value64.Data32.Low = Cache->Data;
        Value64.Data32.High = RegisterCache->Data[Index + 1].Data;
        MrcWriteCR64 (MrcData, Cache->Offset, Value64.Data);
      } else {
        MrcWriteCR (MrcData, Cache->Offset, Cache->Data);
      }
      Cache->Flags.Bits.Pending = 1;
    }
  }
  return (mrcSuccess);
}


/**
  This function sets the current register value and updates corresponding cache location if update cache is enabled.

  @param[in] MrcData - Pointer to global data.
  @param[in] Offset  - Register offset.
  @param[in] RegSize - TRUE if Offset points to a 64-bit register, FALSE if Offset points to a 32-bit register.
  @param[in] Mode    - Bit-field flags controlling cache access.
  @param[in] Group   - DDRIO group being accessed.
  @param[in] Socket  - Processor socket in the system (0-based).  Not used in Core MRC.
  @param[in] Channel - DDR Channel Number within the processor socket (0-based).
  @param[in] Rank    - Rank index in the channel. (0-based).
  @param[in] Strobe  - Dqs data group within the rank (0-based).
  @param[in] Bit     - Bit index within the data group (0-based).
  @param[in] Delay   - Delay in microseconds to invoke after hardware register write.
  @param[in] Value   - New register value.

  @retval mrcSuccess or mrcWrongInputParameter if cache update is enabled and there is no cache entry.
**/
MrcStatus
MrcCrCacheWrite (
  IN MrcParameters *const MrcData,
  IN const UINT32  Offset,
  IN const BOOLEAN RegSize,
  IN const UINT8   Mode,
  IN const GSM_GT  Group,
  IN const UINT32  Socket,
  IN const UINT32  Channel,
  IN const UINT32  Rank,
  IN const UINT32  Strobe,
  IN const UINT32  Bit,
  IN const UINT32  Delay,
  IN const UINT64  Value
  )
{
  UINT64_STRUCT Value64;
  BOOLEAN Pending;

  Value64.Data = Value;
  Pending = TRUE;
  if (((Mode & GSM_FORCE_WRITE) != 0) || ((Mode & GSM_CACHE_ONLY) == 0)) {
    Pending = FALSE;
    if (RegSize) {
      MrcWriteCR64 (MrcData, Offset, Value);
    } else {
      MrcWriteCR (MrcData, Offset, Value64.Data32.Low);
    }
    if (Delay != 0) {
      MrcWait (MrcData, Delay * HPET_1US);
    }
  }
  if ((Mode & GSM_UPDATE_CACHE) != 0) {
    MrcCrCacheUpdate (MrcData, RegSize, Pending, Group, Socket, Channel, Rank, Strobe, Value);
  }
  return (mrcSuccess);
}

/**
  This function gets the current register value, either from the cache or from hardware if either cache reads are disabled or doesn't exist.

  @param[in] MrcData - Pointer to global data.
  @param[in] Offset  - Register offset.
  @param[in] RegSize - TRUE if Offset points to a 64-bit register, FALSE if Offset points to a 32-bit register.
  @param[in] Mode    - Bit-field flags controlling cache access.
  @param[in] Group   - DDRIO group being accessed.
  @param[in] Socket  - Processor socket in the system (0-based).  Not used in Core MRC.
  @param[in] Channel - DDR Channel Number within the processor socket (0-based).
  @param[in] Rank    - Rank index in the channel. (0-based).
  @param[in] Strobe  - Dqs data group within the rank (0-based).
  @param[in] Bit     - Bit index within the data group (0-based).

  @retval The current register value, either from the cache or from hardware if either cache reads are disabled or doesn't exist.
**/
UINT64
MrcCrCacheRead (
  IN MrcParameters *const MrcData,
  IN const UINT32  Offset,
  IN const BOOLEAN RegSize,
  IN const UINT8   Mode,
  IN const GSM_GT  Group,
  IN const UINT32  Socket,
  IN const UINT32  Channel,
  IN const UINT32  Rank,
  IN const UINT32  Strobe,
  IN const UINT32  Bit
  )
{
  MRC_REGISTER_CACHE *RegisterCache;
  RegCacheStatus     Status;
  UINT64_STRUCT      Value;
  UINT16             Index;
  BOOLEAN            Multicast;

  Multicast = FALSE;
  if ((Mode & GSM_READ_CSR) == 0) {
    if (RegSize) {
      GetRegisterCachedData64 (MrcData, Offset);
    } else {
      RegisterCache = &((MrcIntOutput *) MrcData->IntOutputs.Internal)->Controller[0].RegisterCache;
      Status        = SeekCacheLocation (MrcData, &Index, Offset);
      if (Status == RegCacheSuccess) {
        return (RegisterCache->Data[Index].Data);
      }
    }
  }

  if (((Channel != MRC_IGNORE_ARG_8) && (Channel >= MAX_CHANNEL)) ||
      ((Rank != MRC_IGNORE_ARG_8) && (Rank >= MAX_RANK_IN_CHANNEL)) ||
      ((Strobe != MRC_IGNORE_ARG_8) && (Strobe >= MAX_SDRAM_IN_DIMM))) {
    Multicast = TRUE;
  }

  Value.Data = RegSize ? MrcReadCR64 (MrcData, Offset) : MrcReadCR (MrcData, Offset);
  if ((!Multicast && ((Mode & GSM_UPDATE_CACHE) != 0))) {
    SetCache32 (MrcData, Offset, FALSE, FALSE, FALSE, Value.Data32.Low);
    if (RegSize) {
      SetCache32 (MrcData, Offset + sizeof (UINT32), FALSE, FALSE, FALSE, Value.Data32.High);
    }
  }
  return (Value.Data);
}
#endif // SSA_FLAG
