/** @file
  File to support address decoding and encoding

 @copyright
  INTEL CONFIDENTIAL
  Copyright 1999 - 2016 Intel Corporation.

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

#ifdef MRC_MINIBIOS_BUILD
#define DEBUG(Expression)
#include "MrcOemPlatform.h"
#include "MemoryUtils.h"
#include <MrcRegisters/Pci000.h>
#include <MrcRegisters/MrcMcRegister.h>
#include <MrcRegisters/MrcMcRegisterStruct.h>
#else // MRC_MINIBIOS_BUILD
#include <Uefi.h>
#include <SaRegs.h>
#include <Library/DebugLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/IoLib.h>
#include <Library/BaseLib.h>
#endif // MRC_MINIBIOS_BUILD
#include <MrcTypes.h>
#include <Library/MemoryAddressEncodeDecodeLib.h>

GLOBAL_REMOVE_IF_UNREFERENCED const UINT8 ConfigArrayConst [50][35]= {
  {  0,  0,  0,  0, 15, 14, 13,  0, 31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17, 16,  0, 12, 11, 10,  9, 8, 7, 6, 5, 4, 3},
  {  1, 16,  0,  0, 15, 14, 13,  0, 32, 31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17,  0, 12, 11, 10,  9, 8, 7, 6, 5, 4, 3},
  {  2,  0, 15,  0, 16, 14, 13,  0, 32, 31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17,  0, 12, 11, 10,  9, 8, 7, 6, 5, 4, 3},
  {  3, 17, 15,  0, 16, 14, 13,  0, 33, 32, 31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18,  0, 12, 11, 10,  9, 8, 7, 6, 5, 4, 3},
  {  4, 16, 17,  0, 15, 14, 13,  0, 33, 32, 31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18,  0, 12, 11, 10,  9, 8, 7, 6, 5, 4, 3},
  {  5, 16,  0,  0, 15, 14, 13,  0, 32, 31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17,  0, 12, 11, 10,  9, 8, 7, 6, 5, 4, 3},
  {  6,  0,  0,  0, 16, 15, 14,  0, 32, 31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17, 13, 12, 11, 10,  9, 8, 7, 6, 5, 4, 3},
  {  7, 17,  0,  0, 16, 15, 14,  0, 33, 32, 31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 13, 12, 11, 10,  9, 8, 7, 6, 5, 4, 3},
  {  8,  0, 16,  0, 17, 15, 14,  0, 33, 32, 31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 13, 12, 11, 10,  9, 8, 7, 6, 5, 4, 3},
  {  9, 18, 16,  0, 17, 15, 14,  0, 34, 33, 32, 31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 13, 12, 11, 10,  9, 8, 7, 6, 5, 4, 3},
  { 10, 17, 18,  0, 16, 15, 14,  0, 34, 33, 32, 31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 13, 12, 11, 10,  9, 8, 7, 6, 5, 4, 3},
  { 11, 17,  0,  0, 16, 15, 14,  0, 33, 32, 31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 13, 12, 11, 10,  9, 8, 7, 6, 5, 4, 3},
  { 12, 16,  0,  0, 17, 15, 14,  0, 33, 32, 31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 13, 12, 11, 10,  9, 8, 7, 6, 5, 4, 3},
  { 13, 16,  0,  0, 15, 14, 13,  0, 32, 31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17,  0, 12, 11, 10,  9, 8, 7, 6, 5, 4, 3},
  { 14, 17, 16,  0, 18, 15, 14,  0, 34, 33, 32, 31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 13, 12, 11, 10,  9, 8, 7, 6, 5, 4, 3},
  { 15, 17, 16,  0, 15, 14, 13,  0, 33, 32, 31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18,  0, 12, 11, 10,  9, 8, 7, 6, 5, 4, 3},
  { 16, 16,  0,  0, 17, 15, 14,  0, 33, 32, 31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 13, 12, 11, 10,  9, 8, 7, 6, 5, 4, 3},
  { 17, 16, 17,  0, 15, 14, 13,  0, 33, 32, 31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18,  0, 12, 11, 10,  9, 8, 7, 6, 5, 4, 3},
  { 18, 16, 17,  0, 18, 15, 14,  0, 34, 33, 32, 31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 13, 12, 11, 10,  9, 8, 7, 6, 5, 4, 3},
  { 19, 16,  0,  0, 15, 14, 13,  0, 32, 31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17,  0, 12, 11, 10,  9, 8, 7, 6, 5, 4, 3},
  { 20,  0,  0, 14,  6, 16, 15, 33, 32, 31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17,  0, 13, 12, 11, 10, 9, 8, 7, 5, 4, 3},
  { 21, 17,  0, 14,  6, 16, 15, 34, 33, 32, 31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18,  0, 13, 12, 11, 10, 9, 8, 7, 5, 4, 3},
  { 22,  0, 15, 14,  6, 17, 16, 34, 33, 32, 31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18,  0, 13, 12, 11, 10, 9, 8, 7, 5, 4, 3},
  { 23, 17, 15, 14,  6, 18, 16, 35, 34, 33, 32, 31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19,  0, 13, 12, 11, 10, 9, 8, 7, 5, 4, 3},
  { 24, 17, 15, 14,  6, 18, 16, 35, 34, 33, 32, 31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19,  0, 13, 12, 11, 10, 9, 8, 7, 5, 4, 3},
  { 25, 17,  0, 14,  6, 16, 15, 34, 33, 32, 31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18,  0, 13, 12, 11, 10, 9, 8, 7, 5, 4, 3},
  { 26,  0,  0,  0,  6, 15, 14, 32, 31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17, 16,  0, 13, 12, 11, 10, 9, 8, 7, 5, 4, 3},
  { 27, 16,  0,  0,  6, 15, 14, 33, 32, 31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17,  0, 13, 12, 11, 10, 9, 8, 7, 5, 4, 3},
  { 28,  0, 14,  0,  6, 16, 15, 33, 32, 31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17,  0, 13, 12, 11, 10, 9, 8, 7, 5, 4, 3},
  { 29, 16, 14,  0,  6, 17, 15, 34, 33, 32, 31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18,  0, 13, 12, 11, 10, 9, 8, 7, 5, 4, 3},
  { 30, 16, 14,  0,  6, 17, 15, 34, 33, 32, 31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18,  0, 13, 12, 11, 10, 9, 8, 7, 5, 4, 3},
  { 31, 16,  0,  0,  6, 15, 14, 33, 32, 31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17,  0, 13, 12, 11, 10, 9, 8, 7, 5, 4, 3},
  { 32, 17,  0, 14,  6, 16, 15, 34, 33, 32, 31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18,  0, 13, 12, 11, 10, 9, 8, 7, 5, 4, 3},
  { 33, 17,  0,  0,  6, 15, 14, 33, 32, 31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 16,  0, 13, 12, 11, 10, 9, 8, 7, 5, 4, 3},
  { 34, 17, 15, 14,  6, 18, 16, 35, 34, 33, 32, 31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19,  0, 13, 12, 11, 10, 9, 8, 7, 5, 4, 3},
  { 35, 17, 14,  0,  6, 16, 15, 34, 33, 32, 31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18,  0, 13, 12, 11, 10, 9, 8, 7, 5, 4, 3},
  { 36, 17, 15, 14,  6, 18, 16, 35, 34, 33, 32, 31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19,  0, 13, 12, 11, 10, 9, 8, 7, 5, 4, 3},
  { 37, 17,  0,  0,  6, 15, 14, 33, 32, 31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 16,  0, 13, 12, 11, 10, 9, 8, 7, 5, 4, 3},
  { 38, 17, 14,  0,  6, 16, 15, 34, 33, 32, 31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18,  0, 13, 12, 11, 10, 9, 8, 7, 5, 4, 3},
  { 39, 17,  0, 14,  6, 16, 15, 34, 33, 32, 31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18,  0, 13, 12, 11, 10, 9, 8, 7, 5, 4, 3},
  { 40,  0,  0, 14,  6, 16, 15, 33, 32, 31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17,  0, 13, 12, 11, 10, 9, 8, 7, 5, 4, 3},
  { 41,  0,  0,  0,  6, 15, 14, 32, 31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17, 16,  0, 13, 12, 11, 10, 9, 8, 7, 5, 4, 3},
  { 42,  0,  0,  0, 15, 14, 13,  0, 31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17, 16,  0, 12, 11, 10,  9, 8, 7, 6, 5, 4, 3},
  { 43,  0,  0,  0, 16, 15, 14,  0, 32, 31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17, 13, 12, 11, 10,  9, 8, 7, 6, 5, 4, 3},
  { 44,  0,  0,  0, 15, 14, 13,  0,  0, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17, 16,  0, 12, 11, 10,  9, 8, 7, 6, 5, 4, 3},
  { 45,  0, 15,  0, 16, 14, 13,  0,  0, 31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17,  0, 12, 11, 10,  9, 8, 7, 6, 5, 4, 3},
  { 46,  0,  0,  0, 16, 15, 14,  0,  0, 31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17, 13, 12, 11, 10,  9, 8, 7, 6, 5, 4, 3},
  { 47,  0, 16,  0, 17, 15, 14,  0,  0, 32, 31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 13, 12, 11, 10,  9, 8, 7, 6, 5, 4, 3},
  { 48,  0,  0,  0, 15, 14, 13,  0,  0, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17, 16,  0, 12, 11, 10,  9, 8, 7, 6, 5, 4, 3},
  { 49,  0,  0,  0, 16, 15, 14,  0,  0, 31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17, 13, 12, 11, 10,  9, 8, 7, 6, 5, 4, 3}
};

GLOBAL_REMOVE_IF_UNREFERENCED const UINT8 EnhConfigArrayConst [50][8]= {
  {  0,  0,  0,  0, 18, 17, 16,  0},
  {  1, 20,  0,  0, 19, 18, 17,  0},
  {  2,  0, 19,  0, 20, 18, 17,  0},
  {  3, 22, 20,  0, 21, 19, 18,  0},
  {  4, 21, 22,  0, 20, 19, 18,  0},
  {  5, 21,  0,  0, 20, 19, 18,  0},
  {  6,  0,  0,  0, 19, 18, 17,  0},
  {  7, 21,  0,  0, 20, 19, 18,  0},
  {  8,  0, 20,  0, 21, 19, 18,  0},
  {  9, 23, 21,  0, 22, 20, 19,  0},
  { 10, 22, 23,  0, 21, 20, 19,  0},
  { 11, 22,  0,  0, 21, 20, 19,  0},
  { 12, 21,  0,  0, 22, 20, 19, 18},
  { 13, 21,  0,  0, 20, 19, 18,  0},
  { 14, 22, 21,  0, 23, 20, 19, 18},
  { 15, 22, 21,  0, 20, 19, 18,  0},
  { 16, 21,  0,  0, 22, 20, 19, 18},
  { 17, 21, 22,  0, 20, 19, 18,  0},
  { 18, 21, 22,  0, 23, 20, 19, 18},
  { 19, 21,  0,  0, 20, 19, 18,  0},
  { 20,  0,  0, 17, 13, 19, 18,  0},
  { 21, 21,  0, 18, 13, 20, 19,  0},
  { 22,  0, 19, 18, 13, 21, 20,  0},
  { 23, 22, 20, 19, 13, 23, 21,  0},
  { 24, 22, 20, 19, 13, 23, 21,  0},
  { 25, 22,  0, 19, 13, 21, 20,  0},
  { 26,  0,  0,  0, 13, 17, 16,  0},
  { 27, 19,  0,  0, 13, 18, 17,  0},
  { 28,  0, 17,  0, 13, 19, 18,  0},
  { 29, 20, 18,  0, 13, 21, 19,  0},
  { 30, 20, 18,  0, 13, 21, 19,  0},
  { 31, 20,  0,  0, 13, 19, 18,  0},
  { 32, 19,  0, 17, 13,  0, 18,  0},
  { 33, 19,  0,  0, 13, 18, 17,  0},
  { 34, 21, 19, 18, 13, 22, 20,  0},
  { 35, 21, 18,  0, 13, 20, 19,  0},
  { 36, 21, 20, 19, 13, 22,  0,  0},
  { 37, 21,  0,  0, 13, 20, 19,  0},
  { 38, 21, 18,  0, 13, 20, 19,  0},
  { 39, 21,  0, 18, 13, 20, 19,  0},
  { 40,  0,  0, 17, 13, 19, 18,  0},
  { 41,  0,  0,  0, 13, 18, 17,  0},
  { 42,  0,  0,  0, 18, 17, 16,  0},
  { 43,  0,  0,  0, 19, 18, 17,  0},
  { 44,  0,  0,  0, 18, 17, 16,  0},
  { 45,  0, 19,  0, 20, 18, 17,  0},
  { 46,  0,  0,  0, 19, 18, 17,  0},
  { 47,  0, 20,  0, 21, 19, 18,  0},
  { 48,  0,  0,  0, 18, 17, 16,  0},
  { 49,  0,  0,  0, 19, 18, 17,  0}
};

typedef UINT32       (*MRC_IO_READ_32)              (UINT32 IoAddress);
typedef void         (*MRC_IO_WRITE_32)             (UINT32 IoAddress, UINT32 Value);
typedef UINT32       (*MRC_MMIO_READ_32)            (UINT32 Address);
typedef UINT64       (*MRC_MMIO_READ_64)            (UINT32 Address);
typedef void *       (*MRC_MEMORY_COPY)             (UINT8 *Destination, UINT8 *Source, UINT32 NumBytes);
typedef void *       (*MRC_MEMORY_SET_BYTE)         (UINT8 *Destination, UINT32 NumBytes, UINT8 Value);
typedef UINT64       (*MRC_LEFT_SHIFT_64)           (UINT64 Data, UINT32 NumBits);
typedef UINT64       (*MRC_RIGHT_SHIFT_64)          (UINT64 Data, UINT32 NumBits);
typedef UINT64       (*MRC_MULT_U64_U32)            (UINT64 Multiplicand, UINT32 Multiplier);
typedef UINT64       (*MRC_DIV_U64_U64)             (UINT64 Dividend, UINT64 Divisor, UINT64 *Remainder);

///
/// Function calls that are called external to the MRC.
///   This structure needs to be aligned with SA_FUNCTION_CALLS.  All functions that are
///   not apart of SA_FUNCTION_CALLS need to be at the end of the structure.
///
typedef struct {
  MRC_IO_READ_32              MrcIoRead32;
  MRC_IO_WRITE_32             MrcIoWrite32;
  MRC_MMIO_READ_32            MrcMmioRead32;
  MRC_MMIO_READ_64            MrcMmioRead64;
  MRC_MEMORY_COPY             MrcCopyMem;
  MRC_MEMORY_SET_BYTE         MrcSetMem;
  MRC_LEFT_SHIFT_64           MrcLeftShift64;
  MRC_RIGHT_SHIFT_64          MrcRightShift64;
  MRC_MULT_U64_U32            MrcMultU64x32;
  MRC_DIV_U64_U64             MrcDivU64x64;
} MRC_ADDR_FUNCTION;

#ifdef MRC_MINIBIOS_BUILD
#define R_SA_MCHBAR                                UNCORE_CR_MCHBAR_0_0_0_PCI_REG
#define R_SA_PCIEXBAR                              UNCORE_CR_PCIEXBAR_0_0_0_PCI_REG
#define R_SA_TOLUD                                 UNCORE_CR_TOLUD_0_0_0_PCI_REG
#define R_SA_REMAPBASE                             UNCORE_CR_REMAPBASE_0_0_0_PCI_REG
#define R_SA_REMAPLIMIT                            UNCORE_CR_REMAPLIMIT_0_0_0_PCI_REG
#define R_SA_TOM                                   UNCORE_CR_TOM_0_0_0_PCI_REG

#define R_SA_MCHBAR_MAD_INTER_CHANNEL_OFFSET       MCDECS_CR_MAD_INTER_CHANNEL_MCMAIN_REG
#define R_SA_MCHBAR_MAD_INTRA_CH0_OFFSET           MCDECS_CR_MAD_INTRA_CH0_MCMAIN_REG
#define R_SA_MCHBAR_MAD_INTRA_CH1_OFFSET           MCDECS_CR_MAD_INTRA_CH1_MCMAIN_REG
#define R_SA_MCHBAR_MAD_DIMM_CH0_OFFSET            MCDECS_CR_MAD_DIMM_CH0_MCMAIN_REG
#define R_SA_MCHBAR_MAD_DIMM_CH1_OFFSET            MCDECS_CR_MAD_DIMM_CH1_MCMAIN_REG
#define R_SA_MCHBAR_CHANNEL_HASH_OFFSET            MCDECS_CR_CHANNEL_HASH_MCMAIN_REG
#endif

//
// Bit-Masks used to remove or test register fields
//
#define MC_ADDR_CHANNEL_HASH_MASK_SIZE      14

#define MC_ADDR_TOLUD_MASK                  0xFFF00000
#define MC_ADDR_REMAP_MASK                  0x0000007FFFF00000ULL
#define MC_ADDR_CHAN_HASH_ENABLE_MASK       0x10000000
#define MAXFLDSIZE                          50
#define DRAM_ADDR_SIZE                      34

#define MC_ADDR_REMAP_LIMIT_LOWER_BITS_MASK 0x00000000000FFFFFULL

#define ONE_BIT_MASK                        1
#define TWO_BIT_MASK                        3
#define THREE_BIT_MASK                      7
#define FOUR_BIT_MASK                       15

#define DIMM_NUM_BITS                       1
#define RANK_NUM_BITS                       1
#define BG_NUM_BITS                         2
#define BANK_NUM_BITS                       2
#define ROW_NUM_BITS                        17
#define COL_NUM_BITS                        11
#define ENHANCED_BITS_SIZE                  DIMM_NUM_BITS + RANK_NUM_BITS + BG_NUM_BITS + BANK_NUM_BITS + 1

//
// Useful number constants
//
#define MC_512MB_AS_CL  (1 << 23)
#define MC_1GB_AS_CL    (1 << 24)
#define MC_2GB_AS_CL    (1 << 25)
#define MC_4GB_AS_CL    (1 << 26)
#define MC_8GB_AS_CL    (1 << 27)
#define MC_16GB_AS_CL   (1 << 28)
#define MC_32GB_AS_CL   (1 << 29)
#define MC_64GB_AS_CL   (1 << 30)
#define MC_128GB_AS_CL  (1 << 31)

#define MC_NUM_BER_REGS 4

//
// Functions to extract fields from the registers
//
static
UINT16
get_ddr_type (
  UINT32 MAD_INTER_CHNL
  )
{
  return (UINT16) (MAD_INTER_CHNL & 3); // MAD_INTER_CHNL[1:0]; 0=DDR4; 1=DDR3; 2=LPDDR3;
}

static
UINT64
get_dimm_l_size_as_cl (
  const MRC_ADDR_FUNCTION *MrcCall,
  UINT32 MAD_DIMM
  )
{
  return MrcCall->MrcLeftShift64 ((((UINT64) MAD_DIMM) & 0x003FULL), 24); // MAD_DIMM[ 5:0]*1GB
}

static
UINT64
get_dimm_s_size_as_cl (
  const MRC_ADDR_FUNCTION *MrcCall,
  UINT32 MAD_DIMM
  )
{
  return MrcCall->MrcLeftShift64 ((((UINT64) MAD_DIMM) & 0x003F0000ULL), 8); // MAD_DIMM[21:16]*1GB
}

static
BOOLEAN
get_dimm_and_rank_intlv (
  UINT32 MAD_INTRA_CHNL
  )
{
  return (BOOLEAN) ((MAD_INTRA_CHNL >> 4) & 1); // MAD_INTRA_CHNL[4:4]
}

static
BOOLEAN
get_high_order_intlv_mode (
  UINT32 MAD_INTRA_CHNL
  )
{
  return (BOOLEAN) ((MAD_INTRA_CHNL >> 24) & 1); // MAD_INTRA_CHNL[24:24]
}

static
UINT16
get_hori_addr (
  UINT32 MAD_INTRA_CHNL
  )
{
  return (UINT16) ((MAD_INTRA_CHNL >> 28) & 7); // MAD_INTRA_CHNL[30:28]
}

static
BOOLEAN
get_enhanced_intlv_mode (
  UINT32 MAD_INTRA_CHNL
  )
{
  return (BOOLEAN) ((MAD_INTRA_CHNL >> 8) & 1); // MAD_INTRA_CHNL[8:8]
}

static
UINT16
get_dimm_l_select (
  UINT32 MAD_INTRA_CHNL
  )
{
  return (UINT16) (MAD_INTRA_CHNL & 1);
}

static
BOOLEAN
get_dimm_l_number_of_ranks (
  UINT32 MAD_DIMM
  )
{
  return (BOOLEAN) ((MAD_DIMM >> 10) & 1);
}

static
BOOLEAN
get_dimm_s_number_of_ranks (
  UINT32 MAD_DIMM
  )
{
  return (BOOLEAN) ((MAD_DIMM >> 26) & 1);
}

static
UINT16
get_dimm_l_width (
  UINT32 MAD_DIMM
  )
{
  UINT16  width;
  width = (UINT16) ((MAD_DIMM >> 8) & 3);
  //
  // 0-x8, 1-x16, 2-x32
  //
  if (width < 2) {
    return (UINT16) ((width + 1) << 3);
  } else {
    return (UINT16) ((width + 2) << 3);
  }
}

static
UINT16
get_dimm_s_width (
  UINT32 MAD_DIMM
  )
{
  UINT16  width;
  width = (UINT16) ((MAD_DIMM >> 24) & 3);
  //
  // 0-x8, 1-x16, 2-x32
  //
  if (width < 2) {
    return (UINT16) ((width + 1) << 3);
  } else {
    return (UINT16) ((width + 2) << 3);
  }
}

static
UINT64
get_dimm_l_rank_size_as_cl (
  const MRC_ADDR_FUNCTION *MrcCall,
  UINT32 MAD_DIMM
  )
{
  return MrcCall->MrcRightShift64 (get_dimm_l_size_as_cl (MrcCall, MAD_DIMM), ((UINT16) get_dimm_l_number_of_ranks (MAD_DIMM)));
}

static
UINT64
get_dimm_s_rank_size_as_cl (
  const MRC_ADDR_FUNCTION *MrcCall,
  UINT32 MAD_DIMM
  )
{
  return MrcCall->MrcRightShift64 (get_dimm_s_size_as_cl (MrcCall, MAD_DIMM), ((UINT16) get_dimm_s_number_of_ranks (MAD_DIMM)));
}

UINT16
get_dimm_l_num_col_bits (
  const MRC_ADDR_FUNCTION *MrcCall,
  UINT16 ddr_type,
  UINT32 MAD_DIMM
  )
{
  UINT16 width;
  UINT64 dimm_rank_size_as_cl;

  if (ddr_type == 0) {
    return 10;
  }
  //
  // If we got past the above line, we are LPDDR3/DDR3
  //
  width                = get_dimm_l_width (MAD_DIMM);
  dimm_rank_size_as_cl = get_dimm_l_rank_size_as_cl (MrcCall, MAD_DIMM);

  if ((ddr_type == 2) && (width == 16)) {
    return (dimm_rank_size_as_cl == MC_1GB_AS_CL) ? 10 : 11;
  } else if ((ddr_type == 2) && (width == 32)) {
    return (dimm_rank_size_as_cl == MC_512MB_AS_CL) ? 9 : 10;
  } else {
    return (dimm_rank_size_as_cl == MC_8GB_AS_CL) ? 11 : 10;
  }
}

UINT16
get_dimm_s_num_col_bits (
  const MRC_ADDR_FUNCTION *MrcCall,
  UINT16 ddr_type,
  UINT32 MAD_DIMM
  )
{
  UINT16 width;
  UINT64 dimm_rank_size_as_cl;

  if (ddr_type == 0) {
    return 10;
  }
  width                = get_dimm_s_width (MAD_DIMM);
  dimm_rank_size_as_cl = get_dimm_s_rank_size_as_cl (MrcCall, MAD_DIMM);

  if ((ddr_type == 2) && (width == 16)) {
    return (dimm_rank_size_as_cl == MC_1GB_AS_CL) ? 10 : 11;
  } else if ((ddr_type == 2) && (width == 32)) {
    return (dimm_rank_size_as_cl == MC_512MB_AS_CL) ? 9 : 10;
  } else {
    return (dimm_rank_size_as_cl == MC_8GB_AS_CL) ? 11 : 10;
  }
}

static
UINT16
get_ch_hash_lsb_mask_bit (
  UINT32 CHANNEL_HASH
  )
{
  return (CHANNEL_HASH >> 24) & 3;
}

static
UINT16
get_ch_hash_mask (
  UINT32 CHANNEL_HASH
  )
{
  return (CHANNEL_HASH >> 6) & 0x0003FFF;
}

static
BOOLEAN
get_stacked_mode (
  UINT32 MAD_INTER_CHNL
  )
{
  return (BOOLEAN) ((MAD_INTER_CHNL >> 8) & 1);
}

static
BOOLEAN
get_stacked_mode_ch1 (
  UINT32 MAD_INTER_CHNL
  )
{
  return (BOOLEAN) ((MAD_INTER_CHNL >> 9) & 1);
}

static
UINT16
get_stacked_encoding (
  UINT32 MAD_INTER_CHNL
  )
{
  return (UINT16) (MAD_INTER_CHNL >> 24) & 7;
}

static
UINT16
get_ch_l_map (
  UINT32 MAD_INTER_CHNL
  )
{
  return (UINT16) (MAD_INTER_CHNL >> 4) & 1;
}

static
UINT64
get_ch_s_size_as_cl (
  const MRC_ADDR_FUNCTION *MrcCall,
  UINT32 MAD_INTER_CHNL
  )
{
  return MrcCall->MrcLeftShift64 ((((UINT64) MAD_INTER_CHNL) & 0x007F000ULL), 12);
}

static
UINT16
get_dimm_l_8Gb (
  UINT32 MAD_DIMM
  )
{
  return (UINT16) (MAD_DIMM >> 11) & 1;
}

static
UINT16
get_dimm_s_8Gb (
  UINT32 MAD_DIMM
  )
{
  return (UINT16) (MAD_DIMM >> 27) & 1;
}

//
// Functions to get BER fields
//
static
UINT16
get_ber_chan (
  UINT32 BER_TGT
  )
{
  return (UINT16) ((BER_TGT >> 31) & 0x1UL);
}

static
UINT16
get_ber_dimm (
  UINT32 MAD_INTER_CHNL,
  UINT32 BER_TGT
  )
{
  return (UINT16) ((BER_TGT >> 30) & 0x1UL);
}

static
UINT16
get_ber_rank (
  UINT32 MAD_INTER_CHNL,
  UINT32 BER_TGT
  )
{
  return (UINT16) ((BER_TGT >> 29) & 0x1UL);
}

static
UINT16
get_ber_bg (
  UINT32 MAD_INTER_CHNL,
  UINT32 BER_TGT
  )
{
  return (UINT16) ((BER_TGT >> 27) & 0x3UL);
}

static
UINT16
get_ber_bank (
  UINT32 MAD_INTER_CHNL,
  UINT32 BER_TGT
  )
{
  return (UINT16) ((BER_TGT >> 25) & 0x7UL);
}

static
UINT32
get_ber_row (
  UINT32 BER_TGT
  )
{
  return (UINT32) ((BER_TGT >> 8) & 0x1FFFFUL);
}

static
UINT16
get_ber_col (
  UINT32 BER_TGT
  )
{
  return (UINT16) ((BER_TGT & 0xFFUL) << 3);
}

static
BOOLEAN
get_ber_valid (
  const MRC_ADDR_FUNCTION *MrcCall,
  UINT64 BER_SRC
  )
{
  return (BOOLEAN) (MrcCall->MrcRightShift64 (BER_SRC, 63) & 0x1ULL);
}

static
UINT64
get_ber_sys_addr (
  UINT64 BER_SRC
  )
{
  return BER_SRC & 0x0000007FFFFFFFC0ULL;
}

static
BOOLEAN
get_ber_is_tcm (
  const MRC_ADDR_FUNCTION *MrcCall,
  UINT64 BER_SRC
  )
{
  return (BOOLEAN) (MrcCall->MrcRightShift64 (BER_SRC, 62) & 0x1ULL);
}

//
// Functions to aid in common tasks
// make mask for a certain bits
//
UINT64
get_x_bit_mask (
  const MRC_ADDR_FUNCTION *MrcCall,
  INT16 num_bit
  )
{
  UINT64  x_bit_mask;
  x_bit_mask = 0x00FFFFFFFFULL;
  return MrcCall->MrcRightShift64 (x_bit_mask, (UINT32) (32 - num_bit));
}

//
// Get a nubmer in kilo-bytes
//
static
UINT32
in_kb (
  UINT32 number
  )
{
  return number << 10;
}

//
// convert a cache-line address to a system address
//
static
UINT64
cl_to_sys (
  const MRC_ADDR_FUNCTION *MrcCall,
  UINT64 cache_line
  )
{
  return MrcCall->MrcLeftShift64 (cache_line, 6);
}

//
// Channel conversion functions. For logical channels: 0=L, 1=S.
//
static
UINT16
logical_to_physical_chan (
  UINT32 MAD_INTER_CHNL,
  UINT16 logical_chan
  )
{
  return (UINT16) (((MAD_INTER_CHNL >> 4) & 1) ^ (logical_chan));
}

static
UINT16
physical_to_logical_chan (
  UINT32 MAD_INTER_CHNL,
  UINT16 physical_chan
  )
{

  return ((((UINT16) ((MAD_INTER_CHNL >> 4) & 1)) == physical_chan) ? 0 : 1);
  //
  // 0=L, 1=S
  //
}

//
// Function for decode of stacked channel debug feature
//
static
UINT64
get_stacked_memory_size (
  const MRC_ADDR_FUNCTION *MrcCall,
  UINT16 i_stacked_encoding
  )
{
  return MrcCall->MrcLeftShift64 (0x01000000ULL, i_stacked_encoding);
}

//
// Function to determine if a system address matches an *ENABLED* BER_SRC register
//
static
BOOLEAN
en_sys_ber_match (
  const MRC_ADDR_FUNCTION *MrcCall,
  UINT64  sys_addr,
  BOOLEAN is_tcm,
  UINT64  BER_SRC
  )
{
  return (get_ber_valid (MrcCall, BER_SRC) &&
          ((sys_addr & 0x07FFFFFFFC0ULL) == get_ber_sys_addr (BER_SRC)) &&
          (is_tcm == get_ber_is_tcm (MrcCall, BER_SRC)));
}

//
// Function to determine if a DRAM address matches a BER_TGT register (enabled or not).
//
static
BOOLEAN
dram_ber_match (
  UINT16 chan,
  UINT16 dimm,
  UINT16 rank,
  UINT16 bg,
  UINT16 bank,
  UINT32 row,
  UINT16 col,
  UINT32 BER_TGT,
  UINT32 MAD_INTER_CHNL
  )
{
  return ((chan == get_ber_chan (BER_TGT)) &&
          (dimm == get_ber_dimm (MAD_INTER_CHNL, BER_TGT)) &&
          (rank == get_ber_rank (MAD_INTER_CHNL, BER_TGT)) &&
          (bg == get_ber_bg (MAD_INTER_CHNL, BER_TGT)) &&
          (bank == get_ber_bank (MAD_INTER_CHNL, BER_TGT)) &&
          (row == get_ber_row (BER_TGT)) &&
          ((col & 0xFFF8) == get_ber_col (BER_TGT)));
}


//
// Function for parsing the decode shifters numbers from the decode map
// ------------------------------------------------------------------------------
// config_arr   0           1       2       3       4       5       6       7
//              config_case DIMM0   RANK0   BG1     BG0     BANK1   BANK0   ROW15
//              8           9       10      11      12      13      14      15
//              ROW14       ROW13   ROW12   ROW11   ROW10   ROW9    ROW8    ROW7
//              16          17      18      19      20      21      22      23
//              ROW6        ROW5    ROW4    ROW3    ROW2    ROW1    ROW0    CAS10
//              24          25      26      27      28      29      30      31
//              CAS9        CAS8    CAS7    CAS6    CAS5    CAS4    CAS3    CAS2
//              32          33
//              CAS1        CAS0
// ------------------------------------------------------------------------------
// The config_arr holds all the shifters for the decode function
//
VOID
addr_decode_map_parse (
  const MRC_ADDR_FUNCTION *MrcCall,
  UINT8   *config_arr,
  UINT8   config_case,
  BOOLEAN second_round
  )
{
  UINT8 i;
  UINT8 curr_cfg;

  //
  // Gets the configuration case we need.
  //
  for (i = 0; i < MAXFLDSIZE; i++) {
    curr_cfg = ConfigArrayConst[i][0];
    if (second_round) {
      if (curr_cfg == config_case) {
        break;
      }
    } else {
      //
      // Approximate config case is good enough for first round
      //
      if ((curr_cfg >= config_case) && (curr_cfg < (config_case + 1))) {
        break;
      }
    }
  }
  //
  // Found a configuration - copying it to the config array
  //
  MrcCall->MrcCopyMem ((UINT8 *) config_arr, (UINT8 *) &ConfigArrayConst[i], sizeof (ConfigArrayConst[i]));
}

VOID
enhanced_mode_map_parse (
  const MRC_ADDR_FUNCTION *MrcCall,
  UINT8   *enh_config_arr,
  UINT8   config_case,
  BOOLEAN second_round
  )
{
  UINT8 i;

  //
  // Gets the configuration case we need.
  //
  for (i = 0; i < MAXFLDSIZE; i++) {
    if (second_round) {
      if (EnhConfigArrayConst[i][0] == config_case) {
        break;
      }
    } else {
      //
      // Approximate config case is good enough for first round
      //
      if ((EnhConfigArrayConst[i][0] >= config_case) && (EnhConfigArrayConst[i][0] < (config_case + 1))) {
        break;
      }
    }
  }
  //
  // Found a configuration - copying it to the config array
  //
  MrcCall->MrcCopyMem ((UINT8 *) enh_config_arr, (UINT8 *) &EnhConfigArrayConst[i], sizeof (EnhConfigArrayConst[i]));
}

//
// Gives back the configuration case
//
UINT8
get_the_config_case_num (
  UINT16  ddr_type,
  UINT16  num_of_dimms,
  UINT16  num_of_ranks,
  UINT16  dimm_l_num_of_ranks,
  UINT16  DDR3_8Gb_x8_num_of_dimms,
  UINT16  dimm_l_8Gb,
  UINT16  dimm_l_width,
  BOOLEAN same_dimm_width,
  BOOLEAN dimm_and_rank_interleaving,
  BOOLEAN zone0
  )
{
  UINT8 config_case;

  config_case = 0;

  if (ddr_type == 1) {
    //
    // DDR3
    //
    if (!dimm_and_rank_interleaving) {
      return 42;
    } else if (DDR3_8Gb_x8_num_of_dimms == 0) {
      //
      // DDR3 excluding 8Gb x8
      //
      if (num_of_dimms == 1) {
        switch (num_of_ranks) {
          case 1:
            config_case = 0;
            return config_case;

          case 2:
            config_case = 2;
            return config_case;
        }
      }

      if (num_of_dimms == 2) {
        switch (num_of_ranks) {
          case 2:
            config_case = zone0 ? 1 : 0;
            return config_case;

          case 3:
            config_case = zone0 ? 4 : (dimm_l_num_of_ranks ? 2 : 0);
            return config_case;

          case 4:
            config_case = zone0 ? 3 : 2;
            return config_case;
        }
      }
    } else if (DDR3_8Gb_x8_num_of_dimms == num_of_dimms) {
      //
      // DDR3 only 8Gb x8
      //
      if (num_of_dimms == 1) {
        switch (num_of_ranks) {
          case 1:
            config_case = 6;
            return config_case;

          case 2:
            config_case = 8;
            return config_case;
        }
      }

      if (num_of_dimms == 2) {
        switch (num_of_ranks) {
          case 2:
            config_case = zone0 ? 7 : 6;
            return config_case;

          case 3:
            config_case = zone0 ? 10 : (dimm_l_num_of_ranks ? 8 : 6);
            return config_case;

          case 4:
            config_case = zone0 ? 9 : 8;
            return config_case;
        }
      }
    } else {
      //
      // DDR3 8Gb x8 and other
      //
      switch (num_of_ranks) {
        case 2:
          config_case = zone0 ? 12 : 6;
          return config_case;

        case 3:
          if (dimm_l_num_of_ranks == 1) {
            if ((dimm_l_8Gb == 1) && (dimm_l_width == 8)) {
              config_case = zone0 ? 18 : 8;
            } else {
              config_case = zone0 ? 16 : 2;
            }
          } else {
            if ((dimm_l_8Gb == 1) && (dimm_l_width == 8)) {
              config_case = zone0 ? 16 : 6;
            } else {
              config_case = 16;
            }
          }
          return config_case;

        case 4:
          config_case = zone0 ? 14 : 8;
          return config_case;
      }
    }
  } else if (ddr_type == 0) {
    //
    // DDR4
    //
    if (!dimm_and_rank_interleaving) {
      return 40;
    }

    if (same_dimm_width) {
      if (dimm_l_width == 8) {
        //
        // DDR4 x8
        //
        if (num_of_dimms == 1) {
          switch (num_of_ranks) {
            case 1:
              config_case = 20;
              return config_case;

            case 2:
              config_case = 22;
              return config_case;
          }
        }

        if (num_of_dimms == 2) {
          switch (num_of_ranks) {
            case 2:
              config_case = zone0 ? 21 : 20;
              return config_case;

            case 3:
              config_case = zone0 ? 24 : (dimm_l_num_of_ranks ? 22 : 20);
              return config_case;

            case 4:
              config_case = zone0 ? 23 : 22;
              return config_case;
          }
        }
      } else {
        //
        // DDR4 x16
        //
        if (num_of_dimms == 1) {
          switch (num_of_ranks) {
            case 1:
              config_case = 26;
              return config_case;

            case 2:
              config_case = 28;
              return config_case;
          }
        }

        if (num_of_dimms == 2) {
          switch (num_of_ranks) {
            case 2:
              config_case = zone0 ? 27 : 26;
              return config_case;

            case 3:
              config_case = zone0 ? 30 : (dimm_l_num_of_ranks ? 28 : 26);
              return config_case;

            case 4:
              config_case = zone0 ? 29 : 28;
              return config_case;
          }
        }

      }
    } else {
      //
      // DDR4 x8 & x16
      //
      switch (num_of_ranks) {
        case 2:
          config_case = zone0 ? 32 : ((dimm_l_width == 8) ? 20 : 26);
          return config_case;

        case 3:
          if (dimm_l_num_of_ranks == 1) {
            if (dimm_l_width == 16) {
              config_case = zone0 ? 38 : 28;
            } else {
              config_case = zone0 ? 36 : 22;
            }
          } else {
            if (dimm_l_width == 16) {
              config_case = zone0 ? 36 : 26;
            } else {
              config_case = zone0 ? 38 : 20;
            }
          }

          return config_case;

        case 4:
          config_case = zone0 ? 34 : ((dimm_l_width == 8) ? 22 : 28);
          return config_case;
      }

    }
  } else {
    //
    // LPDDR3
    //
    if (!dimm_and_rank_interleaving) {
      return 48;
    } else {
      if (dimm_l_width == 16) {
        //
        // LPDDR x16
        //
        switch (num_of_ranks) {
          case 1:
            config_case = 46;
            return config_case;

          case 2:
            config_case = 47;
            return config_case;
        }
      } else if (dimm_l_width == 32) {
        //
        // LPDDR x32
        //
        switch (num_of_ranks) {
          case 1:
            config_case = 44;
            return config_case;

          case 2:
            config_case = 45;
            return config_case;
        }
      }
    }
  }

  return config_case;
}

/**
  Address decode function
  Converts system address to DRAM address

  @param[in]      MrcCall            - pointer to MRC_ADDR_FUNCTION struct
  @param[in]      sys_addr           - the 39-bit system address to convert
  @param[in, out] p_is_tcm           - is the transaction to sys_addr "traffic class for the manageability engine"
  @param[in]      TOLUD              - memory register
  @param[in]      REMAP_BASE         - memory register
  @param[in]      REMAP_LIMIT        - memory register
  @param[in]      TOM                - memory register
  @param[in]      CHANNEL_HASH       - memory register
  @param[in]      MAD_INTER_CHNL     - memory register
  @param[in]      MAD_INTRA_CHNL_ch0 - memory register
  @param[in]      MAD_INTRA_CHNL_ch1 - memory register
  @param[in]      MAD_DIMM_ch0       - memory register
  @param[in]      MAD_DIMM_ch1       - memory register
  @param[in]      BER_SRC[]          - memory register
  @param[in]      BER_TGT[]          - memory register
  @param[in]      BER_MC_ABORT       - memory register
  @param[out]     p_chan             - channel sys_addr decodes to
  @param[out]     p_dimm             - DIMM sys_addr decodes to
  @param[out]     p_rank             - rank sys_addr decodes to
  @param[out]     p_bg               - bank group sys_addr decodes to
  @param[out]     p_bank             - bank sys_addr decodes to
  @param[out]     p_row              - row sys_addr decodes to
  @param[out]     p_col              - column sys_addr decodes to.

  @retval TRUE if successful.

**/
BOOLEAN
MrcDecode (
  IN const MRC_ADDR_FUNCTION *MrcCall,
  IN       UINT64       sys_addr,
  IN OUT   BOOLEAN      *p_is_tcm,
  IN       UINT32       TOLUD,
  IN       UINT64       REMAP_BASE,
  IN       UINT64       REMAP_LIMIT,
  IN       UINT64       TOM,
  IN       UINT32       CHANNEL_HASH,
  IN       UINT32       MAD_INTER_CHNL,
  IN       UINT32       MAD_INTRA_CHNL_ch0,
  IN       UINT32       MAD_INTRA_CHNL_ch1,
  IN       UINT32       MAD_DIMM_ch0,
  IN       UINT32       MAD_DIMM_ch1,
  IN       UINT64       BER_SRC[],
  IN       UINT32       BER_TGT[],
  IN       UINT32       BER_MC_ABORT,
  OUT      UINT16       *p_chan,
  OUT      UINT16       *p_dimm,
  OUT      UINT16       *p_rank,
  OUT      UINT16       *p_bg,
  OUT      UINT16       *p_bank,
  OUT      UINT32       *p_row,
  OUT      UINT16       *p_col
  )
{
  //
  // These vars are used to get the configuration case
  //
  UINT16  D8Gb;  // 0-> NOT 8Gb; 1-> 8Gb
  UINT16  hash_lsb_mask_bit;  // LsbMaskBit field from CHANNEL_HASH register
  UINT16  hash_mask;  // channel hash mask from CHANNEL_HASH register
  UINT16  chnl_num_of_dimms;
  UINT16  chnl_num_of_ranks;
  BOOLEAN same_dimm_width;
  UINT16  DDR3_8Gb_x8_num_of_dimms;
  UINT64  remap_addr;  // full address
  UINT64  remap_line;  // cache-line address
  UINT16  hash_line;  // lower bits of remap_line with hash_mask applied
  UINT16  i;
  UINT16  j;
  UINT64  chan_line;  // channel address space (cache-line)
  UINT16  chan_select;  // 0 = Channel L, 1 = Channel S
  UINT32  selected_mad_dimm;  // MAD_DIMM for the selected channel
  UINT32  selected_mad_intra_chnl;  // MAD_INTRA_CHNL for the selected channel
  UINT64  dimm_l_size;  // sizes of the DIMMs on the channel in cache-lines
  UINT64  dimm_s_size;
  BOOLEAN dimm_and_rank_interleaving;  // modes for the selected channel
  BOOLEAN high_order_rank_interleave;
  BOOLEAN enhanced_interleave_mode;
  UINT16  hori_addr;  // bits to use from address for HORI
  UINT64  dimm_line;  // DIMM address space (cache-line)
  UINT16  dimm_select;  // 0 = DIMM L, 1 = DIMM S
  UINT16  dimm_select_arr[DIMM_NUM_BITS];
  UINT16  rank_select_arr[RANK_NUM_BITS];
  UINT16  bg_select_arr[BG_NUM_BITS];
  UINT16  bank_select_arr[BANK_NUM_BITS];
  UINT16  row_select_arr[ROW_NUM_BITS];
  UINT16  col_select_arr[COL_NUM_BITS];
  UINT32  dimm_size;  // size of selected DIMM (cache-lines)
  BOOLEAN dual_rank;  // number of ranks on selected DIMM
  UINT16  dimm_width;
  //
  // Temporary values for bit masking and shifting
  //
  UINT64  row_mask;
  UINT16  rank_bit_shift;
  //
  // Virtual arrays to get the inputs from the addr_decode_maps.csv table, according to the configuration
  //
  UINT8   config_arr[DRAM_ADDR_SIZE + 1];
  //
  // Virtual arrays to get the inputs from the enhanced_mode_map.csv table, according to the configuration
  //
  UINT8   enh_config_arr[ENHANCED_BITS_SIZE + 1];
  UINT8   config_case_num;
  UINT8   config_case_num_int_for_switch;
  UINT8   converter_step;
  //
  // Shifters for bit select (from chnl_addr)according to the address decode map
  //
  INT16   dimm_shifter[DIMM_NUM_BITS];
  INT16   rank_shifter[RANK_NUM_BITS];
  INT16   bg_shifter[BG_NUM_BITS];
  INT16   bank_shifter[BANK_NUM_BITS];
  INT16   row_shifter[ROW_NUM_BITS];
  INT16   col_shifter[COL_NUM_BITS];
  INT16   dimm_enhanced_shifter[DIMM_NUM_BITS];
  INT16   rank_enhanced_shifter[RANK_NUM_BITS];
  INT16   bg_enhanced_shifter[BG_NUM_BITS];
  INT16   bank_enhanced_shifter[BANK_NUM_BITS];
  INT16   col_enhanced_shifter[COL_NUM_BITS];
  //
  // Shifters for bit select not from the address decode map
  //
  UINT16  BANK_SHIFTER_NO_INT;
  UINT16  BANK_ENHANCED_SHIFTER_NO_INT;
  UINT16  ddr_type;                       // DDR4=0; DDR3=1; LPDDR3=2;
  BOOLEAN stacked_mode;                   // channel stacking enabled
  BOOLEAN stacked_mode_ch1;               // Stacking channel 0 on top of channel 1
  UINT16  stacked_encoding;               // Stacked mode channel hash bits
  UINT64  stacked_size;                   // The size of the channels in stacked mode (according to stacked_encoding) (cl address)
  UINT32  mad_dimm_l[2];                  // Make a MAD_DIMM array for easy access
  UINT32  mad_intra_chnl_l[2];            // Make a MAD_INTRA_CHNL array for easy access
  UINT64  ch_s_size;                      // chanel s_size adjusted to cl address
  UINT16  ch_l_map;                       // Virtual channel L mapping (0 - CH 0; 1 - CH 1)
  UINT32  chan_l_mad_dimm;                // channel L's MAD_DIMM register
  UINT32  tolud;                          // TOLUD register after verification and cleanup (system address)
  UINT64  remap_base;                     // REMAP_BASE register after verification and cleanup (system address)
  UINT64  remap_limit;                    // REMAP_LIMIT register after verification and cleanup (system address)
  UINT64  tom;                            // Top Of Memory (system address)
  UINT64  tom_in_cl;                      // Top Of Memory (cl address)
  UINT64  remap_size;                     // size of the remap region (system address)
  UINT64  gap_top;                        // one address above the gap (the remap target region) (system address)
  UINT64  gap_limit;                      // MMIO Gap Limit (system address)
  BOOLEAN ber_en = FALSE;                 // Indicates id BER is enabled
  UINT64  ber_target_base;                // Base address to stolen memory in which BER target DRAM addresses reside (system address)
  UINT32  ber_target_size = 0;            // The size of stolen memory in which BER target DRAM addresses reside (system address)
  BOOLEAN lpddr3_6Gb_dev  = FALSE;        // Indicates we're using LPDDR3 6Gb DRAM devices - restricts some rules
  UINT64 calculated_tom;
  UINT64 Remainder;

  MrcCall->MrcSetMem ((UINT8 *) dimm_select_arr, sizeof (dimm_select_arr), 0);
  MrcCall->MrcSetMem ((UINT8 *) rank_select_arr, sizeof (rank_select_arr), 0);
  MrcCall->MrcSetMem ((UINT8 *) bg_select_arr, sizeof (bg_select_arr), 0);
  MrcCall->MrcSetMem ((UINT8 *) bank_select_arr, sizeof (bank_select_arr), 0);
  MrcCall->MrcSetMem ((UINT8 *) row_select_arr, sizeof (row_select_arr), 0);
  MrcCall->MrcSetMem ((UINT8 *) col_select_arr, sizeof (col_select_arr), 0);
  MrcCall->MrcSetMem ((UINT8 *) config_arr, sizeof (config_arr), 0);
  MrcCall->MrcSetMem ((UINT8 *) enh_config_arr, sizeof (enh_config_arr), 0);
  MrcCall->MrcSetMem ((UINT8 *) dimm_shifter, sizeof (dimm_shifter), 0);
  MrcCall->MrcSetMem ((UINT8 *) rank_shifter, sizeof (rank_shifter), 0);
  MrcCall->MrcSetMem ((UINT8 *) bg_shifter, sizeof (bg_shifter), 0);
  MrcCall->MrcSetMem ((UINT8 *) bank_shifter, sizeof (bank_shifter), 0);
  MrcCall->MrcSetMem ((UINT8 *) row_shifter, sizeof (row_shifter), 0);
  MrcCall->MrcSetMem ((UINT8 *) col_shifter, sizeof (col_shifter), 0);
  MrcCall->MrcSetMem ((UINT8 *) dimm_enhanced_shifter, sizeof (dimm_enhanced_shifter), 0);
  MrcCall->MrcSetMem ((UINT8 *) rank_enhanced_shifter, sizeof (rank_enhanced_shifter), 0);
  MrcCall->MrcSetMem ((UINT8 *) bg_enhanced_shifter, sizeof (bg_enhanced_shifter), 0);
  MrcCall->MrcSetMem ((UINT8 *) bank_enhanced_shifter, sizeof (bank_enhanced_shifter), 0);
  MrcCall->MrcSetMem ((UINT8 *) col_enhanced_shifter, sizeof (col_enhanced_shifter), 0);

  stacked_mode_ch1             = 0;
  stacked_size                 = 0;
  dimm_line                    = 0;
  dimm_select                  = 0;
  BANK_SHIFTER_NO_INT          = 7;
  BANK_ENHANCED_SHIFTER_NO_INT = 10;

  ddr_type            = get_ddr_type (MAD_INTER_CHNL);
  tolud               = TOLUD & MC_ADDR_TOLUD_MASK;
  remap_base          = REMAP_BASE & MC_ADDR_REMAP_MASK;
  remap_limit         = REMAP_LIMIT & MC_ADDR_REMAP_MASK;
  tom                 = TOM & MC_ADDR_REMAP_MASK;
  remap_limit        |= MC_ADDR_REMAP_LIMIT_LOWER_BITS_MASK;
  remap_size          = remap_limit + 1 - remap_base;
  gap_top             = tolud + remap_size;
  mad_dimm_l[0]       = MAD_DIMM_ch0;
  mad_dimm_l[1]       = MAD_DIMM_ch1;
  mad_intra_chnl_l[0] = MAD_INTRA_CHNL_ch0;
  mad_intra_chnl_l[1] = MAD_INTRA_CHNL_ch1;

  //
  // Calculate TOM
  //
  ch_s_size       = get_ch_s_size_as_cl (MrcCall, MAD_INTER_CHNL);
  ch_l_map        = get_ch_l_map (MAD_INTER_CHNL);
  chan_l_mad_dimm = mad_dimm_l[ch_l_map];

  //
  // If we use LPDDR3 6Gb DRAM devices then the actual DRAM size is quarter less then configured in SKL
  // SKL feature f95150
  //
  lpddr3_6Gb_dev  = FALSE;

  calculated_tom  = cl_to_sys (MrcCall, get_dimm_l_size_as_cl (MrcCall, chan_l_mad_dimm));
  calculated_tom += cl_to_sys (MrcCall, get_dimm_s_size_as_cl (MrcCall, chan_l_mad_dimm));
  calculated_tom += cl_to_sys (MrcCall, ch_s_size);

  if ((ddr_type == 2) && (tom == MrcCall->MrcDivU64x64 (MrcCall->MrcMultU64x32 (calculated_tom, 3), 4, &Remainder))) {
    lpddr3_6Gb_dev = TRUE;
  }

  tom_in_cl = MrcCall->MrcRightShift64 (tom, 6);

  //
  // Determine if we are in stacked mode; and if so, what the stacked size is.
  //
  stacked_mode = get_stacked_mode (MAD_INTER_CHNL);
  if (stacked_mode) {
    stacked_mode_ch1  = get_stacked_mode_ch1 (MAD_INTER_CHNL);
    stacked_encoding  = get_stacked_encoding (MAD_INTER_CHNL);
    stacked_size      = get_stacked_memory_size (MrcCall, stacked_encoding);
  }

  //
  // Updating Bit-Error-Recovery related paramenters
  //
  ber_en = FALSE;

  for (i = 0; i < MC_NUM_BER_REGS; i++) {
    if (get_ber_valid (MrcCall, BER_SRC[i])) {
      ber_en = TRUE;
    }
  }
  //
  // Setting Bit-Error-Recovery target base address.
  // This area is reserved area ot the size of ber_target_size (4K if enabled) below TOM
  //
  if (ber_en) {
    ber_target_size = in_kb (4);
    ber_target_base = tom - ber_target_size;
  } else {
    ber_target_size = 0;
    ber_target_base = tom;
  }


  //
  // Remap the address if it is not a TCM transaction and falls inside the remap range
  //
  remap_addr = sys_addr;
  if (remap_limit > remap_base) {
    //
    // Check for remap region being enabled
    //
    gap_limit = ((UINT64) tolud) + remap_limit - remap_base;

    //
    // Check for address falling in remap region
    //
    if ((sys_addr >= remap_base) && (sys_addr <= remap_limit)) {
      if (*p_is_tcm) {
        if (sys_addr >= tom) {

          //
          // Transaction to sys_addr should not have been TCM.
          //
          *p_is_tcm = FALSE;

          return FALSE;
        }
      } else {
        //
        // The address hit the remap region, so remap the address from the remap
        // source region (REMAP_BASE to REMAP_LIMIT) to the remap target region
        // (TOLUD to size-of-gap).
        //
        remap_addr -= remap_base;
        remap_addr += ((UINT64) tolud);
      }
    }
    //
    // Check for address falling in the ME STOLEN region, when TOM is less than 4GB.
    //
    else if ((sys_addr < tom) && (sys_addr > gap_limit) && (tom <= 0x100000000ULL)) {
      if (*p_is_tcm) {
        remap_addr = sys_addr;
      } else {
        remap_addr = sys_addr;
      }
    }
    //
    // Check for address falling in MMIO gap created by remap region
    //
    else if ((sys_addr >= ((UINT64) tolud)) && (sys_addr <= gap_limit)) {

      //
      // Transaction to sys_addr should not have been TCM.
      //
      *p_is_tcm = FALSE;
      return FALSE;
    } else {
      //
      // No remap
      //
    }
  } // if (remap_limit > remap_base) {
  else {
  }
  //
  // From now on we will work on cache-line addresses
  //
  remap_line = MrcCall->MrcRightShift64 (remap_addr, 6);

  if (stacked_mode) {
    //
    // In stacked mode, check that remapped address is below TOM.
    //
    if (remap_line >= tom_in_cl) {
      return FALSE;
    }
    //
    // If we are in stacked channel mode, then the memory from the channels is stacked to create the system memory.
    //
    //  +------0.5 TB------+
    //  |                  |
    //  .                  .
    //  .                  .
    //  .                  .
    //  |                  |
    //  |  unmapped        |
    //  |  space above     |
    //  |  DRAM            |
    //  |                  |
    //  +--2 * Stack size--+  <-- Top Of Memory = L + S
    //  |                  |
    //  |                  |
    //  |                  |
    //  |   Channel S      |
    //  |                  |
    //  |                  |
    //  +--- Stack size ---+  <-- Stack Size = Channel size (channels L and S must be equal)
    //  |                  |
    //  |                  |
    //  |                  |
    //  |   Channel L      |
    //  |                  |
    //  |                  |
    //  +--------0x0-------+
    //
    chan_select = (remap_line < stacked_size) ? 0 : 1;

    chan_line = remap_line;

    //
    // If this is channel 1 in stacked mode, then we need to subtract out the channel size (clear
    // the stacked mode bit)
    //
    if (chan_select == 1) {
      chan_line = chan_line - stacked_size;
    }

    if (stacked_mode_ch1) {
      chan_select ^= 1;
    }
  }
  //
  // Channel Interleaving Zones
  //
  // Determine which range/zone the remapped system address falls into
  //
  //  +-----0.5 TB-----+
  //  |                |
  //  .                .
  //  .                .
  //  .                .
  //  |                |
  //  |  unmapped      |
  //  |  space above   |
  //  |  DRAM          |
  //  |                |
  //  +--Zone 1 Limit--+  <-- Top Of Memory = L + S
  //  |                |
  //  |  No Interleave |
  //  |    Channel L   |
  //  |                |
  //  +--Zone 0 Limit--+  <-- 2 * S
  //  |                |
  //  |                |
  //  |                |
  //  |  2-Way Intlv   |
  //  | Channels L & S |
  //  |                |
  //  |                |
  //  |                |
  //  |                |
  //  +-------0x0------+
  //
  else if (remap_line < MrcCall->MrcLeftShift64 (ch_s_size, 1)) {
    //
    // Zone 0
    //
    //
    // Determine if the channel hash feature is being used
    //
    if (CHANNEL_HASH & MC_ADDR_CHAN_HASH_ENABLE_MASK) {
      hash_lsb_mask_bit = get_ch_hash_lsb_mask_bit (CHANNEL_HASH);
      hash_mask         = get_ch_hash_mask (CHANNEL_HASH);
      hash_mask         = hash_mask | (1 << hash_lsb_mask_bit);
      hash_line         = ((UINT16) remap_line) & hash_mask;
      //
      // Produce chan_select by XORing together all of the bits of hash_line.
      //
      chan_select = 0;
      for (i = 0; i < MC_ADDR_CHANNEL_HASH_MASK_SIZE; i++) {
        chan_select = chan_select ^ (hash_line >> i);
      }

      chan_select = chan_select & 1;

      //
      // sys_addr 6 will be shifted off to produce the channel address, so it must
      // be preserved if it wasn't used in the hash.  This is done by moving it to
      // the position indicated by hash_lsb_mask_bit.
      //
      remap_line = remap_line & (~MrcCall->MrcLeftShift64 (0x0000000000000001ULL, hash_lsb_mask_bit));
      remap_line = remap_line | MrcCall->MrcLeftShift64 ((remap_line & 1), hash_lsb_mask_bit);
    } else {
      chan_select = (UINT16) (remap_line & 1);
    }
    chan_line = MrcCall->MrcRightShift64 (remap_line, 1);

  } else if (remap_line < tom_in_cl) {
    //
    // Zone 1
    //
    chan_select = 0;
    chan_line = remap_line - ch_s_size;

  } else {
    //
    // Address was above memory capacity
    //
    return FALSE;
  }

  //
  // Obtain the physical channel index
  //
  *p_chan = logical_to_physical_chan (MAD_INTER_CHNL, chan_select);

  //
  // Get the register for the channel we're using
  //
  selected_mad_dimm       = mad_dimm_l[*p_chan];
  selected_mad_intra_chnl = mad_intra_chnl_l[*p_chan];

  //
  // Find the DIMM sizes on our selected channel. adjust to cache-line granularity
  //
  dimm_l_size = get_dimm_l_size_as_cl (MrcCall, selected_mad_dimm);
  dimm_s_size = get_dimm_s_size_as_cl (MrcCall, selected_mad_dimm);

  //
  // Find number of ranks and dimms in the selected channel
  //
  chnl_num_of_dimms = (dimm_l_size) ? ((dimm_s_size) ? 2 : 1) : 0;
  chnl_num_of_ranks =
    (dimm_l_size) ? (get_dimm_l_number_of_ranks (selected_mad_dimm) ?
    ((dimm_s_size) ? (get_dimm_s_number_of_ranks (selected_mad_dimm) ? 4 : 3) : 2) :
    ((dimm_s_size) ? (get_dimm_s_number_of_ranks (selected_mad_dimm) ? 3 : 2) : 1)) : 0;

  //
  // Find the dimm width chnl configuration
  //
  same_dimm_width = (dimm_s_size) ? ((get_dimm_l_width (selected_mad_dimm) == get_dimm_s_width (selected_mad_dimm)) ? TRUE : FALSE) : TRUE;

  //
  // Check the num of DDR3 8Gb dimms
  //
  DDR3_8Gb_x8_num_of_dimms =
    (chnl_num_of_dimms == 2) ?
    ((get_dimm_l_8Gb (selected_mad_dimm) == 1 && get_dimm_l_width (selected_mad_dimm) == 8) ?
    ((get_dimm_s_8Gb (selected_mad_dimm) == 1 && get_dimm_s_width (selected_mad_dimm) == 8) ? 2 : 1)
    : ((get_dimm_s_8Gb (selected_mad_dimm) == 1 && get_dimm_s_width (selected_mad_dimm) == 8) ? 1 : 0))
    : ((get_dimm_l_8Gb (selected_mad_dimm) == 1 && get_dimm_l_width (selected_mad_dimm) == 8) ? 1 : 0);

  //
  // Determine if we are doing DIMM and Rank interleaving
  //
  dimm_and_rank_interleaving = get_dimm_and_rank_intlv (selected_mad_intra_chnl);

  //
  // Determine if we are doing high order rank interleave
  //
  high_order_rank_interleave = get_high_order_intlv_mode (selected_mad_intra_chnl);

  //
  // Determine if we are doing Enhanced Interleave Mode (EIM) (XOR rank, bg & bank bits)
  //
  enhanced_interleave_mode = get_enhanced_intlv_mode (selected_mad_intra_chnl);

  //
  // Get the configuration case
  //
  config_case_num = get_the_config_case_num (
                      ddr_type,
                      chnl_num_of_dimms,
                      chnl_num_of_ranks,
                      get_dimm_l_number_of_ranks (selected_mad_dimm),
                      DDR3_8Gb_x8_num_of_dimms,
                      get_dimm_l_8Gb (selected_mad_dimm),
                      get_dimm_l_width (selected_mad_dimm),
                      same_dimm_width,
                      dimm_and_rank_interleaving,
                      TRUE
                      );

  config_case_num_int_for_switch = config_case_num;

  //
  // Calling the parsing method, to get the address decode map for the current configuration.
  // This is the first call, just to know the DIMM shifters
  // in the case of no interleave mode, we don't need this call
  //
  if (dimm_and_rank_interleaving) {
    addr_decode_map_parse (MrcCall, config_arr, config_case_num, FALSE);
    if (enhanced_interleave_mode) {
      enhanced_mode_map_parse (MrcCall, enh_config_arr, config_case_num, FALSE);
    }
  }
  //
  // Dimm_shifters
  //
  for (i = 0; i < DIMM_NUM_BITS; i++) {
    dimm_shifter[i] = (config_arr[i + 1] - 6);
    if (enhanced_interleave_mode) {
      dimm_enhanced_shifter[i] = (enh_config_arr[i + 1] - 6);
    }
  }

  //
  // DIMM address calculation
  // DIMMs are interleaved for both dimm_and_rank_interleaving and high_order_rank_interleave modes.
  //
  if (dimm_and_rank_interleaving || high_order_rank_interleave) {
    //
    // DIMM and Rank interleaving enabled
    //  +------32 GB------+
    //  |                 |
    //  .                 .
    //  .                 .
    //  .                 .
    //  |                 |
    //  |  unmapped       |
    //  |  space above    |
    //  |  channel        |
    //  |  capacity       |
    //  |                 |
    //  +-- Zone 1 Limit--+  <-- dimm_l_size + dimm_s_size
    //  |                 |
    //  |  No Interleave  |
    //  |     DIMM L      |
    //  |                 |
    //  +-- Zone 0 Limit--+  <-- dimm_s_size * 2
    //  |                 |
    //  | 2-Way Interleave|
    //  |   DIMMs L & S   |
    //  |                 |
    //  +-------0x0-------+
    //
    if (chan_line < MrcCall->MrcLeftShift64 (dimm_s_size, 1)) {
      //
      // Range 0
      //
      config_case_num = get_the_config_case_num (
                          ddr_type,
                          chnl_num_of_dimms,
                          chnl_num_of_ranks,
                          get_dimm_l_number_of_ranks (selected_mad_dimm),
                          DDR3_8Gb_x8_num_of_dimms,
                          get_dimm_l_8Gb (selected_mad_dimm),
                          get_dimm_l_width (selected_mad_dimm),
                          same_dimm_width,
                          dimm_and_rank_interleaving,
                          TRUE
                          );
      config_case_num_int_for_switch = config_case_num;

      //
      // Calling the parsing method, to get the address decode map for the current configuration.
      // This is the first call, just to know the DIMM shifters
      // in the case of no interleave mode, we don't need this call
      //
      if (dimm_and_rank_interleaving) {
        addr_decode_map_parse (MrcCall, config_arr, config_case_num, FALSE);
        if (enhanced_interleave_mode) {
          enhanced_mode_map_parse (MrcCall, enh_config_arr, config_case_num, FALSE);
        }
      }
      //
      // 2-way DIMM interleave. Channel address is used to select DIMM according to the decode map.
      //
      for (i = 0; i < DIMM_NUM_BITS; i++) {
        dimm_select_arr[i] = (UINT16) (MrcCall->MrcRightShift64 (chan_line, dimm_shifter[i]) & 1);
        if (enhanced_interleave_mode) {
          if (dimm_enhanced_shifter[i] == -6) {
          } else {
            dimm_select_arr[i] = dimm_select_arr[i] ^ (MrcCall->MrcRightShift64 (chan_line, dimm_enhanced_shifter[i]) & 1);
          }
        }
      }

      dimm_select = 0;
      for (i = 0; i < DIMM_NUM_BITS; i++) {
        dimm_select += (dimm_select_arr[i] << i);
      }

      //
      // DIMM address is channel address with the interleave bits removed
      //
      dimm_line = (MrcCall->MrcRightShift64 (chan_line, 1) & (~((UINT64) get_x_bit_mask (MrcCall, dimm_select_arr[0] - 6)))) | (chan_line & ((UINT64) get_x_bit_mask (MrcCall, dimm_select_arr[0] - 6)));
      for (i = 1; i < DIMM_NUM_BITS; i++) {
        dimm_line = (MrcCall->MrcRightShift64 (dimm_line, 1) & (~((UINT64) get_x_bit_mask (MrcCall, dimm_select_arr[0] - 6 + i)))) | (dimm_line & ((UINT64) get_x_bit_mask (MrcCall, dimm_select_arr[0] - 6 + i)));
      }
      dimm_line = chan_line;
    } else if (chan_line < (dimm_l_size + dimm_s_size)) {
      //
      // Range 1
      //

      //
      // Get the configuration case
      //
      config_case_num = get_the_config_case_num (
                          ddr_type,
                          chnl_num_of_dimms,
                          chnl_num_of_ranks,
                          get_dimm_l_number_of_ranks (selected_mad_dimm),
                          DDR3_8Gb_x8_num_of_dimms,
                          get_dimm_l_8Gb (selected_mad_dimm),
                          get_dimm_l_width (selected_mad_dimm),
                          same_dimm_width,
                          dimm_and_rank_interleaving,
                          FALSE
                          );

      config_case_num_int_for_switch = config_case_num;

      //
      // Calling the parsing method, to get the address decode map for the current configuration.
      // This is the first call, just to know the DIMM shifters
      // in the case of no interleave mode, we don't need this call
      //
      if (dimm_and_rank_interleaving) {
        addr_decode_map_parse (MrcCall, config_arr, config_case_num, FALSE);
        if (enhanced_interleave_mode) {
          enhanced_mode_map_parse (MrcCall, enh_config_arr, config_case_num, FALSE);
        }
      }
      //
      // No DIMM interleave. DIMM is the largest DIMM: DIMM L.
      //
      dimm_select = 0;

      //
      // DIMM address is channel address with DIMM S's contribution removed
      //
      dimm_line = chan_line - dimm_s_size;

    } else {
      return FALSE;
    }
  } else {
    //
    // No DIMM and Rank interleaving
    //
    //
    //  +------32 GB------+
    //  |                 |
    //  .                 .
    //  .                 .
    //  .                 .
    //  |                 |
    //  |  unmapped       |
    //  |  space above    |
    //  |  channel        |
    //  |  capacity       |
    //  |                 |
    //  +--Range 1 Limit--+  <-- dimm_l_size + dimm_s_size
    //  |                 |
    //  |  No Interleave  |
    //  |     DIMM S      |
    //  |                 |
    //  +--Range 0 Limit--+  <-- dimm_l_size
    //  |                 |
    //  |  No Interleave  |
    //  |     DIMM L      |
    //  |                 |
    //  +-------0x0-------+
    //
    dimm_line = chan_line;
    if (chan_line < dimm_l_size) {
      //
      // Range 0
      //
      //
      // Get the configuration case
      //
      config_case_num = get_the_config_case_num (
                          ddr_type,
                          chnl_num_of_dimms,
                          chnl_num_of_ranks,
                          get_dimm_l_number_of_ranks (selected_mad_dimm),
                          DDR3_8Gb_x8_num_of_dimms,
                          get_dimm_l_8Gb (selected_mad_dimm),
                          get_dimm_l_width (selected_mad_dimm),
                          same_dimm_width,
                          dimm_and_rank_interleaving,
                          TRUE
                          );
      config_case_num_int_for_switch = config_case_num;

      //
      // No DIMM interleave. DIMM is the largest DIMM: DIMM L.
      //
      dimm_select = 0;

      //
      // DIMM address is channel address
      //

    } else if (chan_line < (dimm_l_size + dimm_s_size)) {
      //
      // Range 1
      //

      //
      // Get the configuration case
      //
      config_case_num = get_the_config_case_num (
                          ddr_type,
                          chnl_num_of_dimms,
                          chnl_num_of_ranks,
                          get_dimm_l_number_of_ranks (selected_mad_dimm),
                          DDR3_8Gb_x8_num_of_dimms,
                          get_dimm_l_8Gb (selected_mad_dimm),
                          get_dimm_l_width (selected_mad_dimm),
                          same_dimm_width,
                          dimm_and_rank_interleaving,
                          FALSE
                          );
      config_case_num_int_for_switch = config_case_num;

      //
      // No DIMM interleave. DIMM is the smallest DIMM: DIMM S.
      //
      dimm_select = 1;

      //
      // DIMM address is channel address with dimm_l_size removed.
      //
      dimm_line -= dimm_l_size;
    } else {
      return FALSE;
    }
  }
  //
  // Get the physical DIMM index
  //
  *p_dimm = dimm_select ^ get_dimm_l_select (selected_mad_intra_chnl);

  //
  // Get DIMM info
  //
  dimm_size = (UINT32) (dimm_select ? dimm_s_size : dimm_l_size);
  dual_rank = dimm_select ? get_dimm_s_number_of_ranks (selected_mad_dimm) : get_dimm_l_number_of_ranks (selected_mad_dimm);
  D8Gb        = dimm_select ? get_dimm_s_8Gb (selected_mad_dimm) : get_dimm_l_8Gb (selected_mad_dimm);
  dimm_width  = dimm_select ? get_dimm_s_width (selected_mad_dimm) : get_dimm_l_width (selected_mad_dimm);

  //
  // Get the exact configuration case
  //
  switch (config_case_num_int_for_switch) {
    case 4:
      config_case_num = (dual_rank) ? 4 : 5;
      break;

    case 10:
      config_case_num = (dual_rank) ? 10 : 11;
      break;

    case 12:
      config_case_num = ((D8Gb == 1) && (dimm_width == 8)) ? 12 : 13;
      break;

    case 14:
      config_case_num = ((D8Gb == 1) && (dimm_width == 8)) ? 14 : 15;
      break;

    case 16:
      config_case_num = ((D8Gb == 1) && (dimm_width == 8)) ? 16 : 17;
      break;

    case 18:
      config_case_num = ((D8Gb == 1) && (dimm_width == 8)) ? 18 : 19;
      break;

    case 24:
      config_case_num = (dual_rank) ? 24 : 25;
      break;

    case 30:
      config_case_num = (dual_rank) ? 30 : 31;
      break;

    case 32:
      config_case_num = (dimm_width == 8) ? 32 : 33;
      break;

    case 34:
      config_case_num = (dimm_width == 8) ? 34 : 35;
      break;

    case 36:
      config_case_num = (dimm_width == 8) ? 36 : 37;
      break;

    case 38:
      config_case_num = (dimm_width == 8) ? 39 : 38;
      break;

    case 40:
      config_case_num = (dimm_width == 8) ? 40 : 41;
      break;

    case 42:
      config_case_num = ((D8Gb == 1) && (dimm_width == 8)) ? 43 : 42;
      break;

    case 48:
      config_case_num = (dimm_width == 32) ? 48 : 49;
      break;
  }

  addr_decode_map_parse (MrcCall, config_arr, config_case_num, TRUE);
  if (enhanced_interleave_mode) {
    enhanced_mode_map_parse (MrcCall, enh_config_arr, config_case_num, TRUE);
  }

  converter_step = DIMM_NUM_BITS + 1;
  for (i = 0; i < RANK_NUM_BITS; i++) {
    rank_shifter[ (RANK_NUM_BITS - 1) - i]          = (config_arr[i + converter_step] - 6);
    rank_enhanced_shifter[ (RANK_NUM_BITS - 1) - i] = (enh_config_arr[i + converter_step] - 6);
  }

  converter_step += RANK_NUM_BITS;
  for (i = 0; i < BG_NUM_BITS; i++) {
    bg_shifter[ (BG_NUM_BITS - 1) - i]          = (config_arr[i + converter_step] - 6);
    bg_enhanced_shifter[ (BG_NUM_BITS - 1) - i] = (enh_config_arr[i + converter_step] - 6);
  }

  converter_step += BG_NUM_BITS;
  for (i = 0; i < BANK_NUM_BITS; i++) {
    bank_shifter[ (BANK_NUM_BITS - 1) - i]          = (config_arr[i + converter_step] - 6);
    bank_enhanced_shifter[ (BANK_NUM_BITS - 1) - i] = (enh_config_arr[i + converter_step] - 6);
  }

  converter_step += BANK_NUM_BITS;
  for (i = 0; i < ROW_NUM_BITS; i++) {
    row_shifter[ (ROW_NUM_BITS - 1) - i] = (config_arr[i + converter_step] - 6);
  }

  converter_step += ROW_NUM_BITS;
  for (i = 0; i < COL_NUM_BITS; i++) {
    col_shifter[ (COL_NUM_BITS - 1) - i] = (config_arr[i + converter_step] - 6);
    col_enhanced_shifter[i]             = -6;
  }

  col_enhanced_shifter[10] = (enh_config_arr[7] - 6);

  //
  // DRAM address calculation
  // Now compute Rank, Bank Group, Bank, Row and Col
  // high_order_rank_interleave is mutually exclusive with dimm_and_rank_interleaving
  //
  if (dual_rank && high_order_rank_interleave) {
    //
    // Specify which address bit 20-27 to use as the rank interleave bit
    //
    hori_addr = get_hori_addr (selected_mad_intra_chnl);

    //
    // Rank is selected by the HORI address field, which chooses a bit from DimmAddress[27:20]
    //
    *p_rank = (UINT16) (MrcCall->MrcRightShift64 (dimm_line, (hori_addr + 20 - 6)) & ONE_BIT_MASK);

    //
    // Bank in HORI mode is just like no-rank-interleave
    //
    if (ddr_type) {
      //
      // DDR3
      //
      if (D8Gb && (dimm_width == 8)) {
        bg_shifter[0]                = 10;
        bg_shifter[1]                = -1;
        BANK_SHIFTER_NO_INT          = 8;
        bg_enhanced_shifter[0]       = 13;
        bg_enhanced_shifter[1]       = -1;
        BANK_ENHANCED_SHIFTER_NO_INT = 11;
      } else {
        bg_shifter[0]                = 9;
        bg_shifter[1]                = -1;
        BANK_SHIFTER_NO_INT          = 7;
        bg_enhanced_shifter[0]       = 12;
        bg_enhanced_shifter[1]       = -1;
        BANK_ENHANCED_SHIFTER_NO_INT = 10;
      }
    } else {
      //
      // DDR4
      //
      if (dimm_width == 8) {
        bg_shifter[0]                = 0;
        bg_shifter[1]                = 8;
        BANK_SHIFTER_NO_INT          = 9;
        bg_enhanced_shifter[0]       = 7;
        bg_enhanced_shifter[1]       = 11;
        BANK_ENHANCED_SHIFTER_NO_INT = 12;
      } else if (dimm_width == 16) {
        bg_shifter[0]                = 0;
        bg_shifter[1]                = -1;
        BANK_SHIFTER_NO_INT          = 9;
        bg_enhanced_shifter[0]       = 7;
        bg_enhanced_shifter[1]       = -1;
        BANK_ENHANCED_SHIFTER_NO_INT = 12;
      }
    }

    for (i = 0; i < BG_NUM_BITS; i++) {
      if (bg_shifter[i] == -1) {
        bg_select_arr[i] = 0;
      } else {
        bg_select_arr[i] = (UINT16) (MrcCall->MrcRightShift64 (dimm_line, bg_shifter[i]) & 1);
        if (enhanced_interleave_mode) {
          //
          // If enhanced mode - XORing the bit
          //
          if (bg_enhanced_shifter[i] == -1) {
          } else {
            bg_select_arr[i] = bg_select_arr[i] ^ (MrcCall->MrcRightShift64 (dimm_line, bg_enhanced_shifter[i]) & 1);
          }
        }
      }
    }

    *p_bg = 0;
    for (i = 0; i < BG_NUM_BITS; i++) {
      *p_bg += (bg_select_arr[i] << i);
    }
    //
    // Bank
    //
    *p_bank = (UINT16) (MrcCall->MrcRightShift64 (dimm_line, BANK_SHIFTER_NO_INT) & TWO_BIT_MASK);

    if (enhanced_interleave_mode) {
      *p_bank = *p_bank ^ ((UINT16) (MrcCall->MrcRightShift64 (dimm_line, BANK_ENHANCED_SHIFTER_NO_INT) & TWO_BIT_MASK));
    }
    *p_row = (UINT32) MrcCall->MrcRightShift64 (dimm_line, 10);

    //
    // Create a mask with 1's in the position of the row bits below the rank bit
    //
    row_mask = (1 << (hori_addr + 4)) - 1;

    //
    // Shift down the upper bits by one to remove the rank bit and recombine with the lower bits
    //
    *p_row = ((*p_row >> 1) & ((UINT32) (~row_mask))) | (*p_row & ((UINT32) row_mask));

    //
    // Mask away any row bits too large for the size of DIMM (only the number of row bits changes with DIMM size).
    //
    *p_row = *p_row & ((UINT32) ((dimm_size >> 10) - 1));
  } else {
    //
    // This option is for interleave on & off because the only different is for the rank
    //
    if (dimm_and_rank_interleaving) {
      for (i = 0; i < RANK_NUM_BITS; i++) {
        if (rank_shifter[i] == -6) {
          rank_select_arr[i] = 0;
        } else {
          rank_select_arr[i] = (UINT16) (MrcCall->MrcRightShift64 (dimm_line, rank_shifter[i]) & 1);
        }

        if (enhanced_interleave_mode) {
          if (rank_enhanced_shifter[i] == -6) {
          } else {
            rank_select_arr[i] = rank_select_arr[i] ^ (MrcCall->MrcRightShift64 (dimm_line, rank_enhanced_shifter[i]) & 1);
          }
        }
      }

      *p_rank = 0;
      for (i = 0; i < RANK_NUM_BITS; i++) {
        *p_rank += (rank_select_arr[i] << i);
      }
    } else {
      *p_rank = 0;
      if (dual_rank) {
        switch (dimm_size) {
          //
          // dimm_size is in cache-lines
          //
          case MC_2GB_AS_CL:
            rank_bit_shift = 24;
            break;
          case MC_4GB_AS_CL:
            rank_bit_shift = 25;
            break;
          case MC_8GB_AS_CL:
            rank_bit_shift = 26;
            break;
          case MC_16GB_AS_CL:
            rank_bit_shift = 27;
            break;
          case MC_32GB_AS_CL:
            rank_bit_shift = 28;
            break;
          default:
            return FALSE;
        }

        *p_rank = (UINT16) (MrcCall->MrcRightShift64 (dimm_line, rank_bit_shift) & ONE_BIT_MASK);
      }
    }
    //
    // bg taken from the address map
    //
    for (i = 0; i < BG_NUM_BITS; i++) {
      if (bg_shifter[i] == -6) {
        bg_select_arr[i] = 0;
      } else {
        bg_select_arr[i] = (UINT16) (MrcCall->MrcRightShift64 (dimm_line, bg_shifter[i]) & 1);
      }

      if (enhanced_interleave_mode) {
        if (bg_enhanced_shifter[i] == -6) {
        } else {
          bg_select_arr[i] = bg_select_arr[i] ^ (MrcCall->MrcRightShift64 (dimm_line, bg_enhanced_shifter[i]) & 1);
        }
      }
    }

    *p_bg = 0;
    for (i = 0; i < BG_NUM_BITS; i++) {
      *p_bg += (bg_select_arr[i] << i);
    }
    //
    // bank taken from the address map
    //
    for (i = 0; i < BANK_NUM_BITS; i++) {
      if (bank_shifter[i] == -6) {
        bank_select_arr[i] = 0;
      } else {
        bank_select_arr[i] = (UINT16) (MrcCall->MrcRightShift64 (dimm_line, bank_shifter[i]) & 1);
      }

      if (enhanced_interleave_mode) {
        if (bank_enhanced_shifter[i] == -6) {
        } else {
          bank_select_arr[i] = bank_select_arr[i] ^ (MrcCall->MrcRightShift64 (dimm_line, bank_enhanced_shifter[i]) & 1);
        }
      }
    }

    *p_bank = 0;
    for (i = 0; i < BANK_NUM_BITS; i++) {
      *p_bank += (bank_select_arr[i] << i);
    }
    //
    // Row taken from the address map, depends on DIMM size.
    //
    for (i = 0; i < ROW_NUM_BITS; i++) {
      if (row_shifter[i] == -6) {
        row_select_arr[i] = 0;
      } else {
        row_select_arr[i] = (UINT16) (MrcCall->MrcRightShift64 (dimm_line, row_shifter[i]) & 1);
      }
    }

    *p_row = 0;
    for (i = 0; i < ROW_NUM_BITS; i++) {
      *p_row += (row_select_arr[i] << i);
    }

    //
    // Mask away any row bits too large for the size of DIMM (only the number of row bits changes with DIMM size).
    //
    if (ddr_type == 0) {
      //
      // DDR4
      //
      i = (dimm_width == 8) ? 11 : 10;
    } else if (ddr_type == 1) {
      //
      // DDR3
      //
      i = (dimm_width == 8) ? (10 + ((UINT16) D8Gb)) : 10;
    } else {
      //
      // LPDDR3
      //
      i = (dimm_width == 16) ? 11 : 10;
    }

    i       = i + ((UINT16) dual_rank);
    *p_row  = *p_row & ((UINT32) ((dimm_size >> i) - 1));
  }
  //
  // Column is the same for all the options
  //
  for (i = 0; i < COL_NUM_BITS; i++) {
    if (col_shifter[i] == -6) {
      col_select_arr[i] = 0;
    } else if (col_shifter[i] < 0) {
      col_shifter[i] += 6;
      col_select_arr[i] = (UINT16) (MrcCall->MrcRightShift64 (sys_addr, col_shifter[i]) & 1);
    } else {
      col_select_arr[i] = (UINT16) (MrcCall->MrcRightShift64 (dimm_line, col_shifter[i]) & 1);
    }

    if (enhanced_interleave_mode) {
      if (col_enhanced_shifter[i] == -6) {
      } else {
        col_select_arr[i] = col_select_arr[i] ^ (MrcCall->MrcRightShift64 (dimm_line, col_enhanced_shifter[i]) & 1);
      }
    }
  }

  *p_col = 0;
  for (i = 0; i < COL_NUM_BITS; i++) {
    *p_col += (col_select_arr[i] << i);
  }

  if (ber_en && (*p_is_tcm) && (sys_addr >= ber_target_base) && (sys_addr < tom)) {

    *p_chan = get_ber_chan (BER_MC_ABORT);
    *p_dimm = get_ber_dimm (MAD_INTER_CHNL, BER_MC_ABORT);
    *p_rank = get_ber_rank (MAD_INTER_CHNL, BER_MC_ABORT);
    *p_bg   = get_ber_bg (MAD_INTER_CHNL, BER_MC_ABORT);
    *p_bank = get_ber_bank (MAD_INTER_CHNL, BER_MC_ABORT);
    *p_row  = get_ber_row (BER_MC_ABORT);
    *p_col  = get_ber_col (BER_MC_ABORT);
    //
    // Insert the AddrOffset to the [2:0] bits of the col
    //
    for (j = 0; j < 3; j++) {
      *p_col += (col_select_arr[j] << j);
    }
  } else {
    //
    // Check if the system address was removed from the available address space due to errors/faults in the DIMM
    //
    for (i = 0; i < MC_NUM_BER_REGS; i++) {
      if (get_ber_valid (MrcCall, BER_SRC[i]) &&
          dram_ber_match (*p_chan, *p_dimm, *p_rank, *p_bg, *p_bank, *p_row, *p_col, BER_TGT[i], MAD_INTER_CHNL)
          ) {
        return FALSE;
      }
    }
  }
  //
  // Check if the system address is the source of a BER remap, which will override the decode result
  //
  for (i = 0; i < MC_NUM_BER_REGS; i++) {
    if (en_sys_ber_match (MrcCall, sys_addr, *p_is_tcm, BER_SRC[i])) {

      *p_chan = get_ber_chan (BER_TGT[i]);
      *p_dimm = get_ber_dimm (MAD_INTER_CHNL, BER_TGT[i]);
      *p_rank = get_ber_rank (MAD_INTER_CHNL, BER_TGT[i]);
      *p_bg   = get_ber_bg (MAD_INTER_CHNL, BER_TGT[i]);
      *p_bank = get_ber_bank (MAD_INTER_CHNL, BER_TGT[i]);
      *p_row  = get_ber_row (BER_TGT[i]);
      *p_col  = get_ber_col (BER_TGT[i]);
      //
      // Insert the AddrOffset to the [2:0] bits of the col
      //
      for (j = 0; j < 3; j++) {
        *p_col += (col_select_arr[j] << j);
      }
      break;
    }
  }
  *p_bg   = *p_bg | ((*p_bank >> 2) & 1);
  *p_bank = *p_bank & 3;

  //
  // Check legal row address in 6Gb devices
  //
  if (lpddr3_6Gb_dev && (((*p_row >> 13) & 3) == 3)) {
    return FALSE;
  }

  return TRUE;
}

