/** @file
  Address encoding definitions and functions.

 @copyright
  INTEL CONFIDENTIAL
  Copyright 2011 - 2016 Intel Corporation.

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

@par Specification
**/

#ifndef _DCTT_ADDRESS_FUNCTIONS_H_
#define _DCTT_ADDRESS_FUNCTIONS_H_
//Compacting the address to a UINT32
//col = 8 (10) bits     | 0
//row = 16 bits         | 8
//bank = 3 bits         | 24
//rank = 3 bits         | 27
//channel = 2 bits      | 30
//                      | 32

//single bit or multi bit
#define AddressToUINT32(_channel, _rank, _bank, _row, _col) \
  ((((_col) >> 3) & 0xFF) | \
  (((_row) & 0xFFFF) << 8) | \
  (((_bank) & 0x7) << 24)  | \
  (((_rank) & 0x7) << 27)  | \
  (((_channel) & 0x3) << 30))

#define GetColFromUINT32(compactAddress) (((compactAddress) &  0xFF) << 3)

#define GetRowFromUINT32(compactAddress) (((compactAddress) >> 8) & 0xFFFF)

#define GetBankFromUINT32(compactAddress) (((compactAddress) >> 24) & 0x7)

#define GetRankFromUINT32(compactAddress) (((compactAddress) >> 27) & 0x7)

#define GetChannelFromUINT32(compactAddress) (((compactAddress) >> 30) & 0x3)
typedef union {
  struct {
    UINT64  Column    : 11;   ///< Bits 0:10
    UINT64  Bank      : 3;    ///< Bits 11:13
    UINT64  BankGroup : 2;    ///< Bits 14:15
    UINT64  Rank      : 4;    ///< Bits 16:19
    UINT64  Channel   : 3;    ///< Bits 20:22
    UINT64            : 9;    ///< Bits 23:31
    UINT64  Row       : 17;   ///< Bits 32:48
    UINT64            : 15;   ///< Bits 49:63
  } Bits;
  UINT64  Data;
  UINT32  Data32[2];
} DCTT_DDR_ADDRESS;

UINT64
CompressAddress (
  UINT16  Column,
  UINT32  Row,
  UINT8   Bank,
  UINT8   BankGroup,
  UINT8   Rank,
  UINT8   Channel
  );
#endif // _DCTT_ADDRESS_FUNCTIONS_H_
