/*
 * omtbHDVPSSVfpcDei.h
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

#ifndef __OMTB_HD_VPSS_VFPC_DEI_H__
#define __OMTB_HD_VPSS_VFPC_DEI_H__


/******************************************************************************\
 *      Includes
\******************************************************************************/

#include "OMX_TI_Common.h"
#include "omx_vfpc.h"

#include "omtbPortParam.h"
#include "omtbTypes.h"


/******************************************************************************/

#ifdef __cplusplus    /* required for headers that might */
 extern "C" {         /* be compiled by a C++ compiler */
#endif


/******************************************************************************\
 *      Defines
\******************************************************************************/

#define OMTB_VPSS_VFPC_DEI_MAX_INBUFF_SIZE  (1920 * 1080 * 2)/* Max size of I/P buffer */
#define OMTB_VPSS_VFPC_DEI_MAX_OUTBUFF_SIZE (1920 * 1080 * 2)
                                                    /* Max size of I/P buffer */
#define OMTB_VPSS_VFPC_DEI_COMPONENT_NAME   ("OMX.TI.VPSSM3.VFPC.DEIMDUALOUT")  
                                                    /* Comp name */
#define OMTB_VPSS_VFPC_DEI_COMP_REF_STR     ("dei")    /* comp refernce string */
#define OMTB_VPSS_VFPC_DEI_GROUP_PRIORITY   (2)         /* Task group priority */
#define OMTB_VPSS_VFPC_DEI_TSK_STACK_SIZE   (64 * 1024) /* Task stack size */

#define OMTB_VPSS_VFPC_DEI_NUM_IN_BUFS      (1)  /* No of i/p Buffers for VFPC */
#define OMTB_VPSS_VFPC_DEI_NUM_OUT_BUFS     (4)  /* No of o/p Buffers for VFPC */
#define OMTB_VPSS_VFPC_DEI_MAX_NUM_IN_BUFS  (32) /* Max i/p Buffers for VFPC */
#define OMTB_VPSS_VFPC_DEI_MAX_NUM_OUT_BUFS (32) /* Max o/p Buffers for VFPC */

#define OMTB_VPSS_VFPC_DEI_DEF_WIDTH        (720)       /* VFPC def width */
#define OMTB_VPSS_VFPC_DEI_DEF_HEIGHT       (480)       /* VFPC def height */

#define OMTB_VPSS_VFPC_DEI_DEF_SUB_SAMP_FACTOR (1)      /* VFPC def sub sampling factor */

#define OMTB_VPSS_VFPC_DEI_DEF_NO_OF_CHAN    (OMX_VFPC_DEIDUALOUT_MEDIUM_MAX_NUM_CHANNELS)
                                                        /*VFPC def no of channels*/
#define OMTB_VPSS_DEI_MAX_NUM_IN_PORT       (16)
#define OMTB_VPSS_DEI_MAX_NUM_OUT_PORT      (16) 
/******************************************************************************\
 *      Data type definitions
\******************************************************************************/

/*!
*******************************************************************************
*  \struct OMTB_VPSS_VFPC_DEI_INPORT_PARAMS
*  \brief  VPSS VFPC DEI specific input port parameters
*******************************************************************************
*/

typedef struct OMTB_VPSS_VFPC_DEI_INPORT_PARAMS_T
{
  OMTB_INPORT_PARAMS  cmnInParams;    /* Common i/p port params */
  OMX_BUFFERHEADERTYPE* pInBuff[OMTB_VPSS_VFPC_DEI_MAX_NUM_IN_BUFS];
                                      /* I/P Buffers*/
  unsigned int frameCount;            /* Frame counter used to get frame size */
  OMX_COLOR_FORMATTYPE colorFormat;   /* I/P Color Format */
  unsigned int nWidth;                /* I/P Frame Width */
  unsigned int nHeight;               /* I/P Frame Height */
}OMTB_VPSS_VFPC_DEI_INPORT_PARAMS;

/*!
*******************************************************************************
*  \struct OMTB_VPSS_VFPC_DEI_OUTPORT_PARAMS
*  \brief  VPSS VFPC DEI specific output port parameters
*******************************************************************************
*/

typedef struct OMTB_VPSS_VFPC_DEI_OUTPORT_PARAMS_T
{
  OMTB_OUTPORT_PARAMS cmnOutParams;   /* Common o/p port params */
  OMX_BUFFERHEADERTYPE* pOutBuff[OMTB_VPSS_VFPC_DEI_MAX_NUM_OUT_BUFS];/* O/P Bufs */
  OMX_COLOR_FORMATTYPE colorFormat;   /* O/P Color Format */
  OMX_COLOR_FORMATTYPE opColorFormat0;   /* O/P Color Format */
  unsigned int nWidth;                /* O/P Frame Width */
  unsigned int nHeight;               /* O/P Frame Height */

}OMTB_VPSS_VFPC_DEI_OUTPORT_PARAMS;


/* Application's private structure for OMX HDVPSS VFPC DEI Component*/

typedef struct OMTB_VPSS_VFPC_DEI_PRIVATE_T
{

  OMTB_APP_PRIVATE omtbPvt;               /* OMTB common pvt data */
  OMTB_CLIENT_INPORT_PARAMS *inPortParams;  
  OMTB_CLIENT_OUTPORT_PARAMS *outPortParams;
  //OMTB_VPSS_VFPC_DEI_INPORT_PARAMS inPortParams;
                                          /* VPSSVfpcDei specific params */
  //OMTB_VPSS_VFPC_DEI_OUTPORT_PARAMS outPortParams;
                                          /* VPSSVfpcDei specific params */
  char  compressionFormat;                /* encoder compression format */
  void* eofSem;                           /* End of Stream Semaphore */

}OMTB_VPSS_VFPC_DEI_PRIVATE;


/* Configuration structure for OMX HDVPSS VFPC DEI Component */

typedef struct OMTB_VPSS_VFPC_DEI_CONFIG_PARAMS_T
{
  OMTB_BASIC_CONFIG_PARAMS sBasicParams;
                               /*Basic configuration Params */
  OMX_CONFIG_CHANNELNAME sChannelName;
                               /* To configure capture channel name */
  OMX_CONFIG_CHANNELGROUPINFO sConfigChannelGroupInfo;
                               /* To configure the multi port group MFQs */
  OMX_CONFIG_VIDCHANNEL_RESOLUTION sVidChResolutionCfg;
                               /* To configure the Video Channel Resolution */
  OMX_CONFIG_ALG_ENABLE sAlgEnable;
                               /* To configure the Video Alg*/
  OMX_PARAM_COMPPORT_NOTIFYTYPE sCompPortNotifyType;
  							   /* To configure the compport notify type*/
  OMX_PARAM_BUFFERSUPPLIERTYPE sBufSupplier;
 			                   /* To configure the buffer supplier type*/
  OMX_PARAM_BUFFER_MEMORYTYPE sMemTypeCfg;
                               /* To configure the buffer memory type*/
  OMX_CONFIG_SUBSAMPLING_FACTOR sSubSamplingFactor;
                               /* To configure the sub sampling factor*/
  OMX_PARAM_VFPC_NUMCHANNELPERHANDLE sNumChPerHandle;
                               /* To configure the no of channels*/
  OMX_PORT_PARAM_TYPE sPortInit;
                               /* To configure the port init params*/
  OMX_PARAM_PORTDEFINITIONTYPE sPortDefType;									
                                    /* To configure the port defination */								   
}OMTB_VPSS_VFPC_DEI_CONFIG_PARAMS;

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
 *      VPSSVFPCDEI_SetInputPortDefinition Function Definition
\******************************************************************************/
/**
 *
 *  @brief    Set i/p port params.
 *
 *  @param in:
 *            vpssVfpcDeiClient:Pointer to appPrivateType structure
 *
 *  @param Out:
 *            None
 *
 *  @return   OMX_ERRORTYPE - OMX std return/error code
 *
 */

OMX_ERRORTYPE VPSSVFPCDEI_SetInputPortDefinition(
                      OMTB_VPSS_VFPC_DEI_PRIVATE* vpssVfpcDeiClient);


/******************************************************************************\
 *      VPSSVFPCDEI_SetOutputPortDefinition Function Definition
\******************************************************************************/
/**
 *
 *  @brief    Set o/p port params.
 *
 *  @param in:
 *            vpssVfpcDeiClient:Pointer to appPrivateType structure
 *
 *  @param Out:
 *            None
 *
 *  @return   OMX_ERRORTYPE - OMX std return/error code
 *
 */

OMX_ERRORTYPE VPSSVFPCDEI_SetOutputPortDefinition(
                      OMTB_VPSS_VFPC_DEI_PRIVATE* vpssVfpcDeiClient);


/******************************************************************************\
 *      VPSSVFPCDEI_SetPortDefinition Function Prototype
\******************************************************************************/
/**
 *
 *  @brief    Set parameter for input port and output port for VPSS VFPC DEI.
 *
 *  @param in:
 *            vpssVfpcDeiClient:Pointer to appPrivateType structure
 *  @param Out:
 *            None
 *
 *  @return   OMX_ERRORTYPE - OMX std return/error code
 *
 */

OMX_ERRORTYPE VPSSVFPCDEI_SetPortDefinition(void* thisClient);


/******************************************************************************\
 *      VPSSVFPCDEI_GetStructIdx Function Prototype
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

OmtbRet VPSSVFPCDEI_GetStructIdx(
  char *indexStr,
  unsigned int template,
  unsigned int instanceNo,
  unsigned int portIdx,
  unsigned int *nConfigIndex,
  void **pCompCfgStruct);


/******************************************************************************\
 *      VPSSVFPCDEI_FuncTsk Thread Prototype
\******************************************************************************/
/**
 *
 *  @brief    This is a VPSS VFPC DEI thread which invokes during func command
 *
 *  @param in:
 *            void * - Thread args count
 *
 *            void *threadsArg - Pointer to thread arg structure
 *
 *  @return   None
 *
 */

void VPSSVFPCDEI_FuncTsk(void *argc, void *threadsArg);


/******************************************************************************\
 *      VPSSVFPCDEI_ClassInit Function Definition
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
OMX_ERRORTYPE VPSSVFPCDEI_ClassInit(OMTB_CLIENT_PRIVATE* thisClient);
  
#ifdef __cplusplus    /* matches __cplusplus construct above */
 }
#endif

#endif


/*--------------------------------- end of file -----------------------------*/
