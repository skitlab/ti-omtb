/*
 * omtbH264Venc.h
 *
 * This file contains component specific definitions/data types etc.
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

#ifndef __OMTB_H264_VENC_H__
#define __OMTB_H264_VENC_H__


/******************************************************************************\
 *      Includes
\******************************************************************************/

#include "OMX_Core.h"
#include "OMX_Component.h"
#include "OMX_Types.h"
#include "OMX_Video.h"
#include "OMX_IVCommon.h"
#include "OMX_TI_Video.h"
#include "omtbPortParam.h"
#include "omtbTypes.h"
#include "OMX_TI_Common.h"
#include "omtbClient.h"

/******************************************************************************/

#ifdef __cplusplus    /* required for headers that might */
 extern "C" {         /* be compiled by a C++ compiler */
#endif


/******************************************************************************\
 *      Defines
\******************************************************************************/

#define OMTB_H264_VENC_MAX_INBUF_SIZE       ((1920 * 1080 * 3) >> 1)/* Max I/P buffer size*/
#define OMTB_H264_VENC_MAX_OUTBUF_SIZE      (1920 * 1080)/* Max O/P buffer size*/
#define OMTB_H264_VENC_COMPONENT_NAME       ("OMX.TI.DUCATI.VIDENC")
#define OMTB_H264_VENC_COMP_REF_STR         ("h264venc")/* comp ref string */
#define OMTB_H264_VENC_GROUP_PRIORITY       (2)         /* Task priority */
#define OMTB_H264_VENC_TSK_STACK_SIZE       (30 * 1024) /* Task stack size */
#define OMTB_H264_VENC_NUM_DYN_PARAMS       (8)  /* Task stack size */
#define OMTB_H264_VENC_MAX_FRM_NO_ENTRIES   (10) /* Task stack size */
#define OMTB_H264_VENC_NUM_IN_BUFS          (4)  /* No of i/p Buffers for H264 */
#define OMTB_H264_VENC_NUM_OUT_BUFS         (4)  /* No of o/p Buffers for H264 */
#define OMTB_H264_VENC_MAX_NUM_IN_BUFS      (32) /* Max i/p Buffers for H264 */
#define OMTB_H264_VENC_MAX_NUM_OUT_BUFS     (32) /* Max o/p Buffers for H264 */

#define OMTB_H264_VENC_INPUT_PORT_IDX       (0) /* Input port index */
#define OMTB_H264_VENC_OUTPUT_PORT_IDX      (1) /* Output port index */
#define OMTB_H264_VENC_INVALID_PORT_IDX     (5) /* Invalid port index */


#define OMTB_H264_VENC_DEF_WIDTH            (720)
#define OMTB_H264_VENC_DEF_HEIGHT           (480)

#define OMTB_H264_VENC_MIN_I_FRM_INTERVAL   (0)
#define OMTB_H264_VENC_DEF_I_FRM_INTERVAL   (128)
#define OMTB_H264_VENC_MAX_I_FRM_INTERVAL   (512)

#define OMTB_H264_VENC_MIN_P_FRM_INTERVAL   (1)
#define OMTB_H264_VENC_DEF_P_FRM_INTERVAL   (1)
#define OMTB_H264_VENC_MAX_P_FRM_INTERVAL   (256)

#define OMTB_H264_VENC_MIN_B_FRM_INTERVAL   (0)
#define OMTB_H264_VENC_DEF_B_FRM_INTERVAL   (1)
#define OMTB_H264_VENC_MAX_B_FRM_INTERVAL   (256)

#define OMTB_H264_VENC_MIN_NUM_REF_FRM      (0)
#define OMTB_H264_VENC_DEF_NUM_REF_FRM      (0)
#define OMTB_H264_VENC_MAX_NUM_REF_FRM      (16)

#define OMTB_H264_VENC_DEF_REF_IDX_10       (0)
#define OMTB_H264_VENC_DEF_REF_IDX_11       (0)

/* This params values need to be verified/corrected if wrong */
#define OMTB_H264_VENC_DEF_SLICE_HDR_SPACING      (0)
#define OMTB_H264_VENC_DEF_ALLOWED_PIC_TYPE       (0)
#define OMTB_H264_VENC_DEF_WEIGHTED_BIPRED_MODE   (0)
#define OMTB_H264_VENC_DEF_CABAC_INIT_IDX         (0)
#define OMTB_H264_VENC_DEF_NUM_SLICE_GRP          (0)
#define OMTB_H264_VENC_DEF_SLICE_GRP_MAP_TYPE     (0)

#define OMTB_H264_VENC_DEF_LUMA_INTRA_4x4_PRED    (0x1FF)
#define OMTB_H264_VENC_MAX_LUMA_INTRA_4x4_PRED    (0x1FF)

#define OMTB_H264_VENC_DEF_LUMA_INTRA_8x8_PRED    (0x1FF)
#define OMTB_H264_VENC_MAX_LUMA_INTRA_8x8_PRED    (0x1FF)

#define OMTB_H264_VENC_DEF_LUMA_INTRA_16x16_PRED  (0x0F)
#define OMTB_H264_VENC_MAX_LUMA_INTRA_16x16_PRED  (0x0F)

#define OMTB_H264_VENC_DEF_CHROMA_INTRA_8x8_PRED  (0x0F)
#define OMTB_H264_VENC_MAX_CHROMA_INTRA_8x8_PRED  (0x0F)


#define OMTB_H264_VENC_DEF_FRM_RATE     (60 << 16)  /* Def framerate Q16 Format*/

#define OMTB_H264_VENC_DEF_BIT_RATE     (10*1024*1024)   /* Def bitrate */

#define OMTB_H264_VENC_DEF_MESR_HORP    (16)        /* Def ME Search range: P */
#define OMTB_H264_VENC_DEF_MESR_VERP    (16)        /* Def ME Search range: P */
#define OMTB_H264_VENC_DEF_MESR_HORB    (16)        /* Def ME Search range: B */
#define OMTB_H264_VENC_DEF_MESR_VERB    (16)        /* Def ME Search range: B */

#define OMTB_H264_VENC_DEF_MVSR_X       (16)        /* Def MV Search range: X */
#define OMTB_H264_VENC_DEF_MVSR_Y       (16)        /* Def MV Search range: Y */

#define OMTB_H264_VENC_MIN_QP_IPB       (0)         /* Min QP - For I, P & B */
#define OMTB_H264_VENC_MAX_QP_IPB       (51)        /* Max QP - For I, P & B */
#define OMTB_H264_VENC_DEF_QP_I         (25)        /* Def QP - For I frames */
#define OMTB_H264_VENC_DEF_QP_P         (25)        /* Def QP - For P frames */
#define OMTB_H264_VENC_DEF_QP_B         (4)         /* Def QP - For B frames */

#define OMTB_H264_VENC_MAX_SLICE_SIZE   (500)       /* Max QP - For I, P & B */
/* This params values need to be verified/corrected if wrong */
#define OMTB_H264_VENC_DEF_SLICE_SIZE   (0)         /* Def QP - For I, P & B */

#define OMTB_H264_VENC_MAX_NUM_MB       ( (OMTB_MAX_VID_WIDTH >> 4) * \
                                          (OMTB_MAX_VID_HEIGHT >> 4))

