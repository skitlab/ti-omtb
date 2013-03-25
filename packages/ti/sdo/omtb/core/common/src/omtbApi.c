/*
 * omtbApi.c
 *
 * This file contains function dispatchers for common OMX IL APIs across
 *  the components.
 *
 * Copyright (C) 2010 Texas Instruments Incorporated - http://www.ti.com/
 *
 *
 *  Redistribution and use in source and binary forms, with or without
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
#include "omtbAppInit.h"
#include "omtbApi.h"
#include "omtbClient.h"

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

/******************************************************************************\
 *      Globals
\******************************************************************************/

OMTB_COMP_HANDLE     omtbClass[OMTB_MAX_CLASS];    // OMTB class array

OMTB_DATA_THREAD_ARG funcThreadArg[OMTB_MAX_INS];  // Func/API thread arguments

/* Streaming (I/P and O/P) thread arguments */
OMTB_DATA_THREAD_ARG strmThreadArg[OMTB_MAX_INS];

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
 *      OMTB_StateToStr Function Definition
\******************************************************************************/
/**
 *
 *  @brief   This Function returns the string equivalent for component state.
 *
 *  @param   state - component state
 *
 *  @return  char* - Pointer to state string
 *
 */

char *OMTB_StateToStr(OMX_STATETYPE state)
{

  /* Display the current state of the component */
  switch((int)state)
  {
    case OMX_StateInvalid:
      return("OMX_StateInvalid");

    case OMX_StateLoaded:
      return("OMX_StateLoaded");

    case OMX_StateIdle:
      return("OMX_StateIdle");

    case OMX_StateExecuting:
      return("OMX_StateExecuting");

    case OMX_StatePause:
      return("OMX_StatePause");

    case OMX_StateWaitForResources:
      return("OMX_StateWaitForResources");

    default:
      return("OMX_StateUndefined");

  }

}


/******************************************************************************\
 *      OMTB_GetCompVersion Function Prototype
\******************************************************************************/
/**
 *
 *  @brief    This Functionn invokes OMX_GetComponentVersion API
 *
 *  @param    OMX Handle
 *
 *  @return   OMX_ERRORTYPE - OMX std return/error code
 */

OMX_ERRORTYPE OMTB_GetCompVersion(OMX_HANDLETYPE handle)
{
  OMX_ERRORTYPE err = OMX_ErrorNone;
  char component[OMX_MAX_STRINGNAME_SIZE] = {"\0"};
  OMX_VERSIONTYPE pComponentVersion;
  OMX_VERSIONTYPE pSpecVersion;
  OMX_UUIDTYPE pComponentUUID;
  OMTB_OMX_API_TIMING_VAR_DECL;

  /* validate the function arguments */
  ASSERT(NULL != handle);

  PRINT(PRINT_FUNCTION_NAME, "Entering Function:%s\n", __FUNCTION__);

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

  if(OMX_ErrorNone != err)
  {
    PRINT(PRINT_ERR_MSG, "OMX_GetComponentVersion Resulted an Error");
    OMTB_OmxReturnStatus(err);
    return err;
  }
  else
  {
    OMTB_OmxReturnStatus(err);
    PRINT(PRINT_MUST,"Component Version is:%d.%d.%d\n",
          pComponentVersion.s.nVersionMajor,
          pComponentVersion.s.nVersionMinor,
          pComponentVersion.s.nRevision);
    PRINT(PRINT_MUST,"Spec Version is:%8x\n",
                      (unsigned int)pSpecVersion.nVersion);
  }

  PRINT(PRINT_FUNCTION_NAME, "Leaving Function:%s\n", __FUNCTION__);

  return OMX_ErrorNone;
}


/******************************************************************************\
 *      OMTB_OmxInit Function Definition
\******************************************************************************/
/**
 *
 *  @brief    This Function invokes the OMX_Init API
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
OMTB_OmxInit(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine
)
{
  MX_Result  result = ERR_NOERR;
  OMX_ERRORTYPE omxStatus = OMX_ErrorNone;
  OMTB_OMX_API_TIMING_VAR_DECL;

  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;

  /* OpenMax core initialization */
  omxStatus = OMX_Init ();

 // printf ("You could Connect CCS Now:: Press any key to continue: \n");
 //  getchar();
 usleep(3000 * 1000);
  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_Init");

  OMTB_OmxReturnStatus(omxStatus);
  return (result);
}


/******************************************************************************\
 *      OMTB_OmxGetCompVersion Function Definition
\******************************************************************************/
/**
 *
 *  @brief    This Function parses the command and invokes OMTB_GetCompVersion
 *            API for requested component
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
OMTB_OmxGetCompVersion(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine
)
{
  MX_Result  result = ERR_NOERR;
  char componentRequested[OMX_MAX_STRINGNAME_SIZE] = {"\0"};
  unsigned int instanceNo = 0;
  OMX_HANDLETYPE handle = NULL;

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

  /* Get the compoent handle from instance management structure */
  handle = OMTB_GetCompHandle(componentRequested, instanceNo);

  if(NULL == handle)
  {
    PRINT(PRINT_ERR_MSG, "Invalid parameters - %s component instance \
%d might not be created !!!\n", componentRequested, instanceNo);

    XdbgCmdSyntaxShow(pContext, pCmdEntry);
    return ERR_INVNAME;
  }
  else
  {
    /* Get the component version info */
    result = (MX_Result)OMTB_GetCompVersion(handle);

    if(OMX_ErrorNone != result)
      return ERR_INVNAME;
  }

  return ((MX_Result)ERR_NOERR);
}


/******************************************************************************\
 *      OMTB_OmxSetupTunnel Function Definition
\******************************************************************************/
/**
 *
 *  @brief    This Function will set ups the tunnel between the specified port
 *            of two specified components.
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
OMTB_OmxSetupTunnel(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine
)
{
  MX_Result  result = ERR_NOERR;
  OMX_ERRORTYPE err = OMX_ErrorNone;
  unsigned int instanceNoCompA = 0, instanceNoCompB = 0;
  unsigned int compAPortOut = 0, compBPortIn = 0;
  OMX_HANDLETYPE handleCompOutA = NULL, handleCompInB = NULL;
  char componentRequestedA[OMX_MAX_STRINGNAME_SIZE] = {"\0"};
  char componentRequestedB[OMX_MAX_STRINGNAME_SIZE] = {"\0"};
  OMTB_OMX_API_TIMING_VAR_DECL;

  /* Read first component name */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, componentRequestedA);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }

  /* Read instance number of the first component */
  result = XdbgCmdNextNum(pContext, pCmdEntry, ppCmdLine,
                          (UINT32*)&instanceNoCompA);
  if (ERR_NOERR != result)
  {
    XdbgCmdSyntaxShow(pContext, pCmdEntry);
    return result;
  }
  
  if(OMTB_MAX_INS <= instanceNoCompA)
  {
    /* Invalid instance no */
    PRINT(PRINT_ERR_MSG, 
          "Invalid instance number: %d - Valid range: <0 to %d>\n",
          instanceNoCompA, OMTB_MAX_INS - 1);
    XdbgCmdSyntaxShow(pContext, pCmdEntry);
    return ERR_INVNAME;
  }    

  /* Read output port number of the first component */
  result = XdbgCmdNextNum(pContext, pCmdEntry, ppCmdLine,
                          (UINT32 *)&compAPortOut);
  if (ERR_NOERR != result)
  {
    XdbgCmdSyntaxShow(pContext, pCmdEntry);
    return result;
  }

  if(strcmp(componentRequestedA, "NULL") && strcmp(componentRequestedA, "null"))
  {
  /* Get the compoent handle from instance management structure */
  handleCompOutA = OMTB_GetCompHandle(componentRequestedA, instanceNoCompA);

  if(NULL == handleCompOutA)
  {
    PRINT(PRINT_ERR_MSG, "Invalid parameters - %s component instance \
%d might not be created !!!\n",
    componentRequestedA, instanceNoCompA);

    XdbgCmdSyntaxShow(pContext, pCmdEntry);
    return ERR_INVNAME;
    }
  }

  /* Read second component name */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, componentRequestedB);
  if (ERR_NOERR != result)
  {
    if (result == ERR_INVNAME)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }

  /* Read instance number of the second component */
  result = XdbgCmdNextNum(pContext, pCmdEntry, ppCmdLine,
                          (UINT32*)&instanceNoCompB);
  if (ERR_NOERR != result)
  {
    XdbgCmdSyntaxShow(pContext, pCmdEntry);
    return result;
  }

  if(OMTB_MAX_INS <= instanceNoCompB)
  {
    /* Invalid instance no */
    PRINT(PRINT_ERR_MSG, 
          "Invalid instance number: %d - Valid range: <0 to %d>\n",
          instanceNoCompB, OMTB_MAX_INS - 1);
    XdbgCmdSyntaxShow(pContext, pCmdEntry);
    return ERR_INVNAME;
  } 
  
  /* Read input port number of the second component */
  result = XdbgCmdNextNum(pContext, pCmdEntry, ppCmdLine,
                          (UINT32 *)&compBPortIn);
  if (ERR_NOERR != result)
  {
    XdbgCmdSyntaxShow(pContext, pCmdEntry);
    return result;
  }

  if(strcmp(componentRequestedB, "NULL") && strcmp(componentRequestedB, "null"))
  {
  /* Get the compoent handle from instance management structure */
  handleCompInB = OMTB_GetCompHandle(componentRequestedB, instanceNoCompB);

  if(NULL == componentRequestedB)
  {
    PRINT(PRINT_ERR_MSG, "Invalid parameters - %s component instance \
%d might not be created !!!\n",
    componentRequestedB, instanceNoCompB);

    XdbgCmdSyntaxShow(pContext, pCmdEntry);
    return ERR_INVNAME;
    }
  }

  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;

  /* Setup tunnel between the specified port of two components */
  err = OMX_SetupTunnel(handleCompOutA, compAPortOut,
                        handleCompInB , compBPortIn);

  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_SetupTunnel");

  if(OMX_ErrorNone != err)
  {
    OMTB_OmxReturnStatus(err);
    result = ERR_INVNAME;
  }
  else
  {
    OMTB_OmxReturnStatus(err);
    result = ERR_NOERR;

    PRINT(PRINT_DEBUG_MESSAGE, "Tunnel setup successful \
<component , instance # , port #> ==> <%s , %d , %d> <==> <%s , %d , %d>\n",
    componentRequestedA, instanceNoCompA, compAPortOut,
    componentRequestedB, instanceNoCompB, compBPortIn);
  }

  return result;
}


									 
							   
