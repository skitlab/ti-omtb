/*
 * omtbAlsaRecord.c
 *
 * Component specific IL Client Implementation.
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
#include <string.h>
#include <alsa/asoundlib.h>
#include <linux/soundcard.h>

/* OMX standard header files */
#include "OMX_Core.h"
#include "OMX_Component.h"
#include "OMX_Types.h"
#include "OMX_TI_Common.h"
#include "OMX_TI_Index.h"
#include "omx_ctrl.h"


/******************************************************************************\
 *      Customized Includes
\******************************************************************************/

#include "omtbDebug.h"
#include "timm_osal_interfaces.h"

#include "omtbCommon.h"
#include "omtbCmd.h"


/******************************************************************************\
 *      Local Defines
\******************************************************************************/
//#define OMTB_AUDIO_RTP
#define OMTB_USE_PIPE
/******************************************************************************\
 *      Data type definitions
\******************************************************************************/



/******************************************************************************\
 *      Extern Object Definitions
\******************************************************************************/

// Component class structure which holds component instance handle,
// application private data etc
extern OMTB_COMP_HANDLE omtbClass[OMTB_MAX_CLASS];

/* Pointer to OMTB configuration template */
extern OMTB_TEMPLATE_INFO *omtbCfgTemplate[OMTB_MAX_INS];


/******************************************************************************\
 *      Globals
\******************************************************************************/

/* Pointer to ALSARECORD config params */
OMTB_ALSARECORD_CONFIG_PARAMS *alsaRecordConfig = NULL;


/******************************************************************************\
 *      Static Globals
\******************************************************************************/


/******************************************************************************\
 *      Public Function Prototypes
\******************************************************************************/

/******************************************************************************\
 *      Private Function Prototypes
\******************************************************************************/


/******************************************************************************\
 *      Function Definitions
\******************************************************************************/

/******************************************************************************\
 *      ALSARECORD_G711ulawEncode Definition
\******************************************************************************/
/**
 *
 *  @brief    This is a function to encode pcm data to G711
 *
 *  @param in:
 *             dst: Pointer to destination/output buffer 
 * 
 *             src: Pointer to source/input buffer 
 *
 *             bufsize: size of the buffer/No of samples to be processed
 *
 *  @return    Output buffer size
 *
 */
int ALSARECORD_G711ulawEncode(short *dst, short *src, short bufsize)
{
  unsigned short i;
  short data;
  unsigned short isNegative;
  short nOut;
  short lowByte = 1;
  int outputSize = bufsize / 2;

  for (i = 0; i < outputSize; i++)
  {
    data = *(src + i);
    data >>= 2;
    isNegative = (data < 0 ? 1 : 0);
    if (isNegative)
      data = -data;

    if (data <= 1)
	{
      nOut = (char) data;
    }
	else if (data <= 31)
	{
      nOut = ((data - 1) >> 1) + 1;
    }
	else if (data <= 95)
	{
      nOut = ((data - 31) >> 2) + 16;
    }
	else if (data <= 223)
    {
      nOut = ((data - 95) >> 3) + 32;
    }
	else if (data <= 479)
	{
      nOut = ((data - 223) >> 4) + 48;
    }
	else if (data <= 991)
	{
      nOut = ((data - 479) >> 5) + 64;
    }
	else if (data <= 2015)
	{
      nOut = ((data - 991) >> 6) + 80;
    }
    else if (data <= 4063)
    {
      nOut = ((data - 2015) >> 7) + 96;
    }
    else if (data <= 7903)
    {
      nOut = ((data - 4063) >> 8) + 112;
    }
    else
    {
     nOut = 127;
    }

    if (isNegative)
	{
      nOut = 127 - nOut;
    }
    else
    {
      nOut = 255 - nOut;
    }

    // Pack the bytes in a word
    if (lowByte)
      *(dst + (i >> 1)) = (nOut & 0x00FF);
    else
      *(dst + (i >> 1)) |= ((nOut << 8) & 0xFF00);
      
	  lowByte ^= 0x1;
  }

  return (outputSize);
}

/******************************************************************************\
 *      ALSARECORD_ReadAudioSamples Definition
\******************************************************************************/
/**
 *
 *  @brief    This is a function to read audio samples
 *
 *  @param in:
 *             alsaRecordClient: Pointer to OMTB_ALSARECORD_PRIVATE 
 * 
 *             pInBuf: Buffer pointer to read the samples
 *
 *             readsamples: No of audio samples to read
 *
 *  @return     ALSA DRIVER return values
 *
 */
