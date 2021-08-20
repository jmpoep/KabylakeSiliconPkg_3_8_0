/** @file
  This file contains the main entry point for the MRC mini-BIOS.

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

#include "MrcTypes.h"
#include "MrcApi.h"
#include "MrcInterface.h"
#include "MrcCommon.h"
#include "uart16550.h"
#include "crc.h"
#include "McAddress.h"
#include "MrcDebugHook.h"
#include "MrcStartMemoryConfiguration.h"
#include "MrcGeneral.h"
#include "MrcOemPlatform.h"
#include "MemoryUtils.h"
#include "MrcInterpreter.h"
#include "PchRegsPcr.h"
#include "PchRegsDmi.h"
#include "MrcMalloc.h"
#ifdef SSA_FLAG
#include "MrcSsaInitialize.h"
#endif
#define MAX_HEAP_SIZE (32 * 1024)

#define REBOOT_TEST 0


#include "PlatformBoardId.h"

//
// CPU Family and Stepping Masks
//
#define CPU_FAMILY_MASK   0xFFFFFFF0
#define CPU_STEPPING_MASK 0x0000000F

//
// Internal module definitions
//
typedef struct {
  UINT32 MmioWritePtr;
  UINT32 MmioReadPtr;
  UINT32 NextAllocation;
} TMallocParams;


typedef struct {
  UINT32 Start;
  UINT32 End;
} TTimeParams;

///
/// Define the MRC SMBUS devices type.
///
typedef enum {
  datOemSpd_0_0,      ///< use for get the device address for channel 0 dimm 0
  datOemSpd_0_1,      ///< use for get the device address for channel 0 dimm 1
  datOemSpd_1_0,      ///< use for get the device address for channel 1 dimm 0
  datOemSpd_1_1,      ///< use for get the device address for channel 1 dimm 1
  datOemVrefWrite_0,  ///< use for get the device address for dimm vref controlled potentiometer channel 0
  datOemVrefWrite_1,  ///< use for get the device address for dimm vref controlled potentiometer channel 1
  datOemVrefRead      ///< use for get the device address for cpu vref controlled potentiometer
} MRC_OemSmbusDeviceType;

const UINT8 MrcDataStringConst[] = "MRCD";
const UINT8 MrcSpdStringConst[]  = "SPD ";

//
// In full BIOS these are defined in KabylakeSiliconPkg/SiPkg.dec
//
EFI_GUID gEfiMemorySchemaGuid  = { 0xCE3F6794, 0x4883, 0x492C, { 0x8D, 0xBA, 0x2F, 0xC0, 0x98, 0x44, 0x77, 0x10 }};
EFI_GUID gMrcSchemaListHobGuid = { 0x3047C2AC, 0x5E8E, 0x4C55, { 0xA1, 0xCB, 0xEA, 0xAD, 0x0A, 0x88, 0x86, 0x1B }};
EFI_GUID gRmtResultMetadataGuid = { 0x02CB1552, 0xD659, 0x4232, { 0xB5, 0x1F, 0xCA, 0xB1, 0xE1, 0x1F, 0xCA, 0x87}};
EFI_GUID gRmtResultColumnsGuid  = { 0x0E60A1EB, 0x331F, 0x42A1, { 0x9D, 0xE7, 0x45, 0x3E, 0x84, 0x76, 0x11, 0x54}};
EFI_GUID gMargin2DResultMetadataGuid = { 0x48265582, 0x8E49, 0x4AC7, { 0xAA, 0x06, 0xE1, 0xB9, 0xA7, 0x4C, 0x97, 0x16}};
EFI_GUID gMargin2DResultColumnsGuid  = { 0x91A449EC, 0x8A4A, 0x4736, { 0xAD, 0x71, 0xA3, 0xF6, 0xF6, 0xD7, 0x52, 0xD9}};



//
// Internal functions.
//
static
void
init_malloc (
  CPU_SETUP_OPTIONS *Input
  );

static
UINT8
MrcOemGetSmBusDeviceAddress (
  MrcParameters *const    MrcData,
  UINT16                  BoardId,
  MRC_OemSmbusDeviceType  SmbusDeviceType
  );

extern
UINT32
OemMemoryBase (
  void
  );

BOOLEAN
MrcIsTxtProcessor (
  void
  );

BOOLEAN
MrcIsTxtChipset (
  void
  );

UINT16
MrcGetBoardId (
  MrcParameters *const MrcData,
  BOOLEAN       *const SpdPresent
  );

void
MrcMSRWrite (
  UINT32 Index,
  UINT32 ValueH,
  UINT32 ValueL
  );

UINT32
MrcCPUStepGet (
  void
  );

void
GPIOBaseEnable (
  void
  );

/**
  Print IA32 exception number / name and CS:EIP that caused the exception.

  @param[in] Exception - exception type number
  @param[in] RegCs     - CS of the exception
  @param[in] RegEip    - EIP of the exception

**/
void
_PrintExceptionDetails (
  UINT32 Exception,
  UINT32 RegCs,
  UINT32 RegEip
  )
{
#ifdef MRC_DEBUG_PRINT
  UINT8 Str[16];
  static const char UnknownStr[] = "Unknown";
  static const char *ExceptionName[20] = {
    "#DE - Divide Error",
    "#DB - Reserved",
    "NMI Interrupt",
    "#BP - Breakpoint",
    "#OF - Overflow",
    "#BR - BOUND Range Exceeded",
    "#UD - Invalid Opcode (Undefined  Opcode)",
    "#NM - Device Not Available (No Math Coprocessor)",
    "#DF - Double Fault",
    "Coprocessor Segment Overrun (reserved)",
    "#TS - Invalid TSS",
    "#NP - Segment Not Present",
    "#SS - Stack-Segment Fault",
    "#GP - General Protection Fault",
    "#PF - Page Fault",
    "Reserved",
    "#MF - x87 FPU Floating-Point Error (Math Fault)",
    "#AC - Alignment Check",
    "#MC - Machine Check",
    "#XM - SIMD floating point exception"
  };

  MrcOemMemorySet (&Str[0], sizeof (Str), 0);
  MrcPuts ("!!!! IA32 Exception Type - 0x");
  UintnToStr ((const MRC_FUNCTION *) NULL, Exception, sizeof (UINT32), (char *) &Str[0], 2, MRC_PREFIX_ZERO, 16);
  MrcPuts ((const char *) Str);
  MrcPuts (": ");

  if (Exception < 20) {
    MrcPuts (ExceptionName[Exception]);
  } else {
    MrcPuts (UnknownStr);
  }

  MrcPuts ("\r\nAt CS:EIP = 0x");
  MrcOemMemorySet (&Str[0], sizeof (Str), 0);
  UintnToStr ((const MRC_FUNCTION *) NULL, RegCs, sizeof (UINT32), (char *) &Str[0], 4, MRC_PREFIX_ZERO, 16);
  MrcPuts ((const char *) Str);
  MrcPuts (":0x");
  MrcOemMemorySet (&Str[0], sizeof (Str), 0);
  UintnToStr ((const MRC_FUNCTION *) NULL, RegEip, sizeof (UINT32), (char *) &Str[0], 8, MRC_PREFIX_ZERO, 16);
  MrcPuts ((const char *) Str);
  MrcPuts (" !!!!\r\n");
#endif
}

