#ifndef S21_LIB_MAP_H
#define S21_LIB_MAP_H

#include "../tree/s21_tree.h"
#include "s21_map_entry.h"

template <class K, class V>
class Map {
 public:
  using key_type = K;
  using mapped_type = V;
  using value_type = Entry<K, V>;
  using reference = Entry<K, V>&;
  using const_reference = const Entry<K, V>&;
  using iterator = typename Tree<Entry<K, V>>::Iterator;
  using const_iterator = typename Tree<Entry<K, V>>::Iterator;
  using size_type = size_t;

  explicit Map();
  explicit Map(const std::initializer_list<Entry<K, V>>& entries);
  Map(const Map& m);
  Map(Map&& m) noexcept;
  ~Map();
  Map& operator=(Map& m);

  V at(const K& key);
  V operator[](const K& key);

  iterator begin();
  iterator end();

  bool empty() const noexcept;
  size_type size() const noexcept;
  size_type max_size() const noexcept;

  void clear() noexcept;

  std::pair<iterator, bool> insert(const_reference entry);
  std::pair<iterator, bool> insert(const K& key, const V& val);
  std::pair<iterator, bool> insert_or_assign(const K& key, const V& val);
  void erase(iterator pos);
  void swap(Map& other) noexcept;
  void merge(Map& other);

  bool contains(const K& key) const noexcept;

  template <class... Args>
  void insert_many(Args&&... args);

 private:
  Tree<Entry<K, V>>* tree_;

  template <class U>
  void insert_many_aux(U&& arg);

  template <class U, class... Args>
  void insert_many_aux(U&& arg, Args&&... args);
};

#include "s21_map.tpp"

#endif  // S21_LIB_MAP_H
