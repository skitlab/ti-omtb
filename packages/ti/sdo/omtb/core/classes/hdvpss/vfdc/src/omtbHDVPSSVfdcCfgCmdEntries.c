/*
 * omtbHDVPSSVfdcCfgCmdEntries.c
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
extern MX_DBG_CMD_TABLE_T cmdTblIndexParamCompBufferSupplierConfig;
extern MX_DBG_CMD_TABLE_T cmdTblIndexParamBuffMemTypeConfig;
extern MX_DBG_CMD_TABLE_T cmdTblIndexParamVideoInitConfig;
extern MX_DBG_CMD_TABLE_T cmdTblIndexParamVFDCDriverInstIdConfig;
extern MX_DBG_CMD_TABLE_T cmdTblIndexParamVFDCCreateMosaicLayoutConfig;
extern MX_DBG_CMD_TABLE_T cmdTblIndexConfigVFDCMosaicPort2WinMapConfig;
extern MX_DBG_CMD_TABLE_T cmdTblIndexParamPortDefinitionConfig;
extern MX_DBG_CMD_TABLE_T cmdTblIndexParamVFDCCustomModeInfoConfig;

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
 *  OMTB component configuration parameter command entries - VFDC
 ******************************************************************************/

/*******************************************************************************
 *      VFDC config params
 ******************************************************************************/

/* Entry for Set OMX Component Name */

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryVPSSVfdcCompName =
{
  "compname",
  MX_DBG_CMD_TYPE_VAR_STR_BUF,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMTB_VPSS_VFDC_CONFIG_PARAMS,sBasicParams.compName),
  FIELDOFFSET(OMTB_VPSS_VFDC_CONFIG_PARAMS,sBasicParams.inputFile) -
  FIELDOFFSET(OMTB_VPSS_VFDC_CONFIG_PARAMS,sBasicParams.compName),
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

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryVPSSVfdcInFile =
{
  "infile",
  MX_DBG_CMD_TYPE_VAR_STR_BUF,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMTB_VPSS_VFDC_CONFIG_PARAMS,sBasicParams.inputFile),
  FIELDOFFSET(OMTB_VPSS_VFDC_CONFIG_PARAMS,sBasicParams.inputFile) -
  FIELDOFFSET(OMTB_VPSS_VFDC_CONFIG_PARAMS,sBasicParams.inputFile),
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

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryVPSSVfdcOutFile =
{
  "outfile",
  MX_DBG_CMD_TYPE_VAR_STR_BUF,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMTB_VPSS_VFDC_CONFIG_PARAMS,sBasicParams.outputFile),
  FIELDOFFSET(OMTB_VPSS_VFDC_CONFIG_PARAMS,sBasicParams.inputFile) -
  FIELDOFFSET(OMTB_VPSS_VFDC_CONFIG_PARAMS,sBasicParams.outputFile),
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

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryVPSSVfdcWidth =
{
  "frame_width",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_DEC      |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMTB_VPSS_VFDC_CONFIG_PARAMS,sBasicParams.frameWidth),
  FIELDOFFSET(OMTB_VPSS_VFDC_CONFIG_PARAMS,sBasicParams.inputFile) -
  FIELDOFFSET(OMTB_VPSS_VFDC_CONFIG_PARAMS,sBasicParams.frameWidth),
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

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryVPSSVfdcHeight =
{
  "frame_height",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_DEC          |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMTB_VPSS_VFDC_CONFIG_PARAMS,sBasicParams.frameHeight),
  FIELDOFFSET(OMTB_VPSS_VFDC_CONFIG_PARAMS,sBasicParams.inputFile) -
  FIELDOFFSET(OMTB_VPSS_VFDC_CONFIG_PARAMS,sBasicParams.frameHeight),
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

PRIVATE MX_DBG_ENUM_ENTRY_T enumTblVPSSVfdcInputChromaFormat[] =
{
  {"420P",OMX_COLOR_FormatYUV420Planar, ""},
  {"420SP",OMX_COLOR_FormatYUV420SemiPlanar, ""},
  {"422P",OMX_COLOR_FormatYUV422Planar, ""},
  {"422YUYV", OMX_COLOR_FormatYCbYCr, ""},
  {"", 0, ""}
};


