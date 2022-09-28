#include "src/node_manager.h"

namespace dielectric_breakdown {

NodeManager::NodeManager(
    const Domain& domain,
    const RandomPositionGenerator random_position_generator)
    : domain_(domain), random_position_generator_(random_position_generator){};

bool NodeManager::AddNodes(int_t num) {
  bool breakdown = false;
  std::vector<std::vector<int_t>> pos_vec = random_position_generator_.get(num);

  for (auto& pos : pos_vec) {
    nodes_by_position_.insert({pos, new Node(pos)});
    auto neighbors = nodes_by_position_.at(pos)->neighbors();
    for (auto& neighbor : neighbors) {
      if (nodes_by_position_.count(neighbor) == 1) {
        nodes_by_position_.at(pos)->UnionByRank(
            nodes_by_position_.at(neighbor));
      }
    }

    LOG_EVERY_N(INFO, 1000)
        << nodes_by_position_.at(pos)->cluster_min_pos()[0] << " , "
        << nodes_by_position_.at(pos)->cluster_max_pos()[0];
    if (nodes_by_position_.at(pos)->cluster_min_pos()[0] <= 0 &&
        nodes_by_position_.at(pos)->cluster_max_pos()[0] >= domain_.size[0]) {
      breakdown = true;
    }
  }

  return breakdown;
}

}  // namespace dielectric_breakdown