/******************************************************************************\
 *      OMTB_OmxConnect Function Definition
\******************************************************************************/
/**
 *
 *  @brief    This Function will provide info on connection for SNT(standard non tunneling) between the 
 *            specified port of two specified components.
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
OMTB_OmxConnect(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine
)
{
  MX_Result  result = ERR_NOERR;
  OMX_ERRORTYPE err = OMX_ErrorNone;  
  unsigned int instanceNoCompA = 0, instanceNoCompB = 0;
  unsigned int compAPortOut = 0, compBPortIn = 0;
  OMTB_APP_PRIVATE *handleCompPrivA = NULL, *handleCompPrivB = NULL;
  char componentRequestedA[OMX_MAX_STRINGNAME_SIZE] = {"\0"};
  char componentRequestedB[OMX_MAX_STRINGNAME_SIZE] = {"\0"};
  OMTB_OMX_API_TIMING_VAR_DECL;

  /* Read first component name */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, componentRequestedA);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }

  /* Read instance number of the first component */
  result = XdbgCmdNextNum(pContext, pCmdEntry, ppCmdLine,
                          (UINT32*)&instanceNoCompA);
  if (ERR_NOERR != result)
  {
    XdbgCmdSyntaxShow(pContext, pCmdEntry);
    return result;
  }

  if(OMTB_MAX_INS <= instanceNoCompA)
  {
    /* Invalid instance no */
    PRINT(PRINT_ERR_MSG, 
          "Invalid instance number: %d - Valid range: <0 to %d>\n",
          instanceNoCompA, OMTB_MAX_INS - 1);
    XdbgCmdSyntaxShow(pContext, pCmdEntry);
    return ERR_INVNAME;
  }  
  
  /* Read output port number of the first component */
  result = XdbgCmdNextNum(pContext, pCmdEntry, ppCmdLine,
                          (UINT32 *)&compAPortOut);
  if (ERR_NOERR != result)
  {
    XdbgCmdSyntaxShow(pContext, pCmdEntry);
    return result;
  }

  if(strcmp(componentRequestedA, "NULL") && strcmp(componentRequestedA, "null"))
  {
    /* Get the compoent handle from instance management structure */
    handleCompPrivA = OMTB_GetCompPrivHandle(componentRequestedA, instanceNoCompA);


   if(NULL == handleCompPrivA)
    {
      PRINT(PRINT_ERR_MSG, "Invalid parameters - %s component instance \
%d might not be created !!!\n",
      componentRequestedA, instanceNoCompA);

      XdbgCmdSyntaxShow(pContext, pCmdEntry);
      return ERR_INVNAME;
    }
  }

  /* Read second component name */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, componentRequestedB);
  if (ERR_NOERR != result)
  {
    if (result == ERR_INVNAME)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }

  /* Read instance number of the second component */
  result = XdbgCmdNextNum(pContext, pCmdEntry, ppCmdLine,
                          (UINT32*)&instanceNoCompB);
  if (ERR_NOERR != result)
  {
    XdbgCmdSyntaxShow(pContext, pCmdEntry);
    return result;
  }

  if(OMTB_MAX_INS <= instanceNoCompB)
  {
    /* Invalid instance no */
    PRINT(PRINT_ERR_MSG, 
          "Invalid instance number: %d - Valid range: <0 to %d>\n",
          instanceNoCompB, OMTB_MAX_INS - 1);
    XdbgCmdSyntaxShow(pContext, pCmdEntry);
    return ERR_INVNAME;
  }  
  
  /* Read input port number of the second component */
  result = XdbgCmdNextNum(pContext, pCmdEntry, ppCmdLine,
                          (UINT32 *)&compBPortIn);
  if (ERR_NOERR != result)
  {
    XdbgCmdSyntaxShow(pContext, pCmdEntry);
    return result;
  }

  if(strcmp(componentRequestedB, "NULL") && strcmp(componentRequestedB, "null"))
  {
    /* Get the compoent handle from instance management structure */
    handleCompPrivB = OMTB_GetCompPrivHandle(componentRequestedB, instanceNoCompB);

    if(NULL == componentRequestedB)
    {
      PRINT(PRINT_ERR_MSG, "Invalid parameters - %s component instance \
%d might not be created !!!\n",
      componentRequestedB, instanceNoCompB);

      XdbgCmdSyntaxShow(pContext, pCmdEntry);
      return ERR_INVNAME;
    }
  }

  /* Fill the info of two components */
  err = OMTB_ClientConnectComponents((OMTB_CLIENT_PRIVATE *)handleCompPrivA,  compAPortOut,
                                     (OMTB_CLIENT_PRIVATE *)handleCompPrivB , compBPortIn);

  if(OMX_ErrorNone != err)
  {
    OMTB_OmxReturnStatus(err);
    result = ERR_INVNAME;
  }
  else
  {
    OMTB_OmxReturnStatus(err);
    result = ERR_NOERR;

    PRINT(PRINT_DEBUG_MESSAGE, "Connect successful \
<component , instance # , port #> ==> <%s , %d , %d> <==> <%s , %d , %d>\n",
    componentRequestedA, instanceNoCompA, compAPortOut,
    componentRequestedB, instanceNoCompB, compBPortIn);
  }

  return result;
}

/******************************************************************************\
 *      OMTB_OmxSendCommandPort Function Definition
\******************************************************************************/
/**
 *
 *  @brief    This Function parses the command and invokes OMX_SendCommand
 *            API for requested component and port.
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
OMTB_OmxSendCommandPort(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine
)
{
  MX_Result  result = ERR_NOERR;
  OMX_ERRORTYPE err = OMX_ErrorNone;
  OMX_COMMANDTYPE commandType = OMX_CommandPortEnable;
  unsigned int instanceNo = 0;
  int nParam = 0;
  OMX_PTR pCmdData = NULL;
  OMX_HANDLETYPE handle = NULL;
  char cmdName[OMTB_MAX_LEN] = {'\0'};
  char componentRequested[OMX_MAX_STRINGNAME_SIZE] = {"\0"};
  OMTB_CLIENT_PRIVATE*   thisClient = NULL; 
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

  /* Get the compoent handle from instance management structure */
  handle = OMTB_GetCompHandle(componentRequested, instanceNo);

  if(NULL == handle)
  {
    PRINT(PRINT_ERR_MSG, "Invalid parameters - %s component instance \
%d might not be created !!!\n", componentRequested, instanceNo);

    XdbgCmdSyntaxShow(pContext, pCmdEntry);
    return ERR_INVNAME;
  }

  /* Enable or disable the port of a component */
  /* Read command params */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, cmdName);
  if (ERR_NOERR != result)
  {
    if (result == ERR_INVNAME)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }

  if(0 == strcmp(cmdName, "enable"))
  {
    commandType = OMX_CommandPortEnable;
  }
  else if(0 == strcmp(cmdName, "disable"))
  {
    commandType = OMX_CommandPortDisable;
  }
  else if(0 == strcmp(cmdName, "waitforsem"))
  {
      commandType = (OMX_COMMANDTYPE)OMTB_CommandWaitForSem;
  }
  else
  {
    XdbgCmdSyntaxShow(pContext, pCmdEntry);
    return ERR_INVNAME;
  }

  pCmdData = NULL;

  /* Read port Number */
  result = XdbgCmdNextNum(pContext, pCmdEntry, ppCmdLine, (UINT32 *)&nParam);
  if (ERR_NOERR != result)
  {
    return result;
  }

  if(OMTB_CommandWaitForSem == commandType)
  {
    thisClient =  (OMTB_CLIENT_PRIVATE*)OMTB_GetCompPrivHandle(componentRequested, instanceNo); 

    if(NULL == thisClient)
    {
      PRINT(PRINT_ERR_MSG, "Invalid parameters - %s component instance \
%d might not be created !!!\n", componentRequested, instanceNo);

      XdbgCmdSyntaxShow(pContext, pCmdEntry);
      return ERR_INVNAME;
    }
  
    TIMM_OSAL_SemaphoreObtain(thisClient->omtbPvt.eventSem, TIMM_OSAL_SUSPEND);
    PRINT(PRINT_MUST, "%s: Obtained port enable/disable command completion event: \n",__FUNCTION__);
  }
  else
  {  
    /* API entry time calculation macro */
    OMTB_OMX_API_ENTRY_TIME_CALC;
    /* sending command to component to enable/disable the port */
 
    err = OMX_SendCommand(handle, commandType, nParam, pCmdData);

    /* API exit time calculation macro */
    OMTB_OMX_API_EXIT_TIME_CALC(
              "OMX_SendCommand - OMX_CommandPortEnable/OMX_CommandPortDisable");
  }
  
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
 *      OMTB_OmxSendCommandFlush Function Definition
