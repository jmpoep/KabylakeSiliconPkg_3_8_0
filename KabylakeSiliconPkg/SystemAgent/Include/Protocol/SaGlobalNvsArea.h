/** @file
  Definition of the System Agent global NVS area protocol.
  This protocol publishes the address and format of a global ACPI NVS buffer
  used as a communications buffer between SMM/DXE/PEI code and ASL code.

@copyright
 Copyright (c) 2012 - 2016 Intel Corporation. All rights reserved
 This software and associated documentation (if any) is furnished
 under a license and may only be used or copied in accordance
 with the terms of the license. Except as permitted by the
 license, no part of this software or documentation may be
 reproduced, stored in a retrieval system, or transmitted in any
 form or by any means without the express written consent of
 Intel Corporation.
 This file contains an 'Intel Peripheral Driver' and is uniquely
 identified as "Intel Reference Module" and is licensed for Intel
 CPUs and chipsets under the terms of your license agreement with
 Intel or your vendor. This file may be modified by the user, subject
 to additional terms of the license agreement.

@par Specification Reference:
**/
#ifndef _SYSTEM_AGENT_GLOBAL_NVS_AREA_H_
#define _SYSTEM_AGENT_GLOBAL_NVS_AREA_H_

#include "SaNvs.h"
//
// Extern the GUID for protocol users.
//
extern EFI_GUID gSaGlobalNvsAreaProtocolGuid;

///
/// System Agent Global NVS Area Protocol
///
typedef struct {
  SYSTEM_AGENT_GLOBAL_NVS_AREA *Area;        ///< System Agent Global NVS Area Structure
} SYSTEM_AGENT_GLOBAL_NVS_AREA_PROTOCOL;

#endif
