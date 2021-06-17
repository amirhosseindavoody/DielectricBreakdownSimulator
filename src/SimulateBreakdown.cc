#include "src/SimulateBreakdown.h"

#include <glog/logging.h>

#include <algorithm>
#include <array>
#include <iostream>
#include <random>
#include <unordered_map>

#include "absl/hash/hash.h"
#include "absl/time/clock.h"
#include "constants.h"
#include "src/Node.h"
#include "src/RandomPositionGenerator.h"
#include "src/constants.h"

int_t simulate_breakdown() {
  //   LOG(INFO) << "Simulation started at " << absl::Now();
  std::unordered_map<Node::Position, Node*, absl::Hash<Node::Position>> map;

  auto generator = RandomPositionGenerator(0, kSize[0], map);

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