\******************************************************************************/
/**
 *
 *  @brief    This Function parses the command and invokes OMX_SendCommand
 *            API for requested component and flushes the buffer of particular
 *            port.
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
OMTB_OmxSendCommandFlush(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine
)
{
  MX_Result  result = ERR_NOERR;
  OMX_ERRORTYPE err = OMX_ErrorNone;
  OMX_COMMANDTYPE commandType = OMX_CommandFlush;
  unsigned int instanceNo = 0;
  int nParam = 0;
  OMX_PTR pCmdData = NULL;
  OMX_HANDLETYPE handle = NULL;
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
  
  /* Get the compoent handle from instance management structure */
  handle = OMTB_GetCompHandle(componentRequested, instanceNo);

  if(NULL == handle)
  {
    PRINT(PRINT_ERR_MSG, "Invalid parameters - %s component instance \
%d might not be created !!!\n", componentRequested, instanceNo);

    XdbgCmdSyntaxShow(pContext, pCmdEntry);
    return ERR_INVNAME;
  }

  /* Flush the buufer on specific port of the component */
  /* Read port Number */
  result = XdbgCmdNextNum(pContext, pCmdEntry, ppCmdLine, (UINT32 *)&nParam);
  if (ERR_NOERR != result)
  {
    return result;
  }
  commandType = OMX_CommandFlush;
  pCmdData = NULL;

  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;

  /* sending command to component to flush the buffer on specified port */
  err = OMX_SendCommand(handle, commandType, nParam, pCmdData);

  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_SendCommand - OMX_CommandFlush");

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
 *      OMTB_OmxGetState Function Definition
\******************************************************************************/
/**
 *
 *  @brief    This Function will give the current state of the component.
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
OMTB_OmxGetState(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine
)
{
  MX_Result  result = ERR_NOERR;
  OMX_ERRORTYPE err = OMX_ErrorNone;
  unsigned int instanceNo = 0;
  OMX_HANDLETYPE handle= NULL;
  char componentRequested[OMX_MAX_STRINGNAME_SIZE] = {"\0"};
  char stateStr[OMTB_MAX_LEN] = {"\0"};
  OMX_STATETYPE pState = OMX_StateInvalid;
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

  /* Read instance Number */
  result = XdbgCmdNextNum(pContext, pCmdEntry, ppCmdLine, (UINT32*)&instanceNo);
  if (ERR_NOERR != result)
  {
    XdbgCmdSyntaxShow(pContext, pCmdEntry);
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
  
  /* Get the compoent handle from instance management structure */
  handle = OMTB_GetCompHandle(componentRequested, instanceNo);

  if(NULL == handle)
  {
    PRINT(PRINT_ERR_MSG, "Invalid parameters - %s component instance \
%d might not be created !!!\n", componentRequested, instanceNo);

    XdbgCmdSyntaxShow(pContext, pCmdEntry);
    return ERR_INVNAME;
  }

  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;

  /* Get the current state of the component */
  err = OMX_GetState(handle, &pState);

  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_GetState");

  if(OMX_ErrorNone != err)
  {
    OMTB_OmxReturnStatus(err);
    result = ERR_INVNAME;
  }
  else
  {
    OMTB_OmxReturnStatus(err);
    result = ERR_NOERR;

    /* get equivalent string for the state */
    strcpy(stateStr, OMTB_StateToStr(pState));

    PRINT(PRINT_MUST, "<component, instance , state> ==> <%s, %d , %s>\n",
    componentRequested, instanceNo, stateStr);
  }

  return result;
}


/******************************************************************************\
 *      OMTB_OmxGetExtensionIndex Function Definition
\******************************************************************************/
/**
 *
 *  @brief    This Function translates the vendor specific structure string to
 *            openmax standard structure index.
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
OMTB_OmxGetExtensionIndex(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine
)
{
  MX_Result  result = ERR_NOERR;
  OMX_ERRORTYPE err = OMX_ErrorNone;
  unsigned int instanceNo = 0;
  OMX_HANDLETYPE handle = NULL;
  char componentRequested[OMX_MAX_STRINGNAME_SIZE] = {"\0"};
  char vendorSpecificStr[OMX_MAX_STRINGNAME_SIZE]  = {"\0"};
  void *pAppData = NULL;
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

  /* Read instance Number */
  result = XdbgCmdNextNum(pContext, pCmdEntry, ppCmdLine, (UINT32*)&instanceNo);
  if (ERR_NOERR != result)
  {
    XdbgCmdSyntaxShow(pContext, pCmdEntry);
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

  /* Read vendor specific structure string */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, vendorSpecificStr);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }

  /* Get the compoent handle from instance management structure */
  handle = OMTB_GetCompHandle(componentRequested, instanceNo);

  if(NULL == handle)
  {
    PRINT(PRINT_ERR_MSG, "Invalid parameters - %s component instance \
%d might not be created !!!\n", componentRequested, instanceNo);

    XdbgCmdSyntaxShow(pContext, pCmdEntry);
    return ERR_INVNAME;
  }

  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;

  /* Fet the extension index for the vendor specific structure string */
  err = OMX_GetExtensionIndex(handle, vendorSpecificStr, pAppData);

  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_GetExtensionIndex");

  if(OMX_ErrorNone != err)
  {
    OMTB_OmxReturnStatus(err);
    result = ERR_INVNAME;
  }
  else
  {
    OMTB_OmxReturnStatus(err);
    result = ERR_NOERR;

    PRINT(PRINT_MUST, "GetExtensionIndex for <component, instance #, string>:\
 <%s , %d , %s>\n", componentRequested, instanceNo, vendorSpecificStr);
  }

  return result;
}


