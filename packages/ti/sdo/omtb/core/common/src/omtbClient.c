/*
/*
 * omtbClient.c
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
#include <stdlib.h>

/* OMX standard header files */
#include "OMX_Core.h"
#include "OMX_Component.h"
#include "OMX_Types.h"
#include "OMX_TI_Index.h"

/******************************************************************************\
 *      Customized Includes
\******************************************************************************/

#include "omtbDebug.h"
#include "timm_osal_interfaces.h"

#include "omtbCommon.h"
#include "omtbCmd.h"
#include "omtbClient.h"
#include "domx_util.h"
/******************************************************************************\
 *      Local Defines
\******************************************************************************/

#define FILEIO_PROFILE

#ifdef V_PROFILE
#include <sys/time.h>
#define FRAME_COUNT 120
OMX_HANDLETYPE cc_handle = NULL, dc0_handle = NULL, dc1_handle = NULL;
int E_FLAG = 0;
struct timeval timeCatch_c, timeCatch_d0, timeCatch_d1;
unsigned int val1_c = 0, val2_c = 0, fps_c = 0, vcount_c = 0;
unsigned int val1_d0 = 0, val2_d0 = 0, fps_d0 = 0, vcount_d0 = 0;
unsigned int val1_d1 = 0, val2_d1 = 0, fps_d1 = 0, vcount_d1 = 0;
#endif 

#ifdef FILEIO_PROFILE
struct timeval time_file_read, time_file_write;
OMX_U64 before_read = 0, after_read = 0, timer_read = 0, total_bytes_read = 0;
OMX_U64 before_write = 0, after_write = 0, timer_write = 0, total_bytes_write = 0;
#endif

static OMX_CALLBACKTYPE OMTB_Callback = {
  OMTB_ClientEventHandler,      /* Event handler callback */
  OMTB_ClientEmptyBufferDone,   /* Empty buffer done callback */
  OMTB_ClientFillBufferDone     /* Fill buffer done callback */
};
/******************************************************************************\
 *      Data type definitions
\******************************************************************************/

OMX_ERRORTYPE OMTB_ClientProcessPipeCmdFBD(OMTB_CLIENT_PRIVATE *,
                                           OMTB_CLIENT_PIPE_MSG *);
OMX_ERRORTYPE OMTB_ClientProcessPipeCmdFTB(OMTB_CLIENT_PRIVATE *,
                                           OMTB_CLIENT_PIPE_MSG *);
OMX_ERRORTYPE OMTB_ClientProcessPipeCmdEBD(OMTB_CLIENT_PRIVATE *,
                                           OMTB_CLIENT_PIPE_MSG *);
OMX_ERRORTYPE OMTB_ClientProcessPipeCmdETB(OMTB_CLIENT_PRIVATE *,
                                           OMTB_CLIENT_PIPE_MSG *);
OMX_ERRORTYPE OMTB_ClientEmptyBufferDone(OMX_HANDLETYPE hComponent,
                                         OMX_PTR ptrAppData,
                                         OMX_BUFFERHEADERTYPE * pBuffer);

/******************************************************************************\
 *      Extern Object Definitions
\******************************************************************************/
/* global semaphote used for proprietary tunneling */
extern void *gOmtbEofSem;

/* global flag used for demo */
extern OMX_BOOL gOmtbStopVdecDemoFlag;

/* global semaphote used for demo */
extern void *gOmtbVdecDemoSem;

/* global flag used for demo */
extern OMX_BOOL gOmtbStopVencDemoFlag;

/* global semaphote used for vdec demo */
extern void *gOmtbVencDemoSem;
/******************************************************************************\
 *      OMTB_ClientEventHandler callback Function Definition
\******************************************************************************/
/**
 *
 *  @brief    Event handler Callback of the component
 *
 *  @param in:
 *            hComponent: Component Handle
 *
 *            pAppData  : Pointer to Private Data Structure
 *
 *            eEvent    : Variable to OMX_EVENTTYPE enum
 *
 *            nData1     : data associated with event
 *
 *            nData2     : data associated with event
 *
 *            pEventData: Extra Data associated with the event
 *
 *  @return   err       : OMX_ErrorType
 *
 */

OMX_ERRORTYPE OMTB_ClientEventHandler(
  OMX_OUT OMX_HANDLETYPE hComponent,
  OMX_OUT OMX_PTR pAppData,
  OMX_OUT OMX_EVENTTYPE eEvent,
  OMX_OUT OMX_U32 nData1,
  OMX_OUT OMX_U32 nData2,
  OMX_OUT OMX_PTR pEventData)
{
  OMX_ERRORTYPE err = OMX_ErrorNone;
  OMTB_CLIENT_PRIVATE* thisClient = NULL;
  
  /* thread argument validation */
  ASSERT(NULL != hComponent);
  ASSERT(NULL != pAppData);

  thisClient = pAppData;
  
  PRINT(PRINT_FUNCTION_NAME, "Entering <Callback , instance #> : <%s , %d>\n",
                              __FUNCTION__, (int)thisClient->omtbPvt.instanceNo);

  /* Check the eEvent type */
  switch(eEvent)
  {
    case OMX_EventCmdComplete:  /* Command complete event */
      {
        /* state transition command related event */
        if (OMX_CommandStateSet == nData1)
        {
          PRINT(PRINT_MUST,
                "In %s: OMX_EventCmdComplete -  OMX_CommandStateSet\n",
                __FUNCTION__);
         
          switch ((int)nData2)
          {
            case OMX_StateInvalid:
                  PRINT(PRINT_MUST, "OMX_StateInvalid\n");
                  break;
            case OMX_StateLoaded:
                  PRINT(PRINT_MUST, "OMX_StateLoaded\n");
                  break;
            case OMX_StateIdle:
                  PRINT(PRINT_MUST, "OMX_StateIdle\n");
                  break;
            case OMX_StateExecuting:
                  PRINT(PRINT_MUST, "OMX_StateExecuting\n");
                  break;
            case OMX_StatePause:
                  PRINT(PRINT_MUST, "OMX_StatePause\n");
                  break;
            case OMX_StateWaitForResources:
                  PRINT(PRINT_MUST, "OMX_StateWaitForResources\n");
                  break;
          }

          /* Post the component event sem */
          TIMM_OSAL_SemaphoreRelease(thisClient->omtbPvt.eventSem);
        }
        /* port enable command event */
        else if ( OMX_CommandPortEnable == nData1 )
        {
          PRINT(PRINT_MUST,
                "In %s: OMX_CommandPortEnable on %d port\n", __FUNCTION__, nData2);
		  TIMM_OSAL_SemaphoreRelease(thisClient->omtbPvt.eventSem);		

        }
        /* port disable command event */
        else if ( OMX_CommandPortDisable == nData1  )
        {
          PRINT(PRINT_MUST,
                "In %s: OMX_CommandPortDisable on %d port\n", __FUNCTION__, nData2);
          TIMM_OSAL_SemaphoreRelease(thisClient->omtbPvt.eventSem);  
        }
        /* port flush command event */
        else if ( OMX_CommandFlush == nData1  )
        {
          PRINT(PRINT_MUST,
                "In %s: OMX_CommandFlush on %d port\n", __FUNCTION__, nData2);

        }
        /* port disable command event */
        else if ( OMX_CommandMarkBuffer == nData1  )
        {
          PRINT(PRINT_MUST,
                "In %s: OMX_CommandMarkBuffer on %d port\n", __FUNCTION__, nData2);

        }
      }
      break;

    case OMX_EventPortSettingsChanged: /* Port settings changed event */
      {
        PRINT(PRINT_MUST, "In %s: OMX_EventPortSettingsChanged on %d port\n",
                                    __FUNCTION__, nData1);

        if(0 == nData2)
        {
          /* Perform the port settings as per params received from component */
        }
      }
      break;

    case OMX_EventBufferFlag:  /* Buffer related events */
      {
        PRINT(PRINT_MUST, "In %s: OMX_EventBufferFlag - nFlags: %x on %d port\n",
                          __FUNCTION__, nData2, nData1);
        if(OMX_BUFFERFLAG_EOS == (int)(nData2 & OMX_BUFFERFLAG_EOS))
        {
          PRINT(PRINT_MUST, "OMX_EventBufferFlag - OMX_BUFFERFLAG_EOS\n");
          TIMM_OSAL_SemaphoreRelease(thisClient->omtbPvt.eofSem);
		   
          /* release the semaphore used for propreitary tunneling */
		  TIMM_OSAL_SemaphoreRelease(gOmtbEofSem);			  
        }
      }
      break;

    case OMX_EventError:  /* Event error */
      {
        PRINT(PRINT_MUST, "In %s: OMX_EventError - %x\n", __FUNCTION__, nData1);
        OMTB_OmxReturnStatus((OMX_ERRORTYPE)nData1);

        /* release the semaphore in case of incorrect state transitions */
        /*if((OMX_ErrorSameState == (OMX_ERRORTYPE)nData1)  ||
           (OMX_ErrorIncorrectStateTransition == (OMX_ERRORTYPE)nData1))
		*/   
        {
          /* Post the component event sem */
          TIMM_OSAL_SemaphoreRelease(thisClient->omtbPvt.eventSem);
        }
      }
      break;

    case OMX_EventMark: /* Event mark buffer */
      {
        PRINT(PRINT_MUST, "In %s: OMX_EventMark\n", __FUNCTION__);

      }
      break;

    case OMX_EventResourcesAcquired:  /* Event resources acquired */
      {
        PRINT(PRINT_MUST, "In %s: OMX_EventResourcesAcquired\n",
              __FUNCTION__);

      }
      break;

    case OMX_EventComponentResumed: /* Event component resumed */
      {
        PRINT(PRINT_MUST, "In %s: OMX_EventComponentResumed\n",
              __FUNCTION__);

      }
      break;

    case OMX_EventDynamicResourcesAvailable:// Event dynamic resources available
      {
        PRINT(PRINT_MUST,
              "In %s: OMX_EventDynamicResourcesAvailable\n",
              __FUNCTION__);

        /* Post the component event sem */
        TIMM_OSAL_SemaphoreRelease(thisClient->omtbPvt.eventSem);
      }
      break;

    case OMX_EventMax:   // Event not implemented
      {
        PRINT(PRINT_MUST, "In %s: Param1 is %i\n",
              __FUNCTION__, (int)nData1);
        PRINT(PRINT_MUST, "In %s: Param2 is %i\n",
              __FUNCTION__, (int)nData2);
        err = OMX_ErrorNotImplemented;
      }
      break;

    default:  // Event Bad Parameter
      {
        PRINT(PRINT_MUST, "In %s: Param1 is %i\n",
              __FUNCTION__, (int)nData1);
        PRINT(PRINT_MUST, "In %s: Param2 is %i\n",
              __FUNCTION__, (int)nData2);
        err = OMX_ErrorBadParameter;
      }
      break;

  } // switch(eEvent)

  PRINT(PRINT_FUNCTION_NAME, "Leaving <Callback , instance #> : <%s , %d>\n",
                              __FUNCTION__, (int)thisClient->omtbPvt.instanceNo);

  return err;
}

void OMTB_ClientUtilGetSelfBufHeader(OMTB_CLIENT_PRIVATE *thisClient, OMX_U8 *pBuffer, 
        OMTB_PORT_TYPE type,OMX_U32 portIndex, OMX_BUFFERHEADERTYPE **pBufferOut)
{
  int i, bufferFound = 0;
  OMTB_CLIENT_INPORT_PARAMS *inPortParamsPtr;
  OMTB_CLIENT_OUTPORT_PARAMS *outPortParamsPtr;
  
  
   if (type == OMTB_INPUT_PORT) {
      bufferFound = 0;   
      inPortParamsPtr = thisClient->inPortParams + portIndex; 
  for (i=0; i < inPortParamsPtr->cmnInParams.numInBuf; i++) {
     if(pBuffer == inPortParamsPtr->pInBuff[i]->pBuffer) {
       *pBufferOut = inPortParamsPtr->pInBuff[i];
	   bufferFound = 1; 
       }
    }
    if(!bufferFound)	
     PRINT(PRINT_ERR_MSG, "Input buffer not found in <%s>\n", __FUNCTION__);	
  }     
 else {
      bufferFound = 0;
      outPortParamsPtr = thisClient->outPortParams + portIndex - thisClient->omtbPvt.startOutportIndex ; 
  for (i=0; i < outPortParamsPtr->cmnOutParams.numOutBuf; i++) {
     if(pBuffer == outPortParamsPtr->pOutBuff[i]->pBuffer) {
       *pBufferOut = outPortParamsPtr->pOutBuff[i];
	   bufferFound = 1; 	   
       }
    }
    if(!bufferFound)	
     PRINT(PRINT_ERR_MSG, "Output buffer not found in <%s>\n", __FUNCTION__);	
  }    
  
 }

OMX_ERRORTYPE OMTB_ClientUseInitialOutputResources(
  OMTB_CLIENT_PRIVATE* thisClient)
{

  OMX_ERRORTYPE err = OMX_ErrorNone;
  unsigned int i = 0, j;
  OMTB_OMX_API_TIMING_VAR_DECL;
  OMTB_CLIENT_OUTPORT_PARAMS *outPortParamPtr = NULL;
  OMX_PARAM_PORTDEFINITIONTYPE param;
  /* validate the function arguments */
  ASSERT(NULL != thisClient);

  PRINT(PRINT_FUNCTION_NAME, "Entering <Function , instance #> : <%s , %d>\n",
                              __FUNCTION__, (int)thisClient->omtbPvt.instanceNo);

  TIMM_OSAL_Memset(&param, 0, sizeof(param));
  OMTB_SetHeader(&param, sizeof(OMX_PARAM_PORTDEFINITIONTYPE));                              
  /* Give output buffers to component which is limited by no of output buffers
     available. Rest of the data will be written on the callback from output
     data write thread */
    for (j = 0; j<thisClient->omtbPvt.numOutport; j++) {
      
      param.nPortIndex = j + thisClient->omtbPvt.startOutportIndex;

      OMX_GetParameter(thisClient->omtbPvt.handle,
                       OMX_IndexParamPortDefinition, &param);
                         
      outPortParamPtr = thisClient->outPortParams +  j;
      
       if ( OMX_TRUE == param.bEnabled )  {      
         if(outPortParamPtr->connInfo.remotePipe != NULL) {
         
            for(i = 0; i < thisClient->outPortParams->cmnOutParams.pOutPortDef->nBufferCountActual;
                i++)
            {
              /* API entry time calculation macro */
              OMTB_OMX_API_ENTRY_TIME_CALC;

              /* Pass the output buffer to the component */
              err = OMX_FillThisBuffer(
                                thisClient->omtbPvt.handle,
                                outPortParamPtr->pOutBuff[i]);

              /* API exit time calculation macro */
              OMTB_OMX_API_EXIT_TIME_CALC("OMX_FillThisBuffer");

              if(OMX_ErrorNone != err)
              {
                OMTB_OmxReturnStatus(err);
                return err;
              }
              else
              {
                PRINT(PRINT_DEBUG_MESSAGE,"Fill O/P Buffer\n");
              }
            }
           }
         }
      } 
  PRINT(PRINT_FUNCTION_NAME, "Leaving <Function , instance #> : <%s , %d>\n",
                              __FUNCTION__, (int)thisClient->omtbPvt.instanceNo);

  return err;
}

/*Send the CMD/Buffers to their respective neighboring components*/
void OMTB_ClientProcessPipeCmds(OMTB_CLIENT_PRIVATE *thisClient)
{
  OMTB_CLIENT_PIPE_MSG pipeMsg;
  unsigned int  numRemaining = 0;  
  int noInputBuffers = 0, noOutputBuffers = 0;
  int omtb_loop = OMX_TRUE;
  unsigned int actualSize = 0;
  
  int totalInputBuffers = 0;
  int totalOutputBuffers = 0;
  #if 0
  /* Get the total no of input buffers */
  if((NULL != thisClient->inPortParams->connInfo.remoteClient) && 
     (OMX_FALSE == thisClient->inPortParams->cmnInParams.flagUseInBuffer))
  {
    totalInputBuffers = thisClient->inPortParams->cmnInParams.numInBuf;
  }	
	
  /* Get the total no of output buffers */	
  if((NULL != thisClient->outPortParams->connInfo.remoteClient) &&
    (OMX_FALSE == thisClient->outPortParams->cmnOutParams.flagUseOutBuffer))
  {	
    totalOutputBuffers = thisClient->outPortParams->cmnOutParams.numOutBuf;
  }	
 #endif
  //printf("totalInputBuffers:%d, totalOutputBuffers:%d\n",totalInputBuffers, totalOutputBuffers);

  while(omtb_loop)
  {
    /*Get the total no of mesaages in pipe */
    TIMM_OSAL_GetPipeReadyMessageCount (thisClient->omtbPvt.localPipe,
                                      (void*) &numRemaining);

   /* break after receiving and sending all the buffers */
#if 0
   if((totalInputBuffers <= noInputBuffers) && 
	   (totalOutputBuffers <= noOutputBuffers) &&
	   (0 == numRemaining))
#else
    if((0 == numRemaining))
#endif	   
	{  
      PRINT(PRINT_MUST, "Received all the buffers from the component\n");      	
	  /* Break the loop once the component has received all the buffers */
	  break;
	}  

    while(numRemaining)
    {												 
      /* Read the buffer pointer from the local pipe */
      TIMM_OSAL_ReadFromPipe(thisClient->omtbPvt.localPipe,
                             &pipeMsg,
                             sizeof(OMTB_CLIENT_PIPE_MSG),
                             (void *) &actualSize,
							 TIMM_OSAL_SUSPEND);	

	  switch (pipeMsg.cmd) {

	  case OMTB_CLIENT_PIPE_CMD_ETB:
	       noInputBuffers++;
		   break;

      case OMTB_CLIENT_PIPE_CMD_FTB:
	       noOutputBuffers++;	
  		   break;

	  case OMTB_CLIENT_PIPE_CMD_EBD:
		   OMTB_ClientProcessPipeCmdEBD(thisClient, &pipeMsg);
		   break;

	  case OMTB_CLIENT_PIPE_CMD_FBD:
		   OMTB_ClientProcessPipeCmdFBD(thisClient, &pipeMsg);
		   break;

	  default:
		   break;
	  }
	 
	  /*Get the total no of mesaages in pipe */
      TIMM_OSAL_GetPipeReadyMessageCount (thisClient->omtbPvt.localPipe,
                                          (void*) &numRemaining);
    }	
  }//while(omtb_loop)	
}

void OMTB_ClientClearPipe(void *pipe, int size)
{
  void *tempPtr = NULL;
  unsigned int  numRemaining = 0;
  unsigned int actualSize = 0;

  /* Allocate the memory */
  tempPtr = (void*)TIMM_OSAL_Malloc( size,
                                     TIMM_OSAL_TRUE,
                                     0,
                                     TIMMOSAL_MEM_SEGMENT_EXT);	
  if(NULL == tempPtr)									 
    return;
	
 TIMM_OSAL_GetPipeReadyMessageCount (pipe, (void*) &numRemaining);		

  /* Clear the pipe / Ignore the buffers */	
  while(numRemaining)
  {												 
    /* Read the buffer pointer from the local pipe */
    TIMM_OSAL_ReadFromPipe( pipe,
                            tempPtr,
                            size,
                            (void *) &actualSize,
                            TIMM_OSAL_SUSPEND);	
    TIMM_OSAL_GetPipeReadyMessageCount (pipe, (void*) &numRemaining);							 
  } 							 

  /* FIXME: some times crashes when tried to free the memory */
  /* Free the memory */
  TIMM_OSAL_Free(tempPtr);	  
}
  
