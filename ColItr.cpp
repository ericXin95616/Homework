#include <sstream>
#include "ColItr.h"

ColItr::ColItr(Matrix &mat, int start): mat(&mat), index(start),
                                        lowerBound(0), upperBound(mat.getNumCols()) {}

ColElementItr ColItr::operator* () {
  if (*this) {
    return ColElementItr(*this, 0);
  } else {
    std::stringstream errorStream;
    errorStream << "RowItr dereferenced out of bounds. Acceptable values 0 -" << (upperBound - 1)
                << ". Current position: " << index;
    throw std::out_of_range(errorStream.str());
  }
}
//advance one column
ColItr& ColItr::operator++() {
  ++index;
  return *this;
}

ColItr& ColItr::operator++(int) {
  return ++(*this);
}

//move back one column
ColItr& ColItr::operator--() {
  --index;
  return *this;
}
ColItr& ColItr::operator--(int) {
  return --(*this);
}

ColItr& ColItr::operator+=(const int& rhs) {
  index += rhs;
  return *this;
}

ColItr ColItr::operator+(const int& rhs) {
  ColItr copy(*this);
  return copy += rhs;
}

ColItr& ColItr::operator-=(const int& rhs) {
  index -= rhs;
  return *this;
}

ColItr ColItr::operator-(const int& rhs) {
  ColItr copy(*this);
  return copy -= rhs;
}

ColItr::operator bool() const {
  return index >= lowerBound && index < upperBound;
}

bool ColItr::operator!() const {
  return static_cast<bool>(*this);
}

bool ColItr::operator==(const ColItr& rhs) const {
  if (!compatible(rhs)) {
    return false;
  } else if (!*this && !rhs) { // two iterators that are out of bounds
    return true; // are considered to be the same
  } else {
    return index == rhs.index;
  }
}

bool ColItr::operator!=(const ColItr& rhs) const {
  return !(*this == rhs);
}

bool ColItr::operator<(const ColItr& rhs) const {
  return compatible(rhs) && index < rhs.index;
}

bool ColItr::operator>(const ColItr& rhs) const {
  return compatible(rhs) && index > rhs.index;
}

bool ColItr::operator<=(const ColItr& rhs) const {
  return *this == rhs || *this < rhs;
}

bool ColItr::operator>=(const ColItr& rhs) const {
  return *this == rhs || *this > rhs;
}

// this function is used to judge whether these two
// iterator refers to the same matrix
bool ColItr::compatible(const ColItr& other) const {
  return this->mat == other.mat;
}


// replace the whole col
void ColItr::replace(const std::vector<double>& newValues) {

  if (*this) {
    // TO DO: we need to check whether the size of new Values vector
    // and row number are agreed
    for (int i = 0; i < mat->getNumRows(); ++i) {
      mat->matrix[i][index] = newValues.at(i);
    }
  } else {
    std::stringstream errorString;
    errorString << "Attempting to write to col " << index << " but matrix only has cols 0 - " << mat->getNumRows() - 1
                << std::endl;
    throw std::range_error(errorString.str());
  }
}

ColElementItr ColItr::begin(){
  return ColElementItr(*this, 0);
}

ColElementItr ColItr::end(){
  return ColElementItr(*this, mat->getNumRows());
}

double& ColItr::operator[](int i) {
  if (*this) {
    ColElementItr col(*this, i);
    return *col;
  } else {
    std::stringstream errorStream;
    errorStream << "ColItr dereferenced out of bounds. Acceptable values 0 -" << (upperBound - 1)
                << ". Current position: " << index;
    throw std::out_of_range(errorStream.str());
  }

}

int ColItr::getRowNum() const {
  return mat->getNumRows();
}