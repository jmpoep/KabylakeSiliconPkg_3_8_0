/** @file
  Defines Platform BoardIds

 @copyright
  INTEL CONFIDENTIAL
  Copyright 2011 - 2019 Intel Corporation.

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

#ifndef _PLATFORM_BOARD_ID_H_
#define _PLATFORM_BOARD_ID_H_

#define PLATFORM_INFO_HOB_REVISION          0x1

#define FlavorUnknown                       0x0
#define FlavorMobile                        0x1
#define FlavorDesktop                       0x2
#define FlavorWorkstation                   0x3
#define FlavorUpServer                      0x4
#define FlavorEmbedded                      0x5
#define FlavorPlatformMax                   0x6

#define TypeUnknown                         0x0
#define TypeTrad                            0x1
#define TypeUlt                             0x2

#define GenLpt                              0x1
#define GenWpt                              0x2
#define GenUnknown                          0x3

//
// Mobile Board Id 0x00 - 0xFF
//
// PUT SKL CRB BoardIds here
#define BoardIdSkylakeA0Lpddr3Crb           0x1
#define BoardIdSkylakeA0Ddr4Rvp2            0x2
#define BoardIdKabylakeKcDdr3               0x3
#define BoardIdSkylakeA0Rvp3                0x4
#define BoardIdSkylakeYRvp13                0x5
#define BoardIdKabylakeRDdr4                0x7
#define BoardIdSkylakeLpdimmDoe             0x8
#define BoardIdSkylakeStarbrook             0x9
#define BoardIdSkylakeULpddr3Rvp5           0xA
#define BoardIdSkylakeURvp7                 0xB
#define BoardIdSkylakeURvp15                0xC
#define BoardIdKabylakeRLpddr3              0x13
#define BoardIdSkylakeA0Rvp3Ppv             0x14
#define BoardIdSkylakeULpddr3Rvp5Ppv        0x1A
#define BoardIdSkylakeURvp7Ppv              0x1B
#define BoardIdSkylakeSds                   0x20
#define BoardIdSkylakePantherMtn            0x21
#define BoardIdSkylakePhabletPoc            0x23

#define BoardIdSkylakeAioRvp10Erb           0x40
#define BoardIdSkylakeAioRvp9Crb            0x41
#define BoardIdSkylakeDtRvp8Crb             0x42
#define BoardIdSkylakeAioRvp10Crb           0x43
#define BoardIdSkylakeHaloDdr4Rvp11         0x44
#define BoardIdSkylakeHaloDdr4Rvp11Ppv      0x45
#define BoardIdSkylakeAioRvp10CrbPpv        0x46
#define BoardIdSkylakeHaloLpddr3Rvp16       0x48
#define BoardIdSkylakeSlpfPpv               0x49
#define BoardIdKabylakeDdr4Rvp17            0x4A // KblGContent
#define BoardIdSkylakeSdlBrk                0x50

//            ERB build        |   CRB build
// ----------------------------+-------------------------------------
// Karkom X0: HSW_ULT / LPT_LP |   SKL A0 / LPT_LP (in SKL_LPT stream only)
// Karkom A0: HSW_ULT / LPT_LP |   SKL A0 / SKL PCH LP (in SKL_SPT stream)
//


//60-6F reserved for KBL RVPs
#define BoardIdKabyLakeYLpddr3Rvp3          0x60
#define BoardIdKabylakeGrizzlyMtn           0x61
#define BoardIdKabylakeUDdr3lRvp7           0x64
#define BoardIdKabyLakeSDdr4UdimmEvErb      0x66
#define BoardIdKabyLakeSDdr4UdimmEvCrb      0x67
#define BoardIdKabyLakeOc                   0x68
#define BoardIdKabyLakeSDdr4UdimmCrb        0x69
#define BoardIdKabylakeSUdimmCpv            0x6A
#define BoardIdBasinFallsEv                 0x6B
#define BoardIdBasinFallsCrb                0x6C
#define BoardIdBasinFallsPpv                0x6D
#define BoardIdBasinFallsRsvd               0x6E

#define BoardIdZumbaBeachServerEv           0x73
#define BoardIdZumbaBeachServerCrb          0x74

#define BoardIdGlacierFallsXErb             0x78
#define BoardIdGlacierFallsXEv              0x79
#define BoardIdGlacierFallsXCrb             0x7A
#define BoardIdGlacierFallsXPpv             0x7B

#define BoardIdAmberLakeY42Lpddr3Rvp3       0x81
#define BoardIdAmberLakeLpddr3Rvp3          0x82
#define BoardIdAmberLakeLpddr3Rvp13         0x83
#define BoardIdAmberLakeY42Lpddr3Cff        0x84
#define BoardIdAmberLakeY42Lpddr3CffCc      0x85
#define BoardIdAmberLakeY42Lpddr3WcosRvp    0x86

#define BoardIdMobileMax                    0x3f
#define BoardIdDesktopMax                   0x4f
#define BoardIdTradMobileMax                0x1f

#define BoardIdUnknown1                     0xffff
#define BoardIdPlatformMax                  0xff
#define BOARD_ID_MASK_5BIT                  0x1f
#define BOARD_ID_MASK_8BIT                  0xff
#define FAB_ID_MASK                         0x7
#define BOM_ID_MASK                         0x7
#define GENERATION_MASK                     0x100

#define BoardRevPearValleyERB               0x07

#endif
