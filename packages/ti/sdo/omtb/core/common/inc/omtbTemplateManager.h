/*
 * omtbTemplateManager.h
 *
 * This file contains omtb prototypes/declarations for cfg templates
 * and utility commands for template management.
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

#ifndef __OMTB_TEMPLATE_MANAGER_H__
#define __OMTB_TEMPLATE_MANAGER_H__


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
  *      OMTB_AddCfg Function Prototype
 \******************************************************************************/
 /*
  *
  *  @brief    
  *            This function allocates the memory for the specified template.
  *
  *  @param in:
  *            template: Template no which is to be allocated.
  *
  *  @param Out:
  *            None
  *
  *  @return   
  *            ERR_NOERR           successful,
  *
  *            ERR_INVNAME         Incorrect template number/Memory allocation 
  *                                error.
  */

 MX_Result OMTB_AddCfg(unsigned int template);


 /******************************************************************************\
  *      OMTB_RemoveCfg Function Prototype
 \******************************************************************************/
 /*
  *
  *  @brief    
  *            This function releases the memory of the specified template.
  *
  *  @param in:
  *            template: Template no which is to be removed from memory
  *
  *  @param Out:
  *            None
  *
  *  @return   
  *            ERR_NOERR           successful,
  *
  *            ERR_INVNAME         Incorrect template number/file name.
  */

 MX_Result OMTB_RemoveCfg(unsigned int template);
 

 /******************************************************************************\
  *      OMTB_SetTemplateDefVal Function Prototype
 \******************************************************************************/
 /*
  *
  *  @brief    This function copies the default values in specified template.
  *
  *  @param in:
  *            template: Template no which is to be filled with default values
  *
  *  @param Out:
  *            None
  *
  *  @return   
  *            ERR_NOERR           successful,
  *
  *            ERR_INVNAME         Incorrect template number/Memory allocation 
  *                                error.
  */

 MX_Result OMTB_SetTemplateDefVal(unsigned int template);
 
 
 /******************************************************************************\
  *      OMTB_LoadCfg Function Definition
 \******************************************************************************/
 /*
  *
  *  @brief   This function loads the configuration into specified template 
  *           from file.
  *
  *  @param in:
  *            cfgFileName: Pointer to configuration file name
  *
  *            template: Template no to which cfg is to be loaded
  *
  *  @param Out:
  *            None
  *
  *  @return   
  *            ERR_NOERR           successful,
  *
  *            ERR_INVNAME         Incorrect template number/file name.
  */

 MX_Result OMTB_LoadCfg( char *cfgFileName,
                         unsigned int template);


 /******************************************************************************\
  *      OMTB_StoreCfg Function Definition
 \******************************************************************************/
 /*
  *
  *  @brief   
  *            This function copies the default values of specified template to
  *            file.
  *
  *  @param in:
  *            cfgFileName: Pointer to configuration file name
  *
  *            template: Template no for which cfg is to be stored
  *
  *  @param Out:
  *            None
  *
  *  @return   
  *            ERR_NOERR           successful,
  *
  *            ERR_INVNAME         Incorrect template number/file name.
  */

 MX_Result OMTB_StoreCfg(char *cfgFileName,
                         unsigned int template);
 
 
/******************************************************************************\
 *      OMTB_CmdSetTemplate Function Prototype
\******************************************************************************/
/**
 *
 *  @brief    This Function is a wrapper on top of OMTB_CmdTemplate and is 
 *            called if user wants to set parameter in the template
 *
 *  @param    pContext   : Pointer to MX_DBG_CMD_CONTEXT_T structure
 *            pCmdEntry :Pointer to MX_DBG_CMD_Entry_T structure
 *            ppCmdLine :Character Double Pointer containing the command
 *
 *
 *  @return   ERR_NOERR           successful,
 *            ERR_END_OF_CMD      help was requested,
 *            ERR_INVNAME         otherwise.
 */

MX_Result
OMTB_CmdSetTemplate(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine
);


/******************************************************************************\
 *      OMTB_CmdShowTemplate Function Prototype
\******************************************************************************/
/**
 *
 *  @brief    This Function is a wrapper on top of OMTB_CmdTemplate and is 
 *            called if user wants to display the parameter present in the
 *            template
 *
 *  @param    pContext   : Pointer to MX_DBG_CMD_CONTEXT_T structure
 *            pCmdEntry :Pointer to MX_DBG_CMD_Entry_T structure
 *            ppCmdLine :Character Double Pointer containing the command
 *
 *
 *  @return   ERR_NOERR           successful,
 *            ERR_END_OF_CMD      help was requested,
 *            ERR_INVNAME         otherwise.
 */

MX_Result
OMTB_CmdShowTemplate(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine
);


/******************************************************************************\
 *      OMTB_CmdResetTemplate Function Prototype
\******************************************************************************/
/**
 *
 *  @brief    This Function is a wrapper on top of OMTB_CmdTemplate and is 
 *            called if user wants to reset the parameter present in the
 *            template
 *
 *  @param    pContext   : Pointer to MX_DBG_CMD_CONTEXT_T structure
 *            pCmdEntry :Pointer to MX_DBG_CMD_Entry_T structure
 *            ppCmdLine :Character Double Pointer containing the command
 *
 *
 *  @return   ERR_NOERR           successful,
 *            ERR_END_OF_CMD      help was requested,
 *            ERR_INVNAME         otherwise.
 */

MX_Result
OMTB_CmdResetTemplate(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine
);


#ifdef __cplusplus    /* matches __cplusplus construct above */
 }
#endif

#endif


/*----------------------------- end of file ---------------------------------*/
