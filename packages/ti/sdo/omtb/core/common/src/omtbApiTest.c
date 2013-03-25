/*
 * omtbApiTest.c
 *
 * This file contains function dispatchers for each OMX IL API validation.
 *
 * Copyright (C) 2010 Texas Instruments Incorporated - http://www.ti.com/
 *
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *    Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 *    Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the
 *    distribution.
 *
 *    Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 *  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
*/

/******************************************************************************\
 *      Standard Includes
\******************************************************************************/

#include <stdio.h>
#include <string.h>

/* OMX standard header files */
#include "OMX_Core.h"
#include "OMX_Component.h"
#include "OMX_Types.h"
//#include "OMX_TI_Video.h"
#include "OMX_TI_Index.h"


/******************************************************************************\
 *      Customized Includes
\******************************************************************************/

#include "omtbDebug.h"
#include "timm_osal_interfaces.h"
#include "mxDbg.h"
#include "omtbCommon.h"
#include "omtbCmd.h"
#include "omtbApi.h"
#include "omtbApiTest.h"


/******************************************************************************\
 *      Local Defines
\******************************************************************************/

#define OMTB_API_TEST_RESULT_PRINT(err, fpResult, testCaseResult, testCaseId) 

  
/******************************************************************************\
 *      Data type definitions
\******************************************************************************/


/******************************************************************************\
 *      Extern Object Definitions
\******************************************************************************/


/******************************************************************************\
 *      Globals
\******************************************************************************/


/******************************************************************************\
 *      Public Function Prototype
\******************************************************************************/


/******************************************************************************\
 *      Static Globals
\******************************************************************************/

/* Callback structure Definition */

static OMX_CALLBACKTYPE OMTB_APITestCallback = {
  OMTB_APITestEventHandler,       /* Event handler callback */    
  OMTB_APITestEmptyBufferDone,    /* Empty buffer done callback */
  OMTB_APITestFillBufferDone      /* Fill buffer done callback */ 
};


/******************************************************************************\
 *      Private Function Declarations
\******************************************************************************/


/******************************************************************************\
 *      OMTB_APITestEventHandler callback Function Definition
\******************************************************************************/
/**
 *
 *  @brief    Event handler Callback
 *
 *  @param in:
 *            hComponent: Component Handle
 *
 *            pAppData  : Pointer to Private Data Structure
 *
 *            eEvent    : Variable to OMX_EVENTTYPE enum
 *
 *            nData1     : data associated with event
 *
 *            nData2     : data associated with event
 *
 *            pEventData: Extra Data associated with the event
 *
 *  @return   err       : OMX_ErrorType
 *
 */

OMX_ERRORTYPE OMTB_APITestEventHandler(
  OMX_OUT OMX_HANDLETYPE hComponent,
  OMX_OUT OMX_PTR pAppData,
  OMX_OUT OMX_EVENTTYPE eEvent,
  OMX_OUT OMX_U32 nData1,
  OMX_OUT OMX_U32 nData2,
  OMX_OUT OMX_PTR pEventData)
{
  OMX_ERRORTYPE err = OMX_ErrorNone;

  /* thread argument validation */
  ASSERT(NULL != hComponent);
  ASSERT(NULL != pAppData);
  

  PRINT(PRINT_FUNCTION_NAME, "Entering <Callback> : <%s>\n", __FUNCTION__);

  /* Check the eEvent type */
  switch(eEvent)
  {
    case OMX_EventCmdComplete:  /* Command complete event */
      {
        /* state transition command related event */
        if (OMX_CommandStateSet == nData1)
        {
          PRINT(PRINT_MUST, 
                "In %s: OMX_EventCmdComplete -  OMX_CommandStateSet\n",
                __FUNCTION__);
          
          switch ((int)nData2)
          {
            case OMX_StateInvalid:
                  PRINT(PRINT_MUST, "OMX_StateInvalid\n");
                  break;
            case OMX_StateLoaded:
                  PRINT(PRINT_MUST, "OMX_StateLoaded\n");
                  break;
            case OMX_StateIdle:
                  PRINT(PRINT_MUST, "OMX_StateIdle\n");
                  break;
            case OMX_StateExecuting:
                  PRINT(PRINT_MUST, "OMX_StateExecuting\n");
                  break;
            case OMX_StatePause:
                  PRINT(PRINT_MUST, "OMX_StatePause\n");
                  break;
            case OMX_StateWaitForResources:
                  PRINT(PRINT_MUST, "OMX_StateWaitForResources\n");
                  break;
          }

          /* Post the component event sem */
//          TIMM_OSAL_SemaphoreRelease(thisClient->omtbPvt.eventSem);
        }
        /* port enable command event */
        else if ( OMX_CommandPortEnable == nData1 )
        {
          PRINT(PRINT_MUST,
                "In %s: OMX_CommandPortEnable on %d port\n", __FUNCTION__, nData2);

        }
        /* port disable command event */
        else if ( OMX_CommandPortDisable == nData1  )
        {
          PRINT(PRINT_MUST,
                "In %s: OMX_CommandPortDisable on %d port\n", __FUNCTION__, nData2);

        }
        /* port flush command event */
        else if ( OMX_CommandFlush == nData1  )
        {
          PRINT(PRINT_MUST,
                "In %s: OMX_CommandFlush on %d port\n", __FUNCTION__, nData2);

        }
        /* port disable command event */
        else if ( OMX_CommandMarkBuffer == nData1  )
        {
          PRINT(PRINT_MUST,
                "In %s: OMX_CommandMarkBuffer on %d port\n", __FUNCTION__, nData2);

        }
      }
      break;
    
    case OMX_EventPortSettingsChanged: /* Port settings changed event */
      {
        PRINT(PRINT_MUST, "In %s: OMX_EventPortSettingsChanged on %d port\n",
                                    __FUNCTION__, nData1);

        if(0 == nData2)
        {
          /* Perform the port settings as per params received from component */

        }
      }
      break;
    
    case OMX_EventBufferFlag:  /* Buffer related events */
      {
        PRINT(PRINT_MUST, "In %s: OMX_EventBufferFlag - nFlags: %x on %d port\n",
                          __FUNCTION__, nData2, nData1);
        if(OMX_BUFFERFLAG_EOS == (int)(nData2 & OMX_BUFFERFLAG_EOS))
        {
          PRINT(PRINT_MUST, "OMX_EventBufferFlag - OMX_BUFFERFLAG_EOS\n");

          /* Commented temporarily as component sends EOS after each frame */
          //TIMM_OSAL_SemaphoreRelease(thisClient->eofSem);
        }
      }
      break;
    
    case OMX_EventError:  /* Event error */
      {
        PRINT(PRINT_MUST, "In %s: OMX_EventError - %x\n", __FUNCTION__, nData1);
        
      }
      break;
    
    case OMX_EventMark: /* Event mark buffer */
      {
        PRINT(PRINT_MUST, "In %s: OMX_EventMark\n", __FUNCTION__);
        
      }
      break;
    
    case OMX_EventResourcesAcquired:  /* Event resources acquired */
      {
        PRINT(PRINT_MUST, "In %s: OMX_EventResourcesAcquired\n",
              __FUNCTION__);
        
      }
      break;
    
    case OMX_EventComponentResumed: /* Event component resumed */
      {
        PRINT(PRINT_MUST, "In %s: OMX_EventComponentResumed\n",
              __FUNCTION__);
        
      }
      break;
    
    case OMX_EventDynamicResourcesAvailable:// Event dynamic resources available
      {
        PRINT(PRINT_MUST, 
              "In %s: OMX_EventDynamicResourcesAvailable\n",
              __FUNCTION__);
        
      }
      break;
    
    case OMX_EventMax: // Event not implemented
      {
        PRINT(PRINT_MUST, "In %s: Param1 is %i\n",
              __FUNCTION__, (int)nData1);
        PRINT(PRINT_MUST, "In %s: Param2 is %i\n",
              __FUNCTION__, (int)nData2);
        err = OMX_ErrorNotImplemented;
      }
      break;
    
    default:    // Event Bad parameter
      {
        PRINT(PRINT_MUST, "In %s: Param1 is %i\n",
              __FUNCTION__, (int)nData1);
        PRINT(PRINT_MUST, "In %s: Param2 is %i\n",
              __FUNCTION__, (int)nData2);
        err = OMX_ErrorBadParameter;
      }
      break;

  } // switch(eEvent)
    
  PRINT(PRINT_FUNCTION_NAME, "Leaving <Callback> : <%s>\n", __FUNCTION__);
  
  return err;
}


/******************************************************************************\
 *      OMTB_APITestEmptyBufferDone callback Function Definition
\******************************************************************************/
/**
 *
 *  @brief    EmptyBufferDone Callback
 *
 *  @param in:
 *            hComponent: Component Handle
 *
 *            ptrAppData: Pointer to Private Data Structure
 *
 *            pBuffer   : Pointer to i/p Buffer
 *
 *  @return   err       : OMX_ErrorType
 *
 */

OMX_ERRORTYPE OMTB_APITestEmptyBufferDone(
  OMX_HANDLETYPE hComponent,
  OMX_PTR ptrAppData,
  OMX_BUFFERHEADERTYPE* pBuffer)
{

  OMX_ERRORTYPE err = OMX_ErrorNone;
  OMTB_OMX_API_TIMING_VAR_DECL;

  /* validate the function arguments */
  ASSERT(NULL != hComponent);
  ASSERT(NULL != pBuffer);
  
  /* API entry time calculation macro */
  //  OMTB_OMX_API_ENTRY_TIME_CALC;
  
  PRINT(PRINT_FUNCTION_NAME, "Entering <Callback> : <%s>\n", __FUNCTION__);
  PRINT(PRINT_DEBUG_MESSAGE, "Address of pBuffer in emptybuff: %x\n",
                              (unsigned int) pBuffer);
  
  PRINT(PRINT_FUNCTION_NAME, "Leaving <Callback> : <%s>\n", __FUNCTION__);
  
  /* API exit time calculation macro */
  //  OMTB_OMX_API_EXIT_TIME_CALC("EmptyBufferDone");
  
  return err;
}


/******************************************************************************\
 *      OMTB_APITestFillBufferDone callback Function Definition
\******************************************************************************/
/**
 *
 *  @brief    FillBufferDone Callback
 *
 *  @param in:
 *            hComponent: Component Handle
 *            ptrAppData: Pointer to Private Data Structure
 *            pBuffer   : Pointer to o/p Buffer
 *
 *  @return   err       : OMX_ErrorType
 *
 */

OMX_ERRORTYPE OMTB_APITestFillBufferDone(
  OMX_HANDLETYPE hComponent,
  OMX_PTR ptrAppData,
  OMX_BUFFERHEADERTYPE* pBuffer)
{

  OMX_ERRORTYPE err = OMX_ErrorNone;
  OMTB_OMX_API_TIMING_VAR_DECL;

  /* validate the function arguments */
  ASSERT(NULL != hComponent);
  ASSERT(NULL != pBuffer);
  
  /* API entry time calculation macro */
  //  OMTB_OMX_API_ENTRY_TIME_CALC;
  
  PRINT(PRINT_FUNCTION_NAME, "Entering <Callback> : <%s>\n", __FUNCTION__);
  PRINT(PRINT_DEBUG_MESSAGE, "Address of pBuffer in fillbuff: %x\n",
                              (unsigned int) pBuffer);
  
  PRINT(PRINT_FUNCTION_NAME, "Leaving <Callback> : <%s>\n", __FUNCTION__);
  
  /* API exit time calculation macro */
  //  OMTB_OMX_API_EXIT_TIME_CALC("FillBufferDone");
  
  return err;
}


/******************************************************************************\
 *      OMTB_OmxInitOnce Function Definition
\******************************************************************************/
/**
 *
 *  @brief    This Function performs OMX_Init API testing.
 *
 *  @param    Pointer to MX_DBG_CMD_CONTEXT_T structure
 *            Pointer to MX_DBG_CMD_Entry_T structure
 *            Character Double Pointer containing the command
 *
 *  @return   ERR_NOERR           successful,
 *            ERR_END_OF_CMD      help was requested,
 *            ERR_INVNAME         otherwise.
 */

MX_Result
OMTB_OmxInitOnce(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine
)
{
  MX_Result  result = ERR_NOERR;
  OMX_ERRORTYPE err = OMX_ErrorNone;
  char componentRequested[OMTB_MAX_LEN] = {"\0"};
  char resultFileName[OMTB_MAX_LEN] = {"\0"};
  char fOpenMode[OMTB_MAX_LEN] = {"\0"};
  char testCaseId[OMTB_MAX_LEN] = {"\0"};
  char testCaseResult[OMTB_MAX_LEN] = {"\0"}; char returnString[OMTB_MAX_LEN] = {"\0"};
  FILE *fpResult = NULL;
  OMTB_OMX_API_TIMING_VAR_DECL;

  /* Read testcase ID */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, testCaseId);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }
  
  /* Read component type */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, componentRequested);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }

  /* Read result filename */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, resultFileName);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }

  /* Read result file type */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, fOpenMode);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }

  /* Open the result file */
  fpResult = fopen(resultFileName, fOpenMode);

  if(NULL == fpResult)
  {
    PRINT(PRINT_ERR_MSG, "%s: Error in result file open\n", __FUNCTION__);
    fprintf(fpResult, "%s : Error in result file open\n", testCaseId);
    return ERR_INVNAME;
  }

  /* OpenMax core initialization once */
    
  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;

  err = OMX_Init ();

  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_Init");

  if(OMX_ErrorNone == err)
  {
    strcpy(testCaseResult, "PASS");
    fprintf(fpResult, "%s : %s\n", testCaseId, testCaseResult);
  }
  else
  {
    OMTB_OmxReturnStatusString(err, returnString);
    strcpy(testCaseResult, "FAIL");
    fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
    fclose(fpResult);
    return ERR_INVNAME;
  }

  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;

  /* OpenMax core uninitialization */
  err = OMX_Deinit ();

  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_Deinit");

  if(OMX_ErrorNone != err)
  {
    OMTB_OmxReturnStatusString(err, returnString);
    strcpy(testCaseResult, "FAIL - Error in OMX_Deinit()\n");
    fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
    result = ERR_INVNAME;
  }

  /* close the result file */
  fclose(fpResult);
  
  return (result);
}


/******************************************************************************\
 *      OMTB_OmxInitTwice Function Definition
\******************************************************************************/
/**
 *
 *  @brief    This Function performs OMX_Init API testing.
 *
 *  @param    Pointer to MX_DBG_CMD_CONTEXT_T structure
 *            Pointer to MX_DBG_CMD_Entry_T structure
 *            Character Double Pointer containing the command
 *
 *  @return   ERR_NOERR           successful,
 *            ERR_END_OF_CMD      help was requested,
 *            ERR_INVNAME         otherwise.
 */

MX_Result
OMTB_OmxInitTwice(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine
)
{
  MX_Result  result = ERR_NOERR;
  OMX_ERRORTYPE err = OMX_ErrorNone;
  char componentRequested[OMTB_MAX_LEN] = {"\0"};
  char resultFileName[OMTB_MAX_LEN] = {"\0"};
  char fOpenMode[OMTB_MAX_LEN] = {"\0"};
  char testCaseId[OMTB_MAX_LEN] = {"\0"};
  char testCaseResult[OMTB_MAX_LEN] = {"\0"}; char returnString[OMTB_MAX_LEN] = {"\0"};
  FILE *fpResult = NULL;
  OMTB_OMX_API_TIMING_VAR_DECL;

  /* Read testcase ID */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, testCaseId);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }
  
  /* Read component type */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, componentRequested);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }

  /* Read result filename */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, resultFileName);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }

  /* Read result file type */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, fOpenMode);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }

  /* Open the result file */
  fpResult = fopen(resultFileName, fOpenMode);

  if(NULL == fpResult)
  {
    PRINT(PRINT_ERR_MSG, "%s: Error in result file open\n", __FUNCTION__);
    fprintf(fpResult, "%s : Error in result file open\n", testCaseId);
    return ERR_INVNAME;
  }

  /* OpenMax init twice */
  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;
  
  err = OMX_Init ();

  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_Init");

  if(OMX_ErrorNone != err)
  {
    OMTB_OmxReturnStatusString(err, returnString);
    strcpy(testCaseResult, "FAIL - Error in OMX_Init()\n");
    fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
    fclose(fpResult);
    return ERR_INVNAME;
  }

  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;
  
  err = OMX_Init ();

  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_Init");
  if(OMX_ErrorNone == err)
  {
    strcpy(testCaseResult, "PASS");
    fprintf(fpResult, "%s : %s\n", testCaseId, testCaseResult);
  }
  else
  {
    OMTB_OmxReturnStatusString(err, returnString);
    strcpy(testCaseResult, "FAIL");
    fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
    fclose(fpResult);
    return ERR_INVNAME;
  }

  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;

  /* OpenMax core uninitialization */
  err = OMX_Deinit ();

  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_Deinit");

  if(OMX_ErrorNone != err)
  {
    OMTB_OmxReturnStatusString(err, returnString);
    strcpy(testCaseResult, "FAIL - Error in OMX_Deinit()\n");
    fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
    result = ERR_INVNAME;
  }

  /* close the result file */
  fclose(fpResult);
  
  return (result);
}


/******************************************************************************\
 *      OMTB_OmxInitInsuffResources Function Definition
\******************************************************************************/
/**
 *
 *  @brief    This Function performs OMX_Init API testing.
 *
 *  @param    Pointer to MX_DBG_CMD_CONTEXT_T structure
 *            Pointer to MX_DBG_CMD_Entry_T structure
 *            Character Double Pointer containing the command
 *
 *  @return   ERR_NOERR           successful,
 *            ERR_END_OF_CMD      help was requested,
 *            ERR_INVNAME         otherwise.
 */

MX_Result
OMTB_OmxInitInsuffResources(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine
)
{
  MX_Result  result = ERR_NOERR;
  OMX_ERRORTYPE err = OMX_ErrorNone;
  char componentRequested[OMTB_MAX_LEN] = {"\0"};
  char resultFileName[OMTB_MAX_LEN] = {"\0"};
  char fOpenMode[OMTB_MAX_LEN] = {"\0"};
  char testCaseId[OMTB_MAX_LEN] = {"\0"};
  char testCaseResult[OMTB_MAX_LEN] = {"\0"}; char returnString[OMTB_MAX_LEN] = {"\0"};
  FILE *fpResult = NULL;
  OMTB_OMX_API_TIMING_VAR_DECL;

  /* Read testcase ID */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, testCaseId);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }
  
  /* Read component type */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, componentRequested);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }

  /* Read result filename */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, resultFileName);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }

  /* Read result file type */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, fOpenMode);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }

  /* Open the result file */
  fpResult = fopen(resultFileName, fOpenMode);

  if(NULL == fpResult)
  {
    PRINT(PRINT_ERR_MSG, "%s: Error in result file open\n", __FUNCTION__);
    fprintf(fpResult, "%s : Error in result file open\n", testCaseId);
    return ERR_INVNAME;
  }

  /* OpenMax insufficient resources */
    
  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;

  err = OMX_Init ();

  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_Init");

  if(OMX_ErrorInsufficientResources == err)
  {
    strcpy(testCaseResult, "PASS");
    fprintf(fpResult, "%s : %s\n", testCaseId, testCaseResult);
  }
  else
  {
    OMTB_OmxReturnStatusString(err, returnString);
    strcpy(testCaseResult, "FAIL");
    fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
    fclose(fpResult);
    return ERR_INVNAME;
  }

  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;

  /* OpenMax core uninitialization */
  err = OMX_Deinit ();

  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_Deinit");

  if(OMX_ErrorNone != err)
  {
    OMTB_OmxReturnStatusString(err, returnString);
    strcpy(testCaseResult, "FAIL - Error in OMX_Deinit()\n");
    fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
    result = ERR_INVNAME;
  }

  /* close the result file */
  fclose(fpResult);
  
  return (result);
}


/******************************************************************************\
 *      OMTB_OmxInitVerMismatch Function Definition
\******************************************************************************/
/**
 *
 *  @brief    This Function performs OMX_Init API testing.
 *
 *  @param    Pointer to MX_DBG_CMD_CONTEXT_T structure
 *            Pointer to MX_DBG_CMD_Entry_T structure
 *            Character Double Pointer containing the command
 *
 *  @return   ERR_NOERR           successful,
 *            ERR_END_OF_CMD      help was requested,
 *            ERR_INVNAME         otherwise.
 */

MX_Result
OMTB_OmxInitVerMismatch(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine
)
{
  MX_Result  result = ERR_NOERR;
  OMX_ERRORTYPE err = OMX_ErrorNone;
  char componentRequested[OMTB_MAX_LEN] = {"\0"};
  char resultFileName[OMTB_MAX_LEN] = {"\0"};
  char fOpenMode[OMTB_MAX_LEN] = {"\0"};
  char testCaseId[OMTB_MAX_LEN] = {"\0"};
  char testCaseResult[OMTB_MAX_LEN] = {"\0"}; char returnString[OMTB_MAX_LEN] = {"\0"};
  FILE *fpResult = NULL;
  OMTB_OMX_API_TIMING_VAR_DECL;

  /* Read testcase ID */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, testCaseId);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }
  
  /* Read component type */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, componentRequested);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }

  /* Read result filename */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, resultFileName);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }

  /* Read result file type */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, fOpenMode);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }

  /* Open the result file */
  fpResult = fopen(resultFileName, fOpenMode);

  if(NULL == fpResult)
  {
    PRINT(PRINT_ERR_MSG, "%s: Error in result file open\n", __FUNCTION__);
    fprintf(fpResult, "%s : Error in result file open\n", testCaseId);
    return ERR_INVNAME;
  }

  /* OpenMax version mismatch */
    
  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;

  err = OMX_Init ();

  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_Init");

  if(OMX_ErrorVersionMismatch == err)
  {
    strcpy(testCaseResult, "PASS");
    fprintf(fpResult, "%s : %s\n", testCaseId, testCaseResult);
  }
  else
  {
    OMTB_OmxReturnStatusString(err, returnString);
    strcpy(testCaseResult, "FAIL");
    fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
    fclose(fpResult);
    return ERR_INVNAME;
  }

  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;

  /* OpenMax core uninitialization */
  err = OMX_Deinit ();

  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_Deinit");

  if(OMX_ErrorNone != err)
  {
    OMTB_OmxReturnStatusString(err, returnString);
    strcpy(testCaseResult, "FAIL - Error in OMX_Deinit()\n");
    fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
    result = ERR_INVNAME;
  }

  /* close the result file */
  fclose(fpResult);
  
  return (result);
}


/******************************************************************************\
 *      OMTB_OmxInitTimeOut Function Definition
\******************************************************************************/
/**
 *
 *  @brief    This Function performs OMX_Init API testing.
 *
 *  @param    Pointer to MX_DBG_CMD_CONTEXT_T structure
 *            Pointer to MX_DBG_CMD_Entry_T structure
 *            Character Double Pointer containing the command
 *
 *  @return   ERR_NOERR           successful,
 *            ERR_END_OF_CMD      help was requested,
 *            ERR_INVNAME         otherwise.
 */

MX_Result
OMTB_OmxInitTimeOut(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine
)
{
  MX_Result  result = ERR_NOERR;
  OMX_ERRORTYPE err = OMX_ErrorNone;
  char componentRequested[OMTB_MAX_LEN] = {"\0"};
  char resultFileName[OMTB_MAX_LEN] = {"\0"};
  char fOpenMode[OMTB_MAX_LEN] = {"\0"};
  char testCaseId[OMTB_MAX_LEN] = {"\0"};
  char testCaseResult[OMTB_MAX_LEN] = {"\0"}; char returnString[OMTB_MAX_LEN] = {"\0"};
  FILE *fpResult = NULL;
  OMTB_OMX_API_TIMING_VAR_DECL;

  /* Read testcase ID */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, testCaseId);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }
  
  /* Read component type */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, componentRequested);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }

  /* Read result filename */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, resultFileName);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }

  /* Read result file type */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, fOpenMode);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }

  /* Open the result file */
  fpResult = fopen(resultFileName, fOpenMode);

  if(NULL == fpResult)
  {
    PRINT(PRINT_ERR_MSG, "%s: Error in result file open\n", __FUNCTION__);
    fprintf(fpResult, "%s : Error in result file open\n", testCaseId);
    return ERR_INVNAME;
  }

  /* OpenMax timeout */
    
  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;

  err = OMX_Init ();

  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_Init");

  if(OMX_ErrorTimeout == err)
  {
    strcpy(testCaseResult, "PASS");
    fprintf(fpResult, "%s : %s\n", testCaseId, testCaseResult);
  }
  else
  {
    OMTB_OmxReturnStatusString(err, returnString);
    strcpy(testCaseResult, "FAIL");
    fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
    fclose(fpResult);
    return ERR_INVNAME;
  }

  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;

  /* OpenMax core uninitialization */
  err = OMX_Deinit ();

  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_Deinit");

  if(OMX_ErrorNone != err)
  {
    OMTB_OmxReturnStatusString(err, returnString);
    strcpy(testCaseResult, "FAIL - Error in OMX_Deinit()\n");
    fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
    result = ERR_INVNAME;
  }

  /* close the result file */
  fclose(fpResult);
  
  return (result);
}


/******************************************************************************\
 *      OMTB_OmxDeInitOnce Function Definition
\******************************************************************************/
/**
 *
 *  @brief    This Function performs OMX_Deinit API testing.
 *
 *  @param    Pointer to MX_DBG_CMD_CONTEXT_T structure
 *            Pointer to MX_DBG_CMD_Entry_T structure
 *            Character Double Pointer containing the command
 *
 *  @return   ERR_NOERR           successful,
 *            ERR_END_OF_CMD      help was requested,
 *            ERR_INVNAME         otherwise.
 */

MX_Result
OMTB_OmxDeInitOnce(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine
)
{
  MX_Result  result = ERR_NOERR;
  OMX_ERRORTYPE err = OMX_ErrorNone;
  char componentRequested[OMTB_MAX_LEN] = {"\0"};
  char resultFileName[OMTB_MAX_LEN] = {"\0"};
  char fOpenMode[OMTB_MAX_LEN] = {"\0"};
  char testCaseId[OMTB_MAX_LEN] = {"\0"};
  char testCaseResult[OMTB_MAX_LEN] = {"\0"}; char returnString[OMTB_MAX_LEN] = {"\0"};
  FILE *fpResult = NULL;
  OMTB_OMX_API_TIMING_VAR_DECL;

  /* Read testcase ID */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, testCaseId);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }
  
  /* Read component type */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, componentRequested);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }

  /* Read result filename */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, resultFileName);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }

  /* Read result file type */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, fOpenMode);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }

  /* Open the result file */
  fpResult = fopen(resultFileName, fOpenMode);

  if(NULL == fpResult)
  {
    PRINT(PRINT_ERR_MSG, "%s: Error in result file open\n", __FUNCTION__);
    fprintf(fpResult, "%s : Error in result file open\n", testCaseId);
    return ERR_INVNAME;
  }

  /* OpenMax core initialization once */
    
  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;

  err = OMX_Init ();

  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_Init");

  if(OMX_ErrorNone != err)
  {
    OMTB_OmxReturnStatusString(err, returnString);
    strcpy(testCaseResult, "FAIL - Error in OMX_Init()\n");
    fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
    fclose(fpResult);
    return ERR_INVNAME;
  }

  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;

  /* OpenMax core uninitialization */
  err = OMX_Deinit ();

  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_Deinit");

  if(OMX_ErrorNone == err)
  {
    strcpy(testCaseResult, "PASS");
    fprintf(fpResult, "%s : %s\n", testCaseId, testCaseResult);
  }
  else
  {
    OMTB_OmxReturnStatusString(err, returnString);
    strcpy(testCaseResult, "FAIL");
    fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
    result = ERR_INVNAME;
  }

  /* close the result file */
  fclose(fpResult);
  
  return (result);
}


/******************************************************************************\
 *      OMTB_OmxDeInitTwice Function Definition
\******************************************************************************/
/**
 *
 *  @brief    This Function performs OMX_Deinit API testing.
 *
 *  @param    Pointer to MX_DBG_CMD_CONTEXT_T structure
 *            Pointer to MX_DBG_CMD_Entry_T structure
 *            Character Double Pointer containing the command
 *
 *  @return   ERR_NOERR           successful,
 *            ERR_END_OF_CMD      help was requested,
 *            ERR_INVNAME         otherwise.
 */

MX_Result
OMTB_OmxDeInitTwice(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine
)
{
  MX_Result  result = ERR_NOERR;
  OMX_ERRORTYPE err = OMX_ErrorNone;
  char componentRequested[OMTB_MAX_LEN] = {"\0"};
  char resultFileName[OMTB_MAX_LEN] = {"\0"};
  char fOpenMode[OMTB_MAX_LEN] = {"\0"};
  char testCaseId[OMTB_MAX_LEN] = {"\0"};
  char testCaseResult[OMTB_MAX_LEN] = {"\0"}; char returnString[OMTB_MAX_LEN] = {"\0"};
  FILE *fpResult = NULL;
  OMTB_OMX_API_TIMING_VAR_DECL;

  /* Read testcase ID */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, testCaseId);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }
  
  /* Read component type */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, componentRequested);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }

  /* Read result filename */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, resultFileName);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }

  /* Read result file type */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, fOpenMode);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }

  /* Open the result file */
  fpResult = fopen(resultFileName, fOpenMode);

  if(NULL == fpResult)
  {
    PRINT(PRINT_ERR_MSG, "%s: Error in result file open\n", __FUNCTION__);
    fprintf(fpResult, "%s : Error in result file open\n", testCaseId);
    return ERR_INVNAME;
  }

  /* OpenMax init twice */
  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;
  
  err = OMX_Init ();

  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_Init");

  if(OMX_ErrorNone != err)
  {
    OMTB_OmxReturnStatusString(err, returnString);
    strcpy(testCaseResult, "FAIL - Error in OMX_Init()\n");
    fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
    fclose(fpResult);
    return ERR_INVNAME;
  }

  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;
  
  err = OMX_Deinit ();

  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_Deinit");

  if(OMX_ErrorNone != err)
 {
    OMTB_OmxReturnStatusString(err, returnString);
    strcpy(testCaseResult, "FAIL - Error in OMX_DeInit()\n");
    fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
    fclose(fpResult);
    return ERR_INVNAME;
  }
  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;

  /* OpenMax core uninitialization */
  err = OMX_Deinit ();

  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_Deinit");

  if(OMX_ErrorNone == err)
  {
    strcpy(testCaseResult, "PASS");
    fprintf(fpResult, "%s : %s\n", testCaseId, testCaseResult);
  }
  else
  {
    OMTB_OmxReturnStatusString(err, returnString);
    strcpy(testCaseResult, "FAIL");
    fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
    result = ERR_INVNAME;
  }

  /* close the result file */
  fclose(fpResult);
  
  return (result);
}


/******************************************************************************\
 *      OMTB_OmxDeInitVerMismatch Function Definition
\******************************************************************************/
/**
 *
 *  @brief    This Function performs OMX_Deinit API testing.
 *
 *  @param    Pointer to MX_DBG_CMD_CONTEXT_T structure
 *            Pointer to MX_DBG_CMD_Entry_T structure
 *            Character Double Pointer containing the command
 *
 *  @return   ERR_NOERR           successful,
 *            ERR_END_OF_CMD      help was requested,
 *            ERR_INVNAME         otherwise.
 */

MX_Result
OMTB_OmxDeInitVerMismatch(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine
)
{
  MX_Result  result = ERR_NOERR;
  OMX_ERRORTYPE err = OMX_ErrorNone;
  char componentRequested[OMTB_MAX_LEN] = {"\0"};
  char resultFileName[OMTB_MAX_LEN] = {"\0"};
  char fOpenMode[OMTB_MAX_LEN] = {"\0"};
  char testCaseId[OMTB_MAX_LEN] = {"\0"};
  char testCaseResult[OMTB_MAX_LEN] = {"\0"}; char returnString[OMTB_MAX_LEN] = {"\0"};
  FILE *fpResult = NULL;
  OMTB_OMX_API_TIMING_VAR_DECL;

  /* Read testcase ID */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, testCaseId);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }
  
  /* Read component type */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, componentRequested);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }

  /* Read result filename */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, resultFileName);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }

  /* Read result file type */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, fOpenMode);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }

  /* Open the result file */
  fpResult = fopen(resultFileName, fOpenMode);

  if(NULL == fpResult)
  {
    PRINT(PRINT_ERR_MSG, "%s: Error in result file open\n", __FUNCTION__);
    fprintf(fpResult, "%s : Error in result file open\n", testCaseId);
    return ERR_INVNAME;
  }

  /* OpenMax version mismatch */
    
  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;

  err = OMX_Init ();

  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_Init");

  if(OMX_ErrorNone != err)
  {
    OMTB_OmxReturnStatusString(err, returnString);
    strcpy(testCaseResult, "FAIL - Error in OMX_Init()\n");
    fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
    fclose(fpResult);
    return ERR_INVNAME;
  }

  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;

  /* OpenMax core uninitialization */
  err = OMX_Deinit ();

  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_Deinit");

  if(OMX_ErrorVersionMismatch == err)
  {
    strcpy(testCaseResult, "PASS");
    fprintf(fpResult, "%s : %s\n", testCaseId, testCaseResult);
  }
  else
  {
    OMTB_OmxReturnStatusString(err, returnString);
    strcpy(testCaseResult, "FAIL");
    fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
    result = ERR_INVNAME;
  }

  /* close the result file */
  fclose(fpResult);
  
  return (result);
}


/******************************************************************************\
 *      OMTB_OmxDeInitTimeOut Function Definition
\******************************************************************************/
/**
 *
 *  @brief    This Function performs OMX_Deinit API testing.
 *
 *  @param    Pointer to MX_DBG_CMD_CONTEXT_T structure
 *            Pointer to MX_DBG_CMD_Entry_T structure
 *            Character Double Pointer containing the command
 *
 *  @return   ERR_NOERR           successful,
 *            ERR_END_OF_CMD      help was requested,
 *            ERR_INVNAME         otherwise.
 */

MX_Result
OMTB_OmxDeInitTimeOut(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine
)
{
  MX_Result  result = ERR_NOERR;
  OMX_ERRORTYPE err = OMX_ErrorNone;
  char componentRequested[OMTB_MAX_LEN] = {"\0"};
  char resultFileName[OMTB_MAX_LEN] = {"\0"};
  char fOpenMode[OMTB_MAX_LEN] = {"\0"};
  char testCaseId[OMTB_MAX_LEN] = {"\0"};
  char testCaseResult[OMTB_MAX_LEN] = {"\0"}; char returnString[OMTB_MAX_LEN] = {"\0"};
  FILE *fpResult = NULL;
  OMTB_OMX_API_TIMING_VAR_DECL;

  /* Read testcase ID */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, testCaseId);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }
  
  /* Read component type */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, componentRequested);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }

  /* Read result filename */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, resultFileName);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }

  /* Read result file type */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, fOpenMode);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }

  /* Open the result file */
  fpResult = fopen(resultFileName, fOpenMode);

  if(NULL == fpResult)
  {
    PRINT(PRINT_ERR_MSG, "%s: Error in result file open\n", __FUNCTION__);
    fprintf(fpResult, "%s : Error in result file open\n", testCaseId);
    return ERR_INVNAME;
  }

  /* OpenMax timeout */
    
  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;

  err = OMX_Init ();

  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_Init");

  if(OMX_ErrorNone != err)
  {
    OMTB_OmxReturnStatusString(err, returnString);
    strcpy(testCaseResult, "FAIL - Error in OMX_Init()\n");
    fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
    fclose(fpResult);
    return ERR_INVNAME;
  }

  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;

  /* OpenMax core uninitialization */
  err = OMX_Deinit ();

  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_Deinit");

  if(OMX_ErrorTimeout == err)
  {
    strcpy(testCaseResult, "PASS");
    fprintf(fpResult, "%s : %s\n", testCaseId, testCaseResult);
  }
  else
  {
    OMTB_OmxReturnStatusString(err, returnString);
    strcpy(testCaseResult, "FAIL");
    fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
    result = ERR_INVNAME;
  }

  /* close the result file */
  fclose(fpResult);
  
  return (result);
}


/******************************************************************************\
 *      OMTB_OmxDeInitWithoutFreeHandle Function Definition
\******************************************************************************/
/**
 *
 *  @brief    This Function performs OMX_Deinit API testing.
 *
 *  @param    Pointer to MX_DBG_CMD_CONTEXT_T structure
 *            Pointer to MX_DBG_CMD_Entry_T structure
 *            Character Double Pointer containing the command
 *
 *  @return   ERR_NOERR           successful,
 *            ERR_END_OF_CMD      help was requested,
 *            ERR_INVNAME         otherwise.
 */

MX_Result
OMTB_OmxDeInitWithoutFreeHandle(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine
)
{
  MX_Result  result = ERR_NOERR;
  OMX_ERRORTYPE err = OMX_ErrorNone;
  char componentRequested[OMTB_MAX_LEN] = {"\0"};
  char resultFileName[OMTB_MAX_LEN] = {"\0"};
  char fOpenMode[OMTB_MAX_LEN] = {"\0"};
  char testCaseId[OMTB_MAX_LEN] = {"\0"};
  char testCaseResult[OMTB_MAX_LEN] = {"\0"}; char returnString[OMTB_MAX_LEN] = {"\0"};
  FILE *fpResult = NULL;
  OMX_HANDLETYPE handle = NULL;                  /* Component handle */
  OMTB_OMX_API_TIMING_VAR_DECL;

  /* Read testcase ID */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, testCaseId);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }
  
  /* Read component name */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, componentRequested);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }

  /* Read result filename */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, resultFileName);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }

  /* Read result file type */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, fOpenMode);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }

  /* Open the result file */
  fpResult = fopen(resultFileName, fOpenMode);

  if(NULL == fpResult)
  {
    PRINT(PRINT_ERR_MSG, "%s: Error in result file open\n", __FUNCTION__);
    fprintf(fpResult, "%s : Error in result file open\n", testCaseId);
    return ERR_INVNAME;
  }

  /* OpenMax insufficient resources */
    
  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;

  err = OMX_Init ();

  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_Init");

  if(OMX_ErrorNone != err)
  {
    OMTB_OmxReturnStatusString(err, returnString);
    strcpy(testCaseResult, "FAIL - Error in OMX_Init()\n");
    fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
    fclose(fpResult);
    return ERR_INVNAME;
  }

  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;
  
  /* get component handle */
  err = OMX_GetHandle(&handle,
                      (OMX_STRING)componentRequested,
                      NULL,
                      &OMTB_APITestCallback);
  
  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_GetHandle");
  
  if(OMX_ErrorNone != err)
  {
    PRINT(PRINT_ERR_MSG, "No component named \"%s\" found\n",
                          componentRequested);
    OMTB_OmxReturnStatusString(err, returnString);
    strcpy(testCaseResult, "FAIL - Error in OMX_GetHandle()\n");
    fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
    result = ERR_INVNAME;
  }
  
  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;

  /* OpenMax core uninitialization */
  err = OMX_Deinit ();

  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_Deinit");

  if(OMX_ErrorNone == err)
  {
    strcpy(testCaseResult, "PASS");
    fprintf(fpResult, "%s : %s\n", testCaseId, testCaseResult);
  }
  else
  {
    OMTB_OmxReturnStatusString(err, returnString);
    strcpy(testCaseResult, "FAIL");
    fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
    result = ERR_INVNAME;
  }

  /* free component handle */
  if(NULL != handle)
  {
    /* API entry time calculation macro */
    OMTB_OMX_API_ENTRY_TIME_CALC;
    
    err = OMX_FreeHandle(handle);
    
    /* API exit time calculation macro */
    OMTB_OMX_API_EXIT_TIME_CALC("OMX_FreeHandle");
    
    if(OMX_ErrorNone != err)
    {
      OMTB_OmxReturnStatusString(err, returnString);
      strcpy(testCaseResult, "FAIL - Error in OMX_FreeHandle()\n");
      fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
      fclose(fpResult);
      return ERR_INVNAME;
    }

    /* API entry time calculation macro */
    OMTB_OMX_API_ENTRY_TIME_CALC;

    /* OpenMax core uninitialization */
    err = OMX_Deinit ();

    /* API exit time calculation macro */
    OMTB_OMX_API_EXIT_TIME_CALC("OMX_Deinit");
    
    if(OMX_ErrorNone != err)
    {
      OMTB_OmxReturnStatusString(err, returnString);
      strcpy(testCaseResult, "FAIL - Error in OMX_DeInit()\n");
      fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
      result = ERR_INVNAME;
    }
  }

  /* close the result file */
  fclose(fpResult);
  
  return (result);
}


/******************************************************************************\
 *      OMTB_OmxGetHandleOnce Function Definition
\******************************************************************************/
/**
 *
 *  @brief    This Function performs OMX_GetHandle API testing.
 *
 *  @param    Pointer to MX_DBG_CMD_CONTEXT_T structure
 *            Pointer to MX_DBG_CMD_Entry_T structure
 *            Character Double Pointer containing the command
 *
 *  @return   ERR_NOERR           successful,
 *            ERR_END_OF_CMD      help was requested,
 *            ERR_INVNAME         otherwise.
 */

MX_Result
OMTB_OmxGetHandleOnce(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine
)
{
  MX_Result  result = ERR_NOERR;
  OMX_ERRORTYPE err = OMX_ErrorNone;
  char componentRequested[OMTB_MAX_LEN] = {"\0"};
  char resultFileName[OMTB_MAX_LEN] = {"\0"};
  char fOpenMode[OMTB_MAX_LEN] = {"\0"};
  char testCaseId[OMTB_MAX_LEN] = {"\0"};
  char testCaseResult[OMTB_MAX_LEN] = {"\0"}; char returnString[OMTB_MAX_LEN] = {"\0"};
  FILE *fpResult = NULL;
  OMX_HANDLETYPE handle = NULL;                  /* Component handle */
  OMTB_OMX_API_TIMING_VAR_DECL;

  /* Read testcase ID */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, testCaseId);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }
  
  /* Read component name */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, componentRequested);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }

  /* Read result filename */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, resultFileName);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }

  /* Read result file type */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, fOpenMode);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }

  /* Open the result file */
  fpResult = fopen(resultFileName, fOpenMode);

  if(NULL == fpResult)
  {
    PRINT(PRINT_ERR_MSG, "%s: Error in result file open\n", __FUNCTION__);
    fprintf(fpResult, "%s : Error in result file open\n", testCaseId);
    return ERR_INVNAME;
  }

  /* OpenMax insufficient resources */
    
  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;

  err = OMX_Init ();

  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_Init");

  if(OMX_ErrorNone != err)
  {
    OMTB_OmxReturnStatusString(err, returnString);
    strcpy(testCaseResult, "FAIL - Error in OMX_Init()\n");
    fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
    fclose(fpResult);
    return ERR_INVNAME;
  }

  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;
  
  /* get component handle */
  err = OMX_GetHandle(&handle,
                      (OMX_STRING)componentRequested,
                      NULL,
                      &OMTB_APITestCallback);
  
  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_GetHandle");

  if(OMX_ErrorNone == err)
  {
    strcpy(testCaseResult, "PASS");
    fprintf(fpResult, "%s : %s\n", testCaseId, testCaseResult);
  }
  else
  {
    OMTB_OmxReturnStatusString(err, returnString);
    strcpy(testCaseResult, "FAIL");
    fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
    
    /* API entry time calculation macro */
    OMTB_OMX_API_ENTRY_TIME_CALC;

    /* OpenMax core uninitialization */
    err = OMX_Deinit ();

    /* API exit time calculation macro */
    OMTB_OMX_API_EXIT_TIME_CALC("OMX_Deinit");
    
    if(OMX_ErrorNone != err)
    {
      OMTB_OmxReturnStatusString(err, returnString);
      strcpy(testCaseResult, "FAIL - Error in OMX_Deinit()\n");
      fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
      result = ERR_INVNAME;
    }

    fclose(fpResult);
    return ERR_INVNAME;
  }
  
  /* free component handle */
  if(NULL != handle)
  {
    /* API entry time calculation macro */
    OMTB_OMX_API_ENTRY_TIME_CALC;
    
    err = OMX_FreeHandle(handle);
    
    /* API exit time calculation macro */
    OMTB_OMX_API_EXIT_TIME_CALC("OMX_FreeHandle");
    
    if(OMX_ErrorNone != err)
    {
      OMTB_OmxReturnStatusString(err, returnString);
      strcpy(testCaseResult, "FAIL - Error in OMX_FreeHandle()\n");
      fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
      
      result = ERR_INVNAME;
    }
    
  }

  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;
  
  /* OpenMax core uninitialization */
  err = OMX_Deinit ();

  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_Deinit");

  if(OMX_ErrorNone != err)
  {
      OMTB_OmxReturnStatusString(err, returnString);
      strcpy(testCaseResult, "FAIL - Error in OMX_Deinit()\n");
      fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
      result = ERR_INVNAME;
  }

  /* close the result file */
  fclose(fpResult);
  
  return (result);
}


/******************************************************************************\
 *      OMTB_OmxGetHandleTwice Function Definition
\******************************************************************************/
/**
 *
 *  @brief    This Function performs OMX_GetHandle API testing.
 *
 *  @param    Pointer to MX_DBG_CMD_CONTEXT_T structure
 *            Pointer to MX_DBG_CMD_Entry_T structure
 *            Character Double Pointer containing the command
 *
 *  @return   ERR_NOERR           successful,
 *            ERR_END_OF_CMD      help was requested,
 *            ERR_INVNAME         otherwise.
 */

MX_Result
OMTB_OmxGetHandleTwice(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine
)
{
  MX_Result  result = ERR_NOERR;
  OMX_ERRORTYPE err = OMX_ErrorNone;
  char componentRequested[OMTB_MAX_LEN] = {"\0"};
  char resultFileName[OMTB_MAX_LEN] = {"\0"};
  char fOpenMode[OMTB_MAX_LEN] = {"\0"};
  char testCaseId[OMTB_MAX_LEN] = {"\0"};
  char testCaseResult[OMTB_MAX_LEN] = {"\0"}; char returnString[OMTB_MAX_LEN] = {"\0"};
  FILE *fpResult = NULL;
  OMX_HANDLETYPE handle1 = NULL, handle2 = NULL;         /* Component handle */
  OMTB_OMX_API_TIMING_VAR_DECL;

  /* Read testcase ID */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, testCaseId);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }
  
  /* Read component name */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, componentRequested);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }

  /* Read result filename */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, resultFileName);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }

  /* Read result file type */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, fOpenMode);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }

  /* Open the result file */
  fpResult = fopen(resultFileName, fOpenMode);

  if(NULL == fpResult)
  {
    PRINT(PRINT_ERR_MSG, "%s: Error in result file open\n", __FUNCTION__);
    fprintf(fpResult, "%s : Error in result file open\n", testCaseId);
    return ERR_INVNAME;
  }

  /* OpenMax insufficient resources */
    
  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;

  err = OMX_Init ();

  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_Init");

  if(OMX_ErrorNone != err)
  {
    OMTB_OmxReturnStatusString(err, returnString);
    strcpy(testCaseResult, "FAIL - Error in OMX_Init()\n");
    fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
    fclose(fpResult);
    return ERR_INVNAME;
  }

  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;
  
  /* get component handle */
  err = OMX_GetHandle(&handle1,
                      (OMX_STRING)componentRequested,
                      NULL,
                      &OMTB_APITestCallback);
  
  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_GetHandle");

  if(OMX_ErrorNone != err)
  {
    PRINT(PRINT_ERR_MSG, "No component named \"%s\" found\n",
                          componentRequested);
    OMTB_OmxReturnStatusString(err, returnString);
    strcpy(testCaseResult, "FAIL - Error in OMX_GetHandle()\n");
    fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
    
    /* API entry time calculation macro */
    OMTB_OMX_API_ENTRY_TIME_CALC;

    /* OpenMax core uninitialization */
    err = OMX_Deinit ();

    /* API exit time calculation macro */
    OMTB_OMX_API_EXIT_TIME_CALC("OMX_Deinit");
    
    if(OMX_ErrorNone != err)
    {
      OMTB_OmxReturnStatusString(err, returnString);
      strcpy(testCaseResult, "FAIL - Error in OMX_Deinit()\n");
      fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
      result = ERR_INVNAME;
    }

    fclose(fpResult);
    return ERR_INVNAME;
  }
  
  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;
  
  /* get component handle */
  err = OMX_GetHandle(&handle2,
                      (OMX_STRING)componentRequested,
                      NULL,
                      &OMTB_APITestCallback);
  
  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_GetHandle");
  
  if(OMX_ErrorNone == err)
  {
    strcpy(testCaseResult, "PASS");
    fprintf(fpResult, "%s : %s\n", testCaseId, testCaseResult);
  }
  else
  {
    OMTB_OmxReturnStatusString(err, returnString);
    strcpy(testCaseResult, "FAIL");
    fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);

    /* API entry time calculation macro */
    OMTB_OMX_API_ENTRY_TIME_CALC;
    
    err = OMX_FreeHandle(handle1);
    
    /* API exit time calculation macro */
    OMTB_OMX_API_EXIT_TIME_CALC("OMX_FreeHandle");
    
    if(OMX_ErrorNone != err)
    {
      OMTB_OmxReturnStatusString(err, returnString);
      strcpy(testCaseResult, "FAIL - Error in OMX_FreeHandle()\n");
      fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
      
      result = ERR_INVNAME;
    }
    
    /* API entry time calculation macro */
    OMTB_OMX_API_ENTRY_TIME_CALC;

    /* OpenMax core uninitialization */
    err = OMX_Deinit ();

    /* API exit time calculation macro */
    OMTB_OMX_API_EXIT_TIME_CALC("OMX_Deinit");
    
    if(OMX_ErrorNone != err)
    {
      OMTB_OmxReturnStatusString(err, returnString);
      strcpy(testCaseResult, "FAIL - Error in OMX_Deinit()\n");
      fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
      result = ERR_INVNAME;
    }

    fclose(fpResult);
    return ERR_INVNAME;
  }
  
  /* free component handle */
  if(NULL != handle1)
  {
    /* API entry time calculation macro */
    OMTB_OMX_API_ENTRY_TIME_CALC;
    
    err = OMX_FreeHandle(handle1);
    
    /* API exit time calculation macro */
    OMTB_OMX_API_EXIT_TIME_CALC("OMX_FreeHandle");
    
    if(OMX_ErrorNone != err)
    {
      OMTB_OmxReturnStatusString(err, returnString);
      strcpy(testCaseResult, "FAIL - Error in OMX_FreeHandle()\n");
      fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
      
      result = ERR_INVNAME;
    }

    /* API entry time calculation macro */
    OMTB_OMX_API_ENTRY_TIME_CALC;
    
    err = OMX_FreeHandle(handle2);
    
    /* API exit time calculation macro */
    OMTB_OMX_API_EXIT_TIME_CALC("OMX_FreeHandle");
    
    if(OMX_ErrorNone != err)
    {
      OMTB_OmxReturnStatusString(err, returnString);
      strcpy(testCaseResult, "FAIL - Error in OMX_FreeHandle()\n");
      fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
      
      result = ERR_INVNAME;
    }
    
  }

  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;
  
  /* OpenMax core uninitialization */
  err = OMX_Deinit ();

  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_Deinit");

    if(OMX_ErrorNone != err)
    {
      OMTB_OmxReturnStatusString(err, returnString);
      strcpy(testCaseResult, "FAIL - Error in OMX_Deinit()\n");
      fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
      result = ERR_INVNAME;
    }

  /* close the result file */
  fclose(fpResult);
  
  return (result);
}


/******************************************************************************\
 *      OMTB_OmxGetHandleInvCompName Function Definition
\******************************************************************************/
/**
 *
 *  @brief    This Function performs OMX_GetHandle API testing.
 *
 *  @param    Pointer to MX_DBG_CMD_CONTEXT_T structure
 *            Pointer to MX_DBG_CMD_Entry_T structure
 *            Character Double Pointer containing the command
 *
 *  @return   ERR_NOERR           successful,
 *            ERR_END_OF_CMD      help was requested,
 *            ERR_INVNAME         otherwise.
 */

MX_Result
OMTB_OmxGetHandleInvCompName(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine
)
{
  MX_Result  result = ERR_NOERR;
  OMX_ERRORTYPE err = OMX_ErrorNone;
  char componentRequested[OMTB_MAX_LEN] = {"\0"};
  char resultFileName[OMTB_MAX_LEN] = {"\0"};
  char fOpenMode[OMTB_MAX_LEN] = {"\0"};
  char testCaseId[OMTB_MAX_LEN] = {"\0"};
  char testCaseResult[OMTB_MAX_LEN] = {"\0"}; char returnString[OMTB_MAX_LEN] = {"\0"};
  FILE *fpResult = NULL;
  OMX_HANDLETYPE handle = NULL;                  /* Component handle */
  OMTB_OMX_API_TIMING_VAR_DECL;

  /* Read testcase ID */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, testCaseId);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }
  
  /* Read component name */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, componentRequested);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }

  /* set invalid component name */
  TIMM_OSAL_Memset(componentRequested, 0x65, OMX_MAX_STRINGNAME_SIZE);
  componentRequested[OMX_MAX_STRINGNAME_SIZE + 1] = '\0';
  
  
  /* Read result filename */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, resultFileName);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }

  /* Read result file type */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, fOpenMode);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }

  /* Open the result file */
  fpResult = fopen(resultFileName, fOpenMode);

  if(NULL == fpResult)
  {
    PRINT(PRINT_ERR_MSG, "%s: Error in result file open\n", __FUNCTION__);
    fprintf(fpResult, "%s : Error in result file open\n", testCaseId);
    return ERR_INVNAME;
  }

  /* OpenMax insufficient resources */
    
  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;

  err = OMX_Init ();

  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_Init");

  if(OMX_ErrorNone != err)
  {
    OMTB_OmxReturnStatusString(err, returnString);
    strcpy(testCaseResult, "FAIL - Error in OMX_Init()\n");
    fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
    fclose(fpResult);
    return ERR_INVNAME;
  }

  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;
  
  /* get component handle */
  err = OMX_GetHandle(&handle,
                      (OMX_STRING)componentRequested,
                      NULL,
                      &OMTB_APITestCallback);
  
  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_GetHandle");

  if(OMX_ErrorInvalidComponentName == err)
  {
    strcpy(testCaseResult, "PASS");
    fprintf(fpResult, "%s : %s\n", testCaseId, testCaseResult);
  }
  else
  {
    OMTB_OmxReturnStatusString(err, returnString);
    strcpy(testCaseResult, "FAIL");
    fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
    
    /* API entry time calculation macro */
    OMTB_OMX_API_ENTRY_TIME_CALC;

    /* OpenMax core uninitialization */
    err = OMX_Deinit ();

    /* API exit time calculation macro */
    OMTB_OMX_API_EXIT_TIME_CALC("OMX_Deinit");
    
    if(OMX_ErrorNone != err)
    {
      OMTB_OmxReturnStatusString(err, returnString);
      strcpy(testCaseResult, "FAIL - Error in OMX_Deinit()\n");
      fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
      result = ERR_INVNAME;
    }

    fclose(fpResult);
    return ERR_INVNAME;
  }
  
  /* free component handle */
  if(NULL != handle)
  {
    /* API entry time calculation macro */
    OMTB_OMX_API_ENTRY_TIME_CALC;
    
    err = OMX_FreeHandle(handle);
    
    /* API exit time calculation macro */
    OMTB_OMX_API_EXIT_TIME_CALC("OMX_FreeHandle");
    
    if(OMX_ErrorNone != err)
    {
      OMTB_OmxReturnStatusString(err, returnString);
      strcpy(testCaseResult, "FAIL - Error in OMX_FreeHandle()\n");
      fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
      
      result = ERR_INVNAME;
    }
    
  }

  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;
  
  /* OpenMax core uninitialization */
  err = OMX_Deinit ();

  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_Deinit");

    if(OMX_ErrorNone != err)
    {
      OMTB_OmxReturnStatusString(err, returnString);
      strcpy(testCaseResult, "FAIL - Error in OMX_Deinit()\n");
      fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
      result = ERR_INVNAME;
    }

  /* close the result file */
  fclose(fpResult);
  
  return (result);
}


/******************************************************************************\
 *      OMTB_OmxGetHandleCompNotFound Function Definition
\******************************************************************************/
/**
 *
 *  @brief    This Function performs OMX_GetHandle API testing.
 *
 *  @param    Pointer to MX_DBG_CMD_CONTEXT_T structure
 *            Pointer to MX_DBG_CMD_Entry_T structure
 *            Character Double Pointer containing the command
 *
 *  @return   ERR_NOERR           successful,
 *            ERR_END_OF_CMD      help was requested,
 *            ERR_INVNAME         otherwise.
 */

MX_Result
OMTB_OmxGetHandleCompNotFound(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine
)
{
  MX_Result  result = ERR_NOERR;
  OMX_ERRORTYPE err = OMX_ErrorNone;
  char componentRequested[OMTB_MAX_LEN] = {"\0"};
  char resultFileName[OMTB_MAX_LEN] = {"\0"};
  char fOpenMode[OMTB_MAX_LEN] = {"\0"};
  char testCaseId[OMTB_MAX_LEN] = {"\0"};
  char testCaseResult[OMTB_MAX_LEN] = {"\0"}; char returnString[OMTB_MAX_LEN] = {"\0"};
  FILE *fpResult = NULL;
  OMX_HANDLETYPE handle = NULL;                  /* Component handle */
  OMTB_OMX_API_TIMING_VAR_DECL;

  /* Read testcase ID */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, testCaseId);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }
  
  /* Read component name */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, componentRequested);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }

  /* Read result filename */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, resultFileName);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }

  /* Read result file type */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, fOpenMode);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }

  /* Open the result file */
  fpResult = fopen(resultFileName, fOpenMode);

  if(NULL == fpResult)
  {
    PRINT(PRINT_ERR_MSG, "%s: Error in result file open\n", __FUNCTION__);
    fprintf(fpResult, "%s : Error in result file open\n", testCaseId);
    return ERR_INVNAME;
  }

  /* OpenMax insufficient resources */
    
  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;

  err = OMX_Init ();

  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_Init");

  if(OMX_ErrorNone != err)
  {
    OMTB_OmxReturnStatusString(err, returnString);
    strcpy(testCaseResult, "FAIL - Error in OMX_Init()\n");
    fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
    fclose(fpResult);
    return ERR_INVNAME;
  }

  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;
  
  /* get component handle */
  err = OMX_GetHandle(&handle,
                      (OMX_STRING)componentRequested,
                      NULL,
                      &OMTB_APITestCallback);
  
  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_GetHandle");

  if(OMX_ErrorComponentNotFound == err)
  {
    strcpy(testCaseResult, "PASS");
    fprintf(fpResult, "%s : %s\n", testCaseId, testCaseResult);
  }
  else
  {
    OMTB_OmxReturnStatusString(err, returnString);
    strcpy(testCaseResult, "FAIL");
    fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
    
    /* API entry time calculation macro */
    OMTB_OMX_API_ENTRY_TIME_CALC;

    /* OpenMax core uninitialization */
    err = OMX_Deinit ();

    /* API exit time calculation macro */
    OMTB_OMX_API_EXIT_TIME_CALC("OMX_Deinit");
    
    if(OMX_ErrorNone != err)
    {
      OMTB_OmxReturnStatusString(err, returnString);
      strcpy(testCaseResult, "FAIL - Error in OMX_Deinit()\n");
      fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
      result = ERR_INVNAME;
    }

    fclose(fpResult);
    return ERR_INVNAME;
  }
  
  /* free component handle */
  if(NULL != handle)
  {
    /* API entry time calculation macro */
    OMTB_OMX_API_ENTRY_TIME_CALC;
    
    err = OMX_FreeHandle(handle);
    
    /* API exit time calculation macro */
    OMTB_OMX_API_EXIT_TIME_CALC("OMX_FreeHandle");
    
    if(OMX_ErrorNone != err)
    {
      OMTB_OmxReturnStatusString(err, returnString);
      strcpy(testCaseResult, "FAIL - Error in OMX_FreeHandle()\n");
      fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
      
      result = ERR_INVNAME;
    }
    
  }

  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;
  
  /* OpenMax core uninitialization */
  err = OMX_Deinit ();

  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_Deinit");

    if(OMX_ErrorNone != err)
    {
      OMTB_OmxReturnStatusString(err, returnString);
      strcpy(testCaseResult, "FAIL - Error in OMX_Deinit()\n");
      fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
      result = ERR_INVNAME;
    }

  /* close the result file */
  fclose(fpResult);
  
  return (result);
}


/******************************************************************************\
 *      OMTB_OmxGetHandleNoCompInitFxn Function Definition
\******************************************************************************/
/**
 *
 *  @brief    This Function performs OMX_GetHandle API testing.
 *
 *  @param    Pointer to MX_DBG_CMD_CONTEXT_T structure
 *            Pointer to MX_DBG_CMD_Entry_T structure
 *            Character Double Pointer containing the command
 *
 *  @return   ERR_NOERR           successful,
 *            ERR_END_OF_CMD      help was requested,
 *            ERR_INVNAME         otherwise.
 */

MX_Result
OMTB_OmxGetHandleNoCompInitFxn(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine
)
{
  MX_Result  result = ERR_NOERR;
  OMX_ERRORTYPE err = OMX_ErrorNone;
  char componentRequested[OMTB_MAX_LEN] = {"\0"};
  char resultFileName[OMTB_MAX_LEN] = {"\0"};
  char fOpenMode[OMTB_MAX_LEN] = {"\0"};
  char testCaseId[OMTB_MAX_LEN] = {"\0"};
  char testCaseResult[OMTB_MAX_LEN] = {"\0"}; char returnString[OMTB_MAX_LEN] = {"\0"};
  FILE *fpResult = NULL;
  OMX_HANDLETYPE handle = NULL;                  /* Component handle */
  OMTB_OMX_API_TIMING_VAR_DECL;

  /* Read testcase ID */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, testCaseId);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }
  
  /* Read component name */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, componentRequested);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }

  /* Read result filename */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, resultFileName);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }

  /* Read result file type */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, fOpenMode);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }

  /* Open the result file */
  fpResult = fopen(resultFileName, fOpenMode);

  if(NULL == fpResult)
  {
    PRINT(PRINT_ERR_MSG, "%s: Error in result file open\n", __FUNCTION__);
    fprintf(fpResult, "%s : Error in result file open\n", testCaseId);
    return ERR_INVNAME;
  }

  /* OpenMax insufficient resources */
    
  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;

  err = OMX_Init ();

  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_Init");

  if(OMX_ErrorNone != err)
  {
    OMTB_OmxReturnStatusString(err, returnString);
    strcpy(testCaseResult, "FAIL - Error in OMX_Init()\n");
    fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
    fclose(fpResult);
    return ERR_INVNAME;
  }

  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;
  
  /* get component handle */
  err = OMX_GetHandle(&handle,
                      (OMX_STRING)componentRequested,
                      NULL,
                      &OMTB_APITestCallback);
  
  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_GetHandle");

  if(OMX_ErrorInvalidComponent == err)
  {
    strcpy(testCaseResult, "PASS");
    fprintf(fpResult, "%s : %s\n", testCaseId, testCaseResult);
  }
  else
  {
    OMTB_OmxReturnStatusString(err, returnString);
    strcpy(testCaseResult, "FAIL");
    fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
    
    /* API entry time calculation macro */
    OMTB_OMX_API_ENTRY_TIME_CALC;

    /* OpenMax core uninitialization */
    err = OMX_Deinit ();

    /* API exit time calculation macro */
    OMTB_OMX_API_EXIT_TIME_CALC("OMX_Deinit");
    
    if(OMX_ErrorNone != err)
    {
      OMTB_OmxReturnStatusString(err, returnString);
      strcpy(testCaseResult, "FAIL - Error in OMX_Deinit()\n");
      fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
      result = ERR_INVNAME;
    }

    fclose(fpResult);
    return ERR_INVNAME;
  }
  
  /* free component handle */
  if(NULL != handle)
  {
    /* API entry time calculation macro */
    OMTB_OMX_API_ENTRY_TIME_CALC;
    
    err = OMX_FreeHandle(handle);
    
    /* API exit time calculation macro */
    OMTB_OMX_API_EXIT_TIME_CALC("OMX_FreeHandle");
    
    if(OMX_ErrorNone != err)
    {
      OMTB_OmxReturnStatusString(err, returnString);
      strcpy(testCaseResult, "FAIL - Error in OMX_FreeHandle()\n");
      fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
      
      result = ERR_INVNAME;
    }
    
  }

  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;
  
  /* OpenMax core uninitialization */
  err = OMX_Deinit ();

  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_Deinit");

    if(OMX_ErrorNone != err)
    {
      OMTB_OmxReturnStatusString(err, returnString);
      strcpy(testCaseResult, "FAIL - Error in OMX_Deinit()\n");
      fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
      result = ERR_INVNAME;
    }

  /* close the result file */
  fclose(fpResult);
  
  return (result);
}


/******************************************************************************\
 *      OMTB_OmxGetHandleNullCb Function Definition
\******************************************************************************/
/**
 *
 *  @brief    This Function performs OMX_GetHandle API testing.
 *
 *  @param    Pointer to MX_DBG_CMD_CONTEXT_T structure
 *            Pointer to MX_DBG_CMD_Entry_T structure
 *            Character Double Pointer containing the command
 *
 *  @return   ERR_NOERR           successful,
 *            ERR_END_OF_CMD      help was requested,
 *            ERR_INVNAME         otherwise.
 */

MX_Result
OMTB_OmxGetHandleNullCb(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine
)
{
  MX_Result  result = ERR_NOERR;
  OMX_ERRORTYPE err = OMX_ErrorNone;
  char componentRequested[OMTB_MAX_LEN] = {"\0"};
  char resultFileName[OMTB_MAX_LEN] = {"\0"};
  char fOpenMode[OMTB_MAX_LEN] = {"\0"};
  char testCaseId[OMTB_MAX_LEN] = {"\0"};
  char testCaseResult[OMTB_MAX_LEN] = {"\0"}; char returnString[OMTB_MAX_LEN] = {"\0"};
  FILE *fpResult = NULL;
  OMX_HANDLETYPE handle = NULL;                  /* Component handle */
  OMTB_OMX_API_TIMING_VAR_DECL;

  /* Read testcase ID */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, testCaseId);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }
  
  /* Read component name */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, componentRequested);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }

  /* Read result filename */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, resultFileName);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }

  /* Read result file type */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, fOpenMode);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }

  /* Open the result file */
  fpResult = fopen(resultFileName, fOpenMode);

  if(NULL == fpResult)
  {
    PRINT(PRINT_ERR_MSG, "%s: Error in result file open\n", __FUNCTION__);
    fprintf(fpResult, "%s : Error in result file open\n", testCaseId);
    return ERR_INVNAME;
  }

  /* OpenMax insufficient resources */
    
  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;

  err = OMX_Init ();

  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_Init");

  if(OMX_ErrorNone != err)
  {
    OMTB_OmxReturnStatusString(err, returnString);
    strcpy(testCaseResult, "FAIL - Error in OMX_Init()\n");
    fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
    fclose(fpResult);
    return ERR_INVNAME;
  }

  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;
  
  /* get component handle */
  err = OMX_GetHandle(&handle,
                      (OMX_STRING)componentRequested,
                      NULL,
                      NULL);
  
  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_GetHandle");

  if(OMX_ErrorBadParameter == err)
  {
    strcpy(testCaseResult, "PASS");
    fprintf(fpResult, "%s : %s\n", testCaseId, testCaseResult);
  }
  else
  {
    OMTB_OmxReturnStatusString(err, returnString);
    strcpy(testCaseResult, "FAIL");
    fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
    
    /* API entry time calculation macro */
    OMTB_OMX_API_ENTRY_TIME_CALC;

    /* OpenMax core uninitialization */
    err = OMX_Deinit ();

    /* API exit time calculation macro */
    OMTB_OMX_API_EXIT_TIME_CALC("OMX_Deinit");
    
    if(OMX_ErrorNone != err)
    {
      OMTB_OmxReturnStatusString(err, returnString);
      strcpy(testCaseResult, "FAIL - Error in OMX_Deinit()\n");
      fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
      result = ERR_INVNAME;
    }

    fclose(fpResult);
    return ERR_INVNAME;
  }
  
  /* free component handle */
  if(NULL != handle)
  {
    /* API entry time calculation macro */
    OMTB_OMX_API_ENTRY_TIME_CALC;
    
    err = OMX_FreeHandle(handle);
    
    /* API exit time calculation macro */
    OMTB_OMX_API_EXIT_TIME_CALC("OMX_FreeHandle");
    
    if(OMX_ErrorNone != err)
    {
      OMTB_OmxReturnStatusString(err, returnString);
      strcpy(testCaseResult, "FAIL - Error in OMX_FreeHandle()\n");
      fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
      
      result = ERR_INVNAME;
    }
    
  }

  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;
  
  /* OpenMax core uninitialization */
  err = OMX_Deinit ();

  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_Deinit");

    if(OMX_ErrorNone != err)
    {
      OMTB_OmxReturnStatusString(err, returnString);
      strcpy(testCaseResult, "FAIL - Error in OMX_Deinit()\n");
      fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
      result = ERR_INVNAME;
    }

  /* close the result file */
  fclose(fpResult);
  
  return (result);
}


/******************************************************************************\
 *      OMTB_OmxGetHandleNullHandle Function Definition
\******************************************************************************/
/**
 *
 *  @brief    This Function performs OMX_GetHandle API testing.
 *
 *  @param    Pointer to MX_DBG_CMD_CONTEXT_T structure
 *            Pointer to MX_DBG_CMD_Entry_T structure
 *            Character Double Pointer containing the command
 *
 *  @return   ERR_NOERR           successful,
 *            ERR_END_OF_CMD      help was requested,
 *            ERR_INVNAME         otherwise.
 */

MX_Result
OMTB_OmxGetHandleNullHandle(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine
)
{
  MX_Result  result = ERR_NOERR;
  OMX_ERRORTYPE err = OMX_ErrorNone;
  char componentRequested[OMTB_MAX_LEN] = {"\0"};
  char resultFileName[OMTB_MAX_LEN] = {"\0"};
  char fOpenMode[OMTB_MAX_LEN] = {"\0"};
  char testCaseId[OMTB_MAX_LEN] = {"\0"};
  char testCaseResult[OMTB_MAX_LEN] = {"\0"}; char returnString[OMTB_MAX_LEN] = {"\0"};
  FILE *fpResult = NULL;
  OMX_HANDLETYPE handle = NULL;                  /* Component handle */
  OMTB_OMX_API_TIMING_VAR_DECL;

  /* Read testcase ID */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, testCaseId);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }
  
  /* Read component name */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, componentRequested);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }

  /* Read result filename */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, resultFileName);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }

  /* Read result file type */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, fOpenMode);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }

  /* Open the result file */
  fpResult = fopen(resultFileName, fOpenMode);

  if(NULL == fpResult)
  {
    PRINT(PRINT_ERR_MSG, "%s: Error in result file open\n", __FUNCTION__);
    fprintf(fpResult, "%s : Error in result file open\n", testCaseId);
    return ERR_INVNAME;
  }

  /* OpenMax insufficient resources */
    
  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;

  err = OMX_Init ();

  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_Init");

  if(OMX_ErrorNone != err)
  {
    OMTB_OmxReturnStatusString(err, returnString);
    strcpy(testCaseResult, "FAIL - Error in OMX_Init()\n");
    fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
    fclose(fpResult);
    return ERR_INVNAME;
  }

  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;
  
  /* get component handle */
  err = OMX_GetHandle(NULL,
                      (OMX_STRING)componentRequested,
                      NULL,
                      &OMTB_APITestCallback);
  
  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_GetHandle");

  if(OMX_ErrorBadParameter == err)
  {
    strcpy(testCaseResult, "PASS");
    fprintf(fpResult, "%s : %s\n", testCaseId, testCaseResult);
  }
  else
  {
    OMTB_OmxReturnStatusString(err, returnString);
    strcpy(testCaseResult, "FAIL");
    fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
    
    /* API entry time calculation macro */
    OMTB_OMX_API_ENTRY_TIME_CALC;

    /* OpenMax core uninitialization */
    err = OMX_Deinit ();

    /* API exit time calculation macro */
    OMTB_OMX_API_EXIT_TIME_CALC("OMX_Deinit");
    
    if(OMX_ErrorNone != err)
    {
      OMTB_OmxReturnStatusString(err, returnString);
      strcpy(testCaseResult, "FAIL - Error in OMX_Deinit()\n");
      fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
      result = ERR_INVNAME;
    }

    fclose(fpResult);
    return ERR_INVNAME;
  }
  
  /* free component handle */
  if(NULL != handle)
  {
    /* API entry time calculation macro */
    OMTB_OMX_API_ENTRY_TIME_CALC;
    
    err = OMX_FreeHandle(handle);
    
    /* API exit time calculation macro */
    OMTB_OMX_API_EXIT_TIME_CALC("OMX_FreeHandle");
    
    if(OMX_ErrorNone != err)
    {
      OMTB_OmxReturnStatusString(err, returnString);
      strcpy(testCaseResult, "FAIL - Error in OMX_FreeHandle()\n");
      fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
      
      result = ERR_INVNAME;
    }
    
  }

  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;
  
  /* OpenMax core uninitialization */
  err = OMX_Deinit ();

  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_Deinit");

    if(OMX_ErrorNone != err)
    {
      OMTB_OmxReturnStatusString(err, returnString);
      strcpy(testCaseResult, "FAIL - Error in OMX_Deinit()\n");
      fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
      result = ERR_INVNAME;
    }

  /* close the result file */
  fclose(fpResult);
  
  return (result);
}


/******************************************************************************\
 *      OMTB_OmxGetHandleVerMismatch Function Definition
\******************************************************************************/
/**
 *
 *  @brief    This Function performs OMX_GetHandle API testing.
 *
 *  @param    Pointer to MX_DBG_CMD_CONTEXT_T structure
 *            Pointer to MX_DBG_CMD_Entry_T structure
 *            Character Double Pointer containing the command
 *
 *  @return   ERR_NOERR           successful,
 *            ERR_END_OF_CMD      help was requested,
 *            ERR_INVNAME         otherwise.
 */

MX_Result
OMTB_OmxGetHandleVerMismatch(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine
)
{
  MX_Result  result = ERR_NOERR;
  OMX_ERRORTYPE err = OMX_ErrorNone;
  char componentRequested[OMTB_MAX_LEN] = {"\0"};
  char resultFileName[OMTB_MAX_LEN] = {"\0"};
  char fOpenMode[OMTB_MAX_LEN] = {"\0"};
  char testCaseId[OMTB_MAX_LEN] = {"\0"};
  char testCaseResult[OMTB_MAX_LEN] = {"\0"}; char returnString[OMTB_MAX_LEN] = {"\0"};
  FILE *fpResult = NULL;
  OMX_HANDLETYPE handle = NULL;                  /* Component handle */
  OMTB_OMX_API_TIMING_VAR_DECL;

  /* Read testcase ID */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, testCaseId);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }
  
  /* Read component name */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, componentRequested);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }

  /* Read result filename */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, resultFileName);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }

  /* Read result file type */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, fOpenMode);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }

  /* Open the result file */
  fpResult = fopen(resultFileName, fOpenMode);

  if(NULL == fpResult)
  {
    PRINT(PRINT_ERR_MSG, "%s: Error in result file open\n", __FUNCTION__);
    fprintf(fpResult, "%s : Error in result file open\n", testCaseId);
    return ERR_INVNAME;
  }

  /* OpenMax insufficient resources */
    
  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;

  err = OMX_Init ();

  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_Init");

  if(OMX_ErrorNone != err)
  {
    OMTB_OmxReturnStatusString(err, returnString);
    strcpy(testCaseResult, "FAIL - Error in OMX_Init()\n");
    fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
    fclose(fpResult);
    return ERR_INVNAME;
  }

  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;
  
  /* get component handle */
  err = OMX_GetHandle(&handle,
                      (OMX_STRING)componentRequested,
                      NULL,
                      &OMTB_APITestCallback);
  
  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_GetHandle");

  if(OMX_ErrorVersionMismatch == err)
  {
    strcpy(testCaseResult, "PASS");
    fprintf(fpResult, "%s : %s\n", testCaseId, testCaseResult);
  }
  else
  {
    OMTB_OmxReturnStatusString(err, returnString);
    strcpy(testCaseResult, "FAIL");
    fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
    
    /* API entry time calculation macro */
    OMTB_OMX_API_ENTRY_TIME_CALC;

    /* OpenMax core uninitialization */
    err = OMX_Deinit ();

    /* API exit time calculation macro */
    OMTB_OMX_API_EXIT_TIME_CALC("OMX_Deinit");
    
    if(OMX_ErrorNone != err)
    {
      OMTB_OmxReturnStatusString(err, returnString);
      strcpy(testCaseResult, "FAIL - Error in OMX_Deinit()\n");
      fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
      result = ERR_INVNAME;
    }

    fclose(fpResult);
    return ERR_INVNAME;
  }
  
  /* free component handle */
  if(NULL != handle)
  {
    /* API entry time calculation macro */
    OMTB_OMX_API_ENTRY_TIME_CALC;
    
    err = OMX_FreeHandle(handle);
    
    /* API exit time calculation macro */
    OMTB_OMX_API_EXIT_TIME_CALC("OMX_FreeHandle");
    
    if(OMX_ErrorNone != err)
    {
      OMTB_OmxReturnStatusString(err, returnString);
      strcpy(testCaseResult, "FAIL - Error in OMX_FreeHandle()\n");
      fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
      
      result = ERR_INVNAME;
    }
    
  }

  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;
  
  /* OpenMax core uninitialization */
  err = OMX_Deinit ();

  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_Deinit");

    if(OMX_ErrorNone != err)
    {
      OMTB_OmxReturnStatusString(err, returnString);
      strcpy(testCaseResult, "FAIL - Error in OMX_Deinit()\n");
      fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
      result = ERR_INVNAME;
    }

  /* close the result file */
  fclose(fpResult);
  
  return (result);
}


/******************************************************************************\
 *      OMTB_OmxGetHandleTimeOut Function Definition
\******************************************************************************/
/**
 *
 *  @brief    This Function performs OMX_GetHandle API testing.
 *
 *  @param    Pointer to MX_DBG_CMD_CONTEXT_T structure
 *            Pointer to MX_DBG_CMD_Entry_T structure
 *            Character Double Pointer containing the command
 *
 *  @return   ERR_NOERR           successful,
 *            ERR_END_OF_CMD      help was requested,
 *            ERR_INVNAME         otherwise.
 */

MX_Result
OMTB_OmxGetHandleTimeOut(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine
)
{
  MX_Result  result = ERR_NOERR;
  OMX_ERRORTYPE err = OMX_ErrorNone;
  char componentRequested[OMTB_MAX_LEN] = {"\0"};
  char resultFileName[OMTB_MAX_LEN] = {"\0"};
  char fOpenMode[OMTB_MAX_LEN] = {"\0"};
  char testCaseId[OMTB_MAX_LEN] = {"\0"};
  char testCaseResult[OMTB_MAX_LEN] = {"\0"}; char returnString[OMTB_MAX_LEN] = {"\0"};
  FILE *fpResult = NULL;
  OMX_HANDLETYPE handle = NULL;                  /* Component handle */
  OMTB_OMX_API_TIMING_VAR_DECL;

  /* Read testcase ID */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, testCaseId);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }
  
  /* Read component name */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, componentRequested);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }

  /* Read result filename */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, resultFileName);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }

  /* Read result file type */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, fOpenMode);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }

  /* Open the result file */
  fpResult = fopen(resultFileName, fOpenMode);

  if(NULL == fpResult)
  {
    PRINT(PRINT_ERR_MSG, "%s: Error in result file open\n", __FUNCTION__);
    fprintf(fpResult, "%s : Error in result file open\n", testCaseId);
    return ERR_INVNAME;
  }

  /* OpenMax insufficient resources */
    
  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;

  err = OMX_Init ();

  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_Init");

  if(OMX_ErrorNone != err)
  {
    OMTB_OmxReturnStatusString(err, returnString);
    strcpy(testCaseResult, "FAIL - Error in OMX_Init()\n");
    fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
    fclose(fpResult);
    return ERR_INVNAME;
  }

  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;
  
  /* get component handle */
  err = OMX_GetHandle(&handle,
                      (OMX_STRING)componentRequested,
                      NULL,
                      &OMTB_APITestCallback);
  
  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_GetHandle");

  if(OMX_ErrorTimeout == err)
  {
    strcpy(testCaseResult, "PASS");
    fprintf(fpResult, "%s : %s\n", testCaseId, testCaseResult);
  }
  else
  {
    OMTB_OmxReturnStatusString(err, returnString);
    strcpy(testCaseResult, "FAIL");
    fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
    
    /* API entry time calculation macro */
    OMTB_OMX_API_ENTRY_TIME_CALC;

    /* OpenMax core uninitialization */
    err = OMX_Deinit ();

    /* API exit time calculation macro */
    OMTB_OMX_API_EXIT_TIME_CALC("OMX_Deinit");
    
    if(OMX_ErrorNone != err)
    {
      OMTB_OmxReturnStatusString(err, returnString);
      strcpy(testCaseResult, "FAIL - Error in OMX_Deinit()\n");
      fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
      result = ERR_INVNAME;
    }

    fclose(fpResult);
    return ERR_INVNAME;
  }
  
  /* free component handle */
  if(NULL != handle)
  {
    /* API entry time calculation macro */
    OMTB_OMX_API_ENTRY_TIME_CALC;
    
    err = OMX_FreeHandle(handle);
    
    /* API exit time calculation macro */
    OMTB_OMX_API_EXIT_TIME_CALC("OMX_FreeHandle");
    
    if(OMX_ErrorNone != err)
    {
      OMTB_OmxReturnStatusString(err, returnString);
      strcpy(testCaseResult, "FAIL - Error in OMX_FreeHandle()\n");
      fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
      
      result = ERR_INVNAME;
    }
    
  }

  
  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;
  
  /* OpenMax core uninitialization */
  err = OMX_Deinit ();

  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_Deinit");

    if(OMX_ErrorNone != err)
    {
      OMTB_OmxReturnStatusString(err, returnString);
      strcpy(testCaseResult, "FAIL - Error in OMX_Deinit()\n");
      fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
      result = ERR_INVNAME;
    }

  /* close the result file */
  fclose(fpResult);
  
  return (result);
}


/******************************************************************************\
 *      OMTB_OmxGetHandleWithoutCoreInit Function Definition
\******************************************************************************/
/**
 *
 *  @brief    This Function performs OMX_GetHandle API testing.
 *
 *  @param    Pointer to MX_DBG_CMD_CONTEXT_T structure
 *            Pointer to MX_DBG_CMD_Entry_T structure
 *            Character Double Pointer containing the command
 *
 *  @return   ERR_NOERR           successful,
 *            ERR_END_OF_CMD      help was requested,
 *            ERR_INVNAME         otherwise.
 */

MX_Result
OMTB_OmxGetHandleWithoutCoreInit(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine
)
{
  MX_Result  result = ERR_NOERR;
  OMX_ERRORTYPE err = OMX_ErrorNone;
  char componentRequested[OMTB_MAX_LEN] = {"\0"};
  char resultFileName[OMTB_MAX_LEN] = {"\0"};
  char fOpenMode[OMTB_MAX_LEN] = {"\0"};
  char testCaseId[OMTB_MAX_LEN] = {"\0"};
  char testCaseResult[OMTB_MAX_LEN] = {"\0"}; char returnString[OMTB_MAX_LEN] = {"\0"};
  FILE *fpResult = NULL;
  OMX_HANDLETYPE handle = NULL;                  /* Component handle */
  OMTB_OMX_API_TIMING_VAR_DECL;

  /* Read testcase ID */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, testCaseId);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }
  
  /* Read component name */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, componentRequested);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }

  /* Read result filename */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, resultFileName);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }

  /* Read result file type */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, fOpenMode);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }

  /* Open the result file */
  fpResult = fopen(resultFileName, fOpenMode);

  if(NULL == fpResult)
  {
    PRINT(PRINT_ERR_MSG, "%s: Error in result file open\n", __FUNCTION__);
    fprintf(fpResult, "%s : Error in result file open\n", testCaseId);
    return ERR_INVNAME;
  }

  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;
  
  /* get component handle */
  err = OMX_GetHandle(&handle,
                      (OMX_STRING)componentRequested,
                      NULL,
                      &OMTB_APITestCallback);
  
  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_GetHandle");

  if(OMX_ErrorNone == err)
  {
    strcpy(testCaseResult, "PASS");
    fprintf(fpResult, "%s : %s\n", testCaseId, testCaseResult);
  }
  else
  {
    OMTB_OmxReturnStatusString(err, returnString);
    strcpy(testCaseResult, "FAIL");
    fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
    fclose(fpResult);

    return ERR_INVNAME;
  }
  
#if 1 /* currently it's required as component doesn't check whether core is initialized or not */
  /* free component handle */
  if(NULL != handle)
  {
    /* API entry time calculation macro */
    OMTB_OMX_API_ENTRY_TIME_CALC;
    
    err = OMX_FreeHandle(handle);
    
    /* API exit time calculation macro */
    OMTB_OMX_API_EXIT_TIME_CALC("OMX_FreeHandle");
    
    if(OMX_ErrorNone != err)
    {
      OMTB_OmxReturnStatusString(err, returnString);
      strcpy(testCaseResult, "FAIL - Error in OMX_FreeHandle()\n");
      fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
      
      result = ERR_INVNAME;
    }
    
  }

  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;
  
  /* OpenMax core uninitialization */
  err = OMX_Deinit ();

  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_Deinit");

    if(OMX_ErrorNone != err)
    {
      OMTB_OmxReturnStatusString(err, returnString);
      strcpy(testCaseResult, "FAIL - Error in OMX_Deinit()\n");
      fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
      result = ERR_INVNAME;
    }
#endif

  /* close the result file */
  fclose(fpResult);
  
  return (result);
}


/******************************************************************************\
 *      OMTB_OmxFreeHandleOnce Function Definition
\******************************************************************************/
/**
 *
 *  @brief    This Function performs OMX_FreeHandle API testing.
 *
 *  @param    Pointer to MX_DBG_CMD_CONTEXT_T structure
 *            Pointer to MX_DBG_CMD_Entry_T structure
 *            Character Double Pointer containing the command
 *
 *  @return   ERR_NOERR           successful,
 *            ERR_END_OF_CMD      help was requested,
 *            ERR_INVNAME         otherwise.
 */

MX_Result
OMTB_OmxFreeHandleOnce(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine
)
{
  MX_Result  result = ERR_NOERR;
  OMX_ERRORTYPE err = OMX_ErrorNone;
  char componentRequested[OMTB_MAX_LEN] = {"\0"};
  char resultFileName[OMTB_MAX_LEN] = {"\0"};
  char fOpenMode[OMTB_MAX_LEN] = {"\0"};
  char testCaseId[OMTB_MAX_LEN] = {"\0"};
  char testCaseResult[OMTB_MAX_LEN] = {"\0"}; char returnString[OMTB_MAX_LEN] = {"\0"};
  FILE *fpResult = NULL;
  OMX_HANDLETYPE handle = NULL;                  /* Component handle */
  OMTB_OMX_API_TIMING_VAR_DECL;

  /* Read testcase ID */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, testCaseId);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }
  
  /* Read component name */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, componentRequested);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }

  /* Read result filename */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, resultFileName);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }

  /* Read result file type */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, fOpenMode);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }

  /* Open the result file */
  fpResult = fopen(resultFileName, fOpenMode);

  if(NULL == fpResult)
  {
    PRINT(PRINT_ERR_MSG, "%s: Error in result file open\n", __FUNCTION__);
    fprintf(fpResult, "%s : Error in result file open\n", testCaseId);
    return ERR_INVNAME;
  }

  /* OpenMax insufficient resources */
    
  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;

  err = OMX_Init ();

  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_Init");

  if(OMX_ErrorNone != err)
  {
    OMTB_OmxReturnStatusString(err, returnString);
    strcpy(testCaseResult, "FAIL - Error in OMX_Init()\n");
    fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
    fclose(fpResult);
    return ERR_INVNAME;
  }

  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;
  
  /* get component handle */
  err = OMX_GetHandle(&handle,
                      (OMX_STRING)componentRequested,
                      NULL,
                      &OMTB_APITestCallback);
  
  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_GetHandle");

  /* free component handle */
  if(NULL != handle)
  {
    /* API entry time calculation macro */
    OMTB_OMX_API_ENTRY_TIME_CALC;
    
    err = OMX_FreeHandle(handle);
    
    /* API exit time calculation macro */
    OMTB_OMX_API_EXIT_TIME_CALC("OMX_FreeHandle");
    
    if(OMX_ErrorNone == err)
    {
      strcpy(testCaseResult, "PASS");
      fprintf(fpResult, "%s : %s\n", testCaseId, testCaseResult);
    }
    else
    {
      OMTB_OmxReturnStatusString(err, returnString);
      strcpy(testCaseResult, "FAIL");
      fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);

      result = ERR_INVNAME;
    }
    
  }
  else
  {
      OMTB_OmxReturnStatusString(err, returnString);
      strcpy(testCaseResult, "FAIL - Error in OMX_GetHandle()\n");
      fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);

    result = ERR_INVNAME;
  }

  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;
  
  /* OpenMax core uninitialization */
  err = OMX_Deinit ();

  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_Deinit");

    if(OMX_ErrorNone != err)
    {
      OMTB_OmxReturnStatusString(err, returnString);
      strcpy(testCaseResult, "FAIL - Error in OMX_Deinit()\n");
      fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
      result = ERR_INVNAME;
    }

  /* close the result file */
  fclose(fpResult);
  
  return (result);
}


/******************************************************************************\
 *      OMTB_OmxFreeHandleVerMismatch Function Definition
\******************************************************************************/
/**
 *
 *  @brief    This Function performs OMX_FreeHandle API testing.
 *
 *  @param    Pointer to MX_DBG_CMD_CONTEXT_T structure
 *            Pointer to MX_DBG_CMD_Entry_T structure
 *            Character Double Pointer containing the command
 *
 *  @return   ERR_NOERR           successful,
 *            ERR_END_OF_CMD      help was requested,
 *            ERR_INVNAME         otherwise.
 */

MX_Result
OMTB_OmxFreeHandleVerMismatch(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine
)
{
  MX_Result  result = ERR_NOERR;
  OMX_ERRORTYPE err = OMX_ErrorNone;
  char componentRequested[OMTB_MAX_LEN] = {"\0"};
  char resultFileName[OMTB_MAX_LEN] = {"\0"};
  char fOpenMode[OMTB_MAX_LEN] = {"\0"};
  char testCaseId[OMTB_MAX_LEN] = {"\0"};
  char testCaseResult[OMTB_MAX_LEN] = {"\0"}; char returnString[OMTB_MAX_LEN] = {"\0"};
  FILE *fpResult = NULL;
  OMX_HANDLETYPE handle = NULL;                  /* Component handle */
  OMTB_OMX_API_TIMING_VAR_DECL;

  /* Read testcase ID */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, testCaseId);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }
  
  /* Read component name */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, componentRequested);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }

  /* Read result filename */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, resultFileName);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }

  /* Read result file type */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, fOpenMode);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }

  /* Open the result file */
  fpResult = fopen(resultFileName, fOpenMode);

  if(NULL == fpResult)
  {
    PRINT(PRINT_ERR_MSG, "%s: Error in result file open\n", __FUNCTION__);
    fprintf(fpResult, "%s : Error in result file open\n", testCaseId);
    return ERR_INVNAME;
  }

  /* OpenMax insufficient resources */
    
  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;

  err = OMX_Init ();

  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_Init");

  if(OMX_ErrorNone != err)
  {
    OMTB_OmxReturnStatusString(err, returnString);
    strcpy(testCaseResult, "FAIL - Error in OMX_Init()\n");
    fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
    fclose(fpResult);
    return ERR_INVNAME;
  }

  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;
  
  /* get component handle */
  err = OMX_GetHandle(&handle,
                      (OMX_STRING)componentRequested,
                      NULL,
                      &OMTB_APITestCallback);
  
  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_GetHandle");

  /* free component handle */
  if(NULL != handle)
  {
    /* API entry time calculation macro */
    OMTB_OMX_API_ENTRY_TIME_CALC;
    
    err = OMX_FreeHandle(handle);
    
    /* API exit time calculation macro */
    OMTB_OMX_API_EXIT_TIME_CALC("OMX_FreeHandle");
    
    if(OMX_ErrorVersionMismatch == err)
    {
      strcpy(testCaseResult, "PASS");
      fprintf(fpResult, "%s : %s\n", testCaseId, testCaseResult);
    }
    else
    {
      OMTB_OmxReturnStatusString(err, returnString);
      strcpy(testCaseResult, "FAIL");
      fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);

      result = ERR_INVNAME;
    }
    
  }
  else
  {
      OMTB_OmxReturnStatusString(err, returnString);
      strcpy(testCaseResult, "FAIL - Error in OMX_GetHandle()\n");
      fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);

    result = ERR_INVNAME;
  }

  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;
  
  /* OpenMax core uninitialization */
  err = OMX_Deinit ();

  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_Deinit");

    if(OMX_ErrorNone != err)
    {
      OMTB_OmxReturnStatusString(err, returnString);
      strcpy(testCaseResult, "FAIL - Error in OMX_Deinit()\n");
      fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
      result = ERR_INVNAME;
    }

  /* close the result file */
  fclose(fpResult);
  
  return (result);
}


/******************************************************************************\
 *      OMTB_OmxFreeHandleTimeOut Function Definition
\******************************************************************************/
/**
 *
 *  @brief    This Function performs OMX_FreeHandle API testing.
 *
 *  @param    Pointer to MX_DBG_CMD_CONTEXT_T structure
 *            Pointer to MX_DBG_CMD_Entry_T structure
 *            Character Double Pointer containing the command
 *
 *  @return   ERR_NOERR           successful,
 *            ERR_END_OF_CMD      help was requested,
 *            ERR_INVNAME         otherwise.
 */

MX_Result
OMTB_OmxFreeHandleTimeOut(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine
)
{
  MX_Result  result = ERR_NOERR;
  OMX_ERRORTYPE err = OMX_ErrorNone;
  char componentRequested[OMTB_MAX_LEN] = {"\0"};
  char resultFileName[OMTB_MAX_LEN] = {"\0"};
  char fOpenMode[OMTB_MAX_LEN] = {"\0"};
  char testCaseId[OMTB_MAX_LEN] = {"\0"};
  char testCaseResult[OMTB_MAX_LEN] = {"\0"}; char returnString[OMTB_MAX_LEN] = {"\0"};
  FILE *fpResult = NULL;
  OMX_HANDLETYPE handle = NULL;                  /* Component handle */
  OMTB_OMX_API_TIMING_VAR_DECL;

  /* Read testcase ID */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, testCaseId);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }
  
  /* Read component name */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, componentRequested);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }

  /* Read result filename */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, resultFileName);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }

  /* Read result file type */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, fOpenMode);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }

  /* Open the result file */
  fpResult = fopen(resultFileName, fOpenMode);

  if(NULL == fpResult)
  {
    PRINT(PRINT_ERR_MSG, "%s: Error in result file open\n", __FUNCTION__);
    fprintf(fpResult, "%s : Error in result file open\n", testCaseId);
    return ERR_INVNAME;
  }

  /* OpenMax insufficient resources */
    
  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;

  err = OMX_Init ();

  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_Init");

  if(OMX_ErrorNone != err)
  {
    OMTB_OmxReturnStatusString(err, returnString);
    strcpy(testCaseResult, "FAIL - Error in OMX_Init()\n");
    fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
    fclose(fpResult);
    return ERR_INVNAME;
  }

  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;
  
  /* get component handle */
  err = OMX_GetHandle(&handle,
                      (OMX_STRING)componentRequested,
                      NULL,
                      &OMTB_APITestCallback);
  
  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_GetHandle");

  /* free component handle */
  if(NULL != handle)
  {
    /* API entry time calculation macro */
    OMTB_OMX_API_ENTRY_TIME_CALC;
    
    err = OMX_FreeHandle(handle);
    
    /* API exit time calculation macro */
    OMTB_OMX_API_EXIT_TIME_CALC("OMX_FreeHandle");
    
    if(OMX_ErrorTimeout == err)
    {
      strcpy(testCaseResult, "PASS");
      fprintf(fpResult, "%s : %s\n", testCaseId, testCaseResult);
    }
    else
    {
      OMTB_OmxReturnStatusString(err, returnString);
      strcpy(testCaseResult, "FAIL");
      fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);

      result = ERR_INVNAME;
    }
    
  }
  else
  {
      OMTB_OmxReturnStatusString(err, returnString);
      strcpy(testCaseResult, "FAIL - Error in OMX_GetHandle()\n");
      fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);

    result = ERR_INVNAME;
  }

  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;
  
  /* OpenMax core uninitialization */
  err = OMX_Deinit ();

  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_Deinit");

    if(OMX_ErrorNone != err)
    {
      OMTB_OmxReturnStatusString(err, returnString);
      strcpy(testCaseResult, "FAIL - Error in OMX_Deinit()\n");
      fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
      result = ERR_INVNAME;
    }

  /* close the result file */
  fclose(fpResult);
  
  return (result);
}


/******************************************************************************\
 *      OMTB_OmxFreeHandleNullHandle Function Definition
\******************************************************************************/
/**
 *
 *  @brief    This Function performs OMX_FreeHandle API testing.
 *
 *  @param    Pointer to MX_DBG_CMD_CONTEXT_T structure
 *            Pointer to MX_DBG_CMD_Entry_T structure
 *            Character Double Pointer containing the command
 *
 *  @return   ERR_NOERR           successful,
 *            ERR_END_OF_CMD      help was requested,
 *            ERR_INVNAME         otherwise.
 */

MX_Result
OMTB_OmxFreeHandleNullHandle(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine
)
{
  MX_Result  result = ERR_NOERR;
  OMX_ERRORTYPE err = OMX_ErrorNone;
  char componentRequested[OMTB_MAX_LEN] = {"\0"};
  char resultFileName[OMTB_MAX_LEN] = {"\0"};
  char fOpenMode[OMTB_MAX_LEN] = {"\0"};
  char testCaseId[OMTB_MAX_LEN] = {"\0"};
  char testCaseResult[OMTB_MAX_LEN] = {"\0"}; char returnString[OMTB_MAX_LEN] = {"\0"};
  FILE *fpResult = NULL;
  OMTB_OMX_API_TIMING_VAR_DECL;

  /* Read testcase ID */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, testCaseId);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }
  
  /* Read component name */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, componentRequested);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }

  /* Read result filename */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, resultFileName);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }

  /* Read result file type */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, fOpenMode);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }

  /* Open the result file */
  fpResult = fopen(resultFileName, fOpenMode);

  if(NULL == fpResult)
  {
    PRINT(PRINT_ERR_MSG, "%s: Error in result file open\n", __FUNCTION__);
    fprintf(fpResult, "%s : Error in result file open\n", testCaseId);
    return ERR_INVNAME;
  }

  /* OpenMax insufficient resources */
    
  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;

  err = OMX_Init ();

  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_Init");

  if(OMX_ErrorNone != err)
  {
    OMTB_OmxReturnStatusString(err, returnString);
    strcpy(testCaseResult, "FAIL - Error in OMX_Init()\n");
    fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
    fclose(fpResult);
    return ERR_INVNAME;
  }

  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;
  
  err = OMX_FreeHandle(NULL);
  
  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_FreeHandle");
  
  if(OMX_ErrorBadParameter == err)
  {
    strcpy(testCaseResult, "PASS");
    fprintf(fpResult, "%s : %s\n", testCaseId, testCaseResult);
  }
  else
  {
      OMTB_OmxReturnStatusString(err, returnString);
      strcpy(testCaseResult, "FAIL");
      fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);

    result = ERR_INVNAME;
  }

  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;
  
  /* OpenMax core uninitialization */
  err = OMX_Deinit ();

  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_Deinit");

    if(OMX_ErrorNone != err)
    {
      OMTB_OmxReturnStatusString(err, returnString);
      strcpy(testCaseResult, "FAIL - Error in OMX_Deinit()\n");
      fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
      result = ERR_INVNAME;
    }

  /* close the result file */
  fclose(fpResult);
  
  return (result);
}


/******************************************************************************\
 *      OMTB_OmxComponentNameEnumOnce Function Definition
\******************************************************************************/
/**
 *
 *  @brief    This Function performs OMX_ComponentNameEnum API testing.
 *
 *  @param    Pointer to MX_DBG_CMD_CONTEXT_T structure
 *            Pointer to MX_DBG_CMD_Entry_T structure
 *            Character Double Pointer containing the command
 *
 *  @return   ERR_NOERR           successful,
 *            ERR_END_OF_CMD      help was requested,
 *            ERR_INVNAME         otherwise.
 */

MX_Result
OMTB_OmxComponentNameEnumOnce(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine
)
{
  char name[OMX_MAX_STRINGNAME_SIZE] = {"\0"};
  char componentRequested[OMTB_MAX_LEN] = {"\0"};
  char resultFileName[OMTB_MAX_LEN] = {"\0"};
  char fOpenMode[OMTB_MAX_LEN] = {"\0"};
  char testCaseId[OMTB_MAX_LEN] = {"\0"};
  char testCaseResult[OMTB_MAX_LEN] = {"\0"}; char returnString[OMTB_MAX_LEN] = {"\0"};
  FILE *fpResult = NULL;
  int index = 0;
  OMX_ERRORTYPE err = OMX_ErrorNone;
  MX_Result result = ERR_NOERR;
  OMTB_OMX_API_TIMING_VAR_DECL;

  PRINT(PRINT_FUNCTION_NAME, "Entering <function>: <%s>\n", __FUNCTION__);

  /* Read testcase ID */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, testCaseId);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }
  
  /* Read component name */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, componentRequested);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }

  /* Read result filename */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, resultFileName);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }

  /* Read result file type */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, fOpenMode);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }

  /* Open the result file */
  fpResult = fopen(resultFileName, fOpenMode);

  if(NULL == fpResult)
  {
    PRINT(PRINT_ERR_MSG, "%s: Error in result file open\n", __FUNCTION__);
    fprintf(fpResult, "%s : Error in result file open\n", testCaseId);
    return ERR_INVNAME;
  }
  
  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;
  
  /* enumerates through all the names of recognized components in system */
  err = OMX_ComponentNameEnum (name, OMX_MAX_STRINGNAME_SIZE, index);

  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_ComponentNameEnum");
  
  if (OMX_ErrorNone == err)
  {
    PRINT(PRINT_MUST, "Component %i: %s\n", index, name);
    strcpy(testCaseResult, "PASS");
    fprintf(fpResult, "%s : %s\n", testCaseId, testCaseResult);
  }
  else
  {
      OMTB_OmxReturnStatusString(err, returnString);
      strcpy(testCaseResult, "FAIL");
      fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
    result = ERR_INVNAME;
  }
  
  index++;

  fclose(fpResult);
  PRINT(PRINT_FUNCTION_NAME, "Leaving <function>: <%s>\n", __FUNCTION__);
  return result;
}


/******************************************************************************\
 *      OMTB_OmxComponentNameEnumNullCompName Function Definition
\******************************************************************************/
/**
 *
 *  @brief    This Function performs OMX_ComponentNameEnum API testing.
 *
 *  @param    Pointer to MX_DBG_CMD_CONTEXT_T structure
 *            Pointer to MX_DBG_CMD_Entry_T structure
 *            Character Double Pointer containing the command
 *
 *  @return   ERR_NOERR           successful,
 *            ERR_END_OF_CMD      help was requested,
 *            ERR_INVNAME         otherwise.
 */

MX_Result
OMTB_OmxComponentNameEnumNullCompName(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine
)
{
  char name[OMX_MAX_STRINGNAME_SIZE] = {"\0"};
  char componentRequested[OMTB_MAX_LEN] = {"\0"};
  char resultFileName[OMTB_MAX_LEN] = {"\0"};
  char fOpenMode[OMTB_MAX_LEN] = {"\0"};
  char testCaseId[OMTB_MAX_LEN] = {"\0"};
  char testCaseResult[OMTB_MAX_LEN] = {"\0"}; char returnString[OMTB_MAX_LEN] = {"\0"};
  FILE *fpResult = NULL;
  int index = 0;
  OMX_ERRORTYPE err = OMX_ErrorNone;
  MX_Result result = ERR_NOERR;
  OMTB_OMX_API_TIMING_VAR_DECL;

  PRINT(PRINT_FUNCTION_NAME, "Entering <function>: <%s>\n", __FUNCTION__);

  /* Read testcase ID */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, testCaseId);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }
  
  /* Read component name */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, componentRequested);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }

  /* Read result filename */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, resultFileName);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }

  /* Read result file type */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, fOpenMode);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }

  /* Open the result file */
  fpResult = fopen(resultFileName, fOpenMode);

  if(NULL == fpResult)
  {
    PRINT(PRINT_ERR_MSG, "%s: Error in result file open\n", __FUNCTION__);
    fprintf(fpResult, "%s : Error in result file open\n", testCaseId);
    return ERR_INVNAME;
  }
  
  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;
  
  /* enumerates through all the names of recognized components in system */
  err = OMX_ComponentNameEnum (NULL, OMX_MAX_STRINGNAME_SIZE, index);

  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_ComponentNameEnum");
  
  if (OMX_ErrorBadParameter == err)
  {
    PRINT(PRINT_MUST, "Component %i: %s\n", index, name);
    strcpy(testCaseResult, "PASS");
    fprintf(fpResult, "%s : %s\n", testCaseId, testCaseResult);
  }
  else
  {
      OMTB_OmxReturnStatusString(err, returnString);
      strcpy(testCaseResult, "FAIL");
      fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
    result = ERR_INVNAME;
  }
  
  index++;

  fclose(fpResult);
  PRINT(PRINT_FUNCTION_NAME, "Leaving <function>: <%s>\n", __FUNCTION__);
  return result;
}


/******************************************************************************\
 *      OMTB_OmxComponentNameEnumNoMore Function Definition
\******************************************************************************/
/**
 *
 *  @brief    This Function performs OMX_ComponentNameEnum API testing.
 *
 *  @param    Pointer to MX_DBG_CMD_CONTEXT_T structure
 *            Pointer to MX_DBG_CMD_Entry_T structure
 *            Character Double Pointer containing the command
 *
 *  @return   ERR_NOERR           successful,
 *            ERR_END_OF_CMD      help was requested,
 *            ERR_INVNAME         otherwise.
 */

MX_Result
OMTB_OmxComponentNameEnumNoMore(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine
)
{
  char name[OMX_MAX_STRINGNAME_SIZE] = {"\0"};
  char componentRequested[OMTB_MAX_LEN] = {"\0"};
  char resultFileName[OMTB_MAX_LEN] = {"\0"};
  char fOpenMode[OMTB_MAX_LEN] = {"\0"};
  char testCaseId[OMTB_MAX_LEN] = {"\0"};
  char testCaseResult[OMTB_MAX_LEN] = {"\0"}; char returnString[OMTB_MAX_LEN] = {"\0"};
  FILE *fpResult = NULL;
  int index = 0;
  OMX_ERRORTYPE err = OMX_ErrorNone;
  MX_Result result = ERR_NOERR;
  OMTB_OMX_API_TIMING_VAR_DECL;

  PRINT(PRINT_FUNCTION_NAME, "Entering <function>: <%s>\n", __FUNCTION__);

  /* Read testcase ID */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, testCaseId);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }
  
  /* Read component name */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, componentRequested);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }

  /* Read result filename */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, resultFileName);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }

  /* Read result file type */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, fOpenMode);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }

  /* Open the result file */
  fpResult = fopen(resultFileName, fOpenMode);

  if(NULL == fpResult)
  {
    PRINT(PRINT_ERR_MSG, "%s: Error in result file open\n", __FUNCTION__);
    fprintf(fpResult, "%s : Error in result file open\n", testCaseId);
    return ERR_INVNAME;
  }
  
  while(OMTB_LOOP) 
  {
    /* API entry time calculation macro */
    OMTB_OMX_API_ENTRY_TIME_CALC;
    
    /* enumerates through all the names of recognized components in system */
    err = OMX_ComponentNameEnum (name, OMX_MAX_STRINGNAME_SIZE, index);

    /* API exit time calculation macro */
    OMTB_OMX_API_EXIT_TIME_CALC("OMX_ComponentNameEnum");
    
    if ((NULL != name) && (OMX_ErrorNone == err))
    {
      PRINT(PRINT_MUST, "Component %i: %s\n", index, name);
    }
    else if (OMX_ErrorNoMore == err)
    {
      OMTB_OmxReturnStatus(err);
      strcpy(testCaseResult, "PASS");
      fprintf(fpResult, "%s : %s\n", testCaseId, testCaseResult);
      break;
    }
    else if(OMX_ErrorNone != err)
    {
      OMTB_OmxReturnStatusString(err, returnString);
      strcpy(testCaseResult, "FAIL");
      fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
      result = ERR_INVNAME;
      break;
    }
    
    index++;
  } // while(OMTB_LOOP)

  fclose(fpResult);
  PRINT(PRINT_FUNCTION_NAME, "Leaving <function>: <%s>\n", __FUNCTION__);
  return result;
}


/******************************************************************************\
 *      OMTB_OmxComponentNameEnumVerMismatch Function Definition
\******************************************************************************/
/**
 *
 *  @brief    This Function performs OMX_ComponentNameEnum API testing.
 *
 *  @param    Pointer to MX_DBG_CMD_CONTEXT_T structure
 *            Pointer to MX_DBG_CMD_Entry_T structure
 *            Character Double Pointer containing the command
 *
 *  @return   ERR_NOERR           successful,
 *            ERR_END_OF_CMD      help was requested,
 *            ERR_INVNAME         otherwise.
 */

MX_Result
OMTB_OmxComponentNameEnumVerMismatch(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine
)
{
  char name[OMX_MAX_STRINGNAME_SIZE] = {"\0"};
  char componentRequested[OMTB_MAX_LEN] = {"\0"};
  char resultFileName[OMTB_MAX_LEN] = {"\0"};
  char fOpenMode[OMTB_MAX_LEN] = {"\0"};
  char testCaseId[OMTB_MAX_LEN] = {"\0"};
  char testCaseResult[OMTB_MAX_LEN] = {"\0"}; char returnString[OMTB_MAX_LEN] = {"\0"};
  FILE *fpResult = NULL;
  int index = 0;
  OMX_ERRORTYPE err = OMX_ErrorNone;
  MX_Result result = ERR_NOERR;
  OMTB_OMX_API_TIMING_VAR_DECL;

  PRINT(PRINT_FUNCTION_NAME, "Entering <function>: <%s>\n", __FUNCTION__);

  /* Read testcase ID */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, testCaseId);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }
  
  /* Read component name */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, componentRequested);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }

  /* Read result filename */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, resultFileName);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }

  /* Read result file type */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, fOpenMode);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }

  /* Open the result file */
  fpResult = fopen(resultFileName, fOpenMode);

  if(NULL == fpResult)
  {
    PRINT(PRINT_ERR_MSG, "%s: Error in result file open\n", __FUNCTION__);
    fprintf(fpResult, "%s : Error in result file open\n", testCaseId);
    return ERR_INVNAME;
  }
  
  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;
  
  /* enumerates through all the names of recognized components in system */
  err = OMX_ComponentNameEnum (name, OMX_MAX_STRINGNAME_SIZE, index);

  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_ComponentNameEnum");
  
  if (OMX_ErrorVersionMismatch == err)
  {
    PRINT(PRINT_MUST, "Component %i: %s\n", index, name);
    strcpy(testCaseResult, "PASS");
    fprintf(fpResult, "%s : %s\n", testCaseId, testCaseResult);
  }
  else
  {
      OMTB_OmxReturnStatusString(err, returnString);
      strcpy(testCaseResult, "FAIL");
      fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
    result = ERR_INVNAME;
  }
  
  index++;

  fclose(fpResult);
  PRINT(PRINT_FUNCTION_NAME, "Leaving <function>: <%s>\n", __FUNCTION__);
  return result;
}


/******************************************************************************\
 *      OMTB_OmxGetRolesOfComponentOnce Function Definition
\******************************************************************************/
/**
 *
 *  @brief    This Function performs OMX_GetRolesOfComponent API testing.
 *
 *  @param    Pointer to MX_DBG_CMD_CONTEXT_T structure
 *            Pointer to MX_DBG_CMD_Entry_T structure
 *            Character Double Pointer containing the command
 *
 *  @return   ERR_NOERR           successful,
 *            ERR_END_OF_CMD      help was requested,
 *            ERR_INVNAME         otherwise.
 */

MX_Result
OMTB_OmxGetRolesOfComponentOnce(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine
) 
{
  OMX_U32 numOfRoles = 0;
  OMX_U8 **strOfRoles = NULL;
  OMX_ERRORTYPE err = OMX_ErrorNone;
  int index = 0;
  char componentRequested[OMTB_MAX_LEN] = {"\0"};
  char resultFileName[OMTB_MAX_LEN] = {"\0"};
  char fOpenMode[OMTB_MAX_LEN] = {"\0"};
  char testCaseId[OMTB_MAX_LEN] = {"\0"};
  char testCaseResult[OMTB_MAX_LEN] = {"\0"}; char returnString[OMTB_MAX_LEN] = {"\0"};
  FILE *fpResult = NULL;
  MX_Result result = ERR_NOERR;
  OMTB_OMX_API_TIMING_VAR_DECL;

  PRINT(PRINT_FUNCTION_NAME, "Entering <function>: <%s>\n", __FUNCTION__);

  /* Read testcase ID */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, testCaseId);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }
  
  /* Read component name */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, componentRequested);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }

  /* Read result filename */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, resultFileName);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }

  /* Read result file type */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, fOpenMode);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }

  /* Open the result file */
  fpResult = fopen(resultFileName, fOpenMode);

  if(NULL == fpResult)
  {
    PRINT(PRINT_ERR_MSG, "%s: Error in result file open\n", __FUNCTION__);
    fprintf(fpResult, "%s : Error in result file open\n", testCaseId);
    return ERR_INVNAME;
  }

  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;
  
  /* Get number of roles of component */
  err = OMX_GetRolesOfComponent(componentRequested, &numOfRoles, NULL);

  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_GetRolesOfComponent");

  if (OMX_ErrorNone == err)
  {
    strcpy(testCaseResult, "PASS");
    fprintf(fpResult, "%s : %s\n", testCaseId, testCaseResult);
  }
  else
  {
    PRINT(PRINT_ERR_MSG, 
        "In %s: Not able to retrieve number of roles of the given component\n",
        __FUNCTION__);
      OMTB_OmxReturnStatusString(err, returnString);
      strcpy(testCaseResult, "FAIL");
      fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
    fclose(fpResult);
    return ERR_INVNAME;
  }
  
  PRINT(PRINT_MUST, "<component , # of roles> : <%s , %i>\n",
                    componentRequested, (int) numOfRoles);

  if(0 == numOfRoles)
  {
    PRINT(PRINT_ERR_MSG, 
      "The Number or roles is 0\nThe component selected is not correct for \
the purpose of this test\n");    
    OMTB_OmxReturnStatus(err);
  }
  else 
  {
    /* allocate the memory based on the number of roles of the component */
    strOfRoles = (OMX_U8**)
                 TIMM_OSAL_Malloc( numOfRoles * sizeof(OMX_STRING),
                                   TIMM_OSAL_TRUE,
                                   0,
                                   TIMMOSAL_MEM_SEGMENT_EXT);
    for (index = 0; index < numOfRoles; index++)
    {
      *(strOfRoles + index) = (OMX_U8*)
                 TIMM_OSAL_Malloc( numOfRoles * OMX_MAX_STRINGNAME_SIZE,
                                   TIMM_OSAL_TRUE,
                                   0,
                                   TIMMOSAL_MEM_SEGMENT_EXT);
    }

    /* API entry time calculation macro */
    OMTB_OMX_API_ENTRY_TIME_CALC;
    
    /* Get the role string for the component */
    err = OMX_GetRolesOfComponent(componentRequested, &numOfRoles, strOfRoles);

    /* API exit time calculation macro */
    OMTB_OMX_API_EXIT_TIME_CALC("OMX_GetRolesOfComponent");
    
    if (OMX_ErrorNone != err) 
    {
      PRINT(PRINT_ERR_MSG, "Not able to retrieve the roles of the component\n");
      OMTB_OmxReturnStatusString(err, returnString);
      strcpy(testCaseResult, "FAIL");
      fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
      result = ERR_INVNAME;
    }
    else if(NULL != strOfRoles)
    {
      /* Display the component roles */
      for (index = 0; index < numOfRoles; index++)
      {
        PRINT(PRINT_MUST, "<Role # , Component Role> : <%i , %s>\n", 
                                (index + 1), *(strOfRoles + index));
      }
    }
    else
    {
      PRINT(PRINT_ERR_MSG, "Role string is NULL!!!\n");
      err = OMX_ErrorInvalidComponentName;
      OMTB_OmxReturnStatusString(err, returnString);
      strcpy(testCaseResult, "FAIL OMX ERROR OMX_ErrorInvalidComponentName");
      fprintf(fpResult, "%s : %s\n", testCaseId, testCaseResult);
      result = ERR_INVNAME;
    }

    /* Release the memory allocated for the number of roles of the component */
    for (index = 0; index < numOfRoles; index++)
    {
      TIMM_OSAL_Free(*(strOfRoles + index));
    }
    TIMM_OSAL_Free(strOfRoles);
  }

  fclose(fpResult);
  PRINT(PRINT_FUNCTION_NAME, "Leaving <function>: <%s>\n", __FUNCTION__);
  return result;
}


/******************************************************************************\
 *      OMTB_OmxGetRolesOfComponentNullCompName Function Definition
\******************************************************************************/
/**
 *
 *  @brief    This Function performs OMX_GetRolesOfComponent API testing.
 *
 *  @param    Pointer to MX_DBG_CMD_CONTEXT_T structure
 *            Pointer to MX_DBG_CMD_Entry_T structure
 *            Character Double Pointer containing the command
 *
 *  @return   ERR_NOERR           successful,
 *            ERR_END_OF_CMD      help was requested,
 *            ERR_INVNAME         otherwise.
 */

MX_Result
OMTB_OmxGetRolesOfComponentNullCompName(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine
) 
{
  OMX_U32 numOfRoles = 0;
  OMX_ERRORTYPE err = OMX_ErrorNone;
  char componentRequested[OMTB_MAX_LEN] = {"\0"};
  char resultFileName[OMTB_MAX_LEN] = {"\0"};
  char fOpenMode[OMTB_MAX_LEN] = {"\0"};
  char testCaseId[OMTB_MAX_LEN] = {"\0"};
  char testCaseResult[OMTB_MAX_LEN] = {"\0"}; char returnString[OMTB_MAX_LEN] = {"\0"};
  FILE *fpResult = NULL;
  MX_Result result = ERR_NOERR;
  OMTB_OMX_API_TIMING_VAR_DECL;

  PRINT(PRINT_FUNCTION_NAME, "Entering <function>: <%s>\n", __FUNCTION__);

  /* Read testcase ID */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, testCaseId);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }
  
  /* Read component name */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, componentRequested);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }

  /* Read result filename */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, resultFileName);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }

  /* Read result file type */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, fOpenMode);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }

  /* Open the result file */
  fpResult = fopen(resultFileName, fOpenMode);

  if(NULL == fpResult)
  {
    PRINT(PRINT_ERR_MSG, "%s: Error in result file open\n", __FUNCTION__);
    fprintf(fpResult, "%s : Error in result file open\n", testCaseId);
    return ERR_INVNAME;
  }

  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;
  
  /* Get number of roles of component */
  err = OMX_GetRolesOfComponent(NULL, &numOfRoles, NULL);

  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_GetRolesOfComponent");

  if (OMX_ErrorBadParameter == err)
  {
    strcpy(testCaseResult, "PASS");
    fprintf(fpResult, "%s : %s\n", testCaseId, testCaseResult);
  }
  else
  {
    PRINT(PRINT_ERR_MSG, 
        "In %s: Not able to retrieve number of roles of the given component\n",
        __FUNCTION__);
      OMTB_OmxReturnStatusString(err, returnString);
      strcpy(testCaseResult, "FAIL");
      fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
    result = ERR_INVNAME;
  }
  
  fclose(fpResult);
  PRINT(PRINT_FUNCTION_NAME, "Leaving <function>: <%s>\n", __FUNCTION__);
  return result;
}


/******************************************************************************\
 *      OMTB_OmxGetRolesOfComponentNullNumComp Function Definition
\******************************************************************************/
/**
 *
 *  @brief    This Function performs OMX_GetRolesOfComponent API testing.
 *
 *  @param    Pointer to MX_DBG_CMD_CONTEXT_T structure
 *            Pointer to MX_DBG_CMD_Entry_T structure
 *            Character Double Pointer containing the command
 *
 *  @return   ERR_NOERR           successful,
 *            ERR_END_OF_CMD      help was requested,
 *            ERR_INVNAME         otherwise.
 */

MX_Result
OMTB_OmxGetRolesOfComponentNullNumComp(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine
) 
{
  OMX_ERRORTYPE err = OMX_ErrorNone;
  char componentRequested[OMTB_MAX_LEN] = {"\0"};
  char resultFileName[OMTB_MAX_LEN] = {"\0"};
  char fOpenMode[OMTB_MAX_LEN] = {"\0"};
  char testCaseId[OMTB_MAX_LEN] = {"\0"};
  char testCaseResult[OMTB_MAX_LEN] = {"\0"}; char returnString[OMTB_MAX_LEN] = {"\0"};
  FILE *fpResult = NULL;
  MX_Result result = ERR_NOERR;
  OMTB_OMX_API_TIMING_VAR_DECL;

  PRINT(PRINT_FUNCTION_NAME, "Entering <function>: <%s>\n", __FUNCTION__);

  /* Read testcase ID */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, testCaseId);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }
  
  /* Read component name */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, componentRequested);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }

  /* Read result filename */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, resultFileName);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }

  /* Read result file type */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, fOpenMode);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }

  /* Open the result file */
  fpResult = fopen(resultFileName, fOpenMode);

  if(NULL == fpResult)
  {
    PRINT(PRINT_ERR_MSG, "%s: Error in result file open\n", __FUNCTION__);
    fprintf(fpResult, "%s : Error in result file open\n", testCaseId);
    return ERR_INVNAME;
  }

  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;
  
  /* Get number of roles of component */
  err = OMX_GetRolesOfComponent(componentRequested, NULL, NULL);

  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_GetRolesOfComponent");

  if (OMX_ErrorBadParameter == err)
  {
    strcpy(testCaseResult, "PASS");
    fprintf(fpResult, "%s : %s\n", testCaseId, testCaseResult);
  }
  else
  {
    PRINT(PRINT_ERR_MSG, 
        "In %s: Not able to retrieve number of roles of the given component\n",
        __FUNCTION__);
    OMTB_OmxReturnStatusString(err, returnString);
    strcpy(testCaseResult, "FAIL");
    fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
    result = ERR_INVNAME;
  }
  
  fclose(fpResult);
  PRINT(PRINT_FUNCTION_NAME, "Leaving <function>: <%s>\n", __FUNCTION__);
  return result;
}


/******************************************************************************\
 *      OMTB_OmxGetRolesOfComponentInvCompName Function Definition
\******************************************************************************/
/**
 *
 *  @brief    This Function performs OMX_GetRolesOfComponent API testing.
 *
 *  @param    Pointer to MX_DBG_CMD_CONTEXT_T structure
 *            Pointer to MX_DBG_CMD_Entry_T structure
 *            Character Double Pointer containing the command
 *
 *  @return   ERR_NOERR           successful,
 *            ERR_END_OF_CMD      help was requested,
 *            ERR_INVNAME         otherwise.
 */

MX_Result
OMTB_OmxGetRolesOfComponentInvCompName(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine
) 
{
  OMX_U32 numOfRoles = 0;
  OMX_ERRORTYPE err = OMX_ErrorNone;
  char componentRequested[OMTB_MAX_LEN] = {"\0"};
  char resultFileName[OMTB_MAX_LEN] = {"\0"};
  char fOpenMode[OMTB_MAX_LEN] = {"\0"};
  char testCaseId[OMTB_MAX_LEN] = {"\0"};
  char testCaseResult[OMTB_MAX_LEN] = {"\0"}; char returnString[OMTB_MAX_LEN] = {"\0"};
  FILE *fpResult = NULL;
  MX_Result result = ERR_NOERR;
  OMTB_OMX_API_TIMING_VAR_DECL;

  PRINT(PRINT_FUNCTION_NAME, "Entering <function>: <%s>\n", __FUNCTION__);

  /* Read testcase ID */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, testCaseId);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }
  
  /* Read component name */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, componentRequested);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }

  /* set invalid component name */
  TIMM_OSAL_Memset(componentRequested, 0x65, OMX_MAX_STRINGNAME_SIZE);
  componentRequested[OMX_MAX_STRINGNAME_SIZE + 1] = '\0';
  
  /* Read result filename */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, resultFileName);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }

  /* Read result file type */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, fOpenMode);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }

  /* Open the result file */
  fpResult = fopen(resultFileName, fOpenMode);

  if(NULL == fpResult)
  {
    PRINT(PRINT_ERR_MSG, "%s: Error in result file open\n", __FUNCTION__);
    fprintf(fpResult, "%s : Error in result file open\n", testCaseId);
    return ERR_INVNAME;
  }

  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;
  
  /* Get number of roles of component */
  err = OMX_GetRolesOfComponent(componentRequested, &numOfRoles, NULL);

  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_GetRolesOfComponent");

  if (OMX_ErrorInvalidComponentName == err)
  {
    strcpy(testCaseResult, "PASS");
    fprintf(fpResult, "%s : %s\n", testCaseId, testCaseResult);
  }
  else
  {
    PRINT(PRINT_ERR_MSG, 
        "In %s: Not able to retrieve number of roles of the given component\n",
        __FUNCTION__);
      OMTB_OmxReturnStatusString(err, returnString);
      strcpy(testCaseResult, "FAIL");
      fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
    result = ERR_INVNAME;
  }
  
  fclose(fpResult);
  PRINT(PRINT_FUNCTION_NAME, "Leaving <function>: <%s>\n", __FUNCTION__);
  return result;
}


/******************************************************************************\
 *      OMTB_OmxGetComponentsOfRoleOnce Function Definition
\******************************************************************************/
/**
 *
 *  @brief    This Function performs OMX_GetComponentsOfRole API testing.
 *
 *  @param    Pointer to MX_DBG_CMD_CONTEXT_T structure
 *            Pointer to MX_DBG_CMD_Entry_T structure
 *            Character Double Pointer containing the command
 *
 *  @return   ERR_NOERR           successful,
 *            ERR_END_OF_CMD      help was requested,
 *            ERR_INVNAME         otherwise.
 */

MX_Result
OMTB_OmxGetComponentsOfRoleOnce(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine
)
{
  OMX_U32 numCompPerRole = 0;
  OMX_U8 **strOfCompPerRole = NULL;
  OMX_ERRORTYPE err = OMX_ErrorNone;
  int index = 0;
  char roleName[OMX_MAX_STRINGNAME_SIZE] = {"\0"};
  MX_Result result = ERR_NOERR;
  char componentRequested[OMTB_MAX_LEN] = {"\0"};
  char resultFileName[OMTB_MAX_LEN] = {"\0"};
  char fOpenMode[OMTB_MAX_LEN] = {"\0"};
  char testCaseId[OMTB_MAX_LEN] = {"\0"};
  char testCaseResult[OMTB_MAX_LEN] = {"\0"}; char returnString[OMTB_MAX_LEN] = {"\0"};
  FILE *fpResult = NULL;
  OMTB_OMX_API_TIMING_VAR_DECL;

  PRINT(PRINT_FUNCTION_NAME, "Entering <function>: <%s>\n", __FUNCTION__);

  /* Read testcase ID */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, testCaseId);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }
  
  /* Read component name */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, componentRequested);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }

  /* Read result filename */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, resultFileName);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }

  /* Read result file type */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, fOpenMode);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }

  /* Open the result file */
  fpResult = fopen(resultFileName, fOpenMode);

  if(NULL == fpResult)
  {
    PRINT(PRINT_ERR_MSG, "%s: Error in result file open\n", __FUNCTION__);
    fprintf(fpResult, "%s : Error in result file open\n", testCaseId);
    return ERR_INVNAME;
  }
  
  /* Read component role name */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, roleName);
  if (ERR_NOERR != result)
  {
    XdbgCmdSyntaxShow(pContext, pCmdEntry);
    return result;
  }

  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;
  
  /* Getting number of components per role for given role name */
  err = OMX_GetComponentsOfRole(roleName, &numCompPerRole, NULL);

  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_GetComponentsOfRole");

  if (OMX_ErrorNone == err)
  {
    strcpy(testCaseResult, "PASS");
    fprintf(fpResult, "%s : %s\n", testCaseId, testCaseResult);
  }
  else
  {
    PRINT(PRINT_ERR_MSG, 
          "Not able to retrieve number of components of a given role\n");
    OMTB_OmxReturnStatusString(err, returnString);
    strcpy(testCaseResult, "FAIL");
    fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
    fclose(fpResult);
    return ERR_INVNAME;
  }

  /* allocate the memory to hold name of the component supporting given role */
  strOfCompPerRole = (OMX_U8**)
                     TIMM_OSAL_Malloc( numCompPerRole * sizeof(OMX_STRING),
                                       TIMM_OSAL_TRUE,
                                       0,
                                       TIMMOSAL_MEM_SEGMENT_EXT);

  for (index = 0; index < numCompPerRole; index++)
  {
    strOfCompPerRole[index] = (OMX_U8*)
                      TIMM_OSAL_Malloc( OMX_MAX_STRINGNAME_SIZE,
                                        TIMM_OSAL_TRUE,
                                        0,
                                        TIMMOSAL_MEM_SEGMENT_EXT);
  }
  
  PRINT(PRINT_MUST, "Number of components per role <%s> : %i\n", 
        roleName, (int)numCompPerRole);

  
  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;

  /* Get all the components supporting given role */
  err = OMX_GetComponentsOfRole(roleName, &numCompPerRole, strOfCompPerRole);

  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_GetComponentsOfRole");
  
  if (OMX_ErrorNone != err)
  {
    PRINT(PRINT_ERR_MSG, 
          "Not able to retrieve the components of a given role\n");
    OMTB_OmxReturnStatusString(err, returnString);
    strcpy(testCaseResult, "FAIL");
    fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
    result = ERR_INVNAME;
  }
  else if(0 < numCompPerRole)
  {
    /* Display the name of the components supporting given role */
    PRINT(PRINT_MUST, "The components supporting given role <%s> are:\n",
          roleName);
    for (index = 0; index < numCompPerRole; index++)
    {
      PRINT(PRINT_MUST, "%s\n", strOfCompPerRole[index]);
    }
  }
  
  /* Release the memory allocated for name of he component */
  for (index = 0; index < numCompPerRole; index++)
  {
    if(strOfCompPerRole[index])
    {
      TIMM_OSAL_Free(strOfCompPerRole[index]);
      strOfCompPerRole[index] = NULL;
    }
  }

  if(strOfCompPerRole)
  {
    TIMM_OSAL_Free(strOfCompPerRole);
    strOfCompPerRole = NULL;
  }

  fclose(fpResult);
  PRINT(PRINT_FUNCTION_NAME, "Leaving <function>: <%s>\n", __FUNCTION__);
  return result;
}


/******************************************************************************\
 *      OMTB_OmxGetComponentsOfRoleNullRole Function Definition
\******************************************************************************/
/**
 *
 *  @brief    This Function performs OMX_GetComponentsOfRole API testing.
 *
 *  @param    Pointer to MX_DBG_CMD_CONTEXT_T structure
 *            Pointer to MX_DBG_CMD_Entry_T structure
 *            Character Double Pointer containing the command
 *
 *  @return   ERR_NOERR           successful,
 *            ERR_END_OF_CMD      help was requested,
 *            ERR_INVNAME         otherwise.
 */

MX_Result
OMTB_OmxGetComponentsOfRoleNullRole(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine
)
{
  OMX_U32 numCompPerRole = 0;
  OMX_ERRORTYPE err = OMX_ErrorNone;
  char roleName[OMX_MAX_STRINGNAME_SIZE] = {"\0"};
  MX_Result result = ERR_NOERR;
  char componentRequested[OMTB_MAX_LEN] = {"\0"};
  char resultFileName[OMTB_MAX_LEN] = {"\0"};
  char fOpenMode[OMTB_MAX_LEN] = {"\0"};
  char testCaseId[OMTB_MAX_LEN] = {"\0"};
  char testCaseResult[OMTB_MAX_LEN] = {"\0"}; char returnString[OMTB_MAX_LEN] = {"\0"};
  FILE *fpResult = NULL;
  OMTB_OMX_API_TIMING_VAR_DECL;

  PRINT(PRINT_FUNCTION_NAME, "Entering <function>: <%s>\n", __FUNCTION__);

  /* Read testcase ID */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, testCaseId);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }
  
  /* Read component name */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, componentRequested);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }

  /* Read result filename */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, resultFileName);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }

  /* Read result file type */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, fOpenMode);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }

  /* Open the result file */
  fpResult = fopen(resultFileName, fOpenMode);

  if(NULL == fpResult)
  {
    PRINT(PRINT_ERR_MSG, "%s: Error in result file open\n", __FUNCTION__);
    fprintf(fpResult, "%s : Error in result file open\n", testCaseId);
    return ERR_INVNAME;
  }
  
  /* Read component role name */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, roleName);
  if (ERR_NOERR != result)
  {
    XdbgCmdSyntaxShow(pContext, pCmdEntry);
    return result;
  }

  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;
  
  /* Getting number of components per role for given role name */
  err = OMX_GetComponentsOfRole(NULL, &numCompPerRole, NULL);

  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_GetComponentsOfRole");

  if (OMX_ErrorBadParameter == err)
  {
    strcpy(testCaseResult, "PASS");
    fprintf(fpResult, "%s : %s\n", testCaseId, testCaseResult);
  }
  else
  {
    PRINT(PRINT_ERR_MSG, 
          "Not able to retrieve number of components of a given role\n");
    OMTB_OmxReturnStatusString(err, returnString);
    strcpy(testCaseResult, "FAIL");
    fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
    result = ERR_INVNAME;
  }

  fclose(fpResult);
  PRINT(PRINT_FUNCTION_NAME, "Leaving <function>: <%s>\n", __FUNCTION__);
  return result;
}


/******************************************************************************\
 *      OMTB_OmxGetComponentsOfRoleNullNumComp Function Definition
\******************************************************************************/
/**
 *
 *  @brief    This Function performs OMX_GetComponentsOfRole API testing.
 *
 *  @param    Pointer to MX_DBG_CMD_CONTEXT_T structure
 *            Pointer to MX_DBG_CMD_Entry_T structure
 *            Character Double Pointer containing the command
 *
 *  @return   ERR_NOERR           successful,
 *            ERR_END_OF_CMD      help was requested,
 *            ERR_INVNAME         otherwise.
 */

MX_Result
OMTB_OmxGetComponentsOfRoleNullNumComp(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine
)
{
  OMX_ERRORTYPE err = OMX_ErrorNone;
  char roleName[OMX_MAX_STRINGNAME_SIZE] = {"\0"};
  MX_Result result = ERR_NOERR;
  char componentRequested[OMTB_MAX_LEN] = {"\0"};
  char resultFileName[OMTB_MAX_LEN] = {"\0"};
  char fOpenMode[OMTB_MAX_LEN] = {"\0"};
  char testCaseId[OMTB_MAX_LEN] = {"\0"};
  char testCaseResult[OMTB_MAX_LEN] = {"\0"}; char returnString[OMTB_MAX_LEN] = {"\0"};
  FILE *fpResult = NULL;
  OMTB_OMX_API_TIMING_VAR_DECL;

  PRINT(PRINT_FUNCTION_NAME, "Entering <function>: <%s>\n", __FUNCTION__);

  /* Read testcase ID */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, testCaseId);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }
  
  /* Read component name */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, componentRequested);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }

  /* Read result filename */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, resultFileName);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }

  /* Read result file type */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, fOpenMode);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }

  /* Open the result file */
  fpResult = fopen(resultFileName, fOpenMode);

  if(NULL == fpResult)
  {
    PRINT(PRINT_ERR_MSG, "%s: Error in result file open\n", __FUNCTION__);
    fprintf(fpResult, "%s : Error in result file open\n", testCaseId);
    return ERR_INVNAME;
  }
  
  /* Read component role name */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, roleName);
  if (ERR_NOERR != result)
  {
    XdbgCmdSyntaxShow(pContext, pCmdEntry);
    return result;
  }

  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;
  
  /* Getting number of components per role for given role name */
  err = OMX_GetComponentsOfRole(roleName, NULL, NULL);

  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_GetComponentsOfRole");

  if (OMX_ErrorBadParameter == err)
  {
    strcpy(testCaseResult, "PASS");
    fprintf(fpResult, "%s : %s\n", testCaseId, testCaseResult);
  }
  else
  {
    PRINT(PRINT_ERR_MSG, 
          "Not able to retrieve number of components of a given role\n");
    OMTB_OmxReturnStatusString(err, returnString);
    strcpy(testCaseResult, "FAIL");
    fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
    result = ERR_INVNAME;
  }

  fclose(fpResult);
  PRINT(PRINT_FUNCTION_NAME, "Leaving <function>: <%s>\n", __FUNCTION__);
  return result;
}


/******************************************************************************\
 *      OMTB_OmxGetCompVersionOnce Function Definition
\******************************************************************************/
/**
 *
 *  @brief    This Function performs OMX_GetComponentVersion API testing.
 *
 *  @param    Pointer to MX_DBG_CMD_CONTEXT_T structure
 *            Pointer to MX_DBG_CMD_Entry_T structure
 *            Character Double Pointer containing the command
 *
 *  @return   ERR_NOERR           successful,
 *            ERR_END_OF_CMD      help was requested,
 *            ERR_INVNAME         otherwise.
 */

MX_Result
OMTB_OmxGetCompVersionOnce(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine
)
{
  MX_Result  result = ERR_NOERR;
  OMX_ERRORTYPE err = OMX_ErrorNone;
  char componentRequested[OMTB_MAX_LEN] = {"\0"};
  char resultFileName[OMTB_MAX_LEN] = {"\0"};
  char fOpenMode[OMTB_MAX_LEN] = {"\0"};
  char testCaseId[OMTB_MAX_LEN] = {"\0"};
  char testCaseResult[OMTB_MAX_LEN] = {"\0"}; char returnString[OMTB_MAX_LEN] = {"\0"};
  FILE *fpResult = NULL;
  OMX_HANDLETYPE handle = NULL;                  /* Component handle */
  char component[OMX_MAX_STRINGNAME_SIZE] = {"\0"};
  OMX_VERSIONTYPE pComponentVersion;
  OMX_VERSIONTYPE pSpecVersion;
  OMX_UUIDTYPE pComponentUUID;
  OMTB_OMX_API_TIMING_VAR_DECL;

  /* Read testcase ID */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, testCaseId);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }
  
  /* Read component name */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, componentRequested);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }

  /* Read result filename */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, resultFileName);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }

  /* Read result file type */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, fOpenMode);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }

  /* Open the result file */
  fpResult = fopen(resultFileName, fOpenMode);

  if(NULL == fpResult)
  {
    PRINT(PRINT_ERR_MSG, "%s: Error in result file open\n", __FUNCTION__);
    fprintf(fpResult, "%s : Error in result file open\n", testCaseId);
    return ERR_INVNAME;
  }

  /* OpenMax insufficient resources */
    
  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;

  err = OMX_Init ();

  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_Init");

  if(OMX_ErrorNone != err)
  {
    OMTB_OmxReturnStatusString(err, returnString);
    strcpy(testCaseResult, "FAIL - Error in OMX_Init()\n");
    fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
    fclose(fpResult);
    return ERR_INVNAME;
  }

  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;
  
  /* get component handle */
  err = OMX_GetHandle(&handle,
                      (OMX_STRING)componentRequested,
                      NULL,
                      &OMTB_APITestCallback);
  
  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_GetHandle");

  if(OMX_ErrorNone != err)
  {
      OMTB_OmxReturnStatusString(err, returnString);
      strcpy(testCaseResult, "FAIL - Error in OMX_GetHandle()\n");
      fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);

    /* API entry time calculation macro */
    OMTB_OMX_API_ENTRY_TIME_CALC;

    /* OpenMax core uninitialization */
    err = OMX_Deinit ();

    /* API exit time calculation macro */
    OMTB_OMX_API_EXIT_TIME_CALC("OMX_Deinit");
    
    if(OMX_ErrorNone != err)
    {
      OMTB_OmxReturnStatusString(err, returnString);
      strcpy(testCaseResult, "FAIL - Error in OMX_Deinit()\n");
      fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
      result = ERR_INVNAME;
    }
    
    fclose(fpResult);
    return ERR_INVNAME;
  }

  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;
  
  /* Get the component version number */
  err = OMX_GetComponentVersion(handle,
                                component,
                                &pComponentVersion,
                                &pSpecVersion,
                                &pComponentUUID);

  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_GetComponentVersion");

  if(OMX_ErrorNone == err)
  {
    strcpy(testCaseResult, "PASS");
    fprintf(fpResult, "%s : %s\n", testCaseId, testCaseResult);
  }
  else
  {
    OMTB_OmxReturnStatusString(err, returnString);
    strcpy(testCaseResult, "FAIL");
    fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
    result = ERR_INVNAME;
  }
  
  /* free component handle */
  if(NULL != handle)
  {
    /* API entry time calculation macro */
    OMTB_OMX_API_ENTRY_TIME_CALC;
    
    err = OMX_FreeHandle(handle);
    
    /* API exit time calculation macro */
    OMTB_OMX_API_EXIT_TIME_CALC("OMX_FreeHandle");
    
    if(OMX_ErrorNone != err)
    {
	OMTB_OmxReturnStatusString(err, returnString);
    strcpy(testCaseResult, "FAIL - Error in OMX_FreeHandle()\n");
    fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);

      result = ERR_INVNAME;
    }
    
  }

  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;
  
  /* OpenMax core uninitialization */
  err = OMX_Deinit ();

  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_Deinit");

    if(OMX_ErrorNone != err)
    {
      OMTB_OmxReturnStatusString(err, returnString);
      strcpy(testCaseResult, "FAIL - Error in OMX_Deinit()\n");
      fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
      result = ERR_INVNAME;
    }

  /* close the result file */
  fclose(fpResult);
  
  return (result);
}


/******************************************************************************\
 *      OMTB_OmxGetCompVersionNullHandle Function Definition
\******************************************************************************/
/**
 *
 *  @brief    This Function performs OMX_GetComponentVersion API testing.
 *
 *  @param    Pointer to MX_DBG_CMD_CONTEXT_T structure
 *            Pointer to MX_DBG_CMD_Entry_T structure
 *            Character Double Pointer containing the command
 *
 *  @return   ERR_NOERR           successful,
 *            ERR_END_OF_CMD      help was requested,
 *            ERR_INVNAME         otherwise.
 */

MX_Result
OMTB_OmxGetCompVersionNullHandle(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine
)
{
  MX_Result  result = ERR_NOERR;
  OMX_ERRORTYPE err = OMX_ErrorNone;
  char componentRequested[OMTB_MAX_LEN] = {"\0"};
  char resultFileName[OMTB_MAX_LEN] = {"\0"};
  char fOpenMode[OMTB_MAX_LEN] = {"\0"};
  char testCaseId[OMTB_MAX_LEN] = {"\0"};
  char testCaseResult[OMTB_MAX_LEN] = {"\0"}; char returnString[OMTB_MAX_LEN] = {"\0"};
  FILE *fpResult = NULL;
  OMX_HANDLETYPE handle = NULL;                  /* Component handle */
  char component[OMX_MAX_STRINGNAME_SIZE] = {"\0"};
  OMX_VERSIONTYPE pComponentVersion;
  OMX_VERSIONTYPE pSpecVersion;
  OMX_UUIDTYPE pComponentUUID;
  OMTB_OMX_API_TIMING_VAR_DECL;

  /* Read testcase ID */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, testCaseId);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }
  
  /* Read component name */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, componentRequested);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }

  /* Read result filename */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, resultFileName);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }

  /* Read result file type */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, fOpenMode);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }

  /* Open the result file */
  fpResult = fopen(resultFileName, fOpenMode);

  if(NULL == fpResult)
  {
    PRINT(PRINT_ERR_MSG, "%s: Error in result file open\n", __FUNCTION__);
    fprintf(fpResult, "%s : Error in result file open\n", testCaseId);
    return ERR_INVNAME;
  }

  /* OpenMax insufficient resources */
    
  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;

  err = OMX_Init ();

  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_Init");

  if(OMX_ErrorNone != err)
  {
    OMTB_OmxReturnStatusString(err, returnString);
    strcpy(testCaseResult, "FAIL - Error in OMX_Init()\n");
    fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
    fclose(fpResult);
    return ERR_INVNAME;
  }

  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;
  
  /* get component handle */
  err = OMX_GetHandle(&handle,
                      (OMX_STRING)componentRequested,
                      NULL,
                      &OMTB_APITestCallback);
  
  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_GetHandle");

  if(OMX_ErrorNone != err)
  {
      OMTB_OmxReturnStatusString(err, returnString);
      strcpy(testCaseResult, "FAIL - Error in OMX_GetHandle()\n");
      fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);

    /* API entry time calculation macro */
    OMTB_OMX_API_ENTRY_TIME_CALC;

    /* OpenMax core uninitialization */
    err = OMX_Deinit ();

    /* API exit time calculation macro */
    OMTB_OMX_API_EXIT_TIME_CALC("OMX_Deinit");
    
    if(OMX_ErrorNone != err)
    {
      OMTB_OmxReturnStatusString(err, returnString);
      strcpy(testCaseResult, "FAIL - Error in OMX_Deinit()\n");
      fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
      result = ERR_INVNAME;
    }
    
    fclose(fpResult);
    return ERR_INVNAME;
  }

  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;
  
  /* Get the component version number */
  err = OMX_GetComponentVersion(NULL,
                                component,
                                &pComponentVersion,
                                &pSpecVersion,
                                &pComponentUUID);

  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_GetComponentVersion");

  if(OMX_ErrorBadParameter == err)
  {
    strcpy(testCaseResult, "PASS");
    fprintf(fpResult, "%s : %s\n", testCaseId, testCaseResult);
  }
  else
  {
    OMTB_OmxReturnStatusString(err, returnString);
    strcpy(testCaseResult, "FAIL");
    fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
    result = ERR_INVNAME;
  }
  
  /* free component handle */
  if(NULL != handle)
  {
    /* API entry time calculation macro */
    OMTB_OMX_API_ENTRY_TIME_CALC;
    
    err = OMX_FreeHandle(handle);
    
    /* API exit time calculation macro */
    OMTB_OMX_API_EXIT_TIME_CALC("OMX_FreeHandle");
    
    if(OMX_ErrorNone != err)
    {
	OMTB_OmxReturnStatusString(err, returnString);
    strcpy(testCaseResult, "FAIL - Error in OMX_FreeHandle()\n");
    fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);

      result = ERR_INVNAME;
    }
    
  }

  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;
  
  /* OpenMax core uninitialization */
  err = OMX_Deinit ();

  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_Deinit");

    if(OMX_ErrorNone != err)
    {
      OMTB_OmxReturnStatusString(err, returnString);
      strcpy(testCaseResult, "FAIL - Error in OMX_Deinit()\n");
      fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
      result = ERR_INVNAME;
    }

  /* close the result file */
  fclose(fpResult);
  
  return (result);
}


/******************************************************************************\
 *      OMTB_OmxGetCompVersionNullCompName Function Definition
\******************************************************************************/
/**
 *
 *  @brief    This Function performs OMX_GetComponentVersion API testing.
 *
 *  @param    Pointer to MX_DBG_CMD_CONTEXT_T structure
 *            Pointer to MX_DBG_CMD_Entry_T structure
 *            Character Double Pointer containing the command
 *
 *  @return   ERR_NOERR           successful,
 *            ERR_END_OF_CMD      help was requested,
 *            ERR_INVNAME         otherwise.
 */

MX_Result
OMTB_OmxGetCompVersionNullCompName(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine
)
{
  MX_Result  result = ERR_NOERR;
  OMX_ERRORTYPE err = OMX_ErrorNone;
  char componentRequested[OMTB_MAX_LEN] = {"\0"};
  char resultFileName[OMTB_MAX_LEN] = {"\0"};
  char fOpenMode[OMTB_MAX_LEN] = {"\0"};
  char testCaseId[OMTB_MAX_LEN] = {"\0"};
  char testCaseResult[OMTB_MAX_LEN] = {"\0"}; char returnString[OMTB_MAX_LEN] = {"\0"};
  FILE *fpResult = NULL;
  OMX_HANDLETYPE handle = NULL;                  /* Component handle */
  OMX_VERSIONTYPE pComponentVersion;
  OMX_VERSIONTYPE pSpecVersion;
  OMX_UUIDTYPE pComponentUUID;
  OMTB_OMX_API_TIMING_VAR_DECL;

  /* Read testcase ID */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, testCaseId);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }
  
  /* Read component name */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, componentRequested);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }

  /* Read result filename */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, resultFileName);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }

  /* Read result file type */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, fOpenMode);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }

  /* Open the result file */
  fpResult = fopen(resultFileName, fOpenMode);

  if(NULL == fpResult)
  {
    PRINT(PRINT_ERR_MSG, "%s: Error in result file open\n", __FUNCTION__);
    fprintf(fpResult, "%s : Error in result file open\n", testCaseId);
    return ERR_INVNAME;
  }

  /* OpenMax insufficient resources */
    
  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;

  err = OMX_Init ();

  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_Init");

  if(OMX_ErrorNone != err)
  {
    OMTB_OmxReturnStatusString(err, returnString);
    strcpy(testCaseResult, "FAIL - Error in OMX_Init()\n");
    fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
    fclose(fpResult);
    return ERR_INVNAME;
  }

  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;
  
  /* get component handle */
  err = OMX_GetHandle(&handle,
                      (OMX_STRING)componentRequested,
                      NULL,
                      &OMTB_APITestCallback);
  
  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_GetHandle");

  if(OMX_ErrorNone != err)
  {
      OMTB_OmxReturnStatusString(err, returnString);
      strcpy(testCaseResult, "FAIL - Error in OMX_GetHandle()\n");
      fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);

    /* API entry time calculation macro */
    OMTB_OMX_API_ENTRY_TIME_CALC;

    /* OpenMax core uninitialization */
    err = OMX_Deinit ();

    /* API exit time calculation macro */
    OMTB_OMX_API_EXIT_TIME_CALC("OMX_Deinit");
    
    if(OMX_ErrorNone != err)
    {
      OMTB_OmxReturnStatusString(err, returnString);
      strcpy(testCaseResult, "FAIL - Error in OMX_Deinit()\n");
      fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
      result = ERR_INVNAME;
    }
    
    fclose(fpResult);
    return ERR_INVNAME;
  }

  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;
  
  /* Get the component version number */
  err = OMX_GetComponentVersion(handle,
                                NULL,
                                &pComponentVersion,
                                &pSpecVersion,
                                &pComponentUUID);

  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_GetComponentVersion");

  if(OMX_ErrorBadParameter == err)
  {
    strcpy(testCaseResult, "PASS");
    fprintf(fpResult, "%s : %s\n", testCaseId, testCaseResult);
  }
  else
  {
    OMTB_OmxReturnStatusString(err, returnString);
    strcpy(testCaseResult, "FAIL");
    fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
    result = ERR_INVNAME;
  }
  
  /* free component handle */
  if(NULL != handle)
  {
    /* API entry time calculation macro */
    OMTB_OMX_API_ENTRY_TIME_CALC;
    
    err = OMX_FreeHandle(handle);
    
    /* API exit time calculation macro */
    OMTB_OMX_API_EXIT_TIME_CALC("OMX_FreeHandle");
    
    if(OMX_ErrorNone != err)
    {
	OMTB_OmxReturnStatusString(err, returnString);
    strcpy(testCaseResult, "FAIL - Error in OMX_FreeHandle()\n");
    fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);

      result = ERR_INVNAME;
    }
    
  }

  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;
  
  /* OpenMax core uninitialization */
  err = OMX_Deinit ();

  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_Deinit");

    if(OMX_ErrorNone != err)
    {
      OMTB_OmxReturnStatusString(err, returnString);
      strcpy(testCaseResult, "FAIL - Error in OMX_Deinit()\n");
      fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
      result = ERR_INVNAME;
    }

  /* close the result file */
  fclose(fpResult);
  
  return (result);
}


/******************************************************************************\
 *      OMTB_OmxGetCompVersionNullCompVersion Function Definition
\******************************************************************************/
/**
 *
 *  @brief    This Function performs OMX_GetComponentVersion API testing.
 *
 *  @param    Pointer to MX_DBG_CMD_CONTEXT_T structure
 *            Pointer to MX_DBG_CMD_Entry_T structure
 *            Character Double Pointer containing the command
 *
 *  @return   ERR_NOERR           successful,
 *            ERR_END_OF_CMD      help was requested,
 *            ERR_INVNAME         otherwise.
 */

MX_Result
OMTB_OmxGetCompVersionNullCompVersion(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine
)
{
  MX_Result  result = ERR_NOERR;
  OMX_ERRORTYPE err = OMX_ErrorNone;
  char componentRequested[OMTB_MAX_LEN] = {"\0"};
  char resultFileName[OMTB_MAX_LEN] = {"\0"};
  char fOpenMode[OMTB_MAX_LEN] = {"\0"};
  char testCaseId[OMTB_MAX_LEN] = {"\0"};
  char testCaseResult[OMTB_MAX_LEN] = {"\0"}; char returnString[OMTB_MAX_LEN] = {"\0"};
  FILE *fpResult = NULL;
  OMX_HANDLETYPE handle = NULL;                  /* Component handle */
  char component[OMX_MAX_STRINGNAME_SIZE] = {"\0"};
  OMX_VERSIONTYPE pSpecVersion;
  OMX_UUIDTYPE pComponentUUID;
  OMTB_OMX_API_TIMING_VAR_DECL;

  /* Read testcase ID */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, testCaseId);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }
  
  /* Read component name */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, componentRequested);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }

  /* Read result filename */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, resultFileName);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }

  /* Read result file type */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, fOpenMode);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }

  /* Open the result file */
  fpResult = fopen(resultFileName, fOpenMode);

  if(NULL == fpResult)
  {
    PRINT(PRINT_ERR_MSG, "%s: Error in result file open\n", __FUNCTION__);
    fprintf(fpResult, "%s : Error in result file open\n", testCaseId);
    return ERR_INVNAME;
  }

  /* OpenMax insufficient resources */
    
  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;

  err = OMX_Init ();

  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_Init");

  if(OMX_ErrorNone != err)
  {
    OMTB_OmxReturnStatusString(err, returnString);
    strcpy(testCaseResult, "FAIL - Error in OMX_Init()\n");
    fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
    fclose(fpResult);
    return ERR_INVNAME;
  }

  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;
  
  /* get component handle */
  err = OMX_GetHandle(&handle,
                      (OMX_STRING)componentRequested,
                      NULL,
                      &OMTB_APITestCallback);
  
  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_GetHandle");

  if(OMX_ErrorNone != err)
  {
      OMTB_OmxReturnStatusString(err, returnString);
      strcpy(testCaseResult, "FAIL - Error in OMX_GetHandle()\n");
      fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);

    /* API entry time calculation macro */
    OMTB_OMX_API_ENTRY_TIME_CALC;

    /* OpenMax core uninitialization */
    err = OMX_Deinit ();

    /* API exit time calculation macro */
    OMTB_OMX_API_EXIT_TIME_CALC("OMX_Deinit");
    
    if(OMX_ErrorNone != err)
    {
      OMTB_OmxReturnStatusString(err, returnString);
      strcpy(testCaseResult, "FAIL - Error in OMX_Deinit()\n");
      fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
      result = ERR_INVNAME;
    }
    
    fclose(fpResult);
    return ERR_INVNAME;
  }

  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;
  
  /* Get the component version number */
  err = OMX_GetComponentVersion(handle,
                                component,
                                NULL,
                                &pSpecVersion,
                                &pComponentUUID);

  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_GetComponentVersion");

  if(OMX_ErrorBadParameter == err)
  {
    strcpy(testCaseResult, "PASS");
    fprintf(fpResult, "%s : %s\n", testCaseId, testCaseResult);
  }
  else
  {
    OMTB_OmxReturnStatusString(err, returnString);
    strcpy(testCaseResult, "FAIL");
    fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
    result = ERR_INVNAME;
  }
  
  /* free component handle */
  if(NULL != handle)
  {
    /* API entry time calculation macro */
    OMTB_OMX_API_ENTRY_TIME_CALC;
    
    err = OMX_FreeHandle(handle);
    
    /* API exit time calculation macro */
    OMTB_OMX_API_EXIT_TIME_CALC("OMX_FreeHandle");
    
    if(OMX_ErrorNone != err)
    {
	OMTB_OmxReturnStatusString(err, returnString);
    strcpy(testCaseResult, "FAIL - Error in OMX_FreeHandle()\n");
    fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);

      result = ERR_INVNAME;
    }
    
  }

  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;
  
  /* OpenMax core uninitialization */
  err = OMX_Deinit ();

  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_Deinit");

    if(OMX_ErrorNone != err)
    {
      OMTB_OmxReturnStatusString(err, returnString);
      strcpy(testCaseResult, "FAIL - Error in OMX_Deinit()\n");
      fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
      result = ERR_INVNAME;
    }

  /* close the result file */
  fclose(fpResult);
  
  return (result);
}


/******************************************************************************\
 *      OMTB_OmxGetCompVersionNullSpecVersion Function Definition
\******************************************************************************/
/**
 *
 *  @brief    This Function performs OMX_GetComponentVersion API testing.
 *
 *  @param    Pointer to MX_DBG_CMD_CONTEXT_T structure
 *            Pointer to MX_DBG_CMD_Entry_T structure
 *            Character Double Pointer containing the command
 *
 *  @return   ERR_NOERR           successful,
 *            ERR_END_OF_CMD      help was requested,
 *            ERR_INVNAME         otherwise.
 */

MX_Result
OMTB_OmxGetCompVersionNullSpecVersion(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine
)
{
  MX_Result  result = ERR_NOERR;
  OMX_ERRORTYPE err = OMX_ErrorNone;
  char componentRequested[OMTB_MAX_LEN] = {"\0"};
  char resultFileName[OMTB_MAX_LEN] = {"\0"};
  char fOpenMode[OMTB_MAX_LEN] = {"\0"};
  char testCaseId[OMTB_MAX_LEN] = {"\0"};
  char testCaseResult[OMTB_MAX_LEN] = {"\0"}; char returnString[OMTB_MAX_LEN] = {"\0"};
  FILE *fpResult = NULL;
  OMX_HANDLETYPE handle = NULL;                  /* Component handle */
  char component[OMX_MAX_STRINGNAME_SIZE] = {"\0"};
  OMX_VERSIONTYPE pComponentVersion;
  OMX_UUIDTYPE pComponentUUID;
  OMTB_OMX_API_TIMING_VAR_DECL;

  /* Read testcase ID */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, testCaseId);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }
  
  /* Read component name */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, componentRequested);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }

  /* Read result filename */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, resultFileName);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }

  /* Read result file type */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, fOpenMode);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }

  /* Open the result file */
  fpResult = fopen(resultFileName, fOpenMode);

  if(NULL == fpResult)
  {
    PRINT(PRINT_ERR_MSG, "%s: Error in result file open\n", __FUNCTION__);
    fprintf(fpResult, "%s : Error in result file open\n", testCaseId);
    return ERR_INVNAME;
  }

  /* OpenMax insufficient resources */
    
  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;

  err = OMX_Init ();

  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_Init");

  if(OMX_ErrorNone != err)
  {
    OMTB_OmxReturnStatusString(err, returnString);
    strcpy(testCaseResult, "FAIL - Error in OMX_Init()\n");
    fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
    fclose(fpResult);
    return ERR_INVNAME;
  }

  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;
  
  /* get component handle */
  err = OMX_GetHandle(&handle,
                      (OMX_STRING)componentRequested,
                      NULL,
                      &OMTB_APITestCallback);
  
  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_GetHandle");

  if(OMX_ErrorNone != err)
  {
      OMTB_OmxReturnStatusString(err, returnString);
      strcpy(testCaseResult, "FAIL - Error in OMX_GetHandle()\n");
      fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);

    /* API entry time calculation macro */
    OMTB_OMX_API_ENTRY_TIME_CALC;

    /* OpenMax core uninitialization */
    err = OMX_Deinit ();

    /* API exit time calculation macro */
    OMTB_OMX_API_EXIT_TIME_CALC("OMX_Deinit");
    
    if(OMX_ErrorNone != err)
    {
      OMTB_OmxReturnStatusString(err, returnString);
      strcpy(testCaseResult, "FAIL - Error in OMX_Deinit()\n");
      fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
      result = ERR_INVNAME;
    }
    
    fclose(fpResult);
    return ERR_INVNAME;
  }

  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;
  
  /* Get the component version number */
  err = OMX_GetComponentVersion(handle,
                                component,
                                &pComponentVersion,
                                NULL,
                                &pComponentUUID);

  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_GetComponentVersion");

  if(OMX_ErrorBadParameter == err)
  {
    strcpy(testCaseResult, "PASS");
    fprintf(fpResult, "%s : %s\n", testCaseId, testCaseResult);
  }
  else
  {
    OMTB_OmxReturnStatusString(err, returnString);
    strcpy(testCaseResult, "FAIL");
    fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
    result = ERR_INVNAME;
  }
  
  /* free component handle */
  if(NULL != handle)
  {
    /* API entry time calculation macro */
    OMTB_OMX_API_ENTRY_TIME_CALC;
    
    err = OMX_FreeHandle(handle);
    
    /* API exit time calculation macro */
    OMTB_OMX_API_EXIT_TIME_CALC("OMX_FreeHandle");
    
    if(OMX_ErrorNone != err)
    {
	OMTB_OmxReturnStatusString(err, returnString);
    strcpy(testCaseResult, "FAIL - Error in OMX_FreeHandle()\n");
    fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);

      result = ERR_INVNAME;
    }
    
  }

  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;
  
  /* OpenMax core uninitialization */
  err = OMX_Deinit ();

  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_Deinit");

    if(OMX_ErrorNone != err)
    {
      OMTB_OmxReturnStatusString(err, returnString);
      strcpy(testCaseResult, "FAIL - Error in OMX_Deinit()\n");
      fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
      result = ERR_INVNAME;
    }

  /* close the result file */
  fclose(fpResult);
  
  return (result);
}


/******************************************************************************\
 *      OMTB_OmxGetCompVersionVerMismatch Function Definition
\******************************************************************************/
/**
 *
 *  @brief    This Function performs OMX_GetComponentVersion API testing.
 *
 *  @param    Pointer to MX_DBG_CMD_CONTEXT_T structure
 *            Pointer to MX_DBG_CMD_Entry_T structure
 *            Character Double Pointer containing the command
 *
 *  @return   ERR_NOERR           successful,
 *            ERR_END_OF_CMD      help was requested,
 *            ERR_INVNAME         otherwise.
 */

MX_Result
OMTB_OmxGetCompVersionVerMismatch(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine
)
{
  MX_Result  result = ERR_NOERR;
  OMX_ERRORTYPE err = OMX_ErrorNone;
  char componentRequested[OMTB_MAX_LEN] = {"\0"};
  char resultFileName[OMTB_MAX_LEN] = {"\0"};
  char fOpenMode[OMTB_MAX_LEN] = {"\0"};
  char testCaseId[OMTB_MAX_LEN] = {"\0"};
  char testCaseResult[OMTB_MAX_LEN] = {"\0"}; char returnString[OMTB_MAX_LEN] = {"\0"};
  FILE *fpResult = NULL;
  OMX_HANDLETYPE handle = NULL;                  /* Component handle */
  char component[OMX_MAX_STRINGNAME_SIZE] = {"\0"};
  OMX_VERSIONTYPE pComponentVersion;
  OMX_VERSIONTYPE pSpecVersion;
  OMX_UUIDTYPE pComponentUUID;
  OMTB_OMX_API_TIMING_VAR_DECL;

  /* Read testcase ID */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, testCaseId);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }
  
  /* Read component name */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, componentRequested);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }

  /* Read result filename */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, resultFileName);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }

  /* Read result file type */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, fOpenMode);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }

  /* Open the result file */
  fpResult = fopen(resultFileName, fOpenMode);

  if(NULL == fpResult)
  {
    PRINT(PRINT_ERR_MSG, "%s: Error in result file open\n", __FUNCTION__);
    fprintf(fpResult, "%s : Error in result file open\n", testCaseId);
    return ERR_INVNAME;
  }

  /* OpenMax insufficient resources */
    
  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;

  err = OMX_Init ();

  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_Init");

  if(OMX_ErrorNone != err)
  {
    OMTB_OmxReturnStatusString(err, returnString);
    strcpy(testCaseResult, "FAIL - Error in OMX_Init()\n");
    fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
    fclose(fpResult);
    return ERR_INVNAME;
  }

  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;
  
  /* get component handle */
  err = OMX_GetHandle(&handle,
                      (OMX_STRING)componentRequested,
                      NULL,
                      &OMTB_APITestCallback);
  
  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_GetHandle");

  if(OMX_ErrorNone != err)
  {
      OMTB_OmxReturnStatusString(err, returnString);
      strcpy(testCaseResult, "FAIL - Error in OMX_GetHandle()\n");
      fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);

    /* API entry time calculation macro */
    OMTB_OMX_API_ENTRY_TIME_CALC;

    /* OpenMax core uninitialization */
    err = OMX_Deinit ();

    /* API exit time calculation macro */
    OMTB_OMX_API_EXIT_TIME_CALC("OMX_Deinit");
    
    if(OMX_ErrorNone != err)
    {
      OMTB_OmxReturnStatusString(err, returnString);
      strcpy(testCaseResult, "FAIL - Error in OMX_Deinit()\n");
      fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
      result = ERR_INVNAME;
    }
    
    fclose(fpResult);
    return ERR_INVNAME;
  }

  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;
  
  /* Get the component version number */
  err = OMX_GetComponentVersion(handle,
                                component,
                                &pComponentVersion,
                                &pSpecVersion,
                                &pComponentUUID);

  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_GetComponentVersion");

  if(OMX_ErrorVersionMismatch == err)
  {
    strcpy(testCaseResult, "PASS");
    fprintf(fpResult, "%s : %s\n", testCaseId, testCaseResult);
  }
  else
  {
    OMTB_OmxReturnStatusString(err, returnString);
    strcpy(testCaseResult, "FAIL");
    fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
    result = ERR_INVNAME;
  }
  
  /* free component handle */
  if(NULL != handle)
  {
    /* API entry time calculation macro */
    OMTB_OMX_API_ENTRY_TIME_CALC;
    
    err = OMX_FreeHandle(handle);
    
    /* API exit time calculation macro */
    OMTB_OMX_API_EXIT_TIME_CALC("OMX_FreeHandle");
    
    if(OMX_ErrorNone != err)
    {
	OMTB_OmxReturnStatusString(err, returnString);
    strcpy(testCaseResult, "FAIL - Error in OMX_FreeHandle()\n");
    fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);

      result = ERR_INVNAME;
    }
    
  }

  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;
  
  /* OpenMax core uninitialization */
  err = OMX_Deinit ();

  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_Deinit");

    if(OMX_ErrorNone != err)
    {
      OMTB_OmxReturnStatusString(err, returnString);
      strcpy(testCaseResult, "FAIL - Error in OMX_Deinit()\n");
      fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
      result = ERR_INVNAME;
    }

  /* close the result file */
  fclose(fpResult);
  
  return (result);
}


/******************************************************************************\
 *      OMTB_OmxGetStateOnce Function Definition
\******************************************************************************/
/**
 *
 *  @brief    This Function performs OMX_GetState API testing.
 *
 *  @param    Pointer to MX_DBG_CMD_CONTEXT_T structure
 *            Pointer to MX_DBG_CMD_Entry_T structure
 *            Character Double Pointer containing the command
 *
 *  @return   ERR_NOERR           successful,
 *            ERR_END_OF_CMD      help was requested,
 *            ERR_INVNAME         otherwise.
 */

MX_Result
OMTB_OmxGetStateOnce(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine
)
{
  MX_Result  result = ERR_NOERR;
  OMX_ERRORTYPE err = OMX_ErrorNone;
  char componentRequested[OMTB_MAX_LEN] = {"\0"};
  char resultFileName[OMTB_MAX_LEN] = {"\0"};
  char fOpenMode[OMTB_MAX_LEN] = {"\0"};
  char testCaseId[OMTB_MAX_LEN] = {"\0"};
  char testCaseResult[OMTB_MAX_LEN] = {"\0"}; char returnString[OMTB_MAX_LEN] = {"\0"};
  FILE *fpResult = NULL;
  OMX_HANDLETYPE handle = NULL;                  /* Component handle */
  OMX_STATETYPE pState = OMX_StateInvalid;
  OMTB_OMX_API_TIMING_VAR_DECL;

  /* Read testcase ID */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, testCaseId);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }
  
  /* Read component name */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, componentRequested);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }

  /* Read result filename */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, resultFileName);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }

  /* Read result file type */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, fOpenMode);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }

  /* Open the result file */
  fpResult = fopen(resultFileName, fOpenMode);

  if(NULL == fpResult)
  {
    PRINT(PRINT_ERR_MSG, "%s: Error in result file open\n", __FUNCTION__);
    fprintf(fpResult, "%s : Error in result file open\n", testCaseId);
    return ERR_INVNAME;
  }

  /* OpenMax insufficient resources */
    
  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;

  err = OMX_Init ();

  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_Init");

  if(OMX_ErrorNone != err)
  {
    OMTB_OmxReturnStatusString(err, returnString);
    strcpy(testCaseResult, "FAIL - Error in OMX_Init()\n");
    fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
    fclose(fpResult);
    return ERR_INVNAME;
  }

  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;
  
  /* get component handle */
  err = OMX_GetHandle(&handle,
                      (OMX_STRING)componentRequested,
                      NULL,
                      &OMTB_APITestCallback);
  
  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_GetHandle");

  if(OMX_ErrorNone != err)
  {
    OMTB_OmxReturnStatusString(err, returnString);
    strcpy(testCaseResult, "FAIL - Error in OMX_GetHandle()\n");
    fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);

    /* API entry time calculation macro */
    OMTB_OMX_API_ENTRY_TIME_CALC;

    /* OpenMax core uninitialization */
    err = OMX_Deinit ();

    /* API exit time calculation macro */
    OMTB_OMX_API_EXIT_TIME_CALC("OMX_Deinit");
    
    if(OMX_ErrorNone != err)
    {
      OMTB_OmxReturnStatusString(err, returnString);
      strcpy(testCaseResult, "FAIL - Error in OMX_Deinit()\n");
      fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
      result = ERR_INVNAME;
    }
    
    fclose(fpResult);
    return ERR_INVNAME;
  }

  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;

  /* Get the current state of the component */
  err = OMX_GetState(handle, &pState);

  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_GetState");
  
  if(OMX_ErrorNone == err)
  {
    strcpy(testCaseResult, "PASS");
    fprintf(fpResult, "%s : %s\n", testCaseId, testCaseResult);
  }
  else
  {
    OMTB_OmxReturnStatusString(err, returnString);
    strcpy(testCaseResult, "FAIL");
    fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
    result = ERR_INVNAME;
  }
  
  /* free component handle */
  if(NULL != handle)
  {
    /* API entry time calculation macro */
    OMTB_OMX_API_ENTRY_TIME_CALC;
    
    err = OMX_FreeHandle(handle);
    
    /* API exit time calculation macro */
    OMTB_OMX_API_EXIT_TIME_CALC("OMX_FreeHandle");
    
    if(OMX_ErrorNone != err)
    {
	OMTB_OmxReturnStatusString(err, returnString);
    strcpy(testCaseResult, "FAIL - Error in OMX_FreeHandle()\n");
    fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);

      result = ERR_INVNAME;
    }
    
  }

  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;
  
  /* OpenMax core uninitialization */
  err = OMX_Deinit ();

  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_Deinit");

    if(OMX_ErrorNone != err)
    {
      OMTB_OmxReturnStatusString(err, returnString);
      strcpy(testCaseResult, "FAIL - Error in OMX_Deinit()\n");
      fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
      result = ERR_INVNAME;
    }

  /* close the result file */
  fclose(fpResult);
  
  return (result);
}


/******************************************************************************\
 *      OMTB_OmxGetStateNullHandle Function Definition
\******************************************************************************/
/**
 *
 *  @brief    This Function performs OMX_GetState API testing.
 *
 *  @param    Pointer to MX_DBG_CMD_CONTEXT_T structure
 *            Pointer to MX_DBG_CMD_Entry_T structure
 *            Character Double Pointer containing the command
 *
 *  @return   ERR_NOERR           successful,
 *            ERR_END_OF_CMD      help was requested,
 *            ERR_INVNAME         otherwise.
 */

MX_Result
OMTB_OmxGetStateNullHandle(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine
)
{
  MX_Result  result = ERR_NOERR;
  OMX_ERRORTYPE err = OMX_ErrorNone;
  char componentRequested[OMTB_MAX_LEN] = {"\0"};
  char resultFileName[OMTB_MAX_LEN] = {"\0"};
  char fOpenMode[OMTB_MAX_LEN] = {"\0"};
  char testCaseId[OMTB_MAX_LEN] = {"\0"};
  char testCaseResult[OMTB_MAX_LEN] = {"\0"}; char returnString[OMTB_MAX_LEN] = {"\0"};
  FILE *fpResult = NULL;
  OMX_HANDLETYPE handle = NULL;                  /* Component handle */
  OMX_STATETYPE pState = OMX_StateInvalid;
  OMTB_OMX_API_TIMING_VAR_DECL;

  /* Read testcase ID */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, testCaseId);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }
  
  /* Read component name */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, componentRequested);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }

  /* Read result filename */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, resultFileName);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }

  /* Read result file type */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, fOpenMode);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }

  /* Open the result file */
  fpResult = fopen(resultFileName, fOpenMode);

  if(NULL == fpResult)
  {
    PRINT(PRINT_ERR_MSG, "%s: Error in result file open\n", __FUNCTION__);
    fprintf(fpResult, "%s : Error in result file open\n", testCaseId);
    return ERR_INVNAME;
  }

  /* OpenMax insufficient resources */
    
  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;

  err = OMX_Init ();

  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_Init");

  if(OMX_ErrorNone != err)
  {
    OMTB_OmxReturnStatusString(err, returnString);
    strcpy(testCaseResult, "FAIL - Error in OMX_Init()\n");
    fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
    fclose(fpResult);
    return ERR_INVNAME;
  }

  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;
  
  /* get component handle */
  err = OMX_GetHandle(&handle,
                      (OMX_STRING)componentRequested,
                      NULL,
                      &OMTB_APITestCallback);
  
  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_GetHandle");

  if(OMX_ErrorNone != err)
  {
    OMTB_OmxReturnStatusString(err, returnString);
    strcpy(testCaseResult, "FAIL - Error in OMX_GetHandle()\n");
    fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);

    /* API entry time calculation macro */
    OMTB_OMX_API_ENTRY_TIME_CALC;

    /* OpenMax core uninitialization */
    err = OMX_Deinit ();

    /* API exit time calculation macro */
    OMTB_OMX_API_EXIT_TIME_CALC("OMX_Deinit");
    
    if(OMX_ErrorNone != err)
    {
      OMTB_OmxReturnStatusString(err, returnString);
      strcpy(testCaseResult, "FAIL - Error in OMX_Deinit()\n");
      fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
      result = ERR_INVNAME;
    }
    
    fclose(fpResult);
    return ERR_INVNAME;
  }

  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;

  /* Get the current state of the component */
  err = OMX_GetState(NULL, &pState);

  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_GetState");
  
  if(OMX_ErrorBadParameter == err)
  {
    strcpy(testCaseResult, "PASS");
    fprintf(fpResult, "%s : %s\n", testCaseId, testCaseResult);
  }
  else
  {
    OMTB_OmxReturnStatusString(err, returnString);
    strcpy(testCaseResult, "FAIL");
    fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
    result = ERR_INVNAME;
  }
  
  /* free component handle */
  if(NULL != handle)
  {
    /* API entry time calculation macro */
    OMTB_OMX_API_ENTRY_TIME_CALC;
    
    err = OMX_FreeHandle(handle);
    
    /* API exit time calculation macro */
    OMTB_OMX_API_EXIT_TIME_CALC("OMX_FreeHandle");
    
    if(OMX_ErrorNone != err)
    {
	OMTB_OmxReturnStatusString(err, returnString);
    strcpy(testCaseResult, "FAIL - Error in OMX_FreeHandle()\n");
    fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);

      result = ERR_INVNAME;
    }
    
  }

  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;
  
  /* OpenMax core uninitialization */
  err = OMX_Deinit ();

  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_Deinit");

    if(OMX_ErrorNone != err)
    {
      OMTB_OmxReturnStatusString(err, returnString);
      strcpy(testCaseResult, "FAIL - Error in OMX_Deinit()\n");
      fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
      result = ERR_INVNAME;
    }

  /* close the result file */
  fclose(fpResult);
  
  return (result);
}


/******************************************************************************\
 *      OMTB_OmxGetStateVerMismatch Function Definition
\******************************************************************************/
/**
 *
 *  @brief    This Function performs OMX_GetState API testing.
 *
 *  @param    Pointer to MX_DBG_CMD_CONTEXT_T structure
 *            Pointer to MX_DBG_CMD_Entry_T structure
 *            Character Double Pointer containing the command
 *
 *  @return   ERR_NOERR           successful,
 *            ERR_END_OF_CMD      help was requested,
 *            ERR_INVNAME         otherwise.
 */

MX_Result
OMTB_OmxGetStateVerMismatch(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine
)
{
  MX_Result  result = ERR_NOERR;
  OMX_ERRORTYPE err = OMX_ErrorNone;
  char componentRequested[OMTB_MAX_LEN] = {"\0"};
  char resultFileName[OMTB_MAX_LEN] = {"\0"};
  char fOpenMode[OMTB_MAX_LEN] = {"\0"};
  char testCaseId[OMTB_MAX_LEN] = {"\0"};
  char testCaseResult[OMTB_MAX_LEN] = {"\0"}; char returnString[OMTB_MAX_LEN] = {"\0"};
  FILE *fpResult = NULL;
  OMX_HANDLETYPE handle = NULL;                  /* Component handle */
  OMX_STATETYPE pState = OMX_StateInvalid;
  OMTB_OMX_API_TIMING_VAR_DECL;

  /* Read testcase ID */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, testCaseId);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }
  
  /* Read component name */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, componentRequested);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }

  /* Read result filename */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, resultFileName);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }

  /* Read result file type */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, fOpenMode);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }

  /* Open the result file */
  fpResult = fopen(resultFileName, fOpenMode);

  if(NULL == fpResult)
  {
    PRINT(PRINT_ERR_MSG, "%s: Error in result file open\n", __FUNCTION__);
    fprintf(fpResult, "%s : Error in result file open\n", testCaseId);
    return ERR_INVNAME;
  }

  /* OpenMax insufficient resources */
    
  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;

  err = OMX_Init ();

  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_Init");

  if(OMX_ErrorNone != err)
  {
    OMTB_OmxReturnStatusString(err, returnString);
    strcpy(testCaseResult, "FAIL - Error in OMX_Init()\n");
    fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
    fclose(fpResult);
    return ERR_INVNAME;
  }

  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;
  
  /* get component handle */
  err = OMX_GetHandle(&handle,
                      (OMX_STRING)componentRequested,
                      NULL,
                      &OMTB_APITestCallback);
  
  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_GetHandle");

  if(OMX_ErrorNone != err)
  {
    OMTB_OmxReturnStatusString(err, returnString);
    strcpy(testCaseResult, "FAIL - Error in OMX_GetHandle()\n");
    fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);

    /* API entry time calculation macro */
    OMTB_OMX_API_ENTRY_TIME_CALC;

    /* OpenMax core uninitialization */
    err = OMX_Deinit ();

    /* API exit time calculation macro */
    OMTB_OMX_API_EXIT_TIME_CALC("OMX_Deinit");
    
    if(OMX_ErrorNone != err)
    {
      OMTB_OmxReturnStatusString(err, returnString);
      strcpy(testCaseResult, "FAIL - Error in OMX_Deinit()\n");
      fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
      result = ERR_INVNAME;
    }
    
    fclose(fpResult);
    return ERR_INVNAME;
  }

  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;

  /* Get the current state of the component */
  err = OMX_GetState(handle, &pState);

  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_GetState");
  
  if(OMX_ErrorVersionMismatch == err)
  {
    strcpy(testCaseResult, "PASS");
    fprintf(fpResult, "%s : %s\n", testCaseId, testCaseResult);
  }
  else
  {
    OMTB_OmxReturnStatusString(err, returnString);
    strcpy(testCaseResult, "FAIL");
    fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
    result = ERR_INVNAME;
  }
  
  /* free component handle */
  if(NULL != handle)
  {
    /* API entry time calculation macro */
    OMTB_OMX_API_ENTRY_TIME_CALC;
    
    err = OMX_FreeHandle(handle);
    
    /* API exit time calculation macro */
    OMTB_OMX_API_EXIT_TIME_CALC("OMX_FreeHandle");
    
    if(OMX_ErrorNone != err)
    {
	OMTB_OmxReturnStatusString(err, returnString);
    strcpy(testCaseResult, "FAIL - Error in OMX_FreeHandle()\n");
    fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);

      result = ERR_INVNAME;
    }
    
  }

  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;
  
  /* OpenMax core uninitialization */
  err = OMX_Deinit ();

  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_Deinit");

    if(OMX_ErrorNone != err)
    {
      OMTB_OmxReturnStatusString(err, returnString);
      strcpy(testCaseResult, "FAIL - Error in OMX_Deinit()\n");
      fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
      result = ERR_INVNAME;
    }

  /* close the result file */
  fclose(fpResult);
  
  return (result);
}


/******************************************************************************\
 *      OMTB_OmxGetStateTimeOut Function Definition
\******************************************************************************/
/**
 *
 *  @brief    This Function performs OMX_GetState API testing.
 *
 *  @param    Pointer to MX_DBG_CMD_CONTEXT_T structure
 *            Pointer to MX_DBG_CMD_Entry_T structure
 *            Character Double Pointer containing the command
 *
 *  @return   ERR_NOERR           successful,
 *            ERR_END_OF_CMD      help was requested,
 *            ERR_INVNAME         otherwise.
 */

MX_Result
OMTB_OmxGetStateTimeOut(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine
)
{
  MX_Result  result = ERR_NOERR;
  OMX_ERRORTYPE err = OMX_ErrorNone;
  char componentRequested[OMTB_MAX_LEN] = {"\0"};
  char resultFileName[OMTB_MAX_LEN] = {"\0"};
  char fOpenMode[OMTB_MAX_LEN] = {"\0"};
  char testCaseId[OMTB_MAX_LEN] = {"\0"};
  char testCaseResult[OMTB_MAX_LEN] = {"\0"}; char returnString[OMTB_MAX_LEN] = {"\0"};
  FILE *fpResult = NULL;
  OMX_HANDLETYPE handle = NULL;                  /* Component handle */
  OMX_STATETYPE pState = OMX_StateInvalid;
  OMTB_OMX_API_TIMING_VAR_DECL;

  /* Read testcase ID */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, testCaseId);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }
  
  /* Read component name */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, componentRequested);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }

  /* Read result filename */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, resultFileName);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }

  /* Read result file type */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, fOpenMode);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }

  /* Open the result file */
  fpResult = fopen(resultFileName, fOpenMode);

  if(NULL == fpResult)
  {
    PRINT(PRINT_ERR_MSG, "%s: Error in result file open\n", __FUNCTION__);
    fprintf(fpResult, "%s : Error in result file open\n", testCaseId);
    return ERR_INVNAME;
  }

  /* OpenMax insufficient resources */
    
  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;

  err = OMX_Init ();

  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_Init");

  if(OMX_ErrorNone != err)
  {
    OMTB_OmxReturnStatusString(err, returnString);
    strcpy(testCaseResult, "FAIL - Error in OMX_Init()\n");
    fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
    fclose(fpResult);
    return ERR_INVNAME;
  }

  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;
  
  /* get component handle */
  err = OMX_GetHandle(&handle,
                      (OMX_STRING)componentRequested,
                      NULL,
                      &OMTB_APITestCallback);
  
  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_GetHandle");

  if(OMX_ErrorNone != err)
  {
    OMTB_OmxReturnStatusString(err, returnString);
    strcpy(testCaseResult, "FAIL - Error in OMX_GetHandle()\n");
    fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);

    /* API entry time calculation macro */
    OMTB_OMX_API_ENTRY_TIME_CALC;

    /* OpenMax core uninitialization */
    err = OMX_Deinit ();

    /* API exit time calculation macro */
    OMTB_OMX_API_EXIT_TIME_CALC("OMX_Deinit");
    
    if(OMX_ErrorNone != err)
    {
      OMTB_OmxReturnStatusString(err, returnString);
      strcpy(testCaseResult, "FAIL - Error in OMX_Deinit()\n");
      fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
      result = ERR_INVNAME;
    }
    
    fclose(fpResult);
    return ERR_INVNAME;
  }

  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;

  /* Get the current state of the component */
  err = OMX_GetState(handle, &pState);

  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_GetState");
  
  if(OMX_ErrorTimeout == err)
  {
    strcpy(testCaseResult, "PASS");
    fprintf(fpResult, "%s : %s\n", testCaseId, testCaseResult);
  }
  else
  {
    OMTB_OmxReturnStatusString(err, returnString);
    strcpy(testCaseResult, "FAIL");
    fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
    result = ERR_INVNAME;
  }
  
  /* free component handle */
  if(NULL != handle)
  {
    /* API entry time calculation macro */
    OMTB_OMX_API_ENTRY_TIME_CALC;
    
    err = OMX_FreeHandle(handle);
    
    /* API exit time calculation macro */
    OMTB_OMX_API_EXIT_TIME_CALC("OMX_FreeHandle");
    
    if(OMX_ErrorNone != err)
    {
	OMTB_OmxReturnStatusString(err, returnString);
    strcpy(testCaseResult, "FAIL - Error in OMX_FreeHandle()\n");
    fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);

      result = ERR_INVNAME;
    }
    
  }

  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;
  
  /* OpenMax core uninitialization */
  err = OMX_Deinit ();

  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_Deinit");

    if(OMX_ErrorNone != err)
    {
      OMTB_OmxReturnStatusString(err, returnString);
      strcpy(testCaseResult, "FAIL - Error in OMX_Deinit()\n");
      fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
      result = ERR_INVNAME;
    }

  /* close the result file */
  fclose(fpResult);
  
  return (result);
}


/******************************************************************************\
 *      OMTB_OmxGetExtensionIndexOnce Function Definition
\******************************************************************************/
/**
 *
 *  @brief    This Function performs OMX_GetExtensionIndex API testing.
 *
 *  @param    Pointer to MX_DBG_CMD_CONTEXT_T structure
 *            Pointer to MX_DBG_CMD_Entry_T structure
 *            Character Double Pointer containing the command
 *
 *  @return   ERR_NOERR           successful,
 *            ERR_END_OF_CMD      help was requested,
 *            ERR_INVNAME         otherwise.
 */
  
MX_Result
OMTB_OmxGetExtensionIndexOnce(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine
)
{
  MX_Result  result = ERR_NOERR;
  OMX_ERRORTYPE err = OMX_ErrorNone;
  char componentRequested[OMTB_MAX_LEN] = {"\0"};
  char resultFileName[OMTB_MAX_LEN] = {"\0"};
  char fOpenMode[OMTB_MAX_LEN] = {"\0"};
  char testCaseId[OMTB_MAX_LEN] = {"\0"};
  char testCaseResult[OMTB_MAX_LEN] = {"\0"}; char returnString[OMTB_MAX_LEN] = {"\0"};
  FILE *fpResult = NULL;
  OMX_HANDLETYPE handle = NULL;                  /* Component handle */
  char vendorSpecificStr[OMX_MAX_STRINGNAME_SIZE]  = {"\0"};
  OMX_INDEXTYPE pIndex = OMX_IndexMax;
  OMTB_OMX_API_TIMING_VAR_DECL;

  /* Read testcase ID */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, testCaseId);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }
  
  /* Read component name */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, componentRequested);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }

  /* Read result filename */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, resultFileName);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }

  /* Read result file type */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, fOpenMode);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }

  /* Read vendor specific string */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, vendorSpecificStr);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }

  /* Open the result file */
  fpResult = fopen(resultFileName, fOpenMode);

  if(NULL == fpResult)
  {
    PRINT(PRINT_ERR_MSG, "%s: Error in result file open\n", __FUNCTION__);
    fprintf(fpResult, "%s : Error in result file open\n", testCaseId);
    return ERR_INVNAME;
  }

  /* OpenMax insufficient resources */
    
  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;

  err = OMX_Init ();

  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_Init");

  if(OMX_ErrorNone != err)
  {
    OMTB_OmxReturnStatusString(err, returnString);
    strcpy(testCaseResult, "FAIL - Error in OMX_Init()\n");
    fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
    fclose(fpResult);
    return ERR_INVNAME;
  }

  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;
  
  /* get component handle */
  err = OMX_GetHandle(&handle,
                      (OMX_STRING)componentRequested,
                      NULL,
                      &OMTB_APITestCallback);
  
  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_GetHandle");

  if(OMX_ErrorNone != err)
  {
    OMTB_OmxReturnStatusString(err, returnString);
    strcpy(testCaseResult, "FAIL - Error in OMX_GetHandle()\n");
    fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);

    /* API entry time calculation macro */
    OMTB_OMX_API_ENTRY_TIME_CALC;

    /* OpenMax core uninitialization */
    err = OMX_Deinit ();

    /* API exit time calculation macro */
    OMTB_OMX_API_EXIT_TIME_CALC("OMX_Deinit");
    
    if(OMX_ErrorNone != err)
    {
      OMTB_OmxReturnStatusString(err, returnString);
      strcpy(testCaseResult, "FAIL - Error in OMX_Deinit()\n");
      fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
      result = ERR_INVNAME;
    }
    
    fclose(fpResult);
    return ERR_INVNAME;
  }


  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;

  /* Fet the extension index for the vendor specific structure string */
  err = OMX_GetExtensionIndex(handle, vendorSpecificStr, &pIndex);

  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_GetExtensionIndex");

  if(OMX_ErrorNone == err)
  {
    strcpy(testCaseResult, "PASS");
    fprintf(fpResult, "%s : %s\n", testCaseId, testCaseResult);
  }
  else
  {
    OMTB_OmxReturnStatusString(err, returnString);
    strcpy(testCaseResult, "FAIL");
    fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
    result = ERR_INVNAME;
  }
  
  /* free component handle */
  if(NULL != handle)
  {
    /* API entry time calculation macro */
    OMTB_OMX_API_ENTRY_TIME_CALC;
    
    err = OMX_FreeHandle(handle);
    
    /* API exit time calculation macro */
    OMTB_OMX_API_EXIT_TIME_CALC("OMX_FreeHandle");
    
    if(OMX_ErrorNone != err)
    {
	OMTB_OmxReturnStatusString(err, returnString);
    strcpy(testCaseResult, "FAIL - Error in OMX_FreeHandle()\n");
    fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);

      result = ERR_INVNAME;
    }
    
  }

  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;
  
  /* OpenMax core uninitialization */
  err = OMX_Deinit ();

  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_Deinit");

    if(OMX_ErrorNone != err)
    {
      OMTB_OmxReturnStatusString(err, returnString);
      strcpy(testCaseResult, "FAIL - Error in OMX_Deinit()\n");
      fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
      result = ERR_INVNAME;
    }

  /* close the result file */
  fclose(fpResult);
  
  return (result);
}


/******************************************************************************\
 *      OMTB_OmxGetExtensionIndexNullHandle Function Definition
\******************************************************************************/
/**
 *
 *  @brief    This Function performs OMX_GetExtensionIndex API testing.
 *
 *  @param    Pointer to MX_DBG_CMD_CONTEXT_T structure
 *            Pointer to MX_DBG_CMD_Entry_T structure
 *            Character Double Pointer containing the command
 *
 *  @return   ERR_NOERR           successful,
 *            ERR_END_OF_CMD      help was requested,
 *            ERR_INVNAME         otherwise.
 */
  
MX_Result
OMTB_OmxGetExtensionIndexNullHandle(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine
)
{
  MX_Result  result = ERR_NOERR;
  OMX_ERRORTYPE err = OMX_ErrorNone;
  char componentRequested[OMTB_MAX_LEN] = {"\0"};
  char resultFileName[OMTB_MAX_LEN] = {"\0"};
  char fOpenMode[OMTB_MAX_LEN] = {"\0"};
  char testCaseId[OMTB_MAX_LEN] = {"\0"};
  char testCaseResult[OMTB_MAX_LEN] = {"\0"}; char returnString[OMTB_MAX_LEN] = {"\0"};
  FILE *fpResult = NULL;
  OMX_HANDLETYPE handle = NULL;                  /* Component handle */
  char vendorSpecificStr[OMX_MAX_STRINGNAME_SIZE]  = {"\0"};
  OMX_INDEXTYPE pIndex = OMX_IndexMax;
  OMTB_OMX_API_TIMING_VAR_DECL;

  /* Read testcase ID */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, testCaseId);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }
  
  /* Read component name */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, componentRequested);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }

  /* Read result filename */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, resultFileName);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }

  /* Read result file type */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, fOpenMode);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }

  /* Read vendor specific string */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, vendorSpecificStr);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }
  
  /* Open the result file */
  fpResult = fopen(resultFileName, fOpenMode);

  if(NULL == fpResult)
  {
    PRINT(PRINT_ERR_MSG, "%s: Error in result file open\n", __FUNCTION__);
    fprintf(fpResult, "%s : Error in result file open\n", testCaseId);
    return ERR_INVNAME;
  }

  /* OpenMax insufficient resources */
    
  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;

  err = OMX_Init ();

  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_Init");

  if(OMX_ErrorNone != err)
  {
    OMTB_OmxReturnStatusString(err, returnString);
    strcpy(testCaseResult, "FAIL - Error in OMX_Init()\n");
    fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
    fclose(fpResult);
    return ERR_INVNAME;
  }

  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;
  
  /* get component handle */
  err = OMX_GetHandle(&handle,
                      (OMX_STRING)componentRequested,
                      NULL,
                      &OMTB_APITestCallback);
  
  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_GetHandle");

  if(OMX_ErrorNone != err)
  {
    OMTB_OmxReturnStatusString(err, returnString);
    strcpy(testCaseResult, "FAIL - Error in OMX_GetHandle()\n");
    fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);

    /* API entry time calculation macro */
    OMTB_OMX_API_ENTRY_TIME_CALC;

    /* OpenMax core uninitialization */
    err = OMX_Deinit ();

    /* API exit time calculation macro */
    OMTB_OMX_API_EXIT_TIME_CALC("OMX_Deinit");
    
    if(OMX_ErrorNone != err)
    {
      OMTB_OmxReturnStatusString(err, returnString);
      strcpy(testCaseResult, "FAIL - Error in OMX_Deinit()\n");
      fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
      result = ERR_INVNAME;
    }
    
    fclose(fpResult);
    return ERR_INVNAME;
  }


  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;

  /* Fet the extension index for the vendor specific structure string */
  err = OMX_GetExtensionIndex(NULL, vendorSpecificStr, &pIndex);

  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_GetExtensionIndex");

  if(OMX_ErrorBadParameter == err)
  {
    strcpy(testCaseResult, "PASS");
    fprintf(fpResult, "%s : %s\n", testCaseId, testCaseResult);
  }
  else
  {
    OMTB_OmxReturnStatusString(err, returnString);
    strcpy(testCaseResult, "FAIL");
    fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
    result = ERR_INVNAME;
  }
  
  /* free component handle */
  if(NULL != handle)
  {
    /* API entry time calculation macro */
    OMTB_OMX_API_ENTRY_TIME_CALC;
    
    err = OMX_FreeHandle(handle);
    
    /* API exit time calculation macro */
    OMTB_OMX_API_EXIT_TIME_CALC("OMX_FreeHandle");
    
    if(OMX_ErrorNone != err)
    {
	OMTB_OmxReturnStatusString(err, returnString);
    strcpy(testCaseResult, "FAIL - Error in OMX_FreeHandle()\n");
    fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);

      result = ERR_INVNAME;
    }
    
  }

  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;
  
  /* OpenMax core uninitialization */
  err = OMX_Deinit ();

  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_Deinit");

    if(OMX_ErrorNone != err)
    {
      OMTB_OmxReturnStatusString(err, returnString);
      strcpy(testCaseResult, "FAIL - Error in OMX_Deinit()\n");
      fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
      result = ERR_INVNAME;
    }

  /* close the result file */
  fclose(fpResult);
  
  return (result);
}


/******************************************************************************\
 *      OMTB_OmxGetExtensionIndexVerMismatch Function Definition
\******************************************************************************/
/**
 *
 *  @brief    This Function performs OMX_GetExtensionIndex API testing.
 *
 *  @param    Pointer to MX_DBG_CMD_CONTEXT_T structure
 *            Pointer to MX_DBG_CMD_Entry_T structure
 *            Character Double Pointer containing the command
 *
 *  @return   ERR_NOERR           successful,
 *            ERR_END_OF_CMD      help was requested,
 *            ERR_INVNAME         otherwise.
 */
  
MX_Result
OMTB_OmxGetExtensionIndexVerMismatch(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine
)
{
  MX_Result  result = ERR_NOERR;
  OMX_ERRORTYPE err = OMX_ErrorNone;
  char componentRequested[OMTB_MAX_LEN] = {"\0"};
  char resultFileName[OMTB_MAX_LEN] = {"\0"};
  char fOpenMode[OMTB_MAX_LEN] = {"\0"};
  char testCaseId[OMTB_MAX_LEN] = {"\0"};
  char testCaseResult[OMTB_MAX_LEN] = {"\0"}; char returnString[OMTB_MAX_LEN] = {"\0"};
  FILE *fpResult = NULL;
  OMX_HANDLETYPE handle = NULL;                  /* Component handle */
  char vendorSpecificStr[OMX_MAX_STRINGNAME_SIZE]  = {"\0"};
  OMX_INDEXTYPE pIndex = OMX_IndexMax;
  OMTB_OMX_API_TIMING_VAR_DECL;

  /* Read testcase ID */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, testCaseId);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }
  
  /* Read component name */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, componentRequested);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }

  /* Read result filename */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, resultFileName);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }

  /* Read result file type */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, fOpenMode);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }

  /* Read vendor specific string */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, vendorSpecificStr);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }
  
  /* Open the result file */
  fpResult = fopen(resultFileName, fOpenMode);

  if(NULL == fpResult)
  {
    PRINT(PRINT_ERR_MSG, "%s: Error in result file open\n", __FUNCTION__);
    fprintf(fpResult, "%s : Error in result file open\n", testCaseId);
    return ERR_INVNAME;
  }

  /* OpenMax insufficient resources */
    
  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;

  err = OMX_Init ();

  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_Init");

  if(OMX_ErrorNone != err)
  {
    OMTB_OmxReturnStatusString(err, returnString);
    strcpy(testCaseResult, "FAIL - Error in OMX_Init()\n");
    fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
    fclose(fpResult);
    return ERR_INVNAME;
  }

  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;
  
  /* get component handle */
  err = OMX_GetHandle(&handle,
                      (OMX_STRING)componentRequested,
                      NULL,
                      &OMTB_APITestCallback);
  
  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_GetHandle");

  if(OMX_ErrorNone != err)
  {
    OMTB_OmxReturnStatusString(err, returnString);
    strcpy(testCaseResult, "FAIL - Error in OMX_GetHandle()\n");
    fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);

    /* API entry time calculation macro */
    OMTB_OMX_API_ENTRY_TIME_CALC;

    /* OpenMax core uninitialization */
    err = OMX_Deinit ();

    /* API exit time calculation macro */
    OMTB_OMX_API_EXIT_TIME_CALC("OMX_Deinit");
    
  if(OMX_ErrorNone != err)
  {
    OMTB_OmxReturnStatusString(err, returnString);
    strcpy(testCaseResult, "FAIL - Error in OMX_Init()\n");
    fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
    fclose(fpResult);
    return ERR_INVNAME;
  }
    
    fclose(fpResult);
    return ERR_INVNAME;
  }


  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;

  /* Fet the extension index for the vendor specific structure string */
  err = OMX_GetExtensionIndex(handle, vendorSpecificStr, &pIndex);

  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_GetExtensionIndex");

  if(OMX_ErrorVersionMismatch == err)
  {
    strcpy(testCaseResult, "PASS");
    fprintf(fpResult, "%s : %s\n", testCaseId, testCaseResult);
  }
  else
  {
    OMTB_OmxReturnStatusString(err, returnString);
    strcpy(testCaseResult, "FAIL");
    fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
    result = ERR_INVNAME;
  }
  
  /* free component handle */
  if(NULL != handle)
  {
    /* API entry time calculation macro */
    OMTB_OMX_API_ENTRY_TIME_CALC;
    
    err = OMX_FreeHandle(handle);
    
    /* API exit time calculation macro */
    OMTB_OMX_API_EXIT_TIME_CALC("OMX_FreeHandle");
    
    if(OMX_ErrorNone != err)
    {
	OMTB_OmxReturnStatusString(err, returnString);
    strcpy(testCaseResult, "FAIL - Error in OMX_FreeHandle()\n");
    fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);

      result = ERR_INVNAME;
    }
    
  }

  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;
  
  /* OpenMax core uninitialization */
  err = OMX_Deinit ();

  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_Deinit");

    if(OMX_ErrorNone != err)
    {
      OMTB_OmxReturnStatusString(err, returnString);
      strcpy(testCaseResult, "FAIL - Error in OMX_Deinit()\n");
      fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
      result = ERR_INVNAME;
    }

  /* close the result file */
  fclose(fpResult);
  
  return (result);
}


/******************************************************************************\
 *      OMTB_OmxGetExtensionIndexTimeOut Function Definition
\******************************************************************************/
/**
 *
 *  @brief    This Function performs OMX_GetExtensionIndex API testing.
 *
 *  @param    Pointer to MX_DBG_CMD_CONTEXT_T structure
 *            Pointer to MX_DBG_CMD_Entry_T structure
 *            Character Double Pointer containing the command
 *
 *  @return   ERR_NOERR           successful,
 *            ERR_END_OF_CMD      help was requested,
 *            ERR_INVNAME         otherwise.
 */
  
MX_Result
OMTB_OmxGetExtensionIndexTimeOut(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine
)
{
  MX_Result  result = ERR_NOERR;
  OMX_ERRORTYPE err = OMX_ErrorNone;
  char componentRequested[OMTB_MAX_LEN] = {"\0"};
  char resultFileName[OMTB_MAX_LEN] = {"\0"};
  char fOpenMode[OMTB_MAX_LEN] = {"\0"};
  char testCaseId[OMTB_MAX_LEN] = {"\0"};
  char testCaseResult[OMTB_MAX_LEN] = {"\0"}; char returnString[OMTB_MAX_LEN] = {"\0"};
  FILE *fpResult = NULL;
  OMX_HANDLETYPE handle = NULL;                  /* Component handle */
  char vendorSpecificStr[OMX_MAX_STRINGNAME_SIZE]  = {"\0"};
  OMX_INDEXTYPE pIndex = OMX_IndexMax;
  OMTB_OMX_API_TIMING_VAR_DECL;

  /* Read testcase ID */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, testCaseId);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }
  
  /* Read component name */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, componentRequested);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }

  /* Read result filename */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, resultFileName);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }

  /* Read result file type */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, fOpenMode);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }

  /* Read vendor specific string */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, vendorSpecificStr);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }
  
  /* Open the result file */
  fpResult = fopen(resultFileName, fOpenMode);

  if(NULL == fpResult)
  {
    PRINT(PRINT_ERR_MSG, "%s: Error in result file open\n", __FUNCTION__);
    fprintf(fpResult, "%s : Error in result file open\n", testCaseId);
    return ERR_INVNAME;
  }

  /* OpenMax insufficient resources */
    
  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;

  err = OMX_Init ();

  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_Init");

  if(OMX_ErrorNone != err)
  {
    OMTB_OmxReturnStatusString(err, returnString);
    strcpy(testCaseResult, "FAIL - Error in OMX_Init()\n");
    fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
    fclose(fpResult);
    return ERR_INVNAME;
  }

  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;
  
  /* get component handle */
  err = OMX_GetHandle(&handle,
                      (OMX_STRING)componentRequested,
                      NULL,
                      &OMTB_APITestCallback);
  
  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_GetHandle");

  if(OMX_ErrorNone != err)
  {
    OMTB_OmxReturnStatusString(err, returnString);
    strcpy(testCaseResult, "FAIL - Error in OMX_GetHandle()\n");
    fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);

    /* API entry time calculation macro */
    OMTB_OMX_API_ENTRY_TIME_CALC;

    /* OpenMax core uninitialization */
    err = OMX_Deinit ();

    /* API exit time calculation macro */
    OMTB_OMX_API_EXIT_TIME_CALC("OMX_Deinit");
    
    if(OMX_ErrorNone != err)
    {
      OMTB_OmxReturnStatusString(err, returnString);
      strcpy(testCaseResult, "FAIL - Error in OMX_Deinit()\n");
      fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
      result = ERR_INVNAME;
    }
    
    fclose(fpResult);
    return ERR_INVNAME;
  }


  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;

  /* Fet the extension index for the vendor specific structure string */
  err = OMX_GetExtensionIndex(handle, vendorSpecificStr, &pIndex);

  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_GetExtensionIndex");

  if(OMX_ErrorTimeout == err)
  {
    strcpy(testCaseResult, "PASS");
    fprintf(fpResult, "%s : %s\n", testCaseId, testCaseResult);
  }
  else
  {
    OMTB_OmxReturnStatusString(err, returnString);
    strcpy(testCaseResult, "FAIL");
    fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
    result = ERR_INVNAME;
  }
  
  /* free component handle */
  if(NULL != handle)
  {
    /* API entry time calculation macro */
    OMTB_OMX_API_ENTRY_TIME_CALC;
    
    err = OMX_FreeHandle(handle);
    
    /* API exit time calculation macro */
    OMTB_OMX_API_EXIT_TIME_CALC("OMX_FreeHandle");
    
    if(OMX_ErrorNone != err)
    {
	OMTB_OmxReturnStatusString(err, returnString);
    strcpy(testCaseResult, "FAIL - Error in OMX_FreeHandle()\n");
    fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);

      result = ERR_INVNAME;
    }
    
  }

  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;
  
  /* OpenMax core uninitialization */
  err = OMX_Deinit ();

  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_Deinit");

    if(OMX_ErrorNone != err)
    {
      OMTB_OmxReturnStatusString(err, returnString);
      strcpy(testCaseResult, "FAIL - Error in OMX_Deinit()\n");
      fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
      result = ERR_INVNAME;
    }

  /* close the result file */
  fclose(fpResult);
  
  return (result);
}


/******************************************************************************\
 *      OMTB_OmxGetExtensionIndexWrongVendorStr Function Definition
\******************************************************************************/
/**
 *
 *  @brief    This Function performs OMX_GetExtensionIndex API testing.
 *
 *  @param    Pointer to MX_DBG_CMD_CONTEXT_T structure
 *            Pointer to MX_DBG_CMD_Entry_T structure
 *            Character Double Pointer containing the command
 *
 *  @return   ERR_NOERR           successful,
 *            ERR_END_OF_CMD      help was requested,
 *            ERR_INVNAME         otherwise.
 */
  
MX_Result
OMTB_OmxGetExtensionIndexWrongVendorStr(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine
)
{
  MX_Result  result = ERR_NOERR;
  OMX_ERRORTYPE err = OMX_ErrorNone;
  char componentRequested[OMTB_MAX_LEN] = {"\0"};
  char resultFileName[OMTB_MAX_LEN] = {"\0"};
  char fOpenMode[OMTB_MAX_LEN] = {"\0"};
  char testCaseId[OMTB_MAX_LEN] = {"\0"};
  char testCaseResult[OMTB_MAX_LEN] = {"\0"}; char returnString[OMTB_MAX_LEN] = {"\0"};
  FILE *fpResult = NULL;
  OMX_HANDLETYPE handle = NULL;                  /* Component handle */
  char vendorSpecificStr[OMX_MAX_STRINGNAME_SIZE]  = {"\0"};
  OMX_INDEXTYPE pIndex = OMX_IndexMax;
  OMTB_OMX_API_TIMING_VAR_DECL;

  /* Read testcase ID */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, testCaseId);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }
  
  /* Read component name */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, componentRequested);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }

  /* Read result filename */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, resultFileName);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }

  /* Read result file type */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, fOpenMode);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }

  /* Read vendor specific string */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, vendorSpecificStr);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }
  
  /* Open the result file */
  fpResult = fopen(resultFileName, fOpenMode);

  if(NULL == fpResult)
  {
    PRINT(PRINT_ERR_MSG, "%s: Error in result file open\n", __FUNCTION__);
    fprintf(fpResult, "%s : Error in result file open\n", testCaseId);
    return ERR_INVNAME;
  }

  /* OpenMax insufficient resources */
    
  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;

  err = OMX_Init ();

  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_Init");

  if(OMX_ErrorNone != err)
  {
    OMTB_OmxReturnStatusString(err, returnString);
    strcpy(testCaseResult, "FAIL - Error in OMX_Init()\n");
    fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
    fclose(fpResult);
    return ERR_INVNAME;
  }

  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;
  
  /* get component handle */
  err = OMX_GetHandle(&handle,
                      (OMX_STRING)componentRequested,
                      NULL,
                      &OMTB_APITestCallback);
  
  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_GetHandle");

  if(OMX_ErrorNone != err)
  {
    OMTB_OmxReturnStatusString(err, returnString);
    strcpy(testCaseResult, "FAIL - Error in OMX_GetHandle()\n");
    fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);

    /* API entry time calculation macro */
    OMTB_OMX_API_ENTRY_TIME_CALC;

    /* OpenMax core uninitialization */
    err = OMX_Deinit ();

    /* API exit time calculation macro */
    OMTB_OMX_API_EXIT_TIME_CALC("OMX_Deinit");
    
    if(OMX_ErrorNone != err)
    {
      OMTB_OmxReturnStatusString(err, returnString);
      strcpy(testCaseResult, "FAIL - Error in OMX_Deinit()\n");
      fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
      result = ERR_INVNAME;
    }
    
    fclose(fpResult);
    return ERR_INVNAME;
  }


  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;

  /* Fet the extension index for the vendor specific structure string */
  err = OMX_GetExtensionIndex(handle, vendorSpecificStr, &pIndex);

  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_GetExtensionIndex");

  if(OMX_ErrorUnsupportedIndex == err)
  {
    strcpy(testCaseResult, "PASS");
    fprintf(fpResult, "%s : %s\n", testCaseId, testCaseResult);
  }
  else
  {
    OMTB_OmxReturnStatusString(err, returnString);
    strcpy(testCaseResult, "FAIL");
    fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
    result = ERR_INVNAME;
  }
  
  /* free component handle */
  if(NULL != handle)
  {
    /* API entry time calculation macro */
    OMTB_OMX_API_ENTRY_TIME_CALC;
    
    err = OMX_FreeHandle(handle);
    
    /* API exit time calculation macro */
    OMTB_OMX_API_EXIT_TIME_CALC("OMX_FreeHandle");
    
    if(OMX_ErrorNone != err)
    {
	OMTB_OmxReturnStatusString(err, returnString);
    strcpy(testCaseResult, "FAIL - Error in OMX_FreeHandle()\n");
    fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);

      result = ERR_INVNAME;
    }
    
  }

  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;
  
  /* OpenMax core uninitialization */
  err = OMX_Deinit ();

  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_Deinit");

    if(OMX_ErrorNone != err)
    {
      OMTB_OmxReturnStatusString(err, returnString);
      strcpy(testCaseResult, "FAIL - Error in OMX_Deinit()\n");
      fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
      result = ERR_INVNAME;
    }

  /* close the result file */
  fclose(fpResult);
  
  return (result);
}


/******************************************************************************\
 *      OMTB_OmxSetupTunnelOnce Function Definition
\******************************************************************************/
/**
 *
 *  @brief    This Function performs OMX_SetupTunnel API testing.
 *
 *  @param    Pointer to MX_DBG_CMD_CONTEXT_T structure
 *            Pointer to MX_DBG_CMD_Entry_T structure
 *            Character Double Pointer containing the command
 *
 *  @return   ERR_NOERR           successful,
 *            ERR_END_OF_CMD      help was requested,
 *            ERR_INVNAME         otherwise.
 */

MX_Result
OMTB_OmxSetupTunnelOnce(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine
)
{
  MX_Result  result = ERR_NOERR;
  OMX_ERRORTYPE err = OMX_ErrorNone;
  char componentRequested[OMTB_MAX_LEN] = {"\0"};
  char resultFileName[OMTB_MAX_LEN] = {"\0"};
  char fOpenMode[OMTB_MAX_LEN] = {"\0"};
  char testCaseId[OMTB_MAX_LEN] = {"\0"};
  char testCaseResult[OMTB_MAX_LEN] = {"\0"}; char returnString[OMTB_MAX_LEN] = {"\0"};
  FILE *fpResult = NULL;
  char componentRequested2[OMTB_MAX_LEN] = {"\0"};
  int portNo1 = 0, portNo2 = 0;
  OMX_HANDLETYPE handle, handle2;                  /* Component handle */
  OMTB_OMX_API_TIMING_VAR_DECL;

  /* Read testcase ID */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, testCaseId);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }
  
  /* Read first component name */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, componentRequested);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }

  /* Read result filename */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, resultFileName);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }

  /* Read result file type */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, fOpenMode);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }

  /* Read port number */
  result = XdbgCmdNextNum(pContext, pCmdEntry, ppCmdLine, (UINT32*)&portNo1);
  if (ERR_NOERR != result)
  {

    return result;
  }
  
  /* Read second component name */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, componentRequested2);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }

  /* Read port number */
  result = XdbgCmdNextNum(pContext, pCmdEntry, ppCmdLine, (UINT32*)&portNo2);
  if (ERR_NOERR != result)
  {

    return result;
  }
  
  /* Open the result file */
  fpResult = fopen(resultFileName, fOpenMode);

  if(NULL == fpResult)
  {
    PRINT(PRINT_ERR_MSG, "%s: Error in result file open\n", __FUNCTION__);
    fprintf(fpResult, "%s : Error in result file open\n", testCaseId);
    return ERR_INVNAME;
  }

  /* OpenMax insufficient resources */
    
  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;

  err = OMX_Init ();

  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_Init");

  if(OMX_ErrorNone != err)
  {
    OMTB_OmxReturnStatusString(err, returnString);
    strcpy(testCaseResult, "FAIL - Error in OMX_Init()\n");
    fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
    fclose(fpResult);
    return ERR_INVNAME;
  }

  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;
  
  /* get component handle */
  err = OMX_GetHandle(&handle,
                      (OMX_STRING)componentRequested,
                      NULL,
                      &OMTB_APITestCallback);
  
  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_GetHandle");

  if(OMX_ErrorNone != err)
  {
    OMTB_OmxReturnStatusString(err, returnString);
    strcpy(testCaseResult, "FAIL - Error in OMX_GetHandle()\n");
    fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);

    /* API entry time calculation macro */
    OMTB_OMX_API_ENTRY_TIME_CALC;

    /* OpenMax core uninitialization */
    err = OMX_Deinit ();

    /* API exit time calculation macro */
    OMTB_OMX_API_EXIT_TIME_CALC("OMX_Deinit");
    
    if(OMX_ErrorNone != err)
    {
      OMTB_OmxReturnStatusString(err, returnString);
      strcpy(testCaseResult, "FAIL - Error in OMX_Deinit()\n");
      fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
      result = ERR_INVNAME;
    }
    
    fclose(fpResult);
    return ERR_INVNAME;
  }

  
  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;
  
  /* get component handle */
  err = OMX_GetHandle(&handle2,
                      (OMX_STRING)componentRequested2,
                      NULL,
                      &OMTB_APITestCallback);
  
  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_GetHandle");

  if(OMX_ErrorNone != err)
  {
    OMTB_OmxReturnStatusString(err, returnString);
    strcpy(testCaseResult, "FAIL - Error in OMX_GetHandle()\n");
    fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);

    /* API entry time calculation macro */
    OMTB_OMX_API_ENTRY_TIME_CALC;
    
    err = OMX_FreeHandle(handle);
    
    /* API exit time calculation macro */
    OMTB_OMX_API_EXIT_TIME_CALC("OMX_FreeHandle");
    
    if(OMX_ErrorNone != err)
    {
	OMTB_OmxReturnStatusString(err, returnString);
    strcpy(testCaseResult, "FAIL - Error in OMX_FreeHandle()\n");
    fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
      result = ERR_INVNAME;
    }
    
    /* API entry time calculation macro */
    OMTB_OMX_API_ENTRY_TIME_CALC;

    /* OpenMax core uninitialization */
    err = OMX_Deinit ();

    /* API exit time calculation macro */
    OMTB_OMX_API_EXIT_TIME_CALC("OMX_Deinit");
    
    if(OMX_ErrorNone != err)
    {
      OMTB_OmxReturnStatusString(err, returnString);
      strcpy(testCaseResult, "FAIL - Error in OMX_Deinit()\n");
      fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
      result = ERR_INVNAME;
    }
    
    fclose(fpResult);
    return ERR_INVNAME;
  }
  

  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;

  /* Setup tunnel between the specified port of two components */
  err = OMX_SetupTunnel(handle, portNo1, 
                        handle2 , portNo2);

  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_SetupTunnel");
  
  if(OMX_ErrorNone == err)
  {
    strcpy(testCaseResult, "PASS");
    fprintf(fpResult, "%s : %s\n", testCaseId, testCaseResult);
  }
  else
  {
    OMTB_OmxReturnStatusString(err, returnString);
    strcpy(testCaseResult, "FAIL");
    fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
    result = ERR_INVNAME;
  }
  
  /* free component handle */
  if(NULL != handle)
  {
    /* API entry time calculation macro */
    OMTB_OMX_API_ENTRY_TIME_CALC;
    
    err = OMX_FreeHandle(handle);
    
    /* API exit time calculation macro */
    OMTB_OMX_API_EXIT_TIME_CALC("OMX_FreeHandle");
    
    if(OMX_ErrorNone != err)
    {
	 OMTB_OmxReturnStatusString(err, returnString);
     strcpy(testCaseResult, "FAIL - Error in OMX_FreeHandle()\n");
     fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
      result = ERR_INVNAME;
    }

  }

  if(NULL != handle2)
  {
    /* API entry time calculation macro */
    OMTB_OMX_API_ENTRY_TIME_CALC;
    
    err = OMX_FreeHandle(handle2);
    
    /* API exit time calculation macro */
    OMTB_OMX_API_EXIT_TIME_CALC("OMX_FreeHandle");

    if(OMX_ErrorNone != err)
    {
	 OMTB_OmxReturnStatusString(err, returnString);
     strcpy(testCaseResult, "FAIL - Error in OMX_FreeHandle()\n");
     fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
      result = ERR_INVNAME;
    }
  }

  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;
  
  /* OpenMax core uninitialization */
  err = OMX_Deinit ();

  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_Deinit");

    if(OMX_ErrorNone != err)
    {
      OMTB_OmxReturnStatusString(err, returnString);
      strcpy(testCaseResult, "FAIL - Error in OMX_Deinit()\n");
      fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
      result = ERR_INVNAME;
    }

  /* close the result file */
  fclose(fpResult);
  
  return (result);
}


/******************************************************************************\
 *      OMTB_OmxSetupTunnelNullHandle Function Definition
\******************************************************************************/
/**
 *
 *  @brief    This Function performs OMX_SetupTunnel API testing.
 *
 *  @param    Pointer to MX_DBG_CMD_CONTEXT_T structure
 *            Pointer to MX_DBG_CMD_Entry_T structure
 *            Character Double Pointer containing the command
 *
 *  @return   ERR_NOERR           successful,
 *            ERR_END_OF_CMD      help was requested,
 *            ERR_INVNAME         otherwise.
 */

MX_Result
OMTB_OmxSetupTunnelNullHandle(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine
)
{
  MX_Result  result = ERR_NOERR;
  OMX_ERRORTYPE err = OMX_ErrorNone;
  char componentRequested[OMTB_MAX_LEN] = {"\0"};
  char resultFileName[OMTB_MAX_LEN] = {"\0"};
  char fOpenMode[OMTB_MAX_LEN] = {"\0"};
  char testCaseId[OMTB_MAX_LEN] = {"\0"};
  char testCaseResult[OMTB_MAX_LEN] = {"\0"}; char returnString[OMTB_MAX_LEN] = {"\0"};
  FILE *fpResult = NULL;
  char componentRequested2[OMTB_MAX_LEN] = {"\0"};
  int portNo1 = 0, portNo2 = 0;
  OMX_HANDLETYPE handle, handle2;                  /* Component handle */
  OMTB_OMX_API_TIMING_VAR_DECL;

  /* Read testcase ID */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, testCaseId);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }
  
  /* Read first component name */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, componentRequested);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }

  /* Read result filename */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, resultFileName);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }

  /* Read result file type */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, fOpenMode);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }

  /* Read port number */
  result = XdbgCmdNextNum(pContext, pCmdEntry, ppCmdLine, (UINT32*)&portNo1);
  if (ERR_NOERR != result)
  {

    return result;
  }
  
  /* Read second component name */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, componentRequested2);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }

  /* Read port number */
  result = XdbgCmdNextNum(pContext, pCmdEntry, ppCmdLine, (UINT32*)&portNo2);
  if (ERR_NOERR != result)
  {

    return result;
  }
  
  /* Open the result file */
  fpResult = fopen(resultFileName, fOpenMode);

  if(NULL == fpResult)
  {
    PRINT(PRINT_ERR_MSG, "%s: Error in result file open\n", __FUNCTION__);
    fprintf(fpResult, "%s : Error in result file open\n", testCaseId);
    return ERR_INVNAME;
  }

  /* OpenMax insufficient resources */
    
  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;

  err = OMX_Init ();

  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_Init");

  if(OMX_ErrorNone != err)
  {
    OMTB_OmxReturnStatusString(err, returnString);
    strcpy(testCaseResult, "FAIL - Error in OMX_Init()\n");
    fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
    fclose(fpResult);
    return ERR_INVNAME;
  }

  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;
  
  /* get component handle */
  err = OMX_GetHandle(&handle,
                      (OMX_STRING)componentRequested,
                      NULL,
                      &OMTB_APITestCallback);
  
  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_GetHandle");

  if(OMX_ErrorNone != err)
  {
    OMTB_OmxReturnStatusString(err, returnString);
    strcpy(testCaseResult, "FAIL - Error in OMX_GetHandle()\n");
    fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);

    /* API entry time calculation macro */
    OMTB_OMX_API_ENTRY_TIME_CALC;

    /* OpenMax core uninitialization */
    err = OMX_Deinit ();

    /* API exit time calculation macro */
    OMTB_OMX_API_EXIT_TIME_CALC("OMX_Deinit");
    
    if(OMX_ErrorNone != err)
    {
      OMTB_OmxReturnStatusString(err, returnString);
      strcpy(testCaseResult, "FAIL - Error in OMX_Deinit()\n");
      fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
      result = ERR_INVNAME;
    }
    
    fclose(fpResult);
    return ERR_INVNAME;
  }

  
  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;
  
  /* get component handle */
  err = OMX_GetHandle(&handle2,
                      (OMX_STRING)componentRequested2,
                      NULL,
                      &OMTB_APITestCallback);
  
  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_GetHandle");

  if(OMX_ErrorNone != err)
  {
    OMTB_OmxReturnStatusString(err, returnString);
    strcpy(testCaseResult, "FAIL - Error in OMX_GetHandle()\n");
    fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);

    /* API entry time calculation macro */
    OMTB_OMX_API_ENTRY_TIME_CALC;
    
    err = OMX_FreeHandle(handle);
    
    /* API exit time calculation macro */
    OMTB_OMX_API_EXIT_TIME_CALC("OMX_FreeHandle");
    
    if(OMX_ErrorNone != err)
    {
	OMTB_OmxReturnStatusString(err, returnString);
    strcpy(testCaseResult, "FAIL - Error in OMX_FreeHandle()\n");
    fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
      result = ERR_INVNAME;
    }
    
    /* API entry time calculation macro */
    OMTB_OMX_API_ENTRY_TIME_CALC;

    /* OpenMax core uninitialization */
    err = OMX_Deinit ();

    /* API exit time calculation macro */
    OMTB_OMX_API_EXIT_TIME_CALC("OMX_Deinit");
    
    if(OMX_ErrorNone != err)
    {
      OMTB_OmxReturnStatusString(err, returnString);
      strcpy(testCaseResult, "FAIL - Error in OMX_Deinit()\n");
      fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
      result = ERR_INVNAME;
    }
    
    fclose(fpResult);
    return ERR_INVNAME;
  }
  

  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;

  /* Setup tunnel between the specified port of two components */
  err = OMX_SetupTunnel(NULL, portNo1, 
                        NULL , portNo2);

  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_SetupTunnel");
  
  if(OMX_ErrorBadParameter == err)
  {
    strcpy(testCaseResult, "PASS");
    fprintf(fpResult, "%s : %s\n", testCaseId, testCaseResult);
  }
  else
  {
    OMTB_OmxReturnStatusString(err, returnString);
    strcpy(testCaseResult, "FAIL");
    fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
    result = ERR_INVNAME;
  }
  
  /* free component handle */
  if(NULL != handle)
  {
    /* API entry time calculation macro */
    OMTB_OMX_API_ENTRY_TIME_CALC;
    
    err = OMX_FreeHandle(handle);
    
    /* API exit time calculation macro */
    OMTB_OMX_API_EXIT_TIME_CALC("OMX_FreeHandle");
    
    if(OMX_ErrorNone != err)
    {
	OMTB_OmxReturnStatusString(err, returnString);
    strcpy(testCaseResult, "FAIL - Error in OMX_FreeHandle()\n");
    fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
      result = ERR_INVNAME;
    }

  }

  if(NULL != handle2)
  {
    /* API entry time calculation macro */
    OMTB_OMX_API_ENTRY_TIME_CALC;
    
    err = OMX_FreeHandle(handle2);
    
    /* API exit time calculation macro */
    OMTB_OMX_API_EXIT_TIME_CALC("OMX_FreeHandle");

    if(OMX_ErrorNone != err)
    {
	OMTB_OmxReturnStatusString(err, returnString);
    strcpy(testCaseResult, "FAIL - Error in OMX_FreeHandle()\n");
    fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
      result = ERR_INVNAME;
    }
  }
  
  /* OpenMax core uninitialization */
  err = OMX_Deinit ();

  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_Deinit");

    if(OMX_ErrorNone != err)
    {
      OMTB_OmxReturnStatusString(err, returnString);
      strcpy(testCaseResult, "FAIL - Error in OMX_Deinit()\n");
      fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
      result = ERR_INVNAME;
    }

  /* close the result file */
  fclose(fpResult);
  
  return (result);
}


/******************************************************************************\
 *      OMTB_OmxSetupTunnelWrongPortNum Function Definition
\******************************************************************************/
/**
 *
 *  @brief    This Function performs OMX_SetupTunnel API testing.
 *
 *  @param    Pointer to MX_DBG_CMD_CONTEXT_T structure
 *            Pointer to MX_DBG_CMD_Entry_T structure
 *            Character Double Pointer containing the command
 *
 *  @return   ERR_NOERR           successful,
 *            ERR_END_OF_CMD      help was requested,
 *            ERR_INVNAME         otherwise.
 */

MX_Result
OMTB_OmxSetupTunnelWrongPortNum(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine
)
{
  MX_Result  result = ERR_NOERR;
  OMX_ERRORTYPE err = OMX_ErrorNone;
  char componentRequested[OMTB_MAX_LEN] = {"\0"};
  char resultFileName[OMTB_MAX_LEN] = {"\0"};
  char fOpenMode[OMTB_MAX_LEN] = {"\0"};
  char testCaseId[OMTB_MAX_LEN] = {"\0"};
  char testCaseResult[OMTB_MAX_LEN] = {"\0"}; char returnString[OMTB_MAX_LEN] = {"\0"};
  FILE *fpResult = NULL;
  char componentRequested2[OMTB_MAX_LEN] = {"\0"};
  int portNo1 = 0, portNo2 = 0;
  OMX_HANDLETYPE handle, handle2;                  /* Component handle */
  OMTB_OMX_API_TIMING_VAR_DECL;

  /* Read testcase ID */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, testCaseId);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }
  
  /* Read first component name */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, componentRequested);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }

  /* Read result filename */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, resultFileName);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }

  /* Read result file type */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, fOpenMode);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }

  /* Read port number */
  result = XdbgCmdNextNum(pContext, pCmdEntry, ppCmdLine, (UINT32*)&portNo1);
  if (ERR_NOERR != result)
  {

    return result;
  }
  
  /* Read second component name */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, componentRequested2);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }

  /* Read port number */
  result = XdbgCmdNextNum(pContext, pCmdEntry, ppCmdLine, (UINT32*)&portNo2);
  if (ERR_NOERR != result)
  {

    return result;
  }
  
  /* Open the result file */
  fpResult = fopen(resultFileName, fOpenMode);

  if(NULL == fpResult)
  {
    PRINT(PRINT_ERR_MSG, "%s: Error in result file open\n", __FUNCTION__);
    fprintf(fpResult, "%s : Error in result file open\n", testCaseId);
    return ERR_INVNAME;
  }

  /* OpenMax insufficient resources */
    
  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;

  err = OMX_Init ();

  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_Init");

  if(OMX_ErrorNone != err)
  {
    OMTB_OmxReturnStatusString(err, returnString);
    strcpy(testCaseResult, "FAIL - Error in OMX_Init()\n");
    fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
    fclose(fpResult);
    return ERR_INVNAME;
  }

  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;
  
  /* get component handle */
  err = OMX_GetHandle(&handle,
                      (OMX_STRING)componentRequested,
                      NULL,
                      &OMTB_APITestCallback);
  
  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_GetHandle");

  if(OMX_ErrorNone != err)
  {
    OMTB_OmxReturnStatusString(err, returnString);
    strcpy(testCaseResult, "FAIL - Error in OMX_GetHandle()\n");
    fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);

    /* API entry time calculation macro */
    OMTB_OMX_API_ENTRY_TIME_CALC;

    /* OpenMax core uninitialization */
    err = OMX_Deinit ();

    /* API exit time calculation macro */
    OMTB_OMX_API_EXIT_TIME_CALC("OMX_Deinit");
    
    if(OMX_ErrorNone != err)
    {
      OMTB_OmxReturnStatusString(err, returnString);
      strcpy(testCaseResult, "FAIL - Error in OMX_Deinit()\n");
      fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
      result = ERR_INVNAME;
    }
    
    fclose(fpResult);
    return ERR_INVNAME;
  }

  
  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;
  
  /* get component handle */
  err = OMX_GetHandle(&handle2,
                      (OMX_STRING)componentRequested2,
                      NULL,
                      &OMTB_APITestCallback);
  
  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_GetHandle");

  if(OMX_ErrorNone != err)
  {
    OMTB_OmxReturnStatusString(err, returnString);
    strcpy(testCaseResult, "FAIL - Error in OMX_GetHandle()\n");
    fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);

    /* API entry time calculation macro */
    OMTB_OMX_API_ENTRY_TIME_CALC;
    
    err = OMX_FreeHandle(handle);
    
    /* API exit time calculation macro */
    OMTB_OMX_API_EXIT_TIME_CALC("OMX_FreeHandle");
    
    if(OMX_ErrorNone != err)
    {
	OMTB_OmxReturnStatusString(err, returnString);
    strcpy(testCaseResult, "FAIL - Error in OMX_FreeHandle()\n");
    fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
      result = ERR_INVNAME;
    }
    
    /* API entry time calculation macro */
    OMTB_OMX_API_ENTRY_TIME_CALC;

    /* OpenMax core uninitialization */
    err = OMX_Deinit ();

    /* API exit time calculation macro */
    OMTB_OMX_API_EXIT_TIME_CALC("OMX_Deinit");
    
    if(OMX_ErrorNone != err)
    {
      OMTB_OmxReturnStatusString(err, returnString);
      strcpy(testCaseResult, "FAIL - Error in OMX_Deinit()\n");
      fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
      result = ERR_INVNAME;
    }
    
    fclose(fpResult);
    return ERR_INVNAME;
  }
  

  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;

  /* Setup tunnel between the specified port of two components */
  err = OMX_SetupTunnel(handle, portNo1, 
                        handle2 , portNo2);

  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_SetupTunnel");
  
  if(OMX_ErrorBadParameter == err)
  {
    strcpy(testCaseResult, "PASS");
    fprintf(fpResult, "%s : %s\n", testCaseId, testCaseResult);
  }
  else
  {
    OMTB_OmxReturnStatusString(err, returnString);
    strcpy(testCaseResult, "FAIL");
    fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
    result = ERR_INVNAME;
  }
  
  /* free component handle */
  if(NULL != handle)
  {
    /* API entry time calculation macro */
    OMTB_OMX_API_ENTRY_TIME_CALC;
    
    err = OMX_FreeHandle(handle);
    
    /* API exit time calculation macro */
    OMTB_OMX_API_EXIT_TIME_CALC("OMX_FreeHandle");
    
    if(OMX_ErrorNone != err)
    {
	OMTB_OmxReturnStatusString(err, returnString);
    strcpy(testCaseResult, "FAIL - Error in OMX_FreeHandle()\n");
    fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
      result = ERR_INVNAME;
    }

  }

  if(NULL != handle2)
  {
    /* API entry time calculation macro */
    OMTB_OMX_API_ENTRY_TIME_CALC;
    
    err = OMX_FreeHandle(handle2);
    
    /* API exit time calculation macro */
    OMTB_OMX_API_EXIT_TIME_CALC("OMX_FreeHandle");

    if(OMX_ErrorNone != err)
    {
	OMTB_OmxReturnStatusString(err, returnString);
    strcpy(testCaseResult, "FAIL - Error in OMX_FreeHandle()\n");
    fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
      result = ERR_INVNAME;
    }
  }

  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;
  
  /* OpenMax core uninitialization */
  err = OMX_Deinit ();

  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_Deinit");

    if(OMX_ErrorNone != err)
    {
      OMTB_OmxReturnStatusString(err, returnString);
      strcpy(testCaseResult, "FAIL - Error in OMX_Deinit()\n");
      fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
      result = ERR_INVNAME;
    }

  /* close the result file */
  fclose(fpResult);
  
  return (result);
}


/******************************************************************************\
 *      OMTB_OmxSetupTunnelNotImplemented Function Definition
\******************************************************************************/
/**
 *
 *  @brief    This Function performs OMX_SetupTunnel API testing.
 *
 *  @param    Pointer to MX_DBG_CMD_CONTEXT_T structure
 *            Pointer to MX_DBG_CMD_Entry_T structure
 *            Character Double Pointer containing the command
 *
 *  @return   ERR_NOERR           successful,
 *            ERR_END_OF_CMD      help was requested,
 *            ERR_INVNAME         otherwise.
 */

MX_Result
OMTB_OmxSetupTunnelNotImplemented(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine
)
{
  MX_Result  result = ERR_NOERR;
  OMX_ERRORTYPE err = OMX_ErrorNone;
  char componentRequested[OMTB_MAX_LEN] = {"\0"};
  char resultFileName[OMTB_MAX_LEN] = {"\0"};
  char fOpenMode[OMTB_MAX_LEN] = {"\0"};
  char testCaseId[OMTB_MAX_LEN] = {"\0"};
  char testCaseResult[OMTB_MAX_LEN] = {"\0"}; char returnString[OMTB_MAX_LEN] = {"\0"};
  FILE *fpResult = NULL;
  char componentRequested2[OMTB_MAX_LEN] = {"\0"};
  int portNo1 = 0, portNo2 = 0;
  OMX_HANDLETYPE handle, handle2;                  /* Component handle */
  OMTB_OMX_API_TIMING_VAR_DECL;

  /* Read testcase ID */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, testCaseId);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }
  
  /* Read first component name */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, componentRequested);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }

  /* Read result filename */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, resultFileName);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }

  /* Read result file type */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, fOpenMode);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }

  /* Read port number */
  result = XdbgCmdNextNum(pContext, pCmdEntry, ppCmdLine, (UINT32*)&portNo1);
  if (ERR_NOERR != result)
  {

    return result;
  }
  
  /* Read second component name */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, componentRequested2);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }

  /* Read port number */
  result = XdbgCmdNextNum(pContext, pCmdEntry, ppCmdLine, (UINT32*)&portNo2);
  if (ERR_NOERR != result)
  {

    return result;
  }
  
  /* Open the result file */
  fpResult = fopen(resultFileName, fOpenMode);

  if(NULL == fpResult)
  {
    PRINT(PRINT_ERR_MSG, "%s: Error in result file open\n", __FUNCTION__);
    fprintf(fpResult, "%s : Error in result file open\n", testCaseId);
    return ERR_INVNAME;
  }

  /* OpenMax insufficient resources */
    
  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;

  err = OMX_Init ();

  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_Init");

  if(OMX_ErrorNone != err)
  {
    OMTB_OmxReturnStatusString(err, returnString);
    strcpy(testCaseResult, "FAIL - Error in OMX_Init()\n");
    fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
    fclose(fpResult);
    return ERR_INVNAME;
  }

  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;
  
  /* get component handle */
  err = OMX_GetHandle(&handle,
                      (OMX_STRING)componentRequested,
                      NULL,
                      &OMTB_APITestCallback);
  
  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_GetHandle");

  if(OMX_ErrorNone != err)
  {
    OMTB_OmxReturnStatusString(err, returnString);
    strcpy(testCaseResult, "FAIL - Error in OMX_GetHandle()\n");
    fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);

    /* API entry time calculation macro */
    OMTB_OMX_API_ENTRY_TIME_CALC;

    /* OpenMax core uninitialization */
    err = OMX_Deinit ();

    /* API exit time calculation macro */
    OMTB_OMX_API_EXIT_TIME_CALC("OMX_Deinit");
    
    if(OMX_ErrorNone != err)
    {
      OMTB_OmxReturnStatusString(err, returnString);
      strcpy(testCaseResult, "FAIL - Error in OMX_Deinit()\n");
      fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
      result = ERR_INVNAME;
    }
    
    fclose(fpResult);
    return ERR_INVNAME;
  }

  
  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;
  
  /* get component handle */
  err = OMX_GetHandle(&handle2,
                      (OMX_STRING)componentRequested2,
                      NULL,
                      &OMTB_APITestCallback);
  
  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_GetHandle");

  if(OMX_ErrorNone != err)
  {
    OMTB_OmxReturnStatusString(err, returnString);
    strcpy(testCaseResult, "FAIL - Error in OMX_GetHandle()\n");
    fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);

    /* API entry time calculation macro */
    OMTB_OMX_API_ENTRY_TIME_CALC;
    
    err = OMX_FreeHandle(handle);
    
    /* API exit time calculation macro */
    OMTB_OMX_API_EXIT_TIME_CALC("OMX_FreeHandle");
    
    if(OMX_ErrorNone != err)
    {
	OMTB_OmxReturnStatusString(err, returnString);
    strcpy(testCaseResult, "FAIL - Error in OMX_FreeHandle()\n");
    fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
      result = ERR_INVNAME;
    }
    
    /* API entry time calculation macro */
    OMTB_OMX_API_ENTRY_TIME_CALC;

    /* OpenMax core uninitialization */
    err = OMX_Deinit ();

    /* API exit time calculation macro */
    OMTB_OMX_API_EXIT_TIME_CALC("OMX_Deinit");
    
    if(OMX_ErrorNone != err)
    {
      OMTB_OmxReturnStatusString(err, returnString);
      strcpy(testCaseResult, "FAIL - Error in OMX_Deinit()\n");
      fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
      result = ERR_INVNAME;
    }
    
    fclose(fpResult);
    return ERR_INVNAME;
  }
  

  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;

  /* Setup tunnel between the specified port of two components */
  err = OMX_SetupTunnel(handle, portNo1, 
                        handle2 , portNo2);

  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_SetupTunnel");
  
  if(OMX_ErrorNotImplemented == err)
  {
    strcpy(testCaseResult, "PASS");
    fprintf(fpResult, "%s : %s\n", testCaseId, testCaseResult);
  }
  else
  {
    OMTB_OmxReturnStatusString(err, returnString);
    strcpy(testCaseResult, "FAIL");
    fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
    result = ERR_INVNAME;
  }
  
  /* free component handle */
  if(NULL != handle)
  {
    /* API entry time calculation macro */
    OMTB_OMX_API_ENTRY_TIME_CALC;
    
    err = OMX_FreeHandle(handle);
    
    /* API exit time calculation macro */
    OMTB_OMX_API_EXIT_TIME_CALC("OMX_FreeHandle");
    
    if(OMX_ErrorNone != err)
    {
	OMTB_OmxReturnStatusString(err, returnString);
    strcpy(testCaseResult, "FAIL - Error in OMX_FreeHandle()\n");
    fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
      result = ERR_INVNAME;
    }

  }

  if(NULL != handle2)
  {
    /* API entry time calculation macro */
    OMTB_OMX_API_ENTRY_TIME_CALC;
    
    err = OMX_FreeHandle(handle2);
    
    /* API exit time calculation macro */
    OMTB_OMX_API_EXIT_TIME_CALC("OMX_FreeHandle");

    if(OMX_ErrorNone != err)
    {
	OMTB_OmxReturnStatusString(err, returnString);
    strcpy(testCaseResult, "FAIL - Error in OMX_FreeHandle()\n");
    fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
      result = ERR_INVNAME;
    }
  }
  
  /* OpenMax core uninitialization */
  err = OMX_Deinit ();

  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_Deinit");

    if(OMX_ErrorNone != err)
    {
      OMTB_OmxReturnStatusString(err, returnString);
      strcpy(testCaseResult, "FAIL - Error in OMX_Deinit()\n");
      fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
      result = ERR_INVNAME;
    }

  /* close the result file */
  fclose(fpResult);
  
  return (result);
}


/******************************************************************************\
 *      OMTB_OmxSetupTunnelPortIncompatible Function Definition
\******************************************************************************/
/**
 *
 *  @brief    This Function performs OMX_SetupTunnel API testing.
 *
 *  @param    Pointer to MX_DBG_CMD_CONTEXT_T structure
 *            Pointer to MX_DBG_CMD_Entry_T structure
 *            Character Double Pointer containing the command
 *
 *  @return   ERR_NOERR           successful,
 *            ERR_END_OF_CMD      help was requested,
 *            ERR_INVNAME         otherwise.
 */

MX_Result
OMTB_OmxSetupTunnelPortIncompatible(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine
)
{
  MX_Result  result = ERR_NOERR;
  OMX_ERRORTYPE err = OMX_ErrorNone;
  char componentRequested[OMTB_MAX_LEN] = {"\0"};
  char resultFileName[OMTB_MAX_LEN] = {"\0"};
  char fOpenMode[OMTB_MAX_LEN] = {"\0"};
  char testCaseId[OMTB_MAX_LEN] = {"\0"};
  char testCaseResult[OMTB_MAX_LEN] = {"\0"}; char returnString[OMTB_MAX_LEN] = {"\0"};
  FILE *fpResult = NULL;
  char componentRequested2[OMTB_MAX_LEN] = {"\0"};
  int portNo1 = 0, portNo2 = 0;
  OMX_HANDLETYPE handle, handle2;                  /* Component handle */
  OMTB_OMX_API_TIMING_VAR_DECL;

  /* Read testcase ID */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, testCaseId);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }
  
  /* Read first component name */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, componentRequested);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }

  /* Read result filename */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, resultFileName);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }

  /* Read result file type */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, fOpenMode);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }

  /* Read port number */
  result = XdbgCmdNextNum(pContext, pCmdEntry, ppCmdLine, (UINT32*)&portNo1);
  if (ERR_NOERR != result)
  {

    return result;
  }
  
  /* Read second component name */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, componentRequested2);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }

  /* Read port number */
  result = XdbgCmdNextNum(pContext, pCmdEntry, ppCmdLine, (UINT32*)&portNo2);
  if (ERR_NOERR != result)
  {

    return result;
  }
  
  /* Open the result file */
  fpResult = fopen(resultFileName, fOpenMode);

  if(NULL == fpResult)
  {
    PRINT(PRINT_ERR_MSG, "%s: Error in result file open\n", __FUNCTION__);
    fprintf(fpResult, "%s : Error in result file open\n", testCaseId);
    return ERR_INVNAME;
  }

  /* OpenMax insufficient resources */
    
  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;

  err = OMX_Init ();

  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_Init");

  if(OMX_ErrorNone != err)
  {
    OMTB_OmxReturnStatusString(err, returnString);
    strcpy(testCaseResult, "FAIL - Error in OMX_Init()\n");
    fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
    fclose(fpResult);
    return ERR_INVNAME;
  }

  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;
  
  /* get component handle */
  err = OMX_GetHandle(&handle,
                      (OMX_STRING)componentRequested,
                      NULL,
                      &OMTB_APITestCallback);
  
  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_GetHandle");

  if(OMX_ErrorNone != err)
  {
    OMTB_OmxReturnStatusString(err, returnString);
    strcpy(testCaseResult, "FAIL - Error in OMX_GetHandle()\n");
    fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);

    /* API entry time calculation macro */
    OMTB_OMX_API_ENTRY_TIME_CALC;

    /* OpenMax core uninitialization */
    err = OMX_Deinit ();

    /* API exit time calculation macro */
    OMTB_OMX_API_EXIT_TIME_CALC("OMX_Deinit");
    
    if(OMX_ErrorNone != err)
    {
      OMTB_OmxReturnStatusString(err, returnString);
      strcpy(testCaseResult, "FAIL - Error in OMX_Deinit()\n");
      fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
      result = ERR_INVNAME;
    }
    
    fclose(fpResult);
    return ERR_INVNAME;
  }

  
  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;
  
  /* get component handle */
  err = OMX_GetHandle(&handle2,
                      (OMX_STRING)componentRequested2,
                      NULL,
                      &OMTB_APITestCallback);
  
  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_GetHandle");

  if(OMX_ErrorNone != err)
  {
    OMTB_OmxReturnStatusString(err, returnString);
    strcpy(testCaseResult, "FAIL - Error in OMX_GetHandle()\n");
    fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);

    /* API entry time calculation macro */
    OMTB_OMX_API_ENTRY_TIME_CALC;
    
    err = OMX_FreeHandle(handle);
    
    /* API exit time calculation macro */
    OMTB_OMX_API_EXIT_TIME_CALC("OMX_FreeHandle");
    
    if(OMX_ErrorNone != err)
    {
	OMTB_OmxReturnStatusString(err, returnString);
    strcpy(testCaseResult, "FAIL - Error in OMX_FreeHandle()\n");
    fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
      result = ERR_INVNAME;
    }
    
    /* API entry time calculation macro */
    OMTB_OMX_API_ENTRY_TIME_CALC;

    /* OpenMax core uninitialization */
    err = OMX_Deinit ();

    /* API exit time calculation macro */
    OMTB_OMX_API_EXIT_TIME_CALC("OMX_Deinit");
    
    if(OMX_ErrorNone != err)
    {
      OMTB_OmxReturnStatusString(err, returnString);
      strcpy(testCaseResult, "FAIL - Error in OMX_Deinit()\n");
      fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
      result = ERR_INVNAME;
    }
    
    fclose(fpResult);
    return ERR_INVNAME;
  }
  

  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;

  /* Setup tunnel between the specified port of two components */
  err = OMX_SetupTunnel(handle, portNo1, 
                        handle2 , portNo2);

  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_SetupTunnel");
  
  if(OMX_ErrorPortsNotCompatible == err)
  {
    strcpy(testCaseResult, "PASS");
    fprintf(fpResult, "%s : %s\n", testCaseId, testCaseResult);
  }
  else
  {
    OMTB_OmxReturnStatusString(err, returnString);
    strcpy(testCaseResult, "FAIL");
    fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
    result = ERR_INVNAME;
  }
  
  /* free component handle */
  if(NULL != handle)
  {
    /* API entry time calculation macro */
    OMTB_OMX_API_ENTRY_TIME_CALC;
    
    err = OMX_FreeHandle(handle);
    
    /* API exit time calculation macro */
    OMTB_OMX_API_EXIT_TIME_CALC("OMX_FreeHandle");
    
    if(OMX_ErrorNone != err)
    {
	OMTB_OmxReturnStatusString(err, returnString);
    strcpy(testCaseResult, "FAIL - Error in OMX_FreeHandle()\n");
    fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
      result = ERR_INVNAME;
    }

  }

  if(NULL != handle2)
  {
    /* API entry time calculation macro */
    OMTB_OMX_API_ENTRY_TIME_CALC;
    
    err = OMX_FreeHandle(handle2);
    
    /* API exit time calculation macro */
    OMTB_OMX_API_EXIT_TIME_CALC("OMX_FreeHandle");

    if(OMX_ErrorNone != err)
    {
	OMTB_OmxReturnStatusString(err, returnString);
    strcpy(testCaseResult, "FAIL - Error in OMX_FreeHandle()\n");
    fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
      result = ERR_INVNAME;
    }
  }

  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;
  
  /* OpenMax core uninitialization */
  err = OMX_Deinit ();

  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_Deinit");

    if(OMX_ErrorNone != err)
    {
      OMTB_OmxReturnStatusString(err, returnString);
      strcpy(testCaseResult, "FAIL - Error in OMX_Deinit()\n");
      fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
      result = ERR_INVNAME;
    }

  /* close the result file */
  fclose(fpResult);
  
  return (result);
}


/******************************************************************************\
 *      OMTB_OmxSetupTunnelVerMismatch Function Definition
\******************************************************************************/
/**
 *
 *  @brief    This Function performs OMX_SetupTunnel API testing.
 *
 *  @param    Pointer to MX_DBG_CMD_CONTEXT_T structure
 *            Pointer to MX_DBG_CMD_Entry_T structure
 *            Character Double Pointer containing the command
 *
 *  @return   ERR_NOERR           successful,
 *            ERR_END_OF_CMD      help was requested,
 *            ERR_INVNAME         otherwise.
 */

MX_Result
OMTB_OmxSetupTunnelVerMismatch(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine
)
{
  MX_Result  result = ERR_NOERR;
  OMX_ERRORTYPE err = OMX_ErrorNone;
  char componentRequested[OMTB_MAX_LEN] = {"\0"};
  char resultFileName[OMTB_MAX_LEN] = {"\0"};
  char fOpenMode[OMTB_MAX_LEN] = {"\0"};
  char testCaseId[OMTB_MAX_LEN] = {"\0"};
  char testCaseResult[OMTB_MAX_LEN] = {"\0"}; char returnString[OMTB_MAX_LEN] = {"\0"};
  FILE *fpResult = NULL;
  char componentRequested2[OMTB_MAX_LEN] = {"\0"};
  int portNo1 = 0, portNo2 = 0;
  OMX_HANDLETYPE handle, handle2;                  /* Component handle */
  OMTB_OMX_API_TIMING_VAR_DECL;

  /* Read testcase ID */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, testCaseId);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }
  
  /* Read first component name */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, componentRequested);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }

  /* Read result filename */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, resultFileName);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }

  /* Read result file type */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, fOpenMode);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }

  /* Read port number */
  result = XdbgCmdNextNum(pContext, pCmdEntry, ppCmdLine, (UINT32*)&portNo1);
  if (ERR_NOERR != result)
  {

    return result;
  }
  
  /* Read second component name */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, componentRequested2);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }

  /* Read port number */
  result = XdbgCmdNextNum(pContext, pCmdEntry, ppCmdLine, (UINT32*)&portNo2);
  if (ERR_NOERR != result)
  {

    return result;
  }
  
  /* Open the result file */
  fpResult = fopen(resultFileName, fOpenMode);

  if(NULL == fpResult)
  {
    PRINT(PRINT_ERR_MSG, "%s: Error in result file open\n", __FUNCTION__);
    fprintf(fpResult, "%s : Error in result file open\n", testCaseId);
    return ERR_INVNAME;
  }

  /* OpenMax insufficient resources */
    
  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;

  err = OMX_Init ();

  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_Init");

  if(OMX_ErrorNone != err)
  {
    OMTB_OmxReturnStatusString(err, returnString);
    strcpy(testCaseResult, "FAIL - Error in OMX_Init()\n");
    fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
    fclose(fpResult);
    return ERR_INVNAME;
  }

  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;
  
  /* get component handle */
  err = OMX_GetHandle(&handle,
                      (OMX_STRING)componentRequested,
                      NULL,
                      &OMTB_APITestCallback);
  
  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_GetHandle");

  if(OMX_ErrorNone != err)
  {
    OMTB_OmxReturnStatusString(err, returnString);
    strcpy(testCaseResult, "FAIL - Error in OMX_GetHandle()\n");
    fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);

    /* API entry time calculation macro */
    OMTB_OMX_API_ENTRY_TIME_CALC;

    /* OpenMax core uninitialization */
    err = OMX_Deinit ();

    /* API exit time calculation macro */
    OMTB_OMX_API_EXIT_TIME_CALC("OMX_Deinit");
    
    if(OMX_ErrorNone != err)
    {
      OMTB_OmxReturnStatusString(err, returnString);
      strcpy(testCaseResult, "FAIL - Error in OMX_Deinit()\n");
      fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
      result = ERR_INVNAME;
    }
    
    fclose(fpResult);
    return ERR_INVNAME;
  }

  
  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;
  
  /* get component handle */
  err = OMX_GetHandle(&handle2,
                      (OMX_STRING)componentRequested2,
                      NULL,
                      &OMTB_APITestCallback);
  
  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_GetHandle");

  if(OMX_ErrorNone != err)
  {
    OMTB_OmxReturnStatusString(err, returnString);
    strcpy(testCaseResult, "FAIL - Error in OMX_GetHandle()\n");
    fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);

    /* API entry time calculation macro */
    OMTB_OMX_API_ENTRY_TIME_CALC;
    
    err = OMX_FreeHandle(handle);
    
    /* API exit time calculation macro */
    OMTB_OMX_API_EXIT_TIME_CALC("OMX_FreeHandle");
    
    if(OMX_ErrorNone != err)
    {
	OMTB_OmxReturnStatusString(err, returnString);
    strcpy(testCaseResult, "FAIL - Error in OMX_FreeHandle()\n");
    fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
      result = ERR_INVNAME;
    }
    
    /* API entry time calculation macro */
    OMTB_OMX_API_ENTRY_TIME_CALC;

    /* OpenMax core uninitialization */
    err = OMX_Deinit ();

    /* API exit time calculation macro */
    OMTB_OMX_API_EXIT_TIME_CALC("OMX_Deinit");
    
    if(OMX_ErrorNone != err)
    {
      OMTB_OmxReturnStatusString(err, returnString);
      strcpy(testCaseResult, "FAIL - Error in OMX_Deinit()\n");
      fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
      result = ERR_INVNAME;
    }

    
    fclose(fpResult);
    return ERR_INVNAME;
  }
  

  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;

  /* Setup tunnel between the specified port of two components */
  err = OMX_SetupTunnel(handle, portNo1, 
                        handle2 , portNo2);

  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_SetupTunnel");
  
  if(OMX_ErrorVersionMismatch == err)
  {
    strcpy(testCaseResult, "PASS");
    fprintf(fpResult, "%s : %s\n", testCaseId, testCaseResult);
  }
  else
  {
    OMTB_OmxReturnStatusString(err, returnString);
    strcpy(testCaseResult, "FAIL");
    fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
    result = ERR_INVNAME;
  }
  
  /* free component handle */
  if(NULL != handle)
  {
    /* API entry time calculation macro */
    OMTB_OMX_API_ENTRY_TIME_CALC;
    
    err = OMX_FreeHandle(handle);
    
    /* API exit time calculation macro */
    OMTB_OMX_API_EXIT_TIME_CALC("OMX_FreeHandle");
    
    if(OMX_ErrorNone != err)
    {
	OMTB_OmxReturnStatusString(err, returnString);
    strcpy(testCaseResult, "FAIL - Error in OMX_FreeHandle()\n");
    fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
      result = ERR_INVNAME;
    }

  }

  if(NULL != handle2)
  {
    /* API entry time calculation macro */
    OMTB_OMX_API_ENTRY_TIME_CALC;
    
    err = OMX_FreeHandle(handle2);
    
    /* API exit time calculation macro */
    OMTB_OMX_API_EXIT_TIME_CALC("OMX_FreeHandle");

    if(OMX_ErrorNone != err)
    {
	OMTB_OmxReturnStatusString(err, returnString);
    strcpy(testCaseResult, "FAIL - Error in OMX_FreeHandle()\n");
    fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
      result = ERR_INVNAME;
    }
  }

  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;
  
  /* OpenMax core uninitialization */
  err = OMX_Deinit ();

  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_Deinit");

    if(OMX_ErrorNone != err)
    {
      OMTB_OmxReturnStatusString(err, returnString);
      strcpy(testCaseResult, "FAIL - Error in OMX_Deinit()\n");
      fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
      result = ERR_INVNAME;
    }

  /* close the result file */
  fclose(fpResult);
  
  return (result);
}


/******************************************************************************\
 *      OMTB_OmxSetupTunnelTimeOut Function Definition
\******************************************************************************/
/**
 *
 *  @brief    This Function performs OMX_SetupTunnel API testing.
 *
 *  @param    Pointer to MX_DBG_CMD_CONTEXT_T structure
 *            Pointer to MX_DBG_CMD_Entry_T structure
 *            Character Double Pointer containing the command
 *
 *  @return   ERR_NOERR           successful,
 *            ERR_END_OF_CMD      help was requested,
 *            ERR_INVNAME         otherwise.
 */

MX_Result
OMTB_OmxSetupTunnelTimeOut(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine
)
{
  MX_Result  result = ERR_NOERR;
  OMX_ERRORTYPE err = OMX_ErrorNone;
  char componentRequested[OMTB_MAX_LEN] = {"\0"};
  char resultFileName[OMTB_MAX_LEN] = {"\0"};
  char fOpenMode[OMTB_MAX_LEN] = {"\0"};
  char testCaseId[OMTB_MAX_LEN] = {"\0"};
  char testCaseResult[OMTB_MAX_LEN] = {"\0"}; char returnString[OMTB_MAX_LEN] = {"\0"};
  FILE *fpResult = NULL;
  char componentRequested2[OMTB_MAX_LEN] = {"\0"};
  int portNo1 = 0, portNo2 = 0;
  OMX_HANDLETYPE handle, handle2;                  /* Component handle */
  OMTB_OMX_API_TIMING_VAR_DECL;

  /* Read testcase ID */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, testCaseId);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }
  
  /* Read first component name */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, componentRequested);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }

  /* Read result filename */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, resultFileName);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }

  /* Read result file type */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, fOpenMode);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }

  /* Read port number */
  result = XdbgCmdNextNum(pContext, pCmdEntry, ppCmdLine, (UINT32*)&portNo1);
  if (ERR_NOERR != result)
  {

    return result;
  }
  
  /* Read second component name */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, componentRequested2);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }

  /* Read port number */
  result = XdbgCmdNextNum(pContext, pCmdEntry, ppCmdLine, (UINT32*)&portNo2);
  if (ERR_NOERR != result)
  {

    return result;
  }
  
  /* Open the result file */
  fpResult = fopen(resultFileName, fOpenMode);

  if(NULL == fpResult)
  {
    PRINT(PRINT_ERR_MSG, "%s: Error in result file open\n", __FUNCTION__);
    fprintf(fpResult, "%s : Error in result file open\n", testCaseId);
    return ERR_INVNAME;
  }

  /* OpenMax insufficient resources */
    
  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;

  err = OMX_Init ();

  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_Init");

  if(OMX_ErrorNone != err)
  {
    OMTB_OmxReturnStatusString(err, returnString);
    strcpy(testCaseResult, "FAIL - Error in OMX_Init()\n");
    fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
    fclose(fpResult);
    return ERR_INVNAME;
  }

  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;
  
  /* get component handle */
  err = OMX_GetHandle(&handle,
                      (OMX_STRING)componentRequested,
                      NULL,
                      &OMTB_APITestCallback);
  
  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_GetHandle");

  if(OMX_ErrorNone != err)
  {
    OMTB_OmxReturnStatusString(err, returnString);
    strcpy(testCaseResult, "FAIL - Error in OMX_GetHandle()\n");
    fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);

    /* API entry time calculation macro */
    OMTB_OMX_API_ENTRY_TIME_CALC;

    /* OpenMax core uninitialization */
    err = OMX_Deinit ();

    /* API exit time calculation macro */
    OMTB_OMX_API_EXIT_TIME_CALC("OMX_Deinit");
    
    if(OMX_ErrorNone != err)
    {
      OMTB_OmxReturnStatusString(err, returnString);
      strcpy(testCaseResult, "FAIL - Error in OMX_Deinit()\n");
      fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
      result = ERR_INVNAME;
    }
    
    fclose(fpResult);
    return ERR_INVNAME;
  }

  
  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;
  
  /* get component handle */
  err = OMX_GetHandle(&handle2,
                      (OMX_STRING)componentRequested2,
                      NULL,
                      &OMTB_APITestCallback);
  
  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_GetHandle");

  if(OMX_ErrorNone != err)
  {
    OMTB_OmxReturnStatusString(err, returnString);
    strcpy(testCaseResult, "FAIL - Error in OMX_GetHandle()\n");
    fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);

    /* API entry time calculation macro */
    OMTB_OMX_API_ENTRY_TIME_CALC;
    
    err = OMX_FreeHandle(handle);
    
    /* API exit time calculation macro */
    OMTB_OMX_API_EXIT_TIME_CALC("OMX_FreeHandle");
    
    if(OMX_ErrorNone != err)
    {
	OMTB_OmxReturnStatusString(err, returnString);
    strcpy(testCaseResult, "FAIL - Error in OMX_FreeHandle()\n");
    fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
      result = ERR_INVNAME;
    }
    
    /* API entry time calculation macro */
    OMTB_OMX_API_ENTRY_TIME_CALC;

    /* OpenMax core uninitialization */
    err = OMX_Deinit ();

    /* API exit time calculation macro */
    OMTB_OMX_API_EXIT_TIME_CALC("OMX_Deinit");
    
    if(OMX_ErrorNone != err)
    {
      OMTB_OmxReturnStatusString(err, returnString);
      strcpy(testCaseResult, "FAIL - Error in OMX_Deinit()\n");
      fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
      result = ERR_INVNAME;
    }
    
    fclose(fpResult);
    return ERR_INVNAME;
  }
  

  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;

  /* Setup tunnel between the specified port of two components */
  err = OMX_SetupTunnel(handle, portNo1, 
                        handle2 , portNo2);

  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_SetupTunnel");
  
  if(OMX_ErrorTimeout == err)
  {
    strcpy(testCaseResult, "PASS");
    fprintf(fpResult, "%s : %s\n", testCaseId, testCaseResult);
  }
  else
  {
    OMTB_OmxReturnStatusString(err, returnString);
    strcpy(testCaseResult, "FAIL");
    fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
    result = ERR_INVNAME;
  }
  
  /* free component handle */
  if(NULL != handle)
  {
    /* API entry time calculation macro */
    OMTB_OMX_API_ENTRY_TIME_CALC;
    
    err = OMX_FreeHandle(handle);
    
    /* API exit time calculation macro */
    OMTB_OMX_API_EXIT_TIME_CALC("OMX_FreeHandle");
    
    if(OMX_ErrorNone != err)
    {
	OMTB_OmxReturnStatusString(err, returnString);
    strcpy(testCaseResult, "FAIL - Error in OMX_FreeHandle()\n");
    fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
      result = ERR_INVNAME;
    }

  }

  if(NULL != handle2)
  {
    /* API entry time calculation macro */
    OMTB_OMX_API_ENTRY_TIME_CALC;
    
    err = OMX_FreeHandle(handle2);
    
    /* API exit time calculation macro */
    OMTB_OMX_API_EXIT_TIME_CALC("OMX_FreeHandle");

    if(OMX_ErrorNone != err)
    {
	OMTB_OmxReturnStatusString(err, returnString);
    strcpy(testCaseResult, "FAIL - Error in OMX_FreeHandle()\n");
    fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
      result = ERR_INVNAME;
    }
  }

  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;
  
  /* OpenMax core uninitialization */
  err = OMX_Deinit ();

  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_Deinit");

    if(OMX_ErrorNone != err)
    {
      OMTB_OmxReturnStatusString(err, returnString);
      strcpy(testCaseResult, "FAIL - Error in OMX_Deinit()\n");
      fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
      result = ERR_INVNAME;
    }

  /* close the result file */
  fclose(fpResult);
  
  return (result);
}


/******************************************************************************\
 *      OMTB_OmxSendCommandOnce Function Definition
\******************************************************************************/
/**
 *
 *  @brief    This Function performs OMX_SendCommand API testing.
 *
 *  @param    Pointer to MX_DBG_CMD_CONTEXT_T structure
 *            Pointer to MX_DBG_CMD_Entry_T structure
 *            Character Double Pointer containing the command
 *
 *  @return   ERR_NOERR           successful,
 *            ERR_END_OF_CMD      help was requested,
 *            ERR_INVNAME         otherwise.
 */

MX_Result
OMTB_OmxSendCommandOnce(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine
)
{
  MX_Result  result = ERR_NOERR;
  OMX_ERRORTYPE err = OMX_ErrorNone;
  char componentRequested[OMTB_MAX_LEN] = {"\0"};
  char resultFileName[OMTB_MAX_LEN] = {"\0"};
  char fOpenMode[OMTB_MAX_LEN] = {"\0"};
  char testCaseId[OMTB_MAX_LEN] = {"\0"};
  char testCaseResult[OMTB_MAX_LEN] = {"\0"}; char returnString[OMTB_MAX_LEN] = {"\0"};
  FILE *fpResult = NULL;
  OMX_HANDLETYPE handle = NULL;                  /* Component handle */
  int nParam = 0;
  OMX_PTR pCmdData = NULL;
  OMX_COMMANDTYPE commandType = OMX_CommandMax;
  OMTB_OMX_API_TIMING_VAR_DECL;

  /* Read testcase ID */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, testCaseId);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }
  
  /* Read component name */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, componentRequested);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }

  /* Read result filename */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, resultFileName);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }

  /* Read result file type */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, fOpenMode);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }

  /* Read port Number */
  result = XdbgCmdNextNum(pContext, pCmdEntry, ppCmdLine, (UINT32 *)&nParam);
  if (ERR_NOERR != result)
  {
    return result;
  }

  /* set the flush command */
  commandType = OMX_CommandFlush;
  pCmdData = NULL;

  /* Open the result file */
  fpResult = fopen(resultFileName, fOpenMode);

  if(NULL == fpResult)
  {
    PRINT(PRINT_ERR_MSG, "%s: Error in result file open\n", __FUNCTION__);
    fprintf(fpResult, "%s : Error in result file open\n", testCaseId);
    return ERR_INVNAME;
  }

  /* OpenMax insufficient resources */
    
  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;

  err = OMX_Init ();

  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_Init");

  if(OMX_ErrorNone != err)
  {
    OMTB_OmxReturnStatusString(err, returnString);
    strcpy(testCaseResult, "FAIL - Error in OMX_Init()\n");
    fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
    fclose(fpResult);
    return ERR_INVNAME;
  }

  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;
  
  /* get component handle */
  err = OMX_GetHandle(&handle,
                      (OMX_STRING)componentRequested,
                      NULL,
                      &OMTB_APITestCallback);
  
  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_GetHandle");

  if(OMX_ErrorNone != err)
  {
    OMTB_OmxReturnStatusString(err, returnString);
    strcpy(testCaseResult, "FAIL - Error in OMX_GetHandle()\n");
    fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);

    /* API entry time calculation macro */
    OMTB_OMX_API_ENTRY_TIME_CALC;

    /* OpenMax core uninitialization */
    err = OMX_Deinit ();

    /* API exit time calculation macro */
    OMTB_OMX_API_EXIT_TIME_CALC("OMX_Deinit");
    
    if(OMX_ErrorNone != err)
    {
      OMTB_OmxReturnStatusString(err, returnString);
      strcpy(testCaseResult, "FAIL - Error in OMX_Deinit()\n");
      fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
      result = ERR_INVNAME;
    }
    
    fclose(fpResult);
    return ERR_INVNAME;
  }

  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;

  /* sending command to component to flush the buffer on specified port */
  err = OMX_SendCommand(handle, commandType, nParam, pCmdData);

  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_SendCommand - OMX_CommandFlush");
  
  if(OMX_ErrorNone == err)
  {
    strcpy(testCaseResult, "PASS");
    fprintf(fpResult, "%s : %s\n", testCaseId, testCaseResult);
  }
  else
  {
    OMTB_OmxReturnStatusString(err, returnString);
    strcpy(testCaseResult, "FAIL");
    fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
    result = ERR_INVNAME;
  }
  
  /* free component handle */
  if(NULL != handle)
  {
    /* API entry time calculation macro */
    OMTB_OMX_API_ENTRY_TIME_CALC;
    
    err = OMX_FreeHandle(handle);
    
    /* API exit time calculation macro */
    OMTB_OMX_API_EXIT_TIME_CALC("OMX_FreeHandle");
    
    if(OMX_ErrorNone != err)
    {
	OMTB_OmxReturnStatusString(err, returnString);
    strcpy(testCaseResult, "FAIL - Error in OMX_FreeHandle()\n");
    fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);

      result = ERR_INVNAME;
    }
    
  }

  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;
  
  /* OpenMax core uninitialization */
  err = OMX_Deinit ();

  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_Deinit");

    if(OMX_ErrorNone != err)
    {
      OMTB_OmxReturnStatusString(err, returnString);
      strcpy(testCaseResult, "FAIL - Error in OMX_Deinit()\n");
      fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
      result = ERR_INVNAME;
    }

  /* close the result file */
  fclose(fpResult);
  
  return (result);
}


/******************************************************************************\
 *      OMTB_OmxSendCommandInsuffResources Function Definition
\******************************************************************************/
/**
 *
 *  @brief    This Function performs OMX_SendCommand API testing.
 *
 *  @param    Pointer to MX_DBG_CMD_CONTEXT_T structure
 *            Pointer to MX_DBG_CMD_Entry_T structure
 *            Character Double Pointer containing the command
 *
 *  @return   ERR_NOERR           successful,
 *            ERR_END_OF_CMD      help was requested,
 *            ERR_INVNAME         otherwise.
 */

MX_Result
OMTB_OmxSendCommandInsuffResources(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine
)
{
  MX_Result  result = ERR_NOERR;
  OMX_ERRORTYPE err = OMX_ErrorNone;
  char componentRequested[OMTB_MAX_LEN] = {"\0"};
  char resultFileName[OMTB_MAX_LEN] = {"\0"};
  char fOpenMode[OMTB_MAX_LEN] = {"\0"};
  char testCaseId[OMTB_MAX_LEN] = {"\0"};
  char testCaseResult[OMTB_MAX_LEN] = {"\0"}; char returnString[OMTB_MAX_LEN] = {"\0"};
  FILE *fpResult = NULL;
  OMX_HANDLETYPE handle = NULL;                  /* Component handle */
  int nParam = 0;
  OMX_PTR pCmdData = NULL;
  OMX_COMMANDTYPE commandType = OMX_CommandMax;
  OMTB_OMX_API_TIMING_VAR_DECL;

  /* Read testcase ID */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, testCaseId);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }
  
  /* Read component name */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, componentRequested);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }

  /* Read result filename */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, resultFileName);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }

  /* Read result file type */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, fOpenMode);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }

  /* Read port Number */
  result = XdbgCmdNextNum(pContext, pCmdEntry, ppCmdLine, (UINT32 *)&nParam);
  if (ERR_NOERR != result)
  {
    return result;
  }

  /* set the flush command */
  commandType = OMX_CommandFlush;
  pCmdData = NULL;

  /* Open the result file */
  fpResult = fopen(resultFileName, fOpenMode);

  if(NULL == fpResult)
  {
    PRINT(PRINT_ERR_MSG, "%s: Error in result file open\n", __FUNCTION__);
    fprintf(fpResult, "%s : Error in result file open\n", testCaseId);
    return ERR_INVNAME;
  }

  /* OpenMax insufficient resources */
    
  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;

  err = OMX_Init ();

  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_Init");

  if(OMX_ErrorNone != err)
  {
    OMTB_OmxReturnStatusString(err, returnString);
    strcpy(testCaseResult, "FAIL - Error in OMX_Init()\n");
    fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
    fclose(fpResult);
    return ERR_INVNAME;
  }

  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;
  
  /* get component handle */
  err = OMX_GetHandle(&handle,
                      (OMX_STRING)componentRequested,
                      NULL,
                      &OMTB_APITestCallback);
  
  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_GetHandle");

  if(OMX_ErrorNone != err)
  {
    OMTB_OmxReturnStatusString(err, returnString);
    strcpy(testCaseResult, "FAIL - Error in OMX_GetHandle()\n");
    fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);

    /* API entry time calculation macro */
    OMTB_OMX_API_ENTRY_TIME_CALC;

    /* OpenMax core uninitialization */
    err = OMX_Deinit ();

    /* API exit time calculation macro */
    OMTB_OMX_API_EXIT_TIME_CALC("OMX_Deinit");
    
    if(OMX_ErrorNone != err)
    {
      OMTB_OmxReturnStatusString(err, returnString);
      strcpy(testCaseResult, "FAIL - Error in OMX_Deinit()\n");
      fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
      result = ERR_INVNAME;
    }
    
    fclose(fpResult);
    return ERR_INVNAME;
  }

  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;

  /* sending command to component to flush the buffer on specified port */
  err = OMX_SendCommand(handle, commandType, nParam, pCmdData);

  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_SendCommand - OMX_CommandFlush");
  
  if(OMX_ErrorInsufficientResources == err)
  {
    strcpy(testCaseResult, "PASS");
    fprintf(fpResult, "%s : %s\n", testCaseId, testCaseResult);
  }
  else
  {
    OMTB_OmxReturnStatusString(err, returnString);
    strcpy(testCaseResult, "FAIL");
    fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
    result = ERR_INVNAME;
  }
  
  /* free component handle */
  if(NULL != handle)
  {
    /* API entry time calculation macro */
    OMTB_OMX_API_ENTRY_TIME_CALC;
    
    err = OMX_FreeHandle(handle);
    
    /* API exit time calculation macro */
    OMTB_OMX_API_EXIT_TIME_CALC("OMX_FreeHandle");
    
    if(OMX_ErrorNone != err)
    {
	OMTB_OmxReturnStatusString(err, returnString);
    strcpy(testCaseResult, "FAIL - Error in OMX_FreeHandle()\n");
    fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);

      result = ERR_INVNAME;
    }
    
  }

  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;
  
  /* OpenMax core uninitialization */
  err = OMX_Deinit ();

  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_Deinit");

    if(OMX_ErrorNone != err)
    {
      OMTB_OmxReturnStatusString(err, returnString);
      strcpy(testCaseResult, "FAIL - Error in OMX_Deinit()\n");
      fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
      result = ERR_INVNAME;
    }

  /* close the result file */
  fclose(fpResult);
  
  return (result);
}


/******************************************************************************\
 *      OMTB_OmxSendCommandNullHandle Function Definition
\******************************************************************************/
/**
 *
 *  @brief    This Function performs OMX_SendCommand API testing.
 *
 *  @param    Pointer to MX_DBG_CMD_CONTEXT_T structure
 *            Pointer to MX_DBG_CMD_Entry_T structure
 *            Character Double Pointer containing the command
 *
 *  @return   ERR_NOERR           successful,
 *            ERR_END_OF_CMD      help was requested,
 *            ERR_INVNAME         otherwise.
 */

MX_Result
OMTB_OmxSendCommandNullHandle(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine
)
{
  MX_Result  result = ERR_NOERR;
  OMX_ERRORTYPE err = OMX_ErrorNone;
  char componentRequested[OMTB_MAX_LEN] = {"\0"};
  char resultFileName[OMTB_MAX_LEN] = {"\0"};
  char fOpenMode[OMTB_MAX_LEN] = {"\0"};
  char testCaseId[OMTB_MAX_LEN] = {"\0"};
  char testCaseResult[OMTB_MAX_LEN] = {"\0"}; char returnString[OMTB_MAX_LEN] = {"\0"};
  FILE *fpResult = NULL;
  OMX_HANDLETYPE handle = NULL;                  /* Component handle */
  int nParam = 0;
  OMX_PTR pCmdData = NULL;
  OMX_COMMANDTYPE commandType = OMX_CommandMax;
  OMTB_OMX_API_TIMING_VAR_DECL;

  /* Read testcase ID */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, testCaseId);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }
  
  /* Read component name */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, componentRequested);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }

  /* Read result filename */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, resultFileName);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }

  /* Read result file type */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, fOpenMode);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }

  /* Read port Number */
  result = XdbgCmdNextNum(pContext, pCmdEntry, ppCmdLine, (UINT32 *)&nParam);
  if (ERR_NOERR != result)
  {
    return result;
  }

  /* set the flush command */
  commandType = OMX_CommandFlush;
  pCmdData = NULL;

  /* Open the result file */
  fpResult = fopen(resultFileName, fOpenMode);

  if(NULL == fpResult)
  {
    PRINT(PRINT_ERR_MSG, "%s: Error in result file open\n", __FUNCTION__);
    fprintf(fpResult, "%s : Error in result file open\n", testCaseId);
    return ERR_INVNAME;
  }

  /* OpenMax insufficient resources */
    
  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;

  err = OMX_Init ();

  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_Init");

  if(OMX_ErrorNone != err)
  {
    OMTB_OmxReturnStatusString(err, returnString);
    strcpy(testCaseResult, "FAIL - Error in OMX_Init()\n");
    fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
    fclose(fpResult);
    return ERR_INVNAME;
  }

  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;
  
  /* get component handle */
  err = OMX_GetHandle(&handle,
                      (OMX_STRING)componentRequested,
                      NULL,
                      &OMTB_APITestCallback);
  
  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_GetHandle");

  if(OMX_ErrorNone != err)
  {
    OMTB_OmxReturnStatusString(err, returnString);
    strcpy(testCaseResult, "FAIL - Error in OMX_GetHandle()\n");
    fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);

    /* API entry time calculation macro */
    OMTB_OMX_API_ENTRY_TIME_CALC;

    /* OpenMax core uninitialization */
    err = OMX_Deinit ();

    /* API exit time calculation macro */
    OMTB_OMX_API_EXIT_TIME_CALC("OMX_Deinit");
    
    if(OMX_ErrorNone != err)
    {
      OMTB_OmxReturnStatusString(err, returnString);
      strcpy(testCaseResult, "FAIL - Error in OMX_Deinit()\n");
      fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
      result = ERR_INVNAME;
    }
    
    fclose(fpResult);
    return ERR_INVNAME;
  }

  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;

  /* sending command to component to flush the buffer on specified port */
  err = OMX_SendCommand(NULL, commandType, nParam, pCmdData);

  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_SendCommand - OMX_CommandFlush");
  
  if(OMX_ErrorBadParameter == err)
  {
    strcpy(testCaseResult, "PASS");
    fprintf(fpResult, "%s : %s\n", testCaseId, testCaseResult);
  }
  else
  {
    OMTB_OmxReturnStatusString(err, returnString);
    strcpy(testCaseResult, "FAIL");
    fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
    result = ERR_INVNAME;
  }
  
  /* free component handle */
  if(NULL != handle)
  {
    /* API entry time calculation macro */
    OMTB_OMX_API_ENTRY_TIME_CALC;
    
    err = OMX_FreeHandle(handle);
    
    /* API exit time calculation macro */
    OMTB_OMX_API_EXIT_TIME_CALC("OMX_FreeHandle");
    
    if(OMX_ErrorNone != err)
    {
	OMTB_OmxReturnStatusString(err, returnString);
    strcpy(testCaseResult, "FAIL - Error in OMX_FreeHandle()\n");
    fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);

      result = ERR_INVNAME;
    }
    
  }

  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;
  
  /* OpenMax core uninitialization */
  err = OMX_Deinit ();

  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_Deinit");

    if(OMX_ErrorNone != err)
    {
      OMTB_OmxReturnStatusString(err, returnString);
      strcpy(testCaseResult, "FAIL - Error in OMX_Deinit()\n");
      fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
      result = ERR_INVNAME;
    }

  /* close the result file */
  fclose(fpResult);
  
  return (result);
}


/******************************************************************************\
 *      OMTB_OmxSendCommandInvCommand Function Definition
\******************************************************************************/
/**
 *
 *  @brief    This Function performs OMX_SendCommand API testing.
 *
 *  @param    Pointer to MX_DBG_CMD_CONTEXT_T structure
 *            Pointer to MX_DBG_CMD_Entry_T structure
 *            Character Double Pointer containing the command
 *
 *  @return   ERR_NOERR           successful,
 *            ERR_END_OF_CMD      help was requested,
 *            ERR_INVNAME         otherwise.
 */

MX_Result
OMTB_OmxSendCommandInvCommand(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine
)
{
  MX_Result  result = ERR_NOERR;
  OMX_ERRORTYPE err = OMX_ErrorNone;
  char componentRequested[OMTB_MAX_LEN] = {"\0"};
  char resultFileName[OMTB_MAX_LEN] = {"\0"};
  char fOpenMode[OMTB_MAX_LEN] = {"\0"};
  char testCaseId[OMTB_MAX_LEN] = {"\0"};
  char testCaseResult[OMTB_MAX_LEN] = {"\0"}; char returnString[OMTB_MAX_LEN] = {"\0"};
  FILE *fpResult = NULL;
  OMX_HANDLETYPE handle = NULL;                  /* Component handle */
  int nParam = 0;
  OMX_PTR pCmdData = NULL;
  OMX_COMMANDTYPE commandType = OMX_CommandMax;
  OMTB_OMX_API_TIMING_VAR_DECL;

  /* Read testcase ID */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, testCaseId);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }
  
  /* Read component name */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, componentRequested);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }

  /* Read result filename */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, resultFileName);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }

  /* Read result file type */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, fOpenMode);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }

  /* Read port Number */
  result = XdbgCmdNextNum(pContext, pCmdEntry, ppCmdLine, (UINT32 *)&nParam);
  if (ERR_NOERR != result)
  {
    return result;
  }

  /* set the flush command */
  commandType = OMX_CommandMax;
  pCmdData = NULL;

  /* Open the result file */
  fpResult = fopen(resultFileName, fOpenMode);

  if(NULL == fpResult)
  {
    PRINT(PRINT_ERR_MSG, "%s: Error in result file open\n", __FUNCTION__);
    fprintf(fpResult, "%s : Error in result file open\n", testCaseId);
    return ERR_INVNAME;
  }

  /* OpenMax insufficient resources */
    
  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;

  err = OMX_Init ();

  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_Init");

  if(OMX_ErrorNone != err)
  {
    OMTB_OmxReturnStatusString(err, returnString);
    strcpy(testCaseResult, "FAIL - Error in OMX_Init()\n");
    fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
    fclose(fpResult);
    return ERR_INVNAME;
  }

  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;
  
  /* get component handle */
  err = OMX_GetHandle(&handle,
                      (OMX_STRING)componentRequested,
                      NULL,
                      &OMTB_APITestCallback);
  
  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_GetHandle");

  if(OMX_ErrorNone != err)
  {
    OMTB_OmxReturnStatusString(err, returnString);
    strcpy(testCaseResult, "FAIL - Error in OMX_GetHandle()\n");
    fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);

    /* API entry time calculation macro */
    OMTB_OMX_API_ENTRY_TIME_CALC;

    /* OpenMax core uninitialization */
    err = OMX_Deinit ();

    /* API exit time calculation macro */
    OMTB_OMX_API_EXIT_TIME_CALC("OMX_Deinit");
    
    if(OMX_ErrorNone != err)
    {
      OMTB_OmxReturnStatusString(err, returnString);
      strcpy(testCaseResult, "FAIL - Error in OMX_Deinit()\n");
      fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
      result = ERR_INVNAME;
    }
    
    fclose(fpResult);
    return ERR_INVNAME;
  }

  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;

  /* sending command to component to flush the buffer on specified port */
  err = OMX_SendCommand(handle, commandType, nParam, pCmdData);

  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_SendCommand - OMX_CommandFlush");
  
  if(OMX_ErrorNone == err)
  {
    strcpy(testCaseResult, "PASS");
    fprintf(fpResult, "%s : %s\n", testCaseId, testCaseResult);
  }
  else
  {
    OMTB_OmxReturnStatusString(err, returnString);
    strcpy(testCaseResult, "FAIL");
    fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
    result = ERR_INVNAME;
  }
  
  /* free component handle */
  if(NULL != handle)
  {
    /* API entry time calculation macro */
    OMTB_OMX_API_ENTRY_TIME_CALC;
    
    err = OMX_FreeHandle(handle);
    
    /* API exit time calculation macro */
    OMTB_OMX_API_EXIT_TIME_CALC("OMX_FreeHandle");
    
    if(OMX_ErrorNone != err)
    {
	OMTB_OmxReturnStatusString(err, returnString);
    strcpy(testCaseResult, "FAIL - Error in OMX_FreeHandle()\n");
    fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);

      result = ERR_INVNAME;
    }
    
  }

  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;
  
  /* OpenMax core uninitialization */
  err = OMX_Deinit ();

  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_Deinit");

    if(OMX_ErrorNone != err)
    {
      OMTB_OmxReturnStatusString(err, returnString);
      strcpy(testCaseResult, "FAIL - Error in OMX_Deinit()\n");
      fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
      result = ERR_INVNAME;
    }

  /* close the result file */
  fclose(fpResult);
  
  return (result);
}


/******************************************************************************\
 *      OMTB_OmxSendCommandTimeOut Function Definition
\******************************************************************************/
/**
 *
 *  @brief    This Function performs OMX_SendCommand API testing.
 *
 *  @param    Pointer to MX_DBG_CMD_CONTEXT_T structure
 *            Pointer to MX_DBG_CMD_Entry_T structure
 *            Character Double Pointer containing the command
 *
 *  @return   ERR_NOERR           successful,
 *            ERR_END_OF_CMD      help was requested,
 *            ERR_INVNAME         otherwise.
 */

MX_Result
OMTB_OmxSendCommandTimeOut(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine
)
{
  MX_Result  result = ERR_NOERR;
  OMX_ERRORTYPE err = OMX_ErrorNone;
  char componentRequested[OMTB_MAX_LEN] = {"\0"};
  char resultFileName[OMTB_MAX_LEN] = {"\0"};
  char fOpenMode[OMTB_MAX_LEN] = {"\0"};
  char testCaseId[OMTB_MAX_LEN] = {"\0"};
  char testCaseResult[OMTB_MAX_LEN] = {"\0"}; char returnString[OMTB_MAX_LEN] = {"\0"};
  FILE *fpResult = NULL;
  OMX_HANDLETYPE handle = NULL;                  /* Component handle */
  int nParam = 0;
  OMX_PTR pCmdData = NULL;
  OMX_COMMANDTYPE commandType = OMX_CommandMax;
  OMTB_OMX_API_TIMING_VAR_DECL;

  /* Read testcase ID */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, testCaseId);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }
  
  /* Read component name */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, componentRequested);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }

  /* Read result filename */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, resultFileName);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }

  /* Read result file type */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, fOpenMode);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }

  /* Read port Number */
  result = XdbgCmdNextNum(pContext, pCmdEntry, ppCmdLine, (UINT32 *)&nParam);
  if (ERR_NOERR != result)
  {
    return result;
  }

  /* set the flush command */
  commandType = OMX_CommandFlush;
  pCmdData = NULL;

  /* Open the result file */
  fpResult = fopen(resultFileName, fOpenMode);

  if(NULL == fpResult)
  {
    PRINT(PRINT_ERR_MSG, "%s: Error in result file open\n", __FUNCTION__);
    fprintf(fpResult, "%s : Error in result file open\n", testCaseId);
    return ERR_INVNAME;
  }

  /* OpenMax insufficient resources */
    
  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;

  err = OMX_Init ();

  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_Init");

  if(OMX_ErrorNone != err)
  {
    OMTB_OmxReturnStatusString(err, returnString);
    strcpy(testCaseResult, "FAIL - Error in OMX_Init()\n");
    fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
    fclose(fpResult);
    return ERR_INVNAME;
  }

  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;
  
  /* get component handle */
  err = OMX_GetHandle(&handle,
                      (OMX_STRING)componentRequested,
                      NULL,
                      &OMTB_APITestCallback);
  
  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_GetHandle");

  if(OMX_ErrorNone != err)
  {
    OMTB_OmxReturnStatusString(err, returnString);
    strcpy(testCaseResult, "FAIL - Error in OMX_GetHandle()\n");
    fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);

    /* API entry time calculation macro */
    OMTB_OMX_API_ENTRY_TIME_CALC;

    /* OpenMax core uninitialization */
    err = OMX_Deinit ();

    /* API exit time calculation macro */
    OMTB_OMX_API_EXIT_TIME_CALC("OMX_Deinit");
    
    if(OMX_ErrorNone != err)
    {
      OMTB_OmxReturnStatusString(err, returnString);
      strcpy(testCaseResult, "FAIL - Error in OMX_Deinit()\n");
      fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
      result = ERR_INVNAME;
    }
    
    fclose(fpResult);
    return ERR_INVNAME;
  }

  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;

  /* sending command to component to flush the buffer on specified port */
  err = OMX_SendCommand(handle, commandType, nParam, pCmdData);

  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_SendCommand - OMX_CommandFlush");
  
  if(OMX_ErrorTimeout == err)
  {
    strcpy(testCaseResult, "PASS");
    fprintf(fpResult, "%s : %s\n", testCaseId, testCaseResult);
  }
  else
  {
    OMTB_OmxReturnStatusString(err, returnString);
    strcpy(testCaseResult, "FAIL");
    fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
    result = ERR_INVNAME;
  }
  
  /* free component handle */
  if(NULL != handle)
  {
    /* API entry time calculation macro */
    OMTB_OMX_API_ENTRY_TIME_CALC;
    
    err = OMX_FreeHandle(handle);
    
    /* API exit time calculation macro */
    OMTB_OMX_API_EXIT_TIME_CALC("OMX_FreeHandle");
    
    if(OMX_ErrorNone != err)
    {
	OMTB_OmxReturnStatusString(err, returnString);
    strcpy(testCaseResult, "FAIL - Error in OMX_FreeHandle()\n");
    fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);

      result = ERR_INVNAME;
    }
    
  }

  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;
  
  /* OpenMax core uninitialization */
  err = OMX_Deinit ();

  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_Deinit");

    if(OMX_ErrorNone != err)
    {
      OMTB_OmxReturnStatusString(err, returnString);
      strcpy(testCaseResult, "FAIL - Error in OMX_Deinit()\n");
      fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
      result = ERR_INVNAME;
    }

  /* close the result file */
  fclose(fpResult);
  
  return (result);
}


/******************************************************************************\
 *      OMTB_OmxSendCommandOnWrongPort Function Definition
\******************************************************************************/
/**
 *
 *  @brief    This Function performs OMX_SendCommand API testing.
 *
 *  @param    Pointer to MX_DBG_CMD_CONTEXT_T structure
 *            Pointer to MX_DBG_CMD_Entry_T structure
 *            Character Double Pointer containing the command
 *
 *  @return   ERR_NOERR           successful,
 *            ERR_END_OF_CMD      help was requested,
 *            ERR_INVNAME         otherwise.
 */

MX_Result
OMTB_OmxSendCommandOnWrongPort(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine
)
{
  MX_Result  result = ERR_NOERR;
  OMX_ERRORTYPE err = OMX_ErrorNone;
  char componentRequested[OMTB_MAX_LEN] = {"\0"};
  char resultFileName[OMTB_MAX_LEN] = {"\0"};
  char fOpenMode[OMTB_MAX_LEN] = {"\0"};
  char testCaseId[OMTB_MAX_LEN] = {"\0"};
  char testCaseResult[OMTB_MAX_LEN] = {"\0"}; char returnString[OMTB_MAX_LEN] = {"\0"};
  FILE *fpResult = NULL;
  OMX_HANDLETYPE handle = NULL;                  /* Component handle */
  int nParam = 0;
  OMX_PTR pCmdData = NULL;
  OMX_COMMANDTYPE commandType = OMX_CommandMax;
  OMTB_OMX_API_TIMING_VAR_DECL;

  /* Read testcase ID */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, testCaseId);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }
  
  /* Read component name */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, componentRequested);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }

  /* Read result filename */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, resultFileName);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }

  /* Read result file type */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, fOpenMode);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }

  /* Read port Number */
  result = XdbgCmdNextNum(pContext, pCmdEntry, ppCmdLine, (UINT32 *)&nParam);
  if (ERR_NOERR != result)
  {
    return result;
  }

  /* set the flush command */
  commandType = OMX_CommandFlush;
  pCmdData = NULL;

  /* Open the result file */
  fpResult = fopen(resultFileName, fOpenMode);

  if(NULL == fpResult)
  {
    PRINT(PRINT_ERR_MSG, "%s: Error in result file open\n", __FUNCTION__);
    fprintf(fpResult, "%s : Error in result file open\n", testCaseId);
    return ERR_INVNAME;
  }

  /* OpenMax insufficient resources */
    
  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;

  err = OMX_Init ();

  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_Init");

  if(OMX_ErrorNone != err)
  {
    OMTB_OmxReturnStatusString(err, returnString);
    strcpy(testCaseResult, "FAIL - Error in OMX_Init()\n");
    fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
    fclose(fpResult);
    return ERR_INVNAME;
  }

  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;
  
  /* get component handle */
  err = OMX_GetHandle(&handle,
                      (OMX_STRING)componentRequested,
                      NULL,
                      &OMTB_APITestCallback);
  
  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_GetHandle");

  if(OMX_ErrorNone != err)
  {
    OMTB_OmxReturnStatusString(err, returnString);
    strcpy(testCaseResult, "FAIL - Error in OMX_GetHandle()\n");
    fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);

    /* API entry time calculation macro */
    OMTB_OMX_API_ENTRY_TIME_CALC;

    /* OpenMax core uninitialization */
    err = OMX_Deinit ();

    /* API exit time calculation macro */
    OMTB_OMX_API_EXIT_TIME_CALC("OMX_Deinit");
    
    if(OMX_ErrorNone != err)
    {
      OMTB_OmxReturnStatusString(err, returnString);
      strcpy(testCaseResult, "FAIL - Error in OMX_Deinit()\n");
      fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
      result = ERR_INVNAME;
    }
    
    fclose(fpResult);
    return ERR_INVNAME;
  }

  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;

  /* sending command to component to flush the buffer on specified port */
  err = OMX_SendCommand(handle, commandType, nParam, pCmdData);

  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_SendCommand - OMX_CommandFlush");
  
  if(OMX_ErrorBadPortIndex == err)
  {
    strcpy(testCaseResult, "PASS");
    fprintf(fpResult, "%s : %s\n", testCaseId, testCaseResult);
  }
  else
  {
    OMTB_OmxReturnStatusString(err, returnString);
    strcpy(testCaseResult, "FAIL");
    fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
    result = ERR_INVNAME;
  }
  
  /* free component handle */
  if(NULL != handle)
  {
    /* API entry time calculation macro */
    OMTB_OMX_API_ENTRY_TIME_CALC;
    
    err = OMX_FreeHandle(handle);
    
    /* API exit time calculation macro */
    OMTB_OMX_API_EXIT_TIME_CALC("OMX_FreeHandle");
    
    if(OMX_ErrorNone != err)
    {
	OMTB_OmxReturnStatusString(err, returnString);
    strcpy(testCaseResult, "FAIL - Error in OMX_FreeHandle()\n");
    fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);

      result = ERR_INVNAME;
    }
    
  }

  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;
  
  /* OpenMax core uninitialization */
  err = OMX_Deinit ();

  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_Deinit");

    if(OMX_ErrorNone != err)
    {
      OMTB_OmxReturnStatusString(err, returnString);
      strcpy(testCaseResult, "FAIL - Error in OMX_Deinit()\n");
      fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
      result = ERR_INVNAME;
    }

  /* close the result file */
  fclose(fpResult);
  
  return (result);
}


/******************************************************************************\
 *      OmxAllocUseBufferOnce Function Definition
\******************************************************************************/
/**
 *
 *  @brief    This Function performs OMX_AllocateBuffer/OMX_UseBuffer API testing.
 *
 *  @param    Pointer to MX_DBG_CMD_CONTEXT_T structure
 *            Pointer to MX_DBG_CMD_Entry_T structure
 *            Character Double Pointer containing the command
 *
 *  @return   ERR_NOERR           successful,
 *            ERR_END_OF_CMD      help was requested,
 *            ERR_INVNAME         otherwise.
 *
 */

MX_Result OmxAllocUseBufferOnce(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine)
{

  OMX_ERRORTYPE err = OMX_ErrorNone;
  unsigned int i = 0;
  unsigned char *pBuffer = NULL;
  OMTB_CLIENT_PRIVATE* thisClient = NULL;
  unsigned int instance = 0;
  char resultFileName[OMTB_MAX_LEN] = {"\0"};
  char fOpenMode[OMTB_MAX_LEN] = {"\0"};
  char testCaseId[OMTB_MAX_LEN] = {"\0"};
  char testCaseResult[OMTB_MAX_LEN] = {"\0"}; char returnString[OMTB_MAX_LEN] = {"\0"};
  FILE *fpResult = NULL;
  MX_Result  result = ERR_NOERR;
  char componentRequested[OMX_MAX_STRINGNAME_SIZE] = {"\0"};  
  OMTB_OMX_API_TIMING_VAR_DECL;

  /* Read component name */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, componentRequested);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }
  
  /* Read testcase ID */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, testCaseId);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }
  
  /* Read result filename */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, resultFileName);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }

  /* Read result file type */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, fOpenMode);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }
  
  /* Read instance Number */
  result = XdbgCmdNextNum(pContext, pCmdEntry, ppCmdLine, (UINT32 *)&instance);
  if (ERR_NOERR != result)
  {
    return result;
  }

  if(OMTB_MAX_INS <= instance)
  {
    /* Invalid instance no */
    PRINT(PRINT_ERR_MSG, 
          "Invalid instance number: %d - Valid range: <0 to %d>\n",
          instance, OMTB_MAX_INS - 1);
    XdbgCmdSyntaxShow(pContext, pCmdEntry);
    return ERR_INVNAME;
  }   

  /* Open the result file */
  fpResult = fopen(resultFileName, fOpenMode);

  if(NULL == fpResult)
  {
    PRINT(PRINT_ERR_MSG, "%s: Error in result file open\n", __FUNCTION__);
    fprintf(fpResult, "%s : FAIL - Error in result file open\n", testCaseId);
    return ERR_INVNAME;
  }
  
  thisClient =  (OMTB_CLIENT_PRIVATE*)OMTB_GetCompPrivHandle(componentRequested, instance); 
  /* validate the function arguments */
  ASSERT(NULL != thisClient);
  
  PRINT(PRINT_FUNCTION_NAME, "Entering <Function , instance #> : <%s , %d>\n",
                              __FUNCTION__, (int)thisClient->omtbPvt.instanceNo);

  /* Set the port params */
  if(NULL != thisClient->omtbPvt.fpSetPortDefinition)
    err = thisClient->omtbPvt.fpSetPortDefinition((void*)thisClient);  

  if(OMX_ErrorNone != err)
  {
    OMTB_OmxReturnStatusString(err, returnString);
    fprintf(fpResult, "%s : FAIL - Error in SetPortDefinition() OMX ERROR %s\n", testCaseId,returnString);
    fclose(fpResult);
    return ERR_INVNAME;
  }
  
  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;

  /* sending command to component for specified state transition */
  err = OMX_SendCommand(thisClient->omtbPvt.handle, OMX_CommandStateSet, OMX_StateIdle, NULL);

  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_SendCommand - OMX_CommandStateSet");

  if(OMX_ErrorNone != err)
  {
    OMTB_OmxReturnStatusString(err, returnString);
    fprintf(fpResult, "%s : FAIL - Error in OMX_SendCommand(OMX_StateIdle) OMX ERROR %s\n", testCaseId,returnString);
    fclose(fpResult);
    return ERR_INVNAME;
  }
  
  /* Input port buffer allocation */

  /* OMX_AllocateBuffer */
  if(OMX_FALSE == thisClient->inPortParams->cmnInParams.flagUseInBuffer)
  {
    /* API entry time calculation macro */
    OMTB_OMX_API_ENTRY_TIME_CALC;

    err = OMX_AllocateBuffer( 
                      thisClient->omtbPvt.handle,
                      &thisClient->inPortParams->pInBuff[i],
                      thisClient->inPortParams->cmnInParams.pInPortDef->nPortIndex, 
                      thisClient,
                      thisClient->inPortParams->cmnInParams.bufferInSize);

    /* API exit time calculation macro */
    OMTB_OMX_API_EXIT_TIME_CALC("OMX_AllocateBuffer");
  }
  /* OMX_UseBuffer */
  else
  {
    /* Allocating memory for input port buffer */
    pBuffer = (unsigned char*)TIMM_OSAL_Malloc(
                      thisClient->inPortParams->cmnInParams.bufferInSize,
                      (TIMM_OSAL_BOOL)thisClient->inPortParams->cmnInParams.inBufContiguous,
                      thisClient->inPortParams->cmnInParams.inBufAlignment,
                      TIMMOSAL_MEM_SEGMENT_EXT);
    
    if (!pBuffer)
    {
      PRINT(PRINT_ERR_MSG, \
          "Error in Buffer allocation for i/p port\n");

      /* Function to release the resources allocated by component */
      err = OMTB_ClientFreeResources(thisClient);

      if(OMX_ErrorNone != err)
      {
        OMTB_OmxReturnStatusString(err, returnString);
        strcpy(testCaseResult, "FAIL in releasing resources for UseBuffer");
        fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
        result = ERR_INVNAME;
      }
      
      strcpy(testCaseResult, "FAIL in buffer allocation for UseBuffer");
      fprintf(fpResult, "%s : %s\n", testCaseId, testCaseResult);
      result = ERR_INVNAME;
      fclose(fpResult);
      return result;
    }

    /* API entry time calculation macro */
    OMTB_OMX_API_ENTRY_TIME_CALC;

    err = OMX_UseBuffer(thisClient->omtbPvt.handle,
                    &thisClient->inPortParams->pInBuff[i],
                    thisClient->inPortParams->cmnInParams.pInPortDef->nPortIndex, 
                    thisClient,
                    thisClient->inPortParams->cmnInParams.bufferInSize,
                    pBuffer);

    /* API exit time calculation macro */
    OMTB_OMX_API_EXIT_TIME_CALC("OMX_UseBuffer");
  }

  if(OMX_ErrorNone == err)
  {
    strcpy(testCaseResult, "PASS");
    fprintf(fpResult, "%s : %s\n", testCaseId, testCaseResult);
  }
  else
  {
    OMTB_OmxReturnStatusString(err, returnString);
    strcpy(testCaseResult, "FAIL");
    fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
    result = ERR_INVNAME;
  }

  /* Allocate I/O buffers & wait till transition to idle */
  err = (OMX_ERRORTYPE)OMTB_ClientAllocateOutputResources(thisClient);

  if(OMX_ErrorNone != err)
  {
    OMTB_OmxReturnStatusString(err, returnString);
    fprintf(fpResult, "%s : FAIL - Error in OMTB_ClientAllocateOutputResources() OMX ERROR %s\n", testCaseId,returnString);
    result = ERR_INVNAME;
  }
  
//  TIMM_OSAL_SemaphoreObtain(thisClient->omtbPvt.eventSem,
//                  TIMM_OSAL_SUSPEND);
  
  PRINT(PRINT_FUNCTION_NAME, "Leaving <Function , instance #> : <%s , %d>\n",
                              __FUNCTION__, (int)thisClient->omtbPvt.instanceNo);

  fclose(fpResult);
  return result;
}


/******************************************************************************\
 *      OmxAllocUseBufferInsuffResources Function Definition
\******************************************************************************/
/**
 *
 *  @brief    This Function performs OMX_AllocateBuffer/OMX_UseBuffer API testing.
 *
 *  @param    Pointer to MX_DBG_CMD_CONTEXT_T structure
 *            Pointer to MX_DBG_CMD_Entry_T structure
 *            Character Double Pointer containing the command
 *
 *  @return   ERR_NOERR           successful,
 *            ERR_END_OF_CMD      help was requested,
 *            ERR_INVNAME         otherwise.
 *
 */

MX_Result OmxAllocUseBufferInsuffResources(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine)
{

  OMX_ERRORTYPE err = OMX_ErrorNone;
  unsigned int i = 0;
  unsigned char *pBuffer = NULL;
  OMTB_CLIENT_PRIVATE* thisClient = NULL;  
  unsigned int instance = 0;
  char resultFileName[OMTB_MAX_LEN] = {"\0"};
  char fOpenMode[OMTB_MAX_LEN] = {"\0"};
  char testCaseId[OMTB_MAX_LEN] = {"\0"};
  char testCaseResult[OMTB_MAX_LEN] = {"\0"}; char returnString[OMTB_MAX_LEN] = {"\0"};
  FILE *fpResult = NULL;
  MX_Result  result = ERR_NOERR;
  char componentRequested[OMX_MAX_STRINGNAME_SIZE] = {"\0"};    
  OMTB_OMX_API_TIMING_VAR_DECL;

  /* Read component name */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, componentRequested);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }
  
  /* Read testcase ID */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, testCaseId);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }
  
  /* Read result filename */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, resultFileName);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }

  /* Read result file type */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, fOpenMode);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }
  
  /* Read instance Number */
  result = XdbgCmdNextNum(pContext, pCmdEntry, ppCmdLine, (UINT32 *)&instance);
  if (ERR_NOERR != result)
  {
    return result;
  }

  /* Open the result file */
  fpResult = fopen(resultFileName, fOpenMode);

  if(NULL == fpResult)
  {
    PRINT(PRINT_ERR_MSG, "%s: Error in result file open\n", __FUNCTION__);
    fprintf(fpResult, "%s : FAIL - Error in result file open\n", testCaseId);
    return ERR_INVNAME;
  }
  
  thisClient =  (OMTB_CLIENT_PRIVATE*)OMTB_GetCompPrivHandle(componentRequested, instance);
  
  /* validate the function arguments */
  ASSERT(NULL != thisClient);
  
  PRINT(PRINT_FUNCTION_NAME, "Entering <Function , instance #> : <%s , %d>\n",
                              __FUNCTION__, (int)thisClient->omtbPvt.instanceNo);

  /* Set the port params */
  if(NULL != thisClient->omtbPvt.fpSetPortDefinition)
    err = thisClient->omtbPvt.fpSetPortDefinition((void*)thisClient);  

  if(OMX_ErrorNone != err)
  {
    OMTB_OmxReturnStatusString(err, returnString);
    fprintf(fpResult, "%s : FAIL - Error in SetPortDefinition() OMX ERROR %s\n", testCaseId,returnString);
    fclose(fpResult);
    return ERR_INVNAME;
  }
  
  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;

  /* sending command to component for specified state transition */
  err = OMX_SendCommand(thisClient->omtbPvt.handle, OMX_CommandStateSet, OMX_StateIdle, NULL);

  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_SendCommand - OMX_CommandStateSet");

   if(OMX_ErrorNone != err)
  {
    OMTB_OmxReturnStatusString(err, returnString);
    fprintf(fpResult, "%s : FAIL - Error in OMX_SendCommand(OMX_StateIdle) OMX ERROR %s\n", testCaseId,returnString);
    fclose(fpResult);
    return ERR_INVNAME;
  }
  
  /* Input port buffer allocation */

  /* OMX_AllocateBuffer */
  if(OMX_FALSE == thisClient->inPortParams->cmnInParams.flagUseInBuffer)
  {
    /* API entry time calculation macro */
    OMTB_OMX_API_ENTRY_TIME_CALC;

    err = OMX_AllocateBuffer( 
                      thisClient->omtbPvt.handle,
                      &thisClient->inPortParams->pInBuff[i],
                      thisClient->inPortParams->cmnInParams.pInPortDef->nPortIndex, 
                      thisClient,
                      thisClient->inPortParams->cmnInParams.bufferInSize);

    /* API exit time calculation macro */
    OMTB_OMX_API_EXIT_TIME_CALC("OMX_AllocateBuffer");
  }
  /* OMX_UseBuffer */
  else
  {
    /* Allocating memory for input port buffer */
    pBuffer = (unsigned char*)TIMM_OSAL_Malloc(
                      thisClient->inPortParams->cmnInParams.bufferInSize,
                      (TIMM_OSAL_BOOL)thisClient->inPortParams->cmnInParams.inBufContiguous,
                      thisClient->inPortParams->cmnInParams.inBufAlignment,
                      TIMMOSAL_MEM_SEGMENT_EXT);
    
    if (!pBuffer)
    {
      PRINT(PRINT_ERR_MSG, \
          "Error in Buffer allocation for i/p port\n");

      /* Function to release the resources allocated by component */
      err = OMTB_ClientFreeResources(thisClient);

      if(OMX_ErrorNone != err)
      {
        OMTB_OmxReturnStatusString(err, returnString);
        strcpy(testCaseResult, "FAIL in releasing resources for UseBuffer");
        fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
        result = ERR_INVNAME;
      }
      
      strcpy(testCaseResult, "FAIL in buffer allocation for UseBuffer");
      fprintf(fpResult, "%s : %s\n", testCaseId, testCaseResult);
      result = ERR_INVNAME;
      fclose(fpResult);
      return result;
    }

    /* API entry time calculation macro */
    OMTB_OMX_API_ENTRY_TIME_CALC;

    err = OMX_UseBuffer(thisClient->omtbPvt.handle,
                    &thisClient->inPortParams->pInBuff[i],
                    thisClient->inPortParams->cmnInParams.pInPortDef->nPortIndex, 
                    thisClient,
                    thisClient->inPortParams->cmnInParams.bufferInSize,
                    pBuffer);

    /* API exit time calculation macro */
    OMTB_OMX_API_EXIT_TIME_CALC("OMX_UseBuffer");
  }

  if(OMX_ErrorInsufficientResources == err)
  {
    strcpy(testCaseResult, "PASS");
    fprintf(fpResult, "%s : %s\n", testCaseId, testCaseResult);
  }
  else
  {
    OMTB_OmxReturnStatusString(err, returnString);
    strcpy(testCaseResult, "FAIL");
    fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
    result = ERR_INVNAME;
  }

  /* Allocate I/O buffers & wait till transition to idle */
  err = (OMX_ERRORTYPE)OMTB_ClientAllocateOutputResources(thisClient);

  if(OMX_ErrorNone != err)
  {
    OMTB_OmxReturnStatusString(err, returnString);
    fprintf(fpResult, "%s : FAIL - Error in OMTB_ClientAllocateOutputResources() OMX ERROR %s\n", testCaseId,returnString);
    result = ERR_INVNAME;
  }
  
//  TIMM_OSAL_SemaphoreObtain(thisClient->omtbPvt.eventSem,
//                  TIMM_OSAL_SUSPEND);
  
  PRINT(PRINT_FUNCTION_NAME, "Leaving <Function , instance #> : <%s , %d>\n",
                              __FUNCTION__, (int)thisClient->omtbPvt.instanceNo);

  fclose(fpResult);
  return result;
}


/******************************************************************************\
 *      OmxAllocUseBufferNullBufferHdr Function Definition
\******************************************************************************/
/**
 *
 *  @brief    This Function performs OMX_AllocateBuffer/OMX_UseBuffer API testing.
 *
 *  @param    Pointer to MX_DBG_CMD_CONTEXT_T structure
 *            Pointer to MX_DBG_CMD_Entry_T structure
 *            Character Double Pointer containing the command
 *
 *  @return   ERR_NOERR           successful,
 *            ERR_END_OF_CMD      help was requested,
 *            ERR_INVNAME         otherwise.
 *
 */

MX_Result OmxAllocUseBufferNullBufferHdr(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine)
{

  OMX_ERRORTYPE err = OMX_ErrorNone;
  OMTB_CLIENT_PRIVATE* thisClient = NULL;
  unsigned int instance = 0;
  char resultFileName[OMTB_MAX_LEN] = {"\0"};
  char fOpenMode[OMTB_MAX_LEN] = {"\0"};
  char testCaseId[OMTB_MAX_LEN] = {"\0"};
  char testCaseResult[OMTB_MAX_LEN] = {"\0"}; char returnString[OMTB_MAX_LEN] = {"\0"};
  FILE *fpResult = NULL;
  MX_Result  result = ERR_NOERR;
  char componentRequested[OMX_MAX_STRINGNAME_SIZE] = {"\0"};    
  OMTB_OMX_API_TIMING_VAR_DECL;

  /* Read component name */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, componentRequested);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }
  
  /* Read testcase ID */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, testCaseId);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }
  
  /* Read result filename */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, resultFileName);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }

  /* Read result file type */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, fOpenMode);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }
  
  /* Read instance Number */
  result = XdbgCmdNextNum(pContext, pCmdEntry, ppCmdLine, (UINT32 *)&instance);
  if (ERR_NOERR != result)
  {
    return result;
  }

  /* Open the result file */
  fpResult = fopen(resultFileName, fOpenMode);

  if(NULL == fpResult)
  {
    PRINT(PRINT_ERR_MSG, "%s: Error in result file open\n", __FUNCTION__);
    fprintf(fpResult, "%s : FAIL - Error in result file open\n", testCaseId);
    return ERR_INVNAME;
  }
  
  thisClient =  (OMTB_CLIENT_PRIVATE*)OMTB_GetCompPrivHandle(componentRequested, instance);
  
  /* validate the function arguments */
  ASSERT(NULL != thisClient);
  
  PRINT(PRINT_FUNCTION_NAME, "Entering <Function , instance #> : <%s , %d>\n",
                              __FUNCTION__, (int)thisClient->omtbPvt.instanceNo);

  /* Set the port params */
  if(NULL != thisClient->omtbPvt.fpSetPortDefinition)
    err = thisClient->omtbPvt.fpSetPortDefinition((void*)thisClient);  

  if(OMX_ErrorNone != err)
  {
    OMTB_OmxReturnStatusString(err, returnString);
    fprintf(fpResult, "%s : FAIL - Error in SetPortDefinition() OMX ERROR %s\n", testCaseId,returnString);
    fclose(fpResult);
    return ERR_INVNAME;
  }
  
  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;

  /* sending command to component for specified state transition */
  err = OMX_SendCommand(thisClient->omtbPvt.handle, OMX_CommandStateSet, OMX_StateIdle, NULL);

  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_SendCommand - OMX_CommandStateSet");

  if(OMX_ErrorNone != err)
  {
    OMTB_OmxReturnStatusString(err, returnString);
    fprintf(fpResult, "%s : FAIL - Error in OMX_SendCommand(OMX_StateIdle) OMX ERROR %s\n", testCaseId,returnString);
    fclose(fpResult);
    return ERR_INVNAME;
  }
  
  /* Input port buffer allocation */

  /* OMX_AllocateBuffer */
  if(OMX_FALSE == thisClient->inPortParams->cmnInParams.flagUseInBuffer)
  {
    /* API entry time calculation macro */
    OMTB_OMX_API_ENTRY_TIME_CALC;

    err = OMX_AllocateBuffer( 
                      thisClient->omtbPvt.handle,
                      NULL,
                      thisClient->inPortParams->cmnInParams.pInPortDef->nPortIndex, 
                      thisClient,
                      thisClient->inPortParams->cmnInParams.bufferInSize);

    /* API exit time calculation macro */
    OMTB_OMX_API_EXIT_TIME_CALC("OMX_AllocateBuffer");
  }
  /* OMX_UseBuffer */
  else
  {
    /* API entry time calculation macro */
    OMTB_OMX_API_ENTRY_TIME_CALC;

    err = OMX_UseBuffer(thisClient->omtbPvt.handle,
                    NULL,
                    thisClient->inPortParams->cmnInParams.pInPortDef->nPortIndex, 
                    thisClient,
                    thisClient->inPortParams->cmnInParams.bufferInSize,
                    NULL);

    /* API exit time calculation macro */
    OMTB_OMX_API_EXIT_TIME_CALC("OMX_UseBuffer");
  }

  if(OMX_ErrorBadParameter == err)
  {
    strcpy(testCaseResult, "PASS");
    fprintf(fpResult, "%s : %s\n", testCaseId, testCaseResult);
  }
  else
  {
    OMTB_OmxReturnStatusString(err, returnString);
    strcpy(testCaseResult, "FAIL");
    fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
    result = ERR_INVNAME;
  }

  /* Allocate I/O buffers & wait till transition to idle */
  err = (OMX_ERRORTYPE)OMTB_ClientAllocateOutputResources(thisClient);

  if(OMX_ErrorNone != err)
  {
    OMTB_OmxReturnStatusString(err, returnString);
    fprintf(fpResult, "%s : FAIL - Error in OMTB_ClientAllocateOutputResources() OMX ERROR %s\n", testCaseId,returnString);
    result = ERR_INVNAME;
  }
  
//  TIMM_OSAL_SemaphoreObtain(thisClient->omtbPvt.eventSem,
//                  TIMM_OSAL_SUSPEND);
  
  PRINT(PRINT_FUNCTION_NAME, "Leaving <Function , instance #> : <%s , %d>\n",
                              __FUNCTION__, (int)thisClient->omtbPvt.instanceNo);

  fclose(fpResult);
  return result;
}


/******************************************************************************\
 *      OmxAllocUseBufferNullHandle Function Definition
\******************************************************************************/
/**
 *
 *  @brief    This Function performs OMX_AllocateBuffer/OMX_UseBuffer API testing.
 *
 *  @param    Pointer to MX_DBG_CMD_CONTEXT_T structure
 *            Pointer to MX_DBG_CMD_Entry_T structure
 *            Character Double Pointer containing the command
 *
 *  @return   ERR_NOERR           successful,
 *            ERR_END_OF_CMD      help was requested,
 *            ERR_INVNAME         otherwise.
 *
 */

MX_Result OmxAllocUseBufferNullHandle(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine)
{

  OMX_ERRORTYPE err = OMX_ErrorNone;
  unsigned int i = 0;
  unsigned char *pBuffer = NULL;
  OMTB_CLIENT_PRIVATE* thisClient = NULL;
  unsigned int instance = 0;
  char resultFileName[OMTB_MAX_LEN] = {"\0"};
  char fOpenMode[OMTB_MAX_LEN] = {"\0"};
  char testCaseId[OMTB_MAX_LEN] = {"\0"};
  char testCaseResult[OMTB_MAX_LEN] = {"\0"}; char returnString[OMTB_MAX_LEN] = {"\0"};
  FILE *fpResult = NULL;
  MX_Result  result = ERR_NOERR;
  char componentRequested[OMX_MAX_STRINGNAME_SIZE] = {"\0"};    
  OMTB_OMX_API_TIMING_VAR_DECL;

  /* Read component name */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, componentRequested);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }
  
  /* Read testcase ID */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, testCaseId);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }
  
  /* Read result filename */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, resultFileName);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }

  /* Read result file type */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, fOpenMode);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }
  
  /* Read instance Number */
  result = XdbgCmdNextNum(pContext, pCmdEntry, ppCmdLine, (UINT32 *)&instance);
  if (ERR_NOERR != result)
  {
    return result;
  }

  /* Open the result file */
  fpResult = fopen(resultFileName, fOpenMode);

  if(NULL == fpResult)
  {
    PRINT(PRINT_ERR_MSG, "%s: Error in result file open\n", __FUNCTION__);
    fprintf(fpResult, "%s : FAIL - Error in result file open\n", testCaseId);
    return ERR_INVNAME;
  }
  
  thisClient =  (OMTB_CLIENT_PRIVATE*)OMTB_GetCompPrivHandle(componentRequested, instance);
  
  /* validate the function arguments */
  ASSERT(NULL != thisClient);
  
  PRINT(PRINT_FUNCTION_NAME, "Entering <Function , instance #> : <%s , %d>\n",
                              __FUNCTION__, (int)thisClient->omtbPvt.instanceNo);

  /* Set the port params */
  if(NULL != thisClient->omtbPvt.fpSetPortDefinition)
    err = thisClient->omtbPvt.fpSetPortDefinition((void*)thisClient);  

  if(OMX_ErrorNone != err)
  {
    OMTB_OmxReturnStatusString(err, returnString);
    fprintf(fpResult, "%s : FAIL - Error in SetPortDefinition() OMX ERROR %s\n", testCaseId,returnString);
    fclose(fpResult);
    return ERR_INVNAME;
  }
  
  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;

  /* sending command to component for specified state transition */
  err = OMX_SendCommand(thisClient->omtbPvt.handle, OMX_CommandStateSet, OMX_StateIdle, NULL);

  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_SendCommand - OMX_CommandStateSet");

  if(OMX_ErrorNone != err)
  {
    OMTB_OmxReturnStatusString(err, returnString);
    fprintf(fpResult, "%s : FAIL - Error in OMX_SendCommand(OMX_StateIdle) OMX ERROR %s\n", testCaseId,returnString);
    fclose(fpResult);
    return ERR_INVNAME;
  }
  
  /* Input port buffer allocation */

  /* OMX_AllocateBuffer */
  if(OMX_FALSE == thisClient->inPortParams->cmnInParams.flagUseInBuffer)
  {
    /* API entry time calculation macro */
    OMTB_OMX_API_ENTRY_TIME_CALC;

    err = OMX_AllocateBuffer( 
                      NULL,
                      &thisClient->inPortParams->pInBuff[i],
                      thisClient->inPortParams->cmnInParams.pInPortDef->nPortIndex, 
                      thisClient,
                      thisClient->inPortParams->cmnInParams.bufferInSize);

    /* API exit time calculation macro */
    OMTB_OMX_API_EXIT_TIME_CALC("OMX_AllocateBuffer");
  }
  /* OMX_UseBuffer */
  else
  {
    /* Allocating memory for input port buffer */
    pBuffer = (unsigned char*)TIMM_OSAL_Malloc(
                      thisClient->inPortParams->cmnInParams.bufferInSize,
                      (TIMM_OSAL_BOOL)thisClient->inPortParams->cmnInParams.inBufContiguous,
                      thisClient->inPortParams->cmnInParams.inBufAlignment,
                      TIMMOSAL_MEM_SEGMENT_EXT);
    
    if (!pBuffer)
    {
      PRINT(PRINT_ERR_MSG, \
          "Error in Buffer allocation for i/p port\n");

      /* Function to release the resources allocated by component */
      err = OMTB_ClientFreeResources(thisClient);

      if(OMX_ErrorNone != err)
      {
        OMTB_OmxReturnStatusString(err, returnString);
        strcpy(testCaseResult, "FAIL in releasing resources for UseBuffer");
        fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
        result = ERR_INVNAME;
      }
      
      strcpy(testCaseResult, "FAIL in buffer allocation for UseBuffer");
      fprintf(fpResult, "%s : %s\n", testCaseId, testCaseResult);
      result = ERR_INVNAME;
      fclose(fpResult);
      return result;
    }

    /* API entry time calculation macro */
    OMTB_OMX_API_ENTRY_TIME_CALC;

    err = OMX_UseBuffer(NULL,
                    &thisClient->inPortParams->pInBuff[i],
                    thisClient->inPortParams->cmnInParams.pInPortDef->nPortIndex, 
                    thisClient,
                    thisClient->inPortParams->cmnInParams.bufferInSize,
                    pBuffer);

    /* API exit time calculation macro */
    OMTB_OMX_API_EXIT_TIME_CALC("OMX_UseBuffer");
  }

  if(OMX_ErrorBadParameter == err)
  {
    strcpy(testCaseResult, "PASS");
    fprintf(fpResult, "%s : %s\n", testCaseId, testCaseResult);
  }
  else
  {
    OMTB_OmxReturnStatusString(err, returnString);
    strcpy(testCaseResult, "FAIL");
    fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
    result = ERR_INVNAME;
  }

  /* Allocate I/O buffers & wait till transition to idle */
  err = (OMX_ERRORTYPE)OMTB_ClientAllocateOutputResources(thisClient);

  if(OMX_ErrorNone != err)
  {
    OMTB_OmxReturnStatusString(err, returnString);
    fprintf(fpResult, "%s : FAIL - Error in OMTB_ClientAllocateOutputResources() OMX ERROR %s\n", testCaseId,returnString);
    result = ERR_INVNAME;
  }
  
//  TIMM_OSAL_SemaphoreObtain(thisClient->omtbPvt.eventSem,
//                  TIMM_OSAL_SUSPEND);
  
  PRINT(PRINT_FUNCTION_NAME, "Leaving <Function , instance #> : <%s , %d>\n",
                              __FUNCTION__, (int)thisClient->omtbPvt.instanceNo);

  fclose(fpResult);
  return result;
}


/******************************************************************************\
 *      OmxAllocUseBufferVerMismatch Function Definition
\******************************************************************************/
/**
 *
 *  @brief    This Function performs OMX_AllocateBuffer/OMX_UseBuffer API testing.
 *
 *  @param    Pointer to MX_DBG_CMD_CONTEXT_T structure
 *            Pointer to MX_DBG_CMD_Entry_T structure
 *            Character Double Pointer containing the command
 *
 *  @return   ERR_NOERR           successful,
 *            ERR_END_OF_CMD      help was requested,
 *            ERR_INVNAME         otherwise.
 *
 */

MX_Result OmxAllocUseBufferVerMismatch(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine)
{

  OMX_ERRORTYPE err = OMX_ErrorNone;
  unsigned int i = 0;
  unsigned char *pBuffer = NULL;
  OMTB_CLIENT_PRIVATE* thisClient = NULL;
  unsigned int instance = 0;
  char resultFileName[OMTB_MAX_LEN] = {"\0"};
  char fOpenMode[OMTB_MAX_LEN] = {"\0"};
  char testCaseId[OMTB_MAX_LEN] = {"\0"};
  char testCaseResult[OMTB_MAX_LEN] = {"\0"}; char returnString[OMTB_MAX_LEN] = {"\0"};
  FILE *fpResult = NULL;
  MX_Result  result = ERR_NOERR;
  char componentRequested[OMX_MAX_STRINGNAME_SIZE] = {"\0"};    
  OMTB_OMX_API_TIMING_VAR_DECL;

  /* Read component name */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, componentRequested);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }
  
  /* Read testcase ID */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, testCaseId);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }
  
  /* Read result filename */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, resultFileName);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }

  /* Read result file type */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, fOpenMode);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }
  
  /* Read instance Number */
  result = XdbgCmdNextNum(pContext, pCmdEntry, ppCmdLine, (UINT32 *)&instance);
  if (ERR_NOERR != result)
  {
    return result;
  }

  /* Open the result file */
  fpResult = fopen(resultFileName, fOpenMode);

  if(NULL == fpResult)
  {
    PRINT(PRINT_ERR_MSG, "%s: Error in result file open\n", __FUNCTION__);
    fprintf(fpResult, "%s : FAIL - Error in result file open\n", testCaseId);
    return ERR_INVNAME;
  }
  
  thisClient =  (OMTB_CLIENT_PRIVATE*)OMTB_GetCompPrivHandle(componentRequested, instance);
  
  /* validate the function arguments */
  ASSERT(NULL != thisClient);
  
  PRINT(PRINT_FUNCTION_NAME, "Entering <Function , instance #> : <%s , %d>\n",
                              __FUNCTION__, (int)thisClient->omtbPvt.instanceNo);

  /* Set the port params */
  if(NULL != thisClient->omtbPvt.fpSetPortDefinition)
    err = thisClient->omtbPvt.fpSetPortDefinition((void*)thisClient);  

  if(OMX_ErrorNone != err)
  {
    OMTB_OmxReturnStatusString(err, returnString);
    fprintf(fpResult, "%s : FAIL - Error in SetPortDefinition() OMX ERROR %s\n", testCaseId,returnString);
    fclose(fpResult);
    return ERR_INVNAME;
  }
  
  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;

  /* sending command to component for specified state transition */
  err = OMX_SendCommand(thisClient->omtbPvt.handle, OMX_CommandStateSet, OMX_StateIdle, NULL);

  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_SendCommand - OMX_CommandStateSet");

  if(OMX_ErrorNone != err)
  {
    OMTB_OmxReturnStatusString(err, returnString);
    fprintf(fpResult, "%s : FAIL - Error in OMX_SendCommand(OMX_StateIdle) OMX ERROR %s\n", testCaseId,returnString);
    fclose(fpResult);
    return ERR_INVNAME;
  }
  
  /* Input port buffer allocation */

  /* OMX_AllocateBuffer */
  if(OMX_FALSE == thisClient->inPortParams->cmnInParams.flagUseInBuffer)
  {
    /* API entry time calculation macro */
    OMTB_OMX_API_ENTRY_TIME_CALC;

    err = OMX_AllocateBuffer( 
                      thisClient->omtbPvt.handle,
                      &thisClient->inPortParams->pInBuff[i],
                      thisClient->inPortParams->cmnInParams.pInPortDef->nPortIndex, 
                      thisClient,
                      thisClient->inPortParams->cmnInParams.bufferInSize);

    /* API exit time calculation macro */
    OMTB_OMX_API_EXIT_TIME_CALC("OMX_AllocateBuffer");
  }
  /* OMX_UseBuffer */
  else
  {
    /* Allocating memory for input port buffer */
    pBuffer = (unsigned char*)TIMM_OSAL_Malloc(
                      thisClient->inPortParams->cmnInParams.bufferInSize,
                      (TIMM_OSAL_BOOL)thisClient->inPortParams->cmnInParams.inBufContiguous,
                      thisClient->inPortParams->cmnInParams.inBufAlignment,
                      TIMMOSAL_MEM_SEGMENT_EXT);
    
    if (!pBuffer)
    {
      PRINT(PRINT_ERR_MSG, \
          "Error in Buffer allocation for i/p port\n");

      /* Function to release the resources allocated by component */
      err = OMTB_ClientFreeResources(thisClient);

      if(OMX_ErrorNone != err)
      {
        OMTB_OmxReturnStatusString(err, returnString);
        strcpy(testCaseResult, "FAIL in releasing resources for UseBuffer");
        fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
        result = ERR_INVNAME;
      }
      
      strcpy(testCaseResult, "FAIL in buffer allocation for UseBuffer");
      fprintf(fpResult, "%s : %s\n", testCaseId, testCaseResult);
      result = ERR_INVNAME;
      fclose(fpResult);
      return result;
    }

    /* API entry time calculation macro */
    OMTB_OMX_API_ENTRY_TIME_CALC;

    err = OMX_UseBuffer(thisClient->omtbPvt.handle,
                    &thisClient->inPortParams->pInBuff[i],
                    thisClient->inPortParams->cmnInParams.pInPortDef->nPortIndex, 
                    thisClient,
                    thisClient->inPortParams->cmnInParams.bufferInSize,
                    pBuffer);

    /* API exit time calculation macro */
    OMTB_OMX_API_EXIT_TIME_CALC("OMX_UseBuffer");
  }

  if(OMX_ErrorVersionMismatch == err)
  {
    strcpy(testCaseResult, "PASS");
    fprintf(fpResult, "%s : %s\n", testCaseId, testCaseResult);
  }
  else
  {
    OMTB_OmxReturnStatusString(err, returnString);
    strcpy(testCaseResult, "FAIL");
    fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
    result = ERR_INVNAME;
  }

  /* Allocate I/O buffers & wait till transition to idle */
  err = (OMX_ERRORTYPE)OMTB_ClientAllocateOutputResources(thisClient);

  if(OMX_ErrorNone != err)
  {
    OMTB_OmxReturnStatusString(err, returnString);
    fprintf(fpResult, "%s : FAIL - Error in OMTB_ClientAllocateOutputResources() OMX ERROR %s\n", testCaseId,returnString);
    result = ERR_INVNAME;
  }
  
//  TIMM_OSAL_SemaphoreObtain(thisClient->omtbPvt.eventSem,
//                  TIMM_OSAL_SUSPEND);
  
  PRINT(PRINT_FUNCTION_NAME, "Leaving <Function , instance #> : <%s , %d>\n",
                              __FUNCTION__, (int)thisClient->omtbPvt.instanceNo);

  fclose(fpResult);
  return result;
}


/******************************************************************************\
 *      OmxAllocUseBufferTimeOut Function Definition
\******************************************************************************/
/**
 *
 *  @brief    This Function performs OMX_AllocateBuffer/OMX_UseBuffer API testing.
 *
 *  @param    Pointer to MX_DBG_CMD_CONTEXT_T structure
 *            Pointer to MX_DBG_CMD_Entry_T structure
 *            Character Double Pointer containing the command
 *
 *  @return   ERR_NOERR           successful,
 *            ERR_END_OF_CMD      help was requested,
 *            ERR_INVNAME         otherwise.
 *
 */

MX_Result OmxAllocUseBufferTimeOut(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine)
{

  OMX_ERRORTYPE err = OMX_ErrorNone;
  unsigned int i = 0;
  unsigned char *pBuffer = NULL;
  OMTB_CLIENT_PRIVATE* thisClient = NULL;
  unsigned int instance = 0;
  char resultFileName[OMTB_MAX_LEN] = {"\0"};
  char fOpenMode[OMTB_MAX_LEN] = {"\0"};
  char testCaseId[OMTB_MAX_LEN] = {"\0"};
  char testCaseResult[OMTB_MAX_LEN] = {"\0"}; char returnString[OMTB_MAX_LEN] = {"\0"};
  FILE *fpResult = NULL;
  MX_Result  result = ERR_NOERR;
  char componentRequested[OMX_MAX_STRINGNAME_SIZE] = {"\0"};    
  OMTB_OMX_API_TIMING_VAR_DECL;

  /* Read component name */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, componentRequested);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }
  
  /* Read testcase ID */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, testCaseId);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }
  
  /* Read result filename */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, resultFileName);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }

  /* Read result file type */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, fOpenMode);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }
  
  /* Read instance Number */
  result = XdbgCmdNextNum(pContext, pCmdEntry, ppCmdLine, (UINT32 *)&instance);
  if (ERR_NOERR != result)
  {
    return result;
  }

  /* Open the result file */
  fpResult = fopen(resultFileName, fOpenMode);

  if(NULL == fpResult)
  {
    PRINT(PRINT_ERR_MSG, "%s: Error in result file open\n", __FUNCTION__);
    fprintf(fpResult, "%s : FAIL - Error in result file open\n", testCaseId);
    return ERR_INVNAME;
  }
  
  thisClient =  (OMTB_CLIENT_PRIVATE*)OMTB_GetCompPrivHandle(componentRequested, instance);
  
  /* validate the function arguments */
  ASSERT(NULL != thisClient);
  
  PRINT(PRINT_FUNCTION_NAME, "Entering <Function , instance #> : <%s , %d>\n",
                              __FUNCTION__, (int)thisClient->omtbPvt.instanceNo);

  /* Set the port params */
  if(NULL != thisClient->omtbPvt.fpSetPortDefinition)
    err = thisClient->omtbPvt.fpSetPortDefinition((void*)thisClient);  

  if(OMX_ErrorNone != err)
  {
    OMTB_OmxReturnStatusString(err, returnString);
    fprintf(fpResult, "%s : FAIL - Error in SetPortDefinition() OMX ERROR %s\n", testCaseId,returnString);
    fclose(fpResult);
    return ERR_INVNAME;
  }
  
  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;

  /* sending command to component for specified state transition */
  err = OMX_SendCommand(thisClient->omtbPvt.handle, OMX_CommandStateSet, OMX_StateIdle, NULL);

  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_SendCommand - OMX_CommandStateSet");

  if(OMX_ErrorNone != err)
  {
    OMTB_OmxReturnStatusString(err, returnString);
    fprintf(fpResult, "%s : FAIL - Error in OMX_SendCommand(OMX_StateIdle) OMX ERROR %s\n", testCaseId,returnString);
    fclose(fpResult);
    return ERR_INVNAME;
  }
  
  /* Input port buffer allocation */

  /* OMX_AllocateBuffer */
  if(OMX_FALSE == thisClient->inPortParams->cmnInParams.flagUseInBuffer)
  {
    /* API entry time calculation macro */
    OMTB_OMX_API_ENTRY_TIME_CALC;

    err = OMX_AllocateBuffer( 
                      thisClient->omtbPvt.handle,
                      &thisClient->inPortParams->pInBuff[i],
                      thisClient->inPortParams->cmnInParams.pInPortDef->nPortIndex, 
                      thisClient,
                      thisClient->inPortParams->cmnInParams.bufferInSize);

    /* API exit time calculation macro */
    OMTB_OMX_API_EXIT_TIME_CALC("OMX_AllocateBuffer");
  }
  /* OMX_UseBuffer */
  else
  {
    /* Allocating memory for input port buffer */
    pBuffer = (unsigned char*)TIMM_OSAL_Malloc(
                      thisClient->inPortParams->cmnInParams.bufferInSize,
                      (TIMM_OSAL_BOOL)thisClient->inPortParams->cmnInParams.inBufContiguous,
                      thisClient->inPortParams->cmnInParams.inBufAlignment,
                      TIMMOSAL_MEM_SEGMENT_EXT);
    
    if (!pBuffer)
    {
      PRINT(PRINT_ERR_MSG, \
          "Error in Buffer allocation for i/p port\n");

      /* Function to release the resources allocated by component */
      err = OMTB_ClientFreeResources(thisClient);

      if(OMX_ErrorNone != err)
      {
        OMTB_OmxReturnStatusString(err, returnString);
        strcpy(testCaseResult, "FAIL in releasing resources for UseBuffer");
        fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
        result = ERR_INVNAME;
      }
      
      strcpy(testCaseResult, "FAIL in buffer allocation for UseBuffer");
      fprintf(fpResult, "%s : %s\n", testCaseId, testCaseResult);
      result = ERR_INVNAME;
      fclose(fpResult);
      return result;
    }

    /* API entry time calculation macro */
    OMTB_OMX_API_ENTRY_TIME_CALC;

    err = OMX_UseBuffer(thisClient->omtbPvt.handle,
                    &thisClient->inPortParams->pInBuff[i],
                    thisClient->inPortParams->cmnInParams.pInPortDef->nPortIndex, 
                    thisClient,
                    thisClient->inPortParams->cmnInParams.bufferInSize,
                    pBuffer);

    /* API exit time calculation macro */
    OMTB_OMX_API_EXIT_TIME_CALC("OMX_UseBuffer");
  }

  if(OMX_ErrorTimeout == err)
  {
    strcpy(testCaseResult, "PASS");
    fprintf(fpResult, "%s : %s\n", testCaseId, testCaseResult);
  }
  else
  {
    OMTB_OmxReturnStatusString(err, returnString);
    strcpy(testCaseResult, "FAIL");
    fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
    result = ERR_INVNAME;
  }

  /* Allocate I/O buffers & wait till transition to idle */
  err = (OMX_ERRORTYPE)OMTB_ClientAllocateOutputResources(thisClient);

  if(OMX_ErrorNone != err)
  {
    OMTB_OmxReturnStatusString(err, returnString);
    fprintf(fpResult, "%s : FAIL - Error in OMTB_ClientAllocateOutputResources() OMX ERROR %s\n", testCaseId,returnString);
    result = ERR_INVNAME;
  }
  
//  TIMM_OSAL_SemaphoreObtain(thisClient->omtbPvt.eventSem,
//                  TIMM_OSAL_SUSPEND);
  
  PRINT(PRINT_FUNCTION_NAME, "Leaving <Function , instance #> : <%s , %d>\n",
                              __FUNCTION__, (int)thisClient->omtbPvt.instanceNo);

  fclose(fpResult);
  return result;
}


/******************************************************************************\
 *      OmxAllocUseBufferWrongPort Function Definition
\******************************************************************************/
/**
 *
 *  @brief    This Function performs OMX_AllocateBuffer/OMX_UseBuffer API testing.
 *
 *  @param    Pointer to MX_DBG_CMD_CONTEXT_T structure
 *            Pointer to MX_DBG_CMD_Entry_T structure
 *            Character Double Pointer containing the command
 *
 *  @return   ERR_NOERR           successful,
 *            ERR_END_OF_CMD      help was requested,
 *            ERR_INVNAME         otherwise.
 *
 */

MX_Result OmxAllocUseBufferWrongPort(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine)
{

  OMX_ERRORTYPE err = OMX_ErrorNone;
  unsigned int i = 0;
  unsigned char *pBuffer = NULL;
  OMTB_CLIENT_PRIVATE* thisClient = NULL;
  unsigned int instance = 0;
  char resultFileName[OMTB_MAX_LEN] = {"\0"};
  char fOpenMode[OMTB_MAX_LEN] = {"\0"};
  char testCaseId[OMTB_MAX_LEN] = {"\0"};
  char testCaseResult[OMTB_MAX_LEN] = {"\0"}; char returnString[OMTB_MAX_LEN] = {"\0"};
  FILE *fpResult = NULL;
  MX_Result  result = ERR_NOERR;
  char componentRequested[OMX_MAX_STRINGNAME_SIZE] = {"\0"};    
  OMTB_OMX_API_TIMING_VAR_DECL;

  /* Read component name */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, componentRequested);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }
  
  /* Read testcase ID */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, testCaseId);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }
  
  /* Read result filename */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, resultFileName);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }

  /* Read result file type */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, fOpenMode);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }
  
  /* Read instance Number */
  result = XdbgCmdNextNum(pContext, pCmdEntry, ppCmdLine, (UINT32 *)&instance);
  if (ERR_NOERR != result)
  {
    return result;
  }

  /* Open the result file */
  fpResult = fopen(resultFileName, fOpenMode);

  if(NULL == fpResult)
  {
    PRINT(PRINT_ERR_MSG, "%s: Error in result file open\n", __FUNCTION__);
    fprintf(fpResult, "%s : FAIL - Error in result file open\n", testCaseId);
    return ERR_INVNAME;
  }
  
  thisClient =  (OMTB_CLIENT_PRIVATE*)OMTB_GetCompPrivHandle(componentRequested, instance);
  
  /* validate the function arguments */
  ASSERT(NULL != thisClient);
  
  PRINT(PRINT_FUNCTION_NAME, "Entering <Function , instance #> : <%s , %d>\n",
                              __FUNCTION__, (int)thisClient->omtbPvt.instanceNo);

  /* Set the port params */
  if(NULL != thisClient->omtbPvt.fpSetPortDefinition)
    err = thisClient->omtbPvt.fpSetPortDefinition((void*)thisClient);  

  if(OMX_ErrorNone != err)
  {
    OMTB_OmxReturnStatusString(err, returnString);
    fprintf(fpResult, "%s : FAIL - Error in SetPortDefinition() OMX ERROR %s\n", testCaseId,returnString);
    fclose(fpResult);
    return ERR_INVNAME;
  }
  
  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;

  /* sending command to component for specified state transition */
  err = OMX_SendCommand(thisClient->omtbPvt.handle, OMX_CommandStateSet, OMX_StateIdle, NULL);

  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_SendCommand - OMX_CommandStateSet");

  if(OMX_ErrorNone != err)
  {
    OMTB_OmxReturnStatusString(err, returnString);
    fprintf(fpResult, "%s : FAIL - Error in OMX_SendCommand(OMX_StateIdle) OMX ERROR %s\n", testCaseId,returnString);
    fclose(fpResult);
    return ERR_INVNAME;
  }
  
  /* Input port buffer allocation */

  /* OMX_AllocateBuffer */
  if(OMX_FALSE == thisClient->inPortParams->cmnInParams.flagUseInBuffer)
  {
    /* API entry time calculation macro */
    OMTB_OMX_API_ENTRY_TIME_CALC;

    err = OMX_AllocateBuffer( 
                      thisClient->omtbPvt.handle,
                      &thisClient->inPortParams->pInBuff[i],
                      OMTB_H264_VDEC_INVALID_PORT_IDX, 
                      thisClient,
                      thisClient->inPortParams->cmnInParams.bufferInSize);

    /* API exit time calculation macro */
    OMTB_OMX_API_EXIT_TIME_CALC("OMX_AllocateBuffer");
  }
  /* OMX_UseBuffer */
  else
  {
    /* Allocating memory for input port buffer */
    pBuffer = (unsigned char*)TIMM_OSAL_Malloc(
                      thisClient->inPortParams->cmnInParams.bufferInSize,
                      (TIMM_OSAL_BOOL)thisClient->inPortParams->cmnInParams.inBufContiguous,
                      thisClient->inPortParams->cmnInParams.inBufAlignment,
                      TIMMOSAL_MEM_SEGMENT_EXT);
    
    if (!pBuffer)
    {
      PRINT(PRINT_ERR_MSG, \
          "Error in Buffer allocation for i/p port\n");

      /* Function to release the resources allocated by component */
      err = OMTB_ClientFreeResources(thisClient);

      if(OMX_ErrorNone != err)
      {
        OMTB_OmxReturnStatusString(err, returnString);
        strcpy(testCaseResult, "FAIL in releasing resources for UseBuffer");
        fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
        result = ERR_INVNAME;
      }
      
      strcpy(testCaseResult, "FAIL in buffer allocation for UseBuffer");
      fprintf(fpResult, "%s : %s\n", testCaseId, testCaseResult);
      result = ERR_INVNAME;
      fclose(fpResult);
      return result;
    }

    /* API entry time calculation macro */
    OMTB_OMX_API_ENTRY_TIME_CALC;

    err = OMX_UseBuffer(thisClient->omtbPvt.handle,
                    &thisClient->inPortParams->pInBuff[i],
                    OMTB_H264_VDEC_INVALID_PORT_IDX, 
                    thisClient,
                    thisClient->inPortParams->cmnInParams.bufferInSize,
                    pBuffer);

    /* API exit time calculation macro */
    OMTB_OMX_API_EXIT_TIME_CALC("OMX_UseBuffer");
  }

  if(OMX_ErrorBadPortIndex == err)
  {
    strcpy(testCaseResult, "PASS");
    fprintf(fpResult, "%s : %s\n", testCaseId, testCaseResult);
  }
  else
  {
    OMTB_OmxReturnStatusString(err, returnString);
    strcpy(testCaseResult, "FAIL");
    fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
    result = ERR_INVNAME;
  }
  /* Allocate I/O buffers & wait till transition to idle */
  err = (OMX_ERRORTYPE)OMTB_ClientAllocateOutputResources(thisClient);

  if(OMX_ErrorNone != err)
  {
    OMTB_OmxReturnStatusString(err, returnString);
    fprintf(fpResult, "%s : FAIL - Error in OMTB_ClientAllocateOutputResources() OMX ERROR %s\n", testCaseId,returnString);
    result = ERR_INVNAME;
  }
  
//  TIMM_OSAL_SemaphoreObtain(thisClient->omtbPvt.eventSem,
//                  TIMM_OSAL_SUSPEND);
  
  PRINT(PRINT_FUNCTION_NAME, "Leaving <Function , instance #> : <%s , %d>\n",
                              __FUNCTION__, (int)thisClient->omtbPvt.instanceNo);

  fclose(fpResult);
  return result;
}


/******************************************************************************\
 *      OmxAllocUseBufferIdleState Function Definition
\******************************************************************************/
/**
 *
 *  @brief    This Function performs OMX_AllocateBuffer/OMX_UseBuffer API testing.
 *
 *  @param    Pointer to MX_DBG_CMD_CONTEXT_T structure
 *            Pointer to MX_DBG_CMD_Entry_T structure
 *            Character Double Pointer containing the command
 *
 *  @return   ERR_NOERR           successful,
 *            ERR_END_OF_CMD      help was requested,
 *            ERR_INVNAME         otherwise.
 *
 */

MX_Result OmxAllocUseBufferIdleState(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine)
{

  OMX_ERRORTYPE err = OMX_ErrorNone;
  unsigned int i = 0;
  unsigned char *pBuffer = NULL;
  OMTB_CLIENT_PRIVATE* thisClient = NULL;
  unsigned int instance = 0;
  char resultFileName[OMTB_MAX_LEN] = {"\0"};
  char fOpenMode[OMTB_MAX_LEN] = {"\0"};
  char testCaseId[OMTB_MAX_LEN] = {"\0"};
  char testCaseResult[OMTB_MAX_LEN] = {"\0"}; char returnString[OMTB_MAX_LEN] = {"\0"};
  FILE *fpResult = NULL;
  MX_Result  result = ERR_NOERR;
  char componentRequested[OMX_MAX_STRINGNAME_SIZE] = {"\0"};    
  OMTB_OMX_API_TIMING_VAR_DECL;

  /* Read component name */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, componentRequested);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }
  
  /* Read testcase ID */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, testCaseId);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }
  
  /* Read result filename */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, resultFileName);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }

  /* Read result file type */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, fOpenMode);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }
  
  /* Read instance Number */
  result = XdbgCmdNextNum(pContext, pCmdEntry, ppCmdLine, (UINT32 *)&instance);
  if (ERR_NOERR != result)
  {
    return result;
  }

  /* Open the result file */
  fpResult = fopen(resultFileName, fOpenMode);

  if(NULL == fpResult)
  {
    PRINT(PRINT_ERR_MSG, "%s: Error in result file open\n", __FUNCTION__);
    fprintf(fpResult, "%s : FAIL - Error in result file open\n", testCaseId);
    return ERR_INVNAME;
  }
  
  thisClient =  (OMTB_CLIENT_PRIVATE*)OMTB_GetCompPrivHandle(componentRequested, instance);
  
  /* validate the function arguments */
  ASSERT(NULL != thisClient);
  
  PRINT(PRINT_FUNCTION_NAME, "Entering <Function , instance #> : <%s , %d>\n",
                              __FUNCTION__, (int)thisClient->omtbPvt.instanceNo);

  /* Input port buffer allocation */

  /* OMX_AllocateBuffer */
  if(OMX_FALSE == thisClient->inPortParams->cmnInParams.flagUseInBuffer)
  {
    /* API entry time calculation macro */
    OMTB_OMX_API_ENTRY_TIME_CALC;

    err = OMX_AllocateBuffer( 
                      thisClient->omtbPvt.handle,
                      &thisClient->inPortParams->pInBuff[i],
                      thisClient->inPortParams->cmnInParams.pInPortDef->nPortIndex, 
                      thisClient,
                      thisClient->inPortParams->cmnInParams.bufferInSize);

    /* API exit time calculation macro */
    OMTB_OMX_API_EXIT_TIME_CALC("OMX_AllocateBuffer");
  }
  /* OMX_UseBuffer */
  else
  {
    /* Allocating memory for input port buffer */
    pBuffer = (unsigned char*)TIMM_OSAL_Malloc(
                      thisClient->inPortParams->cmnInParams.bufferInSize,
                      (TIMM_OSAL_BOOL)thisClient->inPortParams->cmnInParams.inBufContiguous,
                      thisClient->inPortParams->cmnInParams.inBufAlignment,
                      TIMMOSAL_MEM_SEGMENT_EXT);
    
    if (!pBuffer)
    {
      PRINT(PRINT_ERR_MSG, \
          "Error in Buffer allocation for i/p port\n");

      /* Function to release the resources allocated by component */
      err = OMTB_ClientFreeResources(thisClient);

      if(OMX_ErrorNone != err)
      {
        OMTB_OmxReturnStatusString(err, returnString);
        strcpy(testCaseResult, "FAIL in releasing resources for UseBuffer");
        fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
        result = ERR_INVNAME;
      }
      
      strcpy(testCaseResult, "FAIL in buffer allocation for UseBuffer");
      fprintf(fpResult, "%s : %s\n", testCaseId, testCaseResult);
      result = ERR_INVNAME;
      fclose(fpResult);
      return result;
    }

    /* API entry time calculation macro */
    OMTB_OMX_API_ENTRY_TIME_CALC;

    err = OMX_UseBuffer(thisClient->omtbPvt.handle,
                    &thisClient->inPortParams->pInBuff[i],
                    thisClient->inPortParams->cmnInParams.pInPortDef->nPortIndex, 
                    thisClient,
                    thisClient->inPortParams->cmnInParams.bufferInSize,
                    pBuffer);

    /* API exit time calculation macro */
    OMTB_OMX_API_EXIT_TIME_CALC("OMX_UseBuffer");
  }

  if(OMX_ErrorIncorrectStateOperation == err)
  {
    strcpy(testCaseResult, "PASS");
    fprintf(fpResult, "%s : %s\n", testCaseId, testCaseResult);
  }
  else
  {
    OMTB_OmxReturnStatusString(err, returnString);
    strcpy(testCaseResult, "FAIL");
    fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
    result = ERR_INVNAME;
  }

  PRINT(PRINT_FUNCTION_NAME, "Leaving <Function , instance #> : <%s , %d>\n",
                              __FUNCTION__, (int)thisClient->omtbPvt.instanceNo);

  fclose(fpResult);
  return result;
}


/******************************************************************************\
 *      OmxFreeBufferOnce Function Definition
\******************************************************************************/
/**
 *
 *  @brief    This Function performs OMX_FreeBuffer API testing.
 *
 *  @param    Pointer to MX_DBG_CMD_CONTEXT_T structure
 *            Pointer to MX_DBG_CMD_Entry_T structure
 *            Character Double Pointer containing the command
 *
 *  @return   ERR_NOERR           successful,
 *            ERR_END_OF_CMD      help was requested,
 *            ERR_INVNAME         otherwise.
 *
 */


MX_Result OmxFreeBufferOnce(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine)
{
  OMX_ERRORTYPE err = OMX_ErrorNone;
  unsigned int i = 0;
  OMTB_CLIENT_PRIVATE* thisClient = NULL;
  unsigned int instance = 0;
  char resultFileName[OMTB_MAX_LEN] = {"\0"};
  char fOpenMode[OMTB_MAX_LEN] = {"\0"};
  char testCaseId[OMTB_MAX_LEN] = {"\0"};
  char testCaseResult[OMTB_MAX_LEN] = {"\0"}; char returnString[OMTB_MAX_LEN] = {"\0"};
  FILE *fpResult = NULL;
  MX_Result  result = ERR_NOERR;
  OMX_STATETYPE prevState = OMX_StateInvalid;
  char componentRequested[OMX_MAX_STRINGNAME_SIZE] = {"\0"};    
  OMTB_OMX_API_TIMING_VAR_DECL;

  /* Read component name */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, componentRequested);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }
  
  /* Read testcase ID */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, testCaseId);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }
  
  /* Read result filename */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, resultFileName);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }

  /* Read result file type */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, fOpenMode);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }
  
  /* Read instance Number */
  result = XdbgCmdNextNum(pContext, pCmdEntry, ppCmdLine, (UINT32 *)&instance);
  if (ERR_NOERR != result)
  {
    return result;
  }

  /* Open the result file */
  fpResult = fopen(resultFileName, fOpenMode);

  if(NULL == fpResult)
  {
    PRINT(PRINT_ERR_MSG, "%s: Error in result file open\n", __FUNCTION__);
    fprintf(fpResult, "%s : FAIL - Error in result file open\n", testCaseId);
    return ERR_INVNAME;
  }
  
  thisClient =  (OMTB_CLIENT_PRIVATE*)OMTB_GetCompPrivHandle(componentRequested, instance);
  
  /* validate the function arguments */
  ASSERT(NULL != thisClient);
  
  PRINT(PRINT_FUNCTION_NAME, "Entering <Function , instance #> : <%s , %d>\n",
                              __FUNCTION__, (int)thisClient->omtbPvt.instanceNo);
  
  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;
  
  /* Get the current state of the component */
  err = OMX_GetState(thisClient->omtbPvt.handle, &prevState);

  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_GetState");

  if(OMX_ErrorNone != err)
  {
    OMTB_OmxReturnStatusString(err, returnString);
    fprintf(fpResult, "%s : FAIL - Error in OMX_GetState() OMX ERROR %s\n", testCaseId,returnString);
    fclose(fpResult);
    return ERR_INVNAME;
  }

  if(OMX_StateIdle != prevState)
  {
    /* API entry time calculation macro */
    OMTB_OMX_API_ENTRY_TIME_CALC;

    /* sending command to component for specified state transition */
    err = OMX_SendCommand(thisClient->omtbPvt.handle, OMX_CommandStateSet, OMX_StateIdle, NULL);

    /* API exit time calculation macro */
    OMTB_OMX_API_EXIT_TIME_CALC("OMX_SendCommand - OMX_CommandStateSet");

    if(OMX_ErrorNone != err)
    {
      OMTB_OmxReturnStatusString(err, returnString);
      fprintf(fpResult, "%s : FAIL - Error in OMX_SendCommand(OMX_StateIdle) OMX ERROR %s\n", testCaseId,returnString);
      fclose(fpResult);
      return ERR_INVNAME;
    }
  }
  
  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;

  /* sending command to component for specified state transition */
  err = OMX_SendCommand(thisClient->omtbPvt.handle, OMX_CommandStateSet, OMX_StateLoaded, NULL);

  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_SendCommand - OMX_CommandStateSet");

  if(OMX_ErrorNone != err)
  {
    OMTB_OmxReturnStatusString(err, returnString);
    fprintf(fpResult, "%s : FAIL - Error in OMX_SendCommand(OMX_StateLoaded) OMX ERROR %s\n", testCaseId,returnString);
    fclose(fpResult);
    return ERR_INVNAME;
  }

  
  /* Ask component to Free input port buffers */
  
  /* Release the memory allocated for buffer in case of OMX_UseBuffer */
  if(OMX_TRUE == thisClient->inPortParams->cmnInParams.flagUseInBuffer)
  {
    TIMM_OSAL_Free (thisClient->inPortParams->pInBuff[i]->pBuffer);
  }
  
  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;

  /* freeing buffers of component input ports */
  err = OMX_FreeBuffer( thisClient->omtbPvt.handle,
                    thisClient->inPortParams->cmnInParams.pInPortDef->nPortIndex,
                    thisClient->inPortParams->pInBuff[i]);

  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_FreeBuffer");

  if(OMX_ErrorNone == err)
  {
    strcpy(testCaseResult, "PASS");
    fprintf(fpResult, "%s : %s\n", testCaseId, testCaseResult);
  }
  else
  {
    OMTB_OmxReturnStatusString(err, returnString);
    strcpy(testCaseResult, "FAIL");
    fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
    result = ERR_INVNAME;
  }

  /* Free I/O buffers & wait till transition to idle */
  err = (OMX_ERRORTYPE)OMTB_ClientFreeOutputResources(thisClient);

  if(OMX_ErrorNone != err)
  {
    OMTB_OmxReturnStatusString(err, returnString);
    fprintf(fpResult, "%s : FAIL - Error in OMTB_ClientFreeOutputResources() OMX ERROR %s\n", testCaseId,returnString);
    result = ERR_INVNAME;
  }

  
//  TIMM_OSAL_SemaphoreObtain(thisClient->omtbPvt.eventSem,
//                  TIMM_OSAL_SUSPEND);
  
  PRINT(PRINT_FUNCTION_NAME, "Leaving <Function , instance #> : <%s , %d>\n",
                              __FUNCTION__, (int)thisClient->omtbPvt.instanceNo);

  fclose(fpResult);
  return result;
}


/******************************************************************************\
 *      OmxFreeBufferInsuffResources Function Definition
\******************************************************************************/
/**
 *
 *  @brief    This Function performs OMX_FreeBuffer API testing.
 *
 *  @param    Pointer to MX_DBG_CMD_CONTEXT_T structure
 *            Pointer to MX_DBG_CMD_Entry_T structure
 *            Character Double Pointer containing the command
 *
 *  @return   ERR_NOERR           successful,
 *            ERR_END_OF_CMD      help was requested,
 *            ERR_INVNAME         otherwise.
 *
 */


MX_Result OmxFreeBufferInsuffResources(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine)
{
  OMX_ERRORTYPE err = OMX_ErrorNone;
  unsigned int i = 0;
  OMTB_CLIENT_PRIVATE* thisClient = NULL;
  unsigned int instance = 0;
  char resultFileName[OMTB_MAX_LEN] = {"\0"};
  char fOpenMode[OMTB_MAX_LEN] = {"\0"};
  char testCaseId[OMTB_MAX_LEN] = {"\0"};
  char testCaseResult[OMTB_MAX_LEN] = {"\0"}; char returnString[OMTB_MAX_LEN] = {"\0"};
  FILE *fpResult = NULL;
  MX_Result  result = ERR_NOERR;
  OMX_STATETYPE prevState = OMX_StateInvalid;
  char componentRequested[OMX_MAX_STRINGNAME_SIZE] = {"\0"};    
  OMTB_OMX_API_TIMING_VAR_DECL;

  /* Read component name */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, componentRequested);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }
  
  /* Read testcase ID */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, testCaseId);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }
  
  /* Read result filename */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, resultFileName);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }

  /* Read result file type */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, fOpenMode);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }
  
  /* Read instance Number */
  result = XdbgCmdNextNum(pContext, pCmdEntry, ppCmdLine, (UINT32 *)&instance);
  if (ERR_NOERR != result)
  {
    return result;
  }

  /* Open the result file */
  fpResult = fopen(resultFileName, fOpenMode);

  if(NULL == fpResult)
  {
    PRINT(PRINT_ERR_MSG, "%s: Error in result file open\n", __FUNCTION__);
    fprintf(fpResult, "%s : FAIL - Error in result file open\n", testCaseId);
    return ERR_INVNAME;
  }
  
  thisClient =  (OMTB_CLIENT_PRIVATE*)OMTB_GetCompPrivHandle(componentRequested, instance);
  
  /* validate the function arguments */
  ASSERT(NULL != thisClient);
  
  PRINT(PRINT_FUNCTION_NAME, "Entering <Function , instance #> : <%s , %d>\n",
                              __FUNCTION__, (int)thisClient->omtbPvt.instanceNo);
  
  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;
  
  /* Get the current state of the component */
  err = OMX_GetState(thisClient->omtbPvt.handle, &prevState);

  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_GetState");

  if(OMX_ErrorNone != err)
  {
    OMTB_OmxReturnStatusString(err, returnString);
    fprintf(fpResult, "%s : FAIL - Error in OMX_GetState() OMX ERROR %s\n", testCaseId,returnString);
    fclose(fpResult);
    return ERR_INVNAME;
  }

  if(OMX_StateIdle != prevState)
  {
    /* API entry time calculation macro */
    OMTB_OMX_API_ENTRY_TIME_CALC;

    /* sending command to component for specified state transition */
    err = OMX_SendCommand(thisClient->omtbPvt.handle, OMX_CommandStateSet, OMX_StateIdle, NULL);

    /* API exit time calculation macro */
    OMTB_OMX_API_EXIT_TIME_CALC("OMX_SendCommand - OMX_CommandStateSet");

    if(OMX_ErrorNone != err)
    {
      OMTB_OmxReturnStatusString(err, returnString);
      fprintf(fpResult, "%s : FAIL - Error in OMX_SendCommand(OMX_StateIdle) OMX ERROR %s\n", testCaseId,returnString);
      fclose(fpResult);
      return ERR_INVNAME;
    }
  }
  
  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;

  /* sending command to component for specified state transition */
  err = OMX_SendCommand(thisClient->omtbPvt.handle, OMX_CommandStateSet, OMX_StateLoaded, NULL);

  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_SendCommand - OMX_CommandStateSet");

  if(OMX_ErrorNone != err)
  {
    OMTB_OmxReturnStatusString(err, returnString);
    fprintf(fpResult, "%s : FAIL - Error in OMX_SendCommand(OMX_StateLoaded) OMX ERROR %s\n", testCaseId,returnString);
    fclose(fpResult);
    return ERR_INVNAME;
  }

  
  /* Ask component to Free input port buffers */
  
  /* Release the memory allocated for buffer in case of OMX_UseBuffer */
  if(OMX_TRUE == thisClient->inPortParams->cmnInParams.flagUseInBuffer)
  {
    TIMM_OSAL_Free (thisClient->inPortParams->pInBuff[i]->pBuffer);
  }
  
  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;

  /* freeing buffers of component input ports */
  err = OMX_FreeBuffer( thisClient->omtbPvt.handle,
                    thisClient->inPortParams->cmnInParams.pInPortDef->nPortIndex,
                    thisClient->inPortParams->pInBuff[i]);

  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_FreeBuffer");

  if(OMX_ErrorInsufficientResources == err)
  {
    strcpy(testCaseResult, "PASS");
    fprintf(fpResult, "%s : %s\n", testCaseId, testCaseResult);
  }
  else
  {
    OMTB_OmxReturnStatusString(err, returnString);
    strcpy(testCaseResult, "FAIL");
    fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
    result = ERR_INVNAME;
  }

  /* Free I/O buffers & wait till transition to idle */
  err = (OMX_ERRORTYPE)OMTB_ClientFreeOutputResources(thisClient);

  if(OMX_ErrorNone != err)
  {
    OMTB_OmxReturnStatus(err);
    fprintf(fpResult, "%s : FAIL - Error in OMTB_ClientFreeOutputResources()\n", testCaseId);
    result = ERR_INVNAME;
  }
  
//  TIMM_OSAL_SemaphoreObtain(thisClient->omtbPvt.eventSem,
//                  TIMM_OSAL_SUSPEND);
  
  PRINT(PRINT_FUNCTION_NAME, "Leaving <Function , instance #> : <%s , %d>\n",
                              __FUNCTION__, (int)thisClient->omtbPvt.instanceNo);

  fclose(fpResult);
  return result;
}


/******************************************************************************\
 *      OmxFreeBufferNullBufferHdr Function Definition
\******************************************************************************/
/**
 *
 *  @brief    This Function performs OMX_FreeBuffer API testing.
 *
 *  @param    Pointer to MX_DBG_CMD_CONTEXT_T structure
 *            Pointer to MX_DBG_CMD_Entry_T structure
 *            Character Double Pointer containing the command
 *
 *  @return   ERR_NOERR           successful,
 *            ERR_END_OF_CMD      help was requested,
 *            ERR_INVNAME         otherwise.
 *
 */


MX_Result OmxFreeBufferNullBufferHdr(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine)
{
  OMX_ERRORTYPE err = OMX_ErrorNone;
  OMTB_CLIENT_PRIVATE* thisClient = NULL;
  unsigned int instance = 0, i = 0;
  char resultFileName[OMTB_MAX_LEN] = {"\0"};
  char fOpenMode[OMTB_MAX_LEN] = {"\0"};
  char testCaseId[OMTB_MAX_LEN] = {"\0"};
  char testCaseResult[OMTB_MAX_LEN] = {"\0"}; char returnString[OMTB_MAX_LEN] = {"\0"};
  FILE *fpResult = NULL;
  MX_Result  result = ERR_NOERR;
  OMX_STATETYPE prevState = OMX_StateInvalid;
  char componentRequested[OMX_MAX_STRINGNAME_SIZE] = {"\0"};    
  OMTB_OMX_API_TIMING_VAR_DECL;

  /* Read component name */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, componentRequested);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }
  
  /* Read testcase ID */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, testCaseId);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }
  
  /* Read result filename */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, resultFileName);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }

  /* Read result file type */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, fOpenMode);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }
  
  /* Read instance Number */
  result = XdbgCmdNextNum(pContext, pCmdEntry, ppCmdLine, (UINT32 *)&instance);
  if (ERR_NOERR != result)
  {
    return result;
  }

  /* Open the result file */
  fpResult = fopen(resultFileName, fOpenMode);

  if(NULL == fpResult)
  {
    PRINT(PRINT_ERR_MSG, "%s: Error in result file open\n", __FUNCTION__);
    fprintf(fpResult, "%s : FAIL - Error in result file open\n", testCaseId);
    return ERR_INVNAME;
  }
  
  thisClient =  (OMTB_CLIENT_PRIVATE*)OMTB_GetCompPrivHandle(componentRequested, instance);
  
  /* validate the function arguments */
  ASSERT(NULL != thisClient);
  
  PRINT(PRINT_FUNCTION_NAME, "Entering <Function , instance #> : <%s , %d>\n",
                              __FUNCTION__, (int)thisClient->omtbPvt.instanceNo);
  
  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;
  
  /* Get the current state of the component */
  err = OMX_GetState(thisClient->omtbPvt.handle, &prevState);

  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_GetState");

  if(OMX_ErrorNone != err)
  if(OMX_ErrorNone != err)
  {
    OMTB_OmxReturnStatusString(err, returnString);
    fprintf(fpResult, "%s : FAIL - Error in OMX_GetState() OMX ERROR %s\n", testCaseId,returnString);
    fclose(fpResult);
    return ERR_INVNAME;
  }

  if(OMX_StateIdle != prevState)
  {
    /* API entry time calculation macro */
    OMTB_OMX_API_ENTRY_TIME_CALC;

    /* sending command to component for specified state transition */
    err = OMX_SendCommand(thisClient->omtbPvt.handle, OMX_CommandStateSet, OMX_StateIdle, NULL);

    /* API exit time calculation macro */
    OMTB_OMX_API_EXIT_TIME_CALC("OMX_SendCommand - OMX_CommandStateSet");

      if(OMX_ErrorNone != err)
    {
      OMTB_OmxReturnStatusString(err, returnString);
      fprintf(fpResult, "%s : FAIL - Error in OMX_SendCommand(OMX_StateIdle) OMX ERROR %s\n", testCaseId,returnString);
      fclose(fpResult);
      return ERR_INVNAME;
    }
  }

  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;

  /* sending command to component for specified state transition */
  err = OMX_SendCommand(thisClient->omtbPvt.handle, OMX_CommandStateSet, OMX_StateLoaded, NULL);

  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_SendCommand - OMX_CommandStateSet");

  if(OMX_ErrorNone != err)
  {
    OMTB_OmxReturnStatus(err);
    fprintf(fpResult, "%s : FAIL - Error in OMX_SendCommand(OMX_StateLoaded)\n", testCaseId);
    fclose(fpResult);
    return ERR_INVNAME;
  }  
  
  /* Ask component to Free input port buffers */
  
  /* Release the memory allocated for buffer in case of OMX_UseBuffer */
  if(OMX_TRUE == thisClient->inPortParams->cmnInParams.flagUseInBuffer)
  {
    TIMM_OSAL_Free (thisClient->inPortParams->pInBuff[i]->pBuffer);
  }
  
  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;

  /* freeing buffers of component input ports */
  err = OMX_FreeBuffer( thisClient->omtbPvt.handle,
                    thisClient->inPortParams->cmnInParams.pInPortDef->nPortIndex,
                    NULL);

  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_FreeBuffer");

  if(OMX_ErrorBadParameter == err)
  {
    strcpy(testCaseResult, "PASS");
    fprintf(fpResult, "%s : %s\n", testCaseId, testCaseResult);
  }
  else
  {
    OMTB_OmxReturnStatusString(err, returnString);
    strcpy(testCaseResult, "FAIL");
    fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
    result = ERR_INVNAME;
  }

  /* Free I/O buffers & wait till transition to idle */
  err = (OMX_ERRORTYPE)OMTB_ClientFreeOutputResources(thisClient);

    if(OMX_ErrorNone != err)
  {
    OMTB_OmxReturnStatusString(err, returnString);
    fprintf(fpResult, "%s : FAIL - Error in OMTB_ClientFreeOutputResources() OMX ERROR %s\n", testCaseId,returnString);
    result = ERR_INVNAME;
  }
  
//  TIMM_OSAL_SemaphoreObtain(thisClient->omtbPvt.eventSem,
//                  TIMM_OSAL_SUSPEND);
  
  PRINT(PRINT_FUNCTION_NAME, "Leaving <Function , instance #> : <%s , %d>\n",
                              __FUNCTION__, (int)thisClient->omtbPvt.instanceNo);

  fclose(fpResult);
  return result;
}


/******************************************************************************\
 *      OmxFreeBufferNullHandle Function Definition
\******************************************************************************/
/**
 *
 *  @brief    This Function performs OMX_FreeBuffer API testing.
 *
 *  @param    Pointer to MX_DBG_CMD_CONTEXT_T structure
 *            Pointer to MX_DBG_CMD_Entry_T structure
 *            Character Double Pointer containing the command
 *
 *  @return   ERR_NOERR           successful,
 *            ERR_END_OF_CMD      help was requested,
 *            ERR_INVNAME         otherwise.
 *
 */


MX_Result OmxFreeBufferNullHandle(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine)
{
  OMX_ERRORTYPE err = OMX_ErrorNone;
  unsigned int i = 0;
  OMTB_CLIENT_PRIVATE* thisClient = NULL;
  unsigned int instance = 0;
  char resultFileName[OMTB_MAX_LEN] = {"\0"};
  char fOpenMode[OMTB_MAX_LEN] = {"\0"};
  char testCaseId[OMTB_MAX_LEN] = {"\0"};
  char testCaseResult[OMTB_MAX_LEN] = {"\0"}; char returnString[OMTB_MAX_LEN] = {"\0"};
  FILE *fpResult = NULL;
  MX_Result  result = ERR_NOERR;
  OMX_STATETYPE prevState = OMX_StateInvalid;
  char componentRequested[OMX_MAX_STRINGNAME_SIZE] = {"\0"};    
  OMTB_OMX_API_TIMING_VAR_DECL;

  /* Read component name */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, componentRequested);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }
  
  /* Read testcase ID */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, testCaseId);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }
  
  /* Read result filename */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, resultFileName);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }

  /* Read result file type */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, fOpenMode);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }
  
  /* Read instance Number */
  result = XdbgCmdNextNum(pContext, pCmdEntry, ppCmdLine, (UINT32 *)&instance);
  if (ERR_NOERR != result)
  {
    return result;
  }

  /* Open the result file */
  fpResult = fopen(resultFileName, fOpenMode);

  if(NULL == fpResult)
  {
    PRINT(PRINT_ERR_MSG, "%s: Error in result file open\n", __FUNCTION__);
    fprintf(fpResult, "%s : FAIL - Error in result file open\n", testCaseId);
    return ERR_INVNAME;
  }
  
  thisClient =  (OMTB_CLIENT_PRIVATE*)OMTB_GetCompPrivHandle(componentRequested, instance);
  
  /* validate the function arguments */
  ASSERT(NULL != thisClient);
  
  PRINT(PRINT_FUNCTION_NAME, "Entering <Function , instance #> : <%s , %d>\n",
                              __FUNCTION__, (int)thisClient->omtbPvt.instanceNo);
  
  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;
  
  /* Get the current state of the component */
  err = OMX_GetState(thisClient->omtbPvt.handle, &prevState);

  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_GetState");

  if(OMX_ErrorNone != err)
  {
    OMTB_OmxReturnStatusString(err, returnString);
    fprintf(fpResult, "%s : FAIL - Error in OMX_GetState() OMX ERROR %s\n", testCaseId,returnString);
    fclose(fpResult);
    return ERR_INVNAME;
  }

  if(OMX_StateIdle != prevState)
  {
    /* API entry time calculation macro */
    OMTB_OMX_API_ENTRY_TIME_CALC;

    /* sending command to component for specified state transition */
    err = OMX_SendCommand(thisClient->omtbPvt.handle, OMX_CommandStateSet, OMX_StateIdle, NULL);

    /* API exit time calculation macro */
    OMTB_OMX_API_EXIT_TIME_CALC("OMX_SendCommand - OMX_CommandStateSet");

      if(OMX_ErrorNone != err)
    {
      OMTB_OmxReturnStatusString(err, returnString);
      fprintf(fpResult, "%s : FAIL - Error in OMX_SendCommand(OMX_StateIdle) OMX ERROR %s\n", testCaseId,returnString);
      fclose(fpResult);
      return ERR_INVNAME;
    }
  }

  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;

  /* sending command to component for specified state transition */
  err = OMX_SendCommand(thisClient->omtbPvt.handle, OMX_CommandStateSet, OMX_StateLoaded, NULL);

  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_SendCommand - OMX_CommandStateSet");

 if(OMX_ErrorNone != err)
  {
    OMTB_OmxReturnStatusString(err, returnString);
    fprintf(fpResult, "%s : FAIL - Error in OMX_SendCommand(OMX_StateLoaded) OMX ERROR %s\n", testCaseId,returnString);
    fclose(fpResult);
    return ERR_INVNAME;
  }
  
  /* Ask component to Free input port buffers */
  
  /* Release the memory allocated for buffer in case of OMX_UseBuffer */
  if(OMX_TRUE == thisClient->inPortParams->cmnInParams.flagUseInBuffer)
  {
    TIMM_OSAL_Free (thisClient->inPortParams->pInBuff[i]->pBuffer);
  }
  
  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;

  /* freeing buffers of component input ports */
  err = OMX_FreeBuffer( NULL,
                    thisClient->inPortParams->cmnInParams.pInPortDef->nPortIndex,
                    thisClient->inPortParams->pInBuff[i]);

  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_FreeBuffer");

  if(OMX_ErrorBadParameter == err)
  {
    strcpy(testCaseResult, "PASS");
    fprintf(fpResult, "%s : %s\n", testCaseId, testCaseResult);
  }
  else
  {
    OMTB_OmxReturnStatusString(err, returnString);
    strcpy(testCaseResult, "FAIL");
    fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
    result = ERR_INVNAME;
  }

  /* Free I/O buffers & wait till transition to idle */
  err = (OMX_ERRORTYPE)OMTB_ClientFreeOutputResources(thisClient);

    if(OMX_ErrorNone != err)
  {
    OMTB_OmxReturnStatusString(err, returnString);
    fprintf(fpResult, "%s : FAIL - Error in OMTB_ClientFreeOutputResources() OMX ERROR %s\n", testCaseId,returnString);
    result = ERR_INVNAME;
  }
  
//  TIMM_OSAL_SemaphoreObtain(thisClient->omtbPvt.eventSem,
//                  TIMM_OSAL_SUSPEND);
  
  PRINT(PRINT_FUNCTION_NAME, "Leaving <Function , instance #> : <%s , %d>\n",
                              __FUNCTION__, (int)thisClient->omtbPvt.instanceNo);

  fclose(fpResult);
  return result;
}


/******************************************************************************\
 *      OmxFreeBufferVerMismatch Function Definition
\******************************************************************************/
/**
 *
 *  @brief    This Function performs OMX_FreeBuffer API testing.
 *
 *  @param    Pointer to MX_DBG_CMD_CONTEXT_T structure
 *            Pointer to MX_DBG_CMD_Entry_T structure
 *            Character Double Pointer containing the command
 *
 *  @return   ERR_NOERR           successful,
 *            ERR_END_OF_CMD      help was requested,
 *            ERR_INVNAME         otherwise.
 *
 */


MX_Result OmxFreeBufferVerMismatch(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine)
{
  OMX_ERRORTYPE err = OMX_ErrorNone;
  unsigned int i = 0;
  OMTB_CLIENT_PRIVATE* thisClient = NULL;
  unsigned int instance = 0;
  char resultFileName[OMTB_MAX_LEN] = {"\0"};
  char fOpenMode[OMTB_MAX_LEN] = {"\0"};
  char testCaseId[OMTB_MAX_LEN] = {"\0"};
  char testCaseResult[OMTB_MAX_LEN] = {"\0"}; char returnString[OMTB_MAX_LEN] = {"\0"};
  FILE *fpResult = NULL;
  MX_Result  result = ERR_NOERR;
  OMX_STATETYPE prevState = OMX_StateInvalid;
  char componentRequested[OMX_MAX_STRINGNAME_SIZE] = {"\0"};    
  OMTB_OMX_API_TIMING_VAR_DECL;

  /* Read component name */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, componentRequested);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }
  
  /* Read testcase ID */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, testCaseId);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }
  
  /* Read result filename */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, resultFileName);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }

  /* Read result file type */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, fOpenMode);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }
  
  /* Read instance Number */
  result = XdbgCmdNextNum(pContext, pCmdEntry, ppCmdLine, (UINT32 *)&instance);
  if (ERR_NOERR != result)
  {
    return result;
  }

  /* Open the result file */
  fpResult = fopen(resultFileName, fOpenMode);

  if(NULL == fpResult)
  {
    PRINT(PRINT_ERR_MSG, "%s: Error in result file open\n", __FUNCTION__);
    fprintf(fpResult, "%s : FAIL - Error in result file open\n", testCaseId);
    return ERR_INVNAME;
  }
  
  thisClient =  (OMTB_CLIENT_PRIVATE*)OMTB_GetCompPrivHandle(componentRequested, instance);
  
  /* validate the function arguments */
  ASSERT(NULL != thisClient);
  
  PRINT(PRINT_FUNCTION_NAME, "Entering <Function , instance #> : <%s , %d>\n",
                              __FUNCTION__, (int)thisClient->omtbPvt.instanceNo);
  
  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;
  
  /* Get the current state of the component */
  err = OMX_GetState(thisClient->omtbPvt.handle, &prevState);

  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_GetState");

  if(OMX_ErrorNone != err)
  {
    OMTB_OmxReturnStatusString(err, returnString);
    fprintf(fpResult, "%s : FAIL - Error in OMX_GetState() OMX ERROR %s\n", testCaseId,returnString);
    fclose(fpResult);
    return ERR_INVNAME;
  }

  if(OMX_StateIdle != prevState)
  {
    /* API entry time calculation macro */
    OMTB_OMX_API_ENTRY_TIME_CALC;

    /* sending command to component for specified state transition */
    err = OMX_SendCommand(thisClient->omtbPvt.handle, OMX_CommandStateSet, OMX_StateIdle, NULL);

    /* API exit time calculation macro */
    OMTB_OMX_API_EXIT_TIME_CALC("OMX_SendCommand - OMX_CommandStateSet");

      if(OMX_ErrorNone != err)
    {
      OMTB_OmxReturnStatusString(err, returnString);
      fprintf(fpResult, "%s : FAIL - Error in OMX_SendCommand(OMX_StateIdle) OMX ERROR %s\n", testCaseId,returnString);
      fclose(fpResult);
      return ERR_INVNAME;
    }
  }

  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;

  /* sending command to component for specified state transition */
  err = OMX_SendCommand(thisClient->omtbPvt.handle, OMX_CommandStateSet, OMX_StateLoaded, NULL);

  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_SendCommand - OMX_CommandStateSet");

 if(OMX_ErrorNone != err)
  {
    OMTB_OmxReturnStatusString(err, returnString);
    fprintf(fpResult, "%s : FAIL - Error in OMX_SendCommand(OMX_StateLoaded) OMX ERROR %s\n", testCaseId,returnString);
    fclose(fpResult);
    return ERR_INVNAME;
  }
  
  /* Ask component to Free input port buffers */
  
  /* Release the memory allocated for buffer in case of OMX_UseBuffer */
  if(OMX_TRUE == thisClient->inPortParams->cmnInParams.flagUseInBuffer)
  {
    TIMM_OSAL_Free (thisClient->inPortParams->pInBuff[i]->pBuffer);
  }
  
  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;

  /* freeing buffers of component input ports */
  err = OMX_FreeBuffer( thisClient->omtbPvt.handle,
                    thisClient->inPortParams->cmnInParams.pInPortDef->nPortIndex,
                    thisClient->inPortParams->pInBuff[i]);

  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_FreeBuffer");

  if(OMX_ErrorVersionMismatch == err)
  {
    strcpy(testCaseResult, "PASS");
    fprintf(fpResult, "%s : %s\n", testCaseId, testCaseResult);
  }
  else
  {
    OMTB_OmxReturnStatusString(err, returnString);
    strcpy(testCaseResult, "FAIL");
    fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
    result = ERR_INVNAME;
  }

  /* Free I/O buffers & wait till transition to idle */
  err = (OMX_ERRORTYPE)OMTB_ClientFreeOutputResources(thisClient);

    if(OMX_ErrorNone != err)
  {
    OMTB_OmxReturnStatusString(err, returnString);
    fprintf(fpResult, "%s : FAIL - Error in OMTB_ClientFreeOutputResources() OMX ERROR %s\n", testCaseId,returnString);
    result = ERR_INVNAME;
  }
  
//  TIMM_OSAL_SemaphoreObtain(thisClient->omtbPvt.eventSem,
//                  TIMM_OSAL_SUSPEND);
  
  PRINT(PRINT_FUNCTION_NAME, "Leaving <Function , instance #> : <%s , %d>\n",
                              __FUNCTION__, (int)thisClient->omtbPvt.instanceNo);

  fclose(fpResult);
  return result;
}


/******************************************************************************\
 *      OmxFreeBufferTimeOut Function Definition
\******************************************************************************/
/**
 *
 *  @brief    This Function performs OMX_FreeBuffer API testing.
 *
 *  @param    Pointer to MX_DBG_CMD_CONTEXT_T structure
 *            Pointer to MX_DBG_CMD_Entry_T structure
 *            Character Double Pointer containing the command
 *
 *  @return   ERR_NOERR           successful,
 *            ERR_END_OF_CMD      help was requested,
 *            ERR_INVNAME         otherwise.
 *
 */


MX_Result OmxFreeBufferTimeOut(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine)
{
  OMX_ERRORTYPE err = OMX_ErrorNone;
  unsigned int i = 0;
  OMTB_CLIENT_PRIVATE* thisClient = NULL;
  unsigned int instance = 0;
  char resultFileName[OMTB_MAX_LEN] = {"\0"};
  char fOpenMode[OMTB_MAX_LEN] = {"\0"};
  char testCaseId[OMTB_MAX_LEN] = {"\0"};
  char testCaseResult[OMTB_MAX_LEN] = {"\0"}; char returnString[OMTB_MAX_LEN] = {"\0"};
  FILE *fpResult = NULL;
  MX_Result  result = ERR_NOERR;
  OMX_STATETYPE prevState = OMX_StateInvalid;
  char componentRequested[OMX_MAX_STRINGNAME_SIZE] = {"\0"};    
  OMTB_OMX_API_TIMING_VAR_DECL;

  /* Read component name */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, componentRequested);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }
  
  /* Read testcase ID */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, testCaseId);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }
  
  /* Read result filename */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, resultFileName);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }

  /* Read result file type */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, fOpenMode);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }
  
  /* Read instance Number */
  result = XdbgCmdNextNum(pContext, pCmdEntry, ppCmdLine, (UINT32 *)&instance);
  if (ERR_NOERR != result)
  {
    return result;
  }

  /* Open the result file */
  fpResult = fopen(resultFileName, fOpenMode);

  if(NULL == fpResult)
  {
    PRINT(PRINT_ERR_MSG, "%s: Error in result file open\n", __FUNCTION__);
    fprintf(fpResult, "%s : FAIL - Error in result file open\n", testCaseId);
    return ERR_INVNAME;
  }
  
  thisClient =  (OMTB_CLIENT_PRIVATE*)OMTB_GetCompPrivHandle(componentRequested, instance);
  
  /* validate the function arguments */
  ASSERT(NULL != thisClient);
  
  PRINT(PRINT_FUNCTION_NAME, "Entering <Function , instance #> : <%s , %d>\n",
                              __FUNCTION__, (int)thisClient->omtbPvt.instanceNo);
  
  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;
  
  /* Get the current state of the component */
  err = OMX_GetState(thisClient->omtbPvt.handle, &prevState);

  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_GetState");

  if(OMX_ErrorNone != err)
  {
    OMTB_OmxReturnStatusString(err, returnString);
    fprintf(fpResult, "%s : FAIL - Error in OMX_GetState() OMX ERROR %s\n", testCaseId,returnString);
    fclose(fpResult);
    return ERR_INVNAME;
  }

  if(OMX_StateIdle != prevState)
  {
    /* API entry time calculation macro */
    OMTB_OMX_API_ENTRY_TIME_CALC;

    /* sending command to component for specified state transition */
    err = OMX_SendCommand(thisClient->omtbPvt.handle, OMX_CommandStateSet, OMX_StateIdle, NULL);

    /* API exit time calculation macro */
    OMTB_OMX_API_EXIT_TIME_CALC("OMX_SendCommand - OMX_CommandStateSet");

    if(OMX_ErrorNone != err)
    {
      OMTB_OmxReturnStatusString(err, returnString);
      fprintf(fpResult, "%s : FAIL - Error in OMX_SendCommand(OMX_StateIdle) OMX ERROR %s\n", testCaseId,returnString);
      fclose(fpResult);
      return ERR_INVNAME;
    }
  }

  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;

  /* sending command to component for specified state transition */
  err = OMX_SendCommand(thisClient->omtbPvt.handle, OMX_CommandStateSet, OMX_StateLoaded, NULL);

  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_SendCommand - OMX_CommandStateSet");

  if(OMX_ErrorNone != err)
  {
    OMTB_OmxReturnStatusString(err, returnString);
    fprintf(fpResult, "%s : FAIL - Error in OMX_SendCommand(OMX_StateLoaded) OMX ERROR %s\n", testCaseId,returnString);
    fclose(fpResult);
    return ERR_INVNAME;
  }
  
  /* Ask component to Free input port buffers */
  
  /* Release the memory allocated for buffer in case of OMX_UseBuffer */
  if(OMX_TRUE == thisClient->inPortParams->cmnInParams.flagUseInBuffer)
  {
    TIMM_OSAL_Free (thisClient->inPortParams->pInBuff[i]->pBuffer);
  }
  
  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;

  /* freeing buffers of component input ports */
  err = OMX_FreeBuffer( thisClient->omtbPvt.handle,
                    thisClient->inPortParams->cmnInParams.pInPortDef->nPortIndex,
                    thisClient->inPortParams->pInBuff[i]);

  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_FreeBuffer");

  if(OMX_ErrorTimeout == err)
  {
    strcpy(testCaseResult, "PASS");
    fprintf(fpResult, "%s : %s\n", testCaseId, testCaseResult);
  }
  else
  {
    OMTB_OmxReturnStatusString(err, returnString);
    strcpy(testCaseResult, "FAIL");
    fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
    result = ERR_INVNAME;
  }

  /* Free I/O buffers & wait till transition to idle */
  err = (OMX_ERRORTYPE)OMTB_ClientFreeOutputResources(thisClient);

  if(OMX_ErrorNone != err)
  {
    OMTB_OmxReturnStatusString(err, returnString);
    fprintf(fpResult, "%s : FAIL - Error in OMTB_ClientFreeOutputResources() OMX ERROR %s\n", testCaseId,returnString);
    result = ERR_INVNAME;
  }
  
//  TIMM_OSAL_SemaphoreObtain(thisClient->omtbPvt.eventSem,
//                  TIMM_OSAL_SUSPEND);
  
  PRINT(PRINT_FUNCTION_NAME, "Leaving <Function , instance #> : <%s , %d>\n",
                              __FUNCTION__, (int)thisClient->omtbPvt.instanceNo);

  fclose(fpResult);
  return result;
}


/******************************************************************************\
 *      OmxFreeBufferWrongPort Function Definition
\******************************************************************************/
/**
 *
 *  @brief    This Function performs OMX_FreeBuffer API testing.
 *
 *  @param    Pointer to MX_DBG_CMD_CONTEXT_T structure
 *            Pointer to MX_DBG_CMD_Entry_T structure
 *            Character Double Pointer containing the command
 *
 *  @return   ERR_NOERR           successful,
 *            ERR_END_OF_CMD      help was requested,
 *            ERR_INVNAME         otherwise.
 *
 */


MX_Result OmxFreeBufferWrongPort(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine)
{
  OMX_ERRORTYPE err = OMX_ErrorNone;
  unsigned int i = 0;
  OMTB_CLIENT_PRIVATE* thisClient = NULL;
  unsigned int instance = 0;
  char resultFileName[OMTB_MAX_LEN] = {"\0"};
  char fOpenMode[OMTB_MAX_LEN] = {"\0"};
  char testCaseId[OMTB_MAX_LEN] = {"\0"};
  char testCaseResult[OMTB_MAX_LEN] = {"\0"}; char returnString[OMTB_MAX_LEN] = {"\0"};
  FILE *fpResult = NULL;
  MX_Result  result = ERR_NOERR;
  OMX_STATETYPE prevState = OMX_StateInvalid;
  char componentRequested[OMX_MAX_STRINGNAME_SIZE] = {"\0"};    
  OMTB_OMX_API_TIMING_VAR_DECL;

  /* Read component name */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, componentRequested);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }
  
  /* Read testcase ID */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, testCaseId);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }
  
  /* Read result filename */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, resultFileName);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }

  /* Read result file type */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, fOpenMode);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }
  
  /* Read instance Number */
  result = XdbgCmdNextNum(pContext, pCmdEntry, ppCmdLine, (UINT32 *)&instance);
  if (ERR_NOERR != result)
  {
    return result;
  }

  /* Open the result file */
  fpResult = fopen(resultFileName, fOpenMode);

  if(NULL == fpResult)
  {
    PRINT(PRINT_ERR_MSG, "%s: Error in result file open\n", __FUNCTION__);
    fprintf(fpResult, "%s : FAIL - Error in result file open\n", testCaseId);
    return ERR_INVNAME;
  }
  
  thisClient =  (OMTB_CLIENT_PRIVATE*)OMTB_GetCompPrivHandle(componentRequested, instance);
  
  /* validate the function arguments */
  ASSERT(NULL != thisClient);
  
  PRINT(PRINT_FUNCTION_NAME, "Entering <Function , instance #> : <%s , %d>\n",
                              __FUNCTION__, (int)thisClient->omtbPvt.instanceNo);
  
  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;
  
  /* Get the current state of the component */
  err = OMX_GetState(thisClient->omtbPvt.handle, &prevState);

  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_GetState");

  if(OMX_ErrorNone != err)
  {
    OMTB_OmxReturnStatusString(err, returnString);
    fprintf(fpResult, "%s : FAIL - Error in OMX_GetState() OMX ERROR %s\n", testCaseId,returnString);
    fclose(fpResult);
    return ERR_INVNAME;
  }

  if(OMX_StateIdle != prevState)
  {
    /* API entry time calculation macro */
    OMTB_OMX_API_ENTRY_TIME_CALC;

    /* sending command to component for specified state transition */
    err = OMX_SendCommand(thisClient->omtbPvt.handle, OMX_CommandStateSet, OMX_StateIdle, NULL);

    /* API exit time calculation macro */
    OMTB_OMX_API_EXIT_TIME_CALC("OMX_SendCommand - OMX_CommandStateSet");

    if(OMX_ErrorNone != err)
    {
      OMTB_OmxReturnStatusString(err, returnString);
      fprintf(fpResult, "%s : FAIL - Error in OMX_SendCommand(OMX_StateIdle) OMX ERROR %s\n", testCaseId,returnString);
      fclose(fpResult);
      return ERR_INVNAME;
    }
  }

  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;

  /* sending command to component for specified state transition */
  err = OMX_SendCommand(thisClient->omtbPvt.handle, OMX_CommandStateSet, OMX_StateLoaded, NULL);

  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_SendCommand - OMX_CommandStateSet");

  if(OMX_ErrorNone != err)
 if(OMX_ErrorNone != err)
  {
    OMTB_OmxReturnStatusString(err, returnString);
    fprintf(fpResult, "%s : FAIL - Error in OMX_SendCommand(OMX_StateLoaded) OMX ERROR %s\n", testCaseId,returnString);
    fclose(fpResult);
    return ERR_INVNAME;
  }
  
  /* Ask component to Free input port buffers */
  
  /* Release the memory allocated for buffer in case of OMX_UseBuffer */
  if(OMX_TRUE == thisClient->inPortParams->cmnInParams.flagUseInBuffer)
  {
    TIMM_OSAL_Free (thisClient->inPortParams->pInBuff[i]->pBuffer);
  }
  
  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;

  /* freeing buffers of component input ports */
  err = OMX_FreeBuffer( thisClient->omtbPvt.handle,
                    OMTB_H264_VDEC_INVALID_PORT_IDX,
                    thisClient->inPortParams->pInBuff[i]);

  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_FreeBuffer");

  if(OMX_ErrorBadPortIndex == err)
  {
    strcpy(testCaseResult, "PASS");
    fprintf(fpResult, "%s : %s\n", testCaseId, testCaseResult);
  }
  else
  {
    OMTB_OmxReturnStatusString(err, returnString);
    strcpy(testCaseResult, "FAIL");
    fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
    result = ERR_INVNAME;
  }

  /* Free I/O buffers & wait till transition to idle */
  err = (OMX_ERRORTYPE)OMTB_ClientFreeOutputResources(thisClient);

    if(OMX_ErrorNone != err)
  {
    OMTB_OmxReturnStatusString(err, returnString);
    fprintf(fpResult, "%s : FAIL - Error in OMTB_ClientFreeOutputResources() OMX ERROR %s\n", testCaseId,returnString);
    result = ERR_INVNAME;
  }
  
//  TIMM_OSAL_SemaphoreObtain(thisClient->omtbPvt.eventSem,
//                  TIMM_OSAL_SUSPEND);
  
  PRINT(PRINT_FUNCTION_NAME, "Leaving <Function , instance #> : <%s , %d>\n",
                              __FUNCTION__, (int)thisClient->omtbPvt.instanceNo);

  fclose(fpResult);
  return result;
}


/******************************************************************************\
 *      OmxFreeBufferIdleState Function Definition
\******************************************************************************/
/**
 *
 *  @brief    This Function performs OMX_FreeBuffer API testing.
 *
 *  @param    Pointer to MX_DBG_CMD_CONTEXT_T structure
 *            Pointer to MX_DBG_CMD_Entry_T structure
 *            Character Double Pointer containing the command
 *
 *  @return   ERR_NOERR           successful,
 *            ERR_END_OF_CMD      help was requested,
 *            ERR_INVNAME         otherwise.
 *
 */


MX_Result OmxFreeBufferIdleState(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine)
{
  OMX_ERRORTYPE err = OMX_ErrorNone;
  unsigned int i = 0;
  OMTB_CLIENT_PRIVATE* thisClient = NULL;
  unsigned int instance = 0;
  char resultFileName[OMTB_MAX_LEN] = {"\0"};
  char fOpenMode[OMTB_MAX_LEN] = {"\0"};
  char testCaseId[OMTB_MAX_LEN] = {"\0"};
  char testCaseResult[OMTB_MAX_LEN] = {"\0"}; char returnString[OMTB_MAX_LEN] = {"\0"};
  FILE *fpResult = NULL;
  MX_Result  result = ERR_NOERR;
  char componentRequested[OMX_MAX_STRINGNAME_SIZE] = {"\0"};    
  OMTB_OMX_API_TIMING_VAR_DECL;

  /* Read component name */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, componentRequested);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }
  
  /* Read testcase ID */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, testCaseId);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }
  
  /* Read result filename */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, resultFileName);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }

  /* Read result file type */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, fOpenMode);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }
  
  /* Read instance Number */
  result = XdbgCmdNextNum(pContext, pCmdEntry, ppCmdLine, (UINT32 *)&instance);
  if (ERR_NOERR != result)
  {
    return result;
  }

  /* Open the result file */
  fpResult = fopen(resultFileName, fOpenMode);

  if(NULL == fpResult)
  {
    PRINT(PRINT_ERR_MSG, "%s: Error in result file open\n", __FUNCTION__);
    fprintf(fpResult, "%s : FAIL - Error in result file open\n", testCaseId);
    return ERR_INVNAME;
  }
  
  thisClient =  (OMTB_CLIENT_PRIVATE*)OMTB_GetCompPrivHandle(componentRequested, instance);
  
  /* validate the function arguments */
  ASSERT(NULL != thisClient);
  
  PRINT(PRINT_FUNCTION_NAME, "Entering <Function , instance #> : <%s , %d>\n",
                              __FUNCTION__, (int)thisClient->omtbPvt.instanceNo);
  
  /* Ask component to Free input port buffers */
  
  /* Release the memory allocated for buffer in case of OMX_UseBuffer */
  if(OMX_TRUE == thisClient->inPortParams->cmnInParams.flagUseInBuffer)
  {
    TIMM_OSAL_Free (thisClient->inPortParams->pInBuff[i]->pBuffer);
  }
  
  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;

  /* freeing buffers of component input ports */
  err = OMX_FreeBuffer( thisClient->omtbPvt.handle,
                    thisClient->inPortParams->cmnInParams.pInPortDef->nPortIndex,
                    thisClient->inPortParams->pInBuff[i]);

  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_FreeBuffer");

  if(OMX_ErrorPortUnpopulated == err)
  {
    strcpy(testCaseResult, "PASS");
    fprintf(fpResult, "%s : %s\n", testCaseId, testCaseResult);
  }
  else
  {
    OMTB_OmxReturnStatusString(err, returnString);
    strcpy(testCaseResult, "FAIL");
    fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
    result = ERR_INVNAME;
  }

  PRINT(PRINT_FUNCTION_NAME, "Leaving <Function , instance #> : <%s , %d>\n",
                              __FUNCTION__, (int)thisClient->omtbPvt.instanceNo);

  fclose(fpResult);
  return result;
}


/******************************************************************************\
 *      OMTB_OmxSetParameterOnce Function Definition
\******************************************************************************/
/**
 *
 *  @brief    This Function performs OMX_SetParameter API testing.
 *
 *  @param    Pointer to MX_DBG_CMD_CONTEXT_T structure
 *            Pointer to MX_DBG_CMD_Entry_T structure
 *            Character Double Pointer containing the command
 *
 *  @return   ERR_NOERR           successful,
 *            ERR_END_OF_CMD      help was requested,
 *            ERR_INVNAME         otherwise.

 *
 */

MX_Result OMTB_OmxSetParameterOnce(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine)
{
  OMX_ERRORTYPE err = OMX_ErrorNone;
  unsigned int instance = 0;
  char resultFileName[OMTB_MAX_LEN] = {"\0"};
  char fOpenMode[OMTB_MAX_LEN] = {"\0"};
  char testCaseId[OMTB_MAX_LEN] = {"\0"};
  char testCaseResult[OMTB_MAX_LEN] = {"\0"}; char returnString[OMTB_MAX_LEN] = {"\0"};
  FILE *fpResult = NULL;
  MX_Result  result = ERR_NOERR;
  OMTB_CLIENT_PRIVATE* thisClient = NULL;
  char componentRequested[OMX_MAX_STRINGNAME_SIZE] = {"\0"};    
  OMTB_OMX_API_TIMING_VAR_DECL;

  /* Read component name */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, componentRequested);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }
  
  
  /* Read testcase ID */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, testCaseId);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }
  
  /* Read result filename */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, resultFileName);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }

  /* Read result file type */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, fOpenMode);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }
  
  /* Read instance Number */
  result = XdbgCmdNextNum(pContext, pCmdEntry, ppCmdLine, (UINT32 *)&instance);
  if (ERR_NOERR != result)
  {
    return result;
  }

  /* Open the result file */
  fpResult = fopen(resultFileName, fOpenMode);

  if(NULL == fpResult)
  {
    PRINT(PRINT_ERR_MSG, "%s: Error in result file open\n", __FUNCTION__);
    fprintf(fpResult, "%s : FAIL - Error in result file open\n", testCaseId);
    return ERR_INVNAME;
  }
  
  thisClient =  (OMTB_CLIENT_PRIVATE*)OMTB_GetCompPrivHandle(componentRequested, instance); 

  /* Set the component's OMX_PARAM_PORTDEFINITIONTYPE structure (input) */
  OMTB_SetHeader( thisClient->inPortParams->cmnInParams.pInPortDef,
                  sizeof(OMX_PARAM_PORTDEFINITIONTYPE));

  thisClient->inPortParams->cmnInParams.pInPortDef->nPortIndex = OMTB_H264_VDEC_INPUT_PORT_IDX;
  
  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;
  
  /*Set the inPort Definition*/
  err = OMX_GetParameter( thisClient->omtbPvt.handle,
                          OMX_IndexParamPortDefinition,
                          thisClient->inPortParams->cmnInParams.pInPortDef);
  
  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_GetParameter");

  if(OMX_ErrorNone != err)
  {
    OMTB_OmxReturnStatusString(err, returnString);
    strcpy(testCaseResult, "FAIL in OMX_GetParameter()");
    fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
    result = ERR_INVNAME;
  }

  /* Set the component's OMX_PARAM_PORTDEFINITIONTYPE structure (input) */
  OMTB_SetHeader( thisClient->inPortParams->cmnInParams.pInPortDef,
                  sizeof(OMX_PARAM_PORTDEFINITIONTYPE));

  thisClient->inPortParams->cmnInParams.pInPortDef->nPortIndex = OMTB_H264_VDEC_INPUT_PORT_IDX;
  
  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;
  
  /* Send the portInit parameter structure */
  err = OMX_SetParameter( thisClient->omtbPvt.handle,
                          OMX_IndexParamPortDefinition,
                          thisClient->inPortParams->cmnInParams.pInPortDef);
  
  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_SetParameter");
  
  if(OMX_ErrorNone == err)
  {
    strcpy(testCaseResult, "PASS");
    fprintf(fpResult, "%s : %s\n", testCaseId, testCaseResult);
  }
  else
  {
    OMTB_OmxReturnStatusString(err, returnString);
    strcpy(testCaseResult, "FAIL");
    fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
    result = ERR_INVNAME;
  }

  fclose(fpResult);
  return result;
}


/******************************************************************************\
 *      OMTB_OmxSetParameterNullCfgStruct Function Definition
\******************************************************************************/
/**
 *
 *  @brief    This Function performs OMX_SetParameter API testing.
 *
 *  @param    Pointer to MX_DBG_CMD_CONTEXT_T structure
 *            Pointer to MX_DBG_CMD_Entry_T structure
 *            Character Double Pointer containing the command
 *
 *  @return   ERR_NOERR           successful,
 *            ERR_END_OF_CMD      help was requested,
 *            ERR_INVNAME         otherwise.

 *
 */

MX_Result OMTB_OmxSetParameterNullCfgStruct(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine)
{
  OMX_ERRORTYPE err = OMX_ErrorNone;
  unsigned int instance = 0;
  char resultFileName[OMTB_MAX_LEN] = {"\0"};
  char fOpenMode[OMTB_MAX_LEN] = {"\0"};
  char testCaseId[OMTB_MAX_LEN] = {"\0"};
  char testCaseResult[OMTB_MAX_LEN] = {"\0"}; char returnString[OMTB_MAX_LEN] = {"\0"};
  FILE *fpResult = NULL;
  MX_Result  result = ERR_NOERR;
  OMTB_CLIENT_PRIVATE* thisClient = NULL;
  char componentRequested[OMX_MAX_STRINGNAME_SIZE] = {"\0"};    
  OMTB_OMX_API_TIMING_VAR_DECL;

  /* Read component name */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, componentRequested);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }
  
  /* Read testcase ID */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, testCaseId);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }
  
  /* Read result filename */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, resultFileName);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }

  /* Read result file type */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, fOpenMode);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }
  
  /* Read instance Number */
  result = XdbgCmdNextNum(pContext, pCmdEntry, ppCmdLine, (UINT32 *)&instance);
  if (ERR_NOERR != result)
  {
    return result;
  }

  /* Open the result file */
  fpResult = fopen(resultFileName, fOpenMode);

  if(NULL == fpResult)
  {
    PRINT(PRINT_ERR_MSG, "%s: Error in result file open\n", __FUNCTION__);
    fprintf(fpResult, "%s : FAIL - Error in result file open\n", testCaseId);
    return ERR_INVNAME;
  }
  
    thisClient =  (OMTB_CLIENT_PRIVATE*)OMTB_GetCompPrivHandle(componentRequested, instance); 

  /* Set the component's OMX_PARAM_PORTDEFINITIONTYPE structure (input) */
  OMTB_SetHeader( thisClient->inPortParams->cmnInParams.pInPortDef,
                  sizeof(OMX_PARAM_PORTDEFINITIONTYPE));

  thisClient->inPortParams->cmnInParams.pInPortDef->nPortIndex = OMTB_H264_VDEC_INPUT_PORT_IDX;
  
  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;
  
  /*Set the inPort Definition*/
  err = OMX_GetParameter( thisClient->omtbPvt.handle,
                          OMX_IndexParamPortDefinition,
                          thisClient->inPortParams->cmnInParams.pInPortDef);
  
  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_GetParameter");

  if(OMX_ErrorNone != err)
  {
    OMTB_OmxReturnStatusString(err, returnString);
    strcpy(testCaseResult, "FAIL in OMX_GetParameter()");
    fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
    result = ERR_INVNAME;
  }

  /* Set the component's OMX_PARAM_PORTDEFINITIONTYPE structure (input) */
  OMTB_SetHeader( thisClient->inPortParams->cmnInParams.pInPortDef,
                  sizeof(OMX_PARAM_PORTDEFINITIONTYPE));

  thisClient->inPortParams->cmnInParams.pInPortDef->nPortIndex = OMTB_H264_VDEC_INPUT_PORT_IDX;
  
  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;
  
  /* Send the portInit parameter structure */
  err = OMX_SetParameter( thisClient->omtbPvt.handle,
                          OMX_IndexParamPortDefinition,
                          NULL);
  
  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_SetParameter");
  
  if(OMX_ErrorBadParameter == err)
  {
    strcpy(testCaseResult, "PASS");
    fprintf(fpResult, "%s : %s\n", testCaseId, testCaseResult);
  }
  else
  {
    OMTB_OmxReturnStatusString(err, returnString);
    strcpy(testCaseResult, "FAIL");
    fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
    result = ERR_INVNAME;
  }

  fclose(fpResult);
  return result;
}


/******************************************************************************\
 *      OMTB_OmxSetParameterOnce Function Definition
\******************************************************************************/
/**
 *
 *  @brief    This Function performs OMX_SetParameter API testing.
 *
 *  @param    Pointer to MX_DBG_CMD_CONTEXT_T structure
 *            Pointer to MX_DBG_CMD_Entry_T structure
 *            Character Double Pointer containing the command
 *
 *  @return   ERR_NOERR           successful,
 *            ERR_END_OF_CMD      help was requested,
 *            ERR_INVNAME         otherwise.

 *
 */

MX_Result OMTB_OmxSetParameterNullHandle(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine)
{
  OMX_ERRORTYPE err = OMX_ErrorNone;
  unsigned int instance = 0;
  char resultFileName[OMTB_MAX_LEN] = {"\0"};
  char fOpenMode[OMTB_MAX_LEN] = {"\0"};
  char testCaseId[OMTB_MAX_LEN] = {"\0"};
  char testCaseResult[OMTB_MAX_LEN] = {"\0"}; char returnString[OMTB_MAX_LEN] = {"\0"};
  FILE *fpResult = NULL;
  MX_Result  result = ERR_NOERR;
  OMTB_CLIENT_PRIVATE* thisClient = NULL;
  char componentRequested[OMX_MAX_STRINGNAME_SIZE] = {"\0"};    
  OMTB_OMX_API_TIMING_VAR_DECL;

  /* Read component name */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, componentRequested);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }
  
  /* Read testcase ID */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, testCaseId);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }
  
  /* Read result filename */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, resultFileName);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }

  /* Read result file type */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, fOpenMode);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }
  
  /* Read instance Number */
  result = XdbgCmdNextNum(pContext, pCmdEntry, ppCmdLine, (UINT32 *)&instance);
  if (ERR_NOERR != result)
  {
    return result;
  }

  /* Open the result file */
  fpResult = fopen(resultFileName, fOpenMode);

  if(NULL == fpResult)
  {
    PRINT(PRINT_ERR_MSG, "%s: Error in result file open\n", __FUNCTION__);
    fprintf(fpResult, "%s : FAIL - Error in result file open\n", testCaseId);
    return ERR_INVNAME;
  }
  
    thisClient =  (OMTB_CLIENT_PRIVATE*)OMTB_GetCompPrivHandle(componentRequested, instance); 

  /* Set the component's OMX_PARAM_PORTDEFINITIONTYPE structure (input) */
  OMTB_SetHeader( thisClient->inPortParams->cmnInParams.pInPortDef,
                  sizeof(OMX_PARAM_PORTDEFINITIONTYPE));

  thisClient->inPortParams->cmnInParams.pInPortDef->nPortIndex = OMTB_H264_VDEC_INPUT_PORT_IDX;
  
  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;
  
  /*Set the inPort Definition*/
  err = OMX_GetParameter( thisClient->omtbPvt.handle,
                          OMX_IndexParamPortDefinition,
                          thisClient->inPortParams->cmnInParams.pInPortDef);
  
  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_GetParameter");

  if(OMX_ErrorNone != err)
  {
    OMTB_OmxReturnStatusString(err, returnString);
    strcpy(testCaseResult, "FAIL in OMX_GetParameter()");
    fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
    result = ERR_INVNAME;
  }

  /* Set the component's OMX_PARAM_PORTDEFINITIONTYPE structure (input) */
  OMTB_SetHeader( thisClient->inPortParams->cmnInParams.pInPortDef,
                  sizeof(OMX_PARAM_PORTDEFINITIONTYPE));

  thisClient->inPortParams->cmnInParams.pInPortDef->nPortIndex = OMTB_H264_VDEC_INPUT_PORT_IDX;
  
  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;
  
  /* Send the portInit parameter structure */
  err = OMX_SetParameter( NULL,
                          OMX_IndexParamPortDefinition,
                          thisClient->inPortParams->cmnInParams.pInPortDef);
  
  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_SetParameter");
  
  if(OMX_ErrorBadParameter == err)
  {
    strcpy(testCaseResult, "PASS");
    fprintf(fpResult, "%s : %s\n", testCaseId, testCaseResult);
  }
  else
  {
    OMTB_OmxReturnStatusString(err, returnString);
    strcpy(testCaseResult, "FAIL");
    fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
    result = ERR_INVNAME;
  }

  fclose(fpResult);
  return result;
}


/******************************************************************************\
 *      OMTB_OmxSetParameterVerMismatch Function Definition
\******************************************************************************/
/**
 *
 *  @brief    This Function performs OMX_SetParameter API testing.
 *
 *  @param    Pointer to MX_DBG_CMD_CONTEXT_T structure
 *            Pointer to MX_DBG_CMD_Entry_T structure
 *            Character Double Pointer containing the command
 *
 *  @return   ERR_NOERR           successful,
 *            ERR_END_OF_CMD      help was requested,
 *            ERR_INVNAME         otherwise.

 *
 */

MX_Result OMTB_OmxSetParameterVerMismatch(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine)
{
  OMX_ERRORTYPE err = OMX_ErrorNone;
  unsigned int instance = 0;
  char resultFileName[OMTB_MAX_LEN] = {"\0"};
  char fOpenMode[OMTB_MAX_LEN] = {"\0"};
  char testCaseId[OMTB_MAX_LEN] = {"\0"};
  char testCaseResult[OMTB_MAX_LEN] = {"\0"}; char returnString[OMTB_MAX_LEN] = {"\0"};
  FILE *fpResult = NULL;
  MX_Result  result = ERR_NOERR;
  OMTB_CLIENT_PRIVATE* thisClient = NULL;
  char componentRequested[OMX_MAX_STRINGNAME_SIZE] = {"\0"};    
  OMTB_OMX_API_TIMING_VAR_DECL;

  /* Read component name */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, componentRequested);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }
  
  /* Read testcase ID */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, testCaseId);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }
  
  /* Read result filename */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, resultFileName);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }

  /* Read result file type */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, fOpenMode);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }
  
  /* Read instance Number */
  result = XdbgCmdNextNum(pContext, pCmdEntry, ppCmdLine, (UINT32 *)&instance);
  if (ERR_NOERR != result)
  {
    return result;
  }

  /* Open the result file */
  fpResult = fopen(resultFileName, fOpenMode);

  if(NULL == fpResult)
  {
    PRINT(PRINT_ERR_MSG, "%s: Error in result file open\n", __FUNCTION__);
    fprintf(fpResult, "%s : FAIL - Error in result file open\n", testCaseId);
    return ERR_INVNAME;
  }
  
    thisClient =  (OMTB_CLIENT_PRIVATE*)OMTB_GetCompPrivHandle(componentRequested, instance); 

  /* Set the component's OMX_PARAM_PORTDEFINITIONTYPE structure (input) */
  OMTB_SetHeader( thisClient->inPortParams->cmnInParams.pInPortDef,
                  sizeof(OMX_PARAM_PORTDEFINITIONTYPE));

  thisClient->inPortParams->cmnInParams.pInPortDef->nPortIndex = OMTB_H264_VDEC_INPUT_PORT_IDX;
  
  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;
  
  /*Set the inPort Definition*/
  err = OMX_GetParameter( thisClient->omtbPvt.handle,
                          OMX_IndexParamPortDefinition,
                          thisClient->inPortParams->cmnInParams.pInPortDef);
  
  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_GetParameter");

  if(OMX_ErrorNone != err)
  {
    OMTB_OmxReturnStatusString(err, returnString);
    strcpy(testCaseResult, "FAIL in OMX_GetParameter()");
    fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
    result = ERR_INVNAME;
  }

  /* set incorrect version numbers */
  thisClient->inPortParams->cmnInParams.pInPortDef->nSize = sizeof(OMX_PARAM_PORTDEFINITIONTYPE);
  thisClient->inPortParams->cmnInParams.pInPortDef->nVersion.s.nVersionMajor = 1;
  thisClient->inPortParams->cmnInParams.pInPortDef->nVersion.s.nVersionMinor = 2;
  thisClient->inPortParams->cmnInParams.pInPortDef->nVersion.s.nRevision = 0;
  thisClient->inPortParams->cmnInParams.pInPortDef->nVersion.s.nRevision = 0;

  thisClient->inPortParams->cmnInParams.pInPortDef->nPortIndex = OMTB_H264_VDEC_INPUT_PORT_IDX;
  
  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;
  
  /* Send the portInit parameter structure */
  err = OMX_SetParameter( thisClient->omtbPvt.handle,
                          OMX_IndexParamPortDefinition,
                          thisClient->inPortParams->cmnInParams.pInPortDef);
  
  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_SetParameter");
  
  if(OMX_ErrorVersionMismatch == err)
  {
    strcpy(testCaseResult, "PASS");
    fprintf(fpResult, "%s : %s\n", testCaseId, testCaseResult);
  }
  else
  {
    OMTB_OmxReturnStatusString(err, returnString);
    strcpy(testCaseResult, "FAIL");
    fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
    result = ERR_INVNAME;
  }

  fclose(fpResult);
  return result;
}


/******************************************************************************\
 *      OMTB_OmxSetParameterTimeOut Function Definition
\******************************************************************************/
/**
 *
 *  @brief    This Function performs OMX_SetParameter API testing.
 *
 *  @param    Pointer to MX_DBG_CMD_CONTEXT_T structure
 *            Pointer to MX_DBG_CMD_Entry_T structure
 *            Character Double Pointer containing the command
 *
 *  @return   ERR_NOERR           successful,
 *            ERR_END_OF_CMD      help was requested,
 *            ERR_INVNAME         otherwise.

 *
 */

MX_Result OMTB_OmxSetParameterTimeOut(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine)
{
  OMX_ERRORTYPE err = OMX_ErrorNone;
  unsigned int instance = 0;
  char resultFileName[OMTB_MAX_LEN] = {"\0"};
  char fOpenMode[OMTB_MAX_LEN] = {"\0"};
  char testCaseId[OMTB_MAX_LEN] = {"\0"};
  char testCaseResult[OMTB_MAX_LEN] = {"\0"}; char returnString[OMTB_MAX_LEN] = {"\0"};
  FILE *fpResult = NULL;
  MX_Result  result = ERR_NOERR;
  OMTB_CLIENT_PRIVATE* thisClient = NULL;
  char componentRequested[OMX_MAX_STRINGNAME_SIZE] = {"\0"};    
  OMTB_OMX_API_TIMING_VAR_DECL;

  /* Read component name */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, componentRequested);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }
  
  /* Read testcase ID */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, testCaseId);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }
  
  /* Read result filename */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, resultFileName);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }

  /* Read result file type */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, fOpenMode);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }
  
  /* Read instance Number */
  result = XdbgCmdNextNum(pContext, pCmdEntry, ppCmdLine, (UINT32 *)&instance);
  if (ERR_NOERR != result)
  {
    return result;
  }

  /* Open the result file */
  fpResult = fopen(resultFileName, fOpenMode);

  if(NULL == fpResult)
  {
    PRINT(PRINT_ERR_MSG, "%s: Error in result file open\n", __FUNCTION__);
    fprintf(fpResult, "%s : FAIL - Error in result file open\n", testCaseId);
    return ERR_INVNAME;
  }
  
    thisClient =  (OMTB_CLIENT_PRIVATE*)OMTB_GetCompPrivHandle(componentRequested, instance); 

  /* Set the component's OMX_PARAM_PORTDEFINITIONTYPE structure (input) */
  OMTB_SetHeader( thisClient->inPortParams->cmnInParams.pInPortDef,
                  sizeof(OMX_PARAM_PORTDEFINITIONTYPE));

  thisClient->inPortParams->cmnInParams.pInPortDef->nPortIndex = OMTB_H264_VDEC_INPUT_PORT_IDX;
  
  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;
  
  /*Set the inPort Definition*/
  err = OMX_GetParameter( thisClient->omtbPvt.handle,
                          OMX_IndexParamPortDefinition,
                          thisClient->inPortParams->cmnInParams.pInPortDef);
  
  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_GetParameter");

  if(OMX_ErrorNone != err)
  {
    OMTB_OmxReturnStatus(err);
    strcpy(testCaseResult, "FAIL in OMX_GetParameter()");
    fprintf(fpResult, "%s : %s\n", testCaseId, testCaseResult);
    result = ERR_INVNAME;
  }

  /* Set the component's OMX_PARAM_PORTDEFINITIONTYPE structure (input) */
  OMTB_SetHeader( thisClient->inPortParams->cmnInParams.pInPortDef,
                  sizeof(OMX_PARAM_PORTDEFINITIONTYPE));

  thisClient->inPortParams->cmnInParams.pInPortDef->nPortIndex = OMTB_H264_VDEC_INPUT_PORT_IDX;
  
  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;
  
  /* Send the portInit parameter structure */
  err = OMX_SetParameter( thisClient->omtbPvt.handle,
                          OMX_IndexParamPortDefinition,
                          thisClient->inPortParams->cmnInParams.pInPortDef);
  
  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_SetParameter");
  
  if(OMX_ErrorTimeout == err)
  {
    strcpy(testCaseResult, "PASS");
    fprintf(fpResult, "%s : %s\n", testCaseId, testCaseResult);
  }
  else
  {
    OMTB_OmxReturnStatusString(err, returnString);
    strcpy(testCaseResult, "FAIL");
    fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
    result = ERR_INVNAME;
  }

  fclose(fpResult);
  return result;
}

/******************************************************************************\
 *      OMTB_OmxSetParameterUnSupportedSettings Function Definition
\******************************************************************************/
/**
 *
 *  @brief    This Function performs OMX_SetParameter API testing.
 *
 *  @param    Pointer to MX_DBG_CMD_CONTEXT_T structure
 *            Pointer to MX_DBG_CMD_Entry_T structure
 *            Character Double Pointer containing the command
 *
 *  @return   ERR_NOERR           successful,
 *            ERR_END_OF_CMD      help was requested,
 *            ERR_INVNAME         otherwise.

 *
 */

MX_Result OMTB_OmxSetParameterUnSupportedSettings(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine)
{
  OMX_ERRORTYPE err = OMX_ErrorNone;
  unsigned int instance = 0;
  char resultFileName[OMTB_MAX_LEN] = {"\0"};
  char fOpenMode[OMTB_MAX_LEN] = {"\0"};
  char testCaseId[OMTB_MAX_LEN] = {"\0"};
  char testCaseResult[OMTB_MAX_LEN] = {"\0"}; char returnString[OMTB_MAX_LEN] = {"\0"};
  FILE *fpResult = NULL;
  MX_Result  result = ERR_NOERR;
  OMTB_CLIENT_PRIVATE* thisClient = NULL;
  char componentRequested[OMX_MAX_STRINGNAME_SIZE] = {"\0"};    
  OMTB_OMX_API_TIMING_VAR_DECL;

  /* Read component name */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, componentRequested);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }
    
  /* Read testcase ID */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, testCaseId);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }
  
  /* Read result filename */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, resultFileName);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }

  /* Read result file type */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, fOpenMode);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }
  
  /* Read instance Number */
  result = XdbgCmdNextNum(pContext, pCmdEntry, ppCmdLine, (UINT32 *)&instance);
  if (ERR_NOERR != result)
  {
    return result;
  }

  /* Open the result file */
  fpResult = fopen(resultFileName, fOpenMode);

  if(NULL == fpResult)
  {
    PRINT(PRINT_ERR_MSG, "%s: Error in result file open\n", __FUNCTION__);
    fprintf(fpResult, "%s : FAIL - Error in result file open\n", testCaseId);
    return ERR_INVNAME;
  }
  
    thisClient =  (OMTB_CLIENT_PRIVATE*)OMTB_GetCompPrivHandle(componentRequested, instance); 

  /* Set the component's OMX_PARAM_PORTDEFINITIONTYPE structure (input) */
  OMTB_SetHeader( thisClient->inPortParams->cmnInParams.pInPortDef,
                  sizeof(OMX_PARAM_PORTDEFINITIONTYPE));

  thisClient->inPortParams->cmnInParams.pInPortDef->nPortIndex = OMTB_H264_VDEC_INPUT_PORT_IDX;
  
  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;
  
  /*Set the inPort Definition*/
  err = OMX_GetParameter( thisClient->omtbPvt.handle,
                          OMX_IndexParamPortDefinition,
                          thisClient->inPortParams->cmnInParams.pInPortDef);
  
  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_GetParameter");

  if(OMX_ErrorNone != err)
  {
    OMTB_OmxReturnStatusString(err, returnString);
    strcpy(testCaseResult, "FAIL in OMX_GetParameter()");
    fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
    result = ERR_INVNAME;
  }

  /* Set the component's OMX_PARAM_PORTDEFINITIONTYPE structure (input) */
  OMTB_SetHeader( thisClient->inPortParams->cmnInParams.pInPortDef,
                  sizeof(OMX_PARAM_PORTDEFINITIONTYPE));

  thisClient->inPortParams->cmnInParams.pInPortDef->nPortIndex = OMTB_H264_VDEC_INPUT_PORT_IDX;
  
  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;
  
  /* Send the portInit parameter structure */
  err = OMX_SetParameter( thisClient->omtbPvt.handle,
                          OMX_IndexParamPortDefinition,
                          thisClient->inPortParams->cmnInParams.pInPortDef);
  
  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_SetParameter");
  
  if(OMX_ErrorUnsupportedSetting == err)
  {
    strcpy(testCaseResult, "PASS");
    fprintf(fpResult, "%s : %s\n", testCaseId, testCaseResult);
  }
  else
  {
    OMTB_OmxReturnStatusString(err, returnString);
    strcpy(testCaseResult, "FAIL");
    fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
    result = ERR_INVNAME;
  }

  fclose(fpResult);
  return result;
}


/******************************************************************************\
 *      OMTB_OmxSetParameterUnSupportedIndex Function Definition
\******************************************************************************/
/**
 *
 *  @brief    This Function performs OMX_SetParameter API testing.
 *
 *  @param    Pointer to MX_DBG_CMD_CONTEXT_T structure
 *            Pointer to MX_DBG_CMD_Entry_T structure
 *            Character Double Pointer containing the command
 *
 *  @return   ERR_NOERR           successful,
 *            ERR_END_OF_CMD      help was requested,
 *            ERR_INVNAME         otherwise.

 *
 */

MX_Result OMTB_OmxSetParameterUnSupportedIndex(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine)
{
  OMX_ERRORTYPE err = OMX_ErrorNone;
  unsigned int instance = 0;
  char resultFileName[OMTB_MAX_LEN] = {"\0"};
  char fOpenMode[OMTB_MAX_LEN] = {"\0"};
  char testCaseId[OMTB_MAX_LEN] = {"\0"};
  char testCaseResult[OMTB_MAX_LEN] = {"\0"}; char returnString[OMTB_MAX_LEN] = {"\0"};
  FILE *fpResult = NULL;
  MX_Result  result = ERR_NOERR;
  OMTB_CLIENT_PRIVATE* thisClient = NULL;
  char componentRequested[OMX_MAX_STRINGNAME_SIZE] = {"\0"};    
  OMTB_OMX_API_TIMING_VAR_DECL;

  /* Read component name */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, componentRequested);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }
    
  /* Read testcase ID */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, testCaseId);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }
  
  /* Read result filename */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, resultFileName);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }

  /* Read result file type */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, fOpenMode);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }
  
  /* Read instance Number */
  result = XdbgCmdNextNum(pContext, pCmdEntry, ppCmdLine, (UINT32 *)&instance);
  if (ERR_NOERR != result)
  {
    return result;
  }

  /* Open the result file */
  fpResult = fopen(resultFileName, fOpenMode);

  if(NULL == fpResult)
  {
    PRINT(PRINT_ERR_MSG, "%s: Error in result file open\n", __FUNCTION__);
    fprintf(fpResult, "%s : FAIL - Error in result file open\n", testCaseId);
    return ERR_INVNAME;
  }
  
    thisClient =  (OMTB_CLIENT_PRIVATE*)OMTB_GetCompPrivHandle(componentRequested, instance); 

  /* Set the component's OMX_PARAM_PORTDEFINITIONTYPE structure (input) */
  OMTB_SetHeader( thisClient->inPortParams->cmnInParams.pInPortDef,
                  sizeof(OMX_PARAM_PORTDEFINITIONTYPE));

  thisClient->inPortParams->cmnInParams.pInPortDef->nPortIndex = OMTB_H264_VDEC_INPUT_PORT_IDX;
  
  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;
  
  /*Set the inPort Definition*/
  err = OMX_GetParameter( thisClient->omtbPvt.handle,
                          OMX_IndexParamPortDefinition,
                          thisClient->inPortParams->cmnInParams.pInPortDef);
  
  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_GetParameter");

  if(OMX_ErrorNone != err)
  {
    OMTB_OmxReturnStatusString(err, returnString);
    strcpy(testCaseResult, "FAIL in OMX_GetParameter()");
    fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
    result = ERR_INVNAME;
  }

  /* Set the component's OMX_PARAM_PORTDEFINITIONTYPE structure (input) */
  OMTB_SetHeader( thisClient->inPortParams->cmnInParams.pInPortDef,
                  sizeof(OMX_PARAM_PORTDEFINITIONTYPE));

  thisClient->inPortParams->cmnInParams.pInPortDef->nPortIndex = OMTB_H264_VDEC_INPUT_PORT_IDX;
  
  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;
  
  /* Send the portInit parameter structure */
  err = OMX_SetParameter( thisClient->omtbPvt.handle,
                          OMX_IndexMax,
                          thisClient->inPortParams->cmnInParams.pInPortDef);
  
  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_SetParameter");
  
  if(OMX_ErrorUnsupportedIndex == err)
  {
    strcpy(testCaseResult, "PASS");
    fprintf(fpResult, "%s : %s\n", testCaseId, testCaseResult);
  }
  else
  {
    OMTB_OmxReturnStatusString(err, returnString);
    strcpy(testCaseResult, "FAIL");
    fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
    result = ERR_INVNAME;
  }

  fclose(fpResult);
  return result;
}


/******************************************************************************\
 *      OMTB_OmxSetParameterWrongPort Function Definition
\******************************************************************************/
/**
 *
 *  @brief    This Function performs OMX_SetParameter API testing.
 *
 *  @param    Pointer to MX_DBG_CMD_CONTEXT_T structure
 *            Pointer to MX_DBG_CMD_Entry_T structure
 *            Character Double Pointer containing the command
 *
 *  @return   ERR_NOERR           successful,
 *            ERR_END_OF_CMD      help was requested,
 *            ERR_INVNAME         otherwise.

 *
 */

MX_Result OMTB_OmxSetParameterWrongPort(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine)
{
  OMX_ERRORTYPE err = OMX_ErrorNone;
  unsigned int instance = 0;
  char resultFileName[OMTB_MAX_LEN] = {"\0"};
  char fOpenMode[OMTB_MAX_LEN] = {"\0"};
  char testCaseId[OMTB_MAX_LEN] = {"\0"};
  char testCaseResult[OMTB_MAX_LEN] = {"\0"}; char returnString[OMTB_MAX_LEN] = {"\0"};
  FILE *fpResult = NULL;
  MX_Result  result = ERR_NOERR;
  OMTB_CLIENT_PRIVATE* thisClient = NULL;
  char componentRequested[OMX_MAX_STRINGNAME_SIZE] = {"\0"};    
  OMTB_OMX_API_TIMING_VAR_DECL;

  /* Read component name */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, componentRequested);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }
  
  /* Read testcase ID */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, testCaseId);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }
  
  /* Read result filename */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, resultFileName);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }

  /* Read result file type */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, fOpenMode);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }
  
  /* Read instance Number */
  result = XdbgCmdNextNum(pContext, pCmdEntry, ppCmdLine, (UINT32 *)&instance);
  if (ERR_NOERR != result)
  {
    return result;
  }

  /* Open the result file */
  fpResult = fopen(resultFileName, fOpenMode);

  if(NULL == fpResult)
  {
    PRINT(PRINT_ERR_MSG, "%s: Error in result file open\n", __FUNCTION__);
    fprintf(fpResult, "%s : FAIL - Error in result file open\n", testCaseId);
    return ERR_INVNAME;
  }
  
    thisClient =  (OMTB_CLIENT_PRIVATE*)OMTB_GetCompPrivHandle(componentRequested, instance); 

  /* Set the component's OMX_PARAM_PORTDEFINITIONTYPE structure (input) */
  OMTB_SetHeader( thisClient->inPortParams->cmnInParams.pInPortDef,
                  sizeof(OMX_PARAM_PORTDEFINITIONTYPE));

  thisClient->inPortParams->cmnInParams.pInPortDef->nPortIndex = OMTB_H264_VDEC_INPUT_PORT_IDX;
  
  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;
  
  /*Set the inPort Definition*/
  err = OMX_GetParameter( thisClient->omtbPvt.handle,
                          OMX_IndexParamPortDefinition,
                          thisClient->inPortParams->cmnInParams.pInPortDef);
  
  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_GetParameter");

  if(OMX_ErrorNone != err)
  {
    OMTB_OmxReturnStatusString(err, returnString);
    strcpy(testCaseResult, "FAIL in OMX_GetParameter()");
    fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
    result = ERR_INVNAME;
  }

  /* Set the component's OMX_PARAM_PORTDEFINITIONTYPE structure (input) */
  OMTB_SetHeader( thisClient->inPortParams->cmnInParams.pInPortDef,
                  sizeof(OMX_PARAM_PORTDEFINITIONTYPE));
  
  thisClient->inPortParams->cmnInParams.pInPortDef->nPortIndex = OMTB_H264_VDEC_INVALID_PORT_IDX;
  
  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;
  
  /* Send the portInit parameter structure */
  err = OMX_SetParameter( thisClient->omtbPvt.handle,
                          OMX_IndexParamPortDefinition,
                          thisClient->inPortParams->cmnInParams.pInPortDef);
  
  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_SetParameter");
  
  if(OMX_ErrorBadPortIndex == err)
  {
    strcpy(testCaseResult, "PASS");
    fprintf(fpResult, "%s : %s\n", testCaseId, testCaseResult);
  }
  else
  {
    OMTB_OmxReturnStatusString(err, returnString);
    strcpy(testCaseResult, "FAIL");
    fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
    result = ERR_INVNAME;
  }

  fclose(fpResult);
  return result;
}


/******************************************************************************\
 *      OMTB_OmxSetParameterIdleState Function Definition
\******************************************************************************/
/**
 *
 *  @brief    This Function performs OMX_SetParameter API testing.
 *
 *  @param    Pointer to MX_DBG_CMD_CONTEXT_T structure
 *            Pointer to MX_DBG_CMD_Entry_T structure
 *            Character Double Pointer containing the command
 *
 *  @return   ERR_NOERR           successful,
 *            ERR_END_OF_CMD      help was requested,
 *            ERR_INVNAME         otherwise.

 *
 */

MX_Result OMTB_OmxSetParameterIdleState(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine)
{
  OMX_ERRORTYPE err = OMX_ErrorNone;
  unsigned int instance = 0;
  char resultFileName[OMTB_MAX_LEN] = {"\0"};
  char fOpenMode[OMTB_MAX_LEN] = {"\0"};
  char testCaseId[OMTB_MAX_LEN] = {"\0"};
  char testCaseResult[OMTB_MAX_LEN] = {"\0"}; char returnString[OMTB_MAX_LEN] = {"\0"};
  FILE *fpResult = NULL;
  MX_Result  result = ERR_NOERR;
  OMTB_CLIENT_PRIVATE* thisClient = NULL;
  char componentRequested[OMX_MAX_STRINGNAME_SIZE] = {"\0"};    
  OMTB_OMX_API_TIMING_VAR_DECL;

  /* Read component name */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, componentRequested);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }
    
  /* Read testcase ID */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, testCaseId);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }
  
  /* Read result filename */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, resultFileName);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }

  /* Read result file type */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, fOpenMode);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }
  
  /* Read instance Number */
  result = XdbgCmdNextNum(pContext, pCmdEntry, ppCmdLine, (UINT32 *)&instance);
  if (ERR_NOERR != result)
  {
    return result;
  }

  /* Open the result file */
  fpResult = fopen(resultFileName, fOpenMode);

  if(NULL == fpResult)
  {
    PRINT(PRINT_ERR_MSG, "%s: Error in result file open\n", __FUNCTION__);
    fprintf(fpResult, "%s : FAIL - Error in result file open\n", testCaseId);
    return ERR_INVNAME;
  }
  
  thisClient =  (OMTB_CLIENT_PRIVATE*)OMTB_GetCompPrivHandle(componentRequested, instance); 

  thisClient->inPortParams->cmnInParams.pInPortDef->nPortIndex          = OMTB_H264_VDEC_INPUT_PORT_IDX;
  thisClient->inPortParams->cmnInParams.pInPortDef->eDir                = OMX_DirInput;
  thisClient->inPortParams->cmnInParams.pInPortDef->nBufferCountActual  = 
                                  thisClient->inPortParams->cmnInParams.numInBuf;
  thisClient->inPortParams->cmnInParams.pInPortDef->nBufferCountMin     = 1;
  thisClient->inPortParams->cmnInParams.pInPortDef->nBufferSize         = 
                                  thisClient->inPortParams->cmnInParams.bufferInSize;
  thisClient->inPortParams->cmnInParams.pInPortDef->bEnabled            = OMX_TRUE;
  thisClient->inPortParams->cmnInParams.pInPortDef->bPopulated          = OMX_FALSE;
  thisClient->inPortParams->cmnInParams.pInPortDef->eDomain             = 
                                  OMX_PortDomainVideo;
  thisClient->inPortParams->cmnInParams.pInPortDef->bBuffersContiguous  = OMX_FALSE;
  thisClient->inPortParams->cmnInParams.pInPortDef->nBufferAlignment    = 0x0;
  
  /* OMX_VIDEO_PORTDEFINITION values for input port */
  thisClient->inPortParams->cmnInParams.pInPortDef->format.video.pNativeRender  = NULL;
  thisClient->inPortParams->cmnInParams.pInPortDef->format.video.cMIMEType      = "H264";
  thisClient->inPortParams->cmnInParams.pInPortDef->format.video.nStride        = -1;
  thisClient->inPortParams->cmnInParams.pInPortDef->format.video.nSliceHeight   = 0;
  thisClient->inPortParams->cmnInParams.pInPortDef->format.video.nBitrate       = 0;
  thisClient->inPortParams->cmnInParams.pInPortDef->format.video.xFramerate     = 0;
  thisClient->inPortParams->cmnInParams.pInPortDef->format.video.eColorFormat   =
                      thisClient->outPortParams->colorFormat;
  thisClient->inPortParams->cmnInParams.pInPortDef->format.video.nFrameWidth    = 
                      thisClient->outPortParams->nWidth;
  thisClient->inPortParams->cmnInParams.pInPortDef->format.video.nFrameHeight   = 
                      thisClient->outPortParams->nHeight;
  thisClient->inPortParams->cmnInParams.pInPortDef->format.video.eCompressionFormat = 
                      OMX_VIDEO_CodingAVC;
  thisClient->inPortParams->cmnInParams.pInPortDef->format.video.bFlagErrorConcealment = 
                      OMX_FALSE;

  /* Set the component's OMX_PARAM_PORTDEFINITIONTYPE structure (input) */
  OMTB_SetHeader( thisClient->inPortParams->cmnInParams.pInPortDef,
                  sizeof(OMX_PARAM_PORTDEFINITIONTYPE));
  
  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;
  
  /* Send the portInit parameter structure */
  err = OMX_SetParameter( thisClient->omtbPvt.handle,
                          OMX_IndexParamPortDefinition,
                          thisClient->inPortParams->cmnInParams.pInPortDef);
  
  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_SetParameter");
  
  if(OMX_ErrorIncorrectStateOperation == err)
  {
    strcpy(testCaseResult, "PASS");
    fprintf(fpResult, "%s : %s\n", testCaseId, testCaseResult);
  }
  else
  {
    OMTB_OmxReturnStatusString(err, returnString);
    strcpy(testCaseResult, "FAIL");
    fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
    result = ERR_INVNAME;
  }

  fclose(fpResult);
  return result;
}


/******************************************************************************\
 *      OMTB_OmxSetConfigOnce Function Definition
\******************************************************************************/
/**
 *
 *  @brief    This Function performs OMX_SetConfig API testing.
 *
 *  @param    Pointer to MX_DBG_CMD_CONTEXT_T structure
 *            Pointer to MX_DBG_CMD_Entry_T structure
 *            Character Double Pointer containing the command
 *
 *  @return   ERR_NOERR           successful,
 *            ERR_END_OF_CMD      help was requested,
 *            ERR_INVNAME         otherwise.

 *
 */

MX_Result OMTB_OmxSetConfigOnce(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine)
{
  OMX_ERRORTYPE err = OMX_ErrorNone;
  unsigned int instance = 0;
  char resultFileName[OMTB_MAX_LEN] = {"\0"};
  char fOpenMode[OMTB_MAX_LEN] = {"\0"};
  char testCaseId[OMTB_MAX_LEN] = {"\0"};
  char testCaseResult[OMTB_MAX_LEN] = {"\0"}; char returnString[OMTB_MAX_LEN] = {"\0"};
  FILE *fpResult = NULL;
  MX_Result  result = ERR_NOERR;
  OMTB_CLIENT_PRIVATE* thisClient = NULL;
  char componentRequested[OMX_MAX_STRINGNAME_SIZE] = {"\0"};    
  OMTB_OMX_API_TIMING_VAR_DECL;

  /* Read component name */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, componentRequested);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }
  
  /* Read testcase ID */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, testCaseId);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }
  
  /* Read result filename */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, resultFileName);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }

  /* Read result file type */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, fOpenMode);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }
  
  /* Read instance Number */
  result = XdbgCmdNextNum(pContext, pCmdEntry, ppCmdLine, (UINT32 *)&instance);
  if (ERR_NOERR != result)
  {
    return result;
  }

  /* Open the result file */
  fpResult = fopen(resultFileName, fOpenMode);

  if(NULL == fpResult)
  {
    PRINT(PRINT_ERR_MSG, "%s: Error in result file open\n", __FUNCTION__);
    fprintf(fpResult, "%s : FAIL - Error in result file open\n", testCaseId);
    return ERR_INVNAME;
  }
  
  thisClient =  (OMTB_CLIENT_PRIVATE*)OMTB_GetCompPrivHandle(componentRequested, instance);

  /* Set the component's OMX_PARAM_PORTDEFINITIONTYPE structure (input) */
  OMTB_SetHeader( thisClient->inPortParams->cmnInParams.pInPortDef,
                  sizeof(OMX_PARAM_PORTDEFINITIONTYPE));

  thisClient->inPortParams->cmnInParams.pInPortDef->nPortIndex = OMTB_H264_VDEC_INPUT_PORT_IDX;
  
  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;
  
  /*Set the inPort Definition*/
  err = OMX_GetConfig( thisClient->omtbPvt.handle,
                          OMX_IndexParamPortDefinition,
                          thisClient->inPortParams->cmnInParams.pInPortDef);
  
  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_GetConfig");

  if(OMX_ErrorNone != err)
  {
    OMTB_OmxReturnStatusString(err, returnString);
    strcpy(testCaseResult, "FAIL in OMX_GetConfig()");
    fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
    result = ERR_INVNAME;
  }

  /* Set the component's OMX_PARAM_PORTDEFINITIONTYPE structure (input) */
  OMTB_SetHeader( thisClient->inPortParams->cmnInParams.pInPortDef,
                  sizeof(OMX_PARAM_PORTDEFINITIONTYPE));

  thisClient->inPortParams->cmnInParams.pInPortDef->nPortIndex = OMTB_H264_VDEC_INPUT_PORT_IDX;
  
  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;
  
  /* Send the portInit parameter structure */
  err = OMX_SetConfig( thisClient->omtbPvt.handle,
                          OMX_IndexParamPortDefinition,
                          thisClient->inPortParams->cmnInParams.pInPortDef);
  
  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_SetConfig");
  
  if(OMX_ErrorNone == err)
  {
    strcpy(testCaseResult, "PASS");
    fprintf(fpResult, "%s : %s\n", testCaseId, testCaseResult);
  }
  else
  {
    OMTB_OmxReturnStatusString(err, returnString);
    strcpy(testCaseResult, "FAIL");
    fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
    result = ERR_INVNAME;
  }

  fclose(fpResult);
  return result;
}


/******************************************************************************\
 *      OMTB_OmxSetConfigNullCfgStruct Function Definition
\******************************************************************************/
/**
 *
 *  @brief    This Function performs OMX_SetConfig API testing.
 *
 *  @param    Pointer to MX_DBG_CMD_CONTEXT_T structure
 *            Pointer to MX_DBG_CMD_Entry_T structure
 *            Character Double Pointer containing the command
 *
 *  @return   ERR_NOERR           successful,
 *            ERR_END_OF_CMD      help was requested,
 *            ERR_INVNAME         otherwise.

 *
 */

MX_Result OMTB_OmxSetConfigNullCfgStruct(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine)
{
  OMX_ERRORTYPE err = OMX_ErrorNone;
  unsigned int instance = 0;
  char resultFileName[OMTB_MAX_LEN] = {"\0"};
  char fOpenMode[OMTB_MAX_LEN] = {"\0"};
  char testCaseId[OMTB_MAX_LEN] = {"\0"};
  char testCaseResult[OMTB_MAX_LEN] = {"\0"}; char returnString[OMTB_MAX_LEN] = {"\0"};
  FILE *fpResult = NULL;
  MX_Result  result = ERR_NOERR;
  OMTB_CLIENT_PRIVATE* thisClient = NULL;
  char componentRequested[OMX_MAX_STRINGNAME_SIZE] = {"\0"};    
  OMTB_OMX_API_TIMING_VAR_DECL;

  /* Read component name */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, componentRequested);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }
  
  /* Read testcase ID */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, testCaseId);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }
  
  /* Read result filename */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, resultFileName);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }

  /* Read result file type */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, fOpenMode);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }
  
  /* Read instance Number */
  result = XdbgCmdNextNum(pContext, pCmdEntry, ppCmdLine, (UINT32 *)&instance);
  if (ERR_NOERR != result)
  {
    return result;
  }

  /* Open the result file */
  fpResult = fopen(resultFileName, fOpenMode);

  if(NULL == fpResult)
  {
    PRINT(PRINT_ERR_MSG, "%s: Error in result file open\n", __FUNCTION__);
    fprintf(fpResult, "%s : FAIL - Error in result file open\n", testCaseId);
    return ERR_INVNAME;
  }
  
  thisClient =  (OMTB_CLIENT_PRIVATE*)OMTB_GetCompPrivHandle(componentRequested, instance);

  /* Set the component's OMX_PARAM_PORTDEFINITIONTYPE structure (input) */
  OMTB_SetHeader( thisClient->inPortParams->cmnInParams.pInPortDef,
                  sizeof(OMX_PARAM_PORTDEFINITIONTYPE));

  thisClient->inPortParams->cmnInParams.pInPortDef->nPortIndex = OMTB_H264_VDEC_INPUT_PORT_IDX;
  
  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;
  
  /*Set the inPort Definition*/
  err = OMX_GetConfig( thisClient->omtbPvt.handle,
                          OMX_IndexParamPortDefinition,
                          thisClient->inPortParams->cmnInParams.pInPortDef);
  
  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_GetConfig");

  if(OMX_ErrorNone != err)
  {
    OMTB_OmxReturnStatusString(err, returnString);
    strcpy(testCaseResult, "FAIL in OMX_GetConfig()");
    fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
    result = ERR_INVNAME;
  }

  /* Set the component's OMX_PARAM_PORTDEFINITIONTYPE structure (input) */
  OMTB_SetHeader( thisClient->inPortParams->cmnInParams.pInPortDef,
                  sizeof(OMX_PARAM_PORTDEFINITIONTYPE));

  thisClient->inPortParams->cmnInParams.pInPortDef->nPortIndex = OMTB_H264_VDEC_INPUT_PORT_IDX;
  
  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;
  
  /* Send the portInit parameter structure */
  err = OMX_SetConfig( thisClient->omtbPvt.handle,
                          OMX_IndexParamPortDefinition,
                          NULL);
  
  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_SetConfig");
  
  if(OMX_ErrorBadParameter == err)
  {
    strcpy(testCaseResult, "PASS");
    fprintf(fpResult, "%s : %s\n", testCaseId, testCaseResult);
  }
  else
  {
    OMTB_OmxReturnStatusString(err, returnString);
    strcpy(testCaseResult, "FAIL");
    fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
    result = ERR_INVNAME;
  }

  fclose(fpResult);
  return result;
}


/******************************************************************************\
 *      OMTB_OmxSetConfigOnce Function Definition
\******************************************************************************/
/**
 *
 *  @brief    This Function performs OMX_SetConfig API testing.
 *
 *  @param    Pointer to MX_DBG_CMD_CONTEXT_T structure
 *            Pointer to MX_DBG_CMD_Entry_T structure
 *            Character Double Pointer containing the command
 *
 *  @return   ERR_NOERR           successful,
 *            ERR_END_OF_CMD      help was requested,
 *            ERR_INVNAME         otherwise.

 *
 */

MX_Result OMTB_OmxSetConfigNullHandle(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine)
{
  OMX_ERRORTYPE err = OMX_ErrorNone;
  unsigned int instance = 0;
  char resultFileName[OMTB_MAX_LEN] = {"\0"};
  char fOpenMode[OMTB_MAX_LEN] = {"\0"};
  char testCaseId[OMTB_MAX_LEN] = {"\0"};
  char testCaseResult[OMTB_MAX_LEN] = {"\0"}; char returnString[OMTB_MAX_LEN] = {"\0"};
  FILE *fpResult = NULL;
  MX_Result  result = ERR_NOERR;
  OMTB_CLIENT_PRIVATE* thisClient = NULL;
  char componentRequested[OMX_MAX_STRINGNAME_SIZE] = {"\0"};  
  OMTB_OMX_API_TIMING_VAR_DECL;

  /* Read component name */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, componentRequested);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }
  
  /* Read testcase ID */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, testCaseId);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }
  
  /* Read result filename */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, resultFileName);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }

  /* Read result file type */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, fOpenMode);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }
  
  /* Read instance Number */
  result = XdbgCmdNextNum(pContext, pCmdEntry, ppCmdLine, (UINT32 *)&instance);
  if (ERR_NOERR != result)
  {
    return result;
  }

  /* Open the result file */
  fpResult = fopen(resultFileName, fOpenMode);

  if(NULL == fpResult)
  {
    PRINT(PRINT_ERR_MSG, "%s: Error in result file open\n", __FUNCTION__);
    fprintf(fpResult, "%s : FAIL - Error in result file open\n", testCaseId);
    return ERR_INVNAME;
  }
  
  thisClient =  (OMTB_CLIENT_PRIVATE*)OMTB_GetCompPrivHandle(componentRequested, instance);

  /* Set the component's OMX_PARAM_PORTDEFINITIONTYPE structure (input) */
  OMTB_SetHeader( thisClient->inPortParams->cmnInParams.pInPortDef,
                  sizeof(OMX_PARAM_PORTDEFINITIONTYPE));

  thisClient->inPortParams->cmnInParams.pInPortDef->nPortIndex = OMTB_H264_VDEC_INPUT_PORT_IDX;
  
  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;
  
  /*Set the inPort Definition*/
  err = OMX_GetConfig( thisClient->omtbPvt.handle,
                          OMX_IndexParamPortDefinition,
                          thisClient->inPortParams->cmnInParams.pInPortDef);
  
  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_GetConfig");

  if(OMX_ErrorNone != err)
  {
    OMTB_OmxReturnStatusString(err, returnString);
    strcpy(testCaseResult, "FAIL in OMX_GetConfig()");
    fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
    result = ERR_INVNAME;
  }

  /* Set the component's OMX_PARAM_PORTDEFINITIONTYPE structure (input) */
  OMTB_SetHeader( thisClient->inPortParams->cmnInParams.pInPortDef,
                  sizeof(OMX_PARAM_PORTDEFINITIONTYPE));

  thisClient->inPortParams->cmnInParams.pInPortDef->nPortIndex = OMTB_H264_VDEC_INPUT_PORT_IDX;
  
  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;
  
  /* Send the portInit parameter structure */
  err = OMX_SetConfig( NULL,
                          OMX_IndexParamPortDefinition,
                          thisClient->inPortParams->cmnInParams.pInPortDef);
  
  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_SetConfig");
  
  if(OMX_ErrorBadParameter == err)
  {
    strcpy(testCaseResult, "PASS");
    fprintf(fpResult, "%s : %s\n", testCaseId, testCaseResult);
  }
  else
  {
    OMTB_OmxReturnStatusString(err, returnString);
    strcpy(testCaseResult, "FAIL");
    fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
    result = ERR_INVNAME;
  }

  fclose(fpResult);
  return result;
}


/******************************************************************************\
 *      OMTB_OmxSetConfigVerMismatch Function Definition
\******************************************************************************/
/**
 *
 *  @brief    This Function performs OMX_SetConfig API testing.
 *
 *  @param    Pointer to MX_DBG_CMD_CONTEXT_T structure
 *            Pointer to MX_DBG_CMD_Entry_T structure
 *            Character Double Pointer containing the command
 *
 *  @return   ERR_NOERR           successful,
 *            ERR_END_OF_CMD      help was requested,
 *            ERR_INVNAME         otherwise.

 *
 */

MX_Result OMTB_OmxSetConfigVerMismatch(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine)
{
  OMX_ERRORTYPE err = OMX_ErrorNone;
  unsigned int instance = 0;
  char resultFileName[OMTB_MAX_LEN] = {"\0"};
  char fOpenMode[OMTB_MAX_LEN] = {"\0"};
  char testCaseId[OMTB_MAX_LEN] = {"\0"};
  char testCaseResult[OMTB_MAX_LEN] = {"\0"}; char returnString[OMTB_MAX_LEN] = {"\0"};
  FILE *fpResult = NULL;
  MX_Result  result = ERR_NOERR;
  OMTB_CLIENT_PRIVATE* thisClient = NULL;
  char componentRequested[OMX_MAX_STRINGNAME_SIZE] = {"\0"};    
  OMTB_OMX_API_TIMING_VAR_DECL;
  
  /* Read component name */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, componentRequested);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }
  
  /* Read testcase ID */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, testCaseId);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }
  
  /* Read result filename */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, resultFileName);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }

  /* Read result file type */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, fOpenMode);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }
  
  /* Read instance Number */
  result = XdbgCmdNextNum(pContext, pCmdEntry, ppCmdLine, (UINT32 *)&instance);
  if (ERR_NOERR != result)
  {
    return result;
  }

  /* Open the result file */
  fpResult = fopen(resultFileName, fOpenMode);

  if(NULL == fpResult)
  {
    PRINT(PRINT_ERR_MSG, "%s: Error in result file open\n", __FUNCTION__);
    fprintf(fpResult, "%s : FAIL - Error in result file open\n", testCaseId);
    return ERR_INVNAME;
  }
  
  thisClient =  (OMTB_CLIENT_PRIVATE*)OMTB_GetCompPrivHandle(componentRequested, instance);

  /* Set the component's OMX_PARAM_PORTDEFINITIONTYPE structure (input) */
  OMTB_SetHeader( thisClient->inPortParams->cmnInParams.pInPortDef,
                  sizeof(OMX_PARAM_PORTDEFINITIONTYPE));

  thisClient->inPortParams->cmnInParams.pInPortDef->nPortIndex = OMTB_H264_VDEC_INPUT_PORT_IDX;
  
  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;
  
  /*Set the inPort Definition*/
  err = OMX_GetConfig( thisClient->omtbPvt.handle,
                          OMX_IndexParamPortDefinition,
                          thisClient->inPortParams->cmnInParams.pInPortDef);
  
  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_GetConfig");

  if(OMX_ErrorNone != err)
  {
    OMTB_OmxReturnStatusString(err, returnString);
    strcpy(testCaseResult, "FAIL in OMX_GetConfig()");
    fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
    result = ERR_INVNAME;
  }

  /* set incorrect version numbers */
  thisClient->inPortParams->cmnInParams.pInPortDef->nSize = sizeof(OMX_PARAM_PORTDEFINITIONTYPE);
  thisClient->inPortParams->cmnInParams.pInPortDef->nVersion.s.nVersionMajor = 1;
  thisClient->inPortParams->cmnInParams.pInPortDef->nVersion.s.nVersionMinor = 2;
  thisClient->inPortParams->cmnInParams.pInPortDef->nVersion.s.nRevision = 0;
  thisClient->inPortParams->cmnInParams.pInPortDef->nVersion.s.nRevision = 0;

  thisClient->inPortParams->cmnInParams.pInPortDef->nPortIndex = OMTB_H264_VDEC_INPUT_PORT_IDX;
  
  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;
  
  /* Send the portInit parameter structure */
  err = OMX_SetConfig( thisClient->omtbPvt.handle,
                          OMX_IndexParamPortDefinition,
                          thisClient->inPortParams->cmnInParams.pInPortDef);
  
  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_SetConfig");
  
  if(OMX_ErrorVersionMismatch == err)
  {
    strcpy(testCaseResult, "PASS");
    fprintf(fpResult, "%s : %s\n", testCaseId, testCaseResult);
  }
  else
  {
    OMTB_OmxReturnStatusString(err, returnString);
    strcpy(testCaseResult, "FAIL");
    fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
    result = ERR_INVNAME;
  }

  fclose(fpResult);
  return result;
}


/******************************************************************************\
 *      OMTB_OmxSetConfigTimeOut Function Definition
\******************************************************************************/
/**
 *
 *  @brief    This Function performs OMX_SetConfig API testing.
 *
 *  @param    Pointer to MX_DBG_CMD_CONTEXT_T structure
 *            Pointer to MX_DBG_CMD_Entry_T structure
 *            Character Double Pointer containing the command
 *
 *  @return   ERR_NOERR           successful,
 *            ERR_END_OF_CMD      help was requested,
 *            ERR_INVNAME         otherwise.

 *
 */

MX_Result OMTB_OmxSetConfigTimeOut(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine)
{
  OMX_ERRORTYPE err = OMX_ErrorNone;
  unsigned int instance = 0;
  char resultFileName[OMTB_MAX_LEN] = {"\0"};
  char fOpenMode[OMTB_MAX_LEN] = {"\0"};
  char testCaseId[OMTB_MAX_LEN] = {"\0"};
  char testCaseResult[OMTB_MAX_LEN] = {"\0"}; char returnString[OMTB_MAX_LEN] = {"\0"};
  FILE *fpResult = NULL;
  MX_Result  result = ERR_NOERR;
  OMTB_CLIENT_PRIVATE* thisClient = NULL;
  char componentRequested[OMX_MAX_STRINGNAME_SIZE] = {"\0"};    
  OMTB_OMX_API_TIMING_VAR_DECL;

  /* Read component name */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, componentRequested);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }
  
  /* Read testcase ID */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, testCaseId);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }
  
  /* Read result filename */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, resultFileName);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }

  /* Read result file type */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, fOpenMode);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }
  
  /* Read instance Number */
  result = XdbgCmdNextNum(pContext, pCmdEntry, ppCmdLine, (UINT32 *)&instance);
  if (ERR_NOERR != result)
  {
    return result;
  }

  /* Open the result file */
  fpResult = fopen(resultFileName, fOpenMode);

  if(NULL == fpResult)
  {
    PRINT(PRINT_ERR_MSG, "%s: Error in result file open\n", __FUNCTION__);
    fprintf(fpResult, "%s : FAIL - Error in result file open\n", testCaseId);
    return ERR_INVNAME;
  }
  
  thisClient =  (OMTB_CLIENT_PRIVATE*)OMTB_GetCompPrivHandle(componentRequested, instance);

  /* Set the component's OMX_PARAM_PORTDEFINITIONTYPE structure (input) */
  OMTB_SetHeader( thisClient->inPortParams->cmnInParams.pInPortDef,
                  sizeof(OMX_PARAM_PORTDEFINITIONTYPE));

  thisClient->inPortParams->cmnInParams.pInPortDef->nPortIndex = OMTB_H264_VDEC_INPUT_PORT_IDX;
  
  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;
  
  /*Set the inPort Definition*/
  err = OMX_GetConfig( thisClient->omtbPvt.handle,
                          OMX_IndexParamPortDefinition,
                          thisClient->inPortParams->cmnInParams.pInPortDef);
  
  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_GetConfig");

  if(OMX_ErrorNone != err)
  {
    OMTB_OmxReturnStatusString(err, returnString);
    strcpy(testCaseResult, "FAIL in OMX_GetConfig()");
    fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
    result = ERR_INVNAME;
  }

  /* Set the component's OMX_PARAM_PORTDEFINITIONTYPE structure (input) */
  OMTB_SetHeader( thisClient->inPortParams->cmnInParams.pInPortDef,
                  sizeof(OMX_PARAM_PORTDEFINITIONTYPE));

  thisClient->inPortParams->cmnInParams.pInPortDef->nPortIndex = OMTB_H264_VDEC_INPUT_PORT_IDX;
  
  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;
  
  /* Send the portInit parameter structure */
  err = OMX_SetConfig( thisClient->omtbPvt.handle,
                          OMX_IndexParamPortDefinition,
                          thisClient->inPortParams->cmnInParams.pInPortDef);
  
  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_SetConfig");
  
  if(OMX_ErrorTimeout == err)
  {
    strcpy(testCaseResult, "PASS");
    fprintf(fpResult, "%s : %s\n", testCaseId, testCaseResult);
  }
  else
  {
    OMTB_OmxReturnStatusString(err, returnString);
    strcpy(testCaseResult, "FAIL");
    fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
    result = ERR_INVNAME;
  }

  fclose(fpResult);
  return result;
}

/******************************************************************************\
 *      OMTB_OmxSetConfigUnSupportedSettings Function Definition
\******************************************************************************/
/**
 *
 *  @brief    This Function performs OMX_SetConfig API testing.
 *
 *  @param    Pointer to MX_DBG_CMD_CONTEXT_T structure
 *            Pointer to MX_DBG_CMD_Entry_T structure
 *            Character Double Pointer containing the command
 *
 *  @return   ERR_NOERR           successful,
 *            ERR_END_OF_CMD      help was requested,
 *            ERR_INVNAME         otherwise.

 *
 */

MX_Result OMTB_OmxSetConfigUnSupportedSettings(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine)
{
  OMX_ERRORTYPE err = OMX_ErrorNone;
  unsigned int instance = 0;
  char resultFileName[OMTB_MAX_LEN] = {"\0"};
  char fOpenMode[OMTB_MAX_LEN] = {"\0"};
  char testCaseId[OMTB_MAX_LEN] = {"\0"};
  char testCaseResult[OMTB_MAX_LEN] = {"\0"}; char returnString[OMTB_MAX_LEN] = {"\0"};
  FILE *fpResult = NULL;
  MX_Result  result = ERR_NOERR;
  OMTB_CLIENT_PRIVATE* thisClient = NULL;
  char componentRequested[OMX_MAX_STRINGNAME_SIZE] = {"\0"};    
  OMTB_OMX_API_TIMING_VAR_DECL;

  /* Read component name */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, componentRequested);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }
  
  /* Read testcase ID */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, testCaseId);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }
  
  /* Read result filename */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, resultFileName);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }

  /* Read result file type */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, fOpenMode);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }
  
  /* Read instance Number */
  result = XdbgCmdNextNum(pContext, pCmdEntry, ppCmdLine, (UINT32 *)&instance);
  if (ERR_NOERR != result)
  {
    return result;
  }

  /* Open the result file */
  fpResult = fopen(resultFileName, fOpenMode);

  if(NULL == fpResult)
  {
    PRINT(PRINT_ERR_MSG, "%s: Error in result file open\n", __FUNCTION__);
    fprintf(fpResult, "%s : FAIL - Error in result file open\n", testCaseId);
    return ERR_INVNAME;
  }
  
  thisClient =  (OMTB_CLIENT_PRIVATE*)OMTB_GetCompPrivHandle(componentRequested, instance);

  /* Set the component's OMX_PARAM_PORTDEFINITIONTYPE structure (input) */
  OMTB_SetHeader( thisClient->inPortParams->cmnInParams.pInPortDef,
                  sizeof(OMX_PARAM_PORTDEFINITIONTYPE));

  thisClient->inPortParams->cmnInParams.pInPortDef->nPortIndex = OMTB_H264_VDEC_INPUT_PORT_IDX;
  
  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;
  
  /*Set the inPort Definition*/
  err = OMX_GetConfig( thisClient->omtbPvt.handle,
                          OMX_IndexParamPortDefinition,
                          thisClient->inPortParams->cmnInParams.pInPortDef);
  
  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_GetConfig");

  if(OMX_ErrorNone != err)
  {
    OMTB_OmxReturnStatusString(err, returnString);
    strcpy(testCaseResult, "FAIL in OMX_GetConfig()");
    fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
    result = ERR_INVNAME;
  }

  /* Set the component's OMX_PARAM_PORTDEFINITIONTYPE structure (input) */
  OMTB_SetHeader( thisClient->inPortParams->cmnInParams.pInPortDef,
                  sizeof(OMX_PARAM_PORTDEFINITIONTYPE));

  thisClient->inPortParams->cmnInParams.pInPortDef->nPortIndex = OMTB_H264_VDEC_INPUT_PORT_IDX;
  
  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;
  
  /* Send the portInit parameter structure */
  err = OMX_SetConfig( thisClient->omtbPvt.handle,
                          OMX_IndexParamPortDefinition,
                          thisClient->inPortParams->cmnInParams.pInPortDef);
  
  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_SetConfig");
  
  if(OMX_ErrorUnsupportedSetting == err)
  {
    strcpy(testCaseResult, "PASS");
    fprintf(fpResult, "%s : %s\n", testCaseId, testCaseResult);
  }
  else
  {
    OMTB_OmxReturnStatusString(err, returnString);
    strcpy(testCaseResult, "FAIL");
    fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
    result = ERR_INVNAME;
  }

  fclose(fpResult);
  return result;
}


/******************************************************************************\
 *      OMTB_OmxSetConfigUnSupportedIndex Function Definition
\******************************************************************************/
/**
 *
 *  @brief    This Function performs OMX_SetConfig API testing.
 *
 *  @param    Pointer to MX_DBG_CMD_CONTEXT_T structure
 *            Pointer to MX_DBG_CMD_Entry_T structure
 *            Character Double Pointer containing the command
 *
 *  @return   ERR_NOERR           successful,
 *            ERR_END_OF_CMD      help was requested,
 *            ERR_INVNAME         otherwise.

 *
 */

MX_Result OMTB_OmxSetConfigUnSupportedIndex(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine)
{
  OMX_ERRORTYPE err = OMX_ErrorNone;
  unsigned int instance = 0;
  char resultFileName[OMTB_MAX_LEN] = {"\0"};
  char fOpenMode[OMTB_MAX_LEN] = {"\0"};
  char testCaseId[OMTB_MAX_LEN] = {"\0"};
  char testCaseResult[OMTB_MAX_LEN] = {"\0"}; char returnString[OMTB_MAX_LEN] = {"\0"};
  FILE *fpResult = NULL;
  MX_Result  result = ERR_NOERR;
  OMTB_CLIENT_PRIVATE* thisClient = NULL;
  char componentRequested[OMX_MAX_STRINGNAME_SIZE] = {"\0"};    
  OMTB_OMX_API_TIMING_VAR_DECL;

  
  /* Read component name */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, componentRequested);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }
  
  /* Read testcase ID */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, testCaseId);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }
  
  /* Read result filename */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, resultFileName);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }

  /* Read result file type */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, fOpenMode);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }
  
  /* Read instance Number */
  result = XdbgCmdNextNum(pContext, pCmdEntry, ppCmdLine, (UINT32 *)&instance);
  if (ERR_NOERR != result)
  {
    return result;
  }

  /* Open the result file */
  fpResult = fopen(resultFileName, fOpenMode);

  if(NULL == fpResult)
  {
    PRINT(PRINT_ERR_MSG, "%s: Error in result file open\n", __FUNCTION__);
    fprintf(fpResult, "%s : FAIL - Error in result file open\n", testCaseId);
    return ERR_INVNAME;
  }
  
  thisClient =  (OMTB_CLIENT_PRIVATE*)OMTB_GetCompPrivHandle(componentRequested, instance);

  /* Set the component's OMX_PARAM_PORTDEFINITIONTYPE structure (input) */
  OMTB_SetHeader( thisClient->inPortParams->cmnInParams.pInPortDef,
                  sizeof(OMX_PARAM_PORTDEFINITIONTYPE));

  thisClient->inPortParams->cmnInParams.pInPortDef->nPortIndex = OMTB_H264_VDEC_INPUT_PORT_IDX;
  
  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;
  
  /*Set the inPort Definition*/
  err = OMX_GetConfig( thisClient->omtbPvt.handle,
                          OMX_IndexParamPortDefinition,
                          thisClient->inPortParams->cmnInParams.pInPortDef);
  
  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_GetConfig");

  if(OMX_ErrorNone != err)
  {
    OMTB_OmxReturnStatusString(err, returnString);
    strcpy(testCaseResult, "FAIL in OMX_GetConfig()");
    fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
    result = ERR_INVNAME;
  }

  /* Set the component's OMX_PARAM_PORTDEFINITIONTYPE structure (input) */
  OMTB_SetHeader( thisClient->inPortParams->cmnInParams.pInPortDef,
                  sizeof(OMX_PARAM_PORTDEFINITIONTYPE));

  thisClient->inPortParams->cmnInParams.pInPortDef->nPortIndex = OMTB_H264_VDEC_INPUT_PORT_IDX;
  
  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;
  
  /* Send the portInit parameter structure */
  err = OMX_SetConfig( thisClient->omtbPvt.handle,
                          OMX_IndexMax,
                          thisClient->inPortParams->cmnInParams.pInPortDef);
  
  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_SetConfig");
  
  if(OMX_ErrorUnsupportedIndex == err)
  {
    strcpy(testCaseResult, "PASS");
    fprintf(fpResult, "%s : %s\n", testCaseId, testCaseResult);
  }
  else
  {
    OMTB_OmxReturnStatusString(err, returnString);
    strcpy(testCaseResult, "FAIL");
    fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
    result = ERR_INVNAME;
  }

  fclose(fpResult);
  return result;
}


/******************************************************************************\
 *      OMTB_OmxSetConfigWrongPort Function Definition
\******************************************************************************/
/**
 *
 *  @brief    This Function performs OMX_SetConfig API testing.
 *
 *  @param    Pointer to MX_DBG_CMD_CONTEXT_T structure
 *            Pointer to MX_DBG_CMD_Entry_T structure
 *            Character Double Pointer containing the command
 *
 *  @return   ERR_NOERR           successful,
 *            ERR_END_OF_CMD      help was requested,
 *            ERR_INVNAME         otherwise.

 *
 */

MX_Result OMTB_OmxSetConfigWrongPort(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine)
{
  OMX_ERRORTYPE err = OMX_ErrorNone;
  unsigned int instance = 0;
  char resultFileName[OMTB_MAX_LEN] = {"\0"};
  char fOpenMode[OMTB_MAX_LEN] = {"\0"};
  char testCaseId[OMTB_MAX_LEN] = {"\0"};
  char testCaseResult[OMTB_MAX_LEN] = {"\0"}; char returnString[OMTB_MAX_LEN] = {"\0"};
  FILE *fpResult = NULL;
  MX_Result  result = ERR_NOERR;
  OMTB_CLIENT_PRIVATE* thisClient = NULL;
  char componentRequested[OMX_MAX_STRINGNAME_SIZE] = {"\0"};    
  OMTB_OMX_API_TIMING_VAR_DECL;
  
  /* Read component name */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, componentRequested);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }
  
  /* Read testcase ID */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, testCaseId);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }
  
  /* Read result filename */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, resultFileName);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }

  /* Read result file type */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, fOpenMode);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }
  
  /* Read instance Number */
  result = XdbgCmdNextNum(pContext, pCmdEntry, ppCmdLine, (UINT32 *)&instance);
  if (ERR_NOERR != result)
  {
    return result;
  }

  /* Open the result file */
  fpResult = fopen(resultFileName, fOpenMode);

  if(NULL == fpResult)
  {
    PRINT(PRINT_ERR_MSG, "%s: Error in result file open\n", __FUNCTION__);
    fprintf(fpResult, "%s : FAIL - Error in result file open\n", testCaseId);
    return ERR_INVNAME;
  }
  
  thisClient =  (OMTB_CLIENT_PRIVATE*)OMTB_GetCompPrivHandle(componentRequested, instance);

  /* Set the component's OMX_PARAM_PORTDEFINITIONTYPE structure (input) */
  OMTB_SetHeader( thisClient->inPortParams->cmnInParams.pInPortDef,
                  sizeof(OMX_PARAM_PORTDEFINITIONTYPE));

  thisClient->inPortParams->cmnInParams.pInPortDef->nPortIndex = OMTB_H264_VDEC_INPUT_PORT_IDX;
  
  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;
  
  /*Set the inPort Definition*/
  err = OMX_GetConfig( thisClient->omtbPvt.handle,
                          OMX_IndexParamPortDefinition,
                          thisClient->inPortParams->cmnInParams.pInPortDef);
  
  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_GetConfig");

  if(OMX_ErrorNone != err)
  {
    OMTB_OmxReturnStatusString(err, returnString);
    strcpy(testCaseResult, "FAIL in OMX_GetConfig()");
    fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
    result = ERR_INVNAME;
  }

  /* Set the component's OMX_PARAM_PORTDEFINITIONTYPE structure (input) */
  OMTB_SetHeader( thisClient->inPortParams->cmnInParams.pInPortDef,
                  sizeof(OMX_PARAM_PORTDEFINITIONTYPE));
  
  thisClient->inPortParams->cmnInParams.pInPortDef->nPortIndex = OMTB_H264_VDEC_INVALID_PORT_IDX;
  
  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;
  
  /* Send the portInit parameter structure */
  err = OMX_SetConfig( thisClient->omtbPvt.handle,
                          OMX_IndexParamPortDefinition,
                          thisClient->inPortParams->cmnInParams.pInPortDef);
  
  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_SetConfig");
  
  if(OMX_ErrorBadPortIndex == err)
  {
    strcpy(testCaseResult, "PASS");
    fprintf(fpResult, "%s : %s\n", testCaseId, testCaseResult);
  }
  else
  {
    OMTB_OmxReturnStatusString(err, returnString);
    strcpy(testCaseResult, "FAIL");
    fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
    result = ERR_INVNAME;
  }

  fclose(fpResult);
  return result;
}


/******************************************************************************\
 *      OMTB_OmxGetParameterOnce Function Definition
\******************************************************************************/
/**
 *
 *  @brief    This Function performs OMX_GetParameter API testing.
 *
 *  @param    Pointer to MX_DBG_CMD_CONTEXT_T structure
 *            Pointer to MX_DBG_CMD_Entry_T structure
 *            Character Double Pointer containing the command
 *
 *  @return   ERR_NOERR           successful,
 *            ERR_END_OF_CMD      help was requested,
 *            ERR_INVNAME         otherwise.

 *
 */

MX_Result OMTB_OmxGetParameterOnce(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine)
{
  OMX_ERRORTYPE err = OMX_ErrorNone;
  unsigned int instance = 0;
  char resultFileName[OMTB_MAX_LEN] = {"\0"};
  char fOpenMode[OMTB_MAX_LEN] = {"\0"};
  char testCaseId[OMTB_MAX_LEN] = {"\0"};
  char testCaseResult[OMTB_MAX_LEN] = {"\0"}; char returnString[OMTB_MAX_LEN] = {"\0"};
  FILE *fpResult = NULL;
  MX_Result  result = ERR_NOERR;
  OMTB_CLIENT_PRIVATE* thisClient = NULL;
  char componentRequested[OMX_MAX_STRINGNAME_SIZE] = {"\0"};  
  OMTB_OMX_API_TIMING_VAR_DECL;

  /* Read component name */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, componentRequested);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }
  

  /* Read testcase ID */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, testCaseId);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }
  
  /* Read result filename */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, resultFileName);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }

  /* Read result file type */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, fOpenMode);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }
  
  /* Read instance Number */
  result = XdbgCmdNextNum(pContext, pCmdEntry, ppCmdLine, (UINT32 *)&instance);
  if (ERR_NOERR != result)
  {
    return result;
  }

  /* Open the result file */
  fpResult = fopen(resultFileName, fOpenMode);

  if(NULL == fpResult)
  {
    PRINT(PRINT_ERR_MSG, "%s: Error in result file open\n", __FUNCTION__);
    fprintf(fpResult, "%s : FAIL - Error in result file open\n", testCaseId);
    return ERR_INVNAME;
  }
  
  thisClient =  (OMTB_CLIENT_PRIVATE*)OMTB_GetCompPrivHandle(componentRequested, instance); 

  /* Set the component's OMX_PARAM_PORTDEFINITIONTYPE structure (input) */
  OMTB_SetHeader( thisClient->inPortParams->cmnInParams.pInPortDef,
                  sizeof(OMX_PARAM_PORTDEFINITIONTYPE));

  thisClient->inPortParams->cmnInParams.pInPortDef->nPortIndex = OMTB_H264_VDEC_INPUT_PORT_IDX;
  
  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;
  
  /*Set the inPort Definition*/
  err = OMX_GetParameter( thisClient->omtbPvt.handle,
                          OMX_IndexParamPortDefinition,
                          thisClient->inPortParams->cmnInParams.pInPortDef);
  
  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_GetParameter");

  if(OMX_ErrorNone == err)
  {
    strcpy(testCaseResult, "PASS");
    fprintf(fpResult, "%s : %s\n", testCaseId, testCaseResult);
  }
  else
  {
    OMTB_OmxReturnStatusString(err, returnString);
    strcpy(testCaseResult, "FAIL");
    fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
    result = ERR_INVNAME;
  }

  fclose(fpResult);
  return result;
}


/******************************************************************************\
 *      OMTB_OmxGetParameterNullCfgStruct Function Definition
\******************************************************************************/
/**
 *
 *  @brief    This Function performs OMX_GetParameter API testing.
 *
 *  @param    Pointer to MX_DBG_CMD_CONTEXT_T structure
 *            Pointer to MX_DBG_CMD_Entry_T structure
 *            Character Double Pointer containing the command
 *
 *  @return   ERR_NOERR           successful,
 *            ERR_END_OF_CMD      help was requested,
 *            ERR_INVNAME         otherwise.

 *
 */

MX_Result OMTB_OmxGetParameterNullCfgStruct(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine)
{
  OMX_ERRORTYPE err = OMX_ErrorNone;
  unsigned int instance = 0;
  char resultFileName[OMTB_MAX_LEN] = {"\0"};
  char fOpenMode[OMTB_MAX_LEN] = {"\0"};
  char testCaseId[OMTB_MAX_LEN] = {"\0"};
  char testCaseResult[OMTB_MAX_LEN] = {"\0"}; char returnString[OMTB_MAX_LEN] = {"\0"};
  FILE *fpResult = NULL;
  MX_Result  result = ERR_NOERR;
  OMTB_CLIENT_PRIVATE* thisClient = NULL;
  char componentRequested[OMX_MAX_STRINGNAME_SIZE] = {"\0"};  
  OMTB_OMX_API_TIMING_VAR_DECL;

  /* Read component name */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, componentRequested);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }
  

  /* Read testcase ID */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, testCaseId);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }
  
  /* Read result filename */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, resultFileName);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }

  /* Read result file type */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, fOpenMode);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }
  
  /* Read instance Number */
  result = XdbgCmdNextNum(pContext, pCmdEntry, ppCmdLine, (UINT32 *)&instance);
  if (ERR_NOERR != result)
  {
    return result;
  }

  /* Open the result file */
  fpResult = fopen(resultFileName, fOpenMode);

  if(NULL == fpResult)
  {
    PRINT(PRINT_ERR_MSG, "%s: Error in result file open\n", __FUNCTION__);
    fprintf(fpResult, "%s : FAIL - Error in result file open\n", testCaseId);
    return ERR_INVNAME;
  }
  
  thisClient =  (OMTB_CLIENT_PRIVATE*)OMTB_GetCompPrivHandle(componentRequested, instance); 

  /* Set the component's OMX_PARAM_PORTDEFINITIONTYPE structure (input) */
  OMTB_SetHeader( thisClient->inPortParams->cmnInParams.pInPortDef,
                  sizeof(OMX_PARAM_PORTDEFINITIONTYPE));

  thisClient->inPortParams->cmnInParams.pInPortDef->nPortIndex = OMTB_H264_VDEC_INPUT_PORT_IDX;
  
  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;
  
  /*Set the inPort Definition*/
  err = OMX_GetParameter( thisClient->omtbPvt.handle,
                          OMX_IndexParamPortDefinition,
                          NULL);
  
  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_GetParameter");

  if(OMX_ErrorBadParameter == err)
  {
    strcpy(testCaseResult, "PASS");
    fprintf(fpResult, "%s : %s\n", testCaseId, testCaseResult);
  }
  else
  {
    OMTB_OmxReturnStatusString(err, returnString);
    strcpy(testCaseResult, "FAIL");
    fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
    result = ERR_INVNAME;
  }

  fclose(fpResult);
  return result;
}


/******************************************************************************\
 *      OMTB_OmxGetParameterOnce Function Definition
\******************************************************************************/
/**
 *
 *  @brief    This Function performs OMX_GetParameter API testing.
 *
 *  @param    Pointer to MX_DBG_CMD_CONTEXT_T structure
 *            Pointer to MX_DBG_CMD_Entry_T structure
 *            Character Double Pointer containing the command
 *
 *  @return   ERR_NOERR           successful,
 *            ERR_END_OF_CMD      help was requested,
 *            ERR_INVNAME         otherwise.

 *
 */

MX_Result OMTB_OmxGetParameterNullHandle(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine)
{
  OMX_ERRORTYPE err = OMX_ErrorNone;
  unsigned int instance = 0;
  char resultFileName[OMTB_MAX_LEN] = {"\0"};
  char fOpenMode[OMTB_MAX_LEN] = {"\0"};
  char testCaseId[OMTB_MAX_LEN] = {"\0"};
  char testCaseResult[OMTB_MAX_LEN] = {"\0"}; char returnString[OMTB_MAX_LEN] = {"\0"};
  FILE *fpResult = NULL;
  MX_Result  result = ERR_NOERR;
  OMTB_CLIENT_PRIVATE* thisClient = NULL;
  char componentRequested[OMX_MAX_STRINGNAME_SIZE] = {"\0"};  
  OMTB_OMX_API_TIMING_VAR_DECL;

  /* Read component name */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, componentRequested);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }
  

  /* Read testcase ID */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, testCaseId);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }
  
  /* Read result filename */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, resultFileName);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }

  /* Read result file type */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, fOpenMode);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }
  
  /* Read instance Number */
  result = XdbgCmdNextNum(pContext, pCmdEntry, ppCmdLine, (UINT32 *)&instance);
  if (ERR_NOERR != result)
  {
    return result;
  }

  /* Open the result file */
  fpResult = fopen(resultFileName, fOpenMode);

  if(NULL == fpResult)
  {
    PRINT(PRINT_ERR_MSG, "%s: Error in result file open\n", __FUNCTION__);
    fprintf(fpResult, "%s : FAIL - Error in result file open\n", testCaseId);
    return ERR_INVNAME;
  }
  
  thisClient =  (OMTB_CLIENT_PRIVATE*)OMTB_GetCompPrivHandle(componentRequested, instance); 

  /* Set the component's OMX_PARAM_PORTDEFINITIONTYPE structure (input) */
  OMTB_SetHeader( thisClient->inPortParams->cmnInParams.pInPortDef,
                  sizeof(OMX_PARAM_PORTDEFINITIONTYPE));

  thisClient->inPortParams->cmnInParams.pInPortDef->nPortIndex = OMTB_H264_VDEC_INPUT_PORT_IDX;
  
  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;
  
  /*Set the inPort Definition*/
  err = OMX_GetParameter( NULL,
                          OMX_IndexParamPortDefinition,
                          thisClient->inPortParams->cmnInParams.pInPortDef);
  
  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_GetParameter");

  if(OMX_ErrorBadParameter == err)
  {
    strcpy(testCaseResult, "PASS");
    fprintf(fpResult, "%s : %s\n", testCaseId, testCaseResult);
  }
  else
  {
    OMTB_OmxReturnStatusString(err, returnString);
    strcpy(testCaseResult, "FAIL");
    fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
    result = ERR_INVNAME;
  }

  fclose(fpResult);
  return result;
}


/******************************************************************************\
 *      OMTB_OmxGetParameterVerMismatch Function Definition
\******************************************************************************/
/**
 *
 *  @brief    This Function performs OMX_GetParameter API testing.
 *
 *  @param    Pointer to MX_DBG_CMD_CONTEXT_T structure
 *            Pointer to MX_DBG_CMD_Entry_T structure
 *            Character Double Pointer containing the command
 *
 *  @return   ERR_NOERR           successful,
 *            ERR_END_OF_CMD      help was requested,
 *            ERR_INVNAME         otherwise.

 *
 */

MX_Result OMTB_OmxGetParameterVerMismatch(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine)
{
  OMX_ERRORTYPE err = OMX_ErrorNone;
  unsigned int instance = 0;
  char resultFileName[OMTB_MAX_LEN] = {"\0"};
  char fOpenMode[OMTB_MAX_LEN] = {"\0"};
  char testCaseId[OMTB_MAX_LEN] = {"\0"};
  char testCaseResult[OMTB_MAX_LEN] = {"\0"}; char returnString[OMTB_MAX_LEN] = {"\0"};
  FILE *fpResult = NULL;
  MX_Result  result = ERR_NOERR;
  OMTB_CLIENT_PRIVATE* thisClient = NULL;
  char componentRequested[OMX_MAX_STRINGNAME_SIZE] = {"\0"};  
  OMTB_OMX_API_TIMING_VAR_DECL;

  /* Read component name */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, componentRequested);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }
  
  /* Read testcase ID */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, testCaseId);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }
  
  /* Read result filename */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, resultFileName);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }

  /* Read result file type */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, fOpenMode);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }
  
  /* Read instance Number */
  result = XdbgCmdNextNum(pContext, pCmdEntry, ppCmdLine, (UINT32 *)&instance);
  if (ERR_NOERR != result)
  {
    return result;
  }

  /* Open the result file */
  fpResult = fopen(resultFileName, fOpenMode);

  if(NULL == fpResult)
  {
    PRINT(PRINT_ERR_MSG, "%s: Error in result file open\n", __FUNCTION__);
    fprintf(fpResult, "%s : FAIL - Error in result file open\n", testCaseId);
    return ERR_INVNAME;
  }
  
  thisClient =  (OMTB_CLIENT_PRIVATE*)OMTB_GetCompPrivHandle(componentRequested, instance); 

  /* Set the component's OMX_PARAM_PORTDEFINITIONTYPE structure (input) */
  /* set incorrect version numbers */
  thisClient->inPortParams->cmnInParams.pInPortDef->nSize = sizeof(OMX_PARAM_PORTDEFINITIONTYPE);
  thisClient->inPortParams->cmnInParams.pInPortDef->nVersion.s.nVersionMajor = 1;
  thisClient->inPortParams->cmnInParams.pInPortDef->nVersion.s.nVersionMinor = 2;
  thisClient->inPortParams->cmnInParams.pInPortDef->nVersion.s.nRevision = 0;
  thisClient->inPortParams->cmnInParams.pInPortDef->nVersion.s.nRevision = 0;

  thisClient->inPortParams->cmnInParams.pInPortDef->nPortIndex = OMTB_H264_VDEC_INPUT_PORT_IDX;
  
  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;
  
  /*Set the inPort Definition*/
  err = OMX_GetParameter( thisClient->omtbPvt.handle,
                          OMX_IndexParamPortDefinition,
                          thisClient->inPortParams->cmnInParams.pInPortDef);
  
  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_GetParameter");

  if(OMX_ErrorVersionMismatch == err)
  {
    strcpy(testCaseResult, "PASS");
    fprintf(fpResult, "%s : %s\n", testCaseId, testCaseResult);
  }
  else
  {
    OMTB_OmxReturnStatusString(err, returnString);
    strcpy(testCaseResult, "FAIL");
    fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
    result = ERR_INVNAME;
  }

  fclose(fpResult);
  return result;
}


/******************************************************************************\
 *      OMTB_OmxGetParameterTimeOut Function Definition
\******************************************************************************/
/**
 *
 *  @brief    This Function performs OMX_GetParameter API testing.
 *
 *  @param    Pointer to MX_DBG_CMD_CONTEXT_T structure
 *            Pointer to MX_DBG_CMD_Entry_T structure
 *            Character Double Pointer containing the command
 *
 *  @return   ERR_NOERR           successful,
 *            ERR_END_OF_CMD      help was requested,
 *            ERR_INVNAME         otherwise.

 *
 */

MX_Result OMTB_OmxGetParameterTimeOut(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine)
{
  OMX_ERRORTYPE err = OMX_ErrorNone;
  unsigned int instance = 0;
  char resultFileName[OMTB_MAX_LEN] = {"\0"};
  char fOpenMode[OMTB_MAX_LEN] = {"\0"};
  char testCaseId[OMTB_MAX_LEN] = {"\0"};
  char testCaseResult[OMTB_MAX_LEN] = {"\0"}; char returnString[OMTB_MAX_LEN] = {"\0"};
  FILE *fpResult = NULL;
  MX_Result  result = ERR_NOERR;
  OMTB_CLIENT_PRIVATE* thisClient = NULL;
  char componentRequested[OMX_MAX_STRINGNAME_SIZE] = {"\0"};  
  OMTB_OMX_API_TIMING_VAR_DECL;

  /* Read component name */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, componentRequested);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }
  
  /* Read testcase ID */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, testCaseId);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }
  
  /* Read result filename */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, resultFileName);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }

  /* Read result file type */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, fOpenMode);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }
  
  /* Read instance Number */
  result = XdbgCmdNextNum(pContext, pCmdEntry, ppCmdLine, (UINT32 *)&instance);
  if (ERR_NOERR != result)
  {
    return result;
  }

  /* Open the result file */
  fpResult = fopen(resultFileName, fOpenMode);

  if(NULL == fpResult)
  {
    PRINT(PRINT_ERR_MSG, "%s: Error in result file open\n", __FUNCTION__);
    fprintf(fpResult, "%s : FAIL - Error in result file open\n", testCaseId);
    return ERR_INVNAME;
  }
  
  thisClient =  (OMTB_CLIENT_PRIVATE*)OMTB_GetCompPrivHandle(componentRequested, instance); 

  /* Set the component's OMX_PARAM_PORTDEFINITIONTYPE structure (input) */
  OMTB_SetHeader( thisClient->inPortParams->cmnInParams.pInPortDef,
                  sizeof(OMX_PARAM_PORTDEFINITIONTYPE));

  thisClient->inPortParams->cmnInParams.pInPortDef->nPortIndex = OMTB_H264_VDEC_INPUT_PORT_IDX;
  
  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;
  
  /*Set the inPort Definition*/
  err = OMX_GetParameter( thisClient->omtbPvt.handle,
                          OMX_IndexParamPortDefinition,
                          thisClient->inPortParams->cmnInParams.pInPortDef);
  
  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_GetParameter");

  if(OMX_ErrorTimeout == err)
  {
    strcpy(testCaseResult, "PASS");
    fprintf(fpResult, "%s : %s\n", testCaseId, testCaseResult);
  }
  else
  {
    OMTB_OmxReturnStatusString(err, returnString);
    strcpy(testCaseResult, "FAIL");
    fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
    result = ERR_INVNAME;
  }

  fclose(fpResult);
  return result;
}

/******************************************************************************\
 *      OMTB_OmxGetParameterUnSupportedSettings Function Definition
\******************************************************************************/
/**
 *
 *  @brief    This Function performs OMX_GetParameter API testing.
 *
 *  @param    Pointer to MX_DBG_CMD_CONTEXT_T structure
 *            Pointer to MX_DBG_CMD_Entry_T structure
 *            Character Double Pointer containing the command
 *
 *  @return   ERR_NOERR           successful,
 *            ERR_END_OF_CMD      help was requested,
 *            ERR_INVNAME         otherwise.

 *
 */

MX_Result OMTB_OmxGetParameterUnSupportedSettings(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine)
{
  OMX_ERRORTYPE err = OMX_ErrorNone;
  unsigned int instance = 0;
  char resultFileName[OMTB_MAX_LEN] = {"\0"};
  char fOpenMode[OMTB_MAX_LEN] = {"\0"};
  char testCaseId[OMTB_MAX_LEN] = {"\0"};
  char testCaseResult[OMTB_MAX_LEN] = {"\0"}; char returnString[OMTB_MAX_LEN] = {"\0"};
  FILE *fpResult = NULL;
  MX_Result  result = ERR_NOERR;
  OMTB_CLIENT_PRIVATE* thisClient = NULL;
  char componentRequested[OMX_MAX_STRINGNAME_SIZE] = {"\0"};  
  OMTB_OMX_API_TIMING_VAR_DECL;

  /* Read component name */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, componentRequested);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }
  
  /* Read testcase ID */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, testCaseId);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }
  
  /* Read result filename */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, resultFileName);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }

  /* Read result file type */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, fOpenMode);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }
  
  /* Read instance Number */
  result = XdbgCmdNextNum(pContext, pCmdEntry, ppCmdLine, (UINT32 *)&instance);
  if (ERR_NOERR != result)
  {
    return result;
  }

  /* Open the result file */
  fpResult = fopen(resultFileName, fOpenMode);

  if(NULL == fpResult)
  {
    PRINT(PRINT_ERR_MSG, "%s: Error in result file open\n", __FUNCTION__);
    fprintf(fpResult, "%s : FAIL - Error in result file open\n", testCaseId);
    return ERR_INVNAME;
  }
  
  thisClient =  (OMTB_CLIENT_PRIVATE*)OMTB_GetCompPrivHandle(componentRequested, instance); 

  /* Set the component's OMX_PARAM_PORTDEFINITIONTYPE structure (input) */
  OMTB_SetHeader( thisClient->inPortParams->cmnInParams.pInPortDef,
                  sizeof(OMX_PARAM_PORTDEFINITIONTYPE));

  thisClient->inPortParams->cmnInParams.pInPortDef->nPortIndex = OMTB_H264_VDEC_INPUT_PORT_IDX;
  
  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;
  
  /*Set the inPort Definition*/
  err = OMX_GetParameter( thisClient->omtbPvt.handle,
                          OMX_IndexParamPortDefinition,
                          thisClient->inPortParams->cmnInParams.pInPortDef);
  
  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_GetParameter");

  if(OMX_ErrorUnsupportedSetting == err)
  {
    strcpy(testCaseResult, "PASS");
    fprintf(fpResult, "%s : %s\n", testCaseId, testCaseResult);
  }
  else
  {
    OMTB_OmxReturnStatusString(err, returnString);
    strcpy(testCaseResult, "FAIL");
    fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
    result = ERR_INVNAME;
  }

  fclose(fpResult);
  return result;
}


/******************************************************************************\
 *      OMTB_OmxGetParameterUnSupportedIndex Function Definition
\******************************************************************************/
/**
 *
 *  @brief    This Function performs OMX_GetParameter API testing.
 *
 *  @param    Pointer to MX_DBG_CMD_CONTEXT_T structure
 *            Pointer to MX_DBG_CMD_Entry_T structure
 *            Character Double Pointer containing the command
 *
 *  @return   ERR_NOERR           successful,
 *            ERR_END_OF_CMD      help was requested,
 *            ERR_INVNAME         otherwise.

 *
 */

MX_Result OMTB_OmxGetParameterUnSupportedIndex(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine)
{
  OMX_ERRORTYPE err = OMX_ErrorNone;
  unsigned int instance = 0;
  char resultFileName[OMTB_MAX_LEN] = {"\0"};
  char fOpenMode[OMTB_MAX_LEN] = {"\0"};
  char testCaseId[OMTB_MAX_LEN] = {"\0"};
  char testCaseResult[OMTB_MAX_LEN] = {"\0"}; char returnString[OMTB_MAX_LEN] = {"\0"};
  FILE *fpResult = NULL;
  MX_Result  result = ERR_NOERR;
  OMTB_CLIENT_PRIVATE* thisClient = NULL;
  char componentRequested[OMX_MAX_STRINGNAME_SIZE] = {"\0"};  
  OMTB_OMX_API_TIMING_VAR_DECL;

  /* Read component name */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, componentRequested);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }
  
  /* Read testcase ID */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, testCaseId);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }
  
  /* Read result filename */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, resultFileName);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }

  /* Read result file type */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, fOpenMode);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }
  
  /* Read instance Number */
  result = XdbgCmdNextNum(pContext, pCmdEntry, ppCmdLine, (UINT32 *)&instance);
  if (ERR_NOERR != result)
  {
    return result;
  }

  /* Open the result file */
  fpResult = fopen(resultFileName, fOpenMode);

  if(NULL == fpResult)
  {
    PRINT(PRINT_ERR_MSG, "%s: Error in result file open\n", __FUNCTION__);
    fprintf(fpResult, "%s : FAIL - Error in result file open\n", testCaseId);
    return ERR_INVNAME;
  }
  
  thisClient =  (OMTB_CLIENT_PRIVATE*)OMTB_GetCompPrivHandle(componentRequested, instance); 

  /* Set the component's OMX_PARAM_PORTDEFINITIONTYPE structure (input) */
  OMTB_SetHeader( thisClient->inPortParams->cmnInParams.pInPortDef,
                  sizeof(OMX_PARAM_PORTDEFINITIONTYPE));

  thisClient->inPortParams->cmnInParams.pInPortDef->nPortIndex = OMTB_H264_VDEC_INPUT_PORT_IDX;
  
  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;
  
  /*Set the inPort Definition*/
  err = OMX_GetParameter( thisClient->omtbPvt.handle,
                          OMX_IndexMax,
                          thisClient->inPortParams->cmnInParams.pInPortDef);
  
  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_GetParameter");

  if(OMX_ErrorUnsupportedIndex == err)
  {
    strcpy(testCaseResult, "PASS");
    fprintf(fpResult, "%s : %s\n", testCaseId, testCaseResult);
  }
  else
  {
    OMTB_OmxReturnStatusString(err, returnString);
    strcpy(testCaseResult, "FAIL");
    fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
    result = ERR_INVNAME;
  }

  fclose(fpResult);
  return result;
}


/******************************************************************************\
 *      OMTB_OmxGetParameterWrongPort Function Definition
\******************************************************************************/
/**
 *
 *  @brief    This Function performs OMX_GetParameter API testing.
 *
 *  @param    Pointer to MX_DBG_CMD_CONTEXT_T structure
 *            Pointer to MX_DBG_CMD_Entry_T structure
 *            Character Double Pointer containing the command
 *
 *  @return   ERR_NOERR           successful,
 *            ERR_END_OF_CMD      help was requested,
 *            ERR_INVNAME         otherwise.

 *
 */

MX_Result OMTB_OmxGetParameterWrongPort(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine)
{
  OMX_ERRORTYPE err = OMX_ErrorNone;
  unsigned int instance = 0;
  char resultFileName[OMTB_MAX_LEN] = {"\0"};
  char fOpenMode[OMTB_MAX_LEN] = {"\0"};
  char testCaseId[OMTB_MAX_LEN] = {"\0"};
  char testCaseResult[OMTB_MAX_LEN] = {"\0"}; char returnString[OMTB_MAX_LEN] = {"\0"};
  FILE *fpResult = NULL;
  MX_Result  result = ERR_NOERR;
  OMTB_CLIENT_PRIVATE* thisClient = NULL;
  char componentRequested[OMX_MAX_STRINGNAME_SIZE] = {"\0"};  
  OMTB_OMX_API_TIMING_VAR_DECL;

  /* Read component name */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, componentRequested);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }
  
  /* Read testcase ID */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, testCaseId);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }
  
  /* Read result filename */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, resultFileName);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }

  /* Read result file type */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, fOpenMode);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }
  
  /* Read instance Number */
  result = XdbgCmdNextNum(pContext, pCmdEntry, ppCmdLine, (UINT32 *)&instance);
  if (ERR_NOERR != result)
  {
    return result;
  }

  /* Open the result file */
  fpResult = fopen(resultFileName, fOpenMode);

  if(NULL == fpResult)
  {
    PRINT(PRINT_ERR_MSG, "%s: Error in result file open\n", __FUNCTION__);
    fprintf(fpResult, "%s : FAIL - Error in result file open\n", testCaseId);
    return ERR_INVNAME;
  }
  
  thisClient =  (OMTB_CLIENT_PRIVATE*)OMTB_GetCompPrivHandle(componentRequested, instance); 

  /* Set the component's OMX_PARAM_PORTDEFINITIONTYPE structure (input) */
  OMTB_SetHeader( thisClient->inPortParams->cmnInParams.pInPortDef,
                  sizeof(OMX_PARAM_PORTDEFINITIONTYPE));

  thisClient->inPortParams->cmnInParams.pInPortDef->nPortIndex = OMTB_H264_VDEC_INVALID_PORT_IDX;
  
  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;
  
  /*Set the inPort Definition*/
  err = OMX_GetParameter( thisClient->omtbPvt.handle,
                          OMX_IndexParamPortDefinition,
                          thisClient->inPortParams->cmnInParams.pInPortDef);
  
  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_GetParameter");

  if(OMX_ErrorBadPortIndex == err)
  {
    strcpy(testCaseResult, "PASS");
    fprintf(fpResult, "%s : %s\n", testCaseId, testCaseResult);
  }
  else
  {
    OMTB_OmxReturnStatusString(err, returnString);
    strcpy(testCaseResult, "FAIL");
    fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
    result = ERR_INVNAME;
  }

  fclose(fpResult);
  return result;
}


/******************************************************************************\
 *      OMTB_OmxGetParameterIdleState Function Definition
\******************************************************************************/
/**
 *
 *  @brief    This Function performs OMX_GetParameter API testing.
 *
 *  @param    Pointer to MX_DBG_CMD_CONTEXT_T structure
 *            Pointer to MX_DBG_CMD_Entry_T structure
 *            Character Double Pointer containing the command
 *
 *  @return   ERR_NOERR           successful,
 *            ERR_END_OF_CMD      help was requested,
 *            ERR_INVNAME         otherwise.

 *
 */

MX_Result OMTB_OmxGetParameterIdleState(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine)
{
  OMX_ERRORTYPE err = OMX_ErrorNone;
  unsigned int instance = 0;
  char resultFileName[OMTB_MAX_LEN] = {"\0"};
  char fOpenMode[OMTB_MAX_LEN] = {"\0"};
  char testCaseId[OMTB_MAX_LEN] = {"\0"};
  char testCaseResult[OMTB_MAX_LEN] = {"\0"}; char returnString[OMTB_MAX_LEN] = {"\0"};
  FILE *fpResult = NULL;
  MX_Result  result = ERR_NOERR;
  OMTB_CLIENT_PRIVATE* thisClient = NULL;
  char componentRequested[OMX_MAX_STRINGNAME_SIZE] = {"\0"};  
  OMTB_OMX_API_TIMING_VAR_DECL;

  /* Read component name */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, componentRequested);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }
  
  /* Read testcase ID */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, testCaseId);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }
  
  /* Read result filename */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, resultFileName);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }

  /* Read result file type */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, fOpenMode);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }
  
  /* Read instance Number */
  result = XdbgCmdNextNum(pContext, pCmdEntry, ppCmdLine, (UINT32 *)&instance);
  if (ERR_NOERR != result)
  {
    return result;
  }

  /* Open the result file */
  fpResult = fopen(resultFileName, fOpenMode);

  if(NULL == fpResult)
  {
    PRINT(PRINT_ERR_MSG, "%s: Error in result file open\n", __FUNCTION__);
    fprintf(fpResult, "%s : FAIL - Error in result file open\n", testCaseId);
    return ERR_INVNAME;
  }
  
  thisClient =  (OMTB_CLIENT_PRIVATE*)OMTB_GetCompPrivHandle(componentRequested, instance); 

  /* Set the component's OMX_PARAM_PORTDEFINITIONTYPE structure (input) */
  OMTB_SetHeader( thisClient->inPortParams->cmnInParams.pInPortDef,
                  sizeof(OMX_PARAM_PORTDEFINITIONTYPE));

  thisClient->inPortParams->cmnInParams.pInPortDef->nPortIndex = OMTB_H264_VDEC_INPUT_PORT_IDX;
  
  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;
  
  /*Set the inPort Definition*/
  err = OMX_GetParameter( thisClient->omtbPvt.handle,
                          OMX_IndexParamPortDefinition,
                          thisClient->inPortParams->cmnInParams.pInPortDef);
  
  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_GetParameter");

  if(OMX_ErrorIncorrectStateOperation == err)
  {
    strcpy(testCaseResult, "PASS");
    fprintf(fpResult, "%s : %s\n", testCaseId, testCaseResult);
  }
  else
  {
    OMTB_OmxReturnStatusString(err, returnString);
    strcpy(testCaseResult, "FAIL");
    fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
    result = ERR_INVNAME;
  }

  fclose(fpResult);
  return result;
}


/******************************************************************************\
 *      OMTB_OmxGetConfigOnce Function Definition
\******************************************************************************/
/**
 *
 *  @brief    This Function performs OMX_GetConfig API testing.
 *
 *  @param    Pointer to MX_DBG_CMD_CONTEXT_T structure
 *            Pointer to MX_DBG_CMD_Entry_T structure
 *            Character Double Pointer containing the command
 *
 *  @return   ERR_NOERR           successful,
 *            ERR_END_OF_CMD      help was requested,
 *            ERR_INVNAME         otherwise.

 *
 */

MX_Result OMTB_OmxGetConfigOnce(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine)
{
  OMX_ERRORTYPE err = OMX_ErrorNone;
  unsigned int instance = 0;
  char resultFileName[OMTB_MAX_LEN] = {"\0"};
  char fOpenMode[OMTB_MAX_LEN] = {"\0"};
  char testCaseId[OMTB_MAX_LEN] = {"\0"};
  char testCaseResult[OMTB_MAX_LEN] = {"\0"}; char returnString[OMTB_MAX_LEN] = {"\0"};
  FILE *fpResult = NULL;
  MX_Result  result = ERR_NOERR;
  OMTB_CLIENT_PRIVATE* thisClient = NULL;
  char componentRequested[OMX_MAX_STRINGNAME_SIZE] = {"\0"};  
  OMTB_OMX_API_TIMING_VAR_DECL;

  /* Read component name */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, componentRequested);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }
  
  /* Read testcase ID */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, testCaseId);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }
  
  /* Read result filename */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, resultFileName);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }

  /* Read result file type */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, fOpenMode);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }
  
  /* Read instance Number */
  result = XdbgCmdNextNum(pContext, pCmdEntry, ppCmdLine, (UINT32 *)&instance);
  if (ERR_NOERR != result)
  {
    return result;
  }

  /* Open the result file */
  fpResult = fopen(resultFileName, fOpenMode);

  if(NULL == fpResult)
  {
    PRINT(PRINT_ERR_MSG, "%s: Error in result file open\n", __FUNCTION__);
    fprintf(fpResult, "%s : FAIL - Error in result file open\n", testCaseId);
    return ERR_INVNAME;
  }
  
  thisClient =  (OMTB_CLIENT_PRIVATE*)OMTB_GetCompPrivHandle(componentRequested, instance); 

  /* Set the component's OMX_PARAM_PORTDEFINITIONTYPE structure (input) */
  OMTB_SetHeader( thisClient->inPortParams->cmnInParams.pInPortDef,
                  sizeof(OMX_PARAM_PORTDEFINITIONTYPE));

  thisClient->inPortParams->cmnInParams.pInPortDef->nPortIndex = OMTB_H264_VDEC_INPUT_PORT_IDX;
  
  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;
  
  /*Set the inPort Definition*/
  err = OMX_GetConfig( thisClient->omtbPvt.handle,
                          OMX_IndexParamPortDefinition,
                          thisClient->inPortParams->cmnInParams.pInPortDef);
  
  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_GetConfig");

  if(OMX_ErrorNone == err)
  {
    strcpy(testCaseResult, "PASS");
    fprintf(fpResult, "%s : %s\n", testCaseId, testCaseResult);
  }
  else
  {
    OMTB_OmxReturnStatusString(err, returnString);
    strcpy(testCaseResult, "FAIL");
    fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
    result = ERR_INVNAME;
  }

  fclose(fpResult);
  return result;
}


/******************************************************************************\
 *      OMTB_OmxGetConfigNullCfgStruct Function Definition
\******************************************************************************/
/**
 *
 *  @brief    This Function performs OMX_GetConfig API testing.
 *
 *  @param    Pointer to MX_DBG_CMD_CONTEXT_T structure
 *            Pointer to MX_DBG_CMD_Entry_T structure
 *            Character Double Pointer containing the command
 *
 *  @return   ERR_NOERR           successful,
 *            ERR_END_OF_CMD      help was requested,
 *            ERR_INVNAME         otherwise.

 *
 */

MX_Result OMTB_OmxGetConfigNullCfgStruct(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine)
{
  OMX_ERRORTYPE err = OMX_ErrorNone;
  unsigned int instance = 0;
  char resultFileName[OMTB_MAX_LEN] = {"\0"};
  char fOpenMode[OMTB_MAX_LEN] = {"\0"};
  char testCaseId[OMTB_MAX_LEN] = {"\0"};
  char testCaseResult[OMTB_MAX_LEN] = {"\0"}; 
  FILE *fpResult = NULL;
  MX_Result  result = ERR_NOERR;
  OMTB_CLIENT_PRIVATE* thisClient = NULL;
  char componentRequested[OMX_MAX_STRINGNAME_SIZE] = {"\0"};  
  OMTB_OMX_API_TIMING_VAR_DECL;

  /* Read component name */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, componentRequested);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }
  
  /* Read testcase ID */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, testCaseId);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }
  
  /* Read result filename */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, resultFileName);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }

  /* Read result file type */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, fOpenMode);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }
  
  /* Read instance Number */
  result = XdbgCmdNextNum(pContext, pCmdEntry, ppCmdLine, (UINT32 *)&instance);
  if (ERR_NOERR != result)
  {
    return result;
  }

  /* Open the result file */
  fpResult = fopen(resultFileName, fOpenMode);

  if(NULL == fpResult)
  {
    PRINT(PRINT_ERR_MSG, "%s: Error in result file open\n", __FUNCTION__);
    fprintf(fpResult, "%s : FAIL - Error in result file open\n", testCaseId);
    return ERR_INVNAME;
  }
  
  thisClient =  (OMTB_CLIENT_PRIVATE*)OMTB_GetCompPrivHandle(componentRequested, instance); 

  /* Set the component's OMX_PARAM_PORTDEFINITIONTYPE structure (input) */
  OMTB_SetHeader( thisClient->inPortParams->cmnInParams.pInPortDef,
                  sizeof(OMX_PARAM_PORTDEFINITIONTYPE));

  thisClient->inPortParams->cmnInParams.pInPortDef->nPortIndex = OMTB_H264_VDEC_INPUT_PORT_IDX;
  
  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;
  
  /*Set the inPort Definition*/
  err = OMX_GetConfig( thisClient->omtbPvt.handle,
                          OMX_IndexParamPortDefinition,
                          NULL);
  
  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_GetConfig");

  if(OMX_ErrorBadParameter == err)
  {
    strcpy(testCaseResult, "PASS");
    fprintf(fpResult, "%s : %s\n", testCaseId, testCaseResult);
  }
  else
  {
    OMTB_OmxReturnStatus(err);
    strcpy(testCaseResult, "FAIL");
    fprintf(fpResult, "%s : %s\n", testCaseId, testCaseResult);
    result = ERR_INVNAME;
  }

  fclose(fpResult);
  return result;
}


/******************************************************************************\
 *      OMTB_OmxGetConfigOnce Function Definition
\******************************************************************************/
/**
 *
 *  @brief    This Function performs OMX_GetConfig API testing.
 *
 *  @param    Pointer to MX_DBG_CMD_CONTEXT_T structure
 *            Pointer to MX_DBG_CMD_Entry_T structure
 *            Character Double Pointer containing the command
 *
 *  @return   ERR_NOERR           successful,
 *            ERR_END_OF_CMD      help was requested,
 *            ERR_INVNAME         otherwise.

 *
 */

MX_Result OMTB_OmxGetConfigNullHandle(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine)
{
  OMX_ERRORTYPE err = OMX_ErrorNone;
  unsigned int instance = 0;
  char resultFileName[OMTB_MAX_LEN] = {"\0"};
  char fOpenMode[OMTB_MAX_LEN] = {"\0"};
  char testCaseId[OMTB_MAX_LEN] = {"\0"};
  char testCaseResult[OMTB_MAX_LEN] = {"\0"}; char returnString[OMTB_MAX_LEN] = {"\0"};
  FILE *fpResult = NULL;
  MX_Result  result = ERR_NOERR;
  OMTB_CLIENT_PRIVATE* thisClient = NULL;
  char componentRequested[OMX_MAX_STRINGNAME_SIZE] = {"\0"};  
  OMTB_OMX_API_TIMING_VAR_DECL;

  /* Read component name */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, componentRequested);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }
  
  /* Read testcase ID */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, testCaseId);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }
  
  /* Read result filename */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, resultFileName);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }

  /* Read result file type */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, fOpenMode);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }
  
  /* Read instance Number */
  result = XdbgCmdNextNum(pContext, pCmdEntry, ppCmdLine, (UINT32 *)&instance);
  if (ERR_NOERR != result)
  {
    return result;
  }

  /* Open the result file */
  fpResult = fopen(resultFileName, fOpenMode);

  if(NULL == fpResult)
  {
    PRINT(PRINT_ERR_MSG, "%s: Error in result file open\n", __FUNCTION__);
    fprintf(fpResult, "%s : FAIL - Error in result file open\n", testCaseId);
    return ERR_INVNAME;
  }
  
  thisClient =  (OMTB_CLIENT_PRIVATE*)OMTB_GetCompPrivHandle(componentRequested, instance); 

  /* Set the component's OMX_PARAM_PORTDEFINITIONTYPE structure (input) */
  OMTB_SetHeader( thisClient->inPortParams->cmnInParams.pInPortDef,
                  sizeof(OMX_PARAM_PORTDEFINITIONTYPE));

  thisClient->inPortParams->cmnInParams.pInPortDef->nPortIndex = OMTB_H264_VDEC_INPUT_PORT_IDX;
  
  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;
  
  /*Set the inPort Definition*/
  err = OMX_GetConfig( NULL,
                          OMX_IndexParamPortDefinition,
                          thisClient->inPortParams->cmnInParams.pInPortDef);
  
  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_GetConfig");

  if(OMX_ErrorBadParameter == err)
  {
    strcpy(testCaseResult, "PASS");
    fprintf(fpResult, "%s : %s\n", testCaseId, testCaseResult);
  }
  else
  {
    OMTB_OmxReturnStatusString(err, returnString);
    strcpy(testCaseResult, "FAIL");
    fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
    result = ERR_INVNAME;
  }

  fclose(fpResult);
  return result;
}


/******************************************************************************\
 *      OMTB_OmxGetConfigVerMismatch Function Definition
\******************************************************************************/
/**
 *
 *  @brief    This Function performs OMX_GetConfig API testing.
 *
 *  @param    Pointer to MX_DBG_CMD_CONTEXT_T structure
 *            Pointer to MX_DBG_CMD_Entry_T structure
 *            Character Double Pointer containing the command
 *
 *  @return   ERR_NOERR           successful,
 *            ERR_END_OF_CMD      help was requested,
 *            ERR_INVNAME         otherwise.

 *
 */

MX_Result OMTB_OmxGetConfigVerMismatch(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine)
{
  OMX_ERRORTYPE err = OMX_ErrorNone;
  unsigned int instance = 0;
  char resultFileName[OMTB_MAX_LEN] = {"\0"};
  char fOpenMode[OMTB_MAX_LEN] = {"\0"};
  char testCaseId[OMTB_MAX_LEN] = {"\0"};
  char testCaseResult[OMTB_MAX_LEN] = {"\0"}; char returnString[OMTB_MAX_LEN] = {"\0"};
  FILE *fpResult = NULL;
  MX_Result  result = ERR_NOERR;
  OMTB_CLIENT_PRIVATE* thisClient = NULL;
  char componentRequested[OMX_MAX_STRINGNAME_SIZE] = {"\0"};  
  OMTB_OMX_API_TIMING_VAR_DECL;

  /* Read component name */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, componentRequested);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }
  
  /* Read testcase ID */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, testCaseId);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }
  
  /* Read result filename */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, resultFileName);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }

  /* Read result file type */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, fOpenMode);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }
  
  /* Read instance Number */
  result = XdbgCmdNextNum(pContext, pCmdEntry, ppCmdLine, (UINT32 *)&instance);
  if (ERR_NOERR != result)
  {
    return result;
  }

  /* Open the result file */
  fpResult = fopen(resultFileName, fOpenMode);

  if(NULL == fpResult)
  {
    PRINT(PRINT_ERR_MSG, "%s: Error in result file open\n", __FUNCTION__);
    fprintf(fpResult, "%s : FAIL - Error in result file open\n", testCaseId);
    return ERR_INVNAME;
  }
  
  thisClient =  (OMTB_CLIENT_PRIVATE*)OMTB_GetCompPrivHandle(componentRequested, instance); 

  /* Set the component's OMX_PARAM_PORTDEFINITIONTYPE structure (input) */
  /* set incorrect version numbers */
  thisClient->inPortParams->cmnInParams.pInPortDef->nSize = sizeof(OMX_PARAM_PORTDEFINITIONTYPE);
  thisClient->inPortParams->cmnInParams.pInPortDef->nVersion.s.nVersionMajor = 1;
  thisClient->inPortParams->cmnInParams.pInPortDef->nVersion.s.nVersionMinor = 2;
  thisClient->inPortParams->cmnInParams.pInPortDef->nVersion.s.nRevision = 0;
  thisClient->inPortParams->cmnInParams.pInPortDef->nVersion.s.nRevision = 0;

  thisClient->inPortParams->cmnInParams.pInPortDef->nPortIndex = OMTB_H264_VDEC_INPUT_PORT_IDX;
  
  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;
  
  /*Set the inPort Definition*/
  err = OMX_GetConfig( thisClient->omtbPvt.handle,
                          OMX_IndexParamPortDefinition,
                          thisClient->inPortParams->cmnInParams.pInPortDef);
  
  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_GetConfig");

  if(OMX_ErrorVersionMismatch == err)
  {
    strcpy(testCaseResult, "PASS");
    fprintf(fpResult, "%s : %s\n", testCaseId, testCaseResult);
  }
  else
  {
    OMTB_OmxReturnStatusString(err, returnString);
    strcpy(testCaseResult, "FAIL");
    fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
    result = ERR_INVNAME;
  }

  fclose(fpResult);
  return result;
}


/******************************************************************************\
 *      OMTB_OmxGetConfigTimeOut Function Definition
\******************************************************************************/
/**
 *
 *  @brief    This Function performs OMX_GetConfig API testing.
 *
 *  @param    Pointer to MX_DBG_CMD_CONTEXT_T structure
 *            Pointer to MX_DBG_CMD_Entry_T structure
 *            Character Double Pointer containing the command
 *
 *  @return   ERR_NOERR           successful,
 *            ERR_END_OF_CMD      help was requested,
 *            ERR_INVNAME         otherwise.

 *
 */

MX_Result OMTB_OmxGetConfigTimeOut(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine)
{
  OMX_ERRORTYPE err = OMX_ErrorNone;
  unsigned int instance = 0;
  char resultFileName[OMTB_MAX_LEN] = {"\0"};
  char fOpenMode[OMTB_MAX_LEN] = {"\0"};
  char testCaseId[OMTB_MAX_LEN] = {"\0"};
  char testCaseResult[OMTB_MAX_LEN] = {"\0"}; char returnString[OMTB_MAX_LEN] = {"\0"};
  FILE *fpResult = NULL;
  MX_Result  result = ERR_NOERR;
  OMTB_CLIENT_PRIVATE* thisClient = NULL;
  char componentRequested[OMX_MAX_STRINGNAME_SIZE] = {"\0"};  
  OMTB_OMX_API_TIMING_VAR_DECL;

  /* Read component name */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, componentRequested);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }
  
  /* Read testcase ID */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, testCaseId);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }
  
  /* Read result filename */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, resultFileName);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }

  /* Read result file type */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, fOpenMode);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }
  
  /* Read instance Number */
  result = XdbgCmdNextNum(pContext, pCmdEntry, ppCmdLine, (UINT32 *)&instance);
  if (ERR_NOERR != result)
  {
    return result;
  }

  /* Open the result file */
  fpResult = fopen(resultFileName, fOpenMode);

  if(NULL == fpResult)
  {
    PRINT(PRINT_ERR_MSG, "%s: Error in result file open\n", __FUNCTION__);
    fprintf(fpResult, "%s : FAIL - Error in result file open\n", testCaseId);
    return ERR_INVNAME;
  }
  
  thisClient =  (OMTB_CLIENT_PRIVATE*)OMTB_GetCompPrivHandle(componentRequested, instance); 

  /* Set the component's OMX_PARAM_PORTDEFINITIONTYPE structure (input) */
  OMTB_SetHeader( thisClient->inPortParams->cmnInParams.pInPortDef,
                  sizeof(OMX_PARAM_PORTDEFINITIONTYPE));

  thisClient->inPortParams->cmnInParams.pInPortDef->nPortIndex = OMTB_H264_VDEC_INPUT_PORT_IDX;
  
  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;
  
  /*Set the inPort Definition*/
  err = OMX_GetConfig( thisClient->omtbPvt.handle,
                          OMX_IndexParamPortDefinition,
                          thisClient->inPortParams->cmnInParams.pInPortDef);
  
  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_GetConfig");

  if(OMX_ErrorTimeout == err)
  {
    strcpy(testCaseResult, "PASS");
    fprintf(fpResult, "%s : %s\n", testCaseId, testCaseResult);
  }
  else
  {
    OMTB_OmxReturnStatusString(err, returnString);
    strcpy(testCaseResult, "FAIL");
    fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
    result = ERR_INVNAME;
  }

  fclose(fpResult);
  return result;
}

/******************************************************************************\
 *      OMTB_OmxGetConfigUnSupportedSettings Function Definition
\******************************************************************************/
/**
 *
 *  @brief    This Function performs OMX_GetConfig API testing.
 *
 *  @param    Pointer to MX_DBG_CMD_CONTEXT_T structure
 *            Pointer to MX_DBG_CMD_Entry_T structure
 *            Character Double Pointer containing the command
 *
 *  @return   ERR_NOERR           successful,
 *            ERR_END_OF_CMD      help was requested,
 *            ERR_INVNAME         otherwise.

 *
 */

MX_Result OMTB_OmxGetConfigUnSupportedSettings(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine)
{
  OMX_ERRORTYPE err = OMX_ErrorNone;
  unsigned int instance = 0;
  char resultFileName[OMTB_MAX_LEN] = {"\0"};
  char fOpenMode[OMTB_MAX_LEN] = {"\0"};
  char testCaseId[OMTB_MAX_LEN] = {"\0"};
  char testCaseResult[OMTB_MAX_LEN] = {"\0"}; char returnString[OMTB_MAX_LEN] = {"\0"};
  FILE *fpResult = NULL;
  MX_Result  result = ERR_NOERR;
  OMTB_CLIENT_PRIVATE* thisClient = NULL;
  char componentRequested[OMX_MAX_STRINGNAME_SIZE] = {"\0"};  
  OMTB_OMX_API_TIMING_VAR_DECL;

  /* Read component name */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, componentRequested);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }
  
  /* Read testcase ID */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, testCaseId);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }
  
  /* Read result filename */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, resultFileName);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }

  /* Read result file type */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, fOpenMode);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }
  
  /* Read instance Number */
  result = XdbgCmdNextNum(pContext, pCmdEntry, ppCmdLine, (UINT32 *)&instance);
  if (ERR_NOERR != result)
  {
    return result;
  }

  /* Open the result file */
  fpResult = fopen(resultFileName, fOpenMode);

  if(NULL == fpResult)
  {
    PRINT(PRINT_ERR_MSG, "%s: Error in result file open\n", __FUNCTION__);
    fprintf(fpResult, "%s : FAIL - Error in result file open\n", testCaseId);
    return ERR_INVNAME;
  }
  
  thisClient =  (OMTB_CLIENT_PRIVATE*)OMTB_GetCompPrivHandle(componentRequested, instance); 

  /* Set the component's OMX_PARAM_PORTDEFINITIONTYPE structure (input) */
  OMTB_SetHeader( thisClient->inPortParams->cmnInParams.pInPortDef,
                  sizeof(OMX_PARAM_PORTDEFINITIONTYPE));

  thisClient->inPortParams->cmnInParams.pInPortDef->nPortIndex = OMTB_H264_VDEC_INPUT_PORT_IDX;
  
  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;
  
  /*Set the inPort Definition*/
  err = OMX_GetConfig( thisClient->omtbPvt.handle,
                          OMX_IndexParamPortDefinition,
                          thisClient->inPortParams->cmnInParams.pInPortDef);
  
  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_GetConfig");

  if(OMX_ErrorUnsupportedSetting == err)
  {
    strcpy(testCaseResult, "PASS");
    fprintf(fpResult, "%s : %s\n", testCaseId, testCaseResult);
  }
  else
  {
    OMTB_OmxReturnStatusString(err, returnString);
    strcpy(testCaseResult, "FAIL");
    fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
    result = ERR_INVNAME;
  }

  fclose(fpResult);
  return result;
}


/******************************************************************************\
 *      OMTB_OmxGetConfigUnSupportedIndex Function Definition
\******************************************************************************/
/**
 *
 *  @brief    This Function performs OMX_GetConfig API testing.
 *
 *  @param    Pointer to MX_DBG_CMD_CONTEXT_T structure
 *            Pointer to MX_DBG_CMD_Entry_T structure
 *            Character Double Pointer containing the command
 *
 *  @return   ERR_NOERR           successful,
 *            ERR_END_OF_CMD      help was requested,
 *            ERR_INVNAME         otherwise.

 *
 */

MX_Result OMTB_OmxGetConfigUnSupportedIndex(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine)
{
  OMX_ERRORTYPE err = OMX_ErrorNone;
  unsigned int instance = 0;
  char resultFileName[OMTB_MAX_LEN] = {"\0"};
  char fOpenMode[OMTB_MAX_LEN] = {"\0"};
  char testCaseId[OMTB_MAX_LEN] = {"\0"};
  char testCaseResult[OMTB_MAX_LEN] = {"\0"}; char returnString[OMTB_MAX_LEN] = {"\0"};
  FILE *fpResult = NULL;
  MX_Result  result = ERR_NOERR;
  OMTB_CLIENT_PRIVATE* thisClient = NULL;
  char componentRequested[OMX_MAX_STRINGNAME_SIZE] = {"\0"};  
  OMTB_OMX_API_TIMING_VAR_DECL;

  /* Read component name */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, componentRequested);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }
  
  /* Read testcase ID */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, testCaseId);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }
  
  /* Read result filename */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, resultFileName);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }

  /* Read result file type */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, fOpenMode);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }
  
  /* Read instance Number */
  result = XdbgCmdNextNum(pContext, pCmdEntry, ppCmdLine, (UINT32 *)&instance);
  if (ERR_NOERR != result)
  {
    return result;
  }

  /* Open the result file */
  fpResult = fopen(resultFileName, fOpenMode);

  if(NULL == fpResult)
  {
    PRINT(PRINT_ERR_MSG, "%s: Error in result file open\n", __FUNCTION__);
    fprintf(fpResult, "%s : FAIL - Error in result file open\n", testCaseId);
    return ERR_INVNAME;
  }
  
  thisClient =  (OMTB_CLIENT_PRIVATE*)OMTB_GetCompPrivHandle(componentRequested, instance); 

  /* Set the component's OMX_PARAM_PORTDEFINITIONTYPE structure (input) */
  OMTB_SetHeader( thisClient->inPortParams->cmnInParams.pInPortDef,
                  sizeof(OMX_PARAM_PORTDEFINITIONTYPE));

  thisClient->inPortParams->cmnInParams.pInPortDef->nPortIndex = OMTB_H264_VDEC_INPUT_PORT_IDX;
  
  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;
  
  /*Set the inPort Definition*/
  err = OMX_GetConfig( thisClient->omtbPvt.handle,
                          OMX_IndexMax,
                          thisClient->inPortParams->cmnInParams.pInPortDef);
  
  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_GetConfig");

  if(OMX_ErrorUnsupportedIndex == err)
  {
    strcpy(testCaseResult, "PASS");
    fprintf(fpResult, "%s : %s\n", testCaseId, testCaseResult);
  }
  else
  {
    OMTB_OmxReturnStatusString(err, returnString);
    strcpy(testCaseResult, "FAIL");
    fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
    result = ERR_INVNAME;
  }

  fclose(fpResult);
  return result;
}


/******************************************************************************\
 *      OMTB_OmxGetConfigWrongPort Function Definition
\******************************************************************************/
/**
 *
 *  @brief    This Function performs OMX_GetConfig API testing.
 *
 *  @param    Pointer to MX_DBG_CMD_CONTEXT_T structure
 *            Pointer to MX_DBG_CMD_Entry_T structure
 *            Character Double Pointer containing the command
 *
 *  @return   ERR_NOERR           successful,
 *            ERR_END_OF_CMD      help was requested,
 *            ERR_INVNAME         otherwise.

 *
 */

MX_Result OMTB_OmxGetConfigWrongPort(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine)
{
  OMX_ERRORTYPE err = OMX_ErrorNone;
  unsigned int instance = 0;
  char resultFileName[OMTB_MAX_LEN] = {"\0"};
  char fOpenMode[OMTB_MAX_LEN] = {"\0"};
  char testCaseId[OMTB_MAX_LEN] = {"\0"};
  char testCaseResult[OMTB_MAX_LEN] = {"\0"}; char returnString[OMTB_MAX_LEN] = {"\0"};
  FILE *fpResult = NULL;
  MX_Result  result = ERR_NOERR;
  OMTB_CLIENT_PRIVATE* thisClient = NULL;
  char componentRequested[OMX_MAX_STRINGNAME_SIZE] = {"\0"};  
  OMTB_OMX_API_TIMING_VAR_DECL;

  /* Read component name */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, componentRequested);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }
  
  /* Read testcase ID */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, testCaseId);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }
  
  /* Read result filename */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, resultFileName);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }

  /* Read result file type */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, fOpenMode);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }
  
  /* Read instance Number */
  result = XdbgCmdNextNum(pContext, pCmdEntry, ppCmdLine, (UINT32 *)&instance);
  if (ERR_NOERR != result)
  {
    return result;
  }

  /* Open the result file */
  fpResult = fopen(resultFileName, fOpenMode);

  if(NULL == fpResult)
  {
    PRINT(PRINT_ERR_MSG, "%s: Error in result file open\n", __FUNCTION__);
    fprintf(fpResult, "%s : FAIL - Error in result file open\n", testCaseId);
    return ERR_INVNAME;
  }
  
  thisClient =  (OMTB_CLIENT_PRIVATE*)OMTB_GetCompPrivHandle(componentRequested, instance); 

  /* Set the component's OMX_PARAM_PORTDEFINITIONTYPE structure (input) */
  OMTB_SetHeader( thisClient->inPortParams->cmnInParams.pInPortDef,
                  sizeof(OMX_PARAM_PORTDEFINITIONTYPE));

  thisClient->inPortParams->cmnInParams.pInPortDef->nPortIndex = OMTB_H264_VDEC_INVALID_PORT_IDX;
  
  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;
  
  /*Set the inPort Definition*/
  err = OMX_GetConfig( thisClient->omtbPvt.handle,
                          OMX_IndexParamPortDefinition,
                          thisClient->inPortParams->cmnInParams.pInPortDef);
  
  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_GetConfig");

  if(OMX_ErrorBadPortIndex == err)
  {
    strcpy(testCaseResult, "PASS");
    fprintf(fpResult, "%s : %s\n", testCaseId, testCaseResult);
  }
  else
  {
    OMTB_OmxReturnStatusString(err, returnString);
    strcpy(testCaseResult, "FAIL");
    fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
    result = ERR_INVNAME;
  }

  fclose(fpResult);
  return result;
}


/******************************************************************************\
 *      OMTB_OmxEmptyThisBufferOnce Function Definition
\******************************************************************************/
/**
 *
 *  @brief    This Function performs OMX_EmptyThisBuffer API testing.
 *
 *  @param    Pointer to MX_DBG_CMD_CONTEXT_T structure
 *            Pointer to MX_DBG_CMD_Entry_T structure
 *            Character Double Pointer containing the command
 *
 *  @return   ERR_NOERR           successful,
 *            ERR_END_OF_CMD      help was requested,
 *            ERR_INVNAME         otherwise.
 *
 */

MX_Result OMTB_OmxEmptyThisBufferOnce(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine)
{
  OMX_ERRORTYPE err = OMX_ErrorNone;
  unsigned int i = 0;
  OMTB_CLIENT_PRIVATE* thisClient = NULL;
  unsigned int instance = 0;
  char resultFileName[OMTB_MAX_LEN] = {"\0"};
  char fOpenMode[OMTB_MAX_LEN] = {"\0"};
  char testCaseId[OMTB_MAX_LEN] = {"\0"};
  char testCaseResult[OMTB_MAX_LEN] = {"\0"}; char returnString[OMTB_MAX_LEN] = {"\0"};
  FILE *fpResult = NULL;
  MX_Result  result = ERR_NOERR;
  OMX_STATETYPE prevState = OMX_StateInvalid;
  char componentRequested[OMX_MAX_STRINGNAME_SIZE] = {"\0"};  
  OMTB_OMX_API_TIMING_VAR_DECL;

  /* Read component name */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, componentRequested);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }
  
  /* Read testcase ID */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, testCaseId);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }
  
  /* Read result filename */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, resultFileName);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }

  /* Read result file type */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, fOpenMode);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }
  
  /* Read instance Number */
  result = XdbgCmdNextNum(pContext, pCmdEntry, ppCmdLine, (UINT32 *)&instance);
  if (ERR_NOERR != result)
  {
    return result;
  }

  /* Open the result file */
  fpResult = fopen(resultFileName, fOpenMode);

  if(NULL == fpResult)
  {
    PRINT(PRINT_ERR_MSG, "%s: Error in result file open\n", __FUNCTION__);
    fprintf(fpResult, "%s : FAIL - Error in result file open\n", testCaseId);
    return ERR_INVNAME;
  }
  
  thisClient =  (OMTB_CLIENT_PRIVATE*)OMTB_GetCompPrivHandle(componentRequested, instance); 
  
  /* validate the function arguments */
  ASSERT(NULL != thisClient);
  
  PRINT(PRINT_FUNCTION_NAME, "Entering <Function , instance #> : <%s , %d>\n",
                              __FUNCTION__, (int)thisClient->omtbPvt.instanceNo);
  
  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;
  
  /* Get the current state of the component */
  err = OMX_GetState(thisClient->omtbPvt.handle, &prevState);

  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_GetState");

  if(OMX_ErrorNone != err)
  {
    OMTB_OmxReturnStatusString(err, returnString);
    fprintf(fpResult, "%s : FAIL - Error in OMX_GetState() OMX ERROR %s\n", testCaseId,returnString);
    fclose(fpResult);
    return ERR_INVNAME;
  }

  if(OMX_StateExecuting != prevState)
  {
    /* API entry time calculation macro */
    OMTB_OMX_API_ENTRY_TIME_CALC;

    /* sending command to component for specified state transition */
    err = OMX_SendCommand(thisClient->omtbPvt.handle, OMX_CommandStateSet, OMX_StateExecuting, NULL);

    /* API exit time calculation macro */
    OMTB_OMX_API_EXIT_TIME_CALC("OMX_SendCommand - OMX_CommandStateSet");

      if(OMX_ErrorNone != err)
    {
      OMTB_OmxReturnStatusString(err, returnString);
      fprintf(fpResult, "%s : FAIL - Error in OMX_SendCommand(OMX_StateExecuting) OMX ERROR %s\n", testCaseId,returnString);
      fclose(fpResult);
      return ERR_INVNAME;
    }
  }
  
  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;

  /* Pass the input buffer to the component */
  err = OMX_EmptyThisBuffer(
                      thisClient->omtbPvt.handle,
                      thisClient->inPortParams->pInBuff[i]);
  
  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_EmptyThisBuffer");

  if(OMX_ErrorNone == err)
  {
    strcpy(testCaseResult, "PASS");
    fprintf(fpResult, "%s : %s\n", testCaseId, testCaseResult);
  }
  else
  {
    OMTB_OmxReturnStatusString(err, returnString);
    strcpy(testCaseResult, "FAIL");
    fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
    result = ERR_INVNAME;
  }

  PRINT(PRINT_FUNCTION_NAME, "Leaving <Function , instance #> : <%s , %d>\n",
                              __FUNCTION__, (int)thisClient->omtbPvt.instanceNo);

  fclose(fpResult);
  return result;
}


/******************************************************************************\
 *      OMTB_OmxEmptyThisBufferNullHandle Function Definition
\******************************************************************************/
/**
 *
 *  @brief    This Function performs OMX_EmptyThisBuffer API testing.
 *
 *  @param    Pointer to MX_DBG_CMD_CONTEXT_T structure
 *            Pointer to MX_DBG_CMD_Entry_T structure
 *            Character Double Pointer containing the command
 *
 *  @return   ERR_NOERR           successful,
 *            ERR_END_OF_CMD      help was requested,
 *            ERR_INVNAME         otherwise.
 *
 */


MX_Result OMTB_OmxEmptyThisBufferNullHandle(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine)
{
  OMX_ERRORTYPE err = OMX_ErrorNone;
  unsigned int i = 0;
  OMTB_CLIENT_PRIVATE* thisClient = NULL;
  unsigned int instance = 0;
  char resultFileName[OMTB_MAX_LEN] = {"\0"};
  char fOpenMode[OMTB_MAX_LEN] = {"\0"};
  char testCaseId[OMTB_MAX_LEN] = {"\0"};
  char testCaseResult[OMTB_MAX_LEN] = {"\0"}; char returnString[OMTB_MAX_LEN] = {"\0"};
  FILE *fpResult = NULL;
  MX_Result  result = ERR_NOERR;
  OMX_STATETYPE prevState = OMX_StateInvalid;
  char componentRequested[OMX_MAX_STRINGNAME_SIZE] = {"\0"};  
  OMTB_OMX_API_TIMING_VAR_DECL;

  /* Read component name */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, componentRequested);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }
  
  /* Read testcase ID */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, testCaseId);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }
  
  /* Read result filename */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, resultFileName);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }

  /* Read result file type */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, fOpenMode);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }
  
  /* Read instance Number */
  result = XdbgCmdNextNum(pContext, pCmdEntry, ppCmdLine, (UINT32 *)&instance);
  if (ERR_NOERR != result)
  {
    return result;
  }

  /* Open the result file */
  fpResult = fopen(resultFileName, fOpenMode);

  if(NULL == fpResult)
  {
    PRINT(PRINT_ERR_MSG, "%s: Error in result file open\n", __FUNCTION__);
    fprintf(fpResult, "%s : FAIL - Error in result file open\n", testCaseId);
    return ERR_INVNAME;
  }
  
  thisClient =  (OMTB_CLIENT_PRIVATE*)OMTB_GetCompPrivHandle(componentRequested, instance); 
  
  /* validate the function arguments */
  ASSERT(NULL != thisClient);
  
  PRINT(PRINT_FUNCTION_NAME, "Entering <Function , instance #> : <%s , %d>\n",
                              __FUNCTION__, (int)thisClient->omtbPvt.instanceNo);
  
  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;
  
  /* Get the current state of the component */
  err = OMX_GetState(thisClient->omtbPvt.handle, &prevState);

  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_GetState");

  if(OMX_ErrorNone != err)
  {
    OMTB_OmxReturnStatusString(err, returnString);
    fprintf(fpResult, "%s : FAIL - Error in OMX_GetState() OMX ERROR %s\n", testCaseId,returnString);
    fclose(fpResult);
    return ERR_INVNAME;
  }

  if(OMX_StateExecuting != prevState)
  {
    /* API entry time calculation macro */
    OMTB_OMX_API_ENTRY_TIME_CALC;

    /* sending command to component for specified state transition */
    err = OMX_SendCommand(thisClient->omtbPvt.handle, OMX_CommandStateSet, OMX_StateExecuting, NULL);

    /* API exit time calculation macro */
    OMTB_OMX_API_EXIT_TIME_CALC("OMX_SendCommand - OMX_CommandStateSet");

      if(OMX_ErrorNone != err)
    {
      OMTB_OmxReturnStatusString(err, returnString);
      fprintf(fpResult, "%s : FAIL - Error in OMX_SendCommand(OMX_StateExecuting) OMX ERROR %s\n", testCaseId,returnString);
      fclose(fpResult);
      return ERR_INVNAME;
    }
  }
  
  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;

  /* Pass the input buffer to the component */
  err = OMX_EmptyThisBuffer(
                      NULL,
                      thisClient->inPortParams->pInBuff[i]);
  
  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_EmptyThisBuffer");

  if(OMX_ErrorBadParameter == err)
  {
    strcpy(testCaseResult, "PASS");
    fprintf(fpResult, "%s : %s\n", testCaseId, testCaseResult);
  }
  else
  {
    OMTB_OmxReturnStatusString(err, returnString);
    strcpy(testCaseResult, "FAIL");
    fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
    result = ERR_INVNAME;
  }

  PRINT(PRINT_FUNCTION_NAME, "Leaving <Function , instance #> : <%s , %d>\n",
                              __FUNCTION__, (int)thisClient->omtbPvt.instanceNo);

  fclose(fpResult);
  return result;
}


/******************************************************************************\
 *      OMTB_OmxEmptyThisBufferTimeOut Function Definition
\******************************************************************************/
/**
 *
 *  @brief    This Function performs OMX_EmptyThisBuffer API testing.
 *
 *  @param    Pointer to MX_DBG_CMD_CONTEXT_T structure
 *            Pointer to MX_DBG_CMD_Entry_T structure
 *            Character Double Pointer containing the command
 *
 *  @return   ERR_NOERR           successful,
 *            ERR_END_OF_CMD      help was requested,
 *            ERR_INVNAME         otherwise.
 *
 */


MX_Result OMTB_OmxEmptyThisBufferTimeOut(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine)
{
  OMX_ERRORTYPE err = OMX_ErrorNone;
  unsigned int i = 0;
  OMTB_CLIENT_PRIVATE* thisClient = NULL;
  unsigned int instance = 0;
  char resultFileName[OMTB_MAX_LEN] = {"\0"};
  char fOpenMode[OMTB_MAX_LEN] = {"\0"};
  char testCaseId[OMTB_MAX_LEN] = {"\0"};
  char testCaseResult[OMTB_MAX_LEN] = {"\0"}; char returnString[OMTB_MAX_LEN] = {"\0"};
  FILE *fpResult = NULL;
  MX_Result  result = ERR_NOERR;
  OMX_STATETYPE prevState = OMX_StateInvalid;
  char componentRequested[OMX_MAX_STRINGNAME_SIZE] = {"\0"};  
  OMTB_OMX_API_TIMING_VAR_DECL;

  /* Read component name */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, componentRequested);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }
  
  /* Read testcase ID */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, testCaseId);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }
  
  /* Read result filename */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, resultFileName);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }

  /* Read result file type */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, fOpenMode);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }
  
  /* Read instance Number */
  result = XdbgCmdNextNum(pContext, pCmdEntry, ppCmdLine, (UINT32 *)&instance);
  if (ERR_NOERR != result)
  {
    return result;
  }

  /* Open the result file */
  fpResult = fopen(resultFileName, fOpenMode);

  if(NULL == fpResult)
  {
    PRINT(PRINT_ERR_MSG, "%s: Error in result file open\n", __FUNCTION__);
    fprintf(fpResult, "%s : FAIL - Error in result file open\n", testCaseId);
    return ERR_INVNAME;
  }
  
  thisClient =  (OMTB_CLIENT_PRIVATE*)OMTB_GetCompPrivHandle(componentRequested, instance); 
  
  /* validate the function arguments */
  ASSERT(NULL != thisClient);
  
  PRINT(PRINT_FUNCTION_NAME, "Entering <Function , instance #> : <%s , %d>\n",
                              __FUNCTION__, (int)thisClient->omtbPvt.instanceNo);
  
  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;
  
  /* Get the current state of the component */
  err = OMX_GetState(thisClient->omtbPvt.handle, &prevState);

  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_GetState");

  if(OMX_ErrorNone != err)
  {
    OMTB_OmxReturnStatusString(err, returnString);
    fprintf(fpResult, "%s : FAIL - Error in OMX_GetState() OMX ERROR %s\n", testCaseId,returnString);
    fclose(fpResult);
    return ERR_INVNAME;
  }

  if(OMX_StateExecuting != prevState)
  {
    /* API entry time calculation macro */
    OMTB_OMX_API_ENTRY_TIME_CALC;

    /* sending command to component for specified state transition */
    err = OMX_SendCommand(thisClient->omtbPvt.handle, OMX_CommandStateSet, OMX_StateExecuting, NULL);

    /* API exit time calculation macro */
    OMTB_OMX_API_EXIT_TIME_CALC("OMX_SendCommand - OMX_CommandStateSet");

      if(OMX_ErrorNone != err)
    {
      OMTB_OmxReturnStatusString(err, returnString);
      fprintf(fpResult, "%s : FAIL - Error in OMX_SendCommand(OMX_StateExecuting) OMX ERROR %s\n", testCaseId,returnString);
      fclose(fpResult);
      return ERR_INVNAME;
    }
  }
  
  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;

  /* Pass the input buffer to the component */
  err = OMX_EmptyThisBuffer(
                      thisClient->omtbPvt.handle,
                      thisClient->inPortParams->pInBuff[i]);
  
  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_EmptyThisBuffer");

  if(OMX_ErrorTimeout == err)
  {
    strcpy(testCaseResult, "PASS");
    fprintf(fpResult, "%s : %s\n", testCaseId, testCaseResult);
  }
  else
  {
    OMTB_OmxReturnStatusString(err, returnString);
    strcpy(testCaseResult, "FAIL");
    fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
    result = ERR_INVNAME;
  }

  PRINT(PRINT_FUNCTION_NAME, "Leaving <Function , instance #> : <%s , %d>\n",
                              __FUNCTION__, (int)thisClient->omtbPvt.instanceNo);

  fclose(fpResult);
  return result;
}

/******************************************************************************\
 *      OMTB_OmxEmptyThisBufferIdleState Function Definition
\******************************************************************************/
/**
 *
 *  @brief    This Function performs OMX_EmptyThisBuffer API testing.
 *
 *  @param    Pointer to MX_DBG_CMD_CONTEXT_T structure
 *            Pointer to MX_DBG_CMD_Entry_T structure
 *            Character Double Pointer containing the command
 *
 *  @return   ERR_NOERR           successful,
 *            ERR_END_OF_CMD      help was requested,
 *            ERR_INVNAME         otherwise.
 *
 */


MX_Result OMTB_OmxEmptyThisBufferIdleState(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine)
{
  OMX_ERRORTYPE err = OMX_ErrorNone;
  unsigned int i = 0;
  OMTB_CLIENT_PRIVATE* thisClient = NULL;
  unsigned int instance = 0;
  char resultFileName[OMTB_MAX_LEN] = {"\0"};
  char fOpenMode[OMTB_MAX_LEN] = {"\0"};
  char testCaseId[OMTB_MAX_LEN] = {"\0"};
  char testCaseResult[OMTB_MAX_LEN] = {"\0"}; char returnString[OMTB_MAX_LEN] = {"\0"};
  FILE *fpResult = NULL;
  MX_Result  result = ERR_NOERR;
  char componentRequested[OMX_MAX_STRINGNAME_SIZE] = {"\0"};  
  OMTB_OMX_API_TIMING_VAR_DECL;

  /* Read component name */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, componentRequested);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }
  
  /* Read testcase ID */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, testCaseId);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }
  
  /* Read result filename */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, resultFileName);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }

  /* Read result file type */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, fOpenMode);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }
  
  /* Read instance Number */
  result = XdbgCmdNextNum(pContext, pCmdEntry, ppCmdLine, (UINT32 *)&instance);
  if (ERR_NOERR != result)
  {
    return result;
  }

  /* Open the result file */
  fpResult = fopen(resultFileName, fOpenMode);

  if(NULL == fpResult)
  {
    PRINT(PRINT_ERR_MSG, "%s: Error in result file open\n", __FUNCTION__);
    fprintf(fpResult, "%s : FAIL - Error in result file open\n", testCaseId);
    return ERR_INVNAME;
  }
  
  thisClient =  (OMTB_CLIENT_PRIVATE*)OMTB_GetCompPrivHandle(componentRequested, instance); 
  
  /* validate the function arguments */
  ASSERT(NULL != thisClient);
  
  PRINT(PRINT_FUNCTION_NAME, "Entering <Function , instance #> : <%s , %d>\n",
                              __FUNCTION__, (int)thisClient->omtbPvt.instanceNo);
  
  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;

  /* Pass the input buffer to the component */
  err = OMX_EmptyThisBuffer(
                      thisClient->omtbPvt.handle,
                      thisClient->inPortParams->pInBuff[i]);
  
  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_EmptyThisBuffer");

  if(OMX_ErrorIncorrectStateOperation == err)
  {
    strcpy(testCaseResult, "PASS");
    fprintf(fpResult, "%s : %s\n", testCaseId, testCaseResult);
  }
  else
  {
    OMTB_OmxReturnStatusString(err, returnString);
    strcpy(testCaseResult, "FAIL");
    fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
    result = ERR_INVNAME;
  }

  PRINT(PRINT_FUNCTION_NAME, "Leaving <Function , instance #> : <%s , %d>\n",
                              __FUNCTION__, (int)thisClient->omtbPvt.instanceNo);

  fclose(fpResult);
  return result;
}


/******************************************************************************\
 *      OMTB_OmxEmptyThisBufferWrongPort Function Definition
\******************************************************************************/
/**
 *
 *  @brief    This Function performs OMX_EmptyThisBuffer API testing.
 *
 *  @param    Pointer to MX_DBG_CMD_CONTEXT_T structure
 *            Pointer to MX_DBG_CMD_Entry_T structure
 *            Character Double Pointer containing the command
 *
 *  @return   ERR_NOERR           successful,
 *            ERR_END_OF_CMD      help was requested,
 *            ERR_INVNAME         otherwise.
 *
 */


MX_Result OMTB_OmxEmptyThisBufferWrongPort(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine)
{
  OMX_ERRORTYPE err = OMX_ErrorNone;
  unsigned int i = 0;
  OMTB_CLIENT_PRIVATE* thisClient = NULL;
  unsigned int instance = 0;
  char resultFileName[OMTB_MAX_LEN] = {"\0"};
  char fOpenMode[OMTB_MAX_LEN] = {"\0"};
  char testCaseId[OMTB_MAX_LEN] = {"\0"};
  char testCaseResult[OMTB_MAX_LEN] = {"\0"}; char returnString[OMTB_MAX_LEN] = {"\0"};
  FILE *fpResult = NULL;
  MX_Result  result = ERR_NOERR;
  OMX_STATETYPE prevState = OMX_StateInvalid;
  char componentRequested[OMX_MAX_STRINGNAME_SIZE] = {"\0"};  
  OMTB_OMX_API_TIMING_VAR_DECL;

  /* Read component name */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, componentRequested);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }
  
  /* Read testcase ID */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, testCaseId);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }
  
  /* Read result filename */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, resultFileName);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }

  /* Read result file type */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, fOpenMode);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }
  
  /* Read instance Number */
  result = XdbgCmdNextNum(pContext, pCmdEntry, ppCmdLine, (UINT32 *)&instance);
  if (ERR_NOERR != result)
  {
    return result;
  }

  /* Open the result file */
  fpResult = fopen(resultFileName, fOpenMode);

  if(NULL == fpResult)
  {
    PRINT(PRINT_ERR_MSG, "%s: Error in result file open\n", __FUNCTION__);
    fprintf(fpResult, "%s : FAIL - Error in result file open\n", testCaseId);
    return ERR_INVNAME;
  }
  
  thisClient =  (OMTB_CLIENT_PRIVATE*)OMTB_GetCompPrivHandle(componentRequested, instance); 
  
  /* validate the function arguments */
  ASSERT(NULL != thisClient);
  
  PRINT(PRINT_FUNCTION_NAME, "Entering <Function , instance #> : <%s , %d>\n",
                              __FUNCTION__, (int)thisClient->omtbPvt.instanceNo);
  
  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;
  
  /* Get the current state of the component */
  err = OMX_GetState(thisClient->omtbPvt.handle, &prevState);

  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_GetState");

  if(OMX_ErrorNone != err)
  {
    OMTB_OmxReturnStatusString(err, returnString);
    fprintf(fpResult, "%s : FAIL - Error in OMX_GetState() OMX ERROR %s\n", testCaseId,returnString);
    fclose(fpResult);
    return ERR_INVNAME;
  }

  if(OMX_StateExecuting != prevState)
  {
    /* API entry time calculation macro */
    OMTB_OMX_API_ENTRY_TIME_CALC;

    /* sending command to component for specified state transition */
    err = OMX_SendCommand(thisClient->omtbPvt.handle, OMX_CommandStateSet, OMX_StateExecuting, NULL);

    /* API exit time calculation macro */
    OMTB_OMX_API_EXIT_TIME_CALC("OMX_SendCommand - OMX_CommandStateSet");

      if(OMX_ErrorNone != err)
    {
      OMTB_OmxReturnStatusString(err, returnString);
      fprintf(fpResult, "%s : FAIL - Error in OMX_SendCommand(OMX_StateExecuting) OMX ERROR %s\n", testCaseId,returnString);
      fclose(fpResult);
      return ERR_INVNAME;
    }
  }

  thisClient->inPortParams->pInBuff[i]->nInputPortIndex = OMTB_H264_VDEC_INVALID_PORT_IDX;
  
  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;

  /* Pass the input buffer to the component */
  err = OMX_EmptyThisBuffer(
                      thisClient->omtbPvt.handle,
                      thisClient->inPortParams->pInBuff[i]);
  
  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_EmptyThisBuffer");

  if(OMX_ErrorBadPortIndex == err)
  {
    strcpy(testCaseResult, "PASS");
    fprintf(fpResult, "%s : %s\n", testCaseId, testCaseResult);
  }
  else
  {
    OMTB_OmxReturnStatusString(err, returnString);
    strcpy(testCaseResult, "FAIL");
    fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
    result = ERR_INVNAME;
  }

  PRINT(PRINT_FUNCTION_NAME, "Leaving <Function , instance #> : <%s , %d>\n",
                              __FUNCTION__, (int)thisClient->omtbPvt.instanceNo);

  fclose(fpResult);
  return result;
}


/******************************************************************************\
 *      OMTB_OmxFillThisBufferOnce Function Definition
\******************************************************************************/
/**
 *
 *  @brief    This Function performs OMX_FillThisBuffer API testing.
 *
 *  @param    Pointer to MX_DBG_CMD_CONTEXT_T structure
 *            Pointer to MX_DBG_CMD_Entry_T structure
 *            Character Double Pointer containing the command
 *
 *  @return   ERR_NOERR           successful,
 *            ERR_END_OF_CMD      help was requested,
 *            ERR_INVNAME         otherwise.
 *
 */


MX_Result OMTB_OmxFillThisBufferOnce(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine)
{
  OMX_ERRORTYPE err = OMX_ErrorNone;
  unsigned int i = 0;
  OMTB_CLIENT_PRIVATE* thisClient = NULL;
  unsigned int instance = 0;
  char resultFileName[OMTB_MAX_LEN] = {"\0"};
  char fOpenMode[OMTB_MAX_LEN] = {"\0"};
  char testCaseId[OMTB_MAX_LEN] = {"\0"};
  char testCaseResult[OMTB_MAX_LEN] = {"\0"}; char returnString[OMTB_MAX_LEN] = {"\0"};
  FILE *fpResult = NULL;
  MX_Result  result = ERR_NOERR;
  OMX_STATETYPE prevState = OMX_StateInvalid;
  char componentRequested[OMX_MAX_STRINGNAME_SIZE] = {"\0"};  
  OMTB_OMX_API_TIMING_VAR_DECL;

  /* Read component name */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, componentRequested);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }
  
  /* Read testcase ID */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, testCaseId);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }
  
  /* Read result filename */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, resultFileName);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }

  /* Read result file type */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, fOpenMode);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }
  
  /* Read instance Number */
  result = XdbgCmdNextNum(pContext, pCmdEntry, ppCmdLine, (UINT32 *)&instance);
  if (ERR_NOERR != result)
  {
    return result;
  }

  /* Open the result file */
  fpResult = fopen(resultFileName, fOpenMode);

  if(NULL == fpResult)
  {
    PRINT(PRINT_ERR_MSG, "%s: Error in result file open\n", __FUNCTION__);
    fprintf(fpResult, "%s : FAIL - Error in result file open\n", testCaseId);
    return ERR_INVNAME;
  }
  
  thisClient =  (OMTB_CLIENT_PRIVATE*)OMTB_GetCompPrivHandle(componentRequested, instance); 
  
  /* validate the function arguments */
  ASSERT(NULL != thisClient);
  
  PRINT(PRINT_FUNCTION_NAME, "Entering <Function , instance #> : <%s , %d>\n",
                              __FUNCTION__, (int)thisClient->omtbPvt.instanceNo);
  
  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;
  
  /* Get the current state of the component */
  err = OMX_GetState(thisClient->omtbPvt.handle, &prevState);

  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_GetState");

  if(OMX_ErrorNone != err)
  {
    OMTB_OmxReturnStatusString(err, returnString);
    fprintf(fpResult, "%s : FAIL - Error in OMX_GetState() OMX ERROR %s\n", testCaseId,returnString);
    fclose(fpResult);
    return ERR_INVNAME;
  }

  if(OMX_StateExecuting != prevState)
  {
    /* API entry time calculation macro */
    OMTB_OMX_API_ENTRY_TIME_CALC;

    /* sending command to component for specified state transition */
    err = OMX_SendCommand(thisClient->omtbPvt.handle, OMX_CommandStateSet, OMX_StateExecuting, NULL);

    /* API exit time calculation macro */
    OMTB_OMX_API_EXIT_TIME_CALC("OMX_SendCommand - OMX_CommandStateSet");

      if(OMX_ErrorNone != err)
    {
      OMTB_OmxReturnStatusString(err, returnString);
      fprintf(fpResult, "%s : FAIL - Error in OMX_SendCommand(OMX_StateExecuting) OMX ERROR %s\n", testCaseId,returnString);
      fclose(fpResult);
      return ERR_INVNAME;
    }
  }
  
  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;

  /* Pass the output buffer to the component */
  err = OMX_FillThisBuffer( 
                    thisClient->omtbPvt.handle,
                    thisClient->outPortParams->pOutBuff[i]);
  
  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_FillThisBuffer");

  if(OMX_ErrorNone == err)
  {
    strcpy(testCaseResult, "PASS");
    fprintf(fpResult, "%s : %s\n", testCaseId, testCaseResult);
  }
  else
  {
    OMTB_OmxReturnStatusString(err, returnString);
    strcpy(testCaseResult, "FAIL");
    fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
    result = ERR_INVNAME;
  }

  PRINT(PRINT_FUNCTION_NAME, "Leaving <Function , instance #> : <%s , %d>\n",
                              __FUNCTION__, (int)thisClient->omtbPvt.instanceNo);

  fclose(fpResult);
  return result;
}


/******************************************************************************\
 *      OMTB_OmxFillThisBufferNullHandle Function Definition
\******************************************************************************/
/**
 *
 *  @brief    This Function performs OMX_FillThisBuffer API testing.
 *
 *  @param    Pointer to MX_DBG_CMD_CONTEXT_T structure
 *            Pointer to MX_DBG_CMD_Entry_T structure
 *            Character Double Pointer containing the command
 *
 *  @return   ERR_NOERR           successful,
 *            ERR_END_OF_CMD      help was requested,
 *            ERR_INVNAME         otherwise.
 *
 */


MX_Result OMTB_OmxFillThisBufferNullHandle(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine)
{
  OMX_ERRORTYPE err = OMX_ErrorNone;
  unsigned int i = 0;
  OMTB_CLIENT_PRIVATE* thisClient = NULL;
  unsigned int instance = 0;
  char resultFileName[OMTB_MAX_LEN] = {"\0"};
  char fOpenMode[OMTB_MAX_LEN] = {"\0"};
  char testCaseId[OMTB_MAX_LEN] = {"\0"};
  char testCaseResult[OMTB_MAX_LEN] = {"\0"}; char returnString[OMTB_MAX_LEN] = {"\0"};
  FILE *fpResult = NULL;
  MX_Result  result = ERR_NOERR;
  OMX_STATETYPE prevState = OMX_StateInvalid;
  char componentRequested[OMX_MAX_STRINGNAME_SIZE] = {"\0"};  
  OMTB_OMX_API_TIMING_VAR_DECL;

  /* Read component name */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, componentRequested);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }
  
  /* Read testcase ID */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, testCaseId);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }
  
  /* Read result filename */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, resultFileName);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }

  /* Read result file type */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, fOpenMode);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }
  
  /* Read instance Number */
  result = XdbgCmdNextNum(pContext, pCmdEntry, ppCmdLine, (UINT32 *)&instance);
  if (ERR_NOERR != result)
  {
    return result;
  }

  /* Open the result file */
  fpResult = fopen(resultFileName, fOpenMode);

  if(NULL == fpResult)
  {
    PRINT(PRINT_ERR_MSG, "%s: Error in result file open\n", __FUNCTION__);
    fprintf(fpResult, "%s : FAIL - Error in result file open\n", testCaseId);
    return ERR_INVNAME;
  }
  
  thisClient =  (OMTB_CLIENT_PRIVATE*)OMTB_GetCompPrivHandle(componentRequested, instance); 
  
  /* validate the function arguments */
  ASSERT(NULL != thisClient);
  
  PRINT(PRINT_FUNCTION_NAME, "Entering <Function , instance #> : <%s , %d>\n",
                              __FUNCTION__, (int)thisClient->omtbPvt.instanceNo);
  
  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;
  
  /* Get the current state of the component */
  err = OMX_GetState(thisClient->omtbPvt.handle, &prevState);

  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_GetState");

  if(OMX_ErrorNone != err)
  {
    OMTB_OmxReturnStatusString(err, returnString);
    fprintf(fpResult, "%s : FAIL - Error in OMX_GetState() OMX ERROR %s\n", testCaseId,returnString);
    fclose(fpResult);
    return ERR_INVNAME;
  }

  if(OMX_StateExecuting != prevState)
  {
    /* API entry time calculation macro */
    OMTB_OMX_API_ENTRY_TIME_CALC;

    /* sending command to component for specified state transition */
    err = OMX_SendCommand(thisClient->omtbPvt.handle, OMX_CommandStateSet, OMX_StateExecuting, NULL);

    /* API exit time calculation macro */
    OMTB_OMX_API_EXIT_TIME_CALC("OMX_SendCommand - OMX_CommandStateSet");

      if(OMX_ErrorNone != err)
    {
      OMTB_OmxReturnStatusString(err, returnString);
      fprintf(fpResult, "%s : FAIL - Error in OMX_SendCommand(OMX_StateExecuting) OMX ERROR %s\n", testCaseId,returnString);
      fclose(fpResult);
      return ERR_INVNAME;
    }
  }
  
  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;

  /* Pass the output buffer to the component */
  err = OMX_FillThisBuffer( 
                    NULL,
                    thisClient->outPortParams->pOutBuff[i]);
  
  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_FillThisBuffer");

  if(OMX_ErrorBadParameter == err)
  {
    strcpy(testCaseResult, "PASS");
    fprintf(fpResult, "%s : %s\n", testCaseId, testCaseResult);
  }
  else
  {
    OMTB_OmxReturnStatusString(err, returnString);
    strcpy(testCaseResult, "FAIL");
    fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
    result = ERR_INVNAME;
  }

  PRINT(PRINT_FUNCTION_NAME, "Leaving <Function , instance #> : <%s , %d>\n",
                              __FUNCTION__, (int)thisClient->omtbPvt.instanceNo);

  fclose(fpResult);
  return result;
}


/******************************************************************************\
 *      OMTB_OmxFillThisBufferTimeOut Function Definition
\******************************************************************************/
/**
 *
 *  @brief    This Function performs OMX_FillThisBuffer API testing.
 *
 *  @param    Pointer to MX_DBG_CMD_CONTEXT_T structure
 *            Pointer to MX_DBG_CMD_Entry_T structure
 *            Character Double Pointer containing the command
 *
 *  @return   ERR_NOERR           successful,
 *            ERR_END_OF_CMD      help was requested,
 *            ERR_INVNAME         otherwise.
 *
 */


MX_Result OMTB_OmxFillThisBufferTimeOut(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine)
{
  OMX_ERRORTYPE err = OMX_ErrorNone;
  unsigned int i = 0;
  OMTB_CLIENT_PRIVATE* thisClient = NULL;
  unsigned int instance = 0;
  char resultFileName[OMTB_MAX_LEN] = {"\0"};
  char fOpenMode[OMTB_MAX_LEN] = {"\0"};
  char testCaseId[OMTB_MAX_LEN] = {"\0"};
  char testCaseResult[OMTB_MAX_LEN] = {"\0"}; char returnString[OMTB_MAX_LEN] = {"\0"};
  FILE *fpResult = NULL;
  MX_Result  result = ERR_NOERR;
  OMX_STATETYPE prevState = OMX_StateInvalid;
  char componentRequested[OMX_MAX_STRINGNAME_SIZE] = {"\0"};  
  OMTB_OMX_API_TIMING_VAR_DECL;

  /* Read component name */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, componentRequested);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }
  
  /* Read testcase ID */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, testCaseId);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }
  
  /* Read result filename */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, resultFileName);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }

  /* Read result file type */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, fOpenMode);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }
  
  /* Read instance Number */
  result = XdbgCmdNextNum(pContext, pCmdEntry, ppCmdLine, (UINT32 *)&instance);
  if (ERR_NOERR != result)
  {
    return result;
  }

  /* Open the result file */
  fpResult = fopen(resultFileName, fOpenMode);

  if(NULL == fpResult)
  {
    PRINT(PRINT_ERR_MSG, "%s: Error in result file open\n", __FUNCTION__);
    fprintf(fpResult, "%s : FAIL - Error in result file open\n", testCaseId);
    return ERR_INVNAME;
  }
  
  thisClient =  (OMTB_CLIENT_PRIVATE*)OMTB_GetCompPrivHandle(componentRequested, instance); 
  
  /* validate the function arguments */
  ASSERT(NULL != thisClient);
  
  PRINT(PRINT_FUNCTION_NAME, "Entering <Function , instance #> : <%s , %d>\n",
                              __FUNCTION__, (int)thisClient->omtbPvt.instanceNo);
  
  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;
  
  /* Get the current state of the component */
  err = OMX_GetState(thisClient->omtbPvt.handle, &prevState);

  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_GetState");

  if(OMX_ErrorNone != err)
  {
    OMTB_OmxReturnStatusString(err, returnString);
    fprintf(fpResult, "%s : FAIL - Error in OMX_GetState() OMX ERROR %s\n", testCaseId,returnString);
    fclose(fpResult);
    return ERR_INVNAME;
  }

  if(OMX_StateExecuting != prevState)
  {
    /* API entry time calculation macro */
    OMTB_OMX_API_ENTRY_TIME_CALC;

    /* sending command to component for specified state transition */
    err = OMX_SendCommand(thisClient->omtbPvt.handle, OMX_CommandStateSet, OMX_StateExecuting, NULL);

    /* API exit time calculation macro */
    OMTB_OMX_API_EXIT_TIME_CALC("OMX_SendCommand - OMX_CommandStateSet");

    if(OMX_ErrorNone != err)
    {
      OMTB_OmxReturnStatusString(err, returnString);
      fprintf(fpResult, "%s : FAIL - Error in OMX_SendCommand(OMX_StateExecuting) OMX ERROR %s\n", testCaseId,returnString);
      fclose(fpResult);
      return ERR_INVNAME;
    }
  }
  
  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;

  /* Pass the output buffer to the component */
  err = OMX_FillThisBuffer( 
                    thisClient->omtbPvt.handle,
                    thisClient->outPortParams->pOutBuff[i]);
  
  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_FillThisBuffer");

  if(OMX_ErrorTimeout == err)
  {
    strcpy(testCaseResult, "PASS");
    fprintf(fpResult, "%s : %s\n", testCaseId, testCaseResult);
  }
  else
  {
    OMTB_OmxReturnStatusString(err, returnString);
    strcpy(testCaseResult, "FAIL");
    fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
    result = ERR_INVNAME;
  }

  PRINT(PRINT_FUNCTION_NAME, "Leaving <Function , instance #> : <%s , %d>\n",
                              __FUNCTION__, (int)thisClient->omtbPvt.instanceNo);

  fclose(fpResult);
  return result;
}


/******************************************************************************\
 *      OMTB_OmxFillThisBufferIdleState Function Definition
\******************************************************************************/
/**
 *
 *  @brief    This Function performs OMX_FillThisBuffer API testing.
 *
 *  @param    Pointer to MX_DBG_CMD_CONTEXT_T structure
 *            Pointer to MX_DBG_CMD_Entry_T structure
 *            Character Double Pointer containing the command
 *
 *  @return   ERR_NOERR           successful,
 *            ERR_END_OF_CMD      help was requested,
 *            ERR_INVNAME         otherwise.
 *
 */


MX_Result OMTB_OmxFillThisBufferIdleState(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine)
{
  OMX_ERRORTYPE err = OMX_ErrorNone;
  unsigned int i = 0;
  OMTB_CLIENT_PRIVATE* thisClient = NULL;
  unsigned int instance = 0;
  char resultFileName[OMTB_MAX_LEN] = {"\0"};
  char fOpenMode[OMTB_MAX_LEN] = {"\0"};
  char testCaseId[OMTB_MAX_LEN] = {"\0"};
  char testCaseResult[OMTB_MAX_LEN] = {"\0"}; char returnString[OMTB_MAX_LEN] = {"\0"};
  FILE *fpResult = NULL;
  MX_Result  result = ERR_NOERR;
  char componentRequested[OMX_MAX_STRINGNAME_SIZE] = {"\0"};  
  OMTB_OMX_API_TIMING_VAR_DECL;

  /* Read component name */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, componentRequested);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }
  
  /* Read testcase ID */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, testCaseId);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }
  
  /* Read result filename */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, resultFileName);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }

  /* Read result file type */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, fOpenMode);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }
  
  /* Read instance Number */
  result = XdbgCmdNextNum(pContext, pCmdEntry, ppCmdLine, (UINT32 *)&instance);
  if (ERR_NOERR != result)
  {
    return result;
  }

  /* Open the result file */
  fpResult = fopen(resultFileName, fOpenMode);

  if(NULL == fpResult)
  {
    PRINT(PRINT_ERR_MSG, "%s: Error in result file open\n", __FUNCTION__);
    fprintf(fpResult, "%s : FAIL - Error in result file open\n", testCaseId);
    return ERR_INVNAME;
  }
  
  thisClient =  (OMTB_CLIENT_PRIVATE*)OMTB_GetCompPrivHandle(componentRequested, instance); 
  
  /* validate the function arguments */
  ASSERT(NULL != thisClient);
  
  PRINT(PRINT_FUNCTION_NAME, "Entering <Function , instance #> : <%s , %d>\n",
                              __FUNCTION__, (int)thisClient->omtbPvt.instanceNo);
  
  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;

  /* Pass the output buffer to the component */
  err = OMX_FillThisBuffer( 
                    thisClient->omtbPvt.handle,
                    thisClient->outPortParams->pOutBuff[i]);
  
  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_FillThisBuffer");

  if(OMX_ErrorIncorrectStateOperation == err)
  {
    strcpy(testCaseResult, "PASS");
    fprintf(fpResult, "%s : %s\n", testCaseId, testCaseResult);
  }
  else
  {
    OMTB_OmxReturnStatusString(err, returnString);
    strcpy(testCaseResult, "FAIL");
    fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
    result = ERR_INVNAME;
  }

  PRINT(PRINT_FUNCTION_NAME, "Leaving <Function , instance #> : <%s , %d>\n",
                              __FUNCTION__, (int)thisClient->omtbPvt.instanceNo);

  fclose(fpResult);
  return result;
}


/******************************************************************************\
 *      OMTB_OmxFillThisBufferWrongPort Function Definition
\******************************************************************************/
/**
 *
 *  @brief    This Function performs OMX_FillThisBuffer API testing.
 *
 *  @param    Pointer to MX_DBG_CMD_CONTEXT_T structure
 *            Pointer to MX_DBG_CMD_Entry_T structure
 *            Character Double Pointer containing the command
 *
 *  @return   ERR_NOERR           successful,
 *            ERR_END_OF_CMD      help was requested,
 *            ERR_INVNAME         otherwise.
 *
 */


MX_Result OMTB_OmxFillThisBufferWrongPort(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine)
{
  OMX_ERRORTYPE err = OMX_ErrorNone;
  unsigned int i = 0;
  OMTB_CLIENT_PRIVATE* thisClient = NULL;
  unsigned int instance = 0;
  char resultFileName[OMTB_MAX_LEN] = {"\0"};
  char fOpenMode[OMTB_MAX_LEN] = {"\0"};
  char testCaseId[OMTB_MAX_LEN] = {"\0"};
  char testCaseResult[OMTB_MAX_LEN] = {"\0"}; char returnString[OMTB_MAX_LEN] = {"\0"};
  FILE *fpResult = NULL;
  MX_Result  result = ERR_NOERR;
  OMX_STATETYPE prevState = OMX_StateInvalid;
  char componentRequested[OMX_MAX_STRINGNAME_SIZE] = {"\0"};  
  OMTB_OMX_API_TIMING_VAR_DECL;

  /* Read component name */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, componentRequested);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }
  
  /* Read testcase ID */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, testCaseId);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }
  
  /* Read result filename */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, resultFileName);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }

  /* Read result file type */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, fOpenMode);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }
  
  /* Read instance Number */
  result = XdbgCmdNextNum(pContext, pCmdEntry, ppCmdLine, (UINT32 *)&instance);
  if (ERR_NOERR != result)
  {
    return result;
  }

  /* Open the result file */
  fpResult = fopen(resultFileName, fOpenMode);

  if(NULL == fpResult)
  {
    PRINT(PRINT_ERR_MSG, "%s: Error in result file open\n", __FUNCTION__);
    fprintf(fpResult, "%s : FAIL - Error in result file open\n", testCaseId);
    return ERR_INVNAME;
  }
  
  thisClient =  (OMTB_CLIENT_PRIVATE*)OMTB_GetCompPrivHandle(componentRequested, instance); 
  
  /* validate the function arguments */
  ASSERT(NULL != thisClient);
  
  PRINT(PRINT_FUNCTION_NAME, "Entering <Function , instance #> : <%s , %d>\n",
                              __FUNCTION__, (int)thisClient->omtbPvt.instanceNo);
  
  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;
  
  /* Get the current state of the component */
  err = OMX_GetState(thisClient->omtbPvt.handle, &prevState);

  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_GetState");

  if(OMX_ErrorNone != err)
  {
    OMTB_OmxReturnStatusString(err, returnString);
    fprintf(fpResult, "%s : FAIL - Error in OMX_GetState() OMX ERROR %s\n", testCaseId,returnString);
    fclose(fpResult);
    return ERR_INVNAME;
  }

  if(OMX_StateExecuting != prevState)
  {
    /* API entry time calculation macro */
    OMTB_OMX_API_ENTRY_TIME_CALC;

    /* sending command to component for specified state transition */
    err = OMX_SendCommand(thisClient->omtbPvt.handle, OMX_CommandStateSet, OMX_StateExecuting, NULL);

    /* API exit time calculation macro */
    OMTB_OMX_API_EXIT_TIME_CALC("OMX_SendCommand - OMX_CommandStateSet");

      if(OMX_ErrorNone != err)
    {
      OMTB_OmxReturnStatusString(err, returnString);
      fprintf(fpResult, "%s : FAIL - Error in OMX_SendCommand(OMX_StateExecuting) OMX ERROR %s\n", testCaseId,returnString);
      fclose(fpResult);
      return ERR_INVNAME;
    }
  }

  thisClient->outPortParams->pOutBuff[i]->nOutputPortIndex = OMTB_H264_VDEC_INVALID_PORT_IDX;
  
  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;

  /* Pass the output buffer to the component */
  err = OMX_FillThisBuffer( 
                    thisClient->omtbPvt.handle,
                    thisClient->outPortParams->pOutBuff[i]);
  
  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_FillThisBuffer");

  if(OMX_ErrorBadPortIndex == err)
  {
    strcpy(testCaseResult, "PASS");
    fprintf(fpResult, "%s : %s\n", testCaseId, testCaseResult);
  }
  else
  {
    OMTB_OmxReturnStatusString(err, returnString);
    strcpy(testCaseResult, "FAIL");
    fprintf(fpResult, "%s : %s OMX ERROR %s\n", testCaseId, testCaseResult,returnString);
    result = ERR_INVNAME;
  }

  PRINT(PRINT_FUNCTION_NAME, "Leaving <Function , instance #> : <%s , %d>\n",
                              __FUNCTION__, (int)thisClient->omtbPvt.instanceNo);

  fclose(fpResult);
  return result;
}
/*----------------------------- end of file ---------------------------------*/
