#include <iostream>
#include <vector>
#include "Sort.h"

int main() {
  std::vector<std::vector<int>> v1{{12, -3}, {7, 8}, {50}, {6, 2}, {5, 7}, {1, 10, 50},};

  std::cout << "before sort" << std::endl;
  std::cout << v1 << std::endl;

  sort(v1);

  std::cout << "after sort" << std::endl;
  std::cout << v1 << std::endl;
  std::cout << "Hello, World!" << std::endl;
  return 0;
}