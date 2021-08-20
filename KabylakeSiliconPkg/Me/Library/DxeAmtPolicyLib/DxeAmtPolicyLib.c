/** @file
  This file is DxeAmtPolicyLib library.

 @copyright
  INTEL CONFIDENTIAL
  Copyright 2014 - 2016 Intel Corporation.

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
#include "DxeAmtPolicyLibrary.h"

GLOBAL_REMOVE_IF_UNREFERENCED UINT64                  mDefaultPciDeviceFilterOutTable[]  = { MAX_ADDRESS };
STATIC COMPONENT_BLOCK_ENTRY mAmtIpBlocks [] = {
  {&gAmtDxeConfigGuid,       sizeof (AMT_DXE_CONFIG),           AMT_DXE_CONFIG_REVISION,       NULL},
};

/**
  Get total size of IP list for the config block.

  @param[in] IpBlocks                   The pointer to the IP list
  @param[in] TotalIpSize                The size of IP list

  @retval                               Size of config block table
**/
STATIC
UINT16
EFIAPI
GetConfigBlockTotalSize (
  IN COMPONENT_BLOCK_ENTRY  IpBlocks [],
  IN UINTN                  TotalIpSize
  )
{
  UINT16            TotalBlockCount;
  UINT16            TotalBlockSize;
  UINT16            ConfigBlockHdrSize;
  UINT16            BlockCount;

  TotalBlockCount = (UINT16) (TotalIpSize / sizeof (COMPONENT_BLOCK_ENTRY));
  TotalBlockSize = 0;
  for (BlockCount = 0 ; BlockCount < TotalBlockCount; BlockCount++) {
    TotalBlockSize += (UINT32) IpBlocks[BlockCount].Size;
    DEBUG ((DEBUG_INFO, "TotalBlockSize after adding Block[0x%x]= 0x%x\n", BlockCount, TotalBlockSize));
  }
  ConfigBlockHdrSize = sizeof (CONFIG_BLOCK_TABLE_HEADER);

  return ConfigBlockHdrSize + TotalBlockSize;
}

/**
  CreateConfigBlocksByIpBlocks generates the config blocks for IP list.
  It allocates and zero out buffer, and fills in the Intel default settings.

  @param[in] IpBlocks                     The pointer to the IP list
  @param[in] TotalIpSize                  The size of IP list
  @param[in, out] ConfigBlockTableHeader  The pointer to the config block

  @retval EFI_SUCCESS                     The config block for IP list is created and initialized.
  @retval EFI_OUT_OF_RESOURCES            Insufficient resources to create buffer
**/
STATIC
EFI_STATUS
EFIAPI
CreateConfigBlocksByIpBlocks (
  IN COMPONENT_BLOCK_ENTRY          IpBlocks [],
  IN UINTN                          TotalIpSize,
  IN OUT CONFIG_BLOCK_TABLE_HEADER  **ConfigBlockTableHeader
  )
{
  UINT16            TotalBlockCount;
  UINT16            BlockCount;
  VOID              *ConfigBlockPointer;
  CONFIG_BLOCK      ConfigBlockBuf;
  EFI_STATUS        Status;
  UINT16            RequiredSize;
  CONFIG_BLOCK_TABLE_HEADER      *TableHeader;

  DEBUG ((DEBUG_INFO, "CreateConfigBlocksByIpBlocks\n"));

  TotalBlockCount = (UINT16) (TotalIpSize / sizeof (COMPONENT_BLOCK_ENTRY));
  DEBUG ((DEBUG_INFO, "TotalBlockCount = 0x%x\n", TotalBlockCount));

  RequiredSize = GetConfigBlockTotalSize (IpBlocks, TotalIpSize);

  Status = CreateConfigBlockTable (RequiredSize, (VOID *)&TableHeader);
  ASSERT_EFI_ERROR (Status);

  if (!EFI_ERROR (Status)) {
    //
    // Initialize ConfigBlockPointer to NULL
    //
    ConfigBlockPointer = NULL;
    //
    // Loop to identify each config block from IpBlocks[] Table and add each of them
    //
    for (BlockCount = 0 ; BlockCount < TotalBlockCount; BlockCount++) {
      CopyMem (&(ConfigBlockBuf.Header.GuidHob.Name), IpBlocks[BlockCount].Guid, sizeof (EFI_GUID));
      ConfigBlockBuf.Header.GuidHob.Header.HobLength = IpBlocks[BlockCount].Size;
      ConfigBlockBuf.Header.Revision        = IpBlocks[BlockCount].Revision;
      ConfigBlockPointer = (VOID *)&ConfigBlockBuf;
      Status = AddConfigBlock ((VOID *) TableHeader, (VOID *)&ConfigBlockPointer);
      ASSERT_EFI_ERROR (Status);
      if (IpBlocks[BlockCount].LoadDefault != NULL) {
        IpBlocks[BlockCount].LoadDefault (ConfigBlockPointer);
      }
    }
    //
    // Assignment for returning config block base address
    //
    *ConfigBlockTableHeader = TableHeader;
    return EFI_SUCCESS;
  }

  return Status;
}

