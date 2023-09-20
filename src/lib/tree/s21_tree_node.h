#ifndef S21_LIB_TREE_TREE_NODE_H
#define S21_LIB_TREE_TREE_NODE_H

enum Color { RED = true, BLACK = false };

template <class T>
struct TreeNode {
  explicit TreeNode(T val);
  ~TreeNode();

  T value;
  Color color;
  TreeNode<T>* parent;
  TreeNode<T>* left;
  TreeNode<T>* right;

  int numberOfChildren();

  TreeNode<T>* getGrandparent();
  TreeNode<T>* getUncle();
  TreeNode<T>* getSibling();

  bool operator==(const TreeNode<T>& b) const;
  bool operator<=(const TreeNode<T>& b) const;
};

#include "s21_tree_node.tpp"

#endif  // S21_LIB_TREE_TREE_NODE_H