//
// Created by mfbut on 3/1/2018.
//

#include "MatrixError.h"

const char* MatrixError::what() const noexcept {
  return errString.c_str();
}