/**
  Dump values of AMT config block in DXE phase.

  @param[in] AmtDxeConfig                       The pointer to the config block
**/
VOID
EFIAPI
PrintAmtDxeConfig (
  IN  AMT_DXE_CONFIG                *AmtDxeConfig
  )
{
  DEBUG_CODE_BEGIN ();
  DEBUG ((DEBUG_INFO, "------------------------ AMT_DXE_CONFIG -----------------\n"));
  DEBUG ((DEBUG_INFO, " Revision                 : 0x%x\n", AmtDxeConfig->Header.Revision));
  ASSERT (AmtDxeConfig->Header.Revision == AMT_DXE_CONFIG_REVISION);

  DEBUG ((DEBUG_INFO, " CiraRequest              : 0x%x\n", AmtDxeConfig->CiraRequest));
  DEBUG ((DEBUG_INFO, " ManageabilityMode        : 0x%x\n", AmtDxeConfig->ManageabilityMode));
  DEBUG ((DEBUG_INFO, " UnConfigureMe            : 0x%x\n", AmtDxeConfig->UnConfigureMe));
  DEBUG ((DEBUG_INFO, " MebxDebugMsg             : 0x%x\n", AmtDxeConfig->MebxDebugMsg));
  DEBUG ((DEBUG_INFO, " ForcMebxSyncUp           : 0x%x\n", AmtDxeConfig->ForcMebxSyncUp));
  DEBUG ((DEBUG_INFO, " HideUnConfigureMeConfirm : 0x%x\n", AmtDxeConfig->HideUnConfigureMeConfirm));
  DEBUG ((DEBUG_INFO, " UsbProvision             : 0x%x\n", AmtDxeConfig->UsbProvision));
  DEBUG ((DEBUG_INFO, " AmtbxHotkeyPressed       : 0x%x\n", AmtDxeConfig->AmtbxHotkeyPressed));
  DEBUG ((DEBUG_INFO, " AmtbxSelectionScreen     : 0x%x\n", AmtDxeConfig->AmtbxSelectionScreen));
  DEBUG ((DEBUG_INFO, " CiraTimeout              : 0x%x\n", AmtDxeConfig->CiraTimeout));
  DEBUG ((DEBUG_INFO, " CpuReplacementTimeout    : 0x%x\n", AmtDxeConfig->CpuReplacementTimeout));
  DEBUG ((DEBUG_INFO, " MebxNonUiTextMode        : 0x%x\n", AmtDxeConfig->MebxNonUiTextMode));
  DEBUG ((DEBUG_INFO, " MebxUiTextMode           : 0x%x\n", AmtDxeConfig->MebxUiTextMode));
  DEBUG ((DEBUG_INFO, " MebxGraphicsMode         : 0x%x\n", AmtDxeConfig->MebxGraphicsMode));
  DEBUG ((DEBUG_INFO, " PciDeviceFilterOutTable  : 0x%x\n", AmtDxeConfig->PciDeviceFilterOutTable));
  DEBUG ((DEBUG_INFO, " TestMebxLaunchTimeout    : 0x%x\n", AmtDxeConfig->TestMebxLaunchTimeout));

  DEBUG_CODE_END ();
}

