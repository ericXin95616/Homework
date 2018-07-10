//
// Created by mfbut on 3/2/2018.
//

#ifndef MATRIX_COLITR_H
#define MATRIX_COLITR_H


#include "Matrix.h"
#include "ColElementItr.h"

class ColItr {
  friend ColElementItr;
 public:

  ColItr(Matrix& mat, int start);
  ColElementItr operator* ();//get iterator over this column

  //advance one column
  ColItr& operator++(); // pre
  ColItr& operator++(int); // post

  //move back one column
  ColItr& operator--(); // pre
  ColItr& operator--(int); // post

  ColItr& operator+=(const int& rhs); //advance self rhs columns
  ColItr operator+(const int& rhs); //new iterator rhs columns past self

  ColItr& operator-=(const int& rhs); // move self back rhs columns
  ColItr operator-(const int& rhs); // new iterator rhs columns before self

  operator bool() const; //true if still in bounds
  bool operator!() const; // true if out of bounds
  bool operator==(const ColItr& rhs) const; //referring to same matrix and (at same position or out of bounds)
  bool operator!=(const ColItr& rhs) const; // opposite of ==
  bool operator<(const ColItr& rhs) const; //referring to same matrix and before rhs
  bool operator>(const ColItr& rhs) const; // referring to same matrix and after rhs
  bool operator<=(const ColItr& rhs) const;
  bool operator>=(const ColItr& rhs) const;
  bool compatible(const ColItr& other) const;
  void replace(const std::vector<double>& newValues);
  ColElementItr begin();
  ColElementItr end();
  double& operator[](int i); //get the ith element in this column

  int getRowNum() const;
 private:
  Matrix* mat;
  int index;
  int lowerBound;
  int upperBound;
};

#endif //MATRIX_COLITR_H
