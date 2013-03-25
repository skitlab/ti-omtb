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
#include "omx_vfcc.h"
#include "omtbApi.h"

/******************************************************************************\
 *      Customized Includes
\******************************************************************************/

#include "mxDbg.h"
#include "omtbCommon.h"

/*
 * >>> OMX_PARAM_BUFFERSUPPLIERTYPE, OMX_IndexParamCompBufferSupplier
 */
/* Enum Entry for Supported Buffer Supplier Type */
PRIVATE MX_DBG_ENUM_ENTRY_T enumTblBufSupplierType[] =
{
  {"unspecified", OMX_BufferSupplyUnspecified ,  ""},
  {"input",       OMX_BufferSupplyInput,         ""},
  {"output",      OMX_BufferSupplyOutput,        ""},
  {"",            0,                             ""}
};

/* Entry for set Buffer Suppier Type*/
PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryBufSupplierType =
{
  "eBufferSupplier",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_ENUM         |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMX_PARAM_BUFFERSUPPLIERTYPE,eBufferSupplier),
  FIELDOFFSET(OMX_PARAM_BUFFERSUPPLIERTYPE,nSize) -
  FIELDOFFSET(OMX_PARAM_BUFFERSUPPLIERTYPE,eBufferSupplier),
  0,
  OMX_BufferSupplyUnspecified,
  OMX_BufferSupplyOutput,
  OMX_BufferSupplyUnspecified,
  &enumTblBufSupplierType,
  XdbgCmdVarFunc,
  "Buffer Supplier Type..........................",
  "",
  "",
  ""
};


MX_DBG_CMD_ENTRY_T* cmdListIndexParamCompBufferSupplierConfig[] =
{
  &cmdEntryBufSupplierType,
  NULL
};
  
MX_DBG_CMD_TABLE_T cmdTblIndexParamCompBufferSupplierConfig =
{
  MX_DBG_ACCESS_ALL,
  sizeof(cmdListIndexParamCompBufferSupplierConfig)/sizeof(cmdListIndexParamCompBufferSupplierConfig[0]),
  cmdListIndexParamCompBufferSupplierConfig
};

/*
 * <<< OMX_PARAM_BUFFERSUPPLIERTYPE
 */

 
/*
 * >>> OMX_PARAM_BUFFER_MEMORYTYPE, OMX_TI_IndexParamBuffMemType
 */
/* Enum Entry for Supported Buffer Memory Type */
PRIVATE MX_DBG_ENUM_ENTRY_T enumTblBufMemoryType[] =
{
  {"default",     OMX_BUFFER_MEMORY_DEFAULT,        ""},
  {"tiled8bit",   OMX_BUFFER_MEMORY_TILED_8BIT,     ""},
  {"tiled16bit",  OMX_BUFFER_MEMORY_TILED_16BIT,    ""},
  {"tiled32bit",  OMX_BUFFER_MEMORY_TILED_32BIT,    ""},
  {"tiledpage",   OMX_BUFFER_MEMORY_TILED_PAGE,     ""},
  {"custom",      OMX_BUFFER_MEMORY_CUSTOM,         ""},
  {"",            0,                                ""}
};

/* Entry for set Buffer Memory Type */
PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryBufMemoryType =
{
  "eBufMemoryType",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_ENUM         |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMX_PARAM_BUFFER_MEMORYTYPE,eBufMemoryType),
  FIELDOFFSET(OMX_PARAM_BUFFER_MEMORYTYPE,nSize) -
  FIELDOFFSET(OMX_PARAM_BUFFER_MEMORYTYPE,eBufMemoryType),
  0,
  OMX_BUFFER_MEMORY_DEFAULT,
  OMX_BUFFER_MEMORY_CUSTOM,
  OMX_BUFFER_MEMORY_DEFAULT,
  &enumTblBufMemoryType,
  XdbgCmdVarFunc,
  "Buffer Memory Type............................",
  "",
  "",
  ""
};

MX_DBG_CMD_ENTRY_T* cmdListIndexParamBuffMemTypeConfig[] =
{
  &cmdEntryBufMemoryType,
  NULL
};
  
MX_DBG_CMD_TABLE_T cmdTblIndexParamBuffMemTypeConfig =
{
  MX_DBG_ACCESS_ALL,
  sizeof(cmdListIndexParamBuffMemTypeConfig)/sizeof(cmdListIndexParamBuffMemTypeConfig[0]),
  cmdListIndexParamBuffMemTypeConfig
};

/*
 * <<< OMX_PARAM_BUFFER_MEMORYTYPE
 */

 
/*
 * >>> OMX_PORT_PARAM_TYPE, OMX_IndexParamVideoInit
 */
/* Entry for set Num Of Ports */
PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryNumOfPorts =
{
  "nPorts",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_DEC          |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMX_PORT_PARAM_TYPE,nPorts),
  FIELDOFFSET(OMX_PORT_PARAM_TYPE,nSize) -
  FIELDOFFSET(OMX_PORT_PARAM_TYPE,nPorts),
  0,
  0,
  OMTB_MAX_VAL_U32,
  0,
  NULL,
  XdbgCmdVarFunc,
  "Number of i/p + o/p Ports ....................",
  "<no of ports>",
  "",
  ""
};

/* Entry for set Start Port Number */
PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryStartPortNumber =
{
  "nStartPortNumber",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_DEC          |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMX_PORT_PARAM_TYPE,nStartPortNumber),
  FIELDOFFSET(OMX_PORT_PARAM_TYPE,nSize) -
  FIELDOFFSET(OMX_PORT_PARAM_TYPE,nStartPortNumber),
  0,
  0,
  OMTB_MAX_VAL_U32,
  0,
  NULL,
  XdbgCmdVarFunc,
  "Start Port Number ............................",
  "<start port number>",
  "",
  ""
};

MX_DBG_CMD_ENTRY_T* cmdListIndexParamVideoInitConfig[] =
{
  &cmdEntryNumOfPorts,
  &cmdEntryStartPortNumber,
  NULL
};
  
MX_DBG_CMD_TABLE_T cmdTblIndexParamVideoInitConfig =
{
  MX_DBG_ACCESS_ALL,
  sizeof(cmdListIndexParamVideoInitConfig)/sizeof(cmdListIndexParamVideoInitConfig[0]),
  cmdListIndexParamVideoInitConfig
};


MX_DBG_CMD_ENTRY_T* cmdListIndexParamAudioInitConfig[] =
{
  &cmdEntryNumOfPorts,
  &cmdEntryStartPortNumber,
  NULL
};
  
MX_DBG_CMD_TABLE_T cmdTblIndexParamAudioInitConfig =
{
  MX_DBG_ACCESS_ALL,
  sizeof(cmdListIndexParamAudioInitConfig)/sizeof(cmdListIndexParamAudioInitConfig[0]),
  cmdListIndexParamAudioInitConfig
};
/*
 * <<< OMX_PORT_PARAM_TYPE
 */
 
/*
 * >>> OMX_PARAM_VFCC_HWPORT_PROPERTIES, OMX_TI_IndexParamVFCCHwPortProperties
 */

/* Enum Entry for selecting H/W Capture Mode */
PRIVATE MX_DBG_ENUM_ENTRY_T enumTblHwCaptureModes[] =
{
  {"unused",           OMX_VIDEO_CaptureModeUnused,                  ""},
  {"sc_non_mux",       OMX_VIDEO_CaptureModeSC_NON_MUX,             ""},
  {"mc_line_mux",      OMX_VIDEO_CaptureModeMC_LINE_MUX,            ""},
  {"mc_pel_mux",       OMX_VIDEO_CaptureModeMC_PEL_MUX,             ""},
  {"sc_discrete_sync", OMX_VIDEO_CaptureModeSC_DISCRETESYNC,        ""},
  {"mux_split_line",   OMX_VIDEO_CaptureModeMC_LINE_MUX_SPLIT_LINE, ""},
  {"",                 0,                                           ""}
};

/* Entry for Set H/W Capture Mode */
PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryHwCaptureModes =
{
  "eCaptMode",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_ENUM         |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMX_PARAM_VFCC_HWPORT_PROPERTIES,eCaptMode),
  FIELDOFFSET(OMX_PARAM_VFCC_HWPORT_PROPERTIES,nSize) -
  FIELDOFFSET(OMX_PARAM_VFCC_HWPORT_PROPERTIES,eCaptMode),
  0,
  OMX_VIDEO_CaptureModeUnused,
  OMX_VIDEO_CaptureModeMC_LINE_MUX_SPLIT_LINE,
  OMX_VIDEO_CaptureModeMC_LINE_MUX,
  &enumTblHwCaptureModes,
  XdbgCmdVarFunc,
  "Capture Mode..................................",
  "",
  "",
  ""
};

/* Enum Entry for set Vif Mode */
PRIVATE MX_DBG_ENUM_ENTRY_T enumTblVifModes[] =
{
  {"unused",  OMX_VIDEO_CaptureVifModeUnused, ""},
  {"8_bit",   OMX_VIDEO_CaptureVifMode_08BIT, ""},
  {"16_bit",  OMX_VIDEO_CaptureVifMode_16BIT, ""},
  {"24_bit",  OMX_VIDEO_CaptureVifMode_24BIT, ""},
  {"",        0,                              ""}
};

/* Entry for Set Video Interface Mode */
PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryVifModes =
{
  "eVifMode",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_ENUM         |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMX_PARAM_VFCC_HWPORT_PROPERTIES,eVifMode),
  FIELDOFFSET(OMX_PARAM_VFCC_HWPORT_PROPERTIES,nSize) -
  FIELDOFFSET(OMX_PARAM_VFCC_HWPORT_PROPERTIES,eVifMode),
  0,
  OMX_VIDEO_CaptureVifModeUnused,
  OMX_VIDEO_CaptureVifMode_24BIT,
  OMX_VIDEO_CaptureVifMode_08BIT,
  &enumTblVifModes,
  XdbgCmdVarFunc,
  "Video Interface Mode..........................",
  "",
  "",
  ""
};

/* Enum Entry for selecting Capture Color Format */
PRIVATE MX_DBG_ENUM_ENTRY_T enumTblCaptureColorFormats[] =
{
  {"RGB888",  OMX_COLOR_Format24bitRGB888, ""},
  {"422YUYV", OMX_COLOR_FormatYCbYCr,      ""},
  {"",        0,                           ""}
};

/* Entry for Set Capture Color Format */
PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryCaptureColorFormats =
{
  "eInColorFormat",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_ENUM         |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMX_PARAM_VFCC_HWPORT_PROPERTIES,eInColorFormat),
  FIELDOFFSET(OMX_PARAM_VFCC_HWPORT_PROPERTIES,nSize) -
  FIELDOFFSET(OMX_PARAM_VFCC_HWPORT_PROPERTIES,eInColorFormat),
  0,
  OMX_COLOR_Format24bitRGB888,
  OMX_COLOR_FormatYCbYCr,
  OMX_COLOR_FormatYCbYCr,
  &enumTblCaptureColorFormats,
  XdbgCmdVarFunc,
  "VIP Input Color Format........................",
  "",
  "",
  ""
};

/* Enum Entry for selecting Capture Scan Type */
PRIVATE MX_DBG_ENUM_ENTRY_T enumTblCaptureScanType[] =
{
  {"unused",      OMX_VIDEO_CaptureScanTypeUnused,      ""},
  {"progressive", OMX_VIDEO_CaptureScanTypeProgressive, ""},
  {"interlaced",  OMX_VIDEO_CaptureScanTypeInterlaced,  ""},
  {"",            0,                                    ""}
};

/* Entry for Set Capture Color Format */
PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryCaptureScanType =
{
  "eScanType",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_ENUM         |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMX_PARAM_VFCC_HWPORT_PROPERTIES,eScanType),
  FIELDOFFSET(OMX_PARAM_VFCC_HWPORT_PROPERTIES,nSize) -
  FIELDOFFSET(OMX_PARAM_VFCC_HWPORT_PROPERTIES,eScanType),
  0,
  OMX_VIDEO_CaptureScanTypeUnused,
  OMX_VIDEO_CaptureScanTypeInterlaced,
  OMX_VIDEO_CaptureScanTypeInterlaced,
  &enumTblCaptureScanType,
  XdbgCmdVarFunc,
  "Capture Scan Type.............................",
  "",
  "",
  ""
};

/*Entry for Set Capture Width*/
PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryCaptureWidth =
{
  "nMaxWidth",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_DEC      |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMX_PARAM_VFCC_HWPORT_PROPERTIES,nMaxWidth),
  FIELDOFFSET(OMX_PARAM_VFCC_HWPORT_PROPERTIES,nSize) -
  FIELDOFFSET(OMX_PARAM_VFCC_HWPORT_PROPERTIES,nMaxWidth),
  0,
  0,
  1920,
  OMTB_VPSS_VFCC_DEF_WIDTH,
  NULL,
  XdbgCmdVarFunc,
  "Capture Max Width.............................",
  "<max width>",
  "",
  ""
};

/*Entry for Set Capture Height*/
PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryCaptureHeight =
{
  "nMaxHeight",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_DEC          |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMX_PARAM_VFCC_HWPORT_PROPERTIES,nMaxHeight),
  FIELDOFFSET(OMX_PARAM_VFCC_HWPORT_PROPERTIES,nSize) -
  FIELDOFFSET(OMX_PARAM_VFCC_HWPORT_PROPERTIES,nMaxHeight),
  0,
  0,
  1080,
  OMTB_VPSS_VFCC_DEF_HEIGHT,
  NULL,
  XdbgCmdVarFunc,
  "Capture Max Height............................",
  "<max height>",
  "",
  ""
};

/* Entry for Set Maximum Channels Per HW Port */
PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryMaxChannelPerPort=
{
  "nMaxChnlsPerHwPort",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_DEC          |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMX_PARAM_VFCC_HWPORT_PROPERTIES,nMaxChnlsPerHwPort),
  FIELDOFFSET(OMX_PARAM_VFCC_HWPORT_PROPERTIES,nSize) -
  FIELDOFFSET(OMX_PARAM_VFCC_HWPORT_PROPERTIES,nMaxChnlsPerHwPort),
  0,
  0,
  OMTB_MAX_VAL_U32,
  OMTB_VPSS_VIDEO_CAPTURE_MAX_CHNLS,
  NULL,
  XdbgCmdVarFunc,
  "Maximum Channels Per HW Port..................",
  "<max no of channels>",
  "",
  ""
};

MX_DBG_CMD_ENTRY_T* cmdListIndexParamVFCCHwPortPropertiesConfig[] =
{
  &cmdEntryHwCaptureModes,
  &cmdEntryVifModes,
  &cmdEntryCaptureColorFormats,
  &cmdEntryCaptureScanType,
  &cmdEntryCaptureWidth,
  &cmdEntryCaptureHeight,
  &cmdEntryMaxChannelPerPort,
  NULL
};
  
MX_DBG_CMD_TABLE_T cmdTblIndexParamVFCCHwPortPropertiesConfig =
{
  MX_DBG_ACCESS_ALL,
  sizeof(cmdListIndexParamVFCCHwPortPropertiesConfig)/sizeof(cmdListIndexParamVFCCHwPortPropertiesConfig[0]),
  cmdListIndexParamVFCCHwPortPropertiesConfig
};

/*
 * <<< OMX_PARAM_VFCC_HWPORT_PROPERTIES
 */
 
 
/*
 * >>> OMX_PARAM_VFCC_HWPORT_ID, OMX_TI_IndexParamVFCCHwPortID
 */
 
/* Enum Entry for Select Hardware Ports */
PRIVATE MX_DBG_ENUM_ENTRY_T enumTblHwPorts[] =
{
  {"unused",          OMX_VIDEO_CaptureHWPortUnUsed,       ""},
  {"vip1_porta",      OMX_VIDEO_CaptureHWPortVIP1_PORTA,   ""},
  {"vip1_portb",      OMX_VIDEO_CaptureHWPortVIP1_PORTB,   ""},
  {"vip2_porta",      OMX_VIDEO_CaptureHWPortVIP2_PORTA,   ""},
  {"vip2_portb",      OMX_VIDEO_CaptureHWPortVIP2_PORTB,   ""},
  {"all_ports",       OMX_VIDEO_CaptureHWPortALL_PORTS,    ""},
  {"",                0,                                   ""}
};

/* Entry for Set Selecting Hardware Ports */
PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryVideoCaptureHwPortId =
{
  "eHwPortId",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_ENUM         |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMX_PARAM_VFCC_HWPORT_ID,eHwPortId),
  FIELDOFFSET(OMX_PARAM_VFCC_HWPORT_ID,nSize) -
  FIELDOFFSET(OMX_PARAM_VFCC_HWPORT_ID,eHwPortId),
  0,
  OMX_VIDEO_CaptureHWPortUnUsed,
  OMX_VIDEO_CaptureHWPortALL_PORTS,
  OMX_VIDEO_CaptureHWPortALL_PORTS,
  &enumTblHwPorts,
  XdbgCmdVarFunc,
  "Hardware port ID..............................",
  "",
  "",
  ""
};
 
MX_DBG_CMD_ENTRY_T* cmdListIndexParamVFCCHwPortIDConfig[] =
{
  &cmdEntryVideoCaptureHwPortId,
  NULL
};
  
MX_DBG_CMD_TABLE_T cmdTblIndexParamVFCCHwPortIDConfig =
{
  MX_DBG_ACCESS_ALL,
  sizeof(cmdListIndexParamVFCCHwPortIDConfig)/sizeof(cmdListIndexParamVFCCHwPortIDConfig[0]),
  cmdListIndexParamVFCCHwPortIDConfig
}; 
/*
 * <<< OMX_PARAM_VFCC_HWPORT_ID
 */
 
/*
 * >>> OMX_PARAM_CTRL_VIDDECODER_INFO, OMX_TI_IndexParamCTRLVidDecInfo
 */

/* Enum Entry for Selecting Video Decoder */
PRIVATE MX_DBG_ENUM_ENTRY_T enumTblVPSSTvpVideoDecoder[] =
{
  {"unused",          OMX_VID_DEC_Unused,        ""},
  {"sii9135",         OMX_VID_DEC_SII9135_DRV,   ""},
  {"tvp7002",         OMX_VID_DEC_TVP7002_DRV,   ""},
  {"tvp5158",         OMX_VID_DEC_TVP5158_DRV,   ""},
  {"",                0,                      ""}
};

/* Entry for Set Selecting Video Decoder */
PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryVPSSTvpVideoDecoder =
{
  "videoDecoderId",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_ENUM         |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMX_PARAM_CTRL_VIDDECODER_INFO,videoDecoderId),
  FIELDOFFSET(OMX_PARAM_CTRL_VIDDECODER_INFO,nSize) -
  FIELDOFFSET(OMX_PARAM_CTRL_VIDDECODER_INFO,videoDecoderId),
  0,
  OMX_VID_DEC_Unused,
  OMX_VID_DEC_TVP5158_DRV,
  OMX_VID_DEC_TVP5158_DRV,
  &enumTblVPSSTvpVideoDecoder,
  XdbgCmdVarFunc,
  "TVP Decoder ID................................",
  "",
  "",
  ""
};

/* Enum Entry for Selecting Video Decoder Standards */
PRIVATE MX_DBG_ENUM_ENTRY_T enumTblVPSSTvpVideoDecoderStd[] =
{
  {"unused",        OMX_VIDEO_DECODER_STD_Unused ,      ""},
  {"auto_detect",   OMX_VIDEO_DECODER_STD_AUTO_DETECT,  ""},
#ifdef OMTB_SNT  
  {"1080P60",       OMX_VIDEO_DECODER_STD_1080P_60,     ""},
  {"1080I60",       OMX_VIDEO_DECODER_STD_1080I_60,     ""},  
  {"720P60",        OMX_VIDEO_DECODER_STD_720P_60,      ""},    
#endif
  {"mux_4ch_d1",    OMX_VIDEO_DECODER_STD_MUX_4CH_D1,   ""},
  {"",              0,                                  ""}
};

/* Entry for Set Selecting Video Decoder Standards */
PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryVPSSTvpVideoDecoderStd =
{
  "videoStandard",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_ENUM         |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMX_PARAM_CTRL_VIDDECODER_INFO,videoStandard),
  FIELDOFFSET(OMX_PARAM_CTRL_VIDDECODER_INFO,nSize) -
  FIELDOFFSET(OMX_PARAM_CTRL_VIDDECODER_INFO,videoStandard),
  0,
  OMX_VIDEO_DECODER_STD_Unused,
  OMX_VIDEO_DECODER_STD_MUX_4CH_D1,
  OMX_VIDEO_DECODER_STD_MUX_4CH_D1,
  &enumTblVPSSTvpVideoDecoderStd,
  XdbgCmdVarFunc,
  "TVP video decoder standards...................",
  "",
  "",
  ""
};

/* Enum Entry for Selecting Video System ID */
PRIVATE MX_DBG_ENUM_ENTRY_T enumTblVPSSTvpVideoSystemId[] =
{
  {"ntsc",        OMX_VIDEO_DECODER_VIDEO_SYSTEM_NTSC,          ""},
  {"pal",         OMX_VIDEO_DECODER_VIDEO_SYSTEM_PAL,           ""},
  {"auto_detect", OMX_VIDEO_DECODER_VIDEO_SYSTEM_AUTO_DETECT,   ""},
  {"",                0,                      ""}
};

/* Entry for Set selecting Video System ID */
PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryVPSSTvpVideoSystemId =
{
  "videoSystemId",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_ENUM         |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMX_PARAM_CTRL_VIDDECODER_INFO,videoSystemId ),
  FIELDOFFSET(OMX_PARAM_CTRL_VIDDECODER_INFO,nSize) -
  FIELDOFFSET(OMX_PARAM_CTRL_VIDDECODER_INFO,videoSystemId ),
  0,
  OMX_VIDEO_DECODER_VIDEO_SYSTEM_NTSC,
  OMX_VIDEO_DECODER_VIDEO_SYSTEM_AUTO_DETECT,
  OMX_VIDEO_DECODER_VIDEO_SYSTEM_AUTO_DETECT,
  &enumTblVPSSTvpVideoSystemId,
  XdbgCmdVarFunc,
  "TVP Video System ID is configured with........",
  "",
  "",
  ""
};

/* OMX_TI_IndexParamCTRLVidDecInfo */
MX_DBG_CMD_ENTRY_T* cmdListIndexParamCTRLVidDecInfoConfig[] =
{
  &cmdEntryVPSSTvpVideoDecoderStd,
  &cmdEntryVPSSTvpVideoDecoder,
  &cmdEntryVPSSTvpVideoSystemId,
  NULL
};
  
MX_DBG_CMD_TABLE_T cmdTblIndexParamCTRLVidDecInfoConfig =
{
  MX_DBG_ACCESS_ALL,
  sizeof(cmdListIndexParamCTRLVidDecInfoConfig)/sizeof(cmdListIndexParamCTRLVidDecInfoConfig[0]),
  cmdListIndexParamCTRLVidDecInfoConfig
};
/*
 * <<< OMX_PARAM_CTRL_VIDDECODER_INFO
 */ 
 
/*
 * >>> OMX_CONFIG_VFCC_FRAMESKIP_INFO, OMX_TI_IndexConfigVFCCFrameSkip
 */

 /* Entry for Set Selecting Frame Skip Mask*/
PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryFrameSkipMask =
{
  "frameSkipMask",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_DEC          |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMX_CONFIG_VFCC_FRAMESKIP_INFO,frameSkipMask),
  FIELDOFFSET(OMX_CONFIG_VFCC_FRAMESKIP_INFO,nSize) -
  FIELDOFFSET(OMX_CONFIG_VFCC_FRAMESKIP_INFO,frameSkipMask),
  0,
  0,
  OMTB_MAX_VAL_U32,
  OMTB_VPSS_VFCC_DEF_FRAME_SKIP_MASK,
  NULL,
  XdbgCmdVarFunc,
  "Frame Skip Mask...............................",
  "<frame skip mask>",
  "",
  ""
};

MX_DBG_CMD_ENTRY_T* cmdListIndexConfigVFCCFrameSkipConfig[] =
{
  &cmdEntryFrameSkipMask,
  NULL
};
  
MX_DBG_CMD_TABLE_T cmdTblIndexConfigVFCCFrameSkipConfig =
{
  MX_DBG_ACCESS_ALL,
  sizeof(cmdListIndexConfigVFCCFrameSkipConfig)/sizeof(cmdListIndexConfigVFCCFrameSkipConfig[0]),
  cmdListIndexConfigVFCCFrameSkipConfig
}; 
/*
 * <<< OMX_CONFIG_VFCC_FRAMESKIP_INFO
 */
 
 
/*
 * >>> OMX_CONFIG_VIDCHANNEL_RESOLUTION, OMX_TI_IndexConfigVidChResolution
 */
/*Entry for Set Channel ID */
PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryVidChResolutionCfgnChId =
{
  "nChId",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_DEC      |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMX_CONFIG_VIDCHANNEL_RESOLUTION,nChId),
  FIELDOFFSET(OMX_CONFIG_VIDCHANNEL_RESOLUTION,nSize) -
  FIELDOFFSET(OMX_CONFIG_VIDCHANNEL_RESOLUTION,nChId),
  0,
  0,
  16,
  //OMX_VFPC_DEIDUALOUT_HIGH_MAX_NUM_CHANNELS,
  0,
  NULL,
  XdbgCmdVarFunc,
  "Channel Id....................................",
  "<nChId>",
  "",
  ""
};


/*Entry for Set Frm0Width */
PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryVidChResolutionCfgFrm0Width =
{
  "Frm0Width",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_DEC      |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMX_CONFIG_VIDCHANNEL_RESOLUTION,Frm0Width),
  FIELDOFFSET(OMX_CONFIG_VIDCHANNEL_RESOLUTION,nSize) -
  FIELDOFFSET(OMX_CONFIG_VIDCHANNEL_RESOLUTION,Frm0Width),
  0,
  0,
  1920,
  360,
  NULL,
  XdbgCmdVarFunc,
  "Frame width for even port.....................",
  "<Frm0Width>",
  "",
  ""
};

/*Entry for Set Frm0Height */
PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryVidChResolutionCfgFrm0Height =
{
  "Frm0Height",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_DEC      |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMX_CONFIG_VIDCHANNEL_RESOLUTION,Frm0Height),
  FIELDOFFSET(OMX_CONFIG_VIDCHANNEL_RESOLUTION,nSize) -
  FIELDOFFSET(OMX_CONFIG_VIDCHANNEL_RESOLUTION,Frm0Height),
  0,
  0,
  1080,
  240,
  NULL,
  XdbgCmdVarFunc,
  "Frame height for even port....................",
  "<Frm0Height>",
  "",
  ""
};

/*Entry for Set Frm0Pitch */
PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryVidChResolutionCfgFrm0Pitch =
{
  "Frm0Pitch",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_DEC      |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMX_CONFIG_VIDCHANNEL_RESOLUTION,Frm0Pitch),
  FIELDOFFSET(OMX_CONFIG_VIDCHANNEL_RESOLUTION,nSize) -
  FIELDOFFSET(OMX_CONFIG_VIDCHANNEL_RESOLUTION,Frm0Pitch),
  0,
  0,
  3840,
  720,
  NULL,
  XdbgCmdVarFunc,
  "Frame pitch for even port.....................",
  "<Frm0Pitch>",
  "",
  ""
};

