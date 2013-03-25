/*
 * omtbOmxApiCmdEntries.c
 *
 * This file contains function dispatchers for common OMX IL APIs across
 *  the components.
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

MX_DBG_CMD_TABLE_T   funcCmdTbl;              // Command table for func command


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

/* Entry for OMX Core Init */

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryOmxInit =
{
  "init",
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
  OMTB_OmxInit,
  "",
  "",
  "",
  ""
};


/* Entry for OMX Core DeInit */

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryOmxDeInit =
{
  "uninit",
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
  OMTB_OmxDeinit,
  "",
  "",
  "",
  ""
};


/* GetHandle command list */
MX_DBG_CMD_ENTRY_T* cmdListOmtbGetHandle[OMTB_MAX_CLASS] =
{
  NULL
};


/* GetHandle command table */
MX_DBG_CMD_TABLE_T cmdTblOmtbGetHandle =
{
  MX_DBG_ACCESS_ALL,
  sizeof(cmdListOmtbGetHandle) / sizeof(cmdListOmtbGetHandle[0]),
  cmdListOmtbGetHandle
};


/* Entry for OMX Component GetHandle */
PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryOmxGetHandle =
{
  "gethandle",
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
  OMTB_OmxGetHandle,
  "",
  "<dsrc | dsnk | vfcc | vfdc | nf | dei | sc | h264venc | h264vdec> <instance #> <template #>",
  "",
  ""
};


/* Entry for OMX Component GetCompVersion */

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryOmxGetCompVersion =
{
  "compver",
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
  OMTB_OmxGetCompVersion,
  "",
  "    <dsrc | dsnk | vfcc | vfdc | nf | dei | sc | h264venc | h264vdec> <instance #>",
  "",
  ""
};


/* SetParam command list */
MX_DBG_CMD_ENTRY_T* cmdListOmtbSetParam[OMTB_MAX_CLASS] =
{
  NULL
};


/* SetParam command table */
MX_DBG_CMD_TABLE_T cmdTblOmtbSetParam =
{
  MX_DBG_ACCESS_ALL,
  sizeof(cmdListOmtbSetParam) / sizeof(cmdListOmtbSetParam[0]),
  cmdListOmtbSetParam
};


/* Entry for OMX Component SetParam */
PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryOmxSetParam =
{
  "setparam",
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
  OMTB_OmxSetParam,
  "",
  "<dsrc | dsnk | vfcc | vfdc | nf | dei | sc | h264venc | h264vdec> <instance #> <template #> \
<port #> <OMX Index>",
  "",
  ""
};

/* SetConfig command list */
MX_DBG_CMD_ENTRY_T* cmdListOmtbSetConfig[OMTB_MAX_CLASS] =
{
  NULL
};


/* SetConfig command table */
MX_DBG_CMD_TABLE_T cmdTblOmtbSetConfig =
{
  MX_DBG_ACCESS_ALL,
  sizeof(cmdListOmtbSetConfig) / sizeof(cmdListOmtbSetConfig[0]),
  cmdListOmtbSetConfig
};


/* Entry for OMX Component SetConfig */
PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryOmxSetConfig =
{
  "setconfig",
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
  OMTB_OmxSetConfig,
  "",
  "<dsrc | dsnk | vfcc | vfdc | nf | dei | sc | h264venc | h264vdec> <instance #> <template #> \
<port #> <OMX Index>",
  "",
  ""
};

/* GetParam command list */
MX_DBG_CMD_ENTRY_T* cmdListOmtbGetParam[OMTB_MAX_CLASS] =
{
  NULL
};


/* GetParam command table */
MX_DBG_CMD_TABLE_T cmdTblOmtbGetParam =
{
  MX_DBG_ACCESS_ALL,
  sizeof(cmdListOmtbGetParam) / sizeof(cmdListOmtbGetParam[0]),
  cmdListOmtbGetParam
};


