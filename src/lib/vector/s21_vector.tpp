#include "s21_vector.h"

template <class T>
Vector<T>::Vector() noexcept : size_(0U), capacity_(0U), array_(nullptr) {}

template <class T>
Vector<T>::Vector(size_type size)
    : size_(size),
      capacity_(size),
      array_(size ? (new value_type[size]{}) : nullptr) {}

template <class T>
Vector<T>::Vector(std::initializer_list<value_type> const &items) {
  array_ = new value_type[items.size()]{};
  int i = 0;
  for (value_type element : items) {
    array_[i] = element;
    ++i;
  }
  size_ = items.size();
  capacity_ = items.size();
}

template <class T>
Vector<T>::Vector(const Vector &v)
    : size_(v.size_),
      capacity_(v.capacity_),
      array_(v.capacity_ ? new value_type[v.capacity_] : nullptr) {
  for (size_type i = 0; i < v.size_; ++i) {
    array_[i] = v.array_[i];
  }
}

template <class T>
Vector<T>::Vector(Vector &&v) noexcept
    : size_(v.size_), capacity_(v.capacity_), array_(v.array_) {
  v.size_ = 0;
  v.capacity_ = 0;
  v.array_ = nullptr;
}

template <class T>
Vector<T> &Vector<T>::operator=(const Vector &v) {
  if (capacity_ != v.capacity_) {
    delete[] array_;
    array_ = new value_type[v.capacity_]{};
  }
  size_ = v.size_;
  capacity_ = v.capacity_;
  for (size_type i = 0; i < size_; ++i) {
    array_[i] = v.array_[i];
  }
  return *this;
}

template <class T>
constexpr Vector<T> &Vector<T>::operator=(Vector &&v) noexcept {
  std::swap(size_, v.size_);
  std::swap(capacity_, v.capacity_);
  std::swap(array_, v.array_);
  return *this;
}

template <class T>
Vector<T>::~Vector() {
  if (array_) {
    delete[] array_;
    array_ = nullptr;
  }
  size_ = 0;
  capacity_ = 0;
}

template <class T>
constexpr typename Vector<T>::reference Vector<T>::at(size_type pos) const {
  if (pos >= size_ || size_ == 0) {
    throw std::range_error("Invalid argument");
  }
  return array_[pos];
}

template <class T>
constexpr typename Vector<T>::reference Vector<T>::operator[](
    size_type pos) const {
  return array_[pos];
}

template <class T>
constexpr typename Vector<T>::const_reference Vector<T>::front() const {
  if (capacity_ == 0) {
    throw std::range_error("Invalid argument");
  }
  return array_[0];
}

template <class T>
constexpr typename Vector<T>::const_reference Vector<T>::back() const {
  if (capacity_ == 0) {
    throw std::range_error("Invalid argument");
  }
  return array_[size_ - 1];
}

template <class T>
constexpr typename Vector<T>::iterator Vector<T>::data() const noexcept {
  return array_;
}

template <class T>
constexpr typename Vector<T>::iterator Vector<T>::begin() const noexcept {
  return array_;
}

template <class T>
constexpr typename Vector<T>::iterator Vector<T>::end() const noexcept {
  return array_ + size_;
}

template <class T>
constexpr bool Vector<T>::empty() const noexcept {
  return size_ == 0;
}

template <class T>
constexpr typename Vector<T>::size_type Vector<T>::size() const noexcept {
  return size_;
}

template <class T>
constexpr typename Vector<T>::size_type Vector<T>::max_size() const noexcept {
  return std::numeric_limits<std::size_t>::max() / sizeof(value_type) / 2;
}

template <class T>
void Vector<T>::reserve(size_type size) {
  if (size > max_size()) {
    throw std::length_error("Can't allocate memory of this size");
  }
  if (capacity_ >= size) {
    return;
  }
  value_type *buff = new value_type[size]{};
  for (size_type i = 0; i < size_; ++i) {
    buff[i] = std::move(array_[i]);
  }
  delete[] array_;
  array_ = buff;
  capacity_ = size;
}

template <class T>
constexpr typename Vector<T>::size_type Vector<T>::capacity() const noexcept {
  return capacity_;
}

template <class T>
void Vector<T>::shrink_to_fit() {
  if (capacity_ > size_) {
    value_type *buff = new value_type[size_]{};
    for (size_type i = 0; i < size_; ++i) {
      buff[i] = std::move(array_[i]);
    }
    delete[] array_;
    array_ = buff;
    capacity_ = size_;
  }
}

template <class T>
constexpr void Vector<T>::clear() noexcept {
  size_ = 0;
}

template <class T>
typename Vector<T>::iterator Vector<T>::insert(const_iterator pos,
                                               const_reference value) {
  size_type indexPos = pos - array_;
  if (indexPos > size_) {
    throw std::range_error("Invalid argument - pos");
  }
  if (capacity_ == size_) {
    reserve_more_capacity(size_ + 1);
  }
  ++size_;
  value_type tmp1 = array_[indexPos];
  array_[indexPos] = value;
  value_type tmp2;
  for (size_type i = indexPos + 1; i < size_; ++i) {
    tmp2 = array_[i];
    array_[i] = tmp1;
    tmp1 = tmp2;
  }
  return array_ + indexPos;
}

template <class T>
void Vector<T>::erase(const_iterator pos) {
  size_type indexPos = pos - array_;
  if (size_ == 0 || indexPos > size_ - 1) {
    throw std::range_error("Invalid argument - pos");
  }
  --size_;
  for (size_type i = indexPos; i < size_; ++i) {
    array_[i] = array_[i + 1];
  }
}

template <class T>
void Vector<T>::push_back(const_reference v) {
  if (size_ == capacity_) {
    reserve_more_capacity(size_ + size_ + 1);
  }
  array_[size_] = v;
  ++size_;
}

template <class T>
constexpr void Vector<T>::pop_back() noexcept {
  if (size_ > 0) {
    --size_;
  }
}

template <class T>
constexpr void Vector<T>::swap(Vector &other) noexcept {
  std::swap(size_, other.size_);
  std::swap(capacity_, other.capacity_);
  std::swap(array_, other.array_);
}

template <class T>
void Vector<T>::reserve_more_capacity(size_type size) {
  if (size > capacity_) {
    value_type *buff = new value_type[size]{};
    for (size_type i = 0; i < size_; ++i) {
      buff[i] = std::move(array_[i]);
    }
    delete[] array_;
    array_ = buff;
    capacity_ = size;
  }
}

template <class T>
template <class... Args>
typename Vector<T>::iterator Vector<T>::insert_many(Vector<T>::iterator pos,
                                                    Args &&...args) {
  return insert_many_aux(pos, args...);
}

template <class T>
template <class... Args>
void Vector<T>::insert_many_back(Args &&...args) {
  insert_many_aux(end(), args...);
}

template <class T>
typename Vector<T>::iterator Vector<T>::insert_many_aux(iterator pos) {
  return pos;
}

template <class T>
template <class U>
typename Vector<T>::iterator Vector<T>::insert_many_aux(iterator pos, U &&arg) {
  pos = insert(pos, arg);
  ++pos;
  return pos;
}

template <class T>
template <class U, class... Args>
typename Vector<T>::iterator Vector<T>::insert_many_aux(iterator pos, U &&arg,
                                                        Args &&...args) {
  pos = insert(pos, arg);
  ++pos;
  pos = insert_many_aux(pos, args...);
  ++pos;
  return pos;
}
