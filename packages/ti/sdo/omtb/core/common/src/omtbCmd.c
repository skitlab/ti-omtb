/*
 * omtbCmd.c
 *
 * This file is mainly responsible for second level command parsing and
 * utility command handling.
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
#include <ctype.h>
#include <string.h>

/* OMX standard header files */
#include "OMX_Component.h"
#include "OMX_Types.h"


/******************************************************************************\
 *      Customized Includes
\******************************************************************************/

#include "omtbDebug.h"
#include "timm_osal_interfaces.h"
#include "mxDbg.h"
#include "omtbCommon.h"
#include "omtbCmd.h"
#include "omtbTemplateManager.h"


/******************************************************************************\
 *      Local Defines
\******************************************************************************/

#define IS_LINE_END(c) (((c) == '\0') || ((c) == '\r') || ((c) == '\n'))


/******************************************************************************\
 *      Data type definitions
\******************************************************************************/


/******************************************************************************\
 *      Extern Object Definitions 
\******************************************************************************/

extern MX_DBG_CMD_MODE_T  mx_dbg_cmd_mode;  // parser debug mode

extern OMTB_TEMPLATE_INFO *omtbCfgTemplate[OMTB_MAX_INS];  // Template params

extern unsigned int armCpuLoadDispFlag; // Arm CPU load display On/Off flag

extern int globDebugDisable;            // Flag to toggle component log display

extern OMTB_DATA_THREAD_ARG funcThreadArg[OMTB_MAX_INS]; // Func/API thread args

extern MX_DBG_CMD_ENTRY_T cmdEntryOmx;     // command entry for omx command

extern MX_DBG_CMD_TABLE_T cmdTblOmx;       // command table for omx command

/* Buffer to store the commands */
extern char gInputCmd[4096][512];

/* Flag to check if the command had to be copied or not */
extern unsigned int gCopyCommand;

/* No of valid command in the buffer */
extern int gCmdCount;

/* no of iterations the commands should execute */
extern int gLoopCount;
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
 *      OMTB_OmxReturnStatus Function Definition
\******************************************************************************/
/**
 *
 *  @brief    This Function prints the proper error code for OMX API return
 *            values
 *
 *  @param    Retruns status from OMX API's
 *
 *  @return   None
 *
 */

