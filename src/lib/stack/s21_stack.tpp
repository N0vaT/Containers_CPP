#include "s21_stack.h"

template <class T>
Stack<T>::Stack() noexcept : topNode_(nullptr), size_(0) {}
template <class T>
Stack<T>::~Stack() noexcept {
  clean();
}

template <class T>
Stack<T>::Stack(const Stack& s) : Stack() {
  copy(s);
}

template <class T>
Stack<T>::Stack(Stack&& s) noexcept : topNode_(s.topNode_), size_(s.size_) {
  s.topNode_ = nullptr;
  s.size_ = 0;
}

template <class T>
Stack<T>::Stack(const std::initializer_list<T>& items) : Stack() {
  for (T element : items) {
    push(element);
  }
}

template <class T>
Stack<T>& Stack<T>::operator=(Stack&& s) noexcept {
  topNode_ = s.topNode_;
  size_ = s.size_;
  s.topNode_ = nullptr;
  s.size_ = 0;
  return *this;
}

template <class T>
void Stack<T>::swap(Stack& other) noexcept {
  std::swap(topNode_, other.topNode_);
  std::swap(size_, other.size_);
}

template <class T>
void Stack<T>::push(const_reference value) {
  StackNode<T>* next = new StackNode(value, topNode_);
  topNode_ = next;
  ++size_;
}

template <class T>
void Stack<T>::pop() {
  if (topNode_ == nullptr) {
    throw std::exception();
  }
  StackNode<T>* next = topNode_->nextNode;
  delete topNode_;
  topNode_ = next;
  --size_;
}

template <class T>
typename Stack<T>::const_reference Stack<T>::top() const {
  if (topNode_ == nullptr) {
    throw std::exception();
  }
  return topNode_->value;
}

template <class T>
bool Stack<T>::empty() const noexcept {
  return (topNode_ == nullptr);
}

template <class T>
typename Stack<T>::size_type Stack<T>::size() const noexcept {
  return size_;
}

template <class T>
typename Stack<T>::size_type Stack<T>::max_size() const noexcept {
  return std::numeric_limits<std::size_t>::max() / sizeof(value_type) / 2;
}

template <class T>
void Stack<T>::clean() noexcept {
  while (topNode_ != nullptr) {
    StackNode<T>* temp = topNode_;
    topNode_ = topNode_->nextNode;
    delete temp;
  }
}

template <class T>
void Stack<T>::copy(const Stack<T>& s) {
  T values[s.size_];
  StackNode<T>* temp = s.topNode_;
  for (int i = s.size_ - 1; i >= 0; i--) {
    values[i] = temp->value;
    temp = temp->nextNode;
  }
  for (unsigned int i = 0; i < s.size_; i++) {
    push(values[i]);
  }
}

template <class T>
template <class... Args>
void Stack<T>::insert_many_front(Args&&... args) {
  insert_many_front_aux(args...);
}

template <class T>
template <class U>
void Stack<T>::insert_many_front_aux(U&& arg) {
  push(arg);
}

template <class T>
template <class U, class... Args>
void Stack<T>::insert_many_front_aux(U&& arg, Args&&... args) {
  push(arg);
  insert_many_front_aux(args...);
}