#define OMTB_H264_VENC_DEF_NO_OF_PORTS     (2) /* No of ports */
#define OMTB_H264_VENC_DEF_START_PORT_NUM  (0) /* Start Port Number */

#define OMTB_H264_VENC_MAX_IN_PORT  (1)
#define OMTB_H264_VENC_MAX_OUT_PORT  (1)

#define OMTB_SIZE_SPS_PPS_HDR (128)
#define OMTB_MAX_FILE_SIZE    (512 * 1024 * 1024) /* 512MB */

#define OMTB_H264_VENC_MAX_WRITE_SIZE (1920 * 1080)

#define OMTB_H264_VENC_DEF_HRD_BUFF_SIZE (OMTB_H264_VENC_DEF_BIT_RATE)
#define OMTB_H264_VENC_DEF_BUFFER_LEVEL  (OMTB_H264_VENC_DEF_BIT_RATE)

#define OMTB_H264_VENC_MIN_BLK_SIZE_P (1)
#define OMTB_H264_VENC_MAX_BLK_SIZE_P (4)
#define OMTB_H264_VENC_DEF_BLK_SIZE_P (1)

#define OMTB_H264_VENC_MIN_BLK_SIZE_B (1) 
#define OMTB_H264_VENC_MAX_BLK_SIZE_B (4) 
#define OMTB_H264_VENC_DEF_BLK_SIZE_B (1)

