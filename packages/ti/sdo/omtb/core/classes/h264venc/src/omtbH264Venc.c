/*
 * omtbH264Venc.c
 *
 * Component specific IL Client Implementation.
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
#include <string.h>
#include <stdlib.h>

/* OMX standard header files */
#include "OMX_Core.h"
#include "OMX_Component.h"
#include "OMX_Types.h"
#include "OMX_TI_Index.h"
#include "domx_util.h"

/******************************************************************************\
 *      Customized Includes
\******************************************************************************/

#include "omtbDebug.h"
#include "timm_osal_interfaces.h"
#include "omtbCommon.h"
#include "omtbCmd.h"


/******************************************************************************\
 *      Local Defines
\******************************************************************************/

/******************************************************************************\
 *      Data type definitions
\******************************************************************************/

/* Callback structure Definition */

static OMX_CALLBACKTYPE H264VENC_Callback = {
  OMTB_ClientEventHandler,      /* Event handler callback */
  OMTB_ClientEmptyBufferDone,   /* Empty buffer done callback */
  OMTB_ClientFillBufferDone     /* Fill buffer done callback */
};


/******************************************************************************\
 *      Extern Object Definitions
\******************************************************************************/

// Component class structure which holds component instance handle,
// application private data etc
extern OMTB_COMP_HANDLE omtbClass[OMTB_MAX_CLASS];

/* Streaming (I/P and O/P) thread arguments */
extern OMTB_DATA_THREAD_ARG strmThreadArg[OMTB_MAX_INS];

/* Pointer to OMTB configuration template */
extern OMTB_TEMPLATE_INFO    *omtbCfgTemplate[OMTB_MAX_INS];

/* Func/API thread arguments */
extern OMTB_DATA_THREAD_ARG funcThreadArg[OMTB_MAX_INS];

/* global semaphote used for proprietary tunneling */
extern void *gOmtbEofSem;

/* global flag used for demo */
extern OMX_BOOL gOmtbStopVencDemoFlag;

/* global semaphote used for vdec demo */
extern void *gOmtbVencDemoSem;
/******************************************************************************\
 *      Globals
\******************************************************************************/

/* Pointer to H264 venc config params */
OMTB_H264_VENC_CONFIG_PARAMS *h264VencConfig = NULL;


/******************************************************************************\
 *      Static Globals
\******************************************************************************/
static OMX_U32 H264VENC_funcCreateCount = 0;  /* Func create count */
static OMX_U32 H264VENC_apiCreateCount = 0;   /* API create count */

static OMX_U32 H264VENC_funcDeleteCount = 0;  /* Func delete count */
static OMX_U32 H264VENC_apiDeleteCount = 0;   /* API delete count */

/* Enum Entry for Supported cfg param indexs */

PRIVATE MX_DBG_ENUM_ENTRY_T enumTblH264VencCfgParamIdx[] =
{

  /* Basic configuration params */
  {"OMX_IndexParamVideoAvc",
    OMX_IndexParamVideoAvc,
    ""},
	
  {"OMX_IndexParamVideoBitrate",
    OMX_IndexParamVideoBitrate,
    ""},

  {"OMX_IndexParamVideoProfileLevelCurrent",
    OMX_IndexParamVideoProfileLevelCurrent,
    ""},

  {"OMX_TI_IndexParamVideoBitStreamFormatSelect",
    OMX_TI_IndexParamVideoBitStreamFormatSelect,
    ""},

  {"OMX_TI_IndexParamVideoEncoderPreset",
    OMX_TI_IndexParamVideoEncoderPreset,
    ""},

  {"OMX_TI_IndexParamVideoFrameDataContentSettings",
    OMX_TI_IndexParamVideoFrameDataContentSettings,
    ""},

  {"OMX_TI_IndexParamVideoTransformBlockSize",
    OMX_TI_IndexParamVideoTransformBlockSize,
    ""},

  {"OMX_TI_IndexConfigChannelGroupInfo",
    OMX_TI_IndexConfigChannelGroupInfo,
    ""},

  {"OMX_IndexParamVideoSliceFMO",
    OMX_IndexParamVideoSliceFMO,
    ""},
  
  {"OMX_TI_IndexConfigChannelName",
    OMX_TI_IndexConfigChannelName,
    ""},
	
  {"OMX_TI_IndexParamBuffMemType",
    OMX_TI_IndexParamBuffMemType,
    ""},

  {"OMX_IndexParamCompBufferSupplier",
    OMX_IndexParamCompBufferSupplier,
    ""},

  {"OMX_IndexParamVideoPortFormat",
    OMX_IndexParamVideoPortFormat,
    ""},
  {"OMX_IndexParamVideoMotionVector",
    OMX_IndexParamVideoMotionVector,
    ""},

  {"OMX_IndexParamVideoQuantization",
    OMX_IndexParamVideoQuantization,
    ""},

  {"OMX_IndexParamVideoInit",
	OMX_IndexParamVideoInit,
	""},

		
	
  /* Dynamic configuration params */
  {"OMX_IndexConfigVideoFramerate",
    OMX_IndexConfigVideoFramerate,
    ""},
  {"OMX_IndexConfigVideoBitrate",
    OMX_IndexConfigVideoBitrate,
    ""},
  {"OMX_TI_IndexConfigVideoMESearchRange",
    OMX_TI_IndexConfigVideoMESearchRange,
    ""},
  {"OMX_IndexConfigVideoIntraVOPRefresh",
    OMX_IndexConfigVideoIntraVOPRefresh,
    ""},
  {"OMX_TI_IndexConfigVideoQPSettings",
    OMX_TI_IndexConfigVideoQPSettings,
    ""},
  {"OMX_IndexConfigVideoAVCIntraPeriod",
    OMX_IndexConfigVideoAVCIntraPeriod,
    ""},
  {"OMX_TI_IndexConfigSliceSettings",
    OMX_TI_IndexConfigSliceSettings,
    ""},
  {"OMX_TI_IndexConfigVideoPixelInfo",
    OMX_TI_IndexConfigVideoPixelInfo,
    ""},
  {"OMX_IndexConfigVideoNalSize",
	OMX_IndexConfigVideoNalSize,
	""},	

  /* Advanced configuration params */
  {"OMX_TI_IndexParamVideoNALUsettings",
    OMX_TI_IndexParamVideoNALUsettings,
    ""},
  {"OMX_TI_IndexParamVideoAdvancedFMO",
    OMX_TI_IndexParamVideoAdvancedFMO,
    ""},
  {"OMX_TI_IndexParamVideoMEBlockSize",
    OMX_TI_IndexParamVideoMEBlockSize,
    ""},
  {"OMX_IndexParamVideoIntraRefresh",
    OMX_IndexParamVideoIntraRefresh,
    ""},
  {"OMX_TI_IndexParamVideoVUIsettings",
    OMX_TI_IndexParamVideoVUIsettings,
    ""},
  {"OMX_TI_IndexParamVideoIntraPredictionSettings",
    OMX_TI_IndexParamVideoIntraPredictionSettings,
    ""},
  {"OMX_TI_IndexParamVideoDataSyncMode",
    OMX_TI_IndexParamVideoDataSyncMode,
    ""},
  {"OMX_TI_IndexParamCompPortNotifyType",
    OMX_TI_IndexParamCompPortNotifyType,
    ""},  
  {"OMX_IndexParamPortDefinition",
    OMX_IndexParamPortDefinition,
    ""},  	
  {"OMX_TI_IndexConfigVideoDynamicParams",
    OMX_TI_IndexConfigVideoDynamicParams,
    ""},  		
  {"", 0, ""}
};


/******************************************************************************\
 *      Public Function Prototypes
\******************************************************************************/

/******************************************************************************\
 *      Private Function Prototypes
\******************************************************************************/


/******************************************************************************\
 *      Function Definitions
\******************************************************************************/

