#include <iostream>
#include "Matrix.h"

int main() {
  Matrix m1({{1, 2, 3}, {4, 5, 6}});
  std::cout << "Matrix 1" << std::endl << m1;
  return 0;
}