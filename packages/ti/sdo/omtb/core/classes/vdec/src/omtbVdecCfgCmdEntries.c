/*
 * omtbVdecCfgCmdEntries.c
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
extern MX_DBG_CMD_TABLE_T cmdTblIndexParamCompBufferSupplierConfig;
extern MX_DBG_CMD_TABLE_T cmdTblIndexParamBuffMemTypeConfig;
extern MX_DBG_CMD_TABLE_T cmdTblIndexParamVideoInitConfig;
extern MX_DBG_CMD_TABLE_T cmdTblIndexConfigVideoMacroBlockErrorMapConfig;
extern MX_DBG_CMD_TABLE_T cmdTblIndexParamFileModeTypeConfig;
extern MX_DBG_CMD_TABLE_T cmdTblIndexParamVideoPortFormatConfig;
extern MX_DBG_CMD_TABLE_T cmdTblIndexParamCompPortNotifyTypeConfig;
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
 *  OMTB component configuration parameter command entries - vdec
 ******************************************************************************/

/*******************************************************************************
 *      Video decoder config params
 ******************************************************************************/

/* Entry for Set OMX Component Name */

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryVdecCompName =
{
  "compname",
  MX_DBG_CMD_TYPE_VAR_STR_BUF,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMTB_VDEC_CONFIG_PARAMS,sBasicParams.compName),
  FIELDOFFSET(OMTB_VDEC_CONFIG_PARAMS,sBasicParams.inputFile) -
  FIELDOFFSET(OMTB_VDEC_CONFIG_PARAMS,sBasicParams.compName),
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

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryVdecInFile =
{
  "infile",
  MX_DBG_CMD_TYPE_VAR_STR_BUF,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMTB_VDEC_CONFIG_PARAMS,sBasicParams.inputFile),
  FIELDOFFSET(OMTB_VDEC_CONFIG_PARAMS,sBasicParams.inputFile) -
  FIELDOFFSET(OMTB_VDEC_CONFIG_PARAMS,sBasicParams.inputFile),
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

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryVdecOutFile =
{
  "outfile",
  MX_DBG_CMD_TYPE_VAR_STR_BUF,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMTB_VDEC_CONFIG_PARAMS,sBasicParams.outputFile),
  FIELDOFFSET(OMTB_VDEC_CONFIG_PARAMS,sBasicParams.inputFile) -
  FIELDOFFSET(OMTB_VDEC_CONFIG_PARAMS,sBasicParams.outputFile),
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

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryVdecWidth =
{
  "frame_width",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_DEC      |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMTB_VDEC_CONFIG_PARAMS,sBasicParams.frameWidth),
  FIELDOFFSET(OMTB_VDEC_CONFIG_PARAMS,sBasicParams.inputFile) -
  FIELDOFFSET(OMTB_VDEC_CONFIG_PARAMS,sBasicParams.frameWidth),
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

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryVdecHeight =
{
  "frame_height",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_DEC          |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMTB_VDEC_CONFIG_PARAMS,sBasicParams.frameHeight),
  FIELDOFFSET(OMTB_VDEC_CONFIG_PARAMS,sBasicParams.inputFile) -
  FIELDOFFSET(OMTB_VDEC_CONFIG_PARAMS,sBasicParams.frameHeight),
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

PRIVATE MX_DBG_ENUM_ENTRY_T enumTblVdecOutputChromaFormat[] =
{
  {"420P",OMX_COLOR_FormatYUV420Planar, ""},
  {"420SP",OMX_COLOR_FormatYUV420SemiPlanar, ""},
  {"422P",OMX_COLOR_FormatYUV422Planar, ""},
  {"422YUYV", OMX_COLOR_FormatYCbYCr, ""},
  {"", 0, ""}
};


/* Entry for Set O/P Color Format */

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryVdecOutputChromaFormat =
{
  "op_chromat_format",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_ENUM          |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMTB_VDEC_CONFIG_PARAMS,sBasicParams.colorFormat),
  FIELDOFFSET(OMTB_VDEC_CONFIG_PARAMS,sBasicParams.inputFile) -
  FIELDOFFSET(OMTB_VDEC_CONFIG_PARAMS,sBasicParams.colorFormat),
  0,
  OMX_COLOR_FormatYUV420Planar,
  OMX_COLOR_FormatYCbYCr,
  OMX_COLOR_FormatYUV420SemiPlanar,
  &enumTblVdecOutputChromaFormat,
  XdbgCmdVarFunc,
  "O/P Chroma Format.............................",
  "",
  "",
  ""
};

