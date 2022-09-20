#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <array>
#include <cstdint>

using int_t = int64_t;

constexpr int kNdim = 3;
const std::array<int_t, kNdim> kSize{100, 100};

#endif  // CONSTANTS_H