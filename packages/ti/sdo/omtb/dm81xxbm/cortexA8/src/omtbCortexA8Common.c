/*
 * omtbCortexA8Common.c
 *
 * Platform specific common function definitions across the components.
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

/* OMX standard header files */
#include "OMX_Component.h"
#include "OMX_Types.h"


/******************************************************************************\
 *      Customized Includes
\******************************************************************************/

#include "omtbMain.h"
#include "omtbDebug.h"
#include "omtbCommon.h"


/******************************************************************************\
 *      Local Defines
\******************************************************************************/


/******************************************************************************\
 *      Data type definitions
\******************************************************************************/


/******************************************************************************\
 *      Extern Object Definitions
\******************************************************************************/
/* Component class structure which holds component instance handle,
   application private data etc */
extern OMTB_COMP_HANDLE     omtbClass[OMTB_MAX_CLASS];    // OMTB class array

/* Pointer to OMTB configuration template */
extern OMTB_TEMPLATE_INFO *omtbCfgTemplate[OMTB_MAX_INS];
/******************************************************************************\
 *      Globals
\******************************************************************************/


/******************************************************************************\
 *      Public Function Prototype
\******************************************************************************/


/******************************************************************************\
 *      Static Globals
\******************************************************************************/


/******************************************************************************\
 *      Private Function Declarations
\******************************************************************************/


/******************************************************************************\
 *      OMTB_SetHeader Function Definition
\******************************************************************************/
/**
 *
 *  @brief    This Function Sets the OMX version no for the application
 *            allocated omx structures
 *
 *  @param    header: Void Pointer
 *            size  : Size of structure
 *
 *  @return   None
 */

void OMTB_SetHeader(OMX_PTR header, unsigned int size)
{
  OMX_VERSIONTYPE* ver = (OMX_VERSIONTYPE*)((unsigned int)header + sizeof(OMX_U32));

  /* return if structure pointer is NULL */
  if(NULL == header)
  {
    PRINT(PRINT_ERR_MSG, "%s: OMX Structure pointer is NULL !!!\n", __FUNCTION__);
    return;
  }

  *((OMX_U32*)header) = size;

  ver->s.nVersionMajor = OMTB_VERSION_MAJOR;
  ver->s.nVersionMinor = OMTB_VERSION_MINOR;
  ver->s.nRevision = OMTB_VERSION_REVISION;
  ver->s.nStep = OMTB_VERSION_STEP;
}


/******************************************************************************\
 *      OMTB_GetCompHandle Function Definition
\******************************************************************************/
/**
 *
 *  @brief   This Function returns the component handle based on the component
 *           name and instance number.
 *
 *  @param   componentRequested - Pointer to the requested component name
 *
 *           instanceNo - Component instance number
 *
 *  @return  OMX_HANDLETYPE      component handle,
 *           NULL                otherwise.
 */

