#include "RandomPositionGenerator.h"

#include <unordered_set>

namespace {
// Will be used to obtain a seed for the random number engine
std::random_device rd;

// Standard mersenne_twister_engine seeded with rd()
std::mt19937 gen(rd());

constexpr int16_t kSeed = 0;
// gen.seed(kSeed);

}  // namespace
RandomPositionGenerator::RandomPositionGenerator(
    int_t min, int_t max,
    const std::unordered_map<Node::Position, Node*, absl::Hash<Node::Position>>&
        map)
    : distrib_(min, max), map_(map) {
  gen.seed(kSeed);
}

std::vector<Node::Position> RandomPositionGenerator::get(int_t n) {
  CHECK_GT(n, 0) << ": input n must be greater than 0";
  std::vector<Node::Position> res;
  Node::Position pos;

  // This set is used to keep track of the positions that are generated in the
  // current execution of the function.
  std::unordered_set<Node::Position, absl::Hash<Node::Position>> set;

  auto populate_pos = [this, &pos]() {
    for (auto& p : pos) {
      p = distrib_(gen);
    }
  };

  while (res.size() < static_cast<size_t>(n)) {
    populate_pos();
    if (map_.count(pos) == 0 && set.count(pos) == 0) {
      res.push_back(pos);
      set.insert(pos);
    }
  }

  return res;
}