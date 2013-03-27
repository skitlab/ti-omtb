#
# OMTB
#
ifeq ($(ROOTDIR),)
  $(error Error: Environment variable ROOTDIR not set)
endif

# Begin block - Build options
#  By the end of this block, we'd have either xdc or make or both in BUILD_OPTIONS
#  using which, we'd build either XDC packages (+run configuro) 
#  or make based components (+link) or both.
BUILD_OPTIONS = xdc make
VALID_BUILD_OPTIONS = full $(BUILD_OPTIONS)
ifeq ($(filter $(BUILD),$(VALID_BUILD_OPTIONS)),)
 ifeq ($(BUILD),)
  BUILD = full
 else
  $(error Error: Invalid value specified for BUILD. Valid values are - $(VALID_BUILD_OPTIONS))
 endif
endif
ifneq ($(BUILD),full)
 BUILD_OPTIONS = $(BUILD)
endif
# End block - Build options

include $(ROOTDIR)/makerules/build_config.mk
include $(ROOTDIR)/makerules/env.mk
include component.mk

omx_COMP_LIST_ALL = $(omx_COMP_LIST_m3video) $(omx_COMP_LIST_m3vpss) $(omx_COMP_LIST_a8host) $(omx_COMP_LIST_common) $(EXT_COMP_LIST_common) $(EXT_COMP_LIST_m3video) $(EXT_COMP_LIST_m3vpss) $(EXT_COMP_LIST_a8host)
omx_PKG_LIST_ALL = $(foreach PKG,$(omx_COMP_LIST_ALL),$($(PKG)_PKG_LIST))
omx_PKG_LIST_common = $(foreach PKG,$(omx_COMP_LIST_common),$($(PKG)_PKG_LIST))
omx_PKG_LIST_m3video = $(foreach PKG,$(omx_COMP_LIST_m3video),$($(PKG)_PKG_LIST))
ALL_COMP_LIST_m3vpss = $(omx_COMP_LIST_m3vpss) $(EXT_COMP_LIST_m3vpss)
omx_PKG_LIST_m3vpss = $(foreach PKG,$(ALL_COMP_LIST_m3vpss),$($(PKG)_PKG_LIST))
omx_PKG_LIST_a8host = $(foreach PKG,$(omx_COMP_LIST_a8host),$($(PKG)_PKG_LIST))
CLEANALL_TARGETS = $(addsuffix _clean, $(omx_PKG_LIST_ALL))
CLEANALL_m3video = $(addsuffix _clean, $(omx_PKG_LIST_m3video))
CLEANALL_m3vpss = $(addsuffix _clean, $(omx_PKG_LIST_m3vpss))
CLEANALL_a8host = $(addsuffix _clean, $(omx_PKG_LIST_a8host))
CLEANALL_common = $(addsuffix _clean, $(omx_PKG_LIST_common))
CLEANALL_OMTB = $(addsuffix _clean, $(omx_OMTB_LIST))

.PHONY : $(omx_PKG_LIST_ALL) $(omx_OMTB_LIST)

libs: $(omx_PKG_LIST_ALL)

all: libs omtb

omtb: $(omx_OMTB_LIST)

clean: $(CLEANALL_TARGETS)

cleanall: $(CLEANALL_TARGETS) $(CLEANALL_OMTB)

#
# Rule to build all modules and omtb
#

$(omx_PKG_LIST_common) :
	$(ECHO) \# Making $(PLATFORM):m3video:$(PROFILE_m3video):$@...
	$(MAKE) -C $($@_PATH) CORE=m3video
	$(ECHO) \# Making $(PLATFORM):m3vpss:$(PROFILE_m3vpss):$@...
	$(MAKE) -C $($@_PATH) CORE=m3vpss
	$(ECHO) \# Making $(PLATFORM):a8host:$(PROFILE_a8host):$@...
	$(MAKE) -C $($@_PATH) CORE=a8host

$(omx_PKG_LIST_m3video) :
	$(ECHO) \# Making $(PLATFORM):m3video:$(PROFILE_m3video):$@...
	$(MAKE) -C $($@_PATH) CORE=m3video

$(omx_PKG_LIST_m3vpss) :
	$(ECHO) \# Making $(PLATFORM):m3vpss:$(PROFILE_m3vpss):$@...
	$(MAKE) -C $($@_PATH) CORE=m3vpss

$(omx_PKG_LIST_a8host) :
	$(ECHO) \# Making $(PLATFORM):a8host:$(PROFILE_a8host):$@...
	$(MAKE) -C $($@_PATH) CORE=a8host