/* Entry for Set I/P Color Format */

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryVdecInputChromaFormat =
{
  "ip_chromat_format",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_ENUM          |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMTB_VDEC_CONFIG_PARAMS,sBasicParams.inColorFormat),
  FIELDOFFSET(OMTB_VDEC_CONFIG_PARAMS,sBasicParams.inputFile) -
  FIELDOFFSET(OMTB_VDEC_CONFIG_PARAMS,sBasicParams.inColorFormat),
  0,
  OMX_COLOR_FormatYUV420Planar,
  OMX_COLOR_FormatYCbYCr,
  OMX_COLOR_FormatYUV420Planar,
  &enumTblVdecOutputChromaFormat,
  XdbgCmdVarFunc,
  "I/P Chroma Format.............................",
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

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryVdecOutputMode =
{
  "data_opmode",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_ENUM          |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMTB_VDEC_CONFIG_PARAMS,sBasicParams.dataOutPutMode),
  FIELDOFFSET(OMTB_VDEC_CONFIG_PARAMS,sBasicParams.inputFile) -
  FIELDOFFSET(OMTB_VDEC_CONFIG_PARAMS,sBasicParams.dataOutPutMode),
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


/* Enum Entry for Selecting Data O/P Mode */

PRIVATE MX_DBG_ENUM_ENTRY_T enumTblDataInputMode[] =
{
  {"file",  OMTB_FILE,    ""},
  {"driver",OMTB_DRIVER,  ""},
  {"none",  OMTB_NONE,    ""},
  {"",      0,            ""}
};


/* Entry for Setting Data Output Mode */

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryVdecInputMode =
{
  "data_ipmode",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_ENUM         |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMTB_VDEC_CONFIG_PARAMS,sBasicParams.dataInPutMode),
  FIELDOFFSET(OMTB_VDEC_CONFIG_PARAMS,sBasicParams.inputFile) -
  FIELDOFFSET(OMTB_VDEC_CONFIG_PARAMS,sBasicParams.dataInPutMode),
  0,
  OMTB_FILE,
  OMTB_NONE,
  OMTB_FILE,
  &enumTblDataInputMode,
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

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryVdecFlagUseAllocInBuffer =
{
  "inbuf",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_ENUM          |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMTB_VDEC_CONFIG_PARAMS,sBasicParams.flagUseInBuffer),
  FIELDOFFSET(OMTB_VDEC_CONFIG_PARAMS,sBasicParams.inputFile) -
  FIELDOFFSET(OMTB_VDEC_CONFIG_PARAMS,sBasicParams.flagUseInBuffer),
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


/* Entry for Setting Use/Allocate output buffer */

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryVdecFlagUseAllocOutBuffer =
{
  "outbuf",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_ENUM          |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMTB_VDEC_CONFIG_PARAMS,sBasicParams.flagUseOutBuffer),
  FIELDOFFSET(OMTB_VDEC_CONFIG_PARAMS,sBasicParams.inputFile) -
  FIELDOFFSET(OMTB_VDEC_CONFIG_PARAMS,sBasicParams.flagUseOutBuffer),
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


/*Entry for Set number of i/p buffers */

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryVdecNumInBuf =
{
  "numinbuf",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_DEC      |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMTB_VDEC_CONFIG_PARAMS,sBasicParams.numInBuf),
  FIELDOFFSET(OMTB_VDEC_CONFIG_PARAMS,sBasicParams.inputFile) -
  FIELDOFFSET(OMTB_VDEC_CONFIG_PARAMS,sBasicParams.numInBuf),
  0,
  0,
  OMTB_VDEC_MAX_NUM_IN_BUFS,
  OMTB_VDEC_MAX_NUM_IN_BUFS,
  NULL,
  XdbgCmdVarFunc,
  "Number of i/p buffer..........................",
  "<# of input buffers>",
  "",
  ""
};