OMX_HANDLETYPE OMTB_GetCompHandle(
  char *componentRequested,
  unsigned int instanceNo)
{
  if(!strcmp(componentRequested,OMTB_H264_VDEC_COMP_REF_STR))
  {
    return (omtbClass[OMTB_H264_VDEC_CLASS].handle[instanceNo]);
  }
  else if(!strcmp(componentRequested,OMTB_H264_VENC_COMP_REF_STR))
  {
    return (omtbClass[OMTB_H264_VENC_CLASS].handle[instanceNo]);
  }
  else if(!strcmp(componentRequested,OMTB_VDEC_COMP_REF_STR))
  {
    return (omtbClass[OMTB_VDEC_CLASS].handle[instanceNo]);
  }  
  else if(!strcmp(componentRequested,OMTB_ADEC_COMP_REF_STR))
  {
    return (omtbClass[OMTB_ADEC_CLASS].handle[instanceNo]);
  }    
  else if(!strcmp(componentRequested,OMTB_VPSS_VFCC_COMP_REF_STR))
  {
    return (omtbClass[OMTB_VPSS_VFCC_CLASS].handle[instanceNo]);
  }
  else if(!strcmp(componentRequested,OMTB_VPSS_TVP_COMP_REF_STR))
  {
    return (omtbClass[OMTB_VPSS_TVP_CLASS].handle[instanceNo]);
  }  
  else if(!strcmp(componentRequested,OMTB_VPSS_VFDC_COMP_REF_STR))
  {
    return (omtbClass[OMTB_VPSS_VFDC_CLASS].handle[instanceNo]);
  }
  else if(!strcmp(componentRequested,OMTB_VPSS_DC_COMP_REF_STR))
  {
    return (omtbClass[OMTB_VPSS_DC_CLASS].handle[instanceNo]);
  }  
  else if(!strcmp(componentRequested,OMTB_VPSS_VFPC_DEI_COMP_REF_STR))
  {
    return (omtbClass[OMTB_VPSS_VFPC_DEI_CLASS].handle[instanceNo]);
  }
  else if(!strcmp(componentRequested,OMTB_VPSS_VFPC_NF_COMP_REF_STR))
  {
    return (omtbClass[OMTB_VPSS_VFPC_NF_CLASS].handle[instanceNo]);
  }
  else if(!strcmp(componentRequested,OMTB_VPSS_VFPC_SC_COMP_REF_STR))
  {
    return (omtbClass[OMTB_VPSS_VFPC_SC_CLASS].handle[instanceNo]);
  }
  else
  {
    PRINT(PRINT_ERR_MSG, "%s component instance %d not created",
                          componentRequested, instanceNo);
    return NULL;
  }
}



/******************************************************************************\
 *      OMTB_SetCompHandle Function Definition
\******************************************************************************/
/**
 *
 *  @brief   This Function sets the component handle based on the component
 *           name and instance number.
 *
 *  @param   componentRequested - Pointer to the requested component name
 *
 *           instanceNo - Component instance number
 *
 *  @return  OMX_HANDLETYPE      component handle,
 *           NULL                otherwise.
 */

OMX_HANDLETYPE OMTB_SetCompHandle(
  char *componentRequested,
  unsigned int instanceNo,
  void *pHandle)
{
  if(!strcmp(componentRequested,OMTB_H264_VDEC_COMP_REF_STR))
  {
    omtbClass[OMTB_H264_VDEC_CLASS].handle[instanceNo] = pHandle;
  }
  else if(!strcmp(componentRequested,OMTB_H264_VENC_COMP_REF_STR))
  {
    omtbClass[OMTB_H264_VENC_CLASS].handle[instanceNo] = pHandle;
  }
  else if(!strcmp(componentRequested,OMTB_VDEC_COMP_REF_STR))
  {
    omtbClass[OMTB_VDEC_CLASS].handle[instanceNo] = pHandle;
  }  
  else if(!strcmp(componentRequested,OMTB_ADEC_COMP_REF_STR))
  {
    omtbClass[OMTB_ADEC_CLASS].handle[instanceNo] = pHandle;
  }    
  else if(!strcmp(componentRequested,OMTB_VPSS_VFCC_COMP_REF_STR))
  {
    omtbClass[OMTB_VPSS_VFCC_CLASS].handle[instanceNo] = pHandle;
  }
  else if(!strcmp(componentRequested,OMTB_VPSS_TVP_COMP_REF_STR))
  {
    omtbClass[OMTB_VPSS_TVP_CLASS].handle[instanceNo] = pHandle;
  }  
  else if(!strcmp(componentRequested,OMTB_VPSS_VFDC_COMP_REF_STR))
  {
    omtbClass[OMTB_VPSS_VFDC_CLASS].handle[instanceNo] = pHandle;
  }
  else if(!strcmp(componentRequested,OMTB_VPSS_DC_COMP_REF_STR))
  {
    omtbClass[OMTB_VPSS_DC_CLASS].handle[instanceNo] = pHandle;
  }  
  else if(!strcmp(componentRequested,OMTB_VPSS_VFPC_DEI_COMP_REF_STR))
  {
    omtbClass[OMTB_VPSS_VFPC_DEI_CLASS].handle[instanceNo] = pHandle;
  }
  else if(!strcmp(componentRequested,OMTB_VPSS_VFPC_NF_COMP_REF_STR))
  {
    omtbClass[OMTB_VPSS_VFPC_NF_CLASS].handle[instanceNo] = pHandle;
  }
  else if(!strcmp(componentRequested,OMTB_VPSS_VFPC_SC_COMP_REF_STR))
  {
    omtbClass[OMTB_VPSS_VFPC_SC_CLASS].handle[instanceNo] = pHandle;
  }
  else
  {
    PRINT(PRINT_ERR_MSG, "%s component instance %d not created",
                          componentRequested, instanceNo);
    return NULL;
  }
}


