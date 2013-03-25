/*
 * omtbAlsaPlay.c
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
#if 1
#include "OMX_Core.h"
#include "OMX_Component.h"
#include "OMX_Types.h"
#include "OMX_TI_Common.h"
#include "OMX_TI_Index.h"
#include "omx_ctrl.h"
//#include "omx_alsaPlay_priv.h"

/******************************************************************************\
 *      Customized Includes
\******************************************************************************/

#include "omtbDebug.h"
#include "timm_osal_interfaces.h"

#include "omtbCommon.h"
#include "omtbCmd.h"
#endif

/******************************************************************************\
 *      Local Defines
\******************************************************************************/
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

/* Pointer to ALSAPLAY config params */
OMTB_ALSAPLAY_CONFIG_PARAMS *alsaPlayConfig = NULL;


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
 *      ALSAPLAY_G711ulawDecode Definition
\******************************************************************************/
/**
 *
 *  @brief    This is a function to encode pcm data to G711
 *
 *  @param in:
 *             input: input value to decode
 * 
 *
 *  @return    Output value
 *
 */
short ALSAPLAY_G711ulawDecode(unsigned short input)
{
  unsigned short isNegative;
  short nOut;

  isNegative= ((input & 0x80) == 0);
  if (isNegative) 
    nOut= 127 - input;
  else 
    nOut= 255 - input;

  if (nOut < 2)
    nOut *= 2;
  else if (nOut < 16) 
    nOut= ((nOut - 1) << 1) +1 + 1;
  else if (nOut < 32) 
    nOut= ((nOut - 16) << 2) +2 + 31;
  else if (nOut < 48) 
    nOut= ((nOut - 32) << 3) +4 + 95;
  else if (nOut < 64) 
    nOut= ((nOut - 48) << 4) +8 + 223;
  else if (nOut < 80) 
    nOut= ((nOut - 64) << 5) +16 + 479;
  else if (nOut < 96) 
    nOut= ((nOut - 80) << 6) +32 + 991;
  else if (nOut < 112) 
    nOut= ((nOut - 96) << 7) +64 + 2015;
  else 
    nOut= ((nOut - 112) << 8) +128 + 4063;
  
  if (isNegative)
    nOut= - nOut;
  
  nOut <<= 2;
  
  return nOut;
}

/******************************************************************************\
 *      ALSAPLAY_ReadAudioSamples Definition
\******************************************************************************/
/**
 *
 *  @brief    This is a function to read audio samples
 *
 *  @param in:
 *             alsaPlayClient: Pointer to OMTB_ALSAPLAY_PRIVATE 
 * 
 *             pInBuf: Buffer pointer to read the samples
 *
 *             readsamples: No of audio samples to read
 *
 *  @return     ALSA DRIVER return values
 *
 */
int ALSAPLAY_WriteAudioSamples(OMTB_ALSAPLAY_PRIVATE *alsaPlayClient,void *pInBuf, int writeSamples)
{
  int rc = 0;

  PRINT(PRINT_FUNCTION_NAME, "Entering <Function> : <%s>\n", __FUNCTION__);  
	
  while (writeSamples > 0)
  {
    rc = snd_pcm_writei(alsaPlayClient->hAudioHandle, pInBuf, writeSamples);

    if (rc == -EPIPE) 
    {
      /* EPIPE means overrun */
      PRINT(PRINT_ERR_MSG, "AUDIO WARNING: Underrun occurred. Preparing pcm..\n");
		
      if (snd_pcm_prepare(alsaPlayClient->hAudioHandle) < 0)
      {
        PRINT(PRINT_ERR_MSG, "Failed to recover from underrun\n");
      }
    }
    else
    {
      if( rc < 0 )
      {
        PRINT(PRINT_ERR_MSG, "AUDIO ERROR: error from write : %s\n",snd_strerror(rc));
				
        if (snd_pcm_prepare(alsaPlayClient->hAudioHandle) < 0)
        {
          PRINT(PRINT_ERR_MSG, "AUDIO ERROR: Failed to recover from snd_strerror\n");
        }
      }
      return rc;
    }
		
    if (rc == -EPIPE)
	{ 
      //memset(pInBuf, 0x7F, writeSamples*2*2);
      //printf("rc != writeSamples\n");
    }
    else
    {
      writeSamples -= rc;
    }
  }
  
  PRINT(PRINT_FUNCTION_NAME, "Leaving <Function> : <%s>\n", __FUNCTION__);
  
  return rc;  
}

