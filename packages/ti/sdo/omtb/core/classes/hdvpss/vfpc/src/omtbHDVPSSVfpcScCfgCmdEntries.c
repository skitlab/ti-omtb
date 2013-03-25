/*
 * omtbHDVPSSVfpcScCfgCmdEntries.c
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
#include "omx_vfpc.h"


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
extern MX_DBG_CMD_TABLE_T cmdTblIndexParamCompBufferSupplierConfig;
extern MX_DBG_CMD_TABLE_T cmdTblIndexParamBuffMemTypeConfig;
extern MX_DBG_CMD_TABLE_T cmdTblIndexParamVideoInitConfig;
extern MX_DBG_CMD_TABLE_T cmdTblIndexConfigVidChResolutionConfig;
extern MX_DBG_CMD_TABLE_T cmdTblIndexConfigAlgEnableConfig;
extern MX_DBG_CMD_TABLE_T cmdTblIndexParamCompPortNotifyTypeConfig;
extern MX_DBG_CMD_TABLE_T cmdTblIndexParamVFPCNumChPerHandleConfig;
extern MX_DBG_CMD_TABLE_T cmdTblIndexParamPortDefinitionConfig;
extern MX_DBG_CMD_TABLE_T cmdTblIndexConfigChannelNameConfig;

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
 *  OMTB component configuration parameter command entries - VFPC SC
 ******************************************************************************/

/*******************************************************************************
 *      VFPC SC config params
 ******************************************************************************/

/* Entry for Set OMX Component Name */

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryVPSSVfpcScCompName =
{
  "compname",
  MX_DBG_CMD_TYPE_VAR_STR_BUF,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMTB_VPSS_VFPC_SC_CONFIG_PARAMS,sBasicParams.compName),
  FIELDOFFSET(OMTB_VPSS_VFPC_SC_CONFIG_PARAMS,sBasicParams.inputFile) -
  FIELDOFFSET(OMTB_VPSS_VFPC_SC_CONFIG_PARAMS,sBasicParams.compName),
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


/* Entry for Set Input File Name */

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryVPSSVfpcScInFile =
{
  "infile",
  MX_DBG_CMD_TYPE_VAR_STR_BUF,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMTB_VPSS_VFPC_SC_CONFIG_PARAMS,sBasicParams.inputFile),
  FIELDOFFSET(OMTB_VPSS_VFPC_SC_CONFIG_PARAMS,sBasicParams.inputFile) -
  FIELDOFFSET(OMTB_VPSS_VFPC_SC_CONFIG_PARAMS,sBasicParams.inputFile),
  0,
  0,
  OMTB_MAX_LEN,
  (int)NULL,
  NULL,
  XdbgCmdVarFunc,
  "Input File name...............................",
  "<file_name>",
  "",
  ""
};


/* Entry for Set Output File Name */

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryVPSSVfpcScOutFile =
{
  "outfile",
  MX_DBG_CMD_TYPE_VAR_STR_BUF,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMTB_VPSS_VFPC_SC_CONFIG_PARAMS,sBasicParams.outputFile),
  FIELDOFFSET(OMTB_VPSS_VFPC_SC_CONFIG_PARAMS,sBasicParams.inputFile) -
  FIELDOFFSET(OMTB_VPSS_VFPC_SC_CONFIG_PARAMS,sBasicParams.outputFile),
  0,
  0,
  OMTB_MAX_LEN,
  (int)NULL,
  NULL,
  XdbgCmdVarFunc,
  "Output File name..............................",
  "<file_name>",
  "",
  ""
};


/*Entry for Set Input Frame Width*/

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryVPSSVfpcScWidth =
{
  "frame_width",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_DEC      |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMTB_VPSS_VFPC_SC_CONFIG_PARAMS,sBasicParams.frameWidth),
  FIELDOFFSET(OMTB_VPSS_VFPC_SC_CONFIG_PARAMS,sBasicParams.inputFile) -
  FIELDOFFSET(OMTB_VPSS_VFPC_SC_CONFIG_PARAMS,sBasicParams.frameWidth),
  0,
  0,
  OMTB_MAX_VID_WIDTH,
  OMTB_MAX_VID_WIDTH,
  NULL,
  XdbgCmdVarFunc,
  "Input Frame Width.............................",
  "<width>",
  "",
  ""
};


