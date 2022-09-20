#ifndef SRC_CONSTANTS_H
#define SRC_CONSTANTS_H

#include <array>
#include <cstdint>

using int_t = int64_t;

constexpr int kNdim = 3;
const std::array<int_t, kNdim> kSize{100, 100};

#endif  // SRC_CONSTANTS_H