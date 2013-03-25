/*
 * omtbDisplayParams.c
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

#include <xdc/std.h>
#include <xdc/runtime/Assert.h>
#include <xdc/runtime/Gate.h>
#include <xdc/runtime/knl/Thread.h>
#include <xdc/runtime/Timestamp.h>

/* OMX standard header files */
#include "OMX_Core.h"
#include "OMX_Component.h"
#include "OMX_Types.h"
#include "OMX_TI_Index.h"
#include "omx_vfdc.h"
//#include "omx_vfdc_priv.h"
#include "domx_util.h"
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

#define PRINT_PARAM(n, args...) if ((PRINT_LEVEL | omtbDbgLogLevel) & (n))  \
                            {                                           \
                              fprintf(stdout,"   "args);                    \
                            }
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
 *      Static Globals
\******************************************************************************/

/******************************************************************************\
 *      Public Function Prototypes
\******************************************************************************/

/******************************************************************************\
 *      Private Function Prototypes
\******************************************************************************/
void OMTBBASE_DisplayGetParams(unsigned int nParamIndex, OMX_PTR pCompCfgStruct);
void OMTBBASE_DisplaySetParams(unsigned int nParamIndex, OMX_PTR pCompCfgStruct);

/******************************************************************************\
 *      Function Definitions
\******************************************************************************/

/******************************************************************************\
 *      OMTB_DisplaySetParams Function Prototype
\******************************************************************************/
/**
 *
 *  @brief    This Function print the values of the index on output console/file
 *
 *  @param    nParamIndex
 *            pCompCfgStruct
 *
 *  @return   None
 */
