
template <class T>
void Tree<T>::remove(TreeNode<T>* n) {
  int children = n->numberOfChildren();
  if (children == 1) {
    deleteOneChild(n);
  } else if (children == 2) {
    TreeNode<T>* replacement = findMin(n->right);
    std::swap(n->value, replacement->value);
    if (replacement->numberOfChildren() == 0) {
      deleteNoChild(replacement);
    } else {
      deleteOneChild(replacement);
    }
  } else {  // children == 0
    if (n == root_) {
      root_ = nullptr;
    } else if (n->parent->left == n) {
      n->parent->left = nullptr;
    } else {
      n->parent->right = nullptr;
    }
    delete n;
  }
  size_--;
}

template <class T>
void Tree<T>::replaceNode(TreeNode<T>* n, TreeNode<T>* child) noexcept {
  child->parent = n->parent;
  if (n->parent == nullptr) {
    root_ = child;
  } else if (n == n->parent->left) {
    n->parent->left = child;
  } else {
    n->parent->right = child;
  }
}

template <class T>
void Tree<T>::deleteNoChild(TreeNode<T>* n) noexcept {
  if (n->parent->left == n) {
    n->parent->left = nullptr;
  } else {
    n->parent->right = nullptr;
  }
  delete n;
}

template <class T>
void Tree<T>::deleteOneChild(TreeNode<T>* n) noexcept {
  TreeNode<T>* child = (n->right == nullptr) ? n->left : n->right;

  replaceNode(n, child);
  if (n->color == BLACK) {
    if (child->color == RED) {
      child->color = BLACK;
    } else {
      delete_case1(child);
    }
  }
  delete n;
}

template <class T>
void Tree<T>::delete_case1(TreeNode<T>* n) noexcept {
  if (n->parent != NULL) {
    delete_case2(n);
  }
}

template <class T>
void Tree<T>::delete_case2(TreeNode<T>* n) noexcept {
  TreeNode<T>* s = n->getSibling();

  if (s->color == RED) {
    n->parent->color = RED;
    s->color = BLACK;
    if (n == n->parent->left) {
      rotateLeft(n->parent);
    } else {
      rotateRight(n->parent);
    }
  }
  delete_case3(n);
}

template <class T>
void Tree<T>::delete_case3(TreeNode<T>* n) noexcept {
  TreeNode<T>* s = n->getSibling();

  if ((n->parent->color == BLACK) && (s->color == BLACK) &&
      (s->left != nullptr && s->left->color == BLACK) &&
      (s->right != nullptr && s->right->color == BLACK)) {
    s->color = RED;
    delete_case1(n->parent);
  } else {
    delete_case4(n);
  }
}

template <class T>
void Tree<T>::delete_case4(TreeNode<T>* n) noexcept {
  TreeNode<T>* s = n->getSibling();

  if ((n->parent->color == RED) && (s->color == BLACK) &&
      (s->left != nullptr && s->left->color == BLACK) &&
      (s->right != nullptr && s->right->color == BLACK)) {
    s->color = RED;
    n->parent->color = BLACK;
  } else {
    delete_case5(n);
  }
}

template <class T>
void Tree<T>::delete_case5(TreeNode<T>* n) noexcept {
  TreeNode<T>* s = n->getSibling();

  if (s->color == BLACK) {
    if ((n == n->parent->left) &&
        (s->right != nullptr && s->right->color == BLACK) &&
        (s->left != nullptr && s->left->color == RED)) {
      s->color = RED;
      s->left->color = BLACK;
      rotateRight(s);
    } else if ((n == n->parent->right) &&
               (s->left != nullptr && s->left->color == BLACK) &&
               (s->right != nullptr && s->right->color == RED)) {
      s->color = RED;
      s->right->color = BLACK;
      rotateLeft(s);
    }
  }
  delete_case6(n);
}

template <class T>
void Tree<T>::delete_case6(TreeNode<T>* n) noexcept {
  TreeNode<T>* s = n->getSibling();
  if (s == nullptr || n->parent == nullptr) {
    return;
  }

  s->color = n->parent->color;
  n->parent->color = BLACK;

  if (n == n->parent->left) {
    if (s->right != nullptr) {
      s->right->color = BLACK;
    }
    if (n->right != nullptr && n->parent->right->left != nullptr) {
      rotateLeft(n->parent);
    }
  } else {
    if (s->left != nullptr) {
      s->left->color = BLACK;
    }
    if (n->left != nullptr) {
      rotateRight(n->parent);
    }
  }
}
