#include <gtest/gtest.h>

#include "s21_matrix_oop.h"

TEST(test_class, default_constructor) {
  S21Matrix m;
  EXPECT_EQ(m.get_cols(), 0);
  EXPECT_EQ(m.get_rows(), 0);
}

TEST(test_class, element_access_empty_matrix) {
  S21Matrix m;
  // Попытка доступа к элементам пустой матрицы должна вызывать исключение
  EXPECT_ANY_THROW(m(0, 0));
}

TEST(test_class, constructor_params) {
  S21Matrix m(21, 130);
  EXPECT_EQ(m.get_rows(), 21);
  EXPECT_EQ(m.get_cols(), 130);
}

TEST(test_class, negative_rows_cols) {
  EXPECT_ANY_THROW({ S21Matrix m(-1, 5); });
  EXPECT_ANY_THROW({ S21Matrix m(5, -1); });
  EXPECT_ANY_THROW({ S21Matrix m(-1, -1); });
}

TEST(test_class, zero_rows_cols) {
  EXPECT_ANY_THROW({ S21Matrix m(0, 5); });
  EXPECT_ANY_THROW({ S21Matrix m(5, 0); });
  EXPECT_ANY_THROW({ S21Matrix m(0, 0); });
}

TEST(test_class, constructor_invalid_params) {
  EXPECT_ANY_THROW(S21Matrix(0, 10));
  EXPECT_ANY_THROW(S21Matrix(10, 0));
  EXPECT_ANY_THROW(S21Matrix(-1, 5));
  EXPECT_ANY_THROW(S21Matrix(5, -1));
}

TEST(test_class, copy_constructor) {
  S21Matrix m(5, 5);
  S21Matrix copy(m);
  EXPECT_EQ(copy.get_cols(), 5);
  EXPECT_EQ(copy.get_rows(), 5);
}

TEST(test_class, move_constructor) {
  S21Matrix m(5, 5);
  S21Matrix moved(std::move(m));
  EXPECT_EQ(m.get_rows(), 0);
  EXPECT_EQ(m.get_cols(), 0);
  EXPECT_EQ(moved.get_rows(), 5);
  EXPECT_EQ(moved.get_cols(), 5);
}

TEST(test_setter, set_rows_increment) {
  S21Matrix m(2, 2);
  m[1][1] = 3.5;
  m.set_rows(10);
  EXPECT_EQ(m.get_rows(), 10);
  EXPECT_EQ(m[1][1], 3.5);
}

TEST(test_setter, set_rows_reduction) {
  S21Matrix m(3, 3);
  m[0][0] = 3.5;
  m.set_rows(1);
  EXPECT_EQ(m.get_rows(), 1);
  EXPECT_EQ(m[0][0], 3.5);
}

TEST(test_setter, set_rows_zero) {
  S21Matrix m;
  EXPECT_ANY_THROW(m.set_rows(0));
}

TEST(test_setter, set_rows_negative) {
  S21Matrix m;
  EXPECT_ANY_THROW(m.set_rows(-1));
}

TEST(test_setter, set_cols_increment) {
  S21Matrix m(2, 2);
  m[1][1] = 3.5;
  m.set_cols(10);
  EXPECT_EQ(m.get_cols(), 10);
  EXPECT_EQ(m[1][1], 3.5);
}

TEST(test_setter, set_cols_reduction) {
  S21Matrix m(3, 3);
  m[0][0] = 3.5;
  m.set_cols(1);
  EXPECT_EQ(m.get_cols(), 1);
  EXPECT_EQ(m[0][0], 3.5);
}

TEST(test_setter, set_cols_zero) {
  S21Matrix m;
  EXPECT_ANY_THROW(m.set_cols(0));
}

TEST(test_setter, set_cols_negative) {
  S21Matrix m;
  EXPECT_ANY_THROW(m.set_cols(-1));
}

TEST(test_functional, eq_matrix) {
  S21Matrix m(5, 5);
  S21Matrix m1(5, 5);
  ASSERT_TRUE(m.eq_matrix(m1));
}

