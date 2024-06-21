#include "s21_matrix_oop.h"

S21Matrix::S21Matrix() : rows_(0), cols_(0) {
  matrix_ = std::vector<std::vector<double>>(
      rows_, std::vector<double>(
                 cols_, 0.0));  // двумерный вектор, rows_ cтрок cодержит cols_
                                // эл-тов типа double cо значением 0.0
}

S21Matrix::S21Matrix(int rows, int cols) : rows_(rows), cols_(cols) {
  if (rows_ < 1 || cols_ < 1) {
    throw std::length_error("Matrix dimensions cannot be less than one");
  } else {
    matrix_.resize(rows_, std::vector<double>(cols_));
  }
}

S21Matrix::S21Matrix(const S21Matrix& other)
    : rows_(other.rows_), cols_(other.cols_) {
  matrix_ = std::vector<std::vector<double>>(rows_, std::vector<double>(cols_));
  matrix_.assign(other.matrix_.begin(), other.matrix_.end());
}

S21Matrix::S21Matrix(S21Matrix&& other) noexcept
    : rows_(other.rows_),
      cols_(other.cols_),
      matrix_(std::move(other.matrix_)) {
  other.rows_ = 0;
  other.cols_ = 0;
}
S21Matrix::~S21Matrix() {
}  // деcтруктор S21Matrix вызывает деcтруктор std::vector, std::vector
   // cамоcтоятельно удаляет вcе элементы из вектора и оcвобождает выделенную
   // память.

int S21Matrix::get_rows() const noexcept { return rows_; }

int S21Matrix::get_cols() const noexcept { return cols_; }

void S21Matrix::set_rows(const int new_rows) {
  if (new_rows < 1) {
    throw std::length_error("Number of rows cannot be less than one");
  } else {
    if (new_rows > rows_) {
      matrix_.resize(new_rows, std::vector<double>(cols_));
    } else {
      matrix_.resize(new_rows);
    }
    rows_ = new_rows;
  }
}

void S21Matrix::set_cols(const int new_cols) {
  if (new_cols < 1) {
    throw std::length_error("Number of cols cannot be less than one");
  } else {
    if (new_cols > cols_) {
      for (auto& row : matrix_) {  //  позволяет нам пройти по каждой cтроке row
                                   //  в векторе matrix_
        row.resize(new_cols, 0.0);
      }
    } else {
      for (auto& row : matrix_) {
        row.resize(new_cols);
      }
    }
    cols_ = new_cols;
  }
}

bool S21Matrix::eq_matrix(const S21Matrix& other) const noexcept {
  bool are_equal = true;
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    are_equal = false;
  }
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      if (std::fabs(matrix_[i][j] - other.matrix_[i][j]) > 1e-6) {
        are_equal = false;
        break;
      }
    }
    if (!are_equal) {
      break;
    }
  }
  return are_equal;
}

void S21Matrix::sum_matrix(const S21Matrix& other) {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw std::invalid_argument("Matrix sizes do not match for summation.");
  } else {
    for (int i = 0; i < rows_; ++i) {
      for (int j = 0; j < cols_; ++j) {
        matrix_[i][j] += other.matrix_[i][j];
      }
    }
  }
}

void S21Matrix::sub_matrix(const S21Matrix& other) {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw std::invalid_argument("Matrix sizes do not match for subtraction.");
  } else {
    for (int i = 0; i < rows_; ++i) {
      for (int j = 0; j < cols_; ++j) {
        matrix_[i][j] -= other.matrix_[i][j];
      }
    }
  }
}

void S21Matrix::mul_number(const double val) {  // nan
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      matrix_[i][j] *= val;
    }
  }
}

void S21Matrix::mul_matrix(const S21Matrix& other) {
  if (cols_ != other.rows_) {
    throw std::invalid_argument(
        "Matrix sizes do not match for multiplication.");
  } else {
    S21Matrix result(rows_, other.cols_);
    for (int i = 0; i < rows_; ++i) {
      for (int j = 0; j < other.cols_; ++j) {
        for (int k = 0; k < cols_; ++k) {
          result.matrix_[i][j] += matrix_[i][k] * other.matrix_[k][j];
        }
      }
    }
    rows_ = result.rows_;
    cols_ = result.cols_;
    matrix_ = result.matrix_;
  }
}

S21Matrix S21Matrix::transpose() noexcept {
  S21Matrix result(cols_, rows_);
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      result.matrix_[j][i] = matrix_[i][j];
    }
  }
  return result;
}

void S21Matrix::fill_minor_for_determinant(S21Matrix& minor, int x) {
  for (int i = 0; i < minor.get_rows(); ++i) {
    for (int j = 0; j < minor.get_cols(); ++j) {
      int tmp_j = (j >= x) ? 1 : 0;
      minor.matrix_[i][j] = matrix_[i + 1][j + tmp_j];
    }
  }
}

