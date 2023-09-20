#ifndef S21_QUEUE_H
#define S21_QUEUE_H

#include <exception>
#include <initializer_list>

template <class T>
class Queue {
 public:
  using value_type = T;
  using reference = T&;
  using const_reference = const T&;
  using size_type = size_t;

  Queue() noexcept;
  explicit Queue(std::initializer_list<value_type> const& items);
  Queue(const Queue& q);
  Queue(Queue&& q) noexcept;
  Queue<T>& operator=(const Queue& q);
  Queue<T>& operator=(Queue&& q);
  ~Queue();

  const_reference front() const;
  const_reference back() const;

  bool empty() const noexcept;
  size_type size() const noexcept;

  void push(const_reference value);
  void pop();
  void swap(Queue& other) noexcept;

  template <class... Args>
  void insert_many_back(Args&&... args);

 protected:
  struct Node {
    explicit Node(value_type value) : value_(value), ptr_prevNode_(nullptr) {}
    value_type value_;
    Node* ptr_prevNode_;
  };

 private:
  size_type size_;
  Node* ptr_head_;
  Node* ptr_tail_;

  template <class U>
  void insert_many_aux(U&& arg);
  template <class U, class... Args>
  void insert_many_aux(U&& arg, Args&&... args);
};

#include "s21_queue.tpp"

#endif  // S21_QUEUE_H