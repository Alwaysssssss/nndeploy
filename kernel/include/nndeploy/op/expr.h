
#ifndef _NNDEPLOY_OP_EXPR_H_
#define _NNDEPLOY_OP_EXPR_H_

#include "nndeploy/base/macro.h"
#include "nndeploy/device/tensor.h"
#include "nndeploy/op/ir.h"

namespace nndeploy {
namespace op {

// 标识Expr的类型
enum ExprType : int {
  // TODO：需要细分为输入、输出、权重吗？似乎现在这样更加简单且直观，但是只有这个信息能区分输入与权重吗？（应该可以？）
  kExprTypeValueDesc = 0x0000,
  kExprTypeOpDesc,
  kExprTypeModelDesc,
};

class NNDEPLOY_CC_API Expr {
 public:
  Expr(const std::string &name);
  Expr(const std::string &name, base::DataType data_type);
  Expr(const std::string &name, base::DataType data_type,
       base::IntVector shape);
  Expr(std::shared_ptr<ValueDesc> value_desc);
  Expr(std::shared_ptr<OpDesc> op_desc);
  Expr(std::shared_ptr<ModelDesc> model_desc);

  std::vector<std::string> getOutputName();

 protected:
  ExprType expr_type_;
  std::shared_ptr<ValueDesc> value_desc_;
  std::shared_ptr<OpDesc> op_desc_;
  std::shared_ptr<ModelDesc> model_desc_;
};

/**
 * @brief  一系列创建函数
 */
// input
NNDEPLOY_CC_API std::shared_ptr<Expr> makeInput(
    ModelDesc *model_desc, std::string name,
    base::DataType data_type = base::dataTypeOf<float>(),
    base::IntVector shape = base::IntVector());
// output
NNDEPLOY_CC_API void makeOutput(ModelDesc *model_desc,
                                std::shared_ptr<Expr> expr);
// block
NNDEPLOY_CC_API std::shared_ptr<Expr> makeBlock(
    ModelDesc *model_desc, std::shared_ptr<ModelDesc> model_block);
// conv2d
NNDEPLOY_CC_API std::shared_ptr<Expr> makeConv(ModelDesc *model_desc,
                               std::shared_ptr<Expr> input,
                               std::shared_ptr<ConvParam> param,
                               const std::string &weight = "",
                               const std::string &bias = "",
                               std::string op_name = "",
                               std::string output_name = "");
// relu
NNDEPLOY_CC_API std::shared_ptr<Expr> makeRelu(ModelDesc *model_desc,
                               std::shared_ptr<Expr> input,
                               std::string op_name = "",
                               std::string output_name = "");

// relu
NNDEPLOY_CC_API std::shared_ptr<Expr> makeSoftMax(ModelDesc *model_desc,
                                  std::shared_ptr<Expr> input,
                                  std::shared_ptr<SoftmaxParam> param,
                                  std::string op_name = "",
                                  std::string output_name = "");

// TODO: @Leonisux:
// 补充llama的算子的手动构图函数

}  // namespace op
}  // namespace nndeploy

#endif