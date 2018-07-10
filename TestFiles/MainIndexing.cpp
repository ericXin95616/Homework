#include <iostream>
#include "Matrix.h"

int main() {
  Matrix m1({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}, {10, 11, 12}});

  std::cout << " Matrix 1 " << std::endl;
  for (int rowIndex = 0; rowIndex < m1.getNumRows(); ++ rowIndex) {
    for (int colIndex = 0; colIndex < m1.getNumCols(); ++ colIndex) {
      std::cout << m1[rowIndex][colIndex] << ' ';
      m1[rowIndex][colIndex] += 1;
    }
    std::cout << std::endl;
  }

  std::cout << " Matrix 1 after adding 1 to each element " << std::endl;
  std::cout << std::endl << " Matrix 1 " << std::endl << m1 << std::endl;

  return 0;
}