/* Enum Entry for setting eDir*/
PRIVATE MX_DBG_ENUM_ENTRY_T enumTbleDirInputOutput[] =
{
  {"input",  OMX_DirInput,   ""},
  {"output", OMX_DirOutput,  ""},
  {"",        0,          ""}
};

/*Entry for Set eDir */
PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryVidChResolutionCfgeDir =
{
  "eDir",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_ENUM         |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMX_CONFIG_VIDCHANNEL_RESOLUTION,eDir),
  FIELDOFFSET(OMX_CONFIG_VIDCHANNEL_RESOLUTION,nSize) -
  FIELDOFFSET(OMX_CONFIG_VIDCHANNEL_RESOLUTION,eDir),
  0,
  OMX_DirInput,
  OMX_DirOutput,
  OMX_DirInput,
  &enumTbleDirInputOutput,
  XdbgCmdVarFunc,
  "Input/Output directory........................",
  "",
  "",
  ""
};

/*Entry for Set Frm1Width */
PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryVidChResolutionCfgFrm1Width =
{
  "Frm1Width",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_DEC      |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMX_CONFIG_VIDCHANNEL_RESOLUTION,Frm1Width),
  FIELDOFFSET(OMX_CONFIG_VIDCHANNEL_RESOLUTION,nSize) -
  FIELDOFFSET(OMX_CONFIG_VIDCHANNEL_RESOLUTION,Frm1Width),
  0,
  0,
  1920,
  720,
  NULL,
  XdbgCmdVarFunc,
  "Frame width for odd port......................",
  "<Frm1Width>",
  "",
  ""
};


/*Entry for Set Frm1Height */
PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryVidChResolutionCfgFrm1Height =
{
  "Frm1Height",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_DEC      |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMX_CONFIG_VIDCHANNEL_RESOLUTION,Frm1Height),
  FIELDOFFSET(OMX_CONFIG_VIDCHANNEL_RESOLUTION,nSize) -
  FIELDOFFSET(OMX_CONFIG_VIDCHANNEL_RESOLUTION,Frm1Height),
  0,
  0,
  1080,
  480,
  NULL,
  XdbgCmdVarFunc,
  "Frame height for odd port.....................",
  "<Frm1Height>",
  "",
  ""
};

/*Entry for Set Frm1Pitch */
PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryVidChResolutionCfgFrm1Pitch =
{
  "Frm1Pitch",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_DEC      |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMX_CONFIG_VIDCHANNEL_RESOLUTION,Frm1Pitch),
  FIELDOFFSET(OMX_CONFIG_VIDCHANNEL_RESOLUTION,nSize) -
  FIELDOFFSET(OMX_CONFIG_VIDCHANNEL_RESOLUTION,Frm1Pitch),
  0,
  0,
  3840,
  720,
  NULL,
  XdbgCmdVarFunc,
  "Frame pitch for odd port......................",
  "<Frm1Pitch>",
  "",
  ""
};

/*Entry for Set FrmStartX */
PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryVidChResolutionCfgFrmStartX =
{
  "FrmStartX",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_DEC      |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMX_CONFIG_VIDCHANNEL_RESOLUTION,FrmStartX),
  FIELDOFFSET(OMX_CONFIG_VIDCHANNEL_RESOLUTION,nSize) -
  FIELDOFFSET(OMX_CONFIG_VIDCHANNEL_RESOLUTION,FrmStartX),
  0,
  0,
  1920,
  0,
  NULL,
  XdbgCmdVarFunc,
  "Start X position..............................",
  "<FrmStartX>",
  "",
  ""
};

/*Entry for Set FrmStartY */
PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryVidChResolutionCfgFrmStartY =
{
  "FrmStartY",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_DEC      |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMX_CONFIG_VIDCHANNEL_RESOLUTION,FrmStartY),
  FIELDOFFSET(OMX_CONFIG_VIDCHANNEL_RESOLUTION,nSize) -
  FIELDOFFSET(OMX_CONFIG_VIDCHANNEL_RESOLUTION,FrmStartY),
  0,
  0,
  1080,
  0,
  NULL,
  XdbgCmdVarFunc,
  "Start Y position..............................",
  "<FrmStartY>",
  "",
  ""
};

/*Entry for Set FrmCropWidth  */
PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryVidChResolutionCfgFrmCropWidth  =
{
  "FrmCropWidth",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_DEC      |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMX_CONFIG_VIDCHANNEL_RESOLUTION,FrmCropWidth),
  FIELDOFFSET(OMX_CONFIG_VIDCHANNEL_RESOLUTION,nSize) -
  FIELDOFFSET(OMX_CONFIG_VIDCHANNEL_RESOLUTION,FrmCropWidth),
  0,
  0,
  1920,
  1920,
  NULL,
  XdbgCmdVarFunc,
  "Frame crop width .............................",
  "<FrmCropWidth>",
  "",
  ""
};

/*Entry for Set FrmCropHeight */
PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryVidChResolutionCfgFrmCropHeight =
{
  "FrmCropHeight",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_DEC      |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMX_CONFIG_VIDCHANNEL_RESOLUTION,FrmCropHeight),
  FIELDOFFSET(OMX_CONFIG_VIDCHANNEL_RESOLUTION,nSize) -
  FIELDOFFSET(OMX_CONFIG_VIDCHANNEL_RESOLUTION,FrmCropHeight),
  0,
  0,
  1080,
  1080,
  NULL,
  XdbgCmdVarFunc,
  "Frame crop height ............................",
  "<FrmCropHeight>",
  "",
  ""
};

MX_DBG_CMD_ENTRY_T* cmdListIndexConfigVidChResolutionConfig[] =
{
  &cmdEntryVidChResolutionCfgnChId,
  &cmdEntryVidChResolutionCfgFrm0Width,
  &cmdEntryVidChResolutionCfgFrm0Height,
  &cmdEntryVidChResolutionCfgFrm0Pitch,
  &cmdEntryVidChResolutionCfgeDir,
  &cmdEntryVidChResolutionCfgFrm1Width,
  &cmdEntryVidChResolutionCfgFrm1Height,
  &cmdEntryVidChResolutionCfgFrm1Pitch,
  &cmdEntryVidChResolutionCfgFrmStartX,
  &cmdEntryVidChResolutionCfgFrmStartY,
  &cmdEntryVidChResolutionCfgFrmCropWidth,
  &cmdEntryVidChResolutionCfgFrmCropHeight,
  NULL
};
  
MX_DBG_CMD_TABLE_T cmdTblIndexConfigVidChResolutionConfig =
{
  MX_DBG_ACCESS_ALL,
  sizeof(cmdListIndexConfigVidChResolutionConfig)/sizeof(cmdListIndexConfigVidChResolutionConfig[0]),
  cmdListIndexConfigVidChResolutionConfig
}; 
/*
 * <<< OMX_CONFIG_VIDCHANNEL_RESOLUTION
 */
 
 
/*
 * >>> OMX_CONFIG_ALG_ENABLE, OMX_TI_IndexConfigAlgEnable
 */
/*FIXME: OMX_VFPC_DEIDUALOUT_HIGH_MAX_NUM_CHANNELS is replaced by 16, do not used hard coded values*/
/* Entry for Set channel id */
PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryAlgEnablenChId =
{
  "nChId",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_DEC      |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMX_CONFIG_ALG_ENABLE,nChId),
  FIELDOFFSET(OMX_CONFIG_ALG_ENABLE,nSize) -
  FIELDOFFSET(OMX_CONFIG_ALG_ENABLE,nChId),
  0,
  0,
  16,
  0,
  NULL,
  XdbgCmdVarFunc,
  "nChId.........................................",
  "<nChId>",
  "",
  ""
};

/* Enum Entry for enabling or disabling flag */
PRIVATE MX_DBG_ENUM_ENTRY_T enumTblOnOff[] =
{
  {"enable",  OMX_TRUE,   ""},
  {"disable", OMX_FALSE,  ""},
  {"",        0,          ""}
};

/* Entry for Set algorithm bypass */
PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryAlgEnablebAlgBypass =
{
  "bAlgBypass",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_ENUM         |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMX_CONFIG_ALG_ENABLE,bAlgBypass),
  FIELDOFFSET(OMX_CONFIG_ALG_ENABLE,nSize) -
  FIELDOFFSET(OMX_CONFIG_ALG_ENABLE,bAlgBypass),
  0,
  OMX_FALSE,
  OMX_TRUE,
  OMX_FALSE,
  &enumTblOnOff,
  XdbgCmdVarFunc,
  "Video Algorithm Bypass........................",
  "",
  "",
  ""
};

MX_DBG_CMD_ENTRY_T* cmdListIndexConfigAlgEnableConfig[] =
{
  &cmdEntryAlgEnablenChId,
  &cmdEntryAlgEnablebAlgBypass,
  NULL
};
  
MX_DBG_CMD_TABLE_T cmdTblIndexConfigAlgEnableConfig =
{
  MX_DBG_ACCESS_ALL,
  sizeof(cmdListIndexConfigAlgEnableConfig)/sizeof(cmdListIndexConfigAlgEnableConfig[0]),
  cmdListIndexConfigAlgEnableConfig
};
  
/*
 * <<< OMX_CONFIG_ALG_ENABLE
 */ 
 
 
/*
 * >>> OMX_PARAM_COMPPORT_NOTIFYTYPE, OMX_TI_IndexParamCompPortNotifyType
 */
 /* Enum Entry for Component Port Notify type*/
PRIVATE MX_DBG_ENUM_ENTRY_T  enumTblCompPortNotifyType[]=
{
  {"none",     OMX_NOTIFY_TYPE_NONE,       ""},
  {"always",   OMX_NOTIFY_TYPE_ALWAYS,     ""},
  {"once",     OMX_NOTIFY_TYPE_ONCE,       ""},
  {"",            0,                       ""}
};

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryCompPortNotifyType=
{
  "eNotifyType",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_ENUM         |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMX_PARAM_COMPPORT_NOTIFYTYPE,eNotifyType ),
  FIELDOFFSET(OMX_PARAM_COMPPORT_NOTIFYTYPE,nSize) -
  FIELDOFFSET(OMX_PARAM_COMPPORT_NOTIFYTYPE,eNotifyType ),
  0,
  OMX_NOTIFY_TYPE_NONE,
  OMX_NOTIFY_TYPE_ONCE,
  OMX_NOTIFY_TYPE_ALWAYS,
  &enumTblCompPortNotifyType,
  XdbgCmdVarFunc,
  "Comp Port Notify Type.........................",
  "",
  "",
  ""
};

MX_DBG_CMD_ENTRY_T* cmdListIndexParamCompPortNotifyTypeConfig[] =
{
  &cmdEntryCompPortNotifyType,
  NULL
};
  
MX_DBG_CMD_TABLE_T cmdTblIndexParamCompPortNotifyTypeConfig =
{
  MX_DBG_ACCESS_ALL,
  sizeof(cmdListIndexParamCompPortNotifyTypeConfig)/sizeof(cmdListIndexParamCompPortNotifyTypeConfig[0]),
  cmdListIndexParamCompPortNotifyTypeConfig
};
/*
 * <<< OMX_PARAM_COMPPORT_NOTIFYTYPE
 */
 
 
/*
 * >>> OMX_PARAM_COMPPORT_NOTIFYTYPE, OMX_TI_IndexConfigSubSamplingFactor
 */
/*Entry for Set Sub Sampling Factor*/
PRIVATE MX_DBG_CMD_ENTRY_T cmdEntrySubSampFactor =
{
  "nSubSamplingFactor",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_DEC          |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMX_CONFIG_SUBSAMPLING_FACTOR,nSubSamplingFactor),
  FIELDOFFSET(OMX_CONFIG_SUBSAMPLING_FACTOR,nSize) -
  FIELDOFFSET(OMX_CONFIG_SUBSAMPLING_FACTOR,nSubSamplingFactor),
  0,
  0,
  OMTB_MAX_VAL_U32,
  OMTB_VPSS_VFPC_DEI_DEF_SUB_SAMP_FACTOR,
  NULL,
  XdbgCmdVarFunc,
  "Sub sampling factor...........................",
  "< set 1 if capture rate is 30 else 2>",
  "",
  ""
};

MX_DBG_CMD_ENTRY_T* cmdListIndexConfigSubSamplingFactorConfig[] =
{
  &cmdEntrySubSampFactor,
  NULL
};
  
MX_DBG_CMD_TABLE_T cmdTblIndexConfigSubSamplingFactorConfig =
{
  MX_DBG_ACCESS_ALL,
  sizeof(cmdListIndexConfigSubSamplingFactorConfig)/sizeof(cmdListIndexConfigSubSamplingFactorConfig[0]),
  cmdListIndexConfigSubSamplingFactorConfig
};
/*
 * <<< OMX_PARAM_COMPPORT_NOTIFYTYPE
 */
 
 
/*
 * >>> OMX_PARAM_VFPC_NUMCHANNELPERHANDLE, OMX_TI_IndexParamVFPCNumChPerHandle
 */
/*Entry for Set the Number Of Channels Per Handle*/
PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryNoOfChanPerHandle =
{
  "nNumChannelsPerHandle",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_DEC          |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMX_PARAM_VFPC_NUMCHANNELPERHANDLE,nNumChannelsPerHandle),
  FIELDOFFSET(OMX_PARAM_VFPC_NUMCHANNELPERHANDLE,nSize) -
  FIELDOFFSET(OMX_PARAM_VFPC_NUMCHANNELPERHANDLE,nNumChannelsPerHandle),
  0,
  0,
  OMTB_MAX_VAL_U32,
  OMTB_VPSS_VFPC_DEI_DEF_NO_OF_CHAN,
  NULL,
  XdbgCmdVarFunc,
  "No of channels per handle.....................",
  "",
  "",
  ""
};

MX_DBG_CMD_ENTRY_T* cmdListIndexParamVFPCNumChPerHandleConfig[] =
{
  &cmdEntryNoOfChanPerHandle,
  NULL
};
  
MX_DBG_CMD_TABLE_T cmdTblIndexParamVFPCNumChPerHandleConfig =
{
  MX_DBG_ACCESS_ALL,
  sizeof(cmdListIndexParamVFPCNumChPerHandleConfig)/sizeof(cmdListIndexParamVFPCNumChPerHandleConfig[0]),
  cmdListIndexParamVFPCNumChPerHandleConfig
};
/*
 * <<< OMX_PARAM_VFPC_NUMCHANNELPERHANDLE
 */
 
 
 /*
 * >>> OMX_PARAM_VFDC_DRIVERINSTID, OMX_TI_IndexParamVFDCDriverInstId
 */

 /*Entry for Set driver instance ID */
PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryDvrInstanceId =
{
  "nDrvInstID",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_DEC      |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMX_PARAM_VFDC_DRIVERINSTID,nDrvInstID),
  FIELDOFFSET(OMX_PARAM_VFDC_DRIVERINSTID,nSize) -
  FIELDOFFSET(OMX_PARAM_VFDC_DRIVERINSTID,nDrvInstID),
  0,
  0,
  OMTB_MAX_VAL_U32,
  0,
  NULL,
  XdbgCmdVarFunc,
  "VFDC Driver Instance ID.......................",
  "<0 (HD Private Path 0) | 1 (HD Private Path 1) | 2 (SD Path)>",
  "",
  ""
};

 /* Enum Entry for Supported DC Mode id */
PRIVATE MX_DBG_ENUM_ENTRY_T enumTblDcModeId[] =
{
  {"ntsc",    OMX_DC_MODE_NTSC,     ""},
  {"pal",     OMX_DC_MODE_PAL,      ""},
  {"1080p60", OMX_DC_MODE_1080P_60, ""},
  {"720p60",  OMX_DC_MODE_720P_60,  ""},
  {"1080i60", OMX_DC_MODE_1080I_60, ""},
  {"1080p30", OMX_DC_MODE_1080P_30, ""},
  {"",        0,                    ""}
};

/* Entry for Setting DC Mode id */
PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryDispVencMode =
{
  "eDispVencMode",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_ENUM          |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMX_PARAM_VFDC_DRIVERINSTID,eDispVencMode),
  FIELDOFFSET(OMX_PARAM_VFDC_DRIVERINSTID,nSize) -
  FIELDOFFSET(OMX_PARAM_VFDC_DRIVERINSTID,eDispVencMode),
  0,
  OMX_DC_MODE_NTSC,
  OMX_DC_MODE_1080P_30,
  OMX_DC_MODE_1080P_60,
  &enumTblDcModeId,
  XdbgCmdVarFunc,
  "Display Venc Mode.............................",
  "",
  "",
  ""
};

MX_DBG_CMD_ENTRY_T* cmdListIndexParamVFDCDriverInstIdConfig[] =
{
  &cmdEntryDvrInstanceId,
  &cmdEntryDispVencMode,
  NULL
};
  
MX_DBG_CMD_TABLE_T cmdTblIndexParamVFDCDriverInstIdConfig =
{
  MX_DBG_ACCESS_ALL,
  sizeof(cmdListIndexParamVFDCDriverInstIdConfig)/sizeof(cmdListIndexParamVFDCDriverInstIdConfig[0]),
  cmdListIndexParamVFDCDriverInstIdConfig
};

 /*
 * <<< OMX_PARAM_VFDC_DRIVERINSTID
 */
 
 /*
 * >>> OMX_PARAM_DC_CUSTOM_MODE_INFO, OMX_TI_IndexParamVFDCCustomModeInfo
 */ 

/* Entry for Setting Width */
PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryCustomModeWidth =
{
  "width",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_DEC      |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMX_PARAM_DC_CUSTOM_MODE_INFO,width),
  FIELDOFFSET(OMX_PARAM_DC_CUSTOM_MODE_INFO,nSize) -
  FIELDOFFSET(OMX_PARAM_DC_CUSTOM_MODE_INFO,width),
  0,
  0,
  OMTB_MAX_VAL_U32,
  OMTB_VPSS_VFDC_DEF_WIDTH,
  NULL,
  XdbgCmdVarFunc,
  "Active video frame width in pixels............",
  "",
  "",
  ""
};

/* Entry for Setting Height */
PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryCustomModeHeight =
{
  "height",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_DEC      |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMX_PARAM_DC_CUSTOM_MODE_INFO,height),
  FIELDOFFSET(OMX_PARAM_DC_CUSTOM_MODE_INFO,nSize) -
  FIELDOFFSET(OMX_PARAM_DC_CUSTOM_MODE_INFO,height),
  0,
  0,
  OMTB_MAX_VAL_U32,
  OMTB_VPSS_VFDC_DEF_HEIGHT,
  NULL,
  XdbgCmdVarFunc,
  "Active video frame height in lines............",
  "",
  "",
  ""
}; 

 /* Enum Entry for Supported Scan Format */
PRIVATE MX_DBG_ENUM_ENTRY_T enumTblDcScanFormat[] =
{
  {"interlaced",    OMX_DC_SF_INTERLACED,     ""},
  {"progressive",   OMX_SF_PROGRESSIVE,       ""},
  {"",              0,                        ""}  
};

/* Entry for Setting Scan Format */
PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryCustomModeScanFormat =
{
  "scanFormat",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_ENUM          |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMX_PARAM_DC_CUSTOM_MODE_INFO,scanFormat),
  FIELDOFFSET(OMX_PARAM_DC_CUSTOM_MODE_INFO,nSize) -
  FIELDOFFSET(OMX_PARAM_DC_CUSTOM_MODE_INFO,scanFormat),
  0,
  OMX_DC_SF_INTERLACED,
  OMX_SF_PROGRESSIVE,
  OMX_DC_MODE_1080P_60,
  &enumTblDcScanFormat,
  XdbgCmdVarFunc,
  "Scan format...................................",
  "",
  "",
  ""
};

/* Entry for Setting Pixel Clock */
PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryCustomModePixelClock =
{
  "pixelClock",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_DEC      |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMX_PARAM_DC_CUSTOM_MODE_INFO,pixelClock),
  FIELDOFFSET(OMX_PARAM_DC_CUSTOM_MODE_INFO,nSize) -
  FIELDOFFSET(OMX_PARAM_DC_CUSTOM_MODE_INFO,pixelClock),
  0,
  0,
  OMTB_MAX_VAL_U32,
  0,
  NULL,
  XdbgCmdVarFunc,
  "Pixel clock of standard in KHz................",
  "",
  "",
  ""
};  

/* Entry for Setting Fps */
PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryCustomModefps =
{
  "fps",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_DEC      |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMX_PARAM_DC_CUSTOM_MODE_INFO,fps),
  FIELDOFFSET(OMX_PARAM_DC_CUSTOM_MODE_INFO,nSize) -
  FIELDOFFSET(OMX_PARAM_DC_CUSTOM_MODE_INFO,fps),
  0,
  0,
  OMTB_MAX_VAL_U32,
  0,
  NULL,
  XdbgCmdVarFunc,
  "Custom Mode Fps...............................",
  "",
  "",
  ""
};    

/* Entry for Setting Horizontal Front porch */
PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryCustomHorFrontPorch =
{
  "hFrontPorch",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_DEC      |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMX_PARAM_DC_CUSTOM_MODE_INFO,hFrontPorch),
  FIELDOFFSET(OMX_PARAM_DC_CUSTOM_MODE_INFO,nSize) -
  FIELDOFFSET(OMX_PARAM_DC_CUSTOM_MODE_INFO,hFrontPorch),
  0,
  0,
  OMTB_MAX_VAL_U32,
  0,
  NULL,
  XdbgCmdVarFunc,
  "Horizontal front porch........................",
  "",
  "",
  ""
}; 

/* Entry for Setting Horizontal Back porch */
PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryCustomHorBackPorch =
{
  "hBackPorch",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_DEC      |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMX_PARAM_DC_CUSTOM_MODE_INFO,hBackPorch),
  FIELDOFFSET(OMX_PARAM_DC_CUSTOM_MODE_INFO,nSize) -
  FIELDOFFSET(OMX_PARAM_DC_CUSTOM_MODE_INFO,hBackPorch),
  0,
  0,
  OMTB_MAX_VAL_U32,
  0,
  NULL,
  XdbgCmdVarFunc,
  "Horizontal back porch.........................",
  "",
  "",
  ""
};

/* Entry for Setting Horizontal Sync Len */
PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryCustomHorSyncLen =
{
  "hSyncLen",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_DEC      |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMX_PARAM_DC_CUSTOM_MODE_INFO,hSyncLen),
  FIELDOFFSET(OMX_PARAM_DC_CUSTOM_MODE_INFO,nSize) -
  FIELDOFFSET(OMX_PARAM_DC_CUSTOM_MODE_INFO,hSyncLen),
  0,
  0,
  OMTB_MAX_VAL_U32,
  0,
  NULL,
  XdbgCmdVarFunc,
  "Horizontal sync length........................",
  "",
  "",
  ""
};

/* Entry for Setting Vertical Front porch */
PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryCustomVerFrontPorch =
{
  "vFrontPorch",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_DEC      |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMX_PARAM_DC_CUSTOM_MODE_INFO,vFrontPorch),
  FIELDOFFSET(OMX_PARAM_DC_CUSTOM_MODE_INFO,nSize) -
  FIELDOFFSET(OMX_PARAM_DC_CUSTOM_MODE_INFO,vFrontPorch),
  0,
  0,
  OMTB_MAX_VAL_U32,
  0,
  NULL,
  XdbgCmdVarFunc,
  "Vertical front porch for each field or frame..",
  "",
  "",
  ""
}; 

/* Entry for Setting Vertical Back porch */
PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryCustomVerBackPorch =
{
  "vBackPorch",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_DEC      |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMX_PARAM_DC_CUSTOM_MODE_INFO,vBackPorch),
  FIELDOFFSET(OMX_PARAM_DC_CUSTOM_MODE_INFO,nSize) -
  FIELDOFFSET(OMX_PARAM_DC_CUSTOM_MODE_INFO,vBackPorch),
  0,
  0,
  OMTB_MAX_VAL_U32,
  0,
  NULL,
  XdbgCmdVarFunc,
  "Vertical back porch for each field or frame...",
  "",
  "",
  ""
};

/* Entry for Setting Vertical Sync Len */
PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryCustomVerSyncLen =
{
  "vSyncLen",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_DEC      |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMX_PARAM_DC_CUSTOM_MODE_INFO,vSyncLen),
  FIELDOFFSET(OMX_PARAM_DC_CUSTOM_MODE_INFO,nSize) -
  FIELDOFFSET(OMX_PARAM_DC_CUSTOM_MODE_INFO,vSyncLen),
  0,
  0,
  OMTB_MAX_VAL_U32,
  0,
  NULL,
  XdbgCmdVarFunc,
  "Vertical sync length for each field...........",
  "",
  "",
  ""
};

MX_DBG_CMD_ENTRY_T* cmdListIndexParamVFDCCustomModeInfoConfig[] =
{
  &cmdEntryCustomModeWidth,
  &cmdEntryCustomModeHeight,
  &cmdEntryCustomModeScanFormat,
  &cmdEntryCustomModePixelClock,
  &cmdEntryCustomModefps,
  &cmdEntryCustomHorFrontPorch,
  &cmdEntryCustomHorBackPorch,
  &cmdEntryCustomHorSyncLen,
  &cmdEntryCustomVerFrontPorch,
  &cmdEntryCustomVerBackPorch,
  &cmdEntryCustomVerSyncLen,
  NULL
};
  
MX_DBG_CMD_TABLE_T cmdTblIndexParamVFDCCustomModeInfoConfig =
{
  MX_DBG_ACCESS_ALL,
  sizeof(cmdListIndexParamVFDCCustomModeInfoConfig)/sizeof(cmdListIndexParamVFDCCustomModeInfoConfig[0]),
  cmdListIndexParamVFDCCustomModeInfoConfig
};

 /*
 * <<< OMX_PARAM_DC_CUSTOM_MODE_INFO
 */

 /*
 * >>> OMX_PARAM_DC_CUSTOM_MODE_INFO, OMX_TI_IndexParamVFDCCustomModeInfo
 */ 
 
/* Video Encoder setp commands */

/*
 * >>> OMX_CONFIG_FRAMERATETYPE, OMX_IndexConfigVideoFramerate
 */ 

/* Entry for Set Framerate */
PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryEncodeFramerate =
{
  "xEncodeFramerate",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_DEC          |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMX_CONFIG_FRAMERATETYPE,xEncodeFramerate),
  FIELDOFFSET(OMX_CONFIG_FRAMERATETYPE,nSize) -
  FIELDOFFSET(OMX_CONFIG_FRAMERATETYPE,xEncodeFramerate),
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

MX_DBG_CMD_ENTRY_T* cmdListIndexConfigVideoFramerateConfig[] =
{
  &cmdEntryEncodeFramerate,
  NULL
};
  
MX_DBG_CMD_TABLE_T cmdTblIndexConfigVideoFramerateConfig =
{
  MX_DBG_ACCESS_ALL,
  sizeof(cmdListIndexConfigVideoFramerateConfig)/sizeof(cmdListIndexConfigVideoFramerateConfig[0]),
  cmdListIndexConfigVideoFramerateConfig
};
 /*
 * <<< OMX_CONFIG_FRAMERATETYPE
 */ 
 
/*
 * >>> OMX_VIDEO_CONFIG_BITRATETYPE, OMX_IndexConfigVideoBitrate
 */
 