/******************************************************************************\
 *      ALSAPLAY_AllocateMemory Definition
\******************************************************************************/
/**
 *
 *  @brief    Allocate memory for input buffer and output buffer
 *
 *  @param in:
 *           alsaPlayClient: Pointer to OMTB_ALSAPLAY_PRIVATE 
 * 
 *  @return  OmtbReturn Value
 *
 */
OmtbRet ALSAPLAY_AllocateMemory(OMTB_ALSAPLAY_PRIVATE *alsaPlayClient)
{
  OmtbRet err = OMTB_SUCCESS;
  unsigned int retVal = TIMM_OSAL_ERR_NONE;  
  
  /* validate the function arguments */
  ASSERT(NULL != alsaPlayClient);
  
  PRINT(PRINT_FUNCTION_NAME, "Entering <Function> : <%s>\n", __FUNCTION__);  
	
  /* Allocating memory for Audio Buffers */
  alsaPlayClient->outputBuf = (unsigned short *)TIMM_OSAL_Malloc( OMTB_RAW_AUDIO_BUFFER_SIZE,
                                                  TIMM_OSAL_TRUE,
                                                  0,
                                                  TIMMOSAL_MEM_SEGMENT_EXT);
  if (NULL == alsaPlayClient->outputBuf)
  {
    PRINT(PRINT_ERR_MSG, "Output Buffer memory allocation failed\n");
    err = OMTB_INSUFFICIENT_RESOURCES;
	return err;
  }
  
  alsaPlayClient->decodeBuf = (unsigned char *)TIMM_OSAL_Malloc( OMTB_ENCODED_AUDIO_BUFFER_SIZE,
                                                 TIMM_OSAL_TRUE,
                                                 0,
                                                 TIMMOSAL_MEM_SEGMENT_EXT);
  if (NULL == alsaPlayClient->decodeBuf)
  {
    PRINT(PRINT_ERR_MSG, "Input Buffer memory allocation failed\n");
    err = OMTB_INSUFFICIENT_RESOURCES;
	return err;
  }

  /* Create input pipe for input buffers */
  retVal = TIMM_OSAL_CreatePipe(
                    &(alsaPlayClient->ipPipe),
                    ((sizeof(char*)) * OMTB_ALSAPLAY_MAX_NUM_IN_BUFS),
                     sizeof(char*),
					 OMX_TRUE);

  if (TIMM_OSAL_ERR_NONE != retVal)
  {
    PRINT(PRINT_ERR_MSG, "TIMM_OSAL_CreatePipe failed to open\n");
    err = OMTB_INSUFFICIENT_RESOURCES;
  }
  
  PRINT(PRINT_FUNCTION_NAME, "Leaving <Function> : <%s>\n", __FUNCTION__);
  
  return err;
}


/******************************************************************************\
 *      ALSAPLAY_FreeMemory Definition
\******************************************************************************/
/**
 *
 *  @brief    Allocate memory for input buffer and output buffer
 *
 *  @param in:
 *           alsaPlayClient: Pointer to OMTB_ALSAPLAY_PRIVATE 
 * 
 *  @return  None
 *
 */