TEST(test_functional, eq_matrix_different) {
  S21Matrix m(2, 2);
  S21Matrix m1(2, 2);
  m(0, 0) = 1.;
  m(0, 1) = 1.;
  m(1, 0) = 1.;
  m(1, 1) = 1.;
  m1(0, 0) = 1.;
  m1(0, 1) = 2.;
  m1(1, 0) = 1.;
  m1(1, 1) = 1.;
  ASSERT_FALSE(m.eq_matrix(m1));
}

TEST(test_functional, no_eq_matrix) {
  S21Matrix m(2, 5);
  S21Matrix m1(5, 5);
  ASSERT_FALSE(m.eq_matrix(m1));
}

TEST(test_functional, no_eq_matrix1) {
  S21Matrix m(5, 2);
  S21Matrix m1(5, 5);
  ASSERT_FALSE(m.eq_matrix(m1));
}

TEST(test_functional, sum_matrix) {
  S21Matrix m(2, 2);
  S21Matrix m1(2, 2);
  m(0, 0) = 1.;
  m(0, 1) = 1.;
  m(1, 0) = 1.;
  m(1, 1) = 1.;
  m1(0, 0) = 1.;
  m1(0, 1) = 1.;
  m1(1, 0) = 1.;
  m1(1, 1) = 1.;
  m.sum_matrix(m1);
  EXPECT_EQ(m(0, 0), 2.);
  EXPECT_EQ(m(0, 1), 2.);
  EXPECT_EQ(m(1, 0), 2.);
  EXPECT_EQ(m(1, 1), 2.);
}

TEST(test_functional, sum_matrix_exception) {
  S21Matrix m(2, 2);
  S21Matrix m1(3, 3);
  EXPECT_ANY_THROW(m.sum_matrix(m1));
}

TEST(test_functional, sum_matrix_different_cols_exception) {
  S21Matrix m(2, 2);
  S21Matrix m1(2, 3);
  EXPECT_ANY_THROW(m.sum_matrix(m1));
}

TEST(test_functional, sum_matrix_different_rows_exception) {
  S21Matrix m(2, 2);
  S21Matrix m1(3, 2);
  EXPECT_ANY_THROW(m.sum_matrix(m1));
}

TEST(test_functional, sub_matrix) {
  S21Matrix m(2, 2);
  S21Matrix m1(2, 2);
  m(0, 0) = 1.;
  m(0, 1) = 1.;
  m(1, 0) = 1.;
  m(1, 1) = 1.;
  m1(0, 0) = 0.5;
  m1(0, 1) = 0.5;
  m1(1, 0) = 0.5;
  m1(1, 1) = 0.5;
  m.sub_matrix(m1);
  EXPECT_EQ(m(0, 0), 0.5);
  EXPECT_EQ(m(0, 1), 0.5);
  EXPECT_EQ(m(1, 0), 0.5);
  EXPECT_EQ(m(1, 1), 0.5);
}

TEST(test_functional, sub_matrix_exception) {
  S21Matrix m(2, 2);
  S21Matrix m1(3, 3);
  EXPECT_ANY_THROW(m.sub_matrix(m1));
}

TEST(test_functional, sub_matrix_different_cols_exception) {
  S21Matrix m(2, 2);
  S21Matrix m1(2, 3);
  EXPECT_ANY_THROW(m.sub_matrix(m1));
}

TEST(test_functional, sub_matrix_different_rows_exception) {
  S21Matrix m(2, 2);
  S21Matrix m1(3, 2);
  EXPECT_ANY_THROW(m.sub_matrix(m1));
}

TEST(test_functional, mul_number) {
  S21Matrix m(2, 2);
  m[0][0] = 1.;
  m[0][1] = 2.;
  m[1][0] = 3.;
  m[1][1] = 4.;
  m.mul_number(2.);
  EXPECT_EQ(m[0][0], 2.);
  EXPECT_EQ(m[0][1], 4.);
  EXPECT_EQ(m[1][0], 6.);
  EXPECT_EQ(m[1][1], 8.);
}

