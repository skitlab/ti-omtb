/*
 * omtbCommon.h
 *
 * This file contains platform specific common structures required
 * across the components.
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

#ifndef __OMTB_COMMON_H__
#define __OMTB_COMMON_H__

#define USE_SCRIPT
#define OMTB_DEMO

/* Forword Declaration */
/* Different OMX Classes */
typedef enum _OMX_CLASS
{

  OMTB_H264_VDEC_CLASS,      /* H264 decoder identifier */
  OMTB_H264_VENC_CLASS,      /* H264 encoder identifier */
  OMTB_VDEC_CLASS,           /* Video Decoder identifier */
  OMTB_ADEC_CLASS,           /* Audio Decoder identifier */
  OMTB_VPSS_VFCC_CLASS,      /* VPSS VFCC identifier */
  OMTB_VPSS_TVP_CLASS,       /* VPSS TVP identifier */
  OMTB_VPSS_VFDC_CLASS,      /* VPSS VFDC identifier */
  OMTB_VPSS_DC_CLASS,        /* VPSS VFDC identifier */
  OMTB_VPSS_VFPC_DEI_CLASS,  /* VPSS VFPC DEI identifier */
  OMTB_VPSS_VFPC_NF_CLASS,   /* VPSS VFPC NF identifier */
  OMTB_VPSS_VFPC_SC_CLASS,   /* VPSS VFPC SC identifier */
  OMTB_ALSARECORD_CLASS,     /* ALSA RECORD identifier */  
  OMTB_ALSAPLAY_CLASS,       /* ALSA PLAY identifier */    
  OMTB_DUMMY_CLASS,
  OMTB_MAX_CLASS = OMTB_DUMMY_CLASS + 1,
                             /* Max no of class entries + 1  */
  OMTB_MAX_VIDDEC = 3,       /* Max no of video decoders + 1 */
  OMTB_MAX_AUDDEC = 2,       /* Max no of audio decoders + 1 */
  OMTB_MAX_VIDENC = 2,       /* Max no of video encoders + 1 */
  OMTB_MAX_AUDENC = 2,       /* Max no of audio encoders + 1 */
  OMTB_MAX_HDVPSS = 7,       /* Max no of video processing subsystems + 1 */
  OMTB_MAX_ALSA   = 3,       /* Max no of audio capture + audio playback + 1 */
  OMTB_MAX_SAMPCOMP = 2      /* Max no of sample component + 1 */

}OMX_CLASS;

/******************************************************************************\
*     Includes
\******************************************************************************/

#include "omtbMain.h"
#include "omtbH264Vdec.h"
#include "omtbH264Venc.h"
#include "omtbVdec.h"
#include "omtbAdec.h"
#include "omtbHDVPSSVfcc.h"
#include "omtbHDVPSSTvp.h"
#include "omtbHDVPSSVfdc.h"
#include "omtbHDVPSSDc.h"
#include "omtbHDVPSSVfpcDei.h"
#include "omtbHDVPSSVfpcDeiApi.h"
#include "omtbHDVPSSVfpcNf.h"
#include "omtbHDVPSSVfpcNfApi.h"
#include "omtbHDVPSSVfpcSc.h"
#include "omtbHDVPSSVfpcScApi.h"
#include "omtbAlsaRecord.h"
#include "omtbAlsaPlay.h"
#include <assert.h>


/******************************************************************************/

