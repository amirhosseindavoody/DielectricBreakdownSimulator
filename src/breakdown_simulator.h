#ifndef SRC_SIMULATE_BREAKDOWN_H
#define SRC_SIMULATE_BREAKDOWN_H

#include "src/constants.h"
#include "src/node_manager.h"
#include "src/random_position_generator.h"

namespace dielectric_breakdown {

int_t simulate_breakdown();

class BreakdownSimulator {
 public:
  struct Result {
    int_t step_count = 0;
    bool breakdown = false;
    int_t initial_number_of_defects = 0;
    int_t final_number_of_defects = 0;
  };

  explicit BreakdownSimulator(const Domain& domain);

  ~BreakdownSimulator();

  // Instantiate the dielectric with a given initial_number_of_defects at step
  // zero, then keep increasing the number of defects by one defect per step.
  // The simulation continues for a maximum of max_steps.
  Result Run(int_t initial_number_of_defects, int_t max_steps);

 private:
  // Creates n new defects and returns if the dielectric is broken down. The
  // criteria for breakdown is that the is a continious path from coordinate 0
  // to max_coordinate along the zero'th dimensions.
  bool CreateDefect(int_t num_defects);

  std::unordered_map<std::vector<int_t>, Node*, absl::Hash<std::vector<int_t>>>
      map_;
  RandomPositionGenerator random_position_generator_;
  Domain domain_;
  NodeManager node_manager_;
};

std::ostream& operator<<(std::ostream& os,
                         const BreakdownSimulator::Result& result);

}  // namespace dielectric_breakdown

#endif  // SRC_SIMULATE_BREAKDOWN_H