/* Entry for Set Bitrate */
PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryEncodeBitrate =
{
  "nEncodeBitrate",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_DEC          |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMX_VIDEO_CONFIG_BITRATETYPE,nEncodeBitrate),
  FIELDOFFSET(OMX_VIDEO_CONFIG_BITRATETYPE,nSize) -
  FIELDOFFSET(OMX_VIDEO_CONFIG_BITRATETYPE,nEncodeBitrate),
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

MX_DBG_CMD_ENTRY_T* cmdListIndexConfigVideoBitrateConfig[] =
{
  &cmdEntryEncodeBitrate,
  NULL
};
  
MX_DBG_CMD_TABLE_T cmdTblIndexConfigVideoBitrateConfig =
{
  MX_DBG_ACCESS_ALL,
  sizeof(cmdListIndexConfigVideoBitrateConfig)/sizeof(cmdListIndexConfigVideoBitrateConfig[0]),
  cmdListIndexConfigVideoBitrateConfig
};

/*
 * <<< OMX_VIDEO_CONFIG_BITRATETYPE
 */ 
 
/*
 * OMX_VIDEO_CONFIG_MESEARCHRANGETYPE, OMX_TI_IndexConfigVideoMESearchRange
 */
 
/* Enum Entry for Supported motion vector accuracy */

PRIVATE MX_DBG_ENUM_ENTRY_T enumTblMVAccuracy[] =
{
  {"pel",         OMX_Video_MotionVectorPixel,      ""},
  {"halfpel",     OMX_Video_MotionVectorHalfPel,    ""},
  {"quarterpel",  OMX_Video_MotionVectorQuarterPel, ""},
  {"eighthpel",   OMX_Video_MotionVectorEighthPel,  ""},
  {"",            0,                                ""}
};

/* Entry for Set motion vector accuracy */

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryMVAccuracy =
{
  "eMVAccuracy",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_ENUM         |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMX_VIDEO_CONFIG_MESEARCHRANGETYPE,eMVAccuracy),
  FIELDOFFSET(OMX_VIDEO_CONFIG_MESEARCHRANGETYPE,nSize) -
  FIELDOFFSET(OMX_VIDEO_CONFIG_MESEARCHRANGETYPE,eMVAccuracy),
  0,
  OMX_Video_MotionVectorPixel,
  OMX_Video_MotionVectorMax,
  OMX_Video_MotionVectorQuarterPel,
  &enumTblMVAccuracy,
  XdbgCmdVarFunc,
  "Motion vector accuracy........................",
  "",
  "",
  ""
};


/* Entry for Set ME horizontal Search Range - P frames */

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryMEHorSearchRangeP =
{
  "nHorSearchRangeP",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_DEC          |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMX_VIDEO_CONFIG_MESEARCHRANGETYPE,nHorSearchRangeP),
  FIELDOFFSET(OMX_VIDEO_CONFIG_MESEARCHRANGETYPE,nSize) -
  FIELDOFFSET(OMX_VIDEO_CONFIG_MESEARCHRANGETYPE,nHorSearchRangeP),
  0,
  OMTB_MIN_VAL_U32,
  OMTB_MAX_VID_WIDTH,
  OMTB_H264_VENC_DEF_MESR_HORP,
  NULL,
  XdbgCmdVarFunc,
  "ME Horizontal Search Range for P Frames.......",
  "<ME Horizontal Search range for P frames>",
  "",
  ""
};


/* Entry for Set ME vertical Search Range - P frames */

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryMEVerSearchRangeP =
{
  "nVerSearchRangeP",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_DEC          |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMX_VIDEO_CONFIG_MESEARCHRANGETYPE,nVerSearchRangeP),
  FIELDOFFSET(OMX_VIDEO_CONFIG_MESEARCHRANGETYPE,nSize) -
  FIELDOFFSET(OMX_VIDEO_CONFIG_MESEARCHRANGETYPE,nVerSearchRangeP),
  0,
  OMTB_MIN_VAL_U32,
  OMTB_MAX_VID_HEIGHT,
  OMTB_H264_VENC_DEF_MESR_VERP,
  NULL,
  XdbgCmdVarFunc,
  "ME Vertical Search Range for P Frames.........",
  "<ME Vertical Search range for P frames>",
  "",
  ""
};

/* Entry for Set ME horizontal Search Range - B frames */

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryMEHorSearchRangeB =
{
  "nHorSearchRangeB",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_DEC          |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMX_VIDEO_CONFIG_MESEARCHRANGETYPE,nHorSearchRangeB),
  FIELDOFFSET(OMX_VIDEO_CONFIG_MESEARCHRANGETYPE,nSize) -
  FIELDOFFSET(OMX_VIDEO_CONFIG_MESEARCHRANGETYPE,nHorSearchRangeB),
  0,
  OMTB_MIN_VAL_U32,
  OMTB_MAX_VID_WIDTH,
  OMTB_H264_VENC_DEF_MESR_HORB,
  NULL,
  XdbgCmdVarFunc,
  "ME Horizontal Search Range for B Frames.......",
  "<ME Horizontal Search range for B frames>",
  "",
  ""
};


/* Entry for Set ME vertical Search Range - B frames */

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryMEVerSearchRangeB =
{
  "nVerSearchRangeB",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_DEC          |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMX_VIDEO_CONFIG_MESEARCHRANGETYPE,nVerSearchRangeB),
  FIELDOFFSET(OMX_VIDEO_CONFIG_MESEARCHRANGETYPE,nSize) -
  FIELDOFFSET(OMX_VIDEO_CONFIG_MESEARCHRANGETYPE,nVerSearchRangeB),
  0,
  OMTB_MIN_VAL_U32,
  OMTB_MAX_VID_HEIGHT,
  OMTB_H264_VENC_DEF_MESR_VERB,
  NULL,
  XdbgCmdVarFunc,
  "ME Vertical Search Range for B Frames.........",
  "<ME Vertical Search Range for B Frames>",
  "",
  ""
};

MX_DBG_CMD_ENTRY_T* cmdListIndexConfigVideoMESearchRangeConfig[] =
{
  &cmdEntryMVAccuracy,
  &cmdEntryMEHorSearchRangeP,
  &cmdEntryMEVerSearchRangeP,
  &cmdEntryMEHorSearchRangeB,
  &cmdEntryMEVerSearchRangeB,
  NULL
};
  
MX_DBG_CMD_TABLE_T cmdTblIndexConfigVideoMESearchRangeConfig =
{
  MX_DBG_ACCESS_ALL,
  sizeof(cmdListIndexConfigVideoMESearchRangeConfig)/sizeof(cmdListIndexConfigVideoMESearchRangeConfig[0]),
  cmdListIndexConfigVideoMESearchRangeConfig
};

/*
 * <<< OMX_VIDEO_CONFIG_MESEARCHRANGETYPE
 */ 
 
 
 
/*
 * >>> OMX_CONFIG_INTRAREFRESHVOPTYPE, OMX_IndexConfigVideoIntraVOPRefresh
 */
/* Entry for Set Intra Refresh VOP */

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryIntraRefreshVOP =
{
  "IntraRefreshVOP",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_ENUM         |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMX_CONFIG_INTRAREFRESHVOPTYPE,IntraRefreshVOP),
  FIELDOFFSET(OMX_CONFIG_INTRAREFRESHVOPTYPE,nSize) -
  FIELDOFFSET(OMX_CONFIG_INTRAREFRESHVOPTYPE,IntraRefreshVOP),
  0,
  OMX_FALSE,
  OMX_TRUE,
  OMX_FALSE,
  &enumTblOnOff,
  XdbgCmdVarFunc,
  "Intra Refresh VOP.............................",
  "",
  "",
  ""
};

MX_DBG_CMD_ENTRY_T* cmdListIndexConfigVideoIntraVOPRefreshConfig[] =
{
  &cmdEntryIntraRefreshVOP,
  NULL
};
  
MX_DBG_CMD_TABLE_T cmdTblIndexConfigVideoIntraVOPRefreshConfig =
{
  MX_DBG_ACCESS_ALL,
  sizeof(cmdListIndexConfigVideoIntraVOPRefreshConfig)/sizeof(cmdListIndexConfigVideoIntraVOPRefreshConfig[0]),
  cmdListIndexConfigVideoIntraVOPRefreshConfig
};

/*
 * <<< OMX_CONFIG_INTRAREFRESHVOPTYPE
 */
 
 
/*
 * >>> OMX_VIDEO_CONFIG_QPSETTINGSTYPE, OMX_TI_IndexConfigVideoQPSettings
 */
/* Entry for Set QP for I frames */

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryQPSettingsQpI =
{
  "nQpI",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_DEC          |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMX_VIDEO_CONFIG_QPSETTINGSTYPE,nQpI),
  FIELDOFFSET(OMX_VIDEO_CONFIG_QPSETTINGSTYPE,nSize) -
  FIELDOFFSET(OMX_VIDEO_CONFIG_QPSETTINGSTYPE,nQpI),
  0,
  OMTB_H264_VENC_MIN_QP_IPB,
  OMTB_H264_VENC_MAX_QP_IPB,
  OMTB_H264_VENC_DEF_QP_I,
  NULL,
  XdbgCmdVarFunc,
  "QP for I frames...............................",
  "<QP # - For I frames>",
  "",
  ""
};


/* Entry for Set QP Max for I frames */

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryQPSettingsQpMaxI =
{
  "nQpMaxI",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_DEC          |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMX_VIDEO_CONFIG_QPSETTINGSTYPE,nQpMaxI),
  FIELDOFFSET(OMX_VIDEO_CONFIG_QPSETTINGSTYPE,nSize) -
  FIELDOFFSET(OMX_VIDEO_CONFIG_QPSETTINGSTYPE,nQpMaxI),
  0,
  OMTB_H264_VENC_MIN_QP_IPB,
  OMTB_H264_VENC_MAX_QP_IPB,
  OMTB_H264_VENC_MAX_QP_IPB,
  NULL,
  XdbgCmdVarFunc,
  "QP Max for I frames...........................",
  "<QP Max # - For I frames>",
  "",
  ""
};

/* Entry for Set QP Min for I frames */

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryQPSettingsQpMinI =
{
  "nQpMinI",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_DEC          |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMX_VIDEO_CONFIG_QPSETTINGSTYPE,nQpMinI),
  FIELDOFFSET(OMX_VIDEO_CONFIG_QPSETTINGSTYPE,nSize) -
  FIELDOFFSET(OMX_VIDEO_CONFIG_QPSETTINGSTYPE,nQpMinI),
  0,
  OMTB_H264_VENC_MIN_QP_IPB,
  OMTB_H264_VENC_MAX_QP_IPB,
  OMTB_H264_VENC_MIN_QP_IPB,
  NULL,
  XdbgCmdVarFunc,
  "QP Min for I frames...........................",
  "<QP Min # - For I frames>",
  "",
  ""
};


/* Entry for Set QP for P frames */

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryQPSettingsQpP =
{
  "nQpP",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_DEC          |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMX_VIDEO_CONFIG_QPSETTINGSTYPE,nQpP),
  FIELDOFFSET(OMX_VIDEO_CONFIG_QPSETTINGSTYPE,nSize) -
  FIELDOFFSET(OMX_VIDEO_CONFIG_QPSETTINGSTYPE,nQpP),
  0,
  OMTB_H264_VENC_MIN_QP_IPB,
  OMTB_H264_VENC_MAX_QP_IPB,
  OMTB_H264_VENC_DEF_QP_P,
  NULL,
  XdbgCmdVarFunc,
  "QP for P frames...............................",
  "<QP # - For P frames>",
  "",
  ""
};

/* Entry for Set QP Max for P frames */

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryQPSettingsQpMaxP =
{
  "nQpMaxP",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_DEC          |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMX_VIDEO_CONFIG_QPSETTINGSTYPE,nQpMaxP),
  FIELDOFFSET(OMX_VIDEO_CONFIG_QPSETTINGSTYPE,nSize) -
  FIELDOFFSET(OMX_VIDEO_CONFIG_QPSETTINGSTYPE,nQpMaxP),
  0,
  OMTB_H264_VENC_MIN_QP_IPB,
  OMTB_H264_VENC_MAX_QP_IPB,
  OMTB_H264_VENC_MAX_QP_IPB,
  NULL,
  XdbgCmdVarFunc,
  "QP Max for P frames...........................",
  "<QP Max # - For P frames>",
  "",
  ""
};

/* Entry for Set QP Min for P frames */

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryQPSettingsQpMinP =
{
  "nQpMinP",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_DEC          |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMX_VIDEO_CONFIG_QPSETTINGSTYPE,nQpMinP),
  FIELDOFFSET(OMX_VIDEO_CONFIG_QPSETTINGSTYPE,nSize) -
  FIELDOFFSET(OMX_VIDEO_CONFIG_QPSETTINGSTYPE,nQpMinP),
  0,
  OMTB_H264_VENC_MIN_QP_IPB,
  OMTB_H264_VENC_MAX_QP_IPB,
  OMTB_H264_VENC_MIN_QP_IPB,
  NULL,
  XdbgCmdVarFunc,
  "QP Min for P frames...........................",
  "<QP Min # - For P frames>",
  "",
  ""
};

/* Entry for Set QP offset for B frames */

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryQPSettingsQpOffsetB =
{
  "nQpOffsetB",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_DEC          |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMX_VIDEO_CONFIG_QPSETTINGSTYPE,nQpOffsetB),
  FIELDOFFSET(OMX_VIDEO_CONFIG_QPSETTINGSTYPE,nSize) -
  FIELDOFFSET(OMX_VIDEO_CONFIG_QPSETTINGSTYPE,nQpOffsetB),
  0,
  OMTB_H264_VENC_MIN_QP_IPB,
  OMTB_H264_VENC_MAX_QP_IPB,
  OMTB_H264_VENC_DEF_QP_B,
  NULL,
  XdbgCmdVarFunc,
  "QP offset for B frames........................",
  "<QP Offset # - For B frames>",
  "",
  ""
};

/* Entry for Set QP Max for B frames */

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryQPSettingsQpMaxB =
{
  "nQpMaxB",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_DEC          |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMX_VIDEO_CONFIG_QPSETTINGSTYPE,nQpMaxB),
  FIELDOFFSET(OMX_VIDEO_CONFIG_QPSETTINGSTYPE,nSize) -
  FIELDOFFSET(OMX_VIDEO_CONFIG_QPSETTINGSTYPE,nQpMaxB),
  0,
  OMTB_H264_VENC_MIN_QP_IPB,
  OMTB_H264_VENC_MAX_QP_IPB,
  OMTB_H264_VENC_MAX_QP_IPB,
  NULL,
  XdbgCmdVarFunc,
  "QP Max for B frames...........................",
  "<QP Max # - For B frames>",
  "",
  ""
};

/* Entry for Set QP Min for B frames */

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryQPSettingsQpMinB =
{
  "nQpMinB",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_DEC          |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMX_VIDEO_CONFIG_QPSETTINGSTYPE,nQpMinB),
  FIELDOFFSET(OMX_VIDEO_CONFIG_QPSETTINGSTYPE,nSize) -
  FIELDOFFSET(OMX_VIDEO_CONFIG_QPSETTINGSTYPE,nQpMinB),
  0,
  OMTB_H264_VENC_MIN_QP_IPB,
  OMTB_H264_VENC_MAX_QP_IPB,
  OMTB_H264_VENC_MIN_QP_IPB,
  NULL,
  XdbgCmdVarFunc,
  "QP Min for B frames...........................",
  "<QP Min # - For B frames>",
  "",
  ""
};

MX_DBG_CMD_ENTRY_T* cmdListIndexConfigVideoQPSettingsConfig[] =
{
  &cmdEntryQPSettingsQpI,
  &cmdEntryQPSettingsQpMaxI,
  &cmdEntryQPSettingsQpMinI,
  &cmdEntryQPSettingsQpP,
  &cmdEntryQPSettingsQpMaxP,
  &cmdEntryQPSettingsQpMinP,
  &cmdEntryQPSettingsQpOffsetB,
  &cmdEntryQPSettingsQpMaxB,
  &cmdEntryQPSettingsQpMinB,
  NULL
};

MX_DBG_CMD_TABLE_T cmdTblIndexConfigVideoQPSettingsConfig =
{
  MX_DBG_ACCESS_ALL,
  sizeof(cmdListIndexConfigVideoQPSettingsConfig)/sizeof(cmdListIndexConfigVideoQPSettingsConfig[0]),
  cmdListIndexConfigVideoQPSettingsConfig
}; 
/*
 * <<< OMX_VIDEO_CONFIG_QPSETTINGSTYPE
 */
 
/*
 * >>> OMX_VIDEO_CONFIG_AVCINTRAPERIOD, OMX_IndexConfigVideoAVCIntraPeriod
 */ 
/* Entry for Set IDR - Intra period */

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryAVCIntraPeriodIDRPeriod =
{
  "nIDRPeriod",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_DEC          |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMX_VIDEO_CONFIG_AVCINTRAPERIOD,nIDRPeriod),
  FIELDOFFSET(OMX_VIDEO_CONFIG_AVCINTRAPERIOD,nSize) -
  FIELDOFFSET(OMX_VIDEO_CONFIG_AVCINTRAPERIOD,nIDRPeriod),
  0,
  OMTB_H264_VENC_MIN_I_FRM_INTERVAL,
  OMTB_H264_VENC_MAX_I_FRM_INTERVAL,
  OMTB_H264_VENC_DEF_I_FRM_INTERVAL,
  NULL,
  XdbgCmdVarFunc,
  "IDR period....................................",
  "<IDR Period>",
  "",
  ""
};


/* Entry for Set P - Inter period */

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryAVCIntraPeriodPFrames =
{
  "nPFrames",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_DEC          |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMX_VIDEO_CONFIG_AVCINTRAPERIOD,nPFrames),
  FIELDOFFSET(OMX_VIDEO_CONFIG_AVCINTRAPERIOD,nSize) -
  FIELDOFFSET(OMX_VIDEO_CONFIG_AVCINTRAPERIOD,nPFrames),
  0,
  OMTB_H264_VENC_MIN_I_FRM_INTERVAL,
  OMTB_H264_VENC_MAX_I_FRM_INTERVAL,
  OMTB_H264_VENC_DEF_I_FRM_INTERVAL,
  NULL,
  XdbgCmdVarFunc,
  "P frames period...............................",
  "<P Frames Inter Period>",
  "",
  ""
}; 

MX_DBG_CMD_ENTRY_T* cmdListIndexConfigVideoAVCIntraPeriodConfig[] =
{
  &cmdEntryAVCIntraPeriodIDRPeriod,
  &cmdEntryAVCIntraPeriodPFrames,
  NULL
};

MX_DBG_CMD_TABLE_T cmdTblIndexConfigVideoAVCIntraPeriodConfig =
{
  MX_DBG_ACCESS_ALL,
  sizeof(cmdListIndexConfigVideoAVCIntraPeriodConfig)/sizeof(cmdListIndexConfigVideoAVCIntraPeriodConfig[0]),
  cmdListIndexConfigVideoAVCIntraPeriodConfig
}; 

/*
 * <<< OMX_VIDEO_CONFIG_AVCINTRAPERIOD
 */ 
 
 
/*
 * >>> OMX_VIDEO_CONFIG_SLICECODINGTYPE, OMX_TI_IndexConfigSliceSettings
 */ 

/* Enum Entry for Supported slice mode type */

PRIVATE MX_DBG_ENUM_ENTRY_T enumTblSliceModeType[] =
{
  {"default",      OMX_VIDEO_SLICEMODE_AVCDefault,    ""},
  {"mbslice",      OMX_VIDEO_SLICEMODE_AVCMBSlice,    ""},
  {"byteslice",    OMX_VIDEO_SLICEMODE_AVCByteSlice,  ""},
  {"",             0,                                 ""}
};

/* Entry for Set slice mode type */

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntrySliceSettingsSliceMode =
{
  "eSliceMode",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_ENUM         |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMX_VIDEO_CONFIG_SLICECODINGTYPE,eSliceMode),
  FIELDOFFSET(OMX_VIDEO_CONFIG_SLICECODINGTYPE,nSize) -
  FIELDOFFSET(OMX_VIDEO_CONFIG_SLICECODINGTYPE,eSliceMode),
  0,
  OMX_VIDEO_SLICEMODE_AVCDefault,
  OMX_VIDEO_SLICEMODE_AVCLevelMax,
  OMX_VIDEO_SLICEMODE_AVCDefault,
  &enumTblSliceModeType,
  XdbgCmdVarFunc,
  "Slice Mode Type...............................",
  "",
  "",
  ""
};

/* Entry for Set slice size */

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntrySliceSettingsSliceSize =
{
  "nSlicesize",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_DEC          |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMX_VIDEO_CONFIG_SLICECODINGTYPE,nSlicesize),
  FIELDOFFSET(OMX_VIDEO_CONFIG_SLICECODINGTYPE,nSize) -
  FIELDOFFSET(OMX_VIDEO_CONFIG_SLICECODINGTYPE,nSlicesize),
  0,
  OMTB_MIN_VAL_U32,
  OMTB_H264_VENC_MAX_SLICE_SIZE,
  OMTB_H264_VENC_DEF_SLICE_SIZE,
  NULL,
  XdbgCmdVarFunc,
  "Slice Size....................................",
  "<Slice Size>",
  "",
  ""
};

MX_DBG_CMD_ENTRY_T* cmdListIndexConfigSliceSettingsConfig[] =
{
  &cmdEntrySliceSettingsSliceMode,
  &cmdEntrySliceSettingsSliceSize,
  NULL
};

MX_DBG_CMD_TABLE_T cmdTblIndexConfigSliceSettingsConfig =
{
  MX_DBG_ACCESS_ALL,
  sizeof(cmdListIndexConfigSliceSettingsConfig)/sizeof(cmdListIndexConfigSliceSettingsConfig[0]),
  cmdListIndexConfigSliceSettingsConfig
}; 
/*
 * <<< OMX_VIDEO_CONFIG_SLICECODINGTYPE
 */
 
 
/*
 * >>> OMX_VIDEO_CONFIG_PIXELINFOTYPE, OMX_TI_IndexConfigVideoPixelInfo
 */
/* Entry for Set Input Pixel Width */

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryPixelInfoWidth =
{
  "nWidth",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_DEC          |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMX_VIDEO_CONFIG_PIXELINFOTYPE,nWidth),
  FIELDOFFSET(OMX_VIDEO_CONFIG_PIXELINFOTYPE,nSize) -
  FIELDOFFSET(OMX_VIDEO_CONFIG_PIXELINFOTYPE,nWidth),
  0,
  OMTB_MIN_VAL_U32,
  OMTB_MAX_VID_WIDTH,
  OMTB_MAX_VID_WIDTH,
  NULL,
  XdbgCmdVarFunc,
  "Input Pixel Width.............................",
  "<Pixel Width>",
  "",
  ""
};


/* Entry for Set Input Pixel Height */

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryPixelInfoHeight =
{
  "nHeight",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_DEC          |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMX_VIDEO_CONFIG_PIXELINFOTYPE,nHeight),
  FIELDOFFSET(OMX_VIDEO_CONFIG_PIXELINFOTYPE,nSize) -
  FIELDOFFSET(OMX_VIDEO_CONFIG_PIXELINFOTYPE,nHeight),
  0,
  OMTB_MIN_VAL_U32,
  OMTB_MAX_VID_HEIGHT,
  OMTB_MAX_VID_HEIGHT,
  NULL,
  XdbgCmdVarFunc,
  "Input Pixel Height............................",
  "<Pixel Height>",
  "",
  ""
};

MX_DBG_CMD_ENTRY_T* cmdListIndexConfigVideoPixelInfoConfig[] =
{
  &cmdEntryPixelInfoWidth,
  &cmdEntryPixelInfoHeight,
  NULL
};

MX_DBG_CMD_TABLE_T cmdTblIndexConfigVideoPixelInfoConfig =
{
  MX_DBG_ACCESS_ALL,
  sizeof(cmdListIndexConfigVideoPixelInfoConfig)/sizeof(cmdListIndexConfigVideoPixelInfoConfig[0]),
  cmdListIndexConfigVideoPixelInfoConfig
}; 
/*
 * <<< OMX_VIDEO_CONFIG_PIXELINFOTYPE
 */

/*
 * >>> OMX_VIDEO_PARAM_AVCNALUCONTROLTYPE, OMX_TI_IndexParamVideoNALUsettings
 */
/* Entry for Set NALU SOS */

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryNaluStartOfSeq =
{
  "nStartofSequence",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_DEC          |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMX_VIDEO_PARAM_AVCNALUCONTROLTYPE,nStartofSequence),
  FIELDOFFSET(OMX_VIDEO_PARAM_AVCNALUCONTROLTYPE,nSize) -
  FIELDOFFSET(OMX_VIDEO_PARAM_AVCNALUCONTROLTYPE,nStartofSequence),
  0,
  OMTB_MIN_VAL_U32,
  OMTB_MAX_VAL_U32,
  OMTB_MIN_VAL_U32,
  NULL,
  XdbgCmdVarFunc,
  "NALU Start of Sequence........................",
  "<NALU Start Of Sequence>",
  "",
  ""
};


/* Entry for Set NALU EOS */

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryNaluEndOfSeq =
{
  "nEndofSequence",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_DEC          |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMX_VIDEO_PARAM_AVCNALUCONTROLTYPE,nEndofSequence),
  FIELDOFFSET(OMX_VIDEO_PARAM_AVCNALUCONTROLTYPE,nSize) -
  FIELDOFFSET(OMX_VIDEO_PARAM_AVCNALUCONTROLTYPE,nEndofSequence),
  0,
  OMTB_MIN_VAL_U32,
  OMTB_MAX_VAL_U32,
  OMTB_MIN_VAL_U32,
  NULL,
  XdbgCmdVarFunc,
  "NALU End of Sequence..........................",
  "<NALU End Of Sequence>",
  "",
  ""
};


/* Entry for Set NALU IDR frame number */

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryNaluIDR =
{
  "nIDR",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_DEC          |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMX_VIDEO_PARAM_AVCNALUCONTROLTYPE,nIDR),
  FIELDOFFSET(OMX_VIDEO_PARAM_AVCNALUCONTROLTYPE,nSize) -
  FIELDOFFSET(OMX_VIDEO_PARAM_AVCNALUCONTROLTYPE,nIDR),
  0,
  OMTB_MIN_VAL_U32,
  OMTB_MAX_VAL_U32,
  OMTB_MIN_VAL_U32,
  NULL,
  XdbgCmdVarFunc,
  "NALU IDR Frame #..............................",
  "<NALU IDR Frame #>",
  "",
  ""
};


/* Entry for Set NALU Intra picture number */

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryNaluIntraPicture =
{
  "nIntraPicture",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_DEC          |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMX_VIDEO_PARAM_AVCNALUCONTROLTYPE,nIntraPicture),
  FIELDOFFSET(OMX_VIDEO_PARAM_AVCNALUCONTROLTYPE,nSize) -
  FIELDOFFSET(OMX_VIDEO_PARAM_AVCNALUCONTROLTYPE,nIntraPicture),
  0,
  OMTB_MIN_VAL_U32,
  OMTB_MAX_VAL_U32,
  OMTB_MIN_VAL_U32,
  NULL,
  XdbgCmdVarFunc,
  "NALU Intra Picture #..........................",
  "<NALU Intra Picture #>",
  "",
  ""
};


