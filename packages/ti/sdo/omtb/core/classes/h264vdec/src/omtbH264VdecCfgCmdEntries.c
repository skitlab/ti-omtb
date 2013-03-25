/*
 * omtbH264VdecCfgCmdEntries.c
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
 *  OMTB component configuration parameter command entries - h264vdec
 ******************************************************************************/

/*******************************************************************************
 *      H264 decoder config params
 ******************************************************************************/

/* Entry for Set OMX Component Name */

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryH264VdecCompName =
{
  "compname",
  MX_DBG_CMD_TYPE_VAR_STR_BUF,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMTB_H264_VDEC_CONFIG_PARAMS,sBasicParams.compName),
  FIELDOFFSET(OMTB_H264_VDEC_CONFIG_PARAMS,sBasicParams.inputFile) -
  FIELDOFFSET(OMTB_H264_VDEC_CONFIG_PARAMS,sBasicParams.compName),
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

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryH264VdecInFile =
{
  "infile",
  MX_DBG_CMD_TYPE_VAR_STR_BUF,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMTB_H264_VDEC_CONFIG_PARAMS,sBasicParams.inputFile),
  FIELDOFFSET(OMTB_H264_VDEC_CONFIG_PARAMS,sBasicParams.inputFile) -
  FIELDOFFSET(OMTB_H264_VDEC_CONFIG_PARAMS,sBasicParams.inputFile),
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

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryH264VdecOutFile =
{
  "outfile",
  MX_DBG_CMD_TYPE_VAR_STR_BUF,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMTB_H264_VDEC_CONFIG_PARAMS,sBasicParams.outputFile),
  FIELDOFFSET(OMTB_H264_VDEC_CONFIG_PARAMS,sBasicParams.inputFile) -
  FIELDOFFSET(OMTB_H264_VDEC_CONFIG_PARAMS,sBasicParams.outputFile),
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

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryH264VdecWidth =
{
  "frame_width",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_DEC      |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMTB_H264_VDEC_CONFIG_PARAMS,sBasicParams.frameWidth),
  FIELDOFFSET(OMTB_H264_VDEC_CONFIG_PARAMS,sBasicParams.inputFile) -
  FIELDOFFSET(OMTB_H264_VDEC_CONFIG_PARAMS,sBasicParams.frameWidth),
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

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryH264VdecHeight =
{
  "frame_height",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_DEC          |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMTB_H264_VDEC_CONFIG_PARAMS,sBasicParams.frameHeight),
  FIELDOFFSET(OMTB_H264_VDEC_CONFIG_PARAMS,sBasicParams.inputFile) -
  FIELDOFFSET(OMTB_H264_VDEC_CONFIG_PARAMS,sBasicParams.frameHeight),
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

PRIVATE MX_DBG_ENUM_ENTRY_T enumTblH264VdecOutputChromaFormat[] =
{
  {"420P",OMX_COLOR_FormatYUV420Planar, ""},
  {"420SP",OMX_COLOR_FormatYUV420SemiPlanar, ""},
  {"422P",OMX_COLOR_FormatYUV422Planar, ""},
  {"422YUYV", OMX_COLOR_FormatYCbYCr, ""},
  {"", 0, ""}
};


/* Entry for Set O/P Color Format */

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryH264VdecOutputChromaFormat =
{
  "op_chromat_format",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_ENUM          |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMTB_H264_VDEC_CONFIG_PARAMS,sBasicParams.colorFormat),
  FIELDOFFSET(OMTB_H264_VDEC_CONFIG_PARAMS,sBasicParams.inputFile) -
  FIELDOFFSET(OMTB_H264_VDEC_CONFIG_PARAMS,sBasicParams.colorFormat),
  0,
  OMX_COLOR_FormatYUV420Planar,
  OMX_COLOR_FormatYCbYCr,
  OMX_COLOR_FormatYUV420SemiPlanar,
  &enumTblH264VdecOutputChromaFormat,
  XdbgCmdVarFunc,
  "O/P Chroma Format.............................",
  "",
  "",
  ""
};

