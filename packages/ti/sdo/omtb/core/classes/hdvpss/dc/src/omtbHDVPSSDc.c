/*
 * omtbHDVPSSDc.c
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

#include <xdc/runtime/Gate.h>
#include <xdc/runtime/Assert.h>
#include <xdc/runtime/knl/Thread.h>
#include <xdc/runtime/Timestamp.h>

/* OMX standard header files */
#include "OMX_Core.h"
#include "OMX_Component.h"
#include "OMX_Types.h"
#include "OMX_TI_Index.h"
#include "omx_vfdc.h"

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

static OMX_CALLBACKTYPE VPSSDC_Callback = {
  OMTB_ClientEventHandler,   /* Event handler callback */
  NULL,   /* Empty buffer done callback */
  NULL    /* Fill buffer done callback */
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

/* Pointer to DC config params */
OMTB_VPSS_DC_CONFIG_PARAMS *vpssDcConfig = NULL;


/******************************************************************************\
 *      Static Globals
\******************************************************************************/

static OMX_U32 VPSSDC_funcCreateCount = 0;  /* Func create count */
static OMX_U32 VPSSDC_apiCreateCount = 0;   /* API create count */

static OMX_U32 VPSSDC_funcDeleteCount = 0;  /* Func delete count */
static OMX_U32 VPSSDC_apiDeleteCount = 0;   /* API delete count */

/* Enum Entry for Supported cfg param indexs */

PRIVATE MX_DBG_ENUM_ENTRY_T enumTblVpssDcCfgParamIdx[] =
{
  /* ADD ENTRIES HERE for SetConfig/SetParam/GetConfig/GetParam */
  {"OMX_TI_IndexParamVFDCDriverInstId",        OMX_TI_IndexParamVFDCDriverInstId,        ""},
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
 *      VPSSDC_GetStructIdx Function Definition
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

OmtbRet VPSSDC_GetStructIdx(
  char *indexStr,
  unsigned int template,
  unsigned int instanceNo,  
  unsigned int portIdx,
  unsigned int *nConfigIndex,
  void **pCompCfgStruct)
{
  unsigned int enumCount = 0;

  /* Use the specified template structure */
  vpssDcConfig = (OMTB_VPSS_DC_CONFIG_PARAMS*)
                     &(omtbCfgTemplate[template]->vpssDcTemplate);

  /* Get the corresponding string for enum values from enum table
     Set structure index
     Set structure pointer
     Set port index for which parameter to be updated
     Set structure header info */
  while(strcmp(enumTblVpssDcCfgParamIdx[enumCount].name , ""))
  {
    if(0 == strcmp(enumTblVpssDcCfgParamIdx[enumCount].name,
                   indexStr))
    {
      switch(enumTblVpssDcCfgParamIdx[enumCount].value)
      {
        /* ADD Similar implementation below for supported indexes */
        case OMX_TI_IndexParamVFDCDriverInstId:
          {
            *nConfigIndex   = enumTblVpssDcCfgParamIdx[enumCount].value;
            *pCompCfgStruct = &vpssDcConfig->sDvrInstId;
            vpssDcConfig->sDvrInstId.nPortIndex = 0;
            OMTB_SetHeader( *pCompCfgStruct,
                            sizeof(OMX_PARAM_VFDC_DRIVERINSTID));
          }
          return OMTB_SUCCESS;
     	case OMX_TI_IndexParamVFDCCustomModeInfo:
	      {
		    *nConfigIndex   = enumTblVpssDcCfgParamIdx[enumCount].value;
		    *pCompCfgStruct = &vpssDcConfig->sCustomModeInfo;
            vpssDcConfig->sCustomModeInfo.nPortIndex = portIdx;			
		    OMTB_SetHeader( *pCompCfgStruct,
			   			    sizeof(OMX_PARAM_DC_CUSTOM_MODE_INFO));
	      }
	      return OMTB_SUCCESS;
		  
        default:
          {
            return OMTB_FAIL;
          }

      } // switch(enumTblVpssDcCfgParamIdx[enumCount].value)

    } // if(0 == strcmp(enumTblVpssDcCfgParamIdx[enumCount].name, ...

    enumCount++;
  }

  return OMTB_SUCCESS;
}

/******************************************************************************\
 *      VPSSDC_SetTemplateDefVal Function Definition
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

MX_Result VPSSDC_SetTemplateDefVal(OMTB_TEMPLATE_INFO *pTemplate)
{
  OMTB_VPSS_DC_CONFIG_PARAMS *vpssHdDcCfg = NULL;

  /* param validation */
  if(NULL == pTemplate)
  {
    PRINT(PRINT_ERR_MSG, "%s: Memory for Template not allocated\n",__FUNCTION__);
    return ERR_INVNAME;
  }

  /* VPSS DC configuration */
  vpssHdDcCfg = &pTemplate->vpssDcTemplate;

  strcpy(vpssHdDcCfg->sBasicParams.compName,   OMTB_VPSS_DC_COMPONENT_NAME);
  vpssHdDcCfg->sBasicParams.dataOutPutMode     = OMTB_DRIVER;
  vpssHdDcCfg->sBasicParams.dataInPutMode      = OMTB_DRIVER;
  
  vpssHdDcCfg->sDvrInstId.nDrvInstID = OMX_VIDEO_DISPLAY_ID_HD0;
  vpssHdDcCfg->sDvrInstId.eDispVencMode = OMX_DC_MODE_1080P_60;

  vpssHdDcCfg->sCustomModeInfo.width        = OMTB_VPSS_DC_DEF_WIDTH;
  vpssHdDcCfg->sCustomModeInfo.height       = OMTB_VPSS_DC_DEF_HEIGHT;
  vpssHdDcCfg->sCustomModeInfo.scanFormat   = OMX_SF_PROGRESSIVE;
  vpssHdDcCfg->sCustomModeInfo.pixelClock   = 0;
  vpssHdDcCfg->sCustomModeInfo.fps          = 0;
  vpssHdDcCfg->sCustomModeInfo.hFrontPorch  = 0;
  vpssHdDcCfg->sCustomModeInfo.hBackPorch   = 0;
  vpssHdDcCfg->sCustomModeInfo.hSyncLen     = 0;
  vpssHdDcCfg->sCustomModeInfo.vFrontPorch  = 0;
  vpssHdDcCfg->sCustomModeInfo.vBackPorch   = 0 ;
  vpssHdDcCfg->sCustomModeInfo.vSyncLen     = 0;
  
  return ERR_NOERR;
}

OmtbRet VPSSDC_SetBufferSize(void *thisClient)
{
   return OMTB_SUCCESS;
}

/******************************************************************************\
 *      VPSSDC_ClassInit Function Definition
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
OMX_ERRORTYPE VPSSDC_ClassInit(OMTB_CLIENT_PRIVATE* thisClient)
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
  thisClient->omtbPvt.fpGetStructIdx = VPSSDC_GetStructIdx; 
  thisClient->omtbPvt.fpSetBufferSize = VPSSDC_SetBufferSize;
  thisClient->omtbPvt.fpSetPortDefinition = NULL;
	
  thisClient->omtbPvt.numFileInBufs = 0;
  thisClient->omtbPvt.numFileOutBufs = 0;
  
  thisClient->omtbPvt.readSize       = 0;
  thisClient->omtbPvt.writeSize      = 0; 	 
  
  thisClient->omtbPvt.eClassType = OMTB_VPSS_DC_CLASS;
  
  PRINT(PRINT_FUNCTION_NAME, "Leaving <Function> : <%s>\n",
                              __FUNCTION__);  
  return (err);							  
}
/*----------------------------- end of file ----------------------------------*/

