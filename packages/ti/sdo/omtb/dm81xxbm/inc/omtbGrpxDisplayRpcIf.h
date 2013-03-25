/*
 * omtbGrpxDisplayRpcIf.h
 *
 * This local header file contains structure definitions, function
 * Headers for the Graphic component.
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

#ifndef _GRPX_DISPLAY_RPC_IF_H
  #define _GRPX_DISPLAY_RPC_IF_H

#ifdef _cplusplus
extern "C"
{
#endif /* _cplusplus */

#include <stdio.h>
#include <xdc/std.h>
#include <xdc/runtime/System.h>

#define DVSDK_DSS_GRPX_SERVER_NAME       "GrpxRcmServer_DSS"
#define DVSDK_DSS_GRPX_INIT_FXN_NAME     "GrpxInit"
#define DVSDK_DSS_GRPX_START_FXN_NAME    "GrpxStart"
#define DVSDK_DSS_GRPX_STOP_FXN_NAME     "GrpxStop"
#define DVSDK_DSS_GRPX_DEINIT_FXN_NAME   "GrpxDeinit"
#define DVSDK_DSS_GRPX_DISPLAYTOGGLE_FXN_NAME "GrpxDispToggle"

#define GRPX_DRIVER_INSTANCEID_0          (0)
#define GRPX_DRIVER_INSTANCEID_1          (1)

Int dvsdk_grapx_display_rpc_init   (Int instID);
Int dvsdk_grapx_display_rpc_start  (Int instID);
Int dvsdk_grapx_display_rpc_stop   (Int instID);
Int dvsdk_grapx_display_rpc_deinit (Int instID);
Int dvsdk_grapx_display_rpc_display_toggle (Int instID);


#ifdef _cplusplus
}
#endif/* __cplusplus */

#endif /* _GRPX_DISPLAY_RPC_IF_H */

/* grpx_display_rpc_if.h - EOF */

