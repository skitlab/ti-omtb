/*
 * omtbOmxApiTestCmdEntries.c
 *
 * This file contains command entries for OMX API validation.
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
#include <xdc/runtime/Gate.h>

/* OMX standard header files */
#include "OMX_Core.h"
#include "OMX_Component.h"
#include "OMX_Types.h"


/******************************************************************************\
 *      Customized Includes
\******************************************************************************/

#include "mxDbg.h"
#include "omtbCommon.h"
#include "omtbApi.h"
#include "omtbApiTest.h"


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

/*******************************************************************************
 *  OMX API mode OR Func Mode Command Entries/Tables - api/func
 ******************************************************************************/

/*******************************************************************************
 *      OMX API command entry
 ******************************************************************************/

/* Entry for OMX core init once */

MX_DBG_CMD_ENTRY_T cmdEntryOmtbOmxInitOnce =
{
  "once",
  MX_DBG_CMD_TYPE_VAR_UINT16,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_VALID_PTR,
  0,
  0,
  0,
  0,
  0,
  0,
  NULL,
  OMTB_OmxInitOnce,
  "",
  "<Testcase #> <Component Name> <Result File Name> <wb | ab>",
  "",
  ""
};

/* Entry for OMX core init twice */

MX_DBG_CMD_ENTRY_T cmdEntryOmtbOmxInitTwice =
{
  "twice",
  MX_DBG_CMD_TYPE_VAR_UINT16,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_VALID_PTR,
  0,
  0,
  0,
  0,
  0,
  0,
  NULL,
  OMTB_OmxInitTwice,
  "",
  "<Testcase #> <Component Name> <Result File Name> <wb | ab>",
  "",
  ""
};

/* Entry for OMX core init insuff resources */

MX_DBG_CMD_ENTRY_T cmdEntryOmtbOmxInitInsuffResources =
{
  "insuff_res",
  MX_DBG_CMD_TYPE_VAR_UINT16,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_VALID_PTR,
  0,
  0,
  0,
  0,
  0,
  0,
  NULL,
  OMTB_OmxInitInsuffResources,
  "",
  "<Testcase #> <Component Name> <Result File Name> <wb | ab>",
  "",
  ""
};

/* Entry for OMX core init version mismatch */

MX_DBG_CMD_ENTRY_T cmdEntryOmtbOmxInitVerMismatch =
{
  "ver_mismatch",
  MX_DBG_CMD_TYPE_VAR_UINT16,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_VALID_PTR,
  0,
  0,
  0,
  0,
  0,
  0,
  NULL,
  OMTB_OmxInitVerMismatch,
  "",
  "<Testcase #> <Component Name> <Result File Name> <wb | ab>",
  "",
  ""
};

/* Entry for OMX core init timeout */

MX_DBG_CMD_ENTRY_T cmdEntryOmtbOmxInitTimeOut =
{
  "timeout",
  MX_DBG_CMD_TYPE_VAR_UINT16,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_VALID_PTR,
  0,
  0,
  0,
  0,
  0,
  0,
  NULL,
  OMTB_OmxInitTimeOut,
  "",
  "<Testcase #> <Component Name> <Result File Name> <wb | ab>",
  "",
  ""
};

/* init command list */
MX_DBG_CMD_ENTRY_T* cmdListOmtbOmxInitTest[] =
{
  &cmdEntryOmtbOmxInitOnce,
  &cmdEntryOmtbOmxInitTwice,
  &cmdEntryOmtbOmxInitInsuffResources,
  &cmdEntryOmtbOmxInitVerMismatch,
  &cmdEntryOmtbOmxInitTimeOut,
  NULL
};


/* init command table */
MX_DBG_CMD_TABLE_T cmdTblOmtbOmxInitTest =
{
  MX_DBG_ACCESS_ALL,
  sizeof(cmdListOmtbOmxInitTest) / sizeof(cmdListOmtbOmxInitTest[0]),
  cmdListOmtbOmxInitTest
};

/* Entry for OMX Core Init */

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryOmxInitTest =
{
  "init",
  MX_DBG_CMD_TYPE_CMD_TABLE,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_VALID_PTR,
  0,
  0,
  0,
  0,
  0,
  0,
  &cmdTblOmtbOmxInitTest,
  OMTB_ParseCmdTblEntries,
  "",
  "",
  "",
  ""
};


/* Entry for OMX core init once */

MX_DBG_CMD_ENTRY_T cmdEntryOmtbOmxDeInitOnce =
{
  "once",
  MX_DBG_CMD_TYPE_VAR_UINT16,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_VALID_PTR,
  0,
  0,
  0,
  0,
  0,
  0,
  NULL,
  OMTB_OmxDeInitOnce,
  "",
  "<Testcase #> <Component Name> <Result File Name> <wb | ab>",
  "",
  ""
};

/* Entry for OMX core init twice */

MX_DBG_CMD_ENTRY_T cmdEntryOmtbOmxDeInitTwice =
{
  "twice",
  MX_DBG_CMD_TYPE_VAR_UINT16,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_VALID_PTR,
  0,
  0,
  0,
  0,
  0,
  0,
  NULL,
  OMTB_OmxDeInitTwice,
  "",
  "<Testcase #> <Component Name> <Result File Name> <wb | ab>",
  "",
  ""
};


/* Entry for OMX core init version mismatch */

MX_DBG_CMD_ENTRY_T cmdEntryOmtbOmxDeInitVerMismatch =
{
  "ver_mismatch",
  MX_DBG_CMD_TYPE_VAR_UINT16,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_VALID_PTR,
  0,
  0,
  0,
  0,
  0,
  0,
  NULL,
  OMTB_OmxDeInitVerMismatch,
  "",
  "<Testcase #> <Component Name> <Result File Name> <wb | ab>",
  "",
  ""
};


/* Entry for OMX core init timeout */

MX_DBG_CMD_ENTRY_T cmdEntryOmtbOmxDeInitTimeOut =
{
  "timeout",
  MX_DBG_CMD_TYPE_VAR_UINT16,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_VALID_PTR,
  0,
  0,
  0,
  0,
  0,
  0,
  NULL,
  OMTB_OmxDeInitTimeOut,
  "",
  "<Testcase #> <Component Name> <Result File Name> <wb | ab>",
  "",
  ""
};


/* Entry for OMX core init timeout */

MX_DBG_CMD_ENTRY_T cmdEntryOmtbOmxDeInitWithoutFreeHandle =
{
  "without_freehandle",
  MX_DBG_CMD_TYPE_VAR_UINT16,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_VALID_PTR,
  0,
  0,
  0,
  0,
  0,
  0,
  NULL,
  OMTB_OmxDeInitWithoutFreeHandle,
  "",
  "<Testcase #> <Component Name> <Result File Name> <wb | ab>",
  "",
  ""
};


/* deinit command list */
MX_DBG_CMD_ENTRY_T* cmdListOmtbOmxDeInitTest[] =
{
  &cmdEntryOmtbOmxDeInitOnce,
  &cmdEntryOmtbOmxDeInitTwice,
  &cmdEntryOmtbOmxDeInitVerMismatch,
  &cmdEntryOmtbOmxDeInitTimeOut,
  &cmdEntryOmtbOmxDeInitWithoutFreeHandle,
  NULL
};


/* deinit command table */
MX_DBG_CMD_TABLE_T cmdTblOmtbOmxDeInitTest =
{
  MX_DBG_ACCESS_ALL,
  sizeof(cmdListOmtbOmxDeInitTest) / sizeof(cmdListOmtbOmxDeInitTest[0]),
  cmdListOmtbOmxDeInitTest
};


/* Entry for OMX Core DeInit */

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryOmxDeInitTest =
{
  "uninit",
  MX_DBG_CMD_TYPE_CMD_TABLE,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_VALID_PTR,
  0,
  0,
  0,
  0,
  0,
  0,
  &cmdTblOmtbOmxDeInitTest,
  OMTB_ParseCmdTblEntries,
  "",
  "",
  "",
  ""
};


/* Entry for OMX get handle once */

MX_DBG_CMD_ENTRY_T cmdEntryOmtbOmxGetHandleOnce =
{
  "once",
  MX_DBG_CMD_TYPE_VAR_UINT16,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_VALID_PTR,
  0,
  0,
  0,
  0,
  0,
  0,
  NULL,
  OMTB_OmxGetHandleOnce,
  "",
  "<Testcase #> <Component Name> <Result File Name> <wb | ab>",
  "",
  ""
};

/* Entry for OMX get handle twice */

MX_DBG_CMD_ENTRY_T cmdEntryOmtbOmxGetHandleTwice =
{
  "twice",
  MX_DBG_CMD_TYPE_VAR_UINT16,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_VALID_PTR,
  0,
  0,
  0,
  0,
  0,
  0,
  NULL,
  OMTB_OmxGetHandleTwice,
  "",
  "<Testcase #> <Component Name> <Result File Name> <wb | ab>",
  "",
  ""
};


/* Entry for OMX get handle with invalid comp name */

MX_DBG_CMD_ENTRY_T cmdEntryOmtbOmxGetHandleInvCompName =
{
  "inv_comp_name",
  MX_DBG_CMD_TYPE_VAR_UINT16,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_VALID_PTR,
  0,
  0,
  0,
  0,
  0,
  0,
  NULL,
  OMTB_OmxGetHandleInvCompName,
  "",
  "<Testcase #> <Component Name> <Result File Name> <wb | ab>",
  "",
  ""
};

/* Entry for OMX get handle with comp name not present */

MX_DBG_CMD_ENTRY_T cmdEntryOmtbOmxGetHandleCompNotFound =
{
  "comp_not_present",
  MX_DBG_CMD_TYPE_VAR_UINT16,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_VALID_PTR,
  0,
  0,
  0,
  0,
  0,
  0,
  NULL,
  OMTB_OmxGetHandleCompNotFound,
  "",
  "<Testcase #> <Component Name> <Result File Name> <wb | ab>",
  "",
  ""
};


/* Entry for OMX get handle with comp having no init fxn */

MX_DBG_CMD_ENTRY_T cmdEntryOmtbOmxGetHandleNoCompInitFxn =
{
  "comp_no_init_fxn",
  MX_DBG_CMD_TYPE_VAR_UINT16,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_VALID_PTR,
  0,
  0,
  0,
  0,
  0,
  0,
  NULL,
  OMTB_OmxGetHandleNoCompInitFxn,
  "",
  "<Testcase #> <Component Name> <Result File Name> <wb | ab>",
  "",
  ""
};

/* Entry for OMX get handle with NULL cb */

MX_DBG_CMD_ENTRY_T cmdEntryOmtbOmxGetHandleNullCb =
{
  "null_cb",
  MX_DBG_CMD_TYPE_VAR_UINT16,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_VALID_PTR,
  0,
  0,
  0,
  0,
  0,
  0,
  NULL,
  OMTB_OmxGetHandleNullCb,
  "",
  "<Testcase #> <Component Name> <Result File Name> <wb | ab>",
  "",
  ""
};

/* Entry for OMX get handle with NULL handle */

MX_DBG_CMD_ENTRY_T cmdEntryOmtbOmxGetHandleNullHandle =
{
  "null_handle",
  MX_DBG_CMD_TYPE_VAR_UINT16,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_VALID_PTR,
  0,
  0,
  0,
  0,
  0,
  0,
  NULL,
  OMTB_OmxGetHandleNullHandle,
  "",
  "<Testcase #> <Component Name> <Result File Name> <wb | ab>",
  "",
  ""
};

/* Entry for OMX get handle version mismatch */