void OMTB_OmxReturnStatus(
  OMX_ERRORTYPE  status
)
{
  switch(status)
  {
    case OMX_ErrorNone:
        PRINT( PRINT_ERR_MSG, "OMX_ErrorNone\n");
        break;
    case OMX_ErrorInsufficientResources:
        PRINT( PRINT_ERR_MSG, "FAIL: OMX_ErrorInsufficientResources\n");
        break;
    case OMX_ErrorUndefined:
        PRINT( PRINT_ERR_MSG, "FAIL: OMX_ErrorUndefined\n");
        break;
    case OMX_ErrorInvalidComponentName:
        PRINT( PRINT_ERR_MSG, "FAIL: OMX_ErrorInvalidComponentName\n");
        break;
    case OMX_ErrorComponentNotFound:
        PRINT( PRINT_ERR_MSG, "FAIL: OMX_ErrorComponentNotFound\n");
        break;
    case OMX_ErrorInvalidComponent:
        PRINT( PRINT_ERR_MSG, "FAIL: OMX_ErrorInvalidComponent\n");
        break;
    case OMX_ErrorBadParameter:
        PRINT( PRINT_ERR_MSG, "FAIL: OMX_ErrorBadParameter\n");
        break;
    case OMX_ErrorNotImplemented:
        PRINT( PRINT_ERR_MSG, "FAIL: OMX_ErrorNotImplemented\n");
        break;
    case OMX_ErrorUnderflow:
        PRINT( PRINT_ERR_MSG, "FAIL: OMX_ErrorUnderflow\n");
        break;
    case OMX_ErrorOverflow:
        PRINT( PRINT_ERR_MSG, "FAIL: OMX_ErrorOverflow\n");
        break;
    case OMX_ErrorHardware:
        PRINT( PRINT_ERR_MSG, "FAIL: OMX_ErrorHardware\n");
        break;
    case OMX_ErrorInvalidState:
        PRINT( PRINT_ERR_MSG, "FAIL: OMX_ErrorInvalidState\n");
        break;
    case OMX_ErrorStreamCorrupt:
        PRINT( PRINT_ERR_MSG, "FAIL: OMX_ErrorStreamCorrupt\n");
        break;
    case OMX_ErrorPortsNotCompatible:
        PRINT( PRINT_ERR_MSG, "FAIL: OMX_ErrorPortsNotCompatible\n");
        break;
    case OMX_ErrorResourcesLost:
        PRINT( PRINT_ERR_MSG, "FAIL: OMX_ErrorResourcesLost\n");
        break;
    case OMX_ErrorNoMore:
        PRINT( PRINT_ERR_MSG, "FAIL: OMX_ErrorNoMore\n");
        break;
    case OMX_ErrorVersionMismatch:
        PRINT( PRINT_ERR_MSG, "FAIL: OMX_ErrorVersionMismatch\n");
        break;
    case OMX_ErrorNotReady:
        PRINT( PRINT_ERR_MSG, "FAIL: OMX_ErrorNotReady\n");
        break;
    case OMX_ErrorTimeout:
        PRINT( PRINT_ERR_MSG, "FAIL: OMX_ErrorTimeout\n");
        break;
    case OMX_ErrorSameState:
        PRINT( PRINT_ERR_MSG, "FAIL: OMX_ErrorSameState\n");
        break;
    case OMX_ErrorResourcesPreempted:
        PRINT( PRINT_ERR_MSG, "FAIL: OMX_ErrorResourcesPreempted\n");
        break;
    case OMX_ErrorPortUnresponsiveDuringAllocation:
        PRINT( PRINT_ERR_MSG, "FAIL: OMX_ErrorPortUnresponsiveDuringAllocation\n");
        break;
    case OMX_ErrorPortUnresponsiveDuringDeallocation:
        PRINT( PRINT_ERR_MSG, "FAIL: OMX_ErrorPortUnresponsiveDuringDeallocation\n");
        break;   /* No more indicies can be enumerated */
    case OMX_ErrorPortUnresponsiveDuringStop:
        PRINT( PRINT_ERR_MSG, "FAIL: OMX_ErrorPortUnresponsiveDuringStop\n");
        break;
    case OMX_ErrorIncorrectStateTransition:
        PRINT( PRINT_ERR_MSG, "FAIL: OMX_ErrorIncorrectStateTransition\n");
        break;
    case OMX_ErrorIncorrectStateOperation:
        PRINT( PRINT_ERR_MSG, "FAIL: OMX_ErrorIncorrectStateOperation\n");
        break;
    case OMX_ErrorUnsupportedSetting:
        PRINT( PRINT_ERR_MSG, "FAIL: OMX_ErrorUnsupportedSetting\n");
        break;
    case OMX_ErrorUnsupportedIndex:
        PRINT( PRINT_ERR_MSG, "FAIL: OMX_ErrorUnsupportedIndex\n");
        break;
    case OMX_ErrorBadPortIndex:
        PRINT( PRINT_ERR_MSG, "FAIL: OMX_ErrorBadPortIndex\n");
        break;
    case OMX_ErrorPortUnpopulated:
        PRINT( PRINT_ERR_MSG, "FAIL: OMX_ErrorPortUnpopulated\n");
        break;
    case OMX_ErrorComponentSuspended:
        PRINT( PRINT_ERR_MSG, "FAIL: OMX_ErrorComponentSuspended\n");
        break;
    case OMX_ErrorDynamicResourcesUnavailable:
        PRINT( PRINT_ERR_MSG, "FAIL: OMX_ErrorDynamicResourcesUnavailable\n");
        break;
    case OMX_ErrorMbErrorsInFrame:
        PRINT( PRINT_ERR_MSG, "FAIL: OMX_ErrorMbErrorsInFrame\n");
        break;
    case OMX_ErrorFormatNotDetected:
        PRINT( PRINT_ERR_MSG, "FAIL: OMX_ErrorFormatNotDetected\n");
        break;
    case OMX_ErrorContentPipeOpenFailed:
        PRINT( PRINT_ERR_MSG, "FAIL: OMX_ErrorContentPipeOpenFailed\n");
        break;
    case OMX_ErrorContentPipeCreationFailed:
        PRINT( PRINT_ERR_MSG, "FAIL: OMX_ErrorContentPipeCreationFailed\n");
        break;
    case OMX_ErrorSeperateTablesUsed:
        PRINT( PRINT_ERR_MSG, "FAIL: OMX_ErrorSeperateTablesUsed\n");
        break;
    case OMX_ErrorTunnelingUnsupported:
        PRINT( PRINT_ERR_MSG, "FAIL: OMX_ErrorTunnelingUnsupported\n");
        break;
    case OMX_ErrorMax:
        PRINT( PRINT_ERR_MSG, "FAIL: OMX_ErrorMax\n");
        break;
    default:
        PRINT( PRINT_ERR_MSG, "FAIL: Unknown Error\n");
        break;
  } // switch(status)
}

