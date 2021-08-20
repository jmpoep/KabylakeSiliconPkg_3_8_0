/** @file
  This file contains the BIOS implementation of the BIOS-SSA Common Configuration API.

 @copyright
  INTEL CONFIDENTIAL
  Copyright 2013 - 2016 Intel Corporation.

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
#include "SsaBios.h"
#include "MrcSsaServices.h"
#include "MrcSsaCommon.h"
#include "MrcCommon.h"
#include "MrcGeneral.h"
#include "MrcDebugPrint.h"
#include "MrcMalloc.h"
#ifdef MRC_MINIBIOS_BUILD

#else
#include "MemoryInit.h"
#endif

#ifdef SSA_FLAG
extern
BOOLEAN
GetDimmCrc (
  IN  const UINT8 *const Buffer,
  IN  const UINT32       Size,
  OUT UINT16      *const Crc
  );

/**
  Reads a variable-sized value from a memory mapped register using an absolute address.
  This function takes advantage of any caching implemented by BIOS.

  @param[in, out] This    - Interface pointer that implements the particular SSA_BIOS_SERVICES_PPI instance.
  @param[in]      Width   - The size of the value to write.
  @param[in]      Address - Address of the register to be accessed.
  @param[out]     Buffer  - Value storage location.

  @retval Nothing.
**/
VOID
(EFIAPI BiosReadMem) (
  SSA_BIOS_SERVICES_PPI *This,
  REG_WIDTH             Width,
  EFI_PHYSICAL_ADDRESS  Address,
  VOID                  *Buffer
  )
{
  MRC_FUNCTION  *MrcCall;
  MMIO_BUFFER *MmioBuffer;

  MrcCall  = ((MrcParameters *) This->SsaMemoryConfig->MrcData)->Inputs.Call.Func;
  MmioBuffer = (MMIO_BUFFER *) Buffer;
  switch (Width) {
    case RegWidth8:
      MmioBuffer->Data8 = MrcCall->MrcMmioRead8 ((UINT32) Address);
      break;

    case RegWidth16:
      MmioBuffer->Data16 = MrcCall->MrcMmioRead16 ((UINT32) Address);
      break;

    case RegWidth32:
      MmioBuffer->Data32 = MrcCall->MrcMmioRead32 ((UINT32) Address);
      break;

    case RegWidth64:
      MmioBuffer->Data64 = MrcCall->MrcMmioRead64 ((UINT32) Address);
      break;

    default:
      break;
  }
  return;
}

/**
  Writes a variable sized value to a memory mapped register using an absolute address.

  @param[in, out] This    - Interface pointer that implements the particular SSA_BIOS_SERVICES_PPI instance.
  @param[in]      Width   - The size of the value to write.
  @param[in]      Address - Address of the register to be accessed.
  @param[in]      Buffer  - Value to write.

  @retval Nothing.
**/
VOID
(EFIAPI BiosWriteMem) (
  SSA_BIOS_SERVICES_PPI *This,
  REG_WIDTH             Width,
  EFI_PHYSICAL_ADDRESS  Address,
  VOID                  *Buffer
  )
{
  MRC_FUNCTION  *MrcCall;
  MMIO_BUFFER   *MmioBuffer;

  MrcCall  = ((MrcParameters *) This->SsaMemoryConfig->MrcData)->Inputs.Call.Func;
  MmioBuffer = (MMIO_BUFFER *) Buffer;
  switch (Width) {
    case RegWidth8:
      MrcCall->MrcMmioWrite8 ((UINT32) Address, MmioBuffer->Data8);
      break;

    case RegWidth16:
      MrcCall->MrcMmioWrite16 ((UINT32) Address, MmioBuffer->Data16);
      break;

    case RegWidth32:
      MrcCall->MrcMmioWrite32 ((UINT32) Address, MmioBuffer->Data32);
      break;

    case RegWidth64:
      MrcCall->MrcMmioWrite64 ((UINT32) Address, MmioBuffer->Data64);
      break;

    default:
      break;
  }
  return;
}

