# File: component.mk
#       This file is component include make file of OMX.

# List of variables set in this file and their purpose:
# <mod>_RELPATH        - This is the relative path of the module, typically from
#                        top-level directory of the package
# <mod>_PATH           - This is the absolute path of the module. It derives from
#                        absolute path of the top-level directory (set in env.mk)
#                        and relative path set above
# <mod>_INCLUDE        - This is the path that has interface header files of the
#                        module. This can be multiple directories (space separated)
# <mod>_PKG_LIST       - Names of the modules (and sub-modules) that are a part
#                        part of this module, including itself.
# <mod>_PLATFORM_DEPENDENCY - "yes": means the code for this module depends on 
#                             platform and the compiled obj/lib has to be kept
#                             under <platform> directory
#                             "no" or "" or if this variable is not defined: means
#                             this module has no platform dependent code and hence
#                             the obj/libs are not kept under <platform> dir.
# <mod>_CORE_DEPENDENCY     - "yes": means the code for this module depends on 
#                             core and the compiled obj/lib has to be kept
#                             under <core> directory
#                             "no" or "" or if this variable is not defined: means
#                             this module has no core dependent code and hence
#                             the obj/libs are not kept under <core> dir.
# <mod>_APP_STAGE_FILES     - List of source files that belongs to the module
#                             <mod>, but that needs to be compiled at application
#                             build stage (in the context of the app). This is
#                             primarily for link time configurations or if the
#                             source file is dependent on options/defines that are
#                             application dependent. This can be left blank or
#                             not defined at all, in which case, it means there
#                             no source files in the module <mod> that are required
#                             to be compiled in the application build stage.
#

# List of modules under OMX
omx_COMP_LIST_common = 
omx_COMP_LIST_m3vpss = 
omx_COMP_LIST_m3video =
omx_COMP_LIST_a8host = 

EXT_COMP_LIST_common = 
EXT_COMP_LIST_m3vpss = 
EXT_COMP_LIST_m3video = 
EXT_COMP_LIST_a8host = 

# List of platforms supported by OMTB
omx_OMTB_LIST = dm816x dm81xxbm

#
# OMX Modules
#

# OMX Standard version 1.1: openMaxv11 
openmaxv11_PATH = $(omx_PATH)/ti/omx/interfaces/openMaxv11
openmaxv11_INCLUDE = $(openmaxv11_PATH)

# VFDC - Video Frame Display Component
vfdc_RELPATH = ti/omx/comp/vfdc
vfdc_PATH = $(omx_PATH)/$(vfdc_RELPATH)
vfdc_INCLUDE = $(vfdc_PATH) $(vfdc_PATH)/src
vfdc_PKG_LIST = vfdc
vfdc_PLATFORM_DEPENDENCY = yes

# VFCC - Video Frame Capture Component
vfcc_RELPATH = ti/omx/comp/vfcc
vfcc_PATH = $(omx_PATH)/$(vfcc_RELPATH)
vfcc_INCLUDE = $(vfcc_PATH) $(vfcc_PATH)/src
vfcc_PLATFORM_DEPENDENCY = yes
vfcc_APP_STAGE_FILES = vfcc_cfg.c
vfcc_PKG_LIST = vfcc

# VFPC - Video Frame Processing Component
vfpc_RELPATH = ti/omx/comp/vfpc
vfpc_PATH = $(omx_PATH)/$(vfpc_RELPATH)
vfpc_INCLUDE = $(vfpc_PATH) $(vfpc_PATH)/src
vfpc_PKG_LIST = vfpc
vfpc_PLATFORM_DEPENDENCY = yes

# VSRC - Video dummy Source Component
vsrc_RELPATH = ti/omx/comp/vsrc
vsrc_PATH = $(omx_PATH)/$(vsrc_RELPATH)
vsrc_INCLUDE = $(vsrc_PATH) $(vsrc_PATH)/src
vsrc_PKG_LIST = vsrc
vsrc_PLATFORM_DEPENDENCY = yes

