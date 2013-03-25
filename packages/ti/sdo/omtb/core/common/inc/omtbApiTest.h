/*
 * omtbApiTest.h
 *
 * This file contains omtb prototypes/declarations for OMX API dispatchers for
 * API validation.
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

#ifndef __OMTB_API_TEST_H__
#define __OMTB_API_TEST_H__


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
 *      Data type Definitions
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
 *      OMTB_APITestEventHandler callback Function Prototype
\******************************************************************************/
/**
 *
 *  @brief    Event handler Callback
 *
 *  @param in:
 *            hComponent: Component Handle
 *
 *            pAppData  : Pointer to Private Data Structure
 *
 *            eEvent    : Variable to OMX_EVENTTYPE enum
 *
 *            nData1     : data associated with event
 *
 *            nData2     : data associated with event
 *
 *            pEventData: Extra Data associated with the event
 *
 *  @return   err       : OMX_ErrorType
 *
 */

OMX_ERRORTYPE OMTB_APITestEventHandler(
  OMX_OUT OMX_HANDLETYPE hComponent,
  OMX_OUT OMX_PTR pAppData,
  OMX_OUT OMX_EVENTTYPE eEvent,
  OMX_OUT OMX_U32 nData1,
  OMX_OUT OMX_U32 nData2,
  OMX_OUT OMX_PTR pEventData);


/******************************************************************************\
 *      OMTB_APITestEmptyBufferDone callback Function Prototype
\******************************************************************************/
/**
 *
 *  @brief    EmptyBufferDone Callback
 *
 *  @param in:
 *            hComponent: Component Handle
 *
 *            ptrAppData: Pointer to Private Data Structure
 *
 *            pBuffer   : Pointer to i/p Buffer
 *
 *  @return   err       : OMX_ErrorType
 *
 */

OMX_ERRORTYPE OMTB_APITestEmptyBufferDone(
  OMX_HANDLETYPE hComponent,
  OMX_PTR ptrAppData,
  OMX_BUFFERHEADERTYPE* pBuffer);


/******************************************************************************\
 *      OMTB_APITestFillBufferDone callback Function Prototype
\******************************************************************************/
/**
 *
 *  @brief    FillBufferDone Callback
 *
 *  @param in:
 *            hComponent: Component Handle
 *            ptrAppData: Pointer to Private Data Structure
 *            pBuffer   : Pointer to o/p Buffer
 *
 *  @return   err       : OMX_ErrorType
 *
 */

OMX_ERRORTYPE OMTB_APITestFillBufferDone(
  OMX_HANDLETYPE hComponent,
  OMX_PTR ptrAppData,
  OMX_BUFFERHEADERTYPE* pBuffer);


