/** @file
  This file contains the definition of the BIOS implementation of the BIOS-SSA Results Configuration API.

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
#ifndef __BIOS_SSA_RESULTS_CONFIG__
#define __BIOS_SSA_RESULTS_CONFIG__

/**
  Function allocates a buffer to collect results data.
  It is made up of a block of metadata of MetadataSize and a block of results
  elements which is ResultsElementSize * ResultsCapacity in size.

  @param[in, out] This              - Interface pointer that implements the particular SSA_BIOS_SERVICES_PPI instance.
  @param[in]      MetadataSize      - Declares the size of the result buffers metadata block.
  @param[in]      ResultElementSize - Declares the size of an individual result element.
  @param[in]      ResultsCapacity   - Declares the number of elements to store results in.

  @retval NotAvailable if there is insufficient memory to create the result buffer. Else Success.
**/
SSA_STATUS
(EFIAPI BiosCreateResultBuffer) (
  SSA_BIOS_SERVICES_PPI *This,
  UINT32                MetadataSize,
  UINT32                ResultElementSize,
  UINT32                ResultsCapacity
  );

/**
  Function sets the type of the metadata.

  @param[in, out] This     - Interface pointer that implements the particular SSA_BIOS_SERVICES_PPI instance.
  @param[in]      Revision - Incremented when a backwards compatible binary change is made to the results format.

  @retval NotAvailable if a results buffer has not been created. Else Success.
**/
SSA_STATUS
(EFIAPI BiosSetRevision) (
  SSA_BIOS_SERVICES_PPI *This,
  UINT32                Revision
  );

/**
  Function gets the type of the metadata.

  @param[in, out] This     - Interface pointer that implements the particular SSA_BIOS_SERVICES_PPI instance.
  @param[out]     Revision - Incremented when a backwards compatible binary change is made to the results format.

  @retval UnsupportedValue if Revision is NULL. Else NotAvailable if a results buffer has not been created. Else Success.
**/
SSA_STATUS
(EFIAPI BiosGetRevision) (
  SSA_BIOS_SERVICES_PPI *This,
  UINT32                **Revision
  );

/**
  Function sets the GUID associated with the metadata.

  @param[in, out] This         - Interface pointer that implements the particular SSA_BIOS_SERVICES_PPI instance.
  @param[in]      MetadataType - Address to an EFI_GUID representing a specific metadata type.

  @retval UnsupportedValue if MetadataType is NULL or invalid. Else NotAvailable if a results buffer has not been created. Else Success.
**/
SSA_STATUS
(EFIAPI BiosSetMetadataType) (
  SSA_BIOS_SERVICES_PPI *This,
  EFI_GUID              *MetadataType
  );

/**
  Function gets the GUID associated with the metadata.

  @param[in, out] This         - Interface pointer that implements the particular SSA_BIOS_SERVICES_PPI instance.
  @param[out]     MetadataType - Address to an EFI_GUID representing a specific metadata type.

  @retval UnsupportedValue if MetadataType is NULL. Else NotAvailable if a results buffer has not been created. Else Success.
**/
SSA_STATUS
(EFIAPI BiosGetMetadataType) (
  SSA_BIOS_SERVICES_PPI *This,
  EFI_GUID              **MetadataType
  );

/**
  Function returns the size of the metadata block.

  @param[in, out] This         - Interface pointer that implements the particular SSA_BIOS_SERVICES_PPI instance.
  @param[out]     MetadataSize - The address to the UINT32 in the results data buffer that holds the size.

  @retval UnsupportedValue if MetadataSize is NULL. Else NotAvailable if a results buffer has not been created. Else Success.
**/
SSA_STATUS
(EFIAPI BiosGetMetadataSize) (
  SSA_BIOS_SERVICES_PPI *This,
  UINT32                **MetadataSize
  );

/**
  Function returns the address to the metadata contained in the results data buffer.

  @param[in, out] This     - Interface pointer that implements the particular SSA_BIOS_SERVICES_PPI instance.
  @param[out]     Metadata - The address to the metadata contained in the results data buffer.

  @retval UnsupportedValue if Metadata is NULL. Else NotAvailable if a results buffer has not been created. Else Success.
**/
SSA_STATUS
(EFIAPI BiosGetMetadata) (
  SSA_BIOS_SERVICES_PPI *This,
  VOID                  **Metadata
  );

/**
  Function sets the GUID associated with result elements.

  @param[in, out] This       - Interface pointer that implements the particular SSA_BIOS_SERVICES_PPI instance.
  @param[in]      ResultType - The address to an EFI_GUID representing a specific result type.

  @retval UnsupportedValue if ResultType is NULL or invalid. Else NotAvailable if a results buffer has not been created. Else Success.
**/
SSA_STATUS
(EFIAPI BiosSetResultElementType) (
  SSA_BIOS_SERVICES_PPI *This,
  EFI_GUID              *ResultType
  );

