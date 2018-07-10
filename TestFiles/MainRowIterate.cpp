#include <iostream>
#include "Matrix.h"

int main() {
  Matrix m1({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}, {10, 11, 12}});

  for (RowItr ritr = m1.rowBegin(); ritr != m1.rowEnd(); ++ritr) {
    for (RowElementItr elementItr = ritr.begin(); elementItr != ritr.end(); ++elementItr) {
      std::cout << *elementItr << ' ';
    }
    std::cout << std::endl;
  }

  return 0;
}