/** @file
  Spi policy

 @copyright
  INTEL CONFIDENTIAL
  Copyright 2015 - 2017 Intel Corporation.

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
#ifndef _SPI_CONFIG_H_
#define _SPI_CONFIG_H_

#define SPI_CONFIG_REVISION 2
extern EFI_GUID gSpiConfigGuid;

#pragma pack (push,1)

/**
  This structure contains the policies which are related to SPI.

  <b>Revision 1</b>:
  - Initial version.
  <b>Revision 2</b>:
  - Add FlashCfgLockDown. If platform decides to skip this programming,
    it must lock the SPI register settings before end of post.
**/
typedef struct {
  CONFIG_BLOCK_HEADER   Header;                   ///< Config Block Header
  /**
    Force to show SPI controller.
    <b>0: FALSE</b>, 1: TRUE
    NOTE: For Windows OS, it MUST BE false. It's optional for other OSs.
  **/
  UINT32    ShowSpiController           :  1;
  /**
    Flash Configuration Lock Down.
    0: FALSE, <b>1: TRUE</b>
    If platform decides to skip this programming, it must program below settings
    before end of post.
    1. SPI_BAR0 + 0x0C (DLOCK. SPT-H feature, not for LP.)
    2. SPI_BAR0 + 0x04 BIT15 (FLOCKDN), and make sure BIT11 (WRSDIS) is set.

    For SPI_BAR0 + 0x04 access, use 16bit write to avoid touching two upper bytes
    what may cause the write cycle to fail in case a prior transaction has not completed.
  **/
  UINT32    FlashCfgLockDown            :  1;
  UINT32    RsvdBits                    : 30;     ///< Reserved bits
} PCH_SPI_CONFIG;

#pragma pack (pop)

#endif // _SPI_CONFIG_H_
