/*
 * omtbVdecApi.c
 *
 * This file contains function dispatchers for component specific OMX IL APIs.
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


/******************************************************************************\
 *      Local Defines
\******************************************************************************/


/******************************************************************************\
 *      Data type definitions
\******************************************************************************/


/******************************************************************************\
 *      Extern Object Definitions
\******************************************************************************/

/* Pointer to OMTB configuration template */
extern OMTB_TEMPLATE_INFO    *omtbCfgTemplate[OMTB_MAX_INS];

/* Pointer to vdec config params */
extern OMTB_VDEC_CONFIG_PARAMS *vdecConfig;

/* Streaming (I/P and O/P) thread arguments */
extern OMTB_DATA_THREAD_ARG strmThreadArg[OMTB_MAX_INS];

/* OMTB class array */
extern OMTB_COMP_HANDLE omtbClass[OMTB_MAX_CLASS];

/* Func/API thread arguments */
extern OMTB_DATA_THREAD_ARG funcThreadArg[OMTB_MAX_INS];

extern OMX_U32 OMTB_CODEC_CHANNEL_G;
/******************************************************************************\
 *      Globals
\******************************************************************************/


/******************************************************************************\
 *      Public Function Prototype
\******************************************************************************/


/******************************************************************************\
 *      Static Globals
\******************************************************************************/


/******************************************************************************\
 *      Private Function Declarations
\******************************************************************************/


/******************************************************************************\
 *      VDEC_GetCompHandle Function Definition
\******************************************************************************/
/**
 *
 *  @brief   This Function returns the component handle based on the component
 *           name and instance number.
 *
 *  @param   componentRequested - Pointer to the requested component name
 *
 *           instanceNo - Component instance number
 *
 *  @return  OMX_HANDLETYPE      component handle,
 *           NULL                otherwise.
 */

OMX_HANDLETYPE          
VDEC_GetCompHandle(
  char *componentRequested,
  unsigned int instanceNo
)
{
  if(!strcmp(componentRequested,OMTB_VDEC_COMP_REF_STR))
  {
    return (omtbClass[OMTB_VDEC_CLASS].handle[instanceNo]);
  }
  else
  {
    PRINT(PRINT_ERR_MSG, "%s component instance %d not created",
                          componentRequested, instanceNo);
    return NULL;
  }
}

/******************************************************************************\
 *      VDEC_OmxSendCommandMark Function Definition
\******************************************************************************/
/**
 *
 *  @brief    This Function parses the command and invokes OMX_SendCommand
 *            API for requested component and marks particular buffer.
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
VDEC_OmxSendCommandMark(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine
)
{
  MX_Result  result = ERR_NOERR;
  OMX_ERRORTYPE err = OMX_ErrorNone;
  OMX_COMMANDTYPE commandType = OMX_CommandMarkBuffer;
  unsigned int instanceNo = 0;
  int nParam = 0;
  OMX_PTR pCmdData = NULL;
  OMX_HANDLETYPE handle = NULL;
  char componentRequested[OMX_MAX_STRINGNAME_SIZE] = {"\0"};
  OMX_MARKTYPE omxMarkType;
  char markComponentName[OMX_MAX_STRINGNAME_SIZE] = {"\0"};
  unsigned int markCompInstanceNo = 0;
  OMTB_OMX_API_TIMING_VAR_DECL;

  /* Read component name */
  strcpy(componentRequested, OMTB_VDEC_COMP_REF_STR);

  /* Read instance Number */
  result = XdbgCmdNextNum(pContext, pCmdEntry, ppCmdLine, (UINT32*)&instanceNo);
  if (ERR_NOERR != result)
  {

    return result;
  }

  if(OMTB_MAX_INS <= instanceNo)
  {
    /* Invalid instance no */
    PRINT(PRINT_ERR_MSG, 
          "Invalid instance number: %d - Valid range: <0 to %d>\n",
          instanceNo, OMTB_MAX_INS - 1);
    XdbgCmdSyntaxShow(pContext, pCmdEntry);
    return ERR_INVNAME;
  } 
  
  /* Get the component handle from instance management structure */
  handle = VDEC_GetCompHandle(componentRequested, instanceNo);

  if(NULL == handle)
  {
    PRINT(PRINT_ERR_MSG, "Invalid parameters - %s component instance \
%d might not be created !!!\n", componentRequested, instanceNo);

    XdbgCmdSyntaxShow(pContext, pCmdEntry);
    return ERR_INVNAME;
  }

  /* Mark a buffer and specify which other component will raise the event */
  /* mark received */

  /* Read component name which will mark the buffer */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, markComponentName);
  if (ERR_NOERR != result)
  {
    if (result == ERR_INVNAME)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }

  /* Read instance Number of component which will mark the buffer */
  result = XdbgCmdNextNum(pContext, pCmdEntry, ppCmdLine,
                          (UINT32 *)&markCompInstanceNo);
  if (ERR_NOERR != result)
  {

    return result;
  }

  if(OMTB_MAX_INS <= markCompInstanceNo)
  {
    /* Invalid instance no */
    PRINT(PRINT_ERR_MSG, 
          "Invalid instance number: %d - Valid range: <0 to %d>\n",
          markCompInstanceNo, OMTB_MAX_INS - 1);
    XdbgCmdSyntaxShow(pContext, pCmdEntry);
    return ERR_INVNAME;
  }
  
  /* Update the mark component and data based on the component specified */
  if(!strcmp(markComponentName, OMTB_VDEC_COMP_REF_STR))
  {
    omxMarkType.hMarkTargetComponent =
        omtbClass[OMTB_VDEC_CLASS].handle[markCompInstanceNo];

    omxMarkType.pMarkData =
        omtbClass[OMTB_VDEC_CLASS].vdecClient[markCompInstanceNo];
  }
  else
  {
    XdbgCmdSyntaxShow(pContext, pCmdEntry);
    return ERR_INVNAME;
  }

  pCmdData = &omxMarkType;
  commandType = OMX_CommandMarkBuffer;

  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;

  /* sending command to component to mark the buffer by specified component */
  err = OMX_SendCommand(handle, commandType, nParam, pCmdData);

  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_SendCommand - OMX_CommandMarkBuffer");

  if(OMX_ErrorNone != err)
  {
    OMTB_OmxReturnStatus(err);
    return ERR_INVNAME;
  }
  else
  {
    OMTB_OmxReturnStatus(err);
    return ERR_NOERR;

  } // if(OMX_ErrorNone != err) ... else ...

}