/* Both ports connected to some component */
void OMTB_Client_ConnIn_ConnOut_Tsk(void *argc, void *threadsArg)
{
    unsigned int actualSize = 0;
    OMTB_CLIENT_PIPE_MSG pipeMsg;
    OMTB_CLIENT_PRIVATE *thisClient = (OMTB_CLIENT_PRIVATE *) threadsArg;
    OMX_ERRORTYPE err = OMX_ErrorNone;
    unsigned int omtb_loop = OMX_TRUE;

    PRINT(PRINT_MUST, "Entering <Thread , instance #> : <%s>\n", __FUNCTION__);
					 
    OMTB_ClientUseInitialOutputResources(thisClient);
    
    for (;omtb_loop;) {
        /* Read from Pipe */
        TIMM_OSAL_ReadFromPipe(thisClient->omtbPvt.localPipe,
                               &pipeMsg,
                               sizeof(OMTB_CLIENT_PIPE_MSG),
                               (void *) &actualSize, TIMM_OSAL_SUSPEND);

        /* check the function type */

        switch (pipeMsg.cmd) {
        case OMTB_CLIENT_PIPE_CMD_ETB:
            err = OMTB_ClientProcessPipeCmdETB(thisClient, &pipeMsg);
			 
			/* put back the frame in pipe and exit the thread*/
            if(OMX_ErrorNone != err) {
              if(OMX_ErrorIncorrectStateOperation == err) {			
                TIMM_OSAL_WriteToPipe(thisClient->omtbPvt.localPipe,
                                      &pipeMsg,
                                      sizeof(OMTB_CLIENT_PIPE_MSG),
                                      TIMM_OSAL_SUSPEND);
                omtb_loop = OMX_FALSE;									   
              }	
              else {
			    OMTB_OmxReturnStatus(err);
			  }			   
             }
             break;
        case OMTB_CLIENT_PIPE_CMD_FTB:
            err = OMTB_ClientProcessPipeCmdFTB(thisClient, &pipeMsg);
           
		   /* put back the frame in pipe and exit the thread*/
            if(OMX_ErrorNone != err) {
              if(OMX_ErrorIncorrectStateOperation == err) {
               TIMM_OSAL_WriteToPipe(thisClient->omtbPvt.localPipe,
                                     &pipeMsg,
                                     sizeof(OMTB_CLIENT_PIPE_MSG),
                                     TIMM_OSAL_SUSPEND);
                omtb_loop = OMX_FALSE;									 
              }
              else {
			    OMTB_OmxReturnStatus(err);
			  }
            }
            break;

        case OMTB_CLIENT_PIPE_CMD_EBD:
            OMTB_ClientProcessPipeCmdEBD(thisClient, &pipeMsg);

            break;
        case OMTB_CLIENT_PIPE_CMD_FBD:
            OMTB_ClientProcessPipeCmdFBD(thisClient, &pipeMsg);
            break;
			
        case OMTB_CLIENT_PIPE_CMD_EXIT:
		    omtb_loop = OMX_FALSE; 
            break;			
			
        default:
            break;
        }

    }
  //printf("The execution of the conn data read is terminated\n");	
  PRINT(DEFAULT_MESSAGES, "The execution of the conn data read is terminated\n");
  
  /*Send the CMD/Buffers to their respective neighboring components 
    Wait to get back all the resources */
  //OMTB_ClientProcessPipeCmds(thisClient);
  //printf("DEBUG_1\n");	
  /* Clear if any buffers in pipe */
  //OMTB_ClientClearPipe(thisClient->omtbPvt.localPipe, sizeof(OMTB_CLIENT_PIPE_MSG));
  //printf("DEBUG_2\n");	
  /* post conn Data thread exit */
  TIMM_OSAL_SemaphoreRelease(thisClient->omtbPvt.connDataStrmThrExit);
  //printf("DEBUG_3\n");	 
  PRINT(PRINT_MUST, "Leaving <Thread #> : <%s>\n", __FUNCTION__);

  /* exit the thread */
  TIMM_OSAL_ExitTask(thisClient->omtbPvt.connDataStrmThrdId, NULL);	
}

OMX_ERRORTYPE OMTB_ClientProcessPipeCmdETB(OMTB_CLIENT_PRIVATE * thisClient,
                                           OMTB_CLIENT_PIPE_MSG * pipeMsg)
{
    OMX_ERRORTYPE err = OMX_ErrorNone;
    OMX_BUFFERHEADERTYPE *pBufferIn;

    /* search its own buffer header based on submitted by connected comp */
    OMTB_ClientUtilGetSelfBufHeader(thisClient, pipeMsg->bufHeader.pBuffer, OMTB_INPUT_PORT ,pipeMsg->bufHeader.nInputPortIndex, &pBufferIn);

    /* populate buffer header */
    pBufferIn->nFilledLen = pipeMsg->bufHeader.nFilledLen;
    pBufferIn->nOffset = pipeMsg->bufHeader.nOffset;
  //  pBufferIn->pAppPrivate = pipeMsg->bufHeader.pAppPrivate;
  //  pBufferIn->pPlatformPrivate = pipeMsg->bufHeader.pPlatformPrivate;
  //  pBufferIn->pInputPortPrivate = pipeMsg->bufHeader.pInputPortPrivate;
 //   pBufferIn->pOutputPortPrivate = pipeMsg->bufHeader.pOutputPortPrivate;
    pBufferIn->nTimeStamp = pipeMsg->bufHeader.nTimeStamp;
    pBufferIn->nFlags = pipeMsg->bufHeader.nFlags;
    pBufferIn->hMarkTargetComponent = pipeMsg->bufHeader.hMarkTargetComponent;
    pBufferIn->pMarkData = pipeMsg->bufHeader.pMarkData;
    pBufferIn->nTickCount = 0;


    /* call etb to the component */
    err = OMX_EmptyThisBuffer(thisClient->omtbPvt.handle, pBufferIn);
   
    return (err);
}

OMX_ERRORTYPE OMTB_ClientProcessPipeCmdFTB(OMTB_CLIENT_PRIVATE * thisClient,
                                           OMTB_CLIENT_PIPE_MSG * pipeMsg)
{
    OMX_ERRORTYPE err = OMX_ErrorNone;
    OMX_BUFFERHEADERTYPE *pBufferOut;

    /* search its own buffer header based on submitted by connected comp */
    OMTB_ClientUtilGetSelfBufHeader(thisClient, pipeMsg->bufHeader.pBuffer,OMTB_OUTPUT_PORT, pipeMsg->bufHeader.nOutputPortIndex, &pBufferOut);

    /* call etb to the component */
    err = OMX_FillThisBuffer(thisClient->omtbPvt.handle, pBufferOut);
    
    return (err);
}

OMX_ERRORTYPE OMTB_ClientProcessPipeCmdEBD(OMTB_CLIENT_PRIVATE * thisClient,
                                           OMTB_CLIENT_PIPE_MSG * pipeMsg)
{
    OMX_ERRORTYPE err = OMX_ErrorNone;
    OMX_BUFFERHEADERTYPE *pBufferIn;
    OMTB_CLIENT_PIPE_MSG remotePipeMsg;
    OMTB_CLIENT_INPORT_PARAMS *inPortParamsPtr;
    TIMM_OSAL_ERRORTYPE retVal = TIMM_OSAL_ERR_NONE;

    pBufferIn = pipeMsg->pbufHeader;
    
    inPortParamsPtr = thisClient->inPortParams + pBufferIn->nInputPortIndex;

    remotePipeMsg.cmd = OMTB_CLIENT_PIPE_CMD_FTB;
    remotePipeMsg.bufHeader.pBuffer = pBufferIn->pBuffer;
    remotePipeMsg.bufHeader.nOutputPortIndex = inPortParamsPtr->connInfo.remotePort;

    /* write the fill buffer message to remote pipe */
    retVal = TIMM_OSAL_WriteToPipe(inPortParamsPtr->connInfo.remotePipe,
                                   &remotePipeMsg,
                                   sizeof(OMTB_CLIENT_PIPE_MSG),
                                   TIMM_OSAL_SUSPEND);

    if (TIMM_OSAL_ERR_NONE != retVal) {
        PRINT(PRINT_ERR_MSG, "Error writing to remote Pipe!\n");
        err = OMX_ErrorNotReady;
        return err;
    }

    return (err);
}

OMX_ERRORTYPE OMTB_ClientProcessPipeCmdFBD(OMTB_CLIENT_PRIVATE * thisClient,
                                           OMTB_CLIENT_PIPE_MSG * pipeMsg)
{
    OMX_ERRORTYPE err = OMX_ErrorNone;
    OMX_BUFFERHEADERTYPE *pBufferOut;
    OMTB_CLIENT_PIPE_MSG remotePipeMsg;
    OMTB_CLIENT_OUTPORT_PARAMS *outPortParamsPtr;
    TIMM_OSAL_ERRORTYPE retVal = TIMM_OSAL_ERR_NONE;
    pBufferOut = pipeMsg->pbufHeader;

    remotePipeMsg.cmd = OMTB_CLIENT_PIPE_CMD_ETB;
    remotePipeMsg.bufHeader.pBuffer = pBufferOut->pBuffer;

    outPortParamsPtr =
        thisClient->outPortParams + (pBufferOut->nOutputPortIndex -
                                     thisClient->omtbPvt.startOutportIndex);

    /* populate buffer header */
    remotePipeMsg.bufHeader.nFilledLen = pBufferOut->nFilledLen;
    remotePipeMsg.bufHeader.nOffset = pBufferOut->nOffset;
  //  remotePipeMsg.bufHeader.pAppPrivate = pBufferOut->pAppPrivate;
 //   remotePipeMsg.bufHeader.pPlatformPrivate = pBufferOut->pPlatformPrivate;
 //   remotePipeMsg.bufHeader.pInputPortPrivate = pBufferOut->pInputPortPrivate;
 //   remotePipeMsg.bufHeader.pOutputPortPrivate = pBufferOut->pOutputPortPrivate;
    remotePipeMsg.bufHeader.nTimeStamp = pBufferOut->nTimeStamp;
    remotePipeMsg.bufHeader.nFlags = pBufferOut->nFlags;
    remotePipeMsg.bufHeader.hMarkTargetComponent = pBufferOut->hMarkTargetComponent;
    remotePipeMsg.bufHeader.pMarkData = pBufferOut->pMarkData;
    remotePipeMsg.bufHeader.nTickCount = pBufferOut->nTickCount;
    remotePipeMsg.bufHeader.nInputPortIndex = outPortParamsPtr->connInfo.remotePort;
    
    /* write the fill buffer message to remote pipe */
    retVal = TIMM_OSAL_WriteToPipe(outPortParamsPtr->connInfo.remotePipe,
                                   &remotePipeMsg,
                                   sizeof(OMTB_CLIENT_PIPE_MSG),
                                   TIMM_OSAL_SUSPEND);

    if (TIMM_OSAL_ERR_NONE != retVal) {
        PRINT(PRINT_ERR_MSG, "Error writing to remote Pipe!\n");
        err = OMX_ErrorNotReady;
        return err;
    }

    return (err);
}

OMX_ERRORTYPE OMTB_ClientEmptyBufferDone(OMX_HANDLETYPE hComponent,
                                         OMX_PTR ptrAppData,
                                         OMX_BUFFERHEADERTYPE * pBuffer)
{

    OMTB_CLIENT_PRIVATE *thisClient = (OMTB_CLIENT_PRIVATE *) ptrAppData;
    OMTB_CLIENT_INPORT_PARAMS *inPortParamsPtr;
    OMTB_CLIENT_PIPE_MSG localPipeMsg;

    OMX_ERRORTYPE err = OMX_ErrorNone;
    TIMM_OSAL_ERRORTYPE retVal = TIMM_OSAL_ERR_NONE;
    OMTB_OMX_API_TIMING_VAR_DECL;

    /* validate the function arguments */
    ASSERT(NULL != hComponent);
    ASSERT(NULL != thisClient);
    ASSERT(NULL != pBuffer);

    /* API entry time calculation macro */
    //  OMTB_OMX_API_ENTRY_TIME_CALC;
#ifdef V_PROFILE

	if(!E_FLAG){
                cc_handle = OMTB_GetCompHandle(OMTB_VPSS_VFCC_COMP_REF_STR, 0);
                dc0_handle = OMTB_GetCompHandle(OMTB_VPSS_VFDC_COMP_REF_STR, 0);
                dc1_handle = OMTB_GetCompHandle(OMTB_VPSS_VFDC_COMP_REF_STR, 1);
                E_FLAG = !E_FLAG;
                val1_d0 = 0;
                val2_d0 = 0;
                vcount_d0 = 0;
                val1_d1 = 0;
                val2_d1 = 0;
                vcount_d1 = 0;                
        }

if(hComponent == dc0_handle){
//      PRINT(PRINT_MUST, "***B:%d %d %d %d***\n", E_FLAG, val1, val2, vcount);
        if (vcount_d0 == 0){
                gettimeofday(&timeCatch_d0,0);
                val1_d0 = ((timeCatch_d0.tv_sec * 1000 * 1000) + timeCatch_d0.tv_usec);
        }
        vcount_d0++;

        if(vcount_d0 >= FRAME_COUNT){
                gettimeofday(&timeCatch_d0,0);
                val2_d0 = ((timeCatch_d0.tv_sec * 1000 * 1000) + timeCatch_d0.tv_usec);
                fps_d0 = ((vcount_d0*1000000)/(val2_d0 - val1_d0));
                //fprintf(stdout,"***********fps: %d", fps);
              PRINT(PRINT_DEBUG_MESSAGE,
              "***********fps_display 0: %d \n", (int)fps_d0);                  
              vcount_d0 = 0;
        }
//      PRINT(PRINT_MUST, "A:***%d %d %d %d***\n", E_FLAG, val1, val2, vcount);
}

if(hComponent == dc1_handle){
//      PRINT(PRINT_MUST, "***B:%d %d %d %d***\n", E_FLAG, val1, val2, vcount);
        if (vcount_d1 == 0){
                gettimeofday(&timeCatch_d1,0);
                val1_d1 = ((timeCatch_d1.tv_sec * 1000 * 1000) + timeCatch_d1.tv_usec);
        }
        vcount_d1++;

        if(vcount_d1 >= FRAME_COUNT){
                gettimeofday(&timeCatch_d1,0);
                val2_d1 = ((timeCatch_d1.tv_sec * 1000 * 1000) + timeCatch_d1.tv_usec);
                fps_d1 = ((vcount_d1*1000000)/(val2_d1 - val1_d1));
                //fprintf(stdout,"***********fps: %d", fps);
              //  printf( "***********fps_d1: %d \n", (int)fps_d1);
              PRINT(PRINT_DEBUG_MESSAGE,
              "***********fps_display 1: %d \n", (int)fps_d1);                
                vcount_d1 = 0;
        }
//      PRINT(PRINT_MUST, "A:***%d %d %d %d***\n", E_FLAG, val1, val2, vcount);
}
#endif
    PRINT(PRINT_FUNCTION_NAME, "Entering <Callback , instance #> : <%s , %d>\n",
          __FUNCTION__, (int) thisClient->omtbPvt.instanceNo);
    PRINT(PRINT_DEBUG_MESSAGE, "Address of pBuffer in emptybuff: %x\n",
          (unsigned int) pBuffer);

    inPortParamsPtr = thisClient->inPortParams + pBuffer->nInputPortIndex;

    if (inPortParamsPtr->connInfo.remotePipe == NULL) {
        /* write the empty buffer pointer to input pipe */
        retVal = TIMM_OSAL_WriteToPipe(inPortParamsPtr->cmnInParams.ipBufPipe,
                                       &pBuffer,
                                       sizeof(pBuffer), TIMM_OSAL_SUSPEND);

        if (TIMM_OSAL_ERR_NONE != retVal) {
            PRINT(PRINT_ERR_MSG, "Error writing to Input buffer i/p Pipe!\n");
            err = OMX_ErrorNotReady;
            return err;
        }

        PRINT(PRINT_FUNCTION_NAME,
              "Leaving <Callback , instance #> : <%s , %d>\n", __FUNCTION__,
              (int) thisClient->omtbPvt.instanceNo);
    }
    else {
        localPipeMsg.cmd = OMTB_CLIENT_PIPE_CMD_EBD;
        localPipeMsg.pbufHeader = pBuffer;
        retVal = TIMM_OSAL_WriteToPipe(thisClient->omtbPvt.localPipe,
                                       &localPipeMsg,
                                       sizeof(OMTB_CLIENT_PIPE_MSG),
                                       TIMM_OSAL_SUSPEND);

        if (TIMM_OSAL_ERR_NONE != retVal) {
            PRINT(PRINT_ERR_MSG, "Error writing to local Pipe!\n");
            err = OMX_ErrorNotReady;
            return err;
        }

    }
    /* API exit time calculation macro */
    //  OMTB_OMX_API_EXIT_TIME_CALC("H264VDEC_EmptyBufferDone");

    return err;
}

OMX_ERRORTYPE OMTB_ClientFillBufferDone(OMX_HANDLETYPE hComponent,
                                        OMX_PTR ptrAppData,
                                        OMX_BUFFERHEADERTYPE * pBuffer)
{

    OMTB_CLIENT_PRIVATE *thisClient = (OMTB_CLIENT_PRIVATE *) ptrAppData;
    OMTB_CLIENT_OUTPORT_PARAMS *outPortParamsPtr;
    OMTB_CLIENT_PIPE_MSG localPipeMsg;

    OMX_ERRORTYPE err = OMX_ErrorNone;
    TIMM_OSAL_ERRORTYPE retVal = TIMM_OSAL_ERR_NONE;
    OMTB_OMX_API_TIMING_VAR_DECL;

    /* validate the function arguments */
    ASSERT(NULL != hComponent);
    ASSERT(NULL != thisClient);
    ASSERT(NULL != pBuffer);

    /* API entry time calculation macro */
    //  OMTB_OMX_API_ENTRY_TIME_CALC;
#ifdef V_PROFILE
	if(!E_FLAG){
    cc_handle = OMTB_GetCompHandle(OMTB_VPSS_VFCC_COMP_REF_STR, 0);
    dc0_handle = OMTB_GetCompHandle(OMTB_VPSS_VFDC_COMP_REF_STR, 0);
    dc1_handle = OMTB_GetCompHandle(OMTB_VPSS_VFDC_COMP_REF_STR, 1);
		E_FLAG = !E_FLAG;
		val1_c = 0;
		val2_c = 0;
		vcount_c = 0;
	}

//PRINT(PRINT_MUST, "*************CLIENT FBD CALLED*******************%d %d %d\n", hComponent, cc_handle, dc_handle);

if(hComponent == cc_handle){
//	PRINT(PRINT_MUST, "***B:%d %d %d %d***\n", E_FLAG, val1, val2, vcount);
	if (vcount_c == 0){
                gettimeofday(&timeCatch_c,0);
                val1_c = ((timeCatch_c.tv_sec * 1000 * 1000) + timeCatch_c.tv_usec);
        }
        vcount_c++;

        if(vcount_c >= FRAME_COUNT){
                gettimeofday(&timeCatch_c,0);
                val2_c = ((timeCatch_c.tv_sec * 1000 * 1000) + timeCatch_c.tv_usec);
                fps_c = ((vcount_c*1000000)/(val2_c - val1_c));
                //fprintf(stdout,"***********fps: %d", fps);
              PRINT(PRINT_DEBUG_MESSAGE,
              "***********fps_capture : %d \n", (int)fps_c);                  
              vcount_c = 0;
        }
//	PRINT(PRINT_MUST, "A:***%d %d %d %d***\n", E_FLAG, val1, val2, vcount);
}
#endif
	

    PRINT(PRINT_FUNCTION_NAME, "Entering <Callback , instance #> : <%s , %d>\n",
          __FUNCTION__, (int) thisClient->omtbPvt.instanceNo);
    PRINT(PRINT_DEBUG_MESSAGE, "Address of pBuffer in emptybuff: %x\n",
          (unsigned int) pBuffer);

   /*		  
    outPortParamsPtr =
        thisClient->outPortParams + (pBuffer->nOutputPortIndex -
                                     thisClient->omtbPvt.startOutportIndex);
   */
    /* only one pipe is created for file write operation for all the ports*/
    outPortParamsPtr = thisClient->outPortParams;        

    if (outPortParamsPtr->connInfo.remotePipe == NULL) {
        /* write the empty buffer pointer to input pipe */
        retVal = TIMM_OSAL_WriteToPipe(outPortParamsPtr->cmnOutParams.opBufPipe,
                                       &pBuffer,
                                       sizeof(pBuffer), TIMM_OSAL_SUSPEND);

        if (TIMM_OSAL_ERR_NONE != retVal) {
            PRINT(PRINT_ERR_MSG, "Error writing to Input buffer i/p Pipe!\n");
            err = OMX_ErrorNotReady;
            return err;
        }

        /* Post the input data read thread */
       // TIMM_OSAL_SemaphoreRelease(outPortParamsPtr->
       //                            cmnOutParams.outputDataReady);

        PRINT(PRINT_FUNCTION_NAME,
              "Leaving <Callback , instance #> : <%s , %d>\n", __FUNCTION__,
              (int) thisClient->omtbPvt.instanceNo);
    }

    else {
        localPipeMsg.cmd = OMTB_CLIENT_PIPE_CMD_FBD;
        localPipeMsg.pbufHeader = pBuffer;
        retVal = TIMM_OSAL_WriteToPipe(thisClient->omtbPvt.localPipe,
                                       &localPipeMsg,
                                       sizeof(OMTB_CLIENT_PIPE_MSG),
                                       TIMM_OSAL_SUSPEND);

        if (TIMM_OSAL_ERR_NONE != retVal) {
            PRINT(PRINT_ERR_MSG, "Error writing to local Pipe!\n");
            err = OMX_ErrorNotReady;
            return err;
        }

    }
    /* API exit time calculation macro */
    //  OMTB_OMX_API_EXIT_TIME_CALC("H264VDEC_EmptyBufferDone");

    return err;
}


