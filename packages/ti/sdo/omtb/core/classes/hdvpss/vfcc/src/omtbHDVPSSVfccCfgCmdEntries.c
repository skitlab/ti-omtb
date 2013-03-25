/*
 * omtbHDVPSSVfccCfgCmdEntries.c
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
#include "omx_vfcc.h"


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
extern MX_DBG_CMD_TABLE_T cmdTblIndexParamVFCCHwPortPropertiesConfig;
extern MX_DBG_CMD_TABLE_T cmdTblIndexParamVFCCHwPortIDConfig;
extern MX_DBG_CMD_TABLE_T cmdTblIndexConfigVFCCFrameSkipConfig;
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
 *  OMTB component configuration parameter command entries - VFCC
 ******************************************************************************/

/*******************************************************************************
 *      VFCC config params
 ******************************************************************************/

/* Entry for Set OMX Component Name */

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryVPSSVfccCompName =
{
  "compname",
  MX_DBG_CMD_TYPE_VAR_STR_BUF,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMTB_VPSS_VFCC_CONFIG_PARAMS,sBasicParams.compName),
  FIELDOFFSET(OMTB_VPSS_VFCC_CONFIG_PARAMS,sBasicParams.inputFile) -
  FIELDOFFSET(OMTB_VPSS_VFCC_CONFIG_PARAMS,sBasicParams.compName),
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

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryVPSSVfccInFile =
{
  "infile",
  MX_DBG_CMD_TYPE_VAR_STR_BUF,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMTB_VPSS_VFCC_CONFIG_PARAMS,sBasicParams.inputFile),
  FIELDOFFSET(OMTB_VPSS_VFCC_CONFIG_PARAMS,sBasicParams.inputFile) -
  FIELDOFFSET(OMTB_VPSS_VFCC_CONFIG_PARAMS,sBasicParams.inputFile),
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

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryVPSSVfccOutFile =
{
  "outfile",
  MX_DBG_CMD_TYPE_VAR_STR_BUF,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMTB_VPSS_VFCC_CONFIG_PARAMS,sBasicParams.outputFile),
  FIELDOFFSET(OMTB_VPSS_VFCC_CONFIG_PARAMS,sBasicParams.inputFile) -
  FIELDOFFSET(OMTB_VPSS_VFCC_CONFIG_PARAMS,sBasicParams.outputFile),
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

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryVPSSVfccWidth =
{
  "frame_width",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_DEC      |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMTB_VPSS_VFCC_CONFIG_PARAMS,sBasicParams.frameWidth),
  FIELDOFFSET(OMTB_VPSS_VFCC_CONFIG_PARAMS,sBasicParams.inputFile) -
  FIELDOFFSET(OMTB_VPSS_VFCC_CONFIG_PARAMS,sBasicParams.frameWidth),
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

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryVPSSVfccHeight =
{
  "frame_height",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_DEC          |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMTB_VPSS_VFCC_CONFIG_PARAMS,sBasicParams.frameHeight),
  FIELDOFFSET(OMTB_VPSS_VFCC_CONFIG_PARAMS,sBasicParams.inputFile) -
  FIELDOFFSET(OMTB_VPSS_VFCC_CONFIG_PARAMS,sBasicParams.frameHeight),
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

PRIVATE MX_DBG_ENUM_ENTRY_T enumTblVPSSVfccOutputChromaFormat[] =
{
  {"RGB888",  OMX_COLOR_Format24bitRGB888, ""},
  {"420P",OMX_COLOR_FormatYUV420Planar, ""},
  {"420SP",OMX_COLOR_FormatYUV420SemiPlanar, ""},
  {"422P",OMX_COLOR_FormatYUV422Planar, ""},
  {"422YUYV", OMX_COLOR_FormatYCbYCr, ""},
  {"422SP",OMX_COLOR_FormatYUV422SemiPlanar, ""},
  {"", 0, ""}
};


