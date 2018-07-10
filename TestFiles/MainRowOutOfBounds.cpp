#include <iostream>
#include "Matrix.h"
#include "stdexcept"

int main() {
  Matrix m1({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}, {10, 11, 12}});

  try {
    std::cout << m1[-1][2] << std::endl;
  } catch (std::out_of_range& oor) {
    std::cout << oor.what() << std::endl;
  }

  return 0;
}