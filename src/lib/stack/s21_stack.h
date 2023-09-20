#ifndef S21_LIB_STACK_H
#define S21_LIB_STACK_H

#include <stdarg.h>

#include <exception>
#include <initializer_list>

#include "s21_stack_node.h"

template <class T>
class Stack {
 public:
  using value_type = T;
  using reference = T&;
  using const_reference = const T&;
  using size_type = size_t;

  Stack() noexcept;
  explicit Stack(const std::initializer_list<T>& items);
  Stack(const Stack& s);
  Stack(Stack&& s) noexcept;
  ~Stack() noexcept;
  Stack& operator=(Stack&& s) noexcept;
  void swap(Stack& other) noexcept;

  const_reference top() const;

  bool empty() const noexcept;
  size_type size() const noexcept;
  size_type max_size() const noexcept;

  void push(const_reference value);
  void pop();

  template <class... Args>
  void insert_many_front(Args&&... args);

 private:
  StackNode<T>* topNode_;
  size_type size_;

  void clean() noexcept;
  void copy(const Stack<T>& s);

  template <class U>
  void insert_many_front_aux(U&& arg);

  template <class U, class... Args>
  void insert_many_front_aux(U&& arg, Args&&... args);
};

#include "s21_stack.tpp"

#endif  // S21_LIB_STACK_H