/*Entry for Set number of o/p buffers */

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryVdecNumOutBuf =
{
  "numoutbuf",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_DEC      |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMTB_VDEC_CONFIG_PARAMS,sBasicParams.numOutBuf),
  FIELDOFFSET(OMTB_VDEC_CONFIG_PARAMS,sBasicParams.inputFile) -
  FIELDOFFSET(OMTB_VDEC_CONFIG_PARAMS,sBasicParams.numOutBuf),
  0,
  0,
  OMTB_VDEC_MAX_NUM_OUT_BUFS,
  OMTB_VDEC_MAX_NUM_OUT_BUFS,
  NULL,
  XdbgCmdVarFunc,
  "Number of o/p buffer..........................",
  "<# of output buffers>",
  "",
  ""
};


/* Entry for Set i/p buffer size */

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryVdecInBufSize =
{
  "inbufsize",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_DEC          |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMTB_VDEC_CONFIG_PARAMS,sBasicParams.inBufSize),
  FIELDOFFSET(OMTB_VDEC_CONFIG_PARAMS,sBasicParams.inputFile) -
  FIELDOFFSET(OMTB_VDEC_CONFIG_PARAMS,sBasicParams.inBufSize),
  0,
  0,
  OMTB_MAX_VAL_U32,
  OMTB_VDEC_MAX_INBUFF_SIZE,
  NULL,
  XdbgCmdVarFunc,
  "I/p buffer size...............................",
  "<input buffer size>",
  "",
  ""
};


/* Entry for Set o/p buffer size */

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryVdecOutBufSize =
{
  "outbufsize",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_DEC          |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMTB_VDEC_CONFIG_PARAMS,sBasicParams.outBufSize),
  FIELDOFFSET(OMTB_VDEC_CONFIG_PARAMS,sBasicParams.inputFile) -
  FIELDOFFSET(OMTB_VDEC_CONFIG_PARAMS,sBasicParams.outBufSize),
  0,
  0,
  OMTB_MAX_VAL_U32,
  OMTB_VDEC_MAX_OUTBUFF_SIZE,
  NULL,
  XdbgCmdVarFunc,
  "O/p buffer size...............................",
  "<output buffer size>",
  "",
  ""
};


/* Entry for Set i/p buffer alignment */

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryVdecInBufAlignment =
{
  "inbufalign",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_DEC          |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMTB_VDEC_CONFIG_PARAMS,sBasicParams.inBufAlignment),
  FIELDOFFSET(OMTB_VDEC_CONFIG_PARAMS,sBasicParams.inputFile) -
  FIELDOFFSET(OMTB_VDEC_CONFIG_PARAMS,sBasicParams.inBufAlignment),
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


/* Entry for Set o/p buffer alignment */

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryVdecOutBufAlignment =
{
  "outbufalign",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_DEC          |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMTB_VDEC_CONFIG_PARAMS,sBasicParams.outBufAlignment),
  FIELDOFFSET(OMTB_VDEC_CONFIG_PARAMS,sBasicParams.inputFile) -
  FIELDOFFSET(OMTB_VDEC_CONFIG_PARAMS,sBasicParams.outBufAlignment),
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

PRIVATE MX_DBG_ENUM_ENTRY_T enumTblVdecOnOff[] =
{
  {"enable",  OMX_TRUE,   ""},
  {"disable", OMX_FALSE,  ""},
  {"",        0,          ""}
};


/* Entry for Set i/p buffer size */

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryVdecInBufSzFlag =
{
  "inbufsize_flag",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_ENUM         |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMTB_VDEC_CONFIG_PARAMS,sBasicParams.inBufSzFlag),
  FIELDOFFSET(OMTB_VDEC_CONFIG_PARAMS,sBasicParams.inputFile) -
  FIELDOFFSET(OMTB_VDEC_CONFIG_PARAMS,sBasicParams.inBufSzFlag),
  0,
  OMX_FALSE,
  OMX_TRUE,
  OMX_FALSE,
  &enumTblVdecOnOff,
  XdbgCmdVarFunc,
  "I/P buffer size input from user...............",
  "",
  "",
  ""
};


