
/*
 * omtbH264Vdec.c
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

/******************************************************************************\
 *      Customized Includes
\******************************************************************************/

#include "omtbDebug.h"
#include "timm_osal_interfaces.h"

#include "omtbCommon.h"
#include "omtbCmd.h"
#include "omtbClient.h"
#include "omtbH264Vdec.h"
#include "domx_util.h"


/******************************************************************************\
 *      Local Defines
\******************************************************************************/

/******************************************************************************\
 *      Data type definitions
\******************************************************************************/


/******************************************************************************\
 *      Extern Object Definitions
\******************************************************************************/

// Component class structure which holds component instance handle,
// application private data etc
extern OMTB_COMP_HANDLE omtbClass[OMTB_MAX_CLASS];

/* Streaming (I/P and O/P) thread arguments */
extern OMTB_DATA_THREAD_ARG strmThreadArg[OMTB_MAX_INS];

/* Pointer to OMTB configuration template */
extern OMTB_TEMPLATE_INFO *omtbCfgTemplate[OMTB_MAX_INS];

/* global semaphote used for proprietary tunneling */
extern void *gOmtbEofSem;

/* global flag used for demo */
extern OMX_BOOL gOmtbStopVdecDemoFlag;

/* global semaphote used for demo */
extern void *gOmtbVdecDemoSem;
/******************************************************************************\
 *      Globals
\******************************************************************************/

/* Pointer to H264 config params */
OMTB_H264_VDEC_CONFIG_PARAMS *h264VdecConfig = NULL;


/******************************************************************************\
 *      Static Globals
\******************************************************************************/

static OMX_U32 H264VDEC_funcCreateCount = 0;  /* Func create count */
static OMX_U32 H264VDEC_apiCreateCount = 0;   /* API create count */

static OMX_U32 H264VDEC_funcDeleteCount = 0;  /* Func delete count */
static OMX_U32 H264VDEC_apiDeleteCount = 0;   /* API delete count */

/* Enum Entry for Supported cfg param indexs */

PRIVATE MX_DBG_ENUM_ENTRY_T enumTblH264VdecCfgParamIdx[] =
{
  /* ADD ENTRIES HERE for SetConfig/SetParam/GetConfig/GetParam */
  {"OMX_TI_IndexConfigChannelName",          OMX_TI_IndexConfigChannelName,          ""},
  {"OMX_TI_IndexConfigChannelGroupInfo",     OMX_TI_IndexConfigChannelGroupInfo,     ""},
  {"OMX_TI_IndexParamBuffMemType",           OMX_TI_IndexParamBuffMemType,           ""},
  {"OMX_IndexParamCompBufferSupplier",       OMX_IndexParamCompBufferSupplier,       ""},
  {"OMX_IndexParamVideoPortFormat",          OMX_IndexParamVideoPortFormat,          ""},
  {"OMX_IndexConfigVideoMacroBlockErrorMap", OMX_IndexConfigVideoMacroBlockErrorMap, ""},
  {"OMX_TI_IndexParamFileModeType",          OMX_TI_IndexParamFileModeType,          ""},
  {"OMX_IndexParamVideoInit",                OMX_IndexParamVideoInit,                ""},
  {"OMX_IndexParamVideoAvc",                 OMX_IndexParamVideoAvc,                 ""},
  {"OMX_IndexParamVideoMacroblocksPerFrame", OMX_IndexParamVideoMacroblocksPerFrame, ""},	
  {"OMX_TI_IndexParamCompPortNotifyType",    OMX_TI_IndexParamCompPortNotifyType,    ""},
  {"OMX_IndexParamPortDefinition",           OMX_IndexParamPortDefinition,           ""},     
  {"", 0, ""}
};


/******************************************************************************\
 *      Public Function Prototypes
\******************************************************************************/

/******************************************************************************\
 *      Private Function Prototypes
\******************************************************************************/

/******************************************************************************\
 *      H264_outputDisplayFrame Function Definition
\******************************************************************************/
/**
 *
 *  @brief  Sub function to write output data to a file
 *
 *  @param in:
 *          lBuffPtr          Luma buffer pointer
            cBuffPtr          Chroma buffer pointer
 *          xoff              X Offset
 *          yoff              
 *          ref_width         Padded Width of the image
 *          ref_height        Padded Height of the image 
 *          width             Width of the image 
 *          height            Height of the image 
 *          fout              Output file pointer  
 *          fieldBuf          Scratch buffer for interleaving the data
 *
 *  @param Out:
 *            None
 *  @return   None
 *
 */
static unsigned short H264_outputDisplayFrame(char * lBuffPtr,
                                         char * cBuffPtr,
                                         unsigned int xoff,
                                         unsigned int yoff,
                                         unsigned int ref_width,
                                         unsigned int ref_height,
                                        unsigned int width,
                                         unsigned int height,
                                         void  *fieldBuf, FILE * fout
                                        )
{

  /*--------------------------------------------------------------------------------
   Here the actual frame data (w/out padding), is extracted and dumped.
   Also UV is de-interleaved.   
  --------------------------------------------------------------------------------*/
    unsigned short retval = 0;
    char *CbBuf, *CrBuf, *YBuf, *lumaAddr, *chromaAddr;
    unsigned int pic_size, i, j;
    
	PRINT(PRINT_DEBUG_MESSAGE, " xoff %d \n yoff %d \n",xoff,yoff); 
    PRINT(PRINT_DEBUG_MESSAGE, " ref_width %d \n ref_height %d \n",ref_width,ref_height); 
    
    pic_size = width * height;

    lumaAddr =
        (char *) ((unsigned int) lBuffPtr +
                  (yoff * ref_width) + xoff);
    chromaAddr =
        (char *) ((unsigned int) cBuffPtr +
                  ((yoff >> 1) * ref_width) + xoff);

    YBuf = (char *) fieldBuf;
    for (i = 0; i < height; i++) {
        memcpy(YBuf, lumaAddr, width);
        YBuf += width;
        lumaAddr += ref_width;
    }

    CbBuf = (char *) ((unsigned int)fieldBuf + pic_size);
    CrBuf = (char *) ((unsigned int)fieldBuf + pic_size + (pic_size >> 2));
    for (i = 0; i < (height >> 1); i++) {
        for (j = 0; j < (width >> 1); j++) {
            CbBuf[j] = chromaAddr[(j * 2)];
            CrBuf[j] = chromaAddr[(j * 2) + 1];
        }
        CbBuf += (width >> 1);
        CrBuf += (width >> 1);
        chromaAddr += ref_width;
    }
  	
	PRINT(PRINT_DEBUG_MESSAGE, " writting file size %d \n", ((pic_size * 3) >> 1));
  
        fwrite((void *) fieldBuf, sizeof(unsigned char), ((pic_size * 3) >> 1),
               fout);
    return (retval);
}

/******************************************************************************\
 *      H264_TestApp_WriteOutputData Function Definition
\******************************************************************************/
/**
 *
 *  @brief  Application function to write output data to a file
 *
 *  @param in:
 *          fOutFile           output file ptr
 *          pBufHeader         pointer to buffer header
 *          imageHeight        Height of the image 
 *          imageWidth         Width of the image
 *          fieldBuf           Scratch buffer for interleaving the data
 *
 *  @param Out:
 *            None
 *  @return   None
 *
 */
