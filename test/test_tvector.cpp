#include "tmatrix.h"

#include <gtest.h>

TEST(TDynamicVector, can_create_vector_with_positive_length)
{
  ASSERT_NO_THROW(TDynamicVector<int> v(5));
}

TEST(TDynamicVector, cant_create_too_large_vector)
{
  ASSERT_ANY_THROW(TDynamicVector<int> v(MAX_VECTOR_SIZE + 1));
}

TEST(TDynamicVector, throws_when_create_vector_with_negative_length)
{
  ASSERT_ANY_THROW(TDynamicVector<int> v(-5));
}

TEST(TDynamicVector, can_create_copied_vector)
{
  TDynamicVector<int> v(10);

  ASSERT_NO_THROW(TDynamicVector<int> v1(v));
}

TEST(TDynamicVector, copied_vector_is_equal_to_source_one)
{
	TDynamicVector<int> v(2);
	v[0] = 0; v[1] = 1;
	TDynamicVector<int> z(v);
	EXPECT_EQ(v.size(), z.size());
	EXPECT_EQ(v[0], z[0]);
	EXPECT_EQ(v[1], z[1]);
}

TEST(TDynamicVector, copied_vector_has_its_own_memory)
{
	TDynamicVector<int> v(2);
	TDynamicVector<int> z(v);
	ASSERT_NE(&v[0], &z[0]);
}

TEST(TDynamicVector, can_get_size)
{
  TDynamicVector<int> v(4);
  EXPECT_EQ(4, v.size());
}

TEST(TDynamicVector, can_set_and_get_element)
{
  TDynamicVector<int> v(4);
  v[0] = 4;
  EXPECT_EQ(4, v[0]);
}

TEST(TDynamicVector, throws_when_set_element_with_negative_index)
{
	TDynamicVector<int> v(4);
	ASSERT_ANY_THROW(v[-1] = 4);
}

TEST(TDynamicVector, throws_when_set_element_with_too_large_index)
{
	TDynamicVector<int> v(4);
	ASSERT_ANY_THROW(v[4] = 4);
}

TEST(TDynamicVector, can_assign_vector_to_itself)
{
	TDynamicVector<int> v(2);
	v[0] = 0; v[1] = 1;
	v = v;
	EXPECT_EQ(v[0],0);
	EXPECT_EQ(v[1], 1);
}

TEST(TDynamicVector, can_assign_vectors_of_equal_size)
{
	TDynamicVector<int> v(2);
	v[0] = 0; v[1] = 1;
	TDynamicVector<int> z(2);
	z = v;
	EXPECT_EQ(v.size(), z.size());
	EXPECT_EQ(v[0], z[0]);
	EXPECT_EQ(v[1], z[1]);
	v[0] = 3;
	EXPECT_EQ(z[0], 0);
}

TEST(TDynamicVector, assign_operator_change_vector_size)
{
	TDynamicVector<int> v(3);
	TDynamicVector<int> z(2);
	z = v;
	EXPECT_EQ(z.size(), 3);
}

TEST(TDynamicVector, can_assign_vectors_of_different_size)
{
	TDynamicVector<int> v(3);
	v[0] = 0; v[1] = 1; v[2] = 2;
	TDynamicVector<int> z(2);
	z = v;
	EXPECT_EQ(v[0], z[0]);
	EXPECT_EQ(v[1], z[1]);
	EXPECT_EQ(v[2], z[2]);
}

TEST(TDynamicVector, compare_equal_vectors_return_true)
{
	TDynamicVector<int> v(3);
	v[0] = 0; v[1] = 1; v[2] = 2;
	TDynamicVector<int> z(3);
	z[0] = 0; z[1] = 1; z[2] = 2;
	EXPECT_EQ(v, z);
}

TEST(TDynamicVector, compare_vector_with_itself_return_true)
{
	TDynamicVector<int> v(3);
	v[0] = 0; v[1] = 1; v[2] = 2;
	EXPECT_EQ(v, v);
}

TEST(TDynamicVector, vectors_with_different_size_are_not_equal)
{
	TDynamicVector<int> v(3);
	v[0] = 0; v[1] = 1; v[2] = 2;
	TDynamicVector<int> z(2);
	z[0] = 0; z[1] = 1;
	EXPECT_NE(v, z);
}

TEST(TDynamicVector, can_add_scalar_to_vector)
{
	TDynamicVector<int> v(3);
	v[0] = 0; v[1] = 1; v[2] = 2;
	v = v + 1;
	EXPECT_EQ(v[0], 1);
	EXPECT_EQ(v[1], 2);
	EXPECT_EQ(v[2], 3);
}

TEST(TDynamicVector, can_subtract_scalar_from_vector)
{
	TDynamicVector<int> v(3);
	v[0] = 1; v[1] = 2; v[2] = 3;
	v = v - 1;
	EXPECT_EQ(v[0], 0);
	EXPECT_EQ(v[1], 1);
	EXPECT_EQ(v[2], 2);
}

TEST(TDynamicVector, can_multiply_scalar_by_vector)
{
	TDynamicVector<int> v(3);
	v[0] = 1; v[1] = 2; v[2] = 3;
	v = v * 2;
	EXPECT_EQ(v[0], 2);
	EXPECT_EQ(v[1], 4);
	EXPECT_EQ(v[2], 6);
}

TEST(TDynamicVector, can_add_vectors_with_equal_size)
{
	TDynamicVector<int> v(3);
	v[0] = 0; v[1] = 1; v[2] = 2;
	TDynamicVector<int> z(3);
	z[0] = 3; z[1] = 4; z[2] = 5;
	v = v + z;
	EXPECT_EQ(v[0], 3);
	EXPECT_EQ(v[1], 5);
	EXPECT_EQ(v[2], 7);
}

TEST(TDynamicVector, cant_add_vectors_with_not_equal_size)
{
	TDynamicVector<int> v(3);
	v[0] = 0; v[1] = 1; v[2] = 2;
	TDynamicVector<int> z(2);
	z[0] = 3; z[1] = 4;
	ASSERT_ANY_THROW(v = v + z);
}

TEST(TDynamicVector, can_subtract_vectors_with_equal_size)
{
	TDynamicVector<int> v(3);
	v[0] = 0; v[1] = 1; v[2] = 2;
	TDynamicVector<int> z(3);
	z[0] = 3; z[1] = 4; z[2] = 5;
	v = z - v;
	EXPECT_EQ(v[0], 3);
	EXPECT_EQ(v[1], 3);
	EXPECT_EQ(v[2], 3);
}

TEST(TDynamicVector, cant_subtract_vectors_with_not_equal_size)
{
	TDynamicVector<int> v(3);
	v[0] = 0; v[1] = 1; v[2] = 2;
	TDynamicVector<int> z(2);
	z[0] = 3; z[1] = 4;
	ASSERT_ANY_THROW(v = v - z);
}

TEST(TDynamicVector, can_multiply_vectors_with_equal_size)
{
	TDynamicVector<int> v(3);
	v[0] = 0; v[1] = 1; v[2] = 2;
	TDynamicVector<int> z(3);
	z[0] = 3; z[1] = 4; z[2] = 5;
	int w = v * z;
	EXPECT_EQ(w, 14);
	
}

TEST(TDynamicVector, cant_multiply_vectors_with_not_equal_size)
{
	TDynamicVector<int> v(3);
	v[0] = 0; v[1] = 1; v[2] = 2;
	TDynamicVector<int> z(2);
	z[0] = 3; z[1] = 4;
	ASSERT_ANY_THROW(v = v * z);
}