TEST(test_functional, mul_matrix) {
  S21Matrix m1(2, 3);
  m1[0][0] = 1.;
  m1[0][1] = 2.;
  m1[0][2] = 3.;
  m1[1][0] = 4.;
  m1[1][1] = 5.;
  m1[1][2] = 6.;
  S21Matrix m2(3, 2);
  m2[0][0] = 7.;
  m2[0][1] = 8.;
  m2[1][0] = 9.;
  m2[1][1] = 10.;
  m2[2][0] = 11.;
  m2[2][1] = 12.;
  m1.mul_matrix(m2);
  EXPECT_EQ(m1[0][0], 58.);
  EXPECT_EQ(m1[0][1], 64.);
  EXPECT_EQ(m1[1][0], 139.);
  EXPECT_EQ(m1[1][1], 154.);
}

TEST(test_functional, mul_matrix_exception) {
  S21Matrix m1(2, 3);
  S21Matrix m2(1, 4);
  EXPECT_ANY_THROW(m1.mul_matrix(m2));
}

TEST(test_functional, transpose) {
  S21Matrix m(2, 3);
  m[0][0] = 1.;
  m[0][1] = 2.;
  m[0][2] = 3.;
  m[1][0] = 4.;
  m[1][1] = 5.;
  m[1][2] = 6.;
  S21Matrix transposed = m.transpose();
  EXPECT_EQ(transposed.get_rows(), 3);
  EXPECT_EQ(transposed.get_cols(), 2);
  EXPECT_EQ(transposed[0][0], 1.);
  EXPECT_EQ(transposed[1][0], 2.);
  EXPECT_EQ(transposed[2][0], 3.);
  EXPECT_EQ(transposed[0][1], 4.);
  EXPECT_EQ(transposed[1][1], 5.);
  EXPECT_EQ(transposed[2][1], 6.);
}

TEST(test_overload, sum_operator) {
  S21Matrix m(2, 2);
  m[0][0] = 1.;
  m[0][1] = 2.;
  m[1][0] = 3.;
  m[1][1] = 4.;
  S21Matrix m1(2, 2);
  m1[0][0] = 5.;
  m1[0][1] = 6.;
  m1[1][0] = 7.;
  m1[1][1] = 8.;
  S21Matrix sum = m + m1;
  EXPECT_EQ(sum.get_rows(), 2);
  EXPECT_EQ(sum.get_cols(), 2);
  EXPECT_EQ(sum[0][0], 6.);
  EXPECT_EQ(sum[0][1], 8.);
  EXPECT_EQ(sum[1][0], 10.);
  EXPECT_EQ(sum[1][1], 12.);
}

TEST(test_overload, sum_operator_exception) {
  S21Matrix m(2, 3);
  S21Matrix m1(3, 2);

  EXPECT_ANY_THROW({ S21Matrix sum = m + m1; });
}

TEST(test_overload, sub_operator) {
  S21Matrix m(2, 2);
  m[0][0] = 1.;
  m[0][1] = 2.;
  m[1][0] = 3.;
  m[1][1] = 4.;
  S21Matrix m1(2, 2);
  m1[0][0] = 5.;
  m1[0][1] = 6.;
  m1[1][0] = 7.;
  m1[1][1] = 8.;
  S21Matrix diff = m - m1;
  EXPECT_EQ(diff.get_rows(), 2);
  EXPECT_EQ(diff.get_cols(), 2);
  EXPECT_EQ(diff[0][0], -4.);
  EXPECT_EQ(diff[0][1], -4.);
  EXPECT_EQ(diff[1][0], -4.);
  EXPECT_EQ(diff[1][1], -4.);
}

TEST(test_overload, sub_operator_exception) {
  S21Matrix m(2, 3);
  S21Matrix m1(3, 2);

  EXPECT_ANY_THROW({ S21Matrix diff = m - m1; });
}

