#include "../tests_libplus.h"

TEST(Multiset, MultisetInit) {
  Multiset<int> mset;
  ASSERT_EQ(mset.empty(), true);
  ASSERT_EQ(mset.size(), 0);

  mset.insert(3);
  ASSERT_EQ(mset.empty(), false);
  ASSERT_EQ(mset.size(), 1);
  ASSERT_EQ(mset.contains(3), true);

  mset.insert(4);
  mset.insert(3);
  ASSERT_EQ(mset.empty(), false);
  ASSERT_EQ(mset.size(), 3);
  ASSERT_EQ(mset.contains(3), true);
}

TEST(Multiset, MultisetInitializerListInit) {
  Multiset<int> mset({1, 2, 3, 3, 4, 6, 8, 7, 7, 7, 7});
  ASSERT_EQ(mset.empty(), false);
  ASSERT_EQ(mset.size(), 11);
  ASSERT_EQ(mset.contains(3), true);
  ASSERT_EQ(mset.contains(7), true);
  ASSERT_EQ(mset.contains(5), false);
}

TEST(Multiset, MultisetMaxSize) {
  Multiset<int> mset({1, 2, 3, 3, 4, 6, 8, 7, 7, 7, 7});
  ASSERT_EQ(mset.max_size(), 2305843009213693951);
}

TEST(Multiset, MultisetErase) {
  Multiset<int> mset({1, 2, 3, 3, 4, 6, 8, 7, 7, 7, 7});
  ASSERT_EQ(mset.contains(4), true);

  Tree<int>::Iterator iter = mset.begin();
  ++iter;
  ++iter;
  ++iter;
  ++iter;
  ++iter;
  ASSERT_EQ(*iter, 4);

  mset.erase(iter);
  ASSERT_EQ(mset.contains(4), false);
}

TEST(Multiset, MultisetCountZero) {
  Multiset<int> mset({3});
  ASSERT_EQ(mset.count(1), 0);
}

TEST(Multiset, MultisetCount) {
  Multiset<int> mset({1, 2, 3, 3, 4, 6, 8, 7, 7, 7, 7});
  ASSERT_EQ(mset.count(1), 1);
  ASSERT_EQ(mset.count(3), 2);
}

TEST(Multiset, MultisetFind) {
  Multiset<int> mset({1, 2, 3, 3, 4, 6, 8, 7, 7, 7, 7});
  Multiset<int>::iterator iter = mset.find(3);
  ASSERT_EQ(*iter, 3);
  ++iter;
  ASSERT_EQ(*iter, 3);
}

TEST(Multiset, MultisetFindException) {
  Multiset<int> mset({1, 2, 3, 3, 4, 6, 8, 7, 7, 7, 7});
  ASSERT_ANY_THROW(mset.find(9));
}

TEST(Multiset, MultisetEqualRange) {
  Multiset<int> mset({1, 2, 3, 3, 4, 6, 8, 7, 7, 7, 7});
  std::pair<typename Multiset<int>::iterator, typename Multiset<int>::iterator>
      pair = mset.equal_range(3);

  ASSERT_EQ(*pair.first, 3);
  ASSERT_EQ(*pair.second, 3);
  ASSERT_EQ(pair.first != pair.second, true);
}

TEST(Multiset, MultisetLowerBound) {
  Multiset<int> mset({1, 2, 3, 3, 4, 6, 8, 7, 7, 7, 7});
  Multiset<int>::iterator iter = mset.lower_bound(5);
  ASSERT_EQ(*iter, 6);

  Multiset<int>::iterator iter1 = mset.lower_bound(3);
  ASSERT_EQ(*iter1, 3);
  --iter1;
  ASSERT_EQ(*iter1, 2);
}

TEST(Multiset, MultisetUpperBound) {
  Multiset<int> mset({1, 2, 3, 3, 4, 6, 8, 7, 7, 7, 7});
  Multiset<int>::iterator iter = mset.upper_bound(5);
  ASSERT_EQ(*iter, 4);

  Multiset<int>::iterator iter1 = mset.upper_bound(3);
  ASSERT_EQ(*iter1, 3);
  ++iter1;
  ASSERT_EQ(*iter1, 4);
}

TEST(Multiset, MultisetInsertMultiple) {
  Multiset<int> mset({1, 2, 3, 3, 4, 6, 8, 7, 7, 7, 7});
  mset.insert_many(3, 5, 9);

  ASSERT_EQ(mset.contains(3), true);
  ASSERT_EQ(mset.contains(5), true);
  ASSERT_EQ(mset.contains(9), true);
}

TEST(Multiset, MultisetClear) {
  Multiset<int> mset({1, 2, 3, 3, 4, 6, 8, 7, 7, 7, 7});
  mset.clear();

  ASSERT_EQ(mset.empty(), true);
}

TEST(Multiset, MultisetSwap) {
  Multiset<int> mset({2, 4, 6, 8});
  Multiset<int> mset1({1, 3, 5, 7});
  mset.swap(mset1);

  ASSERT_EQ(mset.contains(2), false);
  ASSERT_EQ(mset.contains(3), true);

  ASSERT_EQ(mset1.contains(2), true);
  ASSERT_EQ(mset1.contains(3), false);
}

TEST(Multiset, MultisetMerge) {
  Multiset<int> mset({2, 4, 6, 8});
  Multiset<int> mset1({1, 3, 5, 7});
  mset.merge(mset1);

  ASSERT_EQ(mset.contains(2), true);
  ASSERT_EQ(mset.contains(3), true);
}

TEST(Multiset, MultisetCopy) {
  Multiset<int> mset({2, 4, 6, 8});
  Multiset<int> mset1(mset);

  ASSERT_EQ(mset1.size(), 4);
  ASSERT_EQ(mset1.contains(4), true);
}

TEST(Multiset, MultisetMove) {
  Multiset<int> mset({2, 4, 6, 8});
  Multiset<int> mset1 = std::move(mset);

  ASSERT_EQ(mset1.size(), 4);
  ASSERT_EQ(mset1.contains(4), true);
}

TEST(Multiset, MultisetAssign) {
  Multiset<int> mset({2, 4, 6, 8});
  Multiset<int> mset1({3, 5, 7});

  mset = mset1;

  ASSERT_EQ(mset.size(), 3);
  ASSERT_EQ(mset.contains(4), false);
  ASSERT_EQ(mset.contains(5), true);
}

TEST(Multiset, MultisetIteratorEnd) {
  Multiset<int> mset({2, 4, 6, 8});
  Multiset<int>::iterator iter = mset.end();
  --iter;
  ASSERT_EQ(*iter, 8);
}

TEST(Multiset, MultisetEqualRangeException) {
  Multiset<int> mset({2, 4, 6, 8});
  ASSERT_ANY_THROW(mset.equal_range(7));
}