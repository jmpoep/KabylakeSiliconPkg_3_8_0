/** @file
  Header file for PCH Initialization Driver.

 @copyright
  INTEL CONFIDENTIAL
  Copyright 1999 - 2017 Intel Corporation.

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
#ifndef _PCH_INITIALIZATION_DRIVER_H_
#define _PCH_INITIALIZATION_DRIVER_H_

typedef UINT16                    STRING_REF;
#ifdef FSP_FLAG
#include <Library/PeiServicesLib.h>
#include <Uefi/UefiSpec.h>
#endif
#include <Library/DebugLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/IoLib.h>
#include <Library/TimerLib.h>
#include <Library/ConfigBlockLib.h>
#include <Protocol/DriverSupportedEfiVersion.h>
#include <Library/PchCycleDecodingLib.h>
#include <Library/PchPcieRpLib.h>
#include <Library/PchP2sbLib.h>
#include <Library/PchPcrLib.h>
#include <Library/PchEspiLib.h>
#include <Library/PchInfoLib.h>
#include <Library/TraceHubInitLib.h>
#include <Guid/EventGroup.h>
#include <Library/S3BootScriptLib.h>
#include <Protocol/PciIo.h>
#include <Protocol/PciPlatform.h>
#include <Protocol/PciEnumerationComplete.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/HobLib.h>
#include <Library/UefiLib.h>
#include <Library/MemoryAllocationLib.h>
#ifndef FSP_FLAG
#include <Library/DxeServicesTableLib.h>
#endif

#include <PchAccess.h>
#include <Private/SiConfigHob.h>
#include <Protocol/PchInfo.h>
#include <IndustryStandard/Pci30.h>
#include <Library/AslUpdateLib.h>
#include <Library/MmPciLib.h>
#include <Library/CpuPlatformLib.h>
#include <Protocol/BlockIo.h>
#include <Protocol/PchEmmcTuning.h>
#include <Library/GpioLib.h>
#include <Library/GpioNativeLib.h>
#include <Private/Protocol/PchNvs.h>
#include <Private/Protocol/PcieIoTrap.h>
#include <Private/Library/PchInitCommonLib.h>
#include <Private/Library/PchPciExpressHelpersLib.h>
#include <Library/PchPsfLib.h>
#include <Private/Library/PchPsfPrivateLib.h>
#include <Private/PchConfigHob.h>

typedef struct {
  PCH_INFO_PROTOCOL PchInfo;
} PCH_INSTANCE_PRIVATE_DATA;

//
// This struct is used to record the fields that is required to be saved and restored during RST PCIe Storage Remapping Configuration
//
typedef struct {
  UINT8     PmCapPtr;
  UINT8     PcieCapPtr;
  UINT16    L1ssCapPtr;
  UINT8     EndpointL1ssControl2;
  UINT32    EndpointL1ssControl1;
  UINT16    LtrCapPtr;
  UINT32    EndpointLtrData;
  UINT16    EndpointLctlData16;
  UINT16    EndpointDctlData16;
  UINT16    EndpointDctl2Data16;
  UINT16    RootPortDctl2Data16;
} PCH_RST_PCIE_STORAGE_SAVE_RESTORE;

//
// This struct is used to record the result of RST PCIe Storage detection for each RST PCIe Storage Cycle Router supported on the platform
//
typedef struct {
  BOOLEAN                               SupportRstPcieStoragRemapping;    // Indicates if RST PCIe Storage Remapping is supported and PCIe storage device is found under a Cycle Router
  UINT8                                 RootPortNum;                      // Indicates the root port number with RST PCIe Storage Remapping remapping supported and PCIe storage device plugged on, numbering is 0-based
  UINT8                                 RootPortLane;                     // Indicates the root port lanes occupied by the PCIe storage device with 4-bit mask
  UINT8                                 DeviceInterface;                  // Indicates the interface of the PCIe storage device (AHCI or NVMe)
  UINT8                                 IsMsixSupported;                  // Indicates if the PCIe storage device support MSI-X cap
  UINT16                                MsixStartingVector;               // Records the starting vector of PCIe storage device's MSI-X (if supported)
  UINT16                                MsixEndingVector;                 // Records the ending vector of PCIe storage device's MSI-X (if supported)
  UINT32                                EndPointBarSize;                  // Records the PCIe storage device's BAR size
  UINT32                                EndPointUniqueMsixTableBar;       // Records the PCIe storage device's MSI-X Table BAR if it supports unique MSI-X Table BAR
  UINT32                                EndPointUniqueMsixTableBarValue;  // Records the PCIe storage device's MSI-X Table BAR value if it supports unique MSI-X Table BAR
  UINT32                                EndPointUniqueMsixPbaBar;         // Records the PCIe storage device's MSI-X PBA BAR if it supports unique MSI-X PBA BAR
  UINT32                                EndPointUniqueMsixPbaBarValue;    // Records the PCIe storage device's MSI-X PBA BAR value if it supports unique MSI-X PBA BAR
  UINT8                                 EndPointBcc;                      // Records the PCIe storage device's Base Class Code
  UINT8                                 EndPointScc;                      // Records the PCIe storage device's Sub Class Code
  UINT8                                 EndPointPi;                       // Records the PCIe storage device's Programming Interface
  PCH_RST_PCIE_STORAGE_SAVE_RESTORE     PchRstPcieStorageSaveRestore;     // Records the fields that is required to be saved and restored
} PCH_RST_PCIE_STORAGE_DETECTION;

//
// Data definitions
//
extern EFI_HANDLE               mImageHandle;

//
// Pch NVS area definition
//
extern PCH_NVS_AREA_PROTOCOL    mPchNvsAreaProtocol;

extern PCH_CONFIG_HOB           *mPchConfigHob;
extern SI_CONFIG_HOB            *mSiConfigHob;

//
// Function Prototype
//

//
// Local function prototypes
//
/**
  Initialize the PCH device according to the PCH Policy HOB
  and install PCH info instance.

**/
VOID
InitializePchDevice (
  VOID
  );

