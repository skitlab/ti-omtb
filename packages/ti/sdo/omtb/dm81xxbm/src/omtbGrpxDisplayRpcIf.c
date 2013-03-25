/*
 * omtbGrpxDisplayRpcIf.c
 *
 * VPS FVID2 Graphics display driver interface file.RPC support
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

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdio.h>
#include <xdc/std.h>
#include <xdc/cfg/global.h>
#include <xdc/runtime/System.h>
#include <xdc/runtime/Assert.h>
#include <xdc/runtime/Diags.h>
#include <xdc/runtime/Gate.h>
#include <xdc/runtime/knl/GateThread.h>
#include <xdc/runtime/knl/GateH.h>
#include <xdc/runtime/IGateProvider.h>
#include <xdc/runtime/knl/Thread.h>
#include <ti/ipc/MultiProc.h>
#include <ti/ipc/MessageQ.h>
#include <ti/ipc/SharedRegion.h>
#include <ti/sdo/rcm/RcmClient.h>
#include "omtbGrpxDisplayRpcIf.h"


typedef struct graphicsRpcStubObject_t
{
  Bool                   bRemoteInitDone;
  IGateProvider_Handle   hGate;
  UInt32                 nInitFxnIdx;
  UInt32                 nStartFxnIdx;  
  UInt32                 nStopFxnIdx;  
  UInt32                 nDeinitFxnIdx;  
  UInt32                 nDisplayToggelFxnIdx;
  RcmClient_Handle       hRcmClient;
} graphicsRpcStubObject_t;

graphicsRpcStubObject_t g_RemoteStubContext = { FALSE,   /* bRemoteInitDone */
                                                NULL,    /* hGate           */
                       ~(0u),      /* nInitFxnIdx     */
                       ~(0u),      /* nStartFxnIdx    */
                       ~(0u),      /* nStopFxnIdx     */
                       ~(0u),      /* nDeinitFxnIdx   */
                       ~(0u)       /* nDisplayToggelFxnIdx */
                       }; 

static Int dvsdk_grapx_display_rpc_remote_mode_init ()
{
   RcmClient_Params  rcmClientParams;
   IArg key;
   Bool doInit = FALSE;
   Int status = 0;
   
   key = Gate_enterSystem();
   if (FALSE == g_RemoteStubContext.bRemoteInitDone) {
     doInit = TRUE;
   }
   Gate_leaveSystem(key);
  
   if (TRUE == doInit) {
       GateThread_Params gtParams;
    
    GateThread_Params_init (&gtParams);
       g_RemoteStubContext.hGate = GateThread_Handle_upCast(GateThread_create(&gtParams, NULL));
    key = GateH_enter (g_RemoteStubContext.hGate);
    
    MessageQ_registerHeap(SharedRegion_getHeap(0),Global_GrpxDssMsgHeapId);
    RcmClient_Params_init (&rcmClientParams);
    rcmClientParams.heapId = Global_GrpxDssMsgHeapId;
    do {
      status = RcmClient_create(DVSDK_DSS_GRPX_SERVER_NAME,
                      &rcmClientParams,
                  &g_RemoteStubContext.hRcmClient);
    if (status < 0) {
      Thread_yield(NULL);
    }
       } while (status < 0);
       if (0 == status) {
      status = RcmClient_getSymbolIndex (g_RemoteStubContext.hRcmClient,
                                          DVSDK_DSS_GRPX_INIT_FXN_NAME,
                                          &g_RemoteStubContext.nInitFxnIdx);
    }
       if (0 == status) {
      status = RcmClient_getSymbolIndex (g_RemoteStubContext.hRcmClient,
                                          DVSDK_DSS_GRPX_START_FXN_NAME,
                                          &g_RemoteStubContext.nStartFxnIdx);
    }
       if (0 == status) {
      status = RcmClient_getSymbolIndex (g_RemoteStubContext.hRcmClient,
                                          DVSDK_DSS_GRPX_STOP_FXN_NAME,
                                          &g_RemoteStubContext.nStopFxnIdx);
    }
    if (0 == status) {
      status = RcmClient_getSymbolIndex (g_RemoteStubContext.hRcmClient,
                                          DVSDK_DSS_GRPX_DEINIT_FXN_NAME,
                                          &g_RemoteStubContext.nDeinitFxnIdx);
    }
    if (0 == status) {
      status = RcmClient_getSymbolIndex (g_RemoteStubContext.hRcmClient,
                                          DVSDK_DSS_GRPX_DISPLAYTOGGLE_FXN_NAME,
                                          &g_RemoteStubContext.nDisplayToggelFxnIdx);
    }
    g_RemoteStubContext.bRemoteInitDone = TRUE;
    GateH_leave(g_RemoteStubContext.hGate, key);
   }
   return status;   
}