#define OMTB_H264_VENC_DEF_SLICE_UNIT_SIZE (11200)
/******************************************************************************\
 *      Data type definitions
\******************************************************************************/

/*!
*******************************************************************************
*  \struct OMTB_H264_VENC_INPORT_PARAMS
*  \brief  H264 video encoder specific input port parameters
*******************************************************************************
*/

typedef struct OMTB_H264_VENC_INPORT_PARAMS_T
{
  OMTB_INPORT_PARAMS  cmnInParams;    /* Common i/p port params */
  OMX_BUFFERHEADERTYPE* pInBuff[OMTB_H264_VENC_MAX_NUM_IN_BUFS];
                                      /* I/P Buffers*/
  OMX_COLOR_FORMATTYPE colorFormat;   /* I/P Color Format */
  unsigned int nWidth;                /* I/P Frame Width */
  unsigned int nHeight;               /* I/P Frame Height */
  unsigned int frameCount;            /* Frame counter */
  unsigned int nStride;               /* # of bytes per span */
}OMTB_H264_VENC_INPORT_PARAMS;


/*!
*******************************************************************************
*  \struct OMTB_H264_VENC_OUTPORT_PARAMS
*  \brief  H264 video encoder specific output port parameters
*******************************************************************************
*/

typedef struct OMTB_H264_VENC_OUTPORT_PARAMS_T
{
  OMTB_OUTPORT_PARAMS cmnOutParams;   /* Common o/p port params */
  OMX_BUFFERHEADERTYPE* pOutBuff[OMTB_H264_VENC_MAX_NUM_OUT_BUFS];
                                      /* O/P Bufs */

}OMTB_H264_VENC_OUTPORT_PARAMS;


/* Application's private structure for OMX H264 Video Encoder Component*/

typedef struct OMTB_H264_VENC_PRIVATE_T
{

  OMTB_APP_PRIVATE omtbPvt;         /* OMTB common pvt data */
  OMTB_CLIENT_INPORT_PARAMS *inPortParams;
                                    /* H264Venc specific params */
  OMTB_CLIENT_OUTPORT_PARAMS *outPortParams;
                                    /* H264Venc specific params */
  OMX_VIDEO_PARAM_AVCTYPE* pH264;   /* H264 video param struct */
  char  compressionFormat;          /* encoder compression format */
  void* eofSem;                     /* End of Stream Semaphore */
 
  char outputFile[OMTB_MAX_LEN];    /* Array to store o/p File Name */
  unsigned long int fileSize;
  unsigned long int maxFileSize;
}OMTB_H264_VENC_PRIVATE;


/* Configuration structure for OMX H264 Video Enocder Component */

