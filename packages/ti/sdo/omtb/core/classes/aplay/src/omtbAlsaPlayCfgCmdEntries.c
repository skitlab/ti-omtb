/*
 * omtbAlsaPlayCfgCmdEntries.c
 *
 * This file contains command entries for configuration parameters.
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
#include <xdc/runtime/Gate.h>

/* OMX standard header files */
#include "OMX_Core.h"
#include "OMX_Component.h"
#include "OMX_Types.h"


/******************************************************************************\
 *      Customized Includes
\******************************************************************************/

#include "mxDbg.h"
#include "omtbCommon.h"


/******************************************************************************\
 *      Local Defines
\******************************************************************************/


/******************************************************************************\
 *      Data type definitions
\******************************************************************************/


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
 *      Private Function Declarations
\******************************************************************************/

/*******************************************************************************
 *  OMTB component configuration parameter command entries - ALSAPLAY
 ******************************************************************************/

/*******************************************************************************
 *      ALSAPLAY config params
 ******************************************************************************/

/* Entry for Set No Of Channels */

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryAlsaPlayNoOfChannels =
{
  "nChannels",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_DEC      |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMTB_ALSAPLAY_CONFIG_PARAMS,nChannels),
  FIELDOFFSET(OMTB_ALSAPLAY_CONFIG_PARAMS,nChannels) -
  FIELDOFFSET(OMTB_ALSAPLAY_CONFIG_PARAMS,nChannels),
  0,
  0,
  OMTB_MAX_VAL_U32,
  OMTB_AUDIO_NUM_CHANNELS,
  NULL,
  XdbgCmdVarFunc,
  "No of Channeles...............................",
  "<nChannels>",
  "",
  ""
};


/* Entry for Set SamplingRate */

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryAlsaPlaySamplingRate =
{
  "nSamplingRate",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_DEC      |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMTB_ALSAPLAY_CONFIG_PARAMS,nSamplingRate),
  FIELDOFFSET(OMTB_ALSAPLAY_CONFIG_PARAMS,nSamplingRate) -
  FIELDOFFSET(OMTB_ALSAPLAY_CONFIG_PARAMS,nSamplingRate),
  0,
  0,
  OMTB_MAX_VAL_U32,
  OMTB_AUDIO_SAMPLING_RATE,
  NULL,
  XdbgCmdVarFunc,
  "Sampling Rate.................................",
  "<nSamplingRate>",
  "",
  ""
};

/* Entry for Set NumSamples */

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryAlsaPlayNumSamples =
{
  "nNumSamples",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_DEC      |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMTB_ALSAPLAY_CONFIG_PARAMS,nNumSamples),
  FIELDOFFSET(OMTB_ALSAPLAY_CONFIG_PARAMS,nNumSamples) -
  FIELDOFFSET(OMTB_ALSAPLAY_CONFIG_PARAMS,nNumSamples),
  0,
  0,
  OMTB_MAX_VAL_U32,
  OMTB_AUDIO_NUM_SAMPLES,
  NULL,
  XdbgCmdVarFunc,
  "Num of Samples................................",
  "<nNumSamples>",
  "",
  ""
};



/* Entry for Set AudioPort */

PRIVATE MX_DBG_CMD_ENTRY_T cmdEntryAlsaPlayAudioPort =
{
  "nAudioPort",
  MX_DBG_CMD_TYPE_VAR_UINT32,
  MX_DBG_CMD_OPT_INST_CUR     |
  MX_DBG_CMD_OPT_DEC      |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMTB_ALSAPLAY_CONFIG_PARAMS,nAudioPort),
  FIELDOFFSET(OMTB_ALSAPLAY_CONFIG_PARAMS,nAudioPort) -
  FIELDOFFSET(OMTB_ALSAPLAY_CONFIG_PARAMS,nAudioPort),
  0,
  0,
  OMTB_MAX_VAL_U32,
  OMTB_AUDIO_PORT,
  NULL,
  XdbgCmdVarFunc,
  "Audio Port....................................",
  "<nAudioPort>",
  "",
  ""
};

MX_DBG_CMD_ENTRY_T* cmdListAlsaPlayConfig[] =
{
  &cmdEntryAlsaPlayNoOfChannels,
  &cmdEntryAlsaPlaySamplingRate,
  &cmdEntryAlsaPlayNumSamples,
  &cmdEntryAlsaPlayAudioPort,
  NULL
};

/* AlsaPlay config command table */

MX_DBG_CMD_TABLE_T cmdTblAlsaPlayConfig =
{
  MX_DBG_ACCESS_ALL,
  sizeof(cmdListAlsaPlayConfig)/sizeof(cmdListAlsaPlayConfig[0]),
  cmdListAlsaPlayConfig
};


/* AlsaPlay config command entry */

MX_DBG_CMD_ENTRY_T cmdEntryAlsaPlayConfig =
{
  OMTB_ALSAPLAY_COMP_REF_STR,
  MX_DBG_CMD_TYPE_CMD_TABLE,
  MX_DBG_CMD_OPT_INST_CUR |
  MX_DBG_CMD_OPT_VALID_PTR,
  FIELDOFFSET(OMTB_TEMPLATE_INFO,alsaPlayTemplate),
  0,
  0,
  0,
  0,
  0,
  &cmdTblAlsaPlayConfig,
  XdbgCmdTblFunc,
  "\nAlsaPlay Config Parameters:\n",
  "",
  "",
  ""
};


/*----------------------------- end of file ---------------------------------*/