/* Entry for Set O/P Color Format */

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryVPSSVfdcInputChromaFormat =
{
  "ip_chromat_format",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_ENUM          |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMTB_VPSS_VFDC_CONFIG_PARAMS,sBasicParams.inColorFormat),
  FIELDOFFSET(OMTB_VPSS_VFDC_CONFIG_PARAMS,sBasicParams.inputFile) -
  FIELDOFFSET(OMTB_VPSS_VFDC_CONFIG_PARAMS,sBasicParams.inColorFormat),
  0,
  OMX_COLOR_FormatYUV420Planar,
  OMX_COLOR_FormatYCbYCr,
  OMX_COLOR_FormatYUV422Planar,
  &enumTblVPSSVfdcInputChromaFormat,
  XdbgCmdVarFunc,
  "I/P Chroma Format.............................",
  "",
  "",
  ""
};


/* Enum Entry for Selecting Data O/P Mode */

PRIVATE MX_DBG_ENUM_ENTRY_T enumTblDataMode[] =
{
  {"file",  OMTB_FILE,    ""},
  {"driver",OMTB_DRIVER,  ""},
  {"none",  OMTB_NONE,    ""},
  {"",      0,            ""}
};


/* Entry for Setting Data Output Mode */

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryVPSSVfdcInputMode =
{
  "data_ipmode",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_ENUM          |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMTB_VPSS_VFDC_CONFIG_PARAMS,sBasicParams.dataInPutMode),
  FIELDOFFSET(OMTB_VPSS_VFDC_CONFIG_PARAMS,sBasicParams.inputFile) -
  FIELDOFFSET(OMTB_VPSS_VFDC_CONFIG_PARAMS,sBasicParams.dataInPutMode),
  0,
  OMTB_FILE,
  OMTB_NONE,
  OMTB_FILE,
  &enumTblDataMode,
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


/* Entry for Setting Use/Allocate input buffer */

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryVPSSVfdcFlagUseAllocInBuffer =
{
  "inbuf",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_ENUM          |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMTB_VPSS_VFDC_CONFIG_PARAMS,sBasicParams.flagUseInBuffer),
  FIELDOFFSET(OMTB_VPSS_VFDC_CONFIG_PARAMS,sBasicParams.inputFile) -
  FIELDOFFSET(OMTB_VPSS_VFDC_CONFIG_PARAMS,sBasicParams.flagUseInBuffer),
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

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryVPSSVfdcNumInBuf =
{
  "numinbuf",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_DEC      |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMTB_VPSS_VFDC_CONFIG_PARAMS,sBasicParams.numInBuf),
  FIELDOFFSET(OMTB_VPSS_VFDC_CONFIG_PARAMS,sBasicParams.inputFile) -
  FIELDOFFSET(OMTB_VPSS_VFDC_CONFIG_PARAMS,sBasicParams.numInBuf),
  0,
  0,
  OMTB_VPSS_VFDC_MAX_NUM_IN_BUFS,
  OMTB_VPSS_VFDC_MAX_NUM_IN_BUFS,
  NULL,
  XdbgCmdVarFunc,
  "Number of i/p buffer..........................",
  "<# of input buffers>",
  "",
  ""
};

/* Entry for Set i/p buffer size */

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryVPSSVfdcInBufSize =
{
  "inbufsize",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_DEC          |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMTB_VPSS_VFDC_CONFIG_PARAMS,sBasicParams.inBufSize),
  FIELDOFFSET(OMTB_VPSS_VFDC_CONFIG_PARAMS,sBasicParams.inputFile) -
  FIELDOFFSET(OMTB_VPSS_VFDC_CONFIG_PARAMS,sBasicParams.inBufSize),
  0,
  0,
  OMTB_MAX_VAL_U32,
  OMTB_VPSS_VFDC_MAX_INBUFF_SIZE,
  NULL,
  XdbgCmdVarFunc,
  "I/p buffer size...............................",
  "<input buffer size>",
  "",
  ""
};