/******************************************************************************\
 *      OMTB_OmxReturnStatusString Function Definition
\******************************************************************************/
/**
 *
 *  @brief    This Function copies the proper error code for OMX API return
 *            values to a string
 *
 *  @param    Retruns status from OMX API's
 *
 *  @return   String contains the proper error code
 *
 */
void OMTB_OmxReturnStatusString(
  OMX_ERRORTYPE  status, char returnString[]
)
{
  switch(status)
  {
    case OMX_ErrorNone:
        strcpy(returnString, "OMX_ErrorNone");
        break;
    case OMX_ErrorInsufficientResources:
        strcpy(returnString, "OMX_ErrorInsufficientResources");
        break;
    case OMX_ErrorUndefined:
        strcpy(returnString, "OMX_ErrorUndefined");
        break;
    case OMX_ErrorInvalidComponentName:
        strcpy(returnString, "OMX_ErrorInvalidComponentName");
        break;
    case OMX_ErrorComponentNotFound:
        strcpy(returnString, "OMX_ErrorComponentNotFound");
        break;
    case OMX_ErrorInvalidComponent:
        strcpy(returnString, "OMX_ErrorInvalidComponent");
        break;
    case OMX_ErrorBadParameter:
        strcpy(returnString, "OMX_ErrorBadParameter");
        break;
    case OMX_ErrorNotImplemented:
        strcpy(returnString, "OMX_ErrorNotImplemented");
        break;
    case OMX_ErrorUnderflow:
        strcpy(returnString, "OMX_ErrorUnderflow");
        break;
    case OMX_ErrorOverflow:
        strcpy(returnString, "OMX_ErrorOverflow");
        break;
    case OMX_ErrorHardware:
        strcpy(returnString, "OMX_ErrorHardware");
        break;
    case OMX_ErrorInvalidState:
        strcpy(returnString, "OMX_ErrorInvalidState");
        break;
    case OMX_ErrorStreamCorrupt:
        strcpy(returnString, "OMX_ErrorStreamCorrupt");
        break;
    case OMX_ErrorPortsNotCompatible:
        strcpy(returnString, "OMX_ErrorPortsNotCompatible");
        break;
    case OMX_ErrorResourcesLost:
        strcpy(returnString, "OMX_ErrorResourcesLost");
        break;
    case OMX_ErrorNoMore:
        strcpy(returnString, "OMX_ErrorNoMore");
        break;
    case OMX_ErrorVersionMismatch:
        strcpy(returnString, "OMX_ErrorVersionMismatch");
        break;
    case OMX_ErrorNotReady:
        strcpy(returnString, "OMX_ErrorNotReady");
        break;
    case OMX_ErrorTimeout:
        strcpy(returnString, "OMX_ErrorTimeout");
        break;
    case OMX_ErrorSameState:
        strcpy(returnString, "OMX_ErrorSameState");
        break;
    case OMX_ErrorResourcesPreempted:
        strcpy(returnString, "OMX_ErrorResourcesPreempted");
        break;
    case OMX_ErrorPortUnresponsiveDuringAllocation:
        strcpy(returnString, "OMX_ErrorPortUnresponsiveDuringAllocation");
        break;
    case OMX_ErrorPortUnresponsiveDuringDeallocation:
        strcpy(returnString, "OMX_ErrorPortUnresponsiveDuringDeallocation");
        break;   /* No more indicies can be enumerated */
    case OMX_ErrorPortUnresponsiveDuringStop:
        strcpy(returnString, "OMX_ErrorPortUnresponsiveDuringStop");
        break;
    case OMX_ErrorIncorrectStateTransition:
        strcpy(returnString, "OMX_ErrorIncorrectStateTransition");
        break;
    case OMX_ErrorIncorrectStateOperation:
        strcpy(returnString, "OMX_ErrorIncorrectStateOperation");
        break;
    case OMX_ErrorUnsupportedSetting:
        strcpy(returnString, "OMX_ErrorUnsupportedSetting");
        break;
    case OMX_ErrorUnsupportedIndex:
        strcpy(returnString, "OMX_ErrorUnsupportedIndex");
        break;
    case OMX_ErrorBadPortIndex:
        strcpy(returnString, "OMX_ErrorBadPortIndex");
        break;
    case OMX_ErrorPortUnpopulated:
        strcpy(returnString, "OMX_ErrorPortUnpopulated");
        break;
    case OMX_ErrorComponentSuspended:
        strcpy(returnString, "OMX_ErrorComponentSuspended");
        break;
    case OMX_ErrorDynamicResourcesUnavailable:
        strcpy(returnString, "OMX_ErrorDynamicResourcesUnavailable");
        break;
    case OMX_ErrorMbErrorsInFrame:
        strcpy(returnString, "OMX_ErrorMbErrorsInFrame");
        break;
    case OMX_ErrorFormatNotDetected:
        strcpy(returnString, "OMX_ErrorFormatNotDetected");
        break;
    case OMX_ErrorContentPipeOpenFailed:
        strcpy(returnString, "OMX_ErrorContentPipeOpenFailed");
        break;
    case OMX_ErrorContentPipeCreationFailed:
        strcpy(returnString, "OMX_ErrorContentPipeCreationFailed");
        break;
    case OMX_ErrorSeperateTablesUsed:
        strcpy(returnString, "OMX_ErrorSeperateTablesUsed");
        break;
    case OMX_ErrorTunnelingUnsupported:
        strcpy(returnString, "OMX_ErrorTunnelingUnsupported");
        break;
    case OMX_ErrorMax:
        strcpy(returnString, "OMX_ErrorMax");
        break;
    default:
        strcpy(returnString, "Unknown Error");
        break;
  } // switch(status)
}


