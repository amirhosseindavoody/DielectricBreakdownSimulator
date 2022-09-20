#include <glog/logging.h>

#include <algorithm>
#include <array>
#include <iostream>
#include <random>
#include <unordered_map>

#include "absl/hash/hash.h"
#include "absl/time/clock.h"
#include "gflags/gflags.h"
#include "src/breakdown_simulator.h"
#include "src/constants.h"
#include "src/node.h"
#include "src/random_position_generator.h"

DEFINE_int64(size_of_grid, 100, "Size of the grid");

int main(int argc, char** argv) {
  // Initialize Google’s logging library.
  google::InitGoogleLogging(argv[0]);
  google::ParseCommandLineFlags(&argc, &argv, false);

  // FLAGS_logtostderr = true;

  LOG(INFO) << "Simulation started at " << absl::Now();
  std::vector<BreakdownSimulator::Result> sim_results;
  for (int i = 0; i < 10; ++i) {
    LOG_EVERY_N(INFO, 1) << "Step: " << i;

    BreakdownSimulator simulator(kSize);
    BreakdownSimulator::Result sim_result = simulator.Run(4000, 10000);
    sim_results.push_back(sim_result);

    std::cout << "Simulation " << i << ": " << sim_results.back() << std::endl;
  }
}
