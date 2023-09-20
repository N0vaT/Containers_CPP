#ifndef S21_ARRAY_H
#define S21_ARRAY_H

#include <exception>
#include <initializer_list>

template <class T, std::size_t N>
class Array {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = T *;
  using const_iterator = const T *;
  using size_type = size_t;

  Array() noexcept;
  explicit Array(std::initializer_list<value_type> const &items);
  Array(const Array &a);
  Array(Array &&a) noexcept;
  Array<T, N> &operator=(const Array &a);
  Array<T, N> &operator=(Array &&a) noexcept;
  ~Array() = default;

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

  constexpr void swap(Array &other) noexcept;
  constexpr void fill(const_reference value);

 private:
  size_type size_ = N;
  value_type array_[N]{};
};

#include "s21_array.tpp"

#endif  // S21_ARRAY_H