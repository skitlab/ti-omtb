/*
 * omtbAlsaPlayApi.h
 *
 * This file contains component specific function declarations.
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

/* OMX standard header files */
#include "OMX_Core.h"
#include "OMX_Component.h"
#include "OMX_Types.h"


/******************************************************************************\
 *      Customized Includes
\******************************************************************************/

#include "mxDbg.h"


/******************************************************************************\
 *      Local Defines
\******************************************************************************/


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


/******************************************************************************\
 *      Private Function Declarations
\******************************************************************************/


/******************************************************************************\
 *      ALSAPLAY_GetCompHandle Function Prototype
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
);

/******************************************************************************\
 *      ALSAPLAY_Func Function Prototype
\******************************************************************************/
/**
 *
 *  @brief    This Function invokes the H264VDEC_FuncTsk Thread
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
);
/*----------------------------- end of file ---------------------------------*/