/* Entry for Set I/P Color Format */

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryH264VdecInputChromaFormat =
{
  "ip_chromat_format",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_ENUM          |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMTB_H264_VDEC_CONFIG_PARAMS,sBasicParams.inColorFormat),
  FIELDOFFSET(OMTB_H264_VDEC_CONFIG_PARAMS,sBasicParams.inputFile) -
  FIELDOFFSET(OMTB_H264_VDEC_CONFIG_PARAMS,sBasicParams.inColorFormat),
  0,
  OMX_COLOR_FormatYUV420Planar,
  OMX_COLOR_FormatYCbYCr,
  OMX_COLOR_FormatYUV420Planar,
  &enumTblH264VdecOutputChromaFormat,
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

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryH264VdecOutputMode =
{
  "data_opmode",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_ENUM          |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMTB_H264_VDEC_CONFIG_PARAMS,sBasicParams.dataOutPutMode),
  FIELDOFFSET(OMTB_H264_VDEC_CONFIG_PARAMS,sBasicParams.inputFile) -
  FIELDOFFSET(OMTB_H264_VDEC_CONFIG_PARAMS,sBasicParams.dataOutPutMode),
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

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryH264VdecInputMode =
{
  "data_ipmode",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_ENUM         |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMTB_H264_VDEC_CONFIG_PARAMS,sBasicParams.dataInPutMode),
  FIELDOFFSET(OMTB_H264_VDEC_CONFIG_PARAMS,sBasicParams.inputFile) -
  FIELDOFFSET(OMTB_H264_VDEC_CONFIG_PARAMS,sBasicParams.dataInPutMode),
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

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryH264VdecFlagUseAllocInBuffer =
{
  "inbuf",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_ENUM          |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMTB_H264_VDEC_CONFIG_PARAMS,sBasicParams.flagUseInBuffer),
  FIELDOFFSET(OMTB_H264_VDEC_CONFIG_PARAMS,sBasicParams.inputFile) -
  FIELDOFFSET(OMTB_H264_VDEC_CONFIG_PARAMS,sBasicParams.flagUseInBuffer),
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

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryH264VdecFlagUseAllocOutBuffer =
{
  "outbuf",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_ENUM          |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMTB_H264_VDEC_CONFIG_PARAMS,sBasicParams.flagUseOutBuffer),
  FIELDOFFSET(OMTB_H264_VDEC_CONFIG_PARAMS,sBasicParams.inputFile) -
  FIELDOFFSET(OMTB_H264_VDEC_CONFIG_PARAMS,sBasicParams.flagUseOutBuffer),
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

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryH264VdecNumInBuf =
{
  "numinbuf",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_DEC      |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMTB_H264_VDEC_CONFIG_PARAMS,sBasicParams.numInBuf),
  FIELDOFFSET(OMTB_H264_VDEC_CONFIG_PARAMS,sBasicParams.inputFile) -
  FIELDOFFSET(OMTB_H264_VDEC_CONFIG_PARAMS,sBasicParams.numInBuf),
  0,
  0,
  OMTB_H264_VDEC_MAX_NUM_IN_BUFS,
  OMTB_H264_VDEC_MAX_NUM_IN_BUFS,
  NULL,
  XdbgCmdVarFunc,
  "Number of i/p buffer..........................",
  "<# of input buffers>",
  "",
  ""
};


/*Entry for Set number of o/p buffers */

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryH264VdecNumOutBuf =
{
  "numoutbuf",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_DEC      |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMTB_H264_VDEC_CONFIG_PARAMS,sBasicParams.numOutBuf),
  FIELDOFFSET(OMTB_H264_VDEC_CONFIG_PARAMS,sBasicParams.inputFile) -
  FIELDOFFSET(OMTB_H264_VDEC_CONFIG_PARAMS,sBasicParams.numOutBuf),
  0,
  0,
  OMTB_H264_VDEC_MAX_NUM_OUT_BUFS,
  OMTB_H264_VDEC_MAX_NUM_OUT_BUFS,
  NULL,
  XdbgCmdVarFunc,
  "Number of o/p buffer..........................",
  "<# of output buffers>",
  "",
  ""
};


/* Entry for Set i/p buffer size */

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryH264VdecInBufSize =
{
  "inbufsize",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_DEC          |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMTB_H264_VDEC_CONFIG_PARAMS,sBasicParams.inBufSize),
  FIELDOFFSET(OMTB_H264_VDEC_CONFIG_PARAMS,sBasicParams.inputFile) -
  FIELDOFFSET(OMTB_H264_VDEC_CONFIG_PARAMS,sBasicParams.inBufSize),
  0,
  0,
  OMTB_MAX_VAL_U32,
  OMTB_H264_VDEC_MAX_INBUFF_SIZE,
  NULL,
  XdbgCmdVarFunc,
  "I/p buffer size...............................",
  "<input buffer size>",
  "",
  ""
};