/**
  Address encode function (reverse address decode)
  DRAM address to system address conversion

  @param[in]      MrcCall            - pointer to MRC_ADDR_FUNCTION struct
  @param[in]      chan               - channel addr to encode
  @param[in]      dimm               - DIMM address to encode
  @param[in]      rank               - rank address to encode
  @param[in]      bg                 - bank group address to encode
  @param[in]      bank               - bank address to encode
  @param[in]      row                - row address to encode
  @param[in]      col                - column address to encode. Note: The architecture is limited to half-cache-line
                                       granularity for burst order. Therefore the last two bits of the column are ignored.
  @param[in]      TOLUD              - memory register
  @param[in]      REMAP_BASE         - memory register
  @param[in]      REMAP_LIMIT        - memory register
  @param[in]      TOM                - memory register
  @param[in]      CHANNEL_HASH       - memory register
  @param[in]      MAD_INTER_CHNL     - memory register
  @param[in]      MAD_INTRA_CHNL_ch0 - memory register
  @param[in]      MAD_INTRA_CHNL_ch1 - memory register
  @param[in]      MAD_DIMM_ch0       - memory register
  @param[in]      MAD_DIMM_ch1       - memory register
  @param[in]      BER_SRC[]          - memory register
  @param[in]      BER_TGT[]          - memory register
  @param[in]      BER_MC_ABORT       - memory register
  @param[out]     sys_addr           - the 39-bit system address convert to
  @param[in, out] p_is_tcm           - is the transaction to sys_addr "traffic class for the manageability engine"

  @retval TRUE if successful.

**/
BOOLEAN
MrcEncode (
  IN const MRC_ADDR_FUNCTION *MrcCall,
  IN       UINT16       chan,
  IN       UINT16       dimm,
  IN       UINT16       rank,
  IN       UINT16       bg,
  IN       UINT16       bank,
  IN       UINT32       row,
  IN       UINT16       col,
  IN       UINT32       TOLUD,
  IN       UINT64       REMAP_BASE,
  IN       UINT64       REMAP_LIMIT,
  IN       UINT64       TOM,
  IN       UINT32       CHANNEL_HASH,
  IN       UINT32       MAD_INTER_CHNL,
  IN       UINT32       MAD_INTRA_CHNL_ch0,
  IN       UINT32       MAD_INTRA_CHNL_ch1,
  IN       UINT32       MAD_DIMM_ch0,
  IN       UINT32       MAD_DIMM_ch1,
  IN       UINT64       BER_SRC[],
  IN       UINT32       BER_TGT[],
  IN       UINT32       BER_MC_ABORT,
  OUT      UINT64       *p_sys_addr,
  IN OUT   BOOLEAN      *p_is_tcm
  )
{
  UINT16  D8Gb;  // 0-> NOT 8Gb; 1-> 8Gb
  UINT16  unselected_D8Gb;
  UINT16  hash_lsb_mask_bit;  // LsbMaskBit field from CHANNEL_HASH register
  UINT16  hash_mask;  // channel hash mask from CHANNEL_HASH register
  UINT64  dimm_select;  // DIMM L=0, S=1
  UINT64  dimm_size;  // size of selected DIMM
  UINT64  unselectet_dimm_size;  // size of unselected DIMM
  UINT16  dimm_width;  // x8=8; x16=16
  UINT16  unselected_dimm_width;
  BOOLEAN dual_rank;  // number of ranks on selected DIMM
  BOOLEAN unselected_dual_rank;
  UINT64  bit_above_row;  // one-hot bit to mark the size of the row address
  BOOLEAN dimm_and_rank_interleaving;  // modes for the selected channel
  BOOLEAN high_order_rank_interleave;
  BOOLEAN enhanced_interleave_mode;
  UINT16  hori_addr;  // bits to use from address for HORI
  UINT16  row_mask;  // used to insert rank bit inbetween row bits in HORI mode
  UINT64  dimm_line;  // DIMM address space (cache-line)
  UINT64  chan_line;  // Channel address space (cache-line)
  UINT64  dimm_l_size;
  UINT64  dimm_s_size;
  BOOLEAN same_dimm_width;
  UINT16  chnl_num_of_dimms;
  UINT16  chnl_num_of_ranks;
  UINT16  dimm_s_num_of_ranks;
  UINT16  DDR3_8Gb_x8_num_of_dimms;
  UINT16  num_col_bits;
  UINT16  chan_select;  // 0 = Channel L, 1 = Channel S
  UINT64  remap_line;  // address before reverse decoding the remap region
  UINT64  remap_addr;  // full address
  UINT16  hash_line;  // lower bits of remap_line with hash_mask applied
  UINT16  hash_bit;  // bit that gets destroyed in forward decode
  UINT16  i;
  //
  // virtual arrays to get the inputs from the addr_decode_maps.csv table, according to the configuration
  //
  UINT8   config_arr[DRAM_ADDR_SIZE + 1];
  //
  // virtual arrays to get the inputs from the enhanced_mode_map.csv table, according to the configuration
  //
  UINT8   enh_config_arr[ENHANCED_BITS_SIZE + 1];
  UINT8   config_case_num;
  UINT8   config_case_num_int_for_switch;
  UINT8   converter_step;
  //
  // virtual var
  //
  UINT64  num_rows_in_dimm_s;
  UINT16  denominator;
  //
  // Shifters for bit select (from chnl_addr)according to the address decode map
  //
  INT16   dimm_shifter[DIMM_NUM_BITS];
  INT16   rank_shifter[RANK_NUM_BITS];
  INT16   bg_shifter[BG_NUM_BITS];
  INT16   bank_shifter[BANK_NUM_BITS];
  INT16   row_shifter[ROW_NUM_BITS];
  INT16   col_shifter[COL_NUM_BITS];
  INT16   dimm_enhanced_shifter[DIMM_NUM_BITS];
  INT16   rank_enhanced_shifter[RANK_NUM_BITS];
  INT16   bg_enhanced_shifter[BG_NUM_BITS];
  INT16   bank_enhanced_shifter[BANK_NUM_BITS];
  INT16   col_enhanced_shifter[COL_NUM_BITS];
  UINT64  top_of_remaped_mem;  // used for reverse decode of remap region
  BOOLEAN rerun_zone_1;
  BOOLEAN found_the_dimm_zone;
  UINT64  Remainder;
  UINT16  ddr_type;                       // DDR4=0; DDR3=1; LPDDR3=2;
  BOOLEAN stacked_mode;                   // channel stacking enabled
  BOOLEAN stacked_mode_ch1;               // Stacking channel 0 on top of channel 1
  UINT16  stacked_encoding;               // Stacked mode channel hash bits
  UINT64  stacked_size;                   // The size of the channels in stacked mode (according to stacked_encoding) (cl address)
  UINT32  mad_dimm_l[2];                  // Make a MAD_DIMM array for easy access
  UINT32  mad_intra_chnl_l[2];            // Make a MAD_INTRA_CHNL array for easy access
  UINT64  ch_s_size;                      // chanel s_size adjusted to cl address
  UINT16  ch_l_map;                       // Virtual channel L mapping (0 - CH 0; 1 - CH 1)
  UINT32  chan_l_mad_dimm;                // channel L's MAD_DIMM register
  UINT32  tolud;                          // TOLUD register after verification and cleanup (system address)
  UINT64  remap_base;                     // REMAP_BASE register after verification and cleanup (system address)
  UINT64  remap_limit;                    // REMAP_LIMIT register after verification and cleanup (system address)
  UINT64  tom;                            // Top Of Memory (system address)
  UINT64  tom_in_cl;                      // Top Of Memory (cl address)
  UINT64  remap_size;                     // size of the remap region (system address)
  UINT64  gap_top;                        // one address above the gap (the remap target region) (system address)
  BOOLEAN ber_en = FALSE;                 // Indicates id BER is enabled
  UINT64  ber_target_base;                // Base address to stolen memory in which BER target DRAM addresses reside (system address)
  UINT32  ber_target_size = 0;            // The size of stolen memory in which BER target DRAM addresses reside (system address)
  BOOLEAN lpddr3_6Gb_dev  = FALSE;        // Indicates we're using LPDDR3 6Gb DRAM devices - restricts some rules
  UINT64 calculated_tom;

  MrcCall->MrcSetMem ((UINT8 *) config_arr, sizeof (config_arr), 0);
  MrcCall->MrcSetMem ((UINT8 *) enh_config_arr, sizeof (enh_config_arr), 0);
  MrcCall->MrcSetMem ((UINT8 *) dimm_shifter, sizeof (dimm_shifter), 0);
  MrcCall->MrcSetMem ((UINT8 *) rank_shifter, sizeof (rank_shifter), 0);
  MrcCall->MrcSetMem ((UINT8 *) bg_shifter, sizeof (bg_shifter), 0);
  MrcCall->MrcSetMem ((UINT8 *) bank_shifter, sizeof (bank_shifter), 0);
  MrcCall->MrcSetMem ((UINT8 *) row_shifter, sizeof (row_shifter), 0);
  MrcCall->MrcSetMem ((UINT8 *) col_shifter, sizeof (col_shifter), 0);
  MrcCall->MrcSetMem ((UINT8 *) dimm_enhanced_shifter, sizeof (dimm_enhanced_shifter), 0);
  MrcCall->MrcSetMem ((UINT8 *) rank_enhanced_shifter, sizeof (rank_enhanced_shifter), 0);
  MrcCall->MrcSetMem ((UINT8 *) bg_enhanced_shifter, sizeof (bg_enhanced_shifter), 0);
  MrcCall->MrcSetMem ((UINT8 *) bank_enhanced_shifter, sizeof (bank_enhanced_shifter), 0);
  MrcCall->MrcSetMem ((UINT8 *) col_enhanced_shifter, sizeof (col_enhanced_shifter), 0);

  stacked_mode_ch1    = 0;
  stacked_encoding    = 0;
  num_rows_in_dimm_s  = 0;
  rerun_zone_1        = FALSE;
  found_the_dimm_zone = FALSE;
  chan_line           = 0;
  dimm_line           = 0;
  ddr_type            = get_ddr_type (MAD_INTER_CHNL);
  tolud               = TOLUD & MC_ADDR_TOLUD_MASK;
  remap_base          = REMAP_BASE & MC_ADDR_REMAP_MASK;
  remap_limit         = REMAP_LIMIT & MC_ADDR_REMAP_MASK;
  tom                 = TOM & MC_ADDR_REMAP_MASK;
  remap_limit        |= MC_ADDR_REMAP_LIMIT_LOWER_BITS_MASK;
  remap_size          = remap_limit + 1 - remap_base;
  gap_top             = tolud + remap_size;
  mad_dimm_l[0]       = MAD_DIMM_ch0;
  mad_dimm_l[1]       = MAD_DIMM_ch1;
  mad_intra_chnl_l[0] = MAD_INTRA_CHNL_ch0;
  mad_intra_chnl_l[1] = MAD_INTRA_CHNL_ch1;

  //
  // Calculate TOM
  //
  ch_s_size       = get_ch_s_size_as_cl (MrcCall, MAD_INTER_CHNL);
  ch_l_map        = get_ch_l_map (MAD_INTER_CHNL);
  chan_l_mad_dimm = mad_dimm_l[ch_l_map];

  //
  // If we use LPDDR3 6Gb DRAM devices then the actual DRAM size is quarter less then configured in SKL
  // SKL feature f95150
  //
  lpddr3_6Gb_dev  = FALSE;

  calculated_tom  = cl_to_sys (MrcCall, get_dimm_l_size_as_cl (MrcCall, chan_l_mad_dimm));
  calculated_tom += cl_to_sys (MrcCall, get_dimm_s_size_as_cl (MrcCall, chan_l_mad_dimm));
  calculated_tom += cl_to_sys (MrcCall, ch_s_size);

  if ((ddr_type == 2) && (tom == MrcCall->MrcDivU64x64 (MrcCall->MrcMultU64x32 (calculated_tom, 3), 4, &Remainder))) {
    lpddr3_6Gb_dev = TRUE;
  }

  tom_in_cl = MrcCall->MrcRightShift64 (tom, 6);

  //
  // Determine if we are in stacked mode; and if so, what the stacked size is.
  //
  stacked_mode = get_stacked_mode (MAD_INTER_CHNL);
  if (stacked_mode) {
    stacked_mode_ch1  = get_stacked_mode_ch1 (MAD_INTER_CHNL);
    stacked_encoding  = get_stacked_encoding (MAD_INTER_CHNL);
    stacked_size      = get_stacked_memory_size (MrcCall, stacked_encoding);
  }

  //
  // Updating Bit-Error-Recovery related paramenters
  //
  ber_en = FALSE;

  for (i = 0; i < MC_NUM_BER_REGS; i++) {
    if (get_ber_valid (MrcCall, BER_SRC[i])) {
      ber_en = TRUE;
    }
  }
  //
  // Setting Bit-Error-Recovery target base address.
  // This area is reserved area ot the size of ber_target_size (4K if enabled) below TOM
  //
  if (ber_en) {
    ber_target_size = in_kb (4);
    ber_target_base = tom - ber_target_size;
  } else {
    ber_target_size = 0;
    ber_target_base = tom;
  }


  //
  // Perform some checks on the inputs
  // Illegal channel check
  //
  if (chan & ~((UINT16) 1)) {
    return FALSE;
  }
  //
  // Check for too high of a DIMM index
  //
  if (dimm & ~((UINT16) 1)) {
    return FALSE;
  }
  //
  // Is it DIMM L or S? L=0, S=1
  //
  dimm_select = (UINT64) (dimm ^ get_dimm_l_select (mad_intra_chnl_l[chan]));

  //
  // Get DIMM size
  //
  dimm_size = dimm_select ? get_dimm_s_size_as_cl (MrcCall, mad_dimm_l[chan]) : get_dimm_l_size_as_cl (MrcCall, mad_dimm_l[chan]);
  unselectet_dimm_size = dimm_select ? get_dimm_l_size_as_cl (MrcCall, mad_dimm_l[chan]) : get_dimm_s_size_as_cl (MrcCall, mad_dimm_l[chan]);

  //
  // Check if DIMM slot is populated
  //
  if (dimm_size == 0) {
    return FALSE;
  }
  //
  // Check for too high of a rank index
  //
  if (rank & ~((UINT16) 1)) {
    return FALSE;
  }
  //
  // Get some selected DIMM parameters
  //
  dual_rank  = dimm_select ? get_dimm_s_number_of_ranks (mad_dimm_l[chan]) : get_dimm_l_number_of_ranks (mad_dimm_l[chan]);
  dimm_width = dimm_select ? get_dimm_s_width (mad_dimm_l[chan]) : get_dimm_l_width (mad_dimm_l[chan]);
  D8Gb       = dimm_select ? get_dimm_s_8Gb (mad_dimm_l[chan]) : get_dimm_l_8Gb (mad_dimm_l[chan]);

  //
  // Get some unselected DIMM parameters
  //
  unselected_dual_rank  = dimm_select ? get_dimm_l_number_of_ranks (mad_dimm_l[chan]) : get_dimm_s_number_of_ranks (mad_dimm_l[chan]);
  unselected_dimm_width = dimm_select ? get_dimm_l_width (mad_dimm_l[chan]) : get_dimm_s_width (mad_dimm_l[chan]);
  unselected_D8Gb       = dimm_select ? get_dimm_l_8Gb (mad_dimm_l[chan]) : get_dimm_s_8Gb (mad_dimm_l[chan]);

  //
  // Check that rank exists on DIMM
  //
  if (rank && !dual_rank) {
    return FALSE;
  }
  //
  // Check for too high of a bg index
  //
  if ((ddr_type) || ((!ddr_type) && (dimm_width == 16))) {
    //
    // DDR3 LPDDR3 (ddr_type==1,2 => TRUE) or DDR4 (DDR4==0 => FALSE) x16 => bg[1]=0
    //
    if (bg & ~((UINT16) 0x1)) {
      return FALSE;
    }
  } else if (bg & ~((UINT16) 0x3)) {
    return FALSE;
  }
  //
  // Check for too high of a bank index
  //
  if (bank & ~((UINT16) 0x7)) {
    return FALSE;
  }
  //
  // Set a bit in a position that is one bit higher than the highest row bit
  //
  //  Most-Significant-Bits of Supported DRAM Chip Organizations
  //  DDR     Config  Size    Row     Col     Bg  Bank
  //  ---     ------  ------  ---     ---     --  ----
  //  DDR3    x8      2 Gb    14      9       0   1
  //  DDR3    x8      4 Gb    15      9       0   1   (8 GB DIMM, when dual rank) largest DDR3 DIMM when not using 8Gb
  //  DDR3    x8      8 Gb    15      10      0   1   (16 GB DIMM, when dual rank) largest DDR3 DIMM when using 8Gb
  //  DDR3    x16     2 Gb    13      9       0   1   (1 GB DIMM, when single rank) smallest DDR3 DIMM
  //  DDR3    x16     4 Gb    14      9       0   1
  //  DDR3    x16     8 Gb    15      9       0   1
  //  DDR4    x8      2 Gb    13      9       1   1   (2 GB DIMM, when single rank)
  //  DDR4    x8      4 Gb    14      9       1   1
  //  DDR4    x8      8 Gb    15      9       1   1
  //  DDR4    x8      16 Gb   16      9       1   1
  //  DDR4    x16     2 Gb    13      9       0   1   (1 GB DIMM, when single rank)
  //  DDR4    x16     4 Gb    14      9       0   1
  //  DDR4    x16     8 Gb    15      9       0   1
  //  DDR4    x16     16 Gb   16      9       0   1
  //  LPDDR3  x16     2 Gb    13      9       0   1   (1 GB DIMM, when single rank)
  //  LPDDR3  x16     4 Gb    13      10      0   1
  //  LPDDR3  x16     8 Gb    14      10      0   1
  //  LPDDR3  x32     2 Gb    13      8       0   1   (0.5 GB DIMM, when single rank)
  //  LPDDR3  x32     4 Gb    13      9       0   1
  //  LPDDR3  x32     8 Gb    14      9       0   1
  //
  // dimm size (GB) | dimm_size (cache-line)
  // ---------------+-----------------------
  //       32 GB    |     1<<29
  //       16 GB    |     1<<28
  //        8 GB    |     1<<27
  //        4 GB    |     1<<26
  //        2 GB    |     1<<25
  //        1 GB    |     1<<24
  //      0.5 GB    |     1<<23
  //
  num_col_bits = dimm_select ? get_dimm_s_num_col_bits (MrcCall, ddr_type, mad_dimm_l[chan]) : get_dimm_l_num_col_bits (MrcCall, ddr_type, mad_dimm_l[chan]);

  bit_above_row = MrcCall->MrcRightShift64 (dimm_size, (num_col_bits + ((UINT16) dual_rank)));

  //
  // When DDR4 x8, Bg has two bits and the size can be twice bigger.
  //
  bit_above_row = ((!ddr_type) && (dimm_width == 8)) ? MrcCall->MrcRightShift64 (bit_above_row, 1) : bit_above_row;

  //
  // Check for unexpected high-order row bits
  //
  if (row & ~(((UINT32) bit_above_row) - 1)) {
    return FALSE;
  }
  //
  // Check for unexpected high-order column bits
  //
  if (col & ~((((UINT16) 1) << num_col_bits) - 1)) {
    return FALSE;
  }

  //
  // Determine if we are doing DIMM and Rank interleaving
  //
  dimm_and_rank_interleaving = get_dimm_and_rank_intlv (mad_intra_chnl_l[chan]);

  //
  // Determine if we are doing high order rank interleave
  //
  high_order_rank_interleave = get_high_order_intlv_mode (mad_intra_chnl_l[chan]);

  //
  // Determine if we are doing Enhanced Interleave Mode (EIM) (XOR dimm, rank, bg & bank bits)
  //
  enhanced_interleave_mode = get_enhanced_intlv_mode (mad_intra_chnl_l[chan]);

  //
  // Find the DIMM sizes on our selected channel. adjust to cache-line granularity
  //
  dimm_l_size = get_dimm_l_size_as_cl (MrcCall, mad_dimm_l[chan]);
  dimm_s_size = get_dimm_s_size_as_cl (MrcCall, mad_dimm_l[chan]);

  //
  // Find number of ranks and dimms in the selected channel
  //
  chnl_num_of_dimms = (dimm_l_size) ? ((dimm_s_size) ? 2 : 1) : 0;
  chnl_num_of_ranks = (dimm_l_size) ? (get_dimm_l_number_of_ranks (mad_dimm_l[chan]) ?
                      ((dimm_s_size) ? (get_dimm_s_number_of_ranks (mad_dimm_l[chan]) ? 4 : 3) : 2) :
                      ((dimm_s_size) ? (get_dimm_s_number_of_ranks (mad_dimm_l[chan]) ? 3 : 2) : 1)) : 0;

  dimm_s_num_of_ranks = (dimm_s_size) ? (get_dimm_s_number_of_ranks (mad_dimm_l[chan]) ? 2 : 1) : 0;

  //
  // Find the dimm width chnl configuration
  //
  same_dimm_width = (dimm_s_size) ? ((get_dimm_l_width (mad_dimm_l[chan]) == get_dimm_s_width (mad_dimm_l[chan])) ? TRUE : FALSE) : TRUE;

  //
  // Check the num of DDR3 8Gb dimms
  //
  DDR3_8Gb_x8_num_of_dimms =
    (chnl_num_of_dimms == 2) ?
    ((get_dimm_l_8Gb (mad_dimm_l[chan]) == 1 && get_dimm_l_width (mad_dimm_l[chan]) == 8) ?
    ((get_dimm_s_8Gb (mad_dimm_l[chan]) == 1 && get_dimm_s_width (mad_dimm_l[chan]) == 8) ? 2 : 1)
    : ((get_dimm_s_8Gb (mad_dimm_l[chan]) == 1 && get_dimm_s_width (mad_dimm_l[chan]) == 8) ? 1 : 0))
    : ((get_dimm_l_8Gb (mad_dimm_l[chan]) == 1 && get_dimm_l_width (mad_dimm_l[chan]) == 8) ? 1 : 0);

  //
  // denominator = dimm_s_num_of_ranks
  //
  denominator = (1 << BG_NUM_BITS);


  if (!dimm_s_size) {
    num_rows_in_dimm_s = 0;
  } else {
    num_rows_in_dimm_s = MrcCall->MrcDivU64x64 (
                                    MrcCall->MrcLeftShift64 (dimm_s_size, 6),
                                    dimm_s_num_of_ranks * (1 << COL_NUM_BITS) * (64 / get_dimm_s_width (mad_dimm_l[chan])),
                                    &Remainder
                                    );
  }

  //
  // Get the configuration case
  //
  config_case_num = get_the_config_case_num (
                      ddr_type,
                      chnl_num_of_dimms,
                      chnl_num_of_ranks,
                      get_dimm_l_number_of_ranks (mad_dimm_l[chan]),
                      DDR3_8Gb_x8_num_of_dimms,
                      get_dimm_l_8Gb (mad_dimm_l[chan]),
                      get_dimm_l_width (mad_dimm_l[chan]),
                      same_dimm_width,
                      dimm_and_rank_interleaving,
                      !rerun_zone_1
                      );

  while (!found_the_dimm_zone) {

    config_case_num = get_the_config_case_num (
                        ddr_type,
                        chnl_num_of_dimms,
                        chnl_num_of_ranks,
                        get_dimm_l_number_of_ranks (mad_dimm_l[chan]),
                        DDR3_8Gb_x8_num_of_dimms,
                        get_dimm_l_8Gb (mad_dimm_l[chan]),
                        get_dimm_l_width (mad_dimm_l[chan]),
                        same_dimm_width,
                        dimm_and_rank_interleaving,
                        !rerun_zone_1
                        );

    //
    // Get the exact configuration case
    //
    config_case_num_int_for_switch = config_case_num;
    switch (config_case_num_int_for_switch) {
      case 4:
        config_case_num = (dual_rank) ? 4 : 5;
        break;

      case 10:
        config_case_num = (dual_rank) ? 10 : 11;
        break;

      case 12:
        config_case_num = ((D8Gb == 1) && (dimm_width == 8)) ? 12 : 13;
        break;

      case 14:
        config_case_num = ((D8Gb == 1) && (dimm_width == 8)) ? 14 : 15;
        break;

      case 16:
        config_case_num = ((D8Gb == 1) && (dimm_width == 8)) ? 16 : 17;
        break;

      case 18:
        config_case_num = ((D8Gb == 1) && (dimm_width == 8)) ? 18 : 19;
        break;

      case 24:
        config_case_num = (dual_rank) ? 24 : 25;
        break;

      case 30:
        config_case_num = (dual_rank) ? 30 : 31;
        break;

      case 32:
        config_case_num = (dimm_width == 8) ? 32 : 33;
        break;

      case 34:
        config_case_num = (dimm_width == 8) ? 34 : 35;
        break;

      case 36:
        config_case_num = (dimm_width == 8) ? 36 : 37;
        break;

      case 38:
        config_case_num = (dimm_width == 8) ? 39 : 38;
        break;

      case 40:
        config_case_num = (dimm_width == 8) ? 40 : 41;
        break;

      case 42:
        config_case_num = ((D8Gb == 1) && (dimm_width == 8)) ? 43 : 42;
        break;

      case 48:
        config_case_num = (dimm_width == 32) ? 48 : 49;
        break;
    }

    if (rerun_zone_1) {
      config_case_num_int_for_switch = config_case_num;
      switch (config_case_num_int_for_switch) {
        case 4:
        case 5:
          config_case_num = (dual_rank) ? 2 : 0;
          break;

        case 10:
        case 11:
          config_case_num = (dual_rank) ? 8 : 6;
          break;

        case 24:
        case 25:
          config_case_num = (dual_rank) ? 22 : 20;
          break;

        case 30:
        case 31:
          config_case_num = (dual_rank) ? 28 : 26;
          break;
      }
    }

    addr_decode_map_parse (MrcCall, config_arr, config_case_num, TRUE);
    if (enhanced_interleave_mode) {
      enhanced_mode_map_parse (MrcCall, enh_config_arr, config_case_num, TRUE);
    }

    converter_step = 1;
    for (i = 0; i < DIMM_NUM_BITS; i++) {
      dimm_shifter[ (DIMM_NUM_BITS - 1) - i]          = (config_arr[i + converter_step] - 6);
      dimm_enhanced_shifter[ (DIMM_NUM_BITS - 1) - i] = (enh_config_arr[i + converter_step] - 6);
    }

    converter_step += DIMM_NUM_BITS;
    for (i = 0; i < RANK_NUM_BITS; i++) {
      rank_shifter[ (RANK_NUM_BITS - 1) - i]          = (config_arr[i + converter_step] - 6);
      rank_enhanced_shifter[ (RANK_NUM_BITS - 1) - i] = (enh_config_arr[i + converter_step] - 6);
    }

    converter_step += RANK_NUM_BITS;
    for (i = 0; i < BG_NUM_BITS; i++) {
      bg_shifter[ (BG_NUM_BITS - 1) - i]          = (config_arr[i + converter_step] - 6);
      bg_enhanced_shifter[ (BG_NUM_BITS - 1) - i] = (enh_config_arr[i + converter_step] - 6);
    }

    converter_step += BG_NUM_BITS;
    for (i = 0; i < BANK_NUM_BITS; i++) {
      bank_shifter[ (BANK_NUM_BITS - 1) - i]          = (config_arr[i + converter_step] - 6);
      bank_enhanced_shifter[ (BANK_NUM_BITS - 1) - i] = (enh_config_arr[i + converter_step] - 6);
    }

    converter_step += BANK_NUM_BITS;
    for (i = 0; i < ROW_NUM_BITS; i++) {
      row_shifter[ (ROW_NUM_BITS - 1) - i] = (config_arr[i + converter_step] - 6);
    }

    converter_step += ROW_NUM_BITS;
    for (i = 0; i < COL_NUM_BITS; i++) {
      col_shifter[ (COL_NUM_BITS - 1) - i] = (config_arr[i + converter_step] - 6);
      col_enhanced_shifter[i]             = -6;
    }
    col_enhanced_shifter[10] = (enh_config_arr[7] - 6);


    //
    // Start building the DIMM Address Space (as a cache-line address)
    // build the rank, bg, bank, and row parts of the DIMM space address
    //
    if (dual_rank && high_order_rank_interleave) {
      hori_addr = get_hori_addr (mad_intra_chnl_l[chan]);

      //
      // Put the row part of the address into the dimm address
      // Create a mask with all 1's in the positions of the row bits below the rank bit
      //
      row_mask = (1 << (hori_addr + 4)) - 1;

      //
      // Split the row address at the rank bit and put it into the dimm address
      //
      dimm_line = dimm_line | MrcCall->MrcLeftShift64 ((UINT64) (MrcCall->MrcLeftShift64 ((row & ~row_mask), 1) | (row & row_mask)), (16 - 6));

      //
      // Put the bank part of the address into the dimm address
      //
      dimm_line = dimm_line | ((UINT64) MrcCall->MrcLeftShift64 (bank, (13 - 6)));

      //
      // Rank bit goes into the spot specified by hori_addr
      //
      dimm_line = dimm_line | ((UINT64) MrcCall->MrcLeftShift64 (rank, (20 - 6 + hori_addr)));

      //
      // Reverse the XOR operation for enhanced interleave mode
      //
      if (enhanced_interleave_mode) {
        dimm_line = dimm_line ^ MrcCall->MrcRightShift64 ((dimm_line & 0x1C00ULL), 3);
      }
    } else {
      //
      // The same for rank interleave on/off
      //

      dimm_line = 0;

      //
      // Put in the col part of the address
      //
      for (i = 0; i < (COL_NUM_BITS - 1); i++) {
        if (col_shifter[i] == -6) {
        } else if (col_shifter[i] < 0) {
          col_shifter[i] += 6;
          *p_sys_addr = *p_sys_addr | (UINT64) MrcCall->MrcLeftShift64 ((MrcCall->MrcRightShift64 (col, i) & 1), col_shifter[i]);
        } else {
          if (enhanced_interleave_mode && (col_enhanced_shifter[i] != -6)) {
            dimm_line = dimm_line | (UINT64) MrcCall->MrcLeftShift64 (((MrcCall->MrcRightShift64 (col, i) & 1) ^ (MrcCall->MrcRightShift64 (dimm_line, col_enhanced_shifter[i]) & 1)), col_shifter[i]);
          } else {
            dimm_line = dimm_line | (UINT64) MrcCall->MrcLeftShift64 ((MrcCall->MrcRightShift64 (col, i) & 1), col_shifter[i]);
          }
        }
      }

      //
      // Put in the row part of the address
      //
      for (i = 0; i < ROW_NUM_BITS; i++) {
        if (row_shifter[i] == -6) {
        } else {
          dimm_line = dimm_line | (UINT64) MrcCall->MrcLeftShift64 ((MrcCall->MrcRightShift64 (row, i) & 1), row_shifter[i]);
        }
      }

      if ((dimm_line < MrcCall->MrcLeftShift64 (dimm_s_size, 1)) && (rerun_zone_1 == FALSE)) {
        //
        // Range 0
        //
        //
        // Insert dimm_select bit
        //
        for (i = 0; i < DIMM_NUM_BITS; i++) {
          if (dimm_shifter[i] == -6) {
          } else {
            dimm_line = dimm_line |
            MrcCall->MrcLeftShift64 (
                       (enhanced_interleave_mode) ?
                       ((MrcCall->MrcRightShift64 (dimm_select, i) & 1) ^ (MrcCall->MrcRightShift64 (dimm_line, dimm_enhanced_shifter[i]) & 1)) :
                       (MrcCall->MrcRightShift64 (dimm_select, i) & 1),
                       dimm_shifter[i]
                       );
          }
        }
      }
      //
      // Put in the bank part of the address
      //
      for (i = 0; i < BANK_NUM_BITS; i++) {
        if (bank_shifter[i] == -6) {
        } else if (enhanced_interleave_mode) {
          dimm_line = dimm_line | (UINT64) MrcCall->MrcLeftShift64 (
                                                      (MrcCall->MrcRightShift64 (bank, i) & 1) ^ (MrcCall->MrcRightShift64 (dimm_line, bank_enhanced_shifter[i]) & 1),
                                                      bank_shifter[i]
                                                      );
        } else {
          dimm_line = dimm_line | (UINT64) MrcCall->MrcLeftShift64 ((MrcCall->MrcRightShift64 (bank, i) & 1), bank_shifter[i]);
        }
      }

      //
      // Put in the bg part of the address
      //
      for (i = 0; i < BG_NUM_BITS; i++) {
        if (bg_shifter[i] == -6) {
        } else if (enhanced_interleave_mode) {
          dimm_line = dimm_line | (UINT64) MrcCall->MrcLeftShift64 (
                                                      (MrcCall->MrcRightShift64 (bg, i) & 1) ^ (MrcCall->MrcRightShift64 (dimm_line, bg_enhanced_shifter[i]) & 1),
                                                      bg_shifter[i]
                                                      );
        } else {
          dimm_line = dimm_line | (UINT64) MrcCall->MrcLeftShift64 ((MrcCall->MrcRightShift64 (bg, i) & 1), bg_shifter[i]);
        }
      }

      //
      // Put in the rank part of the address
      //
      if (!dimm_and_rank_interleaving && rank) {
        dimm_line = dimm_line | MrcCall->MrcRightShift64 (dimm_size, 1);
      } else {
        for (i = 0; i < RANK_NUM_BITS; i++) {
          if (rank_shifter[i] == -6) {
          } else if (enhanced_interleave_mode) {
            dimm_line = dimm_line | (UINT64) MrcCall->MrcLeftShift64 (
                                                        (MrcCall->MrcRightShift64 (rank, i) & 1) ^ (MrcCall->MrcRightShift64 (dimm_line, rank_enhanced_shifter[i]) & 1),
                                                        rank_shifter[i]
                                                        );
          } else {
            dimm_line = dimm_line | (UINT64) MrcCall->MrcLeftShift64 ((MrcCall->MrcRightShift64 (rank, i) & 1), rank_shifter[i]);
          }
        }
      }

      //
      // Put in the col[10:10] part of the address:
      //
      for (i = (COL_NUM_BITS - 1); i < COL_NUM_BITS; i++) {
        if (col_shifter[i] == -6) {
        } else if (col_shifter[i] < 0) {
          col_shifter[i] += 6;
          *p_sys_addr = *p_sys_addr | (UINT64) MrcCall->MrcLeftShift64 ((MrcCall->MrcRightShift64 (col, i) & 1), col_shifter[i]);
        } else {
          if (enhanced_interleave_mode && (col_enhanced_shifter[i] != -6)) {
            dimm_line = dimm_line | (UINT64) MrcCall->MrcLeftShift64 (
                                                        (MrcCall->MrcRightShift64 (col, i) & 1) ^ (MrcCall->MrcRightShift64 (dimm_line, col_enhanced_shifter[i]) & 1),
                                                        col_shifter[i]
                                                        );
          } else {
            dimm_line = dimm_line | (UINT64) MrcCall->MrcLeftShift64 ((MrcCall->MrcRightShift64 (col, i) & 1), col_shifter[i]);
          }
        }
      }
    }

    //
    // DIMM address to channel address
    //
    // Find the DIMM sizes on our selected channel. adjust to cache-line granularity
    //
    dimm_l_size = get_dimm_l_size_as_cl (MrcCall, mad_dimm_l[chan]);
    dimm_s_size = get_dimm_s_size_as_cl (MrcCall, mad_dimm_l[chan]);

    //
    // Both dimm_and_rank_interleaving and high_order_rank_interleave cause DIMM interleaving.
    //
    if (dimm_and_rank_interleaving || high_order_rank_interleave) {
      //
      // DIMM and Rank interleaving (or HORI) enabled
      //
      //  +------16 GB------+
      //  |                 |
      //  .                 .
      //  .                 .
      //  .                 .
      //  |                 |
      //  |  unmapped       |
      //  |  space above    |
      //  |  channel        |
      //  |  capacity       |
      //  |                 |
      //  +--Range 1 Limit--+  <-- dimm_l_size + dimm_s_size
      //  |                 |
      //  |  No Interleave  |
      //  |     DIMM L      |
      //  |                 |
      //  +--Range 0 Limit--+  <-- dimm_s_size * 2
      //  |                 |
      //  | 2-Way Interleave|
      //  |   DIMMs L & S   |
      //  |                 |
      //  +-------0x0-------+
      //
      if ((dimm_line < MrcCall->MrcLeftShift64 (dimm_s_size, 1)) && (rerun_zone_1 == FALSE)) {
        //
        // Range 0
        //
        //
        // Insert dimm_select bit and convert to chan_line
        //
        for (i = 0; i < DIMM_NUM_BITS; i++) {
          if (dimm_shifter[i] == -6) {
            chan_line = dimm_line;
          } else {
            chan_line = dimm_line |
            MrcCall->MrcLeftShift64 (
                       (enhanced_interleave_mode) ?
                       ((MrcCall->MrcRightShift64 (dimm_select, i) & 1) ^ (MrcCall->MrcRightShift64 (dimm_line, dimm_enhanced_shifter[i]) & 1)) :
                       (MrcCall->MrcRightShift64 (dimm_select, i) & 1),
                       dimm_shifter[i]
                       );
          }
        }
        found_the_dimm_zone = TRUE;
      } else {
        //
        // Range 1
        //
        //
        // Channel address is DIMM L address with DIMM S's contribution from Range 0 added in
        //
        chan_line = dimm_line + dimm_s_size;

        if (rerun_zone_1 == FALSE) {
          rerun_zone_1 = TRUE;
        } else {
          found_the_dimm_zone = TRUE;
        }
      }
    } else {
      //
      // no DIMM and Rank interleaving (nor HORI).
      //
      //
      //  +------16 GB------+
      //  |                 |
      //  .                 .
      //  .                 .
      //  .                 .
      //  |                 |
      //  |  unmapped       |
      //  |  space above    |
      //  |  channel        |
      //  |  capacity       |
      //  |                 |
      //  +--Range 1 Limit--+  <-- dimm_l_size + dimm_s_size
      //  |                 |
      //  |  No Interleave  |
      //  |     DIMM S      |
      //  |                 |
      //  +--Range 0 Limit--+  <-- dimm_l_size
      //  |                 |
      //  |  No Interleave  |
      //  |     DIMM L      |
      //  |                 |
      //  +-------0x0-------+
      //
      chan_line = dimm_line;
      if (dimm_select) {
        //
        // DIMM is S
        //
        chan_line += dimm_l_size;
      }
      found_the_dimm_zone = TRUE;
    }
  }

  //
  // Channel address to remaped system address
  //

  //
  // Map physical channel to L or S
  //
  chan_select = physical_to_logical_chan (MAD_INTER_CHNL, chan);

  //
  // Stacked channel mode
  //
  //  +------0.5 TB------+
  //  |                  |
  //  .                  .
  //  .                  .
  //  .                  .
  //  |                  |
  //  |  unmapped        |
  //  |  space above     |
  //  |  DRAM            |
  //  |                  |
  //  +--2 * Stack size--+  <-- Top Of Memory = L + S
  //  |                  |
  //  |                  |
  //  |                  |
  //  |   Channel S      |
  //  |                  |
  //  |                  |
  //  +--- Stack size ---+  <-- Stack Size = Channel size (channels L and S must be equal)
  //  |                  |
  //  |                  |
  //  |                  |
  //  |   Channel L      |
  //  |                  |
  //  |                  |
  //  +--------0x0-------+
  //
  if (stacked_mode) {
    remap_line = chan_line;
    if (stacked_mode_ch1) {
      chan_select ^= 1;
    }
    //
    // In stacked mode, the channel is chosen based on the bit corresponding to the
    // size of the stacked register.  Bit-wise 'OR' in the channel selection bit into that
    // position.
    //
    remap_line |= MrcCall->MrcLeftShift64 (chan_select, 24 + stacked_encoding);
  }
  //
  // Determine which range/zone the remapped system address falls into
  //
  //  +-----0.5 TB-----+
  //  |                |
  //  .                .
  //  .                .
  //  .                .
  //  |                |
  //  |  unmapped      |
  //  |  space above   |
  //  |  DRAM          |
  //  |                |
  //  +--Zone 1 Limit--+  <-- Top Of Memory = L + S
  //  |                |
  //  |  No Interleave |
  //  |    Channel L   |
  //  |                |
  //  +--Zone 0 Limit--+  <-- 2 * S
  //  |                |
  //  |  2-Way Intlv   |
  //  | Channels L & S |
  //  |                |
  //  |                |
  //  |                |
  //  |                |
  //  |                |
  //  |                |
  //  +-------0x0------+
  //
  else if (chan_line < (ch_s_size)) {
    //
    // Zone 0
    //
    remap_line = MrcCall->MrcLeftShift64 (chan_line, 1);

    //
    // Determine if the channel hash feature is being used
    //
    if (CHANNEL_HASH & MC_ADDR_CHAN_HASH_ENABLE_MASK) {
      //
      // Test enable bit
      //
      hash_lsb_mask_bit = get_ch_hash_lsb_mask_bit (CHANNEL_HASH);
      hash_mask         = get_ch_hash_mask (CHANNEL_HASH);

      //
      // Reverse the swap of sys_addr bit 6 with bit pointed to by hash_lsb_mask_bit
      //
      remap_line = remap_line | (MrcCall->MrcRightShift64 (remap_line, hash_lsb_mask_bit) & 0x0000000000000001ULL);
      //
      // Copy hash_lsb_mask_bit to bit 6
      //
      remap_line = remap_line & (~(MrcCall->MrcLeftShift64 (0x0000000000000001ULL, hash_lsb_mask_bit)));

      hash_line = ((UINT16) remap_line) & hash_mask;

      //
      // Recreate the value of the bit at hash_lsb_mask_bit by doint the hash
      // XORs.
      //
      hash_bit = 0;
      for (i = 0; i < MC_ADDR_CHANNEL_HASH_MASK_SIZE; i++) {
        hash_bit = hash_bit ^ (hash_line >> i);
      }

      hash_bit = hash_bit & 1;

      //
      // Recreate the missing bit by XORing the chan_select (the result of
      // the forward decode).
      // (If X = A ^ B, then A = X ^ B)
      //
      hash_bit = hash_bit ^ chan_select;

      //
      // Put the missing bit back into the address
      //
      remap_line = remap_line | MrcCall->MrcLeftShift64 (hash_bit, hash_lsb_mask_bit);
    } else {
      //
      // Without the hash, sys_addr[6:6] determines the channel
      //
      remap_line |= ((UINT64) chan_select);
    }
  } else {
    //
    // Zone 1
    //
    remap_line = chan_line + (ch_s_size);
  }
  //
  // Work on full address instead of cache-line address;
  //
  remap_addr = MrcCall->MrcLeftShift64 (remap_line, 6);

  //
  // Determine if the address is under the remap zone and therefore must be a
  // TCM.  remap_line can't be at or above TOM (Top Of Memory), so no need to
  // check that.  Simply check if the remap_line is between the base and
  // limit.
  //
  *p_is_tcm = (remap_addr <= remap_limit) && (remap_addr >= remap_base);
  //
  // reverse decode the remap region
  //
  *p_sys_addr = remap_addr;
  //
  // If the remap doesn't apply system address is remap address
  //
  if (!(*p_is_tcm) && (remap_limit > remap_base)) {
    //
    // Remap doesn't apply if remap zone disabled
    //
    top_of_remaped_mem = (UINT64) tolud;
    top_of_remaped_mem += remap_limit;
    top_of_remaped_mem -= remap_base;
    if ((remap_addr <= top_of_remaped_mem) && (remap_addr >= ((UINT64) tolud))) {
      //
      // Remap applies, move the address to the remap zone
      //
      *p_sys_addr -= ((UINT64) tolud);
      *p_sys_addr += remap_base;
    }
  }
  //
  // Check if the DRAM address was removed from the available address space due to errors/faults in the DIMM
  //
  for (i = 0; i < MC_NUM_BER_REGS; i++) {
    if (en_sys_ber_match (MrcCall, *p_sys_addr, *p_is_tcm, BER_SRC[i])) {
      return FALSE;
    }
  }
  //
  // Check if the DRAM address is the target of a BER remap, which will override the reverse-decode result
  //
  for (i = 0; i < MC_NUM_BER_REGS; i++) {
    if (get_ber_valid (MrcCall, BER_SRC[i]) && dram_ber_match (chan, dimm, rank, bg, bank, row, col, BER_TGT[i], MAD_INTER_CHNL)) {
      *p_sys_addr = get_ber_sys_addr (BER_SRC[i]);
      *p_is_tcm   = get_ber_is_tcm (MrcCall, BER_SRC[i]);
      break;
    }
  }
  //
  // Restore cache-line chunk order
  //
  *p_sys_addr = *p_sys_addr | (MrcCall->MrcLeftShift64 (((UINT64) col), 3) & 0x3FULL);

  if (tom < remap_addr) {
    return FALSE;
  };
  return TRUE;
}

