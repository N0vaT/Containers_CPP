#include "../tests_lib.h"

TEST(List, ListEmptyConstructor) {
  List<int> l1;
  ASSERT_EQ(l1.size(), 0);
  ASSERT_ANY_THROW(l1.front());
  ASSERT_ANY_THROW(l1.back());

  List<char> l2;
  ASSERT_EQ(l2.size(), 0);
  ASSERT_ANY_THROW(l1.front());
  ASSERT_ANY_THROW(l1.back());
}

TEST(List, ListConstructorParameter) {
  List<int> l1(5);
  ASSERT_EQ(l1.size(), 5);
  ASSERT_ANY_THROW(List<int> v2(-1));
}

TEST(List, ListCopyConstructor) {
  List<int> l1;
  l1.push_back(2);
  l1.push_back(4);
  l1.push_back(16);
  List<int> l2(l1);

  ASSERT_EQ(l2.size(), 3);
  ASSERT_EQ(l2.back(), 16);
  ASSERT_EQ(l2.front(), 2);

  ASSERT_EQ(l1.size(), 3);
  ASSERT_EQ(l1.front(), 2);
  ASSERT_EQ(l1.back(), 16);
}

TEST(List, ListMoveConstructor) {
  List<int> l1;
  l1.push_back(2);
  l1.push_back(4);
  l1.push_back(16);
  List<int> l2(std::move(l1));

  ASSERT_EQ(l2.size(), 3);
  ASSERT_EQ(l2.back(), 16);
  ASSERT_EQ(l2.front(), 2);

  ASSERT_EQ(l1.size(), 0);
  ASSERT_ANY_THROW(l1.front());
  ASSERT_ANY_THROW(l1.back());
}

TEST(List, ListOperatorEqualsCopy) {
  List<int> l1{1, 2, 3};
  List<int> l2 = l1;
  ASSERT_EQ(l1.size(), 3);
  ASSERT_EQ(l1.front(), 1);
  ASSERT_EQ(l1.back(), 3);

  ASSERT_EQ(l2.size(), 3);
  ASSERT_EQ(l2.front(), 1);
  ASSERT_EQ(l2.back(), 3);
}

TEST(List, ListOperatorEqualsMove) {
  List<int> l1{1, 2, 3};
  List<int> l2 = std::move(l1);
  ASSERT_EQ(l2.size(), 3);
  ASSERT_EQ(l2.front(), 1);
  ASSERT_EQ(l2.back(), 3);
  ASSERT_EQ(l1.size(), 0);
  ASSERT_ANY_THROW(l1.front());
  ASSERT_ANY_THROW(l1.back());
}

TEST(List, ListFront) {
  List<int> l1{1, 2, 3};
  ASSERT_EQ(l1.front(), 1);
  List<int> l2;
  ASSERT_ANY_THROW(l2.front());
}

TEST(List, ListBack) {
  List<int> l1{1, 2, 3};
  ASSERT_EQ(l1.back(), 3);
  List<int> l2;
  ASSERT_ANY_THROW(l2.back());
}

TEST(List, ListEmpty) {
  List<int> l1{1, 2, 3};
  ASSERT_FALSE(l1.empty());
  List<int> l2;
  ASSERT_TRUE(l2.empty());
}

TEST(List, ListBegin) {
  List<int> l1{1, 2, 3};
  List<int>::iterator iter = l1.begin();
  ASSERT_EQ(*iter, 1);
  ++iter;
  ASSERT_EQ(*iter, 2);
  ++iter;
  ASSERT_EQ(*iter, 3);
  --iter;
  ASSERT_EQ(*iter, 2);
  ++iter;
  ASSERT_EQ(*iter, 3);
}

TEST(List, ListEnd) {
  List<int> l1{1, 2, 3};
  List<int>::iterator iter = l1.end();
  ASSERT_EQ(iter.getNode(), nullptr);
}

