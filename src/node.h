#ifndef SRC_NODE_H
#define SRC_NODE_H

#include <algorithm>
#include <iostream>
#include <random>
#include <unordered_map>
#include <vector>

#include "constants.h"

namespace dielectric_breakdown {

class Node {
 public:
  Node(const std::vector<int_t> &pos);

  std::vector<std::vector<int_t>> neighbors();

  Node *FindRoot();

  void UnionBySize(Node *node);

  void UnionByRank(Node *node);

  std::string str() const;

  const std::vector<int_t> &pos() const;

  int_t cluster_size();

  const std::vector<int_t> &cluster_max_pos();

  const std::vector<int_t> &cluster_min_pos();

  Node *self_ptr();

  friend std::ostream &operator<<(std::ostream &os, const Node &dt);

 private:
  std::vector<int_t> pos_;
  std::vector<int_t> pos_max_;
  std::vector<int_t> pos_min_;

  Node *parent_ = nullptr;

  int_t size_ = 1;
  int_t rank_ = 0;
};

std::ostream &operator<<(std::ostream &os, const std::vector<int_t> &pos);
std::string pos_to_string(const std::vector<int_t> &pos);

}  // namespace dielectric_breakdown

#endif  // SRC_NODE_H
