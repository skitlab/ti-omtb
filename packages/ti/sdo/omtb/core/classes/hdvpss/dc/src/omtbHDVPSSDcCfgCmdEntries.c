/*
 * omtbHDVPSSDcCfgCmdEntries.c
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
#include "omx_vfdc.h"
//#include "omx_vfdc_priv.h"

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

/******************************************************************************\
 *      Globals
\******************************************************************************/
extern MX_DBG_CMD_TABLE_T cmdTblIndexParamVFDCDriverInstIdConfig;
extern MX_DBG_CMD_TABLE_T cmdTblIndexParamVFDCCustomModeInfoConfig;

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
 *  OMTB component configuration parameter command entries - DC
 ******************************************************************************/

/*******************************************************************************
 *      DC config params
 ******************************************************************************/

/* Entry for Set OMX Component Name */

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryVPSSDcCompName =
{
  "compname",
  MX_DBG_CMD_TYPE_VAR_STR_BUF,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMTB_VPSS_DC_CONFIG_PARAMS,sBasicParams.compName),
  FIELDOFFSET(OMTB_VPSS_DC_CONFIG_PARAMS,sBasicParams.inputFile) -
  FIELDOFFSET(OMTB_VPSS_DC_CONFIG_PARAMS,sBasicParams.compName),
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

/* Entry to set params of OMX_TI_IndexParamVFDCDriverInstId index*/
PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryVPSSDcIndexParamVFDCDriverInstIdConfig =
{
  "OMX_TI_IndexParamVFDCDriverInstId",
  MX_DBG_CMD_TYPE_CMD_TABLE,
  MX_DBG_CMD_OPT_INST_CUR |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMTB_VPSS_DC_CONFIG_PARAMS,sDvrInstId),
  0,
  0,
  0,
  0,
  0,
  &cmdTblIndexParamVFDCDriverInstIdConfig,
  XdbgCmdTblFunc,
  "OMX_TI_IndexParamVFDCDriverInstId Index Parameters:",
  "",
  "",
  ""
};

/* Entry to set params of OMX_TI_IndexParamVFDCCustomModeInfo index*/
PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryVPSSDcIndexParamVFDCCustomModeInfoConfig =
{
  "OMX_TI_IndexParamVFDCCustomModeInfo",
  MX_DBG_CMD_TYPE_CMD_TABLE,
  MX_DBG_CMD_OPT_INST_CUR |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMTB_VPSS_DC_CONFIG_PARAMS,sCustomModeInfo),
  0,
  0,
  0,
  0,
  0,
  &cmdTblIndexParamVFDCCustomModeInfoConfig,
  XdbgCmdTblFunc,
  "OMX_TI_IndexParamVFDCCustomModeInfo Index Parameters:",
  "",
  "",
  ""
};

/* VPSS DC config command table Entry */

MX_DBG_CMD_ENTRY_T* cmdListVPSSDcConfig[] =
{
  &cmdEntryVPSSDcCompName,
  &cmdEntryVPSSDcIndexParamVFDCDriverInstIdConfig,
  &cmdEntryVPSSDcIndexParamVFDCCustomModeInfoConfig,
  NULL
};


/* VPSS DC config command table */

MX_DBG_CMD_TABLE_T cmdTblVPSSDcConfig =
{
  MX_DBG_ACCESS_ALL,
  sizeof(cmdListVPSSDcConfig)/sizeof(cmdListVPSSDcConfig[0]),
  cmdListVPSSDcConfig
};


/* VPSS DC config command entry */

MX_DBG_CMD_ENTRY_T cmdEntryVPSSDcConfig =
{
  OMTB_VPSS_DC_COMP_REF_STR,
  MX_DBG_CMD_TYPE_CMD_TABLE,
  MX_DBG_CMD_OPT_INST_CUR |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMTB_TEMPLATE_INFO,vpssDcTemplate),
  0,
  0,
  0,
  0,
  0,
  &cmdTblVPSSDcConfig,
  XdbgCmdTblFunc,
  "\nVPSS DC Config Parameters:\n",
  "",
  "",
  ""
};


/*----------------------------- end of file ---------------------------------*/
