/*
 * omtbHDVPSSVfpcDei.c
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

/* OMX standard header files */
#include "OMX_Core.h"
#include "OMX_Component.h"
#include "OMX_Types.h"
#include "OMX_TI_Common.h"
#include "OMX_TI_Index.h"
#include "omx_vfpc.h"
#include "domx_util.h"

//#include "omx_vfpc_priv.h"

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

static OMX_CALLBACKTYPE VPSSVFPCDEI_Callback = {
  OMTB_ClientEventHandler,     /* Event handler callback */
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
extern OMTB_TEMPLATE_INFO *omtbCfgTemplate[OMTB_MAX_INS];

/* global semaphote used for proprietary tunneling */
extern void *gOmtbEofSem;
/******************************************************************************\
 *      Globals
\******************************************************************************/

/* Pointer to VFPC config params */
OMTB_VPSS_VFPC_DEI_CONFIG_PARAMS *vpssVfpcDeiConfig = NULL;


/******************************************************************************\
 *      Static Globals
\******************************************************************************/

static OMX_U32 VPSSVFPCDEI_funcCreateCount = 0;  /* Func create count */
static OMX_U32 VPSSVFPCDEI_apiCreateCount = 0;   /* API create count */

static OMX_U32 VPSSVFPCDEI_funcDeleteCount = 0;  /* Func delete count */
static OMX_U32 VPSSVFPCDEI_apiDeleteCount = 0;   /* API delete count */

/* Enum Entry for Supported cfg param indexs */

PRIVATE MX_DBG_ENUM_ENTRY_T enumTblVpssVfpcDeiCfgParamIdx[] =
{
  /* ADD ENTRIES HERE for SetConfig/SetParam/GetConfig/GetParam */
  {"OMX_TI_IndexConfigChannelName",       OMX_TI_IndexConfigChannelName,        ""},
  {"OMX_TI_IndexConfigChannelGroupInfo",  OMX_TI_IndexConfigChannelGroupInfo,   ""},
  {"OMX_TI_IndexConfigVidChResolution",   OMX_TI_IndexConfigVidChResolution,    ""},
  {"OMX_TI_IndexConfigAlgEnable",         OMX_TI_IndexConfigAlgEnable,          ""},
  {"OMX_TI_IndexParamCompPortNotifyType", OMX_TI_IndexParamCompPortNotifyType,  ""},
  {"OMX_IndexParamCompBufferSupplier",    OMX_IndexParamCompBufferSupplier,     ""},
  {"OMX_TI_IndexParamBuffMemType",        OMX_TI_IndexParamBuffMemType,         ""},
  {"OMX_TI_IndexConfigSubSamplingFactor", OMX_TI_IndexConfigSubSamplingFactor,  ""},
  {"OMX_TI_IndexParamVFPCNumChPerHandle", OMX_TI_IndexParamVFPCNumChPerHandle,  ""},
  {"OMX_IndexParamVideoInit",             OMX_IndexParamVideoInit,              ""},
  {"OMX_IndexParamPortDefinition",          OMX_IndexParamPortDefinition,       ""},   
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
 *      VPSSVFPCDEI_SetInputPortDefinition Function Definition
\******************************************************************************/
/**
 *
 *  @brief    Set i/p port params.
 *
 *  @param in:
 *            vpssVfpcDeiClient:Pointer to appPrivateType structure
 *
 *  @param Out:
 *            None
 *
 *  @return   OMX_ERRORTYPE - OMX std return/error code
 *
 */

OMX_ERRORTYPE VPSSVFPCDEI_SetInputPortDefinition(OMTB_VPSS_VFPC_DEI_PRIVATE* vpssVfpcDeiClient)
{

  OMX_ERRORTYPE err = OMX_ErrorNone;
  OMTB_OMX_API_TIMING_VAR_DECL;
  unsigned int i = 0;
  OMTB_CLIENT_INPORT_PARAMS *inPortParamsPtr = NULL;

  /* validate the function arguments */
  ASSERT(NULL != vpssVfpcDeiClient);

  PRINT(PRINT_FUNCTION_NAME, "Entering <Function , instance #> : <%s , %d>\n",
                              __FUNCTION__, (int)vpssVfpcDeiClient->omtbPvt.instanceNo);

  for (i =0 ; i < vpssVfpcDeiClient->omtbPvt.numInport ; i++)
  {
  inPortParamsPtr = vpssVfpcDeiClient->inPortParams + i; 
	
  //inPortParamsPtr->cmnInParams.bufferInSize   = OMTB_VPSS_VFPC_DEI_MAX_INBUFF_SIZE;

  /* Set the component's OMX_PARAM_PORTDEFINITIONTYPE structure (input) */
  OMTB_SetHeader( inPortParamsPtr->cmnInParams.pInPortDef,
                  sizeof(OMX_PARAM_PORTDEFINITIONTYPE));


    inPortParamsPtr->cmnInParams.pInPortDef->nPortIndex          =
                                  (OMX_VFPC_INPUT_PORT_START_INDEX + i);

    /* API entry time calculation macro */
    OMTB_OMX_API_ENTRY_TIME_CALC;

    /*Get the inPort Definition*/
    err = OMX_GetParameter( vpssVfpcDeiClient->omtbPvt.handle,
                            OMX_IndexParamPortDefinition,
                            inPortParamsPtr->cmnInParams.pInPortDef);

    /* API exit time calculation macro */
    OMTB_OMX_API_EXIT_TIME_CALC("OMX_GetParameter");


    inPortParamsPtr->cmnInParams.pInPortDef->eDir                = OMX_DirInput;

    inPortParamsPtr->cmnInParams.pInPortDef->nBufferCountActual  =
                                  inPortParamsPtr->cmnInParams.numInBuf;
    inPortParamsPtr->cmnInParams.pInPortDef->nBufferCountMin     = 1;
#if 1
      inPortParamsPtr->cmnInParams.pInPortDef->nBufferSize         =
                                      inPortParamsPtr->cmnInParams.bufferInSize;
#endif									  
    inPortParamsPtr->cmnInParams.pInPortDef->bEnabled            = OMX_FALSE;
    inPortParamsPtr->cmnInParams.pInPortDef->bPopulated          = OMX_FALSE;
    inPortParamsPtr->cmnInParams.pInPortDef->eDomain             =
                                    OMX_PortDomainVideo;
    inPortParamsPtr->cmnInParams.pInPortDef->bBuffersContiguous  =
                                    (OMX_BOOL)inPortParamsPtr->cmnInParams.inBufContiguous;
    inPortParamsPtr->cmnInParams.pInPortDef->nBufferAlignment    =
    								inPortParamsPtr->cmnInParams.inBufAlignment;
	inPortParamsPtr->cmnInParams.pInPortDef->format.video.nFrameWidth =
                                  inPortParamsPtr->nWidth;
	inPortParamsPtr->cmnInParams.pInPortDef->format.video.nFrameHeight =
                                  inPortParamsPtr->nHeight;

    inPortParamsPtr->cmnInParams.pInPortDef->format.video.eCompressionFormat =
                                    OMX_VIDEO_CodingUnused;
    inPortParamsPtr->cmnInParams.pInPortDef->format.video.eColorFormat =
                                    inPortParamsPtr->colorFormat;

    if ((inPortParamsPtr->cmnInParams.pInPortDef->format.video.eColorFormat ==
	                                                            OMX_COLOR_FormatYUV420Planar)       ||
        (inPortParamsPtr->cmnInParams.pInPortDef->format.video.eColorFormat ==
		                                                        OMX_COLOR_FormatYUV420PackedPlanar) ||
        (inPortParamsPtr->cmnInParams.pInPortDef->format.video.eColorFormat ==
		                                                        OMX_COLOR_FormatYUV420SemiPlanar)   ||
        (inPortParamsPtr->cmnInParams.pInPortDef->format.video.eColorFormat ==
		                                                        OMX_COLOR_FormatYUV420PackedSemiPlanar))
    {
      inPortParamsPtr->cmnInParams.pInPortDef->format.video.nStride =
                      inPortParamsPtr->cmnInParams.pInPortDef->format.video.nFrameWidth;
    }
#if 1	
    else
    if ((inPortParamsPtr->cmnInParams.pInPortDef->format.video.eColorFormat ==
	                                                            OMX_COLOR_FormatYCbYCr)       ||
        (inPortParamsPtr->cmnInParams.pInPortDef->format.video.eColorFormat ==
		                                                        OMX_COLOR_FormatYCrYCb) ||
        (inPortParamsPtr->cmnInParams.pInPortDef->format.video.eColorFormat ==
		                                                        OMX_COLOR_FormatCbYCrY)   ||
        (inPortParamsPtr->cmnInParams.pInPortDef->format.video.eColorFormat ==
		                                                        OMX_COLOR_FormatCrYCbY))
    {
      inPortParamsPtr->cmnInParams.pInPortDef->format.video.nStride =
                      inPortParamsPtr->cmnInParams.pInPortDef->format.video.nFrameWidth * 2;
    }
#endif	
    /* API entry time calculation macro */
    OMTB_OMX_API_ENTRY_TIME_CALC;

    /*Set the inPort Definition*/
    err = OMX_SetParameter( vpssVfpcDeiClient->omtbPvt.handle,
                            OMX_IndexParamPortDefinition,
                            inPortParamsPtr->cmnInParams.pInPortDef);

    /* API exit time calculation macro */
    OMTB_OMX_API_EXIT_TIME_CALC("OMX_SetParameter");

    if(OMX_ErrorNone != err)
    {
      OMTB_OmxReturnStatus(err);
      return err;
    }
  }

  PRINT(PRINT_FUNCTION_NAME, "Leaving <Function , instance #> : <%s , %d>\n",
                              __FUNCTION__, (int)vpssVfpcDeiClient->omtbPvt.instanceNo);

  return err;
}


/******************************************************************************\
 *      VPSSVFPCDEI_SetOutputPortDefinition Function Definition
\******************************************************************************/
/**
 *
 *  @brief    Set o/p port params.
 *
 *  @param in:
 *            vpssVfpcDeiClient:Pointer to appPrivateType structure
 *
 *  @param Out:
 *            None
 *
 *  @return   OMX_ERRORTYPE - OMX std return/error code
 *
 */

OMX_ERRORTYPE VPSSVFPCDEI_SetOutputPortDefinition(OMTB_VPSS_VFPC_DEI_PRIVATE* vpssVfpcDeiClient)
{

  OMX_ERRORTYPE err = OMX_ErrorNone;
  OMTB_OMX_API_TIMING_VAR_DECL;
  unsigned int i = 0;
  OMTB_CLIENT_OUTPORT_PARAMS *outPortParamsPtr = NULL;

  /* validate the function arguments */
  ASSERT(NULL != vpssVfpcDeiClient);

  PRINT(PRINT_FUNCTION_NAME, "Entering <Function , instance #> : <%s , %d>\n",
                              __FUNCTION__, (int)vpssVfpcDeiClient->omtbPvt.instanceNo);

  /*
  if(OMX_FALSE == outPortParamsPtr->cmnOutParams.outBufSzFlag)
  {
    outPortParamsPtr->cmnOutParams.bufferOutSize =
                      (outPortParamsPtr->nWidth *\
                      outPortParamsPtr->nHeight * 2);
  }
  */

  for (i =0 ; i < vpssVfpcDeiClient->omtbPvt.numOutport ; i++)
  {
   outPortParamsPtr =  vpssVfpcDeiClient->outPortParams + i;  

  /* Set the component's OMX_PARAM_PORTDEFINITIONTYPE structure (output) */
    OMTB_SetHeader( outPortParamsPtr->cmnOutParams.pOutPortDef,
                  sizeof(OMX_PARAM_PORTDEFINITIONTYPE));
				  
    outPortParamsPtr->cmnOutParams.pOutPortDef->nPortIndex         =
                                    (vpssVfpcDeiClient->omtbPvt.startOutportIndex + i);

     /* API entry time calculation macro */
    OMTB_OMX_API_ENTRY_TIME_CALC;

    /*Get the OutPort Definition*/
    err = OMX_GetParameter( vpssVfpcDeiClient->omtbPvt.handle,
                            OMX_IndexParamPortDefinition,
                            outPortParamsPtr->cmnOutParams.pOutPortDef);

    /* API exit time calculation macro */
    OMTB_OMX_API_EXIT_TIME_CALC("OMX_GetParameter");

    outPortParamsPtr->cmnOutParams.pOutPortDef->eDir               = OMX_DirOutput;

	outPortParamsPtr->cmnOutParams.pOutPortDef->nBufferCountActual =
                                    outPortParamsPtr->cmnOutParams.numOutBuf;
    outPortParamsPtr->cmnOutParams.pOutPortDef->nBufferCountMin    = 4;

    outPortParamsPtr->cmnOutParams.pOutPortDef->nBufferSize        =
                                    outPortParamsPtr->cmnOutParams.bufferOutSize;
    outPortParamsPtr->cmnOutParams.pOutPortDef->bEnabled           = OMX_FALSE;
    outPortParamsPtr->cmnOutParams.pOutPortDef->bPopulated         = OMX_FALSE;
    outPortParamsPtr->cmnOutParams.pOutPortDef->eDomain            =
                                    OMX_PortDomainVideo;

    outPortParamsPtr->cmnOutParams.pOutPortDef->bBuffersContiguous =
                                    (OMX_BOOL)outPortParamsPtr->cmnOutParams.outBufContiguous;
    outPortParamsPtr->cmnOutParams.pOutPortDef->nBufferAlignment   =
                                    outPortParamsPtr->cmnOutParams.outBufAlignment;
	outPortParamsPtr->cmnOutParams.pOutPortDef->format.video.nFrameWidth =
                                  outPortParamsPtr->nWidth;

    outPortParamsPtr->cmnOutParams.pOutPortDef->format.video.nFrameHeight =
                                  outPortParamsPtr->nHeight;

	outPortParamsPtr->cmnOutParams.pOutPortDef->format.video.eCompressionFormat =
                                    OMX_VIDEO_CodingUnused;

	/*FIXME: Check if the value of i is an even number set the color format to 420_SP for encoder
         If i is even set to YCbYCr for VFDC display*/
    if(i & 1)
    {
      outPortParamsPtr->cmnOutParams.pOutPortDef->format.video.eColorFormat =
                                    outPortParamsPtr->colorFormat;
	}
	else
	{
  	  outPortParamsPtr->cmnOutParams.pOutPortDef->format.video.eColorFormat = OMX_COLOR_FormatYCbYCr;
                                      //vpssHdVfpcDeiCfg->opColorFormat0;
	}

	if ((outPortParamsPtr->cmnOutParams.pOutPortDef->format.video.eColorFormat ==
	                                                            OMX_COLOR_FormatYUV420Planar)       ||
        (outPortParamsPtr->cmnOutParams.pOutPortDef->format.video.eColorFormat ==
		                                                        OMX_COLOR_FormatYUV420PackedPlanar) ||
        (outPortParamsPtr->cmnOutParams.pOutPortDef->format.video.eColorFormat ==
		                                                        OMX_COLOR_FormatYUV420SemiPlanar)   ||
        (outPortParamsPtr->cmnOutParams.pOutPortDef->format.video.eColorFormat ==
		                                                        OMX_COLOR_FormatYUV420PackedSemiPlanar))
    {
      outPortParamsPtr->cmnOutParams.pOutPortDef->format.video.nStride =
                      outPortParamsPtr->cmnOutParams.pOutPortDef->format.video.nFrameWidth;
    }
#if 1
    else
    if ((outPortParamsPtr->cmnOutParams.pOutPortDef->format.video.eColorFormat ==
	                                                            OMX_COLOR_FormatYCbYCr)       ||
        (outPortParamsPtr->cmnOutParams.pOutPortDef->format.video.eColorFormat ==
		                                                        OMX_COLOR_FormatYCrYCb) ||
        (outPortParamsPtr->cmnOutParams.pOutPortDef->format.video.eColorFormat ==
		                                                        OMX_COLOR_FormatCbYCrY)   ||
        (outPortParamsPtr->cmnOutParams.pOutPortDef->format.video.eColorFormat ==
		                                                        OMX_COLOR_FormatCrYCbY))
    {
      outPortParamsPtr->cmnOutParams.pOutPortDef->format.video.nStride =
                      outPortParamsPtr->cmnOutParams.pOutPortDef->format.video.nFrameWidth * 2;
    }
#endif
    /* API entry time calculation macro */
    OMTB_OMX_API_ENTRY_TIME_CALC;

    /*Set the OutPort Definition*/
    err = OMX_SetParameter( vpssVfpcDeiClient->omtbPvt.handle,
                            OMX_IndexParamPortDefinition,
                            outPortParamsPtr->cmnOutParams.pOutPortDef);

    /* API exit time calculation macro */
    OMTB_OMX_API_EXIT_TIME_CALC("OMX_SetParameter");

    if(OMX_ErrorNone != err)
    {
      OMTB_OmxReturnStatus(err);
      return err;
    }
  }

  PRINT(PRINT_FUNCTION_NAME, "Leaving <Function , instance #> : <%s , %d>\n",
                              __FUNCTION__, (int)vpssVfpcDeiClient->omtbPvt.instanceNo);

  return err;
}


/******************************************************************************\
 *      VPSSVFPCDEI_SetPortDefinition Function Definition
\******************************************************************************/
/**
 *
 *  @brief    Set i/o port params.
 *
 *  @param in:
 *            vpssVfpcDeiClient:Pointer to appPrivateType structure
 *
 *  @param Out:
 *            None
 *
 *  @return   OMX_ERRORTYPE - OMX std return/error code
 *
 */

OMX_ERRORTYPE VPSSVFPCDEI_SetPortDefinition(void* thisClient)
{

  OMX_ERRORTYPE err = OMX_ErrorNone;
//  OMX_PORT_PARAM_TYPE portInit;
  OMTB_OMX_API_TIMING_VAR_DECL;
  OMTB_VPSS_VFPC_DEI_PRIVATE* vpssVfpcDeiClient = (OMTB_VPSS_VFPC_DEI_PRIVATE*) thisClient;
  /* validate the function arguments */
  ASSERT(NULL != vpssVfpcDeiClient);

  PRINT(PRINT_FUNCTION_NAME, "Entering <Function , instance #> : <%s , %d>\n",
                              __FUNCTION__, (int)vpssVfpcDeiClient->omtbPvt.instanceNo);
#if 0
  /* Set the component's OMX_PARAM_PORTDEFINITIONTYPE structure (input) */
  OMTB_SetHeader(&portInit,sizeof(OMX_PORT_PARAM_TYPE));
  portInit.nPorts = 2;
  portInit.nStartPortNumber = 0;

  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;

  /* Initialize the Port*/
  err = OMX_SetParameter( vpssVfpcDeiClient->omtbPvt.handle,
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
  err = VPSSVFPCDEI_SetInputPortDefinition(vpssVfpcDeiClient);
  if(OMX_ErrorNone != err)
  {
    PRINT(PRINT_ERR_MSG, "Error in setting i/p port params\n");
    OMTB_OmxReturnStatus(err);
  }

  /* set the o/p port params */
  err = VPSSVFPCDEI_SetOutputPortDefinition(vpssVfpcDeiClient);
  if(OMX_ErrorNone != err)
  {
    PRINT(PRINT_ERR_MSG, "Error in setting o/p port params\n");
    OMTB_OmxReturnStatus(err);
  }


  PRINT(PRINT_FUNCTION_NAME, "Leaving <Function , instance #> : <%s , %d>\n",
                              __FUNCTION__, (int)vpssVfpcDeiClient->omtbPvt.instanceNo);

  return err;
}

/******************************************************************************\
 *      VPSSVFPCDEI_GetStructIdx Function Definition
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

OmtbRet VPSSVFPCDEI_GetStructIdx(
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
  vpssVfpcDeiConfig = (OMTB_VPSS_VFPC_DEI_CONFIG_PARAMS*)
                     &(omtbCfgTemplate[template]->vpssVfpcDeiTemplate);

  /* Get the corresponding string for enum values from enum table
     Set structure index
     Set structure pointer
     Set port index for which parameter to be updated
     Set structure header info */
  while(strcmp(enumTblVpssVfpcDeiCfgParamIdx[enumCount].name , ""))
  {
    if(0 == strcmp(enumTblVpssVfpcDeiCfgParamIdx[enumCount].name,
                   indexStr))
    {
      switch(enumTblVpssVfpcDeiCfgParamIdx[enumCount].value)
      {

        case OMX_TI_IndexConfigChannelName:
          {
            *nConfigIndex   = enumTblVpssVfpcDeiCfgParamIdx[enumCount].value;
            *pCompCfgStruct = &vpssVfpcDeiConfig->sChannelName;
            vpssVfpcDeiConfig->sChannelName.nPortIndex = portIdx;
/* FIXME:  To support backword compatability with the older omtb scripts,
           the following code has not been removed, 
*/		   
//            if(!strcmp("NULL", vpssVfpcDeiConfig->sChannelName.cChannelName))	
            {			
			if(instanceNo==0)
			{
            snprintf(channelName, OMX_MAX_STRINGNAME_SIZE, "FQ_DEIMOUT_%d",
                     portIdx);
			}
			else
			{
			snprintf(channelName, OMX_MAX_STRINGNAME_SIZE, "FQ_DEIHOUT_%d",
                     portIdx);
			}
            channelName[OMX_MAX_STRINGNAME_SIZE - 1] = '\0';

			DOMX_UTL_Strncpy ( ( char * ) vpssVfpcDeiConfig->sChannelName.cChannelName, channelName,
					  sizeof ( vpssVfpcDeiConfig->sChannelName.cChannelName ) );
			}		  
            OMTB_SetHeader( *pCompCfgStruct,
                            sizeof(OMX_CONFIG_CHANNELNAME));
          }
          return OMTB_SUCCESS;

        case OMX_TI_IndexConfigChannelGroupInfo:
          {
            *nConfigIndex   = enumTblVpssVfpcDeiCfgParamIdx[enumCount].value;
            *pCompCfgStruct = &vpssVfpcDeiConfig->sConfigChannelGroupInfo;
//            vpssVfpcDeiConfig->sConfigChannelGroupInfo.nPortIndex = portIdx;
            OMTB_SetHeader( *pCompCfgStruct,
                            sizeof(OMX_CONFIG_CHANNELGROUPINFO));
          }
          return OMTB_SUCCESS;

        case OMX_TI_IndexConfigVidChResolution:
          {
            *nConfigIndex   = enumTblVpssVfpcDeiCfgParamIdx[enumCount].value;
            *pCompCfgStruct = &vpssVfpcDeiConfig->sVidChResolutionCfg;
            OMTB_SetHeader( *pCompCfgStruct,
                            sizeof(OMX_CONFIG_VIDCHANNEL_RESOLUTION));
          }
          return OMTB_SUCCESS;

        case OMX_TI_IndexConfigAlgEnable:
          {
            *nConfigIndex   = enumTblVpssVfpcDeiCfgParamIdx[enumCount].value;
            *pCompCfgStruct = &vpssVfpcDeiConfig->sAlgEnable;
             vpssVfpcDeiConfig->sAlgEnable.nPortIndex = portIdx;
             OMTB_SetHeader( *pCompCfgStruct,
                            sizeof(OMX_CONFIG_ALG_ENABLE));
          }
          return OMTB_SUCCESS;

   		case OMX_TI_IndexParamCompPortNotifyType:
          {
			*nConfigIndex   = enumTblVpssVfpcDeiCfgParamIdx[enumCount].value;
			*pCompCfgStruct = &vpssVfpcDeiConfig->sCompPortNotifyType;
            vpssVfpcDeiConfig->sCompPortNotifyType.nPortIndex = portIdx;
            OMTB_SetHeader( *pCompCfgStruct,
                            sizeof(OMX_PARAM_COMPPORT_NOTIFYTYPE));

		  }
		  return OMTB_SUCCESS;

		case OMX_IndexParamCompBufferSupplier:
		  {
			*nConfigIndex   = enumTblVpssVfpcDeiCfgParamIdx[enumCount].value;
			*pCompCfgStruct = &vpssVfpcDeiConfig->sBufSupplier;
			 vpssVfpcDeiConfig->sBufSupplier.nPortIndex = portIdx;
			 OMTB_SetHeader( *pCompCfgStruct,
							 sizeof(OMX_PARAM_BUFFERSUPPLIERTYPE));
		  }
  		  return OMTB_SUCCESS;

		case OMX_TI_IndexParamBuffMemType:
		  {
			*nConfigIndex   = enumTblVpssVfpcDeiCfgParamIdx[enumCount].value;
			*pCompCfgStruct = &vpssVfpcDeiConfig->sMemTypeCfg;
			 vpssVfpcDeiConfig->sMemTypeCfg.nPortIndex = portIdx;
			 OMTB_SetHeader( *pCompCfgStruct,
							 sizeof(OMX_PARAM_BUFFER_MEMORYTYPE));
		  }
  		  return OMTB_SUCCESS;

		case OMX_TI_IndexConfigSubSamplingFactor:
		  {
			*nConfigIndex   = enumTblVpssVfpcDeiCfgParamIdx[enumCount].value;
			*pCompCfgStruct = &vpssVfpcDeiConfig->sSubSamplingFactor;
			 vpssVfpcDeiConfig->sSubSamplingFactor.nPortIndex = portIdx;
			 OMTB_SetHeader( *pCompCfgStruct,
							 sizeof(OMX_CONFIG_SUBSAMPLING_FACTOR));
		  }
  		  return OMTB_SUCCESS;

		case OMX_TI_IndexParamVFPCNumChPerHandle:
		  {
			*nConfigIndex   = enumTblVpssVfpcDeiCfgParamIdx[enumCount].value;
			*pCompCfgStruct = &vpssVfpcDeiConfig->sNumChPerHandle;
			 vpssVfpcDeiConfig->sNumChPerHandle.nPortIndex = portIdx;
			 OMTB_SetHeader( *pCompCfgStruct,
							 sizeof(OMX_PARAM_VFPC_NUMCHANNELPERHANDLE));
		  }
  		  return OMTB_SUCCESS;

		case OMX_IndexParamVideoInit:
		  {
		    *nConfigIndex   = enumTblVpssVfpcDeiCfgParamIdx[enumCount].value;
			*pCompCfgStruct = &vpssVfpcDeiConfig->sPortInit;
			 OMTB_SetHeader( *pCompCfgStruct,
							 sizeof(OMX_PORT_PARAM_TYPE));
		  }
		  return OMTB_SUCCESS;

        case OMX_IndexParamPortDefinition:
	      {
		    *nConfigIndex   = enumTblVpssVfpcDeiCfgParamIdx[enumCount].value;
		    *pCompCfgStruct = &vpssVfpcDeiConfig->sPortDefType;
            vpssVfpcDeiConfig->sPortDefType.nPortIndex = portIdx;			
		    OMTB_SetHeader( *pCompCfgStruct,
			   			    sizeof(OMX_PARAM_PORTDEFINITIONTYPE));
	      }
	      return OMTB_SUCCESS;
		  
        default:
          {
            return OMTB_FAIL;
          }

      } // switch(enumTblVpssVfpcDeiCfgParamIdx[enumCount].value)

    } // if(0 == strcmp(enumTblVpssVfpcDeiCfgParamIdx[enumCount].name, ...

    enumCount++;
  }

  return OMTB_SUCCESS;
}

/******************************************************************************\
 *      VPSSVFPCDEI_FuncTsk Thread Definition
\******************************************************************************/
/**
 *
 *  @brief    This is a VPSS VFPC DEI thread which invokes during func command
 *
 *  @param in:
 *            void * - Thread args count
 *
 *            void *threadsArg - Pointer to thread arg structure
 *
 *  @return   None
 *
 */

void VPSSVFPCDEI_FuncTsk(void *argc, void *threadsArg)
{
//  int threadRes = TIMM_OSAL_ERR_NONE;
  OMX_ERRORTYPE err = OMX_ErrorNone;
  OMTB_VPSS_VFPC_DEI_PRIVATE* vpssVfpcDeiClient = NULL;
  OMTB_DATA_THREAD_ARG *funcDataThreadArg = (OMTB_DATA_THREAD_ARG *)threadsArg;
  unsigned int instanceNo = 0;
  OMTB_CLIENT_INPORT_PARAMS *inPortParamsPtr = NULL;
  OMTB_CLIENT_OUTPORT_PARAMS *outPortParamsPtr = NULL;
  unsigned int j = 0;	  
  OMTB_OMX_API_TIMING_VAR_DECL;

  /* thread argument validation */
  ASSERT(NULL != threadsArg);
  ASSERT(NULL != funcDataThreadArg->vpssVfpcDeiClient);

  vpssVfpcDeiClient = funcDataThreadArg->vpssVfpcDeiClient;

  PRINT(PRINT_MUST, "Entering <Thread , instance #> : <%s , %d>\n",
                     __FUNCTION__, (int)vpssVfpcDeiClient->omtbPvt.instanceNo);
#if 0
  PRINT(PRINT_SIMPLE_MESSAGE, "\nbufferOutSize:%d\n",\
        (int)outPortParamsPtr->cmnOutParams.bufferOutSize);
#endif
  /* Set the port params */
  err = VPSSVFPCDEI_SetPortDefinition(vpssVfpcDeiClient);

  if(OMX_ErrorNone != err)
  {
    OMTB_OmxReturnStatus(err);
  }

  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;

  /* send command to component to go to idle state */
  err = OMX_SendCommand(vpssVfpcDeiClient->omtbPvt.handle,
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
  err = OMTB_ClientAllocateResources(vpssVfpcDeiClient);

  if(OMX_ErrorNone != err)
  {
    OMTB_OmxReturnStatus(err);
  }

  /* waiting for component to go to idle state */
  TIMM_OSAL_SemaphoreObtain(vpssVfpcDeiClient->omtbPvt.eventSem, TIMM_OSAL_SUSPEND);

  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;

  /* send command to component to go to executing state */
  err = OMX_SendCommand(vpssVfpcDeiClient->omtbPvt.handle,
                        OMX_CommandStateSet,
                        OMX_StateExecuting,
                        NULL);

  if(OMX_ErrorNone != err)
  {
    OMTB_OmxReturnStatus(err);
  }

  /* waiting for component to go to executing state */
  TIMM_OSAL_SemaphoreObtain(vpssVfpcDeiClient->omtbPvt.eventSem, TIMM_OSAL_SUSPEND);

  /* Update the func create count */
  VPSSVFPCDEI_funcCreateCount++;
  PRINT(PRINT_MUST, "%s: VPSS VFPC DEI FUNC Create Count: %u\n", __FUNCTION__,
                    (unsigned int) VPSSVFPCDEI_funcCreateCount);

#if 0
  /* Update the data streaming thread arguments */
  strmThreadArg[vpssVfpcDeiClient->omtbPvt.instanceNo].vpssVfpcDeiClient = vpssVfpcDeiClient;

  /* Create input data read thread */
  threadRes = TIMM_OSAL_CreateTask(
                    (void *)&inPortParamsPtr->cmnInParams.inDataStrmThrdId,
                    (TIMM_OSAL_TaskProc)VPSSVFPCDEI_InputDataRead,
                    0,
                    &strmThreadArg[vpssVfpcDeiClient->omtbPvt.instanceNo],
                    OMTB_VPSS_VFPC_DEI_TSK_STACK_SIZE,
                    OMTB_VPSS_VFPC_DEI_GROUP_PRIORITY,
                    (signed char*)"VPSS_VFPC_DEI_DATA_IN_TSK");

  if(TIMM_OSAL_ERR_NONE != threadRes)
  {
    PRINT(PRINT_ERR_MSG,
          "Unable to start VPSS VFPC DEI input data read thread\n");
  }

  /* Create output data write thread */
  threadRes = TIMM_OSAL_CreateTask(
                    (void *)&outPortParamsPtr->cmnOutParams.outDataStrmThrdId,
                    (TIMM_OSAL_TaskProc)VPSSVFPCDEI_OutputDataWrite,
                    0,
                    &strmThreadArg[vpssVfpcDeiClient->omtbPvt.instanceNo],
                    OMTB_VPSS_VFPC_DEI_TSK_STACK_SIZE,
                    OMTB_VPSS_VFPC_DEI_GROUP_PRIORITY,
                    (signed char*)"VPSS_VFPC_DEI_DATA_OUT_TSK");

  if(TIMM_OSAL_ERR_NONE != threadRes)
  {
    PRINT(PRINT_ERR_MSG,
          "Unable to start VPSS VFPC DEI output data write thread\n");
  }
#endif
  /* Wait for EOS */
  TIMM_OSAL_SemaphoreObtain(vpssVfpcDeiClient->eofSem, TIMM_OSAL_SUSPEND);

  PRINT(DEFAULT_MESSAGES, "The execution of the VPSS VFPC DEI \
                           process is terminated\n");

  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;

  /* state change of component from executing to idle */
  err = OMX_SendCommand(vpssVfpcDeiClient->omtbPvt.handle,
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
  TIMM_OSAL_SemaphoreObtain(vpssVfpcDeiClient->omtbPvt.eventSem, TIMM_OSAL_SUSPEND);

  PRINT(DEFAULT_MESSAGES, "State transitioned to Idle\n");

  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;

  /* sending command to component to go to loaded state */
  err = OMX_SendCommand(vpssVfpcDeiClient->omtbPvt.handle,
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
  for (j =0 ; j < OMTB_VPSS_DEI_MAX_NUM_IN_PORT ; j++) {
    inPortParamsPtr = vpssVfpcDeiClient->inPortParams + j;   
    inPortParamsPtr->cmnInParams.flagInputEos = OMX_FALSE;
  }
  for (j =0 ; j < OMTB_VPSS_DEI_MAX_NUM_OUT_PORT ; j++) {
    outPortParamsPtr = vpssVfpcDeiClient->outPortParams + j; 
    outPortParamsPtr->cmnOutParams.flagEos = OMX_FALSE;
  }

  /* Function to release the resources allocated by component */
  err = OMTB_ClientFreeResources(vpssVfpcDeiClient);

  if(OMX_ErrorNone != err)
  {
    OMTB_OmxReturnStatus(err);
  }

  /* wait for event handler to report completion of loaded command */
  /* Temporarily commented to allow new commands after IDLE to LOADED state transition */
//  TIMM_OSAL_SemaphoreObtain(vpssVfpcDeiClient->omtbPvt.eventSem, TIMM_OSAL_SUSPEND);

  PRINT(PRINT_SIMPLE_MESSAGE, "State transitioned to loaded\n");

  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;

  /* Delete the component instance */
  err = OMX_FreeHandle(vpssVfpcDeiClient->omtbPvt.handle);

  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_FreeHandle");

  if(OMX_ErrorNone != err)
  {
    OMTB_OmxReturnStatus(err);
  }
  else
  {
    /* Update the component instance management structure for deleted instance
       by assigning NULL pointer */
    vpssVfpcDeiClient->omtbPvt.handle = NULL;
    PRINT(PRINT_MUST,
          "\r      \n\nOMTB-Deleted VPSS VFPC DEI Instance #: %d\n\n",
          (int) vpssVfpcDeiClient->omtbPvt.instanceNo);
    omtbClass[OMTB_VPSS_VFPC_DEI_CLASS].handle[vpssVfpcDeiClient->omtbPvt.instanceNo] = NULL;
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
  vpssVfpcDeiClient->omtbPvt.flagThrCreated = OMX_FALSE;

  /* save the instance no to local variable */
  instanceNo = vpssVfpcDeiClient->omtbPvt.instanceNo;

  /* release the memory allocated for app pvt data */
  OMTB_FreeMemory(vpssVfpcDeiClient);

  /* Update the func delete count */
  VPSSVFPCDEI_funcDeleteCount++;

  PRINT(PRINT_MUST, "%s: VPSS VFPC DEI FUNC Delete Count: %u\n", __FUNCTION__,
                    (unsigned int) VPSSVFPCDEI_funcDeleteCount);

  PRINT(PRINT_MUST, "Leaving <Thread , instance #> : <%s , %d>\n",
                     __FUNCTION__, (int)instanceNo);

  /* exit the thread */
  TIMM_OSAL_ExitTask(
      omtbClass[OMTB_VPSS_VFPC_DEI_CLASS].execThreadId[instanceNo],
      NULL);
}

/******************************************************************************\
 *      VPSSVFPCDEI_SetTemplateDefVal Function Definition
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

MX_Result VPSSVFPCDEI_SetTemplateDefVal(OMTB_TEMPLATE_INFO *pTemplate)
{
  OMTB_VPSS_VFPC_DEI_CONFIG_PARAMS *vpssHdVfpcDeiCfg = NULL;

  /* param validation */
  if(NULL == pTemplate)
  {
    PRINT(PRINT_ERR_MSG, "%s: Memory for Template not allocated\n",__FUNCTION__);
    return ERR_INVNAME;
  }

  /* VPSS VFPC DEI configuration */
  vpssHdVfpcDeiCfg = &pTemplate->vpssVfpcDeiTemplate;

  strcpy(vpssHdVfpcDeiCfg->sBasicParams.inputFile, "vpssvfpc_dei_sample.yuv");
  strcpy(vpssHdVfpcDeiCfg->sBasicParams.outputFile,"vpssvfpc_dei_test.yuv");
  strcpy(vpssHdVfpcDeiCfg->sBasicParams.compName,   OMTB_VPSS_VFPC_DEI_COMPONENT_NAME);
  vpssHdVfpcDeiCfg->sBasicParams.frameWidth       = OMTB_VPSS_VFPC_DEI_DEF_WIDTH;
  vpssHdVfpcDeiCfg->sBasicParams.frameHeight      = OMTB_VPSS_VFPC_DEI_DEF_HEIGHT;
  vpssHdVfpcDeiCfg->sBasicParams.colorFormat      = OMX_COLOR_FormatYUV420SemiPlanar;
  vpssHdVfpcDeiCfg->sBasicParams.inColorFormat    = OMX_COLOR_FormatYUV420SemiPlanar;
  //vpssHdVfpcDeiCfg->sBasicParams.opColorFormat0   = OMX_COLOR_FormatYCbYCr;
  vpssHdVfpcDeiCfg->sBasicParams.dataOutPutMode   = OMTB_DRIVER;
  vpssHdVfpcDeiCfg->sBasicParams.dataInPutMode    = OMTB_DRIVER;  
  vpssHdVfpcDeiCfg->sBasicParams.numInBuf         = OMTB_VPSS_VFPC_DEI_NUM_IN_BUFS;
  vpssHdVfpcDeiCfg->sBasicParams.inBufAlignment   = 0;
  vpssHdVfpcDeiCfg->sBasicParams.inBufContiguous  = TIMM_OSAL_FALSE;
  vpssHdVfpcDeiCfg->sBasicParams.inBufSize        = OMTB_VPSS_VFPC_DEI_MAX_INBUFF_SIZE;
  vpssHdVfpcDeiCfg->sBasicParams.inBufSzFlag      = OMX_FALSE;
  vpssHdVfpcDeiCfg->sBasicParams.flagUseInBuffer  = OMX_FALSE;
  vpssHdVfpcDeiCfg->sBasicParams.numOutBuf        = OMTB_VPSS_VFPC_DEI_NUM_OUT_BUFS;
  vpssHdVfpcDeiCfg->sBasicParams.outBufAlignment  = 0;
  vpssHdVfpcDeiCfg->sBasicParams.outBufContiguous = TIMM_OSAL_FALSE;
  vpssHdVfpcDeiCfg->sBasicParams.outBufSize       = OMTB_VPSS_VFPC_DEI_MAX_OUTBUFF_SIZE;
  vpssHdVfpcDeiCfg->sBasicParams.outBufSzFlag     = OMX_FALSE;
  vpssHdVfpcDeiCfg->sBasicParams.flagUseOutBuffer = OMX_FALSE;
  vpssHdVfpcDeiCfg->sBasicParams.compressionFormat = OMX_VIDEO_CodingUnused;
  vpssHdVfpcDeiCfg->sBasicParams.fileReset        = OMX_TRUE;
	
  vpssHdVfpcDeiCfg->sVidChResolutionCfg.nPortIndex    = 0;
  vpssHdVfpcDeiCfg->sVidChResolutionCfg.nChId         = 0;
  vpssHdVfpcDeiCfg->sVidChResolutionCfg.Frm0Width     = 360;
  vpssHdVfpcDeiCfg->sVidChResolutionCfg.Frm0Height    = 240;
  vpssHdVfpcDeiCfg->sVidChResolutionCfg.Frm0Pitch     = 1440;
  vpssHdVfpcDeiCfg->sVidChResolutionCfg.eDir          = OMX_DirOutput;
  vpssHdVfpcDeiCfg->sVidChResolutionCfg.Frm1Width     = 720;
  vpssHdVfpcDeiCfg->sVidChResolutionCfg.Frm1Height    = 480;
  vpssHdVfpcDeiCfg->sVidChResolutionCfg.Frm1Pitch     = 720;
  vpssHdVfpcDeiCfg->sVidChResolutionCfg.FrmStartX     = 0;
  vpssHdVfpcDeiCfg->sVidChResolutionCfg.FrmStartY     = 0;
  vpssHdVfpcDeiCfg->sVidChResolutionCfg.FrmCropWidth  = 720;
  vpssHdVfpcDeiCfg->sVidChResolutionCfg.FrmCropHeight = 480;

  vpssHdVfpcDeiCfg->sAlgEnable.nChId = 0;
  vpssHdVfpcDeiCfg->sAlgEnable.bAlgBypass = OMX_FALSE;

  vpssHdVfpcDeiCfg->sCompPortNotifyType.eNotifyType = OMX_NOTIFY_TYPE_ALWAYS;

  vpssHdVfpcDeiCfg->sBufSupplier.eBufferSupplier =  OMX_BufferSupplyUnspecified;

  vpssHdVfpcDeiCfg->sMemTypeCfg.eBufMemoryType = OMX_BUFFER_MEMORY_DEFAULT;

  vpssHdVfpcDeiCfg->sSubSamplingFactor.nSubSamplingFactor = OMTB_VPSS_VFPC_DEI_DEF_SUB_SAMP_FACTOR;

  vpssHdVfpcDeiCfg->sNumChPerHandle.nNumChannelsPerHandle = OMTB_VPSS_VFPC_DEI_DEF_NO_OF_CHAN;

  vpssHdVfpcDeiCfg->sPortInit.nPorts           = OMX_VFPC_NUM_PORTS;
  vpssHdVfpcDeiCfg->sPortInit.nStartPortNumber = OMX_VFPC_DEFAULT_START_PORT_NUM;

  vpssHdVfpcDeiCfg->sPortDefType.eDir                               = OMX_DirInput;
  vpssHdVfpcDeiCfg->sPortDefType.nBufferCountActual                 = OMTB_VPSS_VFPC_DEI_NUM_IN_BUFS;
  vpssHdVfpcDeiCfg->sPortDefType.nBufferCountMin                    = 1; 
  vpssHdVfpcDeiCfg->sPortDefType.nBufferSize                        = OMTB_VPSS_VFPC_DEI_MAX_INBUFF_SIZE;    
  vpssHdVfpcDeiCfg->sPortDefType.bEnabled                           = OMX_FALSE; 
  vpssHdVfpcDeiCfg->sPortDefType.bPopulated                         = OMX_FALSE; 
  vpssHdVfpcDeiCfg->sPortDefType.eDomain                            = OMX_PortDomainVideo;
  vpssHdVfpcDeiCfg->sPortDefType.bBuffersContiguous                 = OMX_FALSE;
  vpssHdVfpcDeiCfg->sPortDefType.nBufferAlignment                   = 0;
  vpssHdVfpcDeiCfg->sPortDefType.format.video.cMIMEType             = NULL;
  vpssHdVfpcDeiCfg->sPortDefType.format.video.pNativeRender         = NULL;
  vpssHdVfpcDeiCfg->sPortDefType.format.video.nFrameWidth           = OMTB_VPSS_VFPC_DEI_DEF_WIDTH;
  vpssHdVfpcDeiCfg->sPortDefType.format.video.nFrameHeight          = OMTB_VPSS_VFPC_DEI_DEF_HEIGHT;
  vpssHdVfpcDeiCfg->sPortDefType.format.video.nStride               = (OMTB_VPSS_VFPC_DEI_DEF_WIDTH * 2);
  vpssHdVfpcDeiCfg->sPortDefType.format.video.nSliceHeight          = 0;
  vpssHdVfpcDeiCfg->sPortDefType.format.video.nBitrate              = 0;
  vpssHdVfpcDeiCfg->sPortDefType.format.video.xFramerate            = 0;
  vpssHdVfpcDeiCfg->sPortDefType.format.video.bFlagErrorConcealment = OMX_FALSE;
  vpssHdVfpcDeiCfg->sPortDefType.format.video.eCompressionFormat    = OMX_VIDEO_CodingUnused;
  vpssHdVfpcDeiCfg->sPortDefType.format.video.eColorFormat          = OMX_COLOR_FormatYCbYCr;
  vpssHdVfpcDeiCfg->sPortDefType.format.video.pNativeWindow         = NULL;
  
  strcpy(vpssHdVfpcDeiCfg->sChannelName.cChannelName, "NULL");  
  return ERR_NOERR;
}


OmtbRet VPSSVFPCDEI_SetBufferSize(void *thisClient)
{
  OmtbRet err = OMTB_SUCCESS;
  unsigned int i = 0;
  OMTB_BASIC_CONFIG_PARAMS *pBasicConfig = NULL;
  OMTB_VPSS_VFPC_DEI_PRIVATE *vpssVfpcDeiClient = NULL;
  OMTB_CLIENT_INPORT_PARAMS *inPortParamsPtr = NULL;
  OMTB_CLIENT_OUTPORT_PARAMS *outPortParamsPtr = NULL;
	
  /* validate the function arguments */
  ASSERT(NULL != thisClient);
  vpssVfpcDeiClient = (OMTB_VPSS_VFPC_DEI_PRIVATE*)thisClient;
  pBasicConfig = &(omtbCfgTemplate[vpssVfpcDeiClient->omtbPvt.templateNo]->vpssVfpcDeiTemplate.sBasicParams);
  
  PRINT(PRINT_FUNCTION_NAME, "Entering <Function , instance #> : <%s , %d>\n",
                              __FUNCTION__, (int)vpssVfpcDeiClient->omtbPvt.instanceNo);
  for (i =0 ; i < vpssVfpcDeiClient->omtbPvt.numInport; i++)
  {
    inPortParamsPtr = vpssVfpcDeiClient->inPortParams + i; 	
    
	/* set the input buffer size */    
    if(OMX_FALSE == inPortParamsPtr->cmnInParams.inBufSzFlag)
    {
      /* input buffer size calculation based on frame dimension speculation */
      switch(inPortParamsPtr->colorFormat)
      {
        case OMX_COLOR_FormatYUV420Planar:
        case OMX_COLOR_FormatYUV420SemiPlanar:
          inPortParamsPtr->cmnInParams.bufferInSize =
                  (((pBasicConfig->frameWidth * pBasicConfig->frameHeight) * 3) >> 1);
        break;

        case OMX_COLOR_FormatYUV422Planar:
        case OMX_COLOR_FormatYCbYCr:
          inPortParamsPtr->cmnInParams.bufferInSize =
                  ((pBasicConfig->frameWidth * pBasicConfig->frameHeight) * 2);
        break;

        default:
          PRINT(PRINT_MUST, "Undefined chroma format. Setting o/p buffer size \
according to 422P format.\n");
          inPortParamsPtr->cmnInParams.bufferInSize =
                  ((pBasicConfig->frameWidth * pBasicConfig->frameHeight) * 2);
        break;
      } // switch(h264VdecClient->inPortParams->colorFormat)
    }
    else
    {
      inPortParamsPtr->cmnInParams.bufferInSize = pBasicConfig->inBufSize;
    }
  }	
  
  for (i =0 ; i < vpssVfpcDeiClient->omtbPvt.numOutport; i++)
  {
    outPortParamsPtr = vpssVfpcDeiClient->outPortParams + i; 	
    
	/* set the output buffer size */    
    if(OMX_FALSE == outPortParamsPtr->cmnOutParams.outBufSzFlag)
    {
      /* output buffer size calculation based on frame dimension speculation */
      switch(outPortParamsPtr->colorFormat)
      {
        case OMX_COLOR_FormatYUV420Planar:
        case OMX_COLOR_FormatYUV420SemiPlanar:
          outPortParamsPtr->cmnOutParams.bufferOutSize =
                  (((pBasicConfig->frameWidth * pBasicConfig->frameHeight) * 3) >> 1);
        break;

        case OMX_COLOR_FormatYUV422Planar:
        case OMX_COLOR_FormatYCbYCr:
          outPortParamsPtr->cmnOutParams.bufferOutSize =
                  ((pBasicConfig->frameWidth * pBasicConfig->frameHeight) * 2);
        break;

        default:
          PRINT(PRINT_MUST, "Undefined chroma format. Setting o/p buffer size \
according to 422P format.\n");
          outPortParamsPtr->cmnOutParams.bufferOutSize =
                  ((pBasicConfig->frameWidth * pBasicConfig->frameHeight) * 2);
        break;
      } // switch(h264VdecClient->outPortParams->colorFormat)
    }
    else
    {
      outPortParamsPtr->cmnOutParams.bufferOutSize = pBasicConfig->outBufSize;
    }
  }	
  
  PRINT(PRINT_FUNCTION_NAME, "Leaving <Function #> : <%s>\n",
                             __FUNCTION__);  
  return err;
}

/******************************************************************************\
 *      VPSSVFPCDEI_ClassInit Function Definition
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
OMX_ERRORTYPE VPSSVFPCDEI_ClassInit(OMTB_CLIENT_PRIVATE* thisClient)
{
  OmtbRet err = OMTB_SUCCESS;
  
  PRINT(PRINT_FUNCTION_NAME, "Entering <Function> : <%s>\n",
                              __FUNCTION__);
							  
  /* no of input / output ports */
  thisClient->omtbPvt.numInport  = 1; //OMTB_VPSS_DEI_MAX_NUM_IN_PORT;
  thisClient->omtbPvt.numOutport = 2; //OMTB_VPSS_DEI_MAX_NUM_OUT_PORT
  thisClient->omtbPvt.startOutportIndex = OMTB_VPSS_DEI_MAX_NUM_IN_PORT;
  
  thisClient->omtbPvt.outputDataWriteTask = OMTB_OutputDataWrite;
  thisClient->omtbPvt.inputDataReadTask = OMTB_InputDataRead;

  /* Function pointer for GetStructIdx */
  thisClient->omtbPvt.fpGetStructIdx = VPSSVFPCDEI_GetStructIdx; 
  thisClient->omtbPvt.fpSetBufferSize = VPSSVFPCDEI_SetBufferSize;
  thisClient->omtbPvt.fpSetPortDefinition = VPSSVFPCDEI_SetPortDefinition;
  
  thisClient->omtbPvt.numFileInBufs = OMTB_CLIENT_MAX_NUM_FILE_IN_BUFS;
  thisClient->omtbPvt.numFileOutBufs = OMTB_CLIENT_MAX_NUM_FILE_OUT_BUFS;
  
  thisClient->omtbPvt.readSize       = OMTB_VPSS_VFPC_DEI_MAX_INBUFF_SIZE;
  thisClient->omtbPvt.writeSize      = OMTB_VPSS_VFPC_DEI_MAX_OUTBUFF_SIZE; 	 
  
  thisClient->omtbPvt.eClassType = OMTB_VPSS_VFPC_DEI_CLASS;
	
  PRINT(PRINT_FUNCTION_NAME, "Leaving <Function> : <%s>\n",
                              __FUNCTION__);  
  return (err);							  
}
/*----------------------------- end of file ----------------------------------*/

