//
// Created by adish on 6/11/2023.
//
#include "Matrix.h"
#include <iostream>
#include <fstream>

void Matrix::err_check_constructor (int rows, int cols)
{
  if (rows <= 0 || cols <= 0)
  {
    exceptions_thrower (LENGTH_ERROR);
  }
}

Matrix::Matrix (int rows, int cols) : rows (rows), cols (cols)
{
  err_check_constructor (rows, cols);
  int num_of_vals = rows * cols;
  value = new float[num_of_vals] (); // Init to 0
}

Matrix::Matrix () : rows (1), cols (1)
{
  value = new float[1] (); // Init to 0
}

Matrix::Matrix (const Matrix &other) : rows (other.rows), cols (other.cols)
{
  int num_of_vals = rows * cols;
  value = new float[num_of_vals];
  for (int i = 0; i < num_of_vals; ++i)
  {
    value[i] = other.value[i];
  }
}

int Matrix::get_rows () const
{
  return static_cast<int>(rows);
}

int Matrix::get_cols () const
{
  return static_cast<int>(cols);
}

Matrix &Matrix::transpose ()
{
  Matrix new_mat(cols, rows);

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      new_mat(j, i) = (*this)(i, j);
    }
  }
  *this = new_mat;
  return *this;
}

Matrix &Matrix::vectorize ()
{
  int new_rows = rows * cols;
  int new_cols = 1;
  cols = new_cols;
  rows = new_rows;
  return *this;
}

void Matrix::plain_print () const
{
  for (int i = 0; i < rows; i++)
  {
    for (int j = 0; j < cols; j++)
    {
      int computed_ind = i * cols + j;
      std::cout << value[computed_ind] << ' ';
    }
    std::cout << '\n';
  }
}

Matrix Matrix::dot (const Matrix &m) const
{
  if (rows != m.rows || cols != m.cols)
  {
    exceptions_thrower (LENGTH_ERROR);
  }

  Matrix dot_prod (rows, cols);
  int i = 0;
  int j;
  while (i < rows)
  {
    j = 0;
    while (j < cols)
    {
      int ind_to_take = i * cols + j;
      dot_prod.value[ind_to_take] =
          value[ind_to_take] * m.value[ind_to_take];
      j++;
    }
    i++;
  }
  return dot_prod;
}

float Matrix::norm () const
{
  float sum_of_sq = 0;
  int i = 0;
  int j;
  while (i < rows)
  {
    j = 0;
    while (j < cols)
    {
      int computed_ind = i * cols + j;
      sum_of_sq += value[computed_ind] * value[computed_ind];
      j++;
    }
    i++;
  }
  return sqrt (sum_of_sq);
}

int Matrix::argmax () const
{
  int largest_as_ind = 0;
  float runner = value[0];
  int run_until = rows * cols;
  int i = 1;
  while (i < run_until)
  {
    if (value[i] > runner)
    {
      largest_as_ind = i;
      runner = value[i];
    }
    i++;
  }
  return largest_as_ind;
}

void Matrix::rows_swapper (Matrix &mat, int fst_r, int sec_r, int colser)
{
//  if (fst_r < 0 || fst_r >= mat.rows || sec_r < 0 || sec_r >= mat.rows)
//  {
//    exceptions_thrower (OUT_OF_RANGE_ERROR);
//  }

  int k = 0;
  while (k < colser)
  {
    int computed_f_ind = fst_r * colser + k;
    int computed_s_ind = sec_r * colser + k;
    std::swap (mat.value[computed_f_ind],
               mat.value[computed_s_ind]);
    k++;
  }
}

void Matrix::rows_scaler (Matrix &mat, int row, float scalar, int colser)
{
//  if (row < 0 || row >= mat.rows)
//  {
//    exceptions_thrower (OUT_OF_RANGE_ERROR);
//  }

  int k = 0;
  while (k < colser)
  {
    int computed_ind = row * colser + k;
    mat.value[computed_ind] /= scalar;
    k++;
  }
}