/**
  Common PchInit Module Entry Point
**/
VOID
PchInitEntryPointCommon (
  VOID
  );

/**
  Common PCH initialization on PCI enumeration complete.
**/
VOID
PchOnPciEnumCompleteCommon (
  VOID
  );

#ifndef MINTREE_FLAG
/**
  Function to configure RST PCIe Storage Remapping (Intel RST Driver is required)

  @param[in] TempPciBusMin        The temporary minimum Bus number for root port initialization
  @param[in] TempPciBusMax        The temporary maximum Bus number for root port initialization

  @retval EFI_SUCCESS             The function completed successfully
**/
EFI_STATUS
ConfigureRstPcieStorageRemapping (
  IN UINT8                         TempPciBusMin,
  IN UINT8                         TempPciBusMax
  );
#endif //MINTREE_FLAG
/**
  Configures Serial IO Controllers

**/
EFI_STATUS
ConfigureSerialIoAtBoot (
  VOID
  );

/**
  Creates device handles for SerialIo devices in ACPI mode

**/
VOID
CreateSerialIoHandles (
  VOID
  );

/**
  Mark memory used by SerialIo devices in ACPI mode as allocated

  @retval EFI_SUCCESS             The function completed successfully
**/
EFI_STATUS
AllocateSerialIoMemory (
  VOID
  );

/**
  Update ASL definitions for SerialIo devices.

  @retval EFI_SUCCESS             The function completed successfully
**/
EFI_STATUS
UpdateSerialIoAcpiData (
  VOID
  );

/**
  Initialize PCIE SRC clocks in ICC subsystem

  @param[in] GbePortNumber        Number of PCIE rootport assigned to GbE adapter

**/
VOID
ConfigurePchPcieClocks (
  IN UINTN                        GbePortNumber
  );

/**
  Initialize Intel High Definition Audio ACPI Tables

  @retval EFI_SUCCESS             The function completed successfully
  @retval EFI_LOAD_ERROR          ACPI table cannot be installed
  @retval EFI_UNSUPPORTED         ACPI table not set because DSP is disabled
**/
EFI_STATUS
PchHdAudioAcpiInit (
  VOID
  );

/**
  Configure eMMC in HS400 Mode

  @param[in] This                         A pointer to PCH_EMMC_TUNING_PROTOCOL structure
  @param[in] Revision                     Revision parameter used to verify the layout of EMMC_INFO and TUNINGDATA.
  @param[in] EmmcInfo                     A pointer to EMMC_INFO structure
  @param[out] EmmcTuningData              A pointer to EMMC_TUNING_DATA structure

  @retval EFI_SUCCESS                     The function completed successfully
  @retval EFI_NOT_FOUND                   The item was not found
  @retval EFI_OUT_OF_RESOURCES            The request could not be completed due to a lack of resources.
  @retval EFI_INVALID_PARAMETER           A parameter was incorrect.
  @retval EFI_DEVICE_ERROR                Hardware Error
  @retval EFI_NO_MEDIA                    No media
  @retval EFI_MEDIA_CHANGED               Media Change
  @retval EFI_BAD_BUFFER_SIZE             Buffer size is bad
  @retval EFI_CRC_ERROR                   Command or Data CRC Error
**/
EFI_STATUS
EFIAPI
ConfigureEmmcHs400Mode (
  IN  PCH_EMMC_TUNING_PROTOCOL          *This,
  IN  UINT8                             Revision,
  IN  EMMC_INFO                         *EmmcInfo,
  OUT EMMC_TUNING_DATA                  *EmmcTuningData
  );

/**
  Install PCH EMMC TUNING PROTOCOL

**/
VOID
InstallPchEmmcTuningProtocol (
  VOID
  );

/**
  Perform the remaining configuration on PCH SATA to perform device detection,
  then set the SATA SPD and PxE corresponding, and set the Register Lock on PCH SATA

  @retval None
**/
VOID
ConfigurePchSataOnEndOfDxe (
  VOID
  );

/**
  Update ASL data for CIO2 Device.

  @retval EFI_SUCCESS             The function completed successfully
**/
EFI_STATUS
UpdateCio2AcpiData (
   VOID
   );

/**
  Initialize Pch acpi
  @param[in] ImageHandle          Handle for the image of this driver

  @retval EFI_SUCCESS             The function completed successfully
  @retval EFI_OUT_OF_RESOURCES    Do not have enough resources to initialize the driver
**/
EFI_STATUS
EFIAPI
PchAcpiInit (
  IN EFI_HANDLE         ImageHandle
  );

/**
  Update ASL object before Boot

  @retval EFI_STATUS
  @retval EFI_NOT_READY         The Acpi protocols are not ready.
**/
EFI_STATUS
PchUpdateNvsArea (
  VOID
  );

/**
  Initialize PCH Nvs Area opeartion region.

  @retval EFI_SUCCESS    initialized successfully
  @retval EFI_NOT_FOUND  Nvs Area operation region is not found
**/
EFI_STATUS
PatchPchNvsAreaAddress (
  VOID
  );

/**
  PCH Update NvsArea ExitBootServicesFlag on ExitBootService. This event is used if only ExitBootService is used
  and not in legacy boot

  @retval None
**/
VOID
EFIAPI
PchUpdateNvsOnExitBootServices (
  VOID
  );
#endif // _PCH_INITIALIZATION_DRIVER_H_