TEST(test_overload, mul_operator) {
  S21Matrix m1(2, 3);
  m1[0][0] = 1.;
  m1[0][1] = 2.;
  m1[0][2] = 3.;
  m1[1][0] = 4.;
  m1[1][1] = 5.;
  m1[1][2] = 6.;
  S21Matrix m2(3, 2);
  m2[0][0] = 7.;
  m2[0][1] = 8.;
  m2[1][0] = 9.;
  m2[1][1] = 10.;
  m2[2][0] = 11.;
  m2[2][1] = 12.;
  S21Matrix result = m1 * m2;
  EXPECT_EQ(result.get_rows(), 2);
  EXPECT_EQ(result.get_cols(), 2);
  EXPECT_EQ(result[0][0], 58.);
  EXPECT_EQ(result[0][1], 64.);
  EXPECT_EQ(result[1][0], 139.);
  EXPECT_EQ(result[1][1], 154.);
}

TEST(test_overload, mul_operator_exception) {
  // Создаем матрицы разного размера, которые нельзя перемножить
  S21Matrix m1(2, 3);
  S21Matrix m2(2, 2);

  // Заполняем матрицы
  m1[0][0] = 1.;
  m1[0][1] = 2.;
  m1[0][2] = 3.;
  m1[1][0] = 4.;
  m1[1][1] = 5.;
  m1[1][2] = 6.;
  m2[0][0] = 7.;
  m2[0][1] = 8.;
  m2[1][0] = 9.;
  m2[1][1] = 10.;

  // При попытке умножить эти матрицы должно произойти исключение
  EXPECT_ANY_THROW({ S21Matrix result = m1 * m2; });
}

TEST(test_overload, mul_number_operator) {
  S21Matrix m(2, 2);
  m[0][0] = 1.;
  m[0][1] = 2.;
  m[1][0] = 3.;
  m[1][1] = 4.;
  S21Matrix result = m * 2.;
  EXPECT_EQ(result.get_rows(), 2);
  EXPECT_EQ(result.get_cols(), 2);
  EXPECT_EQ(result[0][0], 2.);
  EXPECT_EQ(result[0][1], 4.);
  EXPECT_EQ(result[1][0], 6.);
  EXPECT_EQ(result[1][1], 8.);
}

TEST(test_overload, mul_matrix_operator) {
  S21Matrix m1(2, 3);
  m1[0][0] = 1.;
  m1[0][1] = 2.;
  m1[0][2] = 3.;
  m1[1][0] = 4.;
  m1[1][1] = 5.;
  m1[1][2] = 6.;
  S21Matrix m2(3, 2);
  m2[0][0] = 7.;
  m2[0][1] = 8.;
  m2[1][0] = 9.;
  m2[1][1] = 10.;
  m2[2][0] = 11.;
  m2[2][1] = 12.;
  m1 *= m2;
  EXPECT_EQ(m1.get_rows(), 2);
  EXPECT_EQ(m1.get_cols(), 2);
  EXPECT_EQ(m1[0][0], 58.);
  EXPECT_EQ(m1[0][1], 64.);
  EXPECT_EQ(m1[1][0], 139.);
  EXPECT_EQ(m1[1][1], 154.);
}

TEST(test_overload, mul_number_operator2) {
  S21Matrix m(2, 2);
  m[0][0] = 1.;
  m[0][1] = 2.;
  m[1][0] = 3.;
  m[1][1] = 4.;
  m *= 2.;
  EXPECT_EQ(m[0][0], 2.);
  EXPECT_EQ(m[0][1], 4.);
  EXPECT_EQ(m[1][0], 6.);
  EXPECT_EQ(m[1][1], 8.);
}

TEST(test_overload, sum_operator_equal) {
  S21Matrix m(2, 2);
  m[0][0] = 1.;
  m[0][1] = 2.;
  m[1][0] = 3.;
  m[1][1] = 4.;
  S21Matrix m1(2, 2);
  m1[0][0] = 5.;
  m1[0][1] = 6.;
  m1[1][0] = 7.;
  m1[1][1] = 8.;
  m += m1;
  EXPECT_EQ(m[0][0], 6.);
  EXPECT_EQ(m[0][1], 8.);
  EXPECT_EQ(m[1][0], 10.);
  EXPECT_EQ(m[1][1], 12.);
}

