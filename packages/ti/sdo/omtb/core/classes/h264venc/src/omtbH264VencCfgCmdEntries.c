/*
 * omtbH264VencCfgCmdEntries.c
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
#include "OMX_TI_Video.h"
#include "OMX_TI_Index.h"


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
extern MX_DBG_CMD_TABLE_T  cmdTblIndexConfigVideoFramerateConfig;
extern MX_DBG_CMD_TABLE_T  cmdTblIndexConfigVideoBitrateConfig;
extern MX_DBG_CMD_TABLE_T  cmdTblIndexConfigVideoMESearchRangeConfig;
extern MX_DBG_CMD_TABLE_T  cmdTblIndexConfigVideoIntraVOPRefreshConfig;
extern MX_DBG_CMD_TABLE_T  cmdTblIndexConfigVideoQPSettingsConfig;
extern MX_DBG_CMD_TABLE_T  cmdTblIndexConfigVideoAVCIntraPeriodConfig;
extern MX_DBG_CMD_TABLE_T  cmdTblIndexConfigSliceSettingsConfig;
extern MX_DBG_CMD_TABLE_T  cmdTblIndexConfigVideoPixelInfoConfig;
extern MX_DBG_CMD_TABLE_T  cmdTblIndexParamVideoNALUsettingsConfig;
extern MX_DBG_CMD_TABLE_T  cmdTblIndexParamVideoAdvancedFMOConfig;
extern MX_DBG_CMD_TABLE_T  cmdTblIndexParamVideoMEBlockSizeConfig;
extern MX_DBG_CMD_TABLE_T  cmdTblIndexParamVideoIntraRefreshConfig;
extern MX_DBG_CMD_TABLE_T  cmdTblIndexParamVideoVUIsettingsConfig;
extern MX_DBG_CMD_TABLE_T  cmdTblIndexParamVideoIntraPredictionSettingsConfig;
extern MX_DBG_CMD_TABLE_T  cmdTblIndexParamVideoDataSyncModeConfig;
extern MX_DBG_CMD_TABLE_T  cmdTblIndexConfigVideoNalSizeConfig;
extern MX_DBG_CMD_TABLE_T  cmdTblIndexParamVideoAvcConfig;
extern MX_DBG_CMD_TABLE_T  cmdTblIndexParamVideoBitrateConfig;
extern MX_DBG_CMD_TABLE_T  cmdTblIndexParamVideoProfileLevelCurrentConfig;
extern MX_DBG_CMD_TABLE_T  cmdTblIndexParamVideoBitStreamFormatSelectConfig;
extern MX_DBG_CMD_TABLE_T  cmdTblIndexParamVideoEncoderPresetConfig;
extern MX_DBG_CMD_TABLE_T  cmdTblIndexParamVideoFrameDataContentSettingsConfig;
extern MX_DBG_CMD_TABLE_T  cmdTblIndexParamVideoTransformBlockSizeConfig;
extern MX_DBG_CMD_TABLE_T  cmdTblIndexParamVideoSliceFMOConfig;
extern MX_DBG_CMD_TABLE_T  cmdTblIndexParamVideoMotionVectorConfig;
extern MX_DBG_CMD_TABLE_T  cmdTblIndexParamBuffMemTypeConfig;
extern MX_DBG_CMD_TABLE_T  cmdTblIndexParamCompBufferSupplierConfig;
extern MX_DBG_CMD_TABLE_T  cmdTblIndexParamVideoInitConfig;
extern MX_DBG_CMD_TABLE_T  cmdTblIndexParamVideoPortFormatConfig;
extern MX_DBG_CMD_TABLE_T  cmdTblIndexParamVideoQuantizationConfig;
extern MX_DBG_CMD_TABLE_T  cmdTblIndexParamCompPortNotifyTypeConfig;
extern MX_DBG_CMD_TABLE_T  cmdTblIndexParamPortDefinitionConfig;  
extern MX_DBG_CMD_TABLE_T  cmdTblIndexConfigChannelNameConfig;
extern MX_DBG_CMD_TABLE_T  cmdTblIndexParamVideoDynamicParamsConfig;

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
 *  OMTB component configuration parameter command entries - h264venc
 ******************************************************************************/

/*******************************************************************************
 *      H264 encoder config params
 ******************************************************************************/

/*******************************************************************************
 *                    Basic configuration Params
 ******************************************************************************/

/* Entry for Set OMX Component Name */

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryH264VencCompName =
{
  "compname",
  MX_DBG_CMD_TYPE_VAR_STR_BUF,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMTB_H264_VENC_CONFIG_PARAMS,sBasicParams.compName),
  FIELDOFFSET(OMTB_H264_VENC_CONFIG_PARAMS,sBasicParams.inputFile) -
  FIELDOFFSET(OMTB_H264_VENC_CONFIG_PARAMS,sBasicParams.compName),
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

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryH264VencInFile =
{
  "infile",
  MX_DBG_CMD_TYPE_VAR_STR_BUF,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMTB_H264_VENC_CONFIG_PARAMS,sBasicParams.inputFile),
  FIELDOFFSET(OMTB_H264_VENC_CONFIG_PARAMS,sBasicParams.inputFile) -
  FIELDOFFSET(OMTB_H264_VENC_CONFIG_PARAMS,sBasicParams.inputFile),
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

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryH264VencOutFile =
{
  "outfile",
  MX_DBG_CMD_TYPE_VAR_STR_BUF,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMTB_H264_VENC_CONFIG_PARAMS,sBasicParams.outputFile),
  FIELDOFFSET(OMTB_H264_VENC_CONFIG_PARAMS,sBasicParams.inputFile) -
  FIELDOFFSET(OMTB_H264_VENC_CONFIG_PARAMS,sBasicParams.outputFile),
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

/* Entry for set number of bytes per span of an image */
PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryH264VencStride =
{
  "stride",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_DEC      |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMTB_H264_VENC_CONFIG_PARAMS,sBasicParams.nStride),
  FIELDOFFSET(OMTB_H264_VENC_CONFIG_PARAMS,sBasicParams.inputFile) -
  FIELDOFFSET(OMTB_H264_VENC_CONFIG_PARAMS,sBasicParams.nStride),
  0,
  0,
  OMTB_MAX_VID_WIDTH,
  OMTB_MAX_VID_WIDTH,
  NULL,
  XdbgCmdVarFunc,
  "I/P Stride (# of bytes per span of image).....",
  "<Stride>",
  "",
  ""
};

