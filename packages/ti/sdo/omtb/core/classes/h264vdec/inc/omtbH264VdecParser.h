/*
 * omtbH264VdecParser.h
 *
 * This file contains the interfaces for H.264 File Parsing
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

#ifndef __OMTB_H264_VDEC_PARSER_H__
#define __OMTB_H264_VDEC_PARSER_H__


/******************************************************************************\
 *      Includes
\******************************************************************************/


/******************************************************************************/

#ifdef __cplusplus    /* required for headers that might */
 extern "C" {         /* be compiled by a C++ compiler */
#endif


/******************************************************************************\
 *      Defines
\******************************************************************************/

/* Various start codes for H264 */
/* Last byte only */
#define H264_NAL_ACCESS_UNIT_CODEDSLICE_CODE_FOR_NONIDR		0x01
#define H264_NAL_ACCESS_UNIT_CODEDSLICE_CODE_FOR_IDR 		0x05
#define H264_PPS_START_CODE                                 0x08
#define H264_SPS_START_CODE                                 0x07
#define H264_WORKING_WORD_INIT  							0xFFFFFFFF

#define H264PARSER_READSIZE 	(1*256*1024)
#define H264PARSER_CHUNKSIZE    (1*1024*1024)


/******************************************************************************\
*      Data type definitions
\******************************************************************************/

/*!
*******************************************************************************
*  \enum
*  \brief  Parser State
*******************************************************************************
*/
enum {
	H264_ST_LOOKING_FOR_SPS, /**< Initial state at start, look for SPS */
	H264_ST_LOOKING_FOR_ZERO_SLICE,/**< Looking for slice header with zero MB num */
	H264_ST_INSIDE_PICTURE,     /**< Inside a picture, looking for next picure start */
	H264_ST_STREAM_ERR,         /**< When some discontinuity was detected in the stream */
	H264_ST_HOLDING_SC          /**< Intermediate state, when a new frame is detected */
};

/*!
*******************************************************************************
*  \struct H.264_ChunkingCtx
*  \brief  H.264 Chunking Context
*******************************************************************************
*/
/* H264 video chunking */
typedef struct
{
	unsigned int workingWord;
	unsigned char fifthByte;
	unsigned char state;
} H264_ChunkingCtx;

typedef struct
{
	FILE *fp;
	unsigned int frameNo;
	unsigned int frameSize;
	unsigned char *readBuf;
	unsigned char *chunkBuf;
	H264_ChunkingCtx ctx;
	AVChunk_Buf inBuf;
	AVChunk_Buf outBuf;
	unsigned int bytes;
	unsigned int tmp;
	unsigned char firstParse;
	unsigned int chunkCnt;
} H264_ParsingCtx;

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
*      OMTB_H264ChunkingCtxInit Function Declaration
\******************************************************************************/
/**
*
*  @brief    H.264 Chunking Context initialization
*
*  @param in:
*            c: Pointer to H264_ChunkingCtx structure
*
*  @param Out:
*            None
*
*  @return   void
*
*/

void OMTB_H264ChunkingCtxInit(H264_ChunkingCtx *c);

/******************************************************************************\
*      OMTB_H264DoChunking Function Declaration
\******************************************************************************/
/**
*
*  @brief    Does H.264 Frame Chunking.
*
*  @param in:
*            c: Pointer to H264_ChunkingCtx structure
*            opBufs: Pointer to AVChunk_Buf Structure
*            numOutBufs: Number of output buffers
*            inBuf: Pointer to AVChunk_Buf Structure
*            attrs: Additional attributes
*
*  @param Out:
*            None
*
*  @return   AVC_Err - AVC Error Code
*
*/

AVC_Err OMTB_H264DoChunking(H264_ChunkingCtx *c,
	AVChunk_Buf *opBufs, unsigned int numOutBufs, AVChunk_Buf *inBuf, void *attrs);

/******************************************************************************\
*      OMTB_H264GetNextFrameSize Function Declaration
\******************************************************************************/
/**
*
*  @brief    Gets the size of the next frame.
*
*  @param in:
*            pc: Pointer to H264_ParsingCtx structure
*
*  @param Out:
*            None
*
*  @return   uint32_t - Frame Size
*
*/
unsigned int OMTB_H264GetNextFrameSize(H264_ParsingCtx *pc, void *fileIpBufPipe, void *fileOpBufPipe);


/******************************************************************************\
*      OMTB_H264Reset_Parser Function Declaration
\******************************************************************************/
/**
*
*  @brief    Reset the file parser.
*
*  @param in:
*            pc: Pointer to H264_ParsingCtx structure
*
*  @param Out:
*            None
*
*  @return   None
*
*/
void OMTB_H264Reset_Parser(void *parserPtr); 

#ifdef __cplusplus    /* matches __cplusplus construct above */
 }
#endif

#endif


/*--------------------------------- end of file -----------------------------*/