TEST(test_overload, sub_operator_equal) {
  S21Matrix m(2, 2);
  m[0][0] = 1;
  m[0][1] = 2;
  m[1][0] = 3;
  m[1][1] = 4;
  S21Matrix m1(2, 2);
  m1[0][0] = 5;
  m1[0][1] = 6;
  m1[1][0] = 7;
  m1[1][1] = 8;
  m -= m1;
  EXPECT_EQ(m[0][0], -4.);
  EXPECT_EQ(m[0][1], -4.);
  EXPECT_EQ(m[1][0], -4.);
  EXPECT_EQ(m[1][1], -4.);
}

TEST(test_overload, equal_operator) {
  S21Matrix m(2, 2);
  m[0][0] = 1.;
  m[0][1] = 2.;
  m[1][0] = 3.;
  m[1][1] = 4.;
  S21Matrix m1(2, 2);
  m1[0][0] = 1.;
  m1[0][1] = 2.;
  m1[1][0] = 3.;
  m1[1][1] = 4.;
  ASSERT_TRUE(m == m1);
}

TEST(test_overload, assignment_operator) {
  S21Matrix m(2, 2);
  m[0][0] = 1.;
  m[0][1] = 2.;
  m[1][0] = 3.;
  m[1][1] = 4.;
  S21Matrix m1;
  m1 = m;
  EXPECT_EQ(m1.get_rows(), 2);
  EXPECT_EQ(m1.get_cols(), 2);
  EXPECT_EQ(m1[0][0], 1.);
  EXPECT_EQ(m1[0][1], 2.);
  EXPECT_EQ(m1[1][0], 3.);
  EXPECT_EQ(m1[1][1], 4.);
}

TEST(test_overload, parentheses_operator) {
  S21Matrix m(3, 3);
  m(0, 0) = 1.;
  m(1, 1) = 2.;
  m(2, 2) = 3.;
  EXPECT_EQ(m(0, 0), 1.);
  EXPECT_EQ(m(1, 1), 2.);
  EXPECT_EQ(m(2, 2), 3.);
  m(0, 0) = 5.;
  EXPECT_EQ(m(0, 0), 5.);
}

TEST(test_overload, parentheses_operator_exception) {
  S21Matrix m(3, 3);
  EXPECT_ANY_THROW(m(3, 0));
  EXPECT_ANY_THROW(m(0, 3));
  EXPECT_ANY_THROW(m(-1, 0));
  EXPECT_ANY_THROW(m(0, -1));
}

TEST(test_overload, square_brackets_operator) {
  S21Matrix m(3, 3);
  m[0][0] = 1.;
  m[0][1] = 2.;
  m[0][2] = 3.;
  m[1][0] = 4.;
  m[1][1] = 5.;
  m[1][2] = 6.;
  m[2][0] = 7.;
  m[2][1] = 8.;
  m[2][2] = 9.;
  EXPECT_EQ(m[0][0], 1.);
  EXPECT_EQ(m[0][1], 2.);
  EXPECT_EQ(m[0][2], 3.);
  EXPECT_EQ(m[1][0], 4.);
  EXPECT_EQ(m[1][1], 5.);
  EXPECT_EQ(m[1][2], 6.);
  EXPECT_EQ(m[2][0], 7.);
  EXPECT_EQ(m[2][1], 8.);
  EXPECT_EQ(m[2][2], 9.);
}

TEST(test_overload, square_brackets_operator_exception) {
  S21Matrix m(3, 3);
  EXPECT_ANY_THROW(m[10]);
  EXPECT_ANY_THROW(m[3]);
}

TEST(test_functional, determinant_1x1) {
  S21Matrix m(1, 1);
  m(0, 0) = 5.;
  double det = m.determinant();
  ASSERT_NEAR(det, 5., 1e-6);
}

TEST(test_functional, determinant_2x2) {
  S21Matrix m(2, 2);
  m(0, 0) = 1.;
  m(0, 1) = 2.;
  m(1, 0) = 3.;
  m(1, 1) = 4.;
  double det = m.determinant();
  ASSERT_NEAR(det, -2., 1e-6);
}