/* Entry for Set Input Frame Width */

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryH264VencWidth =
{
  "frame_width",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_DEC      |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMTB_H264_VENC_CONFIG_PARAMS,sBasicParams.frameWidth),
  FIELDOFFSET(OMTB_H264_VENC_CONFIG_PARAMS,sBasicParams.inputFile) -
  FIELDOFFSET(OMTB_H264_VENC_CONFIG_PARAMS,sBasicParams.frameWidth),
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


/* Entry for Set Input Frame Height */

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryH264VencHeight =
{
  "frame_height",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_DEC          |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMTB_H264_VENC_CONFIG_PARAMS,sBasicParams.frameHeight),
  FIELDOFFSET(OMTB_H264_VENC_CONFIG_PARAMS,sBasicParams.inputFile) -
  FIELDOFFSET(OMTB_H264_VENC_CONFIG_PARAMS,sBasicParams.frameHeight),
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


/* Enum Entry for Supported I/P Color Format */

PRIVATE MX_DBG_ENUM_ENTRY_T enumTblH264VencInputChromaFormat[] =
{
  {"420P",    OMX_COLOR_FormatYUV420Planar, ""},
  {"420SP",   OMX_COLOR_FormatYUV420SemiPlanar, ""},
  {"422P",    OMX_COLOR_FormatYUV422Planar, ""},
  {"422YUYV", OMX_COLOR_FormatYCbYCr, ""},
  {"420PSP", OMX_COLOR_FormatYUV420PackedSemiPlanar, ""},
  {"", 0, ""}
};


/* Entry for Set I/P Color Format */

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryH264VencInputChromaFormat =
{
  "ip_chromat_format",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_ENUM          |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMTB_H264_VENC_CONFIG_PARAMS,sBasicParams.colorFormat),
  FIELDOFFSET(OMTB_H264_VENC_CONFIG_PARAMS,sBasicParams.inputFile) -
  FIELDOFFSET(OMTB_H264_VENC_CONFIG_PARAMS,sBasicParams.colorFormat),
  0,
  OMX_COLOR_FormatYUV420Planar,
  OMX_COLOR_FormatYCbYCr,
  OMX_COLOR_FormatYUV422Planar,
  &enumTblH264VencInputChromaFormat,
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

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryH264VencOutputMode =
{
  "data_opmode",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_ENUM         |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMTB_H264_VENC_CONFIG_PARAMS,sBasicParams.dataOutPutMode),
  FIELDOFFSET(OMTB_H264_VENC_CONFIG_PARAMS,sBasicParams.inputFile) -
  FIELDOFFSET(OMTB_H264_VENC_CONFIG_PARAMS,sBasicParams.dataOutPutMode),
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

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryH264VencInputMode =
{
  "data_ipmode",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_ENUM         |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMTB_H264_VENC_CONFIG_PARAMS,sBasicParams.dataInPutMode),
  FIELDOFFSET(OMTB_H264_VENC_CONFIG_PARAMS,sBasicParams.inputFile) -
  FIELDOFFSET(OMTB_H264_VENC_CONFIG_PARAMS,sBasicParams.dataInPutMode),
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

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryH264VencFlagUseAllocInBuffer =
{
  "inbuf",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_ENUM         |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMTB_H264_VENC_CONFIG_PARAMS,sBasicParams.flagUseInBuffer),
  FIELDOFFSET(OMTB_H264_VENC_CONFIG_PARAMS,sBasicParams.inputFile) -
  FIELDOFFSET(OMTB_H264_VENC_CONFIG_PARAMS,sBasicParams.flagUseInBuffer),
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

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryH264VencFlagUseAllocOutBuffer =
{
  "outbuf",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_ENUM         |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMTB_H264_VENC_CONFIG_PARAMS,sBasicParams.flagUseOutBuffer),
  FIELDOFFSET(OMTB_H264_VENC_CONFIG_PARAMS,sBasicParams.inputFile) -
  FIELDOFFSET(OMTB_H264_VENC_CONFIG_PARAMS,sBasicParams.flagUseOutBuffer),
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


/* Entry for Set number of i/p buffers */

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryH264VencNumInBuf =
{
  "numinbuf",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_DEC          |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMTB_H264_VENC_CONFIG_PARAMS,sBasicParams.numInBuf),
  FIELDOFFSET(OMTB_H264_VENC_CONFIG_PARAMS,sBasicParams.inputFile) -
  FIELDOFFSET(OMTB_H264_VENC_CONFIG_PARAMS,sBasicParams.numInBuf),
  0,
  0,
  OMTB_H264_VENC_MAX_NUM_IN_BUFS,
  OMTB_H264_VENC_MAX_NUM_IN_BUFS,
  NULL,
  XdbgCmdVarFunc,
  "Number of i/p buffer..........................",
  "<# of input buffers>",
  "",
  ""
};


/* Entry for Set number of o/p buffers */

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryH264VencNumOutBuf =
{
  "numoutbuf",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_DEC          |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMTB_H264_VENC_CONFIG_PARAMS,sBasicParams.numOutBuf),
  FIELDOFFSET(OMTB_H264_VENC_CONFIG_PARAMS,sBasicParams.inputFile) -
  FIELDOFFSET(OMTB_H264_VENC_CONFIG_PARAMS,sBasicParams.numOutBuf),
  0,
  0,
  OMTB_H264_VENC_MAX_NUM_OUT_BUFS,
  OMTB_H264_VENC_MAX_NUM_OUT_BUFS,
  NULL,
  XdbgCmdVarFunc,
  "Number of o/p buffer..........................",
  "<# of output buffers>",
  "",
  ""
};


