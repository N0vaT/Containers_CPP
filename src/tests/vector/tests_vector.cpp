#include "../tests_lib.h"

TEST(Vector, VectorEmptyConstructor) {
  Vector<int> v1;
  ASSERT_EQ(v1.size(), 0);
  ASSERT_EQ(v1.capacity(), 0);
  ASSERT_EQ(v1.data(), nullptr);
}

TEST(Vector, VectorConstructorParameter) {
  Vector<int> v1(5);
  ASSERT_EQ(v1.size(), 5);
  ASSERT_EQ(v1.capacity(), 5);
  ASSERT_EQ(v1.at(0), 0);
  ASSERT_ANY_THROW(Vector<int> v2(-1));
}

TEST(Vector, VectorConstructorInitializerList) {
  Vector<int> v1{1, 2, 3};
  ASSERT_EQ(v1.size(), 3);
  ASSERT_EQ(v1.capacity(), 3);
  ASSERT_EQ(v1.at(0), 1);
  ASSERT_EQ(v1.at(1), 2);
  ASSERT_EQ(v1.at(2), 3);
}

TEST(Vector, VectorCopyConstructor) {
  Vector<int> src;
  src.push_back(2);
  src.push_back(4);
  src.push_back(16);
  Vector<int> dst(src);

  ASSERT_EQ(dst.at(0), 2);
  ASSERT_EQ(dst.at(1), 4);
  ASSERT_EQ(dst.at(2), 16);

  ASSERT_EQ(src.at(0), 2);
  ASSERT_EQ(src.at(1), 4);
  ASSERT_EQ(src.at(2), 16);
}

TEST(Vector, VectorMoveConstructor) {
  Vector<int> src;
  src.push_back(2);
  src.push_back(4);
  src.push_back(16);
  Vector<int> dst(std::move(src));

  ASSERT_EQ(dst.at(2), 16);
  ASSERT_EQ(dst.at(1), 4);
  ASSERT_EQ(dst.at(0), 2);

  ASSERT_EQ(src.size(), 0);
  ASSERT_EQ(src.capacity(), 0);
  ASSERT_EQ(src.data(), nullptr);
}

TEST(Vector, VectorOperatorEqualsCopy) {
  Vector<int> v1{1, 2, 3};
  Vector<int> v2 = v1;
  ASSERT_EQ(v2.size(), 3);
  ASSERT_EQ(v2.capacity(), 3);
  ASSERT_EQ(v2.at(0), 1);
  ASSERT_EQ(v2.at(1), 2);
  ASSERT_EQ(v2.at(2), 3);

  ASSERT_EQ(v1.size(), 3);
  ASSERT_EQ(v1.capacity(), 3);
  ASSERT_EQ(v1.at(0), 1);
  ASSERT_EQ(v1.at(1), 2);
  ASSERT_EQ(v1.at(2), 3);
}

TEST(Vector, VectorOperatorEqualsMove) {
  Vector<int> v1{1, 2, 3};
  Vector<int> v2 = std::move(v1);
  ASSERT_EQ(v2.size(), 3);
  ASSERT_EQ(v2.capacity(), 3);
  ASSERT_EQ(v2.at(0), 1);
  ASSERT_EQ(v2.at(1), 2);
  ASSERT_EQ(v2.at(2), 3);
}

TEST(Vector, VectorAt) {
  Vector<int> v1{1, 2, 3};
  ASSERT_EQ(v1.at(0), 1);
  ASSERT_EQ(v1.at(1), 2);
  ASSERT_EQ(v1.at(2), 3);
  ASSERT_ANY_THROW(v1.at(3));
  ASSERT_ANY_THROW(v1.at(-1));
}

TEST(Vector, VectorFront) {
  Vector<int> v1{1, 2, 3};
  ASSERT_EQ(v1.front(), 1);
  Vector<int> v2;
  ASSERT_ANY_THROW(v2.front());
}

TEST(Vector, VectorBack) {
  Vector<int> v1{1, 2, 3};
  ASSERT_EQ(v1.back(), 3);
  Vector<int> v2;
  ASSERT_ANY_THROW(v2.back());
}

TEST(Vector, VectorData) {
  Vector<int> v1{1, 2, 3};
  int *data = v1.data();
  ASSERT_EQ(data[0], 1);
  ASSERT_EQ(data[1], 2);
  ASSERT_EQ(data[2], 3);
}

TEST(Vector, VectorIteratorBegin) {
  Vector<int> v1{1, 2, 3};
  int *iter = v1.begin();
  ASSERT_EQ(*iter, 1);
  ASSERT_EQ(*(++iter), 2);
  ASSERT_EQ(*(++iter), 3);

  Vector<int> v2;
  int *iter2 = v2.begin();
  ASSERT_EQ(iter2, nullptr);
}