/**

Routine description:

  Prints the stack depth reached by MiniBIOS.  Called from assembly.
  Assumes this is called after _prepareToCallMemRefCode().
  Todo: If heap is used in MiniBIOS, this causes stack depth function
  to return a value near to full stack size, incorrectly reporting stack usage.

Arguments:

  StackDepth - The amount of stack used

Returns

  Nothing.

**/
void
_printStackDepth (
  UINT32 StackDepth
  )
{
#ifdef MRC_DEBUG_PRINT
  UINT8 Str[16];

  MrcOemMemorySet ((UINT8 *) &Str[0], sizeof (Str), 0);
  UintnToStr ((const MRC_FUNCTION *) NULL, StackDepth, sizeof (UINT32), (char *) &Str[0], 0, 0, 10);
  MrcPuts ((const char *) Str);
  MrcPuts (" (");
  MrcOemMemorySet ((UINT8 *) &Str[0], sizeof (Str), 0);
  UintnToStr ((const MRC_FUNCTION *) NULL, StackDepth, sizeof (UINT32), (char *) &Str[0], 0, 0, 16);
  MrcPuts ((const char *) Str);
  MrcPuts ("h)\r\n");
#endif
  return;
}

static
void
Dummy (
  void
  )
{
  return;
}

UINT32
_prepareToCallMemRefCode (
  CPU_SETUP_OPTIONS *Input
  )
