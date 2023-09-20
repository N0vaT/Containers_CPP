
template <class T>
TreeNode<T>::TreeNode(T val)
    : value(val), color(RED), parent(nullptr), left(nullptr), right(nullptr) {}

template <class T>
TreeNode<T>::~TreeNode() {}

template <class T>
int TreeNode<T>::numberOfChildren() {
  if (left != nullptr && right != nullptr) {
    return 2;
  } else if ((left == nullptr) ^ (right == nullptr)) {
    return 1;
  }
  return 0;
}

template <class T>
TreeNode<T>* TreeNode<T>::getGrandparent() {
  if (parent == nullptr) {
    return nullptr;
  }
  return parent->parent;
}

template <class T>
TreeNode<T>* TreeNode<T>::getUncle() {
  TreeNode<T>* grandparent = getGrandparent();
  if (grandparent == nullptr) {
    return nullptr;
  }
  if (grandparent->left != parent) return grandparent->left;
  return grandparent->right;
}

template <class T>
TreeNode<T>* TreeNode<T>::getSibling() {
  if (parent == nullptr) {
    return nullptr;
  }
  if (parent->left != this) {
    return parent->right;
  } else {
    return parent->left;
  }
}

template <class T>
bool TreeNode<T>::operator==(const TreeNode<T>& b) const {
  return (value == b.value);
}

template <class T>
bool TreeNode<T>::operator<=(const TreeNode<T>& b) const {
  return (value <= b.value);
}
