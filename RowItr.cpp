//
// Created by mfbut on 3/1/2018.
//
#include <stdexcept>
#include <sstream>
#include "RowItr.h"

RowItr::RowItr(Matrix& mat, int start) : mat(&mat), index(start), lowerBound(0), upperBound(mat.getNumRows()){

}

RowElementItr RowItr::operator*() {
  if (*this) {
    return RowElementItr(*this, 0);
  } else {
    std::stringstream errorStream;
    errorStream << "RowItr dereferenced out of bounds. Acceptable values 0 -" << (upperBound - 1)
                << ". Current position: " << index;
    throw std::out_of_range(errorStream.str());
  }
}

RowItr& RowItr::operator++() {
  index++;
  return *this;
}

RowItr& RowItr::operator++(int) {
  return ++(*this);
}

RowItr& RowItr::operator--() {
  index--;
  return *this;
}

RowItr& RowItr::operator--(int) {
  return --(*this);
}

RowItr& RowItr::operator+=(const int& rhs) {
  index += rhs;
  return *this;
}

RowItr RowItr::operator+(const int& rhs) {
  RowItr copy(*this);
  copy += rhs;
  return copy;
}

RowItr& RowItr::operator-=(const int& rhs) {
  index -= rhs;
  return *this;
}

RowItr RowItr::operator-(const int& rhs) {
  RowItr copy(*this);
  copy -= rhs;
  return copy;
}

RowItr::operator bool() const {
  return index >= lowerBound && index < upperBound;
}

bool RowItr::operator!() const {
  return !static_cast<bool>(*this);
}

bool RowItr::operator==(const RowItr& rhs) const {
  if (!compatible(rhs)) {
    return false;
  } else if (!*this && !rhs) { // two iterators that are out of bounds
    return true; // are considered to be the same
  } else {
    return index == rhs.index;
  }
}

bool RowItr::operator!=(const RowItr& rhs) const {
  return !(*this == rhs);
}

bool RowItr::operator<(const RowItr& rhs) const {
  return compatible(rhs) && index < rhs.index;
}

bool RowItr::operator>(const RowItr& rhs) const {
  return compatible(rhs) && index > rhs.index;
}

bool RowItr::operator<=(const RowItr& rhs) const {
  return *this == rhs || *this < rhs;
}

bool RowItr::operator>=(const RowItr& rhs) const {
  return *this == rhs || *this > rhs;
}

// this function is used to judge whether these two
// iterator refers to the same matrix
bool RowItr::compatible(const RowItr& other) const {
  return this->mat == other.mat;
}


// replace the whole row
void RowItr::replace(const std::vector<double>& newValues) {

  if (*this) {
    // TO DO: we need to check whether the size of new Values vector
    // and column number are agreed
    (mat->matrix).at(index) = newValues;
  } else {
    std::stringstream errorString;
    errorString << "Attempting to write to row " << index << " but matrix only has rows 0 - " << mat->getNumRows() - 1
                << std::endl;
    throw std::range_error(errorString.str());
  }
}

RowElementItr RowItr::begin(){
  return RowElementItr(*this, 0);
}

RowElementItr RowItr::end(){
  return RowElementItr(*this, mat->getNumCols());
}

double& RowItr::operator[](int i) {
  if (*this) {
    RowElementItr rei = RowElementItr(*this, i);
    return *rei;
  } else {
    std::stringstream errorStream;
    errorStream << "RowItr dereferenced out of bounds. Acceptable values 0 -" << (upperBound - 1)
                << ". Current position: " << index;
    throw std::out_of_range(errorStream.str());
  }

}

int RowItr::getColNum() const {
  return mat->getNumCols();
}