/******************************************************************************\
 *      OMTB_OMXComponentNameEnum Function Definition
\******************************************************************************/
/**
 *
 *  @brief    This Function enumerates through all the names of recognized
 *            components in the system to detect all the components in the
 *            system run-time.
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
OMTB_OMXComponentNameEnum(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine
)
{
  char name[OMX_MAX_STRINGNAME_SIZE] = {"\0"};
  int index = 0;
  OMX_ERRORTYPE err = OMX_ErrorNone;
  MX_Result result = ERR_NOERR;
  OMTB_OMX_API_TIMING_VAR_DECL;

  PRINT(PRINT_FUNCTION_NAME, "Entering <function>: <%s>\n", __FUNCTION__);

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
      //OMTB_OmxReturnStatus(err);
      break;
    }
    else
    {
      OMTB_OmxReturnStatus(err);
      result = ERR_INVNAME;
      break;
    }

    index++;
  } // while(OMTB_LOOP)

  PRINT(PRINT_FUNCTION_NAME, "Leaving <function>: <%s>\n", __FUNCTION__);
  return result;
}


/******************************************************************************\
 *      OMTB_OMXRoleEnum Function Definition
\******************************************************************************/
/**
 *
 *  @brief    This Function queries all the roles fulfilled by a given a
 *            component.
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
OMTB_OMXRoleEnum(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine
)
{
  OMX_U32 numOfRoles = 0;
  OMX_U8 **strOfRoles = NULL;
  OMX_ERRORTYPE err = OMX_ErrorNone;
  int index = 0;
  char componentName[OMX_MAX_STRINGNAME_SIZE] = {"\0"};
  MX_Result result = ERR_NOERR;
  OMTB_OMX_API_TIMING_VAR_DECL;

  PRINT(PRINT_FUNCTION_NAME, "Entering <function>: <%s>\n", __FUNCTION__);

  /* Read component name */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, componentName);
  if (ERR_NOERR != result)
  {
    XdbgCmdSyntaxShow(pContext, pCmdEntry);
    return result;
  }

  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;

  /* Get number of roles of component */
  err = OMX_GetRolesOfComponent(componentName, &numOfRoles, NULL);

  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_GetRolesOfComponent");

  if (OMX_ErrorNone != err)
  {
    PRINT(PRINT_ERR_MSG,
        "In %s: Not able to retrieve number of roles of the given component\n",
        __FUNCTION__);
    OMTB_OmxReturnStatus(err);
    result = ERR_INVNAME;
    return result;
  }
  PRINT(PRINT_MUST, "<component , # of roles> : <%s , %i>\n",
                    componentName, (int) numOfRoles);

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
								   
    if(NULL == strOfRoles) 								   
	{
      PRINT(PRINT_ERR_MSG, "Unable to allocate memory\n");	
	  err = OMX_ErrorInsufficientResources;
      OMTB_OmxReturnStatus(err);
      return ERR_INVNAME;	
	}
	
    for (index = 0; index < numOfRoles; index++)
    {
      *(strOfRoles + index) = (OMX_U8*)
                 TIMM_OSAL_Malloc( numOfRoles * OMX_MAX_STRINGNAME_SIZE,
                                   TIMM_OSAL_TRUE,
                                   0,
                                   TIMMOSAL_MEM_SEGMENT_EXT);
								   
      if(NULL == *(strOfRoles + index)) 								   
	  {
        PRINT(PRINT_ERR_MSG, "Unable to allocate memory\n");	
	    err = OMX_ErrorInsufficientResources;
        OMTB_OmxReturnStatus(err);
		
        /* Release the memory allocated for the number of roles of the component */
        for (index = 0; index < numOfRoles; index++)
        {
		  if(NULL != *(strOfRoles + index))
            TIMM_OSAL_Free(*(strOfRoles + index));
        }
        
		if(NULL != strOfRoles)
		  TIMM_OSAL_Free(strOfRoles);		
        
		return ERR_INVNAME;	
	  }								   
    }

    /* API entry time calculation macro */
    OMTB_OMX_API_ENTRY_TIME_CALC;

    /* Get the role string for the component */
    err = OMX_GetRolesOfComponent(componentName, &numOfRoles, strOfRoles);

    /* API exit time calculation macro */
    OMTB_OMX_API_EXIT_TIME_CALC("OMX_GetRolesOfComponent");

    if (OMX_ErrorNone != err)
    {
      PRINT(PRINT_ERR_MSG, "Not able to retrieve the roles of the component\n");
      OMTB_OmxReturnStatus(err);
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
      OMTB_OmxReturnStatus(err);
      result = ERR_INVNAME;
    }

    /* Release the memory allocated for the number of roles of the component */
    for (index = 0; index < numOfRoles; index++)
    {
	  if(NULL != *(strOfRoles + index))
        TIMM_OSAL_Free(*(strOfRoles + index));
    }
        
	if(NULL != strOfRoles)
	  TIMM_OSAL_Free(strOfRoles);	
  }

  PRINT(PRINT_FUNCTION_NAME, "Leaving <function>: <%s>\n", __FUNCTION__);
  return result;
}


/******************************************************************************\
 *      OMTB_OMXComponentEnumByRole Function Definition
\******************************************************************************/
/**
 *
 *  @brief    This Function queries the names of all installed components that
 *            support a given role.
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
OMTB_OMXComponentEnumByRole(
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
  OMTB_OMX_API_TIMING_VAR_DECL;

  PRINT(PRINT_FUNCTION_NAME, "Entering <function>: <%s>\n", __FUNCTION__);

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

  if (OMX_ErrorNone != err)
  {
    PRINT(PRINT_ERR_MSG,
          "Not able to retrieve number of components of a given role\n");
    OMTB_OmxReturnStatus(err);
    result = ERR_INVNAME;
    return result;
  }

  /* allocate the memory to hold name of the component supporting given role */
  strOfCompPerRole = (OMX_U8**)
                     TIMM_OSAL_Malloc( numCompPerRole * sizeof(OMX_STRING),
                                       TIMM_OSAL_TRUE,
                                       0,
                                       TIMMOSAL_MEM_SEGMENT_EXT);
  if(NULL == strOfCompPerRole) 								   
  {	
    PRINT(PRINT_ERR_MSG, "Unable to allocate memory\n");	
	err = OMX_ErrorInsufficientResources;
    OMTB_OmxReturnStatus(err);
    return ERR_INVNAME;	
  }
	
  for (index = 0; index < numCompPerRole; index++)
  {
    strOfCompPerRole[index] = (OMX_U8*)
                      TIMM_OSAL_Malloc( OMX_MAX_STRINGNAME_SIZE,
                                        TIMM_OSAL_TRUE,
                                        0,
                                        TIMMOSAL_MEM_SEGMENT_EXT);
    if(NULL == strOfCompPerRole[index]) 								   
    {	
      PRINT(PRINT_ERR_MSG, "Unable to allocate memory\n");	
	  err = OMX_ErrorInsufficientResources;
      OMTB_OmxReturnStatus(err);
      
	  /* Release the memory allocated for name of he component */
      for (index = 0; index < numCompPerRole; index++)
      {
        if(NULL != strOfCompPerRole[index])
        {
          TIMM_OSAL_Free(strOfCompPerRole[index]);
          strOfCompPerRole[index] = NULL;
        }
      }

      if(NULL != strOfCompPerRole)
      {
        TIMM_OSAL_Free(strOfCompPerRole);
        strOfCompPerRole = NULL;
      }
  
      return ERR_INVNAME;	
    }										
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
    OMTB_OmxReturnStatus(err);
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

  PRINT(PRINT_FUNCTION_NAME, "Leaving <function>: <%s>\n", __FUNCTION__);
  return result;
}


/******************************************************************************\
 *      OMTB_OmxDeinit Function Definition
\******************************************************************************/
/**
 *
 *  @brief    This Function invokes OMX_Deinit API
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
OMTB_OmxDeinit(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine
)
{
  MX_Result  result = ERR_NOERR;
  OMX_ERRORTYPE omxStatus = OMX_ErrorNone;
  OMTB_OMX_API_TIMING_VAR_DECL;

  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;

  /* OpenMax core uninitialization */
  omxStatus = OMX_Deinit ();

  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_Deinit");

  if(OMX_ErrorNone == omxStatus)
  {
    OMTB_OmxReturnStatus(omxStatus);
  }
  else
  {
    OMTB_OmxReturnStatus(omxStatus);
  }

  return (result);
}