/******************************************************************************\
 *      OMTB_ClientFreeInputResources Function Definition
\******************************************************************************/
/**
 *
 *  @brief    Free the resources allocated for i/p port
 *
 *  @param in:
 *            thisClient: Pointer to OMTB_CLIENT_PRIVATE struct
 *
 *  @return   OMX_ERRORTYPE - OMX std return/error code
 *
 */

OMX_ERRORTYPE OMTB_ClientFreeInputResources(OMTB_CLIENT_PRIVATE *thisClient)
{
  OMX_ERRORTYPE err = OMX_ErrorNone;
  unsigned int i = 0, port = 0;
  OMX_PARAM_PORTDEFINITIONTYPE param;
  OMTB_CLIENT_INPORT_PARAMS *inPortParamPtr = NULL;
  OMTB_OMX_API_TIMING_VAR_DECL;

  /* validate the function arguments */
  ASSERT(NULL != thisClient);

  PRINT(PRINT_FUNCTION_NAME, "Entering <Function , instance #> : <%s , %d>\n",
                              __FUNCTION__, (int)thisClient->omtbPvt.instanceNo);
  for (port = 0; port < thisClient->omtbPvt.numInport; port++)
  {							  
    TIMM_OSAL_Memset(&param, 0, sizeof (param));
    OMTB_SetHeader( &param ,sizeof(OMX_PARAM_PORTDEFINITIONTYPE));
    param.nPortIndex = port;
    OMX_GetParameter (thisClient->omtbPvt.handle, OMX_IndexParamPortDefinition, &param);
    PRINT(PRINT_DEBUG_MESSAGE, " Input port index of the component, %d\n",
                                 (int)param.nPortIndex);
    PRINT(PRINT_DEBUG_MESSAGE, " Number of input buffers needed by the component is , %d\n",
                                 (int)param.nBufferCountActual);
    PRINT(PRINT_DEBUG_MESSAGE, " Input buffer size needed by the component is , %d\n",
                                 (int)param.nBufferSize);
    inPortParamPtr = thisClient->inPortParams + port;
	
    /* Ask component to Free input port buffers */
              /* OMX_AllocateBuffer */
    if ( OMX_TRUE == param.bEnabled ) {			  
    for(i = 0; i < (int)param.nBufferCountActual; i++)
    {
      PRINT(PRINT_DEBUG_MESSAGE, "Free I/P ports\n");

      PRINT(PRINT_DEBUG_MESSAGE, "Value of Handle is %x\n",\
            (unsigned int) thisClient->omtbPvt.handle);

      PRINT(PRINT_DEBUG_MESSAGE, "Port Index is %x\n", \
            (unsigned int) inPortParamPtr->cmnInParams.pInPortDef->nPortIndex);
      PRINT(PRINT_DEBUG_MESSAGE, "Buff addr is  %x\n",\
            (unsigned int) inPortParamPtr->pInBuff[i]);

       /* OMX_FreeBuffer */
      //if (OMX_FALSE == inPortParamPtr->cmnInParams.flagUseInBuffer)
	  {
        /* API entry time calculation macro */
        OMTB_OMX_API_ENTRY_TIME_CALC;

        /* freeing buffers of component input ports */
        err = OMX_FreeBuffer( thisClient->omtbPvt.handle,
                              inPortParamPtr->cmnInParams.pInPortDef->nPortIndex,
                              inPortParamPtr->pInBuff[i]);

        /* API exit time calculation macro */
        OMTB_OMX_API_EXIT_TIME_CALC("OMX_FreeBuffer");
      }		

      if(OMX_ErrorNone != err)
      {
        OMTB_OmxReturnStatus(err);
        return err;
      }

    } // for(i = 0; i < inPortParamPtr->cmnInParams.pInPortDef
	}
  }
  
  PRINT(PRINT_FUNCTION_NAME, "Leaving <Function , instance #> : <%s , %d>\n",
                              __FUNCTION__, (int)thisClient->omtbPvt.instanceNo);

  return err;
}


/******************************************************************************\
 *      OMTB_ClientFreeOutputResources Function Definition
\******************************************************************************/
/**
 *
 *  @brief    Free the resources allocated for o/p port
 *
 *  @param in:
 *            thisClient: Pointer to OMTB_CLIENT_PRIVATE struct
 *
 *  @return   OMX_ERRORTYPE - OMX std return/error code
 *
 */

OMX_ERRORTYPE OMTB_ClientFreeOutputResources(OMTB_CLIENT_PRIVATE *thisClient)
{
  OMX_ERRORTYPE err = OMX_ErrorNone;
  unsigned int i = 0, port = 0;
  OMX_PARAM_PORTDEFINITIONTYPE param;
  OMTB_CLIENT_OUTPORT_PARAMS *outPortParamPtr = NULL;  
  OMTB_OMX_API_TIMING_VAR_DECL;

  /* validate the function arguments */
  ASSERT(NULL != thisClient);

  PRINT(PRINT_FUNCTION_NAME, "Entering <Function , instance #> : <%s , %d>\n",
                              __FUNCTION__, (int)thisClient->omtbPvt.instanceNo);
  for (port = 0; port < thisClient->omtbPvt.numOutport; port++)
  {								  
    TIMM_OSAL_Memset(&param, 0, sizeof (param));
    OMTB_SetHeader( &param ,sizeof(OMX_PARAM_PORTDEFINITIONTYPE));
    param.nPortIndex = port + thisClient->omtbPvt.startOutportIndex;
    OMX_GetParameter (thisClient->omtbPvt.handle, OMX_IndexParamPortDefinition, &param);
    PRINT(PRINT_DEBUG_MESSAGE, " Output port index of the component, %d\n", (int)param.nPortIndex);
    PRINT(PRINT_DEBUG_MESSAGE, " Number of output buffers needed by the component is , %d\n",
	                                 (int)param.nBufferCountActual);
    PRINT(PRINT_DEBUG_MESSAGE, " Output buffer size needed by the component is , %d\n",
	                                   (int)param.nBufferSize);
	outPortParamPtr = thisClient->outPortParams + port;
	
	if ( OMX_TRUE == param.bEnabled ) {
    /* Ask component to Free output port buffers */
    for(i = 0; i < (int)param.nBufferCountActual;i++)
    {
      PRINT(PRINT_DEBUG_MESSAGE, "Free O/P ports\n");

      PRINT(PRINT_DEBUG_MESSAGE, "Value of Handle is %x\n",
            (unsigned int) thisClient->omtbPvt.handle);
      PRINT(PRINT_DEBUG_MESSAGE, "Port Index is %d\n",
            (unsigned int) outPortParamPtr->cmnOutParams.pOutPortDef->nPortIndex);
      PRINT(PRINT_DEBUG_MESSAGE, "Buff addr is  %x\n",
            (unsigned int) outPortParamPtr->pOutBuff[i]);
      
       /* OMX_FreeBuffer */
      //if (OMX_FALSE == outPortParamPtr->cmnOutParams.flagUseOutBuffer)
	  {  
        /* API entry time calculation macro */
        OMTB_OMX_API_ENTRY_TIME_CALC;

        /* freeing buffers of component output ports */
        err = OMX_FreeBuffer( thisClient->omtbPvt.handle,
                              //outPortParamPtr->cmnOutParams.pOutPortDef->nPortIndex,
							  param.nPortIndex,
                              outPortParamPtr->pOutBuff[i]);

        /* API exit time calculation macro */
        OMTB_OMX_API_EXIT_TIME_CALC("OMX_FreeBuffer");
      }		

      if(OMX_ErrorNone != err)
      {
        OMTB_OmxReturnStatus(err);
        return err;
      }

    } // for(i = 0; i < outPortParamPtr->cmnOutParams.pOutPortDef ...
	}
  }
    PRINT(PRINT_FUNCTION_NAME, "Leaving <Function , instance #> : <%s , %d>\n",
                                __FUNCTION__, (int)thisClient->omtbPvt.instanceNo);

    return err;
}

OMX_ERRORTYPE OMTB_ClientFreeResources(OMTB_CLIENT_PRIVATE *thisClient)
{
  OMX_ERRORTYPE err = OMX_ErrorNone;
  OMTB_OMX_API_TIMING_VAR_DECL;

  /* validate the function arguments */
  ASSERT(NULL != thisClient);

  PRINT(PRINT_FUNCTION_NAME, "Entering <Function , instance #> : <%s , %d>\n",
                              __FUNCTION__, (int)thisClient->omtbPvt.instanceNo);

  /* release input port buffers */
  err = OMTB_ClientFreeInputResources(thisClient);

  if(OMX_ErrorNone != err)
  {
    PRINT(PRINT_ERR_MSG, "Error in Buffer release for i/p port\n");
    OMTB_OmxReturnStatus(err);
  }

  /* release output port buffers */
  err = OMTB_ClientFreeOutputResources(thisClient);

  if(OMX_ErrorNone != err)
  {
    PRINT(PRINT_ERR_MSG, "Error in Buffer release for o/p port\n");
    OMTB_OmxReturnStatus(err);
  }

  PRINT(PRINT_FUNCTION_NAME, "Leaving <Function , instance #> : <%s , %d>\n",
                              __FUNCTION__, (int)thisClient->omtbPvt.instanceNo);

  return err;
}


OMX_ERRORTYPE OMTB_ClientAllocateResources(OMTB_CLIENT_PRIVATE * thisClient)
{

    OMX_ERRORTYPE err = OMX_ErrorNone;
    OMTB_OMX_API_TIMING_VAR_DECL;

    /* validate the function arguments */
    ASSERT(NULL != thisClient);

    PRINT(PRINT_FUNCTION_NAME, "Entering <Function , instance #> : <%s , %d>\n",
          __FUNCTION__, (int) thisClient->omtbPvt.instanceNo);

    /* allocate i/p port buffers */
    err = OMTB_ClientAllocateInputResources(thisClient);

    if (OMX_ErrorNone != err) {
        PRINT(PRINT_ERR_MSG, "Error in Buffer allocation for i/p port\n");
        OMTB_OmxReturnStatus(err);
    }

    /* allocate o/p port buffers */
    err = OMTB_ClientAllocateOutputResources(thisClient);

    if (OMX_ErrorNone != err) {
        PRINT(PRINT_ERR_MSG, "Error in Buffer allocation for o/p port\n");
        OMTB_OmxReturnStatus(err);
    }

    PRINT(PRINT_FUNCTION_NAME, "Leaving <Function , instance #> : <%s , %d>\n",
          __FUNCTION__, (int) thisClient->omtbPvt.instanceNo);

    return err;
}

OMX_ERRORTYPE OMTB_ClientAllocateInputResources(OMTB_CLIENT_PRIVATE *
                                                thisClient)
{

    OMX_ERRORTYPE err = OMX_ErrorNone;
    unsigned int port, i = 0;
    OMX_BUFFERHEADERTYPE *pBuffer = NULL;
    OMX_PARAM_PORTDEFINITIONTYPE param;
    OMTB_CLIENT_INPORT_PARAMS *inPortParamPtr = NULL;
    OMTB_CLIENT_OUTPORT_PARAMS *connPortParamPtr = NULL;
    OMTB_OMX_API_TIMING_VAR_DECL;
    OMX_U8 *pbuf, *hBufHeapPerPort = NULL;
    /* validate the function arguments */
    ASSERT(NULL != thisClient);

    PRINT(PRINT_FUNCTION_NAME, "Entering <Function , instance #> : <%s , %d>\n",
          __FUNCTION__, (int) thisClient->omtbPvt.instanceNo);
    TIMM_OSAL_Memset(&param, 0, sizeof(param));
    OMTB_SetHeader(&param, sizeof(OMX_PARAM_PORTDEFINITIONTYPE));

    for (port = 0; port < thisClient->omtbPvt.numInport; port++) {
        param.nPortIndex = port;
        OMX_GetParameter(thisClient->omtbPvt.handle,
                         OMX_IndexParamPortDefinition, &param);
        PRINT(PRINT_DEBUG_MESSAGE, " Input port index of the component, %d\n",
              (int) param.nPortIndex);
        PRINT(PRINT_DEBUG_MESSAGE,
              " Number of input buffers needed by the component is , %d\n",
              (int) param.nBufferCountActual);
        PRINT(PRINT_DEBUG_MESSAGE,
              " Input buffer size needed by the component is , %d\n",
              (int) param.nBufferSize);
        inPortParamPtr = thisClient->inPortParams + port;

        /* Input port buffer allocation */

        /* !!! TODO check port enable !!! */
        if ( OMX_TRUE == param.bEnabled ) {
          for (i = 0; i < (int) param.nBufferCountActual; i++) {
              /* OMX_AllocateBuffer */
              if (OMX_FALSE == inPortParamPtr->cmnInParams.flagUseInBuffer) {
                  /* API entry time calculation macro */
                  OMTB_OMX_API_ENTRY_TIME_CALC;

                  err = OMX_AllocateBuffer(thisClient->omtbPvt.handle,
                                           &inPortParamPtr->pInBuff[i],
                                           inPortParamPtr->cmnInParams.
                                           pInPortDef->nPortIndex, thisClient,
                                           inPortParamPtr->cmnInParams.
                                           bufferInSize);

                  /* API exit time calculation macro */
                  OMTB_OMX_API_EXIT_TIME_CALC("OMX_AllocateBuffer");
              }
              /* OMX_UseBuffer */
              else {
                  if (inPortParamPtr->connInfo.remotePipe != NULL) {

                      OMTB_CLIENT_PRIVATE *remoteClientPtr =
                          inPortParamPtr->connInfo.remoteClient;
                      connPortParamPtr =
                          remoteClientPtr->outPortParams +
                          (inPortParamPtr->connInfo.remotePort -
                           remoteClientPtr->omtbPvt.startOutportIndex);

                      /* API entry time calculation macro */
                      OMTB_OMX_API_ENTRY_TIME_CALC;


                      err = OMX_UseBuffer(thisClient->omtbPvt.handle,
                                          &pBuffer,
                                          inPortParamPtr->cmnInParams.pInPortDef->
                                          nPortIndex, thisClient,
                                          connPortParamPtr->cmnOutParams.
                                          bufferOutSize,
                                          connPortParamPtr->pOutBuff[i]->pBuffer);

                      inPortParamPtr->pInBuff[i] = pBuffer;

                      /* API exit time calculation macro */
                      OMTB_OMX_API_EXIT_TIME_CALC("OMX_UseBuffer");
                  } else {

                      /* Allocating memory for input port buffer from shared region */
                      /* !!!! TODO !!! SHARE REGION HEAP POINTER ASSIGNMENT */
                      pbuf =
                          (unsigned char *) TIMM_OSAL_MallocExtn(inPortParamPtr->
                                                                 cmnInParams.
                                                                 bufferInSize,
                                                                 (TIMM_OSAL_BOOL)
                                                                 inPortParamPtr->
                                                                 cmnInParams.
                                                                 inBufContiguous,
                                                                 inPortParamPtr->
                                                                 cmnInParams.
                                                                 inBufAlignment,
                                                                 TIMMOSAL_MEM_SEGMENT_EXT,
                                                                 hBufHeapPerPort);

                      if (!pBuffer) {
                          PRINT(PRINT_ERR_MSG,
                                "Error in Buffer allocation for i/p port\n");

                          /* Function to release the resources allocated by component */
                          err = OMTB_ClientFreeResources(thisClient);

                          if (OMX_ErrorNone != err) {
                              OMTB_OmxReturnStatus(err);
                          }

                          err = (OMX_ERRORTYPE) OMTB_INSUFFICIENT_RESOURCES;
                          return err;
                      }
                      err = OMX_UseBuffer(thisClient->omtbPvt.handle,
                                          &pBuffer,
                                          inPortParamPtr->cmnInParams.pInPortDef->
                                          nPortIndex, thisClient,
                                          inPortParamPtr->cmnInParams.
                                          bufferInSize, pbuf);

                      inPortParamPtr->pInBuff[i] = pBuffer;


                  }
              }

              if (OMX_ErrorNone != err) {
                  OMX_ERRORTYPE tempErr = err;
                  OMTB_OmxReturnStatus(err);

                  /* Function to release the resources allocated by component */
                  err = OMTB_ClientFreeResources(thisClient);

                  if (OMX_ErrorNone != err) {
                      OMTB_OmxReturnStatus(err);
                  }

                  return tempErr;
              } else {
                  PRINT(PRINT_DEBUG_MESSAGE,
                        "Buffers allocated successfully for i/p port\n");
              }
          }
       }
    }
    PRINT(PRINT_FUNCTION_NAME, "Leaving <Function , instance #> : <%s , %d>\n",
          __FUNCTION__, (int) thisClient->omtbPvt.instanceNo);

    return err;
}