static Int dvsdk_grapx_display_exec_rpc   (Int instID, UInt32 rcmFxnIdx)
{
  Int status = 0;
  RcmClient_Message * rcmMsg;  
  IArg key;
  
 
  key = GateH_enter (g_RemoteStubContext.hGate);
  if (0 == status) {
    status = RcmClient_alloc(g_RemoteStubContext.hRcmClient,
              sizeof(UInt32), 
              &rcmMsg);
  }
  if (0 == status) {
   UInt32 *instIDPtr = &(rcmMsg->data[0]);
   *instIDPtr = instID;
   // fill in the remote command message
 rcmMsg->fxnIdx = rcmFxnIdx;
    //rcmMsg->msgId  = msgId; /* MsgId no longer part of RcmClient_Message */
 rcmMsg->result = 0;

 // execute the remote command message
 status = RcmClient_exec(g_RemoteStubContext.hRcmClient, rcmMsg, &rcmMsg);
  }
  if (status >= 0) {
    if (rcmMsg->result < 0) {
   status = -1;
 }
 RcmClient_free (g_RemoteStubContext.hRcmClient,rcmMsg);
  }
  GateH_leave (g_RemoteStubContext.hGate,key);
  return status;
}


Int dvsdk_grapx_display_rpc_init  (Int instID)
{
  Int status;  

  Assert_isTrue((MultiProc_self() != MultiProc_getId("VPSS-M3")), Assert_E_assertFailed);
  status = dvsdk_grapx_display_rpc_remote_mode_init();
  if (status >= 0) {
    status = dvsdk_grapx_display_exec_rpc(instID, g_RemoteStubContext.nInitFxnIdx);
  }
  return status;
}

Int dvsdk_grapx_display_rpc_start  (Int instID)
{
  Int status;
  
  Assert_isTrue((MultiProc_self() != MultiProc_getId("VPSS-M3")), Assert_E_assertFailed);
  status = dvsdk_grapx_display_rpc_remote_mode_init();
  if (status >= 0) {
    status = dvsdk_grapx_display_exec_rpc(instID, g_RemoteStubContext.nStartFxnIdx);
  }
  return status; 
}

Int dvsdk_grapx_display_rpc_stop   (Int instID)
{
  Int status;
    
  Assert_isTrue((MultiProc_self() != MultiProc_getId("VPSS-M3")), Assert_E_assertFailed);
  status = dvsdk_grapx_display_rpc_remote_mode_init();
  if (status >= 0) {
    status = dvsdk_grapx_display_exec_rpc(instID, g_RemoteStubContext.nStopFxnIdx);
  }
  return status;  
}

Int dvsdk_grapx_display_rpc_deinit (Int instID)
{
  Int status;
    
  Assert_isTrue((MultiProc_self() != MultiProc_getId("VPSS-M3")), Assert_E_assertFailed);
  status = dvsdk_grapx_display_rpc_remote_mode_init();
  if (status >= 0) {
    status = dvsdk_grapx_display_exec_rpc(instID, g_RemoteStubContext.nDeinitFxnIdx);
  }
  return status;  
}


Int dvsdk_grapx_display_rpc_display_toggle (Int instID)
{
  Int status;
    
  Assert_isTrue((MultiProc_self() != MultiProc_getId("VPSS-M3")), Assert_E_assertFailed);
  status = dvsdk_grapx_display_rpc_remote_mode_init();
  if (status >= 0) {
    status = dvsdk_grapx_display_exec_rpc(instID, g_RemoteStubContext.nDisplayToggelFxnIdx);
  }
  return status;  
}



/* EOF : grpx_display_rpc_if.c */