/**
  Reads a variable sized value from I/O.
  This function takes advantage of any caching implemented by BIOS.

  @param[in, out] This    - Interface pointer that implements the particular SSA_BIOS_SERVICES_PPI instance.
  @param[in]      Width   - The size of the value to write.
  @param[in]      Address - Address of the I/O to be accessed.
  @param[out]     Buffer  - Value storage location.

  @retval Nothing.
**/
VOID
(EFIAPI BiosReadIo) (
  SSA_BIOS_SERVICES_PPI *This,
  REG_WIDTH             Width,
  UINT32                Address,
  VOID                  *Buffer
  )
{
  MRC_FUNCTION  *MrcCall;
  IO_BUFFER     *IoBuffer;

  MrcCall  = ((MrcParameters *) This->SsaMemoryConfig->MrcData)->Inputs.Call.Func;
  IoBuffer = (IO_BUFFER *) Buffer;
  switch (Width) {
    case RegWidth8:
      IoBuffer->Data8 = MrcCall->MrcIoRead8 ((UINT16) Address);
      break;

    case RegWidth16:
      IoBuffer->Data16 = MrcCall->MrcIoRead16 ((UINT16) Address);
      break;

    case RegWidth32:
      IoBuffer->Data32 = MrcCall->MrcIoRead32 ((UINT16) Address);
      break;

    default:
      break;
  }
  return;
}

/**
  Writes a variable sized value to I/O.

  @param[in, out] This    - Interface pointer that implements the particular SSA_BIOS_SERVICES_PPI instance.
  @param[in]      Width   - The size of the value to write.
  @param[in]      Address - Address of the I/O to be accessed.
  @param[in]      Buffer  - Value to write.

  @retval Nothing.
**/
VOID
(EFIAPI BiosWriteIo) (
  SSA_BIOS_SERVICES_PPI *This,
  REG_WIDTH             Width,
  UINT32                Address,
  VOID                  *Buffer
  )
{
  MRC_FUNCTION  *MrcCall;
  IO_BUFFER     *IoBuffer;

  MrcCall  = ((MrcParameters *) This->SsaMemoryConfig->MrcData)->Inputs.Call.Func;
  IoBuffer = (IO_BUFFER *) Buffer;
  switch (Width) {
    case RegWidth8:
      MrcCall->MrcIoWrite8 ((UINT16) Address, IoBuffer->Data8);
      break;

    case RegWidth16:
      MrcCall->MrcIoWrite16 ((UINT16) Address, IoBuffer->Data16);
      break;

    case RegWidth32:
      MrcCall->MrcIoWrite32 ((UINT16) Address, IoBuffer->Data32);
      break;

    default:
      break;
  }
  return;
}

/**
  Reads a variable sized value from the PCI config space register.
  This function takes advantage of any caching implemented by BIOS.

  @param[in, out] This       - Interface pointer that implements the particular SSA_BIOS_SERVICES_PPI instance.
  @param[in]      Width      - The size of the value to write.
  @param[in]      Address    - Address of the I/O to be accessed. Must be modulo 'Width'.
  @param[out]     Buffer     - Value storage location.

  @retval Nothing.
**/
VOID
(EFIAPI BiosReadPci) (
  SSA_BIOS_SERVICES_PPI           *This,
  REG_WIDTH                       Width,
  EFI_PEI_PCI_CFG_PPI_PCI_ADDRESS *Address,
  VOID                            *Buffer
  )
{
  MrcInput          *Inputs;
  MRC_FUNCTION      *MrcCall;
  PCI_BUFFER        *PciBuffer;
  PCI_CONFIG_SPACE  PciAddress;
  UINT32            Value;

  Inputs                    = &((MrcParameters *) This->SsaMemoryConfig->MrcData)->Inputs;
  MrcCall                   = Inputs->Call.Func;
  PciBuffer                 = (PCI_BUFFER *) Buffer;
  PciAddress.Value          = Address->Register;
  PciAddress.Bits.Bus       = Address->Bus;
  PciAddress.Bits.Device    = Address->Device;
  PciAddress.Bits.Function  = Address->Function;
  PciAddress.Bits.Reserved0 = 0;
  PciAddress.Bits.Enable    = 1;
  MrcCall->MrcIoWrite32 (Inputs->PciIndex, PciAddress.Value);
  Value = MrcCall->MrcIoRead32 (Inputs->PciData);

  switch (Width) {
    case RegWidth8:
      PciBuffer->Data8 = (UINT8) Value;
      break;

    case RegWidth16:
      PciBuffer->Data16 = (UINT16) Value;
      break;

    case RegWidth32:
      PciBuffer->Data32 = Value;
      break;

    default:
      break;
  }

  return;
}

