//
// Created by mfbut on 3/3/2018.
//

#include <fstream>
#include <iostream>
#include "Matrix.h"

int main(int argc, char** argv){
  constexpr int numArgsNeeded = 3;

  if(argc == numArgsNeeded){
    std::ifstream matFile1(argv[1]), matFile2(argv[2]);
    if(matFile1.good()){
      Matrix matrix1, matrix2;

      matFile1 >> matrix1;
      std::cout << "The matrix in " << argv[1] << " is " << std::endl << matrix1;

      matFile2 >> matrix2;
      std::cout << "The matrix in " << argv[2] << " is " << std::endl << matrix2;

      matrix1 -= matrix2;
      std::cout << "Matrix1 -= Matrix2" << std::endl;

      std::cout << "Matrix 1" << std::endl;
      std::cout << matrix1;

      std::cout << std::endl;

      std::cout << "Matrix 2" << std::endl;
      std::cout << matrix2;
    }else{
      std::cout << "Could not open " << argv[1] << std::endl;
    }
  } else{
    std::cout << "Wrong number of parameters passed in" << std::endl;
    std::cout << "Expected " << (numArgsNeeded - 1) << " but received " << (argc - 1) << std::endl;
  }

  return 0;
}