/******************************************************************************\
 *  OMTB_DimtSkipWhiteSpace Function Definition
\******************************************************************************/
/**
 *
 *  @brief    This Function Skip White Space from command line  
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
OMTB_DimtSkipWhiteSpace(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine
)
{
  char*   p_char = NULL;

  p_char = (char*) *ppCmdLine;

  /* Skip leading white space. Stop if comment or end of line. */
  while (isspace((INT16)*p_char))
  {
    p_char++;
  }

  if (IS_LINE_END(*p_char))
  {
    return ((MX_Result)ERR_INVNAME);
  }
  return ((MX_Result)ERR_NOERR);
}


/******************************************************************************\
 *      OMTB_ShowCmdHelp Function Definition
\******************************************************************************/
/**
 *
 *  @brief    This Function show the command help it is called from 
 *            OMTB_CmdParseOmx if the first command entered doesn't 
 *            match with the string expected
 *
 *  @param    pContext: Pointer to MX_DBG_CMD_CONTEXT_T
 *
 *  @return   None
 *
 */

PRIVATE void 
OMTB_ShowCmdHelp(
  MX_DBG_CMD_CONTEXT_T*   pContext
)
{
  MX_DBG_CMD_TABLE_T*     pCmdTbl = NULL;
  MX_DBG_CMD_ENTRY_T*     pTempCmdEntry = NULL;
  UINT8                   i = 0;
  UINT8                   j = 0;
  UINT16                  numColumns = 0;
  char                    line[OMTB_MAX_LEN] = {"\0"};
  
  printf("\nomx");
  
  pCmdTbl = (MX_DBG_CMD_TABLE_T*)pContext->p_cur_cmd_tbl;

  numColumns = 3u;
  TIMM_OSAL_Memset(line, 0, sizeof(line));

  while (NULL != (pTempCmdEntry = pCmdTbl->p_entries[i++]))
  {
    /* Display '-' below each category defined by dummy entry having no 
       command */
    if (strcmp(pTempCmdEntry->name, "") == 0)
    {
      int len = 0;
      printf("%s\n\n", line);
      TIMM_OSAL_Memset(line, 0, sizeof(line));
      len = printf("\n%s\n", pTempCmdEntry->syntax_str);
      
      while(0 < --len)
        printf("-");
        
      printf("\n");
      j = 0;
      continue;
    }

    /* display the secondary level command in n rows of 3 column each */
    /* no of rows depends on the command entry in the command table of omx */
    switch (j % numColumns)
    {
      case 0:
        
        sprintf(line, "   %-22s", pTempCmdEntry->name); 
        break;

      case 1:
        
        sprintf(line, "%s%-22s", line, pTempCmdEntry->name); 
        break;

      case 2:
        
        printf("%s%-22s\n", line, pTempCmdEntry->name);
        TIMM_OSAL_Memset(line, 0, sizeof(line));
        break;
      
      default:

        break;
    }
    
    j++;
  }
  printf("%s\n", line);
}


/******************************************************************************\
 *      OMTB_CmdParseOmx Function Definition
\******************************************************************************/
/**
 *
 *  @brief    This Function compares the first command if first command matches
 *            with the string mentioned parses rest of commands else returns 
 *            appropriate error code
 *
 *  @param    argc: Number of arguments received from command line
 *            argv: Array of pointers to commands 
 *                  entered through the command line
 *
 *  @return   ERR_NOERR           successful,
 *            ERR_END_OF_CMD      help was requested,
 *            ERR_INVNAME         otherwise.
 */

