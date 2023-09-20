#include "../tests_lib.h"

TEST(Stack, StackInit) {
  Stack<int> s1;
  s1.push(2);
  s1.push(5);
  ASSERT_EQ(s1.top(), 5);
  s1.pop();
  ASSERT_EQ(s1.top(), 2);
  s1.pop();
  ASSERT_ANY_THROW(s1.pop());
  ASSERT_ANY_THROW(s1.top());
  s1.push(3);
  s1.push(4);

  ASSERT_EQ(s1.max_size(), 2305843009213693951);
}

TEST(Stack, StackCopyConstructor) {
  Stack<int> src;
  src.push(2);
  src.push(4);
  src.push(16);
  Stack<int> dst(src);

  ASSERT_EQ(src.top(), 16);
  src.pop();
  ASSERT_EQ(src.top(), 4);
  src.pop();
  ASSERT_EQ(src.top(), 2);
  src.pop();
  ASSERT_ANY_THROW(src.pop());

  ASSERT_EQ(dst.top(), 16);
  dst.pop();
  ASSERT_EQ(dst.top(), 4);
  dst.pop();
  ASSERT_EQ(dst.top(), 2);
  dst.pop();
  ASSERT_ANY_THROW(dst.pop());
}

TEST(Stack, StackMoveConstructor) {
  Stack<int> src;
  src.push(2);
  src.push(4);
  src.push(16);
  Stack<int> dst = std::move(src);

  ASSERT_ANY_THROW(src.pop());

  ASSERT_EQ(dst.top(), 16);
  dst.pop();
  ASSERT_EQ(dst.top(), 4);
  dst.pop();
  ASSERT_EQ(dst.top(), 2);
  dst.pop();
  ASSERT_ANY_THROW(dst.pop());
}

TEST(Stack, StackMoveOperator) {
  Stack<int> src;
  src.push(2);
  src.push(4);
  src.push(16);
  Stack<int> dst;
  dst = std::move(src);

  ASSERT_ANY_THROW(src.pop());

  ASSERT_EQ(dst.top(), 16);
  dst.pop();
  ASSERT_EQ(dst.top(), 4);
  dst.pop();
  ASSERT_EQ(dst.top(), 2);
  dst.pop();
  ASSERT_ANY_THROW(dst.pop());
}

TEST(Stack, StackSizeGetter) {
  Stack<int> s;
  ASSERT_EQ(s.size(), 0);
  s.push(4);
  ASSERT_EQ(s.size(), 1);
  s.push(16);
  ASSERT_EQ(s.size(), 2);

  s.pop();
  ASSERT_EQ(s.size(), 1);
  s.pop();
  ASSERT_EQ(s.size(), 0);
}

TEST(Stack, StackEmptyFunction) {
  Stack<int> s;
  ASSERT_EQ(s.empty(), true);
  s.push(4);
  ASSERT_EQ(s.empty(), false);
  s.push(16);
  ASSERT_EQ(s.empty(), false);

  s.pop();
  ASSERT_EQ(s.empty(), false);
  s.pop();
  ASSERT_EQ(s.empty(), true);
}

TEST(Stack, StackSwapMethod) {
  Stack<int> s1;
  s1.push(2);
  s1.push(4);
  s1.push(16);

  Stack<int> s2;
  s2.push(3);
  s2.push(9);

  s1.swap(s2);

  ASSERT_EQ(s1.size(), 2);
  ASSERT_EQ(s2.size(), 3);

  ASSERT_EQ(s1.top(), 9);
  s1.pop();
  ASSERT_EQ(s1.top(), 3);
  s1.pop();
  ASSERT_ANY_THROW(s1.pop());

  ASSERT_EQ(s2.top(), 16);
  s2.pop();
  ASSERT_EQ(s2.top(), 4);
  s2.pop();
  ASSERT_EQ(s2.top(), 2);
  s2.pop();
  ASSERT_ANY_THROW(s2.pop());
}

TEST(Stack, StackInitializerListConstructor) {
  Stack<int> s({1, 2, 4, 16});
  ASSERT_EQ(s.size(), 4);

  ASSERT_EQ(s.top(), 16);
  s.pop();
  ASSERT_EQ(s.top(), 4);
  s.pop();
  ASSERT_EQ(s.top(), 2);
  s.pop();
  ASSERT_EQ(s.top(), 1);
  s.pop();
  ASSERT_ANY_THROW(s.pop());
}

TEST(Stack, StackPushMany) {
  Stack<int> s({1, 2, 3});
  ASSERT_EQ(s.size(), 3);

  s.insert_many_front(4, 5, 6);
  ASSERT_EQ(s.size(), 6);
  ASSERT_EQ(s.top(), 6);
}