/**
  This function prints the AMT DXE phase policy.

  @param[in] DxeAmtPolicy - AMT DXE Policy protocol
**/
VOID
AmtPrintPolicyProtocol (
  IN  AMT_POLICY_PROTOCOL     *DxeAmtPolicy
  )
{
  DEBUG_CODE_BEGIN ();
  EFI_STATUS                        Status;
  AMT_DXE_CONFIG                    *AmtDxeConfig;

  Status = GetConfigBlock ((VOID *) DxeAmtPolicy, &gAmtDxeConfigGuid, (VOID *) &AmtDxeConfig);
  ASSERT_EFI_ERROR (Status);

  DEBUG ((DEBUG_INFO, "\n------------------------ AmtPolicy Print Begin -----------------\n"));
  DEBUG ((DEBUG_INFO, " Revision : 0x%x\n", DxeAmtPolicy->TableHeader.Header.Revision));
  ASSERT (DxeAmtPolicy->TableHeader.Header.Revision == AMT_POLICY_PROTOCOL_REVISION);

  PrintAmtDxeConfig (AmtDxeConfig);

  DEBUG ((DEBUG_INFO, "\n------------------------ AmtPolicy Print End -------------------\n"));
  DEBUG_CODE_END ();
}

/**
  CreateConfigBlocks generates the config blocksg of AMT Policy.
  It allocates and zero out buffer, and fills in the Intel default settings.

  @param[in, out] DxeAmtPolicy          The pointer to get AMT Policy protocol instance

  @retval EFI_SUCCESS                   The policy default is initialized.
  @retval EFI_OUT_OF_RESOURCES          Insufficient resources to create buffer
**/
EFI_STATUS
EFIAPI
AmtDxeCreateConfigBlocks (
  IN OUT  AMT_POLICY_PROTOCOL       **DxeAmtPolicy
  )
{
  EFI_STATUS        Status;

  DEBUG ((DEBUG_INFO, "AmtDxeCreateConfigBlocks\n"));

  Status = CreateConfigBlocksByIpBlocks (mAmtIpBlocks, sizeof (mAmtIpBlocks), (CONFIG_BLOCK_TABLE_HEADER **) DxeAmtPolicy);
  if (!EFI_ERROR (Status)) {
    //
    // Initialize Policy Revision
    //
    (*DxeAmtPolicy)->TableHeader.Header.Revision = AMT_POLICY_PROTOCOL_REVISION;
  }

  DEBUG ((DEBUG_INFO, "AmtDxeCreateConfigBlocks done, Status: %r\n", Status));
  return Status;
}