/******************************************************************************\
 *      H264VENC_SetInputPortDefinition Function Definition
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

OMX_ERRORTYPE H264VENC_SetInputPortDefinition(OMTB_H264_VENC_PRIVATE* h264VencClient)
{

  OMX_ERRORTYPE err = OMX_ErrorNone;
  OMTB_OMX_API_TIMING_VAR_DECL;

  /* validate the function arguments */
  ASSERT(NULL != h264VencClient);

  PRINT(PRINT_FUNCTION_NAME, "Entering <Function , instance #> : <%s , %d>\n",
                              __FUNCTION__, (int)h264VencClient->omtbPvt.instanceNo);

  if(OMX_FALSE == h264VencClient->inPortParams->cmnInParams.inBufSzFlag)
  {
    /* input buffer size calculation based on frame dimension speculation */
    switch(h264VencClient->inPortParams->colorFormat)
    {
      case OMX_COLOR_FormatYUV420Planar:
      case OMX_COLOR_FormatYUV420SemiPlanar:

        h264VencClient->inPortParams->cmnInParams.bufferInSize   =
                      ((h264VencClient->inPortParams->nWidth *
                      h264VencClient->inPortParams->nHeight * 3)
                      >> 1);

        break;

      case OMX_COLOR_FormatYUV422Planar:
      case OMX_COLOR_FormatYCbYCr:

        h264VencClient->inPortParams->cmnInParams.bufferInSize   =
                      (h264VencClient->inPortParams->nWidth *
                      h264VencClient->inPortParams->nHeight * 2);

        break;

      default:

        PRINT(PRINT_MUST, "Undefined chroma format. Setting i/p buffer size for \
  420p \n");
        h264VencClient->inPortParams->cmnInParams.bufferInSize   =
                      ((h264VencClient->inPortParams->nWidth *
                      h264VencClient->inPortParams->nHeight * 3)
                      >> 1);

        break;

    } // switch(h264VencClient->inPortParams->colorFormat)

  } // if(OMX_FALSE == h264VencClient->inPortParams->cmnInParams.inBufSzFlag)

  /* Set the component's OMX_PARAM_PORTDEFINITIONTYPE structure (input) */
  OMTB_SetHeader( h264VencClient->inPortParams->cmnInParams.pInPortDef,
                  sizeof(OMX_PARAM_PORTDEFINITIONTYPE));

  h264VencClient->inPortParams->cmnInParams.pInPortDef->nPortIndex          = OMTB_H264_VENC_INPUT_PORT_IDX;
  /* Get the default values of input port params set by the encoder*/
  err = OMX_GetParameter( h264VencClient->omtbPvt.handle,
                          OMX_IndexParamPortDefinition,
                          h264VencClient->inPortParams->cmnInParams.pInPortDef);
  if(OMX_ErrorNone != err)
  {
	OMTB_OmxReturnStatus(err);
	return err;
  }
  h264VencClient->inPortParams->cmnInParams.pInPortDef->eDir                = OMX_DirInput;
  
  h264VencClient->inPortParams->cmnInParams.pInPortDef->nBufferCountActual  =
                                  h264VencClient->inPortParams->cmnInParams.numInBuf;
  h264VencClient->inPortParams->cmnInParams.pInPortDef->nBufferCountMin     = 1;

  h264VencClient->inPortParams->cmnInParams.pInPortDef->nBufferSize         =
                                  h264VencClient->inPortParams->cmnInParams.bufferInSize;
  h264VencClient->inPortParams->cmnInParams.pInPortDef->bEnabled            = OMX_FALSE;
  h264VencClient->inPortParams->cmnInParams.pInPortDef->bPopulated          = OMX_FALSE;
  h264VencClient->inPortParams->cmnInParams.pInPortDef->eDomain             =
                                  OMX_PortDomainVideo;
  h264VencClient->inPortParams->cmnInParams.pInPortDef->bBuffersContiguous  = OMX_FALSE;
  h264VencClient->inPortParams->cmnInParams.pInPortDef->nBufferAlignment    = 0x0;

  /* OMX_VIDEO_PORTDEFINITION values for input port */
  h264VencClient->inPortParams->cmnInParams.pInPortDef->format.video.pNativeRender  = NULL;
  h264VencClient->inPortParams->cmnInParams.pInPortDef->format.video.cMIMEType      = "H264";
  //h264VencClient->inPortParams->cmnInParams.pInPortDef->format.video.nSliceHeight   = 16;
  //h264VencClient->inPortParams->cmnInParams.pInPortDef->format.video.nBitrate       = 0;
  //h264VencClient->inPortParams->cmnInParams.pInPortDef->format.video.xFramerate     = 0;
  h264VencClient->inPortParams->cmnInParams.pInPortDef->format.video.eColorFormat   =
                    h264VencClient->inPortParams->colorFormat;
  h264VencClient->inPortParams->cmnInParams.pInPortDef->format.video.nFrameWidth    =
                    h264VencClient->inPortParams->nWidth;
  h264VencClient->inPortParams->cmnInParams.pInPortDef->format.video.nFrameHeight   =
                    h264VencClient->inPortParams->nHeight;
  h264VencClient->inPortParams->cmnInParams.pInPortDef->format.video.nStride        =
                    h264VencClient->inPortParams->nWidth;
  /*h264VencClient->inPortParams->cmnInParams.pInPortDef->format.video.eCompressionFormat =
                    OMX_VIDEO_CodingAVC;
   */
  h264VencClient->inPortParams->cmnInParams.pInPortDef->format.video.bFlagErrorConcealment =
                    OMX_FALSE;

  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;

  /*Set the inPort Definition*/
  err = OMX_SetParameter( h264VencClient->omtbPvt.handle,
                          OMX_IndexParamPortDefinition,
                          h264VencClient->inPortParams->cmnInParams.pInPortDef);

  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_SetParameter");

  if(OMX_ErrorNone != err)
  {
    OMTB_OmxReturnStatus(err);
    return err;
  }

  PRINT(PRINT_FUNCTION_NAME, "Leaving <Function , instance #> : <%s , %d>\n",
                              __FUNCTION__, (int)h264VencClient->omtbPvt.instanceNo);

  return err;
}


/******************************************************************************\
 *      H264VENC_SetOutputPortDefinition Function Definition
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

OMX_ERRORTYPE H264VENC_SetOutputPortDefinition(OMTB_H264_VENC_PRIVATE* h264VencClient)
{

  OMX_ERRORTYPE err = OMX_ErrorNone;
  OMTB_OMX_API_TIMING_VAR_DECL;
  OMTB_H264_VENC_CONFIG_PARAMS *h264VencConfig = NULL; //added by arun

  /* validate the function arguments */
  ASSERT(NULL != h264VencClient);

  PRINT(PRINT_FUNCTION_NAME, "Entering <Function , instance #> : <%s , %d>\n",
                              __FUNCTION__, (int)h264VencClient->omtbPvt.instanceNo);
  h264VencConfig = (OMTB_H264_VENC_CONFIG_PARAMS*)
                       &(omtbCfgTemplate[h264VencClient->omtbPvt.templateNo]->h264VencTemplate);

  if(OMX_FALSE == h264VencClient->outPortParams->cmnOutParams.outBufSzFlag)
  {
    h264VencClient->outPortParams->cmnOutParams.bufferOutSize = OMTB_H264_VENC_MAX_OUTBUF_SIZE;
  }

  OMTB_SetHeader( h264VencClient->outPortParams->cmnOutParams.pOutPortDef,
                  sizeof(OMX_PARAM_PORTDEFINITIONTYPE));

  /* Set the component's OMX_PARAM_PORTDEFINITIONTYPE structure (output) */

  h264VencClient->outPortParams->cmnOutParams.pOutPortDef->nPortIndex         = OMTB_H264_VENC_OUTPUT_PORT_IDX;

  /* Get the default values of output port params set by the encoder*/
  err = OMX_GetParameter( h264VencClient->omtbPvt.handle,
                          OMX_IndexParamPortDefinition,
                          h264VencClient->outPortParams->cmnOutParams.pOutPortDef);

  if(OMX_ErrorNone != err)
  {
	OMTB_OmxReturnStatus(err);
	return err;
  }

  h264VencClient->outPortParams->cmnOutParams.pOutPortDef->eDir               = OMX_DirOutput;

  h264VencClient->outPortParams->cmnOutParams.pOutPortDef->nBufferCountActual =
                                  h264VencClient->outPortParams->cmnOutParams.numOutBuf;
  h264VencClient->outPortParams->cmnOutParams.pOutPortDef->nBufferCountMin    = 1;

  h264VencClient->outPortParams->cmnOutParams.pOutPortDef->nBufferSize        =
                                  h264VencClient->outPortParams->cmnOutParams.bufferOutSize;
  h264VencClient->outPortParams->cmnOutParams.pOutPortDef->bEnabled           = OMX_FALSE;
  h264VencClient->outPortParams->cmnOutParams.pOutPortDef->bPopulated         = OMX_FALSE;
  h264VencClient->outPortParams->cmnOutParams.pOutPortDef->eDomain            =
                                         OMX_PortDomainVideo;
  h264VencClient->outPortParams->cmnOutParams.pOutPortDef->bBuffersContiguous = OMX_FALSE;
  h264VencClient->outPortParams->cmnOutParams.pOutPortDef->nBufferAlignment   = 0x0;

  /* OMX_VIDEO_PORTDEFINITION values for output port */
  h264VencClient->outPortParams->cmnOutParams.pOutPortDef->format.video.cMIMEType   = "H264";
  h264VencClient->outPortParams->cmnOutParams.pOutPortDef->format.video.pNativeRender = NULL;

  h264VencClient->outPortParams->cmnOutParams.pOutPortDef->format.video.nFrameWidth   =
  						h264VencClient->inPortParams->nWidth;
  h264VencClient->outPortParams->cmnOutParams.pOutPortDef->format.video.nFrameHeight  =
  						h264VencClient->inPortParams->nHeight;
  h264VencClient->outPortParams->cmnOutParams.pOutPortDef->format.video.nStride       =
  						h264VencClient->inPortParams->nWidth;
  h264VencClient->outPortParams->cmnOutParams.pOutPortDef->format.video.nSliceHeight  = 0;
  h264VencClient->outPortParams->cmnOutParams.pOutPortDef->format.video.nBitrate      =
                         h264VencConfig->sBasicParams.nBitrate;
  h264VencClient->outPortParams->cmnOutParams.pOutPortDef->format.video.xFramerate    =
                         h264VencConfig->sBasicParams.nFramerate;
  h264VencClient->outPortParams->cmnOutParams.pOutPortDef->format.video.bFlagErrorConcealment=
                            OMX_FALSE;
  h264VencClient->outPortParams->cmnOutParams.pOutPortDef->format.video.eCompressionFormat   =
                            OMX_VIDEO_CodingAVC;

  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;

  /*Set the OutPort Definition*/
  err = OMX_SetParameter( h264VencClient->omtbPvt.handle,
                          OMX_IndexParamPortDefinition,
                          h264VencClient->outPortParams->cmnOutParams.pOutPortDef);

  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_SetParameter");

  if(OMX_ErrorNone != err)
  {
    OMTB_OmxReturnStatus(err);
    return err;
  }

  PRINT(PRINT_FUNCTION_NAME, "Leaving <Function , instance #> : <%s , %d>\n",
                              __FUNCTION__, (int)h264VencClient->omtbPvt.instanceNo);

  return err;
}


/******************************************************************************\
 *      H264VENC_SetPortDefinition Function Definition
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

OMX_ERRORTYPE H264VENC_SetPortDefinition(void* thisClient)
{

  OMX_ERRORTYPE err = OMX_ErrorNone;
  OMX_PORT_PARAM_TYPE portInit;
  OMTB_OMX_API_TIMING_VAR_DECL;
  
  OMTB_H264_VENC_PRIVATE* h264VencClient = (OMTB_H264_VENC_PRIVATE*)thisClient;
  /* validate the function arguments */
  ASSERT(NULL != h264VencClient);

  PRINT(PRINT_FUNCTION_NAME, "Entering <Function , instance #> : <%s , %d>\n",
                              __FUNCTION__, (int)h264VencClient->omtbPvt.instanceNo);

  /* Set the component's OMX_PARAM_PORTDEFINITIONTYPE structure (input) */
  OMTB_SetHeader(&portInit,sizeof(OMX_PORT_PARAM_TYPE));
  portInit.nPorts = 2;
  portInit.nStartPortNumber = 0;
#if 0
  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;

  /* Initialize the Port*/
  err = OMX_SetParameter( h264VencClient->omtbPvt.handle,
                          OMX_IndexParamVideoInit,
                          &portInit);

  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_SetParameter");

  if(OMX_ErrorNone != err)
  {
    OMTB_OmxReturnStatus(err);
    return err;
  }
  else
  {
    PRINT(DEFAULT_MESSAGES, "Found The component for encoding\n");
  }
#endif
  /* set the i/p port params */
  err = H264VENC_SetInputPortDefinition(h264VencClient);
  if(OMX_ErrorNone != err)
  {
    PRINT(PRINT_ERR_MSG, "Error in setting i/p port params\n");
    OMTB_OmxReturnStatus(err);
  }

  /* set the o/p port params */
  err = H264VENC_SetOutputPortDefinition(h264VencClient);
  if(OMX_ErrorNone != err)
  {
    PRINT(PRINT_ERR_MSG, "Error in setting o/p port params\n");
    OMTB_OmxReturnStatus(err);
  }

  PRINT(PRINT_FUNCTION_NAME, "Leaving <Function , instance #> : <%s , %d>\n",
                              __FUNCTION__, (int)h264VencClient->omtbPvt.instanceNo);

  return err;
}


