//
// Created by mfbut on 3/2/2018.
//

#ifndef MATRIX_COLELEMENTITR_H
#define MATRIX_COLELEMENTITR_H

#include "ColItr.h"
class Matrix;
class ColItr;

class ColElementItr{
 public:
  ColElementItr(ColItr& it, int start);
  //get the current element in the column we are referring to
  double& operator*();

  //move one element forward
  ColElementItr& operator++(); // pre
  ColElementItr& operator++(int); // post

  //move one element back
  ColElementItr& operator--(); // pre
  ColElementItr& operator--(int); // post

  ColElementItr& operator+=(const int& rhs); //move self rhs elements forward
  ColElementItr operator+(const int& rhs); // new iterator rhs elements after self

  ColElementItr& operator-=(const int& rhs); //move self rhs elements backward
  ColElementItr operator-(const int& rhs); //new iterator rhs elements before self

  operator bool() const; //true if in bounds
  bool operator!() const; //ture if out of bounds
  bool operator==(const ColElementItr& rhs) const; //referring to same matrix and (at same position or out of bounds)
  bool operator!=(const ColElementItr& rhs) const; //opposite of ==
  bool operator<(const ColElementItr& rhs) const; // referring to same matrix and before rhs
  bool operator>(const ColElementItr& rhs) const; //referring to same matrix and after rhs
  bool operator<=(const ColElementItr& rhs) const;
  bool operator>=(const ColElementItr& rhs) const;

  bool compatible(const ColElementItr& other) const;
 private:
  ColItr* it;
  int index;
  int lowerBound;
  int upperBound;
};


#endif //MATRIX_COLELEMENTITR_H