/* Entry for OMX Component GetParam */
PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryOmxGetParam =
{
  "getparam",
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
  OMTB_OmxGetParam,
  "",
  "<dsrc | dsnk | vfcc | vfdc | nf | dei | sc | h264venc | h264vdec> <instance #> <template #> \
<port #> <OMX Index>",
  "",
  ""
};

/* GetConfig command list */
MX_DBG_CMD_ENTRY_T* cmdListOmtbGetConfig[OMTB_MAX_CLASS] =
{
  NULL
};


/* GetConfig command table */
MX_DBG_CMD_TABLE_T cmdTblOmtbGetConfig =
{
  MX_DBG_ACCESS_ALL,
  sizeof(cmdListOmtbGetConfig) / sizeof(cmdListOmtbGetConfig[0]),
  cmdListOmtbGetConfig
};


/* Entry for OMX Component GetConfig */
PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryOmxGetConfig =
{
  "getconfig",
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
  OMTB_OmxGetConfig,
  "",
  "<dsrc | dsnk | vfcc | vfdc | nf | dei | sc | h264venc | h264vdec> <instance #> <template #> \
<port #> <OMX Index>",
  "",
  ""
};


/* Entry for OMX Component GetExtensionIndex */

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryOmxGetExtensionIndex =
{
  "getextindex",
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
  OMTB_OmxGetExtensionIndex,
  "",
  "<dsrc | dsnk | vfcc | vfdc | nf | dei | sc | h264venc | h264vdec> <instance #> <Index String>",
  "",
  ""
};


/* Entry for OMX Component GetState */

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryOmxGetState =
{
  "getstate",
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
  OMTB_OmxGetState,
  "",
  "   <dsrc | dsnk | vfcc | vfdc | nf | dei | sc | h264venc | h264vdec> <instance #>",
  "",
  ""
};


/* Entry for OMX Component SetupTunnel */

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryOmxSetupTunnel =
{
  "setuptunnel",
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
  OMTB_OmxSetupTunnel,
  "",
  "<dsrc | dsnk | vfcc | vfdc | nf | dei | sc | h264venc | h264vdec> <instance #> <port #> \
<dsrc | dsnk | vfcc | vfdc | nf | dei | sc | h264venc | h264vdec> <instance #> <port #>",
  "",
  ""
};



/* Entry for OMX Component SetupTunnel */

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryOmxConnect =
{
  "connect",
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
  OMTB_OmxConnect,
  "",
  "<dsrc | dsnk | vfcc | vfdc | nf | dei | sc | h264venc | h264vdec> <instance #> <port #> \
<dsrc | dsnk | vfcc | vfdc | nf | dei | sc | h264venc | h264vdec> <instance #> <port #>",
  "",
  ""
};

/* FreeHandle command list */
MX_DBG_CMD_ENTRY_T* cmdListOmtbFreeHandle[OMTB_MAX_CLASS] =
{
  NULL
};


/* FreeHandle command table */
MX_DBG_CMD_TABLE_T cmdTblOmtbFreeHandle =
{
  MX_DBG_ACCESS_ALL,
  sizeof(cmdListOmtbFreeHandle) / sizeof(cmdListOmtbFreeHandle[0]),
  cmdListOmtbFreeHandle
};


/* Entry for OMX Component FreeHandle */
PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryOmxFreeHandle =
{
  "freehandle",
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
  OMTB_OmxFreeHandle,
  "",
  "<dsrc | dsnk | vfcc | vfdc | nf | dei | sc | h264venc | h264vdec> <instance #> <template #>",
  "",
  ""
};

/* SendCommandState command list */
MX_DBG_CMD_ENTRY_T* cmdListOmtbSendCommandState[OMTB_MAX_CLASS] =
{
  NULL
};