/**
  Address decode function
  Converts memory address to DRAM address

  @param[in]      MemoryAddress  - The 39-bit memory address to decode.
  @param[out]     DramAddress    - The DRAM address struct that the memory address decodes to.

  @retval Returns EFI_SUCCESS if successful, EFI_UNSUPPORTED otherwise.
**/
EFI_STATUS
(EFIAPI MrcMemoryAddressDecode) (
  IN  UINT64           MemoryAddress,
  OUT MRC_DRAM_ADDRESS *DramAddress
  )
{
  MRC_ADDR_FUNCTION CallTable;
  MRC_ADDR_FUNCTION *MrcCall;
  EFI_STATUS    Status;
  UINT32        MchBarBaseAddress;
  UINT32        PciEBaseAddress;
  UINT32        Offset;
  UINT16        TempChannel;
  UINT16        TempDimm;
  UINT16        TempRank;
  UINT16        TempBankGroup;
  UINT16        TempBank;
  UINT32        TempRow;
  UINT16        TempColumn;
  UINT64        TempBerSrc[] = {0,0,0,0};
  UINT32        TempBerTgt[] = {0,0,0,0};
  UINT64        Tom;
  UINT64        RemapBase;
  UINT64        RemapLimit;
  UINT32        Tolud;
  UINT32        ChannelHash;
  UINT32        MadInterChannel;
  UINT32        MadIntraCh0;
  UINT32        MadIntraCh1;
  UINT32        MadDimmCh0;
  UINT32        MadDimmCh1;
  BOOLEAN       IsTcm;

  MrcCall = &CallTable;
  Status  = EFI_UNSUPPORTED;

  //
  // Set function pointers
  //
#ifdef MRC_MINIBIOS_BUILD
  MrcCall->MrcIoRead32     = (MRC_IO_READ_32) (&MrcOemInPort32);
  MrcCall->MrcIoWrite32    = (MRC_IO_WRITE_32) (&MrcOemOutPort32);
  MrcCall->MrcMmioRead32   = (MRC_MMIO_READ_32) (&MrcOemMmioRead32);
  MrcCall->MrcMmioRead64   = (MRC_MMIO_READ_64) (&SaMmioRead64);
  MrcCall->MrcCopyMem      = (MRC_MEMORY_COPY) (&MrcOemMemoryCpy);
#else
  MrcCall->MrcIoRead32     = (MRC_IO_READ_32) (&IoRead32);
  MrcCall->MrcIoWrite32    = (MRC_IO_WRITE_32) (&IoWrite32);
  MrcCall->MrcMmioRead32   = (MRC_MMIO_READ_32) (&MmioRead32);
  MrcCall->MrcMmioRead64   = (MRC_MMIO_READ_64) (&MmioRead64);
  MrcCall->MrcCopyMem      = (MRC_MEMORY_COPY) (&CopyMem);
#endif // MRC_MINIBIOS_BUILD
  MrcCall->MrcSetMem       = (MRC_MEMORY_SET_BYTE) (&SetMem);
  MrcCall->MrcMultU64x32   = (MRC_MULT_U64_U32) (&MultU64x32);
  MrcCall->MrcDivU64x64    = (MRC_DIV_U64_U64) (&DivU64x64Remainder);
  MrcCall->MrcLeftShift64  = (MRC_LEFT_SHIFT_64) (&LShiftU64);
  MrcCall->MrcRightShift64 = (MRC_RIGHT_SHIFT_64) (&RShiftU64);

  //
  // Check that MCHBAR is programmed
  //
  MrcCall->MrcIoWrite32 (0xCF8, MRC_BIT31 | R_SA_MCHBAR);
  MchBarBaseAddress = MrcCall->MrcIoRead32 (0xCFC);

  if ((MchBarBaseAddress & MRC_BIT0) == MRC_BIT0) {
    MchBarBaseAddress &= (~MRC_BIT0);
  } else {
    return Status;
  }

  //
  // Check that PCIEXBAR is programmed
  //
  MrcCall->MrcIoWrite32 (0xCF8, MRC_BIT31 | R_SA_PCIEXBAR);
  PciEBaseAddress = MrcCall->MrcIoRead32 (0xCFC);

  if ((PciEBaseAddress & MRC_BIT0) == MRC_BIT0) {
    PciEBaseAddress &= ~(MRC_BIT2 | MRC_BIT1 | MRC_BIT0);
  } else {
    return Status;
  }

  //
  // Collect address configuration from registers
  //
  Offset               = PciEBaseAddress + R_SA_TOLUD;
  Tolud                = MrcCall->MrcMmioRead32 (Offset);
  Offset               = PciEBaseAddress + R_SA_REMAPBASE;
  RemapBase            = (UINT64) (MrcCall->MrcMmioRead32 (Offset) + MrcCall->MrcLeftShift64 (MrcCall->MrcMmioRead32 (Offset + 4), 32));
  Offset               = PciEBaseAddress + R_SA_REMAPLIMIT;
  RemapLimit           = (UINT64) (MrcCall->MrcMmioRead32 (Offset) + MrcCall->MrcLeftShift64 (MrcCall->MrcMmioRead32 (Offset + 4), 32));
  Offset               = PciEBaseAddress + R_SA_TOM;
  Tom                  = (UINT64) (MrcCall->MrcMmioRead32 (Offset) + MrcCall->MrcLeftShift64 (MrcCall->MrcMmioRead32 (Offset + 4), 32));
  ChannelHash          = MrcCall->MrcMmioRead32 (MchBarBaseAddress + R_SA_MCHBAR_CHANNEL_HASH_OFFSET);
  MadInterChannel      = MrcCall->MrcMmioRead32 (MchBarBaseAddress + R_SA_MCHBAR_MAD_INTER_CHANNEL_OFFSET);
  MadIntraCh0          = MrcCall->MrcMmioRead32 (MchBarBaseAddress + R_SA_MCHBAR_MAD_INTRA_CH0_OFFSET);
  MadIntraCh1          = MrcCall->MrcMmioRead32 (MchBarBaseAddress + R_SA_MCHBAR_MAD_INTRA_CH1_OFFSET);
  MadDimmCh0           = MrcCall->MrcMmioRead32 (MchBarBaseAddress + R_SA_MCHBAR_MAD_DIMM_CH0_OFFSET);
  MadDimmCh1           = MrcCall->MrcMmioRead32 (MchBarBaseAddress + R_SA_MCHBAR_MAD_DIMM_CH1_OFFSET);
  IsTcm                = FALSE;

  if (MrcDecode (
        MrcCall,
        MemoryAddress,
        &IsTcm,
        Tolud,
        RemapBase,
        RemapLimit,
        Tom,
        ChannelHash,
        MadInterChannel,
        MadIntraCh0,
        MadIntraCh1,
        MadDimmCh0,
        MadDimmCh1,
        TempBerSrc,
        TempBerTgt,
        0, //@todo BER_MC_ABORT,
        &TempChannel,
        &TempDimm,
        &TempRank,
        &TempBankGroup,
        &TempBank,
        &TempRow,
        &TempColumn
        )) {
    Status = EFI_SUCCESS;
  }
  DramAddress->Controller    = 0;
  DramAddress->ChannelNumber = (UINT8)  TempChannel;
  DramAddress->DimmNumber    = (UINT8)  TempDimm;
  DramAddress->Rank          = (UINT8)  TempRank;
  DramAddress->BankGroup     = (UINT8)  TempBankGroup;
  DramAddress->Bank          = (UINT8)  TempBank;
  DramAddress->Ras           = (UINT32) TempRow;
  DramAddress->Cas           = (UINT16) TempColumn;

  return Status;
}

