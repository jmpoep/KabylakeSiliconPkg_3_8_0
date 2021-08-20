/** @file
  BIOS SSA loader ITP implementation.

 @copyright
  INTEL CONFIDENTIAL
  Copyright 1999 - 2015 Intel Corporation.

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

#include "EvItpDownloadAgent.h"
#include "ScratchPadReg.h"
#include "PeLoader.h"

#ifdef _MSC_VER
#pragma warning(disable : 4100)
#endif

UINT32
FlushBios (
  void
  )
{
  UINT32          temp;
  UINT32          codeRegionStartAdr = 0xFFF00000;
  UINT32          codeSizeInDWords = 128 * 1024 / 4;   // 128K / 4
  volatile UINT32 *codeAdr;
  UINT32          DWordIdx;
  UINT32          repeatCnt = 2;
  UINT32          repeatIdx;

  temp = 0;
  for (repeatIdx = 0 ; repeatIdx < repeatCnt; repeatIdx++) {
    for (DWordIdx = 0; DWordIdx < codeSizeInDWords; DWordIdx++) {
      codeAdr = (volatile UINT32 *) (codeRegionStartAdr + DWordIdx * 4);
      temp |= *codeAdr;
    }
  }

  return temp;
}
//
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
//
MrcStatus
EvItpDownloadCmd (
  SSA_BIOS_SERVICES_PPI *SsaServicesPpi,
  VOID                  *CheckpointData
  )
/*++

Routine Description:

  Do EV commands while at a the RUN_EV_TOOL checkpoint

Arguments:

  pHandle     - Pointer to the system structure

Returns:

  0 - successful
  1 - failure

--*/
{
  MRC_EV_AGENT_CMD_STRUCT               cmdReg;
  UINT32                                toolSize;
  UINT32                                imageHandle = 0;
  UINT32                                inputNum = 0;
  UINT32                                entryPoint;
  UINT32                                inputBufferForITP = 0;
  UINT32                                memBlockHandle = 0;
  UINT16                                majorRev;
  UINT16                                minorRev;
  BOOLEAN                               exitCmdLoop = FALSE;
  EFI_PHYSICAL_ADDRESS                  baseAddress;
  SSA_STATUS                            retStatus;
  VOID *                                OriginalResultsData = NULL;
  const SCRATCHPAD_REGISTER_FUNCTIONS   *scratchpadFunctions;

  //
  // Memory buffer to separate downloaded code from other data.
  // basically the download image is sandwiched by these 4KB buffer.
  //
  UINT32 totalImageBuffer = 0;

  //
  // "EVCP" - EV Check Point
  //
  UINT32 checkPoint = ('E' << 24) | ('V' << 16) | ('C' <<8) | 'P';

  EV_LOADER_PRINT (DEBUG_ERROR, "Inside EV agent ... \n");

  scratchpadFunctions = GetScratchpadFunctions (SsaServicesPpi);


  retStatus = SsaServicesPpi->SsaCommonConfig->GetBaseAddress (SsaServicesPpi, 0, 0, 0, MCH_BAR,&baseAddress);
  if (retStatus != Success) {
    //TODO: Handle error condition
  }

  //
  // First indicate we are in the checkpoint where running EV content
  //
  scratchpadFunctions->writeScratchPad_currentCheckPoint (SsaServicesPpi, baseAddress, checkPoint);

  //
  // Backup the ResultsData on the remote chance another
  // module was using it.
  //
  OriginalResultsData = SsaServicesPpi->SsaResultsConfig->ResultsData;

  do {
    //
    // Read scratchpad register to get the EV command
    //
    cmdReg.Data = scratchpadFunctions->readScratchPad_CMD (SsaServicesPpi, baseAddress);

    //
    // Execute cmd
    //
    if (cmdReg.Bits.command_pending_execution) {
      //
      // Update the cmd register to indicate the cmd is no more pending
      //
      cmdReg.Bits.command_pending_execution = MRC_EVAGENT_NO_PENDING_CMD;
      cmdReg.Bits.status                    = MRC_EVAGENT_STATUS_BUSY;
      scratchpadFunctions->writeScratchPad_CMD (SsaServicesPpi, baseAddress, cmdReg.Data);

      //
      // Execute
      //
      switch (cmdReg.Bits.command_opcode) {
        //
        // PING
        //
        case MRC_EVAGENT_CMD_PING:
          //
          // Update status
          //
          cmdReg.Bits.error_code = MRC_EVAGENT_CMD_NO_ERROR;
          break;

          //
          // Get the callback table revision
          //
        case MRC_EVAGENT_CMD_GET_CALLBACK_REV:

          EV_LOADER_PRINT (
            DEBUG_ERROR,
            "MRC_EVAGENT_CMD_GET_CALLBACK_REV  called ... \n"
            );
          majorRev = *(((UINT16*) (&SsaServicesPpi->SsaCommonConfig->Revision)) + 1);
          minorRev = *((UINT16*) (&SsaServicesPpi->SsaCommonConfig->Revision));
          scratchpadFunctions->writeScratchPad_DATA0 (SsaServicesPpi, baseAddress, majorRev);
          scratchpadFunctions->writeScratchPad_DATA1 (SsaServicesPpi, baseAddress, minorRev);
          cmdReg.Bits.error_code = MRC_EVAGENT_CMD_NO_ERROR;
          break;

        case MRC_EVAGENT_CMD_GET_AGENT_VERSION:
          EV_LOADER_PRINT (
            DEBUG_ERROR,
            "MRC_EVAGENT_CMD_GET_AGENT_VERSION  called ... \n"
            );
          scratchpadFunctions->writeScratchPad_DATA0 (SsaServicesPpi, baseAddress, (TOOL_MAJOR_VERSION << 16) | (TOOL_MINOR_VERSION));
          scratchpadFunctions->writeScratchPad_DATA1 (SsaServicesPpi, baseAddress, TOOL_REVISION);
          cmdReg.Bits.error_code = MRC_EVAGENT_CMD_NO_ERROR;
          break;

        case MRC_EVAGENT_CMD_GET_DLL_VERSION:
          EV_LOADER_PRINT (
            DEBUG_ERROR,
            "MRC_EVAGENT_CMD_GET_DLL_VERSION  called ... \n"
            );
          if (imageHandle) {
            //
            // Call the PE module
            //
            entryPoint = GetPeEntrypoint ((UINT8 *) imageHandle);

            cmdReg.Bits.error_code = MRC_EVAGENT_CMD_NO_ERROR;
          } else {
            cmdReg.Bits.error_code = MRC_EVAGENT_CMD_ERROR_INVALID_TOOL_HANDLE;
          }
          break;

        case MRC_EVAGENT_CMD_FLUSH_CACHE:
          EV_LOADER_PRINT (
            DEBUG_ERROR,
            "MRC_EVAGENT_CMD_GET_DLL_VERSION  called ... \n"
            );

          FlushBios ();
          cmdReg.Bits.error_code = MRC_EVAGENT_CMD_NO_ERROR;
          EV_LOADER_PRINT (
            DEBUG_ERROR,
            "MRC_EVAGENT_CMD_GET_DLL_VERSION  done ... \n"
            );
          break;
          //
          // Get the memory buffer where the EV tool will be placed
          //
        case MRC_EVAGENT_CMD_GET_TOOL_BUFFER:
          //
          // Get the size of the tool image
          //
          toolSize = scratchpadFunctions->readScratchPad_DATA0 (SsaServicesPpi, baseAddress);

          EV_LOADER_PRINT (
            DEBUG_ERROR,
            "MRC_EVAGENT_CMD_GET_DLL_VERSION before malloc ... \n"
            );

          //
          // Reserve 4KB buffers below and above the tool image
          //
          totalImageBuffer = (UINT32) SsaServicesPpi->SsaCommonConfig->Malloc (SsaServicesPpi, (1024 * 4) + toolSize + (1024 * 4));
          imageHandle = totalImageBuffer + (1024 * 4);

          EV_LOADER_PRINT (
            DEBUG_ERROR,
            "MRC_EVAGENT_CMD_GET_DLL_VERSION after malloc ... \n"
            );

          //
          // Update the data0 with the imageHandle
          //
          scratchpadFunctions->writeScratchPad_DATA0 (SsaServicesPpi, baseAddress, imageHandle);

          EV_LOADER_PRINT (
            DEBUG_ERROR,
            "MRC_EVAGENT_CMD_GET_DLL_VERSION after writeScratchPad_DATA0 ... \n"
            );

          if (!totalImageBuffer) {
            EV_LOADER_PRINT (
              DEBUG_ERROR,
              "MRC_EVAGENT_CMD_GET_DLL_VERSION  !totalImageBuffer ... \n"
              );
          }

          if (!totalImageBuffer) {
            cmdReg.Bits.error_code = MRC_EVAGENT_CMD_ERROR_MALLOC_FAIL;
          } else {
            cmdReg.Bits.error_code = MRC_EVAGENT_CMD_NO_ERROR;
          }
          EV_LOADER_PRINT (
            DEBUG_ERROR,
            "MRC_EVAGENT_CMD_GET_DLL_VERSION  done ... \n"
            );
          break;
          //
          //Free Results
          //
        case MRC_EVAGENT_CMD_FREE_RESULTS:
          EV_LOADER_PRINT (
            DEBUG_ERROR,
            "MRC_EVAGENT_CMD_FREE_RESULTS  called ... \n"
            );
          if (SsaServicesPpi->SsaResultsConfig->ResultsData != NULL) {
            EV_LOADER_PRINT (
              DEBUG_ERROR,
              "Freeing Result Buffer ... \n"
              );
            SsaServicesPpi->SsaCommonConfig->Free (SsaServicesPpi, SsaServicesPpi->SsaResultsConfig->ResultsData);
            SsaServicesPpi->SsaResultsConfig->ResultsData = NULL;
          }
          cmdReg.Bits.error_code = MRC_EVAGENT_CMD_NO_ERROR;
          break;
          //
          // Load tool
          //
        case MRC_EVAGENT_CMD_LOAD_TOOL:
          EV_LOADER_PRINT (
            DEBUG_ERROR,
            "MRC_EVAGENT_CMD_LOAD_TOOL  called ... \n"
            );
          //
          // Call loader to locate the PE module
          //
          if (imageHandle) {
            PlacePeImage ((UINT8 *) imageHandle);
            FlushBios ();
            cmdReg.Bits.error_code = MRC_EVAGENT_CMD_NO_ERROR;
          } else {
            cmdReg.Bits.error_code = MRC_EVAGENT_CMD_ERROR_INVALID_TOOL_HANDLE;
          }
          EV_LOADER_PRINT (
            DEBUG_ERROR,
            "MRC_EVAGENT_CMD_LOAD_TOOL  done ... \n"
            );
          break;
          //
          // Unload tool
          //
        case MRC_EVAGENT_CMD_UNLOAD_TOOL:
          //
          // Get the imageHandle of the tool image from data0
          //
          memBlockHandle = scratchpadFunctions->readScratchPad_DATA0 (SsaServicesPpi, baseAddress);
          if ((memBlockHandle == imageHandle) && (memBlockHandle != 0)) {
            //
            // Free the two memory buffers as well
            //
            SsaServicesPpi->SsaCommonConfig->Free (SsaServicesPpi, (void *) totalImageBuffer);
            //
            // Reset the imageHandle
            //
            imageHandle = 0;
            totalImageBuffer = 0;
            cmdReg.Bits.error_code = MRC_EVAGENT_CMD_NO_ERROR;
          } else {
            cmdReg.Bits.error_code = MRC_EVAGENT_CMD_ERROR_INVALID_TOOL_HANDLE;
          }
          break;

          //
          // Get the location of input parameter and output data
          //
        case MRC_EVAGENT_CMD_GET_INPUT_BUFFER:
          EV_LOADER_PRINT (
            DEBUG_ERROR,
            "MRC_EVAGENT_CMD_GET_INPUT_BUFFER  called ... \n"
            );
          //
          // Get the number of input and output from data0 and data1
          //
          inputNum = scratchpadFunctions->readScratchPad_DATA0 (SsaServicesPpi, baseAddress);
          EV_LOADER_PRINT (
            DEBUG_ERROR,
            "MRC_EVAGENT_CMD_GET_INPUT_BUFFER  readScratchPad_DATA0 done ... \n"
            );
          //
          // Input location
          //
          inputBufferForITP = (UINT32) SsaServicesPpi->SsaCommonConfig->Malloc (SsaServicesPpi, (inputNum * sizeof (UINT32)));

          //
          // Update the data0 and data1
          //
          scratchpadFunctions->writeScratchPad_DATA0 (SsaServicesPpi, baseAddress, inputBufferForITP);

          if (!inputBufferForITP) {
            cmdReg.Bits.error_code = MRC_EVAGENT_CMD_ERROR_MALLOC_FAIL;
          } else {
            cmdReg.Bits.error_code = MRC_EVAGENT_CMD_NO_ERROR;
          }
          break;

          //
          // Release the memory occupied by the input parameter and output data
          //
        case MRC_EVAGENT_CMD_FREE_MEMORY:
          //
          // Get the memory block handle(aka. address) from data0
          //
          memBlockHandle = scratchpadFunctions->readScratchPad_DATA0 (SsaServicesPpi, baseAddress);

          if (memBlockHandle) {
            SsaServicesPpi->SsaCommonConfig->Free (SsaServicesPpi, (void *) memBlockHandle);
            cmdReg.Bits.error_code = MRC_EVAGENT_CMD_NO_ERROR;
          } else {
            cmdReg.Bits.error_code = MRC_EVAGENT_CMD_ERROR_INVALID_MEMORY_HANDLE;
          }
          break;

          //
          // Run EV tool
          //
        case MRC_EVAGENT_CMD_RUN_EV_TOOL:
          EV_LOADER_PRINT (
            DEBUG_ERROR,
            "MRC_EVAGENT_CMD_RUN_EV_TOOL  called ... \n"
            );
          //
          // Check imageHandle first
          //
          if (imageHandle) {
            //
            // Call the PE module
            //
            entryPoint = GetPeEntrypoint ((UINT8 *) imageHandle);

            ((EvToolEntryPoint*) entryPoint) (SsaServicesPpi, (UINT32 *) inputBufferForITP);

            //
            // If there are results
            //
            if (SsaServicesPpi->SsaResultsConfig->ResultsData != NULL) {
              RESULTS_DATA_HDR *ResultsDataHdr;
              UINT32 ResultsDataSize;

              ResultsDataHdr = (RESULTS_DATA_HDR *) SsaServicesPpi->SsaResultsConfig->ResultsData;
              ResultsDataSize = sizeof (RESULTS_DATA_HDR) + ResultsDataHdr->MdBlock.MetadataSize + ( ResultsDataHdr->RsBlock.ResultElementSize * ResultsDataHdr->RsBlock.ResultCapacity);

              //
              // Set the results block memory position.
              //
              scratchpadFunctions->writeScratchPad_DATA0 (SsaServicesPpi, baseAddress, (UINT32) SsaServicesPpi->SsaResultsConfig->ResultsData);
              //
              // Set the results block size.
              //
              scratchpadFunctions->writeScratchPad_DATA1 (SsaServicesPpi, baseAddress, ResultsDataSize);
              cmdReg.Bits.error_code = MRC_EVAGENT_CMD_NO_ERROR;
            } else {  // No results to pass back
              //
              // Set the results block memory position.
              //
              scratchpadFunctions->writeScratchPad_DATA0 (SsaServicesPpi, baseAddress, 0);
              //
              // Set the results block size.
              //
              scratchpadFunctions->writeScratchPad_DATA1 (SsaServicesPpi, baseAddress, 0);
              cmdReg.Bits.error_code = MRC_EVAGENT_CMD_NO_ERROR;
            }
          } else {
            cmdReg.Bits.error_code = MRC_EVAGENT_CMD_ERROR_INVALID_TOOL_HANDLE;
          }
          break;
          //
          // EXIT
          //
        case MRC_EVAGENT_CMD_EXIT:
          exitCmdLoop = TRUE;
          //
          // Update status
          //
          cmdReg.Bits.error_code = MRC_EVAGENT_CMD_NO_ERROR;
          break;

        default:
          //
          // Unknown command
          //
          cmdReg.Bits.error_code = MRC_EVAGENT_CMD_ERROR_UNKNOWN_CMD;
          break;
      }

      //
      // Update status
      //
      cmdReg.Bits.status = MRC_EVAGENT_STATUS_READY;
      scratchpadFunctions->writeScratchPad_CMD (SsaServicesPpi, baseAddress, cmdReg.Data);
    } // cmdReg.Bits.command_pending_execution
  } while (!exitCmdLoop); // While still in the cmd loop

  SsaServicesPpi->SsaResultsConfig->ResultsData = OriginalResultsData;

  return mrcSuccess;

}