void H264_TestApp_WriteOutputData(FILE * fOutFile,
                             char * pBuffer,
							 unsigned int nFilledLen,
							 unsigned int nOffset,
 	  					     unsigned int imageHeight,
							 unsigned int imageWidth, 
							 void * fieldBuf) 
{
    unsigned int paddedheight;
    unsigned int xOffset, yOffset, imagePitch;
    char * cBuffer;
  /*-------------------------------------------------------------------------*/
  /*    Pointer to Display buffer structure                                    */
  /*-------------------------------------------------------------------------*/
    imagePitch = ((imageWidth + (2 * OMTB_H264_VDEC_PADX) + 127) & 0xFFFFFF80);
    
	xOffset = nOffset % imagePitch;
    yOffset = nOffset / imagePitch;
	
    paddedheight = imageHeight + (yOffset << 1);

    
    cBuffer = (char *)((OMX_U32) pBuffer + ((nFilledLen / 3) << 1));
    
    
	H264_outputDisplayFrame(pBuffer,
					       cBuffer,
					       (unsigned int) xOffset,
					       (unsigned int) yOffset,
					       imagePitch,
					       paddedheight,
					       (unsigned int) imageWidth,
					       (unsigned int) imageHeight,
						   fieldBuf,
						   fOutFile);

}

/******************************************************************************\
 *      H264VDEC_SetBufferSize Function Definition
\******************************************************************************/
/**
 *
 *  @brief    Allocate memory for private data structure for h264 video decode
 *            component
 *
 *  @param in:
 *            h264VdecClient:Pointer to appPrivateType structure
 *
 *  @param Out:
 *            None
 *
 *  @return   OmtbRet - OMTB return/error code
 *
 */

OmtbRet H264VDEC_SetBufferSize(void *thisClient)
{
  OmtbRet err = OMTB_SUCCESS;
  OMTB_BASIC_CONFIG_PARAMS *pBasicConfig = NULL;
  OMTB_H264_VDEC_PRIVATE *h264VdecClient = NULL;
  
  /* validate the function arguments */
  ASSERT(NULL != thisClient);
  h264VdecClient = (OMTB_H264_VDEC_PRIVATE*)thisClient;
  pBasicConfig = &(omtbCfgTemplate[h264VdecClient->omtbPvt.templateNo]->h264VdecTemplate.sBasicParams);

  
  PRINT(PRINT_FUNCTION_NAME, "Entering <Function , instance #> : <%s , %d>\n",
                              __FUNCTION__, (int)h264VdecClient->omtbPvt.instanceNo);

  /* set the input buffer size */
  if(OMX_FALSE == h264VdecClient->inPortParams->cmnInParams.inBufSzFlag)
  {
    /* i/p buffer size calculation based on input dimension speculation */  
    h264VdecClient->inPortParams->cmnInParams.bufferInSize = pBasicConfig->frameWidth * pBasicConfig->frameHeight;
  }
  else
  {
    h264VdecClient->inPortParams->cmnInParams.bufferInSize =  pBasicConfig->inBufSize;
  }
  
  /* set the output buffer size */    
  if(OMX_FALSE == h264VdecClient->outPortParams->cmnOutParams.outBufSzFlag)
  {
    /* output buffer size calculation based on frame dimension speculation */
    switch(h264VdecClient->outPortParams->colorFormat)
    {
      case OMX_COLOR_FormatYUV420Planar:
      case OMX_COLOR_FormatYUV420SemiPlanar:

        h264VdecClient->outPortParams->cmnOutParams.bufferOutSize =
        ((((pBasicConfig->frameWidth + (2 * OMTB_H264_VDEC_PADX) + 127) & 0xFFFFFF80) * ((pBasicConfig->frameHeight +
                                                      (4 * OMTB_H264_VDEC_PADY))) * 3) >> 1);
        break;

      case OMX_COLOR_FormatYUV422Planar:
      case OMX_COLOR_FormatYCbYCr:
        h264VdecClient->outPortParams->cmnOutParams.bufferOutSize =
                      (pBasicConfig->frameWidth *\
                      pBasicConfig->frameHeight * 2);

        break;

      default:
        PRINT(PRINT_MUST, "Undefined chroma format. Setting o/p buffer size \
  according to 420P format.\n");
        h264VdecClient->outPortParams->cmnOutParams.bufferOutSize =
        ((((pBasicConfig->frameWidth + (2 * OMTB_H264_VDEC_PADX) + 127) & 0xFFFFFF80) * ((pBasicConfig->frameHeight +
                                                      (4 * OMTB_H264_VDEC_PADY))) * 3) >> 1);
        break;

    } // switch(h264VdecClient->outPortParams->colorFormat)
  }
  else
  {
    h264VdecClient->outPortParams->cmnOutParams.bufferOutSize =
                                               pBasicConfig->outBufSize;
  }
  
  PRINT(PRINT_FUNCTION_NAME, "Leaving <Function #> : <%s>\n",
                             __FUNCTION__);  
  return err;
}

/******************************************************************************\
 *      H264VDEC_SetInputPortDefinition Function Definition
\******************************************************************************/
/**
 *
 *  @brief    Set i/p port params.
 *
 *  @param in:
 *            h264VdecClient:Pointer to appPrivateType structure
 *
 *  @param Out:
 *            None
 *
 *  @return   OMX_ERRORTYPE - OMX std return/error code
 *
 */

