/** @file
  This module configures the memory controller power modes.

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

///
/// Include files
///
#include "MrcTypes.h"
#include "MrcApi.h"
#include "MrcPowerModes.h"
#include "MrcDebugPrint.h"
#include "MrcSpdProcessing.h"

GLOBAL_REMOVE_IF_UNREFERENCED const DdrPowerWeightEntry Ddr3PowerWeightTable0[] = {
  {{{VDD_135, ECC_F, TYPE_SODIMM, WIDTH_8,  RANKS_1, DPC_1, FREQ_1067, DENSITY_2, 0}}, 4, 0x56, 0xA3, 0x69, 0x7, 0x0D, 0x07},
  {{{VDD_135, ECC_F, TYPE_SODIMM, WIDTH_8,  RANKS_2, DPC_1, FREQ_1067, DENSITY_2, 0}}, 4, 0x54, 0xDD, 0x67, 0x7, 0x0B, 0x09},
  {{{VDD_135, ECC_F, TYPE_SODIMM, WIDTH_8,  RANKS_1, DPC_1, FREQ_1067, DENSITY_4, 0}}, 4, 0x61, 0xAD, 0x6C, 0x9, 0x10, 0x08},
  {{{VDD_135, ECC_F, TYPE_SODIMM, WIDTH_8,  RANKS_2, DPC_1, FREQ_1067, DENSITY_4, 0}}, 4, 0x5F, 0xE7, 0x6A, 0x9, 0x0E, 0x0B},
  {{{VDD_135, ECC_F, TYPE_SODIMM, WIDTH_16, RANKS_1, DPC_1, FREQ_1067, DENSITY_2, 0}}, 4, 0x4A, 0x8F, 0x65, 0x4, 0x09, 0x06},
  {{{VDD_135, ECC_F, TYPE_SODIMM, WIDTH_16, RANKS_2, DPC_1, FREQ_1067, DENSITY_2, 0}}, 4, 0x48, 0xC9, 0x63, 0x4, 0x07, 0x07},
  {{{VDD_135, ECC_F, TYPE_SODIMM, WIDTH_16, RANKS_1, DPC_1, FREQ_1067, DENSITY_4, 0}}, 4, 0x53, 0x96, 0x69, 0x5, 0x0A, 0x06},
  {{{VDD_135, ECC_F, TYPE_SODIMM, WIDTH_16, RANKS_2, DPC_1, FREQ_1067, DENSITY_4, 0}}, 4, 0x51, 0xD0, 0x67, 0x5, 0x08, 0x08},
  {{{VDD_135, ECC_F, TYPE_SODIMM, WIDTH_8,  RANKS_1, DPC_2, FREQ_1067, DENSITY_2, 0}}, 3, 0x81, 0xA4, 0x34, 0x4, 0x06, 0x0E},
  {{{VDD_135, ECC_F, TYPE_SODIMM, WIDTH_8,  RANKS_2, DPC_2, FREQ_1067, DENSITY_2, 0}}, 3, 0x80, 0xA3, 0x33, 0x4, 0x06, 0x14},
  {{{VDD_135, ECC_F, TYPE_SODIMM, WIDTH_8,  RANKS_1, DPC_2, FREQ_1067, DENSITY_4, 0}}, 3, 0x87, 0xA9, 0x36, 0x5, 0x07, 0x10},
  {{{VDD_135, ECC_F, TYPE_SODIMM, WIDTH_8,  RANKS_2, DPC_2, FREQ_1067, DENSITY_4, 0}}, 3, 0x86, 0xA8, 0x35, 0x5, 0x07, 0x16},
  {{{VDD_135, ECC_F, TYPE_SODIMM, WIDTH_16, RANKS_1, DPC_2, FREQ_1067, DENSITY_2, 0}}, 3, 0x7B, 0x9A, 0x32, 0x2, 0x04, 0x0C},
  {{{VDD_135, ECC_F, TYPE_SODIMM, WIDTH_16, RANKS_2, DPC_2, FREQ_1067, DENSITY_2, 0}}, 3, 0x7A, 0x99, 0x31, 0x2, 0x03, 0x0E},
  {{{VDD_135, ECC_F, TYPE_SODIMM, WIDTH_16, RANKS_1, DPC_2, FREQ_1067, DENSITY_4, 0}}, 3, 0x7F, 0x9D, 0x34, 0x3, 0x05, 0x0D},
  {{{VDD_135, ECC_F, TYPE_SODIMM, WIDTH_16, RANKS_2, DPC_2, FREQ_1067, DENSITY_4, 0}}, 3, 0x7F, 0x9D, 0x33, 0x3, 0x04, 0x10},
  {{{VDD_135, ECC_F, TYPE_SODIMM, WIDTH_8,  RANKS_1, DPC_1, FREQ_1333, DENSITY_2, 0}}, 4, 0x53, 0x91, 0x6E, 0x6, 0x0C, 0x08},
  {{{VDD_135, ECC_F, TYPE_SODIMM, WIDTH_8,  RANKS_2, DPC_1, FREQ_1333, DENSITY_2, 0}}, 4, 0x51, 0x8F, 0x6D, 0x6, 0x0A, 0x0B},
  {{{VDD_135, ECC_F, TYPE_SODIMM, WIDTH_8,  RANKS_1, DPC_1, FREQ_1333, DENSITY_4, 0}}, 4, 0x5E, 0x9B, 0x71, 0x8, 0x0E, 0x09},
  {{{VDD_135, ECC_F, TYPE_SODIMM, WIDTH_8,  RANKS_2, DPC_1, FREQ_1333, DENSITY_4, 0}}, 4, 0x5C, 0x99, 0x6F, 0x8, 0x0C, 0x0C},
  {{{VDD_135, ECC_F, TYPE_SODIMM, WIDTH_16, RANKS_1, DPC_1, FREQ_1333, DENSITY_2, 0}}, 5, 0x8D, 0xF9, 0xC9, 0x7, 0x0F, 0x06},
  {{{VDD_135, ECC_F, TYPE_SODIMM, WIDTH_16, RANKS_2, DPC_1, FREQ_1333, DENSITY_2, 0}}, 5, 0x8A, 0xF6, 0xC5, 0x7, 0x0C, 0x08},
  {{{VDD_135, ECC_F, TYPE_SODIMM, WIDTH_16, RANKS_1, DPC_1, FREQ_1333, DENSITY_4, 0}}, 4, 0x4F, 0x84, 0x68, 0x4, 0x09, 0x07},
  {{{VDD_135, ECC_F, TYPE_SODIMM, WIDTH_16, RANKS_2, DPC_1, FREQ_1333, DENSITY_4, 0}}, 4, 0x4E, 0x82, 0x66, 0x4, 0x07, 0x09},
  {{{VDD_135, ECC_F, TYPE_SODIMM, WIDTH_8,  RANKS_1, DPC_2, FREQ_1333, DENSITY_2, 0}}, 3, 0x6E, 0x8A, 0x37, 0x3, 0x05, 0x0F},
  {{{VDD_135, ECC_F, TYPE_SODIMM, WIDTH_8,  RANKS_2, DPC_2, FREQ_1333, DENSITY_2, 0}}, 3, 0x6E, 0x8A, 0x36, 0x3, 0x05, 0x16},
  {{{VDD_135, ECC_F, TYPE_SODIMM, WIDTH_8,  RANKS_1, DPC_2, FREQ_1333, DENSITY_4, 0}}, 3, 0x74, 0x8F, 0x38, 0x4, 0x06, 0x11},
  {{{VDD_135, ECC_F, TYPE_SODIMM, WIDTH_8,  RANKS_2, DPC_2, FREQ_1333, DENSITY_4, 0}}, 3, 0x74, 0x8F, 0x38, 0x4, 0x06, 0x18},
  {{{VDD_135, ECC_F, TYPE_SODIMM, WIDTH_16, RANKS_1, DPC_2, FREQ_1333, DENSITY_2, 0}}, 3, 0x68, 0x80, 0x32, 0x2, 0x04, 0x0E},
  {{{VDD_135, ECC_F, TYPE_SODIMM, WIDTH_16, RANKS_2, DPC_2, FREQ_1333, DENSITY_2, 0}}, 4, 0xCF, 0xFF, 0x62, 0x4, 0x06, 0x10},
  {{{VDD_135, ECC_F, TYPE_SODIMM, WIDTH_16, RANKS_1, DPC_2, FREQ_1333, DENSITY_4, 0}}, 3, 0x6D, 0x84, 0x34, 0x2, 0x04, 0x0E},
  {{{VDD_135, ECC_F, TYPE_SODIMM, WIDTH_16, RANKS_2, DPC_2, FREQ_1333, DENSITY_4, 0}}, 3, 0x6C, 0x83, 0x33, 0x2, 0x04, 0x13},
  {{{VDD_135, ECC_F, TYPE_SODIMM, WIDTH_8,  RANKS_1, DPC_1, FREQ_1600, DENSITY_2, 0}}, 4, 0x5D, 0xCD, 0x75, 0x6, 0x0B, 0x0A},
  {{{VDD_135, ECC_F, TYPE_SODIMM, WIDTH_8,  RANKS_2, DPC_1, FREQ_1600, DENSITY_2, 0}}, 4, 0x5B, 0xCB, 0x73, 0x6, 0x09, 0x0D},
  {{{VDD_135, ECC_F, TYPE_SODIMM, WIDTH_8,  RANKS_1, DPC_1, FREQ_1600, DENSITY_4, 0}}, 4, 0x68, 0xD6, 0x77, 0x7, 0x0C, 0x0B},
  {{{VDD_135, ECC_F, TYPE_SODIMM, WIDTH_8,  RANKS_2, DPC_1, FREQ_1600, DENSITY_4, 0}}, 4, 0x66, 0xD5, 0x76, 0x7, 0x0B, 0x0E},
  {{{VDD_135, ECC_F, TYPE_SODIMM, WIDTH_16, RANKS_1, DPC_1, FREQ_1600, DENSITY_2, 0}}, 4, 0x50, 0xB9, 0x66, 0x3, 0x07, 0x08},
  {{{VDD_135, ECC_F, TYPE_SODIMM, WIDTH_16, RANKS_2, DPC_1, FREQ_1600, DENSITY_2, 0}}, 4, 0x4E, 0xB8, 0x65, 0x3, 0x06, 0x0A},
  {{{VDD_135, ECC_F, TYPE_SODIMM, WIDTH_16, RANKS_1, DPC_1, FREQ_1600, DENSITY_4, 0}}, 4, 0x58, 0xC0, 0x69, 0x4, 0x08, 0x09},
  {{{VDD_135, ECC_F, TYPE_SODIMM, WIDTH_16, RANKS_2, DPC_1, FREQ_1600, DENSITY_4, 0}}, 4, 0x57, 0xBE, 0x68, 0x4, 0x07, 0x0B},
  {{{VDD_135, ECC_F, TYPE_SODIMM, WIDTH_8,  RANKS_1, DPC_2, FREQ_1600, DENSITY_2, 0}}, 3, 0x73, 0xA7, 0x3A, 0x3, 0x05, 0x13},
  {{{VDD_135, ECC_F, TYPE_SODIMM, WIDTH_8,  RANKS_2, DPC_2, FREQ_1600, DENSITY_2, 0}}, 3, 0x73, 0xA6, 0x3A, 0x3, 0x05, 0x1A},
  {{{VDD_135, ECC_F, TYPE_SODIMM, WIDTH_8,  RANKS_1, DPC_2, FREQ_1600, DENSITY_4, 0}}, 3, 0x79, 0xAB, 0x3B, 0x4, 0x06, 0x15},
  {{{VDD_135, ECC_F, TYPE_SODIMM, WIDTH_8,  RANKS_2, DPC_2, FREQ_1600, DENSITY_4, 0}}, 3, 0x79, 0xAB, 0x3B, 0x4, 0x05, 0x1B},
  {{{VDD_135, ECC_F, TYPE_SODIMM, WIDTH_16, RANKS_1, DPC_2, FREQ_1600, DENSITY_2, 0}}, 3, 0x6D, 0x9D, 0x33, 0x2, 0x03, 0x0F},
  {{{VDD_135, ECC_F, TYPE_SODIMM, WIDTH_16, RANKS_2, DPC_2, FREQ_1600, DENSITY_2, 0}}, 3, 0x6D, 0x9C, 0x32, 0x2, 0x03, 0x14},
  {{{VDD_135, ECC_F, TYPE_SODIMM, WIDTH_16, RANKS_1, DPC_2, FREQ_1600, DENSITY_4, 0}}, 3, 0x71, 0xA0, 0x34, 0x2, 0x04, 0x11},
  {{{VDD_135, ECC_F, TYPE_SODIMM, WIDTH_16, RANKS_2, DPC_2, FREQ_1600, DENSITY_4, 0}}, 3, 0x71, 0xA0, 0x34, 0x2, 0x03, 0x14},
  {{{VDD_135, ECC_F, TYPE_SODIMM, WIDTH_8,  RANKS_1, DPC_1, FREQ_1867, DENSITY_2, 0}}, 4, 0x5A, 0xBA, 0x7F, 0x5, 0x0A, 0x0B},
  {{{VDD_135, ECC_F, TYPE_SODIMM, WIDTH_8,  RANKS_2, DPC_1, FREQ_1867, DENSITY_2, 0}}, 4, 0x59, 0xB9, 0x7E, 0x5, 0x09, 0x0F},
  {{{VDD_135, ECC_F, TYPE_SODIMM, WIDTH_8,  RANKS_1, DPC_1, FREQ_1867, DENSITY_4, 0}}, 4, 0x65, 0xC3, 0x81, 0x7, 0x0B, 0x0C},
  {{{VDD_135, ECC_F, TYPE_SODIMM, WIDTH_8,  RANKS_2, DPC_1, FREQ_1867, DENSITY_4, 0}}, 4, 0x64, 0xC2, 0x80, 0x7, 0x0A, 0x10},
  {{{VDD_135, ECC_F, TYPE_SODIMM, WIDTH_16, RANKS_1, DPC_1, FREQ_1867, DENSITY_2, 0}}, 4, 0x4D, 0xA7, 0x6B, 0x3, 0x06, 0x09},
  {{{VDD_135, ECC_F, TYPE_SODIMM, WIDTH_16, RANKS_2, DPC_1, FREQ_1867, DENSITY_2, 0}}, 4, 0x4C, 0xA6, 0x69, 0x3, 0x05, 0x0A},
  {{{VDD_135, ECC_F, TYPE_SODIMM, WIDTH_16, RANKS_1, DPC_1, FREQ_1867, DENSITY_4, 0}}, 4, 0x55, 0xAD, 0x6E, 0x4, 0x07, 0x09},
  {{{VDD_135, ECC_F, TYPE_SODIMM, WIDTH_16, RANKS_2, DPC_1, FREQ_1867, DENSITY_4, 0}}, 4, 0x54, 0xAC, 0x6C, 0x4, 0x06, 0x0C},
  {{{VDD_135, ECC_F, TYPE_SODIMM, WIDTH_8,  RANKS_1, DPC_2, FREQ_1867, DENSITY_2, 0}}, 3, 0x68, 0x94, 0x3F, 0x3, 0x05, 0x15},
  {{{VDD_135, ECC_F, TYPE_SODIMM, WIDTH_8,  RANKS_2, DPC_2, FREQ_1867, DENSITY_2, 0}}, 3, 0x68, 0x94, 0x3F, 0x3, 0x04, 0x1B},
  {{{VDD_135, ECC_F, TYPE_SODIMM, WIDTH_8,  RANKS_1, DPC_2, FREQ_1867, DENSITY_4, 0}}, 3, 0x6E, 0x99, 0x40, 0x4, 0x05, 0x16},
  {{{VDD_135, ECC_F, TYPE_SODIMM, WIDTH_8,  RANKS_2, DPC_2, FREQ_1867, DENSITY_4, 0}}, 3, 0x6D, 0x98, 0x40, 0x4, 0x05, 0x1E},
  {{{VDD_135, ECC_F, TYPE_SODIMM, WIDTH_16, RANKS_1, DPC_2, FREQ_1867, DENSITY_2, 0}}, 3, 0x62, 0x8A, 0x35, 0x2, 0x03, 0x11},
  {{{VDD_135, ECC_F, TYPE_SODIMM, WIDTH_16, RANKS_2, DPC_2, FREQ_1867, DENSITY_2, 0}}, 3, 0x62, 0x8A, 0x35, 0x2, 0x03, 0x16},
  {{{VDD_135, ECC_F, TYPE_SODIMM, WIDTH_16, RANKS_1, DPC_2, FREQ_1867, DENSITY_4, 0}}, 3, 0x66, 0x8E, 0x37, 0x2, 0x03, 0x11},
  {{{VDD_135, ECC_F, TYPE_SODIMM, WIDTH_16, RANKS_2, DPC_2, FREQ_1867, DENSITY_4, 0}}, 3, 0x66, 0x8D, 0x36, 0x2, 0x03, 0x17},
  {{{VDD_135, ECC_F, TYPE_SODIMM, WIDTH_8,  RANKS_1, DPC_1, FREQ_2133, DENSITY_2, 0}}, 4, 0x58, 0xAC, 0x86, 0x5, 0x09, 0x0C},
  {{{VDD_135, ECC_F, TYPE_SODIMM, WIDTH_8,  RANKS_2, DPC_1, FREQ_2133, DENSITY_2, 0}}, 4, 0x57, 0xAB, 0x85, 0x5, 0x08, 0x10},
  {{{VDD_135, ECC_F, TYPE_SODIMM, WIDTH_8,  RANKS_1, DPC_1, FREQ_2133, DENSITY_4, 0}}, 4, 0x63, 0xB5, 0x88, 0x6, 0x0B, 0x0E},
  {{{VDD_135, ECC_F, TYPE_SODIMM, WIDTH_8,  RANKS_2, DPC_1, FREQ_2133, DENSITY_4, 0}}, 4, 0x62, 0xB4, 0x87, 0x6, 0x0A, 0x12},
  {{{VDD_135, ECC_F, TYPE_SODIMM, WIDTH_16, RANKS_1, DPC_1, FREQ_2133, DENSITY_2, 0}}, 4, 0x4A, 0x99, 0x6D, 0x3, 0x06, 0x0A},
  {{{VDD_135, ECC_F, TYPE_SODIMM, WIDTH_16, RANKS_2, DPC_1, FREQ_2133, DENSITY_2, 0}}, 4, 0x49, 0x98, 0x6C, 0x3, 0x05, 0x0C},
  {{{VDD_135, ECC_F, TYPE_SODIMM, WIDTH_16, RANKS_1, DPC_1, FREQ_2133, DENSITY_4, 0}}, 4, 0x53, 0x9F, 0x70, 0x4, 0x07, 0x0B},
  {{{VDD_135, ECC_F, TYPE_SODIMM, WIDTH_16, RANKS_2, DPC_1, FREQ_2133, DENSITY_4, 0}}, 4, 0x52, 0x9E, 0x6F, 0x4, 0x06, 0x0D},
  {{{VDD_135, ECC_F, TYPE_SODIMM, WIDTH_8,  RANKS_1, DPC_2, FREQ_2133, DENSITY_2, 0}}, 3, 0x60, 0x86, 0x43, 0x3, 0x04, 0x16},
  {{{VDD_135, ECC_F, TYPE_SODIMM, WIDTH_8,  RANKS_2, DPC_2, FREQ_2133, DENSITY_2, 0}}, 3, 0x60, 0x86, 0x43, 0x3, 0x04, 0x1D},
  {{{VDD_135, ECC_F, TYPE_SODIMM, WIDTH_8,  RANKS_1, DPC_2, FREQ_2133, DENSITY_4, 0}}, 3, 0x65, 0x8B, 0x44, 0x3, 0x05, 0x18},
  {{{VDD_135, ECC_F, TYPE_SODIMM, WIDTH_8,  RANKS_2, DPC_2, FREQ_2133, DENSITY_4, 0}}, 3, 0x65, 0x8B, 0x44, 0x3, 0x05, 0x22},
  {{{VDD_135, ECC_F, TYPE_SODIMM, WIDTH_16, RANKS_1, DPC_2, FREQ_2133, DENSITY_2, 0}}, 4, 0xB2, 0xF9, 0x6C, 0x3, 0x05, 0x11},
  {{{VDD_135, ECC_F, TYPE_SODIMM, WIDTH_16, RANKS_2, DPC_2, FREQ_2133, DENSITY_2, 0}}, 4, 0xB1, 0xF8, 0x6C, 0x3, 0x05, 0x16},
  {{{VDD_135, ECC_F, TYPE_SODIMM, WIDTH_16, RANKS_1, DPC_2, FREQ_2133, DENSITY_4, 0}}, 4, 0xBA, 0xFF, 0x6F, 0x4, 0x06, 0x13},
  {{{VDD_135, ECC_F, TYPE_SODIMM, WIDTH_16, RANKS_2, DPC_2, FREQ_2133, DENSITY_4, 0}}, 4, 0xB9, 0xFF, 0x6F, 0x4, 0x05, 0x17},
  {{{VDD_135, ECC_F, TYPE_UDIMM,  WIDTH_8,  RANKS_1, DPC_1, FREQ_1067, DENSITY_2, 0}}, 4, 0x63, 0xA3, 0x69, 0x7, 0x0D, 0x07},
  {{{VDD_135, ECC_F, TYPE_UDIMM,  WIDTH_8,  RANKS_2, DPC_1, FREQ_1067, DENSITY_2, 0}}, 4, 0x61, 0xA1, 0x67, 0x7, 0x0B, 0x09},
  {{{VDD_135, ECC_F, TYPE_UDIMM,  WIDTH_8,  RANKS_1, DPC_1, FREQ_1067, DENSITY_4, 0}}, 4, 0x6E, 0xAD, 0x6C, 0x9, 0x10, 0x08},
  {{{VDD_135, ECC_F, TYPE_UDIMM,  WIDTH_8,  RANKS_2, DPC_1, FREQ_1067, DENSITY_4, 0}}, 4, 0x6C, 0xAB, 0x6A, 0x9, 0x0E, 0x0B},
  {{{VDD_135, ECC_F, TYPE_UDIMM,  WIDTH_16, RANKS_1, DPC_1, FREQ_1067, DENSITY_2, 0}}, 4, 0x57, 0x8F, 0x65, 0x4, 0x09, 0x06},
  {{{VDD_135, ECC_F, TYPE_UDIMM,  WIDTH_16, RANKS_2, DPC_1, FREQ_1067, DENSITY_2, 0}}, 4, 0x55, 0x8D, 0x63, 0x4, 0x07, 0x07},
  {{{VDD_135, ECC_F, TYPE_UDIMM,  WIDTH_16, RANKS_1, DPC_1, FREQ_1067, DENSITY_4, 0}}, 4, 0x5F, 0x96, 0x68, 0x5, 0x0A, 0x06},
  {{{VDD_135, ECC_F, TYPE_UDIMM,  WIDTH_16, RANKS_2, DPC_1, FREQ_1067, DENSITY_4, 0}}, 4, 0x5D, 0x94, 0x67, 0x5, 0x08, 0x08},
  {{{VDD_135, ECC_F, TYPE_UDIMM,  WIDTH_8,  RANKS_1, DPC_2, FREQ_1067, DENSITY_2, 0}}, 3, 0x99, 0xBC, 0x34, 0x4, 0x06, 0x10},
  {{{VDD_135, ECC_F, TYPE_UDIMM,  WIDTH_8,  RANKS_2, DPC_2, FREQ_1067, DENSITY_2, 0}}, 3, 0x99, 0xBC, 0x33, 0x4, 0x06, 0x16},
  {{{VDD_135, ECC_F, TYPE_UDIMM,  WIDTH_8,  RANKS_1, DPC_2, FREQ_1067, DENSITY_4, 0}}, 3, 0x9F, 0xC1, 0x36, 0x5, 0x07, 0x11},
  {{{VDD_135, ECC_F, TYPE_UDIMM,  WIDTH_8,  RANKS_2, DPC_2, FREQ_1067, DENSITY_4, 0}}, 3, 0x9E, 0xC1, 0x35, 0x5, 0x07, 0x18},
  {{{VDD_135, ECC_F, TYPE_UDIMM,  WIDTH_16, RANKS_1, DPC_2, FREQ_1067, DENSITY_2, 0}}, 3, 0x93, 0xB2, 0x32, 0x2, 0x04, 0x0D},
  {{{VDD_135, ECC_F, TYPE_UDIMM,  WIDTH_16, RANKS_2, DPC_2, FREQ_1067, DENSITY_2, 0}}, 3, 0x93, 0xB1, 0x31, 0x2, 0x03, 0x0F},
  {{{VDD_135, ECC_F, TYPE_UDIMM,  WIDTH_16, RANKS_1, DPC_2, FREQ_1067, DENSITY_4, 0}}, 3, 0x98, 0xB6, 0x34, 0x3, 0x05, 0x0F},
  {{{VDD_135, ECC_F, TYPE_UDIMM,  WIDTH_16, RANKS_2, DPC_2, FREQ_1067, DENSITY_4, 0}}, 3, 0x97, 0xB5, 0x33, 0x3, 0x04, 0x12},
  {{{VDD_135, ECC_F, TYPE_UDIMM,  WIDTH_8,  RANKS_1, DPC_1, FREQ_1333, DENSITY_2, 0}}, 4, 0x5D, 0x91, 0x6E, 0x6, 0x0C, 0x08},
  {{{VDD_135, ECC_F, TYPE_UDIMM,  WIDTH_8,  RANKS_2, DPC_1, FREQ_1333, DENSITY_2, 0}}, 4, 0x5B, 0x8F, 0x6D, 0x6, 0x0A, 0x0B},
  {{{VDD_135, ECC_F, TYPE_UDIMM,  WIDTH_8,  RANKS_1, DPC_1, FREQ_1333, DENSITY_4, 0}}, 4, 0x68, 0x9B, 0x71, 0x8, 0x0E, 0x09},
  {{{VDD_135, ECC_F, TYPE_UDIMM,  WIDTH_8,  RANKS_2, DPC_1, FREQ_1333, DENSITY_4, 0}}, 4, 0x67, 0x99, 0x6F, 0x8, 0x0C, 0x0D},
  {{{VDD_135, ECC_F, TYPE_UDIMM,  WIDTH_16, RANKS_1, DPC_1, FREQ_1333, DENSITY_2, 0}}, 5, 0xA2, 0xF9, 0xC8, 0x7, 0x0F, 0x07},
  {{{VDD_135, ECC_F, TYPE_UDIMM,  WIDTH_16, RANKS_2, DPC_1, FREQ_1333, DENSITY_2, 0}}, 5, 0x9E, 0xF6, 0xC5, 0x7, 0x0C, 0x08},
  {{{VDD_135, ECC_F, TYPE_UDIMM,  WIDTH_16, RANKS_1, DPC_1, FREQ_1333, DENSITY_4, 0}}, 4, 0x5A, 0x84, 0x68, 0x4, 0x09, 0x07},
  {{{VDD_135, ECC_F, TYPE_UDIMM,  WIDTH_16, RANKS_2, DPC_1, FREQ_1333, DENSITY_4, 0}}, 4, 0x58, 0x82, 0x66, 0x4, 0x07, 0x09},
  {{{VDD_135, ECC_F, TYPE_UDIMM,  WIDTH_8,  RANKS_1, DPC_2, FREQ_1333, DENSITY_2, 0}}, 3, 0x82, 0x9E, 0x37, 0x3, 0x05, 0x11},
  {{{VDD_135, ECC_F, TYPE_UDIMM,  WIDTH_8,  RANKS_2, DPC_2, FREQ_1333, DENSITY_2, 0}}, 3, 0x81, 0x9D, 0x36, 0x3, 0x05, 0x17},
  {{{VDD_135, ECC_F, TYPE_UDIMM,  WIDTH_8,  RANKS_1, DPC_2, FREQ_1333, DENSITY_4, 0}}, 3, 0x88, 0xA3, 0x38, 0x4, 0x06, 0x12},
  {{{VDD_135, ECC_F, TYPE_UDIMM,  WIDTH_8,  RANKS_2, DPC_2, FREQ_1333, DENSITY_4, 0}}, 3, 0x87, 0xA2, 0x38, 0x4, 0x06, 0x1A},
  {{{VDD_135, ECC_F, TYPE_UDIMM,  WIDTH_16, RANKS_1, DPC_2, FREQ_1333, DENSITY_2, 0}}, 3, 0x7C, 0x94, 0x32, 0x2, 0x03, 0x0E},
  {{{VDD_135, ECC_F, TYPE_UDIMM,  WIDTH_16, RANKS_2, DPC_2, FREQ_1333, DENSITY_2, 0}}, 3, 0x7B, 0x93, 0x31, 0x2, 0x03, 0x12},
  {{{VDD_135, ECC_F, TYPE_UDIMM,  WIDTH_16, RANKS_1, DPC_2, FREQ_1333, DENSITY_4, 0}}, 3, 0x80, 0x97, 0x34, 0x2, 0x04, 0x0F},
  {{{VDD_135, ECC_F, TYPE_UDIMM,  WIDTH_16, RANKS_2, DPC_2, FREQ_1333, DENSITY_4, 0}}, 3, 0x80, 0x97, 0x33, 0x2, 0x04, 0x14},
  {{{VDD_135, ECC_F, TYPE_UDIMM,  WIDTH_8,  RANKS_1, DPC_1, FREQ_1600, DENSITY_2, 0}}, 4, 0x63, 0xAA, 0x74, 0x6, 0x0B, 0x0A},
  {{{VDD_135, ECC_F, TYPE_UDIMM,  WIDTH_8,  RANKS_2, DPC_1, FREQ_1600, DENSITY_2, 0}}, 4, 0x62, 0xA9, 0x73, 0x6, 0x09, 0x0D},
  {{{VDD_135, ECC_F, TYPE_UDIMM,  WIDTH_8,  RANKS_1, DPC_1, FREQ_1600, DENSITY_4, 0}}, 4, 0x6F, 0xB4, 0x77, 0x7, 0x0C, 0x0B},
  {{{VDD_135, ECC_F, TYPE_UDIMM,  WIDTH_8,  RANKS_2, DPC_1, FREQ_1600, DENSITY_4, 0}}, 4, 0x6D, 0xB2, 0x76, 0x7, 0x0B, 0x0F},
  {{{VDD_135, ECC_F, TYPE_UDIMM,  WIDTH_16, RANKS_1, DPC_1, FREQ_1600, DENSITY_2, 0}}, 4, 0x56, 0x96, 0x66, 0x3, 0x07, 0x08},
  {{{VDD_135, ECC_F, TYPE_UDIMM,  WIDTH_16, RANKS_2, DPC_1, FREQ_1600, DENSITY_2, 0}}, 4, 0x55, 0x95, 0x64, 0x3, 0x06, 0x0A},
  {{{VDD_135, ECC_F, TYPE_UDIMM,  WIDTH_16, RANKS_1, DPC_1, FREQ_1600, DENSITY_4, 0}}, 4, 0x5F, 0x9D, 0x69, 0x4, 0x08, 0x09},
  {{{VDD_135, ECC_F, TYPE_UDIMM,  WIDTH_16, RANKS_2, DPC_1, FREQ_1600, DENSITY_4, 0}}, 4, 0x5D, 0x9C, 0x68, 0x4, 0x07, 0x0B},
  {{{VDD_135, ECC_F, TYPE_UDIMM,  WIDTH_8,  RANKS_1, DPC_2, FREQ_1600, DENSITY_2, 0}}, 3, 0x73, 0x97, 0x3A, 0x3, 0x05, 0x13},
  {{{VDD_135, ECC_F, TYPE_UDIMM,  WIDTH_8,  RANKS_2, DPC_2, FREQ_1600, DENSITY_2, 0}}, 3, 0x73, 0x96, 0x3A, 0x3, 0x05, 0x1A},
  {{{VDD_135, ECC_F, TYPE_UDIMM,  WIDTH_8,  RANKS_1, DPC_2, FREQ_1600, DENSITY_4, 0}}, 3, 0x79, 0x9C, 0x3B, 0x4, 0x06, 0x15},
  {{{VDD_135, ECC_F, TYPE_UDIMM,  WIDTH_8,  RANKS_2, DPC_2, FREQ_1600, DENSITY_4, 0}}, 3, 0x78, 0x9B, 0x3B, 0x4, 0x05, 0x1B},
  {{{VDD_135, ECC_F, TYPE_UDIMM,  WIDTH_16, RANKS_1, DPC_2, FREQ_1600, DENSITY_2, 0}}, 3, 0x6D, 0x8D, 0x33, 0x2, 0x03, 0x0F},
  {{{VDD_135, ECC_F, TYPE_UDIMM,  WIDTH_16, RANKS_2, DPC_2, FREQ_1600, DENSITY_2, 0}}, 3, 0x6C, 0x8D, 0x32, 0x2, 0x03, 0x14},
  {{{VDD_135, ECC_F, TYPE_UDIMM,  WIDTH_16, RANKS_1, DPC_2, FREQ_1600, DENSITY_4, 0}}, 3, 0x71, 0x90, 0x34, 0x2, 0x04, 0x11},
  {{{VDD_135, ECC_F, TYPE_UDIMM,  WIDTH_16, RANKS_2, DPC_2, FREQ_1600, DENSITY_4, 0}}, 3, 0x70, 0x90, 0x34, 0x2, 0x03, 0x14},
  {{{VDD_135, ECC_F, TYPE_UDIMM,  WIDTH_8,  RANKS_1, DPC_1, FREQ_1867, DENSITY_2, 0}}, 4, 0x60, 0x9C, 0x7F, 0x5, 0x0A, 0x0B},
  {{{VDD_135, ECC_F, TYPE_UDIMM,  WIDTH_8,  RANKS_2, DPC_1, FREQ_1867, DENSITY_2, 0}}, 4, 0x5F, 0x9B, 0x7E, 0x5, 0x09, 0x0F},
  {{{VDD_135, ECC_F, TYPE_UDIMM,  WIDTH_8,  RANKS_1, DPC_1, FREQ_1867, DENSITY_4, 0}}, 4, 0x6B, 0xA6, 0x81, 0x7, 0x0B, 0x0C},
  {{{VDD_135, ECC_F, TYPE_UDIMM,  WIDTH_8,  RANKS_2, DPC_1, FREQ_1867, DENSITY_4, 0}}, 4, 0x6A, 0xA5, 0x80, 0x7, 0x0A, 0x10},
  {{{VDD_135, ECC_F, TYPE_UDIMM,  WIDTH_16, RANKS_1, DPC_1, FREQ_1867, DENSITY_2, 0}}, 4, 0x53, 0x89, 0x6A, 0x3, 0x06, 0x09},
  {{{VDD_135, ECC_F, TYPE_UDIMM,  WIDTH_16, RANKS_2, DPC_1, FREQ_1867, DENSITY_2, 0}}, 4, 0x52, 0x88, 0x69, 0x3, 0x05, 0x0B},
  {{{VDD_135, ECC_F, TYPE_UDIMM,  WIDTH_16, RANKS_1, DPC_1, FREQ_1867, DENSITY_4, 0}}, 4, 0x5B, 0x90, 0x6D, 0x4, 0x07, 0x0A},
  {{{VDD_135, ECC_F, TYPE_UDIMM,  WIDTH_16, RANKS_2, DPC_1, FREQ_1867, DENSITY_4, 0}}, 4, 0x5A, 0x8F, 0x6C, 0x4, 0x06, 0x0C},
  {{{VDD_135, ECC_F, TYPE_UDIMM,  WIDTH_8,  RANKS_1, DPC_2, FREQ_1867, DENSITY_2, 0}}, 3, 0x68, 0x87, 0x3F, 0x3, 0x05, 0x15},
  {{{VDD_135, ECC_F, TYPE_UDIMM,  WIDTH_8,  RANKS_2, DPC_2, FREQ_1867, DENSITY_2, 0}}, 3, 0x68, 0x86, 0x3F, 0x3, 0x04, 0x1A},
  {{{VDD_135, ECC_F, TYPE_UDIMM,  WIDTH_8,  RANKS_1, DPC_2, FREQ_1867, DENSITY_4, 0}}, 3, 0x6D, 0x8B, 0x40, 0x4, 0x05, 0x16},
  {{{VDD_135, ECC_F, TYPE_UDIMM,  WIDTH_8,  RANKS_2, DPC_2, FREQ_1867, DENSITY_4, 0}}, 3, 0x6D, 0x8B, 0x40, 0x4, 0x05, 0x1E},
  {{{VDD_135, ECC_F, TYPE_UDIMM,  WIDTH_16, RANKS_1, DPC_2, FREQ_1867, DENSITY_2, 0}}, 4, 0xC3, 0xF9, 0x6A, 0x3, 0x05, 0x10},
  {{{VDD_135, ECC_F, TYPE_UDIMM,  WIDTH_16, RANKS_2, DPC_2, FREQ_1867, DENSITY_2, 0}}, 4, 0xC2, 0xF9, 0x69, 0x3, 0x05, 0x14},
  {{{VDD_135, ECC_F, TYPE_UDIMM,  WIDTH_16, RANKS_1, DPC_2, FREQ_1867, DENSITY_4, 0}}, 3, 0x66, 0x80, 0x37, 0x2, 0x03, 0x11},
  {{{VDD_135, ECC_F, TYPE_UDIMM,  WIDTH_16, RANKS_2, DPC_2, FREQ_1867, DENSITY_4, 0}}, 4, 0xCA, 0xFF, 0x6C, 0x4, 0x06, 0x16},
  {{{VDD_135, ECC_F, TYPE_UDIMM,  WIDTH_8,  RANKS_1, DPC_1, FREQ_2133, DENSITY_2, 0}}, 4, 0x5D, 0x92, 0x86, 0x5, 0x09, 0x0C},
  {{{VDD_135, ECC_F, TYPE_UDIMM,  WIDTH_8,  RANKS_2, DPC_1, FREQ_2133, DENSITY_2, 0}}, 4, 0x5C, 0x91, 0x85, 0x5, 0x08, 0x10},
  {{{VDD_135, ECC_F, TYPE_UDIMM,  WIDTH_8,  RANKS_1, DPC_1, FREQ_2133, DENSITY_4, 0}}, 4, 0x68, 0x9B, 0x88, 0x6, 0x0B, 0x0E},
  {{{VDD_135, ECC_F, TYPE_UDIMM,  WIDTH_8,  RANKS_2, DPC_1, FREQ_2133, DENSITY_4, 0}}, 4, 0x67, 0x9A, 0x87, 0x6, 0x0A, 0x12},
  {{{VDD_135, ECC_F, TYPE_UDIMM,  WIDTH_16, RANKS_1, DPC_1, FREQ_2133, DENSITY_2, 0}}, 5, 0x9F, 0xFD, 0xDA, 0x5, 0x0B, 0x0A},
  {{{VDD_135, ECC_F, TYPE_UDIMM,  WIDTH_16, RANKS_2, DPC_1, FREQ_2133, DENSITY_2, 0}}, 5, 0x9D, 0xFB, 0xD8, 0x5, 0x09, 0x0B},
  {{{VDD_135, ECC_F, TYPE_UDIMM,  WIDTH_16, RANKS_1, DPC_1, FREQ_2133, DENSITY_4, 0}}, 4, 0x58, 0x85, 0x70, 0x4, 0x07, 0x0B},
  {{{VDD_135, ECC_F, TYPE_UDIMM,  WIDTH_16, RANKS_2, DPC_1, FREQ_2133, DENSITY_4, 0}}, 4, 0x57, 0x84, 0x6F, 0x4, 0x06, 0x0D},
  {{{VDD_135, ECC_F, TYPE_UDIMM,  WIDTH_8,  RANKS_1, DPC_2, FREQ_2133, DENSITY_2, 0}}, 4, 0xBF, 0xF4, 0x85, 0x5, 0x08, 0x15},
  {{{VDD_135, ECC_F, TYPE_UDIMM,  WIDTH_8,  RANKS_2, DPC_2, FREQ_2133, DENSITY_2, 0}}, 4, 0xBE, 0xF4, 0x85, 0x5, 0x08, 0x1D},
  {{{VDD_135, ECC_F, TYPE_UDIMM,  WIDTH_8,  RANKS_1, DPC_2, FREQ_2133, DENSITY_4, 0}}, 4, 0xCA, 0xFE, 0x87, 0x6, 0x0A, 0x18},
  {{{VDD_135, ECC_F, TYPE_UDIMM,  WIDTH_8,  RANKS_2, DPC_2, FREQ_2133, DENSITY_4, 0}}, 4, 0xC9, 0xFD, 0x87, 0x6, 0x09, 0x20},
  {{{VDD_135, ECC_F, TYPE_UDIMM,  WIDTH_16, RANKS_1, DPC_2, FREQ_2133, DENSITY_2, 0}}, 4, 0xB1, 0xE1, 0x6C, 0x3, 0x05, 0x11},
  {{{VDD_135, ECC_F, TYPE_UDIMM,  WIDTH_16, RANKS_2, DPC_2, FREQ_2133, DENSITY_2, 0}}, 4, 0xB1, 0xE1, 0x6C, 0x3, 0x05, 0x16},
  {{{VDD_135, ECC_F, TYPE_UDIMM,  WIDTH_16, RANKS_1, DPC_2, FREQ_2133, DENSITY_4, 0}}, 4, 0xB9, 0xE8, 0x6F, 0x4, 0x06, 0x13},
  {{{VDD_135, ECC_F, TYPE_UDIMM,  WIDTH_16, RANKS_2, DPC_2, FREQ_2133, DENSITY_4, 0}}, 4, 0xB9, 0xE7, 0x6F, 0x4, 0x05, 0x17},
  {{{VDD_135, ECC_T, TYPE_UDIMM,  WIDTH_8,  RANKS_1, DPC_1, FREQ_1067, DENSITY_2, 0}}, 4, 0x6E, 0xB7, 0x76, 0x8, 0x0E, 0x06},
  {{{VDD_135, ECC_T, TYPE_UDIMM,  WIDTH_8,  RANKS_2, DPC_1, FREQ_1067, DENSITY_2, 0}}, 4, 0x6C, 0xB5, 0x74, 0x8, 0x0C, 0x09},
  {{{VDD_135, ECC_T, TYPE_UDIMM,  WIDTH_8,  RANKS_1, DPC_1, FREQ_1067, DENSITY_4, 0}}, 4, 0x7B, 0xC2, 0x79, 0xA, 0x11, 0x07},
  {{{VDD_135, ECC_T, TYPE_UDIMM,  WIDTH_8,  RANKS_2, DPC_1, FREQ_1067, DENSITY_4, 0}}, 4, 0x79, 0xC0, 0x77, 0xA, 0x0F, 0x0A},
  {{{VDD_135, ECC_T, TYPE_UDIMM,  WIDTH_16, RANKS_1, DPC_1, FREQ_1067, DENSITY_2, 0}}, 4, 0x68, 0xA7, 0x7D, 0x5, 0x0A, 0x05},
  {{{VDD_135, ECC_T, TYPE_UDIMM,  WIDTH_16, RANKS_2, DPC_1, FREQ_1067, DENSITY_2, 0}}, 4, 0x66, 0xA5, 0x7B, 0x5, 0x08, 0x07},
  {{{VDD_135, ECC_T, TYPE_UDIMM,  WIDTH_16, RANKS_1, DPC_1, FREQ_1067, DENSITY_4, 0}}, 4, 0x73, 0xB0, 0x81, 0x6, 0x0C, 0x06},
  {{{VDD_135, ECC_T, TYPE_UDIMM,  WIDTH_16, RANKS_2, DPC_1, FREQ_1067, DENSITY_4, 0}}, 4, 0x71, 0xAF, 0x7F, 0x6, 0x0A, 0x08},
  {{{VDD_135, ECC_T, TYPE_UDIMM,  WIDTH_8,  RANKS_1, DPC_2, FREQ_1067, DENSITY_2, 0}}, 3, 0xC0, 0xE3, 0x3A, 0x4, 0x07, 0x0D},
  {{{VDD_135, ECC_T, TYPE_UDIMM,  WIDTH_8,  RANKS_2, DPC_2, FREQ_1067, DENSITY_2, 0}}, 3, 0xBF, 0xE2, 0x3A, 0x4, 0x06, 0x12},
  {{{VDD_135, ECC_T, TYPE_UDIMM,  WIDTH_8,  RANKS_1, DPC_2, FREQ_1067, DENSITY_4, 0}}, 3, 0xC6, 0xE8, 0x3C, 0x5, 0x08, 0x0E},
  {{{VDD_135, ECC_T, TYPE_UDIMM,  WIDTH_8,  RANKS_2, DPC_2, FREQ_1067, DENSITY_4, 0}}, 3, 0xC6, 0xE8, 0x3B, 0x5, 0x07, 0x14},
  {{{VDD_135, ECC_T, TYPE_UDIMM,  WIDTH_16, RANKS_1, DPC_2, FREQ_1067, DENSITY_2, 0}}, 3, 0xBD, 0xDB, 0x3E, 0x3, 0x04, 0x0A},
  {{{VDD_135, ECC_T, TYPE_UDIMM,  WIDTH_16, RANKS_2, DPC_2, FREQ_1067, DENSITY_2, 0}}, 3, 0xBC, 0xDA, 0x3D, 0x3, 0x04, 0x0E},
  {{{VDD_135, ECC_T, TYPE_UDIMM,  WIDTH_16, RANKS_1, DPC_2, FREQ_1067, DENSITY_4, 0}}, 3, 0xC2, 0xDF, 0x40, 0x3, 0x05, 0x0B},
  {{{VDD_135, ECC_T, TYPE_UDIMM,  WIDTH_16, RANKS_2, DPC_2, FREQ_1067, DENSITY_4, 0}}, 3, 0xC2, 0xDF, 0x40, 0x3, 0x05, 0x10},
  {{{VDD_135, ECC_T, TYPE_UDIMM,  WIDTH_8,  RANKS_1, DPC_1, FREQ_1333, DENSITY_2, 0}}, 4, 0x68, 0xA2, 0x7B, 0x7, 0x0D, 0x07},
  {{{VDD_135, ECC_T, TYPE_UDIMM,  WIDTH_8,  RANKS_2, DPC_1, FREQ_1333, DENSITY_2, 0}}, 4, 0x66, 0xA1, 0x7A, 0x7, 0x0B, 0x0A},
  {{{VDD_135, ECC_T, TYPE_UDIMM,  WIDTH_8,  RANKS_1, DPC_1, FREQ_1333, DENSITY_4, 0}}, 4, 0x75, 0xAE, 0x7E, 0x9, 0x0F, 0x08},
  {{{VDD_135, ECC_T, TYPE_UDIMM,  WIDTH_8,  RANKS_2, DPC_1, FREQ_1333, DENSITY_4, 0}}, 4, 0x73, 0xAC, 0x7D, 0x9, 0x0D, 0x0C},
  {{{VDD_135, ECC_T, TYPE_UDIMM,  WIDTH_16, RANKS_1, DPC_1, FREQ_1333, DENSITY_2, 0}}, 4, 0x62, 0x93, 0x7D, 0x4, 0x09, 0x06},
  {{{VDD_135, ECC_T, TYPE_UDIMM,  WIDTH_16, RANKS_2, DPC_1, FREQ_1333, DENSITY_2, 0}}, 4, 0x61, 0x92, 0x7B, 0x4, 0x07, 0x08},
  {{{VDD_135, ECC_T, TYPE_UDIMM,  WIDTH_16, RANKS_1, DPC_1, FREQ_1333, DENSITY_4, 0}}, 4, 0x6D, 0x9C, 0x81, 0x5, 0x0A, 0x07},
  {{{VDD_135, ECC_T, TYPE_UDIMM,  WIDTH_16, RANKS_2, DPC_1, FREQ_1333, DENSITY_4, 0}}, 4, 0x6B, 0x9A, 0x7F, 0x5, 0x08, 0x09},
  {{{VDD_135, ECC_T, TYPE_UDIMM,  WIDTH_8,  RANKS_1, DPC_2, FREQ_1333, DENSITY_2, 0}}, 3, 0xD3, 0xED, 0x3D, 0x4, 0x06, 0x0F},
  {{{VDD_135, ECC_T, TYPE_UDIMM,  WIDTH_8,  RANKS_2, DPC_2, FREQ_1333, DENSITY_2, 0}}, 3, 0xD3, 0xEC, 0x3D, 0x4, 0x05, 0x14},
  {{{VDD_135, ECC_T, TYPE_UDIMM,  WIDTH_8,  RANKS_1, DPC_2, FREQ_1333, DENSITY_4, 0}}, 3, 0xDA, 0xF2, 0x3F, 0x5, 0x07, 0x10},
  {{{VDD_135, ECC_T, TYPE_UDIMM,  WIDTH_8,  RANKS_2, DPC_2, FREQ_1333, DENSITY_4, 0}}, 3, 0xD9, 0xF2, 0x3E, 0x5, 0x07, 0x19},
  {{{VDD_135, ECC_T, TYPE_UDIMM,  WIDTH_16, RANKS_1, DPC_2, FREQ_1333, DENSITY_2, 0}}, 3, 0xD0, 0xE5, 0x3E, 0x2, 0x04, 0x0D},
  {{{VDD_135, ECC_T, TYPE_UDIMM,  WIDTH_16, RANKS_2, DPC_2, FREQ_1333, DENSITY_2, 0}}, 3, 0xD0, 0xE5, 0x3D, 0x2, 0x04, 0x11},
  {{{VDD_135, ECC_T, TYPE_UDIMM,  WIDTH_16, RANKS_1, DPC_2, FREQ_1333, DENSITY_4, 0}}, 3, 0xD6, 0xE9, 0x40, 0x3, 0x05, 0x0E},
  {{{VDD_135, ECC_T, TYPE_UDIMM,  WIDTH_16, RANKS_2, DPC_2, FREQ_1333, DENSITY_4, 0}}, 3, 0xD5, 0xE9, 0x40, 0x3, 0x04, 0x12},
  {{{VDD_135, ECC_T, TYPE_UDIMM,  WIDTH_8,  RANKS_1, DPC_1, FREQ_1600, DENSITY_2, 0}}, 4, 0x64, 0x95, 0x83, 0x6, 0x0B, 0x08},
  {{{VDD_135, ECC_T, TYPE_UDIMM,  WIDTH_8,  RANKS_2, DPC_1, FREQ_1600, DENSITY_2, 0}}, 4, 0x63, 0x94, 0x81, 0x6, 0x0A, 0x0B},
  {{{VDD_135, ECC_T, TYPE_UDIMM,  WIDTH_8,  RANKS_1, DPC_1, FREQ_1600, DENSITY_4, 0}}, 4, 0x71, 0xA0, 0x85, 0x8, 0x0D, 0x09},
  {{{VDD_135, ECC_T, TYPE_UDIMM,  WIDTH_8,  RANKS_2, DPC_1, FREQ_1600, DENSITY_4, 0}}, 4, 0x70, 0x9F, 0x84, 0x8, 0x0C, 0x0D},
  {{{VDD_135, ECC_T, TYPE_UDIMM,  WIDTH_16, RANKS_1, DPC_1, FREQ_1600, DENSITY_2, 0}}, 4, 0x5D, 0x86, 0x7E, 0x4, 0x08, 0x07},
  {{{VDD_135, ECC_T, TYPE_UDIMM,  WIDTH_16, RANKS_2, DPC_1, FREQ_1600, DENSITY_2, 0}}, 4, 0x5C, 0x85, 0x7D, 0x4, 0x07, 0x09},
  {{{VDD_135, ECC_T, TYPE_UDIMM,  WIDTH_16, RANKS_1, DPC_1, FREQ_1600, DENSITY_4, 0}}, 4, 0x68, 0x8F, 0x82, 0x5, 0x09, 0x07},
  {{{VDD_135, ECC_T, TYPE_UDIMM,  WIDTH_16, RANKS_2, DPC_1, FREQ_1600, DENSITY_4, 0}}, 4, 0x66, 0x8D, 0x81, 0x5, 0x08, 0x0A},
  {{{VDD_135, ECC_T, TYPE_UDIMM,  WIDTH_8,  RANKS_1, DPC_2, FREQ_1600, DENSITY_2, 0}}, 3, 0xB7, 0xCC, 0x41, 0x3, 0x05, 0x10},
  {{{VDD_135, ECC_T, TYPE_UDIMM,  WIDTH_8,  RANKS_2, DPC_2, FREQ_1600, DENSITY_2, 0}}, 3, 0xB7, 0xCC, 0x41, 0x3, 0x05, 0x17},
  {{{VDD_135, ECC_T, TYPE_UDIMM,  WIDTH_8,  RANKS_1, DPC_2, FREQ_1600, DENSITY_4, 0}}, 3, 0xBD, 0xD2, 0x42, 0x4, 0x06, 0x11},
  {{{VDD_135, ECC_T, TYPE_UDIMM,  WIDTH_8,  RANKS_2, DPC_2, FREQ_1600, DENSITY_4, 0}}, 3, 0xBD, 0xD1, 0x42, 0x4, 0x06, 0x1A},
  {{{VDD_135, ECC_T, TYPE_UDIMM,  WIDTH_16, RANKS_1, DPC_2, FREQ_1600, DENSITY_2, 0}}, 3, 0xB3, 0xC5, 0x3F, 0x2, 0x04, 0x0E},
  {{{VDD_135, ECC_T, TYPE_UDIMM,  WIDTH_16, RANKS_2, DPC_2, FREQ_1600, DENSITY_2, 0}}, 3, 0xB3, 0xC4, 0x3F, 0x2, 0x03, 0x11},
  {{{VDD_135, ECC_T, TYPE_UDIMM,  WIDTH_16, RANKS_1, DPC_2, FREQ_1600, DENSITY_4, 0}}, 3, 0xB9, 0xC9, 0x41, 0x3, 0x04, 0x0E},
  {{{VDD_135, ECC_T, TYPE_UDIMM,  WIDTH_16, RANKS_2, DPC_2, FREQ_1600, DENSITY_4, 0}}, 3, 0xB8, 0xC9, 0x41, 0x3, 0x04, 0x14},
  {{{VDD_135, ECC_T, TYPE_UDIMM,  WIDTH_8,  RANKS_1, DPC_1, FREQ_1867, DENSITY_2, 0}}, 4, 0x62, 0x8C, 0x8E, 0x6, 0x0B, 0x0A},
  {{{VDD_135, ECC_T, TYPE_UDIMM,  WIDTH_8,  RANKS_2, DPC_1, FREQ_1867, DENSITY_2, 0}}, 4, 0x61, 0x8A, 0x8D, 0x6, 0x0A, 0x0D},
  {{{VDD_135, ECC_T, TYPE_UDIMM,  WIDTH_8,  RANKS_1, DPC_1, FREQ_1867, DENSITY_4, 0}}, 4, 0x6E, 0x96, 0x90, 0x8, 0x0C, 0x0A},
  {{{VDD_135, ECC_T, TYPE_UDIMM,  WIDTH_8,  RANKS_2, DPC_1, FREQ_1867, DENSITY_4, 0}}, 4, 0x6D, 0x95, 0x8F, 0x8, 0x0B, 0x0F},
  {{{VDD_135, ECC_T, TYPE_UDIMM,  WIDTH_16, RANKS_1, DPC_1, FREQ_1867, DENSITY_2, 0}}, 4, 0x5B, 0x7D, 0x84, 0x4, 0x07, 0x08},
  {{{VDD_135, ECC_T, TYPE_UDIMM,  WIDTH_16, RANKS_2, DPC_1, FREQ_1867, DENSITY_2, 0}}, 4, 0x5A, 0x7C, 0x83, 0x4, 0x06, 0x0A},
  {{{VDD_135, ECC_T, TYPE_UDIMM,  WIDTH_16, RANKS_1, DPC_1, FREQ_1867, DENSITY_4, 0}}, 4, 0x65, 0x85, 0x88, 0x5, 0x08, 0x08},
  {{{VDD_135, ECC_T, TYPE_UDIMM,  WIDTH_16, RANKS_2, DPC_1, FREQ_1867, DENSITY_4, 0}}, 4, 0x64, 0x84, 0x87, 0x5, 0x07, 0x0B},
  {{{VDD_135, ECC_T, TYPE_UDIMM,  WIDTH_8,  RANKS_1, DPC_2, FREQ_1867, DENSITY_2, 0}}, 3, 0xA3, 0xB5, 0x47, 0x3, 0x05, 0x12},
  {{{VDD_135, ECC_T, TYPE_UDIMM,  WIDTH_8,  RANKS_2, DPC_2, FREQ_1867, DENSITY_2, 0}}, 3, 0xA2, 0xB5, 0x47, 0x3, 0x05, 0x1A},
  {{{VDD_135, ECC_T, TYPE_UDIMM,  WIDTH_8,  RANKS_1, DPC_2, FREQ_1867, DENSITY_4, 0}}, 3, 0xA9, 0xBA, 0x48, 0x4, 0x06, 0x14},
  {{{VDD_135, ECC_T, TYPE_UDIMM,  WIDTH_8,  RANKS_2, DPC_2, FREQ_1867, DENSITY_4, 0}}, 3, 0xA9, 0xBA, 0x48, 0x4, 0x06, 0x1E},
  {{{VDD_135, ECC_T, TYPE_UDIMM,  WIDTH_16, RANKS_1, DPC_2, FREQ_1867, DENSITY_2, 0}}, 3, 0x9F, 0xAE, 0x42, 0x2, 0x03, 0x0E},
  {{{VDD_135, ECC_T, TYPE_UDIMM,  WIDTH_16, RANKS_2, DPC_2, FREQ_1867, DENSITY_2, 0}}, 3, 0x9F, 0xAD, 0x42, 0x2, 0x03, 0x13},
  {{{VDD_135, ECC_T, TYPE_UDIMM,  WIDTH_16, RANKS_1, DPC_2, FREQ_1867, DENSITY_4, 0}}, 3, 0xA4, 0xB2, 0x44, 0x3, 0x04, 0x10},
  {{{VDD_135, ECC_T, TYPE_UDIMM,  WIDTH_16, RANKS_2, DPC_2, FREQ_1867, DENSITY_4, 0}}, 3, 0xA4, 0xB2, 0x44, 0x3, 0x04, 0x17},
  {{{VDD_135, ECC_T, TYPE_UDIMM,  WIDTH_8,  RANKS_1, DPC_1, FREQ_2133, DENSITY_2, 0}}, 4, 0x60, 0x85, 0x97, 0x6, 0x0A, 0x0B},
  {{{VDD_135, ECC_T, TYPE_UDIMM,  WIDTH_8,  RANKS_2, DPC_1, FREQ_2133, DENSITY_2, 0}}, 4, 0x5F, 0x84, 0x96, 0x6, 0x09, 0x0E},
  {{{VDD_135, ECC_T, TYPE_UDIMM,  WIDTH_8,  RANKS_1, DPC_1, FREQ_2133, DENSITY_4, 0}}, 4, 0x6C, 0x8F, 0x99, 0x7, 0x0C, 0x0C},
  {{{VDD_135, ECC_T, TYPE_UDIMM,  WIDTH_8,  RANKS_2, DPC_1, FREQ_2133, DENSITY_4, 0}}, 4, 0x6B, 0x8E, 0x98, 0x7, 0x0B, 0x11},
  {{{VDD_135, ECC_T, TYPE_UDIMM,  WIDTH_16, RANKS_1, DPC_1, FREQ_2133, DENSITY_2, 0}}, 4, 0x58, 0x76, 0x88, 0x3, 0x07, 0x09},
  {{{VDD_135, ECC_T, TYPE_UDIMM,  WIDTH_16, RANKS_2, DPC_1, FREQ_2133, DENSITY_2, 0}}, 4, 0x57, 0x75, 0x87, 0x3, 0x06, 0x0B},
  {{{VDD_135, ECC_T, TYPE_UDIMM,  WIDTH_16, RANKS_1, DPC_1, FREQ_2133, DENSITY_4, 0}}, 4, 0x62, 0x7E, 0x8B, 0x4, 0x08, 0x09},
  {{{VDD_135, ECC_T, TYPE_UDIMM,  WIDTH_16, RANKS_2, DPC_1, FREQ_2133, DENSITY_4, 0}}, 4, 0x61, 0x7D, 0x8A, 0x4, 0x07, 0x0C},
  {{{VDD_135, ECC_T, TYPE_UDIMM,  WIDTH_8,  RANKS_1, DPC_2, FREQ_2133, DENSITY_2, 0}}, 3, 0x94, 0xA4, 0x4B, 0x3, 0x05, 0x14},
  {{{VDD_135, ECC_T, TYPE_UDIMM,  WIDTH_8,  RANKS_2, DPC_2, FREQ_2133, DENSITY_2, 0}}, 3, 0x93, 0xA3, 0x4B, 0x3, 0x05, 0x1E},
  {{{VDD_135, ECC_T, TYPE_UDIMM,  WIDTH_8,  RANKS_1, DPC_2, FREQ_2133, DENSITY_4, 0}}, 3, 0x9A, 0xA9, 0x4C, 0x4, 0x06, 0x16},
  {{{VDD_135, ECC_T, TYPE_UDIMM,  WIDTH_8,  RANKS_2, DPC_2, FREQ_2133, DENSITY_4, 0}}, 3, 0x99, 0xA8, 0x4C, 0x4, 0x05, 0x1E},
  {{{VDD_135, ECC_T, TYPE_UDIMM,  WIDTH_16, RANKS_1, DPC_2, FREQ_2133, DENSITY_2, 0}}, 3, 0x90, 0x9C, 0x44, 0x2, 0x03, 0x0F},
  {{{VDD_135, ECC_T, TYPE_UDIMM,  WIDTH_16, RANKS_2, DPC_2, FREQ_2133, DENSITY_2, 0}}, 3, 0x8F, 0x9C, 0x43, 0x2, 0x03, 0x15},
  {{{VDD_135, ECC_T, TYPE_UDIMM,  WIDTH_16, RANKS_1, DPC_2, FREQ_2133, DENSITY_4, 0}}, 3, 0x95, 0xA0, 0x45, 0x2, 0x04, 0x11},
  {{{VDD_135, ECC_T, TYPE_UDIMM,  WIDTH_16, RANKS_2, DPC_2, FREQ_2133, DENSITY_4, 0}}, 3, 0x95, 0xA0, 0x45, 0x2, 0x03, 0x16}
};
GLOBAL_REMOVE_IF_UNREFERENCED const DdrPowerWeightEntry Ddr3PowerWeightTable1[] = {
  {{{VDD_135, ECC_F, TYPE_SODIMM, 0       , 0      , 0    , 0        , 0        , 0}}, 3, 0x87, 0xAB, 0x44, 0x5, 0x08, 0x22},
  {{{VDD_135, ECC_F, TYPE_UDIMM,  0       , 0      , 0    , 0        , 0        , 0}}, 3, 0x9F, 0xC1, 0x44, 0x5, 0x08, 0x20},
  {{{VDD_135, ECC_T, TYPE_UDIMM,  0       , 0      , 0    , 0        , 0        , 0}}, 3, 0xDA, 0xF2, 0x4D, 0x5, 0x09, 0x1E}
};
GLOBAL_REMOVE_IF_UNREFERENCED const DdrPowerWeightEntry Ddr3PowerWeightTable2[] = {
  {{{0      , 0    , 0          , 0       , 0      , 0    , 0        , 0        , 0}}, 2, 0x98, 0xA3, 0x73, 0x5, 0x09, 0x34}
};

GLOBAL_REMOVE_IF_UNREFERENCED const Lpddr3PowerWeightEntry Lpddr3PowerWeightTable1[] = {
  {{{VDD_120, 0    , 0          , WIDTH_32, RANKS_2, 0    , FREQ_1333, DENSITY_4, 0}}, 5, 0xA9, 0x84, 0xEE, 0x2, 0x04, 0x06, 0x3},
  {{{VDD_120, 0    , 0          , WIDTH_32, RANKS_1, 0    , FREQ_1333, DENSITY_4, 0}}, 5, 0x91, 0x4C, 0xEE, 0x2, 0x04, 0x05, 0x3},
  {{{VDD_120, 0    , 0          , WIDTH_32, RANKS_2, 0    , FREQ_1600, DENSITY_4, 0}}, 5, 0xA3, 0x79, 0xE9, 0x2, 0x03, 0x07, 0x4},
  {{{VDD_120, 0    , 0          , WIDTH_32, RANKS_1, 0    , FREQ_1600, DENSITY_4, 0}}, 5, 0x8B, 0x4A, 0xE9, 0x2, 0x03, 0x06, 0x3},
  {{{VDD_120, 0    , 0          , WIDTH_16, RANKS_2, 0    , FREQ_1333, DENSITY_4, 0}}, 4, 0x6B, 0x56, 0xE0, 0x2, 0x03, 0x09, 0x5},
  {{{VDD_120, 0    , 0          , WIDTH_16, RANKS_1, 0    , FREQ_1333, DENSITY_4, 0}}, 4, 0x5F, 0x3D, 0xE0, 0x2, 0x03, 0x08, 0x4},
  {{{VDD_120, 0    , 0          , WIDTH_16, RANKS_2, 0    , FREQ_1600, DENSITY_4, 0}}, 4, 0x67, 0x4F, 0xDB, 0x2, 0x03, 0x0A, 0x6},
  {{{VDD_120, 0    , 0          , WIDTH_16, RANKS_1, 0    , FREQ_1600, DENSITY_4, 0}}, 4, 0x5B, 0x38, 0xDB, 0x2, 0x03, 0x09, 0x5}
};
GLOBAL_REMOVE_IF_UNREFERENCED const Lpddr3PowerWeightEntry Lpddr3PowerWeightTable2[] = {
  {{{0      , 0    , 0          , 0       , 0      , 0    , 0        , 0        , 0}}, 4, 0x6B, 0x56, 0xE0, 0x2, 0x03, 0x0A, 0x6}
};

GLOBAL_REMOVE_IF_UNREFERENCED const DdrPowerWeightEntry Ddr4PowerWeightTable2[] = {
  {{{0      , 0    , 0          , 0       , 0      , 0    , 0        , 0        , 0}}, 5, 0xC8, 0x96, 0x8F, 0x7, 0x0B, 0x00}
};

/**
  This function configure the MC power register post training after normal mode before PCU start working.

  @param[in, out] MrcData - Include all MRC global data.

  @retval Nothing.
**/
void
MrcPowerModesPostTraining (
  IN OUT MrcParameters *const MrcData
  )
{
  //
  // Configure Power Down CR
  //
  MrcPowerDownConfig (MrcData);
}

