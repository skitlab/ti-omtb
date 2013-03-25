/*
 * omtbH264VencApiTest.h
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
 *      H264VENC_OmxAllocUseBufferOnce Function Prototype
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

MX_Result H264VENC_OmxAllocUseBufferOnce(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine);


/******************************************************************************\
 *      H264VENC_OmxAllocUseBufferInsuffResources Function Prototype
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

MX_Result H264VENC_OmxAllocUseBufferInsuffResources(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine);


/******************************************************************************\
 *      H264VENC_OmxAllocUseBufferNullBufferHdr Function Prototype
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

MX_Result H264VENC_OmxAllocUseBufferNullBufferHdr(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine);


/******************************************************************************\
 *      H264VENC_OmxAllocUseBufferNullHandle Function Prototype
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

MX_Result H264VENC_OmxAllocUseBufferNullHandle(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine);


/******************************************************************************\
 *      H264VENC_OmxAllocUseBufferVerMismatch Function Prototype
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

MX_Result H264VENC_OmxAllocUseBufferVerMismatch(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine);


/******************************************************************************\
 *      H264VENC_OmxAllocUseBufferTimeOut Function Prototype
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

MX_Result H264VENC_OmxAllocUseBufferTimeOut(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine);


/******************************************************************************\
 *      H264VENC_OmxAllocUseBufferWrongPort Function Prototype
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

MX_Result H264VENC_OmxAllocUseBufferWrongPort(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine);


/******************************************************************************\
 *      H264VENC_OmxAllocUseBufferIdleState Function Definition
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

MX_Result H264VENC_OmxAllocUseBufferIdleState(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine);


/******************************************************************************\
 *      H264VENC_OmxFreeBufferOnce Function Prototype
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


MX_Result H264VENC_OmxFreeBufferOnce(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine);


/******************************************************************************\
 *      H264VENC_OmxFreeBufferInsuffResources Function Prototype
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


MX_Result H264VENC_OmxFreeBufferInsuffResources(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine);


/******************************************************************************\
 *      H264VENC_OmxFreeBufferNullBufferHdr Function Prototype
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


MX_Result H264VENC_OmxFreeBufferNullBufferHdr(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine);


/******************************************************************************\
 *      H264VENC_OmxFreeBufferNullHandle Function Prototype
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


MX_Result H264VENC_OmxFreeBufferNullHandle(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine);


/******************************************************************************\
 *      H264VENC_OmxFreeBufferVerMismatch Function Prototype
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


MX_Result H264VENC_OmxFreeBufferVerMismatch(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine);


/******************************************************************************\
 *      H264VENC_OmxFreeBufferTimeOut Function Prototype
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


MX_Result H264VENC_OmxFreeBufferTimeOut(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine);


/******************************************************************************\
 *      H264VENC_OmxFreeBufferWrongPort Function Prototype
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


MX_Result H264VENC_OmxFreeBufferWrongPort(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine);


/******************************************************************************\
 *      H264VENC_OmxFreeBufferIdleState Function Prototype
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


MX_Result H264VENC_OmxFreeBufferIdleState(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine);


/******************************************************************************\
 *      H264VENC_SetParameterOnce Function Prototype
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

MX_Result H264VENC_SetParameterOnce(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine);


/******************************************************************************\
 *      H264VENC_SetParameterNullCfgStruct Function Prototype
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

MX_Result H264VENC_SetParameterNullCfgStruct(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine);


/******************************************************************************\
 *      H264VENC_SetParameterOnce Function Prototype
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

MX_Result H264VENC_SetParameterNullHandle(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine);


/******************************************************************************\
 *      H264VENC_SetParameterVerMismatch Function Prototype
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

MX_Result H264VENC_SetParameterVerMismatch(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine);


/******************************************************************************\
 *      H264VENC_SetParameterTimeOut Function Prototype
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

MX_Result H264VENC_SetParameterTimeOut(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine);


/******************************************************************************\
 *      H264VENC_SetParameterUnSupportedSettings Function Prototype
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

MX_Result H264VENC_SetParameterUnSupportedSettings(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine);


/******************************************************************************\
 *      H264VENC_SetParameterUnSupportedIndex Function Prototype
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

MX_Result H264VENC_SetParameterUnSupportedIndex(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine);


/******************************************************************************\
 *      H264VENC_SetParameterWrongPort Function Prototype
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

MX_Result H264VENC_SetParameterWrongPort(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine);


/******************************************************************************\
 *      H264VENC_SetParameterIdleState Function Prototype
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

MX_Result H264VENC_SetParameterIdleState(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine);


/******************************************************************************\
 *      H264VENC_SetConfigOnce Function Prototype
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

MX_Result H264VENC_SetConfigOnce(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine);


/******************************************************************************\
 *      H264VENC_SetConfigNullCfgStruct Function Prototype
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

MX_Result H264VENC_SetConfigNullCfgStruct(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine);


/******************************************************************************\
 *      H264VENC_SetConfigNullHandle Function Prototype
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

MX_Result H264VENC_SetConfigNullHandle(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine);


/******************************************************************************\
 *      H264VENC_SetConfigVerMismatch Function Prototype
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

MX_Result H264VENC_SetConfigVerMismatch(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine);


/******************************************************************************\
 *      H264VENC_SetConfigTimeOut Function Prototype
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

MX_Result H264VENC_SetConfigTimeOut(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine);


/******************************************************************************\
 *      H264VENC_SetConfigUnSupportedSettings Function Prototype
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

MX_Result H264VENC_SetConfigUnSupportedSettings(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine);


/******************************************************************************\
 *      H264VENC_SetConfigUnSupportedIndex Function Prototype
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

MX_Result H264VENC_SetConfigUnSupportedIndex(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine);


/******************************************************************************\
 *      H264VENC_SetConfigWrongPort Function Prototype
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

MX_Result H264VENC_SetConfigWrongPort(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine);


/******************************************************************************\
 *      H264VENC_GetParameterOnce Function Prototype
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

MX_Result H264VENC_GetParameterOnce(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine);


/******************************************************************************\
 *      H264VENC_GetParameterNullCfgStruct Function Prototype
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

MX_Result H264VENC_GetParameterNullCfgStruct(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine);


/******************************************************************************\
 *      H264VENC_GetParameterOnce Function Prototype
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

MX_Result H264VENC_GetParameterNullHandle(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine);


/******************************************************************************\
 *      H264VENC_GetParameterVerMismatch Function Prototype
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

MX_Result H264VENC_GetParameterVerMismatch(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine);


/******************************************************************************\
 *      H264VENC_GetParameterTimeOut Function Prototype
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

MX_Result H264VENC_GetParameterTimeOut(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine);


/******************************************************************************\
 *      H264VENC_GetParameterUnSupportedSettings Function Prototype
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

MX_Result H264VENC_GetParameterUnSupportedSettings(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine);


/******************************************************************************\
 *      H264VENC_GetParameterUnSupportedIndex Function Prototype
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

MX_Result H264VENC_GetParameterUnSupportedIndex(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine);


/******************************************************************************\
 *      H264VENC_GetParameterWrongPort Function Prototype
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

MX_Result H264VENC_GetParameterWrongPort(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine);


/******************************************************************************\
 *      H264VENC_GetParameterIdleState Function Prototype
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

MX_Result H264VENC_GetParameterIdleState(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine);


/******************************************************************************\
 *      H264VENC_GetConfigOnce Function Prototype
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

MX_Result H264VENC_GetConfigOnce(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine);


/******************************************************************************\
 *      H264VENC_GetConfigNullCfgStruct Function Prototype
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

MX_Result H264VENC_GetConfigNullCfgStruct(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine);


/******************************************************************************\
 *      H264VENC_GetConfigNullHandle Function Prototype
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

MX_Result H264VENC_GetConfigNullHandle(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine);


/******************************************************************************\
 *      H264VENC_GetConfigVerMismatch Function Prototype
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

MX_Result H264VENC_GetConfigVerMismatch(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine);


/******************************************************************************\
 *      H264VENC_GetConfigTimeOut Function Prototype
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

MX_Result H264VENC_GetConfigTimeOut(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine);


/******************************************************************************\
 *      H264VENC_GetConfigUnSupportedSettings Function Prototype
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

MX_Result H264VENC_GetConfigUnSupportedSettings(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine);


/******************************************************************************\
 *      H264VENC_GetConfigUnSupportedIndex Function Prototype
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

MX_Result H264VENC_GetConfigUnSupportedIndex(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine);


/******************************************************************************\
 *      H264VENC_GetConfigWrongPort Function Prototype
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

MX_Result H264VENC_GetConfigWrongPort(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine);


/******************************************************************************\
 *      H264VENC_OmxEmptyThisBufferOnce Function Prototype
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


MX_Result H264VENC_OmxEmptyThisBufferOnce(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine);


/******************************************************************************\
 *      H264VENC_OmxEmptyThisBufferNullHandle Function Prototype
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


MX_Result H264VENC_OmxEmptyThisBufferNullHandle(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine);


/******************************************************************************\
 *      H264VENC_OmxEmptyThisBufferTimeOut Function Prototype
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


MX_Result H264VENC_OmxEmptyThisBufferTimeOut(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine);


/******************************************************************************\
 *      H264VENC_OmxEmptyThisBufferIdleState Function Prototype
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


MX_Result H264VENC_OmxEmptyThisBufferIdleState(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine);


/******************************************************************************\
 *      H264VENC_OmxEmptyThisBufferWrongPort Function Prototype
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


MX_Result H264VENC_OmxEmptyThisBufferWrongPort(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine);


/******************************************************************************\
 *      H264VENC_OmxFillThisBufferOnce Function Prototype
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


MX_Result H264VENC_OmxFillThisBufferOnce(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine);


/******************************************************************************\
 *      H264VENC_OmxFillThisBufferNullHandle Function Prototype
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


MX_Result H264VENC_OmxFillThisBufferNullHandle(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine);


/******************************************************************************\
 *      H264VENC_OmxFillThisBufferTimeOut Function Prototype
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


MX_Result H264VENC_OmxFillThisBufferTimeOut(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine);


/******************************************************************************\
 *      H264VENC_OmxFillThisBufferIdleState Function Prototype
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


MX_Result H264VENC_OmxFillThisBufferIdleState(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine);


/******************************************************************************\
 *      H264VENC_OmxFillThisBufferWrongPort Function Prototype
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


MX_Result H264VENC_OmxFillThisBufferWrongPort(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine);


/*----------------------------- end of file ---------------------------------*/
