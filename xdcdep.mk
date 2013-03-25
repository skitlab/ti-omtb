# This make include file defines env variables required to build XDC
XDCBUILDCFG = $(CONFIG_BLD_XDC_$(ISA))
XDCARGS = core=vpss_m3 profile=$(PROFILE_$(CORE))
XDCOPTIONS = v
OMXMAXRESOLUTION = $(MAX_RESOLUTION)
export OMXMAXRESOLUTION
export XDCBUILDCFG
export XDCARGS
export XDCOPTIONS

ifeq ($(IPC_MODE),remote)
  OMXIPCMODE = OMXIPC_INTERDUCATI
endif
ifeq ($(IPC_MODE),remoteWithHOST)
  OMXIPCMODE = OMXIPC_ALLCORES
endif
export OMXIPCMODE

# Nothing beyond this point