double S21Matrix::determinant() {
  if (rows_ != cols_) {
    throw std::invalid_argument(
        "determinant is defined only for square matrices.");
  }
  if (rows_ == 1) {
    return matrix_[0][0];
  }
  if (rows_ == 2) {
    return matrix_[0][0] * matrix_[1][1] - matrix_[0][1] * matrix_[1][0];
  }
  double det = 0.0;
  S21Matrix minor(rows_ - 1, cols_ - 1);
  for (int x = 0; x < cols_; ++x) {
    fill_minor_for_determinant(minor, x);
    double minor_det = minor.determinant();
    double sign = (x % 2 == 0) ? 1 : -1;
    det += matrix_[0][x] * minor_det * sign;
  }
  return det;
}

void S21Matrix::fill_minor_for_complement(S21Matrix& minor, int i,
                                          int j) const {
  int row = 0;
  for (int k = 0; k < rows_; ++k) {
    if (k == i) continue;
    int col = 0;
    for (int z = 0; z < cols_; ++z) {
      if (z == j) continue;
      minor.matrix_[row][col] = matrix_[k][z];
      ++col;
    }
    ++row;
  }
}

void S21Matrix::calc_complement_2x2_matrix(S21Matrix& result) const {
  S21Matrix minor(1, 1);
  for (int i = 0; i < 2; ++i) {
    for (int j = 0; j < 2; ++j) {
      double sign = (i + j) % 2 == 0 ? 1 : -1;
      fill_minor_for_complement(minor, i, j);
      double minor_det = minor.determinant();
      result.matrix_[i][j] = sign * minor_det;
    }
  }
}

S21Matrix S21Matrix::calc_complements() {
  S21Matrix tmp(*this);
  double det = tmp.determinant();
  if (det == 0) {
    throw std::invalid_argument(
        "Cannot calculate complements for a matrix with determinant 0.");
  }
  S21Matrix result(rows_, cols_);
  if (rows_ == 1 && cols_ == 1) {
    result.matrix_[0][0] = 1.0 / matrix_[0][0];
  } else if (rows_ == 2 && cols_ == 2) {
    calc_complement_2x2_matrix(result);
  } else if (rows_ >= 3 && cols_ >= 3) {
    S21Matrix minor(rows_ - 1, cols_ - 1);
    for (int i = 0; i < rows_; ++i) {
      for (int j = 0; j < cols_; ++j) {
        fill_minor_for_complement(minor, i, j);
        double minor_det = minor.determinant();
        double sign = ((i + j) % 2 == 0) ? 1 : -1;
        result.matrix_[i][j] = sign * minor_det;
      }
    }
  }

  return result;
}

S21Matrix S21Matrix::inverse_matrix() {
  S21Matrix result(*this);
  double det = result.determinant();
  if (det == 0) {
    throw std::invalid_argument(
        "Cannot calculate inverse for a matrix with determinant 0. 1");
  }
  S21Matrix alg_compl_matrix = result.calc_complements();

  S21Matrix transp_matrix = alg_compl_matrix.transpose();

  transp_matrix.mul_number(1.0 / det);
  return transp_matrix;
}

S21Matrix S21Matrix::operator+(const S21Matrix& other) const {
  S21Matrix result = *this;
  result.sum_matrix(other);
  return result;
}

S21Matrix S21Matrix::operator-(const S21Matrix& other) const {
  S21Matrix result = *this;
  result.sub_matrix(other);
  return result;
}

S21Matrix S21Matrix::operator*(const S21Matrix& other) const {
  S21Matrix result = *this;
  result.mul_matrix(other);
  return result;
}

S21Matrix S21Matrix::operator*(const double val) const {
  S21Matrix result = *this;
  result.mul_number(val);
  return result;
}

S21Matrix& S21Matrix::operator*=(const S21Matrix& other) {
  this->mul_matrix(other);
  return *this;
}

S21Matrix& S21Matrix::operator*=(const double val) {
  this->mul_number(val);
  return *this;
}

S21Matrix& S21Matrix::operator+=(const S21Matrix& other) {
  this->sum_matrix(other);
  return *this;
}

S21Matrix& S21Matrix::operator-=(const S21Matrix& other) {
  this->sub_matrix(other);
  return *this;
}

bool S21Matrix::operator==(const S21Matrix& other) const noexcept {
  return this->eq_matrix(other);
}

S21Matrix& S21Matrix::operator=(const S21Matrix& other) {
  rows_ = other.rows_;
  cols_ = other.cols_;
  matrix_ = other.matrix_;
  return *this;
}

double& S21Matrix::operator()(int i, int j) {
  if (i < 0 || i >= rows_ || j < 0 || j >= cols_) {
    throw std::out_of_range("Index out of bounds");
  }
  return matrix_[i][j];
}

std::vector<double>& S21Matrix::operator[](int i) {
  if (i < 0 || i >= rows_) {
    throw std::out_of_range("Index out of bounds");
  }
  return matrix_[i];
}
