#ifndef SRC_RANDOM_POSITION_GENERATOR_H
#define SRC_RANDOM_POSITION_GENERATOR_H

#include <random>
#include <vector>

#include "absl/hash/hash.h"
#include "constants.h"
#include "node.h"

namespace dielectric_breakdown
{

  class RandomPositionGenerator
  {
  public:
    RandomPositionGenerator(std::vector<int_t> max_pos);

    // Get a vector of N unique random positions.
    std::vector<std::vector<int_t>> getN(int_t n);

    // Get a one random position.
    std::vector<int_t> get();

  private:
    std::vector<std::uniform_int_distribution<int_t>> distributions_;
    std::vector<int_t> max_positions_;
  };

} // namespace dielectric_breakdown

#endif // SRC_RANDOM_POSITION_GENERATOR_H