/******************************************************************************\
 *      OMTB_GetCompPrivHandle Function Definition
\******************************************************************************/
/**
 *
 *  @brief   This Function returns the component private handle based on the component
 *           name and instance number.
 *
 *  @param   componentRequested - Pointer to the requested component name
 *
 *           instanceNo - Component instance number
 *
 *  @return  OMX_HANDLETYPE      component handle,
 *           NULL                otherwise.
 */
OMTB_APP_PRIVATE* OMTB_GetCompPrivHandle(
  char *componentRequested,
  unsigned int instanceNo)
{
  OMTB_APP_PRIVATE *appPrivate;
  
  if(!strcmp(componentRequested,OMTB_H264_VDEC_COMP_REF_STR))
  {
    appPrivate = &(omtbClass[OMTB_H264_VDEC_CLASS].h264VdecClient[instanceNo]->omtbPvt);
  }
  else if(!strcmp(componentRequested,OMTB_H264_VENC_COMP_REF_STR))
  {
    appPrivate = &(omtbClass[OMTB_H264_VENC_CLASS].h264VencClient[instanceNo]->omtbPvt);
  }
  else if(!strcmp(componentRequested,OMTB_VDEC_COMP_REF_STR))
  {
    appPrivate = &(omtbClass[OMTB_VDEC_CLASS].vdecClient[instanceNo]->omtbPvt);
  }
  else if(!strcmp(componentRequested,OMTB_ADEC_COMP_REF_STR))
  {
    appPrivate = &(omtbClass[OMTB_ADEC_CLASS].adecClient[instanceNo]->omtbPvt);
  }  
  else if(!strcmp(componentRequested,OMTB_VPSS_VFCC_COMP_REF_STR))
  {
    appPrivate = &(omtbClass[OMTB_VPSS_VFCC_CLASS].vpssVfccClient[instanceNo]->omtbPvt);
  }
  else if(!strcmp(componentRequested,OMTB_VPSS_TVP_COMP_REF_STR))
  {
    appPrivate = &(omtbClass[OMTB_VPSS_TVP_CLASS].vpssTvpClient[instanceNo]->omtbPvt);
  }
  else if(!strcmp(componentRequested,OMTB_VPSS_VFDC_COMP_REF_STR))
  {
    appPrivate = &(omtbClass[OMTB_VPSS_VFDC_CLASS].vpssVfdcClient[instanceNo]->omtbPvt);
  }
  else if(!strcmp(componentRequested,OMTB_VPSS_DC_COMP_REF_STR))
  {
    appPrivate = &(omtbClass[OMTB_VPSS_DC_CLASS].vpssDcClient[instanceNo]->omtbPvt);
  }  
  else if(!strcmp(componentRequested,OMTB_VPSS_VFPC_DEI_COMP_REF_STR))
  {
    appPrivate = &(omtbClass[OMTB_VPSS_VFPC_DEI_CLASS].vpssVfpcDeiClient[instanceNo]->omtbPvt);
  }
  else if(!strcmp(componentRequested,OMTB_VPSS_VFPC_NF_COMP_REF_STR))
  {
    appPrivate = &(omtbClass[OMTB_VPSS_VFPC_NF_CLASS].vpssVfpcNfClient[instanceNo]->omtbPvt);
  }
  else if(!strcmp(componentRequested,OMTB_VPSS_VFPC_SC_COMP_REF_STR))
  {
    appPrivate = &(omtbClass[OMTB_VPSS_VFPC_SC_CLASS].vpssVfpcScClient[instanceNo]->omtbPvt);
  }
  else
  {
    PRINT(PRINT_ERR_MSG, "%s component instance %d not created",
                          componentRequested, instanceNo);
    return NULL;
  }  	
  return(appPrivate); 	
}  
	