/**

Routine Description:

  Main starting point for the Mini-BIOS MRC.

Arguments:

  Input - Various input options.

Returns:

  mrcSuccess or failure indication.

**/
{
  MrcParameters                 *MrcData;
  MrcControllerIn               *ControllerIn;
  MrcChannelIn                  *ChannelIn;
  MrcDimmIn                     *DimmIn;
  MRC_FUNCTION                  CallTableFunc;
  MRC_FUNCTION                  *MrcCall;
  MrcStatus                     Status;
  UINT32                        MchBarBaseAddress;
  UINT32                        PciEBaseAddress;
  UINT32                        SmbusBaseAddress;
  NCDECS_CR_GDXCBAR_NCU_STRUCT  GdxcBaseAddress;
  UINT32                        HpetBaseAddress;
  TMallocParams                 *MallocParams;
  MrcInput                      *Inputs;
  MrcOutput                     *Outputs;
  MrcIntOutput                  *IntOutputs;
  MrcDebug                      *Debug;
  UINT32                        CpuModelStep;
  UINT32                        DeviceId;
  BOOLEAN                       UlxUlt;
  BOOLEAN                       HasEdram;
  BOOLEAN                       SpdPresent;
  UINT32                        Crc32;
  UINT32                        DmiBar;
  UINT32                        Value;
  PCIE_CR_OPIO_RX_DLL_GLOBAL3_STRUCT  RxDllGlobal3;
  UINT16                        BoardId;
  UINT16                        SAFE;
  UINT8                         Controller;
  UINT8                         Channel;
  UINT8                         Dimm;
  UINT8                         Index;
  MrcIntOutput                  MrcIntGlobalData;
  MrcParameters                 GlobalData;

  Init16550Uart ();
  init_malloc (Input);

  MrcOemMemorySet ((UINT8 *) &GlobalData, sizeof (MrcParameters), 0);
  MrcOemMemorySet ((UINT8 *) &MrcIntGlobalData, sizeof (MrcIntOutput), 0);
  MrcData                                         = &GlobalData;
  Inputs                                          = &MrcData->Inputs;
  Inputs->Call.Func                               = &CallTableFunc;
  MrcCall                                         = Inputs->Call.Func;
  IntOutputs                                      = &MrcIntGlobalData;
  MrcData->IntOutputs.Internal                    = IntOutputs;
  Outputs                                         = &MrcData->Outputs;
  Debug                                           = &Outputs->Debug;
  MrcCall->MrcIoRead8                             = (MRC_IO_READ_8) (&MrcOemInPort8);
  MrcCall->MrcIoRead16                            = (MRC_IO_READ_16) (&MrcOemInPort16);
  MrcCall->MrcIoRead32                            = (MRC_IO_READ_32) (&MrcOemInPort32);
  MrcCall->MrcIoWrite8                            = (MRC_IO_WRITE_8) (&MrcOemOutPort8);
  MrcCall->MrcIoWrite16                           = (MRC_IO_WRITE_16) (&MrcOemOutPort16);
  MrcCall->MrcIoWrite32                           = (MRC_IO_WRITE_32) (&MrcOemOutPort32);
  MrcCall->MrcMmioRead8                           = (MRC_MMIO_READ_8) (&MrcOemMmioRead8);
  MrcCall->MrcMmioRead16                          = (MRC_MMIO_READ_16) (&MrcOemMmioRead16);
  MrcCall->MrcMmioRead32                          = (MRC_MMIO_READ_32) (&MrcOemMmioRead32);
  MrcCall->MrcMmioRead64                          = (MRC_MMIO_READ_64) (&SaMmioRead64);
  MrcCall->MrcMmioWrite8                          = (MRC_MMIO_WRITE_8) (&MrcOemMmioWrite8);
  MrcCall->MrcMmioWrite16                         = (MRC_MMIO_WRITE_16) (&MrcOemMmioWrite16);
  MrcCall->MrcMmioWrite32                         = (MRC_MMIO_WRITE_32) (&MrcOemMmioWrite32);
  MrcCall->MrcMmioWrite64                         = (MRC_MMIO_WRITE_64) (&SaMmioWrite64);
  MrcCall->MrcSmbusRead8                          = (MRC_SMBUS_READ_8) (&SmBusReadDataByte);
  MrcCall->MrcSmbusRead16                         = (MRC_SMBUS_READ_16) (&SmBusReadDataWord);
  MrcCall->MrcSmbusWrite8                         = (MRC_SMBUS_WRITE_8) (&SmBusWriteDataByte);
  MrcCall->MrcSmbusWrite16                        = (MRC_SMBUS_WRITE_16) (&SmBusWriteDataWord);
  MrcCall->MrcGetPciDeviceAddress                 = (MRC_GET_PCI_DEVICE_ADDRESS) (&GetPciDeviceAddress);
  MrcCall->MrcGetPcieDeviceAddress                = (MRC_GET_PCIE_DEVICE_ADDRESS) (&GetPcieDeviceAddress);
  MrcCall->MrcGetRtcTime                          = (MRC_GET_RTC_TIME) (&GetRtcTime);
  MrcCall->MrcGetCpuTime                          = (MRC_GET_CPU_TIME) (&GetCpuTime);
  MrcCall->MrcCopyMem                             = (MRC_MEMORY_COPY) (&MrcOemMemoryCpy);
  MrcCall->MrcSetMem                              = (MRC_MEMORY_SET_BYTE) (&SetMem);
  MrcCall->MrcSetMemWord                          = (MRC_MEMORY_SET_WORD) (&SetMemWord);
  MrcCall->MrcSetMemDword                         = (MRC_MEMORY_SET_DWORD) (&SetMemDword);
  MrcCall->MrcLeftShift64                         = (MRC_LEFT_SHIFT_64) (&LShiftU64);
  MrcCall->MrcRightShift64                        = (MRC_RIGHT_SHIFT_64) (&RShiftU64);
  MrcCall->MrcMultU64x32                          = (MRC_MULT_U64_U32) (&MultU64x32);
  MrcCall->MrcDivU64x64                           = (MRC_DIV_U64_U64) (&DivU64x64Remainder);
  MrcCall->MrcGetSpdData                          = (MRC_GET_SPD_DATA) (&GetSpdData);
  MrcCall->MrcGetRandomNumber                     = (MRC_GET_RANDOM_NUMBER) (&GetRandomNumber32);
  MrcCall->MrcCpuMailboxRead                      = (MRC_CPU_MAILBOX_READ) (&MailboxRead);
  MrcCall->MrcCpuMailboxWrite                     = (MRC_CPU_MAILBOX_WRITE) (&MailboxWrite);
  MrcCall->MrcGetMemoryVdd                        = (MRC_GET_MEMORY_VDD) (&GetMemoryVdd);
  MrcCall->MrcSetMemoryVdd                        = (MRC_SET_MEMORY_VDD) (&SetMemoryVdd);
  MrcCall->MrcCheckpoint                          = (MRC_CHECKPOINT) (&CheckPoint);
  MrcCall->MrcDebugHook                           = (MRC_DEBUG_HOOK) (&MrcOemDebugHook);
#ifdef MRC_DEBUG_PRINT
  MrcCall->MrcPrintString                         = (MRC_PRINT_STRING) (&MrcPuts);
#else
  MrcCall->MrcPrintString                         = (MRC_PRINT_STRING) (&Dummy);
#endif
  MrcCall->MrcRtcCmos                             = (MRC_GET_RTC_CMOS) (&RtcRead);
  MrcCall->MrcReadMsr64                           = (MRC_MSR_READ_64) (&ReadMsr64);
  MrcCall->MrcWriteMsr64                          = (MRC_MSR_WRITE_64) (&WriteMsr64);
  MrcCall->MrcReturnFromSmc                       = (MRC_RETURN_FROM_SMC) (&Dummy);
  MrcCall->MrcDramReset                           = (MRC_DRAM_RESET) (&MrcOemDramReset);
  MrcCall->MrcSetLockPrmrr                        = (MRC_SET_LOCK_PRMRR) (&MrcSetUncorePrmrr);
  MrcCall->MrcTxtAcheck                           = (MRC_TXT_ACHECK) (&Dummy);
  Inputs->PciIndex                                = 0xCF8;
  Inputs->PciData                                 = 0xCFC;
  MrcData->MrcDataSize                            = sizeof (MrcParameters);
  MrcData->Save.Size                              = sizeof (MrcSave);
  MrcData->Inputs.Header.GuidHob.Header.HobLength = sizeof (MrcInput);
  Outputs->Size                                   = sizeof (MrcOutput);
  IntOutputs->Size                                = sizeof (MrcIntOutput);
  MrcCall->MrcCopyMem ((UINT8 *) &MrcData->MrcDataString[0], (UINT8 *) MrcDataStringConst, sizeof (MrcData->MrcDataString));
  SAFE = 0;

  Inputs->DebugLevel  = MSG_LEVEL_CSV;  // Everything excluding MSG_LEVEL_TIME
  Inputs->DebugStream = 1;
  //
  // Top of stack at the beginning of MRC - for stack usage calculations.
  // Don't count IDT table and the heap buffer - they are specific to MiniBios.
  //
  Inputs->MrcStackTop = Input->nem_data_addr + Input->nem_data_size - 21 * 8 - MAX_HEAP_SIZE;

  MRC_DEBUG_MSG_OPEN (MrcData, Inputs->DebugLevel, Inputs->DebugStream, Inputs->SerialBuffer, Inputs->SerialBufferSize);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "MiniBIOS MRC hello world\n");
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "NemData Address/Size: 0x%x / 0x%x\n",Input->nem_data_addr, Input->nem_data_size);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "TopStackAddr: 0x%x\n", Debug->TopStackAddr);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "sizeof (MrcParameters): %6d\n", sizeof (MrcParameters));
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "  sizeof (MrcInput):    %6d\n", sizeof (MrcInput));
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "  sizeof (MrcOutput):   %6d\n", sizeof (MrcOutput));
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "  sizeof (MrcSave):     %6d\n", sizeof (MrcSave));
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "sizeof (MrcIntOutput):  %6d\n", sizeof (MrcIntOutput));

  //
  // Clear the high port80 byte.
  //
  MrcOemOutPort16 (0x80, 0);

  //
  // Check that MCHBAR is programmed
  //
  MrcCall->MrcIoWrite32 (Inputs->PciIndex, MrcCall->MrcGetPciDeviceAddress (0, 0, 0, UNCORE_CR_MCHBAR_0_0_0_PCI_REG));
  MchBarBaseAddress = MrcCall->MrcIoRead32 (Inputs->PciData);

  if ((MchBarBaseAddress & MRC_BIT0) == MRC_BIT0) {
    MchBarBaseAddress &= (~MRC_BIT0);
  } else {
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "MCHBAR is not programmed!\n");
    return mrcFail;
  }

  //
  // Check that PCIEXBAR is programmed
  //
  MrcCall->MrcIoWrite32 (Inputs->PciIndex, MrcCall->MrcGetPciDeviceAddress (0, 0, 0, UNCORE_CR_PCIEXBAR_0_0_0_PCI_REG));
  PciEBaseAddress = MrcCall->MrcIoRead32 (Inputs->PciData);


  if ((PciEBaseAddress & MRC_BIT0) == MRC_BIT0) {
    PciEBaseAddress &= (~MRC_BIT0);
  } else {
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "PCIEXBAR is not programmed!\n");
    return mrcFail;
  }

  Inputs->MchBarBaseAddress = MchBarBaseAddress;
  Inputs->PciEBaseAddress   = PciEBaseAddress;

  MrcDisablePciePorts (MrcData);

  MrcOemDebugHook (MrcData, MRC_INITIALIZATION_START);

  //
  // Determine the CPU and stepping
  //
  CpuModelStep = MrcCPUStepGet ();
  Inputs->CpuidModel    = CpuModelStep & CPU_FAMILY_MASK;
  Inputs->CpuidStepping = CpuModelStep & CPU_STEPPING_MASK;
  Status = MrcSetCpuInformation (MrcData, Inputs->CpuidModel, Inputs->CpuidStepping);
  if (Status != mrcSuccess) {
    MRC_DEBUG_MSG (
      Debug,
      MSG_LEVEL_ERROR,
      "ERROR: CPU Family/Model/Step %Xh is not supported.  Continuing as KBL ULX/ULT last known stepping: %Xh.\n",
      CpuModelStep,
      csKblUlxUltLast
      );
    Inputs->CpuModel    = cmKBL_ULX_ULT;
    Inputs->CpuStepping = csKblUlxUltLast;
    Inputs->CpuFamily   = cfKbl;
  }
  UlxUlt   = ((Inputs->CpuModel == cmSKL_ULX_ULT) || (Inputs->CpuModel == cmKBL_ULX_ULT));
  HasEdram = ((AsmReadMsr64 (MSR_PLATFORM_INFO) & B_PLATFORM_INFO_EDRAM_EN) != 0);
  //
  // Check that Hpet Base Address is programmed
  // TODO: Need to add code to check for RCBA base and the check HPTC and HPGC registers
  HpetBaseAddress = 0xFED00000;

  //
  // Check that SMBUS Base Address is programmed
  //
  SmbusBaseAddress = GetSmBusBaseAddress ();
  if (SmbusBaseAddress == 0) {
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "SMBUS base address is not programmed!\n");
    return mrcFail;
  }
  GPIOBaseEnable ();
  MrcOemGpioInit (MrcData);
  Inputs->SmbusBaseAddress       = SmbusBaseAddress;
  Inputs->HpetBaseAddress        = HpetBaseAddress;

  //
  // Scrambler Suppport.
  //
  Inputs->ScramblerEnable        = TRUE;
  //
  // Remap above 4G Support
  //
  Inputs->RemapEnable            = TRUE;

  Inputs->VddVoltage             = VDD_INVALID;   // Based on SPD
  Inputs->VddSettleWaitTime      = 0;             // Additive latency to the 200us default.  0 us by default

  //
  // Get VccIO value:
  // SKL ULT/ULX: 0.85v/0.95v, according to PCIE_CR_OPIO_RX_DLL_GLOBAL3[31:30]
  // SKL DT/Halo: 0.95v always
  //
  Inputs->VccIomV = 950;
  if (UlxUlt) {
    DmiBar = (MrcCall->MrcMmioRead32 (Inputs->PciEBaseAddress + UNCORE_CR_DMIBAR_0_0_0_PCI_REG)) & ~BIT0;
    if (DmiBar == 0) {
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "DMIBAR is not programmed!\n");
      return mrcFail;
    }
    RxDllGlobal3.Data = MrcCall->MrcMmioRead32 (DmiBar + PCIE_CR_OPIO_RX_DLL_GLOBAL3_REG);
    if (RxDllGlobal3.Bits.select_vccio_level == 0) {
      Inputs->VccIomV = 850;
    }
  }

  Inputs->McLock                 = TRUE;

  //
  // Check that Gdxc Base Address is programmed
  //
  GdxcBaseAddress.Data = MrcCall->MrcMmioRead64 (Inputs->MchBarBaseAddress + NCDECS_CR_GDXCBAR_NCU_REG);
  if (GdxcBaseAddress.Bits.GDXCBAREN != 0) {
    Inputs->GdxcBaseAddress = GdxcBaseAddress.Data32[0] & 0xFFFFF000;
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "GdxcBaseAddress = 0x%X\n", Inputs->GdxcBaseAddress);
  } else {
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "GDXC base address is not programmed! 0x%X_%X\n", GdxcBaseAddress.Data32[1], GdxcBaseAddress.Data32[0]);
    return mrcFail;
  }

  //
  // Detect the board type.
  // OEM must fill in correct board type here.
  //
  SpdPresent = TRUE;
  BoardId    = 1;
  //
  // Switch for ECC/Memory Scrubbing test.
  //
  Inputs->CleanMemory = FALSE;

  //
  // Init the memory map values (only for testing).
  //
  Inputs->MeStolenSize               = 0;            // MB
  Inputs->MmioSize                   = 1024;         // MB
  Inputs->TsegSize                   = 8;            // MB
  Inputs->GraphicsGttSize            = 0;            // MB
  Inputs->GraphicsStolenSize         = 0;            // MB
  Inputs->GfxIsVersatileAcceleration = FALSE;
  Inputs->DprSize                    = 0;            // MB
  Inputs->PrmrrSize                  = MrcCheckPrmrrSupport(MrcData, 128); // MB

  //
  // Init working modes.
  //
  Inputs->MemoryProfile          = STD_PROFILE;
  Inputs->FreqMax                = f4133;
  Inputs->EccSupport             = TRUE;
  Inputs->BClkFrequency          = BCLK_DEFAULT;
  Inputs->OddRatioMode           = FALSE;
  Inputs->NModeSupport           = 0;
  Inputs->EnCmdRate              = 3;

  if (Inputs->MemoryProfile == USER_PROFILE) {
    Inputs->Ratio                = 0;  // Auto
    Inputs->RefClk               = MRC_REF_CLOCK_133;
  }

  for (Controller = 0; Controller < MAX_CONTROLLERS; Controller++) {
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      ChannelIn = &Inputs->Controller[Controller].Channel[Channel];
      for (Dimm = 0; Dimm < MAX_DIMMS_IN_CHANNEL; Dimm++) {
        DimmIn = &ChannelIn->Dimm[Dimm];

        DimmIn->Timing.NMode   = 0;
        if (Inputs->MemoryProfile == USER_PROFILE) {
          DimmIn->Timing.tCL     = 0;
          DimmIn->Timing.tCWL    = 0;
          DimmIn->Timing.tFAW    = 0;
          DimmIn->Timing.tRAS    = 0;
          DimmIn->Timing.tRCDtRP = 0;
          DimmIn->Timing.tREFI   = 0;
          DimmIn->Timing.tRFC    = 0;
          DimmIn->Timing.tRRD    = 0;
          DimmIn->Timing.tRTP    = 0;
          DimmIn->Timing.tWR     = 0;
          DimmIn->Timing.tWTR    = 0;
        }
      }
    }
  }


  Inputs->PowerDownMode                 = pdmAuto;         // 0/1/6/0xFF = NO PD/APD/PPD-DLLOFF/Auto
  Inputs->PwdwnIdleCounter              = 0;               // Auto
  Inputs->RhPrevention                  = TRUE;            // Row Hammer prevention.
  Inputs->RhSolution                    = HardwareRhp;     // Type of solution to be used for RHP - 0/1 = HardwareRhp/Refresh2x
  Inputs->RhActProbability              = OneIn2To11;       // Activation probability for Hardware RHP
  Inputs->RankInterleave                = TRUE;            // Enable Rank Interleave. HORI can't be enabled at the same time
  Inputs->EnhancedInterleave            = TRUE;            // Enable Enhanced Interleave.

  Inputs->WeaklockEn                    = TRUE;            // Enable Weak Lock
  Inputs->EnCmdRate                     = 7;               // Valid values are: 0,5,7,9,11,13,15
  Inputs->CmdTriStateDis                = FALSE;           // Enable/disale CMD 3st disable
  Inputs->ChHashEnable                  = TRUE;            // Enale/disable CH HASH support
  Inputs->ChHashMask                    = (UlxUlt && HasEdram) ? 0x30D0 : 0x30C8;          // Addr bits[19:6] to include in Channel XOR function.
  Inputs->ChHashInterleaveBit           = 2;               // BIT8 (Valid values are 0-7 for BITS 6 - 13)
  //
  // Options for Thermal settings
  //
  Inputs->EnableExtts                   = 0;
  Inputs->EnableCltm                    = 0;
  Inputs->EnableOltm                    = 0;
  Inputs->EnablePwrDn                   = 1;
  Inputs->EnablePwrDnLpddr              = 1;
  Inputs->Refresh2X                     = 0;
  Inputs->DdrThermalSensor              = 1;        // Enable LPDDR MR4 temperature reads
  Inputs->LockPTMregs                   = 0;

  Inputs->EnergyScaleFact               = 3;
  Inputs->RaplLim2Lock                  = 0;
  Inputs->ThermalEnables.RaplLim2WindX  = 0;
  Inputs->ThermalEnables.RaplLim2WindY  = 0;
  Inputs->RaplLim2Ena                   = 0;
  Inputs->ThermalEnables.RaplLim2Pwr    = 0;
  Inputs->ThermalEnables.RaplLim1WindX  = 0;
  Inputs->ThermalEnables.RaplLim1WindY  = 0;
  Inputs->RaplLim1Ena                   = 0;
  Inputs->ThermalEnables.RaplLim1Pwr    = 0;
  Inputs->RaplPwrFlCh0                  = 0;
  Inputs->RaplPwrFlCh1                  = 0;

  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    for (Dimm = 0; Dimm < MAX_DIMMS_IN_CHANNEL; Dimm++) {
      Inputs->ThermalEnables.WarmThreshold[Channel][Dimm] = 0xFF;
      Inputs->ThermalEnables.HotThreshold[Channel][Dimm]  = 0xFF;
      Inputs->ThermalEnables.WarmBudget[Channel][Dimm]    = 0xFF;
      Inputs->ThermalEnables.HotBudget[Channel][Dimm]     = 0xFF;
      Inputs->ThermalEnables.IdleEnergy[Channel][Dimm]    = 0;
      Inputs->ThermalEnables.PdEnergy[Channel][Dimm]      = 0;
      Inputs->ThermalEnables.ActEnergy[Channel][Dimm]     = 0;
      Inputs->ThermalEnables.RdEnergy[Channel][Dimm]      = 0;
      Inputs->ThermalEnables.WrEnergy[Channel][Dimm]      = 0;
    }
  }

  Inputs->SrefCfgEna            = 1;
  Inputs->SrefCfgIdleTmr        = 0x200;
  Inputs->ThrtCkeMinDefeat      = 0;
  Inputs->ThrtCkeMinTmr         = 0x30;
  Inputs->ThrtCkeMinDefeatLpddr = 1;
  Inputs->ThrtCkeMinTmrLpddr    = 0x40;

  Inputs->Gdxc.GdxcEnable          = FALSE;           // Default is HD Port
  Inputs->Gdxc.GdxcIotSize         = 4;               // 32 MB, in 8MB units
  Inputs->Gdxc.GdxcMotSize         = 12;              // 96 MB, in 8MB units
  Inputs->MemoryTrace              = 0;

  Inputs->AutoSelfRefreshSupport = TRUE;
  Inputs->ExtTemperatureSupport  = TRUE;

  Inputs->MaxRttWr = 0;
  Inputs->StrongWkLeaker  = 7;
  Inputs->ForceSingleRank = 0;

  //
  // Options for training steps
  //
  Inputs->TrainingEnables.ECT         = 0;
  Inputs->TrainingEnables.WRSRT       = 0;
  Inputs->TrainingEnables.RMT         = 0;
  Inputs->TrainingEnables.MEMTST      = 0;
  Inputs->EnBER                       = 1;


  Inputs->TrainingEnables.SOT         = 1;
  Inputs->TrainingEnables.RDMPRT      = 1;
  Inputs->TrainingEnables.RCVET       = 1;
  Inputs->TrainingEnables.JWRL        = 1;
  Inputs->TrainingEnables.ERDMPRTC2D  = 1;
  Inputs->TrainingEnables.EWRTC2D     = 1;
  Inputs->TrainingEnables.ERDTC2D     = 1;
  Inputs->TrainingEnables.WRTC1D      = 1;
  Inputs->TrainingEnables.WRVC1D      = 1;
  Inputs->TrainingEnables.RDTC1D      = 1;
  Inputs->DDR4MAP                     = 0;
  Inputs->TrainingEnables.DIMMODTT    = 1;
  Inputs->TrainingEnables.DIMMRONT    = 1;
  Inputs->TrainingEnables.WRDSEQT     = (UlxUlt) ? 0 : 1;
  Inputs->TrainingEnables.WRDSUDT     = 0;
  Inputs->TrainingEnables.WRSRT       = 1;
  Inputs->TrainingEnables.RDEQT       = 1;
  Inputs->TrainingEnables.RDODTT      = 1;
  Inputs->TrainingEnables.RDAPT       = 1;
  Inputs->TrainingEnables.CMDVC       = 1;
  Inputs->TrainingEnables.WRTC2D      = 1;
  Inputs->TrainingEnables.RDTC2D      = 1;
  Inputs->TrainingEnables.WRVC2D      = 1;
  Inputs->TrainingEnables.RDVC2D      = 1;
  Inputs->TrainingEnables.LCT         = 1;
  Inputs->TrainingEnables.RTL         = 1;
  Inputs->TrainingEnables.TAT         = 1;
  Inputs->TrainingEnables.RCVENC1D    = 1;
  Inputs->TrainingEnables.ALIASCHK    = 1;
  Inputs->TrainingEnables.RMC         = 1;
  Inputs->TrainingEnables2.CMDSR      = 1;
  Inputs->TrainingEnables2.CMDDSEQ    = 1;
  Inputs->TrainingEnables2.CMDNORM    = 1;
  Inputs->TrainingEnables2.EWRDSEQ    = 1;

  Inputs->PowerTrainingMode           = (UlxUlt) ? MrcTmPower : MrcTmMargin;

  Inputs->LpddrMemWriteLatencySet = 1; // Set B Enabled
  Inputs->EvLoader                = 1;
  Inputs->EvLoaderDelay           = 1;

  Inputs->DllBwEn0 = 0;
  Inputs->DllBwEn1 = 1;
  Inputs->DllBwEn2 = 2;
  Inputs->DllBwEn3 = 2;

  //
  // Get RTC time
  //
  MrcCall->MrcGetRtcTime (&(Inputs->BaseTime.Seconds), &(Inputs->BaseTime.Minutes),
             &(Inputs->BaseTime.Hours), &(Inputs->BaseTime.DayOfMonth),
             &(Inputs->BaseTime.Month), &(Inputs->BaseTime.Year));

  //
  // Read PCI 0:0:0:2 - Device ID
  //
  DeviceId = MrcCall->MrcMmioRead32 (PciEBaseAddress);
  DeviceId >>= 16;
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "CPU Device ID: 0x%04X - ", DeviceId);
  switch (DeviceId) {
    case MRC_SA_DEVICE_ID_SKL_ULT:
    case MRC_SA_DEVICE_ID_SKL_ULX:
    case MRC_SA_DEVICE_ID_SKL_ULX_1:
    case MRC_SA_DEVICE_ID_KBL_ULT:
    case MRC_SA_DEVICE_ID_KBL_ULX:
    case MRC_SA_DEVICE_ID_KBL_ULTR:
    case MRC_SA_DEVICE_ID_AML_MB_ULX_1:
      Inputs->BoardType      = btUser4; // ULT board type
      Inputs->MobilePlatform = TRUE;
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "ULT/ULX\n");
      break;

    case MRC_SA_DEVICE_ID_SKL_MB_HALO:
      Inputs->BoardType      = btCRBMB;
      Inputs->MobilePlatform = TRUE;
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Mobile Halo\n");
      break;

    case MRC_SA_DEVICE_ID_SKL_DT:
    case MRC_SA_DEVICE_ID_SKL_DT_1:
    case MRC_SA_DEVICE_ID_SKL_DT_2:
    case MRC_SA_DEVICE_ID_SKL_DT_3:
    case MRC_SA_DEVICE_ID_SKL_SVR:
    case MRC_SA_DEVICE_ID_SKL_SVR_1:
    case MRC_SA_DEVICE_ID_KBL_DT_HALO:
    case MRC_SA_DEVICE_ID_KBL_DT_HALO_1:
    case MRC_SA_DEVICE_ID_KBL_DT:
    case MRC_SA_DEVICE_ID_KBL_DT_1:
    case MRC_SA_DEVICE_ID_KBL_SVR:
    case MRC_SA_DEVICE_ID_KBL_SVR_1:
    case MRC_SA_DEVICE_ID_CFL:
    case MRC_SA_DEVICE_ID_CFL_1:
    case MRC_SA_DEVICE_ID_CFL_SVR_1:
    case MRC_SA_DEVICE_ID_CFL_SVR_2:
      Inputs->BoardType      = btCRBDT;
      Inputs->MobilePlatform = FALSE;
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Desktop / UP Server\n");
      break;

    default:
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "ERROR: Unknown CPU Device ID!\n");
      MRC_DEADLOOP ();
  }

  //
  // RVP16 is DT Halo with LPDDR3, so use ULT board type and Mobile.
  //
  if (BoardId == BoardIdSkylakeHaloLpddr3Rvp16) {
    Inputs->BoardType      = btUser4; // ULT board type
    Inputs->MobilePlatform = TRUE;
  }

  //
  // Interleaving mode of DQ/DQS pins - depends on board routing
  //
  switch (BoardId) {
    case BoardIdSkylakeURvp7:
    case BoardIdKabylakeRDdr4:
    case BoardIdKabylakeKcDdr3:
    case BoardIdSkylakeURvp7Ppv:
    case BoardIdSkylakeDtRvp8Crb:
    case BoardIdSkylakeHaloDdr4Rvp11:
    case BoardIdSkylakeHaloDdr4Rvp11Ppv:
    case BoardIdKabylakeDdr4Rvp17:  // KblGContent
    case BoardIdSkylakeURvp15:
    case BoardIdZumbaBeachServerEv:
    case BoardIdZumbaBeachServerCrb:
    case BoardIdSkylakeSdlBrk:
    case BoardIdKabyLakeSDdr4UdimmEvCrb:
      Inputs->DqPinsInterleaved = 1;
      break;

    default:
      Inputs->DqPinsInterleaved = 0;
  }

  //
  // CPU ODT mode
  //
  Inputs->EnVttOdt = UlxUlt;
  Inputs->VttCompForVsshi = 1;

  //
  // Board CA Vref connectivity - depends on board routing
  //
  switch (BoardId) {
    case BoardIdSkylakeDtRvp8Crb:
    case BoardIdSkylakeAioRvp9Crb:
    case BoardIdSkylakeHaloDdr4Rvp11:
    case BoardIdSkylakeHaloDdr4Rvp11Ppv:
    case BoardIdKabylakeDdr4Rvp17: // KblGContent
    case BoardIdSkylakeURvp15:
    case BoardIdKabylakeRDdr4:
    case BoardIdZumbaBeachServerEv:
    case BoardIdZumbaBeachServerCrb:
    case BoardIdSkylakeSdlBrk:
    case BoardIdKabyLakeSDdr4UdimmEvCrb:
      Inputs->CaVrefConfig = 2;   // DDR4 boards
      break;

    case BoardIdSkylakeA0Ddr4Rvp2:
      Inputs->CaVrefConfig = 1;
      break;

    default:
      Inputs->CaVrefConfig = 0;   // All DDR3L/LPDDR3 boards
  }

  //
  // DRAM ODT
  //
  Inputs->LpddrDramOdt = (UlxUlt && (Inputs->CpuStepping >= csKblY0)) ? 1 : 0;
  Inputs->Ddr3DramOdt  = 1;
  Inputs->Ddr4DramOdt  = 1;

  Inputs->BerEnable     = 0; //# of BER Addresses (1-4 means # of passed in addresses, 5-8 means # of Random addresses [1-4 random addresses], 0 means disabled)

  Inputs->SaGv               = MrcSaGvDisabled;
  Inputs->FreqSaGvLow        = 0;  // SA GV: 0 is Auto, otherwise holds the frequency value.
  Inputs->EpgEnable          = 0;  // EPG disabled by default.
  Inputs->Idd3n              = 26;
  Inputs->Idd3p              = 11;
  Inputs->Ddr4DdpSharedClock = 0;  // Select if CLK0 is shared between Rank0 and Rank1 in DDR4 DDP package.   0=Not shared, 1=Shared
  Inputs->Ddr4DdpSharedZq    = 0;  // Select if ZQ pin is shared between Rank0 and Rank1 in DDR4 DDP package. 0=Not shared, 1=Shared
  Inputs->Ddr4MixedUDimm2DpcLimit = 0; // Enable/Disable the 2DPC Mixed U-DIMM frequency limitation (2667 not allowed for Mixed U-DIMM Part Numbers within a channel)
  //
  // Initialize the board-specific CMD/CTL/CLK and DQ/DQS mapping for LPDDR3
  //
  MrcOemLpddrBoardMapping (MrcData, BoardId);

  //
  // Initialize the board-specific RCOMP values
  //
  MrcOemRcompValues (MrcData, BoardId);


  //
  // Unlock CPU in case LT is enabled
  //
  Value = MrcCall->MrcMmioRead32 (0xFED40000);

  if (MrcIsTxtChipset ()) {
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "Chipset is LT-capable, Unlocking Memory\n");
    MrcMSRWrite (0x2E6, 0, 0);
  }
  //
  // Get DIMM SpdBaseAddresses.
  //
  for (Controller = 0; Controller < MAX_CONTROLLERS; Controller++) {
    ControllerIn               = &Inputs->Controller[Controller];
    ControllerIn->ChannelCount = MAX_CHANNEL;
    for (Channel = 0;  Channel < MAX_CHANNEL; Channel++) {
      ChannelIn            = &ControllerIn->Channel[Channel];
      ChannelIn->Status    = CHANNEL_PRESENT;
      ChannelIn->DimmCount = MAX_DIMMS_IN_CHANNEL;
      for (Dimm = 0; Dimm < MAX_DIMMS_IN_CHANNEL; Dimm++) {
        Index              = (Channel * MAX_DIMMS_IN_CHANNEL) + Dimm;
        DimmIn             = &ChannelIn->Dimm[Dimm];
        DimmIn->Status     = DIMM_ENABLED;
        if (SpdPresent) {
          DimmIn->SpdAddress = MrcOemGetSmBusDeviceAddress (MrcData, BoardId, (MRC_OemSmbusDeviceType) Index);
          MrcCall->MrcCopyMem ((UINT8 *) &DimmIn->Spd.MrcSpdString[0], (UINT8 *) MrcSpdStringConst, sizeof (DimmIn->Spd.MrcSpdString));
        }
        DimmIn->Spd.Flag.Bit.DimmNumber    = Dimm;
        DimmIn->Spd.Flag.Bit.ChannelNumber = Channel;
        DimmIn->Spd.Flag.Bit.MdSocket      = (DimmIn->SpdAddress > 0) ? 1 : 0;
      }
    }
  }
  //
  // Enables MiniBIOS to support Memory Down configs such as Harris Beach which does not have an SPD.
  //
