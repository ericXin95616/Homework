#include <iostream>
#include "Matrix.h"

int main() {
  Matrix m1({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}, {10, 11, 12}});

  for (ColItr citr = m1.colBegin(); citr != m1.colEnd(); ++citr) {
    for (ColElementItr elementItr = citr.begin(); elementItr != citr.end(); ++elementItr) {
      std::cout << *elementItr << ' ';
    }
    std::cout << std::endl;
  }

  return 0;
}