/**
  Writes a variable sized value to the PCI config space register.

  @param[in, out] This       - Interface pointer that implements the particular SSA_BIOS_SERVICES_PPI instance.
  @param[in]      Width      - The size of the value to write.
  @param[in]      Address    - Address of the I/O to be accessed. Must be modulo 'Width'.
  @param[in]      Buffer     - Value to write.

  @retval Nothing.
**/
VOID
(EFIAPI BiosWritePci) (
  SSA_BIOS_SERVICES_PPI           *This,
  REG_WIDTH                       Width,
  EFI_PEI_PCI_CFG_PPI_PCI_ADDRESS *Address,
  VOID                            *Buffer
  )
{
  MrcInput          *Inputs;
  MRC_IO_WRITE_32   MrcIoWrite32;
  PCI_BUFFER        *PciBuffer;
  PCI_CONFIG_SPACE  PciAddress;
  BOOLEAN           DoIt;
  UINT32            Value;

  Inputs                    = &((MrcParameters *) This->SsaMemoryConfig->MrcData)->Inputs;
  MrcIoWrite32              = Inputs->Call.Func->MrcIoWrite32;
  PciBuffer                 = (PCI_BUFFER *) Buffer;
  DoIt                      = TRUE;
  PciAddress.Value          = Address->Register;
  PciAddress.Bits.Bus       = Address->Bus;
  PciAddress.Bits.Device    = Address->Device;
  PciAddress.Bits.Function  = Address->Function;
  PciAddress.Bits.Reserved0 = 0;
  PciAddress.Bits.Enable    = 1;
  Value                     = 0;

  switch (Width) {
    case RegWidth8:
      BiosReadPci (This, RegWidth32, Address, (PCI_BUFFER *) &Value);
      Value &= ~0xFF;
      Value |= (UINT32) PciBuffer->Data8;
      break;

    case RegWidth16:
      BiosReadPci (This, RegWidth32, Address, (PCI_BUFFER *) &Value);
      Value &= ~0xFFFF;
      Value |= (UINT32) PciBuffer->Data16;
      break;

    case RegWidth32:
      Value = PciBuffer->Data32;
      break;

    default:
      Value = 0;
      DoIt  = FALSE;
      break;
  }

  if (DoIt) {
    MrcIoWrite32 (Inputs->PciIndex, PciAddress.Value);
    MrcIoWrite32 (Inputs->PciData, Value);
  }

  return;
}

/**
  Gets a base address to be used in the different memory map or MMIO register access functions.

  @param[in, out] This            - Interface pointer that implements the particular SSA_BIOS_SERVICES_PPI instance.
  @param[in]      Socket          - Zero based CPU socket number.
  @param[in]      Controller      - Zero based controller number.
  @param[in]      Index           - Additional index to locate the register.
  @param[in]      BaseAddressType - Value that indicates the type of base address to be retrieved.
  @param[out]     BaseAddress     - Where to write the base address

  @retval NotAvailable if the system does not support this feature.  Else UnsupportedValue if BaseAddressType is out of range.  Else Success.
**/
SSA_STATUS
(EFIAPI BiosGetBaseAddress) (
  SSA_BIOS_SERVICES_PPI *This,
  UINT8                 Socket,
  UINT8                 Controller,
  UINT8                 Index,
  BASE_ADDR_TYPE        BaseAddressType,
  EFI_PHYSICAL_ADDRESS  *BaseAddress
  )
{
  MrcParameters *MrcData;
  SSA_STATUS    SsaStatus;
  MrcStatus     Status;

  SsaStatus = UnsupportedValue;
#ifdef SSA_PARAM_ERROR_CHECK
  if (BaseAddress > 0)
#endif
  {
    MrcData = (MrcParameters *) This->SsaMemoryConfig->MrcData;
    switch (BaseAddressType) {
      case MCH_BAR:
        Status = IsControllerPresent (MrcData, Socket, Controller);
        if (Status == mrcSuccess) {
          *BaseAddress = MrcData->Inputs.MchBarBaseAddress;
          SsaStatus    = Success;
        }
        break;

      default:
        break;
    }
    SSA_DEBUG_MSG (&MrcData->Outputs.Debug, MSG_LEVEL_NOTE, "GetBaseAddress %u %u %u %u %u %08X\n", Socket, Controller, Index, BaseAddressType, SsaStatus, *BaseAddress);
  }
  return (SsaStatus);
}