#if (defined MEMORY_DOWN_SUPPORT && (MEMORY_DOWN_SUPPORT > 0))
  EnableMemoryDown (MrcData, BoardId, SpdPresent);
#endif

  //
  // Read SPD data.
  // Setup the DIMM population and DIMM data.
  //
  Inputs->BootMode = bmCold;

  //
  // This enabled Fast/Warm boot flow.
  // In Stub mode we save the MrcSave struct to a file on the client.
  // In MiniBios the MrcSave struct should be flashed at offset MRC_SAVE_DATA_FLASH_PTR (0xFFFD0000)
  //
  if (MrcSaveExists ()) {
    MrcGetMrcSaveData ((UINT8 *) &MrcData->Save, sizeof (MrcSave));
    Crc32 = MrcCalculateCrc32 ((UINT8 *) (&MrcData->Save.Data), sizeof (MrcSaveData));
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Calc. crc = 0x%x, Header crc = 0x%x\n", Crc32, MrcData->Save.Header.Crc);
    if (Crc32 == MrcData->Save.Header.Crc) {
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Save Data is valid.  Boot Mode: ");
      if (MrcGetBootMode (MrcData) == bmWarm) {
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "bmWarm\n");
        Inputs->BootMode = bmWarm;
      } else {
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "bmFast\n");
        Inputs->BootMode = bmFast;
      }
    } else {
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Save Data is not valid\nCold boot\n");
    }
  }

  if (mrcSuccess != GetSpdData (Inputs->BootMode, MrcData)) {
    MRC_DEADLOOP ();
  }

  //
  // MiniBios overrides start here
  //
  MrcMiniBiosOverrides (MrcData);

  if ((BoardId == BoardIdZumbaBeachServerEv) || (BoardId == BoardIdZumbaBeachServerCrb)) {
    MrcUpServerSendEndOfPost ();
  }

  //
  // Run the memory configuration code.
  //
  Status = mrcSuccess;
  if (Status == mrcSuccess) {
    Status = MrcStartMemoryConfiguration (MrcData, 0);

    switch (Status) {
      case mrcSuccess:
        break;

      default:
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "!!!!!!!!!!!!!!!!!!!\n");
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, " ERROR: MRC failed\n");
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "!!!!!!!!!!!!!!!!!!!\n");

        MRC_DEADLOOP ();
    }

    MrcSetDISB (MrcData);             // Set DRAM Initialization Status Bit, so that we can do Warm flow

    MallocParams = (TMallocParams  *) OemMemoryBase ();
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "*********************************************************************\n");
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "*  MRC is done and MC is in NORMAL MODE and ready to use            *\n");
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "*  Number of MMIO reads:  %8d                                  *\n", MallocParams->MmioReadPtr);
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "*  Number of MMIO writes: %8d                                  *\n", MallocParams->MmioWritePtr);
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "*  MrcSave: 0x%08X, size: 0x%08X bytes                      *\n", &MrcData->Save, sizeof (MrcSave));
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "*  Stack: Top: 0x%x Bottom: 0x%x Depth: %d\n",
      Debug->TopStackAddr,
      Debug->LowestStackAddr,
      Debug->TopStackAddr - Debug->LowestStackAddr
      );
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "*********************************************************************\n");

    MrcOemDebugHook (MrcData, MRC_MEM_INIT_DONE);
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "MRC Stack Depth: "); //_printStackDepth function prints the actual value and is called from assembly code.
  }



  return Status;
}