/* Entry for Set NALU Non Intra picture number */

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryNaluNonIntraPicture =
{
  "nNonIntraPicture",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_DEC          |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMX_VIDEO_PARAM_AVCNALUCONTROLTYPE,nNonIntraPicture),
  FIELDOFFSET(OMX_VIDEO_PARAM_AVCNALUCONTROLTYPE,nSize) -
  FIELDOFFSET(OMX_VIDEO_PARAM_AVCNALUCONTROLTYPE,nNonIntraPicture),
  0,
  OMTB_MIN_VAL_U32,
  OMTB_MAX_VAL_U32,
  OMTB_MIN_VAL_U32,
  NULL,
  XdbgCmdVarFunc,
  "NALU Non Intra Picture #......................",
  "<NALU Non Intra Picture #>",
  "",
  ""
};

MX_DBG_CMD_ENTRY_T* cmdListIndexParamVideoNALUsettingsConfig[] =
{
  &cmdEntryNaluStartOfSeq,
  &cmdEntryNaluEndOfSeq,
  &cmdEntryNaluIDR,
  &cmdEntryNaluIntraPicture,
  &cmdEntryNaluNonIntraPicture,
  NULL
};

MX_DBG_CMD_TABLE_T cmdTblIndexParamVideoNALUsettingsConfig =
{
  MX_DBG_ACCESS_ALL,
  sizeof(cmdListIndexParamVideoNALUsettingsConfig)/sizeof(cmdListIndexParamVideoNALUsettingsConfig[0]),
  cmdListIndexParamVideoNALUsettingsConfig
}; 
/*
 * <<< OMX_VIDEO_PARAM_AVCNALUCONTROLTYPE
 */
 
 
/*
 * >>> OMX_VIDEO_PARAM_AVCADVANCEDFMOTYPE, OMX_TI_IndexParamVideoAdvancedFMO
 */
/* Entry for Set FMO Num Slice Groups */

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryAdvancedFMONumSliceGroups =
{
  "nNumSliceGroups",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_DEC          |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMX_VIDEO_PARAM_AVCADVANCEDFMOTYPE,nNumSliceGroups),
  FIELDOFFSET(OMX_VIDEO_PARAM_AVCADVANCEDFMOTYPE,nSize) -
  FIELDOFFSET(OMX_VIDEO_PARAM_AVCADVANCEDFMOTYPE,nNumSliceGroups),
  0,
  OMTB_MIN_VAL_U8,
  OMTB_MAX_VAL_U8,
  OMTB_MIN_VAL_U8,
  NULL,
  XdbgCmdVarFunc,
  "FMO Num Slice Groups..........................",
  "<FMO Num Slice Groups>",
  "",
  ""
};

/* Entry for Set FMO Slice Group Map Type */

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryAdvancedFMOSliceGroupMapType =
{
  "nSliceGroupMapType",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_DEC          |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMX_VIDEO_PARAM_AVCADVANCEDFMOTYPE,nSliceGroupMapType),
  FIELDOFFSET(OMX_VIDEO_PARAM_AVCADVANCEDFMOTYPE,nSize) -
  FIELDOFFSET(OMX_VIDEO_PARAM_AVCADVANCEDFMOTYPE,nSliceGroupMapType),
  0,
  OMTB_MIN_VAL_U8,
  OMTB_MAX_VAL_U8,
  OMTB_MIN_VAL_U8,
  NULL,
  XdbgCmdVarFunc,
  "FMO Slice Groups Map Type.....................",
  "<FMO Slice Groups Map Type>",
  "",
  ""
};


/* Enum Entry for Selecting Slice Group Change Direction */

PRIVATE MX_DBG_ENUM_ENTRY_T enumTblSliceGrpChangeDir[] =
{
  {"raster",        OMX_Video_Raster_Scan,          ""},
  {"clkwise",       OMX_Video_Clockwise,            ""},
  {"right",         OMX_Video_Right,                ""},
  {"rev_raster",    OMX_Video_Reverse_Raster_Scan,  ""},
  {"anti_clkwise",  OMX_Video_Counter_Clockwise,    ""},
  {"left",          OMX_Video_Left,                 ""},
  {"",              0,                              ""}
};


/* Entry for Set FMO Slice Group Change Direction */

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryAdvancedFMOSliceGrpChangeDir =
{
  "eSliceGrpChangeDir",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_ENUM         |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMX_VIDEO_PARAM_AVCADVANCEDFMOTYPE,eSliceGrpChangeDir),
  FIELDOFFSET(OMX_VIDEO_PARAM_AVCADVANCEDFMOTYPE,nSize) -
  FIELDOFFSET(OMX_VIDEO_PARAM_AVCADVANCEDFMOTYPE,eSliceGrpChangeDir),
  0,
  OMX_Video_Raster_Scan,
  OMX_Video_Left,
  OMX_Video_Raster_Scan,
  &enumTblSliceGrpChangeDir,
  XdbgCmdVarFunc,
  "FMO Slice Groups Change Direction.............",
  "",
  "",
  ""
};


/* Entry for Set FMO Slice Group Change Rate */

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryAdvancedFMOSliceGroupChangeRate =
{
  "nSliceGroupChangeRate",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_DEC          |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMX_VIDEO_PARAM_AVCADVANCEDFMOTYPE,nSliceGroupChangeRate),
  FIELDOFFSET(OMX_VIDEO_PARAM_AVCADVANCEDFMOTYPE,nSize) -
  FIELDOFFSET(OMX_VIDEO_PARAM_AVCADVANCEDFMOTYPE,nSliceGroupChangeRate),
  0,
  OMTB_MIN_VAL_U32,
  OMTB_MAX_VAL_U32,
  OMTB_MIN_VAL_U32,
  NULL,
  XdbgCmdVarFunc,
  "FMO Slice Groups Change Rate..................",
  "<FMO Slice Groups Change Rate>",
  "",
  ""
};


/* Entry for Set FMO Slice Group Change Cycle */

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryAdvancedFMOSliceGroupChangeCycle =
{
  "nSliceGroupChangeCycle",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_DEC          |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMX_VIDEO_PARAM_AVCADVANCEDFMOTYPE,nSliceGroupChangeCycle),
  FIELDOFFSET(OMX_VIDEO_PARAM_AVCADVANCEDFMOTYPE,nSize) -
  FIELDOFFSET(OMX_VIDEO_PARAM_AVCADVANCEDFMOTYPE,nSliceGroupChangeCycle),
  0,
  OMTB_MIN_VAL_U32,
  OMTB_MAX_VAL_U32,
  OMTB_MIN_VAL_U32,
  NULL,
  XdbgCmdVarFunc,
  "FMO Slice Groups Change Cycle.................",
  "<FMO Slice Groups Change Cycle>",
  "",
  ""
};

/* Entry for Set FMO Slice Group Param 0 */
//Need to chk in spec
PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryAdvancedFMOSliceGroupParams0 =
{
  "nSliceGroupParams.0",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_DEC          |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMX_VIDEO_PARAM_AVCADVANCEDFMOTYPE,nSliceGroupParams[0]),
  FIELDOFFSET(OMX_VIDEO_PARAM_AVCADVANCEDFMOTYPE,nSize) -
  FIELDOFFSET(OMX_VIDEO_PARAM_AVCADVANCEDFMOTYPE,nSliceGroupParams[0]),
  0,
  OMTB_MIN_VAL_U32,
  OMTB_MAX_VAL_U32,
  OMTB_MIN_VAL_U32,
  NULL,
  XdbgCmdVarFunc,
  "FMO Slice Groups Param 0......................",
  "<FMO Slice Groups Param 0>",
  "",
  ""
};


/* Entry for Set FMO Slice Group Param 1 */

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryAdvancedFMOSliceGroupParams1 =
{
  "nSliceGroupParams.1",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_DEC          |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMX_VIDEO_PARAM_AVCADVANCEDFMOTYPE,nSliceGroupParams[1]),
  FIELDOFFSET(OMX_VIDEO_PARAM_AVCADVANCEDFMOTYPE,nSize) -
  FIELDOFFSET(OMX_VIDEO_PARAM_AVCADVANCEDFMOTYPE,nSliceGroupParams[1]),
  0,
  OMTB_MIN_VAL_U32,
  OMTB_MAX_VAL_U32,
  OMTB_MIN_VAL_U32,
  NULL,
  XdbgCmdVarFunc,
  "FMO Slice Groups Param 1......................",
  "<FMO Slice Groups Param 1>",
  "",
  ""
};


MX_DBG_CMD_ENTRY_T* cmdListIndexParamVideoAdvancedFMOConfig[] =
{
  &cmdEntryAdvancedFMONumSliceGroups,
  &cmdEntryAdvancedFMOSliceGroupMapType,
  &cmdEntryAdvancedFMOSliceGrpChangeDir,
  &cmdEntryAdvancedFMOSliceGroupChangeRate,
  &cmdEntryAdvancedFMOSliceGroupChangeCycle,
  &cmdEntryAdvancedFMOSliceGroupParams0,
  &cmdEntryAdvancedFMOSliceGroupParams1,
  NULL
};

MX_DBG_CMD_TABLE_T cmdTblIndexParamVideoAdvancedFMOConfig =
{
  MX_DBG_ACCESS_ALL,
  sizeof(cmdListIndexParamVideoAdvancedFMOConfig)/sizeof(cmdListIndexParamVideoAdvancedFMOConfig[0]),
  cmdListIndexParamVideoAdvancedFMOConfig
}; 
/*
 * <<< OMX_VIDEO_PARAM_AVCADVANCEDFMOTYPE
 */
 
 
/*
 * >>> OMX_VIDEO_PARAM_MEBLOCKSIZETYPE, OMX_TI_IndexParamVideoMEBlockSize
 */
/* Enum Entry for Selecting Minimum Block Size */

PRIVATE MX_DBG_ENUM_ENTRY_T enumTblMEMinBlockSize[] =
{
  {"16x16", OMX_Video_Block_Size_16x16, ""},
  {"8x8",   OMX_Video_Block_Size_8x8,   ""},
  {"8x4",   OMX_Video_Block_Size_8x4,   ""},
  {"4x8",   OMX_Video_Block_Size_4x8,   ""},
  {"4x4",   OMX_Video_Block_Size_4x4,   ""},
  {"",      0,            ""}
};


/* Entry for Set ME block size - P frame */

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryMEMinBlockSizeP =
{
  "eMinBlockSizeP",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_ENUM         |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMX_VIDEO_PARAM_MEBLOCKSIZETYPE,eMinBlockSizeP),
  FIELDOFFSET(OMX_VIDEO_PARAM_MEBLOCKSIZETYPE,nSize) -
  FIELDOFFSET(OMX_VIDEO_PARAM_MEBLOCKSIZETYPE,eMinBlockSizeP),
  0,
  OMX_Video_Block_Size_16x16,
  OMX_Video_Block_Size_4x4,
  OMX_Video_Block_Size_16x16,
  &enumTblMEMinBlockSize,
  XdbgCmdVarFunc,
  "ME Min Block Size - P Frame...................",
  "",
  "",
  ""
};

/* Entry for Set ME block size - B frame */

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryMEMinBlockSizeB =
{
  "eMinBlockSizeB",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_ENUM         |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMX_VIDEO_PARAM_MEBLOCKSIZETYPE,eMinBlockSizeB),
  FIELDOFFSET(OMX_VIDEO_PARAM_MEBLOCKSIZETYPE,nSize) -
  FIELDOFFSET(OMX_VIDEO_PARAM_MEBLOCKSIZETYPE,eMinBlockSizeB),
  0,
  OMX_Video_Block_Size_16x16,
  OMX_Video_Block_Size_4x4,
  OMX_Video_Block_Size_16x16,
  &enumTblMEMinBlockSize,
  XdbgCmdVarFunc,
  "ME Min Block Size - B Frame...................",
  "",
  "",
  ""
};

MX_DBG_CMD_ENTRY_T* cmdListIndexParamVideoMEBlockSizeConfig[] =
{
  &cmdEntryMEMinBlockSizeP,
  &cmdEntryMEMinBlockSizeB,
  NULL
};

MX_DBG_CMD_TABLE_T cmdTblIndexParamVideoMEBlockSizeConfig =
{
  MX_DBG_ACCESS_ALL,
  sizeof(cmdListIndexParamVideoMEBlockSizeConfig)/sizeof(cmdListIndexParamVideoMEBlockSizeConfig[0]),
  cmdListIndexParamVideoMEBlockSizeConfig
}; 
/*
 * <<< OMX_VIDEO_PARAM_MEBLOCKSIZETYPE
 */
 
 
/*
 * >>> OMX_VIDEO_PARAM_INTRAREFRESHTYPE, OMX_IndexParamVideoIntraRefresh
 */
/* Enum Entry for Selecting Intra Refresh Mode */

PRIVATE MX_DBG_ENUM_ENTRY_T enumTblIntraRefreshMode[] =
{
  {"cyclic",    OMX_VIDEO_IntraRefreshCyclic,   ""},
  {"adaptive",  OMX_VIDEO_IntraRefreshAdaptive, ""},
  {"both",      OMX_VIDEO_IntraRefreshBoth,     ""},
  {"",          0,                              ""}
};


/* Entry for Set Intra refresh period */

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryIntraRefreshMode =
{
  "eRefreshMode",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_ENUM         |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMX_VIDEO_PARAM_INTRAREFRESHTYPE,eRefreshMode),
  FIELDOFFSET(OMX_VIDEO_PARAM_INTRAREFRESHTYPE,nSize) -
  FIELDOFFSET(OMX_VIDEO_PARAM_INTRAREFRESHTYPE,eRefreshMode),
  0,
  OMX_VIDEO_IntraRefreshCyclic,
  OMX_VIDEO_IntraRefreshMax,
  OMX_VIDEO_IntraRefreshBoth,
  &enumTblIntraRefreshMode,
  XdbgCmdVarFunc,
  "Intra Refresh Mode............................",
  "",
  "",
  ""
};


/* Entry for Set Number of intra macroblocks to refresh in a frame when AIR
   is enabled */

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryIntraRefreshAirMBs =
{
  "nAirMBs",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_DEC          |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMX_VIDEO_PARAM_INTRAREFRESHTYPE,nAirMBs),
  FIELDOFFSET(OMX_VIDEO_PARAM_INTRAREFRESHTYPE,nSize) -
  FIELDOFFSET(OMX_VIDEO_PARAM_INTRAREFRESHTYPE,nAirMBs),
  0,
  OMTB_MIN_VAL_U32,
  OMTB_H264_VENC_MAX_NUM_MB,
  OMTB_MIN_VAL_U32,
  NULL,
  XdbgCmdVarFunc,
  "# of Intra MBs to be Refreshed................",
  "<# of Intra MBs to be Refreshed>",
  "",
  ""
};


/* Entry for Set Number of times a motion marked macroblock has to be intra
   coded */

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryIntraRefreshAirRef =
{
  "nAirRef",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_DEC          |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMX_VIDEO_PARAM_INTRAREFRESHTYPE,nAirRef),
  FIELDOFFSET(OMX_VIDEO_PARAM_INTRAREFRESHTYPE,nSize) -
  FIELDOFFSET(OMX_VIDEO_PARAM_INTRAREFRESHTYPE,nAirRef),
  0,
  OMTB_MIN_VAL_U32,
  OMTB_MAX_VAL_U32,
  OMTB_MIN_VAL_U32,
  NULL,
  XdbgCmdVarFunc,
  "# of times Motion marked MB be Intra Coded....",
  "<# of times Motion marked MB to be Intra Coded>",
  "",
  ""
};


/* Entry for Set Number of consecutive macroblocks to be coded as intra when
   CIR is enabled */

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryIntraRefreshCirMBs =
{
  "nCirMBs",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_DEC          |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMX_VIDEO_PARAM_INTRAREFRESHTYPE,nCirMBs),
  FIELDOFFSET(OMX_VIDEO_PARAM_INTRAREFRESHTYPE,nSize) -
  FIELDOFFSET(OMX_VIDEO_PARAM_INTRAREFRESHTYPE,nCirMBs),
  0,
  OMTB_MIN_VAL_U32,
  OMTB_H264_VENC_MAX_NUM_MB,
  OMTB_MIN_VAL_U32,
  NULL,
  XdbgCmdVarFunc,
  "# of Consecutive MBs to be Intra Coded........",
  "<# of Consecutive MBs to be Intra Coded>",
  "",
  ""
};

MX_DBG_CMD_ENTRY_T* cmdListIndexParamVideoIntraRefreshConfig[] =
{
  &cmdEntryIntraRefreshMode,
  &cmdEntryIntraRefreshAirMBs,
  &cmdEntryIntraRefreshAirRef,  
  &cmdEntryIntraRefreshCirMBs,
  NULL
};

MX_DBG_CMD_TABLE_T cmdTblIndexParamVideoIntraRefreshConfig =
{
  MX_DBG_ACCESS_ALL,
  sizeof(cmdListIndexParamVideoIntraRefreshConfig)/sizeof(cmdListIndexParamVideoIntraRefreshConfig[0]),
  cmdListIndexParamVideoIntraRefreshConfig
}; 
/*
 * <<< OMX_VIDEO_PARAM_INTRAREFRESHTYPE
 */
 
 
 
/*
 * >>> OMX_VIDEO_PARAM_VUIINFOTYPE, OMX_TI_IndexParamVideoVUIsettings
 */
/* Entry for Set Aspect Ratio Present Falg */

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryVUIAspectRatioPresent =
{
  "bAspectRatioPresent",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_ENUM         |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMX_VIDEO_PARAM_VUIINFOTYPE,bAspectRatioPresent),
  FIELDOFFSET(OMX_VIDEO_PARAM_VUIINFOTYPE,nSize) -
  FIELDOFFSET(OMX_VIDEO_PARAM_VUIINFOTYPE,bAspectRatioPresent),
  0,
  OMX_FALSE,
  OMX_TRUE,
  OMX_FALSE,
  &enumTblOnOff,
  XdbgCmdVarFunc,
  "VUI Aspect Ratio Present Flag.................",
  "",
  "",
  ""
};


/* Enum Entry for Selecting Pixel Aspect Ratio */

PRIVATE MX_DBG_ENUM_ENTRY_T enumTblPixelAspectRatio[] =
{
  {"none",    OMX_Video_AR_Unspecified, ""},
  {"1x1",     OMX_Video_AR_Square,      ""},
  {"12x11",   OMX_Video_AR_12_11,       ""},
  {"10x11",   OMX_Video_AR_10_11,       ""},
  {"16x11",   OMX_Video_AR_16_11,       ""},
  {"40x33",   OMX_Video_AR_40_33,       ""},
  {"24x11",   OMX_Video_AR_24_11,       ""},
  {"20x11",   OMX_Video_AR_20_11,       ""},
  {"32x11",   OMX_Video_AR_32_11,       ""},
  {"80x33",   OMX_Video_AR_80_33,       ""},
  {"18x11",   OMX_Video_AR_18_11,       ""},
  {"15x15",   OMX_Video_AR_15_15,       ""},
  {"64x33",   OMX_Video_AR_64_33,       ""},
  {"160x99",  OMX_Video_AR_160_99,      ""},
  {"4x3",     OMX_Video_AR_4_3,         ""},
  {"3x2",     OMX_Video_AR_3_2,         ""},
  {"2x1",     OMX_Video_AR_2_1,         ""},
  {"",        0,                        ""}
};


/* Entry for Set Pixel Aspect Ratio */

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryVUIPixelAspectRatio =
{
  "ePixelAspectRatio",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_ENUM         |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMX_VIDEO_PARAM_VUIINFOTYPE,ePixelAspectRatio),
  FIELDOFFSET(OMX_VIDEO_PARAM_VUIINFOTYPE,nSize) -
  FIELDOFFSET(OMX_VIDEO_PARAM_VUIINFOTYPE,ePixelAspectRatio),
  0,
  OMX_Video_AR_Unspecified,
  OMX_Video_AR_Extended,
  OMX_Video_AR_4_3,
  &enumTblPixelAspectRatio,
  XdbgCmdVarFunc,
  "VUI Pixel Aspect Ratio........................",
  "",
  "",
  ""
};


/* Entry for Set Pixel Value Range is Full Range or not */

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryVUIFullRange =
{
  "bFullRange",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_ENUM         |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMX_VIDEO_PARAM_VUIINFOTYPE,bFullRange),
  FIELDOFFSET(OMX_VIDEO_PARAM_VUIINFOTYPE,nSize) -
  FIELDOFFSET(OMX_VIDEO_PARAM_VUIINFOTYPE,bFullRange),
  0,
  OMX_FALSE,
  OMX_TRUE,
  OMX_FALSE,
  &enumTblOnOff,
  XdbgCmdVarFunc,
  "VUI Pixel Value Full Range Flag...............",
  "",
  "",
  ""
};


MX_DBG_CMD_ENTRY_T* cmdListIndexParamVideoVUIsettingsConfig[] =
{
  &cmdEntryVUIAspectRatioPresent,
  &cmdEntryVUIPixelAspectRatio,
  &cmdEntryVUIFullRange,
  NULL
};

MX_DBG_CMD_TABLE_T cmdTblIndexParamVideoVUIsettingsConfig =
{
  MX_DBG_ACCESS_ALL,
  sizeof(cmdListIndexParamVideoVUIsettingsConfig)/sizeof(cmdListIndexParamVideoVUIsettingsConfig[0]),
  cmdListIndexParamVideoVUIsettingsConfig
}; 
/*
 * <<< OMX_VIDEO_PARAM_VUIINFOTYPE
 */

 
/*
 * >>> OMX_VIDEO_PARAM_INTRAPREDTYPE, OMX_TI_IndexParamVideoIntraPredictionSettings
 */
/* Entry for Set 4x4 Luma Intra Modes */

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryIntraPredLumaIntra4x4Enable =
{
  "nLumaIntra4x4Enable",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_DEC          |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMX_VIDEO_PARAM_INTRAPREDTYPE,nLumaIntra4x4Enable),
  FIELDOFFSET(OMX_VIDEO_PARAM_INTRAPREDTYPE,nSize) -
  FIELDOFFSET(OMX_VIDEO_PARAM_INTRAPREDTYPE,nLumaIntra4x4Enable),
  0,
  OMTB_MIN_VAL_U32,
  OMTB_H264_VENC_MAX_LUMA_INTRA_4x4_PRED,
  OMTB_H264_VENC_DEF_LUMA_INTRA_4x4_PRED,
  NULL,
  XdbgCmdVarFunc,
  "Luma Intra 4x4 Pred Modes Enabled.............",
  "<0x000 to 0x1FF - (Bit positions (MSB to LSB): \
HOR_UP|VER_LEFT|HOR_DOWN|VER_RIGHT|DIAG_DOWN_RIGHT|DIAG_DOWN_LEFT|DC|HOR|VER)>",
  "",
  ""
};


/* Entry for Set 8x8 Luma Intra Modes */

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryIntraPredLumaIntra8x8Enable =
{
  "nLumaIntra8x8Enable",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_DEC          |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMX_VIDEO_PARAM_INTRAPREDTYPE,nLumaIntra8x8Enable),
  FIELDOFFSET(OMX_VIDEO_PARAM_INTRAPREDTYPE,nSize) -
  FIELDOFFSET(OMX_VIDEO_PARAM_INTRAPREDTYPE,nLumaIntra8x8Enable),
  0,
  OMTB_MIN_VAL_U32,
  OMTB_H264_VENC_MAX_LUMA_INTRA_8x8_PRED,
  OMTB_H264_VENC_DEF_LUMA_INTRA_8x8_PRED,
  NULL,
  XdbgCmdVarFunc,
  "Luma Intra 8x8 Pred Modes Enabled.............",
  "<0x000 to 0x1FF - (Bit positions (MSB to LSB): \
HOR_UP|VER_LEFT|HOR_DOWN|VER_RIGHT|DIAG_DOWN_RIGHT|DIAG_DOWN_LEFT|DC|HOR|VER)>",
  "",
  ""
};


/* Entry for Set 16x16 Luma Intra Modes */

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryIntraPredLumaIntra16x16Enable =
{
  "nLumaIntra16x16Enable",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_DEC          |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMX_VIDEO_PARAM_INTRAPREDTYPE,nLumaIntra16x16Enable),
  FIELDOFFSET(OMX_VIDEO_PARAM_INTRAPREDTYPE,nSize) -
  FIELDOFFSET(OMX_VIDEO_PARAM_INTRAPREDTYPE,nLumaIntra16x16Enable),
  0,
  OMTB_MIN_VAL_U32,
  OMTB_H264_VENC_MAX_LUMA_INTRA_16x16_PRED,
  OMTB_H264_VENC_DEF_LUMA_INTRA_16x16_PRED,
  NULL,
  XdbgCmdVarFunc,
  "Luma Intra 16x16 Pred Modes Enabled...........",
  "<0x00 to 0x0F - (Bit positions (MSB to LSB): \
PLANE|DC|HOR|VER>",
  "",
  ""
};


/* Entry for Set 8x8 Chroma Intra Modes */

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryIntraPredChromaIntra8x8Enable =
{
  "nChromaIntra8x8Enable",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_DEC          |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMX_VIDEO_PARAM_INTRAPREDTYPE,nChromaIntra8x8Enable),
  FIELDOFFSET(OMX_VIDEO_PARAM_INTRAPREDTYPE,nSize) -
  FIELDOFFSET(OMX_VIDEO_PARAM_INTRAPREDTYPE,nChromaIntra8x8Enable),
  0,
  OMTB_MIN_VAL_U32,
  OMTB_H264_VENC_MAX_CHROMA_INTRA_8x8_PRED,
  OMTB_H264_VENC_DEF_CHROMA_INTRA_8x8_PRED,
  NULL,
  XdbgCmdVarFunc,
  "Chroma Intra 8x8 Pred Modes Enabled...........",
  "<0x00 to 0x0F - (Bit positions (MSB to LSB): \
PLANE|DC|HOR|VER>",
  "",
  ""
};


/* Enum Entry for Selecting chroma component */

PRIVATE MX_DBG_ENUM_ENTRY_T enumTblIntraPredChromaComponentEnable[] =
{
  {"cr_only",     OMX_Video_Chroma_Component_Cr_Only,     ""},
  {"cb_cr_both",  OMX_Video_Chroma_Component_Cb_Cr_Both,  ""},
  {"",            0,                                      ""}
};


/* Entry for Set Pixel Aspect Ratio */

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryIntraPredChromaComponentEnable =
{
  "eChromaComponentEnable",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_ENUM         |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMX_VIDEO_PARAM_INTRAPREDTYPE,eChromaComponentEnable),
  FIELDOFFSET(OMX_VIDEO_PARAM_INTRAPREDTYPE,nSize) -
  FIELDOFFSET(OMX_VIDEO_PARAM_INTRAPREDTYPE,eChromaComponentEnable),
  0,
  OMX_Video_Chroma_Component_Cr_Only,
  OMX_Video_Chroma_Component_Cb_Cr_Both,
  OMX_Video_Chroma_Component_Cr_Only,
  &enumTblIntraPredChromaComponentEnable,
  XdbgCmdVarFunc,
  "Chroma Intra Component........................",
  "",
  "",
  ""
};
 
