#include <iostream>
#include <vector>
#include "Sort.h"



int main() {
  std::vector<int>v1{7, 8, 6, 2, 5, 7};

  std::cout << "before sort" << std::endl;
  std::cout << v1 << std::endl;

  sort(v1);

  std::cout << "after sort" << std::endl;
  std::cout << v1 << std::endl;
  std::cout << "Hello, World!" << std::endl;
  return 0;
}