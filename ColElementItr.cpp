#include <sstream>
#include "ColElementItr.h"

ColElementItr::ColElementItr(ColItr& _it, int index): it(&_it), index(index),
                                                     lowerBound(0), upperBound(_it.getRowNum()) {}

double& ColElementItr::operator*() {
  if (*this) {
    return it->mat->matrix[this->index][it->index];
  } else {
    std::stringstream errorStream;
    errorStream << "ColElementItr dereferenced out of bounds. Acceptable values 0 -" << (upperBound - 1)
                << ". Current position: " << index;
    throw std::out_of_range(errorStream.str());
  }
}

ColElementItr& ColElementItr::operator++() {
  index++;
  return *this;
}

ColElementItr& ColElementItr::operator++(int) {
  return ++(*this);
}

ColElementItr& ColElementItr::operator--() {
  index--;
  return *this;
}

ColElementItr& ColElementItr::operator--(int) {
  return --(*this);
}

ColElementItr& ColElementItr::operator+=(const int& rhs) {
  index += rhs;
  return *this;
}

ColElementItr ColElementItr::operator+(const int& rhs) {
  ColElementItr copy(*this);
  copy += rhs;
  return copy;
}

ColElementItr& ColElementItr::operator-=(const int& rhs) {
  index -= rhs;
  return *this;
}

ColElementItr ColElementItr::operator-(const int& rhs) {
  ColElementItr copy(*this);
  copy -= rhs;
  return copy;
}

ColElementItr::operator bool() const {
  return index >= lowerBound && index < upperBound;
}

bool ColElementItr::operator!() const {
  return !static_cast<bool>(*this);
}

bool ColElementItr::operator==(const ColElementItr& rhs) const {
  if (!compatible(rhs)) {
    return false;
  } else if (!*this && !rhs) { // two iterators that are out of bounds
    return true; // are considered to be the same
  } else {
    return index == rhs.index;
  }
}

bool ColElementItr::operator!=(const ColElementItr& rhs) const {
  return !(*this == rhs);
}

bool ColElementItr::operator<(const ColElementItr& rhs) const {
  return compatible(rhs) && index < rhs.index;
}

bool ColElementItr::operator>(const ColElementItr& rhs) const {
  return compatible(rhs) && index > rhs.index;
}

bool ColElementItr::operator<=(const ColElementItr& rhs) const {
  return *this == rhs || *this < rhs;
}

bool ColElementItr::operator>=(const ColElementItr& rhs) const {
  return *this == rhs || *this > rhs;
}

// this function is used to judge whether these two
// iterator refers to the same matrix
bool ColElementItr::compatible(const ColElementItr& other) const {
  return this->it == other.it;
}