# VSNK - Video dummy Sync Component
vsnk_RELPATH = ti/omx/comp/vsnk
vsnk_PATH = $(omx_PATH)/$(vsnk_RELPATH)
vsnk_INCLUDE = $(vsnk_PATH) $(vsnk_PATH)/src
vsnk_PLATFORM_DEPENDENCY = yes
vsnk_APP_STAGE_FILES = vsnk_cfg.c
vsnk_PKG_LIST = vsnk

# VENC - Video Encode component
venc_RELPATH = ti/omx/comp/venc
venc_PATH = $(omx_PATH)/$(venc_RELPATH)
venc_INCLUDE = $(venc_PATH) $(venc_PATH)/src
venc_PKG_LIST = venc
venc_PLATFORM_DEPENDENCY = yes

# VDEC - Video Decode component
vdec_RELPATH = ti/omx/comp/vdec
vdec_PATH = $(omx_PATH)/$(vdec_RELPATH)
vdec_INCLUDE = $(vdec_PATH) $(vdec_PATH)/src
vdec_PKG_LIST = vdec
vdec_PLATFORM_DEPENDENCY = yes

# SCHEDULER - IVA-HD Scheduler
scheduler_RELPATH = ti/omx/comp/scheduler
scheduler_PATH = $(omx_PATH)/$(scheduler_RELPATH)
scheduler_INCLUDE = $(scheduler_PATH)
scheduler_PKG_LIST = scheduler
scheduler_PLATFORM_DEPENDENCY = yes

# SERVER - IVA-HD Server
server_RELPATH = ti/omx/comp/server
server_PATH = $(omx_PATH)/$(server_RELPATH)
server_INCLUDE = $(server_PATH)
server_PKG_LIST = server
server_PLATFORM_DEPENDENCY = yes

# CTRL - OMX Control module
ctrl_RELPATH = ti/omx/comp/ctrl
ctrl_PATH = $(omx_PATH)/$(ctrl_RELPATH)
ctrl_INCLUDE = $(ctrl_PATH)
ctrl_PKG_LIST = ctrl
ctrl_PLATFORM_DEPENDENCY = yes

# OMXBASE - OMX Base component
omxbase_RELPATH = ti/omx/comp/omxbase
omxbase_PATH = $(omx_PATH)/$(omxbase_RELPATH)
omxbase_INCLUDE = $(omxbase_PATH) $(omxbase_PATH)/omx_base_comp/inc
omxbase_PLATFORM_DEPENDENCY = no
omxbase_CORE_DEPENDENCY = yes
omxbase_APP_STAGE_FILES = omxbase_cfg.c
omxbase_PKG_LIST = omxbase

# OMX CORE
omxcore_RELPATH = ti/omx/omxcore
omxcore_PATH = $(omx_PATH)/$(omxcore_RELPATH)
omxcore_INCLUDE = $(omxcore_PATH)
omxcore_CORE_DEPENDENCY = yes
omxcore_APP_STAGE_FILES = omxcore_cfg.c
omxcore_PKG_LIST = omxcore

# MEMCFG
memcfg_RELPATH = ti/omx/memcfg
memcfg_PATH = $(omx_PATH)/$(memcfg_RELPATH)
memcfg_INCLUDE = $(memcfg_PATH)
memcfg_CORE_DEPENDENCY = yes
memcfg_APP_STAGE_FILES = memtbl_cfg.c
memcfg_PKG_LIST = memcfg

# OMX Utils
omxutils_RELPATH = ti/omx/omxutils
omxutils_PATH = $(omx_PATH)/$(omxutils_RELPATH)
omxutils_INCLUDE = $(omxutils_PATH) $(omxutils_PATH)/src
omxutils_CORE_DEPENDENCY = yes
omxutils_PKG_LIST = omxutils