/* Entry for Set i/p buffer size */

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryH264VencInBufSize =
{
  "inbufsize",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_DEC          |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMTB_H264_VENC_CONFIG_PARAMS,sBasicParams.inBufSize),
  FIELDOFFSET(OMTB_H264_VENC_CONFIG_PARAMS,sBasicParams.inputFile) -
  FIELDOFFSET(OMTB_H264_VENC_CONFIG_PARAMS,sBasicParams.inBufSize),
  0,
  0,
  OMTB_MAX_VAL_U32,
  OMTB_H264_VENC_MAX_INBUF_SIZE,
  NULL,
  XdbgCmdVarFunc,
  "I/p buffer size...............................",
  "<input buffer size>",
  "",
  ""
};


/* Entry for Set o/p buffer size */

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryH264VencOutBufSize =
{
  "outbufsize",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_DEC          |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMTB_H264_VENC_CONFIG_PARAMS,sBasicParams.outBufSize),
  FIELDOFFSET(OMTB_H264_VENC_CONFIG_PARAMS,sBasicParams.inputFile) -
  FIELDOFFSET(OMTB_H264_VENC_CONFIG_PARAMS,sBasicParams.outBufSize),
  0,
  0,
  OMTB_MAX_VAL_U32,
  OMTB_H264_VENC_MAX_OUTBUF_SIZE,
  NULL,
  XdbgCmdVarFunc,
  "O/p buffer size...............................",
  "<output buffer size>",
  "",
  ""
};


/* Entry for Set i/p buffer alignment */

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryH264VencInBufAlignment =
{
  "inbufalign",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_DEC          |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMTB_H264_VENC_CONFIG_PARAMS,sBasicParams.inBufAlignment),
  FIELDOFFSET(OMTB_H264_VENC_CONFIG_PARAMS,sBasicParams.inputFile) -
  FIELDOFFSET(OMTB_H264_VENC_CONFIG_PARAMS,sBasicParams.inBufAlignment),
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

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryH264VencOutBufAlignment =
{
  "outbufalign",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_DEC          |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMTB_H264_VENC_CONFIG_PARAMS,sBasicParams.outBufAlignment),
  FIELDOFFSET(OMTB_H264_VENC_CONFIG_PARAMS,sBasicParams.inputFile) -
  FIELDOFFSET(OMTB_H264_VENC_CONFIG_PARAMS,sBasicParams.outBufAlignment),
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

PRIVATE MX_DBG_ENUM_ENTRY_T enumTblH264VencOnOff[] =
{
  {"enable",  OMX_TRUE,   ""},
  {"disable", OMX_FALSE,  ""},
  {"",        0,          ""}
};


/* Entry for Set i/p buffer size */

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryH264VencInBufSzFlag =
{
  "inbufsize_flag",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_ENUM         |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMTB_H264_VENC_CONFIG_PARAMS,sBasicParams.inBufSzFlag),
  FIELDOFFSET(OMTB_H264_VENC_CONFIG_PARAMS,sBasicParams.inputFile) -
  FIELDOFFSET(OMTB_H264_VENC_CONFIG_PARAMS,sBasicParams.inBufSzFlag),
  0,
  OMX_FALSE,
  OMX_TRUE,
  OMX_FALSE,
  &enumTblH264VencOnOff,
  XdbgCmdVarFunc,
  "I/P buffer size input from user...............",
  "",
  "",
  ""
};


/* Entry for Set o/p buffer size */

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryH264VencOutBufSzFlag =
{
  "outbufsize_flag",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_ENUM         |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMTB_H264_VENC_CONFIG_PARAMS,sBasicParams.outBufSzFlag),
  FIELDOFFSET(OMTB_H264_VENC_CONFIG_PARAMS,sBasicParams.inputFile) -
  FIELDOFFSET(OMTB_H264_VENC_CONFIG_PARAMS,sBasicParams.outBufSzFlag),
  0,
  OMX_FALSE,
  OMX_TRUE,
  OMX_FALSE,
  &enumTblH264VencOnOff,
  XdbgCmdVarFunc,
  "O/P buffer size input from user...............",
  "",
  "",
  ""
};

/* Entry for Set i/p buffer continuous memory allocation */

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryH264VencInBufContiguous =
{
  "inbuf_contig",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_ENUM         |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMTB_H264_VENC_CONFIG_PARAMS,sBasicParams.inBufContiguous),
  FIELDOFFSET(OMTB_H264_VENC_CONFIG_PARAMS,sBasicParams.inputFile) -
  FIELDOFFSET(OMTB_H264_VENC_CONFIG_PARAMS,sBasicParams.inBufContiguous),
  0,
  OMX_FALSE,
  OMX_TRUE,
  OMX_FALSE,
  &enumTblH264VencOnOff,
  XdbgCmdVarFunc,
  "Contiguous i/p buffer memory..................",
  "",
  "",
  ""
};


/* Entry for Set o/p buffer continuous memory allocation */

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryH264VencOutBufContiguous =
{
  "outbuf_contig",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_ENUM         |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMTB_H264_VENC_CONFIG_PARAMS,sBasicParams.outBufContiguous),
  FIELDOFFSET(OMTB_H264_VENC_CONFIG_PARAMS,sBasicParams.inputFile) -
  FIELDOFFSET(OMTB_H264_VENC_CONFIG_PARAMS,sBasicParams.outBufContiguous),
  0,
  OMX_FALSE,
  OMX_TRUE,
  OMX_FALSE,
  &enumTblH264VencOnOff,
  XdbgCmdVarFunc,
  "Contiguous o/p buffer memory..................",
  "",
  "",
  ""
};

/* Enum Entry for Supported Output Compression Format */

PRIVATE MX_DBG_ENUM_ENTRY_T enumTblH264VencOutputCompressionFormat[] =
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

/* Entry for Set Output Compression Format */

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryH264VencOutputCompressionFormat =
{
  "op_compression_format",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_ENUM          |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMTB_H264_VENC_CONFIG_PARAMS,sBasicParams.compressionFormat),
  FIELDOFFSET(OMTB_H264_VENC_CONFIG_PARAMS,sBasicParams.inputFile) -
  FIELDOFFSET(OMTB_H264_VENC_CONFIG_PARAMS,sBasicParams.compressionFormat),
  0,
  OMX_VIDEO_CodingUnused,
  OMX_VIDEO_CodingMJPEG,
  OMX_VIDEO_CodingAVC,
  &enumTblH264VencOutputCompressionFormat,
  XdbgCmdVarFunc,
  "O/P Compression Format........................",
  "",
  "",
  ""
};