void ALSAPLAY_FreeMemory(OMTB_ALSAPLAY_PRIVATE *alsaPlayClient)
{

  /* validate the function arguments */
  ASSERT(NULL != alsaPlayClient);

  PRINT(PRINT_FUNCTION_NAME, "Entering <Function> : <%s>\n", __FUNCTION__);
  
  /* Free the Audio Buffers */
  if(NULL != alsaPlayClient->outputBuf)
  {
    TIMM_OSAL_Free (alsaPlayClient->outputBuf);
	alsaPlayClient->outputBuf = NULL;
  }	
	
  if(NULL != alsaPlayClient->decodeBuf)
  {
    TIMM_OSAL_Free (alsaPlayClient->decodeBuf);	
	alsaPlayClient->decodeBuf = NULL;
  }
    
  PRINT(PRINT_FUNCTION_NAME, "Leaving <Function> : <%s>\n", __FUNCTION__);
}

/******************************************************************************\
 *      ALSAPLAY_FuncTsk Thread Definition
\******************************************************************************/
/**
 *
 *  @brief    This is a ALSA Play thread which invokes during func command
 *
 *  @param in:
 *            void * - Thread args count
 *
 *            void *threadsArg - Pointer to thread arg structure
 *
 *  @return   None
 *
 */

void ALSAPLAY_FuncTsk(void *argc, void *threadsArg)
{
  int rc = 0, i = 0;
  int numBytes = OMTB_RAW_AUDIO_BUFFER_SIZE;
  int rcvLen = 0;
  void *rtpSessionRx = NULL;
  static int npkt = 0;
  static unsigned int ts = 0;
  static int totRcvd = 0;
  OMTB_ALSAPLAY_PRIVATE *alsaPlayClient = ( OMTB_ALSAPLAY_PRIVATE * ) threadsArg;
  TIMM_OSAL_ERRORTYPE osalError = TIMM_OSAL_ERR_NONE;
  OmtbRet err = OMTB_SUCCESS;
  
  /* thread argument validation */
  ASSERT(NULL != threadsArg);
  ASSERT(NULL != alsaPlayClient->hAudioHandle);
  
  PRINT(PRINT_FUNCTION_NAME, "Entering <Function> : <%s>\n", __FUNCTION__);  
  
  err = ALSAPLAY_AllocateMemory(alsaPlayClient);
  /* Check for memory allocation */
  if(OMTB_SUCCESS != err)
    return;

#ifdef OMTB_USE_PIPE  
  int instanceNo = 0;
  OMTB_ALSARECORD_PRIVATE *alsaRecordClient = NULL;  
  unsigned int actualSize = 0;
#endif
	
#ifdef OMTB_AUDIO_RTP  	
  /*Initiate a RTP session for audio receive*/
  rtpSessionRx = (void *)rtp_init_audio_recv(alsaPlayConfig->nAudioPort, 96);
  if (rtpSessionRx != NULL)
  {
    PRINT(PRINT_MUST, "\nAudio Receive (RTP) on port %d\n", alsaPlayConfig->nAudioPort);
  }
  else
  {
    PRINT(PRINT_ERR_MSG, "\nRTP Error: AUDIO RECV INIT FAILED\n");
	/* Free the input and output audio buffers */
	ALSAPLAY_FreeMemory(alsaPlayClient);
	
	return;
  }	
#endif
	
  /* Periodically wakeup and  pump the data */
  //FIXME: TO add a timer/counter instead of loop forever  
  while ( 1 )
  {

#ifdef OMTB_AUDIO_RTP  
    void *mp = NULL;
    /* receive RTP packet in message blk format */
    mp = rtp_session_recvm_with_ts (rtpSessionRx, ts);
    
	if (mp != NULL)
    {
      rcvLen = msg_to_buf_aac(mp, (unsigned char *)alsaPlayClient->decodeBuf, OMTB_ENCODED_AUDIO_BUFFER_SIZE);
      npkt++;
      totRcvd += rcvLen;	
#endif

#ifdef OMTB_USE_PIPE   
	/* Read the buffer pointer to be decoded from the pipe */
    TIMM_OSAL_ReadFromPipe (alsaPlayClient->ipPipe,
                            &alsaPlayClient->decodeBuf,
                            sizeof(alsaPlayClient->decodeBuf),
                            (void*) &actualSize,
                            TIMM_OSAL_SUSPEND);
#endif	

      for( i = 0; i < OMTB_ENCODED_AUDIO_BUFFER_SIZE; i++)
      {
        *((unsigned short*)alsaPlayClient->outputBuf + i) =  
		                   ALSAPLAY_G711ulawDecode(*((unsigned char *)alsaPlayClient->decodeBuf + i));
      }

#ifdef OMTB_USE_PIPE 
    alsaRecordClient = (OMTB_ALSARECORD_PRIVATE*)omtbClass[OMTB_ALSARECORD_CLASS].alsaRecordClient[instanceNo];  
	
	/* Write to the pipe of alsa record */
    TIMM_OSAL_WriteToPipe (alsaRecordClient->opPipe,
                            &alsaPlayClient->decodeBuf,
                            sizeof(alsaPlayClient->decodeBuf),
                            TIMM_OSAL_SUSPEND);
#endif	
	  
      /*Write PCM audio data*/
      rc = ALSAPLAY_WriteAudioSamples(alsaPlayClient, (unsigned short *)alsaPlayClient->outputBuf, OMTB_AUDIO_NUM_SAMPLES);

	  if (rc == 0) 
      {
        /* EPIPE means underrun */
        PRINT(PRINT_ERR_MSG, "EPIPE in Audio_DrvWrite\n");
        //return OSA_SOK;
      } 
      else if (rc < 0) 
      {
        PRINT(PRINT_ERR_MSG, "AUDIO ERROR: Wrote %d samples\n", rc);
        break;	
      }
      else if (rc != (int)OMTB_AUDIO_NUM_SAMPLES) 
      {
        PRINT(PRINT_ERR_MSG, "AUDIO WARNING: short write, wrote %d frames\n",rc);
        numBytes = rc<<1;
      } 
      else 
      {
        numBytes = rc;
      }
#ifdef OMTB_AUDIO_RTP	  
    }
    else
    {
      /* wait for RTP receive packets */
      rtp_session_wait_for_rxpkt(rtpSessionRx);
      //printf("rtp_session_wait_for_rxpkt in audio\n");
    }	
    

    if (rcvLen)
    {
      ts += rcvLen;
    }
    else
    {
      ts += OMTB_ENCODED_AUDIO_BUFFER_SIZE;
    }
   
    freemsg(mp);
    mp = NULL;		
#endif
    osalError = TIMM_OSAL_SleepTask ( OMTB_AUDIO_PERIODIC_TASK_SLEEP_DURATION );
    if (osalError != TIMM_OSAL_ERR_NONE)
	{
      PRINT(PRINT_ERR_MSG, "TIMM_OSAL_SleepTask Error\n");
    }
    ASSERT(TIMM_OSAL_ERR_NONE == osalError);
  }

  /* Free the input and output audio buffers */
  ALSAPLAY_FreeMemory(alsaPlayClient);
  
  PRINT(PRINT_FUNCTION_NAME, "Leaving <Function> : <%s>\n", __FUNCTION__);
  
  return;
}

