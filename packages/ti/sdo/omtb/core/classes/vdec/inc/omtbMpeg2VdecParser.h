/*
 * omtbMpeg2VdecParser.h
 *
 * This file contains the interfaces for MPEG2 File Parsing
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

#ifndef __OMTB_MPEG2_VDEC_PARSER_H__
#define __OMTB_MPEG2_VDEC_PARSER_H__


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
/* Various start codes for MPEG-2/1 */
#define MPEG2V_PICTURE_START_CODE 0x100
#define MPEG2V_SEQ_START_CODE     0x1B3
#define MPEG2V_GOP_START_CODE     0x1B8

#define MPEG2V_WORKING_WORD_INIT  0xFFFFFFFF

#define MPEG2PARSER_READSIZE 	(1*256*1024)
#define MPEG2PARSER_CHUNKSIZE    (1*1024*1024)

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
	MPEG2V_ST_LOOKING_FOR_SEQ_SC, /**< Initial state at start, look for seq-start code */
	MPEG2V_ST_LOOKING_FOR_PICT_SC,/**< Looking for picture-start-code to start a frame */
	MPEG2V_ST_INSIDE_PICT_SC,     /**< Pict-SC found, now look for other SCs to end a frame */
	MPEG2V_ST_STREAM_ERR,         /**< When some discontinuity was detected in the stream */
	MPEG2V_ST_HOLDING_SC          /**< Intermediate state, when a new frame is detected */
};

/*!
*******************************************************************************
*  \struct Mpeg2Vid_ChunkingCtx
*  \brief  MPEG2 Chunking Context
*******************************************************************************
*/
/* MPEG2 video chunking */
typedef struct
{
	unsigned int workingWord;
	unsigned char state;
} Mpeg2Vid_ChunkingCtx;

typedef struct
{
	FILE *fp;
	unsigned int frameNo;
	unsigned int frameSize;
	unsigned char *readBuf;
	unsigned char *chunkBuf;
	Mpeg2Vid_ChunkingCtx ctx;
	AVChunk_Buf inBuf;
	AVChunk_Buf outBuf;
	unsigned int bytes;
	unsigned int tmp;
	unsigned char firstParse;
	unsigned int chunkCnt;
} Mpeg2_ParsingCtx;

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
*      OMTB_Mpeg2VidChunkingCtxInit Function Declaration
\******************************************************************************/
/**
*
*  @brief    MPEG2 Chunking Context initialization
*
*  @param in:
*            c: Pointer to Mpeg2Vid_ChunkingCtx structure
*
*  @param Out:
*            None
*
*  @return   void
*
*/

void OMTB_Mpeg2VidChunkingCtxInit(Mpeg2Vid_ChunkingCtx *c);

/******************************************************************************\
*      OMTB_Mpeg2VidDoChunking Function Declaration
\******************************************************************************/
/**
*
*  @brief    Does MPEG2 Frame Chunking.
*
*  @param in:
*            c: Pointer to Mpeg2Vid_ChunkingCtx structure
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

AVC_Err OMTB_Mpeg2VidDoChunking(Mpeg2Vid_ChunkingCtx *c, 
	AVChunk_Buf *opBufs, unsigned int numOutBufs, AVChunk_Buf *inBuf, void *attrs);

/******************************************************************************\
*      OMTB_Mpeg2GetNextFrameSize Function Declaration
\******************************************************************************/
/**
*
*  @brief    Gets the size of the next frame.
*
*  @param in:
*            pc: Pointer to Mpeg2_ParsingCtx structure
*
*  @param Out:
*            None
*
*  @return   unsigned int - Frame Size
*
*/
unsigned int OMTB_Mpeg2VidGetNextFrameSize(Mpeg2_ParsingCtx *pc, void *fileIpBufPipe, void *fileOpBufPipe);

/******************************************************************************\
*      OMTB_Mpeg2VidResetParser Function Declaration
\******************************************************************************/
/**
*
*  @brief    Reset the MPEG2 file parser.
*
*  @param in:
*            pc: Pointer to Mpeg2_ParsingCtx structure
*
*  @param Out:
*            None
*
*  @return   None
*
*/
void OMTB_Mpeg2VidResetParser(void *parserPtr);

#ifdef __cplusplus    /* matches __cplusplus construct above */
 }
#endif

#endif


/*--------------------------------- end of file -----------------------------*/