/******************************************************************************\
 *      H264VENC_SetBasicParams Function Definition
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
  int portIdx)
{
  char inputCmdLine[OMTB_MAX_LEN] = {'\0'};

  /* generate the command */
  sprintf(inputCmdLine, "omx api setparam %s %d %d %d %s",
          OMTB_H264_VENC_COMP_REF_STR,
          h264VencClient->omtbPvt.instanceNo,
          template,
          portIdx,
          "OMX_IndexParamVideoAvc");

  /* Process the command */
  procCmdLine(inputCmdLine);

  /* generate the command */
  sprintf(inputCmdLine, "omx api setparam %s %d %d %d %s",
            OMTB_H264_VENC_COMP_REF_STR,
            h264VencClient->omtbPvt.instanceNo,
            template,
            portIdx,
            "OMX_IndexParamVideoBitrate");

    /* Process the command */
  procCmdLine(inputCmdLine);


  /* generate the command */
  sprintf(inputCmdLine, "omx api setparam %s %d %d %d %s",
          OMTB_H264_VENC_COMP_REF_STR,
          h264VencClient->omtbPvt.instanceNo,
          template,
          portIdx,
          "OMX_IndexParamVideoProfileLevelCurrent");

  /* Process the command */
  procCmdLine(inputCmdLine);

  /* generate the command */
  sprintf(inputCmdLine, "omx api setparam %s %d %d %d %s",
          OMTB_H264_VENC_COMP_REF_STR,
          h264VencClient->omtbPvt.instanceNo,
          template,
          portIdx,
          "OMX_TI_IndexParamVideoBitStreamFormatSelect");

  /* Process the command */
  procCmdLine(inputCmdLine);

  /* generate the command */
  sprintf(inputCmdLine, "omx api setparam %s %d %d %d %s",
          OMTB_H264_VENC_COMP_REF_STR,
          h264VencClient->omtbPvt.instanceNo,
          template,
          portIdx,
          "OMX_TI_IndexParamVideoEncoderPreset");

  /* Process the command */
  procCmdLine(inputCmdLine);

  /* generate the command */
  sprintf(inputCmdLine, "omx api setparam %s %d %d %d %s",
          OMTB_H264_VENC_COMP_REF_STR,
          h264VencClient->omtbPvt.instanceNo,
          template,
          portIdx,
          "OMX_TI_IndexParamVideoFrameDataContentSettings");

  /* Process the command */
  procCmdLine(inputCmdLine);

  /* generate the command */
  sprintf(inputCmdLine, "omx api setparam %s %d %d %d %s",
          OMTB_H264_VENC_COMP_REF_STR,
          h264VencClient->omtbPvt.instanceNo,
          template,
          portIdx,
          "OMX_TI_IndexParamVideoTransformBlockSize");

  /* Process the command */
  procCmdLine(inputCmdLine);

}

/******************************************************************************\
 *      H264VENC_SetAdvancedParams Function Definition
\******************************************************************************/
/**
 *
 *  @brief    Initializes advanced cfg params.
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

void H264VENC_SetAdvancedParams(
   OMTB_H264_VENC_PRIVATE* h264VencClient,
   int template,
   int portIdx)
{
   char inputCmdLine[OMTB_MAX_LEN] = {'\0'};


   /* generate the command */
   sprintf(inputCmdLine, "omx api setparam %s %d %d %d %s",
           OMTB_H264_VENC_COMP_REF_STR,
           h264VencClient->omtbPvt.instanceNo,
           template,
           portIdx,
           "OMX_TI_IndexParamVideoNALUsettings");

   /* Process the command */
  procCmdLine(inputCmdLine);

   /* generate the command */
   sprintf(inputCmdLine, "omx api setparam %s %d %d %d %s",
           OMTB_H264_VENC_COMP_REF_STR,
           h264VencClient->omtbPvt.instanceNo,
           template,
           portIdx,
           "OMX_TI_IndexParamVideoAdvancedFMO");

   /* Process the command */
  procCmdLine(inputCmdLine);

   /* generate the command */
   sprintf(inputCmdLine, "omx api setparam %s %d %d %d %s",
           OMTB_H264_VENC_COMP_REF_STR,
           h264VencClient->omtbPvt.instanceNo,
           template,
           portIdx,
           "OMX_TI_IndexParamVideoMEBlockSize");

   /* Process the command */
  procCmdLine(inputCmdLine);

   /* generate the command */
   sprintf(inputCmdLine, "omx api setparam %s %d %d %d %s",
           OMTB_H264_VENC_COMP_REF_STR,
           h264VencClient->omtbPvt.instanceNo,
           template,
           portIdx,
           "OMX_IndexParamVideoIntraRefresh");

   /* Process the command */
  procCmdLine(inputCmdLine);

   /* generate the command */
   sprintf(inputCmdLine, "omx api setparam %s %d %d %d %s",
           OMTB_H264_VENC_COMP_REF_STR,
           h264VencClient->omtbPvt.instanceNo,
           template,
           portIdx,
           "OMX_TI_IndexParamVideoVUIsettings");

   /* Process the command */
  procCmdLine(inputCmdLine);

   /* generate the command */
   sprintf(inputCmdLine, "omx api setconfig %s %d %d %d %s",
           OMTB_H264_VENC_COMP_REF_STR,
           h264VencClient->omtbPvt.instanceNo,
           template,
           portIdx,
           "OMX_IndexConfigVideoFramerate");

   /* Process the command */
  procCmdLine(inputCmdLine);

   /* generate the command */
   sprintf(inputCmdLine, "omx api setparam %s %d %d %d %s",
           OMTB_H264_VENC_COMP_REF_STR,
           h264VencClient->omtbPvt.instanceNo,
           template,
           portIdx,
           "OMX_TI_IndexParamVideoIntraPredictionSettings");

   /* Process the command */
  procCmdLine(inputCmdLine);

   /* generate the command */
   sprintf(inputCmdLine, "omx api setparam %s %d %d %d %s",
           OMTB_H264_VENC_COMP_REF_STR,
           h264VencClient->omtbPvt.instanceNo,
           template,
           portIdx,
           "OMX_TI_IndexParamVideoDataSyncMode");

   /* Process the command */
  procCmdLine(inputCmdLine);
}


/******************************************************************************\
 *      H264VENC_SetDynamicParams Function Definition
\******************************************************************************/
/**
 *
 *  @brief    Initializes dynmamic cfg params.
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

void H264VENC_SetDynamicParams(
  OMTB_H264_VENC_PRIVATE* h264VencClient,
  int template,
  int portIdx)
{
  char inputCmdLine[OMTB_MAX_LEN] = {'\0'};


  /* generate the command */
  sprintf(inputCmdLine, "omx api setconfig %s %d %d %d %s",
          OMTB_H264_VENC_COMP_REF_STR,
          h264VencClient->omtbPvt.instanceNo,
          template,
          portIdx,
          "OMX_IndexConfigVideoFramerate");

  /* Process the command */
  procCmdLine(inputCmdLine);

  /* generate the command */
  sprintf(inputCmdLine, "omx api setconfig %s %d %d %d %s",
            OMTB_H264_VENC_COMP_REF_STR,
            h264VencClient->omtbPvt.instanceNo,
            template,
            portIdx,
            "OMX_IndexConfigVideoBitrate");

    /* Process the command */
  procCmdLine(inputCmdLine);

  /* generate the command */
  sprintf(inputCmdLine, "omx api setconfig %s %d %d %d %s",
            OMTB_H264_VENC_COMP_REF_STR,
            h264VencClient->omtbPvt.instanceNo,
            template,
            portIdx,
            "OMX_TI_IndexConfigVideoMESearchRange");

  /* Process the command */
  procCmdLine(inputCmdLine);

  /* generate the command */
  sprintf(inputCmdLine, "omx api setconfig %s %d %d %d %s",
            OMTB_H264_VENC_COMP_REF_STR,
            h264VencClient->omtbPvt.instanceNo,
            template,
            portIdx,
            "OMX_IndexConfigVideoIntraVOPRefresh");

  /* Process the command */
  procCmdLine(inputCmdLine);

  /* generate the command */
  sprintf(inputCmdLine, "omx api setconfig %s %d %d %d %s",
            OMTB_H264_VENC_COMP_REF_STR,
            h264VencClient->omtbPvt.instanceNo,
            template,
            portIdx,
            "OMX_TI_IndexConfigVideoQPSettings");

  /* Process the command */
  procCmdLine(inputCmdLine);

  /* generate the command */
  sprintf(inputCmdLine, "omx api setconfig %s %d %d %d %s",
            OMTB_H264_VENC_COMP_REF_STR,
            h264VencClient->omtbPvt.instanceNo,
            template,
            portIdx,
            "OMX_IndexConfigVideoAVCIntraPeriod");

  /* Process the command */
  procCmdLine(inputCmdLine);

  /* generate the command */
  sprintf(inputCmdLine, "omx api setconfig %s %d %d %d %s",
            OMTB_H264_VENC_COMP_REF_STR,
            h264VencClient->omtbPvt.instanceNo,
            template,
            portIdx,
            "OMX_TI_IndexConfigSliceSettings");

    /* Process the command */
  procCmdLine(inputCmdLine);

  /* generate the command */
  sprintf(inputCmdLine, "omx api setconfig %s %d %d %d %s",
            OMTB_H264_VENC_COMP_REF_STR,
            h264VencClient->omtbPvt.instanceNo,
            template,
            portIdx,
            "OMX_TI_IndexConfigVideoPixelInfo");

    /* Process the command */
  procCmdLine(inputCmdLine);

}