/******************************************************************************\
 *      ALSAPLAY_SetHwparam Function Definition
\******************************************************************************/
/**
 *
 *  @brief    Set the hardware params for ALSA PLAY/CAPTURE
 *
 *  @param in:
 *            alsaPlayClient: Pointer to OMTB_ALSAPLAY_PRIVATE 
 *
 *            
 *  @param Out:
 *            None
 *
 *  @return   OMX_ERRORTYPE - OMX standard error code
 *
 */
OMX_ERRORTYPE ALSAPLAY_SetHwparam(OMTB_ALSAPLAY_PRIVATE* alsaPlayClient)
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
  snd_pcm_hw_params_any(alsaPlayClient->hAudioHandle, sound_params);

  /* Set the desired hardware parameters. */
  /* Interleaved mode */
  snd_pcm_hw_params_set_access(alsaPlayClient->hAudioHandle, sound_params,
								SND_PCM_ACCESS_RW_INTERLEAVED );

  /* Signed 16-bit little-endian format */
  snd_pcm_hw_params_set_format(alsaPlayClient->hAudioHandle, sound_params,
	  					      SND_PCM_FORMAT_S16_LE);
  /* channels */
  snd_pcm_hw_params_set_channels(alsaPlayClient->hAudioHandle, sound_params, alsaPlayConfig->nChannels);

  /* Sampling rate*/
  val = alsaPlayConfig->nSamplingRate;
  
  snd_pcm_hw_params_set_rate_near(alsaPlayClient->hAudioHandle, sound_params, &val, &dir);
		
  if (val != alsaPlayConfig->nSamplingRate) 
  {
    PRINT(PRINT_ERR_MSG,"Rate doesn't match (requested %iHz, get %iHz)\n", alsaPlayConfig->nSamplingRate, val);
	err = OMX_ErrorUndefined;
    OMTB_OmxReturnStatus(err);	
    return err;
  }

  /* set the buffer time */
  if( bufferTime )
  {
	rc = snd_pcm_hw_params_set_buffer_time_near(alsaPlayClient->hAudioHandle, sound_params, &bufferTime, &dir);
	if (rc < 0)
	{
	 PRINT(PRINT_ERR_MSG,"Unable to set buffer time %i for Playture: %s\n", bufferTime, snd_strerror(rc));
	err = OMX_ErrorUndefined;
	OMTB_OmxReturnStatus(err);
    return err;
    }
  }  
	
  /* Set period size of frames. */
  frames = alsaPlayConfig->nNumSamples;
  snd_pcm_hw_params_set_period_size_near(alsaPlayClient->hAudioHandle,
									 sound_params, &frames, &dir);

  /* Write the parameters to the driver */
  rc = snd_pcm_hw_params(alsaPlayClient->hAudioHandle, sound_params);
  if (rc < 0) 
  {
	PRINT(PRINT_ERR_MSG, "Unable to set hw parameters: %s\n", snd_strerror(rc));
	err = OMX_ErrorUndefined;
    OMTB_OmxReturnStatus(err);  	
    return err;
  }	
  
  /* Use a buffer large enough to hold one period */
  snd_pcm_hw_params_get_period_size(sound_params, &frames, &dir);		
  PRINT(PRINT_MUST, "ALSA play period size = %d frames\n", (int)frames);

  snd_pcm_hw_params_get_period_time(sound_params, &val, &dir);
  PRINT(PRINT_MUST, "ALSA play period time = %d us\n", val);
  
  PRINT(PRINT_FUNCTION_NAME, "Leaving <Function> : <%s>\n", __FUNCTION__);
  
  return err;
}  
  
  
/******************************************************************************\
 *      ALSAPLAY_GetHandle Function Definition
\******************************************************************************/
/**
 *
 *  @brief    Get the handle for ALSAPLAY component
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

OMX_ERRORTYPE ALSAPLAY_GetHandle(
  OMTB_COMP_HANDLE * classPtr,
  unsigned int instance)
{
  OMX_ERRORTYPE err = OMX_ErrorNone;
  OMTB_ALSAPLAY_PRIVATE* alsaPlayClient = NULL;
  int rc = 0;
  
  /* validate the function arguments */
  ASSERT(NULL != classPtr);

  PRINT(PRINT_FUNCTION_NAME, "Entering <Function , instance #> : <%s , %d>\n",
                              __FUNCTION__, (int)instance);

  /* Allocate memory for application private data */
  alsaPlayClient = (OMTB_ALSAPLAY_PRIVATE *)
                    TIMM_OSAL_Malloc( sizeof(OMTB_ALSAPLAY_PRIVATE),
                                      TIMM_OSAL_TRUE,
                                      0,
                                      TIMMOSAL_MEM_SEGMENT_EXT);

  if (!alsaPlayClient)
  {
    PRINT(PRINT_ERR_MSG, "Error allocating alsaPlayClient structure \n");
    err = (OMX_ERRORTYPE)OMTB_INSUFFICIENT_RESOURCES;
    return err;
  }
  else
  {
    /* Update the application instance management structure with app pvt data
       structure pointer */
    classPtr->alsaPlayClient[instance] =
                          (struct OMTB_ALSAPLAY_PRIVATE *)alsaPlayClient;
    TIMM_OSAL_Memset(alsaPlayClient, 0, sizeof(OMTB_ALSAPLAY_PRIVATE));
    alsaPlayClient->omtbPvt.instanceNo = instance;
  }

  /* Open PCM device for playing */
  rc = snd_pcm_open(&(alsaPlayClient->hAudioHandle), "default",
	  		          SND_PCM_STREAM_PLAYBACK, 0);
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
    classPtr->handle[instance] = alsaPlayClient->hAudioHandle;
    PRINT(PRINT_MUST,
          "\r      \n\nOMTB-ALSAPLAY Instance #: %d\n\n", instance);
  }

  /* Set the Audio Hardware Parameters */
   err = ALSAPLAY_SetHwparam(alsaPlayClient);
  
	
  PRINT(PRINT_FUNCTION_NAME, "Leaving <Function , instance #> : <%s , %d>\n",
                              __FUNCTION__, (int)alsaPlayClient->omtbPvt.instanceNo);

  return err;
}