OMX_ERRORTYPE OMTB_ClientAllocateOutputResources(OMTB_CLIENT_PRIVATE *
                                                 thisClient)
{

    OMX_ERRORTYPE err = OMX_ErrorNone;
    unsigned int port, i = 0;
    OMX_BUFFERHEADERTYPE *pBuffer = NULL;
    OMX_PARAM_PORTDEFINITIONTYPE param;
    OMTB_CLIENT_OUTPORT_PARAMS *outPortParamPtr = NULL;
    OMTB_CLIENT_INPORT_PARAMS *connPortParamPtr = NULL;
    OMTB_OMX_API_TIMING_VAR_DECL;
    OMX_U8 *pbuf, *hBufHeapPerPort = NULL;
    /* validate the function arguments */
    ASSERT(NULL != thisClient);

    PRINT(PRINT_FUNCTION_NAME, "Entering <Function , instance #> : <%s , %d>\n",
          __FUNCTION__, (int) thisClient->omtbPvt.instanceNo);
    TIMM_OSAL_Memset(&param, 0, sizeof(param));
    OMTB_SetHeader(&param, sizeof(OMX_PARAM_PORTDEFINITIONTYPE));

    for (port = 0; port < thisClient->omtbPvt.numOutport; port++) {
        
        param.nPortIndex = port + thisClient->omtbPvt.startOutportIndex;

        OMX_GetParameter(thisClient->omtbPvt.handle,
                         OMX_IndexParamPortDefinition, &param);

        PRINT(PRINT_DEBUG_MESSAGE, " Output port index of the component, %d\n",
              (int) param.nPortIndex);
        PRINT(PRINT_DEBUG_MESSAGE,
              " Number of output buffers needed by the component is , %d\n",
              (int) param.nBufferCountActual);
        PRINT(PRINT_DEBUG_MESSAGE,
              " Output buffer size needed by the component is , %d\n",
              (int) param.nBufferSize);

        outPortParamPtr = thisClient->outPortParams + port;

        /* Output port buffer allocation */

        if ( OMX_TRUE == param.bEnabled ) { 
            for (i = 0; i < (int) param.nBufferCountActual; i++) {
                /* OMX_AllocateBuffer */
                if (OMX_FALSE == outPortParamPtr->cmnOutParams.flagUseOutBuffer) {
                    /* API entry time calculation macro */
                    OMTB_OMX_API_ENTRY_TIME_CALC;

                    err = OMX_AllocateBuffer(thisClient->omtbPvt.handle,
                                             &outPortParamPtr->pOutBuff[i],
                                             outPortParamPtr->cmnOutParams.
                                             pOutPortDef->nPortIndex, thisClient,
                                             outPortParamPtr->cmnOutParams.
                                             bufferOutSize);

                    /* API exit time calculation macro */
                    OMTB_OMX_API_EXIT_TIME_CALC("OMX_AllocateBuffer");
                }
                /* OMX_UseBuffer */
                else {
                    if (outPortParamPtr->connInfo.remotePipe != NULL) {

                        OMTB_CLIENT_PRIVATE *remoteClientPtr =
                            outPortParamPtr->connInfo.remoteClient;
                        connPortParamPtr =
                            remoteClientPtr->inPortParams +
                            outPortParamPtr->connInfo.remotePort;

                        /* API entry time calculation macro */
                        OMTB_OMX_API_ENTRY_TIME_CALC;


                        err = OMX_UseBuffer(thisClient->omtbPvt.handle,
                                            &pBuffer,
                                            outPortParamPtr->cmnOutParams.
                                            pOutPortDef->nPortIndex, thisClient,
                                            connPortParamPtr->cmnInParams.
                                            bufferInSize,
                                            connPortParamPtr->pInBuff[i]->pBuffer);

                        outPortParamPtr->pOutBuff[i] = pBuffer;

                        /* API exit time calculation macro */
                        OMTB_OMX_API_EXIT_TIME_CALC("OMX_UseBuffer");
                    } else {

                        /* Allocating memory for input port buffer from shared region */
                        /* !!!! TODO !!! SHARE REGION HEAP POINTER ASSIGNMENT */
                        pbuf =
                            (unsigned char *) TIMM_OSAL_MallocExtn(outPortParamPtr->
                                                                   cmnOutParams.
                                                                   bufferOutSize,
                                                                   (TIMM_OSAL_BOOL)
                                                                   outPortParamPtr->
                                                                   cmnOutParams.
                                                                   outBufContiguous,
                                                                   outPortParamPtr->
                                                                   cmnOutParams.
                                                                   outBufAlignment,
                                                                   TIMMOSAL_MEM_SEGMENT_EXT,
                                                                   hBufHeapPerPort);

                        if (!pBuffer) {
                            PRINT(PRINT_ERR_MSG,
                                  "Error in Buffer allocation for i/p port\n");

                            /* Function to release the resources allocated by component */
                            err = OMTB_ClientFreeResources(thisClient);

                            if (OMX_ErrorNone != err) {
                                OMTB_OmxReturnStatus(err);
                            }

                            err = (OMX_ERRORTYPE) OMTB_INSUFFICIENT_RESOURCES;
                            return err;
                        }
                        err = OMX_UseBuffer(thisClient->omtbPvt.handle,
                                            &pBuffer,
                                            outPortParamPtr->cmnOutParams.
                                            pOutPortDef->nPortIndex, thisClient,
                                            outPortParamPtr->cmnOutParams.
                                            bufferOutSize, pbuf);

                        outPortParamPtr->pOutBuff[i] = pBuffer;


                    }
                }

                if (OMX_ErrorNone != err) {
                    OMX_ERRORTYPE tempErr = err;
                    OMTB_OmxReturnStatus(err);

                    /* Function to release the resources allocated by component */
                    err = OMTB_ClientFreeResources(thisClient);

                    if (OMX_ErrorNone != err) {
                        OMTB_OmxReturnStatus(err);
                    }

                    return tempErr;
                } else {
                    PRINT(PRINT_DEBUG_MESSAGE,
                          "Buffers allocated successfully for o/p port\n");
                }
            }
        }
    }
    PRINT(PRINT_FUNCTION_NAME, "Leaving <Function , instance #> : <%s , %d>\n",
          __FUNCTION__, (int) thisClient->omtbPvt.instanceNo);

    return err;
}



OMX_ERRORTYPE OMTB_ClientConnectComponents(OMTB_CLIENT_PRIVATE *handleCompPrivA,
                                     unsigned int compAPortOut,
                                     OMTB_CLIENT_PRIVATE *handleCompPrivB,
                                     unsigned int compBPortIn)
{
  OMX_ERRORTYPE err = OMX_ErrorNone;
    OMTB_CLIENT_OUTPORT_PARAMS *outPortParamPtr = NULL;
    OMTB_CLIENT_INPORT_PARAMS *inPortParamPtr = NULL;
   
 
 
  /* update the input port connect structure */
    outPortParamPtr = handleCompPrivA->outPortParams + compAPortOut - handleCompPrivA->omtbPvt.startOutportIndex; 
  
    inPortParamPtr = handleCompPrivB->inPortParams + compBPortIn;
    
    if((inPortParamPtr->cmnInParams.flagUseInBuffer == OMX_FALSE) &&
       (outPortParamPtr->cmnOutParams.flagUseOutBuffer == OMX_FALSE)) {
    
    PRINT(PRINT_FUNCTION_NAME, "Both Ports are supplier <Function , instance #> : <%s , %d>\n",
          __FUNCTION__, (int) handleCompPrivA->omtbPvt.instanceNo);
       
         }
    
    inPortParamPtr->connInfo.remoteClient = handleCompPrivA;
    inPortParamPtr->connInfo.remotePort   = compAPortOut;
    inPortParamPtr->connInfo.remotePipe   =  handleCompPrivA->omtbPvt.localPipe;
    
    
    outPortParamPtr->connInfo.remoteClient = handleCompPrivB;
    outPortParamPtr->connInfo.remotePort   = compBPortIn;
    outPortParamPtr->connInfo.remotePipe   =  handleCompPrivB->omtbPvt.localPipe;
  
  return err;
}
extern OMTB_DATA_THREAD_ARG strmThreadArg[OMTB_MAX_INS];

void OMTB_ClientApiTsk(void *argc, void *threadsArg)
{
  int i,threadRes = TIMM_OSAL_ERR_NONE;
  OMTB_CLIENT_PRIVATE* thisClient = NULL;

  OMTB_OMX_API_TIMING_VAR_DECL;
  OMTB_CLIENT_OUTPORT_PARAMS *outPortParamPtr = NULL;
  OMTB_CLIENT_INPORT_PARAMS *inPortParamPtr = NULL;
  OMX_BOOL fileReadThread = OMX_FALSE, fileWriteThread = OMX_FALSE, compConnThread = OMX_FALSE;
  
  OMX_PARAM_PORTDEFINITIONTYPE param;
    
  /* thread argument validation */
  ASSERT(NULL != threadsArg);

  thisClient = (OMTB_CLIENT_PRIVATE *) threadsArg;

  PRINT(PRINT_MUST, "Entering <Thread , instance #> : <%s , %d>\n",
                     __FUNCTION__, (int)thisClient->omtbPvt.instanceNo);

  TIMM_OSAL_Memset(&param, 0, sizeof(param));
  OMTB_SetHeader(&param, sizeof(OMX_PARAM_PORTDEFINITIONTYPE));
  
  for (i = 0; i<thisClient->omtbPvt.numInport; i++) {
      inPortParamPtr = thisClient->inPortParams +  i;
      param.nPortIndex = i;
      
      OMX_GetParameter(thisClient->omtbPvt.handle,
                         OMX_IndexParamPortDefinition, &param);       
      if ( OMX_TRUE == param.bEnabled ) {
      // check if port is enabled
        if(inPortParamPtr->connInfo.remotePipe == NULL) {
          fileReadThread = OMX_TRUE;
        } 
        else {
          compConnThread = OMX_TRUE;
        }
      }
    }
    
    for (i = 0; i<thisClient->omtbPvt.numOutport; i++) {
      outPortParamPtr = thisClient->outPortParams +  i;
      param.nPortIndex = i + thisClient->omtbPvt.startOutportIndex;
      
      OMX_GetParameter(thisClient->omtbPvt.handle,
                         OMX_IndexParamPortDefinition, &param);        
      if ( OMX_TRUE == param.bEnabled ) {
      // check if port is enabled
        if(outPortParamPtr->connInfo.remotePipe == NULL) {
          fileWriteThread = OMX_TRUE;
        }
        else {
          compConnThread = OMX_TRUE;
        }
      }      
    }
    
   if ( fileReadThread == OMX_TRUE ) {  
  /* Create input data read thread */
  threadRes = TIMM_OSAL_CreateTask(
                    (void *)&thisClient->omtbPvt.inDataStrmThrdId,
					(TIMM_OSAL_TaskProc)thisClient->omtbPvt.inputDataReadTask,
                    0,
                    thisClient, 
                    OMTB_H264_VDEC_TSK_STACK_SIZE,
                    OMTB_H264_VDEC_GROUP_PRIORITY,
                    (signed char*)"H264_VDEC_DATA_IN_TSK");

  if(TIMM_OSAL_ERR_NONE != threadRes)
  {
    PRINT(PRINT_ERR_MSG,
          "Unable to start input data read thread\n");
  }

 }
 if (fileWriteThread == OMX_TRUE ) {
  /* Create output data write thread */
  threadRes = TIMM_OSAL_CreateTask(
                    (void *)&thisClient->omtbPvt.outDataStrmThrdId,
					(TIMM_OSAL_TaskProc)thisClient->omtbPvt.outputDataWriteTask,
                    0,
                    thisClient,
                    OMTB_H264_VDEC_TSK_STACK_SIZE,
                    OMTB_H264_VDEC_GROUP_PRIORITY,
                    (signed char*)"OMTB_DATA_OUT_TSK");

  if(TIMM_OSAL_ERR_NONE != threadRes)              
  {
    PRINT(PRINT_ERR_MSG,
          "Unable to start output data write thread\n");
  }
  }

 if(compConnThread == OMX_TRUE) {
  /* Create output data write thread */
  threadRes = TIMM_OSAL_CreateTask(
                    (void *)&thisClient->omtbPvt.connDataStrmThrdId,
                    (TIMM_OSAL_TaskProc)OMTB_Client_ConnIn_ConnOut_Tsk,
                    0,
                    thisClient,
                    OMTB_H264_VDEC_TSK_STACK_SIZE,
                    OMTB_H264_VDEC_GROUP_PRIORITY,
                    (signed char*)"OMTB_DATA_OUT_TSK");

  if(TIMM_OSAL_ERR_NONE != threadRes)              
  {
    PRINT(PRINT_ERR_MSG,
          "Unable to start ConnIn ConnOut thread\n");
  }
 
 
   }
   
  //TIMM_OSAL_SemaphoreObtain(thisClient->omtbPvt.eofSem, TIMM_OSAL_SUSPEND);
  
  /* Wait till the processing is completed by the child threads*/  
  if (fileReadThread == OMX_TRUE )
  {
    TIMM_OSAL_SemaphoreObtain(thisClient->omtbPvt.inputDataReadThrExit, TIMM_OSAL_SUSPEND); 
  }

  if (fileWriteThread == OMX_TRUE )
  {
    TIMM_OSAL_SemaphoreObtain(thisClient->omtbPvt.outputDataWriteThrExit, TIMM_OSAL_SUSPEND);   
  }   

  if(compConnThread == OMX_TRUE)
  {
    TIMM_OSAL_SemaphoreObtain(thisClient->omtbPvt.connDataStrmThrExit, TIMM_OSAL_SUSPEND);   
  }

  /* reset the flag used to determine whether Func/API thread is created */
  thisClient->omtbPvt.flagThrCreated = OMX_FALSE;
  
  thisClient->omtbPvt.connDataStrmThrdId = NULL;
  thisClient->omtbPvt.outDataStrmThrdId = NULL;
  thisClient->omtbPvt.inDataStrmThrdId = NULL;

  PRINT(PRINT_MUST, "Leaving <Thread , instance #> : <%s , %d>\n",
                     __FUNCTION__, (int)thisClient->omtbPvt.instanceNo);

  /* exit the thread */
  TIMM_OSAL_ExitTask(
      thisClient->omtbPvt.apiThreadId,
      NULL);
}