/******************************************************************************\
 *      OMTB_OmxInitOnce Function Prototype
\******************************************************************************/
/**
 *
 *  @brief    This Function performs OMX_Init API testing.
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
OMTB_OmxInitOnce(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine
);


/******************************************************************************\
 *      OMTB_OmxInitTwice Function Prototype
\******************************************************************************/
/**
 *
 *  @brief    This Function performs OMX_Init API testing.
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
OMTB_OmxInitTwice(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine
);


/******************************************************************************\
 *      OMTB_OmxInitInsuffResources Function Prototype
\******************************************************************************/
/**
 *
 *  @brief    This Function performs OMX_Init API testing.
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
OMTB_OmxInitInsuffResources(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine
);


/******************************************************************************\
 *      OMTB_OmxInitVerMismatch Function Prototype
\******************************************************************************/
/**
 *
 *  @brief    This Function performs OMX_Init API testing.
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
OMTB_OmxInitVerMismatch(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine
);


/******************************************************************************\
 *      OMTB_OmxInitTimeOut Function Prototype
\******************************************************************************/
/**
 *
 *  @brief    This Function performs OMX_Init API testing.
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
OMTB_OmxInitTimeOut(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine
);


/******************************************************************************\
 *      OMTB_OmxDeInitOnce Function Prototype
\******************************************************************************/
/**
 *
 *  @brief    This Function performs OMX_DeInit API testing.
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
OMTB_OmxDeInitOnce(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine
);


/******************************************************************************\
 *      OMTB_OmxDeInitTwice Function Prototype
\******************************************************************************/
/**
 *
 *  @brief    This Function performs OMX_DeInit API testing.
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
OMTB_OmxDeInitTwice(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine
);


/******************************************************************************\
 *      OMTB_OmxDeInitVerMismatch Function Prototype
\******************************************************************************/
/**
 *
 *  @brief    This Function performs OMX_DeInit API testing.
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
OMTB_OmxDeInitVerMismatch(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine
);


/******************************************************************************\
 *      OMTB_OmxDeInitTimeOut Function Prototype
\******************************************************************************/
/**
 *
 *  @brief    This Function performs OMX_DeInit API testing.
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
OMTB_OmxDeInitTimeOut(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine
);


/******************************************************************************\
 *      OMTB_OmxDeInitWithoutFreeHandle Function Prototype
\******************************************************************************/
/**
 *
 *  @brief    This Function performs OMX_DeInit API testing.
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
OMTB_OmxDeInitWithoutFreeHandle(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine
);


/******************************************************************************\
 *      OMTB_OmxGetHandleOnce Function Prototype
\******************************************************************************/
/**
 *
 *  @brief    This Function performs OMX_GetHandle API testing.
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
OMTB_OmxGetHandleOnce(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine
);


/******************************************************************************\
 *      OMTB_OmxGetHandleTwice Function Prototype
\******************************************************************************/
/**
 *
 *  @brief    This Function performs OMX_GetHandle API testing.
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
OMTB_OmxGetHandleTwice(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine
);


/******************************************************************************\
 *      OMTB_OmxGetHandleInvCompName Function Prototype
\******************************************************************************/
/**
 *
 *  @brief    This Function performs OMX_GetHandle API testing.
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
OMTB_OmxGetHandleInvCompName(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine
);


/******************************************************************************\
 *      OMTB_OmxGetHandleCompNotFound Function Prototype
\******************************************************************************/
/**
 *
 *  @brief    This Function performs OMX_GetHandle API testing.
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
OMTB_OmxGetHandleCompNotFound(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine
);


/******************************************************************************\
 *      OMTB_OmxGetHandleNoCompInitFxn Function Prototype
\******************************************************************************/
/**
 *
 *  @brief    This Function performs OMX_GetHandle API testing.
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
OMTB_OmxGetHandleNoCompInitFxn(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine
);


/******************************************************************************\
 *      OMTB_OmxGetHandleNullCb Function Prototype
\******************************************************************************/
/**
 *
 *  @brief    This Function performs OMX_GetHandle API testing.
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
OMTB_OmxGetHandleNullCb(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine
);


/******************************************************************************\
 *      OMTB_OmxGetHandleNullHandle Function Prototype
\******************************************************************************/
/**
 *
 *  @brief    This Function performs OMX_GetHandle API testing.
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
OMTB_OmxGetHandleNullHandle(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine
);


/******************************************************************************\
 *      OMTB_OmxGetHandleVerMismatch Function Prototype
\******************************************************************************/
/**
 *
 *  @brief    This Function performs OMX_GetHandle API testing.
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
OMTB_OmxGetHandleVerMismatch(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine
);


/******************************************************************************\
 *      OMTB_OmxGetHandleTimeOut Function Prototype
\******************************************************************************/
/**
 *
 *  @brief    This Function performs OMX_GetHandle API testing.
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
OMTB_OmxGetHandleTimeOut(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine
);


/******************************************************************************\
 *      OMTB_OmxGetHandleWithoutCoreInit Function Prototype
\******************************************************************************/
/**
 *
 *  @brief    This Function performs OMX_GetHandle API testing.
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
OMTB_OmxGetHandleWithoutCoreInit(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine
);


/******************************************************************************\
 *      OMTB_OmxFreeHandleOnce Function Prototype
\******************************************************************************/
/**
 *
 *  @brief    This Function performs OMX_FreeHandle API testing.
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
OMTB_OmxFreeHandleOnce(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine
);


/******************************************************************************\
 *      OMTB_OmxFreeHandleVerMismatch Function Prototype
\******************************************************************************/
/**
 *
 *  @brief    This Function performs OMX_FreeHandle API testing.
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
OMTB_OmxFreeHandleVerMismatch(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine
);


/******************************************************************************\
 *      OMTB_OmxFreeHandleTimeOut Function Prototype
\******************************************************************************/
/**
 *
 *  @brief    This Function performs OMX_FreeHandle API testing.
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
OMTB_OmxFreeHandleTimeOut(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine
);


/******************************************************************************\
 *      OMTB_OmxFreeHandleNullHandle Function Prototype
\******************************************************************************/
/**
 *
 *  @brief    This Function performs OMX_FreeHandle API testing.
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
OMTB_OmxFreeHandleNullHandle(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine
);


/******************************************************************************\
 *      OMTB_OmxComponentNameEnumOnce Function Prototype
\******************************************************************************/
/**
 *
 *  @brief    This Function performs OMX_ComponentNameEnum API testing.
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
OMTB_OmxComponentNameEnumOnce(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine
);


/******************************************************************************\
 *      OMTB_OmxComponentNameEnumNullCompName Function Prototype
\******************************************************************************/
/**
 *
 *  @brief    This Function performs OMX_ComponentNameEnum API testing.
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
OMTB_OmxComponentNameEnumNullCompName(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine
);


/******************************************************************************\
 *      OMTB_OmxComponentNameEnumNoMore Function Prototype
\******************************************************************************/
/**
 *
 *  @brief    This Function performs OMX_ComponentNameEnum API testing.
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
OMTB_OmxComponentNameEnumNoMore(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine
);


/******************************************************************************\
 *      OMTB_OmxComponentNameEnumVerMismatch Function Prototype
\******************************************************************************/
/**
 *
 *  @brief    This Function performs OMX_ComponentNameEnum API testing.
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
OMTB_OmxComponentNameEnumVerMismatch(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine
);


/******************************************************************************\
 *      OMTB_OmxGetRolesOfComponentOnce Function Prototype
\******************************************************************************/
/**
 *
 *  @brief    This Function performs OMX_GetRolesOfComponent API testing.
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
OMTB_OmxGetRolesOfComponentOnce(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine
);


/******************************************************************************\
 *      OMTB_OmxGetRolesOfComponentNullCompName Function Prototype
\******************************************************************************/
/**
 *
 *  @brief    This Function performs OMX_GetRolesOfComponent API testing.
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
OMTB_OmxGetRolesOfComponentNullCompName(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine
);


/******************************************************************************\
 *      OMTB_OmxGetRolesOfComponentNullNumComp Function Prototype
\******************************************************************************/
/**
 *
 *  @brief    This Function performs OMX_GetRolesOfComponent API testing.
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
OMTB_OmxGetRolesOfComponentNullNumComp(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine
);


/******************************************************************************\
 *      OMTB_OmxGetRolesOfComponentInvCompName Function Prototype
\******************************************************************************/
/**
 *
 *  @brief    This Function performs OMX_GetRolesOfComponent API testing.
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
OMTB_OmxGetRolesOfComponentInvCompName(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine
);


/******************************************************************************\
 *      OMTB_OmxGetComponentsOfRoleOnce Function Prototype
\******************************************************************************/
/**
 *
 *  @brief    This Function performs OMX_GetComponentsOfRole API testing.
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
OMTB_OmxGetComponentsOfRoleOnce(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine
);


/******************************************************************************\
 *      OMTB_OmxGetComponentsOfRoleNullRole Function Prototype
\******************************************************************************/
/**
 *
 *  @brief    This Function performs OMX_GetComponentsOfRole API testing.
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
OMTB_OmxGetComponentsOfRoleNullRole(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine
);


/******************************************************************************\
 *      OMTB_OmxGetComponentsOfRoleNullNumComp Function Prototype
\******************************************************************************/
/**
 *
 *  @brief    This Function performs OMX_GetComponentsOfRole API testing.
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
OMTB_OmxGetComponentsOfRoleNullNumComp(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine
);


/******************************************************************************\
 *      OMTB_OmxGetCompVersionOnce Function Prototype
\******************************************************************************/
/**
 *
 *  @brief    This Function performs OMX_GetComponentVersion API testing.
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
OMTB_OmxGetCompVersionOnce(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine
);


/******************************************************************************\
 *      OMTB_OmxGetCompVersionNullHandle Function Prototype
\******************************************************************************/
/**
 *
 *  @brief    This Function performs OMX_GetComponentVersion API testing.
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
OMTB_OmxGetCompVersionNullHandle(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine
);


/******************************************************************************\
 *      OMTB_OmxGetCompVersionNullCompName Function Prototype
\******************************************************************************/
/**
 *
 *  @brief    This Function performs OMX_GetComponentVersion API testing.
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
OMTB_OmxGetCompVersionNullCompName(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine
);


/******************************************************************************\
 *      OMTB_OmxGetCompVersionNullCompVersion Function Prototype
\******************************************************************************/
/**
 *
 *  @brief    This Function performs OMX_GetComponentVersion API testing.
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
OMTB_OmxGetCompVersionNullCompVersion(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine
);


/******************************************************************************\
 *      OMTB_OmxGetCompVersionNullSpecVersion Function Prototype
\******************************************************************************/
/**
 *
 *  @brief    This Function performs OMX_GetComponentVersion API testing.
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
OMTB_OmxGetCompVersionNullSpecVersion(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine
);


/******************************************************************************\
 *      OMTB_OmxGetCompVersionVerMismatch Function Prototype
\******************************************************************************/
/**
 *
 *  @brief    This Function performs OMX_GetComponentVersion API testing.
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
OMTB_OmxGetCompVersionVerMismatch(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine
);


/******************************************************************************\
 *      OMTB_OmxGetStateOnce Function Prototype
\******************************************************************************/
/**
 *
 *  @brief    This Function performs OMX_GetState API testing.
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
OMTB_OmxGetStateOnce(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine
);


/******************************************************************************\
 *      OMTB_OmxGetStateNullHandle Function Prototype
\******************************************************************************/
/**
 *
 *  @brief    This Function performs OMX_GetState API testing.
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
OMTB_OmxGetStateNullHandle(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine
);


/******************************************************************************\
 *      OMTB_OmxGetStateVerMismatch Function Prototype
\******************************************************************************/
/**
 *
 *  @brief    This Function performs OMX_GetState API testing.
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
OMTB_OmxGetStateVerMismatch(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine
);


/******************************************************************************\
 *      OMTB_OmxGetStateTimeOut Function Prototype
\******************************************************************************/
/**
 *
 *  @brief    This Function performs OMX_GetState API testing.
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
OMTB_OmxGetStateTimeOut(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine
);


/******************************************************************************\
 *      OMTB_OmxGetExtensionIndexOnce Function Prototype
\******************************************************************************/
/**
 *
 *  @brief    This Function performs OMX_GetExtensionIndex API testing.
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
OMTB_OmxGetExtensionIndexOnce(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine
);


/******************************************************************************\
 *      OMTB_OmxGetExtensionIndexNullHandle Function Prototype
\******************************************************************************/
/**
 *
 *  @brief    This Function performs OMX_GetExtensionIndex API testing.
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
OMTB_OmxGetExtensionIndexNullHandle(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine
);


/******************************************************************************\
 *      OMTB_OmxGetExtensionIndexVerMismatch Function Prototype
\******************************************************************************/
/**
 *
 *  @brief    This Function performs OMX_GetExtensionIndex API testing.
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
OMTB_OmxGetExtensionIndexVerMismatch(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine
);


/******************************************************************************\
 *      OMTB_OmxGetExtensionIndexTimeOut Function Prototype
\******************************************************************************/
/**
 *
 *  @brief    This Function performs OMX_GetExtensionIndex API testing.
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
OMTB_OmxGetExtensionIndexTimeOut(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine
);


/******************************************************************************\
 *      OMTB_OmxGetExtensionIndexWrongVendorStr Function Prototype
\******************************************************************************/
/**
 *
 *  @brief    This Function performs OMX_GetExtensionIndex API testing.
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
OMTB_OmxGetExtensionIndexWrongVendorStr(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine
);


/******************************************************************************\
 *      OMTB_OmxSetupTunnelOnce Function Prototype
\******************************************************************************/
/**
 *
 *  @brief    This Function performs OMX_SetupTunnel API testing.
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
OMTB_OmxSetupTunnelOnce(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine
);


/******************************************************************************\
 *      OMTB_OmxSetupTunnelNullHandle Function Prototype
\******************************************************************************/
/**
 *
 *  @brief    This Function performs OMX_SetupTunnel API testing.
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
OMTB_OmxSetupTunnelNullHandle(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine
);


/******************************************************************************\
 *      OMTB_OmxSetupTunnelWrongPortNum Function Prototype
\******************************************************************************/
/**
 *
 *  @brief    This Function performs OMX_SetupTunnel API testing.
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
OMTB_OmxSetupTunnelWrongPortNum(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine
);


/******************************************************************************\
 *      OMTB_OmxSetupTunnelNotImplemented Function Prototype
\******************************************************************************/
/**
 *
 *  @brief    This Function performs OMX_SetupTunnel API testing.
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
OMTB_OmxSetupTunnelNotImplemented(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine
);


/******************************************************************************\
 *      OMTB_OmxSetupTunnelPortIncompatible Function Prototype
\******************************************************************************/
/**
 *
 *  @brief    This Function performs OMX_SetupTunnel API testing.
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
OMTB_OmxSetupTunnelPortIncompatible(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine
);


/******************************************************************************\
 *      OMTB_OmxSetupTunnelVerMismatch Function Prototype
\******************************************************************************/
/**
 *
 *  @brief    This Function performs OMX_SetupTunnel API testing.
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
OMTB_OmxSetupTunnelVerMismatch(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine
);


/******************************************************************************\
 *      OMTB_OmxSetupTunnelTimeOut Function Prototype
\******************************************************************************/
/**
 *
 *  @brief    This Function performs OMX_SetupTunnel API testing.
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
OMTB_OmxSetupTunnelTimeOut(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine
);


/******************************************************************************\
 *      OMTB_OmxSendCommandOnce Function Prototype
\******************************************************************************/
/**
 *
 *  @brief    This Function performs OMX_SendCommand API testing.
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
OMTB_OmxSendCommandOnce(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine
);


/******************************************************************************\
 *      OMTB_OmxSendCommandInsuffResources Function Prototype
\******************************************************************************/
/**
 *
 *  @brief    This Function performs OMX_SendCommand API testing.
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
OMTB_OmxSendCommandInsuffResources(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine
);


/******************************************************************************\
 *      OMTB_OmxSendCommandNullHandle Function Prototype
\******************************************************************************/
/**
 *
 *  @brief    This Function performs OMX_SendCommand API testing.
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
OMTB_OmxSendCommandNullHandle(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine
);


/******************************************************************************\
 *      OMTB_OmxSendCommandInvCommand Function Prototype
\******************************************************************************/
/**
 *
 *  @brief    This Function performs OMX_SendCommand API testing.
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
OMTB_OmxSendCommandInvCommand(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine
);


/******************************************************************************\
 *      OMTB_OmxSendCommandTimeOut Function Prototype
\******************************************************************************/
/**
 *
 *  @brief    This Function performs OMX_SendCommand API testing.
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
OMTB_OmxSendCommandTimeOut(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine
);


/******************************************************************************\
 *      OMTB_OmxSendCommandOnWrongPort Function Prototype
\******************************************************************************/
/**
 *
 *  @brief    This Function performs OMX_SendCommand API testing.
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
OMTB_OmxSendCommandOnWrongPort(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine
);


/******************************************************************************\
 *      OmxAllocUseBufferOnce Function Definition
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

MX_Result OmxAllocUseBufferOnce(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine);

/******************************************************************************\
 *      OmxAllocUseBufferInsuffResources Function Definition
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

MX_Result OmxAllocUseBufferInsuffResources(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine);
  

/******************************************************************************\
 *      OmxAllocUseBufferNullBufferHdr Function Definition
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

MX_Result OmxAllocUseBufferNullBufferHdr(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine);


/******************************************************************************\
 *      OmxAllocUseBufferNullHandle Function Definition
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

MX_Result OmxAllocUseBufferNullHandle(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine);


/******************************************************************************\
 *      OmxAllocUseBufferVerMismatch Function Definition
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

MX_Result OmxAllocUseBufferVerMismatch(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine);


/******************************************************************************\
 *      OmxAllocUseBufferTimeOut Function Definition
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

MX_Result OmxAllocUseBufferTimeOut(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine);


/******************************************************************************\
 *      OmxAllocUseBufferWrongPort Function Definition
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

MX_Result OmxAllocUseBufferWrongPort(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine);


/******************************************************************************\
 *      OmxAllocUseBufferIdleState Function Definition
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

MX_Result OmxAllocUseBufferIdleState(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine);

/******************************************************************************\
 *      OmxFreeBufferOnce Function Definition
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


MX_Result OmxFreeBufferOnce(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine);


/******************************************************************************\
 *      OmxFreeBufferInsuffResources Function Definition
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


MX_Result OmxFreeBufferInsuffResources(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine);


/******************************************************************************\
 *      OmxFreeBufferNullBufferHdr Function Definition
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


MX_Result OmxFreeBufferNullBufferHdr(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine);


/******************************************************************************\
 *      OmxFreeBufferNullHandle Function Definition
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


MX_Result OmxFreeBufferNullHandle(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine);


/******************************************************************************\
 *      OmxFreeBufferVerMismatch Function Definition
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


MX_Result OmxFreeBufferVerMismatch(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine);


/******************************************************************************\
 *      OmxFreeBufferTimeOut Function Definition
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


MX_Result OmxFreeBufferTimeOut(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine);


/******************************************************************************\
 *      OmxFreeBufferWrongPort Function Definition
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


MX_Result OmxFreeBufferWrongPort(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine);


/******************************************************************************\
 *      OmxFreeBufferIdleState Function Definition
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


MX_Result OmxFreeBufferIdleState(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine);  
  
/******************************************************************************\
 *      OMTB_OmxSetParameterOnce Function Definition
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

MX_Result OMTB_OmxSetParameterOnce(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine);


/******************************************************************************\
 *      OMTB_OmxSetParameterNullCfgStruct Function Definition
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

MX_Result OMTB_OmxSetParameterNullCfgStruct(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine);


/******************************************************************************\
 *      OMTB_OmxSetParameterOnce Function Definition
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

MX_Result OMTB_OmxSetParameterNullHandle(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine);


/******************************************************************************\
 *      OMTB_OmxSetParameterVerMismatch Function Definition
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

MX_Result OMTB_OmxSetParameterVerMismatch(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine);


/******************************************************************************\
 *      OMTB_OmxSetParameterTimeOut Function Definition
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

MX_Result OMTB_OmxSetParameterTimeOut(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine);


/******************************************************************************\
 *      OMTB_OmxSetParameterUnSupportedSettings Function Definition
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

MX_Result OMTB_OmxSetParameterUnSupportedSettings(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine);


/******************************************************************************\
 *      OMTB_OmxSetParameterUnSupportedIndex Function Definition
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

MX_Result OMTB_OmxSetParameterUnSupportedIndex(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine);


/******************************************************************************\
 *      OMTB_OmxSetParameterWrongPort Function Definition
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

MX_Result OMTB_OmxSetParameterWrongPort(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine);


/******************************************************************************\
 *      OMTB_OmxSetParameterIdleState Function Definition
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

MX_Result OMTB_OmxSetParameterIdleState(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine);  
  

/******************************************************************************\
 *      OMTB_OmxSetConfigOnce Function Definition
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

MX_Result OMTB_OmxSetConfigOnce(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine);


/******************************************************************************\
 *      OMTB_OmxSetConfigNullCfgStruct Function Definition
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

MX_Result OMTB_OmxSetConfigNullCfgStruct(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine);


/******************************************************************************\
 *      OMTB_OmxSetConfigOnce Function Definition
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

MX_Result OMTB_OmxSetConfigNullHandle(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine);


/******************************************************************************\
 *      OMTB_OmxSetConfigVerMismatch Function Definition
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

MX_Result OMTB_OmxSetConfigVerMismatch(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine);


/******************************************************************************\
 *      OMTB_OmxSetConfigTimeOut Function Definition
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

MX_Result OMTB_OmxSetConfigTimeOut(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine);  
  

/******************************************************************************\
 *      OMTB_OmxSetConfigUnSupportedSettings Function Definition
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

MX_Result OMTB_OmxSetConfigUnSupportedSettings(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine);

  
/******************************************************************************\
 *      OMTB_OmxSetConfigUnSupportedIndex Function Definition
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

MX_Result OMTB_OmxSetConfigUnSupportedIndex(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine);
  
  
/******************************************************************************\
 *      OMTB_OmxSetConfigWrongPort Function Definition
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

MX_Result OMTB_OmxSetConfigWrongPort(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine);
  

/******************************************************************************\
 *      OMTB_OmxGetParameterOnce Function Definition
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

MX_Result OMTB_OmxGetParameterOnce(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine);


/******************************************************************************\
 *      OMTB_OmxGetParameterNullCfgStruct Function Definition
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

MX_Result OMTB_OmxGetParameterNullCfgStruct(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine);


/******************************************************************************\
 *      OMTB_OmxGetParameterOnce Function Definition
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

MX_Result OMTB_OmxGetParameterNullHandle(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine);


/******************************************************************************\
 *      OMTB_OmxGetParameterVerMismatch Function Definition
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

MX_Result OMTB_OmxGetParameterVerMismatch(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine);



/******************************************************************************\
 *      OMTB_OmxGetParameterTimeOut Function Definition
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

MX_Result OMTB_OmxGetParameterTimeOut(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine);


/******************************************************************************\
 *      OMTB_OmxGetParameterUnSupportedSettings Function Definition
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

MX_Result OMTB_OmxGetParameterUnSupportedSettings(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine);


/******************************************************************************\
 *      OMTB_OmxGetParameterUnSupportedIndex Function Definition
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

MX_Result OMTB_OmxGetParameterUnSupportedIndex(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine);


/******************************************************************************\
 *      OMTB_OmxGetParameterWrongPort Function Definition
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

MX_Result OMTB_OmxGetParameterWrongPort(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine);


/******************************************************************************\
 *      OMTB_OmxGetParameterIdleState Function Definition
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

MX_Result OMTB_OmxGetParameterIdleState(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine);


/******************************************************************************\
 *      OMTB_OmxGetConfigOnce Function Definition
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

MX_Result OMTB_OmxGetConfigOnce(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine);


/******************************************************************************\
 *      OMTB_OmxGetConfigNullCfgStruct Function Definition
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

MX_Result OMTB_OmxGetConfigNullCfgStruct(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine);


/******************************************************************************\
 *      OMTB_OmxGetConfigOnce Function Definition
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

MX_Result OMTB_OmxGetConfigNullHandle(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine);


/******************************************************************************\
 *      OMTB_OmxGetConfigVerMismatch Function Definition
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

MX_Result OMTB_OmxGetConfigVerMismatch(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine);


/******************************************************************************\
 *      OMTB_OmxGetConfigTimeOut Function Definition
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

MX_Result OMTB_OmxGetConfigTimeOut(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine);


/******************************************************************************\
 *      OMTB_OmxGetConfigUnSupportedSettings Function Definition
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

MX_Result OMTB_OmxGetConfigUnSupportedSettings(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine);


/******************************************************************************\
 *      OMTB_OmxGetConfigUnSupportedIndex Function Definition
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

MX_Result OMTB_OmxGetConfigUnSupportedIndex(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine);


/******************************************************************************\
 *      OMTB_OmxGetConfigWrongPort Function Definition
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

MX_Result OMTB_OmxGetConfigWrongPort(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine);


/******************************************************************************\
 *      OMTB_OmxEmptyThisBufferOnce Function Definition
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

MX_Result OMTB_OmxEmptyThisBufferOnce(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine);


/******************************************************************************\
 *      OMTB_OmxEmptyThisBufferNullHandle Function Definition
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


MX_Result OMTB_OmxEmptyThisBufferNullHandle(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine);


/******************************************************************************\
 *      OMTB_OmxEmptyThisBufferTimeOut Function Definition
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


MX_Result OMTB_OmxEmptyThisBufferTimeOut(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine);

/******************************************************************************\
 *      OMTB_OmxEmptyThisBufferIdleState Function Definition
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


MX_Result OMTB_OmxEmptyThisBufferIdleState(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine);


/******************************************************************************\
 *      OMTB_OmxEmptyThisBufferWrongPort Function Definition
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


MX_Result OMTB_OmxEmptyThisBufferWrongPort(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine);


/******************************************************************************\
 *      OMTB_OmxFillThisBufferOnce Function Definition
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


MX_Result OMTB_OmxFillThisBufferOnce(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine);


/******************************************************************************\
 *      OMTB_OmxFillThisBufferNullHandle Function Definition
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


MX_Result OMTB_OmxFillThisBufferNullHandle(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine);


/******************************************************************************\
 *      OMTB_OmxFillThisBufferTimeOut Function Definition
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


MX_Result OMTB_OmxFillThisBufferTimeOut(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine);


/******************************************************************************\
 *      OMTB_OmxFillThisBufferIdleState Function Definition
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


MX_Result OMTB_OmxFillThisBufferIdleState(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine);


/******************************************************************************\
 *      OMTB_OmxFillThisBufferWrongPort Function Definition
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


MX_Result OMTB_OmxFillThisBufferWrongPort(
  MX_DBG_CMD_CONTEXT_T*   pContext,
  MX_DBG_CMD_ENTRY_T*     pCmdEntry,
  char**                  ppCmdLine);

  
#ifdef __cplusplus    /* matches __cplusplus construct above */
 }
#endif

#endif


/*----------------------------- end of file ---------------------------------*/