MX_DBG_CMD_ENTRY_T cmdEntryOmtbOmxGetHandleVerMismatch =
{
  "ver_mismatch",
  MX_DBG_CMD_TYPE_VAR_UINT16,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_VALID_PTR,
  0,
  0,
  0,
  0,
  0,
  0,
  NULL,
  OMTB_OmxGetHandleVerMismatch,
  "",
  "<Testcase #> <Component Name> <Result File Name> <wb | ab>",
  "",
  ""
};

/* Entry for OMX get handle timeout */

MX_DBG_CMD_ENTRY_T cmdEntryOmtbOmxGetHandleTimeOut =
{
  "timeout",
  MX_DBG_CMD_TYPE_VAR_UINT16,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_VALID_PTR,
  0,
  0,
  0,
  0,
  0,
  0,
  NULL,
  OMTB_OmxGetHandleTimeOut,
  "",
  "<Testcase #> <Component Name> <Result File Name> <wb | ab>",
  "",
  ""
};

/* Entry for OMX get handle without core init */

MX_DBG_CMD_ENTRY_T cmdEntryOmtbOmxGetHandleWithoutCoreInit =
{
  "without_coreinit",
  MX_DBG_CMD_TYPE_VAR_UINT16,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_VALID_PTR,
  0,
  0,
  0,
  0,
  0,
  0,
  NULL,
  OMTB_OmxGetHandleWithoutCoreInit,
  "",
  "<Testcase #> <Component Name> <Result File Name> <wb | ab>",
  "",
  ""
};

/* GetHandle command list */
MX_DBG_CMD_ENTRY_T* cmdListOmtbGetHandleTest[] =
{
  &cmdEntryOmtbOmxGetHandleOnce,
  &cmdEntryOmtbOmxGetHandleTwice,
  &cmdEntryOmtbOmxGetHandleInvCompName,
  &cmdEntryOmtbOmxGetHandleCompNotFound,
  &cmdEntryOmtbOmxGetHandleNoCompInitFxn,
  &cmdEntryOmtbOmxGetHandleNullCb,
  &cmdEntryOmtbOmxGetHandleNullHandle,
  &cmdEntryOmtbOmxGetHandleVerMismatch,
  &cmdEntryOmtbOmxGetHandleTimeOut,
  &cmdEntryOmtbOmxGetHandleWithoutCoreInit,
  NULL
};


/* GetHandle command table */
MX_DBG_CMD_TABLE_T cmdTblOmtbGetHandleTest =
{
  MX_DBG_ACCESS_ALL,
  sizeof(cmdListOmtbGetHandleTest) / sizeof(cmdListOmtbGetHandleTest[0]),
  cmdListOmtbGetHandleTest
};


/* Entry for OMX Component GetHandle */

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryOmxGetHandleTest =
{
  "gethandle",
  MX_DBG_CMD_TYPE_CMD_TABLE,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_VALID_PTR,
  0,
  0,
  0,
  0,
  0,
  0,
  &cmdTblOmtbGetHandleTest,
  OMTB_ParseCmdTblEntries,
  "",
  "",
  "",
  ""
};


/* Entry for OMX get comp version once */

MX_DBG_CMD_ENTRY_T cmdEntryOmtbOmxGetCompVersionOnce =
{
  "once",
  MX_DBG_CMD_TYPE_VAR_UINT16,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_VALID_PTR,
  0,
  0,
  0,
  0,
  0,
  0,
  NULL,
  OMTB_OmxGetCompVersionOnce,
  "",
  "<Testcase #> <Component Name> <Result File Name> <wb | ab>",
  "",
  ""
};

/* Entry for OMX get comp version with NULL handle */

MX_DBG_CMD_ENTRY_T cmdEntryOmtbOmxGetCompVersionNullHandle =
{
  "null_handle",
  MX_DBG_CMD_TYPE_VAR_UINT16,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_VALID_PTR,
  0,
  0,
  0,
  0,
  0,
  0,
  NULL,
  OMTB_OmxGetCompVersionNullHandle,
  "",
  "<Testcase #> <Component Name> <Result File Name> <wb | ab>",
  "",
  ""
};

/* Entry for OMX get comp version with NULL comp name */

MX_DBG_CMD_ENTRY_T cmdEntryOmtbOmxGetCompVersionNullCompName =
{
  "null_comp_name",
  MX_DBG_CMD_TYPE_VAR_UINT16,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_VALID_PTR,
  0,
  0,
  0,
  0,
  0,
  0,
  NULL,
  OMTB_OmxGetCompVersionNullCompName,
  "",
  "<Testcase #> <Component Name> <Result File Name> <wb | ab>",
  "",
  ""
};

/* Entry for OMX get comp version with NULL comp version ptr */

MX_DBG_CMD_ENTRY_T cmdEntryOmtbOmxGetCompVersionNullCompVersion =
{
  "null_comp_ver",
  MX_DBG_CMD_TYPE_VAR_UINT16,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_VALID_PTR,
  0,
  0,
  0,
  0,
  0,
  0,
  NULL,
  OMTB_OmxGetCompVersionNullCompVersion,
  "",
  "<Testcase #> <Component Name> <Result File Name> <wb | ab>",
  "",
  ""
};

/* Entry for OMX get comp version with NULL spec version ptr */

MX_DBG_CMD_ENTRY_T cmdEntryOmtbOmxGetCompVersionNullSpecVersion =
{
  "null_spec_ver",
  MX_DBG_CMD_TYPE_VAR_UINT16,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_VALID_PTR,
  0,
  0,
  0,
  0,
  0,
  0,
  NULL,
  OMTB_OmxGetCompVersionNullSpecVersion,
  "",
  "<Testcase #> <Component Name> <Result File Name> <wb | ab>",
  "",
  ""
};

/* Entry for OMX get comp version with version mismatch */

MX_DBG_CMD_ENTRY_T cmdEntryOmtbOmxGetCompVersionVerMismatch =
{
  "ver_mismatch",
  MX_DBG_CMD_TYPE_VAR_UINT16,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_VALID_PTR,
  0,
  0,
  0,
  0,
  0,
  0,
  NULL,
  OMTB_OmxGetCompVersionVerMismatch,
  "",
  "<Testcase #> <Component Name> <Result File Name> <wb | ab>",
  "",
  ""
};

/* get comp version command list */
MX_DBG_CMD_ENTRY_T* cmdListOmtbOmxGetCompVersionTest[] =
{
  &cmdEntryOmtbOmxGetCompVersionOnce,
  &cmdEntryOmtbOmxGetCompVersionNullHandle,
  &cmdEntryOmtbOmxGetCompVersionNullCompName,
  &cmdEntryOmtbOmxGetCompVersionNullCompVersion,
  &cmdEntryOmtbOmxGetCompVersionNullSpecVersion,
  &cmdEntryOmtbOmxGetCompVersionVerMismatch,
  NULL
};


/* get comp version command table */
MX_DBG_CMD_TABLE_T cmdTblOmtbOmxGetCompVersionTest =
{
  MX_DBG_ACCESS_ALL,
  sizeof(cmdListOmtbOmxGetCompVersionTest) / sizeof(cmdListOmtbOmxGetCompVersionTest[0]),
  cmdListOmtbOmxGetCompVersionTest
};


/* Entry for OMX Component GetCompVersion */

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryOmxGetCompVersionTest =
{
  "get_comp_ver",
  MX_DBG_CMD_TYPE_CMD_TABLE,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_VALID_PTR,
  0,
  0,
  0,
  0,
  0,
  0,
  &cmdTblOmtbOmxGetCompVersionTest,
  OMTB_ParseCmdTblEntries,
  "",
  "",
  "",
  ""
};

/* Entry for OMX alloc/use buffer once */

MX_DBG_CMD_ENTRY_T cmdEntryOmxAllocUseBufferOnce =
{
  "once",
  MX_DBG_CMD_TYPE_VAR_UINT16,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_VALID_PTR,
  0,
  0,
  0,
  0,
  0,
  0,
  NULL,
  OmxAllocUseBufferOnce,
  "",
  "<Testcase #> <Component Name> <Result File Name> <wb | ab> <instance #>",
  "",
  ""
};


/* Entry for OMX alloc/use buffer with insufficient resources */

MX_DBG_CMD_ENTRY_T cmdEntryOmxAllocUseBufferInsuffResources =
{
  "insuff_res",
  MX_DBG_CMD_TYPE_VAR_UINT16,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_VALID_PTR,
  0,
  0,
  0,
  0,
  0,
  0,
  NULL,
  OmxAllocUseBufferInsuffResources,
  "",
  "<Testcase #> <Component Name> <Result File Name> <wb | ab> <instance #>",
  "",
  ""
};

/* Entry for OMX alloc/use buffer with null buffer */

MX_DBG_CMD_ENTRY_T cmdEntryOmxAllocUseBufferNullBufferHdr =
{
  "null_buffer",
  MX_DBG_CMD_TYPE_VAR_UINT16,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_VALID_PTR,
  0,
  0,
  0,
  0,
  0,
  0,
  NULL,
  OmxAllocUseBufferNullBufferHdr,
  "",
  "<Testcase #> <Component Name> <Result File Name> <wb | ab> <instance #>",
  "",
  ""
};

/* Entry for OMX alloc/use buffer with null handle */

MX_DBG_CMD_ENTRY_T cmdEntryOmxAllocUseBufferNullHandle =
{
  "null_handle",
  MX_DBG_CMD_TYPE_VAR_UINT16,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_VALID_PTR,
  0,
  0,
  0,
  0,
  0,
  0,
  NULL,
  OmxAllocUseBufferNullHandle,
  "",
  "<Testcase #> <Component Name> <Result File Name> <wb | ab> <instance #>",
  "",
  ""
};


/* Entry for OMX alloc/use buffer with version mismatch */

MX_DBG_CMD_ENTRY_T cmdEntryOmxAllocUseBufferVerMismatch =
{
  "ver_mismatch",
  MX_DBG_CMD_TYPE_VAR_UINT16,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_VALID_PTR,
  0,
  0,
  0,
  0,
  0,
  0,
  NULL,
  OmxAllocUseBufferVerMismatch,
  "",
  "<Testcase #> <Component Name> <Result File Name> <wb | ab> <instance #>",
  "",
  ""
};

/* Entry for OMX alloc/use buffer with timeout */

MX_DBG_CMD_ENTRY_T cmdEntryOmxAllocUseBufferTimeOut =
{
  "timeout",
  MX_DBG_CMD_TYPE_VAR_UINT16,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_VALID_PTR,
  0,
  0,
  0,
  0,
  0,
  0,
  NULL,
  OmxAllocUseBufferTimeOut,
  "",
  "<Testcase #> <Component Name> <Result File Name> <wb | ab> <instance #>",
  "",
  ""
};

/* Entry for OMX alloc/use buffer with wrong port */

MX_DBG_CMD_ENTRY_T cmdEntryOmxAllocUseBufferWrongPort =
{
  "wrong_port",
  MX_DBG_CMD_TYPE_VAR_UINT16,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_VALID_PTR,
  0,
  0,
  0,
  0,
  0,
  0,
  NULL,
  OmxAllocUseBufferWrongPort,
  "",
  "<Testcase #> <Component Name> <Result File Name> <wb | ab> <instance #>",
  "",
  ""
};

/* Entry for OMX alloc/use buffer in idle state */

MX_DBG_CMD_ENTRY_T cmdEntryOmxAllocUseBufferIdleState =
{
  "idle_state",
  MX_DBG_CMD_TYPE_VAR_UINT16,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_VALID_PTR,
  0,
  0,
  0,
  0,
  0,
  0,
  NULL,
  OmxAllocUseBufferIdleState,
  "",
  "<Testcase #> <Component Name> <Result File Name> <wb | ab> <instance #>",
  "",
  ""
};

