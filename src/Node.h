#ifndef NODE_H
#define NODE_H

#include <iostream>
#include <array>
#include <algorithm>
#include <unordered_map>
#include <random>
#include "constants.h"

constexpr int ndim = 2;

class Node
{
public:
  using Position = std::array<int_t, kNdim>;

  Node(const Position &pos);

  std::vector<Position> neighbors();

  Node *FindRoot();

  void UnionBySize(Node *node);

  void UnionByRank(Node *node);

  std::string str() const;

  Position pos() const;

  friend std::ostream &operator<<(std::ostream &os, const Node &dt);

private:
  Position pos_;
  Position pos_max_;
  Position pos_min_;

  Node *parent_ = nullptr;

  int_t size_ = 1;
  int_t rank_ = 0;
};

#endif // NODE_H