/* Entry for Set basic param flag */
#if 0
PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryH264VencBasicParamFlag =
{
  "basicparam_flag",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_ENUM         |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMTB_H264_VENC_CONFIG_PARAMS,sBasicParams.flagBasicParam),
  FIELDOFFSET(OMTB_H264_VENC_CONFIG_PARAMS,sBasicParams.inputFile) -
  FIELDOFFSET(OMTB_H264_VENC_CONFIG_PARAMS,sBasicParams.flagBasicParam),
  0,
  OMX_FALSE,
  OMX_TRUE,
  OMX_FALSE,
  &enumTblH264VencOnOff,
  XdbgCmdVarFunc,
  "Set Basic Parameters from template............",
  "",
  "",
  ""
};
#endif
 
/* Entry for Set Bitrate */
PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryH264VencBitrate =
{
  "bitrate",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_DEC          |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMTB_H264_VENC_CONFIG_PARAMS,sBasicParams.nBitrate),
  FIELDOFFSET(OMTB_H264_VENC_CONFIG_PARAMS,sBasicParams.inputFile) -
  FIELDOFFSET(OMTB_H264_VENC_CONFIG_PARAMS,sBasicParams.nBitrate),
  0,
  0,
  OMTB_MAX_VAL_U32,
  OMTB_H264_VENC_DEF_BIT_RATE,
  NULL,
  XdbgCmdVarFunc,
  "Bitrate.......................................",
  "<bitrate>",
  "",
  ""
};

/* Entry for Set Framerate */
PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryH264VencFramerate =
{
  "framerate",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_DEC          |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMTB_H264_VENC_CONFIG_PARAMS,sBasicParams.nFramerate),
  FIELDOFFSET(OMTB_H264_VENC_CONFIG_PARAMS,sBasicParams.inputFile) -
  FIELDOFFSET(OMTB_H264_VENC_CONFIG_PARAMS,sBasicParams.nFramerate),
  0,
  0,
  OMTB_MAX_VAL_U32,
  OMTB_H264_VENC_DEF_FRM_RATE,
  NULL,
  XdbgCmdVarFunc,
  "Frame rate....................................",
  "<framerate>",
  "",
  ""
};

/* Entry for set number of bytes per span of an image */
PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryH264VencMaxFileSize =
{
  "maxfilesize",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_DEC      |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMTB_H264_VENC_CONFIG_PARAMS,sBasicParams.maxFileSize),
  FIELDOFFSET(OMTB_H264_VENC_CONFIG_PARAMS,sBasicParams.inputFile) -
  FIELDOFFSET(OMTB_H264_VENC_CONFIG_PARAMS,sBasicParams.maxFileSize),
  0,
  0,
  OMTB_MAX_VAL_U32,
  OMTB_MAX_FILE_SIZE,
  NULL,
  XdbgCmdVarFunc,
  "Max file size for OMTB demo...................",
  "<MaxFileSize>",
  "",
  ""
};


/* Entry for Set File reset flag */

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryH264VencFileResetFlag =
{
  "filereset_flag",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_ENUM         |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMTB_H264_VENC_CONFIG_PARAMS,sBasicParams.fileReset),
  FIELDOFFSET(OMTB_H264_VENC_CONFIG_PARAMS,sBasicParams.inputFile) -
  FIELDOFFSET(OMTB_H264_VENC_CONFIG_PARAMS,sBasicParams.fileReset),
  0,
  OMX_FALSE,
  OMX_TRUE,
  OMX_FALSE,
  &enumTblH264VencOnOff,
  XdbgCmdVarFunc,
  "File Reset Flag...............................",
  "",
  "",
  ""
};


/*******************************************************************************
 *                    Configuration Params
 ******************************************************************************/

/*Basic configuration Params */

/* Entry to set params of OMX_IndexParamVideoAvc index*/
PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryH264VencIndexParamVideoAvcConfig =
{
  "OMX_IndexParamVideoAvc",
  MX_DBG_CMD_TYPE_CMD_TABLE,
  MX_DBG_CMD_OPT_INST_CUR |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMTB_H264_VENC_CONFIG_PARAMS,sAVCParams),
  0,
  0,
  0,
  0,
  0,
  &cmdTblIndexParamVideoAvcConfig,
  XdbgCmdTblFunc,
  "OMX_IndexParamVideoAvc Index Parameters:",
  "",
  "",
  ""
};
	
/* Entry to set params of OMX_IndexParamVideoBitrate index*/
PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryH264VencIndexParamVideoBitrateConfig =
{
  "OMX_IndexParamVideoBitrate",
  MX_DBG_CMD_TYPE_CMD_TABLE,
  MX_DBG_CMD_OPT_INST_CUR |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMTB_H264_VENC_CONFIG_PARAMS,sParamBitRate),
  0,
  0,
  0,
  0,
  0,
  &cmdTblIndexParamVideoBitrateConfig,
  XdbgCmdTblFunc,
  "OMX_IndexParamVideoBitrate Index Parameters:",
  "",
  "",
  ""
};

/* Entry to set params of OMX_IndexParamVideoProfileLevelCurrent index*/
PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryH264VencIndexParamVideoProfileLevelCurrentConfig =
{
  "OMX_IndexParamVideoProfileLevelCurrent",
  MX_DBG_CMD_TYPE_CMD_TABLE,
  MX_DBG_CMD_OPT_INST_CUR |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMTB_H264_VENC_CONFIG_PARAMS,sProfileLevel),
  0,
  0,
  0,
  0,
  0,
  &cmdTblIndexParamVideoProfileLevelCurrentConfig,
  XdbgCmdTblFunc,
  "OMX_IndexParamVideoProfileLevelCurrent Index Parameters:",
  "",
  "",
  ""
};

