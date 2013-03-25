/*
 * omtbPortParam.h
 *
 * This file contains structure specific to OMX components port
 * definition related parameters.
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

#ifndef __OMTB_PORT_PARAM_H__
#define __OMTB_PORT_PARAM_H__

/******************************************************************************\
 *      Includes
\******************************************************************************/


/******************************************************************************/

#ifdef __cplusplus   /* required for headers that might */
 extern "C" {         /* be compiled by a C++ compiler */
#endif


/******************************************************************************\
 *      Defines
\******************************************************************************/

/* Max video frame height and width */
#define OMTB_MAX_VID_WIDTH                (1920)
#define OMTB_MAX_VID_HEIGHT               (1088)


/******************************************************************************\
 *      Data type definitions
\******************************************************************************/

/*!
 *******************************************************************************
 *  \struct OMTB_INPORT_PARAMS
 *  \brief  Structure for openmax component input port related param
 *******************************************************************************
 */

typedef struct OMTB_INPORT_PARAMS_T
{

  OMX_PARAM_PORTDEFINITIONTYPE* pInPortDef;   /* input port def var */
  OMX_PTR ipBufPipe;              /* input pipe */
  FILE *fin;                      /* I/P File Pointer */
  //void* inputDataReady;           /* EmptyBuffer Done Semaphore */
  unsigned int flagInputEos;      /* EOS indication flag */
  unsigned int bufferInSize;      /* I/P buffer size */
  unsigned int inBufSzFlag;       /* Flag to enable/disable user i/p for i/p
                                     buffer size */
  void* inDataStrmThrdId;         /* I/P data streaming thread id */
  unsigned int flagUseInBuffer;   /* 0: OMX_AllocateBuffer & 1: OMX_UseBuffer*/
  OmtbDataMode dataInPutMode;     /* For selecting I/P Mode */
  unsigned int numInBuf;          /* Number of i/p buffers */
  unsigned int inBufAlignment;    /* I/P buffer alignment */
  unsigned int inBufContiguous;   /* I/P buffer contiguous or not */
  
  OMX_PTR fileIpBufPipe;          /* file input pipe */
  OMX_PTR fileOpBufPipe;          /* file output pipe */  
  OMX_BOOL fileReset;             /* Falg to reset the file pointer */ 
  
  OMX_BOOL stopFileRead;          /* Flag used to stop file reading */
}OMTB_INPORT_PARAMS;


/*!
 *******************************************************************************
 *  \struct OMTB_OUTPORT_PARAMS
 *  \brief  Structure for openmax component output port related param
 *******************************************************************************
 */

typedef struct OMTB_OUTPORT_PARAMS_T
{
  OMX_PARAM_PORTDEFINITIONTYPE* pOutPortDef;  /* output port def var */
  OMX_PTR opBufPipe;              /* output pipe */
  FILE *fout;                     /* O/P File Pointer */
  //void* outputDataReady;          /* FillBuffer Done Semaphore */
  unsigned int flagEos;           /* EOS indication flag */
  unsigned int bufferOutSize;     /* O/P buffer size */
  unsigned int outBufSzFlag;      /* Flag to enable/disable user i/p for o/p
                                     buffer size */
  void* outDataStrmThrdId;        /* O/P data streaming thread id */
  unsigned int flagUseOutBuffer;  /* 0: OMX_AllocateBuffer & 1: OMX_UseBuffer*/
  OmtbDataMode dataOutPutMode;    /* For selecting O/P Mode */
  unsigned int numOutBuf;         /* Number of o/p buffers */
  unsigned int outBufAlignment;   /* O/P buffer alignment */
  unsigned int outBufContiguous;  /* O/P buffer contiguous or not */
 
  OMX_PTR fileIpBufPipe;          /* file input pipe */
  OMX_PTR fileOpBufPipe;          /* file output pipe */    
  
  OMX_BOOL stopFileWrite;          /* Flag used to stop file reading */  
}OMTB_OUTPORT_PARAMS;


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


/*--------------------------------- end of file ------------------------------*/

