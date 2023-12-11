//
// Created by adish on 6/11/2023.
//
#ifndef ACTIVATION_H
#define ACTIVATION_H
#include "Matrix.h"

/**
 *  typedef of function pointer type.
 */
typedef Matrix (*ActivationFunc)(const Matrix&);

namespace activation {
    /**
      * Applies Relu function to the input.
      */
    Matrix relu(const Matrix& m);

    /**
     * Applies Softmax function to the input.
     */
    Matrix softmax(const Matrix& m);
    }
#endif //ACTIVATION_H