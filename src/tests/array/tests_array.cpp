#include "../tests_libplus.h"

TEST(Array, ArrayEmptyConstructor) {
  Array<int, 0> a1;
  ASSERT_EQ(a1.size(), 0);

  Array<int, 2> a2;
  ASSERT_EQ(a2.size(), 2);

  Array<char, 2> a3;
  ASSERT_EQ(a3.size(), 2);
}

TEST(Array, ArrayConstructorInitializerList) {
  Array<int, 3> a1{1, 2, 3};
  ASSERT_EQ(a1.size(), 3);
  ASSERT_EQ(a1.at(0), 1);
  ASSERT_EQ(a1.at(1), 2);
  ASSERT_EQ(a1.at(2), 3);

  Array<char, 3> a2{'a', 'b', 'c'};
  ASSERT_EQ(a2.size(), 3);
  ASSERT_EQ(a2.at(0), 'a');
  ASSERT_EQ(a2.at(1), 'b');
  ASSERT_EQ(a2.at(2), 'c');

  Array<char, 4> a3{'a', 'b', 'c'};
  std::array<char, 4> a4{'a', 'b', 'c'};
  ASSERT_EQ(a3.size(), a4.size());
  ASSERT_EQ(a3.at(0), a4.at(0));
  ASSERT_EQ(a3.at(1), a4.at(1));
  ASSERT_EQ(a3.at(2), a4.at(2));
}

TEST(Array, ArrayCopyConstructor) {
  Array<int, 3> a1{1, 2, 3};
  Array<int, 3> a2(a1);
  std::array<int, 3> a3{1, 2, 3};
  std::array<int, 3> a4(a3);

  ASSERT_EQ(a2.at(0), a4.at(0));
  ASSERT_EQ(a2.at(1), a4.at(1));
  ASSERT_EQ(a2.at(2), a4.at(2));
}

TEST(Array, ArrayMoveConstructor) {
  Array<int, 3> a1{1, 2, 3};
  Array<int, 3> a2(std::move(a1));
  std::array<int, 3> a3{1, 2, 3};
  std::array<int, 3> a4(std::move(a3));

  ASSERT_EQ(a2.at(0), a4.at(0));
  ASSERT_EQ(a2.at(1), a4.at(1));
  ASSERT_EQ(a2.at(2), a4.at(2));
}

TEST(Array, ArrayOperatorEqualsCopy) {
  Array<int, 3> a1{1, 2, 3};
  Array<int, 3> a2 = a1;
  ASSERT_EQ(a2.size(), 3);
  ASSERT_EQ(a2.at(0), 1);
  ASSERT_EQ(a2.at(1), 2);
  ASSERT_EQ(a2.at(2), 3);

  ASSERT_EQ(a1.size(), 3);
  ASSERT_EQ(a1.at(0), 1);
  ASSERT_EQ(a1.at(1), 2);
  ASSERT_EQ(a1.at(2), 3);
}

TEST(Array, ArrayOperatorEqualsMove) {
  Array<int, 3> a1{1, 2, 3};
  Array<int, 3> a2 = std::move(a1);
  ASSERT_EQ(a2.size(), 3);
  ASSERT_EQ(a2.at(0), 1);
  ASSERT_EQ(a2.at(1), 2);
  ASSERT_EQ(a2.at(2), 3);

  ASSERT_EQ(a1.size(), 3);
  ASSERT_EQ(a1.at(0), 1);
  ASSERT_EQ(a1.at(1), 2);
  ASSERT_EQ(a1.at(2), 3);

  std::array<int, 3> a3{1, 2, 3};
  std::array<int, 3> a4 = std::move(a3);
  ASSERT_EQ(a4.size(), 3);
  ASSERT_EQ(a4.at(0), 1);
  ASSERT_EQ(a4.at(1), 2);
  ASSERT_EQ(a4.at(2), 3);

  ASSERT_EQ(a3.size(), 3);
  ASSERT_EQ(a3.at(0), 1);
  ASSERT_EQ(a3.at(1), 2);
  ASSERT_EQ(a3.at(2), 3);
}

TEST(Array, ArrayAt) {
  Array<int, 3> a1{1, 2, 3};
  ASSERT_EQ(a1.at(0), 1);
  ASSERT_EQ(a1.at(1), 2);
  ASSERT_EQ(a1.at(2), 3);
  ASSERT_ANY_THROW(a1.at(3));
  ASSERT_ANY_THROW(a1.at(-1));
}

TEST(Array, ArrayOperatorSquareBrackets) {
  Array<int, 3> a1{1, 2, 3};
  ASSERT_EQ(a1[0], 1);
  ASSERT_EQ(a1[1], 2);
  ASSERT_EQ(a1[2], 3);
}