/**
  This function configures the power down control register.

  @param[in]  - MrcData - The MRC global data.

  @retval - Nothing
**/
void
MrcPowerDownConfig (
  IN MrcParameters *const MrcData
  )
{
  const MrcInput  *Inputs;
  MrcOutput       *Outputs;
  BOOLEAN         UlxUlt;
  MCSCHEDS_CR_PM_PDWN_CONFIG_STRUCT PmPdwnConfig;

  Inputs    = &MrcData->Inputs;
  Outputs   = &MrcData->Outputs;
  UlxUlt    = ((Inputs->CpuModel == cmSKL_ULX_ULT) || (Inputs->CpuModel == cmKBL_ULX_ULT));

  PmPdwnConfig.Data                   = 0;
  PmPdwnConfig.Bits.PDWN_idle_counter = (UlxUlt) ? PDWN_IDLE_COUNTER_ULX_ULT : PDWN_IDLE_COUNTER_DT_HALO;

  if (Inputs->PwdwnIdleCounter != 0) {  // 0 means AUTO
    PmPdwnConfig.Bits.PDWN_idle_counter = Inputs->PwdwnIdleCounter;
  }

  switch (Inputs->PowerDownMode) {
    case pdmNoPowerDown:
      break;

    case pdmAPD:
      PmPdwnConfig.Bits.APD = 1;
      break;

    case pdmPPDDLLOFF:
      PmPdwnConfig.Bits.PPD = 1;
      PmPdwnConfig.Bits.Slow_Exit = 1;
      break;

    case pdmAuto:
      PmPdwnConfig.Bits.PPD = 1;
      if ((Outputs->DdrType != MRC_DDR_TYPE_LPDDR3) && (UlxUlt)) {
        //
        // Slow Exit (DLL Off) on ULX/ULT
        // Fast Exit on DT/Halo
        // @todo: might need Slow Exit on Halo (BGA) as well
        //
        PmPdwnConfig.Bits.Slow_Exit = 1;
      }
      break;
  }

  MrcWriteCR (MrcData, MCSCHEDS_CR_PM_PDWN_CONFIG_REG, PmPdwnConfig.Data);

  return;
}

