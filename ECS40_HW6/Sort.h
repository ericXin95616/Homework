//
// Created by xinbochao on 18-3-11.
//

#ifndef HW6_SORT_H
#define HW6_SORT_H

#include <vector>
#include <iostream>

template <typename T>
std::ostream& operator<<(std::ostream& os, std::vector<T> vec) {
  for(auto i = vec.begin(), end = vec.end(); i != end; ++i) {
    os << *i << " ";
  }
  return os;
}

template <typename T>
void sort(std::vector<T> &vec) {
  for(auto i = vec.begin(), end = vec.end(); i != end; ++i) {
    for (auto j = vec.begin(); j != end - 1; ++j) {
      if(*j > *(j + 1)) {
        T temp = *j;
        *j = *(j + 1);
        *(j + 1) = temp;
      }
    }
  }
}
#endif //HW6_SORT_H