/* Entry for Set o/p buffer size */

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryVdecOutBufSzFlag =
{
  "outbufsize_flag",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_ENUM         |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMTB_VDEC_CONFIG_PARAMS,sBasicParams.outBufSzFlag),
  FIELDOFFSET(OMTB_VDEC_CONFIG_PARAMS,sBasicParams.inputFile) -
  FIELDOFFSET(OMTB_VDEC_CONFIG_PARAMS,sBasicParams.outBufSzFlag),
  0,
  OMX_FALSE,
  OMX_TRUE,
  OMX_FALSE,
  &enumTblVdecOnOff,
  XdbgCmdVarFunc,
  "O/P buffer size input from user...............",
  "",
  "",
  ""
};

/* Entry for Set i/p buffer continuous memory allocation */

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryVdecInBufContiguous =
{
  "inbuf_contig",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_ENUM         |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMTB_VDEC_CONFIG_PARAMS,sBasicParams.inBufContiguous),
  FIELDOFFSET(OMTB_VDEC_CONFIG_PARAMS,sBasicParams.inputFile) -
  FIELDOFFSET(OMTB_VDEC_CONFIG_PARAMS,sBasicParams.inBufContiguous),
  0,
  OMX_FALSE,
  OMX_TRUE,
  OMX_FALSE,
  &enumTblVdecOnOff,
  XdbgCmdVarFunc,
  "Contiguous i/p buffer memory..................",
  "",
  "",
  ""
};


/* Entry for Set o/p buffer continuous memory allocation */

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryVdecOutBufContiguous =
{
  "outbuf_contig",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_ENUM         |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMTB_VDEC_CONFIG_PARAMS,sBasicParams.outBufContiguous),
  FIELDOFFSET(OMTB_VDEC_CONFIG_PARAMS,sBasicParams.inputFile) -
  FIELDOFFSET(OMTB_VDEC_CONFIG_PARAMS,sBasicParams.outBufContiguous),
  0,
  OMX_FALSE,
  OMX_TRUE,
  OMX_FALSE,
  &enumTblVdecOnOff,
  XdbgCmdVarFunc,
  "Contiguous o/p buffer memory..................",
  "",
  "",
  ""
};

/* Enum Entry for Supported Input Compression Format */

PRIVATE MX_DBG_ENUM_ENTRY_T enumTblVdecInputCompressionFormat[] =
{
  {"unused",     OMX_VIDEO_CodingUnused,     ""},
  {"autodetect", OMX_VIDEO_CodingAutoDetect, ""},
  {"mpeg2",      OMX_VIDEO_CodingMPEG2,      ""},
  {"h263",       OMX_VIDEO_CodingH263,       ""},
  {"mpeg4",      OMX_VIDEO_CodingMPEG4,      ""},
  {"wmv",        OMX_VIDEO_CodingWMV,        ""},
  {"rv",         OMX_VIDEO_CodingRV,         ""},
  {"avc",        OMX_VIDEO_CodingAVC,        ""},
  {"mjpeg",      OMX_VIDEO_CodingMJPEG,      ""},
  {"",           0,                          ""}
};

/* Entry for Set Compression Format */

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryVdecInputCompressionFormat =
{
  "ip_compression_format",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_ENUM          |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMTB_VDEC_CONFIG_PARAMS,sBasicParams.compressionFormat),
  FIELDOFFSET(OMTB_VDEC_CONFIG_PARAMS,sBasicParams.inputFile) -
  FIELDOFFSET(OMTB_VDEC_CONFIG_PARAMS,sBasicParams.compressionFormat),
  0,
  OMX_VIDEO_CodingUnused,
  OMX_VIDEO_CodingMJPEG,
  OMX_VIDEO_CodingAVC,
  &enumTblVdecInputCompressionFormat,
  XdbgCmdVarFunc,
  "I/P Compression Format........................",
  "",
  "",
  ""
};