/**
  This functions sets power weight, scale factor and Channel
  Power Floor values from lookup table based on DIMMs present in
  the system.

  @param[in] MrcData - Include all MRC global data.

  @retval MrcStatus - mrcSuccess or reason for failure.
**/
MrcStatus
MrcPowerWeight (
  IN     MrcParameters *const MrcData
  )
{
  const MrcInput               *Inputs;
  const MrcControllerIn        *ControllerIn;
  const MrcChannelIn           *ChannelIn;
  const MrcDimmIn              *DimmIn;
  const MrcSpd                 *Spd;
  MrcDebug                     *Debug;
  const MRC_FUNCTION           *MrcCall;
  MrcOutput                    *Outputs;
  MrcControllerOut             *ControllerOut;
  MrcChannelOut                *ChannelOut;
  MrcDimmOut                   *DimmOut;
  UINT8                        Channel;
  UINT8                        Dimm;
  const DdrPowerWeightEntry    *DdrPwt[3];
  const Lpddr3PowerWeightEntry *Lpddr3Pwt[3];
  UINT8                        PwtSetPtr;
  UINT16                       PwtSize[3];
  PowerWeightInputs            DimmPwt;
  UINT8                        i;
  UINT16                       j;
  BOOLEAN                      DimmEntryFound;
  BOOLEAN                      Lpddr3;
  BOOLEAN                      Ddr3;
  BOOLEAN                      Ddr4;
  UINT8                        SfDiff;
  UINT8                        MinScaleFactor;
  UINT8                        ScaleFactor[MAX_CHANNEL][MAX_DIMMS_IN_CHANNEL];
  UINT8                        ChPwrFloor[MAX_CHANNEL][MAX_DIMMS_IN_CHANNEL];
  UINT32                       Offset;
  MCHBAR_CH0_CR_PM_DIMM_RD_ENERGY_STRUCT         PmDimmRdEnergy[MAX_CHANNEL];
  MCHBAR_CH0_CR_PM_DIMM_WR_ENERGY_STRUCT         PmDimmWrEnergy[MAX_CHANNEL];
  MCHBAR_CH0_CR_PM_DIMM_ACT_ENERGY_STRUCT        PmDimmActEnergy[MAX_CHANNEL];
  MCHBAR_CH0_CR_PM_DIMM_PD_ENERGY_STRUCT         PmDimmPdEnergy[MAX_CHANNEL];
  MCHBAR_CH0_CR_PM_DIMM_IDLE_ENERGY_STRUCT       PmDimmIdleEnergy[MAX_CHANNEL];
  PCU_CR_DDR_RAPL_CHANNEL_POWER_FLOOR_PCU_STRUCT DdrRaplChannelPowerFloor;

  Inputs                        = &MrcData->Inputs;
  MrcCall                       = Inputs->Call.Func;
  Outputs                       = &MrcData->Outputs;
  Debug                         = &Outputs->Debug;
  ControllerIn                  = &Inputs->Controller[0];
  ControllerOut                 = &Outputs->Controller[0];
  MinScaleFactor                = (UINT8) ~0;
  DdrRaplChannelPowerFloor.Data = 0;

  Lpddr3 = (Outputs->DdrType == MRC_DDR_TYPE_LPDDR3);
  Ddr3   = (Outputs->DdrType == MRC_DDR_TYPE_DDR3);
  Ddr4   = (Outputs->DdrType == MRC_DDR_TYPE_DDR4);

  MrcCall->MrcSetMem ((UINT8 *) PmDimmRdEnergy, sizeof (PmDimmRdEnergy), 0);
  MrcCall->MrcSetMem ((UINT8 *) PmDimmWrEnergy, sizeof (PmDimmWrEnergy), 0);
  MrcCall->MrcSetMem ((UINT8 *) PmDimmActEnergy, sizeof (PmDimmActEnergy), 0);
  MrcCall->MrcSetMem ((UINT8 *) PmDimmPdEnergy, sizeof (PmDimmPdEnergy), 0);
  MrcCall->MrcSetMem ((UINT8 *) PmDimmIdleEnergy, sizeof (PmDimmIdleEnergy), 0);
  MrcCall->MrcSetMem ((UINT8 *) ScaleFactor, sizeof (ScaleFactor), 0xFF);
  MrcCall->MrcSetMem ((UINT8 *) ChPwrFloor, sizeof (ChPwrFloor), 0);

  if (Ddr3) {
    DdrPwt[0]    = Ddr3PowerWeightTable0;
    DdrPwt[1]    = Ddr3PowerWeightTable1;
    DdrPwt[2]    = Ddr3PowerWeightTable2;
    PwtSize[0]   = ARRAY_COUNT (Ddr3PowerWeightTable0);
    PwtSize[1]   = ARRAY_COUNT (Ddr3PowerWeightTable1);
    PwtSize[2]   = ARRAY_COUNT (Ddr3PowerWeightTable2);
    PwtSetPtr    = 0;
  } else if (Lpddr3) {
    Lpddr3Pwt[0] = NULL;
    Lpddr3Pwt[1] = Lpddr3PowerWeightTable1;
    Lpddr3Pwt[2] = Lpddr3PowerWeightTable2;
    PwtSize[1]   = ARRAY_COUNT (Lpddr3PowerWeightTable1);
    PwtSize[2]   = ARRAY_COUNT (Lpddr3PowerWeightTable2);
    PwtSetPtr    = 1;
  } else { // Ddr4
    DdrPwt[0]    = NULL;
    DdrPwt[1]    = NULL;
    DdrPwt[2]    = Ddr4PowerWeightTable2;
    PwtSize[2]   = ARRAY_COUNT (Ddr4PowerWeightTable2);
    PwtSetPtr    = 2;
  }

  if (Inputs->MemoryProfile != USER_PROFILE) {
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      if (!MrcChannelExist (Outputs, Channel)) {
        continue;
      }
      ChannelIn  = &ControllerIn->Channel[Channel];
      ChannelOut = &ControllerOut->Channel[Channel];
      //
      // Collect Channel level data for lookup
      //
      for (Dimm = 0; Dimm < MAX_DIMMS_IN_CHANNEL; Dimm++) {
        DimmIn  = &ChannelIn->Dimm[Dimm];
        DimmOut = &ChannelOut->Dimm[Dimm];
        if (DimmOut->Status != DIMM_PRESENT) {
          continue;
        }

        DimmPwt.Data = 0;
        //
        // Collect DIMM level data for lookup
        //

        Spd = &DimmIn->Spd.Data;

        switch (Outputs->VddVoltage[Inputs->MemoryProfile]) {
          case VDD_1_20:
            DimmPwt.Bits.Vddq = VDD_120;
            break;

          case VDD_1_35:
            DimmPwt.Bits.Vddq = VDD_135;
            break;

          case VDD_1_50:
            DimmPwt.Bits.Vddq = VDD_150;
            break;

          default:
            DimmPwt.Bits.Vddq = VDD_OTHER;
            PwtSetPtr = MAX (2, PwtSetPtr);
            break;
        }

        DimmPwt.Bits.Ecc         = DimmOut->EccSupport;
        DimmPwt.Bits.DimmType    = DimmOut->ModuleType;
        if ((DimmOut->ModuleType == SoUDimmEccMemoryPackageDdr3) ||
            (DimmOut->ModuleType == SoUDimmEccMemoryPackageDdr4)) {
          DimmPwt.Bits.DimmType = SoDimmMemoryPackage;  // The table checks for UDIMM vs. SO-DIMM, so treat ECC SO-DIMM as SO-DIMM
        }
        DimmPwt.Bits.DeviceWidth = DimmOut->SdramWidthIndex;
        DimmPwt.Bits.NumOfRanks  = DimmOut->RankInDimm;
        DimmPwt.Bits.Dpc         = ChannelOut->DimmCount;

        switch (Outputs->Frequency) {
          case f1067:
            DimmPwt.Bits.Frequency = FREQ_1067;
            break;

          case f1333:
            DimmPwt.Bits.Frequency = FREQ_1333;
            break;

          case f1600:
            DimmPwt.Bits.Frequency = FREQ_1600;
            break;

          case f1867:
            DimmPwt.Bits.Frequency = FREQ_1867;
            break;

          case f2133:
            DimmPwt.Bits.Frequency = FREQ_2133;
            break;

          default:
            PwtSetPtr = (Ddr3) ? MAX (1, PwtSetPtr) : MAX (2, PwtSetPtr);
            break;
        }

        DimmPwt.Bits.DramDensity = DimmOut->DensityIndex;

        //
        // Search lookup table for DIMM entry
        //
        DimmEntryFound = FALSE;

        for (i = PwtSetPtr; i < 3; i++) {
          if (DimmEntryFound) {
            break;
          }
          if (i == 1) {
            DimmPwt.Bits.Dpc         = 0;
            if (Ddr3) {
              DimmPwt.Bits.DeviceWidth = 0;
              DimmPwt.Bits.NumOfRanks  = 0;
              DimmPwt.Bits.Frequency   = 0;
              DimmPwt.Bits.DramDensity = 0;
            } else if (Lpddr3) {
              DimmPwt.Bits.Ecc      = 0;
              DimmPwt.Bits.DimmType = 0;
            }
          } else if (i == 2) {
            DimmPwt.Data = 0;
          }
          for (j = 0; j < PwtSize[i]; j++) {
            if (Ddr3 || Ddr4) {
              if (DimmPwt.Data == DdrPwt[i][j].PwInput.Data) {
                PmDimmRdEnergy[Channel].Data8[Dimm]   = DdrPwt[i][j].RdCr;
                PmDimmWrEnergy[Channel].Data8[Dimm]   = DdrPwt[i][j].WrCr;
                PmDimmActEnergy[Channel].Data8[Dimm]  = DdrPwt[i][j].ActCr;
                PmDimmPdEnergy[Channel].Data8[Dimm]   = DdrPwt[i][j].CkeL;
                PmDimmIdleEnergy[Channel].Data8[Dimm] = DdrPwt[i][j].CkeH;
                ScaleFactor[Channel][Dimm]            = DdrPwt[i][j].ScaleFactor;
                ChPwrFloor[Channel][Dimm]             = DdrPwt[i][j].ChPwrFloor;
                MinScaleFactor                        = MIN (MinScaleFactor, ScaleFactor[Channel][Dimm]);
                DimmEntryFound                        = TRUE;
                break;
              }
            } else { // Lpddr3
              if (DimmPwt.Data == Lpddr3Pwt[i][j].PwInput.Data) {
                PmDimmRdEnergy[Channel].Data8[Dimm]   = Lpddr3Pwt[i][j].RdCr;
                PmDimmWrEnergy[Channel].Data8[Dimm]   = Lpddr3Pwt[i][j].WrCr;
                PmDimmActEnergy[Channel].Data8[Dimm]  = Lpddr3Pwt[i][j].ActCr;
                PmDimmPdEnergy[Channel].Data8[Dimm]   = Lpddr3Pwt[i][j].CkeL;
                PmDimmIdleEnergy[Channel].Data8[Dimm] = Lpddr3Pwt[i][j].CkeH;
                ScaleFactor[Channel][Dimm]            = Lpddr3Pwt[i][j].ScaleFactor;
                ChPwrFloor[Channel][Dimm]             =
                  (ControllerOut->ChannelCount == 1)
                  ? Lpddr3Pwt[i][j].OneChPwrFloor
                  : Lpddr3Pwt[i][j].TwoChPwrFloor;
                MinScaleFactor                        = MIN (MinScaleFactor, ScaleFactor[Channel][Dimm]);
                DimmEntryFound                        = TRUE;
                break;
              }
            }
          }
        }
      }
    }

    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      if (!MrcChannelExist (Outputs, Channel)) {
        continue;
      }
      ChannelOut = &ControllerOut->Channel[Channel];
      for (Dimm = 0; Dimm < MAX_DIMMS_IN_CHANNEL; Dimm++) {
        DimmOut = &ChannelOut->Dimm[Dimm];
        if (DimmOut->Status != DIMM_PRESENT) {
          continue;
        }
        //
        // Set Scale Factor of all DIMMs to lowest Scale Factor and adjust weights accordingly.
        //
        if ((SfDiff = ScaleFactor[Channel][Dimm] - MinScaleFactor) > 0) {
          PmDimmRdEnergy[Channel].Data8[Dimm]   = (PmDimmRdEnergy[Channel].Data8[Dimm] + 1) >> SfDiff;
          PmDimmWrEnergy[Channel].Data8[Dimm]   = (PmDimmWrEnergy[Channel].Data8[Dimm] + 1) >> SfDiff;
          PmDimmActEnergy[Channel].Data8[Dimm]  = (PmDimmActEnergy[Channel].Data8[Dimm] + 1) >> SfDiff;
          PmDimmPdEnergy[Channel].Data8[Dimm]   = (PmDimmPdEnergy[Channel].Data8[Dimm] + 1) >> SfDiff;
          PmDimmIdleEnergy[Channel].Data8[Dimm] = (PmDimmIdleEnergy[Channel].Data8[Dimm] + 1) >> SfDiff;
        }
      }
      //
      // Set RAPL Channel Power Floor to average of DIMMs rounded up to nearest integer multiple of 0.125W (which is
      // going to be a multiple of 8 for Channel Power Floor Register).
      //
      if (ChannelOut->DimmCount > 1) {
        if (ChPwrFloor[Channel][0] != ChPwrFloor[Channel][1]) {
          ChPwrFloor[Channel][0] = (ChPwrFloor[Channel][0] + ChPwrFloor[Channel][1] + 1) / 2;
          if (ChPwrFloor[Channel][0] < 0xF8) {
            if ((ChPwrFloor[Channel][0] % 8) != 0) {
              ChPwrFloor[Channel][0] = ChPwrFloor[Channel][0] + (8 - (ChPwrFloor[Channel][0] % 8));
            }
          } else { // No more 8-bit mulitples of 8 after 0xF8, must round down.
            ChPwrFloor[Channel][0] = 0xF8;
          }
        }
      } else {
        for (Dimm = 0; Dimm < MAX_DIMMS_IN_CHANNEL; Dimm++) {
          ChPwrFloor[Channel][0] = MAX (ChPwrFloor[Channel][0], ChPwrFloor[Channel][Dimm]);
        }
      }

      //
      // Apply power weights
      //
      Offset = MCHBAR_CH0_CR_PM_DIMM_RD_ENERGY_REG +
        (MCHBAR_CH1_CR_PM_DIMM_RD_ENERGY_REG - MCHBAR_CH0_CR_PM_DIMM_RD_ENERGY_REG) * Channel;
      MrcWriteCR (MrcData, Offset, PmDimmRdEnergy[Channel].Data);
      Offset = MCHBAR_CH0_CR_PM_DIMM_WR_ENERGY_REG +
        (MCHBAR_CH1_CR_PM_DIMM_WR_ENERGY_REG - MCHBAR_CH0_CR_PM_DIMM_WR_ENERGY_REG) * Channel;
      MrcWriteCR (MrcData, Offset, PmDimmWrEnergy[Channel].Data);
      Offset = MCHBAR_CH0_CR_PM_DIMM_ACT_ENERGY_REG +
        (MCHBAR_CH1_CR_PM_DIMM_ACT_ENERGY_REG - MCHBAR_CH0_CR_PM_DIMM_ACT_ENERGY_REG) * Channel;
      MrcWriteCR (MrcData, Offset, PmDimmActEnergy[Channel].Data);
      Offset = MCHBAR_CH0_CR_PM_DIMM_PD_ENERGY_REG +
        (MCHBAR_CH1_CR_PM_DIMM_PD_ENERGY_REG - MCHBAR_CH0_CR_PM_DIMM_PD_ENERGY_REG) * Channel;
      MrcWriteCR (MrcData, Offset, PmDimmPdEnergy[Channel].Data);
      Offset = MCHBAR_CH0_CR_PM_DIMM_IDLE_ENERGY_REG +
        (MCHBAR_CH1_CR_PM_DIMM_IDLE_ENERGY_REG - MCHBAR_CH0_CR_PM_DIMM_IDLE_ENERGY_REG) * Channel;
      MrcWriteCR (MrcData, Offset, PmDimmIdleEnergy[Channel].Data);
    }
    DdrRaplChannelPowerFloor.Bits.CH0 = ChPwrFloor[0][0];
    DdrRaplChannelPowerFloor.Bits.CH1 = ChPwrFloor[1][0];
    MrcWriteCR (MrcData, PCU_CR_DDR_RAPL_CHANNEL_POWER_FLOOR_PCU_REG, DdrRaplChannelPowerFloor.Data);
    MrcWriteCR (MrcData, PCU_CR_DDR_ENERGY_SCALEFACTOR_PCU_REG, (UINT32) MinScaleFactor);