/*Entry for Set Input Frame Height*/

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryVPSSVfpcScHeight =
{
  "frame_height",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_DEC          |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMTB_VPSS_VFPC_SC_CONFIG_PARAMS,sBasicParams.frameHeight),
  FIELDOFFSET(OMTB_VPSS_VFPC_SC_CONFIG_PARAMS,sBasicParams.inputFile) -
  FIELDOFFSET(OMTB_VPSS_VFPC_SC_CONFIG_PARAMS,sBasicParams.frameHeight),
  0,
  0,
  OMTB_MAX_VID_HEIGHT,
  OMTB_MAX_VID_HEIGHT,
  NULL,
  XdbgCmdVarFunc,
  "Input Frame Height............................",
  "<Height>",
  "",
  ""
};


/* Enum Entry for Supported O/P Color Format */

PRIVATE MX_DBG_ENUM_ENTRY_T enumTblVPSSVfpcScOutputChromaFormat[] =
{
  {"420P",OMX_COLOR_FormatYUV420Planar, ""},
  {"420SP",OMX_COLOR_FormatYUV420SemiPlanar, ""},
  {"422P",OMX_COLOR_FormatYUV422Planar, ""},
  {"422YUYV", OMX_COLOR_FormatYCbYCr, ""},
  {"", 0, ""}
};


/* Entry for Set O/P Color Format */

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryVPSSVfpcScOutputChromaFormat =
{
  "op_chromat_format",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_ENUM          |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMTB_VPSS_VFPC_SC_CONFIG_PARAMS,sBasicParams.colorFormat),
  FIELDOFFSET(OMTB_VPSS_VFPC_SC_CONFIG_PARAMS,sBasicParams.inputFile) -
  FIELDOFFSET(OMTB_VPSS_VFPC_SC_CONFIG_PARAMS,sBasicParams.colorFormat),
  0,
  OMX_COLOR_FormatYUV420Planar,
  OMX_COLOR_FormatYCbYCr,
  OMX_COLOR_FormatYUV422Planar,
  &enumTblVPSSVfpcScOutputChromaFormat,
  XdbgCmdVarFunc,
  "O/P Chroma Format.............................",
  "",
  "",
  ""
};


/* Enum Entry for Supported I/P Color Format */

PRIVATE MX_DBG_ENUM_ENTRY_T enumTblVPSSVfpcScInputChromaFormat[] =
{
  {"420P",OMX_COLOR_FormatYUV420Planar, ""},
  {"420SP",OMX_COLOR_FormatYUV420SemiPlanar, ""},
  {"422P",OMX_COLOR_FormatYUV422Planar, ""},
  {"422YUYV", OMX_COLOR_FormatYCbYCr, ""},
  {"", 0, ""}
};


/* Entry for Set O/P Color Format */

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryVPSSVfpcScInputChromaFormat =
{
  "ip_chromat_format",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_ENUM          |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMTB_VPSS_VFPC_SC_CONFIG_PARAMS,sBasicParams.inColorFormat),
  FIELDOFFSET(OMTB_VPSS_VFPC_SC_CONFIG_PARAMS,sBasicParams.inputFile) -
  FIELDOFFSET(OMTB_VPSS_VFPC_SC_CONFIG_PARAMS,sBasicParams.inColorFormat),
  0,
  OMX_COLOR_FormatYUV420Planar,
  OMX_COLOR_FormatYCbYCr,
  OMX_COLOR_FormatYUV422Planar,
  &enumTblVPSSVfpcScInputChromaFormat,
  XdbgCmdVarFunc,
  "I/P Chroma Format.............................",
  "",
  "",
  ""
};

/* Enum Entry for Selecting Data Mode */

PRIVATE MX_DBG_ENUM_ENTRY_T enumTblDatatMode[] =
{
  {"file",  OMTB_FILE,    ""},
  {"driver",OMTB_DRIVER,  ""},
  {"none",  OMTB_NONE,    ""},
  {"",      0,            ""}
};


/* Entry for Setting Data Output Mode */

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryVPSSVfpcScOutputMode =
{
  "data_opmode",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_ENUM          |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMTB_VPSS_VFPC_SC_CONFIG_PARAMS,sBasicParams.dataOutPutMode),
  FIELDOFFSET(OMTB_VPSS_VFPC_SC_CONFIG_PARAMS,sBasicParams.inputFile) -
  FIELDOFFSET(OMTB_VPSS_VFPC_SC_CONFIG_PARAMS,sBasicParams.dataOutPutMode),
  0,
  OMTB_FILE,
  OMTB_NONE,
  OMTB_FILE,
  &enumTblDatatMode,
  XdbgCmdVarFunc,
  "Data O/P Mode.................................",
  "",
  "",
  ""
};


