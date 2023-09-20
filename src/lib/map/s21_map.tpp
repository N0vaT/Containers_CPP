
template <class K, class V>
Map<K, V>::Map() : tree_(new Tree<Entry<K, V>>(false)) {}

template <class K, class V>
Map<K, V>::Map(const std::initializer_list<Entry<K, V>>& entries) : Map() {
  for (Entry<K, V> entry : entries) {
    insert(entry);
  }
}

template <class K, class V>
Map<K, V>::Map(const Map& m) : tree_(new Tree<Entry<K, V>>(*m.tree_)) {}

template <class K, class V>
Map<K, V>::Map(Map&& m) noexcept : tree_(m.tree_) {
  m.tree_ = nullptr;
}

template <class K, class V>
Map<K, V>::~Map() {
  if (tree_ != nullptr) {
    delete tree_;
  }
}

template <class K, class V>
Map<K, V>& Map<K, V>::operator=(Map& m) {
  if (this == &m) {
    return *this;
  }

  delete tree_;
  tree_ = m.tree_;
  m.tree_ = nullptr;
  return *this;
}

template <class K, class V>
bool Map<K, V>::empty() const noexcept {
  return tree_->empty();
}

template <class K, class V>
typename Map<K, V>::size_type Map<K, V>::size() const noexcept {
  return tree_->size();
}

template <class K, class V>
typename Map<K, V>::size_type Map<K, V>::max_size() const noexcept {
  return std::numeric_limits<std::size_t>::max() / sizeof(value_type) / 2;
}

template <class K, class V>
void Map<K, V>::clear() noexcept {
  tree_->clear();
}

template <class K, class V>
bool Map<K, V>::contains(const K& key) const noexcept {
  return tree_->contains(Entry<K, V>(key, 0));
}

template <class K, class V>
V Map<K, V>::at(const K& key) {
  return tree_->retrieveSingle(Entry<K, V>(key, 0)).getValue();
}

template <class K, class V>
V Map<K, V>::operator[](const K& key) {
  return at(key);
}

template <class K, class V>
typename Map<K, V>::iterator Map<K, V>::begin() {
  return tree_->begin();
}

template <class K, class V>
typename Map<K, V>::iterator Map<K, V>::end() {
  return tree_->end();
}

template <class K, class V>
std::pair<typename Map<K, V>::iterator, bool> Map<K, V>::insert(
    const_reference entry) {
  try {
    typename Map<K, V>::iterator iter = tree_->insert(entry);
    bool res = true;
    return std::pair{iter, res};
  } catch (const std::exception& e) {
    typename Map<K, V>::iterator iter = tree_->find(entry);
    bool res = false;
    return std::pair{iter, res};
  }
}

template <class K, class V>
std::pair<typename Map<K, V>::iterator, bool> Map<K, V>::insert(const K& key,
                                                                const V& val) {
  return insert(Entry<K, V>(key, val));
}

template <class K, class V>
std::pair<typename Map<K, V>::iterator, bool> Map<K, V>::insert_or_assign(
    const K& key, const V& val) {
  std::pair<typename Map<K, V>::iterator, bool> pair = insert(key, val);
  if (pair.second == false) {
    pair.first->setValue(val);
  }
  return pair;
}

template <class K, class V>
void Map<K, V>::swap(Map& other) noexcept {
  std::swap(tree_, other.tree_);
}

template <class K, class V>
void Map<K, V>::merge(Map& other) {
  typename Map<K, V>::iterator iter = other.begin();
  ++iter;
  for (int i = 0; i < other.size(); i++) {
    insert(*(iter++));
  }
}

template <class K, class V>
void Map<K, V>::erase(iterator pos) {
  tree_->remove(pos.getNode());
}

template <class K, class V>
template <class... Args>
void Map<K, V>::insert_many(Args&&... args) {
  insert_many_aux(args...);
}

template <class K, class V>
template <class U>
void Map<K, V>::insert_many_aux(U&& arg) {
  insert(arg);
}

template <class K, class V>
template <class U, class... Args>
void Map<K, V>::insert_many_aux(U&& arg, Args&&... args) {
  insert(arg);
  insert_many_aux(args...);
}