OMX_ERRORTYPE H264VDEC_SetInputPortDefinition(OMTB_H264_VDEC_PRIVATE* h264VdecClient)
{

  OMX_ERRORTYPE err = OMX_ErrorNone;
  OMTB_OMX_API_TIMING_VAR_DECL;
  OMTB_H264_VDEC_CONFIG_PARAMS *h264VdecConfig = NULL; 


  /* validate the function arguments */
  ASSERT(NULL != h264VdecClient);

  PRINT(PRINT_FUNCTION_NAME, "Entering <Function , instance #> : <%s , %d>\n",
                              __FUNCTION__, (int)h264VdecClient->omtbPvt.instanceNo);

  h264VdecConfig = (OMTB_H264_VDEC_CONFIG_PARAMS*)
                     &(omtbCfgTemplate[h264VdecClient->omtbPvt.templateNo]->h264VdecTemplate);
  
  /* input buffer size calculation based on input dimension speculation */
  //h264VdecClient->inPortParams->cmnInParams.bufferInSize   = OMTB_H264_VDEC_MAX_INBUFF_SIZE;
  if(OMX_FALSE == h264VdecClient->inPortParams->cmnInParams.inBufSzFlag)
  {
    /* i/p buffer size calculation based on input dimension speculation */  
    h264VdecClient->inPortParams->cmnInParams.bufferInSize = h264VdecConfig->sBasicParams.frameWidth * h264VdecConfig->sBasicParams.frameHeight;
  }
  else
  {
    h264VdecClient->inPortParams->cmnInParams.bufferInSize =  h264VdecConfig->sBasicParams.inBufSize;
  }

  /* Set the component's OMX_PARAM_PORTDEFINITIONTYPE structure (input) */
  OMTB_SetHeader( h264VdecClient->inPortParams->cmnInParams.pInPortDef,
                  sizeof(OMX_PARAM_PORTDEFINITIONTYPE));

  h264VdecClient->inPortParams->cmnInParams.pInPortDef->nPortIndex          = OMTB_H264_VDEC_INPUT_PORT_IDX;
  /* Get the default values of input port params set by the decoder*/
  err = OMX_GetParameter( h264VdecClient->omtbPvt.handle,
                          OMX_IndexParamPortDefinition,
                          h264VdecClient->inPortParams->cmnInParams.pInPortDef);
  if(OMX_ErrorNone != err)
  {
	OMTB_OmxReturnStatus(err);
	return err;
  }
  
  h264VdecClient->inPortParams->cmnInParams.pInPortDef->eDir                = OMX_DirInput;

  h264VdecClient->inPortParams->cmnInParams.pInPortDef->nBufferCountActual  =
                                  h264VdecClient->inPortParams->cmnInParams.numInBuf;
  h264VdecClient->inPortParams->cmnInParams.pInPortDef->nBufferCountMin     = 1;

  h264VdecClient->inPortParams->cmnInParams.pInPortDef->nBufferSize         =
                                  h264VdecClient->inPortParams->cmnInParams.bufferInSize;
  h264VdecClient->inPortParams->cmnInParams.pInPortDef->bEnabled            = OMX_FALSE;
  h264VdecClient->inPortParams->cmnInParams.pInPortDef->bPopulated          = OMX_FALSE;
  h264VdecClient->inPortParams->cmnInParams.pInPortDef->eDomain             =
                                  OMX_PortDomainVideo;
  h264VdecClient->inPortParams->cmnInParams.pInPortDef->bBuffersContiguous  = OMX_FALSE;
  h264VdecClient->inPortParams->cmnInParams.pInPortDef->nBufferAlignment    = 0x0;

  /* OMX_VIDEO_PORTDEFINITION values for input port */
  h264VdecClient->inPortParams->cmnInParams.pInPortDef->format.video.pNativeRender  = NULL;
  h264VdecClient->inPortParams->cmnInParams.pInPortDef->format.video.cMIMEType      = "H264";
  h264VdecClient->inPortParams->cmnInParams.pInPortDef->format.video.nStride        = -1;
  h264VdecClient->inPortParams->cmnInParams.pInPortDef->format.video.nSliceHeight   = 0;
  h264VdecClient->inPortParams->cmnInParams.pInPortDef->format.video.nBitrate = 10485760;  // pAppData->nBitRate; // Confirm this
  h264VdecClient->inPortParams->cmnInParams.pInPortDef->format.video.xFramerate     = h264VdecConfig->sBasicParams.nFramerate << 16; 
  h264VdecClient->inPortParams->cmnInParams.pInPortDef->format.video.eColorFormat   =
                     h264VdecClient->inPortParams->colorFormat;
  h264VdecClient->inPortParams->cmnInParams.pInPortDef->format.video.nFrameWidth    =
                      h264VdecClient->inPortParams->nWidth;
  h264VdecClient->inPortParams->cmnInParams.pInPortDef->format.video.nFrameHeight   =
                      h264VdecClient->inPortParams->nHeight;

  h264VdecClient->inPortParams->cmnInParams.pInPortDef->format.video.eCompressionFormat =
                      OMX_VIDEO_CodingAVC;
  h264VdecClient->inPortParams->cmnInParams.pInPortDef->format.video.bFlagErrorConcealment =
                      OMX_FALSE;

  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;

  /*Set the inPort Definition*/
  err = OMX_SetParameter( h264VdecClient->omtbPvt.handle,
                          OMX_IndexParamPortDefinition,
                          h264VdecClient->inPortParams->cmnInParams.pInPortDef);

  /* Initialize H.264 Parsing Context */
  h264VdecClient->inPortParams->h264ParseCtx.readBuf =
                        (unsigned char *)TIMM_OSAL_Malloc(H264PARSER_READSIZE, 
                                                   TIMM_OSAL_TRUE,
                                                   0,
                                                   TIMMOSAL_MEM_SEGMENT_EXT);
  if (!h264VdecClient->inPortParams->h264ParseCtx.readBuf)
  {
    PRINT(PRINT_ERR_MSG, "h264 Parser read buf memory allocation failed\n");
    err = OMTB_INSUFFICIENT_RESOURCES;
  }

  OMTB_H264ChunkingCtxInit(&h264VdecClient->inPortParams->h264ParseCtx.ctx);
  h264VdecClient->inPortParams->h264ParseCtx.fp = h264VdecClient->inPortParams->cmnInParams.fin;
  h264VdecClient->inPortParams->h264ParseCtx.frameNo = 0;
  h264VdecClient->inPortParams->h264ParseCtx.frameSize = 0;
  h264VdecClient->inPortParams->h264ParseCtx.bytes = 0;
  h264VdecClient->inPortParams->h264ParseCtx.tmp = 0;
  h264VdecClient->inPortParams->h264ParseCtx.firstParse = 1;
  h264VdecClient->inPortParams->h264ParseCtx.chunkCnt = 1;

  h264VdecClient->inPortParams->h264ParseCtx.outBuf.ptr = NULL;
  h264VdecClient->inPortParams->h264ParseCtx.outBuf.bufsize = 0;
  h264VdecClient->inPortParams->h264ParseCtx.outBuf.bufused = 0;
  /**************End Initialization****/

  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_SetParameter");

  if(OMX_ErrorNone != err)
  {
    OMTB_OmxReturnStatus(err);
    return err;
  }

  PRINT(PRINT_FUNCTION_NAME, "Leaving <Function , instance #> : <%s , %d>\n",
                              __FUNCTION__, (int)h264VdecClient->omtbPvt.instanceNo);

  return err;
}


/******************************************************************************\
 *      H264VDEC_SetOutputPortDefinition Function Definition
\******************************************************************************/
/**
 *
 *  @brief    Set o/p port params.
 *
 *  @param in:
 *            h264VdecClient:Pointer to appPrivateType structure
 *
 *  @param Out:
 *            None
 *
 *  @return   OMX_ERRORTYPE - OMX std return/error code
 *
 */

