/*
 * omtbHDVPSSDc.h
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

#ifndef __OMTB_HD_VPSS_DC_H__
#define __OMTB_HD_VPSS_DC_H__


/******************************************************************************\
 *      Includes
\******************************************************************************/

#include "omtbPortParam.h"
#include "omtbTypes.h"
#include "omx_vfdc.h"


/******************************************************************************/

#ifdef __cplusplus    /* required for headers that might */
 extern "C" {         /* be compiled by a C++ compiler */
#endif


/******************************************************************************\
 *      Defines
\******************************************************************************/

#define OMTB_VPSS_DC_MAX_INBUFF_SIZE  (1920 * 1080 * 2)/* Max size of I/P buffer */
#define OMTB_VPSS_DC_COMPONENT_NAME   ("OMX.TI.VPSSM3.CTRL.DC")
                                                    /* Comp name */
#define OMTB_VPSS_DC_COMP_REF_STR     ("dc")    /* comp refernce string */
#define OMTB_VPSS_DC_GROUP_PRIORITY   (2)         /* Task group priority */
#define OMTB_VPSS_DC_TSK_STACK_SIZE   (64 * 1024) /* Task stack size */

#define OMTB_VPSS_DC_NUM_IN_BUFS      (1)  /* No of i/p Buffers for DC */
#define OMTB_VPSS_DC_NUM_OUT_BUFS     (3)  /* No of o/p Buffers for DC */
#define OMTB_VPSS_DC_MAX_NUM_IN_BUFS  (32) /* Max i/p Buffers for DC */
#define OMTB_VPSS_DC_MAX_NUM_OUT_BUFS (32) /* Max o/p Buffers for DC */

#define OMTB_VPSS_DC_DEF_WIDTH        (720)       /* DC def width */
#define OMTB_VPSS_DC_DEF_HEIGHT       (480)       /* DC def height */

#define OMTB_GRPX_DRIVER_INSTANCEID_0   (0)   /*Graphics Inst Id 0*/
#define OMTB_GRPX_DRIVER_INSTANCEID_1   (1)   /*Graphics Inst Id 1*/

#define OMTB_VPSS_DC_DEF_NO_OF_PORTS  (16) /* No of ports */
/******************************************************************************\
 *      Data type definitions
\******************************************************************************/

/*!
*******************************************************************************
*  \struct OMTB_VPSS_DC_INPORT_PARAMS
*  \brief  VPSS DC specific input port parameters
*******************************************************************************
*/

/* Application's private structure for OMX HDVPSS DC Component*/

typedef struct OMTB_VPSS_DC_PRIVATE_T
{
  OMTB_APP_PRIVATE omtbPvt;               /* OMTB common pvt data */
  OMTB_CLIENT_INPORT_PARAMS *inPortParams;  
  OMTB_CLIENT_OUTPORT_PARAMS *outPortParams;
}OMTB_VPSS_DC_PRIVATE;

/* Configuration structure for OMX HDVPSS DC Component */

typedef struct OMTB_VPSS_DC_CONFIG_PARAMS_T
{
  OMTB_BASIC_CONFIG_PARAMS sBasicParams;
                                    /*Basic configuration Params */									
  OMX_PARAM_VFDC_DRIVERINSTID sDvrInstId;
                                    /* DC driver instance ID */
  OMX_PARAM_DC_CUSTOM_MODE_INFO sCustomModeInfo;
                                    /* To configure the custom mode info */									
}OMTB_VPSS_DC_CONFIG_PARAMS;

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
OMX_ERRORTYPE VPSSDC_ClassInit(OMTB_CLIENT_PRIVATE* thisClient);

#ifdef __cplusplus    /* matches __cplusplus construct above */
 }
#endif

#endif


/*--------------------------------- end of file -----------------------------*/