/******************************************************************************\
 *      H264VENC_GetStructIdx Function Definition
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
  void **pCompCfgStruct)
{

  unsigned int enumCount = 0;
  char channelName[OMX_MAX_STRINGNAME_SIZE];         /* Capture channel name */
  OMTB_H264_VENC_CONFIG_PARAMS *h264VencConfig = NULL; 

  /* Use the specified template structure */
  h264VencConfig = (OMTB_H264_VENC_CONFIG_PARAMS*)
                     &(omtbCfgTemplate[template]->h264VencTemplate);

  /* Get the corresponding string for enum values from enum table
     Set structure index
     Set structure pointer
     Set port index for which parameter to be updated
     Set structure header info */
  while(strcmp(enumTblH264VencCfgParamIdx[enumCount].name , ""))
  {
    if(0 == strcmp(enumTblH264VencCfgParamIdx[enumCount].name,
                   indexStr))
    {
      switch(enumTblH264VencCfgParamIdx[enumCount].value)
      {
	    case OMX_TI_IndexConfigChannelName:
          {
            *nConfigIndex   = enumTblH264VencCfgParamIdx[enumCount].value;
            *pCompCfgStruct = &h264VencConfig->sChannelName;
            h264VencConfig->sChannelName.nPortIndex = portIdx;
/* FIXME:  To support backword compatability with the older omtb scripts,
           the following code has not been removed, 
*/		   
//            if(!strcmp("NULL", vpssVfccConfig->sChannelName.cChannelName))			
            { 	
            snprintf(channelName, OMX_MAX_STRINGNAME_SIZE, "FQ_ENCOP_%d",
                     instanceNo);
            channelName[OMX_MAX_STRINGNAME_SIZE - 1] = '\0';
			DOMX_UTL_Strncpy ( ( char * ) h264VencConfig->sChannelName.cChannelName, channelName,
					  sizeof ( h264VencConfig->sChannelName.cChannelName ) );
            }					  
            OMTB_SetHeader( *pCompCfgStruct,
                            sizeof(OMX_CONFIG_CHANNELNAME));
          }
          return OMTB_SUCCESS;
        case OMX_TI_IndexConfigChannelGroupInfo:
          {
            *nConfigIndex   = enumTblH264VencCfgParamIdx[enumCount].value;
            *pCompCfgStruct = &h264VencConfig->sConfigChannelGroupInfo;
//            vpssVfpcScConfig->sConfigChannelGroupInfo.nPortIndex = portIdx;
            OMTB_SetHeader( *pCompCfgStruct,
                            sizeof(OMX_CONFIG_CHANNELGROUPINFO));
          }
          return OMTB_SUCCESS;
        case OMX_IndexConfigVideoFramerate:
          {
            *nConfigIndex   = enumTblH264VencCfgParamIdx[enumCount].value;
            *pCompCfgStruct = &h264VencConfig->sFrameRate;
            h264VencConfig->sFrameRate.nPortIndex = portIdx;
            OMTB_SetHeader( *pCompCfgStruct,
                            sizeof(OMX_CONFIG_FRAMERATETYPE));
          }
          return OMTB_SUCCESS;

        case OMX_IndexParamVideoBitrate:
          {

            *nConfigIndex   = enumTblH264VencCfgParamIdx[enumCount].value;
            *pCompCfgStruct = &h264VencConfig->sParamBitRate;
            h264VencConfig->sParamBitRate.nPortIndex = portIdx;
            OMTB_SetHeader( *pCompCfgStruct,
                            sizeof(OMX_VIDEO_PARAM_BITRATETYPE));
          }
          return OMTB_SUCCESS;

        case OMX_IndexConfigVideoBitrate:
          {
            *nConfigIndex   = enumTblH264VencCfgParamIdx[enumCount].value;
            *pCompCfgStruct = &h264VencConfig->sConfigBitRate;
            h264VencConfig->sConfigBitRate.nPortIndex = portIdx;
            OMTB_SetHeader( *pCompCfgStruct,
                            sizeof(OMX_VIDEO_CONFIG_BITRATETYPE));
          }
          return OMTB_SUCCESS;

        case OMX_TI_IndexConfigVideoMESearchRange:
          {
            *nConfigIndex   = enumTblH264VencCfgParamIdx[enumCount].value;
            *pCompCfgStruct = &h264VencConfig->sMESearchrange;
            h264VencConfig->sMESearchrange.nPortIndex = portIdx;
            OMTB_SetHeader( *pCompCfgStruct,
                            sizeof(OMX_VIDEO_CONFIG_MESEARCHRANGETYPE));
          }
          return OMTB_SUCCESS;

        case OMX_IndexConfigVideoIntraVOPRefresh:
          {
            *nConfigIndex   = enumTblH264VencCfgParamIdx[enumCount].value;
            *pCompCfgStruct = &h264VencConfig->sForceFrame;
            h264VencConfig->sForceFrame.nPortIndex = portIdx;
            OMTB_SetHeader( *pCompCfgStruct,
                            sizeof(OMX_CONFIG_INTRAREFRESHVOPTYPE));
          }
          return OMTB_SUCCESS;

        case OMX_TI_IndexConfigVideoQPSettings:
          {
            *nConfigIndex   = enumTblH264VencCfgParamIdx[enumCount].value;
            *pCompCfgStruct = &h264VencConfig->sQPSettings;
            h264VencConfig->sQPSettings.nPortIndex = portIdx;
            OMTB_SetHeader( *pCompCfgStruct,
                            sizeof(OMX_VIDEO_CONFIG_QPSETTINGSTYPE));
          }
          return OMTB_SUCCESS;

        case OMX_IndexConfigVideoAVCIntraPeriod:
          {
            *nConfigIndex   = enumTblH264VencCfgParamIdx[enumCount].value;
            *pCompCfgStruct = &h264VencConfig->sAVCIntraPeriod;
            h264VencConfig->sAVCIntraPeriod.nPortIndex = portIdx;
            OMTB_SetHeader( *pCompCfgStruct,
                            sizeof(OMX_VIDEO_CONFIG_AVCINTRAPERIOD));
          }
          return OMTB_SUCCESS;

        case OMX_TI_IndexConfigSliceSettings:
          {
            *nConfigIndex   = enumTblH264VencCfgParamIdx[enumCount].value;
            *pCompCfgStruct = &h264VencConfig->sSliceSettings;
            h264VencConfig->sSliceSettings.nPortIndex = portIdx;
            OMTB_SetHeader( *pCompCfgStruct,
                            sizeof(OMX_VIDEO_CONFIG_SLICECODINGTYPE));
          }
          return OMTB_SUCCESS;

        case OMX_TI_IndexConfigVideoPixelInfo:
          {
            *nConfigIndex   = enumTblH264VencCfgParamIdx[enumCount].value;
            *pCompCfgStruct = &h264VencConfig->sPixelInfo;
            h264VencConfig->sPixelInfo.nPortIndex = portIdx;
            OMTB_SetHeader( *pCompCfgStruct,
                            sizeof(OMX_VIDEO_CONFIG_PIXELINFOTYPE));
          }
          return OMTB_SUCCESS;


        case OMX_TI_IndexParamVideoNALUsettings:
          {
            *nConfigIndex   = enumTblH264VencCfgParamIdx[enumCount].value;
            *pCompCfgStruct = &h264VencConfig->sNALUSettings;
            h264VencConfig->sNALUSettings.nPortIndex = portIdx;
            OMTB_SetHeader( *pCompCfgStruct,
                            sizeof(OMX_VIDEO_PARAM_AVCNALUCONTROLTYPE));
          }
          return OMTB_SUCCESS;

        case OMX_TI_IndexParamVideoAdvancedFMO:
          {
            *nConfigIndex   = enumTblH264VencCfgParamIdx[enumCount].value;
            *pCompCfgStruct = &h264VencConfig->sAVCAdvancedFMO;
            h264VencConfig->sAVCAdvancedFMO.nPortIndex = portIdx;
            OMTB_SetHeader( *pCompCfgStruct,
                            sizeof(OMX_VIDEO_PARAM_AVCADVANCEDFMOTYPE));
          }
          return OMTB_SUCCESS;

        case OMX_TI_IndexParamVideoMEBlockSize:
          {
            *nConfigIndex   = enumTblH264VencCfgParamIdx[enumCount].value;
            *pCompCfgStruct = &h264VencConfig->sMEBlockSize;
            h264VencConfig->sMEBlockSize.nPortIndex = portIdx;
            OMTB_SetHeader( *pCompCfgStruct,
                            sizeof(OMX_VIDEO_PARAM_MEBLOCKSIZETYPE));
          }
          return OMTB_SUCCESS;

        case OMX_IndexParamVideoIntraRefresh:
          {
            *nConfigIndex   = enumTblH264VencCfgParamIdx[enumCount].value;
            *pCompCfgStruct = &h264VencConfig->sIntraRefresh;
            h264VencConfig->sIntraRefresh.nPortIndex = portIdx;
            OMTB_SetHeader( *pCompCfgStruct,
                            sizeof(OMX_VIDEO_PARAM_INTRAREFRESHTYPE));
          }
          return OMTB_SUCCESS;

        case OMX_TI_IndexParamVideoVUIsettings:
          {
            *nConfigIndex   = enumTblH264VencCfgParamIdx[enumCount].value;
            *pCompCfgStruct = &h264VencConfig->sVUISettings;
            h264VencConfig->sVUISettings.nPortIndex = portIdx;
            OMTB_SetHeader( *pCompCfgStruct,
                            sizeof(OMX_VIDEO_PARAM_VUIINFOTYPE));
          }
          return OMTB_SUCCESS;

        case OMX_TI_IndexParamVideoIntraPredictionSettings:
          {
            *nConfigIndex   = enumTblH264VencCfgParamIdx[enumCount].value;
            *pCompCfgStruct = &h264VencConfig->sIntraPred;
            h264VencConfig->sIntraPred.nPortIndex = portIdx;
            OMTB_SetHeader( *pCompCfgStruct,
                            sizeof(OMX_VIDEO_PARAM_INTRAPREDTYPE));
          }
          return OMTB_SUCCESS;

        case OMX_TI_IndexParamVideoDataSyncMode:
          {
            *nConfigIndex   = enumTblH264VencCfgParamIdx[enumCount].value;
            *pCompCfgStruct = &h264VencConfig->sVidDataMode;
            h264VencConfig->sVidDataMode.nPortIndex = portIdx;
            OMTB_SetHeader( *pCompCfgStruct,
                            sizeof(OMX_VIDEO_PARAM_DATASYNCMODETYPE));
          }
          return OMTB_SUCCESS;

        case OMX_IndexParamVideoAvc:
          {
            *nConfigIndex   = enumTblH264VencCfgParamIdx[enumCount].value;
            *pCompCfgStruct = &h264VencConfig->sAVCParams;
            h264VencConfig->sAVCParams.nPortIndex = portIdx;
            OMTB_SetHeader( *pCompCfgStruct,
                            sizeof(OMX_VIDEO_PARAM_AVCTYPE));
          }
          return OMTB_SUCCESS;

        case OMX_IndexParamVideoProfileLevelCurrent:
          {
            *nConfigIndex   = enumTblH264VencCfgParamIdx[enumCount].value;
            *pCompCfgStruct = &h264VencConfig->sProfileLevel;
            h264VencConfig->sProfileLevel.nPortIndex = portIdx;
            OMTB_SetHeader( *pCompCfgStruct,
                            sizeof(OMX_VIDEO_PARAM_PROFILELEVELTYPE));
          }
          return OMTB_SUCCESS;

        case OMX_TI_IndexParamVideoBitStreamFormatSelect:
          {
            *nConfigIndex   = enumTblH264VencCfgParamIdx[enumCount].value;
            *pCompCfgStruct = &h264VencConfig->sBitStreamFormat;
            h264VencConfig->sBitStreamFormat.nPortIndex = portIdx;
            OMTB_SetHeader( *pCompCfgStruct,
                            sizeof(OMX_VIDEO_PARAM_AVCBITSTREAMFORMATTYPE));
          }
          return OMTB_SUCCESS;

        case OMX_TI_IndexParamVideoEncoderPreset:
          {
            *nConfigIndex   = enumTblH264VencCfgParamIdx[enumCount].value;
            *pCompCfgStruct = &h264VencConfig->sEncoderPreset;
            h264VencConfig->sEncoderPreset.nPortIndex = portIdx;
            OMTB_SetHeader( *pCompCfgStruct,
                            sizeof(OMX_VIDEO_PARAM_ENCODER_PRESETTYPE));
          }
          return OMTB_SUCCESS;

        case OMX_TI_IndexParamVideoFrameDataContentSettings:
          {
            *nConfigIndex   = enumTblH264VencCfgParamIdx[enumCount].value;
            *pCompCfgStruct = &h264VencConfig->sInputImgFmt;
            h264VencConfig->sInputImgFmt.nPortIndex = portIdx;
            OMTB_SetHeader( *pCompCfgStruct,
                            sizeof(OMX_VIDEO_PARAM_FRAMEDATACONTENTTYPE));
          }
          return OMTB_SUCCESS;

        case OMX_TI_IndexParamVideoTransformBlockSize:
          {
            *nConfigIndex   = enumTblH264VencCfgParamIdx[enumCount].value;
            *pCompCfgStruct = &h264VencConfig->sTransformBlockSize;
            h264VencConfig->sTransformBlockSize.nPortIndex = portIdx;
            OMTB_SetHeader( *pCompCfgStruct,
                            sizeof(OMX_VIDEO_PARAM_TRANSFORM_BLOCKSIZETYPE));
          }
          return OMTB_SUCCESS;

        case OMX_IndexParamVideoSliceFMO:
          {
            *nConfigIndex   = enumTblH264VencCfgParamIdx[enumCount].value;
            *pCompCfgStruct = &h264VencConfig->sAVCSliceFMO;
            h264VencConfig->sAVCSliceFMO.nPortIndex = portIdx;
            OMTB_SetHeader( *pCompCfgStruct,
                            sizeof(OMX_VIDEO_PARAM_AVCSLICEFMO));
          }
          return OMTB_SUCCESS;

		case OMX_TI_IndexParamBuffMemType:
		  {
			*nConfigIndex   = enumTblH264VencCfgParamIdx[enumCount].value;
			*pCompCfgStruct = &h264VencConfig->sMemTypeCfg;
			 h264VencConfig->sMemTypeCfg.nPortIndex = portIdx;
			 OMTB_SetHeader( *pCompCfgStruct,
							 sizeof(OMX_PARAM_BUFFER_MEMORYTYPE));
		  }
  		  return OMTB_SUCCESS;

		case OMX_IndexParamCompBufferSupplier:
		  {
			*nConfigIndex   = enumTblH264VencCfgParamIdx[enumCount].value;
			*pCompCfgStruct = &h264VencConfig->sBufSupplier;
			 h264VencConfig->sBufSupplier.nPortIndex = portIdx;
			 OMTB_SetHeader( *pCompCfgStruct,
							 sizeof(OMX_PARAM_BUFFERSUPPLIERTYPE));
		  }
  		  return OMTB_SUCCESS;

        case OMX_IndexParamVideoPortFormat:
		  {
			*nConfigIndex   = enumTblH264VencCfgParamIdx[enumCount].value;
			*pCompCfgStruct = &h264VencConfig->sVideoPortFormat;
			 h264VencConfig->sVideoPortFormat.nPortIndex = portIdx;
             OMTB_SetHeader( *pCompCfgStruct,
							 sizeof(OMX_VIDEO_PARAM_PORTFORMATTYPE));
		  }
  		  return OMTB_SUCCESS;

		case OMX_IndexParamVideoMotionVector:
		  {
			*nConfigIndex   = enumTblH264VencCfgParamIdx[enumCount].value;
			*pCompCfgStruct = &h264VencConfig->sMotionVectorType;
			 h264VencConfig->sMotionVectorType.nPortIndex = portIdx;
			 OMTB_SetHeader( *pCompCfgStruct,
							 sizeof(OMX_VIDEO_PARAM_MOTIONVECTORTYPE));
		  }
  		  return OMTB_SUCCESS;

  	    case OMX_IndexParamVideoQuantization:
		  {
		    *nConfigIndex   = enumTblH264VencCfgParamIdx[enumCount].value;
		    *pCompCfgStruct = &h264VencConfig->sQuantType;
		    h264VencConfig->sQuantType.nPortIndex = portIdx;
		    OMTB_SetHeader( *pCompCfgStruct,
							  sizeof(OMX_VIDEO_CONFIG_QPSETTINGSTYPE));
		  }
		  return OMTB_SUCCESS;

        case OMX_IndexParamVideoInit:
          {
		    *nConfigIndex   = enumTblH264VencCfgParamIdx[enumCount].value;
		    *pCompCfgStruct = &h264VencConfig->sPortInit;
		    OMTB_SetHeader( *pCompCfgStruct,
						 sizeof(OMX_PORT_PARAM_TYPE));
	      }
	      return OMTB_SUCCESS;
		  
        case OMX_IndexConfigVideoNalSize:
          {
		    *nConfigIndex   = enumTblH264VencCfgParamIdx[enumCount].value;
		    *pCompCfgStruct = &h264VencConfig->sNalSize;
		    OMTB_SetHeader( *pCompCfgStruct,
						 sizeof(OMX_VIDEO_CONFIG_NALSIZE));
	      }
	      return OMTB_SUCCESS;
		  
		case OMX_TI_IndexParamCompPortNotifyType:
          {
			*nConfigIndex   = enumTblH264VencCfgParamIdx[enumCount].value;
			*pCompCfgStruct = &h264VencConfig->sCompPortNotifyType;
            h264VencConfig->sCompPortNotifyType.nPortIndex = portIdx;
            OMTB_SetHeader( *pCompCfgStruct,
                            sizeof(OMX_PARAM_COMPPORT_NOTIFYTYPE));
		  }
		  return OMTB_SUCCESS;				  

        case OMX_IndexParamPortDefinition:
	      {
		    *nConfigIndex   = enumTblH264VencCfgParamIdx[enumCount].value;
		    *pCompCfgStruct = &h264VencConfig->sPortDefType;
            h264VencConfig->sPortDefType.nPortIndex = portIdx;			
		    OMTB_SetHeader( *pCompCfgStruct,
			   			    sizeof(OMX_PARAM_PORTDEFINITIONTYPE));
	      }
	      return OMTB_SUCCESS;

#ifdef _VIDEO_M3_DYNAMIC_CONFIG
        case OMX_TI_IndexConfigVideoDynamicParams:
	      {
		    *nConfigIndex   = enumTblH264VencCfgParamIdx[enumCount].value;
		    *pCompCfgStruct = &h264VencConfig->sDynamicParams;
            h264VencConfig->sDynamicParams.nPortIndex = portIdx;			
		    OMTB_SetHeader( *pCompCfgStruct,
			   			    sizeof(OMX_VIDEO_CONFIG_DYNAMICPARAMS));
	      }
	      return OMTB_SUCCESS;		  
#endif
        default:
          {
            return OMTB_FAIL;
          }

      } // switch(enumTblH264VencCfgParamIdx[enumCount].value)

    } // if(0 == strcmp(enumTblH264VencCfgParamIdx[enumCount].name, ...

    enumCount++;
  }

  return OMTB_SUCCESS;
}