/**
  Address encode function (reverse address decode)
  DRAM address to memory address conversion

  @param[in]      DramAddress    - The DRAM address that is to be encoded.
  @param[out]     MemoryAddress  - The 39-bit memory address to convert to.

  @retval Returns EFI_SUCCESS if successful, EFI_UNSUPPORTED otherwise.
**/
EFI_STATUS
(EFIAPI MrcMemoryAddressEncode) (
  IN  MRC_DRAM_ADDRESS *DramAddress,
  OUT UINT64           *MemoryAddress
  )
{
  MRC_ADDR_FUNCTION CallTable;
  MRC_ADDR_FUNCTION *MrcCall;
  EFI_STATUS    Status;
  UINT32        MchBarBaseAddress;
  UINT32        PciEBaseAddress;
  UINT32        Offset;
  BOOLEAN       IsTcm;
  UINT64        TempBerSrc[] = {0,0,0,0};
  UINT32        TempBerTgt[] = {0,0,0,0};
  UINT64        Tom;
  UINT64        RemapBase;
  UINT64        RemapLimit;
  UINT32        Tolud;
  UINT32        ChannelHash;
  UINT32        MadInterChannel;
  UINT32        MadIntraCh0;
  UINT32        MadIntraCh1;
  UINT32        MadDimmCh0;
  UINT32        MadDimmCh1;

  MrcCall = &CallTable;
  Status  = EFI_UNSUPPORTED;

  //
  // Set function pointers
  //
#ifdef MRC_MINIBIOS_BUILD
  MrcCall->MrcIoRead32     = (MRC_IO_READ_32) (&MrcOemInPort32);
  MrcCall->MrcIoWrite32    = (MRC_IO_WRITE_32) (&MrcOemOutPort32);
  MrcCall->MrcMmioRead32   = (MRC_MMIO_READ_32) (&MrcOemMmioRead32);
  MrcCall->MrcMmioRead64   = (MRC_MMIO_READ_64) (&SaMmioRead64);
  MrcCall->MrcCopyMem      = (MRC_MEMORY_COPY) (&MrcOemMemoryCpy);
#else
  MrcCall->MrcIoRead32     = (MRC_IO_READ_32) (&IoRead32);
  MrcCall->MrcIoWrite32    = (MRC_IO_WRITE_32) (&IoWrite32);
  MrcCall->MrcMmioRead32   = (MRC_MMIO_READ_32) (&MmioRead32);
  MrcCall->MrcMmioRead64   = (MRC_MMIO_READ_64) (&MmioRead64);
  MrcCall->MrcCopyMem      = (MRC_MEMORY_COPY) (&CopyMem);
#endif // MRC_MINIBIOS_BUILD
  MrcCall->MrcSetMem       = (MRC_MEMORY_SET_BYTE) (&SetMem);
  MrcCall->MrcMultU64x32   = (MRC_MULT_U64_U32) (&MultU64x32);
  MrcCall->MrcDivU64x64    = (MRC_DIV_U64_U64) (&DivU64x64Remainder);
  MrcCall->MrcLeftShift64  = (MRC_LEFT_SHIFT_64) (&LShiftU64);
  MrcCall->MrcRightShift64 = (MRC_RIGHT_SHIFT_64) (&RShiftU64);

  //
  // Check that MCHBAR is programmed
  //
  MrcCall->MrcIoWrite32 (0xCF8, MRC_BIT31 | R_SA_MCHBAR);
  MchBarBaseAddress = MrcCall->MrcIoRead32 (0xCFC);

  if ((MchBarBaseAddress & MRC_BIT0) == MRC_BIT0) {
    MchBarBaseAddress &= (~MRC_BIT0);
  } else {
    return Status;
  }

  //
  // Check that PCIEXBAR is programmed
  //
  MrcCall->MrcIoWrite32 (0xCF8, MRC_BIT31 | R_SA_PCIEXBAR);
  PciEBaseAddress = MrcCall->MrcIoRead32 (0xCFC);

  if ((PciEBaseAddress & MRC_BIT0) == MRC_BIT0) {
    PciEBaseAddress &= ~(MRC_BIT2 | MRC_BIT1 | MRC_BIT0);
  } else {
    return Status;
  }

  //
  // Collect address configuration from registers
  //
  Offset               = PciEBaseAddress + R_SA_TOLUD;
  Tolud                = MrcCall->MrcMmioRead32 (Offset);
  Offset               = PciEBaseAddress + R_SA_REMAPBASE;
  RemapBase            = (UINT64) (MrcCall->MrcMmioRead32 (Offset) + MrcCall->MrcLeftShift64 (MrcCall->MrcMmioRead32 (Offset + 4), 32));
  Offset               = PciEBaseAddress + R_SA_REMAPLIMIT;
  RemapLimit           = (UINT64) (MrcCall->MrcMmioRead32 (Offset) + MrcCall->MrcLeftShift64 (MrcCall->MrcMmioRead32 (Offset + 4), 32));
  Offset               = PciEBaseAddress + R_SA_TOM;
  Tom                  = (UINT64) (MrcCall->MrcMmioRead32 (Offset) + MrcCall->MrcLeftShift64 (MrcCall->MrcMmioRead32 (Offset + 4), 32));
  ChannelHash          = MrcCall->MrcMmioRead32 (MchBarBaseAddress + R_SA_MCHBAR_CHANNEL_HASH_OFFSET);
  MadInterChannel      = MrcCall->MrcMmioRead32 (MchBarBaseAddress + R_SA_MCHBAR_MAD_INTER_CHANNEL_OFFSET);
  MadIntraCh0          = MrcCall->MrcMmioRead32 (MchBarBaseAddress + R_SA_MCHBAR_MAD_INTRA_CH0_OFFSET);
  MadIntraCh1          = MrcCall->MrcMmioRead32 (MchBarBaseAddress + R_SA_MCHBAR_MAD_INTRA_CH1_OFFSET);
  MadDimmCh0           = MrcCall->MrcMmioRead32 (MchBarBaseAddress + R_SA_MCHBAR_MAD_DIMM_CH0_OFFSET);
  MadDimmCh1           = MrcCall->MrcMmioRead32 (MchBarBaseAddress + R_SA_MCHBAR_MAD_DIMM_CH1_OFFSET);
  IsTcm                = FALSE;


  if (MrcEncode (
        MrcCall,
        DramAddress->ChannelNumber,
        DramAddress->DimmNumber,
        DramAddress->Rank,
        DramAddress->BankGroup,
        DramAddress->Bank,
        DramAddress->Ras,
        DramAddress->Cas,
        Tolud,
        RemapBase,
        RemapLimit,
        Tom,
        ChannelHash,
        MadInterChannel,
        MadIntraCh0,
        MadIntraCh1,
        MadDimmCh0,
        MadDimmCh1,
        TempBerSrc,
        TempBerTgt,
        0,
        MemoryAddress,
        &IsTcm
        )) {
    Status = EFI_SUCCESS;
  }

  return Status;
}
