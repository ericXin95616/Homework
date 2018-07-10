//
// Created by mfbut on 3/3/2018.
//

#include "Matrix.h"

int main(){
  Matrix m1({{1, 2, 3}, {4, 5, 6}});
  m1 = m1;
  std::cout << "Negative Matrix " << std::endl << m1;
  return 0;
}
