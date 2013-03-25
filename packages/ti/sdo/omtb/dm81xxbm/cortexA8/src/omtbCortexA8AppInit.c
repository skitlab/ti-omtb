/*
 * omtbCortexA8AppInit.c
 *
 * Platform specific initialization for application data structures.
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
#undef USE_LIBEDIT

#include <stdio.h>

/* OMX standard header files */
#include "OMX_Core.h"
#include "OMX_Component.h"
#include "OMX_Types.h"
//#include "OMX_TI_Video.h"
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
#include "omtbAppInit.h"
#include "omtbH264VdecApi.h"
#include "omtbH264VencApi.h"
#include "omtbVdecApi.h"
#include "omtbAdecApi.h"
#include "omtbHDVPSSVfccApi.h"
#include "omtbHDVPSSTvpApi.h"
#include "omtbHDVPSSVfdcApi.h"
#include "omtbHDVPSSDcApi.h"
#include "omtbHDVPSSVfpcDeiApi.h"
#include "omtbHDVPSSVfpcNfApi.h"
#include "omtbHDVPSSVfpcScApi.h"
#include "omtbH264VdecApiTest.h"
#include "omtbH264VencApiTest.h"

/******************************************************************************\
 *      Local Defines
\******************************************************************************/


/******************************************************************************\
 *      Data type definitions
\******************************************************************************/


/******************************************************************************\
 *      Extern Object Definitions
\******************************************************************************/


/* command table used for setp/getp/store cfg commands */
extern MX_DBG_CMD_TABLE_T   setpCmdTbl;

/* h264 vdec cfg command entry */
extern MX_DBG_CMD_ENTRY_T   cmdEntryH264VdecConfig;

/* h264 venc cfg command entry */
extern MX_DBG_CMD_ENTRY_T   cmdEntryH264VencConfig;

/* vdec cfg command entry */
extern MX_DBG_CMD_ENTRY_T   cmdEntryVdecConfig;

/* adec cfg command entry */
extern MX_DBG_CMD_ENTRY_T   cmdEntryAdecConfig;

/* vpss vfcc cfg command entry */
extern MX_DBG_CMD_ENTRY_T   cmdEntryVPSSVfccConfig;

/* vpss tvp cfg command entry */
extern MX_DBG_CMD_ENTRY_T   cmdEntryVPSSTvpConfig;

/* vpss vfdc cfg command entry */
extern MX_DBG_CMD_ENTRY_T   cmdEntryVPSSVfdcConfig;

/* vpss dc cfg command entry */
extern MX_DBG_CMD_ENTRY_T   cmdEntryVPSSDcConfig;

/* VPSS VFPC DEI cfg command entry */
extern MX_DBG_CMD_ENTRY_T   cmdEntryVPSSVfpcDeiConfig;

/* VPSS VFPC NF cfg command entry */
extern MX_DBG_CMD_ENTRY_T   cmdEntryVPSSVfpcNfConfig;

/* VPSS VFPC SC cfg command entry */
extern MX_DBG_CMD_ENTRY_T   cmdEntryVPSSVfpcScConfig;

/* alsarecord cfg command entry */
extern MX_DBG_CMD_ENTRY_T   cmdEntryAlsaRecordConfig;

/* alsaplay cfg command entry */
extern MX_DBG_CMD_ENTRY_T   cmdEntryAlsaPlayConfig;

/* Template params */
extern OMTB_TEMPLATE_INFO *omtbCfgTemplate[OMTB_MAX_INS];

/* setp command list entry */
extern MX_DBG_CMD_ENTRY_T* setpCmdList[OMTB_MAX_CLASS];

/* func command list entry */
extern MX_DBG_CMD_ENTRY_T* funcCmdList[OMTB_MAX_CLASS];

/* SendCommandMark command list */
extern MX_DBG_CMD_ENTRY_T* cmdListOmtbSendCommandMark[OMTB_MAX_CLASS];

/* viddec command list entry */
extern MX_DBG_CMD_ENTRY_T* viddecCmdList[OMTB_MAX_VIDDEC];

/* videnc command list entry */
extern MX_DBG_CMD_ENTRY_T* videncCmdList[OMTB_MAX_VIDENC];

/* vpss command list entry */
extern MX_DBG_CMD_ENTRY_T* vpssCmdList[OMTB_MAX_HDVPSS];

/* alsa command list entry */
extern MX_DBG_CMD_ENTRY_T* alsaCmdList[OMTB_MAX_ALSA];

/* Command entry for video decoder */
extern MX_DBG_CMD_ENTRY_T cmdEntryFuncVidDec;

