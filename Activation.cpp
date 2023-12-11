//
// Created by adish on 6/11/2023.
//
#include "Activation.h"

Matrix activation::relu (const Matrix &m)
{
  int mat_rows = m.get_rows ();
  int mat_cols = m.get_cols ();
  Matrix new_mat (mat_rows, mat_cols);
  int mult_dim = mat_rows * mat_cols;
  int i = 0;
  while (i < mult_dim)
  {
    if (m[i] < 0)
    {
      new_mat[i] = 0;
    }
    else
    {
      new_mat[i] = m[i];
    }
    i++;
  }
  return new_mat;
}

Matrix activation::softmax (const Matrix &m)
{
  Matrix softer (m);
  float sigma;
  int mult_dim = softer.get_rows () * softer.get_cols ();
  int i = 0;
  while (i < mult_dim)
  {
    softer[i] = expf (m[i]);
    i++;
  }
  sigma = softer.sum ();
  Matrix calculated = softer * (1 / sigma);
  return calculated;
}