OMX_ERRORTYPE H264VDEC_SetOutputPortDefinition(OMTB_H264_VDEC_PRIVATE* h264VdecClient)
{

  OMX_ERRORTYPE err = OMX_ErrorNone;
  OMTB_OMX_API_TIMING_VAR_DECL;
  OMTB_H264_VDEC_CONFIG_PARAMS *h264VdecConfig = NULL; 

  /* validate the function arguments */
  ASSERT(NULL != h264VdecClient);

  PRINT(PRINT_FUNCTION_NAME, "Entering <Function , instance #> : <%s , %d>\n",
                              __FUNCTION__, (int)h264VdecClient->omtbPvt.instanceNo);

  h264VdecConfig =(OMTB_H264_VDEC_CONFIG_PARAMS*)
                     &(omtbCfgTemplate[h264VdecClient->omtbPvt.templateNo]->h264VdecTemplate);
  if(OMX_FALSE == h264VdecClient->outPortParams->cmnOutParams.outBufSzFlag)
  {
    /* output buffer size calculation based on frame dimension speculation */
    switch(h264VdecClient->outPortParams->colorFormat)
    {
      case OMX_COLOR_FormatYUV420Planar:
      case OMX_COLOR_FormatYUV420SemiPlanar:

        h264VdecClient->outPortParams->cmnOutParams.bufferOutSize =
                      ((h264VdecClient->outPortParams->nWidth *\
                        h264VdecClient->outPortParams->nHeight * 3)
                        >> 1);

        break;

      case OMX_COLOR_FormatYUV422Planar:
      case OMX_COLOR_FormatYCbYCr:

        h264VdecClient->outPortParams->cmnOutParams.bufferOutSize =
                      (h264VdecClient->outPortParams->nWidth *\
                      h264VdecClient->outPortParams->nHeight * 2);

        break;

      default:

        PRINT(PRINT_MUST, "Undefined chroma format. Setting o/p buffer size \
  according to 420P format.\n");
        h264VdecClient->outPortParams->cmnOutParams.bufferOutSize =
                      ((h264VdecClient->outPortParams->nWidth *\
                        h264VdecClient->outPortParams->nHeight * 3)
                        >> 1);

        break;

    } // switch(h264VdecClient->outPortParams->colorFormat)

    h264VdecClient->outPortParams->cmnOutParams.bufferOutSize = ((((h264VdecClient->outPortParams->nWidth + (2*OMTB_H264_VDEC_PADX) + 127) & 0xFFFFFF80) *  
	                                                               ((h264VdecClient->outPortParams->nHeight + (4*OMTB_H264_VDEC_PADY))) * 3) >> 1);
  }
  else
  {
    h264VdecClient->outPortParams->cmnOutParams.bufferOutSize =
                                               h264VdecConfig->sBasicParams.outBufSize;
  }


 OMTB_SetHeader( h264VdecClient->outPortParams->cmnOutParams.pOutPortDef,
                  sizeof(OMX_PARAM_PORTDEFINITIONTYPE));

  /* Set the component's OMX_PARAM_PORTDEFINITIONTYPE structure (output) */

  h264VdecClient->outPortParams->cmnOutParams.pOutPortDef->nPortIndex         = OMTB_H264_VDEC_OUTPUT_PORT_IDX;
  
  /* Get the default values of output port params set by the decoder*/
  err = OMX_GetParameter( h264VdecClient->omtbPvt.handle,
                          OMX_IndexParamPortDefinition,
                          h264VdecClient->outPortParams->cmnOutParams.pOutPortDef);

  if(OMX_ErrorNone != err)
  {
	OMTB_OmxReturnStatus(err);
	return err;
  }
  h264VdecClient->outPortParams->cmnOutParams.pOutPortDef->eDir               = OMX_DirOutput;

  h264VdecClient->outPortParams->cmnOutParams.pOutPortDef->nBufferCountActual =
                                  h264VdecClient->outPortParams->cmnOutParams.numOutBuf;
  h264VdecClient->outPortParams->cmnOutParams.pOutPortDef->nBufferCountMin    = 1;

  h264VdecClient->outPortParams->cmnOutParams.pOutPortDef->nBufferSize        =
                                  h264VdecClient->outPortParams->cmnOutParams.bufferOutSize;
  h264VdecClient->outPortParams->cmnOutParams.pOutPortDef->bEnabled           = OMX_FALSE;
  h264VdecClient->outPortParams->cmnOutParams.pOutPortDef->bPopulated         = OMX_FALSE;
  h264VdecClient->outPortParams->cmnOutParams.pOutPortDef->eDomain            =
                                  OMX_PortDomainVideo;
  h264VdecClient->outPortParams->cmnOutParams.pOutPortDef->bBuffersContiguous = OMX_FALSE;
  h264VdecClient->outPortParams->cmnOutParams.pOutPortDef->nBufferAlignment   = 0x0;

  /* OMX_VIDEO_PORTDEFINITION values for output port */
  h264VdecClient->outPortParams->cmnOutParams.pOutPortDef->format.video.cMIMEType  = "H264";
  h264VdecClient->outPortParams->cmnOutParams.pOutPortDef->format.video.pNativeRender = NULL;
  
  h264VdecClient->outPortParams->cmnOutParams.pOutPortDef->format.video.nFrameWidth   =
                       h264VdecClient->outPortParams->nWidth;
  h264VdecClient->outPortParams->cmnOutParams.pOutPortDef->format.video.nFrameHeight  =
                       h264VdecClient->outPortParams->nHeight;
  h264VdecClient->outPortParams->cmnOutParams.pOutPortDef->format.video.nStride       =
                       h264VdecClient->outPortParams->nWidth;
					   
  h264VdecClient->outPortParams->cmnOutParams.pOutPortDef->format.video.eColorFormat  =
                       h264VdecClient->outPortParams->colorFormat;
  h264VdecClient->outPortParams->cmnOutParams.pOutPortDef->format.video.nSliceHeight  = 0;
  h264VdecClient->outPortParams->cmnOutParams.pOutPortDef->format.video.nBitrate = 10485760;
  h264VdecClient->outPortParams->cmnOutParams.pOutPortDef->format.video.xFramerate    = h264VdecConfig->sBasicParams.nFramerate << 16;
  h264VdecClient->outPortParams->cmnOutParams.pOutPortDef->format.video.bFlagErrorConcealment=
                       OMX_FALSE;
  h264VdecClient->outPortParams->cmnOutParams.pOutPortDef->format.video.eCompressionFormat   =
                       OMX_VIDEO_CodingUnused; //for tunnelling

  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;

  /*Set the OutPort Definition*/
  err = OMX_SetParameter( h264VdecClient->omtbPvt.handle,
                          OMX_IndexParamPortDefinition,
                          h264VdecClient->outPortParams->cmnOutParams.pOutPortDef);

  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_SetParameter");

  if(OMX_ErrorNone != err)
  {
    OMTB_OmxReturnStatus(err);
    return err;
  }

  PRINT(PRINT_FUNCTION_NAME, "Leaving <Function , instance #> : <%s , %d>\n",
                              __FUNCTION__, (int)h264VdecClient->omtbPvt.instanceNo);

  return err;
}


/******************************************************************************\
 *      H264VDEC_SetPortDefinition Function Definition
\******************************************************************************/
/**
 *
 *  @brief    Set i/o port params.
 *
 *  @param in:
 *            h264VdecClient:Pointer to appPrivateType structure
 *
 *  @param Out:
 *            None
 *
 *  @return   OMX_ERRORTYPE - OMX std return/error code
 *
 */

OMX_ERRORTYPE H264VDEC_SetPortDefinition(void* thisClient)
{

  OMX_ERRORTYPE err = OMX_ErrorNone;
  OMX_PORT_PARAM_TYPE portInit;
  OMTB_H264_VDEC_PRIVATE* h264VdecClient;
  OMTB_OMX_API_TIMING_VAR_DECL;

  h264VdecClient = (OMTB_H264_VDEC_PRIVATE*)thisClient;

  /* validate the function arguments */
  ASSERT(NULL != h264VdecClient);

  PRINT(PRINT_FUNCTION_NAME, "Entering <Function , instance #> : <%s , %d>\n",
                              __FUNCTION__, (int)h264VdecClient->omtbPvt.instanceNo);
  
  /* Set the component's OMX_PARAM_PORTDEFINITIONTYPE structure (input) */
  OMTB_SetHeader(&portInit,sizeof(OMX_PORT_PARAM_TYPE));
  portInit.nPorts = 2;
  portInit.nStartPortNumber = 0;
#if 1
  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;

  /* Initialize the Port*/
  err = OMX_SetParameter( h264VdecClient->omtbPvt.handle,
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
    PRINT(DEFAULT_MESSAGES, "Found The component for decoding\n");
  }
#endif
  /* set the i/p port params */
  err = H264VDEC_SetInputPortDefinition(h264VdecClient);
  if(OMX_ErrorNone != err)
  {
    PRINT(PRINT_ERR_MSG, "Error in setting i/p port params\n");
    OMTB_OmxReturnStatus(err);
  }

  /* set the o/p port params */
  err = H264VDEC_SetOutputPortDefinition(h264VdecClient);
  if(OMX_ErrorNone != err)
  {
    PRINT(PRINT_ERR_MSG, "Error in setting o/p port params\n");
    OMTB_OmxReturnStatus(err);
  }

  PRINT(PRINT_FUNCTION_NAME, "Leaving <Function , instance #> : <%s , %d>\n",
                              __FUNCTION__, (int)h264VdecClient->omtbPvt.instanceNo);

  return err;
}


/******************************************************************************\
 *      H264VDEC_ChangePortSettings Function Definition
\******************************************************************************/
/**
 *
 *  @brief    Change params for output port for H264 decoder.
 *
 *  @param in:
 *            h264VdecClient:Pointer to appPrivateType structure
 *
 *  @param Out:
 *            None
 *
 *  @return   OMX_ERRORTYPE - OMX std return/error code
 *
 */