/* alloc/use buffer command list */
MX_DBG_CMD_ENTRY_T* cmdListOmtbAllocUseBufferTest[] =
{
  &cmdEntryOmxAllocUseBufferOnce,
  &cmdEntryOmxAllocUseBufferInsuffResources,
  &cmdEntryOmxAllocUseBufferNullBufferHdr,
  &cmdEntryOmxAllocUseBufferNullHandle,
  &cmdEntryOmxAllocUseBufferVerMismatch,
  &cmdEntryOmxAllocUseBufferTimeOut,
  &cmdEntryOmxAllocUseBufferWrongPort,
  &cmdEntryOmxAllocUseBufferIdleState,  
  NULL
  
};


/* alloc/use buffer command table */
MX_DBG_CMD_TABLE_T cmdTblOmtbAllocUseBufferTest =
{
  MX_DBG_ACCESS_ALL,
  sizeof(cmdListOmtbAllocUseBufferTest) / sizeof(cmdListOmtbAllocUseBufferTest[0]),
  cmdListOmtbAllocUseBufferTest
};


/* Entry for OMX alloc/use buffer */

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryOmxAllocUseBufferTest =
{
  "buf_alloc",
  MX_DBG_CMD_TYPE_CMD_TABLE,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_VALID_PTR,
  0,
  0,
  0,
  0,
  0,
  0,
  &cmdTblOmtbAllocUseBufferTest,
  OMTB_ParseCmdTblEntries,
  "",
  "",
  "",
  ""
};


/* Entry for OMX free buffer once */

MX_DBG_CMD_ENTRY_T cmdEntryOmxFreeBufferOnce =
{
  "once",
  MX_DBG_CMD_TYPE_VAR_UINT16,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_VALID_PTR,
  0,
  0,
  0,
  0,
  0,
  0,
  NULL,
  OmxFreeBufferOnce,
  "",
  "<Testcase #> <Component Name> <Result File Name> <wb | ab> <instance #>",
  "",
  ""
};

/* Entry for OMX free buffer with insufficient resources */

MX_DBG_CMD_ENTRY_T cmdEntryOmxFreeBufferInsuffResources =
{
  "insuff_res",
  MX_DBG_CMD_TYPE_VAR_UINT16,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_VALID_PTR,
  0,
  0,
  0,
  0,
  0,
  0,
  NULL,
  OmxFreeBufferInsuffResources,
  "",
  "<Testcase #> <Component Name> <Result File Name> <wb | ab> <instance #>",
  "",
  ""
};

/* Entry for OMX free buffer with null buffer */

MX_DBG_CMD_ENTRY_T cmdEntryOmxFreeBufferNullBufferHdr =
{
  "null_buffer",
  MX_DBG_CMD_TYPE_VAR_UINT16,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_VALID_PTR,
  0,
  0,
  0,
  0,
  0,
  0,
  NULL,
  OmxFreeBufferNullBufferHdr,
  "",
  "<Testcase #> <Component Name> <Result File Name> <wb | ab> <instance #>",
  "",
  ""
};

/* Entry for OMX free buffer with null handle */

MX_DBG_CMD_ENTRY_T cmdEntryOmxFreeBufferNullHandle =
{
  "null_handle",
  MX_DBG_CMD_TYPE_VAR_UINT16,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_VALID_PTR,
  0,
  0,
  0,
  0,
  0,
  0,
  NULL,
  OmxFreeBufferNullHandle,
  "",
  "<Testcase #> <Component Name> <Result File Name> <wb | ab> <instance #>",
  "",
  ""
};


/* Entry for OMX free buffer with version mismatch */

MX_DBG_CMD_ENTRY_T cmdEntryOmxFreeBufferVerMismatch =
{
  "ver_mismatch",
  MX_DBG_CMD_TYPE_VAR_UINT16,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_VALID_PTR,
  0,
  0,
  0,
  0,
  0,
  0,
  NULL,
  OmxFreeBufferVerMismatch,
  "",
  "<Testcase #> <Component Name> <Result File Name> <wb | ab> <instance #>",
  "",
  ""
};

/* Entry for OMX free buffer with timeout */

MX_DBG_CMD_ENTRY_T cmdEntryOmxFreeBufferTimeOut =
{
  "timeout",
  MX_DBG_CMD_TYPE_VAR_UINT16,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_VALID_PTR,
  0,
  0,
  0,
  0,
  0,
  0,
  NULL,
  OmxFreeBufferTimeOut,
  "",
  "<Testcase #> <Component Name> <Result File Name> <wb | ab> <instance #>",
  "",
  ""
};

/* Entry for OMX free buffer with wrong port */

MX_DBG_CMD_ENTRY_T cmdEntryOmxFreeBufferWrongPort =
{
  "wrong_port",
  MX_DBG_CMD_TYPE_VAR_UINT16,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_VALID_PTR,
  0,
  0,
  0,
  0,
  0,
  0,
  NULL,
  OmxFreeBufferWrongPort,
  "",
  "<Testcase #> <Component Name> <Result File Name> <wb | ab> <instance #>",
  "",
  ""
};

/* Entry for OMX free buffer in idle state */

MX_DBG_CMD_ENTRY_T cmdEntryOmxFreeBufferIdleState =
{
  "idle_state",
  MX_DBG_CMD_TYPE_VAR_UINT16,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_VALID_PTR,
  0,
  0,
  0,
  0,
  0,
  0,
  NULL,
  OmxFreeBufferIdleState,
  "",
  "<Testcase #> <Component Name> <Result File Name> <wb | ab> <instance #>",
  "",
  ""
};

/* free buffer command list */
MX_DBG_CMD_ENTRY_T* cmdListOmtbFreeBufferTest[] =
{
  &cmdEntryOmxFreeBufferOnce,
  &cmdEntryOmxFreeBufferInsuffResources,
  &cmdEntryOmxFreeBufferNullBufferHdr,
  &cmdEntryOmxFreeBufferNullHandle,
  &cmdEntryOmxFreeBufferVerMismatch,
  &cmdEntryOmxFreeBufferTimeOut,
  &cmdEntryOmxFreeBufferWrongPort,
  &cmdEntryOmxFreeBufferIdleState,
  NULL
};


/* free buffer command table */
MX_DBG_CMD_TABLE_T cmdTblOmtbFreeBufferTest =
{
  MX_DBG_ACCESS_ALL,
  sizeof(cmdListOmtbFreeBufferTest) / sizeof(cmdListOmtbFreeBufferTest[0]),
  cmdListOmtbFreeBufferTest
};


/* Entry for OMX free buffer */

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryOmxFreeBufferTest =
{
  "buf_free",
  MX_DBG_CMD_TYPE_CMD_TABLE,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_VALID_PTR,
  0,
  0,
  0,
  0,
  0,
  0,
  &cmdTblOmtbFreeBufferTest,
  OMTB_ParseCmdTblEntries,
  "",
  "",
  "",
  ""
};



/* Entry for OMX setparam once */

MX_DBG_CMD_ENTRY_T cmdEntryOmxSetParameterOnce =
{
  "once",
  MX_DBG_CMD_TYPE_VAR_UINT16,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_VALID_PTR,
  0,
  0,
  0,
  0,
  0,
  0,
  NULL,
  OMTB_OmxSetParameterOnce,
  "",
  "<Testcase #> <Component Name> <Result File Name> <wb | ab> <instance #>",
  "",
  ""
};

/* Entry for OMX setparam with NULL config structure */

MX_DBG_CMD_ENTRY_T cmdEntryOmxSetParameterNullCfgStruct =
{
  "null_cfg_struct",
  MX_DBG_CMD_TYPE_VAR_UINT16,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_VALID_PTR,
  0,
  0,
  0,
  0,
  0,
  0,
  NULL,
  OMTB_OmxSetParameterNullCfgStruct,
  "",
  "<Testcase #> <Component Name> <Result File Name> <wb | ab> <instance #>",
  "",
  ""
};

/* Entry for OMX setparam with NULL handle */

MX_DBG_CMD_ENTRY_T cmdEntryOmxSetParameterNullHandle =
{
  "null_handle",
  MX_DBG_CMD_TYPE_VAR_UINT16,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_VALID_PTR,
  0,
  0,
  0,
  0,
  0,
  0,
  NULL,
  OMTB_OmxSetParameterNullHandle,
  "",
  "<Testcase #> <Component Name> <Result File Name> <wb | ab> <instance #>",
  "",
  ""
};

/* Entry for OMX setparam version mismatch */

MX_DBG_CMD_ENTRY_T cmdEntryOmxSetParameterVerMismatch =
{
  "ver_mismatch",
  MX_DBG_CMD_TYPE_VAR_UINT16,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_VALID_PTR,
  0,
  0,
  0,
  0,
  0,
  0,
  NULL,
  OMTB_OmxSetParameterVerMismatch,
  "",
  "<Testcase #> <Component Name> <Result File Name> <wb | ab> <instance #>",
  "",
  ""
};

/* Entry for OMX setparam timeout */

MX_DBG_CMD_ENTRY_T cmdEntryOmxSetParameterTimeOut =
{
  "timeout",
  MX_DBG_CMD_TYPE_VAR_UINT16,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_VALID_PTR,
  0,
  0,
  0,
  0,
  0,
  0,
  NULL,
  OMTB_OmxSetParameterTimeOut,
  "",
  "<Testcase #> <Component Name> <Result File Name> <wb | ab> <instance #>",
  "",
  ""
};

/* Entry for OMX setparam with unsupported settings */

MX_DBG_CMD_ENTRY_T cmdEntryOmxSetParameterUnSupportedSettings =
{
  "unsupported_set",
  MX_DBG_CMD_TYPE_VAR_UINT16,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_VALID_PTR,
  0,
  0,
  0,
  0,
  0,
  0,
  NULL,
  OMTB_OmxSetParameterUnSupportedSettings,
  "",
  "<Testcase #> <Component Name> <Result File Name> <wb | ab> <instance #>",
  "",
  ""
};

/* Entry for OMX setparam with unsupported index */

MX_DBG_CMD_ENTRY_T cmdEntryOmxSetParameterUnSupportedIndex =
{
  "unsupported_idx",
  MX_DBG_CMD_TYPE_VAR_UINT16,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_VALID_PTR,
  0,
  0,
  0,
  0,
  0,
  0,
  NULL,
  OMTB_OmxSetParameterUnSupportedIndex,
  "",
  "<Testcase #> <Component Name> <Result File Name> <wb | ab> <instance #>",
  "",
  ""
};

/* Entry for OMX setparam with wrong port */

MX_DBG_CMD_ENTRY_T cmdEntryOmxSetParameterWrongPort =
{
  "wrong_port",
  MX_DBG_CMD_TYPE_VAR_UINT16,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_VALID_PTR,
  0,
  0,
  0,
  0,
  0,
  0,
  NULL,
  OMTB_OmxSetParameterWrongPort,
  "",
  "<Testcase #> <Component Name> <Result File Name> <wb | ab> <instance #>",
  "",
  ""
};

/* Entry for OMX setparam in idle state */

MX_DBG_CMD_ENTRY_T cmdEntryOmxSetParameterIdleState =
{
  "idle_state",
  MX_DBG_CMD_TYPE_VAR_UINT16,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_VALID_PTR,
  0,
  0,
  0,
  0,
  0,
  0,
  NULL,
  OMTB_OmxSetParameterIdleState,
  "",
  "<Testcase #> <Component Name> <Result File Name> <wb | ab> <instance #>",
  "",
  ""
};

