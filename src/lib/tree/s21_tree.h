#ifndef S21_LIB_TREE_TREE_H
#define S21_LIB_TREE_TREE_H

#include "../stack/s21_stack.h"
#include "s21_tree_node.h"

template <class T>
class Tree {
 public:
  explicit Tree(bool allowDuplicates);
  Tree(Tree& t);
  ~Tree();

  typename Tree<T>::Iterator insert(T val);
  void remove(TreeNode<T>* n);

  void clear();

  T retrieveSingle(T val);
  bool contains(T val);
  size_t count(T val);

  bool empty() const noexcept;
  size_t size() const noexcept;

  class Iterator : public std::iterator<std::bidirectional_iterator_tag, T, T,
                                        const T*, T> {
   public:
    Iterator(Tree<T>* tree, TreeNode<T>* node);

    T operator*();
    T* operator->();

    // Prefix increment
    Iterator& operator++();
    // Postfix increments
    Iterator operator++(int);

    // Prefix decrement
    Iterator& operator--();
    // Postfix decrement
    Iterator operator--(int);

    TreeNode<T>* getNode();

    bool operator==(const Iterator& other) const noexcept;
    bool operator!=(const Iterator& other) const noexcept;

    bool isPastEnd() const noexcept;
    bool isPastStart() const noexcept;

   private:
    TreeNode<T>* node_;
    Tree<T>* tree_;
    TreeNode<T>* first = nullptr;
    TreeNode<T>* last = nullptr;

    TreeNode<T>* getNextNode(TreeNode<T>* node);
    TreeNode<T>* getPrevNode(TreeNode<T>* node);
  };

  Iterator begin();
  Iterator end();
  Iterator find(T val);
  Iterator lower_bound(T val);
  Iterator upper_bound(T val);

 private:
  TreeNode<T>* root_;
  size_t size_;
  bool allowDuplicates_;

  void clearTree(TreeNode<T>* rootNode) noexcept;

  TreeNode<T>* findNode(T val);
  static TreeNode<T>* findMin(TreeNode<T>* root) noexcept;
  static TreeNode<T>* findMax(TreeNode<T>* root) noexcept;

  void insertNode(TreeNode<T>* newNode);
  TreeNode<T>* findParent(TreeNode<T>* root, TreeNode<T>* newNode) const;

  void insert_case1(TreeNode<T>* n) noexcept;
  void insert_case2(TreeNode<T>* n) noexcept;
  void insert_case3(TreeNode<T>* n) noexcept;
  void insert_case4(TreeNode<T>* n) noexcept;
  void insert_case5(TreeNode<T>* n) noexcept;

  void rotateRight(TreeNode<T>* n) noexcept;
  void rotateLeft(TreeNode<T>* n) noexcept;

  void replaceNode(TreeNode<T>* n, TreeNode<T>* child) noexcept;
  void deleteOneChild(TreeNode<T>* n) noexcept;
  void deleteNoChild(TreeNode<T>* n) noexcept;

  void delete_case1(TreeNode<T>* n) noexcept;
  void delete_case2(TreeNode<T>* n) noexcept;
  void delete_case3(TreeNode<T>* n) noexcept;
  void delete_case4(TreeNode<T>* n) noexcept;
  void delete_case5(TreeNode<T>* n) noexcept;
  void delete_case6(TreeNode<T>* n) noexcept;
};

#include "s21_tree.tpp"
#include "s21_tree_delete.tpp"
#include "s21_tree_insert.tpp"
#include "s21_tree_iterator.tpp"

#endif  // S21_LIB_TREE_TREE_H