MX_DBG_CMD_ENTRY_T* cmdListIndexParamVideoIntraPredictionSettingsConfig[] =
{
  &cmdEntryIntraPredLumaIntra4x4Enable,
  &cmdEntryIntraPredLumaIntra8x8Enable,
  &cmdEntryIntraPredLumaIntra16x16Enable,
  &cmdEntryIntraPredChromaIntra8x8Enable,
  &cmdEntryIntraPredChromaComponentEnable,
  NULL
};

MX_DBG_CMD_TABLE_T cmdTblIndexParamVideoIntraPredictionSettingsConfig =
{
  MX_DBG_ACCESS_ALL,
  sizeof(cmdListIndexParamVideoIntraPredictionSettingsConfig)/sizeof(cmdListIndexParamVideoIntraPredictionSettingsConfig[0]),
  cmdListIndexParamVideoIntraPredictionSettingsConfig
}; 
/*
 * <<< OMX_VIDEO_PARAM_INTRAPREDTYPE
 */
 
 
 /*
 * >>> OMX_VIDEO_PARAM_DATASYNCMODETYPE, OMX_TI_IndexParamVideoDataSyncMode
 */
/* Enum Entry for Selecting Video Data Mode */

PRIVATE MX_DBG_ENUM_ENTRY_T enumTblVidDataMode[] =
{
  {"fixed_length",  OMX_Video_FixedLength,  ""},
  {"slice",         OMX_Video_SliceMode,    ""},
  {"num_mb_rows",   OMX_Video_NumMBRows,    ""},
  {"frame",         OMX_Video_EntireFrame,  ""},
  {"",              0,                      ""}
};


/* Entry for Set Vid Num Data Units */

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryVidDataMode =
{
  "eDataMode",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_ENUM         |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMX_VIDEO_PARAM_DATASYNCMODETYPE,eDataMode),
  FIELDOFFSET(OMX_VIDEO_PARAM_DATASYNCMODETYPE,nSize) -
  FIELDOFFSET(OMX_VIDEO_PARAM_DATASYNCMODETYPE,eDataMode),
  0,
  OMX_Video_FixedLength,
  OMX_Video_EntireFrame,
  OMX_Video_EntireFrame,
  &enumTblVidDataMode,
  XdbgCmdVarFunc,
  "Video Data Mode...............................",
  "",
  "",
  ""
};


/* Entry for Set Vid Num Data Units */

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryVidDataModeNumDataUnits =
{
  "nNumDataUnits",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_DEC          |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMX_VIDEO_PARAM_DATASYNCMODETYPE,nNumDataUnits),
  FIELDOFFSET(OMX_VIDEO_PARAM_DATASYNCMODETYPE,nSize) -
  FIELDOFFSET(OMX_VIDEO_PARAM_DATASYNCMODETYPE,nNumDataUnits),
  0,
  OMTB_MIN_VAL_U32,
  OMTB_MAX_VAL_U32,
  OMTB_MIN_VAL_U32,
  NULL,
  XdbgCmdVarFunc,
  "Video Num Data Units..........................",
  "<Video Num Data Units>",
  "",
  ""
};

 MX_DBG_CMD_ENTRY_T* cmdListIndexParamVideoDataSyncModeConfig[] =
{
  &cmdEntryVidDataMode,
  &cmdEntryVidDataModeNumDataUnits,
  NULL
};

MX_DBG_CMD_TABLE_T cmdTblIndexParamVideoDataSyncModeConfig =
{
  MX_DBG_ACCESS_ALL,
  sizeof(cmdListIndexParamVideoDataSyncModeConfig)/sizeof(cmdListIndexParamVideoDataSyncModeConfig[0]),
  cmdListIndexParamVideoDataSyncModeConfig
}; 
 /*
 * <<< OMX_VIDEO_PARAM_DATASYNCMODETYPE
 */
 
 
/*
 * >>> OMX_VIDEO_PARAM_AVCTYPE, OMX_IndexParamVideoAvc
 */
 
 /* Enum Entry for Supported AVC profiles */

PRIVATE MX_DBG_ENUM_ENTRY_T enumTblProfile[] =
{
  {"baseline",  OMX_VIDEO_AVCProfileBaseline, ""},
  {"main",      OMX_VIDEO_AVCProfileMain, ""},
  {"extended",  OMX_VIDEO_AVCProfileExtended, ""},
  {"high",      OMX_VIDEO_AVCProfileHigh, ""},
  {"high10",    OMX_VIDEO_AVCProfileHigh10, ""},
  {"high422",   OMX_VIDEO_AVCProfileHigh422, ""},
  {"high444",   OMX_VIDEO_AVCProfileHigh444, ""},
  {"", 0, ""}
};


/* Enum Entry for Supported AVC levels */

PRIVATE MX_DBG_ENUM_ENTRY_T enumTblLevel[] =
{
  {"1",     OMX_VIDEO_AVCLevel1, ""},
  {"1.0",   OMX_VIDEO_AVCLevel1, ""},
  {"1b",    OMX_VIDEO_AVCLevel1b, ""},
  {"1.1",   OMX_VIDEO_AVCLevel11, ""},
  {"1.2",   OMX_VIDEO_AVCLevel12, ""},
  {"1.3",   OMX_VIDEO_AVCLevel13, ""},
  {"2",     OMX_VIDEO_AVCLevel2, ""},
  {"2.0",   OMX_VIDEO_AVCLevel2, ""},
  {"2.1",   OMX_VIDEO_AVCLevel21, ""},
  {"2.2",   OMX_VIDEO_AVCLevel22, ""},
  {"3",     OMX_VIDEO_AVCLevel3, ""},
  {"3.0",   OMX_VIDEO_AVCLevel3, ""},
  {"3.1",   OMX_VIDEO_AVCLevel31, ""},
  {"3.2",   OMX_VIDEO_AVCLevel32, ""},
  {"4",     OMX_VIDEO_AVCLevel4, ""},
  {"4.0",   OMX_VIDEO_AVCLevel4, ""},
  {"4.1",   OMX_VIDEO_AVCLevel41, ""},
  {"4.2",   OMX_VIDEO_AVCLevel42, ""},
  {"5",     OMX_VIDEO_AVCLevel5, ""},
  {"5.0",   OMX_VIDEO_AVCLevel5, ""},
  {"5.1",   OMX_VIDEO_AVCLevel51, ""},
  {"", 0, ""}
};

/* Entry for Set num MBs between slice headers */

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryAVCParamSliceHeaderSpacing =
{
  "nSliceHeaderSpacing",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_DEC          |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMX_VIDEO_PARAM_AVCTYPE,nSliceHeaderSpacing),
  FIELDOFFSET(OMX_VIDEO_PARAM_AVCTYPE,nSize) -
  FIELDOFFSET(OMX_VIDEO_PARAM_AVCTYPE,nSliceHeaderSpacing),
  0,
  OMTB_MIN_VAL_U32,
  OMTB_H264_VENC_MAX_NUM_MB,
  OMTB_H264_VENC_DEF_SLICE_HDR_SPACING,
  NULL,
  XdbgCmdVarFunc,
  "Num MBs Between Slice Header..................",
  "<# of MBs Between Slice Header>",
  "",
  ""
};


/* Entry for Set max P frame between each I frames */

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryAVCParamPFrames =
{
  "nPFrames",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_DEC          |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMX_VIDEO_PARAM_AVCTYPE,nPFrames),
  FIELDOFFSET(OMX_VIDEO_PARAM_AVCTYPE,nSize) -
  FIELDOFFSET(OMX_VIDEO_PARAM_AVCTYPE,nPFrames),
  0,
  OMTB_H264_VENC_MIN_P_FRM_INTERVAL,
  OMTB_H264_VENC_MAX_P_FRM_INTERVAL,
  OMTB_H264_VENC_DEF_P_FRM_INTERVAL,
  NULL,
  XdbgCmdVarFunc,
  "Max # of P Frames between each I Frames.......",
  "<Max # of P Frames between each I Frames>",
  "",
  ""
};


/* Entry for Set max B frame between each I frames */

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryAVCParamBFrames =
{
  "nBFrames",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_DEC          |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMX_VIDEO_PARAM_AVCTYPE,nBFrames),
  FIELDOFFSET(OMX_VIDEO_PARAM_AVCTYPE,nSize) -
  FIELDOFFSET(OMX_VIDEO_PARAM_AVCTYPE,nBFrames),
  0,
  OMTB_H264_VENC_MIN_B_FRM_INTERVAL,
  OMTB_H264_VENC_MAX_B_FRM_INTERVAL,
  OMTB_H264_VENC_DEF_B_FRM_INTERVAL,
  NULL,
  XdbgCmdVarFunc,
  "Max # of B Frames between each I Frames.......",
  "<Max # of B Frames between each I Frames>",
  "",
  ""
};


/* Entry for Set hadamard transform */

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryAVCParamUseHadamard =
{
  "bUseHadamard",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_ENUM         |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMX_VIDEO_PARAM_AVCTYPE,bUseHadamard),
  FIELDOFFSET(OMX_VIDEO_PARAM_AVCTYPE,nSize) -
  FIELDOFFSET(OMX_VIDEO_PARAM_AVCTYPE,bUseHadamard),
  0,
  OMX_FALSE,
  OMX_TRUE,
  OMX_FALSE,
  &enumTblOnOff,
  XdbgCmdVarFunc,
  "Hadamard Transform............................",
  "",
  "",
  ""
};


/* Entry for Set num refrence frames */

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryAVCParamRefFrames =
{
  "nRefFrames",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_DEC          |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMX_VIDEO_PARAM_AVCTYPE,nRefFrames),
  FIELDOFFSET(OMX_VIDEO_PARAM_AVCTYPE,nSize) -
  FIELDOFFSET(OMX_VIDEO_PARAM_AVCTYPE,nRefFrames),
  0,
  OMTB_H264_VENC_MIN_NUM_REF_FRM,
  OMTB_H264_VENC_MAX_NUM_REF_FRM,
  OMTB_H264_VENC_DEF_NUM_REF_FRM,
  NULL,
  XdbgCmdVarFunc,
  "# of Refrence Frames..........................",
  "<# of Refrence Frames>",
  "",
  ""
};


/* Entry for Set index in ref frm buffer of trailing frames list */

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryAVCParamRefIdx10ActiveMinus1 =
{
  "nRefIdx10ActiveMinus1",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_DEC          |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMX_VIDEO_PARAM_AVCTYPE,nRefIdx10ActiveMinus1),
  FIELDOFFSET(OMX_VIDEO_PARAM_AVCTYPE,nSize) -
  FIELDOFFSET(OMX_VIDEO_PARAM_AVCTYPE,nRefIdx10ActiveMinus1),
  0,
  OMTB_MIN_VAL_U32,
  OMTB_MAX_VAL_U32,
  OMTB_H264_VENC_DEF_REF_IDX_10,
  NULL,
  XdbgCmdVarFunc,
  "Refrence Index in Bwd Frames list.............",
  "<Refrence Index in Bwd Frames list>",
  "",
  ""
};


/* Entry for Set index in ref frm buffer of forward frames list */

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryAVCParamRefIdx11ActiveMinus1 =
{
  "nRefIdx11ActiveMinus1",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_DEC          |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMX_VIDEO_PARAM_AVCTYPE,nRefIdx11ActiveMinus1),
  FIELDOFFSET(OMX_VIDEO_PARAM_AVCTYPE,nSize) -
  FIELDOFFSET(OMX_VIDEO_PARAM_AVCTYPE,nRefIdx11ActiveMinus1),
  0,
  OMTB_MIN_VAL_U32,
  OMTB_MAX_VAL_U32,
  OMTB_H264_VENC_DEF_REF_IDX_11,
  NULL,
  XdbgCmdVarFunc,
  "Refrence Index in Fwd Frames list.............",
  "<Refrence Index in Fwd Frames list>",
  "",
  ""
};


/* Entry for Set UEP flag */

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryAVCParamEnableUEP =
{
  "bEnableUEP",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_ENUM         |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMX_VIDEO_PARAM_AVCTYPE,bEnableUEP),
  FIELDOFFSET(OMX_VIDEO_PARAM_AVCTYPE,nSize) -
  FIELDOFFSET(OMX_VIDEO_PARAM_AVCTYPE,bEnableUEP),
  0,
  OMX_FALSE,
  OMX_TRUE,
  OMX_FALSE,
  &enumTblOnOff,
  XdbgCmdVarFunc,
  "Unequal Error Protection......................",
  "",
  "",
  ""
};


/* Entry for Set FMO */

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryAVCParamFMO =
{
  "bEnableFMO",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_ENUM         |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMX_VIDEO_PARAM_AVCTYPE,bEnableFMO),
  FIELDOFFSET(OMX_VIDEO_PARAM_AVCTYPE,nSize) -
  FIELDOFFSET(OMX_VIDEO_PARAM_AVCTYPE,bEnableFMO),
  0,
  OMX_FALSE,
  OMX_TRUE,
  OMX_FALSE,
  &enumTblOnOff,
  XdbgCmdVarFunc,
  "Flexible Macroblock Ordering..................",
  "",
  "",
  ""
};


/* Entry for Set ASO flag */

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryAVCParamEnableASO =
{
  "bEnableASO",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_ENUM         |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMX_VIDEO_PARAM_AVCTYPE,bEnableASO),
  FIELDOFFSET(OMX_VIDEO_PARAM_AVCTYPE,nSize) -
  FIELDOFFSET(OMX_VIDEO_PARAM_AVCTYPE,bEnableASO),
  0,
  OMX_FALSE,
  OMX_TRUE,
  OMX_FALSE,
  &enumTblOnOff,
  XdbgCmdVarFunc,
  "Arbitrary Slice Ordering......................",
  "",
  "",
  ""
};


/* Entry for Set RS flag */

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryAVCParamEnableRS =
{
  "bEnableRS",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_ENUM         |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMX_VIDEO_PARAM_AVCTYPE,bEnableRS),
  FIELDOFFSET(OMX_VIDEO_PARAM_AVCTYPE,nSize) -
  FIELDOFFSET(OMX_VIDEO_PARAM_AVCTYPE,bEnableRS),
  0,
  OMX_FALSE,
  OMX_TRUE,
  OMX_FALSE,
  &enumTblOnOff,
  XdbgCmdVarFunc,
  "Redundant Slices..............................",
  "",
  "",
  ""
};


/* Entry for Set AVC profile */

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryAVCParamProfile =
{
  "eProfile",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_ENUM         |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMX_VIDEO_PARAM_AVCTYPE,eProfile),
  FIELDOFFSET(OMX_VIDEO_PARAM_AVCTYPE,nSize) -
  FIELDOFFSET(OMX_VIDEO_PARAM_AVCTYPE,eProfile),
  0,
  OMX_VIDEO_AVCProfileBaseline,
  OMX_VIDEO_AVCProfileMax,
  OMX_VIDEO_AVCProfileBaseline,
  &enumTblProfile,
  XdbgCmdVarFunc,
  "AVC Profile...................................",
  "",
  "",
  ""
};


/* Entry for Set AVC level */

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryAVCParamLevel =
{
  "eLevel",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_ENUM         |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMX_VIDEO_PARAM_AVCTYPE,eLevel),
  FIELDOFFSET(OMX_VIDEO_PARAM_AVCTYPE,nSize) -
  FIELDOFFSET(OMX_VIDEO_PARAM_AVCTYPE,eLevel),
  0,
  OMX_VIDEO_AVCLevel1,
  OMX_VIDEO_AVCLevelMax,
  OMX_VIDEO_AVCLevel1,
  &enumTblLevel,
  XdbgCmdVarFunc,
  "AVC Level.....................................",
  "",
  "",
  ""
};


/* Entry for Set picture types allowed in bitstream */

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryAVCParamAllowedPictureTypes =
{
  "nAllowedPictureTypes",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_DEC          |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMX_VIDEO_PARAM_AVCTYPE,nAllowedPictureTypes),
  FIELDOFFSET(OMX_VIDEO_PARAM_AVCTYPE,nSize) -
  FIELDOFFSET(OMX_VIDEO_PARAM_AVCTYPE,nAllowedPictureTypes),
  0,
  OMTB_MIN_VAL_U32,
  OMTB_MAX_VAL_U32,
  OMTB_H264_VENC_DEF_ALLOWED_PIC_TYPE,
  NULL,
  XdbgCmdVarFunc,
  "Picture Types Allowed In Bitstream............",
  "<Picture Types Allowed In Bitstream>",
  "",
  ""
};


/* Entry for Set Frame MBs only flag */

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryAVCParamFrameMBsOnly =
{
  "bFrameMBsOnly",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_ENUM         |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMX_VIDEO_PARAM_AVCTYPE,bFrameMBsOnly),
  FIELDOFFSET(OMX_VIDEO_PARAM_AVCTYPE,nSize) -
  FIELDOFFSET(OMX_VIDEO_PARAM_AVCTYPE,bFrameMBsOnly),
  0,
  OMX_FALSE,
  OMX_TRUE,
  OMX_FALSE,
  &enumTblOnOff,
  XdbgCmdVarFunc,
  "Frame MBs Only................................",
  "",
  "",
  ""
};


/* Entry for Set Frame feild MB switching flag */

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryAVCParamMBAFF =
{
  "bMBAFF",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_ENUM         |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMX_VIDEO_PARAM_AVCTYPE,bMBAFF),
  FIELDOFFSET(OMX_VIDEO_PARAM_AVCTYPE,nSize) -
  FIELDOFFSET(OMX_VIDEO_PARAM_AVCTYPE,bMBAFF),
  0,
  OMX_FALSE,
  OMX_TRUE,
  OMX_FALSE,
  &enumTblOnOff,
  XdbgCmdVarFunc,
  "Frame Field MB Switching......................",
  "",
  "",
  ""
};


/* Entry for Set CABAC mode */

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryAVCParamCABAC =
{
  "bEntropyCodingCABAC",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_ENUM         |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMX_VIDEO_PARAM_AVCTYPE,bEntropyCodingCABAC),
  FIELDOFFSET(OMX_VIDEO_PARAM_AVCTYPE,nSize) -
  FIELDOFFSET(OMX_VIDEO_PARAM_AVCTYPE,bEntropyCodingCABAC),
  0,
  OMX_FALSE,
  OMX_TRUE,
  OMX_FALSE,
  &enumTblOnOff,
  XdbgCmdVarFunc,
  "CABAC.........................................",
  "",
  "",
  ""
};


/* Entry for Set Weighted Prediction flag for P frames */

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryAVCParamWeightedPPrediction =
{
  "bWeightedPPrediction",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_ENUM         |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMX_VIDEO_PARAM_AVCTYPE,bWeightedPPrediction),
  FIELDOFFSET(OMX_VIDEO_PARAM_AVCTYPE,nSize) -
  FIELDOFFSET(OMX_VIDEO_PARAM_AVCTYPE,bWeightedPPrediction),
  0,
  OMX_FALSE,
  OMX_TRUE,
  OMX_FALSE,
  &enumTblOnOff,
  XdbgCmdVarFunc,
  "Weighted Prediction for P frames..............",
  "",
  "",
  ""
};


/* Entry for Set weighted Biprediction modes */

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryAVCParamWeightedBipredicitonMode =
{
  "nWeightedBipredicitonMode",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_DEC          |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMX_VIDEO_PARAM_AVCTYPE,nWeightedBipredicitonMode),
  FIELDOFFSET(OMX_VIDEO_PARAM_AVCTYPE,nSize) -
  FIELDOFFSET(OMX_VIDEO_PARAM_AVCTYPE,nWeightedBipredicitonMode),
  0,
  OMTB_MIN_VAL_U32,
  OMTB_MAX_VAL_U32,
  OMTB_H264_VENC_DEF_WEIGHTED_BIPRED_MODE,
  NULL,
  XdbgCmdVarFunc,
  "Weighted Biprediciton Mode....................",
  "<Weighted Biprediciton Mode>",
  "",
  ""
};


/* Entry for Set Constrained Intra Prediction */

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryAVCParamConstIntraPred =
{
  "bconstIpred",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_ENUM         |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMX_VIDEO_PARAM_AVCTYPE,bconstIpred),
  FIELDOFFSET(OMX_VIDEO_PARAM_AVCTYPE,nSize) -
  FIELDOFFSET(OMX_VIDEO_PARAM_AVCTYPE,bconstIpred),
  0,
  OMX_FALSE,
  OMX_TRUE,
  OMX_FALSE,
  &enumTblOnOff,
  XdbgCmdVarFunc,
  "Constrained Intra Prediction..................",
  "",
  "",
  ""
};


/* Entry for Set Method used for Luma motion vector for B_Skip, B_Direct_16x16
   and B_Direct_8x8 */

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryAVCParamDirect8x8Inference =
{
  "bDirect8x8Inference",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_ENUM         |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMX_VIDEO_PARAM_AVCTYPE,bDirect8x8Inference),
  FIELDOFFSET(OMX_VIDEO_PARAM_AVCTYPE,nSize) -
  FIELDOFFSET(OMX_VIDEO_PARAM_AVCTYPE,bDirect8x8Inference),
  0,
  OMX_FALSE,
  OMX_TRUE,
  OMX_FALSE,
  &enumTblOnOff,
  XdbgCmdVarFunc,
  "Luma Motion Vector Method for B Frames........",
  "",
  "",
  ""
};


/* Entry for Set Weighted Prediction flag for P frames */

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryAVCParamDirectSpatialTemporal =
{
  "bDirectSpatialTemporal",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_ENUM         |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMX_VIDEO_PARAM_AVCTYPE,bDirectSpatialTemporal),
  FIELDOFFSET(OMX_VIDEO_PARAM_AVCTYPE,nSize) -
  FIELDOFFSET(OMX_VIDEO_PARAM_AVCTYPE,bDirectSpatialTemporal),
  0,
  OMX_FALSE,
  OMX_TRUE,
  OMX_FALSE,
  &enumTblOnOff,
  XdbgCmdVarFunc,
  "Spatial/Temporal mode for B Frame Coding......",
  "",
  "",
  ""
};


/* Entry for Set weighted Biprediction modes */

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryAVCParamCabacInitIdc =
{
  "nCabacInitIdc",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_DEC          |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMX_VIDEO_PARAM_AVCTYPE,nCabacInitIdc),
  FIELDOFFSET(OMX_VIDEO_PARAM_AVCTYPE,nSize) -
  FIELDOFFSET(OMX_VIDEO_PARAM_AVCTYPE,nCabacInitIdc),
  0,
  OMTB_MIN_VAL_U32,
  OMTB_MAX_VAL_U32,
  OMTB_H264_VENC_DEF_CABAC_INIT_IDX,
  NULL,
  XdbgCmdVarFunc,
  "CABAC Context Init Index......................",
  "<CABAC Context Init Index>",
  "",
  ""
};


/* Enum Entry for enabling or disabling flag */

PRIVATE MX_DBG_ENUM_ENTRY_T enumTblAVCParamLoopFilter[] =
{
  {"enable",                  OMX_VIDEO_AVCLoopFilterEnable,                ""},
  {"disable",                 OMX_VIDEO_AVCLoopFilterDisable,               ""},
  {"disable_slice_boundary",  OMX_VIDEO_AVCLoopFilterDisableSliceBoundary,  ""},
  {"",                        0,                                            ""}
};


/* Entry for Set loop filter */

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryAVCParamLoopFilter =
{
  "eLoopFilterMode",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_ENUM         |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMX_VIDEO_PARAM_AVCTYPE,eLoopFilterMode),
  FIELDOFFSET(OMX_VIDEO_PARAM_AVCTYPE,nSize) -
  FIELDOFFSET(OMX_VIDEO_PARAM_AVCTYPE,eLoopFilterMode),
  0,
  OMX_VIDEO_AVCLoopFilterEnable,
  OMX_VIDEO_AVCLoopFilterMax,
  OMX_VIDEO_AVCLoopFilterDisable,
  &enumTblAVCParamLoopFilter,
  XdbgCmdVarFunc,
  "Loop Filter Mode..............................",
  "",
  "",
  ""
};

MX_DBG_CMD_ENTRY_T* cmdListIndexParamVideoAvcConfig[] =
{
  &cmdEntryAVCParamSliceHeaderSpacing,
  &cmdEntryAVCParamPFrames,
  &cmdEntryAVCParamBFrames,
  &cmdEntryAVCParamUseHadamard,
  &cmdEntryAVCParamRefFrames,
  &cmdEntryAVCParamRefIdx10ActiveMinus1,
  &cmdEntryAVCParamRefIdx11ActiveMinus1,
  &cmdEntryAVCParamEnableUEP,
  &cmdEntryAVCParamFMO,
  &cmdEntryAVCParamEnableASO,
  &cmdEntryAVCParamEnableRS,
  &cmdEntryAVCParamProfile,
  &cmdEntryAVCParamLevel,
  &cmdEntryAVCParamAllowedPictureTypes,
  &cmdEntryAVCParamFrameMBsOnly,
  &cmdEntryAVCParamMBAFF,
  &cmdEntryAVCParamCABAC,
  &cmdEntryAVCParamWeightedPPrediction,
  &cmdEntryAVCParamWeightedBipredicitonMode,
  &cmdEntryAVCParamConstIntraPred,
  &cmdEntryAVCParamDirect8x8Inference,
  &cmdEntryAVCParamDirectSpatialTemporal,
  &cmdEntryAVCParamCabacInitIdc,
  &cmdEntryAVCParamLoopFilter,
  NULL
};

MX_DBG_CMD_TABLE_T cmdTblIndexParamVideoAvcConfig =
{
  MX_DBG_ACCESS_ALL,
  sizeof(cmdListIndexParamVideoAvcConfig)/sizeof(cmdListIndexParamVideoAvcConfig[0]),
  cmdListIndexParamVideoAvcConfig
}; 

/*
 * <<< OMX_VIDEO_PARAM_AVCTYPE
 */
 
 
 
 /*
 * >>> OMX_VIDEO_PARAM_BITRATETYPE, OMX_IndexParamVideoBitrate
 */ 
 
 /* Entry for Set Bitrate */
PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryTargetBitrate =
{
  "nTargetBitrate",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_DEC          |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMX_VIDEO_PARAM_BITRATETYPE,nTargetBitrate),
  FIELDOFFSET(OMX_VIDEO_PARAM_BITRATETYPE,nSize) -
  FIELDOFFSET(OMX_VIDEO_PARAM_BITRATETYPE,nTargetBitrate),
  0,
  0,
  OMTB_MAX_VAL_U32,
  OMTB_H264_VENC_DEF_BIT_RATE,
  NULL,
  XdbgCmdVarFunc,
  "Param Bitrate.................................",
  "<bitrate>",
  "",
  ""
};

/* Enum Entry for Supported rate control algorithm */
PRIVATE MX_DBG_ENUM_ENTRY_T enumTblRateCtrlAlg[] =
{
  {"disable",         OMX_Video_ControlRateDisable,             ""},
  {"variable",        OMX_Video_ControlRateVariable,            ""},
  {"constant",        OMX_Video_ControlRateConstant,            ""},
  {"var_frm_skip",    OMX_Video_ControlRateVariableSkipFrames,  ""},
  {"const_frm_skip",  OMX_Video_ControlRateConstantSkipFrames,  ""},
  {"",                0,                                        ""}
};

