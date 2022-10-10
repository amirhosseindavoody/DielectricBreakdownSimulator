#include "src/random_position_generator.h"

#include <unordered_set>
#include <vector>

#include "absl/container/flat_hash_set.h"
#include "absl/log/check.h"

namespace dielectric_breakdown {

namespace {

constexpr int kSeed = 0;

inline std::mt19937_64& random_gen() {
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
    std::vector<int_t> max_positions)
    : max_positions_(max_positions) {
  for (const auto max_position : max_positions_) {
    distributions_.push_back(
        std::uniform_int_distribution<int_t>(0, max_position));
  }
}

std::vector<std::vector<int_t>> RandomPositionGenerator::getN(int_t n) {
  CHECK_GT(n, 0) << ": input n must be greater than 0";
  std::vector<std::vector<int_t>> res;
  std::vector<int_t> pos;

  // This set is used to keep track of the positions that are generated in the
  // current execution of the function.
  absl::flat_hash_set<std::vector<int_t>> set;

  while (res.size() < static_cast<size_t>(n)) {
    std::vector<int_t> pos = get();
    if (set.count(pos) == 0) {
      res.push_back(pos);
      set.insert(pos);
    }
  }

  return res;
}

std::vector<int_t> RandomPositionGenerator::get() {
  std::vector<int_t> res;

  for (auto& d : distributions_) {
    res.push_back(d(random_gen()));
  }

  return res;
}

}  // namespace dielectric_breakdown
