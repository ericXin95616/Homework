//
// Created by mfbut on 1/22/2018.
//

#ifndef MATRIX_MATRIX_H
#define MATRIX_MATRIX_H
#include <vector>
#include <iostream>

#include "RowItr.h"
#include "RowElementItr.h"
#include "ColItr.h"
#include "ColElementItr.h"
#include "MatrixSizeError.h"
#include "MatrixSizeMismatchError.h"
#include "MatrixInnerDimensionMismatchError.h"

typedef std::vector<std::vector<double > > TwoDimensionDoubleVec;
class RowItr;
class RowElementItr;
class ColItr;
class ColElementItr;
class Matrix {
  friend RowItr;
  friend RowElementItr;
  friend ColItr;
  friend ColElementItr;
 public:
  Matrix() = default;
  
  //create a matrix from a vector of vector of doubles
  //where each inner vector is a row of the matrix
  explicit Matrix(const std::vector<std::vector<double>>& mat);
  
  // create a matrix that is numRows X numCols where all elements are val
  Matrix(const double val, const int numRows, const int numCols); 
  Matrix(const Matrix& rhs) = default;

  int getNumRows() const;
  int getNumCols() const;

  Matrix& operator=(const Matrix& rhs);
  Matrix operator-() const; // negation. negate all elements of matric

  Matrix& operator+=(const Matrix& rhs); // matrix addition
  Matrix& operator+=(const double& rhs); //scalar addition

  Matrix operator+(const Matrix& rhs) const; // matrix addition
  Matrix operator+(const double& rhs) const; // scalar addition
  friend Matrix operator+(const double lhs, const Matrix& rhs); // scalar addition

  Matrix& operator-=(const Matrix& rhs); // matrix subtraction
  Matrix& operator-=(const double& rhs); // scalar subtraction

  Matrix operator-(const Matrix& rhs) const; //matrix subtraction
  Matrix operator-(const double& rhs) const; // scalar subtraction
  friend Matrix operator-(const double lhs, const Matrix& rhs); // scalar subtraction

  Matrix& operator*=(const Matrix& rhs); // matrix multiplication
  Matrix& operator*=(const double& rhs); // scalar multiplication

  Matrix operator*(const Matrix& rhs) const; //matrix multiplication
  Matrix operator*(const double& rhs) const; // scalar multiplication
  friend Matrix operator*(const double& lhs, const Matrix& rhs); // scalar multiplication

  RowItr operator [](int i); // get RowItr over row i

  friend std::ostream& operator<<(std::ostream& out,  const Matrix& mat);
  friend std::istream& operator>>(std::istream& in, Matrix& mat);

  RowItr rowBegin(); //get itr to first row
  RowItr rowEnd(); //get itr to one past last row

  ColItr colBegin(); // get itr to first column
  ColItr colEnd(); // get itr to one past last column

 private:
  TwoDimensionDoubleVec matrix;
};

#endif //MATRIX_MATRIX_H
