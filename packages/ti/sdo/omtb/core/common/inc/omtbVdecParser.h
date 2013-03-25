/*
 * omtbVdecParser.h
 *
 * This file contains the common interfaces for MPEG2 and H264 File Parsing
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

#ifndef __OMTB_VDEC_PARSER_H__
#define __OMTB_VDEC_PARSER_H__


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
#define AVCLOG(X,Y,Z) {} // { printf Z; printf ("\n"); }

/* In lieu of avc.h */
typedef unsigned int AVC_Err;


/* Common errorcodes */
#define AVC_SUCCESS                 (0)
#define AVC_ERR_NOT_SUPPORTED       (1)
#define AVC_ERR_MALLOC_FAILED       (2)
#define AVC_ERR_INTERNAL_ERROR      (3)
#define AVC_ERR_INVALID_ARGS        (4)
#define AVC_ERR_NO_OUTPUT_CHANNEL   (5)
#define AVC_ERR_WRONG_STATE         (6)
#define AVC_ERR_INSUFFICIENT_INPUT  (7)


#define CHECKPOINT


/******************************************************************************\
*      Data type definitions
\******************************************************************************/

/*!
*******************************************************************************
*  \struct AVChunk_Buf
*  \brief  Chunk Buffer
*******************************************************************************
*/

typedef struct
{
	unsigned char *ptr;
	int bufsize;
	int bufused;
} AVChunk_Buf;


/******************************************************************************\
*      Macros
\******************************************************************************/


/******************************************************************************\
*      Globals
\******************************************************************************/

/******************************************************************************\
*      External Object Definitions
\******************************************************************************/

#ifdef __cplusplus    /* matches __cplusplus construct above */
 }
#endif

#endif


/*--------------------------------- end of file -----------------------------*/
