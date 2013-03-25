/*
 * omtbHDVPSSTvp.h
 *
 * This file contains component specific definitions/data types etc.
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

#ifndef __OMTB_HD_VPSS_TVP_H__
#define __OMTB_HD_VPSS_TVP_H__


/******************************************************************************\
 *      Includes
\******************************************************************************/

#include "OMX_TI_Common.h"
#include "omx_ctrl.h"

#include "omtbPortParam.h"
#include "omtbTypes.h"


/******************************************************************************/

#ifdef __cplusplus    /* required for headers that might */
 extern "C" {         /* be compiled by a C++ compiler */
#endif


/******************************************************************************\
 *      Defines
\******************************************************************************/

#define OMTB_VPSS_TVP_COMPONENT_NAME   ("OMX.TI.VPSSM3.CTRL.TVP")
                                                    /* Comp name */
#define OMTB_VPSS_TVP_COMP_REF_STR     ("tvp")    /* comp refernce string */

#define OMTB_VPSS_TVP_DEF_WIDTH        (720)       /* TVP def width */
#define OMTB_VPSS_TVP_DEF_HEIGHT       (480)       /* TVP def height */
/******************************************************************************\
 *      Data type definitions
\******************************************************************************/

/*!
*******************************************************************************
*  \struct OMTB_VPSS_TVP_OUTPORT_PARAMS
*  \brief  VPSS TVP specific output port parameters
*******************************************************************************
*/

/* Application's private structure for OMX HDVPSS TVP Component*/

typedef struct OMTB_VPSS_TVP_PRIVATE_T
{
  OMTB_APP_PRIVATE omtbPvt;               /* OMTB common pvt data */
  OMTB_CLIENT_INPORT_PARAMS *inPortParams;  
  OMTB_CLIENT_OUTPORT_PARAMS *outPortParams;
}OMTB_VPSS_TVP_PRIVATE;


/* Configuration structure for OMX HDVPSS TVP Component */

typedef struct OMTB_VPSS_TVP_CONFIG_PARAMS_T
{
  OMTB_BASIC_CONFIG_PARAMS sBasicParams;
                                    /*Basic configuration Params */	

  OMX_PARAM_VFCC_HWPORT_PROPERTIES sHwPortParam;
                                    /* To configure the video capture h/w properties*/
  OMX_PARAM_VFCC_HWPORT_ID sHwPortId;
                                    /* To configure the video capture port id*/

  OMX_PARAM_CTRL_VIDDECODER_INFO sVidDecParam;
                                   /* To Configure the TVP video decoder params*/  
}OMTB_VPSS_TVP_CONFIG_PARAMS;

/******************************************************************************\
 *      Macros
\******************************************************************************/


/******************************************************************************\
 *      Globals
\******************************************************************************/


/******************************************************************************\
 *      External Object Definitions
\******************************************************************************/


/******************************************************************************\
 *      Public Function Prototypes
\******************************************************************************/

/******************************************************************************\
 *      VPSSTVP_GetStructIdx Function Prototype
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
  void **pCompCfgStruct);

  
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
OMX_ERRORTYPE VPSSTVP_ClassInit(OMTB_CLIENT_PRIVATE* thisClient);  

#ifdef __cplusplus    /* matches __cplusplus construct above */
 }
#endif

#endif


/*--------------------------------- end of file -----------------------------*/