void OMTB_DisplaySetParams(unsigned int nParamIndex, OMX_PTR pCompCfgStruct)
{
 unsigned int i = 0;
 unsigned int j = 0;
 
 switch (nParamIndex)
 {
   /* Add VFCC/TVP component indexes here*/
   case OMX_TI_IndexParamVFCCHwPortID:
     {
       OMX_PARAM_VFCC_HWPORT_ID *pParamStruct = (OMX_PARAM_VFCC_HWPORT_ID *)pCompCfgStruct;       	

       PRINT_PARAM(PRINT_SET_PARAM, "\n \rOMX_TI_IndexParamVFCCHwPortID:\n");
	   PRINT_PARAM(PRINT_SET_PARAM, "nSize..................%d\n", (int)pParamStruct->nSize);
       PRINT_PARAM(PRINT_SET_PARAM, "nVersion...............%d\n", (int)pParamStruct->nVersion.nVersion);
       PRINT_PARAM(PRINT_SET_PARAM, "nPortIndex.............%d\n", (int)pParamStruct->nPortIndex);
       PRINT_PARAM(PRINT_SET_PARAM, "eHwPortId => port_id...%d\n", (int)pParamStruct->eHwPortId);
     }
     break;

   case OMX_TI_IndexParamVFCCHwPortProperties:
     {
       OMX_PARAM_VFCC_HWPORT_PROPERTIES *pParamStruct = (OMX_PARAM_VFCC_HWPORT_PROPERTIES *)pCompCfgStruct;       	
       
       PRINT_PARAM(PRINT_SET_PARAM, "\n \rOMX_TI_IndexParamVFCCHwPortProperties:\n");	   
	   PRINT_PARAM(PRINT_SET_PARAM, "nSize......................................%d\n",
                          (int)pParamStruct->nSize);
       PRINT_PARAM(PRINT_SET_PARAM, "nVersion...................................%d\n",
                          (int)pParamStruct->nVersion.nVersion);
       PRINT_PARAM(PRINT_SET_PARAM, "nPortIndex.................................%d\n",
                          (int)pParamStruct->nPortIndex);
       PRINT_PARAM(PRINT_SET_PARAM, "eCaptMode => cap_mode......................%d\n",
                          (int)pParamStruct->eCaptMode);
       PRINT_PARAM(PRINT_SET_PARAM, "eVifMode => vif_mode.......................%d\n",
                          (int)pParamStruct->eVifMode);
       PRINT_PARAM(PRINT_SET_PARAM, "eInColorFormat => cap_color_format.........%d\n",
                          (int)pParamStruct->eInColorFormat);
       PRINT_PARAM(PRINT_SET_PARAM, "eScanType => cap_scan_type.................%d\n",
                  	      (int)pParamStruct->eScanType);
       PRINT_PARAM(PRINT_SET_PARAM, "nMaxWidth => cap_width.....................%d\n",
                          (int)pParamStruct->nMaxWidth);
       PRINT_PARAM(PRINT_SET_PARAM, "nMaxHeight => cap_height...................%d\n",
                          (int)pParamStruct->nMaxHeight);
       PRINT_PARAM(PRINT_SET_PARAM, "nMaxChnlsPerHwPort => max_chan_per_port....%d\n",
                          (int)pParamStruct->nMaxChnlsPerHwPort);
	   
     }
     break;
  
   case OMX_TI_IndexParamCTRLVidDecInfo:
     {
       OMX_PARAM_CTRL_VIDDECODER_INFO *pParamStruct = (OMX_PARAM_CTRL_VIDDECODER_INFO *)pCompCfgStruct;       	
      
       PRINT_PARAM(PRINT_SET_PARAM, "\n \rOMX_TI_IndexParamCTRLVidDecInfo:\n");		  
	   PRINT_PARAM(PRINT_SET_PARAM, "nSize............................%d\n", (int)pParamStruct->nSize);
       PRINT_PARAM(PRINT_SET_PARAM, "nVersion.........................%d\n", (int)pParamStruct->nVersion.nVersion);
       PRINT_PARAM(PRINT_SET_PARAM, "nPortIndex.......................%d\n", (int)pParamStruct->nPortIndex);
       PRINT_PARAM(PRINT_SET_PARAM, "videoStandard => tvp_dec_std.....%d\n", (int)pParamStruct->videoStandard);
       PRINT_PARAM(PRINT_SET_PARAM, "videoDecoderId => tvp_dec_id.....%d\n", (int)pParamStruct->videoDecoderId);
     }
     break;	 
   
   case OMX_IndexConfigVFCCPortResetStats:
     {
       OMX_CONFIG_VIDEO_CAPTURE_RESET_STATS *pParamStruct = 
	                     (OMX_CONFIG_VIDEO_CAPTURE_RESET_STATS *)pCompCfgStruct;       	
       
	   PRINT_PARAM(PRINT_SET_PARAM, "\n \rOMX_IndexConfigVFCCPortResetStats:\n");	       
	   PRINT_PARAM(PRINT_SET_PARAM, "nSize............................%d\n", (int)pParamStruct->nSize);
       PRINT_PARAM(PRINT_SET_PARAM, "nVersion.........................%d\n", (int)pParamStruct->nVersion.nVersion);
       PRINT_PARAM(PRINT_SET_PARAM, "nPortIndex.......................%d\n", (int)pParamStruct->nPortIndex);
     }
     break;	 

   case OMX_TI_IndexConfigVFCCFrameSkip:
     {
       OMX_CONFIG_VFCC_FRAMESKIP_INFO *pParamStruct = (OMX_CONFIG_VFCC_FRAMESKIP_INFO *)pCompCfgStruct;       	

	   PRINT_PARAM(PRINT_SET_PARAM, "\n \rOMX_TI_IndexConfigVFCCFrameSkip:\n");	        
	   PRINT_PARAM(PRINT_SET_PARAM, "nSize.................................%d\n", (int)pParamStruct->nSize);
       PRINT_PARAM(PRINT_SET_PARAM, "nVersion..............................%d\n", (int)pParamStruct->nVersion.nVersion);
       PRINT_PARAM(PRINT_SET_PARAM, "nPortIndex............................%d\n", (int)pParamStruct->nPortIndex);
       PRINT_PARAM(PRINT_SET_PARAM, "frameSkipMask => frame_skip_mask......%d\n", (int)pParamStruct->frameSkipMask);
     }
     break;	 
   
   /* Add VFPC DEI/NF/SC component indexes here*/
   case OMX_TI_IndexParamVFPCNumChPerHandle:
     {
       OMX_PARAM_VFPC_NUMCHANNELPERHANDLE *pParamStruct = (OMX_PARAM_VFPC_NUMCHANNELPERHANDLE *)pCompCfgStruct;       	
       
	   PRINT_PARAM(PRINT_SET_PARAM, "\n \rOMX_TI_IndexParamVFPCNumChPerHandle:\n");	 	   
	   PRINT_PARAM(PRINT_SET_PARAM, "nSize...........................................%d\n",
                         (int)pParamStruct->nSize);
       PRINT_PARAM(PRINT_SET_PARAM, "nVersion........................................%d\n",
                         (int)pParamStruct->nVersion.nVersion);
       PRINT_PARAM(PRINT_SET_PARAM, "nPortIndex......................................%d\n",
                  	     (int)pParamStruct->nPortIndex);
       PRINT_PARAM(PRINT_SET_PARAM, "nNumChannelsPerHandle => num_chan_per_handle....%d\n",
                        (int)pParamStruct->nNumChannelsPerHandle);
     }
     break;
	 
   case OMX_TI_IndexConfigSubSamplingFactor:
     {
       OMX_CONFIG_SUBSAMPLING_FACTOR *pParamStruct = (OMX_CONFIG_SUBSAMPLING_FACTOR *)pCompCfgStruct;       	

	   PRINT_PARAM(PRINT_SET_PARAM, "\n \rOMX_TI_IndexConfigSubSamplingFactor:\n");	        
	   PRINT_PARAM(PRINT_SET_PARAM, "nSize...........................................%d\n",
                         (int)pParamStruct->nSize);
       PRINT_PARAM(PRINT_SET_PARAM, "nVersion........................................%d\n",
                         (int)pParamStruct->nVersion.nVersion);
       PRINT_PARAM(PRINT_SET_PARAM, "nPortIndex......................................%d\n",
                  	     (int)pParamStruct->nPortIndex);
       PRINT_PARAM(PRINT_SET_PARAM, "nSubSamplingFactor => sub_samp_factor...........%d\n",
                        (int)pParamStruct->nSubSamplingFactor);	 
	 }
	 break;
	 
   case OMX_TI_IndexConfigVidChResolution:
     {
       OMX_CONFIG_VIDCHANNEL_RESOLUTION *pParamStruct = (OMX_CONFIG_VIDCHANNEL_RESOLUTION *)pCompCfgStruct;       	

	   PRINT_PARAM(PRINT_SET_PARAM, "\n \rOMX_TI_IndexConfigVidChResolution:\n");	      	   
	   PRINT_PARAM(PRINT_SET_PARAM, "nSize................................................%d\n",
	                     (int)pParamStruct->nSize);
       PRINT_PARAM(PRINT_SET_PARAM, "nVersion.............................................%d\n",
	                     (int)pParamStruct->nVersion.nVersion);
       PRINT_PARAM(PRINT_SET_PARAM, "nPortIndex...........................................%d\n",
	                     (int)pParamStruct->nPortIndex);
       PRINT_PARAM(PRINT_SET_PARAM, "eDir => vidChResolutionCfgeDir.......................%d\n",
	                     (int)pParamStruct->eDir);
       PRINT_PARAM(PRINT_SET_PARAM, "nChId => vidChResolutionCfgnChId.....................%d\n",
	                     (int)pParamStruct->nChId);
       PRINT_PARAM(PRINT_SET_PARAM, "Frm0Width => vidChResolutionCfgFrm0Width.............%d\n",
	                     (int)pParamStruct->Frm0Width);
       PRINT_PARAM(PRINT_SET_PARAM, "Frm0Height => vidChResolutionCfgFrm0Height...........%d\n",
	                     (int)pParamStruct->Frm0Height);
       PRINT_PARAM(PRINT_SET_PARAM, "Frm0Pitch => vidChResolutionCfgFrm0Pitch.............%d\n",
	                     (int)pParamStruct->Frm0Pitch);
       PRINT_PARAM(PRINT_SET_PARAM, "Frm1Width => vidChResolutionCfgFrm1Width.............%d\n",
	                     (int)pParamStruct->Frm1Width);
       PRINT_PARAM(PRINT_SET_PARAM, "Frm1Height => vidChResolutionCfgFrm1Height...........%d\n",
	                     (int)pParamStruct->Frm1Height);
       PRINT_PARAM(PRINT_SET_PARAM, "Frm1Pitch => vidChResolutionCfgFrm1Pitch.............%d\n",
	                     (int)pParamStruct->Frm1Pitch);
       PRINT_PARAM(PRINT_SET_PARAM, "FrmStartX => vidChResolutionCfgFrmStartX.............%d\n",
	                     (int)pParamStruct->FrmStartX);
       PRINT_PARAM(PRINT_SET_PARAM, "FrmStartY => vidChResolutionCfgFrmStartY.............%d\n",
	                     (int)pParamStruct->FrmStartY);
       PRINT_PARAM(PRINT_SET_PARAM, "FrmCropWidth => vidChResolutionCfgFrmCropWidth.......%d\n", 
	                     (int)pParamStruct->FrmCropWidth);
       PRINT_PARAM(PRINT_SET_PARAM, "FrmCropHeight => vidChResolutionCfgFrmCropHeight.....%d\n",
               	         (int)pParamStruct->FrmCropHeight);
    }	 
	 break;
 
   case OMX_TI_IndexConfigAlgEnable:
     {
       OMX_CONFIG_ALG_ENABLE *pParamStruct = (OMX_CONFIG_ALG_ENABLE *)pCompCfgStruct;       	

  	   PRINT_PARAM(PRINT_SET_PARAM, "\n \rOMX_TI_IndexConfigAlgEnable:\n");	        
	   PRINT_PARAM(PRINT_SET_PARAM, "nSize.................................%d\n", (int)pParamStruct->nSize);
       PRINT_PARAM(PRINT_SET_PARAM, "nVersion..............................%d\n", (int)pParamStruct->nVersion.nVersion);
       PRINT_PARAM(PRINT_SET_PARAM, "nPortIndex............................%d\n", (int)pParamStruct->nPortIndex);
       PRINT_PARAM(PRINT_SET_PARAM, "nChId => algEnablenChId...............%d\n", (int)pParamStruct->nChId);
       PRINT_PARAM(PRINT_SET_PARAM, "bAlgBypass => algEnablebAlgBypass.....%d\n", (int)pParamStruct->bAlgBypass);
     }
     break;     
   
   /* Add VFDC/DC component indexes here*/
   case OMX_TI_IndexParamVFDCDriverInstId:
     {
       OMX_PARAM_VFDC_DRIVERINSTID *pParamStruct = (OMX_PARAM_VFDC_DRIVERINSTID *)pCompCfgStruct;       	

  	   PRINT_PARAM(PRINT_SET_PARAM, "\n \rOMX_TI_IndexParamVFDCDriverInstId:\n");		   
	   PRINT_PARAM(PRINT_SET_PARAM, "nSize............................%d\n", (int)pParamStruct->nSize);
       PRINT_PARAM(PRINT_SET_PARAM, "nVersion.........................%d\n", (int)pParamStruct->nVersion.nVersion);
       PRINT_PARAM(PRINT_SET_PARAM, "nPortIndex.......................%d\n", (int)pParamStruct->nPortIndex);
       PRINT_PARAM(PRINT_SET_PARAM, "nDrvInstID => dvr_inst_id........%d\n", (int)pParamStruct->nDrvInstID);
       PRINT_PARAM(PRINT_SET_PARAM, "eDispVencMode => disp_venc_mode..%d\n", (int)pParamStruct->eDispVencMode);
     }
     break;

   case OMX_TI_IndexParamVFDCCreateMosaicLayout:
     {
       OMX_PARAM_VFDC_CREATEMOSAICLAYOUT *pParamStruct = (OMX_PARAM_VFDC_CREATEMOSAICLAYOUT *)pCompCfgStruct;       	

  	   PRINT_PARAM(PRINT_SET_PARAM, "\n \rOMX_TI_IndexParamVFDCCreateMosaicLayout:\n");	       
	   PRINT_PARAM(PRINT_SET_PARAM, "nSize.......................................%d\n", (int)pParamStruct->nSize);
       PRINT_PARAM(PRINT_SET_PARAM, "nVersion....................................%d\n", (int)pParamStruct->nVersion.nVersion);
       PRINT_PARAM(PRINT_SET_PARAM, "nPortIndex..................................%d\n", (int)pParamStruct->nPortIndex);
       PRINT_PARAM(PRINT_SET_PARAM, "nDisChannelNum..............................%d\n", (int)pParamStruct->nDisChannelNum);
       PRINT_PARAM(PRINT_SET_PARAM, "nLayoutId => mosaic_layout_id...............%d\n", (int)pParamStruct->nLayoutId);
       PRINT_PARAM(PRINT_SET_PARAM, "nNumWindows => mosaicNumRows,mosaicNumCols..%d\n", (int)pParamStruct->nNumWindows);
	   
	   PRINT_PARAM(PRINT_SET_PARAM, "\n \nsMosaicWinFmt for each mosaic window:\n");	   
	   for(i = 0; i < (int)pParamStruct->nNumWindows; i++)
	   {
	     PRINT_PARAM(PRINT_SET_PARAM, "*************Mosaic Window: %d*************\n", i);
   	     PRINT_PARAM(PRINT_SET_PARAM, "winStartX => mosaic_start_x...............%d\n", (int)pParamStruct->sMosaicWinFmt[i].winStartX);
   	     PRINT_PARAM(PRINT_SET_PARAM, "winStartY => mosaic_start_y...............%d\n", (int)pParamStruct->sMosaicWinFmt[i].winStartY);
   	     PRINT_PARAM(PRINT_SET_PARAM, "winWidth => mosaicFrameWidth..............%d\n", (int)pParamStruct->sMosaicWinFmt[i].winWidth);
   	     PRINT_PARAM(PRINT_SET_PARAM, "winHeight => mosaicFrameHeight............%d\n", (int)pParamStruct->sMosaicWinFmt[i].winHeight);
		 
		 PRINT_PARAM(PRINT_SET_PARAM, "pitch => mosaicFramePitchYUV422I444I,mosaicFramePitchY420SP,\
		                    mosaicFramePitchUV420SP..");
		 for(j = 0;  j < VFDC_MAX_PLANES; j++)
		  PRINT_PARAM(PRINT_SET_PARAM, "%d ", (int)pParamStruct->sMosaicWinFmt[i].pitch[j]);
		 PRINT_PARAM(PRINT_SET_PARAM, "\n");
		  
   	     PRINT_PARAM(PRINT_SET_PARAM, "dataFormat => mosaicDataFormat............%d\n", (int)pParamStruct->sMosaicWinFmt[i].dataFormat);
   	     PRINT_PARAM(PRINT_SET_PARAM, "bpp => mosaic_bpp.........................%d\n", (int)pParamStruct->sMosaicWinFmt[i].bpp);
   	     PRINT_PARAM(PRINT_SET_PARAM, "priority => mosaic_priority...............%d\n", (int)pParamStruct->sMosaicWinFmt[i].priority);
	     PRINT_PARAM(PRINT_SET_PARAM, "Misc:\n  mosaicDispWindowHeight \n  mosaicDispWindowHeight\n");	 
	   } 	 

     }
     break;	
	 
   case OMX_TI_IndexConfigVFDCMosaicPort2WinMap:
     {
       OMX_CONFIG_VFDC_MOSAICLAYOUT_PORT2WINMAP *pParamStruct = (OMX_CONFIG_VFDC_MOSAICLAYOUT_PORT2WINMAP *)pCompCfgStruct;       	

  	   PRINT_PARAM(PRINT_SET_PARAM, "\n \rOMX_TI_IndexConfigVFDCMosaicPort2WinMap:\n");	        
	   PRINT_PARAM(PRINT_SET_PARAM, "nSize.............%d\n", (int)pParamStruct->nSize);
       PRINT_PARAM(PRINT_SET_PARAM, "nVersion..........%d\n", (int)pParamStruct->nVersion.nVersion);
       PRINT_PARAM(PRINT_SET_PARAM, "nPortIndex........%d\n", (int)pParamStruct->nPortIndex);
       PRINT_PARAM(PRINT_SET_PARAM, "nLayoutId.........%d\n", (int)pParamStruct->nLayoutId);
       PRINT_PARAM(PRINT_SET_PARAM, "numWindows........%d\n", (int)pParamStruct->numWindows);
	   PRINT_PARAM(PRINT_SET_PARAM, "omxPortList.......");	   
	   for(i = 0; i < (int)pParamStruct->numWindows; i++)
	     PRINT_PARAM(PRINT_SET_PARAM, "%d ", (int)pParamStruct->omxPortList[i]);
       PRINT_PARAM(PRINT_SET_PARAM, "\n");
     }
     break;	


   /* Add VENC component indexes here*/
   case OMX_IndexParamVideoInit:
     {
       OMX_PORT_PARAM_TYPE *pParamStruct = (OMX_PORT_PARAM_TYPE *)pCompCfgStruct;
	   
  	   PRINT_PARAM(PRINT_SET_PARAM, "\n \rOMX_IndexParamVideoInit:\n");	    	   
       PRINT_PARAM(PRINT_SET_PARAM, "nSize.................................%d\n", (int)pParamStruct->nSize);
       PRINT_PARAM(PRINT_SET_PARAM, "nVersion..............................%d\n", (int)pParamStruct->nVersion.nVersion);
	   PRINT_PARAM(PRINT_SET_PARAM, "nPorts => no_of_ports.................%d\n", (int)pParamStruct->nPorts);
	   PRINT_PARAM(PRINT_SET_PARAM, "nStartPortNumber => start_port_num....%d\n", (int)pParamStruct->nStartPortNumber);	 
	 }
	 break;

   case OMX_IndexParamPortDefinition:
     {
#if 0 //To be implemented      
  	   OMX_CONFIG_CHANNELNAME *pParamStruct = (OMX_CONFIG_CHANNELNAME *)pCompCfgStruct;
	   
  	   PRINT_PARAM(PRINT_SET_PARAM, "\n \rOMX_IndexParamPortDefinition:\n");	   	   
       PRINT_PARAM(PRINT_SET_PARAM, "nSize..................%d\n", (int)pParamStruct->nSize);
       PRINT_PARAM(PRINT_SET_PARAM, "nVersion...............%d\n", (int)pParamStruct->nVersion.nVersion);
       PRINT_PARAM(PRINT_SET_PARAM, "nPortIndex.............%d\n", (int)pParamStruct->nPortIndex);
       PRINT_PARAM(PRINT_SET_PARAM, "cChannelName...........%s\n", pParamStruct->cChannelName);	 
#endif	   
	 }
	 break;

   case OMX_IndexParamVideoPortFormat:
     {
       OMX_VIDEO_PARAM_PORTFORMATTYPE *pParamStruct = (OMX_VIDEO_PARAM_PORTFORMATTYPE *)pCompCfgStruct;       	

  	   PRINT_PARAM(PRINT_SET_PARAM, "\n \rOMX_IndexParamVideoPortFormat:\n");	       
	   PRINT_PARAM(PRINT_SET_PARAM, "nSize...........................................%d\n", (int)pParamStruct->nSize);
       PRINT_PARAM(PRINT_SET_PARAM, "nVersion........................................%d\n", (int)pParamStruct->nVersion.nVersion);
       PRINT_PARAM(PRINT_SET_PARAM, "nPortIndex......................................%d\n", (int)pParamStruct->nPortIndex);
       PRINT_PARAM(PRINT_SET_PARAM, "nIndex => Param not Supported for setparm.......%d\n", (int)pParamStruct->nIndex);
       PRINT_PARAM(PRINT_SET_PARAM, "eCompressionFormat => ip_compression_format/op_compression_format\n");
       PRINT_PARAM(PRINT_SET_PARAM, "................................................%d\n", (int)pParamStruct->eCompressionFormat);
       PRINT_PARAM(PRINT_SET_PARAM, "eColorFormat => ip_chromat_format/op_chromat_format\n");
       PRINT_PARAM(PRINT_SET_PARAM, "................................................%d\n", (int)pParamStruct->eColorFormat);
       PRINT_PARAM(PRINT_SET_PARAM, "xFramerate => frame_rate........................%d\n", (int)pParamStruct->xFramerate); 
	 }
	 break;

   case OMX_IndexParamVideoBitrate:
     {
       OMX_VIDEO_PARAM_BITRATETYPE *pParamStruct = (OMX_VIDEO_PARAM_BITRATETYPE *)pCompCfgStruct;

  	   PRINT_PARAM(PRINT_SET_PARAM, "\n \rOMX_IndexParamVideoBitrate:\n");		   
	   PRINT_PARAM(PRINT_SET_PARAM, "nSize............................%d\n", (int)pParamStruct->nSize);
       PRINT_PARAM(PRINT_SET_PARAM, "nVersion.........................%d\n", (int)pParamStruct->nVersion.nVersion);
       PRINT_PARAM(PRINT_SET_PARAM, "nPortIndex.......................%d\n", (int)pParamStruct->nPortIndex);
       PRINT_PARAM(PRINT_SET_PARAM, "eControlRate => rate_ctrl_alg....%d\n", (int)pParamStruct->eControlRate);
       PRINT_PARAM(PRINT_SET_PARAM, "nTargetBitrate => target_bitrate.%d\n", (int)pParamStruct->nTargetBitrate); 
	 }
	 break;	 
	 
   case OMX_IndexParamVideoAvc:	 
     {
       OMX_VIDEO_PARAM_AVCTYPE *pParamStruct = (OMX_VIDEO_PARAM_AVCTYPE *)pCompCfgStruct;

  	   PRINT_PARAM(PRINT_SET_PARAM, "\n \rOMX_IndexParamVideoAvc:\n");	       
	   PRINT_PARAM(PRINT_SET_PARAM, "nSize...........................................%d\n", (int)pParamStruct->nSize);
       PRINT_PARAM(PRINT_SET_PARAM, "nVersion........................................%d\n", (int)pParamStruct->nVersion.nVersion);
       PRINT_PARAM(PRINT_SET_PARAM, "nPortIndex......................................%d\n", (int)pParamStruct->nPortIndex);
       PRINT_PARAM(PRINT_SET_PARAM, "nSliceHeaderSpacing => slice_hdr_space..........%d\n", (int)pParamStruct->nSliceHeaderSpacing);
       PRINT_PARAM(PRINT_SET_PARAM, "nPFrames => max_p_frms .........................%d\n", (int)pParamStruct->nPFrames);
       PRINT_PARAM(PRINT_SET_PARAM, "nBFrames => max_b_frms..........................%d\n", (int)pParamStruct->nBFrames);
       PRINT_PARAM(PRINT_SET_PARAM, "bUseHadamard => use_hadamard....................%d\n", (int)pParamStruct->bUseHadamard);
       PRINT_PARAM(PRINT_SET_PARAM, "nRefFrames => num_ref_frms......................%d\n", (int)pParamStruct->nRefFrames);
       PRINT_PARAM(PRINT_SET_PARAM, "nRefIdx10ActiveMinus1 => ref_idx_10_bwd_list....%d\n", (int)pParamStruct->nRefIdx10ActiveMinus1);
       PRINT_PARAM(PRINT_SET_PARAM, "nRefIdx11ActiveMinus1 => ref_idx_11_fwd_list....%d\n", (int)pParamStruct->nRefIdx11ActiveMinus1);
       PRINT_PARAM(PRINT_SET_PARAM, "bEnableUEP => uep...............................%d\n", (int)pParamStruct->bEnableUEP);
       PRINT_PARAM(PRINT_SET_PARAM, "bEnableFMO => fmo...............................%d\n", (int)pParamStruct->bEnableFMO);
       PRINT_PARAM(PRINT_SET_PARAM, "bEnableASO => aso...............................%d\n", (int)pParamStruct->bEnableASO);
       PRINT_PARAM(PRINT_SET_PARAM, "bEnableRS => rs.................................%d\n", (int)pParamStruct->bEnableRS);
       PRINT_PARAM(PRINT_SET_PARAM, "eProfile => avc_profile.........................%d\n", (int)pParamStruct->eProfile);
       PRINT_PARAM(PRINT_SET_PARAM, "eLevel => avc_level.............................%d\n", (int)pParamStruct->eLevel);
       PRINT_PARAM(PRINT_SET_PARAM, "nAllowedPictureTypes => allowed_pic_type........%d\n", (int)pParamStruct->nAllowedPictureTypes);
       PRINT_PARAM(PRINT_SET_PARAM, "bFrameMBsOnly => frm_mbs_only...................%d\n", (int)pParamStruct->bFrameMBsOnly);
       PRINT_PARAM(PRINT_SET_PARAM, "bMBAFF => mbaff.................................%d\n", (int)pParamStruct->bMBAFF);
       PRINT_PARAM(PRINT_SET_PARAM, "bEntropyCodingCABAC => cabac....................%d\n", (int)pParamStruct->bEntropyCodingCABAC);
       PRINT_PARAM(PRINT_SET_PARAM, "bWeightedPPrediction => weight_pred.............%d\n", (int)pParamStruct->bWeightedPPrediction);
       PRINT_PARAM(PRINT_SET_PARAM, "nWeightedBipredicitonMode => weighted_bipred_mode.%d\n", (int)pParamStruct->nWeightedBipredicitonMode);
       PRINT_PARAM(PRINT_SET_PARAM, "bconstIpred => const_intra_pred.................%d\n", (int)pParamStruct->bconstIpred);
       PRINT_PARAM(PRINT_SET_PARAM, "bDirect8x8Inference => dir_8x8_ref..............%d\n", (int)pParamStruct->bDirect8x8Inference);
       PRINT_PARAM(PRINT_SET_PARAM, "bDirectSpatialTemporal => dir_spatial_temporal..%d\n", (int)pParamStruct->bDirectSpatialTemporal);
       PRINT_PARAM(PRINT_SET_PARAM, "nCabacInitIdc => cabac_init_idx.................%d\n", (int)pParamStruct->nCabacInitIdc);
       PRINT_PARAM(PRINT_SET_PARAM, "eLoopFilterMode => loop_filter..................%d\n", (int)pParamStruct->eLoopFilterMode);		 
	 }
     break;	 
	
   case OMX_IndexParamVideoMotionVector:	 
     {
       OMX_VIDEO_PARAM_MOTIONVECTORTYPE *pParamStruct = (OMX_VIDEO_PARAM_MOTIONVECTORTYPE *)pCompCfgStruct; 	 

  	   PRINT_PARAM(PRINT_SET_PARAM, "\n \rOMX_IndexParamVideoMotionVector:\n");       
	   PRINT_PARAM(PRINT_SET_PARAM, "nSize.......................%d\n", (int)pParamStruct->nSize);
       PRINT_PARAM(PRINT_SET_PARAM, "nVersion....................%d\n", (int)pParamStruct->nVersion.nVersion);
       PRINT_PARAM(PRINT_SET_PARAM, "nPortIndex..................%d\n", (int)pParamStruct->nPortIndex);
       PRINT_PARAM(PRINT_SET_PARAM, "eAccuracy => mvaccuracy.....%d\n", (int)pParamStruct->eAccuracy);
       PRINT_PARAM(PRINT_SET_PARAM, "bUnrestrictedMVs => umv.....%d\n", (int)pParamStruct->bUnrestrictedMVs);
       PRINT_PARAM(PRINT_SET_PARAM, "bFourMV => four_mv..........%d\n", (int)pParamStruct->bFourMV);
       PRINT_PARAM(PRINT_SET_PARAM, "sXSearchRange => mvx_sr.....%d\n", (int)pParamStruct->sXSearchRange);
       PRINT_PARAM(PRINT_SET_PARAM, "sYSearchRange => mvy_sr.....%d\n", (int)pParamStruct->sYSearchRange);	
	 }
     break;	 

   case OMX_IndexParamVideoQuantization:
     {
       OMX_VIDEO_PARAM_QUANTIZATIONTYPE *pParamStruct = (OMX_VIDEO_PARAM_QUANTIZATIONTYPE *)pCompCfgStruct; 	 
       
  	   PRINT_PARAM(PRINT_SET_PARAM, "\n \rOMX_IndexParamVideoQuantization:\n");   	   
	   PRINT_PARAM(PRINT_SET_PARAM, "nSize..................%d\n", (int)pParamStruct->nSize);
       PRINT_PARAM(PRINT_SET_PARAM, "nVersion...............%d\n", (int)pParamStruct->nVersion.nVersion);
       PRINT_PARAM(PRINT_SET_PARAM, "nPortIndex.............%d\n", (int)pParamStruct->nPortIndex);
       PRINT_PARAM(PRINT_SET_PARAM, "nQpI => qpi............%d\n", (int)pParamStruct->nQpI);
       PRINT_PARAM(PRINT_SET_PARAM, "nQpP => qpp............%d\n", (int)pParamStruct->nQpP);
       PRINT_PARAM(PRINT_SET_PARAM, "nQpB => qpb............%d\n", (int)pParamStruct->nQpB);	
	 }
     break;	   
	
   case OMX_IndexParamVideoSliceFMO:
     {
       OMX_VIDEO_PARAM_AVCSLICEFMO *pParamStruct = (OMX_VIDEO_PARAM_AVCSLICEFMO *)pCompCfgStruct; 	 

  	   PRINT_PARAM(PRINT_SET_PARAM, "\n \rOMX_IndexParamVideoSliceFMO:\n");        
	   PRINT_PARAM(PRINT_SET_PARAM, "nSize.................................%d\n", (int)pParamStruct->nSize);
       PRINT_PARAM(PRINT_SET_PARAM, "nVersion..............................%d\n", (int)pParamStruct->nVersion.nVersion);
       PRINT_PARAM(PRINT_SET_PARAM, "nPortIndex............................%d\n", (int)pParamStruct->nPortIndex);
       PRINT_PARAM(PRINT_SET_PARAM, "nNumSliceGroups => num_slice_grp......%d\n", (int)pParamStruct->nNumSliceGroups);
       PRINT_PARAM(PRINT_SET_PARAM, "nSliceGroupMapType => slice_grp_map...%d\n", (int)pParamStruct->nSliceGroupMapType);
       PRINT_PARAM(PRINT_SET_PARAM, "eSliceMode => slice_mode..............%d\n", (int)pParamStruct->eSliceMode);	
	 }
     break;	 
  
   case OMX_IndexParamVideoIntraRefresh:
     {
       OMX_VIDEO_PARAM_INTRAREFRESHTYPE *pParamStruct = (OMX_VIDEO_PARAM_INTRAREFRESHTYPE *)pCompCfgStruct; 	 
      
  	   PRINT_PARAM(PRINT_SET_PARAM, "\n \rOMX_IndexParamVideoIntraRefresh:\n"); 	  
	   PRINT_PARAM(PRINT_SET_PARAM, "nSize.................................%d\n", (int)pParamStruct->nSize);
       PRINT_PARAM(PRINT_SET_PARAM, "nVersion..............................%d\n", (int)pParamStruct->nVersion.nVersion);
       PRINT_PARAM(PRINT_SET_PARAM, "nPortIndex............................%d\n", (int)pParamStruct->nPortIndex);
       PRINT_PARAM(PRINT_SET_PARAM, "eRefreshMode => intra_refresh_mode....%d\n", (int)pParamStruct->eRefreshMode);
       PRINT_PARAM(PRINT_SET_PARAM, "nAirMBs => intra_refresh_airmb........%d\n", (int)pParamStruct->nAirMBs);
       PRINT_PARAM(PRINT_SET_PARAM, "nAirRef => intra_refresh_airref.......%d\n", (int)pParamStruct->nAirRef);
       PRINT_PARAM(PRINT_SET_PARAM, "nCirMBs => intra_refresh_cirmb........%d\n", (int)pParamStruct->nCirMBs);	
	 }
     break;	   
  
   case OMX_IndexParamVideoProfileLevelCurrent:
     {
       OMX_VIDEO_PARAM_PROFILELEVELTYPE *pParamStruct = (OMX_VIDEO_PARAM_PROFILELEVELTYPE *)pCompCfgStruct; 	 

  	   PRINT_PARAM(PRINT_SET_PARAM, "\n \rOMX_IndexParamVideoIntraRefresh:\n"); 	       
	   PRINT_PARAM(PRINT_SET_PARAM, "nSize.......................%d\n", (int)pParamStruct->nSize);
       PRINT_PARAM(PRINT_SET_PARAM, "nVersion....................%d\n", (int)pParamStruct->nVersion.nVersion);
       PRINT_PARAM(PRINT_SET_PARAM, "nPortIndex..................%d\n", (int)pParamStruct->nPortIndex);
       PRINT_PARAM(PRINT_SET_PARAM, "eProfile => profile.........%d\n", (int)pParamStruct->eProfile);
       PRINT_PARAM(PRINT_SET_PARAM, "eLevel => level.............%d\n", (int)pParamStruct->eLevel);
       PRINT_PARAM(PRINT_SET_PARAM, "nProfileIndex...............(?)%d\n", (int)pParamStruct->nProfileIndex);	
	 }
     break;	   
	
   case OMX_TI_IndexParamVideoDataSyncMode:
     {
       OMX_VIDEO_PARAM_DATASYNCMODETYPE *pParamStruct = (OMX_VIDEO_PARAM_DATASYNCMODETYPE *)pCompCfgStruct; 	 

  	   PRINT_PARAM(PRINT_SET_PARAM, "\n \rOMX_TI_IndexParamVideoDataSyncMode:\n");        
	   PRINT_PARAM(PRINT_SET_PARAM, "nSize.................................%d\n", (int)pParamStruct->nSize);
       PRINT_PARAM(PRINT_SET_PARAM, "nVersion..............................%d\n", (int)pParamStruct->nVersion.nVersion);
       PRINT_PARAM(PRINT_SET_PARAM, "nPortIndex............................%d\n", (int)pParamStruct->nPortIndex);
       PRINT_PARAM(PRINT_SET_PARAM, "eDataMode => vid_data_mode............%d\n", (int)pParamStruct->eDataMode);
       PRINT_PARAM(PRINT_SET_PARAM, "nNumDataUnits => vid_num_data_unit....%d\n", (int)pParamStruct->nNumDataUnits);	
	 }
     break;	 
	
   case OMX_TI_IndexParamVideoBitStreamFormatSelect:
     {
       OMX_VIDEO_PARAM_AVCBITSTREAMFORMATTYPE *pParamStruct = (OMX_VIDEO_PARAM_AVCBITSTREAMFORMATTYPE *)pCompCfgStruct; 	 

  	   PRINT_PARAM(PRINT_SET_PARAM, "\n \rOMX_TI_IndexParamVideoBitStreamFormatSelect:\n");         
	   PRINT_PARAM(PRINT_SET_PARAM, "nSize............................%d\n", (int)pParamStruct->nSize);
       PRINT_PARAM(PRINT_SET_PARAM, "nVersion.........................%d\n", (int)pParamStruct->nVersion.nVersion);
       PRINT_PARAM(PRINT_SET_PARAM, "nPortIndex.......................%d\n", (int)pParamStruct->nPortIndex);
       PRINT_PARAM(PRINT_SET_PARAM, "eStreamFormat => bitstrm_fmt.....%d\n", (int)pParamStruct->eStreamFormat);		
	 }
     break;	  
	
   case OMX_TI_IndexParamVideoNALUsettings:
     {
       OMX_VIDEO_PARAM_AVCNALUCONTROLTYPE *pParamStruct = (OMX_VIDEO_PARAM_AVCNALUCONTROLTYPE *)pCompCfgStruct; 	 
       
  	   PRINT_PARAM(PRINT_SET_PARAM, "\n \rOMX_TI_IndexParamVideoNALUsettings:\n");  	   
	   PRINT_PARAM(PRINT_SET_PARAM, "nSize.................................%d\n", (int)pParamStruct->nSize);
       PRINT_PARAM(PRINT_SET_PARAM, "nVersion..............................%d\n", (int)pParamStruct->nVersion.nVersion);
       PRINT_PARAM(PRINT_SET_PARAM, "nPortIndex............................%d\n", (int)pParamStruct->nPortIndex);
       PRINT_PARAM(PRINT_SET_PARAM, "nStartofSequence => nalu_sos..........%d\n", (int)pParamStruct->nStartofSequence);
       PRINT_PARAM(PRINT_SET_PARAM, "nEndofSequence => nalu_eos............%d\n", (int)pParamStruct->nEndofSequence);
       PRINT_PARAM(PRINT_SET_PARAM, "nIDR => nalu_idr......................%d\n", (int)pParamStruct->nIDR);
       PRINT_PARAM(PRINT_SET_PARAM, "nIntraPicture => nalu_intra...........%d\n", (int)pParamStruct->nIntraPicture);
       PRINT_PARAM(PRINT_SET_PARAM, "nNonIntraPicture => nalu_nonintra.....%d\n", (int)pParamStruct->nNonIntraPicture);	
	 }
     break;	   
   
   case OMX_TI_IndexParamVideoMEBlockSize:
     {
       OMX_VIDEO_PARAM_MEBLOCKSIZETYPE *pParamStruct = (OMX_VIDEO_PARAM_MEBLOCKSIZETYPE *)pCompCfgStruct; 	 

  	   PRINT_PARAM(PRINT_SET_PARAM, "\n \rOMX_TI_IndexParamVideoMEBlockSize:\n");         
	   PRINT_PARAM(PRINT_SET_PARAM, "nSize.................................%d\n", (int)pParamStruct->nSize);
       PRINT_PARAM(PRINT_SET_PARAM, "nVersion..............................%d\n", (int)pParamStruct->nVersion.nVersion);
       PRINT_PARAM(PRINT_SET_PARAM, "nPortIndex............................%d\n", (int)pParamStruct->nPortIndex);
       PRINT_PARAM(PRINT_SET_PARAM, "eMinBlockSizeP => me_min_blk_sizep....%d\n", (int)pParamStruct->eMinBlockSizeP);
       PRINT_PARAM(PRINT_SET_PARAM, "eMinBlockSizeB => me_min_blk_sizeb....%d\n", (int)pParamStruct->eMinBlockSizeB);	
 	 }
     break;	   
	
   case OMX_TI_IndexParamVideoIntraPredictionSettings:
     {
       OMX_VIDEO_PARAM_INTRAPREDTYPE *pParamStruct = (OMX_VIDEO_PARAM_INTRAPREDTYPE *)pCompCfgStruct; 	 
       
  	   PRINT_PARAM(PRINT_SET_PARAM, "\n \rOMX_TI_IndexParamVideoIntraPredictionSettings:\n");  	   
	   PRINT_PARAM(PRINT_SET_PARAM, "nSize................................................%d\n", (int)pParamStruct->nSize);
       PRINT_PARAM(PRINT_SET_PARAM, "nVersion.............................................%d\n", (int)pParamStruct->nVersion.nVersion);
       PRINT_PARAM(PRINT_SET_PARAM, "nPortIndex...........................................%d\n", (int)pParamStruct->nPortIndex);
       PRINT_PARAM(PRINT_SET_PARAM, "nLumaIntra4x4Enable => luma_intra_4x4_pred_mode......%d\n", (int)pParamStruct->nLumaIntra4x4Enable);
       PRINT_PARAM(PRINT_SET_PARAM, "nLumaIntra8x8Enable => luma_intra_8x8_pred_mode......%d\n", (int)pParamStruct->nLumaIntra8x8Enable);
       PRINT_PARAM(PRINT_SET_PARAM, "nLumaIntra16x16Enable => luma_intra_16x16_pred_mode..%d\n", (int)pParamStruct->nLumaIntra16x16Enable);
       PRINT_PARAM(PRINT_SET_PARAM, "nChromaIntra8x8Enable => chroma_intra_8x8_pred_mode..%d\n", (int)pParamStruct->nChromaIntra8x8Enable);
       PRINT_PARAM(PRINT_SET_PARAM, "eChromaComponentEnable =>chroma_intra_pred_comp......%d\n", (int)pParamStruct->eChromaComponentEnable);	
	 }
     break;	   
	
   case OMX_TI_IndexParamVideoEncoderPreset:
     {
       OMX_VIDEO_PARAM_ENCODER_PRESETTYPE *pParamStruct = (OMX_VIDEO_PARAM_ENCODER_PRESETTYPE *)pCompCfgStruct; 	 
       
  	   PRINT_PARAM(PRINT_SET_PARAM, "\n \rOMX_TI_IndexParamVideoEncoderPreset:\n");  	   
	   PRINT_PARAM(PRINT_SET_PARAM, "nSize......................................%d\n", (int)pParamStruct->nSize);
       PRINT_PARAM(PRINT_SET_PARAM, "nVersion...................................%d\n", (int)pParamStruct->nVersion.nVersion);
       PRINT_PARAM(PRINT_SET_PARAM, "nPortIndex.................................%d\n", (int)pParamStruct->nPortIndex);
       PRINT_PARAM(PRINT_SET_PARAM, "eEncodingModePreset => enc_preset..........%d\n", (int)pParamStruct->eEncodingModePreset);
       PRINT_PARAM(PRINT_SET_PARAM, "eRateControlPreset => rate_ctrl_preset.....%d\n", (int)pParamStruct->eRateControlPreset);	
	 }
     break;	   
	
   case OMX_TI_IndexParamVideoFrameDataContentSettings:
     {
       OMX_VIDEO_PARAM_FRAMEDATACONTENTTYPE *pParamStruct = (OMX_VIDEO_PARAM_FRAMEDATACONTENTTYPE *)pCompCfgStruct; 	 
       
  	   PRINT_PARAM(PRINT_SET_PARAM, "\n \rOMX_TI_IndexParamVideoFrameDataContentSettings:\n"); 	   
	   PRINT_PARAM(PRINT_SET_PARAM, "nSize...........................................%d\n", (int)pParamStruct->nSize);
       PRINT_PARAM(PRINT_SET_PARAM, "nVersion........................................%d\n", (int)pParamStruct->nVersion.nVersion);
       PRINT_PARAM(PRINT_SET_PARAM, "nPortIndex......................................%d\n", (int)pParamStruct->nPortIndex);
       PRINT_PARAM(PRINT_SET_PARAM, "eContentType => content_type....................%d\n", (int)pParamStruct->eContentType);
       PRINT_PARAM(PRINT_SET_PARAM, "eInterlaceCodingType => interlaced_coding_type..%d\n", (int)pParamStruct->eInterlaceCodingType);	
	 }
     break;	   
	
  case OMX_TI_IndexParamVideoTransformBlockSize:
     {
       OMX_VIDEO_PARAM_TRANSFORM_BLOCKSIZETYPE *pParamStruct = (OMX_VIDEO_PARAM_TRANSFORM_BLOCKSIZETYPE *)pCompCfgStruct; 	 

  	   PRINT_PARAM(PRINT_SET_PARAM, "\n \rOMX_TI_IndexParamVideoTransformBlockSize:\n");       
	   PRINT_PARAM(PRINT_SET_PARAM, "nSize.................................%d\n", (int)pParamStruct->nSize);
       PRINT_PARAM(PRINT_SET_PARAM, "nVersion..............................%d\n", (int)pParamStruct->nVersion.nVersion);
       PRINT_PARAM(PRINT_SET_PARAM, "nPortIndex............................%d\n", (int)pParamStruct->nPortIndex);
       PRINT_PARAM(PRINT_SET_PARAM, "eTransformBlocksize => dct_blk_size...%d\n", (int)pParamStruct->eTransformBlocksize);	
	 }
     break;	   
	
   case OMX_TI_IndexParamVideoVUIsettings:
     {
       OMX_VIDEO_PARAM_VUIINFOTYPE *pParamStruct = (OMX_VIDEO_PARAM_VUIINFOTYPE *)pCompCfgStruct; 	 

  	   PRINT_PARAM(PRINT_SET_PARAM, "\n \rOMX_TI_IndexParamVideoVUIsettings:\n");          
	   PRINT_PARAM(PRINT_SET_PARAM, "nSize...........................................%d\n", (int)pParamStruct->nSize);
       PRINT_PARAM(PRINT_SET_PARAM, "nVersion........................................%d\n", (int)pParamStruct->nVersion.nVersion);
       PRINT_PARAM(PRINT_SET_PARAM, "nPortIndex......................................%d\n", (int)pParamStruct->nPortIndex);
       PRINT_PARAM(PRINT_SET_PARAM, "bAspectRatioPresent => vui_aspect_ratio_flag....%d\n", (int)pParamStruct->bAspectRatioPresent);
       PRINT_PARAM(PRINT_SET_PARAM, "ePixelAspectRatio => vui_pixel_aspect_ratio.....%d\n", (int)pParamStruct->ePixelAspectRatio);
       PRINT_PARAM(PRINT_SET_PARAM, "bFullRange => vui_full_range_flag...............%d\n", (int)pParamStruct->bFullRange);	
	 }
     break;	   
	
   case OMX_TI_IndexParamVideoAdvancedFMO:
     {
       OMX_VIDEO_PARAM_AVCADVANCEDFMOTYPE *pParamStruct = (OMX_VIDEO_PARAM_AVCADVANCEDFMOTYPE *)pCompCfgStruct; 	 

  	   PRINT_PARAM(PRINT_SET_PARAM, "\n \rOMX_TI_IndexParamVideoAdvancedFMO:\n");         
	   PRINT_PARAM(PRINT_SET_PARAM, "nSize................................................%d\n", (int)pParamStruct->nSize);
       PRINT_PARAM(PRINT_SET_PARAM, "nVersion.............................................%d\n", (int)pParamStruct->nVersion.nVersion);
       PRINT_PARAM(PRINT_SET_PARAM, "nPortIndex...........................................%d\n", (int)pParamStruct->nPortIndex);
       PRINT_PARAM(PRINT_SET_PARAM, "nNumSliceGroups => fmo_num_slice_grp.................%d\n", (int)pParamStruct->nNumSliceGroups);
       PRINT_PARAM(PRINT_SET_PARAM, "nSliceGroupMapType => fmo_slice_grp_map_type.........%d\n", (int)pParamStruct->nSliceGroupMapType);
       PRINT_PARAM(PRINT_SET_PARAM, "eSliceGrpChangeDir => fmo_slice_grp_chng_dir.........%d\n", (int)pParamStruct->eSliceGrpChangeDir);
       PRINT_PARAM(PRINT_SET_PARAM, "nSliceGroupChangeRate => fmo_slice_grp_chng_rate.....%d\n", (int)pParamStruct->nSliceGroupChangeRate);
       PRINT_PARAM(PRINT_SET_PARAM, "nSliceGroupChangeCycle =>fmo_slice_grp_chng_cycle....%d\n", (int)pParamStruct->nSliceGroupChangeCycle);	
	 }
     break;	   

   case OMX_IndexConfigVideoBitrate:
     {
       OMX_VIDEO_CONFIG_BITRATETYPE *pParamStruct = (OMX_VIDEO_CONFIG_BITRATETYPE *)pCompCfgStruct; 	 	 
  	   
	   PRINT_PARAM(PRINT_SET_PARAM, "\n \rOMX_IndexConfigVideoBitrate:\n");       
 	   PRINT_PARAM(PRINT_SET_PARAM, "nSize.......................%d\n", (int)pParamStruct->nSize);
       PRINT_PARAM(PRINT_SET_PARAM, "nVersion....................%d\n", (int)pParamStruct->nVersion.nVersion);
       PRINT_PARAM(PRINT_SET_PARAM, "nPortIndex..................%d\n", (int)pParamStruct->nPortIndex);
       PRINT_PARAM(PRINT_SET_PARAM, "nEncodeBitrate => bitrate...%d\n", (int)pParamStruct->nEncodeBitrate);	
	 }
     break;	   
	
   case OMX_IndexConfigVideoFramerate:
     {
       OMX_CONFIG_FRAMERATETYPE *pParamStruct = (OMX_CONFIG_FRAMERATETYPE *)pCompCfgStruct; 	 	 

	   PRINT_PARAM(PRINT_SET_PARAM, "\n \rOMX_IndexConfigVideoFramerate:\n");          
	   PRINT_PARAM(PRINT_SET_PARAM, "nSize............................%d\n", (int)pParamStruct->nSize);
       PRINT_PARAM(PRINT_SET_PARAM, "nVersion.........................%d\n", (int)pParamStruct->nVersion.nVersion);
       PRINT_PARAM(PRINT_SET_PARAM, "nPortIndex.......................%d\n", (int)pParamStruct->nPortIndex);
       PRINT_PARAM(PRINT_SET_PARAM, "xEncodeFramerate => framerate....%d\n", (int)pParamStruct->xEncodeFramerate);	
	 }
     break;	 
	
   case OMX_IndexConfigVideoAVCIntraPeriod:
     {
       OMX_VIDEO_CONFIG_AVCINTRAPERIOD *pParamStruct = (OMX_VIDEO_CONFIG_AVCINTRAPERIOD *)pCompCfgStruct; 	 	 

	   PRINT_PARAM(PRINT_SET_PARAM, "\n \rOMX_IndexConfigVideoAVCIntraPeriod:\n");       
	   PRINT_PARAM(PRINT_SET_PARAM, "nSize.......................%d\n", (int)pParamStruct->nSize);
       PRINT_PARAM(PRINT_SET_PARAM, "nVersion....................%d\n", (int)pParamStruct->nVersion.nVersion);
       PRINT_PARAM(PRINT_SET_PARAM, "nPortIndex..................%d\n", (int)pParamStruct->nPortIndex);
       PRINT_PARAM(PRINT_SET_PARAM, "nIDRPeriod => idr_period....%d\n", (int)pParamStruct->nIDRPeriod);
       PRINT_PARAM(PRINT_SET_PARAM, "nPFrames => inter_period....%d\n", (int)pParamStruct->nPFrames);	
	 }
     break;	   
	
   case OMX_IndexConfigVideoIntraVOPRefresh:
     {
       OMX_CONFIG_INTRAREFRESHVOPTYPE *pParamStruct = (OMX_CONFIG_INTRAREFRESHVOPTYPE *)pCompCfgStruct; 	 	 

	   PRINT_PARAM(PRINT_SET_PARAM, "\n \rOMX_IndexConfigVideoIntraVOPRefresh:\n");         
	   PRINT_PARAM(PRINT_SET_PARAM, "nSize.................................%d\n", (int)pParamStruct->nSize);
       PRINT_PARAM(PRINT_SET_PARAM, "nVersion..............................%d\n", (int)pParamStruct->nVersion.nVersion);
       PRINT_PARAM(PRINT_SET_PARAM, "nPortIndex............................%d\n", (int)pParamStruct->nPortIndex);
       PRINT_PARAM(PRINT_SET_PARAM, "IntraRefreshVOP => intra_refresh_vop..%d\n", (int)pParamStruct->IntraRefreshVOP);	   	
	 }
     break;	   
	
   case OMX_IndexConfigVideoNalSize:
     {
       OMX_VIDEO_CONFIG_NALSIZE *pParamStruct = (OMX_VIDEO_CONFIG_NALSIZE *)pCompCfgStruct; 	 	 

	   PRINT_PARAM(PRINT_SET_PARAM, "\n \rOMX_IndexConfigVideoNalSize:\n");        
	   PRINT_PARAM(PRINT_SET_PARAM, "nSize.............%d\n", (int)pParamStruct->nSize);
       PRINT_PARAM(PRINT_SET_PARAM, "nVersion..........%d\n", (int)pParamStruct->nVersion.nVersion);
       PRINT_PARAM(PRINT_SET_PARAM, "nPortIndex........%d\n", (int)pParamStruct->nPortIndex);
       PRINT_PARAM(PRINT_SET_PARAM, "nNaluBytes => nal_bytes........%d\n", (int)pParamStruct->nNaluBytes);	 		
	 }
     break;	   
	
   case OMX_TI_IndexConfigVideoPixelInfo:
     {
       OMX_VIDEO_CONFIG_PIXELINFOTYPE *pParamStruct = (OMX_VIDEO_CONFIG_PIXELINFOTYPE *)pCompCfgStruct; 	
	   
	   PRINT_PARAM(PRINT_SET_PARAM, "\n \rOMX_TI_IndexConfigVideoPixelInfo:\n"); 	   
	   PRINT_PARAM(PRINT_SET_PARAM, "nSize.......................%d\n", (int)pParamStruct->nSize);
       PRINT_PARAM(PRINT_SET_PARAM, "nVersion....................%d\n", (int)pParamStruct->nVersion.nVersion);
       PRINT_PARAM(PRINT_SET_PARAM, "nPortIndex..................%d\n", (int)pParamStruct->nPortIndex);
       PRINT_PARAM(PRINT_SET_PARAM, "nWidth => pixel_width.......%d\n", (int)pParamStruct->nWidth);		   
       PRINT_PARAM(PRINT_SET_PARAM, "nHeight => pixel_height.....%d\n", (int)pParamStruct->nHeight);			
	 }
     break;	 
	
   case OMX_TI_IndexConfigVideoMESearchRange:
     {
       OMX_VIDEO_CONFIG_MESEARCHRANGETYPE *pParamStruct = (OMX_VIDEO_CONFIG_MESEARCHRANGETYPE *)pCompCfgStruct; 	 	 

	   PRINT_PARAM(PRINT_SET_PARAM, "\n \rOMX_TI_IndexConfigVideoMESearchRange:\n");        
	   PRINT_PARAM(PRINT_SET_PARAM, "nSize............................%d\n", (int)pParamStruct->nSize);
       PRINT_PARAM(PRINT_SET_PARAM, "nVersion.........................%d\n", (int)pParamStruct->nVersion.nVersion);
       PRINT_PARAM(PRINT_SET_PARAM, "nPortIndex.......................%d\n", (int)pParamStruct->nPortIndex);
       PRINT_PARAM(PRINT_SET_PARAM, "eMVAccuracy => mvaccuracy........%d\n", (int)pParamStruct->eMVAccuracy);
       PRINT_PARAM(PRINT_SET_PARAM, "nHorSearchRangeP => mesr_horp....%d\n", (int)pParamStruct->nHorSearchRangeP);
       PRINT_PARAM(PRINT_SET_PARAM, "nVerSearchRangeP => mesr_verp....%d\n", (int)pParamStruct->nVerSearchRangeP);
       PRINT_PARAM(PRINT_SET_PARAM, "nHorSearchRangeB => mesr_horb....%d\n", (int)pParamStruct->nHorSearchRangeB);
       PRINT_PARAM(PRINT_SET_PARAM, "nVerSearchRangeB => mesr_verb....%d\n", (int)pParamStruct->nVerSearchRangeB);	
	 }
     break;	   
	
   case OMX_TI_IndexConfigVideoQPSettings:
     {
       OMX_VIDEO_CONFIG_QPSETTINGSTYPE *pParamStruct = (OMX_VIDEO_CONFIG_QPSETTINGSTYPE *)pCompCfgStruct; 	 	 
	   
	   PRINT_PARAM(PRINT_SET_PARAM, "\n \rOMX_TI_IndexConfigVideoQPSettings:\n");        
	   PRINT_PARAM(PRINT_SET_PARAM, "nSize.......................%d\n", (int)pParamStruct->nSize);
       PRINT_PARAM(PRINT_SET_PARAM, "nVersion....................%d\n", (int)pParamStruct->nVersion.nVersion);
       PRINT_PARAM(PRINT_SET_PARAM, "nPortIndex..................%d\n", (int)pParamStruct->nPortIndex);
       PRINT_PARAM(PRINT_SET_PARAM, "nQpI => qpi.................%d\n", (int)pParamStruct->nQpI);
       PRINT_PARAM(PRINT_SET_PARAM, "nQpMaxI => qp_max_i ........%d\n", (int)pParamStruct->nQpMaxI);
       PRINT_PARAM(PRINT_SET_PARAM, "nQpMinI => qp_min_i.........%d\n", (int)pParamStruct->nQpMinI);
       PRINT_PARAM(PRINT_SET_PARAM, "nQpP => qpp.................%d\n", (int)pParamStruct->nQpP);
       PRINT_PARAM(PRINT_SET_PARAM, "nQpMaxP => qp_max_p.........%d\n", (int)pParamStruct->nQpMaxP);
       PRINT_PARAM(PRINT_SET_PARAM, "nQpMinP => qp_min_p.........%d\n", (int)pParamStruct->nQpMinP);
       PRINT_PARAM(PRINT_SET_PARAM, "nQpOffsetB => qpb_offset....%d\n", (int)pParamStruct->nQpOffsetB);
       PRINT_PARAM(PRINT_SET_PARAM, "nQpMaxB => qp_max_b.........%d\n", (int)pParamStruct->nQpMaxB);
       PRINT_PARAM(PRINT_SET_PARAM, "nQpMinB => qp_min_b.........%d\n", (int)pParamStruct->nQpMinB);	
	 }
     break;	   
	
   case OMX_TI_IndexConfigSliceSettings:
     {
       OMX_VIDEO_CONFIG_SLICECODINGTYPE *pParamStruct = (OMX_VIDEO_CONFIG_SLICECODINGTYPE *)pCompCfgStruct; 	 	 

	   PRINT_PARAM(PRINT_SET_PARAM, "\n \rOMX_TI_IndexConfigSliceSettings:\n");       
	   PRINT_PARAM(PRINT_SET_PARAM, "nSize.......................%d\n", (int)pParamStruct->nSize);
       PRINT_PARAM(PRINT_SET_PARAM, "nVersion....................%d\n", (int)pParamStruct->nVersion.nVersion);
       PRINT_PARAM(PRINT_SET_PARAM, "nPortIndex..................%d\n", (int)pParamStruct->nPortIndex);
       PRINT_PARAM(PRINT_SET_PARAM, "eSliceMode => slice_mode....%d\n", (int)pParamStruct->eSliceMode);
       PRINT_PARAM(PRINT_SET_PARAM, "nSlicesize => slice_size....%d\n", (int)pParamStruct->nSlicesize);
	 }
     break;	   
   
   /* Add VDEC indexes here*/
   case OMX_TI_IndexParamFileModeType:
     {
       OMX_PARAM_FILEMODE_TYPE *pParamStruct = (OMX_PARAM_FILEMODE_TYPE *)pCompCfgStruct; 	 	 

	   PRINT_PARAM(PRINT_SET_PARAM, "\n \rOMX_TI_IndexParamFileModeType:\n");       
	   PRINT_PARAM(PRINT_SET_PARAM, "nSize.................................%d\n", (int)pParamStruct->nSize);
       PRINT_PARAM(PRINT_SET_PARAM, "nVersion..............................%d\n", (int)pParamStruct->nVersion.nVersion);
       PRINT_PARAM(PRINT_SET_PARAM, "nPortIndex............................%d\n", (int)pParamStruct->nPortIndex);
       PRINT_PARAM(PRINT_SET_PARAM, "bEnableFileMode => file_mode_flag.....%d\n", (int)pParamStruct->bEnableFileMode);
	 }
	 break;	 

	 case OMX_IndexConfigVideoMacroBlockErrorMap:
     {
       OMX_CONFIG_MBERRORREPORTINGTYPE *pParamStruct = (OMX_CONFIG_MBERRORREPORTINGTYPE *)pCompCfgStruct; 	 	 

	   PRINT_PARAM(PRINT_SET_PARAM, "\n \rOMX_TI_IndexParamFileModeType:\n");       
	   PRINT_PARAM(PRINT_SET_PARAM, "nSize.................................%d\n", (int)pParamStruct->nSize);
       PRINT_PARAM(PRINT_SET_PARAM, "nVersion..............................%d\n", (int)pParamStruct->nVersion.nVersion);
       PRINT_PARAM(PRINT_SET_PARAM, "nPortIndex............................%d\n", (int)pParamStruct->nPortIndex);
       PRINT_PARAM(PRINT_SET_PARAM, "bEnabled => .....%d\n", (int)pParamStruct->bEnabled);
	 }
	 break;	 

#ifdef OMTB_FILE_IO_CONFIG	 
   /* Add VSRC/VSNK indexes here*/
   case OMX_TI_IndexConfigFileIO:
     {
       OMX_VSRC_FILEIO_CONFIG *pParamStruct = (OMX_VSRC_FILEIO_CONFIG *)pCompCfgStruct;       	

	   PRINT_PARAM(PRINT_SET_PARAM, "\n \rOMX_TI_IndexConfigFileIO:\n");         
	   PRINT_PARAM(PRINT_SET_PARAM, "nSize...........................................%d\n",
	                     (int)pParamStruct->nSize);
       PRINT_PARAM(PRINT_SET_PARAM, "nVersion........................................%d\n",
                         (int)pParamStruct->nVersion.nVersion);
       PRINT_PARAM(PRINT_SET_PARAM, "nPortIndex......................................%d\n",
                         (int)pParamStruct->nPortIndex);
       PRINT_PARAM(PRINT_SET_PARAM, "bFileIOEnable => port_fileio....................%d\n",
                         (int)pParamStruct->bFileIOEnable);
#if 0       
	   PRINT_PARAM(PRINT_SET_PARAM, "bDumpYUV420P => dump_420p........................%d\n",
                         (int)pParamStruct->bDumpYUV420P);						 
#endif						 
       PRINT_PARAM(PRINT_SET_PARAM, "pIn/OutFileName => port_infile/port_outfile.....%s\n",
                         pParamStruct->pInFileName);
       PRINT_PARAM(PRINT_SET_PARAM, "nOutWidth => out_width..........................%d\n",
                         (int)pParamStruct->nOutWidth);
       PRINT_PARAM(PRINT_SET_PARAM, "nOutHeight => out_height........................%d\n",
                         (int)pParamStruct->nOutHeight);
       PRINT_PARAM(PRINT_SET_PARAM, "nOutFramePitch => out_pitch.....................%d\n",
                         (int)pParamStruct->nOutFramePitch);
       PRINT_PARAM(PRINT_SET_PARAM, "eOutChromaFormat => out_chroma_fmt..............%d\n",
                         (int)pParamStruct->eOutChromaFormat);
       PRINT_PARAM(PRINT_SET_PARAM, "eOutFrameType => out_frm_type...................%d\n",
                         (int)pParamStruct->eOutFrameType);
     }
     break;	
#endif


   default:
     {
	   /*Base Index which will be common for all the components*/	
       OMTBBASE_DisplaySetParams(nParamIndex, pCompCfgStruct);
     } 
	 break;	 
  }
}