/******************************************************************************\
 *      OMTB_SetCompPrivHandle Function Definition
\******************************************************************************/
/**
 *
 *  @brief   This Function sets the component private handle based on the component
 *           name and instance number.
 *
 *  @param   componentRequested - Pointer to the requested component name
 *
 *           instanceNo - Component instance number
 *
 *  @return  OMX_HANDLETYPE      component handle,
 *           NULL                otherwise.
 */

OMX_HANDLETYPE OMTB_SetCompPrivHandle(
  char *componentRequested,
  unsigned int instanceNo,
  void *pPrivHandle)
{
  if(!strcmp(componentRequested,OMTB_H264_VDEC_COMP_REF_STR))
  {
    omtbClass[OMTB_H264_VDEC_CLASS].h264VdecClient[instanceNo] = (OMTB_H264_VDEC_PRIVATE*)pPrivHandle;
  }
  else if(!strcmp(componentRequested,OMTB_H264_VENC_COMP_REF_STR))
  {
    omtbClass[OMTB_H264_VENC_CLASS].h264VencClient[instanceNo] = pPrivHandle;
  }
  else if(!strcmp(componentRequested,OMTB_VDEC_COMP_REF_STR))
  {
    omtbClass[OMTB_VDEC_CLASS].vdecClient[instanceNo] = (OMTB_VDEC_PRIVATE*)pPrivHandle;
  }  
  else if(!strcmp(componentRequested,OMTB_ADEC_COMP_REF_STR))
  {
    omtbClass[OMTB_ADEC_CLASS].adecClient[instanceNo] = (OMTB_ADEC_PRIVATE*)pPrivHandle;
  }    
  else if(!strcmp(componentRequested,OMTB_VPSS_VFCC_COMP_REF_STR))
  {
    omtbClass[OMTB_VPSS_VFCC_CLASS].vpssVfccClient[instanceNo] = pPrivHandle;
  }
  else if(!strcmp(componentRequested,OMTB_VPSS_TVP_COMP_REF_STR))
  {
    omtbClass[OMTB_VPSS_TVP_CLASS].vpssTvpClient[instanceNo] = pPrivHandle;
  }  
  else if(!strcmp(componentRequested,OMTB_VPSS_VFDC_COMP_REF_STR))
  {
    omtbClass[OMTB_VPSS_VFDC_CLASS].vpssVfdcClient[instanceNo] = pPrivHandle;
  }
  else if(!strcmp(componentRequested,OMTB_VPSS_DC_COMP_REF_STR))
  {
    omtbClass[OMTB_VPSS_DC_CLASS].vpssDcClient[instanceNo] = pPrivHandle;
  }  
  else if(!strcmp(componentRequested,OMTB_VPSS_VFPC_DEI_COMP_REF_STR))
  {
    omtbClass[OMTB_VPSS_VFPC_DEI_CLASS].vpssVfpcDeiClient[instanceNo] = pPrivHandle;
  }
  else if(!strcmp(componentRequested,OMTB_VPSS_VFPC_NF_COMP_REF_STR))
  {
    omtbClass[OMTB_VPSS_VFPC_NF_CLASS].vpssVfpcNfClient[instanceNo] = pPrivHandle;
  }
  else if(!strcmp(componentRequested,OMTB_VPSS_VFPC_SC_COMP_REF_STR))
  {
    omtbClass[OMTB_VPSS_VFPC_SC_CLASS].vpssVfpcScClient[instanceNo] = pPrivHandle;
  }
  else
  {
    PRINT(PRINT_ERR_MSG, "%s component instance %d not created",
                          componentRequested, instanceNo);
    return NULL;
  }
}
	