/* Entry for Setting Data Output Mode */

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryVPSSVfpcScInputMode =
{
  "data_ipmode",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_ENUM         |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMTB_VPSS_VFPC_SC_CONFIG_PARAMS,sBasicParams.dataInPutMode),
  FIELDOFFSET(OMTB_VPSS_VFPC_SC_CONFIG_PARAMS,sBasicParams.inputFile) -
  FIELDOFFSET(OMTB_VPSS_VFPC_SC_CONFIG_PARAMS,sBasicParams.dataInPutMode),
  0,
  OMTB_FILE,
  OMTB_NONE,
  OMTB_FILE,
  &enumTblDatatMode,
  XdbgCmdVarFunc,
  "Data I/P Mode.................................",
  "",
  "",
  ""
};

/* Enum Entry for Selecting OMX_AllocateBuffer or OMX_UseBuffer Mode */

PRIVATE MX_DBG_ENUM_ENTRY_T enumTblBufAllocationMode[] =
{
  {"use",      OMX_TRUE,  ""},
  {"allocate", OMX_FALSE, ""},
  {"",         0,         ""}
};


/* Entry for Setting Use/Allocate input buffer */

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryVPSSVfpcScFlagUseAllocInBuffer =
{
  "inbuf",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_ENUM          |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMTB_VPSS_VFPC_SC_CONFIG_PARAMS,sBasicParams.flagUseInBuffer),
  FIELDOFFSET(OMTB_VPSS_VFPC_SC_CONFIG_PARAMS,sBasicParams.inputFile) -
  FIELDOFFSET(OMTB_VPSS_VFPC_SC_CONFIG_PARAMS,sBasicParams.flagUseInBuffer),
  0,
  OMX_FALSE,
  OMX_TRUE,
  OMX_TRUE,
  &enumTblBufAllocationMode,
  XdbgCmdVarFunc,
  "I/P Buffer allocation Mode....................",
  "",
  "",
  ""
};

/*Entry for Set number of i/p buffers */

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryVPSSVfpcScNumInBuf =
{
  "numinbuf",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_DEC      |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMTB_VPSS_VFPC_SC_CONFIG_PARAMS,sBasicParams.numInBuf),
  FIELDOFFSET(OMTB_VPSS_VFPC_SC_CONFIG_PARAMS,sBasicParams.inputFile) -
  FIELDOFFSET(OMTB_VPSS_VFPC_SC_CONFIG_PARAMS,sBasicParams.numInBuf),
  0,
  0,
  OMTB_VPSS_VFPC_SC_MAX_NUM_IN_BUFS,
  OMTB_VPSS_VFPC_SC_MAX_NUM_IN_BUFS,
  NULL,
  XdbgCmdVarFunc,
  "Number of i/p buffer..........................",
  "<# of input buffers>",
  "",
  ""
};

/* Entry for Set i/p buffer size */

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryVPSSVfpcScInBufSize =
{
  "inbufsize",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_DEC          |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMTB_VPSS_VFPC_SC_CONFIG_PARAMS,sBasicParams.inBufSize),
  FIELDOFFSET(OMTB_VPSS_VFPC_SC_CONFIG_PARAMS,sBasicParams.inputFile) -
  FIELDOFFSET(OMTB_VPSS_VFPC_SC_CONFIG_PARAMS,sBasicParams.inBufSize),
  0,
  0,
  OMTB_MAX_VAL_U32,
  OMTB_VPSS_VFPC_SC_MAX_INBUFF_SIZE,
  NULL,
  XdbgCmdVarFunc,
  "I/p buffer size...............................",
  "<input buffer size>",
  "",
  ""
};

/* Entry for Set i/p buffer alignment */

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryVPSSVfpcScInBufAlignment =
{
  "inbufalign",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_DEC          |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMTB_VPSS_VFPC_SC_CONFIG_PARAMS,sBasicParams.inBufAlignment),
  FIELDOFFSET(OMTB_VPSS_VFPC_SC_CONFIG_PARAMS,sBasicParams.inputFile) -
  FIELDOFFSET(OMTB_VPSS_VFPC_SC_CONFIG_PARAMS,sBasicParams.inBufAlignment),
  0,
  0,
  OMTB_MAX_VAL_U32,
  0,
  NULL,
  XdbgCmdVarFunc,
  "I/p buffer alignment..........................",
  "<input buffer alignment>",
  "",
  ""
};