/* Entry for Set rate control algorithm */
PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryParamRateCtrlAlg =
{
  "eControlRate",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_ENUM         |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMX_VIDEO_PARAM_BITRATETYPE,eControlRate),
  FIELDOFFSET(OMX_VIDEO_PARAM_BITRATETYPE,nSize) -
  FIELDOFFSET(OMX_VIDEO_PARAM_BITRATETYPE,eControlRate),
  0,
  OMX_Video_ControlRateDisable,
  OMX_Video_ControlRateMax,
  OMX_Video_ControlRateDisable,
  &enumTblRateCtrlAlg,
  XdbgCmdVarFunc,
  "Param Rate Control Algorithm..................",
  "",
  "",
  ""
};
 
MX_DBG_CMD_ENTRY_T* cmdListIndexParamVideoBitrateConfig[] =
{
  &cmdEntryTargetBitrate,
  &cmdEntryParamRateCtrlAlg,
  NULL
};
  
MX_DBG_CMD_TABLE_T cmdTblIndexParamVideoBitrateConfig =
{
  MX_DBG_ACCESS_ALL,
  sizeof(cmdListIndexParamVideoBitrateConfig)/sizeof(cmdListIndexParamVideoBitrateConfig[0]),
  cmdListIndexParamVideoBitrateConfig
};
 /*
 * <<< OMX_VIDEO_PARAM_BITRATETYPE
 */

/*
 * >>> OMX_VIDEO_PARAM_PROFILELEVELTYPE, OMX_IndexParamVideoProfileLevelCurrent
 */
/* Entry for Set Profile */

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryProfile =
{
  "eProfile",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_ENUM         |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMX_VIDEO_PARAM_PROFILELEVELTYPE,eProfile),
  FIELDOFFSET(OMX_VIDEO_PARAM_PROFILELEVELTYPE,nSize) -
  FIELDOFFSET(OMX_VIDEO_PARAM_PROFILELEVELTYPE,eProfile),
  0,
  OMX_VIDEO_AVCProfileBaseline,
  OMX_VIDEO_AVCProfileMax,
  OMX_VIDEO_AVCProfileBaseline,
  &enumTblProfile,
  XdbgCmdVarFunc,
  "Profile.......................................",
  "",
  "",
  ""
};


/* Entry for Set level */

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryLevel =
{
  "eLevel",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_ENUM         |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMX_VIDEO_PARAM_PROFILELEVELTYPE,eLevel),
  FIELDOFFSET(OMX_VIDEO_PARAM_PROFILELEVELTYPE,nSize) -
  FIELDOFFSET(OMX_VIDEO_PARAM_PROFILELEVELTYPE,eLevel),
  0,
  OMX_VIDEO_AVCLevel1,
  OMX_VIDEO_AVCLevelMax,
  OMX_VIDEO_AVCLevel1,
  &enumTblLevel,
  XdbgCmdVarFunc,
  "Level.........................................",
  "",
  "",
  ""
};

MX_DBG_CMD_ENTRY_T* cmdListIndexParamVideoProfileLevelCurrentConfig[] =
{
  &cmdEntryProfile,
  &cmdEntryLevel,
  NULL
};

MX_DBG_CMD_TABLE_T cmdTblIndexParamVideoProfileLevelCurrentConfig =
{
  MX_DBG_ACCESS_ALL,
  sizeof(cmdListIndexParamVideoProfileLevelCurrentConfig)/sizeof(cmdListIndexParamVideoProfileLevelCurrentConfig[0]),
  cmdListIndexParamVideoProfileLevelCurrentConfig
}; 

/*
 * <<< OMX_VIDEO_PARAM_PROFILELEVELTYPE
 */
 
 
/*
 * OMX_VIDEO_PARAM_AVCBITSTREAMFORMATTYPE, OMX_TI_IndexParamVideoBitStreamFormatSelect
 */
/* Enum Entry for Supported bitstream format */

PRIVATE MX_DBG_ENUM_ENTRY_T enumTblBitStrmFmt[] =
{
  {"byte",   OMX_Video_BitStreamFormatByte, ""},
  {"nal",    OMX_Video_BitStreamFormatNAL, ""},
  {"", 0, ""}
};


/* Entry for Set bitstream format */

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryBitStrmFmt =
{
  "eStreamFormat",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_ENUM          |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMX_VIDEO_PARAM_AVCBITSTREAMFORMATTYPE,eStreamFormat),
  FIELDOFFSET(OMX_VIDEO_PARAM_AVCBITSTREAMFORMATTYPE,nSize) -
  FIELDOFFSET(OMX_VIDEO_PARAM_AVCBITSTREAMFORMATTYPE,eStreamFormat),
  0,
  OMX_Video_BitStreamFormatByte,
  OMX_Video_BitStreamFormatNAL,
  OMX_Video_BitStreamFormatByte,
  &enumTblBitStrmFmt,
  XdbgCmdVarFunc,
  "Bitstream Format..............................",
  "",
  "",
  ""
};

MX_DBG_CMD_ENTRY_T* cmdListIndexParamVideoBitStreamFormatSelectConfig[] =
{
  &cmdEntryBitStrmFmt,
  NULL
};

MX_DBG_CMD_TABLE_T cmdTblIndexParamVideoBitStreamFormatSelectConfig =
{
  MX_DBG_ACCESS_ALL,
  sizeof(cmdListIndexParamVideoBitStreamFormatSelectConfig)/sizeof(cmdListIndexParamVideoBitStreamFormatSelectConfig[0]),
  cmdListIndexParamVideoBitStreamFormatSelectConfig
}; 

/*
 * <<< OMX_VIDEO_PARAM_AVCBITSTREAMFORMATTYPE
 */
 
/*
 * >>> OMX_VIDEO_PARAM_ENCODER_PRESETTYPE, OMX_TI_IndexParamVideoEncoderPreset
 */
/* Enum Entry for Supported encoding preset settings */

PRIVATE MX_DBG_ENUM_ENTRY_T enumTblEncodingModePreset[] =
{
  {"default",   OMX_Video_Enc_Default,                ""},
  {"hq",        OMX_Video_Enc_High_Quality,           ""},
  {"userdef",   OMX_Video_Enc_User_Defined,           ""},
  {"hsmq",      OMX_Video_Enc_High_Speed_Med_Quality, ""},
  {"msmq",      OMX_Video_Enc_Med_Speed_Med_Quality,  ""},
  {"mshq",      OMX_Video_Enc_Med_Speed_High_Quality, ""},
  {"hs",        OMX_Video_Enc_High_Speed,             ""},
  {"",          0,                                    ""}
};


/* Entry for Set encoding preset setting */

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryEncodingModePreset =
{
  "eEncodingModePreset",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_ENUM         |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMX_VIDEO_PARAM_ENCODER_PRESETTYPE,eEncodingModePreset),
  FIELDOFFSET(OMX_VIDEO_PARAM_ENCODER_PRESETTYPE,nSize) -
  FIELDOFFSET(OMX_VIDEO_PARAM_ENCODER_PRESETTYPE,eEncodingModePreset),
  0,
  OMX_Video_Enc_Default,
  OMX_Video_Enc_High_Speed,
  OMX_Video_Enc_Default,
  &enumTblEncodingModePreset,
  XdbgCmdVarFunc,
  "Encoder Preset................................",
  "",
  "",
  ""
};


/* Enum Entry for Supported rate control settings */

PRIVATE MX_DBG_ENUM_ENTRY_T enumTblRateCtrlPreset[] =
{
  {"default",   OMX_Video_RC_Low_Delay,     ""},
  {"hq",        OMX_Video_RC_Storage,       ""},
  {"userdef",   OMX_Video_RC_Twopass,       ""},
  {"hsmq",      OMX_Video_RC_None,          ""},
  {"msmq",      OMX_Video_RC_User_Defined,  ""},
  {"",          0,                          ""}
};


/* Entry for Set rate control setting */

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryRateCtrlPreset =
{
  "eRateControlPreset",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_ENUM         |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMX_VIDEO_PARAM_ENCODER_PRESETTYPE,eRateControlPreset),
  FIELDOFFSET(OMX_VIDEO_PARAM_ENCODER_PRESETTYPE,nSize) -
  FIELDOFFSET(OMX_VIDEO_PARAM_ENCODER_PRESETTYPE,eRateControlPreset),
  0,
  OMX_Video_RC_Low_Delay,
  OMX_Video_RC_User_Defined,
  OMX_Video_RC_None,
  &enumTblRateCtrlPreset,
  XdbgCmdVarFunc,
  "Rate Control Preset...........................",
  "",
  "",
  ""
}; 

MX_DBG_CMD_ENTRY_T* cmdListIndexParamVideoEncoderPresetConfig[] =
{
  &cmdEntryEncodingModePreset,
  &cmdEntryRateCtrlPreset,
  NULL
};

MX_DBG_CMD_TABLE_T cmdTblIndexParamVideoEncoderPresetConfig =
{
  MX_DBG_ACCESS_ALL,
  sizeof(cmdListIndexParamVideoEncoderPresetConfig)/sizeof(cmdListIndexParamVideoEncoderPresetConfig[0]),
  cmdListIndexParamVideoEncoderPresetConfig
}; 

/*
 * <<< OMX_VIDEO_PARAM_ENCODER_PRESETTYPE
 */


/*
 * >>> OMX_VIDEO_PARAM_FRAMEDATACONTENTTYPE, OMX_TI_IndexParamVideoFrameDataContentSettings
 */
/* Enum Entry for Supported I/P frame content type */

PRIVATE MX_DBG_ENUM_ENTRY_T enumTblContentType[] =
{
  {"progressive", OMX_Video_Progressive,            ""},
  {"interlaced",  OMX_Video_Interlaced,             ""},
  {"topfld",      OMX_Video_Interlaced_Topfield,    ""},
  {"botfld",      OMX_Video_Interlaced_Bottomfield, ""},
  {"",            0,                                ""}
};


/* Entry for Set I/P frame content type */

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryInFrmContentType =
{
  "eContentType",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_ENUM         |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMX_VIDEO_PARAM_FRAMEDATACONTENTTYPE,eContentType),
  FIELDOFFSET(OMX_VIDEO_PARAM_FRAMEDATACONTENTTYPE,nSize) -
  FIELDOFFSET(OMX_VIDEO_PARAM_FRAMEDATACONTENTTYPE,eContentType),
  0,
  OMX_Video_Progressive,
  OMX_Video_Interlaced_Bottomfield,
  OMX_Video_Progressive,
  &enumTblContentType,
  XdbgCmdVarFunc,
  "Input Content Type............................",
  "",
  "",
  ""
};


/* Enum Entry for Supported interlace coding type */

PRIVATE MX_DBG_ENUM_ENTRY_T enumTblInterlacedCodingType[] =
{
  {"picaff",      OMX_Video_Interlace_PICAFF,         ""},
  {"mbaff",       OMX_Video_Interlace_MBAFF,          ""},
  {"fldonly",     OMX_Video_Interlace_Fieldonly,      ""},
  {"fldonly_mrf", OMX_Video_Interlace_Fieldonly_MRF,  ""},
  {"fldonly_arf", OMX_Video_Interlace_Fieldonly_ARF,  ""},
  {"fldonly_spf", OMX_Video_Interlace_Fieldonly_SPF,  ""},
  {"", 0, ""}
};


/* Entry for Set interlace coding type */

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryInterlacedCodingType =
{
  "eInterlaceCodingType",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_ENUM         |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMX_VIDEO_PARAM_FRAMEDATACONTENTTYPE,eInterlaceCodingType),
  FIELDOFFSET(OMX_VIDEO_PARAM_FRAMEDATACONTENTTYPE,nSize) -
  FIELDOFFSET(OMX_VIDEO_PARAM_FRAMEDATACONTENTTYPE,eInterlaceCodingType),
  0,
  OMX_Video_Interlace_PICAFF,
  OMX_Video_Interlace_Fieldonly_SPF,
  OMX_Video_Interlace_PICAFF,
  &enumTblInterlacedCodingType,
  XdbgCmdVarFunc,
  "Interlace Coding Type.........................",
  "",
  "",
  ""
};

MX_DBG_CMD_ENTRY_T* cmdListIndexParamVideoFrameDataContentSettingsConfig[] =
{
  &cmdEntryInFrmContentType,
  &cmdEntryInterlacedCodingType,
  NULL
};

MX_DBG_CMD_TABLE_T cmdTblIndexParamVideoFrameDataContentSettingsConfig =
{
  MX_DBG_ACCESS_ALL,
  sizeof(cmdListIndexParamVideoFrameDataContentSettingsConfig)/sizeof(cmdListIndexParamVideoFrameDataContentSettingsConfig[0]),
  cmdListIndexParamVideoFrameDataContentSettingsConfig
}; 

/*
 * <<< OMX_VIDEO_PARAM_FRAMEDATACONTENTTYPE
 */
 
 
/*
 * >>> OMX_VIDEO_PARAM_TRANSFORM_BLOCKSIZETYPE, OMX_TI_IndexParamVideoTransformBlockSize
 */
/* Enum Entry for Supported transform blk size */

PRIVATE MX_DBG_ENUM_ENTRY_T enumTblTransformBlkSize[] =
{
  {"4x4",       OMX_Video_Transform_Block_Size_4x4,       ""},
  {"8x8",       OMX_Video_Transform_Block_Size_8x8,       ""},
  {"adaptive",  OMX_Video_Transform_Block_Size_Adaptive,  ""},
  {"",          0,                                        ""}
};


/* Entry for Set transform blk size */

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryTransformBlkSize =
{
  "eTransformBlocksize",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_ENUM         |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMX_VIDEO_PARAM_TRANSFORM_BLOCKSIZETYPE,eTransformBlocksize),
  FIELDOFFSET(OMX_VIDEO_PARAM_TRANSFORM_BLOCKSIZETYPE,nSize) -
  FIELDOFFSET(OMX_VIDEO_PARAM_TRANSFORM_BLOCKSIZETYPE,eTransformBlocksize),
  0,
  OMX_Video_Transform_Block_Size_4x4,
  OMX_Video_Transform_Block_Size_Adaptive,
  OMX_Video_Transform_Block_Size_4x4,
  &enumTblTransformBlkSize,
  XdbgCmdVarFunc,
  "Transform Block Size..........................",
  "",
  "",
  ""
};

MX_DBG_CMD_ENTRY_T* cmdListIndexParamVideoTransformBlockSizeConfig[] =
{
  &cmdEntryTransformBlkSize,
  NULL
};

MX_DBG_CMD_TABLE_T cmdTblIndexParamVideoTransformBlockSizeConfig =
{
  MX_DBG_ACCESS_ALL,
  sizeof(cmdListIndexParamVideoTransformBlockSizeConfig)/sizeof(cmdListIndexParamVideoTransformBlockSizeConfig[0]),
  cmdListIndexParamVideoTransformBlockSizeConfig
}; 

/*
 * <<< OMX_VIDEO_PARAM_TRANSFORM_BLOCKSIZETYPE
 */
 
 
/*
 * >>> OMX_VIDEO_PARAM_AVCSLICEFMO, OMX_IndexParamVideoSliceFMO
 */
/* Entry for Set num slice groups */

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryFMONumSliceGrp =
{
  "nNumSliceGroups",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_DEC          |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMX_VIDEO_PARAM_AVCSLICEFMO,nNumSliceGroups),
  FIELDOFFSET(OMX_VIDEO_PARAM_AVCSLICEFMO,nSize) -
  FIELDOFFSET(OMX_VIDEO_PARAM_AVCSLICEFMO,nNumSliceGroups),
  0,
  OMTB_MIN_VAL_U8,
  OMTB_MAX_VAL_U8,
  OMTB_H264_VENC_DEF_NUM_SLICE_GRP,
  NULL,
  XdbgCmdVarFunc,
  "Num Slice Group...............................",
  "<Slice Group #>",
  "",
  ""
};


/* Entry for Set slice group map type */

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryFMOSliceGrpMapType =
{
  "nSliceGroupMapType",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_DEC          |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMX_VIDEO_PARAM_AVCSLICEFMO,nSliceGroupMapType),
  FIELDOFFSET(OMX_VIDEO_PARAM_AVCSLICEFMO,nSize) -
  FIELDOFFSET(OMX_VIDEO_PARAM_AVCSLICEFMO,nSliceGroupMapType),
  0,
  OMTB_MIN_VAL_U8,
  OMTB_MAX_VAL_U8,
  OMTB_H264_VENC_DEF_SLICE_GRP_MAP_TYPE,
  NULL,
  XdbgCmdVarFunc,
  "Slice Group map type..........................",
  "<Slice Group Map Type>",
  "",
  ""
};


/* Entry for Set slice mode type */

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryFMOSliceModeType =
{
  "eSliceMode",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_ENUM         |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMX_VIDEO_PARAM_AVCSLICEFMO,eSliceMode),
  FIELDOFFSET(OMX_VIDEO_PARAM_AVCSLICEFMO,nSize) -
  FIELDOFFSET(OMX_VIDEO_PARAM_AVCSLICEFMO,eSliceMode),
  0,
  OMX_VIDEO_SLICEMODE_AVCDefault,
  OMX_VIDEO_SLICEMODE_AVCLevelMax,
  OMX_VIDEO_SLICEMODE_AVCDefault,
  &enumTblSliceModeType,
  XdbgCmdVarFunc,
  "Slice Mode Type...............................",
  "",
  "",
  ""
};

MX_DBG_CMD_ENTRY_T* cmdListIndexParamVideoSliceFMOConfig[] =
{
  &cmdEntryFMONumSliceGrp,
  &cmdEntryFMOSliceGrpMapType,
  &cmdEntryFMOSliceModeType,
  NULL
};

MX_DBG_CMD_TABLE_T cmdTblIndexParamVideoSliceFMOConfig =
{
  MX_DBG_ACCESS_ALL,
  sizeof(cmdListIndexParamVideoSliceFMOConfig)/sizeof(cmdListIndexParamVideoSliceFMOConfig[0]),
  cmdListIndexParamVideoSliceFMOConfig
}; 
/*
 * <<< OMX_VIDEO_PARAM_AVCSLICEFMO
 */
 
/*
 * >>> OMX_VIDEO_PARAM_MOTIONVECTORTYPE, OMX_IndexParamVideoMotionVector
 */ 
/* Entry for Setting Unrestricted MVs */

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryUMV =
{
  "bUnrestrictedMVs",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_ENUM         |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMX_VIDEO_PARAM_MOTIONVECTORTYPE,bUnrestrictedMVs),
  FIELDOFFSET(OMX_VIDEO_PARAM_MOTIONVECTORTYPE,nSize) -
  FIELDOFFSET(OMX_VIDEO_PARAM_MOTIONVECTORTYPE,bUnrestrictedMVs),
  0,
  OMX_FALSE,
  OMX_TRUE,
  OMX_TRUE,
  &enumTblOnOff,
  XdbgCmdVarFunc,
  "Unrestricted Motion Vector....................",
  "",
  "",
  ""
};

/* Entry for Setting Four MVs */

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryFourMV =
{
  "bFourMV",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_ENUM         |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMX_VIDEO_PARAM_MOTIONVECTORTYPE,bFourMV),
  FIELDOFFSET(OMX_VIDEO_PARAM_MOTIONVECTORTYPE,nSize) -
  FIELDOFFSET(OMX_VIDEO_PARAM_MOTIONVECTORTYPE,bFourMV),
  0,
  OMX_FALSE,
  OMX_TRUE,
  OMX_TRUE,
  &enumTblOnOff,
  XdbgCmdVarFunc,
  "Four Motion Vectors...........................",
  "",
  "",
  ""
};

/* Entry for Setting Motion Vector Search Range - X */

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryMVXSearchRange =
{
  "sXSearchRange",
  MX_DBG_CMD_TYPE_VAR_SINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_DEC          |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMX_VIDEO_PARAM_MOTIONVECTORTYPE,sXSearchRange),
  FIELDOFFSET(OMX_VIDEO_PARAM_MOTIONVECTORTYPE,nSize) -
  FIELDOFFSET(OMX_VIDEO_PARAM_MOTIONVECTORTYPE,sXSearchRange),
  0,
  -(OMTB_MAX_VID_WIDTH),
  OMTB_MAX_VID_WIDTH,
  OMTB_H264_VENC_DEF_MVSR_X,
  NULL,
  XdbgCmdVarFunc,
  "Motion Vector X Search Range .................",
  "",
  "",
  ""
};


/* Entry for Setting Motion Vector Search Range - Y */

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryMVYSearchRange =
{
  "sYSearchRange",
  MX_DBG_CMD_TYPE_VAR_SINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_DEC          |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMX_VIDEO_PARAM_MOTIONVECTORTYPE,sYSearchRange),
  FIELDOFFSET(OMX_VIDEO_PARAM_MOTIONVECTORTYPE,nSize) -
  FIELDOFFSET(OMX_VIDEO_PARAM_MOTIONVECTORTYPE,sYSearchRange),
  0,
  -(OMTB_MAX_VID_WIDTH),
  OMTB_MAX_VID_WIDTH,
  OMTB_H264_VENC_DEF_MVSR_Y,
  NULL,
  XdbgCmdVarFunc,
  "Motion Vector Y Search Range .................",
  "",
  "",
  ""
};

MX_DBG_CMD_ENTRY_T* cmdListIndexParamVideoMotionVectorConfig[] =
{
  &cmdEntryUMV,
  &cmdEntryFourMV,
  &cmdEntryMVXSearchRange,
  &cmdEntryMVYSearchRange,
  NULL
};

MX_DBG_CMD_TABLE_T cmdTblIndexParamVideoMotionVectorConfig =
{
  MX_DBG_ACCESS_ALL,
  sizeof(cmdListIndexParamVideoMotionVectorConfig)/sizeof(cmdListIndexParamVideoMotionVectorConfig[0]),
  cmdListIndexParamVideoMotionVectorConfig
}; 
/*
 * <<< OMX_VIDEO_PARAM_MOTIONVECTORTYPE
 */
 
/*
 * >>> OMX_VIDEO_CONFIG_NALSIZE, OMX_IndexConfigVideoNalSize
 */
/* Entry for set start port number */

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryNalBytes =
{
  "nNaluBytes",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_DEC          |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMX_VIDEO_CONFIG_NALSIZE,nNaluBytes),
  FIELDOFFSET(OMX_VIDEO_CONFIG_NALSIZE,nSize) -
  FIELDOFFSET(OMX_VIDEO_CONFIG_NALSIZE,nNaluBytes),
  0,
  0,
  OMTB_MAX_VAL_U32,
  0,
  NULL,
  XdbgCmdVarFunc,
  "NAL bytes .....................................",
  "<No of bytes of data in NAL Units>",
  "",
  ""
};

MX_DBG_CMD_ENTRY_T* cmdListIndexConfigVideoNalSizeConfig[] =
{
  &cmdEntryNalBytes,
  NULL
};

MX_DBG_CMD_TABLE_T cmdTblIndexConfigVideoNalSizeConfig =
{
  MX_DBG_ACCESS_ALL,
  sizeof(cmdListIndexConfigVideoNalSizeConfig)/sizeof(cmdListIndexConfigVideoNalSizeConfig[0]),
  cmdListIndexConfigVideoNalSizeConfig
}; 
/*
 * <<< OMX_VIDEO_CONFIG_NALSIZE
 */
 
/*
 * >>> OMX_CONFIG_MBERRORREPORTINGTYPE, OMX_IndexConfigVideoMacroBlockErrorMap
 */ 
 
/* Entry for Set MB Error Reporting Type Enable Flag */

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryMbErrorReportingTypeEnable =
{
  "bEnabled",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_ENUM         |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMX_CONFIG_MBERRORREPORTINGTYPE,bEnabled),
  FIELDOFFSET(OMX_CONFIG_MBERRORREPORTINGTYPE,nSize) -
  FIELDOFFSET(OMX_CONFIG_MBERRORREPORTINGTYPE,bEnabled) ,
  0,
  OMX_FALSE,
  OMX_TRUE,
  OMX_FALSE,
  &enumTblOnOff,
  XdbgCmdVarFunc,
  "MB Error Reporting Type.......................",
  "",
  "",
  ""
};

MX_DBG_CMD_ENTRY_T* cmdListIndexConfigVideoMacroBlockErrorMapConfig[] =
{
  &cmdEntryMbErrorReportingTypeEnable,
  NULL
};

MX_DBG_CMD_TABLE_T cmdTblIndexConfigVideoMacroBlockErrorMapConfig =
{
  MX_DBG_ACCESS_ALL,
  sizeof(cmdListIndexConfigVideoMacroBlockErrorMapConfig)/sizeof(cmdListIndexConfigVideoMacroBlockErrorMapConfig[0]),
  cmdListIndexConfigVideoMacroBlockErrorMapConfig
}; 

/*
 * <<< OMX_CONFIG_MBERRORREPORTINGTYPE
 */ 
 
/*
 * >>> OMX_PARAM_FILEMODE_TYPE, OMX_TI_IndexParamFileModeType
 */ 
/* Entry for Set file mode falg enable */

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryEnableFileMode =
{
  "bEnableFileMode",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_ENUM         |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMX_PARAM_FILEMODE_TYPE,bEnableFileMode),
  FIELDOFFSET(OMX_PARAM_FILEMODE_TYPE,nSize) -
  FIELDOFFSET(OMX_PARAM_FILEMODE_TYPE,bEnableFileMode) ,
  0,
  OMX_FALSE,
  OMX_TRUE,
  OMX_FALSE,
  &enumTblOnOff,
  XdbgCmdVarFunc,
  "File Mode Cfg Flag ...........................",
  "",
  "",
  ""
};

MX_DBG_CMD_ENTRY_T* cmdListIndexParamFileModeTypeConfig[] =
{
  &cmdEntryEnableFileMode,
  NULL
};

MX_DBG_CMD_TABLE_T cmdTblIndexParamFileModeTypeConfig =
{
  MX_DBG_ACCESS_ALL,
  sizeof(cmdListIndexParamFileModeTypeConfig)/sizeof(cmdListIndexParamFileModeTypeConfig[0]),
  cmdListIndexParamFileModeTypeConfig
}; 

/*
 * <<< OMX_PARAM_FILEMODE_TYPE
 */ 
 

 /*
 * >>> OMX_VIDEO_PARAM_PORTFORMATTYPE, OMX_IndexParamVideoPortFormat
 */  

/* Enum Entry for Supported Compression Format */

PRIVATE MX_DBG_ENUM_ENTRY_T enumTblCompressionFormat[] =
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
 
/*Entry for Set eCompressionFormat*/

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryPortFormatCompressionFormat =
{
  "eCompressionFormat",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_ENUM         |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMX_VIDEO_PARAM_PORTFORMATTYPE,eCompressionFormat),
  FIELDOFFSET(OMX_VIDEO_PARAM_PORTFORMATTYPE,nSize) -
  FIELDOFFSET(OMX_VIDEO_PARAM_PORTFORMATTYPE,eCompressionFormat),
  0,
  OMX_VIDEO_CodingUnused,
  OMX_VIDEO_CodingMJPEG,
  OMX_VIDEO_CodingAVC,
  &enumTblCompressionFormat,
  XdbgCmdVarFunc,
  "Compression Format............................",
  "",
  "",
  ""
};

