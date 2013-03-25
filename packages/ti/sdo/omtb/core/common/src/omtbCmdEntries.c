/*
 * omtbCmdEntries.c
 *
 * This file contains command entries for omx command table and utility
 * commands.
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
#include "OMX_Component.h"
#include "OMX_Types.h"


/******************************************************************************\
 *      Customized Includes
\******************************************************************************/

#include "mxDbg.h"
#include "omtbCommon.h"
#include "omtbCmd.h"
#include "omtbTemplateManager.h"
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

extern MX_DBG_CMD_TABLE_T funcCmdTbl;             // Command table for FUNC mode
extern MX_DBG_CMD_TABLE_T cmdTblOmxApi;           // Command table for API mode
extern MX_DBG_CMD_TABLE_T cmdTblOmxTiApi;           // Command table for API mode
extern MX_DBG_CMD_TABLE_T cmdTblOmxApiTest;       // Command table for API Test


/******************************************************************************\
 *      Globals
\******************************************************************************/

MX_DBG_CMD_TABLE_T setpCmdTbl;                    /* command table for setp */


/******************************************************************************\
 *      Public Function Prototype
\******************************************************************************/


/******************************************************************************\
 *      Static Globals
\******************************************************************************/

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryOmtbSetp;/* Command entry for setp */
PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryOmtbFunc;/* command entry for func command*/
MX_DBG_CMD_TABLE_T cmdTblOmx;       /* command table for omx command */
MX_DBG_CMD_ENTRY_T cmdEntryOmx;     /* command entry for omx command */


/******************************************************************************\
 *      Private Function Declarations
\******************************************************************************/


/*******************************************************************************
 *  Second Level Command Entries/Tables - omx
 ******************************************************************************/

/* setp command list entry */

MX_DBG_CMD_ENTRY_T* setpCmdList[OMTB_MAX_CLASS] =
{
  NULL
};


/* setp command table */

MX_DBG_CMD_TABLE_T setpCmdTbl=
{
  MX_DBG_ACCESS_ALL,
  sizeof(setpCmdList) / sizeof(setpCmdList[0]),
  setpCmdList
};


/*******************************************************************************
 *  OMTB OMX API/Func Mode Commands
 ******************************************************************************/

/* Dummy entry to isolate OMTB OMX commands */

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryOmtbOmxCmd =
{
  "",
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
  NULL,
  "",
  "OMTB Commands:",
  "",
  ""
};


/* func command entry */

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryOmtbFunc =
{
  "func",
  MX_DBG_CMD_TYPE_CMD_TABLE,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_VALID_PTR,
  0,
  0,
  0,
  0,
  0,
  0,
  &funcCmdTbl,
  OMTB_ParseCmdTblEntries,
  "",
  "",
  "",
  ""
};


/* comp command entry */

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryOmtbApi =
{
  "api",
  MX_DBG_CMD_TYPE_CMD_TABLE,
  MX_DBG_CMD_OPT_INST_CUR |
  MX_DBG_CMD_OPT_VALID_PTR,
  0,
  0,
  0,
  0,
  0,
  0,
  &cmdTblOmxApi,
  OMTB_ParseCmdTblEntries,
  "",
  "",
  "",
  ""
};

/* comp command entry */
#ifdef OMTB_TI_API
PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryOmtbTiApi =
{
  "tiapi",
  MX_DBG_CMD_TYPE_CMD_TABLE,
  MX_DBG_CMD_OPT_INST_CUR |
  MX_DBG_CMD_OPT_VALID_PTR,
  0,
  0,
  0,
  0,
  0,
  0,
  &cmdTblOmxTiApi,
  OMTB_ParseCmdTblEntries,
  "",
  "",
  "",
  ""
};
#endif

/* comp command entry */
PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryOmtbApiTest =
{
  "api_test",
  MX_DBG_CMD_TYPE_CMD_TABLE,
  MX_DBG_CMD_OPT_INST_CUR |
  MX_DBG_CMD_OPT_VALID_PTR,
  0,
  0,
  0,
  0,
  0,
  0,
  &cmdTblOmxApiTest,
  OMTB_ParseCmdTblEntries,
  "",
  "",
  "",
  ""
};


/*******************************************************************************
 *  Utility Commands
 ******************************************************************************/

/* Dummy entry to isolate utility commands */

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryOmtbUtilityCmd =
{
  "",
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
  NULL,
  "",
  "Utility Commands:",
  "",
  ""
};


/* Run OMTB using DVS script */

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryOmtbRunScript =
{
  "-s",
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
  OMTB_CmdRunScript,
  "",
  "<script_file_name>",
  "",
  ""
};


/* setp command entry */

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryOmtbSetp =
{
  "setp",
  MX_DBG_CMD_TYPE_CMD_TABLE,
  MX_DBG_CMD_OPT_INST_CUR,
  0,
  0,
  0,
  0,
  0,
  0,
  &setpCmdTbl,
  OMTB_CmdSetTemplate,
  "",
  "<template #>",
  "",
  ""
};


