//
// Created by xinbochao on 18-3-3.
//

#include <iostream>
#include "Matrix.h"
#include <vector>
#include <fstream>

using std::cout;
using std::endl;
using std::cin;
using std::vector;

typedef vector<vector<double > > doubleVecOf2D;

int main() {
  Matrix m1({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}, {10, 11, 12}});

  for (ColItr citr = m1.colBegin(); citr != m1.colEnd(); ++citr) {
    for (ColElementItr elementItr = citr.begin(); elementItr != citr.end(); ++elementItr) {
      std::cout << *elementItr << ' ';
    }
    std::cout << std::endl;
  }

  return 0;
}
/*
int main(){
  // three different ways to construct matrix
  Matrix a(5, 3, 3);
  Matrix b(1, 5, 5);
  Matrix c = b;

  int row, col;
  cout << "Please enter the number of row and col" << endl;
  cin >> row >> col;
  double temp = 0.0;

  // testing Matrix(std::vector<std::vector<double>>)
  doubleVecOf2D vec;
  for(int i = 0; i < row; ++i) {
    vector<double > vecTemp;
    for (int j = 0; j < col; ++j) {
      cout << "Please enter the value in (" << i << ", " << j << ") : ";
      cin >> temp;
      vecTemp.push_back(temp);
    }
    vec.push_back(vecTemp);
  }
  Matrix d(vec);

  // test matrix input
  // cin >> a;
  // output matrix
  std::ifstream in("readMatrix.txt");
  if(in)
    in >> a;
  else
    cout << "Fail to open that file" << endl;

  cout << a;
  cout << b << c << d << endl;

  // binary operator test
  cout << b + c  << endl;
  cout << b - c << endl;
  cout << b * c << endl;

  // scalar operator test
  cout << 10 * a << endl;
  cout << a * 10 << endl;
  cout << d + 10 << endl;
  cout << 10 + d << endl;
  cout << d - 10 << endl;
  cout << 10 - d << endl;

  // iterator test
  for (auto k = a.rowBegin(), end = a.rowEnd(); k != end ; ++k) {
    for (int i = 0; i < a.getNumCols(); ++i) {
      cout << k[i] << " ";
    }
    cout << endl;
  }

  for (auto i = a.colBegin(), colend = a.colEnd(); i != colend ; ++i) {
    for (int j = 0; j < a.getNumRows(); ++j) {
      cout << i[j] << " ";
    }
    cout << endl;
  }

  // exception test
  // Matrix Size Error
  //cout << "Matrix Size Error test\nPlease enter a matrix that has different numbers of column" << endl;
  //cin >> a;
  //cout << "Will it change the original content in Matrix a?" << endl;
  //cout << a;
  // Matrix Size Mismatch Error
  cout << "Matrix Size Mismatch Error test" << endl;
  Matrix e(1, 5, 5);
  Matrix f(10, 3, 5);
  cout << "Matrix e is:";
  cout << e << endl;
  cout << "Matrix f is:";
  cout << f << endl;
  cout << "Matrix e + f is:";
  cout << e + f << endl;
  // Matrix Inner Dimension Mismatch Error test
  cout << "Matrix Inner Dimension Mismatch Error test" << endl;
  Matrix e1(1, 5, 5);
  Matrix f1(10, 3, 5);
  cout << "Matrix e is:";
  cout << e << endl;
  cout << "Matrix f is:";
  cout << f << endl;
  cout << "Matrix f * e is:";
  cout << e*f << endl;
  cout << "Matrix e * f is:";
  cout << f*e << endl;
}
*/