TEST(List, ListSize) {
  List<int> l1{1, 2, 3};
  ASSERT_EQ(l1.size(), 3);
  l1.pop_back();
  ASSERT_EQ(l1.size(), 2);
  l1.pop_back();
  ASSERT_EQ(l1.size(), 1);
  l1.pop_back();
  ASSERT_EQ(l1.size(), 0);
  List<int> l2;
  ASSERT_EQ(l2.size(), 0);
}

TEST(List, ListClear) {
  List<int> l1{1, 2, 3};
  l1.clear();
  ASSERT_EQ(l1.size(), 0);
  ASSERT_ANY_THROW(l1.front());
  ASSERT_ANY_THROW(l1.back());
  List<int> l2;
  ASSERT_EQ(l2.size(), 0);
  ASSERT_ANY_THROW(l2.front());
  ASSERT_ANY_THROW(l2.back());
}

TEST(List, ListInsert) {
  List<int> l1{1, 2, 3};
  List<int>::iterator iter = l1.begin();
  l1.insert(iter, 666);
  ASSERT_EQ(l1.size(), 4);
  ASSERT_EQ(l1.front(), 666);
  ++iter;
  ++iter;
  l1.insert(iter, 555);
  iter = l1.begin();
  ASSERT_EQ(*iter, 666);
  ++iter;
  ASSERT_EQ(*iter, 1);
  ++iter;
  ASSERT_EQ(*iter, 2);
  ++iter;
  ASSERT_EQ(*iter, 555);
  ++iter;
  ASSERT_EQ(*iter, 3);
}

TEST(List, ListErase) {
  List<int> l1{1, 2, 3};
  List<int>::iterator iter = l1.begin();
  l1.erase(iter);
  ASSERT_EQ(l1.size(), 2);
  iter = l1.begin();
  ASSERT_EQ(*iter, 2);
  ++iter;
  ASSERT_EQ(*iter, 3);

  List<int> l2{1, 2, 3};
  iter = l2.begin();
  ++iter;
  l2.erase(iter);
  ASSERT_EQ(l2.size(), 2);
  iter = l2.begin();
  ASSERT_EQ(*iter, 1);
  ++iter;
  ASSERT_EQ(*iter, 3);

  List<int> l3{1, 2, 3};
  iter = l3.begin();
  ++iter;
  ++iter;
  l3.erase(iter);
  ASSERT_EQ(l3.size(), 2);
  iter = l3.begin();
  ASSERT_EQ(*iter, 1);
  ++iter;
  ASSERT_EQ(*iter, 2);
}

TEST(List, ListPushBack) {
  List<int> l1{1, 2, 3};
  ASSERT_EQ(l1.size(), 3);
  ASSERT_EQ(l1.back(), 3);
  l1.push_back(4);
  ASSERT_EQ(l1.size(), 4);
  ASSERT_EQ(l1.back(), 4);
  l1.push_back(5);
  ASSERT_EQ(l1.size(), 5);
  ASSERT_EQ(l1.back(), 5);
  List<int> l2;
  ASSERT_EQ(l2.size(), 0);
  l2.push_back(555);
  ASSERT_EQ(l2.size(), 1);
  ASSERT_EQ(l2.front(), 555);
  ASSERT_EQ(l2.back(), 555);
}

TEST(List, ListPopBack) {
  List<int> l1{1, 2, 3};
  ASSERT_EQ(l1.size(), 3);
  ASSERT_EQ(l1.back(), 3);
  l1.pop_back();
  ASSERT_EQ(l1.end().getNode(), nullptr);
  ASSERT_EQ(l1.size(), 2);
  ASSERT_EQ(l1.back(), 2);
  l1.pop_back();
  ASSERT_EQ(l1.size(), 1);
  ASSERT_EQ(l1.back(), 1);
  ASSERT_EQ(l1.front(), 1);
  l1.pop_back();
  ASSERT_EQ(l1.size(), 0);
  ASSERT_ANY_THROW(l1.front());
  ASSERT_ANY_THROW(l1.back());
  ASSERT_ANY_THROW(l1.pop_back());
  List<int> l2;
  ASSERT_ANY_THROW(l2.pop_back());
  l2.push_back(555);
  ASSERT_EQ(l2.size(), 1);
  l2.pop_back();
  ASSERT_EQ(l2.size(), 0);
}