void Matrix::rows_elim (Matrix &mat, int r_pivot, int c_pivot, int colser)
{
//  if (r_pivot < 0 || r_pivot >= mat.rows || c_pivot < 0 || c_pivot >= colser)
//  {
//    exceptions_thrower (OUT_OF_RANGE_ERROR);
//  }

  int k = 0;
  while (k < colser)
  {
    if (k != r_pivot)
    {
      int computed_int_factor = k * colser + c_pivot;
      float factor = mat.value[computed_int_factor];
      int j = 0;
      while (j < colser)
      {
        int computed_ind_ded_from = k * colser + j;
        int computed_ind_to_ded = r_pivot * colser + j;
        mat.value[computed_ind_ded_from] -=
            factor * mat.value[computed_ind_to_ded];
        j++;
      }
    }
    k++;
  }
}

Matrix Matrix::rref () const
{
  int tracker = 0;
  Matrix cop_m = (*this);
  int rower = cop_m.rows;
  int colser = cop_m.cols;

  int runner = 0;
  while (runner < rower)
  {
    if (colser <= tracker)
    {
      break;
    }
    int j = runner;
    while (cop_m.value[tracker + colser * j] == 0)
    {
      j++;
      if (j == rower)
      {
        j = runner;
        tracker++;
        if (tracker == colser)
        {
          break;
        }
      }
    }
    int checker_for_copm = j * colser + tracker;
    if (cop_m.value[checker_for_copm] != 0)
    {
      if (j != runner)
      {
        rows_swapper (cop_m, j, runner, colser);
      }
      float runner_sc = cop_m.value[runner * colser + tracker];
      rows_scaler (cop_m, runner, runner_sc, colser);
      rows_elim (cop_m, runner, tracker, colser);
      tracker++;
    }
    runner++;
  }
  return cop_m;
}

void Matrix::err_check_add_operator (const Matrix &other) const
{
  if (rows != other.rows || cols != other.cols)
  {
    exceptions_thrower (LENGTH_ERROR);
  }
}

Matrix Matrix::operator+ (const Matrix &other) const
{
  err_check_add_operator (other);

  Matrix to_return (rows, cols);
  int k = 0;
  while (k < rows * cols)
  {
    to_return.value[k] = value[k] + other.value[k];
    k++;
  }
  return to_return;
}

Matrix &Matrix::operator= (const Matrix &mat)
{
  if (this == &mat)
  {
    return *this;
  }
  delete[] value;
  rows = mat.rows;
  cols = mat.cols;
  value = new float[rows * cols];
  std::copy (mat.value, mat.value + (rows * cols), value);

  return *this;
}

Matrix Matrix::operator* (const Matrix &m) const
{
  int num_of_rows_in_origin_mat = rows;
  int num_of_cols_in_origin_mat = cols;
  int num_of_cols_in_new_mat = m.cols;
  int num_of_rows_in_new_mat = m.rows;

  if (num_of_cols_in_origin_mat != num_of_rows_in_new_mat)
  {
    exceptions_thrower (LENGTH_ERROR);
  }

  Matrix multiplied_m (num_of_rows_in_origin_mat,
                       num_of_cols_in_new_mat);
  int i = 0, j = 0, k = 0;
  while (i < num_of_rows_in_origin_mat)
  {
    j = 0;
    while (j < num_of_cols_in_new_mat)
    {
      float summer = 0;
      k = 0;
      while (k < num_of_cols_in_origin_mat)
      {
        int computed_to_add_ind_orig = k + i * num_of_cols_in_origin_mat;
        int computed_to_add_ind_new = k * num_of_cols_in_new_mat + j;
        float to_add = value[computed_to_add_ind_orig]
                       * m.value[computed_to_add_ind_new];
        summer += to_add;
        k++;
      }
      int ind_for_runner_val = j + i * multiplied_m.cols;
      multiplied_m.value[ind_for_runner_val] = summer;
      j++;
    }
    i++;
  }
  return multiplied_m;
}