/**
  Function used to dynamically allocate memory.

  @param[in, out] This - Interface pointer that implements the particular SSA_BIOS_SERVICES_PPI instance.
  @param[in]      Size - Amount of memory in bytes to allocate.

  @retval Returns a pointer to an allocated memory block on success or NULL on failure.
**/
VOID *
(EFIAPI BiosMalloc) (
  SSA_BIOS_SERVICES_PPI *This,
  UINT32                Size
  )
{
  MrcParameters  *MrcData;
  MrcInput       *Inputs;
  VOID           *Buffer;
#ifdef SSA_DEBUG_PRINT
  MrcVersion     Version;
#endif

  MrcData = (MrcParameters *) This->SsaMemoryConfig->MrcData;
  Inputs  = &MrcData->Inputs;
#ifdef SSA_DEBUG_PRINT
  MrcVersionGet (MrcData, &Version);
#endif
  if (Inputs->SerialBuffer > 0) {

    MrcHeapFree (MrcData, (void *) Inputs->SerialBuffer);
    Inputs->SerialBuffer = 0;
    MrcData->Outputs.Debug.Current = 0;
    SSA_DEBUG_MSG (&MrcData->Outputs.Debug, MSG_LEVEL_NOTE, "SSA has freed serial buffer\n");
  }
  Buffer = ((VOID *) MrcHeapMalloc (MrcData, Size));
  SSA_DEBUG_MSG (&MrcData->Outputs.Debug, MSG_LEVEL_NOTE, "BiosMalloc %u.%u.%u.%u %08X %u\n", Version.Major, Version.Minor, Version.Rev, Version.Build, Buffer, Size);
  return (Buffer);
}

/**
  Function used to release memory allocated using Malloc.

  @param[in, out] This   - Interface pointer that implements the particular SSA_BIOS_SERVICES_PPI instance.
  @param[in]      Buffer - The buffer to return to the free pool.

  @retval Nothing.
**/
VOID
(EFIAPI BiosFree) (
  SSA_BIOS_SERVICES_PPI *This,
  VOID                  *Buffer
  )
{
  MrcParameters  *MrcData;

  MrcData = (MrcParameters *) This->SsaCommonConfig->BiosData;
  SSA_DEBUG_MSG (&MrcData->Outputs.Debug, MSG_LEVEL_NOTE, "BiosFree %08Xh\n", Buffer);
  MrcHeapFree (MrcData, Buffer);
  return;
}

/**
  Function used to output debug messages to the output logging device.

  @param[in, out] This         - Interface pointer that implements the particular SSA_BIOS_SERVICES_PPI instance.
  @param[in]      PrintLevel   - The severity level of the string.
  @param[in]      FormatString - The reduced set of printf style format specifiers.
  @param          %[flags][width]type
  @param          [flags] '-' left align
  @param          [flags] '+' prefix with sign (+ or -)
  @param          [flags] '0' zero pad numbers
  @param          [flags] ' ' prefix blank in front of postive numbers
  @param          [flags] 'l' used with x, X, u, d, i types to indicate 64-bit value.
  @param          [flags] ','|'_' used with x, X, u, d, i types to add comma (dec) or underscore (hex) to display value. Specify after 'l' flag when 'l' flag is used.
  @param          [width] non negative decimal integer that specifies the width to print a value.
  @param          [width] '*' get the width from a int argument on the stack.
  @param          type    'd'|'i' signed decimal integer
  @param          type    'u' unsigned integer
  @param          type    'x'|'X' hexadecimal using "ABCDEF"
  @param          type    'c' print character
  @param          type    'p' print a pointer to void
  @param          type    's' print a null terminated string
  @param          type    '%%' prints a percent sign
  @param[in]      ...          - Variable list of output values.

  @retval Nothing.
**/
VOID
(EFIAPI BiosSsaDebugPrint) (
  SSA_BIOS_SERVICES_PPI *This,
  PRINT_LEVEL           PrintLevel,
  UINT8                 *FormatString,
  ...
  )
{
#ifdef MRC_DEBUG_PRINT
  MRC_FUNCTION   *MrcCall;
  MrcVaList      Marker;
  char           Buffer[MAX_STRING_LENGTH];

  if (PrintLevel <= This->SsaCommonConfig->CurrentPrintLevel) {
    if (FormatString != NULL) {
      VA_START (Marker, FormatString);
      MrcCall = ((MrcParameters *) This->SsaMemoryConfig->MrcData)->Inputs.Call.Func;
      if (StringFormatter (MrcCall, (const char *const) FormatString, Marker, sizeof (Buffer), (UINT8 *) &Buffer[0]) > 0) {
#ifdef MRC_MINIBIOS_BUILD
        MrcPuts (Buffer);
#else
        DEBUG ((PrintLevel, Buffer));
#endif
      }
    }
  }
#endif

  return;
}

