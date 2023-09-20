
template <class T>
Set<T>::Set() : tree_(new Tree<T>(false)) {}

template <class T>
Set<T>::~Set() {
  if (tree_ != nullptr) {
    delete tree_;
  }
}

template <class T>
Set<T>::Set(std::initializer_list<T> const &items) : Set() {
  for (T item : items) {
    insert(item);
  }
}

template <class T>
Set<T>::Set(const Set &s) : tree_(new Tree<T>(*s.tree_)) {}

template <class T>
Set<T>::Set(Set &&s) noexcept : tree_(s.tree_) {
  s.tree_ = nullptr;
}

template <class T>
Set<T> &Set<T>::operator=(Set &s) {
  if (this == &s) {
    return *this;
  }

  delete tree_;
  tree_ = s.tree_;
  s.tree_ = nullptr;
  return *this;
}

template <class T>
typename Set<T>::iterator Set<T>::begin() {
  return tree_->begin();
}

template <class T>
typename Set<T>::iterator Set<T>::end() {
  return tree_->end();
}

template <class T>
bool Set<T>::empty() const noexcept {
  return tree_->empty();
}

template <class T>
typename Set<T>::size_type Set<T>::size() const noexcept {
  return tree_->size();
}

template <class T>
typename Set<T>::size_type Set<T>::max_size() const noexcept {
  return std::numeric_limits<std::size_t>::max() / sizeof(value_type) / 2;
}

template <class T>
void Set<T>::clear() noexcept {
  tree_->clear();
}

template <class T>
std::pair<typename Tree<T>::Iterator, bool> Set<T>::insert(
    const_reference value) {
  try {
    typename Tree<T>::Iterator iter = tree_->insert(value);
    bool res = true;
    return std::pair(iter, res);
  } catch (const std::exception &e) {
    typename Tree<T>::Iterator iter = tree_->find(value);
    bool res = false;
    return std::pair{iter, res};
  }
}

template <class T>
void Set<T>::swap(Set &other) {
  std::swap(tree_, other.tree_);
}

template <class T>
typename Tree<T>::Iterator Set<T>::find(const_reference key) {
  return tree_->find(key);
}

template <class T>
bool Set<T>::contains(const_reference key) const noexcept {
  return tree_->contains(key);
}

template <class T>
void Set<T>::erase(iterator pos) {
  tree_->remove(pos.getNode());
}

template <class T>
void Set<T>::merge(Set &other) {
  if (!other.empty()) {
    Set<T>::iterator iter = other.begin();
    for (int i = 0; i < other.size(); i++) {
      insert(*(++iter));
    }
  }
}

template <class T>
template <class... Args>
void Set<T>::insert_many(Args &&...args) {
  insert_many_aux(args...);
}

template <class T>
template <class U>
void Set<T>::insert_many_aux(U &&arg) {
  insert(arg);
}

template <class T>
template <class U, class... Args>
void Set<T>::insert_many_aux(U &&arg, Args &&...args) {
  insert(arg);
  insert_many_aux(args...);
}