#ifdef MRC_DEBUG_PRINT
    MRC_DEBUG_MSG (
      Debug,
      MSG_LEVEL_NOTE,
      "Applied Power Weights:\n\tSclFctr\tRdCr\tWrCr\tActCr\tCkeL\tCkeH\tChPwrFloor\n"
      );
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      if (!MrcChannelExist (Outputs, Channel)) {
        continue;
      }
      ChannelOut = &ControllerOut->Channel[Channel];
      for (Dimm = 0; Dimm < MAX_DIMMS_IN_CHANNEL; Dimm++) {
        DimmOut = &ChannelOut->Dimm[Dimm];
        if (DimmOut->Status == DIMM_PRESENT) {
          MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "C%dD%d:\t", Channel, Dimm);
          MRC_DEBUG_MSG (
            Debug,
            MSG_LEVEL_NOTE,
            "%d\t%2Xh\t%2Xh\t%2Xh\t%Xh\t%2Xh\t%2Xh\n",
            MinScaleFactor,
            PmDimmRdEnergy[Channel].Data8[Dimm],
            PmDimmWrEnergy[Channel].Data8[Dimm],
            PmDimmActEnergy[Channel].Data8[Dimm],
            PmDimmPdEnergy[Channel].Data8[Dimm],
            PmDimmIdleEnergy[Channel].Data8[Dimm],
            ChPwrFloor[Channel][0]
            );
        }
      }
    }