OmtbRet OMTB_AllocateMemory(OMTB_CLIENT_PRIVATE *thisClient, OMTB_BASIC_CONFIG_PARAMS *pBasicConfig)
{
  OmtbRet err = OMTB_SUCCESS;
  unsigned int retVal = TIMM_OSAL_ERR_NONE;
  unsigned int i = 0;
  OMTB_CLIENT_INPORT_PARAMS *inPortParamsPtr = NULL;
  OMTB_CLIENT_OUTPORT_PARAMS *outPortParamsPtr = NULL;
  unsigned int totalBuffers = 0;
  
  /* validate the function arguments */
  ASSERT(NULL != thisClient);

  PRINT(PRINT_FUNCTION_NAME, "Entering <Function , instance #> : <%s , %d>\n",
                              __FUNCTION__, (int)thisClient->omtbPvt.instanceNo);

  /* Allocating memory for callback structure */
  thisClient->omtbPvt.cb=(OMX_CALLBACKTYPE*)
                    TIMM_OSAL_Malloc( sizeof(OMX_CALLBACKTYPE),
                                      TIMM_OSAL_TRUE,
                                      0,
                                      TIMMOSAL_MEM_SEGMENT_EXT);

  if (!thisClient->omtbPvt.cb)
  {
    PRINT(PRINT_ERR_MSG, "Callback structure memory allocation failed\n");
    err = OMTB_INSUFFICIENT_RESOURCES;
	OMTB_FreeMemory(thisClient);
    return err;	 	
  }

  if(0 != thisClient->omtbPvt.numInport)
  {
    /* Allocate memory for input port param */
    thisClient->inPortParams =   (OMTB_CLIENT_INPORT_PARAMS *)
                      TIMM_OSAL_Malloc( sizeof(OMTB_CLIENT_INPORT_PARAMS) * 
                                        thisClient->omtbPvt.numInport,
                                        TIMM_OSAL_TRUE,
                                        0,
                                        TIMMOSAL_MEM_SEGMENT_EXT);
    if (!thisClient->inPortParams)
    {
      PRINT(PRINT_ERR_MSG, "Input port memory allocation failed\n");
      err = OMTB_INSUFFICIENT_RESOURCES;
	  OMTB_FreeMemory(thisClient);
      return err;	 	
    }
    else
    {  
      TIMM_OSAL_Memset(thisClient->inPortParams, 0, sizeof (OMTB_CLIENT_INPORT_PARAMS)* 
                                                        thisClient->omtbPvt.numInport);
    }													  
  }	

  if(0 != thisClient->omtbPvt.numOutport)
  {
    /* Allocate memory for output port params */
    thisClient->outPortParams = (OMTB_CLIENT_OUTPORT_PARAMS *)
                      TIMM_OSAL_Malloc( sizeof(OMTB_CLIENT_OUTPORT_PARAMS) * 
                                        thisClient->omtbPvt.numOutport,
                                        TIMM_OSAL_TRUE,
                                        0,
                                        TIMMOSAL_MEM_SEGMENT_EXT);
    if (!thisClient->outPortParams)
    {
      PRINT(PRINT_ERR_MSG, "Output port memory allocation failed\n");
      err = OMTB_INSUFFICIENT_RESOURCES;
	  OMTB_FreeMemory(thisClient);
      return err;	 	
    }
    else
    {
      TIMM_OSAL_Memset(thisClient->outPortParams, 0, sizeof (OMTB_CLIENT_OUTPORT_PARAMS)*
                                                     thisClient->omtbPvt.numOutport);
    }
  }	

  for (i =0 ; i < thisClient->omtbPvt.numInport ; i++)
  {
    inPortParamsPtr = thisClient->inPortParams + i; 
    
	/* Allocating memory for input port definition structure */
    inPortParamsPtr->cmnInParams.pInPortDef = (OMX_PARAM_PORTDEFINITIONTYPE*)
                    TIMM_OSAL_Malloc( sizeof(OMX_PARAM_PORTDEFINITIONTYPE),
                                      TIMM_OSAL_TRUE,
                                      0,
                                      TIMMOSAL_MEM_SEGMENT_EXT);

    if (!inPortParamsPtr->cmnInParams.pInPortDef)
    {
      PRINT(PRINT_ERR_MSG, "Input port struct memory allocation failed\n");
      err = OMTB_INSUFFICIENT_RESOURCES;
	  OMTB_FreeMemory(thisClient);
      return err;	 	  
    }

    /* Create input pipe for input buffers */
    retVal = TIMM_OSAL_CreatePipe(
                      &(inPortParamsPtr->cmnInParams.ipBufPipe),
                      ((sizeof(OMX_BUFFERHEADERTYPE*)) *
                      (pBasicConfig->numInBuf + 4)),
                      sizeof(OMX_BUFFERHEADERTYPE*), OMX_TRUE );

    if (TIMM_OSAL_ERR_NONE != retVal)
    {
      PRINT(PRINT_ERR_MSG, "TIMM_OSAL_CreatePipe failed to open\n");
      err = OMTB_INSUFFICIENT_RESOURCES;
	  OMTB_FreeMemory(thisClient);
      return err;	  
    }	
	totalBuffers +=  pBasicConfig->numInBuf;	
  }	

  for (i =0 ; i < thisClient->omtbPvt.numOutport ; i++)
  {
    outPortParamsPtr = thisClient->outPortParams + i; 
	
    /* Allocating memory for output port definition structure */
    outPortParamsPtr->cmnOutParams.pOutPortDef = (OMX_PARAM_PORTDEFINITIONTYPE*)
                      TIMM_OSAL_Malloc(sizeof(OMX_PARAM_PORTDEFINITIONTYPE),
                                              TIMM_OSAL_TRUE,
                                              0,
                                              TIMMOSAL_MEM_SEGMENT_EXT);

    if (!outPortParamsPtr->cmnOutParams.pOutPortDef)
    {
      PRINT(PRINT_ERR_MSG, "Output port struct memory allocation failed\n");
      err = OMTB_INSUFFICIENT_RESOURCES;
	  OMTB_FreeMemory(thisClient);
      return err;	 	  
    }


    /* Create output pipe for output buffers */
    retVal = TIMM_OSAL_CreatePipe(
                      &(outPortParamsPtr->cmnOutParams.opBufPipe),
                      ((sizeof(OMX_BUFFERHEADERTYPE*)) *
                      (pBasicConfig->numOutBuf + 4 )), 
                      sizeof(OMX_BUFFERHEADERTYPE*), OMX_TRUE );

    if (TIMM_OSAL_ERR_NONE != retVal)
    {
      PRINT(PRINT_ERR_MSG, "TIMM_OSAL_CreatePipe failed to open\n");
      err = OMTB_INSUFFICIENT_RESOURCES;
	  OMTB_FreeMemory(thisClient);
      return err;	 	  
    }	
	  
	totalBuffers += pBasicConfig->numOutBuf;  		
  }	

  /* Create input pipe for input buffers */
  retVal = TIMM_OSAL_CreatePipe(
                    &(thisClient->omtbPvt.localPipe),
                    ((sizeof(OMTB_CLIENT_PIPE_MSG)) *
                    totalBuffers), 					   
                    sizeof(OMTB_CLIENT_PIPE_MSG), OMX_TRUE );
 
  if (TIMM_OSAL_ERR_NONE != retVal)
  {
    PRINT(PRINT_ERR_MSG, "TIMM_OSAL_CreatePipe failed to open\n");
    err = (OMX_ERRORTYPE)OMTB_INSUFFICIENT_RESOURCES;
	OMTB_FreeMemory(thisClient);
    return err;	 	
  }


  /* Create a pipe, used to put buffer pointer after the vdec has consumed the buffer*/
  if((0 != thisClient->omtbPvt.numFileInBufs) && (0 != thisClient->omtbPvt.numInport))
  {
    retVal = TIMM_OSAL_CreatePipe(
                      &(thisClient->inPortParams->cmnInParams.fileIpBufPipe),
                      ((sizeof(OMTB_CLIENT_FILEIO_PARAMS)) * (thisClient->omtbPvt.numFileInBufs + 1 )),
                       sizeof(OMTB_CLIENT_FILEIO_PARAMS),
			       	   OMX_TRUE);

    if (TIMM_OSAL_ERR_NONE != retVal)
    {
      PRINT(PRINT_ERR_MSG, "TIMM_OSAL_CreatePipe failed to open\n");
      err = OMTB_INSUFFICIENT_RESOURCES;
	  OMTB_FreeMemory(thisClient);
      return err;	 	
    }

    /* Create a pipe, used to put buffer pointer after fileRead to the buffer*/
    retVal = TIMM_OSAL_CreatePipe(
                      &(thisClient->inPortParams->cmnInParams.fileOpBufPipe),
                      ((sizeof(OMTB_CLIENT_FILEIO_PARAMS)) *  (thisClient->omtbPvt.numFileInBufs + 1)),
                       sizeof(OMTB_CLIENT_FILEIO_PARAMS),
			  		   OMX_TRUE);

    if (TIMM_OSAL_ERR_NONE != retVal)
    {
      PRINT(PRINT_ERR_MSG, "TIMM_OSAL_CreatePipe failed to open\n");
      err = OMTB_INSUFFICIENT_RESOURCES;
	  OMTB_FreeMemory(thisClient);
      return err;	 	
    }  
 
    /* Allocating memory for file read */  
    for(i = 0; i < thisClient->omtbPvt.numFileInBufs; i++)
    {
      thisClient->inPortParams->sFileIOBuff[i].pBuff = 
                      (unsigned char*)TIMM_OSAL_Malloc(
                       thisClient->omtbPvt.readSize,
                       TIMM_OSAL_TRUE,
                       0,
                       TIMMOSAL_MEM_SEGMENT_EXT);

      if (!thisClient->inPortParams->sFileIOBuff[i].pBuff)
      {
        PRINT(PRINT_ERR_MSG, "component specific memory allocation failed\n");
        err = OMTB_INSUFFICIENT_RESOURCES;
	    OMTB_FreeMemory(thisClient);
        return err;	 	  
      }					
    }	  
  } 

  if((0 != thisClient->omtbPvt.numFileOutBufs) && (0 != thisClient->omtbPvt.numOutport))  
  {  

    /* Create a pipe, used to put buffer pointer after the vdec has consumed the buffer*/
    retVal = TIMM_OSAL_CreatePipe(
                      &(thisClient->outPortParams->cmnOutParams.fileIpBufPipe),
                      ((sizeof(OMTB_CLIENT_FILEIO_PARAMS)) * thisClient->omtbPvt.numFileOutBufs),
                       sizeof(OMTB_CLIENT_FILEIO_PARAMS),
			  		   OMX_TRUE);

    if (TIMM_OSAL_ERR_NONE != retVal)
    {
      PRINT(PRINT_ERR_MSG, "TIMM_OSAL_CreatePipe failed to open\n");
      err = OMTB_INSUFFICIENT_RESOURCES;
	  OMTB_FreeMemory(thisClient);
      return err;	 	
    }
 
    /* Create a pipe, used to put buffer pointer after fileRead to the buffer*/
    retVal = TIMM_OSAL_CreatePipe(
                      &(thisClient->outPortParams->cmnOutParams.fileOpBufPipe),
                      ((sizeof(OMTB_CLIENT_FILEIO_PARAMS)) *  thisClient->omtbPvt.numFileOutBufs),
                       sizeof(OMTB_CLIENT_FILEIO_PARAMS),
			      	   OMX_TRUE);

    if (TIMM_OSAL_ERR_NONE != retVal)
    {
      PRINT(PRINT_ERR_MSG, "TIMM_OSAL_CreatePipe failed to open\n");
      err = OMTB_INSUFFICIENT_RESOURCES;
	  OMTB_FreeMemory(thisClient);
      return err;	 	
    }  
  
   /* Allocating memory for file write */  
    for(i = 0; i < thisClient->omtbPvt.numFileOutBufs; i++)
    {
      thisClient->outPortParams->sFileIOBuff[i].pBuff = 
                      (unsigned char*)TIMM_OSAL_Malloc(
                       thisClient->omtbPvt.writeSize,
                       TIMM_OSAL_TRUE,
                       0,
                       TIMMOSAL_MEM_SEGMENT_EXT);

      if (!thisClient->outPortParams->sFileIOBuff[i].pBuff)
      {
        PRINT(PRINT_ERR_MSG, "component specific memory allocation failed\n");
        err = OMTB_INSUFFICIENT_RESOURCES;
	    OMTB_FreeMemory(thisClient);
        return err;	 	  
      }					
    } 
  }

 
  /* Initialize the semaphores */
  TIMM_OSAL_SemaphoreCreate(&thisClient->omtbPvt.eventSem, 0);

  TIMM_OSAL_SemaphoreCreate(&thisClient->omtbPvt.fileReadThrExit, 0);  
  TIMM_OSAL_SemaphoreCreate(&thisClient->omtbPvt.fileWriteThrExit, 0);  
  TIMM_OSAL_SemaphoreCreate(&thisClient->omtbPvt.connDataStrmThrExit, 0);  
  TIMM_OSAL_SemaphoreCreate(&thisClient->omtbPvt.inputDataReadThrExit, 0);
  TIMM_OSAL_SemaphoreCreate(&thisClient->omtbPvt.outputDataWriteThrExit, 0);
  TIMM_OSAL_SemaphoreCreate(&thisClient->omtbPvt.eofSem, 0);  
  
  //TIMM_OSAL_SemaphoreCreate(&thisClient->inPortParams->cmnInParams.inputDataReady, 0);
  //TIMM_OSAL_SemaphoreCreate(&thisClient->outPortParams->cmnOutParams.outputDataReady, 0);

  PRINT(PRINT_FUNCTION_NAME, "Leaving <Function , instance #> : <%s , %d>\n",
                              __FUNCTION__, (int)thisClient->omtbPvt.instanceNo);				
  return err;
}

OMX_ERRORTYPE OMTB_GetHandle(
  char *componentRequested,
  unsigned int instance,
  unsigned int template)
{
  OMX_ERRORTYPE err = OMX_ErrorNone;

  char inputFile[OMTB_MAX_LEN]  = {"\0"};
  char outputFile[OMTB_MAX_LEN] = {"\0"};
  OMTB_CLIENT_PRIVATE* thisClient = NULL;
  OMTB_BASIC_CONFIG_PARAMS *pBasicConfig = NULL;
  unsigned int nSize = 0;
  unsigned int i = 0;
  OMTB_OMX_API_TIMING_VAR_DECL;
  TIMM_OSAL_ERRORTYPE retVal;
  OMTB_ClassInitPtr fpClassInit = NULL;
  
  OMTB_CLIENT_INPORT_PARAMS *inPortParamsPtr = NULL;
  OMTB_CLIENT_OUTPORT_PARAMS *outPortParamsPtr = NULL;
  
  /* validate the function arguments */
  ASSERT(NULL != componentRequested);

  PRINT(PRINT_FUNCTION_NAME, "Entering <Function , instance #> : <%s , %d>\n",
                              __FUNCTION__, (int)instance);

  pBasicConfig = OMTB_GetCompBasicConfigPtr(componentRequested, template);
  
  /*Get the size for app pvt*/
  nSize = OMTB_GetSizeCompPrivStruct(componentRequested);
  
 /* Allocate memory for application private data */
  thisClient = (OMTB_CLIENT_PRIVATE *) TIMM_OSAL_Malloc( nSize,
                                                         TIMM_OSAL_TRUE,
                                                         0, 
                                                         TIMMOSAL_MEM_SEGMENT_EXT);
  if (!thisClient)
  {
    PRINT(PRINT_ERR_MSG, "Error allocating thisClient structure \n");
    err = (OMX_ERRORTYPE)OMTB_INSUFFICIENT_RESOURCES;
    return err;
  }

  /* Update the application instance management structure with app pvt data
     structure pointer */
  OMTB_SetCompPrivHandle(componentRequested, instance, (void*)thisClient);
  TIMM_OSAL_Memset(thisClient, 0, nSize);

  thisClient->omtbPvt.instanceNo = instance;
  thisClient->omtbPvt.templateNo = template;
  
  thisClient->omtbPvt.prevState  = OMX_StateInvalid;  
  thisClient->omtbPvt.currState  = OMX_StateInvalid;

  /* call the component specific initialization function */
  fpClassInit = OMTB_GetClassInitFuncPtr(componentRequested);	
  err = fpClassInit(thisClient);

  if(OMTB_SUCCESS != err)
  {
    PRINT(PRINT_ERR_MSG, "Unable to allocate memory for component specific structure\n");
    err = (OMX_ERRORTYPE)OMTB_INSUFFICIENT_RESOURCES;
   OMTB_FreeMemory(thisClient);
    return err;
  }
  
  /*Function to allocate memory for app pvt struct members*/
  err = (OMX_ERRORTYPE)OMTB_AllocateMemory((OMTB_CLIENT_PRIVATE*)thisClient, pBasicConfig);

  if(OMTB_SUCCESS != err)
  {
    PRINT(PRINT_ERR_MSG, "Unable to allocate memory for app pvt structure\n");
    err = (OMX_ERRORTYPE)OMTB_INSUFFICIENT_RESOURCES;
    OMTB_FreeMemory(thisClient);
    return err;
  }
    
  /* Make local copy of input, output and framesize file names */
  strcpy(outputFile, pBasicConfig->outputFile);
  strcpy(inputFile,  pBasicConfig->inputFile);
  strcpy(thisClient->omtbPvt.compName,  pBasicConfig->compName);

  PRINT(PRINT_DEBUG_MESSAGE, "Component Name is:%s\n",
                              thisClient->omtbPvt.compName);
  PRINT(PRINT_DEBUG_MESSAGE, "Input File is:%s\n", inputFile);
  PRINT(PRINT_DEBUG_MESSAGE, "Output File is:%s\n", outputFile);

  for (i =0 ; i < thisClient->omtbPvt.numInport ; i++)
  {
    inPortParamsPtr = thisClient->inPortParams + i;    
    																																													
    /* Data output mode selection - File/Driver */
    inPortParamsPtr->cmnInParams.dataInPutMode = pBasicConfig->dataInPutMode;
    /* Buffer allocation mode - OMX_UseBuffer or OMX_AllocateBuffer */
    inPortParamsPtr->cmnInParams.flagUseInBuffer = pBasicConfig->flagUseInBuffer;
  
    inPortParamsPtr->cmnInParams.inBufSzFlag = pBasicConfig->inBufSzFlag;
    inPortParamsPtr->cmnInParams.inBufAlignment = pBasicConfig->inBufAlignment;
    inPortParamsPtr->cmnInParams.inBufContiguous = pBasicConfig->inBufContiguous;
    
	/* no of i/p buffers */
    inPortParamsPtr->cmnInParams.numInBuf  = pBasicConfig->numInBuf;
	
	/* Flag to reset the file pointer */
	inPortParamsPtr->cmnInParams.fileReset = pBasicConfig->fileReset;

    if(OMTB_FILE == inPortParamsPtr->cmnInParams.dataInPutMode )
    {
      /* Open the input file */
      inPortParamsPtr->cmnInParams.fin = fopen(inputFile, "rb");
      if(NULL == inPortParamsPtr->cmnInParams.fin)
      {
        PRINT(PRINT_ERR_MSG, "Error in opening input file %s\n",inputFile);
        err = (OMX_ERRORTYPE)OMTB_INSUFFICIENT_RESOURCES;
        OMTB_FreeMemory(thisClient);
        return err;
      }
    }	
    else if(OMTB_DRIVER == inPortParamsPtr->cmnInParams.dataInPutMode)
    {
      /* do nothing */
    }
  
    /* Initialize the counter to get frame size from input data read thread */
    inPortParamsPtr->frameCount = 0;

    inPortParamsPtr->nWidth = pBasicConfig->frameWidth;
    inPortParamsPtr->nHeight = pBasicConfig->frameHeight;
   
    inPortParamsPtr->colorFormat = pBasicConfig->inColorFormat;
    
	/* Initialize the EOS flag */
    inPortParamsPtr->cmnInParams.flagInputEos = OMX_FALSE;
    inPortParamsPtr->cmnInParams.stopFileRead = OMX_FALSE; 
  }

  for (i =0 ; i < thisClient->omtbPvt.numOutport ; i++)
  {
    outPortParamsPtr = thisClient->outPortParams + i; 
    
    /* Data output mode selection - File/Driver */
    outPortParamsPtr->cmnOutParams.dataOutPutMode = pBasicConfig->dataOutPutMode;
    
	/* Buffer allocation mode - OMX_UseBuffer or OMX_AllocateBuffer */
    outPortParamsPtr->cmnOutParams.flagUseOutBuffer = pBasicConfig->flagUseOutBuffer;
    outPortParamsPtr->cmnOutParams.outBufSzFlag = pBasicConfig->outBufSzFlag;
    outPortParamsPtr->cmnOutParams.outBufAlignment = pBasicConfig->outBufAlignment;
    outPortParamsPtr->cmnOutParams.outBufContiguous = pBasicConfig->outBufContiguous;
  
    /* no of o/p buffers */											
    outPortParamsPtr->cmnOutParams.numOutBuf = pBasicConfig->numOutBuf;

    if(OMTB_FILE == outPortParamsPtr->cmnOutParams.dataOutPutMode )
    {
      /* Open the output file */
      outPortParamsPtr->cmnOutParams.fout = fopen(outputFile, "wb");
      if(NULL == outPortParamsPtr->cmnOutParams.fout)
      {
        PRINT(PRINT_ERR_MSG, "Error opening output file %s\n",outputFile);
        err = (OMX_ERRORTYPE)OMTB_INSUFFICIENT_RESOURCES;
        OMTB_FreeMemory(thisClient);
        return err;
      }
    }
    else if(OMTB_DRIVER == outPortParamsPtr->cmnOutParams.dataOutPutMode)
    {
     /* do nothing */ 
    }
    																																												
    outPortParamsPtr->nWidth = pBasicConfig->frameWidth;
    outPortParamsPtr->nHeight = pBasicConfig->frameHeight;
    outPortParamsPtr->colorFormat = pBasicConfig->colorFormat;
    outPortParamsPtr->cmnOutParams.flagEos = OMX_FALSE;
  }
   
  /*Assign the callbacks*/
  *thisClient->omtbPvt.cb = OMTB_Callback;
  /* Initialize the flag used to determine whether Func/API thread is created */
  thisClient->omtbPvt.flagThrCreated = OMX_FALSE;
  
  /*Component/class specific allocations */ 
  err = (OMX_ERRORTYPE)thisClient->omtbPvt.fpSetBufferSize((void*)thisClient);
  
  if(OMTB_SUCCESS != err)
  {
    PRINT(PRINT_ERR_MSG, "Unable to allocate memory for app pvt structure\n");
    err = (OMX_ERRORTYPE)OMTB_INSUFFICIENT_RESOURCES;
    OMTB_FreeMemory(thisClient);
    return err;
  }
  
  /* API entry time calculation macro */
  OMTB_OMX_API_ENTRY_TIME_CALC;

  /* get component handle */
  err = OMX_GetHandle(&thisClient->omtbPvt.handle,
                      (OMX_STRING)thisClient->omtbPvt.compName,
                      thisClient,
                      thisClient->omtbPvt.cb);

  /* API exit time calculation macro */
  OMTB_OMX_API_EXIT_TIME_CALC("OMX_GetHandle");

  if(OMX_ErrorNone != err)
  {
    PRINT(PRINT_ERR_MSG, "No component named \"%s\" found\n",
                          thisClient->omtbPvt.compName);
    OMTB_OmxReturnStatus(err);
    OMTB_FreeMemory(thisClient);
    return err;
  }
  else
  {
    /* Update the application instance management strucutre with handle */
	OMTB_SetCompHandle(componentRequested, instance, thisClient->omtbPvt.handle);

    PRINT(PRINT_MUST,
          "\r      \n\nOMTB-%s Instance #: %d\n\n", componentRequested, instance);
    PRINT(PRINT_SIMPLE_MESSAGE, "Component Handle Available\n");
  }
   for (i =0 ; i < thisClient->omtbPvt.numOutport ; i++) {
    outPortParamsPtr = thisClient->outPortParams + i; 

  PRINT(PRINT_DEBUG_MESSAGE, "\nbufferOutSize: %d\n",\
        (int)outPortParamsPtr->cmnOutParams.bufferOutSize);
  }
  
  PRINT(PRINT_FUNCTION_NAME, "Leaving <Function , instance #> : <%s , %d>\n",
                              __FUNCTION__, (int)thisClient->omtbPvt.instanceNo);

  return err;
}


OMX_ERRORTYPE OMTB_ClientSendCmdEXIT(OMTB_CLIENT_PRIVATE *thisClient, void *inPipe, void *opPipe)
{
  OMX_ERRORTYPE err = OMX_ErrorNone;
  OMTB_CLIENT_FILEIO_PARAMS pipeMsg;  
  TIMM_OSAL_ERRORTYPE retVal = TIMM_OSAL_ERR_NONE;
  unsigned int actualSize = 0;
#if 0    
  /* Read a message from pipe */
  TIMM_OSAL_ReadFromPipe (inPipe,
                          &pipeMsg,
                          sizeof(OMTB_CLIENT_FILEIO_PARAMS),
                          (void*) &actualSize,
                          TIMM_OSAL_SUSPEND );    
#endif	
						
  pipeMsg.pBuff = NULL;
  pipeMsg.nOffset = 0;
  pipeMsg.buffLen = 0;
  pipeMsg.cmd = OMTB_CLIENT_PIPE_CMD_EXIT;	
	
  /* Write to the pipe */
  TIMM_OSAL_WriteToPipe (opPipe,
                         &pipeMsg,
                         sizeof(OMTB_CLIENT_FILEIO_PARAMS),
                         TIMM_OSAL_SUSPEND );						 

  if (TIMM_OSAL_ERR_NONE != retVal) {
      PRINT(PRINT_ERR_MSG, "Error writing to remote Pipe!\n");
      err = OMX_ErrorNotReady;
      return err;
  }
	
  return (err);
}	
/******************************************************************************\
 *      OMTB_UseInitialInputResources Function Definition
\******************************************************************************/
/**
 *
 *  @brief    Tells component to empty the initial buffers.
 *
 *  @param in:
 *            h264VdecClient: Pointer to appPrivateType structure
 *
 *  @param Out:
 *            None
 *
 *  @return   OMX_ERRORTYPE - OMX std return/error code
 *
 */

