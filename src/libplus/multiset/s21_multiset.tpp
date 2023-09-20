
template <class T>
Multiset<T>::Multiset() : tree_(new Tree<T>(true)) {}

template <class T>
Multiset<T>::~Multiset() {
  if (tree_ != nullptr) {
    delete tree_;
  }
}

template <class T>
Multiset<T>::Multiset(std::initializer_list<T> const& items) : Multiset() {
  for (T item : items) {
    insert(item);
  }
}

template <class T>
Multiset<T>::Multiset(Multiset& ms) : Multiset() {
  typename Multiset<T>::iterator iter = ms.begin();
  for (int i = 0; i < ms.size(); i++) {
    insert(*(++iter));
  }
}

template <class T>
Multiset<T>::Multiset(Multiset&& ms) noexcept : tree_(ms.tree_) {
  ms.tree_ = nullptr;
}

template <class T>
Multiset<T>& Multiset<T>::operator=(Multiset& ms) {
  if (this == &ms) {
    return *this;
  }

  delete tree_;
  tree_ = ms.tree_;
  ms.tree_ = nullptr;
  return *this;
}

template <class T>
typename Multiset<T>::iterator Multiset<T>::begin() {
  return tree_->begin();
}

template <class T>
typename Multiset<T>::iterator Multiset<T>::end() {
  return tree_->end();
}

template <class T>
bool Multiset<T>::empty() const noexcept {
  return tree_->empty();
}

template <class T>
typename Multiset<T>::size_type Multiset<T>::size() const noexcept {
  return tree_->size();
}

template <class T>
typename Multiset<T>::size_type Multiset<T>::max_size() const noexcept {
  return std::numeric_limits<std::size_t>::max() / sizeof(value_type) / 2;
}

template <class T>
void Multiset<T>::clear() {
  tree_->clear();
}

template <class T>
typename Multiset<T>::iterator Multiset<T>::insert(const_reference value) {
  return tree_->insert(value);
}

template <class T>
void Multiset<T>::swap(Multiset& other) {
  std::swap(tree_, other.tree_);
}

template <class T>
void Multiset<T>::merge(Multiset& other) {
  typename Multiset<T>::iterator iter = other.begin();
  for (int i = 0; i < other.size(); i++) {
    insert(*(++iter));
  }
}

template <class T>
bool Multiset<T>::contains(const_reference key) const noexcept {
  return tree_->contains(key);
}

template <class T>
void Multiset<T>::erase(iterator pos) {
  tree_->remove(pos.getNode());
}

template <class T>
typename Multiset<T>::size_type Multiset<T>::count(
    const T& key) const noexcept {
  return tree_->count(key);
}

template <class T>
typename Multiset<T>::iterator Multiset<T>::find(const T& key) {
  if (!tree_->contains(key)) {
    throw std::range_error("No node found");
  }
  Multiset<T>::iterator iter = tree_->find(key);
  while (!iter.isPastStart() && *iter == key) {
    --iter;
  }
  ++iter;
  return iter;
}

template <class T>
std::pair<typename Multiset<T>::iterator, typename Multiset<T>::iterator>
Multiset<T>::equal_range(const T& key) {
  if (!tree_->contains(key)) {
    throw std::range_error("No element found");
  }
  Multiset<T>::iterator left = tree_->find(key);
  Multiset<T>::iterator right = left;
  while (!left.isPastStart() && *left == key) {
    --left;
  }
  ++left;
  while (!right.isPastEnd() && *right == key) {
    ++right;
  }
  --right;
  return std::pair<typename Multiset<T>::iterator,
                   typename Multiset<T>::iterator>(left, right);
}

template <class T>
typename Multiset<T>::iterator Multiset<T>::lower_bound(const T& key) {
  return tree_->lower_bound(key);
}

template <class T>
typename Multiset<T>::iterator Multiset<T>::upper_bound(const T& key) {
  return tree_->upper_bound(key);
}

template <class T>
template <class... Args>
void Multiset<T>::insert_many(Args&&... args) {
  insert_many_aux(args...);
}

template <class T>
template <class U>
void Multiset<T>::insert_many_aux(U&& arg) {
  insert(arg);
}

template <class T>
template <class U, class... Args>
void Multiset<T>::insert_many_aux(U&& arg, Args&&... args) {
  insert(arg);
  insert_many_aux(args...);
}
