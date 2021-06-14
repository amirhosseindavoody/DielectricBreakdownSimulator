#ifndef SRC_RANDOM_POSITION_GENERATOR_H
#define SRC_RANDOM_POSITION_GENERATOR_H

#include <random>

#include "Node.h"
#include "constants.h"

class RandomPositionGenerator {
 private:
  std::uniform_int_distribution<int_t> distrib_;

 public:
  RandomPositionGenerator(int_t min, int_t max);

  Node::Position get();
};

#endif  // SRC_RANDOM_POSITION_GENERATOR_H