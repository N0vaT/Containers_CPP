#include "s21_queue.h"

template <class T>
Queue<T>::Queue() noexcept
    : size_(0U), ptr_head_(nullptr), ptr_tail_(nullptr) {}

template <class T>
Queue<T>::Queue(std::initializer_list<value_type> const& items) : Queue() {
  for (value_type element : items) {
    push(element);
  }
}

template <class T>
Queue<T>::Queue(const Queue& q) : Queue() {
  Node* ptr_q = q.ptr_head_;
  for (size_type i = 0; i < q.size_; ++i) {
    push(ptr_q->value_);
    ptr_q = ptr_q->ptr_prevNode_;
  }
}

template <class T>
Queue<T>::Queue(Queue&& q) noexcept : Queue() {
  *this = std::move(q);
}

template <class T>
Queue<T>& Queue<T>::operator=(const Queue& q) {
  if (this != &q) {
    while (ptr_head_) {
      pop();
    }
    size_ = 0;
    Node* ptr_q = q.ptr_head_;
    for (size_type i = 0; i < q.size_; ++i) {
      push(ptr_q->value_);
      ptr_q = ptr_q->ptr_prevNode_;
    }
  }
  return *this;
}

template <class T>
Queue<T>& Queue<T>::operator=(Queue&& q) {
  if (this != &q) {
    while (ptr_head_) {
      pop();
    }
    std::swap(size_, q.size_);
    std::swap(ptr_head_, q.ptr_head_);
    std::swap(ptr_tail_, q.ptr_tail_);
  }
  return *this;
}

template <class T>
Queue<T>::~Queue() {
  while (ptr_head_) {
    pop();
  }
}

template <class T>
typename Queue<T>::const_reference Queue<T>::front() const {
  if (!ptr_head_) {
    throw std::range_error("Invalid Queue for front, queue is empty");
  }
  return ptr_head_->value_;
}

template <class T>
typename Queue<T>::const_reference Queue<T>::back() const {
  if (size_ == 0) {
    throw std::range_error("Invalid Queue for back, queue is empty");
  }
  return ptr_tail_->value_;
}

template <class T>
bool Queue<T>::empty() const noexcept {
  return size_ == 0;
}

template <class T>
typename Queue<T>::size_type Queue<T>::size() const noexcept {
  return size_;
}

template <class T>
void Queue<T>::push(const_reference value) {
  Node* new_node = new Node(value);
  if (!ptr_head_) {
    ptr_head_ = new_node;
  } else if (!ptr_tail_) {
    ptr_head_->ptr_prevNode_ = new_node;
    ptr_tail_ = new_node;
  } else {
    ptr_tail_->ptr_prevNode_ = new_node;
    ptr_tail_ = new_node;
  }
  ++size_;
}

template <class T>
void Queue<T>::pop() {
  if (!ptr_head_) {
    throw std::range_error("Invalid Queue for pop, queue is empty");
  }
  Node* prev = ptr_head_->ptr_prevNode_;
  delete ptr_head_;
  ptr_head_ = prev;
  --size_;
  if (!ptr_head_) {
    ptr_tail_ = nullptr;
  }
}

template <class T>
void Queue<T>::swap(Queue& other) noexcept {
  std::swap(size_, other.size_);
  std::swap(ptr_head_, other.ptr_head_);
  std::swap(ptr_tail_, other.ptr_tail_);
}

template <class T>
template <class... Args>
void Queue<T>::insert_many_back(Args&&... args) {
  insert_many_aux(args...);
}

template <class T>
template <class U>
void Queue<T>::insert_many_aux(U&& arg) {
  push(arg);
}

template <class T>
template <class U, class... Args>
void Queue<T>::insert_many_aux(U&& arg, Args&&... args) {
  push(arg);
  insert_many_aux(args...);
}