/**
  Function used to stall the software progress for the given period of time.

  @param[in, out] This  - Interface pointer that implements the particular SSA_BIOS_SERVICES_PPI instance.
  @param[in]      Delay - The amount of time to wait, in microseconds.

  @retval Nothing.
**/
VOID
(EFIAPI BiosWait) (
  SSA_BIOS_SERVICES_PPI *This,
  UINT32                Delay
  )
{
  MrcWait ((MrcParameters *const) (This->SsaCommonConfig->BiosData), Delay * HPET_1US);
  return;
}

/**
  Function used to add data to the BDAT v4 or later structure that will be created by BIOS in reserved physical memory.

  @param[in, out] This        - Interface pointer that implements the particular SSA_BIOS_SERVICES_PPI instance.
  @param[in]      SchemaGuid  - The Schema ID GUID.  This is a unique identifier that indicates the format of the data to be added to the BDAT structure.
  @param[in]      Data        - The location of the data block to add to the BDAT structure.
  @param[in]      DataSize    - The size of the data to be added to the BDAT structure in bytes.

  @retval NotAvailable if the system does not support this feature.  Else OutOfMemory if there is insufficient memory to add the data to the structure.  Else Success.
**/
SSA_STATUS
(EFIAPI BiosSaveToBdat) (
  SSA_BIOS_SERVICES_PPI *This,
  EFI_GUID              *SchemaGuid,
  CONST UINT8           *Data,
  UINT32                DataSize
  )
{
  SSA_STATUS                       SsaStatus = NotAvailable;
#ifdef BDAT_SUPPORT
#ifndef MRC_MINIBIOS_BUILD
  MrcParameters                    *MrcData;
  MRC_FUNCTION                     *MrcCall;
  MrcInput                         *Inputs;
  MrcOutput                        *Outputs;
  MRC_BDAT_SCHEMA_HEADER_STRUCTURE *BdatSchemaHdrPtr;
  UINT16                           NextSchema;
  UINT8                            Index;

  MrcData   = (MrcParameters *) This->SsaMemoryConfig->MrcData;
  Inputs    = &MrcData->Inputs;
  Outputs   = &MrcData->Outputs;
  MrcCall   = Inputs->Call.Func;
  Index     = 0;

#ifdef SSA_PARAM_ERROR_CHECK
  SsaStatus = EfiGuidCheck (This, SchemaGuid);
  if (SsaStatus == Success) {
    SsaStatus = NotAvailable;
    if ((Data == NULL) || (DataSize == 0)) {
      SsaStatus = UnsupportedValue;
      //
      // This function requires BDAT v4.0 support.
      //
    } else
#endif
    {
#if ((defined RMT_PRIMARY_VERSION) && (RMT_PRIMARY_VERSION > 3))
      for (Index = 0; Index < MAX_SCHEMA_LIST_LENGTH; Index++) {
        if (Outputs->BdatMemoryHob[Index].Pointer == NULL) {
          break;
        }
      }
      if ((Index < MAX_SCHEMA_LIST_LENGTH) && (Outputs->BdatSchemasHob.Pointer != NULL)) {
        if (EFI_SUCCESS == MrcGetHobForDataStorage (
                             (VOID **)&Outputs->BdatMemoryHob[Index].Pointer,
                             (UINT16) (DataSize + sizeof (MRC_BDAT_SCHEMA_HEADER_STRUCTURE) + sizeof (EFI_HOB_GUID_TYPE)),
                             SchemaGuid)) {
          SSA_DEBUG_MSG (&MrcData->Outputs.Debug, MSG_LEVEL_NOTE, "HOB at %08Xh\n", Outputs->BdatMemoryHob[Index]);
          NextSchema = Outputs->BdatSchemasHob.Pointer->SchemaHobCount;
          Outputs->BdatSchemasHob.Pointer->SchemaHobCount = NextSchema + 1;
          MrcCall->MrcCopyMem ((UINT8 *) &(Outputs->BdatSchemasHob.Pointer->SchemaHobGuids[NextSchema]), (UINT8 *) SchemaGuid, sizeof (EFI_GUID));
          BdatSchemaHdrPtr = (MRC_BDAT_SCHEMA_HEADER_STRUCTURE *) &((Outputs->BdatMemoryHob[Index].Pointer)->MemorySchema);
          MrcCall->MrcCopyMem ((UINT8 *) &BdatSchemaHdrPtr->SchemaId, (UINT8 *) SchemaGuid, sizeof (EFI_GUID));
          BdatSchemaHdrPtr->DataSize = DataSize;
          GetDimmCrc ((UINT8 *) BdatSchemaHdrPtr, sizeof (MRC_BDAT_SCHEMA_HEADER_STRUCTURE), &BdatSchemaHdrPtr->Crc16);
          MrcCall->MrcCopyMem (((UINT8 *) &((Outputs->BdatMemoryHob[Index].Pointer)->MemorySchema)) + sizeof (MRC_BDAT_SCHEMA_HEADER_STRUCTURE), (UINT8 *) Data, DataSize);
          SsaStatus = Success;
        }
      }
#endif
    }
#ifdef SSA_PARAM_ERROR_CHECK
  }
#endif
  SSA_DEBUG_MSG (&MrcData->Outputs.Debug, MSG_LEVEL_NOTE, "SaveToBdat %Xh %Xh %u %u\n", SchemaGuid, Data, DataSize, SsaStatus);
#endif
#endif
  return (SsaStatus);
}