#if 0
static OMX_ERRORTYPE H264VDEC_ChangePortSettings(OMTB_H264_VDEC_PRIVATE* h264VdecClient)
{
//  TIMM_OSAL_ERRORTYPE retval;
  OMX_ERRORTYPE err = OMX_ErrorNone;

  ASSERT(NULL != h264VdecClient);

  PRINT(PRINT_FUNCTION_NAME, "Entering <Function , instance #> : <%s , %d>\n",
                                __FUNCTION__, (int)h264VdecClient->omtbPvt.instanceNo);

  /* disable the port */
  err = OMX_SendCommand(h264VdecClient->omtbPvt.handle,
                        OMX_CommandPortDisable,
                        h264VdecClient->outPortParams->cmnOutParams.pOutPortDef->nPortIndex,
                        NULL);
  if(OMX_ErrorNone != err)
  {
    PRINT(PRINT_ERR_MSG, "%s: Error from SendCommand OMX_CommandPortDisable\n", __FUNCTION__);
    return err;
  }

  /* release output port buffers */
  err = H264VDEC_FreeOutputResources(h264VdecClient);

  if(OMX_ErrorNone != err)
  {
    PRINT(PRINT_ERR_MSG, "Error in Buffer release for o/p port\n");
    OMTB_OmxReturnStatus(err);
    return err;
  }

  /* get the updated port settings */
  err = OMX_GetParameter(h264VdecClient->omtbPvt.handle,
                     OMX_IndexParamPortDefinition,
                     h264VdecClient->outPortParams->cmnOutParams.pOutPortDef);
  if(OMX_ErrorNone != err)
  {
    PRINT(PRINT_ERR_MSG, "%s: Error in OMX_GetParameter\n", __FUNCTION__);
    return err;
  }

  err = OMX_SendCommand(h264VdecClient->omtbPvt.handle,
                        OMX_CommandPortEnable,
                        h264VdecClient->outPortParams->cmnOutParams.pOutPortDef->nPortIndex,
                        NULL);
  if(OMX_ErrorNone != err)
  {
    PRINT(PRINT_ERR_MSG, "%s: Error in OMX_SendCommand:OMX_CommandPortEnable\n", __FUNCTION__);
    return err;
  }

/*  retval = TIMM_OSAL_ClearPipe(h264VdecClient->outPortParams->cmnOutParams.opBufPipe);
  if (TIMM_OSAL_ERR_NONE != retval)
  {
    PRINT(PRINT_ERR_MSG, "%s: Error in clearing Output Pipe!\n", __FUNCTION__);
    err = OMX_ErrorNotReady;
    return err;
  }
*/
  /* allocate i/p port buffers */
  err = H264VDEC_AllocateOutputResources(h264VdecClient);

  if(OMX_ErrorNone != err)
  {
    PRINT(PRINT_ERR_MSG, "Error in Buffer allocation for o/p port\n");
    OMTB_OmxReturnStatus(err);
    return err;
  }

  /* use o/p buffers */
  err = H264VDEC_UseInitialOutputResources(h264VdecClient);

  if(OMX_ErrorNone != err)
  {
    PRINT(PRINT_ERR_MSG, "Error in sending initial buffers to o/p port\n");
    OMTB_OmxReturnStatus(err);
    return err;
  }

  PRINT(PRINT_FUNCTION_NAME, "Leaving <Function , instance #> : <%s , %d>\n",
                                  __FUNCTION__, (int)h264VdecClient->omtbPvt.instanceNo);

  return err;
}
#endif

/******************************************************************************\
 *      H264VDEC_GetStructIdx Function Definition
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

OmtbRet H264VDEC_GetStructIdx(
  char *indexStr,
  unsigned int template,
  unsigned int instanceNo,
  unsigned int portIdx,
  unsigned int *nConfigIndex,
  void **pCompCfgStruct)
{
  unsigned int enumCount = 0;
  char channelName[OMX_MAX_STRINGNAME_SIZE];         /* Capture channel name */

  /* Use the specified template structure */
  h264VdecConfig = (OMTB_H264_VDEC_CONFIG_PARAMS*)
                     &(omtbCfgTemplate[template]->h264VdecTemplate);

  /* Get the corresponding string for enum values from enum table
     Set structure index
     Set structure pointer
     Set port index for which parameter to be updated
     Set structure header info */
  while(strcmp(enumTblH264VdecCfgParamIdx[enumCount].name , ""))
  {
    if(0 == strcmp(enumTblH264VdecCfgParamIdx[enumCount].name,
                   indexStr))
    {
      switch(enumTblH264VdecCfgParamIdx[enumCount].value)
      {
        case OMX_TI_IndexConfigChannelName:
          {
            *nConfigIndex   = enumTblH264VdecCfgParamIdx[enumCount].value;
            *pCompCfgStruct = &h264VdecConfig->sChannelName;
            h264VdecConfig->sChannelName.nPortIndex = 1;
/* FIXME:  To support backword compatability with the older omtb scripts,
           the following code has not been removed, 
*/		   
//            if(!strcmp("NULL", vpssVfccConfig->sChannelName.cChannelName))			
            {
            snprintf(channelName, OMX_MAX_STRINGNAME_SIZE, "FQ_DECOUT_%d",
                     instanceNo);
            channelName[OMX_MAX_STRINGNAME_SIZE - 1] = '\0';
 
			DOMX_UTL_Strncpy ( ( char * ) h264VdecConfig->sChannelName.cChannelName, channelName,
					  sizeof ( h264VdecConfig->sChannelName.cChannelName ) );
            }
            OMTB_SetHeader( *pCompCfgStruct,
                            sizeof(OMX_CONFIG_CHANNELNAME));
          }
          return OMTB_SUCCESS;
        case OMX_TI_IndexConfigChannelGroupInfo:
          {
            *nConfigIndex   = enumTblH264VdecCfgParamIdx[enumCount].value;
            *pCompCfgStruct = &h264VdecConfig->sConfigChannelGroupInfo;
//            vpssVfpcScConfig->sConfigChannelGroupInfo.nPortIndex = portIdx;
            OMTB_SetHeader( *pCompCfgStruct,
                            sizeof(OMX_CONFIG_CHANNELGROUPINFO));
          }
          return OMTB_SUCCESS;

        case OMX_TI_IndexParamBuffMemType:
          {
            *nConfigIndex   = enumTblH264VdecCfgParamIdx[enumCount].value;
            *pCompCfgStruct = &h264VdecConfig->sMemTypeCfg;
             h264VdecConfig->sMemTypeCfg.nPortIndex = portIdx;
             OMTB_SetHeader( *pCompCfgStruct,
			                 sizeof(OMX_PARAM_BUFFER_MEMORYTYPE));
          }
  		  return OMTB_SUCCESS;

  		case OMX_IndexParamCompBufferSupplier:
		  {
			*nConfigIndex   = enumTblH264VdecCfgParamIdx[enumCount].value;
			*pCompCfgStruct = &h264VdecConfig->sBufSupplier;
			 h264VdecConfig->sBufSupplier.nPortIndex = portIdx;
			 OMTB_SetHeader( *pCompCfgStruct,
							 sizeof(OMX_PARAM_BUFFERSUPPLIERTYPE));
		  }
  		  return OMTB_SUCCESS;

        case OMX_IndexParamVideoPortFormat:
		  {
			*nConfigIndex   = enumTblH264VdecCfgParamIdx[enumCount].value;
			*pCompCfgStruct = &h264VdecConfig->sVideoPortFormat;
			 h264VdecConfig->sVideoPortFormat.nPortIndex = portIdx;
             OMTB_SetHeader( *pCompCfgStruct,
							 sizeof(OMX_VIDEO_PARAM_PORTFORMATTYPE));
		  }
  		  return OMTB_SUCCESS;

       	case OMX_IndexConfigVideoMacroBlockErrorMap:
		  {
			*nConfigIndex   = enumTblH264VdecCfgParamIdx[enumCount].value;
			*pCompCfgStruct = &h264VdecConfig->sMbErrorReporting;
			 h264VdecConfig->sMbErrorReporting.nPortIndex = portIdx;
			 OMTB_SetHeader( *pCompCfgStruct,
							 sizeof(OMX_CONFIG_MBERRORREPORTINGTYPE));
		  }
  		  return OMTB_SUCCESS;

       	case OMX_TI_IndexParamFileModeType:
		  {
			*nConfigIndex   = enumTblH264VdecCfgParamIdx[enumCount].value;
			*pCompCfgStruct = &h264VdecConfig->sFileModeCfg;
			 h264VdecConfig->sFileModeCfg.nPortIndex = portIdx;
			 OMTB_SetHeader( *pCompCfgStruct,
							 sizeof(OMX_PARAM_FILEMODE_TYPE));
		  }
  		  return OMTB_SUCCESS;

       	case OMX_IndexParamVideoInit:
		  {
			*nConfigIndex   = enumTblH264VdecCfgParamIdx[enumCount].value;
			*pCompCfgStruct = &h264VdecConfig->sPortInit;
			 OMTB_SetHeader( *pCompCfgStruct,
							 sizeof(OMX_PORT_PARAM_TYPE));
		  }
		  return OMTB_SUCCESS;

        case OMX_IndexParamVideoAvc:
		  {
			*nConfigIndex   = enumTblH264VdecCfgParamIdx[enumCount].value;
			*pCompCfgStruct = &h264VdecConfig->avcParams;
			 OMTB_SetHeader( *pCompCfgStruct,
							 sizeof(OMX_VIDEO_PARAM_AVCTYPE));
		  }
		  return OMTB_SUCCESS;

        case OMX_IndexParamVideoMacroblocksPerFrame:
		  {
			*nConfigIndex   = enumTblH264VdecCfgParamIdx[enumCount].value;
			*pCompCfgStruct = &h264VdecConfig->sMBType;
			 OMTB_SetHeader( *pCompCfgStruct,
							 sizeof(OMX_PARAM_MACROBLOCKSTYPE));
		  }
		  return OMTB_SUCCESS;
		  
		case OMX_TI_IndexParamCompPortNotifyType:
          {
			*nConfigIndex   = enumTblH264VdecCfgParamIdx[enumCount].value;
			*pCompCfgStruct = &h264VdecConfig->sCompPortNotifyType;
            h264VdecConfig->sCompPortNotifyType.nPortIndex = portIdx;
            OMTB_SetHeader( *pCompCfgStruct,
                            sizeof(OMX_PARAM_COMPPORT_NOTIFYTYPE));
		  }
		  return OMTB_SUCCESS;	
		  
  		case OMX_IndexParamPortDefinition:
	      {
		    *nConfigIndex   = enumTblH264VdecCfgParamIdx[enumCount].value;
		    *pCompCfgStruct = &h264VdecConfig->sPortDefType;
            h264VdecConfig->sPortDefType.nPortIndex = portIdx;			
		    OMTB_SetHeader( *pCompCfgStruct,
			   			    sizeof(OMX_PARAM_PORTDEFINITIONTYPE));
	      }
	      return OMTB_SUCCESS;
		  
       	default:
          {
            return OMTB_FAIL;
          }

      } // switch(enumTblH264VdecCfgParamIdx[enumCount].value)

    } // if(0 == strcmp(enumTblH264VdecCfgParamIdx[enumCount].name, ...

    enumCount++;
  }

  return OMTB_SUCCESS;
}


