# 注：依赖opencv

include_directories(${ROOT_PATH}/plugin/include)
include_directories(${ROOT_PATH}/plugin/source)

# make
set(NNDEPLOY_PLUGIN_DIRECTORY nndeploy_plugin)
set(NNDEPLOY_PLUGIN_LIST)

# plugin path
set(PLUGIN_ROOT_PATH ${ROOT_PATH}/plugin)

# plugin
# # basic
nndeploy_option(ENABLE_NNDEPLOY_PLUGIN_PREPROCESS "ENABLE_NNDEPLOY_PLUGIN_PREPROCESS" ON)

if(ENABLE_NNDEPLOY_PLUGIN_PREPROCESS)
  include(${PLUGIN_ROOT_PATH}/source/nndeploy/preprocess/config.cmake)
endif()

# # infer
nndeploy_option(ENABLE_NNDEPLOY_PLUGIN_INFER "ENABLE_NNDEPLOY_PLUGIN_INFER" ON)

if(ENABLE_NNDEPLOY_PLUGIN_INFER)
  include(${PLUGIN_ROOT_PATH}/source/nndeploy/infer/config.cmake)
endif()

# # codec
nndeploy_option(ENABLE_NNDEPLOY_PLUGIN_CODEC "ENABLE_NNDEPLOY_PLUGIN_CODEC" ON)

if(ENABLE_NNDEPLOY_PLUGIN_CODEC)
  include(${PLUGIN_ROOT_PATH}/source/nndeploy/codec/config.cmake)
endif()

# # detect
nndeploy_option(ENABLE_NNDEPLOY_PLUGIN_DETECT "ENABLE_NNDEPLOY_PLUGIN_DETECT" OFF)
nndeploy_option(ENABLE_NNDEPLOY_PLUGIN_DETECT_DETR "ENABLE_NNDEPLOY_PLUGIN_DETECT_DETR" OFF)
nndeploy_option(ENABLE_NNDEPLOY_PLUGIN_DETECT_YOLO "ENABLE_NNDEPLOY_PLUGIN_DETECT_YOLO" OFF)

if(ENABLE_NNDEPLOY_PLUGIN_DETECT)
  include(${PLUGIN_ROOT_PATH}/source/nndeploy/detect/config.cmake)
endif()

# # segment
nndeploy_option(ENABLE_NNDEPLOY_PLUGIN_SEGMENT "ENABLE_NNDEPLOY_PLUGIN_SEGMENT" OFF)
nndeploy_option(ENABLE_NNDEPLOY_PLUGIN_SEGMENT_SEGMENT_ANYTHING "ENABLE_NNDEPLOY_PLUGIN_SEGMENT_SEGMENT_ANYTHING" OFF)

if(ENABLE_NNDEPLOY_PLUGIN_SEGMENT)
  include(${PLUGIN_ROOT_PATH}/source/nndeploy/segment/config.cmake)
endif()

# # tokenizer
nndeploy_option(ENABLE_NNDEPLOY_PLUGIN_TOKENIZER "ENABLE_NNDEPLOY_PLUGIN_TOKENIZER" OFF)

if(ENABLE_NNDEPLOY_PLUGIN_TOKENIZER)
  include(${PLUGIN_ROOT_PATH}/source/nndeploy/tokenizer/config.cmake)
endif()

# # stable_diffusion
nndeploy_option(ENABLE_NNDEPLOY_PLUGIN_STABLE_DIFFUSION "ENABLE_NNDEPLOY_PLUGIN_STABLE_DIFFUSION" OFF)

if(ENABLE_NNDEPLOY_PLUGIN_STABLE_DIFFUSION)
  include(${PLUGIN_ROOT_PATH}/source/nndeploy/stable_diffusion/config.cmake)
endif()

# appedn list
message(STATUS "NNDEPLOY_PLUGIN_LIST: ${NNDEPLOY_PLUGIN_LIST}")