/* SendCommandState command table */
MX_DBG_CMD_TABLE_T cmdTblOmtbSendCommandState =
{
  MX_DBG_ACCESS_ALL,
  sizeof(cmdListOmtbSendCommandState) / sizeof(cmdListOmtbSendCommandState[0]),
  cmdListOmtbSendCommandState
};


/* Entry for OMX SendCommandState*/
PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryOmxSendCommandState =
{
  "state",
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
  OMTB_OmxSendCommandState,
  "",
  "<dsrc | dsnk | vfcc | vfdc | nf | dei | sc | h264venc | h264vdec> <instance #> <loaded | idle | exec>",
  "",
  ""
};

/* Entry for OMX SendCommandPort*/
PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryOmxSendCommandPort =
{
  "port",
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
  OMTB_OmxSendCommandPort,
  "",
  " <dsrc | dsnk | vfcc | vfdc | nf | dei | sc | h264venc | h264vdec> <instance #> \
<enable|disable> <port #>",
  "",
  ""
};


/* Entry for OMX SendCommandFlush*/

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryOmxSendCommandFlush =
{
  "flush",
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
  OMTB_OmxSendCommandFlush,
  "",
  "<dsrc | dsnk | vfcc | vfdc | nf | dei | sc | h264venc | h264vdec> <instance #> <port #>",
  "",
  ""
};

/* SendCommandMark command list */
MX_DBG_CMD_ENTRY_T* cmdListOmtbSendCommandMark[OMTB_MAX_CLASS] =
{
  NULL
};

/* SendCommandMark command table */
MX_DBG_CMD_TABLE_T cmdTblOmtbSendCommandMark =
{
  MX_DBG_ACCESS_ALL,
  sizeof(cmdListOmtbSendCommandMark) / sizeof(cmdListOmtbSendCommandMark[0]),
  cmdListOmtbSendCommandMark
};


/* Entry for OMX SendCommandMark*/

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryOmxSendCommandMark =
{
  "mark",
  MX_DBG_CMD_TYPE_CMD_TABLE,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_VALID_PTR,
  0,
  0,
  0,
  0,
  0,
  0,
  &cmdTblOmtbSendCommandMark,
  OMTB_ParseCmdTblEntries,
  "",
  "",
  "",
  ""
};


/* sencommand entry command list */

PRIVATE MX_DBG_CMD_ENTRY_T* cmdListOmxApiSendCommand[] =
{
  &cmdEntryOmxSendCommandState,
  &cmdEntryOmxSendCommandPort,
  &cmdEntryOmxSendCommandFlush,
  &cmdEntryOmxSendCommandMark,
  NULL
};


/* Entry for OMX Component Get Extension Index */

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryOMXComponentNameEnum =
{
  "getcompname",
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
  OMTB_OMXComponentNameEnum,
  "",
  "",
  "",
  ""
};


/* Entry for OMX Component Get Extension Index */

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryOMXRoleEnum =
{
  "rolesbycomp",
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
  OMTB_OMXRoleEnum,
  "",
  "<Component name>",
  "",
  ""
};


/* Entry for OMX Component Get Extension Index */

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryOMXComponentEnumByRole =
{
  "compsbyrole",
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
  OMTB_OMXComponentEnumByRole,
  "",
  "<Role name>",
  "",
  ""
};


/* comp command table */

MX_DBG_CMD_TABLE_T cmdTblOmxApiSendCommand =
{
  MX_DBG_ACCESS_ALL,
  sizeof(cmdListOmxApiSendCommand)/sizeof(cmdListOmxApiSendCommand[0]),
  cmdListOmxApiSendCommand
};


/* Entry for OMX Send Command*/

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryOmxSendCommand =
{
  "sendcommand",
  MX_DBG_CMD_TYPE_CMD_TABLE,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_VALID_PTR,
  0,
  0,
  0,
  0,
  0,
  0,
  &cmdTblOmxApiSendCommand,
  OMTB_ParseCmdTblEntries,
  "",
  "",
  "",
  ""
};