PRIVATE MX_DBG_ENUM_ENTRY_T enumTblChromaFormat[] =
{
  {"420P",OMX_COLOR_FormatYUV420Planar, ""},
  {"420SP",OMX_COLOR_FormatYUV420SemiPlanar, ""},
  {"422P",OMX_COLOR_FormatYUV422Planar, ""},
  {"422YUYV", OMX_COLOR_FormatYCbYCr, ""},
  {"", 0, ""}
};

/*Entry for Set eColorFormat*/

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryPortFormatColorFormat =
{
  "eColorFormat",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_ENUM         |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMX_VIDEO_PARAM_PORTFORMATTYPE,eColorFormat),
  FIELDOFFSET(OMX_VIDEO_PARAM_PORTFORMATTYPE,nSize) -
  FIELDOFFSET(OMX_VIDEO_PARAM_PORTFORMATTYPE,eColorFormat),
  0,
  OMX_COLOR_FormatYUV420Planar,
  OMX_COLOR_FormatYCbYCr,
  OMX_COLOR_FormatYUV420SemiPlanar,
  &enumTblChromaFormat,
  XdbgCmdVarFunc,
  "Color Format..................................",
  "",
  "",
  ""
};

/* Entry for Set Framerate */
PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryPortFormatXFramerate =
{
  "xFramerate",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_DEC          |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMX_VIDEO_PARAM_PORTFORMATTYPE,xFramerate),
  FIELDOFFSET(OMX_VIDEO_PARAM_PORTFORMATTYPE,nSize) -
  FIELDOFFSET(OMX_VIDEO_PARAM_PORTFORMATTYPE,xFramerate),
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

MX_DBG_CMD_ENTRY_T* cmdListIndexParamVideoPortFormatConfig[] =
{
  &cmdEntryPortFormatCompressionFormat,
  &cmdEntryPortFormatColorFormat,
  &cmdEntryPortFormatXFramerate,
  NULL
};

MX_DBG_CMD_TABLE_T cmdTblIndexParamVideoPortFormatConfig =
{
  MX_DBG_ACCESS_ALL,
  sizeof(cmdListIndexParamVideoPortFormatConfig)/sizeof(cmdListIndexParamVideoPortFormatConfig[0]),
  cmdListIndexParamVideoPortFormatConfig
}; 

/*
 * <<< OMX_VIDEO_PARAM_PORTFORMATTYPE
 */
 
 
 
/*
 * >>> OMX_VIDEO_PARAM_QUANTIZATIONTYPE, OMX_IndexParamVideoQuantization
 */ 
 
 /* Entry for Set QP for I frames */

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryQPTypeQpI =
{
  "nQpI",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_DEC          |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMX_VIDEO_PARAM_QUANTIZATIONTYPE,nQpI),
  FIELDOFFSET(OMX_VIDEO_PARAM_QUANTIZATIONTYPE,nSize) -
  FIELDOFFSET(OMX_VIDEO_PARAM_QUANTIZATIONTYPE,nQpI),
  0,
  OMTB_H264_VENC_MIN_QP_IPB,
  OMTB_H264_VENC_MAX_QP_IPB,
  OMTB_H264_VENC_DEF_QP_I,
  NULL,
  XdbgCmdVarFunc,
  "QP for I frames...............................",
  "<QP # - For I frames>",
  "",
  ""
};


/* Entry for Set QP for P frames */

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryQPTypeQpP =
{
  "nQpP",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_DEC          |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMX_VIDEO_PARAM_QUANTIZATIONTYPE,nQpP),
  FIELDOFFSET(OMX_VIDEO_PARAM_QUANTIZATIONTYPE,nSize) -
  FIELDOFFSET(OMX_VIDEO_PARAM_QUANTIZATIONTYPE,nQpP),
  0,
  OMTB_H264_VENC_MIN_QP_IPB,
  OMTB_H264_VENC_MAX_QP_IPB,
  OMTB_H264_VENC_DEF_QP_P,
  NULL,
  XdbgCmdVarFunc,
  "QP for P frames...............................",
  "<QP # - For P frames>",
  "",
  ""
};


/* Entry for Set QP for B frames */

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryQPTypeQpB =
{
  "nQpB",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_DEC          |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMX_VIDEO_PARAM_QUANTIZATIONTYPE,nQpB),
  FIELDOFFSET(OMX_VIDEO_PARAM_QUANTIZATIONTYPE,nSize) -
  FIELDOFFSET(OMX_VIDEO_PARAM_QUANTIZATIONTYPE,nQpB),
  0,
  OMTB_H264_VENC_MIN_QP_IPB,
  OMTB_H264_VENC_MAX_QP_IPB,
  OMTB_H264_VENC_DEF_QP_B,
  NULL,
  XdbgCmdVarFunc,
  "QP for B frames...............................",
  "<QP # - For B frames>",
  "",
  ""
};

MX_DBG_CMD_ENTRY_T* cmdListIndexParamVideoQuantizationConfig[] =
{
  &cmdEntryQPTypeQpI,
  &cmdEntryQPTypeQpP,
  &cmdEntryQPTypeQpB,
  NULL
};

MX_DBG_CMD_TABLE_T cmdTblIndexParamVideoQuantizationConfig =
{
  MX_DBG_ACCESS_ALL,
  sizeof(cmdListIndexParamVideoQuantizationConfig)/sizeof(cmdListIndexParamVideoQuantizationConfig[0]),
  cmdListIndexParamVideoQuantizationConfig
}; 

/*
 * <<< OMX_VIDEO_PARAM_QUANTIZATIONTYPE
 */
 
/* 
 * >>> OMX_CONFIG_VFDC_MOSAICLAYOUT_PORT2WINMAP, OMX_TI_IndexConfigVFDCMosaicPort2WinMap
 */
 
/* Entry for Set ID of the mosaic layout */

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryVPSSVfdcWinMapLayoutId =
{
  "nLayoutId",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_DEC          |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMX_CONFIG_VFDC_MOSAICLAYOUT_PORT2WINMAP,nLayoutId),
  FIELDOFFSET(OMX_CONFIG_VFDC_MOSAICLAYOUT_PORT2WINMAP,nSize) -
  FIELDOFFSET(OMX_CONFIG_VFDC_MOSAICLAYOUT_PORT2WINMAP,nLayoutId),
  0,
  0,
  OMTB_MAX_VAL_U32,
  0,
  NULL,
  XdbgCmdVarFunc,
  "Mosaic Layout Id..............................",
  "",
  "",
  ""
};

MX_DBG_CMD_ENTRY_T* cmdListIndexConfigVFDCMosaicPort2WinMapConfig[] =
{
  &cmdEntryVPSSVfdcWinMapLayoutId,
  NULL
};

MX_DBG_CMD_TABLE_T cmdTblIndexConfigVFDCMosaicPort2WinMapConfig =
{
  MX_DBG_ACCESS_ALL,
  sizeof(cmdListIndexConfigVFDCMosaicPort2WinMapConfig)/sizeof(cmdListIndexConfigVFDCMosaicPort2WinMapConfig[0]),
  cmdListIndexConfigVFDCMosaicPort2WinMapConfig
};  
/* 
 * <<< OMX_CONFIG_VFDC_MOSAICLAYOUT_PORT2WINMAP
 */
 

 /*
 * >>> OMX_PARAM_VFDC_CREATEMOSAICLAYOUT, OMX_TI_IndexParamVFDCCreateMosaicLayout
 */ 
 
/* Entry for Start X of the mosaic layout */

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryVPSSVfdcWinStartX =
{
  "winStartX",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_DEC          |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMTB_VPSS_VFDC_MOSAIC_PARAMS,winStartX),
  FIELDOFFSET(OMTB_VPSS_VFDC_MOSAIC_PARAMS,winStartX) -
  FIELDOFFSET(OMTB_VPSS_VFDC_MOSAIC_PARAMS,winStartX),
  0,
  0,
  OMTB_MAX_VAL_U32,
  0,
  NULL,
  XdbgCmdVarFunc,
  "Start X.......................................",
  "<start X position>",
  "",
  ""
};

/* Entry for Start Y of the mosaic layout */

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryVPSSVfdcWinStartY =
{
  "winStartY",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_DEC          |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMTB_VPSS_VFDC_MOSAIC_PARAMS,winStartY),
  FIELDOFFSET(OMTB_VPSS_VFDC_MOSAIC_PARAMS,winStartX) -
  FIELDOFFSET(OMTB_VPSS_VFDC_MOSAIC_PARAMS,winStartY),
  0,
  0,
  OMTB_MAX_VAL_U32,
  0,
  NULL,
  XdbgCmdVarFunc,
  "Start Y.......................................",
  "<start Y position>",
  "",
  ""
};

/*Entry for Setting Mosaic Frame Width*/

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryVPSSVfdcWinWidth =
{
  "winWidth",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_DEC      |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMTB_VPSS_VFDC_MOSAIC_PARAMS,winWidth),
  FIELDOFFSET(OMTB_VPSS_VFDC_MOSAIC_PARAMS,winStartX) -
  FIELDOFFSET(OMTB_VPSS_VFDC_MOSAIC_PARAMS,winWidth),
  0,
  0,
  1920,
  240,
  NULL,
  XdbgCmdVarFunc,
  "VFDC Mosaic Frame Width.......................",
  "<Mosaic Frame Width>",
  "",
  ""
};

/*Entry for Setting Mosaic Frame Height*/

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryVPSSVfdcWinHeight =
{
  "winHeight",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_DEC      |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMTB_VPSS_VFDC_MOSAIC_PARAMS,winHeight),
  FIELDOFFSET(OMTB_VPSS_VFDC_MOSAIC_PARAMS,winStartX) -
  FIELDOFFSET(OMTB_VPSS_VFDC_MOSAIC_PARAMS,winHeight),
  0,
  0,
  1080,
  360,
  NULL,
  XdbgCmdVarFunc,
  "VFDC Mosaic Frame Height......................",
  "<Mosaic Frame Height>",
  "",
  ""
};

/*Entry for Setting Mosaic Frame Pitch for YUV 422I or 444I*/

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryVPSSVfdcPitchVFDC_YUV_INT_ADDR_IDX =
{
  "pitch.VFDC_YUV_INT_ADDR_IDX",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_DEC      |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMTB_VPSS_VFDC_MOSAIC_PARAMS,pitchVFDC_YUV_INT_ADDR_IDX),
  FIELDOFFSET(OMTB_VPSS_VFDC_MOSAIC_PARAMS,winStartX) -
  FIELDOFFSET(OMTB_VPSS_VFDC_MOSAIC_PARAMS,pitchVFDC_YUV_INT_ADDR_IDX),
  0,
  0,
  3840,
  1920,
  NULL,
  XdbgCmdVarFunc,
  "VFDC Mosaic Frame Pitch YUV 422I|444I.........",
  "<Mosaic Frame Pitch for YUV 422I|444I>",
  "",
  ""
};

/*Entry for Setting Mosaic Frame Pitch for the Y of 420SP*/

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryVPSSVfdcPitchVFDC_YUV_SP_Y_ADDR_IDX =
{
  "pitch.VFDC_YUV_SP_Y_ADDR_IDX",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_DEC      |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMTB_VPSS_VFDC_MOSAIC_PARAMS,pitchVFDC_YUV_SP_Y_ADDR_IDX),
  FIELDOFFSET(OMTB_VPSS_VFDC_MOSAIC_PARAMS,winStartX) -
  FIELDOFFSET(OMTB_VPSS_VFDC_MOSAIC_PARAMS,pitchVFDC_YUV_SP_Y_ADDR_IDX),
  0,
  0,
  3840,
  1920,
  NULL,
  XdbgCmdVarFunc,
  "VFDC Mosaic Frame Pitch the Y of 420SP........",
  "<Mosaic Frame Pitch for the Y of 420SP>",
  "",
  ""
};

/*Entry for Setting Mosaic Frame Pitch for the UV of 420SP*/

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryVPSSVfdcPitchVFDC_YUV_SP_CBCR_ADDR_IDX =
{
  "pitch.VFDC_YUV_SP_CBCR_ADDR_IDX",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_DEC      |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMTB_VPSS_VFDC_MOSAIC_PARAMS,pitchVFDC_YUV_SP_CBCR_ADDR_IDX),
  FIELDOFFSET(OMTB_VPSS_VFDC_MOSAIC_PARAMS,winStartX) -
  FIELDOFFSET(OMTB_VPSS_VFDC_MOSAIC_PARAMS,pitchVFDC_YUV_SP_CBCR_ADDR_IDX),
  0,
  0,
  3840,
  1920,
  NULL,
  XdbgCmdVarFunc,
  "VFDC Mosaic Frame Pitch the UV of 420SP.......",
  "<Mosaic Frame Pitch for the UV of 420SP>",
  "",
  ""
};

/* Enum Entry for Supported Mosaic Data Format */

PRIVATE MX_DBG_ENUM_ENTRY_T enumTblVPSSVfdcMosaicDataFormat[] =
{
  {"422I_YUYV",  VFDC_DF_YUV422I_YUYV, ""},
  {"420SP_UV",   VFDC_DF_YUV420SP_UV,  ""},
  {"", 0, ""}
};

/* Entry for Setting Mosaic Data Format */

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryVPSSVfdcDataFormat =
{
  "dataFormat",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_ENUM          |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMTB_VPSS_VFDC_MOSAIC_PARAMS,dataFormat),
  FIELDOFFSET(OMTB_VPSS_VFDC_MOSAIC_PARAMS,winStartX) -
  FIELDOFFSET(OMTB_VPSS_VFDC_MOSAIC_PARAMS,dataFormat),
  0,
  VFDC_DF_YUV422I_YUYV,
  VFDC_DF_YUV420SP_UV,
  VFDC_DF_YUV422I_YUYV,
  &enumTblVPSSVfdcMosaicDataFormat,
  XdbgCmdVarFunc,
  "Mosaic Data Format............................",
  "",
  "",
  ""
};

/* Enum Entry for Supported BPP */
PRIVATE MX_DBG_ENUM_ENTRY_T enumTblVPSSVfdcMosaicBpp[] =
{
  {"bits1",  VFDC_BPP_BITS1,  ""},
  {"bits2",  VFDC_BPP_BITS2,  ""},
  {"bits4",  VFDC_BPP_BITS4,  ""},
  {"bits8",  VFDC_BPP_BITS8,  ""},
  {"bits12", VFDC_BPP_BITS12, ""},
  {"bits16", VFDC_BPP_BITS16, ""},
  {"bits24", VFDC_BPP_BITS24, ""},
  {"bits32", VFDC_BPP_BITS32, ""},
  {"",       0,               ""}
};

/* Entry for Bits per pixel of the mosaic layout */
PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryVPSSVfdcBpp =
{
  "bpp",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_ENUM          |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMTB_VPSS_VFDC_MOSAIC_PARAMS,bpp),
  FIELDOFFSET(OMTB_VPSS_VFDC_MOSAIC_PARAMS,winStartX) -
  FIELDOFFSET(OMTB_VPSS_VFDC_MOSAIC_PARAMS,bpp),
  0,
  VFDC_BPP_BITS1,
  VFDC_BPP_BITS32,
  VFDC_BPP_BITS16,
  &enumTblVPSSVfdcMosaicBpp,
  XdbgCmdVarFunc,
  "Bits Per Pixel................................",
  "",
  "",
  ""
};

/* Entry for priority of the mosaic layout */

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryVPSSVfdcPriority =
{
  "priority",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_DEC          |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMTB_VPSS_VFDC_MOSAIC_PARAMS,priority),
  FIELDOFFSET(OMTB_VPSS_VFDC_MOSAIC_PARAMS,winStartX) -
  FIELDOFFSET(OMTB_VPSS_VFDC_MOSAIC_PARAMS,priority),
  0,
  0,
  OMTB_MAX_VAL_U32,
  0,
  NULL,
  XdbgCmdVarFunc,
  "Mosaic priority...............................",
  "<priority of window>",
  "",
  ""
};


/* Entry for Set ID of the mosaic layout */

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryVPSSVfdcLayoutId =
{
  "nLayoutId",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_DEC          |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMTB_VPSS_VFDC_MOSAIC_PARAMS,sMosaicLayout.nLayoutId),
  FIELDOFFSET(OMTB_VPSS_VFDC_MOSAIC_PARAMS,winStartX) -
  FIELDOFFSET(OMTB_VPSS_VFDC_MOSAIC_PARAMS,sMosaicLayout.nLayoutId),
  0,
  0,
  OMTB_MAX_VAL_U32,
  0,
  NULL,
  XdbgCmdVarFunc,
  "Mosaic Layout Id..............................",
  "",
  "",
  ""
};


MX_DBG_CMD_ENTRY_T* cmdListIndexParamVFDCCreateMosaicLayoutConfig[] =
{
  &cmdEntryVPSSVfdcWinStartX,
  &cmdEntryVPSSVfdcWinStartY,
  &cmdEntryVPSSVfdcWinWidth,
  &cmdEntryVPSSVfdcWinHeight,
  &cmdEntryVPSSVfdcPitchVFDC_YUV_INT_ADDR_IDX,
  &cmdEntryVPSSVfdcPitchVFDC_YUV_SP_Y_ADDR_IDX,
  &cmdEntryVPSSVfdcPitchVFDC_YUV_SP_CBCR_ADDR_IDX,
  &cmdEntryVPSSVfdcDataFormat,
  &cmdEntryVPSSVfdcBpp,
  &cmdEntryVPSSVfdcPriority,
  &cmdEntryVPSSVfdcLayoutId,
  NULL
};

MX_DBG_CMD_TABLE_T cmdTblIndexParamVFDCCreateMosaicLayoutConfig =
{
  MX_DBG_ACCESS_ALL,
  sizeof(cmdListIndexParamVFDCCreateMosaicLayoutConfig)/sizeof(cmdListIndexParamVFDCCreateMosaicLayoutConfig[0]),
  cmdListIndexParamVFDCCreateMosaicLayoutConfig
}; 
/*
 * <<< OMX_PARAM_VFDC_CREATEMOSAICLAYOUT
 */ 
 
 
/*
 * >>> OMX_PARAM_PORTDEFINITIONTYPE, OMX_IndexParamPortDefinition
 */ 
 
/* Entry for Set eDir */
PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryPortDefDir =
{
  "eDir",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_ENUM         |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMX_PARAM_PORTDEFINITIONTYPE,eDir),
  FIELDOFFSET(OMX_PARAM_PORTDEFINITIONTYPE,nSize) -
  FIELDOFFSET(OMX_PARAM_PORTDEFINITIONTYPE,eDir),
  0,
  OMX_DirInput,
  OMX_DirOutput,
  OMX_DirInput,
  &enumTbleDirInputOutput,
  XdbgCmdVarFunc,
  "Port Direction................................",
  "",
  "",
  ""
};

/* Entry for Set Buffer Count Actual */
PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryPortDefBufferCountActual =
{
  "nBufferCountActual",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_DEC          |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMX_PARAM_PORTDEFINITIONTYPE,nBufferCountActual),
  FIELDOFFSET(OMX_PARAM_PORTDEFINITIONTYPE,nSize) -
  FIELDOFFSET(OMX_PARAM_PORTDEFINITIONTYPE,nBufferCountActual),
  0,
  0,
  OMTB_MAX_VAL_U32,
  0,
  NULL,
  XdbgCmdVarFunc,
  "Buffer Count Actual...........................",
  "<no of actual buffers>",
  "",
  ""
};

/* Entry for Set for Buffer Count Min*/
PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryPortDefBufferCountMin =
{
  "nBufferCountMin",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_DEC          |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMX_PARAM_PORTDEFINITIONTYPE,nBufferCountMin),
  FIELDOFFSET(OMX_PARAM_PORTDEFINITIONTYPE,nSize) -
  FIELDOFFSET(OMX_PARAM_PORTDEFINITIONTYPE,nBufferCountMin),
  0,
  0,
  OMTB_MAX_VAL_U32,
  0,
  NULL,
  XdbgCmdVarFunc,
  "Buffer Count Min..............................",
  "<no of min buffers>",
  "",
  ""
};

/* Entry for Set for Buffer Size*/
PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryPortDefBufferSize =
{
  "nBufferSize",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_DEC          |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMX_PARAM_PORTDEFINITIONTYPE,nBufferSize),
  FIELDOFFSET(OMX_PARAM_PORTDEFINITIONTYPE,nSize) -
  FIELDOFFSET(OMX_PARAM_PORTDEFINITIONTYPE,nBufferSize),
  0,
  0,
  OMTB_MAX_VAL_U32,
  0,
  NULL,
  XdbgCmdVarFunc,
  "Buffer Size...................................",
  "<buffer size>",
  "",
  ""
};

/* Entry for Set for Enabled */
PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryPortDefEnabled =
{
  "bEnabled",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_ENUM         |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMX_PARAM_PORTDEFINITIONTYPE,bEnabled),
  FIELDOFFSET(OMX_PARAM_PORTDEFINITIONTYPE,nSize) -
  FIELDOFFSET(OMX_PARAM_PORTDEFINITIONTYPE,bEnabled),
  0,
  OMX_FALSE,
  OMX_TRUE,
  OMX_FALSE,
  &enumTblOnOff,
  XdbgCmdVarFunc,
  "Port Default Status...........................",
  "",
  "",
  ""
};

/* Entry for Set for Populated*/
PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryPortDefPopulated =
{
  "bPopulated",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_ENUM         |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMX_PARAM_PORTDEFINITIONTYPE,bPopulated),
  FIELDOFFSET(OMX_PARAM_PORTDEFINITIONTYPE,nSize) -
  FIELDOFFSET(OMX_PARAM_PORTDEFINITIONTYPE,bPopulated),
  0,
  OMX_FALSE,
  OMX_TRUE,
  OMX_FALSE,
  &enumTblOnOff,
  XdbgCmdVarFunc,
  "Port Populated................................",
  "",
  "",
  ""
};

/* Enum Entry for Set for Domain*/
PRIVATE MX_DBG_ENUM_ENTRY_T enumTblPortDomainType[] =
{
  {"audio", OMX_PortDomainAudio,    ""},
  {"video", OMX_PortDomainVideo,    ""},
  {"image", OMX_PortDomainImage,    ""},
  {"other", OMX_PortDomainOther,    ""},  
  {"",      0,                      ""}
};

/* Entry for Set for Domain*/
PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryPortDefDomain =
{
  "eDomain",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_ENUM         |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMX_PARAM_PORTDEFINITIONTYPE,eDomain),
  FIELDOFFSET(OMX_PARAM_PORTDEFINITIONTYPE,nSize) -
  FIELDOFFSET(OMX_PARAM_PORTDEFINITIONTYPE,eDomain),
  0,
  OMX_PortDomainAudio,
  OMX_PortDomainOther,
  OMX_PortDomainVideo,
  &enumTblPortDomainType,
  XdbgCmdVarFunc,
  "Domain........................................",
  "",
  "",
  ""
};

/* Entry for Set for Buffers Contiguous*/
PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryPortDefBuffersContiguous =
{
  "bBuffersContiguous",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_ENUM         |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMX_PARAM_PORTDEFINITIONTYPE,bBuffersContiguous),
  FIELDOFFSET(OMX_PARAM_PORTDEFINITIONTYPE,nSize) -
  FIELDOFFSET(OMX_PARAM_PORTDEFINITIONTYPE,bBuffersContiguous),
  0,
  OMX_FALSE,
  OMX_TRUE,
  OMX_FALSE,
  &enumTblOnOff,
  XdbgCmdVarFunc,
  "Buffers Contiguous............................",
  "",
  "",
  ""
};

/* Entry for Set for Buffer Alignment*/
PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryPortDefBufferAlignment =
{
  "nBufferAlignment",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_DEC          |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMX_PARAM_PORTDEFINITIONTYPE,nBufferAlignment),
  FIELDOFFSET(OMX_PARAM_PORTDEFINITIONTYPE,nSize) -
  FIELDOFFSET(OMX_PARAM_PORTDEFINITIONTYPE,nBufferAlignment),
  0,
  0,
  OMTB_MAX_VAL_U32,
  0,
  NULL,
  XdbgCmdVarFunc,
  "Buffer Alignment..............................",
  "<buffer alignment>",
  "",
  ""
};

/* Entry for Set for Mime Type*/
PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryPortDefVideoMIMEType =
{
  "video.cMIMEType",
  MX_DBG_CMD_TYPE_VAR_STR_BUF,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMX_PARAM_PORTDEFINITIONTYPE,format.video.cMIMEType),
  FIELDOFFSET(OMX_PARAM_PORTDEFINITIONTYPE,nSize) -
  FIELDOFFSET(OMX_PARAM_PORTDEFINITIONTYPE,format.video.cMIMEType),
  0,
  0,
  OMX_MAX_STRINGNAME_SIZE,
  (int)NULL,
  NULL,
  XdbgCmdVarFunc,
  "MIME Type.....................................",
  "<mime type>",
  "",
  ""
};

/* Entry for Set for Native Render*/	
PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryPortDefVideoNativeRender =
{
  "video.pNativeRender",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_DEC          |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMX_PARAM_PORTDEFINITIONTYPE,format.video.pNativeRender),
  FIELDOFFSET(OMX_PARAM_PORTDEFINITIONTYPE,nSize) -
  FIELDOFFSET(OMX_PARAM_PORTDEFINITIONTYPE,format.video.pNativeRender),
  0,
  0,
  OMTB_MAX_VAL_U32,
  0,
  NULL,
  XdbgCmdVarFunc,
  "Native Render.................................",
  "<pointer/reference to a render object>",
  "",
  ""
};

/* Entry for Set for Frame Width*/	
PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryPortDefVideoFrameWidth =
{
  "video.nFrameWidth",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_DEC          |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMX_PARAM_PORTDEFINITIONTYPE,format.video.nFrameWidth),
  FIELDOFFSET(OMX_PARAM_PORTDEFINITIONTYPE,nSize) -
  FIELDOFFSET(OMX_PARAM_PORTDEFINITIONTYPE,format.video.nFrameWidth),
  0,
  0,
  OMTB_MAX_VAL_U32,
  0,
  NULL,
  XdbgCmdVarFunc,
  "Frame Width...................................",
  "<frame width>",
  "",
  ""
};

/* Entry for Set for Frame Height*/	
PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryPortDefVideoFrameHeight =
{
  "video.nFrameHeight",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_DEC          |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMX_PARAM_PORTDEFINITIONTYPE,format.video.nFrameHeight),
  FIELDOFFSET(OMX_PARAM_PORTDEFINITIONTYPE,nSize) -
  FIELDOFFSET(OMX_PARAM_PORTDEFINITIONTYPE,format.video.nFrameHeight),
  0,
  0,
  OMTB_MAX_VAL_U32,
  0,
  NULL,
  XdbgCmdVarFunc,
  "Frame Height..................................",
  "<frame height>",
  "",
  ""
};

/* Entry for Set for Stride*/	
PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryPortDefVideoStride =
{
  "video.nStride",
  MX_DBG_CMD_TYPE_VAR_SINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_DEC          |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMX_PARAM_PORTDEFINITIONTYPE,format.video.nStride),
  FIELDOFFSET(OMX_PARAM_PORTDEFINITIONTYPE,nSize) -
  FIELDOFFSET(OMX_PARAM_PORTDEFINITIONTYPE,format.video.nStride),
  0,
  -1920,
  3840,
  720,
  NULL,
  XdbgCmdVarFunc,
  "Stride........................................",
  "<stride>",
  "",
  ""
};

