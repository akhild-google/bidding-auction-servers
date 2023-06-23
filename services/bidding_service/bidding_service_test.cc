//  Copyright 2022 Google LLC
//
//  Licensed under the Apache License, Version 2.0 (the "License");
//  you may not use this file except in compliance with the License.
//  You may obtain a copy of the License at
//
//       http://www.apache.org/licenses/LICENSE-2.0
//
//  Unless required by applicable law or agreed to in writing, software
//  distributed under the License is distributed on an "AS IS" BASIS,
//  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//  See the License for the specific language governing permissions and
//  limitations under the License.

#include "services/bidding_service/bidding_service.h"

#include <memory>

#include "absl/synchronization/blocking_counter.h"
#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "services/bidding_service/benchmarking/bidding_no_op_logger.h"
#include "services/bidding_service/generate_bids_reactor.h"
#include "services/common/metric/server_definition.h"
#include "services/common/test/mocks.h"

namespace privacy_sandbox::bidding_auction_servers {
namespace {

TEST(BiddingServiceTest, InstantiatesGenerateBidsReactor) {
  MockCodeDispatchClient client;
  GenerateBidsRequest request;
  GenerateBidsResponse response;
  absl::BlockingCounter init_pending(1);
  // initialize
  server_common::metric::ServerConfig config_proto;
  config_proto.set_mode(server_common::metric::ServerConfig::PROD);
  metric::BiddingContextMap(
      server_common::metric::BuildDependentConfig(config_proto));
  BiddingService service(
      [&client, &init_pending](
          const GenerateBidsRequest* request, GenerateBidsResponse* response,
          server_common::KeyFetcherManagerInterface* key_fetcher_manager,
          CryptoClientWrapperInterface* crypto_client,
          const BiddingServiceRuntimeConfig& runtime_config) {
        std::unique_ptr<BiddingBenchmarkingLogger> benchmarkingLogger =
            std::make_unique<BiddingNoOpLogger>();
        auto mock = new MockGenerateBidsReactor(
            client, request, response, "", std::move(benchmarkingLogger),
            key_fetcher_manager, crypto_client, runtime_config);
        EXPECT_CALL(*mock, Execute).Times(1);
        init_pending.DecrementCount();
        return mock;
      },
      nullptr, nullptr, BiddingServiceRuntimeConfig());
  grpc::CallbackServerContext context;
  auto mock = service.GenerateBids(&context, &request, &response);
  init_pending.Wait();
  delete mock;
}

}  // namespace
}  // namespace privacy_sandbox::bidding_auction_servers