# DOMX - Distributed OMX
domx_RELPATH = ti/omx/domx
domx_PATH = $(omx_PATH)/$(domx_RELPATH)
domx_INCLUDE = $(domx_PATH) 
domx_CORE_DEPENDENCY = yes
domx_APP_STAGE_FILES = domx_cfg.c 
domx_PKG_LIST = domx domx_delegates_shmem

domx_delegates_shmem_RELPATH = $(domx_RELPATH)/delegates/shmem
domx_delegates_shmem_PATH = $(omx_PATH)/$(domx_delegates_shmem_RELPATH)
domx_delegates_shmem_INCLUDE = $(domx_delegates_shmem_PATH)
domx_delegates_shmem_CORE_DEPENDENCY = yes
domx_delegates_shmem_APP_STAGE_FILES = domx_delegates_shmem_cfg.c

domx_interfaces_RELPATH = $(domx_RELPATH)/interfaces
domx_interfaces_PATH = $(omx_PATH)/$(domx_interfaces_RELPATH)
domx_interfaces_INCLUDE = $(domx_interfaces_PATH)
domx_interfaces_CORE_DEPENDENCY = yes

# CMUX - Mux
cmux_RELPATH = ti/omx/comp/cmux
cmux_PATH = $(omx_PATH)/$(cmux_RELPATH)
cmux_INCLUDE = $(cmux_PATH) $(cmux_PATH)/src
cmux_PKG_LIST = cmux

# DMUX - De-mux
dmux_RELPATH = ti/omx/comp/dmux
dmux_PATH = $(omx_PATH)/$(dmux_RELPATH)
dmux_INCLUDE = $(dmux_PATH) $(dmux_PATH)/src
dmux_PKG_LIST = dmux

# VLPB - Video Loopback Component
vlpb_RELPATH = ti/omx/comp/vlpb
vlpb_PATH = $(omx_PATH)/$(vlpb_RELPATH)
vlpb_INCLUDE = $(vlpb_PATH) $(vlpb_PATH)/src
vlpb_PKG_LIST = vlpb
# TIMMOSAL - TIMM Osal module
timmosal_RELPATH = ti/timmosal
timmosal_PATH = $(omx_PATH)/$(timmosal_RELPATH)
timmosal_INCLUDE = $(timmosal_PATH)
timmosal_CORE_DEPENDENCY = yes
timmosal_PKG_LIST = timmosal

# RTPTX 
rtptx_RELPATH = ti/omx/comp/rtptx
rtptx_PATH = $(omx_PATH)/$(rtptx_RELPATH)
rtptx_INCLUDE = $(rtptx_PATH) $(rtptx_PATH)/src
rtptx_PKG_LIST = rtptx

# RTPRX
rtprx_RELPATH = ti/omx/comp/rtprx
rtprx_PATH = $(omx_PATH)/$(rtprx_RELPATH)
rtprx_INCLUDE = $(rtprx_PATH) $(rtprx_PATH)/src
rtprx_PKG_LIST = rtprx

# OMX top level
omx_INCLUDE = $(omx_PATH) $(openmaxv11_INCLUDE) $(omxbase_INCLUDE) \
              $(omxcore_INCLUDE) $(memcfg_INCLUDE) $(omxutils_INCLUDE) $(vfdc_INCLUDE) \
              $(vfpc_INCLUDE) $(vfcc_INCLUDE) $(vsrc_INCLUDE) $(vsnk_INCLUDE) \
              $(venc_INCLUDE) $(vdec_INCLUDE) $(scheduler_INCLUDE) \
              $(ctrl_INCLUDE) $(domx_INCLUDE) $(vlpb_INCLUDE) $(server_INCLUDE) \
              $(cmux_INCLUDE) $(dmux_INCLUDE) $(rtptx_INCLUDE) $(rtprx_INCLUDE)

#
# OMTB Paths
#

# dm816x
dm816x_OMTB_RELPATH = packages/ti/sdo/omtb/dm816x
dm816x_OMTB_PATH = $(OMTB_ROOT)/$(dm816x_OMTB_RELPATH)
export dm816x_OMTB_PATH

