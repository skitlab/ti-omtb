/*
 * omtbClient.h
 *
 * This file contains omtb prototypes/declarations utility commands.
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

#ifndef __OMTB_CLIENT_H__
#define __OMTB_CLIENT_H__


/******************************************************************************\
 *      Includes
\******************************************************************************/

#include "OMX_TI_Common.h"
#include "omtbPortParam.h"
#include "omtbTypes.h"
#include "omtbVdecParser.h"
#include "omtbH264VdecParser.h"
#include "omtbMpeg2VdecParser.h"

/******************************************************************************/

#ifdef __cplusplus    /* required for headers that might */
 extern "C" {         /* be compiled by a C++ compiler */
#endif
#define OMTB_CLIENT_MAX_NUM_IN_BUFS 8
#define OMTB_CLIENT_MAX_NUM_OUT_BUFS 8

/*Note: for vdec no of buffers would be mutiplied with 4 i.e (OMTB_CLIENT_MAX_NUM_FILE_IN_BUFS * 4) */
#define OMTB_CLIENT_MAX_NUM_FILE_IN_BUFS 2
#define OMTB_CLIENT_MAX_NUM_FILE_OUT_BUFS 2

typedef struct OMTB_CLIENT_PRIVATE_T  OMTB_CLIENT_PRIVATE;

/* Function pointer for ClassInit */								  
typedef OMX_ERRORTYPE (*OMTB_ClassInitPtr)(OMTB_CLIENT_PRIVATE* thisClient);
							  
OMX_ERRORTYPE OMTB_ClientConnectComponents(OMTB_CLIENT_PRIVATE *handleCompPrivA,
                                     unsigned int compAPortOut,
                                     OMTB_CLIENT_PRIVATE *handleCompPrivB,
                                     unsigned int compBPortIn);
void OMTB_ClientApiTsk(void *argc, void *threadsArg);

OMX_ERRORTYPE OMTB_ClientFillBufferDone(OMX_HANDLETYPE hComponent,
                                        OMX_PTR ptrAppData,
                                        OMX_BUFFERHEADERTYPE * pBuffer);

OMX_ERRORTYPE OMTB_ClientEmptyBufferDone(OMX_HANDLETYPE hComponent,
                                         OMX_PTR ptrAppData,
                                         OMX_BUFFERHEADERTYPE * pBuffer);
                                     
OMX_ERRORTYPE OMTB_ClientAllocateInputResources(OMTB_CLIENT_PRIVATE *
                                                thisClient);
												
OMX_ERRORTYPE OMTB_ClientEventHandler(OMX_OUT OMX_HANDLETYPE hComponent,
                                      OMX_OUT OMX_PTR pAppData,
                                      OMX_OUT OMX_EVENTTYPE eEvent,
                                      OMX_OUT OMX_U32 nData1,
                                      OMX_OUT OMX_U32 nData2,
                                      OMX_OUT OMX_PTR pEventData);

void OMTB_InputDataRead(void *argc, void *threadsArg);
void OMTB_OutputDataWrite(void *argc, void *threadsArg);

typedef enum 
{
    OMTB_CLIENT_PIPE_CMD_ETB,
    OMTB_CLIENT_PIPE_CMD_FTB,
    OMTB_CLIENT_PIPE_CMD_EBD,
    OMTB_CLIENT_PIPE_CMD_FBD,
	OMTB_CLIENT_PIPE_CMD_EXIT,
    OMTB_CommandMax = 0X7FFFFFFF
} OMTB_CLIENT_PIPE_CMD_TYPE;

typedef enum 
{
    OMTB_INPUT_PORT,
    OMTB_OUTPUT_PORT,
    OMTB_PortMax = 0X7FFFFFFF
} OMTB_PORT_TYPE;

typedef struct OMTB_CLIENT_SNT_CONNECT_T
{
  OMX_U32        remotePort;
  void          *remotePipe;  /* for making ETB / FTB calls to connected comp */
  OMTB_CLIENT_PRIVATE *remoteClient;  /* For allocate / use buffer */
}OMTB_CLIENT_SNT_CONNECT;

typedef struct OMTB_CLIENT_FILEIO_PARAMS_T
{
  char *pBuff; 			 	 /* pointer to buffer */
  unsigned int nOffset;      /* start of valid bytes */ 
  int buffLen;               /* size of valid bytes*/
  OMTB_CLIENT_PIPE_CMD_TYPE cmd; /* Pipe Command */
}OMTB_CLIENT_FILEIO_PARAMS;

typedef struct OMTB_CLIENT_INPORT_PARAMS_T
{
  OMTB_INPORT_PARAMS  cmnInParams;          /* Common i/p port params */
  OMTB_CLIENT_SNT_CONNECT connInfo;
  OMX_BUFFERHEADERTYPE* pInBuff[OMTB_CLIENT_MAX_NUM_IN_BUFS];
                                            /* I/P Buffers*/
  FILE *frameFile;                          /* Frame Size File Pointer */
  unsigned int frameSize[OMTB_MAX_FRAME];   /* Buffer for keeping frame sizes */
  unsigned int frameCount;            /* Frame counter used to get frame size */
  OMX_COLOR_FORMATTYPE colorFormat; /* Variable to store O/P Color Format */
  unsigned int nWidth;                /* I/P Frame Width */
  unsigned int nHeight;               /* I/P Frame Height */
  H264_ParsingCtx  h264ParseCtx;           /* Contex to H.264 Video Decoder Parser */ 
  Mpeg2_ParsingCtx mpeg2ParseCtx;           /* Contex to MPEG2Video Decoder Parser */ 
  OMTB_CLIENT_FILEIO_PARAMS  sFileIOBuff[OMTB_CLIENT_MAX_NUM_FILE_IN_BUFS * 4]; /* multiplied by 4 for vdec */
                                       /* file Input/Output buffers */
  OMX_BUFFERHEADERTYPE tempBuff;       /* patch to exit the h264venc write thread */  
  
  OMTB_CLIENT_FILEIO_PARAMS adecBuffer; /* additional buffer to handle whole or in-part */
    
}OMTB_CLIENT_INPORT_PARAMS;

typedef struct OMTB_CLIENT_PIPE_MSG_T
{
  OMTB_CLIENT_PIPE_CMD_TYPE cmd;
  OMX_BUFFERHEADERTYPE      *pbufHeader;  /* used for EBD/FBD  */
  OMX_BUFFERHEADERTYPE      bufHeader;    /* used for ETB/FTB */
} OMTB_CLIENT_PIPE_MSG;


/*!
*******************************************************************************
*  \struct OMTB_H264_VDEC_OUTPORT_PARAMS
*  \brief  H264 video decoder specific output port parameters
*******************************************************************************
*/

typedef struct OMTB_CLIENT_OUTPORT_PARAMS_T
{
  OMTB_OUTPORT_PARAMS cmnOutParams;   /* Common o/p port params */
  OMTB_CLIENT_SNT_CONNECT connInfo;  
  OMX_BUFFERHEADERTYPE* pOutBuff[OMTB_CLIENT_MAX_NUM_OUT_BUFS];
                                      /* O/P Bufs */
  OMX_COLOR_FORMATTYPE colorFormat;   /* O/P Color Format */
  unsigned int nWidth;                /* I/P Frame Width */
  unsigned int nHeight;               /* I/P Frame Height */
  
  OMTB_CLIENT_FILEIO_PARAMS  sFileIOBuff[OMTB_CLIENT_MAX_NUM_FILE_OUT_BUFS];
                                       /* file Input/Output buffers */
  OMX_BUFFERHEADERTYPE tempBuff;       /* patch to exit the h264venc write thread */   									   
}OMTB_CLIENT_OUTPORT_PARAMS;

struct OMTB_CLIENT_PRIVATE_T {
  OMTB_APP_PRIVATE omtbPvt;               /* OMTB common pvt data */
  OMTB_CLIENT_INPORT_PARAMS *inPortParams;                                          
  OMTB_CLIENT_OUTPORT_PARAMS *outPortParams;
};

#ifdef __cplusplus    /* matches __cplusplus construct above */
 }
#endif

#endif