TEST(Array, ArrayFront) {
  Array<int, 3> a1{1, 2, 3};
  ASSERT_EQ(a1.front(), 1);

  std::array<int, 3> a3{1, 2, 3};
  ASSERT_EQ(a3.front(), 1);
}

TEST(Array, ArrayBack) {
  Array<int, 3> a1{1, 2, 3};
  std::array<int, 3> a3{1, 2, 3};
  ASSERT_EQ(a3.back(), a1.back());
}

TEST(Array, ArrayData) {
  Array<int, 3> a1{1, 2, 3};
  std::array<int, 3> a2{1, 2, 3};
  int *data1 = a1.data();
  int *data2 = a2.data();
  ASSERT_EQ(data1[0], data2[0]);
  ASSERT_EQ(data1[1], data2[1]);
  ASSERT_EQ(data1[2], data2[2]);
}

TEST(Array, ArrayIteratorBegin) {
  Array<int, 3> a1{1, 2, 3};
  int *iter = a1.begin();
  ASSERT_EQ(*iter, 1);
  ASSERT_EQ(*(++iter), 2);
  ASSERT_EQ(*(++iter), 3);

  Array<int, 0> v2;
  int *iter2 = v2.begin();
  ASSERT_EQ(iter2, v2.data());
}

TEST(Array, ArrayIteratorEnd) {
  Array<int, 3> a1{1, 2, 3};
  int *iterEnd = a1.end();
  ASSERT_EQ(*(--iterEnd), 3);
  ASSERT_EQ(*(--iterEnd), 2);
  ASSERT_EQ(*(--iterEnd), 1);

  Array<int, 0> v2;
  auto *iter2 = v2.end();
  ASSERT_EQ(iter2, v2.data());

  Array<int, 4> v3{1, 2, 3, 4};
  auto *iter = v3.begin();
  auto *iterEnd2 = v3.end();
  int count = 0;
  while (iter != iterEnd2) {
    count++;
    iter++;
  }
  ASSERT_EQ(count, 4);
}

TEST(Array, ArrayEmpty) {
  Array<int, 3> a1{1, 2, 3};
  ASSERT_FALSE(a1.empty());
  Array<int, 0> v2;
  ASSERT_TRUE(v2.empty());
}

TEST(Array, ArraySize) {
  Array<int, 3> a1{1, 2, 3};
  ASSERT_EQ(a1.size(), 3);
  Array<int, 0> v2;
  ASSERT_EQ(v2.size(), 0);
}

TEST(Array, ArrayMaxSize) {
  Array<int, 4> s21_vec_int{1, 4, 8, 9};
  std::array<int, 4> std_vec_int{1, 4, 8, 9};

  Array<int, 0> s21_vec_int_0;
  std::array<int, 0> std_vec_int_0;

  Array<double, 4> s21_vec_double{1.4, 4.8, 8.9, 9.1};
  std::array<double, 4> std_vec_double{1.4, 4.8, 8.9, 9.1};

  Array<std::string, 4> s21_vec_string{"Hello", ",", "world", "!"};
  std::array<std::string, 4> std_vec_string{"Hello", ",", "world", "!"};

  EXPECT_EQ(s21_vec_int.max_size(), std_vec_int.max_size());
  EXPECT_EQ(s21_vec_int_0.max_size(), std_vec_int_0.max_size());
  EXPECT_EQ(s21_vec_double.max_size(), std_vec_double.max_size());
  EXPECT_EQ(s21_vec_string.max_size(), std_vec_string.max_size());
}

TEST(Array, ArraySwap) {
  Array<int, 3> a1{1, 2, 3};
  Array<int, 3> a2{4, 5, 6};
  a1.swap(a2);

  std::array<int, 3> a3{1, 2, 3};
  std::array<int, 3> a4{4, 5, 6};
  a3.swap(a4);

  ASSERT_EQ(a1.size(), a3.size());
  ASSERT_EQ(a1.at(0), a3.at(0));
  ASSERT_EQ(a1.at(1), a3.at(1));
  ASSERT_EQ(a1.at(2), a3.at(2));

  ASSERT_EQ(a2.size(), a4.size());
  ASSERT_EQ(a2.at(0), a4.at(0));
  ASSERT_EQ(a2.at(1), a4.at(1));
  ASSERT_EQ(a2.at(2), a4.at(2));
}

TEST(Array, ArrayFill) {
  Array<int, 3> a1{1, 2, 3};
  a1.fill(666);

  std::array<int, 3> a3{1, 2, 3};
  a3.fill(666);

  ASSERT_EQ(a1.size(), a3.size());
  ASSERT_EQ(a1.at(0), a3.at(0));
  ASSERT_EQ(a1.at(1), a3.at(1));
  ASSERT_EQ(a1.at(2), a3.at(2));
}