typedef struct OMTB_H264_VENC_CONFIG_PARAMS_T
{
  OMTB_BASIC_CONFIG_PARAMS sBasicParams;
                                    /*Basic configuration Params */
  OMX_VIDEO_PARAM_AVCTYPE sAVCParams;
                                    /* AVC config params */
  OMX_VIDEO_PARAM_BITRATETYPE sParamBitRate;
                                    /* Bitrate & Control rate */
  OMX_VIDEO_PARAM_PROFILELEVELTYPE sProfileLevel;
                                    /* H264 profile & level */
  OMX_VIDEO_PARAM_AVCBITSTREAMFORMATTYPE sBitStreamFormat;
                                    /* Bitstream format*/
  OMX_VIDEO_PARAM_ENCODER_PRESETTYPE sEncoderPreset;
                                    /* Encoding & Rate control preset */									
  OMX_VIDEO_PARAM_FRAMEDATACONTENTTYPE sInputImgFmt;
                                    /* Input Image format */									
  OMX_VIDEO_PARAM_TRANSFORM_BLOCKSIZETYPE sTransformBlockSize;
                                    /* Transform BLK size */
  OMX_CONFIG_CHANNELGROUPINFO sConfigChannelGroupInfo;
                                    /* To configure the multi port group MFQs */  
  OMX_VIDEO_PARAM_AVCSLICEFMO sAVCSliceFMO;
                                    /* FMO slice mode params */
  OMX_CONFIG_CHANNELNAME sChannelName;
                                    /* To configure capture channel name */
  OMX_PARAM_BUFFER_MEMORYTYPE sMemTypeCfg;
  									/* To configure the buffer memory type*/
  OMX_PARAM_BUFFERSUPPLIERTYPE sBufSupplier;
  									/* To configure the buffer supplier type*/
  OMX_VIDEO_PARAM_PORTFORMATTYPE sVideoPortFormat;
                                    /* To configure the video params*/
  OMX_VIDEO_PARAM_MOTIONVECTORTYPE sMotionVectorType;
                                    /* To configure the Motion Vector Type*/										
  OMX_VIDEO_PARAM_QUANTIZATIONTYPE sQuantType;
  									/* To configure the Quantization parameters*/
  OMX_PORT_PARAM_TYPE sPortInit;    /* To configure the port init params*/									

  /* Dynamic configuration params */
  OMX_CONFIG_FRAMERATETYPE sFrameRate;
                                    /* Framerate */
  OMX_VIDEO_CONFIG_BITRATETYPE sConfigBitRate;
                                    /* Bitrate */
  OMX_VIDEO_CONFIG_MESEARCHRANGETYPE sMESearchrange;
                                    /* Motion estimation search range */
  OMX_CONFIG_INTRAREFRESHVOPTYPE sForceFrame;
                                    /* Intra referesh VOP type */
  OMX_VIDEO_CONFIG_QPSETTINGSTYPE sQPSettings;
                                    /* QP settings */
  OMX_VIDEO_CONFIG_AVCINTRAPERIOD sAVCIntraPeriod;
                                    /* Intra frame period */
  OMX_VIDEO_CONFIG_SLICECODINGTYPE sSliceSettings;
                                    /* Slice settings */
  OMX_VIDEO_CONFIG_PIXELINFOTYPE sPixelInfo;
                                    /* Pixel information like aspect ratio */

  /* Advanced configuration params */
  OMX_VIDEO_PARAM_AVCNALUCONTROLTYPE sNALUSettings;
                                    /* NALU settings */
  OMX_VIDEO_PARAM_AVCADVANCEDFMOTYPE sAVCAdvancedFMO;
                                    /* Advanced FMO settings */									
  OMX_VIDEO_PARAM_MEBLOCKSIZETYPE sMEBlockSize;
                                    /* ME block size */
  OMX_VIDEO_PARAM_INTRAREFRESHTYPE sIntraRefresh;
                                    /* Intra refresh period */
  OMX_VIDEO_PARAM_VUIINFOTYPE sVUISettings;
                                    /* VUI settings */
  OMX_VIDEO_PARAM_INTRAPREDTYPE sIntraPred;
                                    /* Intra prediction modes */
  OMX_VIDEO_PARAM_DATASYNCMODETYPE  sVidDataMode;
                                    /* Video data mode */
  OMX_VIDEO_CONFIG_NALSIZE sNalSize;
                                   /* To configure the nal size*/
  OMX_PARAM_COMPPORT_NOTIFYTYPE sCompPortNotifyType;
  									/* To configure the compport notify type*/
  OMX_PARAM_PORTDEFINITIONTYPE sPortDefType;									
                                    /* To configure the port defination */	
#ifdef _VIDEO_M3_DYNAMIC_CONFIG
  OMX_VIDEO_CONFIG_DYNAMICPARAMS sDynamicParams;
                                    /* To configure the Dynamic parameters */	  
#endif                                    
}OMTB_H264_VENC_CONFIG_PARAMS;

/******************************************************************************\
 *      Macros
\******************************************************************************/


/******************************************************************************\
 *      Globals
\******************************************************************************/


/******************************************************************************\
 *      External Object Definitions
\******************************************************************************/


/******************************************************************************\
 *      Public Function Prototypes
\******************************************************************************/


/******************************************************************************\
 *      H264VENC_GetStructIdx Function Prototype
\******************************************************************************/
/**
 *
 *  @brief    Get config index and structure pointer based on the index string
 *
 *  @param in:
 *            char *: Pointer to config structure index string
 *
 *            unsigned int: Template number to be used for configuration
 *
 *            unsigned int: Port index
 *
 *  @param Out:
 *            unsigned int*: Pointer to configuration structure index
 *
 *            void *: Pointer to config structure
 *
 *  @return   OmtbRet - OMTB return code
 *
 */