#endif
  }

  return mrcSuccess;
}

/**
  Override Thermal settings

  @param[in] MrcData  - The MRC "global data" area.
**/
void
MrcThermalOverrides (
  IN MrcParameters *MrcData
  )
{
  MrcInput                                        *Inputs;
  MrcOutput                                       *Outputs;
  MrcDebug                                        *Debug;
  ThermalMngmtEn                                  *ThermalEnables;
  MrcDdrType                                      DdrType;
  UINT8                                           Channel;
  UINT32                                          Offset;
  PCU_CR_DDR_PTM_CTL_PCU_STRUCT                   DdrPtmCtl;
  PCU_CR_DDR_ENERGY_SCALEFACTOR_PCU_STRUCT        DdrEnergyScaleFactor;
  PCU_CR_DDR_RAPL_CHANNEL_POWER_FLOOR_PCU_STRUCT  DdrRaplChannelPowerFloor;
  PCU_CR_DDR_RAPL_LIMIT_PCU_STRUCT                DdrRaplLimit;
  PCU_CR_DDR_WARM_THRESHOLD_CH0_PCU_STRUCT        DdrWarmThresholdCh0;
  PCU_CR_DDR_WARM_THRESHOLD_CH1_PCU_STRUCT        DdrWarmThresholdCh1;
  PCU_CR_DDR_HOT_THRESHOLD_CH0_PCU_STRUCT         DdrHotThresholdCh0;
  PCU_CR_DDR_HOT_THRESHOLD_CH1_PCU_STRUCT         DdrHotThresholdCh1;
  PCU_CR_DDR_WARM_BUDGET_CH0_PCU_STRUCT           DdrWarmBudgetCh0;
  PCU_CR_DDR_WARM_BUDGET_CH1_PCU_STRUCT           DdrWarmBudgetCh1;
  PCU_CR_DDR_HOT_BUDGET_CH0_PCU_STRUCT            DdrHotBudgetCh0;
  PCU_CR_DDR_HOT_BUDGET_CH1_PCU_STRUCT            DdrHotBudgetCh1;
  MCHBAR_CH0_CR_PM_DIMM_IDLE_ENERGY_STRUCT        PmDimmIdleEnergy;
  MCHBAR_CH0_CR_PM_DIMM_PD_ENERGY_STRUCT          PmDimmPdEnergy;
  MCHBAR_CH0_CR_PM_DIMM_ACT_ENERGY_STRUCT         PmDimmActEnergy;
  MCHBAR_CH0_CR_PM_DIMM_RD_ENERGY_STRUCT          PmDimmRdEnergy;
  MCHBAR_CH0_CR_PM_DIMM_WR_ENERGY_STRUCT          PmDimmWrEnergy;
  MCHBAR_CH0_CR_PM_PDWN_CONFIG_STRUCT             PmPwdnConfig;
  MCDECS_CR_PM_SREF_CONFIG_MCMAIN_STRUCT          PmSrefConfig;

  Inputs              = &MrcData->Inputs;
  Outputs             = &MrcData->Outputs;
  Debug               = &Outputs->Debug;
  ThermalEnables      = &Inputs->ThermalEnables;
  DdrType             = Outputs->DdrType;
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "...SV Thermal Overwrite ...\n");

  if (Inputs->UserPowerWeightsEn) {
    //
    // ENERGY SCALE FACTOR
    //
    DdrEnergyScaleFactor.Data             = 0;
    DdrEnergyScaleFactor.Bits.SCALEFACTOR = Inputs->EnergyScaleFact;
    MRC_DEBUG_MSG (
      Debug,
      MSG_LEVEL_NOTE,
      "DDR_ENERGY_SCALEFACTOR %Xh: %Xh \n",
      PCU_CR_DDR_ENERGY_SCALEFACTOR_PCU_REG,
      DdrEnergyScaleFactor.Data
      );
    MrcWriteCR (MrcData, PCU_CR_DDR_ENERGY_SCALEFACTOR_PCU_REG, DdrEnergyScaleFactor.Data);

    //
    // RAPL POWER FLOOR
    //
    DdrRaplChannelPowerFloor.Data     = 0;
    DdrRaplChannelPowerFloor.Bits.CH0 = Inputs->RaplPwrFlCh0;
    DdrRaplChannelPowerFloor.Bits.CH1 = Inputs->RaplPwrFlCh1;
    MRC_DEBUG_MSG (
      Debug,
      MSG_LEVEL_NOTE,
      "DDR_RAPL_CHANNEL_POWER_FLOOR %Xh: %Xh \n",
      PCU_CR_DDR_RAPL_CHANNEL_POWER_FLOOR_PCU_REG,
      DdrRaplChannelPowerFloor.Data
      );
    MrcWriteCR (MrcData, PCU_CR_DDR_RAPL_CHANNEL_POWER_FLOOR_PCU_REG, DdrRaplChannelPowerFloor.Data);
  }

  //
  // RAPL LIMIT
  //
  DdrRaplLimit.Data                       = 0;
  DdrRaplLimit.Bits.LIMIT1_TIME_WINDOW_X  = ThermalEnables->RaplLim1WindX;
  DdrRaplLimit.Bits.LIMIT1_TIME_WINDOW_Y  = ThermalEnables->RaplLim1WindY;
  DdrRaplLimit.Bits.LIMIT1_ENABLE         = Inputs->RaplLim1Ena;
  DdrRaplLimit.Bits.LIMIT1_POWER          = ThermalEnables->RaplLim1Pwr;
  DdrRaplLimit.Bits.LOCKED                = Inputs->RaplLim2Lock;
  DdrRaplLimit.Bits.LIMIT2_TIME_WINDOW_X  = ThermalEnables->RaplLim2WindX;
  DdrRaplLimit.Bits.LIMIT2_TIME_WINDOW_Y  = ThermalEnables->RaplLim2WindY;
  DdrRaplLimit.Bits.LIMIT2_ENABLE         = Inputs->RaplLim2Ena;
  DdrRaplLimit.Bits.LIMIT2_POWER          = ThermalEnables->RaplLim2Pwr;
  MRC_DEBUG_MSG (
    Debug,
    MSG_LEVEL_NOTE,
    "DDR_RAPL_LIMIT1 %Xh: %Xh \n",
    PCU_CR_DDR_RAPL_LIMIT_PCU_REG,
    DdrRaplLimit.Data32[0]
    );
  MRC_DEBUG_MSG (
    Debug,
    MSG_LEVEL_NOTE,
    "DDR_RAPL_LIMIT2 %Xh: %Xh \n",
    PCU_CR_DDR_RAPL_LIMIT_PCU_REG + 4,
    DdrRaplLimit.Data32[1]
    );
  MrcWriteCR (MrcData, PCU_CR_DDR_RAPL_LIMIT_PCU_REG, DdrRaplLimit.Data32[0]);
  MrcWriteCR (MrcData, PCU_CR_DDR_RAPL_LIMIT_PCU_REG + 4, DdrRaplLimit.Data32[1]);

