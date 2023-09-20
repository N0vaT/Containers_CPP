
#ifndef S21_LIBPLUS_MULTISET_H
#define S21_LIBPLUS_MULTISET_H

#include "../../lib/tree/s21_tree.h"

template <class T>
class Multiset {
 public:
  using key_type = T;
  using value_type = T;
  using reference = T&;
  using const_reference = const T&;
  using iterator = typename Tree<T>::Iterator;
  using const_iterator = typename Tree<T>::Iterator;
  using size_type = size_t;

  Multiset();
  ~Multiset();
  explicit Multiset(std::initializer_list<value_type> const& items);
  Multiset(Multiset& ms);
  Multiset(Multiset&& ms) noexcept;
  Multiset<T>& operator=(Multiset& ms);

  iterator begin();
  iterator end();

  bool empty() const noexcept;
  size_type size() const noexcept;
  size_type max_size() const noexcept;

  void clear();
  iterator insert(const_reference value);
  void erase(iterator pos);
  void swap(Multiset& other);
  void merge(Multiset& other);

  size_type count(const T& key) const noexcept;
  iterator find(const T& key);
  bool contains(const_reference key) const noexcept;
  std::pair<iterator, iterator> equal_range(const T& key);
  iterator lower_bound(const T& key);
  iterator upper_bound(const T& key);

  template <class... Args>
  void insert_many(Args&&... args);

 private:
  Tree<T>* tree_;

  template <class U>
  void insert_many_aux(U&& arg);

  template <class U, class... Args>
  void insert_many_aux(U&& arg, Args&&... args);
};

#include "s21_multiset.tpp"

#endif  // S21_LIBPLUS_MULTISET_H