# File: env.mk. This file contains all the paths and other ENV variables

#
# Module paths
#

# Directory where all internal software packages are located; typically 
#  those that are checked into version controlled repository. In this case all
#  the OMX components and SDK/OMX demo.
OMX_INSTALL_DIR = U:/avmecomp

# Directory where all external (imported) software packages are located; typically 
#  those that are NOT checked into version controlled repository. In this case,
#  compiler tool chains, BIOS, XDC, Syslink, IPC, FC, CE, drivers, codecs, etc.
EZSDK_INSTALL_DIR =  E:/share/sdktools

#OMTB ROOT DIRECTORY
OMTB_ROOT = $(ROOTDIR)
export OMTB_ROOT

# Destination root directory.
#   - specify the directory where you want to place the object, archive/library,
#     binary and other generated files in a different location than source tree
#   - or leave it blank to place then in the same tree as the source
DEST_ROOT = $(OMTB_ROOT)/bin

# Utilities directory. This is required only if the build machine is Windows.
#   - specify the installation directory of utility which supports POSIX commands
#     (eg: Cygwin installation or MSYS installation).
UTILS_INSTALL_DIR = C:/cygwin


#Code sourcery tool
CSTOOL_DIR = E:/share/sdktools/CodeSourcery/2009q1-203

# Set path separator, etc based on the OS
ifeq ($(OS),Windows_NT)
  PATH_SEPARATOR = ;
  UTILSPATH = $(UTILS_INSTALL_DIR)/bin/
else 
  # else, assume it is linux
  PATH_SEPARATOR = :
endif

# BIOS

bios_PATH = $(EZSDK_INSTALL_DIR)/bios_6_32_01_38
bios_INCLUDE = $(bios_PATH)/packages

# FC - Framework Components
fc_PATH = $(EZSDK_INSTALL_DIR)/framework_components_3_21_00_21_eng
fc_INCLUDE = $(fc_PATH)/packages

# CE - Codec Engine
ce_PATH =$(EZSDK_INSTALL_DIR)/codec_engine_3_21_00_17_eng
ce_INCLUDE = $(ce_PATH)/packages

# H264ENC - H.264 Encoder
h264enc_PATH = $(EZSDK_INSTALL_DIR)/ivahd_h264enc_01_00_03_00_production
h264enc_INCLUDE = $(h264enc_PATH)/packages

# H264DEC - H.264 Decoder
h264dec_PATH = $(EZSDK_INSTALL_DIR)/ivahd_h264dec_01_00_00_02_production
h264dec_INCLUDE = $(h264dec_PATH)/packages

# MPEG2DEC - MPEG2 Decoder
mpeg2dec_PATH = $(EZSDK_INSTALL_DIR)/ivahd_mpeg2vdec_01_00_01_00_production
mpeg2dec_INCLUDE = $(mpeg2dec_PATH)/packages

# MPEG2ENC - MPEG2 Encoder
mpeg2enc_PATH = $(EZSDK_INSTALL_DIR)/codecs-dm816x_5_00_00_00
mpeg2enc_INCLUDE = $(mpeg2enc_PATH)/packages

# HDVICP20API - HDVICP 2.0 API module
hdvicp20api_PATH = $(EZSDK_INSTALL_DIR)/ivahd_hdvicp20api_01_00_00_19_production
hdvicp20api_INCLUDE = $(hdvicp20api_PATH)/packages

# IPC
ipc_PATH = $(EZSDK_INSTALL_DIR)/ipc_1_23_01_26
ipc_INCLUDE = $(ipc_PATH)/packages
# OSAL
osal_PATH = $(EZSDK_INSTALL_DIR)/osal_1_21_00_07
osal_INCLUDE = $(osal_PATH)/packages

# XDAIS
xdais_PATH = $(EZSDK_INSTALL_DIR)/xdais_7_21_00_02
xdais_INCLUDE = $(xdais_PATH)/packages

# LINUXUTILS
linuxutils_PATH = $(EZSDK_INSTALL_DIR)/linuxutils_3_21_00_03_eng
linuxutils_INCLUDE = $(linuxutils_PATH)/packages

# SYSLINK 
syslink_PATH = $(EZSDK_INSTALL_DIR)/syslink_2_00_00_78
syslink_INCLUDE = $(syslink_PATH)/packages