/******************************************************************************\
 *      H264VENC_FuncTsk Thread Definition
\******************************************************************************/
/**
 *
 *  @brief    This is a H264 thread which invokes during func command
 *
 *  @param in:
 *            void * - Thread args count
 *
 *            void *threadsArg - Pointer to thread arg structure
 *
 *  @return   None
 *
 */

void H264VENC_FuncTsk(void *argc, void *threadsArg)
{
  int threadRes = TIMM_OSAL_ERR_NONE;
  OMX_ERRORTYPE err = OMX_ErrorNone;
  OMTB_H264_VENC_PRIVATE* h264VencClient = NULL;
  OMTB_DATA_THREAD_ARG *funcDataThreadArg = (OMTB_DATA_THREAD_ARG *)threadsArg;
  unsigned int instanceNo = 0;
  OMTB_OMX_API_TIMING_VAR_DECL;

  /* thread argument validation */
  ASSERT(NULL != threadsArg);
  ASSERT(NULL != funcDataThreadArg->h264VencClient);

  h264VencClient = funcDataThreadArg->h264VencClient;

  PRINT(PRINT_MUST, "Entering <Thread , instance #> : <%s , %d>\n",
                     __FUNCTION__, (int)h264VencClient->omtbPvt.instanceNo);

  PRINT(PRINT_SIMPLE_MESSAGE, "\nbufferOutSize:%d\n",\
        (int)h264VencClient->outPortParams->cmnOutParams.bufferOutSize);

  /* Set the port params */
  err = H264VENC_SetPortDefinition(h264VencClient);

  if(OMX_ErrorNone != err)
  {
    OMTB_OmxReturnStatus(err);
  }

  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;

  /* send command to component to go to idle state */
  err = OMX_SendCommand(h264VencClient->omtbPvt.handle,
                        OMX_CommandStateSet,
                        OMX_StateIdle,
                        NULL);

  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_SendCommand");

  if(OMX_ErrorNone != err)
  {
    OMTB_OmxReturnStatus(err);
  }

  /* Allocate I/O port buffers and wait till state transition to idle */
  err = OMTB_ClientAllocateResources(h264VencClient);

  if(OMX_ErrorNone != err)
  {
    OMTB_OmxReturnStatus(err);
  }

  /* waiting for component to go to idle state */
  TIMM_OSAL_SemaphoreObtain(h264VencClient->omtbPvt.eventSem, TIMM_OSAL_SUSPEND);

  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;

  /* send command to component to go to executing state */
  err = OMX_SendCommand(h264VencClient->omtbPvt.handle,
                        OMX_CommandStateSet,
                        OMX_StateExecuting,
                        NULL);

  if(OMX_ErrorNone != err)
  {
    OMTB_OmxReturnStatus(err);
  }

  /* waiting for component to go to executing state */
  TIMM_OSAL_SemaphoreObtain(h264VencClient->omtbPvt.eventSem, TIMM_OSAL_SUSPEND);

  /* Update the func create count */
  H264VENC_funcCreateCount++;
  PRINT(PRINT_MUST, "%s: H264 FUNC Create Count: %u\n", __FUNCTION__,
                    (unsigned int) H264VENC_funcCreateCount);

  /* Update the data streaming thread arguments */
  strmThreadArg[h264VencClient->omtbPvt.instanceNo].h264VencClient = h264VencClient;

  /* Create input data read thread */
  threadRes = TIMM_OSAL_CreateTask(
                    (void *)&h264VencClient->inPortParams->cmnInParams.inDataStrmThrdId,
                    (TIMM_OSAL_TaskProc)OMTB_InputDataRead,
                    0,
                    &strmThreadArg[h264VencClient->omtbPvt.instanceNo],
                    OMTB_H264_VENC_TSK_STACK_SIZE,
                    OMTB_H264_VENC_GROUP_PRIORITY,
                    (signed char*)"H264_VENC_DATA_IN_TSK");

  if(TIMM_OSAL_ERR_NONE != threadRes)
  {
    PRINT(PRINT_ERR_MSG,
          "Unable to start H264 video encode input data read thread\n");
  }

  /* Create output data write thread */
  threadRes = TIMM_OSAL_CreateTask(
                    (void *)&h264VencClient->outPortParams->cmnOutParams.outDataStrmThrdId,
                    (TIMM_OSAL_TaskProc)OMTB_OutputDataWrite,
                    0,
                    &strmThreadArg[h264VencClient->omtbPvt.instanceNo],
                    OMTB_H264_VENC_TSK_STACK_SIZE,
                    OMTB_H264_VENC_GROUP_PRIORITY,
                    (signed char*)"H264_VENC_DATA_OUT_TSK");

  if(TIMM_OSAL_ERR_NONE != threadRes)
  {
    PRINT(PRINT_ERR_MSG,
          "Unable to start H264 video encode output data write thread\n");
  }


  /* Wait for EOS */
  TIMM_OSAL_SemaphoreObtain(h264VencClient->eofSem, TIMM_OSAL_SUSPEND);

  PRINT(DEFAULT_MESSAGES, "The execution of the video encoding\
                           process is terminated\n");

  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;

  /* state change of component from executing to idle */
  err = OMX_SendCommand(h264VencClient->omtbPvt.handle,
                        OMX_CommandStateSet,
                        OMX_StateIdle,
                        NULL);

  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_SendCommand");

  if(OMX_ErrorNone != err)
  {
    OMTB_OmxReturnStatus(err);
  }

  /* waiting for component to go to idle state */
  TIMM_OSAL_SemaphoreObtain(h264VencClient->omtbPvt.eventSem, TIMM_OSAL_SUSPEND);

  PRINT(DEFAULT_MESSAGES, "State transitioned to Idle\n");

  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;

  /* sending command to component to go to loaded state */
  err = OMX_SendCommand(h264VencClient->omtbPvt.handle,
                        OMX_CommandStateSet,
                        OMX_StateLoaded,
                        NULL);

  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_SendCommand");

  if(OMX_ErrorNone != err)
  {
    OMTB_OmxReturnStatus(err);
  }

  /* Reset the EOS indication flag */
  h264VencClient->outPortParams->cmnOutParams.flagEos = OMX_FALSE;
  h264VencClient->inPortParams->cmnInParams.flagInputEos = OMX_FALSE;

  /* Function to reelase the resources allocated by component */
  err = OMTB_ClientFreeResources(h264VencClient);

  if(OMX_ErrorNone != err)
  {
    OMTB_OmxReturnStatus(err);
  }

  /*wait for event handler to report completion of loaded command */
  TIMM_OSAL_SemaphoreObtain(h264VencClient->omtbPvt.eventSem, TIMM_OSAL_SUSPEND);

  PRINT(PRINT_SIMPLE_MESSAGE, "State transitioned to loaded\n");

  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;

  /* Delete the component instance */
  err = OMX_FreeHandle(h264VencClient->omtbPvt.handle);

  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_FreeHandle");

  if(OMX_ErrorNone != err)
  {
    OMTB_OmxReturnStatus(err);
  }
  else
  {
    /* Update the component instance management strucutre for deleted instance
       by assigning NULL pointer */
    h264VencClient->omtbPvt.handle = NULL;
    PRINT(PRINT_MUST,
          "\r      \n\nOMTB-Deleted h264Venc Instance #: %d\n\n",
          (int) h264VencClient->omtbPvt.instanceNo);
    omtbClass[OMTB_H264_VENC_CLASS].handle[h264VencClient->omtbPvt.instanceNo] = NULL;
  }

  PRINT(PRINT_SIMPLE_MESSAGE, "video encoder freed\n");

  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;

  /* OMX core un-initialization */
  err = OMX_Deinit();

  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_Deinit");

  if(OMX_ErrorNone != err)
  {
    OMTB_OmxReturnStatus(err);
  }

  /* reset the flag used to determine whether Func/API thread is created */
  h264VencClient->omtbPvt.flagThrCreated = OMX_FALSE;

  /* save the instance no to local variable */
  instanceNo = h264VencClient->omtbPvt.instanceNo;

  /* Reelase the memory allocated for app pvt data */
  OMTB_FreeMemory(h264VencClient);

  /* Update the func delete count */
  H264VENC_funcDeleteCount++;

  PRINT(PRINT_MUST, "%s: H264 FUNC Delete Count: %u\n", __FUNCTION__,
                    (unsigned int) H264VENC_funcDeleteCount);

  PRINT(PRINT_MUST, "Leaving <Thread , instance #> : <%s , %d>\n",
                     __FUNCTION__, (int)instanceNo);

  /* exit the thread */
  TIMM_OSAL_ExitTask(
      omtbClass[OMTB_H264_VENC_CLASS].execThreadId[instanceNo],
      NULL);

}