TEST(List, ListPushFront) {
  List<int> l1{1, 2, 3};
  ASSERT_EQ(l1.size(), 3);
  ASSERT_EQ(l1.front(), 1);
  l1.push_front(111);
  ASSERT_EQ(l1.size(), 4);
  ASSERT_EQ(l1.front(), 111);
  l1.push_front(5);
  ASSERT_EQ(l1.size(), 5);
  ASSERT_EQ(l1.front(), 5);
  List<int> l2;
  ASSERT_EQ(l2.size(), 0);
  l2.push_front(555);
  ASSERT_EQ(l2.size(), 1);
  ASSERT_EQ(l2.front(), 555);
  ASSERT_EQ(l2.back(), 555);
}

TEST(List, ListPopFront) {
  List<int> l1{1, 2, 3};
  ASSERT_EQ(l1.size(), 3);
  ASSERT_EQ(l1.front(), 1);
  l1.pop_front();
  ASSERT_EQ(l1.begin().getNode()->ptr_prev_, nullptr);
  ASSERT_EQ(l1.size(), 2);
  ASSERT_EQ(l1.front(), 2);
  l1.pop_front();
  ASSERT_EQ(l1.size(), 1);
  ASSERT_EQ(l1.front(), 3);
  ASSERT_EQ(l1.back(), 3);
  l1.pop_front();
  ASSERT_EQ(l1.size(), 0);
  ASSERT_ANY_THROW(l1.front());
  ASSERT_ANY_THROW(l1.back());
  ASSERT_ANY_THROW(l1.pop_front());
  List<int> l2;
  ASSERT_ANY_THROW(l2.pop_front());
  l2.push_front(555);
  ASSERT_EQ(l2.size(), 1);
  l2.pop_front();
  ASSERT_EQ(l2.size(), 0);
}

TEST(List, ListSwap) {
  List<int> l1{1, 2, 3, 4};
  List<int> l2{6, 7, 8};
  l1.swap(l2);

  ASSERT_EQ(l2.size(), 4);
  ASSERT_EQ(l2.front(), 1);
  ASSERT_EQ(l2.back(), 4);

  ASSERT_EQ(l1.size(), 3);
  ASSERT_EQ(l1.front(), 6);
  ASSERT_EQ(l1.back(), 8);
}

TEST(List, ListMerge) {
  List<int> l1{27, 0, 16};
  List<int> l2{-2, 7, 16};
  l1.merge(l2);

  ASSERT_EQ(l1.size(), 6);
  List<int>::iterator iter = l1.begin();
  ASSERT_EQ(*iter, -2);
  ++iter;
  ASSERT_EQ(*iter, 0);
  ++iter;
  ASSERT_EQ(*iter, 7);
  ++iter;
  ASSERT_EQ(*iter, 16);
  ++iter;
  ASSERT_EQ(*iter, 16);
  ++iter;
  ASSERT_EQ(*iter, 27);

  List<int> l3{27, 0, 16};
  List<int> l4{-2};
  l3.merge(l4);
  iter = l3.begin();
  ASSERT_EQ(l3.size(), 4);
  ASSERT_EQ(*iter, -2);
  ++iter;
  ASSERT_EQ(*iter, 0);
  ++iter;
  ASSERT_EQ(*iter, 16);
  ++iter;
  ASSERT_EQ(*iter, 27);
}

