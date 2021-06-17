#include "src/RandomPositionGenerator.h"

#include <unordered_set>

namespace {

constexpr int kSeed = 0;

std::mt19937_64& random_gen() {
  static std::mt19937_64 gen_ = [] {
    // Will be used to obtain a seed for the random number engine
    std::random_device rd;
    // Standard mersenne_twister_engine seeded with rd()
    std::mt19937_64 gen(rd());
    // Set the seed
    gen.seed(kSeed);
    return gen;
  }();
  return gen_;
}

}  // namespace

RandomPositionGenerator::RandomPositionGenerator(
    int_t min, int_t max,
    const std::unordered_map<Node::Position, Node*, absl::Hash<Node::Position>>&
        map)
    : distrib_(min, max), map_(map) {}

std::vector<Node::Position> RandomPositionGenerator::get(int_t n) {
  CHECK_GT(n, 0) << ": input n must be greater than 0";
  std::vector<Node::Position> res;
  Node::Position pos;

  // This set is used to keep track of the positions that are generated in the
  // current execution of the function.
  std::unordered_set<Node::Position, absl::Hash<Node::Position>> set;

  auto populate_pos = [this, &pos]() {
    for (auto& p : pos) {
      p = distrib_(random_gen());
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