#include "src/random_position_generator.h"

#include <gtest/gtest.h>

#include <iostream>
#include <vector>

#include "absl/log/log.h"

namespace dielectric_breakdown {

// Demonstrate some basic assertions.
TEST(HelloTest, BasicAssertions) {
  std::vector<int_t> max_position{1};
  RandomPositionGenerator random_position_generator(max_position);
  LOG(INFO) << "Amirhossein: hi";
  std::cout << "Hello world!" << std::endl;
}

}  // namespace dielectric_breakdown
