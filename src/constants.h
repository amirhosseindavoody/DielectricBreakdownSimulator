#ifndef SRC_CONSTANTS_H
#define SRC_CONSTANTS_H

#include <cstdint>
#include <vector>

namespace dielectric_breakdown {

using int_t = int64_t;

struct Domain {
  int_t number_of_dimensions = 0;
  std::vector<int_t> size;
};

// It is important to inline this function since it is declared in a header
// file. The other way would be to declare it here and put the definition in a
// separate cc file.
inline const Domain& kDomain() {
  static const auto* domain_ptr = [] {
    return new Domain{
        .number_of_dimensions = 2,
        .size = {100, 100},
    };
  }();

  return *domain_ptr;
}

}  // namespace dielectric_breakdown

#endif  // SRC_CONSTANTS_H