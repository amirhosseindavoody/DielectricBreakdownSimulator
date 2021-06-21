#ifndef SRC_RANDOM_POSITION_GENERATOR_H
#define SRC_RANDOM_POSITION_GENERATOR_H

#include <glog/logging.h>

#include <random>
#include <vector>

#include "absl/hash/hash.h"
#include "src/Node.h"
#include "src/constants.h"

class RandomPositionGenerator {
 public:
  RandomPositionGenerator(
      std::array<int_t, kNdim> max_pos,
      const std::unordered_map<Node::Position, Node*,
                               absl::Hash<Node::Position>>& map);

  std::vector<Node::Position> get(int_t n);

 private:
  std::vector<std::uniform_int_distribution<int_t>> distrib_;
  std::array<int_t, kNdim> max_pos_;

  const std::unordered_map<Node::Position, Node*, absl::Hash<Node::Position>>&
      map_;
};

#endif  // SRC_RANDOM_POSITION_GENERATOR_H