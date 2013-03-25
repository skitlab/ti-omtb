
/*
 * omtbH264VdecParser.c
 *
 * H.264 File Parser interface implementation
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
//#include <unistd.h>
#include <string.h>
#include <stdint.h>
//#include <sys/time.h>

//#define OMTB_FILE_READ_IN_PARSER
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
#include "omtbH264VdecParser.h"


/******************************************************************************\
 *      Includes
\******************************************************************************/



void OMTB_H264ChunkingCtxInit(H264_ChunkingCtx *c)
{
	c->workingWord = H264_WORKING_WORD_INIT;
	c->fifthByte = 0xFF;
	c->state = H264_ST_LOOKING_FOR_SPS;
}

AVC_Err OMTB_H264DoChunking(H264_ChunkingCtx *c,
	AVChunk_Buf *opBufs, uint32_t numOutBufs, AVChunk_Buf *inBuf, void *attrs)
{
	int i = 0,j,frame_end,sc_found,tmp,bytes;
	uint32_t w, z;
	uint8_t *inp;

	inp = &inBuf->ptr[inBuf->bufused];
	bytes = inBuf->bufsize - inBuf->bufused;

BACK:
	if (c->state == H264_ST_INSIDE_PICTURE)
	{
		tmp = i;
		sc_found = frame_end = 0;
		while (i < bytes)
		{
			z = c->workingWord << 8;
			w = c->fifthByte;
			c->workingWord = z | w;
			c->fifthByte = inp[i++];

			if (z == 0x100)
			{
				// printf("%d: %08x @ %d\n",chunkCnt, c->workingWord, opBufs->bufused+i-tmp-6);

				w &= 0x1f;
				if (w == H264_NAL_ACCESS_UNIT_CODEDSLICE_CODE_FOR_NONIDR ||
						w == H264_NAL_ACCESS_UNIT_CODEDSLICE_CODE_FOR_IDR)
				{
					/* check for MB number in slice header */
					if (c->fifthByte & 0x80)
					{
						sc_found = frame_end = 1;
						break;
					}
				}
				if (w == H264_PPS_START_CODE ||
					w == H264_SPS_START_CODE)
				{
						sc_found = frame_end = 1;
						break;
				}
			}
		}
		j = i - tmp;

		/* minus 5 to remove next header that is already copied */
		if (frame_end) j -= 5;

		if (j > (int32_t)(opBufs->bufsize - opBufs->bufused))
		{
		/* output buffer is full, end the frame right here
		 */
			AVCLOG(AVC_MOD_MAIN, AVC_LVL_TRACE_ALL, ("memcpy(%p,%d,%p,%d,%d)",
				opBufs->ptr, opBufs->bufused, inp, tmp, opBufs->bufsize - opBufs->bufused));
			memcpy(&opBufs->ptr[opBufs->bufused],&inp[tmp],opBufs->bufsize - opBufs->bufused);
			opBufs->bufused = opBufs->bufsize;
			c->state = H264_ST_LOOKING_FOR_ZERO_SLICE;
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
			if (sc_found)
			{
				c->state = H264_ST_HOLDING_SC;
				//printf("FrameSize = %d\n", i);
			}
			inBuf->bufused += i;
			return AVC_SUCCESS;
		}
	}
	if (c->state == H264_ST_LOOKING_FOR_ZERO_SLICE)
	{
		tmp = i;
		sc_found = 0;
		while (i < bytes)
		{
			z = c->workingWord << 8;
			w = c->fifthByte;
			c->workingWord = z | w;
			c->fifthByte = inp[i++];

			if (z == 0x100)
			{
				// printf("%d: %08x @ %d\n",chunkCnt, c->workingWord, opBufs->bufused+i-tmp-6);
				w &= 0x1f;
				if (w == H264_NAL_ACCESS_UNIT_CODEDSLICE_CODE_FOR_NONIDR ||
						w == H264_NAL_ACCESS_UNIT_CODEDSLICE_CODE_FOR_IDR)
				{
					/* check for MB number in slice header */
					if (c->fifthByte & 0x80)
					{
						sc_found = 1;
						break;
					}
				}
			}
		}
		j = i - tmp;

		if (j > (opBufs->bufsize - opBufs->bufused))
		{
		/* output buffer is full, discard this data, go back to looking for seq start code
		 */
			opBufs->bufused = 0;
			c->state = H264_ST_LOOKING_FOR_SPS;
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
			c->state = H264_ST_INSIDE_PICTURE;
		}
	}
	if (c->state == H264_ST_STREAM_ERR)
	{
		while (i < bytes)
		{
			z = c->workingWord << 8;
			w = c->fifthByte;
			c->workingWord = z | w;
			c->fifthByte = inp[i++];

			if (z == 0x100)
			{
				w &= 0x1f;
				if (w == H264_NAL_ACCESS_UNIT_CODEDSLICE_CODE_FOR_NONIDR ||
						w == H264_NAL_ACCESS_UNIT_CODEDSLICE_CODE_FOR_IDR)
				{
					/* chueck for MB number in slice header */
					if (c->fifthByte & 0x80)
					{
						c->state = H264_ST_HOLDING_SC;
						break;
					}
				}
				if (w == H264_PPS_START_CODE ||
					w == H264_SPS_START_CODE)
				{
						c->state = H264_ST_HOLDING_SC;
						break;
				}
			}
		}
	}
	if (c->state == H264_ST_LOOKING_FOR_SPS)
	{
		while (i < bytes)
		{
			z = c->workingWord << 8;
			w = c->fifthByte;
			c->workingWord = z | w;
			c->fifthByte = inp[i++];

			if (z == 0x100)
			{
				// printf("%d: %08x @ %d\n",chunkCnt, c->workingWord, inBuf->bufused+i-6);

				w &= 0x1f;
				if (w == H264_SPS_START_CODE)
				{
					c->state = H264_ST_HOLDING_SC;
					break;
				}
			}
		}
	}
	if (c->state == H264_ST_HOLDING_SC)
	{
		w = c->workingWord;
		opBufs->bufused = 0;
		if (opBufs->bufsize < 5)
		{
			/* Means output buffer does not have space for 4 bytes, bad error
			 */
			AVCLOG(AVC_MOD_MAIN, AVC_LVL_CRITICAL_ERROR, ("Bad error"));
		}
		/* Copy these 5 bytes into output */
		for (j=0; j<4;j++,w<<=8)
		{
			opBufs->ptr[opBufs->bufused+j] = ((w >> 24) & 0xFF);
		}
		opBufs->ptr[opBufs->bufused+j] = c->fifthByte;
		opBufs->bufused += 5;
		/* Copying frame start code done, now proceed to next state
		 */
		w = c->workingWord & 0x1f;
		if (w == H264_PPS_START_CODE ||
			w == H264_SPS_START_CODE)
		{
			c->state = H264_ST_LOOKING_FOR_ZERO_SLICE;
		}
		else
		{
			c->state = H264_ST_INSIDE_PICTURE;
		}

		c->workingWord = H264_WORKING_WORD_INIT;
		c->fifthByte = 0xFF;
	}

	if (i < bytes) goto BACK;

	inBuf->bufused += i;
	return AVC_ERR_INSUFFICIENT_INPUT;
}