/* Entry for Set O/P Color Format */

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryVPSSVfccOutputChromaFormat =
{
  "op_chromat_format",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_ENUM          |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMTB_VPSS_VFCC_CONFIG_PARAMS,sBasicParams.colorFormat),
  FIELDOFFSET(OMTB_VPSS_VFCC_CONFIG_PARAMS,sBasicParams.inputFile) -
  FIELDOFFSET(OMTB_VPSS_VFCC_CONFIG_PARAMS,sBasicParams.colorFormat),
  0,
  OMX_COLOR_FormatYUV420Planar,
  OMX_COLOR_FormatYCbYCr,
  OMX_COLOR_FormatYUV422Planar,
  &enumTblVPSSVfccOutputChromaFormat,
  XdbgCmdVarFunc,
  "O/P Chroma Format.............................",
  "",
  "",
  ""
};


/* Enum Entry for Selecting Data O/P Mode */

PRIVATE MX_DBG_ENUM_ENTRY_T enumTblDataOutputMode[] =
{
  {"file",  OMTB_FILE,    ""},
  {"driver",OMTB_DRIVER,  ""},
  {"none",  OMTB_NONE,    ""},
  {"",      0,            ""}
};


/* Entry for Setting Data Output Mode */

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryVPSSVfccOutputMode =
{
  "data_opmode",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_ENUM          |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMTB_VPSS_VFCC_CONFIG_PARAMS,sBasicParams.dataOutPutMode),
  FIELDOFFSET(OMTB_VPSS_VFCC_CONFIG_PARAMS,sBasicParams.inputFile) -
  FIELDOFFSET(OMTB_VPSS_VFCC_CONFIG_PARAMS,sBasicParams.dataOutPutMode),
  0,
  OMTB_FILE,
  OMTB_NONE,
  OMTB_FILE,
  &enumTblDataOutputMode,
  XdbgCmdVarFunc,
  "Data O/P Mode.................................",
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


/* Entry for Setting Use/Allocate output buffer */

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryVPSSVfccFlagUseAllocOutBuffer =
{
  "outbuf",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_ENUM          |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMTB_VPSS_VFCC_CONFIG_PARAMS,sBasicParams.flagUseOutBuffer),
  FIELDOFFSET(OMTB_VPSS_VFCC_CONFIG_PARAMS,sBasicParams.inputFile) -
  FIELDOFFSET(OMTB_VPSS_VFCC_CONFIG_PARAMS,sBasicParams.flagUseOutBuffer),
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

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryVPSSVfccNumOutBuf =
{
  "numoutbuf",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_DEC      |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMTB_VPSS_VFCC_CONFIG_PARAMS,sBasicParams.numOutBuf),
  FIELDOFFSET(OMTB_VPSS_VFCC_CONFIG_PARAMS,sBasicParams.inputFile) -
  FIELDOFFSET(OMTB_VPSS_VFCC_CONFIG_PARAMS,sBasicParams.numOutBuf),
  0,
  0,
  OMTB_VPSS_VFCC_MAX_NUM_OUT_BUFS,
  OMTB_VPSS_VFCC_MAX_NUM_OUT_BUFS,
  NULL,
  XdbgCmdVarFunc,
  "Number of o/p buffer..........................",
  "<# of output buffers>",
  "",
  ""
};

/* Entry for Set o/p buffer size */

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryVPSSVfccOutBufSize =
{
  "outbufsize",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_DEC          |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMTB_VPSS_VFCC_CONFIG_PARAMS,sBasicParams.outBufSize),
  FIELDOFFSET(OMTB_VPSS_VFCC_CONFIG_PARAMS,sBasicParams.inputFile) -
  FIELDOFFSET(OMTB_VPSS_VFCC_CONFIG_PARAMS,sBasicParams.outBufSize),
  0,
  0,
  OMTB_MAX_VAL_U32,
  OMTB_VPSS_VFCC_MAX_OUTBUFF_SIZE,
  NULL,
  XdbgCmdVarFunc,
  "O/p buffer size...............................",
  "<output buffer size>",
  "",
  ""
};

