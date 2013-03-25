/*
 * omtbAlsaPlayApi.c
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

/* Pointer to VPSS ALSAPLAY config params */
extern OMTB_ALSAPLAY_CONFIG_PARAMS *alsaPlayConfig;

/* OMTB class array */
extern OMTB_COMP_HANDLE omtbClass[OMTB_MAX_CLASS];


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
 *      ALSAPLAY_GetCompHandle Function Definition
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

OMX_HANDLETYPE ALSAPLAY_GetCompHandle(
  char *componentRequested,
  unsigned int instanceNo
)
{
  if(!strcmp(componentRequested,OMTB_ALSAPLAY_COMP_REF_STR))
  {
    return (omtbClass[OMTB_ALSAPLAY_CLASS].handle[instanceNo]);
  }
  else
  {
    PRINT(PRINT_ERR_MSG, "%s component instance %d not created",
                          componentRequested, instanceNo);
    return NULL;
  }
}


/******************************************************************************\
 *      ALSAPLAY_Func Function Definition
\******************************************************************************/
/**
 *
 *  @brief    This Function invokes ALSAPLAY_Func API
 *
 *  @param    Pointer to MX_DBG_CMD_CONTEXT_T structure
 *            Pointer to MX_DBG_CMD_Entry_T structure
 *            Character Double Pointer containing the command
 *
 *  @return   ERR_NOERR           successful,
 *            ERR_END_OF_CMD      help was requested,
 *            ERR_INVNAME         otherwise.
 */

MX_Result ALSAPLAY_Func(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine
)
{
  MX_Result  result = ERR_NOERR;
  OMX_ERRORTYPE omxStatus = OMX_ErrorNone;
  unsigned int template = 0, instanceNo = 0, threadRes = 0;
  char componentRequested[OMX_MAX_STRINGNAME_SIZE] = {"\0"};

  PRINT(PRINT_FUNCTION_NAME, "Entering <Function> : <%s>\n", __FUNCTION__);  
	
  /* Read component type */
  strcpy(componentRequested, OMTB_ALSAPLAY_COMP_REF_STR);

  /* Read instance number */
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
  
  /* Read Template Number */
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

  /* Invoke appropriate components's GetHandle function */
  if(!strcmp(componentRequested, OMTB_ALSAPLAY_COMP_REF_STR))
  {
    if(NULL != omtbClass[OMTB_ALSAPLAY_CLASS].handle[instanceNo])
    {
      /* Specified instance already created */
      /* Invalid instance number */
      PRINT(PRINT_ERR_MSG,
            "Instance %d already exist - Valid range: <0 to %d>\n",
            instanceNo, OMTB_MAX_INS - 1);
      return ERR_INVNAME;
    }

	alsaPlayConfig = (OMTB_ALSAPLAY_CONFIG_PARAMS*)
                     &(omtbCfgTemplate[template]->alsaPlayTemplate);
					 
    omxStatus = ALSAPLAY_GetHandle( &omtbClass[OMTB_ALSAPLAY_CLASS],
                                    instanceNo);
    
	if(OMX_ErrorNone != omxStatus)
      return ((MX_Result)ERR_INVNAME);									
									
  /* create the execution thread for func mode */
    threadRes = TIMM_OSAL_CreateTask(
              (void*)&omtbClass[OMTB_ALSAPLAY_CLASS].execThreadId[instanceNo],
                        (TIMM_OSAL_TaskProc)ALSAPLAY_FuncTsk,
                        0,
                        omtbClass[OMTB_ALSAPLAY_CLASS].alsaPlayClient[instanceNo],
                        OMTB_ALSAPLAY_TSK_STACK_SIZE,
                        OMTB_ALSAPLAY_GROUP_PRIORITY,
                        (signed char*)"ALSAPLAY_OMX_FUNC_MODE_TSK");

    if(TIMM_OSAL_ERR_NONE != threadRes)
    {
      PRINT(PRINT_ERR_MSG, "Unable to create thread\n");
    }									

  }
  else
  {
    XdbgCmdSyntaxShow(pContext, pCmdEntry);
    return ERR_INVNAME;
  }
  
  /* Wait for completion of Audio processing */
  //FIXME: Add a semaphore wait   

  /* Free the resources */
  //ALSAPLAY_FreeHandle(omtbClass[OMTB_ALSAPLAY_CLASS].alsaPlayClient[instanceNo]);
  
  PRINT(PRINT_FUNCTION_NAME, "Leaving <Function> : <%s>\n", __FUNCTION__);
  
  return ((MX_Result)ERR_NOERR);
}
/*----------------------------- end of file ---------------------------------*/
