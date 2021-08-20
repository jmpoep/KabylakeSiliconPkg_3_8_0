/** @file
  Container Module for recording errors found during the memory test.

 @copyright
  INTEL CONFIDENTIAL
  Copyright 2011 - 2015 Intel Corporation.

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
#include "DcttWrapper.h"
#include "DcttSetContainer.h"
#include "DcttHelpers.h"

VOID SetStorage_Init (SetStorage* self)
{
  self->maxSize = MAX_SET_STORAGE_SIZE;
  self->currentSize = 0;
  self->sorted = TRUE;
  self->reversed = FALSE;
}

VOID SetContainer_Init (SetContainer* self, SetStorage* storage1, SetStorage* storage2, SetStorage* storage3)
{
  SetStorage_Init (storage1);
  SetStorage_Init (storage2);
  SetStorage_Init (storage3);
  self->mainStorage = storage1;
  self->auxStorage = storage2;
  self->runStorage = storage3;
}

BOOLEAN SetContainer_InitFromContainer (SetContainer* self, SetStorage* storage1, SetContainer* containerWithAuxStorage)
{
  if ((containerWithAuxStorage->auxStorage == NULL) || (containerWithAuxStorage->runStorage == NULL))
  {//We have no run or aux storage; impossible to transfer to self
    return FALSE;
  }
  self->auxStorage = containerWithAuxStorage->auxStorage;
  self->runStorage = containerWithAuxStorage->runStorage;
  self->mainStorage = storage1;
  containerWithAuxStorage->auxStorage = NULL;
  containerWithAuxStorage->runStorage = NULL;

  SetStorage_Init (self->mainStorage);
  SetStorage_Init (self->auxStorage);
  SetStorage_Init (self->runStorage);

  return TRUE;
}

BOOLEAN
SetContainer_TransferAuxStorages (
  SetContainer  *self,
  SetContainer  *containerToReceiveStorages
  )
{
  if ((self->auxStorage == NULL) || (self->runStorage == NULL)) {
    //We do not have aux or run, we cannot transfer
    return FALSE;
  }

  if ((containerToReceiveStorages->auxStorage != NULL) || (containerToReceiveStorages->runStorage != NULL)) {
    //ContainerToReceive has aux or run, we shouldn't transfer
    return FALSE;
  }

  containerToReceiveStorages->auxStorage = self->auxStorage;
  containerToReceiveStorages->runStorage = self->runStorage;
  self->auxStorage = NULL;
  self->runStorage = NULL;

  return TRUE;
}

VOID SetContainer_Clear (SetContainer* self)
{
  SetStorage_Init (self->mainStorage);
  if (self->auxStorage != NULL) {
    SetStorage_Init (self->auxStorage);
  }
  if (self->runStorage != NULL) {
    SetStorage_Init (self->runStorage);
  }
}

BOOLEAN
SetStorage_AddItem (
  SetStorage  *self,
  UINT32 setItem
  )
{
  if (self->currentSize >= self->maxSize) {
    //We run out of space in the storage
    return FALSE;
  }

  self->storage[self->currentSize] = setItem;
  self->currentSize = self->currentSize + 1;
  return TRUE;
}

BOOLEAN
SetContainer_SetRunDirectionUp (
  SetContainer  *self
  )
{
  if (self->runStorage == NULL) {
    return FALSE;
  }

  SetStorage_SetDirectionReversed (self->runStorage, FALSE);
  return TRUE;
}

BOOLEAN SetContainer_SetRunDirectionDown (SetContainer* self)
{
  if (self->runStorage == NULL) {
    return FALSE;
  }
  SetStorage_SetDirectionReversed (self->runStorage, TRUE);
  return TRUE;
}

BOOLEAN SetContainer_SetRunSorted (SetContainer* self)
{
  if (self->runStorage == NULL) {
    return FALSE;
  }
  SetStorage_SetSorted (self->runStorage, TRUE);
  return TRUE;
}

BOOLEAN
SetContainer_SetRunUnsorted (
  SetContainer  *self
  )
{
  if (self->runStorage == NULL) {
    return FALSE;
  }

  SetStorage_SetSorted (self->runStorage, FALSE);
  return TRUE;
}

BOOLEAN SetContainer_SetAuxStorages (SetContainer* self, SetStorage** auxStorage1, SetStorage** auxStorage2)
{
  self->auxStorage = *auxStorage1;
  self->runStorage = *auxStorage2;
  //TODO: Check if it would be better to invalidate the storages passed to the set, ex. Set them to NULL
  *auxStorage1 = NULL;
  *auxStorage2 = NULL;
  return TRUE;
}

BOOLEAN SetContainer_ReturnAuxStorages (SetContainer* self, SetStorage** auxStorage1, SetStorage** auxStorage2)
{
  if ((self->auxStorage == NULL) ||
      (self->runStorage == NULL)) {
    return FALSE;
  }

  *auxStorage1 = self->auxStorage;
  *auxStorage2 = self->runStorage;

  self->auxStorage = NULL;
  self->runStorage = NULL;
  return TRUE;
}

static
VOID
SetStorage_MoveIndex (
  SetStorage  *storage,
  UINT32      *currentIndex
  )
{
  UINT32 currentVal;
  UINT32 storageIndex;

  currentVal = storage->storage[*currentIndex];
  if (storage->reversed) {
    //going down to 0
    if (*currentIndex == 0) {
      //We cannot go back more, return.
      //Put current index to a value 1+ the maximum value on the list
      //to signal that we cannot do more
      *currentIndex = storage->currentSize;
      return;
    }
    //for (storageIndex = (*currentIndex) - 1; storageIndex >= 0; storageIndex--)
    for (storageIndex = (*currentIndex) - 1; storageIndex != ((UINT32) -1); storageIndex--) {
      if (storage->storage[storageIndex] != currentVal) {
        *currentIndex = storageIndex;
        return;
      }
    }
  } else {
    if (*currentIndex >= storage->currentSize) {
      //We cannot go further to the right, return.
      //Put current index to a value 1+ the maximum value on the list
      //to signal that we cannot do more
      *currentIndex = storage->currentSize;
      return;
    }

    for (storageIndex = (*currentIndex) + 1; storageIndex < storage->currentSize; storageIndex++) {
      if (storage->storage[storageIndex] != currentVal) {
        *currentIndex = storageIndex;
        return;
      }
    }
  }
  //If we are here then we went over all the list already
  //Put current index to a value 1+ the maximum value on the list to signal that we cannot do more
  *currentIndex = storage->currentSize;
}

BOOLEAN
SetContainer_ConsolidateContainers (
  SetContainer  *self,
  SetContainer  *containerToAdd
  )
{
  SetStorage *tempSelfStorageRef;
  UINT32 containerToAddCurrentSize;
  BOOLEAN containerToAddReversed, containerToAddSorted; //These 2 shouldn't be needed because they will always have the same value
  BOOLEAN retVal;

  //if ((self->auxStorage == NULL))
  if ((self->auxStorage == NULL) || (self->runStorage == NULL)) {
    //We have no run or aux storage; impossible to consolidate
    //DcttOutputPrint (DcttMain, "\n");
    return FALSE;
  }
  tempSelfStorageRef = self->runStorage;
  containerToAddCurrentSize = containerToAdd->mainStorage->currentSize;
  containerToAddReversed = containerToAdd->mainStorage->reversed;
  containerToAddSorted = containerToAdd->mainStorage->sorted;
  self->runStorage = containerToAdd->mainStorage;

  retVal = SetContainer_ConsolidateStorages (self);

  containerToAdd->mainStorage->currentSize = containerToAddCurrentSize;
  containerToAdd->mainStorage->reversed = containerToAddReversed;
  containerToAdd->mainStorage->sorted = containerToAddSorted;
  self->runStorage = tempSelfStorageRef;

  return retVal;
}

UINT32
SetContainer_NumberCommonElements (
  SetContainer  *self,
  SetContainer  *container2
  )
{
  UINT32 numberCommonElements;
  UINT32 maxNumberElements, elementNumber;
  UINT32 selfIndex, container2Index;

  ////TODO:Not checking for overflow at this point because I am not planning on using storages that are close
  ////to having max(uint32) elements.
  maxNumberElements = self->mainStorage->currentSize + container2->mainStorage->currentSize;
  numberCommonElements = 0;
  selfIndex = 0;
  container2Index = 0;

  for (elementNumber = 0; elementNumber < maxNumberElements; elementNumber++) {
    ////TODO: check if it would be more efficient to collapse
    ////some of the conditions using longer boolean expressions.
    if ((selfIndex >= self->mainStorage->currentSize) || (container2Index >= container2->mainStorage->currentSize)) {
      //Nothing else to do here, one of the list has been completely checked
      //No more common errors can be found
      break;
    } else if (SetStorage_GetElement (self->mainStorage, selfIndex) >
               SetStorage_GetElement (container2->mainStorage, container2Index)) {
      //Container's elements are stored incrementally.  Since the current element in
      //container2 is less than current in self container, increment container2
      //to find a repeated element
      SetStorage_MoveIndex (container2->mainStorage, &container2Index);
    } else if (SetStorage_GetElement (container2->mainStorage,container2Index) >
               SetStorage_GetElement (self->mainStorage, selfIndex)) {
      //Container's elements are stored incrementally.  Since the current element in
      //self container is less than current in container2, increment self container
      //to find a repeated element.
      SetStorage_MoveIndex (self->mainStorage, &selfIndex);
    } else {
      //in this case (self->runStorage[runIndex] == self->mainStorage[mainIndex])
      numberCommonElements++;
      SetStorage_MoveIndex (self->mainStorage, &selfIndex);
      SetStorage_MoveIndex (container2->mainStorage, &container2Index);
    }
  }

  return numberCommonElements;
}

BOOLEAN
SetContainer_ConsolidateStorages (
  SetContainer  *self
  )
{
  UINT32 runIndex;
  UINT32 mainIndex;
  UINT32 maxNumberElements;
  UINT32 elementNumber;
  UINT32 newAuxStorageItem;
  SetStorage* tempStorageRef;

  if ((self->auxStorage == NULL) || (self->runStorage == NULL)) {
    //We have no run or aux storage; impossible to consolidate
    return FALSE;
  }

  if (self->runStorage->currentSize == 0) {
    //We have nothing on the run storage, so there is nothing to consolidate; return
    return TRUE;
  }

  if (self->mainStorage->currentSize >= self->mainStorage->maxSize) {
    //We do not have more storage available for results; no point in trying to consolidate
    return FALSE;
  }

  if (self->runStorage->sorted == FALSE) {
    SetContainer_ForceSortRunStorage (self);
  }

  //At this point run storage and main storage are both sorted. Merge them into AuxStorage
  self->auxStorage->reversed = FALSE;
  self->auxStorage->sorted = TRUE;
  self->auxStorage->currentSize = 0;
  ////TODO:Not checking for overflow at this point because I am not planning on using storages that are close
  ////to having max(uint32) elements.
  maxNumberElements = self->mainStorage->currentSize + self->runStorage->currentSize;

  mainIndex = 0;
  if (self->runStorage->reversed) {
    runIndex = self->runStorage->currentSize - 1;
  } else {
    runIndex = 0;
  }

  for (elementNumber = 0; elementNumber < maxNumberElements; elementNumber++) {
    ////TODO: check if it would be more efficient to collapse
    ////some of the conditions using longer boolean expressions.
    if ((runIndex >= self->runStorage->currentSize) && (mainIndex >= self->mainStorage->currentSize)) {
      //Nothing else to do here, both lists have been completely checked
      break;
    } else if (runIndex >= self->runStorage->currentSize) {
      //run out of run index, get element from main storage
      newAuxStorageItem = self->mainStorage->storage[mainIndex];
      SetStorage_MoveIndex (self->mainStorage, &mainIndex);
    } else if (mainIndex >= self->mainStorage->currentSize) {
      //run out of main index, get element from run storage
      newAuxStorageItem = self->runStorage->storage[runIndex];
      SetStorage_MoveIndex (self->runStorage, &runIndex);
    } else if (SetStorage_GetElement (self->mainStorage,mainIndex) >
               SetStorage_GetElement (self->runStorage, runIndex)) {
      newAuxStorageItem = self->runStorage->storage[runIndex];
      SetStorage_MoveIndex (self->runStorage, &runIndex);
    } else if (SetStorage_GetElement (self->runStorage,runIndex) >
               SetStorage_GetElement (self->mainStorage, mainIndex)) {
      newAuxStorageItem = self->mainStorage->storage[mainIndex];
      SetStorage_MoveIndex (self->mainStorage, &mainIndex);
    } else {
      //in this case (self->runStorage[runIndex] == self->mainStorage[mainIndex])
      newAuxStorageItem = self->mainStorage->storage[mainIndex];
      SetStorage_MoveIndex (self->mainStorage, &mainIndex);
      SetStorage_MoveIndex (self->runStorage, &runIndex);
    }

    //Add new element to the aux storage
    if (!SetStorage_AddItem (self->auxStorage, newAuxStorageItem)) {
      //Run out of space in the auxStorage; stop merging
      break;
    }
  }

  //Reorganize the storages, at this point aux storage is the main storage
  tempStorageRef = self->mainStorage;
  self->mainStorage = self->auxStorage;
  self->auxStorage = tempStorageRef;
  self->auxStorage->currentSize = 0;
  self->runStorage->currentSize = 0;

  return TRUE;
}

BOOLEAN SetContainer_CheckRunIsSorted (SetContainer* self)
{
  UINT32 numElements, elementIndex;

  if ((self->auxStorage == NULL) || (self->runStorage == NULL))
  {//We have no run or aux storage; impossible to sort
    return FALSE;
  }
  if (self->runStorage->currentSize == 0)
  {//We have nothing on the run storage, so there is nothing to check
    return TRUE;
  }
  numElements = self->runStorage->currentSize;
  for (elementIndex = 0; elementIndex < numElements - 1; elementIndex++) {
    //If could be combined in one
    if ((!(self->runStorage->reversed)) && (self->runStorage->storage[elementIndex] > self->runStorage->storage[elementIndex + 1])) {
      self->runStorage->sorted = FALSE;
      return FALSE;
    } else if ((self->runStorage->reversed) && (self->runStorage->storage[elementIndex] < self->runStorage->storage[elementIndex + 1])) {
      self->runStorage->sorted = FALSE;
      return FALSE;
    }
  }
  self->runStorage->sorted = TRUE;
  return TRUE;
}

BOOLEAN SetContainer_SortRunStorage (SetContainer* self)
{
  if ((self->auxStorage == NULL) || (self->runStorage == NULL))
  {//We have no run or aux storage; impossible to sort
    return FALSE;
  }
  if (self->runStorage->sorted) {
    //If the storage says that it is sorted, skip the sorting
    return TRUE;
  } else {
    return SetContainer_ForceSortRunStorage (self);
  }
}

BOOLEAN
SetContainer_ForceSortRunStorage (
  SetContainer  *self
  )
{
  UINT32 arr1Start, arr2Start, arrEnd, indexArr1, indexArr2, arrWidth, numElements, indexResult;
  SetStorage* storageRef;

  if ((self->auxStorage == NULL) || (self->runStorage == NULL)) {
    //We have no run or aux storage; impossible to sort
    return FALSE;
  }
  if (self->runStorage->currentSize == 0) {
    //We have nothing on the run storage, so there is nothing to sort
    return TRUE;
  }
  numElements = self->runStorage->currentSize;

  for (arrWidth = 1; arrWidth < numElements; arrWidth = arrWidth * 2) {
    for (arr1Start = 0; arr1Start < numElements; arr1Start = arr1Start + arrWidth * 2) {
      arr2Start = MIN (arr1Start + arrWidth, numElements);
      arrEnd = MIN (arr1Start + arrWidth * 2, numElements);

      indexArr1 = arr1Start;
      indexArr2 = arr2Start;
      for (indexResult = arr1Start; indexResult < arrEnd; indexResult++) {
        if ((indexArr1 < arr2Start) &&
            ((indexArr2 >= arrEnd) || (self->runStorage->storage[indexArr1] <= self->runStorage->storage[indexArr2]))) {
          //We have an element on the first part of the array and either
          //is less than the current element on the second half or we
          //have run out of second half elements
          self->auxStorage->storage[indexResult] = self->runStorage->storage[indexArr1];
          indexArr1++;
        } else {
          self->auxStorage->storage[indexResult] = self->runStorage->storage[indexArr2];
          indexArr2++;
        }
      }
    }

    storageRef = self->runStorage;
    self->runStorage = self->auxStorage;
    self->auxStorage = storageRef;
  }

  self->runStorage->currentSize = numElements;
  self->runStorage->sorted = TRUE;
  self->runStorage->reversed = FALSE;

  self->auxStorage->currentSize = 0;
  self->auxStorage->sorted = TRUE;
  self->auxStorage->reversed = FALSE;

  return TRUE;
}

//Function only used for debugging purposes
BOOLEAN _SetContainer_GetMainStorage (SetContainer* self, SetStorage** mainStorageRef)
{
  *mainStorageRef = self->mainStorage;
  return TRUE;
}

BOOLEAN _SetContainer_GetRunStorage (SetContainer* self, SetStorage** runStorageRef)
{
  *runStorageRef = self->runStorage;
  if (self->runStorage == NULL) {
    return FALSE;
  }
  return TRUE;
}