dm816x_OMTB_RELPATH_A8 = packages/ti/sdo/omtb/dm816x/cortexA8
dm816x_OMTB_A8_PATH = $(OMTB_ROOT)/$(dm816x_OMTB_RELPATH_A8)
export dm816x_OMTB_A8_PATH

dm816x_OMTB_RELPATH_VIDEOM3 = packages/ti/sdo/omtb/dm816x/videoM3
dm816x_OMTB_VIDEOM3_PATH = $(OMTB_ROOT)/$(dm816x_OMTB_RELPATH_VIDEOM3)
export dm816x_OMTB_VIDEOM3_PATH

dm816x_OMTB_RELPATH_DSSM3 = packages/ti/sdo/omtb/dm816x/dssM3
dm816x_OMTB_DSSM3_PATH = $(OMTB_ROOT)/$(dm816x_OMTB_RELPATH_DSSM3)
export dm816x_OMTB_DSSM3_PATH

# dm81xxbm
dm81xxbm_OMTB_RELPATH = packages/ti/sdo/omtb/dm81xxbm
dm81xxbm_OMTB_PATH = $(OMTB_ROOT)/$(dm81xxbm_OMTB_RELPATH)
export dm816xbm_OMTB_PATH

dm81xxbm_OMTB_RELPATH_A8 = packages/ti/sdo/omtb/dm81xxbm/cortexA8
dm81xxbm_OMTB_A8_PATH = $(OMTB_ROOT)/$(dm81xxbm_OMTB_RELPATH_A8)
export dm81xxbm_OMTB_A8_PATH

export APP_NAME
export CODECS_IN_APP
-include $($(APP_NAME)_OMTB_PATH)/app_properties.mk

# Component specific CFLAGS
CFLAGS_COMP_COMMON += 

# CFLAGS based on example/demo/application properties
ifeq ($(MAX_RESOLUTION),sd)
  CFLAGS_COMP_COMMON += -DMAX_RESOLUTION_SD
endif
ifeq ($(MAX_RESOLUTION),hd)
  CFLAGS_COMP_COMMON += -DMAX_RESOLUTION_HD
endif
ifeq ($(IPC_MODE),remote)
  CFLAGS_COMP_COMMON += -DDOMX_CORE_REMOTEDUCATI
endif
ifeq ($(IPC_MODE),remoteWithHOST)
  CFLAGS_COMP_COMMON += -DDOMX_CORE_REMOTEDUCATIHOST
endif

ifeq ($(APP_TYPE),vs)
  CFLAGS_COMP_COMMON += -DVS_APPS
endif

ifeq ($(VSRCVSNKIO_TYPE),file_based)
  CFLAGS_COMP_COMMON += -DFILE_BASED
endif

ifeq ($(PLATFORM_TYPE),simulator)
  CFLAGS_COMP_COMMON += -DPLATFORM_SIM
endif

# CFLAGS based on codecs selected
ifeq ($(findstring h264enc, $(CODECS_IN_APP)),h264enc)
  CFLAGS_COMP_COMMON += -DCODEC_H264ENC
endif
ifeq ($(findstring mpeg2enc, $(CODECS_IN_APP)),mpeg2enc)
  CFLAGS_COMP_COMMON += -DCODEC_MPEG2ENC
endif
ifeq ($(findstring h264dec, $(CODECS_IN_APP)),h264dec)
  CFLAGS_COMP_COMMON += -DCODEC_H264DEC
endif
ifeq ($(findstring mpeg2dec, $(CODECS_IN_APP)),mpeg2dec)
  CFLAGS_COMP_COMMON += -DCODEC_MPEG2DEC
endif

ifeq ($(TUNNEL_MODE),snt)
  CFLAGS_COMP_COMMON += -DOMTB_SNT
endif

# Nothing beyond this point