/* Entry for Set for Slice Height*/	
PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryPortDefVideoSliceHeight =
{
  "video.nSliceHeight",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_DEC          |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMX_PARAM_PORTDEFINITIONTYPE,format.video.nSliceHeight),
  FIELDOFFSET(OMX_PARAM_PORTDEFINITIONTYPE,nSize) -
  FIELDOFFSET(OMX_PARAM_PORTDEFINITIONTYPE,format.video.nSliceHeight),
  0,
  0,
  OMTB_MAX_VAL_U32,
  0,
  NULL,
  XdbgCmdVarFunc,
  "Slice Height..................................",
  "<slice height>",
  "",
  ""
};

/* Entry for Set for Bit Rate*/	
PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryPortDefVideoBitrate =
{
  "video.nBitrate",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_DEC          |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMX_PARAM_PORTDEFINITIONTYPE,format.video.nBitrate),
  FIELDOFFSET(OMX_PARAM_PORTDEFINITIONTYPE,nSize) -
  FIELDOFFSET(OMX_PARAM_PORTDEFINITIONTYPE,format.video.nBitrate),
  0,
  0,
  OMTB_MAX_VAL_U32,
  0,
  NULL,
  XdbgCmdVarFunc,
  "Bit Rate......................................",
  "<bitrate>",
  "",
  ""
};

/* Entry for Set for Frame Rate*/	
PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryPortDefVideoFramerate =
{
  "video.xFramerate",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_DEC          |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMX_PARAM_PORTDEFINITIONTYPE,format.video.xFramerate),
  FIELDOFFSET(OMX_PARAM_PORTDEFINITIONTYPE,nSize) -
  FIELDOFFSET(OMX_PARAM_PORTDEFINITIONTYPE,format.video.xFramerate),
  0,
  0,
  OMTB_MAX_VAL_U32,
  0,
  NULL,
  XdbgCmdVarFunc,
  "Frame Rate....................................",
  "<framerate>",
  "",
  ""
};


/* Entry for Set for Flag Error Concealment*/	
PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryPortDefVideoFlagErrorConcealment =
{
  "video.bFlagErrorConcealment",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_ENUM         |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMX_PARAM_PORTDEFINITIONTYPE,format.video.bFlagErrorConcealment),
  FIELDOFFSET(OMX_PARAM_PORTDEFINITIONTYPE,nSize) -
  FIELDOFFSET(OMX_PARAM_PORTDEFINITIONTYPE,format.video.bFlagErrorConcealment),
  0,
  OMX_FALSE,
  OMX_TRUE,
  OMX_FALSE,
  &enumTblOnOff,
  XdbgCmdVarFunc,
  "Flag Error Concealment........................",
  "",
  "",
  ""
};

/*Entry for Set Compression Format*/
PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryPortDefVideoCompressionFormat =
{
  "video.eCompressionFormat",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_ENUM         |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMX_PARAM_PORTDEFINITIONTYPE,format.video.eCompressionFormat),
  FIELDOFFSET(OMX_PARAM_PORTDEFINITIONTYPE,nSize) -
  FIELDOFFSET(OMX_PARAM_PORTDEFINITIONTYPE,format.video.eCompressionFormat),
  0,
  OMX_VIDEO_CodingUnused,
  OMX_VIDEO_CodingMJPEG,
  OMX_VIDEO_CodingAVC,
  &enumTblCompressionFormat,
  XdbgCmdVarFunc,
  "Compression Format............................",
  "",
  "",
  ""
};


/*Entry for Set Color Format*/
PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryPortDefVideoColorFormat =
{
  "video.eColorFormat",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_ENUM         |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMX_PARAM_PORTDEFINITIONTYPE,format.video.eColorFormat),
  FIELDOFFSET(OMX_PARAM_PORTDEFINITIONTYPE,nSize) -
  FIELDOFFSET(OMX_PARAM_PORTDEFINITIONTYPE,format.video.eColorFormat),
  0,
  OMX_COLOR_FormatYUV420Planar,
  OMX_COLOR_FormatYCbYCr,
  OMX_COLOR_FormatYUV420SemiPlanar,
  &enumTblChromaFormat,
  XdbgCmdVarFunc,
  "Color Format..................................",
  "",
  "",
  ""
};

/*Entry for Set Native Window*/
PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryPortDefVideoNativeWindow =
{
  "video.pNativeWindow",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_DEC          |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMX_PARAM_PORTDEFINITIONTYPE,format.video.pNativeWindow),
  FIELDOFFSET(OMX_PARAM_PORTDEFINITIONTYPE,nSize) -
  FIELDOFFSET(OMX_PARAM_PORTDEFINITIONTYPE,format.video.pNativeWindow),
  0,
  0,
  OMTB_MAX_VAL_U32,
  0,
  NULL,
  XdbgCmdVarFunc,
  "Native Window.................................",
  "<poninter for a window object>",
  "",
  ""
};

 MX_DBG_CMD_ENTRY_T* cmdListIndexParamPortDefinitionConfig[] =
{
  &cmdEntryPortDefDir,
  &cmdEntryPortDefBufferCountActual,
  &cmdEntryPortDefBufferCountMin,
  &cmdEntryPortDefBufferSize,
  &cmdEntryPortDefEnabled,
  &cmdEntryPortDefPopulated,
  &cmdEntryPortDefDomain,
  &cmdEntryPortDefBuffersContiguous,
  &cmdEntryPortDefBufferAlignment,
  &cmdEntryPortDefVideoMIMEType,
  &cmdEntryPortDefVideoNativeRender,
  &cmdEntryPortDefVideoFrameWidth,
  &cmdEntryPortDefVideoFrameHeight,
  &cmdEntryPortDefVideoStride,
  &cmdEntryPortDefVideoSliceHeight,
  &cmdEntryPortDefVideoBitrate,
  &cmdEntryPortDefVideoFramerate,
  &cmdEntryPortDefVideoFlagErrorConcealment,
  &cmdEntryPortDefVideoCompressionFormat,
  &cmdEntryPortDefVideoColorFormat,
  &cmdEntryPortDefVideoNativeWindow,
  NULL
};

MX_DBG_CMD_TABLE_T cmdTblIndexParamPortDefinitionConfig =
{
  MX_DBG_ACCESS_ALL,
  sizeof(cmdListIndexParamPortDefinitionConfig)/sizeof(cmdListIndexParamPortDefinitionConfig[0]),
  cmdListIndexParamPortDefinitionConfig
}; 
/*
 * <<< OMX_PARAM_PORTDEFINITIONTYPE
 */ 
 

/*
 * >>> OMX_TI_IndexConfigChannelName, OMX_PARAM_PORTDEFINITIONTYPE
 */  
 
/* Entry for Set Channel Name */
PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryChannelName =
{
  "cChannelName",
  MX_DBG_CMD_TYPE_VAR_STR_BUF,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMX_CONFIG_CHANNELNAME,cChannelName),
  FIELDOFFSET(OMX_CONFIG_CHANNELNAME,nSize) -
  FIELDOFFSET(OMX_CONFIG_CHANNELNAME,cChannelName),
  0,
  0,
  OMX_MAX_STRINGNAME_SIZE,
  (int)NULL,
  NULL,
  XdbgCmdVarFunc,
  "Frame Queue Channel name......................",
  "<chan name>",
  "",
  ""
};

MX_DBG_CMD_ENTRY_T* cmdListIndexConfigChannelNameConfig[] =
{
  &cmdEntryChannelName,
  NULL
};

MX_DBG_CMD_TABLE_T cmdTblIndexConfigChannelNameConfig =
{
  MX_DBG_ACCESS_ALL,
  sizeof(cmdListIndexConfigChannelNameConfig)/sizeof(cmdListIndexConfigChannelNameConfig[0]),
  cmdListIndexConfigChannelNameConfig
};

/*
 * <<< OMX_PARAM_PORTDEFINITIONTYPE
 */  
 
/*
 * >>> OMX_TI_IndexConfigVideoDynamicParams, OMX_VIDEO_CONFIG_DYNAMICPARAMS
 */
#ifdef _VIDEO_M3_DYNAMIC_CONFIG
/* Entry for Set Bitrate */
PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryDynamicParamsTargetBitrate =
{
  "h264EncDynamicParams.targetBitRate",
  MX_DBG_CMD_TYPE_VAR_SINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_DEC          |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMX_VIDEO_CONFIG_DYNAMICPARAMS,
              videoDynamicParams.h264EncDynamicParams.videnc2DynamicParams.targetBitRate),
  FIELDOFFSET(OMX_VIDEO_CONFIG_DYNAMICPARAMS,nSize) -
  FIELDOFFSET(OMX_VIDEO_CONFIG_DYNAMICPARAMS,
              videoDynamicParams.h264EncDynamicParams.videnc2DynamicParams.targetBitRate),
  0,
  0,
  OMTB_MAX_VAL_S32,
  OMTB_H264_VENC_DEF_BIT_RATE,
  NULL,
  XdbgCmdVarFunc,
  "Target Bitrate................................",
  "<bitrate>",
  "",
  ""
};

/* Entry for Intra period */
PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryDynamicParamsIntraFrameInterval =
{
  "h264EncDynamicParams.intraFrameInterval",
  MX_DBG_CMD_TYPE_VAR_SINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_DEC          |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMX_VIDEO_CONFIG_DYNAMICPARAMS,
              videoDynamicParams.h264EncDynamicParams.videnc2DynamicParams.intraFrameInterval),
  FIELDOFFSET(OMX_VIDEO_CONFIG_DYNAMICPARAMS,nSize) -
  FIELDOFFSET(OMX_VIDEO_CONFIG_DYNAMICPARAMS,
              videoDynamicParams.h264EncDynamicParams.videnc2DynamicParams.intraFrameInterval),
  0,
  OMTB_H264_VENC_MIN_I_FRM_INTERVAL,
  OMTB_H264_VENC_MAX_I_FRM_INTERVAL,
  OMTB_H264_VENC_DEF_I_FRM_INTERVAL,
  NULL,
  XdbgCmdVarFunc,
  "Intra Frame Interval..........................",
  "<No of frames between two consecutive I frames>",
  "",
  ""
};

/* Entry for Inter period */
PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryDynamicParamsInterFrameInterval =
{
  "h264EncDynamicParams.interFrameInterval",
  MX_DBG_CMD_TYPE_VAR_SINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_DEC          |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMX_VIDEO_CONFIG_DYNAMICPARAMS,
              videoDynamicParams.h264EncDynamicParams.videnc2DynamicParams.interFrameInterval),
  FIELDOFFSET(OMX_VIDEO_CONFIG_DYNAMICPARAMS,nSize) -
  FIELDOFFSET(OMX_VIDEO_CONFIG_DYNAMICPARAMS,
              videoDynamicParams.h264EncDynamicParams.videnc2DynamicParams.interFrameInterval),
  0,
  OMTB_H264_VENC_MIN_B_FRM_INTERVAL,
  OMTB_H264_VENC_MAX_B_FRM_INTERVAL,
  OMTB_H264_VENC_DEF_B_FRM_INTERVAL,
  NULL,
  XdbgCmdVarFunc,
  "Inter Frame Interval..........................",
  "<No of B frames between two consecutive I/P frames>",
  "",
  ""
}; 

/* Entry for Set rate control algorithm */
PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryDynamicParamsRCAlgo =
{
  "h264EncDynamicParams.rcAlgo",
  MX_DBG_CMD_TYPE_VAR_SINT8,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_ENUM         |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMX_VIDEO_CONFIG_DYNAMICPARAMS,videoDynamicParams.h264EncDynamicParams.rateControlParams.rcAlgo),
  FIELDOFFSET(OMX_VIDEO_CONFIG_DYNAMICPARAMS,nSize) -
  FIELDOFFSET(OMX_VIDEO_CONFIG_DYNAMICPARAMS,videoDynamicParams.h264EncDynamicParams.rateControlParams.rcAlgo),
  0,
  OMX_Video_ControlRateDisable,
  OMX_Video_ControlRateMax,
  OMX_Video_ControlRateConstant,
  &enumTblRateCtrlAlg,
  XdbgCmdVarFunc,
  "Rate Control Algorithm........................",
  "",
  "",
  ""
};

/* Entry for Set QP for I frames */
PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryDynamicParamsQpI =
{
  "h264EncDynamicParams.qpI",
  MX_DBG_CMD_TYPE_VAR_SINT8,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_DEC          |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMX_VIDEO_CONFIG_DYNAMICPARAMS,videoDynamicParams.h264EncDynamicParams.rateControlParams.qpI),
  FIELDOFFSET(OMX_VIDEO_CONFIG_DYNAMICPARAMS,nSize) -
  FIELDOFFSET(OMX_VIDEO_CONFIG_DYNAMICPARAMS,videoDynamicParams.h264EncDynamicParams.rateControlParams.qpI),
  0,
  OMTB_H264_VENC_MIN_QP_IPB,
  OMTB_H264_VENC_MAX_QP_IPB,
  OMTB_H264_VENC_DEF_QP_I,
  NULL,
  XdbgCmdVarFunc,
  "Inital QP for I frames........................",
  "<QP # - For I frames>",
  "",
  ""
};


/* Entry for Set QP Max for I frames */
PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryDynamicParamsQpMaxI =
{
  "h264EncDynamicParams.qpMaxI",
  MX_DBG_CMD_TYPE_VAR_SINT8,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_DEC          |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMX_VIDEO_CONFIG_DYNAMICPARAMS,videoDynamicParams.h264EncDynamicParams.rateControlParams.qpMaxI),
  FIELDOFFSET(OMX_VIDEO_CONFIG_DYNAMICPARAMS,nSize) -
  FIELDOFFSET(OMX_VIDEO_CONFIG_DYNAMICPARAMS,videoDynamicParams.h264EncDynamicParams.rateControlParams.qpMaxI),
  0,
  OMTB_H264_VENC_MIN_QP_IPB,
  OMTB_H264_VENC_MAX_QP_IPB,
  OMTB_H264_VENC_MAX_QP_IPB,
  NULL,
  XdbgCmdVarFunc,
  "QP Max for I frames...........................",
  "<QP Max # - For I frames>",
  "",
  ""
};

/* Entry for Set QP Min for I frames */
PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryDynamicParamsQpMinI =
{
  "h264EncDynamicParams.qpMinI",
  MX_DBG_CMD_TYPE_VAR_SINT8,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_DEC          |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMX_VIDEO_CONFIG_DYNAMICPARAMS,videoDynamicParams.h264EncDynamicParams.rateControlParams.qpMinI),
  FIELDOFFSET(OMX_VIDEO_CONFIG_DYNAMICPARAMS,nSize) -
  FIELDOFFSET(OMX_VIDEO_CONFIG_DYNAMICPARAMS,videoDynamicParams.h264EncDynamicParams.rateControlParams.qpMinI),
  0,
  OMTB_H264_VENC_MIN_QP_IPB,
  OMTB_H264_VENC_MAX_QP_IPB,
  OMTB_H264_VENC_MIN_QP_IPB,
  NULL,
  XdbgCmdVarFunc,
  "QP Min for I frames...........................",
  "<QP Min # - For I frames>",
  "",
  ""
};

/* Entry for Set QP Max for P frames */
PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryDynamicParamsQpMaxP =
{
  "h264EncDynamicParams.qpMaxP",
  MX_DBG_CMD_TYPE_VAR_SINT8,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_DEC          |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMX_VIDEO_CONFIG_DYNAMICPARAMS,videoDynamicParams.h264EncDynamicParams.rateControlParams.qpMaxP),
  FIELDOFFSET(OMX_VIDEO_CONFIG_DYNAMICPARAMS,nSize) -
  FIELDOFFSET(OMX_VIDEO_CONFIG_DYNAMICPARAMS,videoDynamicParams.h264EncDynamicParams.rateControlParams.qpMaxP),
  0,
  OMTB_H264_VENC_MIN_QP_IPB,
  OMTB_H264_VENC_MAX_QP_IPB,
  OMTB_H264_VENC_MAX_QP_IPB,
  NULL,
  XdbgCmdVarFunc,
  "QP Max for P frames...........................",
  "<QP Max # - For P frames>",
  "",
  ""
};

/* Entry for Set QP Min for P frames */
PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryDynamicParamsQpMinP =
{
  "h264EncDynamicParams.qpMinP",
  MX_DBG_CMD_TYPE_VAR_SINT8,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_DEC          |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMX_VIDEO_CONFIG_DYNAMICPARAMS,videoDynamicParams.h264EncDynamicParams.rateControlParams.qpMinP),
  FIELDOFFSET(OMX_VIDEO_CONFIG_DYNAMICPARAMS,nSize) -
  FIELDOFFSET(OMX_VIDEO_CONFIG_DYNAMICPARAMS,videoDynamicParams.h264EncDynamicParams.rateControlParams.qpMinP),
  0,
  OMTB_H264_VENC_MIN_QP_IPB,
  OMTB_H264_VENC_MAX_QP_IPB,
  OMTB_H264_VENC_MIN_QP_IPB,
  NULL,
  XdbgCmdVarFunc,
  "QP Min for P frames...........................",
  "<QP Min # - For P frames>",
  "",
  ""
};


/* Entry for Set QP Max for B frames */
PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryDynamicParamsQpMaxB =
{
  "h264EncDynamicParams.qpMaxB",
  MX_DBG_CMD_TYPE_VAR_SINT8,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_DEC          |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMX_VIDEO_CONFIG_DYNAMICPARAMS,videoDynamicParams.h264EncDynamicParams.rateControlParams.qpMaxB),
  FIELDOFFSET(OMX_VIDEO_CONFIG_DYNAMICPARAMS,nSize) -
  FIELDOFFSET(OMX_VIDEO_CONFIG_DYNAMICPARAMS,videoDynamicParams.h264EncDynamicParams.rateControlParams.qpMaxB),
  0,
  OMTB_H264_VENC_MIN_QP_IPB,
  OMTB_H264_VENC_MAX_QP_IPB,
  OMTB_H264_VENC_MAX_QP_IPB,
  NULL,
  XdbgCmdVarFunc,
  "QP Max for B frames...........................",
  "<QP Max # - For B frames>",
  "",
  ""
};

/* Entry for Set QP Min for B frames */
PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryDynamicParamsQpMinB =
{
  "h264EncDynamicParams.qpMinB",
  MX_DBG_CMD_TYPE_VAR_SINT8,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_DEC          |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMX_VIDEO_CONFIG_DYNAMICPARAMS,videoDynamicParams.h264EncDynamicParams.rateControlParams.qpMinB),
  FIELDOFFSET(OMX_VIDEO_CONFIG_DYNAMICPARAMS,nSize) -
  FIELDOFFSET(OMX_VIDEO_CONFIG_DYNAMICPARAMS,videoDynamicParams.h264EncDynamicParams.rateControlParams.qpMinB),
  0,
  OMTB_H264_VENC_MIN_QP_IPB,
  OMTB_H264_VENC_MAX_QP_IPB,
  OMTB_H264_VENC_MIN_QP_IPB,
  NULL,
  XdbgCmdVarFunc,
  "QP Min for B frames...........................",
  "<QP Min # - For B frames>",
  "",
  ""
};


 /* Entry for Set InitialBufferLevel */
PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryDynamicParamsInitialBufferLevel =
{
  "h264EncDynamicParams.initialBufferLevel",
  MX_DBG_CMD_TYPE_VAR_SINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_DEC          |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMX_VIDEO_CONFIG_DYNAMICPARAMS,
              videoDynamicParams.h264EncDynamicParams.rateControlParams.initialBufferLevel),
  FIELDOFFSET(OMX_VIDEO_CONFIG_DYNAMICPARAMS,nSize) -
  FIELDOFFSET(OMX_VIDEO_CONFIG_DYNAMICPARAMS,
              videoDynamicParams.h264EncDynamicParams.rateControlParams.initialBufferLevel),
  0,
  0,
  OMTB_MAX_VAL_S32,
  OMTB_H264_VENC_DEF_BUFFER_LEVEL,
  NULL,
  XdbgCmdVarFunc,
  "Initial Buffer Level..........................",
  "<initial delay for decoder to start consuming the bits>",
  "",
  ""
};

 /* Entry for Set HRDBufferSize */
PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryDynamicParamsHRDBufferSize =
{
  "h264EncDynamicParams.HRDBufferSize",
  MX_DBG_CMD_TYPE_VAR_SINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_DEC          |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMX_VIDEO_CONFIG_DYNAMICPARAMS,
              videoDynamicParams.h264EncDynamicParams.rateControlParams.HRDBufferSize),
  FIELDOFFSET(OMX_VIDEO_CONFIG_DYNAMICPARAMS,nSize) -
  FIELDOFFSET(OMX_VIDEO_CONFIG_DYNAMICPARAMS,
              videoDynamicParams.h264EncDynamicParams.rateControlParams.HRDBufferSize),
  0,
  0,
  OMTB_MAX_VAL_S32,
  OMTB_H264_VENC_DEF_HRD_BUFF_SIZE,
  NULL,
  XdbgCmdVarFunc,
  "HRD Buffer Size...............................",
  "",
  "",
  ""
};


/* Entry for Set MinBlockSizeP */
PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryDynamicParamsMinBlockSizeP =
{
  "h264EncDynamicParams.minBlockSizeP",
  MX_DBG_CMD_TYPE_VAR_SINT8,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_DEC          |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMX_VIDEO_CONFIG_DYNAMICPARAMS,videoDynamicParams.h264EncDynamicParams.interCodingParams.minBlockSizeP),
  FIELDOFFSET(OMX_VIDEO_CONFIG_DYNAMICPARAMS,nSize) -
  FIELDOFFSET(OMX_VIDEO_CONFIG_DYNAMICPARAMS,videoDynamicParams.h264EncDynamicParams.interCodingParams.minBlockSizeP),
  0,
  OMTB_H264_VENC_MIN_BLK_SIZE_P,
  OMTB_H264_VENC_MIN_BLK_SIZE_P,
  OMTB_H264_VENC_MIN_BLK_SIZE_P,
  NULL,
  XdbgCmdVarFunc,
  "Min Block Size P..............................",
  "<No of motion vectors per macroblock for P frames>",
  "",
  ""
};


/* Entry for Set MinBlockSizeB */
PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryDynamicParamsMinBlockSizeB =
{
  "h264EncDynamicParams.minBlockSizeB",
  MX_DBG_CMD_TYPE_VAR_SINT8,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_DEC          |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMX_VIDEO_CONFIG_DYNAMICPARAMS,videoDynamicParams.h264EncDynamicParams.interCodingParams.minBlockSizeB),
  FIELDOFFSET(OMX_VIDEO_CONFIG_DYNAMICPARAMS,nSize) -
  FIELDOFFSET(OMX_VIDEO_CONFIG_DYNAMICPARAMS,videoDynamicParams.h264EncDynamicParams.interCodingParams.minBlockSizeB),
  0,
  OMTB_H264_VENC_MIN_BLK_SIZE_B,
  OMTB_H264_VENC_MIN_BLK_SIZE_B,
  OMTB_H264_VENC_MIN_BLK_SIZE_B,
  NULL,
  XdbgCmdVarFunc,
  "Min Block Size B..............................",
  "<No of motion vectors per macroblock for B frames>",
  "",
  ""
};


/* Enum Entry for Selecting Slice Mode */
PRIVATE MX_DBG_ENUM_ENTRY_T enumTblSliceMode[] =
{
  {"none",   IH264_SLICEMODE_NONE,    ""},
  {"mbunit", IH264_SLICEMODE_MBUNIT,  ""},
  {"bytes",  IH264_SLICEMODE_BYTES,   ""},
  {"offset", IH264_SLICEMODE_OFFSET,  ""},
  {"",       0,                       ""}
};


/* Entry for Setting Slice Mode */
PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryDynamicParamsSliceMode =
{
  "h264EncDynamicParams.sliceMode",
  MX_DBG_CMD_TYPE_VAR_SINT16,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_ENUM          |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMX_VIDEO_CONFIG_DYNAMICPARAMS,videoDynamicParams.h264EncDynamicParams.sliceCodingParams.sliceMode),
  FIELDOFFSET(OMX_VIDEO_CONFIG_DYNAMICPARAMS,nSize) -
  FIELDOFFSET(OMX_VIDEO_CONFIG_DYNAMICPARAMS,videoDynamicParams.h264EncDynamicParams.sliceCodingParams.sliceMode),
  0,
  IH264_SLICEMODE_NONE,
  IH264_SLICEMODE_OFFSET,
  IH264_SLICEMODE_MBUNIT,
  &enumTblSliceMode,
  XdbgCmdVarFunc,
  "Slice Mode....................................",
  "",
  "",
  ""
};

 /* Entry for Set SliceUnitSize */
PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryDynamicParamsSliceUnitSize =
{
  "h264EncDynamicParams.sliceUnitSize",
  MX_DBG_CMD_TYPE_VAR_SINT16,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_DEC          |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMX_VIDEO_CONFIG_DYNAMICPARAMS,
              videoDynamicParams.h264EncDynamicParams.sliceCodingParams.sliceUnitSize),
  FIELDOFFSET(OMX_VIDEO_CONFIG_DYNAMICPARAMS,nSize) -
  FIELDOFFSET(OMX_VIDEO_CONFIG_DYNAMICPARAMS,
              videoDynamicParams.h264EncDynamicParams.sliceCodingParams.sliceUnitSize),
  0,
  0,
  OMTB_MAX_VAL_S16,
  OMTB_H264_VENC_DEF_SLICE_UNIT_SIZE,
  NULL,
  XdbgCmdVarFunc,
  "Slice Unit Size...............................",
  "",
  "",
  ""
};

MX_DBG_CMD_ENTRY_T* cmdListIndexParamVideoDynamicParamsConfig[] =
{
  &cmdEntryDynamicParamsTargetBitrate,
  &cmdEntryDynamicParamsIntraFrameInterval,
  &cmdEntryDynamicParamsInterFrameInterval,
  &cmdEntryDynamicParamsRCAlgo,
  &cmdEntryDynamicParamsQpI,
  &cmdEntryDynamicParamsQpMaxI,
  &cmdEntryDynamicParamsQpMinI,
  &cmdEntryDynamicParamsQpMaxP,
  &cmdEntryDynamicParamsQpMinP,
  &cmdEntryDynamicParamsQpMaxB,
  &cmdEntryDynamicParamsQpMinB,
  &cmdEntryDynamicParamsInitialBufferLevel,
  &cmdEntryDynamicParamsHRDBufferSize,
  &cmdEntryDynamicParamsMinBlockSizeP,
  &cmdEntryDynamicParamsMinBlockSizeB,
  &cmdEntryDynamicParamsSliceMode,
  &cmdEntryDynamicParamsSliceUnitSize,
  NULL
};

MX_DBG_CMD_TABLE_T cmdTblIndexParamVideoDynamicParamsConfig =
{
  MX_DBG_ACCESS_ALL,
  sizeof(cmdListIndexParamVideoDynamicParamsConfig)/sizeof(cmdListIndexParamVideoDynamicParamsConfig[0]),
  cmdListIndexParamVideoDynamicParamsConfig
};

#endif
/*
 * <<< OMX_VIDEO_CONFIG_DYNAMICPARAMS
 */