/******************************************************************************\
 *      H264VDEC_FuncTsk Thread Definition
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

void H264VDEC_FuncTsk(void *argc, void *threadsArg)
{
  int threadRes = TIMM_OSAL_ERR_NONE;
  OMX_ERRORTYPE err = OMX_ErrorNone;
  OMTB_H264_VDEC_PRIVATE* h264VdecClient = NULL;
  OMTB_DATA_THREAD_ARG *funcDataThreadArg = (OMTB_DATA_THREAD_ARG *)threadsArg;
  unsigned int instanceNo = 0;
  TIMM_OSAL_ERRORTYPE bReturnStatus = TIMM_OSAL_ERR_NONE;  
  OMTB_OMX_API_TIMING_VAR_DECL;

  /* thread argument validation */
  ASSERT(NULL != threadsArg);
  ASSERT(NULL != funcDataThreadArg->h264VdecClient);

  h264VdecClient = funcDataThreadArg->h264VdecClient;

  PRINT(PRINT_MUST, "Entering <Thread , instance #> : <%s , %d>\n",
                     __FUNCTION__, (int)h264VdecClient->omtbPvt.instanceNo);

  PRINT(PRINT_SIMPLE_MESSAGE, "\nbufferOutSize:%d\n",\
        (int)h264VdecClient->outPortParams->cmnOutParams.bufferOutSize);

  /* Set the port params */
  err = H264VDEC_SetPortDefinition(h264VdecClient);

  if(OMX_ErrorNone != err)
  {
    OMTB_OmxReturnStatus(err);
  }

  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;

  /* send command to component to go to idle state */
  err = OMX_SendCommand(h264VdecClient->omtbPvt.handle,
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
  err = OMTB_ClientAllocateResources(h264VdecClient);

  if(OMX_ErrorNone != err)
  {
    OMTB_OmxReturnStatus(err);
  }

  /* waiting for component to go to idle state */
  bReturnStatus = TIMM_OSAL_SemaphoreObtain(h264VdecClient->omtbPvt.eventSem, OMTB_SEM_TIMEOUT);

  if(TIMM_OSAL_WAR_TIMEOUT == bReturnStatus)
  {
    OMTB_OmxReturnStatus(OMX_ErrorTimeout);  
  }
  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;

  /* send command to component to go to executing state */
  err = OMX_SendCommand(h264VdecClient->omtbPvt.handle,
                        OMX_CommandStateSet,
                        OMX_StateExecuting,
                        NULL);

  if(OMX_ErrorNone != err)
  {
    OMTB_OmxReturnStatus(err);
  }

  /* waiting for component to go to executing state */
  bReturnStatus = TIMM_OSAL_SemaphoreObtain(h264VdecClient->omtbPvt.eventSem, OMTB_SEM_TIMEOUT);

  if(TIMM_OSAL_WAR_TIMEOUT == bReturnStatus)
  {
    OMTB_OmxReturnStatus(OMX_ErrorTimeout);  
  }
  
  /* Update the func create count */
  H264VDEC_funcCreateCount++;
  PRINT(PRINT_MUST, "%s: H264 FUNC Create Count: %u\n", __FUNCTION__,
                    (unsigned int) H264VDEC_funcCreateCount);

  /* Update the data streaming thread arguments */
  strmThreadArg[h264VdecClient->omtbPvt.instanceNo].h264VdecClient = h264VdecClient;

  /* Create input data read thread */
  threadRes = TIMM_OSAL_CreateTask(
                    (void *)&h264VdecClient->inPortParams->cmnInParams.inDataStrmThrdId,
                    (TIMM_OSAL_TaskProc)OMTB_InputDataRead,
                    0,
                    &strmThreadArg[h264VdecClient->omtbPvt.instanceNo],
                    OMTB_H264_VDEC_TSK_STACK_SIZE,
                    OMTB_H264_VDEC_GROUP_PRIORITY,
                    (signed char*)"H264_VDEC_DATA_IN_TSK");

  if(TIMM_OSAL_ERR_NONE != threadRes)
  {
    PRINT(PRINT_ERR_MSG,
          "Unable to start H264 video decode input data read thread\n");
  }

  /* Create output data write thread */
  threadRes = TIMM_OSAL_CreateTask(
                    (void *)&h264VdecClient->outPortParams->cmnOutParams.outDataStrmThrdId,
                    (TIMM_OSAL_TaskProc)OMTB_OutputDataWrite,
                    0,
                    &strmThreadArg[h264VdecClient->omtbPvt.instanceNo],
                    OMTB_H264_VDEC_TSK_STACK_SIZE,
                    OMTB_H264_VDEC_GROUP_PRIORITY,
                    (signed char*)"H264_VDEC_DATA_OUT_TSK");

  if(TIMM_OSAL_ERR_NONE != threadRes)
  {
    PRINT(PRINT_ERR_MSG,
          "Unable to start H264 video decode output data write thread\n");
  }


  /* Wait for EOS */
  bReturnStatus = TIMM_OSAL_SemaphoreObtain(h264VdecClient->eofSem, OMTB_SEM_TIMEOUT);

  if(TIMM_OSAL_WAR_TIMEOUT == bReturnStatus)
  {
    OMTB_OmxReturnStatus(OMX_ErrorTimeout);  
  }
  
  PRINT(DEFAULT_MESSAGES, "The execution of the video decoding\
                           process is terminated\n");

  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;

  /* state change of component from executing to idle */
  err = OMX_SendCommand(h264VdecClient->omtbPvt.handle,
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
  bReturnStatus = TIMM_OSAL_SemaphoreObtain(h264VdecClient->omtbPvt.eventSem, OMTB_SEM_TIMEOUT);

  if(TIMM_OSAL_WAR_TIMEOUT == bReturnStatus)
  {
    OMTB_OmxReturnStatus(OMX_ErrorTimeout);  
  }  

  PRINT(DEFAULT_MESSAGES, "State transitioned to Idle\n");

  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;

  /* sending command to component to go to loaded state */
  err = OMX_SendCommand(h264VdecClient->omtbPvt.handle,
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
  h264VdecClient->outPortParams->cmnOutParams.flagEos = OMX_FALSE;
  h264VdecClient->inPortParams->cmnInParams.flagInputEos = OMX_FALSE;

  /* Function to reelase the resources allocated by component */
  err = OMTB_ClientFreeResources(h264VdecClient);

  if(OMX_ErrorNone != err)
  {
    OMTB_OmxReturnStatus(err);
  }

  /*wait for event handler to report completion of loaded command */
  bReturnStatus = TIMM_OSAL_SemaphoreObtain(h264VdecClient->omtbPvt.eventSem, OMTB_SEM_TIMEOUT);

  if(TIMM_OSAL_WAR_TIMEOUT == bReturnStatus)
  {
    OMTB_OmxReturnStatus(OMX_ErrorTimeout);  
  }
  
  PRINT(PRINT_SIMPLE_MESSAGE, "State transitioned to loaded\n");

  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;

  /* Delete the component instance */
  err = OMX_FreeHandle(h264VdecClient->omtbPvt.handle);

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
    h264VdecClient->omtbPvt.handle = NULL;
    PRINT(PRINT_MUST,
          "\r      \n\nOMTB-Deleted H264Vdec Instance #: %d\n\n",
          (int) h264VdecClient->omtbPvt.instanceNo);
    omtbClass[OMTB_H264_VDEC_CLASS].handle[h264VdecClient->omtbPvt.instanceNo] = NULL;
  }

  PRINT(PRINT_SIMPLE_MESSAGE, "video dec freed\n");

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
  h264VdecClient->omtbPvt.flagThrCreated = OMX_FALSE;

  /* save the instance no to local variable */
  instanceNo = h264VdecClient->omtbPvt.instanceNo;

  /* Reelase the memory allocated for app pvt data */
  OMTB_FreeMemory(h264VdecClient);

  /* Update the func delete count */
  H264VDEC_funcDeleteCount++;

  PRINT(PRINT_MUST, "%s: H264 FUNC Delete Count: %u\n", __FUNCTION__,
                    (unsigned int) H264VDEC_funcDeleteCount);

  PRINT(PRINT_MUST, "Leaving <Thread , instance #> : <%s , %d>\n",
                     __FUNCTION__, (int)instanceNo);

  /* exit the thread */
  TIMM_OSAL_ExitTask(
      omtbClass[OMTB_H264_VDEC_CLASS].execThreadId[instanceNo],
      NULL);
}


/******************************************************************************\
 *      H264VDEC_FillData Function Definition
\******************************************************************************/
/**
 *
 *  @brief    This function reads from I/P file and fill date in i/p buffer
 *
 *  @param in:
 *            pAppData: Pointer to private data structure
 *
 *            count - Encoded frame number
 *
 *  @param Out:
 *            OMX_BUFFERHEADERTYPE * - Pointer of I/P filled Buffer
 *  @return   No of bytes read
 *
 */

unsigned int H264VDEC_FillData(
  OMTB_H264_VDEC_PRIVATE* pAppData,
  OMX_BUFFERHEADERTYPE *pBuf,
  unsigned int count)
{
  unsigned int dataRead = 0;
  int frameSize = 0;

  /* validate the function arguments */
  ASSERT(NULL != pAppData);
  ASSERT(NULL != pBuf);


  PRINT(PRINT_DEBUG_MESSAGE, "Entering Function:%s\n",__FUNCTION__);

  pAppData->inPortParams->h264ParseCtx.outBuf.ptr =pBuf->pBuffer;					 
  pAppData->inPortParams->h264ParseCtx.outBuf.bufsize = pAppData->inPortParams->cmnInParams.bufferInSize;					 
  pAppData->inPortParams->h264ParseCtx.outBuf.bufused = 0;
  
  /* Get the size of one frame at a time */
  frameSize =  OMTB_H264GetNextFrameSize(&pAppData->inPortParams->h264ParseCtx,
                                          pAppData->inPortParams->cmnInParams.fileIpBufPipe,
										  pAppData->inPortParams->cmnInParams.fileOpBufPipe);
										  
  PRINT(PRINT_DEBUG_MESSAGE, "--> Frame Size:%d\n",frameSize);
  
    /* Update the buffer header with buffer filled length and alloc length */
  pBuf->nFilledLen = frameSize;


  PRINT(PRINT_DEBUG_MESSAGE, "nAllocLen is %d\n",
                              (int) pBuf->nAllocLen);
  PRINT(PRINT_DEBUG_MESSAGE, "nFilledLen is: %d\n",
                                (int) pBuf->nFilledLen);
  PRINT(PRINT_FUNCTION_NAME, "Leaving <Function , instance #> : <%s , %d>\n",
                              __FUNCTION__, (int)pAppData->omtbPvt.instanceNo);

  return frameSize;
}

/******************************************************************************\
 *      H264VDEC_SetTemplateDefVal Function Definition
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

MX_Result H264VDEC_SetTemplateDefVal(OMTB_TEMPLATE_INFO *pTemplate)
{
  OMTB_H264_VDEC_CONFIG_PARAMS *h264VidDecCfg = NULL;

  /* param validation */
  if(NULL == pTemplate)
  {
    PRINT(PRINT_ERR_MSG, "%s: Memory for Template not allocated\n",__FUNCTION__);
    return ERR_INVNAME;
  }

  /* H264 VDEC configuration */
  h264VidDecCfg = &pTemplate->h264VdecTemplate;

  strcpy(h264VidDecCfg->sBasicParams.inputFile, "h264vdec_sample.264");
  strcpy(h264VidDecCfg->sBasicParams.outputFile,"h264vdec_test.yuv");
  strcpy(h264VidDecCfg->sBasicParams.compName,   OMTB_H264_VDEC_COMPONENT_NAME);
  
  h264VidDecCfg->sBasicParams.frameWidth       = OMTB_H264_VDEC_DEF_WIDTH;
  h264VidDecCfg->sBasicParams.frameHeight      = OMTB_H264_VDEC_DEF_HEIGHT;
  h264VidDecCfg->sBasicParams.colorFormat      = OMX_COLOR_FormatYUV420SemiPlanar;
  h264VidDecCfg->sBasicParams.inColorFormat    = OMX_COLOR_FormatYUV420Planar;
  h264VidDecCfg->sBasicParams.dataOutPutMode   = OMTB_FILE;
  h264VidDecCfg->sBasicParams.dataInPutMode    = OMTB_FILE;
  h264VidDecCfg->sBasicParams.numInBuf         = OMTB_H264_VDEC_NUM_IN_BUFS;
  h264VidDecCfg->sBasicParams.numOutBuf        = OMTB_H264_VDEC_NUM_OUT_BUFS;
  h264VidDecCfg->sBasicParams.inBufAlignment   = 0;
  h264VidDecCfg->sBasicParams.outBufAlignment  = 0;
  h264VidDecCfg->sBasicParams.inBufSize        = OMTB_H264_VDEC_MAX_INBUFF_SIZE;
  h264VidDecCfg->sBasicParams.outBufSize       = 0;
  h264VidDecCfg->sBasicParams.inBufSzFlag      = OMX_FALSE;
  h264VidDecCfg->sBasicParams.outBufSzFlag     = OMX_FALSE;
  h264VidDecCfg->sBasicParams.inBufContiguous  = TIMM_OSAL_TRUE;
  h264VidDecCfg->sBasicParams.outBufContiguous = TIMM_OSAL_TRUE;
  h264VidDecCfg->sBasicParams.flagUseInBuffer  = OMX_TRUE;
  h264VidDecCfg->sBasicParams.flagUseOutBuffer = OMX_FALSE;
  h264VidDecCfg->sBasicParams.compressionFormat = OMX_VIDEO_CodingAVC;
  h264VidDecCfg->sBasicParams.nFramerate       = OMTB_H264_VDEC_DEF_FRM_RATE; 
  h264VidDecCfg->sBasicParams.fileReset        = OMX_TRUE;
  
  h264VidDecCfg->sMemTypeCfg.eBufMemoryType = OMX_BUFFER_MEMORY_DEFAULT;

  h264VidDecCfg->sBufSupplier.eBufferSupplier =  OMX_BufferSupplyUnspecified;

  h264VidDecCfg->sMbErrorReporting.bEnabled = OMX_FALSE;

  h264VidDecCfg->sFileModeCfg.bEnableFileMode = OMX_FALSE;

  h264VidDecCfg->sPortInit.nPorts           = OMTB_H264_VDEC_DEF_NO_OF_PORTS;
  h264VidDecCfg->sPortInit.nStartPortNumber = OMTB_H264_VDEC_DEF_START_PORT_NUM;
  
  h264VidDecCfg->sVideoPortFormat.eCompressionFormat = OMX_VIDEO_CodingAVC;
  h264VidDecCfg->sVideoPortFormat.eColorFormat = OMX_COLOR_FormatYUV420SemiPlanar;
  h264VidDecCfg->sVideoPortFormat.xFramerate = OMTB_H264_VDEC_DEF_FRM_RATE;
  
  h264VidDecCfg->sCompPortNotifyType.eNotifyType = OMX_NOTIFY_TYPE_ALWAYS;
  
  h264VidDecCfg->sPortDefType.eDir                               = OMX_DirInput;
  h264VidDecCfg->sPortDefType.nBufferCountActual                 = OMTB_H264_VDEC_NUM_IN_BUFS;
  h264VidDecCfg->sPortDefType.nBufferCountMin                    = 1; 
  h264VidDecCfg->sPortDefType.nBufferSize                        = OMTB_H264_VDEC_MAX_INBUFF_SIZE;    
  h264VidDecCfg->sPortDefType.bEnabled                           = OMX_FALSE; 
  h264VidDecCfg->sPortDefType.bPopulated                         = OMX_FALSE; 
  h264VidDecCfg->sPortDefType.eDomain                            = OMX_PortDomainVideo;
  h264VidDecCfg->sPortDefType.bBuffersContiguous                 = OMX_FALSE;
  h264VidDecCfg->sPortDefType.nBufferAlignment                   = 0;
  h264VidDecCfg->sPortDefType.format.video.cMIMEType             = NULL;
  h264VidDecCfg->sPortDefType.format.video.pNativeRender         = NULL;
  h264VidDecCfg->sPortDefType.format.video.nFrameWidth           = OMTB_H264_VDEC_DEF_WIDTH;
  h264VidDecCfg->sPortDefType.format.video.nFrameHeight          = OMTB_H264_VDEC_DEF_HEIGHT;
  h264VidDecCfg->sPortDefType.format.video.nStride               = (OMTB_H264_VDEC_DEF_WIDTH);
  h264VidDecCfg->sPortDefType.format.video.nSliceHeight          = 0;
  h264VidDecCfg->sPortDefType.format.video.nBitrate              = OMTB_H264_VDEC_DEF_BIT_RATE;
  h264VidDecCfg->sPortDefType.format.video.xFramerate            = OMTB_H264_VDEC_DEF_FRM_RATE;
  h264VidDecCfg->sPortDefType.format.video.bFlagErrorConcealment = OMX_FALSE;
  h264VidDecCfg->sPortDefType.format.video.eCompressionFormat    = OMX_VIDEO_CodingAVC;
  h264VidDecCfg->sPortDefType.format.video.eColorFormat          = OMX_COLOR_FormatYCbYCr;
  h264VidDecCfg->sPortDefType.format.video.pNativeWindow         = NULL;
  
  strcpy(h264VidDecCfg->sChannelName.cChannelName, "NULL");
  
  return ERR_NOERR;
}

