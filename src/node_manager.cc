#include "src/node_manager.h"

namespace dielectric_breakdown {

NodeManager::NodeManager(
    const Domain &domain,
    const RandomPositionGenerator random_position_generator)
    : domain_(domain), random_position_generator_(random_position_generator){};



}  // namespace dielectric_breakdown