#ifndef S21MATRIX_H
#define S21MATRIX_H

#include <cmath>
#include <iostream>
#include <stdexcept>
#include <vector>

class S21Matrix {
 private:
  int rows_;
  int cols_;
  std::vector<std::vector<double>> matrix_;

 public:
  S21Matrix();
  S21Matrix(int rows, int cols);
  S21Matrix(const S21Matrix& other);
  S21Matrix(S21Matrix&& other) noexcept;
  ~S21Matrix();

  int get_rows() const noexcept;
  int get_cols() const noexcept;

  void set_rows(const int rows);
  void set_cols(const int cols);

  bool eq_matrix(const S21Matrix& other) const noexcept;
  void sum_matrix(const S21Matrix& other);
  void sub_matrix(const S21Matrix& other);
  void mul_number(const double val);
  void mul_matrix(const S21Matrix& other);
  S21Matrix transpose() noexcept;

  void fill_minor_for_determinant(S21Matrix& minor, int x);
  double determinant();

  void fill_minor_for_complement(S21Matrix& minor, int i, int j) const;
  void calc_complement_2x2_matrix(S21Matrix& result) const;
  S21Matrix calc_complements();

  S21Matrix inverse_matrix();

  S21Matrix operator+(const S21Matrix& other) const;
  S21Matrix operator-(const S21Matrix& other) const;
  S21Matrix operator*(const S21Matrix& other) const;
  S21Matrix operator*(const double val) const;
  S21Matrix& operator*=(const S21Matrix& other);
  S21Matrix& operator*=(const double val);
  S21Matrix& operator+=(const S21Matrix& other);
  S21Matrix& operator-=(const S21Matrix& other);
  bool operator==(const S21Matrix& other) const noexcept;
  S21Matrix& operator=(const S21Matrix& other);
  double& operator()(int i, int j);
  std::vector<double>& operator[](int i);
};

#endif  // S21MATRIX_H