int ALSARECORD_ReadAudioSamples(OMTB_ALSARECORD_PRIVATE *alsaRecordClient,void *pInBuf, int readsamples)
{
  int rc;

  PRINT(PRINT_FUNCTION_NAME, "Entering <Function> : <%s>\n", __FUNCTION__);  
	 
  /* Read stereo data from codec */
  rc = snd_pcm_readi(alsaRecordClient->hAudioHandle, pInBuf, readsamples);

  if (rc == -EPIPE) 
  {
    /* EPIPE means overrun */
    PRINT(PRINT_ERR_MSG, "AUDIO WARNING:overrun occurred\n");
    snd_pcm_prepare(alsaRecordClient->hAudioHandle);
    return 0;
  }
  else
  {
    if( rc < 0 )
    {
      PRINT(PRINT_ERR_MSG, "AUDIO ERROR:error from read : %s\n",snd_strerror(rc));
    }
		
    return rc;
  
  }
  
  PRINT(PRINT_FUNCTION_NAME, "Leaving <Function> : <%s>\n", __FUNCTION__);
}
  

/******************************************************************************\
 *      ALSARECORD_AllocateMemory Definition
\******************************************************************************/
/**
 *
 *  @brief    Allocate memory for input buffer and output buffer
 *
 *  @param in:
 *           alsaRecordClient: Pointer to OMTB_ALSARECORD_PRIVATE 
 * 
 *  @return  OmtbReturn Value
 *
 */
OmtbRet ALSARECORD_AllocateMemory(OMTB_ALSARECORD_PRIVATE *alsaRecordClient)
{
  OmtbRet err = OMTB_SUCCESS;
  unsigned int retVal = TIMM_OSAL_ERR_NONE;  
  int i = 0;
  
  /* validate the function arguments */
  ASSERT(NULL != alsaRecordClient);
  
  PRINT(PRINT_FUNCTION_NAME, "Entering <Function> : <%s>\n", __FUNCTION__);  
	
  /* Allocating memory for Audio Buffers */
  alsaRecordClient->inputBuf = (unsigned short *)TIMM_OSAL_Malloc( OMTB_RAW_AUDIO_BUFFER_SIZE,
                                                  TIMM_OSAL_TRUE,
                                                  0,
                                                  TIMMOSAL_MEM_SEGMENT_EXT);
  if (NULL == alsaRecordClient->inputBuf)
  {
    PRINT(PRINT_ERR_MSG, "Input Buffer memory allocation failed\n");
    err = OMTB_INSUFFICIENT_RESOURCES;
	return err;
  }
  
  for(i = 0; i < OMTB_ALSARECORD_MAX_NUM_OUT_BUFS; i++)
  {
    alsaRecordClient->encodedBuf[i] = (short *)TIMM_OSAL_Malloc( OMTB_ENCODED_AUDIO_BUFFER_SIZE,
                                                              TIMM_OSAL_TRUE,
                                                              0,
                                                              TIMMOSAL_MEM_SEGMENT_EXT);
    if (NULL == alsaRecordClient->encodedBuf[i])
    {
      PRINT(PRINT_ERR_MSG, "Output Buffer memory allocation failed\n");
      err = OMTB_INSUFFICIENT_RESOURCES;
	  return err;
    }
  }

  /* Create pipe for output buffers */
  retVal = TIMM_OSAL_CreatePipe(
                    &(alsaRecordClient->opPipe),
                    ((sizeof(char*)) * OMTB_ALSARECORD_MAX_NUM_OUT_BUFS),
                     sizeof(char*),
					 OMX_TRUE );
					 
  if (TIMM_OSAL_ERR_NONE != retVal)
  {
    PRINT(PRINT_ERR_MSG, "TIMM_OSAL_CreatePipe failed to open\n");
    err = OMTB_INSUFFICIENT_RESOURCES;
  }
  
  PRINT(PRINT_FUNCTION_NAME, "Leaving <Function> : <%s>\n", __FUNCTION__);
  
  return err;
}


