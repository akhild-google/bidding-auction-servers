/*
 * Copyright 2023 Google LLC
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

#ifndef SERVICES_BIDDING_SERVICE_CONSTANTS_H_
#define SERVICES_BIDDING_SERVICE_CONSTANTS_H_

#include <cstdint>

namespace privacy_sandbox::bidding_auction_servers {

inline constexpr uint64_t kProtectedAudienceGenerateBidBlobVersion = 1;
inline constexpr uint64_t kProtectedAppSignalsGenerateBidBlobVersion = 2;
inline constexpr uint64_t kPrepareDataForAdRetrievalBlobVersion = 3;
inline constexpr char kDecodedSignals[] = "decodedSignals";
inline constexpr char kRetrievalData[] = "retrievalData";
inline constexpr char kPrepareDataForAdRetrievalHandler[] =
    "prepareDataForAdRetrieval";
inline constexpr char kPrepareDataForAdRetrievalEntryFunctionName[] =
    "prepareDataForAdRetrievalEntryFunction";
inline constexpr char kPrepareDataForAdRetrievalArgs[] =
    "encodedOnDeviceSignalsVersion, "
    "sellerAuctionSignals, contextualSignals";
constexpr absl::string_view kProtectedAudienceGenerateBidsArgs =
    "interest_group, auction_signals, buyer_signals, trusted_bidding_signals, "
    "device_signals";
constexpr absl::string_view kProtectedAppSignalsGenerateBidsArgs =
    "ads, sellerAuctionSignals, buyerSignals, "
    "preprocessedDataForRetrieval";

// Params related to the UDF that can be used to retrieve the protected
// embeddings that can later be used to fetch the top-k ads from ads retrieval
// service.
inline constexpr int kNumPrepareDataForRetrievalUdfArgs = 5;
enum class PrepareDataForRetrievalUdfArgs {
  kProtectedAppSignals = 0,
  kProtectedAppSignalsVersion,
  kAuctionSignals,
  kBuyerSignals,
  kFeatureFlags,
};

// Params related to the UDF to use to generate bids for the protected signals.
inline constexpr int kNumGenerateBidsUdfArgs = 7;
enum class GenerateBidsUdfArgs {
  kAds = 0,
  kAuctionSignals,
  kBuyerSignals,
  kPreProcessedDataForRetrieval,
  kFeatureFlags,
};

inline constexpr char kUnexpectedNumberOfRomaResponses[] =
    "Unexpected count of roma responses received.";
inline constexpr char kDecodedProtectedAppSignalsNotFound[] =
    "Decoded protected signals were not found.";
inline constexpr char kDecodedProtectedAppSignalsUnexpectedType[] =
    "Decoded protected signals are not in a string format.";

}  // namespace privacy_sandbox::bidding_auction_servers

#endif  // SERVICES_BIDDING_SERVICE_CONSTANTS_H_
