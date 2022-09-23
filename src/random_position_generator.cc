#include "src/random_position_generator.h"

#include <unordered_set>
#include <vector>

namespace dielectric_breakdown {

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
    std::vector<int_t> max_pos,
    const std::unordered_map<std::vector<int_t>, Node*,
                             absl::Hash<std::vector<int_t>>>& map)
    : max_pos_(max_pos), map_(map) {
  for (int i = 0; i < kNdim; ++i) {
    distrib_.push_back(std::uniform_int_distribution<int_t>(0, max_pos_[i]));
  }
}

std::vector<std::vector<int_t>> RandomPositionGenerator::get(int_t n) {
  CHECK_GT(n, 0) << ": input n must be greater than 0";
  std::vector<std::vector<int_t>> res;
  std::vector<int_t> pos;

  // This set is used to keep track of the positions that are generated in the
  // current execution of the function.
  std::unordered_set<std::vector<int_t>, absl::Hash<std::vector<int_t>>> set;

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

}  // namespace dielectric_breakdown