/* Entry to set params of OMX_TI_IndexParamVideoBitStreamFormatSelect index*/
PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryH264VencIndexParamVideoBitStreamFormatSelectConfig =
{
  "OMX_TI_IndexParamVideoBitStreamFormatSelect",
  MX_DBG_CMD_TYPE_CMD_TABLE,
  MX_DBG_CMD_OPT_INST_CUR |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMTB_H264_VENC_CONFIG_PARAMS,sBitStreamFormat),
  0,
  0,
  0,
  0,
  0,
  &cmdTblIndexParamVideoBitStreamFormatSelectConfig,
  XdbgCmdTblFunc,
  "OMX_TI_IndexParamVideoBitStreamFormatSelect Index Parameters:",
  "",
  "",
  ""
};

/* Entry to set params of OMX_TI_IndexParamVideoEncoderPreset index*/
PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryH264VencIndexParamVideoEncoderPresetConfig =
{
  "OMX_TI_IndexParamVideoEncoderPreset",
  MX_DBG_CMD_TYPE_CMD_TABLE,
  MX_DBG_CMD_OPT_INST_CUR |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMTB_H264_VENC_CONFIG_PARAMS,sEncoderPreset),
  0,
  0,
  0,
  0,
  0,
  &cmdTblIndexParamVideoEncoderPresetConfig,
  XdbgCmdTblFunc,
  "OMX_TI_IndexParamVideoEncoderPreset Index Parameters:",
  "",
  "",
  ""
};

/* Entry to set params of OMX_TI_IndexParamVideoFrameDataContentSettings index*/
PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryH264VencIndexParamVideoFrameDataContentSettingsConfig =
{
  "OMX_TI_IndexParamVideoFrameDataContentSettings",
  MX_DBG_CMD_TYPE_CMD_TABLE,
  MX_DBG_CMD_OPT_INST_CUR |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMTB_H264_VENC_CONFIG_PARAMS,sInputImgFmt),
  0,
  0,
  0,
  0,
  0,
  &cmdTblIndexParamVideoFrameDataContentSettingsConfig,
  XdbgCmdTblFunc,
  "OMX_TI_IndexParamVideoFrameDataContentSettings Index Parameters:",
  "",
  "",
  ""
};

/* Entry to set params of OMX_TI_IndexParamVideoTransformBlockSize index*/
PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryH264VencIndexParamVideoTransformBlockSizeConfig =
{
  "OMX_TI_IndexParamVideoTransformBlockSize",
  MX_DBG_CMD_TYPE_CMD_TABLE,
  MX_DBG_CMD_OPT_INST_CUR |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMTB_H264_VENC_CONFIG_PARAMS,sTransformBlockSize),
  0,
  0,
  0,
  0,
  0,
  &cmdTblIndexParamVideoTransformBlockSizeConfig,
  XdbgCmdTblFunc,
  "OMX_TI_IndexParamVideoTransformBlockSize Index Parameters:",
  "",
  "",
  ""
};

/* Entry to set params of OMX_IndexParamVideoSliceFMO index*/
PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryH264VencIndexParamVideoSliceFMOConfig =
{
  "OMX_IndexParamVideoSliceFMO",
  MX_DBG_CMD_TYPE_CMD_TABLE,
  MX_DBG_CMD_OPT_INST_CUR |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMTB_H264_VENC_CONFIG_PARAMS,sAVCSliceFMO),
  0,
  0,
  0,
  0,
  0,
  &cmdTblIndexParamVideoSliceFMOConfig,
  XdbgCmdTblFunc,
  "OMX_IndexParamVideoSliceFMO Index Parameters:",
  "",
  "",
  ""
};


/* Entry to set params of OMX_IndexParamVideoMotionVector index*/
PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryH264VencIndexParamVideoMotionVectorConfig =
{
  "OMX_IndexParamVideoMotionVector",
  MX_DBG_CMD_TYPE_CMD_TABLE,
  MX_DBG_CMD_OPT_INST_CUR |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMTB_H264_VENC_CONFIG_PARAMS,sMotionVectorType),
  0,
  0,
  0,
  0,
  0,
  &cmdTblIndexParamVideoMotionVectorConfig,
  XdbgCmdTblFunc,
  "OMX_IndexParamVideoMotionVector Index Parameters:",
  "",
  "",
  ""
};


/* Entry to set params of OMX_IndexParamCompBufferSupplier index*/
PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryH264VencIndexParamCompBufferSupplierConfig =
{
  "OMX_IndexParamCompBufferSupplier",
  MX_DBG_CMD_TYPE_CMD_TABLE,
  MX_DBG_CMD_OPT_INST_CUR |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMTB_H264_VENC_CONFIG_PARAMS,sBufSupplier),
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
PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryH264VencIndexParamBuffMemTypeConfig =
{
  "OMX_TI_IndexParamBuffMemType",
  MX_DBG_CMD_TYPE_CMD_TABLE,
  MX_DBG_CMD_OPT_INST_CUR |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMTB_H264_VENC_CONFIG_PARAMS,sMemTypeCfg),
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
PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryH264VencIndexParamVideoInitConfig =
{
  "OMX_IndexParamVideoInit",
  MX_DBG_CMD_TYPE_CMD_TABLE,
  MX_DBG_CMD_OPT_INST_CUR |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMTB_H264_VENC_CONFIG_PARAMS,sPortInit),
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

/* Dynamic configuration params */
/* Entry to set params of OMX_IndexConfigVideoFramerate index*/
PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryH264VencIndexConfigVideoFramerateConfig =
{
  "OMX_IndexConfigVideoFramerate",
  MX_DBG_CMD_TYPE_CMD_TABLE,
  MX_DBG_CMD_OPT_INST_CUR |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMTB_H264_VENC_CONFIG_PARAMS,sFrameRate),
  0,
  0,
  0,
  0,
  0,
  &cmdTblIndexConfigVideoFramerateConfig,
  XdbgCmdTblFunc,
  "OMX_IndexConfigVideoFramerate Index Parameters:",
  "",
  "",
  ""
};

