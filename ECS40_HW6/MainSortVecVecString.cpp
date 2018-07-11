#include <iostream>
#include <vector>
#include "Sort.h"



int main() {
  std::vector<std::vector<std::vector<std::string> > >
      v1{ {{"cats", "dogs", "monkey", "pear"}, {"bears", "beat", "beets", "Battle Start Galatica"}},
          {{"bear", "bears", "be"}, {"bee", "zebra"}, {"cantaloupe", "cactus"}}};

  std::cout << "before sort" << std::endl;
  std::cout << v1 << std::endl;

  sort(v1);

  std::cout << "after sort" << std::endl;
  std::cout << v1 << std::endl;
  std::cout << "Hello, World!" << std::endl;
  return 0;
}