/******************************************************************************\
 *      H264VENC_ConfigureRunTimeSettings Function Definition
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
  OMX_STRING structIdxStr)
{
  char inputCmdLine[OMTB_MAX_LEN] = {'\0'};
  int i = 0, j = 0;
  unsigned int NumDynCfgPramas = OMTB_H264_VENC_NUM_DYN_PARAMS;

  /* Frame numbers at which configurations to be applied.
     User can set 10 different frame nos for each cfg params.
     Current implementation allows 1st 8 entry of enumTblH264VencCfgParamIdx */
  unsigned int frmNoForCfgParam[OMTB_H264_VENC_NUM_DYN_PARAMS]\
                               [OMTB_H264_VENC_MAX_FRM_NO_ENTRIES] =
                                 {{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},  /* cfg 0 - OMX_IndexConfigVideoFramerate */
                                  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},  /* cfg 1 - OMX_IndexConfigVideoBitrate */
                                  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},  /* cfg 2 - OMX_TI_IndexConfigVideoMESearchRange */
                                  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},  /* cfg 3 - OMX_IndexConfigVideoIntraVOPRefresh */
                                  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},  /* cfg 4 - OMX_TI_IndexConfigVideoQPSettings */
                                  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},  /* cfg 5 - OMX_IndexConfigVideoAVCIntraPeriod */
                                  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},  /* cfg 6 - OMX_TI_IndexConfigSliceSettings */
                                  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}}; /* cfg 7 - OMX_TI_IndexConfigVideoPixelInfo */

  /* Iterate for no of dynamic params times to cover all dynamic cfg params */
  for(i = 0; i < NumDynCfgPramas; i++)
  {
    /* Format the command string which will be used for input to process command */
    sprintf(inputCmdLine, "omx api setconfig %s %d %d %d %s",
    componentName,
    instance,
    i /*template*/, /* Later this can be changed to template no passed as input */
    portIdx,
    enumTblH264VencCfgParamIdx[i].name); /* Later this can be replaced by i/p structure index */

    /* Iterate for OMTB_H264_VENC_MAX_FRM_NO_ENTRIES times to check for frame number */
    for(j = 0; j < OMTB_H264_VENC_MAX_FRM_NO_ENTRIES; j++)
    {

      if(frmNoForCfgParam[i][j] == frameNum)
      {
        /* Process the setconfig command if framenumber matches */
        procCmdLine(inputCmdLine);
      }

    }  // for(j = 0; j < OMTB_H264_VENC_MAX_FRM_NO_ENTRIES; j++)

  }  // for(i = 0; i < NumDynCfgPramas; i++)

  return OMTB_SUCCESS;
}

/******************************************************************************\
 *      H264VENC_SetTemplateDefVal Function Definition
\******************************************************************************/
/*
 *
 *  @brief    This function copies the default values in specified template.
 *
 *  @param in:
 *            pTemplate: Pointer to template structure
 *
 *  @param Out:
 *            None
 *
 *  @return
 *            ERR_NOERR           successful,
 *
 *            ERR_INVNAME         Incorrect template pointer/Memory allocation
 *                                error.
 */

