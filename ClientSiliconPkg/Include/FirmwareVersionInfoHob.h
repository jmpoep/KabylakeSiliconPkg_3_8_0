/** @file
  Header file for Firmware Version Information

 Copyright (c) 2015 - 2016, Intel Corporation. All rights reserved.<BR>

 This program and the accompanying materials are licensed and made available under
 the terms and conditions of the BSD License which accompanies this distribution.
 The full text of the license may be found at
 http://opensource.org/licenses/bsd-license.php

 THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
 WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

**/

#ifndef _FIRMWARE_VERSION_INFO_HOB_H_
#define _FIRMWARE_VERSION_INFO_HOB_H_

#include <Uefi.h>
#include <Pi/PiHob.h>

#pragma pack(1)
///
/// Firmware Version Structure
///
typedef struct {
  UINT8                          MajorVersion;
  UINT8                          MinorVersion;
  UINT8                          Revision;
  UINT16                         BuildNumber;
} FIRMWARE_VERSION;

///
/// Firmware Version Information Structure
///
typedef struct {
  UINT8                          ComponentNameIndex;        ///< Offset 0   Index of Component Name
  UINT8                          VersionStringIndex;        ///< Offset 1   Index of Version String
  FIRMWARE_VERSION               Version;                   ///< Offset 2-6 Firmware version
} FIRMWARE_VERSION_INFO;

///
/// Firmware Version Information HOB Structure
///
typedef struct {
  EFI_HOB_GUID_TYPE              Header;                    ///< Offset 0-23  The header of FVI HOB
  UINT8                          Count;                     ///< Offset 24    Number of FVI elements included.
///
/// FIRMWARE_VERSION_INFO structures followed by the null terminated string buffer
///
} FIRMWARE_VERSION_INFO_HOB;
#pragma pack()

#endif // _FIRMWARE_VERSION_INFO_HOB_H_