/* Entry for Setting Use/Allocate output buffer */

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryVPSSVfpcScFlagUseAllocOutBuffer =
{
  "outbuf",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_ENUM          |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMTB_VPSS_VFPC_SC_CONFIG_PARAMS,sBasicParams.flagUseOutBuffer),
  FIELDOFFSET(OMTB_VPSS_VFPC_SC_CONFIG_PARAMS,sBasicParams.inputFile) -
  FIELDOFFSET(OMTB_VPSS_VFPC_SC_CONFIG_PARAMS,sBasicParams.flagUseOutBuffer),
  0,
  OMX_FALSE,
  OMX_TRUE,
  OMX_TRUE,
  &enumTblBufAllocationMode,
  XdbgCmdVarFunc,
  "O/P Buffer allocation Mode....................",
  "",
  "",
  ""
};

/*Entry for Set number of o/p buffers */

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryVPSSVfpcScNumOutBuf =
{
  "numoutbuf",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_DEC      |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMTB_VPSS_VFPC_SC_CONFIG_PARAMS,sBasicParams.numOutBuf),
  FIELDOFFSET(OMTB_VPSS_VFPC_SC_CONFIG_PARAMS,sBasicParams.inputFile) -
  FIELDOFFSET(OMTB_VPSS_VFPC_SC_CONFIG_PARAMS,sBasicParams.numOutBuf),
  0,
  0,
  OMTB_VPSS_VFPC_SC_MAX_NUM_OUT_BUFS,
  OMTB_VPSS_VFPC_SC_MAX_NUM_OUT_BUFS,
  NULL,
  XdbgCmdVarFunc,
  "Number of o/p buffer..........................",
  "<# of output buffers>",
  "",
  ""
};

/* Entry for Set o/p buffer size */

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryVPSSVfpcScOutBufSize =
{
  "outbufsize",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_DEC          |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMTB_VPSS_VFPC_SC_CONFIG_PARAMS,sBasicParams.outBufSize),
  FIELDOFFSET(OMTB_VPSS_VFPC_SC_CONFIG_PARAMS,sBasicParams.inputFile) -
  FIELDOFFSET(OMTB_VPSS_VFPC_SC_CONFIG_PARAMS,sBasicParams.outBufSize),
  0,
  0,
  OMTB_MAX_VAL_U32,
  OMTB_VPSS_VFPC_SC_MAX_OUTBUFF_SIZE,
  NULL,
  XdbgCmdVarFunc,
  "O/p buffer size...............................",
  "<output buffer size>",
  "",
  ""
};

/* Entry for Set o/p buffer alignment */

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryVPSSVfpcScOutBufAlignment =
{
  "outbufalign",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_DEC          |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMTB_VPSS_VFPC_SC_CONFIG_PARAMS,sBasicParams.outBufAlignment),
  FIELDOFFSET(OMTB_VPSS_VFPC_SC_CONFIG_PARAMS,sBasicParams.inputFile) -
  FIELDOFFSET(OMTB_VPSS_VFPC_SC_CONFIG_PARAMS,sBasicParams.outBufAlignment),
  0,
  0,
  OMTB_MAX_VAL_U32,
  0,
  NULL,
  XdbgCmdVarFunc,
  "O/p buffer alignment..........................",
  "<output buffer alignment>",
  "",
  ""
};


/* Enum Entry for enabling or disabling flag */

PRIVATE MX_DBG_ENUM_ENTRY_T enumTblVPSSVfpcScOnOff[] =
{
  {"enable",  OMX_TRUE,   ""},
  {"disable", OMX_FALSE,  ""},
  {"",        0,          ""}
};


/* Entry for Set i/p buffer size */

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryVPSSVfpcScInBufSzFlag =
{
  "inbufsize_flag",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_ENUM         |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMTB_VPSS_VFPC_SC_CONFIG_PARAMS,sBasicParams.inBufSzFlag),
  FIELDOFFSET(OMTB_VPSS_VFPC_SC_CONFIG_PARAMS,sBasicParams.inputFile) -
  FIELDOFFSET(OMTB_VPSS_VFPC_SC_CONFIG_PARAMS,sBasicParams.inBufSzFlag),
  0,
  OMX_FALSE,
  OMX_TRUE,
  OMX_FALSE,
  &enumTblVPSSVfpcScOnOff,
  XdbgCmdVarFunc,
  "I/P buffer size input from user...............",
  "",
  "",
  ""
};