#ifdef UP_SERVER_FLAG
  if ((Inputs->UserThresholdEnable) || (Inputs->BoardType != btUpServer)) {
#endif
    //
    // DDR WARM AND HOT THRESHOLD
    //
    DdrWarmThresholdCh0.Data        = 0;
    DdrWarmThresholdCh0.Bits.DIMM1  = ThermalEnables->WarmThreshold[0][1];
    DdrWarmThresholdCh0.Bits.DIMM0  = ThermalEnables->WarmThreshold[0][0];
    MRC_DEBUG_MSG (
      Debug,
      MSG_LEVEL_NOTE,
      "DDR_WARM_THRESHOLD_CH0 %Xh: %Xh \n",
      PCU_CR_DDR_WARM_THRESHOLD_CH0_PCU_REG,
      DdrWarmThresholdCh0.Data
      );
    MrcWriteCR (MrcData, PCU_CR_DDR_WARM_THRESHOLD_CH0_PCU_REG, DdrWarmThresholdCh0.Data);

    DdrWarmThresholdCh1.Data        = 0;
    DdrWarmThresholdCh1.Bits.DIMM1  = ThermalEnables->WarmThreshold[1][1];
    DdrWarmThresholdCh1.Bits.DIMM0  = ThermalEnables->WarmThreshold[1][0];
    MRC_DEBUG_MSG (
      Debug,
      MSG_LEVEL_NOTE,
      "DDR_WARM_THRESHOLD_CH1 %Xh: %Xh \n",
      PCU_CR_DDR_WARM_THRESHOLD_CH1_PCU_REG,
      DdrWarmThresholdCh1.Data
      );
    MrcWriteCR (MrcData, PCU_CR_DDR_WARM_THRESHOLD_CH1_PCU_REG, DdrWarmThresholdCh1.Data);

    DdrHotThresholdCh0.Data       = 0;
    DdrHotThresholdCh0.Bits.DIMM1 = ThermalEnables->HotThreshold[0][1];
    DdrHotThresholdCh0.Bits.DIMM0 = ThermalEnables->HotThreshold[0][0];
    MRC_DEBUG_MSG (
      Debug,
      MSG_LEVEL_NOTE,
      "DDR_HOT_THRESHOLD_CH0 %Xh: %Xh \n",
      PCU_CR_DDR_HOT_THRESHOLD_CH0_PCU_REG,
      DdrHotThresholdCh0.Data
      );
    MrcWriteCR (MrcData, PCU_CR_DDR_HOT_THRESHOLD_CH0_PCU_REG, DdrHotThresholdCh0.Data);

    DdrHotThresholdCh1.Data       = 0;
    DdrHotThresholdCh1.Bits.DIMM1 = ThermalEnables->HotThreshold[1][1];
    DdrHotThresholdCh1.Bits.DIMM0 = ThermalEnables->HotThreshold[1][0];
    MRC_DEBUG_MSG (
      Debug,
      MSG_LEVEL_NOTE,
      "DDR_HOT_THRESHOLD_CH1 %Xh: %Xh \n",
      PCU_CR_DDR_HOT_THRESHOLD_CH1_PCU_REG,
      DdrHotThresholdCh1.Data
      );
    MrcWriteCR (MrcData, PCU_CR_DDR_HOT_THRESHOLD_CH1_PCU_REG, DdrHotThresholdCh1.Data);
#ifdef UP_SERVER_FLAG
  }

  if ((Inputs->UserBudgetEnable) || (Inputs->BoardType != btUpServer)) {
#endif
    //
    // DDR WARM AND HOT BUDGET
    //
    DdrWarmBudgetCh0.Data       = 0;
    DdrWarmBudgetCh0.Bits.DIMM1 = ThermalEnables->WarmBudget[0][1];
    DdrWarmBudgetCh0.Bits.DIMM0 = ThermalEnables->WarmBudget[0][0];
    MRC_DEBUG_MSG (
      Debug,
      MSG_LEVEL_NOTE,
      "DDR_WARM_BUDGET_CH0 %Xh: %Xh \n",
      PCU_CR_DDR_WARM_BUDGET_CH0_PCU_REG,
      DdrWarmBudgetCh0.Data
      );
    MrcWriteCR (MrcData, PCU_CR_DDR_WARM_BUDGET_CH0_PCU_REG, DdrWarmBudgetCh0.Data);

    DdrWarmBudgetCh1.Data       = 0;
    DdrWarmBudgetCh1.Bits.DIMM1 = ThermalEnables->WarmBudget[1][1];
    DdrWarmBudgetCh1.Bits.DIMM0 = ThermalEnables->WarmBudget[1][0];
    MRC_DEBUG_MSG (
      Debug,
      MSG_LEVEL_NOTE,
      "DDR_WARM_BUDGET_CH1 %Xh: %Xh \n",
      PCU_CR_DDR_WARM_BUDGET_CH1_PCU_REG,
      DdrWarmBudgetCh1.Data
      );
    MrcWriteCR (MrcData, PCU_CR_DDR_WARM_BUDGET_CH1_PCU_REG, DdrWarmBudgetCh1.Data);

    DdrHotBudgetCh0.Data        = 0;
    DdrHotBudgetCh0.Bits.DIMM1  = ThermalEnables->HotBudget[0][1];
    DdrHotBudgetCh0.Bits.DIMM0  = ThermalEnables->HotBudget[0][0];
    MRC_DEBUG_MSG (
      Debug,
      MSG_LEVEL_NOTE,
      "DDR_HOT_BUDGET_CH0 %Xh: %Xh \n",
      PCU_CR_DDR_HOT_BUDGET_CH0_PCU_REG,
      DdrHotBudgetCh0.Data
      );
    MrcWriteCR (MrcData, PCU_CR_DDR_HOT_BUDGET_CH0_PCU_REG, DdrHotBudgetCh0.Data);

    DdrHotBudgetCh1.Data        = 0;
    DdrHotBudgetCh1.Bits.DIMM1  = ThermalEnables->HotBudget[1][1];
    DdrHotBudgetCh1.Bits.DIMM0  = ThermalEnables->HotBudget[1][0];
    MRC_DEBUG_MSG (
      Debug,
      MSG_LEVEL_NOTE,
      "DDR_HOT_BUDGET_CH1 %Xh: %Xh \n",
      PCU_CR_DDR_HOT_BUDGET_CH1_PCU_REG,
      DdrHotBudgetCh1.Data
      );
    MrcWriteCR (MrcData, PCU_CR_DDR_HOT_BUDGET_CH1_PCU_REG, DdrHotBudgetCh1.Data);
#ifdef UP_SERVER_FLAG
  }