MX_Result H264VENC_SetTemplateDefVal(OMTB_TEMPLATE_INFO *pTemplate)
{
  OMTB_H264_VENC_CONFIG_PARAMS *h264VidEncCfg = NULL;

  /* param validation */
  if(NULL == pTemplate)
  {
    PRINT(PRINT_ERR_MSG, "%s: Memory for Template not allocated\n",__FUNCTION__);
    return ERR_INVNAME;
  }

  /* H264 VENC configuration */
  h264VidEncCfg = &pTemplate->h264VencTemplate;
  strcpy(h264VidEncCfg->sBasicParams.inputFile, "h264venc_sample.yuv");
  strcpy(h264VidEncCfg->sBasicParams.outputFile,"h264venc_test.264");
  strcpy(h264VidEncCfg->sBasicParams.compName,   OMTB_H264_VENC_COMPONENT_NAME);
  h264VidEncCfg->sBasicParams.frameWidth         = OMTB_H264_VENC_DEF_WIDTH;
  h264VidEncCfg->sBasicParams.frameHeight        = OMTB_H264_VENC_DEF_HEIGHT;
  h264VidEncCfg->sBasicParams.colorFormat        = OMX_COLOR_FormatYUV420SemiPlanar;
  h264VidEncCfg->sBasicParams.inColorFormat      = OMX_COLOR_FormatYUV420SemiPlanar;
  h264VidEncCfg->sBasicParams.compressionFormat  = OMX_VIDEO_CodingAVC;
  h264VidEncCfg->sBasicParams.nBitrate           = OMTB_H264_VENC_DEF_BIT_RATE;
  h264VidEncCfg->sBasicParams.nFramerate         = OMTB_H264_VENC_DEF_FRM_RATE;
  h264VidEncCfg->sBasicParams.maxFileSize        = OMTB_MAX_FILE_SIZE;
  h264VidEncCfg->sBasicParams.dataOutPutMode     = OMTB_FILE;
  h264VidEncCfg->sBasicParams.dataInPutMode      = OMTB_DRIVER;
  h264VidEncCfg->sBasicParams.numInBuf           = OMTB_H264_VENC_NUM_IN_BUFS;
  h264VidEncCfg->sBasicParams.numOutBuf          = OMTB_H264_VENC_NUM_OUT_BUFS;
  h264VidEncCfg->sBasicParams.inBufAlignment     = 0;
  h264VidEncCfg->sBasicParams.outBufAlignment    = 0;
  h264VidEncCfg->sBasicParams.inBufSize          = 0;
  h264VidEncCfg->sBasicParams.outBufSize         = OMTB_H264_VENC_MAX_OUTBUF_SIZE;
  h264VidEncCfg->sBasicParams.inBufSzFlag        = OMX_FALSE;
  h264VidEncCfg->sBasicParams.outBufSzFlag       = OMX_FALSE;
  h264VidEncCfg->sBasicParams.inBufContiguous    = TIMM_OSAL_TRUE;
  h264VidEncCfg->sBasicParams.outBufContiguous   = TIMM_OSAL_TRUE;
  h264VidEncCfg->sBasicParams.flagUseInBuffer    = OMX_TRUE;
  h264VidEncCfg->sBasicParams.flagUseOutBuffer   = OMX_FALSE;
  h264VidEncCfg->sBasicParams.flagBasicParam     = OMX_FALSE;  
  h264VidEncCfg->sBasicParams.fileReset          = OMX_TRUE;
  
  h264VidEncCfg->sProfileLevel.eProfile  = OMX_VIDEO_AVCProfileHigh;
  h264VidEncCfg->sProfileLevel.eLevel    = OMX_VIDEO_AVCLevel41;

  h264VidEncCfg->sInputImgFmt.eContentType         = OMX_Video_Progressive;
  h264VidEncCfg->sInputImgFmt.eInterlaceCodingType = OMX_Video_Interlace_PICAFF;

  h264VidEncCfg->sAVCParams.eLoopFilterMode     = OMX_VIDEO_AVCLoopFilterEnable;
  h264VidEncCfg->sAVCParams.bEntropyCodingCABAC = OMX_FALSE;
  h264VidEncCfg->sAVCParams.bEnableFMO     = OMX_FALSE;
  h264VidEncCfg->sAVCParams.bconstIpred    = OMX_FALSE;
  h264VidEncCfg->sAVCParams.bUseHadamard   = OMX_FALSE;
  h264VidEncCfg->sAVCParams.bEnableASO     = OMX_FALSE;
  h264VidEncCfg->sAVCParams.bEnableRS      = OMX_FALSE;
  h264VidEncCfg->sAVCParams.bEnableUEP     = OMX_FALSE;
  h264VidEncCfg->sAVCParams.bFrameMBsOnly  = OMX_FALSE;
  h264VidEncCfg->sAVCParams.bMBAFF         = OMX_FALSE;
  h264VidEncCfg->sAVCParams.bWeightedPPrediction   = OMX_FALSE;
  h264VidEncCfg->sAVCParams.bDirect8x8Inference    = OMX_FALSE;
  h264VidEncCfg->sAVCParams.bDirectSpatialTemporal = OMX_FALSE;

  h264VidEncCfg->sAVCParams.nSliceHeaderSpacing    =
                 OMTB_H264_VENC_DEF_SLICE_HDR_SPACING;
  h264VidEncCfg->sAVCParams.nPFrames               =
               OMTB_H264_VENC_DEF_P_FRM_INTERVAL;
  h264VidEncCfg->sAVCParams.nBFrames               =
               OMTB_H264_VENC_DEF_B_FRM_INTERVAL;
  h264VidEncCfg->sAVCParams.nRefFrames             =
                OMTB_H264_VENC_DEF_NUM_REF_FRM;
  h264VidEncCfg->sAVCParams.nRefIdx10ActiveMinus1  =
               OMTB_H264_VENC_DEF_REF_IDX_10;
  h264VidEncCfg->sAVCParams.nRefIdx11ActiveMinus1  =
               OMTB_H264_VENC_DEF_REF_IDX_11;
  h264VidEncCfg->sAVCParams.nAllowedPictureTypes   =
               OMTB_H264_VENC_DEF_ALLOWED_PIC_TYPE;
  h264VidEncCfg->sAVCParams.nCabacInitIdc          =
               OMTB_H264_VENC_DEF_CABAC_INIT_IDX;
  h264VidEncCfg->sAVCParams.nWeightedBipredicitonMode =
               OMTB_H264_VENC_DEF_WEIGHTED_BIPRED_MODE;
  h264VidEncCfg->sAVCParams.eProfile  =
               OMX_VIDEO_AVCProfileHigh;
  h264VidEncCfg->sAVCParams.eLevel =
               OMX_VIDEO_AVCLevel41;

  h264VidEncCfg->sAVCSliceFMO.nNumSliceGroups     = 0;
  h264VidEncCfg->sAVCSliceFMO.nSliceGroupMapType  = 0;
  h264VidEncCfg->sAVCSliceFMO.eSliceMode          = OMX_VIDEO_SLICEMODE_AVCDefault;

  h264VidEncCfg->sTransformBlockSize.eTransformBlocksize = OMX_Video_Transform_Block_Size_8x8;
  h264VidEncCfg->sBitStreamFormat.eStreamFormat     = OMX_Video_BitStreamFormatByte;

  h264VidEncCfg->sEncoderPreset.eEncodingModePreset = OMX_Video_Enc_User_Defined;
  h264VidEncCfg->sEncoderPreset.eRateControlPreset  = OMX_Video_RC_User_Defined;

  h264VidEncCfg->sFrameRate.xEncodeFramerate = OMTB_H264_VENC_DEF_FRM_RATE;
  h264VidEncCfg->sConfigBitRate.nEncodeBitrate     = OMTB_H264_VENC_DEF_BIT_RATE;

  h264VidEncCfg->sMESearchrange.eMVAccuracy = OMX_Video_MotionVectorQuarterPel;
  h264VidEncCfg->sMESearchrange.nHorSearchRangeP = OMTB_H264_VENC_DEF_MESR_HORP;
  h264VidEncCfg->sMESearchrange.nVerSearchRangeP = OMTB_H264_VENC_DEF_MESR_VERP;
  h264VidEncCfg->sMESearchrange.nHorSearchRangeB = OMTB_H264_VENC_DEF_MESR_HORB;
  h264VidEncCfg->sMESearchrange.nVerSearchRangeB = OMTB_H264_VENC_DEF_MESR_VERB;

  h264VidEncCfg->sForceFrame.IntraRefreshVOP = OMX_FALSE;

  h264VidEncCfg->sQPSettings.nQpI        = OMTB_H264_VENC_DEF_QP_I;
  h264VidEncCfg->sQPSettings.nQpP        = OMTB_H264_VENC_DEF_QP_P;
  h264VidEncCfg->sQPSettings.nQpOffsetB  = OMTB_H264_VENC_DEF_QP_B;

  h264VidEncCfg->sQPSettings.nQpMinI = OMTB_H264_VENC_MIN_QP_IPB;
  h264VidEncCfg->sQPSettings.nQpMinP = OMTB_H264_VENC_MIN_QP_IPB;
  h264VidEncCfg->sQPSettings.nQpMinB = OMTB_H264_VENC_MIN_QP_IPB;

  h264VidEncCfg->sQPSettings.nQpMaxI = OMTB_H264_VENC_MAX_QP_IPB;
  h264VidEncCfg->sQPSettings.nQpMaxP = OMTB_H264_VENC_MAX_QP_IPB;
  h264VidEncCfg->sQPSettings.nQpMaxB = OMTB_H264_VENC_MAX_QP_IPB;

  h264VidEncCfg->sAVCIntraPeriod.nIDRPeriod  =
                              OMTB_H264_VENC_DEF_I_FRM_INTERVAL;

  h264VidEncCfg->sSliceSettings.eSliceMode   = OMX_VIDEO_SLICEMODE_AVCDefault;
  h264VidEncCfg->sSliceSettings.nSlicesize   = 0;

  h264VidEncCfg->sPixelInfo.nWidth   = 0;
  h264VidEncCfg->sPixelInfo.nHeight  = 0;

  h264VidEncCfg->sMemTypeCfg.eBufMemoryType   = OMX_BUFFER_MEMORY_DEFAULT;
  h264VidEncCfg->sBufSupplier.eBufferSupplier =  OMX_BufferSupplyUnspecified;

  h264VidEncCfg->sMotionVectorType.eAccuracy        = OMX_Video_MotionVectorQuarterPel;
  h264VidEncCfg->sMotionVectorType.bUnrestrictedMVs = OMX_FALSE;
  h264VidEncCfg->sMotionVectorType.bFourMV          = OMX_FALSE;
  h264VidEncCfg->sMotionVectorType.sXSearchRange    = OMTB_H264_VENC_DEF_MVSR_X;
  h264VidEncCfg->sMotionVectorType.sYSearchRange    = OMTB_H264_VENC_DEF_MVSR_Y;

  h264VidEncCfg->sPortInit.nPorts           = OMTB_H264_VENC_DEF_NO_OF_PORTS;
  h264VidEncCfg->sPortInit.nStartPortNumber = OMTB_H264_VENC_DEF_START_PORT_NUM;
  
  h264VidEncCfg->sNalSize.nNaluBytes = 0;
  
  h264VidEncCfg->sVideoPortFormat.eCompressionFormat = OMX_VIDEO_CodingAVC;
  h264VidEncCfg->sVideoPortFormat.eColorFormat       = OMX_COLOR_FormatYUV420SemiPlanar;
  h264VidEncCfg->sVideoPortFormat.xFramerate         = OMTB_H264_VENC_DEF_FRM_RATE;  

  h264VidEncCfg->sQuantType.nQpI =  OMTB_H264_VENC_DEF_QP_I;
  h264VidEncCfg->sQuantType.nQpP =  OMTB_H264_VENC_DEF_QP_P;   
  h264VidEncCfg->sQuantType.nQpB =  OMTB_H264_VENC_DEF_QP_B; 
  
  h264VidEncCfg->sCompPortNotifyType.eNotifyType = OMX_NOTIFY_TYPE_ALWAYS;
		  
  h264VidEncCfg->sPortDefType.eDir                               = OMX_DirInput;
  h264VidEncCfg->sPortDefType.nBufferCountActual                 = OMTB_H264_VENC_NUM_IN_BUFS;
  h264VidEncCfg->sPortDefType.nBufferCountMin                    = 1; 
  h264VidEncCfg->sPortDefType.nBufferSize                        = OMTB_H264_VENC_MAX_INBUF_SIZE;    
  h264VidEncCfg->sPortDefType.bEnabled                           = OMX_FALSE; 
  h264VidEncCfg->sPortDefType.bPopulated                         = OMX_FALSE; 
  h264VidEncCfg->sPortDefType.eDomain                            = OMX_PortDomainVideo;
  h264VidEncCfg->sPortDefType.bBuffersContiguous                 = OMX_FALSE;
  h264VidEncCfg->sPortDefType.nBufferAlignment                   = 0;
  h264VidEncCfg->sPortDefType.format.video.cMIMEType             = NULL;
  h264VidEncCfg->sPortDefType.format.video.pNativeRender         = NULL;
  h264VidEncCfg->sPortDefType.format.video.nFrameWidth           = OMTB_H264_VENC_DEF_WIDTH;
  h264VidEncCfg->sPortDefType.format.video.nFrameHeight          = OMTB_H264_VENC_DEF_HEIGHT;
  h264VidEncCfg->sPortDefType.format.video.nStride               = (OMTB_H264_VENC_DEF_WIDTH);
  h264VidEncCfg->sPortDefType.format.video.nSliceHeight          = 0;
  h264VidEncCfg->sPortDefType.format.video.nBitrate              = 0;
  h264VidEncCfg->sPortDefType.format.video.xFramerate            = 0;
  h264VidEncCfg->sPortDefType.format.video.bFlagErrorConcealment = OMX_FALSE;
  h264VidEncCfg->sPortDefType.format.video.eCompressionFormat    = OMX_VIDEO_CodingUnused;
  h264VidEncCfg->sPortDefType.format.video.eColorFormat          = OMX_COLOR_FormatYUV420SemiPlanar;
  h264VidEncCfg->sPortDefType.format.video.pNativeWindow         = NULL;

#ifdef _VIDEO_M3_DYNAMIC_CONFIG
  h264VidEncCfg->sDynamicParams.videoDynamicParams.h264EncDynamicParams.videnc2DynamicParams.targetBitRate =
                                                                   OMTB_H264_VENC_DEF_BIT_RATE;
  h264VidEncCfg->sDynamicParams.videoDynamicParams.h264EncDynamicParams.videnc2DynamicParams.intraFrameInterval =
                                                                   OMTB_H264_VENC_DEF_I_FRM_INTERVAL;  
  h264VidEncCfg->sDynamicParams.videoDynamicParams.h264EncDynamicParams.videnc2DynamicParams.interFrameInterval =
                                                                   OMTB_H264_VENC_DEF_B_FRM_INTERVAL; 
  h264VidEncCfg->sDynamicParams.videoDynamicParams.h264EncDynamicParams.rateControlParams.rcAlgo =
                                                                   OMX_Video_ControlRateConstant; 
  h264VidEncCfg->sDynamicParams.videoDynamicParams.h264EncDynamicParams.rateControlParams.qpI =
                                                                   OMTB_H264_VENC_DEF_QP_I;  
  h264VidEncCfg->sDynamicParams.videoDynamicParams.h264EncDynamicParams.rateControlParams.qpMaxI =
                                                                   OMTB_H264_VENC_MAX_QP_IPB;
  h264VidEncCfg->sDynamicParams.videoDynamicParams.h264EncDynamicParams.rateControlParams.qpMinI =
                                                                   OMTB_H264_VENC_MIN_QP_IPB; 
  h264VidEncCfg->sDynamicParams.videoDynamicParams.h264EncDynamicParams.rateControlParams.qpMaxP =
                                                                   OMTB_H264_VENC_MAX_QP_IPB; 
  h264VidEncCfg->sDynamicParams.videoDynamicParams.h264EncDynamicParams.rateControlParams.qpMinP =
                                                                   OMTB_H264_VENC_MIN_QP_IPB;  
  h264VidEncCfg->sDynamicParams.videoDynamicParams.h264EncDynamicParams.rateControlParams.qpMaxB =
                                                                   OMTB_H264_VENC_MAX_QP_IPB;  
  h264VidEncCfg->sDynamicParams.videoDynamicParams.h264EncDynamicParams.rateControlParams.qpMinB =
                                                                   OMTB_H264_VENC_MIN_QP_IPB;  
  h264VidEncCfg->sDynamicParams.videoDynamicParams.h264EncDynamicParams.rateControlParams.initialBufferLevel =
                                                                   OMTB_H264_VENC_DEF_BUFFER_LEVEL;
  h264VidEncCfg->sDynamicParams.videoDynamicParams.h264EncDynamicParams.rateControlParams.HRDBufferSize =
                                                                   OMTB_H264_VENC_DEF_HRD_BUFF_SIZE; 
  h264VidEncCfg->sDynamicParams.videoDynamicParams.h264EncDynamicParams.interCodingParams.minBlockSizeP =
                                                                   OMTB_H264_VENC_DEF_BLK_SIZE_P;
  h264VidEncCfg->sDynamicParams.videoDynamicParams.h264EncDynamicParams.interCodingParams.minBlockSizeB =
                                                                   OMTB_H264_VENC_DEF_BLK_SIZE_B;  
  h264VidEncCfg->sDynamicParams.videoDynamicParams.h264EncDynamicParams.sliceCodingParams.sliceMode = 
                                                                   IH264_SLICEMODE_BYTES;
  h264VidEncCfg->sDynamicParams.videoDynamicParams.h264EncDynamicParams.sliceCodingParams.sliceUnitSize =
                                                                   OMTB_H264_VENC_DEF_SLICE_UNIT_SIZE; 
#endif
  
  strcpy(h264VidEncCfg->sChannelName.cChannelName, "NULL");
  
  return ERR_NOERR;
}