/* Entry to set params of OMX_IndexConfigVideoBitrate index*/
PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryH264VencIndexConfigVideoBitrateConfig =
{
  "OMX_IndexConfigVideoBitrate",
  MX_DBG_CMD_TYPE_CMD_TABLE,
  MX_DBG_CMD_OPT_INST_CUR |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMTB_H264_VENC_CONFIG_PARAMS,sConfigBitRate),
  0,
  0,
  0,
  0,
  0,
  &cmdTblIndexConfigVideoBitrateConfig,
  XdbgCmdTblFunc,
  "OMX_IndexConfigVideoBitrate Index Parameters:",
  "",
  "",
  ""
};

/* Entry to set params of OMX_TI_IndexConfigVideoMESearchRange index*/
PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryH264VencIndexConfigVideoMESearchRangeConfig =
{
  "OMX_TI_IndexConfigVideoMESearchRange",
  MX_DBG_CMD_TYPE_CMD_TABLE,
  MX_DBG_CMD_OPT_INST_CUR |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMTB_H264_VENC_CONFIG_PARAMS,sMESearchrange),
  0,
  0,
  0,
  0,
  0,
  &cmdTblIndexConfigVideoMESearchRangeConfig,
  XdbgCmdTblFunc,
  "OMX_TI_IndexConfigVideoMESearchRange Index Parameters:",
  "",
  "",
  ""
};

/* Entry to set params of OMX_IndexConfigVideoIntraVOPRefresh index*/
PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryH264VencIndexConfigVideoIntraVOPRefreshConfig =
{
  "OMX_IndexConfigVideoIntraVOPRefresh",
  MX_DBG_CMD_TYPE_CMD_TABLE,
  MX_DBG_CMD_OPT_INST_CUR |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMTB_H264_VENC_CONFIG_PARAMS,sForceFrame),
  0,
  0,
  0,
  0,
  0,
  &cmdTblIndexConfigVideoIntraVOPRefreshConfig,
  XdbgCmdTblFunc,
  "OMX_IndexConfigVideoIntraVOPRefresh Index Parameters:",
  "",
  "",
  ""
};

/* Entry to set params of OMX_TI_IndexConfigVideoQPSettings index*/
PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryH264VencIndexConfigVideoQPSettingsConfig =
{
  "OMX_TI_IndexConfigVideoQPSettings",
  MX_DBG_CMD_TYPE_CMD_TABLE,
  MX_DBG_CMD_OPT_INST_CUR |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMTB_H264_VENC_CONFIG_PARAMS,sQPSettings),
  0,
  0,
  0,
  0,
  0,
  &cmdTblIndexConfigVideoQPSettingsConfig,
  XdbgCmdTblFunc,
  "OMX_TI_IndexConfigVideoQPSettings Index Parameters:",
  "",
  "",
  ""
};

/* Entry to set params of OMX_IndexConfigVideoAVCIntraPeriod index*/
PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryH264VencIndexConfigVideoAVCIntraPeriodConfig =
{
  "OMX_IndexConfigVideoAVCIntraPeriod",
  MX_DBG_CMD_TYPE_CMD_TABLE,
  MX_DBG_CMD_OPT_INST_CUR |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMTB_H264_VENC_CONFIG_PARAMS,sAVCIntraPeriod),
  0,
  0,
  0,
  0,
  0,
  &cmdTblIndexConfigVideoAVCIntraPeriodConfig,
  XdbgCmdTblFunc,
  "OMX_IndexConfigVideoAVCIntraPeriod Index Parameters:",
  "",
  "",
  ""
};


/* Entry to set params of OMX_TI_IndexConfigSliceSettings index*/
PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryH264VencIndexConfigSliceSettingsConfig =
{
  "OMX_TI_IndexConfigSliceSettings",
  MX_DBG_CMD_TYPE_CMD_TABLE,
  MX_DBG_CMD_OPT_INST_CUR |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMTB_H264_VENC_CONFIG_PARAMS,sSliceSettings),
  0,
  0,
  0,
  0,
  0,
  &cmdTblIndexConfigSliceSettingsConfig,
  XdbgCmdTblFunc,
  "OMX_TI_IndexConfigSliceSettings Index Parameters:",
  "",
  "",
  ""
};

/* Entry to set params of OMX_TI_IndexConfigVideoPixelInfo index*/
PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryH264VencIndexConfigVideoPixelInfoConfig =
{
  "OMX_TI_IndexConfigVideoPixelInfo",
  MX_DBG_CMD_TYPE_CMD_TABLE,
  MX_DBG_CMD_OPT_INST_CUR |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMTB_H264_VENC_CONFIG_PARAMS,sPixelInfo),
  0,
  0,
  0,
  0,
  0,
  &cmdTblIndexConfigVideoPixelInfoConfig,
  XdbgCmdTblFunc,
  "OMX_TI_IndexConfigVideoPixelInfo Index Parameters:",
  "",
  "",
  ""
};

/* Advanced configuration params */
/* Entry to set params of OMX_TI_IndexParamVideoNALUsettings index*/
PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryH264VencIndexParamVideoNALUsettingsConfig =
{
  "OMX_TI_IndexParamVideoNALUsettings",
  MX_DBG_CMD_TYPE_CMD_TABLE,
  MX_DBG_CMD_OPT_INST_CUR |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMTB_H264_VENC_CONFIG_PARAMS,sNALUSettings),
  0,
  0,
  0,
  0,
  0,
  &cmdTblIndexParamVideoNALUsettingsConfig,
  XdbgCmdTblFunc,
  "OMX_TI_IndexParamVideoNALUsettings Index Parameters:",
  "",
  "",
  ""
};

/* Entry to set params of OMX_TI_IndexParamVideoAdvancedFMO index*/
PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryH264VencIndexParamVideoAdvancedFMOConfig =
{
  "OMX_TI_IndexParamVideoAdvancedFMO",
  MX_DBG_CMD_TYPE_CMD_TABLE,
  MX_DBG_CMD_OPT_INST_CUR |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMTB_H264_VENC_CONFIG_PARAMS,sAVCAdvancedFMO),
  0,
  0,
  0,
  0,
  0,
  &cmdTblIndexParamVideoAdvancedFMOConfig,
  XdbgCmdTblFunc,
  "OMX_TI_IndexParamVideoAdvancedFMO Index Parameters:",
  "",
  "",
  ""
};

	
/* Entry to set params of OMX_TI_IndexParamVideoMEBlockSize index*/
PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryH264VencIndexParamVideoMEBlockSizeConfig =
{
  "OMX_TI_IndexParamVideoMEBlockSize",
  MX_DBG_CMD_TYPE_CMD_TABLE,
  MX_DBG_CMD_OPT_INST_CUR |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMTB_H264_VENC_CONFIG_PARAMS,sMEBlockSize),
  0,
  0,
  0,
  0,
  0,
  &cmdTblIndexParamVideoMEBlockSizeConfig,
  XdbgCmdTblFunc,
  "OMX_TI_IndexParamVideoMEBlockSize Index Parameters:",
  "",
  "",
  ""
};