/* Command entry for video encoders */
extern MX_DBG_CMD_ENTRY_T cmdEntryFuncVidEnc;

/* Command entry for HD VPSS VFDC */
extern MX_DBG_CMD_ENTRY_T cmdEntryFuncHdVpss;

/* Command entry for ALSA */
extern MX_DBG_CMD_ENTRY_T cmdEntryFuncAlsa;

extern MX_DBG_CMD_ENTRY_T cmdEntryOmtbSendCommandMarkH264Vdec;
extern MX_DBG_CMD_ENTRY_T cmdEntryOmtbSendCommandMarkH264Venc;
extern MX_DBG_CMD_ENTRY_T cmdEntryOmtbSendCommandMarkVdec;
extern MX_DBG_CMD_ENTRY_T cmdEntryOmtbSendCommandMarkAdec;
extern MX_DBG_CMD_ENTRY_T cmdEntryOmtbSendCommandMarkVPSSVfcc;
extern MX_DBG_CMD_ENTRY_T cmdEntryOmtbSendCommandMarkVPSSVfdc;
extern MX_DBG_CMD_ENTRY_T cmdEntryOmtbSendCommandMarkVPSSVfpcDei;
extern MX_DBG_CMD_ENTRY_T cmdEntryOmtbSendCommandMarkVPSSVfpcNf;
extern MX_DBG_CMD_ENTRY_T cmdEntryOmtbSendCommandMarkVPSSVfpcSc;

/* Command entry for video decoder */
extern MX_DBG_CMD_ENTRY_T cmdEntryFuncH264Vdec;

/* Command entry for video encoder */
extern MX_DBG_CMD_ENTRY_T cmdEntryFuncH264Venc;

/* Command entry for video decoder */
extern MX_DBG_CMD_ENTRY_T cmdEntryFuncVdec;

/* Command entry for audio decoder */
extern MX_DBG_CMD_ENTRY_T cmdEntryFuncAdec;

/* Command entry for vfcc */
extern MX_DBG_CMD_ENTRY_T cmdEntryFuncVPSSVfcc;

/* Command entry for tvp */
//extern MX_DBG_CMD_ENTRY_T cmdEntryFuncVPSSTvp;

/* Command entry for vfcc */
extern MX_DBG_CMD_ENTRY_T cmdEntryFuncVPSSVfdc;

/* Command entry for VPSS VFPC DEI */
extern MX_DBG_CMD_ENTRY_T cmdEntryFuncVPSSVfpcDei;

/* Command entry for VPSS VFPC NF */
extern MX_DBG_CMD_ENTRY_T cmdEntryFuncVPSSVfpcNf;

/* Command entry for VPSS VFPC SC */
extern MX_DBG_CMD_ENTRY_T cmdEntryFuncVPSSVfpcSc;
/* Command entry for ALSA Record */
extern MX_DBG_CMD_ENTRY_T cmdEntryAlsaRecordFunc;

/* Command entry for ALSA Play */
extern MX_DBG_CMD_ENTRY_T cmdEntryAlsaPlayFunc;

/* component specific command entries for API testing */
//extern MX_DBG_CMD_ENTRY_T cmdEntryOmxH264VdecAllocUseBufferTest;
extern MX_DBG_CMD_ENTRY_T cmdEntryOmxH264VencAllocUseBufferTest;

extern MX_DBG_CMD_ENTRY_T cmdEntryOmxH264VdecFreeBufferTest;
extern MX_DBG_CMD_ENTRY_T cmdEntryOmxH264VencFreeBufferTest;

extern MX_DBG_CMD_ENTRY_T cmdEntryOmxH264VdecSetParamTest;
extern MX_DBG_CMD_ENTRY_T cmdEntryOmxH264VencSetParamTest;

extern MX_DBG_CMD_ENTRY_T cmdEntryOmxH264VdecSetConfigTest;
extern MX_DBG_CMD_ENTRY_T cmdEntryOmxH264VencSetConfigTest;

extern MX_DBG_CMD_ENTRY_T cmdEntryOmxH264VdecGetParamTest;
extern MX_DBG_CMD_ENTRY_T cmdEntryOmxH264VencGetParamTest;

extern MX_DBG_CMD_ENTRY_T cmdEntryOmxH264VdecGetConfigTest;
extern MX_DBG_CMD_ENTRY_T cmdEntryOmxH264VencGetConfigTest;

extern MX_DBG_CMD_ENTRY_T cmdEntryOmxH264VdecEmptyThisBufferTest;
extern MX_DBG_CMD_ENTRY_T cmdEntryOmxH264VencEmptyThisBufferTest;

