# Defines properties of the example/demo/application

# Application Type
#     vs: video surveillance
APP_TYPE = vc

# Max resolution supported in this app
MAX_RESOLUTION = hd

# IPC Modes: 
#     local: only this core 
#     remote: only intra-ducati (between two M3 cores)
#     remoteWithHOST: ducati cores and host (A8)
IPC_MODE = remoteWithHOST

# Codecs required for this demo:
#     Eg: h264enc mpeg2enc...
CODECS_IN_APP = h264enc h264dec

# Tunneling mode used by the omx components
#     snt: standard non tunneling
TUNNEL_MODE = snt

# Nothing beyond this point