#ifdef __cplusplus    /* required for headers that might */
 extern "C" {         /* be compiled by a C++ compiler */
#endif


/******************************************************************************\
*     Data type definitions
\******************************************************************************/

/* OMX IL Specification version */
#define OMTB_VERSION_MAJOR              (0x01)
#define OMTB_VERSION_MINOR              (0x01)
#define OMTB_VERSION_REVISION           (0x00)
#define OMTB_VERSION_STEP               (0x00)

#define OMTB_TI_IndexParamVFDCCreateMosaicLayout (0x7F0000FE)
#define OMTB_CommandWaitForSem                   (0x7F0000FF)

/*!
 *******************************************************************************
 *  \struct OMTB_TEMPLATE_INFO
 *  \brief  Common Global structure used all component configuration
 *******************************************************************************
*/
typedef struct OMTB_TEMPLATE_INFO_T
{
  OMTB_H264_VDEC_CONFIG_PARAMS h264VdecTemplate;/* H264 vdec app cfg struct */
  OMTB_H264_VENC_CONFIG_PARAMS h264VencTemplate;/* H264 venc app cfg struct */
  OMTB_VDEC_CONFIG_PARAMS vdecTemplate;         /* Video dec app cfg struct */
  OMTB_ADEC_CONFIG_PARAMS adecTemplate;         /* Audio dec app cfg struct */
  OMTB_VPSS_VFCC_CONFIG_PARAMS vpssVfccTemplate;/* VPSS VFCC app cfg struct */
  OMTB_VPSS_TVP_CONFIG_PARAMS  vpssTvpTemplate; /* VPSS TVP app cfg struct */
  OMTB_VPSS_VFDC_CONFIG_PARAMS vpssVfdcTemplate;/* VPSS VFDC app cfg struct */
  OMTB_VPSS_DC_CONFIG_PARAMS   vpssDcTemplate;   /* VPSS DC app cfg struct */
  OMTB_VPSS_VFPC_DEI_CONFIG_PARAMS vpssVfpcDeiTemplate;
                                                /* VPSS VFPC DEI app cfg struct */
  OMTB_VPSS_VFPC_NF_CONFIG_PARAMS vpssVfpcNfTemplate;
                                                /* VPSS VFPC NF app cfg struct */
  OMTB_VPSS_VFPC_SC_CONFIG_PARAMS vpssVfpcScTemplate;
                                                /* VPSS VFPC SC app cfg struct */
  OMTB_ALSARECORD_CONFIG_PARAMS alsaRecordTemplate;   /* ALSARECORD app cfg struct */  
  OMTB_ALSAPLAY_CONFIG_PARAMS alsaPlayTemplate;   /* ALSAPLAY app cfg struct */  
  unsigned int currTemplate;                    /* Current template number */
}OMTB_TEMPLATE_INFO;

/*!
 *******************************************************************************
 *  \struct OMTB_DATA_THREAD_ARG
 *  \brief  Streaming thread data structure
 *******************************************************************************
 */
typedef struct _OmtbDataThreadArg
{
  OMTB_H264_VDEC_PRIVATE* h264VdecClient;     /* H264 vdec app pvt data */
  OMTB_H264_VENC_PRIVATE* h264VencClient;     /* H264 vdec app pvt data */
  OMTB_VDEC_PRIVATE* vdecClient;              /* Video dec app pvt data */
  OMTB_ADEC_PRIVATE* adecClient;              /* Audio dec app pvt data */
  OMTB_VPSS_VFCC_PRIVATE* vpssVfccClient;     /* VPSS VFCC app pvt data */
  OMTB_VPSS_TVP_PRIVATE*  vpssTvpClient;      /* VPSS TVP app pvt data */
  OMTB_VPSS_VFDC_PRIVATE* vpssVfdcClient;     /* VPSS VFDC app pvt data */
  OMTB_VPSS_DC_PRIVATE* vpssDcClient;         /* VPSS DC app pvt data */
  OMTB_VPSS_VFPC_DEI_PRIVATE* vpssVfpcDeiClient;
                                              /* VPSS VFPC DEI app pvt data */
  OMTB_VPSS_VFPC_NF_PRIVATE* vpssVfpcNfClient;
                                              /* VPSS VFPC NF app pvt data */
  OMTB_VPSS_VFPC_SC_PRIVATE* vpssVfpcScClient;
                                              /* VPSS VFPC SC app pvt data */
}OMTB_DATA_THREAD_ARG;

/*!
 *******************************************************************************
 *  \struct OMTB_COMP_HANDLE
 *  \brief  Structure for openmax component handle to class name mapping,
 *  rewuired to support multiple instance
 *******************************************************************************
 */
typedef struct _OMTB_COMP_HANDLE_T
{
  OMX_HANDLETYPE handle[OMTB_MAX_INS];            /* OMX component handle */
  OMTB_H264_VDEC_PRIVATE *h264VdecClient[OMTB_MAX_INS];
                                                  /* H264 vdec app pvt data */
  OMTB_H264_VENC_PRIVATE *h264VencClient[OMTB_MAX_INS];
                                                  /* H264 venc app pvt data */
  OMTB_VDEC_PRIVATE *vdecClient[OMTB_MAX_INS];
                                                  /* vdec app pvt data */												  
  OMTB_VDEC_PRIVATE *adecClient[OMTB_MAX_INS];
                                                  /* adec app pvt data */														  
  OMTB_VPSS_VFCC_PRIVATE *vpssVfccClient[OMTB_MAX_INS];
                                                  /* VPSS VFCC app pvt data */
  OMTB_VPSS_TVP_PRIVATE  *vpssTvpClient[OMTB_MAX_INS];
                                                  /* VPSS VFCC app pvt data */

  OMTB_VPSS_VFDC_PRIVATE *vpssVfdcClient[OMTB_MAX_INS];
                                                  /* VPSS DC app pvt data */
  OMTB_VPSS_DC_PRIVATE *vpssDcClient[OMTB_MAX_INS];
                                                  /* VPSS VFDC app pvt data */

  OMTB_VPSS_VFPC_DEI_PRIVATE *vpssVfpcDeiClient[OMTB_MAX_INS];
                                                  /* VPSS VFPC DEI app pvt data */
  OMTB_VPSS_VFPC_NF_PRIVATE *vpssVfpcNfClient[OMTB_MAX_INS];
                                                  /* VPSS VFPC NF app pvt data */
  OMTB_VPSS_VFPC_SC_PRIVATE *vpssVfpcScClient[OMTB_MAX_INS];
                                                  /* VPSS VFPC SC app pvt data */
  OMTB_ALSARECORD_PRIVATE *alsaRecordClient[OMTB_MAX_INS];
                                                  /* ALSARECORD app pvt data */												  												  												  
  OMTB_ALSAPLAY_PRIVATE *alsaPlayClient[OMTB_MAX_INS];
                                                  /* ALSAPLAY app pvt data */												  												  												  												  
  void *execThreadId[OMTB_MAX_INS];               /* Execution Thread ID  */
  unsigned int componentInstanceNo;               /* Component instance no */
}OMTB_COMP_HANDLE;

/******************************************************************************\
*     Macros
\******************************************************************************/

#define OMTB_CMEM_ALLOCATION      (101)   /* CMEM allocation flag for OSAL */
#define ASSERT(condition)         (assert(condition));  /* Assert */

/******************************************************************************\
*     Globals
\******************************************************************************/



/******************************************************************************\
*     External Object Definitions
\******************************************************************************/


/******************************************************************************\
*     Public Function Prototypes
\******************************************************************************/

/******************************************************************************\
 *      OMTB_SetHeader Function Prototype
\******************************************************************************/
/**
 *
 *  @brief    This Function sets the OMX Version header information
 *
 *  @param    header: Pointer to OMX structure
 *            Size  : Size of OMX Structure
 *
 *  @return   None
 *
 */
void OMTB_SetHeader(OMX_PTR header, unsigned int size);


/******************************************************************************\
 *      OMTB_GetCompHandle Function Prototype
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
  unsigned int instanceNo
);

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
  void *pHandle
);
  
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
  unsigned int instanceNo
);

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
  void *pPrivHandle
);
  
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
  unsigned int templateNo
);

/******************************************************************************\
 *      H264VDEC_GetHandle Function Prototype
\******************************************************************************/
/**
 *
 *  @brief    This function invokes the getHandle API
 *
 *  @param in:
 *            classPtr         : Pointer to OMTB_COMP_HANDLE struct
 *
 *            unsigned int : Instance no of the component
 *
 *            unsigned int : Template no of the component
 *
 *  @return   OMX_ERRORTYPE : OMX standard error code
 *
 */

OMX_ERRORTYPE H264VDEC_GetHandle(OMTB_COMP_HANDLE * , unsigned int , unsigned int );


/******************************************************************************\
 *      H264VENC_GetHandle Function Prototype
\******************************************************************************/
/**
 *
 *  @brief    This function invokes the getHandle API
 *
 *  @param in:
 *            classPtr         : Pointer to OMTB_COMP_HANDLE struct
 *
 *            unsigned int : Instance no of the component
 *
 *            unsigned int : Template no of the component
 *
 *  @return   OMX_ERRORTYPE : OMX standard error code
 *
 */

OMX_ERRORTYPE H264VENC_GetHandle(OMTB_COMP_HANDLE * , unsigned int , unsigned int );

/******************************************************************************\
 *      VPSSVFCC_GetHandle Function Prototype
\******************************************************************************/
/**
 *
 *  @brief    This function invokes the getHandle API
 *
 *  @param in:
 *            classPtr         : Pointer to OMTB_COMP_HANDLE struct
 *
 *            unsigned int : Instance no of the component
 *
 *  @return   OMX_ERRORTYPE : OMX standard error code
 *
 */

OMX_ERRORTYPE VPSSVFCC_GetHandle(OMTB_COMP_HANDLE * , unsigned int );



/******************************************************************************\
 *      VPSSTVP_GetHandle Function Prototype
\******************************************************************************/
/**
 *
 *  @brief    This function invokes the getHandle API
 *
 *  @param in:
 *            classPtr         : Pointer to OMTB_COMP_HANDLE struct
 *
 *            unsigned int : Instance no of the component
 *
 *  @return   OMX_ERRORTYPE : OMX standard error code
 *
 */

OMX_ERRORTYPE VPSSTVP_GetHandle(OMTB_COMP_HANDLE * , unsigned int );

/******************************************************************************\
 *      VPSSVFDC_GetHandle Function Prototype
\******************************************************************************/
/**
 *
 *  @brief    This function invokes the getHandle API
 *
 *  @param in:
 *            classPtr         : Pointer to OMTB_COMP_HANDLE struct
 *
 *            unsigned int : Instance no of the component
 *
 *  @return   OMX_ERRORTYPE : OMX standard error code
 *
 */

OMX_ERRORTYPE VPSSVFDC_GetHandle(OMTB_COMP_HANDLE * , unsigned int );


/******************************************************************************\
 *      VPSSVFPCDEI_GetHandle Function Prototype
\******************************************************************************/
/**
 *
 *  @brief    This function invokes the getHandle API
 *
 *  @param in:
 *            classPtr         : Pointer to OMTB_COMP_HANDLE struct
 *
 *            unsigned int : Instance no of the component
 *
 *  @return   OMX_ERRORTYPE : OMX standard error code
 *
 */

OMX_ERRORTYPE VPSSVFPCDEI_GetHandle(OMTB_COMP_HANDLE * , unsigned int );


/******************************************************************************\
 *      VPSSVFPCNF_GetHandle Function Prototype
\******************************************************************************/
/**
 *
 *  @brief    This function invokes the getHandle API
 *
 *  @param in:
 *            classPtr         : Pointer to OMTB_COMP_HANDLE struct
 *
 *            unsigned int : Instance no of the component
 *
 *  @return   OMX_ERRORTYPE : OMX standard error code
 *
 */

OMX_ERRORTYPE VPSSVFPCNF_GetHandle(OMTB_COMP_HANDLE * , unsigned int );


/******************************************************************************\
 *      VPSSVFPCSC_GetHandle Function Prototype
\******************************************************************************/
/**
 *
 *  @brief    This function invokes the getHandle API
 *
 *  @param in:
 *            classPtr         : Pointer to OMTB_COMP_HANDLE struct
 *
 *            unsigned int : Instance no of the component
 *
 *  @return   OMX_ERRORTYPE : OMX standard error code
 *
 */

OMX_ERRORTYPE VPSSVFPCSC_GetHandle(OMTB_COMP_HANDLE * , unsigned int );

/******************************************************************************\
 *      H264VDEC_SetTemplateDefVal Function Prototype
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

MX_Result H264VDEC_SetTemplateDefVal(OMTB_TEMPLATE_INFO *pTemplate);

/******************************************************************************\
 *      H264VENC_SetTemplateDefVal Function Prototype
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

MX_Result H264VENC_SetTemplateDefVal(OMTB_TEMPLATE_INFO *pTemplate);

/******************************************************************************\
 *      VDEC_SetTemplateDefVal Function Prototype
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

MX_Result VDEC_SetTemplateDefVal(OMTB_TEMPLATE_INFO *pTemplate);


/******************************************************************************\
 *      ADEC_SetTemplateDefVal Function Prototype
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

MX_Result ADEC_SetTemplateDefVal(OMTB_TEMPLATE_INFO *pTemplate);

/******************************************************************************\
 *      VPSSVFCC_SetTemplateDefVal Function Prototype
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

MX_Result VPSSVFCC_SetTemplateDefVal(OMTB_TEMPLATE_INFO *pTemplate);


/******************************************************************************\
 *      VPSSTVP_SetTemplateDefVal Function Prototype
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

MX_Result VPSSTVP_SetTemplateDefVal(OMTB_TEMPLATE_INFO *pTemplate);

/******************************************************************************\
 *      VPSSVFDC_SetTemplateDefVal Function Prototype
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

MX_Result VPSSVFDC_SetTemplateDefVal(OMTB_TEMPLATE_INFO *pTemplate);


/******************************************************************************\
 *      VPSSDC_SetTemplateDefVal Function Prototype
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

MX_Result VPSSDC_SetTemplateDefVal(OMTB_TEMPLATE_INFO *pTemplate);

/******************************************************************************\
 *      VPSSVFPCDEI_SetTemplateDefVal Function Prototype
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

MX_Result VPSSVFPCDEI_SetTemplateDefVal(OMTB_TEMPLATE_INFO *pTemplate);


/******************************************************************************\
 *      VPSSVFPCNF_SetTemplateDefVal Function Prototype
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

MX_Result VPSSVFPCNF_SetTemplateDefVal(OMTB_TEMPLATE_INFO *pTemplate);


/******************************************************************************\
 *      VPSSVFPCSC_SetTemplateDefVal Function Prototype
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

MX_Result VPSSVFPCSC_SetTemplateDefVal(OMTB_TEMPLATE_INFO *pTemplate);


/******************************************************************************\
 *      ALSARECORD_SetTemplateDefVal Function Prototype
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

MX_Result ALSARECORD_SetTemplateDefVal(OMTB_TEMPLATE_INFO *pTemplate);


/******************************************************************************\
 *      ALSAPLAY_SetTemplateDefVal Function Prototype
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

MX_Result ALSAPLAY_SetTemplateDefVal(OMTB_TEMPLATE_INFO *pTemplate);

/******************************************************************************\
 *      OMTB_DisplaySetParams Function Prototype
\******************************************************************************/
/*
 *
 *  @brief    This Function print the values of the index on output console/file
 *
 *  @param in:
 *            nParamIndex: OMX Index
 *            pCompCfgStruct: Pointer to Index structure
 *
 *  @param Out:
 *            None
 *
 */
void OMTB_DisplaySetParams(unsigned int nParamIndex, OMX_PTR pCompCfgStruct);

/******************************************************************************\
 *      OMTB_DisplayGetParams Function Prototype
\******************************************************************************/
/*
 *
 *  @brief    This Function print the values of the index on output console/file
 *
 *  @param in:
 *            nParamIndex: OMX Index
 *            pCompCfgStruct: Pointer to Index structure
 *
 *  @param Out:
 *            None
 *
 */
void OMTB_DisplayGetParams(unsigned int nParamIndex, OMX_PTR pCompCfgStruct);

#ifdef __cplusplus    /* matches __cplusplus construct above */
 }
#endif

#endif

/*--------------------------------- end of file ------------------------------*/