OMX_ERRORTYPE OMTB_UseInitialInputResources(
  OMTB_CLIENT_PRIVATE* thisClient)
{
  OMX_ERRORTYPE err = OMX_ErrorNone;
  unsigned int i = 0;
  int dataRead = 0;
  unsigned int actualSize = 0;  
  OMTB_CLIENT_FILEIO_PARAMS pipeMsg;   
  unsigned int retVal = TIMM_OSAL_ERR_NONE;   
  OMTB_OMX_API_TIMING_VAR_DECL;

  /* validate the function arguments */
  ASSERT(NULL != thisClient);

  PRINT(PRINT_FUNCTION_NAME, "Entering <Function , instance #> : <%s , %d>\n",
                              __FUNCTION__, (int)thisClient->omtbPvt.instanceNo);


  /* Give input buffers to component which is limited by no of input buffers
     available. Rest of the data will be read on the callback from input data
     read thread */
  for(i = 0; i < thisClient->inPortParams->cmnInParams.pInPortDef->nBufferCountActual;
      i++)
  {
    /* Memcpy: DDR -> DDR Copy */
    if(OMTB_H264_VDEC_CLASS == thisClient->omtbPvt.eClassType)
	{
	  /* Fill the data in the empty buffer, the buffer will have one complete frame */
      dataRead = H264VDEC_FillData(thisClient, thisClient->inPortParams->pInBuff[i], 0);						
	}
    else if(OMTB_VDEC_CLASS == thisClient->omtbPvt.eClassType)
	{
	  /* TODO: Need to identify the fill data function call based on the video decoder type */
	  /* Fill the data in the empty buffer, the buffer will have one complete frame */
      dataRead = MPEG2VDEC_FillData(thisClient, thisClient->inPortParams->pInBuff[i], 0);						
	}	
    else
    {
       /* Read the buffer poniter from pipe */
       TIMM_OSAL_ReadFromPipe( thisClient->inPortParams->cmnInParams.fileOpBufPipe,
                               &pipeMsg,
                               sizeof(OMTB_CLIENT_FILEIO_PARAMS),
                               (void*) &actualSize,
                               TIMM_OSAL_SUSPEND );	
							   
       /* Fill data in i/p Buffer */
      /* memcpy: DDR to DDR Copy */
      retVal = TIMM_OSAL_Memcpy(thisClient->inPortParams->pInBuff[i]->pBuffer,  (pipeMsg.pBuff + pipeMsg.nOffset), pipeMsg.buffLen);

      /* Update the buffer header with buffer filled length */
      thisClient->inPortParams->pInBuff[i]->nFilledLen = pipeMsg.buffLen;
      if (TIMM_OSAL_ERR_NONE != retVal)
      {
        PRINT(PRINT_ERR_MSG, "TIMM_OSAL_Memcpy failed\n");
        break;
      }	  
	  
	  dataRead = pipeMsg.buffLen;

   	  /* Write to the pipe of File Read Thread */
      TIMM_OSAL_WriteToPipe( thisClient->inPortParams->cmnInParams.fileIpBufPipe,
                             &pipeMsg,
                             sizeof(OMTB_CLIENT_FILEIO_PARAMS),
                             TIMM_OSAL_SUSPEND );		  
	}
	
	/* Exit the loop if no data available */    
    if(dataRead <= -1)
    {
      PRINT(PRINT_MUST, "No data read\n");	  	
  	  break;
    } 	
	
    PRINT(PRINT_DEBUG_MESSAGE, "Empty first  buffer %x\n",
          (int)thisClient->inPortParams->pInBuff[i]->pBuffer);

    /* API entry time calculation macro */
    OMTB_OMX_API_ENTRY_TIME_CALC;

    /* Pass the input buffer to the component */
  
	err = OMX_EmptyThisBuffer(
                        thisClient->omtbPvt.handle,
                        thisClient->inPortParams->pInBuff[i]);

    /* API exit time calculation macro */
    OMTB_OMX_API_EXIT_TIME_CALC("OMX_EmptyThisBuffer");

    if(OMX_ErrorNone != err)
    {
      OMTB_OmxReturnStatus(err);
      return err;
    }
  }
  
  PRINT(PRINT_FUNCTION_NAME, "Leaving <Function , instance #> : <%s , %d>\n",
                              __FUNCTION__, (int)thisClient->omtbPvt.instanceNo);

  return err;
}


/******************************************************************************\
 *      OMTB_FileRead Thread Definition
\******************************************************************************/
/**
 *
 *  @brief    This is a File Read thread which reads data from input file
 *
 *  @param in:
 *            void * - Thread args count
 *
 *            void *threadsArg - Pointer to thread arg structure
 *
 *  @return   None
 *
 */

void OMTB_FileRead(void *argc, void *threadsArg)
{
  unsigned int actualSize = 0,dataRead = 0;
  OMTB_CLIENT_PRIVATE* thisClient = NULL;
  OMTB_CLIENT_FILEIO_PARAMS pipeMsg;
  unsigned int i = 0;
  unsigned int readSize = 0;
  unsigned int numRemaining = 0;
  unsigned int putPipeMessage = OMX_FALSE;
  OMTB_OMX_API_TIMING_VAR_DECL;

  /* thread argument validation */
  ASSERT(NULL != threadsArg);
  thisClient = threadsArg; 

  PRINT(PRINT_MUST, "Entering <Thread , instance #> : <%s , %d>\n",
                     __FUNCTION__, (int)thisClient->omtbPvt.instanceNo);
  
  thisClient->inPortParams->cmnInParams.stopFileRead = OMX_FALSE;  
  
  /* Initially put all the buffers into the pipe */
  for(i = 0; i < thisClient->omtbPvt.numFileInBufs; i++)
  {
    /* write the buffers into the pipe */
    TIMM_OSAL_WriteToPipe (thisClient->inPortParams->cmnInParams.fileIpBufPipe,
                           &thisClient->inPortParams->sFileIOBuff[i],
                           sizeof(OMTB_CLIENT_FILEIO_PARAMS),
                           TIMM_OSAL_SUSPEND );  
  }
  
  /* Set the read buffer size */
  if(OMTB_H264_VDEC_CLASS == thisClient->omtbPvt.eClassType)
  {
    readSize = H264PARSER_READSIZE;
  }
  else if(OMTB_VDEC_CLASS == thisClient->omtbPvt.eClassType)
  {
	/* TODO: Need to identify the size based on the video decoder type */  
    readSize = MPEG2PARSER_READSIZE;
  }
  else
  {
    readSize = thisClient->inPortParams->cmnInParams.bufferInSize;
  }

  /* Break the loop and deleted the thread if the component moves to idle state */  
  /* do not read the data if the component is not in exec state, exit the thread */
  while(OMX_TRUE != thisClient->inPortParams->cmnInParams.stopFileRead)
  {
    /* Read empty buffer pointer from the pipe of file io */
    TIMM_OSAL_ReadFromPipe (thisClient->inPortParams->cmnInParams.fileIpBufPipe,
                            &pipeMsg,
                            sizeof(OMTB_CLIENT_FILEIO_PARAMS),
                            (void*) &actualSize,
                            TIMM_OSAL_SUSPEND );       
	
	PRINT(PRINT_DEBUG_MESSAGE, "Read Size:%d\n", readSize);	       

    /* EOS Stream / Stop cmd received from parent thread  */
	if(OMTB_CLIENT_PIPE_CMD_EXIT == pipeMsg.cmd)
    {
		putPipeMessage = OMX_TRUE;
        pipeMsg.buffLen = 0;		
		break;	
	}
	
	ASSERT(NULL != thisClient->inPortParams->cmnInParams.fin);
	ASSERT(NULL != pipeMsg.pBuff);

#ifdef FILEIO_PROFILE
    gettimeofday(&time_file_read,0);
    before_read = ((time_file_read.tv_sec * 1000 * 1000) + time_file_read.tv_usec);
#endif

    dataRead = fread(pipeMsg.pBuff, 1, readSize, thisClient->inPortParams->cmnInParams.fin);
	
#ifdef FILEIO_PROFILE
    gettimeofday(&time_file_read,0);
    after_read = ((time_file_read.tv_sec * 1000 * 1000) + time_file_read.tv_usec);
	timer_read += (after_read - before_read);
	total_bytes_read += dataRead;
#if 0
	/*chk the date rate for one sec*/
	if(timer_read >= (1000000))
	{
	  printf("Read Data Rate in MB/s:%d\n", (total_bytes_read)/(1024 * 1024));
	  total_bytes_read = 0;
	  timer_read = 0;
	}
#else
	//printf("Read Data -> bytes:[%d], time in usecs[%llu]\n", dataRead,(after_read - before_read));
#endif	
#endif	
	pipeMsg.buffLen = dataRead;
    
	PRINT(PRINT_DEBUG_MESSAGE, "Data read from file:%d\n", dataRead);	  
    
	/* Exit the loop if no data available */
    if(0 >= dataRead)
    {
	  if(feof(thisClient->inPortParams->cmnInParams.fin) && (OMX_TRUE == thisClient->inPortParams->cmnInParams.fileReset))
      {
        /* Rewind the file */
        fseek(thisClient->inPortParams->cmnInParams.fin, 0, SEEK_SET);
 	
  	    /* Read the data from file */
        dataRead = fread(pipeMsg.pBuff, 1, readSize, thisClient->inPortParams->cmnInParams.fin);
	    pipeMsg.buffLen = dataRead;		   
      }
      else
      {
        PRINT(PRINT_MUST, "No dataRead, End of stream reached\n");
  	    /*Reached end of stream, stop the file read */
        thisClient->inPortParams->cmnInParams.stopFileRead = OMX_TRUE;
        pipeMsg.buffLen = 0;	
		putPipeMessage = OMX_TRUE;
		break;
      }	
    }

	/*Write the buffer pointer to pipe, will be used by the vdec parser / for DDR -> DDR copy*/
    TIMM_OSAL_WriteToPipe (thisClient->inPortParams->cmnInParams.fileOpBufPipe,
                           &pipeMsg,
                           sizeof(OMTB_CLIENT_FILEIO_PARAMS),
                           TIMM_OSAL_SUSPEND );
  }  
   	
  /* put the message back on the pipe */
  if(OMX_TRUE == putPipeMessage)
  {
    TIMM_OSAL_WriteToPipe (thisClient->inPortParams->cmnInParams.fileOpBufPipe,
                           &pipeMsg,
                           sizeof(OMTB_CLIENT_FILEIO_PARAMS),
                           TIMM_OSAL_SUSPEND );  
  }
  
  PRINT(DEFAULT_MESSAGES, "The execution of the file read is terminated\n");

  /* post input buffer read thread exit */
  TIMM_OSAL_SemaphoreRelease(thisClient->omtbPvt.fileReadThrExit);

  PRINT(PRINT_MUST, "Leaving <Thread #> : <%s>\n", __FUNCTION__);
					 
  /* exit the thread */
  TIMM_OSAL_ExitTask(thisClient->omtbPvt.fileReadThrdId, NULL);
}


/******************************************************************************\
 *      OMTB_InputDataRead Thread Definition
\******************************************************************************/
/**
 *
 *  @brief    This is a H264 thread which reads data from input file
 *
 *  @param in:
 *            void * - Thread args count
 *
 *            void *threadsArg - Pointer to thread arg structure
 *
 *  @return   None
 *
 */

void OMTB_InputDataRead(void *argc, void *threadsArg)
{
  unsigned int actualSize = 0,dataRead = 0;
  OMX_ERRORTYPE err = OMX_ErrorNone;
  OMTB_CLIENT_PRIVATE* thisClient = NULL;
  OMX_BUFFERHEADERTYPE* pBufferIn = NULL;
  OMX_STATETYPE pState = OMX_StateInvalid;
  TIMM_OSAL_ERRORTYPE bReturnStatus = TIMM_OSAL_ERR_NONE;  
  int threadRes = TIMM_OSAL_ERR_NONE;
  unsigned int retVal = TIMM_OSAL_ERR_NONE;  
  OMTB_CLIENT_FILEIO_PARAMS pipeMsg;  
  unsigned int numRemaining;  
  int noInputbuffers = 0;
  int totalInputBuffers = 0;
  unsigned int putPipeMessage = OMX_FALSE;
  int readBytes = 0;
  int eosFlag = OMX_FALSE;
  int ipBuffSize = 0;
  OMTB_OMX_API_TIMING_VAR_DECL;

  /* thread argument validation */
  ASSERT(NULL != threadsArg);

  thisClient = threadsArg; 

  PRINT(PRINT_MUST, "Entering <Thread , instance #> : <%s , %d>\n",
                     __FUNCTION__, (int)thisClient->omtbPvt.instanceNo);

  
  /* Create input data read thread */
  threadRes = TIMM_OSAL_CreateTask(
                    (void *)&thisClient->omtbPvt.fileReadThrdId,
                    (TIMM_OSAL_TaskProc)OMTB_FileRead,
                    0,
                    threadsArg, 
                    OMTB_H264_VDEC_TSK_STACK_SIZE,
                    1,
                    (signed char*)"FILE_READ_TSK");

  if(TIMM_OSAL_ERR_NONE != threadRes)
  {
    PRINT(PRINT_ERR_MSG,
          "Unable to start OMTB FileRead thread\n");
  }

  /* use the initial i/p buffers and make empty this buffer calls */
  err = OMTB_UseInitialInputResources(thisClient);

  if(OMX_ErrorNone != err)
  {
    OMTB_OmxReturnStatus(err);
  }

  /* set the input buffer size used for Audio decode*/
  ipBuffSize = thisClient->inPortParams->cmnInParams.bufferInSize;
		
  while(OMTB_LOOP)
  {
    PRINT(PRINT_DEBUG_MESSAGE,"Entering EmptyThisBuffer Loop\n");

#ifdef OMTB_DEMO   
	if((OMX_TRUE == gOmtbStopVdecDemoFlag) && (OMTB_H264_VDEC_CLASS == thisClient->omtbPvt.eClassType)) 
	{
      /* wait for the start command from the main thread*/
	  TIMM_OSAL_SemaphoreObtain(gOmtbVdecDemoSem, TIMM_OSAL_SUSPEND);
      gOmtbStopVdecDemoFlag = OMX_FALSE;
    }
#endif

    /* Read empty buffer pointer from the pipe */
    TIMM_OSAL_ReadFromPipe (thisClient->inPortParams->cmnInParams.ipBufPipe,
                            &pBufferIn,
                            sizeof(pBufferIn),
                            (void*) &actualSize,
                            TIMM_OSAL_SUSPEND );       


    /* FIXME:Exit the loop if exec -> idle state tranistion or EOS  is reached*/
	/* The following chk used is used to exit this thread from the parent thread (api_task) */
    if(OMX_BUFFERFLAG_EOS == (pBufferIn->nFlags & OMX_BUFFERFLAG_EOS))
    {
      //PRINT(PRINT_MUST, "EOS reached ...\n");
	  putPipeMessage = OMX_TRUE;
      break;
    }	
	
	/* Memcpy: DDR -> DDR Copy */
    if(OMTB_H264_VDEC_CLASS == thisClient->omtbPvt.eClassType)
	{
	  /* Fill the data in the empty buffer, the buffer will have one complete frame */
      dataRead = H264VDEC_FillData(
                        thisClient,
                        pBufferIn,
                        thisClient->inPortParams->frameCount);
	}
    else if(OMTB_VDEC_CLASS == thisClient->omtbPvt.eClassType)
	{
	  /* TODO: Need to identify the fill data function call based on the video decoder type */
	  /* Fill the data in the empty buffer, the buffer will have one complete frame */
      dataRead = MPEG2VDEC_FillData(thisClient, pBufferIn, 0);						
	}	
    else if(OMTB_ADEC_CLASS == thisClient->omtbPvt.eClassType)
	{	
	    /* Fill data in i/p Buffer */
	    /* if the total buffer size is less than required input size, fill the data */
	    if(((thisClient->inPortParams->adecBuffer.buffLen + pBufferIn->nFilledLen) < 
		   thisClient->inPortParams->cmnInParams.bufferInSize) && (OMX_FALSE == eosFlag))
        { 
          /* Read the buffer poniter from pipe */
          TIMM_OSAL_ReadFromPipe( thisClient->inPortParams->cmnInParams.fileOpBufPipe,
                                 &pipeMsg,
                                 sizeof(OMTB_CLIENT_FILEIO_PARAMS),
                                 (void*) &actualSize,
                                 TIMM_OSAL_SUSPEND );	
								 
          if(0 == pipeMsg.buffLen) 
		    eosFlag = OMX_TRUE;  

          /* copy or move the existing data to the begining of the buffer*/
		  retVal = TIMM_OSAL_Memcpy(thisClient->inPortParams->adecBuffer.pBuff,  
		                            (thisClient->inPortParams->adecBuffer.pBuff + thisClient->inPortParams->adecBuffer.nOffset), 
								    thisClient->inPortParams->adecBuffer.buffLen);  	
	  
          /* copy the buffer */									
          retVal = TIMM_OSAL_Memcpy((thisClient->inPortParams->adecBuffer.pBuff + thisClient->inPortParams->adecBuffer.buffLen),  
		                            (pipeMsg.pBuff + pipeMsg.nOffset),
									pipeMsg.buffLen);  		
									
          thisClient->inPortParams->adecBuffer.nOffset	= 0;									
          thisClient->inPortParams->adecBuffer.buffLen	+= pipeMsg.buffLen;	
		  
	      /* Write to the pipe of File Read Thread */
          TIMM_OSAL_WriteToPipe( thisClient->inPortParams->cmnInParams.fileIpBufPipe,
                               &pipeMsg,
                               sizeof(OMTB_CLIENT_FILEIO_PARAMS),
                               TIMM_OSAL_SUSPEND );				  
		}  
			
  	    /* move the remaining bytes to the begining of the buffer */  
  	    retVal = TIMM_OSAL_Memcpy(pBufferIn->pBuffer,  
		                          (pBufferIn->pBuffer +  (ipBuffSize - pBufferIn->nFilledLen)), 
		 					      pBufferIn->nFilledLen); 
								  
		/* chk to handle EOS */
        if((thisClient->inPortParams->adecBuffer.buffLen + pBufferIn->nFilledLen) < thisClient->inPortParams->cmnInParams.bufferInSize)
		{
  		  readBytes = thisClient->inPortParams->adecBuffer.buffLen;		  
		  ipBuffSize = pBufferIn->nFilledLen + readBytes;
		}  
		else
		  readBytes = (thisClient->inPortParams->cmnInParams.bufferInSize - pBufferIn->nFilledLen);		

								  
        /* copy the remaining bytes from the temp  buffer */ 								  
        retVal = TIMM_OSAL_Memcpy( (pBufferIn->pBuffer + pBufferIn->nFilledLen),  
		                           (thisClient->inPortParams->adecBuffer.pBuff + thisClient->inPortParams->adecBuffer.nOffset),
								   readBytes);  
								   
        thisClient->inPortParams->adecBuffer.nOffset += readBytes;									
        thisClient->inPortParams->adecBuffer.buffLen -= readBytes;		
		  
        /* Update the buffer header with buffer filled length */
        pBufferIn->nFilledLen += readBytes;		
	        
	    dataRead = pBufferIn->nFilledLen;	  

        if (TIMM_OSAL_ERR_NONE != retVal)
        {
          PRINT(PRINT_ERR_MSG, "TIMM_OSAL_Memcpy failed\n");
		  putPipeMessage = OMX_TRUE;
          break;
        }	  
	}	
    else
    {
       /* Read the buffer poniter from pipe */
       TIMM_OSAL_ReadFromPipe( thisClient->inPortParams->cmnInParams.fileOpBufPipe,
                               &pipeMsg,
                               sizeof(OMTB_CLIENT_FILEIO_PARAMS),
                               (void*) &actualSize,
                               TIMM_OSAL_SUSPEND );	
							   
       /* Fill data in i/p Buffer */
      /* memcpy: DDR to DDR Copy */
      retVal = TIMM_OSAL_Memcpy(pBufferIn->pBuffer,  (pipeMsg.pBuff + pipeMsg.nOffset), pipeMsg.buffLen);

      /* Update the buffer header with buffer filled length */
      pBufferIn->nFilledLen = pipeMsg.buffLen;
  
      if (TIMM_OSAL_ERR_NONE != retVal)
      {
        PRINT(PRINT_ERR_MSG, "TIMM_OSAL_Memcpy failed\n");
		putPipeMessage = OMX_TRUE;
        break;
      }	  
	  
      dataRead = pipeMsg.buffLen;
   	  
	  /* Write to the pipe of File Read Thread */
      TIMM_OSAL_WriteToPipe( thisClient->inPortParams->cmnInParams.fileIpBufPipe,
                             &pipeMsg,
                             sizeof(OMTB_CLIENT_FILEIO_PARAMS),
                             TIMM_OSAL_SUSPEND );		  
	}	

	PRINT(PRINT_DEBUG_MESSAGE, "Bytes read are:%d\n", dataRead);
  
   /* Exit the loop/Reset the file if no data is available */
    if(0 >= dataRead)
    {
      PRINT(PRINT_DEBUG_MESSAGE, "%s: End of File reached\n", __FUNCTION__);	
      pBufferIn->nFlags |= OMX_BUFFERFLAG_EOS;
	  
      /*FIXME: patch */
	  /* release the semaphore as some components does not notify EOS */
      TIMM_OSAL_SemaphoreRelease(thisClient->omtbPvt.eofSem);
		  
	  /* Pass the input buffer to the component */
      err = OMX_EmptyThisBuffer(thisClient->omtbPvt.handle, pBufferIn);	  
      
	  putPipeMessage = OMX_FALSE;
      break;											
    }
    else
    {
      /* increase the frame counter if some data is available */
      thisClient->inPortParams->frameCount++;
    }

    PRINT(PRINT_DEBUG_MESSAGE, "Address of pBufferIn is: %x\n",
                                (unsigned int) pBufferIn);
    PRINT(PRINT_DEBUG_MESSAGE, "nAlloca length is: %d\n", \
                                (int) pBufferIn->nAllocLen);
    PRINT(PRINT_DEBUG_MESSAGE, "nFilled length is: %d\n", \
                                (int) pBufferIn->nFilledLen);
    PRINT(PRINT_DEBUG_MESSAGE,"nFlags: %d\n", pBufferIn->nFlags == OMX_BUFFERFLAG_EOS);

    /* API entry time calculation macro */
    OMTB_OMX_API_ENTRY_TIME_CALC;

    /* Pass the input buffer to the component */
    err = OMX_EmptyThisBuffer(thisClient->omtbPvt.handle, pBufferIn);

    /* API exit time calculation macro */
    OMTB_OMX_API_EXIT_TIME_CALC("OMX_EmptyThisBuffer");

    if(OMX_ErrorNone != err)
    {
	  /* If the component is not in exec state put back the frame in pipe and exit the thread*/
      if(OMX_ErrorIncorrectStateOperation != err)   
	  {
	    OMTB_OmxReturnStatus(err);	  
      }
      putPipeMessage = OMX_TRUE;
      break; 						
    }
  } // while(OMTB_LOOP)

  /* Added to exit based on the EOS received from input read thread as */
  /* component is not reporting EOS event currently */
  if(OMX_BUFFERFLAG_EOS == pBufferIn->nFlags)
  {
    thisClient->inPortParams->cmnInParams.flagInputEos = OMX_TRUE;
    thisClient->outPortParams->cmnOutParams.flagEos = OMX_TRUE;
  }

  /* put back the frame in pipe */	  
  if(OMX_TRUE == putPipeMessage)
  {
    TIMM_OSAL_WriteToPipe (thisClient->inPortParams->cmnInParams.ipBufPipe,
                           &pBufferIn,
                           sizeof(pBufferIn),
                           TIMM_OSAL_SUSPEND );	  
  }

  thisClient->inPortParams->cmnInParams.stopFileRead = OMX_TRUE;
  
  /* Send the EXIT Command for file read thread*/
  OMTB_ClientSendCmdEXIT(thisClient, 
                         thisClient->inPortParams->cmnInParams.fileOpBufPipe,
						 thisClient->inPortParams->cmnInParams.fileIpBufPipe);

  /* Wait till the processing is completed by the child threads(file read) */
  TIMM_OSAL_SemaphoreObtain(thisClient->omtbPvt.fileReadThrExit, TIMM_OSAL_SUSPEND);  

#if 0  
  /* Remove/Clear all the buffer in fileIo input Pipe */
  OMTB_ClientClearPipe(thisClient->inPortParams->cmnInParams.fileIpBufPipe, sizeof(OMTB_CLIENT_FILEIO_PARAMS));  

  /* Remove/Clear all the buffer in fileIo output Pipe */
  OMTB_ClientClearPipe(thisClient->inPortParams->cmnInParams.fileOpBufPipe, sizeof(OMTB_CLIENT_FILEIO_PARAMS));  

  PRINT(PRINT_MUST, "Get all the file read input buffers from the component:%d\n", thisClient->inPortParams->cmnInParams.numInBuf);  
  
  totalInputBuffers = thisClient->inPortParams->cmnInParams.numInBuf;
  
  if((OMTB_H264_VDEC_CLASS == thisClient->omtbPvt.eClassType) ||
     (OMTB_H264_VDEC_CLASS == thisClient->omtbPvt.eClassType))
  {
    /* wait for one buffer incase of h264 and mpeg2 as the parser holds one buffer */
    //totalInputBuffers = totalInputBuffers - 1;
  }	
	
  //while(noInputbuffers < totalInputBuffers) 
  {
    TIMM_OSAL_GetPipeReadyMessageCount (thisClient->inPortParams->cmnInParams.ipBufPipe,
									 (void*) &numRemaining);
    while(numRemaining)
    {									 
      /* Read empty buffer pointer from the pipe of file io */
      TIMM_OSAL_ReadFromPipe (thisClient->inPortParams->cmnInParams.ipBufPipe,
	       				      &pBufferIn,
						      sizeof(pBufferIn),
						      (void*) &actualSize,
						      TIMM_OSAL_SUSPEND );    
							  
      TIMM_OSAL_GetPipeReadyMessageCount (thisClient->inPortParams->cmnInParams.ipBufPipe,
									 (void*) &numRemaining);					  
	  noInputbuffers++;
    }
  }
  PRINT(PRINT_MUST, "Received all the file read input buffers from the component:%d\n", thisClient->inPortParams->cmnInParams.numInBuf);
  
  /* Remove all the buffer in Input Buffer Pipe */
  /* Clear the pipe / Ignore the buffers */												 
  OMTB_ClientClearPipe(thisClient->inPortParams->cmnInParams.ipBufPipe, sizeof(pBufferIn));   
#endif  
  PRINT(DEFAULT_MESSAGES, "The execution of the input data read is terminated\n");
  /* post input buffer read thread exit */
  TIMM_OSAL_SemaphoreRelease(thisClient->omtbPvt.inputDataReadThrExit);

  PRINT(PRINT_MUST, "Leaving <Thread , instance #> : <%s , %d>\n",
                     __FUNCTION__, (int)thisClient->omtbPvt.instanceNo);

  /* exit the thread */
  TIMM_OSAL_ExitTask(thisClient->inPortParams->cmnInParams.inDataStrmThrdId, NULL);
}