/******************************************************************************\
 *      H264VDEC_ClassInit Function Definition
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
OMX_ERRORTYPE H264VDEC_ClassInit(OMTB_CLIENT_PRIVATE* thisClient)
{
  OmtbRet err = OMTB_SUCCESS;
  
  PRINT(PRINT_FUNCTION_NAME, "Entering <Function> : <%s>\n",
                              __FUNCTION__);
							  
  /* no of input / output ports */
  thisClient->omtbPvt.numInport  = OMTB_H264_VDEC_MAX_IN_PORT;
  thisClient->omtbPvt.numOutport = OMTB_H264_VDEC_MAX_OUT_PORT;
  thisClient->omtbPvt.startOutportIndex = OMTB_H264_VDEC_MAX_IN_PORT;
  
  thisClient->omtbPvt.outputDataWriteTask = OMTB_OutputDataWrite;
  thisClient->omtbPvt.inputDataReadTask = OMTB_InputDataRead;

  /* Function pointer for GetStructIdx */
  thisClient->omtbPvt.fpGetStructIdx = H264VDEC_GetStructIdx; 
  thisClient->omtbPvt.fpSetBufferSize = H264VDEC_SetBufferSize;
  thisClient->omtbPvt.fpSetPortDefinition = H264VDEC_SetPortDefinition;
	
  thisClient->omtbPvt.numFileInBufs = (OMTB_CLIENT_MAX_NUM_FILE_IN_BUFS * 4);
  thisClient->omtbPvt.numFileOutBufs = OMTB_CLIENT_MAX_NUM_FILE_OUT_BUFS;
  
  thisClient->omtbPvt.readSize       = H264PARSER_READSIZE;
  thisClient->omtbPvt.writeSize      = OMTB_H264_VDEC_MAX_OUTBUFF_SIZE; 	 
  
  thisClient->omtbPvt.eClassType = OMTB_H264_VDEC_CLASS;
	
  PRINT(PRINT_FUNCTION_NAME, "Leaving <Function> : <%s>\n",
                              __FUNCTION__);  
  return (err);							  
}
/*----------------------------- end of file ----------------------------------*/