/**
  This function to register a new handler for a hook.

  @param[in, out] This        - Interface pointer that implements the particular SSA_BIOS_SERVICES_PPI instance.
  @param[in]      HookGuid    - GUID defining the hook to invoke the handlers for.
  @param[in]      HookHandler - Function pointer to the new hook handler. This hook handler will be invoked whenever a corresponding call to RunHook() is made with the correct hook GUID.

  @retval NotAvailable if the system does not support this feature.  Else OutOfMemory if unable to allocate a buffer to store the hook.  Else Success.
**/
SSA_STATUS
(EFIAPI BiosRegisterHookHandler) (
  SSA_BIOS_SERVICES_PPI *This,
  VOID                  *HookGuid,
  SSA_BIOS_HOOK_HANDLER HookHandler
  )
{
  UINT32 Ptr;

  Ptr = (UINT32) HookHandler;
  SSA_DEBUG_MSG (
    &((MrcParameters *) This->SsaMemoryConfig->MrcData)->Outputs.Debug,
    MSG_LEVEL_NOTE,
    "RegisterHookHandler %08Xh %08Xh %08Xh\n",
    HookGuid,
    HookHandler,
    (UINT32) HookHandler
    );
  return (AddToHookHandler (This, HookGuid, HookHandlerTypeFunction, (VOID *) Ptr));
}

/**
  This function invokes all registered handlers for a specific hook.

  @param[in, out] This        - Interface pointer that implements the particular SSA_BIOS_SERVICES_PPI instance.
  @param[in]      HookGuid    - GUID defining the hook to invoke the handlers for.
  @param[in]      Parameters  - Data passed to the hook handlers. The type and format of this data differs depending on what hook is being invoked.  The type and format of the data must be the same as all other cases where RunHook() is called with a specific hook GUID.  This value can be NULL if the hook does not pass any additional data.

  @retval Success when all hook handlers are successfully invoked. Else Failure.
**/
SSA_STATUS
(EFIAPI BiosRunHook) (
  SSA_BIOS_SERVICES_PPI *This,
  VOID                  *HookGuid,
  VOID                  *Parameters
  )
{
  SSA_STATUS    SsaStatus;
  UINT32        HookPointer;

  SsaStatus = GetHookHandler (This, HookGuid, HookHandlerTypeFunction, &HookPointer);
  if (Success == SsaStatus) {
    SSA_DEBUG_MSG (
      &((MrcParameters *) This->SsaMemoryConfig->MrcData)->Outputs.Debug,
      MSG_LEVEL_NOTE,
      "RunHook calls %08Xh with %08Xh, ",
      HookPointer,
      Parameters
      );
    (*((SSA_BIOS_HOOK_HANDLER) HookPointer)) (This, Parameters);
  }
  return (SsaStatus);
}

