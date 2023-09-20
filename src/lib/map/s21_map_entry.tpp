
template <class K, class V>
Entry<K, V>::Entry(const K key, V value) noexcept : key_(key), value_(value) {}

template <class K, class V>
K Entry<K, V>::getKey() const noexcept {
  return key_;
}

template <class K, class V>
V Entry<K, V>::getValue() const noexcept {
  return value_;
}

template <class K, class V>
void Entry<K, V>::setValue(V value) noexcept {
  value_ = value;
}

template <class K, class V>
bool Entry<K, V>::operator==(const Entry<K, V>& b) const noexcept {
  return (key_ == b.key_);
}

template <class K, class V>
bool Entry<K, V>::operator<(const Entry<K, V>& b) const noexcept {
  return (key_ < b.key_);
}

template <class K, class V>
bool Entry<K, V>::operator>(const Entry<K, V>& b) const noexcept {
  return (key_ > b.key_);
}

template <class K, class V>
bool Entry<K, V>::operator<=(const Entry<K, V>& b) const noexcept {
  return (key_ <= b.key_);
}