/* comp entry command list */

PRIVATE MX_DBG_CMD_ENTRY_T* cmdListOmxApi[] =
{
  &cmdEntryOmxInit,
  &cmdEntryOmxGetHandle,
  &cmdEntryOmxGetCompVersion,
  &cmdEntryOmxSetParam,
  &cmdEntryOmxSetConfig,
  &cmdEntryOmxSendCommand,
  &cmdEntryOmxSetupTunnel,
  &cmdEntryOmxConnect,
  &cmdEntryOmxGetParam,
  &cmdEntryOmxGetConfig,
  &cmdEntryOmxGetState,
  &cmdEntryOmxGetExtensionIndex,
  &cmdEntryOMXComponentNameEnum,
  &cmdEntryOMXRoleEnum,
  &cmdEntryOMXComponentEnumByRole,
  &cmdEntryOmxFreeHandle,
  &cmdEntryOmxDeInit,
  NULL
};

/* comp command table */

MX_DBG_CMD_TABLE_T cmdTblOmxApi =
{
  MX_DBG_ACCESS_ALL,
  sizeof(cmdListOmxApi)/sizeof(cmdListOmxApi[0]),
  cmdListOmxApi
};


/*******************************************************************************
 *      Func command entries
 ******************************************************************************/

/* viddec command list entry */

MX_DBG_CMD_ENTRY_T* viddecCmdList[OMTB_MAX_VIDDEC] =
{
  NULL
};


/* viddec command table */

MX_DBG_CMD_TABLE_T viddecCmdTbl=
{
  MX_DBG_ACCESS_ALL,
  sizeof(viddecCmdList) / sizeof(viddecCmdList[0]),
  viddecCmdList
};


/* Command entry for video decoder */
MX_DBG_CMD_ENTRY_T cmdEntryFuncVidDec =
{
  "viddec",
  MX_DBG_CMD_TYPE_CMD_TABLE,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_VALID_PTR,
  0,
  0,
  0,
  0,
  0,
  0,
  &viddecCmdTbl,
  OMTB_ParseCmdTblEntries,
  "",
  "",
  "",
  ""
};


/* auddec command list entry */

MX_DBG_CMD_ENTRY_T* auddecCmdList[OMTB_MAX_AUDDEC] =
{
  NULL
};


/* auddec command table */

MX_DBG_CMD_TABLE_T auddecCmdTbl=
{
  MX_DBG_ACCESS_ALL,
  sizeof(auddecCmdList) / sizeof(auddecCmdList[0]),
  auddecCmdList
};


/* Command entry for audio decoder */

MX_DBG_CMD_ENTRY_T cmdEntryFuncAudDec =
{
  "auddec",
  MX_DBG_CMD_TYPE_CMD_TABLE,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_VALID_PTR,
  0,
  0,
  0,
  0,
  0,
  0,
  &auddecCmdTbl,
  OMTB_ParseCmdTblEntries,
  "",
  "",
  "",
  ""
};


/* videnc command list entry */

MX_DBG_CMD_ENTRY_T* videncCmdList[OMTB_MAX_VIDENC] =
{
  NULL
};


/* videnc command table */

MX_DBG_CMD_TABLE_T videncCmdTbl=
{
  MX_DBG_ACCESS_ALL,
  sizeof(videncCmdList) / sizeof(videncCmdList[0]),
  videncCmdList
};


/* Command entry for video encoders */
MX_DBG_CMD_ENTRY_T cmdEntryFuncVidEnc =
{
  "videnc",
  MX_DBG_CMD_TYPE_CMD_TABLE,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_VALID_PTR,
  0,
  0,
  0,
  0,
  0,
  0,
  &videncCmdTbl,
  OMTB_ParseCmdTblEntries,
  "",
  "",
  "",
  ""
};


/* audenc command list entry */

MX_DBG_CMD_ENTRY_T* audencCmdList[OMTB_MAX_AUDENC] =
{
  NULL
};