uint32_t OMTB_H264GetNextFrameSize(H264_ParsingCtx *pc, void *fileIpBufPipe, void *fileOpBufPipe)
{
	FILE *fp = pc->fp;
	uint8_t *readBuf = pc->readBuf;
	uint8_t *chunkBuf = pc->chunkBuf;
	H264_ChunkingCtx *ctx = &pc->ctx;
	AVChunk_Buf *inBuf = &pc->inBuf;
	AVChunk_Buf *outBuf = &pc->outBuf;

	uint8_t termCond = 1;
	
#ifndef OMTB_FILE_READ_IN_PARSER
    static OMTB_CLIENT_FILEIO_PARAMS pipeMsg;
	unsigned int actualSize = 0;
#endif	

	if(pc->firstParse == 1)
		termCond = 0;


	while ((!feof(fp)) || ((((pc->firstParse==0)&&(pc->bytes!=0)) && (pc->bytes <= H264PARSER_READSIZE) && (pc->tmp <= pc->bytes))))
	{
//		printf("Inside while1(while(!feof(fp))): bytes=%d, tmp=%d\n", pc->bytes, pc->tmp);
		if(pc->firstParse == 1)
		{
#ifdef OMTB_FILE_READ_IN_PARSER			
			pc->bytes = fread(readBuf, 1, H264PARSER_READSIZE, fp);
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
				pc->bytes = fread(readBuf, 1, H264PARSER_READSIZE, fp);
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

		//printf("pc->bytes = %d, pc->tmp = %d\n", pc->bytes, pc->tmp);
		while (pc->bytes > pc->tmp)
		{
//			printf("Inside while2(while(bytes>tmp)): bytes=%d, tmp=%d\n", pc->bytes, pc->tmp);
			inBuf->bufsize = ((pc->bytes - pc->tmp)>184)?184:(pc->bytes - pc->tmp);
			inBuf->bufused = 0;

			while (inBuf->bufsize != inBuf->bufused)
			{
//				printf("Inside while3(while(inBuf.bufsize != inBuf.bufused)): bytes=%d, tmp=%d\n", pc->bytes, pc->tmp);
				if (AVC_SUCCESS == OMTB_H264DoChunking(ctx, outBuf, 1, inBuf, NULL))
				{
					//printf("Frame#: %d, FrameSize: %d\n", pc->chunkCnt++, outBuf->bufused);
					pc->frameNo = pc->chunkCnt++;
					pc->frameSize = outBuf->bufused;
					pc->tmp += inBuf->bufused;
					inBuf->ptr += inBuf->bufused;
					//printf("inBuf->bufsize = %d, inBuf->bufused = %d\n", inBuf->bufsize, inBuf->bufused);
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
*      OMTB_H264Reset_Parser Function Declaration
\******************************************************************************/
/**
*
*  @brief    Reset the H264 file parser.
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
void OMTB_H264ResetParser(void *parserPtr) 
{
  H264_ParsingCtx *pc = (H264_ParsingCtx *)parserPtr;
  OMTB_H264ChunkingCtxInit(&(pc->ctx));
  fseek(pc->fp, 0, SEEK_SET);
  pc->frameNo = 0;
  pc->frameSize = 0;
  pc->bytes = 0;
  pc->tmp = 0;
  pc->firstParse = 1;
  pc->chunkCnt = 1;
  pc->outBuf.ptr = NULL;
  pc->outBuf.bufsize = 0;
  pc->outBuf.bufused = 0;
}

#ifdef STANDALONE

void usage(char *progName)
{
	printf("Usage: %s <elementary stream filename>\n",progName);
}


int main(int argc, char *argv[])
{
	H264_ParsingCtx pc;
	int frameSize = 0;
	int cnt=0;
	int totalBufSize=0;

	//This init should be done from the callee
	if (argc < 2) usage(argv[0]);

	pc.readBuf = (uint8_t*)malloc(H264PARSER_READSIZE);
	if (!pc.readBuf) exit(1);
	//printf("pc.readBuf = %X\n", pc.readBuf);

	pc.chunkBuf = (uint8_t*)malloc(CHUNKSIZE);
	if (!pc.chunkBuf) exit(1);

	OMTB_H264ChunkingCtxInit(&pc.ctx);
	pc.frameNo = 0;
	pc.frameSize = 0;
	pc.bytes = 0;
	pc.tmp = 0;
	pc.firstParse = 1;
	pc.chunkCnt = 1;

	pc.outBuf.ptr = pc.chunkBuf;
	pc.outBuf.bufsize = CHUNKSIZE;
	pc.outBuf.bufused = 0;

	pc.fp = fopen(argv[1],"rb");
	//printf ("FILE* pc.fp=%X\n", pc.fp);
	if (!pc.fp) exit(1);
	while (-1 != (frameSize = OMTB_H264GetNextFrameSize(&pc)))
	{
		printf("Frame#: %d, Frame Size: %d\n", pc.frameNo, frameSize);
		//printf("%d\n", frameSize);
		cnt++;
		totalBufSize += frameSize;
		//if(totalBufSize > 4194303)
		//if(totalBufSize > 4100000)
		//	break;
		//printf("pc.bytes = %d, pc.tmp = %d\n", pc.bytes, pc.tmp);
		//if(cnt > 75)
		//	break;
	}

	/*Free up the pointers*/
	free(pc.chunkBuf);
	free(pc.readBuf);
	fclose(pc.fp);

	return 0;
}
#endif