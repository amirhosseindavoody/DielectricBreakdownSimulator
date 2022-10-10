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

  // Creates n new defects and returns if the dielectric is broken down. The
  // criteria for breakdown is that the is a continious path from coordinate 0
  // to max_coordinate along the zero'th dimensions.
  bool AddNodes(int_t num);

 private:
  // Creates a new node in the dielectric space.
  void AddNode();

  // List of nodes generated
  std::vector<Node *> nodes_;

  // All nodes indexed by their position
  std::unordered_map<std::vector<int_t>, Node *, absl::Hash<std::vector<int_t>>>
      nodes_by_position_;

  // The domain that the nodes are created inside
  Domain domain_;

  //  The random position generator
  RandomPositionGenerator random_position_generator_;
};

}  // namespace dielectric_breakdown

#endif  // SRC_NODE_MANAGER_H
