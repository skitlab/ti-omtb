/*
 * omtbCmd.h
 *
 * This file contains omtb prototypes/declarations utility commands.
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

#ifndef __OMTB_CMD_H__
#define __OMTB_CMD_H__


/******************************************************************************\
 *      Standard Includes
\******************************************************************************/

#include <stdio.h>
#include <ctype.h>

/* OMX standard header files */
#include "OMX_Component.h"
#include "OMX_Types.h"


/******************************************************************************\
 *      Customized Includes
\******************************************************************************/

#include "mxDbg.h"
#include "omtbCommon.h"


/******************************************************************************/

#ifdef __cplusplus    /* required for headers that might */
 extern "C" {         /* be compiled by a C++ compiler */
#endif


/******************************************************************************\
 *      Defines
\******************************************************************************/


/******************************************************************************\
 *      Data type definitions
\******************************************************************************/


/******************************************************************************\
 *      Macros
\******************************************************************************/


/******************************************************************************\
 *      Globals
\******************************************************************************/


/******************************************************************************\
 *      External Object Definitions
\******************************************************************************/


/******************************************************************************\
 *      Public Function Prototypes
\******************************************************************************/

/******************************************************************************\
 *      OMTB_CmdParseOmx Function Prototype
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
);


/******************************************************************************\
 *      OMTB_OmxReturnStatus Function Prototype
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

void OMTB_OmxReturnStatus(OMX_ERRORTYPE  status);

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
);


/******************************************************************************\
 *      OMTB_DimtSkipWhiteSpace Function Prototype
\******************************************************************************/
/**
 *
 *  @brief   This Function Skip White Space from command line  
 *
 *  @param   Pointer to MX_DBG_CMD_CONTEXT_T structure
 *           Pointer to MX_DBG_CMD_Entry_T structure
 *           Character Double Pointer containing the command
 *
 *  @return  ERR_NOERR           successful,
 *           ERR_END_OF_CMD      help was requested,
 *           ERR_INVNAME         otherwise.
 */

MX_Result OMTB_DimtSkipWhiteSpace(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine
);


/******************************************************************************\
 *      OMTB_CmdReleaseInfo Function Prototype
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
);


/******************************************************************************\
 *      OMTB_CmdStoreCfg Function Prototype
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
);


/******************************************************************************\
 *      OMTB_CmdLoadCfg Function Prototype
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
);


/******************************************************************************\
 *      OMTB_CmdAddCfg Function Prototype
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
);


/******************************************************************************\
 *      OMTB_CmdRemoveCfg Function Prototype
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
);


/******************************************************************************\
 *      OMTB_CmdRunScript Function Prototype
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
);


/******************************************************************************\
 *      OMTB_CmdShowArmLoad Function Prototype
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
);


/******************************************************************************\
 *      OMTB_CmdToggleCompDbgLog Function Prototype
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
);


/******************************************************************************\
 *      OMTB_CmdSetDbgLogLevel Function Prototype
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
);


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
);

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
);

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
);
#ifdef __cplusplus    /* matches __cplusplus construct above */
 }
#endif

#endif


/*----------------------------- end of file ---------------------------------*/
