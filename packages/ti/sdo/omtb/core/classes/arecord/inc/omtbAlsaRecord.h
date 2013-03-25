/*
 * omtbAlsaRecord.h
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

#ifndef __OMTB_ALSARECORD_H__
#define __OMTB_ALSARECORD_H__


/******************************************************************************\
 *      Includes
\******************************************************************************/
#include <alsa/asoundlib.h>

#include "OMX_TI_Common.h"
#include "omx_ctrl.h"

#include "omtbPortParam.h"
#include "omtbTypes.h"


/******************************************************************************/

#ifdef __cplusplus    /* required for headers that might */
 extern "C" {         /* be compiled by a C++ compiler */
#endif


/******************************************************************************\
 *      Defines
\******************************************************************************/

#define OMTB_ALSARECORD_COMP_REF_STR     ("arecord")    /* comp refernce string */

#define OMTB_ALSARECORD_REMOTE_IP        ("127.0.0.1")  /* Local host / Remote IP */ 

#define OMTB_ALSARECORD_GROUP_PRIORITY   (12)           /* Task group priority */
#define OMTB_ALSARECORD_TSK_STACK_SIZE   (50 * 1024)    /* Task stack size */
/*
 *  OMX_AUDIO_PERIODIC_TASK_SLEEP_DURN - The Data component emulates a recording
 *  scenario wherein the audio field data is recorded/captured at every 20 ms.
*/
#define OMTB_AUDIO_PERIODIC_TASK_SLEEP_DURATION (32/4) 
#define OMTB_AUDIO_NUM_CHANNELS	(1)                               /* Number of audio channels */
#define OMTB_AUDIO_SAMPLING_RATE (16000)                           /* Audio Sampling Rate */
#define OMTB_AUDIO_NUM_SAMPLES	(480)                             /* Number of Samples per record/playback */
#define OMTB_RAW_AUDIO_BUFFER_SIZE (OMTB_AUDIO_NUM_SAMPLES * OMTB_AUDIO_NUM_CHANNELS * 2)
                                                                  /* Raw Audio Buffer size */
#define OMTB_ENCODED_AUDIO_BUFFER_SIZE (OMTB_RAW_AUDIO_BUFFER_SIZE/2)
                                                                  /* Encoded Audio Buffer size */
																  
#define OMTB_AUDIO_PORT (1236)									  /* Audio Port */							  

#define ALSA_PCM_NEW_HW_PARAMS_API

#define OMTB_ALSARECORD_MAX_NUM_OUT_BUFS (6)     
    
/******************************************************************************\
 *      Data type definitions
\******************************************************************************/

/* Application's private structure for OMX ALSARECORD Component*/

typedef struct OMTB_ALSARECORD_PRIVATE_T
{

  OMTB_APP_PRIVATE omtbPvt;                   /* OMTB common pvt data */
  snd_pcm_t *hAudioHandle;                    /* Audio Handle */  
  unsigned short *inputBuf;                   /* Input Buffer */ 
  short *encodedBuf[OMTB_ALSARECORD_MAX_NUM_OUT_BUFS];
                                             /* Output Buffer */
  void          *opPipe;					 /* pipe to hold the output buffer pointers */						 
}OMTB_ALSARECORD_PRIVATE;


/* Configuration structure for OMX ALSARECORD Component */

typedef struct OMTB_ALSARECORD_CONFIG_PARAMS_T
{
  char remoteIP[OMX_MAX_STRINGNAME_SIZE];
                                    /* Remote IP */
  unsigned int nChannels;           /* No of channels */
  unsigned int nSamplingRate;       /* Sampling Rate */
  unsigned int nNumSamples;		    /* No of samples */						 	
  int nAudioPort;                   /* Audio port */
}OMTB_ALSARECORD_CONFIG_PARAMS;

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
 *      ALSARECORD_FuncTsk Thread Prototype
\******************************************************************************/
/**
 *
 *  @brief    This is a H264 thread which invokes during func command
 *
 *  @param in:
 *            void * - Thread args count
 *
 *            void *threadsArg - Pointer to thread arg structure
 *
 *  @return   None
 *
 */

void ALSARECORD_FuncTsk(void *argc, void *threadsArg);


/******************************************************************************\
 *      ALSARECORD_GetHandle Function Definition
\******************************************************************************/
/**
 *
 *  @brief    Get the handle for ALSARECORD component
 *
 *  @param in:
 *            classPtr: Pointer to OMTB_COMP_HANDLE structure
 *
 *            instance: Instance number of the component
 *
 *  @param Out:
 *            None
 *
 *  @return   OMX_ERRORTYPE - OMX standard error code
 *
 */

//OMX_ERRORTYPE ALSARECORD_GetHandle(OMTB_COMP_HANDLE *classPtr, unsigned int instance);

/******************************************************************************\
 *      ALSARECORD_FreeHandle Function Definition
\******************************************************************************/
/**
 *
 *  @brief    Free the memory allocated for the component
 *
 *  @param in:
 *            alsaRecordClient: Pointer to OMTB_ALSARECORD_PRIVATE struct
 *
 *  @return   None
 *
 */

void ALSARECORD_FreeHandle(OMTB_ALSARECORD_PRIVATE *alsaRecordClient);

#ifdef __cplusplus    /* matches __cplusplus construct above */
 }
#endif

#endif


/*--------------------------------- end of file -----------------------------*/
