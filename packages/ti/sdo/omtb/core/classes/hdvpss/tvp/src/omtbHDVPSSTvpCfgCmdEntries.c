/*
 * omtbHDVPSSTvpCfgCmdEntries.c
 *
 * This file contains command entries for configuration parameters.
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


/******************************************************************************\
 *      Local Defines
\******************************************************************************/


/******************************************************************************\
 *      Data type definitions
\******************************************************************************/


/******************************************************************************\
 *      Extern Object Definitions
\******************************************************************************/
extern MX_DBG_CMD_TABLE_T cmdTblIndexParamVFCCHwPortPropertiesConfig;
extern MX_DBG_CMD_TABLE_T cmdTblIndexParamVFCCHwPortIDConfig;
extern MX_DBG_CMD_TABLE_T cmdTblIndexParamCTRLVidDecInfoConfig;

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
 *  OMTB component configuration parameter command entries - TVP
 ******************************************************************************/

/*******************************************************************************
 *      TVP config params
 ******************************************************************************/

/* Entry for Set OMX Component Name */

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryVPSSTvpCompName =
{
  "compname",
  MX_DBG_CMD_TYPE_VAR_STR_BUF,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMTB_VPSS_TVP_CONFIG_PARAMS,sBasicParams.compName),
  FIELDOFFSET(OMTB_VPSS_TVP_CONFIG_PARAMS,sBasicParams.inputFile) -
  FIELDOFFSET(OMTB_VPSS_TVP_CONFIG_PARAMS,sBasicParams.compName),
  0,
  0,
  OMX_MAX_STRINGNAME_SIZE,
  (int)NULL,
  NULL,
  XdbgCmdVarFunc,
  "OMX Component name............................",
  "<omx_comp_name>",
  "",
  ""
};

/* Entry to set params of OMX_TI_IndexParamVFCCHwPortProperties index*/
PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryVPSSTvpIndexParamVFCCHwPortPropertiesConfig =
{
  "OMX_TI_IndexParamVFCCHwPortProperties",
  MX_DBG_CMD_TYPE_CMD_TABLE,
  MX_DBG_CMD_OPT_INST_CUR |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMTB_VPSS_TVP_CONFIG_PARAMS,sHwPortParam),
  0,
  0,
  0,
  0,
  0,
  &cmdTblIndexParamVFCCHwPortPropertiesConfig,
  XdbgCmdTblFunc,
  "OMX_TI_IndexParamVFCCHwPortProperties Index Parameters:",
  "",
  "",
  ""
};

/* Entry to set params of OMX_TI_IndexParamVFCCHwPortID index*/
PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryVPSSTvpIndexParamVFCCHwPortIDConfig =
{
  "OMX_TI_IndexParamVFCCHwPortID",
  MX_DBG_CMD_TYPE_CMD_TABLE,
  MX_DBG_CMD_OPT_INST_CUR |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMTB_VPSS_TVP_CONFIG_PARAMS,sHwPortId),
  0,
  0,
  0,
  0,
  0,
  &cmdTblIndexParamVFCCHwPortIDConfig,
  XdbgCmdTblFunc,
  "OMX_TI_IndexParamVFCCHwPortID Index Parameters:",
  "",
  "",
  ""
};

/* Entry to set params of OMX_TI_IndexParamCTRLVidDecInfo index*/
PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryVPSSTvpIndexParamCTRLVidDecInfoConfig =
{
  "OMX_TI_IndexParamCTRLVidDecInfo",
  MX_DBG_CMD_TYPE_CMD_TABLE,
  MX_DBG_CMD_OPT_INST_CUR |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMTB_VPSS_TVP_CONFIG_PARAMS,sVidDecParam),
  0,
  0,
  0,
  0,
  0,
  &cmdTblIndexParamCTRLVidDecInfoConfig,
  XdbgCmdTblFunc,
  "OMX_TI_IndexParamCTRLVidDecInfo Index Parameters:",
  "",
  "",
  ""
};

MX_DBG_CMD_ENTRY_T* cmdListVPSSTvpConfig[] =
{
  &cmdEntryVPSSTvpCompName,
  &cmdEntryVPSSTvpIndexParamVFCCHwPortPropertiesConfig,
  &cmdEntryVPSSTvpIndexParamVFCCHwPortIDConfig,
  &cmdEntryVPSSTvpIndexParamCTRLVidDecInfoConfig,
  NULL
};


/* VPSS tvp config command table */

MX_DBG_CMD_TABLE_T cmdTblVPSSTvpConfig =
{
  MX_DBG_ACCESS_ALL,
  sizeof(cmdListVPSSTvpConfig)/sizeof(cmdListVPSSTvpConfig[0]),
  cmdListVPSSTvpConfig
};


/* VPSS tvp config command entry */

MX_DBG_CMD_ENTRY_T cmdEntryVPSSTvpConfig =
{
  OMTB_VPSS_TVP_COMP_REF_STR,
  MX_DBG_CMD_TYPE_CMD_TABLE,
  MX_DBG_CMD_OPT_INST_CUR |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMTB_TEMPLATE_INFO,vpssTvpTemplate),
  0,
  0,
  0,
  0,
  0,
  &cmdTblVPSSTvpConfig,
  XdbgCmdTblFunc,
  "\nVPSS tvp Config Parameters:\n",
  "",
  "",
  ""
};


/*----------------------------- end of file ---------------------------------*/