TEST(List, ListSplice) {
  List<int> l1{27, 0, 16};
  List<int> l2{-2, 7, 16};
  List<int>::const_iterator iter = l1.begin();
  l1.splice(iter, l2);
  iter = l1.begin();
  ASSERT_EQ(l1.size(), 6);
  ASSERT_EQ(*iter, -2);
  ++iter;
  ASSERT_EQ(*iter, 7);
  ++iter;
  ASSERT_EQ(*iter, 16);
  ++iter;
  ASSERT_EQ(*iter, 27);
  ++iter;
  ASSERT_EQ(*iter, 0);
  ++iter;
  ASSERT_EQ(*iter, 16);

  List<int> l3{27, 0, 16};
  List<int> l4{-2, 7};
  List<int>::const_iterator iter2 = l3.begin();
  ++iter2;
  l3.splice(iter2, l4);
  iter2 = l3.begin();
  ASSERT_EQ(l3.size(), 5);
  ASSERT_EQ(*iter2, 27);
  ++iter2;
  ASSERT_EQ(*iter2, -2);
  ++iter2;
  ASSERT_EQ(*iter2, 7);
  ++iter2;
  ASSERT_EQ(*iter2, 0);
  ++iter2;
  ASSERT_EQ(*iter2, 16);

  List<int> l5{27, 0, 16};
  List<int> l6{-2, 7};
  List<int>::const_iterator iter3 = l5.begin();
  ++iter3;
  ++iter3;
  l5.splice(iter3, l6);
  iter3 = l5.begin();
  ASSERT_EQ(l5.size(), 5);
  ASSERT_EQ(*iter3, 27);
  ++iter3;
  ASSERT_EQ(*iter3, 0);
  ++iter3;
  ASSERT_EQ(*iter3, -2);
  ++iter3;
  ASSERT_EQ(*iter3, 7);
  ++iter3;
  ASSERT_EQ(*iter3, 16);
}

TEST(List, ListReverse) {
  List<int> l1{27, 0, 16};
  l1.reverse();
  List<int>::iterator iter = l1.begin();
  ASSERT_EQ(l1.size(), 3);
  ASSERT_EQ(*iter, 16);
  ++iter;
  ASSERT_EQ(*iter, 0);
  ++iter;
  ASSERT_EQ(*iter, 27);

  List<int> l3{27, 0};
  l3.reverse();
  List<int>::iterator iter2 = l3.begin();
  ASSERT_EQ(l3.size(), 2);
  ASSERT_EQ(*iter2, 0);
  ++iter2;
  ASSERT_EQ(*iter2, 27);

  List<int> l5;
  l5.reverse();
  List<int>::const_iterator iter3 = l5.begin();
  iter3 = l5.begin();
  ASSERT_EQ(l5.size(), 0);
}

TEST(List, ListUnique) {
  List<int> l1{27, 0, 0, 0, 16};
  l1.unique();
  List<int>::iterator iter = l1.begin();
  ASSERT_EQ(l1.size(), 3);
  ASSERT_EQ(*iter, 27);
  ++iter;
  ASSERT_EQ(*iter, 0);
  ++iter;
  ASSERT_EQ(*iter, 16);

  List<int> l2{27, 0, 16};
  l2.unique();
  iter = l2.begin();
  ASSERT_EQ(l2.size(), 3);
  ASSERT_EQ(*iter, 27);
  ++iter;
  ASSERT_EQ(*iter, 0);
  ++iter;
  ASSERT_EQ(*iter, 16);

  List<int> l3{27, 27, 0, 16, 16};
  l3.unique();
  iter = l3.begin();
  ASSERT_EQ(l3.size(), 3);
  ASSERT_EQ(*iter, 27);
  ++iter;
  ASSERT_EQ(*iter, 0);
  ++iter;
  ASSERT_EQ(*iter, 16);

  List<int> l4;
  l4.unique();
  ASSERT_EQ(l4.size(), 0);

  List<int> l5{27, 0, 16};
  l5.unique();
  iter = l5.begin();
  ASSERT_EQ(l5.size(), 3);
  ASSERT_EQ(*iter, 27);
  ++iter;
  ASSERT_EQ(*iter, 0);
  ++iter;
  ASSERT_EQ(*iter, 16);
}

