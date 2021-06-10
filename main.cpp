#include <iostream>
#include <array>
#include <algorithm>
#include <unordered_map>
#include <random>

#include "Node.h"

int main() {
  std::unordered_map<Node::Position, Node*> map;
  
  auto generator = RandomPositionGenerator(0, 1000, 0);
  Node* node = nullptr;

  for (int64_t i=0; i<10; i++) {
      while (!node || map.count(node->pos())==1){
        delete node;
        node = new Node(generator.get());
      }
      map[node->str()] = node;
      node = nullptr;
  }

  for (auto& m : map){
    std::cout << m.first << " -- " << m.second->str() << std::endl;
    delete m.second;
    m.second = nullptr;
  }

  std::cout << std::endl;

  std::cout << "Hello World!\n";
}
