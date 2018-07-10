//
// Created by mfbut on 3/3/2018.
//

#include <fstream>
#include <iostream>
#include "Matrix.h"

int main(int argc, char** argv){
  constexpr int numArgsNeeded = 2;
  if(argc == numArgsNeeded){
    std::ifstream matFile(argv[1]);
    if(matFile.good()){
      Matrix matrix;
      matFile >> matrix;
      std::cout << "The matrix in " << argv[1] << " is " << std::endl << matrix;
    }else{
      std::cout << "Could not open " << argv[1] << std::endl;
    }
  } else{
    std::cout << "Wrong number of parameters passed in" << std::endl;
    std::cout << "Expected " << (numArgsNeeded - 1) << " but received " << (argc - 1) << std::endl;
  }

  return 0;
}