TEST(Vector, VectorIteratorEnd) {
  Vector<int> v1{1, 2, 3};
  int *iterEnd = v1.end();
  ASSERT_EQ(*(--iterEnd), 3);
  ASSERT_EQ(*(--iterEnd), 2);
  ASSERT_EQ(*(--iterEnd), 1);

  Vector<int> v2;
  auto *iter2 = v2.end();
  ASSERT_EQ(iter2, nullptr);

  Vector<int> v3{1, 2, 3, 4};
  auto *iter = v3.begin();
  auto *iterEnd2 = v3.end();
  int count = 0;
  while (iter != iterEnd2) {
    count++;
    iter++;
  }
  ASSERT_EQ(count, 4);
}

TEST(Vector, VectorEmpty) {
  Vector<int> v1{1, 2, 3};
  ASSERT_FALSE(v1.empty());
  Vector<int> v2;
  ASSERT_TRUE(v2.empty());
}

TEST(Vector, VectorSize) {
  Vector<int> v1{1, 2, 3};
  ASSERT_EQ(v1.size(), 3);
  Vector<int> v2;
  ASSERT_EQ(v2.size(), 0);
}

TEST(Vector, VectorMaxSize) {
  Vector<int> s21_vec_int{1, 4, 8, 9};
  std::vector<int> std_vec_int{1, 4, 8, 9};

  Vector<double> s21_vec_double{1.4, 4.8, 8.9, 9.1};
  std::vector<double> std_vec_double{1.4, 4.8, 8.9, 9.1};

  Vector<std::string> s21_vec_string{"Hello", ",", "world", "!"};
  std::vector<std::string> std_vec_string{"Hello", ",", "world", "!"};

  EXPECT_EQ(s21_vec_int.max_size(), std_vec_int.max_size());
  EXPECT_EQ(s21_vec_double.max_size(), std_vec_double.max_size());
  EXPECT_EQ(s21_vec_string.max_size(), std_vec_string.max_size());
}

TEST(Vector, VectorReserv) {
  Vector<int> v1{1, 2, 3};
  v1.reserve(20);
  ASSERT_EQ(v1.size(), 3);
  ASSERT_EQ(v1.capacity(), 20);
  ASSERT_EQ(v1.at(0), 1);
  ASSERT_EQ(v1.at(1), 2);
  ASSERT_EQ(v1.at(2), 3);

  v1.reserve(2);
  ASSERT_EQ(v1.size(), 3);
  ASSERT_EQ(v1.capacity(), 20);
  ASSERT_EQ(v1.at(0), 1);
  ASSERT_EQ(v1.at(1), 2);
  ASSERT_EQ(v1.at(2), 3);
}

TEST(Vector, VectorCapacity) {
  Vector<int> v1{1, 2, 3};
  ASSERT_EQ(v1.capacity(), 3);
  v1.reserve(20);
  ASSERT_EQ(v1.capacity(), 20);

  Vector<int> v2;
  ASSERT_EQ(v2.capacity(), 0);
}

TEST(Vector, VectorShrinkToFit) {
  Vector<int> v1;
  v1.reserve(100);
  ASSERT_EQ(v1.capacity(), 100);
  v1.shrink_to_fit();
  ASSERT_EQ(v1.capacity(), 0);
  Vector<int> v2{1, 2, 3};
  v2.shrink_to_fit();
  ASSERT_EQ(v2.capacity(), 3);
  v2.reserve(100);
  ASSERT_EQ(v2.capacity(), 100);
  v2.shrink_to_fit();
  ASSERT_EQ(v2.capacity(), 3);
}

TEST(Vector, VectorClear) {
  Vector<int> v1{1, 2, 3};
  ASSERT_EQ(v1.size(), 3);
  ASSERT_EQ(v1.capacity(), 3);
  v1.clear();
  ASSERT_EQ(v1.size(), 0);
  ASSERT_EQ(v1.capacity(), 3);

  Vector<int> v2;
  v2.clear();
  ASSERT_EQ(v2.size(), 0);
  ASSERT_EQ(v2.capacity(), 0);
}

TEST(Vector, VectorInsert) {
  Vector<int> v1{1, 2, 3, 4};
  v1.insert(v1.begin(), 3);
  ASSERT_EQ(v1.at(0), 3);
  ASSERT_EQ(v1.at(1), 1);
  ASSERT_EQ(v1.at(2), 2);
  ASSERT_EQ(v1.at(3), 3);
  ASSERT_EQ(v1.at(4), 4);

  Vector<int> v2;
  v2.insert(v2.begin(), 3);
  ;
  ASSERT_EQ(v2.at(0), 3);

  Vector<int> v3{1, 2, 3};
  ASSERT_ANY_THROW(v3.insert(v3.begin() + 5, 3));
}

