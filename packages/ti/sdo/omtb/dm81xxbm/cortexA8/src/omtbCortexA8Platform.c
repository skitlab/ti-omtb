/*
 * omtbCortexA8Platform.c
 *
 * This file contains all Functions related to platform initialization
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

/*******************************************************************************
*                             Compilation Control Switches
*******************************************************************************/
/* None */

/* -------------------- system and platform files ----------------------------*/
#include <stdlib.h>
#include <xdc/std.h>
#include <string.h>
#include <xdc/runtime/System.h>
#include <xdc/runtime/Error.h>
#include <xdc/runtime/Assert.h>
#include <xdc/runtime/Diags.h>
#include <ti/timmosal/timm_osal_error.h>
#include <ti/timmosal/timm_osal_osal.h>
#include <ti/timmosal/timm_osal_trace.h>
#include <ti/omx/interfaces/openMaxv11/OMX_Types.h>
#include <ti/omx/interfaces/openMaxv11/OMX_Core.h>
#include <omx_vfdc.h>
#include <ti/omx/memcfg/memcfg.h>

/*-------------------------program files -------------------------------------*/
/* None */

/*******************************************************************************
 * EXTERNAL REFERENCES NOTE : only use if not found in header file
*******************************************************************************/

/*-----------------------data declarations -----------------------------------*/
/* None */

/*--------------------- function prototypes ----------------------------------*/
/* None */

/*******************************************************************************
 * PUBLIC DECLARATIONS Defined here, used elsewhere
 ******************************************************************************/

/*---------------------data declarations -------------------------------------*/
/* None */

/*---------------------function prototypes -----------------------------------*/
void platform_init (  );

void platform_deinit (  );

/*******************************************************************************
 * PRIVATE DECLARATIONS Defined here, used only here
 ******************************************************************************/

/*--------------------------- macros  ----------------------------------------*/
/*None */

/** 
********************************************************************************
 *  @fn     platform_init
 *  @brief  Calls various initialization routines for diffrent modules.
 *          
 *          Following modules are initialized. 
 *          OSAL, OMX core
 *
 *  @return none
********************************************************************************
*/
void platform_init (  )
{
  OMX_ERRORTYPE eError = OMX_ErrorUndefined;

  TIMM_OSAL_ERRORTYPE tStatus = TIMM_OSAL_ERR_NONE;

  /*--------------------------------------------------------------------------*/
  /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  /* Initialize the OSAL                                                      */
  /*                                                                          */
  /*--------------------------------------------------------------------------*/

  tStatus = TIMM_OSAL_Init (  );
  Assert_isTrue ( ( TIMM_OSAL_ERR_NONE == tStatus ), Assert_E_assertFailed );


  /*--------------------------------------------------------------------------*/
  /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  /* Initialize the OMX core                                                  */
  /*                                                                          */
  /*--------------------------------------------------------------------------*/
 // eError = OMX_Init (  );
 // Assert_isTrue ( ( OMX_ErrorNone == eError ), Assert_E_assertFailed );

  //MEMCFG_ModuleInit();

}/* platform_init */

void platform_deinit (  )
{
  TIMM_OSAL_ERRORTYPE tStatus = TIMM_OSAL_ERR_NONE;

  /*--------------------------------------------------------------------------*/
  /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  /* DeInitialize the OMX core                                                */
  /*                                                                          */
  /*--------------------------------------------------------------------------*/
  /*--------------------------------------------------------------------------*/
  /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
  /* DeInitialize the OMX core */
  /* */
  /*--------------------------------------------------------------------------*/
  /* This function performs de-initialization of shared regions and set the
     Module instance appropriately */

  //MEMCFG_ModuleDeInit ();
  /* deinitialized OMX core */

  //OMX_Deinit ();

  tStatus = TIMM_OSAL_Deinit (  );
  Assert_isTrue ( ( TIMM_OSAL_ERR_NONE == tStatus ), Assert_E_assertFailed );

}/* platform_deinit */
/* mmsw_platfor_vidm3.c - EOF */
