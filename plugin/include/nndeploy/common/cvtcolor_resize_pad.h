
#ifndef _NNDEPLOY_MODEL_PREPROCESS_CVTCOLOR_RESIZE_PAD_H_
#define _NNDEPLOY_MODEL_PREPROCESS_CVTCOLOR_RESIZE_PAD_H_

#include "nndeploy/base/common.h"
#include "nndeploy/base/glic_stl_include.h"
#include "nndeploy/base/log.h"
#include "nndeploy/base/macro.h"
#include "nndeploy/base/object.h"
#include "nndeploy/base/opencv_include.h"
#include "nndeploy/base/status.h"
#include "nndeploy/base/string.h"
#include "nndeploy/base/value.h"
#include "nndeploy/dag/edge.h"
#include "nndeploy/dag/node.h"
#include "nndeploy/device/buffer.h"
#include "nndeploy/device/device.h"
#include "nndeploy/device/memory_pool.h"
#include "nndeploy/device/tensor.h"
#include "nndeploy/model/preprocess/opencv_convert.h"
#include "nndeploy/model/preprocess/params.h"


namespace nndeploy {
namespace model {

class NNDEPLOY_CC_API CvtColorResizePad : public dag::Node {
 public:
  CvtColorResizePad(const std::string &name, dag::Edge *input,
                    dag::Edge *output)
      : Node(name, input, output) {
    param_ = std::make_shared<CvtclorResizePadParam>();
  }
  virtual ~CvtColorResizePad() {}

  virtual base::Status run();
};

}  // namespace model
}  // namespace nndeploy

#endif /* _NNDEPLOY_MODEL_PREPROCESS_CVTCOLOR_RESIZE_PAD_H_ */