void OMTB_CmdParseOmx(
        UINT32  argc,
        CHAR    *argv[]
)
{
  MX_DBG_CMD_CONTEXT_T    cmdCntxt;
  MX_Result               result = ERR_NOERR;

  /* Initialize the command context */
  TIMM_OSAL_Memset(&cmdCntxt, 0, sizeof(MX_DBG_CMD_CONTEXT_T));
  cmdCntxt.p_cur_cmd_tbl = &cmdTblOmx;
  cmdCntxt.cur_inst      = MX_DBG_CMD_CONTEXT_INIT_INST;
  strcpy(cmdCntxt.syntax_str, "omx");
  strcpy(cmdCntxt.cmd_line_str, cmdCntxt.syntax_str);

  if(2u > argc)
  {
    OMTB_ShowCmdHelp(&cmdCntxt);
    return;
  }

  result = XdbgCmdParse(&cmdCntxt, &cmdEntryOmx, &argv[1]);

  if (ERR_NOERR == result)
  {
    printf("OK\n");
  }
}


/******************************************************************************\
 *      OMTB_CmdReleaseInfo Function Definition
\******************************************************************************/
/**
 *
 *  @brief    This Function displays OMTB application version number.
 *
 *
 *  @param    Pointer to MX_DBG_CMD_CONTEXT_T structure
 *            Pointer to MX_DBG_CMD_Entry_T structure
 *            Character Double Pointer containing the command
 *
 *  @return   ERR_NOERR           successful,
 *
 */

MX_Result
OMTB_CmdReleaseInfo(
  MX_DBG_CMD_CONTEXT_T*       pContext,
  MX_DBG_CMD_ENTRY_T*         pCmdEntry,
  char**                      ppCmdLine
)
{
  /* Display the OMTB version number */
  PRINT(PRINT_MUST, "OMTB Version: %s\n", OMTB_REL_INFO_STRING);

  return ERR_NOERR;
}


/******************************************************************************\
 *      OMTB_CmdStoreCfg Function Definition
\******************************************************************************/
/**
 *
 *  @brief    This Function stores OMTB configuration to specified file.
 *
 *
 *  @param    Pointer to MX_DBG_CMD_CONTEXT_T structure
 *            Pointer to MX_DBG_CMD_Entry_T structure
 *            Character Double Pointer containing the command
 *
 *  @return   ERR_NOERR           successful,
 *
 */

MX_Result
OMTB_CmdStoreCfg(
  MX_DBG_CMD_CONTEXT_T*       pContext,
  MX_DBG_CMD_ENTRY_T*         pCmdEntry,
  char**                      ppCmdLine
)
{
  MX_Result result = ERR_NOERR;
  unsigned int template = 0;
  char cfgFileName[OMTB_MAX_LEN] = {"\0"};

  /* Read template number */
  result = XdbgCmdNextNum(pContext,pCmdEntry, ppCmdLine, (UINT32*)&template);
  if (ERR_NOERR != result)
  { 
    return result;
  }
  
  if(OMTB_MAX_TEMPLATE <= template)
  {
    /* Invalid template */
    PRINT(PRINT_ERR_MSG, "Invalid template number %d -Valid range: <0 to %d>\n",
                          template, OMTB_MAX_TEMPLATE - 1);
    return ERR_INVNAME;
  }

  /* Read the config file name */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, cfgFileName);
  if (ERR_NOERR != result)
  {
    XdbgCmdSyntaxShow(pContext, pCmdEntry);
    return result;
  }

  /* Invoke the store configuration to dump the current cfg to file */
  result = OMTB_StoreCfg(cfgFileName, template);
  
  if(ERR_NOERR != result)
  {
    PRINT(PRINT_ERR_MSG, "%s: Error storing config params\n", __FUNCTION__);
    return result;
  }
  
  return ERR_NOERR;
}


/******************************************************************************\
 *      OMTB_CmdLoadCfg Function Definition
\******************************************************************************/
/**
 *
 *  @brief    This Function loads OMTB configuration from specified file.
 *
 *
 *  @param    Pointer to MX_DBG_CMD_CONTEXT_T structure
 *            Pointer to MX_DBG_CMD_Entry_T structure
 *            Character Double Pointer containing the command
 *
 *  @return   ERR_NOERR           successful,
 *
 */