/* Entry to set params of OMX_IndexParamVideoIntraRefresh index*/
PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryH264VencIndexParamVideoIntraRefreshConfig =
{
  "OMX_IndexParamVideoIntraRefresh",
  MX_DBG_CMD_TYPE_CMD_TABLE,
  MX_DBG_CMD_OPT_INST_CUR |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMTB_H264_VENC_CONFIG_PARAMS,sIntraRefresh),
  0,
  0,
  0,
  0,
  0,
  &cmdTblIndexParamVideoIntraRefreshConfig,
  XdbgCmdTblFunc,
  "OMX_IndexParamVideoIntraRefresh Index Parameters:",
  "",
  "",
  ""
};

	
/* Entry to set params of OMX_TI_IndexParamVideoVUIsettings index*/
PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryH264VencIndexParamVideoVUIsettingsConfig =
{
  "OMX_TI_IndexParamVideoVUIsettings",
  MX_DBG_CMD_TYPE_CMD_TABLE,
  MX_DBG_CMD_OPT_INST_CUR |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMTB_H264_VENC_CONFIG_PARAMS,sVUISettings),
  0,
  0,
  0,
  0,
  0,
  &cmdTblIndexParamVideoVUIsettingsConfig,
  XdbgCmdTblFunc,
  "OMX_TI_IndexParamVideoVUIsettings Index Parameters:",
  "",
  "",
  ""
};

/* Entry to set params of OMX_TI_IndexParamVideoIntraPredictionSettings index*/
PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryH264VencIndexParamVideoIntraPredictionSettingsConfig =
{
  "OMX_TI_IndexParamVideoIntraPredictionSettings",
  MX_DBG_CMD_TYPE_CMD_TABLE,
  MX_DBG_CMD_OPT_INST_CUR |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMTB_H264_VENC_CONFIG_PARAMS,sIntraPred),
  0,
  0,
  0,
  0,
  0,
  &cmdTblIndexParamVideoIntraPredictionSettingsConfig,
  XdbgCmdTblFunc,
  "OMX_TI_IndexParamVideoIntraPredictionSettings Index Parameters:",
  "",
  "",
  ""
};

/* Entry to set params of OMX_TI_IndexParamVideoDataSyncMode index*/
PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryH264VencIndexParamVideoDataSyncModeConfig =
{
  "OMX_TI_IndexParamVideoDataSyncMode",
  MX_DBG_CMD_TYPE_CMD_TABLE,
  MX_DBG_CMD_OPT_INST_CUR |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMTB_H264_VENC_CONFIG_PARAMS,sVidDataMode),
  0,
  0,
  0,
  0,
  0,
  &cmdTblIndexParamVideoDataSyncModeConfig,
  XdbgCmdTblFunc,
  "OMX_TI_IndexParamVideoDataSyncMode Index Parameters:",
  "",
  "",
  ""
};
	

/* Entry to set params of OMX_IndexConfigVideoNalSize index*/
PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryH264VencIndexConfigVideoNalSizeConfig =
{
  "OMX_IndexConfigVideoNalSize",
  MX_DBG_CMD_TYPE_CMD_TABLE,
  MX_DBG_CMD_OPT_INST_CUR |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMTB_H264_VENC_CONFIG_PARAMS,sNalSize),
  0,
  0,
  0,
  0,
  0,
  &cmdTblIndexConfigVideoNalSizeConfig,
  XdbgCmdTblFunc,
  "OMX_IndexConfigVideoNalSize Index Parameters:",
  "",
  "",
  ""
};

/* Entry to set params of OMX_IndexParamVideoPortFormat index*/
PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryH264VencIndexParamVideoPortFormatConfig =
{
  "OMX_IndexParamVideoPortFormat",
  MX_DBG_CMD_TYPE_CMD_TABLE,
  MX_DBG_CMD_OPT_INST_CUR |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMTB_H264_VENC_CONFIG_PARAMS,sVideoPortFormat),
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

/* Entry to set params of OMX_IndexParamVideoQuantization index*/
PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryH264VencIndexParamVideoQuantizationConfig =
{
  "OMX_IndexParamVideoQuantization",
  MX_DBG_CMD_TYPE_CMD_TABLE,
  MX_DBG_CMD_OPT_INST_CUR |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMTB_H264_VENC_CONFIG_PARAMS,sQuantType),
  0,
  0,
  0,
  0,
  0,
  &cmdTblIndexParamVideoQuantizationConfig,
  XdbgCmdTblFunc,
  "OMX_IndexParamVideoQuantization Index Parameters:",
  "",
  "",
  ""
};

/* Entry to set params of OMX_TI_IndexParamCompPortNotifyType index*/
PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryH264VencIndexParamCompPortNotifyTypeConfig =
{
  "OMX_TI_IndexParamCompPortNotifyType",
  MX_DBG_CMD_TYPE_CMD_TABLE,
  MX_DBG_CMD_OPT_INST_CUR |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMTB_H264_VENC_CONFIG_PARAMS,sCompPortNotifyType),
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
PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryH264VencIndexParamPortDefinitionConfig =
{
  "OMX_IndexParamPortDefinition",
  MX_DBG_CMD_TYPE_CMD_TABLE,
  MX_DBG_CMD_OPT_INST_CUR |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMTB_H264_VENC_CONFIG_PARAMS,sPortDefType),
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
PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryH264VencIndexConfigChannelNameConfig =
{
  "OMX_TI_IndexConfigChannelName",
  MX_DBG_CMD_TYPE_CMD_TABLE,
  MX_DBG_CMD_OPT_INST_CUR |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMTB_H264_VENC_CONFIG_PARAMS,sChannelName),
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