TEST(test_functional, determinant_3x3) {
  S21Matrix m(3, 3);
  m(0, 0) = 6.;
  m(0, 1) = 1.;
  m(0, 2) = 1.;
  m(1, 0) = 4.;
  m(1, 1) = -2.;
  m(1, 2) = 5.;
  m(2, 0) = 2.;
  m(2, 1) = 8.;
  m(2, 2) = 7.;
  double det = m.determinant();
  ASSERT_NEAR(det, -306, 1e-6);
}

TEST(test_functional, determinant_larger_matrix) {
  S21Matrix m(4, 4);
  m(0, 0) = 1.;
  m(0, 1) = 2.;
  m(0, 2) = 3.;
  m(0, 3) = 4.;
  m(1, 0) = 5.;
  m(1, 1) = 6.;
  m(1, 2) = 7.;
  m(1, 3) = 8.;
  m(2, 0) = 9.;
  m(2, 1) = 10.;
  m(2, 2) = 11.;
  m(2, 3) = 12.;
  m(3, 0) = 13.;
  m(3, 1) = 14.;
  m(3, 2) = 15.;
  m(3, 3) = 16.;
  double det = m.determinant();
  ASSERT_NEAR(det, 0., 1e-6);
}

TEST(test_functional, determinant_zero) {
  S21Matrix m(3, 3);
  m(0, 0) = 1.;
  m(0, 1) = 2.;
  m(0, 2) = 3.;
  m(1, 0) = 4.;
  m(1, 1) = 5.;
  m(1, 2) = 6.;
  m(2, 0) = 7.;
  m(2, 1) = 8.;
  m(2, 2) = 9.;
  double det = m.determinant();
  ASSERT_NEAR(det, 0., 1e-6);
}

TEST(test_functional, determinant_non_square_matrix) {
  S21Matrix m(2, 3);
  m(0, 0) = 1.;
  m(0, 1) = 2.;
  m(0, 2) = 3.;
  m(1, 0) = 4.;
  m(1, 1) = 5.;
  m(1, 2) = 6.;
  EXPECT_ANY_THROW(m.determinant());
}

TEST(test_functional, complement_1x1) {
  S21Matrix m(1, 1);
  m(0, 0) = 5.;
  S21Matrix comp = m.calc_complements();
  EXPECT_FLOAT_EQ(comp(0, 0), 1.0 / 5.);
}

TEST(test_functional, complement_2x2) {
  S21Matrix m(2, 2);
  m(0, 0) = 4.;
  m(0, 1) = 7.;
  m(1, 0) = 2.;
  m(1, 1) = 6.;
  S21Matrix comp = m.calc_complements();
  EXPECT_FLOAT_EQ(comp(0, 0), 6.0);
  EXPECT_FLOAT_EQ(comp(0, 1), -2.0);
  EXPECT_FLOAT_EQ(comp(1, 0), -7.0);
  EXPECT_FLOAT_EQ(comp(1, 1), 4.0);
}

TEST(test_functional, complement_4x4_nonzero_determinant) {
  S21Matrix m(4, 4);
  m(0, 0) = 6.;
  m(0, 1) = 2.;
  m(0, 2) = 3.;
  m(0, 3) = 4.;
  m(1, 0) = 5.;
  m(1, 1) = 6.;
  m(1, 2) = 7.;
  m(1, 3) = 8.;
  m(2, 0) = 9.;
  m(2, 1) = 10.;
  m(2, 2) = 23.;
  m(2, 3) = 0.;
  m(3, 0) = 5.;
  m(3, 1) = 1.;
  m(3, 2) = 15.;
  m(3, 3) = 16.;
  S21Matrix comp = m.calc_complements();
  EXPECT_FLOAT_EQ(comp(0, 0), 2104.);
  EXPECT_FLOAT_EQ(comp(0, 1), -992.);
  EXPECT_FLOAT_EQ(comp(0, 2), -392.);
  EXPECT_FLOAT_EQ(comp(0, 3), -228.);
  EXPECT_FLOAT_EQ(comp(1, 0), -764.);
  EXPECT_FLOAT_EQ(comp(1, 1), 1856.);
  EXPECT_FLOAT_EQ(comp(1, 2), -508.);
  EXPECT_FLOAT_EQ(comp(1, 3), 599.);
  EXPECT_FLOAT_EQ(comp(2, 0), 52.);
  EXPECT_FLOAT_EQ(comp(2, 1), 8.);
  EXPECT_FLOAT_EQ(comp(2, 2), 348.);
  EXPECT_FLOAT_EQ(comp(2, 3), -343.);
  EXPECT_FLOAT_EQ(comp(3, 0), -144.);
  EXPECT_FLOAT_EQ(comp(3, 1), -680.);
  EXPECT_FLOAT_EQ(comp(3, 2), 352.);
  EXPECT_FLOAT_EQ(comp(3, 3), 292.);
}

