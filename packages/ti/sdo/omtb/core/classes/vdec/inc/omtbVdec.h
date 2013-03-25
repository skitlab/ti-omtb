/*
 * omtbVdec.h
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

#ifndef __OMTB_VDEC_H__
#define __OMTB_VDEC_H__


/******************************************************************************\
 *      Includes
\******************************************************************************/

#include "OMX_TI_Common.h"
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

#define OMTB_VDEC_MAX_INBUFF_SIZE   (1920 * 1080)/* Max size of I/P buffer */
#define OMTB_VDEC_MAX_OUTBUFF_SIZE  ((2048 * 1176 * 3)>>1)/* Max size of O/P buffer */
                                          /* 2048 =  1920 + Pad Width, 1176 = 1080 + Pad Height */
#define OMTB_VDEC_COMPONENT_NAME   ("OMX.TI.DUCATI.VIDDEC")
                                                    /* Comp name */
#define OMTB_VDEC_COMP_REF_STR     ("vdec")/* comp refernce string */
#define OMTB_VDEC_GROUP_PRIORITY   (2)         /* Task group priority */
#define OMTB_VDEC_TSK_STACK_SIZE   (30 * 1024) /* Task stack size */
#define OMTB_VDEC_NUM_IN_BUFS      (4)  /* No of i/p Buffers for VDEC */
#define OMTB_VDEC_NUM_OUT_BUFS     (4)  /* No of o/p Buffers for VDEC */
#define OMTB_VDEC_MAX_NUM_IN_BUFS  (32) /* Max i/p Buffers for VDEC */
#define OMTB_VDEC_MAX_NUM_OUT_BUFS (32) /* Max o/p Buffers for VDEC */

#define OMTB_VDEC_INPUT_PORT_IDX   (0) /* Input port index */
#define OMTB_VDEC_OUTPUT_PORT_IDX  (1) /* Output port index */
#define OMTB_VDEC_INVALID_PORT_IDX (5) /* Invalid port index */

/* Default width and height used for video decoders */
#define OMTB_VDEC_DEF_WIDTH        (720)
#define OMTB_VDEC_DEF_HEIGHT       (480)

#define OMTB_VDEC_DEF_FRM_RATE       (30 << 16)  /* Q16 format */
#define OMTB_VDEC_DEF_BIT_RATE       (10485760)  /* 10 Mbps */

#define OMTB_VDEC_MAX_IN_PORT           (1)
#define OMTB_VDEC_MAX_OUT_PORT          (1)

#define OMTB_VDEC_DEF_NO_OF_PORTS     (2) /* No of ports */
#define OMTB_VDEC_DEF_START_PORT_NUM  (0) /* Start Port Number */

#define OMTB_VDEC_PADX (32)
#define OMTB_VDEC_PADY (24)
/******************************************************************************\
 *      Data type definitions
\******************************************************************************/

/*!
*******************************************************************************
*  \struct OMTB_VDEC_INPORT_PARAMS
*  \brief  video decoder specific input port parameters
*******************************************************************************
*/

typedef struct OMTB_VDEC_INPORT_PARAMS_T
{
  OMTB_INPORT_PARAMS  cmnInParams;          /* Common i/p port params */
  OMX_BUFFERHEADERTYPE* pInBuff[OMTB_VDEC_MAX_NUM_IN_BUFS];
                                            /* I/P Buffers*/
  FILE *frameFile;                          /* Frame Size File Pointer */
  unsigned int frameSize[OMTB_MAX_FRAME];   /* Buffer for keeping frame sizes */
  unsigned int frameCount;            /* Frame counter used to get frame size */
  OMX_COLOR_FORMATTYPE colorFormat; /* Variable to store O/P Color Format */
  unsigned int nWidth;                /* I/P Frame Width */
  unsigned int nHeight;               /* I/P Frame Height */
}OMTB_VDEC_INPORT_PARAMS;


/*!
*******************************************************************************
*  \struct OMTB_VDEC_OUTPORT_PARAMS
*  \brief  video decoder specific output port parameters
*******************************************************************************
*/

typedef struct OMTB_VDEC_OUTPORT_PARAMS_T
{
  OMTB_OUTPORT_PARAMS cmnOutParams;   /* Common o/p port params */
  OMX_BUFFERHEADERTYPE* pOutBuff[OMTB_VDEC_MAX_NUM_OUT_BUFS];
                                      /* O/P Bufs */
  OMX_COLOR_FORMATTYPE colorFormat;   /* O/P Color Format */
  unsigned int nWidth;                /* I/P Frame Width */
  unsigned int nHeight;               /* I/P Frame Height */

}OMTB_VDEC_OUTPORT_PARAMS;


/* Application's private structure for OMX Video Decoder Component*/