/* audenc command table */

MX_DBG_CMD_TABLE_T audencCmdTbl=
{
  MX_DBG_ACCESS_ALL,
  sizeof(audencCmdList) / sizeof(audencCmdList[0]),
  audencCmdList
};


/* Command entry for audio encoder */

MX_DBG_CMD_ENTRY_T cmdEntryFuncAudEnc =
{
  "audenc",
  MX_DBG_CMD_TYPE_CMD_TABLE,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_VALID_PTR,
  0,
  0,
  0,
  0,
  0,
  0,
  &audencCmdTbl,
  OMTB_ParseCmdTblEntries,
  "",
  "",
  "",
  ""
};


/* vpss command list entry */

MX_DBG_CMD_ENTRY_T* vpssCmdList[OMTB_MAX_HDVPSS] =
{
  NULL
};


/* vpss command table */

MX_DBG_CMD_TABLE_T vpssCmdTbl =
{
  MX_DBG_ACCESS_ALL,
  sizeof(vpssCmdList) / sizeof(vpssCmdList[0]),
  vpssCmdList
};


/* Command entry for HD VPSS VFDC */
MX_DBG_CMD_ENTRY_T cmdEntryFuncHdVpss =
{
  "hdvpss",
  MX_DBG_CMD_TYPE_CMD_TABLE,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_VALID_PTR,
  0,
  0,
  0,
  0,
  0,
  0,
  &vpssCmdTbl,
  OMTB_ParseCmdTblEntries,
  "",
  "",
  "",
  ""
};


/* alsa command list entry */
/*FIXME: The following macro has beeen added to resolve the build issues when 
         OMTB runs on Video-M3 */  
#ifndef __ti__
MX_DBG_CMD_ENTRY_T* alsaCmdList[OMTB_MAX_ALSA] =
{
  NULL
};

/* alsa command table */
MX_DBG_CMD_TABLE_T alsaCmdTbl=
{
  MX_DBG_ACCESS_ALL,
  sizeof(alsaCmdList) / sizeof(alsaCmdList[0]),
  alsaCmdList
};

/* Command entry for ALSA */
MX_DBG_CMD_ENTRY_T cmdEntryFuncAlsa =
{
  "alsa",
  MX_DBG_CMD_TYPE_CMD_TABLE,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_VALID_PTR,
  0,
  0,
  0,
  0,
  0,
  0,
  &alsaCmdTbl,
  OMTB_ParseCmdTblEntries,
  "",
  "",
  "",
  ""
};
#endif //#ifndef __ti__
/* sampComp command list entry */

MX_DBG_CMD_ENTRY_T* sampcompCmdList[OMTB_MAX_SAMPCOMP] =
{
  NULL
};


/* sampComp command table */

MX_DBG_CMD_TABLE_T sampcompCmdTbl=
{
  MX_DBG_ACCESS_ALL,
  sizeof(sampcompCmdList) / sizeof(sampcompCmdList[0]),
  sampcompCmdList
};


/* Command entry for sampComp */

MX_DBG_CMD_ENTRY_T cmdEntryFuncSampCompClass =
{
  "sampcomp",
  MX_DBG_CMD_TYPE_CMD_TABLE,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_VALID_PTR,
  0,
  0,
  0,
  0,
  0,
  0,
  &sampcompCmdTbl,
  OMTB_ParseCmdTblEntries,
  "",
  "",
  "",
  ""
};


/* func command list entry */

MX_DBG_CMD_ENTRY_T* funcCmdList[OMTB_MAX_CLASS] =
{
  NULL
};


/* func command table */

MX_DBG_CMD_TABLE_T funcCmdTbl=
{
  MX_DBG_ACCESS_ALL,
  sizeof(funcCmdList) / sizeof(funcCmdList[0]),
  funcCmdList
};


/*----------------------------- end of file ---------------------------------*/
