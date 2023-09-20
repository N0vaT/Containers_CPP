#include "s21_array.h"

template <class T, size_t N>
Array<T, N>::Array() noexcept {}

template <class T, size_t N>
Array<T, N>::Array(std::initializer_list<value_type> const &items) : Array() {
  if (items.size() > N) {
    throw std::range_error("Invalid argument - items");
  }
  std::copy(items.begin(), items.end(), array_);
}

template <class T, size_t N>
Array<T, N>::Array(const Array &a) : Array() {
  std::copy(a.begin(), a.end(), array_);
}

template <class T, size_t N>
Array<T, N>::Array(Array &&a) noexcept : Array() {
  std::move(a.begin(), a.end(), array_);
}

template <class T, size_t N>
Array<T, N> &Array<T, N>::operator=(const Array &a) {
  if (this != &a) {
    std::copy(a.begin(), a.end(), array_);
    size_ = a.size_;
  }
  return *this;
}

template <class T, size_t N>
Array<T, N> &Array<T, N>::operator=(Array &&a) noexcept {
  if (this != &a) {
    std::swap(array_, a.array_);
    size_ = a.size_;
  }
  return *this;
}

template <class T, size_t N>
constexpr typename Array<T, N>::reference Array<T, N>::at(size_type pos) const {
  if (pos >= size_ || size_ == 0) {
    throw std::range_error("Invalid argument");
  }
  return (reference)array_[pos];
}

template <class T, size_t N>
constexpr typename Array<T, N>::reference Array<T, N>::operator[](
    size_type pos) const {
  return (reference)array_[pos];
}

template <class T, size_t N>
constexpr typename Array<T, N>::const_reference Array<T, N>::front() const {
  return array_[0];
}

template <class T, size_t N>
constexpr typename Array<T, N>::const_reference Array<T, N>::back() const {
  return (const_reference)array_[size_ == 0 ? 0 : size_ - 1];
}

template <class T, size_t N>
constexpr typename Array<T, N>::iterator Array<T, N>::data() const noexcept {
  return (iterator)array_;
}

template <class T, size_t N>
constexpr typename Array<T, N>::iterator Array<T, N>::begin() const noexcept {
  return (iterator)array_;
}

template <class T, size_t N>
constexpr typename Array<T, N>::iterator Array<T, N>::end() const noexcept {
  return (iterator)array_ + size_;
}

template <class T, size_t N>
constexpr bool Array<T, N>::empty() const noexcept {
  return size_ == 0;
}

template <class T, size_t N>
constexpr typename Array<T, N>::size_type Array<T, N>::size() const noexcept {
  return size_;
}

template <class T, size_t N>
constexpr typename Array<T, N>::size_type Array<T, N>::max_size()
    const noexcept {
  return size_;
}

template <class T, size_t N>
constexpr void Array<T, N>::swap(Array &other) noexcept {
  std::swap(size_, other.size_);
  std::swap(array_, other.array_);
}

template <class T, size_t N>
constexpr void Array<T, N>::fill(const_reference value) {
  for (size_type i = 0; i < size_; ++i) {
    array_[i] = value;
  }
}
