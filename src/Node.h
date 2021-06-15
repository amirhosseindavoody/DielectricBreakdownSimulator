#ifndef SRC_NODE_H
#define SRC_NODE_H

#include <algorithm>
#include <array>
#include <iostream>
#include <random>
#include <unordered_map>

#include "constants.h"

constexpr int ndim = 2;

class Node {
 public:
  using Position = std::array<int_t, kNdim>;

  Node(const Position &pos);

  std::vector<Position> neighbors();

  Node *FindRoot();

  void UnionBySize(Node *node);

  void UnionByRank(Node *node);

  std::string str() const;

  Position pos() const;

  int_t cluster_size();

  Position cluster_max_pos();
  
  Position cluster_min_pos();

  Node *self_ptr();

  friend std::ostream &operator<<(std::ostream &os, const Node &dt);

 private:
  Position pos_;
  Position pos_max_;
  Position pos_min_;

  Node *parent_ = nullptr;

  int_t size_ = 1;
  int_t rank_ = 0;
};

std::ostream &operator<<(std::ostream &os, const Node::Position &pos);
std::string pos_to_string(const Node::Position &pos);

#endif  // SRC_NODE_H