typedef struct OMTB_VDEC_PRIVATE_T
{

  OMTB_APP_PRIVATE omtbPvt;               /* OMTB common pvt data */
  OMTB_CLIENT_INPORT_PARAMS *inPortParams;
                                          /* H264Vdec specific params */
  OMTB_CLIENT_OUTPORT_PARAMS *outPortParams;
                                          /* H264Vdec specific params */
  char  compressionFormat;                /* encoder compression format */
  void* eofSem;                           /* End of Stream Semaphore */

}OMTB_VDEC_PRIVATE;


/* Configuration structure for OMX Video Decoder Component */

typedef struct OMTB_VDEC_CONFIG_PARAMS_T
{
  OMTB_BASIC_CONFIG_PARAMS sBasicParams;
                                    /*Basic configuration Params */
  OMX_VIDEO_CODINGTYPE compressionFormat;
                                    /*Variable to store I/P Compression Format*/
  OMX_CONFIG_CHANNELNAME sChannelName;
                                    /* To configure capture channel name */
  OMX_CONFIG_CHANNELGROUPINFO sConfigChannelGroupInfo;
                                    /* To configure the multi port group MFQs */
  OMX_PARAM_BUFFER_MEMORYTYPE sMemTypeCfg;
  									/* To configure the buffer memory type*/
  OMX_PARAM_BUFFERSUPPLIERTYPE sBufSupplier;
  									/* To configure the buffer supplier type*/
  OMX_VIDEO_PARAM_PORTFORMATTYPE sVideoPortFormat;
  									/* To configure the video params*/
  OMX_CONFIG_MBERRORREPORTINGTYPE sMbErrorReporting;
                  				    /* To configure the Mb Error Reporting Type*/
  OMX_PARAM_FILEMODE_TYPE sFileModeCfg;
                                    /* To configure the file mode*/
  OMX_PORT_PARAM_TYPE sPortInit;    /* To configure the port init params*/
  OMX_VIDEO_PARAM_AVCTYPE avcParams;/* To get the avc params */  
  OMX_PARAM_MACROBLOCKSTYPE sMBType;/* To get the info of the MB */    
  OMX_PARAM_COMPPORT_NOTIFYTYPE sCompPortNotifyType;
  									/* To configure the compport notify type*/
  OMX_PARAM_PORTDEFINITIONTYPE sPortDefType;									
                                    /* To configure the port defination */										
}OMTB_VDEC_CONFIG_PARAMS;

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
 *      VDEC_SetPortDefinition Function Prototype
\******************************************************************************/
/**
 *
 *  @brief    Set parameter for input port and output port for decoder.
 *
 *  @param in:
 *            h264VdecClient:Pointer to appPrivateType structure
 *  @param Out:
 *            None
 *
 *  @return   OMX_ERRORTYPE - OMX std return/error code
 *
 */

OMX_ERRORTYPE VDEC_SetPortDefinition(
                      void* thisClient);


/******************************************************************************\
 *      VDEC_GetStructIdx Function Prototype
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

OmtbRet VDEC_GetStructIdx(
  char *indexStr,
  unsigned int template,
  unsigned int instanceNo,
  unsigned int portIdx,
  unsigned int *nConfigIndex,
  void **pCompCfgStruct);


/******************************************************************************\
 *      VDEC_SetInputPortDefinition Function Definition
\******************************************************************************/
/**
 *
 *  @brief    Set i/p port params.
 *
 *  @param in:
 *            h264VdecClient:Pointer to appPrivateType structure
 *
 *  @param Out:
 *            None
 *
 *  @return   OMX_ERRORTYPE - OMX std return/error code
 *
 */

OMX_ERRORTYPE VDEC_SetInputPortDefinition(OMTB_VDEC_PRIVATE* h264VdecClient);


/******************************************************************************\
 *      VDEC_SetOutputPortDefinition Function Definition
\******************************************************************************/
/**
 *
 *  @brief    Set o/p port params.
 *
 *  @param in:
 *            h264VdecClient:Pointer to appPrivateType structure
 *
 *  @param Out:
 *            None
 *
 *  @return   OMX_ERRORTYPE - OMX std return/error code
 *
 */

OMX_ERRORTYPE VDEC_SetOutputPortDefinition(OMTB_VDEC_PRIVATE* h264VdecClient);

/******************************************************************************\
 *      VDEC_FuncTsk Thread Prototype
\******************************************************************************/
/**
 *
 *  @brief    This is a Video Dec thread which invokes during func command
 *
 *  @param in:
 *            void * - Thread args count
 *
 *            void *threadsArg - Pointer to thread arg structure
 *
 *  @return   None
 *
 */

void VDEC_FuncTsk(void *argc, void *threadsArg);


/******************************************************************************\
 *      VDEC_ClassInit Function Definition
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
OMX_ERRORTYPE VDEC_ClassInit(
        OMTB_CLIENT_PRIVATE* thisClient);	
		
#ifdef __cplusplus    /* matches __cplusplus construct above */
 }
#endif

#endif


/*--------------------------------- end of file -----------------------------*/