/* Entry for Set Framerate */
PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryVdecFramerate =
{
  "framerate",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_DEC          |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMTB_VDEC_CONFIG_PARAMS,sBasicParams.nFramerate),
  FIELDOFFSET(OMTB_VDEC_CONFIG_PARAMS,sBasicParams.inputFile) -
  FIELDOFFSET(OMTB_VDEC_CONFIG_PARAMS,sBasicParams.nFramerate),
  0,
  0,
  OMTB_MAX_VAL_U32,
  OMTB_VDEC_DEF_FRM_RATE,
  NULL,
  XdbgCmdVarFunc,
  "Frame rate....................................",
  "<framerate>",
  "",
  ""
};


/* Entry for Set File reset flag */

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryVdecFileResetFlag =
{
  "filereset_flag",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_ENUM         |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMTB_VDEC_CONFIG_PARAMS,sBasicParams.fileReset),
  FIELDOFFSET(OMTB_VDEC_CONFIG_PARAMS,sBasicParams.inputFile) -
  FIELDOFFSET(OMTB_VDEC_CONFIG_PARAMS,sBasicParams.fileReset),
  0,
  OMX_FALSE,
  OMX_TRUE,
  OMX_FALSE,
  &enumTblVdecOnOff,
  XdbgCmdVarFunc,
  "File Reset Flag...............................",
  "",
  "",
  ""
};

/* Entry to set params of OMX_IndexParamCompBufferSupplier index*/
PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryVdecIndexParamCompBufferSupplierConfig =
{
  "OMX_IndexParamCompBufferSupplier",
  MX_DBG_CMD_TYPE_CMD_TABLE,
  MX_DBG_CMD_OPT_INST_CUR |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMTB_VDEC_CONFIG_PARAMS,sBufSupplier),
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
PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryVdecIndexParamBuffMemTypeConfig =
{
  "OMX_TI_IndexParamBuffMemType",
  MX_DBG_CMD_TYPE_CMD_TABLE,
  MX_DBG_CMD_OPT_INST_CUR |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMTB_VDEC_CONFIG_PARAMS,sMemTypeCfg),
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
PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryVdecIndexParamVideoInitConfig =
{
  "OMX_IndexParamVideoInit",
  MX_DBG_CMD_TYPE_CMD_TABLE,
  MX_DBG_CMD_OPT_INST_CUR |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMTB_VDEC_CONFIG_PARAMS,sPortInit),
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

/* Entry to set params of OMX_IndexConfigVideoMacroBlockErrorMap index*/
PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryVdecIndexConfigVideoMacroBlockErrorMapConfig =
{
  "OMX_IndexConfigVideoMacroBlockErrorMap",
  MX_DBG_CMD_TYPE_CMD_TABLE,
  MX_DBG_CMD_OPT_INST_CUR |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMTB_VDEC_CONFIG_PARAMS,sMbErrorReporting),
  0,
  0,
  0,
  0,
  0,
  &cmdTblIndexConfigVideoMacroBlockErrorMapConfig,
  XdbgCmdTblFunc,
  "OMX_IndexConfigVideoMacroBlockErrorMap Index Parameters:",
  "",
  "",
  ""
};

/* Entry to set params of OMX_TI_IndexParamFileModeType index*/
PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryVdecIndexParamFileModeTypeConfig =
{
  "OMX_TI_IndexParamFileModeType",
  MX_DBG_CMD_TYPE_CMD_TABLE,
  MX_DBG_CMD_OPT_INST_CUR |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMTB_VDEC_CONFIG_PARAMS,sFileModeCfg),
  0,
  0,
  0,
  0,
  0,
  &cmdTblIndexParamFileModeTypeConfig,
  XdbgCmdTblFunc,
  "OMX_TI_IndexParamFileModeType Index Parameters:",
  "",
  "",
  ""
};

/* Entry to set params of OMX_IndexParamVideoPortFormat index*/
PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryVdecIndexParamVideoPortFormatConfig =
{
  "OMX_IndexParamVideoPortFormat",
  MX_DBG_CMD_TYPE_CMD_TABLE,
  MX_DBG_CMD_OPT_INST_CUR |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMTB_VDEC_CONFIG_PARAMS,sVideoPortFormat),
  0,
  0,
  0,
  0,
  0,
  &cmdTblIndexParamVideoPortFormatConfig,
  XdbgCmdTblFunc,
  "OMX_IndexParamVideoPortFormat Index Parameters:",
  "",
  "",
  ""
};