extern MX_DBG_CMD_ENTRY_T cmdEntryOmxH264VdecFillThisBufferTest;
extern MX_DBG_CMD_ENTRY_T cmdEntryOmxH264VencFillThisBufferTest;


/* alloc/use buffer command list */
extern MX_DBG_CMD_ENTRY_T* cmdListOmtbAllocUseBufferTest[OMTB_MAX_CLASS];

/* free buffer command list */
extern MX_DBG_CMD_ENTRY_T* cmdListOmtbFreeBufferTest[OMTB_MAX_CLASS];

/* SetParam command list */
extern MX_DBG_CMD_ENTRY_T* cmdListOmtbSetParamTest[OMTB_MAX_CLASS];

/* SetConfig command list */
extern MX_DBG_CMD_ENTRY_T* cmdListOmtbSetConfigTest[OMTB_MAX_CLASS];

/* SetParam command list */
extern MX_DBG_CMD_ENTRY_T* cmdListOmtbGetParamTest[OMTB_MAX_CLASS];

/* SetConfig command list */
extern MX_DBG_CMD_ENTRY_T* cmdListOmtbGetConfigTest[OMTB_MAX_CLASS];

/* empty this buffer command list */
extern MX_DBG_CMD_ENTRY_T* cmdListOmtbEmptyThisBufferTest[OMTB_MAX_CLASS];

/* fill this buffer command list */
extern MX_DBG_CMD_ENTRY_T* cmdListOmtbFillThisBufferTest[OMTB_MAX_CLASS];

/******************************************************************************\
 *      Globals
\******************************************************************************/

/* Function pointers used to set cfg template values */
OMTB_SET_DEF_VAL_TEMPLATE_FUNC omtbSetTemplateDefValFuncPtrs[OMTB_MAX_CLASS] =
{
  {OMTB_H264_VDEC_COMP_REF_STR, H264VDEC_SetTemplateDefVal},
  {OMTB_H264_VENC_COMP_REF_STR, H264VENC_SetTemplateDefVal},
  {OMTB_VDEC_COMP_REF_STR, VDEC_SetTemplateDefVal},  
  {OMTB_ADEC_COMP_REF_STR, ADEC_SetTemplateDefVal},  
  {OMTB_VPSS_VFCC_COMP_REF_STR, VPSSVFCC_SetTemplateDefVal},
  {OMTB_VPSS_TVP_COMP_REF_STR,  VPSSTVP_SetTemplateDefVal},
  {OMTB_VPSS_VFDC_COMP_REF_STR, VPSSVFDC_SetTemplateDefVal},
  {OMTB_VPSS_DC_COMP_REF_STR, VPSSDC_SetTemplateDefVal},
  {OMTB_VPSS_VFPC_DEI_COMP_REF_STR, VPSSVFPCDEI_SetTemplateDefVal},
  {OMTB_VPSS_VFPC_NF_COMP_REF_STR, VPSSVFPCNF_SetTemplateDefVal},
  {OMTB_VPSS_VFPC_SC_COMP_REF_STR, VPSSVFPCSC_SetTemplateDefVal},
  {OMTB_ALSARECORD_COMP_REF_STR, ALSARECORD_SetTemplateDefVal},  
  {OMTB_ALSAPLAY_COMP_REF_STR, ALSAPLAY_SetTemplateDefVal}, 
  {NULL, NULL}
};

/* setp command list entry for initialization */

PRIVATE MX_DBG_CMD_ENTRY_T* setpCmdListInit[OMTB_MAX_CLASS] =
{
  &cmdEntryH264VdecConfig,
  &cmdEntryH264VencConfig,
  &cmdEntryVdecConfig,  
  &cmdEntryAdecConfig,    
  &cmdEntryVPSSVfccConfig,
  &cmdEntryVPSSTvpConfig,
  &cmdEntryVPSSVfdcConfig,
  &cmdEntryVPSSDcConfig,
  &cmdEntryVPSSVfpcDeiConfig,
  &cmdEntryVPSSVfpcNfConfig,
  &cmdEntryVPSSVfpcScConfig,
  &cmdEntryAlsaRecordConfig,
  &cmdEntryAlsaPlayConfig, 
  NULL
};

/* func command list entry for initialization */

PRIVATE MX_DBG_CMD_ENTRY_T* funcCmdListInit[OMTB_MAX_CLASS] =
{
  &cmdEntryFuncVidDec,
  &cmdEntryFuncVidEnc,
  &cmdEntryFuncHdVpss,
  &cmdEntryFuncAlsa,
  NULL,
  NULL
};


