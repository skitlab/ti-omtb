/*
 * omtbAppInit.h
 *
 * Platform specific application initialization function prototype
 * and datatype definitions.
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

/* OMX standard header files */
#include "OMX_Core.h"
#include "OMX_Component.h"
#include "OMX_Types.h"
#include "OMX_TI_Video.h"
#include "OMX_TI_Index.h"


/******************************************************************************\
 *      Customized Includes
\******************************************************************************/

#include "omtbDebug.h"
#include "timm_osal_interfaces.h"
#include "mxDbg.h"
#include "omtbMain.h"
#include "omtbCommon.h"
#include "omtbCmd.h"


/******************************************************************************\
 *      Local Defines
\******************************************************************************/


/******************************************************************************\
 *      Data type definitions
\******************************************************************************/

/* portEnableDisable function typedef */

typedef MX_Result (*portEnableDisableFuncPtrs)(unsigned int instanceNo,OMX_COMMANDTYPE commandType, int nParam , OMX_PTR pCmdData );

/*!
 *******************************************************************************
 *  \struct OMTB_PORT_ENABLE_DISABLE_FUNC
 *  \brief  Common structure containing function pointers used for port enable or
 *          disable
 *******************************************************************************
*/

typedef struct OMTB_PORT_ENABLE_DISABLE_FUNC_T
{
  char name[OMX_MAX_STRINGNAME_SIZE];
  portEnableDisableFuncPtrs fPtr;
} OMTB_PORT_ENABLE_DISABLE_FUNC;

/* setTemplateDefVal function typedef */
typedef MX_Result (*setTemplateDefValFuncPtrs)(OMTB_TEMPLATE_INFO *pTemplate);

/*!
 *******************************************************************************
 *  \struct OMTB_SET_DEF_VAL_TEMPLATE_FUNC
 *  \brief  Common structure containing function pointers used for all template 
 *          cfg
 *******************************************************************************
*/
typedef struct OMTB_SET_DEF_VAL_TEMPLATE_FUNC_T
{
  char name[OMX_MAX_STRINGNAME_SIZE];
  setTemplateDefValFuncPtrs fPtr;
} OMTB_SET_DEF_VAL_TEMPLATE_FUNC;


/******************************************************************************\
 *      Extern Object Definitions 
\******************************************************************************/


/******************************************************************************\
 *      Globals 
\******************************************************************************/


/******************************************************************************\
 *      Public Function Prototype
\******************************************************************************/


/******************************************************************************\
 *      Static Globals
\******************************************************************************/


/******************************************************************************\
 *      Public Function Declarations 
\******************************************************************************/

/******************************************************************************\
 *      OMTB_AppInit Function Definition
\******************************************************************************/
/*
 *
 *  @brief    
 *            This function initializes platform specific command entries
 *            and other initialization.
 *
 *  @param in:
 *            None
 *
 *  @param Out:
 *            None
 *
 *  @return   
 *            None
 */

void OMTB_AppInit();
/******************************************************************************\
 *      OMTB_GetPortEnableDisableFunc Function Prototype
\******************************************************************************/
/*
 *
 *  @brief
 *            This function gets component specific port enable/disable func
 *
 *  @param in:
 *            componentRequested: String contains component name
 *
 *  @param Out:
 *            portEnableDisableFuncPtrs component specific port enable/disble
 *
 *  @return
 *            portEnableDisableFuncPtrs component specific port enable/disble
 */
portEnableDisableFuncPtrs OMTB_GetPortEnableDisableFunc(char componentRequested[]);


/******************************************************************************\
 *      OMTB_InitTemplates Function Prototype
\******************************************************************************/
/*
 *
 *  @brief    
 *            This function initializes cfg templates.
 *
 *  @param in:
 *            pTemplate: Pointer to cfg template structure
 *
 *  @param Out:
 *            None
 *
 *  @return   
 *            None
 */

void OMTB_InitTemplates(OMTB_TEMPLATE_INFO *pTemplate);


/******************************************************************************\
 *      OMTB_InitSetpCmdList Function Prototype
\******************************************************************************/
/*
 *
 *  @brief    
 *            This function initializes setp command list.
 *
 *  @param in:
 *            None
 *
 *  @param Out:
 *            None
 *
 *  @return   
 *            None
 */

void OMTB_InitSetpCmdList();


/******************************************************************************\
 *      OMTB_InitFuncCmdList Function Prototype
\******************************************************************************/
/*
 *
 *  @brief    
 *            This function initializes func handler command list.
 *
 *  @param in:
 *            None
 *
 *  @param Out:
 *            None
 *
 *  @return   
 *            None
 */

void OMTB_InitFuncCmdList();


/******************************************************************************\
 *      OMTB_InitApiCmdList Function Prototype
\******************************************************************************/
/*
 *
 *  @brief    
 *            This function initializes API handler command list.
 *
 *  @param in:
 *            None
 *
 *  @param Out:
 *            None
 *
 *  @return   
 *            None
 */

void OMTB_InitApiCmdList();

/******************************************************************************\
 *      OMTB_InitApiTestCmdList Function Prototype
\******************************************************************************/
/*
 *
 *  @brief    
 *            This function initializes API handler command list.
 *
 *  @param in:
 *            None
 *
 *  @param Out:
 *            None
 *
 *  @return   
 *            None
 */

void OMTB_InitApiTestCmdList();


/******************************************************************************\
 *      OMTB_InitHelpStr Function Prototype
\******************************************************************************/
/*
 *
 *  @brief    
 *            This function initializes command help strings.
 *
 *  @param in:
 *            None
 *
 *  @param Out:
 *            None
 *
 *  @return   
 *            None
 */

void OMTB_InitHelpStr();


/*----------------------------- end of file ---------------------------------*/
