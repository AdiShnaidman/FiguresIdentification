//
// Created by adish on 6/11/2023.
//
#ifndef DENSE_H
#define DENSE_H

#include "Activation.h"
#include "Matrix.h"

class Dense
{
 private:
  Matrix weights;
  Matrix bias;
  ActivationFunc activation;

 public:
  /**
   * The public constructor for Dense.
   */
  Dense (const Matrix &weights, const Matrix &bias,
         ActivationFunc activationFunc)
      : weights (weights), bias (bias), activation (activationFunc)
  {}
  /**
    * Returns the weights matrix for dense layer.
    */
  Matrix get_weights () const;

  /**
    * Returns the bias matrix for dense layer
    */
  Matrix get_bias () const;

  /**
    * Returns the activation function used in the dense layer
    */
  ActivationFunc get_activation () const;

  /**
   * This function performs error checking for dimensions for matrix
   * multiplication.
   */
  Matrix operator() (const Matrix &input) const;

  /**
   * A helper function for operator()'s errors.
   */
  static void err_check_dense (int w_rows, int w_cols, int in_rows,
                               int in_cols, int bi_rows, int bi_cols);
};

#endif //DENSE_H