/******************************************************************************\
 *      OMTBBASE_DisplaySetParams Function Prototype
\******************************************************************************/
/**
 *
 *  @brief    This Function conatins the indexs common for all the components
 *
 *  @param    nParamIndex
 *            pCompCfgStruct
 *
 *  @return   None
 */
void OMTBBASE_DisplaySetParams(unsigned int nParamIndex, OMX_PTR pCompCfgStruct)
{
  unsigned int i = 0;
 
  switch(nParamIndex)
  {
   case OMX_TI_IndexConfigChannelGroupInfo:
     {
       OMX_CONFIG_CHANNELGROUPINFO *pParamStruct = (OMX_CONFIG_CHANNELGROUPINFO *)pCompCfgStruct;       	

	   PRINT_PARAM(PRINT_SET_PARAM, "\n \rOMX_TI_IndexConfigChannelGroupInfo:\n");          
	   PRINT_PARAM(PRINT_SET_PARAM, "nSize............................%d\n", (int)pParamStruct->nSize);
       PRINT_PARAM(PRINT_SET_PARAM, "nVersion.........................%d\n", (int)pParamStruct->nVersion.nVersion);
       PRINT_PARAM(PRINT_SET_PARAM, "nPortIndex.......................%d\n", (int)pParamStruct->nPortIndex);
       PRINT_PARAM(PRINT_SET_PARAM, "cChannelGroupName................%s\n", pParamStruct->cChannelGroupName);
       PRINT_PARAM(PRINT_SET_PARAM, "nNumPortsInGroup.................%d\n", (int)pParamStruct->nNumPortsInGroup);
       PRINT_PARAM(PRINT_SET_PARAM, "auPortGroupIndex.................");
       for(i = 0; i < (int)pParamStruct->nNumPortsInGroup; i++)
	     PRINT_PARAM(PRINT_SET_PARAM, "%d ", (int)pParamStruct->auPortGroupIndex[i]);
       PRINT_PARAM(PRINT_SET_PARAM, "\n");
     }
     break;	
	 
	 case OMX_TI_IndexParamCompPortNotifyType:
     {
       OMX_PARAM_COMPPORT_NOTIFYTYPE *pParamStruct = (OMX_PARAM_COMPPORT_NOTIFYTYPE *)pCompCfgStruct;       	
       
	   PRINT_PARAM(PRINT_SET_PARAM, "\n \rOMX_TI_IndexParamCompPortNotifyType:\n"); 	   
	   PRINT_PARAM(PRINT_SET_PARAM, "nSize.................................%d\n", (int)pParamStruct->nSize);
       PRINT_PARAM(PRINT_SET_PARAM, "nVersion..............................%d\n", (int)pParamStruct->nVersion.nVersion);
       PRINT_PARAM(PRINT_SET_PARAM, "nPortIndex............................%d\n", (int)pParamStruct->nPortIndex);
       PRINT_PARAM(PRINT_SET_PARAM, "eNotifyType => comp_port_notify_type..%d\n", (int)pParamStruct->eNotifyType);
     }
     break;
	 
  case OMX_IndexParamPortDefinition:
     { 
       OMX_PARAM_PORTDEFINITIONTYPE *pParamStruct = (OMX_PARAM_PORTDEFINITIONTYPE *)pCompCfgStruct;
	   PRINT_PARAM(PRINT_SET_PARAM, "\n \rOMX_IndexParamPortDefinition:\n"); 	   
	   PRINT_PARAM(PRINT_SET_PARAM, "nSize.................................%d\n", (int)pParamStruct->nSize);
       PRINT_PARAM(PRINT_SET_PARAM, "nVersion..............................%d\n", (int)pParamStruct->nVersion.nVersion);
       PRINT_PARAM(PRINT_SET_PARAM, "nPortIndex............................%d\n", (int)pParamStruct->nPortIndex);	   
     }
     break;

   case OMX_IndexParamCompBufferSupplier:
     { 
       OMX_PARAM_BUFFERSUPPLIERTYPE *pParamStruct = (OMX_PARAM_BUFFERSUPPLIERTYPE *)pCompCfgStruct;
	   
	   PRINT_PARAM(PRINT_SET_PARAM, "\n \rOMX_IndexParamCompBufferSupplier:\n"); 		   
       PRINT_PARAM(PRINT_SET_PARAM, "nSize............................%d\n", (int)pParamStruct->nSize);
       PRINT_PARAM(PRINT_SET_PARAM, "nVersion.........................%d\n", (int)pParamStruct->nVersion.nVersion);
       PRINT_PARAM(PRINT_SET_PARAM, "nPortIndex.......................%d\n", (int)pParamStruct->nPortIndex);	   
       PRINT_PARAM(PRINT_SET_PARAM, "eBufferSupplier => buf_supplier..%d\n", (int)pParamStruct->eBufferSupplier);
     }
     break;

   case OMX_IndexParamPriorityMgmt:
     { 
       OMX_PRIORITYMGMTTYPE *pParamStruct = (OMX_PRIORITYMGMTTYPE *)pCompCfgStruct;
	   
	   PRINT_PARAM(PRINT_SET_PARAM, "\n \rOMX_IndexParamPriorityMgmt:\n"); 	   

	   PRINT_PARAM(PRINT_SET_PARAM, "nSize.............%d\n",(int)pParamStruct->nSize);
       PRINT_PARAM(PRINT_SET_PARAM, "nVersion..........%d\n",(int)pParamStruct->nVersion.nVersion);
       PRINT_PARAM(PRINT_SET_PARAM, "nGroupPriority....%d\n",(int)pParamStruct->nGroupPriority);
       PRINT_PARAM(PRINT_SET_PARAM, "nGroupID..........%d\n",(int)pParamStruct->nGroupID);	   

     }
     break;

   case OMX_TI_IndexParamBuffMemType:
     {
       OMX_PARAM_BUFFER_MEMORYTYPE *pParamStruct = (OMX_PARAM_BUFFER_MEMORYTYPE *)pCompCfgStruct;

	   PRINT_PARAM(PRINT_SET_PARAM, "\n \rOMX_TI_IndexParamBuffMemType:\n"); 		   
       PRINT_PARAM(PRINT_SET_PARAM, "nSize............................%d\n",(int)pParamStruct->nSize);
       PRINT_PARAM(PRINT_SET_PARAM, "nVersion.........................%d\n",(int)pParamStruct->nVersion.nVersion);
       PRINT_PARAM(PRINT_SET_PARAM, "nPortIndex.......................%d\n",(int)pParamStruct->nPortIndex);
       PRINT_PARAM(PRINT_SET_PARAM, "eBufMemoryType => buf_memory.....%d\n",(int)pParamStruct->eBufMemoryType);	  	 
     }
     break; 	 
 
   case OMX_TI_IndexConfigChannelName:
     {
       OMX_CONFIG_CHANNELNAME *pParamStruct = (OMX_CONFIG_CHANNELNAME *)pCompCfgStruct;

	   PRINT_PARAM(PRINT_SET_PARAM, "\n \rOMX_TI_IndexConfigChannelName:\n"); 	   
       PRINT_PARAM(PRINT_SET_PARAM, "nSize..................%d\n", (int)pParamStruct->nSize);
       PRINT_PARAM(PRINT_SET_PARAM, "nVersion...............%d\n", (int)pParamStruct->nVersion.nVersion);
       PRINT_PARAM(PRINT_SET_PARAM, "nPortIndex.............%d\n", (int)pParamStruct->nPortIndex);
       PRINT_PARAM(PRINT_SET_PARAM, "cChannelName...........%s\n", pParamStruct->cChannelName);	 
	 }
	 break;
  
   default:
     { 
       /* Add the new index in OMTB code when this error is printed */
	   PRINT_PARAM(PRINT_SET_PARAM, "Index not supported by OMTB\n");
     }
     break;	 
  }
}  