/******************************************************************************\
 *      ALSAPLAY_FreeHandle Function Definition
\******************************************************************************/
/**
 *
 *  @brief    Free the memory allocated for the component
 *
 *  @param in:
 *            alsaPlayClient: Pointer to OMTB_ALSAPLAY_PRIVATE struct
 *
 *  @return   None
 *
 */

void ALSAPLAY_FreeHandle(OMTB_ALSAPLAY_PRIVATE *alsaPlayClient)
{
  /* validate the function arguments */
  ASSERT(NULL != alsaPlayClient);
  
  int instanceNo = alsaPlayClient->omtbPvt.instanceNo;

  PRINT(PRINT_FUNCTION_NAME, "Entering <Function , instance #> : <%s , %d>\n",
                              __FUNCTION__, (int)alsaPlayClient->omtbPvt.instanceNo);

  /* Flush the audio data */
  snd_pcm_drain(alsaPlayClient->hAudioHandle);
  
  /* Close the audio instance */
  snd_pcm_close(alsaPlayClient->hAudioHandle);

  /* Release app pvt data private structure */
  if(NULL != alsaPlayClient)
    TIMM_OSAL_Free(alsaPlayClient);

  PRINT(PRINT_FUNCTION_NAME, "Leaving <Function , instance #> : <%s , %d>\n",
                              __FUNCTION__, (int)instanceNo);
}

/******************************************************************************\
 *      ALSAPLAY_SetTemplateDefVal Function Definition
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

MX_Result ALSAPLAY_SetTemplateDefVal(OMTB_TEMPLATE_INFO *pTemplate)
{
  OMTB_ALSAPLAY_CONFIG_PARAMS *alsaPlayCfg = NULL;

  /* param validation */
  if(NULL == pTemplate)
  {
    PRINT(PRINT_ERR_MSG, "%s: Memory for Template not allocated\n",__FUNCTION__);
    return ERR_INVNAME;
  }

  /* ALSAPLAY configuration */
  alsaPlayCfg = &pTemplate->alsaPlayTemplate;

  alsaPlayCfg->nChannels = OMTB_AUDIO_NUM_CHANNELS;
  alsaPlayCfg->nSamplingRate = OMTB_AUDIO_SAMPLING_RATE;
  alsaPlayCfg->nNumSamples = OMTB_AUDIO_NUM_SAMPLES;
  alsaPlayCfg->nAudioPort = OMTB_AUDIO_PORT;
  
return ERR_NOERR;
}

/*----------------------------- end of file ----------------------------------*/

