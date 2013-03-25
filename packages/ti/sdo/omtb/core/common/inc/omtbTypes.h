/*
 * omtbTypes.h
 *
 * This file contains data types definition for OMTB.
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

#ifndef __OMTB_TYPES_H__
#define __OMTB_TYPES_H__


/******************************************************************************\
 *      Includes
\******************************************************************************/


/******************************************************************************/

#ifdef __cplusplus    /* required for headers that might */
 extern "C" {         /* be compiled by a C++ compiler */
#endif

#include "timm_osal_interfaces.h"
/******************************************************************************\
 *      Defines
\******************************************************************************/


/******************************************************************************\
 *      Data type definitions
\******************************************************************************/
#define OMX_MAX_NO_PORTS 16

/* Function pointer for GetStructIdx */
typedef OmtbRet (*OMTB_GetStructIdxPtr)(char *indexStr,
                                  unsigned int template,
                                  unsigned int instanceNo,								  
                                  unsigned int portIdx,
                                  unsigned int *nConfigIndex,
                                  void **pCompCfgStruct);
/* Function pointer for SetBufferSize */
typedef OMX_ERRORTYPE (*OMTB_ClassSetBufferSizePtr)(void* thisClient);
/* Function pointer for SetPortDefinition */
typedef OMX_ERRORTYPE (*OMTB_ClassSetPortDefinition)(void* thisClient);

/* OMTB common private structure */
typedef struct OMTB_APP_PRIVATE_T 
{

  OMX_HANDLETYPE handle;                  /* Component handle */
  OMX_CALLBACKTYPE* cb;                   /* callback struct var */
  void* eventSem;                         /* Event Semaphore */
  //void* eofSem;                           /* eos semaphore */

  unsigned int instanceNo;                /* Instance number */
  unsigned int templateNo;                /* Configuration Template number */
  unsigned int flagThrCreated;            /* Func/API thread created Flag */
  unsigned int numInport;                 /* number of input ports */
  unsigned int numOutport;                /* number of outputput ports */  
  unsigned int startOutportIndex;         /* start index of o/p port */
  volatile OMX_STATETYPE  currState;      /* curr state of the component*/ 
  volatile OMX_STATETYPE  prevState;      /* prev state of the component*/   
  char compName[OMX_MAX_STRINGNAME_SIZE]; /* OMX component name */
  unsigned int portDisableFlag[OMX_MAX_NO_PORTS];       /* Port is disabled or not Number 10 stands for max no of ports*/
  
  void* fileReadThrExit;                  /* semaphore for child thread*/
  void* fileWriteThrExit;                 /* semaphore for child thread*/
  void* inputDataReadThrExit;             /* semaphore for I/P data read thread */
  void* outputDataWriteThrExit;           /* semaphore for O/P data write thread */  
  void* connDataStrmThrExit;              /* semaphore for child thread*/
  void* eofSem;                           /* semaphore for end of stream*/
  
  TIMM_OSAL_PTR  fileReadThrdId;          /* thread id for child thread*/
  TIMM_OSAL_PTR  fileWriteThrdId;         /* thread id for child thread*/ 
  TIMM_OSAL_PTR  inDataStrmThrdId;        /* thread id for I/P data read thread*/
  TIMM_OSAL_PTR  outDataStrmThrdId;       /* thread id for O/P data write thread */ 
  TIMM_OSAL_PTR  connDataStrmThrdId;      /* thread id for connection thread*/
  TIMM_OSAL_PTR  apiThreadId;             /* thread id for client API thread*/

  TIMM_OSAL_TaskProc outputDataWriteTask; /* function pointer to data write task */   
  TIMM_OSAL_TaskProc inputDataReadTask;   /* function pointer to data read task */   
  OMTB_GetStructIdxPtr fpGetStructIdx;    /* function pointer to get struct index */   
  OMTB_ClassSetBufferSizePtr fpSetBufferSize; /* function pointer to set buffer size */   
  OMTB_ClassSetPortDefinition fpSetPortDefinition; /* function pointer to set port defination */   
  
  void *localPipe;                       /* pointer to local pipe */	   
  unsigned int numFileInBufs;            /* no of file io buffers */	  
  unsigned int numFileOutBufs;           /* no of file io buffers */  

  unsigned int readSize;                 /* max no of bytes to read */  
  unsigned int writeSize;                /* max no of bytes to write */  
  OMX_CLASS eClassType;                  /* type of the class */   
}OMTB_APP_PRIVATE;

/* Basic configuration parameters */
typedef struct OMTB_BASIC_CONFIG_PARAMS_T 
{
  char inputFile[OMTB_MAX_LEN];     /* Array to store i/p File Name */
  char outputFile[OMTB_MAX_LEN];    /* Array to store o/p File Name */
  char codecType[OMTB_MAX_LEN];     /* Array to store code type */
  unsigned int frameWidth;          /* Variable to store I/P Frame Width */
  unsigned int frameHeight;         /* Variable to store I/P Frame Height */
  unsigned int nStride;             /* # of bytes per span */
  OMX_COLOR_FORMATTYPE colorFormat; /* Variable to store I/P Color Format */
  OMX_COLOR_FORMATTYPE inColorFormat; /* Variable to store I/P Color Format */
  OmtbDataMode dataOutPutMode;      /* For selecting O/P Mode */
  OmtbDataMode dataInPutMode;       /* For selecting I/P Mode */  
  unsigned int numInBuf;            /* Number of i/p buffers */
  unsigned int numOutBuf;           /* Number of o/p buffers */
  unsigned int inBufAlignment;      /* I/P buffer alignment */
  unsigned int inBufContiguous;     /* I/P buffer contiguous or not */
  unsigned int inBufSize;           /* I/P buffer size */
  unsigned int inBufSzFlag;         /* Flag to enable/disable user i/p for i/p
                                       buffer size */
  unsigned int outBufAlignment;     /* O/P buffer alignment */
  unsigned int outBufContiguous;    /* O/P buffer contiguous or not */
  unsigned int outBufSize;          /* O/P buffer size */
  unsigned int outBufSzFlag;        /* Flag to enable/disable user i/p for o/p
                                       buffer size */
  unsigned int nFramerate;          /* Framerate used for port params */
  unsigned int nBitrate;  			/* Bitrate used for port params */ 						   
  //unsigned int tunnelFlag;          /* Flag to enable/disable tunneling */
  unsigned int flagUseInBuffer;     /* 0: OMX_AllocateBuffer & 1:OMX_UseBuffer*/
  unsigned int flagUseOutBuffer;    /* 0: OMX_AllocateBuffer & 1:OMX_UseBuffer*/
  unsigned int flagBasicParam;      /* 0: User will set the basic params,
                                       1: omtb will set the basic params from template structure*/
  char compName[OMX_MAX_STRINGNAME_SIZE];
                                    /* OMX component name */
  unsigned long int maxFileSize;									
  OMX_VIDEO_CODINGTYPE compressionFormat;
                                    /*Variable to store I/P Compression Format*/
									
  unsigned int graphicsFlag;        /* Flag to display the graphics */ 
  unsigned int fileReset;           /* Flag to reset the file pointer */  
  
  char remoteIP[OMX_MAX_STRINGNAME_SIZE];
                                    /* Remote IP */
  unsigned int decodeEnableFlag;
                                   /* Flag to set port params for src/snk component */
unsigned int encodeEnableFlag;     /* Flag to set port params for src/snk component */
}OMTB_BASIC_CONFIG_PARAMS;

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


#ifdef __cplusplus    /* matches __cplusplus construct above */
 }
#endif

#endif


/*--------------------------------- end of file -----------------------------*/

