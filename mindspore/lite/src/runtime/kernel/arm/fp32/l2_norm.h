/**
 * Copyright 2020 Huawei Technologies Co., Ltd
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef MINDSPORE_LITE_SRC_RUNTIME_KERNEL_ARM_FP32_RESHAPE_H_
#define MINDSPORE_LITE_SRC_RUNTIME_KERNEL_ARM_FP32_RESHAPE_H_

#include <vector>
#include "include/context.h"
#include "src/lite_kernel.h"
#include "nnacl/l2_norm_parameter.h"
#include "schema/model_generated.h"
#include "src/kernel_registry.h"

using mindspore::lite::InnerContext;

namespace mindspore::kernel {
class L2NormCPUKernel : public LiteKernel {
 public:
  L2NormCPUKernel(OpParameter *parameter, const std::vector<lite::Tensor *> &inputs,
                  const std::vector<lite::Tensor *> &outputs, const InnerContext *ctx,
                  const mindspore::lite::PrimitiveC *primitive)
      : LiteKernel(parameter, inputs, outputs, ctx, primitive) {
    l2_norm_param_ = reinterpret_cast<L2NormParameter *>(op_parameter_);
  }
  ~L2NormCPUKernel() {
    FreeTmpBuffer();
    if (l2_norm_param_->axis_ != nullptr) {
      free(l2_norm_param_->axis_);
    }
  }

  int CalcSquareSum(int task_id);
  int DivSqrtSum(int task_id);
  int CalcL2NormTrailingAxis(int task_id);

  int Init() override;
  int ReSize() override;
  int Run() override;

 private:
  int MallocTmpBuffer();
  void FreeTmpBuffer();
  L2NormParameter *l2_norm_param_;
  float sqrt_sum_;
  float *input_ptr_;
  float *output_ptr_;
  float *tmp_sum_ = nullptr;
};
}  // namespace mindspore::kernel

#endif  // MINDSPORE_LITE_SRC_RUNTIME_KERNEL_ARM_FP32_RESHAPE_H_
