#include <iostream>
#include <vector>
#include "Sort.h"



int main() {
  std::vector<std::string> v1{"bear", "bears", "be", "bee", "zebra", "cantaloupe", "cactus"};

  std::cout << "before sort" << std::endl;
  std::cout << v1 << std::endl;

  sort(v1);

  std::cout << "after sort" << std::endl;
  std::cout << v1 << std::endl;
  std::cout << "Hello, World!" << std::endl;
  return 0;
}