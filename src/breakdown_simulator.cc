#include "src/breakdown_simulator.h"

#include <glog/logging.h>

#include <algorithm>
#include <array>
#include <iostream>
#include <random>
#include <unordered_map>

#include "absl/hash/hash.h"
#include "absl/strings/substitute.h"
#include "absl/time/clock.h"
#include "constants.h"
#include "src/constants.h"
#include "src/node.h"
#include "src/random_position_generator.h"

namespace dielectric_breakdown {

int_t simulate_breakdown() {
  LOG(INFO) << "Simulation started at " << absl::Now();
  std::unordered_map<std::vector<int_t>, Node*, absl::Hash<std::vector<int_t>>>
      map;

  auto generator = RandomPositionGenerator(kSize, map);

  bool breakdown = false;
  int_t step_counter = 0;

  while (!breakdown) {
    step_counter++;
    // LOG_EVERY_N(INFO, 100) << i;
    auto pos_vec = generator.get(1);
    for (auto& p : pos_vec) {
      map.insert({p, new Node(p)});
      auto neighbors = map.at(p)->neighbors();
      for (auto& n : neighbors) {
        if (map.count(n) == 1) {
          map.at(p)->UnionByRank(map.at(n));
        }
      }

      LOG_EVERY_N(INFO, 1000) << map.at(p)->cluster_min_pos()[0] << " , "
                              << map.at(p)->cluster_max_pos()[0];
      if (map.at(p)->cluster_min_pos()[0] == 0 &&
          map.at(p)->cluster_max_pos()[0] == kSize[0]) {
        LOG(INFO) << "Breakdown in " << step_counter << " steps.";
        breakdown = true;
        break;
      }
    }
  }

  return step_counter;
}

BreakdownSimulator::BreakdownSimulator(const std::vector<int_t>& size)
    : random_position_generator_(size, map_), size_(size) {}

bool BreakdownSimulator::CreateDefect(int_t num_defects) {
  bool breakdown = false;
  auto pos_vec = random_position_generator_.get(num_defects);

  for (auto& pos : pos_vec) {
    map_.insert({pos, new Node(pos)});
    auto neighbors = map_.at(pos)->neighbors();
    for (auto& neighbor : neighbors) {
      if (map_.count(neighbor) == 1) {
        map_.at(pos)->UnionByRank(map_.at(neighbor));
      }
    }

    LOG_EVERY_N(INFO, 1000) << map_.at(pos)->cluster_min_pos()[0] << " , "
                            << map_.at(pos)->cluster_max_pos()[0];
    if (map_.at(pos)->cluster_min_pos()[0] <= 0 &&
        map_.at(pos)->cluster_max_pos()[0] >= size_[0]) {
      breakdown = true;
    }
  }

  return breakdown;
}

BreakdownSimulator::Result BreakdownSimulator::Run(
    int_t initial_number_of_defects, int_t max_steps) {
  Result result;

  // Assume that there are a number of pre-existing defects.
  while (!result.breakdown &&
         result.initial_number_of_defects < initial_number_of_defects) {
    result.breakdown = CreateDefect(1);
    result.initial_number_of_defects++;
    result.final_number_of_defects++;
  }

  // Progress in time and create one new defect with each timestep
  while (!result.breakdown && result.step_count < max_steps) {
    result.breakdown = CreateDefect(1);
    result.final_number_of_defects++;
    result.step_count++;
  }

  return result;
}

BreakdownSimulator::~BreakdownSimulator() {
  for (auto& m : map_) {
    delete m.second;
    m.second = nullptr;
  }
}

std::ostream& operator<<(std::ostream& os,
                         const BreakdownSimulator::Result& result) {
  os << absl::Substitute("step=$0, breakdown=$1, N0=$2, Nfinal=$3",
                         result.step_count, result.breakdown,
                         result.initial_number_of_defects,
                         result.final_number_of_defects);
  return os;
}

}  // namespace dielectric_breakdown
