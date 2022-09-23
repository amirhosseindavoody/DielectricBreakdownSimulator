#ifndef SRC_RANDOM_POSITION_GENERATOR_H
#define SRC_RANDOM_POSITION_GENERATOR_H

#include <glog/logging.h>

#include <random>
#include <vector>

#include "absl/hash/hash.h"
#include "src/constants.h"
#include "src/node.h"

namespace dielectric_breakdown {

class RandomPositionGenerator {
 public:
  RandomPositionGenerator(
      std::vector<int_t> max_pos,
      const std::unordered_map<std::vector<int_t>, Node*,
                               absl::Hash<std::vector<int_t>>>& map);

  std::vector<std::vector<int_t>> get(int_t n);

 private:
  std::vector<std::uniform_int_distribution<int_t>> distrib_;
  std::vector<int_t> max_pos_;

  const std::unordered_map<std::vector<int_t>, Node*,
                           absl::Hash<std::vector<int_t>>>& map_;
};

}  // namespace dielectric_breakdown

#endif  // SRC_RANDOM_POSITION_GENERATOR_H