/******************************************************************************\
 *      VDEC_FuncViddec Function Definition
\******************************************************************************/
/**
 *
 *  @brief    This Function invokes the VDEC_FuncTsk Thread
 *
 *  @param    Pointer to MX_DBG_CMD_CONTEXT_T structure
 *            Pointer to MX_DBG_CMD_Entry_T structure
 *            Character Double Pointer containing the command
 *
 *  @return   ERR_NOERR           successful,
 *            ERR_END_OF_CMD      help was requested,
 *            ERR_INVNAME         otherwise.
 */


MX_Result VDEC_FuncViddec(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine
)
{
  MX_Result result = ERR_NOERR;
  unsigned int template = 0, instanceNo = 0;
  int threadRes = TIMM_OSAL_ERR_NONE;
  char codecType[OMX_MAX_STRINGNAME_SIZE] = {"\0"};

  /* Read the template number */
  result = XdbgCmdNextNum(pContext, pCmdEntry, ppCmdLine, (UINT32 *)&template);
  if (ERR_NOERR != result)
  {
    return result;
  }

  if(OMTB_MAX_TEMPLATE <= template)
  {
    /* Invalid template */
    PRINT(PRINT_ERR_MSG,
          "Invalid template number: %d - Valid range: <0 to %d>\n",
          template, OMTB_MAX_TEMPLATE - 1);
    XdbgCmdSyntaxShow(pContext, pCmdEntry);
    return ERR_INVNAME;
  }

  /* Read the instance number */
  result = XdbgCmdNextNum(pContext, pCmdEntry, ppCmdLine, (UINT32*)&instanceNo);
  if (ERR_NOERR != result)
  {
    return result;
  }

  if(OMTB_MAX_INS <= instanceNo)
  {
    /* Invalid instance no */
    PRINT(PRINT_ERR_MSG, 
          "Invalid instance number: %d - Valid range: <0 to %d>\n",
          instanceNo, OMTB_MAX_INS - 1);
    XdbgCmdSyntaxShow(pContext, pCmdEntry);
    return ERR_INVNAME;
  } 
  
  /* read the codec type */
  strcpy(codecType, OMTB_VDEC_COMP_REF_STR);

  if(!strcmp(codecType, OMTB_VDEC_COMP_REF_STR))
  {
    if(NULL != omtbClass[OMTB_VDEC_CLASS].handle[instanceNo])
    {
      /* Specified instance already created */
      /* Invalid instance number */
      PRINT(PRINT_ERR_MSG,
            "Instance %d already exist - Valid range: <0 to %d>\n",
            instanceNo, OMTB_MAX_INS - 1);
      return ERR_INVNAME;
    }

  /* removed by arun
    vdecConfig = (OMTB_VDEC_CONFIG_PARAMS*)
                          &(omtbCfgTemplate[template]->vdecTemplate);
  */

    /* Create the component instance */
  result = (MX_Result)OMTB_GetHandle(OMTB_VDEC_COMP_REF_STR, instanceNo, template);

    if(OMX_ErrorNone != result)
    {
      PRINT(PRINT_ERR_MSG, "Error in %s instance creation\n", codecType);
      return ((MX_Result)ERR_INVNAME);
    }

    funcThreadArg[instanceNo].vdecClient = (OMTB_VDEC_PRIVATE*)
        omtbClass[OMTB_VDEC_CLASS].vdecClient[instanceNo];

    /* create the execution thread for func mode */
    threadRes = TIMM_OSAL_CreateTask(
              (void*)&omtbClass[OMTB_VDEC_CLASS].execThreadId[instanceNo],
                        (TIMM_OSAL_TaskProc)VDEC_FuncTsk,
                        0,
                        &funcThreadArg[instanceNo],
                        OMTB_VDEC_TSK_STACK_SIZE,
                        OMTB_VDEC_GROUP_PRIORITY,
                        (signed char*)"VDEC_OMX_FUNC_MODE_TSK");

    if(TIMM_OSAL_ERR_NONE != threadRes)
    {
      PRINT(PRINT_ERR_MSG, "Unable to start %s thread\n", codecType);
    }
    else
    {
      /* set flag used to determine Func/API thread is created or not */
      ((OMTB_VDEC_PRIVATE*)\
      (omtbClass[OMTB_VDEC_CLASS].vdecClient[\
            instanceNo]))->omtbPvt.flagThrCreated = OMX_TRUE;
    }

  }
  else
  {
    XdbgCmdSyntaxShow(pContext, pCmdEntry);
    PRINT(PRINT_ERR_MSG, "Wrong video decoder type selected\n");
    return ERR_INVNAME;
  }

  return ERR_NOERR;
}


/*----------------------------- end of file ---------------------------------*/