TEST(Vector, VectorErase) {
  Vector<int> v1{1, 2, 3, 4};
  ASSERT_EQ(v1.size(), 4);
  v1.erase(v1.begin());
  ASSERT_EQ(v1.at(0), 2);
  ASSERT_EQ(v1.at(1), 3);
  ASSERT_EQ(v1.at(2), 4);
  ASSERT_EQ(v1.size(), 3);

  Vector<int> v2;
  ASSERT_ANY_THROW(v2.erase(v2.begin()));

  Vector<int> v3{1, 2, 3, 4};
  ASSERT_EQ(v3.size(), 4);
  v3.erase(v3.begin() + 3);
  ASSERT_EQ(v3.at(0), 1);
  ASSERT_EQ(v3.at(1), 2);
  ASSERT_EQ(v3.at(2), 3);
  ASSERT_EQ(v3.size(), 3);
}

TEST(Vector, VectorPushBack) {
  Vector<int> v1{1, 2, 3};
  ASSERT_EQ(v1.size(), 3);
  v1.push_back(4);
  ASSERT_EQ(v1.size(), 4);
  v1.push_back(5);
  ASSERT_EQ(v1.size(), 5);
  ASSERT_EQ(v1.at(0), 1);
  ASSERT_EQ(v1.at(1), 2);
  ASSERT_EQ(v1.at(2), 3);
  ASSERT_EQ(v1.at(3), 4);
  ASSERT_EQ(v1.at(4), 5);
}

TEST(Vector, VectorPopBack) {
  Vector<int> v1{1, 2, 3};
  ASSERT_EQ(v1.size(), 3);
  ASSERT_EQ(v1.capacity(), 3);
  ASSERT_EQ(v1.at(0), 1);
  ASSERT_EQ(v1.at(1), 2);
  ASSERT_EQ(v1.at(2), 3);
  v1.pop_back();
  ASSERT_EQ(v1.size(), 2);
  ASSERT_EQ(v1.capacity(), 3);
  ASSERT_EQ(v1.at(0), 1);
  ASSERT_EQ(v1.at(1), 2);
}

TEST(Vector, VectorSwap) {
  Vector<int> v1{1, 2, 3};
  Vector<int> v2{4, 5, 6, 7};
  v1.swap(v2);
  ASSERT_EQ(v1.size(), 4);
  ASSERT_EQ(v1.capacity(), 4);
  ASSERT_EQ(v1.at(0), 4);
  ASSERT_EQ(v1.at(1), 5);
  ASSERT_EQ(v1.at(2), 6);
  ASSERT_EQ(v1.at(3), 7);

  ASSERT_EQ(v2.size(), 3);
  ASSERT_EQ(v2.capacity(), 3);
  ASSERT_EQ(v2.at(0), 1);
  ASSERT_EQ(v2.at(1), 2);
  ASSERT_EQ(v2.at(2), 3);
}

TEST(Vector, VectorInsertMany) {
  Vector<int> v1{1, 2, 3};
  v1.insert_many(v1.begin(), 666, 3, 7);
  ASSERT_EQ(v1.size(), 6);
  ASSERT_EQ(v1.at(0), 666);
  ASSERT_EQ(v1.at(1), 3);
  ASSERT_EQ(v1.at(2), 7);
  ASSERT_EQ(v1.at(3), 1);
  ASSERT_EQ(v1.at(4), 2);
  ASSERT_EQ(v1.at(5), 3);

  Vector<int> v2{1, 2, 3};
  v2.insert_many(v2.end(), 666, 3, 7);
  ASSERT_EQ(v2.size(), 6);
  ASSERT_EQ(v2.at(0), 1);
  ASSERT_EQ(v2.at(1), 2);
  ASSERT_EQ(v2.at(2), 3);
  ASSERT_EQ(v2.at(3), 666);
  ASSERT_EQ(v2.at(4), 3);
  ASSERT_EQ(v2.at(5), 7);

  Vector<int> v3;
  v3.insert_many(v3.begin(), 666, 3, 7);
  ASSERT_EQ(v3.size(), 3);
  ASSERT_EQ(v3.at(0), 666);
  ASSERT_EQ(v3.at(1), 3);
  ASSERT_EQ(v3.at(2), 7);
}

TEST(Vector, VectorInsertManyBack) {
  Vector<int> v1{1, 2, 3};
  v1.insert_many_back(666, 3, 7);
  ASSERT_EQ(v1.size(), 6);
  ASSERT_EQ(v1.at(0), 1);
  ASSERT_EQ(v1.at(1), 2);
  ASSERT_EQ(v1.at(2), 3);
  ASSERT_EQ(v1.at(3), 666);
  ASSERT_EQ(v1.at(4), 3);
  ASSERT_EQ(v1.at(5), 7);

  Vector<int> v3;
  v3.insert_many_back(666, 3, 7);
  ASSERT_EQ(v3.size(), 3);
  ASSERT_EQ(v3.at(0), 666);
  ASSERT_EQ(v3.at(1), 3);
  ASSERT_EQ(v3.at(2), 7);
}