/* Entry to set params of OMX_TI_IndexParamCompPortNotifyType index*/
PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryVdecIndexParamCompPortNotifyTypeConfig =
{
  "OMX_TI_IndexParamCompPortNotifyType",
  MX_DBG_CMD_TYPE_CMD_TABLE,
  MX_DBG_CMD_OPT_INST_CUR |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMTB_VDEC_CONFIG_PARAMS,sCompPortNotifyType),
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

/* Entry to set params of OMX_IndexParamPortDefinition index*/
PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryVdecIndexParamPortDefinitionConfig =
{
  "OMX_IndexParamPortDefinition",
  MX_DBG_CMD_TYPE_CMD_TABLE,
  MX_DBG_CMD_OPT_INST_CUR |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMTB_VDEC_CONFIG_PARAMS,sPortDefType),
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
PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryVdecIndexConfigChannelNameConfig =
{
  "OMX_TI_IndexConfigChannelName",
  MX_DBG_CMD_TYPE_CMD_TABLE,
  MX_DBG_CMD_OPT_INST_CUR |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMTB_VDEC_CONFIG_PARAMS,sChannelName),
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

/* vdec config command table Entry */

MX_DBG_CMD_ENTRY_T* cmdListVdecConfig[] =
{
  &cmdEntryVdecCompName,
  &cmdEntryVdecInFile,
  &cmdEntryVdecOutFile,
  &cmdEntryVdecWidth,
  &cmdEntryVdecHeight,
  &cmdEntryVdecOutputChromaFormat,
  &cmdEntryVdecInputChromaFormat,
  &cmdEntryVdecOutputMode,
  &cmdEntryVdecInputMode,  
  &cmdEntryVdecFlagUseAllocInBuffer,
  &cmdEntryVdecNumInBuf,
  &cmdEntryVdecInBufAlignment,
  &cmdEntryVdecInBufContiguous,
  &cmdEntryVdecInBufSzFlag,
  &cmdEntryVdecInBufSize,
  &cmdEntryVdecFlagUseAllocOutBuffer,
  &cmdEntryVdecNumOutBuf,
  &cmdEntryVdecOutBufAlignment,
  &cmdEntryVdecOutBufContiguous,
  &cmdEntryVdecOutBufSzFlag,
  &cmdEntryVdecOutBufSize,
  &cmdEntryVdecInputCompressionFormat,
  &cmdEntryVdecFramerate,
  &cmdEntryVdecFileResetFlag,
  
  &cmdEntryVdecIndexParamBuffMemTypeConfig,
  &cmdEntryVdecIndexParamVideoInitConfig,
  &cmdEntryVdecIndexConfigVideoMacroBlockErrorMapConfig,
  &cmdEntryVdecIndexParamFileModeTypeConfig,
  &cmdEntryVdecIndexParamCompBufferSupplierConfig,
  &cmdEntryVdecIndexParamVideoPortFormatConfig,
  &cmdEntryVdecIndexParamCompPortNotifyTypeConfig,
  &cmdEntryVdecIndexParamPortDefinitionConfig,
  &cmdEntryVdecIndexConfigChannelNameConfig,
  NULL
};


/* vdec config command table */

MX_DBG_CMD_TABLE_T cmdTblVdecConfig =
{
  MX_DBG_ACCESS_ALL,
  sizeof(cmdListVdecConfig)/sizeof(cmdListVdecConfig[0]),
  cmdListVdecConfig
};


/* vdec config command entry */

MX_DBG_CMD_ENTRY_T cmdEntryVdecConfig =
{
  OMTB_VDEC_COMP_REF_STR,
  MX_DBG_CMD_TYPE_CMD_TABLE,
  MX_DBG_CMD_OPT_INST_CUR |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMTB_TEMPLATE_INFO,vdecTemplate),
  0,
  0,
  0,
  0,
  0,
  &cmdTblVdecConfig,
  XdbgCmdTblFunc,
  "\n Video Decoder Config Parameters:\n",
  "",
  "",
  ""
};


/*----------------------------- end of file ---------------------------------*/