/* SetParam command list */
MX_DBG_CMD_ENTRY_T* cmdListOmtbSetParamTest[] =
{
  &cmdEntryOmxSetParameterOnce,
  &cmdEntryOmxSetParameterNullCfgStruct,
  &cmdEntryOmxSetParameterNullHandle,
  &cmdEntryOmxSetParameterVerMismatch,
  &cmdEntryOmxSetParameterTimeOut,
  &cmdEntryOmxSetParameterUnSupportedSettings,
  &cmdEntryOmxSetParameterUnSupportedIndex,
  &cmdEntryOmxSetParameterWrongPort,
  &cmdEntryOmxSetParameterIdleState,
  NULL  
};


/* SetParam command table */
MX_DBG_CMD_TABLE_T cmdTblOmtbSetParamTest =
{
  MX_DBG_ACCESS_ALL,
  sizeof(cmdListOmtbSetParamTest) / sizeof(cmdListOmtbSetParamTest[0]),
  cmdListOmtbSetParamTest
};


/* Entry for OMX Component SetParam */

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryOmxSetParamTest =
{
  "setparam",
  MX_DBG_CMD_TYPE_CMD_TABLE,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_VALID_PTR,
  0,
  0,
  0,
  0,
  0,
  0,
  &cmdTblOmtbSetParamTest,
  OMTB_ParseCmdTblEntries,
  "",
  "",
  "",
  ""
};


/* Entry for OMX setconfig once */

MX_DBG_CMD_ENTRY_T cmdEntryOmxSetConfigOnce =
{
  "once",
  MX_DBG_CMD_TYPE_VAR_UINT16,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_VALID_PTR,
  0,
  0,
  0,
  0,
  0,
  0,
  NULL,
 OMTB_OmxSetConfigOnce,
  "",
  "<Testcase #> <Component Name> <Result File Name> <wb | ab> <instance #>",
  "",
  ""
};

/* Entry for OMX setconfig with NULL config structure */

MX_DBG_CMD_ENTRY_T cmdEntryOmxSetConfigNullCfgStruct =
{
  "null_cfg_struct",
  MX_DBG_CMD_TYPE_VAR_UINT16,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_VALID_PTR,
  0,
  0,
  0,
  0,
  0,
  0,
  NULL,
 OMTB_OmxSetConfigNullCfgStruct,
  "",
  "<Testcase #> <Component Name> <Result File Name> <wb | ab> <instance #>",
  "",
  ""
};

/* Entry for OMX setconfig with NULL handle */

MX_DBG_CMD_ENTRY_T cmdEntryOmxSetConfigNullHandle =
{
  "null_handle",
  MX_DBG_CMD_TYPE_VAR_UINT16,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_VALID_PTR,
  0,
  0,
  0,
  0,
  0,
  0,
  NULL,
 OMTB_OmxSetConfigNullHandle,
  "",
  "<Testcase #> <Component Name> <Result File Name> <wb | ab> <instance #>",
  "",
  ""
};

/* Entry for OMX setconfig version mismatch */

MX_DBG_CMD_ENTRY_T cmdEntryOmxSetConfigVerMismatch =
{
  "ver_mismatch",
  MX_DBG_CMD_TYPE_VAR_UINT16,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_VALID_PTR,
  0,
  0,
  0,
  0,
  0,
  0,
  NULL,
 OMTB_OmxSetConfigVerMismatch,
  "",
  "<Testcase #> <Component Name> <Result File Name> <wb | ab> <instance #>",
  "",
  ""
};

/* Entry for OMX setconfig timeout */

MX_DBG_CMD_ENTRY_T cmdEntryOmxSetConfigTimeOut =
{
  "timeout",
  MX_DBG_CMD_TYPE_VAR_UINT16,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_VALID_PTR,
  0,
  0,
  0,
  0,
  0,
  0,
  NULL,
 OMTB_OmxSetConfigTimeOut,
  "",
  "<Testcase #> <Component Name> <Result File Name> <wb | ab> <instance #>",
  "",
  ""
};

/* Entry for OMX setconfig with unsupported settings */

MX_DBG_CMD_ENTRY_T cmdEntryOmxSetConfigUnSupportedSettings =
{
  "unsupported_set",
  MX_DBG_CMD_TYPE_VAR_UINT16,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_VALID_PTR,
  0,
  0,
  0,
  0,
  0,
  0,
  NULL,
 OMTB_OmxSetConfigUnSupportedSettings,
  "",
  "<Testcase #> <Component Name> <Result File Name> <wb | ab> <instance #>",
  "",
  ""
};

/* Entry for OMX setconfig with unsupported index */

MX_DBG_CMD_ENTRY_T cmdEntryOmxSetConfigUnSupportedIndex =
{
  "unsupported_idx",
  MX_DBG_CMD_TYPE_VAR_UINT16,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_VALID_PTR,
  0,
  0,
  0,
  0,
  0,
  0,
  NULL,
 OMTB_OmxSetConfigUnSupportedIndex,
  "",
  "<Testcase #> <Component Name> <Result File Name> <wb | ab> <instance #>",
  "",
  ""
};

/* Entry for OMX setconfig with wrong port */

MX_DBG_CMD_ENTRY_T cmdEntryOmxSetConfigWrongPort =
{
  "wrong_port",
  MX_DBG_CMD_TYPE_VAR_UINT16,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_VALID_PTR,
  0,
  0,
  0,
  0,
  0,
  0,
  NULL,
 OMTB_OmxSetConfigWrongPort,
  "",
  "<Testcase #> <Component Name> <Result File Name> <wb | ab> <instance #>",
  "",
  ""
};

/* SetConfig command list */
MX_DBG_CMD_ENTRY_T* cmdListOmtbSetConfigTest[] =
{
  &cmdEntryOmxSetConfigOnce,
  &cmdEntryOmxSetConfigNullCfgStruct,
  &cmdEntryOmxSetConfigNullHandle,
  &cmdEntryOmxSetConfigVerMismatch,
  &cmdEntryOmxSetConfigTimeOut,
  &cmdEntryOmxSetConfigUnSupportedSettings,
  &cmdEntryOmxSetConfigUnSupportedIndex,
  &cmdEntryOmxSetConfigWrongPort,
  NULL
};


/* SetConfig command table */
MX_DBG_CMD_TABLE_T cmdTblOmtbSetConfigTest =
{
  MX_DBG_ACCESS_ALL,
  sizeof(cmdListOmtbSetConfigTest) / sizeof(cmdListOmtbSetConfigTest[0]),
  cmdListOmtbSetConfigTest
};


/* Entry for OMX Component SetConfig */

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryOmxSetConfigTest =
{
  "setconfig",
  MX_DBG_CMD_TYPE_CMD_TABLE,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_VALID_PTR,
  0,
  0,
  0,
  0,
  0,
  0,
  &cmdTblOmtbSetConfigTest,
  OMTB_ParseCmdTblEntries,
  "",
  "",
  "",
  ""
};


/* Entry for OMX getparam once */

MX_DBG_CMD_ENTRY_T cmdEntryOmxGetParameterOnce =
{
  "once",
  MX_DBG_CMD_TYPE_VAR_UINT16,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_VALID_PTR,
  0,
  0,
  0,
  0,
  0,
  0,
  NULL,
  OMTB_OmxGetParameterOnce,
  "",
  "<Testcase #> <Component Name> <Result File Name> <wb | ab> <instance #>",
  "",
  ""
};

/* Entry for OMX getparam with NULL config structure */

MX_DBG_CMD_ENTRY_T cmdEntryOmxGetParameterNullCfgStruct =
{
  "null_cfg_struct",
  MX_DBG_CMD_TYPE_VAR_UINT16,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_VALID_PTR,
  0,
  0,
  0,
  0,
  0,
  0,
  NULL,
  OMTB_OmxGetParameterNullCfgStruct,
  "",
  "<Testcase #> <Component Name> <Result File Name> <wb | ab> <instance #>",
  "",
  ""
};

/* Entry for OMX getparam with NULL handle */

MX_DBG_CMD_ENTRY_T cmdEntryOmxGetParameterNullHandle =
{
  "null_handle",
  MX_DBG_CMD_TYPE_VAR_UINT16,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_VALID_PTR,
  0,
  0,
  0,
  0,
  0,
  0,
  NULL,
  OMTB_OmxGetParameterNullHandle,
  "",
  "<Testcase #> <Component Name> <Result File Name> <wb | ab> <instance #>",
  "",
  ""
};

/* Entry for OMX getparam version mismatch */

MX_DBG_CMD_ENTRY_T cmdEntryOmxGetParameterVerMismatch =
{
  "ver_mismatch",
  MX_DBG_CMD_TYPE_VAR_UINT16,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_VALID_PTR,
  0,
  0,
  0,
  0,
  0,
  0,
  NULL,
  OMTB_OmxGetParameterVerMismatch,
  "",
  "<Testcase #> <Component Name> <Result File Name> <wb | ab> <instance #>",
  "",
  ""
};

/* Entry for OMX getparam timeout */

MX_DBG_CMD_ENTRY_T cmdEntryOmxGetParameterTimeOut =
{
  "timeout",
  MX_DBG_CMD_TYPE_VAR_UINT16,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_VALID_PTR,
  0,
  0,
  0,
  0,
  0,
  0,
  NULL,
  OMTB_OmxGetParameterTimeOut,
  "",
  "<Testcase #> <Component Name> <Result File Name> <wb | ab> <instance #>",
  "",
  ""
};

/* Entry for OMX getparam with unsupported settings */

MX_DBG_CMD_ENTRY_T cmdEntryOmxGetParameterUnSupportedSettings =
{
  "unsupported_set",
  MX_DBG_CMD_TYPE_VAR_UINT16,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_VALID_PTR,
  0,
  0,
  0,
  0,
  0,
  0,
  NULL,
  OMTB_OmxGetParameterUnSupportedSettings,
  "",
  "<Testcase #> <Component Name> <Result File Name> <wb | ab> <instance #>",
  "",
  ""
};

/* Entry for OMX getparam with unsupported index */

MX_DBG_CMD_ENTRY_T cmdEntryOmxGetParameterUnSupportedIndex =
{
  "unsupported_idx",
  MX_DBG_CMD_TYPE_VAR_UINT16,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_VALID_PTR,
  0,
  0,
  0,
  0,
  0,
  0,
  NULL,
  OMTB_OmxGetParameterUnSupportedIndex,
  "",
  "<Testcase #> <Component Name> <Result File Name> <wb | ab> <instance #>",
  "",
  ""
};

/* Entry for OMX getparam with wrong port */

MX_DBG_CMD_ENTRY_T cmdEntryOmxGetParameterWrongPort =
{
  "wrong_port",
  MX_DBG_CMD_TYPE_VAR_UINT16,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_VALID_PTR,
  0,
  0,
  0,
  0,
  0,
  0,
  NULL,
  OMTB_OmxGetParameterWrongPort,
  "",
  "<Testcase #> <Component Name> <Result File Name> <wb | ab> <instance #>",
  "",
  ""
};

/* Entry for OMX getparam in idle state */

MX_DBG_CMD_ENTRY_T cmdEntryOmxGetParameterIdleState =
{
  "idle_state",
  MX_DBG_CMD_TYPE_VAR_UINT16,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_VALID_PTR,
  0,
  0,
  0,
  0,
  0,
  0,
  NULL,
  OMTB_OmxGetParameterIdleState,
  "",
  "<Testcase #> <Component Name> <Result File Name> <wb | ab> <instance #>",
  "",
  ""
};


