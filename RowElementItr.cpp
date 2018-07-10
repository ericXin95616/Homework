#include <sstream>
#include "RowElementItr.h"

RowElementItr::RowElementItr(RowItr& it, int index): it(&it), index(index),
                                                     lowerBound(0), upperBound(it.getColNum()) {}

double& RowElementItr::operator*() {
  if (*this) {
    return it->mat->matrix[it->index][this->index];
  } else {
    std::stringstream errorStream;
    errorStream << "RowElementItr dereferenced out of bounds. Acceptable values 0 -" << (upperBound - 1)
                << ". Current position: " << index;
    throw std::out_of_range(errorStream.str());
  }
}

RowElementItr& RowElementItr::operator++() {
  index++;
  return *this;
}

RowElementItr& RowElementItr::operator++(int) {
  return ++(*this);
}

RowElementItr& RowElementItr::operator--() {
  index--;
  return *this;
}

RowElementItr& RowElementItr::operator--(int) {
  return --(*this);
}

RowElementItr& RowElementItr::operator+=(const int& rhs) {
  index += rhs;
  return *this;
}

RowElementItr RowElementItr::operator+(const int& rhs) {
  RowElementItr copy(*this);
  copy += rhs;
  return copy;
}

RowElementItr& RowElementItr::operator-=(const int& rhs) {
  index -= rhs;
  return *this;
}

RowElementItr RowElementItr::operator-(const int& rhs) {
  RowElementItr copy(*this);
  copy -= rhs;
  return copy;
}

RowElementItr::operator bool() const {
  return index >= lowerBound && index < upperBound;
}

bool RowElementItr::operator!() const {
  return !static_cast<bool>(*this);
}

bool RowElementItr::operator==(const RowElementItr& rhs) const {
  if (!compatible(rhs)) {
    return false;
  } else if (!*this && !rhs) { // two iterators that are out of bounds
    return true; // are considered to be the same
  } else {
    return index == rhs.index;
  }
}

bool RowElementItr::operator!=(const RowElementItr& rhs) const {
  return !(*this == rhs);
}

bool RowElementItr::operator<(const RowElementItr& rhs) const {
  return compatible(rhs) && index < rhs.index;
}

bool RowElementItr::operator>(const RowElementItr& rhs) const {
  return compatible(rhs) && index > rhs.index;
}

bool RowElementItr::operator<=(const RowElementItr& rhs) const {
  return *this == rhs || *this < rhs;
}

bool RowElementItr::operator>=(const RowElementItr& rhs) const {
  return *this == rhs || *this > rhs;
}

// this function is used to judge whether these two
// iterator refers to the same matrix
bool RowElementItr::compatible(const RowElementItr& other) const {
  return this->it == other.it;
}


/*
void RowElementItr::replace(const std::vector<double>& newValues) {

  if (*this) {
    // TO DO: we need to check whether the size of new Values vector
    // and column number are agreed
    (mat->matrix).at(index) = newValues;
  } else {
    std::stringstream errorString;
    errorString << "Attempting to write to col " << index << " but matrix only has rows 0 - " << mat->getNumRows()
                << std::endl;
    throw std::range_error(errorString.str());
  }
}
*/
/*
RowElementItr RowElementItr::begin(){
  return RowElementItr(*it, 0);
}

RowElementItr RowItr::end(){
  return RowElementItr(*this, mat->getNumCols());
}

double& RowElementItr::operator[](int i) {
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
*/