
/*
 * omtbMpeg2VdecParser.c
 *
 * MPEG2 File Parser interface implementation
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

/******************************************************************************\
 *      Standard Includes
\******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

//#define OMTB_FILE_READ_IN_PARSER 1
//#define STANDALONE 1
/******************************************************************************\
 *      Customized Includes
\******************************************************************************/
/* OMX standard header files */
#include "OMX_Core.h"
#include "OMX_Component.h"
#include "OMX_Types.h"
#include "OMX_TI_Index.h"

#include "omtbDebug.h"
#include "timm_osal_interfaces.h"

#include "omtbCommon.h"
#include "omtbCmd.h"
#include "omtbClient.h"
#include "omtbVdecParser.h"
#include "omtbMpeg2VdecParser.h"

/******************************************************************************\
 *      Includes
\******************************************************************************/

/******************************************************************************\
*      OMTB_Mpeg2VidChunkingCtxInit Function Declaration
\******************************************************************************/
/**
*
*  @brief    MPEG2 Chunking Context initialization
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
void OMTB_Mpeg2VidChunkingCtxInit(Mpeg2Vid_ChunkingCtx *c)
{
	c->workingWord = MPEG2V_WORKING_WORD_INIT;
	c->state = MPEG2V_ST_LOOKING_FOR_SEQ_SC;
}


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
	AVChunk_Buf *opBufs, uint32_t numOutBufs, AVChunk_Buf *inBuf, void *attrs)
{
	int i = 0,j,frame_end,sc_found,tmp,bytes;
	uint32_t w;
	uint8_t *inp;

	inp = &inBuf->ptr[inBuf->bufused];
	bytes = inBuf->bufsize - inBuf->bufused;

BACK:
	if (c->state == MPEG2V_ST_INSIDE_PICT_SC)
	{
		tmp = i;
		frame_end = sc_found = 0;
		while (i < bytes)
		{
			c->workingWord <<= 8;
			c->workingWord |= inp[i++];
			if (c->workingWord == MPEG2V_PICTURE_START_CODE ||
					c->workingWord == MPEG2V_SEQ_START_CODE ||
					c->workingWord == MPEG2V_GOP_START_CODE)
			{
				frame_end = sc_found = 1;
				break;
			}
		}
		j = i - tmp;

		/* minus 4 to remove next header that is already copied */
		if (sc_found) j -= 4;

		if (j > (int32_t)(opBufs->bufsize - opBufs->bufused))
		{
		/* output buffer is full, end the frame right here
		 */
			AVCLOG(AVC_MOD_MAIN, AVC_LVL_TRACE_ALL, ("memcpy(%p,%d,%p,%d,%d)", 
				opBufs->ptr, opBufs->bufused, inp, tmp, opBufs->bufsize - opBufs->bufused));
			memcpy(&opBufs->ptr[opBufs->bufused],&inp[tmp],opBufs->bufsize - opBufs->bufused);
			opBufs->bufused = opBufs->bufsize;
			c->state = MPEG2V_ST_LOOKING_FOR_PICT_SC;
			frame_end = 1;
		}
		else if (j > 0)
		{
			AVCLOG(AVC_MOD_MAIN, AVC_LVL_TRACE_ALL, ("memcpy(%p,%d,%p,%d,%d)", 
				opBufs->ptr, opBufs->bufused, inp, tmp, j));
			memcpy(&opBufs->ptr[opBufs->bufused],&inp[tmp],j);
			opBufs->bufused += j;
		}
		else
		{
			opBufs->bufused += j;
		}
		
		if (frame_end)
		{
			if (sc_found) c->state = MPEG2V_ST_HOLDING_SC;
			inBuf->bufused += i;
			return AVC_SUCCESS;
		}
	}
	if (c->state == MPEG2V_ST_LOOKING_FOR_PICT_SC)
	{
		tmp = i;
		sc_found = 0;
		while (i < bytes)
		{
			c->workingWord <<= 8;
			c->workingWord |= inp[i++];
			if (c->workingWord == MPEG2V_PICTURE_START_CODE)
			{
				sc_found = 1;
				break;
			}
		}
		j = i - tmp;

		if (j > (opBufs->bufsize - opBufs->bufused))
		{
		/* output buffer is full, discard this data, go back to looking for seq start code
		 */
			opBufs->bufused = 0;
			c->state = MPEG2V_ST_LOOKING_FOR_SEQ_SC;
		}
		else if (j > 0)
		{
			AVCLOG(AVC_MOD_MAIN, AVC_LVL_TRACE_ALL, ("memcpy(%p,%d,%p,%d,%d)", 
				opBufs->ptr, opBufs->bufused, inp, tmp, j));
			memcpy(&opBufs->ptr[opBufs->bufused],&inp[tmp],j);
			opBufs->bufused += j;
		}
		
		if (sc_found)
		{
			/* Set the attribute at rioWptr */
			c->state = MPEG2V_ST_INSIDE_PICT_SC;
		}
	}
	if (c->state == MPEG2V_ST_STREAM_ERR)
	{
		while (i < bytes)
		{
			c->workingWord <<= 8;
			c->workingWord |= inp[i++];

			if (c->workingWord == MPEG2V_PICTURE_START_CODE ||
					c->workingWord == MPEG2V_SEQ_START_CODE ||
					c->workingWord == MPEG2V_GOP_START_CODE)
			{
				c->state = MPEG2V_ST_HOLDING_SC;
				break;
			}
		}
	}
	if (c->state == MPEG2V_ST_LOOKING_FOR_SEQ_SC)
	{
		while (i < bytes)
		{
			c->workingWord <<= 8;
			c->workingWord |= inp[i++];

			if (c->workingWord == MPEG2V_SEQ_START_CODE)
			{
				c->state = MPEG2V_ST_HOLDING_SC;
				break;
			}
		}
	}
	if (c->state == MPEG2V_ST_HOLDING_SC)
	{
		w = c->workingWord;
		opBufs->bufused = 0;
		if (opBufs->bufsize < 4)
		{
			/* Means output buffer does not have space for 4 bytes, bad error
			 */
			AVCLOG(AVC_MOD_MAIN, AVC_LVL_CRITICAL_ERROR, ("Bad error"));
		}
		/* Copy these 4 bytes into output */
		for (j=0; j<4;j++,w<<=8) 
		{
			opBufs->ptr[opBufs->bufused+j] = ((w >> 24) & 0xFF);
		}
		/* Copying frame start code done, now proceed to next state
		 */
		opBufs->bufused += j;
		c->state = (c->workingWord == MPEG2V_PICTURE_START_CODE)?
			MPEG2V_ST_INSIDE_PICT_SC:MPEG2V_ST_LOOKING_FOR_PICT_SC;

		c->workingWord = MPEG2V_WORKING_WORD_INIT;
	}

	if (i < bytes) goto BACK;

	inBuf->bufused += i;
	return AVC_ERR_INSUFFICIENT_INPUT;
}

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
*  @return   uint32_t - Frame Size
*
*/
uint32_t OMTB_Mpeg2VidGetNextFrameSize(Mpeg2_ParsingCtx *pc, void *fileIpBufPipe, void *fileOpBufPipe)
{
	FILE *fp = pc->fp;
	uint8_t *readBuf = pc->readBuf;
	uint8_t *chunkBuf = pc->chunkBuf;
	Mpeg2_ParsingCtx *ctx = &pc->ctx;
	AVChunk_Buf *inBuf = &pc->inBuf;
	AVChunk_Buf *outBuf = &pc->outBuf;
	
#ifndef OMTB_FILE_READ_IN_PARSER
    static OMTB_CLIENT_FILEIO_PARAMS pipeMsg;
	unsigned int actualSize = 0;
#endif	

	while ((!feof(fp)) || ((((pc->firstParse==0)&&(pc->bytes!=0)) && (pc->bytes <= MPEG2PARSER_READSIZE) && (pc->tmp <= pc->bytes))))
	{
        if(pc->firstParse == 1)
		{
#ifdef OMTB_FILE_READ_IN_PARSER			
			pc->bytes = fread(readBuf, 1, MPEG2PARSER_READSIZE, fp);
			//printf ("bytes read %d\n", pc->bytes);
#else
			/* Read empty buffer pointer from the pipe of file io */
			TIMM_OSAL_ReadFromPipe (fileOpBufPipe,
									&pipeMsg,
									sizeof(OMTB_CLIENT_FILEIO_PARAMS),
									(void*) &actualSize,
									TIMM_OSAL_SUSPEND );       
			
			readBuf = pipeMsg.pBuff;
            pc->bytes = pipeMsg.buffLen;
			
			/* No data to process */
			if(0 >= pc->bytes)
			 return 0;
#endif			
			inBuf->ptr = readBuf;
			pc->tmp = 0;
			pc->firstParse = 0;
		}
		else
		{
			if(pc->bytes <= pc->tmp)
			{
#ifdef OMTB_FILE_READ_IN_PARSER	
				pc->bytes = fread(readBuf, 1, MPEG2PARSER_READSIZE, fp);
				//printf ("bytes read %d\n", pc->bytes);
#else
	          /*Write the buffer pointer to pipe, will be used by the file read thread */
              TIMM_OSAL_WriteToPipe (fileIpBufPipe,
                                     &pipeMsg,
                                     sizeof(OMTB_CLIENT_FILEIO_PARAMS),
                                     TIMM_OSAL_SUSPEND );			
		  
			  /* Read empty buffer pointer from the pipe of file io */
			  TIMM_OSAL_ReadFromPipe (fileOpBufPipe,
							  		  &pipeMsg,
									  sizeof(OMTB_CLIENT_FILEIO_PARAMS),
									  (void*) &actualSize,
									  TIMM_OSAL_SUSPEND );       
			  
			  readBuf = pipeMsg.pBuff;              
			  pc->bytes  = pipeMsg.buffLen;		
			  
			  /* No data to process */
			  if(0 >= pc->bytes)
			   return 0;			  
#endif
				inBuf->ptr = readBuf;
				pc->tmp = 0;
			}
		}	


		while (pc->bytes > pc->tmp)
		{
			inBuf->bufsize = ((pc->bytes-pc->tmp)>184)?184:(pc->bytes-pc->tmp);
			inBuf->bufused = 0;

			while (inBuf->bufsize != inBuf->bufused)
			{
				if (AVC_SUCCESS == OMTB_Mpeg2VidDoChunking(ctx, outBuf, 1, inBuf, NULL))
				{
					pc->frameNo = pc->chunkCnt++;
					pc->frameSize = outBuf->bufused;
					pc->tmp += inBuf->bufused;
					inBuf->ptr += inBuf->bufused;
					printf("frameSize = %d\n", pc->frameSize);
					return pc->frameSize;

				}
			}
			pc->tmp += inBuf->bufused;
			inBuf->ptr += inBuf->bufused;
		}
	
   }
	return -1;	
}

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
void OMTB_Mpeg2VidResetParser(void *parserPtr) 
{
  Mpeg2_ParsingCtx *pc = (Mpeg2_ParsingCtx *)parserPtr;
  OMTB_Mpeg2VidChunkingCtxInit(&(pc->ctx));
  fseek(pc->fp, 0, SEEK_SET);
  pc->frameNo = 0;
  pc->frameSize = 0;
  pc->bytes = 0;
  pc->tmp = 0;
  pc->firstParse = 1;
  pc->chunkCnt = 0;
  pc->outBuf.ptr = NULL;
  pc->outBuf.bufsize = 0;
  pc->outBuf.bufused = 0;
}