/**
  AmtCreatePolicyDefaults creates the default setting of AMT Policy.
  It allocates and zero out buffer, and fills in the Intel default settings.

  @param[in, out] DxeAmtPolicy          The pointer to get Amt Policy protocol instance

  @retval EFI_SUCCESS                   The policy default is initialized.
  @retval EFI_UNSUPPORTED               The current SKU doesn't support AMT feature

**/
EFI_STATUS
EFIAPI
AmtCreatePolicyDefaults (
  IN OUT  AMT_POLICY_PROTOCOL       **DxeAmtPolicy
  )
{
  EFI_STATUS                      Status;
  UINTN                           VariableSize;
  ME_BIOS_EXTENSION_SETUP         MeBiosExtensionSetupData;

  ME_BIOS_PAYLOAD_HOB             *MbpHob;
  AMT_DXE_CONFIG                  *AmtDxeConfig;

  Status = AmtDxeCreateConfigBlocks (DxeAmtPolicy);
  if (!EFI_ERROR (Status)) {

    Status = GetConfigBlock ((VOID *) *DxeAmtPolicy, &gAmtDxeConfigGuid, (VOID *) &AmtDxeConfig);
    ASSERT_EFI_ERROR (Status);

    MbpHob = NULL;

    MbpHob = GetFirstGuidHob (&gMeBiosPayloadHobGuid);
    if (MbpHob == NULL) {
      DEBUG ((DEBUG_ERROR, "No MBP Data Protocol available\n"));
      return EFI_UNSUPPORTED;
    }

    if (MbpHob->MeBiosPayload.FwPlatType.RuleData.Fields.IntelMeFwImageType != IntelMeCorporateFw) {
      DEBUG ((DEBUG_INFO, "Current ME FW is not Corporate SKU, Amt Policy protocol is not installed then.\n"));
      return EFI_UNSUPPORTED;
    }

    ///
    /// MEBX_GRAPHICS_AUTO
    ///
    AmtDxeConfig->PciDeviceFilterOutTable = (UINT32) (UINTN) mDefaultPciDeviceFilterOutTable;

    ///
    /// Please don't change the default value of ForcMebxSyncUp
    /// This let customer to force MEBX execution if they need
    ///
    AmtDxeConfig->ForcMebxSyncUp = 0;

    ///
    /// Get BIOS Sync-up data from MEBx to Amt Policy
    ///
    VariableSize = sizeof (MeBiosExtensionSetupData);
    Status = gRT->GetVariable (
                    ME_BIOS_EXTENSION_SETUP_VARIABLE_NAME,
                    &gMeBiosExtensionSetupGuid,
                    NULL,
                    &VariableSize,
                    &MeBiosExtensionSetupData
                    );
    if (EFI_ERROR (Status) || (MeBiosExtensionSetupData.InterfaceVersion == 0)) {
      AmtDxeConfig->ManageabilityMode = 0;
      ///
      /// Check if this is first boot after update BIOS or the MebxSetupData variable is destroyed.
      /// In that case, we can set the force bit to synch up data with Mebx. For the normal case,
      /// ForcMebxSyncUp is still updated per customization as above comment.
      ///
      AmtDxeConfig->ForcMebxSyncUp    = 1;
    } else {
      AmtDxeConfig->ManageabilityMode = MeBiosExtensionSetupData.PlatformMngSel;
    }

    return EFI_SUCCESS;
  }

  return Status;
}

/**
  AmtInstallPolicyProtocol installs ME Policy.
  While installed, RC assumes the Policy is ready and finalized. So please update and override
  any setting before calling this function.

  @param[in] ImageHandle                Image handle of this driver.
  @param[in] DxeAmtPolicy               The pointer to Amt Policy Protocol instance

  @retval EFI_SUCCESS                   The policy is installed.
  @retval EFI_OUT_OF_RESOURCES          Insufficient resources to create buffer

**/
EFI_STATUS
EFIAPI
AmtInstallPolicyProtocol (
  IN  EFI_HANDLE                        ImageHandle,
  IN  AMT_POLICY_PROTOCOL               *DxeAmtPolicy
  )
{
  EFI_STATUS            Status;

  ///
  /// Print Amt DXE Policy
  ///
  AmtPrintPolicyProtocol (DxeAmtPolicy);

  ///
  /// Install protocol to allow access to this Policy.
  ///
  Status = gBS->InstallMultipleProtocolInterfaces (
                  &ImageHandle,
                  &gDxeAmtPolicyGuid,
                  DxeAmtPolicy,
                  NULL
                  );
  ASSERT_EFI_ERROR (Status);

  return Status;
}

