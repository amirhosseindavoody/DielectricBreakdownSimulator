#include "src/random_position_generator.h"

#include <gtest/gtest.h>

#include <iostream>
#include <vector>

#include "absl/log/log.h"

namespace dielectric_breakdown {

// Trivial test
TEST(RandomPositionGeneratorTest, TrivialTest) {
  std::vector<int_t> max_position{1};
  RandomPositionGenerator random_position_generator(max_position);
}

}  // namespace dielectric_breakdown
