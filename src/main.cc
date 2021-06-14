#include <algorithm>
#include <array>
#include <iostream>
#include <random>
#include <unordered_map>

#include "Node.h"
#include "RandomPositionGenerator.h"
#include "absl/hash/hash.h"
#include "constants.h"

int main() {
  std::unordered_map<Node::Position, Node *, absl::Hash<Node::Position>> map;

  auto generator = RandomPositionGenerator(0, 1000, map);
  Node *node = new Node(generator.get(1)[0]);

  for (int64_t i = 0; i < 10; i++) {
    while (!node || map.count(node->pos()) == 1) {
      delete node;
      node = new Node(generator.get(1)[0]);
    }
    map[node->pos()] = node;
    node = nullptr;
  }

  for (auto &m : map) {
    std::cout << m.first << " -- " << m.second->str() << std::endl;
    delete m.second;
    m.second = nullptr;
  }

  std::cout << std::endl;
}