# Netra: DM816x
dm816x: dm816xducati dm816xhost

dm816xxdcAll: dm816xducatiXdc

dm816xducatiXdc:
ifeq ($(findstring xdc,$(BUILD_OPTIONS)),xdc)
	$(ECHO) \# Making XDC dependent packages for $(subst ducatiXdc,,$@):M3
	$(MAKE) -f xdcdepmakefile _APP=$(subst ducatiXdc,,$@) CORE=m3video
	$(ECHO) \# Configuring XDC packages for $(subst ducatiXdc,,$@):m3video
	$(MAKE) -C $($(subst ducatiXdc,,$@)_OMTB_VIDEOM3_PATH) xdc_configuro CORE=m3video
	$(ECHO) \# Configuring XDC packages for $(subst ducatiXdc,,$@):m3vpss
	$(MAKE) -C $($(subst ducatiXdc,,$@)_OMTB_DSSM3_PATH) xdc_configuro CORE=m3vpss
endif

dm816xducati: dm816xvm3 dm816xdm3
dm816xvm3: dm816xducatiXdc
ifeq ($(findstring make,$(BUILD_OPTIONS)),make)
	$(ECHO) \# Building $(subst vm3,,$@) executable for core: m3video
	$(MAKE) -C $($(subst vm3,,$@)_OMTB_VIDEOM3_PATH) CORE=m3video
endif
	
dm816xdm3: dm816xducatiXdc
ifeq ($(findstring make,$(BUILD_OPTIONS)),make)
	$(ECHO) \# Building $(subst dm3,,$@) executable for core: m3vpss
	$(MAKE) -C $($(subst dm3,,$@)_OMTB_DSSM3_PATH) CORE=m3vpss
endif

dm816xhost:
ifeq ($(findstring make,$(BUILD_OPTIONS)),make)
	$(ECHO) \# Building $(subst host,,$@) executable for core: a8host
	$(MAKE) -C $($(subst host,,$@)_OMTB_A8_PATH) CORE=a8host
endif	

# DM816xBM and DM814xBM
dm81xxbm:
ifeq ($(findstring make,$(BUILD_OPTIONS)),make)
	$(ECHO) \# Building $(subst host,,$@) executable for core: a8host
	$(MAKE) -C $($(subst host,,$@)_OMTB_A8_PATH) CORE=a8host
endif

# Clean targets	
$(CLEANALL_common) : 
	$(ECHO) \# Cleaning $(subst _clean,,$@)...
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=m3video
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=m3vpss
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=a8host

$(CLEANALL_m3video) : 
	$(ECHO) \# Cleaning $(subst _clean,,$@)...
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=m3video

$(CLEANALL_m3vpss) : 
	$(ECHO) \# Cleaning $(subst _clean,,$@)...
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=m3vpss

$(CLEANALL_a8host) : 
	$(ECHO) \# Cleaning $(subst _clean,,$@)...
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=a8host

$(CLEANALL_OMTB) : 
	$(ECHO) \# Cleaning $(subst _clean,,$@)...
ifeq ($(findstring xdc,$(BUILD_OPTIONS)),xdc)
	$(MAKE) -f xdcdepmakefile xdcdepclean _APP=$(subst _clean,,$@) CORE=m3video
endif
	$(MAKE) -C $($(subst _clean,,$@)_OMTB_VIDEOM3_PATH) clean CORE=m3video
	$(MAKE) -C $($(subst _clean,,$@)_OMTB_DSSM3_PATH) clean CORE=m3vpss
	$(MAKE) -C $($(subst _clean,,$@)_OMTB_A8_PATH) clean CORE=a8host

clean_dm81xxbm:
	$(ECHO) \# Cleaning $(subst _clean,,$@)...
	#$(MAKE) -C $($(subst clean_,,$@)_OMTB_A8_PATH) clean CORE=a8host
	$(RM) -rf $(DEST_ROOT)

install_dm81xxbm:
	$(ECHO) \# Installing OMTB for $(subst install_,,$@)... 
	install -d $(EXEC_DIR)
	cp $(ROOTDIR)/bin/dm81xxbm/bin/ti816x-evm/omtb_dm81xxbm_a8host.xv5T  $(EXEC_DIR)/omtb_dm81xxbm_a8host.xv5T
	install -d $(EXEC_DIR)/omtb_scripts
	cp $(ROOTDIR)/packages/ti/sdo/omtb/scripts/*.oms $(EXEC_DIR)/omtb_scripts

# Nothing beyond this point