/******************************************************************************\
 *      OMTB_OmxSendCommandState Function Definition
\******************************************************************************/
/**
 *
 *  @brief    This Function parses the command and invokes OMX_SendCommand
 *            API for requested component and particular state
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
OMTB_OmxSendCommandState(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine
)
{
  MX_Result  result = ERR_NOERR;
  OMX_ERRORTYPE err = OMX_ErrorNone;
  OMX_COMMANDTYPE commandType = OMX_CommandStateSet;
  unsigned int instanceNo = 0, threadRes = TIMM_OSAL_ERR_NONE;
  OMX_STATETYPE prevState = OMX_StateInvalid;
  OMX_STATETYPE nParam = OMX_StateInvalid;
  OMX_PTR pCmdData = NULL;
  OMX_HANDLETYPE handle = NULL;
  char cmdName[OMTB_MAX_LEN] = {'\0'};
  char componentRequested[OMX_MAX_STRINGNAME_SIZE] = {"\0"};
  TIMM_OSAL_ERRORTYPE bReturnStatus = TIMM_OSAL_ERR_NONE;  
  OMTB_CLIENT_PRIVATE*   thisClient = NULL;  
  OMTB_CLIENT_FILEIO_PARAMS pipeMsg;  
  unsigned int numRemaining  = 0;
  unsigned int actualSize  = 0;
  OMTB_OMX_API_TIMING_VAR_DECL;

  
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

  /* Read instance number of the first component */
  result = XdbgCmdNextNum(pContext, pCmdEntry, ppCmdLine,
                          (UINT32*)&instanceNo);
  if (ERR_NOERR != result)
  {
    XdbgCmdSyntaxShow(pContext, pCmdEntry);
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
  handle = OMTB_GetCompHandle(componentRequested, instanceNo);

  if(NULL == handle)
  {
    PRINT(PRINT_ERR_MSG, "Invalid parameters - %s component instance \
%d might not be created !!!\n", componentRequested, instanceNo);

    XdbgCmdSyntaxShow(pContext, pCmdEntry);
    return ERR_INVNAME;
  }
  
  /* Perform the state transition inside the component */
  commandType = OMX_CommandStateSet;
  pCmdData = NULL;

  /* Read command params */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, cmdName);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
    return result;
  }
  
  if(0 == strcmp(cmdName, "idle"))
  {
    nParam = OMX_StateIdle;
  }
  else if (0 == strcmp(cmdName, "exec"))
  {
    nParam = OMX_StateExecuting;
  }
  else if (0 == strcmp(cmdName, "pause"))
  {
    nParam = OMX_StatePause;
  }
  else if (0 == strcmp(cmdName, "loaded"))
  {
    nParam = OMX_StateLoaded;
  }
  else if (0 == strcmp(cmdName, "waitforresources"))
  {
    nParam = OMX_StateWaitForResources;
  }
  else if (0 == strcmp(cmdName, "waitforsem"))
  {
    nParam = (OMX_STATETYPE)OMTB_CommandWaitForSem;
  }
  else
  {
    XdbgCmdSyntaxShow(pContext, pCmdEntry);
    return ERR_INVNAME;
  }
  
  thisClient =  (OMTB_CLIENT_PRIVATE*)OMTB_GetCompPrivHandle(componentRequested, instanceNo);    

  if(NULL == thisClient)
  {
    PRINT(PRINT_ERR_MSG, "Invalid parameters - %s component instance \
%d might not be created !!!\n", componentRequested, instanceNo);

    XdbgCmdSyntaxShow(pContext, pCmdEntry);
    return ERR_INVNAME;
  }

 
  /*Wait for semaphore, this is not part of OMX Spec, user has been provided
    to wait on semaphore for completion of the state transistion using script*/
  if(OMTB_CommandWaitForSem == nParam)
  {
      prevState = thisClient->omtbPvt.prevState;
#if 0
   if(OMX_StateIdle == prevState && OMX_StateExecuting == thisClient->omtbPvt.currState)
   {
     if(OMTB_VPSS_DC_CLASS == thisClient->omtbPvt.eClassType)
	 {
		  char installHDMISysCmd[(OMX_MAX_STRINGNAME_SIZE + 1)];
		  
		  /* Only 1080p60 configuration supported */
		  //Assert_isTrue((eDcMode == OMX_DC_MODE_1080P_60),Assert_E_assertFailed);
		  snprintf (installHDMISysCmd, OMX_MAX_STRINGNAME_SIZE,
					" insmod TI81xx_hdmi.ko hdmi_mode=%d", 2);
		  installHDMISysCmd[OMX_MAX_STRINGNAME_SIZE] = 0;
		  printf ("\nSystem Cmd to insert HDMI driver:%s", installHDMISysCmd);
		  /* Invoke system command to install HDMI driver */
		  system (installHDMISysCmd);	   
	 }
   }
#endif
  
   /* Perform resource handling for state transitions */
    switch(thisClient->omtbPvt.currState)
    {
      case OMX_StateLoaded:
        if(OMX_TRUE == thisClient->omtbPvt.flagThrCreated)
        {
          /* Exit the input data read thread */
          thisClient->inPortParams->cmnInParams.flagInputEos = OMX_TRUE;
         /*
  		 TIMM_OSAL_SemaphoreRelease(
	         thisClient->inPortParams->cmnInParams.inputDataReady);
        */  			 

          /* Exit the output data write thread */
          thisClient->outPortParams->cmnOutParams.flagEos = OMX_TRUE;
         /*		  
          TIMM_OSAL_SemaphoreRelease(
	      thisClient->outPortParams->cmnOutParams.outputDataReady);
		  */
        } 
#ifdef OMTB_SNT        
		/* release the resources acquire by the component */
        err = OMTB_ClientFreeResources(thisClient);

        if(OMX_ErrorNone != err)
        {
          OMTB_OmxReturnStatus(err);
          return ERR_INVNAME;
        }
#endif //#ifdef OMTB_SNT
       	  bReturnStatus = TIMM_OSAL_SemaphoreObtain(thisClient->omtbPvt.eventSem, OMTB_SEM_TIMEOUT);
	      if(TIMM_OSAL_WAR_TIMEOUT == bReturnStatus)
	      {
            OMTB_OmxReturnStatus(OMX_ErrorTimeout);  
            PRINT(PRINT_ERR_MSG,"TimeOut state transition\n", __FUNCTION__);		
          }
        break;

      case OMX_StateIdle:
        if(OMX_StateLoaded == prevState)
        {
#ifdef OMTB_SNT
          /* Allocate I/O buffers & wait till transition to idle */
          err = OMTB_ClientAllocateResources((OMTB_CLIENT_PRIVATE *)thisClient);

          if(OMX_ErrorNone != err)
          {
            OMTB_OmxReturnStatus(err);
            return ERR_INVNAME;
          }
#endif //#ifdef OMTB_SNT    
       	  bReturnStatus = TIMM_OSAL_SemaphoreObtain(thisClient->omtbPvt.eventSem, OMTB_SEM_TIMEOUT);
	      if(TIMM_OSAL_WAR_TIMEOUT == bReturnStatus)
	      {
            OMTB_OmxReturnStatus(OMX_ErrorTimeout);  
            PRINT(PRINT_ERR_MSG,"TimeOut state transition\n", __FUNCTION__);		
          }
        } // if(OMX_StateLoaded == prevState)
        else if( OMX_StateExecuting == prevState )
        {
#ifdef OMTB_SNT		
            /*Sending exit cmd for all the threads when state transistion exec -> Idle*/
		    if(NULL != thisClient->omtbPvt.connDataStrmThrdId)
			{
			  OMTB_CLIENT_PIPE_MSG pipeMsg;
              pipeMsg.cmd = OMTB_CLIENT_PIPE_CMD_EXIT; 
              pipeMsg.pbufHeader = NULL;
              pipeMsg.bufHeader.pBuffer = NULL;
			  
			  /* send EXIT to connDataStrm thread */
			  TIMM_OSAL_WriteToPipe(thisClient->omtbPvt.localPipe,
                                    &pipeMsg,
                                    sizeof(OMTB_CLIENT_PIPE_MSG),
                                    TIMM_OSAL_SUSPEND);
			}
			
			if(NULL != thisClient->omtbPvt.outDataStrmThrdId)
			{
			  OMX_BUFFERHEADERTYPE* pBufferOut = &thisClient->outPortParams->tempBuff;
			  pBufferOut->nFlags = OMX_BUFFERFLAG_EOS; 	
              
			  TIMM_OSAL_WriteToPipe (thisClient->outPortParams->cmnOutParams.opBufPipe,
                                     &pBufferOut,
                                     sizeof(pBufferOut),
                                     TIMM_OSAL_SUSPEND );			  
			}  
		   
		    if(NULL != thisClient->omtbPvt.inDataStrmThrdId)
			{
			  OMX_BUFFERHEADERTYPE* pBufferIn = &thisClient->inPortParams->tempBuff;
			  pBufferIn->nFlags = OMX_BUFFERFLAG_EOS; 	
              
			  TIMM_OSAL_WriteToPipe (thisClient->inPortParams->cmnInParams.ipBufPipe,
                                     &pBufferIn,
                                     sizeof(pBufferIn),
                                     TIMM_OSAL_SUSPEND );			  
			}			
			
		    while(OMX_TRUE == thisClient->omtbPvt.flagThrCreated)
            {
			  /* loop till the thread is deleted */
			}			
#endif //#ifdef OMTB_SNT			
       	    bReturnStatus = TIMM_OSAL_SemaphoreObtain(thisClient->omtbPvt.eventSem, OMTB_SEM_TIMEOUT);
	        if(TIMM_OSAL_WAR_TIMEOUT == bReturnStatus)
	        {
              OMTB_OmxReturnStatus(OMX_ErrorTimeout);  
              PRINT(PRINT_ERR_MSG,"TimeOut state transition\n", __FUNCTION__);		
            }		
        } // if( OMX_StateExecuting == prevState )
        else if( OMX_StatePause     == prevState  )
		{
		
		}// if( OMX_StatePause     == prevState  )
        break;

      case OMX_StateExecuting:
       	
		bReturnStatus = TIMM_OSAL_SemaphoreObtain(thisClient->omtbPvt.eventSem, OMTB_SEM_TIMEOUT);
	    if(TIMM_OSAL_WAR_TIMEOUT == bReturnStatus)
	    {
          OMTB_OmxReturnStatus(OMX_ErrorTimeout);  
          PRINT(PRINT_ERR_MSG,"TimeOut state transition\n", __FUNCTION__);		
        }	  
#ifdef OMTB_SNT
        /* Do not create the threads for DC and TVP components */  		
		if(OMTB_VPSS_DC_CLASS == thisClient->omtbPvt.eClassType || 
		   OMTB_VPSS_TVP_CLASS == thisClient->omtbPvt.eClassType)
        {		   
		  return ERR_NOERR;
		}
		
        if(OMX_StatePause != prevState)
        {
          /* Reset the file parser */
          if(OMTB_H264_VDEC_CLASS == thisClient->omtbPvt.eClassType)
          {
            if(thisClient->inPortParams->h264ParseCtx.fp != NULL )
            {
              OMTB_H264ResetParser(&(thisClient->inPortParams->h264ParseCtx));
            }  
          }	
		
          if( OMX_FALSE == thisClient->omtbPvt.flagThrCreated)
          {
            /* Create execution thread for API mode */
            threadRes = TIMM_OSAL_CreateTask(
              (void*)&(thisClient->omtbPvt.apiThreadId),
                        (TIMM_OSAL_TaskProc)OMTB_ClientApiTsk,
                        0,
                        thisClient,
                        OMTB_TSK_STACK_SIZE,
                        OMTB_GROUP_PRIORITY,
                        (signed char*)"OMTB_API_TSK");
              PRINT(PRINT_ERR_MSG,
                    "Create OMTB_ClientApiTsk\n");
            if(TIMM_OSAL_ERR_NONE != threadRes)
            {
              PRINT(PRINT_ERR_MSG,
                    "Unable to start omtb api task\n");
              return ERR_INVNAME;
            }
            else
            {
              /* set flag used to determine Func/API thread is created or
                 not */
              thisClient->omtbPvt.flagThrCreated = OMX_TRUE;
            }
          }
          else
          {
              /* do not create the thread in exec -> pause -> exec state */
          } 
        } 
       else
        {
          /* Don't create thread for pause -> exec transition, only perform
             state transition */
        } // if(OMX_StatePause != prevState) ... else ...
#endif //#ifdef OMTB_SNT		
        break;

      case OMX_StatePause:
        /* Nothing to do as of now */
        break;

      case OMX_StateWaitForResources:
        /* Nothing to do as of now */
        break;

      default:
        /* Nothing to do as of now */
        break;
    } // switch(nParam)
	
    return ERR_NOERR;
  }
 
  /*  Move the component to a different state */
  
  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;

  /* Get the current state of the component */
  err = OMX_GetState(handle, &prevState);

  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_GetState");
  if(OMX_ErrorNone != err)
  {
    OMTB_OmxReturnStatus(err);
  }
  else
  {
    thisClient->omtbPvt.prevState = prevState;
  }	

  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;

  /* sending command to component for specified state transition */
  err = OMX_SendCommand(handle, commandType, nParam, pCmdData);

  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_SendCommand - OMX_CommandStateSet");
  if(OMX_ErrorNone != err)
  {
    OMTB_OmxReturnStatus(err);
    return ERR_INVNAME;
  }
  else
  {
    OMTB_OmxReturnStatus(err);
    thisClient->omtbPvt.currState = nParam;	
  }   
 	
  return ERR_NOERR;
}