/* Entry for Set o/p buffer alignment */

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryVPSSVfccOutBufAlignment =
{
  "outbufalign",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_DEC          |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMTB_VPSS_VFCC_CONFIG_PARAMS,sBasicParams.outBufAlignment),
  FIELDOFFSET(OMTB_VPSS_VFCC_CONFIG_PARAMS,sBasicParams.inputFile) -
  FIELDOFFSET(OMTB_VPSS_VFCC_CONFIG_PARAMS,sBasicParams.outBufAlignment),
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

PRIVATE MX_DBG_ENUM_ENTRY_T enumTblVPSSVfccOnOff[] =
{
  {"enable",  OMX_TRUE,   ""},
  {"disable", OMX_FALSE,  ""},
  {"",        0,          ""}
};

/* Entry for Set o/p buffer size */

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryVPSSVfccOutBufSzFlag =
{
  "outbufsize_flag",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_ENUM         |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMTB_VPSS_VFCC_CONFIG_PARAMS,sBasicParams.outBufSzFlag),
  FIELDOFFSET(OMTB_VPSS_VFCC_CONFIG_PARAMS,sBasicParams.inputFile) -
  FIELDOFFSET(OMTB_VPSS_VFCC_CONFIG_PARAMS,sBasicParams.outBufSzFlag),
  0,
  OMX_FALSE,
  OMX_TRUE,
  OMX_FALSE,
  &enumTblVPSSVfccOnOff,
  XdbgCmdVarFunc,
  "O/P buffer size input from user...............",
  "",
  "",
  ""
};



/* Entry for Set o/p buffer continuous memory allocation */

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryVPSSVfccOutBufContiguous =
{
  "outbuf_contig",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_ENUM         |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMTB_VPSS_VFCC_CONFIG_PARAMS,sBasicParams.outBufContiguous),
  FIELDOFFSET(OMTB_VPSS_VFCC_CONFIG_PARAMS,sBasicParams.inputFile) -
  FIELDOFFSET(OMTB_VPSS_VFCC_CONFIG_PARAMS,sBasicParams.outBufContiguous),
  0,
  OMX_FALSE,
  OMX_TRUE,
  OMX_FALSE,
  &enumTblVPSSVfccOnOff,
  XdbgCmdVarFunc,
  "Contiguous o/p buffer memory..................",
  "",
  "",
  ""
};

/* Entry to set params of OMX_IndexParamCompBufferSupplier index*/
PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryVPSSVfccIndexParamCompBufferSupplierConfig =
{
  "OMX_IndexParamCompBufferSupplier",
  MX_DBG_CMD_TYPE_CMD_TABLE,
  MX_DBG_CMD_OPT_INST_CUR |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMTB_VPSS_VFCC_CONFIG_PARAMS,sBufSupplier),
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
PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryVPSSVfccIndexParamBuffMemTypeConfig =
{
  "OMX_TI_IndexParamBuffMemType",
  MX_DBG_CMD_TYPE_CMD_TABLE,
  MX_DBG_CMD_OPT_INST_CUR |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMTB_VPSS_VFCC_CONFIG_PARAMS,sMemTypeCfg),
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
PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryVPSSVfccIndexParamVideoInitConfig =
{
  "OMX_IndexParamVideoInit",
  MX_DBG_CMD_TYPE_CMD_TABLE,
  MX_DBG_CMD_OPT_INST_CUR |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMTB_VPSS_VFCC_CONFIG_PARAMS,sPortInit),
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

/* Entry to set params of OMX_TI_IndexParamVFCCHwPortProperties index*/
PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryVPSSVfccIndexParamVFCCHwPortPropertiesConfig =
{
  "OMX_TI_IndexParamVFCCHwPortProperties",
  MX_DBG_CMD_TYPE_CMD_TABLE,
  MX_DBG_CMD_OPT_INST_CUR |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMTB_VPSS_VFCC_CONFIG_PARAMS,sHwPortParam),
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
PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryVPSSVfccIndexParamVFCCHwPortIDConfig =
{
  "OMX_TI_IndexParamVFCCHwPortID",
  MX_DBG_CMD_TYPE_CMD_TABLE,
  MX_DBG_CMD_OPT_INST_CUR |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMTB_VPSS_VFCC_CONFIG_PARAMS,sHwPortId),
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

