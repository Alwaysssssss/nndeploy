
#ifndef _NNDEPLOY_MODEL_CONVERT_TO_H_
#define _NNDEPLOY_MODEL_CONVERT_TO_H_

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
#include "nndeploy/device/tensor.h"

namespace nndeploy {
namespace model {

class NNDEPLOY_CC_API ConvertToParam : public base::Param {
 public:
  base::DataType dst_data_type_ = base::dataTypeOf<float>();
};

class NNDEPLOY_CC_API ConvertTo : public dag::Node {
 public:
  ConvertTo(const std::string &name, dag::Edge *input, dag::Edge *output)
      : Node(name, input, output) {
    param_ = std::make_shared<ConvertToParam>();
  }
  virtual ~ConvertTo() {}

  virtual base::Status run();
};

}  // namespace model
}  // namespace nndeploy

#endif /* _NNDEPLOY_MODEL_CONVERT_TO_H_ */
