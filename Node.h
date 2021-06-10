#ifndef NODE_H
#define NODE_H

#include <iostream>
#include <array>
#include <algorithm>
#include <unordered_map>
#include <random>

constexpr int ndim = 2;



// class Position : std::array<int_t, ndim> {
//   std::string str() {

//   }
// }

class Node {
  public:
    using int_t = int64_t;
    using Position = std::array<int_t, ndim>;

 private:
  Node* parent_ = nullptr;
  Position pos_;
  Position pos_min_;
  Position pos_max_;
  int_t size_;
  int_t rank_;
 public:
  Node(const Position& pos):
    pos_(pos), pos_min_(pos),
    pos_max_(pos), parent_(this),
    size_(1), rank_(0) {};

  std::vector<Position> neighbors() {
    std::vector<Position> neighbor;
    for (int i=0; i<pos_.size(); ++i) {
      if (pos_[i]>0) {
        neighbor.push_back(pos_);
        neighbor.back()[i] -= 1;
      }
      if (pos_[i]<(pos_.size()-1)) {
        neighbor.push_back(pos_);
        neighbor.back()[i] += 1;
      }
    }

    return neighbor;
  }

  Node* FindRoot() {
    // These two passes can be reduced to only one pass.
    Node* root = this;
    while (root != root->parent_){
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

  void UnionBySize(Node* node) {
    auto my_root = FindRoot();
    auto other_root = node->FindRoot();

    if (my_root == other_root) {
      return;
    }

    if (my_root->size_ < other_root->size_){
      std::swap(my_root, other_root);
    }

    other_root->parent_ = my_root;
    my_root->size_ = other_root->size_ + my_root->size_;

  }

  void UnionByRank(Node* node) {
    auto my_root = FindRoot();
    auto other_root = node->FindRoot();

    if (my_root == other_root) {
      return;
    }

    if (my_root->rank_ < other_root->rank_){
      std::swap(my_root, other_root);
    }

    other_root->parent_ = my_root;
    if (my_root->rank_ == other_root->rank_){
      my_root->rank_ += 1;
    }
  }

  std::string str() const {
    std::string res;
    for (const auto& p: pos_){
      res.append(std::to_string(p));
      res.push_back(',');
    }
    res.pop_back();
    return res;
  }

  Position const pos(){
    return pos_;
  }

  friend std::ostream& operator<<(std::ostream& os, const Node& dt);
};

std::ostream& operator<<(std::ostream& os, const Node& node)
{
    os << node.str();
    return os;
}

class RandomPositionGenerator {
  private:
    //Will be used to obtain a seed for the random number engine
    std::random_device rd_; 
    //Standard mersenne_twister_engine seeded with rd()
    std::mt19937 gen_; 

    std::uniform_int_distribution<> distrib_;
  
  public:
    RandomPositionGenerator(Node::int_t min, Node::int_t max, int16_t seed):
    rd_(), gen_(rd_()), distrib_(min, max) {
      gen_.seed(seed);
    }
  
    Node::Position get() {
      Node::Position pos;
      for (auto& p : pos) {
        p = distrib_(gen_);
      }
      return pos;
    }
};

#endif // NODE_H