/* Entry for Set i/p buffer continuous memory allocation */

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryVPSSVfpcScInBufContiguous =
{
  "inbuf_contig",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_ENUM         |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMTB_VPSS_VFPC_SC_CONFIG_PARAMS,sBasicParams.inBufContiguous),
  FIELDOFFSET(OMTB_VPSS_VFPC_SC_CONFIG_PARAMS,sBasicParams.inputFile) -
  FIELDOFFSET(OMTB_VPSS_VFPC_SC_CONFIG_PARAMS,sBasicParams.inBufContiguous),
  0,
  OMX_FALSE,
  OMX_TRUE,
  OMX_FALSE,
  &enumTblVPSSVfpcScOnOff,
  XdbgCmdVarFunc,
  "Contiguous i/p buffer memory..................",
  "",
  "",
  ""
};


/* Entry for Set o/p buffer size */

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryVPSSVfpcScOutBufSzFlag =
{
  "outbufsize_flag",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_ENUM         |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMTB_VPSS_VFPC_SC_CONFIG_PARAMS,sBasicParams.outBufSzFlag),
  FIELDOFFSET(OMTB_VPSS_VFPC_SC_CONFIG_PARAMS,sBasicParams.inputFile) -
  FIELDOFFSET(OMTB_VPSS_VFPC_SC_CONFIG_PARAMS,sBasicParams.outBufSzFlag),
  0,
  OMX_FALSE,
  OMX_TRUE,
  OMX_FALSE,
  &enumTblVPSSVfpcScOnOff,
  XdbgCmdVarFunc,
  "O/P buffer size input from user...............",
  "",
  "",
  ""
};


/* Entry for Set o/p buffer continuous memory allocation */

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryVPSSVfpcScOutBufContiguous =
{
  "outbuf_contig",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_ENUM         |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMTB_VPSS_VFPC_SC_CONFIG_PARAMS,sBasicParams.outBufContiguous),
  FIELDOFFSET(OMTB_VPSS_VFPC_SC_CONFIG_PARAMS,sBasicParams.inputFile) -
  FIELDOFFSET(OMTB_VPSS_VFPC_SC_CONFIG_PARAMS,sBasicParams.outBufContiguous),
  0,
  OMX_FALSE,
  OMX_TRUE,
  OMX_FALSE,
  &enumTblVPSSVfpcScOnOff,
  XdbgCmdVarFunc,
  "Contiguous o/p buffer memory..................",
  "",
  "",
  ""
};

/* Entry for Set File reset flag */

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryVPSSVfpcScFileResetFlag =
{
  "filereset_flag",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_ENUM         |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMTB_VPSS_VFPC_SC_CONFIG_PARAMS,sBasicParams.fileReset),
  FIELDOFFSET(OMTB_VPSS_VFPC_SC_CONFIG_PARAMS,sBasicParams.inputFile) -
  FIELDOFFSET(OMTB_VPSS_VFPC_SC_CONFIG_PARAMS,sBasicParams.fileReset),
  0,
  OMX_FALSE,
  OMX_TRUE,
  OMX_FALSE,
  &enumTblVPSSVfpcScOnOff,
  XdbgCmdVarFunc,
  "File Reset Flag...............................",
  "",
  "",
  ""
};


/* Entry to set params of OMX_IndexParamCompBufferSupplier index*/
PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryVPSSVfpcScIndexParamCompBufferSupplierConfig =
{
  "OMX_IndexParamCompBufferSupplier",
  MX_DBG_CMD_TYPE_CMD_TABLE,
  MX_DBG_CMD_OPT_INST_CUR |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMTB_VPSS_VFPC_SC_CONFIG_PARAMS,sBufSupplier),
  0,
  0,
  0,
  0,
  0,
  &cmdTblIndexParamCompBufferSupplierConfig,
  XdbgCmdTblFunc,
  "OMX_IndexParamCompBufferSupplier Index Parameters:",
  "",
  "",
  ""
};

