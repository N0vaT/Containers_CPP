
template <class T>
void Tree<T>::insertNode(TreeNode<T>* newNode) {
  if (root_ == nullptr) {
    root_ = newNode;
  } else {
    TreeNode<T>* parent = findParent(root_, newNode);
    if ((*newNode) <= (*parent)) {
      parent->left = newNode;
    } else {
      parent->right = newNode;
    }
    newNode->parent = parent;
  }
  size_++;
  insert_case1(newNode);
}

template <class T>
void Tree<T>::insert_case1(TreeNode<T>* n) noexcept {
  if (n->parent == nullptr) {
    n->color = BLACK;
  } else {
    insert_case2(n);
  }
}

template <class T>
void Tree<T>::insert_case2(TreeNode<T>* n) noexcept {
  if (n->parent->color != BLACK) {
    insert_case3(n);
  }
}

template <class T>
void Tree<T>::insert_case3(TreeNode<T>* n) noexcept {
  TreeNode<T>* u = n->getUncle();
  if (u != nullptr && u->color == RED) {
    n->parent->color = BLACK;
    u->color = BLACK;
    TreeNode<T>* g = n->getGrandparent();
    g->color = RED;
    insert_case1(g);
  } else {
    insert_case4(n);
  }
}

template <class T>
void Tree<T>::insert_case4(TreeNode<T>* n) noexcept {
  TreeNode<T>* g = n->getGrandparent();
  if (n == n->parent->right && n->parent == g->left) {
    rotateLeft(n->parent);
    n = n->left;
  } else if (n == n->parent->left && n->parent == g->right) {
    rotateRight(n->parent);
    n = n->right;
  }
  insert_case5(n);
}

template <class T>
void Tree<T>::insert_case5(TreeNode<T>* n) noexcept {
  TreeNode<T>* g = n->getGrandparent();
  n->parent->color = BLACK;
  g->color = RED;
  if (n == n->parent->left && n->parent == g->left) {
    rotateRight(g);
  } else {
    rotateLeft(g);
  }
}
