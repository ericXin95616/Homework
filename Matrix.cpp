#include "Matrix.h"
#include <string>
#include <sstream>

Matrix::Matrix(const std::vector<std::vector<double>> &mat) {
  // TO DO: throw Matrix Size Error Exception
  // if these vector's size do not agree
  if(mat.empty())
    return;
  size_t prev = mat.at(0).size();
  for (unsigned int i = 0; i < mat.size(); ++i) {
    if(mat.at(i).size() != prev) {
      std::stringstream errString;
      errString << "All rows of the matrix should have the same number of elements. "
                << "Expected rows to contain " << prev << " elements but found row "
                << "that contained " << mat.at(i).size() <<" elements.";
      throw MatrixSizeError(errString.str());
    }
  }

  matrix = mat;
}

Matrix::Matrix(const double val, const int numRows, const int numCols) {
  std::vector<double> temp(numCols, val);
  for (int i = 0; i < numRows; ++i) {
    matrix.push_back(temp);
  }
}

int Matrix::getNumRows() const {
  return matrix.size();
}

int Matrix::getNumCols() const {
  return matrix.at(0).size();
}

Matrix& Matrix::operator=(const Matrix &rhs) {
  matrix = rhs.matrix;
  return *this;
}

Matrix Matrix::operator-() const {
  Matrix temp(*this);
  for (int i = 0; i < temp.getNumRows(); ++i) {
    for (int j = 0; j < temp.getNumCols(); ++j) {
      temp.matrix[i][j] = -temp.matrix[i][j];
    }
  }
  return temp;
}

Matrix Matrix::operator+(const double &rhs) const {
  Matrix temp(*this);
  for (int i = 0; i < temp.getNumRows(); ++i) {
    for (int j = 0; j < temp.getNumCols(); ++j) {
      temp.matrix[i][j] += rhs;
    }
  }
  return temp;
}

Matrix Matrix::operator+(const Matrix &rhs) const {
  // TO DO: if rhs.matrix and this->matrix's size
  // does not agree, we throw MatrixSizeMismatchError
  if(this->getNumRows() != rhs.getNumRows() || this->getNumCols() != rhs.getNumCols()) {
    std::stringstream errString;
    errString << "  Matrices must be the same size but Matrix1 is " << this->getNumRows() << " X " << this->getNumCols()
              << " and Matrix2 is " << rhs.getNumRows() << " X " << rhs.getNumCols();
    throw MatrixSizeMismatchError(errString.str());
  }

  Matrix temp(*this);
  for (int i = 0; i < temp.getNumRows(); ++i) {
    for (int j = 0; j < temp.getNumCols(); ++j) {
      temp.matrix[i][j] += rhs.matrix[i][j];
    }
  }
  return temp;
}

Matrix operator+(const double lhs, const Matrix &rhs) {
  return rhs + lhs;
}

Matrix& Matrix::operator+=(const double &rhs) {
  return *this = *this + rhs;
}

Matrix& Matrix::operator+=(const Matrix &rhs) {
  // operator + will help us check whether their size
  // are agreed
  return *this = *this + rhs;
}

Matrix Matrix::operator-(const double &rhs) const {
  return *this + (-rhs);
}

Matrix Matrix::operator-(const Matrix &rhs) const {
  // operator + will help us check whether their size
  // are agreed
  return *this + (-rhs);
}

Matrix operator-(const double lhs, const Matrix &rhs) {
  return -rhs + lhs;
}

Matrix& Matrix::operator-=(const double &rhs) {
  *this = *this - rhs;
  return *this;
}

Matrix& Matrix::operator-=(const Matrix &rhs) {
  // operator + will help us check whether their size
  // are agreed
  *this = *this - rhs;
  return *this;
}

Matrix Matrix::operator*(const Matrix &rhs) const {
  // TO DO: check whether their inner dimensions are agreed
  // if not we throw MatrixInnerDimensionMismatchError
  if(this->getNumCols() != rhs.getNumRows()) {
    std::stringstream errString;
    errString << "Inner dimensions do not agree. "
              << "First matrix has " << this->getNumCols() << " columns "
              << "but second matrix has " << rhs.getNumRows() << " rows.";
    throw MatrixInnerDimensionMismatchError(errString.str());
  }

  TwoDimensionDoubleVec temp(this->getNumRows(), std::vector<double >(rhs.getNumCols(), 0));
  int innerDimension = this->getNumCols();
  for (int i = 0; i < this->getNumRows(); ++i) {
    for (int j = 0; j < rhs.getNumCols(); ++j) {
      double sum = 0.0;
      for (int k = 0; k < innerDimension; ++k) {
        sum += matrix[i][k]*rhs.matrix[k][j];
      }
      temp[i][j] = sum;
    }
  }
  return Matrix(temp);
}

Matrix Matrix::operator*(const double &rhs) const {
  Matrix temp(*this);
  for (int i = 0; i < getNumRows(); ++i) {
    for (int j = 0; j < getNumCols(); ++j) {
      temp.matrix[i][j] *= rhs;
    }
  }
  return temp;
}

Matrix operator*(const double &lhs, const Matrix &rhs) {
  return rhs * lhs;
}

Matrix& Matrix::operator*=(const double &rhs) {
  return *this = (*this) * rhs;
}

Matrix& Matrix::operator*=(const Matrix &rhs) {
  // operator * will help us to check whether
  // their size are agreed or not
  return *this = (*this) * rhs;
}

std::ostream& operator<<(std::ostream &out, const Matrix &mat) {
  for (int i = 0; i < mat.getNumRows(); ++i) {
    for (int j = 0; j < mat.getNumCols(); ++j) {
      out << mat.matrix[i][j] << " ";
    }
    out << std::endl;
  }
  return out;
}

/*
 * did not know how to write this function
 */
std::istream& operator>>(std::istream &in, Matrix &mat) {
  TwoDimensionDoubleVec newMatrix;
  std::vector<double> vecTemp;
  int row = 0, col = 0;
  in >> row >> col;
  double temp = 0.0;
  for (int i = 0; i < row; ++i) {
    for (int j = 0; j < col; ++j) {
      in >> temp;
      vecTemp.push_back(temp);
    }
    newMatrix.push_back(vecTemp);
    vecTemp.clear();
  }
  // we use copy constructor here
  // because I want the constructor help me
  // to check whether this new matrix's col
  // length are agreed
  mat = Matrix(newMatrix);
  return in;
}

RowItr Matrix::rowBegin() {
  return RowItr(*this, 0);
}

RowItr Matrix::rowEnd() {
  return RowItr(*this, this->getNumRows());
}

ColItr Matrix::colBegin() {
  return ColItr(*this, 0);
}

ColItr Matrix::colEnd() {
  return ColItr(*this, this->getNumCols());
}

RowItr Matrix::operator[](int i) {
  return RowItr(*this, i);
}