/* GetParam command list */
MX_DBG_CMD_ENTRY_T* cmdListOmtbGetParamTest[] =
{
  &cmdEntryOmxGetParameterOnce,
  &cmdEntryOmxGetParameterNullCfgStruct,
  &cmdEntryOmxGetParameterNullHandle,
  &cmdEntryOmxGetParameterVerMismatch,
  &cmdEntryOmxGetParameterTimeOut,
  &cmdEntryOmxGetParameterUnSupportedSettings,
  &cmdEntryOmxGetParameterUnSupportedIndex,
  &cmdEntryOmxGetParameterWrongPort,
  &cmdEntryOmxGetParameterIdleState,
  NULL
};


/* GetParam command table */
MX_DBG_CMD_TABLE_T cmdTblOmtbGetParamTest =
{
  MX_DBG_ACCESS_ALL,
  sizeof(cmdListOmtbGetParamTest) / sizeof(cmdListOmtbGetParamTest[0]),
  cmdListOmtbGetParamTest
};


/* Entry for OMX Component GetParam */

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryOmxGetParamTest =
{
  "getparam",
  MX_DBG_CMD_TYPE_CMD_TABLE,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_VALID_PTR,
  0,
  0,
  0,
  0,
  0,
  0,
  &cmdTblOmtbGetParamTest,
  OMTB_ParseCmdTblEntries,
  "",
  "",
  "",
  ""
};



/* Entry for OMX getconfig once */

MX_DBG_CMD_ENTRY_T cmdEntryOmxGetConfigOnce =
{
  "once",
  MX_DBG_CMD_TYPE_VAR_UINT16,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_VALID_PTR,
  0,
  0,
  0,
  0,
  0,
  0,
  NULL,
  OMTB_OmxGetConfigOnce,
  "",
  "<Testcase #> <Component Name> <Result File Name> <wb | ab> <instance #>",
  "",
  ""
};

/* Entry for OMX getconfig with NULL config structure */

MX_DBG_CMD_ENTRY_T cmdEntryOmxGetConfigNullCfgStruct =
{
  "null_cfg_struct",
  MX_DBG_CMD_TYPE_VAR_UINT16,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_VALID_PTR,
  0,
  0,
  0,
  0,
  0,
  0,
  NULL,
  OMTB_OmxGetConfigNullCfgStruct,
  "",
  "<Testcase #> <Component Name> <Result File Name> <wb | ab> <instance #>",
  "",
  ""
};

/* Entry for OMX getconfig with NULL handle */

MX_DBG_CMD_ENTRY_T cmdEntryOmxGetConfigNullHandle =
{
  "null_handle",
  MX_DBG_CMD_TYPE_VAR_UINT16,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_VALID_PTR,
  0,
  0,
  0,
  0,
  0,
  0,
  NULL,
  OMTB_OmxGetConfigNullHandle,
  "",
  "<Testcase #> <Component Name> <Result File Name> <wb | ab> <instance #>",
  "",
  ""
};

/* Entry for OMX getconfig version mismatch */

MX_DBG_CMD_ENTRY_T cmdEntryOmxGetConfigVerMismatch =
{
  "ver_mismatch",
  MX_DBG_CMD_TYPE_VAR_UINT16,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_VALID_PTR,
  0,
  0,
  0,
  0,
  0,
  0,
  NULL,
  OMTB_OmxGetConfigVerMismatch,
  "",
  "<Testcase #> <Component Name> <Result File Name> <wb | ab> <instance #>",
  "",
  ""
};

/* Entry for OMX getconfig timeout */

MX_DBG_CMD_ENTRY_T cmdEntryOmxGetConfigTimeOut =
{
  "timeout",
  MX_DBG_CMD_TYPE_VAR_UINT16,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_VALID_PTR,
  0,
  0,
  0,
  0,
  0,
  0,
  NULL,
  OMTB_OmxGetConfigTimeOut,
  "",
  "<Testcase #> <Component Name> <Result File Name> <wb | ab> <instance #>",
  "",
  ""
};

/* Entry for OMX getconfig with unsupported settings */

MX_DBG_CMD_ENTRY_T cmdEntryOmxGetConfigUnSupportedSettings =
{
  "unsupported_set",
  MX_DBG_CMD_TYPE_VAR_UINT16,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_VALID_PTR,
  0,
  0,
  0,
  0,
  0,
  0,
  NULL,
  OMTB_OmxGetConfigUnSupportedSettings,
  "",
  "<Testcase #> <Component Name> <Result File Name> <wb | ab> <instance #>",
  "",
  ""
};

/* Entry for OMX getconfig with unsupported index */

MX_DBG_CMD_ENTRY_T cmdEntryOmxGetConfigUnSupportedIndex =
{
  "unsupported_idx",
  MX_DBG_CMD_TYPE_VAR_UINT16,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_VALID_PTR,
  0,
  0,
  0,
  0,
  0,
  0,
  NULL,
  OMTB_OmxGetConfigUnSupportedIndex,
  "",
  "<Testcase #> <Component Name> <Result File Name> <wb | ab> <instance #>",
  "",
  ""
};

/* Entry for OMX getconfig with wrong port */

MX_DBG_CMD_ENTRY_T cmdEntryOmxGetConfigWrongPort =
{
  "wrong_port",
  MX_DBG_CMD_TYPE_VAR_UINT16,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_VALID_PTR,
  0,
  0,
  0,
  0,
  0,
  0,
  NULL,
  OMTB_OmxGetConfigWrongPort,
  "",
  "<Testcase #> <Component Name> <Result File Name> <wb | ab> <instance #>",
  "",
  ""
};


/* GetConfig command list */
MX_DBG_CMD_ENTRY_T* cmdListOmtbGetConfigTest[] =
{
  &cmdEntryOmxGetConfigOnce,
  &cmdEntryOmxGetConfigNullCfgStruct,
  &cmdEntryOmxGetConfigNullHandle,
  &cmdEntryOmxGetConfigVerMismatch,
  &cmdEntryOmxGetConfigTimeOut,
  &cmdEntryOmxGetConfigUnSupportedSettings,
  &cmdEntryOmxGetConfigUnSupportedIndex,
  &cmdEntryOmxGetConfigWrongPort,
  NULL
};

/* GetConfig command table */
MX_DBG_CMD_TABLE_T cmdTblOmtbGetConfigTest =
{
  MX_DBG_ACCESS_ALL,
  sizeof(cmdListOmtbGetConfigTest) / sizeof(cmdListOmtbGetConfigTest[0]),
  cmdListOmtbGetConfigTest
};


/* Entry for OMX Component GetConfig */

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryOmxGetConfigTest =
{
  "getconfig",
  MX_DBG_CMD_TYPE_CMD_TABLE,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_VALID_PTR,
  0,
  0,
  0,
  0,
  0,
  0,
  &cmdTblOmtbGetConfigTest,
  OMTB_ParseCmdTblEntries,
  "",
  "",
  "",
  ""
};


/* Entry for OMX get extension index once */

MX_DBG_CMD_ENTRY_T cmdEntryOmtbOmxGetExtensionIndexOnce =
{
  "once",
  MX_DBG_CMD_TYPE_VAR_UINT16,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_VALID_PTR,
  0,
  0,
  0,
  0,
  0,
  0,
  NULL,
  OMTB_OmxGetExtensionIndexOnce,
  "",
  "<Testcase #> <Component Name> <Result File Name> <wb | ab> <Vendor String>",
  "",
  ""
};

/* Entry for OMX get extension index with NULL handle */

MX_DBG_CMD_ENTRY_T cmdEntryOmtbOmxGetExtensionIndexNullHandle =
{
  "null_handle",
  MX_DBG_CMD_TYPE_VAR_UINT16,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_VALID_PTR,
  0,
  0,
  0,
  0,
  0,
  0,
  NULL,
  OMTB_OmxGetExtensionIndexNullHandle,
  "",
  "<Testcase #> <Component Name> <Result File Name> <wb | ab> <Vendor String>",
  "",
  ""
};

/* Entry for OMX get extension index version mismatch */

MX_DBG_CMD_ENTRY_T cmdEntryOmtbOmxGetExtensionIndexVerMismatch =
{
  "ver_mismatch",
  MX_DBG_CMD_TYPE_VAR_UINT16,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_VALID_PTR,
  0,
  0,
  0,
  0,
  0,
  0,
  NULL,
  OMTB_OmxGetExtensionIndexVerMismatch,
  "",
  "<Testcase #> <Component Name> <Result File Name> <wb | ab> <Vendor String>",
  "",
  ""
};

/* Entry for OMX get extension index timeout */

MX_DBG_CMD_ENTRY_T cmdEntryOmtbOmxGetExtensionIndexTimeOut =
{
  "timeout",
  MX_DBG_CMD_TYPE_VAR_UINT16,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_VALID_PTR,
  0,
  0,
  0,
  0,
  0,
  0,
  NULL,
  OMTB_OmxGetExtensionIndexTimeOut,
  "",
  "<Testcase #> <Component Name> <Result File Name> <wb | ab> <Vendor String>",
  "",
  ""
};

/* Entry for OMX get extension index with incorrect vendor string */

MX_DBG_CMD_ENTRY_T cmdEntryOmtbOmxGetExtensionIndexWrongVendorStr =
{
  "wrong_vendor_str",
  MX_DBG_CMD_TYPE_VAR_UINT16,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_VALID_PTR,
  0,
  0,
  0,
  0,
  0,
  0,
  NULL,
  OMTB_OmxGetExtensionIndexWrongVendorStr,
  "",
  "<Testcase #> <Component Name> <Result File Name> <wb | ab> <Vendor String>",
  "",
  ""
};


/* get extension index command list */
MX_DBG_CMD_ENTRY_T* cmdListOmtbOmxGetExtensionIndexTest[] =
{
  &cmdEntryOmtbOmxGetExtensionIndexOnce,
  &cmdEntryOmtbOmxGetExtensionIndexNullHandle,
  &cmdEntryOmtbOmxGetExtensionIndexVerMismatch,
  &cmdEntryOmtbOmxGetExtensionIndexTimeOut,
  &cmdEntryOmtbOmxGetExtensionIndexWrongVendorStr,
  NULL
};


/* get extension index command table */
MX_DBG_CMD_TABLE_T cmdTblOmtbOmxGetExtensionIndexTest =
{
  MX_DBG_ACCESS_ALL,
  sizeof(cmdListOmtbOmxGetExtensionIndexTest) / sizeof(cmdListOmtbOmxGetExtensionIndexTest[0]),
  cmdListOmtbOmxGetExtensionIndexTest
};


/* Entry for OMX Component GetExtensionIndex */

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryOmxGetExtensionIndexTest =
{
  "getextindex",
  MX_DBG_CMD_TYPE_CMD_TABLE,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_VALID_PTR,
  0,
  0,
  0,
  0,
  0,
  0,
  &cmdTblOmtbOmxGetExtensionIndexTest,
  OMTB_ParseCmdTblEntries,
  "",
  "",
  "",
  ""
};


/* Entry for OMX get state once */

MX_DBG_CMD_ENTRY_T cmdEntryOmtbOmxGetStateOnce =
{
  "once",
  MX_DBG_CMD_TYPE_VAR_UINT16,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_VALID_PTR,
  0,
  0,
  0,
  0,
  0,
  0,
  NULL,
  OMTB_OmxGetStateOnce,
  "",
  "<Testcase #> <Component Name> <Result File Name> <wb | ab>",
  "",
  ""
};

/* Entry for OMX get state with NULL handle */