/******************************************************************************\
 *      OMTB_OmxSetParam Function Definition
\******************************************************************************/
/**
 *
 *  @brief    This Function parses the command and invokes SetParameter
 *            API for requested component
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
OMTB_OmxSetParam(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine
)
{
  MX_Result  result = ERR_NOERR;
  unsigned int template = 0, portIdx = 0;
  unsigned int instanceNo = 0;
  unsigned int i = 0;
  OMX_ERRORTYPE err = OMX_ErrorNone;
  OMX_HANDLETYPE handle = NULL;
  void *pCompCfgStruct = NULL;
  OMX_INDEXTYPE nConfigIndex = OMX_IndexMax;
  char componentRequested[OMX_MAX_STRINGNAME_SIZE] = {"\0"};
  char indexStr[OMX_MAX_STRINGNAME_SIZE] = {"\0"};
  OMTB_CLIENT_PRIVATE*   thisClient = NULL;    
  OMTB_OMX_API_TIMING_VAR_DECL;

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

  /* Read port index Number */
  result = XdbgCmdNextNum(pContext, pCmdEntry, ppCmdLine, (UINT32*)&portIdx);
  if (ERR_NOERR != result)
  {
    return result;
  }

  /* Get the component handle from instance management structure */
  handle = OMTB_GetCompHandle(componentRequested, instanceNo);

  if(NULL == handle)
  {
    PRINT(PRINT_ERR_MSG, "Invalid parameters - %s component instance \
%d might not be created !!!\n", componentRequested, instanceNo);

    XdbgCmdSyntaxShow(pContext, pCmdEntry);
    return ERR_INVNAME;
  }

  /* Read cfg structure index string */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, indexStr);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
     return result;
  }

  thisClient =  (OMTB_CLIENT_PRIVATE*)OMTB_GetCompPrivHandle(componentRequested, instanceNo);   

  if(NULL == thisClient)
  {
    PRINT(PRINT_ERR_MSG, "Invalid parameters - %s component instance \
%d might not be created !!!\n", componentRequested, instanceNo);

    XdbgCmdSyntaxShow(pContext, pCmdEntry);
    return ERR_INVNAME;
  }
	
  /* Get the cfg structure index and pointer */
  err = (OMX_ERRORTYPE)thisClient->omtbPvt.fpGetStructIdx(indexStr,
                                                          template,
														  instanceNo,
                                                          portIdx,
                                                          (unsigned int *)&nConfigIndex,
                                                          &pCompCfgStruct);
  if(OMTB_SUCCESS != err)
  {
    return ERR_INVNAME;
  }
  
  if(OMX_IndexParamDupPorts  == nConfigIndex)
  {
    OMX_PARAM_DUPEPORTSINFO *pDupPortInfo = NULL;

    pDupPortInfo = (OMX_PARAM_DUPEPORTSINFO*)pCompCfgStruct;

    /* Read the # of duped ports */
    result = XdbgCmdNextNum(pContext, pCmdEntry, ppCmdLine,
                            (UINT32 *)&pDupPortInfo->nNumDupedPorts);
    if (ERR_NOERR != result)
    {
      return result;
    }

    /* Read the individual port indexes */
    for(i = 0; i < pDupPortInfo->nNumDupedPorts; i++)
    {
      result = XdbgCmdNextNum(pContext, pCmdEntry, ppCmdLine,
                            (UINT32 *)&pDupPortInfo->auDupedPortsIndex[i]);
      if (ERR_NOERR != result)
      {
        return result;
      }

    } /* for(i = 0; i < sCfgChanGrpInfo->nNumDupedPorts; i++) */
  } /* if(OMX_IndexParamDupPorts == nConfigIndex) */
  
  /* Send the portInit parameter structure */
  if(OMX_TI_IndexParamVFDCCreateMosaicLayout == nConfigIndex)
  {
    OMTB_VPSS_VFDC_CONFIG_PARAMS *vpssVfdcConfig = NULL;
	
    /* Use the specified template structure */
    vpssVfdcConfig = (OMTB_VPSS_VFDC_CONFIG_PARAMS*)
                     &(omtbCfgTemplate[template]->vpssVfdcTemplate);

   	err = VPSSVFDC_SetSymmetricMosaicFormat(handle, pCompCfgStruct,
	                                        vpssVfdcConfig->mosaicDemoConfig);
  }
  else if(OMTB_TI_IndexParamVFDCCreateMosaicLayout == nConfigIndex)
  {
    OMX_VFDC_MultipleWindowFmt *winFmt = NULL;
    OMTB_VPSS_VFDC_MOSAIC_PARAMS *vpssVfdcMosaicParams = NULL;
    OMTB_VPSS_VFDC_CONFIG_PARAMS *vpssVfdcConfig = NULL;
	
	/* Use the specified template structure */
    vpssVfdcConfig = (OMTB_VPSS_VFDC_CONFIG_PARAMS*)
                     &(omtbCfgTemplate[template]->vpssVfdcTemplate);
					 
	vpssVfdcMosaicParams  = &(vpssVfdcConfig->sMosaicParams);
    
    winFmt = &( vpssVfdcMosaicParams->sMosaicLayout.sMosaicWinFmt[vpssVfdcMosaicParams->windowId] );           
    
	winFmt->winStartX = vpssVfdcMosaicParams->winStartX;
    winFmt->winStartY = vpssVfdcMosaicParams->winStartY;
    winFmt->winWidth = vpssVfdcMosaicParams->winWidth;
    winFmt->winHeight = vpssVfdcMosaicParams->winHeight;
	winFmt->pitch[VFDC_YUV_INT_ADDR_IDX] =   vpssVfdcMosaicParams->pitchVFDC_YUV_INT_ADDR_IDX;
	winFmt->pitch[VFDC_YUV_SP_Y_ADDR_IDX] =  vpssVfdcMosaicParams->pitchVFDC_YUV_SP_Y_ADDR_IDX;
	winFmt->pitch[VFDC_YUV_SP_CBCR_ADDR_IDX] = vpssVfdcMosaicParams->pitchVFDC_YUV_SP_CBCR_ADDR_IDX;
    winFmt->dataFormat = vpssVfdcMosaicParams->dataFormat;
    winFmt->bpp = vpssVfdcMosaicParams->bpp;
    winFmt->priority = vpssVfdcMosaicParams->priority;
  }  
  else
  {  
    /* API entry time calculation macro */
    OMTB_OMX_API_ENTRY_TIME_CALC;

    /* Send the portInit parameter structure */
    err = OMX_SetParameter(handle, nConfigIndex, pCompCfgStruct);

    /* API exit time calculation macro */
    OMTB_OMX_API_EXIT_TIME_CALC("OMX_SetParameter");
  
    /* print the values of this index on output console/file */
    OMTB_DisplaySetParams(nConfigIndex, pCompCfgStruct);
  }
  
  if(OMX_ErrorNone != err)
  {
    OMTB_OmxReturnStatus(err);
    result = ERR_INVNAME;
  }
  else
  {
    OMTB_OmxReturnStatus(err);
    result = ERR_NOERR;
  }

  return result;
}


