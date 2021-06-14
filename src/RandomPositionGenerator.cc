#include "RandomPositionGenerator.h"

namespace {
// Will be used to obtain a seed for the random number engine
std::random_device rd;

// Standard mersenne_twister_engine seeded with rd()
std::mt19937 gen(rd());

constexpr int16_t kSeed = 0;
// gen.seed(kSeed);

}  // namespace
RandomPositionGenerator::RandomPositionGenerator(int_t min, int_t max)
    : distrib_(min, max) {
  gen.seed(kSeed);
}

Node::Position RandomPositionGenerator::get() {
  Node::Position pos;
  for (auto &p : pos) {
    p = distrib_(gen);
  }
  return pos;
}