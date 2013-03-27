#*****************************************************************************\
# Copyright © 2009 Texas Instruments Incorporated - http://www.ti.com/
#*****************************************************************************/
##  @file       Makefile
 #
 #  @brief      Platform specific makefile.
 #

APP_NAME = dm81xxbm

SRCDIR = ./../../core/classes/h264venc/src \
./../../core/classes/h264vdec/src \
./../../core/classes/vdec/src \
./../../core/classes/adec/src \
./../../core/classes/hdvpss/vfcc/src \
./../../core/classes/hdvpss/tvp/src \
./../../core/classes/hdvpss/vfdc/src \
./../../core/classes/hdvpss/dc/src \
./../../core/classes/hdvpss/vfpc/src \
./../../core/classes/arecord/src \
./../../core/classes/aplay/src \
./../../core/common/src \
./../../core/parser/src \
./src \
./../src \

INCDIR = ./../../core/classes/h264vdec/inc \
./../../core/classes/h264venc/inc \
./../../core/classes/vdec/inc \
./../../core/classes/adec/inc \
./../../core/classes/hdvpss/vfcc/inc \
./../../core/classes/hdvpss/tvp/inc \
./../../core/classes/hdvpss/vfdc/inc \
./../../core/classes/hdvpss/dc/inc \
./../../core/classes/hdvpss/vfpc/inc \
./../../core/classes/arecord/inc \
./../../core/classes/aplay/inc \
./../../core/common/inc \
./../../core/parser/inc \
./inc \
./../inc \
$(audio_INCLUDE)/include


# List all the external components/interfaces, whose interface header files 
#  need to be included for this component
INCLUDE_EXERNAL_INTERFACES = bios xdc omx timmosal hdvpss ipc fc xdais osal syslink audio \
                             ce h264enc h264dec

# List of all external libraries that need to be linked
EXTLIBS_m3video =
EXTLIBS_m3vpss =
EXTLIBS_a8host = $(omx_PATH)/lib/omxcore.av5T \
                 $(omx_PATH)/lib/memcfg.av5T \
                 $(omx_PATH)/lib/domx.av5T \
                 $(omx_PATH)/lib/domx_delegates_shmem.av5T \
                 $(omx_PATH)/lib/timmosal.av5T \
                 $(omx_PATH)/lib/omxcfg.av5T \
                 $(osal_PATH)/packages/linuxdist/build/lib/osal.a \
                 $(osal_PATH)/packages/linuxdist/cstubs/lib/cstubs.a \
                 $(fc_PATH)/packages/ti/sdo/rcm/lib/debug/rcm_syslink.av5T \
                 $(fc_PATH)/packages/ti/sdo/fc/memutils/lib/release/memutils.av5T \
                 $(osal_PATH)/packages/ti/sdo/xdcruntime/linux/lib/debug/osal_linux_470.av5T \
                 $(fc_PATH)/packages/ti/sdo/fc/global/lib/debug/fcsettings.av5T \
                 $(syslink_PATH)/packages/ti/syslink/lib/syslink.a_release \
                 $(linuxutils_PATH)/packages/ti/sdo/linuxutils/cmem/lib/cmem.a470MV \
                 $(uia_PATH)/packages/ti/uia/linux/lib/servicemgr.a \
                 -L$(lindevkit_PATH)/lib -lasound -lncursesw -lreadline
#                 ./lib/libedit.a
#                 $(slog_PATH)/lib/slog.a \

# List all the components required by the application
COMP_LIST_m3video = 
COMP_LIST_m3vpss = 
COMP_LIST_a8host = 

# XDC CFG File
XDC_CFG_FILE_m3vpss = ../omtbAppMain.cfg
XDC_CFG_FILE_m3video = ../omtbAppMain.cfg

# Common source files and CFLAGS across all platforms and cores
SRCS_COMMON =
CFLAGS_LOCAL_COMMON = -DGlobal_appTerminate=0

SRCS_a8host =  omtbH264Venc.c omtbH264VencApi.c omtbH264VencApiCmdEntries.c omtbH264VencCfgCmdEntries.c omtbH264VencParser.c \
               omtbH264Vdec.c omtbH264VdecApi.c omtbH264VdecApiCmdEntries.c omtbH264VdecCfgCmdEntries.c omtbH264VdecParser.c \
               omtbVdec.c omtbVdecApi.c omtbVdecApiCmdEntries.c omtbVdecCfgCmdEntries.c omtbMpeg2VdecParser.c \
               omtbAdec.c omtbAdecApi.c omtbAdecApiCmdEntries.c omtbAdecCfgCmdEntries.c \
               omtbHDVPSSVfcc.c omtbHDVPSSVfccApi.c omtbHDVPSSVfccApiCmdEntries.c omtbHDVPSSVfccCfgCmdEntries.c \
               omtbHDVPSSTvp.c omtbHDVPSSTvpApi.c  omtbHDVPSSTvpApiCmdEntries.c  omtbHDVPSSTvpCfgCmdEntries.c \
               omtbHDVPSSVfdc.c omtbHDVPSSVfdcApi.c omtbHDVPSSVfdcApiCmdEntries.c omtbHDVPSSVfdcCfgCmdEntries.c \
               omtbHDVPSSDc.c omtbHDVPSSDcApi.c omtbHDVPSSDcApiCmdEntries.c omtbHDVPSSDcCfgCmdEntries.c \
               omtbHDVPSSVfpcDei.c omtbHDVPSSVfpcDeiApi.c omtbHDVPSSVfpcDeiApiCmdEntries.c omtbHDVPSSVfpcDeiCfgCmdEntries.c \
               omtbHDVPSSVfpcNf.c omtbHDVPSSVfpcNfApi.c omtbHDVPSSVfpcNfApiCmdEntries.c omtbHDVPSSVfpcNfCfgCmdEntries.c \
               omtbHDVPSSVfpcSc.c omtbHDVPSSVfpcScApi.c omtbHDVPSSVfpcScApiCmdEntries.c omtbHDVPSSVfpcScCfgCmdEntries.c \
               omtbAlsaRecord.c omtbAlsaRecordApi.c omtbAlsaRecordApiCmdEntries.c omtbAlsaRecordCfgCmdEntries.c \
               omtbAlsaPlay.c omtbAlsaPlayApi.c omtbAlsaPlayApiCmdEntries.c omtbAlsaPlayCfgCmdEntries.c \
               omtbApiTest.c omtbApiTestCmdEntries.c omtbApi.c omtbApiCmdEntries.c omtbCmd.c omtbCmdEntries.c \
               omtbMain.c omtbTemplateManager.c omtbClient.c\
               cmdLine.c dbgCmd.c mvxDbg.c \
               omtbDisplayParams.c  omtbSetpIndex.c \
               omtbCortexA8AppInit.c omtbCortexA8Common.c \
               omtbCortexA8Main.c omtbCortexA8Platform.c

CFLAGS_LOCAL_a8host = -DGlobal_GrpxDssMsgHeapId=6 -DGlobal_TilerHeapId=7

# Core/SoC/platform specific source files and CFLAGS
# Example: 
#   SRCS_<core/SoC/platform-name> = 
#   CFLAGS_LOCAL_<core/SoC/platform-name> =

ifeq ($(CORE),a8host)
  CFLAGS_LOCAL_a8host += -D_LOCAL_CORE_a8host_ -DREADLINE=1 -DUSE_LIBEDIT
endif

# Include common make files
include $(ROOTDIR)/makerules/common.mk

# OBJs and libraries are built by using rule defined in rules_<target>.mk 
#     and need not be explicitly specified here

#################################### End of file ##############################