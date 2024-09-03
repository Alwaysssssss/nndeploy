
file(GLOB MODEL_SOURCE
  "${ROOT_PATH}/include/nndeploy/model/*.h"
  "${ROOT_PATH}/source/nndeploy/model/*.cc"
)

if(ENABLE_NNDEPLOY_OPENCV)
  file(GLOB_RECURSE MODEL_PREPROCESS_SOURCE
    "${ROOT_PATH}/include/nndeploy/model/preprocess/*.h"
    "${ROOT_PATH}/source/nndeploy/model/preprocess/*.cc"
  )
  set(MODEL_SOURCE ${MODEL_SOURCE} ${MODEL_PREPROCESS_SOURCE})
endif()

nndeploy_option(ENABLE_NNDEPLOY_MODEL_DETECT "ENABLE_NNDEPLOY_MODEL_DETECT" OFF)
nndeploy_option(ENABLE_NNDEPLOY_MODEL_DETECT_YOLOV3 "ENABLE_NNDEPLOY_MODEL_DETECT_YOLOV3" OFF)
nndeploy_option(ENABLE_NNDEPLOY_MODEL_DETECT_DETR "ENABLE_NNDEPLOY_MODEL_DETECT_DETR" OFF)
nndeploy_option(ENABLE_NNDEPLOY_MODEL_DETECT_YOLO "ENABLE_NNDEPLOY_MODEL_DETECT_YOLO" OFF)
if (ENABLE_NNDEPLOY_MODEL_DETECT)
  include(${ROOT_PATH}/source/nndeploy/model/detect/config.cmake)
endif()

nndeploy_option(ENABLE_NNDEPLOY_MODEL_SEGMENT "ENABLE_NNDEPLOY_MODEL_SEGMENT" OFF)
nndeploy_option(ENABLE_NNDEPLOY_MODEL_SEGMENT_SEGMENT_ANYTHING "ENABLE_NNDEPLOY_MODEL_SEGMENT_SEGMENT_ANYTHING" OFF)
if (ENABLE_NNDEPLOY_MODEL_SEGMENT)
  include(${ROOT_PATH}/source/nndeploy/model/segment/config.cmake)
endif()

if (ENABLE_NNDEPLOY_MODEL_TOKENIZER)
  include(${ROOT_PATH}/source/nndeploy/model/tokenizer/config.cmake)
endif()

nndeploy_option(ENABLE_NNDEPLOY_MODEL_STABLE_DIFFUSION "ENABLE_NNDEPLOY_MODEL_STABLE_DIFFUSION" OFF)
if (ENABLE_NNDEPLOY_MODEL_STABLE_DIFFUSION)
  include(${ROOT_PATH}/source/nndeploy/model/stable_diffusion/config.cmake)
endif()