OmtbRet H264VENC_SetBufferSize(void *thisClient)
{
  OmtbRet err = OMTB_SUCCESS;
  unsigned int retVal = TIMM_OSAL_ERR_NONE;
  unsigned int i = 0;
  OMTB_BASIC_CONFIG_PARAMS *pBasicConfig = NULL;
  OMTB_H264_VENC_PRIVATE *h264VencClient = NULL;
  
  /* validate the function arguments */
  ASSERT(NULL != thisClient);
  h264VencClient = (OMTB_H264_VENC_PRIVATE*)thisClient;
  pBasicConfig = &(omtbCfgTemplate[h264VencClient->omtbPvt.templateNo]->h264VencTemplate.sBasicParams);

  /* copy the output file name */  
  strcpy(h264VencClient->outputFile, pBasicConfig->outputFile);
	
  PRINT(PRINT_FUNCTION_NAME, "Entering <Function , instance #> : <%s , %d>\n",
                              __FUNCTION__, (int)h264VencClient->omtbPvt.instanceNo);
  
  h264VencClient->maxFileSize = pBasicConfig->maxFileSize;
	
  if(OMX_FALSE == h264VencClient->inPortParams->cmnInParams.inBufSzFlag)
  {
    /* input buffer size calculation based on frame dimension speculation */
    switch(h264VencClient->inPortParams->colorFormat)
    {
      case OMX_COLOR_FormatYUV420Planar:
      case OMX_COLOR_FormatYUV420SemiPlanar:
        h264VencClient->inPortParams->cmnInParams.bufferInSize   =
                      ((pBasicConfig->frameWidth * pBasicConfig->frameHeight  * 3)>> 1);
        break;

      case OMX_COLOR_FormatYUV422Planar:
      case OMX_COLOR_FormatYCbYCr:
        h264VencClient->inPortParams->cmnInParams.bufferInSize   =
                      (pBasicConfig->frameWidth * pBasicConfig->frameHeight  * 2);
        break;

      default:
        PRINT(PRINT_MUST, "Undefined chroma format. Setting i/p buffer size \
  according to 420P format.\n");
        h264VencClient->inPortParams->cmnInParams.bufferInSize   =
                      ((pBasicConfig->frameWidth * pBasicConfig->frameHeight  * 3)>> 1);

        break;

    } // switch(h264VencClient->inPortParams->colorFormat)

  } // if(OMX_FALSE == h264VencClient->inPortParams->cmnInParams.inBufSzFlag)
  else
  {
    h264VencClient->inPortParams->cmnInParams.bufferInSize = pBasicConfig->inBufSize;
  }

  if(OMX_FALSE == h264VencClient->outPortParams->cmnOutParams.outBufSzFlag)
  {
    h264VencClient->outPortParams->cmnOutParams.bufferOutSize = (pBasicConfig->frameWidth * pBasicConfig->frameHeight);
  }
  else
  {
    h264VencClient->outPortParams->cmnOutParams.bufferOutSize = pBasicConfig->outBufSize;
  }  
  
  PRINT(PRINT_FUNCTION_NAME, "Leaving <Function #> : <%s>\n",
                              __FUNCTION__);  
  return err;  
}

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
OMX_ERRORTYPE H264VENC_ClassInit(OMTB_CLIENT_PRIVATE* thisClient)
{
  OmtbRet err = OMTB_SUCCESS;
  
  PRINT(PRINT_FUNCTION_NAME, "Entering <Function> : <%s>\n",
                              __FUNCTION__);
							  
  /* no of input / output ports */
  thisClient->omtbPvt.numInport  = OMTB_H264_VENC_MAX_IN_PORT;
  thisClient->omtbPvt.numOutport = OMTB_H264_VENC_MAX_OUT_PORT;
  thisClient->omtbPvt.startOutportIndex = OMTB_H264_VENC_MAX_IN_PORT;
  
  thisClient->omtbPvt.outputDataWriteTask = OMTB_OutputDataWrite;
  thisClient->omtbPvt.inputDataReadTask = OMTB_InputDataRead;

  /* Function pointer for GetStructIdx */
  thisClient->omtbPvt.fpGetStructIdx = H264VENC_GetStructIdx; 
  thisClient->omtbPvt.fpSetBufferSize = H264VENC_SetBufferSize;
  thisClient->omtbPvt.fpSetPortDefinition = H264VENC_SetPortDefinition;

  
  thisClient->omtbPvt.numFileInBufs = OMTB_CLIENT_MAX_NUM_FILE_IN_BUFS;
  thisClient->omtbPvt.numFileOutBufs = OMTB_CLIENT_MAX_NUM_FILE_OUT_BUFS;
  
  thisClient->omtbPvt.readSize       = OMTB_H264_VENC_MAX_INBUF_SIZE;
  thisClient->omtbPvt.writeSize      = OMTB_H264_VENC_MAX_WRITE_SIZE; 
  
  thisClient->omtbPvt.eClassType = OMTB_H264_VENC_CLASS;
  
  PRINT(PRINT_FUNCTION_NAME, "Leaving <Function> : <%s>\n",
                              __FUNCTION__);  
  return (err);							  
}



/*----------------------------- end of file ----------------------------------*/

