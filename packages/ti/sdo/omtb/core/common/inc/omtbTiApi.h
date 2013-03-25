/*
 * omtbTiApi.h
 *
 * This file contains omtb prototypes/declarations for OMTB OMX API dispatchers.
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

#ifndef __OMTB_TI_API_H__
#define __OMTB_TI_API_H__


/******************************************************************************\
 *      Standard Includes
\******************************************************************************/

#include <stdio.h>
#include <ctype.h>

/* OMX standard header files */
#include "OMX_Component.h"
#include "OMX_Types.h"
#include <ti/omx/omxutils/omx_utils.h>

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
typedef struct OMTB_FQ_MANAGER_T {
  OMX_UTL_TUNNEL_CONTEXT sTunnelCtxt[OMTB_MAX_TUNNELS]; /* Array of the tunnels */
  OMX_U8 nPoolId[OMTB_MAX_TUNNELS]; /*Array of Pool Ids */
  unsigned int nFQTunnelIndex; /* Index used for sTunnelCtxt and nPoolId */
}OMTB_FQ_MANAGER;

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
 *      OMTB_OmxCreateFQ Function Prototype
\******************************************************************************/
/**
 *
 *  @brief    This Function will  create a Frame Queue Buffer Manager between
 *            two specified components.
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
OMTB_OmxCreateFQ(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine
);

/******************************************************************************\
 *      OMTB_OmxConfigFQ Function Prototype
\******************************************************************************/
/**
 *
 *  @brief    This Function will config params used to create a  Frame Queue between
 *            two specified components.
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
OMTB_OmxConfigFQ(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine
);

/******************************************************************************\
 *      OMTB_OmxDeleteFQ Function Prototype
\******************************************************************************/
/**
 *
 *  @brief    This Function will delete the Frame Queue Buffer Manager.
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
OMTB_OmxDeleteFQ(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine
);

#ifdef __cplusplus    /* matches __cplusplus construct above */
 }
#endif

#endif


/*----------------------------- end of file ---------------------------------*/