/**
  This function saves a pointer into a table that can later be retrieved.

  @param[in, out] This        - Interface pointer that implements the particular SSA_BIOS_SERVICES_PPI instance.
  @param[in]      PointerId   - GUID that uniquely identifies the pointer.
  @param[in]      Pointer     - The pointer to save.

  @retval NotAvailable if the system does not support this feature.  Else Success when the pointer is successfully saved.  Else Failure.
**/
SSA_STATUS
(EFIAPI BiosSaveDataPointer) (
  SSA_BIOS_SERVICES_PPI *This,
  EFI_GUID              *PointerId,
  VOID                  *Pointer
  )
{
  SSA_DEBUG_MSG (
    &((MrcParameters *) This->SsaMemoryConfig->MrcData)->Outputs.Debug,
    MSG_LEVEL_NOTE,
    "SaveDataPointer %08Xh %08Xh\n",
    PointerId,
    Pointer
    );
  return (AddToHookHandler (This, PointerId, HookHandlerTypeData, Pointer));
}

/**
  This function returns a pointer that was earlier saved using SaveDataPointer function.

  @param[in, out] This        - Interface pointer that implements the particular SSA_BIOS_SERVICES_PPI instance.
  @param[in]      PointerId   - GUID that uniquely identifies the pointer.

  @retval The value of the pointer or NULL if the pointer for the specified GUID does not exist.
**/
VOID *
(EFIAPI BiosRestoreDataPointer) (
  SSA_BIOS_SERVICES_PPI *This,
  EFI_GUID              *PointerId
  )
{
  SSA_STATUS    SsaStatus;
  UINT32        HookPointer;

  SSA_DEBUG_MSG (
    &((MrcParameters *) This->SsaMemoryConfig->MrcData)->Outputs.Debug,
    MSG_LEVEL_NOTE,
    "RestoreDataPointer entry, %08Xh\n",
    PointerId
    );
  SsaStatus = GetHookHandler (This, PointerId, HookHandlerTypeData, &HookPointer);
  return ((Success == SsaStatus) ? (VOID *) HookPointer : NULL);
}

/**
  This function disables the watchdog timer.

  @param[in, out] This - Interface pointer that implements the particular SSA_BIOS_SERVICES_PPI instance.

  @retval Nothing.
**/
VOID
(EFIAPI BiosDisableWatchdogTimer) (
  SSA_BIOS_SERVICES_PPI *This
  )
{
}

/**
  Function used to get the elapsed time since the last CPU reset in milliseconds.

  @param[in, out] This      - Interface pointer that implements the particular SSA_BIOS_SERVICES_PPI instance.
  @param[out]     Timestamp - Pointer to were the elapsed time since the last CPU reset in milliseconds will be written.

  @retval Nothing.
**/
VOID
(EFIAPI BiosGetTimestamp) (
  SSA_BIOS_SERVICES_PPI *This,
  UINT32                *Timestamp
  )
{
  MrcParameters *MrcData;

  MrcData = (MrcParameters *) This->SsaMemoryConfig->MrcData;
#ifdef SSA_PARAM_ERROR_CHECK
  if (Timestamp == NULL) {
    return;
  }
#endif
  *Timestamp = (UINT32) MrcData->Inputs.Call.Func->MrcGetCpuTime (MrcData);
  SSA_DEBUG_MSG (
    &MrcData->Outputs.Debug,
    MSG_LEVEL_NOTE,
    "GetTimestamp, %08Xh\n",
    *Timestamp
    );
  return;
}

#endif // SSA_FLAG
// end file BiosSsaCommonConfig.c
