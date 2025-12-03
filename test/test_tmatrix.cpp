#include "tmatrix.h"

#include <gtest.h>

TEST(TDynamicMatrix, can_create_matrix_with_positive_length)
{
  ASSERT_NO_THROW(TDynamicMatrix<int> m(5));
}

TEST(TDynamicMatrix, cant_create_too_large_matrix)
{
  ASSERT_ANY_THROW(TDynamicMatrix<int> m(MAX_MATRIX_SIZE + 1));
}

TEST(TDynamicMatrix, throws_when_create_matrix_with_negative_length)
{
  ASSERT_ANY_THROW(TDynamicMatrix<int> m(-5));
}

TEST(TDynamicMatrix, can_create_copied_matrix)
{
  TDynamicMatrix<int> m(5);
  ASSERT_NO_THROW(TDynamicMatrix<int> m1(m));
}

TEST(TDynamicMatrix, copied_matrix_is_equal_to_source_one)
{
	TDynamicMatrix<int> v(2);
	v[0][0] = 0; v[0][1] = 1;
	v[1][0] = 2; v[1][1] = 3;
	TDynamicMatrix<int> y(2);
	y = v;
	ASSERT_EQ(v, y);
}

TEST(TDynamicMatrix, copied_matrix_has_its_own_memory)
{
	TDynamicMatrix<int> v(2);
	TDynamicMatrix<int> z(v);
	ASSERT_NE(&v[0], &z[0]);
}

TEST(TDynamicMatrix, can_get_size)
{
	TDynamicMatrix<int> v(4);
	EXPECT_EQ(4, v[0].size());
}

TEST(TDynamicMatrix, can_set_and_get_element)
{
	TDynamicMatrix<int> v(4);
	v[0][0] = 4;
	EXPECT_EQ(v[0][0], 4);
}

TEST(TDynamicMatrix, throws_when_set_element_with_negative_index)
{
	TDynamicMatrix<int> v(4);
	ASSERT_ANY_THROW(v[-1][0] = 4);
}

TEST(TDynamicMatrix, throws_when_set_element_with_too_large_index)
{
	TDynamicMatrix<int> v(4);
	ASSERT_ANY_THROW(v[4][4] = 4);
}

TEST(TDynamicMatrix, can_assign_matrix_to_itself)
{
	TDynamicMatrix<int> v(2);
	v[0][0] = 0; v[0][1] = 1;
	v[1][0] = 2; v[1][1] = 3;
	v = v;
	EXPECT_EQ(v[0][0], 0);
	EXPECT_EQ(v[1][1], 3);
}

TEST(TDynamicMatrix, can_assign_matrices_of_equal_size)
{
	TDynamicMatrix<int> v(2);
	v[0][0] = 0; v[0][1] = 1;
	v[1][0] = 2; v[1][1] = 3;
	TDynamicMatrix<int> z(2);
	z = v;
	EXPECT_EQ(v[0].size(), z[0].size());
	EXPECT_EQ(v[0][0], z[0][0]);
	EXPECT_EQ(v[1][0], z[1][0]);
	v[0][0] = 3;
	EXPECT_EQ(z[0][0], 0);
}

TEST(TDynamicMatrix, assign_operator_change_matrix_size)
{
	TDynamicMatrix<int> v(3);
	TDynamicMatrix<int> z(2);
	z = v;
	EXPECT_EQ(z[0].size(), 3);
}

TEST(TDynamicMatrix, can_assign_matrices_of_different_size)
{
	TDynamicMatrix<int> v(2);
	v[0][0] = 0; v[0][1] = 1;
	v[1][0] = 2; v[1][1] = 3;
	TDynamicMatrix<int> z(1);
	z = v;
	EXPECT_EQ(v[0][0], z[0][0]);
	EXPECT_EQ(v[1][0], z[1][0]);
}

TEST(TDynamicMatrix, compare_equal_matrices_return_true)
{
	TDynamicMatrix<int> v(2);
	v[0][0] = 0; v[0][1] = 1;
	v[1][0] = 2; v[1][1] = 3;
	TDynamicMatrix<int> z(2);
	z[0][0] = 0; z[0][1] = 1;
	z[1][0] = 2; z[1][1] = 3;
	EXPECT_EQ(v, z);
}

TEST(TDynamicMatrix, compare_matrix_with_itself_return_true)
{
	TDynamicMatrix<int> v(2);
	v[0][0] = 0; v[0][1] = 1;
	v[1][0] = 2; v[1][1] = 3;
	EXPECT_EQ(v, v);
}

TEST(TDynamicMatrix, matrices_with_different_size_are_not_equal)
{
	TDynamicMatrix<int> v(2);
	v[0][0] = 0; v[0][1] = 1;
	v[1][0] = 2; v[1][1] = 3;
	TDynamicMatrix<int> z(1);
	z[0][0] = 0;
	EXPECT_NE(v, z);
}

TEST(TDynamicMatrix, can_add_matrices_with_equal_size)
{
	TDynamicMatrix<int> v(2);
	v[0][0] = 0; v[0][1] = 1;
	v[1][0] = 2; v[1][1] = 3;
	TDynamicMatrix<int> z(2);
	z[0][0] = 4; z[0][1] = -1;
	z[1][0] = 3; z[1][1] = 7;
	v = z + v;
	EXPECT_EQ(v[0][0], 4);
	EXPECT_EQ(v[0][1], 0);
	EXPECT_EQ(v[1][0], 5);
	EXPECT_EQ(v[1][1], 10);
}

TEST(TDynamicMatrix, cant_add_matrices_with_not_equal_size)
{
	TDynamicMatrix<int> v(2);
	v[0][0] = 0; v[0][1] = 1;
	v[1][0] = 2; v[1][1] = 3;
	TDynamicMatrix<int> z(1);
	z[0][0] = 1;
	ASSERT_ANY_THROW(v = z + v);
}

TEST(TDynamicMatrix, can_subtract_matrices_with_equal_size)
{
	TDynamicMatrix<int> v(2);
	v[0][0] = 0; v[0][1] = 1;
	v[1][0] = 2; v[1][1] = 3;
	TDynamicMatrix<int> z(2);
	z[0][0] = 4; z[0][1] = -1;
	z[1][0] = 3; z[1][1] = 7;
	v = z - v;
	EXPECT_EQ(v[0][0], 4);
	EXPECT_EQ(v[0][1], -2);
	EXPECT_EQ(v[1][0], 1);
	EXPECT_EQ(v[1][1], 4);
}

TEST(TDynamicMatrix, cant_subtract_matrixes_with_not_equal_size)
{
	TDynamicMatrix<int> v(2);
	v[0][0] = 0; v[0][1] = 1;
	v[1][0] = 2; v[1][1] = 3;
	TDynamicMatrix<int> z(1);
	z[0][0] = 1;
	ASSERT_ANY_THROW(v = z - v);
}