MX_DBG_CMD_ENTRY_T cmdEntryOmtbOmxGetStateNullHandle =
{
  "null_handle",
  MX_DBG_CMD_TYPE_VAR_UINT16,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_VALID_PTR,
  0,
  0,
  0,
  0,
  0,
  0,
  NULL,
  OMTB_OmxGetStateNullHandle,
  "",
  "<Testcase #> <Component Name> <Result File Name> <wb | ab>",
  "",
  ""
};

/* Entry for OMX get state version mismatch */

MX_DBG_CMD_ENTRY_T cmdEntryOmtbOmxGetStateVerMismatch =
{
  "ver_mismatch",
  MX_DBG_CMD_TYPE_VAR_UINT16,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_VALID_PTR,
  0,
  0,
  0,
  0,
  0,
  0,
  NULL,
  OMTB_OmxGetStateVerMismatch,
  "",
  "<Testcase #> <Component Name> <Result File Name> <wb | ab>",
  "",
  ""
};

/* Entry for OMX get state timeout */

MX_DBG_CMD_ENTRY_T cmdEntryOmtbOmxGetStateTimeOut =
{
  "timeout",
  MX_DBG_CMD_TYPE_VAR_UINT16,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_VALID_PTR,
  0,
  0,
  0,
  0,
  0,
  0,
  NULL,
  OMTB_OmxGetStateTimeOut,
  "",
  "<Testcase #> <Component Name> <Result File Name> <wb | ab>",
  "",
  ""
};


/* get state command list */
MX_DBG_CMD_ENTRY_T* cmdListOmtbOmxGetStateTest[] =
{
  &cmdEntryOmtbOmxGetStateOnce,
  &cmdEntryOmtbOmxGetStateNullHandle,
  &cmdEntryOmtbOmxGetStateVerMismatch,
  &cmdEntryOmtbOmxGetStateTimeOut,
  NULL
};


/* get state command table */
MX_DBG_CMD_TABLE_T cmdTblOmtbOmxGetStateTest =
{
  MX_DBG_ACCESS_ALL,
  sizeof(cmdListOmtbOmxGetStateTest) / sizeof(cmdListOmtbOmxGetStateTest[0]),
  cmdListOmtbOmxGetStateTest
};


/* Entry for OMX Component GetState */

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryOmxGetStateTest =
{
  "getstate",
  MX_DBG_CMD_TYPE_CMD_TABLE,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_VALID_PTR,
  0,
  0,
  0,
  0,
  0,
  0,
  &cmdTblOmtbOmxGetStateTest,
  OMTB_ParseCmdTblEntries,
  "",
  "",
  "",
  ""
};


/* Entry for OMX setup tunnel once */

MX_DBG_CMD_ENTRY_T cmdEntryOmtbOmxSetupTunnelOnce =
{
  "once",
  MX_DBG_CMD_TYPE_VAR_UINT16,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_VALID_PTR,
  0,
  0,
  0,
  0,
  0,
  0,
  NULL,
  OMTB_OmxSetupTunnelOnce,
  "",
  "<Testcase #> <1st Component Name> <Result File Name> <wb | ab> <1st Comp Port #> <2nd Component Name> <2nd Comp Port #>",
  "",
  ""
};

/* Entry for OMX setup tunnel null handle */

MX_DBG_CMD_ENTRY_T cmdEntryOmtbOmxSetupTunnelNullHandle =
{
  "null_handle",
  MX_DBG_CMD_TYPE_VAR_UINT16,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_VALID_PTR,
  0,
  0,
  0,
  0,
  0,
  0,
  NULL,
  OMTB_OmxSetupTunnelNullHandle,
  "",
  "<Testcase #> <1st Component Name> <Result File Name> <wb | ab> <1st Comp Port #> <2nd Component Name> <2nd Comp Port #>",
  "",
  ""
};

/* Entry for OMX setup tunnel with wrong port number */

MX_DBG_CMD_ENTRY_T cmdEntryOmtbOmxSetupTunnelWrongPortNum =
{
  "wrong_port_num",
  MX_DBG_CMD_TYPE_VAR_UINT16,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_VALID_PTR,
  0,
  0,
  0,
  0,
  0,
  0,
  NULL,
  OMTB_OmxSetupTunnelWrongPortNum,
  "",
  "<Testcase #> <1st Component Name> <Result File Name> <wb | ab> <1st Comp Port #> <2nd Component Name> <2nd Comp Port #>",
  "",
  ""
};


/* Entry for OMX setup tunnel when not implemented */

MX_DBG_CMD_ENTRY_T cmdEntryOmtbOmxSetupTunnelNotImplemented =
{
  "not_impl",
  MX_DBG_CMD_TYPE_VAR_UINT16,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_VALID_PTR,
  0,
  0,
  0,
  0,
  0,
  0,
  NULL,
  OMTB_OmxSetupTunnelNotImplemented,
  "",
  "<Testcase #> <1st Component Name> <Result File Name> <wb | ab> <1st Comp Port #> <2nd Component Name> <2nd Comp Port #>",
  "",
  ""
};

/* Entry for OMX setup tunnel with incompatible port */

MX_DBG_CMD_ENTRY_T cmdEntryOmtbOmxSetupTunnelPortIncompatible =
{
  "incompatible_port",
  MX_DBG_CMD_TYPE_VAR_UINT16,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_VALID_PTR,
  0,
  0,
  0,
  0,
  0,
  0,
  NULL,
  OMTB_OmxSetupTunnelPortIncompatible,
  "",
  "<Testcase #> <1st Component Name> <Result File Name> <wb | ab> <1st Comp Port #> <2nd Component Name> <2nd Comp Port #>",
  "",
  ""
};

/* Entry for OMX setup tunnel version mismatch */

MX_DBG_CMD_ENTRY_T cmdEntryOmtbOmxSetupTunnelVerMismatch =
{
  "ver_mismatch",
  MX_DBG_CMD_TYPE_VAR_UINT16,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_VALID_PTR,
  0,
  0,
  0,
  0,
  0,
  0,
  NULL,
  OMTB_OmxSetupTunnelVerMismatch,
  "",
  "<Testcase #> <1st Component Name> <Result File Name> <wb | ab> <1st Comp Port #> <2nd Component Name> <2nd Comp Port #>",
  "",
  ""
};

/* Entry for OMX setup tunnel timeout */

MX_DBG_CMD_ENTRY_T cmdEntryOmtbOmxSetupTunnelTimeOut =
{
  "timeout",
  MX_DBG_CMD_TYPE_VAR_UINT16,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_VALID_PTR,
  0,
  0,
  0,
  0,
  0,
  0,
  NULL,
  OMTB_OmxSetupTunnelTimeOut,
  "",
  "<Testcase #> <1st Component Name> <Result File Name> <wb | ab> <1st Comp Port #> <2nd Component Name> <2nd Comp Port #>",
  "",
  ""
};


/* setup tunnel command list */
MX_DBG_CMD_ENTRY_T* cmdListOmtbOmxSetupTunnelTest[] =
{
  &cmdEntryOmtbOmxSetupTunnelOnce,
  &cmdEntryOmtbOmxSetupTunnelNullHandle,
  &cmdEntryOmtbOmxSetupTunnelWrongPortNum,
  &cmdEntryOmtbOmxSetupTunnelNotImplemented,
  &cmdEntryOmtbOmxSetupTunnelPortIncompatible,
  &cmdEntryOmtbOmxSetupTunnelVerMismatch,
  &cmdEntryOmtbOmxSetupTunnelTimeOut,
  NULL
};


/* setup tunnel command table */
MX_DBG_CMD_TABLE_T cmdTblOmtbOmxSetupTunnelTest =
{
  MX_DBG_ACCESS_ALL,
  sizeof(cmdListOmtbOmxSetupTunnelTest) / sizeof(cmdListOmtbOmxSetupTunnelTest[0]),
  cmdListOmtbOmxSetupTunnelTest
};


/* Entry for OMX Component SetupTunnel */

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryOmxSetupTunnelTest =
{
  "setuptunnel",
  MX_DBG_CMD_TYPE_CMD_TABLE,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_VALID_PTR,
  0,
  0,
  0,
  0,
  0,
  0,
  &cmdTblOmtbOmxSetupTunnelTest,
  OMTB_ParseCmdTblEntries,
  "",
  "",
  "",
  ""
};


/* Entry for OMX free handle once */

MX_DBG_CMD_ENTRY_T cmdEntryOmtbOmxFreeHandleOnce =
{
  "once",
  MX_DBG_CMD_TYPE_VAR_UINT16,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_VALID_PTR,
  0,
  0,
  0,
  0,
  0,
  0,
  NULL,
  OMTB_OmxFreeHandleOnce,
  "",
  "<Testcase #> <Component Name> <Result File Name> <wb | ab>",
  "",
  ""
};

/* Entry for OMX free handle version mismatch */

MX_DBG_CMD_ENTRY_T cmdEntryOmtbOmxFreeHandleVerMismatch =
{
  "ver_mismatch",
  MX_DBG_CMD_TYPE_VAR_UINT16,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_VALID_PTR,
  0,
  0,
  0,
  0,
  0,
  0,
  NULL,
  OMTB_OmxFreeHandleVerMismatch,
  "",
  "<Testcase #> <Component Name> <Result File Name> <wb | ab>",
  "",
  ""
};

/* Entry for OMX free handle timeout */

MX_DBG_CMD_ENTRY_T cmdEntryOmtbOmxFreeHandleTimeOut =
{
  "timeout",
  MX_DBG_CMD_TYPE_VAR_UINT16,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_VALID_PTR,
  0,
  0,
  0,
  0,
  0,
  0,
  NULL,
  OMTB_OmxFreeHandleTimeOut,
  "",
  "<Testcase #> <Component Name> <Result File Name> <wb | ab>",
  "",
  ""
};

/* Entry for OMX free handle with NULL handle */

MX_DBG_CMD_ENTRY_T cmdEntryOmtbOmxFreeHandleNullHandle =
{
  "null_handle",
  MX_DBG_CMD_TYPE_VAR_UINT16,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_VALID_PTR,
  0,
  0,
  0,
  0,
  0,
  0,
  NULL,
  OMTB_OmxFreeHandleNullHandle,
  "",
  "<Testcase #> <Component Name> <Result File Name> <wb | ab>",
  "",
  ""
};

/* FreeHandle command list */
MX_DBG_CMD_ENTRY_T* cmdListOmtbFreeHandleTest[] =
{
  &cmdEntryOmtbOmxFreeHandleOnce,
  &cmdEntryOmtbOmxFreeHandleVerMismatch,
  &cmdEntryOmtbOmxFreeHandleTimeOut,
  &cmdEntryOmtbOmxFreeHandleNullHandle,
  NULL
};


/* FreeHandle command table */
MX_DBG_CMD_TABLE_T cmdTblOmtbFreeHandleTest =
{
  MX_DBG_ACCESS_ALL,
  sizeof(cmdListOmtbFreeHandleTest) / sizeof(cmdListOmtbFreeHandleTest[0]),
  cmdListOmtbFreeHandleTest
};


/* Entry for OMX Component FreeHandle */

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryOmxFreeHandleTest =
{
  "freehandle",
  MX_DBG_CMD_TYPE_CMD_TABLE,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_VALID_PTR,
  0,
  0,
  0,
  0,
  0,
  0,
  &cmdTblOmtbFreeHandleTest,
  OMTB_ParseCmdTblEntries,
  "",
  "",
  "",
  ""
};


/* Entry for OMX comp name enum once */

