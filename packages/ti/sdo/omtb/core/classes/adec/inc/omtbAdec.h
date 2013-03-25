/*
 * omtbAdec.h
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

#ifndef __OMTB_ADEC_H__
#define __OMTB_ADEC_H__


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

#define OMTB_ADEC_MAX_INBUFF_SIZE   (1920 * 1080)/* Max size of I/P buffer */
#define OMTB_ADEC_MAX_OUTBUFF_SIZE  ((2048 * 1176 * 3)>>1)/* Max size of O/P buffer */
                                          /* 2048 =  1920 + Pad Width, 1176 = 1080 + Pad Height */
#define OMTB_ADEC_COMPONENT_NAME   ("OMX.TI.DSP.AUDDEC")
                                                    /* Comp name */
#define OMTB_ADEC_COMP_REF_STR     ("adec")/* comp refernce string */
#define OMTB_ADEC_GROUP_PRIORITY   (2)         /* Task group priority */
#define OMTB_ADEC_TSK_STACK_SIZE   (30 * 1024) /* Task stack size */
#define OMTB_ADEC_NUM_IN_BUFS      (4)  /* No of i/p Buffers for ADEC */
#define OMTB_ADEC_NUM_OUT_BUFS     (4)  /* No of o/p Buffers for ADEC */
#define OMTB_ADEC_MAX_NUM_IN_BUFS  (32) /* Max i/p Buffers for ADEC */
#define OMTB_ADEC_MAX_NUM_OUT_BUFS (32) /* Max o/p Buffers for ADEC */

#define OMTB_ADEC_INPUT_PORT_IDX   (0) /* Input port index */
#define OMTB_ADEC_OUTPUT_PORT_IDX  (1) /* Output port index */
#define OMTB_ADEC_INVALID_PORT_IDX (5) /* Invalid port index */

#define OMTB_ADEC_DEF_FRM_RATE       (30 << 16)  /* Q16 format */
#define OMTB_ADEC_DEF_BIT_RATE       (10485760)  /* 10 Mbps */

#define OMTB_ADEC_MAX_IN_PORT           (1)
#define OMTB_ADEC_MAX_OUT_PORT          (1)

#define OMTB_ADEC_DEF_NO_OF_PORTS     (2) /* No of ports */
#define OMTB_ADEC_DEF_START_PORT_NUM  (0) /* Start Port Number */

/******************************************************************************\
 *      Data type definitions
\******************************************************************************/

/*!
*******************************************************************************
*  \struct OMTB_ADEC_INPORT_PARAMS
*  \brief  video decoder specific input port parameters
*******************************************************************************
*/

typedef struct OMTB_ADEC_INPORT_PARAMS_T
{
  OMTB_INPORT_PARAMS  cmnInParams;          /* Common i/p port params */
  OMX_BUFFERHEADERTYPE* pInBuff[OMTB_ADEC_MAX_NUM_IN_BUFS];
                                            /* I/P Buffers*/
  FILE *frameFile;                          /* Frame Size File Pointer */
  unsigned int frameSize[OMTB_MAX_FRAME];   /* Buffer for keeping frame sizes */
  unsigned int frameCount;            /* Frame counter used to get frame size */
  OMX_COLOR_FORMATTYPE colorFormat; /* Variable to store O/P Color Format */
  unsigned int nWidth;                /* I/P Frame Width */
  unsigned int nHeight;               /* I/P Frame Height */
}OMTB_ADEC_INPORT_PARAMS;


/*!
*******************************************************************************
*  \struct OMTB_ADEC_OUTPORT_PARAMS
*  \brief  video decoder specific output port parameters
*******************************************************************************
*/

typedef struct OMTB_ADEC_OUTPORT_PARAMS_T
{
  OMTB_OUTPORT_PARAMS cmnOutParams;   /* Common o/p port params */
  OMX_BUFFERHEADERTYPE* pOutBuff[OMTB_ADEC_MAX_NUM_OUT_BUFS];
                                      /* O/P Bufs */
  OMX_COLOR_FORMATTYPE colorFormat;   /* O/P Color Format */
  unsigned int nWidth;                /* I/P Frame Width */
  unsigned int nHeight;               /* I/P Frame Height */

}OMTB_ADEC_OUTPORT_PARAMS;


/* Application's private structure for OMX Audio Decoder Component*/

