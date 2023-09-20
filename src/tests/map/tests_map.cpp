#include "../tests_lib.h"

TEST(Map, MapInit) {
  Map<int, double> map;
  ASSERT_EQ(map.size(), 0);
  ASSERT_EQ(map.empty(), true);

  ASSERT_ANY_THROW(map.at(9));
  ASSERT_ANY_THROW(map[9]);

  auto pair = map.insert(Entry<int, double>(9, 3.14));
  ASSERT_EQ(pair.second, true);
  ASSERT_EQ(pair.first->getKey(), 9);
  ASSERT_EQ(pair.first->getValue(), 3.14);
  ASSERT_EQ(map.size(), 1);
  ASSERT_EQ(map.empty(), false);

  pair = map.insert(Entry<int, double>(18, 92.35));
  ASSERT_EQ(pair.second, true);
  ASSERT_EQ(pair.first->getKey(), 18);
  ASSERT_EQ(pair.first->getValue(), 92.35);
  ASSERT_EQ(map.size(), 2);
  ASSERT_EQ(map.empty(), false);

  pair = map.insert(Entry<int, double>(18, 234.0));
  ASSERT_EQ(pair.second, false);
  ASSERT_EQ(pair.first->getKey(), 18);
  ASSERT_EQ(pair.first->getValue(), 92.35);
  ASSERT_EQ(map.size(), 2);
  ASSERT_EQ(map.empty(), false);

  pair = map.insert(26, 0.0034);
  ASSERT_EQ(pair.second, true);
  ASSERT_EQ(pair.first->getKey(), 26);
  ASSERT_EQ(pair.first->getValue(), 0.0034);
  ASSERT_EQ(map.size(), 3);
  ASSERT_EQ(map.empty(), false);

  pair = map.insert_or_assign(26, 1.5);
  ASSERT_EQ(pair.second, false);
  ASSERT_EQ(pair.first->getKey(), 26);
  ASSERT_EQ(pair.first->getValue(), 1.5);
  ASSERT_EQ(map.size(), 3);
  ASSERT_EQ(map.empty(), false);
}

TEST(Map, MapSwap) {
  Map<int, double> map1;
  map1.insert(1, 100.0);
  map1.insert(2, 200.0);
  map1.insert(3, 300.0);
  map1.insert(4, 400.0);
  ASSERT_EQ(map1.at(3), 300.0);
  ASSERT_EQ(map1[3], 300.0);

  Map<int, double> map2;
  map2.insert(11, -100.0);
  map2.insert(12, -200.0);
  map2.insert(13, -300.0);
  map2.insert(14, -400.0);

  map1.swap(map2);

  ASSERT_EQ(map1.size(), 4);
  ASSERT_EQ(map1.at(11), -100.0);
  ASSERT_EQ(map1.at(12), -200.0);
  ASSERT_EQ(map1.at(13), -300.0);
  ASSERT_EQ(map1.at(14), -400.0);
  ASSERT_ANY_THROW(map1.at(2));

  ASSERT_EQ(map2.size(), 4);
  ASSERT_EQ(map2.at(1), 100.0);
  ASSERT_EQ(map2.at(2), 200.0);
  ASSERT_EQ(map2.at(3), 300.0);
  ASSERT_EQ(map2.at(4), 400.0);
  ASSERT_ANY_THROW(map2.at(13));
}

TEST(Map, MapInitializerListConstructor) {
  Map<int, double> map({{1, 100.2}, {2, 200.314}});
  ASSERT_EQ(map.size(), 2);
  auto iter = map.begin();
  ++iter;
  Entry<int, double> entry = *iter;
  ASSERT_EQ(entry.getKey(), 1);
  ASSERT_EQ(entry.getValue(), 100.2);
  iter++;
  Entry<int, double> entry1 = *iter;
  ASSERT_EQ(entry1.getKey(), 2);
  ASSERT_EQ(entry1.getValue(), 200.314);
}

TEST(Map, MapMoveConstructor) {
  Map<int, double> map({{1, 100.2}, {2, 200.314}});
  ASSERT_EQ(map.size(), 2);

  Map<int, double> map1 = std::move(map);
  ASSERT_EQ(map1.size(), 2);
  ASSERT_EQ(map1.contains(2), true);
}

TEST(Map, MapClear) {
  Map<int, double> map({{1, 100.2}, {2, 200.314}});
  map.clear();

  ASSERT_EQ(map.size(), 0);
  ASSERT_EQ(map.contains(2), false);
}

TEST(Map, MapMaxSize) {
  Map<int, double> map({{1, 100.2}, {2, 200.314}});

  ASSERT_EQ(map.max_size(), 576460752303423487);
}

TEST(Map, MapErase) {
  Map<int, double> map({{1, 100.2}, {2, 200.314}, {5, 124.432}});

  ASSERT_EQ(map.size(), 3);
  ASSERT_EQ(map.contains(1), true);
  ASSERT_EQ(map.contains(2), true);
  ASSERT_EQ(map.contains(5), true);

  Tree<Entry<int, double>>::Iterator iter = map.begin();
  ++iter;
  ++iter;
  ASSERT_EQ(iter->getKey(), 2);

  map.erase(iter);

  ASSERT_EQ(map.contains(1), true);
  ASSERT_EQ(map.contains(2), false);
  ASSERT_EQ(map.contains(5), true);
}

TEST(Map, MapEndIterator) {
  Map<int, double> map({{1, 100.2}, {2, 200.314}});
  Map<int, double>::iterator iter = map.end();
  --iter;
  ASSERT_EQ(iter->getValue(), 200.314);
}

TEST(Map, MapMerge) {
  Map<int, double> map({{1, 100.2}, {2, 200.314}});
  Map<int, double> map1({{3, 300.2}, {4, 500.314}});

  map.merge(map1);

  ASSERT_EQ(map.size(), 4);
  ASSERT_EQ(map[3], 300.2);
}

TEST(Map, MapAssign) {
  Map<int, double> map({{1, 100.2}, {2, 200.314}, {5, 124.432}});
  Map<int, double> map1({{4, 0.0}});

  map = map1;

  ASSERT_EQ(map.size(), 1);
  ASSERT_EQ(map.contains(4), true);
}

TEST(Map, MapCopyConstructor) {
  Map<int, double> map({{1, 100.2}, {2, 200.314}, {5, 124.432}});
  Map<int, double> map1(map);

  ASSERT_EQ(map1.size(), 3);
}

TEST(Map, MapInsertMultiple) {
  Map<int, double> map({{1, 100.2}, {2, 200.314}, {5, 124.432}});
  map.insert_many(Entry<int, double>(3, 300.2), Entry<int, double>(6, 300.2));

  ASSERT_EQ(map.contains(1), true);
  ASSERT_EQ(map.contains(3), true);
  ASSERT_EQ(map.contains(6), true);
}