MX_Result
OMTB_CmdLoadCfg(
  MX_DBG_CMD_CONTEXT_T*       pContext,
  MX_DBG_CMD_ENTRY_T*         pCmdEntry,
  char**                      ppCmdLine
)
{
  MX_Result result = ERR_NOERR;
  unsigned int template = 0;
  char cfgFileName[OMTB_MAX_LEN] = {"\0"};

  /* Read template number */
  result = XdbgCmdNextNum(pContext,pCmdEntry, ppCmdLine, (UINT32*)&template);
  if (ERR_NOERR != result)
  { 
    return result;
  }
  
  if(OMTB_MAX_TEMPLATE <= template)
  {
    /* Invalid template */
    PRINT(PRINT_ERR_MSG, "Invalid template number %d -Valid range: <0 to %d>\n",
                          template, OMTB_MAX_TEMPLATE - 1);
    return ERR_INVNAME;
  }

  /* Read the config file name */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, cfgFileName);
  if (ERR_NOERR != result)
  {
    XdbgCmdSyntaxShow(pContext, pCmdEntry);
    return result;
  }

  /* load the template from file having configuration params in specific 
     command format */
  result = OMTB_LoadCfg(cfgFileName, template);
  
  if(ERR_NOERR != result)
  {
    PRINT(PRINT_ERR_MSG, "%s: Error loading config params\n", __FUNCTION__);
    return result;
  }
  
  return ERR_NOERR;
}


/******************************************************************************\
 *      OMTB_CmdAddCfg Function Definition
\******************************************************************************/
/**
 *
 *  @brief    This Function allocates specified OMTB configuration template 
 *            memory.
 *
 *
 *  @param    Pointer to MX_DBG_CMD_CONTEXT_T structure
 *            Pointer to MX_DBG_CMD_Entry_T structure
 *            Character Double Pointer containing the command
 *
 *  @return   ERR_NOERR           successful,
 *
 */

MX_Result
OMTB_CmdAddCfg(
  MX_DBG_CMD_CONTEXT_T*       pContext,
  MX_DBG_CMD_ENTRY_T*         pCmdEntry,
  char**                      ppCmdLine
)
{
  MX_Result result = ERR_NOERR;
  unsigned int template = 0;

  /* Read template number */
  result = XdbgCmdNextNum(pContext,pCmdEntry, ppCmdLine, (UINT32*)&template);
  if (ERR_NOERR != result)
  { 
    return result;
  }
  
  if(OMTB_MAX_TEMPLATE <= template)
  {
    /* Invalid template */
    PRINT(PRINT_ERR_MSG, "Invalid template number %d -Valid range: <0 to %d>\n",
                          template, OMTB_MAX_TEMPLATE - 1);
    return ERR_INVNAME;
  }

  /* add the new configuration template into memory */
  result = OMTB_AddCfg(template);
  
  if(ERR_NOERR != result)
  {
    PRINT(PRINT_ERR_MSG, "%s: Error allocating cfg params memory\n", __FUNCTION__);
    return result;
  }
  
  return ERR_NOERR;
}


/******************************************************************************\
 *      OMTB_CmdRemoveCfg Function Definition
\******************************************************************************/
/**
 *
 *  @brief    This Function releases specified OMTB configuration template 
 *            memory.
 *
 *
 *  @param    Pointer to MX_DBG_CMD_CONTEXT_T structure
 *            Pointer to MX_DBG_CMD_Entry_T structure
 *            Character Double Pointer containing the command
 *
 *  @return   ERR_NOERR           successful,
 *
 */

MX_Result
OMTB_CmdRemoveCfg(
  MX_DBG_CMD_CONTEXT_T*       pContext,
  MX_DBG_CMD_ENTRY_T*         pCmdEntry,
  char**                      ppCmdLine
)
{
  MX_Result result = ERR_NOERR;
  unsigned int template = 0;

  /* Read template number */
  result = XdbgCmdNextNum(pContext,pCmdEntry, ppCmdLine, (UINT32*)&template);
  if (ERR_NOERR != result)
  { 
    return result;
  }
  
  if(OMTB_MAX_TEMPLATE <= template)
  {
    /* Invalid template */
    PRINT(PRINT_ERR_MSG, "Invalid template number %d -Valid range: <0 to %d>\n",
                          template, OMTB_MAX_TEMPLATE - 1);
    return ERR_INVNAME;
  }

  /* remove the specified configuration template from the memory */
  result = OMTB_RemoveCfg(template);
  
  if(ERR_NOERR != result)
  {
    PRINT(PRINT_ERR_MSG, "%s: Error releasing config params memory\n", 
                          __FUNCTION__);
    return result;
  }
  
  return ERR_NOERR;
}


/******************************************************************************\
 *      OMTB_CmdRunScript Function Definition
\******************************************************************************/
/**
 *
 *  @brief   
 *            This Function runs OMTB using DVS script.
 *
 *  @param    Pointer to MX_DBG_CMD_CONTEXT_T structure
 *            Pointer to MX_DBG_CMD_Entry_T structure
 *            Character Double Pointer containing the command
 *
 *  @return   ERR_NOERR           successful,
 *
 */