/******************************************************************************\
 *      OMTB_DisplayGetParams Function Prototype
\******************************************************************************/
/**
 *
 *  @brief    This Function print the values of the index on output console/file
 *
 *  @param    nParamIndex
 *            pCompCfgStruct
 *
 *  @return   None
 */
void OMTB_DisplayGetParams(unsigned int nParamIndex, OMX_PTR pCompCfgStruct)
{
 unsigned int i = 0;
 
 /* print the values of this index on output console/file */ 
 switch (nParamIndex)
 {
   /* Add VFCC/TVP component indexes here*/
   case OMX_IndexConfigVFCCPortStats:
     {
       OMX_PARAM_VIDEO_CAPTURE_STATS *pParamStruct = (OMX_PARAM_VIDEO_CAPTURE_STATS *)pCompCfgStruct;       	
	   
	   PRINT_PARAM(PRINT_GET_PARAM, "\n \rOMX_IndexConfigVFCCPortStats:\n"); 	       
	   PRINT_PARAM(PRINT_GET_PARAM, "nSize..................%d\n", (int)pParamStruct->nSize);
       PRINT_PARAM(PRINT_GET_PARAM, "nVersion...............%d\n", (int)pParamStruct->nVersion.nVersion);
       PRINT_PARAM(PRINT_GET_PARAM, "nPortIndex.............%d\n", (int)pParamStruct->nPortIndex);
       PRINT_PARAM(PRINT_GET_PARAM, "uBufsRxdFromHWPort.....%d\n", (int)pParamStruct->uBufsRxdFromHWPort);
       PRINT_PARAM(PRINT_GET_PARAM, "uHeightErrCnt......... %d\n", (int)pParamStruct->uHeightErrCnt);
       PRINT_PARAM(PRINT_GET_PARAM, "uWidthErrCnt...........%d\n", (int)pParamStruct->uWidthErrCnt);
     }
     break;

   /* Add VFPC DEI/NF/SC component indexes here*/
   case OMX_TI_IndexParamCompPortNotifyType:
     {
       OMX_PARAM_COMPPORT_NOTIFYTYPE *pParamStruct = (OMX_PARAM_COMPPORT_NOTIFYTYPE *)pCompCfgStruct;       	
	   
	   PRINT_PARAM(PRINT_GET_PARAM, "\n \rOMX_TI_IndexParamCompPortNotifyType:\n");        
	   PRINT_PARAM(PRINT_GET_PARAM, "nSize.............%d\n", (int)pParamStruct->nSize);
       PRINT_PARAM(PRINT_GET_PARAM, "nVersion..........%d\n", (int)pParamStruct->nVersion.nVersion);
       PRINT_PARAM(PRINT_GET_PARAM, "nPortIndex........%d\n", (int)pParamStruct->nPortIndex);
       PRINT_PARAM(PRINT_GET_PARAM, "eNotifyType.......%d\n", (int)pParamStruct->eNotifyType);
     }
     break;
	 
   /* Add VFDC/DC component indexes here*/
   case OMX_TI_IndexConfigChannelGroupInfo:
     {
       OMX_CONFIG_CHANNELGROUPINFO *pParamStruct = (OMX_CONFIG_CHANNELGROUPINFO *)pCompCfgStruct;       	
       
	   PRINT_PARAM(PRINT_GET_PARAM, "\n \rOMX_TI_IndexConfigChannelGroupInfo:\n");     	   
	   PRINT_PARAM(PRINT_GET_PARAM, "nSize.............%d\n", (int)pParamStruct->nSize);
       PRINT_PARAM(PRINT_GET_PARAM, "nVersion..........%d\n", (int)pParamStruct->nVersion.nVersion);
       PRINT_PARAM(PRINT_GET_PARAM, "nPortIndex........%d\n", (int)pParamStruct->nPortIndex);
       PRINT_PARAM(PRINT_GET_PARAM, "cChannelGroupName.%s\n", pParamStruct->cChannelGroupName);
       PRINT_PARAM(PRINT_GET_PARAM, "nNumPortsInGroup..%d\n", (int)pParamStruct->nNumPortsInGroup);
	   PRINT_PARAM(PRINT_GET_PARAM, "auPortGroupIndex..");	   
	   for(i = 0; i < (int)pParamStruct->nNumPortsInGroup; i++)
	     PRINT_PARAM(PRINT_GET_PARAM, "%d ", (int)pParamStruct->auPortGroupIndex[i]);
       PRINT_PARAM(PRINT_GET_PARAM, "\n");
     }
     break;
	 
   case OMX_TI_IndexConfigVFDCMosaicPort2WinMap:
     {
       OMX_CONFIG_VFDC_MOSAICLAYOUT_PORT2WINMAP *pParamStruct = (OMX_CONFIG_VFDC_MOSAICLAYOUT_PORT2WINMAP *)pCompCfgStruct;       	
	   
	   PRINT_PARAM(PRINT_GET_PARAM, "\n \rOMX_TI_IndexConfigVFDCMosaicPort2WinMap:\n");       
	   PRINT_PARAM(PRINT_GET_PARAM, "nSize.............%d\n", (int)pParamStruct->nSize);
       PRINT_PARAM(PRINT_GET_PARAM, "nVersion..........%d\n", (int)pParamStruct->nVersion.nVersion);
       PRINT_PARAM(PRINT_GET_PARAM, "nPortIndex........%d\n", (int)pParamStruct->nPortIndex);
       PRINT_PARAM(PRINT_GET_PARAM, "nLayoutId.........%d\n", (int)pParamStruct->nLayoutId);
       PRINT_PARAM(PRINT_GET_PARAM, "numWindows........%d\n", (int)pParamStruct->numWindows);
	   PRINT_PARAM(PRINT_GET_PARAM, "omxPortList.......");	   
	   for(i = 0; i < (int)pParamStruct->numWindows; i++)
	     PRINT_PARAM(PRINT_GET_PARAM, "%d ", (int)pParamStruct->omxPortList[i]);
       PRINT_PARAM(PRINT_GET_PARAM, "\n");
     }
     break;	    
	 
   /* Add VENC component indexes here*/
   case OMX_IndexParamVideoPortFormat:
     {
       OMX_VIDEO_PARAM_PORTFORMATTYPE *pParamStruct = (OMX_VIDEO_PARAM_PORTFORMATTYPE *)pCompCfgStruct;       	

	   PRINT_PARAM(PRINT_GET_PARAM, "\n \rOMX_IndexParamVideoPortFormat:\n");       
	   PRINT_PARAM(PRINT_GET_PARAM, "nSize..............%d\n", (int)pParamStruct->nSize);
       PRINT_PARAM(PRINT_GET_PARAM, "nVersion...........%d\n", (int)pParamStruct->nVersion.nVersion);
       PRINT_PARAM(PRINT_GET_PARAM, "nPortIndex.........%d\n", (int)pParamStruct->nPortIndex);
       PRINT_PARAM(PRINT_GET_PARAM, "nIndex.............%d\n", (int)pParamStruct->nIndex);
       PRINT_PARAM(PRINT_GET_PARAM, "eCompressionFormat.%d\n", (int)pParamStruct->eCompressionFormat);
       PRINT_PARAM(PRINT_GET_PARAM, "eColorFormat.......%d\n", (int)pParamStruct->eColorFormat);
       PRINT_PARAM(PRINT_GET_PARAM, "xFramerate.........%d\n", (int)pParamStruct->xFramerate);
     }
     break;
	 
   case OMX_IndexParamVideoBitrate:
     {
       OMX_VIDEO_PARAM_BITRATETYPE *pParamStruct = (OMX_VIDEO_PARAM_BITRATETYPE *)pCompCfgStruct; 
	   
	   PRINT_PARAM(PRINT_GET_PARAM, "\n \rOMX_IndexParamVideoBitrate:\n");    	   
	   PRINT_PARAM(PRINT_GET_PARAM, "nSize.............%d\n", (int)pParamStruct->nSize);
       PRINT_PARAM(PRINT_GET_PARAM, "nVersion..........%d\n", (int)pParamStruct->nVersion.nVersion);
       PRINT_PARAM(PRINT_GET_PARAM, "nPortIndex........%d\n", (int)pParamStruct->nPortIndex);
       PRINT_PARAM(PRINT_GET_PARAM, "eControlRate......%d\n", (int)pParamStruct->eControlRate);
       PRINT_PARAM(PRINT_GET_PARAM, "nTargetBitrate....%d\n", (int)pParamStruct->nTargetBitrate);
	 }
	 break;
	 
   case OMX_IndexParamVideoAvc:
     {
       OMX_VIDEO_PARAM_AVCTYPE *pParamStruct = (OMX_VIDEO_PARAM_AVCTYPE *)pCompCfgStruct;

	   PRINT_PARAM(PRINT_GET_PARAM, "\n \rOMX_IndexParamVideoAvc:\n");         
	   PRINT_PARAM(PRINT_GET_PARAM, "nSize..................%d\n", (int)pParamStruct->nSize);
       PRINT_PARAM(PRINT_GET_PARAM, "nVersion...............%d\n", (int)pParamStruct->nVersion.nVersion);
       PRINT_PARAM(PRINT_GET_PARAM, "nPortIndex.............%d\n", (int)pParamStruct->nPortIndex);
       PRINT_PARAM(PRINT_GET_PARAM, "nSliceHeaderSpacing....%d\n", (int)pParamStruct->nSliceHeaderSpacing);
       PRINT_PARAM(PRINT_GET_PARAM, "nPFrames...............%d\n", (int)pParamStruct->nPFrames);
       PRINT_PARAM(PRINT_GET_PARAM, "nBFrames...............%d\n", (int)pParamStruct->nBFrames);
       PRINT_PARAM(PRINT_GET_PARAM, "bUseHadamard...........%d\n", (int)pParamStruct->bUseHadamard);
       PRINT_PARAM(PRINT_GET_PARAM, "nRefFrames.............%d\n", (int)pParamStruct->nRefFrames);
       PRINT_PARAM(PRINT_GET_PARAM, "nRefIdx10ActiveMinus1..%d\n", (int)pParamStruct->nRefIdx10ActiveMinus1);
       PRINT_PARAM(PRINT_GET_PARAM, "nRefIdx11ActiveMinus1..%d\n", (int)pParamStruct->nRefIdx11ActiveMinus1);
       PRINT_PARAM(PRINT_GET_PARAM, "bEnableUEP.............%d\n", (int)pParamStruct->bEnableUEP);
       PRINT_PARAM(PRINT_GET_PARAM, "bEnableFMO.............%d\n", (int)pParamStruct->bEnableFMO);
       PRINT_PARAM(PRINT_GET_PARAM, "bEnableASO.............%d\n", (int)pParamStruct->bEnableASO);
       PRINT_PARAM(PRINT_GET_PARAM, "bEnableRS..............%d\n", (int)pParamStruct->bEnableRS);
       PRINT_PARAM(PRINT_GET_PARAM, "eProfile...............%d\n", (int)pParamStruct->eProfile);
       PRINT_PARAM(PRINT_GET_PARAM, "eLevel.................%d\n", (int)pParamStruct->eLevel);
       PRINT_PARAM(PRINT_GET_PARAM, "nAllowedPictureTypes...%d\n", (int)pParamStruct->nAllowedPictureTypes);
       PRINT_PARAM(PRINT_GET_PARAM, "bFrameMBsOnly..........%d\n", (int)pParamStruct->bFrameMBsOnly);
       PRINT_PARAM(PRINT_GET_PARAM, "bMBAFF.................%d\n", (int)pParamStruct->bMBAFF);
       PRINT_PARAM(PRINT_GET_PARAM, "bEntropyCodingCABAC....%d\n", (int)pParamStruct->bEntropyCodingCABAC);
       PRINT_PARAM(PRINT_GET_PARAM, "bWeightedPPrediction...%d\n", (int)pParamStruct->bWeightedPPrediction);
       PRINT_PARAM(PRINT_GET_PARAM, "nWeightedBipredicitonMode.%d\n", (int)pParamStruct->nWeightedBipredicitonMode);
       PRINT_PARAM(PRINT_GET_PARAM, "bconstIpred............%d\n", (int)pParamStruct->bconstIpred);
       PRINT_PARAM(PRINT_GET_PARAM, "bDirect8x8Inference....%d\n", (int)pParamStruct->bDirect8x8Inference);
       PRINT_PARAM(PRINT_GET_PARAM, "bDirectSpatialTemporal.%d\n", (int)pParamStruct->bDirectSpatialTemporal);
       PRINT_PARAM(PRINT_GET_PARAM, "nCabacInitIdc..........%d\n", (int)pParamStruct->nCabacInitIdc);
       PRINT_PARAM(PRINT_GET_PARAM, "eLoopFilterMode........%d\n", (int)pParamStruct->eLoopFilterMode);	 
	 }
	 break;	 
	 
   case OMX_IndexParamVideoMotionVector:
     {
       OMX_VIDEO_PARAM_MOTIONVECTORTYPE *pParamStruct = (OMX_VIDEO_PARAM_MOTIONVECTORTYPE *)pCompCfgStruct; 	 
       
	   PRINT_PARAM(PRINT_GET_PARAM, "\n \rOMX_IndexParamVideoMotionVector:\n");  	   
	   PRINT_PARAM(PRINT_GET_PARAM, "nSize.............%d\n", (int)pParamStruct->nSize);
       PRINT_PARAM(PRINT_GET_PARAM, "nVersion..........%d\n", (int)pParamStruct->nVersion.nVersion);
       PRINT_PARAM(PRINT_GET_PARAM, "nPortIndex........%d\n", (int)pParamStruct->nPortIndex);
       PRINT_PARAM(PRINT_GET_PARAM, "eAccuracy.........%d\n", (int)pParamStruct->eAccuracy);
       PRINT_PARAM(PRINT_GET_PARAM, "bUnrestrictedMVs..%d\n", (int)pParamStruct->bUnrestrictedMVs);
       PRINT_PARAM(PRINT_GET_PARAM, "bFourMV...........%d\n", (int)pParamStruct->bFourMV);
       PRINT_PARAM(PRINT_GET_PARAM, "sXSearchRange.....%d\n", (int)pParamStruct->sXSearchRange);
       PRINT_PARAM(PRINT_GET_PARAM, "sYSearchRange.....%d\n", (int)pParamStruct->sYSearchRange);
	 }
	 break;
	 
   case OMX_IndexParamVideoQuantization:
     {
       OMX_VIDEO_PARAM_QUANTIZATIONTYPE *pParamStruct = (OMX_VIDEO_PARAM_QUANTIZATIONTYPE *)pCompCfgStruct; 	 
       
	   PRINT_PARAM(PRINT_GET_PARAM, "\n \rOMX_IndexParamVideoQuantization:\n");  	   
	   PRINT_PARAM(PRINT_GET_PARAM, "nSize.............%d\n", (int)pParamStruct->nSize);
       PRINT_PARAM(PRINT_GET_PARAM, "nVersion..........%d\n", (int)pParamStruct->nVersion.nVersion);
       PRINT_PARAM(PRINT_GET_PARAM, "nPortIndex........%d\n", (int)pParamStruct->nPortIndex);
       PRINT_PARAM(PRINT_GET_PARAM, "nQpI..............%d\n", (int)pParamStruct->nQpI);
       PRINT_PARAM(PRINT_GET_PARAM, "nQpP..............%d\n", (int)pParamStruct->nQpP);
       PRINT_PARAM(PRINT_GET_PARAM, "nQpB..............%d\n", (int)pParamStruct->nQpB);
	 }
	 break;
	 
   case OMX_IndexParamVideoSliceFMO:
     {
       OMX_VIDEO_PARAM_AVCSLICEFMO *pParamStruct = (OMX_VIDEO_PARAM_AVCSLICEFMO *)pCompCfgStruct; 	 
       
	   PRINT_PARAM(PRINT_GET_PARAM, "\n \rOMX_IndexParamVideoSliceFMO:\n"); 	   
	   PRINT_PARAM(PRINT_GET_PARAM, "nSize..................%d\n", (int)pParamStruct->nSize);
       PRINT_PARAM(PRINT_GET_PARAM, "nVersion...............%d\n", (int)pParamStruct->nVersion.nVersion);
       PRINT_PARAM(PRINT_GET_PARAM, "nPortIndex.............%d\n", (int)pParamStruct->nPortIndex);
       PRINT_PARAM(PRINT_GET_PARAM, "nNumSliceGroups........%d\n", (int)pParamStruct->nNumSliceGroups);
       PRINT_PARAM(PRINT_GET_PARAM, "nSliceGroupMapType.....%d\n", (int)pParamStruct->nSliceGroupMapType);
       PRINT_PARAM(PRINT_GET_PARAM, "eSliceMode.............%d\n", (int)pParamStruct->eSliceMode);
	 }
	 break;
	 
   case OMX_IndexParamVideoIntraRefresh:
     {
       OMX_VIDEO_PARAM_INTRAREFRESHTYPE *pParamStruct = (OMX_VIDEO_PARAM_INTRAREFRESHTYPE *)pCompCfgStruct; 	 
       
	   PRINT_PARAM(PRINT_GET_PARAM, "\n \rOMX_IndexParamVideoIntraRefresh:\n"); 	 	   
	   PRINT_PARAM(PRINT_GET_PARAM, "nSize.............%d\n", (int)pParamStruct->nSize);
       PRINT_PARAM(PRINT_GET_PARAM, "nVersion..........%d\n", (int)pParamStruct->nVersion.nVersion);
       PRINT_PARAM(PRINT_GET_PARAM, "nPortIndex........%d\n", (int)pParamStruct->nPortIndex);
       PRINT_PARAM(PRINT_GET_PARAM, "eRefreshMode......%d\n", (int)pParamStruct->eRefreshMode);
       PRINT_PARAM(PRINT_GET_PARAM, "nAirMBs...........%d\n", (int)pParamStruct->nAirMBs);
       PRINT_PARAM(PRINT_GET_PARAM, "nAirRef...........%d\n", (int)pParamStruct->nAirRef);
       PRINT_PARAM(PRINT_GET_PARAM, "nCirMBs...........%d\n", (int)pParamStruct->nCirMBs);
	 }
	 break;	 

   case OMX_IndexParamVideoProfileLevelCurrent:
     {
       OMX_VIDEO_PARAM_PROFILELEVELTYPE *pParamStruct = (OMX_VIDEO_PARAM_PROFILELEVELTYPE *)pCompCfgStruct; 	 
       
	   PRINT_PARAM(PRINT_GET_PARAM, "\n \rOMX_IndexParamVideoProfileLevelCurrent:\n"); 		   
	   PRINT_PARAM(PRINT_GET_PARAM, "nSize.............%d\n", (int)pParamStruct->nSize);
       PRINT_PARAM(PRINT_GET_PARAM, "nVersion..........%d\n", (int)pParamStruct->nVersion.nVersion);
       PRINT_PARAM(PRINT_GET_PARAM, "nPortIndex........%d\n", (int)pParamStruct->nPortIndex);
       PRINT_PARAM(PRINT_GET_PARAM, "eProfile..........%d\n", (int)pParamStruct->eProfile);
       PRINT_PARAM(PRINT_GET_PARAM, "eLevel............%d\n", (int)pParamStruct->eLevel);
       PRINT_PARAM(PRINT_GET_PARAM, "nProfileIndex.....%d\n", (int)pParamStruct->nProfileIndex);
	 }
	 break;	
	 
   case OMX_IndexParamVideoProfileLevelQuerySupported:
     {
       OMX_VIDEO_PARAM_PROFILELEVELTYPE *pParamStruct = (OMX_VIDEO_PARAM_PROFILELEVELTYPE *)pCompCfgStruct; 	 
       
	   PRINT_PARAM(PRINT_GET_PARAM, "\n \rOMX_IndexParamVideoProfileLevelQuerySupported:\n"); 	   
	   PRINT_PARAM(PRINT_GET_PARAM, "nSize.............%d\n", (int)pParamStruct->nSize);
       PRINT_PARAM(PRINT_GET_PARAM, "nVersion..........%d\n", (int)pParamStruct->nVersion.nVersion);
       PRINT_PARAM(PRINT_GET_PARAM, "nPortIndex........%d\n", (int)pParamStruct->nPortIndex);
       PRINT_PARAM(PRINT_GET_PARAM, "eProfile..........%d\n", (int)pParamStruct->eProfile);
       PRINT_PARAM(PRINT_GET_PARAM, "eLevel............%d\n", (int)pParamStruct->eLevel);
       PRINT_PARAM(PRINT_GET_PARAM, "nProfileIndex.....%d\n", (int)pParamStruct->nProfileIndex);	   
	 }
	 break;	
	 
   case OMX_TI_IndexParamVideoDataSyncMode:
     {
       OMX_VIDEO_PARAM_DATASYNCMODETYPE *pParamStruct = (OMX_VIDEO_PARAM_DATASYNCMODETYPE *)pCompCfgStruct; 	 
       
	   PRINT_PARAM(PRINT_GET_PARAM, "\n \rOMX_TI_IndexParamVideoDataSyncMode:\n");	   
	   PRINT_PARAM(PRINT_GET_PARAM, "nSize.............%d\n", (int)pParamStruct->nSize);
       PRINT_PARAM(PRINT_GET_PARAM, "nVersion..........%d\n", (int)pParamStruct->nVersion.nVersion);
       PRINT_PARAM(PRINT_GET_PARAM, "nPortIndex........%d\n", (int)pParamStruct->nPortIndex);
       PRINT_PARAM(PRINT_GET_PARAM, "eDataMode.........%d\n", (int)pParamStruct->eDataMode);
       PRINT_PARAM(PRINT_GET_PARAM, "nNumDataUnits.....%d\n", (int)pParamStruct->nNumDataUnits);
	 }
	 break;	
	 
   case OMX_TI_IndexParamVideoBitStreamFormatSelect:
     {
       OMX_VIDEO_PARAM_AVCBITSTREAMFORMATTYPE *pParamStruct = (OMX_VIDEO_PARAM_AVCBITSTREAMFORMATTYPE *)pCompCfgStruct; 	 
       
	   PRINT_PARAM(PRINT_GET_PARAM, "\n \rOMX_TI_IndexParamVideoBitStreamFormatSelect:\n");	   	   
	   PRINT_PARAM(PRINT_GET_PARAM, "nSize.............%d\n", (int)pParamStruct->nSize);
       PRINT_PARAM(PRINT_GET_PARAM, "nVersion..........%d\n", (int)pParamStruct->nVersion.nVersion);
       PRINT_PARAM(PRINT_GET_PARAM, "nPortIndex........%d\n", (int)pParamStruct->nPortIndex);
       PRINT_PARAM(PRINT_GET_PARAM, "eStreamFormat.....%d\n", (int)pParamStruct->eStreamFormat);	   
	 }
	 break;	
	 
   case OMX_TI_IndexParamVideoNALUsettings:
     {
       OMX_VIDEO_PARAM_AVCNALUCONTROLTYPE *pParamStruct = (OMX_VIDEO_PARAM_AVCNALUCONTROLTYPE *)pCompCfgStruct; 	 
       
	   PRINT_PARAM(PRINT_GET_PARAM, "\n \rOMX_TI_IndexParamVideoNALUsettings:\n");		   
	   PRINT_PARAM(PRINT_GET_PARAM, "nSize.............%d\n", (int)pParamStruct->nSize);
       PRINT_PARAM(PRINT_GET_PARAM, "nVersion..........%d\n", (int)pParamStruct->nVersion.nVersion);
       PRINT_PARAM(PRINT_GET_PARAM, "nPortIndex........%d\n", (int)pParamStruct->nPortIndex);
       PRINT_PARAM(PRINT_GET_PARAM, "nStartofSequence..%d\n", (int)pParamStruct->nStartofSequence);
       PRINT_PARAM(PRINT_GET_PARAM, "nEndofSequence....%d\n", (int)pParamStruct->nEndofSequence);
       PRINT_PARAM(PRINT_GET_PARAM, "nIDR..............%d\n", (int)pParamStruct->nIDR);
       PRINT_PARAM(PRINT_GET_PARAM, "nIntraPicture.....%d\n", (int)pParamStruct->nIntraPicture);
       PRINT_PARAM(PRINT_GET_PARAM, "nNonIntraPicture..%d\n", (int)pParamStruct->nNonIntraPicture);
	 }
	 break;	
	 
   case OMX_TI_IndexParamVideoMEBlockSize:
     {
       OMX_VIDEO_PARAM_MEBLOCKSIZETYPE *pParamStruct = (OMX_VIDEO_PARAM_MEBLOCKSIZETYPE *)pCompCfgStruct; 	 
       
	   PRINT_PARAM(PRINT_GET_PARAM, "\n \rOMX_TI_IndexParamVideoMEBlockSize:\n");	   
	   PRINT_PARAM(PRINT_GET_PARAM, "nSize.............%d\n", (int)pParamStruct->nSize);
       PRINT_PARAM(PRINT_GET_PARAM, "nVersion..........%d\n", (int)pParamStruct->nVersion.nVersion);
       PRINT_PARAM(PRINT_GET_PARAM, "nPortIndex........%d\n", (int)pParamStruct->nPortIndex);
       PRINT_PARAM(PRINT_GET_PARAM, "eMinBlockSizeP....%d\n", (int)pParamStruct->eMinBlockSizeP);
       PRINT_PARAM(PRINT_GET_PARAM, "eMinBlockSizeB....%d\n", (int)pParamStruct->eMinBlockSizeB);
	 }
	 break;	
	 
   case OMX_TI_IndexParamVideoIntraPredictionSettings:
     {
       OMX_VIDEO_PARAM_INTRAPREDTYPE *pParamStruct = (OMX_VIDEO_PARAM_INTRAPREDTYPE *)pCompCfgStruct; 	 
       
	   PRINT_PARAM(PRINT_GET_PARAM, "\n \rOMX_TI_IndexParamVideoIntraPredictionSettings:\n");	   
	   PRINT_PARAM(PRINT_GET_PARAM, "nSize..................%d\n", (int)pParamStruct->nSize);
       PRINT_PARAM(PRINT_GET_PARAM, "nVersion...............%d\n", (int)pParamStruct->nVersion.nVersion);
       PRINT_PARAM(PRINT_GET_PARAM, "nPortIndex.............%d\n", (int)pParamStruct->nPortIndex);
       PRINT_PARAM(PRINT_GET_PARAM, "nLumaIntra4x4Enable....%d\n", (int)pParamStruct->nLumaIntra4x4Enable);
       PRINT_PARAM(PRINT_GET_PARAM, "nLumaIntra8x8Enable....%d\n", (int)pParamStruct->nLumaIntra8x8Enable);
       PRINT_PARAM(PRINT_GET_PARAM, "nLumaIntra16x16Enable..%d\n", (int)pParamStruct->nLumaIntra16x16Enable);
       PRINT_PARAM(PRINT_GET_PARAM, "nChromaIntra8x8Enable..%d\n", (int)pParamStruct->nChromaIntra8x8Enable);
       PRINT_PARAM(PRINT_GET_PARAM, "eChromaComponentEnable.%d\n", (int)pParamStruct->eChromaComponentEnable);
	 }
	 break;	
	 
   case OMX_TI_IndexParamVideoEncoderPreset:
     {
       OMX_VIDEO_PARAM_ENCODER_PRESETTYPE *pParamStruct = (OMX_VIDEO_PARAM_ENCODER_PRESETTYPE *)pCompCfgStruct; 	 
       
	   PRINT_PARAM(PRINT_GET_PARAM, "\n \rOMX_TI_IndexParamVideoEncoderPreset:\n");		   
	   PRINT_PARAM(PRINT_GET_PARAM, "nSize..................%d\n", (int)pParamStruct->nSize);
       PRINT_PARAM(PRINT_GET_PARAM, "nVersion...............%d\n", (int)pParamStruct->nVersion.nVersion);
       PRINT_PARAM(PRINT_GET_PARAM, "nPortIndex.............%d\n", (int)pParamStruct->nPortIndex);
       PRINT_PARAM(PRINT_GET_PARAM, "eEncodingModePreset....%d\n", (int)pParamStruct->eEncodingModePreset);
       PRINT_PARAM(PRINT_GET_PARAM, "eRateControlPreset.....%d\n", (int)pParamStruct->eRateControlPreset);
	 }
	 break;	
	 
   case OMX_TI_IndexParamVideoFrameDataContentSettings:
     {
       OMX_VIDEO_PARAM_FRAMEDATACONTENTTYPE *pParamStruct = (OMX_VIDEO_PARAM_FRAMEDATACONTENTTYPE *)pCompCfgStruct; 	 
       
	   PRINT_PARAM(PRINT_GET_PARAM, "\n \rOMX_TI_IndexParamVideoFrameDataContentSettings:\n");		   
	   PRINT_PARAM(PRINT_GET_PARAM, "nSize..................%d\n", (int)pParamStruct->nSize);
       PRINT_PARAM(PRINT_GET_PARAM, "nVersion...............%d\n", (int)pParamStruct->nVersion.nVersion);
       PRINT_PARAM(PRINT_GET_PARAM, "nPortIndex.............%d\n", (int)pParamStruct->nPortIndex);
       PRINT_PARAM(PRINT_GET_PARAM, "eContentType...........%d\n", (int)pParamStruct->eContentType);
       PRINT_PARAM(PRINT_GET_PARAM, "eInterlaceCodingType...%d\n", (int)pParamStruct->eInterlaceCodingType);
	 }
	 break;	
   case OMX_TI_IndexParamVideoTransformBlockSize:
     {
       OMX_VIDEO_PARAM_TRANSFORM_BLOCKSIZETYPE *pParamStruct = (OMX_VIDEO_PARAM_TRANSFORM_BLOCKSIZETYPE *)pCompCfgStruct; 	 
       
	   PRINT_PARAM(PRINT_GET_PARAM, "\n \rOMX_TI_IndexParamVideoTransformBlockSize:\n");		   
	   PRINT_PARAM(PRINT_GET_PARAM, "nSize..................%d\n", (int)pParamStruct->nSize);
       PRINT_PARAM(PRINT_GET_PARAM, "nVersion...............%d\n", (int)pParamStruct->nVersion.nVersion);
       PRINT_PARAM(PRINT_GET_PARAM, "nPortIndex.............%d\n", (int)pParamStruct->nPortIndex);
       PRINT_PARAM(PRINT_GET_PARAM, "eTransformBlocksize....%d\n", (int)pParamStruct->eTransformBlocksize);
	 }
	 break;	

   case OMX_TI_IndexParamVideoVUIsettings:
     {
       OMX_VIDEO_PARAM_VUIINFOTYPE *pParamStruct = (OMX_VIDEO_PARAM_VUIINFOTYPE *)pCompCfgStruct; 	 
       
	   PRINT_PARAM(PRINT_GET_PARAM, "\n \rOMX_TI_IndexParamVideoVUIsettings:\n");		   
	   PRINT_PARAM(PRINT_GET_PARAM, "nSize..................%d\n", (int)pParamStruct->nSize);
       PRINT_PARAM(PRINT_GET_PARAM, "nVersion...............%d\n", (int)pParamStruct->nVersion.nVersion);
       PRINT_PARAM(PRINT_GET_PARAM, "nPortIndex.............%d\n", (int)pParamStruct->nPortIndex);
       PRINT_PARAM(PRINT_GET_PARAM, "bAspectRatioPresent....%d\n", (int)pParamStruct->bAspectRatioPresent);
       PRINT_PARAM(PRINT_GET_PARAM, "ePixelAspectRatio......%d\n", (int)pParamStruct->ePixelAspectRatio);
       PRINT_PARAM(PRINT_GET_PARAM, "bFullRange.............%d\n", (int)pParamStruct->bFullRange);
	 }
	 break;		
	 
   case OMX_TI_IndexParamVideoAdvancedFMO:
     {
       OMX_VIDEO_PARAM_AVCADVANCEDFMOTYPE *pParamStruct = (OMX_VIDEO_PARAM_AVCADVANCEDFMOTYPE *)pCompCfgStruct; 	 
       
	   PRINT_PARAM(PRINT_GET_PARAM, "\n \rOMX_TI_IndexParamVideoAdvancedFMO:\n");		   
	   PRINT_PARAM(PRINT_GET_PARAM, "nSize..................%d\n", (int)pParamStruct->nSize);
       PRINT_PARAM(PRINT_GET_PARAM, "nVersion...............%d\n", (int)pParamStruct->nVersion.nVersion);
       PRINT_PARAM(PRINT_GET_PARAM, "nPortIndex.............%d\n", (int)pParamStruct->nPortIndex);
       PRINT_PARAM(PRINT_GET_PARAM, "nNumSliceGroups........%d\n", (int)pParamStruct->nNumSliceGroups);
       PRINT_PARAM(PRINT_GET_PARAM, "nSliceGroupMapType.....%d\n", (int)pParamStruct->nSliceGroupMapType);
       PRINT_PARAM(PRINT_GET_PARAM, "eSliceGrpChangeDir.....%d\n", (int)pParamStruct->eSliceGrpChangeDir);
       PRINT_PARAM(PRINT_GET_PARAM, "nSliceGroupChangeRate..%d\n", (int)pParamStruct->nSliceGroupChangeRate);
       PRINT_PARAM(PRINT_GET_PARAM, "nSliceGroupChangeCycle.%d\n", (int)pParamStruct->nSliceGroupChangeCycle);
	 }
	 break;		
	 
   case OMX_IndexConfigVideoBitrate:
     {
       OMX_VIDEO_CONFIG_BITRATETYPE *pParamStruct = (OMX_VIDEO_CONFIG_BITRATETYPE *)pCompCfgStruct; 	 	 
      
	   PRINT_PARAM(PRINT_GET_PARAM, "\n \rOMX_IndexConfigVideoBitrate:\n");		  
 	   PRINT_PARAM(PRINT_GET_PARAM, "nSize.............%d\n", (int)pParamStruct->nSize);
       PRINT_PARAM(PRINT_GET_PARAM, "nVersion..........%d\n", (int)pParamStruct->nVersion.nVersion);
       PRINT_PARAM(PRINT_GET_PARAM, "nPortIndex........%d\n", (int)pParamStruct->nPortIndex);
       PRINT_PARAM(PRINT_GET_PARAM, "nEncodeBitrate....%d\n", (int)pParamStruct->nEncodeBitrate);
	 }
	 break;	
	 
   case OMX_IndexConfigVideoFramerate:
     {
       OMX_CONFIG_FRAMERATETYPE *pParamStruct = (OMX_CONFIG_FRAMERATETYPE *)pCompCfgStruct; 	 	 
       
	   PRINT_PARAM(PRINT_GET_PARAM, "\n \rOMX_IndexConfigVideoFramerate:\n");		   
	   PRINT_PARAM(PRINT_GET_PARAM, "nSize.............%d\n", (int)pParamStruct->nSize);
       PRINT_PARAM(PRINT_GET_PARAM, "nVersion..........%d\n", (int)pParamStruct->nVersion.nVersion);
       PRINT_PARAM(PRINT_GET_PARAM, "nPortIndex........%d\n", (int)pParamStruct->nPortIndex);
       PRINT_PARAM(PRINT_GET_PARAM, "xEncodeFramerate..%d\n", (int)pParamStruct->xEncodeFramerate);
	 }
	 break;	
	 
   case OMX_IndexConfigVideoAVCIntraPeriod:
     {
       OMX_VIDEO_CONFIG_AVCINTRAPERIOD *pParamStruct = (OMX_VIDEO_CONFIG_AVCINTRAPERIOD *)pCompCfgStruct; 	 	 
       
	   PRINT_PARAM(PRINT_GET_PARAM, "\n \rOMX_IndexConfigVideoAVCIntraPeriod:\n");	   
	   PRINT_PARAM(PRINT_GET_PARAM, "nSize.............%d\n", (int)pParamStruct->nSize);
       PRINT_PARAM(PRINT_GET_PARAM, "nVersion..........%d\n", (int)pParamStruct->nVersion.nVersion);
       PRINT_PARAM(PRINT_GET_PARAM, "nPortIndex........%d\n", (int)pParamStruct->nPortIndex);
       PRINT_PARAM(PRINT_GET_PARAM, "nIDRPeriod........%d\n", (int)pParamStruct->nIDRPeriod);
       PRINT_PARAM(PRINT_GET_PARAM, "nPFrames..........%d\n", (int)pParamStruct->nPFrames);
	 }
	 break;	
	 
   case OMX_IndexConfigVideoIntraVOPRefresh:
     {
       OMX_CONFIG_INTRAREFRESHVOPTYPE *pParamStruct = (OMX_CONFIG_INTRAREFRESHVOPTYPE *)pCompCfgStruct; 	 	 
       
	   PRINT_PARAM(PRINT_GET_PARAM, "\n \rOMX_IndexConfigVideoIntraVOPRefresh:\n");	   
	   PRINT_PARAM(PRINT_GET_PARAM, "nSize.............%d\n", (int)pParamStruct->nSize);
       PRINT_PARAM(PRINT_GET_PARAM, "nVersion..........%d\n", (int)pParamStruct->nVersion.nVersion);
       PRINT_PARAM(PRINT_GET_PARAM, "nPortIndex........%d\n", (int)pParamStruct->nPortIndex);
       PRINT_PARAM(PRINT_GET_PARAM, "IntraRefreshVOP...%d\n", (int)pParamStruct->IntraRefreshVOP);	   
	 }
	 break;	
	 
   case OMX_IndexConfigVideoNalSize:
     {
       OMX_VIDEO_CONFIG_NALSIZE *pParamStruct = (OMX_VIDEO_CONFIG_NALSIZE *)pCompCfgStruct; 	 	 
	   
	   PRINT_PARAM(PRINT_GET_PARAM, "\n \rOMX_IndexConfigVideoNalSize:\n");	        
	   PRINT_PARAM(PRINT_GET_PARAM, "nSize.............%d\n", (int)pParamStruct->nSize);
       PRINT_PARAM(PRINT_GET_PARAM, "nVersion..........%d\n", (int)pParamStruct->nVersion.nVersion);
       PRINT_PARAM(PRINT_GET_PARAM, "nPortIndex........%d\n", (int)pParamStruct->nPortIndex);
       PRINT_PARAM(PRINT_GET_PARAM, "nNaluBytes........%d\n", (int)pParamStruct->nNaluBytes);	 	   
	 }
	 break;	
	 
   case OMX_TI_IndexConfigVideoPixelInfo:
     {
       OMX_VIDEO_CONFIG_PIXELINFOTYPE *pParamStruct = (OMX_VIDEO_CONFIG_PIXELINFOTYPE *)pCompCfgStruct; 	 	 
       
	   PRINT_PARAM(PRINT_GET_PARAM, "\n \rOMX_TI_IndexConfigVideoPixelInfo:\n");	  
	   PRINT_PARAM(PRINT_GET_PARAM, "nSize.............%d\n", (int)pParamStruct->nSize);
       PRINT_PARAM(PRINT_GET_PARAM, "nVersion..........%d\n", (int)pParamStruct->nVersion.nVersion);
       PRINT_PARAM(PRINT_GET_PARAM, "nPortIndex........%d\n", (int)pParamStruct->nPortIndex);
       PRINT_PARAM(PRINT_GET_PARAM, "nWidth........... %d\n", (int)pParamStruct->nWidth);		   
       PRINT_PARAM(PRINT_GET_PARAM, "nHeight...........%d\n", (int)pParamStruct->nHeight);		   
	 }
	 break;	
	 
   case OMX_TI_IndexConfigVideoMESearchRange:
     {
       OMX_VIDEO_CONFIG_MESEARCHRANGETYPE *pParamStruct = (OMX_VIDEO_CONFIG_MESEARCHRANGETYPE *)pCompCfgStruct; 	 	 
       
       PRINT_PARAM(PRINT_GET_PARAM, "\n \rOMX_TI_IndexConfigVideoMESearchRange:\n");	 
	   PRINT_PARAM(PRINT_GET_PARAM, "nSize............ %d\n", (int)pParamStruct->nSize);
       PRINT_PARAM(PRINT_GET_PARAM, "nVersion..........%d\n", (int)pParamStruct->nVersion.nVersion);
       PRINT_PARAM(PRINT_GET_PARAM, "nPortIndex........%d\n", (int)pParamStruct->nPortIndex);
       PRINT_PARAM(PRINT_GET_PARAM, "eMVAccuracy.......%d\n", (int)pParamStruct->eMVAccuracy);
       PRINT_PARAM(PRINT_GET_PARAM, "nHorSearchRangeP..%d\n", (int)pParamStruct->nHorSearchRangeP);
       PRINT_PARAM(PRINT_GET_PARAM, "nVerSearchRangeP..%d\n", (int)pParamStruct->nVerSearchRangeP);
       PRINT_PARAM(PRINT_GET_PARAM, "nHorSearchRangeB..%d\n", (int)pParamStruct->nHorSearchRangeB);
       PRINT_PARAM(PRINT_GET_PARAM, "nVerSearchRangeB..%d\n", (int)pParamStruct->nVerSearchRangeB);
	 }
	 break;	
	 
   case OMX_TI_IndexConfigVideoQPSettings:
     {
       OMX_VIDEO_CONFIG_QPSETTINGSTYPE *pParamStruct = (OMX_VIDEO_CONFIG_QPSETTINGSTYPE *)pCompCfgStruct; 	 	 

       PRINT_PARAM(PRINT_GET_PARAM, "\n \rOMX_TI_IndexConfigVideoQPSettings:\n");	       
	   PRINT_PARAM(PRINT_GET_PARAM, "nSize.............%d\n", (int)pParamStruct->nSize);
       PRINT_PARAM(PRINT_GET_PARAM, "nVersion..........%d\n", (int)pParamStruct->nVersion.nVersion);
       PRINT_PARAM(PRINT_GET_PARAM, "nPortIndex........%d\n", (int)pParamStruct->nPortIndex);
       PRINT_PARAM(PRINT_GET_PARAM, "nQpI..............%d\n", (int)pParamStruct->nQpI);
       PRINT_PARAM(PRINT_GET_PARAM, "nQpMaxI...........%d\n", (int)pParamStruct->nQpMaxI);
       PRINT_PARAM(PRINT_GET_PARAM, "nQpMinI...........%d\n", (int)pParamStruct->nQpMinI);
       PRINT_PARAM(PRINT_GET_PARAM, "nQpP..............%d\n", (int)pParamStruct->nQpP);
       PRINT_PARAM(PRINT_GET_PARAM, "nQpMaxP...........%d\n", (int)pParamStruct->nQpMaxP);
       PRINT_PARAM(PRINT_GET_PARAM, "nQpMinP...........%d\n", (int)pParamStruct->nQpMinP);
       PRINT_PARAM(PRINT_GET_PARAM, "nQpOffsetB........%d\n", (int)pParamStruct->nQpOffsetB);
       PRINT_PARAM(PRINT_GET_PARAM, "nQpMaxB...........%d\n", (int)pParamStruct->nQpMaxB);
       PRINT_PARAM(PRINT_GET_PARAM, "nQpMinB...........%d\n", (int)pParamStruct->nQpMinB);
	 }
	 break;	
	 
   case OMX_TI_IndexConfigSliceSettings:
     {
       OMX_VIDEO_CONFIG_SLICECODINGTYPE *pParamStruct = (OMX_VIDEO_CONFIG_SLICECODINGTYPE *)pCompCfgStruct; 	 	 
       
       PRINT_PARAM(PRINT_GET_PARAM, "\n \rOMX_TI_IndexConfigSliceSettings:\n");		   
	   PRINT_PARAM(PRINT_GET_PARAM, "nSize.............%d\n", (int)pParamStruct->nSize);
       PRINT_PARAM(PRINT_GET_PARAM, "nVersion..........%d\n", (int)pParamStruct->nVersion.nVersion);
       PRINT_PARAM(PRINT_GET_PARAM, "nPortIndex........%d\n", (int)pParamStruct->nPortIndex);
       PRINT_PARAM(PRINT_GET_PARAM, "eSliceMode........%d\n", (int)pParamStruct->eSliceMode);
       PRINT_PARAM(PRINT_GET_PARAM, "nSlicesize........%d\n", (int)pParamStruct->nSlicesize);
	 }
	 break;		 
	 
   /* Add VDEC indexes here*/
   case OMX_IndexParamVideoMacroblocksPerFrame:
     {
       OMX_PARAM_MACROBLOCKSTYPE *pParamStruct = (OMX_PARAM_MACROBLOCKSTYPE *)pCompCfgStruct; 	 	 

	   PRINT_PARAM(PRINT_GET_PARAM, "\n \rOMX_IndexParamVideoMacroblocksPerFrame:\n");       
	   PRINT_PARAM(PRINT_GET_PARAM, "nSize.................................%d\n", (int)pParamStruct->nSize);
       PRINT_PARAM(PRINT_GET_PARAM, "nVersion..............................%d\n", (int)pParamStruct->nVersion.nVersion);
       PRINT_PARAM(PRINT_GET_PARAM, "nPortIndex............................%d\n", (int)pParamStruct->nPortIndex);
       PRINT_PARAM(PRINT_GET_PARAM, "nMacroblocks.........................%d\n", (int)pParamStruct->nMacroblocks);
	 }
	 break;
	 case OMX_IndexConfigVideoMacroBlockErrorMap:
     {
       OMX_CONFIG_MBERRORREPORTINGTYPE *pParamStruct = (OMX_CONFIG_MBERRORREPORTINGTYPE *)pCompCfgStruct; 	 	 

	   PRINT_PARAM(PRINT_SET_PARAM, "\n \rOMX_TI_IndexParamFileModeType:\n");       
	   PRINT_PARAM(PRINT_SET_PARAM, "nSize.................................%d\n", (int)pParamStruct->nSize);
       PRINT_PARAM(PRINT_SET_PARAM, "nVersion..............................%d\n", (int)pParamStruct->nVersion.nVersion);
       PRINT_PARAM(PRINT_SET_PARAM, "nPortIndex............................%d\n", (int)pParamStruct->nPortIndex);
       PRINT_PARAM(PRINT_SET_PARAM, "bEnabled..............................%d\n", (int)pParamStruct->bEnabled);
	 }
	 break;	 	 
   /* Add VSRC/VSNK indexes here*/   
   default:
     {
	   /*Base Index which will be common for all the components*/	
       OMTBBASE_DisplayGetParams(nParamIndex, pCompCfgStruct);
     } 
	 break;   
  }
}  

