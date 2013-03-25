/*
 * omtbHDVPSSVfdc.c
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

#include <xdc/std.h>
#include <xdc/runtime/Assert.h>
#include <xdc/runtime/Gate.h>
#include <xdc/runtime/knl/Thread.h>
#include <xdc/runtime/Timestamp.h>

/* OMX standard header files */
#include "OMX_Core.h"
#include "OMX_Component.h"
#include "OMX_Types.h"
#include "OMX_TI_Index.h"
#include "omx_vfdc.h"
//#include "omx_vfdc_priv.h"
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

static OMX_CALLBACKTYPE VPSSVFDC_Callback = {
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

/* Pointer to VFDC config params */
OMTB_VPSS_VFDC_CONFIG_PARAMS *vpssVfdcConfig = NULL;


/******************************************************************************\
 *      Static Globals
\******************************************************************************/

static OMX_U32 VPSSVFDC_funcCreateCount = 0;  /* Func create count */
static OMX_U32 VPSSVFDC_apiCreateCount = 0;   /* API create count */

static OMX_U32 VPSSVFDC_funcDeleteCount = 0;  /* Func delete count */
static OMX_U32 VPSSVFDC_apiDeleteCount = 0;   /* API delete count */

/* Enum Entry for Supported cfg param indexs */

PRIVATE MX_DBG_ENUM_ENTRY_T enumTblVpssVfdcCfgParamIdx[] =
{
  /* ADD ENTRIES HERE for SetConfig/SetParam/GetConfig/GetParam */
  {"OMX_TI_IndexParamVFDCDriverInstId",        OMX_TI_IndexParamVFDCDriverInstId,        ""},
  {"OMX_TI_IndexConfigChannelGroupInfo",       OMX_TI_IndexConfigChannelGroupInfo,       ""},
  {"OMX_IndexParamCompBufferSupplier",         OMX_IndexParamCompBufferSupplier,         ""},
  {"OMX_TI_IndexParamBuffMemType",             OMX_TI_IndexParamBuffMemType,             ""},
  {"OMX_TI_IndexParamVFDCCreateMosaicLayout",  OMX_TI_IndexParamVFDCCreateMosaicLayout,  ""},
  {"OMX_TI_IndexConfigVFDCMosaicPort2WinMap",  OMX_TI_IndexConfigVFDCMosaicPort2WinMap,  ""},
  {"OMX_IndexParamVideoInit",                  OMX_IndexParamVideoInit,                  ""},
  {"OMTB_TI_IndexParamVFDCCreateMosaicLayout", OMTB_TI_IndexParamVFDCCreateMosaicLayout, ""},
  {"OMX_IndexParamPortDefinition",             OMX_IndexParamPortDefinition ,            ""},          
  {"OMX_TI_IndexParamVFDCCustomModeInfo",      OMX_TI_IndexParamVFDCCustomModeInfo ,     ""},       
  {"",                                         0,                                        ""}
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
 *      VPSSVFDC_SetInputPortDefinition Function Definition
\******************************************************************************/
/**
 *
 *  @brief    Set i/p port params.
 *
 *  @param in:
 *            vpssVfdcClient:Pointer to appPrivateType structure
 *
 *  @param Out:
 *            None
 *
 *  @return   OMX_ERRORTYPE - OMX std return/error code
 *
 */

OMX_ERRORTYPE VPSSVFDC_SetInputPortDefinition(OMTB_VPSS_VFDC_PRIVATE* vpssVfdcClient)
{

  OMX_ERRORTYPE err = OMX_ErrorNone;
  OMTB_OMX_API_TIMING_VAR_DECL;
  unsigned int i = 0, j;
  OMTB_CLIENT_INPORT_PARAMS *inPortParamsPtr = NULL;

  /* validate the function arguments */
  ASSERT(NULL != vpssVfdcClient);

  PRINT(PRINT_FUNCTION_NAME, "Entering <Function , instance #> : <%s , %d>\n",
                              __FUNCTION__, (int)vpssVfdcClient->omtbPvt.instanceNo);


  for(i = 0; i < vpssVfdcClient->omtbPvt.numInport ; i++)
  {
    inPortParamsPtr = vpssVfdcClient->inPortParams + i;   

   inPortParamsPtr->cmnInParams.bufferInSize   = OMTB_VPSS_VFDC_MAX_INBUFF_SIZE;

  /* Set the component's OMX_PARAM_PORTDEFINITIONTYPE structure (input) */
  OMTB_SetHeader( inPortParamsPtr->cmnInParams.pInPortDef,
                  sizeof(OMX_PARAM_PORTDEFINITIONTYPE));
	
 inPortParamsPtr->cmnInParams.pInPortDef->nPortIndex         =
                                  (OMX_VFDC_INPUT_PORT_START_INDEX + i);

    /* API entry time calculation macro */
    OMTB_OMX_API_ENTRY_TIME_CALC;

    /*Get the OutPort Definition*/
    err = OMX_GetParameter( vpssVfdcClient->omtbPvt.handle,
                            OMX_IndexParamPortDefinition,
                            inPortParamsPtr->cmnInParams.pInPortDef);

    /* API exit time calculation macro */
    OMTB_OMX_API_EXIT_TIME_CALC("OMX_GetParameter");


    inPortParamsPtr->cmnInParams.pInPortDef->eDir                = OMX_DirInput;

	inPortParamsPtr->cmnInParams.pInPortDef->nBufferCountActual  =
                                  inPortParamsPtr->cmnInParams.numInBuf;
    inPortParamsPtr->cmnInParams.pInPortDef->nBufferCountMin     = 1;
#if 0    
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
    inPortParamsPtr->cmnInParams.pInPortDef->format.video.eCompressionFormat =
                                  vpssVfdcClient->compressionFormat;
    inPortParamsPtr->cmnInParams.pInPortDef->format.video.eColorFormat =
                                  inPortParamsPtr->colorFormat;

    /* API entry time calculation macro */
    OMTB_OMX_API_ENTRY_TIME_CALC;

    /*Set the inPort Definition*/
    err = OMX_SetParameter( vpssVfdcClient->omtbPvt.handle,
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
                              __FUNCTION__, (int)vpssVfdcClient->omtbPvt.instanceNo);

  return err;
}


/******************************************************************************\
 *      VPSSVFDC_SetPortDefinition Function Definition
\******************************************************************************/
/**
 *
 *  @brief    Set i/o port params.
 *
 *  @param in:
 *            vpssVfdcClient:Pointer to appPrivateType structure
 *
 *  @param Out:
 *            None
 *
 *  @return   OMX_ERRORTYPE - OMX std return/error code
 *
 */

OMX_ERRORTYPE VPSSVFDC_SetPortDefinition(void* thisClient)
{

  OMX_ERRORTYPE err = OMX_ErrorNone;
//  OMX_PORT_PARAM_TYPE portInit;
  OMTB_OMX_API_TIMING_VAR_DECL;
  OMTB_VPSS_VFDC_PRIVATE* vpssVfdcClient = (OMTB_VPSS_VFDC_PRIVATE*) thisClient;
  
  /* validate the function arguments */
  ASSERT(NULL != vpssVfdcClient);

  PRINT(PRINT_FUNCTION_NAME, "Entering <Function , instance #> : <%s , %d>\n",
                              __FUNCTION__, (int)vpssVfdcClient->omtbPvt.instanceNo);
#if 0
  /* Set the component's OMX_PARAM_PORTDEFINITIONTYPE structure (input) */
  OMTB_SetHeader(&portInit,sizeof(OMX_PORT_PARAM_TYPE));
  portInit.nPorts = 2;
  portInit.nStartPortNumber = 0;

  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;

  /* Initialize the Port*/
  err = OMX_SetParameter( vpssVfdcClient->omtbPvt.handle,
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
  err = VPSSVFDC_SetInputPortDefinition(vpssVfdcClient);
  if(OMX_ErrorNone != err)
  {
    PRINT(PRINT_ERR_MSG, "Error in setting i/p port params\n");
    OMTB_OmxReturnStatus(err);
  }


  PRINT(PRINT_FUNCTION_NAME, "Leaving <Function , instance #> : <%s , %d>\n",
                              __FUNCTION__, (int)vpssVfdcClient->omtbPvt.instanceNo);
  return err;
}

/******************************************************************************\
 *      VPSSVFDC_SetSymmetricMosaicFormat Function Definition
\******************************************************************************/
/**
 *
 *  @brief    Set mosaic params.
 *
 *  @param in:
 *            vpssVfdcClient:Pointer to appPrivateType structure
 *
 *  @param Out:
 *            None
 *
 *  @return   OMX_ERRORTYPE - OMX std return/error code
 *
 */

OMX_ERRORTYPE VPSSVFDC_SetSymmetricMosaicFormat(OMX_HANDLETYPE handle, OMTB_VPSS_VFDC_MOSAIC_PARAMS* vpssVfdcMosaicParams,
                                                OMTB_VFDC_MOSAIC_WINDOW_CONFIG mosaicDemo)
{
  OMX_ERRORTYPE err = OMX_ErrorNone;
  UInt32 row = 0, col = 0;
  UInt32 hGap = 0, vGap = 0;
  UInt32 winStartX = 0, winStartY = 0;
  OMX_VFDC_MultipleWindowFmt *winFmt = NULL;
  OMTB_OMX_API_TIMING_VAR_DECL;
  
//FIXME: The first if case has hard-coded values which has be removed later,
//       it has been added for 45-day VC demo use case
   /*Set the display for VC- use case*/
  if(OMTB_VC_DEMO == mosaicDemo)
  {
    winFmt = &( vpssVfdcMosaicParams->sMosaicLayout.sMosaicWinFmt[0u] );

    /*---------------------------------------------------------------------------*
     * Configure the first window
     *--------------------------------------------------------------------------*/
    winFmt->winStartX = vpssVfdcMosaicParams->winStartX;;
    winFmt->winStartY = vpssVfdcMosaicParams->winStartY;;
    winFmt->winWidth =  vpssVfdcMosaicParams->winWidth;
    winFmt->winHeight = vpssVfdcMosaicParams->winHeight;
	winFmt->pitch[VFDC_YUV_SP_Y_ADDR_IDX] = vpssVfdcMosaicParams->pitchVFDC_YUV_SP_Y_ADDR_IDX;
    winFmt->pitch[VFDC_YUV_SP_CBCR_ADDR_IDX] =  vpssVfdcMosaicParams->pitchVFDC_YUV_SP_CBCR_ADDR_IDX;
    winFmt->dataFormat = vpssVfdcMosaicParams->dataFormat;
    winFmt->bpp = vpssVfdcMosaicParams->bpp;
    winFmt->priority = vpssVfdcMosaicParams->priority;
    winFmt++;

  /*---------------------------------------------------------------------------*
   * Configure the second window
   *--------------------------------------------------------------------------*/
    winFmt->winStartX = vpssVfdcMosaicParams->winWidth;
    winFmt->winStartY = 180;
    winFmt->winWidth =  640;//pVfdcCfg->nWinWidth1;
    winFmt->winHeight = 360;//pVfdcCfg->nWinHeight1;
    winFmt->pitch[VFDC_YUV_SP_Y_ADDR_IDX] = vpssVfdcMosaicParams->pitchVFDC_YUV_SP_Y_ADDR_IDX;
    winFmt->pitch[VFDC_YUV_SP_CBCR_ADDR_IDX] =  vpssVfdcMosaicParams->pitchVFDC_YUV_SP_CBCR_ADDR_IDX;
    winFmt->dataFormat = vpssVfdcMosaicParams->dataFormat;
    winFmt->bpp = vpssVfdcMosaicParams->bpp;
    winFmt->priority = vpssVfdcMosaicParams->priority;

    vpssVfdcMosaicParams->sMosaicLayout.nDisChannelNum = 0u;
    vpssVfdcMosaicParams->sMosaicLayout.nNumWindows = vpssVfdcMosaicParams->numRows
                                                      * vpssVfdcMosaicParams->numCols;
  }
  /* Set the single window display for SD */
#if 0  
  else if ( vpssVfdcMosaicParams->dispWindowWidth == 720) 
  {
    wFmt = &( vpssVfdcMosaicParams->sMosaicLayout.sMosaicWinFmt[0u] );

    wFmt->winStartX = 0;
    wFmt->winStartY = 0;
    wFmt->winWidth = vpssVfdcMosaicParams->winWidth;
    wFmt->winHeight = vpssVfdcMosaicParams->winHeight;

    wFmt->pitch[VFDC_YUV_SP_Y_ADDR_IDX] = vpssVfdcMosaicParams->framePitchY420SP;
    wFmt->pitch[VFDC_YUV_SP_CBCR_ADDR_IDX] =  vpssVfdcMosaicParams->framePitchUV420SP;
    wFmt->dataFormat = VFDC_DF_YUV420SP_UV;
    wFmt->bpp =  VFDC_BPP_BITS16;
    wFmt->priority = 0u;
    vpssVfdcMosaicParams->sMosaicLayout.nDisChannelNum = 0u;
    vpssVfdcMosaicParams->sMosaicLayout.nNumWindows = 1;

  }
#endif
  else if (OMTB_VS_DEMO == mosaicDemo)
  {
    /* Set the 3x4 (12) window mosaic format for HD display */
    {
      winFmt = &( (&(vpssVfdcMosaicParams->sMosaicLayout))->sMosaicWinFmt[0u] );

     /*---------------------------------------------------------------------------*
      * Calculate the vertical Gap between the windows
      *--------------------------------------------------------------------------*/
      vGap = ( vpssVfdcMosaicParams->dispWindowHeight
             - ( vpssVfdcMosaicParams->numRows * vpssVfdcMosaicParams->winHeight ) )
             / ( 2u * vpssVfdcMosaicParams->numRows );
      winStartY = vpssVfdcMosaicParams->winStartX;

      /*---------------------------------------------------------------------------*
       * In each rows start from top to botteom Arrange
       * the windows from left to right
       *--------------------------------------------------------------------------*/
       for ( row = 0u; row < vpssVfdcMosaicParams->numRows; row++ )  {
         winStartY += vGap;
         winStartX = vpssVfdcMosaicParams->winStartY;

        /*-------------------------------------------------------------------------*
         * Calculate & add the horizontal Gap between the windows
         *------------------------------------------------------------------------*/
         hGap = ( vpssVfdcMosaicParams->dispWindowWidth
                - ( vpssVfdcMosaicParams->numCols * vpssVfdcMosaicParams->winWidth ) )
                / ( 2u * vpssVfdcMosaicParams->numCols );

         for ( col = 0u; col < vpssVfdcMosaicParams->numCols; col++ ){
           winStartX += hGap;
           winFmt->winStartX = winStartX;
           winFmt->winStartY = winStartY;
           winFmt->winWidth = vpssVfdcMosaicParams->winWidth;
           winFmt->winHeight = vpssVfdcMosaicParams->winHeight;
           winFmt->pitch[VFDC_YUV_INT_ADDR_IDX] =   vpssVfdcMosaicParams->pitchVFDC_YUV_INT_ADDR_IDX;
		   winFmt->pitch[VFDC_YUV_SP_Y_ADDR_IDX] =  vpssVfdcMosaicParams->pitchVFDC_YUV_SP_Y_ADDR_IDX;
		   winFmt->pitch[VFDC_YUV_SP_CBCR_ADDR_IDX] = vpssVfdcMosaicParams->pitchVFDC_YUV_SP_CBCR_ADDR_IDX;
           winFmt->dataFormat = vpssVfdcMosaicParams->dataFormat;
           winFmt->bpp = vpssVfdcMosaicParams->bpp;
           winFmt->priority = vpssVfdcMosaicParams->priority;

           winStartX += ( hGap + vpssVfdcMosaicParams->winWidth);
           winFmt++;
         }

        /*-------------------------------------------------------------------------*
         * Add the verical gap & window height to get the next verical start
         *------------------------------------------------------------------------*/
         winStartY += ( vGap + vpssVfdcMosaicParams->winHeight);
      }

      (&(vpssVfdcMosaicParams->sMosaicLayout))->nDisChannelNum = 0u;
      vpssVfdcMosaicParams->sMosaicLayout.nNumWindows = vpssVfdcMosaicParams->numRows
                                                      * vpssVfdcMosaicParams->numCols;
    }
  }
  /*Manual Mosaic configuration for each window */
  else
  {
      (&(vpssVfdcMosaicParams->sMosaicLayout))->nDisChannelNum = 0u;
      vpssVfdcMosaicParams->sMosaicLayout.nNumWindows = vpssVfdcMosaicParams->numRows
                                                      * vpssVfdcMosaicParams->numCols;
  }													  

  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;

  /* set the given mosaic configuration with appropriate layout ID */
  err = OMX_SetParameter ( handle,
                         ( OMX_INDEXTYPE ) OMX_TI_IndexParamVFDCCreateMosaicLayout,
                         &(vpssVfdcMosaicParams->sMosaicLayout) );

  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_SetParameter");
  
  /* print the values of this index on output console/file */
  OMTB_DisplaySetParams(OMX_TI_IndexParamVFDCCreateMosaicLayout,  &(vpssVfdcMosaicParams->sMosaicLayout));  

  if(OMX_ErrorNone != err)
  {
    OMTB_OmxReturnStatus(err);
  }

  return err;
}


/******************************************************************************\
 *      VPSSVFDC_GetStructIdx Function Definition
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

OmtbRet VPSSVFDC_GetStructIdx(
  char *indexStr,
  unsigned int template,
  unsigned int instanceNo,  
  unsigned int portIdx,
  unsigned int *nConfigIndex,
  void **pCompCfgStruct)
{
  unsigned int enumCount = 0;

  /* Use the specified template structure */
  vpssVfdcConfig = (OMTB_VPSS_VFDC_CONFIG_PARAMS*)
                     &(omtbCfgTemplate[template]->vpssVfdcTemplate);

  /* Get the corresponding string for enum values from enum table
     Set structure index
     Set structure pointer
     Set port index for which parameter to be updated
     Set structure header info */
  while(strcmp(enumTblVpssVfdcCfgParamIdx[enumCount].name , ""))
  {
    if(0 == strcmp(enumTblVpssVfdcCfgParamIdx[enumCount].name,
                   indexStr))
    {
      switch(enumTblVpssVfdcCfgParamIdx[enumCount].value)
      {
        /* ADD Similar implementation below for supported indexes */
        case OMX_TI_IndexParamVFDCDriverInstId:
          {
            *nConfigIndex   = enumTblVpssVfdcCfgParamIdx[enumCount].value;
            *pCompCfgStruct = &vpssVfdcConfig->sDvrInstId;
            vpssVfdcConfig->sDvrInstId.nPortIndex = 0;
            OMTB_SetHeader( *pCompCfgStruct,
                            sizeof(OMX_PARAM_VFDC_DRIVERINSTID));
          }
          return OMTB_SUCCESS;

        case OMX_TI_IndexConfigChannelGroupInfo:
          {
            *nConfigIndex   = enumTblVpssVfdcCfgParamIdx[enumCount].value;
            *pCompCfgStruct = &vpssVfdcConfig->sConfigChannelGroupInfo;
//            vpssVfdcConfig->sConfigChannelGroupInfo.nPortIndex = portIdx;
            OMTB_SetHeader( *pCompCfgStruct,
                            sizeof(OMX_CONFIG_CHANNELGROUPINFO));
          }
          return OMTB_SUCCESS;

        case OMX_IndexParamCompBufferSupplier:
          {
            *nConfigIndex   = enumTblVpssVfdcCfgParamIdx[enumCount].value;
            *pCompCfgStruct = &vpssVfdcConfig->sBufSupplier;
            vpssVfdcConfig->sBufSupplier.nPortIndex = portIdx;
            OMTB_SetHeader( *pCompCfgStruct,
                            sizeof(OMX_PARAM_BUFFERSUPPLIERTYPE));
          }
          return OMTB_SUCCESS;

		case OMX_TI_IndexParamBuffMemType:
		  {
			*nConfigIndex   = enumTblVpssVfdcCfgParamIdx[enumCount].value;
			*pCompCfgStruct = &vpssVfdcConfig->sMemTypeCfg;
			 vpssVfdcConfig->sMemTypeCfg.nPortIndex = portIdx;
			 OMTB_SetHeader( *pCompCfgStruct,
							 sizeof(OMX_PARAM_BUFFER_MEMORYTYPE));
		  }
  		  return OMTB_SUCCESS;

        case OMX_TI_IndexParamVFDCCreateMosaicLayout:
          {
            *nConfigIndex   = enumTblVpssVfdcCfgParamIdx[enumCount].value;
            *pCompCfgStruct = &vpssVfdcConfig->sMosaicParams;
            vpssVfdcConfig->sMosaicParams.sMosaicLayout.nPortIndex = portIdx;
			/* Special case to handle mosaic configuration */
			OMTB_SetHeader((void *)&vpssVfdcConfig->sMosaicParams.sMosaicLayout,
							 sizeof(OMX_PARAM_VFDC_CREATEMOSAICLAYOUT));
          }
          return OMTB_SUCCESS;

        case OMX_TI_IndexConfigVFDCMosaicPort2WinMap:
          {
            *nConfigIndex   = enumTblVpssVfdcCfgParamIdx[enumCount].value;
            *pCompCfgStruct = &vpssVfdcConfig->sLayoutIndex;
            vpssVfdcConfig->sLayoutIndex.nPortIndex = portIdx;
			OMTB_SetHeader( *pCompCfgStruct,
							 sizeof(OMX_CONFIG_VFDC_MOSAICLAYOUT_PORT2WINMAP));
          }
          return OMTB_SUCCESS;

     	case OMX_IndexParamVideoInit:
	      {
		    *nConfigIndex   = enumTblVpssVfdcCfgParamIdx[enumCount].value;
		    *pCompCfgStruct = &vpssVfdcConfig->sPortInit;
		    OMTB_SetHeader( *pCompCfgStruct,
			   			    sizeof(OMX_PORT_PARAM_TYPE));
	      }
	      return OMTB_SUCCESS;
        
		/* OMTB Index used for mosaic window configuration */ 		  
		case OMTB_TI_IndexParamVFDCCreateMosaicLayout:
	      {
		    *nConfigIndex   = enumTblVpssVfdcCfgParamIdx[enumCount].value;
	      }
	      return OMTB_SUCCESS;

     	case OMX_IndexParamPortDefinition:
	      {
		    *nConfigIndex   = enumTblVpssVfdcCfgParamIdx[enumCount].value;
		    *pCompCfgStruct = &vpssVfdcConfig->sPortDefType;
            vpssVfdcConfig->sPortDefType.nPortIndex = portIdx;			
		    OMTB_SetHeader( *pCompCfgStruct,
			   			    sizeof(OMX_PARAM_PORTDEFINITIONTYPE));
	      }
	      return OMTB_SUCCESS;
		  
     	case OMX_TI_IndexParamVFDCCustomModeInfo:
	      {
		    *nConfigIndex   = enumTblVpssVfdcCfgParamIdx[enumCount].value;
		    *pCompCfgStruct = &vpssVfdcConfig->sCustomModeInfo;
            vpssVfdcConfig->sCustomModeInfo.nPortIndex = portIdx;			
		    OMTB_SetHeader( *pCompCfgStruct,
			   			    sizeof(OMX_PARAM_DC_CUSTOM_MODE_INFO));
	      }
	      return OMTB_SUCCESS;
		  
        default:
          {
            return OMTB_FAIL;
          }

      } // switch(enumTblVpssVfdcCfgParamIdx[enumCount].value)

    } // if(0 == strcmp(enumTblVpssVfdcCfgParamIdx[enumCount].name, ...

    enumCount++;
  }

  return OMTB_SUCCESS;
}


/******************************************************************************\
 *      VPSSVFDC_FuncTsk Thread Definition
\******************************************************************************/
/**
 *
 *  @brief    This is a VPSS VFDC thread which invokes during func command
 *
 *  @param in:
 *            void * - Thread args count
 *
 *            void *threadsArg - Pointer to thread arg structure
 *
 *  @return   None
 *
 */

void VPSSVFDC_FuncTsk(void *argc, void *threadsArg)
{
//  int threadRes = TIMM_OSAL_ERR_NONE;
  OMX_ERRORTYPE err = OMX_ErrorNone;
  OMTB_VPSS_VFDC_PRIVATE* vpssVfdcClient = NULL;
  OMTB_DATA_THREAD_ARG *funcDataThreadArg = (OMTB_DATA_THREAD_ARG *)threadsArg;
  unsigned int instanceNo = 0;
  OMTB_CLIENT_INPORT_PARAMS *inPortParamsPtr = NULL;
  unsigned int j = 0;  
  OMTB_OMX_API_TIMING_VAR_DECL;

  /* thread argument validation */
  ASSERT(NULL != threadsArg);
  ASSERT(NULL != funcDataThreadArg->vpssVfdcClient);

  vpssVfdcClient = funcDataThreadArg->vpssVfdcClient;

  PRINT(PRINT_MUST, "Entering <Thread , instance #> : <%s , %d>\n",
                     __FUNCTION__, (int)vpssVfdcClient->omtbPvt.instanceNo);

  /* Set the port params */
  err = VPSSVFDC_SetPortDefinition(vpssVfdcClient);

  if(OMX_ErrorNone != err)
  {
    OMTB_OmxReturnStatus(err);
  }

  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;

  /* send command to component to go to idle state */
  err = OMX_SendCommand(vpssVfdcClient->omtbPvt.handle,
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
  err = OMTB_ClientAllocateResources(vpssVfdcClient);

  if(OMX_ErrorNone != err)
  {
    OMTB_OmxReturnStatus(err);
  }

  /* waiting for component to go to idle state */
  TIMM_OSAL_SemaphoreObtain(vpssVfdcClient->omtbPvt.eventSem, TIMM_OSAL_SUSPEND);

  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;

  /* send command to component to go to executing state */
  err = OMX_SendCommand(vpssVfdcClient->omtbPvt.handle,
                        OMX_CommandStateSet,
                        OMX_StateExecuting,
                        NULL);

  if(OMX_ErrorNone != err)
  {
    OMTB_OmxReturnStatus(err);
  }

  /* waiting for component to go to executing state */
  TIMM_OSAL_SemaphoreObtain(vpssVfdcClient->omtbPvt.eventSem, TIMM_OSAL_SUSPEND);

  /* Update the func create count */
  VPSSVFDC_funcCreateCount++;
  PRINT(PRINT_MUST, "%s: VPSS VFDC FUNC Create Count: %u\n", __FUNCTION__,
                    (unsigned int) VPSSVFDC_funcCreateCount);

#if 0
  /* Update the data streaming thread arguments */
  strmThreadArg[vpssVfdcClient->omtbPvt.instanceNo].vpssVfdcClient = vpssVfdcClient;

  /* Create input data read thread */
  threadRes = TIMM_OSAL_CreateTask(
                    (void *)&inPortParamsPtr->cmnInParams.inDataStrmThrdId,
                    (TIMM_OSAL_TaskProc)VPSSVFDC_InputDataRead,
                    0,
                    &strmThreadArg[vpssVfdcClient->omtbPvt.instanceNo],
                    OMTB_VPSS_VFDC_TSK_STACK_SIZE,
                    OMTB_VPSS_VFDC_GROUP_PRIORITY,
                    (signed char*)"VPSS_VFDC_DATA_IN_TSK");

  if(TIMM_OSAL_ERR_NONE != threadRes)
  {
    PRINT(PRINT_ERR_MSG,
          "Unable to start VPSS VFDC input data read thread\n");
  }

#endif
  /* Wait for EOS */
  TIMM_OSAL_SemaphoreObtain(vpssVfdcClient->eofSem, TIMM_OSAL_SUSPEND);

  PRINT(DEFAULT_MESSAGES, "The execution of the video display\
                           process is terminated\n");

  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;

  /* state change of component from executing to idle */
  err = OMX_SendCommand(vpssVfdcClient->omtbPvt.handle,
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
  TIMM_OSAL_SemaphoreObtain(vpssVfdcClient->omtbPvt.eventSem, TIMM_OSAL_SUSPEND);

  PRINT(DEFAULT_MESSAGES, "State transitioned to Idle\n");

  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;

  /* sending command to component to go to loaded state */
  err = OMX_SendCommand(vpssVfdcClient->omtbPvt.handle,
                        OMX_CommandStateSet,
                        OMX_StateLoaded,
                        NULL);

  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_SendCommand");

  if(OMX_ErrorNone != err)
  {
    OMTB_OmxReturnStatus(err);
  }

  for (j =0 ; j < OMTB_VPSS_VFDC_MAX_NUM_IN_PORT ; j++) {
    inPortParamsPtr = vpssVfdcClient->inPortParams + j; 
  /* Reset the EOS indication flag */
    inPortParamsPtr->cmnInParams.flagInputEos = OMX_FALSE;
  }	
  

  /* Function to Release the resources allocated by component */
  err = OMTB_ClientFreeResources(vpssVfdcClient);

  if(OMX_ErrorNone != err)
  {
    OMTB_OmxReturnStatus(err);
  }

  /*wait for event handler to report completion of loaded command */
  TIMM_OSAL_SemaphoreObtain(vpssVfdcClient->omtbPvt.eventSem, TIMM_OSAL_SUSPEND);

  PRINT(PRINT_SIMPLE_MESSAGE, "State transitioned to loaded\n");

  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;

  /* Delete the component instance */
  err = OMX_FreeHandle(vpssVfdcClient->omtbPvt.handle);

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
    vpssVfdcClient->omtbPvt.handle = NULL;
    PRINT(PRINT_MUST,
          "\r      \n\nOMTB-Deleted VPSS VFDC Instance #: %d\n\n",
          (int) vpssVfdcClient->omtbPvt.instanceNo);
    omtbClass[OMTB_VPSS_VFDC_CLASS].handle[vpssVfdcClient->omtbPvt.instanceNo] = NULL;
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
  vpssVfdcClient->omtbPvt.flagThrCreated = OMX_FALSE;

  /* save the instance no to local variable */
  instanceNo = vpssVfdcClient->omtbPvt.instanceNo;

  /* Release the memory allocated for app pvt data */
  OMTB_FreeMemory(vpssVfdcClient);

  /* Update the func delete count */
  VPSSVFDC_funcDeleteCount++;

  PRINT(PRINT_MUST, "%s: VPSS VFDC FUNC Delete Count: %u\n", __FUNCTION__,
                    (unsigned int) VPSSVFDC_funcDeleteCount);

  PRINT(PRINT_MUST, "Leaving <Thread , instance #> : <%s , %d>\n",
                     __FUNCTION__, (int)instanceNo);

  /* exit the thread */
  TIMM_OSAL_ExitTask(
      omtbClass[OMTB_VPSS_VFDC_CLASS].execThreadId[instanceNo],
      NULL);
}

/******************************************************************************\
 *      VPSSVFDC_SetTemplateDefVal Function Definition
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

MX_Result VPSSVFDC_SetTemplateDefVal(OMTB_TEMPLATE_INFO *pTemplate)
{
  OMTB_VPSS_VFDC_CONFIG_PARAMS *vpssHdVfdcCfg = NULL;

  /* param validation */
  if(NULL == pTemplate)
  {
    PRINT(PRINT_ERR_MSG, "%s: Memory for Template not allocated\n",__FUNCTION__);
    return ERR_INVNAME;
  }

  /* VPSS VFDC configuration */
  vpssHdVfdcCfg = &pTemplate->vpssVfdcTemplate;

  strcpy(vpssHdVfdcCfg->sBasicParams.inputFile, "vpssvfdc_sample.yuv");
  strcpy(vpssHdVfdcCfg->sBasicParams.outputFile,"vpssvfdc_test.yuv");
  strcpy(vpssHdVfdcCfg->sBasicParams.compName,   OMTB_VPSS_VFDC_COMPONENT_NAME);
  vpssHdVfdcCfg->sBasicParams.frameWidth         = OMTB_VPSS_VFDC_DEF_WIDTH;
  vpssHdVfdcCfg->sBasicParams.frameHeight        = OMTB_VPSS_VFDC_DEF_HEIGHT;
  vpssHdVfdcCfg->sBasicParams.colorFormat        = OMX_COLOR_FormatYCbYCr;
  vpssHdVfdcCfg->sBasicParams.inColorFormat      = OMX_COLOR_FormatYCbYCr;
  vpssHdVfdcCfg->sBasicParams.dataOutPutMode     = OMTB_DRIVER;
  vpssHdVfdcCfg->sBasicParams.dataInPutMode      = OMTB_DRIVER;
  vpssHdVfdcCfg->sBasicParams.numInBuf           = OMTB_VPSS_VFDC_NUM_IN_BUFS;
  vpssHdVfdcCfg->sBasicParams.inBufAlignment     = 0;
  vpssHdVfdcCfg->sBasicParams.inBufContiguous    = TIMM_OSAL_FALSE;
  vpssHdVfdcCfg->sBasicParams.inBufSize          = OMTB_VPSS_VFDC_MAX_INBUFF_SIZE;
  vpssHdVfdcCfg->sBasicParams.inBufSzFlag        = OMX_FALSE;
  vpssHdVfdcCfg->sBasicParams.flagUseInBuffer    = OMX_FALSE;
  vpssHdVfdcCfg->sBasicParams.compressionFormat  = OMX_VIDEO_CodingUnused;
  vpssHdVfdcCfg->sBasicParams.graphicsFlag       = OMX_FALSE;
  vpssHdVfdcCfg->sBasicParams.fileReset          = OMX_TRUE;
  
  vpssHdVfdcCfg->sDvrInstId.nDrvInstID = OMX_VIDEO_DISPLAY_ID_HD0;
  vpssHdVfdcCfg->sDvrInstId.eDispVencMode = OMX_DC_MODE_1080P_60;

  vpssHdVfdcCfg->sBufSupplier.eBufferSupplier =  OMX_BufferSupplyUnspecified;
  vpssHdVfdcCfg->sMemTypeCfg.eBufMemoryType = OMX_BUFFER_MEMORY_DEFAULT;
  
  vpssHdVfdcCfg->sMosaicParams.winStartX                      = 0;
  vpssHdVfdcCfg->sMosaicParams.winStartY                      = 0;
  vpssHdVfdcCfg->sMosaicParams.winWidth                       = 320;
  vpssHdVfdcCfg->sMosaicParams.winHeight                      = 240;
  vpssHdVfdcCfg->sMosaicParams.pitchVFDC_YUV_INT_ADDR_IDX     = 1440;
  vpssHdVfdcCfg->sMosaicParams.pitchVFDC_YUV_SP_Y_ADDR_IDX    = 720;
  vpssHdVfdcCfg->sMosaicParams.pitchVFDC_YUV_SP_CBCR_ADDR_IDX = 720;
  vpssHdVfdcCfg->sMosaicParams.dataFormat                     = VFDC_DF_YUV422I_YUYV;
  vpssHdVfdcCfg->sMosaicParams.bpp                            = VFDC_BPP_BITS16;  
  vpssHdVfdcCfg->sMosaicParams.priority                       = 0;
  
  vpssHdVfdcCfg->sMosaicParams.windowId                       = 0;
  vpssHdVfdcCfg->sMosaicParams.dispWindowWidth                = 1920;
  vpssHdVfdcCfg->sMosaicParams.dispWindowHeight               = 1080;
  vpssHdVfdcCfg->sMosaicParams.numRows                        = 4;
  vpssHdVfdcCfg->sMosaicParams.numCols                        = 5;

  vpssHdVfdcCfg->sLayoutIndex.nLayoutId = 0;

  vpssHdVfdcCfg->mosaicDemoConfig = OMTB_MANUAL;

  vpssHdVfdcCfg->sPortInit.nPorts           = OMTB_VPSS_VFDC_DEF_NO_OF_PORTS;
  vpssHdVfdcCfg->sPortInit.nStartPortNumber = OMX_VFDC_DEFAULT_START_PORT_NUM;
  
  vpssHdVfdcCfg->sPortDefType.eDir                               = OMX_DirInput;
  vpssHdVfdcCfg->sPortDefType.nBufferCountActual                 = OMTB_VPSS_VFDC_NUM_IN_BUFS;
  vpssHdVfdcCfg->sPortDefType.nBufferCountMin                    = 1; 
  vpssHdVfdcCfg->sPortDefType.nBufferSize                        = OMTB_VPSS_VFDC_MAX_INBUFF_SIZE;    
  vpssHdVfdcCfg->sPortDefType.bEnabled                           = OMX_FALSE; 
  vpssHdVfdcCfg->sPortDefType.bPopulated                         = OMX_FALSE; 
  vpssHdVfdcCfg->sPortDefType.eDomain                            = OMX_PortDomainVideo;
  vpssHdVfdcCfg->sPortDefType.bBuffersContiguous                 = OMX_FALSE;
  vpssHdVfdcCfg->sPortDefType.nBufferAlignment                   = 0;
  vpssHdVfdcCfg->sPortDefType.format.video.cMIMEType             = NULL;
  vpssHdVfdcCfg->sPortDefType.format.video.pNativeRender         = NULL;
  vpssHdVfdcCfg->sPortDefType.format.video.nFrameWidth           = OMTB_VPSS_VFDC_DEF_WIDTH;
  vpssHdVfdcCfg->sPortDefType.format.video.nFrameHeight          = OMTB_VPSS_VFDC_DEF_HEIGHT;
  vpssHdVfdcCfg->sPortDefType.format.video.nStride               = (OMTB_VPSS_VFDC_DEF_WIDTH * 2);
  vpssHdVfdcCfg->sPortDefType.format.video.nSliceHeight          = 0;
  vpssHdVfdcCfg->sPortDefType.format.video.nBitrate              = 0;
  vpssHdVfdcCfg->sPortDefType.format.video.xFramerate            = 0;
  vpssHdVfdcCfg->sPortDefType.format.video.bFlagErrorConcealment = OMX_FALSE;
  vpssHdVfdcCfg->sPortDefType.format.video.eCompressionFormat    = OMX_VIDEO_CodingUnused;
  vpssHdVfdcCfg->sPortDefType.format.video.eColorFormat          = OMX_COLOR_FormatYCbYCr;
  vpssHdVfdcCfg->sPortDefType.format.video.pNativeWindow         = NULL;
 
  vpssHdVfdcCfg->sCustomModeInfo.width        = OMTB_VPSS_VFDC_DEF_WIDTH;
  vpssHdVfdcCfg->sCustomModeInfo.height       = OMTB_VPSS_VFDC_DEF_HEIGHT;
  vpssHdVfdcCfg->sCustomModeInfo.scanFormat   = OMX_SF_PROGRESSIVE;
  vpssHdVfdcCfg->sCustomModeInfo.pixelClock   = 0;
  vpssHdVfdcCfg->sCustomModeInfo.fps          = 0;
  vpssHdVfdcCfg->sCustomModeInfo.hFrontPorch  = 0;
  vpssHdVfdcCfg->sCustomModeInfo.hBackPorch   = 0;
  vpssHdVfdcCfg->sCustomModeInfo.hSyncLen     = 0;
  vpssHdVfdcCfg->sCustomModeInfo.vFrontPorch  = 0;
  vpssHdVfdcCfg->sCustomModeInfo.vBackPorch   = 0 ;
  vpssHdVfdcCfg->sCustomModeInfo.vSyncLen     = 0;
 
  return ERR_NOERR;
}

OmtbRet VPSSVFDC_SetBufferSize(void *thisClient)
{
  OmtbRet err = OMTB_SUCCESS;
  unsigned int i = 0;
  OMTB_BASIC_CONFIG_PARAMS *pBasicConfig = NULL;
  OMTB_VPSS_VFDC_PRIVATE *vpssVfdcClient = NULL;
  OMTB_CLIENT_INPORT_PARAMS *inPortParamsPtr = NULL;
	
  /* validate the function arguments */
  ASSERT(NULL != thisClient);
  vpssVfdcClient = (OMTB_VPSS_VFDC_PRIVATE*)thisClient;
  pBasicConfig = &(omtbCfgTemplate[vpssVfdcClient->omtbPvt.templateNo]->vpssVfdcTemplate.sBasicParams);
  
  vpssVfdcClient->graphicsFlag = pBasicConfig->graphicsFlag; 
  
  PRINT(PRINT_FUNCTION_NAME, "Entering <Function , instance #> : <%s , %d>\n",
                              __FUNCTION__, (int)vpssVfdcClient->omtbPvt.instanceNo);
  for (i =0 ; i < vpssVfdcClient->omtbPvt.numInport; i++)
  {
    inPortParamsPtr = vpssVfdcClient->inPortParams + i; 	
    
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
          PRINT(PRINT_MUST, "Undefined chroma format:%d Setting o/p buffer size \
according to 422P format.\n", inPortParamsPtr->colorFormat);
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
  
  PRINT(PRINT_FUNCTION_NAME, "Leaving <Function #> : <%s>\n",
                             __FUNCTION__);  
  return err;
}

/******************************************************************************\
 *      VPSSVFDC_ClassInit Function Definition
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
OMX_ERRORTYPE VPSSVFDC_ClassInit(OMTB_CLIENT_PRIVATE* thisClient)
{
  OmtbRet err = OMTB_SUCCESS;
  
  PRINT(PRINT_FUNCTION_NAME, "Entering <Function> : <%s>\n",
                              __FUNCTION__);
							  
  /* no of input / output ports */
  thisClient->omtbPvt.numInport  = 1; //OMTB_VPSS_VFDC_MAX_NUM_IN_PORT;
  thisClient->omtbPvt.numOutport = 0;
  thisClient->omtbPvt.startOutportIndex = 0;
  
  thisClient->omtbPvt.outputDataWriteTask = NULL;
  thisClient->omtbPvt.inputDataReadTask = OMTB_InputDataRead;

  /* Function pointer for GetStructIdx */
  thisClient->omtbPvt.fpGetStructIdx = VPSSVFDC_GetStructIdx; 
  thisClient->omtbPvt.fpSetBufferSize = VPSSVFDC_SetBufferSize;
  thisClient->omtbPvt.fpSetPortDefinition = VPSSVFDC_SetPortDefinition;
	
  thisClient->omtbPvt.numFileInBufs = OMTB_CLIENT_MAX_NUM_FILE_IN_BUFS;
  thisClient->omtbPvt.numFileOutBufs = 0;
  
  thisClient->omtbPvt.readSize       = OMTB_VPSS_VFDC_MAX_INBUFF_SIZE;
  thisClient->omtbPvt.writeSize      = 0; 	 
  
  thisClient->omtbPvt.eClassType = OMTB_VPSS_VFDC_CLASS;
  
  PRINT(PRINT_FUNCTION_NAME, "Leaving <Function> : <%s>\n",
                              __FUNCTION__);  
  return (err);							  
}
/*----------------------------- end of file ----------------------------------*/