MX_Result
OMTB_CmdRunScript(
  MX_DBG_CMD_CONTEXT_T*       pContext,
  MX_DBG_CMD_ENTRY_T*         pCmdEntry,
  char**                      ppCmdLine
)
{
  MX_Result result = ERR_NOERR;
  char scriptFileName[OMTB_MAX_LEN] = {"\0"};

  /* Read the script file name */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, scriptFileName);
  if (ERR_NOERR != result)
  {
    XdbgCmdSyntaxShow(pContext, pCmdEntry);
    return result;
  }

  /* run the script */
  result = OMTB_RunScript(scriptFileName);
  
  return result;
}


/******************************************************************************\
 *      OMTB_CmdShowArmLoad Function Definition
\******************************************************************************/
/**
 *
 *  @brief    This Function is used to ENABLE/DISABLE arm load measuring thread
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
OMTB_CmdShowArmLoad(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine
)
{
  /* Toggle the ARM CPU load display */
  armCpuLoadDispFlag = !(armCpuLoadDispFlag);
  return ((MX_Result)ERR_NOERR);
}


/******************************************************************************\
 *      OMTB_CmdToggleCompDbgLog Function Definition
\******************************************************************************/
/**
 *
 *  @brief    This Function is used to ENABLE/DISABLE component debug logs.
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
OMTB_CmdToggleCompDbgLog(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine
)
{
  /* Toggle the component debug log display */
  globDebugDisable = !(globDebugDisable);
  return ((MX_Result)ERR_NOERR);
}


/******************************************************************************\
 *      OMTB_CmdSetDbgLogLevel Function Definition
\******************************************************************************/
/**
 *
 *  @brief    This Function is used to set OMTB debug log level for display.
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
OMTB_CmdSetDbgLogLevel(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine
)
{
  unsigned int dbgLogLevel = 0;
  MX_Result result = ERR_NOERR;

  /* Read debug log level */
  result = XdbgCmdNextNum(pContext, pCmdEntry, ppCmdLine,
                          (UINT32 *)&dbgLogLevel);
  if (ERR_NOERR != result)
  {

    return result;
  }

  /* Disable all prints except errors and compulsary prints */
  if (PRINT_NO_OUTPUT == dbgLogLevel)
  {
    omtbDbgLogLevel = PRINT_NO_OUTPUT;
    return ((MX_Result)ERR_NOERR);
  }

  /* Print Simple Message */
  if (PRINT_SIMPLE_MESSAGE & dbgLogLevel)
  {
    omtbDbgLogLevel |= PRINT_SIMPLE_MESSAGE;
  }

  /* Print Default Message */
  if (DEFAULT_MESSAGES & dbgLogLevel)
  {
    omtbDbgLogLevel |= DEFAULT_MESSAGES;
  }

  /* Print Function Name*/
  if (PRINT_FUNCTION_NAME & dbgLogLevel)
  {
    omtbDbgLogLevel |= PRINT_FUNCTION_NAME;
  }

  /* Print Debug Mesaage */
  if (PRINT_DEBUG_MESSAGE & dbgLogLevel)
  {
    omtbDbgLogLevel |= PRINT_DEBUG_MESSAGE;
  }

  /* Print the info for Set Param / Set config */ 
  if (PRINT_SET_PARAM & dbgLogLevel)
  {
    omtbDbgLogLevel |= PRINT_SET_PARAM;
  }
  
  /* Print the info for Get Param / Get config */ 
  if (PRINT_GET_PARAM & dbgLogLevel)
  {
    omtbDbgLogLevel |= PRINT_GET_PARAM;
  }
  
  /* Print Compulsary Mesaage */
  if (PRINT_MUST & dbgLogLevel)
  {
    omtbDbgLogLevel |= PRINT_MUST;
  }

  /* Print Error Mesaage */
  if (PRINT_ERR_MSG & dbgLogLevel)
  {
    omtbDbgLogLevel |= PRINT_ERR_MSG;
  }
    
  return ((MX_Result)ERR_NOERR);
}


/******************************************************************************\
 *      OMTB_CmdStartLoop Function Definition
\******************************************************************************/
/**
 *
 *  @brief   
 *            This Function is called when start loop command is invoked.
 *
 *  @param    Pointer to MX_DBG_CMD_CONTEXT_T structure
 *            Pointer to MX_DBG_CMD_Entry_T structure
 *            Character Double Pointer containing the command
 *
 *  @return   ERR_NOERR           successful,
 *
 */