/* SendCommandMark command list */
MX_DBG_CMD_ENTRY_T* cmdListOmtbSendCommandMarkInit[OMTB_MAX_CLASS] =
{
  &cmdEntryOmtbSendCommandMarkH264Vdec,
  &cmdEntryOmtbSendCommandMarkH264Venc,
  &cmdEntryOmtbSendCommandMarkVdec,
  &cmdEntryOmtbSendCommandMarkAdec,  
  &cmdEntryOmtbSendCommandMarkVPSSVfcc,
  &cmdEntryOmtbSendCommandMarkVPSSVfdc,
  &cmdEntryOmtbSendCommandMarkVPSSVfpcDei,
  &cmdEntryOmtbSendCommandMarkVPSSVfpcNf,
  &cmdEntryOmtbSendCommandMarkVPSSVfpcSc,
  NULL
};


/* viddec command list entry */

MX_DBG_CMD_ENTRY_T* viddecCmdListInit[OMTB_MAX_VIDDEC] =
{
  &cmdEntryFuncH264Vdec,
  &cmdEntryFuncVdec,  
  NULL
};


/* videnc command list entry */

MX_DBG_CMD_ENTRY_T* videncCmdListInit[OMTB_MAX_VIDENC] =
{
  &cmdEntryFuncH264Venc,
  NULL
};


/* vpss command list entry */

MX_DBG_CMD_ENTRY_T* vpssCmdListInit[OMTB_MAX_HDVPSS] =
{
  &cmdEntryFuncVPSSVfcc,
  //&cmdEntryFuncVPSSTvp,
  &cmdEntryFuncVPSSVfdc,
  &cmdEntryFuncVPSSVfpcDei,
  &cmdEntryFuncVPSSVfpcNf,
  &cmdEntryFuncVPSSVfpcSc,
  NULL
};

MX_DBG_CMD_ENTRY_T* alsaCmdListInit[OMTB_MAX_ALSA] =
{
  &cmdEntryAlsaRecordFunc,
  &cmdEntryAlsaPlayFunc,
  NULL
};


/******************************************************************************\
 *      Public Function Prototype
\******************************************************************************/


/******************************************************************************\
 *      Static Globals
\******************************************************************************/


/******************************************************************************\
 *      Private Function Declarations
\******************************************************************************/


/******************************************************************************\
 *      Function Definitions
\******************************************************************************/

/******************************************************************************\
 *      OMTB_InitViddecCmdList Function Definition
\******************************************************************************/
/*
 *
 *  @brief
 *            This function initializes class handler command list.
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

static void OMTB_InitViddecCmdList()
{
  int i = 0;

  /* Initialize viddec func cmd list entries */
  for(i = 0; i < (OMTB_MAX_VIDDEC - 1); i++)
  {
    if(NULL != viddecCmdListInit[i])
    {
      viddecCmdList[i] = viddecCmdListInit[i];

    }  // if(NULL != viddecCmdListInit[i])

  }  // for(i = 0; i < (OMTB_MAX_VIDDEC - 1); i++)

  /* Set the last entry to NULL */
  viddecCmdList[i] = NULL;

}

/******************************************************************************\
 *      OMTB_InitVidencCmdList Function Definition
\******************************************************************************/
/*
 *
 *  @brief
 *            This function initializes class handler command list.
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

static void OMTB_InitVidencCmdList()
{
  int i = 0;

  /* Initialize videnc func cmd list entries */
  for(i = 0; i < (OMTB_MAX_VIDENC - 1); i++)
  {
    if(NULL != videncCmdListInit[i])
    {
      videncCmdList[i] = videncCmdListInit[i];

    }  // if(NULL != videncCmdListInit[i])

  }  // for(i = 0; i < (OMTB_MAX_VIDENC - 1); i++)

  /* Set the last entry to NULL */
  videncCmdList[i] = NULL;

}


/******************************************************************************\
 *      OMTB_InitHdvpssCmdList Function Definition
\******************************************************************************/
/*
 *
 *  @brief
 *            This function initializes class handler command list.
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

static void OMTB_InitHdvpssCmdList()
{
  int i = 0;

  /* Initialize vpss func cmd list entries */
  for(i = 0; i < (OMTB_MAX_HDVPSS - 1); i++)
  {
    if(NULL != vpssCmdListInit[i])
    {
      vpssCmdList[i] = vpssCmdListInit[i];

    }  // if(NULL != vpssCmdListInit[i])

  }  // for(i = 0; i < (OMTB_MAX_HDVPSS - 1); i++)

  /* Set the last entry to NULL */
  vpssCmdList[i] = NULL;

}


