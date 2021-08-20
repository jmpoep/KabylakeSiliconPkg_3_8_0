/** @file
  Container definitions and macros.

 @copyright
  INTEL CONFIDENTIAL
  Copyright 2011 - 2016 Intel Corporation.

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

@par Specification
**/

#ifndef _DCTT_SET_CONTAINER_H_
#define _DCTT_SET_CONTAINER_H_

#define MAX_SET_STORAGE_SIZE 500

#define SetStorage_SetDirectionReversed(pSelf, directionReversed) (pSelf)->reversed = (directionReversed)

#define SetStorage_SetSorted(pSelf, IsSorted) (pSelf)->sorted = (IsSorted)

#define SetStorage_GetSize(pSelf) (pSelf)->currentSize

#define SetStorage_GetElement(pSelf, elementNumber) (((elementNumber) >= (pSelf)->currentSize)? (0) : ((pSelf)->storage[(elementNumber)]))
//BOOLEAN SetContainer_AddItem(SetContainer* self, UINT32 setItem)
#define SetContainer_AddItem(pSelf, setItem) SetStorage_AddItem((pSelf)->runStorage, (setItem))

#define SetContainer_NumberElements(pSelf) (pSelf)->mainStorage->currentSize

#define SetContainer_NumberElementsCurrentRun(pSelf) (pSelf)->runStorage->currentSize

#define SetContainer_GetElement(pSelf, elementNumber) (((elementNumber) >= (pSelf)->mainStorage->currentSize)? (0) : ((pSelf)->mainStorage->storage[(elementNumber)]))

#define SetStorage_VARDEF(varName) \
  SetStorage* varName; \
  SetStorage _internalVar_##varName

#define SetStorage_VARINIT(varName) \
  varName = &(_internalVar_##varName);\
  (varName)->maxSize = MAX_SET_STORAGE_SIZE;\
  (varName)->currentSize = 0;\
  (varName)->sorted = TRUE;\
  (varName)->reversed = FALSE

#define SetContainer_VARDEF(varName) \
  SetContainer* varName; \
  SetContainer _internalVar_##varName

#define SetContainer_VARINIT(varName, pStorage1, pStorage2, pStorage3) \
  varName = &(_internalVar_##varName); \
  (varName)->mainStorage = (pStorage1); \
  (varName)->runStorage = (pStorage2); \
  (varName)->auxStorage = (pStorage3)

typedef struct SetStorage {
  BOOLEAN reversed;
  BOOLEAN sorted;
  UINT32 storage[MAX_SET_STORAGE_SIZE];
  UINT32 maxSize;
  UINT32 currentSize;
} SetStorage;

typedef struct SetContainer {
  SetStorage* mainStorage;
  SetStorage* runStorage;
  SetStorage* auxStorage;
} SetContainer;

VOID SetStorage_Init(SetStorage* self);

VOID SetContainer_Init(SetContainer* self, SetStorage* storage1, SetStorage* storage2, SetStorage* storage3);

BOOLEAN SetContainer_InitFromContainer(SetContainer* self, SetStorage* storage1, SetContainer* containerWithAuxStorage);

BOOLEAN SetStorage_AddItem(SetStorage* self, UINT32 setItem);

BOOLEAN SetContainer_ConsolidateStorages(SetContainer* self);

BOOLEAN SetContainer_SortRunStorage(SetContainer* self);

BOOLEAN SetContainer_ForceSortRunStorage(SetContainer* self);

BOOLEAN SetContainer_SetAuxStorages(SetContainer* self, SetStorage** auxStorage1, SetStorage** auxStorage2);

BOOLEAN SetContainer_ReturnAuxStorages(SetContainer* self, SetStorage** auxStorage1, SetStorage** auxStorage2);

BOOLEAN SetContainer_SetRunDirectionUp(SetContainer* self);

BOOLEAN SetContainer_SetRunDirectionDown(SetContainer* self);

BOOLEAN SetContainer_SetRunSorted(SetContainer* self);

BOOLEAN SetContainer_CheckRunIsSorted(SetContainer* self);

BOOLEAN SetContainer_SetRunUnsorted(SetContainer* self);

BOOLEAN SetContainer_TransferAuxStorages(SetContainer* self, SetContainer* containerToReceiveStorages);

UINT32 SetContainer_NumberCommonElements(SetContainer* self, SetContainer* container2);

VOID SetContainer_Clear(SetContainer* self);

//Adds elements in containerToAdd to self
//containerToAdd is allowed to have released its auxiliar storages
//self has to have its storages
BOOLEAN SetContainer_ConsolidateContainers(SetContainer* self, SetContainer* containerToAdd);

//Functions only used for debugging purposes
BOOLEAN _SetContainer_GetMainStorage(SetContainer* self, SetStorage** mainStorageRef);

BOOLEAN _SetContainer_GetRunStorage(SetContainer* self, SetStorage** runStorageRef);

#endif // _DCTT_SET_CONTAINER_H_