/******************************************************************************\
 *      OMTB_GetCompBasicConfigPtr Function Definition
\******************************************************************************/
/**
 *
 *  @brief   This Function returns the component Basic Param pointer based on the component
 *           name and template number.
 *
 *  @param   componentRequested - Pointer to the requested component name
 *
 *           templateNo - Component template number
 *
 *  @return  OMX_HANDLETYPE      component handle,
 *           NULL                otherwise.
 */
OMTB_BASIC_CONFIG_PARAMS* OMTB_GetCompBasicConfigPtr(
  char *componentRequested,
  unsigned int templateNo)
{
  OMTB_BASIC_CONFIG_PARAMS *pBasicParams = NULL;
  
  if(!strcmp(componentRequested,OMTB_H264_VDEC_COMP_REF_STR))
  {
    pBasicParams = &(omtbCfgTemplate[templateNo]->h264VdecTemplate.sBasicParams);
  }
  else if(!strcmp(componentRequested,OMTB_H264_VENC_COMP_REF_STR))
  {
    pBasicParams = &(omtbCfgTemplate[templateNo]->h264VencTemplate.sBasicParams);
  }
  else if(!strcmp(componentRequested,OMTB_VDEC_COMP_REF_STR))
  {
    pBasicParams = &(omtbCfgTemplate[templateNo]->vdecTemplate.sBasicParams);
  }  
  else if(!strcmp(componentRequested,OMTB_ADEC_COMP_REF_STR))
  {
    pBasicParams = &(omtbCfgTemplate[templateNo]->adecTemplate.sBasicParams);
  }    
  else if(!strcmp(componentRequested,OMTB_VPSS_VFCC_COMP_REF_STR))
  {
    pBasicParams = &(omtbCfgTemplate[templateNo]->vpssVfccTemplate);
  }
  else if(!strcmp(componentRequested,OMTB_VPSS_TVP_COMP_REF_STR))
  {
    pBasicParams = &(omtbCfgTemplate[templateNo]->vpssTvpTemplate);
  }
  else if(!strcmp(componentRequested,OMTB_VPSS_VFDC_COMP_REF_STR))
  {
    pBasicParams = &(omtbCfgTemplate[templateNo]->vpssVfdcTemplate);
  }
  else if(!strcmp(componentRequested,OMTB_VPSS_DC_COMP_REF_STR))
  {
    pBasicParams = &(omtbCfgTemplate[templateNo]->vpssDcTemplate);
  }  
  else if(!strcmp(componentRequested,OMTB_VPSS_VFPC_DEI_COMP_REF_STR))
  {
    pBasicParams = &(omtbCfgTemplate[templateNo]->vpssVfpcDeiTemplate);
  }
  else if(!strcmp(componentRequested,OMTB_VPSS_VFPC_NF_COMP_REF_STR))
  {
    pBasicParams = &(omtbCfgTemplate[templateNo]->vpssVfpcNfTemplate);
  }
  else if(!strcmp(componentRequested,OMTB_VPSS_VFPC_SC_COMP_REF_STR))
  {
    pBasicParams = &(omtbCfgTemplate[templateNo]->vpssVfpcScTemplate);
  }
  else
  {
    PRINT(PRINT_ERR_MSG, "%s template is %d not created",
                          componentRequested, templateNo);
    return NULL;
  }  	
  return(pBasicParams); 	
}