/* Entry to set params of OMX_TI_IndexConfigVFCCFrameSkip index*/
PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryVPSSVfccIndexConfigVFCCFrameSkipConfig =
{
  "OMX_TI_IndexConfigVFCCFrameSkip",
  MX_DBG_CMD_TYPE_CMD_TABLE,
  MX_DBG_CMD_OPT_INST_CUR |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMTB_VPSS_VFCC_CONFIG_PARAMS,sCapSkipFrames),
  0,
  0,
  0,
  0,
  0,
  &cmdTblIndexConfigVFCCFrameSkipConfig,
  XdbgCmdTblFunc,
  "OMX_TI_IndexConfigVFCCFrameSkip Index Parameters:",
  "",
  "",
  ""
};


/* Entry to set params of OMX_IndexParamPortDefinition index*/
PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryVPSSVfccIndexParamPortDefinitionConfig =
{
  "OMX_IndexParamPortDefinition",
  MX_DBG_CMD_TYPE_CMD_TABLE,
  MX_DBG_CMD_OPT_INST_CUR |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMTB_VPSS_VFCC_CONFIG_PARAMS,sPortDefType),
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
PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryVPSSVfccIndexConfigChannelNameConfig =
{
  "OMX_TI_IndexConfigChannelName",
  MX_DBG_CMD_TYPE_CMD_TABLE,
  MX_DBG_CMD_OPT_INST_CUR |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMTB_VPSS_VFCC_CONFIG_PARAMS,sChannelName),
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

/* VPSS VFCC config command table Entry */

MX_DBG_CMD_ENTRY_T* cmdListVPSSVfccConfig[] =
{
  &cmdEntryVPSSVfccCompName,
  &cmdEntryVPSSVfccInFile,
  &cmdEntryVPSSVfccOutFile,
  &cmdEntryVPSSVfccWidth,
  &cmdEntryVPSSVfccHeight,
  &cmdEntryVPSSVfccOutputChromaFormat,
  &cmdEntryVPSSVfccOutputMode,
  &cmdEntryVPSSVfccFlagUseAllocOutBuffer,
  &cmdEntryVPSSVfccNumOutBuf,
  &cmdEntryVPSSVfccOutBufAlignment,
  &cmdEntryVPSSVfccOutBufContiguous,
  &cmdEntryVPSSVfccOutBufSzFlag,
  &cmdEntryVPSSVfccOutBufSize,
  &cmdEntryVPSSVfccIndexParamCompBufferSupplierConfig,
  &cmdEntryVPSSVfccIndexParamBuffMemTypeConfig,
  &cmdEntryVPSSVfccIndexParamVideoInitConfig,
  &cmdEntryVPSSVfccIndexParamVFCCHwPortPropertiesConfig,
  &cmdEntryVPSSVfccIndexParamVFCCHwPortIDConfig,
  &cmdEntryVPSSVfccIndexConfigVFCCFrameSkipConfig,
  &cmdEntryVPSSVfccIndexParamPortDefinitionConfig,
  &cmdEntryVPSSVfccIndexConfigChannelNameConfig,
  NULL
};

/* VPSS VFCC config command table */

MX_DBG_CMD_TABLE_T cmdTblVPSSVfccConfig =
{
  MX_DBG_ACCESS_ALL,
  sizeof(cmdListVPSSVfccConfig)/sizeof(cmdListVPSSVfccConfig[0]),
  cmdListVPSSVfccConfig
};


/* VPSS VFCC config command entry */

MX_DBG_CMD_ENTRY_T cmdEntryVPSSVfccConfig =
{
  OMTB_VPSS_VFCC_COMP_REF_STR,
  MX_DBG_CMD_TYPE_CMD_TABLE,
  MX_DBG_CMD_OPT_INST_CUR |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMTB_TEMPLATE_INFO,vpssVfccTemplate),
  0,
  0,
  0,
  0,
  0,
  &cmdTblVPSSVfccConfig,
  XdbgCmdTblFunc,
  "\nVPSS VFCC Config Parameters:\n",
  "",
  "",
  ""
};


/*----------------------------- end of file ---------------------------------*/