/******************************************************************************\
 *      OMTB_OmxSetConfig Function Definition
\******************************************************************************/
/**
 *
 *  @brief    This Function parses the command and invokes SetConfig
 *            API for requested component
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
OMTB_OmxSetConfig(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine
)
{
  MX_Result  result = ERR_NOERR;
  unsigned int template = 0, portIdx = 0;
  unsigned int instanceNo = 0, i = 0;
  OMX_ERRORTYPE err = OMX_ErrorNone;
  OMX_HANDLETYPE handle = NULL;
  char componentRequested[OMX_MAX_STRINGNAME_SIZE] = {"\0"};
  void *pCompCfgStruct = NULL;
  OMX_INDEXTYPE nConfigIndex = OMX_IndexMax;
  char indexStr[OMX_MAX_STRINGNAME_SIZE] = {"\0"};
  OMTB_CLIENT_PRIVATE*   thisClient = NULL;    
  OMTB_OMX_API_TIMING_VAR_DECL;

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

  /* Read port index Number */
  result = XdbgCmdNextNum(pContext, pCmdEntry, ppCmdLine, (UINT32*)&portIdx);
  if (ERR_NOERR != result)
  {
    return result;
  }

  /* Get the component handle from instance management structure */
  handle = OMTB_GetCompHandle(componentRequested, instanceNo);

  if(NULL == handle)
  {
    PRINT(PRINT_ERR_MSG, "Invalid parameters - %s component instance \
%d might not be created !!!\n", componentRequested, instanceNo);

    XdbgCmdSyntaxShow(pContext, pCmdEntry);
    return ERR_INVNAME;
  }

  /* Read cfg structure index string */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, indexStr);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
     return result;
  }

  thisClient =  (OMTB_CLIENT_PRIVATE*)OMTB_GetCompPrivHandle(componentRequested, instanceNo);   

  if(NULL == thisClient)
  {
    PRINT(PRINT_ERR_MSG, "Invalid parameters - %s component instance \
%d might not be created !!!\n", componentRequested, instanceNo);

    XdbgCmdSyntaxShow(pContext, pCmdEntry);
    return ERR_INVNAME;
  }
  
  /* Get the cfg structure index and pointer */
  err = (OMX_ERRORTYPE)thisClient->omtbPvt.fpGetStructIdx(indexStr,
                                                           template,
														   instanceNo,
                                                           portIdx,
                                                           (unsigned int *)&nConfigIndex,
                                                           &pCompCfgStruct);
  if(OMTB_SUCCESS != err)
  {
    return ERR_INVNAME;
  }

  if(OMX_TI_IndexConfigChannelGroupInfo == nConfigIndex)
  {
    OMX_CONFIG_CHANNELGROUPINFO *sCfgChanGrpInfo = NULL;

    sCfgChanGrpInfo = (OMX_CONFIG_CHANNELGROUPINFO*)pCompCfgStruct;

    /* Read the group name */
    result = XdbgCmdNextVar(pCmdEntry, ppCmdLine,
                            (char *)sCfgChanGrpInfo->cChannelGroupName);
    if (ERR_NOERR != result)
    {
      if (ERR_INVNAME == result)
      {
        XdbgCmdSyntaxShow(pContext, pCmdEntry);
      }
      return result;
    }

    /* Read the # of ports */
    result = XdbgCmdNextNum(pContext, pCmdEntry, ppCmdLine,
                            (UINT32 *)&sCfgChanGrpInfo->nNumPortsInGroup);
    if (ERR_NOERR != result)
    {
      return result;
    }

    /* Read the individual port indexes */
    for(i = 0; i < sCfgChanGrpInfo->nNumPortsInGroup; i++)
    {
      result = XdbgCmdNextNum(pContext, pCmdEntry, ppCmdLine,
                            (UINT32 *)&sCfgChanGrpInfo->auPortGroupIndex[i]);
      if (ERR_NOERR != result)
      {
        return result;
      }

    } /* for(i = 0; i < sCfgChanGrpInfo->nNumPortsInGroup; i++) */

  } /* if(OMX_TI_IndexConfigChannelGroupInfo == nConfigIndex) */

  if(OMX_TI_IndexConfigVFDCMosaicPort2WinMap  == nConfigIndex)
  {
    OMX_CONFIG_VFDC_MOSAICLAYOUT_PORT2WINMAP *pLayoutIndex = NULL;

    pLayoutIndex = (OMX_CONFIG_VFDC_MOSAICLAYOUT_PORT2WINMAP*)pCompCfgStruct;

    /* Read the # of ports */
    result = XdbgCmdNextNum(pContext, pCmdEntry, ppCmdLine,
                            (UINT32 *)&pLayoutIndex->numWindows);
    if (ERR_NOERR != result)
    {
      return result;
    }

    /* Read the individual port indexes */
    for(i = 0; i < pLayoutIndex->numWindows; i++)
    {
      result = XdbgCmdNextNum(pContext, pCmdEntry, ppCmdLine,
                            (UINT32 *)&pLayoutIndex->omxPortList[i]);
      if (ERR_NOERR != result)
      {
        return result;
      }

    } /* for(i = 0; i < pLayoutIndex->numWindows; i++) */
  } /* if(OMX_TI_IndexConfigVFDCMosaicPort2WinMap == nConfigIndex) */

  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;

  /* Send the portInit parameter structure */
  err = OMX_SetConfig(handle, nConfigIndex, pCompCfgStruct);

  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_SetConfig");

   /* print the values of this index on output console/file */
  OMTB_DisplaySetParams(nConfigIndex, pCompCfgStruct);
  
  if(OMX_ErrorNone != err)
  {
    OMTB_OmxReturnStatus(err);
    result = ERR_INVNAME;
  }
  else
  {
    OMTB_OmxReturnStatus(err);
    result = ERR_NOERR;
  }

  return result;
}


/******************************************************************************\
 *      OMTB_OmxGetParam Function Definition
\******************************************************************************/
/**
 *
 *  @brief    This Function parses the command and invokes GetParameter
 *            API for requested component
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
OMTB_OmxGetParam(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine
)
{
  MX_Result  result = ERR_NOERR;
  unsigned int template = 0, portIdx = 0;
  unsigned int instanceNo = 0;
  OMX_ERRORTYPE err = OMX_ErrorNone;
  OMX_HANDLETYPE handle = NULL;
  void *pCompCfgStruct = NULL;
  OMX_INDEXTYPE nConfigIndex = OMX_IndexMax;
  char componentRequested[OMX_MAX_STRINGNAME_SIZE] = {"\0"};
  char indexStr[OMX_MAX_STRINGNAME_SIZE] = {"\0"};
  OMTB_CLIENT_PRIVATE*   thisClient = NULL;    
  OMTB_OMX_API_TIMING_VAR_DECL;

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

  /* Read port index Number */
  result = XdbgCmdNextNum(pContext, pCmdEntry, ppCmdLine, (UINT32*)&portIdx);
  if (ERR_NOERR != result)
  {
    return result;
  }

  /* Get the component handle from instance management structure */
  handle = OMTB_GetCompHandle(componentRequested, instanceNo);

  if(NULL == handle)
  {
    PRINT(PRINT_ERR_MSG, "Invalid parameters - %s component instance \
%d might not be created !!!\n", componentRequested, instanceNo);

    XdbgCmdSyntaxShow(pContext, pCmdEntry);
    return ERR_INVNAME;
  }

  /* Read cfg structure index string */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, indexStr);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
     return result;
  }

  thisClient =  (OMTB_CLIENT_PRIVATE*)OMTB_GetCompPrivHandle(componentRequested, instanceNo);   
  
  if(NULL == thisClient)
  {
    PRINT(PRINT_ERR_MSG, "Invalid parameters - %s component instance \
%d might not be created !!!\n", componentRequested, instanceNo);

    XdbgCmdSyntaxShow(pContext, pCmdEntry);
    return ERR_INVNAME;
  }
  
  /* Get the cfg structure index and pointer */
  err = (OMX_ERRORTYPE)thisClient->omtbPvt.fpGetStructIdx(indexStr,
                                                         template,
														 instanceNo,
                                                         portIdx,
                                                         (unsigned int *)&nConfigIndex,
                                                         &pCompCfgStruct);
  if(OMTB_SUCCESS != err)
  {
    return ERR_INVNAME;
  }

  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;

  /* Send the portInit parameter structure */
  err = OMX_GetParameter(handle, nConfigIndex, pCompCfgStruct);

  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_GetParameter");

  if(OMX_ErrorNone != err)
  {
    OMTB_OmxReturnStatus(err);
    result = ERR_INVNAME;
  }
  else
  {
    /* print the values of this index on output console/file */
    OMTB_DisplayGetParams(nConfigIndex, pCompCfgStruct);
	
    OMTB_OmxReturnStatus(err);
    result = ERR_NOERR;
  }

  return result;
}