static
void
init_malloc (
  CPU_SETUP_OPTIONS *Input
  )
/**

Routine Description:

    init the malloc system. need to be call in the MiniBIOS start.

Arguments:

   N/A

Returns:

    N/A

**/
{
  TMallocParams *MallocParams;
  MallocParams  = (TMallocParams *) Input->nem_data_addr;

  MallocParams->NextAllocation = (sizeof (TMallocParams) + (UINT32) MallocParams);
  MallocParams->MmioReadPtr  = 0;
  MallocParams->MmioWritePtr = 0;
  return;
}

void
MmioWriteCount (
  void
  )
/**

Routine Description:

  This function count the number of access to writes MMIO registers .

Arguments:

  N/A

Returns:

  N/A

**/
{
  TMallocParams  *MallocParams;
  MallocParams = (TMallocParams *) OemMemoryBase ();
  MallocParams->MmioWritePtr++;
  return;
}

void
MmioReadCount (
  void
  )
/**

Routine Description:

     This function count the number of access to reads MMIO registers .

Arguments:

    N/A

Returns:

    N/A

**/
{
  TMallocParams  *MallocParams;
  MallocParams = (TMallocParams *) OemMemoryBase ();
  MallocParams->MmioReadPtr++;
  return;
}

void
MrcMSRWrite (
  UINT32 Index,
  UINT32 ValueH,
  UINT32 ValueL
  )
