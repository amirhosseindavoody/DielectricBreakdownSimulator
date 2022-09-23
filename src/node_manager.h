#ifndef SRC_NODE_MANAGER_H
#define SRC_NODE_MANAGER_H

#include <algorithm>
#include <iostream>
#include <random>
#include <unordered_map>
#include <vector>

#include "src/constants.h"
#include "src/node.h"
#include "src/random_position_generator.h"

namespace dielectric_breakdown {

class NodeManager {
 public:
  NodeManager(const Domain &domain,
              const RandomPositionGenerator random_position_generator);

 private:
  // List of nodes generated
  std::vector<Node *> nodes_;

  // The domain that the nodes are created inside
  Domain domain_;

  //  The random position generator
  RandomPositionGenerator random_position_generator_;
};

}  // namespace dielectric_breakdown

#endif  // SRC_NODE_MANAGER_H