/* Entry for Set o/p buffer size */

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryH264VdecOutBufSize =
{
  "outbufsize",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_DEC          |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMTB_H264_VDEC_CONFIG_PARAMS,sBasicParams.outBufSize),
  FIELDOFFSET(OMTB_H264_VDEC_CONFIG_PARAMS,sBasicParams.inputFile) -
  FIELDOFFSET(OMTB_H264_VDEC_CONFIG_PARAMS,sBasicParams.outBufSize),
  0,
  0,
  OMTB_MAX_VAL_U32,
  OMTB_H264_VDEC_MAX_OUTBUFF_SIZE,
  NULL,
  XdbgCmdVarFunc,
  "O/p buffer size...............................",
  "<output buffer size>",
  "",
  ""
};


/* Entry for Set i/p buffer alignment */

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryH264VdecInBufAlignment =
{
  "inbufalign",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_DEC          |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMTB_H264_VDEC_CONFIG_PARAMS,sBasicParams.inBufAlignment),
  FIELDOFFSET(OMTB_H264_VDEC_CONFIG_PARAMS,sBasicParams.inputFile) -
  FIELDOFFSET(OMTB_H264_VDEC_CONFIG_PARAMS,sBasicParams.inBufAlignment),
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

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryH264VdecOutBufAlignment =
{
  "outbufalign",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_DEC          |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMTB_H264_VDEC_CONFIG_PARAMS,sBasicParams.outBufAlignment),
  FIELDOFFSET(OMTB_H264_VDEC_CONFIG_PARAMS,sBasicParams.inputFile) -
  FIELDOFFSET(OMTB_H264_VDEC_CONFIG_PARAMS,sBasicParams.outBufAlignment),
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

PRIVATE MX_DBG_ENUM_ENTRY_T enumTblH264VdecOnOff[] =
{
  {"enable",  OMX_TRUE,   ""},
  {"disable", OMX_FALSE,  ""},
  {"",        0,          ""}
};


/* Entry for Set i/p buffer size */

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryH264VdecInBufSzFlag =
{
  "inbufsize_flag",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_ENUM         |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMTB_H264_VDEC_CONFIG_PARAMS,sBasicParams.inBufSzFlag),
  FIELDOFFSET(OMTB_H264_VDEC_CONFIG_PARAMS,sBasicParams.inputFile) -
  FIELDOFFSET(OMTB_H264_VDEC_CONFIG_PARAMS,sBasicParams.inBufSzFlag),
  0,
  OMX_FALSE,
  OMX_TRUE,
  OMX_FALSE,
  &enumTblH264VdecOnOff,
  XdbgCmdVarFunc,
  "I/P buffer size input from user...............",
  "",
  "",
  ""
};


/* Entry for Set o/p buffer size */

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryH264VdecOutBufSzFlag =
{
  "outbufsize_flag",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_ENUM         |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMTB_H264_VDEC_CONFIG_PARAMS,sBasicParams.outBufSzFlag),
  FIELDOFFSET(OMTB_H264_VDEC_CONFIG_PARAMS,sBasicParams.inputFile) -
  FIELDOFFSET(OMTB_H264_VDEC_CONFIG_PARAMS,sBasicParams.outBufSzFlag),
  0,
  OMX_FALSE,
  OMX_TRUE,
  OMX_FALSE,
  &enumTblH264VdecOnOff,
  XdbgCmdVarFunc,
  "O/P buffer size input from user...............",
  "",
  "",
  ""
};

/* Entry for Set i/p buffer continuous memory allocation */

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryH264VdecInBufContiguous =
{
  "inbuf_contig",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_ENUM         |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMTB_H264_VDEC_CONFIG_PARAMS,sBasicParams.inBufContiguous),
  FIELDOFFSET(OMTB_H264_VDEC_CONFIG_PARAMS,sBasicParams.inputFile) -
  FIELDOFFSET(OMTB_H264_VDEC_CONFIG_PARAMS,sBasicParams.inBufContiguous),
  0,
  OMX_FALSE,
  OMX_TRUE,
  OMX_FALSE,
  &enumTblH264VdecOnOff,
  XdbgCmdVarFunc,
  "Contiguous i/p buffer memory..................",
  "",
  "",
  ""
};


/* Entry for Set o/p buffer continuous memory allocation */

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryH264VdecOutBufContiguous =
{
  "outbuf_contig",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_ENUM         |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMTB_H264_VDEC_CONFIG_PARAMS,sBasicParams.outBufContiguous),
  FIELDOFFSET(OMTB_H264_VDEC_CONFIG_PARAMS,sBasicParams.inputFile) -
  FIELDOFFSET(OMTB_H264_VDEC_CONFIG_PARAMS,sBasicParams.outBufContiguous),
  0,
  OMX_FALSE,
  OMX_TRUE,
  OMX_FALSE,
  &enumTblH264VdecOnOff,
  XdbgCmdVarFunc,
  "Contiguous o/p buffer memory..................",
  "",
  "",
  ""
};