/******************************************************************************\
 *      ALSARECORD_FreeMemory Definition
\******************************************************************************/
/**
 *
 *  @brief    Allocate memory for input buffer and output buffer
 *
 *  @param in:
 *           alsaRecordClient: Pointer to OMTB_ALSARECORD_PRIVATE 
 * 
 *  @return  None
 *
 */
void ALSARECORD_FreeMemory(OMTB_ALSARECORD_PRIVATE *alsaRecordClient)
{
  int i = 0;
  /* validate the function arguments */
  ASSERT(NULL != alsaRecordClient);

  PRINT(PRINT_FUNCTION_NAME, "Entering <Function> : <%s>\n", __FUNCTION__);
  
  /* Free the Audio Buffers */
  if(NULL != alsaRecordClient->inputBuf)
  {
    TIMM_OSAL_Free (alsaRecordClient->inputBuf);
	alsaRecordClient->inputBuf = NULL;
  }	
	
  for(i = 0; i < OMTB_ALSARECORD_MAX_NUM_OUT_BUFS; i++)
  {	
    if(NULL != alsaRecordClient->encodedBuf[i])
    {
      TIMM_OSAL_Free (alsaRecordClient->encodedBuf[i]);	
	  alsaRecordClient->encodedBuf[i] = NULL;
    }
  }	
    
  PRINT(PRINT_FUNCTION_NAME, "Leaving <Function> : <%s>\n", __FUNCTION__);
}

/******************************************************************************\
 *      ALSARECORD_FuncTsk Thread Definition
\******************************************************************************/
/**
 *
 *  @brief    This is a ALSA Record thread which invokes during func command
 *
 *  @param in:
 *            void * - Thread args count
 *
 *            void *threadsArg - Pointer to thread arg structure
 *
 *  @return   None
 *
 */

