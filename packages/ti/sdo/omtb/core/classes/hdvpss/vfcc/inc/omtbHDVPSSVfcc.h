/*
 * omtbHDVPSSVfcc.h
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

#ifndef __OMTB_HD_VPSS_VFCC_H__
#define __OMTB_HD_VPSS_VFCC_H__


/******************************************************************************\
 *      Includes
\******************************************************************************/

#include "OMX_TI_Common.h"
#include "omx_vfcc.h"

#include "omtbPortParam.h"
#include "omtbTypes.h"
#include "omtbClient.h"


/******************************************************************************/

#ifdef __cplusplus    /* required for headers that might */
 extern "C" {         /* be compiled by a C++ compiler */
#endif


/******************************************************************************\
 *      Defines
\******************************************************************************/

#define OMTB_VPSS_VFCC_MAX_OUTBUFF_SIZE (1920 * 1080 * 2)
                                                    /* Max size of I/P buffer */
#define OMTB_VPSS_VFCC_COMPONENT_NAME   ("OMX.TI.VPSSM3.VFCC")
                                                    /* Comp name */
#define OMTB_VPSS_VFCC_COMP_REF_STR     ("vfcc")    /* comp refernce string */
#define OMTB_VPSS_VFCC_GROUP_PRIORITY   (2)         /* Task group priority */
#define OMTB_VPSS_VFCC_TSK_STACK_SIZE   (64 * 1024) /* Task stack size */

#define OMTB_VPSS_VFCC_NUM_IN_BUFS      (4)  /* No of i/p Buffers for VFCC */
#define OMTB_VPSS_VFCC_NUM_OUT_BUFS     (6)  /* No of o/p Buffers for VFCC */
#define OMTB_VPSS_VFCC_MAX_NUM_IN_BUFS  (32) /* Max i/p Buffers for VFCC */
#define OMTB_VPSS_VFCC_MAX_NUM_OUT_BUFS (32) /* Max o/p Buffers for VFCC */

#define OMTB_VPSS_VFCC_DEF_WIDTH        (720)       /* VFCC def width */
#define OMTB_VPSS_VFCC_DEF_HEIGHT       (480)       /* VFCC def height */

#define OMTB_VPSS_VIDEO_CAPTURE_MAX_CHNLS (4)       /* Max video capture channels*/

#define OMTB_VPSS_VFCC_DEF_FRAME_SKIP_MASK (0x2AAAAAAA) /* Default frame skip mask*/

#define OMTB_VPSS_VFCC_DEF_NO_OF_PORTS  (16) /* No of ports */

#define OMTB_VPSS_VFCC_MAX_NUM_OUT_PORT  (16)
/******************************************************************************\
 *      Data type definitions
\******************************************************************************/

/*!
*******************************************************************************
*  \struct OMTB_VPSS_VFCC_OUTPORT_PARAMS
*  \brief  VPSS VFCC specific output port parameters
*******************************************************************************
*/

typedef struct OMTB_VPSS_VFCC_OUTPORT_PARAMS_T
{
  OMTB_OUTPORT_PARAMS cmnOutParams;   /* Common o/p port params */
  OMX_BUFFERHEADERTYPE* pOutBuff[OMTB_VPSS_VFCC_MAX_NUM_OUT_BUFS];/* O/P Bufs */
  OMX_COLOR_FORMATTYPE colorFormat;   /* O/P Color Format */
  unsigned int nWidth;                /* I/P Frame Width */
  unsigned int nHeight;               /* I/P Frame Height */

}OMTB_VPSS_VFCC_OUTPORT_PARAMS;


/* Application's private structure for OMX HDVPSS VFCC Component*/

typedef struct OMTB_VPSS_VFCC_PRIVATE_T
{

  OMTB_APP_PRIVATE omtbPvt;               /* OMTB common pvt data */
  OMTB_CLIENT_INPORT_PARAMS *inPortParams;  
  OMTB_CLIENT_OUTPORT_PARAMS *outPortParams;
                                          /* VPSSVfcc specific params */
  OMX_VIDEO_CODINGTYPE  compressionFormat; /* encoder compression format */
  void* eofSem;                           /* End of Stream Semaphore */

}OMTB_VPSS_VFCC_PRIVATE;


/* Configuration structure for OMX HDVPSS VFCC Component */

typedef struct OMTB_VPSS_VFCC_CONFIG_PARAMS_T
{
  OMTB_BASIC_CONFIG_PARAMS sBasicParams;
                                    /*Basic configuration Params */	
  OMX_CONFIG_CHANNELNAME sChannelName;
                                    /* To configure capture channel name */
  OMX_CONFIG_CHANNELGROUPINFO sConfigChannelGroupInfo;
                                    /* To configure the multi port group MFQs */
  OMX_PARAM_BUFFER_MEMORYTYPE sMemTypeCfg;
                                    /* To configure the buffer memory type*/
  OMX_PARAM_BUFFERSUPPLIERTYPE sBufSupplier;
           			                /* To configure the buffer supplier type*/
  OMX_PARAM_VFCC_HWPORT_PROPERTIES sHwPortParam;
                                    /* To configure the video capture h/w properties*/
  OMX_PARAM_VFCC_HWPORT_ID sHwPortId;
                                    /* To configure the video capture port id*/
  OMX_CONFIG_VFCC_FRAMESKIP_INFO sCapSkipFrames;
                                    /* To configure the video capture skip frames*/
  OMX_PARAM_DUPEPORTSINFO sDupPortInfo;
                                    /* To configure the Dup port*/    
  OMX_PORT_PARAM_TYPE sPortInit;    /* To configure the port init params*/
  
  OMX_PARAM_VIDEO_CAPTURE_STATS sCapStats;
                                    /* To get the capture stats*/
  OMX_CONFIG_VIDEO_CAPTURE_RESET_STATS	sCapResetStats;
                                    /* To reset the capture stats*/  
  OMX_PARAM_PORTDEFINITIONTYPE sPortDefType;									
                                    /* To configure the port defination */									
}OMTB_VPSS_VFCC_CONFIG_PARAMS;

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

OMX_ERRORTYPE VPSSVFCC_SetOutputPortDefinition(
                      OMTB_VPSS_VFCC_PRIVATE* vpssVfccClient);


/******************************************************************************\
 *      VPSSVFCC_SetPortDefinition Function Prototype
\******************************************************************************/
/**
 *
 *  @brief    Set parameter for input port and output port for VPSS VFCC.
 *
 *  @param in:
 *            vpssVfccClient:Pointer to appPrivateType structure
 *  @param Out:
 *            None
 *
 *  @return   OMX_ERRORTYPE - OMX std return/error code
 *
 */

OMX_ERRORTYPE VPSSVFCC_SetPortDefinition(void* thisClient);


/******************************************************************************\
 *      VPSSVFCC_GetStructIdx Function Prototype
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
  void **pCompCfgStruct);


/******************************************************************************\
 *      VPSSVFCC_FuncTsk Thread Prototype
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

void VPSSVFCC_FuncTsk(void *argc, void *threadsArg);

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
OMX_ERRORTYPE VPSSVFCC_ClassInit(OMTB_CLIENT_PRIVATE* thisClient);  
#ifdef __cplusplus    /* matches __cplusplus construct above */
 }
#endif

#endif


/*--------------------------------- end of file -----------------------------*/