/* Entry for Set i/p buffer alignment */

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryVPSSVfdcInBufAlignment =
{
  "inbufalign",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_DEC          |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMTB_VPSS_VFDC_CONFIG_PARAMS,sBasicParams.inBufAlignment),
  FIELDOFFSET(OMTB_VPSS_VFDC_CONFIG_PARAMS,sBasicParams.inputFile) -
  FIELDOFFSET(OMTB_VPSS_VFDC_CONFIG_PARAMS,sBasicParams.inBufAlignment),
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

/* Enum Entry for enabling or disabling flag */

PRIVATE MX_DBG_ENUM_ENTRY_T enumTblVPSSVfdcOnOff[] =
{
  {"enable",  OMX_TRUE,   ""},
  {"disable", OMX_FALSE,  ""},
  {"",        0,          ""}
};


/* Entry for Set i/p buffer size */

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryVPSSVfdcInBufSzFlag =
{
  "inbufsize_flag",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_ENUM         |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMTB_VPSS_VFDC_CONFIG_PARAMS,sBasicParams.inBufSzFlag),
  FIELDOFFSET(OMTB_VPSS_VFDC_CONFIG_PARAMS,sBasicParams.inputFile) -
  FIELDOFFSET(OMTB_VPSS_VFDC_CONFIG_PARAMS,sBasicParams.inBufSzFlag),
  0,
  OMX_FALSE,
  OMX_TRUE,
  OMX_FALSE,
  &enumTblVPSSVfdcOnOff,
  XdbgCmdVarFunc,
  "I/P buffer size input from user...............",
  "",
  "",
  ""
};

/* Entry for Set i/p buffer continuous memory allocation */

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryVPSSVfdcInBufContiguous =
{
  "inbuf_contig",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_ENUM         |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMTB_VPSS_VFDC_CONFIG_PARAMS,sBasicParams.inBufContiguous),
  FIELDOFFSET(OMTB_VPSS_VFDC_CONFIG_PARAMS,sBasicParams.inputFile) -
  FIELDOFFSET(OMTB_VPSS_VFDC_CONFIG_PARAMS,sBasicParams.inBufContiguous),
  0,
  OMX_FALSE,
  OMX_TRUE,
  OMX_FALSE,
  &enumTblVPSSVfdcOnOff,
  XdbgCmdVarFunc,
  "Contiguous i/p buffer memory..................",
  "",
  "",
  ""
};


/* Entry for Set graphics flag */

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryVPSSVfdcGraphicsFlag =
{
  "graphics_flag",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_ENUM         |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMTB_VPSS_VFDC_CONFIG_PARAMS,sBasicParams.graphicsFlag),
  FIELDOFFSET(OMTB_VPSS_VFDC_CONFIG_PARAMS,sBasicParams.inputFile) -
  FIELDOFFSET(OMTB_VPSS_VFDC_CONFIG_PARAMS,sBasicParams.graphicsFlag),
  0,
  OMX_FALSE,
  OMX_TRUE,
  OMX_FALSE,
  &enumTblVPSSVfdcOnOff,
  XdbgCmdVarFunc,
  "Graphics Flag.................................",
  "",
  "",
  ""
};

/* Entry for Set File reset flag */

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryVPSSVfdcFileResetFlag =
{
  "filereset_flag",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_ENUM         |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMTB_VPSS_VFDC_CONFIG_PARAMS,sBasicParams.fileReset),
  FIELDOFFSET(OMTB_VPSS_VFDC_CONFIG_PARAMS,sBasicParams.inputFile) -
  FIELDOFFSET(OMTB_VPSS_VFDC_CONFIG_PARAMS,sBasicParams.fileReset),
  0,
  OMX_FALSE,
  OMX_TRUE,
  OMX_FALSE,
  &enumTblVPSSVfdcOnOff,
  XdbgCmdVarFunc,
  "File Reset Flag...............................",
  "",
  "",
  ""
};