void ALSARECORD_FuncTsk(void *argc, void *threadsArg)
{
  int rc = 0;
  int numBytes = OMTB_RAW_AUDIO_BUFFER_SIZE;
  
#ifdef OMTB_AUDIO_RTP	  
  void *rtpSessionTx = NULL;
#endif  

  int encBufSize = 0;
  int sentlen = 0;
  static int npkt = 0;
  static unsigned int ts = 0;
  OMTB_ALSARECORD_PRIVATE *alsaRecordClient = ( OMTB_ALSARECORD_PRIVATE * ) threadsArg;
  
  TIMM_OSAL_ERRORTYPE osalError = TIMM_OSAL_ERR_NONE;
  OmtbRet err = OMTB_SUCCESS;

#ifdef OMTB_USE_PIPE  
  int instanceNo = 0;
  int i = 0;
  OMTB_ALSAPLAY_PRIVATE *alsaPlayClient = NULL;  
  short *pOutBuf = NULL;
  unsigned int actualSize = 0;
#endif
				
  /* thread argument validation */
  ASSERT(NULL != threadsArg);
  ASSERT(NULL != alsaRecordClient->hAudioHandle);
   
  PRINT(PRINT_FUNCTION_NAME, "Entering <Function> : <%s>\n", __FUNCTION__);  
  
  err = ALSARECORD_AllocateMemory(alsaRecordClient);
  /* Check for memory allocation */
  if(OMTB_SUCCESS != err)
    return;
	
#ifdef OMTB_AUDIO_RTP	
  /*Initiate a RTP session for audio send*/
  rtpSessionTx = (void *)rtp_init_audio_send(alsaRecordConfig->nAudioPort, alsaRecordConfig->remoteIP, 96);
  
  if (rtpSessionTx !=NULL)
  {
    PRINT(PRINT_MUST, "\nSpeech Sent (RTP) on port %d ip %s\n",	alsaRecordConfig->nAudioPort, alsaRecordConfig->remoteIP);
  }  
  else
  {
    PRINT(PRINT_ERR_MSG, "\nRTP Error: SPEECH SEND INIT FAILED\n");
	/* Free the input and output audio buffers */
	ALSARECORD_FreeMemory(alsaRecordClient);
    return;	
  }
#endif

#ifdef OMTB_USE_PIPE    
   /* Prime the buffers / use intial resources */
   for(i = 0; i < OMTB_ALSARECORD_MAX_NUM_OUT_BUFS; i++)	
   {
     pOutBuf = alsaRecordClient->encodedBuf[i];
     TIMM_OSAL_WriteToPipe (alsaRecordClient->opPipe,
                            &pOutBuf,
                            sizeof(pOutBuf),
                            TIMM_OSAL_SUSPEND );	
   }							
#endif
						   
  /* Periodically wakeup and  pump the data.                                  */
  //FIXME: TO add a timer/counter instead of loop forever
  while ( 1 )
  {
    /* Read PCM audio data */
	rc = ALSARECORD_ReadAudioSamples(alsaRecordClient, alsaRecordClient->inputBuf, OMTB_AUDIO_NUM_SAMPLES);
    if (rc == 0) 
    {
      /* EPIPE means overrun */
      PRINT(PRINT_ERR_MSG, "EPIPE in ALSARECORD_ReadAudioSamples\n");
      continue;
    } 
    else if (rc < 0) 
    {
      PRINT(PRINT_ERR_MSG, "AUDIO ERROR: Read %d samples\n",rc);
      break;
    }
    else if (rc != (int)OMTB_AUDIO_NUM_SAMPLES) 
    {
      PRINT(PRINT_ERR_MSG, "AUDIO WARNING:short read, read %d frames\n",rc);
      numBytes = rc<<1;
    } 
    else 
    {
      numBytes = OMTB_RAW_AUDIO_BUFFER_SIZE;
    }

#ifdef OMTB_USE_PIPE    
	/* Read empty buffer pointer from the pipe */
    TIMM_OSAL_ReadFromPipe (alsaRecordClient->opPipe,
                            &pOutBuf,
                            sizeof(pOutBuf),
                            (void*) &actualSize,
                            TIMM_OSAL_SUSPEND );
#else
    pOutBuf = alsaRecordClient->encodedBuf[0];
#endif

   encBufSize = ALSARECORD_G711ulawEncode((short*)pOutBuf,(short *)alsaRecordClient->inputBuf,numBytes);
   
    if ((encBufSize == 0)|| (pOutBuf == NULL))
    {
      PRINT(PRINT_ERR_MSG, "Audio Encode failed\n");
    }
    else
    {
#ifdef OMTB_AUDIO_RTP		
      sentlen = rtp_session_send_with_ts(rtpSessionTx, (unsigned char *)pOutBuf, encBufSize, ts);
      ts += (sentlen -12);
      npkt++;
#endif			

#ifdef OMTB_USE_PIPE
    alsaPlayClient = (OMTB_ALSAPLAY_PRIVATE*)omtbClass[OMTB_ALSAPLAY_CLASS].alsaPlayClient[instanceNo];
	
	/* Write to the pipe of alsa playback*/
    TIMM_OSAL_WriteToPipe (alsaPlayClient->ipPipe,
                           &pOutBuf,
                           sizeof(pOutBuf),
                           TIMM_OSAL_SUSPEND);	
#endif

	}
			
    osalError = TIMM_OSAL_SleepTask ( OMTB_AUDIO_PERIODIC_TASK_SLEEP_DURATION );
    if (osalError != TIMM_OSAL_ERR_NONE)
	{
      PRINT(PRINT_ERR_MSG, "TIMM_OSAL_SleepTask Error\n");
    }
    ASSERT(TIMM_OSAL_ERR_NONE == osalError);
  }

  /* Free the input and output audio buffers */
  ALSARECORD_FreeMemory(alsaRecordClient);
  
  PRINT(PRINT_FUNCTION_NAME, "Leaving <Function> : <%s>\n", __FUNCTION__);
  
  return;
}

/******************************************************************************\
 *      ALSARECORD_SetHwparam Function Definition
\******************************************************************************/
/**
 *
 *  @brief    Set the hardware params for ALSA RECORD/CAPTURE
 *
 *  @param in:
 *            alsaRecordClient: Pointer to OMTB_ALSARECORD_PRIVATE 
 *
 *            
 *  @param Out:
 *            None
 *
 *  @return   OMX_ERRORTYPE - OMX standard error code
 *
 */
