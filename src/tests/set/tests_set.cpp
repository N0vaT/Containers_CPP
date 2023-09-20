#include "../tests_lib.h"

TEST(Set, SetInit) {
  Set<int> set;
  ASSERT_EQ(set.size(), 0);
  ASSERT_EQ(set.empty(), true);

  set.insert(1);
  ASSERT_EQ(set.size(), 1);

  Set<int> set1(set);

  Set<int> set2 = std::move(set);
  ASSERT_EQ(set2.size(), 1);
}

TEST(Set, SetSwap) {
  Set<int> set({1, 2, 4, 6, 8});
  Set<int> set1({3, 5, 7});
  ASSERT_EQ(set.size(), 5);
  ASSERT_EQ(set1.size(), 3);

  set.swap(set1);

  ASSERT_EQ(set.size(), 3);
  ASSERT_EQ(set1.size(), 5);
}

TEST(Set, SetIterator) {
  Set<int> set({1, 2, 4, 6, 8, 10, 12, 14, 16});
  ASSERT_EQ(set.size(), 9);

  typename Tree<int>::Iterator iter = ++set.begin();
  ASSERT_EQ(*iter, 1);
  ++iter;
  ASSERT_EQ(*iter, 2);

  typename Tree<int>::Iterator iter1 = --set.end();
  ASSERT_EQ(*iter1, 16);

  typename Tree<int>::Iterator iter2 = set.find(12);
  ASSERT_EQ(*iter2, 12);

  iter2++;
  iter2++;
  ASSERT_EQ(iter1 == iter2, true);
}

TEST(Set, SetContains) {
  Set<int> set({1, 2, 4, 6, 8, 10, 12, 14, 16});
  ASSERT_EQ(set.size(), 9);

  ASSERT_EQ(set.contains(6), true);
  ASSERT_EQ(set.contains(7), false);
}

TEST(Set, SetInsertDuplicate) {
  Set<int> set({1, 2, 4, 6, 8, 10});
  ASSERT_EQ(set.size(), 6);

  std::pair<typename Tree<int>::Iterator, bool> pair = set.insert(4);
  ASSERT_EQ(*pair.first, 4);
  ASSERT_EQ(pair.second, false);
}

TEST(Set, SetClear) {
  Set<int> set({1, 2, 4, 6, 8, 10});
  ASSERT_EQ(set.size(), 6);

  set.clear();
  ASSERT_EQ(set.empty(), true);
}

TEST(Set, SetMaxSize) {
  Set<int> set({1, 2, 4, 6, 8, 10});
  ASSERT_EQ(set.max_size(), 2305843009213693951);
}

TEST(Set, SetErase) {
  Set<int> set({1, 2, 4, 6, 8, 10});
  ASSERT_EQ(set.contains(4), true);

  Tree<int>::Iterator iter = ++set.begin();
  ++iter;
  ++iter;
  ASSERT_EQ(*iter, 4);

  set.erase(iter);
  ASSERT_EQ(set.contains(4), false);
}

TEST(Set, SetMerge) {
  Set<int> set({1, 2, 4, 6, 8, 10});
  Set<int> set1({1, 2, 3, 6, 9});

  set.merge(set1);
  ASSERT_EQ(set.size(), 8);

  ASSERT_EQ(set.contains(1), true);
  ASSERT_EQ(set.contains(3), true);
  ASSERT_EQ(set.contains(4), true);
}

TEST(Set, SetIteratorDecrement) {
  Set<int> set({1, 2, 4, 6, 8, 10});

  Set<int>::iterator iter = --set.end();
  ASSERT_EQ(*iter, 10);
  iter--;
  ASSERT_EQ(*iter, 8);
  --iter;
  ASSERT_EQ(*iter, 6);
}

TEST(Set, SetIteratorEnd) {
  Set<int> set({1, 2, 3, 4, 5});

  Set<int>::iterator iter = --set.end();
  ASSERT_EQ(*iter, 5);
  iter++;
  ASSERT_ANY_THROW(++iter);
  iter--;
  ASSERT_EQ(*iter, 5);
}

TEST(Set, SetOperator) {
  Set<int> set({1, 2, 3, 4, 5});
  Set<int> set1({6, 7, 8, 9});

  set = set1;
  ASSERT_EQ(set.size(), 4);
}

TEST(Set, SetIteratorStart) {
  Set<int> set({1, 2, 3, 4, 5});

  Set<int>::iterator iter = ++set.begin();
  ASSERT_EQ(*iter, 1);
  --iter;
  ASSERT_ANY_THROW(--iter);
  ++iter;
  ASSERT_EQ(*iter, 1);
}

TEST(Set, SetInsertMany) {
  Set<int> set({1, 2, 4, 6, 8});
  set.insert_many(3, 5, 6, 7);

  ASSERT_EQ(set.size(), 8);
}
