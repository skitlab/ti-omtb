
/*
 * omtbAdec.c
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
#include "omtbAdec.h"
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

/******************************************************************************\
 *      Globals
\******************************************************************************/

/* Pointer to config params */
OMTB_ADEC_CONFIG_PARAMS *adecConfig = NULL;


/******************************************************************************\
 *      Static Globals
\******************************************************************************/

static OMX_U32 ADEC_funcCreateCount = 0;  /* Func create count */
static OMX_U32 ADEC_apiCreateCount = 0;   /* API create count */

static OMX_U32 ADEC_funcDeleteCount = 0;  /* Func delete count */
static OMX_U32 ADEC_apiDeleteCount = 0;   /* API delete count */

/* Enum Entry for Supported cfg param indexs */

PRIVATE MX_DBG_ENUM_ENTRY_T enumTblAdecCfgParamIdx[] =
{
  /* ADD ENTRIES HERE for SetConfig/SetParam/GetConfig/GetParam */
  {"OMX_TI_IndexConfigChannelName",          OMX_TI_IndexConfigChannelName,          ""},
  {"OMX_TI_IndexParamBuffMemType",           OMX_TI_IndexParamBuffMemType,           ""},
  {"OMX_IndexParamCompBufferSupplier",       OMX_IndexParamCompBufferSupplier,       ""},
  {"OMX_IndexParamAudioPortFormat",          OMX_IndexParamAudioPortFormat,          ""},
  {"OMX_TI_IndexParamFileModeType",          OMX_TI_IndexParamFileModeType,          ""},
  {"OMX_IndexParamAudioInit",                OMX_IndexParamAudioInit,                ""},
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
 *      ADEC_SetBufferSize Function Definition
\******************************************************************************/
/**
 *
 *  @brief    Allocate memory for private data structure for audio decode
 *            component
 *
 *  @param in:
 *            adecClient:Pointer to appPrivateType structure
 *
 *  @param Out:
 *            None
 *
 *  @return   OmtbRet - OMTB return/error code
 *
 */

OmtbRet ADEC_SetBufferSize(void *thisClient)
{
  OmtbRet err = OMTB_SUCCESS;
  OMTB_BASIC_CONFIG_PARAMS *pBasicConfig = NULL;
  OMTB_ADEC_PRIVATE *adecClient = NULL;
  
  /* validate the function arguments */
  ASSERT(NULL != thisClient);
  adecClient = (OMTB_ADEC_PRIVATE*)thisClient;
  pBasicConfig = &(omtbCfgTemplate[adecClient->omtbPvt.templateNo]->adecTemplate.sBasicParams);

  
  PRINT(PRINT_FUNCTION_NAME, "Entering <Function , instance #> : <%s , %d>\n",
                              __FUNCTION__, (int)adecClient->omtbPvt.instanceNo);

  /* set the input buffer size */
  if(OMX_FALSE == adecClient->inPortParams->cmnInParams.inBufSzFlag)
  {
    /* i/p buffer size calculation based on input dimension speculation */  
    //adecClient->inPortParams->cmnInParams.bufferInSize = pBasicConfig->frameWidth * pBasicConfig->frameHeight;
	adecClient->inPortParams->cmnInParams.bufferInSize = 4096;
  }
  else
  {
    adecClient->inPortParams->cmnInParams.bufferInSize =  pBasicConfig->inBufSize;
  }
  
  /* set the output buffer size */    
  if(OMX_FALSE == adecClient->outPortParams->cmnOutParams.outBufSzFlag)
  {
    /* output buffer size calculation based on frame dimension speculation */
    adecClient->outPortParams->cmnOutParams.bufferOutSize = 8192;	
  }
  else
  {
    adecClient->outPortParams->cmnOutParams.bufferOutSize =
                                               pBasicConfig->outBufSize;
  }
  
  PRINT(PRINT_FUNCTION_NAME, "Leaving <Function #> : <%s>\n",
                             __FUNCTION__);  
  return err;
}

/******************************************************************************\
 *      ADEC_SetInputPortDefinition Function Definition
\******************************************************************************/
/**
 *
 *  @brief    Set i/p port params.
 *
 *  @param in:
 *            adecClient:Pointer to appPrivateType structure
 *
 *  @param Out:
 *            None
 *
 *  @return   OMX_ERRORTYPE - OMX std return/error code
 *
 */

OMX_ERRORTYPE ADEC_SetInputPortDefinition(OMTB_ADEC_PRIVATE* adecClient)
{

  OMX_ERRORTYPE err = OMX_ErrorNone;
  OMTB_OMX_API_TIMING_VAR_DECL;
  OMTB_ADEC_CONFIG_PARAMS *adecConfig = NULL; 


  /* validate the function arguments */
  ASSERT(NULL != adecClient);

  PRINT(PRINT_FUNCTION_NAME, "Entering <Function , instance #> : <%s , %d>\n",
                              __FUNCTION__, (int)adecClient->omtbPvt.instanceNo);

  adecConfig = (OMTB_ADEC_CONFIG_PARAMS*)
                     &(omtbCfgTemplate[adecClient->omtbPvt.templateNo]->adecTemplate);
  
  /* input buffer size calculation based on input dimension speculation */
  if(OMX_FALSE == adecClient->inPortParams->cmnInParams.inBufSzFlag)
  {
    /* i/p buffer size calculation based on input dimension speculation */  
    adecClient->inPortParams->cmnInParams.bufferInSize = adecConfig->sBasicParams.frameWidth * adecConfig->sBasicParams.frameHeight;
  }
  else
  {
    adecClient->inPortParams->cmnInParams.bufferInSize =  adecConfig->sBasicParams.inBufSize;
  }

  /* Set the component's OMX_PARAM_PORTDEFINITIONTYPE structure (input) */
  OMTB_SetHeader( adecClient->inPortParams->cmnInParams.pInPortDef,
                  sizeof(OMX_PARAM_PORTDEFINITIONTYPE));

  adecClient->inPortParams->cmnInParams.pInPortDef->nPortIndex          = OMTB_ADEC_INPUT_PORT_IDX;
  /* Get the default values of input port params set by the decoder*/
  err = OMX_GetParameter( adecClient->omtbPvt.handle,
                          OMX_IndexParamPortDefinition,
                          adecClient->inPortParams->cmnInParams.pInPortDef);
  if(OMX_ErrorNone != err)
  {
	OMTB_OmxReturnStatus(err);
	return err;
  }
  
  adecClient->inPortParams->cmnInParams.pInPortDef->eDir                = OMX_DirInput;

  adecClient->inPortParams->cmnInParams.pInPortDef->nBufferCountActual  =
                                  adecClient->inPortParams->cmnInParams.numInBuf;
  adecClient->inPortParams->cmnInParams.pInPortDef->nBufferCountMin     = 1;

  adecClient->inPortParams->cmnInParams.pInPortDef->nBufferSize         =
                                  adecClient->inPortParams->cmnInParams.bufferInSize;
  adecClient->inPortParams->cmnInParams.pInPortDef->bEnabled            = OMX_FALSE;
  adecClient->inPortParams->cmnInParams.pInPortDef->bPopulated          = OMX_FALSE;
  adecClient->inPortParams->cmnInParams.pInPortDef->eDomain             =
                                  OMX_PortDomainAudio;
  adecClient->inPortParams->cmnInParams.pInPortDef->bBuffersContiguous  = OMX_FALSE;
  adecClient->inPortParams->cmnInParams.pInPortDef->nBufferAlignment    = 32;

  /* OMX_AUDIO_PORTDEFINITION values for input port */
  adecClient->inPortParams->cmnInParams.pInPortDef->format.audio.cMIMEType      = "ADEC";
  adecClient->inPortParams->cmnInParams.pInPortDef->format.audio.pNativeRender  = NULL;
  adecClient->inPortParams->cmnInParams.pInPortDef->format.audio.bFlagErrorConcealment = OMX_FALSE;
  adecClient->inPortParams->cmnInParams.pInPortDef->format.audio.eEncoding = adecConfig->sBasicParams.compressionFormat;

  
  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;

  /*Set the inPort Definition*/
  err = OMX_SetParameter( adecClient->omtbPvt.handle,
                          OMX_IndexParamPortDefinition,
                          adecClient->inPortParams->cmnInParams.pInPortDef);


  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_SetParameter");

  if(OMX_ErrorNone != err)
  {
    OMTB_OmxReturnStatus(err);
    return err;
  }
  
  /* Initialize H.264 Parsing Context */
  adecClient->inPortParams->adecBuffer.pBuff =
                        (unsigned char *)TIMM_OSAL_Malloc((adecClient->inPortParams->cmnInParams.pInPortDef->nBufferSize << 1), 
                                                   TIMM_OSAL_TRUE,
                                                   0,
                                                   TIMMOSAL_MEM_SEGMENT_EXT);
  if (!adecClient->inPortParams->adecBuffer.pBuff)
  {
    PRINT(PRINT_ERR_MSG, "audio decode buf memory allocation failed\n");
    err = OMTB_INSUFFICIENT_RESOURCES;
  }
  else
  {  
    adecClient->inPortParams->adecBuffer.buffLen = 0;
    adecClient->inPortParams->adecBuffer.nOffset = 0;	
  }	
  
  PRINT(PRINT_FUNCTION_NAME, "Leaving <Function , instance #> : <%s , %d>\n",
                              __FUNCTION__, (int)adecClient->omtbPvt.instanceNo);

  return err;
}


/******************************************************************************\
 *      ADEC_SetOutputPortDefinition Function Definition
\******************************************************************************/
/**
 *
 *  @brief    Set o/p port params.
 *
 *  @param in:
 *            adecClient:Pointer to appPrivateType structure
 *
 *  @param Out:
 *            None
 *
 *  @return   OMX_ERRORTYPE - OMX std return/error code
 *
 */

OMX_ERRORTYPE ADEC_SetOutputPortDefinition(OMTB_ADEC_PRIVATE* adecClient)
{

  OMX_ERRORTYPE err = OMX_ErrorNone;
  OMTB_OMX_API_TIMING_VAR_DECL;
  OMTB_ADEC_CONFIG_PARAMS *adecConfig = NULL; 

  /* validate the function arguments */
  ASSERT(NULL != adecClient);

  PRINT(PRINT_FUNCTION_NAME, "Entering <Function , instance #> : <%s , %d>\n",
                              __FUNCTION__, (int)adecClient->omtbPvt.instanceNo);

  adecConfig =(OMTB_ADEC_CONFIG_PARAMS*)
                     &(omtbCfgTemplate[adecClient->omtbPvt.templateNo]->adecTemplate);
  if(OMX_FALSE == adecClient->outPortParams->cmnOutParams.outBufSzFlag)
  {
    /* output buffer size calculation based on frame dimension speculation */
    switch(adecClient->outPortParams->colorFormat)
    {
      case OMX_COLOR_FormatYUV420Planar:
      case OMX_COLOR_FormatYUV420SemiPlanar:

        adecClient->outPortParams->cmnOutParams.bufferOutSize =
                      ((adecClient->outPortParams->nWidth *\
                        adecClient->outPortParams->nHeight * 3)
                        >> 1);

        break;

      case OMX_COLOR_FormatYUV422Planar:
      case OMX_COLOR_FormatYCbYCr:

        adecClient->outPortParams->cmnOutParams.bufferOutSize =
                      (adecClient->outPortParams->nWidth *\
                      adecClient->outPortParams->nHeight * 2);

        break;

      default:

        PRINT(PRINT_MUST, "Undefined chroma format. Setting o/p buffer size \
  according to 420P format.\n");
        adecClient->outPortParams->cmnOutParams.bufferOutSize =
                      ((adecClient->outPortParams->nWidth *\
                        adecClient->outPortParams->nHeight * 3)
                        >> 1);

        break;

    } // switch(adecClient->outPortParams->colorFormat)

   // adecClient->outPortParams->cmnOutParams.bufferOutSize = ((((adecClient->outPortParams->nWidth + (2*OMTB_ADEC_PADX) + 127) & 0xFFFFFF80) *  
	//                                                               ((adecClient->outPortParams->nHeight + (4*OMTB_ADEC_PADY))) * 3) >> 1);
	adecClient->outPortParams->cmnOutParams.bufferOutSize = 8192;
  }
  else
  {
    adecClient->outPortParams->cmnOutParams.bufferOutSize =
                                               adecConfig->sBasicParams.outBufSize;
  }


 OMTB_SetHeader( adecClient->outPortParams->cmnOutParams.pOutPortDef,
                  sizeof(OMX_PARAM_PORTDEFINITIONTYPE));

  /* Set the component's OMX_PARAM_PORTDEFINITIONTYPE structure (output) */

  adecClient->outPortParams->cmnOutParams.pOutPortDef->nPortIndex         = OMTB_ADEC_OUTPUT_PORT_IDX;
  
  /* Get the default values of output port params set by the decoder*/
  err = OMX_GetParameter( adecClient->omtbPvt.handle,
                          OMX_IndexParamPortDefinition,
                          adecClient->outPortParams->cmnOutParams.pOutPortDef);

  if(OMX_ErrorNone != err)
  {
	OMTB_OmxReturnStatus(err);
	return err;
  }
  adecClient->outPortParams->cmnOutParams.pOutPortDef->eDir               = OMX_DirOutput;

  adecClient->outPortParams->cmnOutParams.pOutPortDef->nBufferCountActual =
                                  adecClient->outPortParams->cmnOutParams.numOutBuf;
  adecClient->outPortParams->cmnOutParams.pOutPortDef->nBufferCountMin    = 1;

  adecClient->outPortParams->cmnOutParams.pOutPortDef->nBufferSize        =
                                  adecClient->outPortParams->cmnOutParams.bufferOutSize;
  adecClient->outPortParams->cmnOutParams.pOutPortDef->bEnabled           = OMX_FALSE;
  adecClient->outPortParams->cmnOutParams.pOutPortDef->bPopulated         = OMX_FALSE;
  adecClient->outPortParams->cmnOutParams.pOutPortDef->eDomain            =
                                  OMX_PortDomainAudio;
  adecClient->outPortParams->cmnOutParams.pOutPortDef->bBuffersContiguous = OMX_FALSE;
  adecClient->outPortParams->cmnOutParams.pOutPortDef->nBufferAlignment   = 32;

  /* OMX_AUDIO_PORTDEFINITION values for output port */
  adecClient->outPortParams->cmnOutParams.pOutPortDef->format.audio.cMIMEType  = "PCM";
  adecClient->outPortParams->cmnOutParams.pOutPortDef->format.audio.pNativeRender  = NULL;
  adecClient->outPortParams->cmnOutParams.pOutPortDef->format.audio.bFlagErrorConcealment = OMX_FALSE;
  adecClient->outPortParams->cmnOutParams.pOutPortDef->format.audio.eEncoding = OMX_AUDIO_CodingUnused;
  
  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;

  /*Set the OutPort Definition*/
  err = OMX_SetParameter( adecClient->omtbPvt.handle,
                          OMX_IndexParamPortDefinition,
                          adecClient->outPortParams->cmnOutParams.pOutPortDef);

  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_SetParameter");

  if(OMX_ErrorNone != err)
  {
    OMTB_OmxReturnStatus(err);
    return err;
  }

  PRINT(PRINT_FUNCTION_NAME, "Leaving <Function , instance #> : <%s , %d>\n",
                              __FUNCTION__, (int)adecClient->omtbPvt.instanceNo);

  return err;
}


/******************************************************************************\
 *      ADEC_SetPortDefinition Function Definition
\******************************************************************************/
/**
 *
 *  @brief    Set i/o port params.
 *
 *  @param in:
 *            adecClient:Pointer to appPrivateType structure
 *
 *  @param Out:
 *            None
 *
 *  @return   OMX_ERRORTYPE - OMX std return/error code
 *
 */

OMX_ERRORTYPE ADEC_SetPortDefinition(void* thisClient)
{

  OMX_ERRORTYPE err = OMX_ErrorNone;
  OMX_PORT_PARAM_TYPE portInit;
  OMTB_ADEC_PRIVATE* adecClient;
  OMTB_OMX_API_TIMING_VAR_DECL;

  adecClient = (OMTB_ADEC_PRIVATE*)thisClient;

  /* validate the function arguments */
  ASSERT(NULL != adecClient);

  PRINT(PRINT_FUNCTION_NAME, "Entering <Function , instance #> : <%s , %d>\n",
                              __FUNCTION__, (int)adecClient->omtbPvt.instanceNo);
  
  /* Set the component's OMX_PARAM_PORTDEFINITIONTYPE structure (input) */
  OMTB_SetHeader(&portInit,sizeof(OMX_PORT_PARAM_TYPE));
  portInit.nPorts = 2;
  portInit.nStartPortNumber = 0;
#if 1
  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;

  /* Initialize the Port*/
  err = OMX_SetParameter( adecClient->omtbPvt.handle,
                          OMX_IndexParamAudioInit,
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
  err = ADEC_SetInputPortDefinition(adecClient);
  if(OMX_ErrorNone != err)
  {
    PRINT(PRINT_ERR_MSG, "Error in setting i/p port params\n");
    OMTB_OmxReturnStatus(err);
  }

  /* set the o/p port params */
  err = ADEC_SetOutputPortDefinition(adecClient);
  if(OMX_ErrorNone != err)
  {
    PRINT(PRINT_ERR_MSG, "Error in setting o/p port params\n");
    OMTB_OmxReturnStatus(err);
  }

  PRINT(PRINT_FUNCTION_NAME, "Leaving <Function , instance #> : <%s , %d>\n",
                              __FUNCTION__, (int)adecClient->omtbPvt.instanceNo);

  return err;
}


/******************************************************************************\
 *      ADEC_ChangePortSettings Function Definition
\******************************************************************************/
/**
 *
 *  @brief    Change params for output port for decoder.
 *
 *  @param in:
 *            adecClient:Pointer to appPrivateType structure
 *
 *  @param Out:
 *            None
 *
 *  @return   OMX_ERRORTYPE - OMX std return/error code
 *
 */
#if 0
static OMX_ERRORTYPE ADEC_ChangePortSettings(OMTB_ADEC_PRIVATE* adecClient)
{
//  TIMM_OSAL_ERRORTYPE retval;
  OMX_ERRORTYPE err = OMX_ErrorNone;

  ASSERT(NULL != adecClient);

  PRINT(PRINT_FUNCTION_NAME, "Entering <Function , instance #> : <%s , %d>\n",
                                __FUNCTION__, (int)adecClient->omtbPvt.instanceNo);

  /* disable the port */
  err = OMX_SendCommand(adecClient->omtbPvt.handle,
                        OMX_CommandPortDisable,
                        adecClient->outPortParams->cmnOutParams.pOutPortDef->nPortIndex,
                        NULL);
  if(OMX_ErrorNone != err)
  {
    PRINT(PRINT_ERR_MSG, "%s: Error from SendCommand OMX_CommandPortDisable\n", __FUNCTION__);
    return err;
  }

  /* release output port buffers */
  err = ADEC_FreeOutputResources(adecClient);

  if(OMX_ErrorNone != err)
  {
    PRINT(PRINT_ERR_MSG, "Error in Buffer release for o/p port\n");
    OMTB_OmxReturnStatus(err);
    return err;
  }

  /* get the updated port settings */
  err = OMX_GetParameter(adecClient->omtbPvt.handle,
                     OMX_IndexParamPortDefinition,
                     adecClient->outPortParams->cmnOutParams.pOutPortDef);
  if(OMX_ErrorNone != err)
  {
    PRINT(PRINT_ERR_MSG, "%s: Error in OMX_GetParameter\n", __FUNCTION__);
    return err;
  }

  err = OMX_SendCommand(adecClient->omtbPvt.handle,
                        OMX_CommandPortEnable,
                        adecClient->outPortParams->cmnOutParams.pOutPortDef->nPortIndex,
                        NULL);
  if(OMX_ErrorNone != err)
  {
    PRINT(PRINT_ERR_MSG, "%s: Error in OMX_SendCommand:OMX_CommandPortEnable\n", __FUNCTION__);
    return err;
  }

/*  retval = TIMM_OSAL_ClearPipe(adecClient->outPortParams->cmnOutParams.opBufPipe);
  if (TIMM_OSAL_ERR_NONE != retval)
  {
    PRINT(PRINT_ERR_MSG, "%s: Error in clearing Output Pipe!\n", __FUNCTION__);
    err = OMX_ErrorNotReady;
    return err;
  }
*/
  /* allocate i/p port buffers */
  err = ADEC_AllocateOutputResources(adecClient);

  if(OMX_ErrorNone != err)
  {
    PRINT(PRINT_ERR_MSG, "Error in Buffer allocation for o/p port\n");
    OMTB_OmxReturnStatus(err);
    return err;
  }

  /* use o/p buffers */
  err = ADEC_UseInitialOutputResources(adecClient);

  if(OMX_ErrorNone != err)
  {
    PRINT(PRINT_ERR_MSG, "Error in sending initial buffers to o/p port\n");
    OMTB_OmxReturnStatus(err);
    return err;
  }

  PRINT(PRINT_FUNCTION_NAME, "Leaving <Function , instance #> : <%s , %d>\n",
                                  __FUNCTION__, (int)adecClient->omtbPvt.instanceNo);

  return err;
}
#endif

/******************************************************************************\
 *      ADEC_GetStructIdx Function Definition
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

OmtbRet ADEC_GetStructIdx(
  char *indexStr,
  unsigned int template,unsigned int instanceNo,
  unsigned int portIdx,
  unsigned int *nConfigIndex,
  void **pCompCfgStruct)
{
  unsigned int enumCount = 0;
  char channelName[OMX_MAX_STRINGNAME_SIZE];         /* Capture channel name */

  /* Use the specified template structure */
  adecConfig = (OMTB_ADEC_CONFIG_PARAMS*)
                     &(omtbCfgTemplate[template]->adecTemplate);

  /* Get the corresponding string for enum values from enum table
     Set structure index
     Set structure pointer
     Set port index for which parameter to be updated
     Set structure header info */
  while(strcmp(enumTblAdecCfgParamIdx[enumCount].name , ""))
  {
    if(0 == strcmp(enumTblAdecCfgParamIdx[enumCount].name,
                   indexStr))
    {
      switch(enumTblAdecCfgParamIdx[enumCount].value)
      {
        case OMX_TI_IndexConfigChannelName:
          {
            *nConfigIndex   = enumTblAdecCfgParamIdx[enumCount].value;
            *pCompCfgStruct = &adecConfig->sChannelName;
            adecConfig->sChannelName.nPortIndex = 1;
/* FIXME:  To support backword compatability with the older omtb scripts,
           the following code has not been removed, 
*/		   
//            if(!strcmp("NULL", vpssVfccConfig->sChannelName.cChannelName))			
            {
            snprintf(channelName, OMX_MAX_STRINGNAME_SIZE, "FQ_DECOUT_%d",
                     instanceNo);
            channelName[OMX_MAX_STRINGNAME_SIZE - 1] = '\0';
 
			DOMX_UTL_Strncpy ( ( char * ) adecConfig->sChannelName.cChannelName, channelName,
					  sizeof ( adecConfig->sChannelName.cChannelName ) );
            }
            OMTB_SetHeader( *pCompCfgStruct,
                            sizeof(OMX_CONFIG_CHANNELNAME));
          }
          return OMTB_SUCCESS;

        case OMX_TI_IndexParamBuffMemType:
          {
            *nConfigIndex   = enumTblAdecCfgParamIdx[enumCount].value;
            *pCompCfgStruct = &adecConfig->sMemTypeCfg;
             adecConfig->sMemTypeCfg.nPortIndex = portIdx;
             OMTB_SetHeader( *pCompCfgStruct,
			                 sizeof(OMX_PARAM_BUFFER_MEMORYTYPE));
          }
  		  return OMTB_SUCCESS;

  		case OMX_IndexParamCompBufferSupplier:
		  {
			*nConfigIndex   = enumTblAdecCfgParamIdx[enumCount].value;
			*pCompCfgStruct = &adecConfig->sBufSupplier;
			 adecConfig->sBufSupplier.nPortIndex = portIdx;
			 OMTB_SetHeader( *pCompCfgStruct,
							 sizeof(OMX_PARAM_BUFFERSUPPLIERTYPE));
		  }
  		  return OMTB_SUCCESS;

        case OMX_IndexParamAudioPortFormat:
		  {
			*nConfigIndex   = enumTblAdecCfgParamIdx[enumCount].value;
			*pCompCfgStruct = &adecConfig->sAudioPortFormat;
			 adecConfig->sAudioPortFormat.nPortIndex = portIdx;
             OMTB_SetHeader( *pCompCfgStruct,
							 sizeof(OMX_AUDIO_PARAM_PORTFORMATTYPE));
		  }
  		  return OMTB_SUCCESS;

       	case OMX_TI_IndexParamFileModeType:
		  {
			*nConfigIndex   = enumTblAdecCfgParamIdx[enumCount].value;
			*pCompCfgStruct = &adecConfig->sFileModeCfg;
			 adecConfig->sFileModeCfg.nPortIndex = portIdx;
			 OMTB_SetHeader( *pCompCfgStruct,
							 sizeof(OMX_PARAM_FILEMODE_TYPE));
		  }
  		  return OMTB_SUCCESS;

       	case OMX_IndexParamAudioInit:
		  {
			*nConfigIndex   = enumTblAdecCfgParamIdx[enumCount].value;
			*pCompCfgStruct = &adecConfig->sPortInit;
			 OMTB_SetHeader( *pCompCfgStruct,
							 sizeof(OMX_PORT_PARAM_TYPE));
		  }
		  return OMTB_SUCCESS;

		case OMX_TI_IndexParamCompPortNotifyType:
          {
			*nConfigIndex   = enumTblAdecCfgParamIdx[enumCount].value;
			*pCompCfgStruct = &adecConfig->sCompPortNotifyType;
            adecConfig->sCompPortNotifyType.nPortIndex = portIdx;
            OMTB_SetHeader( *pCompCfgStruct,
                            sizeof(OMX_PARAM_COMPPORT_NOTIFYTYPE));
		  }
		  return OMTB_SUCCESS;	
		  
  		case OMX_IndexParamPortDefinition:
	      {
		    *nConfigIndex   = enumTblAdecCfgParamIdx[enumCount].value;
		    *pCompCfgStruct = &adecConfig->sPortDefType;
            adecConfig->sPortDefType.nPortIndex = portIdx;			
		    OMTB_SetHeader( *pCompCfgStruct,
			   			    sizeof(OMX_PARAM_PORTDEFINITIONTYPE));
	      }
	      return OMTB_SUCCESS;
		  
       	default:
          {
            return OMTB_FAIL;
          }

      } // switch(enumTblAdecCfgParamIdx[enumCount].value)

    } // if(0 == strcmp(enumTblAdecCfgParamIdx[enumCount].name, ...

    enumCount++;
  }

  return OMTB_SUCCESS;
}


/******************************************************************************\
 *      ADEC_FuncTsk Thread Definition
\******************************************************************************/
/**
 *
 *  @brief    This is a thread which invokes during func command
 *
 *  @param in:
 *            void * - Thread args count
 *
 *            void *threadsArg - Pointer to thread arg structure
 *
 *  @return   None
 *
 */

void ADEC_FuncTsk(void *argc, void *threadsArg)
{
  int threadRes = TIMM_OSAL_ERR_NONE;
  OMX_ERRORTYPE err = OMX_ErrorNone;
  OMTB_ADEC_PRIVATE* adecClient = NULL;
  OMTB_DATA_THREAD_ARG *funcDataThreadArg = (OMTB_DATA_THREAD_ARG *)threadsArg;
  unsigned int instanceNo = 0;
  TIMM_OSAL_ERRORTYPE bReturnStatus = TIMM_OSAL_ERR_NONE;  
  OMTB_OMX_API_TIMING_VAR_DECL;

  /* thread argument validation */
  ASSERT(NULL != threadsArg);
  ASSERT(NULL != funcDataThreadArg->adecClient);

  adecClient = funcDataThreadArg->adecClient;

  PRINT(PRINT_MUST, "Entering <Thread , instance #> : <%s , %d>\n",
                     __FUNCTION__, (int)adecClient->omtbPvt.instanceNo);

  PRINT(PRINT_SIMPLE_MESSAGE, "\nbufferOutSize:%d\n",\
        (int)adecClient->outPortParams->cmnOutParams.bufferOutSize);

  /* Set the port params */
  err = ADEC_SetPortDefinition(adecClient);

  if(OMX_ErrorNone != err)
  {
    OMTB_OmxReturnStatus(err);
  }

  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;

  /* send command to component to go to idle state */
  err = OMX_SendCommand(adecClient->omtbPvt.handle,
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
  err = OMTB_ClientAllocateResources(adecClient);

  if(OMX_ErrorNone != err)
  {
    OMTB_OmxReturnStatus(err);
  }

  /* waiting for component to go to idle state */
  bReturnStatus = TIMM_OSAL_SemaphoreObtain(adecClient->omtbPvt.eventSem, OMTB_SEM_TIMEOUT);

  if(TIMM_OSAL_WAR_TIMEOUT == bReturnStatus)
  {
    OMTB_OmxReturnStatus(OMX_ErrorTimeout);  
  }
  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;

  /* send command to component to go to executing state */
  err = OMX_SendCommand(adecClient->omtbPvt.handle,
                        OMX_CommandStateSet,
                        OMX_StateExecuting,
                        NULL);

  if(OMX_ErrorNone != err)
  {
    OMTB_OmxReturnStatus(err);
  }

  /* waiting for component to go to executing state */
  bReturnStatus = TIMM_OSAL_SemaphoreObtain(adecClient->omtbPvt.eventSem, OMTB_SEM_TIMEOUT);

  if(TIMM_OSAL_WAR_TIMEOUT == bReturnStatus)
  {
    OMTB_OmxReturnStatus(OMX_ErrorTimeout);  
  }
  
  /* Update the func create count */
  ADEC_funcCreateCount++;
  PRINT(PRINT_MUST, "%s: FUNC Create Count: %u\n", __FUNCTION__,
                    (unsigned int) ADEC_funcCreateCount);

  /* Update the data streaming thread arguments */
  strmThreadArg[adecClient->omtbPvt.instanceNo].adecClient = adecClient;

  /* Create input data read thread */
  threadRes = TIMM_OSAL_CreateTask(
                    (void *)&adecClient->inPortParams->cmnInParams.inDataStrmThrdId,
                    (TIMM_OSAL_TaskProc)OMTB_InputDataRead,
                    0,
                    &strmThreadArg[adecClient->omtbPvt.instanceNo],
                    OMTB_ADEC_TSK_STACK_SIZE,
                    OMTB_ADEC_GROUP_PRIORITY,
                    (signed char*)"ADEC_DATA_IN_TSK");

  if(TIMM_OSAL_ERR_NONE != threadRes)
  {
    PRINT(PRINT_ERR_MSG,
          "Unable to start audio decode input data read thread\n");
  }

  /* Create output data write thread */
  threadRes = TIMM_OSAL_CreateTask(
                    (void *)&adecClient->outPortParams->cmnOutParams.outDataStrmThrdId,
                    (TIMM_OSAL_TaskProc)OMTB_OutputDataWrite,
                    0,
                    &strmThreadArg[adecClient->omtbPvt.instanceNo],
                    OMTB_ADEC_TSK_STACK_SIZE,
                    OMTB_ADEC_GROUP_PRIORITY,
                    (signed char*)"ADEC_DATA_OUT_TSK");

  if(TIMM_OSAL_ERR_NONE != threadRes)
  {
    PRINT(PRINT_ERR_MSG,
          "Unable to start audio decode output data write thread\n");
  }


  /* Wait for EOS */
  bReturnStatus = TIMM_OSAL_SemaphoreObtain(adecClient->eofSem, OMTB_SEM_TIMEOUT);

  if(TIMM_OSAL_WAR_TIMEOUT == bReturnStatus)
  {
    OMTB_OmxReturnStatus(OMX_ErrorTimeout);  
  }
  
  PRINT(DEFAULT_MESSAGES, "The execution of the audio decoding\
                           process is terminated\n");

  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;

  /* state change of component from executing to idle */
  err = OMX_SendCommand(adecClient->omtbPvt.handle,
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
  bReturnStatus = TIMM_OSAL_SemaphoreObtain(adecClient->omtbPvt.eventSem, OMTB_SEM_TIMEOUT);

  if(TIMM_OSAL_WAR_TIMEOUT == bReturnStatus)
  {
    OMTB_OmxReturnStatus(OMX_ErrorTimeout);  
  }  

  PRINT(DEFAULT_MESSAGES, "State transitioned to Idle\n");

  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;

  /* sending command to component to go to loaded state */
  err = OMX_SendCommand(adecClient->omtbPvt.handle,
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
  adecClient->outPortParams->cmnOutParams.flagEos = OMX_FALSE;
  adecClient->inPortParams->cmnInParams.flagInputEos = OMX_FALSE;

  /* Function to reelase the resources allocated by component */
  err = OMTB_ClientFreeResources(adecClient);

  if(OMX_ErrorNone != err)
  {
    OMTB_OmxReturnStatus(err);
  }

  /*wait for event handler to report completion of loaded command */
  bReturnStatus = TIMM_OSAL_SemaphoreObtain(adecClient->omtbPvt.eventSem, OMTB_SEM_TIMEOUT);

  if(TIMM_OSAL_WAR_TIMEOUT == bReturnStatus)
  {
    OMTB_OmxReturnStatus(OMX_ErrorTimeout);  
  }
  
  PRINT(PRINT_SIMPLE_MESSAGE, "State transitioned to loaded\n");

  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;

  /* Delete the component instance */
  err = OMX_FreeHandle(adecClient->omtbPvt.handle);

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
    adecClient->omtbPvt.handle = NULL;
    PRINT(PRINT_MUST,
          "\r      \n\nOMTB-Deleted Adec Instance #: %d\n\n",
          (int) adecClient->omtbPvt.instanceNo);
    omtbClass[OMTB_ADEC_CLASS].handle[adecClient->omtbPvt.instanceNo] = NULL;
  }

  PRINT(PRINT_SIMPLE_MESSAGE, "audio dec freed\n");

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
  adecClient->omtbPvt.flagThrCreated = OMX_FALSE;

  /* save the instance no to local variable */
  instanceNo = adecClient->omtbPvt.instanceNo;

  /* Reelase the memory allocated for app pvt data */
  OMTB_FreeMemory(adecClient);

  /* Update the func delete count */
  ADEC_funcDeleteCount++;

  PRINT(PRINT_MUST, "%s: FUNC Delete Count: %u\n", __FUNCTION__,
                    (unsigned int) ADEC_funcDeleteCount);

  PRINT(PRINT_MUST, "Leaving <Thread , instance #> : <%s , %d>\n",
                     __FUNCTION__, (int)instanceNo);

  /* exit the thread */
  TIMM_OSAL_ExitTask(
      omtbClass[OMTB_ADEC_CLASS].execThreadId[instanceNo],
      NULL);
}

/******************************************************************************\
 *      ADEC_SetTemplateDefVal Function Definition
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

MX_Result ADEC_SetTemplateDefVal(OMTB_TEMPLATE_INFO *pTemplate)
{
  OMTB_ADEC_CONFIG_PARAMS *audDecCfg = NULL;

  /* param validation */
  if(NULL == pTemplate)
  {
    PRINT(PRINT_ERR_MSG, "%s: Memory for Template not allocated\n",__FUNCTION__);
    return ERR_INVNAME;
  }

  /* ADEC configuration */
  audDecCfg = &pTemplate->adecTemplate;

  strcpy(audDecCfg->sBasicParams.inputFile, "adec_sample.mpeg2");
  strcpy(audDecCfg->sBasicParams.outputFile,"adec_test.yuv");
  strcpy(audDecCfg->sBasicParams.compName,   OMTB_ADEC_COMPONENT_NAME);
  
  audDecCfg->sBasicParams.dataOutPutMode   = OMTB_FILE;
  audDecCfg->sBasicParams.dataInPutMode    = OMTB_FILE;
  audDecCfg->sBasicParams.numInBuf         = OMTB_ADEC_NUM_IN_BUFS;
  audDecCfg->sBasicParams.numOutBuf        = OMTB_ADEC_NUM_OUT_BUFS;
  audDecCfg->sBasicParams.inBufAlignment   = 0;
  audDecCfg->sBasicParams.outBufAlignment  = 0;
  audDecCfg->sBasicParams.inBufSize        = OMTB_ADEC_MAX_INBUFF_SIZE;
  audDecCfg->sBasicParams.outBufSize       = 0;
  audDecCfg->sBasicParams.inBufSzFlag      = OMX_FALSE;
  audDecCfg->sBasicParams.outBufSzFlag     = OMX_FALSE;
  audDecCfg->sBasicParams.inBufContiguous  = TIMM_OSAL_TRUE;
  audDecCfg->sBasicParams.outBufContiguous = TIMM_OSAL_TRUE;
  audDecCfg->sBasicParams.flagUseInBuffer  = OMX_TRUE;
  audDecCfg->sBasicParams.flagUseOutBuffer = OMX_FALSE;
  audDecCfg->sBasicParams.compressionFormat = OMX_AUDIO_CodingAAC;
  audDecCfg->sBasicParams.fileReset        = OMX_TRUE;
  
  audDecCfg->sMemTypeCfg.eBufMemoryType = OMX_BUFFER_MEMORY_DEFAULT;

  audDecCfg->sBufSupplier.eBufferSupplier =  OMX_BufferSupplyUnspecified;

  audDecCfg->sFileModeCfg.bEnableFileMode = OMX_FALSE;

  audDecCfg->sPortInit.nPorts           = OMTB_ADEC_DEF_NO_OF_PORTS;
  audDecCfg->sPortInit.nStartPortNumber = OMTB_ADEC_DEF_START_PORT_NUM;
  
  audDecCfg->sAudioPortFormat.eEncoding = OMX_AUDIO_CodingAAC;
  
  audDecCfg->sCompPortNotifyType.eNotifyType = OMX_NOTIFY_TYPE_ALWAYS;
  
  audDecCfg->sPortDefType.eDir                               = OMX_DirInput;
  audDecCfg->sPortDefType.nBufferCountActual                 = OMTB_ADEC_NUM_IN_BUFS;
  audDecCfg->sPortDefType.nBufferCountMin                    = 1; 
  audDecCfg->sPortDefType.nBufferSize                        = OMTB_ADEC_MAX_INBUFF_SIZE;    
  audDecCfg->sPortDefType.bEnabled                           = OMX_FALSE; 
  audDecCfg->sPortDefType.bPopulated                         = OMX_FALSE; 
  audDecCfg->sPortDefType.eDomain                            = OMX_PortDomainAudio;
  audDecCfg->sPortDefType.bBuffersContiguous                 = OMX_FALSE;
  audDecCfg->sPortDefType.nBufferAlignment                   = 0;
  audDecCfg->sPortDefType.format.audio.cMIMEType             = "ADEC";
  audDecCfg->sPortDefType.format.audio.pNativeRender         = NULL;
  audDecCfg->sPortDefType.format.audio.bFlagErrorConcealment = OMX_FALSE;
  audDecCfg->sPortDefType.format.audio.eEncoding             = OMX_AUDIO_CodingAAC;
  
  strcpy(audDecCfg->sChannelName.cChannelName, "NULL");
  
  return ERR_NOERR;
}

/******************************************************************************\
 *      ADEC_ClassInit Function Definition
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
OMX_ERRORTYPE ADEC_ClassInit(OMTB_CLIENT_PRIVATE* thisClient)
{
  OmtbRet err = OMTB_SUCCESS;
  
  PRINT(PRINT_FUNCTION_NAME, "Entering <Function> : <%s>\n",
                              __FUNCTION__);
							  
  /* no of input / output ports */
  thisClient->omtbPvt.numInport  = OMTB_ADEC_MAX_IN_PORT;
  thisClient->omtbPvt.numOutport = OMTB_ADEC_MAX_OUT_PORT;
  thisClient->omtbPvt.startOutportIndex = OMTB_ADEC_MAX_IN_PORT;
  
  thisClient->omtbPvt.outputDataWriteTask = OMTB_OutputDataWrite;
  thisClient->omtbPvt.inputDataReadTask = OMTB_InputDataRead;

  /* Function pointer for GetStructIdx */
  thisClient->omtbPvt.fpGetStructIdx = ADEC_GetStructIdx; 
  thisClient->omtbPvt.fpSetBufferSize = ADEC_SetBufferSize;
  thisClient->omtbPvt.fpSetPortDefinition = ADEC_SetPortDefinition;
	
  thisClient->omtbPvt.numFileInBufs = (OMTB_CLIENT_MAX_NUM_FILE_IN_BUFS * 4);
  thisClient->omtbPvt.numFileOutBufs = OMTB_CLIENT_MAX_NUM_FILE_OUT_BUFS;
  
  thisClient->omtbPvt.readSize       = MPEG2PARSER_READSIZE;
  thisClient->omtbPvt.writeSize      = OMTB_ADEC_MAX_OUTBUFF_SIZE; 	 
  
  thisClient->omtbPvt.eClassType = OMTB_ADEC_CLASS;
	
  PRINT(PRINT_FUNCTION_NAME, "Leaving <Function> : <%s>\n",
                              __FUNCTION__);  
  return (err);							  
}
/*----------------------------- end of file ----------------------------------*/