OMX_ERRORTYPE ALSARECORD_SetHwparam(OMTB_ALSARECORD_PRIVATE* alsaRecordClient)
{
  OMX_ERRORTYPE err = OMX_ErrorNone;
  unsigned int val = 0;  
  int dir = 0;
  int rc = 0;
  unsigned int bufferTime = 0;
  snd_pcm_hw_params_t *sound_params = NULL;
  snd_pcm_uframes_t frames={0};
  
  PRINT(PRINT_FUNCTION_NAME, "Entering <Function> : <%s>\n", __FUNCTION__);  
  
  /* Allocate a hardware parameters object. */
  snd_pcm_hw_params_alloca(&sound_params);
  
  /* Fill it in with default values. */
  snd_pcm_hw_params_any(alsaRecordClient->hAudioHandle, sound_params);

  /* Set the desired hardware parameters. */
  /* Interleaved mode */
  snd_pcm_hw_params_set_access(alsaRecordClient->hAudioHandle, sound_params,
								SND_PCM_ACCESS_RW_INTERLEAVED );

  /* Signed 16-bit little-endian format */
  snd_pcm_hw_params_set_format(alsaRecordClient->hAudioHandle, sound_params,
	  					      SND_PCM_FORMAT_S16_LE);
  /* channels */
  snd_pcm_hw_params_set_channels(alsaRecordClient->hAudioHandle, sound_params, alsaRecordConfig->nChannels);

  /* Sampling rate*/
  val = alsaRecordConfig->nSamplingRate;
  
  snd_pcm_hw_params_set_rate_near(alsaRecordClient->hAudioHandle, sound_params, &val, &dir);
		
  if (val != alsaRecordConfig->nSamplingRate) 
  {
    PRINT(PRINT_ERR_MSG,"Rate doesn't match (requested %iHz, get %iHz)\n", alsaRecordConfig->nSamplingRate, val);
	err = OMX_ErrorUndefined;
    OMTB_OmxReturnStatus(err);	
    return err;
  }

  /* set the buffer time */
  if( bufferTime )
  {
	rc = snd_pcm_hw_params_set_buffer_time_near(alsaRecordClient->hAudioHandle, sound_params, &bufferTime, &dir);
	if (rc < 0)
	{
	 PRINT(PRINT_ERR_MSG,"Unable to set buffer time %i for Recordture: %s\n", bufferTime, snd_strerror(rc));
	err = OMX_ErrorUndefined;
	OMTB_OmxReturnStatus(err);
    return err;
    }
  }  
	
  /* Set period size of frames. */
  frames = alsaRecordConfig->nNumSamples;
  snd_pcm_hw_params_set_period_size_near(alsaRecordClient->hAudioHandle,
									 sound_params, &frames, &dir);

  /* Write the parameters to the driver */
  rc = snd_pcm_hw_params(alsaRecordClient->hAudioHandle, sound_params);
  if (rc < 0) 
  {
	PRINT(PRINT_ERR_MSG, "Unable to set hw parameters: %s\n", snd_strerror(rc));
	err = OMX_ErrorUndefined;
    OMTB_OmxReturnStatus(err);  	
    return err;
  }	
  
  /* Use a buffer large enough to hold one period */
  snd_pcm_hw_params_get_period_size(sound_params, &frames, &dir);		
  PRINT(PRINT_MUST, "ALSA record period size = %d frames\n", (int)frames);

  snd_pcm_hw_params_get_period_time(sound_params, &val, &dir);
  PRINT(PRINT_MUST, "ALSA record period time = %d us\n", val);
  
  PRINT(PRINT_FUNCTION_NAME, "Leaving <Function> : <%s>\n", __FUNCTION__);
  
  return err;
}  
  
  
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