/******************************************************************************\
 *      OMTB_FileWrite Thread Definition
\******************************************************************************/
/**
 *
 *  @brief    This is a H264 thread which writes data to file
 *
 *  @param in:
 *            void * - Thread args count
 *
 *            void *threadsArg - Pointer to thread arg structure
 *
 *  @return   None
 *
 */

void OMTB_FileWrite(void *argc, void *threadsArg)
{
  unsigned int actualSize = 0,dataWrite = 0;
  OMTB_CLIENT_PRIVATE* thisClient = NULL;
  OMTB_CLIENT_FILEIO_PARAMS pipeMsg;
  unsigned int i = 0;
  unsigned int  numRemaining = 0;
  unsigned int putPipeMessage = OMX_FALSE;
  OMTB_OMX_API_TIMING_VAR_DECL;

  /* thread argument validation */
  ASSERT(NULL != threadsArg);
  thisClient = threadsArg; 

  PRINT(PRINT_MUST, "Entering <Thread , instance #> : <%s , %d>\n",
                     __FUNCTION__, (int)thisClient->omtbPvt.instanceNo);
  
  thisClient->outPortParams->cmnOutParams.stopFileWrite = OMX_FALSE;  
  
  /* Initially put all the buffers into the pipe */
  for(i = 0; i < thisClient->omtbPvt.numFileOutBufs; i++)
  {
    /* write the buffers into the pipe */
    TIMM_OSAL_WriteToPipe (thisClient->outPortParams->cmnOutParams.fileIpBufPipe,
                           &thisClient->outPortParams->sFileIOBuff[i],
                           sizeof(OMTB_CLIENT_FILEIO_PARAMS),
                           TIMM_OSAL_SUSPEND );  
  }
  
  /* Break the loop and delete the thread if the component moves to idle state */  
  while(OMX_TRUE != thisClient->outPortParams->cmnOutParams.stopFileWrite)
  {

    PRINT(PRINT_DEBUG_MESSAGE,"FileWrite Loop, Write the buffer\n");

    /* Read empty buffer pointer from the pipe of file io */
    TIMM_OSAL_ReadFromPipe (thisClient->outPortParams->cmnOutParams.fileOpBufPipe,
                            &pipeMsg,
                            sizeof(OMTB_CLIENT_FILEIO_PARAMS),
                            (void*) &actualSize,
                            TIMM_OSAL_SUSPEND );       
      
	/* received EXIT the thread */
    if((-1 == pipeMsg.buffLen) || (OMTB_CLIENT_PIPE_CMD_EXIT == pipeMsg.cmd))
    {
	  thisClient->outPortParams->cmnOutParams.stopFileWrite = OMX_TRUE;
      putPipeMessage = OMX_TRUE;
      break;
	} 	  
	  
	ASSERT(NULL != thisClient->outPortParams->cmnOutParams.fout);
	PRINT(PRINT_DEBUG_MESSAGE, "Write Size:%d\n", pipeMsg.buffLen);	
	
    if(OMTB_H264_VDEC_CLASS == thisClient->omtbPvt.eClassType)
	{
      long fieldBuf;
      fieldBuf = (long) TIMM_OSAL_Malloc(thisClient->outPortParams->cmnOutParams.bufferOutSize,
                                         TIMM_OSAL_TRUE,
										 0,
										 TIMMOSAL_MEM_SEGMENT_EXT);

      H264_TestApp_WriteOutputData(thisClient->outPortParams->cmnOutParams.fout,
		                           pipeMsg.pBuff,
				   			  	   pipeMsg.buffLen,
								   pipeMsg.nOffset,
                                   thisClient->outPortParams->nHeight,		
                                   thisClient->outPortParams->nWidth,
                                   fieldBuf);
								
      TIMM_OSAL_Free((TIMM_OSAL_PTR)fieldBuf);

      dataWrite = pipeMsg.buffLen;
    }
    else if(OMTB_VDEC_CLASS == thisClient->omtbPvt.eClassType)
	{
      long fieldBuf;
      fieldBuf = (long) TIMM_OSAL_Malloc(thisClient->outPortParams->cmnOutParams.bufferOutSize,
                                   		 TIMM_OSAL_TRUE,
									     0,
										 TIMMOSAL_MEM_SEGMENT_EXT);

 	  TestApp_WriteOutputData(thisClient->outPortParams->cmnOutParams.fout,
		                      pipeMsg.pBuff,
		                      pipeMsg.buffLen,
							  pipeMsg.nOffset,
                              thisClient->outPortParams->nHeight,		
                              thisClient->outPortParams->nWidth,
                              fieldBuf);
								
      TIMM_OSAL_Free((TIMM_OSAL_PTR)fieldBuf);

	   dataWrite = pipeMsg.buffLen;
	}	  
	else
	{
#ifdef FILEIO_PROFILE
      gettimeofday(&time_file_write,0);
      before_write = ((time_file_write.tv_sec * 1000 * 1000) + time_file_write.tv_usec);
#endif	  
      /* Write the data to file */
      dataWrite = fwrite(pipeMsg.pBuff, 1, pipeMsg.buffLen, thisClient->outPortParams->cmnOutParams.fout);
	  fflush(thisClient->outPortParams->cmnOutParams.fout);
		
#ifdef FILEIO_PROFILE
      gettimeofday(&time_file_write,0);
      after_write = ((time_file_write.tv_sec * 1000 * 1000) + time_file_write.tv_usec);
	  timer_write += (after_write - before_write);
	  total_bytes_write += dataWrite;
#if 0		
	  /*chk the date rate for one sec*/
	  if(timer_write >= (1000000))
	  {
	    printf("Write Data Rate in MB/s:%d\n", (total_bytes_write)/(1024 * 1024));
	    total_bytes_write = 0;
	    timer_write = 0;
	  }
#else
	  //printf("Write Data -> bytes:[%d], time in usecs[%llu]\n", dataWrite, (after_write - before_write));
#endif		
#endif		
	}	
	  
    /* Exit the loop if error in data write */
    if((0 >= dataWrite) && (pipeMsg.buffLen > 0))
    {
      PRINT(PRINT_ERR_MSG, "Error in <%s , fwrite>:\n", __FUNCTION__);
      thisClient->outPortParams->cmnOutParams.stopFileWrite = OMX_TRUE;
	  putPipeMessage = OMX_TRUE;		
	  break;
    }

	/*Write the buffer pointer to pipe, will be used for memcpy DDR -> DDR */
    TIMM_OSAL_WriteToPipe (thisClient->outPortParams->cmnOutParams.fileIpBufPipe,
                            &pipeMsg,
                            sizeof(OMTB_CLIENT_FILEIO_PARAMS),
                            TIMM_OSAL_SUSPEND );
      
  }	
  
  /*put the message back on the pipe */
  if(OMX_TRUE == putPipeMessage)
  {
    TIMM_OSAL_WriteToPipe (thisClient->outPortParams->cmnOutParams.fileIpBufPipe,
                            &pipeMsg,
                            sizeof(OMTB_CLIENT_FILEIO_PARAMS),
                            TIMM_OSAL_SUSPEND );
  }							
  
  PRINT(DEFAULT_MESSAGES, "The execution of the file write is terminated\n");

  /* post output buffer write thread exit */
  TIMM_OSAL_SemaphoreRelease(thisClient->omtbPvt.fileWriteThrExit);

  PRINT(PRINT_MUST, "Leaving <Thread #> : <%s>\n", __FUNCTION__);

  /* exit the thread */
  TIMM_OSAL_ExitTask(thisClient->omtbPvt.fileWriteThrdId, NULL);
}

/******************************************************************************\
 *      OMTB_UseInitialOutputResources_new Function Definition
\******************************************************************************/
/**
 *
 *  @brief    Tells component to fill the initial buffers.
 *
 *  @param in:
 *            h264VencClient: Pointer to appPrivateType structure
 *
 *  @param Out:
 *            None
 *
 *  @return   OMX_ERRORTYPE - OMX std return/error code
 *
 */

OMX_ERRORTYPE OMTB_UseInitialOutputResources_new(
  OMTB_CLIENT_PRIVATE* thisClient)
{

  OMX_ERRORTYPE err = OMX_ErrorNone;
  unsigned int i = 0, j = 0;
  OMTB_CLIENT_OUTPORT_PARAMS *outPortParamsPtr;  
  OMTB_OMX_API_TIMING_VAR_DECL;

  /* validate the function arguments */
  ASSERT(NULL != thisClient);

  PRINT(PRINT_FUNCTION_NAME, "Entering <Function , instance #> : <%s , %d>\n",
                              __FUNCTION__, (int)thisClient->omtbPvt.instanceNo);

  for(j = 0; j < thisClient->omtbPvt.numOutport; j++)
  {
    outPortParamsPtr = thisClient->outPortParams + j;

    /* Give output buffers to component which is limited by no of output buffers
       available. Rest of the data will be written on the callback from output
       data write thread */
    for(i = 0; i < outPortParamsPtr->cmnOutParams.pOutPortDef->nBufferCountActual; i++)
    {
      /* API entry time calculation macro */
      OMTB_OMX_API_ENTRY_TIME_CALC;

      /* Pass the output buffer to the component */
      err = OMX_FillThisBuffer(
                        thisClient->omtbPvt.handle,
                        outPortParamsPtr->pOutBuff[i]);

      /* API exit time calculation macro */
      OMTB_OMX_API_EXIT_TIME_CALC("OMX_FillThisBuffer");

      if(OMX_ErrorNone != err)
      {
        OMTB_OmxReturnStatus(err);
        return err;
      }
      else
      {
        PRINT(PRINT_DEBUG_MESSAGE,"Fill O/P Buffer\n");
      }
    }
  }
  
  PRINT(PRINT_FUNCTION_NAME, "Leaving <Function , instance #> : <%s , %d>\n",
                              __FUNCTION__, (int)thisClient->omtbPvt.instanceNo);

  return err;
}
/******************************************************************************\
 *      OMTB_OutputDataWrite Thread Definition
\******************************************************************************/
/**
 *
 *  @brief    This is a thread which writes data to output file
 *
 *  @param in:
 *            void * - Thread args count
 *
 *            threadArg - Parameters which we need to pass from func function.
 *
 *  @return   None
 *
 */