typedef struct OMTB_ADEC_PRIVATE_T
{

  OMTB_APP_PRIVATE omtbPvt;               /* OMTB common pvt data */
  OMTB_CLIENT_INPORT_PARAMS *inPortParams;
                                          /* adec specific params */
  OMTB_CLIENT_OUTPORT_PARAMS *outPortParams;
                                          /* adec specific params */
  char  compressionFormat;                /* encoder compression format */
  void* eofSem;                           /* End of Stream Semaphore */

}OMTB_ADEC_PRIVATE;


/* Configuration structure for OMX Audio Decoder Component */

typedef struct OMTB_ADEC_CONFIG_PARAMS_T
{
  OMTB_BASIC_CONFIG_PARAMS sBasicParams;
                                    /*Basic configuration Params */
  OMX_CONFIG_CHANNELNAME sChannelName;
                                    /* To configure capture channel name */
  OMX_PARAM_BUFFER_MEMORYTYPE sMemTypeCfg;
  									/* To configure the buffer memory type*/
  OMX_PARAM_BUFFERSUPPLIERTYPE sBufSupplier;
  									/* To configure the buffer supplier type*/
  OMX_AUDIO_PARAM_PORTFORMATTYPE sAudioPortFormat;
  									/* To configure the video params*/
  OMX_PARAM_FILEMODE_TYPE sFileModeCfg;
                                    /* To configure the file mode*/
  OMX_PORT_PARAM_TYPE sPortInit;    /* To configure the port init params*/
  OMX_PARAM_COMPPORT_NOTIFYTYPE sCompPortNotifyType;
  									/* To configure the compport notify type*/
  OMX_PARAM_PORTDEFINITIONTYPE sPortDefType;									
                                    /* To configure the port defination */										
}OMTB_ADEC_CONFIG_PARAMS;

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
 *      ADEC_SetPortDefinition Function Prototype
\******************************************************************************/
/**
 *
 *  @brief    Set parameter for input port and output port for decoder.
 *
 *  @param in:
 *            thisClient:Pointer to appPrivateType structure
 *  @param Out:
 *            None
 *
 *  @return   OMX_ERRORTYPE - OMX std return/error code
 *
 */

OMX_ERRORTYPE ADEC_SetPortDefinition(
                      void* thisClient);


/******************************************************************************\
 *      ADEC_GetStructIdx Function Prototype
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

OmtbRet ADEC_GetStructIdx(
  char *indexStr,
  unsigned int template,
  unsigned int instanceNo,
  unsigned int portIdx,
  unsigned int *nConfigIndex,
  void **pCompCfgStruct);


/******************************************************************************\
 *      ADEC_SetInputPortDefinition Function Definition
\******************************************************************************/
/**
 *
 *  @brief    Set i/p port params.
 *
 *  @param in:
 *            adecClient:Pointer to appPrivateType structure
 *
 *  @param Out:
 *            None
 *
 *  @return   OMX_ERRORTYPE - OMX std return/error code
 *
 */

OMX_ERRORTYPE ADEC_SetInputPortDefinition(OMTB_ADEC_PRIVATE* adecClient);


/******************************************************************************\
 *      ADEC_SetOutputPortDefinition Function Definition
\******************************************************************************/
/**
 *
 *  @brief    Set o/p port params.
 *
 *  @param in:
 *            adecClient:Pointer to appPrivateType structure
 *
 *  @param Out:
 *            None
 *
 *  @return   OMX_ERRORTYPE - OMX std return/error code
 *
 */

OMX_ERRORTYPE ADEC_SetOutputPortDefinition(OMTB_ADEC_PRIVATE* adecClient);

/******************************************************************************\
 *      ADEC_FuncTsk Thread Prototype
\******************************************************************************/
/**
 *
 *  @brief    This is a Audio Dec thread which invokes during func command
 *
 *  @param in:
 *            void * - Thread args count
 *
 *            void *threadsArg - Pointer to thread arg structure
 *
 *  @return   None
 *
 */

void ADEC_FuncTsk(void *argc, void *threadsArg);


/******************************************************************************\
 *      ADEC_ClassInit Function Definition
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
OMX_ERRORTYPE ADEC_ClassInit(
        OMTB_CLIENT_PRIVATE* thisClient);	
		
#ifdef __cplusplus    /* matches __cplusplus construct above */
 }
#endif

#endif


/*--------------------------------- end of file -----------------------------*/