/*Entry for Setting Mosaic Display Window Width*/

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryVPSSVfdcMosaicDispWindowWidth =
{
  "mosaicDispWindowWidth",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_DEC      |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMTB_VPSS_VFDC_CONFIG_PARAMS,sMosaicParams.dispWindowWidth),
  FIELDOFFSET(OMTB_VPSS_VFDC_CONFIG_PARAMS,sBasicParams.inputFile) -
  FIELDOFFSET(OMTB_VPSS_VFDC_CONFIG_PARAMS,sMosaicParams.dispWindowWidth),
  0,
  0,
  1920,
  1920,
  NULL,
  XdbgCmdVarFunc,
  "VFDC Mosaic Display Window Width..............",
  "<Mosaic Display Window Width>",
  "",
  ""
};

/*Entry for Setting Mosaic Display Window Height*/

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryVPSSVfdcMosaicDispWindowHeight =
{
  "mosaicDispWindowHeight",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_DEC      |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMTB_VPSS_VFDC_CONFIG_PARAMS,sMosaicParams.dispWindowHeight),
  FIELDOFFSET(OMTB_VPSS_VFDC_CONFIG_PARAMS,sBasicParams.inputFile) -
  FIELDOFFSET(OMTB_VPSS_VFDC_CONFIG_PARAMS,sMosaicParams.dispWindowHeight),
  0,
  0,
  1080,
  1080,
  NULL,
  XdbgCmdVarFunc,
  "VFDC Mosaic Display Window Height.............",
  "<Mosaic Display Window Height>",
  "",
  ""
};

/*Entry for Setting Mosaic Num Rows */

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryVPSSVfdcMosaicNumRows =
{
  "mosaicNumRows",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_DEC      |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMTB_VPSS_VFDC_CONFIG_PARAMS,sMosaicParams.numRows),
  FIELDOFFSET(OMTB_VPSS_VFDC_CONFIG_PARAMS,sBasicParams.inputFile) -
  FIELDOFFSET(OMTB_VPSS_VFDC_CONFIG_PARAMS,sMosaicParams.numRows),
  0,
  0,
  OMTB_MAX_VAL_U32,
  3,
  NULL,
  XdbgCmdVarFunc,
  "VFDC Mosaic Num Rows..........................",
  "<Mosaic Num Rows>",
  "",
  ""
};

/*Entry for Setting Mosaic Num Cols */

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryVPSSVfdcMosaicNumCols =
{
  "mosaicNumCols",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_DEC      |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMTB_VPSS_VFDC_CONFIG_PARAMS,sMosaicParams.numCols),
  FIELDOFFSET(OMTB_VPSS_VFDC_CONFIG_PARAMS,sBasicParams.inputFile) -
  FIELDOFFSET(OMTB_VPSS_VFDC_CONFIG_PARAMS,sMosaicParams.numCols),
  0,
  0,
  OMTB_MAX_VAL_U32,
  4,
  NULL,
  XdbgCmdVarFunc,
  "VFDC Mosaic Num Cols..........................",
  "<Mosaic Num Cols>",
  "",
  ""
};

/* Entry for priority of the mosaic window id */

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryVPSSVfdcMosaicWindowId =
{
  "mosaic_window_id",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_DEC          |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMTB_VPSS_VFDC_CONFIG_PARAMS,sMosaicParams.windowId),
  FIELDOFFSET(OMTB_VPSS_VFDC_CONFIG_PARAMS,sBasicParams.inputFile) -
  FIELDOFFSET(OMTB_VPSS_VFDC_CONFIG_PARAMS,sMosaicParams.windowId),
  0,
  0,
  OMTB_MAX_VAL_U32,
  0,
  NULL,
  XdbgCmdVarFunc,
  "Mosaic Window Id...............................",
  "",
  "",
  ""
};

/* Enum Entry for Supported mosaic window config */
PRIVATE MX_DBG_ENUM_ENTRY_T enumTblVPSSVfdcMosaicWindowConfig[] =
{
  {"vc",     OMTB_VC_DEMO,	 ""},
  {"vs",     OMTB_VS_DEMO,   ""},
  {"manual", OMTB_MANUAL,    ""},
  {"",        0,             ""}
};