OMX_ERRORTYPE ALSARECORD_GetHandle(
  OMTB_COMP_HANDLE * classPtr,
  unsigned int instance)
{
  OMX_ERRORTYPE err = OMX_ErrorNone;
  OMTB_ALSARECORD_PRIVATE* alsaRecordClient = NULL;
  int rc = 0;
  
  /* validate the function arguments */
  ASSERT(NULL != classPtr);

  PRINT(PRINT_FUNCTION_NAME, "Entering <Function , instance #> : <%s , %d>\n",
                              __FUNCTION__, (int)instance);

  /* Allocate memory for application private data */
  alsaRecordClient = (OMTB_ALSARECORD_PRIVATE *)
                    TIMM_OSAL_Malloc( sizeof(OMTB_ALSARECORD_PRIVATE),
                                      TIMM_OSAL_TRUE,
                                      0,
                                      TIMMOSAL_MEM_SEGMENT_EXT);

  if (!alsaRecordClient)
  {
    PRINT(PRINT_ERR_MSG, "Error allocating alsaRecordClient structure \n");
    err = (OMX_ERRORTYPE)OMTB_INSUFFICIENT_RESOURCES;
    return err;
  }
  else
  {
    /* Update the application instance management structure with app pvt data
       structure pointer */
    classPtr->alsaRecordClient[instance] =
                          (struct OMTB_ALSARECORD_PRIVATE *)alsaRecordClient;
    TIMM_OSAL_Memset(alsaRecordClient, 0, sizeof(OMTB_ALSARECORD_PRIVATE));
    alsaRecordClient->omtbPvt.instanceNo = instance;
  }

  /* Open PCM device for recording/capturing */
  rc = snd_pcm_open(&(alsaRecordClient->hAudioHandle), "default",
	  		          SND_PCM_STREAM_CAPTURE, 0);
  if (rc < 0)
  {
    PRINT(PRINT_ERR_MSG,"Unable to create/open pcm device: %s\n", snd_strerror(rc));
    err = OMX_ErrorInvalidComponent;
  }

  if(OMX_ErrorNone != err)
  {
    OMTB_OmxReturnStatus(err);
    return err;
  }
  else
  {
    /* Update the application instance management structure with handle */
    classPtr->handle[instance] = alsaRecordClient->hAudioHandle;
    PRINT(PRINT_MUST,
          "\r      \n\nOMTB-ALSARECORD Instance #: %d\n\n", instance);
  }

  /* Set the Audio Hardware Parameters */
   err = ALSARECORD_SetHwparam(alsaRecordClient);
  
	
  PRINT(PRINT_FUNCTION_NAME, "Leaving <Function , instance #> : <%s , %d>\n",
                              __FUNCTION__, (int)alsaRecordClient->omtbPvt.instanceNo);

  return err;
}


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

void ALSARECORD_FreeHandle(OMTB_ALSARECORD_PRIVATE *alsaRecordClient)
{
  /* validate the function arguments */
  ASSERT(NULL != alsaRecordClient);
  
  int instanceNo = alsaRecordClient->omtbPvt.instanceNo;


  PRINT(PRINT_FUNCTION_NAME, "Entering <Function , instance #> : <%s , %d>\n",
                              __FUNCTION__, (int)alsaRecordClient->omtbPvt.instanceNo);

  /* Flush the audio data */
  snd_pcm_drain(alsaRecordClient->hAudioHandle);
  
  /* Close the audio instance */
  snd_pcm_close(alsaRecordClient->hAudioHandle);

  /* Release app pvt data private structure */
  if(NULL != alsaRecordClient)
    TIMM_OSAL_Free(alsaRecordClient);

  PRINT(PRINT_FUNCTION_NAME, "Leaving <Function , instance #> : <%s , %d>\n",
                              __FUNCTION__, (int)instanceNo);
}

/******************************************************************************\
 *      ALSARECORD_SetTemplateDefVal Function Definition
\******************************************************************************/
/*
 *
 *  @brief    This function copies the default values in specified template.
 *
 *  @param in:
 *            pTemplate: Pointer to template structure
 *
 *  @param Out:
 *            None
 *
 *  @return
 *            ERR_NOERR           successful,
 *
 *            ERR_INVNAME         Incorrect template pointer/Memory allocation
 *                                error.
 */

MX_Result ALSARECORD_SetTemplateDefVal(OMTB_TEMPLATE_INFO *pTemplate)
{
  OMTB_ALSARECORD_CONFIG_PARAMS *alsaRecordCfg = NULL;

  /* param validation */
  if(NULL == pTemplate)
  {
    PRINT(PRINT_ERR_MSG, "%s: Memory for Template not allocated\n",__FUNCTION__);
    return ERR_INVNAME;
  }

  /* ALSARECORD configuration */
  alsaRecordCfg = &pTemplate->alsaRecordTemplate;

  strcpy(alsaRecordCfg->remoteIP,   OMTB_ALSARECORD_REMOTE_IP);
  
  alsaRecordCfg->nChannels = OMTB_AUDIO_NUM_CHANNELS;
  alsaRecordCfg->nSamplingRate = OMTB_AUDIO_SAMPLING_RATE;
  alsaRecordCfg->nNumSamples = OMTB_AUDIO_NUM_SAMPLES;
  alsaRecordCfg->nAudioPort = OMTB_AUDIO_PORT;
  
  return ERR_NOERR;
}

/*----------------------------- end of file ----------------------------------*/

