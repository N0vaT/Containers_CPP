#include <queue>

#include "../tests_lib.h"

TEST(Queue, QueueEmptyConstructor) {
  Queue<int> a1;
  std::queue<int> a2;
  ASSERT_EQ(a1.size(), a2.size());

  Queue<char> a3;
  std::queue<char> a4;
  ASSERT_EQ(a3.size(), a4.size());
}

TEST(Queue, QueueConstructorInitializerList) {
  Queue<int> a1{1, 2, 3};
  ASSERT_EQ(a1.size(), 3);
  ASSERT_EQ(a1.front(), 1);
  a1.pop();
  ASSERT_EQ(a1.front(), 2);
  a1.pop();
  ASSERT_EQ(a1.front(), 3);

  Queue<char> a2{'a', 'b', 'c'};
  ASSERT_EQ(a2.size(), 3);
  ASSERT_EQ(a2.front(), 'a');
  a2.pop();
  ASSERT_EQ(a2.front(), 'b');
  a2.pop();
  ASSERT_EQ(a2.front(), 'c');
}

TEST(Queue, QueueCopyConstructor) {
  Queue<int> a1{1, 2, 3};
  Queue<int> a2(a1);

  ASSERT_EQ(a2.size(), 3);
  ASSERT_EQ(a2.front(), 1);
  a2.pop();
  ASSERT_EQ(a2.front(), 2);
  a2.pop();
  ASSERT_EQ(a2.front(), 3);

  Queue<int> a3;
  Queue<int> a4(a3);
  ASSERT_EQ(a4.size(), 0);
}

TEST(Queue, QueueMoveConstructor) {
  Queue<int> a1{1, 2, 3};
  Queue<int> a2(std::move(a1));

  ASSERT_EQ(a2.size(), 3);
  ASSERT_EQ(a2.front(), 1);
  a2.pop();
  ASSERT_EQ(a2.front(), 2);
  a2.pop();
  ASSERT_EQ(a2.front(), 3);

  ASSERT_EQ(a1.size(), 0);
}

TEST(Queue, QueueOperatorEqualsCopy) {
  Queue<int> a1{1, 2, 3};
  Queue<int> a2 = a1;
  ASSERT_EQ(a2.size(), 3);
  ASSERT_EQ(a2.front(), 1);
  a2.pop();
  ASSERT_EQ(a2.front(), 2);
  a2.pop();
  ASSERT_EQ(a2.front(), 3);

  ASSERT_EQ(a1.size(), 3);
  ASSERT_EQ(a1.front(), 1);
  a1.pop();
  ASSERT_EQ(a1.front(), 2);
  a1.pop();
  ASSERT_EQ(a1.front(), 3);
}

TEST(Queue, QueueOperatorEqualsMove) {
  Queue<int> a1{1, 2, 3};
  Queue<int> a2 = std::move(a1);
  ASSERT_EQ(a2.size(), 3);
  ASSERT_EQ(a2.front(), 1);
  a2.pop();
  ASSERT_EQ(a2.front(), 2);
  a2.pop();
  ASSERT_EQ(a2.front(), 3);

  ASSERT_EQ(a1.size(), 0);
}

TEST(Queue, QueueFront) {
  Queue<int> a1{1, 2, 3};
  ASSERT_EQ(a1.front(), 1);
  a1.pop();
  ASSERT_EQ(a1.front(), 2);
  a1.pop();
  ASSERT_EQ(a1.front(), 3);
  a1.pop();
  ASSERT_ANY_THROW(a1.front());
}

TEST(Queue, QueueBack) {
  Queue<int> a1{1, 2, 3};
  ASSERT_EQ(a1.back(), 3);
  a1.pop();
  ASSERT_EQ(a1.back(), 3);
  a1.pop();
  ASSERT_EQ(a1.back(), 3);
  a1.pop();
  ASSERT_ANY_THROW(a1.back());
  Queue<int> a2;
  ASSERT_ANY_THROW(a2.back());
}

TEST(Queue, QueueEmpty) {
  Queue<int> a1{1, 2, 3};
  ASSERT_FALSE(a1.empty());
  Queue<int> a2;
  ASSERT_TRUE(a2.empty());
}

TEST(Queue, QueueSize) {
  Queue<int> a1{1, 2, 3};
  ASSERT_EQ(a1.size(), 3);
  Queue<int> a2;
  ASSERT_EQ(a2.size(), 0);
}

TEST(Queue, QueuePush) {
  Queue<int> a1;
  a1.push(2);
  ASSERT_EQ(a1.front(), 2);
  a1.push(666);
  ASSERT_EQ(a1.back(), 666);
  a1.push(777);
  ASSERT_EQ(a1.back(), 777);

  Queue<int> a2{1, 2, 3};
  a2.push(666);
  ASSERT_EQ(a2.back(), 666);
}

TEST(Queue, QueuePop) {
  Queue<int> a1{1, 2, 666};
  ASSERT_EQ(a1.front(), 1);
  a1.pop();
  ASSERT_EQ(a1.front(), 2);
  a1.pop();
  ASSERT_EQ(a1.front(), 666);
  a1.pop();
  ASSERT_ANY_THROW(a1.pop());

  Queue<int> a2;
  ASSERT_ANY_THROW(a2.pop());
}

TEST(Queue, QueueSwap) {
  Queue<int> a1{1, 2, 3};
  Queue<int> a2{4, 5, 6, 7};
  a1.swap(a2);

  ASSERT_EQ(a1.size(), 4);
  ASSERT_EQ(a1.front(), 4);
  a1.pop();
  ASSERT_EQ(a1.front(), 5);
  a1.pop();
  ASSERT_EQ(a1.front(), 6);
  ASSERT_EQ(a1.back(), 7);

  ASSERT_EQ(a2.size(), 3);
  ASSERT_EQ(a2.front(), 1);
  a2.pop();
  ASSERT_EQ(a2.front(), 2);
  ASSERT_EQ(a2.back(), 3);
  Queue<int> a3;
  Queue<int> a4{4, 5, 6, 7};
  a3.swap(a4);
  ASSERT_EQ(a3.size(), 4);
  ASSERT_EQ(a3.front(), 4);
  a3.pop();
  ASSERT_EQ(a3.front(), 5);
  a3.pop();
  ASSERT_EQ(a3.front(), 6);
  ASSERT_EQ(a3.back(), 7);
  ASSERT_EQ(a4.size(), 0);
  Queue<int> a5;
  Queue<int> a6;
  a5.swap(a6);
  ASSERT_EQ(a5.size(), 0);
  ASSERT_EQ(a6.size(), 0);
}

TEST(Queue, QueuensertManyBack) {
  Queue<int> v1{1, 2, 3};
  v1.insert_many_back(666, 3, 7);
  ASSERT_EQ(v1.size(), 6);
  ASSERT_EQ(v1.front(), 1);
  v1.pop();
  ASSERT_EQ(v1.front(), 2);
  v1.pop();
  ASSERT_EQ(v1.front(), 3);
  v1.pop();
  ASSERT_EQ(v1.front(), 666);
  v1.pop();
  ASSERT_EQ(v1.front(), 3);
  v1.pop();
  ASSERT_EQ(v1.front(), 7);

  Queue<int> v3;
  v3.insert_many_back(666, 3, 7);
  ASSERT_EQ(v3.size(), 3);
  ASSERT_EQ(v3.front(), 666);
  v3.pop();
  ASSERT_EQ(v3.front(), 3);
  v3.pop();
  ASSERT_EQ(v3.front(), 7);
}
