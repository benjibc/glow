/**
 * Copyright (c) Glow Contributors. See CONTRIBUTORS file.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#ifndef GLOW_RUNTIME_REQUESTDATA_H
#define GLOW_RUNTIME_REQUESTDATA_H

#include "folly/io/async/Request.h"

namespace glow {
namespace runtime {

class RequestData : public folly::RequestData {
public:
  int64_t appLevelRequestId{0};
  folly::Synchronized<std::vector<std::pair<std::string, int64_t>>> counters_;

  static RequestData *get() {
    auto data = dynamic_cast<RequestData *>(
        folly::RequestContext::get()->getContextData(kContextDataName));
    if (!data) {
      return nullptr;
    }
    return data;
  }

  static void set(std::unique_ptr<RequestData> data) {
    folly::RequestContext::get()->setContextData(kContextDataName,
                                                 std::move(data));
  }

  bool hasCallback() override { return false; }

private:
  static constexpr const char *kContextDataName{"Glow request data"};
};

} // namespace runtime
} // namespace glow
#endif // GLOW_RUNTIME_REQUESTDATA_H
