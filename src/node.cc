#include "node.h"

#include <vector>

namespace dielectric_breakdown {

Node::Node(const std::vector<int_t> &pos)
    : pos_(pos),
      pos_max_(pos),
      pos_min_(pos),
      parent_(this),
      size_(1),
      rank_(0){};

Node *Node::self_ptr() { return this; };

std::vector<std::vector<int_t>> Node::neighbors() {
  std::vector<std::vector<int_t>> neighbor;
  for (std::size_t i = 0; i < pos_.size(); ++i) {
    if (pos_[i] > 0) {
      neighbor.push_back(pos_);
      neighbor.back()[i] -= 1;
    }
    if (pos_[i] < (kDomain().size[i] - 1)) {
      neighbor.push_back(pos_);
      neighbor.back()[i] += 1;
    }
  }
  return neighbor;
}

Node *Node::FindRoot() {
  // These two passes can be reduced to only one pass.
  Node *root = this;
  while (root != root->parent_) {
    root = root->parent_;
  }
  auto node = this;
  while (node->parent_ != root) {
    auto parent = node->parent_;
    node->parent_ = root;
    node = parent;
  }
  return root;
}

void Node::UnionBySize(Node *node) {
  auto my_root = FindRoot();
  auto other_root = node->FindRoot();

  if (my_root == other_root) {
    return;
  }

  if (my_root->size_ < other_root->size_) {
    std::swap(my_root, other_root);
  }

  other_root->parent_ = my_root;
  my_root->size_ = other_root->size_ + my_root->size_;
}

void Node::UnionByRank(Node *node) {
  auto my_root = FindRoot();
  auto other_root = node->FindRoot();

  if (my_root == other_root) {
    return;
  }

  if (my_root->rank_ < other_root->rank_) {
    std::swap(my_root, other_root);
  }

  other_root->parent_ = my_root;
  if (my_root->rank_ == other_root->rank_) {
    my_root->rank_ += 1;
  }

  // Optionally keep track of cluster sizes
  my_root->size_ = other_root->size_ + my_root->size_;

  // Update the minimum and maximum position of the cluster
  for (size_t i = 0; i < pos_max_.size(); ++i) {
    my_root->pos_min_[i] = my_root->pos_min_[i] > other_root->pos_min_[i]
                               ? other_root->pos_min_[i]
                               : my_root->pos_min_[i];
    my_root->pos_max_[i] = my_root->pos_max_[i] < other_root->pos_max_[i]
                               ? other_root->pos_max_[i]
                               : my_root->pos_max_[i];
  }
}

std::string Node::str() const {
  std::string res;
  for (const auto &p : pos_) {
    res.append(std::to_string(p));
    res.push_back(',');
  }
  res.pop_back();
  return res;
}

const std::vector<int_t> &Node::pos() const { return pos_; }

std::ostream &operator<<(std::ostream &os, const Node &node) {
  os << node.str();
  return os;
}

int_t Node::cluster_size() { return FindRoot()->size_; };

const std::vector<int_t> &Node::cluster_max_pos() {
  return FindRoot()->pos_max_;
}

const std::vector<int_t> &Node::cluster_min_pos() {
  return FindRoot()->pos_min_;
}

std::string pos_to_string(const std::vector<int_t> &pos) {
  std::string res;
  for (const auto &p : pos) {
    res.append(std::to_string(p));
    res.push_back(',');
  }
  res.pop_back();
  return res;
}

std::ostream &operator<<(std::ostream &os, const std::vector<int_t> &pos) {
  std::string res;
  for (const auto &p : pos) {
    res.append(std::to_string(p));
    res.push_back(',');
  }
  res.pop_back();
  os << res;
  return os;
}

}  // namespace dielectric_breakdown