MX_Result
OMTB_CmdStartLoop(
  MX_DBG_CMD_CONTEXT_T*       pContext,
  MX_DBG_CMD_ENTRY_T*         pCmdEntry,
  char**                      ppCmdLine
)
{
  MX_Result result = ERR_NOERR;
  unsigned int loopCount = 0;
  
  /* Read the loopCount */
  result = XdbgCmdNextNum(pContext, pCmdEntry, ppCmdLine,
                          (UINT32 *)&loopCount);

  if (ERR_NOERR != result)
  {
    //XdbgCmdSyntaxShow(pContext, pCmdEntry);
    return result;
  }

  gLoopCount = loopCount;
  PRINT(PRINT_MUST, "Loop Count: <%d>\n", gLoopCount);  
  
  gCopyCommand = OMX_TRUE;	  
  gCmdCount = 0;

  return result;
}

/******************************************************************************\
 *      OMTB_CmdEndLoop Function Definition
\******************************************************************************/
/**
 *
 *  @brief   
 *            This Function is called when end loop command is invoked.
 *
 *  @param    Pointer to MX_DBG_CMD_CONTEXT_T structure
 *            Pointer to MX_DBG_CMD_Entry_T structure
 *            Character Double Pointer containing the command
 *
 *  @return   ERR_NOERR           successful,
 *
 */

MX_Result
OMTB_CmdEndLoop(
  MX_DBG_CMD_CONTEXT_T*       pContext,
  MX_DBG_CMD_ENTRY_T*         pCmdEntry,
  char**                      ppCmdLine
)
{
  int i = 0, j = 0;
  MX_Result result = ERR_NOERR;
  
  /* stop copying the commands */
  gCopyCommand = OMX_FALSE;

  /* Run all the commands in a loop for n iterartions */	
  for(i = 0; i < (gLoopCount-1); i++)
  {
    for(j = 0; j < (gCmdCount-1); j++)
	{
      /* Invoke the omx command processing function */
      PRINT(PRINT_MUST, "\r     \nOMTB> %s\n", gInputCmd[j]);		
      procCmdLine(gInputCmd[j]);
	}
  }
  
  gLoopCount = 0;
  gCmdCount = 0;
  
  return result;  
}	

/******************************************************************************\
 *      OMTB_CmdNotify Function Definition
\******************************************************************************/
/**
 *
 *  @brief   
 *            This Function sleeps or "pauses the main thread" and gets notification
 *            after the task has been completed.
 *
 *  @param    Pointer to MX_DBG_CMD_CONTEXT_T structure
 *            Pointer to MX_DBG_CMD_Entry_T structure
 *            Character Double Pointer containing the command
 *
 *  @return   ERR_NOERR           successful,
 *
 */
MX_Result
OMTB_CmdNotify(
  MX_DBG_CMD_CONTEXT_T*       pContext,
  MX_DBG_CMD_ENTRY_T*         pCmdEntry,
  char**                      ppCmdLine
)
{
  MX_Result result = ERR_NOERR;
  char componentRequested[OMX_MAX_STRINGNAME_SIZE] = {"\0"};  
  char cmd[OMX_MAX_STRINGNAME_SIZE] = {"\0"};  
  OMTB_CLIENT_PRIVATE* thisClient = NULL;
  unsigned int instanceNo = 0;
  
  /* Read the Component Name */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, componentRequested);
  if (ERR_NOERR != result)
  {
    XdbgCmdSyntaxShow(pContext, pCmdEntry);
    return result;
  }

  /* Read the Instance Num */
  result = XdbgCmdNextNum(pContext, pCmdEntry, ppCmdLine,
                         (UINT32 *)&instanceNo);
  if (ERR_NOERR != result)
  {
    XdbgCmdSyntaxShow(pContext, pCmdEntry);
    return result;
  }

  /* Get the pointer */
  thisClient =  (OMTB_CLIENT_PRIVATE*)OMTB_GetCompPrivHandle(componentRequested, instanceNo);   
	
  /* Read the cmd to process */
  result = XdbgCmdNextVar(pCmdEntry, ppCmdLine, cmd);
  if (ERR_NOERR != result)
  {
    XdbgCmdSyntaxShow(pContext, pCmdEntry);
    return result;
  }
  
  if(0 == memcmp(cmd, OMTB_APP_EOS_CMD_STR, strlen(OMTB_APP_EOS_CMD_STR)))
  {
    /* wait for event notfication EOS */
    TIMM_OSAL_SemaphoreObtain(thisClient->omtbPvt.eofSem, TIMM_OSAL_SUSPEND);	
  }
  
  return result;    
}
/*----------------------------- end of file ---------------------------------*/