#ifdef _VIDEO_M3_DYNAMIC_CONFIG
/* Entry to set params of OMX_TI_IndexConfigVideoDynamicParams index*/
PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryH264VencIndexParamVideoDynamicParamsConfig =
{
  "OMX_TI_IndexConfigVideoDynamicParams",
  MX_DBG_CMD_TYPE_CMD_TABLE,
  MX_DBG_CMD_OPT_INST_CUR |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMTB_H264_VENC_CONFIG_PARAMS,sDynamicParams),
  0,
  0,
  0,
  0,
  0,
  &cmdTblIndexParamVideoDynamicParamsConfig,
  XdbgCmdTblFunc,
  "OMX_TI_IndexConfigVideoDynamicParams Index Parameters:",
  "",
  "",
  ""
};
#endif
	
/* h264venc config command table Entry */

MX_DBG_CMD_ENTRY_T* cmdListH264VencConfig[] =
{
  &cmdEntryH264VencCompName,
  &cmdEntryH264VencInFile,
  &cmdEntryH264VencOutFile,
  &cmdEntryH264VencWidth,
  &cmdEntryH264VencHeight,

  &cmdEntryH264VencInputChromaFormat,
  &cmdEntryH264VencOutputMode,
  &cmdEntryH264VencInputMode,
  &cmdEntryH264VencFlagUseAllocInBuffer,
  &cmdEntryH264VencNumInBuf,
  &cmdEntryH264VencInBufAlignment,
  &cmdEntryH264VencInBufContiguous,
  &cmdEntryH264VencInBufSzFlag,
  &cmdEntryH264VencInBufSize,
  &cmdEntryH264VencFlagUseAllocOutBuffer,
  &cmdEntryH264VencNumOutBuf,
  &cmdEntryH264VencOutBufAlignment,
  &cmdEntryH264VencOutBufContiguous,
  &cmdEntryH264VencOutBufSzFlag,
  &cmdEntryH264VencOutBufSize,
  &cmdEntryH264VencOutputCompressionFormat,
  &cmdEntryH264VencStride,
  &cmdEntryH264VencBitrate,
  &cmdEntryH264VencFramerate,
  &cmdEntryH264VencMaxFileSize,
  &cmdEntryH264VencFileResetFlag,
  
  &cmdEntryH264VencIndexConfigVideoFramerateConfig,
  &cmdEntryH264VencIndexConfigVideoBitrateConfig,
  &cmdEntryH264VencIndexConfigVideoMESearchRangeConfig,
  &cmdEntryH264VencIndexConfigVideoIntraVOPRefreshConfig,
  &cmdEntryH264VencIndexConfigVideoQPSettingsConfig,
  &cmdEntryH264VencIndexConfigVideoAVCIntraPeriodConfig,
  &cmdEntryH264VencIndexConfigSliceSettingsConfig,
  &cmdEntryH264VencIndexConfigVideoPixelInfoConfig,
  &cmdEntryH264VencIndexParamVideoNALUsettingsConfig,
  &cmdEntryH264VencIndexParamVideoAdvancedFMOConfig,
  &cmdEntryH264VencIndexParamVideoMEBlockSizeConfig,
  &cmdEntryH264VencIndexParamVideoIntraRefreshConfig,
  &cmdEntryH264VencIndexParamVideoVUIsettingsConfig,
  &cmdEntryH264VencIndexParamVideoIntraPredictionSettingsConfig,
  &cmdEntryH264VencIndexParamVideoDataSyncModeConfig,
  &cmdEntryH264VencIndexConfigVideoNalSizeConfig,
  &cmdEntryH264VencIndexParamVideoAvcConfig,
  &cmdEntryH264VencIndexParamVideoBitrateConfig,
  &cmdEntryH264VencIndexParamVideoProfileLevelCurrentConfig,
  &cmdEntryH264VencIndexParamVideoBitStreamFormatSelectConfig,
  &cmdEntryH264VencIndexParamVideoEncoderPresetConfig,
  &cmdEntryH264VencIndexParamVideoFrameDataContentSettingsConfig,
  &cmdEntryH264VencIndexParamVideoTransformBlockSizeConfig,
  &cmdEntryH264VencIndexParamVideoSliceFMOConfig,
  &cmdEntryH264VencIndexParamVideoMotionVectorConfig,
  &cmdEntryH264VencIndexParamBuffMemTypeConfig,
  &cmdEntryH264VencIndexParamCompBufferSupplierConfig,
  &cmdEntryH264VencIndexParamVideoInitConfig,
  &cmdEntryH264VencIndexParamVideoPortFormatConfig,
  &cmdEntryH264VencIndexParamVideoQuantizationConfig,
  &cmdEntryH264VencIndexParamCompPortNotifyTypeConfig,
  &cmdEntryH264VencIndexParamPortDefinitionConfig,  
  &cmdEntryH264VencIndexConfigChannelNameConfig,
#ifdef _VIDEO_M3_DYNAMIC_CONFIG
  &cmdEntryH264VencIndexParamVideoDynamicParamsConfig,
#endif  
  NULL
};


/* h264venc config command table */

MX_DBG_CMD_TABLE_T cmdTblH264VencConfig =
{
  MX_DBG_ACCESS_ALL,
  sizeof(cmdListH264VencConfig)/sizeof(cmdListH264VencConfig[0]),
  cmdListH264VencConfig
};


/* H264venc config command entry */

MX_DBG_CMD_ENTRY_T cmdEntryH264VencConfig =
{
  OMTB_H264_VENC_COMP_REF_STR,
  MX_DBG_CMD_TYPE_CMD_TABLE,
  MX_DBG_CMD_OPT_INST_CUR |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMTB_TEMPLATE_INFO,h264VencTemplate),
  0,
  0,
  0,
  0,
  0,
  &cmdTblH264VencConfig,
  XdbgCmdTblFunc,
  "\nH264 Video Encoder Config Parameters:\n",
  "",
  "",
  ""
};


/*----------------------------- end of file ---------------------------------*/