void OMTB_OutputDataWrite(void *argc, void *threadsArg)
{
  unsigned int actualSize = 0,framesEncoded = 0;
  OMX_ERRORTYPE err = OMX_ErrorNone;
  OMTB_CLIENT_PRIVATE* thisClient = NULL;
  OMX_BUFFERHEADERTYPE* pBufferOut = NULL;
  OMX_STATETYPE pState = OMX_StateInvalid;
  int template = 0;
  int portIdx = 0;
  int fileIoFlag = OMX_TRUE;
  char inputCmdLine[OMTB_MAX_LEN] = {'\0'};

  int threadRes = TIMM_OSAL_ERR_NONE;
  TIMM_OSAL_ERRORTYPE retVal = TIMM_OSAL_ERR_NONE;
  OMTB_CLIENT_FILEIO_PARAMS pipeMsg;
  unsigned int numRemaining;  
  int noOutputbuffers = 0;
  unsigned int putPipeMessage  = OMX_FALSE;
  OMTB_OMX_API_TIMING_VAR_DECL;

  /* thread argument validation */
  ASSERT(NULL != threadsArg);
  thisClient = threadsArg;

  PRINT(PRINT_MUST, "Entering <Thread , instance #> : <%s , %d>\n",
                     __FUNCTION__, (int)thisClient->omtbPvt.instanceNo);
  
  /* Create input data read thread */
  threadRes = TIMM_OSAL_CreateTask(
                    (void *)&thisClient->omtbPvt.fileWriteThrdId,
                    (TIMM_OSAL_TaskProc)OMTB_FileWrite,
                    0,
                    threadsArg, 
                    OMTB_H264_VENC_TSK_STACK_SIZE,
                    OMTB_H264_VENC_GROUP_PRIORITY,
                    (signed char*)"H264_VENC_FILEIO_TSK");

  if(TIMM_OSAL_ERR_NONE != threadRes)
  {
    PRINT(PRINT_ERR_MSG,
          "Unable to start OMTB FileWrite thread\n");
  }  

  /* use the initial o/p buffers and make fill this buffer calls */
  err = OMTB_UseInitialOutputResources_new(thisClient);

  if(OMX_ErrorNone != err)
  {
    OMTB_OmxReturnStatus(err);
  }

  while(OMTB_LOOP)
  {
    PRINT(PRINT_DEBUG_MESSAGE,"Entering FillThisBuffer Loop\n");

#ifdef OMTB_DEMO
    if((OMX_TRUE == gOmtbStopVencDemoFlag) && (OMTB_H264_VENC_CLASS == thisClient->omtbPvt.eClassType)) 
    {
	  OMTB_H264_VENC_PRIVATE* h264VencClient = (OMTB_H264_VENC_PRIVATE*)thisClient;
      
	  /*Close the file when the demo stops */
      fclose(thisClient->outPortParams->cmnOutParams.fout);
		 
      /* wait for the start command from the main thread*/
	  TIMM_OSAL_SemaphoreObtain(gOmtbVencDemoSem, TIMM_OSAL_SUSPEND);
       
	  /* call setconfig for Force IDR Frame */
	  portIdx = OMTB_H264_VENC_DEF_START_PORT_NUM + OMTB_H264_VENC_MAX_IN_PORT;
	     
      /* generate the command */
      sprintf(inputCmdLine, "omx setp %d %s OMX_IndexConfigVideoIntraVOPRefresh IntraRefreshVOP enable",
              template,
              OMTB_H264_VENC_COMP_REF_STR);				 
      PRINT(PRINT_MUST, "%s\n", inputCmdLine);   
      /* Process the command */
      procCmdLine(inputCmdLine);
		 
      /* generate the command */
      sprintf(inputCmdLine, "omx api setconfig %s %d %d %d %s",
              OMTB_H264_VENC_COMP_REF_STR,
              thisClient->omtbPvt.instanceNo,
              template,
              portIdx,
              "OMX_IndexConfigVideoIntraVOPRefresh");
      PRINT(PRINT_MUST, "%s\n", inputCmdLine);
      /* Process the command */
      procCmdLine(inputCmdLine);
  
      /*Re-Open the file when the demo starts */
      thisClient->outPortParams->cmnOutParams.fout = fopen(h264VencClient->outputFile, "wb");
      
	  if(NULL == thisClient->outPortParams->cmnOutParams.fout)
      {
        PRINT(PRINT_ERR_MSG, "Error opening output file %s\n",h264VencClient->outputFile);
		return;
      }		 
		 
      gOmtbStopVencDemoFlag = OMX_FALSE;
		 
      /* Start writing data after finding the IDR frame */
      fileIoFlag = OMX_FALSE;
	}
#endif
    /* Read filled buffer pointer from the pipe */
    TIMM_OSAL_ReadFromPipe( thisClient->outPortParams->cmnOutParams.opBufPipe,
                            &pBufferOut,
                            sizeof(pBufferOut),
                            (void*) &actualSize,
                            TIMM_OSAL_SUSPEND );

    /* FIXME:Exit the loop if exec -> idle state tranistion or EOS  is reached*/
	/* The following chk used is used to exit this thread from the parent thread (api_task) */
    if(OMX_BUFFERFLAG_EOS == (pBufferOut->nFlags & OMX_BUFFERFLAG_EOS))
    {
      //PRINT(PRINT_MUST, "EOS reached ...\n");
	  putPipeMessage = OMX_TRUE;
      break;
    }							

#ifdef OMTB_DEMO
	  /* Chk for IDR frame as first frame is expected to be IDR, Ignore the first few P frames */
	  if((OMX_FALSE == fileIoFlag) && (OMTB_H264_VENC_CLASS == thisClient->omtbPvt.eClassType))
	  {
	    if(OMX_TRUE == OMTB_H264IsIDRFrame(pBufferOut->pBuffer, pBufferOut->nFilledLen))
        {
	      fileIoFlag = OMX_TRUE;
        }	  
	  }   
#endif	 
 	  
    if(OMTB_FILE == thisClient->outPortParams->cmnOutParams.dataOutPutMode)
    {
#ifdef OMTB_DEMO	
	 OMTB_H264_VENC_PRIVATE* h264VencClient = (OMTB_H264_VENC_PRIVATE*)thisClient; 
     if(OMTB_H264_VENC_CLASS == thisClient->omtbPvt.eClassType)
	 { 
      if( h264VencClient->maxFileSize <= (h264VencClient->fileSize + pBufferOut->nFilledLen))
      {
		/* call setconfig for Force IDR Frame */
	    portIdx = OMTB_H264_VENC_DEF_START_PORT_NUM + OMTB_H264_VENC_MAX_IN_PORT;		
          
		/*close the file pointer */  
		fclose(thisClient->outPortParams->cmnOutParams.fout);
		  
		/*Re-Open the file when it goes beyond the max file size */
        thisClient->outPortParams->cmnOutParams.fout = fopen(h264VencClient->outputFile, "wb");
		if(NULL == thisClient->outPortParams->cmnOutParams.fout)
        {
          PRINT(PRINT_ERR_MSG, "Error in opening output file %s\n",h264VencClient->outputFile);
          break;
        }
		  
		/* generate the command */
        sprintf(inputCmdLine, "omx setp %d %s OMX_IndexConfigVideoIntraVOPRefresh IntraRefreshVOP enable",
                template,
                OMTB_H264_VENC_COMP_REF_STR);				 
        PRINT(PRINT_MUST, "%s\n", inputCmdLine);   
	    /* Process the command */
        procCmdLine(inputCmdLine);
		 
		/* generate the command */
        sprintf(inputCmdLine, "omx api setconfig %s %d %d %d %s",
                OMTB_H264_VENC_COMP_REF_STR,
                thisClient->omtbPvt.instanceNo,
                template,
                portIdx,
                "OMX_IndexConfigVideoIntraVOPRefresh");
        PRINT(PRINT_MUST, "%s\n", inputCmdLine);
        /* Process the command */
        procCmdLine(inputCmdLine);
		 
		/*Start Writing the data after finding the IDR frame*/
		fileIoFlag = OMX_FALSE;
		  
		h264VencClient->fileSize = 0;
	  }
     }	  
#endif		
	  if(OMX_TRUE == fileIoFlag)
	  {	
	    if(OMTB_H264_VENC_CLASS == thisClient->omtbPvt.eClassType)
		  h264VencClient->fileSize += pBufferOut->nFilledLen;
		  
        /* Read the buffer poniter from pipe */
        TIMM_OSAL_ReadFromPipe( thisClient->outPortParams->cmnOutParams.fileIpBufPipe,
                                &pipeMsg,
                                sizeof(OMTB_CLIENT_FILEIO_PARAMS),
                                (void*) &actualSize,
                                TIMM_OSAL_SUSPEND ); 	

        /*Fixme: component issue */
        if(OMTB_VPSS_VFPC_DEI_CLASS == thisClient->omtbPvt.eClassType)
		  pBufferOut->nFilledLen = 4147200; // pBufferOut->nFilledLen >> 1;

		/* memcpy: DDR to DDR Copy */
        retVal = TIMM_OSAL_Memcpy( pipeMsg.pBuff, pBufferOut->pBuffer, pBufferOut->nFilledLen);
		pipeMsg.buffLen = pBufferOut->nFilledLen;
		pipeMsg.nOffset = pBufferOut->nOffset;

		if (TIMM_OSAL_ERR_NONE != retVal)
        {
          PRINT(PRINT_ERR_MSG, "TIMM_OSAL_Memcpy failed\n");
          break;
        }
		 
   	    /* Write to the pipe of File Write Thread */
        TIMM_OSAL_WriteToPipe( thisClient->outPortParams->cmnOutParams.fileOpBufPipe,
                               &pipeMsg,
                               sizeof(OMTB_CLIENT_FILEIO_PARAMS),
                               TIMM_OSAL_SUSPEND );	

        PRINT(PRINT_SIMPLE_MESSAGE, "Frame:%d encoded\n",++framesEncoded );
        fflush (thisClient->outPortParams->cmnOutParams.fout);

      } 
    }
    else if(OMTB_DRIVER == thisClient->outPortParams->cmnOutParams.dataOutPutMode)
    {
      /* do nothing */  
    }

    /* reset the buffer filled length */
    pBufferOut->nFilledLen = 0;

    /* API entry time calculation macro */
    OMTB_OMX_API_ENTRY_TIME_CALC;

    /* Pass the output buffer to the component */
    err = OMX_FillThisBuffer(thisClient->omtbPvt.handle, pBufferOut);

    /* API exit time calculation macro */
    OMTB_OMX_API_EXIT_TIME_CALC("OMX_FillThisBuffer");

    if(OMX_ErrorNone != err)
    {
	  if(OMX_ErrorIncorrectStateOperation != err)
	  {
	    OMTB_OmxReturnStatus(err);	  
      }	  
	  putPipeMessage = OMX_TRUE;
      break;   							  
    }
  } // while(OMTB_LOOP)

    /* put back the message in pipe*/  
  if(OMX_TRUE == putPipeMessage)
  {
    TIMM_OSAL_WriteToPipe (thisClient->outPortParams->cmnOutParams.opBufPipe,
                           &pBufferOut,
                           sizeof(pBufferOut),
                           TIMM_OSAL_SUSPEND );
  }						   
  
  thisClient->outPortParams->cmnOutParams.stopFileWrite = OMX_TRUE;
  
  /* Send the EXIT Command for file write thread*/
  OMTB_ClientSendCmdEXIT(thisClient,
                         thisClient->outPortParams->cmnOutParams.fileIpBufPipe,
                         thisClient->outPortParams->cmnOutParams.fileOpBufPipe); 	  

  /* Wait till the processing is completed by the child threads(file write) */
  TIMM_OSAL_SemaphoreObtain(thisClient->omtbPvt.fileWriteThrExit, TIMM_OSAL_SUSPEND);  
#if 0
  /* Remove/Clear all the buffer in fileIo input Pipe */
  OMTB_ClientClearPipe(thisClient->outPortParams->cmnOutParams.fileIpBufPipe, sizeof(OMTB_CLIENT_FILEIO_PARAMS));  

  /* Remove/Clear all the buffer in fileIo output Pipe */
  OMTB_ClientClearPipe(thisClient->outPortParams->cmnOutParams.fileOpBufPipe, sizeof(OMTB_CLIENT_FILEIO_PARAMS));  

  
  PRINT(PRINT_MUST, "Get all the file write output buffers from the component\n");  
  //while(noOutputbuffers < thisClient->outPortParams->cmnOutParams.numOutBuf) 
  {
    TIMM_OSAL_GetPipeReadyMessageCount (thisClient->outPortParams->cmnOutParams.opBufPipe,
									    (void*) &numRemaining);
    while(numRemaining)
    {									 
      /* Read empty buffer pointer from the pipe of file io */
      TIMM_OSAL_ReadFromPipe (thisClient->outPortParams->cmnOutParams.opBufPipe,
	       				      &pBufferOut,
						      sizeof(pBufferOut),
						      (void*) &actualSize,
						      TIMM_OSAL_SUSPEND );    
							  
      TIMM_OSAL_GetPipeReadyMessageCount(thisClient->outPortParams->cmnOutParams.opBufPipe,
                                          (void*) &numRemaining);					  
	  noOutputbuffers++;
    }
  }
  PRINT(PRINT_MUST, "Received all the file write output buffers from the component\n");
  
  /* Remove all the buffer in Input Buffer Pipe */
  /* Clear the pipe / Ignore the buffers */												 
  OMTB_ClientClearPipe(thisClient->outPortParams->cmnOutParams.opBufPipe, sizeof(pBufferOut));  
#endif  
  /* waiting for output buffer write thread exit */
  TIMM_OSAL_SemaphoreRelease(
            thisClient->omtbPvt.outputDataWriteThrExit);

  PRINT(PRINT_MUST, "Leaving <Thread , instance #> : <%s , %d>\n",
                     __FUNCTION__, (int)thisClient->omtbPvt.instanceNo);

  /* exit the thread */
  TIMM_OSAL_ExitTask(thisClient->outPortParams->cmnOutParams.outDataStrmThrdId, NULL);

}



/******************************************************************************\
 *      OMTB_FreeMemory Function Definition
\******************************************************************************/
/**
 *
 *  @brief    Free the memory allocated for the component
 *
 *  @param in:
 *            h264VencClient: Pointer to OMTB_H264_VENC_PRIVATE struct
 *
 *  @return   None
 *
 */

void OMTB_FreeMemory(OMTB_CLIENT_PRIVATE* thisClient)
{
  int instanceNo = thisClient->omtbPvt.instanceNo;
  unsigned int i = 0;
  OMTB_CLIENT_INPORT_PARAMS *inPortParamsPtr = NULL;
  OMTB_CLIENT_OUTPORT_PARAMS *outPortParamsPtr = NULL;
  
  /* validate the function arguments */
  ASSERT(NULL != thisClient);

  PRINT(PRINT_FUNCTION_NAME, "Entering <Function , instance #> : <%s , %d>\n",
                              __FUNCTION__, (int)thisClient->omtbPvt.instanceNo);
  if(NULL != thisClient->omtbPvt.cb)
      TIMM_OSAL_Free(thisClient->omtbPvt.cb);

  if(NULL != thisClient->inPortParams)
  {
    /* Release input port, port defination structure*/
    for (i =0 ; i < thisClient->omtbPvt.numInport ; i++)
    {
      inPortParamsPtr = thisClient->inPortParams + i; 
      if(NULL != inPortParamsPtr->cmnInParams.pInPortDef)
	    TIMM_OSAL_Free(inPortParamsPtr->cmnInParams.pInPortDef);
	  
      if(NULL != inPortParamsPtr->cmnInParams.ipBufPipe)	  
        TIMM_OSAL_DeletePipe(inPortParamsPtr->cmnInParams.ipBufPipe);	  
    }	

	/* Free the memory for file read */  
    for(i = 0; i < thisClient->omtbPvt.numFileInBufs; i++)
    {
      if(NULL != thisClient->inPortParams->sFileIOBuff[i].pBuff)
        TIMM_OSAL_Free(thisClient->inPortParams->sFileIOBuff[i].pBuff);
    }   

    inPortParamsPtr = thisClient->inPortParams;
    /* closing the input file */
    if(NULL != inPortParamsPtr->cmnInParams.fin)
      fclose(thisClient->inPortParams->cmnInParams.fin);

    /* Delete the fileio pipe */
    if(NULL != inPortParamsPtr->cmnInParams.fileIpBufPipe)
      TIMM_OSAL_DeletePipe(thisClient->inPortParams->cmnInParams.fileIpBufPipe);

    /* Delete the fileio pipe */	
    if(NULL != inPortParamsPtr->cmnInParams.fileOpBufPipe)
      TIMM_OSAL_DeletePipe(thisClient->inPortParams->cmnInParams.fileOpBufPipe);	

	if (NULL != thisClient->inPortParams->h264ParseCtx.readBuf)	  
	  TIMM_OSAL_Free( thisClient->inPortParams->h264ParseCtx.readBuf);

	if (NULL != thisClient->inPortParams->mpeg2ParseCtx.readBuf)	  
	  TIMM_OSAL_Free(thisClient->inPortParams->mpeg2ParseCtx.readBuf);	  

	if (NULL != thisClient->inPortParams->adecBuffer.pBuff)	  
	  TIMM_OSAL_Free(thisClient->inPortParams->adecBuffer.pBuff);
	  
  /* Release input port memory */  
     TIMM_OSAL_Free(thisClient->inPortParams);
   }
  
  /* Release output port memory */
  if(NULL != thisClient->outPortParams)
  {
    /* Release output port, port defination structure*/
    for (i =0 ; i < thisClient->omtbPvt.numOutport ; i++)
    {
      outPortParamsPtr = thisClient->outPortParams + i;   
      if(NULL != outPortParamsPtr->cmnOutParams.pOutPortDef)
        TIMM_OSAL_Free(outPortParamsPtr->cmnOutParams.pOutPortDef);

      if(NULL != outPortParamsPtr->cmnOutParams.opBufPipe)	  
        TIMM_OSAL_DeletePipe(outPortParamsPtr->cmnOutParams.opBufPipe);	  
    }	  

    /* Free the memory for file write */  
    for(i = 0; i < thisClient->omtbPvt.numFileOutBufs; i++)
    {
      if(NULL != thisClient->outPortParams->sFileIOBuff[i].pBuff)
        TIMM_OSAL_Free(thisClient->outPortParams->sFileIOBuff[i].pBuff);
    } 

    /* closing the output file */  
    if(OMTB_FILE == thisClient->outPortParams->cmnOutParams.dataOutPutMode)
    {
      if(NULL != thisClient->outPortParams->cmnOutParams.fout)
        fclose(thisClient->outPortParams->cmnOutParams.fout);
    }
    else if(OMTB_DRIVER == thisClient->outPortParams->cmnOutParams.dataOutPutMode)
    {
      /* Driver interface is TBD. So currently using File mode for driver also */
      /* closing the output file */
      if(NULL != thisClient->outPortParams->cmnOutParams.fout)
        fclose(thisClient->outPortParams->cmnOutParams.fout);
    }

    /* Delete the fileio pipe */
    if(NULL != thisClient->outPortParams->cmnOutParams.fileIpBufPipe)
      TIMM_OSAL_DeletePipe(thisClient->outPortParams->cmnOutParams.fileIpBufPipe);
	
    /* Delete the fileio pipe */	
    if(NULL != thisClient->outPortParams->cmnOutParams.fileOpBufPipe)
      TIMM_OSAL_DeletePipe(thisClient->outPortParams->cmnOutParams.fileOpBufPipe);

    TIMM_OSAL_Free(thisClient->outPortParams);
  }	  

  /*Release the memory allocated for pipes */
  if(NULL != thisClient->omtbPvt.localPipe)
    TIMM_OSAL_DeletePipe(thisClient->omtbPvt.localPipe);

  /* Release component event handling semaphore memory */
  if(NULL != thisClient->omtbPvt.eventSem)
    TIMM_OSAL_SemaphoreDelete(thisClient->omtbPvt.eventSem);

  /* Release file read semaphore memory */
  if(NULL != thisClient->omtbPvt.fileReadThrExit)
    TIMM_OSAL_SemaphoreDelete(thisClient->omtbPvt.fileReadThrExit);

  /* Release file read semaphore memory */
  if(NULL != thisClient->omtbPvt.fileWriteThrExit)
    TIMM_OSAL_SemaphoreDelete(thisClient->omtbPvt.fileWriteThrExit);

  /* Release connection data stream semaphore memory */
  if(NULL != thisClient->omtbPvt.connDataStrmThrExit)
    TIMM_OSAL_SemaphoreDelete(thisClient->omtbPvt.connDataStrmThrExit);
	
  /* Release input data read thread exit semaphore memory */
  if(NULL != thisClient->omtbPvt.inputDataReadThrExit)
    TIMM_OSAL_SemaphoreDelete(thisClient->omtbPvt.inputDataReadThrExit);

  /* Release output data write thread exit semaphore memory */
  if(NULL != thisClient->omtbPvt.outputDataWriteThrExit)
    TIMM_OSAL_SemaphoreDelete(
              thisClient->omtbPvt.outputDataWriteThrExit);
			  
  /* Release end of stream semaphore memory */
  if(NULL != thisClient->omtbPvt.eofSem)
    TIMM_OSAL_SemaphoreDelete(
              thisClient->omtbPvt.eofSem);			  

  /* Release app pvt data private structure */
  if(NULL != thisClient)
    TIMM_OSAL_Free(thisClient);

  PRINT(PRINT_FUNCTION_NAME, "Leaving <Function , instance #> : <%s , %d>\n",
                              __FUNCTION__, (int)instanceNo);
}