/* Entry for Set mosaic window configuration */
PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryVPSSVfdcMosaicWindowConfig =
{
  "mosaic_window_config",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_ENUM         |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMTB_VPSS_VFDC_CONFIG_PARAMS,mosaicDemoConfig),
  FIELDOFFSET(OMTB_VPSS_VFDC_CONFIG_PARAMS,sBasicParams.inputFile) -
  FIELDOFFSET(OMTB_VPSS_VFDC_CONFIG_PARAMS,mosaicDemoConfig),
  0,
  OMTB_VC_DEMO,
  OMTB_MANUAL,
  OMTB_MANUAL,
  &enumTblVPSSVfdcMosaicWindowConfig,
  XdbgCmdVarFunc,
  "Select the Mosaic Window Config...............",
  "",
  "",
  ""
};


/* Entry to set params of OMX_IndexParamVideoInit index*/
PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryVPSSVfdcIndexParamVideoInitConfig =
{
  "OMX_IndexParamVideoInit",
  MX_DBG_CMD_TYPE_CMD_TABLE,
  MX_DBG_CMD_OPT_INST_CUR |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMTB_VPSS_VFDC_CONFIG_PARAMS,sPortInit),
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

/* Entry to set params of OMX_IndexParamCompBufferSupplier index*/
PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryVPSSVfdcIndexParamCompBufferSupplierConfig =
{
  "OMX_IndexParamCompBufferSupplier",
  MX_DBG_CMD_TYPE_CMD_TABLE,
  MX_DBG_CMD_OPT_INST_CUR |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMTB_VPSS_VFDC_CONFIG_PARAMS,sBufSupplier),
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
PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryVPSSVfdcIndexParamBuffMemTypeConfig =
{
  "OMX_TI_IndexParamBuffMemType",
  MX_DBG_CMD_TYPE_CMD_TABLE,
  MX_DBG_CMD_OPT_INST_CUR |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMTB_VPSS_VFDC_CONFIG_PARAMS,sMemTypeCfg),
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

/* Entry to set params of OMX_TI_IndexParamVFDCDriverInstId index*/
PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryVPSSVfdcIndexParamVFDCDriverInstIdConfig =
{
  "OMX_TI_IndexParamVFDCDriverInstId",
  MX_DBG_CMD_TYPE_CMD_TABLE,
  MX_DBG_CMD_OPT_INST_CUR |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMTB_VPSS_VFDC_CONFIG_PARAMS,sDvrInstId),
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

/* Entry to set params of OMX_TI_IndexParamVFDCCreateMosaicLayout index*/
PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryVPSSVfdcIndexParamVFDCCreateMosaicLayoutConfig =
{
  "OMX_TI_IndexParamVFDCCreateMosaicLayout",
  MX_DBG_CMD_TYPE_CMD_TABLE,
  MX_DBG_CMD_OPT_INST_CUR |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMTB_VPSS_VFDC_CONFIG_PARAMS,sMosaicParams),
  0,
  0,
  0,
  0,
  0,
  &cmdTblIndexParamVFDCCreateMosaicLayoutConfig,
  XdbgCmdTblFunc,
  "OMX_TI_IndexParamVFDCCreateMosaicLayout Index Parameters:",
  "",
  "",
  ""
};

/* Entry to set params of OMX_TI_IndexConfigVFDCMosaicPort2WinMap index*/
PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryVPSSVfdcIndexConfigVFDCMosaicPort2WinMapConfig =
{
  "OMX_TI_IndexConfigVFDCMosaicPort2WinMap",
  MX_DBG_CMD_TYPE_CMD_TABLE,
  MX_DBG_CMD_OPT_INST_CUR |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMTB_VPSS_VFDC_CONFIG_PARAMS,sLayoutIndex),
  0,
  0,
  0,
  0,
  0,
  &cmdTblIndexConfigVFDCMosaicPort2WinMapConfig,
  XdbgCmdTblFunc,
  "OMX_TI_IndexConfigVFDCMosaicPort2WinMap Index Parameters:",
  "",
  "",
  ""
};

