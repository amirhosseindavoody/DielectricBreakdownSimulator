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
    std::array<int_t, kNdim> max_pos,
    const std::unordered_map<Node::Position, Node*, absl::Hash<Node::Position>>&
        map)
    : max_pos_(max_pos), map_(map) {
  for (int i = 0; i < kNdim; ++i) {
    distrib_.push_back(std::uniform_int_distribution<int_t>(0, max_pos_[i]));
  }
}

std::vector<Node::Position> RandomPositionGenerator::get(int_t n) {
  CHECK_GT(n, 0) << ": input n must be greater than 0";
  std::vector<Node::Position> res;
  Node::Position pos;

  // This set is used to keep track of the positions that are generated in the
  // current execution of the function.
  std::unordered_set<Node::Position, absl::Hash<Node::Position>> set;

  auto populate_pos = [this, &pos]() {
    for (size_t i = 0; i < pos.size(); i++) {
      pos[i] = distrib_[i](random_gen());
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