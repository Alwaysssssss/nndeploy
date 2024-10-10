
#ifndef _NNDEPLOY_OP_OP_SPLIT_H_
#define _NNDEPLOY_OP_OP_SPLIT_H_

#include "nndeploy/ir/ir.h"
#include "nndeploy/op/op.h"

namespace nndeploy {
namespace op {

class OpSplit : public Op {
 public:
  OpSplit() : Op() {}
  virtual ~OpSplit() {}

  virtual base::Status inferShape();
};

}  // namespace op
}  // namespace nndeploy

#endif