#ifdef STANDALONE

void usage(char *progName)
{
	printf("Usage: %s <elementary stream filename>\n",progName);
	exit(0);
}
int main(int argc, char *argv[])
{
    Mpeg2_ParsingCtx pc;
	unsigned int frameSize = 0;

	if (argc < 2) usage(argv[0]);

	pc.readBuf = (uint8_t*)malloc(MPEG2PARSER_READSIZE);
	if (!pc.readBuf) exit(1);

	pc.chunkBuf = (uint8_t*)malloc(CHUNKSIZE);
	if (!pc.chunkBuf) exit(1);

    pc.fp = fopen(argv[1],"rb");
	if (!pc.fp)
  	  exit(1);

	OMTB_Mpeg2VidChunkingCtxInit(&pc.ctx);
	pc.frameNo = 0;
	pc.frameSize = 0;
	pc.bytes = 0;
	pc.tmp = 0;
	pc.firstParse = 1;
	pc.chunkCnt = 0;
	
	pc.outBuf.ptr = pc.chunkBuf;
	pc.outBuf.bufsize = CHUNKSIZE;
	pc.outBuf.bufused = 0;

	while (-1 != (frameSize = OMTB_Mpeg2GetNextFrameSize(&pc)))
	{
		printf("Frame#: %d, Frame Size: %d\n", pc.frameNo, frameSize);

    }
	
	free(pc.chunkBuf);
	free(pc.readBuf);
	fclose(pc.fp);
}
#endif