OmtbRet H264VENC_GetStructIdx(
  char *indexStr,
  unsigned int template,
  unsigned int instanceNo,
  unsigned int portIdx,
  unsigned int *nConfigIndex,
  void **pCompCfgStruct);

/******************************************************************************\
 *      H264VENC_SetInputPortPrototype Function Prototype
\******************************************************************************/
/**
 *
 *  @brief    Set i/p port params.
 *
 *  @param in:
 *            h264VencClient:Pointer to appPrivateType structure
 *
 *  @param Out:
 *            None
 *
 *  @return   OMX_ERRORTYPE - OMX std return/error code
 *
 */

OMX_ERRORTYPE H264VENC_SetInputPortDefinition(OMTB_H264_VENC_PRIVATE* h264VencClient);


/******************************************************************************\
 *      H264VENC_SetOutputPortPrototype Function Prototype
\******************************************************************************/
/**
 *
 *  @brief    Set o/p port params.
 *
 *  @param in:
 *            h264VencClient:Pointer to appPrivateType structure
 *
 *  @param Out:
 *            None
 *
 *  @return   OMX_ERRORTYPE - OMX std return/error code
 *
 */

OMX_ERRORTYPE H264VENC_SetOutputPortDefinition(OMTB_H264_VENC_PRIVATE* h264VencClient);


/******************************************************************************\
 *      H264VENC_SetPortPrototype Function Prototype
\******************************************************************************/
/**
 *
 *  @brief    Set i/o port params.
 *
 *  @param in:
 *            h264VencClient:Pointer to appPrivateType structure
 *
 *  @param Out:
 *            None
 *
 *  @return   OMX_ERRORTYPE - OMX std return/error code
 *
 */

OMX_ERRORTYPE H264VENC_SetPortDefinition(void* thisClient);



/******************************************************************************\
 *      H264VENC_SetBasicParams Function Prototype
\******************************************************************************/
/**
 *
 *  @brief    Initializes initial basic cfg params.
 *
 *  @param in:
 *            h264VencClient: Pointer to appPrivateType structure
 *
 *            template: template no to be used
 *
 *            portIdx: port on which configuration is to be done
 *
 *  @param Out:
 *            None
 *
 *  @return   None
 *
 */

void H264VENC_SetBasicParams(
  OMTB_H264_VENC_PRIVATE* h264VencClient,
  int template,
  int portIdx);

/******************************************************************************\
 *      H264VENC_FuncTsk Thread Prototype
\******************************************************************************/
/**
 *
 *  @brief    This is a H264 thread which invokes during func command
 *
 *  @param in:
 *            void * - Thread args count
 *
 *            void *threads_arg - Pointer to thread arg structure
 *
 *  @return   None
 *
 */

void H264VENC_FuncTsk(void *argc, void *threadsArg);

/******************************************************************************\
 *      H264VENC_ConfigureRunTimeSettings Function Prototype
\******************************************************************************/
/**
 *
 *  @brief    Run time configuration parameter settings for H264VENC
 *
 *  @param in:
 *            componentName: Component Name String
 *
 *            instance     : Component instance number
 *
 *            template     : Cfg Template number to be used
 *
 *            portIdx      : Port number to which cfg to be done
 *
 *            frameNum     : Current I/P or O/P Frame number
 *
 *
 *  @return   err       : OmtbRet
 *
 */

OmtbRet H264VENC_ConfigureRunTimeSettings(
  OMX_STRING componentName,
  OMX_U32 instance,
  OMX_U32 template,
  OMX_U32 portIdx,
  OMX_U32 frameNum,
  OMX_STRING structIdxStr);


/******************************************************************************\
 *      H264VENC_ClassInit Function Definition
\******************************************************************************/
/*
 *
 *  @brief    This function sets the defalut values to an instance of the class.
 *
 *  @param in:
 *            thisClient: Pointer to appPrivateType structure
 *
 *  @param Out:
 *            None
 *
 *  @return
 *            OMTB_SUCCESS           successful
 *
 */
OMX_ERRORTYPE H264VENC_ClassInit(OMTB_CLIENT_PRIVATE* thisClient);		
#ifdef __cplusplus    /* matches __cplusplus construct above */
 }
#endif

#endif


/*--------------------------------- end of file -----------------------------*/