MX_DBG_CMD_ENTRY_T cmdEntryOmtbOmxComponentNameEnumOnce =
{
  "once",
  MX_DBG_CMD_TYPE_VAR_UINT16,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_VALID_PTR,
  0,
  0,
  0,
  0,
  0,
  0,
  NULL,
  OMTB_OmxComponentNameEnumOnce,
  "",
  "<Testcase #> <Component Name> <Result File Name> <wb | ab>",
  "",
  ""
};

/* Entry for OMX comp name enum with NULL comp name */

MX_DBG_CMD_ENTRY_T cmdEntryOmtbOmxComponentNameEnumNullCompName =
{
  "null_comp_name",
  MX_DBG_CMD_TYPE_VAR_UINT16,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_VALID_PTR,
  0,
  0,
  0,
  0,
  0,
  0,
  NULL,
  OMTB_OmxComponentNameEnumNullCompName,
  "",
  "<Testcase #> <Component Name> <Result File Name> <wb | ab>",
  "",
  ""
};

/* Entry for OMX comp name enum till end of list */

MX_DBG_CMD_ENTRY_T cmdEntryOmtbOmxComponentNameEnumNoMore =
{
  "no_more",
  MX_DBG_CMD_TYPE_VAR_UINT16,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_VALID_PTR,
  0,
  0,
  0,
  0,
  0,
  0,
  NULL,
  OMTB_OmxComponentNameEnumNoMore,
  "",
  "<Testcase #> <Component Name> <Result File Name> <wb | ab>",
  "",
  ""
};

/* Entry for OMX comp name enum with version mismatch */

MX_DBG_CMD_ENTRY_T cmdEntryOmtbOmxComponentNameEnumVerMismatch =
{
  "ver_mismatch",
  MX_DBG_CMD_TYPE_VAR_UINT16,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_VALID_PTR,
  0,
  0,
  0,
  0,
  0,
  0,
  NULL,
  OMTB_OmxComponentNameEnumVerMismatch,
  "",
  "<Testcase #> <Component Name> <Result File Name> <wb | ab>",
  "",
  ""
};

/* get comp name command list */
MX_DBG_CMD_ENTRY_T* cmdListOmtbOmxComponentNameEnumTest[] =
{
  &cmdEntryOmtbOmxComponentNameEnumOnce,
  &cmdEntryOmtbOmxComponentNameEnumNullCompName,
  &cmdEntryOmtbOmxComponentNameEnumNoMore,
  &cmdEntryOmtbOmxComponentNameEnumVerMismatch,
  NULL
};


/* get comp name command table */
MX_DBG_CMD_TABLE_T cmdTblOmtbOmxComponentNameEnumTest =
{
  MX_DBG_ACCESS_ALL,
  sizeof(cmdListOmtbOmxComponentNameEnumTest) / sizeof(cmdListOmtbOmxComponentNameEnumTest[0]),
  cmdListOmtbOmxComponentNameEnumTest
};


/* Entry for OMX Component Get Extension Index */

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryOMXComponentNameEnumTest =
{
  "comp_name_enum",
  MX_DBG_CMD_TYPE_CMD_TABLE,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_VALID_PTR,
  0,
  0,
  0,
  0,
  0,
  0,
  &cmdTblOmtbOmxComponentNameEnumTest,
  OMTB_ParseCmdTblEntries,
  "",
  "",
  "",
  ""
};


/* Entry for OMX get roles of comp once */

MX_DBG_CMD_ENTRY_T cmdEntryOmtbOmxGetRolesOfComponentOnce =
{
  "once",
  MX_DBG_CMD_TYPE_VAR_UINT16,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_VALID_PTR,
  0,
  0,
  0,
  0,
  0,
  0,
  NULL,
  OMTB_OmxGetRolesOfComponentOnce,
  "",
  "<Testcase #> <Component Name> <Result File Name> <wb | ab>",
  "",
  ""
};

/* Entry for OMX get roles of comp with NULL comp name */

MX_DBG_CMD_ENTRY_T cmdEntryOmtbOmxGetRolesOfComponentNullCompName =
{
  "null_comp_name",
  MX_DBG_CMD_TYPE_VAR_UINT16,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_VALID_PTR,
  0,
  0,
  0,
  0,
  0,
  0,
  NULL,
  OMTB_OmxGetRolesOfComponentNullCompName,
  "",
  "<Testcase #> <Component Name> <Result File Name> <wb | ab>",
  "",
  ""
};

/* Entry for OMX get roles of comp with NULL ptr to no of comps */

MX_DBG_CMD_ENTRY_T cmdEntryOmtbOmxGetRolesOfComponentNullNumComp =
{
  "null_num_comp",
  MX_DBG_CMD_TYPE_VAR_UINT16,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_VALID_PTR,
  0,
  0,
  0,
  0,
  0,
  0,
  NULL,
  OMTB_OmxGetRolesOfComponentNullNumComp,
  "",
  "<Testcase #> <Component Name> <Result File Name> <wb | ab>",
  "",
  ""
};

/* Entry for OMX get roles of comp with invalid comp name */

MX_DBG_CMD_ENTRY_T cmdEntryOmtbOmxGetRolesOfComponentInvCompName =
{
  "inv_comp_name",
  MX_DBG_CMD_TYPE_VAR_UINT16,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_VALID_PTR,
  0,
  0,
  0,
  0,
  0,
  0,
  NULL,
  OMTB_OmxGetRolesOfComponentInvCompName,
  "",
  "<Testcase #> <Component Name> <Result File Name> <wb | ab>",
  "",
  ""
};

/* get comp name command list */
MX_DBG_CMD_ENTRY_T* cmdListOmtbOmxGetRolesOfCompTest[] =
{
  &cmdEntryOmtbOmxGetRolesOfComponentOnce,
  &cmdEntryOmtbOmxGetRolesOfComponentNullCompName,
  &cmdEntryOmtbOmxGetRolesOfComponentNullNumComp,
  &cmdEntryOmtbOmxGetRolesOfComponentInvCompName,
  NULL
};


/* get comp name command table */
MX_DBG_CMD_TABLE_T cmdTblOmtbOmxGetRolesOfCompTest =
{
  MX_DBG_ACCESS_ALL,
  sizeof(cmdListOmtbOmxGetRolesOfCompTest) / sizeof(cmdListOmtbOmxGetRolesOfCompTest[0]),
  cmdListOmtbOmxGetRolesOfCompTest
};


/* Entry for OMX Component Get roles of comp */

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryOMXGetRolesOfCompTest =
{
  "roles_of_comp",
  MX_DBG_CMD_TYPE_CMD_TABLE,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_VALID_PTR,
  0,
  0,
  0,
  0,
  0,
  0,
  &cmdTblOmtbOmxGetRolesOfCompTest,
  OMTB_ParseCmdTblEntries,
  "",
  "",
  "",
  ""
};


/* Entry for OMX get comps of role once */

MX_DBG_CMD_ENTRY_T cmdEntryOmtbOmxGetComponentsOfRoleOnce =
{
  "once",
  MX_DBG_CMD_TYPE_VAR_UINT16,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_VALID_PTR,
  0,
  0,
  0,
  0,
  0,
  0,
  NULL,
  OMTB_OmxGetComponentsOfRoleOnce,
  "",
  "<Testcase #> <Component Name> <Result File Name> <wb | ab> <Role Name>",
  "",
  ""
};

/* Entry for OMX get comps of role with NULL comp name */

MX_DBG_CMD_ENTRY_T cmdEntryOmtbOmxGetComponentsOfRoleNullRole =
{
  "null_comp_name",
  MX_DBG_CMD_TYPE_VAR_UINT16,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_VALID_PTR,
  0,
  0,
  0,
  0,
  0,
  0,
  NULL,
  OMTB_OmxGetComponentsOfRoleNullRole,
  "",
  "<Testcase #> <Component Name> <Result File Name> <wb | ab> <Role Name>",
  "",
  ""
};

/* Entry for OMX get comps of role with NULL ptr to no of comps */

MX_DBG_CMD_ENTRY_T cmdEntryOmtbOmxGetComponentsOfRoleNullNumComp =
{
  "null_num_comp",
  MX_DBG_CMD_TYPE_VAR_UINT16,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_VALID_PTR,
  0,
  0,
  0,
  0,
  0,
  0,
  NULL,
  OMTB_OmxGetComponentsOfRoleNullNumComp,
  "",
  "<Testcase #> <Component Name> <Result File Name> <wb | ab> <Role Name>",
  "",
  ""
};


/* get comps of role command list */
MX_DBG_CMD_ENTRY_T* cmdListOmtbOmxGetCompsOfRoleTest[] =
{
  &cmdEntryOmtbOmxGetComponentsOfRoleOnce,
  &cmdEntryOmtbOmxGetComponentsOfRoleNullRole,
  &cmdEntryOmtbOmxGetComponentsOfRoleNullNumComp,
  NULL
};


/* get comps of role command table */
MX_DBG_CMD_TABLE_T cmdTblOmtbOmxGetCompsOfRoleTest =
{
  MX_DBG_ACCESS_ALL,
  sizeof(cmdListOmtbOmxGetCompsOfRoleTest) / sizeof(cmdListOmtbOmxGetCompsOfRoleTest[0]),
  cmdListOmtbOmxGetCompsOfRoleTest
};


/* Entry for OMX get comps of role */

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryOMXGetCompsOfRoleTest =
{
  "comps_of_role",
  MX_DBG_CMD_TYPE_CMD_TABLE,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_VALID_PTR,
  0,
  0,
  0,
  0,
  0,
  0,
  &cmdTblOmtbOmxGetCompsOfRoleTest,
  OMTB_ParseCmdTblEntries,
  "",
  "",
  "",
  ""
};


/* Entry for OMX send command once */

MX_DBG_CMD_ENTRY_T cmdEntryOmtbOmxSendCommandOnce =
{
  "once",
  MX_DBG_CMD_TYPE_VAR_UINT16,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_VALID_PTR,
  0,
  0,
  0,
  0,
  0,
  0,
  NULL,
  OMTB_OmxSendCommandOnce,
  "",
  "<Testcase #> <Component Name> <Result File Name> <wb | ab> <Port #>",
  "",
  ""
};

/* Entry for OMX send command with insufficient resoures */

MX_DBG_CMD_ENTRY_T cmdEntryOmtbOmxSendCommandInsuffResources =
{
  "insuff_res",
  MX_DBG_CMD_TYPE_VAR_UINT16,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_VALID_PTR,
  0,
  0,
  0,
  0,
  0,
  0,
  NULL,
  OMTB_OmxSendCommandInsuffResources,
  "",
  "<Testcase #> <Component Name> <Result File Name> <wb | ab> <Port #>",
  "",
  ""
};

/* Entry for OMX send command with NULL handle */

MX_DBG_CMD_ENTRY_T cmdEntryOmtbOmxSendCommandNullHandle =
{
  "null_handle",
  MX_DBG_CMD_TYPE_VAR_UINT16,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_VALID_PTR,
  0,
  0,
  0,
  0,
  0,
  0,
  NULL,
  OMTB_OmxSendCommandNullHandle,
  "",
  "<Testcase #> <Component Name> <Result File Name> <wb | ab> <Port #>",
  "",
  ""
};

/* Entry for OMX send command with invalid command */

MX_DBG_CMD_ENTRY_T cmdEntryOmtbOmxSendCommandInvCommand =
{
  "inv_command",
  MX_DBG_CMD_TYPE_VAR_UINT16,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_VALID_PTR,
  0,
  0,
  0,
  0,
  0,
  0,
  NULL,
  OMTB_OmxSendCommandInvCommand,
  "",
  "<Testcase #> <Component Name> <Result File Name> <wb | ab> <Port #>",
  "",
  ""
};

