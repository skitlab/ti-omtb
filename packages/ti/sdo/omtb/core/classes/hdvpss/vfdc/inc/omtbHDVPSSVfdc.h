/*
 * omtbHDVPSSVfdc.h
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

#ifndef __OMTB_HD_VPSS_VFDC_H__
#define __OMTB_HD_VPSS_VFDC_H__


/******************************************************************************\
 *      Includes
\******************************************************************************/

#include "omtbPortParam.h"
#include "omtbTypes.h"
#include "omx_vfdc.h"
#include "omtbClient.h"

/******************************************************************************/

#ifdef __cplusplus    /* required for headers that might */
 extern "C" {         /* be compiled by a C++ compiler */
#endif


/******************************************************************************\
 *      Defines
\******************************************************************************/

#define OMTB_VPSS_VFDC_MAX_INBUFF_SIZE  (1920 * 1080 * 2)/* Max size of I/P buffer */
#define OMTB_VPSS_VFDC_COMPONENT_NAME   ("OMX.TI.VPSSM3.VFDC")
                                                    /* Comp name */
#define OMTB_VPSS_VFDC_COMP_REF_STR     ("vfdc")    /* comp refernce string */
#define OMTB_VPSS_VFDC_GROUP_PRIORITY   (2)         /* Task group priority */
#define OMTB_VPSS_VFDC_TSK_STACK_SIZE   (64 * 1024) /* Task stack size */

#define OMTB_VPSS_VFDC_NUM_IN_BUFS      (1)  /* No of i/p Buffers for VFDC */
#define OMTB_VPSS_VFDC_NUM_OUT_BUFS     (3)  /* No of o/p Buffers for VFDC */
#define OMTB_VPSS_VFDC_MAX_NUM_IN_BUFS  (32) /* Max i/p Buffers for VFDC */
#define OMTB_VPSS_VFDC_MAX_NUM_OUT_BUFS (32) /* Max o/p Buffers for VFDC */

#define OMTB_VPSS_VFDC_DEF_WIDTH        (720)       /* VFDC def width */
#define OMTB_VPSS_VFDC_DEF_HEIGHT       (480)       /* VFDC def height */

#define OMTB_GRPX_DRIVER_INSTANCEID_0   (0)   /*Graphics Inst Id 0*/
#define OMTB_GRPX_DRIVER_INSTANCEID_1   (1)   /*Graphics Inst Id 1*/

#define OMTB_VPSS_VFDC_DEF_NO_OF_PORTS  (16) /* No of ports */

#define OMTB_VPSS_VFDC_MAX_NUM_IN_PORT (16)
/******************************************************************************\
 *      Data type definitions
\******************************************************************************/

/* Enum Entry for Demos */
typedef enum
{
  OMTB_VC_DEMO, /* VC 2-display demo */
  OMTB_VS_DEMO, /* VS mosaic windows of same size */
  OMTB_MANUAL   /* Configuare each windows as required by user */
}OMTB_VFDC_MOSAIC_WINDOW_CONFIG;

/*!
*******************************************************************************
*  \struct OMTB_VPSS_VFDC_INPORT_PARAMS
*  \brief  VPSS VFDC specific input port parameters
*******************************************************************************
*/

typedef struct OMTB_VPSS_VFDC_INPORT_PARAMS_T
{
  OMTB_INPORT_PARAMS  cmnInParams;    /* Common i/p port params */
  OMX_BUFFERHEADERTYPE* pInBuff[OMTB_VPSS_VFDC_MAX_NUM_IN_BUFS];
                                      /* I/P Buffers*/
  unsigned int frameCount;            /* Frame counter used to get frame size */
  OMX_COLOR_FORMATTYPE colorFormat;   /* O/P Color Format */

}OMTB_VPSS_VFDC_INPORT_PARAMS;


typedef struct OMTB_VPSS_VFDC_MOSAIC_PARAMS_T
{
  /* Window configuration, set the windowId and configure */ 
  unsigned int winStartX;         /* Start of X position*/
  unsigned int winStartY;         /* Start of Y position*/
  unsigned int winWidth;          /* Width of each mosaic display */
  unsigned int winHeight;         /* Height of each mosaic display */  
  unsigned int pitchVFDC_YUV_INT_ADDR_IDX;
                                  /* Pitch of each mosaic display for YUV 422I or 444I */  
  unsigned int pitchVFDC_YUV_SP_Y_ADDR_IDX;
                                  /* Pitch of each mosaic display for the Y of 420SP */  
  unsigned int pitchVFDC_YUV_SP_CBCR_ADDR_IDX;
                                  /* Pitch of each mosaic display for the UV 420SP */    
  VFDC_DataFormat dataFormat;	  /* Data Format */
  unsigned int bpp;               /* bits per pixel*/
  unsigned int priority;          /* */  
  
  unsigned int windowId;          /* select the windows for configuration */
  
  unsigned int dispWindowWidth;   /* Display Window's total Width. 1920 for HD and 720 for SD */
  unsigned int dispWindowHeight;  /* Display Window's total Height 1080 for HD and 480 for SD */
  unsigned int numRows;			  /* Number of mosaic rows */
  unsigned int numCols;			  /* Number of mosaic columns */
  
  OMX_PARAM_VFDC_CREATEMOSAICLAYOUT sMosaicLayout;
}OMTB_VPSS_VFDC_MOSAIC_PARAMS;

/* Application's private structure for OMX HDVPSS VFDC Component*/

typedef struct OMTB_VPSS_VFDC_PRIVATE_T
{

  OMTB_APP_PRIVATE omtbPvt;               /* OMTB common pvt data */
  OMTB_CLIENT_INPORT_PARAMS *inPortParams;  
  OMTB_CLIENT_OUTPORT_PARAMS *outPortParams;
                                          /* VPSSVfdc specific params */
  OMX_VIDEO_CODINGTYPE  compressionFormat; /* encoder compression format */
  void* eofSem;                           /* End of Stream Semaphore */
  unsigned int grpxdriverInst;            /* Graphics instance id */
  unsigned int graphicsFlag;              /* Flag to enable/disable graphics*/

}OMTB_VPSS_VFDC_PRIVATE;

/* Configuration structure for OMX HDVPSS VFDC Component */

typedef struct OMTB_VPSS_VFDC_CONFIG_PARAMS_T
{
  OMTB_BASIC_CONFIG_PARAMS sBasicParams;
                                    /*Basic configuration Params */
  OMX_PARAM_VFDC_DRIVERINSTID sDvrInstId;
                                    /* VFDC driver instance ID */
  OMX_CONFIG_CHANNELGROUPINFO sConfigChannelGroupInfo;
                                    /* To configure the multi port group MFQs */
  OMX_PARAM_BUFFERSUPPLIERTYPE sBufSupplier;
  			                        /* To configure the buffer supplier type*/
  OMX_PARAM_BUFFER_MEMORYTYPE sMemTypeCfg;
                                    /* To configure the buffer memory type*/
  OMTB_VPSS_VFDC_MOSAIC_PARAMS sMosaicParams;
								    /* VPSSVfdc specific mosaic params */
  OMX_PORT_PARAM_TYPE sPortInit;    /* To configure the port init params*/
  OMX_CONFIG_VFDC_MOSAICLAYOUT_PORT2WINMAP sLayoutIndex;
                                    /* To configure the mosaic layout */
  OMX_PARAM_PORTDEFINITIONTYPE sPortDefType;									
                                    /* To configure the port defination */
  OMX_PARAM_DC_CUSTOM_MODE_INFO sCustomModeInfo;
                                    /* To configure the custom mode info */
  OMTB_VFDC_MOSAIC_WINDOW_CONFIG mosaicDemoConfig;
                                    /* Flag to select the demos of fixed config*/
}OMTB_VPSS_VFDC_CONFIG_PARAMS;

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

OMX_ERRORTYPE VPSSVFDC_SetInputPortDefinition(
                      OMTB_VPSS_VFDC_PRIVATE* vpssVfdcClient);


/******************************************************************************\
 *      VPSSVFDC_SetPortDefinition Function Prototype
\******************************************************************************/
/**
 *
 *  @brief    Set parameter for input port and output port for VPSS VFDC.
 *
 *  @param in:
 *            vpssVfdcClient:Pointer to appPrivateType structure
 *  @param Out:
 *            None
 *
 *  @return   OMX_ERRORTYPE - OMX std return/error code
 *
 */

OMX_ERRORTYPE VPSSVFDC_SetPortDefinition(void* thisClient);


/******************************************************************************\
 *      VPSSVFDC_GetStructIdx Function Prototype
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
  void **pCompCfgStruct);

/******************************************************************************\
 *      VPSSVFDC_FuncTsk Thread Prototype
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

void VPSSVFDC_FuncTsk(void *argc, void *threadsArg);


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

OMX_ERRORTYPE VPSSVFDC_SetSymmetricMosaicFormat(
		OMX_HANDLETYPE handle, OMTB_VPSS_VFDC_MOSAIC_PARAMS* vpssVfdcMosaicParams,
		OMTB_VFDC_MOSAIC_WINDOW_CONFIG mosaicDemo);

		
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
OMX_ERRORTYPE VPSSVFDC_ClassInit(OMTB_CLIENT_PRIVATE* thisClient);  
#ifdef __cplusplus    /* matches __cplusplus construct above */
 }
#endif

#endif


/*--------------------------------- end of file -----------------------------*/