TEST(test_functional, complement_4x4_zero_determinant) {
  S21Matrix m(4, 4);
  m(0, 0) = 1.;
  m(0, 1) = 2.;
  m(0, 2) = 3.;
  m(0, 3) = 4.;
  m(1, 0) = 5.;
  m(1, 1) = 6.;
  m(1, 2) = 7.;
  m(1, 3) = 8.;
  m(2, 0) = 9.;
  m(2, 1) = 10.;
  m(2, 2) = 11.;
  m(2, 3) = 12.;
  m(3, 0) = 13.;
  m(3, 1) = 14.;
  m(3, 2) = 15.;
  m(3, 3) = 16.;
  EXPECT_ANY_THROW({ S21Matrix comp = m.calc_complements(); });
}

TEST(test_functional, inverse_2x2) {
  S21Matrix m(2, 2);
  m(0, 0) = 4.;
  m(0, 1) = 7.;
  m(1, 0) = 2.;
  m(1, 1) = 6.;
  S21Matrix inv = m.inverse_matrix();
  EXPECT_FLOAT_EQ(inv(0, 0), 0.6);
  EXPECT_FLOAT_EQ(inv(0, 1), -0.7);
  EXPECT_FLOAT_EQ(inv(1, 0), -0.2);
  EXPECT_FLOAT_EQ(inv(1, 1), 0.4);
}

TEST(test_functional, inverse_3x3) {
  S21Matrix m(3, 3);
  m(0, 0) = 2.;
  m(0, 1) = 2.;
  m(0, 2) = 2.;
  m(1, 0) = 0.;
  m(1, 1) = 4.;
  m(1, 2) = 0.;
  m(2, 0) = 4.;
  m(2, 1) = 2.;
  m(2, 2) = 2.;
  S21Matrix inv = m.inverse_matrix();
  EXPECT_FLOAT_EQ(inv(0, 0), -0.5);
  EXPECT_FLOAT_EQ(inv(0, 1), 0);
  EXPECT_FLOAT_EQ(inv(0, 2), 0.5);
  EXPECT_FLOAT_EQ(inv(1, 0), 0);
  EXPECT_FLOAT_EQ(inv(1, 1), 0.25);
  EXPECT_FLOAT_EQ(inv(1, 2), 0);
  EXPECT_FLOAT_EQ(inv(2, 0), 1);
  EXPECT_FLOAT_EQ(inv(2, 1), -0.25);
  EXPECT_FLOAT_EQ(inv(2, 2), -0.5);
}

TEST(test_functional, inverse_4x4_zero_determinant) {
  S21Matrix m(4, 4);
  m(0, 0) = 1.;
  m(0, 1) = 2.;
  m(0, 2) = 3.;
  m(0, 3) = 4.;
  m(1, 0) = 5.;
  m(1, 1) = 6.;
  m(1, 2) = 7.;
  m(1, 3) = 8.;
  m(2, 0) = 9.;
  m(2, 1) = 10.;
  m(2, 2) = 11.;
  m(2, 3) = 12.;
  m(3, 0) = 13.;
  m(3, 1) = 14.;
  m(3, 2) = 15.;
  m(3, 3) = 16.;
  EXPECT_ANY_THROW({ S21Matrix inv = m.inverse_matrix(); });
}

int main() {
  testing::InitGoogleTest();
  if (RUN_ALL_TESTS()) {
    std::cout << "Some tests have failed" << std::endl;
  }
}