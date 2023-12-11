#ifndef MATRIX_H
#define MATRIX_H
#include <iostream>
#include <cmath>
#define RUNTIME_ERROR "runtime_error"
#define RUNTIME_ERROR_MSG "Runtime error exception was thrown"
#define LENGTH_ERROR "length_error"
#define LENGTH_ERROR_MSG "Length error exception was thrown"
#define OUT_OF_RANGE_ERROR "out_of_range"
#define OUT_OF_RANGE_ERROR_MSG "Out of range exception was thrown"
#define INVALID_ARGUMENT "invalid_argument"
#define INVALID_ARGUMENT_MSG "Invalid argument exception was thrown"

#define DOUBLE_ASTERISK "**"
#define DOUBLE_SPACE "  "
#define NEW_LINE "\n"
#define MAGIC_ASTERISK 0.1
#include <stdexcept>

/**
 * @struct matrix_dims
 * @brief Matrix dimensions container. Used in MlpNetwork.h and main.cpp
 */
typedef struct matrix_dims
{
    int rows, cols;
} matrix_dims;

/**
 * Represents a 2D matrix.
 */
class Matrix
{
 private:
  int rows;
  int cols;
  float *value;

 public:
  /**
   *  Checks the validity of the matrix dimensions during matrix construction.
   *  Throws an Length Error exception if the rows or columns are less than or
   *  equal to 0.
   */
  static void err_check_constructor (int rows, int cols);

  /**
   * Constructor for matrix of given size. Elements are initialized to 0.
   * Throws invalid_argument if rows or cols is less than or equal to 0.
   */
  Matrix (int rows, int cols);

  /**
   * Default constructorfor a 1x1 matrix. element init to 0
   */
  Matrix ();

  /**
   * Copy constructor. Constructs a matrix from another matrix.
   **/
  Matrix (const Matrix &other);

  /**
   * Returns the number of rows in matrix.
   */
  int get_rows () const;

  /**
   * Returns the number of cols in matrix.
   */
  int get_cols () const;

  /**
   * Transposes matrix.
   */
  Matrix &transpose ();

  /**
   * Transforms matrix into column vector. Returns reference to vectorized mat.
   */
  Matrix &vectorize ();

  /**
   * Prints the matrix elements.
   */
  void plain_print () const;

  /**
  * Element-wise multiplication with second matrix.
  * Throws invalid_argument if the dimensions of the matrices do not fit.
  */
  Matrix dot (const Matrix &m) const;

  /**
   * Returns the Frobenius norm of matr.
   */
  float norm () const;

  /**
   * Returns the index of the largest number in the matrix.
   */
  int argmax () const;

  /**
   * Swaps rows for rref.
   */
  static void rows_swapper (Matrix &m, int row1, int row2, int colser);

  /**
   * Scales rows for rref.
   */
  static void rows_scaler (Matrix &m, int row, float scalar, int colser);

  /**
   * Scales rows for rref.
   */
  static void rows_elim (Matrix &m, int pivotRow, int pivotCol, int colser);

  /**
   * Computes the reduced row echelon form (rref) of the matrix.
   */
  Matrix rref () const;

  /**
   * Overloads matrix addition operator.
   */
  Matrix operator+ (const Matrix &m) const;

  /**
   * Checks for length error for addition operation.
   */
  void err_check_add_operator (const Matrix &other) const;

  /**
   * Overloads assignment operator.
   */
  Matrix &operator= (const Matrix &m);

  /**
   * Overloads matrix multiplication operator
   */
  Matrix operator* (const Matrix &m) const;

  /**
   * Overloads scalar multiplication on right operator
   */
  Matrix operator* (float scalar) const;

  /**
    * Overloads scalar multiplication on left operator
    */
  friend Matrix operator* (float scalar, const Matrix &m);

  /**
   * Checks the validity of the row and column for parenthesis indexing
   */
  void err_check_para_operator (int row, int col) const;

  /**
    * Returns a reference to the element at the specified row and column
    */
  float &operator() (int row, int col);

  /**
   * Returns a const reference to the element at the specified row and column
   */
  const float &operator() (int row, int col) const;

  /**
   * Checks the validity of the index for bracket indexing
   */
  void err_check_brackets_operator (int index) const;

  /**
    * Returns a reference to the element at the specified index
    */
  float &operator[] (int index);

  /**
    * Returns a const reference to the element at the specified index
    */
  const float &operator[] (int index) const;

  /**
    * Overloads the ostream operator to enable the printing of matrix
    */
  friend std::ostream &operator<< (std::ostream &os, const Matrix &m);

  /**
    * Checks the validity of the input stream and fills the matrix elements
    */
  void err_check_istream_operator(std::ifstream& is, Matrix& m);
  /**
    * Overloads the istream operator to enable the reading of elements
    */
  friend std::istream &operator>> (std::istream &is, Matrix &m);

  /**
    * Throws an exception of the specified type
    */
  static void exceptions_thrower (const std::string &type);

  /**
   * This function calculates and returns the sum of all elements in the
   * matrix.
   */
  float sum() const;

  /**
   * This function overloads the "+=" operator for the Matrix class,
   * allowing the addition of another matrix to the current matrix. It first
   * checks for validity by calling the err_check_add_operator function.
   */
  Matrix& operator+=(const Matrix& other);

  /**
   * Destructor for matrix.
   */
  ~Matrix ();
};

#endif //MATRIX_H