/**

Routine Description:

  This function writes to MSR

Arguments:

  UINT32 Index
  UINT64 Value

Returns:

  N/A

**/
{
  ASM {

    pushad
    mov    ecx, Index
    mov    eax, DWORD PTR ValueH
    mov    edx, DWORD PTR ValueL
    wrmsr
    popad
  }
  return;
}

BOOLEAN
MrcIsTxtProcessor (
  void
  )
/**

  Determines whether or not the current processor is TXT Capable.


  @retval TRUE          - If the current processor supports TXT
  @retval FALSE         - If the current processor does not support TXT

**/
{
  UINT32 TxtCapable;

  ASM {
    mov   ecx, 1
    cpuid
    and   ecx, MRC_BIT6
    shr   ecx, 6
    mov   TxtCapable, ecx
  }

  return (BOOLEAN) TxtCapable;
}

BOOLEAN
MrcIsTxtChipset (
  void
  )
/**

  Determines whether or not the current chipset is TXT Capable.


  @retval TRUE          - If the current chipset supports TXT
  @retval FALSE         - If the current chipset doesn't supports TXT

**/
{
  BOOLEAN TxtCapable;
  UINT32  Data32;

  Data32 = * (volatile UINT32 *) (0xFED30000 + 0x10);

  TxtCapable = (BOOLEAN) ((Data32 & MRC_BIT0) != 0);

  return TxtCapable;
}


