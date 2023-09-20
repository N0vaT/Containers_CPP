#ifndef S21_LIB_MAP_ENTRY_H
#define S21_LIB_MAP_ENTRY_H

template <class K, class V>
class Entry {
 public:
  Entry(const K key, V value) noexcept;

  K getKey() const noexcept;
  V getValue() const noexcept;

  void setValue(V value) noexcept;

  bool operator==(const Entry<K, V>& b) const noexcept;
  bool operator<(const Entry<K, V>& b) const noexcept;
  bool operator>(const Entry<K, V>& b) const noexcept;
  bool operator<=(const Entry<K, V>& b) const noexcept;

 private:
  K key_;
  V value_;
};

#include "s21_map_entry.tpp"

#endif  // S21_LIB_MAP_ENTRY_H