/******************************************************************************\
 *      OMTB_InitAlsaCmdList Function Definition
\******************************************************************************/
/*
 *
 *  @brief
 *            This function initializes class handler command list.
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

static void OMTB_InitAlsaCmdList()
{
  int i = 0;

  /* Initialize alsa func cmd list entries */
  for(i = 0; i < (OMTB_MAX_ALSA - 1); i++)
  {
    if(NULL != alsaCmdListInit[i])
    {
      alsaCmdList[i] = alsaCmdListInit[i];

    }  // if(NULL != alsaCmdListInit[i])

  }  // for(i = 0; i < (OMTB_MAX_ALSA - 1); i++)

  /* Set the last entry to NULL */
  alsaCmdList[i] = NULL;

}

/******************************************************************************\
 *      OMTB_InitTemplates Function Definition
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

void OMTB_InitTemplates(OMTB_TEMPLATE_INFO *pTemplate)
{
  int i = 0;
  MX_Result result = ERR_NOERR;

  /* Initialize template cfg params */
  for(i = 0; i < (OMTB_MAX_CLASS - 1); i++)
  {
    if(NULL != omtbSetTemplateDefValFuncPtrs[i].fPtr)
    {
      result = omtbSetTemplateDefValFuncPtrs[i].fPtr(pTemplate);
      if(ERR_NOERR != result)
      {
        PRINT(PRINT_ERR_MSG, "%s: Error in initializing %s template \n",
        __FUNCTION__, omtbSetTemplateDefValFuncPtrs[i].name);

      }  // if(ERR_NOERR != result)

    }  // if(NULL != omtbSetTemplateDefValFuncPtrs[i].fPtr)

  }  // for(i = 0; i < (OMTB_MAX_CLASS - 1); i++)
}


/******************************************************************************\
 *      OMTB_InitSetpCmdList Function Definition
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

void OMTB_InitSetpCmdList()
{
  int i = 0;

  /* Initialize setp cmd list entries */
  for(i = 0; i < (OMTB_MAX_CLASS - 1); i++)
  {
    if(NULL != setpCmdListInit[i])
    {
      setpCmdList[i] = setpCmdListInit[i];

    }  // if(NULL != setpCmdListInit[i])

  }  // for(i = 0; i < (OMTB_MAX_CLASS - 1); i++)

  /* Set the last entry to NULL */
  setpCmdList[i] = NULL;
}


/******************************************************************************\
 *      OMTB_InitFuncCmdList Function Definition
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

void OMTB_InitFuncCmdList()
{
  int i = 0;

  /* Initialize func cmd list entries */
  for(i = 0; i < (OMTB_MAX_CLASS - 1); i++)
  {
    if(NULL != funcCmdListInit[i])
    {
      funcCmdList[i] = funcCmdListInit[i];

    }  // if(NULL != funcCmdListInit[i])

  }  // for(i = 0; i < (OMTB_MAX_CLASS - 1); i++)

  /* Set the last entry to NULL */
  funcCmdList[i] = NULL;

  /* Initialize individual class entries */
  OMTB_InitViddecCmdList();
  OMTB_InitVidencCmdList();
  OMTB_InitHdvpssCmdList();
  OMTB_InitAlsaCmdList();
}


/******************************************************************************\
 *      OMTB_InitApiCmdList Function Definition
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

void OMTB_InitApiCmdList()
{
  int i = 0;

  /* Initialize API cmd list entries */
  for(i = 0; i < (OMTB_MAX_CLASS - 1); i++)
  {
    cmdListOmtbSendCommandMark[i] = cmdListOmtbSendCommandMarkInit[i];
  }  // for(i = 0; i < (OMTB_MAX_CLASS - 1); i++)

  /* Set the last entry to NULL */
  cmdListOmtbSendCommandMark[i] = NULL;

}


/******************************************************************************\
 *      OMTB_InitHelpStr Function Definition
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

void OMTB_InitHelpStr()
{

}


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

void OMTB_AppInit()
{

#ifdef CEDEBUG
  GT_setprintf( (GT_PrintFxn)printf );
  GT_set( "*+01234567,GT_prefix=1235,GT_time=0" );
#endif

  /* Invoke the different initialization functions */
  OMTB_InitSetpCmdList();
  OMTB_InitFuncCmdList();
  OMTB_InitApiCmdList();
  //OMTB_InitApiTestCmdList();
  OMTB_InitHelpStr();
}


/*----------------------------- end of file ----------------------------------*/
