#include "../tests_lib.h"

TEST(Tree, TreeInitNoDuplicates) {
  Tree<int> tree(false);
  ASSERT_EQ(tree.size(), 0);

  tree.insert(100);
  ASSERT_EQ(tree.size(), 1);

  tree.insert(110);
  ASSERT_EQ(tree.size(), 2);

  tree.insert(90);
  ASSERT_EQ(tree.size(), 3);

  tree.insert(105);
  tree.insert(107);
  tree.insert(115);
  tree.insert(114);
  ASSERT_EQ(tree.size(), 7);
  ASSERT_EQ(tree.contains(100), true);
  ASSERT_EQ(tree.contains(110), true);
  ASSERT_EQ(tree.contains(90), true);
  ASSERT_EQ(tree.contains(105), true);
  ASSERT_EQ(tree.contains(107), true);
  ASSERT_EQ(tree.contains(115), true);
  ASSERT_EQ(tree.contains(114), true);

  ASSERT_ANY_THROW(tree.insert(115));
}

TEST(Tree, TreeInitWithDuplicates) {
  Tree<int> tree(true);
  ASSERT_EQ(tree.size(), 0);

  tree.insert(100);
  ASSERT_EQ(tree.size(), 1);

  tree.insert(110);
  ASSERT_EQ(tree.size(), 2);

  tree.insert(90);
  ASSERT_EQ(tree.size(), 3);

  tree.insert(105);
  tree.insert(107);
  tree.insert(115);
  tree.insert(114);
  ASSERT_EQ(tree.size(), 7);
  ASSERT_EQ(tree.contains(100), true);
  ASSERT_EQ(tree.contains(110), true);
  ASSERT_EQ(tree.contains(90), true);
  ASSERT_EQ(tree.contains(105), true);
  ASSERT_EQ(tree.contains(107), true);
  ASSERT_EQ(tree.contains(115), true);
  ASSERT_EQ(tree.contains(114), true);

  tree.insert(115);

  tree.clear();
  ASSERT_EQ(tree.empty(), true);
}

TEST(Tree, TreeIteratorNoDuplicates) {
  Tree<int> tree(false);
  tree.insert(100);
  tree.insert(110);
  tree.insert(90);

  Tree<int>::Iterator iter = ++tree.begin();
  ASSERT_EQ(*iter, 90);
  iter++;
  ASSERT_EQ(*iter, 100);
  ++iter;
  ASSERT_EQ(*iter, 110);
  ++iter;
  ASSERT_EQ(iter.isPastEnd(), true);
  --iter;

  ASSERT_EQ(iter == --tree.end(), true);
  ASSERT_EQ(iter != --tree.end(), false);
}

TEST(Tree, TreeCopyConstructor) {
  Tree<int> tree(false);
  tree.insert(3);
  tree.insert(5);
  Tree<int> tree1(tree);
  ASSERT_EQ(tree.size(), 2);
  ASSERT_EQ(tree1.size(), 2);
  ASSERT_EQ(tree.contains(3), true);
  ASSERT_EQ(tree1.contains(3), true);
  ASSERT_EQ(tree.contains(5), true);
  ASSERT_EQ(tree1.contains(5), true);
}

TEST(Tree, TreeDeleteWithChild) {
  Tree<int> tree(false);
  tree.insert(3);
  tree.insert(2);
  tree.insert(4);
  tree.insert(1);
  tree.insert(6);

  tree.remove(tree.find(3).getNode());

  ASSERT_EQ(tree.contains(3), false);

  for (int i = 10; i < 100; i++) {
    tree.insert(i);
  }

  for (int i = 10; i < 50; i++) {
    tree.remove(tree.find(i).getNode());
  }
}