/* getp command entry */

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryOmtbGetp =
{
  "getp",
  MX_DBG_CMD_TYPE_CMD_TABLE,
  MX_DBG_CMD_OPT_INST_CUR,
  0,
  0,
  0,
  0,
  0,
  0,
  &setpCmdTbl,
  OMTB_CmdShowTemplate,
  "",
  "<template #>",
  "",
  ""
};


/* Get OMTB version information*/

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryOmtbReleaseInfo =
{
  "omtb_rel_info",
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
  OMTB_CmdReleaseInfo,
  "",
  "",
  "",
  ""
};


/* Remove OMTB configuration template from memory */

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryOmtbAddCfg =
{
  "add",
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
  OMTB_CmdAddCfg,
  "",
  "<template #>",
  "",
  ""
};


/* Remove OMTB configuration template from memory */

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryOmtbRemoveCfg =
{
  "remove",
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
  OMTB_CmdRemoveCfg,
  "",
  "<template #>",
  "",
  ""
};


/* Load OMTB configuration */

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryOmtbLoadCfg =
{
  "load",
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
  OMTB_CmdLoadCfg,
  "",
  "<template #> <cfg_file_name>",
  "",
  ""
};


/* Store OMTB configuration */

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryOmtbStoreCfg =
{
  "store",
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
  OMTB_CmdStoreCfg,
  "",
  "<template #> <cfg_file_name>",
  "",
  ""
};


/* reset */
PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryOmtbResetProfile =
{
  "reset",
  MX_DBG_CMD_TYPE_CMD_TABLE,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_VALID_PTR,
  0,
  0,
  0,
  0,
  0,
  0,
  &setpCmdTbl,
  OMTB_CmdResetTemplate,
  "",
  "<template #>",
  "",
  ""
};


/* cpu load command entry */

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryToggleArmLoadDisp =
{
  "tog_arm_load",
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
  OMTB_CmdShowArmLoad,
  "",
  "",
  "",
  ""
};


/* OMX Component Debug log enable/disable */

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryToggleCompDbgLog =
{
  "comp_dbg_log",
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
  OMTB_CmdToggleCompDbgLog,
  "",
  "",
  "",
  ""
};


/* OMTB Debug level setting */

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntrySetOmtbDbgLevel =
{
  "omtb_dbg_lvl",
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
  OMTB_CmdSetDbgLogLevel,
  "",
  "<debug level>\n\
where <debug level> can be, 0x00 - Disable Logs;\n\
                            0x02 - Simple Logs;\n\
                            0x04 - Default Logs;\n\
                            0x08 - Function Names;\n\
                            0x10 - Debug Logs;\n\
                            0x20 - Set Param Logs;\n\
                            0x40 - Get Param Logs;\n\
                            0x80 - Compulsary Logs/Error Logs",
  "",
  ""
};


/* OMTB Start loop setting */

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryStartLoop =
{
  "loop_start",
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
  OMTB_CmdStartLoop,
  "",
  "<count>",
  "",
  ""
};


/* OMTB End loop setting */

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryEndLoop =
{
  "loop_end",
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
  OMTB_CmdEndLoop,
  "",
  "",
  "",
  ""
};


/* OMTB End loop setting */

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryNotify =
{
  "notify",
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
  OMTB_CmdNotify,
  "",
  "<h264venc | h264vdec | vdec> <instance #> <eos>",
  "",
  ""
};

/*******************************************************************************
 *  First Level Command Entry/Table - omx
 ******************************************************************************/

/* omx command list */
PRIVATE MX_DBG_CMD_ENTRY_T* cmdListOmx[] =
{
  &cmdEntryOmtbOmxCmd,
  &cmdEntryOmtbFunc,
  &cmdEntryOmtbApi,
#ifdef OMTB_TI_API  
  &cmdEntryOmtbTiApi,
#endif  
  &cmdEntryOmtbApiTest,
  &cmdEntryOmtbUtilityCmd,
  &cmdEntryOmtbRunScript,
  &cmdEntryOmtbSetp,
  &cmdEntryOmtbGetp,
  &cmdEntryOmtbReleaseInfo,
  &cmdEntryOmtbAddCfg,
  &cmdEntryOmtbRemoveCfg,
  &cmdEntryOmtbLoadCfg,
  &cmdEntryOmtbStoreCfg,
  &cmdEntryOmtbResetProfile,
  &cmdEntryToggleArmLoadDisp,
  &cmdEntryToggleCompDbgLog,
  &cmdEntrySetOmtbDbgLevel,
  &cmdEntryStartLoop,
  &cmdEntryEndLoop,
  &cmdEntryNotify,
  NULL
};


/* omx command table */
MX_DBG_CMD_TABLE_T cmdTblOmx =
{
  MX_DBG_ACCESS_ALL,
  sizeof(cmdListOmx) / sizeof(cmdListOmx[0]),
  cmdListOmx
};


/* omx command entry */
MX_DBG_CMD_ENTRY_T cmdEntryOmx =
{
  "omx",
  MX_DBG_CMD_TYPE_CMD_TABLE,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_VALID_PTR,
  0,
  0,
  0,
  0,
  0,
  0,
  &cmdTblOmx,
  NULL,
  "",
  "",
  "",
  ""
};


/*----------------------------- end of file ---------------------------------*/
