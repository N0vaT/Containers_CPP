
template <class T>
Tree<T>::Tree(bool allowDuplicates)
    : root_(nullptr), size_(0), allowDuplicates_(allowDuplicates) {}

template <class T>
Tree<T>::~Tree() {
  clearTree(root_);
}

template <class T>
Tree<T>::Tree(Tree& t)
    : root_(nullptr), allowDuplicates_(t.allowDuplicates_), size_(0) {
  typename Tree<T>::Iterator iter = t.begin();
  ++iter;
  for (int i = 0; i < t.size(); i++) {
    T val = *iter;
    insert(val);
    ++iter;
  }
}

template <class T>
void Tree<T>::clear() {
  clearTree(root_);
  size_ = 0;
  root_ = nullptr;
};

template <class T>
T Tree<T>::retrieveSingle(T val) {
  TreeNode<T>* result = findNode(val);
  if (result == nullptr) {
    throw std::range_error("No node found");
  }
  return result->value;
}

template <class T>
size_t Tree<T>::count(T val) {
  if (!contains(val)) {
    return 0;
  }

  Tree<T>::Iterator iterLeft = find(val);
  Tree<T>::Iterator iterRight = iterLeft;
  ++iterRight;

  int count = 0;
  while ((!iterLeft.isPastStart()) && *iterLeft == val) {
    count++;
    --iterLeft;
  }
  while ((!iterRight.isPastEnd()) && *iterRight == val) {
    count++;
    ++iterRight;
  }
  return count;
}

template <class T>
TreeNode<T>* Tree<T>::findNode(T val) {
  TreeNode<T>* result = root_;
  while (true) {
    if (result == nullptr || result->value == val) {
      return result;
    } else if (val < result->value) {
      result = result->left;
    } else {
      result = result->right;
    }
  }
}

template <class T>
TreeNode<T>* Tree<T>::findMin(TreeNode<T>* root) noexcept {
  TreeNode<T>* result = root;
  while (result->left != nullptr) {
    result = result->left;
  }
  return result;
}

template <class T>
TreeNode<T>* Tree<T>::findMax(TreeNode<T>* root) noexcept {
  TreeNode<T>* result = root;
  while (result->right != nullptr) {
    result = result->right;
  }
  return result;
}

template <class T>
bool Tree<T>::contains(T val) {
  return (findNode(val) != nullptr);
}

template <class T>
TreeNode<T>* Tree<T>::findParent(TreeNode<T>* root,
                                 TreeNode<T>* newNode) const {
  if (!allowDuplicates_ && (*newNode) == (*root)) {
    delete newNode;
    throw std::range_error("No place for this node");
  }
  if ((*newNode) <= (*root)) {
    if (root->left == nullptr) {
      return root;
    }
    return findParent(root->left, newNode);
  } else {
    if (root->right == nullptr) {
      return root;
    }
    return findParent(root->right, newNode);
  }
}

template <class T>
void Tree<T>::rotateLeft(TreeNode<T>* n) noexcept {
  TreeNode<T>* pivot = n->right;

  pivot->parent = n->parent;
  if (n->parent != NULL) {
    if (n->parent->left == n) {
      n->parent->left = pivot;
    } else {
      n->parent->right = pivot;
    }
  } else {
    root_ = pivot;
  }

  n->right = pivot->left;
  if (pivot->left != NULL) {
    pivot->left->parent = n;
  }

  n->parent = pivot;
  pivot->left = n;
}

template <class T>
void Tree<T>::rotateRight(TreeNode<T>* n) noexcept {
  TreeNode<T>* pivot = n->left;

  pivot->parent = n->parent;
  if (n->parent != NULL) {
    if (n->parent->left == n) {
      n->parent->left = pivot;
    } else {
      n->parent->right = pivot;
    }
  } else {
    root_ = pivot;
  }

  n->left = pivot->right;
  if (pivot->right != NULL) {
    pivot->right->parent = n;
  }

  n->parent = pivot;
  pivot->right = n;
}

template <class T>
void Tree<T>::clearTree(TreeNode<T>* rootNode) noexcept {
  if (rootNode == nullptr) {
    return;
  }
  clearTree(rootNode->left);
  clearTree(rootNode->right);
  delete rootNode;
}

template <class T>
typename Tree<T>::Iterator Tree<T>::insert(T val) {
  TreeNode<T>* node = new TreeNode<T>(val);
  insertNode(node);
  return Iterator(this, node);
}

template <class T>
bool Tree<T>::empty() const noexcept {
  return (size_ == 0);
}

template <class T>
size_t Tree<T>::size() const noexcept {
  return size_;
}
