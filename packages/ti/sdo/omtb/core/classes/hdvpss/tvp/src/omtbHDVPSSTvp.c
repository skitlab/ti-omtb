/*
 * omtbHDVPSSTvp.c
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
#include "omx_ctrl.h"

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

static OMX_CALLBACKTYPE VPSSTVP_Callback = {
  OMTB_ClientEventHandler,      /* Event handler callback */
  NULL,                         /* Empty buffer done callback */
  NULL                          /* Fill buffer done callback */
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

/* Pointer to TVP config params */
OMTB_VPSS_TVP_CONFIG_PARAMS *vpssTvpConfig = NULL;


/******************************************************************************\
 *      Static Globals
\******************************************************************************/

/* Enum Entry for Supported cfg param indexs */

PRIVATE MX_DBG_ENUM_ENTRY_T enumTblVpssTvpCfgParamIdx[] =
{
  /* ADD ENTRIES HERE for SetConfig/SetParam/GetConfig/GetParam */

  {"OMX_TI_IndexParamVFCCHwPortProperties", OMX_TI_IndexParamVFCCHwPortProperties, ""},
  {"OMX_TI_IndexParamVFCCHwPortID",         OMX_TI_IndexParamVFCCHwPortID,         ""},
  {"OMX_TI_IndexParamCTRLVidDecInfo",       OMX_TI_IndexParamCTRLVidDecInfo,       ""}, 
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
 *      VPSSTVP_GetStructIdx Function Definition
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

OmtbRet VPSSTVP_GetStructIdx(
  char *indexStr,
  unsigned int template,
  unsigned int instanceNo,  
  unsigned int portIdx,
  unsigned int *nConfigIndex,
  void **pCompCfgStruct)
{
  unsigned int enumCount = 0;

  /* Use the specified template structure */
  vpssTvpConfig = (OMTB_VPSS_TVP_CONFIG_PARAMS*)
                     &(omtbCfgTemplate[template]->vpssTvpTemplate);

  /* Get the corresponding string for enum values from enum table
     Set structure index
     Set structure pointer
     Set port index for which parameter to be updated
     Set structure header info */
  while(strcmp(enumTblVpssTvpCfgParamIdx[enumCount].name , ""))
  {
    if(0 == strcmp(enumTblVpssTvpCfgParamIdx[enumCount].name,
                   indexStr))
    {
      switch(enumTblVpssTvpCfgParamIdx[enumCount].value)
      {

        case OMX_TI_IndexParamVFCCHwPortProperties:
		  {
			*nConfigIndex   = enumTblVpssTvpCfgParamIdx[enumCount].value;
			*pCompCfgStruct = &vpssTvpConfig->sHwPortParam;
			 vpssTvpConfig->sHwPortParam.nPortIndex = portIdx;
			 OMTB_SetHeader( *pCompCfgStruct,
							 sizeof(OMX_PARAM_VFCC_HWPORT_PROPERTIES));
		  }
  		  return OMTB_SUCCESS;

		case OMX_TI_IndexParamVFCCHwPortID:
		  {
			*nConfigIndex   = enumTblVpssTvpCfgParamIdx[enumCount].value;
			*pCompCfgStruct = &vpssTvpConfig->sHwPortId;
			 vpssTvpConfig->sHwPortId.nPortIndex = portIdx;
			 OMTB_SetHeader( *pCompCfgStruct,
							 sizeof(OMX_PARAM_VFCC_HWPORT_ID));
		  }
  		  return OMTB_SUCCESS;
		  
		case OMX_TI_IndexParamCTRLVidDecInfo:
		  {
			*nConfigIndex   = enumTblVpssTvpCfgParamIdx[enumCount].value;
			*pCompCfgStruct = &vpssTvpConfig->sVidDecParam;
			 vpssTvpConfig->sVidDecParam.nPortIndex = portIdx;
			 OMTB_SetHeader( *pCompCfgStruct,
							 sizeof(OMX_PARAM_CTRL_VIDDECODER_INFO));
		  }
  		  return OMTB_SUCCESS;  

		default:
          {
            return OMTB_FAIL;
          }

      } // switch(enumTblVpssTvpCfgParamIdx[enumCount].value)

    } // if(0 == strcmp(enumTblVpssTvpCfgParamIdx[enumCount].name, ...

    enumCount++;
  }

  return OMTB_SUCCESS;
}

/******************************************************************************\
 *      VPSSTVP_SetTemplateDefVal Function Definition
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

MX_Result VPSSTVP_SetTemplateDefVal(OMTB_TEMPLATE_INFO *pTemplate)
{
  OMTB_VPSS_TVP_CONFIG_PARAMS *vpssHdTvpCfg = NULL;

  /* param validation */
  if(NULL == pTemplate)
  {
    PRINT(PRINT_ERR_MSG, "%s: Memory for Template not allocated\n",__FUNCTION__);
    return ERR_INVNAME;
  }

  /* VPSS TVP configuration */
  vpssHdTvpCfg = &pTemplate->vpssTvpTemplate;

  strcpy(vpssHdTvpCfg->sBasicParams.compName,   OMTB_VPSS_TVP_COMPONENT_NAME);

  vpssHdTvpCfg->sHwPortParam.eCaptMode          = OMX_VIDEO_CaptureModeMC_LINE_MUX;
  vpssHdTvpCfg->sHwPortParam.eVifMode           = OMX_VIDEO_CaptureVifMode_08BIT;
  vpssHdTvpCfg->sHwPortParam.eInColorFormat     = OMX_COLOR_FormatYCbYCr;
  vpssHdTvpCfg->sHwPortParam.eScanType          = OMX_VIDEO_CaptureScanTypeInterlaced;
  vpssHdTvpCfg->sHwPortParam.nMaxHeight         = OMTB_VPSS_TVP_DEF_HEIGHT;
  vpssHdTvpCfg->sHwPortParam.nMaxWidth          = OMTB_VPSS_TVP_DEF_WIDTH;
  vpssHdTvpCfg->sHwPortParam.nMaxChnlsPerHwPort = OMTB_VPSS_VIDEO_CAPTURE_MAX_CHNLS;
  
  vpssHdTvpCfg->sHwPortId.eHwPortId             = OMX_VIDEO_CaptureHWPortALL_PORTS;
  
  vpssHdTvpCfg->sVidDecParam.videoStandard      = OMX_VIDEO_DECODER_STD_AUTO_DETECT;     
  vpssHdTvpCfg->sVidDecParam.videoDecoderId     = OMX_VID_DEC_TVP7002_DRV;    
  vpssHdTvpCfg->sVidDecParam.videoSystemId      = OMX_VIDEO_DECODER_VIDEO_SYSTEM_AUTO_DETECT; 

  return ERR_NOERR;
}

