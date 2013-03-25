/*
 * omtbH264VdecApiTest.h
 *
 * This file contains component specific function declarations for API testing.
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
 *      H264VDEC_OmxAllocUseBufferOnce Function Prototype
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

MX_Result H264VDEC_OmxAllocUseBufferOnce(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine);


/******************************************************************************\
 *      H264VDEC_OmxAllocUseBufferInsuffResources Function Prototype
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

MX_Result H264VDEC_OmxAllocUseBufferInsuffResources(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine);


/******************************************************************************\
 *      H264VDEC_OmxAllocUseBufferNullBufferHdr Function Prototype
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

MX_Result H264VDEC_OmxAllocUseBufferNullBufferHdr(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine);


/******************************************************************************\
 *      H264VDEC_OmxAllocUseBufferNullHandle Function Prototype
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

MX_Result H264VDEC_OmxAllocUseBufferNullHandle(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine);


/******************************************************************************\
 *      H264VDEC_OmxAllocUseBufferVerMismatch Function Prototype
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

MX_Result H264VDEC_OmxAllocUseBufferVerMismatch(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine);


/******************************************************************************\
 *      H264VDEC_OmxAllocUseBufferTimeOut Function Prototype
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

MX_Result H264VDEC_OmxAllocUseBufferTimeOut(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine);


/******************************************************************************\
 *      H264VDEC_OmxAllocUseBufferWrongPort Function Prototype
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

MX_Result H264VDEC_OmxAllocUseBufferWrongPort(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine);


/******************************************************************************\
 *      H264VDEC_OmxAllocUseBufferIdleState Function Prototype
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

MX_Result H264VDEC_OmxAllocUseBufferIdleState(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine);


/******************************************************************************\
 *      H264VDEC_OmxFreeBufferOnce Function Prototype
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


MX_Result H264VDEC_OmxFreeBufferOnce(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine);


/******************************************************************************\
 *      H264VDEC_OmxFreeBufferInsuffResources Function Prototype
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


MX_Result H264VDEC_OmxFreeBufferInsuffResources(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine);


/******************************************************************************\
 *      H264VDEC_OmxFreeBufferNullBufferHdr Function Prototype
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


MX_Result H264VDEC_OmxFreeBufferNullBufferHdr(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine);


/******************************************************************************\
 *      H264VDEC_OmxFreeBufferNullHandle Function Prototype
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


MX_Result H264VDEC_OmxFreeBufferNullHandle(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine);


/******************************************************************************\
 *      H264VDEC_OmxFreeBufferVerMismatch Function Prototype
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


MX_Result H264VDEC_OmxFreeBufferVerMismatch(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine);


/******************************************************************************\
 *      H264VDEC_OmxFreeBufferTimeOut Function Prototype
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


MX_Result H264VDEC_OmxFreeBufferTimeOut(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine);


/******************************************************************************\
 *      H264VDEC_OmxFreeBufferWrongPort Function Prototype
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


MX_Result H264VDEC_OmxFreeBufferWrongPort(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine);


/******************************************************************************\
 *      H264VDEC_OmxFreeBufferIdleState Function Prototype
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


MX_Result H264VDEC_OmxFreeBufferIdleState(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine);


/******************************************************************************\
 *      H264VDEC_SetParameterOnce Function Prototype
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

MX_Result H264VDEC_SetParameterOnce(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine);


/******************************************************************************\
 *      H264VDEC_SetParameterNullCfgStruct Function Prototype
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

MX_Result H264VDEC_SetParameterNullCfgStruct(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine);


/******************************************************************************\
 *      H264VDEC_SetParameterOnce Function Prototype
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

MX_Result H264VDEC_SetParameterNullHandle(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine);


/******************************************************************************\
 *      H264VDEC_SetParameterVerMismatch Function Prototype
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

MX_Result H264VDEC_SetParameterVerMismatch(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine);


/******************************************************************************\
 *      H264VDEC_SetParameterTimeOut Function Prototype
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

MX_Result H264VDEC_SetParameterTimeOut(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine);


/******************************************************************************\
 *      H264VDEC_SetParameterUnSupportedSettings Function Prototype
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

MX_Result H264VDEC_SetParameterUnSupportedSettings(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine);


/******************************************************************************\
 *      H264VDEC_SetParameterUnSupportedIndex Function Prototype
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

MX_Result H264VDEC_SetParameterUnSupportedIndex(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine);


/******************************************************************************\
 *      H264VDEC_SetParameterWrongPort Function Prototype
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

MX_Result H264VDEC_SetParameterWrongPort(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine);


/******************************************************************************\
 *      H264VDEC_SetParameterIdleState Function Prototype
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

MX_Result H264VDEC_SetParameterIdleState(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine);


/******************************************************************************\
 *      H264VDEC_SetConfigOnce Function Prototype
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

MX_Result H264VDEC_SetConfigOnce(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine);


/******************************************************************************\
 *      H264VDEC_SetConfigNullCfgStruct Function Prototype
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

MX_Result H264VDEC_SetConfigNullCfgStruct(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine);


/******************************************************************************\
 *      H264VDEC_SetConfigOnce Function Prototype
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

MX_Result H264VDEC_SetConfigNullHandle(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine);


/******************************************************************************\
 *      H264VDEC_SetConfigVerMismatch Function Prototype
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

MX_Result H264VDEC_SetConfigVerMismatch(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine);


/******************************************************************************\
 *      H264VDEC_SetConfigTimeOut Function Prototype
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

MX_Result H264VDEC_SetConfigTimeOut(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine);


/******************************************************************************\
 *      H264VDEC_SetConfigUnSupportedSettings Function Prototype
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

MX_Result H264VDEC_SetConfigUnSupportedSettings(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine);


/******************************************************************************\
 *      H264VDEC_SetConfigUnSupportedIndex Function Prototype
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

MX_Result H264VDEC_SetConfigUnSupportedIndex(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine);


/******************************************************************************\
 *      H264VDEC_SetConfigWrongPort Function Prototype
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

MX_Result H264VDEC_SetConfigWrongPort(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine);


/******************************************************************************\
 *      H264VDEC_GetParameterOnce Function Prototype
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

MX_Result H264VDEC_GetParameterOnce(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine);


/******************************************************************************\
 *      H264VDEC_GetParameterNullCfgStruct Function Prototype
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

MX_Result H264VDEC_GetParameterNullCfgStruct(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine);


/******************************************************************************\
 *      H264VDEC_GetParameterOnce Function Prototype
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

MX_Result H264VDEC_GetParameterNullHandle(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine);


/******************************************************************************\
 *      H264VDEC_GetParameterVerMismatch Function Prototype
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

MX_Result H264VDEC_GetParameterVerMismatch(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine);


/******************************************************************************\
 *      H264VDEC_GetParameterTimeOut Function Prototype
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

MX_Result H264VDEC_GetParameterTimeOut(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine);


/******************************************************************************\
 *      H264VDEC_GetParameterUnSupportedSettings Function Prototype
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

MX_Result H264VDEC_GetParameterUnSupportedSettings(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine);


/******************************************************************************\
 *      H264VDEC_GetParameterUnSupportedIndex Function Prototype
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

MX_Result H264VDEC_GetParameterUnSupportedIndex(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine);


/******************************************************************************\
 *      H264VDEC_GetParameterWrongPort Function Prototype
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

MX_Result H264VDEC_GetParameterWrongPort(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine);


/******************************************************************************\
 *      H264VDEC_GetParameterIdleState Function Prototype
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

MX_Result H264VDEC_GetParameterIdleState(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine);


/******************************************************************************\
 *      H264VDEC_GetConfigOnce Function Prototype
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

MX_Result H264VDEC_GetConfigOnce(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine);


/******************************************************************************\
 *      H264VDEC_GetConfigNullCfgStruct Function Prototype
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

MX_Result H264VDEC_GetConfigNullCfgStruct(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine);


/******************************************************************************\
 *      H264VDEC_GetConfigOnce Function Prototype
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

MX_Result H264VDEC_GetConfigNullHandle(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine);


/******************************************************************************\
 *      H264VDEC_GetConfigVerMismatch Function Prototype
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

MX_Result H264VDEC_GetConfigVerMismatch(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine);


/******************************************************************************\
 *      H264VDEC_GetConfigTimeOut Function Prototype
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

MX_Result H264VDEC_GetConfigTimeOut(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine);


/******************************************************************************\
 *      H264VDEC_GetConfigUnSupportedSettings Function Prototype
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

MX_Result H264VDEC_GetConfigUnSupportedSettings(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine);


/******************************************************************************\
 *      H264VDEC_GetConfigUnSupportedIndex Function Prototype
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

MX_Result H264VDEC_GetConfigUnSupportedIndex(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine);


/******************************************************************************\
 *      H264VDEC_GetConfigWrongPort Function Prototype
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

MX_Result H264VDEC_GetConfigWrongPort(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine);


/******************************************************************************\
 *      H264VDEC_OmxEmptyThisBufferOnce Function Prototype
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


MX_Result H264VDEC_OmxEmptyThisBufferOnce(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine);


/******************************************************************************\
 *      H264VDEC_OmxEmptyThisBufferNullHandle Function Prototype
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


MX_Result H264VDEC_OmxEmptyThisBufferNullHandle(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine);


/******************************************************************************\
 *      H264VDEC_OmxEmptyThisBufferTimeOut Function Prototype
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


MX_Result H264VDEC_OmxEmptyThisBufferTimeOut(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine);


/******************************************************************************\
 *      H264VDEC_OmxEmptyThisBufferIdleState Function Prototype
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


MX_Result H264VDEC_OmxEmptyThisBufferIdleState(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine);


/******************************************************************************\
 *      H264VDEC_OmxEmptyThisBufferWrongPort Function Prototype
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


MX_Result H264VDEC_OmxEmptyThisBufferWrongPort(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine);


/******************************************************************************\
 *      H264VDEC_OmxFillThisBufferOnce Function Prototype
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


MX_Result H264VDEC_OmxFillThisBufferOnce(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine);


/******************************************************************************\
 *      H264VDEC_OmxFillThisBufferNullHandle Function Prototype
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


MX_Result H264VDEC_OmxFillThisBufferNullHandle(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine);


/******************************************************************************\
 *      H264VDEC_OmxFillThisBufferTimeOut Function Prototype
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


MX_Result H264VDEC_OmxFillThisBufferTimeOut(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine);


/******************************************************************************\
 *      H264VDEC_OmxFillThisBufferIdleState Function Prototype
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


MX_Result H264VDEC_OmxFillThisBufferIdleState(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine);


/******************************************************************************\
 *      H264VDEC_OmxFillThisBufferWrongPort Function Prototype
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


MX_Result H264VDEC_OmxFillThisBufferWrongPort(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine);


/*----------------------------- end of file ---------------------------------*/