/******************************************************************************\
 *      OMTB_OmxGetConfig Function Definition
\******************************************************************************/
/**
 *
 *  @brief    This Function parses the command and invokes GetConfig
 *            API for requested component
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
OMTB_OmxGetConfig(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine
)
{
  MX_Result  result = ERR_NOERR;
  unsigned int template = 0, portIdx = 0;
  unsigned int instanceNo = 0;
  OMX_ERRORTYPE err = OMX_ErrorNone;
  OMX_HANDLETYPE handle = NULL;
  void *pCompCfgStruct = NULL;
  OMX_INDEXTYPE nConfigIndex = OMX_IndexMax;
  char componentRequested[OMX_MAX_STRINGNAME_SIZE] = {"\0"};
  char indexStr[OMX_MAX_STRINGNAME_SIZE] = {"\0"};
  OMTB_CLIENT_PRIVATE*   thisClient = NULL;    
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

  /* Read port index Number */
  result = XdbgCmdNextNum(pContext, pCmdEntry, ppCmdLine, (UINT32*)&portIdx);
  if (ERR_NOERR != result)
  {
    return result;
  }

  /* Get the component handle from instance management structure */
  handle = OMTB_GetCompHandle(componentRequested, instanceNo);

  if(NULL == handle)
  {
    PRINT(PRINT_ERR_MSG, "Invalid parameters - %s component instance \
%d might not be created !!!\n", componentRequested, instanceNo);

    XdbgCmdSyntaxShow(pContext, pCmdEntry);
    return ERR_INVNAME;
  }

  /* Read cfg structure index string */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, indexStr);
  if (ERR_NOERR != result)
  {
    if (ERR_INVNAME == result)
    {
      XdbgCmdSyntaxShow(pContext, pCmdEntry);
    }
     return result;
  }

  thisClient =  (OMTB_CLIENT_PRIVATE*)OMTB_GetCompPrivHandle(componentRequested, instanceNo);   
  
  if(NULL == thisClient)
  {
    PRINT(PRINT_ERR_MSG, "Invalid parameters - %s component instance \
%d might not be created !!!\n", componentRequested, instanceNo);

    XdbgCmdSyntaxShow(pContext, pCmdEntry);
    return ERR_INVNAME;
  }
  
  /* Get the cfg structure index and pointer */
  err = (OMX_ERRORTYPE)thisClient->omtbPvt.fpGetStructIdx(indexStr,
                                                           template,
														   instanceNo,
                                                           portIdx,
                                                           (unsigned int *)&nConfigIndex,
                                                           &pCompCfgStruct);
  if(OMTB_SUCCESS != err)
  {
    return ERR_INVNAME;
  }

  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;

  /* Send the portInit parameter structure */
  err = OMX_GetConfig(handle, nConfigIndex, pCompCfgStruct);

  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_GetConfig");

  if(OMX_ErrorNone != err)
  {
    OMTB_OmxReturnStatus(err);
    result = ERR_INVNAME;
  }
  else
  {
    /* print the values of this index on output console/file */
    OMTB_DisplayGetParams(nConfigIndex, pCompCfgStruct);
	
    OMTB_OmxReturnStatus(err);
    result = ERR_NOERR;
  }

  return result;
}

/******************************************************************************\
 *      OMTB_OmxGetHandle Function Definition
\******************************************************************************/
/**
 *
 *  @brief    This Function invokes OMTB_GetHandle API
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
OMTB_OmxGetHandle(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine
)
{
  MX_Result  result = ERR_NOERR;
  OMX_ERRORTYPE err = OMX_ErrorNone;
  OMX_ERRORTYPE omxStatus = OMX_ErrorNone;
  unsigned int template = 0, instanceNo = 0;
  char componentRequested[OMX_MAX_STRINGNAME_SIZE] = {"\0"};
  OMTB_CLIENT_PRIVATE*   thisClient = NULL;    
  
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
  if(NULL != OMTB_GetCompHandle(componentRequested, instanceNo))
  {
    /* Specified instance already created */
    /* Invalid instance number */
    PRINT(PRINT_ERR_MSG,
          "Instance %d already exist - Valid range: <0 to %d>\n",
          instanceNo, OMTB_MAX_INS - 1);
    return ERR_INVNAME;
  }
  
  omxStatus = OMTB_GetHandle( componentRequested, instanceNo, template);
  
  if(OMX_ErrorNone != omxStatus)
    return ((MX_Result)ERR_INVNAME);
	
  thisClient =  (OMTB_CLIENT_PRIVATE*)OMTB_GetCompPrivHandle(componentRequested, instanceNo);  
  
  if(NULL == thisClient)
  {
    PRINT(PRINT_ERR_MSG, "Invalid parameters - %s component instance \
%d might not be created !!!\n", componentRequested, instanceNo);

    XdbgCmdSyntaxShow(pContext, pCmdEntry);
    return ERR_INVNAME;
  }
  
  PRINT(PRINT_DEBUG_MESSAGE, "Setting all port params\n");
  
  /* Set the port params */
  if(NULL != thisClient->omtbPvt.fpSetPortDefinition)
    err = thisClient->omtbPvt.fpSetPortDefinition((void*)thisClient);

  if(OMX_ErrorNone != err)
  {
    OMTB_OmxReturnStatus(err);
    return ERR_INVNAME;
  }
  
  return ((MX_Result)ERR_NOERR);  
}

/******************************************************************************\
 *      OMTB_ParseCmdTblEntries Function Definition
\******************************************************************************/
/**
 *
 *  @brief    This Function parses the command table entries.
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
OMTB_ParseCmdTblEntries(
  MX_DBG_CMD_CONTEXT_T*       pContext,
  MX_DBG_CMD_ENTRY_T*         pCmdEntry,
  char**                      ppCmdLine
)
{
  MX_Result result = ERR_NOERR;

  /* Remove the unnecessary white spaces */
  result = OMTB_DimtSkipWhiteSpace(pContext, pCmdEntry, ppCmdLine);
  if (ERR_NOERR != result)
  {
    XdbgCmdSyntaxShow(pContext, pCmdEntry);
    return result;
  }

  return XdbgCmdParse(pContext, pCmdEntry, ppCmdLine);
}


/******************************************************************************\
 *      OMTB_OmxFreeHandle Function Definition
\******************************************************************************/
/**
 *
 *  @brief    This Function parses the command and invokes OMX_FreeHandle
 *            API for requested component and particular state
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
OMTB_OmxFreeHandle(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine
)
{
  MX_Result  result = ERR_NOERR;;
  OMX_ERRORTYPE err = OMX_ErrorNone;
  unsigned int instanceNo = 0;
  char componentRequested[OMX_MAX_STRINGNAME_SIZE] = {"\0"};
  OMX_HANDLETYPE handle = NULL;
  OMTB_CLIENT_PRIVATE *thisClient = NULL;   
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
  
  /* Get the compoent handle from instance management structure */
  handle = OMTB_GetCompHandle(componentRequested, instanceNo);

  if(NULL == handle)
  {
    PRINT(PRINT_ERR_MSG, "Invalid parameters - %s component instance \
%d might not be created !!!\n", componentRequested, instanceNo);

    XdbgCmdSyntaxShow(pContext, pCmdEntry);
    return ERR_INVNAME;
  }

  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;

  /* Delete the component instance */
  err = OMX_FreeHandle(handle);

  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_FreeHandle");

  if(OMX_ErrorNone == err)
  {
    OMTB_OmxReturnStatus(err);

    /* Reelase the app pvt data structure memory of the component */
    /* Assign NULL pointer to instance management structure entry */
    thisClient =  (OMTB_CLIENT_PRIVATE*)OMTB_GetCompPrivHandle(componentRequested, instanceNo);    
  
    OMTB_FreeMemory(thisClient);

    handle = NULL;	
    /* set the component handle to NULL */
	OMTB_SetCompHandle(componentRequested, instanceNo, handle); 

    PRINT(PRINT_MUST,
        "\r      \n\nOMTB-Deleted %s Instance #: %d\n\n",
        componentRequested, instanceNo);
  }
  else
  {
    OMTB_OmxReturnStatus(err);
  }
  return (result);
}

/*----------------------------- end of file ---------------------------------*/