/* Enum Entry for Supported Input Compression Format */

PRIVATE MX_DBG_ENUM_ENTRY_T enumTblH264VdecInputCompressionFormat[] =
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

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryH264VdecInputCompressionFormat =
{
  "ip_compression_format",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_ENUM          |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMTB_H264_VDEC_CONFIG_PARAMS,sBasicParams.compressionFormat),
  FIELDOFFSET(OMTB_H264_VDEC_CONFIG_PARAMS,sBasicParams.inputFile) -
  FIELDOFFSET(OMTB_H264_VDEC_CONFIG_PARAMS,sBasicParams.compressionFormat),
  0,
  OMX_VIDEO_CodingUnused,
  OMX_VIDEO_CodingMJPEG,
  OMX_VIDEO_CodingAVC,
  &enumTblH264VdecInputCompressionFormat,
  XdbgCmdVarFunc,
  "I/P Compression Format........................",
  "",
  "",
  ""
};


/* Entry for Set Framerate */
PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryH264VdecFramerate =
{
  "framerate",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_DEC          |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMTB_H264_VDEC_CONFIG_PARAMS,sBasicParams.nFramerate),
  FIELDOFFSET(OMTB_H264_VDEC_CONFIG_PARAMS,sBasicParams.inputFile) -
  FIELDOFFSET(OMTB_H264_VDEC_CONFIG_PARAMS,sBasicParams.nFramerate),
  0,
  0,
  OMTB_MAX_VAL_U32,
  OMTB_H264_VDEC_DEF_FRM_RATE,
  NULL,
  XdbgCmdVarFunc,
  "Frame rate....................................",
  "<framerate>",
  "",
  ""
};


/* Entry for Set File reset flag */

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryH264VdecFileResetFlag =
{
  "filereset_flag",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_ENUM         |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMTB_H264_VDEC_CONFIG_PARAMS,sBasicParams.fileReset),
  FIELDOFFSET(OMTB_H264_VDEC_CONFIG_PARAMS,sBasicParams.inputFile) -
  FIELDOFFSET(OMTB_H264_VDEC_CONFIG_PARAMS,sBasicParams.fileReset),
  0,
  OMX_FALSE,
  OMX_TRUE,
  OMX_FALSE,
  &enumTblH264VdecOnOff,
  XdbgCmdVarFunc,
  "File Reset Flag...............................",
  "",
  "",
  ""
};

/* Entry to set params of OMX_IndexParamCompBufferSupplier index*/
PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryH264VdecIndexParamCompBufferSupplierConfig =
{
  "OMX_IndexParamCompBufferSupplier",
  MX_DBG_CMD_TYPE_CMD_TABLE,
  MX_DBG_CMD_OPT_INST_CUR |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMTB_H264_VDEC_CONFIG_PARAMS,sBufSupplier),
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
PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryH264VdecIndexParamBuffMemTypeConfig =
{
  "OMX_TI_IndexParamBuffMemType",
  MX_DBG_CMD_TYPE_CMD_TABLE,
  MX_DBG_CMD_OPT_INST_CUR |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMTB_H264_VDEC_CONFIG_PARAMS,sMemTypeCfg),
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
PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryH264VdecIndexParamVideoInitConfig =
{
  "OMX_IndexParamVideoInit",
  MX_DBG_CMD_TYPE_CMD_TABLE,
  MX_DBG_CMD_OPT_INST_CUR |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMTB_H264_VDEC_CONFIG_PARAMS,sPortInit),
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
PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryH264VdecIndexConfigVideoMacroBlockErrorMapConfig =
{
  "OMX_IndexConfigVideoMacroBlockErrorMap",
  MX_DBG_CMD_TYPE_CMD_TABLE,
  MX_DBG_CMD_OPT_INST_CUR |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMTB_H264_VDEC_CONFIG_PARAMS,sMbErrorReporting),
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
PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryH264VdecIndexParamFileModeTypeConfig =
{
  "OMX_TI_IndexParamFileModeType",
  MX_DBG_CMD_TYPE_CMD_TABLE,
  MX_DBG_CMD_OPT_INST_CUR |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMTB_H264_VDEC_CONFIG_PARAMS,sFileModeCfg),
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
PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryH264VdecIndexParamVideoPortFormatConfig =
{
  "OMX_IndexParamVideoPortFormat",
  MX_DBG_CMD_TYPE_CMD_TABLE,
  MX_DBG_CMD_OPT_INST_CUR |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMTB_H264_VDEC_CONFIG_PARAMS,sVideoPortFormat),
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
PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryH264VdecIndexParamCompPortNotifyTypeConfig =
{
  "OMX_TI_IndexParamCompPortNotifyType",
  MX_DBG_CMD_TYPE_CMD_TABLE,
  MX_DBG_CMD_OPT_INST_CUR |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMTB_H264_VDEC_CONFIG_PARAMS,sCompPortNotifyType),
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
PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryH264VdecIndexParamPortDefinitionConfig =
{
  "OMX_IndexParamPortDefinition",
  MX_DBG_CMD_TYPE_CMD_TABLE,
  MX_DBG_CMD_OPT_INST_CUR |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMTB_H264_VDEC_CONFIG_PARAMS,sPortDefType),
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
PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryH264VdecIndexConfigChannelNameConfig =
{
  "OMX_TI_IndexConfigChannelName",
  MX_DBG_CMD_TYPE_CMD_TABLE,
  MX_DBG_CMD_OPT_INST_CUR |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMTB_H264_VDEC_CONFIG_PARAMS,sChannelName),
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

