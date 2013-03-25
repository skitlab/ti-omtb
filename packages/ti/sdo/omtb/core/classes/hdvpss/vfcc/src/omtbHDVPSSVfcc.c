/*
 * omtbHDVPSSVfcc.c
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
#include "omx_vfcc.h"
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

static OMX_CALLBACKTYPE VPSSVFCC_Callback = {
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


/******************************************************************************\
 *      Globals
\******************************************************************************/

/* Pointer to VFCC config params */
OMTB_VPSS_VFCC_CONFIG_PARAMS *vpssVfccConfig = NULL;


/******************************************************************************\
 *      Static Globals
\******************************************************************************/

static OMX_U32 VPSSVFCC_funcCreateCount = 0;  /* Func create count */
static OMX_U32 VPSSVFCC_apiCreateCount = 0;   /* API create count */

static OMX_U32 VPSSVFCC_funcDeleteCount = 0;  /* Func delete count */
static OMX_U32 VPSSVFCC_apiDeleteCount = 0;   /* API delete count */

/* Enum Entry for Supported cfg param indexs */

PRIVATE MX_DBG_ENUM_ENTRY_T enumTblVpssVfccCfgParamIdx[] =
{
  /* ADD ENTRIES HERE for SetConfig/SetParam/GetConfig/GetParam */
  {"OMX_TI_IndexConfigChannelName",         OMX_TI_IndexConfigChannelName,         ""},
  {"OMX_TI_IndexConfigChannelGroupInfo",    OMX_TI_IndexConfigChannelGroupInfo,    ""},
  {"OMX_IndexParamCompBufferSupplier",      OMX_IndexParamCompBufferSupplier,      ""},
  {"OMX_TI_IndexParamBuffMemType",          OMX_TI_IndexParamBuffMemType,          ""},
  {"OMX_TI_IndexParamVFCCHwPortProperties", OMX_TI_IndexParamVFCCHwPortProperties, ""},
  {"OMX_TI_IndexParamVFCCHwPortID",         OMX_TI_IndexParamVFCCHwPortID,         ""},
  {"OMX_TI_IndexConfigVFCCFrameSkip",       OMX_TI_IndexConfigVFCCFrameSkip,       ""},
  {"OMX_IndexParamDupPorts",                OMX_IndexParamDupPorts,                ""},
  {"OMX_IndexParamVideoInit",               OMX_IndexParamVideoInit,               ""},
  {"OMX_IndexConfigVFCCPortStats",          OMX_IndexConfigVFCCPortStats,          ""},
  {"OMX_IndexConfigVFCCPortResetStats",     OMX_IndexConfigVFCCPortResetStats,     ""}, 
  {"OMX_IndexParamPortDefinition",          OMX_IndexParamPortDefinition,          ""}, 
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
 *      VPSSVFCC_SetOutputPortDefinition Function Definition
\******************************************************************************/
/**
 *
 *  @brief    Set o/p port params.
 *
 *  @param in:
 *            vpssVfccClient:Pointer to appPrivateType structure
 *
 *  @param Out:
 *            None
 *
 *  @return   OMX_ERRORTYPE - OMX std return/error code
 *
 */

OMX_ERRORTYPE VPSSVFCC_SetOutputPortDefinition(OMTB_VPSS_VFCC_PRIVATE* vpssVfccClient)
{
  OMTB_CLIENT_OUTPORT_PARAMS *outPortParamsPtr;
  OMX_ERRORTYPE err = OMX_ErrorNone;
  OMTB_OMX_API_TIMING_VAR_DECL;
  unsigned int i = 0;

  /* validate the function arguments */
  ASSERT(NULL != vpssVfccClient);

  PRINT(PRINT_FUNCTION_NAME, "Entering <Function , instance #> : <%s , %d>\n",
                              __FUNCTION__, (int)vpssVfccClient->omtbPvt.instanceNo);
  /*
  if(OMX_FALSE == outPortParamsPtr->cmnOutParams.outBufSzFlag)
  {
    outPortParamsPtr->cmnOutParams.bufferOutSize =
                      (outPortParamsPtr->nWidth *\
                      outPortParamsPtr->nHeight * 2) + 288;
  }
  */
  for (i =0 ; i < vpssVfccClient->omtbPvt.numOutport ; i++)
  {
    outPortParamsPtr = vpssVfccClient->outPortParams + i; 
    
	OMTB_SetHeader( outPortParamsPtr->cmnOutParams.pOutPortDef,
                  sizeof(OMX_PARAM_PORTDEFINITIONTYPE));   
				  
	/* Set the component's OMX_PARAM_PORTDEFINITIONTYPE structure (output) */
    outPortParamsPtr->cmnOutParams.pOutPortDef->nPortIndex         =
                                  (OMX_VFCC_OUTPUT_PORT_START_INDEX + i);

    /* API entry time calculation macro */
    OMTB_OMX_API_ENTRY_TIME_CALC;

    /*Get the OutPort Definition*/
    err = OMX_GetParameter( vpssVfccClient->omtbPvt.handle,
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
    outPortParamsPtr->cmnOutParams.pOutPortDef->format.video.eCompressionFormat =
                                  vpssVfccClient->compressionFormat;
    outPortParamsPtr->cmnOutParams.pOutPortDef->format.video.eColorFormat =
                                  outPortParamsPtr->colorFormat;

	  outPortParamsPtr->cmnOutParams.pOutPortDef->format.video.nFrameWidth =
                                  outPortParamsPtr->nWidth;

    outPortParamsPtr->cmnOutParams.pOutPortDef->format.video.nFrameHeight =
                                  outPortParamsPtr->nHeight;
    
  // As VFCC is a real time OMX component, EOS is not applicable here.    
    outPortParamsPtr->cmnOutParams.flagEos = OMX_FALSE;
    
	if ((outPortParamsPtr->colorFormat == OMX_COLOR_FormatYUV420Planar)       ||
        (outPortParamsPtr->colorFormat == OMX_COLOR_FormatYUV420PackedPlanar) ||
        (outPortParamsPtr->colorFormat == OMX_COLOR_FormatYUV420SemiPlanar)   ||
        (outPortParamsPtr->colorFormat == OMX_COLOR_FormatYUV420PackedSemiPlanar))
    {
      outPortParamsPtr->cmnOutParams.pOutPortDef->format.video.nStride =
                      outPortParamsPtr->cmnOutParams.pOutPortDef->format.video.nFrameWidth;
    }
    else 
	if( (outPortParamsPtr->colorFormat == OMX_COLOR_FormatYCbYCr)       ||
             (outPortParamsPtr->colorFormat == OMX_COLOR_FormatYCrYCb)       ||
             (outPortParamsPtr->colorFormat == OMX_COLOR_FormatCbYCrY)       ||
             (outPortParamsPtr->colorFormat == OMX_COLOR_FormatCrYCbY))
    {
      outPortParamsPtr->cmnOutParams.pOutPortDef->format.video.nStride =
                      outPortParamsPtr->cmnOutParams.pOutPortDef->format.video.nFrameWidth * 2;
    }

    /* API entry time calculation macro */
    OMTB_OMX_API_ENTRY_TIME_CALC;

    /*Set the OutPort Definition*/
    err = OMX_SetParameter( vpssVfccClient->omtbPvt.handle,
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
                                __FUNCTION__, (int)vpssVfccClient->omtbPvt.instanceNo);
  return err;
}


/******************************************************************************\
 *      VPSSVFCC_SetPortDefinition Function Definition
\******************************************************************************/
/**
 *
 *  @brief    Set i/o port params.
 *
 *  @param in:
 *            vpssVfccClient:Pointer to appPrivateType structure
 *
 *  @param Out:
 *            None
 *
 *  @return   OMX_ERRORTYPE - OMX std return/error code
 *
 */

OMX_ERRORTYPE VPSSVFCC_SetPortDefinition(void* thisClient)
{
  OMX_ERRORTYPE err = OMX_ErrorNone;
//  OMX_PORT_PARAM_TYPE portInit;
  OMTB_OMX_API_TIMING_VAR_DECL;

  OMTB_VPSS_VFCC_PRIVATE* vpssVfccClient = (OMTB_VPSS_VFCC_PRIVATE*)thisClient;
  /* validate the function arguments */
  ASSERT(NULL != vpssVfccClient);

  PRINT(PRINT_FUNCTION_NAME, "Entering <Function , instance #> : <%s , %d>\n",
                              __FUNCTION__, (int)vpssVfccClient->omtbPvt.instanceNo);
#if 0
  /* Set the component's OMX_PARAM_PORTDEFINITIONTYPE structure (input) */
  OMTB_SetHeader(&portInit,sizeof(OMX_PORT_PARAM_TYPE));
  portInit.nPorts = 2;
  portInit.nStartPortNumber = 0;

  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;

  /* Initialize the Port*/
  err = OMX_SetParameter( vpssVfccClient->omtbPvt.handle,
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

  /* set the o/p port params */
  err = VPSSVFCC_SetOutputPortDefinition(vpssVfccClient);
  if(OMX_ErrorNone != err)
  {
    PRINT(PRINT_ERR_MSG, "Error in setting o/p port params\n");
    OMTB_OmxReturnStatus(err);
  }

  PRINT(PRINT_FUNCTION_NAME, "Leaving <Function , instance #> : <%s , %d>\n",
                              __FUNCTION__, (int)vpssVfccClient->omtbPvt.instanceNo);

  return err;
}

/******************************************************************************\
 *      VPSSVFCC_GetStructIdx Function Definition
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

OmtbRet VPSSVFCC_GetStructIdx(
  char *indexStr,
  unsigned int template,
  unsigned int instanceNo,  
  unsigned int portIdx,
  unsigned int *nConfigIndex,
  void **pCompCfgStruct)
{
  unsigned int enumCount = 0;
  char channelName[OMX_MAX_STRINGNAME_SIZE] = {'0'};         /* Capture channel name */

  /* Use the specified template structure */
  vpssVfccConfig = (OMTB_VPSS_VFCC_CONFIG_PARAMS*)
                     &(omtbCfgTemplate[template]->vpssVfccTemplate);

  /* Get the corresponding string for enum values from enum table
     Set structure index
     Set structure pointer
     Set port index for which parameter to be updated
     Set structure header info */
  while(strcmp(enumTblVpssVfccCfgParamIdx[enumCount].name , ""))
  {
    if(0 == strcmp(enumTblVpssVfccCfgParamIdx[enumCount].name,
                   indexStr))
    {
      switch(enumTblVpssVfccCfgParamIdx[enumCount].value)
      {

        case OMX_TI_IndexConfigChannelName:
          {

            *nConfigIndex   = enumTblVpssVfccCfgParamIdx[enumCount].value;
            *pCompCfgStruct = &vpssVfccConfig->sChannelName;
            vpssVfccConfig->sChannelName.nPortIndex = portIdx;
            
/* FIXME:  To support backword compatability with the older omtb scripts,
           the following code has not been removed, 
*/		   
//            if(!strcmp("NULL", vpssVfccConfig->sChannelName.cChannelName))			
			{
            snprintf(channelName, OMX_MAX_STRINGNAME_SIZE, "FQ_VFCCOUT_%d",
                     portIdx);
            channelName[OMX_MAX_STRINGNAME_SIZE - 1] = '\0';
			DOMX_UTL_Strncpy ( ( char * ) vpssVfccConfig->sChannelName.cChannelName, channelName,
					  sizeof ( vpssVfccConfig->sChannelName.cChannelName ) );
			}

            OMTB_SetHeader( *pCompCfgStruct,
                            sizeof(OMX_CONFIG_CHANNELNAME));
          }
          return OMTB_SUCCESS;

        case OMX_TI_IndexConfigChannelGroupInfo:
          {
            *nConfigIndex   = enumTblVpssVfccCfgParamIdx[enumCount].value;
            *pCompCfgStruct = &vpssVfccConfig->sConfigChannelGroupInfo;
//            vpssVfccConfig->sConfigChannelGroupInfo.nPortIndex = portIdx;
            OMTB_SetHeader( *pCompCfgStruct,
                            sizeof(OMX_CONFIG_CHANNELGROUPINFO));
          }
          return OMTB_SUCCESS;

		case OMX_IndexParamCompBufferSupplier:
		  {
			*nConfigIndex   = enumTblVpssVfccCfgParamIdx[enumCount].value;
			*pCompCfgStruct = &vpssVfccConfig->sBufSupplier;
			 vpssVfccConfig->sBufSupplier.nPortIndex = portIdx;
			 OMTB_SetHeader( *pCompCfgStruct,
							 sizeof(OMX_PARAM_BUFFERSUPPLIERTYPE));
		  }
  		  return OMTB_SUCCESS;

		case OMX_TI_IndexParamBuffMemType:
		  {
			*nConfigIndex   = enumTblVpssVfccCfgParamIdx[enumCount].value;
			*pCompCfgStruct = &vpssVfccConfig->sMemTypeCfg;
			 vpssVfccConfig->sMemTypeCfg.nPortIndex = portIdx;
			 OMTB_SetHeader( *pCompCfgStruct,
							 sizeof(OMX_PARAM_BUFFER_MEMORYTYPE));
		  }
  		  return OMTB_SUCCESS;

		case OMX_TI_IndexParamVFCCHwPortProperties:
		  {
			*nConfigIndex   = enumTblVpssVfccCfgParamIdx[enumCount].value;
			*pCompCfgStruct = &vpssVfccConfig->sHwPortParam;
			 vpssVfccConfig->sHwPortParam.nPortIndex = portIdx;
			 OMTB_SetHeader( *pCompCfgStruct,
							 sizeof(OMX_PARAM_VFCC_HWPORT_PROPERTIES));
		  }
  		  return OMTB_SUCCESS;

		case OMX_TI_IndexParamVFCCHwPortID:
		  {
			*nConfigIndex   = enumTblVpssVfccCfgParamIdx[enumCount].value;
			*pCompCfgStruct = &vpssVfccConfig->sHwPortId;
			 vpssVfccConfig->sHwPortId.nPortIndex = portIdx;
			 OMTB_SetHeader( *pCompCfgStruct,
							 sizeof(OMX_PARAM_VFCC_HWPORT_ID));
		  }
  		  return OMTB_SUCCESS;

		case OMX_TI_IndexConfigVFCCFrameSkip:
		  {
			*nConfigIndex   = enumTblVpssVfccCfgParamIdx[enumCount].value;
			*pCompCfgStruct = &vpssVfccConfig->sCapSkipFrames;
			 vpssVfccConfig->sCapSkipFrames.nPortIndex = portIdx;
			 OMTB_SetHeader( *pCompCfgStruct,
							 sizeof(OMX_CONFIG_VFCC_FRAMESKIP_INFO));
		  }
  		  return OMTB_SUCCESS;
		
		case OMX_IndexParamDupPorts:
		  {
			*nConfigIndex   = enumTblVpssVfccCfgParamIdx[enumCount].value;
			*pCompCfgStruct = &vpssVfccConfig->sDupPortInfo;
			 vpssVfccConfig->sDupPortInfo.nPortIndex = portIdx;
			 OMTB_SetHeader( *pCompCfgStruct,
							 sizeof(OMX_PARAM_DUPEPORTSINFO));
		  }
  		  return OMTB_SUCCESS;

        case OMX_IndexParamVideoInit:
	      {
		    *nConfigIndex   = enumTblVpssVfccCfgParamIdx[enumCount].value;
		    *pCompCfgStruct = &vpssVfccConfig->sPortInit;
		     OMTB_SetHeader( *pCompCfgStruct,
			    			sizeof(OMX_PORT_PARAM_TYPE));
	      }
	      return OMTB_SUCCESS;

        case OMX_IndexConfigVFCCPortStats:
	      {
		    *nConfigIndex   = enumTblVpssVfccCfgParamIdx[enumCount].value;
		    *pCompCfgStruct = &vpssVfccConfig->sCapStats;
		     OMTB_SetHeader( *pCompCfgStruct,
			    			sizeof(OMX_PARAM_VIDEO_CAPTURE_STATS));
	      }	
	      return OMTB_SUCCESS;
		  
        case OMX_IndexConfigVFCCPortResetStats:
	      {
		    *nConfigIndex   = enumTblVpssVfccCfgParamIdx[enumCount].value;
		    *pCompCfgStruct = &vpssVfccConfig->sCapResetStats;
		     OMTB_SetHeader( *pCompCfgStruct,
			    			sizeof(OMX_CONFIG_VIDEO_CAPTURE_RESET_STATS));
	      }		
	      return OMTB_SUCCESS;		  

	    case OMX_IndexParamPortDefinition:
	      {
		    *nConfigIndex   = enumTblVpssVfccCfgParamIdx[enumCount].value;
		    *pCompCfgStruct = &vpssVfccConfig->sPortDefType;
            vpssVfccConfig->sPortDefType.nPortIndex = portIdx;			
		    OMTB_SetHeader( *pCompCfgStruct,
			   			    sizeof(OMX_PARAM_PORTDEFINITIONTYPE));
	      }
	      return OMTB_SUCCESS;
		  
        default:
          {
            return OMTB_FAIL;
          }

      } // switch(enumTblVpssVfccCfgParamIdx[enumCount].value)

    } // if(0 == strcmp(enumTblVpssVfccCfgParamIdx[enumCount].name, ...

    enumCount++;
  }

  return OMTB_SUCCESS;
}


/******************************************************************************\
 *      VPSSVFCC_FuncTsk Thread Definition
\******************************************************************************/
/**
 *
 *  @brief    This is a VPSS VFCC thread which invokes during func command
 *
 *  @param in:
 *            void * - Thread args count
 *
 *            void *threadsArg - Pointer to thread arg structure
 *
 *  @return   None
 *
 */

void VPSSVFCC_FuncTsk(void *argc, void *threadsArg)
{
  int threadRes = TIMM_OSAL_ERR_NONE;
  OMX_ERRORTYPE err = OMX_ErrorNone;
  OMTB_VPSS_VFCC_PRIVATE* vpssVfccClient = NULL;
  OMTB_DATA_THREAD_ARG *funcDataThreadArg = (OMTB_DATA_THREAD_ARG *)threadsArg;
  unsigned int instanceNo = 0;
  OMTB_OMX_API_TIMING_VAR_DECL;
  OMTB_CLIENT_OUTPORT_PARAMS *outPortParamsPtr;
  int i;
  /* thread argument validation */
  ASSERT(NULL != threadsArg);
  ASSERT(NULL != funcDataThreadArg->vpssVfccClient);

  vpssVfccClient = funcDataThreadArg->vpssVfccClient;

  PRINT(PRINT_MUST, "Entering <Thread , instance #> : <%s , %d>\n",
                     __FUNCTION__, (int)vpssVfccClient->omtbPvt.instanceNo);

   for (i =0 ; i < OMTB_VPSS_VFCC_MAX_NUM_OUT_PORT ; i++) {
   outPortParamsPtr = vpssVfccClient->outPortParams + i; 

  PRINT(PRINT_SIMPLE_MESSAGE, "\nbufferOutSize:%d\n",\
        (int)outPortParamsPtr->cmnOutParams.bufferOutSize);
   }
  /* Set the port params */
  err = VPSSVFCC_SetPortDefinition(vpssVfccClient);

  if(OMX_ErrorNone != err)
  {
    OMTB_OmxReturnStatus(err);
  }

  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;

  /* send command to component to go to idle state */
  err = OMX_SendCommand(vpssVfccClient->omtbPvt.handle,
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
  err = OMTB_ClientAllocateResources(vpssVfccClient);

  if(OMX_ErrorNone != err)
  {
    OMTB_OmxReturnStatus(err);
  }

  /* waiting for component to go to idle state */
  TIMM_OSAL_SemaphoreObtain(vpssVfccClient->omtbPvt.eventSem, TIMM_OSAL_SUSPEND);

  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;

  /* send command to component to go to executing state */
  err = OMX_SendCommand(vpssVfccClient->omtbPvt.handle,
                        OMX_CommandStateSet,
                        OMX_StateExecuting,
                        NULL);

  if(OMX_ErrorNone != err)
  {
    OMTB_OmxReturnStatus(err);
  }

  /* waiting for component to go to executing state */
  TIMM_OSAL_SemaphoreObtain(vpssVfccClient->omtbPvt.eventSem, TIMM_OSAL_SUSPEND);

  /* Update the func create count */
  VPSSVFCC_funcCreateCount++;
  PRINT(PRINT_MUST, "%s: VPSS VFCC FUNC Create Count: %u\n", __FUNCTION__,
                    (unsigned int) VPSSVFCC_funcCreateCount);


  /* Update the data streaming thread arguments */
  strmThreadArg[vpssVfccClient->omtbPvt.instanceNo].vpssVfccClient = vpssVfccClient;

  /* Create output data write thread */
  threadRes = TIMM_OSAL_CreateTask(
                    (void *)&outPortParamsPtr->cmnOutParams.outDataStrmThrdId,
                    (TIMM_OSAL_TaskProc)OMTB_OutputDataWrite,
                    0,
                    &strmThreadArg[vpssVfccClient->omtbPvt.instanceNo],
                    OMTB_VPSS_VFCC_TSK_STACK_SIZE,
                    OMTB_VPSS_VFCC_GROUP_PRIORITY,
                    (signed char*)"VPSS_VFCC_DATA_OUT_TSK");

  if(TIMM_OSAL_ERR_NONE != threadRes)
  {
    PRINT(PRINT_ERR_MSG,
          "Unable to start VPSS VFCC output data write thread\n");
  }

  /* Wait for EOS */
  TIMM_OSAL_SemaphoreObtain(vpssVfccClient->eofSem, TIMM_OSAL_SUSPEND);

  PRINT(DEFAULT_MESSAGES, "The execution of the VPSS VFCC capture\
                           process is terminated\n");

  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;

  /* state change of component from executing to idle */
  err = OMX_SendCommand(vpssVfccClient->omtbPvt.handle,
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
  TIMM_OSAL_SemaphoreObtain(vpssVfccClient->omtbPvt.eventSem, TIMM_OSAL_SUSPEND);

  PRINT(DEFAULT_MESSAGES, "State transitioned to Idle\n");

  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;

  /* sending command to component to go to loaded state */
  err = OMX_SendCommand(vpssVfccClient->omtbPvt.handle,
                        OMX_CommandStateSet,
                        OMX_StateLoaded,
                        NULL);

  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_SendCommand");

  if(OMX_ErrorNone != err)
  {
    OMTB_OmxReturnStatus(err);
  }
   for (i =0 ; i < OMTB_VPSS_VFCC_MAX_NUM_OUT_PORT ; i++) {
   outPortParamsPtr = vpssVfccClient->outPortParams + i; 
  /* Reset the EOS indication flag */
  outPortParamsPtr->cmnOutParams.flagEos = OMX_FALSE;
  }
  /* Function to release the resources allocated by component */
  err = OMTB_ClientFreeResources(vpssVfccClient);

  if(OMX_ErrorNone != err)
  {
    OMTB_OmxReturnStatus(err);
  }

  /* wait for event handler to report completion of loaded command */
  /* Temporarily commented to allow new commands after IDLE to LOADED state transition */
//  TIMM_OSAL_SemaphoreObtain(vpssVfccClient->omtbPvt.eventSem, TIMM_OSAL_SUSPEND);

  PRINT(PRINT_SIMPLE_MESSAGE, "State transitioned to loaded\n");

  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;

  /* Delete the component instance */
  err = OMX_FreeHandle(vpssVfccClient->omtbPvt.handle);

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
    vpssVfccClient->omtbPvt.handle = NULL;
    PRINT(PRINT_MUST,
          "\r      \n\nOMTB-Deleted VPSS VFCC Instance #: %d\n\n",
          (int) vpssVfccClient->omtbPvt.instanceNo);
    omtbClass[OMTB_VPSS_VFCC_CLASS].handle[vpssVfccClient->omtbPvt.instanceNo] = NULL;
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
  vpssVfccClient->omtbPvt.flagThrCreated = OMX_FALSE;

  /* save the instance no to local variable */
  instanceNo = vpssVfccClient->omtbPvt.instanceNo;

  /* release the memory allocated for app pvt data */
  OMTB_FreeMemory(vpssVfccClient);

  /* Update the func delete count */
  VPSSVFCC_funcDeleteCount++;

  PRINT(PRINT_MUST, "%s: VPSS VFCC FUNC Delete Count: %u\n", __FUNCTION__,
                    (unsigned int) VPSSVFCC_funcDeleteCount);

  PRINT(PRINT_MUST, "Leaving <Thread , instance #> : <%s , %d>\n",
                     __FUNCTION__, (int)instanceNo);

  /* exit the thread */
  TIMM_OSAL_ExitTask(
      omtbClass[OMTB_VPSS_VFCC_CLASS].execThreadId[instanceNo],
      NULL);
}

/******************************************************************************\
 *      VPSSVFCC_SetTemplateDefVal Function Definition
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

MX_Result VPSSVFCC_SetTemplateDefVal(OMTB_TEMPLATE_INFO *pTemplate)
{
  OMTB_VPSS_VFCC_CONFIG_PARAMS *vpssHdVfccCfg = NULL;

  /* param validation */
  if(NULL == pTemplate)
  {
    PRINT(PRINT_ERR_MSG, "%s: Memory for Template not allocated\n",__FUNCTION__);
    return ERR_INVNAME;
  }

  /* VPSS VFCC configuration */
  vpssHdVfccCfg = &pTemplate->vpssVfccTemplate;

  strcpy(vpssHdVfccCfg->sBasicParams.inputFile, "vpssvfcc_sample.yuv");
  strcpy(vpssHdVfccCfg->sBasicParams.outputFile,"vpssvfcc_test.yuv");
  strcpy(vpssHdVfccCfg->sBasicParams.compName,   OMTB_VPSS_VFCC_COMPONENT_NAME);

  vpssHdVfccCfg->sBasicParams.frameWidth       = OMTB_VPSS_VFCC_DEF_WIDTH;
  vpssHdVfccCfg->sBasicParams.frameHeight      = OMTB_VPSS_VFCC_DEF_HEIGHT;
  vpssHdVfccCfg->sBasicParams.colorFormat      = OMX_COLOR_FormatYCbYCr;
  vpssHdVfccCfg->sBasicParams.dataOutPutMode   = OMTB_DRIVER;

  vpssHdVfccCfg->sBasicParams.numOutBuf        = OMTB_VPSS_VFCC_NUM_OUT_BUFS;
  vpssHdVfccCfg->sBasicParams.outBufAlignment  = 0;
  vpssHdVfccCfg->sBasicParams.outBufContiguous = TIMM_OSAL_FALSE;
  vpssHdVfccCfg->sBasicParams.outBufSize       = OMTB_VPSS_VFCC_MAX_OUTBUFF_SIZE;
  vpssHdVfccCfg->sBasicParams.outBufSzFlag     = OMX_FALSE;
  vpssHdVfccCfg->sBasicParams.flagUseOutBuffer = OMX_FALSE;
  vpssHdVfccCfg->sBasicParams.compressionFormat = OMX_VIDEO_CodingUnused;
  
  vpssHdVfccCfg->sMemTypeCfg.eBufMemoryType   = OMX_BUFFER_MEMORY_DEFAULT;
  vpssHdVfccCfg->sBufSupplier.eBufferSupplier =  OMX_BufferSupplyUnspecified;

  vpssHdVfccCfg->sHwPortParam.eCaptMode          = OMX_VIDEO_CaptureModeMC_LINE_MUX;
  vpssHdVfccCfg->sHwPortParam.eVifMode           = OMX_VIDEO_CaptureVifMode_08BIT;
  vpssHdVfccCfg->sHwPortParam.eInColorFormat     = OMX_COLOR_FormatYCbYCr;
  vpssHdVfccCfg->sHwPortParam.eScanType          = OMX_VIDEO_CaptureScanTypeInterlaced;
  vpssHdVfccCfg->sHwPortParam.nMaxHeight         = OMTB_VPSS_VFCC_DEF_HEIGHT;
  vpssHdVfccCfg->sHwPortParam.nMaxWidth          = OMTB_VPSS_VFCC_DEF_WIDTH;
  vpssHdVfccCfg->sHwPortParam.nMaxChnlsPerHwPort = OMTB_VPSS_VIDEO_CAPTURE_MAX_CHNLS;

  vpssHdVfccCfg->sHwPortId.eHwPortId = OMX_VIDEO_CaptureHWPortALL_PORTS;

  vpssHdVfccCfg->sCapSkipFrames.frameSkipMask = OMTB_VPSS_VFCC_DEF_FRAME_SKIP_MASK;

  vpssHdVfccCfg->sPortInit.nPorts           = OMTB_VPSS_VFCC_DEF_NO_OF_PORTS;
  vpssHdVfccCfg->sPortInit.nStartPortNumber = OMX_VFCC_DEFAULT_START_PORT_NUM;

  vpssHdVfccCfg->sPortDefType.eDir                               = OMX_DirOutput;
  vpssHdVfccCfg->sPortDefType.nBufferCountActual                 = OMTB_VPSS_VFCC_NUM_OUT_BUFS;
  vpssHdVfccCfg->sPortDefType.nBufferCountMin                    = 1; 
  vpssHdVfccCfg->sPortDefType.nBufferSize                        = OMTB_VPSS_VFCC_MAX_OUTBUFF_SIZE;    
  vpssHdVfccCfg->sPortDefType.bEnabled                           = OMX_FALSE; 
  vpssHdVfccCfg->sPortDefType.bPopulated                         = OMX_FALSE; 
  vpssHdVfccCfg->sPortDefType.eDomain                            = OMX_PortDomainVideo;
  vpssHdVfccCfg->sPortDefType.bBuffersContiguous                 = OMX_FALSE;
  vpssHdVfccCfg->sPortDefType.nBufferAlignment                   = 0;
  vpssHdVfccCfg->sPortDefType.format.video.cMIMEType             = NULL;
  vpssHdVfccCfg->sPortDefType.format.video.pNativeRender         = NULL;
  vpssHdVfccCfg->sPortDefType.format.video.nFrameWidth           = OMTB_VPSS_VFCC_DEF_WIDTH;
  vpssHdVfccCfg->sPortDefType.format.video.nFrameHeight          = OMTB_VPSS_VFCC_DEF_HEIGHT;
  vpssHdVfccCfg->sPortDefType.format.video.nStride               = (OMTB_VPSS_VFCC_DEF_WIDTH * 2);
  vpssHdVfccCfg->sPortDefType.format.video.nSliceHeight          = 0;
  vpssHdVfccCfg->sPortDefType.format.video.nBitrate              = 0;
  vpssHdVfccCfg->sPortDefType.format.video.xFramerate            = 0;
  vpssHdVfccCfg->sPortDefType.format.video.bFlagErrorConcealment = OMX_FALSE;
  vpssHdVfccCfg->sPortDefType.format.video.eCompressionFormat    = OMX_VIDEO_CodingUnused;
  vpssHdVfccCfg->sPortDefType.format.video.eColorFormat          = OMX_COLOR_FormatYCbYCr;
  vpssHdVfccCfg->sPortDefType.format.video.pNativeWindow         = NULL;
  
  strcpy(vpssHdVfccCfg->sChannelName.cChannelName, "NULL");
  
  return ERR_NOERR;
}

OmtbRet VPSSVFCC_SetBufferSize(void *thisClient)
{
  OmtbRet err = OMTB_SUCCESS;
  unsigned int i = 0;
  OMTB_BASIC_CONFIG_PARAMS *pBasicConfig = NULL;
  OMTB_VPSS_VFCC_PRIVATE *vpssVfccClient = NULL;
  OMTB_CLIENT_OUTPORT_PARAMS *outPortParamsPtr = NULL;
	
  /* validate the function arguments */
  ASSERT(NULL != thisClient);
  vpssVfccClient = (OMTB_VPSS_VFCC_PRIVATE*)thisClient;
  pBasicConfig = &(omtbCfgTemplate[vpssVfccClient->omtbPvt.templateNo]->vpssVfccTemplate.sBasicParams);

  
  PRINT(PRINT_FUNCTION_NAME, "Entering <Function , instance #> : <%s , %d>\n",
                              __FUNCTION__, (int)vpssVfccClient->omtbPvt.instanceNo);
  for (i =0 ; i < vpssVfccClient->omtbPvt.numOutport; i++)
  {
    outPortParamsPtr = vpssVfccClient->outPortParams + i; 	
    
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
 *      VPSSVFCC_ClassInit Function Definition
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
OMX_ERRORTYPE VPSSVFCC_ClassInit(OMTB_CLIENT_PRIVATE* thisClient)
{
  OmtbRet err = OMTB_SUCCESS;
  
  PRINT(PRINT_FUNCTION_NAME, "Entering <Function> : <%s>\n",
                              __FUNCTION__);
							  
  /* no of input / output ports */
  thisClient->omtbPvt.numInport  = 0;
  thisClient->omtbPvt.numOutport = 1; //OMTB_VPSS_VFCC_MAX_NUM_OUT_PORT;
  thisClient->omtbPvt.startOutportIndex = 0;
  
  thisClient->omtbPvt.outputDataWriteTask = OMTB_OutputDataWrite;
  thisClient->omtbPvt.inputDataReadTask = NULL;

  /* Function pointer for GetStructIdx */
  thisClient->omtbPvt.fpGetStructIdx = VPSSVFCC_GetStructIdx; 
  thisClient->omtbPvt.fpSetBufferSize = VPSSVFCC_SetBufferSize;
  thisClient->omtbPvt.fpSetPortDefinition = VPSSVFCC_SetPortDefinition;
	
  thisClient->omtbPvt.numFileInBufs = 0;
  thisClient->omtbPvt.numFileOutBufs = OMTB_CLIENT_MAX_NUM_FILE_OUT_BUFS;
  
  thisClient->omtbPvt.readSize       = 0;
  thisClient->omtbPvt.writeSize      = OMTB_VPSS_VFCC_MAX_OUTBUFF_SIZE; 	 
  
  thisClient->omtbPvt.eClassType = OMTB_VPSS_VFCC_CLASS;
	
  PRINT(PRINT_FUNCTION_NAME, "Leaving <Function> : <%s>\n",
                              __FUNCTION__);  
  return (err);							  
}
/*----------------------------- end of file ----------------------------------*/