UINT32
MrcCPUStepGet (
  void
  )
/**

Routine Description:

    This function returns the CPUID.1.EAX value.

Arguments:

    N/A
Returns:
    CPU ID

**/
{
  UINT32 Value;

  ASM {
    mov  eax, 1
    cpuid
    mov Value, eax
  }
  return Value;
}

void
GPIOBaseEnable (
  void
  )
/**

Routine Description:

    Enables GPIO base.

Arguments:

    N/A

Returns:

    N/A

**/
{
  ASM {

    ;
    ; Enable GPIO BASE I/O registers
    ;
    mov  eax, PCI_LPC_BASE + 48h
    mov  dx, 0CF8h
    out  dx, eax
    mov  eax, GPIO_BASE_ADDRESS
    add  dx, 4
    out  dx, eax

    mov  eax, PCI_LPC_BASE + 4Ch
    mov  dx, 0CF8h
    out  dx, eax
    add  dx, 4
    in   al, dx
    or   al, BIT4       ; GPIOBASE Enable
    out  dx, al
  }
  return;
}

static
UINT8
MrcOemGetSmBusDeviceAddress (
  MrcParameters *const    MrcData,
  UINT16                  BoardId,
  MRC_OemSmbusDeviceType  SmbusDeviceType
  )
/*++

Routine Description:

  this routine return the SMBUS device address to each dimm.

Arguments:

  OemSmbusDeviceAddressType - point to the require device address.

Returns:

 UINT8 - Smbus device address

--*/
{
  UINT8 SmBusDeviceAddress;

  switch (SmbusDeviceType) {
    case datOemSpd_0_0:
      SmBusDeviceAddress = 0xA0;
      break;
    case datOemSpd_0_1:
      SmBusDeviceAddress = 0xA2;
      break;
    case datOemSpd_1_0:
      SmBusDeviceAddress = 0xA4;
      break;
    case datOemSpd_1_1:
      SmBusDeviceAddress = 0xA6;
      break;
    case datOemVrefWrite_0:
      SmBusDeviceAddress = 0x00;
      break;
    case datOemVrefWrite_1:
      SmBusDeviceAddress = 0x00;
      break;
    case datOemVrefRead:
      SmBusDeviceAddress = 0x00;
      break;
      default :
      SmBusDeviceAddress = 0x00;
      break;
  }

  return SmBusDeviceAddress;
}