/**
  Function gets the GUID associated with result elements.

  @param[in, out] This       - Interface pointer that implements the particular SSA_BIOS_SERVICES_PPI instance.
  @param[out]     ResultType - The address to an EFI_GUID representing a specific result type.

  @retval UnsupportedValue if ResultType is NULL. Else NotAvailable if a results buffer has not been created. Else Success.
**/
SSA_STATUS
(EFIAPI BiosGetResultElementType) (
  SSA_BIOS_SERVICES_PPI *This,
  EFI_GUID              **ResultType
  );

/**
  Function returns the size a result element.

  @param[in, out] This       - Interface pointer that implements the particular SSA_BIOS_SERVICES_PPI instance.
  @param[out]     ResultSize - Returns the address to the UINT32 in the results data buffer that holds the size.

  @retval UnsupportedValue if ResultSize is NULL. Else NotAvailable if a results buffer has not been created. Else Success.
**/
SSA_STATUS
(EFIAPI BiosGetResultElementSize) (
  SSA_BIOS_SERVICES_PPI *This,
  UINT32                **ResultSize
  );

/**
  Function returns how many elements can be stored in the results data buffer.

  @param[in, out] This           - Interface pointer that implements the particular SSA_BIOS_SERVICES_PPI instance.
  @param[out]     ResultCapacity - Returns the address to the UINT32 in the results data buffer that holds the capacity.

  @retval UnsupportedValue if ResultCapacity is NULL. Else NotAvailable if a results buffer has not been created. Else Success.
**/
SSA_STATUS
(EFIAPI BiosGetResultElementCapacity) (
  SSA_BIOS_SERVICES_PPI *This,
  UINT32                **ResultCapacity
  );

/**
  Function returns how many elements are currently stored in the results data buffer.

  @param[in, out] This        - Interface pointer that implements the particular SSA_BIOS_SERVICES_PPI instance.
  @param[out]     ResultCount - Returns the address to the UINT32 in the results data buffer that holds the current element count.

  @retval UnsupportedValue if ResultCount is NULL. Else NotAvailable if a results buffer has not been created. Else Success.
**/
SSA_STATUS
(EFIAPI BiosGetResultElementCount) (
  SSA_BIOS_SERVICES_PPI *This,
  UINT32                **ResultCount
  );

/**
  Function returns the next available result element in the results data buffer.
  While in automatic transfer mode every time a new element is requested the current element count is checked.
  If the buffer is full the entire block is transferred back to the host and the buffer count is reset.
  Note: results remaining in the buffer will be finalized (transferred, etc) either by the loader when the test completes
  or by CreateResultsBuffer() before it frees any preexisting buffer.

  @param[in, out] This          - Interface pointer that implements the particular SSA_BIOS_SERVICES_PPI instance.
  @param[out]     ResultElement - Returns the address to next available results element in the results data buffer.

  @retval UnsupportedValue if ResultElement is NULL. Else NotAvailable if a results buffer has not been created or there are no results elements available. Else Success.
**/
SSA_STATUS
(EFIAPI BiosGetNextResultElement) (
  SSA_BIOS_SERVICES_PPI *This,
  void                  **ResultElement
  );

/**
  The function toggles the explicit mode either on or off.

  @param[in, out] This - Interface pointer that implements the particular SSA_BIOS_SERVICES_PPI instance.
  @param[in]      Mode - Toggle explicit mode on (TRUE) or off (FALSE).

  @retval NotAvailable if a results buffer has not been created. Else Success.
**/
SSA_STATUS
(EFIAPI BiosSetExplicitTransferMode) (
  SSA_BIOS_SERVICES_PPI *This,
  BOOLEAN               Mode
  );

/**
  The function returns the current explicit mode value.

  @param[in, out] This - Interface pointer that implements the particular SSA_BIOS_SERVICES_PPI instance.
  @param[in, out] Mode - Returns the current explicit mode, on (TRUE) or off (FALSE).

  @retval UnsupportedValue if Mode is NULL. Else NotAvailable if a results buffer has not been created. Else Success.
**/
SSA_STATUS
(EFIAPI BiosGetExplicitTransferMode) (
  SSA_BIOS_SERVICES_PPI *This,
  BOOLEAN               *Mode
  );

/**
  The function flushes the used portion of the results buffer and resets the results data index.
  (Used in explicit transfer mode only.) Note: results remaining in the buffer will be finalized
  (transferred, etc) either by the loader when the test completes or by CreateResultsBuffer()
  before it frees any pre-existing buffer.

  @param[in, out] This - Interface pointer that implements the particular SSA_BIOS_SERVICES_PPI instance.

  @retval NotAvailable if a results buffer has not been created or the explcit transfer mode is FALSE. Else Success.
**/
SSA_STATUS
(EFIAPI BiosPushResults) (
  SSA_BIOS_SERVICES_PPI *This
  );

#endif // __BIOS_SSA_RESULTS_CONFIG__

// end file BiosSsaResultsConfig.h
