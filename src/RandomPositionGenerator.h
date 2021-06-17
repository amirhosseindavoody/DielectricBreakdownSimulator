#ifndef SRC_RANDOM_POSITION_GENERATOR_H
#define SRC_RANDOM_POSITION_GENERATOR_H

#include <glog/logging.h>

#include <random>
#include <vector>

#include "absl/hash/hash.h"
#include "src/Node.h"
#include "src/constants.h"

class RandomPositionGenerator {
 private:
  std::uniform_int_distribution<int_t> distrib_;
  const std::unordered_map<Node::Position, Node*, absl::Hash<Node::Position>>&
      map_;

 public:
  RandomPositionGenerator(
      int_t min, int_t max,
      const std::unordered_map<Node::Position, Node*,
                               absl::Hash<Node::Position>>& map);

  std::vector<Node::Position> get(int_t n);
};

#endif  // SRC_RANDOM_POSITION_GENERATOR_H