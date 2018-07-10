//
// Created by mfbut on 3/1/2018.
//

#ifndef MATRIX_ROWELEMENTITR_H
#define MATRIX_ROWELEMENTITR_H

#include "RowItr.h"
class Matrix;
class RowItr;

class RowElementItr{
 public:

  RowElementItr(RowItr& it, int index);
  //get the element in this row we are pointing at
  double& operator*();

  //advance to next element in row
  RowElementItr& operator++(); // pre
  RowElementItr& operator++(int); // post

  //move to previous element in row
  RowElementItr& operator--(); // pre
  RowElementItr& operator--(int); // post

  RowElementItr& operator+=(const int& rhs); //move self rhs elements forward
  RowElementItr operator+(const int& rhs); //new iterator rhs elements past self

  RowElementItr& operator-=(const int& rhs); // move self rhs elements back
  RowElementItr operator-(const int& rhs); //new iterator rhs elements before self

  operator bool() const; // true if in bounds
  bool operator!() const; // true if out of bounds
  bool operator==(const RowElementItr& rhs) const; //referring to same matrix and (at same position or out of bounds)
  bool operator!=(const RowElementItr& rhs) const; // opposite of ==
  bool operator<(const RowElementItr& rhs) const; // referring to same matrix and before rhs
  bool operator>(const RowElementItr& rhs) const; // referring to same matrix and after rhs
  bool operator<=(const RowElementItr& rhs) const;
  bool operator>=(const RowElementItr& rhs) const;
  bool compatible(const RowElementItr& other) const;

 private:
  RowItr* it;
  int index;
  int lowerBound;
  int upperBound;
};

#endif //MATRIX_ROWELEMENTITR_H