/* Entry for OMX send command timeout */

MX_DBG_CMD_ENTRY_T cmdEntryOmtbOmxSendCommandTimeOut =
{
  "timeout",
  MX_DBG_CMD_TYPE_VAR_UINT16,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_VALID_PTR,
  0,
  0,
  0,
  0,
  0,
  0,
  NULL,
  OMTB_OmxSendCommandTimeOut,
  "",
  "<Testcase #> <Component Name> <Result File Name> <wb | ab> <Port #>",
  "",
  ""
};

/* Entry for OMX send command timeout */

MX_DBG_CMD_ENTRY_T cmdEntryOmtbOmxSendCommandOnWrongPort =
{
  "wrong_port",
  MX_DBG_CMD_TYPE_VAR_UINT16,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_VALID_PTR,
  0,
  0,
  0,
  0,
  0,
  0,
  NULL,
  OMTB_OmxSendCommandOnWrongPort,
  "",
  "<Testcase #> <Component Name> <Result File Name> <wb | ab> <Port #>",
  "",
  ""
};


/* sencommand entry command list */

PRIVATE MX_DBG_CMD_ENTRY_T* cmdListOmxApiSendCommandTest[] =
{
  &cmdEntryOmtbOmxSendCommandOnce,
  &cmdEntryOmtbOmxSendCommandInsuffResources,
  &cmdEntryOmtbOmxSendCommandNullHandle,
  &cmdEntryOmtbOmxSendCommandInvCommand,
  &cmdEntryOmtbOmxSendCommandTimeOut,
  &cmdEntryOmtbOmxSendCommandOnWrongPort,
  NULL
};


/* comp command table */

MX_DBG_CMD_TABLE_T cmdTblOmxApiSendCommandTest =
{
  MX_DBG_ACCESS_ALL,
  sizeof(cmdListOmxApiSendCommandTest)/sizeof(cmdListOmxApiSendCommandTest[0]),
  cmdListOmxApiSendCommandTest
};


/* Entry for OMX Send Command*/

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryOmxSendCommandTest =
{
  "send_command",
  MX_DBG_CMD_TYPE_CMD_TABLE,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_VALID_PTR,
  0,
  0,
  0,
  0,
  0,
  0,
  &cmdTblOmxApiSendCommandTest,
  OMTB_ParseCmdTblEntries,
  "",
  "",
  "",
  ""
};


/* Entry for OMX etb once */

MX_DBG_CMD_ENTRY_T cmdEntryOmxEmptyThisBufferOnce =
{
  "once",
  MX_DBG_CMD_TYPE_VAR_UINT16,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_VALID_PTR,
  0,
  0,
  0,
  0,
  0,
  0,
  NULL,
  OMTB_OmxEmptyThisBufferOnce,
  "",
  "<Testcase #> <Component Name> <Result File Name> <wb | ab> <Instance #>",
  "",
  ""
};

/* Entry for OMX etb with NULL handle */

MX_DBG_CMD_ENTRY_T cmdEntryOmxEmptyThisBufferNullHandle =
{
  "null_handle",
  MX_DBG_CMD_TYPE_VAR_UINT16,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_VALID_PTR,
  0,
  0,
  0,
  0,
  0,
  0,
  NULL,
  OMTB_OmxEmptyThisBufferNullHandle,
  "",
  "<Testcase #> <Component Name> <Result File Name> <wb | ab> <Instance #>",
  "",
  ""
};

/* Entry for OMX etb with timeout */

MX_DBG_CMD_ENTRY_T cmdEntryOmxEmptyThisBufferTimeOut =
{
  "timeout",
  MX_DBG_CMD_TYPE_VAR_UINT16,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_VALID_PTR,
  0,
  0,
  0,
  0,
  0,
  0,
  NULL,
  OMTB_OmxEmptyThisBufferTimeOut,
  "",
  "<Testcase #> <Component Name> <Result File Name> <wb | ab> <Instance #>",
  "",
  ""
};

/* Entry for OMX etb in idle state */

MX_DBG_CMD_ENTRY_T cmdEntryOmxEmptyThisBufferIdleState =
{
  "idle_state",
  MX_DBG_CMD_TYPE_VAR_UINT16,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_VALID_PTR,
  0,
  0,
  0,
  0,
  0,
  0,
  NULL,
  OMTB_OmxEmptyThisBufferIdleState,
  "",
  "<Testcase #> <Component Name> <Result File Name> <wb | ab> <Instance #>",
  "",
  ""
};

/* Entry for OMX etb with wrong port */

MX_DBG_CMD_ENTRY_T cmdEntryOmxEmptyThisBufferWrongPort =
{
  "wrong_port",
  MX_DBG_CMD_TYPE_VAR_UINT16,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_VALID_PTR,
  0,
  0,
  0,
  0,
  0,
  0,
  NULL,
  OMTB_OmxEmptyThisBufferWrongPort,
  "",
  "<Testcase #> <Component Name> <Result File Name> <wb | ab> <Instance #>",
  "",
  ""
};

/* empty this buffer command list */
MX_DBG_CMD_ENTRY_T* cmdListOmtbEmptyThisBufferTest[] =
{
  &cmdEntryOmxEmptyThisBufferOnce,
  &cmdEntryOmxEmptyThisBufferNullHandle,
  &cmdEntryOmxEmptyThisBufferTimeOut,
  &cmdEntryOmxEmptyThisBufferIdleState,
  &cmdEntryOmxEmptyThisBufferWrongPort,
  NULL
};


/* empty this buffer command table */
MX_DBG_CMD_TABLE_T cmdTblOmtbEmptyThisBufferTest =
{
  MX_DBG_ACCESS_ALL,
  sizeof(cmdListOmtbEmptyThisBufferTest) / sizeof(cmdListOmtbEmptyThisBufferTest[0]),
  cmdListOmtbEmptyThisBufferTest
};


/* Entry for OMX empty this buffer */

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryOmxEmptyThisBufferTest =
{
  "etb",
  MX_DBG_CMD_TYPE_CMD_TABLE,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_VALID_PTR,
  0,
  0,
  0,
  0,
  0,
  0,
  &cmdTblOmtbEmptyThisBufferTest,
  OMTB_ParseCmdTblEntries,
  "",
  "",
  "",
  ""
};


/* Entry for OMX ftb once */

MX_DBG_CMD_ENTRY_T cmdEntryOmxFillThisBufferOnce =
{
  "once",
  MX_DBG_CMD_TYPE_VAR_UINT16,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_VALID_PTR,
  0,
  0,
  0,
  0,
  0,
  0,
  NULL,
  OMTB_OmxFillThisBufferOnce,
  "",
  "<Testcase #> <Component Name> <Result File Name> <wb | ab> <Instance #>",
  "",
  ""
};

/* Entry for OMX ftb with NULL handle */

MX_DBG_CMD_ENTRY_T cmdEntryOmxFillThisBufferNullHandle =
{
  "null_handle",
  MX_DBG_CMD_TYPE_VAR_UINT16,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_VALID_PTR,
  0,
  0,
  0,
  0,
  0,
  0,
  NULL,
  OMTB_OmxFillThisBufferNullHandle,
  "",
  "<Testcase #> <Component Name> <Result File Name> <wb | ab> <Instance #>",
  "",
  ""
};

/* Entry for OMX ftb with timeout */

MX_DBG_CMD_ENTRY_T cmdEntryOmxFillThisBufferTimeOut =
{
  "timeout",
  MX_DBG_CMD_TYPE_VAR_UINT16,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_VALID_PTR,
  0,
  0,
  0,
  0,
  0,
  0,
  NULL,
  OMTB_OmxFillThisBufferTimeOut,
  "",
  "<Testcase #> <Component Name> <Result File Name> <wb | ab> <Instance #>",
  "",
  ""
};

/* Entry for OMX ftb in idle state */

MX_DBG_CMD_ENTRY_T cmdEntryOmxFillThisBufferIdleState =
{
  "idle_state",
  MX_DBG_CMD_TYPE_VAR_UINT16,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_VALID_PTR,
  0,
  0,
  0,
  0,
  0,
  0,
  NULL,
  OMTB_OmxFillThisBufferIdleState,
  "",
  "<Testcase #> <Component Name> <Result File Name> <wb | ab> <Instance #>",
  "",
  ""
};

/* Entry for OMX ftb with wrong port */

MX_DBG_CMD_ENTRY_T cmdEntryOmxFillThisBufferWrongPort =
{
  "wrong_port",
  MX_DBG_CMD_TYPE_VAR_UINT16,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_VALID_PTR,
  0,
  0,
  0,
  0,
  0,
  0,
  NULL,
  OMTB_OmxFillThisBufferWrongPort,
  "",
  "<Testcase #> <Component Name> <Result File Name> <wb | ab> <Instance #>",
  "",
  ""
};


/* fill this buffer command list */
MX_DBG_CMD_ENTRY_T* cmdListOmtbFillThisBufferTest[] =
{
  &cmdEntryOmxFillThisBufferOnce,
  &cmdEntryOmxFillThisBufferNullHandle,
  &cmdEntryOmxFillThisBufferTimeOut,
  &cmdEntryOmxFillThisBufferIdleState,
  &cmdEntryOmxFillThisBufferWrongPort,
  NULL
};


/* fill this buffer command table */
MX_DBG_CMD_TABLE_T cmdTblOmtbFillThisBufferTest =
{
  MX_DBG_ACCESS_ALL,
  sizeof(cmdListOmtbFillThisBufferTest) / sizeof(cmdListOmtbFillThisBufferTest[0]),
  cmdListOmtbFillThisBufferTest
};


/* Entry for OMX fill this buffer */

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryOmxFillThisBufferTest =
{
  "ftb",
  MX_DBG_CMD_TYPE_CMD_TABLE,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_VALID_PTR,
  0,
  0,
  0,
  0,
  0,
  0,
  &cmdTblOmtbFillThisBufferTest,
  OMTB_ParseCmdTblEntries,
  "",
  "",
  "",
  ""
};



/* comp entry command list */

PRIVATE MX_DBG_CMD_ENTRY_T* cmdListOmxApiTest[] =
{
  &cmdEntryOmxInitTest,
  &cmdEntryOmxGetHandleTest,
  &cmdEntryOmxGetCompVersionTest,
  &cmdEntryOmxAllocUseBufferTest,
  &cmdEntryOmxFreeBufferTest,
  &cmdEntryOmxSetParamTest,
  &cmdEntryOmxSetConfigTest,
  &cmdEntryOmxSendCommandTest,
  &cmdEntryOmxSetupTunnelTest,
  &cmdEntryOmxGetParamTest,
  &cmdEntryOmxGetConfigTest,
  &cmdEntryOmxGetStateTest,
  &cmdEntryOmxGetExtensionIndexTest,
  &cmdEntryOMXComponentNameEnumTest,
  &cmdEntryOMXGetRolesOfCompTest,
  &cmdEntryOMXGetCompsOfRoleTest,
  &cmdEntryOmxFreeHandleTest,
  &cmdEntryOmxDeInitTest,
  &cmdEntryOmxEmptyThisBufferTest,
  &cmdEntryOmxFillThisBufferTest,
  NULL
};

/* comp command table */

MX_DBG_CMD_TABLE_T cmdTblOmxApiTest =
{
  MX_DBG_ACCESS_ALL,
  sizeof(cmdListOmxApiTest)/sizeof(cmdListOmxApiTest[0]),
  cmdListOmxApiTest
};


/*----------------------------- end of file ---------------------------------*/
