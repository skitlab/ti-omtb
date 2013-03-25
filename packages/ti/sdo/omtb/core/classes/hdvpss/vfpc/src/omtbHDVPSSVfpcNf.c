/*
 * omtbHDVPSSVfpcDeiCfgCmdEntries.c
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

static OMX_CALLBACKTYPE VPSSVFPCNF_Callback = {
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
OMTB_VPSS_VFPC_NF_CONFIG_PARAMS *vpssVfpcNfConfig = NULL;


/******************************************************************************\
 *      Static Globals
\******************************************************************************/

static OMX_U32 VPSSVFPCNF_funcCreateCount = 0;  /* Func create count */
static OMX_U32 VPSSVFPCNF_apiCreateCount = 0;   /* API create count */

static OMX_U32 VPSSVFPCNF_funcDeleteCount = 0;  /* Func delete count */
static OMX_U32 VPSSVFPCNF_apiDeleteCount = 0;   /* API delete count */

/* Enum Entry for Supported cfg param indexs */

PRIVATE MX_DBG_ENUM_ENTRY_T enumTblVpssVfpcNfCfgParamIdx[] =
{
  /* ADD ENTRIES HERE for SetConfig/SetParam/GetConfig/GetParam */
  {"OMX_TI_IndexConfigChannelName",        OMX_TI_IndexConfigChannelName,        ""},
  {"OMX_TI_IndexConfigChannelGroupInfo",   OMX_TI_IndexConfigChannelGroupInfo,   ""},
  {"OMX_TI_IndexConfigVidChResolution",    OMX_TI_IndexConfigVidChResolution,    ""},
  {"OMX_TI_IndexParamCompPortNotifyType",  OMX_TI_IndexParamCompPortNotifyType,  ""},
  {"OMX_IndexParamCompBufferSupplier",     OMX_IndexParamCompBufferSupplier,     ""},
  {"OMX_TI_IndexParamBuffMemType",         OMX_TI_IndexParamBuffMemType,         ""},
  {"OMX_TI_IndexConfigAlgEnable",          OMX_TI_IndexConfigAlgEnable,          ""},
  {"OMX_TI_IndexConfigSubSamplingFactor",  OMX_TI_IndexConfigSubSamplingFactor,  ""},  
  {"OMX_TI_IndexParamVFPCNumChPerHandle",  OMX_TI_IndexParamVFPCNumChPerHandle,  ""},
  {"OMX_IndexParamVideoInit",              OMX_IndexParamVideoInit,              ""},
  {"OMX_IndexParamPortDefinition",         OMX_IndexParamPortDefinition,         ""},   
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
 *      VPSSVFPCNF_SetInputPortDefinition Function Definition
\******************************************************************************/
/**
 *
 *  @brief    Set i/p port params.
 *
 *  @param in:
 *            vpssVfpcNfClient:Pointer to appPrivateType structure
 *
 *  @param Out:
 *            None
 *
 *  @return   OMX_ERRORTYPE - OMX std return/error code
 *
 */

OMX_ERRORTYPE VPSSVFPCNF_SetInputPortDefinition(OMTB_VPSS_VFPC_NF_PRIVATE* vpssVfpcNfClient)
{

  OMX_ERRORTYPE err = OMX_ErrorNone;
  OMTB_OMX_API_TIMING_VAR_DECL;
  unsigned int i = 0;
  OMTB_CLIENT_INPORT_PARAMS *inPortParamsPtr = NULL;  
  /* validate the function arguments */
  ASSERT(NULL != vpssVfpcNfClient);

  PRINT(PRINT_FUNCTION_NAME, "Entering <Function , instance #> : <%s , %d>\n",
                              __FUNCTION__, (int)vpssVfpcNfClient->omtbPvt.instanceNo);


  for (i =0 ; i < vpssVfpcNfClient->omtbPvt.numInport ; i++)
  {
    inPortParamsPtr = vpssVfpcNfClient->inPortParams + i; 
    
	/* Set the component's OMX_PARAM_PORTDEFINITIONTYPE structure (input) */
    OMTB_SetHeader( inPortParamsPtr->cmnInParams.pInPortDef,
                    sizeof(OMX_PARAM_PORTDEFINITIONTYPE));	
    
	inPortParamsPtr->cmnInParams.pInPortDef->nPortIndex          =
                                    (OMX_VFPC_INPUT_PORT_START_INDEX + i);

    /* API entry time calculation macro */
    OMTB_OMX_API_ENTRY_TIME_CALC;

    /*Get the OutPort Definition*/
    err = OMX_GetParameter( vpssVfpcNfClient->omtbPvt.handle,
                            OMX_IndexParamPortDefinition,
                            inPortParamsPtr->cmnInParams.pInPortDef);

    /* API exit time calculation macro */
    OMTB_OMX_API_EXIT_TIME_CALC("OMX_GetParameter");


    inPortParamsPtr->cmnInParams.pInPortDef->eDir                = OMX_DirInput;
 
	inPortParamsPtr->cmnInParams.pInPortDef->nBufferCountActual  =
                                    inPortParamsPtr->cmnInParams.numInBuf;
    inPortParamsPtr->cmnInParams.pInPortDef->nBufferCountMin     = 1;

    //  inPortParamsPtr->cmnInParams.pInPortDef->nBufferSize         =
    //                                  inPortParamsPtr->cmnInParams.bufferInSize;
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

    /* API entry time calculation macro */
    OMTB_OMX_API_ENTRY_TIME_CALC;

    /*Set the inPort Definition*/
    err = OMX_SetParameter( vpssVfpcNfClient->omtbPvt.handle,
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
                              __FUNCTION__, (int)vpssVfpcNfClient->omtbPvt.instanceNo);

  return err;
}


/******************************************************************************\
 *      VPSSVFPCNF_SetOutputPortDefinition Function Definition
\******************************************************************************/
/**
 *
 *  @brief    Set o/p port params.
 *
 *  @param in:
 *            vpssVfpcNfClient:Pointer to appPrivateType structure
 *
 *  @param Out:
 *            None
 *
 *  @return   OMX_ERRORTYPE - OMX std return/error code
 *
 */

OMX_ERRORTYPE VPSSVFPCNF_SetOutputPortDefinition(OMTB_VPSS_VFPC_NF_PRIVATE* vpssVfpcNfClient)
{

  OMX_ERRORTYPE err = OMX_ErrorNone;
  OMTB_OMX_API_TIMING_VAR_DECL;
  unsigned int i = 0;
  OMTB_CLIENT_OUTPORT_PARAMS *outPortParamsPtr = NULL;
  /* validate the function arguments */
  ASSERT(NULL != vpssVfpcNfClient);

  PRINT(PRINT_FUNCTION_NAME, "Entering <Function , instance #> : <%s , %d>\n",
                              __FUNCTION__, (int)vpssVfpcNfClient->omtbPvt.instanceNo);

  /*
  if(OMX_FALSE == vpssVfpcNfClient->outPortParams.cmnOutParams.outBufSzFlag)
  {
    vpssVfpcNfClient->outPortParams.cmnOutParams.bufferOutSize =
                      (vpssVfpcNfClient->outPortParams.nWidth *\
                      vpssVfpcNfClient->outPortParams.nHeight * 2);
  }
  */



  /* Set the component's OMX_PARAM_PORTDEFINITIONTYPE structure (output) */
  for (i =0 ; i < vpssVfpcNfClient->omtbPvt.numOutport ; i++)
  {
    outPortParamsPtr =  vpssVfpcNfClient->outPortParams + i;  
	 
    OMTB_SetHeader( outPortParamsPtr->cmnOutParams.pOutPortDef,
                  sizeof(OMX_PARAM_PORTDEFINITIONTYPE));
				  
    outPortParamsPtr->cmnOutParams.pOutPortDef->nPortIndex         =
                                    (vpssVfpcNfClient->omtbPvt.startOutportIndex + i);

    /* API entry time calculation macro */
	OMTB_OMX_API_ENTRY_TIME_CALC;

	/*Get the OutPort Definition*/
	err = OMX_GetParameter( vpssVfpcNfClient->omtbPvt.handle,
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
    outPortParamsPtr->cmnOutParams.pOutPortDef->bBuffersContiguous  =
                                    (OMX_BOOL)outPortParamsPtr->cmnOutParams.outBufContiguous;
    outPortParamsPtr->cmnOutParams.pOutPortDef->nBufferAlignment    =
                                    outPortParamsPtr->cmnOutParams.outBufAlignment;

    outPortParamsPtr->cmnOutParams.pOutPortDef->format.video.nFrameWidth =
                                  outPortParamsPtr->nWidth;

    outPortParamsPtr->cmnOutParams.pOutPortDef->format.video.nFrameHeight =
                                  outPortParamsPtr->nHeight;
								  
    outPortParamsPtr->cmnOutParams.pOutPortDef->format.video.eCompressionFormat =
                                    OMX_VIDEO_CodingUnused;
    outPortParamsPtr->cmnOutParams.pOutPortDef->format.video.eColorFormat =
                                    outPortParamsPtr->colorFormat;
	
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
    err = OMX_SetParameter( vpssVfpcNfClient->omtbPvt.handle,
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
                              __FUNCTION__, (int)vpssVfpcNfClient->omtbPvt.instanceNo);

  return err;
}


/******************************************************************************\
 *      VPSSVFPCNF_SetPortDefinition Function Definition
\******************************************************************************/
/**
 *
 *  @brief    Set i/o port params.
 *
 *  @param in:
 *            vpssVfpcNfClient:Pointer to appPrivateType structure
 *
 *  @param Out:
 *            None
 *
 *  @return   OMX_ERRORTYPE - OMX std return/error code
 *
 */

OMX_ERRORTYPE VPSSVFPCNF_SetPortDefinition(void* thisClient)
{

  OMX_ERRORTYPE err = OMX_ErrorNone;
//  OMX_PORT_PARAM_TYPE portInit;
  OMTB_OMX_API_TIMING_VAR_DECL;
  OMTB_VPSS_VFPC_NF_PRIVATE* vpssVfpcNfClient = (OMTB_VPSS_VFPC_NF_PRIVATE*) thisClient;
  /* validate the function arguments */
  ASSERT(NULL != vpssVfpcNfClient);

  PRINT(PRINT_FUNCTION_NAME, "Entering <Function , instance #> : <%s , %d>\n",
                              __FUNCTION__, (int)vpssVfpcNfClient->omtbPvt.instanceNo);
#if 0
  /* Set the component's OMX_PARAM_PORTDEFINITIONTYPE structure (input) */
  OMTB_SetHeader(&portInit,sizeof(OMX_PORT_PARAM_TYPE));
  portInit.nPorts = 2;
  portInit.nStartPortNumber = 0;

  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;

  /* Initialize the Port*/
  err = OMX_SetParameter( vpssVfpcNfClient->omtbPvt.handle,
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
  err = VPSSVFPCNF_SetInputPortDefinition(vpssVfpcNfClient);
  if(OMX_ErrorNone != err)
  {
    PRINT(PRINT_ERR_MSG, "Error in setting i/p port params\n");
    OMTB_OmxReturnStatus(err);
  }

  /* set the o/p port params */
  err = VPSSVFPCNF_SetOutputPortDefinition(vpssVfpcNfClient);
  if(OMX_ErrorNone != err)
  {
    PRINT(PRINT_ERR_MSG, "Error in setting o/p port params\n");
    OMTB_OmxReturnStatus(err);
  }


  PRINT(PRINT_FUNCTION_NAME, "Leaving <Function , instance #> : <%s , %d>\n",
                              __FUNCTION__, (int)vpssVfpcNfClient->omtbPvt.instanceNo);

  return err;
}

/******************************************************************************\
 *      VPSSVFPCNF_GetStructIdx Function Definition
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

OmtbRet VPSSVFPCNF_GetStructIdx(
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
  vpssVfpcNfConfig = (OMTB_VPSS_VFPC_NF_CONFIG_PARAMS*)
                     &(omtbCfgTemplate[template]->vpssVfpcNfTemplate);

  /* Get the corresponding string for enum values from enum table
     Set structure index
     Set structure pointer
     Set port index for which parameter to be updated
     Set structure header info */
  while(strcmp(enumTblVpssVfpcNfCfgParamIdx[enumCount].name , ""))
  {
    if(0 == strcmp(enumTblVpssVfpcNfCfgParamIdx[enumCount].name,
                   indexStr))
    {
      switch(enumTblVpssVfpcNfCfgParamIdx[enumCount].value)
      {

        case OMX_TI_IndexConfigChannelName:
          {
            *nConfigIndex   = enumTblVpssVfpcNfCfgParamIdx[enumCount].value;
            *pCompCfgStruct = &vpssVfpcNfConfig->sChannelName;
            vpssVfpcNfConfig->sChannelName.nPortIndex = portIdx;
/* FIXME:  To support backword compatability with the older omtb scripts,
           the following code has not been removed, 
*/		   
//            if(!strcmp("NULL", vpssVfpcNfConfig->sChannelName.cChannelName))	
            {
              snprintf(channelName, OMX_MAX_STRINGNAME_SIZE, "FQ_NFOUT_%d",
                       portIdx);
              channelName[OMX_MAX_STRINGNAME_SIZE - 1] = '\0';
			  DOMX_UTL_Strncpy ( ( char * ) vpssVfpcNfConfig->sChannelName.cChannelName, channelName,
				  	    sizeof ( vpssVfpcNfConfig->sChannelName.cChannelName ) );
            }
            OMTB_SetHeader( *pCompCfgStruct,
                            sizeof(OMX_CONFIG_CHANNELNAME));
          }
          return OMTB_SUCCESS;

        case OMX_TI_IndexConfigChannelGroupInfo:
          {
            *nConfigIndex   = enumTblVpssVfpcNfCfgParamIdx[enumCount].value;
            *pCompCfgStruct = &vpssVfpcNfConfig->sConfigChannelGroupInfo;
//            vpssVfpcNfConfig->sConfigChannelGroupInfo.nPortIndex = portIdx;
            OMTB_SetHeader( *pCompCfgStruct,
                            sizeof(OMX_CONFIG_CHANNELGROUPINFO));
          }
          return OMTB_SUCCESS;

        case OMX_TI_IndexConfigVidChResolution:
          {
            *nConfigIndex   = enumTblVpssVfpcNfCfgParamIdx[enumCount].value;
            *pCompCfgStruct = &vpssVfpcNfConfig->sVidChResolutionCfg;
            OMTB_SetHeader( *pCompCfgStruct,
                            sizeof(OMX_CONFIG_VIDCHANNEL_RESOLUTION));
          }
          return OMTB_SUCCESS;
   		
		case OMX_TI_IndexParamCompPortNotifyType:
          {
			*nConfigIndex   = enumTblVpssVfpcNfCfgParamIdx[enumCount].value;
			*pCompCfgStruct = &vpssVfpcNfConfig->sCompPortNotifyType;
            vpssVfpcNfConfig->sCompPortNotifyType.nPortIndex = portIdx;
            OMTB_SetHeader( *pCompCfgStruct,
                            sizeof(OMX_PARAM_COMPPORT_NOTIFYTYPE));

		  }
		  return OMTB_SUCCESS;
		  
		case OMX_IndexParamCompBufferSupplier:
		  {
			*nConfigIndex   = enumTblVpssVfpcNfCfgParamIdx[enumCount].value;
			*pCompCfgStruct = &vpssVfpcNfConfig->sBufSupplier;
			 vpssVfpcNfConfig->sBufSupplier.nPortIndex = portIdx;
			 OMTB_SetHeader( *pCompCfgStruct,
							 sizeof(OMX_PARAM_BUFFERSUPPLIERTYPE));
		  }
  		  return OMTB_SUCCESS;

  		case OMX_TI_IndexParamBuffMemType:
		  {
			*nConfigIndex   = enumTblVpssVfpcNfCfgParamIdx[enumCount].value;
			*pCompCfgStruct = &vpssVfpcNfConfig->sMemTypeCfg;
			 vpssVfpcNfConfig->sMemTypeCfg.nPortIndex = portIdx;
			 OMTB_SetHeader( *pCompCfgStruct,
							 sizeof(OMX_PARAM_BUFFER_MEMORYTYPE));
		  }
  		  return OMTB_SUCCESS;

        case OMX_TI_IndexConfigAlgEnable:
          {
            *nConfigIndex   = enumTblVpssVfpcNfCfgParamIdx[enumCount].value;
            *pCompCfgStruct = &vpssVfpcNfConfig->sAlgEnable;
             vpssVfpcNfConfig->sAlgEnable.nPortIndex = portIdx;
             OMTB_SetHeader( *pCompCfgStruct,
                            sizeof(OMX_CONFIG_ALG_ENABLE));
          }
          return OMTB_SUCCESS;
		
		case OMX_TI_IndexConfigSubSamplingFactor:
		  {
			*nConfigIndex   = enumTblVpssVfpcNfCfgParamIdx[enumCount].value;
			*pCompCfgStruct = &vpssVfpcNfConfig->sSubSamplingFactor;
			 vpssVfpcNfConfig->sSubSamplingFactor.nPortIndex = portIdx;
			 OMTB_SetHeader( *pCompCfgStruct,
							 sizeof(OMX_CONFIG_SUBSAMPLING_FACTOR));
		  }
  		  return OMTB_SUCCESS;
		  
		case OMX_TI_IndexParamVFPCNumChPerHandle:
		  {
			*nConfigIndex   = enumTblVpssVfpcNfCfgParamIdx[enumCount].value;
			*pCompCfgStruct = &vpssVfpcNfConfig->sNumChPerHandle;
			 vpssVfpcNfConfig->sNumChPerHandle.nPortIndex = portIdx;
			 OMTB_SetHeader( *pCompCfgStruct,
							 sizeof(OMX_PARAM_VFPC_NUMCHANNELPERHANDLE));
		  }
  		  return OMTB_SUCCESS;

		case OMX_IndexParamVideoInit:
	      {
		    *nConfigIndex   = enumTblVpssVfpcNfCfgParamIdx[enumCount].value;
		    *pCompCfgStruct = &vpssVfpcNfConfig->sPortInit;
		     OMTB_SetHeader( *pCompCfgStruct,
			      			 sizeof(OMX_PORT_PARAM_TYPE));
	      }
	      return OMTB_SUCCESS;
		  
     	case OMX_IndexParamPortDefinition:
	      {
		    *nConfigIndex   = enumTblVpssVfpcNfCfgParamIdx[enumCount].value;
		    *pCompCfgStruct = &vpssVfpcNfConfig->sPortDefType;
            vpssVfpcNfConfig->sPortDefType.nPortIndex = portIdx;			
		    OMTB_SetHeader( *pCompCfgStruct,
			   			    sizeof(OMX_PARAM_PORTDEFINITIONTYPE));
	      }
	      return OMTB_SUCCESS;
		  
		default:
          {
            return OMTB_FAIL;
          }

      } // switch(enumTblVpssVfpcNfCfgParamIdx[enumCount].value)

    } // if(0 == strcmp(enumTblVpssVfpcNfCfgParamIdx[enumCount].name, ...

    enumCount++;
  }

  return OMTB_SUCCESS;
}

/******************************************************************************\
 *      VPSSVFPCNF_FuncTsk Thread Definition
\******************************************************************************/
/**
 *
 *  @brief    This is a VPSS VFPC NF thread which invokes during func command
 *
 *  @param in:
 *            void * - Thread args count
 *
 *            void *threadsArg - Pointer to thread arg structure
 *
 *  @return   None
 *
 */

void VPSSVFPCNF_FuncTsk(void *argc, void *threadsArg)
{
//  int threadRes = TIMM_OSAL_ERR_NONE;
  OMX_ERRORTYPE err = OMX_ErrorNone;
  OMTB_VPSS_VFPC_NF_PRIVATE* vpssVfpcNfClient = NULL;
  OMTB_DATA_THREAD_ARG *funcDataThreadArg = (OMTB_DATA_THREAD_ARG *)threadsArg;
  unsigned int instanceNo = 0;
  OMTB_OMX_API_TIMING_VAR_DECL;

  /* thread argument validation */
  ASSERT(NULL != threadsArg);
  ASSERT(NULL != funcDataThreadArg->vpssVfpcNfClient);
#if 0
  vpssVfpcNfClient = funcDataThreadArg->vpssVfpcNfClient;

  PRINT(PRINT_MUST, "Entering <Thread , instance #> : <%s , %d>\n",
                     __FUNCTION__, (int)vpssVfpcNfClient->omtbPvt.instanceNo);

  PRINT(PRINT_SIMPLE_MESSAGE, "\nbufferOutSize:%d\n",\
        (int)vpssVfpcNfClient->outPortParams.cmnOutParams.bufferOutSize);

  /* Set the port params */
  err = VPSSVFPCNF_SetPortDefinition(vpssVfpcNfClient);

  if(OMX_ErrorNone != err)
  {
    OMTB_OmxReturnStatus(err);
  }

  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;

  /* send command to component to go to idle state */
  err = OMX_SendCommand(vpssVfpcNfClient->omtbPvt.handle,
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
  err = OMTB_ClientAllocateResources(vpssVfpcNfClient);

  if(OMX_ErrorNone != err)
  {
    OMTB_OmxReturnStatus(err);
  }

  /* waiting for component to go to idle state */
  TIMM_OSAL_SemaphoreObtain(vpssVfpcNfClient->omtbPvt.eventSem, TIMM_OSAL_SUSPEND);

  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;

  /* send command to component to go to executing state */
  err = OMX_SendCommand(vpssVfpcNfClient->omtbPvt.handle,
                        OMX_CommandStateSet,
                        OMX_StateExecuting,
                        NULL);

  if(OMX_ErrorNone != err)
  {
    OMTB_OmxReturnStatus(err);
  }

  /* waiting for component to go to executing state */
  TIMM_OSAL_SemaphoreObtain(vpssVfpcNfClient->omtbPvt.eventSem, TIMM_OSAL_SUSPEND);

  /* Update the func create count */
  VPSSVFPCNF_funcCreateCount++;
  PRINT(PRINT_MUST, "%s: VPSS VFPC NF FUNC Create Count: %u\n", __FUNCTION__,
                    (unsigned int) VPSSVFPCNF_funcCreateCount);

#if 0
  /* Update the data streaming thread arguments */
  strmThreadArg[vpssVfpcNfClient->omtbPvt.instanceNo].vpssVfpcNfClient = vpssVfpcNfClient;

  /* Create input data read thread */
  threadRes = TIMM_OSAL_CreateTask(
                    (void *)&vpssVfpcNfClient->inPortParams.cmnInParams.inDataStrmThrdId,
                    (TIMM_OSAL_TaskProc)VPSSVFPCNF_InputDataRead,
                    0,
                    &strmThreadArg[vpssVfpcNfClient->omtbPvt.instanceNo],
                    OMTB_VPSS_VFPC_NF_TSK_STACK_SIZE,
                    OMTB_VPSS_VFPC_NF_GROUP_PRIORITY,
                    (signed char*)"VPSS_VFPC_NF_DATA_IN_TSK");

  if(TIMM_OSAL_ERR_NONE != threadRes)
  {
    PRINT(PRINT_ERR_MSG,
          "Unable to start VPSS VFPC NF input data read thread\n");
  }

  /* Create output data write thread */
  threadRes = TIMM_OSAL_CreateTask(
                    (void *)&vpssVfpcNfClient->outPortParams.cmnOutParams.outDataStrmThrdId,
                    (TIMM_OSAL_TaskProc)VPSSVFPCNF_OutputDataWrite,
                    0,
                    &strmThreadArg[vpssVfpcNfClient->omtbPvt.instanceNo],
                    OMTB_VPSS_VFPC_NF_TSK_STACK_SIZE,
                    OMTB_VPSS_VFPC_NF_GROUP_PRIORITY,
                    (signed char*)"VPSS_VFPC_NF_DATA_OUT_TSK");

  if(TIMM_OSAL_ERR_NONE != threadRes)
  {
    PRINT(PRINT_ERR_MSG,
          "Unable to start VPSS VFPC NF output data write thread\n");
  }
#endif
  /* Wait for EOS */
  TIMM_OSAL_SemaphoreObtain(vpssVfpcNfClient->eofSem, TIMM_OSAL_SUSPEND);

  PRINT(DEFAULT_MESSAGES, "The execution of the VPSS VFPC NF \
                           process is terminated\n");

  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;

  /* state change of component from executing to idle */
  err = OMX_SendCommand(vpssVfpcNfClient->omtbPvt.handle,
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
  TIMM_OSAL_SemaphoreObtain(vpssVfpcNfClient->omtbPvt.eventSem, TIMM_OSAL_SUSPEND);

  PRINT(DEFAULT_MESSAGES, "State transitioned to Idle\n");

  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;

  /* sending command to component to go to loaded state */
  err = OMX_SendCommand(vpssVfpcNfClient->omtbPvt.handle,
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
  vpssVfpcNfClient->inPortParams.cmnInParams.flagInputEos = OMX_FALSE;
  vpssVfpcNfClient->outPortParams.cmnOutParams.flagEos = OMX_FALSE;

  /* Function to release the resources allocated by component */
  err = OMTB_ClientFreeResources(vpssVfpcNfClient);

  if(OMX_ErrorNone != err)
  {
    OMTB_OmxReturnStatus(err);
  }

  /* wait for event handler to report completion of loaded command */
  /* Temporarily commented to allow new commands after IDLE to LOADED state transition */
//  TIMM_OSAL_SemaphoreObtain(vpssVfpcNfClient->omtbPvt.eventSem, TIMM_OSAL_SUSPEND);

  PRINT(PRINT_SIMPLE_MESSAGE, "State transitioned to loaded\n");

  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;

  /* Delete the component instance */
  err = OMX_FreeHandle(vpssVfpcNfClient->omtbPvt.handle);

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
    vpssVfpcNfClient->omtbPvt.handle = NULL;
    PRINT(PRINT_MUST,
          "\r      \n\nOMTB-Deleted VPSS VFPC NF Instance #: %d\n\n",
          (int) vpssVfpcNfClient->omtbPvt.instanceNo);
    omtbClass[OMTB_VPSS_VFPC_NF_CLASS].handle[vpssVfpcNfClient->omtbPvt.instanceNo] = NULL;
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
  vpssVfpcNfClient->omtbPvt.flagThrCreated = OMX_FALSE;

  /* save the instance no to local variable */
  instanceNo = vpssVfpcNfClient->omtbPvt.instanceNo;

  /* release the memory allocated for app pvt data */
  OMTB_FreeMemory(vpssVfpcNfClient);

  /* Update the func delete count */
  VPSSVFPCNF_funcDeleteCount++;

  PRINT(PRINT_MUST, "%s: VPSS VFPC NF FUNC Delete Count: %u\n", __FUNCTION__,
                    (unsigned int) VPSSVFPCNF_funcDeleteCount);

  PRINT(PRINT_MUST, "Leaving <Thread , instance #> : <%s , %d>\n",
                     __FUNCTION__, (int)instanceNo);
#endif
  /* exit the thread */
  TIMM_OSAL_ExitTask(
      omtbClass[OMTB_VPSS_VFPC_NF_CLASS].execThreadId[instanceNo],
      NULL);
}


/******************************************************************************\
 *      VPSSVFPCNF_SetTemplateDefVal Function Definition
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

MX_Result VPSSVFPCNF_SetTemplateDefVal(OMTB_TEMPLATE_INFO *pTemplate)
{
  OMTB_VPSS_VFPC_NF_CONFIG_PARAMS *vpssHdVfpcNfCfg = NULL;

  /* param validation */
  if(NULL == pTemplate)
  {
    PRINT(PRINT_ERR_MSG, "%s: Memory for Template not allocated\n",__FUNCTION__);
    return ERR_INVNAME;
  }

  /* VPSS VFPC NF configuration */
  vpssHdVfpcNfCfg = &pTemplate->vpssVfpcNfTemplate;

  strcpy(vpssHdVfpcNfCfg->sBasicParams.inputFile, "vpssvfpc_nf_sample.yuv");
  strcpy(vpssHdVfpcNfCfg->sBasicParams.outputFile,"vpssvfpc_nf_test.yuv");
  strcpy(vpssHdVfpcNfCfg->sBasicParams.compName,   OMTB_VPSS_VFPC_NF_COMPONENT_NAME);
  vpssHdVfpcNfCfg->sBasicParams.frameWidth       = OMTB_VPSS_VFPC_NF_DEF_WIDTH;
  vpssHdVfpcNfCfg->sBasicParams.frameHeight      = OMTB_VPSS_VFPC_NF_DEF_HEIGHT;
  vpssHdVfpcNfCfg->sBasicParams.colorFormat      = OMX_COLOR_FormatYUV420SemiPlanar;
  vpssHdVfpcNfCfg->sBasicParams.inColorFormat    = OMX_COLOR_FormatYCbYCr;
  vpssHdVfpcNfCfg->sBasicParams.dataOutPutMode   = OMTB_DRIVER;
  vpssHdVfpcNfCfg->sBasicParams.dataInPutMode    = OMTB_DRIVER;  
  vpssHdVfpcNfCfg->sBasicParams.numInBuf         = OMTB_VPSS_VFPC_NF_NUM_IN_BUFS;
  vpssHdVfpcNfCfg->sBasicParams.inBufAlignment   = 0;
  vpssHdVfpcNfCfg->sBasicParams.inBufContiguous  = TIMM_OSAL_FALSE;
  vpssHdVfpcNfCfg->sBasicParams.inBufSize        = OMTB_VPSS_VFPC_NF_MAX_INBUFF_SIZE;
  vpssHdVfpcNfCfg->sBasicParams.inBufSzFlag      = OMX_FALSE;
  vpssHdVfpcNfCfg->sBasicParams.flagUseInBuffer  = OMX_FALSE;
  vpssHdVfpcNfCfg->sBasicParams.numOutBuf        = OMTB_VPSS_VFPC_NF_NUM_OUT_BUFS;
  vpssHdVfpcNfCfg->sBasicParams.outBufAlignment  = 0;
  vpssHdVfpcNfCfg->sBasicParams.outBufContiguous = TIMM_OSAL_FALSE;
  vpssHdVfpcNfCfg->sBasicParams.outBufSize       = OMTB_VPSS_VFPC_NF_MAX_OUTBUFF_SIZE;
  vpssHdVfpcNfCfg->sBasicParams.outBufSzFlag     = OMX_FALSE;
  vpssHdVfpcNfCfg->sBasicParams.flagUseOutBuffer = OMX_FALSE;
  vpssHdVfpcNfCfg->sBasicParams.compressionFormat = OMX_VIDEO_CodingUnused;
  vpssHdVfpcNfCfg->sBasicParams.fileReset        = OMX_TRUE;
  
  vpssHdVfpcNfCfg->sVidChResolutionCfg.nPortIndex = 0;
  vpssHdVfpcNfCfg->sVidChResolutionCfg.nChId      = 0;
  vpssHdVfpcNfCfg->sVidChResolutionCfg.Frm0Width  = 360;
  vpssHdVfpcNfCfg->sVidChResolutionCfg.Frm0Height = 120;
  vpssHdVfpcNfCfg->sVidChResolutionCfg.Frm0Pitch  = 1440;
  vpssHdVfpcNfCfg->sVidChResolutionCfg.eDir       = OMX_DirInput;
  vpssHdVfpcNfCfg->sVidChResolutionCfg.Frm1Width  = 0;
  vpssHdVfpcNfCfg->sVidChResolutionCfg.Frm1Height = 0;

  vpssHdVfpcNfCfg->sAlgEnable.nChId = 0;
  vpssHdVfpcNfCfg->sAlgEnable.bAlgBypass = OMX_FALSE;
  
  vpssHdVfpcNfCfg->sCompPortNotifyType.eNotifyType = OMX_NOTIFY_TYPE_ALWAYS;
  
  vpssHdVfpcNfCfg->sBufSupplier.eBufferSupplier =  OMX_BufferSupplyUnspecified;

  vpssHdVfpcNfCfg->sMemTypeCfg.eBufMemoryType = OMX_BUFFER_MEMORY_DEFAULT;
  
  vpssHdVfpcNfCfg->sSubSamplingFactor.nSubSamplingFactor = OMTB_VPSS_VFPC_NF_DEF_SUB_SAMP_FACTOR;
  vpssHdVfpcNfCfg->sNumChPerHandle.nNumChannelsPerHandle = OMTB_VPSS_VFPC_NF_DEF_NO_OF_CHAN;

  vpssHdVfpcNfCfg->sPortInit.nPorts           = OMX_VFPC_NUM_PORTS;
  vpssHdVfpcNfCfg->sPortInit.nStartPortNumber = OMX_VFPC_DEFAULT_START_PORT_NUM;

  vpssHdVfpcNfCfg->sPortDefType.eDir                               = OMX_DirInput;
  vpssHdVfpcNfCfg->sPortDefType.nBufferCountActual                 = OMTB_VPSS_VFPC_NF_NUM_IN_BUFS;
  vpssHdVfpcNfCfg->sPortDefType.nBufferCountMin                    = 1; 
  vpssHdVfpcNfCfg->sPortDefType.nBufferSize                        = OMTB_VPSS_VFPC_NF_MAX_INBUFF_SIZE;    
  vpssHdVfpcNfCfg->sPortDefType.bEnabled                           = OMX_FALSE; 
  vpssHdVfpcNfCfg->sPortDefType.bPopulated                         = OMX_FALSE; 
  vpssHdVfpcNfCfg->sPortDefType.eDomain                            = OMX_PortDomainVideo;
  vpssHdVfpcNfCfg->sPortDefType.bBuffersContiguous                 = OMX_FALSE;
  vpssHdVfpcNfCfg->sPortDefType.nBufferAlignment                   = 0;
  vpssHdVfpcNfCfg->sPortDefType.format.video.cMIMEType             = NULL;
  vpssHdVfpcNfCfg->sPortDefType.format.video.pNativeRender         = NULL;
  vpssHdVfpcNfCfg->sPortDefType.format.video.nFrameWidth           = OMTB_VPSS_VFPC_NF_DEF_WIDTH;
  vpssHdVfpcNfCfg->sPortDefType.format.video.nFrameHeight          = OMTB_VPSS_VFPC_NF_DEF_HEIGHT;
  vpssHdVfpcNfCfg->sPortDefType.format.video.nStride               = (OMTB_VPSS_VFPC_NF_DEF_WIDTH * 2);
  vpssHdVfpcNfCfg->sPortDefType.format.video.nSliceHeight          = 0;
  vpssHdVfpcNfCfg->sPortDefType.format.video.nBitrate              = 0;
  vpssHdVfpcNfCfg->sPortDefType.format.video.xFramerate            = 0;
  vpssHdVfpcNfCfg->sPortDefType.format.video.bFlagErrorConcealment = OMX_FALSE;
  vpssHdVfpcNfCfg->sPortDefType.format.video.eCompressionFormat    = OMX_VIDEO_CodingUnused;
  vpssHdVfpcNfCfg->sPortDefType.format.video.eColorFormat          = OMX_COLOR_FormatYCbYCr;
  vpssHdVfpcNfCfg->sPortDefType.format.video.pNativeWindow         = NULL;
  
  strcpy(vpssHdVfpcNfCfg->sChannelName.cChannelName, "NULL");  
  
  return ERR_NOERR;
}

OmtbRet VPSSVFPCNF_SetBufferSize(void *thisClient)
{
  OmtbRet err = OMTB_SUCCESS;
  unsigned int i = 0;
  OMTB_BASIC_CONFIG_PARAMS *pBasicConfig = NULL;
  OMTB_VPSS_VFPC_NF_PRIVATE *vpssVfpcNfClient = NULL;
  OMTB_CLIENT_INPORT_PARAMS *inPortParamsPtr = NULL;
  OMTB_CLIENT_OUTPORT_PARAMS *outPortParamsPtr = NULL;
	
  /* validate the function arguments */
  ASSERT(NULL != thisClient);
  vpssVfpcNfClient = (OMTB_VPSS_VFPC_NF_PRIVATE*)thisClient;
  pBasicConfig = &(omtbCfgTemplate[vpssVfpcNfClient->omtbPvt.templateNo]->vpssVfpcNfTemplate.sBasicParams);
  
  PRINT(PRINT_FUNCTION_NAME, "Entering <Function , instance #> : <%s , %d>\n",
                              __FUNCTION__, (int)vpssVfpcNfClient->omtbPvt.instanceNo);
  for (i =0 ; i < vpssVfpcNfClient->omtbPvt.numInport; i++)
  {
    inPortParamsPtr = vpssVfpcNfClient->inPortParams + i; 	
    
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
  
  for (i =0 ; i < vpssVfpcNfClient->omtbPvt.numOutport; i++)
  {
    outPortParamsPtr = vpssVfpcNfClient->outPortParams + i; 	
    
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
 *      VPSSVFPCNF_ClassInit Function Definition
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
OMX_ERRORTYPE VPSSVFPCNF_ClassInit(OMTB_CLIENT_PRIVATE* thisClient)
{
  OmtbRet err = OMTB_SUCCESS;
  
  PRINT(PRINT_FUNCTION_NAME, "Entering <Function> : <%s>\n",
                              __FUNCTION__);

  /* no of input / output ports */
  thisClient->omtbPvt.numInport  = OMTB_VPSS_NF_MAX_NUM_IN_PORT;
  thisClient->omtbPvt.numOutport = OMTB_VPSS_NF_MAX_NUM_OUT_PORT;
  thisClient->omtbPvt.startOutportIndex = OMTB_VPSS_NF_MAX_NUM_IN_PORT;
  
  thisClient->omtbPvt.outputDataWriteTask = OMTB_OutputDataWrite;
  thisClient->omtbPvt.inputDataReadTask = OMTB_InputDataRead;

  /* Function pointer for GetStructIdx */
  thisClient->omtbPvt.fpGetStructIdx = VPSSVFPCNF_GetStructIdx; 
  thisClient->omtbPvt.fpSetBufferSize = VPSSVFPCNF_SetBufferSize;
  thisClient->omtbPvt.fpSetPortDefinition = VPSSVFPCNF_SetPortDefinition;
  
  thisClient->omtbPvt.numFileInBufs = 0;
  thisClient->omtbPvt.numFileOutBufs = 0;
  
  thisClient->omtbPvt.readSize       = 0;
  thisClient->omtbPvt.writeSize      = 0; 	 
  
  thisClient->omtbPvt.eClassType = OMTB_VPSS_VFPC_DEI_CLASS;
  
  PRINT(PRINT_FUNCTION_NAME, "Leaving <Function> : <%s>\n",
                              __FUNCTION__);  
  return (err);							  
}
/*----------------------------- end of file ----------------------------------*/