#endif

  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    if (MrcChannelExist (Outputs, Channel)) {
      if (Inputs->UserPowerWeightsEn) {
        PmDimmIdleEnergy.Data                   = 0;
        PmDimmIdleEnergy.Bits.DIMM1_IDLE_ENERGY = ThermalEnables->IdleEnergy[Channel][1];
        PmDimmIdleEnergy.Bits.DIMM0_IDLE_ENERGY = ThermalEnables->IdleEnergy[Channel][0];
        Offset = MCHBAR_CH0_CR_PM_DIMM_IDLE_ENERGY_REG +
          (MCHBAR_CH1_CR_PM_DIMM_IDLE_ENERGY_REG - MCHBAR_CH0_CR_PM_DIMM_IDLE_ENERGY_REG) * Channel;
        MRC_DEBUG_MSG (
          Debug,
          MSG_LEVEL_NOTE,
          "C%u PM_DIMM_IDLE_ENERGY %Xh: %Xh \n",
          Channel,
          Offset,
          PmDimmIdleEnergy.Data
          );
        MrcWriteCR (MrcData, Offset, PmDimmIdleEnergy.Data);

        PmDimmPdEnergy.Data                 = 0;
        PmDimmPdEnergy.Bits.DIMM1_PD_ENERGY = ThermalEnables->PdEnergy[Channel][1];
        PmDimmPdEnergy.Bits.DIMM0_PD_ENERGY = ThermalEnables->PdEnergy[Channel][0];
        Offset = MCHBAR_CH0_CR_PM_DIMM_PD_ENERGY_REG +
          (MCHBAR_CH1_CR_PM_DIMM_PD_ENERGY_REG - MCHBAR_CH0_CR_PM_DIMM_PD_ENERGY_REG) * Channel;
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "C%u PM_DIMM_PD_ENERGY %Xh: %Xh \n", Channel, Offset, PmDimmPdEnergy.Data);
        MrcWriteCR (MrcData, Offset, PmDimmPdEnergy.Data);

        PmDimmActEnergy.Data                  = 0;
        PmDimmActEnergy.Bits.DIMM1_ACT_ENERGY = ThermalEnables->ActEnergy[Channel][1];
        PmDimmActEnergy.Bits.DIMM0_ACT_ENERGY = ThermalEnables->ActEnergy[Channel][0];
        Offset = MCHBAR_CH0_CR_PM_DIMM_ACT_ENERGY_REG +
          (MCHBAR_CH1_CR_PM_DIMM_ACT_ENERGY_REG - MCHBAR_CH0_CR_PM_DIMM_ACT_ENERGY_REG) * Channel;
        MRC_DEBUG_MSG (
          Debug,
          MSG_LEVEL_NOTE,
          "C%u PM_DIMM_ACT_ENERGY %Xh: %Xh \n",
          Channel,
          Offset,
          PmDimmActEnergy.Data
          );
        MrcWriteCR (MrcData, Offset, PmDimmActEnergy.Data);

        PmDimmRdEnergy.Data                 = 0;
        PmDimmRdEnergy.Bits.DIMM1_RD_ENERGY = ThermalEnables->RdEnergy[Channel][1];
        PmDimmRdEnergy.Bits.DIMM0_RD_ENERGY = ThermalEnables->RdEnergy[Channel][0];
        Offset = MCHBAR_CH0_CR_PM_DIMM_RD_ENERGY_REG +
          (MCHBAR_CH1_CR_PM_DIMM_RD_ENERGY_REG - MCHBAR_CH0_CR_PM_DIMM_RD_ENERGY_REG) * Channel;
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "C%u PM_DIMM_RD_ENERGY %Xh: %Xh \n", Channel, Offset, PmDimmRdEnergy.Data);
        MrcWriteCR (MrcData, Offset, PmDimmRdEnergy.Data);

        PmDimmWrEnergy.Data                 = 0;
        PmDimmWrEnergy.Bits.DIMM1_WR_ENERGY = ThermalEnables->WrEnergy[Channel][1];
        PmDimmWrEnergy.Bits.DIMM0_WR_ENERGY = ThermalEnables->WrEnergy[Channel][0];
        Offset = MCHBAR_CH0_CR_PM_DIMM_WR_ENERGY_REG +
          (MCHBAR_CH1_CR_PM_DIMM_WR_ENERGY_REG - MCHBAR_CH0_CR_PM_DIMM_WR_ENERGY_REG) * Channel;
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "C%u PM_DIMM_WR_ENERGY %Xh: %Xh \n", Channel, Offset, PmDimmWrEnergy.Data);
        MrcWriteCR (MrcData, Offset, PmDimmWrEnergy.Data);
      }

      Offset = MCHBAR_CH0_CR_PM_PDWN_CONFIG_REG +
        (MCHBAR_CH1_CR_PM_PDWN_CONFIG_REG - MCHBAR_CH0_CR_PM_PDWN_CONFIG_REG) * Channel;
      PmPwdnConfig.Data = MrcReadCR (MrcData, Offset);
      if (DdrType == MRC_DDR_TYPE_LPDDR3) {
        PmPwdnConfig.Bits.dis_cke_tt      = Inputs->ThrtCkeMinDefeatLpddr;
        PmPwdnConfig.Bits.TT_idle_counter = Inputs->ThrtCkeMinTmrLpddr;
      } else {
        PmPwdnConfig.Bits.dis_cke_tt      = Inputs->ThrtCkeMinDefeat;
        PmPwdnConfig.Bits.TT_idle_counter = Inputs->ThrtCkeMinTmr;
      }
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "C%u PM_PDWN_CONFIG: %Xh \n", Channel, PmPwdnConfig.Data);
      MrcWriteCR (MrcData, Offset, PmPwdnConfig.Data);
    }
  }
  PmSrefConfig.Data             = 0;
  PmSrefConfig.Bits.SR_Enable   = Inputs->SrefCfgEna;
  PmSrefConfig.Bits.Idle_timer  = Inputs->SrefCfgIdleTmr;
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "PM_SREF_CONFIG %Xh: %Xh\n", MCDECS_CR_PM_SREF_CONFIG_MCMAIN_REG, PmSrefConfig.Data);
  MrcWriteCR (MrcData, MCDECS_CR_PM_SREF_CONFIG_MCMAIN_REG, PmSrefConfig.Data);

  //
  // POWER THERMAL MANAGEMENT CONTROL
  //
  DdrPtmCtl.Data                    = MrcReadCR (MrcData, PCU_CR_DDR_PTM_CTL_PCU_REG);
  DdrPtmCtl.Bits.OLTM_ENABLE        = Inputs->EnableOltm;
  DdrPtmCtl.Bits.CLTM_ENABLE        = Inputs->EnableCltm;
  DdrPtmCtl.Bits.EXTTS_ENABLE       = Inputs->EnableExtts;
  DdrPtmCtl.Bits.REFRESH_2X_MODE    = Inputs->Refresh2X;

  if (DdrType == MRC_DDR_TYPE_DDR4) {
    if ((Outputs->TCRSensitiveHynixDDR4) || (Outputs->TCRSensitiveMicronDDR4)) {
      DdrPtmCtl.Bits.DDR4_SKIP_REFRESH_EN = 0;
    } else {
      DdrPtmCtl.Bits.DDR4_SKIP_REFRESH_EN = (Inputs->Ddr4SkipRefreshEn == 1) ? 1 : 0;
    }
    DdrPtmCtl.Bits.DISABLE_DRAM_TS = (Inputs->DdrThermalSensor == 0) ? 1 : 0;
  }

  if (DdrType == MRC_DDR_TYPE_LPDDR3) {
    DdrPtmCtl.Bits.PDWN_CONFIG_CTL = Inputs->EnablePwrDnLpddr;
    DdrPtmCtl.Bits.DISABLE_DRAM_TS = (Inputs->DdrThermalSensor == 0) ? 1 : 0;
  } else {
    DdrPtmCtl.Bits.PDWN_CONFIG_CTL = Inputs->EnablePwrDn;
  }
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "DDR_PTM_CTL %Xh: %Xh\n", PCU_CR_DDR_PTM_CTL_PCU_REG, DdrPtmCtl.Data);
  MrcWriteCR (MrcData, PCU_CR_DDR_PTM_CTL_PCU_REG, DdrPtmCtl.Data);

#ifdef UP_SERVER_FLAG
  if (Inputs->BoardType == btUpServer) {
    MrcCltmTsodInitChecking (MrcData);
    if (Inputs->TsodManualEnable != 0) {
      CltmTsodConfiguration (MrcData);
    }
  }
#endif

  return;
}