/* Entry to set params of OMX_TI_IndexParamBuffMemType index*/
PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryVPSSVfpcScIndexParamBuffMemTypeConfig =
{
  "OMX_TI_IndexParamBuffMemType",
  MX_DBG_CMD_TYPE_CMD_TABLE,
  MX_DBG_CMD_OPT_INST_CUR |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMTB_VPSS_VFPC_SC_CONFIG_PARAMS,sMemTypeCfg),
  0,
  0,
  0,
  0,
  0,
  &cmdTblIndexParamBuffMemTypeConfig,
  XdbgCmdTblFunc,
  "OMX_TI_IndexParamBuffMemType Index Parameters:",
  "",
  "",
  ""
};

/* Entry to set params of OMX_IndexParamVideoInit index*/
PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryVPSSVfpcScIndexParamVideoInitConfig =
{
  "OMX_IndexParamVideoInit",
  MX_DBG_CMD_TYPE_CMD_TABLE,
  MX_DBG_CMD_OPT_INST_CUR |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMTB_VPSS_VFPC_SC_CONFIG_PARAMS,sPortInit),
  0,
  0,
  0,
  0,
  0,
  &cmdTblIndexParamVideoInitConfig,
  XdbgCmdTblFunc,
  "OMX_IndexParamVideoInit Index Parameters:",
  "",
  "",
  ""
};

/* Entry to set params of OMX_TI_IndexConfigVidChResolution index*/
PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryVPSSVfpcScIndexConfigVidChResolutionConfig =
{
  "OMX_TI_IndexConfigVidChResolution",
  MX_DBG_CMD_TYPE_CMD_TABLE,
  MX_DBG_CMD_OPT_INST_CUR |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMTB_VPSS_VFPC_SC_CONFIG_PARAMS,sVidChResolutionCfg),
  0,
  0,
  0,
  0,
  0,
  &cmdTblIndexConfigVidChResolutionConfig,
  XdbgCmdTblFunc,
  "OMX_TI_IndexConfigVidChResolution Index Parameters:",
  "",
  "",
  ""
};


/* Entry to set params of OMX_TI_IndexConfigAlgEnable index*/
PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryVPSSVfpcScIndexConfigAlgEnableConfig =
{
  "OMX_TI_IndexConfigAlgEnable",
  MX_DBG_CMD_TYPE_CMD_TABLE,
  MX_DBG_CMD_OPT_INST_CUR |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMTB_VPSS_VFPC_SC_CONFIG_PARAMS,sAlgEnable),
  0,
  0,
  0,
  0,
  0,
  &cmdTblIndexConfigAlgEnableConfig,
  XdbgCmdTblFunc,
  "OMX_TI_IndexConfigAlgEnable Index Parameters:",
  "",
  "",
  ""
};

/* Entry to set params of OMX_TI_IndexParamCompPortNotifyType index*/
PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryVPSSVfpcScIndexParamCompPortNotifyTypeConfig =
{
  "OMX_TI_IndexParamCompPortNotifyType",
  MX_DBG_CMD_TYPE_CMD_TABLE,
  MX_DBG_CMD_OPT_INST_CUR |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMTB_VPSS_VFPC_SC_CONFIG_PARAMS,sCompPortNotifyType),
  0,
  0,
  0,
  0,
  0,
  &cmdTblIndexParamCompPortNotifyTypeConfig,
  XdbgCmdTblFunc,
  "OMX_TI_IndexParamCompPortNotifyType Index Parameters:",
  "",
  "",
  ""
};


/* Entry to set params of OMX_TI_IndexParamVFPCNumChPerHandle index*/
PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryVPSSVfpcScIndexParamVFPCNumChPerHandleConfig =
{
  "OMX_TI_IndexParamVFPCNumChPerHandle",
  MX_DBG_CMD_TYPE_CMD_TABLE,
  MX_DBG_CMD_OPT_INST_CUR |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMTB_VPSS_VFPC_SC_CONFIG_PARAMS,sNumChPerHandle),
  0,
  0,
  0,
  0,
  0,
  &cmdTblIndexParamVFPCNumChPerHandleConfig,
  XdbgCmdTblFunc,
  "OMX_TI_IndexParamVFPCNumChPerHandle Index Parameters:",
  "",
  "",
  ""
};

/* Entry to set params of OMX_IndexParamPortDefinition index*/
PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryVPSSVfpcScIndexParamPortDefinitionConfig =
{
  "OMX_IndexParamPortDefinition",
  MX_DBG_CMD_TYPE_CMD_TABLE,
  MX_DBG_CMD_OPT_INST_CUR |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMTB_VPSS_VFPC_SC_CONFIG_PARAMS,sPortDefType),
  0,
  0,
  0,
  0,
  0,
  &cmdTblIndexParamPortDefinitionConfig,
  XdbgCmdTblFunc,
  "OMX_IndexParamPortDefinition Index Parameters:",
  "",
  "",
  ""
};

