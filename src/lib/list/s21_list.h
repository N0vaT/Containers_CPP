#ifndef S21_LIST_H
#define S21_LIST_H

#include <exception>
#include <initializer_list>

template <class T>
class List {
 private:
  class ListIterator;
  class ListConstIterator;

 public:
  using value_type = T;
  using reference = T&;
  using const_reference = const T&;
  using size_type = size_t;
  using iterator = ListIterator;
  using const_iterator = ListConstIterator;

  List() noexcept;
  explicit List(size_type n);
  explicit List(std::initializer_list<value_type> const& items);
  List(const List& l);
  List(List&& l) noexcept;
  List<T>& operator=(const List& l);
  List<T>& operator=(List&& l);
  ~List();

  const_reference front() const;
  const_reference back() const;

  iterator begin() const noexcept;
  iterator end() const noexcept;

  bool empty() const noexcept;
  size_type size() const noexcept;
  size_type max_size() const noexcept;

  void clear();
  iterator insert(iterator pos, const_reference value);
  void erase(iterator pos);
  void push_back(const_reference value);
  void pop_back();
  void push_front(const_reference value);
  void pop_front();
  void swap(List& other) noexcept;
  void merge(List& other);
  void splice(const_iterator pos, List& other);
  void reverse() noexcept;
  void unique();
  void sort();

  template <class... Args>
  iterator insert_many(iterator pos, Args&&... args);
  template <class... Args>
  void insert_many_back(Args&&... args);
  template <class... Args>
  void insert_many_front(Args&&... args);

 protected:
  struct Node {
    Node() : value_(value_type{}), ptr_prev_(nullptr), ptr_next_(nullptr) {}
    explicit Node(value_type value)
        : value_(value), ptr_prev_(nullptr), ptr_next_(nullptr) {}
    value_type value_;
    Node* ptr_prev_;
    Node* ptr_next_;
  };

 private:
  iterator insert_many_aux(iterator pos);
  template <class U>
  iterator insert_many_aux(iterator pos, U&& arg);
  template <class U, class... Args>
  iterator insert_many_aux(iterator pos, U&& arg, Args&&... args);

  Node* partition(Node* low, Node* high);
  void quickSort(Node* low, Node* high);

  class ListConstIterator {
   public:
    ListConstIterator() noexcept : ptr_node_(nullptr) {}
    explicit ListConstIterator(Node* pos) : ptr_node_(pos) {}
    ListConstIterator(const const_iterator& i) : ptr_node_(i.ptr_node_) {}
    explicit ListConstIterator(const_iterator&& i) noexcept
        : ListConstIterator() {
      *this = std::move(i);
    }
    const_iterator operator=(const const_iterator& other) noexcept {
      if (this != &other) {
        std::swap(ptr_node_, other.ptr_node_);
      }
      return *this;
    }
    const_iterator operator=(const_iterator&& other) noexcept {
      if (this != &other) {
        ptr_node_ = nullptr;
        std::swap(ptr_node_, other.ptr_node_);
      }
      return *this;
    }
    ~ListConstIterator() = default;

    const_reference operator*() noexcept { return ptr_node_->value_; }

    const_iterator& operator++() noexcept {
      ptr_node_ = ptr_node_->ptr_next_;
      return *this;
    }

    const_iterator& operator--() noexcept {
      ptr_node_ = ptr_node_->ptr_prev_;
      return *this;
    }

    bool operator==(const const_iterator& other) const noexcept {
      return ptr_node_ == other.ptr_node_;
    }

    bool operator!=(const const_iterator& other) const noexcept {
      return ptr_node_ != other.ptr_node_;
    }

    Node* getNode() { return ptr_node_; }

   protected:
    Node* ptr_node_;
  };

  class ListIterator : public ListConstIterator {
   public:
    ListIterator() noexcept : ListConstIterator() {}
    explicit ListIterator(Node* pos) noexcept : ListConstIterator(pos) {}
    explicit ListIterator(const iterator& other) noexcept
        : ListConstIterator() {
      if (this != &other) {
        this->ptr_node_ = other.ptr_node_;
      }
    }
    explicit ListIterator(iterator&& other) noexcept : ListConstIterator() {
      *this = std::move(other);
    }
    ListIterator(const const_iterator& other) noexcept
        : ListConstIterator(other){};
    iterator& operator=(const iterator& other) noexcept {
      if (this != &other) this->ptr_node_ = other.ptr_node_;
      return *this;
    }
    iterator operator=(iterator&& other) noexcept {
      if (this != &other) {
        this->ptr_node_ = nullptr;
        std::swap(this->ptr_node_, other.ptr_node_);
      }
      return *this;
    }
    ~ListIterator() = default;

    reference operator*() noexcept {
      return (reference)this->ptr_node_->value_;
    }

    iterator& operator++() noexcept {
      this->ptr_node_ = this->ptr_node_->ptr_next_;
      return *this;
    }

    iterator& operator--() noexcept {
      this->ptr_node_ = this->ptr_node_->ptr_prev_;
      return *this;
    }

    bool operator==(const iterator& other) const noexcept {
      return this->ptr_node_ == other.ptr_node_;
    }

    bool operator!=(const iterator& other) const noexcept {
      return this->ptr_node_ != other.ptr_node_;
    }
  };

  size_type size_;
  Node* ptr_head_;
  Node* ptr_tail_;
};

#include "s21_list.tpp"

#endif  // S21_LIST_H