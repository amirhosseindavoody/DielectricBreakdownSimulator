#include <glog/logging.h>

#include <algorithm>
#include <array>
#include <iostream>
#include <random>
#include <unordered_map>

#include "absl/flags/flag.h"
#include "absl/flags/parse.h"
#include "absl/hash/hash.h"
#include "absl/time/clock.h"
// #include "gflags/gflags.h"
#include "src/BreakdownSimulator.h"
#include "src/Node.h"
#include "src/RandomPositionGenerator.h"
#include "src/constants.h"

ABSL_FLAG(int64_t, size_of_grid, 100, "Size of the grid");
// DEFINE_int64(size_of_grid, 100, "Size of the grid");

int main(int argc, char** argv) {
  // Initialize Google’s logging library.
  google::InitGoogleLogging(argv[0]);
  google::ParseCommandLineFlags(&argc, &argv, false);


  absl::ParseCommandLine(argc, argv);

  std::cout << "size_of_grid=" << absl::GetFlag(FLAGS_size_of_grid)
            << std::endl;

  // std::cout << "size_of_grid=" << FLAGS_size_of_grid
  //           << std::endl;

  LOG(INFO) << "Simulation started at " << absl::Now();
  // std::vector<BreakdownSimulator::Result> sim_results;
  // for (int i = 0; i < 10; ++i) {

  //   BreakdownSimulator simulator(kSize);
  //   BreakdownSimulator::Result sim_result = simulator.Run(0, 10000);
  //   sim_results.push_back(sim_result);

  //   std::cout << "Simulation " << i << ": " << sim_results.back() <<
  //   std::endl;
  // }
}
