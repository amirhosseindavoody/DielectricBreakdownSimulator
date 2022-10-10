#include <algorithm>
#include <array>
#include <iostream>
#include <random>
#include <unordered_map>

#include "absl/flags/flag.h"
#include "absl/flags/parse.h"
#include "absl/hash/hash.h"
#include "absl/log/log.h"
#include "absl/time/clock.h"
#include "src/breakdown_simulator.h"
#include "src/constants.h"
#include "src/node.h"
#include "src/random_position_generator.h"

namespace {

using namespace ::dielectric_breakdown;

}  // namespace

int main(int argc, char** argv) {
  absl::ParseCommandLine(argc, argv);

  LOG(INFO) << "Simulation started at " << absl::Now();
  std::vector<BreakdownSimulator::Result> sim_results;
  for (int i = 0; i < 10; ++i) {
    LOG_EVERY_N(INFO, 1) << "Step: " << i;

    BreakdownSimulator simulator(kDomain());
    BreakdownSimulator::Result sim_result = simulator.Run(
        /*initial_number_of_defects = */ 4000, /*max_steps = */ 10000);
    sim_results.push_back(sim_result);

    std::cout << "Simulation " << i << ": " << sim_result << std::endl;
  }
}