# XDC
xdc_PATH = $(EZSDK_INSTALL_DIR)/xdctools_3_22_01_21
xdc_INCLUDE = $(xdc_PATH)/packages

#UIA 
uia_PATH = $(EZSDK_INSTALL_DIR)/uia_1_00_01_17
uia_INCLUDE = $(uia_PATH)/packages

# HDVPSS drivers

hdvpss_PATH = $(EZSDK_INSTALL_DIR)/hdvpss_01_00_01_28
hdvpss_INCLUDE = $(hdvpss_PATH)/packages
-include $(hdvpss_PATH)/component.mk
export hdvpss_PATH

# Linux Dev Kit
lindevkit_PATH = $(EZSDK_INSTALL_DIR)/linux-devkit/arm-none-linux-gnueabi/usr
lindevkit_INCLUDE = $(lindevkit_PATH)/include

# PSP
psp_PATH = $(EZSDK_INSTALL_DIR)/TI816X-LINUX-PSP-04.00.00.12
psp_INCLUDE = $(psp_PATH)/src/kernel/linux-04.00.00.12/include $(psp_PATH)/src/kernel/linux-04.00.00.12/arch/arm/include

# Audio (ALSA)
audio_INCLUDE = $(lindevkit_INCLUDE)

# RTP library
rtp_PATH = $(EZSDK_INSTALL_DIR)/ortp_0.14.2

# OMX Top-level package directory
omx_PATH = $(OMX_INSTALL_DIR)
include $(OMTB_ROOT)/component.mk



# SLog
slog_PATH = $(EZSDK_INSTALL_DIR)/slog_3_2
slog_INCLUDE = $(slog_PATH)

#
# Tools paths
#
# Cortex-M3

CODEGEN_PATH_M3 = $(EZSDK_INSTALL_DIR)/cgt470_4_9_0

# Cortex-A8
CODEGEN_PATH_A8 = $(CSTOOL_DIR)

# DSP
CODEGEN_PATH_DSP = 


# Commands commonly used within the make files

RM = $(UTILSPATH)rm
RMDIR = $(UTILSPATH)rm -rf
MKDIR = $(UTILSPATH)mkdir
ECHO = @echo
# MAKE = $(UTILSPATH)make
EGREP = $(UTILSPATH)egrep
CP = $(UTILSPATH)cp
CHMOD = $(UTILSPATH)chmod

#
# XDC specific ENV variables
#

# XDC Config.bld file (required for configuro) ; Derives from top-level omx_PATH
CONFIG_BLD_XDC_m3 = $(omx_PATH)/ti/omx/build/config.bld
CONFIG_BLD_XDC_a8 = $(omx_PATH)/ti/omx/build/config_ca8.bld

XDCPATH = $(bios_PATH)/packages;$(fc_PATH)/packages;$(hdvpss_PATH)/packages;$(ipc_PATH)/packages;$(syslink_PATH);$(xdc_PATH)/packages;$(ce_PATH)/packages;$(omx_PATH);$(omx_PATH)/ti/omx/interfaces/openMaxv11;.;$(h264enc_PATH)/packages;$(h264dec_PATH)/packages;$(mpeg2dec_PATH)/packages;$(mpeg2enc_PATH)/packages;$(omx_PATH)/ti/omx/comp/omxbase;$(omx_PATH)/ti/omx/omxcore;$(hdvicp20api_PATH)/packages;$(osal_PATH)/packages;$(xdais_PATH)/packages;$(linuxutils_PATH)/packages;$(OMTB_ROOT)/packages;$(uia_PATH)/packages;
export XDCPATH

XDCROOT = $(xdc_PATH)
XDCTOOLS = $(xdc_PATH)
export XDCROOT
export XDCTOOLS

TMS470CGTOOLPATH = $(CODEGEN_PATH_M3)
export TMS470CGTOOLPATH

CODESOURCERYCGTOOLS = $(CODEGEN_PATH_A8)
export CODESOURCERYCGTOOLS

PATH += $(PATH_SEPARATOR)$(xdc_PATH)$(PATH_SEPARATOR)$(CODEGEN_PATH_M3)/bin
export PATH

# Nothing beyond this point