unsigned int OMTB_GetSizeCompPrivStruct(char *componentRequested)
{	
  unsigned int nSize = 0;
  
  if(!strcmp(componentRequested,OMTB_H264_VDEC_COMP_REF_STR))
  {
    nSize = sizeof(OMTB_H264_VDEC_PRIVATE);
  }
  else if(!strcmp(componentRequested,OMTB_H264_VENC_COMP_REF_STR))
  {
    nSize = sizeof(OMTB_H264_VENC_PRIVATE);    
  }
  else if(!strcmp(componentRequested,OMTB_VDEC_COMP_REF_STR))
  {
    nSize = sizeof(OMTB_VDEC_PRIVATE);
  }  
  else if(!strcmp(componentRequested,OMTB_ADEC_COMP_REF_STR))
  {
    nSize = sizeof(OMTB_ADEC_PRIVATE);
  }    
  else if(!strcmp(componentRequested,OMTB_VPSS_VFCC_COMP_REF_STR))
  {
    nSize = sizeof(OMTB_VPSS_VFCC_PRIVATE);  
  }
  else if(!strcmp(componentRequested,OMTB_VPSS_TVP_COMP_REF_STR))
  {
    nSize = sizeof(OMTB_VPSS_TVP_PRIVATE);      
  }
  else if(!strcmp(componentRequested,OMTB_VPSS_VFDC_COMP_REF_STR))
  {
    nSize = sizeof(OMTB_VPSS_VFDC_PRIVATE); 
  }
  else if(!strcmp(componentRequested,OMTB_VPSS_DC_COMP_REF_STR))
  {
    nSize = sizeof(OMTB_VPSS_DC_PRIVATE);    
  }  
  else if(!strcmp(componentRequested,OMTB_VPSS_VFPC_DEI_COMP_REF_STR))
  {
    nSize = sizeof(OMTB_VPSS_VFPC_DEI_PRIVATE);    
  }
  else if(!strcmp(componentRequested,OMTB_VPSS_VFPC_NF_COMP_REF_STR))
  {
    nSize = sizeof(OMTB_VPSS_VFPC_NF_PRIVATE);    
  }
  else if(!strcmp(componentRequested,OMTB_VPSS_VFPC_SC_COMP_REF_STR))
  {
    nSize = sizeof(OMTB_VPSS_VFPC_SC_PRIVATE);   
  }
  else
  {
    PRINT(PRINT_ERR_MSG, "%s component not found",
                          componentRequested);
    return NULL;
  }  	
  
  return(nSize); 	  
}


OMTB_ClassInitPtr OMTB_GetClassInitFuncPtr(char *componentRequested)
{	
  OMTB_ClassInitPtr fpClassInit = NULL;
  
  if(!strcmp(componentRequested,OMTB_H264_VDEC_COMP_REF_STR))
  {
    fpClassInit = H264VDEC_ClassInit;
  }
  else if(!strcmp(componentRequested,OMTB_H264_VENC_COMP_REF_STR))
  {
    fpClassInit = H264VENC_ClassInit;
  }
  else if(!strcmp(componentRequested,OMTB_VDEC_COMP_REF_STR))
  {
    fpClassInit = VDEC_ClassInit;
  }  
  else if(!strcmp(componentRequested,OMTB_ADEC_COMP_REF_STR))
  {
    fpClassInit = ADEC_ClassInit;
  }  
  else if(!strcmp(componentRequested,OMTB_VPSS_VFCC_COMP_REF_STR))
  {
    fpClassInit =  VPSSVFCC_ClassInit;    
  }
  else if(!strcmp(componentRequested,OMTB_VPSS_TVP_COMP_REF_STR))
  {
    fpClassInit =  VPSSTVP_ClassInit;
  }
  else if(!strcmp(componentRequested,OMTB_VPSS_VFDC_COMP_REF_STR))
  {
    fpClassInit =  VPSSVFDC_ClassInit;  
  }
  else if(!strcmp(componentRequested,OMTB_VPSS_DC_COMP_REF_STR))
  {
    fpClassInit = VPSSDC_ClassInit;
  }  
  else if(!strcmp(componentRequested,OMTB_VPSS_VFPC_DEI_COMP_REF_STR))
  {
    fpClassInit = VPSSVFPCDEI_ClassInit;  
  }
  else if(!strcmp(componentRequested,OMTB_VPSS_VFPC_NF_COMP_REF_STR))
  {
    fpClassInit = VPSSVFPCNF_ClassInit; 
  }
  else if(!strcmp(componentRequested,OMTB_VPSS_VFPC_SC_COMP_REF_STR))
  {
    fpClassInit = VPSSVFPCSC_ClassInit;    
  }
  else
  {
    PRINT(PRINT_ERR_MSG, "%s component not found",
                          componentRequested);
    return NULL;
  }  	
  
  return(fpClassInit); 	  
}
/*----------------------------- end of file ---------------------------------*/
