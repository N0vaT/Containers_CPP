#ifndef S21_VECTOR_H
#define S21_VECTOR_H

#include <exception>
#include <initializer_list>

template <class T>
class Vector {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = T *;
  using const_iterator = const T *;
  using size_type = size_t;

  Vector() noexcept;
  explicit Vector(size_type size);
  explicit Vector(std::initializer_list<value_type> const &items);
  Vector(const Vector &v);
  Vector(Vector &&v) noexcept;
  Vector<T> &operator=(const Vector &v);
  constexpr Vector<T> &operator=(Vector &&v) noexcept;
  ~Vector();

  constexpr reference at(size_type pos) const;
  constexpr reference operator[](size_type pos) const;
  constexpr const_reference front() const;
  constexpr const_reference back() const;
  constexpr iterator data() const noexcept;

  constexpr iterator begin() const noexcept;
  constexpr iterator end() const noexcept;

  constexpr bool empty() const noexcept;
  constexpr size_type size() const noexcept;
  constexpr size_type max_size() const noexcept;
  void reserve(size_type size);
  constexpr size_type capacity() const noexcept;
  void shrink_to_fit();

  constexpr void clear() noexcept;
  iterator insert(const_iterator pos, const_reference value);
  void erase(const_iterator pos);
  void push_back(const_reference value);
  constexpr void pop_back() noexcept;
  constexpr void swap(Vector &other) noexcept;

  template <class... Args>
  iterator insert_many(iterator pos, Args &&...args);
  template <class... Args>
  void insert_many_back(Args &&...args);

  void reserve_more_capacity(size_type size);

 private:
  size_type size_;
  size_type capacity_;
  T *array_;

  iterator insert_many_aux(iterator pos);
  template <class U>
  iterator insert_many_aux(iterator pos, U &&arg);
  template <class U, class... Args>
  iterator insert_many_aux(iterator pos, U &&arg, Args &&...args);
};

#include "s21_vector.tpp"

#endif  // S21_VECTOR_H