/* Entry to set params of OMX_TI_IndexConfigChannelName index*/
PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryVPSSVfpcScIndexConfigChannelNameConfig =
{
  "OMX_TI_IndexConfigChannelName",
  MX_DBG_CMD_TYPE_CMD_TABLE,
  MX_DBG_CMD_OPT_INST_CUR |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMTB_VPSS_VFPC_SC_CONFIG_PARAMS,sChannelName),
  0,
  0,
  0,
  0,
  0,
  &cmdTblIndexConfigChannelNameConfig,
  XdbgCmdTblFunc,
  "OMX_TI_IndexConfigChannelName Index Parameters:",
  "",
  "",
  ""
};

/* VFPC config command table Entry */

MX_DBG_CMD_ENTRY_T* cmdListVPSSVfpcScConfig[] =
{
  &cmdEntryVPSSVfpcScCompName,
  &cmdEntryVPSSVfpcScInFile,
  &cmdEntryVPSSVfpcScOutFile,
  &cmdEntryVPSSVfpcScWidth,
  &cmdEntryVPSSVfpcScHeight,
  &cmdEntryVPSSVfpcScOutputChromaFormat,
  &cmdEntryVPSSVfpcScInputChromaFormat,
  &cmdEntryVPSSVfpcScOutputMode,
  &cmdEntryVPSSVfpcScInputMode,
  &cmdEntryVPSSVfpcScFlagUseAllocInBuffer,
  &cmdEntryVPSSVfpcScNumInBuf,
  &cmdEntryVPSSVfpcScInBufAlignment,
  &cmdEntryVPSSVfpcScInBufContiguous,
  &cmdEntryVPSSVfpcScInBufSzFlag,
  &cmdEntryVPSSVfpcScInBufSize,
  &cmdEntryVPSSVfpcScFlagUseAllocOutBuffer,
  &cmdEntryVPSSVfpcScNumOutBuf,
  &cmdEntryVPSSVfpcScOutBufAlignment,
  &cmdEntryVPSSVfpcScOutBufContiguous,
  &cmdEntryVPSSVfpcScOutBufSzFlag,
  &cmdEntryVPSSVfpcScOutBufSize,
  &cmdEntryVPSSVfpcScFileResetFlag,
  
  &cmdEntryVPSSVfpcScIndexParamCompBufferSupplierConfig,
  &cmdEntryVPSSVfpcScIndexParamBuffMemTypeConfig,
  &cmdEntryVPSSVfpcScIndexParamVideoInitConfig,
  &cmdEntryVPSSVfpcScIndexConfigVidChResolutionConfig,
  &cmdEntryVPSSVfpcScIndexConfigAlgEnableConfig,
  &cmdEntryVPSSVfpcScIndexParamCompPortNotifyTypeConfig,
  &cmdEntryVPSSVfpcScIndexParamVFPCNumChPerHandleConfig,
  &cmdEntryVPSSVfpcScIndexParamPortDefinitionConfig,
  &cmdEntryVPSSVfpcScIndexConfigChannelNameConfig,
  NULL
};


/* VFPC config command table */

MX_DBG_CMD_TABLE_T cmdTblVPSSVfpcScConfig =
{
  MX_DBG_ACCESS_ALL,
  sizeof(cmdListVPSSVfpcScConfig)/sizeof(cmdListVPSSVfpcScConfig[0]),
  cmdListVPSSVfpcScConfig
};


/* VPSS VFPC SC config command entry */

MX_DBG_CMD_ENTRY_T cmdEntryVPSSVfpcScConfig =
{
  OMTB_VPSS_VFPC_SC_COMP_REF_STR,
  MX_DBG_CMD_TYPE_CMD_TABLE,
  MX_DBG_CMD_OPT_INST_CUR |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMTB_TEMPLATE_INFO,vpssVfpcScTemplate),
  0,
  0,
  0,
  0,
  0,
  &cmdTblVPSSVfpcScConfig,
  XdbgCmdTblFunc,
  "\nVPSS VFPC SC Config Parameters:\n",
  "",
  "",
  ""
};


/*----------------------------- end of file ---------------------------------*/