/******************************************************************************\
 *      OMTBBASE_DisplayGetParams Function Prototype
\******************************************************************************/
/**
 *
 *  @brief    This Function print the values of the index on output console/file
 *
 *  @param    nParamIndex
 *            pCompCfgStruct
 *
 *  @return   None
 */
void OMTBBASE_DisplayGetParams(unsigned int nParamIndex, OMX_PTR pCompCfgStruct)
{
 
 unsigned int i = 0;
 
 switch (nParamIndex)
 {
   case OMX_IndexParamAudioInit:
     { 
       OMX_PORT_PARAM_TYPE *pParamStruct = (OMX_PORT_PARAM_TYPE *)pCompCfgStruct;
	   
       PRINT_PARAM(PRINT_GET_PARAM, "\n \rOMX_IndexParamAudioInit:\n");
       PRINT_PARAM(PRINT_GET_PARAM, "\n \rOMX_TI_IndexConfigSliceSettings:\n");
       PRINT_PARAM(PRINT_GET_PARAM, "nSize.............%d\n", (int)pParamStruct->nSize);
	   PRINT_PARAM(PRINT_GET_PARAM, "nVersion..........%d\n", (int)pParamStruct->nVersion.nVersion);
	   PRINT_PARAM(PRINT_GET_PARAM, "nPorts............%d\n", (int)pParamStruct->nPorts);
	   PRINT_PARAM(PRINT_GET_PARAM, "nStartPortNumber..%d\n", (int)pParamStruct->nStartPortNumber);
     }
     break;
    
   case OMX_IndexParamImageInit:
     { 
       OMX_PORT_PARAM_TYPE *pParamStruct = (OMX_PORT_PARAM_TYPE *)pCompCfgStruct;
	   
       PRINT_PARAM(PRINT_GET_PARAM, "\n \rOMX_IndexParamImageInit:\n");	   
       PRINT_PARAM(PRINT_GET_PARAM, "nSize.............%d\n", (int)pParamStruct->nSize);
	   PRINT_PARAM(PRINT_GET_PARAM, "nVersion..........%d\n", (int)pParamStruct->nVersion.nVersion);
	   PRINT_PARAM(PRINT_GET_PARAM, "nPorts............%d\n", (int)pParamStruct->nPorts);
	   PRINT_PARAM(PRINT_GET_PARAM, "nStartPortNumber..%d\n", (int)pParamStruct->nStartPortNumber);
     }
     break;
	 
   case OMX_IndexParamVideoInit:
     { 
       OMX_PORT_PARAM_TYPE *pParamStruct = (OMX_PORT_PARAM_TYPE *)pCompCfgStruct;
	   
       PRINT_PARAM(PRINT_GET_PARAM, "\n \rOMX_IndexParamVideoInit:\n");	   
       PRINT_PARAM(PRINT_GET_PARAM, "nSize.............%d\n", (int)pParamStruct->nSize);
	   PRINT_PARAM(PRINT_GET_PARAM, "nVersion..........%d\n", (int)pParamStruct->nVersion.nVersion);
	   PRINT_PARAM(PRINT_GET_PARAM, "nPorts............%d\n", (int)pParamStruct->nPorts);
	   PRINT_PARAM(PRINT_GET_PARAM, "nStartPortNumber..%d\n", (int)pParamStruct->nStartPortNumber);
     }
     break;
	 
   case OMX_IndexParamOtherInit:
     { 
       OMX_PORT_PARAM_TYPE *pParamStruct = (OMX_PORT_PARAM_TYPE *)pCompCfgStruct;
	   
       PRINT_PARAM(PRINT_GET_PARAM, "\n \rOMX_IndexParamOtherInit:\n");	   
       PRINT_PARAM(PRINT_GET_PARAM, "nSize.............%d\n", (int)pParamStruct->nSize);
	   PRINT_PARAM(PRINT_GET_PARAM, "nVersion..........%d\n", (int)pParamStruct->nVersion.nVersion);
	   PRINT_PARAM(PRINT_GET_PARAM, "nPorts............%d\n", (int)pParamStruct->nPorts);
	   PRINT_PARAM(PRINT_GET_PARAM, "nStartPortNumber..%d\n", (int)pParamStruct->nStartPortNumber);
     }
     break;	 

   case OMX_IndexParamPortDefinition:
     { 
       OMX_PARAM_PORTDEFINITIONTYPE *pParamStruct = (OMX_PARAM_PORTDEFINITIONTYPE *)pCompCfgStruct;
	   
       PRINT_PARAM(PRINT_GET_PARAM, "\n \rOMX_IndexParamPortDefinition:\n");	  	   
       PRINT_PARAM(PRINT_GET_PARAM, "nSize..................%d\n", (int)pParamStruct->nSize);
	   PRINT_PARAM(PRINT_GET_PARAM, "nVersion...............%d\n", (int)pParamStruct->nVersion.nVersion);
       PRINT_PARAM(PRINT_GET_PARAM, "nPortIndex.............%d\n", (int)pParamStruct->nPortIndex);
	   PRINT_PARAM(PRINT_GET_PARAM, "eDir...................%d\n", (int)pParamStruct->eDir);
       PRINT_PARAM(PRINT_GET_PARAM, "nBufferCountActual.....%d\n", (int)pParamStruct->nBufferCountActual);
	   PRINT_PARAM(PRINT_GET_PARAM, "nBufferCountMin........%d\n", (int)pParamStruct->nBufferCountMin);
       PRINT_PARAM(PRINT_GET_PARAM, "nBufferSize............%d\n", (int)pParamStruct->nBufferSize);
	   PRINT_PARAM(PRINT_GET_PARAM, "bEnabled...............%d\n", (int)pParamStruct->bEnabled);
       PRINT_PARAM(PRINT_GET_PARAM, "bPopulated.............%d\n", (int)pParamStruct->bPopulated);
	   PRINT_PARAM(PRINT_GET_PARAM, "eDomain................%d\n", (int)pParamStruct->eDomain);

       PRINT_PARAM(PRINT_GET_PARAM, "bBuffersContiguous.....%d\n", (int)pParamStruct->bBuffersContiguous);	
       PRINT_PARAM(PRINT_GET_PARAM, "nBufferAlignment.......%d\n", (int)pParamStruct->nBufferAlignment);		   
     }
     break;

   case OMX_IndexParamCompBufferSupplier:
     { 
       OMX_PARAM_BUFFERSUPPLIERTYPE *pParamStruct = (OMX_PARAM_BUFFERSUPPLIERTYPE *)pCompCfgStruct;
	   
       PRINT_PARAM(PRINT_GET_PARAM, "\n \rOMX_IndexParamCompBufferSupplier:\n");	  	   
       PRINT_PARAM(PRINT_GET_PARAM, "nSize.............%d\n", (int)pParamStruct->nSize);
       PRINT_PARAM(PRINT_GET_PARAM, "nVersion..........%d\n", (int)pParamStruct->nVersion.nVersion);
       PRINT_PARAM(PRINT_GET_PARAM, "nPortIndex........%d\n", (int)pParamStruct->nPortIndex);	   
       PRINT_PARAM(PRINT_GET_PARAM, "eBufferSupplier...%d\n", (int)pParamStruct->eBufferSupplier);
     }
     break;

   case OMX_IndexParamPriorityMgmt:
     { 
       OMX_PRIORITYMGMTTYPE *pParamStruct = (OMX_PRIORITYMGMTTYPE *)pCompCfgStruct;
	   
       PRINT_PARAM(PRINT_GET_PARAM, "\n \rOMX_IndexParamPriorityMgmt:\n");	  	   	   
       PRINT_PARAM(PRINT_GET_PARAM, "nSize.............%d\n", (int)pParamStruct->nSize);
       PRINT_PARAM(PRINT_GET_PARAM, "nVersion..........%d\n", (int)pParamStruct->nVersion.nVersion);
       PRINT_PARAM(PRINT_GET_PARAM, "nGroupPriority....%d\n", (int)pParamStruct->nGroupPriority);
       PRINT_PARAM(PRINT_GET_PARAM, "nGroupID..........%d\n", (int)pParamStruct->nGroupID);	   
     }
     break;

   case OMX_TI_IndexParamBuffMemType:
     {
       OMX_PARAM_BUFFER_MEMORYTYPE *pParamStruct = (OMX_PARAM_BUFFER_MEMORYTYPE *)pCompCfgStruct;
	   
       PRINT_PARAM(PRINT_GET_PARAM, "\n \rOMX_TI_IndexParamBuffMemType:\n");		   
       PRINT_PARAM(PRINT_GET_PARAM, "nSize.............%d\n", (int)pParamStruct->nSize);
       PRINT_PARAM(PRINT_GET_PARAM, "nVersion..........%d\n", (int)pParamStruct->nVersion.nVersion);
       PRINT_PARAM(PRINT_GET_PARAM, "nPortIndex........%d\n", (int)pParamStruct->nPortIndex);
       PRINT_PARAM(PRINT_GET_PARAM, "eBufMemoryType....%d\n", (int)pParamStruct->eBufMemoryType);	  	 
     }
     break; 	 

   default:
     { 
       /* Add this index in OMTB code if default case is selected */
	   PRINT_PARAM(PRINT_GET_PARAM, "Index not supported by OMTB\n");
     }
     break;
 }
}
/*----------------------------- end of file ----------------------------------*/