TEST(List, ListSort) {
  List<int> l1{27, 0, 16, -1, 3, 1};
  l1.sort();

  ASSERT_EQ(l1.size(), 6);
  List<int>::iterator iter = l1.begin();
  ASSERT_EQ(*iter, -1);
  ++iter;
  ASSERT_EQ(*iter, 0);
  ++iter;
  ASSERT_EQ(*iter, 1);
  ++iter;
  ASSERT_EQ(*iter, 3);
  ++iter;
  ASSERT_EQ(*iter, 16);
  ++iter;
  ASSERT_EQ(*iter, 27);

  List<int> l2{27};
  l2.sort();
  ASSERT_EQ(l2.size(), 1);
  ASSERT_EQ(l2.front(), 27);

  List<int> l3;
  l3.sort();
  ASSERT_EQ(l3.size(), 0);
  ASSERT_ANY_THROW(l3.front());
}

TEST(List, ListInsertMany) {
  List<int> v1{1, 2, 3};
  v1.insert_many(v1.begin(), 666, 3, 7);
  ASSERT_EQ(v1.size(), 6);
  List<int>::iterator iter = v1.begin();
  ASSERT_EQ(*iter, 666);
  ++iter;
  ASSERT_EQ(*iter, 3);
  ++iter;
  ASSERT_EQ(*iter, 7);
  ++iter;
  ASSERT_EQ(*iter, 1);
  ++iter;
  ASSERT_EQ(*iter, 2);
  ++iter;
  ASSERT_EQ(*iter, 3);

  List<int> v2{1, 2, 3};
  iter = v2.begin();
  ++iter;
  ++iter;
  v2.insert_many(iter, 666, 3, 7);
  iter = v2.begin();
  ASSERT_EQ(v2.size(), 6);
  ASSERT_EQ(*iter, 1);
  ++iter;
  ASSERT_EQ(*iter, 2);
  ++iter;
  ASSERT_EQ(*iter, 666);
  ++iter;
  ASSERT_EQ(*iter, 3);
  ++iter;
  ASSERT_EQ(*iter, 7);
  ++iter;
  ASSERT_EQ(*iter, 3);

  List<int> v3;
  v3.insert_many(v3.begin(), 666, 3, 7);
  ASSERT_EQ(v3.size(), 3);
  iter = v3.begin();
  ASSERT_EQ(*iter, 666);
  ++iter;
  ASSERT_EQ(*iter, 3);
  ++iter;
  ASSERT_EQ(*iter, 7);
}

TEST(List, ListInsertManyBack) {
  List<int> v1{1, 2, 3};
  v1.insert_many_back(666, 3, 7);
  ASSERT_EQ(v1.size(), 6);
  List<int>::iterator iter = v1.begin();
  ASSERT_EQ(*iter, 1);
  ++iter;
  ASSERT_EQ(*iter, 2);
  ++iter;
  ASSERT_EQ(*iter, 3);
  ++iter;
  ASSERT_EQ(*iter, 666);
  ++iter;
  ASSERT_EQ(*iter, 3);
  ++iter;
  ASSERT_EQ(*iter, 7);

  List<int> v3;
  v3.insert_many_back(666, 3, 7);
  ASSERT_EQ(v3.size(), 3);
  iter = v3.begin();
  ASSERT_EQ(*iter, 666);
  ++iter;
  ASSERT_EQ(*iter, 3);
  ++iter;
  ASSERT_EQ(*iter, 7);
}

TEST(List, ListInsertManyFront) {
  List<int> v1{1, 2, 3};
  v1.insert_many_front(666, 3, 7);
  ASSERT_EQ(v1.size(), 6);
  List<int>::iterator iter = v1.begin();
  ASSERT_EQ(*iter, 666);
  ++iter;
  ASSERT_EQ(*iter, 3);
  ++iter;
  ASSERT_EQ(*iter, 7);
  ++iter;
  ASSERT_EQ(*iter, 1);
  ++iter;
  ASSERT_EQ(*iter, 2);
  ++iter;
  ASSERT_EQ(*iter, 3);

  List<int> v3;
  v3.insert_many_front(666, 3, 7);
  ASSERT_EQ(v3.size(), 3);
  iter = v3.begin();
  ASSERT_EQ(*iter, 666);
  ++iter;
  ASSERT_EQ(*iter, 3);
  ++iter;
  ASSERT_EQ(*iter, 7);
}
