#include <glog/logging.h>

#include <algorithm>
#include <array>
#include <iostream>
#include <random>
#include <unordered_map>

#include "absl/hash/hash.h"
#include "absl/time/clock.h"
#include "src/Node.h"
#include "src/RandomPositionGenerator.h"
#include "src/SimulateBreakdown.h"
#include "src/constants.h"

int main(int argc, char* argv[]) {
  // Initialize Google’s logging library.
  google::InitGoogleLogging(argv[0]);

  LOG(INFO) << "Simulation started at " << absl::Now();
  std::vector<int> breakdown_step;
  for (int i = 0; i < 10; ++i) {
    breakdown_step.push_back(simulate_breakdown());
    std::cout << "Breakdown at: " << breakdown_step.back() << std::endl;
  }
}