/* Entry to set params of OMX_IndexParamPortDefinition index*/
PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryVPSSVfdcIndexParamPortDefinitionConfig =
{
  "OMX_IndexParamPortDefinition",
  MX_DBG_CMD_TYPE_CMD_TABLE,
  MX_DBG_CMD_OPT_INST_CUR |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMTB_VPSS_VFDC_CONFIG_PARAMS,sPortDefType),
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

/* Entry to set params of OMX_TI_IndexParamVFDCCustomModeInfo index*/
PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryVPSSVfdcIndexParamVFDCCustomModeInfoConfig =
{
  "OMX_TI_IndexParamVFDCCustomModeInfo",
  MX_DBG_CMD_TYPE_CMD_TABLE,
  MX_DBG_CMD_OPT_INST_CUR |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMTB_VPSS_VFDC_CONFIG_PARAMS,sPortDefType),
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

/* VPSS VFDC config command table Entry */

MX_DBG_CMD_ENTRY_T* cmdListVPSSVfdcConfig[] =
{
  &cmdEntryVPSSVfdcCompName,
  &cmdEntryVPSSVfdcInFile,
  &cmdEntryVPSSVfdcOutFile,
  &cmdEntryVPSSVfdcWidth,
  &cmdEntryVPSSVfdcHeight,
  &cmdEntryVPSSVfdcInputChromaFormat,
  &cmdEntryVPSSVfdcInputMode,
  &cmdEntryVPSSVfdcFlagUseAllocInBuffer,
  &cmdEntryVPSSVfdcNumInBuf,
  &cmdEntryVPSSVfdcInBufAlignment,
  &cmdEntryVPSSVfdcInBufContiguous,
  &cmdEntryVPSSVfdcInBufSzFlag,
  &cmdEntryVPSSVfdcInBufSize,
  &cmdEntryVPSSVfdcGraphicsFlag,
  &cmdEntryVPSSVfdcFileResetFlag,
  &cmdEntryVPSSVfdcMosaicWindowConfig,
  &cmdEntryVPSSVfdcMosaicDispWindowWidth,
  &cmdEntryVPSSVfdcMosaicDispWindowHeight,
  &cmdEntryVPSSVfdcMosaicNumRows,
  &cmdEntryVPSSVfdcMosaicNumCols,
  &cmdEntryVPSSVfdcMosaicWindowId,
  
  &cmdEntryVPSSVfdcIndexParamVideoInitConfig,
  &cmdEntryVPSSVfdcIndexParamCompBufferSupplierConfig,
  &cmdEntryVPSSVfdcIndexParamBuffMemTypeConfig,
  &cmdEntryVPSSVfdcIndexParamVFDCDriverInstIdConfig,
  &cmdEntryVPSSVfdcIndexParamVFDCCreateMosaicLayoutConfig,
  &cmdEntryVPSSVfdcIndexConfigVFDCMosaicPort2WinMapConfig,
  &cmdEntryVPSSVfdcIndexParamPortDefinitionConfig,  
  &cmdEntryVPSSVfdcIndexParamVFDCCustomModeInfoConfig,
  NULL
};


/* VPSS VFDC config command table */

MX_DBG_CMD_TABLE_T cmdTblVPSSVfdcConfig =
{
  MX_DBG_ACCESS_ALL,
  sizeof(cmdListVPSSVfdcConfig)/sizeof(cmdListVPSSVfdcConfig[0]),
  cmdListVPSSVfdcConfig
};


/* VPSS VFDC config command entry */

MX_DBG_CMD_ENTRY_T cmdEntryVPSSVfdcConfig =
{
  OMTB_VPSS_VFDC_COMP_REF_STR,
  MX_DBG_CMD_TYPE_CMD_TABLE,
  MX_DBG_CMD_OPT_INST_CUR |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMTB_TEMPLATE_INFO,vpssVfdcTemplate),
  0,
  0,
  0,
  0,
  0,
  &cmdTblVPSSVfdcConfig,
  XdbgCmdTblFunc,
  "\nVPSS VFDC Config Parameters:\n",
  "",
  "",
  ""
};
/*----------------------------- end of file ---------------------------------*/