Matrix Matrix::operator* (float scalar) const
{
  Matrix scalar_prod_from_right (rows, cols);
  int rows_times_cols = rows * cols;

  for (int i = 0; i < rows_times_cols; i++)
  {
    scalar_prod_from_right.value[i] = value[i] * scalar;
  }
  return scalar_prod_from_right;
}

Matrix operator* (float scalar, const Matrix &m)
{
  Matrix scalar_prod_from_left (m.rows, m.cols);
  int m_rows_times_cols = m.rows * m.cols;

  for (int i = 0; i < m_rows_times_cols; i++)
  {
    scalar_prod_from_left.value[i] = scalar * m.value[i];
  }
  return scalar_prod_from_left;
}

void Matrix::err_check_para_operator (int row, int col) const
{
  if (!(row >= 0 && col >= 0 && row < rows && col < cols))
  {
    exceptions_thrower (OUT_OF_RANGE_ERROR);
  }
}

float &Matrix::operator() (int row, int col)
{
  err_check_para_operator (row, col);
  int ind = row * cols + col;
  return value[ind];
}

const float &Matrix::operator() (int row, int col) const
{
  err_check_para_operator (row, col);
  int ind = row * cols + col;
  return value[ind];
}

void Matrix::err_check_brackets_operator (int index) const
{
  if (index < 0 || rows * cols <= index)
  {
    return exceptions_thrower (OUT_OF_RANGE_ERROR);
  }
}

float &Matrix::operator[] (int index)
{
  err_check_brackets_operator (index);
  return value[index];
}

const float &Matrix::operator[] (int index) const
{
  err_check_brackets_operator (index);
  return value[index];
}

std::ostream &operator<< (std::ostream &os, const Matrix &m)
{
  for (int i = 0; i < m.rows; i++)
  {
    for (int j = 0; j < m.cols; j++)
    {
      if (m.value[i * m.cols + j] > MAGIC_ASTERISK)
      {
        os << DOUBLE_ASTERISK;
      }
      else
      {
        os << DOUBLE_SPACE;
      }
    }
    os << NEW_LINE;
  }
  return os;
}

void Matrix::err_check_istream_operator (std::ifstream &is, Matrix &m)
{
  if (!is.is_open ())
  {
    exceptions_thrower (RUNTIME_ERROR);
  }
  is.seekg (0, std::ios_base::end);
  long unsigned int l = is.tellg ();
  int all_en = m.cols * m.rows;
  if (l < all_en * sizeof (float))
  {
    is.close ();
    exceptions_thrower (RUNTIME_ERROR);
  }
  is.seekg (0, std::ios_base::beg);
  if (!is.read ((char *) (value), all_en * sizeof (float)))
  {
    exceptions_thrower (RUNTIME_ERROR);
  }
  is.seekg (0, std::ios_base::beg);
  if (!is)
  {
    exceptions_thrower (RUNTIME_ERROR);
  }
}

std::istream &operator>> (std::istream &is, Matrix &m)
{
  m.err_check_istream_operator (dynamic_cast<std::ifstream &>(is), m);
  return is;
}

float Matrix::sum () const
{
  float total = 0;
  int all_entries = rows * cols;
  int i = 0;
  while (i < all_entries)
  {
    total += value[i];
    i++;
  }
  return total;
}

Matrix &Matrix::operator+= (const Matrix &other)
{
  err_check_add_operator (other);
  int all_entries = rows * cols;
  int i = 0;
  while (i < all_entries)
  {
    value[i] += other.value[i];
    i++;
  }
  return *this;
}

void Matrix::exceptions_thrower (const std::string &type)
{
  if (type == OUT_OF_RANGE_ERROR)
  {
    throw std::out_of_range (OUT_OF_RANGE_ERROR_MSG);
  }
  else if (type == LENGTH_ERROR)
  {
    throw std::length_error (LENGTH_ERROR_MSG);
  }
  else if (type == RUNTIME_ERROR)
  {
    throw std::runtime_error (RUNTIME_ERROR_MSG);
  }
}

Matrix::~Matrix ()
{
  delete[] value;
}