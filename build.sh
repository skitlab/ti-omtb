. $1

make \
 ROOTDIR=$THIRD_PARTY_DIR/omtb \
 DEST_ROOT=$THIRD_PARTY_DIR/omtb \
 EXEC_DIR=$THIRD_PARTY_DIR/devkit/usr/libexec \
 OMX_INSTALL_DIR=$THIRD_PARTY_DIR/omx \
 osal_PATH=$THIRD_PARTY_DIR/osal \
 ipc_PATH=$THIRD_PARTY_DIR/ipc \
 syslink_PATH=$THIRD_PARTY_DIR/syslink \
 xdc_PATH=$THIRD_PARTY_DIR/xdctools \
 lindevkit_PATH=$THIRD_PARTY_DIR/devkit/usr \
 CODEGEN_PATH_A8=$CROSSCOMPILER_DIR/../ \
 uia_PATH=$THIRD_PARTY_DIR/uia \
 fc_PATH=$THIRD_PARTY_DIR/framework_components \
 linuxutils_PATH=$THIRD_PARTY_DIR/linuxutils \
 PLATFORM=ti816x-evm \
dm81xxbm install_dm81xxbm