/* h264vdec config command table Entry */

MX_DBG_CMD_ENTRY_T* cmdListH264VdecConfig[] =
{
  &cmdEntryH264VdecCompName,
  &cmdEntryH264VdecInFile,
  &cmdEntryH264VdecOutFile,
  &cmdEntryH264VdecWidth,
  &cmdEntryH264VdecHeight,
  &cmdEntryH264VdecOutputChromaFormat,
  &cmdEntryH264VdecInputChromaFormat,
  &cmdEntryH264VdecOutputMode,
  &cmdEntryH264VdecInputMode,  
  &cmdEntryH264VdecFlagUseAllocInBuffer,
  &cmdEntryH264VdecNumInBuf,
  &cmdEntryH264VdecInBufAlignment,
  &cmdEntryH264VdecInBufContiguous,
  &cmdEntryH264VdecInBufSzFlag,
  &cmdEntryH264VdecInBufSize,
  &cmdEntryH264VdecFlagUseAllocOutBuffer,
  &cmdEntryH264VdecNumOutBuf,
  &cmdEntryH264VdecOutBufAlignment,
  &cmdEntryH264VdecOutBufContiguous,
  &cmdEntryH264VdecOutBufSzFlag,
  &cmdEntryH264VdecOutBufSize,
  &cmdEntryH264VdecInputCompressionFormat,
  &cmdEntryH264VdecFramerate,
  &cmdEntryH264VdecFileResetFlag,
  
  &cmdEntryH264VdecIndexParamBuffMemTypeConfig,
  &cmdEntryH264VdecIndexParamVideoInitConfig,
  &cmdEntryH264VdecIndexConfigVideoMacroBlockErrorMapConfig,
  &cmdEntryH264VdecIndexParamFileModeTypeConfig,
  &cmdEntryH264VdecIndexParamCompBufferSupplierConfig,
  &cmdEntryH264VdecIndexParamVideoPortFormatConfig,
  &cmdEntryH264VdecIndexParamCompPortNotifyTypeConfig,
  &cmdEntryH264VdecIndexParamPortDefinitionConfig,
  &cmdEntryH264VdecIndexConfigChannelNameConfig,
  NULL
};


/* h264vdec config command table */

MX_DBG_CMD_TABLE_T cmdTblH264VdecConfig =
{
  MX_DBG_ACCESS_ALL,
  sizeof(cmdListH264VdecConfig)/sizeof(cmdListH264VdecConfig[0]),
  cmdListH264VdecConfig
};


/* H264vdec config command entry */

MX_DBG_CMD_ENTRY_T cmdEntryH264VdecConfig =
{
  OMTB_H264_VDEC_COMP_REF_STR,
  MX_DBG_CMD_TYPE_CMD_TABLE,
  MX_DBG_CMD_OPT_INST_CUR |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMTB_TEMPLATE_INFO,h264VdecTemplate),
  0,
  0,
  0,
  0,
  0,
  &cmdTblH264VdecConfig,
  XdbgCmdTblFunc,
  "\nH264 Video Decoder Config Parameters:\n",
  "",
  "",
  ""
};


/*----------------------------- end of file ---------------------------------*/
