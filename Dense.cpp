//
// Created by adish on 6/11/2023.
//
#include "Dense.h"


Matrix Dense::get_weights () const
{
  return weights;
}


Matrix Dense::get_bias () const
{
  return bias;
}

ActivationFunc Dense::get_activation () const
{
  return activation;
}

void Dense::err_check_dense (int w_rows, int w_cols, int in_rows, int in_cols,
                             int bi_rows, int bi_cols)
{
  if (w_rows != bi_rows || in_cols != bi_cols || in_rows != w_cols)
  {
    throw std::length_error (LENGTH_ERROR_MSG);
  }
}

Matrix Dense::operator() (const Matrix &input) const
{
  int w_rows = weights.get_rows ();
  int w_cols = weights.get_cols ();
  int in_rows = input.get_rows ();
  int in_cols = input.get_cols ();
  int bi_rows = bias.get_rows ();
  int bi_cols = bias.get_cols ();
  err_check_dense (w_rows, w_cols, in_rows, in_cols, bi_rows, bi_cols);
  Matrix b = get_bias ();
  Matrix w = get_weights ();
  Matrix output_mat = (w * input) + b;
  output_mat = activation (output_mat);
  return output_mat;
}
