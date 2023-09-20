#ifndef S21_LIB_SET_H
#define S21_LIB_SET_H

#include "../tree/s21_tree.h"

template <class T>
class Set {
 public:
  using key_type = T;
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = typename Tree<T>::Iterator;
  using const_iterator = typename Tree<T>::Iterator;
  using size_type = size_t;

  Set();
  explicit Set(std::initializer_list<T> const &items);
  Set(const Set &s);
  Set(Set &&s) noexcept;
  ~Set();
  Set<T> &operator=(Set &s);

  iterator begin();
  iterator end();

  bool empty() const noexcept;
  size_type size() const noexcept;
  size_type max_size() const noexcept;

  void clear() noexcept;
  std::pair<typename Tree<T>::Iterator, bool> insert(const_reference value);
  void erase(iterator pos);
  void swap(Set &other);
  void merge(Set &other);

  typename Tree<T>::Iterator find(const_reference key);
  bool contains(const_reference key) const noexcept;

  template <class... Args>
  void insert_many(Args &&...args);

 private:
  Tree<T> *tree_;

  template <class U>
  void insert_many_aux(U &&arg);

  template <class U, class... Args>
  void insert_many_aux(U &&arg, Args &&...args);
};

#include "s21_set.tpp"

#endif  // S21_LIB_SET_H