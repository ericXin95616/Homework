#include <iostream>
#include "Matrix.h"
#include "MatrixError.h"

int main() {
  try {
    Matrix m1({{1, 2, 3}, {4, 5}, {7, 8, 9}});
    std::cout << "Matrix 1" << std::endl << m1;
  } catch(MatrixError& me){
    std::cout << me.what() << std::endl;
  }
  return 0;
}