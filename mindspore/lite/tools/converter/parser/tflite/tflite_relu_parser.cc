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

#include <memory>
#include <vector>
#include "tools/converter/parser/tflite/tflite_relu_parser.h"

namespace mindspore {
namespace lite {
STATUS TfliteReluParser::Parse(const std::unique_ptr<tflite::OperatorT> &tfliteOp,
                                const std::vector<std::unique_ptr<tflite::TensorT>> &tfliteTensors,
                                const std::vector<std::unique_ptr<tflite::BufferT>> &tfliteModelBuffer,
                                const std::vector<std::unique_ptr<tflite::OperatorCodeT>> &tfliteOpSet,
                                schema::CNodeT *op, TensorCache *tensor_cache, bool quantizedModel) {
  MS_LOG(DEBUG) << "parse TfliteReluParser";
  std::unique_ptr<schema::ActivationT> attr(new schema::ActivationT());
  attr->type = schema::ActivationType_RELU;

  if (op != nullptr) {
    op->primitive = std::make_unique<schema::PrimitiveT>();
    op->primitive->value.type = schema::PrimitiveType_Activation;
    op->primitive->value.value = attr.release();
  }
  return RET_OK;
}

TfliteNodeRegister g_TfliteReluParser("Relu", new TfliteReluParser());
}  // namespace lite
}  // namespace mindspore
