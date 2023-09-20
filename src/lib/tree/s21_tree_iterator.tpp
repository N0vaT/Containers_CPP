
template <class T>
Tree<T>::Iterator::Iterator(Tree<T>* tree, TreeNode<T>* node)
    : tree_(tree), node_(node){};

template <class T>
T Tree<T>::Iterator::operator*() {
  return node_->value;
}

template <class T>
T* Tree<T>::Iterator::operator->() {
  return &(node_->value);
}

// Prefix increment
template <class T>
typename Tree<T>::Iterator& Tree<T>::Iterator::operator++() {
  if (last != nullptr) {
    throw std::range_error("Iterator is already over the last element");
  }
  if (first != nullptr) {
    node_ = first;
    first = nullptr;
    return *this;
  }

  try {
    TreeNode<T>* temp = getNextNode(node_);
    node_ = temp;
  } catch (std::exception& e) {
    last = node_;
    node_ = nullptr;
  }
  return *this;
}

// Postfix increment
template <class T>
typename Tree<T>::Iterator Tree<T>::Iterator::operator++(int) {
  Iterator result = *this;
  ++(*this);
  return result;
}

// Prefix decrement
template <class T>
typename Tree<T>::Iterator& Tree<T>::Iterator::operator--() {
  if (first != nullptr) {
    throw std::range_error("Iterator is already over the first element");
  }
  if (last != nullptr) {
    node_ = last;
    last = nullptr;
    return *this;
  }

  try {
    TreeNode<T>* temp = getPrevNode(node_);
    node_ = temp;
  } catch (std::exception& e) {
    first = node_;
    node_ = nullptr;
  }
  return *this;
}

// Postfix decrement
template <class T>
typename Tree<T>::Iterator Tree<T>::Iterator::operator--(int) {
  Iterator result = *this;
  --(*this);
  return result;
}

template <class T>
TreeNode<T>* Tree<T>::Iterator::getNextNode(TreeNode<T>* node) {
  TreeNode<T>* result;
  if (node->right != nullptr) {
    result = tree_->findMin(node->right);
  } else {
    result = node->parent;
    while (result != nullptr && result->value < node->value) {
      result = result->parent;
    }
  }
  if (result == nullptr) {
    throw std::range_error("No node found");
  }
  return result;
}

template <class T>
TreeNode<T>* Tree<T>::Iterator::getPrevNode(TreeNode<T>* node) {
  TreeNode<T>* result;
  if (node->left != nullptr) {
    result = tree_->findMax(node->left);
  } else {
    result = node->parent;
    while (result != nullptr && result->value > node->value) {
      result = result->parent;
    }
  }
  if (result == nullptr) {
    throw std::exception();
  }
  return result;
}

template <class T>
bool Tree<T>::Iterator::operator==(const Iterator& other) const noexcept {
  return (node_ == other.node_);
}

template <class T>
bool Tree<T>::Iterator::operator!=(const Iterator& other) const noexcept {
  return (node_ != other.node_);
}

template <class T>
typename Tree<T>::Iterator Tree<T>::begin() {
  Tree<T>::Iterator iter = Iterator(this, findMin(root_));
  --iter;
  return iter;
}

template <class T>
typename Tree<T>::Iterator Tree<T>::end() {
  Tree<T>::Iterator iter = Iterator(this, findMax(root_));
  ++iter;
  return iter;
}

template <class T>
typename Tree<T>::Iterator Tree<T>::find(T val) {
  return Iterator(this, findNode(val));
}

template <class T>
typename Tree<T>::Iterator Tree<T>::lower_bound(T val) {
  TreeNode<T>* node = root_;
  while (node != nullptr) {
    if (node->value >= val) {
      node = node->left;
    } else {
      break;
    }
  }
  Tree<T>::Iterator iter = Iterator(this, node);
  while (!iter.isPastEnd() && *iter < val) {
    ++iter;
  }
  return iter;
}

template <class T>
typename Tree<T>::Iterator Tree<T>::upper_bound(T val) {
  TreeNode<T>* node = root_;
  while (node != nullptr) {
    if (node->value <= val) {
      node = node->right;
    } else {
      break;
    }
  }
  Tree<T>::Iterator iter = Iterator(this, node);
  while (!iter.isPastStart() && *iter > val) {
    --iter;
  }
  return iter;
}

template <class T>
TreeNode<T>* Tree<T>::Iterator::getNode() {
  return node_;
}

template <class T>
bool Tree<T>::Iterator::isPastEnd() const noexcept {
  return (last != nullptr);
}

template <class T>
bool Tree<T>::Iterator::isPastStart() const noexcept {
  return (first != nullptr);
}