OmtbRet VPSSTVP_SetBufferSize(void *thisClient)
{
    return OMTB_SUCCESS;
}

/******************************************************************************\
 *      VPSSTVP_ClassInit Function Definition
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
OMX_ERRORTYPE VPSSTVP_ClassInit(OMTB_CLIENT_PRIVATE* thisClient)
{
  OmtbRet err = OMTB_SUCCESS;
  
  PRINT(PRINT_FUNCTION_NAME, "Entering <Function> : <%s>\n",
                              __FUNCTION__);
							  
  /* no of input / output ports */
  thisClient->omtbPvt.numInport  = 0;
  thisClient->omtbPvt.numOutport = 0;
  thisClient->omtbPvt.startOutportIndex = 0;
  
  thisClient->omtbPvt.outputDataWriteTask = NULL;
  thisClient->omtbPvt.inputDataReadTask = NULL;

  /* Function pointer for GetStructIdx */
  thisClient->omtbPvt.fpGetStructIdx = VPSSTVP_GetStructIdx; 
  thisClient->omtbPvt.fpSetBufferSize = VPSSTVP_SetBufferSize;
  thisClient->omtbPvt.fpSetPortDefinition = NULL;
	
  thisClient->omtbPvt.numFileInBufs = 0;
  thisClient->omtbPvt.numFileOutBufs = 0;
  
  thisClient->omtbPvt.readSize       = 0;
  thisClient->omtbPvt.writeSize      = 0; 	 
  
  thisClient->omtbPvt.eClassType = OMTB_VPSS_TVP_CLASS;
  
  PRINT(PRINT_FUNCTION_NAME, "Leaving <Function> : <%s>\n",
                              __FUNCTION__);  
  return (err);							  
}
/*----------------------------- end of file ----------------------------------*/

